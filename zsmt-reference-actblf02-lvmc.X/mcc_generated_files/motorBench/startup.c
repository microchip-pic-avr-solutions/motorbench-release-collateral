/**
 * startup.c
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

#include <stdint.h>
#include <stdbool.h>
#include "startup.h"
#include "parameters/timing_params.h"
#include "parameters/startup_params.h"
#include "ui.h"
#include "error_codes.h"
#include "util.h"
#include "parameters/zsmt_params.h"
// Close coupling with ZSMT estimator
#include "commutation/zsmt_types.h"

void MCAF_StartupTransitioningInit(MCAF_MOTOR_STARTUP_DATA *pstartup)
{
    pstartup->alignTime = 0;
    pstartup->rampupAngle = STARTUP_RAMPUP_ANGLE;
    pstartup->alignAngleDelta = STARTUP_ALIGN_ANGLE_DELTA;
    pstartup->iAmplitude = MCAF_STARTUP_CURRENT;
    pstartup->dt = STARTUP_DELTA_T_FACTOR;
    
    pstartup->pllLockTime                = ZSMT_PLL_LOCK_TIME;
    pstartup->pllLockSpeedLimit          = ZSMT_PLL_LOCK_SPEED_LIMIT;
    pstartup->pllLockCurrentSquaredLimit = ZSMT_PLL_LOCK_CURRENT_SQUARED_LIMIT;
    pstartup->idsat = ZSMT_ANGLE_PROBE_CURRENT;
    pstartup->angleProbeTime = ZSMT_ANGLE_PROBE_TIME;
    pstartup->idsatSlewRate = ZSMT_ANGLE_PROBE_SLEW_RATE;
    pstartup->blankingTime = ZSMT_ANGLE_PROBE_BLANKING_TIME;
    pstartup->demodAmplitudeAccum.gain = ZSMT_ANGLE_PROBE_ACCUM_GAIN;
            
    pstartup->referenceFrameInvert = false;
    
    pstartup->restartCount = 0;
}

void MCAF_StartupOnError(ZSMT_STARTUP_STATEMACHINE_RESULT result, 
                         MCAF_MOTOR_STARTUP_DATA *pstartup)
{
    if (result == ZSR_INVALID_STATE)
    {
        MCAF_UiFlashErrorCodeForever(ERR_INVALID_STARTUP_FSM_STATE);
    }
}


