/**
 * CMP Generated Driver Interface Header File
 * 
 * @file      cmp_interface.h
 *            
 * @defgroup  cmpdriver CMP Driver
 *            
 * @brief     High Speed Analog Comparator with Slope Compensation DAC driver using dsPIC MCUs. 
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

#ifndef CMP_INTERFACE_H
#define CMP_INTERFACE_H


#ifdef __cplusplus
extern "C" {
#endif

// Section: Included Files

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "cmp_types.h"

// Section: Data Type Definitions
  
/**
 @ingroup  cmpdriver
 @struct   DAC_DC_INTERFACE
 @brief    Structure containing the function pointers of DAC driver in DC mode
*/
 
struct DAC_DC_INTERFACE
{
    void (*Enable)(void);
    ///< Pointer to CMPx_DACEnable e.g. \ref CMP1_DACEnable
    
    void (*Disable)(void);
    ///< Pointer to CMPx_DACDisable e.g. \ref CMP1_DACDisable
    
    void (*DataWrite)(size_t value);
    ///< Pointer to CMPx_DACDataWrite e.g. \ref CMP1_DACDataWrite
};

/**
 @ingroup  cmpdriver
 @struct   DAC_SLOPE_INTERFACE
 @brief    Structure containing the function pointers of DAC driver in Slope mode
*/
 
struct DAC_SLOPE_INTERFACE
{
    void (*Enable)(void);
    ///< Pointer to CMPx_DACEnable e.g. \ref CMP1_DACEnable
    
    void (*Disable)(void);
    ///< Pointer to CMPx_DACDisable e.g. \ref CMP1_DACDisable
    
    void (*DataHighWrite)(uint16_t dacHighLimit);
    ///< Pointer to CMPx_DACDataHighWrite e.g. \ref CMP1_DACDataHighWrite
    
    void (*DataLowWrite)(uint16_t dacLowLimit);
    ///< Pointer to CMPx_DACDataLowWrite e.g. \ref CMP1_DACDataLowWrite
    
    void (*SlopeWrite)(uint16_t slopeRate);
    ///< Pointer to CMPx_DACSlopeWrite e.g. \ref CMP1_DACSlopeWrite
    
    void (*SlopeUpdateMode)(enum CMP_DAC_SLOPE_UPDATE_MODE updateMode);
    ///< Pointer to CMPx_DACSlopeUpdateMode e.g. \ref CMP1_DACSlopeUpdateMode
};

/**
 @ingroup  cmpdriver
 @struct   CMP_INTERFACE
 @brief    Structure containing the function pointers of CMP driver
*/
 
struct CMP_INTERFACE
{
    void (*Initialize)(void);
    ///< Pointer to CMPx_Initialize e.g. \ref CMP1_Initialize
    
    void (*Deinitialize)(void);
    ///< Pointer to CMPx_Deinitialize e.g. \ref CMP1_Deinitialize
    
    void (*Calibrate)(void);
    ///< Pointer to CMPx_Deinitialize e.g. \ref CMP1_Deinitialize
    
    void (*Enable)(void);
    ///< Pointer to CMPx_Enable e.g. \ref CMP1_Enable
    
    void (*Disable)(void);
    ///< Pointer to CMPx_Disable e.g. \ref CMP1_Disable
    
    bool (*StatusGet)(void);
    ///< Pointer to CMPx_StatusGet e.g. \ref CMP1_StatusGet
    
    void (*EventCallbackRegister)(void (*handler)(void));
    ///< Pointer to CMPx_EventCallbackRegister e.g. \ref CMP1_EventCallbackRegister
    
    void (*Tasks)(void);
    ///< Pointer to CMPx_Tasks e.g. \ref CMP1_Tasks (Supported only in polling mode)
    
    const struct DAC_DC_INTERFACE *cmp_dac_dc_interface;
    ///< Pointer to \ref DAC_DC_INTERFACE
    
    const struct DAC_SLOPE_INTERFACE *cmp_dac_slope_interface;
    ///< Pointer to \ref DAC_SLOPE_INTERFACE
};

#ifdef __cplusplus
}
#endif

#endif
