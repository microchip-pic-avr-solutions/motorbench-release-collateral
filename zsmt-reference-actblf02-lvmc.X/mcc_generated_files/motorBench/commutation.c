/**
 * commutation.c
 *
 * Module to include commutation
 * 
 * Component: commutation
 */ /*
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
 *
 ******************************************************************************/

#include <stdint.h>
#include "units.h"
#include "hal.h"

#include "system_state.h"
#include "commutation.h"
#include "commutation_types.h"
#include "commutation/common.h"
#include "startup.h"
#include "stall_detect_types.h"
#include "test_harness.h"


#include "commutation/zsmt.h"
#include "commutation/pll.h"
#include "commutation/zsmt_hybrid.h"
#include "commutation/zsmt_hybrid_interaction.h"


void MCAF_CommutationStep(MCAF_MOTOR_DATA *pmotor)
{
    MCAF_ESTIMATOR_T *pestimator = &pmotor->estimator;



    /* ---- Zero-speed maximum torque ---- */
    MCAF_EstimatorZsmtStep(
                  &pestimator->zsmt,        // state
                  &pmotor->standardInputs,                   // common inputs
                  &pmotor->motorParameters                   // motorParameters
    );
    if (MCAF_EstimatorZsmtIsActive(pestimator))
    {
        pestimator->theta = MCAF_EstimatorZsmtCommutationAngle(&pestimator->zsmt);
        pestimator->omega = MCAF_EstimatorZsmtElectricalFrequency(&pestimator->zsmt);
    }
    /* ---- Zero-speed maximum torque ---- */

    /* ---- sensorless, phase-locked loop (AN1292 PLL) ---- */
    MCAF_EstimatorPllStep(
                  &pestimator->pll,         // state
                  &pmotor->standardInputs,                   // common inputs
                  &pmotor->motorParameters                   // motorParameters
    );
    if (MCAF_EstimatorPllIsActive(pestimator))
    {
        pestimator->theta = MCAF_EstimatorPllCommutationAngle(&pestimator->pll);
        pestimator->omega = MCAF_EstimatorPllElectricalFrequency(&pestimator->pll);
    }
    /* ---- sensorless, phase-locked loop (AN1292 PLL) ---- */

    /* ---- Binary hard-switch hybrid estimator ('Minotaur') ---- */
    MCAF_EstimatorZsmtHybridStep(
                  &pestimator->zsmtHybrid,   // state
                  &pmotor->standardInputs,                   // common inputs
                  &pmotor->motorParameters                   // motorParameters
    );
    // This estimator has some specific coupling with other modules.    
    MCAF_EstimatorZsmtHybridInteractionStep(
            &pestimator->zsmtHybrid,                   // estimator state
            pmotor,                                    // access to full state
            MCAF_EstimatorPllUpdateOutput,             // pointer to function to update other estimator
            &pestimator->pll                           // other estimator state
    );
    if (MCAF_EstimatorZsmtHybridIsActive(pestimator))
    {
        pestimator->theta = MCAF_EstimatorZsmtHybridCommutationAngle(&pestimator->zsmtHybrid);
        pestimator->omega = MCAF_EstimatorZsmtHybridElectricalFrequency(&pestimator->zsmtHybrid);
    }
    /* ---- Binary hard-switch hybrid estimator ('Minotaur') ---- */

    pmotor->startup.thetaElectricalEstimated = pmotor->estimator.theta;
    pmotor->startup.omegaElectricalEstimated = pmotor->estimator.omega;

    /*
     * Estimators and the test harness are allowed to request
     * a pause in the startup sequence in certain cases.
     *
     * For example, during forced commutation with
     * known fixed current amplitude and commutation frequency,
     * estimators may need to perform a calibration step.
     *
     * The test harness also has a startup pause feature
     * that can delay entering closed-loop operation,
     * to allow diagnosis or troubleshooting.
     */
    const MCAF_STARTUP_STATUS_T startupStatus = MCAF_StartupGetStatus(&pmotor->startup);
    if (startupStatus == MSST_SPIN && MCAF_OverrideStartupPause(&pmotor->testing))
    {
        MCAF_StartupRequestDelay(&pmotor->startup);
    }
    if (MCAF_StartupDelayPermitted(&pmotor->startup))
    {
        if (MCAF_EstimatorZsmtStartupDelayRequested(&pestimator->zsmt, startupStatus))
        {
            MCAF_StartupRequestDelay(&pmotor->startup);
        }
        if (MCAF_EstimatorPllStartupDelayRequested(&pestimator->pll, startupStatus))
        {
            MCAF_StartupRequestDelay(&pmotor->startup);
        }
        if (MCAF_EstimatorZsmtHybridStartupDelayRequested(&pestimator->zsmtHybrid, startupStatus))
        {
            MCAF_StartupRequestDelay(&pmotor->startup);
        }
    }
    
    MCAF_U_ANGLE_ELEC deltatheta;
    if (MCAF_OverrideCommutation(&pmotor->testing))
    {
        deltatheta = MCAF_GetOverrideCommutationFrequency(&pmotor->testing);
    }
    else
    {
        const int16_t motorDirection = UTIL_SignFromHighBit(pmotor->velocityControl.velocityCmd);
        MCAF_StartupTransitioningStep(&pmotor->startup,
            &pmotor->idqCmdRaw, 
            motorDirection,
            &pmotor->estimator.zsmt
        );

        if (MCAF_StartupInOpenLoopCommutation(&pmotor->startup))
        {
            MCAF_U_ANGLE_ELEC thetaElecStartup = MCAF_StartupCalcNextElectricalAngle(&pmotor->startup);
            deltatheta = thetaElecStartup - pmotor->thetaElectrical;
            MCAF_StartupSetThetaError(&pmotor->startup, thetaElecStartup - pmotor->estimator.theta);
            pmotor->omegaCmd = MCAF_StartupGetElectricalFrequency(&pmotor->startup);
        }
        else
        {
            /* Normal closed-loop commutation. We add a compensating factor
             * thetaError during the first part of closed-loop operation;
             * this creates a bumpless transition and thetaError decays toward zero.
             * (See documentation on startup for more information.)
             */
            const MCAF_U_ANGLE_ELEC thetaAdjusted = pmotor->estimator.theta + MCAF_StartupGetThetaError(&pmotor->startup);
            deltatheta = thetaAdjusted - pmotor->thetaElectrical;
        }
    }
    
    pmotor->thetaElectrical += deltatheta;

    {
        // Update required input signals after the estimator step and before QEI sync.
        MCAF_STANDARD_INPUT_SIGNALS_T *pinputs = &pmotor->standardInputs;
        pinputs->startupStatus = MCAF_StartupGetStatus(&pmotor->startup);
        pinputs->thetaForcedCommutation = MCAF_StartupGetIdqCmdAngle(&pmotor->startup);
    }


   pmotor->standardInputs.stateFlags &= ~MSF_CLEAN_STARTUP_SIGNAL;
}

