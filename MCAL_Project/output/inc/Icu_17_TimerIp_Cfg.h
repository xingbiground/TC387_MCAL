
/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2020)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Icu_17_TimerIp_Cfg.h                                          **
**                                                                            **
**  VERSION   : 16.0.0                                                        **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:32              !!!IGNORE-LINE!!!           **
**                                                                            **
**  GENERATOR : Build b191017-0938                !!!IGNORE-LINE!!!           **
**                                                                            **
**  BSW MODULE DECRIPTION : NA                                                **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Icu configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of Icu Driver                            **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/


#ifndef ICU_17_TIMERIP_CFG_H
#define ICU_17_TIMERIP_CFG_H
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/*Section to Generate Autosar Specific Version Information*/

#define ICU_17_TIMERIP_AR_RELEASE_MAJOR_VERSION  (4U)


#define ICU_17_TIMERIP_AR_RELEASE_MINOR_VERSION  (2U)


#define ICU_17_TIMERIP_AR_RELEASE_REVISION_VERSION  (2U)

/*Section to Generate Vendor Specific Version Information*/
/* Vendor specific implementation version information */

#define ICU_17_TIMERIP_SW_MAJOR_VERSION   (20U)


#define ICU_17_TIMERIP_SW_MINOR_VERSION   (25U)


#define ICU_17_TIMERIP_SW_PATCH_VERSION   (0U)

/*
Configuration : ICU_17_TIMERIP_SAFETY_ENABLE
Pre-processor switch to enable/disable the ICU driver safety features.
*/

#define ICU_17_TIMERIP_SAFETY_ENABLE (STD_OFF)
/*
Configuration : ICU_17_TIMERIP_INITCHECK_API
Pre-processor switch to enable/disable the ICU init check API.
*/

#define ICU_17_TIMERIP_INITCHECK_API (STD_OFF)
/* ICU026: General Configuration */
/*
Configuration to decide the mode of execution of Run Time API's
*/

#define ICU_17_TIMERIP_RUNTIME_API_MODE     ICU_17_TIMERIP_MCAL_SUPERVISOR

/*
Configuration to decide the mode of execution of Init and DeInit API's
*/

#define ICU_17_TIMERIP_INIT_DEINIT_API_MODE  ICU_17_TIMERIP_MCAL_SUPERVISOR

/*
Configuration: ICU_17_TIMERIP_DEV_ERROR_DETECT
Adds/removes the Development Error Detection 
from the code 
- if STD_ON, Development error detection is enabled
- if STD_OFF, Development error detection is disabled
*/

#define ICU_17_TIMERIP_DEV_ERROR_DETECT (STD_OFF)
/*
Configuration: ICU_17_TIMERIP_RUNTIME_ERROR_DETECT
Adds/removes the Runtime Error Detection 
from the code 
- if STD_ON, Runtime error detection is enabled
- if STD_OFF, Runtime error detection is disabled
*/

#define ICU_17_TIMERIP_RUNTIME_ERROR_DETECT           (STD_OFF)

/*
Configuration: ICU_17_TIMERIP_MULTICORE_ERROR_DETECT
Adds/removes the Multi-Core Development Error Detection 
from the code 
- if STD_ON, Multi-Core Development error detection is enabled
- if STD_OFF, Multi-Core Development error detection is disabled
*/

#define ICU_17_TIMERIP_MULTICORE_ERROR_DETECT (STD_OFF)
/*
Configuration: ICU_17_TIMERIP_REPORT_WAKEUP_SOURCE
Preprocessor switch to enable/disable the wakeup source reporting
- if STD_ON, Reports wakeup to higher layer
- if STD_OFF, Reporting is switched off
*/

#define ICU_17_TIMERIP_REPORT_WAKEUP_SOURCE (STD_OFF)
/*
Configuration: ICU_17_TIMERIP_DE_INIT_API
Adds/removes Icu_DeInit API 
from the code 
- if STD_ON, Icu_DeInit is enabled
- if STD_OFF, Icu_DeInit is disabled
*/

