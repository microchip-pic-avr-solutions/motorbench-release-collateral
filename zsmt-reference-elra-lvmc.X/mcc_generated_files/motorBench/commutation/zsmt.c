/**
 * zsmt.c
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

#include <stdint.h>
#include <stdbool.h>

#include "util.h"
#include "parameters/zsmt_params.h"
#include "parameters/operating_params.h"
#include "parameters/motor_params.h"
#include "motor_control.h"
#include "motor_control_function_mapping.h"
#include "zsmt.h"
#include "zsmtlib.h"
#include "system_state.h"
#include "commutation/common.h"

void MCAF_EstimatorZsmtStep(MCAF_ESTIMATOR_ZSMT_T *pzsmt, 
                           const MCAF_STANDARD_INPUT_SIGNALS_T *pinput,
                           const MCAF_MOTOR_PARAMETERS_T *pmotor)
{    
    if (ZSMT_IsStandaloneEstimator())
    {
        MC_TransformPark(&pinput->ialphabeta, &pzsmt->sincos, &pzsmt->idq);
    }
    else
    {
        pzsmt->idq = pinput->idq;
    }

    ZSMTLIB_EstimatorZsmtStep(pzsmt, pinput, pmotor);
    
    if (ZSMT_IsStandaloneEstimator())
    {
        const int16_t thetaElectrical = MCAF_EstimatorZsmtCommutationAngle(pzsmt);    

        /* Order of computation is consistent with foc.c;
         * this is done so that theta and cos theta are consistent 
         * at the end of the cycle
         */
        const MCAF_U_VOLTAGE vExcitation = pzsmt->excitation.voltage;
        MC_CalculateSineCosine(thetaElectrical, &pzsmt->sincos);
        /* Full inverse Park transform not necessary since we are just applying along the D-axis:
         * alpha = D*cos - Q*sin,
         * beta  = D*sin + Q*cos */
        pzsmt->vExcitationAlphabeta.alpha = UTIL_MulQ15(pzsmt->sincos.cos, vExcitation);
        pzsmt->vExcitationAlphabeta.beta  = UTIL_MulQ15(pzsmt->sincos.sin, vExcitation);
    }
}

void MCAF_EstimatorZsmtInit(MCAF_ESTIMATOR_ZSMT_T *pzsmt, 
        const MCAF_MOTOR_PARAMETERS_T *pmotor)
{
    pzsmt->excitation.amplitude = ZSMT_EXCITATION_VOLTAGE_AMPLITUDE;
    pzsmt->excitation.voltage = 0;
    pzsmt->counter = 0;
    
    int i;
    for (i = 0; i < 4; ++i)
    {
        pzsmt->idHistory[i] = 0;
        pzsmt->iqHistory[i] = 0;
    }
    
    pzsmt->errorGain                  = ZSMT_ERROR_GAIN;
    pzsmt->errorLimit                 = ZSMT_ERROR_LIMIT;
    pzsmt->filteredError.gain         = ZSMT_FILTER_GAIN;
    pzsmt->filteredError.state.x32    = 0;
    pzsmt->rawError.d                 = 0;
    pzsmt->rawError.q                 = 0;
    pzsmt->pll.error                  = 0;
    pzsmt->pll.velocityIntegrator.x32 = 0;
    pzsmt->pll.angleIntegrator.x32    = 0;
    pzsmt->pll.angleIntegratorInput   = 0;
    pzsmt->pll.kp                     = ZSMT_PLL_KP;
    pzsmt->pll.kpShift                = ZSMT_PLL_KP_Q;
    pzsmt->pll.ki                     = ZSMT_PLL_KI;
    pzsmt->pll.dt                     = ZSMT_PLL_DT;
    pzsmt->flags                      = 0;
    pzsmt->delayCounter               = 0;
    pzsmt->startupStatusPrevious      = MSST_UNSPECIFIED;
    pzsmt->angleTestPerturbation      = 0;
    pzsmt->executePllMask             = ZSMT_PLL_EXECUTION_DIVIDER - 1;
    
    pzsmt->alignTime                  = ZSMT_ALIGN_TIME;
    pzsmt->angleLockDelay             = ZSMT_ANGLE_LOCK_DELAY;
    pzsmt->vExcitationAlphabeta.alpha = 0;
    pzsmt->vExcitationAlphabeta.beta  = 0;
    pzsmt->sincos.cos                 = 0;
    pzsmt->sincos.sin                 = 0;
    pzsmt->correction.gainDC          = ZSMT_CORRECTION_GAIN_DC;
    
    pzsmt->output.thetaElectrical     = 0;
    pzsmt->output.omegaElectrical     = 0;
}
