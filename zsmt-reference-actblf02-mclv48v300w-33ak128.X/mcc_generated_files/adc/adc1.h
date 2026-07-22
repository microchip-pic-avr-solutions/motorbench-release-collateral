/**
 * ADC1 Generated Driver Header File
 * 
 * @file      adc1.h
 *            
 * @ingroup   adcdriver
 *            
 * @brief     This is the generated driver header file for the ADC1 driver          
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

#ifndef ADC1_H
#define ADC1_H


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
#define ADC1_RESOLUTION 12

// Section: Driver Interface Functions

/**
 * @ingroup  adcdriver
 * @brief    Initializes ADC1 module, using the given initialization data
 *           This function must be called before any other ADC1 function is called
 * @param    none
 * @return   none  
 */
void ADC1_Initialize (void);

/**
 * @ingroup  adcdriver
 * @brief    This inline function enables the ADC1 module
 * @pre      \ref ADC1_IsReady must be called to know the status of ADC
 * @param    none
 * @return   none  
 */
inline static void ADC1_Enable(void)
{
    AD1CONbits.ON = 1U;
}

/**
 * @ingroup     adcdriver
 * @brief       This inline function returns true if ADC is ready
 * @pre         This function must be called after calling \ref ADC1_Enable to know ADC status
 * @param       none
 * @return      true - ADC is ready
 * @return      false - ADC is not ready 
 */
inline static bool ADC1_IsReady(void)
{
    return (bool)AD1CONbits.ADRDY;
}

/**
 * @ingroup  adcdriver
 * @brief    This inline function disables the ADC1 module
 * @pre      none
 * @param    none
 * @return   none  
 */
inline static void ADC1_Disable(void)
{
   AD1CONbits.ON = 0U;
}

/**
 * @ingroup     adcdriver
 * @brief       This inline function sets individual software trigger
 * @pre         none
 * @param[in]   channel - Channel for conversion      none
 * @return      none  
 */
