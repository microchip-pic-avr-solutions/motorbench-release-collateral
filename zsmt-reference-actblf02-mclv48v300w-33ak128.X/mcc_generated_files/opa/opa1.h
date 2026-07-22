/**
 * OPA1 Generated Driver Header File
 * 
 * @file      opa1.h
 * 
 * @ingroup   opadriver
 * 
 * @brief     This is the generated driver header file for the OPA1 driver
 *
 * @version   PLIB Version 1.2.3
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

#ifndef OPA1_H
#define OPA1_H


#ifdef __cplusplus
extern "C" {
#endif

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
 extern const struct OPA_INTERFACE MCC_OPA_1;

/**
 * @ingroup  opadriver
 * @brief    This macro defines the Custom Name for \ref OPA1_Initialize API
 */
#define MCC_OPA_1_Initialize OPA1_Initialize
/**
 * @ingroup  opadriver
 * @brief    This macro defines the Custom Name for \ref OPA1_Deinitialize API
 */
#define MCC_OPA_1_Deinitialize OPA1_Deinitialize
/**
 * @ingroup  opadriver
 * @brief    This macro defines the Custom Name for \ref OPA1_Enable API
 */
#define MCC_OPA_1_Enable OPA1_Enable
/**
 * @ingroup  opadriver
 * @brief    This macro defines the Custom Name for \ref OPA1_Disable API
 */
#define MCC_OPA_1_Disable OPA1_Disable
/**
 * @ingroup  opadriver
 * @brief    This macro defines the Custom Name for \ref OPA1_UnityGainEnable API
 */
#define MCC_OPA_1_UnityGainEnable OPA1_UnityGainEnable
/**
 * @ingroup  opadriver
 * @brief    This macro defines the Custom Name for \ref OPA1_HighPowerModeEnable API
 */
#define MCC_OPA_1_HighPowerModeEnable OPA1_HighPowerModeEnable
/**
 * @ingroup  opadriver
 * @brief    This macro defines the Custom Name for \ref OPA1_OutputMonitorEnable API
 */
#define MCC_OPA_1_OutputMonitorEnable OPA1_OutputMonitorEnable
/**
 * @ingroup  opadriver
 * @brief    This macro defines the Custom Name for \ref OPA1_DifferentialInputModeSet API
 */
#define MCC_OPA_1_DifferentialInputModeSet OPA1_DifferentialInputModeSet
/**
 * @ingroup  opadriver
 * @brief    This macro defines the Custom Name for \ref OPA1_OffsetCorrection API
 */
#define MCC_OPA_1_OffsetCorrection OPA1_OffsetCorrection

// Section: Interface Routines

/**
 * @ingroup  opadriver
 * @brief    Initializes the OPA module
 * @param    none
 * @return   none  
 */
void OPA1_Initialize (void);

/**
 * @ingroup  opadriver
 * @brief    Deinitializes the OPA1 to POR values
 * @param    none
 * @return   none  
 */
void OPA1_Deinitialize(void);

/**
 * @ingroup  opadriver
 * @brief    This inline function enables OPA1 module
 * @pre      The OPA1_Initialize function should be called for the 
 *           specified OPA1 driver instance.
 * @param    none
 * @return   none  
 */
inline static void OPA1_Enable( void )
{
    AMP1CON1bits.AMPEN = 1U; //Enable opa;
}

/**
 * @ingroup  opadriver
 * @brief    This inline function disables OPA1 module
 * @param    none
 * @return   none  
 */
inline static void OPA1_Disable( void )
{
    AMP1CON1bits.AMPEN = 0U; //Disable opa;
}

/**
 * @ingroup    opadriver
 * @brief      This inline function enables/disables unity gain of OPA1 module
 * @param[in]  enable - true, enables unity gain 
 * @param[in]  enable - false, disables unity gain  
 * @return     none  
 */
inline static void OPA1_UnityGainEnable( bool enable )
{
    AMP1CON1bits.UGE = enable;     
}

/**
 * @ingroup    opadriver
 * @brief      This inline function enables/disables high power mode of OPA1 module
 * @param[in]  enable - true, enables High Power Mode
 * @param[in]  enable - false, disables High Power Mode 
 * @return     none  
 */
inline static void OPA1_HighPowerModeEnable( bool enable )
{
    AMP1CON1bits.HPEN = enable;     
}

/**
 * @ingroup    opadriver
 * @brief      This inline function enables/disables Enables output of OPA1 module to ADC
 * @param[in]  enable - true, enables output Monitor
 * @param[in]  enable - false, disables output Monitor 
 * @return     none  
 */
inline static void OPA1_OutputMonitorEnable( bool enable )
{
    AMP1CON1bits.OMONEN = enable;     
}

/**
 * @ingroup    opadriver
 * @brief      This inline function enables/disables Enables output of OPA1 module to ADC
 * @param[in]  input - selected differential input mode
 * @return     none  
 */
inline static void OPA1_DifferentialInputModeSet(enum OPA_DIFFERENTIAL_INPUT_MODE input)
{
    AMP1CON1bits.DIFFCON = input;     
}

/**
 * @ingroup    opadriver
 * @brief      This inline function enables/disables Enables output of OPA1 module to ADC
 * @param[in]  inputType   - selected differential input offset register type
 * @param[in]  unitVoltage - selected unit voltage
 * @return     none  
 * @Note       Unit voltage = trim step voltage 3 mV
 */
inline static void OPA1_OffsetCorrection(enum OPA_OFFSET_INPUT_TYPE inputType, enum OPA_OUTPUT_VOLTAGE_OFFSET_CORRECTION unitVoltage)
{
    switch(inputType)
    {
        case OPA_PMOS_OFFSET_IN_HIGH_POWER_MODE:
            AMP1CON2bits.POFFSETHP = unitVoltage;
            break;
            
        case OPA_NMOS_OFFSET_IN_HIGH_POWER_MODE:
            AMP1CON2bits.NOFFSETLP = unitVoltage;
            break;
            
        case OPA_PMOS_OFFSET_IN_LOW_POWER_MODE:
            AMP1CON2bits.POFFSETHP  = unitVoltage;
            break;
            
        case OPA_NMOS_OFFSET_IN_LOW_POWER_MODE:
            AMP1CON2bits.NOFFSETLP  = unitVoltage;
            break;
            
        default:
            break;
    }
}

#ifdef __cplusplus
}
#endif

#endif //OPA1_H

/**
 End of File
*/




