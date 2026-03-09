/**
 * current_measure.h
 *
 * Current measurement routines: multi-channel
 * 
 * Component: ADC compensation
 */

/* *********************************************************************
 *
 * Motor Control Application Framework
 * R9/RC31 (commit 132024, build on 2026 Feb 13)
 *
 * (c) 2017 - 2023 Microchip Technology Inc. and its subsidiaries. You may use
 * this software and any derivatives exclusively with Microchip products.
 *
 * This software and any accompanying information is for suggestion only.
 * It does not modify Microchip's standard warranty for its products.
 * You agree that you are solely responsible for testing the software and
 * determining its suitability.  Microchip has no obligation to modify,
 * test, certify, or support the software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE, OR ITS INTERACTION WITH
 * MICROCHIP PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY
 * APPLICATION.
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL,
 * PUNITIVE, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF
 * ANY KIND WHATSOEVER RELATED TO THE USE OF THIS SOFTWARE, THE
 * motorBench(R) DEVELOPMENT SUITE TOOL, PARAMETERS AND GENERATED CODE,
 * HOWEVER CAUSED, BY END USERS, WHETHER MICROCHIP'S CUSTOMERS OR
 * CUSTOMER'S CUSTOMERS, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES OR THE DAMAGES ARE FORESEEABLE. TO THE
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
 * CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT
 * OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS
 * SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF
 * THESE TERMS.
 *
 * *****************************************************************************/

#ifndef MCAF_CURRENT_MEASURE_H 
#define MCAF_CURRENT_MEASURE_H 

#include <stdint.h>
#include "util.h"
#include "units.h"
#include "current_measure_types.h"
#include "system_state.h"
#include "adc_compensation.h"
#include "parameters/adc_params.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Apply offset to measured current signal based on shunt polarity.
 * 
 * @param measurement raw measurement
 * @param offset value to apply to measurement
 * @param invert polarity of measurement
 * @return compensated measurement
 */
inline static int16_t applyOffset(int16_t measurement, int16_t offset, bool invert)
{
    if (invert)
    {
        return offset - measurement;
    }
    else
    {
        return measurement - offset;
    }
}

/**
 * Apply gain and offset to measured current.
 * 
 * @param pcal current compensation parameters
 * @param piabc raw phase current measurements to compensate
 */
inline static void MCAF_ADCApplyCurrentCompensation(const MCAF_CURRENT_COMPENSATION_PARAMETERS *pcal,
                                             MC_ABC_T *piabc)
{
    const int16_t a1 = applyOffset(piabc->a, pcal->offseta, MCAF_ADCIsPhaseACurrentInverted());
    const int16_t b1 = applyOffset(piabc->b, pcal->offsetb, MCAF_ADCIsPhaseBCurrentInverted());
    
    piabc->a =  (UTIL_mulss(a1, pcal->qKaa)
                +UTIL_mulss(b1, pcal->qKab)) >> 15;
    piabc->b =  (UTIL_mulss(a1, pcal->qKba)
                +UTIL_mulss(b1, pcal->qKbb)) >> 15;

    if (HAL_ADC_IsPhaseCCurrentAvailable())
    {
        const int16_t c1 = applyOffset(piabc->c, pcal->offsetc, MCAF_ADCIsPhaseCCurrentInverted());
        piabc->c = (UTIL_mulss(c1, pcal->qKcc)) >> 15;
    }
}

#if MCAF_ADC_GAIN_COMPENSATION_ENABLED
/**
 * Update gain measured current based on adcGainCompensator.
 * 
 * @param pcal current compensation parameters
 * @param padcgaincompcores adc gain compensator core array
 */
inline static void MCAF_ADCUpdateCurrentCompensation(MCAF_CURRENT_COMPENSATION_PARAMETERS *pcal, MCAF_ADC_GAIN_COMPENSATOR *padcgaincomp)
{
    if (HAL_ADC_IsPhaseACurrentAvailable())
    {
        pcal->qKaa = UTIL_MulQ14(padcgaincomp->core[MCAF_ADC_CORE_PHASEA_CURRENT].compensationFactor, CURRENT_KAA);
    }
    if (HAL_ADC_IsPhaseBCurrentAvailable())
    {
        pcal->qKbb = UTIL_MulQ14(padcgaincomp->core[MCAF_ADC_CORE_PHASEB_CURRENT].compensationFactor, CURRENT_KBB);
    }
#ifdef MCAF_ADC_CORE_PHASEC_CURRENT
    if (HAL_ADC_IsPhaseCCurrentAvailable())
    {
        pcal->qKcc = UTIL_MulQ14(padcgaincomp->core[MCAF_ADC_CORE_PHASEC_CURRENT].compensationFactor, CURRENT_KCC);
    }
#endif
#ifdef MCAF_ADC_CORE_DCLINK_CURRENT
    if (HAL_ADC_IsDCLinkCurrentAvailable())
    {
        pcal->qKidc = UTIL_MulQ14(padcgaincomp->core[MCAF_ADC_CORE_DCLINK_CURRENT].compensationFactor, MCAF_IDC_SCALING_FACTOR);
    }
#endif
}
#endif

/**
 * Obtains motor phase current information from appropriate sources.
 * @param currentMeasure MCAF current measurement
 * @param iabc abc current vector
 */
