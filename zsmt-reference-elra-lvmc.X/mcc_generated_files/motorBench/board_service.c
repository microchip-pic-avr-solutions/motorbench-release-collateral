/**
 * board_service.c
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

#include <stdbool.h>
#include "board_service.h"
#include "error_codes.h"
#include "ui.h"
#include "parameters/hal_params.h"
#include "parameters/timing_params.h"

#if MCAF_GATE_DRIVER_ENABLED
#include "hal/gate_driver_interface.h"
#endif

/**
 * Initializes the state variables for a given button.
 * @param pButtonData pointer to a BOARD_BUTTON_DATA_T struct
 */
static void MCAF_ButtonInit(volatile BOARD_BUTTON_DATA_T *pButtonData)
{
    pButtonData->buttonState = BOARD_BUTTON_UNPRESSED;
    pButtonData->shortButtonPress = false;
    pButtonData->longButtonPress = false;
    pButtonData->counterC1 = 0;
}

/**
 * Runs the button handler to debounce button inputs and 
 * check for short and long press events.
 * @param pButtonData pointer to a BOARD_BUTTON_DATA_T struct
 * @param rawInput is the raw GPIO signal from the board switch
 */
static void MCAF_ButtonService(volatile BOARD_BUTTON_DATA_T *pButtonData, bool rawInput)
{   
    switch(pButtonData->buttonState)
    {
        default:
        case BOARD_BUTTON_UNPRESSED:
        pButtonData->counterC1++;
        if (rawInput)
        {
            if (pButtonData->counterC1 >= MCAF_BUTTON_DEBOUNCE_TIME)
            {
                pButtonData->buttonState = BOARD_BUTTON_PRESSED;
                pButtonData->counterC1 = 0;
            }
        }
        else
        {
            pButtonData->buttonState = BOARD_BUTTON_UNPRESSED;
            pButtonData->counterC1 = 0;
        }
        break;
        
        case BOARD_BUTTON_PRESSED:
        pButtonData->counterC1++;
        if (pButtonData->counterC1 >= MCAF_BUTTON_LONG_PRESS_TIME)
        {
            pButtonData->longButtonPress = true;
            pButtonData->buttonState = BOARD_BUTTON_LONGPRESS;
        }
        else if (!rawInput)
        {
            pButtonData->shortButtonPress = true;
            pButtonData->counterC1 = 0;
            pButtonData->buttonState = BOARD_BUTTON_UNPRESSED;
        }
        break;
        
        case BOARD_BUTTON_LONGPRESS:
        if (!rawInput)
        {
            pButtonData->counterC1 = 0;
            pButtonData->buttonState = BOARD_BUTTON_UNPRESSED;
        }
        break;
    }
}

void MCAF_BoardServiceInit(MCAF_BOARD_DATA *pboard)
{
    pboard->configComplete = true;
    pboard->runtimeState = HAL_BOARD_READY;
    pboard->isrCount = 0;
    MCAF_ButtonInit(&pboard->sw1);
    MCAF_ButtonInit(&pboard->sw2);
#if MCAF_GATE_DRIVER_ENABLED
    MCAF_GateDriverInit(&pboard->gateDriver);
#endif
}

void MCAF_BoardServiceStepMain(MCAF_BOARD_DATA *pboard)
{
    
}

void MCAF_BoardServiceTasks(MCAF_BOARD_DATA *pboard)
{
    MCAF_ButtonService(&pboard->sw1, HAL_ButtonGp1RawInput());
    MCAF_ButtonService(&pboard->sw2, HAL_ButtonGp2RawInput());
#if MCAF_GATE_DRIVER_ENABLED
    MCAF_GateDriverService(&pboard->gateDriver);
#endif
}

bool MCAF_ButtonGp1_EventGet(const MCAF_BOARD_DATA *pboard)
{
    return pboard->sw1.shortButtonPress;
}

bool MCAF_ButtonGp2_EventGet(const MCAF_BOARD_DATA *pboard)
{
    if (HAL_hasTwoButtons())
    {
        return pboard->sw2.shortButtonPress;
    }
    else
    {
        return pboard->sw2.longButtonPress;
    }
}

void MCAF_ButtonGp1_EventClear(MCAF_BOARD_DATA *pboard)
{
    pboard->sw1.shortButtonPress = false;
}

void MCAF_ButtonGp2_EventClear(MCAF_BOARD_DATA *pboard)
{
    if (HAL_hasTwoButtons())
    {
        pboard->sw2.shortButtonPress = false;
    }
    else
    {
        pboard->sw2.longButtonPress = false;
    }
}