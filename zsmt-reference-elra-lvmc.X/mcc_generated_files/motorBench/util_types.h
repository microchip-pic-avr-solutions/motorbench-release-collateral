/**
 * util_types.h
 *
 * Type and union definitions for utility routines
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

#ifndef MCAF_UTIL_TYPES_H
#define MCAF_UTIL_TYPES_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Unions for aliasing 32-bit and pairs of 16-bit variables */

/** Unsigned 16/32 bit alias union */
typedef union tagUX1632_t
{
    struct
    {
        uint16_t lo;    /** lower 16 bits */
        uint16_t hi;    /** upper 16 bits */
    } x16;              /** access as 16-bit values */
    uint32_t x32;       /** access as 32-bit values */
} ux1632_t;

/** Signed 16/32 bit alias union */
typedef union tagSX1632_t
{
    struct
    {
        uint16_t lo;    /** lower 16 bits */
        int16_t  hi;    /** upper 16 bits */ 
    } x16;              /** access as 16-bit values */
    int32_t x32;        /** access as 32-bit values */ 
} sx1632_t;

typedef struct
{
    int16_t min;
    int16_t max;
} minmax16_t;

typedef struct
{
    int16_t min;
    int16_t med;
    int16_t max;
} minmedmax16_t;

#ifdef __cplusplus
}
#endif

#endif /* MCAF_UTIL_TYPES_H */
