/**
 * SCCP1-TIMER Generated Driver Source File
 * 
 * @file      sccp1.c
 * 
 * @ingroup   timerdriver
 * 
 * @brief     This is the generated driver source file for SCCP1-TIMER driver
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

// Section: Included Files

#include <stddef.h> 
#include "../sccp1.h"
#include "../timer_interface.h"

// Section: File specific functions

static void (*SCCP1_TimeoutHandler)(void) = NULL;

// Section: Driver Interface

// Defines an object for TIMER_INTERFACE

const struct TIMER_INTERFACE MCC_TMR_PROFILE = {
    .Initialize     = &SCCP1_Timer_Initialize,
    .Deinitialize   = &SCCP1_Timer_Deinitialize,
    .Start          = &SCCP1_Timer_Start,
    .Stop           = &SCCP1_Timer_Stop,
    .PeriodSet      = &SCCP1_Timer_PeriodSet,
    .PeriodGet	    = &SCCP1_Timer_PeriodGet,
    .CounterGet     = &SCCP1_Timer_CounterGet,
    .InterruptPrioritySet = &SCCP1_Timer_InterruptPrioritySet,
    .TimeoutCallbackRegister = &SCCP1_Timer_TimeoutCallbackRegister,
    .Tasks          = &SCCP1_Timer_Tasks,
};

// Section: Driver Interface Function Definitions

void SCCP1_Timer_Initialize(void)
{
    //MOD 16-Bit/32-Bit Timer; CCSEL disabled; T32 16 Bit; TMRPS 1:1; CLKSEL Standard Speed Peripheral Clock; TMRSYNC disabled; SIDL disabled; ON disabled; SYNC None; ALTSYNC disabled; ONESHOT disabled; TRIGEN disabled; OPS Each Time Base Period Match; RTRGEN disabled; OPSSRC Timer Interrupt Event; 
    CCP1CON1 = 0x0UL;
    //ASDG disabled; SSDG disabled; ASDGM disabled; PWMRSEN disabled; ICS ; AUXOUT Disabled; ICGSM Level-Sensitive mode; OCAEN disabled; OENSYNC disabled; 
    CCP1CON2 = 0x0UL;
    //PSSACE Tri-state; POLACE disabled; OSCNT None; OETRIG disabled; 
    CCP1CON3 = 0x0UL;
    //ICOV disabled; SCEVT disabled; ASEVT disabled; TRCLR disabled; TRSET disabled; ICGARM disabled; RAWIP disabled; RBWIP disabled; TMRLWIP disabled; TMRHWIP disabled; PRLWIP disabled; 
    CCP1STAT = 0x0UL;
    //TMRL 0x0; TMRH 0x0; 
    CCP1TMR = 0x0UL;
    //PRL 65535; PRH 0; 
    CCP1PR = 0xFFFFUL;
    //BUFL 0x0; BUFH 0x0; 
    CCP1BUF = 0x0UL;
    //CMPA 0x0; 
    CCP1RA = 0x0UL;
    //CMPB 0x0; 
    CCP1RB = 0x0UL;
    
    SCCP1_Timer_TimeoutCallbackRegister(&SCCP1_TimeoutCallback);


    CCP1CON1bits.ON = 1; //Enable Module
}

void SCCP1_Timer_Deinitialize(void)
{
    CCP1CON1bits.ON = 0;
    
    CCP1CON1 = 0x0UL; 
    CCP1CON2 = 0x1000000UL; 
    CCP1CON3 = 0x0UL; 
    CCP1STAT = 0x0UL; 
    CCP1TMR = 0x0UL; 
    CCP1PR = 0xFFFFFFFFUL; 
    CCP1BUF = 0x0UL; 
    CCP1RA = 0x0UL; 
    CCP1RB = 0x0UL; 
}

void SCCP1_Timer_Start(void)
{
    CCP1CON1bits.ON = 1;
}

void SCCP1_Timer_Stop(void)
{
    CCP1CON1bits.ON = 0;
}

void SCCP1_Timer_PeriodSet(uint32_t count)
{
    if(count > 0xFFFFU)
    {
        CCP1PR = count;
        CCP1CON1bits.T32 = 1;
    }
    else
    {
        CCP1PR = count;
        CCP1CON1bits.T32 = 0;
    }
}

void SCCP1_Timer_InterruptPrioritySet(enum INTERRUPT_PRIORITY priority)
{
    IPC6bits.CCT1IP = priority;
}

void SCCP1_Timer_TimeoutCallbackRegister(void (*handler)(void))
{
    if(NULL != handler)
    {
        SCCP1_TimeoutHandler = handler;
    }
}

void __attribute__ ((weak)) SCCP1_TimeoutCallback (void)
{ 

} 

void SCCP1_Timer_Tasks(void)
{
    if(IFS1bits.CCT1IF == 1)
    {
        if(NULL != SCCP1_TimeoutHandler)
        {
            (*SCCP1_TimeoutHandler)();
        }
        IFS1bits.CCT1IF = 0;
    }
}

/**
 End of File
*/
