/**
 * commutation_types.h
 * 
 * Type definitions for commutation
 *
 * Component: commutation
 */ /*
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
 *
 ******************************************************************************/

#ifndef __COMMUTATION_TYPES_H
#define __COMMUTATION_TYPES_H

#include <stdint.h>
#include "units.h"
#include "commutation/common.h"
#include "commutation/zsmt.h"
#include "commutation/pll.h"
#include "commutation/zsmt_hybrid.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Relative angle used for comparing estimator electrical angles
 */
typedef struct tagMCAF_RELATIVE_ANGLE_T
{
} MCAF_RELATIVE_ANGLE_T;

/**
 * State estimator data for position/velocity
 */
typedef struct tagMCAF_ESTIMATOR_T
{
    MCAF_ESTIMATOR_ZSMT_T zsmt;  /** Zero-speed maximum torque */
    MCAF_ESTIMATOR_PLL_T pll;  /** sensorless, phase-locked loop (AN1292 PLL) */
    MCAF_ESTIMATOR_ZSMT_HYBRID_T zsmtHybrid;  /** Binary hard-switch hybrid estimator ('Minotaur') */
    MCAF_U_ANGLE_ELEC     theta;                   /** estimated rotor angle (electrical) */
    MCAF_U_VELOCITY_ELEC  omega;                   /** estimated rotor velocity (electrical) */
    MCAF_RELATIVE_ANGLE_T thetaRelativeTo;
} MCAF_ESTIMATOR_T;

inline static bool MCAF_EstimatorZsmtIsActive(const MCAF_ESTIMATOR_T* pestimator) { return false; }
inline static bool MCAF_EstimatorPllIsActive(const MCAF_ESTIMATOR_T* pestimator) { return false; }
inline static bool MCAF_EstimatorZsmtHybridIsActive(const MCAF_ESTIMATOR_T* pestimator) { return true; }

#ifdef __cplusplus
}
#endif

#endif  /* __COMMUTATION_TYPES_H */
