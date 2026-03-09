/**
 * CMP Generated Driver Types Header File
 * 
 * @file      cmp_types.h
 * 
 * @ingroup   clockdriver
 * 
 * @brief     This is the generated driver types header file for the CMP driver
 *
 * @version   PLIB Version 1.1.5
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

#ifndef CMP_TYPES_H
#define CMP_TYPES_H


/**
 @ingroup  clockdriver
 @enum     CMP_DAC_TRANSISION_MODE
 @brief    This enum is used to set the transision mode between smooth 
           and slow transision or fast and sharp transision to new data values
*/
enum CMP_DAC_TRANSISION_MODE
{
    CMP_DAC_TRANSISION_MODE_ENABLED = 0U, /**< Smoother and slower transision to the target value */
    CMP_DAC_TRANSISION_MODE_DISABLED = 1U, /**< Faster transision to the target value and ripple may be introduced  */
    
};

/**
 @ingroup  clockdriver
 @enum     CMP_DAC_SLOPE_UPDATE_MODE
 @brief    CMP slope data registers update mode
 @note     Applicable in slope mode
*/
enum CMP_DAC_SLOPE_UPDATE_MODE
{
    CMP_DAC_SLOPE_UPDATE_IMMIDIATE = 0U, /**< Updates slope related data registers immidiately */
    CMP_DAC_SLOPE_UPDATE_TRIGGERED = 1U, /**< Updates slope related data registers during the external trigger */
    
};

#endif // CMP_TYPES_H


