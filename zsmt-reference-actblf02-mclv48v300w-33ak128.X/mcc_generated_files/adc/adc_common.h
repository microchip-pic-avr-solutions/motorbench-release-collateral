/**
 * ADC Generated Driver Common Header File
 * 
 * @file      adc_common.h
 *            
 * @ingroup   adcdriver
 *            
 * @brief     This is the generated driver common header file for the ADC driver           
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

#ifndef ADC_COMMON_H
#define ADC_COMMON_H

// Section: Included Files

// Section: Data Type Definitions

/**
 @ingroup  adcdriver
 @enum     ADC_CHANNEL
 @brief    Defines the ADC channles that are selected from the MCC Melody 
           User Interface for the ADC conversions.
 @note     The enum list in the Help document might be just a reference to show 
           the analog channel list. Generated enum list is based on the configuration 
           done by user in the MCC Melody user interface.
*/
enum ADC_CHANNEL
{  
    MCAF_ADC_PHASEA_CURRENT  = 0,
    MCAF_ADC_DCLINK_CURRENT  = 1,
    MCAF_ADC_DCLINK_VOLTAGE  = 2,
    MCAF_ADC_POTENTIOMETER  = 3,
    MCAF_ADC_PHASEB_VOLTAGE  = 4,
    MCAF_ADC_BRIDGE_TEMPERATURE  = 5,
    MCAF_ADC_CORE1_UPPER_DIVIDER  = 6,
    ADC1_MAX_CHANNEL_VAL = 7,
    MCAF_ADC_PHASEB_CURRENT  = 8,
    MCAF_ADC_PHASEC_CURRENT  = 9,
    MCAF_ADC_PHASEA_VOLTAGE  = 10,
    MCAF_ADC_PHASEC_VOLTAGE  = 11,
    MCAF_ADC_CORE2_UPPER_DIVIDER  = 12,
    ADC2_MAX_CHANNEL_VAL = 13,
};

/**
 @ingroup  adcdriver
 @enum     ADC_CORE
 @brief    Defines the ADC cores that are 
           available for the module to use.
 @note     The enum list in the Help document might be just a reference to to show 
           the dedicated core list. Generated enum list is based on the configuration 
           done by user in the MCC Melody user interface.
*/
enum ADC_CORE
{
    ADC_CORE_1 = 1,
    ADC_CORE_2 = 2,
    ADC_ENABLED_CORES = 2,
    ADC_MAX_AVAILABLE_CORES = 2,    /**< Max Cores present in device */
    ADC_INVAID_CORE = 0xFFFFFFFFU
    
};

#ifndef ADC_COMMON_TYPES // common types for adc common driver and single core adc plib

#define ADC_COMMON_TYPES

/**
 @ingroup  adcdriver
 @enum     ADC_RESOLUTION_TYPE
 @brief    Defines the supported ADC resolution types.
*/
enum ADC_RESOLUTION_TYPE
{
    ADC_12_BIT_RESOLUTION,     /**< ADC Resolution of 12 bit*/
};

/**
 @ingroup  adcdriver
 @enum     ADC_PWM_INSTANCE
 @brief    Defines the ADC PWM trigger sources that are 
           available for the module to use.
 @note     Refer \ref PWM_GENERATOR enum for mapping between custom name and instance 
*/
enum ADC_PWM_INSTANCE
{
    ADC_PWM_GENERATOR_1,    /**< PWM name:PWM_GENERATOR_1 */
    ADC_PWM_GENERATOR_2,    /**< PWM name:PWM_GENERATOR_2 */
    ADC_PWM_GENERATOR_3,    /**< PWM name:PWM_GENERATOR_3 */
    ADC_PWM_GENERATOR_4,    /**< PWM name:PWM_GENERATOR_4 */
};

/**
 @ingroup  adcdriver
 @enum     ADC_PWM_TRIGGERS
 @brief    Defines the PWM triggers that are available in each individual PWM.
*/
enum ADC_PWM_TRIGGERS
{
    ADC_PWM_TRIGGER_1 = 1,     /**< PWM TRIGGER 1 */
    ADC_PWM_TRIGGER_2 = 2,     /**< PWM TRIGGER 2 */
};

#endif //ADC_COMMON_TYPES
        
/*******************************************************************************
            Macros defined for features supported in ADC Common Driver
*******************************************************************************/

/** 
 @ingroup  adcdriver
 @brief    Defines the macro associated with ADC indvidual channel interrupts

  <b>APIs Supported:</b><br>
   void ADC_IndividualChannelInterruptEnable (enum ADC_CHANNEL channel);<br>
   void ADC_IndividualChannelInterruptDisable (enum ADC_CHANNEL channel);<br>
   void ADC_IndividualChannelInterruptFlagClear (enum ADC_CHANNEL channel);<br>
   
   x denotes instance of ADC, channel denotes dedicated ADC channel. 
   Refer to device specific datasheet to check number of cores and ADC module instance.
   Refer driver header file for detailed description of the APIs.
  
*/
#define ADC_COMMON_INDIVIDUAL_CHANNEL_INTERRUPT_FEATURE_AVAILABLE  1

/** 
 @ingroup  adcdriver
 @brief    Defines the macro associated with individual channel software trigger feature

  <b>APIs Supported:</b><br>
   void ADC_ChannelSoftwareTriggerEnable(enum ADC_CHANNEL channel);<br>

   x denotes instance of ADC in ADCx.
   Refer to device specific datasheet to check number of comparators and ADC module instance.
   Refer driver header file for detailed description of the APIs.
  
*/
#define ADC_COMMON_INDIVIDUAL_SOFTWARE_TRIGGER_FEATURE_AVAILABLE   1

#endif  //ADC_COMMON_H
