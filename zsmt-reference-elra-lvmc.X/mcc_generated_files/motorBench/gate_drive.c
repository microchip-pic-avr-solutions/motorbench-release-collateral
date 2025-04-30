/**
 * gate_drive.c
 * 
 * Provides routines for gate drive management.
 * 
 * Component: HAL
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

#include <stdbool.h>
#include "gate_drive.h"
#include "parameters/hal_params.h"
#include "parameters/timing_params.h"

void MCAF_BootstrapChargeInit(MCAF_BOOTSTRAP_STATE *pbootstrap)
{
    pbootstrap->dutycycle[0] = 0;
    pbootstrap->dutycycle[1] = 0;
    pbootstrap->dutycycle[2] = 0;
    pbootstrap->delayCount = 0;
    pbootstrap->state = 0;
}

static inline uint16_t minimumDutyCycleForBootstrapCharging(void)
{
    return HAL_PARAM_PWM_PERIOD_COUNTS - HAL_PARAM_MIN_LOWER_DUTY_COUNTS;
}

bool MCAF_BootstrapChargeStepIsr(MCAF_BOOTSTRAP_STATE *pbootstrap)
{
    bool returnState = false;
    
    switch(pbootstrap->state)
    {
        case MCBS_IDLE_START:
            /* Override high-side PWMx to LOW and set 
             * low-side PWMx to 0% duty cycle */
            HAL_PWM_Outputs_Disable();
            pbootstrap->dutycycle[0] = HAL_PARAM_PWM_PERIOD_COUNTS;
            pbootstrap->dutycycle[1] = HAL_PARAM_PWM_PERIOD_COUNTS;
            pbootstrap->dutycycle[2] = HAL_PARAM_PWM_PERIOD_COUNTS;
            HAL_PWM_UpperTransistorsOverride_Low();
            HAL_PWM_LowerTransistorsOverride_Disable();
            
            pbootstrap->delayCount = MCAF_BOARD_BOOTSTRAP_INITIAL_DELAY;
            pbootstrap->state = MCBS_WAIT_INITIAL;
            break;
            
        case MCBS_WAIT_INITIAL:
            /* Wait for a preset duration of time before starting to
             * charge the Phase-A bootstrap */
            if (pbootstrap->delayCount == 0)
            {   
                pbootstrap->state = MCBS_PHASE_A_SETUP_CHARGING;
            }
            break;

        case MCBS_PHASE_A_SETUP_CHARGING:
            pbootstrap->dutycycle[0] = minimumDutyCycleForBootstrapCharging();
            pbootstrap->delayCount = MCAF_BOARD_BOOTSTRAP_PHASE_DELAY;
            pbootstrap->state = MCBS_PHASE_A_CHARGING;
            break;
            
        case MCBS_PHASE_A_CHARGING:
            /* Wait for a preset duration of time to let the bootstrap drive
             * charge the Phase-A bootstrap capacitor */
            if (pbootstrap->delayCount == 0)
            {
                pbootstrap->state = MCBS_PHASE_B_SETUP_CHARGING;
            }
            break;
            
        case MCBS_PHASE_B_SETUP_CHARGING:
            pbootstrap->dutycycle[1] = minimumDutyCycleForBootstrapCharging();
            pbootstrap->delayCount = MCAF_BOARD_BOOTSTRAP_PHASE_DELAY;
            pbootstrap->state = MCBS_PHASE_B_CHARGING;
            break;
            
        case MCBS_PHASE_B_CHARGING:
            /* Wait for a preset duration of time to let the bootstrap drive
             * charge the Phase-B bootstrap capacitor */
            if (pbootstrap->delayCount == 0)
            {
                pbootstrap->state = MCBS_PHASE_C_SETUP_CHARGING;
            }
            break;

        case MCBS_PHASE_C_SETUP_CHARGING:
            pbootstrap->dutycycle[2] = minimumDutyCycleForBootstrapCharging();
            pbootstrap->delayCount = MCAF_BOARD_BOOTSTRAP_PHASE_DELAY;
            pbootstrap->state = MCBS_PHASE_C_CHARGING;
            break;
            
        case MCBS_PHASE_C_CHARGING:
            /* Wait for a preset duration of time to let the bootstrap drive
             * charge the Phase-C bootstrap capacitor */
            if (pbootstrap->delayCount == 0)
            {
                pbootstrap->state = MCBS_BOOTSTRAP_COMPLETE;
            }
            break;
            
        case MCBS_BOOTSTRAP_COMPLETE:
            /* Bootstrap sequence is complete, wait in this state */
            returnState = true;
            break;
    }
    HAL_PWM_DutyCycle_Set(pbootstrap->dutycycle);
    
    if (pbootstrap->delayCount > 0)
    {
        pbootstrap->delayCount--;
    }
    
    return returnState;
}