/**
 * PWM Generated Driver Source File
 * 
 * @file      pwm.c
 * 
 * @ingroup   pwmhsdriver
 * 
 * @brief     This is the generated driver source file for PWM driver
 *
 * @skipline @version   PLIB Version 1.3.1
 *
 * @skipline  Device : 
*/

/*disclaimer*/

// Section: Included Files


#include "../pwm.h"

// Section: File specific functions

static void (*PWM_GeneratorEOCEventHandler)(enum PWM_GENERATOR genNum) = NULL;

static void (*PWM_CommonEventHandler)(enum PWM_COMMON_EVENT event) = NULL;

// Section: Driver Interface

const struct PWM_HS_INTERFACE MCC_PWM = {
    .Initialize                     = &PWM_Initialize,
    .Deinitialize                   = &PWM_Deinitialize,
    .Disable                        = &PWM_Disable,
    .Enable                         = &PWM_Enable,
    .ModeSet                        = &PWM_ModeSet,
    .OutputModeSet                  = &PWM_OutputModeSet,
    .MasterPeriodSet                = &PWM_MasterPeriodSet,
    .MasterDutyCycleSet             = &PWM_MasterDutyCycleSet,
    .PeriodSet                      = &PWM_PeriodSet,
    .DutyCycleSet                   = &PWM_DutyCycleSet,
    .PhaseSelect                    = &PWM_PhaseSelect,
    .PhaseSet                       = &PWM_PhaseSet,
    .OverrideDataSet                = &PWM_OverrideDataSet,
    .OverrideDataHighSet            = &PWM_OverrideDataHighSet,
    .OverrideDataLowSet             = &PWM_OverrideDataLowSet,
    .OverrideDataGet                = &PWM_OverrideDataGet,
    .OverrideHighEnable             = &PWM_OverrideHighEnable,
    .OverrideLowEnable              = &PWM_OverrideLowEnable,
    .OverrideHighDisable            = &PWM_OverrideHighDisable,
    .OverrideLowDisable             = &PWM_OverrideLowDisable,
    .DeadTimeLowSet                 = &PWM_DeadTimeLowSet,
    .DeadTimeHighSet                = &PWM_DeadTimeHighSet,
    .DeadTimeSet                    = &PWM_DeadTimeSet,
    .TriggerCompareValueSet         = &PWM_TriggerCompareValueSet,
    .GeneratorInterruptEnable       = &PWM_GeneratorInterruptEnable,
    .GeneratorInterruptDisable      = &PWM_GeneratorInterruptDisable,
    .GeneratorEventStatusGet        = &PWM_GeneratorEventStatusGet,
    .GeneratorEventStatusClear      = &PWM_GeneratorEventStatusClear,

    .SpecialEventPrimaryCompareValueSet     = NULL,    
    .SpecialEventTriggerInterruptFlagClear  = NULL,
    .SpecialEventPrimaryInterruptEnable     = NULL,
    .SpecialEventPrimaryInterruptDisable    = NULL,
    .FaultModeLatchDisable                  = NULL,
    .FaultModeLatchEnable                   = NULL,
    .MasterPhaseSet                         = &PWM_MasterPhaseSet,
    .GeneratorDisable                       = &PWM_GeneratorDisable,
    .GeneratorEnable                        = &PWM_GeneratorEnable,
    .TriggerACompareValueSet                = &PWM_TriggerACompareValueSet,
    .TriggerBCompareValueSet                = &PWM_TriggerBCompareValueSet,
    .TriggerCCompareValueSet                = &PWM_TriggerCCompareValueSet,
    .TriggerDCompareValueSet                = NULL,
    .TriggerECompareValueSet                = NULL,
    .TriggerFCompareValueSet                = NULL,
    .SoftwareUpdateRequest                  = &PWM_SoftwareUpdateRequest,
    .SoftwareUpdatePending                  = &PWM_SoftwareUpdatePending,
    .FaultModeLatchClear                    = &PWM_FaultModeLatchClear,
    .Trigger1Enable                         = &PWM_Trigger1Enable,
    .Trigger1Disable                        = &PWM_Trigger1Disable,
    .Trigger2Enable                         = &PWM_Trigger2Enable,
    .Trigger2Disable                        = &PWM_Trigger2Disable,
    .DACTriggerEnable                       = NULL,
    .DACTriggerDisable                      = NULL,
    .GeneratorEOCEventCallbackRegister = &PWM_GeneratorEOCEventCallbackRegister,
    
    .CommonEventCallbackRegister = &PWM_CommonEventCallbackRegister,
    
    .GeneratorTasks         = &PWM_GeneratorTasks,
    .CommonEventTasks       = &PWM_CommonEventTasks,
};