inline static void MCAF_ADCCurrentRead(const MCAF_CURRENT_MEASUREMENT *currentMeasure, MCAF_U_CURRENT_ABC *iabc)
{
    // dsPIC33A gives unsigned ADC results.
    // XOR with 0x8000 converts to signed format like dsPIC33C/E.
    #ifdef __dsPIC33A__
    const int16_t invert_msb_mask = 0x8000;
    #else
    const int16_t invert_msb_mask = 0x0;
    #endif

    iabc->a = HAL_ADC_ValuePhaseACurrent() ^ invert_msb_mask;
    iabc->b = HAL_ADC_ValuePhaseBCurrent() ^ invert_msb_mask; 
    
    if (HAL_ADC_IsPhaseCCurrentAvailable())
    {
        iabc->c = HAL_ADC_ValuePhaseCCurrent() ^ invert_msb_mask;
    }
}

/**
 * Executes one step of current offset calibration.
 * During the calibration interval, integrates filtered offset
 * based on the compensated measurement value, but only if it is within
 * range.
 * 
 * @param pLPF pointer to low-pass-filter integrator
 * @param measurement compensated measurement
 * @param k integrator gain
 */
inline static void MCAF_ADCCalibrateCurrentOffset(sx1632_t *pLPF, int16_t measurement, int16_t k, bool invert)
{
    const int16_t cal_limit = 2*MCAF_CURRENT_OFS_CAL_RANGE - 1;

    asm volatile ("; BEGIN MCAF_ADCCalibrateCurrentOffset" ::);
    const int16_t adjustment = UTIL_LimitS16(measurement, -cal_limit, cal_limit);
    const int32_t delta = UTIL_mulss(adjustment << MCAF_CURRENT_OFS_CAL_SHIFT, k);
    if (invert)
    {
        pLPF->x32 -= delta;
    }
    else
    {
        pLPF->x32 += delta;
    }
    asm volatile ("; END MCAF_ADCCalibrateCurrentOffset" ::);
}

/**
 * Applies offset
 *
 * @param pLPF low-pass filter state
 * @param poffset offset
 * @return whether it succeeded
 */
inline static bool MCAF_ADCComputeCurrentOffsetCompensation(const sx1632_t* pLPF, int16_t *poffset) {
    const int16_t offset = pLPF->x16.hi >> MCAF_CURRENT_OFS_CAL_SHIFT;
    const bool success = (offset > -MCAF_CURRENT_OFS_CAL_RANGE) && (offset < MCAF_CURRENT_OFS_CAL_RANGE);
    if (success) {
        *poffset = offset;
    }
    return success;
}

/**
 * Executes one step of ADC current compensation
 * 
 * @param pinit motor initialization state data
 * @param pcal current compensation gains
 * @param piabc measured currents
 */
inline static void MCAF_ADCCalibrateCurrentOffsets(MCAF_CURRENT_CALIBRATION *pinit, 
                                                   MCAF_CURRENT_COMPENSATION_PARAMETERS *pcal,
                                                   const MCAF_U_CURRENT_ABC *piabc,
                                                   const MCAF_U_CURRENT pidc)
{
    if (pinit->sampleCount < pinit->sampleCountLimit)
    {
        MCAF_ADCCalibrateCurrentOffset(&pinit->offsetLPF[0],
                                        piabc->a,
                                        pinit->kfilter,
                                        MCAF_ADCIsPhaseACurrentInverted());
        MCAF_ADCCalibrateCurrentOffset(&pinit->offsetLPF[1],
                                        piabc->b,
                                        pinit->kfilter,
                                        MCAF_ADCIsPhaseBCurrentInverted());
        if (HAL_ADC_IsPhaseCCurrentAvailable())
        {
            MCAF_ADCCalibrateCurrentOffset(&pinit->offsetLPF[2],
                                            piabc->c,
                                            pinit->kfilter,
                                            MCAF_ADCIsPhaseCCurrentInverted());
        }
    
        if (!MCAF_ADCComputeCurrentOffsetCompensation(&pinit->offsetLPF[0], &pcal->offseta)) {
            pinit->success = false;
        }
        if (!MCAF_ADCComputeCurrentOffsetCompensation(&pinit->offsetLPF[1], &pcal->offsetb)) {
            pinit->success = false;
        }
        if (HAL_ADC_IsPhaseCCurrentAvailable())
        {
            if (!MCAF_ADCComputeCurrentOffsetCompensation(&pinit->offsetLPF[2], &pcal->offsetc)) {
                pinit->success = false;
            }
        }
        ++pinit->sampleCount;
    }
    else
    {
        pinit->ready = true;
    }
}
/**
 * Initializes state variables for ADC compensation
 * 
 * @param pinit motor initialization state data
 * @param pcal current compensation gains
 */
void MCAF_ADCCompensationInit(MCAF_ADC_COMPENSATION *padccomp, 
                              MCAF_CURRENT_COMPENSATION_PARAMETERS *pcal);

/**
 * Calculate scaled PWM duty cycles from Va,Vb,Vc and the PWM period
 * @param pmotor motor data
 */
void MCAF_ComputeDutyCycleOutputs(MCAF_MOTOR_DATA *pmotor);

/**
  * Initialize multi channel state
  * @param pmultiChannel multi channel state
  */        
 inline static void MCAF_CurrentMeasureInit(MCAF_CURRENT_MEASUREMENT *pmultiChannel) {}
 
 /**
  * Reinitialize multi channel state on restart
  * @param pmultiChannel single channel state
  */        
 inline static void MCAF_CurrentMeasureRestart(MCAF_CURRENT_MEASUREMENT *pmultiChannel) {}
 
#ifdef __cplusplus
}
#endif

#endif /* MCAF_CURRENT_MEASURE_H */
