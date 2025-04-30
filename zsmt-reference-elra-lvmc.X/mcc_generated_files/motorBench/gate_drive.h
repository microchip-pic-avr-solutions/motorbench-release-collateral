/**
 * gate_drive.h
 * 
 * Provides routines for gate drive management.
 * 
 * Component: HAL
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

#ifndef __MCAF_GATE_DRIVE_H
#define __MCAF_GATE_DRIVE_H

#include <stdbool.h>
#include "hal.h"
#include "gate_drive_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initializes the state variables used by the bootstrap charging routine. This function
 * should be called after a board power-up event, and before MCAF_BootstrapChargeStepIsr().
 * @param pbootstrap bootstrap state data
 */
void MCAF_BootstrapChargeInit(MCAF_BOOTSTRAP_STATE *pbootstrap);

/**
 * Executes one step of the bootstrap charging sequence.
 * This is a non-blocking function that should be called after MCAF_BootstrapChargeInit().
 * It implements a state machine to soft-start the board by sequentially ramping up phase
 * duty cycle values to the desired value. This bootstrap step occurs in the control ISR.
 * @param pbootstrap bootstrap state data
 * @return bool value true when bootstrap sequence is complete
 */
bool MCAF_BootstrapChargeStepIsr(MCAF_BOOTSTRAP_STATE *pbootstrap);

#ifdef __cplusplus
}
#endif

#endif /* __MCAF_GATE_DRIVE_H */