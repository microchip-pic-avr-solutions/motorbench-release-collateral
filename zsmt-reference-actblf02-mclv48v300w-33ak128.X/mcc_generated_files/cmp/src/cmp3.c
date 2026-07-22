/**
 * CMP3 Generated Driver Source File
 * 
 * @file      cmp3.c
 *            
 * @ingroup   cmpdriver
 *            
 * @brief     This is the generated driver source file for CMP3 driver
 *
 * @skipline @version   PLIB Version 1.1.6
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

#include <xc.h>
#include "../cmp3.h"

#ifndef CMP_FPDMDAC_ADDRESS
#define CMP_FPDMDAC_ADDRESS 0x7F20B0UL
#endif //CMP_FPDMDAC_ADDRESS

// Section: File specific functions

static void (*CMP3_EventHandler)(void) = NULL;

// Section: Driver Interface
static const struct DAC_DC_INTERFACE dac3_dc_interface = {
    .Enable = &CMP3_DACEnable,
    .Disable = &CMP3_DACDisable,
    .DataWrite = &CMP3_DACDataWrite,
};

const struct CMP_INTERFACE MCC_CMP = {
    .Initialize = &CMP3_Initialize,
    .Deinitialize = &CMP3_Deinitialize,
    .Enable = &CMP3_Enable,
    .Disable = &CMP3_Disable,
    .StatusGet = &CMP3_StatusGet,
    .Calibrate = &CMP3_Calibrate,
    
    .EventCallbackRegister = &CMP3_EventCallbackRegister,
    .Tasks = &CMP3_Tasks,
    .cmp_dac_dc_interface = &dac3_dc_interface,
    .cmp_dac_slope_interface = NULL,
};

// Section: CMP3 Module APIs

void CMP3_Initialize(void)
{           
    // Comparator Register settings
    DACCTRL1 = 0x3F7F0000UL; //FCLKDIV 1:1; DNLADJ 0x0; SIDL disabled; ON disabled; NEGINLADJ 127; POSINLADJ 63; RREN disabled; 
    DACCTRL2 = 0x0UL; //TMODTIME 0; SSTIME 0; 
    DAC3CON = 0x8000UL; //HYSSEL None; HYSPOL Rising Edge; INSEL CMP3A; CMPPOL Non Inverted; FLTREN disabled; DACOEN disabled; CBE disabled; UPDTMDIS disabled; EXTUPD disabled; IRQM Interrupts are disabled; DACEN enabled; TMCB 0; 

    //Slope Settings
    DAC3DAT = 0xF3300CDUL; //DACLOW 205; DACDAT 3891; 
    DAC3SLPCON = 0x0UL; //SLPSTRT None; SLPSTOPB None; SLPSTOPA None; HCFSEL None; FFSEN disabled; PSE Negative; TWME disabled; HME disabled; SLOPEN disabled; 
    DAC3SLPDAT = 0x0UL; //DAC3SLPDAT 0; 
    
    CMP3_EventCallbackRegister(&CMP3_EventCallback);
    
    DACCTRL1bits.ON = 1U;
}

void CMP3_Deinitialize(void)
{ 
    DACCTRL1bits.ON = 0;
    
    
    // Comparator Register settings
    DACCTRL1 = 0x3F7F0000UL;
    DACCTRL2 = 0x8A0001UL;
    DAC3CON = 0x0UL;

    //Slope Settings
    DAC3DAT = 0x0UL;
    DAC3SLPCON = 0x0UL;
    DAC3SLPDAT = 0x0UL;
}

void CMP3_Calibrate(void)
{
    uint32_t *fpdmdac = (uint32_t*)CMP_FPDMDAC_ADDRESS;
    DACCTRL1bits.POSINLADJ = ((*fpdmdac) & _DACCTRL1_POSINLADJ_MASK) >> _DACCTRL1_POSINLADJ_POSITION;
    DACCTRL1bits.NEGINLADJ = ((*fpdmdac) & _DACCTRL1_NEGINLADJ_MASK) >> _DACCTRL1_NEGINLADJ_POSITION;
    DACCTRL1bits.DNLADJ = ((*fpdmdac) & _DACCTRL1_DNLADJ_MASK) >> _DACCTRL1_DNLADJ_POSITION;
    DACCTRL1bits.RREN = 1U;
}

void CMP3_EventCallbackRegister(void (*handler)(void))
{
    if(NULL != handler)
    {
        CMP3_EventHandler = handler;
    }
}

void __attribute__ ((weak)) CMP3_EventCallback(void)
{ 
   
}
 
void CMP3_Tasks(void)
{
    if(IFS2bits.CMP3IF == 1U)
    {
        // CMP3 callback function 
        if(NULL != CMP3_EventHandler)
        {
            (*CMP3_EventHandler)();
        }
    
        // clear the CMP3 interrupt flag
        IFS2bits.CMP3IF = 0U;
    }
}

/**
 End of File
*/
