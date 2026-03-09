/**
 * OPA3 Generated Driver Header File
 * 
 * @file      opa3.h
 * 
 * @ingroup   opadriver
 * 
 * @brief     This is the generated driver header file for the OPA3 driver
 *
 * @version   PLIB Version 1.2.2
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

#ifndef OPA3_H
#define OPA3_H

// Section: Included Files

#include <xc.h>
#include <stdint.h>
#include "opa_interface.h"
// Section: Data Type Definitions

/**
 * @ingroup  opadriver
 * @brief    Structure object of type OPA_INTERFACE with the custom name
 *           given by the user in the Melody Driver User interface. The default name 
 *           e.g. OPA can be changed by the user in the OPA user interface. 
 *           This allows defining a structure with application specific name using 
 *           the 'Custom Name' field. Application specific name allows the API Portability.
*/
extern const struct OPA_INTERFACE MCC_OPA_3;

/**
 * @ingroup  opadriver
 * @brief    This macro defines the Custom Name for \ref OPA3_Initialize API
 */
#define MCC_OPA_3_Initialize OPA3_Initialize
/**
 * @ingroup  opadriver
 * @brief    This macro defines the Custom Name for \ref OPA3_Deinitialize API
 */
#define MCC_OPA_3_Deinitialize OPA3_Deinitialize
/**
 * @ingroup  opadriver
 * @brief    This macro defines the Custom Name for \ref OPA3_Enable API
 */
#define MCC_OPA_3_Enable OPA3_Enable
/**
 * @ingroup  opadriver
 * @brief    This macro defines the Custom Name for \ref OPA3_Disable API
 */
#define MCC_OPA_3_Disable OPA3_Disable
/**
 * @ingroup  opadriver
 * @brief    This macro defines the Custom Name for \ref OPA3_UnityGainEnable API
 */
#define MCC_OPA_3_UnityGainEnable OPA3_UnityGainEnable
/**
 * @ingroup  opadriver
 * @brief    This macro defines the Custom Name for \ref OPA3_HighPowerModeEnable API
 */
#define MCC_OPA_3_HighPowerModeEnable OPA3_HighPowerModeEnable
/**
 * @ingroup  opadriver
 * @brief    This macro defines the Custom Name for \ref OPA3_OutputMonitorEnable API
 */
#define MCC_OPA_3_OutputMonitorEnable OPA3_OutputMonitorEnable
/**
 * @ingroup  opadriver
 * @brief    This macro defines the Custom Name for \ref OPA3_DifferentialInputModeSet API
 */
#define MCC_OPA_3_DifferentialInputModeSet OPA3_DifferentialInputModeSet
/**
 * @ingroup  opadriver
 * @brief    This macro defines the Custom Name for \ref OPA3_OffsetCorrection API
 */
#define MCC_OPA_3_OffsetCorrection OPA3_OffsetCorrection

// Section: Interface Routines

/**
 * @ingroup  opadriver
 * @brief    Initializes the OPA module
 * @param    none
 * @return   none  
 */
void OPA3_Initialize (void);

/**
 * @ingroup  opadriver
 * @brief    Deinitializes the OPA3 to POR values
 * @param    none
 * @return   none  
 */
void OPA3_Deinitialize(void);

/**
 * @ingroup  opadriver
 * @brief    This inline function enables OPA3 module
 * @pre      The OPA3_Initialize function should be called for the 
 *           specified OPA3 driver instance.
 * @param    none
 * @return   none  
 */
inline static void OPA3_Enable( void )
{
    AMP3CON1bits.AMPEN = 1U; //Enable opa;
}

/**
 * @ingroup  opadriver
 * @brief    This inline function disables OPA3 module
 * @param    none
 * @return   none  
 */
inline static void OPA3_Disable( void )
{
    AMP3CON1bits.AMPEN = 0U; //Disable opa;
}

/**
 * @ingroup    opadriver
 * @brief      This inline function enables/disables unity gain of OPA3 module
 * @param[in]  enable - true, enables unity gain 
 * @param[in]  enable - false, disables unity gain  
 * @return     none  
 */
inline static void OPA3_UnityGainEnable( bool enable )
{
    AMP3CON1bits.UGE = enable;     
}

/**
 * @ingroup    opadriver
 * @brief      This inline function enables/disables high power mode of OPA3 module
 * @param[in]  enable - true, enables High Power Mode
 * @param[in]  enable - false, disables High Power Mode 
 * @return     none  
 */
inline static void OPA3_HighPowerModeEnable( bool enable )
{
    AMP3CON1bits.HPEN = enable;     
}

/**
 * @ingroup    opadriver
 * @brief      This inline function enables/disables Enables output of OPA3 module to ADC
 * @param[in]  enable - true, enables output Monitor
 * @param[in]  enable - false, disables output Monitor 
 * @return     none  
 */
inline static void OPA3_OutputMonitorEnable( bool enable )
{
    AMP3CON1bits.OMONEN = enable;     
}

/**
 * @ingroup    opadriver
 * @brief      This inline function enables/disables Enables output of OPA3 module to ADC
 * @param[in]  input - selected differential input mode
 * @return     none  
 */
inline static void OPA3_DifferentialInputModeSet(enum OPA_DIFFERENTIAL_INPUT_MODE input)
{
    AMP3CON1bits.DIFFCON = input;     
}

/**
 * @ingroup    opadriver
 * @brief      This inline function enables/disables Enables output of OPA3 module to ADC
 * @param[in]  inputType   - selected differential input offset register type
 * @param[in]  unitVoltage - selected unit voltage
 * @return     none  
 * @Note       Unit voltage = trim step voltage 3 mV
 */
inline static void OPA3_OffsetCorrection(enum OPA_OFFSET_INPUT_TYPE inputType, enum OPA_OUTPUT_VOLTAGE_OFFSET_CORRECTION unitVoltage)
{
    switch(inputType)
    {
        case OPA_PMOS_OFFSET_IN_HIGH_POWER_MODE:
            AMP3CON2bits.POFFSETHP = unitVoltage;
            break;
            
        case OPA_NMOS_OFFSET_IN_HIGH_POWER_MODE:
            AMP3CON2bits.NOFFSETLP = unitVoltage;
            break;
            
        case OPA_PMOS_OFFSET_IN_LOW_POWER_MODE:
            AMP3CON2bits.POFFSETHP  = unitVoltage;
            break;
            
        case OPA_NMOS_OFFSET_IN_LOW_POWER_MODE:
            AMP3CON2bits.NOFFSETLP  = unitVoltage;
            break;
            
        default:
            break;
    }
}

#endif //OPA3_H

/**
 End of File
*/