// Section: PWM Module APIs

void PWM_Initialize (void)
{
    // 
    PG1CAP = 0x0UL;
    // PSS Tied to 0; PPS Not inverted; PSYNC disabled; SWTERM disabled; AQSS None; AQPS Not inverted; TERM Manual Terminate; TSYNCDIS PWM EOC; TQSS None; TQPS Not inverted; LATMOD disabled; SWPCIM PCI acceptance logic; SWPCI Drives '0'; ACP Level-sensitive; TERMPS disabled; BPSEL PWM Generator 1; BPEN disabled; 
    PG1CLPCI = 0x0UL;
    // MODSEL Center-Aligned; CLKSEL Master clock; TRGCNT 1; ON disabled; SOCS Self-trigger; TRGMOD PWM Generator operates in Single Trigger mode; UPDMOD SOC; MSTEN disabled; MPHSEL disabled; MPERSEL enabled; MDCSEL disabled; 
    PG1CON = 0x4000000CUL;
    // DC 0x0; 
    PG1DC = 0x0UL;
    // DCA 0x0; 
    PG1DCA = 0x0UL;
    // DTL 10.24; DTH 10.24; 
    PG1DT = 0xA000AUL;
    // PGTRGSEL EOC event; UPDTRG Duty Cycle; PWMPCI PWM1; ADTR1EN1 disabled; ADTR1EN2 disabled; ADTR1EN3 disabled; ADTR1PS 1:1; ADTR1OFS None; ADTR2EN1 disabled; ADTR2EN2 disabled; ADTR2EN3 disabled; IEVTSEL Time based interrupts disabled; SIEN disabled; FFIEN disabled; CLIEN disabled; FLTIEN disabled; 
    PG1EVT = 0x3000008UL;
    // PSS Tied to 0; PPS Not inverted; PSYNC disabled; SWTERM disabled; AQSS None; AQPS Not inverted; TERM Manual Terminate; TSYNCDIS PWM EOC; TQSS None; TQPS Not inverted; LATMOD disabled; SWPCIM PCI acceptance logic; SWPCI Drives '0'; ACP Level-sensitive; TERMPS disabled; BPSEL PWM Generator 1; BPEN disabled; 
    PG1FFPCI = 0x0UL;
    // PSS Comparator 3 output; PPS Not inverted; PSYNC disabled; SWTERM disabled; AQSS None; AQPS Not inverted; TERM Manual Terminate; TSYNCDIS PWM EOC; TQSS None; TQPS Not inverted; LATMOD disabled; SWPCIM PCI acceptance logic; SWPCI Drives '0'; ACP Latched; TERMPS disabled; BPSEL PWM Generator 1; BPEN disabled; 
    PG1FPCI = 0x300001DUL;
    // DBDAT 0x0; FFDAT 0x0; CLDAT 0x0; FLTDAT 0; OSYNC User output overrides occur when specified by UPDMOD bits; OVRDAT 0; OVRENL disabled; OVRENH disabled; SWAP disabled; CLMOD disabled; POLL Active-high; POLH Active-high; PENL enabled; PENH enabled; PMOD Complementary; DTCMPSEL PCI Sync Logic; PPSEN disabled; CAPSRC Software; 
    PG1IOCON = 0xC0200UL;
    // LEB disabled; PLF disabled; PLR disabled; PHF disabled; PHR disabled; 
    PG1LEB = 0x0UL;
    // PER 0x0; 
    PG1PER = 0x0UL;
    // PHASE 0x0; 
    PG1PHASE = 0x0UL;
    // PSS Tied to 0; PPS Not inverted; PSYNC disabled; SWTERM disabled; AQSS None; AQPS Not inverted; TERM Manual Terminate; TSYNCDIS PWM EOC; TQSS None; TQPS Not inverted; LATMOD disabled; SWPCIM PCI acceptance logic; SWPCI Drives '0'; ACP Level-sensitive; TERMPS disabled; BPSEL PWM Generator 1; BPEN disabled; 
    PG1SPCI = 0x0UL;
    // UPDREQ disabled; UPDATE disabled; CAP disabled; TRCLR disabled; TRSET disabled; FFEVT disabled; CLEVT disabled; FLTEVT disabled; SEVT disabled; 
    PG1STAT = 0x0UL;
    // TRIGA NaN; CAHALF disabled; 
    PG1TRIGA = 0x0UL;
    // TRIGB 0x0; CAHALF disabled; 
    PG1TRIGB = 0x0UL;
    // TRIGC 0x0; CAHALF disabled; 
    PG1TRIGC = 0x0UL;
    // 
    PG2CAP = 0x0UL;
    // PSS Tied to 0; PPS Not inverted; PSYNC disabled; SWTERM disabled; AQSS None; AQPS Not inverted; TERM Manual Terminate; TSYNCDIS PWM EOC; TQSS None; TQPS Not inverted; LATMOD disabled; SWPCIM PCI acceptance logic; SWPCI Drives '0'; ACP Level-sensitive; TERMPS disabled; BPSEL PWM Generator 1; BPEN disabled; 
    PG2CLPCI = 0x0UL;
    // MODSEL Center-Aligned; CLKSEL Master clock; TRGCNT 1; ON disabled; SOCS Trigger output selected by PG1 or PG5; TRGMOD PWM Generator operates in Single Trigger mode; UPDMOD SOC; MSTEN disabled; MPHSEL disabled; MPERSEL enabled; MDCSEL disabled; 
    PG2CON = 0x4001000CUL;
    // DC 0x0; 
    PG2DC = 0x0UL;
    // DCA 0x0; 
    PG2DCA = 0x0UL;
    // DTL 10.24; DTH 10.24; 
    PG2DT = 0xA000AUL;
    // PGTRGSEL EOC event; UPDTRG Duty Cycle; PWMPCI PWM1; ADTR1EN1 disabled; ADTR1EN2 disabled; ADTR1EN3 disabled; ADTR1PS 1:1; ADTR1OFS None; ADTR2EN1 disabled; ADTR2EN2 disabled; ADTR2EN3 disabled; IEVTSEL Time based interrupts disabled; SIEN disabled; FFIEN disabled; CLIEN disabled; FLTIEN disabled; 
    PG2EVT = 0x3000008UL;
    // PSS Tied to 0; PPS Not inverted; PSYNC disabled; SWTERM disabled; AQSS None; AQPS Not inverted; TERM Manual Terminate; TSYNCDIS PWM EOC; TQSS None; TQPS Not inverted; LATMOD disabled; SWPCIM PCI acceptance logic; SWPCI Drives '0'; ACP Level-sensitive; TERMPS disabled; BPSEL PWM Generator 1; BPEN disabled; 
    PG2FFPCI = 0x0UL;
    // PSS Comparator 3 output; PPS Not inverted; PSYNC disabled; SWTERM disabled; AQSS None; AQPS Not inverted; TERM Manual Terminate; TSYNCDIS PWM EOC; TQSS None; TQPS Not inverted; LATMOD disabled; SWPCIM PCI acceptance logic; SWPCI Drives '0'; ACP Latched; TERMPS disabled; BPSEL PWM Generator 1; BPEN disabled; 
    PG2FPCI = 0x300001DUL;
    // DBDAT 0x0; FFDAT 0x0; CLDAT 0x0; FLTDAT 0; OSYNC User output overrides occur when specified by UPDMOD bits; OVRDAT 0; OVRENL disabled; OVRENH disabled; SWAP disabled; CLMOD disabled; POLL Active-high; POLH Active-high; PENL enabled; PENH enabled; PMOD Complementary; DTCMPSEL PCI Sync Logic; PPSEN disabled; CAPSRC Software; 
    PG2IOCON = 0xC0200UL;
    // LEB disabled; PLF disabled; PLR disabled; PHF disabled; PHR disabled; 
    PG2LEB = 0x0UL;
    // PER 0x0; 
    PG2PER = 0x0UL;
    // PHASE 0x0; 
    PG2PHASE = 0x0UL;
    // PSS Tied to 0; PPS Not inverted; PSYNC disabled; SWTERM disabled; AQSS None; AQPS Not inverted; TERM Manual Terminate; TSYNCDIS PWM EOC; TQSS None; TQPS Not inverted; LATMOD disabled; SWPCIM PCI acceptance logic; SWPCI Drives '0'; ACP Level-sensitive; TERMPS disabled; BPSEL PWM Generator 1; BPEN disabled; 
    PG2SPCI = 0x0UL;
    // UPDREQ disabled; UPDATE disabled; CAP disabled; TRCLR disabled; TRSET disabled; FFEVT disabled; CLEVT disabled; FLTEVT disabled; SEVT disabled; 
    PG2STAT = 0x0UL;
    // TRIGA NaN; CAHALF disabled; 
    PG2TRIGA = 0x0UL;
    // TRIGB 0x0; CAHALF disabled; 
    PG2TRIGB = 0x0UL;
    // TRIGC 0x0; CAHALF disabled; 
    PG2TRIGC = 0x0UL;
    // 
    PG3CAP = 0x0UL;
    // PSS Tied to 0; PPS Not inverted; PSYNC disabled; SWTERM disabled; AQSS None; AQPS Not inverted; TERM Manual Terminate; TSYNCDIS PWM EOC; TQSS None; TQPS Not inverted; LATMOD disabled; SWPCIM PCI acceptance logic; SWPCI Drives '0'; ACP Level-sensitive; TERMPS disabled; BPSEL PWM Generator 1; BPEN disabled; 
    PG3CLPCI = 0x0UL;
    // MODSEL Center-Aligned; CLKSEL Master clock; TRGCNT 1; ON disabled; SOCS Trigger output selected by PG1 or PG5; TRGMOD PWM Generator operates in Single Trigger mode; UPDMOD SOC; MSTEN disabled; MPHSEL disabled; MPERSEL enabled; MDCSEL disabled; 
    PG3CON = 0x4001000CUL;
    // DC 0x0; 
    PG3DC = 0x0UL;
    // DCA 0x0; 
    PG3DCA = 0x0UL;
    // DTL 10.24; DTH 10.24; 
    PG3DT = 0xA000AUL;
    // PGTRGSEL EOC event; UPDTRG Duty Cycle; PWMPCI PWM1; ADTR1EN1 disabled; ADTR1EN2 disabled; ADTR1EN3 disabled; ADTR1PS 1:1; ADTR1OFS None; ADTR2EN1 disabled; ADTR2EN2 disabled; ADTR2EN3 disabled; IEVTSEL Time based interrupts disabled; SIEN disabled; FFIEN disabled; CLIEN disabled; FLTIEN disabled; 
    PG3EVT = 0x3000008UL;
    // PSS Tied to 0; PPS Not inverted; PSYNC disabled; SWTERM disabled; AQSS None; AQPS Not inverted; TERM Manual Terminate; TSYNCDIS PWM EOC; TQSS None; TQPS Not inverted; LATMOD disabled; SWPCIM PCI acceptance logic; SWPCI Drives '0'; ACP Level-sensitive; TERMPS disabled; BPSEL PWM Generator 1; BPEN disabled; 
    PG3FFPCI = 0x0UL;
    // PSS Comparator 3 output; PPS Not inverted; PSYNC disabled; SWTERM disabled; AQSS None; AQPS Not inverted; TERM Manual Terminate; TSYNCDIS PWM EOC; TQSS None; TQPS Not inverted; LATMOD disabled; SWPCIM PCI acceptance logic; SWPCI Drives '0'; ACP Latched; TERMPS disabled; BPSEL PWM Generator 1; BPEN disabled; 
    PG3FPCI = 0x300001DUL;
    // DBDAT 0x0; FFDAT 0x0; CLDAT 0x0; FLTDAT 0; OSYNC User output overrides occur when specified by UPDMOD bits; OVRDAT 0; OVRENL disabled; OVRENH disabled; SWAP disabled; CLMOD disabled; POLL Active-high; POLH Active-high; PENL enabled; PENH enabled; PMOD Complementary; DTCMPSEL PCI Sync Logic; PPSEN disabled; CAPSRC Software; 
    PG3IOCON = 0xC0200UL;
    // LEB disabled; PLF disabled; PLR disabled; PHF disabled; PHR disabled; 
    PG3LEB = 0x0UL;
    // PER 0x0; 
    PG3PER = 0x0UL;
    // PHASE 0x0; 
    PG3PHASE = 0x0UL;
    // PSS Tied to 0; PPS Not inverted; PSYNC disabled; SWTERM disabled; AQSS None; AQPS Not inverted; TERM Manual Terminate; TSYNCDIS PWM EOC; TQSS None; TQPS Not inverted; LATMOD disabled; SWPCIM PCI acceptance logic; SWPCI Drives '0'; ACP Level-sensitive; TERMPS disabled; BPSEL PWM Generator 1; BPEN disabled; 
    PG3SPCI = 0x0UL;
    // UPDREQ disabled; UPDATE disabled; CAP disabled; TRCLR disabled; TRSET disabled; FFEVT disabled; CLEVT disabled; FLTEVT disabled; SEVT disabled; 
    PG3STAT = 0x0UL;
    // TRIGA NaN; CAHALF disabled; 
    PG3TRIGA = 0x0UL;
    // TRIGB 0x0; CAHALF disabled; 
    PG3TRIGB = 0x0UL;
    // TRIGC 0x0; CAHALF disabled; 
    PG3TRIGC = 0x0UL;
    // CTA1EN disabled; CTA2EN disabled; CTA3EN disabled; CTA4EN disabled; CTA5EN disabled; CTA6EN disabled; CTA7EN disabled; CTA8EN disabled; CTB1EN disabled; CTB2EN disabled; CTB3EN disabled; CTB4EN disabled; CTB5EN disabled; CTB6EN disabled; CTB7EN disabled; CTB8EN disabled; 
    CMBTRIG = 0x0UL;
    // FSCL 0x0; 
    FSCL = 0x0UL;
    // FSMINPER 0x0; 
    FSMINPER = 0x0UL;
    // LFSR 0x0; 
    LFSR = 0x0UL;
    // PWMLFAD disabled; PWMLFA OR; S2APOL Positive Logic; S1APOL Positive Logic; PWMS2A PWM1H; PWMS1A PWM1H; 
    LOGCONA = 0x0UL;
    // PWMLFBD disabled; PWMLFB OR; S2BPOL Positive Logic; S1BPOL Positive Logic; PWMS2B PWM1H; PWMS1B PWM1H; 
    LOGCONB = 0x0UL;
    // PWMLFCD disabled; PWMLFC OR; S2CPOL Positive Logic; S1CPOL Positive Logic; PWMS2C PWM1H; PWMS1C PWM1H; 
    LOGCONC = 0x0UL;
    // PWMLFDD disabled; PWMLFD OR; S2DPOL Positive Logic; S1DPOL Positive Logic; PWMS2D PWM1H; PWMS1D PWM1H; 
    LOGCOND = 0x0UL;
    // PWMLFED disabled; PWMLFE OR; S2EPOL Positive Logic; S1EPOL Positive Logic; PWMS2E PWM1H; PWMS1E PWM1H; 
    LOGCONE = 0x0UL;
    // PWMLFFD disabled; PWMLFF OR; S2FPOL Positive Logic; S1FPOL Positive Logic; PWMS2F PWM1H; PWMS1F PWM1H; 
    LOGCONF = 0x0UL;
    // MDC 0x0; 
    MDC = 0x0UL;
    // MPER 79984; 
    MPER = 0x13870UL;
    // MPHASE 0x0; 
    MPHASE = 0x0UL;
    // MCLKSEL Clock Generator 5; DIVSEL 1:2; LOCK disabled; 
    PCLKCON = 0x1UL;
    // EVTAPGS PG1; EVTASEL PGTRGSEL bits; EVTASYNC disabled; EVTASTRD disabled; EVTAPOL disabled; EVTAOEN disabled; 
    PWMEVTA = 0x0UL;
    // EVTBPGS PG1; EVTBSEL PGTRGSEL bits; EVTBSYNC disabled; EVTBSTRD disabled; EVTBPOL disabled; EVTBOEN disabled; 
    PWMEVTB = 0x0UL;
    // EVTCPGS PG1; EVTCSEL PGTRGSEL bits; EVTCSYNC disabled; EVTCSTRD disabled; EVTCPOL disabled; EVTCOEN disabled; 
    PWMEVTC = 0x0UL;
    // EVTDPGS PG1; EVTDSEL PGTRGSEL bits; EVTDSYNC disabled; EVTDSTRD disabled; EVTDPOL disabled; EVTDOEN disabled; 
    PWMEVTD = 0x0UL;
    // EVTEPGS PG1; EVTESEL PGTRGSEL bits; EVTESYNC disabled; EVTESTRD disabled; EVTEPOL disabled; EVTEOEN disabled; 
    PWMEVTE = 0x0UL;
    // EVTFPGS PG1; EVTFSEL PGTRGSEL bits; EVTFSYNC disabled; EVTFSTRD disabled; EVTFPOL disabled; EVTFOEN disabled; 
    PWMEVTF = 0x0UL;
    
    PWM_GeneratorEOCEventCallbackRegister(&PWM_GeneratorEOCEventCallback);
    
    PWM_CommonEventCallbackRegister(&PWM_CommonEventCallback);
    

}

