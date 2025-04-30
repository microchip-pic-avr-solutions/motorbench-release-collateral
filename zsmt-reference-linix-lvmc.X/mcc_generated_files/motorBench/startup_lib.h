/**
 * startup_lib.h
 * 
 * ZS/MT DSAT startup
 *
 * API for precompiled library implementation.
 * These functions are intended only for use with MCAF, 
 * and are not documented for standalone usage.
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

#ifndef __STARTUP_LIB_H
#define __STARTUP_LIB_H

#include <stdint.h>
#include <stdbool.h>
#include "motor_control_types.h"
#include "startup_types.h"
// Close coupling with ZSMT estimator
#include "commutation/zsmt_types.h"


#ifdef __cplusplus
extern "C" {
#endif

  
/** Did the state machine happen OK? */
typedef enum tagZSMT_STARTUP_STATEMACHINE_RESULT
{
   ZSR_OK = 0,                   /** Startup proceeded OK */
   ZSR_INVALID_STATE = 1         /** Invalid state */
} ZSMT_STARTUP_STATEMACHINE_RESULT;

/**
 * State machine step for startup and transition from open- to closed-loop commutation
 *
 * Updates the current command (idqCommand) where appropriate.
 * 
 * NOTE: This is an internal interface and subject to change. 
 * Do not reuse outside of the ZS/MT startup code.
 * 
 * @param pstartup startup state
 * @param idqCommand open loop current command
 * @param direction +1 for positive rotation, -1 for negative rotation
 * @param pzsmt estimator state
 * @return a result code (ZSR_OK if succeeded)
 */
extern ZSMT_STARTUP_STATEMACHINE_RESULT ZSMTLIB_StartupTransitioningStep(
        MCAF_MOTOR_STARTUP_DATA *pstartup,
        MC_DQ_T *idqCommand, 
        int16_t direction,
        MCAF_ESTIMATOR_ZSMT_T *pzsmt);


#ifdef __cplusplus
}
#endif

#endif /* __STARTUP_LIB_H */