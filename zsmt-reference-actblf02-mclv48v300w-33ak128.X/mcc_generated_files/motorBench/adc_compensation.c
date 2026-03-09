/**
 * adc_compensation.c
 * 
 * ADC compensation
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

#include <stdint.h>
#include "util.h"
#include "adc_compensation.h"
#include "system_state.h"
#include "parameters/adc_params.h"
#include "parameters/timing_params.h"
#include "hal.h"
#include "current_measure.h"
#include "filter.h"
#include "test_harness.h"

inline static uint16_t adcScaleVdc(uint16_t raw)
{
    const uint32_t vdcscaled = UTIL_muluu(raw, MCAF_VDC_SCALING_FACTOR);
    // Saturate if we can't shift right into a uint16_t
    return UTIL_SatShrU16(vdcscaled, MCAF_VDC_SCALING_FACTOR_Q);
}

#if MCAF_ADC_GAIN_COMPENSATION_ENABLED

static const unsigned int core_list[] = MCAF_ADC_CORE_LIST;

/**
 * Gain compensator update for all enabled cores on 33A devices 
 * 
 * @param padcgaincomp adc gain compensation data
 * @param padcGainCompOffset test-harness gain offset for each core
 */
static void adcGainCompFilterUpdate(MCAF_ADC_GAIN_COMPENSATOR *padcgaincomp, volatile MCAF_MOTOR_TEST_MANAGER *ptest)
{
    for (uint16_t i = 0; i < MCAF_ADC_NUM_CORES_USED; ++i)
    {
        const uint16_t zero_index = core_list[i] - 1;

        // "upperVoltageDivider" value is Q15 from the Q16 ADC value
        padcgaincomp->core[zero_index].upperVoltageDivider = HAL_ADC_ValueUpperVoltageDivider(core_list[i]) >> 1;
        #ifdef MCAF_TEST_ADC_GAIN_COMPENSATION
        padcgaincomp->core[zero_index].upperVoltageDivider += ptest->adcGainOffset[zero_index];
        #endif

        MCAF_FilterLowPassS16Update(&padcgaincomp->core[zero_index].filter, padcgaincomp->core[zero_index].upperVoltageDivider);
    }
}

/** 
 * Compute a Q14 gain compensation factor for all enabled cores on 33A devices (nominally 1.0 Q14 = 1/2 Q15)
 * 
 * @param padcgaincomp adc gain compensation data
 */
static void adcGainCompFactorUpdate(MCAF_ADC_GAIN_COMPENSATOR *padcgaincomp)
{
    const uint16_t nominal_adc_reading = (15 * (1<<14)) / 16;
    const int16_t nominal_adc_min = (14 * (1<<15)) / 16; // 1/16 is 6.25%

    for (uint16_t i = 0; i < MCAF_ADC_NUM_CORES_USED; ++i)
    {
        const uint16_t zero_index = core_list[i] - 1;

        padcgaincomp->success &= padcgaincomp->core[zero_index].filter.state.x16.hi > nominal_adc_min;
        if (padcgaincomp->success)
        {
            // compensation factor = expected value / test value
            padcgaincomp->core[zero_index].compensationFactor = UTIL_DivQ15(nominal_adc_reading, padcgaincomp->core[zero_index].filter.state.x16.hi);
        }
    }
}

/** 
 * Upper voltage divider gain compensation for 33A devices
 *
 * @param pmotor motor data
 */
void MCAF_ADCGainCompensationStep(MCAF_MOTOR_DATA *pmotor)
{
    MCAF_ADC_GAIN_COMPENSATOR *padcgaincomp = &pmotor->adcCompensation.adcGainCompensator;
    if (HAL_ADC_IsUpperVoltageDividerAvailable())
    {
        if (padcgaincomp->sampleCount < padcgaincomp->sampleCountLimit)
        {
            adcGainCompFilterUpdate(padcgaincomp, &pmotor->testing);
            adcGainCompFactorUpdate(padcgaincomp);
            ++padcgaincomp->sampleCount;
        }
        else
        {
            MCAF_ADCUpdateCurrentCompensation(&pmotor->currentCalibration, padcgaincomp);
            padcgaincomp->ready = true;
        }
    }
    else
    {
        padcgaincomp->ready = true;
    }
}

#endif

