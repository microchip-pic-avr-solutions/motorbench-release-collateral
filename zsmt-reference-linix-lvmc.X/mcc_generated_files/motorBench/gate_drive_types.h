/**
 * gate_drive_types.h
 * 
 * Provides type definitions for the gate drive module.
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

#ifndef __MCAF_GATE_DRIVE_TYPES_H
#define __MCAF_GATE_DRIVE_TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include "hal/hardware_access_functions_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * State machine states for bootstrap charging routine
 */
typedef enum tagMCAF_BOOTSTRAP_FSM_STATE
{
    /** Initialization state */
    MCBS_IDLE_START = 0,
    /** WAIT state before starting the bootstrap charging sequence */
    MCBS_WAIT_INITIAL = 1,
    /** Set up state for PHASE A bootstrap charging */
    MCBS_PHASE_A_SETUP_CHARGING = 2,
    /** PHASE A bootstrap charging */
    MCBS_PHASE_A_CHARGING = 3,
    /** Set up state for PHASE B bootstrap charging */
    MCBS_PHASE_B_SETUP_CHARGING = 4,
    /** PHASE B bootstrap charging */
    MCBS_PHASE_B_CHARGING = 5,
    /** Set up state for PHASE C bootstrap charging */
    MCBS_PHASE_C_SETUP_CHARGING = 6,
    /** PHASE C bootstrap charging */
    MCBS_PHASE_C_CHARGING = 7,
    /** Bootstrap charging is complete */
    MCBS_BOOTSTRAP_COMPLETE = 8
} MCAF_BOOTSTRAP_FSM_STATE;

typedef struct tagMCAF_BOOTSTRAP_STATE
{
    /** Bootstrap charging routine state */
    MCAF_BOOTSTRAP_FSM_STATE state;
    /** Bootstrap charging duty cycles of Phase A, B, and C */
    uint16_t dutycycle[3];
    /** Count used to cause delay in several states */
    uint16_t delayCount;
} MCAF_BOOTSTRAP_STATE;

#ifdef __cplusplus
}
#endif

#endif /* __MCAF_GATE_DRIVE_TYPES_H */