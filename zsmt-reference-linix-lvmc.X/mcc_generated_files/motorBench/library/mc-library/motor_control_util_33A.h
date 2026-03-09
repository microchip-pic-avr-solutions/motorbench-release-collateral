/* 
 * File:   motor_control_util.h
 * 
 * Utility routines for computation used only in Motor control library
 * 
 */

/* *********************************************************************
 *
 * (c) 2017 Microchip Technology Inc. and its subsidiaries. You may use
 * this software and any derivatives exclusively with Microchip products.
 *
 * This software and any accompanying information is for suggestion only.
 * It does not modify Microchip's standard warranty for its products.
 * You agree that you are solely responsible for testing the software and
 * determining its suitability.  Microchip has no obligation to modify,
 * test, certify, or support the software.
 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE, OR ITS INTERACTION WITH
 * MICROCHIP PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY
 * APPLICATION.
 
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL,
 * PUNITIVE, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF
 * ANY KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF
 * MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE
 * FORESEEABLE.  TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL
 * LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT
 * EXCEED THE AMOUNT OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO
 * MICROCHIP FOR THIS SOFTWARE.
 
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF
 * THESE TERMS.
 *
 * *****************************************************************************/

#ifndef _MOTOR_CONTROL_UTIL_H_
#define	_MOTOR_CONTROL_UTIL_H_

#include <stdint.h>

// Declarations for DSP registers
#include "motor_control_dsp.h"    

/*
 * Access to accumulator registers is required
 * only for XC16 1.25 and earlier; this causes
 * a dependency on <xc.h> which is unnecessary
 * for newer versions of the compiler.
 */
#if __XC16_VERSION__ < 1026
#include <xc.h>
#endif


#ifdef	__cplusplus
extern "C" {
#endif


/**
 * Helper function to multiply an unsigned 16-bit quantity
 * and a signed 16-bit quantity and shift-right by 16.
 * (one of the inputs should be a Q16 fixed-point values,
 * and the other one and the output have identical binary points,
 * e.g. Q12 = Q16 * Q12, or Q12 = Q12 * Q16)
 *
 * @param a first input (unsigned)
 * @param b second input (signed)
 * @return (a*b)>>16
 */
inline static int16_t MC_UTIL_mulus16(uint16_t a, int16_t b)
{
    return __builtin_mulus_16(a,b) >> 16;
}

/**
 * Compute the average of two int16_t values
 * @param a first value
 * @param b second value
 * @return (a+b)/2
 */

inline static int16_t MC_UTIL_AverageS16(int16_t a, int16_t b)
{
    return (int16_t)((((int32_t)a) + b) >> 1);
}

/**
 * Compute the minimum and maximum of a set of three int16_t values
 * @param a first value
 * @param b second value
 * @param c third value
 * @return struct containing minimum and maximum value --
 */
inline static MC_minmax16_t MC_UTIL_MinMax3_S16(int16_t a, int16_t b, int16_t c)  //unsupported
{
    MC_minmax16_t result;
    result.max = a;
    result.min = a;
    if(b < result.min)
    {
        result.min = b;
    }
    else if(b > result.max)
    {
        result.max = b;
    }

    if(c < result.min)
    {
        result.min = c;
    }
    else if(c > result.max)
    {
        result.max = c;
    }
    return result;
}
/**  Read accumulator A */
inline static int32_t MC_UTIL_readAccA32()
{
#if __XC16_VERSION__ >= 1030
    return __builtin_sacd(a_Reg, 0);
#elif __XC16_VERSION__ >= 1026
    const int32_t tmp = __builtin_sacd(a_Reg, 0);
    /* Prevent optimization from re-ordering/ignoring this sequence of operations */
    asm volatile ("");
    return tmp;
#elif defined(__dsPIC33A__)
    return __builtin_sacr(a_Reg, 16);
#else
    int32_t result;
    /* Prevent optimization from re-ordering/ignoring this sequence of operations */
    asm volatile ("" : "+w"(a_Reg):); 
    result = ACCAH;
    result <<= 16;
    result |= ACCAL; 
    return result;
#endif
}

/**  Write accumulator B */
inline static void MC_UTIL_writeAccB32(int32_t input)
{
#if __XC16_VERSION__ >= 1030
    b_Reg = __builtin_lacd(input, 0);
#elif __XC16_VERSION__ >= 1026
    const int32_t tmp = input;
    asm volatile ("" :: "r"(tmp)); 
    b_Reg = __builtin_lacd(tmp, 0);
#else
    uint32_t temp_dword;
    uint16_t temp_word;
    temp_dword = 0xFFFF0000 & input;
    temp_dword = temp_dword >> 16;
    temp_word = (uint16_t)temp_dword;
    b_Reg = __builtin_lac(temp_word, 0);
    /* Prevent optimization from re-ordering/ignoring this sequence of operations */
    asm volatile ("" : "+w"(b_Reg):); 
    temp_word = (uint16_t)(0xFFFF & input);
    ACCBL = temp_word;
#endif

}

/**
 * Computes the saturated signed addition x+y limited to the -32768,
 * +32767 range.
 * 
 * @param x input value
 * @param y input value
 * @return the saturated signed addition x+y
 */
inline static int16_t MC_UTIL_SatAddS16(int16_t x, int16_t y)
{
    /* Saturation can only occur if x and y have the same sign.
     * If x is nonnegative and y is nonnegative and we get overflow,
     *    x+y is positive and should be limited to 32767.
     * If x is negative and y is negative and we get overflow,
     *    x+y is negative and should be limited to -32768.
     * In either case, if overflow occurs, 
     *    we can use either x or y's most significant bit to decide the result
     */
    int16_t saturated_sum;
    asm volatile (
        "   ;UTIL_SatAddS16\n"
        "   asr.w %[y], #15, %[s]\n"  // s = 0xFFFF if y is negative, 0 otherwise (1 cycle)
        "   btg.w %[s], #15\n"        // s = 0x7FFF if y is negative, 0x8000 otherwise (1 cycle)
        "   add.w %[x], %[y], %[x]\n" // x = x+y (1 cycle)
        "   bra NOV, 1f\n"          // Branch forward if OV (1x16b branch, work as skip next instruction) (cycles 1 (2 or 3))
        "   com.w %[s], %[x]\n"       // x = ~s if overflow bit was set (1 cycle)
        "   1:\n"       // skipped 1's complement label
        : [x]"+r"(x), // read and write operand, and allow to use a register operand
          [s]"=&r"(saturated_sum) // write only, prev value discared, replaced by output data, indicate operand is an earlyclobber
        : [y]"r"(y) // allow to use register operand
    );
    return x;
}




#ifdef	__cplusplus
}
#endif

#endif	/* _MOTOR_CONTROL_UTIL_H_ */

