/**
 * OPA2 Generated Driver Source File
 * 
 * @file      opa2.c
 * 
 * @ingroup   opadriver
 * 
 * @brief     This is the generated driver source file for OPA2 driver
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
#include "../opa2.h"

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
 *        customerName.OPA2_UnityGainEnable();
 * @endcode
 */
const struct OPA_INTERFACE MCC_OPA_2 = {
    .Intitialize        	  = &OPA2_Initialize,
    .Deintitialize      	  = &OPA2_Deinitialize,
    .Enable            	      = &OPA2_Enable,
    .Disable            	  = &OPA2_Disable,
    .UnityGainEnable          = &OPA2_UnityGainEnable,
    .HighPowerModeEnable      = &OPA2_HighPowerModeEnable,
    .OutputMonitorEnable      = &OPA2_OutputMonitorEnable,
    .DifferentialInputModeSet = &OPA2_DifferentialInputModeSet,
    .OffsetCorrection         = &OPA2_OffsetCorrection,
};
// Section: Driver Interface Function Definitions

void OPA2_Initialize (void)
{
    OPA2_HighPowerModeEnable(true);
    OPA2_DifferentialInputModeSet(OPA_DIFFERENTIAL_INPUT_NMOS_PMOS_PAIR);
    OPA2_OutputMonitorEnable(true);
    OPA2_Enable();
}

void OPA2_Deinitialize (void)
{
    OPA2_Disable();
    
    AMP2CON1 = 0x0;
    AMP2CON2 = 0x0;
}

/**
 End of File
*/
