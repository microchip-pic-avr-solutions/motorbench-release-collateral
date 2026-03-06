/**
 * ADC Generated Driver Header File
 * 
 * @file      adc.h
 *            
 * @ingroup   adcdriver
 *            
 * @brief     This is the generated driver header file for the ADC driver          
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

#ifndef ADC_H
#define ADC_H
// Section: Included Files

#include "adc1.h"
#include "adc2.h"

/**
 * @ingroup  adcdriver
 * @brief    This macro defines the Custom Name for \ref ADC_Initialize API
 */
#define MCC_ADC_Initialize ADC_Initialize

/**
 * @ingroup  adcdriver
 * @brief    This macro defines the Custom Name for \ref ADC_Enable API
 */
#define MCC_ADC_Enable ADC_Enable

/**
 * @ingroup  adcdriver
 * @brief    This macro defines the Custom Name for \ref ADC_IsReady API
 */
#define MCC_ADC_IsReady ADC_IsReady

/**
 * @ingroup  adcdriver
 * @brief    This macro defines the Custom Name for \ref ADC_Disable API
 */
#define MCC_ADC_Disable ADC_Disable

/**
 * @ingroup  adcdriver
 * @brief    This macro defines the Custom Name for \ref ADC_IsConversionComplete API
 */
#define MCC_ADC_IsConversionComplete ADC_IsConversionComplete

/**
 * @ingroup  adcdriver
 * @brief    This macro defines the Custom Name for \ref ADC_ConversionResultGet API
 */
#define MCC_ADC_ConversionResultGet ADC_ConversionResultGet

/**
 * @ingroup  adcdriver
 * @brief    This macro defines the Custom Name for \ref ADC_ChannelSoftwareTriggerEnable API
 */
#define MCC_ADC_ChannelSoftwareTriggerEnable ADC_ChannelSoftwareTriggerEnable

/**
 * @ingroup  adcdriver
 * @brief    This macro defines the Custom Name for \ref ADC_IndividualChannelInterruptEnable API
 */
#define MCC_ADC_IndividualChannelInterruptEnable ADC_IndividualChannelInterruptEnable

/**
 * @ingroup  adcdriver
 * @brief    This macro defines the Custom Name for \ref ADC_IndividualChannelInterruptFlagClear API
 */
#define MCC_ADC_IndividualChannelInterruptFlagClear ADC_IndividualChannelInterruptFlagClear

/**
 * @ingroup  adcdriver
 * @brief    This macro defines the Custom Name for \ref ADC_IndividualChannelInterruptPrioritySet API
 */
#define MCC_ADC_IndividualChannelInterruptPrioritySet ADC_IndividualChannelInterruptPrioritySet

/**
 * @ingroup  adcdriver
 * @brief    This macro defines the Custom Name for \ref ADC_PWMTriggerSourceSet API
 */
#define MCC_ADC_PWMTriggerSourceSet ADC_PWMTriggerSourceSet

/**
 * @ingroup  adcdriver
 * @brief    Initializes all ADC cores, using the given initialization data
 * @param    none
 * @return   none  
 */
void ADC_Initialize(void);

/**
 * @ingroup  adcdriver
 * @brief    This inline function enables all the ADC cores
 * @pre      \ref ADC_IsReady must be called to know if all ADC cores are ready
 * @param    none
 * @return   none  
 */
inline static void ADC_Enable(void)
{
    ADC1_Enable();
    ADC2_Enable();
}

/**
 * @ingroup  adcdriver
 * @brief    This inline function returns true if all ADC cores are ready
 * @pre      This function must be called after calling \ref ADC_Enable to know ADC status
 * @param    none
 * @return   true - ADC is ready
 * @return   false - ADC is not ready 
 */
inline static bool ADC_IsReady(void)
{
    bool status;
    if(!ADC1_IsReady())
    {
        status = false;
    }
    if(!ADC2_IsReady())
    {
        status = false;
    }
    else
    {
        status = true;
    }
    return status;
}

/**
 * @ingroup  adcdriver
 * @brief    This inline function disables all the ADC cores
 * @pre      none
 * @param    none
 * @return   none  
 */
inline static void ADC_Disable(void)
{
    ADC1_Disable();
    ADC2_Disable();
}

/**
 * @ingroup    adcdriver
 * @brief      This inline function returns the status of conversion.This function is used to 
 *             determine if conversion is completed. When conversion is complete 
 *             the function returns true otherwise false.
 * @param[in]  channel - Selected channel  
 * @return     true - Conversion is complete.
 * @return     false - Conversion is not complete.  
 */
inline static uint32_t ADC_IsConversionComplete(const enum ADC_CHANNEL channelName)
{
    bool status;
    
    if(channelName <  ADC1_MAX_CHANNEL_VAL)
    {
        status  = ADC1_IsConversionComplete(channelName);
    }
    else if(channelName <  ADC2_MAX_CHANNEL_VAL)
    {
        status  = ADC2_IsConversionComplete(channelName);
    }
    else
    {
        status = false;
    }
 
    return status;
}

/**
 * @ingroup    adcdriver
 * @brief      Returns the conversion value for the channel selected
 * @pre        This inline function returns the conversion value only after the conversion is complete. 
 * @param[in]  channelName - Selected channel  
 * @return     Returns the analog to digital converted value  
 */