/**
 * Reads ADC samples for current phases, auxiliary analog inputs,
 * and routes results to appropriate area in motor data structure.
 *
 * @param pmotor motor data
*/
void MCAF_ADCRead(MCAF_MOTOR_DATA *pmotor)
{
    MCAF_ADCCurrentRead(&pmotor->currentMeasure, &pmotor->iabc);
#ifdef MCAF_TEST_ADC_OFFSET_COMPENSATION
    pmotor->iabc.a += pmotor->testing.currentOffset[0];
    pmotor->iabc.b += pmotor->testing.currentOffset[1];
    if (HAL_ADC_IsPhaseCCurrentAvailable())
    {
        pmotor->iabc.c += pmotor->testing.currentOffset[2];
    }
#endif
    MCAF_ADCApplyCurrentCompensation(&pmotor->currentCalibration, &pmotor->iabc);

    uint16_t unipolarADCResult;
    #ifdef __dsPIC33A__
    unipolarADCResult = HAL_ADC_ValueDCLinkVoltage();
    #else
    unipolarADCResult = HAL_ADC_UnsignedFromSignedInput(HAL_ADC_ValueDCLinkVoltage());
    #endif

    if (MCAF_ADCIsVdcScaled())
    {
        unipolarADCResult = adcScaleVdc(unipolarADCResult);
    }
    pmotor->psys->vDC = unipolarADCResult >> 1;
    pmotor->vDC = pmotor->psys->vDC;
}

/**
 * Reads ADC samples that are not time critical
 * and routes results to appropriate area in motor data structure.
 *
 * @param pmotor motor data
*/
void MCAF_ADCReadNonCritical(MCAF_MOTOR_DATA *pmotor)
{    
    /* The default ADC result is bipolar with 0 counts =
     * the middle of the input voltage range.
     * VDC sensing is an exception to this rule.
     */
 
    if (HAL_ADC_IsBridgeTemperatureAvailable())
    {
        const uint16_t raw = HAL_ADC_ValueBridgeTemperature();
        
        MCAF_BRIDGE_TEMPERATURE *pbtemp = &pmotor->bridgeTemperature;
        pbtemp->raw = raw;
        pbtemp->processed = UTIL_MulUUQ16(raw, pbtemp->gain) - pbtemp->offset;
        const int32_t dT = UTIL_mulus(pbtemp->filter.gain, pbtemp->processed)
                         - UTIL_mulus(pbtemp->filter.gain, pbtemp->filter.state.x16.hi);
        const int16_t dT_limited = UTIL_LimitS32ToS16(dT, pbtemp->filter.slewRate);
        pbtemp->filter.state.x32 += dT_limited;
        pbtemp->filter.output = pbtemp->filter.state.x16.hi;                
    }

    if (HAL_ADC_IsAbsoluteReferenceVoltageAvailable())
    {
        pmotor->vAbsRef = HAL_ADC_ValueAbsoluteReferenceVoltage();
    }
}

void MCAF_ADCCurrentOffsetCalibrationInit(MCAF_CURRENT_CALIBRATION *pcal)
{
    pcal->sampleCount = 0;
    pcal->success = true;
    pcal->ready = false;
    pcal->sampleCountLimit = MCAF_CURRENT_OFS_CAL_COUNT;
    pcal->offsetLPF[0].x32 = 0;
    pcal->offsetLPF[1].x32 = 0;
    pcal->offsetLPF[2].x32 = 0;
    pcal->kfilter = MCAF_CURRENT_OFS_CAL_FILTER_GAIN;
}

#if MCAF_ADC_GAIN_COMPENSATION_ENABLED
/**
 * Initializes low pass filter used for ADC gain compensation
 */
static void initGainCompFilter(MCAF_ADC_GAIN_COMPENSATOR_CORE *pcompensatorcore, uint16_t coeff)
{
    const uint16_t init_output = (15 * (1<<15)) / 16; //Initialize compensator to 15/16 max Q15 value
    MCAF_FilterLowPassS16Init(&pcompensatorcore->filter, coeff, init_output);
    pcompensatorcore->compensationFactor = 16384; // Q14(1.0)
}

void MCAF_ADCGainCompInit(MCAF_ADC_GAIN_COMPENSATOR *pcompensator)
{
    pcompensator->sampleCountLimit = MCAF_GAIN_COMP_COUNT;
    MCAF_ADCGainCompRestart(pcompensator);
    for (uint16_t i = 0; i < MCAF_ADC_MAX_CORE_USED; ++i) 
    {
        initGainCompFilter(&pcompensator->core[i], MCAF_FILTER_COEFF_GAIN_COMP);
    }
}
#endif
