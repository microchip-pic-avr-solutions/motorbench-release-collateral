/**
 * board_service_types.h
 * 
 * Provides type defines for the hardware-independent board service module.
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

#ifndef __MCAF_BOARD_SERVICE_TYPES_H
#define __MCAF_BOARD_SERVICE_TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include "hal/hardware_access_functions_types.h"
#include "parameters/options.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum tagBOARD_BUTTON_STATE
{
    BOARD_BUTTON_PRESSED   = 0, /** board button is pressed */
    BOARD_BUTTON_UNPRESSED = 1, /** board button is not pressed */
    BOARD_BUTTON_LONGPRESS = 2  /** board button is held down for a long duration */
} BOARD_BUTTON_STATE;
    
typedef struct tagBOARD_BUTTON_DATA_T
{ 
    BOARD_BUTTON_STATE buttonState; /** button state machine */   
    bool shortButtonPress;          /** button flag */
    bool longButtonPress;           /** button flag */
    uint16_t counterC1;             /** used for debounce delay, and button long press timing */
} BOARD_BUTTON_DATA_T;

#if MCAF_GATE_DRIVER_ENABLED

/** return code representing the gate driver status */
typedef enum tagGATE_DRIVER_STATUS
{
    GATE_DRIVER_UNINITIALIZED  = 0, /** the gate driver is not initialized */
    GATE_DRIVER_INITIALIZATION = 1, /** the gate driver is in the process of initialization */
    GATE_DRIVER_READY          = 2, /** the gate driver is fully initialized and ready for operation  */
    GATE_DRIVER_ERROR          = 3  /** the gate driver encounters an error */
} GATE_DRIVER_STATUS;

typedef struct tagMCAF_GATE_DRIVER_T
{  
    uint16_t faultFlags;        /** Fault flags read out from the gate driver */
    GATE_DRIVER_STATUS status;  /** Gate driver status code */
} MCAF_GATE_DRIVER_T;
#endif

typedef struct tagMCAF_BOARD_DATA
{ 
    /** This flag determines which function to be called among 
     *  Board_Service() or Board_Configure() functions
     *  if equals to '0' - Board_Configure()
     *  if equals to '1' - Board_Service()
     */
    bool configComplete;
    /** Maintains runtime state of Board_Service() or Board_Configure() functions */
    HAL_BOARD_STATUS runtimeState;
    /** This variable is used to pre-scale the execution of board service 
     * routines,and is incremented in MCAF_BoardServiceStepIsr */ 
    volatile uint16_t isrCount;

#if MCAF_GATE_DRIVER_ENABLED
    /** 
     * Gate driver status, obtained from gate driver in board service routines
     * and used in MCAF_SystemStateMachine_StepIsr
     */
    volatile MCAF_GATE_DRIVER_T gateDriver;
#endif

    BOARD_BUTTON_DATA_T sw1;
    BOARD_BUTTON_DATA_T sw2;
    
} MCAF_BOARD_DATA;

#ifdef __cplusplus
}
#endif

#endif /* __MCAF_BOARD_SERVICE_TYPES_H */