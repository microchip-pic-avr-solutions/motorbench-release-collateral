/**
 * fault_detect.h
 *
 * Module to detect when motor fault happened
 * 
 * Component: supervisory
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

#ifndef MCAF_FAULT_DETECT_H 
#define MCAF_FAULT_DETECT_H 

#include "fault_detect_types.h"
#include "system_state.h"
#include "adc_compensation.h"
#include "hal.h"

#if MCAF_GATE_DRIVER_ENABLED
#include "hal/gate_driver_interface.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif


/**
 * This function initializes the Fault Detect function
 *
 * Summary : Inits the non recoverable faults module
 *
 * @param pFaultDetect This parameter is pointer to MCAF_FAULT_DETECT_T structure
 */
void MCAF_FaultDetectInit(MCAF_FAULT_DETECT_T *pFaultDetect);

/**
 * This function reset the Fault Detect function
 *
 * Summary : Reset the non recoverable faults module
 *
 * @param pFaultDetect This parameter is pointer to MCAF_FAULT_DETECT_T structure
 */
void MCAF_FaultDetectReset(MCAF_FAULT_DETECT_T *pFaultDetect);


/**
 * This function returns whether an fault fault occurred
 *
 * Summary : Returns whether a fault happened
 *
 * @param pfaultDetect This parameter is pointer to MCAF_FAULT_DETECT_T structure
 * @return whether a fault has been detected
 */
static inline bool MCAF_Fault_IsFaultDetected(MCAF_FAULT_DETECT_T *pfaultDetect)
{
    return pfaultDetect->faultDetectFlag != 0;
}

/**
 * This function returns whether an overvoltage fault occurred
 *
 * Summary : Returns whether an overvoltage happened
 *
 * @param pVoltageDetect This parameter is pointer to MCAF_DCLINKVOLTAGE_DETECT_T structure
 * @param pmotor This parameter is pointer to MCAF_MOTOR_DATA structure
 * @return whether an overvoltage fault has been detected
 */
inline static bool MCAF_OvervoltageDetect(const MCAF_DCLINKVOLTAGE_DETECT_T *pVoltageDetect,
        const MCAF_MOTOR_DATA *pmotor)
{
    return pmotor->psys->vDC > pVoltageDetect->vDCOvervoltageThreshold;
}

/**
 * Returns whether an undervoltage fault occurred
 *
 * @param pVoltageDetect pointer to voltage detection thresholds
 * @param pmotor motor state 
 * @return true if an undervoltage fault has been detected
 */
inline static bool MCAF_UndervoltageDetect(const MCAF_DCLINKVOLTAGE_DETECT_T *pVoltageDetect,
        const MCAF_MOTOR_DATA *pmotor)
{
    return pmotor->psys->vDC < pVoltageDetect->vDCUndervoltageThreshold;
}

/**
 * This function returns whether a hardware overcurrent fault occurred
 *
 * Summary : Returns whether a hardware overcurrent happened
 *
 * @return whether a hardware overcurrent fault has been detected
 */
inline static bool MCAF_OvercurrentHWDetect(void)
{
    return HAL_PWM_FaultStatus_Get();
}

/**
 * Returns whether an overtemperature fault occurred
 *
 * @param threshold temperature threshold
 * @param pmotor motor state 
 * @return true if an overtemperature fault has been detected 
 */
inline static bool MCAF_OvertemperatureDetect(MCAF_U_TEMPERATURE threshold,
                                              const MCAF_MOTOR_DATA *pmotor)
{
    bool faultActive = HAL_ADC_IsBridgeTemperatureAvailable() && 
                        pmotor->bridgeTemperature.filter.output > threshold;
    return faultActive;
}

/**
 * Returns whether a current offset calibration fault occurred
 *
 * @param pmotor motor state 
 * @return true if a current offset calibration fault has been detected 
 */
inline static bool MCAF_CurrCalOffsetFaultDetect(const MCAF_MOTOR_DATA *pmotor)
{
    return !MCAF_ADCCurrentOffsetCalibrationSuccessful(&pmotor->adcCompensation.currentCalibration);
}

#if MCAF_ADC_GAIN_COMPENSATION_ENABLED
/**
 * Returns whether an ADC gain compensation fault occurred
 *
 * @param pmotor motor state 
 * @return true if an ADC gain compensation fault has been detected 
 */
