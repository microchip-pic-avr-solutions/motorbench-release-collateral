/**
 * PINS Generated Driver Header File 
 * 
 * @file      pins.h
 *            
 * @defgroup  pinsdriver Pins Driver
 *            
 * @brief     The Pin Driver directs the operation and function of 
 *            the selected device pins using dsPIC MCUs.
 *
 * @skipline @version   PLIB Version 1.0.5
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

#ifndef PINS_H
#define PINS_H
// Section: Includes
#include <xc.h>

/**
 * @ingroup  pinsdriver
 * @brief    Locks all the Peripheral Remapping registers and cannot be written.
 * @return   none  
 */
#define PINS_PPSLock()           (RPCONbits.IOLOCK = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Unlocks all the Peripheral Remapping registers and can be written.
 * @return   none  
 */
#define PINS_PPSUnlock()         (RPCONbits.IOLOCK = 0)

// Section: Device Pin Macros
/**
 * @ingroup  pinsdriver
 * @brief    Sets the RA1 GPIO Pin which has a custom name of MCAF_TESTPOINT1 to High
 * @pre      The RA1 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define MCAF_TESTPOINT1_SetHigh()          (_LATA1 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RA1 GPIO Pin which has a custom name of MCAF_TESTPOINT1 to Low
 * @pre      The RA1 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define MCAF_TESTPOINT1_SetLow()           (_LATA1 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RA1 GPIO Pin which has a custom name of MCAF_TESTPOINT1
 * @pre      The RA1 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define MCAF_TESTPOINT1_Toggle()           (_LATA1 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RA1 GPIO Pin which has a custom name of MCAF_TESTPOINT1
 * @param    none
 * @return   none  
 */
#define MCAF_TESTPOINT1_GetValue()         _RA1

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RA1 GPIO Pin which has a custom name of MCAF_TESTPOINT1 as Input
 * @param    none
 * @return   none  
 */
#define MCAF_TESTPOINT1_SetDigitalInput()  (_TRISA1 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RA1 GPIO Pin which has a custom name of MCAF_TESTPOINT1 as Output
 * @param    none
 * @return   none  
 */
#define MCAF_TESTPOINT1_SetDigitalOutput() (_TRISA1 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RC9 GPIO Pin which has a custom name of MCAF_LED2 to High
 * @pre      The RC9 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define MCAF_LED2_SetHigh()          (_LATC9 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RC9 GPIO Pin which has a custom name of MCAF_LED2 to Low
 * @pre      The RC9 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define MCAF_LED2_SetLow()           (_LATC9 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RC9 GPIO Pin which has a custom name of MCAF_LED2
 * @pre      The RC9 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define MCAF_LED2_Toggle()           (_LATC9 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RC9 GPIO Pin which has a custom name of MCAF_LED2
 * @param    none
 * @return   none  
 */
#define MCAF_LED2_GetValue()         _RC9

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RC9 GPIO Pin which has a custom name of MCAF_LED2 as Input
 * @param    none
 * @return   none  
 */
#define MCAF_LED2_SetDigitalInput()  (_TRISC9 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RC9 GPIO Pin which has a custom name of MCAF_LED2 as Output
 * @param    none
 * @return   none  
 */
#define MCAF_LED2_SetDigitalOutput() (_TRISC9 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RD5 GPIO Pin which has a custom name of MCAF_LED1 to High
 * @pre      The RD5 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define MCAF_LED1_SetHigh()          (_LATD5 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RD5 GPIO Pin which has a custom name of MCAF_LED1 to Low
 * @pre      The RD5 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define MCAF_LED1_SetLow()           (_LATD5 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RD5 GPIO Pin which has a custom name of MCAF_LED1
 * @pre      The RD5 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define MCAF_LED1_Toggle()           (_LATD5 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RD5 GPIO Pin which has a custom name of MCAF_LED1
 * @param    none
 * @return   none  
 */
#define MCAF_LED1_GetValue()         _RD5

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RD5 GPIO Pin which has a custom name of MCAF_LED1 as Input
 * @param    none
 * @return   none  
 */
#define MCAF_LED1_SetDigitalInput()  (_TRISD5 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RD5 GPIO Pin which has a custom name of MCAF_LED1 as Output
 * @param    none
 * @return   none  
 */
#define MCAF_LED1_SetDigitalOutput() (_TRISD5 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RD9 GPIO Pin which has a custom name of MCAF_BUTTON1 to High
 * @pre      The RD9 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define MCAF_BUTTON1_SetHigh()          (_LATD9 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RD9 GPIO Pin which has a custom name of MCAF_BUTTON1 to Low
 * @pre      The RD9 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define MCAF_BUTTON1_SetLow()           (_LATD9 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RD9 GPIO Pin which has a custom name of MCAF_BUTTON1
 * @pre      The RD9 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define MCAF_BUTTON1_Toggle()           (_LATD9 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RD9 GPIO Pin which has a custom name of MCAF_BUTTON1
 * @param    none
 * @return   none  
 */
#define MCAF_BUTTON1_GetValue()         _RD9

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RD9 GPIO Pin which has a custom name of MCAF_BUTTON1 as Input
 * @param    none
 * @return   none  
 */
#define MCAF_BUTTON1_SetDigitalInput()  (_TRISD9 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RD9 GPIO Pin which has a custom name of MCAF_BUTTON1 as Output
 * @param    none
 * @return   none  
 */
#define MCAF_BUTTON1_SetDigitalOutput() (_TRISD9 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RD10 GPIO Pin which has a custom name of MCAF_BUTTON2 to High
 * @pre      The RD10 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define MCAF_BUTTON2_SetHigh()          (_LATD10 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RD10 GPIO Pin which has a custom name of MCAF_BUTTON2 to Low
 * @pre      The RD10 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define MCAF_BUTTON2_SetLow()           (_LATD10 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RD10 GPIO Pin which has a custom name of MCAF_BUTTON2
 * @pre      The RD10 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define MCAF_BUTTON2_Toggle()           (_LATD10 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RD10 GPIO Pin which has a custom name of MCAF_BUTTON2
 * @param    none
 * @return   none  
 */
#define MCAF_BUTTON2_GetValue()         _RD10

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RD10 GPIO Pin which has a custom name of MCAF_BUTTON2 as Input
 * @param    none
 * @return   none  
 */
#define MCAF_BUTTON2_SetDigitalInput()  (_TRISD10 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RD10 GPIO Pin which has a custom name of MCAF_BUTTON2 as Output
 * @param    none
 * @return   none  
 */
#define MCAF_BUTTON2_SetDigitalOutput() (_TRISD10 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Initializes the PINS module
 * @param    none
 * @return   none  
 */
void PINS_Initialize(void);



#endif
