/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2023)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Mcu_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 21.0.0                                                         **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:31         !!!IGNORE-LINE!!!                **
**                                                                            **
**  GENERATOR : Build b191017-0938             !!!IGNORE-LINE!!!              **
**                                                                            **
**  BSW MODULE DECRIPTION : Mcu.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Mcu configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of Mcu Driver, AUTOSAR Release 4.2.2     **
**                     and 4.4.0                                              **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef MCU_CFG_H
#define MCU_CFG_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/* Autosar version of the module */
#define MCU_AS_VERSION (422)

/* AUTOSAR specification version numbers */
#define MCU_AR_RELEASE_MAJOR_VERSION      (4U)
#define MCU_AR_RELEASE_MINOR_VERSION      (2U)
#define MCU_AR_RELEASE_REVISION_VERSION   (2U)

/* Vendor specific implementation version information */
#define MCU_SW_MAJOR_VERSION   (20U)
#define MCU_SW_MINOR_VERSION   (25U)
#define MCU_SW_PATCH_VERSION   (0U)

/* MCU_MCAL_SUPERVISOR  */
/* Mcu Operation in Supervisory Mode  */
#define MCU_MCAL_SUPERVISOR             (0U)

/* MCU_MCAL_USER1  */
/* Mcu Operation in User 1 Mode  */
#define MCU_MCAL_USER1                  (1U)


/*
  Configuration: MCU_DEV_ERROR_DETECT
  Preprocessor switch for enabling the development error detection and
  reporting.
  ON  : DET is Enabled
  OFF : DET is Disabled
*/
#define  MCU_DEV_ERROR_DETECT (STD_ON)

/*
  Configuration: MCU_MULTICORE_ERROR_DETECT
  Preprocessor switch for enabling the multicore error detection and
  reporting.
  ON  : Multicore error detection and reporting is Enabled
  OFF : Multicore error detection and reporting is Disabled
*/
#define  MCU_MULTICORE_ERROR_DETECT (STD_ON)

/*
  Configuration: MCU_VERSION_INFO_API
  Preprocessor switch to enable / disable the API to read out the modules
  version information.
  ON  : version info API is enabled
  OFF : version info API is disabled
*/
#define MCU_VERSION_INFO_API (STD_OFF)
/*
  Configuration : MCU_DISTRIBUTE_PLL_CLOCK_API
  Preprocessor switch to enable / disable the use of the
  API Mcu_DistributePllClock()
  ENABLED  : Mcu_DistributePllClock API is available
  DISABLED : Mcu_DistributePllClock API is not available
*/
#define  MCU_DISTRIBUTE_PLL_CLOCK_API (STD_ON)

/*
  Configuration : MCU_INIT_CLOCK_API
  Preprocessor switch to enable / disable the use of the
  API Mcu_InitClock()
  ENABLED  : Mcu_InitClock API is available
  DISABLED : Mcu_InitClock API is not available
*/
#define  MCU_INIT_CLOCK_API (STD_ON)

/*
  Configuration : MCU_PERFORM_RESET_API
  Preprocessor switch to enable / disable the use of the
  API Mcu_PerformReset()
  ENABLED  : Mcu_PerformReset API is available
  DISABLED : Mcu_PerformReset API is not available
*/
#define  MCU_PERFORM_RESET_API (STD_ON)
/*
  Configuration : MCU_GET_RAM_STATE_API (McuGetRamStateApi)
  Pre-processor switch to enable/disable the API Mcu_GetRamState.
  (If the H/W does not support the functionality, this parameter
  can be used to disable the API).
*/
#define MCU_GET_RAM_STATE_API (STD_OFF)
/*
  Configuration : MCU_CLR_COLD_RESET_STAT_API (McuClearColdResetStatusApi)
  Pre-processor switch to enable/disable the API Mcu_ClearColdResetStatus.
*/
#define MCU_CLR_COLD_RESET_STAT_API (STD_OFF)

/*
  Configuration : MCU_TRAP_API (McuIfxTrapApi)
  Pre-processor switch to Enables/Disables availability of trap related APIs
  defined by IFX namely Mcu_GetTrapCause, Mcu_SetTrapRequest and
  Mcu_ClearTrapRequest.
*/
#define MCU_TRAP_API (STD_OFF)
/*
  Configuration : MCU_CPU_CCUCON_UPDATE_API (McuIfxCpuCcuconApi)
  This parameter Enables/Disables availability of Cpu Ccucon register
  update API defined by IFX namely Mcu_UpdateCpuCcuconReg
*/
#define MCU_CPU_CCUCON_UPDATE_API (STD_OFF)