inline static bool MCAF_ADCGainCompFaultDetect(const MCAF_MOTOR_DATA *pmotor)
{
    const MCAF_ADC_GAIN_COMPENSATOR *pcompensator = &pmotor->adcCompensation.adcGainCompensator;
    return MCAF_ADCGainCompReady(pcompensator) && !MCAF_ADCGainCompSuccessful(pcompensator);
}
#endif

/**
 * This function updates the fault status in special designated status registers
 *
 * Summary : Updates the fault detection flags for each specific fault detected
 *
 * @param pfaultDetect This parameter is pointer to MCAF_FAULT_DETECT_T structure
 * @param pmotor This parameter is pointer to MCAF_MOTOR_DATA structure
 */
void MCAF_FaultDetect(MCAF_FAULT_DETECT_T *pfaultDetect, const MCAF_MOTOR_DATA *pmotor);

#if MCAF_GATE_DRIVER_ENABLED
/**
 * Returns whether a gate driver fault occurred
 * 
 * @return true if a gate driver fault has been detected
 */
inline static bool MCAF_GateDriverFaultDetect(void)
{
    return HAL_GateDriver_FaultIsActive();
}

/**
 * Returns whether the gate driver fault flag is set
 * @param pfaultinfo fault info
 * @return true if the gate driver fault flag is set
 */
inline static bool MCAF_IsGateDriverFaultFlagSet(const MCAF_FAULT_DETECT_T *pfaultinfo)
{
    return pfaultinfo->faultDetectFlag & MCAF_GATE_DRIVER_FAULT_DETECT;
}
#endif

/**
 * Returns whether the overvoltage flag is set
 * @param pfaultinfo fault info 
 * @return true if overvoltage flag is set
 */
inline static bool MCAF_IsOvervoltageFlagSet(const MCAF_FAULT_DETECT_T *pfaultinfo)
{
    return pfaultinfo->faultDetectFlag & MCAF_OVERVOLTAGE_FAULT_DETECT;
}

/**
 * Returns whether the undervoltage flag is set
 * @param pfaultinfo fault info 
 * @return true if undervoltage flag is set
 */
inline static bool MCAF_IsUndervoltageFlagSet(const MCAF_FAULT_DETECT_T *pfaultinfo)
{
    return pfaultinfo->faultDetectFlag & MCAF_UNDERVOLTAGE_FAULT_DETECT;
}

/**
 * Returns whether the overcurrent flag is set
 * @param pfaultinfo fault info 
 * @return true if overcurrent flag is set
 */
inline static bool MCAF_IsOvercurrentFlagSet(const MCAF_FAULT_DETECT_T *pfaultinfo)
{
    return pfaultinfo->faultDetectFlag & MCAF_OVERCURRENT_HW_FAULT_DETECT;
}

/**
 * Returns whether the overvoltage flag is set
 * @param pfaultinfo fault info 
 * @return true if overvoltage flag is set
 */
inline static bool MCAF_IsOvertemperatureFlagSet(const MCAF_FAULT_DETECT_T *pfaultinfo)
{
    return pfaultinfo->faultDetectFlag & MCAF_OVERTEMPERATURE_FAULT_DETECT;
}

/**
 * Returns whether the current offset calibration fault flag is set
 * @param pfaultinfo fault info 
 * @return true if current offset calibration fault flag is set
 */
inline static bool MCAF_IsCurrCalOffsetFaultFlagSet(const MCAF_FAULT_DETECT_T *pfaultinfo)
{
    return pfaultinfo->faultDetectFlag & MCAF_CURR_OFFSET_CAL_FAULT_DETECT;
}

#if MCAF_ADC_GAIN_COMPENSATION_ENABLED
/**
 * Returns whether the ADC gain compensation fault flag is set
 * @param pfaultinfo fault info 
 * @return true if ADC gain compensation fault flag is set
 */
inline static bool MCAF_IsADCGainCompFaultFlagSet(const MCAF_FAULT_DETECT_T *pfaultinfo)
{
    return pfaultinfo->faultDetectFlag & MCAF_ADC_GAIN_COMP_FAULT_DETECT;
}
#endif

/**
 * Returns whether any fault flag is set
 * @param pfaultinfo fault info 
 * @return true if any fault flag is set
 */
inline static bool MCAF_IsAnyFaultFlagSet(const MCAF_FAULT_DETECT_T *pfaultinfo)
{
    return pfaultinfo->faultDetectFlag != 0;
}

#ifdef __cplusplus
}
#endif

#endif /* MCAF_FAULT_DETECT_H */
