/**
 * ADC2 Generated Driver Header File
 * 
 * @file      adc2.h
 *            
 * @ingroup   adcdriver
 *            
 * @brief     This is the generated driver header file for the ADC2 driver          
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

#ifndef ADC2_H
#define ADC2_H


#ifdef __cplusplus
extern "C" {
#endif

// Section: Included Files

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include "adc_common.h"
#include "../system/interrupt_types.h"

// Section: Data Types

/** 
  @ingroup  adcdriver
  @brief    Defines the ADC Resolution
*/
#define ADC2_RESOLUTION 12

// Section: Driver Interface Functions

/**
 * @ingroup  adcdriver
 * @brief    Initializes ADC2 module, using the given initialization data
 *           This function must be called before any other ADC2 function is called
 * @param    none
 * @return   none  
 */
void ADC2_Initialize (void);

/**
 * @ingroup  adcdriver
 * @brief    This inline function enables the ADC2 module
 * @pre      \ref ADC2_IsReady must be called to know the status of ADC
 * @param    none
 * @return   none  
 */
inline static void ADC2_Enable(void)
{
    AD2CONbits.ON = 1U;
}

/**
 * @ingroup     adcdriver
 * @brief       This inline function returns true if ADC is ready
 * @pre         This function must be called after calling \ref ADC2_Enable to know ADC status
 * @param       none
 * @return      true - ADC is ready
 * @return      false - ADC is not ready 
 */
inline static bool ADC2_IsReady(void)
{
    return (bool)AD2CONbits.ADRDY;
}

/**
 * @ingroup  adcdriver
 * @brief    This inline function disables the ADC2 module
 * @pre      none
 * @param    none
 * @return   none  
 */
inline static void ADC2_Disable(void)
{
   AD2CONbits.ON = 0U;
}

/**
 * @ingroup     adcdriver
 * @brief       This inline function sets individual software trigger
 * @pre         none
 * @param[in]   channel - Channel for conversion      none
 * @return      none  
 */
inline static void ADC2_ChannelSoftwareTriggerEnable(const enum ADC_CHANNEL channel)
{
    switch(channel)
    {
        case MCAF_ADC_PHASEB_CURRENT:
                AD2SWTRGbits.CH0TRG = 0x1U;
                break;
        case MCAF_ADC_PHASEC_CURRENT:
                AD2SWTRGbits.CH1TRG = 0x1U;
                break;
        case MCAF_ADC_PHASEA_VOLTAGE:
                AD2SWTRGbits.CH2TRG = 0x1U;
                break;
        case MCAF_ADC_PHASEC_VOLTAGE:
                AD2SWTRGbits.CH3TRG = 0x1U;
                break;
        case MCAF_ADC_CORE2_UPPER_DIVIDER:
                AD2SWTRGbits.CH4TRG = 0x1U;
                break;
        default:
                break;
    }
}

/**
 * @ingroup    adcdriver
 * @brief      Returns the conversion value for the channel selected
 * @pre        This inline function returns the conversion value only after the conversion is complete. 
 *             Conversion completion status can be checked using 
 *             \ref ADC2_IsConversionComplete(channel) function.
 * @param[in]  channel - Selected channel  
 * @return     Returns the analog to digital converted value  
 */
inline static uint32_t ADC2_ConversionResultGet(const enum ADC_CHANNEL channel)
{
    uint32_t result = 0x0U;

    switch(channel)
    {
        case MCAF_ADC_PHASEB_CURRENT:
                result = AD2CH0DATA;
                break;
        case MCAF_ADC_PHASEC_CURRENT:
                result = AD2CH1DATA;
                break;
        case MCAF_ADC_PHASEA_VOLTAGE:
                result = AD2CH2DATA;
                break;
        case MCAF_ADC_PHASEC_VOLTAGE:
                result = AD2CH3DATA;
                break;
        case MCAF_ADC_CORE2_UPPER_DIVIDER:
                result = AD2CH4DATA;
                break;
        default:
                break;
    }
    return result;
}

/**
 * @ingroup    adcdriver
 * @brief      This inline function returns the status of conversion.This function is used to 
 *             determine if conversion is completed. When conversion is complete 
 *             the function returns true otherwise false.
 * @pre        \ref ADC2_SoftwareTriggerEnable() function should have been 
 *             called before calling this function.
 * @param[in]  channel - Selected channel  
 * @return     true - Conversion is complete.
 * @return     false - Conversion is not complete.  
 */
inline static bool ADC2_IsConversionComplete(const enum ADC_CHANNEL channel)
{
    bool status = false;

    switch(channel)
    {
        case MCAF_ADC_PHASEB_CURRENT:
                status = AD2STATbits.CH0RDY;
                break;
        case MCAF_ADC_PHASEC_CURRENT:
                status = AD2STATbits.CH1RDY;
                break;
        case MCAF_ADC_PHASEA_VOLTAGE:
                status = AD2STATbits.CH2RDY;
                break;
        case MCAF_ADC_PHASEC_VOLTAGE:
                status = AD2STATbits.CH3RDY;
                break;
        case MCAF_ADC_CORE2_UPPER_DIVIDER:
                status = AD2STATbits.CH4RDY;
                break;
        default:
                break;
    }

    return status;
}

