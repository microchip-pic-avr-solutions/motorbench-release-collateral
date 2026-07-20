/**
 * ADC2 Generated Driver Source File
 * 
 * @file      adc2.c
 *            
 * @ingroup   adcdriver
 *            
 * @brief     This is the generated driver source file for ADC2 driver        
 *
 * @skipline @version   PLIB Version 1.2.1
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
#include <stddef.h>
#include "../adc2.h"

// Section: File specific functions

// Section: File specific data type definitions

/**
 @ingroup  adcdriver
 @enum     ADC2_PWM_TRIG_SRCS
 @brief    Defines the PWM ADC TRIGGER sources available for the module to use.
*/
enum ADC2_PWM_TRIG_SRCS {
    PWM4_TRIGGER2 = 0xb, 
    PWM4_TRIGGER1 = 0xa, 
    PWM3_TRIGGER2 = 0x9, 
    PWM3_TRIGGER1 = 0x8, 
    PWM2_TRIGGER2 = 0x7, 
    PWM2_TRIGGER1 = 0x6, 
    PWM1_TRIGGER2 = 0x5, 
    PWM1_TRIGGER1 = 0x4, 
};

// Section: Driver Interface Function Definitions

void ADC2_Initialize(void)
{
    //CALCNT Wait for 2 activity free ADC clock cycles; BUFEN disabled; TSTEN disabled; SIDL disabled; ON enabled; STNDBY disabled; VREFMOD enabled; RPTCNT 1 ADC clock cycles between triggers; CALRATE Every second; ACALEN disabled; CALREQ Calibration cycle is not requested; 
    AD2CON = (uint32_t)0x28000UL & ~_AD1CON_ON_MASK;
    //DATAOVR 0x0; 
    AD2DATAOVR = 0x0UL;
    //CH0RDY disabled; CH1RDY disabled; CH2RDY disabled; CH3RDY disabled; CH4RDY disabled; CH5RDY disabled; CH6RDY disabled; CH7RDY disabled; CH8RDY disabled; CH9RDY disabled; CH10RDY disabled; CH11RDY disabled; CH12RDY disabled; CH13RDY disabled; CH14RDY disabled; CH15RDY disabled; CH16RDY disabled; CH17RDY disabled; CH18RDY disabled; CH19RDY disabled; 
    AD2STAT = 0x0UL;
    //CH0CMP disabled; CH1CMP disabled; CH2CMP disabled; CH3CMP disabled; CH4CMP disabled; CH5CMP disabled; CH6CMP disabled; CH7CMP disabled; CH8CMP disabled; CH9CMP disabled; CH10CMP disabled; CH11CMP disabled; CH12CMP disabled; CH13CMP disabled; CH14CMP disabled; CH15CMP disabled; CH16CMP disabled; CH17CMP disabled; CH18CMP disabled; CH19CMP disabled; 
    AD2CMPSTAT = 0x0UL;
    //CH0TRG disabled; CH1TRG disabled; CH2TRG disabled; CH3TRG disabled; CH4TRG disabled; CH5TRG disabled; CH6TRG disabled; CH7TRG disabled; CH8TRG disabled; CH9TRG disabled; CH10TRG disabled; CH11TRG disabled; CH12TRG disabled; CH13TRG disabled; CH14TRG disabled; CH15TRG disabled; CH16TRG disabled; CH17TRG disabled; CH18TRG disabled; CH19TRG disabled; 
    AD2SWTRG = 0x0UL;
    //TRG1SRC PWM1 Trigger1; SAMC 14.5 TAD; NINSEL AD2ANN0; LEFT Fractional; PINSEL AD2AN1; DIFF disabled; CMPMOD NONE; TRG2SRC disabled; EIEN disabled; TRG1POL disabled; ACCRO disabled; ACCBRST disabled; ACCNUM 4 samples, 13 bits result; MODE Single sample initiated by TRG1SRC[4:0] trigger; 
    AD2CH0CON = 0xCE4UL;
    //TRG1SRC PWM1 Trigger1; SAMC 14.5 TAD; NINSEL AD2ANN0; LEFT Fractional; PINSEL AD2AN9; DIFF disabled; CMPMOD NONE; TRG2SRC disabled; EIEN disabled; TRG1POL disabled; ACCRO disabled; ACCBRST disabled; ACCNUM 4 samples, 13 bits result; MODE Single sample initiated by TRG1SRC[4:0] trigger; 
    AD2CH1CON = 0x4CE4UL;
    //TRG1SRC PWM1 Trigger1; SAMC 14.5 TAD; NINSEL AD2ANN0; LEFT Fractional; PINSEL AD2AN10; DIFF disabled; CMPMOD NONE; TRG2SRC disabled; EIEN disabled; TRG1POL disabled; ACCRO disabled; ACCBRST disabled; ACCNUM 4 samples, 13 bits result; MODE Single sample initiated by TRG1SRC[4:0] trigger; 
    AD2CH2CON = 0x54E4UL;
    //TRG1SRC PWM1 Trigger1; SAMC 14.5 TAD; NINSEL AD2ANN0; LEFT Fractional; PINSEL AD2AN7; DIFF disabled; CMPMOD NONE; TRG2SRC disabled; EIEN disabled; TRG1POL disabled; ACCRO disabled; ACCBRST disabled; ACCNUM 4 samples, 13 bits result; MODE Single sample initiated by TRG1SRC[4:0] trigger; 
    AD2CH3CON = 0x3CE4UL;
    //TRG1SRC PWM1 Trigger1; SAMC 14.5 TAD; NINSEL AD2ANN0; LEFT Fractional; PINSEL AD2AN14; DIFF disabled; CMPMOD NONE; TRG2SRC disabled; EIEN disabled; TRG1POL disabled; ACCRO disabled; ACCBRST disabled; ACCNUM 4 samples, 13 bits result; MODE Single sample initiated by TRG1SRC[4:0] trigger; 
    AD2CH4CON = 0x74E4UL;
    //CNT 0x0; 
    AD2CH0CNT = 0x0UL;
    //CNT 0x0; 
    AD2CH1CNT = 0x0UL;
    //CNT 0x0; 
    AD2CH2CNT = 0x0UL;
    //CNT 0x0; 
    AD2CH3CNT = 0x0UL;
    //CNT 0x0; 
    AD2CH4CNT = 0x0UL;
    //CMPLO 0x0; 
    AD2CH0CMPLO = 0x0UL;
    //CMPLO 0x0; 
    AD2CH1CMPLO = 0x0UL;
    //CMPLO 0x0; 
    AD2CH2CMPLO = 0x0UL;
    //CMPLO 0x0; 
    AD2CH3CMPLO = 0x0UL;
    //CMPLO 0x0; 
    AD2CH4CMPLO = 0x0UL;
    //CMPHI 0x0; 
    AD2CH0CMPHI = 0x0UL;
    //CMPHI 0x0; 
    AD2CH1CMPHI = 0x0UL;
    //CMPHI 0x0; 
    AD2CH2CMPHI = 0x0UL;
    //CMPHI 0x0; 
    AD2CH3CMPHI = 0x0UL;
    //CMPHI 0x0; 
    AD2CH4CMPHI = 0x0UL;
    
    
    // ADC Mode change to run mode
    AD2CONbits.ON = 1U;   
    while(AD2CONbits.ADRDY == 0U)
    {
    }
}

