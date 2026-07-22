/**
 * OPA Generated Driver Interface Header File
 * 
 * @file      opa_interface.h
 * 
 * @defgroup  opadriver OPA Driver
 * 
 * @brief     Operational Amplifier Driver used for a wide variety of purposes 
 *            such as Voltage Amplifiers, Voltage Followers, Interfacing Sensors and 
 *            Signal Conditioning of Analog Input Signals using dsPIC MCUs.
 *
 * @skipline @version   PLIB Version 1.2.3
 *
 * @skipline  Device : dsPIC33AK128MC106
*/

/*disclaimer*/

#ifndef OPA_INTERFACE_H
#define OPA_INTERFACE_H


#ifdef __cplusplus
extern "C" {
#endif

// Section: Included Files

#include <stdbool.h>
#include "opa_types.h"

// Section: Data Type Definitions
        
/**
 @ingroup  opadriver
 @struct   OPA_INTERFACE
 @brief    Structure containing the function pointers of OPA driver.
*/
struct OPA_INTERFACE
{   
    void (*Intitialize)(void);      
    ///< Pointer to OPAx_Initialize e.g. \ref OPA1_Initialize
    
    void (*Deintitialize)(void);    
    ///< Pointer to OPAx_Deinitialize e.g. \ref OPA1_Deinitialize
    
    void (*Enable)(void);           
    ///< Pointer to OPAx_Enable e.g. \ref OPA1_Enable
    
    void (*Disable)(void);          
    ///< Pointer to OPAx_Disable e.g. \ref OPA1_Disable
    
    void (*UnityGainEnable)(bool enable);          
    ///< Pointer to OPAx_UnityGainEnable e.g. \ref OPA1_UnityGainEnable
    
    void (*HighPowerModeEnable)(bool enable);          
    ///< Pointer to OPAx_HighPowerModeEnable e.g. \ref OPA1_HighPowerModeEnable
    
    void (*OutputMonitorEnable)(bool enable);          
    ///< Pointer to OPAx_OutputMonitorEnable e.g. \ref OPA1_OutputMonitorEnable
	
	void (*DifferentialInputModeSet) (enum OPA_DIFFERENTIAL_INPUT_MODE input);
    ///< Pointer to OPAx_DifferentialInputModeSet e.g. \ref OPA1_DifferentialInputModeSet
    
    void (*OffsetCorrection) (enum OPA_OFFSET_INPUT_TYPE inputType, enum OPA_OUTPUT_VOLTAGE_OFFSET_CORRECTION unitVoltage);
    ///< Pointer to OPAx_OffsetCorrection e.g. \ref OPA1_OffsetCorrection
};

#ifdef __cplusplus
}
#endif

#endif //OPA_INTERFACE_H

