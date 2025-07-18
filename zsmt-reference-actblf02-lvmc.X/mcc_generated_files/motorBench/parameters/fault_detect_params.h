/* This is an autogenerated file from a template. Do not edit this file as it will be overwritten.*/
/**
 *
 * fault_detect_params.h
 *
 * Fault detection parameters
 *
 * Component: supervisory
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
#ifndef __FAULT_DETECT_PARAMS_H
#define __FAULT_DETECT_PARAMS_H

#ifdef  __cplusplus
extern "C" {
#endif

/* overcurrent threshold (109.2% of rated allowable current) */
#define THRESHOLD_OVERCURRENT_STALL_DETECT       7396      // Q15(  0.22571) =   +9.84087 A           =   +9.84102 A           - 0.0015%

/*
 * natural_freq_current:         878.993  Hz
 * current loop natural frequency

 * natural_freq_velocity:          2.047  Hz
 * velocity loop natural frequency
 */

/* decimation factor for 2 stage filter LPF */
#define DECIMATION_FACTOR                     100      // Q0(100.00000)  = +100.00000             = +100.00000             + 0.0000%
/* 
 * Coefficient a1 for 2 stage implementation of LPF. Equation used for calculation:
 * f3db*Ts*2*pi. f3db for 1st stage is 10hz
 */
#define DECIMATION_FILTER_LPF1_VARIANCE_DETECT_COEFFA1        103      // Q15(  0.00314) =  +10.00547 Hz          =  +10.00000 Hz          + 0.0547%
/* 
 * Coefficient a1 for 2 stage implementation of LPF. Equation used for calculation:
 * f3db*Ts*2*pi. f3db for second stage is 1/10th of the natural frequency, Ts is 1/200hz
 */
#define DECIMATION_FILTER_LPF2_VARIANCE_DETECT_COEFFA1        211      // Q15(  0.00644) = +204.96639 mHz         = +204.72113 mHz         + 0.1198%
/* 
 * LPF filter coefficient for over current detect. Equation used for calculation:
 * f3db*Ts*2*pi f3d is equal to natural frequency
 */
#define FILTER_LPF_OVERCURRENT_DETECT          21      // Q15(  0.00064) =   +2.03995 Hz          =   +2.04721 Hz          - 0.3547%
/* 
 * LPF filter coefficient for negative Ed detect. Equation used for calculation:
 * f3db*Ts*2*pi f3d is equal to natural frequency
 */
#define FILTER_LPF_NEGATIVE_ED_DETECT          21      // Q15(  0.00064) =   +2.03995 Hz          =   +2.04721 Hz          - 0.3547%
/* 
 * HPF filter coefficient for 16bit implementation of HPF.
 * f3db is 2x natural frequency.
 */
#define FILTER_HPF_VARIANCE_DETECT             84      // Q16(  0.00128) =   +4.07990 Hz          =   +4.09442 Hz          - 0.3547%
/* 
 * Timer threshold to trigger low speed detect.
 * It is set to 3 times (1/natural frequency of velocity loop)
 */
#define ACTIVE_TIMER_THRESHOLD_LOW_SPEED_DETECT      29308      // Q0(29308.00000) =   +1.46540 s           =   +1.46541 s           - 0.0006%
/* 
 * Inactive timer threshold for low speed detect.
 * It is set to (2.0/natural frequency of velocity loop),
 * in units of the ADC ISR period.
 */
#define INACTIVE_TIMER_THRESHOLD_LOW_SPEED_DETECT      29308      // Q0(29308.00000) =   +1.46540 s           =   +1.46541 s           - 0.0006%
/* 
 * Overcurrent detector. Normally if the saturation limit was exceeded,
 * then we have a fault in the controllers.
 * then the error should immediately trigger
 * Timer threshold to trigger over currents detect.
 * It is set to 2 times (1/natural frequency of current loop)
 */
#define TIMER_COUNTS_OVERCURRENT_DETECT         46      // Q0( 46.00000)  =   +2.30000 ms          =   +2.27533 ms          + 1.0842%
/* 
 * Timer threshold to trigger negative Ed stall detect.
 * It is set to 5 times (1/natural frequency of velocity loop)
 */
