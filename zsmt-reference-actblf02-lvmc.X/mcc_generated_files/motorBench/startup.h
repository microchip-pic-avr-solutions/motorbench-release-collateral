/**
 * startup.h
 * 
 * Module for startup and open loop to closed loop transition 
 *
 * Component: state machine
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

#ifndef __STARTUP_H
#define __STARTUP_H

#include <stdint.h>
#include <stdbool.h>
#include "util.h"
#include "motor_control_types.h"
#include "startup_types.h"
#include "parameters/startup_params.h"
// Close coupling with ZSMT estimator
#include "commutation/zsmt_types.h"
#include "startup_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initializes state variables used for startup and open to close transition
 * 
 * @param pstartup startup state
 */
void MCAF_StartupTransitioningInit(MCAF_MOTOR_STARTUP_DATA *pstartup);

/**
 * Handle failure in the startup state machine
 *
 * This is an internal function of this module and subject to change.
 *
 * @param result   result of the state machine step function
 * @param pstartup startup state
 */
void MCAF_StartupOnError(ZSMT_STARTUP_STATEMACHINE_RESULT result, 
                         MCAF_MOTOR_STARTUP_DATA *pstartup);

/**
 * State machine step for startup and transition from open- to closed-loop commutation
 *
 * Updates the current command (idqCommand) where appropriate.
 * 
 * @param pstartup startup state
 * @param idqCommand open loop current command
 * @param direction +1 for positive rotation, -1 for negative rotation
 * @param pzsmt estimator state
 */
inline void MCAF_StartupTransitioningStep(MCAF_MOTOR_STARTUP_DATA *pstartup, 
                                   MC_DQ_T *idqCommand, 
                                   int16_t direction,
                                   MCAF_ESTIMATOR_ZSMT_T *pzsmt
) 
{
    ZSMT_STARTUP_STATEMACHINE_RESULT result =
       ZSMTLIB_StartupTransitioningStep(pstartup, idqCommand, direction, pzsmt);

    if (result != ZSR_OK)
    {
        MCAF_StartupOnError(result, pstartup);
    }
}


/**
 * Reinitializes the startup process.
 * 
 * @param pstartup startup state
 */
inline static void MCAF_StartupReinit(MCAF_MOTOR_STARTUP_DATA *pstartup, int16_t direction)
{
    pstartup->omegaElectrical.x32 = 0;
    pstartup->thetaElectrical.x32 = ((int32_t)pstartup->rampupAngle) << 16;
    pstartup->state = SSM_START;
    pstartup->counter = 0;
    pstartup->complete = false;
    pstartup->enable = false;
    pstartup->delayRequest = false;
    pstartup->iRampupLimit = STARTUP_TORQUE_RAMPUP_RATE;
    ++pstartup->restartCount;
}

/**
 * Allows the startup process to proceed.
 * 
 * @param pstartup startup state
 */
inline static void MCAF_StartupEnable(MCAF_MOTOR_STARTUP_DATA *pstartup)
{
    pstartup->enable = true;
}

/**
 * Returns whether startup has completed
 * 
 * @param pstartup startup state
 * @return true if startup has completed
 */
inline static bool MCAF_StartupHasCompleted(const MCAF_MOTOR_STARTUP_DATA *pstartup)
{
    return pstartup->complete;
}

/**
 * Returns whether startup is in open-loop commutation
 * 
 * @param pstartup startup state
 * @return true if startup is in open-loop commutation
 */
inline static bool MCAF_StartupInOpenLoopCommutation(const MCAF_MOTOR_STARTUP_DATA *pstartup)
{
    return pstartup->state < SSM_PLL_LOCK;
}

/**
 * Returns the startup electrical angle
 * 
 * @param pstartup startup state
 * @return the startup electrical angle
 */
inline static int16_t MCAF_StartupGetElectricalAngle(const MCAF_MOTOR_STARTUP_DATA *pstartup)
{
    return pstartup->thetaElectrical.x16.hi;
}

/**
 * Sets the startup electrical angle.
 * This should only be used with knowledge of what's going on in startup
 * (for example, that omegaElectrical = 0 in the align phase)
 * 
 * @param pstartup startup state
 * @param theta electrical angle
 */
inline static void MCAF_StartupSetElectricalAngle(MCAF_MOTOR_STARTUP_DATA *pstartup, MCAF_U_ANGLE_ELEC theta)
{
    pstartup->thetaElectrical.x16.hi = theta;
}

/**
 * Returns the startup electrical frequency
 * 
 * @param pstartup startup state
 * @return the startup electrical frequency
 */
inline static int16_t MCAF_StartupGetElectricalFrequency(const MCAF_MOTOR_STARTUP_DATA *pstartup)
{
    return pstartup->omegaElectrical.x16.hi;
}

/**
 * Calculates the next electrical angle in open-loop commutation.
 * 
 * @param pstartup startup state
 * @return the next startup electrical angle
 */
inline static int16_t MCAF_StartupCalcNextElectricalAngle(MCAF_MOTOR_STARTUP_DATA *pstartup)
{
    pstartup->thetaElectrical.x32 += 
            UTIL_mulss(pstartup->dt, MCAF_StartupGetElectricalFrequency(pstartup));
    return MCAF_StartupGetElectricalAngle(pstartup);
}

/**
 * Returns whether the reference frame has been flipped (rotated 180)
 * 
 * @param pstartup startup state
 * @return true if the reference frame has been flipped
 */
inline static bool MCAF_StartupReferenceFrameFlip(MCAF_MOTOR_STARTUP_DATA *pstartup)
{
    return pstartup->referenceFrameInvert;
}

#ifdef __cplusplus
}
#endif

#endif /* __STARTUP_H */