#define ICU_17_TIMERIP_DE_INIT_API (STD_OFF)
/*
Configuration: ICU_17_TIMERIP_DISABLE_WAKEUP_API
Adds/removes Icu_DisableWakeup API 
from the code 
- if STD_ON, Icu_DisableWakeup is enabled
- if STD_OFF, Icu_DisableWakeup is disabled
*/

#define ICU_17_TIMERIP_DISABLE_WAKEUP_API (STD_OFF)
/*
Configuration: ICU_17_TIMERIP_ENABLE_WAKEUP_API
Adds/removes Icu_EnableWakeup API 
from the code 
- if STD_ON, Icu_EnableWakeup is enabled
- if STD_OFF, Icu_EnableWakeup is disabled
*/

#define ICU_17_TIMERIP_ENABLE_WAKEUP_API (STD_OFF)
/*
Configuration: ICU_17_TIMERIP_EDGE_COUNT_API
Adds/removes Edge Count Measurement APIs 
from the code 
- if STD_ON, Icu_EnableEdgeCount, Icu_DisableEdgeCount
Icu_ResetEdgeCount, Icu_GetEdgeNumbers is enabled
- if STD_OFF, Icu_EnableEdgeCount, Icu_DisableEdgeCount
Icu_ResetEdgeCount, Icu_GetEdgeNumbers is disabled
*/

#define ICU_17_TIMERIP_EDGE_COUNT_API (STD_OFF)
/*
Configuration: ICU_17_TIMERIP_GET_DUTY_CYCLE_VALUES_API
Adds/removes Icu_GetDutyCycleValues API 
from the code 
- if STD_ON, Icu_GetDutyCycleValues is enabled
- if STD_OFF, Icu_GetDutyCycleValues is disabled
*/

#define ICU_17_TIMERIP_GET_DUTY_CYCLE_VALUES_API (STD_ON)
/*
Configuration: ICU_17_TIMERIP_GET_INPUT_STATE_API
Adds/removes Icu_GetInputState API 
from the code 
- if STD_ON, Icu_GetInputState is enabled
- if STD_OFF, Icu_GetInputState is disabled
*/

#define ICU_17_TIMERIP_GET_INPUT_STATE_API (STD_OFF)
/*
Configuration: ICU_17_TIMERIP_GET_TIME_ELAPSED_API
Adds/removes Icu_GetTimeElapsed API 
from the code 
- if STD_ON, Icu_GetTimeElapsed is enabled
- if STD_OFF, Icu_GetTimeElapsed is disabled
*/

#define ICU_17_TIMERIP_GET_TIME_ELAPSED_API (STD_OFF)
/*
Configuration: ICU_17_TIMERIP_GET_VERSION_INFO_API
Adds/removes Icu_GetVersionInfo API 
from the code 
- if STD_ON, Icu_GetVersionInfo is enabled
- if STD_OFF, Icu_GetVersionInfo is disabled
*/

#define ICU_17_TIMERIP_GET_VERSION_INFO_API (STD_OFF)
/*
Configuration: ICU_17_TIMERIP_SET_MODE_API
Adds/removes Icu_SetMode API 
from the code 
- if STD_ON, Icu_SetMode is enabled
- if STD_OFF, Icu_SetMode is disabled
*/

#define ICU_17_TIMERIP_SET_MODE_API (STD_OFF)
/*
Configuration: ICU_17_TIMERIP_TIMESTAMP_API
Adds/removes Time Stamp APIs 
from the code 
- if STD_ON, Icu_StartTimestamp, Icu_StopTimestamp
Icu_GetTimestampIndex is enabled
- if STD_OFF, Icu_StartTimestamp, Icu_StopTimestamp
Icu_GetTimestampIndex is disabled
*/

#define ICU_17_TIMERIP_TIMESTAMP_API (STD_OFF)
/*
Configuration: ICU_17_TIMERIP_SIGNAL_MEASUREMENT_API
Adds/removes Signal Measurement APIs 
from the code 
- if STD_ON, Icu_StartSignalMeasurement, Icu_StopSignalMeasurement
are enabled
- if STD_OFF, Icu_StartSignalMeasurement, Icu_StopSignalMeasurement
are disabled
*/

