/* This is an autogenerated file from a template. Do not edit this file as it will be overwritten.*/
/**
 *
 * pll_params.h
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
#ifndef __PLL_PARAMS_H
#define __PLL_PARAMS_H

#ifdef  __cplusplus
extern "C" {
#endif

/* Estimator sampling time used for integrating electrical frequency to obtain electrical angle */
#define MCAF_PLL_DT_ANGULAR                   492      // Q15(  0.01501) =  +50.04883 useconds    =  +50.00000 useconds    + 0.0977%
/* Maximum rate of change of current dI/dt, used as limit at high velocity operating range */
#define D_ILIMIT_HS                           655      // Q15(  0.01999) =  +17.43042 kA/s        =  +17.44000 kA/s        - 0.0549%
/* Maximum rate of change of current dI/dt, used as limit at low velocity operating range
 * (Note: this has a different scaling factor from D_ILIMIT_HS to account for the subsampling factor PLL_LOWSPEED_DIBYDT_PRESCALER)
 */
#define D_ILIMIT_LS                          2621      // Q15(  0.07999) =   +8.71854 kA/s        =   +8.72000 kA/s        - 0.0168%
/* Filter constant that is used for filtering the estimated 
 *                   BEMF, at nominal velocity
 */
#define KFILTER_ESDQ                         1199      // Q15(  0.03659) = +731.81152 rad/s       = +731.99109 rad/s       - 0.0245%
/* Filter constant that is used for filtering the estimated 
 *                   BEMF, during field-weakening
 */
#define KFILTER_ESDQ_FW                       164      // Q15(  0.00500) = +100.09766 rad/s       = +100.09766 rad/s       + 0.0000%
/* Filter contant that is used for 
 *                   filtering the estimated velocity
 */
#define KFILTER_VELESTIM                      748      // Q15(  0.02283) = +456.54297 rad/s       = +456.62100 rad/s       - 0.0171%
/* Decimation speed threshold, below which velocity 
 *                   estimation is optimized for stability
 */
#define DECIMATE_BASE_SPEED                  2185      // Q15(  0.06668) = +300.06409 RPM         = +300.00000 RPM         + 0.0214%
/* Velocity filter threshold, below which a slow filter is used */
#define MCAF_PLL_VELOCITY_FILTER_THRESHOLD      21845      // Q15(  0.66666) =   +2.99995 kRPM        =   +3.00000 kRPM        - 0.0015%
/* Number of PLL execution steps per deltaI calculation.
 * This undersampling prescaler must be a power of two
 */
#define PLL_LOWSPEED_DIBYDT_PRESCALER           8
/* Number of shift counts required to compensate 
 * for the gain in dI/dt calculation that is due to undersampling
 */
#define PLL_LOWSPEED_DIBYDT_PRESCALER_SHIFTCOUNT          3
/* Add one-cycle delay to match current and voltage sample timing */
#define MCAF_PLL_DELAY_MATCH                    1
/* Empirical scaling factor for 1/Ke scaling */
#define MCAF_PLL_KE_INVERSE_SCALING         16384      // Q14(  1.00000) =   +1.00000             =   +1.00000             + 0.0000%

#define INITOFFSET_TRANS_OPEN_CLSD  0x0000       // initial offset added to estimated angle value

#ifdef  __cplusplus
}
#endif

#endif // __PLL_PARAMS_H
