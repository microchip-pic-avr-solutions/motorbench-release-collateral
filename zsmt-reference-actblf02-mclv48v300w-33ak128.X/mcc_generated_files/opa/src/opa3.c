/**
 * OPA3 Generated Driver Source File
 * 
 * @file      opa3.c
 * 
 * @ingroup   opadriver
 * 
 * @brief     This is the generated driver source file for OPA3 driver
 *
 * @skipline @version   PLIB Version 1.2.2
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
#include "../opa3.h"

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
const struct OPA_INTERFACE MCC_OPA_3 = {
    .Intitialize        	  = &OPA3_Initialize,
    .Deintitialize      	  = &OPA3_Deinitialize,
    .Enable            	      = &OPA3_Enable,
    .Disable            	  = &OPA3_Disable,
    .UnityGainEnable          = &OPA3_UnityGainEnable,
    .HighPowerModeEnable      = &OPA3_HighPowerModeEnable,
    .OutputMonitorEnable      = &OPA3_OutputMonitorEnable,
    .DifferentialInputModeSet = &OPA3_DifferentialInputModeSet,
    .OffsetCorrection         = &OPA3_OffsetCorrection,
};
// Section: Driver Interface Function Definitions

void OPA3_Initialize (void)
{
    OPA3_HighPowerModeEnable(true);
    OPA3_DifferentialInputModeSet(OPA_DIFFERENTIAL_INPUT_NMOS_PMOS_PAIR);
    OPA3_OutputMonitorEnable(true);
    OPA3_Enable();
}

void OPA3_Deinitialize (void)
{
    OPA3_Disable();
    
    AMP3CON1 = 0x0;
    AMP3CON2 = 0x0;
}

/**
 End of File
*/