#define ICU_17_TIMERIP_SIGNAL_MEASUREMENT_API (STD_ON)
/*
Configuration: ICU_17_TIMERIP_EDGE_DETECT_API
Adds/removes Edge Detect APIs 
from the code 
- if STD_ON, Edge Detection functionality is enabled
- if STD_OFF, Edge Detection functionality is disabled
*/

#define ICU_17_TIMERIP_EDGE_DETECT_API (STD_OFF)
/*
Configuration: ICU_17_TIMERIP_WAKEUP_FUNCTIONALITY_API
Adds/removes the service Icu_CheckWakeup() 
from the code 
- if ON, the service Icu_CheckWakeup() is enabled
- if OFF, the service Icu_CheckWakeup() is disabled
*/

#define ICU_17_TIMERIP_WAKEUP_FUNCTIONALITY_API (STD_OFF)
/*
Configuration: ICU_17_TIMERIP_INCREMENTAL_INTERFACE_API
Adds / removes the services related to incremental interface mode 
from the code 
- if ON, Incremental Interface mode API can be used.
- if OFF, Incremental Interface mode API can not be used.
*/

#define ICU_17_TIMERIP_INCREMENTAL_INTERFACE_API (STD_OFF)
/*
Configuration: ICU_17_TIMERIP_TIMEOUT_DETECTION_API
Adds / removes the service to set the timeout value for a GTM TIM channel.
- if ON, Icu_17_TimerIp_SetTimeoutValue API can be used.
- if OFF, Icu_17_TimerIp_SetTimeoutValue API can not be used.
*/

#define ICU_17_TIMERIP_TIMEOUT_DETECTION_API (STD_OFF)
/*
Configuration: ICU_17_TIMERIP_INSTANCE_ID
InstanceId of ICU module
*/
/* InstanceId of ICU module  */

#define ICU_17_TIMERIP_INSTANCE_ID       ((uint8)0)

/*
Core 0 Configurations    
*/

/*MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars,
in generated code is due to Autosar Naming constraints for symbolic name 
generation*/
/*MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars,
in generated code is due to Autosar Naming constraints for symbolic name 
generation*/
/*MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars,
in generated code is due to Autosar Naming constraints for symbolic name 
generation*/
/*MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars,
in generated code is due to Autosar Naming constraints for symbolic name 
generation*/
#ifndef IcuConf_IcuChannel_SignalMeas
/*MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars,
in generated code is due to Autosar Naming constraints for symbolic name 
generation*/
/*MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars,
in generated code is due to Autosar Naming constraints for symbolic name 
generation*/
/*MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars,
in generated code is due to Autosar Naming constraints for symbolic name 
generation*/
/*MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars,
in generated code is due to Autosar Naming constraints for symbolic name 
generation*/
#define IcuConf_IcuChannel_SignalMeas       ((Icu_17_TimerIp_ChannelType)0U)
#endif

/* Core 0 Configurations summary */

/*MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars,
in generated code is due to Autosar Naming constraints for symbolic name 
generation*/
/*MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars,
in generated code is due to Autosar Naming constraints for symbolic name 
generation*/
/*MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars,
in generated code is due to Autosar Naming constraints for symbolic name 
generation*/
/*MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars,
in generated code is due to Autosar Naming constraints for symbolic name 
generation*/
#define ICU_17_TIMERIP_MAX_CHANNELS_CORE0                   (1U)


/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define ICU_17_TIMERIP_CHNL_DATA_MAX_CHANNELS_CORE0         (1U)

/*
Core 1 Configurations    
*/
/* Core 1 Configurations summary */

/*MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars,
in generated code is due to Autosar Naming constraints for symbolic name 
generation*/
/*MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars,
in generated code is due to Autosar Naming constraints for symbolic name 
generation*/
/*MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars,
in generated code is due to Autosar Naming constraints for symbolic name 
generation*/
/*MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars,
in generated code is due to Autosar Naming constraints for symbolic name 
generation*/
#define ICU_17_TIMERIP_MAX_CHANNELS_CORE1                   (0U)


/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define ICU_17_TIMERIP_CHNL_DATA_MAX_CHANNELS_CORE1         (0U)

/*
Core 2 Configurations    
*/
/* Core 2 Configurations summary */

