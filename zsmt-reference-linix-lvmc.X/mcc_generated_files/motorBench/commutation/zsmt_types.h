/**
 * zsmt_types.h
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

#ifndef __ZSMT_TYPES_H
#define __ZSMT_TYPES_H

#include <stdint.h>
#include "motor_control_types.h"
#include "units.h"
#include "commutation/common.h"
#include "startup_types.h"

#ifdef __cplusplus
extern "C" {
#endif
    
/**
 * State variables for ZS/MT phase-locked loop
 */
typedef struct tagMCAF_ESTIMATOR_ZSMT_PLL {
    sx1632_t               velocityIntegrator; /** velocity integrator */
    sx1632_t               angleIntegrator;    /** angle integrator */
    int32_t                angleIntegratorInput; /** input to angle integrator */
    int16_t                error;              /** error signal */

    int16_t                kp;                 /** proportional gain */
    uint16_t               kpShift;            /** shift count for kp */
    int16_t                ki;                 /** integral gain */
    int16_t                dt;                 /** timestep gain for angle integrator */
} MCAF_ESTIMATOR_ZSMT_PLL_T;
    
/**
 * ZSMT flags
 */
enum {
    ZSMT_F_STARTUP              = 1,           /** Startup flag */
    ZSMT_F_DEMOD_SAMPLE_READY   = 2,           /** Demodulation samples are ready */
    ZSMT_F_STARTUP_COMMAND_SYNC = 4,           /** Command should be changed during startup */
};

/**
 * State variables for ZS/MT estimator
 */
typedef struct tagMCAF_ESTIMATOR_ZSMT
{
    MCAF_ESTIMATOR_OUTPUTS_T output;           /** Estimated velocity and angle */
    
    /** Excitation voltage structure */
    struct {
        MCAF_U_VOLTAGE amplitude;              /** Amplitude of d-axis excitation */
        MCAF_U_VOLTAGE voltage;                /** D-axis excitation voltage (alternates in sign) */
    } excitation;
    MCAF_U_CURRENT         iqHistory[4];       /** length=4 history for FIR filtering/downsampling */  
    MCAF_U_CURRENT         idHistory[4];       /** length=4 history for FIR filtering/downsampling */  
    MC_DQ_T                rawError;           /** Raw error from history */
    int16_t                errorGain;          /** Error gain to PLL error, Q12 */
    int16_t                errorLimit;         /** Error limit after gain and before filter */
    /** Error filtering between input and phase-locked loop, to reduce high-frequency noise */
    struct {
      uint16_t             gain;               /** Low-pass filter gain, Q16 */
      int16_t              input;              /** Input error */
      sx1632_t             state;              /** Filtered error */
    } filteredError;
    /** Correction term for q-axis compensation */
    struct {
      int32_t              iqfilt;             /** term proportional to iq */
      int16_t              gainDC;             /** DC correction gain, Q16 */
    } correction;
    MCAF_ESTIMATOR_ZSMT_PLL_T pll;             /** Phase-locked loop */
    uint16_t               counter;            /** state counter */
    uint16_t               delayCounter;       /** delay counter */
    uint16_t               flags;              /** bit flags */
    uint16_t               executePllMask;     /** mask for timing PLL execution */
    MCAF_STARTUP_STATUS_T  startupStatusPrevious; /** previous startup status */
    
    int16_t                angleTestPerturbation; /** test perturbation */
    
    uint16_t               alignTime;          /** Align-time duration (if startup permits delay) */
    uint16_t               angleLockDelay;     /** Angle-lock duration (if startup permits delay) */
    
    /*
     * State variables to support standalone operation
     */
    
    MCAF_U_DIMENSIONLESS_SINCOS  sincos;               /** sine and cosine */
    MCAF_U_CURRENT_DQ            idq;                  /** dq-frame currents */
    MCAF_U_VOLTAGE_ALPHABETA     vExcitationAlphabeta; /* alpha-beta phase excitation voltage */
} MCAF_ESTIMATOR_ZSMT_T;

/**
 * Gets commutation angle
 * 
 * @param pzsmt ZS/MT state variable structure
 * @return commutation angle
 */
inline static MCAF_U_ANGLE_ELEC MCAF_EstimatorZsmtCommutationAngle(const MCAF_ESTIMATOR_ZSMT_T *pzsmt)
{
    return pzsmt->pll.angleIntegrator.x16.hi;
}

/**
 * Gets electrical frequency
 * 
 * @param pzsmt ZS/MT state variable structure
 * @return electrical frequency
 */
inline static MCAF_U_VELOCITY_ELEC MCAF_EstimatorZsmtElectricalFrequency(const MCAF_ESTIMATOR_ZSMT_T *pzsmt)
{
    return pzsmt->pll.velocityIntegrator.x16.hi;
}

/**
 * Sets PLL state (angle and velocity)
 * 
 * @param pzsmt ZS/MT state variable structure
 * @param angle commutation angle
 * @param velocity electrical frequency
 */
inline static void MCAF_EstimatorZsmtSetPllState(MCAF_ESTIMATOR_ZSMT_T *pzsmt, 
                                                 MCAF_U_ANGLE_ELEC angle,
                                                 MCAF_U_VELOCITY_ELEC velocity)
{
    pzsmt->pll.angleIntegrator.x16.hi = angle;
    pzsmt->pll.velocityIntegrator.x16.hi = velocity;
}

#ifdef __cplusplus
}
#endif

#endif /* __ZSMT_TYPES_H */