inline static uint32_t ADC_ConversionResultGet(const enum ADC_CHANNEL channelName)
{
    uint32_t result = 0;
    
    if(channelName <  ADC1_MAX_CHANNEL_VAL)
    {
        result  = ADC1_ConversionResultGet(channelName);
    }
    else if(channelName <  ADC2_MAX_CHANNEL_VAL)
    {
        result  = ADC2_ConversionResultGet(channelName);
    }
    else
    {
        result = 0;
    }
 
    return result;
}

/**
 * @ingroup     adcdriver
 * @brief       This inline function sets individual software trigger
 * @pre         none
 * @param[in]   channel - Channel for conversion      none
 * @return      none  
 */
inline static void ADC_ChannelSoftwareTriggerEnable(const enum ADC_CHANNEL channelName)
{
    if(channelName <  ADC1_MAX_CHANNEL_VAL)
    {
        ADC1_ChannelSoftwareTriggerEnable(channelName);
    }
    else if(channelName <  ADC2_MAX_CHANNEL_VAL)
    {
        ADC2_ChannelSoftwareTriggerEnable(channelName);
    }
    else
    {
        
    }
}

/**
 * @ingroup    adcdriver
 * @brief      This inline function enables individual channel interrupt
 * @pre        none
 * @param[in]  channelName - Selected channel  
 * @return     none  
 */
inline static void ADC_IndividualChannelInterruptEnable(const enum ADC_CHANNEL channelName)
{
    if(channelName <  ADC1_MAX_CHANNEL_VAL)
    {
        ADC1_IndividualChannelInterruptEnable(channelName);
    }
    else if(channelName <  ADC2_MAX_CHANNEL_VAL)
    {
        ADC2_IndividualChannelInterruptEnable(channelName);
    }
    else
    {
        
    }
}

/**
 * @ingroup    adcdriver
 * @brief      This inline function clears individual channel interrupt flag
 * @pre        The flag is not cleared without reading the data from buffer.
 *             Hence call \ref ADC_ConversionResultGet() function to read data 
 *             before calling this function
 * @param[in]  channelName - Selected channel  
 * @return     none  
 */
inline static void ADC_IndividualChannelInterruptFlagClear(const enum ADC_CHANNEL channelName)
{
    if(channelName <  ADC1_MAX_CHANNEL_VAL)
    {
        ADC1_IndividualChannelInterruptFlagClear(channelName);
    }
    else if(channelName <  ADC2_MAX_CHANNEL_VAL)
    {
        ADC2_IndividualChannelInterruptFlagClear(channelName);
    }
    else
    {
        
    }
}

/**
 * @ingroup    adcdriver
 * @brief      This inline function allows selection of priority for individual channel interrupt
 * @pre        none
 * @param[in]  channelName - Selected channel 
 * @param[in]  priorityValue  -  The numerical value of interrupt priority
 * @return     none  
 */
inline static void ADC_IndividualChannelInterruptPrioritySet(const enum ADC_CHANNEL channelName, enum INTERRUPT_PRIORITY priorityValue)
{
    if(channelName <  ADC1_MAX_CHANNEL_VAL)
    {
        ADC1_IndividualChannelInterruptPrioritySet(channelName,priorityValue);
    }
    else if(channelName <  ADC2_MAX_CHANNEL_VAL)
    {
        ADC2_IndividualChannelInterruptPrioritySet(channelName,priorityValue);
    }
    else
    {
        
    }
}

/**
 * @ingroup  adcdriver
 * @brief    Sets PWM trigger source for corresponding analog input 
 * @param[in]  channelName - Selected channel  
 * @param[in]  pwmInstance - PWM instance for the trigger source
 * @param[in]  triggerNumber - 1, for PWMx Trigger 1
 * @param[in]  triggerNumber - 2, for PWMx Trigger 2
 * @return   none  
 * @note     Configure PWM trigger value using \ref PWM_TriggerACompareValueSet, \ref PWM_TriggerBCompareValueSet
 *           or \ref PWM_TriggerCCompareValueSet before calling this funcion and enable corresponding 
 *           PWM trigger using \ref PWM_Trigger1Enable or \ref PWM_Trigger2Enable post calling it.
 */
inline static void ADC_PWMTriggerSourceSet(const enum ADC_CHANNEL channelName, const enum ADC_PWM_INSTANCE pwmInstance, const  enum ADC_PWM_TRIGGERS triggerNumber)
{
    if(channelName <  ADC1_MAX_CHANNEL_VAL)
    {
        ADC1_PWMTriggerSourceSet(channelName,pwmInstance,triggerNumber);
    }
    else if(channelName <  ADC2_MAX_CHANNEL_VAL)
    {
        ADC2_PWMTriggerSourceSet(channelName,pwmInstance,triggerNumber);
    }
    else
    {
        
    }
}

/**
 * @ingroup    adcdriver
 * @brief      This inline function returns the core to which specified channel belong to
 * @pre        none
 * @param[in]  channelName - Selected channel 
 * @return     \ref ADC_CORE number of which specified channel belong to
 */
inline static enum ADC_CORE ADC_CoreGet(const enum ADC_CHANNEL channelName)
{
    enum ADC_CORE core = ADC_INVAID_CORE;
    if(channelName <  ADC1_MAX_CHANNEL_VAL)
    {
        core = ADC_CORE_1;
    }
    else if(channelName <  ADC2_MAX_CHANNEL_VAL)
    {
        core = ADC_CORE_2;
    }
    else
    {
        
    }
    return core;
}

#endif // ADC_H
    
/**
 End of File
*/
