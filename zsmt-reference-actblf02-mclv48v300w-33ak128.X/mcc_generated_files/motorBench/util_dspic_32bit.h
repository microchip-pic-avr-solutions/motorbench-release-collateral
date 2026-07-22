/**
 * util_dspic_32bit.h
 * 
 * Architecture-specific utility routines for 32-bit dsPIC devices
 * 
 * Component: miscellaneous
 */

/* *********************************************************************
 *
 * Motor Control Application Framework
 * R9/RC32 (commit 132904, build on 2026 Jul 14)
 *
 * (c) 2017 - 2023 Microchip Technology Inc. and its subsidiaries. You may use
 * this software and any derivatives exclusively with Microchip products.
 *
 * This software and any accompanying information is for suggestion only.
 * It does not modify Microchip's standard warranty for its products.
 * You agree that you are solely responsible for testing the software and
 * determining its suitability.  Microchip has no obligation to modify,
 * test, certify, or support the software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE, OR ITS INTERACTION WITH
 * MICROCHIP PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY
 * APPLICATION.
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL,
 * PUNITIVE, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF
 * ANY KIND WHATSOEVER RELATED TO THE USE OF THIS SOFTWARE, THE
 * motorBench(R) DEVELOPMENT SUITE TOOL, PARAMETERS AND GENERATED CODE,
 * HOWEVER CAUSED, BY END USERS, WHETHER MICROCHIP'S CUSTOMERS OR
 * CUSTOMER'S CUSTOMERS, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES OR THE DAMAGES ARE FORESEEABLE. TO THE
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
 * CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT
 * OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS
 * SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF
 * THESE TERMS.
 *
 * *****************************************************************************/

#ifndef MCAF_UTIL_DSPIC_32BIT_H 
#define MCAF_UTIL_DSPIC_32BIT_H 

#include <stdint.h>
#include <stdbool.h>
#include "util_types.h"