static uint16_t ADC2_TriggerSourceValueGet(enum ADC_PWM_INSTANCE pwmInstance, enum ADC_PWM_TRIGGERS triggerNumber)
{
    uint16_t adcTriggerSourceValue = 0x0U;
    switch(pwmInstance)
    {
        case ADC_PWM_GENERATOR_4:
                if(triggerNumber == ADC_PWM_TRIGGER_1)
                {
                    adcTriggerSourceValue = PWM4_TRIGGER1;
                }
                else if(triggerNumber == ADC_PWM_TRIGGER_2)
                {
                    adcTriggerSourceValue = PWM4_TRIGGER2;
                }
                else
                {
                }
                break;
        case ADC_PWM_GENERATOR_3:
                if(triggerNumber == ADC_PWM_TRIGGER_1)
                {
                    adcTriggerSourceValue = PWM3_TRIGGER1;
                }
                else if(triggerNumber == ADC_PWM_TRIGGER_2)
                {
                    adcTriggerSourceValue = PWM3_TRIGGER2;
                }
                else
                {
                }
                break;
        case ADC_PWM_GENERATOR_2:
                if(triggerNumber == ADC_PWM_TRIGGER_1)
                {
                    adcTriggerSourceValue = PWM2_TRIGGER1;
                }
                else if(triggerNumber == ADC_PWM_TRIGGER_2)
                {
                    adcTriggerSourceValue = PWM2_TRIGGER2;
                }
                else
                {
                }
                break;
        case ADC_PWM_GENERATOR_1:
                if(triggerNumber == ADC_PWM_TRIGGER_1)
                {
                    adcTriggerSourceValue = PWM1_TRIGGER1;
                }
                else if(triggerNumber == ADC_PWM_TRIGGER_2)
                {
                    adcTriggerSourceValue = PWM1_TRIGGER2;
                }
                else
                {
                }
                break;
         default:
                break;
    }
    return adcTriggerSourceValue;
}

