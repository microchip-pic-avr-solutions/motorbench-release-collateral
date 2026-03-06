/**
 * util_dspic_16bit.h
 * 
 * Architecture-specific utility routines for 16-bit dsPIC devices
 * 
 * Component: miscellaneous
 */

/* *********************************************************************
 *
 * Motor Control Application Framework
 * R9/RC31 (commit 132024, build on 2026 Feb 13)
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

#ifndef MCAF_UTIL_DSPIC_16BIT_H
#define MCAF_UTIL_DSPIC_16BIT_H

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
    return (int16_t)((x << 1) >> 16);
    /* use << 1 >> 16, rather than >> 15, because it helps the XC16 compiler
     * produce more optimal code; right now there are no specializations
     * for >> 15
     */
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
    return __builtin_mulss(a,b);
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
    return __builtin_mulus(a,b);
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
    return __builtin_mulsu(a,b);
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
    return __builtin_muluu(a,b);
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
        "   btsc %[x], #15\n"
        "   neg  %[x], %[x]\n"
        "   btsc %[x], #15\n"
        "   com  %[x], %[x]\n"
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
        "   asr %[y], #15, %[s]\n"  // s = 0xFFFF if y is negative, 0 otherwise
        "   btg %[s], #15\n"        // s = 0x7FFF if y is negative, 0x8000 otherwise
        "   add %[x], %[y], %[x]\n" // x = x+y
        "   btsc SR, #2\n"          // overflow in OV = SR<2>
        "   com %[s], %[x]\n"       // x = ~s if overflow bit was set, skip otherwise
        : [x]"+r"(x),
          [s]"=&r"(saturated_sum)
        : [y]"r"(y)
    );
    return x;
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
    /* Saturation can only occur if x and y have opposite signs.
     *   (we can lump zero with positive values for arithmetic efficiency
     *    so we can just look at the high bit)
     * If x is nonnegative and y is negative and we get overflow,
     *    x-y is positive and should be limited to 32767
     * If x is negative and y is nonnegative and we get overflow
     *    x-y is negative and should be limited to -32768
     * In either case, if overflow occurs, 
     *    we can use either x or y's most significant bit to decide the result
     */

    int16_t saturated_difference;
    asm volatile (
        "   ;UTIL_SatSubS16\n"
        "   asr %[y], #15, %[s]\n"  // s = 0xFFFF if y is negative, 0 otherwise
        "   btg %[s], #15\n"        // s = 0x7FFF if y is negative, 0x8000 otherwise
        "   sub %[x], %[y], %[x]\n" // x = x-y
        "   btsc SR, #2\n"          // overflow in OV = SR<2>
        "   mov %[s], %[x]\n"       // x = s if overflow was set
        : [x]"+r"(x),
          [s]"=&r"(saturated_difference)
        : [y]"r"(y)
    );
    return x;
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
    asm volatile (
        "   ;UTIL_Abs16Approx\n"
        "   btsc %[x], #15\n"
        "   com  %[x], %[x]\n"
        : [x]"+r"(x)
    );
    return x;
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
    return __builtin_divf(num, den);
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
 * 
 * @param num dividend with Qn binary point
 * @param den divisor with Qd binary point
 * @return quotient = num/den with Q(n-d+15) binary point
 */
inline static int16_t UTIL_DivQ15SatPos(int16_t num, int16_t den)
{
    int16_t quotient;
    int16_t remainder;  // unused, but part of DIVF operation
    
    asm (
        "    ;UTIL_DivQ15SatPos\n"
        "    repeat  #__TARGET_DIVIDE_CYCLES\n"
        "    divf    %[num],%[den]\n"
        "    btsc    SR,#2\n"            // OV = bit 2
        "    mov     #0x7fff, %[quotient]"
        : [quotient]"=a"(quotient), [remainder]"=&b"(remainder)
        : [num]"r"(num), [den]"e"(den)   // den restricted to R2-R14 for DIVF
        : "cc", "RCOUNT"
    );
    return quotient;
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
        "    btg %[x], #15\n"
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
        "    add %[a],%[b],%[c]\n"
        "    rrc %[c],%[c]"
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
    return (int16_t)((((int32_t)a) + b) >> 1);
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
    /* Sort a,b,c */
    asm (
        "    ;UTIL_MinMax3_S16\n"
        "    cpslt   %[a], %[b]\n"
        "    exch    %[a], %[b]\n"
        "    cpslt   %[a], %[c]\n"
        "    exch    %[a], %[c]\n"
        "    cpslt   %[b], %[c]\n"
        "    exch    %[b], %[c]\n"
        : [a]"+r"(a),
          [b]"+r"(b),
          [c]"+r"(c)
    );
    /* Now a <= b <= c */

    minmax16_t result;
    result.min = a;
    result.max = c;
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
    const int16_t intmax = INT16_MAX;

    int16_t m; // most significant bits (30:15) of product
    int16_t s; // sign of m: -1 for negative m, 0 for nonnegative m

    // we will compute:
    // sat = intmax - s:  -32768 for negative m, +32767 for positive m
    // if m is either 0 or -1, then m == s

    asm volatile (
        ";UTIL_ScaleAndClip\n"
        "   rlc     %[result], %[m]\n"
        "   rlc     %d[result], %[m]\n"
        "   asr     %[m], #15, %[s]\n"
        "   cpseq   %[m], %[s]\n"
        "   sub     %[intmax], %[s], %[result]\n"  // set result = sat
        : [result]"+r"(result), [m]"=&r"(m), [s]"=&r"(s)
        : [intmax]"r"(intmax)
    );
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
        "   btss  %[state], #0\n"   // skip if bit 0 set
        "   neg   %[x], %[x]\n"
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
    asm (
        "; UTIL_CopySign\n"
        "   btsc  %[src], #15\n"   // skip if bit 15 is clear
        "   neg   %[x], %[x]\n"
        : [x]"+r"(x)
        : [src]"r"(sign_source)
    );
    return x;   
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
    /* Sort a,b,c */
    asm (
        "    ;UTIL_Sort3_S16\n"
        "    cpslt   %[a], %[b]\n"
        "    exch    %[a], %[b]\n"
        "    cpslt   %[a], %[c]\n"
        "    exch    %[a], %[c]\n"
        "    cpslt   %[b], %[c]\n"
        "    exch    %[b], %[c]\n"
        : [a]"+r"(a),
          [b]"+r"(b),
          [c]"+r"(c)
    );
    /* Now a <= b <= c */

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
 * @return 16-bit signed result of num / den.
 */
inline static int16_t UTIL_Div32By16(int32_t num, int16_t den)
{
    return __builtin_divsd(num, den);
}

#ifdef __cplusplus
}
#endif

#endif /* MCAF_UTIL_DSPIC_16BIT_H */