void PWM_Deinitialize (void)
{
    PWM_Disable();
    
    
    PG1CAP = 0x0UL;
    PG1CLPCI = 0x0UL;
    PG1CON = 0x0UL;
    PG1DC = 0x0UL;
    PG1DCA = 0x0UL;
    PG1DT = 0x0UL;
    PG1EVT = 0x0UL;
    PG1FFPCI = 0x0UL;
    PG1FPCI = 0x0UL;
    PG1IOCON = 0x0UL;
    PG1LEB = 0x0UL;
    PG1PER = 0x0UL;
    PG1PHASE = 0x0UL;
    PG1SPCI = 0x0UL;
    PG1STAT = 0x0UL;
    PG1TRIGA = 0x0UL;
    PG1TRIGB = 0x0UL;
    PG1TRIGC = 0x0UL;
    PG2CAP = 0x0UL;
    PG2CLPCI = 0x0UL;
    PG2CON = 0x0UL;
    PG2DC = 0x0UL;
    PG2DCA = 0x0UL;
    PG2DT = 0x0UL;
    PG2EVT = 0x0UL;
    PG2FFPCI = 0x0UL;
    PG2FPCI = 0x0UL;
    PG2IOCON = 0x0UL;
    PG2LEB = 0x0UL;
    PG2PER = 0x0UL;
    PG2PHASE = 0x0UL;
    PG2SPCI = 0x0UL;
    PG2STAT = 0x0UL;
    PG2TRIGA = 0x0UL;
    PG2TRIGB = 0x0UL;
    PG2TRIGC = 0x0UL;
    PG3CAP = 0x0UL;
    PG3CLPCI = 0x0UL;
    PG3CON = 0x0UL;
    PG3DC = 0x0UL;
    PG3DCA = 0x0UL;
    PG3DT = 0x0UL;
    PG3EVT = 0x0UL;
    PG3FFPCI = 0x0UL;
    PG3FPCI = 0x0UL;
    PG3IOCON = 0x0UL;
    PG3LEB = 0x0UL;
    PG3PER = 0x0UL;
    PG3PHASE = 0x0UL;
    PG3SPCI = 0x0UL;
    PG3STAT = 0x0UL;
    PG3TRIGA = 0x0UL;
    PG3TRIGB = 0x0UL;
    PG3TRIGC = 0x0UL;
    CMBTRIG = 0x0UL;
    FSCL = 0x0UL;
    FSMINPER = 0x0UL;
    LFSR = 0x0UL;
    LOGCONA = 0x0UL;
    LOGCONB = 0x0UL;
    LOGCONC = 0x0UL;
    LOGCOND = 0x0UL;
    LOGCONE = 0x0UL;
    LOGCONF = 0x0UL;
    MDC = 0x0UL;
    MPER = 0x0UL;
    MPHASE = 0x0UL;
    PCLKCON = 0x0UL;
    PWMEVTA = 0x0UL;
    PWMEVTB = 0x0UL;
    PWMEVTC = 0x0UL;
    PWMEVTD = 0x0UL;
    PWMEVTE = 0x0UL;
    PWMEVTF = 0x0UL;
}