/*
  Configuration : MCU_LOW_POWER_MODE_API (McuIfxLpmApi)
  Pre-processor switch to Enables/Disables availability of low power mode APIs
  defined by IFX namely Mcu_GetCpuIdleModeInitiator, Mcu_GetCpuState,
  Mcu_GetWakeupCause and Mcu_ClearWakeupCause.
*/
#define MCU_LOW_POWER_MODE_API (STD_OFF)

/*
  Configuration : MCU_DEINIT_API (McuIfxDeInitApi)
  Pre-processor switch to Enables/Disables availability of
  Mcu Deinitialization API - Mcu_DeInit.
*/
#define MCU_DEINIT_API (STD_OFF)

/*
  Configuration : MCU_CLK_SRC_FAILURE_NOTIF_API
                                   (McuClockSourceFailureNotification)
  Pre-processor switch for availibility of Clock failure related Production Errors
  notification function. ENABLED Clock failure related Production Errors are reported
  DISABLED Clock failure related Production Errors are not reported.
*/

#define MCU_CLK_SRC_FAILURE_NOTIF_API (STD_OFF)

/*
    Configuration : MCU_SAFETY_ENABLE
    Pre-processor switch to enable/disable the MCU driver safety features.
*/
#define MCU_SAFETY_ENABLE (STD_OFF)

#define MCU_INITCHECK_API (STD_OFF)

#define MCU_INIT_DEINIT_API_MODE (MCU_MCAL_SUPERVISOR)

#define MCU_RUNTIME_API_MODE (MCU_MCAL_SUPERVISOR)
/*
    Configuration: MCU_GTM_USED
    This parameter defines if GTM module is used by modules.
*/
  #define MCU_GTM_USED (STD_ON)

  /*
  Configuration: MCU_GTM_NO_OF_TOM_AVAILABLE
  This parameter defines no of TOM units available [0...6]
*/
#define MCU_GTM_NO_OF_TOM_AVAILABLE  (5U)

/*
    Configuration: MCU_GTM_NO_OF_ATOM_AVAILABLE
    This parameter defines no of Atom units available [0...12]
*/
#define MCU_GTM_NO_OF_ATOM_AVAILABLE  (9U)

/*
    Configuration: MCU_GTM_NO_OF_TIM_AVAILABLE
    This parameter defines no of Tim units available [0...12]
*/
#define MCU_GTM_NO_OF_TIM_AVAILABLE  (7U)

/*
    Configuration: MCU_GTM_NO_OF_TBU_CH_AVAILABLE
    This parameter defines no of TOM units available [0...3]
*/
#define MCU_GTM_NO_OF_TBU_CH_AVAILABLE  (4U)

/*
    Configuration: MCU_GTM_NO_OF_CCM_AVAILABLE
    This parameter defines no of CCM clusters available [0...12]
*/
#define MCU_GTM_NO_OF_CCM_AVAILABLE  (9U)

/*
    Configuration: MCU_NO_OF_TOUTSEL_AVAILABLE
    This parameter defines no of TOUTSEL registers available [0...33]
*/
#define MCU_GTM_NO_OF_TOUTSEL_AVAILABLE  (34U)

/*
    Configuration: MCU_GTM_TO_DSADC_TRIG_AVAILABLE
    This parameter specifies whether GTM to DSADC trigger is available or not.
*/
#define MCU_GTM_TO_DSADC_TRIG_AVAILABLE  (STD_ON)

#define MCU_GTM_TO_DSADC_TRIG1  (STD_ON)

#define MCU_TBU_CH_EN_MSK        (0x000000ffU)

#define MCU_GTM_CLS_CLK_CFG_RESET_VAL        (0x0002aaaaU)


/*
    Configuration: MCU_MAIN_OSC_FREQ  (MHz)
    This parameter defines main oscillator frequency in MHz
*/
#define MCU_MAIN_OSC_FREQ  (20U)

/*
    Configuration: MCU_SYSCLK_FREQ  (MHz)
    This parameter defines SYSCLK frequency in MHz
*/
#define MCU_SYSCLK_FREQ  (20U)

/*
    Configuration: MCU_BACKUP_FREQ  (MHz)
    This parameter defines back up frequency in MHz
*/
#define MCU_BACKUP_FREQ    (100U)

/* This parameter defines whether CCU6 kernel 0 is used or not*/
#define MCU_CCU60_USED     (STD_OFF)

/* This parameter defines whether CCU6 kernel 1 is used or not*/

#define MCU_CCU61_USED     (STD_ON)

/* This parameter defines whether GPT1 Block is used or not*/
#define MCU_GPT1_USED     (STD_OFF)

/* This parameter defines whether GPT1 Block is used or not*/
#define MCU_GPT2_USED     (STD_OFF)

/* OSC Frequency Value
    This bit field defines the divider value that generates
    the reference clock that is supervised by the
    oscillator watchdog.
    fOSCREF = OSCCON.OSCVAL - 1 + 16 MHz.
    Equation is OSCVAL = (fOSCREF - 15). */
