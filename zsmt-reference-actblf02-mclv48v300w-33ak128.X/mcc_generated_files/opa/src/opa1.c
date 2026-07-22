/**
 * OPA1 Generated Driver Source File
 * 
 * @file      opa1.c
 * 
 * @ingroup   opadriver
 * 
 * @brief     This is the generated driver source file for OPA1 driver
 *
 * @skipline @version   PLIB Version 1.2.3
 *
 * @skipline  Device : dsPIC33AK128MC106
*/

/*
© [2026] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

// Section: Included Files

#include <stdlib.h>
#include "../opa1.h"

// Section: File specific functions
// Section: File specific data type definitions

/**
 * @ingroup  opadriver
 * @brief    Defines an object for OPA_INTERFACE.
 *           For hardware dependent APIs, make sure the API is not NULL 
 *           before calling it.
 * 
 * @b Example:
 * @code
 *        customerName.OPA1_UnityGainEnable();
 * @endcode
 */
const struct OPA_INTERFACE MCC_OPA_1 = {
    .Intitialize        	  = &OPA1_Initialize,
    .Deintitialize      	  = &OPA1_Deinitialize,
    .Enable            	      = &OPA1_Enable,
    .Disable            	  = &OPA1_Disable,
    .UnityGainEnable          = &OPA1_UnityGainEnable,
    .HighPowerModeEnable      = &OPA1_HighPowerModeEnable,
    .OutputMonitorEnable      = &OPA1_OutputMonitorEnable,
    .DifferentialInputModeSet = &OPA1_DifferentialInputModeSet,
    .OffsetCorrection         = &OPA1_OffsetCorrection,
};
// Section: Driver Interface Function Definitions

void OPA1_Initialize (void)
{
    OPA1_HighPowerModeEnable(true);
    OPA1_DifferentialInputModeSet(OPA_DIFFERENTIAL_INPUT_NMOS_PMOS_PAIR);
    OPA1_OutputMonitorEnable(true);
    OPA1_Enable();
}

void OPA1_Deinitialize (void)
{
    OPA1_Disable();
    
    AMP1CON1 = 0x0;
    AMP1CON2 = 0x0;
}

/**
 End of File
*/