void PWM_GeneratorEOCEventCallbackRegister(void (*callback)(enum PWM_GENERATOR genNum))
{
    if(NULL != callback)
    {
        PWM_GeneratorEOCEventHandler = callback;
    }
}

void __attribute__ ((weak)) PWM_GeneratorEOCEventCallback ( enum PWM_GENERATOR genNum )
{ 
    (void)genNum;
} 

void PWM_CommonEventCallbackRegister(void (*callback)(enum PWM_COMMON_EVENT event))
{
    if(NULL != callback)
    {
        PWM_CommonEventHandler = callback;
    }
}

void __attribute__ ((weak)) PWM_CommonEventCallback ( enum PWM_COMMON_EVENT event )
{ 
    (void)event;
} 


void PWM_GeneratorTasks (enum PWM_GENERATOR intGen)
{
    switch(intGen)
    {
        case MOTOR1_PHASE_A:
            if(IFS1bits.PWM1IF == 1)
            {
                if(NULL != PWM_GeneratorEOCEventHandler)
                {
                    (*PWM_GeneratorEOCEventHandler)(intGen);
                }
                IFS1bits.PWM1IF = 0;
            }
            break;
        case MOTOR1_PHASE_B:
            if(IFS1bits.PWM2IF == 1)
            {
                if(NULL != PWM_GeneratorEOCEventHandler)
                {
                    (*PWM_GeneratorEOCEventHandler)(intGen);
                }
                IFS1bits.PWM2IF = 0;
            }
            break;
        case MOTOR1_PHASE_C:
            if(IFS1bits.PWM3IF == 1)
            {
                if(NULL != PWM_GeneratorEOCEventHandler)
                {
                    (*PWM_GeneratorEOCEventHandler)(intGen);
                }
                IFS1bits.PWM3IF = 0;
            }
            break;
        default:
            break;
    }
}