/**
 * @ingroup    adcdriver
 * @brief      This inline function enables individual channel interrupt
 * @pre        none
 * @param[in]  channel - Selected channel  
 * @return     none  
 */
inline static void ADC2_IndividualChannelInterruptEnable(const enum ADC_CHANNEL channel)
{
    switch(channel)
    {
        case MCAF_ADC_PHASEB_CURRENT:
                IEC5bits.AD2CH0IE = 1U;
                break;
        case MCAF_ADC_PHASEC_CURRENT:
                IEC5bits.AD2CH1IE = 1U;
                break;
        case MCAF_ADC_PHASEA_VOLTAGE:
                IEC6bits.AD2CH2IE = 1U;
                break;
        case MCAF_ADC_PHASEC_VOLTAGE:
                IEC6bits.AD2CH3IE = 1U;
                break;
        case MCAF_ADC_CORE2_UPPER_DIVIDER:
                IEC6bits.AD2CH4IE = 1U;
                break;
        default:
                break;
    }
}

/**
 * @ingroup    adcdriver
 * @brief      This inline function disables individual channel interrupt
 * @pre        none
 * @param[in]  channel - Selected channel  
 * @return     none  
 */
inline static void ADC2_IndividualChannelInterruptDisable(const enum ADC_CHANNEL channel)
{
    switch(channel)
    {
        case MCAF_ADC_PHASEB_CURRENT:
                IEC5bits.AD2CH0IE = 0U;
                break;
        case MCAF_ADC_PHASEC_CURRENT:
                IEC5bits.AD2CH1IE = 0U;
                break;
        case MCAF_ADC_PHASEA_VOLTAGE:
                IEC6bits.AD2CH2IE = 0U;
                break;
        case MCAF_ADC_PHASEC_VOLTAGE:
                IEC6bits.AD2CH3IE = 0U;
                break;
        case MCAF_ADC_CORE2_UPPER_DIVIDER:
                IEC6bits.AD2CH4IE = 0U;
                break;
        default:
                break;
    }
}

/**
 * @ingroup    adcdriver
 * @brief      This inline function clears individual channel interrupt flag
 * @pre        The flag is not cleared without reading the data from buffer.
 *             Hence call \ref ADC2_ConversionResultGet() function to read data 
 *             before calling this function
 * @param[in]  channel - Selected channel  
 * @return     none  
 */
inline static void ADC2_IndividualChannelInterruptFlagClear(const enum ADC_CHANNEL channel)
{
    switch(channel)
    {
        case MCAF_ADC_PHASEB_CURRENT:
                IFS5bits.AD2CH0IF = 0U;
                break;
        case MCAF_ADC_PHASEC_CURRENT:
                IFS5bits.AD2CH1IF = 0U;
                break;
        case MCAF_ADC_PHASEA_VOLTAGE:
                IFS6bits.AD2CH2IF = 0U;
                break;
        case MCAF_ADC_PHASEC_VOLTAGE:
                IFS6bits.AD2CH3IF = 0U;
                break;
        case MCAF_ADC_CORE2_UPPER_DIVIDER:
                IFS6bits.AD2CH4IF = 0U;
                break;
        default:
                break;
    }
}

/**
 * @ingroup    adcdriver
 * @brief      This inline function allows selection of priority for individual channel interrupt
 * @pre        none
 * @param[in]  channel - Selected channel 
 * @param[in]  priorityValue  -  The numerical value of interrupt priority
 * @return     none  
 */
inline static void ADC2_IndividualChannelInterruptPrioritySet(const enum ADC_CHANNEL channel, enum INTERRUPT_PRIORITY priorityValue)
{
	switch(channel)
	{
		case MCAF_ADC_PHASEB_CURRENT:
				IPC23bits.AD2CH0IP = priorityValue;
				break;
		case MCAF_ADC_PHASEC_CURRENT:
				IPC23bits.AD2CH1IP = priorityValue;
				break;
		case MCAF_ADC_PHASEA_VOLTAGE:
				IPC24bits.AD2CH2IP = priorityValue;
				break;
		case MCAF_ADC_PHASEC_VOLTAGE:
				IPC24bits.AD2CH3IP = priorityValue;
				break;
		case MCAF_ADC_CORE2_UPPER_DIVIDER:
				IPC24bits.AD2CH4IP = priorityValue;
				break;
		default:
				break;
	}
}


/**
 * @ingroup  adcdriver
 * @brief    Sets PWM trigger source for corresponding analog input 
 * @param[in]  channel - Selected channel  
 * @param[in]  pwmInstance - PWM instance for the trigger source
 * @param[in]  triggerNumber - 1, for PWMx Trigger 1
 * @param[in]  triggerNumber - 2, for PWMx Trigger 2
 * @return   none  
 * @note     Configure PWM trigger value using \ref PWM_TriggerACompareValueSet, \ref PWM_TriggerBCompareValueSet
 *           or \ref PWM_TriggerCCompareValueSet before calling this funcion and enable corresponding 
 *           PWM trigger using \ref PWM_Trigger1Enable or \ref PWM_Trigger2Enable post calling it.
 */
void ADC2_PWMTriggerSourceSet(const enum ADC_CHANNEL channel, enum ADC_PWM_INSTANCE pwmInstance, enum ADC_PWM_TRIGGERS triggerNumber);


#ifdef __cplusplus
}
#endif

#endif //_ADC2_H
    
/**
 End of File
*/

