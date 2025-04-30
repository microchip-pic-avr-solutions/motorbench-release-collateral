/**
 * foc.h
 * 
 * Module to include field-oriented-control functions
 * 
 * Component: FOC
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

#ifndef __FOC_H
#define __FOC_H

#include <stdbool.h>
#include "system_state.h"
#include "hal.h"
#include "fault_handle.h"
#include "test_harness.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize FOC state variables
 * 
 * @param pmotor motor state
 * @return <code>true</code> if the function succeeds
 */
bool MCAF_FocInit(MCAF_MOTOR_DATA *pmotor);

/**
 * Executes forward-path signal calculations of field-oriented control.
 * Includes control loops and forward modulation (Park, Clarke, SVM/ZSM)
 * 
 * @param pmotor motor state
 */
void MCAF_FocStepIsrForwardPath(MCAF_MOTOR_DATA *pmotor);

/**
 * Executes feedback-path signal calculations of field-oriented control.
 * Includes Park, Clarke transforms, estimators, and sine/cosine calculations.
 * 
 * @param pmotor motor state 
 */
void MCAF_FocStepIsrFeedbackPath(MCAF_MOTOR_DATA *pmotor);

/**
 * Executes non-critical tasks towards the end of the ISR
 * 
 * @param pmotor motor state
 */
void MCAF_FocStepIsrNonCriticalTask(MCAF_MOTOR_DATA *pmotor);

/**
 * Executes required calculations for FOC in the main loop.
 * 
 * @param pmotor motor state.
 */
void MCAF_FocStepMain(MCAF_MOTOR_DATA *pmotor);

/**
 * Executes one step of offset calibration
 * 
 * @param pmotor motor data
 */
void MCAF_FocCalibrateCurrentOffsets(MCAF_MOTOR_DATA *pmotor);

/**
 * Reads the ADC channels for FOC.
 * 
 * This should occur at the beginning of the ADC ISR.
 * Reads the dedicated S&H for A- and B-phase currents,
 * then the mux'd ADC channel.
 * 
 * @param pmotor motor data structure
 */
void MCAF_FocReadADC(MCAF_MOTOR_DATA *pmotor);

/**
 * Updates the velocity command for FOC.
 * 
 * This should occur at the beginning of the ADC ISR.
 * Updates the velocity command from MCAPI.
 * 
 * @param pmotor motor data structure
 */
inline static void MCAF_UpdateVelocityCommand(MCAF_MOTOR_DATA *pmotor)
{
    if (!MCAF_OverrideVelocityCommand(&pmotor->testing))
    {
        pmotor->velocityControl.velocityCmd = pmotor->velocityControl.velocityCmdApi;
    }
}

/**
 * Initialize integrators at startup
 * 
 * @param pmotor motor data structure
 */
inline static void MCAF_FocInitializeIntegrators(MCAF_MOTOR_DATA *pmotor)
{
    /* zero out integrators */
    pmotor->idCtrl.integrator = 0;
    pmotor->iqCtrl.integrator = 0;
    pmotor->omegaCtrl.integrator = 0;    
}

/**
 * Reinitialize motor controllers on restart
 * (when exiting error / debug states)
 * @param pmotor motor data structure
 */
inline static void MCAF_FocRestart(MCAF_MOTOR_DATA *pmotor)
{
    pmotor->initialization.ready = false;
    MCAF_SetFaultLatchDelay(&pmotor->faultHandle);
}

/**
 * Returns whether the ADC initialization is ready
 *
 * @param pmotor motor data structure
 * @return true if ADC initialization is ready
 */
inline static bool MCAF_ADCInitializationReady(const MCAF_MOTOR_DATA *pmotor)
{
    return pmotor->initialization.ready;
}


#ifdef __cplusplus
}
#endif

#endif /* __FOC_H */