/*MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars,
in generated code is due to Autosar Naming constraints for symbolic name 
generation*/
/*MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars,
in generated code is due to Autosar Naming constraints for symbolic name 
generation*/
/*MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars,
in generated code is due to Autosar Naming constraints for symbolic name 
generation*/
/*MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars,
in generated code is due to Autosar Naming constraints for symbolic name 
generation*/
#define ICU_17_TIMERIP_MAX_CHANNELS_CORE2                   (0U)


/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define ICU_17_TIMERIP_CHNL_DATA_MAX_CHANNELS_CORE2         (0U)

/*
Core 3 Configurations    
*/
/* Core 3 Configurations summary */

/*MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars,
in generated code is due to Autosar Naming constraints for symbolic name 
generation*/
/*MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars,
in generated code is due to Autosar Naming constraints for symbolic name 
generation*/
/*MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars,
in generated code is due to Autosar Naming constraints for symbolic name 
generation*/
/*MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars,
in generated code is due to Autosar Naming constraints for symbolic name 
generation*/
#define ICU_17_TIMERIP_MAX_CHANNELS_CORE3                   (0U)


/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define ICU_17_TIMERIP_CHNL_DATA_MAX_CHANNELS_CORE3         (0U)

/*
Core 4 Configurations    
*/
/* Core 4 Configurations summary */

/*MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars,
in generated code is due to Autosar Naming constraints for symbolic name 
generation*/
/*MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars,
in generated code is due to Autosar Naming constraints for symbolic name 
generation*/
/*MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars,
in generated code is due to Autosar Naming constraints for symbolic name 
generation*/
/*MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars,
in generated code is due to Autosar Naming constraints for symbolic name 
generation*/
#define ICU_17_TIMERIP_MAX_CHANNELS_CORE4                   (0U)


/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define ICU_17_TIMERIP_CHNL_DATA_MAX_CHANNELS_CORE4         (0U)

/*
Core 5 Configurations    
*/
/* Core 5 Configurations summary */

/*MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars,
in generated code is due to Autosar Naming constraints for symbolic name 
generation*/
/*MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars,
in generated code is due to Autosar Naming constraints for symbolic name 
generation*/
/*MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars,
in generated code is due to Autosar Naming constraints for symbolic name 
generation*/
/*MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars,
in generated code is due to Autosar Naming constraints for symbolic name 
generation*/
#define ICU_17_TIMERIP_MAX_CHANNELS_CORE5                   (0U)


/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define ICU_17_TIMERIP_CHNL_DATA_MAX_CHANNELS_CORE5         (0U)

/***************************************************************************
TOTAL NUMBER OF CONFIGURED CHANNELS 
****************************************************************************/

#define ICU_17_TIMERIP_MAX_CHANNELS         (1U)

/* Macro to idntify single core execution */
#define  ICU_17_TIMERIP_SINGLE_CORE (STD_ON)
#define  ICU_17_TIMERIP_SINGLE_CORE_ID (0U)
/*
Derived parameters
Vendor specific configuration switches
Format : ICU_<HW>_<MODE>_USED  (Vendor Specific)
HW : TIM, CCU6, ERU, GPT12
STD_ON: <HW> is used for <MODE>.
STD_OFF: <HW> is not used for <MODE>.
*/
/* GTM TIM hardware resource usage */

#define ICU_17_TIMERIP_GTM_TIM_USED (STD_OFF)
/* CCU6 hardware resource usage */

#define ICU_17_TIMERIP_CCU6_USED (STD_ON)

/* CCU6 Kerenl-0 allocation to ICU */
#define ICU_17_TIMERIP_CCU6_KERNEL0_USED (STD_OFF)

/* CCU6 Kerenl-1 allocation to ICU */
#define ICU_17_TIMERIP_CCU6_KERNEL1_USED (STD_ON)
/* GPT12 hardware resource usage */

#define ICU_17_TIMERIP_GPT12_USED (STD_OFF)
/* ERU hardware resource usage */

#define ICU_17_TIMERIP_ERU_SIGEDGE_USED (STD_OFF)
#endif  /* ICU_17_TIMERIP_CFG_H */
