/**
 * diagnostics.c
 * 
 * Diagnostics code
 * 
 * Component: diagnostics
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

#include "X2Cscope.h"
#include "hal.h"
#include <stdint.h>

#define X2C_DATA __attribute__((section("x2cscope_data_buf")))
#define X2C_BUFFER_SIZE 4900
#define X2C_APP_VERSION 0x0800
compilationDate_t compilationDate = {__DATE__, __TIME__};

X2C_DATA static uint8_t X2C_BUFFER[X2C_BUFFER_SIZE];
    /*
     * baud rate = 70MHz/16/(1+baudrate_divider) for highspeed = false
     * baud rate = 70MHz/4/(1+baudrate_divider) for highspeed = true
     * 
     * 4375kbaud => 0 (for DIAG_BAUDRATE_DIVIDER with highspeed = false)
     * 2188kbaud => 1
     * 1458kbaud => 2
     * 1094kbaud => 3
     *  875kbaud => 4
     *  729kbaud => 5
     *  625kbaud => 6
     *  547kbaud => 7
     *  486kbaud => 8
     *  437kbaud => 9
     *  397kbaud => 10
     *  364.6kbaud => 11
     *  336.5kbaud => 12
     *  312.5kbaud => 13
     *  291.7kbaud => 14
     *  273.4kbaud => 15
     *  257.3kbaud => 16
     *  243.1kbaud => 17
     *  230.2kbaud => 18
     *  115.1kbaud => 37
     *   57.6kbaud => 75
     */

void X2Cscope_Init(void);

void MCAF_DiagnosticsInit(void)
{
    HAL_UART_Initialize();
    
    X2Cscope_Init();
}

void MCAF_DiagnosticsStepMain(void)
{
    X2Cscope_Communicate();
}

void MCAF_DiagnosticsStepIsr(void)
{
    X2Cscope_Update();
}

/* ---------- communication primitives used by X2Cscope library ---------- */

static void X2Cscope_sendSerial(uint8_t data)
{
    HAL_UART_Write(data);
}

static uint8_t X2Cscope_receiveSerial()
{
    return HAL_UART_Read();
}

static uint8_t X2Cscope_isReceiveDataAvailable()
{
    return HAL_UART_IsRxReady();
}

static uint8_t X2Cscope_isSendReady()
{
    return HAL_UART_IsTxReady();
}

void X2Cscope_Init(void)
{
    X2Cscope_HookUARTFunctions(
        X2Cscope_sendSerial,
        X2Cscope_receiveSerial,
        X2Cscope_isReceiveDataAvailable,
        X2Cscope_isSendReady);
    X2Cscope_Initialise(X2C_BUFFER, sizeof(X2C_BUFFER), X2C_APP_VERSION, compilationDate);
}