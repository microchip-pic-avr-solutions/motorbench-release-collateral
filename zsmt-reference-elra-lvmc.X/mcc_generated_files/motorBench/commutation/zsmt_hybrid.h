/**
 * zsmt_hybrid.h
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

#ifndef __ZSMT_HYBRID_H
#define __ZSMT_HYBRID_H

#include <stdint.h>
#include "motor_control_types.h"
#include "foc_types.h"
#include "units.h"
#include "commutation/common.h"
//#include "parameters/zsmt_hybrid_params.h"
#include "startup_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * State values
 */
typedef enum tagMCAF_ZSMT_HYBRID_STATE {
    MCAF_ZSMT_HYBRID_SLOW = 0,         /** low-speed */
    MCAF_ZSMT_HYBRID_TRANSITION = 1,   /** transition speed */
    MCAF_ZSMT_HYBRID_FAST = 2          /** high-speed */
} MCAF_ZSMT_HYBRID_STATE;
    
typedef enum tagMCAF_ZSMT_HYBRID_FLAGS {
    MCAF_ZSMT_HYBRID_DISENGAGE_ZSMT     = 0x0001, /** disengage ZS/MT */
    MCAF_ZSMT_HYBRID_ENGAGE_ZSMT        = 0x0002, /** engage ZS/MT */
    MCAF_ZSMT_HYBRID_FORCE_BEMF_STATE   = 0x0004, /** force BEMF state to ZS/MT angle */
    MCAF_ZSMT_HYBRID_INTERACTION_MASK   = 0x0007, /** mask covering all the above flags */
            
    MCAF_ZSMT_HYBRID_STARTUP_MASK       = 0x8000, /** mask to reset appropriate flags at start */
            
    MCAF_ZSMT_HYBRID_LEAVE_ZSMT_RUNNING = 0x8000, /** mask to keep running ZS/MT */
} MCAF_ZSMT_HYBRID_FLAGS;
    
/**
 * State variables for hybrid estimator
 */
typedef struct tagMCAF_ESTIMATOR_ZSMT_HYBRID
{
    /*
     * Runtime-adjustable parameters
     *
     * These values are typically set once, at startup,
     * but may be adjusted using real-time diagnostic tools.
     */
    

    /*
     * State variables
     *
     * The state of the estimator at any given instant 
     * is completely determined by its state variables.
     *
     * At each new step of the estimator, the state variables can theoretically
     * be expressed as a deterministic function of the following values:
     *
     *   - state variables at the previous step
     *   - runtime-adjustable parameters
     *   - inputs to the estimator step function
     */
    MCAF_ZSMT_HYBRID_STATE state;  /** State machine state */
    uint16_t flags;             /** bit flags from MCAF_ZSMT_HYBRID_FLAGS */
    uint16_t delayCounter;      /** delay counter */
    struct {
        MCAF_U_ANGLE_ELEC threshold; /** threshold of angle convergence */
        uint16_t duration;      /** required duration for convergence */
    } angleConvergence;         /** data structure to track angle convergence */
    /** Speed thresholds used to determine state changes */
    struct {
        MCAF_U_VELOCITY_ELEC slow;        /** Speed threshold for MCAF_ZSMT_HYBRID_SLOW */
        MCAF_U_VELOCITY_ELEC transition;  /** Speed threshold for MCAF_ZSMT_HYBRID_TRANSITION */
        MCAF_U_VELOCITY_ELEC fast;        /** Speed threshold for MCAF_ZSMT_HYBRID_FAST */
    } speedThreshold;
    
    const MCAF_ESTIMATOR_OUTPUTS_T *pzsmt_out;  /** Outputs of ZS/MT */
    const MCAF_ESTIMATOR_OUTPUTS_T *pbemf_out;  /** Outputs of BEMF-based estimator */
    const MCAF_ESTIMATOR_OUTPUTS_T *pout;       /** Overall output */

    /*
     * Auxiliary variables
     *
     * These values can be derived from the state variables
     * using memory-less calculations. 
     *
     * They are usually output or intermediate variables,
     * and are typically retained in RAM to support data logging 
     * with real-time diagnostic tools.
     */
    MCAF_U_ANGLE_ELEC thetaDifference;    /** angle difference between two estimators */
} MCAF_ESTIMATOR_ZSMT_HYBRID_T;

/**
 * Initializes hybrid estimator state variables on reset.
 *
 * @param pstate state variable structure
 * @param pmotor motor parameters
 */
void MCAF_EstimatorZsmtHybridInit(MCAF_ESTIMATOR_ZSMT_HYBRID_T *pstate, const MCAF_MOTOR_PARAMETERS_T *pmotor);

/**
 * Initializes hybrid estimator state variables prior to starting motor.
 * 
 * @param pstate state variable structure
 */
void MCAF_EstimatorZsmtHybridStartupInit(MCAF_ESTIMATOR_ZSMT_HYBRID_T *pstate);

/**
 * Initializes hybrid estimator output dependencies
 * 
 * @param pstate state variable structure
 * @param pzsmt_out ZS/MT dependency
 * @param pbemf_out back-emf dependency
 */
void MCAF_EstimatorZsmtHybridSetupOutputDependencies(MCAF_ESTIMATOR_ZSMT_HYBRID_T *pstate,
                                                   const MCAF_ESTIMATOR_OUTPUTS_T *pzsmt_out,
                                                   const MCAF_ESTIMATOR_OUTPUTS_T *pbemf_out);

/**
 * Executes one control step of the hybrid estimator.
 *
 * @param pstate state variable structure
 * @param pinput Standard algorithm inputs (e.g. stationary-frame voltage and current)
 * @param pmotor Motor parameters
 */
void MCAF_EstimatorZsmtHybridStep(MCAF_ESTIMATOR_ZSMT_HYBRID_T *pstate,
                           const MCAF_STANDARD_INPUT_SIGNALS_T *pinput,
                           const MCAF_MOTOR_PARAMETERS_T *pmotor);

/**
 * Returns commutation angle
 * 
 * @param pstate state
 * @return commutation angle
 */
inline static MCAF_U_ANGLE_ELEC MCAF_EstimatorZsmtHybridCommutationAngle(const MCAF_ESTIMATOR_ZSMT_HYBRID_T *pstate)
{
    return pstate->pout->thetaElectrical;
}

/**
 * Returns electrical frequency
 * 
 * @param pstate state
 * @return electrical frequency
 */
inline static MCAF_U_VELOCITY_ELEC MCAF_EstimatorZsmtHybridElectricalFrequency(const MCAF_ESTIMATOR_ZSMT_HYBRID_T *pstate)
{
    return pstate->pout->omegaElectrical;
}

/**
 * Determine whether startup delay is requested
 * 
 * @param pstate state
 * @param startupStatus startup status
 * @return whether a startup delay is requested
 */
inline static bool MCAF_EstimatorZsmtHybridStartupDelayRequested(const MCAF_ESTIMATOR_ZSMT_HYBRID_T *pstate, MCAF_STARTUP_STATUS_T startupStatus)
{
    return false;
}



#ifdef __cplusplus
}
#endif

#endif /* __ZSMT_HYBRID_H */