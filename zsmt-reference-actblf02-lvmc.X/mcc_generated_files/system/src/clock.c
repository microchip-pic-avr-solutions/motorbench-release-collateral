/**
 * CLOCK Generated Driver Source File 
 * 
 * @file      clock.c
 *            
 * @ingroup   clockdriver
 *            
 * @brief     This is the generated source file for CLOCK driver
 *
 * @skipline @version   PLIB Version 1.4.6
 *
 * @skipline  Device : dsPIC33CK256MP508
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

// Section: Includes
#include <xc.h>
#include <stdint.h>
#include "../clock.h"

#define OSC_SOURCE_FRC 0U
#define OSC_SOURCE_FRC_PLL 0x1U
#define OSC_SOURCE_POSC_PLL 0x3U
#define OSCCONH_NOSC_MASK 0x07U

void CLOCK_Initialize(void)
{
    //If PLL derived clock sources are used, then switch to FRC clock before changing PLL related settings
    if(OSCCONbits.COSC == OSC_SOURCE_FRC_PLL || OSCCONbits.COSC == OSC_SOURCE_POSC_PLL)
    {
        //Set to FRC clock if current clock is not FRC
        __builtin_write_OSCCONH((OSCCONH & ~ OSCCONH_NOSC_MASK) | OSC_SOURCE_FRC);
        __builtin_write_OSCCONL((uint8_t) (0x01));
        // Wait for Clock switch to occur
        while (OSCCONbits.OSWEN != 0){}
    }
    // RCDIV FRC/1; PLLPRE 1:1; DOZE 1:8; DOZEN disabled; ROI disabled; 
   CLKDIV = 0x3001U;
    // PLLDIV 50; 
   PLLFBD = 0x32U;
    // TUN Center frequency; 
   OSCTUN = 0x0U;
    // PLLPOST 1:1; VCODIV FVCO/4; POST2DIV 1:1; 
   PLLDIV = 0x11U;
    // ENAPLL disabled; FRCSEL FRC Oscillator; APLLPRE 1:1; 
   ACLKCON1 = 0x101U;
    // APLLFBDIV 150; 
   APLLFBD1 = 0x96U;
    // APSTSCLR 1:4; APOST2DIV 1:1; AVCODIV FVCO/4; 
   APLLDIV1 = 0x41U;
    // CANCLKEN disabled; CANCLKSEL FVCO/4; CANCLKDIV Divide by 1; 
   CANCLKCON = 0x500U;
    // ROEN disabled; DIVSWEN disabled; ROSLP disabled; ROSEL ; OE disabled; ROSIDL disabled; 
   REFOCONL = 0x0U;
    // RODIV 0; 
   REFOCONH = 0x0U;
    // ROTRIM 0; 
   REFOTRIMH = 0x0U;
    // IOLOCK disabled; 
   RPCON = 0x0U;
    // PMDLOCK disabled; 
   PMDCON = 0x0U;
    // ADC1MD enabled; T1MD enabled; U2MD enabled; U1MD enabled; SPI2MD enabled; SPI1MD enabled; QEIMD enabled; PWMMD enabled; I2C1MD enabled; C1MD enabled; 
   PMD1 = 0x0U;
    // CCP2MD enabled; CCP1MD enabled; CCP4MD enabled; CCP3MD enabled; CCP7MD enabled; CCP8MD enabled; CCP5MD enabled; CCP6MD enabled; CCP9MD enabled; 
   PMD2 = 0x0U;
    // U3MD enabled; CRCMD enabled; I2C2MD enabled; I2C3MD enabled; QEI2MD enabled; PMPMD enabled; 
   PMD3 = 0x0U;
    // REFOMD enabled; 
   PMD4 = 0x0U;
    // DMA1MD enabled; DMA2MD enabled; DMA3MD enabled; DMA0MD enabled; SPI3MD enabled; 
   PMD6 = 0x0U;
    // PTGMD enabled; CMP1MD enabled; CMP3MD enabled; CMP2MD enabled; 
   PMD7 = 0x0U;
    // DMTMD enabled; CLC3MD enabled; OPAMPMD enabled; BIASMD enabled; CLC4MD enabled; SENT1MD enabled; CLC1MD enabled; CLC2MD enabled; SENT2MD enabled; 
   PMD8 = 0x0U;
    /*  
       Input frequency                               :  8.00 MHz
       Clock source                                  :  FRC Oscillator with PLL
       System frequency (Fosc)                       :  200.00 MHz [(8.00 MHz / 1) * 50 / 1 / 2 = 200.00 MHz]
       PLL VCO frequency (Fvco)                      :  400.00 MHz [(8.00 MHz / 1) * 50 = 400.00 MHz]
       PLL output frequency (Fpllo)                  :  400.00 MHz [(8.00 MHz / 1) * 50 / 1 = 400.00 MHz]
       PLL VCO divider frequency (Fvcodiv)           :  100.00 MHz [400.00 MHz / 4 = 100.00 MHz]
       Clock switching enabled                       :  true
       Clock source when device boots                :  FRC Oscillator
       Auxiliary clock source                        :  FRC Oscillator
       Auxiliary clock input frequency               :  8.00 MHz
       Auxiliary clock PLL output frequency (AFpllo) :  8.00 MHz
    */
    // CF no clock failure; NOSC FRCPLL; CLKLOCK unlocked; OSWEN Switch is Complete; 
    __builtin_write_OSCCONH((uint8_t) (0x01));
    __builtin_write_OSCCONL((uint8_t) (0x01));
    // Wait for Clock switch to occur
    while (OSCCONbits.OSWEN != 0){}
    while (OSCCONbits.LOCK != 1){}
}

bool CLOCK_AuxPllLockStatusGet(void)
{
    return ACLKCON1bits.APLLCK;
}