void MCAF_CommutationInit(MCAF_MOTOR_DATA *pmotor)
{
    MCAF_EstimatorZsmtInit(&pmotor->estimator.zsmt, &pmotor->motorParameters);
    MCAF_EstimatorPllInit(&pmotor->estimator.pll, &pmotor->motorParameters);
    MCAF_EstimatorZsmtHybridSetupOutputDependencies(&pmotor->estimator.zsmtHybrid, &pmotor->estimator.zsmt.output, &pmotor->estimator.pll.output);
    MCAF_EstimatorZsmtHybridInit(&pmotor->estimator.zsmtHybrid, &pmotor->motorParameters);
}

void MCAF_CommutationStartupInit(MCAF_MOTOR_DATA *pmotor)
{
    pmotor->estimator.theta = 0;
    pmotor->thetaElectrical = 0;

    pmotor->idqCmdRaw.q = MCAF_STARTUP_CURRENT_INITIAL;
    pmotor->idqCmdRaw.d = 0;
    pmotor->velocityControl.velocityCmdRateLimited = 0;
    pmotor->omegaCmd = 0;
    
 
    /* Provide a clean startup signal for one cycle.
     * This will be cleared at the end of the following commutation step,
     * and allows estimators to reinitialize themselves synchronously
     * to their commutation logic.
     */     
    pmotor->standardInputs.stateFlags |= MSF_CLEAN_STARTUP_SIGNAL;
    MCAF_CommutationStartupReinit(pmotor);
    MCAF_StartupEnable(&pmotor->startup);

    /* Allow estimators to re-initialize on startup */
    MCAF_EstimatorZsmtStartupInit(&pmotor->estimator.zsmt);
    MCAF_EstimatorPllStartupInit(&pmotor->estimator.pll);
    MCAF_EstimatorZsmtHybridStartupInit(&pmotor->estimator.zsmtHybrid);
}

void MCAF_CommutationPrepareStallDetectInputs(MCAF_MOTOR_DATA *pmotor)
{
#if MCAF_INCLUDE_STALL_DETECT      
    MCAF_STALL_DETECT_INPUT_T *pinputs = &pmotor->stallDetect.inputs;
    const MCAF_ESTIMATOR_PLL_T *pll = &pmotor->estimator.pll;

    pinputs->esdq            = pll->esdq;
    pinputs->esdqFiltered    = pll->esdqFiltered;
    pinputs->valphabeta      = pll->lastValphabeta;
    pinputs->omegaElectrical = pll->output.omegaElectrical;
#endif
}