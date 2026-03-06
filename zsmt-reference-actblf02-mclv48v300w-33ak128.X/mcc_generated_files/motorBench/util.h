/**
 * util.h common for all supported architectures
 * 
 * Utility routines and types for computation
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

#ifndef MCAF_UTIL_H 
#define MCAF_UTIL_H 

#include <stdint.h>
#include <stdbool.h>

#include "util_types.h"

#if defined(__dsPIC33A__)
#include "util_dspic_32bit.h"
#elif defined(__dsPIC30__) || defined(__dsPIC33C__) || defined(__dsPIC33E__)
#include "util_dspic_16bit.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Limit the slew rate of an output signal to within positive and negative limits.
 * This is intended to be called at a constant rate delta_t, in which case
 * the slew rate limits are equal to limit_pos/delta_t and limit_neg/delta_t.
 * 
 * @param input raw incoming signal
 * @param previousOutput previous output signal
 * @param limitPos maximum positive slew rate
 * @param limitNeg maximum negative slew rate
 * @return updated output signal
 */
inline static int16_t UTIL_LimitSlewRate(int16_t input, int16_t previousOutput, 
        int16_t limitPos, int16_t limitNeg)
{
    /* Note: use 32-bit difference. The difference of a pair of int16_t values
     * is technically a 17-bit integer; contrast the following two cases:
     *   (-10000) - (30000) = -40000
     *   ( 28536) - ( 3000) =  25536
     * If cast to an int16_t, both evaluate to 25536, but this is 
     * clearly an overflow error in the first case.
     */
    const int32_t delta_in = (int32_t)input - previousOutput;
    int16_t output = previousOutput;
    if (delta_in > limitPos)
    {
        output += limitPos;
    }
    else if (delta_in < -limitNeg)
    {
        output -= limitNeg;
    }
    else
    {
        output += (int16_t)delta_in;
    }
    return output;
}

/**
 * Limit the slew rate of an output signal to within positive and negative limits.
 * This is intended to be called at a constant rate delta_t, in which case
 * the slew rate limits are equal to limit/delta_t and limit/delta_t.
 * 
 * @param input raw incoming signal
 * @param previousOutput previous output signal
 * @param limit maximum slew rate
 * @return updated output signal
 */
inline static int16_t UTIL_LimitSlewRateSymmetrical(int16_t input, int16_t previousOutput, 
        int16_t limit)
{
    return UTIL_LimitSlewRate(input, previousOutput, limit, limit);
}

/**
 * Helper function to multiply two Q15 quantities and return a Q15 result.
 * Note that this does NOT correctly handle the overflow situation
 * where -1.0*-1.0 -> -1.0, which needs to be special-cased.
 * 
 * @param a first input in Q15 format
 * @param b second input in Q15 format
 * @return a*b in Q15 format
 */
inline static int16_t UTIL_MulQ15(int16_t a, int16_t b)
{
    return UTIL_Shr15(UTIL_mulss(a,b));
}

/**
 * Function to calculate square of signed number.
 * Please note that use of this function assumes there will be no overflow.
 * The input value -32768 is invalid and will result
 * in an overflow, with the output value -32768. All other inputs are valid.
 *
 * @param x input in Q15 format
 * @return x*x in Q15 format
 */
inline static int16_t UTIL_SignedSqrNoOverflow(int16_t x) 
{
    return UTIL_MulQ15(x, x);
}


/**
 * Limit an unsigned 16-bit value to a specified minimum
 * 
 * @param x input value
 * @param xmin minimum output value
 * @return the input, limited at a minimum to xmin
 */
inline static uint16_t UTIL_LimitMinimumU16(uint16_t x, uint16_t xmin)
{
    return (x < xmin) ? xmin : x;
}

/**
 * Limit a signed 16-bit value to a specified minimum
 * 
 * @param x input value
 * @param xmin minimum output value
 * @return the input, limited at a minimum to xmin
 */
inline static int16_t UTIL_LimitMinimumS16(int16_t x, int16_t xmin)
{
    return (x < xmin) ? xmin : x;
}

/**
 * Limit an unsigned 16-bit value to a specified maximum
 * 
 * @param x input value
 * @param xmax maximum output value
 * @return the input, limited at a maximum to xmax
 */
inline static uint16_t UTIL_LimitMaximumU16(uint16_t x, uint16_t xmax)
{
    return (x > xmax) ? xmax : x;
}

/**
 * Limit a signed 16-bit value to a specified maximum
 * 
 * @param x input value
 * @param xmax maximum output value
 * @return the input, limited at a maximum to xmax
 */
