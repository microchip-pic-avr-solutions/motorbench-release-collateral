/**
 * fault_handle.h
 *
 * Module to handle latched fault flags when motor is in fault condition
 * 
 * Component: supervisory
 */

/* *********************************************************************
 *
 * Motor Control Application Framework
 * R8/RC38 (commit 128946, build on 2025 Apr 09)
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

#ifndef __FAULT_HANDLE_H
#define __FAULT_HANDLE_H

#include "fault_handle_types.h"
#include "parameters/timing_params.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Returns whether the PWM clear flag is pending
 * 
 * @param pFaultHandle fault handle state data
 * @return true if PWM clear flag is pending
 */
inline static bool MCAF_PWMClearFlagPending(const MCAF_FAULT_HANDLE_T *pFaultHandle)
{
    return pFaultHandle->pwmClearDelay == 0;
}

/**
 * Returns whether the HW overcurrent flag is pending
 * 
 * @param pFaultHandle fault handle state data
 * @return true if HW overcurrent flag is pending
 */
inline static bool MCAF_OvercurrentHWFlagPending(const MCAF_FAULT_HANDLE_T *pFaultHandle)
{
    return pFaultHandle->faultLatchDelay == 0;
}

/**
 * Set the motor drive fault handle flag
 * 
 * @param pFaultHandle fault handle state data
 */
inline static void MCAF_SetMotorDriveFaultHandleFlag(MCAF_FAULT_HANDLE_T *pFaultHandle)
{
    pFaultHandle->motorDriveFaultClear = true;
}

/**
 * Clear the motor drive fault handle flag
 * 
 * @param pFaultHandle fault handle state data
 */
inline static void MCAF_ClearMotorDriveFaultHandleFlag(MCAF_FAULT_HANDLE_T *pFaultHandle)
{
    pFaultHandle->motorDriveFaultClear = false;
}

/**
 * Set the overcurrent fault handle flag
 * 
 * @param pFaultHandle fault handle state data
 */
inline static void MCAF_SetOvercurrentFaultHandleFlag(MCAF_FAULT_HANDLE_T *pFaultHandle)
{
    pFaultHandle->overCurrentFaultClear = true;
}

/**
 * Clear the overcurrent fault handle flag
 * 
 * @param pFaultHandle fault handle state data
 */
inline static void MCAF_ClearOvercurrentFaultHandleFlag(MCAF_FAULT_HANDLE_T *pFaultHandle)
{
    pFaultHandle->overCurrentFaultClear = false;
}

/**
 * Set the fault latch delay to one ISR cycle if it is zero
 * 
 * @param pFaultHandle fault handle state data
 */
inline static void MCAF_SetFaultLatchDelay(MCAF_FAULT_HANDLE_T *pFaultHandle)
{
    if (pFaultHandle->faultLatchDelay == 0)
    {
        pFaultHandle->faultLatchDelay = 1;
    }
}

/**
 * Set the PWM clear delay to one ISR cycle if it is zero
 * 
 * @param pFaultHandle fault handle state data
 */
inline static void MCAF_SetPWMClearDelay(MCAF_FAULT_HANDLE_T *pFaultHandle)
{
    if (pFaultHandle->pwmClearDelay == 0)
    {
        pFaultHandle->pwmClearDelay = 1;
    }
}

/**
 * Returns whether the overcurrent fault handle flag is pending
 * 
 * @param pFaultHandle fault handle state data
 * @return true if the overcurrent fault handle flag is pending
 */
inline static bool MCAF_OvercurrentFaultHandleFlagPending(const MCAF_FAULT_HANDLE_T *pFaultHandle)
{
    return pFaultHandle->overCurrentFaultClear;
}

/**
 * Returns whether the motor drive fault handle flag is pending
 * 
 * @param pFaultHandle fault handle state data
 * @return true if the motor drive fault handle flag is pending
 */
inline static bool MCAF_MotorDriveFaultHandleFlagPending(const MCAF_FAULT_HANDLE_T *pFaultHandle)
{
    return pFaultHandle->motorDriveFaultClear;
}

/**
 * Returns whether it is ready to clear HW flag
 * 
 * @param pFaultHandle fault handle state data
 * @return true if it is ready to clear HW flag
 */
inline static bool MCAF_OvercurrentHWFlagAttemptClearReady(MCAF_FAULT_HANDLE_T *pFaultHandle)
{
    return --pFaultHandle->faultLatchDelay == 0;
}

/**
 * Returns whether the overcurrent fault clear process is ready to begin
 * 
 * @param pFaultHandle fault handle state data
 * @return true if overcurrent fault clear process is ready to begin
 */
inline static bool MCAF_OvercurrentFaultClearBegin(MCAF_FAULT_HANDLE_T *pFaultHandle)
{
    if (pFaultHandle->overCurrentFaultClear)
    {
        MCAF_ClearOvercurrentFaultHandleFlag(pFaultHandle);
        return true;
    }
    return false;
}

/**
 * Handles the latched delay ISR cycles,
 * and returns whether the overcurrent fault flag is ready to clear
 * 
 * @param pFaultHandle fault handle state data
 * @return true if the overcurrent fault flag is ready to clear
 */
inline static bool MCAF_OvercurrentFaultClearContinue(MCAF_FAULT_HANDLE_T *pFaultHandle)
{
    if (!MCAF_OvercurrentHWFlagPending(pFaultHandle))
    {
        MCAF_SetPWMClearDelay(pFaultHandle);
        return MCAF_OvercurrentHWFlagAttemptClearReady(pFaultHandle);
    } 
    else if (!MCAF_PWMClearFlagPending(pFaultHandle))
    {
        if (--pFaultHandle->pwmClearDelay == 0)
        {
            MCAF_SetOvercurrentFaultHandleFlag(pFaultHandle);
        }
    }
    return false;
}


/**
 * Initialize the non recoverable faults handle module
 * @param pFaultHandle fault handle state data
 */
void MCAF_FaultHandleInit(MCAF_FAULT_HANDLE_T *pFaultHandle);

/**
 * Initialize the fault latch delay,
 * this is only applied once after a device reset
 * @param pFaultHandle fault handle state data
 */
void MCAF_FaultLatch_PowerupInit(MCAF_FAULT_HANDLE_T *pFaultHandle);

#ifdef __cplusplus
}
#endif

#endif /* __FAULT_DETECT_H */

