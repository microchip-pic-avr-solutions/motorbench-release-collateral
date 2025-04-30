/**
 * zsmtlib.h
 * 
 * Zero speed / maximum torque (ZSMT) estimator
 * 
 * API for precompiled library implementation.
 * These functions are intended only for use with MCAF, 
 * and are not documented for standalone usage.
 * 
 * Component: commutation
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

#ifndef __ZSMTLIB_H
#define __ZSMTLIB_H

#include <stdint.h>
#include "foc_types.h"
#include "zsmt_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Executes one control step of the ZS/MT estimator.
 * @param pzsmt ZS/MT state variable structure
 * @param pinput Standard algorithm inputs (e.g. stationary-frame voltage and current)
 * @param pmotor Motor parameters
 */
extern void ZSMTLIB_EstimatorZsmtStep(MCAF_ESTIMATOR_ZSMT_T *pzsmt,
                                const MCAF_STANDARD_INPUT_SIGNALS_T *pinput,
                                const MCAF_MOTOR_PARAMETERS_T *pmotor);

/**
 * Initializes state variables prior to starting motor.
 * 
 * @param pzsmt ZS/MT state variable structure
 */
void ZSMTLIB_EstimatorZsmtStartupInit(MCAF_ESTIMATOR_ZSMT_T *pzsmt);

#ifdef __cplusplus
}
#endif

#endif /* __ZSMTLIB_H */