void ADC2_PWMTriggerSourceSet(enum ADC_CHANNEL channel, enum ADC_PWM_INSTANCE pwmInstance, enum ADC_PWM_TRIGGERS triggerNumber)
{
    uint16_t adcTriggerValue;
    adcTriggerValue= ADC2_TriggerSourceValueGet(pwmInstance, triggerNumber);
    switch(channel)
    {
        case MCAF_ADC_PHASEB_CURRENT:
                AD2CH0CONbits.TRG1SRC = adcTriggerValue;
                break;
        case MCAF_ADC_PHASEC_CURRENT:
                AD2CH1CONbits.TRG1SRC = adcTriggerValue;
                break;
        case MCAF_ADC_PHASEA_VOLTAGE:
                AD2CH2CONbits.TRG1SRC = adcTriggerValue;
                break;
        case MCAF_ADC_PHASEC_VOLTAGE:
                AD2CH3CONbits.TRG1SRC = adcTriggerValue;
                break;
        case MCAF_ADC_CORE2_UPPER_DIVIDER:
                AD2CH4CONbits.TRG1SRC = adcTriggerValue;
                break;
        default:
                break;
    }
}


/* cppcheck-suppress misra-c2012-8.4
*
* (Rule 8.4) REQUIRED: A compatible declaration shall be visible when an object or 
* function with external linkage is defined
*
* Reasoning: Interrupt declaration are provided by compiler and are available
* outside the driver folder
*/
void __attribute__ ( ( __interrupt__, weak ) ) _AD2CH0Interrupt ( void )
{
    (void)AD2CH0DATA;

    //clear the MCAF_ADC_PHASEB_CURRENT interrupt flag
    IFS5bits.AD2CH0IF = 0U;
}

/* cppcheck-suppress misra-c2012-8.4
*
* (Rule 8.4) REQUIRED: A compatible declaration shall be visible when an object or 
* function with external linkage is defined
*
* Reasoning: Interrupt declaration are provided by compiler and are available
* outside the driver folder
*/
void __attribute__ ( ( __interrupt__, weak ) ) _AD2CH1Interrupt ( void )
{
    (void)AD2CH1DATA;

    //clear the MCAF_ADC_PHASEC_CURRENT interrupt flag
    IFS5bits.AD2CH1IF = 0U;
}

/* cppcheck-suppress misra-c2012-8.4
*
* (Rule 8.4) REQUIRED: A compatible declaration shall be visible when an object or 
* function with external linkage is defined
*
* Reasoning: Interrupt declaration are provided by compiler and are available
* outside the driver folder
*/
void __attribute__ ( ( __interrupt__, weak ) ) _AD2CH2Interrupt ( void )
{
    (void)AD2CH2DATA;

    //clear the MCAF_ADC_PHASEA_VOLTAGE interrupt flag
    IFS6bits.AD2CH2IF = 0U;
}

/* cppcheck-suppress misra-c2012-8.4
*
* (Rule 8.4) REQUIRED: A compatible declaration shall be visible when an object or 
* function with external linkage is defined
*
* Reasoning: Interrupt declaration are provided by compiler and are available
* outside the driver folder
*/
void __attribute__ ( ( __interrupt__, weak ) ) _AD2CH3Interrupt ( void )
{
    (void)AD2CH3DATA;

    //clear the MCAF_ADC_PHASEC_VOLTAGE interrupt flag
    IFS6bits.AD2CH3IF = 0U;
}

/* cppcheck-suppress misra-c2012-8.4
*
* (Rule 8.4) REQUIRED: A compatible declaration shall be visible when an object or 
* function with external linkage is defined
*
* Reasoning: Interrupt declaration are provided by compiler and are available
* outside the driver folder
*/
void __attribute__ ( ( __interrupt__, weak ) ) _AD2CH4Interrupt ( void )
{
    (void)AD2CH4DATA;

    //clear the MCAF_ADC_CORE2_UPPER_DIVIDER interrupt flag
    IFS6bits.AD2CH4IF = 0U;
}

