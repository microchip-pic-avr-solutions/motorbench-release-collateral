/**
 * board_service.h
 * 
 * Provides hardware-independent board service components with interfaces
 * extending into the HAL.
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

#ifndef __MCAF_BOARD_SERVICE_H
#define __MCAF_BOARD_SERVICE_H

#include <stdbool.h>
#include "hal.h"
#include "board_service_types.h"
#include "parameters/options.h"

#if MCAF_GATE_DRIVER_ENABLED
#include "hal/gate_driver_interface.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
    
/**
 * Configures the board. This function is intended to be called from the main 
 * process during initialization phase, only after 
 * the SYSTEM_Initialize() completes.
 * @param pboard board state data
 */
void MCAF_BoardServiceInit(MCAF_BOARD_DATA *pboard);

/**
 * This function is intended to be called from the main loop.
 * Currently, no operations are performed in this function.
 * @param pboard board state data
 */
void MCAF_BoardServiceStepMain(MCAF_BOARD_DATA *pboard);

/**
 * Executes board service tasks every board service period.
 * @param pboard board state data
 */
void MCAF_BoardServiceTasks(MCAF_BOARD_DATA *pboard);

/**
 * Get the value of the potentiometer.
 * @param pboard board state data
 * @return int16_t potentiometer value
 */
inline static int16_t MCAF_BoardServicePotentiometerValue(const MCAF_BOARD_DATA *pboard) 
{ 
    return HAL_ADC_UnsignedFromSignedInput(HAL_ADC_ValuePotentiometer());
}

/**
 * Get whether or not button1 press event has occured.
 * @param pboard board state data
 * @return bool button1 value
 */
bool MCAF_ButtonGp1_EventGet(const MCAF_BOARD_DATA *pboard);

/**
 * Get whether or not button2 press event has occured.
 * @param pboard board state data
 * @return bool button2 value
 */
bool MCAF_ButtonGp2_EventGet(const MCAF_BOARD_DATA *pboard);

/**
 * Clears the button1 flag.
 * @param pboard board state data
 */
void MCAF_ButtonGp1_EventClear(MCAF_BOARD_DATA *pboard);

/**
 * Clears the button2 flag.
 * @param pboard board state data
 */
void MCAF_ButtonGp2_EventClear(MCAF_BOARD_DATA *pboard);

#if MCAF_GATE_DRIVER_ENABLED
/**
 * Indicates if the gate driver is ready
 * @param pGateDriver gate driver state data
 * @return true when the gate driver has been initialized
 */
inline static bool MCAF_GateDriverReady(volatile const MCAF_GATE_DRIVER_T *pGateDriver)
{
    return pGateDriver->status == GATE_DRIVER_READY;
}

/**
 * This function initializes gate driver state
 * @param pGateDriver gate driver state data
 */
inline static void MCAF_GateDriverInit(volatile MCAF_GATE_DRIVER_T *pGateDriver)
{
    pGateDriver->faultFlags = 0;
    pGateDriver->status = GATE_DRIVER_UNINITIALIZED;
}

/**
 * Executes gate driver service tasks
 * @param pGateDriver gate driver state data
 */
inline static void MCAF_GateDriverService(volatile MCAF_GATE_DRIVER_T *pGateDriver)
{
    pGateDriver->status = HAL_GateDriver_HandleCommunication();
    HAL_GateDriver_ReadFaultFlags(pGateDriver);
}
#endif

#ifdef __cplusplus
}
#endif

#endif /* __MCAF_BOARD_SERVICE_H */