inline static int16_t UTIL_LimitMaximumS16(int16_t x, int16_t xmax)
{
    return (x > xmax) ? xmax : x;
}

/** * Limits the input between a minimum and a maximum */
inline static int16_t UTIL_LimitS16(int16_t x, int16_t min, int16_t max)
{
    return (x > max ) ? max : ((x < min) ? min : x);
}

/**
 * Saturates a signed 32-bit value to a 16-bit positive/negative bound.
 * 
 * @param x signed 32-bit input to saturate
 * @param xlim saturation limit
 * @return input x saturated to xlim
 */
inline static int16_t UTIL_LimitS32ToS16(int32_t x, int16_t xlim)
{
    if (x >= xlim)
    {
        return xlim;
    }
    if (x <= -xlim)
    {
        return -xlim;
    }
    return (int16_t)x;
}

/**
 * Clears bits in uint16_t that are defined by mask
 * 
 * @param oldFlags input bits
 * @param mask bits to clear
 * @return input with mask cleared
 */
inline static uint16_t UTIL_ClearBits(uint16_t oldFlags, uint16_t mask)
{
  return oldFlags & ~mask;
}

/**
 * Sets bits in uint16_t that are defined by mask
 * 
 * @param oldFlags input bits
 * @param mask bits to set
 * @return input with mask set
 */
inline static uint16_t UTIL_SetBits(uint16_t oldFlags, uint16_t mask)
{
  return oldFlags | mask;
}

/**
 * Copies bits in uint16_t that are defined by mask:
 * clears if "on" is false, sets if "on" is true
 * 
 * @param oldFlags input bits
 * @param mask bits to set or clear
 * @param on true if setting, false if clearing
 * @return input with mask set or clear
 */
inline static uint16_t UTIL_CopyBits(uint16_t oldFlags, uint16_t mask, bool on)    
{
    return (on) ? UTIL_SetBits(oldFlags, mask)
                : UTIL_ClearBits(oldFlags, mask);
}

/**
 * Construct an unsigned 32-bit integer from two 16-bit integers.
 * @param xlo low word (unsigned 16-bit)
 * @param xhi high word (unsigned 16-bit)
 * @return xhi << 16 | xlo
 */
inline static uint32_t UTIL_PairU16(uint16_t xlo, uint16_t xhi)
{
    ux1632_t result;
    result.x16.lo = xlo;
    result.x16.hi = xhi;
    return result.x32;
}

/**
 * Construct a signed 32-bit integer from two 16-bit integers.
 * @param xlo low word (unsigned 16-bit)
 * @param xhi high word (signed 16-bit)
 * @return xhi << 16 | xlo
 */
inline static int32_t UTIL_PairS16(uint16_t xlo, int16_t xhi)
{
    sx1632_t result;
    result.x16.lo = xlo;
    result.x16.hi = xhi;
    return result.x32;
}

/**
 * Right shift an unsigned 32-bit value by some runtime value N with N <= 16,
 * returning an unsigned 32-bit result. 
 * 
 * @param x input
 * @param N number of right shifts (N <= 16)
 * @return x >> N
 */
inline static uint32_t UTIL_ShrU32N16(uint32_t x, uint16_t N)
{
    const uint16_t Ncomp = 16 - N;
    uint16_t xlo = x;
    uint16_t xhi = x >> 16;
    
    xlo >>= N;
    xlo |= xhi << Ncomp;
    xhi >>= N;
    
    return UTIL_PairU16(xlo, xhi);
}

/**
 * Right shift an unsigned 32-bit value by some runtime value N, returning an
 * unsigned 32-bit result.
 * 
 * @param x input
 * @param N number of right shifts
 * @return x >> N
 */
inline static uint32_t UTIL_ShrU32N(uint32_t x, uint16_t N)
{
    const uint16_t Ncomp = 16 - N;
    uint16_t xlo = x;
    uint16_t xhi = x >> 16;
    
    if ((int16_t)Ncomp < 0)
    {
        xlo = xhi >> (-Ncomp);
        xhi = 0;
    }
    else
    {
        xlo >>= N;
        xlo |= xhi << Ncomp;
        xhi >>= N;
    }
    
    return UTIL_PairU16(xlo, xhi);
}

/**
 * Right shift a signed 32-bit value by some runtime value N with N <= 16,
 * returning a signed 32-bit result.
 * 
 * @param x input
 * @param N number of right shifts (0 <= N <= 16)
 * @return x >> N
 */
