/**
 * zsmt_hybrid_interaction.h
 * 
 * Binary hard-switch hybrid estimator ('Minotaur')
 *
 * Necessary coupling / interaction with other modules is isolated here.
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

#ifndef __ZSMT_HYBRID_INTERACTION_H
#define __ZSMT_HYBRID_INTERACTION_H

#include <stdint.h>
#include "motor_control_types.h"
#include "foc_types.h"
#include "units.h"
#include "commutation/common.h"
#include "system_state.h"
#include "zsmt_hybrid.h"
#include "parameters/zsmt_params.h"
#include "parameters/foc_params.h"
#include "parameters/zsmt_hybrid_params.h"

#include "commutation/zsmt.h"

#ifdef __cplusplus
extern "C" {
#endif

inline static void MCAF_EstimatorZsmtHybridEngageZSMT(MCAF_ESTIMATOR_ZSMT_HYBRID_T *pstate,
                                                    MCAF_MOTOR_DATA *pmotor)
{
    MCAF_EstimatorZsmtEnable(&pmotor->estimator.zsmt);

    // Reinitialize ZSMT PLL with angle/velocity from back-emf
    MCAF_EstimatorZsmtSetPllState(&pmotor->estimator.zsmt,
            pstate->pbemf_out->thetaElectrical,
            pstate->pbemf_out->omegaElectrical);
    pmotor->idqCtrlOutLimit.d = ZSMT_CURRENT_CTRL_D_OUT_LIMIT;
    pmotor->idqCtrlOutLimit.q = ZSMT_CURRENT_CTRL_Q_OUT_LIMIT;
}

inline static void MCAF_EstimatorZsmtHybridDisengageZSMT(MCAF_ESTIMATOR_ZSMT_HYBRID_T *pstate,
                                                       MCAF_MOTOR_DATA *pmotor)
{
    MCAF_EstimatorZsmtDisable(&pmotor->estimator.zsmt);
    pmotor->idqCtrlOutLimit.d = MCAF_CURRENT_CTRL_D_OUT_LIMIT;
    pmotor->idqCtrlOutLimit.q = MCAF_CURRENT_CTRL_Q_OUT_LIMIT;
}

/**
 * Perform one interaction step between the hybrid estimator 
 * and other modules
 * 
 * @param pstate estimator state
 * @param pmotor full motor state
 * @param update_func function for updating other estimator
 * @param other_estimator opaque pointer to other estimator state
 */
inline static void MCAF_EstimatorZsmtHybridInteractionStep(
            MCAF_ESTIMATOR_ZSMT_HYBRID_T *pstate, 
            MCAF_MOTOR_DATA *pmotor,
            MCAF_ESTIMATOR_OUTPUT_UPDATE_FUNCTION update_func,
            void *other_estimator
        )
{
    const uint16_t flags = pstate->flags;
    if (flags & MCAF_ZSMT_HYBRID_ENGAGE_ZSMT)
    {
        MCAF_EstimatorZsmtHybridEngageZSMT(pstate, pmotor);
    }
    if ((flags & MCAF_ZSMT_HYBRID_DISENGAGE_ZSMT)
     && ((flags & MCAF_ZSMT_HYBRID_LEAVE_ZSMT_RUNNING) == 0))
    {
        MCAF_EstimatorZsmtHybridDisengageZSMT(pstate, pmotor);
    }
    if (flags & MCAF_ZSMT_HYBRID_FORCE_BEMF_STATE)
    {
        /*
         * On certain occasions (for example, when the motor speed is too slow)
         * we need to re-initialize the back-emf estimator's output state.
         * 
         * To do this without explicit dependencies 
         * on any particular estimator's source code, 
         * we call an appropriate method using a function pointer.
         * With inline functions, the compiler can optimize out this call
         * if the function is known at compile-time.
         * 
         * This is the equivalent to calling
         * MCAF_EstimatorXyzUpdateOutput(&pmotor->estimator.xyz, pstate->pout);
         * for any compatible estimator Xyz.
         * 
         * Assembly comments added here to help confirm successful inlining
         * of this function call.
         */
        asm volatile ("; BEGIN update other estimator output");
        update_func(other_estimator, pstate->pout);
        asm volatile ("; END update other estimator output");
    }
    pstate->flags &= ~MCAF_ZSMT_HYBRID_INTERACTION_MASK;
}

#ifdef __cplusplus
}
#endif

#endif /* __ZSMT_HYBRID_INTERACTION_H */