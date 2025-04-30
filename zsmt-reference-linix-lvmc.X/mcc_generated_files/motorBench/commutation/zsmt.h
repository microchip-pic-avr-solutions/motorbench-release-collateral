/**
 * zsmt.h
 * 
 * Zero speed / maximum torque (ZSMT) estimator
 * 
 * Component: commutation
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

#ifndef __ZSMT_H
#define __ZSMT_H

#include <stdint.h>
#include "motor_control_types.h"
#include "foc_types.h"
#include "units.h"
#include "commutation/common.h"
#include "startup_types.h"
#include "zsmt_types.h"
#include "zsmtlib.h"
#include "parameters/zsmt_params.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initializes state variables on reset.
 * @param pzsmt ZS/MT state variable structure
 * @param pmotor motor parameters
 */
void MCAF_EstimatorZsmtInit(MCAF_ESTIMATOR_ZSMT_T *pzsmt,
        const MCAF_MOTOR_PARAMETERS_T *pmotor);

/**
 * Executes one control step of the ZS/MT estimator.
 * @param pzsmt ZS/MT state variable structure
 * @param pinput Standard algorithm inputs (e.g. stationary-frame voltage and current)
 * @param pmotor Motor parameters
 */
void MCAF_EstimatorZsmtStep(MCAF_ESTIMATOR_ZSMT_T *pzsmt,
                           const MCAF_STANDARD_INPUT_SIGNALS_T *pinput,
                           const MCAF_MOTOR_PARAMETERS_T *pmotor);

/**
 * Disable ZS/MT estimator.
 * @param pzsmt ZS/MT state variable structure
 */
inline static void MCAF_EstimatorZsmtDisable(MCAF_ESTIMATOR_ZSMT_T *pzsmt)
{
    pzsmt->excitation.amplitude       = 0;
    pzsmt->errorGain                  = 0;
    pzsmt->pll.velocityIntegrator.x32 = 0;
    pzsmt->filteredError.state.x32    = 0;    
}

/**
 * Enable ZS/MT estimator.
 * @param pzsmt ZS/MT state variable structure
 */
inline static void MCAF_EstimatorZsmtEnable(MCAF_ESTIMATOR_ZSMT_T *pzsmt)
{
    pzsmt->excitation.amplitude = ZSMT_EXCITATION_VOLTAGE_AMPLITUDE;
    pzsmt->errorGain            = ZSMT_ERROR_GAIN;
}

/**
 * Gets alpha-axis excitation voltage
 * 
 * @param pzsmt ZS/MT state variable structure
 * @return alpha-axis excitation voltage
 */
inline static MCAF_U_VOLTAGE MCAF_EstimatorZsmtExcitationValpha(const MCAF_ESTIMATOR_ZSMT_T *pzsmt)
{
    if (ZSMT_IsStandaloneEstimator())
    {
        return pzsmt->vExcitationAlphabeta.alpha;
    }
    else
    {
        return 0;
    }
}

/**
 * Gets beta-axis excitation voltage
 * 
 * @param pzsmt ZS/MT state variable structure
 * @return beta-axis excitation voltage
 */
inline static MCAF_U_VOLTAGE MCAF_EstimatorZsmtExcitationVbeta(const MCAF_ESTIMATOR_ZSMT_T *pzsmt)
{
    if (ZSMT_IsStandaloneEstimator())
    {
        return pzsmt->vExcitationAlphabeta.beta;
    }
    else
    {
        return 0;
    }
}

/**
 * Gets D-axis excitation voltage
 * 
 * @param pzsmt ZS/MT state variable structure
 * @return D-axis excitation voltage
 */
inline static MCAF_U_VOLTAGE MCAF_EstimatorZsmtExcitationVd(const MCAF_ESTIMATOR_ZSMT_T *pzsmt)
{
    if (ZSMT_IsStandaloneEstimator())
    {
        return 0;
    }
    else
    {
        return pzsmt->excitation.voltage;
    }
}

/**
 * Gets Q-axis excitation voltage
 * 
 * @param pzsmt ZS/MT state variable structure
 * @return Q-axis excitation voltage
 */
inline static MCAF_U_VOLTAGE MCAF_EstimatorZsmtExcitationVq(const MCAF_ESTIMATOR_ZSMT_T *pzsmt)
{
   return 0;
}

/**
 * Determine whether startup delay is requested
 * 
 * @param atpll state
 * @param startupStatus startup status
 * @return whether a startup delay is requested
 */
inline static bool MCAF_EstimatorZsmtStartupDelayRequested(MCAF_ESTIMATOR_ZSMT_T *pzsmt, MCAF_STARTUP_STATUS_T startupStatus)
{
    return pzsmt->delayCounter > 0;
}

/**
 * Initializes state variables prior to starting motor.
 * (Delegates to precompiled implementation.)
 * 
 * @param pzsmt ZS/MT state variable structure
 */
inline static void MCAF_EstimatorZsmtStartupInit(MCAF_ESTIMATOR_ZSMT_T *pzsmt) {
    ZSMTLIB_EstimatorZsmtStartupInit(pzsmt);
}

#ifdef __cplusplus
}
#endif

#endif /* __ZSMT_H */