inline static int32_t UTIL_ShrS32N16(int32_t x, uint16_t N)
{
    const uint16_t Ncomp = 16 - N;
    uint16_t xlo = x;
    int16_t xhi = x >> 16;
    
    xlo >>= N;
    xlo |= xhi << Ncomp;
    xhi >>= N;
    
    return UTIL_PairS16(xlo, xhi);
}

/**
 * Right shift a signed 32-bit value by some runtime value N, returning a
 * signed 32-bit result.
 * 
 * @param x input
 * @param N number of right shifts (N >= 0)
 * @return x >> N
 */
inline static int32_t UTIL_ShrS32N(int32_t x, uint16_t N)
{
    const uint16_t Ncomp = 16 - N;
    uint16_t xlo = x;
    int16_t xhi = x >> 16;
    
    if ((int16_t)Ncomp < 0)
    {
        xlo = xhi >> (-Ncomp);
        xhi >>= 15;
    }
    else
    {
        xlo >>= N;
        xlo |= xhi << Ncomp;
        xhi >>= N;
    }
    
    return UTIL_PairS16(xlo, xhi);
}

/**
 * Returns a directed version of (a <= b). If dir is negative, we reverse the
 * sign and compute a >= b instead.
 * 
 * @param a first operand
 * @param b second operand
 * @param dir direction
 * @return a <= b if dir is nonnegative else a >= b
 */
inline static bool UTIL_DirectedLessThanEqual(int16_t a, int16_t b, int16_t dir)
{
    return (dir >= 0)
         ? (a <= b)
         : (a >= b);
}

/**
 * Computes the sign of a nonzero value:
 * negative numbers return -1, zero and positive numbers return +1
 */
inline static int16_t UTIL_SignFromHighBit(int16_t x)
{
    return (x >> 15) | 1;
}







/* ----------------------------------------------------------------------------
 * The following functions are comparable to or slightly faster than
 * computing (abs16(x) < limit)
 * ----------------------------------------------------------------------------
 */

/**
 * Returns whether a and b are both negative or both nonnegative
 * 
 * @param a
 * @param b
 * @return true if a and b are both negative, or both nonnegative.
 */
inline static bool UTIL_BothNegativeOrNonnegative(int16_t a, int16_t b)
{
    return (a^b) >= 0;
}

/**
 * Computes whether abs(x) < limit
 * @param x input
 * @param limit limit (must be nonnegative)
 * @return whether abs(x) < limit
 */
inline static bool UTIL_AbsLessThan(int16_t x, int16_t limit)
{
    return (x > -limit) && (x < limit);
}

/**
 * Computes whether abs(x) <= limit
 * @param x input
 * @param limit limit (must be nonnegative)
 * @return whether abs(x) <= limit
 */
inline static bool UTIL_AbsLessThanEqual(int16_t x, int16_t limit)
{
    return (x >= -limit) && (x <= limit);
}

/**
 * Computes whether abs(x) > limit
 * @param x input
 * @param limit limit (must be nonnegative)
 * @return whether abs(x) > limit
 */
inline static bool UTIL_AbsGreaterThan(int16_t x, int16_t limit)
{
    return (x < -limit) || (x > limit);
}

/**
 * Computes whether abs(x) >= limit
 * @param x input
 * @param limit limit (must be nonnegative)
 * @return whether abs(x) >= limit
 */
inline static bool UTIL_AbsGreaterThanEqual(int16_t x, int16_t limit)
{
    return (x <= -limit) || (x >= limit);
}



/**
 * Computes saturated shift-right with an U16 result.
 * If (x >> q) lies within the range of uint16_t values, return it,
 * otherwise return 0xFFFF.
 * 
 * @param x input to shift right
 * @param q number of bits to shift right
 * @return saturated right-shifted result
 */
inline static uint16_t UTIL_SatShrU16(uint32_t x, uint16_t q)
{
    uint16_t hi_word = x >> 16;
    if ((q < 16) && (hi_word >= (uint16_t)(1 << q)))
    {
        return 0xFFFF;
    }
    else
    {
        return x >> q;
    }
}

/**
 * Computes saturated shift-right with an S16 result.
 * If (x >> q) lies within the range of int16_t values, return it,
 * otherwise return the appropriately saturated result (0x8000 if x is negative,
 * else 0x7fff).
 */