inline static void ADC1_ChannelSoftwareTriggerEnable(const enum ADC_CHANNEL channel)
{
    switch(channel)
    {
        case MCAF_ADC_PHASEA_CURRENT:
                AD1SWTRGbits.CH0TRG = 0x1U;
                break;
        case MCAF_ADC_DCLINK_CURRENT:
                AD1SWTRGbits.CH1TRG = 0x1U;
                break;
        case MCAF_ADC_DCLINK_VOLTAGE:
                AD1SWTRGbits.CH2TRG = 0x1U;
                break;
        case MCAF_ADC_POTENTIOMETER:
                AD1SWTRGbits.CH3TRG = 0x1U;
                break;
        case MCAF_ADC_PHASEB_VOLTAGE:
                AD1SWTRGbits.CH4TRG = 0x1U;
                break;
        case MCAF_ADC_BRIDGE_TEMPERATURE:
                AD1SWTRGbits.CH5TRG = 0x1U;
                break;
        case MCAF_ADC_CORE1_UPPER_DIVIDER:
                AD1SWTRGbits.CH6TRG = 0x1U;
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
 *             \ref ADC1_IsConversionComplete(channel) function.
 * @param[in]  channel - Selected channel  
 * @return     Returns the analog to digital converted value  
 */
inline static uint32_t ADC1_ConversionResultGet(const enum ADC_CHANNEL channel)
{
    uint32_t result = 0x0U;

    switch(channel)
    {
        case MCAF_ADC_PHASEA_CURRENT:
                result = AD1CH0DATA;
                break;
        case MCAF_ADC_DCLINK_CURRENT:
                result = AD1CH1DATA;
                break;
        case MCAF_ADC_DCLINK_VOLTAGE:
                result = AD1CH2DATA;
                break;
        case MCAF_ADC_POTENTIOMETER:
                result = AD1CH3DATA;
                break;
        case MCAF_ADC_PHASEB_VOLTAGE:
                result = AD1CH4DATA;
                break;
        case MCAF_ADC_BRIDGE_TEMPERATURE:
                result = AD1CH5DATA;
                break;
        case MCAF_ADC_CORE1_UPPER_DIVIDER:
                result = AD1CH6DATA;
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
 * @pre        \ref ADC1_SoftwareTriggerEnable() function should have been 
 *             called before calling this function.
 * @param[in]  channel - Selected channel  
 * @return     true - Conversion is complete.
 * @return     false - Conversion is not complete.  
 */
inline static bool ADC1_IsConversionComplete(const enum ADC_CHANNEL channel)
{
    bool status = false;

    switch(channel)
    {
        case MCAF_ADC_PHASEA_CURRENT:
                status = AD1STATbits.CH0RDY;
                break;
        case MCAF_ADC_DCLINK_CURRENT:
                status = AD1STATbits.CH1RDY;
                break;
        case MCAF_ADC_DCLINK_VOLTAGE:
                status = AD1STATbits.CH2RDY;
                break;
        case MCAF_ADC_POTENTIOMETER:
                status = AD1STATbits.CH3RDY;
                break;
        case MCAF_ADC_PHASEB_VOLTAGE:
                status = AD1STATbits.CH4RDY;
                break;
        case MCAF_ADC_BRIDGE_TEMPERATURE:
                status = AD1STATbits.CH5RDY;
                break;
        case MCAF_ADC_CORE1_UPPER_DIVIDER:
                status = AD1STATbits.CH6RDY;
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
inline static void ADC1_IndividualChannelInterruptEnable(const enum ADC_CHANNEL channel)
{
    switch(channel)
    {
        case MCAF_ADC_PHASEA_CURRENT:
                IEC4bits.AD1CH0IE = 1U;
                break;
        case MCAF_ADC_DCLINK_CURRENT:
                IEC4bits.AD1CH1IE = 1U;
                break;
        case MCAF_ADC_DCLINK_VOLTAGE:
                IEC4bits.AD1CH2IE = 1U;
                break;
        case MCAF_ADC_POTENTIOMETER:
                IEC4bits.AD1CH3IE = 1U;
                break;
        case MCAF_ADC_PHASEB_VOLTAGE:
                IEC4bits.AD1CH4IE = 1U;
                break;
        case MCAF_ADC_BRIDGE_TEMPERATURE:
                IEC4bits.AD1CH5IE = 1U;
                break;
        case MCAF_ADC_CORE1_UPPER_DIVIDER:
                IEC4bits.AD1CH6IE = 1U;
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
inline static void ADC1_IndividualChannelInterruptDisable(const enum ADC_CHANNEL channel)
{
    switch(channel)
    {
        case MCAF_ADC_PHASEA_CURRENT:
                IEC4bits.AD1CH0IE = 0U;
                break;
        case MCAF_ADC_DCLINK_CURRENT:
                IEC4bits.AD1CH1IE = 0U;
                break;
        case MCAF_ADC_DCLINK_VOLTAGE:
                IEC4bits.AD1CH2IE = 0U;
                break;
        case MCAF_ADC_POTENTIOMETER:
                IEC4bits.AD1CH3IE = 0U;
                break;
        case MCAF_ADC_PHASEB_VOLTAGE:
                IEC4bits.AD1CH4IE = 0U;
                break;
        case MCAF_ADC_BRIDGE_TEMPERATURE:
                IEC4bits.AD1CH5IE = 0U;
                break;
        case MCAF_ADC_CORE1_UPPER_DIVIDER:
                IEC4bits.AD1CH6IE = 0U;
                break;
        default:
                break;
    }
}

/**
 * @ingroup    adcdriver
 * @brief      This inline function clears individual channel interrupt flag
 * @pre        The flag is not cleared without reading the data from buffer.
 *             Hence call \ref ADC1_ConversionResultGet() function to read data 
 *             before calling this function
 * @param[in]  channel - Selected channel  
 * @return     none  
 */
inline static void ADC1_IndividualChannelInterruptFlagClear(const enum ADC_CHANNEL channel)
{
    switch(channel)
    {
        case MCAF_ADC_PHASEA_CURRENT:
                IFS4bits.AD1CH0IF = 0U;
                break;
        case MCAF_ADC_DCLINK_CURRENT:
                IFS4bits.AD1CH1IF = 0U;
                break;
        case MCAF_ADC_DCLINK_VOLTAGE:
                IFS4bits.AD1CH2IF = 0U;
                break;
        case MCAF_ADC_POTENTIOMETER:
                IFS4bits.AD1CH3IF = 0U;
                break;
        case MCAF_ADC_PHASEB_VOLTAGE:
                IFS4bits.AD1CH4IF = 0U;
                break;
        case MCAF_ADC_BRIDGE_TEMPERATURE:
                IFS4bits.AD1CH5IF = 0U;
                break;
        case MCAF_ADC_CORE1_UPPER_DIVIDER:
                IFS4bits.AD1CH6IF = 0U;
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
inline static void ADC1_IndividualChannelInterruptPrioritySet(const enum ADC_CHANNEL channel, enum INTERRUPT_PRIORITY priorityValue)
{
	switch(channel)
	{
		case MCAF_ADC_PHASEA_CURRENT:
				IPC18bits.AD1CH0IP = priorityValue;
				break;
		case MCAF_ADC_DCLINK_CURRENT:
				IPC18bits.AD1CH1IP = priorityValue;
				break;
		case MCAF_ADC_DCLINK_VOLTAGE:
				IPC18bits.AD1CH2IP = priorityValue;
				break;
		case MCAF_ADC_POTENTIOMETER:
				IPC19bits.AD1CH3IP = priorityValue;
				break;
		case MCAF_ADC_PHASEB_VOLTAGE:
				IPC19bits.AD1CH4IP = priorityValue;
				break;
		case MCAF_ADC_BRIDGE_TEMPERATURE:
				IPC19bits.AD1CH5IP = priorityValue;
				break;
		case MCAF_ADC_CORE1_UPPER_DIVIDER:
				IPC19bits.AD1CH6IP = priorityValue;
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
void ADC1_PWMTriggerSourceSet(const enum ADC_CHANNEL channel, enum ADC_PWM_INSTANCE pwmInstance, enum ADC_PWM_TRIGGERS triggerNumber);


#ifdef __cplusplus
}
#endif

#endif //_ADC1_H
    
/**
 End of File
*/