#define ACTIVE_TIMER_THRESHOLD_NEGATIVE_ED_DETECT      48847      // Q0(48847.00000) =   +2.44235 s           =   +2.44235 s           + 0.0001%
/* 
 * Timer threshold to trigger negative Ed stall detect.
 * It is set to 5 times (1/natural frequency of velocity loop)
 */
#define INACTIVE_TIMER_THRESHOLD_NEGATIVE_ED_DETECT      48847      // Q0(48847.00000) =   +2.44235 s           =   +2.44235 s           + 0.0001%
/* 
 * Timer threshold to trigger stall detect based on torque angle.
 * It is set to 3 times (1/natural frequency of velocity loop)
 */
#define ACTIVE_TIMER_THRESHOLD_TORQUE_ANGLE_DETECT      29308      // Q0(29308.00000) =   +1.46540 s           =   +1.46541 s           - 0.0006%
/* 
 * Inactive Timer threshold for stall detect based on torque angle.
 * It is set to 3 times (1/natural frequency of velocity loop)
 */
#define INACTIVE_TIMER_THRESHOLD_TORQUE_ANGLE_DETECT      29308      // Q0(29308.00000) =   +1.46540 s           =   +1.46541 s           - 0.0006%
/* 
 * Timer threshold to trigger stall detect based on variance in Ed and Eq.
 * It is set to (1/natural frequency of velocity loop)
 */
#define TIMER_COUNTS_VARIANCE_DETECT           98      // Q0( 98.00000)  = +490.00000 ms          = +488.46937 ms          + 0.3134%

/* Threshold for under speed detect as a fixed fraction of minimum velocity */
#define THRESHOLD_UNDERSPEED_STALL_DETECT  ((int16_t)(0.333*MCAF_VELOCITY_COMMAND_MIN))
/* Ed detect threshold */
#define THRESHOLD_ED_STALL_DETECT               5      // Q15(  0.00015) =  +10.87952 mV          =  +10.00000 mV          + 8.7952%

/*
 * max error from modified polynomial approximation 0.04846
 * limited normalized frequency omega_c1 = 0.1
 * max error above omega_c1 = 0.018088
 */
/* torque angle threshold polynomial, constant term */
#define STALL_DETECT_TORQUE_ANGLE_COEFF0       6196      // Q15(  0.18909) = +189.08691 m           = +189.08625 m           + 0.0004%
/* torque angle threshold polynomial, linear term */
#define STALL_DETECT_TORQUE_ANGLE_COEFF1      24021      // Q15(  0.73306) = +733.06274 m           = +733.04955 m           + 0.0018%
/* torque angle threshold polynomial, quadratic term */
#define STALL_DETECT_TORQUE_ANGLE_COEFF2       2224      // Q15(  0.06787) =  +67.87109 m           =  +67.86420 m           + 0.0102%
#define STALL_DETECT_TORQUE_ANGLE_K         11939      // Q15(  0.36435) = +364.34937 m           = +364.35514 m           - 0.0016%
/* Maximum velocity for torque angle stall detection (we inhibit at faster speeds) */
#define STALL_DETECT_TORQUE_ANGLE_VELOCITY_THRESHOLD       8738      // Q15(  0.26666) = +167.54905 rad/s       = +167.55161 rad/s       - 0.0015%

/* overvoltage fault threshold */
#define VDC_OVERVOLTAGE_THRESHOLD           12868      // Q15(  0.39270) =  +27.99952 V           =  +28.00000 V           - 0.0017%
/* undervoltage fault threshold */
#define VDC_UNDERVOLTAGE_THRESHOLD           5515      // Q15(  0.16830) =  +12.00011 V           =  +12.00000 V           + 0.0009%
/* overtemperature fault threshold */
#define MCAF_OVERTEMPERATURE_THRESHOLD       5000      // Q15(  0.15259) =  +50.00000 C           =  +50.00000 C           + 0.0000%

#ifdef  __cplusplus
}
#endif

#endif // __FAULT_DETECT_PARAMS_H
