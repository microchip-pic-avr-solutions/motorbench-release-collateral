/**
 * timing.h
 * 
 * Utility routines for timing
 *
 * Component: miscellaneous
 */

/* *********************************************************************
 *
 * Motor Control Application Framework
 * R8/RC38 (commit 128946, build on 2025 Apr 09)
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

#ifndef __TIMING_H
#define __TIMING_H

#include <stdint.h>
#include <stdbool.h>
#include "util.h"
#include "parameters/timing_params.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Blocking delay for ns nsec.
 * Exact delay will have granularity of repeat NOP (n+1) times
 * The value of ns must be fixed at compile-time, otherwise
 * we will incur the cost of calculation.
 * 
 * @param ns nanoseconds to delay
 */
inline static void MCAF_DelayNanoseconds(uint16_t ns)
{
    uint16_t nop_count = (((uint32_t)ns) * MCAF_CYCLES_PER_NANOSECOND_Q16) >> 16;
    UTIL_RepeatNop(nop_count - 1);
}

#ifdef __cplusplus
}
#endif

#endif /* __TIMING_H */