#define MCU_OSCVAL_REG_VALUE  (0x5U)

#define MCU_SYSCLK_OSCVAL     (0x5U)

/*
    MACRO : MCU_OSC_MODE
    configured Oscillator mode
    EXT_CRYSTAL_CERAMIC_RES_MODE - 0
    EXT_INPUT_CLOCK_MODE         - 2
    OSC_DISABLED_MODE            - 3
*/
#define MCU_OSC_MODE    (0U)

/*
    MACRO : MCU_OSC_CAPACITANCE_EN
    configured Oscillator capacitance information
*/
#define MCU_OSC_CAPACITANCE_EN     (0x00000000U)

/* Master Core for triggering System Modes for controller
 1 - Core 0
 2 - Core 1
 3 - Core 2
 4 - Core 3
 5 - Core 4
 6 - Core 5
 7 - All Cores Unanimously
*/
#define MCU_SYSTEM_CORE_NOT_DEFINED     (0U)

#define MCU_SYSTEM_MODE_CORE            (MCU_SYSTEM_CORE_NOT_DEFINED)

/* Master Core for triggering Idle Mode for controller
 1 - Core 0
 2 - Core 1
 3 - Core 2
 4 - Core 3
 5 - Core 4
 6 - Core 5
 0 - All Cores Individually
*/
#define MCU_IDLE_CORE_NOT_DEFINED         (7U)
#define MCU_IDLE_MODE_CORE                (0U)

/* Standby Mode Ram enable configuration */
#define MCU_NO_OF_STDBY_RAM_BLK       (0U)

/*
  Macro to write into Trap disable register
*/
#define MCU_TRAPDIS0_RESET_VAL     (0xFFFFFFFFU)

/*
    Container: McuModeSettingConf
    Multiplicity: 1 - *
    Configuration Options:
    For MCU power down modes Mcu_ModeType :
    IDLE Mode: CPU clock is disabled and peripheral clock is running
    as configured
*/
#define MCU_IDLE             (0U)

/*
    Configuration Options:
    For MCU power down modes Mcu_ModeType :
    SLEEP Mode: CPU clock is disabled and Peripherals go to sleep if
    configured for sleep mode
*/
#define MCU_SLEEP            (1U)

/*
    Configuration Options:
    For MCU power down modes Mcu_ModeType :
*/
#define MCU_STANDBY          (2U)

/*
    Maximum number of modes which are configurable is 3
*/
#define MCU_MAX_NO_MODES     (3U)

/*
  Configuration: Mode Id
  This id corresponds to the container name of the McuModeSettingConfiguration
  Use this as the parameter for API: Mcu_SetMode
*/
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#ifndef McuConf_McuModeSettingConf_McuModeSettingConf_0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  #define McuConf_McuModeSettingConf_McuModeSettingConf_0  (0U)
#endif

/*
  Container: McuClockSettingConfig
  Multiplicity: 1 -*
*/
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#ifndef McuConf_McuClockSettingConfig_McuClockSettingConfig_0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  #define McuConf_McuClockSettingConfig_McuClockSettingConfig_0  (0U)
#endif
/*
  Container: McuRamSectorSettingConf
  Multiplicity: 0 -*
*/

