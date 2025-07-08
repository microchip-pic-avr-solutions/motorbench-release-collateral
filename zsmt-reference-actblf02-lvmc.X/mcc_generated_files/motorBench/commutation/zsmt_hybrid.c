/**
 * zsmt_hybrid.c
 * 
 * Binary hard-switch hybrid estimator ('Minotaur')
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

#include <stdint.h>
#include <stdbool.h>

#include "util.h"
#include "units.h"
#include "parameters/operating_params.h"
#include "parameters/motor_params.h"
#include "parameters/zsmt_hybrid_params.h"
#include "commutation/common.h"
#include "zsmt_hybrid.h"

inline static MCAF_U_ANGLE_ELEC computeAngleDifference(MCAF_ESTIMATOR_ZSMT_HYBRID_T *pstate)
{
    const MCAF_U_ANGLE_ELEC angleDifference = pstate->pbemf_out->thetaElectrical - pstate->pzsmt_out->thetaElectrical;
    pstate->thetaDifference = angleDifference;
    return UTIL_Abs16Approx(angleDifference);
}

void MCAF_EstimatorZsmtHybridStep(MCAF_ESTIMATOR_ZSMT_HYBRID_T *pstate, 
                           const MCAF_STANDARD_INPUT_SIGNALS_T *pinput,
                           const MCAF_MOTOR_PARAMETERS_T *pmotor)
{
    const MCAF_ZSMT_HYBRID_STATE current_state = pstate->state;
    MCAF_ZSMT_HYBRID_STATE next_state = current_state;
    const MCAF_U_VELOCITY_ELEC speed = UTIL_Abs16Approx(pstate->pout->omegaElectrical);
    bool delayComplete;
    if (pstate->delayCounter > 0)
    {
        --pstate->delayCounter;
        delayComplete = false;
    }
    else
    {
        delayComplete = true;
    }
    
    switch (current_state)
    {
        default:
        case MCAF_ZSMT_HYBRID_SLOW:
        {
            // Check ZS/MT convergence
            const MCAF_U_ANGLE_ELEC thetaDifferenceAbs = computeAngleDifference(pstate);
            if (thetaDifferenceAbs > pstate->angleConvergence.threshold)
            {
                // Angle difference too high! Restart counter.
                pstate->delayCounter = pstate->angleConvergence.duration;
            }
            else if (delayComplete && (speed > pstate->speedThreshold.fast))
            {
                // Ready to switch to secondary estimator!
                next_state = MCAF_ZSMT_HYBRID_FAST;
                pstate->flags |= MCAF_ZSMT_HYBRID_DISENGAGE_ZSMT;
                pstate->pout = pstate->pbemf_out;
            }
            
            if (speed < pstate->speedThreshold.slow)
            {
                pstate->flags |= MCAF_ZSMT_HYBRID_FORCE_BEMF_STATE;
            }
            break;
        }
        case MCAF_ZSMT_HYBRID_TRANSITION:
        {
            // Check ZS/MT convergence
            const MCAF_U_ANGLE_ELEC thetaDifferenceAbs = computeAngleDifference(pstate);

            if (speed > pstate->speedThreshold.fast)
            {
                next_state = MCAF_ZSMT_HYBRID_FAST;
                pstate->flags |= MCAF_ZSMT_HYBRID_DISENGAGE_ZSMT;
            }
            else if (delayComplete && (speed < pstate->speedThreshold.slow))
            {
                if (thetaDifferenceAbs <= pstate->angleConvergence.threshold)
                {
                    // Ready to switch back to ZS/MT!
                    next_state = MCAF_ZSMT_HYBRID_SLOW;
                    pstate->pout = pstate->pzsmt_out;
                }
            }
            break;
        }
        case MCAF_ZSMT_HYBRID_FAST:
        {
            // Update ZS/MT angle difference for debugging purpose
            pstate->thetaDifference = 0;

            if (speed < pstate->speedThreshold.transition)
            {
                // Begin transitioning back to ZS/MT, first by re-engaging it
                next_state = MCAF_ZSMT_HYBRID_TRANSITION;
                pstate->flags |= MCAF_ZSMT_HYBRID_ENGAGE_ZSMT;
                pstate->delayCounter = pstate->angleConvergence.duration;
            }
            break;
        }
    }
    pstate->state = next_state;
}

inline void MCAF_EstimatorZsmtHybridStartupInit(MCAF_ESTIMATOR_ZSMT_HYBRID_T *pstate)
{
    pstate->flags &= MCAF_ZSMT_HYBRID_STARTUP_MASK;
    pstate->flags |= MCAF_ZSMT_HYBRID_ENGAGE_ZSMT;

    pstate->state = MCAF_ZSMT_HYBRID_SLOW;
    pstate->delayCounter = pstate->angleConvergence.duration;
}

void MCAF_EstimatorZsmtHybridInit(MCAF_ESTIMATOR_ZSMT_HYBRID_T *pstate, 
        const MCAF_MOTOR_PARAMETERS_T *pmotor)
{
    pstate->flags = 0;
    pstate->angleConvergence.duration  = MCAF_ZSMT_HYBRID_ANGLE_CONVERGE_DURATION; 
    pstate->angleConvergence.threshold = MCAF_ZSMT_HYBRID_ANGLE_CONVERGE_THRESHOLD;
    
    pstate->speedThreshold.slow = MCAF_ZSMT_HYBRID_VELOCITY_THRESHOLD_SLOW;
    pstate->speedThreshold.transition = MCAF_ZSMT_HYBRID_VELOCITY_THRESHOLD_TRANSITION;
    pstate->speedThreshold.fast = MCAF_ZSMT_HYBRID_VELOCITY_THRESHOLD_FAST;
    
    MCAF_EstimatorZsmtHybridStartupInit(pstate);
}

void MCAF_EstimatorZsmtHybridSetupOutputDependencies(MCAF_ESTIMATOR_ZSMT_HYBRID_T *pstate,
                                                   const MCAF_ESTIMATOR_OUTPUTS_T *pzsmt_out,
                                                   const MCAF_ESTIMATOR_OUTPUTS_T *pbemf_out)
{
    pstate->pzsmt_out = pzsmt_out;
    pstate->pbemf_out = pbemf_out;
    pstate->pout = pzsmt_out;
}