void PWM_CommonEventTasks(enum PWM_COMMON_EVENT event)
{
    switch(event)
    {
        case PWM_EVENT_A:
            if(IFS1bits.PEVTAIF == 1)
            {
                if(NULL != PWM_CommonEventHandler)
                {
                    (*PWM_CommonEventHandler)(event);
                }
            
                // clear the PWM PWM_EVENT_A interrupt flag
                IFS1bits.PEVTAIF = 0;
            }
            break;
        case PWM_EVENT_B:
            if(IFS1bits.PEVTBIF == 1)
            {
                if(NULL != PWM_CommonEventHandler)
                {
                    (*PWM_CommonEventHandler)(event);
                }
            
                // clear the PWM PWM_EVENT_B interrupt flag
                IFS1bits.PEVTBIF = 0;
            }
            break;
        case PWM_EVENT_C:
            if(IFS1bits.PEVTCIF == 1)
            {
                if(NULL != PWM_CommonEventHandler)
                {
                    (*PWM_CommonEventHandler)(event);
                }
            
                // clear the PWM PWM_EVENT_C interrupt flag
                IFS1bits.PEVTCIF = 0;
            }
            break;
        case PWM_EVENT_D:
            if(IFS1bits.PEVTDIF == 1)
            {
                if(NULL != PWM_CommonEventHandler)
                {
                    (*PWM_CommonEventHandler)(event);
                }
            
                // clear the PWM PWM_EVENT_D interrupt flag
                IFS1bits.PEVTDIF = 0;
            }
            break;
        case PWM_EVENT_E:
            if(IFS1bits.PEVTEIF == 1)
            {
                if(NULL != PWM_CommonEventHandler)
                {
                    (*PWM_CommonEventHandler)(event);
                }
            
                // clear the PWM PWM_EVENT_E interrupt flag
                IFS1bits.PEVTEIF = 0;
            }
            break;
        case PWM_EVENT_F:
            if(IFS1bits.PEVTFIF == 1)
            {
                if(NULL != PWM_CommonEventHandler)
                {
                    (*PWM_CommonEventHandler)(event);
                }
            
                // clear the PWM PWM_EVENT_F interrupt flag
                IFS1bits.PEVTFIF = 0;
            }
            break;
        default:
            break;
    }
}
/**
 End of File
*/