/*
  Container: McuResetReasonConf
  Multiplicity: 1-1
*/
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#ifndef McuConf_McuResetReasonConf_MCU_ESR0_RESET
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  #define McuConf_McuResetReasonConf_MCU_ESR0_RESET  (0U)
#endif
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#ifndef McuConf_McuResetReasonConf_MCU_ESR1_RESET
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  #define McuConf_McuResetReasonConf_MCU_ESR1_RESET  (1U)
#endif
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#ifndef McuConf_McuResetReasonConf_MCU_SMU_RESET
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  #define McuConf_McuResetReasonConf_MCU_SMU_RESET  (2U)
#endif
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#ifndef McuConf_McuResetReasonConf_MCU_SW_RESET
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  #define McuConf_McuResetReasonConf_MCU_SW_RESET  (3U)
#endif
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#ifndef McuConf_McuResetReasonConf_MCU_STM0_RESET
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  #define McuConf_McuResetReasonConf_MCU_STM0_RESET  (4U)
#endif
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#ifndef McuConf_McuResetReasonConf_MCU_STM1_RESET
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  #define McuConf_McuResetReasonConf_MCU_STM1_RESET  (5U)
#endif
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#ifndef McuConf_McuResetReasonConf_MCU_STM2_RESET
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  #define McuConf_McuResetReasonConf_MCU_STM2_RESET  (6U)
#endif
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#ifndef McuConf_McuResetReasonConf_MCU_STM3_RESET
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  #define McuConf_McuResetReasonConf_MCU_STM3_RESET  (7U)
#endif
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#ifndef McuConf_McuResetReasonConf_MCU_STM4_RESET
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  #define McuConf_McuResetReasonConf_MCU_STM4_RESET  (8U)
#endif
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#ifndef McuConf_McuResetReasonConf_MCU_STM5_RESET
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  #define McuConf_McuResetReasonConf_MCU_STM5_RESET  (9U)
#endif
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#ifndef McuConf_McuResetReasonConf_MCU_POWER_ON_RESET
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  #define McuConf_McuResetReasonConf_MCU_POWER_ON_RESET  (10U)
#endif
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#ifndef McuConf_McuResetReasonConf_MCU_CB0_RESET
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  #define McuConf_McuResetReasonConf_MCU_CB0_RESET  (11U)
#endif
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#ifndef McuConf_McuResetReasonConf_MCU_CB1_RESET
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  #define McuConf_McuResetReasonConf_MCU_CB1_RESET  (12U)
#endif
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#ifndef McuConf_McuResetReasonConf_MCU_CB3_RESET
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  #define McuConf_McuResetReasonConf_MCU_CB3_RESET  (13U)
#endif
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#ifndef McuConf_McuResetReasonConf_MCU_EVRC_RESET
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  #define McuConf_McuResetReasonConf_MCU_EVRC_RESET  (14U)
#endif
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#ifndef McuConf_McuResetReasonConf_MCU_EVR33_RESET
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  #define McuConf_McuResetReasonConf_MCU_EVR33_RESET  (15U)
#endif
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#ifndef McuConf_McuResetReasonConf_MCU_SUPPLY_WDOG_RESET
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  #define McuConf_McuResetReasonConf_MCU_SUPPLY_WDOG_RESET  (16U)
#endif
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#ifndef McuConf_McuResetReasonConf_MCU_STBYR_RESET
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  #define McuConf_McuResetReasonConf_MCU_STBYR_RESET  (17U)
#endif
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#ifndef McuConf_McuResetReasonConf_MCU_LBIST_RESET
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  #define McuConf_McuResetReasonConf_MCU_LBIST_RESET  (18U)
#endif
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#ifndef McuConf_McuResetReasonConf_MCU_RESET_MULTIPLE
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  #define McuConf_McuResetReasonConf_MCU_RESET_MULTIPLE  (254U)
#endif
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#ifndef McuConf_McuResetReasonConf_MCU_RESET_UNDEFINED
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  #define McuConf_McuResetReasonConf_MCU_RESET_UNDEFINED  (255U)
#endif
/* Production Error reporting enable/disabled macro */
#define MCU_ENABLE_DEM_REPORT  (1U)
#define MCU_DISABLE_DEM_REPORT (0U)

/* Production Error enable/disable for Oscillator Failure */
#define MCU_E_OSC_FAILURE_DEM_REPORT     (MCU_DISABLE_DEM_REPORT)

/* Production Error enable/disable for system PLL Timeout */
#define MCU_E_SYSTEM_PLL_TIMEOUT_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)


/* Production Error enable/disable for Peripheral PLL Timeout */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define MCU_E_PERIPHERAL_PLL_TIMEOUT_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)

/* Production Error enable/disable for system PLL lock loss */
#define MCU_E_SYSTEM_PLL_LOCK_LOSS_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)

/* Production Error enable/disable for peripheral PLL lock loss */
#define MCU_E_PERIPHERAL_PLL_LOCK_LOSS_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)

/* Production Error enable/disable for GTM module enable failure */
#define MCU_E_GTM_CLC_ENABLE_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)

/* Production Error enable/disable for GTM module disable failure */
#define MCU_E_GTM_CLC_DISABLE_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)

/* Production Error enable/disable for CONVCTRL module enable failure */
#define MCU_E_CONVCTRL_CLC_ENABLE_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)

/* Production Error enable/disable for CONVCTRL module disable failure */
#define MCU_E_CONVCTRL_CLC_DISABLE_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)

/* Production Error enable/disable for CCUCON0 update inability (LCK bit set) */
#define MCU_E_CCUCON_UPDATE_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)

/* Production Error enable/disable for CCU6 kernel enable */
#define MCU_E_CCU6_CLC_ENABLE_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)

/* Production Error enable/disable for CCU6 kernel disable */
#define MCU_E_CCU6_CLC_DISABLE_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)

/* Production Error enable/disable for GPT12 module enable */
#define MCU_E_GPT12_CLC_ENABLE_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)

/* Production Error enable/disable for GPT12 module disable */
#define MCU_E_GPT12_CLC_DISABLE_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)


/* Production Error enable/disable for PMSWCRx update inability (BUSY bit) */
#define MCU_E_PMSWCR_UPDATE_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)

    
#define MCU_E_ERR_DEM_REPORTING      (STD_OFF)
/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/

#endif /* end of MCU_CFG_H */