#ifdef __cplusplus
extern "C" {
#endif




/**
 * Shifts right a 32-bit value by 15, returning the lower 16 bits of the result.
 * (We can gain some speed by doing it in a way that the compiler handles better.)
 * 
 * @param x input
 * @return x >> 15
 */
inline static int16_t UTIL_Shr15(int32_t x)
{
    return x >> 15;
}

/**
 * Helper function to multiply two signed 16-bit quantities
 * and return a signed 32-bit result.
 * 
 * @param a first input (signed)
 * @param b second input (signed)
 * @return product a*b (signed)
 */
inline static int32_t UTIL_mulss(int16_t a, int16_t b)
{
    return __builtin_mulss_16(a,b);
}

/**
 * Helper function to multiply an unsigned 16-bit quantity
 * and a signed 16-bit quantity
 * and return a signed 32-bit result.
 * 
 * @param a first input (unsigned)
 * @param b second input (signed)
 * @return product a*b (signed)
 */
inline static int32_t UTIL_mulus(uint16_t a, int16_t b)
{
    return __builtin_mulus_16(a,b);
}

/**
 * Helper function to multiply an signed 16-bit quantity
 * and an unsigned 16-bit quantity
 * and return a signed 32-bit result.
 * 
 * @param a first input (signed)
 * @param b second input (unsigned)
 * @return product a*b (signed)
 */
inline static int32_t UTIL_mulsu(int16_t a, uint16_t b)
{
    return __builtin_mulsu_16(a,b);
}

/**
 * Helper function to multiply two unsigned 16-bit quantities
 * and return an unsigned 32-bit result.
 * 
 * @param a first input (unsigned)
 * @param b second input (unsigned)
 * @return product a*b (unsigned)
 */
inline static uint32_t UTIL_muluu(uint16_t a, uint16_t b)
{
    return __builtin_muluu_16(a,b);
}



/**
 * Computes the absolute value of an int16_t number.
 * An input of -32768 will produce an output of +32767;
 * clipping is preferable to overflow. (The dsPIC libq implementation
 * of _Q15abs() uses these same instructions.)
 * 
 * @param x input value
 * @return the absolute value of x
 */
inline static int16_t UTIL_Abs16(int16_t x)
{
    asm volatile (
        "   ;UTIL_Abs16\n"
        "   add.w %[x], #0, %[x]\n" // Fill ALU flags
        "   bra ge, 1f\n" // If possitive, branch over 2s complement
        "   com.w %[x], %[x]\n" // If negative, apply 2s complement
        "   add.w #1, %[x]\n"
        "   bra nn, 1f\n" // If possitve, jump to the end
        "   com.w %[x], %[x]\n" // If negative, it's 0x8000, therefore apply 1s comp
        "   1:\n"        
        : [x]"+r"(x)
    );
    return x;
}


/**
 * Computes the saturated signed addition x+y limited to the -32768,
 * +32767 range.
 * 
 * @param x input value
 * @param y input value
 * @return the saturated signed addition x+y
 */
inline static int16_t UTIL_SatAddS16(int16_t x, int16_t y)
{
	return __builtin_sat_add_s16(x, y);
}

/**
 * Computes the saturated signed difference x-y, which is equal to
 * (x-y) limited to the -32768, +32767 range.
 * 
 * @param x input value
 * @param y input value
 * @return the saturated signed difference x-y
 */
inline static int16_t UTIL_SatSubS16(int16_t x, int16_t y)
{
    return __builtin_sat_sub_s16(x, y);
}

/**
 * Computes the approximate absolute value of an int16_t number.
 * Nonnegative inputs produce an exact output;
 * negative inputs produce an output that is off by 1
 * (e.g. abs16approx(-37) = 36, abs16approx(-32768) = 32767)
 * in order to decrease execution time while preventing overflow.
 * 
 * This function should *not* be used by algorithms which are sensitive
 * to off-by-1 errors: integrators being the main example.
 * 
 * @param x input
 * @return the approximate absolute value of x, equal to (x < 0 ? ~x : x)
 */
inline static int16_t UTIL_Abs16Approx(int16_t x)
{
    return x < 0 ? ~x : x;
}


/**
 * Computes the Q15 quotient of num/den.
 * Does NOT check for overflow or divide-by-zero. 
 *
 * More specifically, it returns the integer calculation (32768 * num)/den,
 * if that is representable as an int16_t. 
 *
 * This is used mainly with num and den that have the same binary point,
 * in which case the result is a Q15 value.
 *
 * UTIL_DivQ15 can also act on inputs with unequal binary points:
 * if num and den are fixed-point values with Qn and Qd binary points,
 * then the result is a fixed-point value with binary point of Q(n-d+15).
 *
 * @param num dividend with Qn binary point
 * @param den divisor with Qd binary point
 * @return quotient = num/den with Q(n-d+15) binary point
 */
inline static int16_t UTIL_DivQ15(int16_t num, int16_t den)
{
    return __builtin_divf_16(num, den);
}

/**
 * Computes the Q15 quotient of num/den, 
 * saturating the result to +32767 on overflow.
 * (NOTE: This assumes num/den is a positive value if it can overflow.
 * Negative quotients that overflow are NOT handled properly by this function.)
 * 
 * Behavior is identical to UTIL_DivQ15(),
 * except that on overflow (if the results are not representable in a signed
 * 16-bit integer) the result is overwritten with 32767, providing a saturated
 * positive value for positive overflow. 
 * 
 * See UTIL_DivQ15 for guidance on using arbitrary binary points;
 * the same guidance applies to this function.
 * ----------------------------------------------------------------
 * 
 * @param num dividend with Qn binary point
 * @param den divisor with Qd binary point
 * @return quotient = num/den with Q(n-d+15) binary point
 */
inline static int16_t UTIL_DivQ15SatPos(int16_t num, int16_t den)
{
    union
    {
        uint16_t numerator;
        uint16_t quotient;
        uint64_t value64;   // "view" of the union exposed to inline asm
    } divdata;

    /* 
     * DIVF.W on dsPIC33A puts the quotient in Wm, remainder in Wm+1,
     * where Wm is the numerator input register.
     * From an input/output standpoint, all we care about is the low 16 bits of Wm
     */

    divdata.numerator = num;

    asm (
        "    ;UTIL_DivQ15SatPos\n"
        "    repeat  #__TARGET_DIVIDE_CYCLES16\n" 
        "    divf.w    %[x],%[den]\n"
        "    bra       NOV, 1f\n"               
        "    mov.w     #0x7fff, %[x]\n" // saturate on overflow; skip otherwise
        "    1:\n"
        : [x]"+r"(divdata.value64)
        : [den]"r"(den)
        : "cc", "RCOUNT"
    );
    return divdata.quotient;
}


/**
 * Toggles the sign bit (bit 15)
 * @param x
 * @return x ^ 0x8000
 */
inline static uint16_t UTIL_ToggleBit15(uint16_t x)
{
    asm (
        "    ;UTIL_ToggleBit15\n"
        "    btg.w %[x], #15\n"
        : [x]"+r"(x)
    );
    return x;  
}



/**
 * Compute the average of two uint16_t values
 * @param a first value
 * @param b second value
 * @return (a+b)/2
 */
inline static uint16_t UTIL_AverageU16(uint16_t a, uint16_t b)
{
    uint16_t c;
    
    asm (
        "    ;UTIL_AverageU16\n"
        "    add.w %[a],%[b],%[c]\n"
        "    rrc.w %[c],%[c]"
        : [c]"=r"(c)
        : [a]"r"(a), [b]"r"(b)
    );
    return c;

}

/**
 * Compute the average of two int16_t values
 * @param a first value
 * @param b second value
 * @return (a+b)/2
 */
inline static int16_t UTIL_AverageS16(int16_t a, int16_t b)
{
    return ((int32_t)a + b) >> 1;
}

/**
 * Compute the average of two int16_t values
 * @param a first value
 * @param b second value
 * @return (a+b)/2
 */
inline static int16_t UTIL_AverageS16_asm(int16_t a, int16_t b)
{
    return UTIL_ToggleBit15(
             UTIL_AverageU16(
               UTIL_ToggleBit15(a),
               UTIL_ToggleBit15(b)
             )
           );
}

/**
 * Compute the minimum and maximum of a set of three int16_t values
 * @param a first value
 * @param b second value
 * @param c third value
 * @return struct containing minimum and maximum value --
 *   this is fairly unusual but it permits the compiler to
 *   optimize by placing in an appropriate pair
 *   of adjacent working registers.
 */
inline static minmax16_t UTIL_MinMax3_S16(int16_t a, int16_t b, int16_t c)
{
    minmax16_t result;
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
    else
    {
        // For MISRA compliance
    }

    if(c < result.min)
    {
        result.min = c;
    }
    else if(c > result.max)
    {
        result.max = c;
    }
    else
    {
        // For MISRA compliance
    }
    return result;
}

/**
 *
 * Computes x*k, limits the result to the [-32768, 32767 range]
 *   This implementation not valid if both x=-32768 and k=-32768
 * 
 * @param x input
 * @param k gain
 * @return x*k, limited to [-32768, 32767]
 */
inline static int16_t UTIL_ScaleAndClip(int16_t x, int16_t k)
{
   int32_t result = (int32_t)x*k;

    if(result >= INT16_MAX)
    {
        result = INT16_MAX;
    }
    else if(result <= INT16_MIN)
    {
        result = INT16_MIN;
    }
    else
    {
        // For MISRA compliance
    }

    return result;
}



/**
 * Computes (state & 1) ? x : -x;
 * @param state input state
 * @param x amplitude
 * @return x if bit 0 of state is set, -x if it is clear
 */
inline static int16_t UTIL_ApplySign(uint16_t state, int16_t x)
{
   asm (
        "; UTIL_ApplySign\n"
        "   btst.wc  %[state], #0\n"   // skip if bit 0 set
        "   bra C, 1f\n"
        "   neg   %[x], %[x]\n"
        "   1:\n"
        : [x]"+r"(x)
        : [state]"r"(state)
    );
    return x;   
}

/**
 * Copy sign from a source value: (state & 0x8000) ? -x : x;
 * @param sign_source source value
 * @param x amplitude
 * @return x if bit 15 of sign_source is clear, -x if it is set
 */
inline static int16_t UTIL_CopySign(int16_t sign_source, int16_t x)
{
    return (sign_source < 0) ? -x: x;
}

/**
 * Sort the minimum, median, and maximum of a set of three int16_t values
 * @param a first value
 * @param b second value
 * @param c third value
 * @return struct containing minimum, median, and maximum value
 */
inline static minmedmax16_t UTIL_Sort3_S16(int16_t a, int16_t b, int16_t c)
{
    int16_t t;
    // if a > b, swap a and b
    if (a > b) { t = a; a = b; b = t; }
    // if a > c, swap a and c
    if (a > c) { t = a; a = c; c = t; }
    // if b > c, swap b and c
    if (b > c) { t = b; b = c; c = t; }

    minmedmax16_t result;
    result.min = a;
    result.med = b;
    result.max = c;
    return result;
}

/**
 * Divides a 32-bit signed integer by a 16-bit signed integer
 *
 * @param num 32-bit signed numerator.
 * @param den 16-bit signed denominator.
 * @return 16-bit signed result of num / den
 */
inline static int16_t UTIL_Div32By16(int32_t num, int16_t den)
{
    return __builtin_div_3216(num, den);
}


#ifdef __cplusplus
}
#endif

#endif /* MCAF_UTIL_DSPIC_32BIT_H */