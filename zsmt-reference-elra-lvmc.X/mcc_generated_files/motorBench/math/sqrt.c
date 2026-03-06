/**
 * sqrt.c
 * 
 * Q15 square root
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

#include <stdint.h>
#include "sqrt.h"
#include "util.h"

static const int16_t sqrt_q15_taylor_coef[8] = {0x4000, 0xF000, 0x0800, 0xFB00, 0x0380, 0xFD60, 0x0210, 0xFE53};

int16_t MCAF_SqrtQ15Taylor(int16_t x)
{
    // Input validation: polynomial evaluation is valid only for x > 0
    if (x <= 0)
    {
        return 0;
    }

    const int16_t sqrt_0_5 = 0x5a82;

    // Normalization (equivalent to ff1l and shifting)
    uint16_t bit_pos = UTIL_ff1l_16(x);
    int16_t shift = bit_pos - 2;
    int16_t norm = x << shift;

    int16_t w4 = norm - 0x8000;
    int16_t w5 = w4 << 1;
    int32_t accum = 0;

    for (int i = 0; i < 8; i++)
    {
        accum += UTIL_mulss(sqrt_q15_taylor_coef[i], w4);
        w4 = UTIL_MulQ16(w4, w5);
    }

    // Denormalization and adjust the result
    accum = (accum >> 15) + 0x8000;
    int16_t rshift = shift >> 1;
    accum >>= rshift;

    // If the shift was odd, apply correction factor (~sqrt(0.5) in Q15 format)
    if (shift & 1)
    {
        accum = UTIL_MulQ15((int16_t)accum, sqrt_0_5);
    }
    
    return accum;
}