inline static int16_t UTIL_SatShrS16(int32_t x, uint16_t q)
{
    const int32_t y = x >> q;    
    const int16_t ylo = y;
    if (q < 16)       // the only chance of overflow is for shift counts < 16
    {        
        const int16_t yhi = y >> 16;
        /* unused bits that will be thrown away
         * These must match the sign of y: either all zero or all one
         */
        const int16_t sign_ylo = ylo >> 15; // -1 if ylo is negative, otherwise 0
        if (yhi != sign_ylo)
        {
            // Uh oh, we had an overflow and need to saturate!
            const int16_t xhi = x >> 16;
            const int16_t sign_x = xhi >> 15;
            return sign_x ^ 0x7fff;
        }
    }
    return ylo;
}






/**
 * Computes  shift-left with an S16 result.
 * If the shift count(q) is positive, the input x << q,
 * else if the shift count(q) is negative, the input x >> (-q)
 * This should only be done if the shift count is a compile-time constant
 * otherwise it takes significant run time
 */
inline static int16_t UTIL_BidirectionalShiftLeft(int16_t x, int16_t q)
{
    if (q < 0)
    {
       return x >> (-q);
    }
    else
    {
       return x << q;
    }   
}

/**
 * Function to calculate the square of signed Q15 values.
 * We use UTIL_Abs16Approx() to fixup the -32768 value efficiently
 * without branching: this is a 2-instruction hit that yields +32767.
 *
 * @param input in Q15 format
 * @return square of the input, in Q15 format
 */
inline static int16_t UTIL_SignedSqr(int16_t x)
{
    return UTIL_Abs16Approx(UTIL_SignedSqrNoOverflow(x));
}

/**
 * Repeat NOP (n+1) times
 * @param n argument to the REPEAT instruction
 */
inline static void UTIL_RepeatNop(uint16_t n)
{
    #if defined(__XC_DSC_VERSION__) && (__XC_DSC_VERSION__ >= 3010)
        __builtin_repeat_nop(n);
    #else
        asm volatile (
            " ;UTIL_RepeatNop\n"
            "   repeat %[n]\n"
            "   nop"
            :: [n]"r"(n) : "memory"
        );
    #endif
}


/**
 * Executes a NOP
 */
inline static void UTIL_Nop(void)
{
    return __builtin_nop();
}

/**
 * Helper function to multiply two quantities and shift right by 16.
 * (It could be two Q16 numbers with a Q16 result, 
 * could be a Q16 and a Q15 number with a Q15 result.)
 * 
 * @param a first input (unsigned)
 * @param b second input
 * @return (a*b)>>16
 */
inline static int16_t UTIL_MulUSQ16(uint16_t a, int16_t b)
{
    return UTIL_mulus(a,b) >> 16;
}

/**
 * Helper function to multiply two unsigned 16-bit quantities and 
 * shift right by 16.
 * (It could be two Q16 numbers with a Q16 result, 
 * could be a Q16 and a Q15 number with a Q15 result.)
 * 
 * @param a first input (unsigned 16-bit)
 * @param b second input (unsigned 16-bit)
 * @return (a*b)>>16 (unsigned 16-bit)
 */
inline static uint16_t UTIL_MulUUQ16(uint16_t a, uint16_t b)
{
    return UTIL_muluu(a,b) >> 16;
}

/**
 * Helper function to multiply two quantities and shift right by 14.
 * @param a first input
 * @param b second input
 * @return (a*b)>>14
 */
inline static int16_t UTIL_MulQ14(int16_t a, int16_t b)
{
    return UTIL_mulss(a,b) >> 14;
}

/**
 * Helper function to multiply two quantities and shift right by 16.
 * (It could be two Q16 numbers with a Q16 result, 
 * could be a Q16 and a Q15 number with a Q15 result.)
 * 
 * @param a first input
 * @param b second input
 * @return (a*b)>>16
 */
inline static int16_t UTIL_MulQ16(int16_t a, int16_t b)
{
    return UTIL_mulss(a,b) >> 16;
}

/**
 * Helper function to find the first one-bit from the left for 16-bit value.
 * 
 * @param x input (signed 16-bit)
 * @return first one-bit from the left for 16-bit input.
 */
inline static uint16_t UTIL_ff1l_16(int16_t x)
{
#ifdef __XC_DSC__
    return __builtin_ff1l_16(x);
#else
    return __builtin_ff1l(x);
#endif
}

/**
 * Disable global interrupts
 */
inline static void UTIL_DisableGlobalInterrupts(void)
{
    __builtin_disable_interrupts();
}


#ifdef __cplusplus
}
#endif

#endif /* MCAF_UTIL_H */
