/**
 * OPA Generated Driver Interface Header File
 * 
 * @file      opa_types.h
 * 
 * @ingroup   opadriver
 * 
 * @brief     This is the generated driver interface header file for the OPA driver
 *
 * @skipline @version   PLIB Version 1.2.2
 *
 * @skipline  Device : dsPIC33AK128MC106
*/

/*disclaimer*/

#ifndef OPA_TYPES_H
#define    OPA_TYPES_H

// Section: Type defines

/**
 @ingroup  opadriver
 @enum     OPA_DIFFERENTIAL_INPUT_MODE
 @brief    This defines Differential input mode enumeration for OPA
*/
enum OPA_DIFFERENTIAL_INPUT_MODE
{ 
    OPA_DIFFERENTIAL_INPUT_NMOS_PMOS_PAIR   = 0,    /**< Use both NMOS and PMOS differential input pair */
    OPA_DIFFERENTIAL_INPUT_NMOS_INPUT_PAIR  = 1,    /**< Turn NMOS differntial input pair ON and turn PMOS differential input pair off */
    OPA_DIFFERENTIAL_INPUT_PMOS_INPUT_PAIR  = 2,    /**< Turn PMOS differntial input pair ON and turn NMOS differential input pair off */
    OPA_DIFFERENTIAL_INPUT_NONE             = 3     /**< No differential input pair selected */

}; 

/**
 @ingroup  opadriver
 @enum     OPA_OFFSET_INPUT_TYPE
 @brief    This defines offset input type enumeration for OPA
*/
enum OPA_OFFSET_INPUT_TYPE
{
    OPA_PMOS_OFFSET_IN_HIGH_POWER_MODE,     /**< Offset Correction for PMOS Differential Input Pair (High-Power mode) */
    OPA_NMOS_OFFSET_IN_HIGH_POWER_MODE,     /**< Offset Correction for NMOS Differential Input Pair (High-Power mode) */
    OPA_PMOS_OFFSET_IN_LOW_POWER_MODE,      /**< Offset Correction for PMOS Differential Input Pair (Low-Power mode) */
    OPA_NMOS_OFFSET_IN_LOW_POWER_MODE       /**< Offset Correction for NMOS Differential Input Pair (Low-Power mode) */
};

/**
 @ingroup  opadriver
 @enum     OPA_OUTPUT_VOLTAGE_OFFSET_CORRECTION
 @brief    This defines offset correction unit voltage enumeration for OPA
 @Note     1 Unit voltage = trim step voltage 3 mV
*/
enum OPA_OUTPUT_VOLTAGE_OFFSET_CORRECTION
{
   DECREASE_15_UNIT_VOLTAGE = 0xf,           /**< Correct offset by -15 unit voltage */

   DECREASE_14_UNIT_VOLTAGE = 0xe,           /**< Correct offset by -14 unit voltage */

   DECREASE_13_UNIT_VOLTAGE = 0xd,           /**< Correct offset by -13 unit voltage */

   DECREASE_12_UNIT_VOLTAGE = 0xc,           /**< Correct offset by -12 unit voltage */

   DECREASE_11_UNIT_VOLTAGE = 0xb,           /**< Correct offset by -11 unit voltage */

   DECREASE_10_UNIT_VOLTAGE = 0xa,           /**< Correct offset by -10 unit voltage */

   DECREASE_9_UNIT_VOLTAGE = 0x9,           /**< Correct offset by -9 unit voltage */

   DECREASE_8_UNIT_VOLTAGE = 0x8,           /**< Correct offset by -8 unit voltage */

   DECREASE_7_UNIT_VOLTAGE = 0x7,           /**< Correct offset by -7 unit voltage */

   DECREASE_6_UNIT_VOLTAGE = 0x6,           /**< Correct offset by -6 unit voltage */

   DECREASE_5_UNIT_VOLTAGE = 0x5,           /**< Correct offset by -5 unit voltage */

   DECREASE_4_UNIT_VOLTAGE = 0x4,           /**< Correct offset by -4 unit voltage */

   DECREASE_3_UNIT_VOLTAGE = 0x3,           /**< Correct offset by -3 unit voltage */

   DECREASE_2_UNIT_VOLTAGE = 0x2,           /**< Correct offset by -2 unit voltage */

   DECREASE_1_UNIT_VOLTAGE = 0x1,           /**< Correct offset by -1 unit voltage */

   NO_CORRECTION = 0x0,           /**< Correct offset by 0 unit voltage */

   INCREASE_1_UNIT_VOLTAGE = 0x1e,           /**< Correct offset by +1 unit voltage */

   INCREASE_2_UNIT_VOLTAGE = 0x1d,           /**< Correct offset by +2 unit voltage */

   INCREASE_3_UNIT_VOLTAGE = 0x1c,           /**< Correct offset by +3 unit voltage */

   INCREASE_4_UNIT_VOLTAGE = 0x1b,           /**< Correct offset by +4 unit voltage */

   INCREASE_5_UNIT_VOLTAGE = 0x1a,           /**< Correct offset by +5 unit voltage */

   INCREASE_6_UNIT_VOLTAGE = 0x19,           /**< Correct offset by +6 unit voltage */

   INCREASE_7_UNIT_VOLTAGE = 0x18,           /**< Correct offset by +7 unit voltage */

   INCREASE_8_UNIT_VOLTAGE = 0x17,           /**< Correct offset by +8 unit voltage */

   INCREASE_9_UNIT_VOLTAGE = 0x16,           /**< Correct offset by +9 unit voltage */

   INCREASE_10_UNIT_VOLTAGE = 0x15,           /**< Correct offset by +10 unit voltage */

   INCREASE_11_UNIT_VOLTAGE = 0x14,           /**< Correct offset by +11 unit voltage */

   INCREASE_12_UNIT_VOLTAGE = 0x13,           /**< Correct offset by +12 unit voltage */

   INCREASE_13_UNIT_VOLTAGE = 0x12,           /**< Correct offset by +13 unit voltage */

   INCREASE_14_UNIT_VOLTAGE = 0x11,           /**< Correct offset by +14 unit voltage */

   INCREASE_15_UNIT_VOLTAGE = 0x10,           /**< Correct offset by +15 unit voltage */

};

#endif  //OPA_TYPES_H
/**
 End of File 
*/
