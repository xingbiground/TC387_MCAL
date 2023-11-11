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
**  FILENAME  : Gpt_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 10.0.0                                                        **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:32       !!!IGNORE-LINE!!!                  **
**                                                                            **
**  GENERATOR : Build b191017-0938           !!!IGNORE-LINE!!!                **
**                                                                            **
**  BSW MODULE DECRIPTION : Gpt.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : GPT configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of GPT Driver, AUTOSAR                   **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

#ifndef  GPT_CFG_H
#define  GPT_CFG_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/


/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/* Section to Generate Autosar Specific Version Information */


#define GPT_AR_RELEASE_MAJOR_VERSION                      (4U)
#define GPT_AR_RELEASE_MINOR_VERSION                      (2U)
#define GPT_AR_RELEASE_REVISION_VERSION                   (2U)

/* Section to Generate Vendor Specific Version Information */
/* Vendor specific implementation version information */
#define GPT_SW_MAJOR_VERSION                              (20U)
#define GPT_SW_MINOR_VERSION                              (25U)
#define GPT_SW_PATCH_VERSION                              (0U)

/*
Container : GptDriverConfiguration
This container contains the channel-wide configuration (parameters) of
the GPT Driver.
*/

/*
Configuration: GPT_SAFETY_ENABLE
Preprocessor switch to enable/disable the safety check and reporting.
- if STD_ON, Enable safety check
- if STD_OFF, Disable safety check
*/
#define GPT_SAFETY_ENABLE                                 (STD_ON)

/*
Configuration: GPT_INITCHECK_API
Adds/removes the service Gpt_InitCheck() from the code
- if STD_ON, Gpt_InitCheck() can be used
- if STD_OFF, Gpt_InitCheck() can not be used
*/
#define GPT_INITCHECK_API                                 (STD_ON)

/*
Configuration: GPT_MULTICORE_ERROR_DETECT
Preprocessor switch to enable/disable the
multicore development error detection and reporting.
- if STD_ON, Enable multicore development error detection
- if STD_OFF, Disable multicore development error detection
*/

#define GPT_MULTICORE_ERROR_DETECT                        (STD_OFF)

/*
Configuration: GPT_DEV_ERROR_DETECT
Preprocessor switch to enable/disable the development error detection and
reporting.
- if STD_ON, Enable development error detection
- if STD_OFF, Disable development error detection
*/
#define GPT_DEV_ERROR_DETECT                              (STD_ON)


#define GPT_RUNTIME_ERROR_DETECT                          (STD_OFF)


/*
Configuration: GPT_REPORT_WAKEUP_SOURCE
Preprocessor switch to enable/disable the wakeup source reporting
- if STD_ON, Report wakeup source
- if STD_OFF, Dont report wakeup source
*/
#define GPT_REPORT_WAKEUP_SOURCE                          (STD_OFF)

/*
Configuration: GPT_PREDEF_TIMER_100US_32BIT_EN
Preprocessor switch to enable/disable the GPT Predef Timer 100us 32bit.
- if STD_ON, Enable 100us 32bit predef timer
- if STD_OFF, Disable 100us 32bit predef timer
*/
#define GPT_PREDEF_TIMER_100US_32BIT_EN                   (STD_OFF)

/*
Configuration: GPT_PREDEF_TIMER_1US_xBIT_EN
Specifies the grade of enabling the GPT Predef Timers with 1us tick duration.
- if STD_ON, Enable 1us xBit predef timer
- if STD_OFF, Disable 1us xBit predef timer
*/
#define GPT_PREDEF_TIMER_1US_16BIT_EN                     (STD_OFF)
#define GPT_PREDEF_TIMER_1US_24BIT_EN                     (STD_OFF)
#define GPT_PREDEF_TIMER_1US_32BIT_EN                     (STD_OFF)

/*
Configuration: GPT_PREDEF_EXTRA_CH_1US and GPT_PREDEF_EXTRA_CH_100US
Preprocessor switch to enable/disable the extra channel to use with predefined
timer.
- if STD_ON, extra channel required
- if STD_OFF, no extra channel required
*/

/*
This macro determines whether the GPT driver needs an extra channel for
1us predefined timer implementation that can be used for frequency tuning.
*/
#define GPT_PREDEF_EXTRA_CH_1US                           (STD_OFF)

/*
This macro determines whether the GPT driver needs an extra channel for
100us predefined timer implementation, that can be used for frequency tuning.
*/
#define GPT_PREDEF_EXTRA_CH_100US                         (STD_OFF)

/*
Container : Configuration of optional API services
This container contains all configuration switches for configuring
optional API services of the GPT driver.
*/

/*
Configuration: GPT_DEINIT_API
Adds/removes the service Gpt_DeInit() from the code
- if STD_ON, Gpt_DeInit() can be used
- if STD_OFF, Gpt_DeInit() can not be used
*/
#define GPT_DEINIT_API                                    (STD_ON)

/*
Configuration: GPT_TIME_ELAPSED_API
Adds/removes the service Gpt_GetTimeElapsed() from the code
- if STD_ON, Gpt_GetTimeElapsed() can be used
- if STD_OFF, Gpt_GetTimeElapsed() can not be used
*/
#define GPT_TIME_ELAPSED_API                              (STD_OFF)

/*
Configuration: GPT_VERSION_INFO_API
Adds/removes the service Gpt_GetVersionInfo() from the code
- if STD_ON, Gpt_GetVersionInfo() can be used
- if STD_OFF, Gpt_GetVersionInfo() can not be used
*/
#define GPT_VERSION_INFO_API                              (STD_OFF)

/*
Configuration: GPT_ENABLE_DISABLE_NOTIFICATION_API
Adds/removes the service Gpt_EnableNotification() and Gpt_DisableNotification
from the code
- if STD_ON, Gpt_EnableNotification() and Gpt_DisableNotification  can be used
- if STD_OFF, Gpt_EnableNotification() and Gpt_DisableNotification  can not be
used
*/
#define GPT_ENABLE_DISABLE_NOTIFICATION_API               (STD_ON)

/*
Configuration: GPT_TIME_REMAINING_API
Adds/removes the service Gpt_GetTimeRemaining() from the code
- if STD_ON, Gpt_GetTimeRemaining() can be used
- if STD_OFF, Gpt_GetTimeRemaining() can not be used
*/
#define GPT_TIME_REMAINING_API                            (STD_OFF)

/*
Configuration: GPT_WAKEUP_FUNCTIONALITY_API
Adds/removes the service Gpt_SetMode(), Gpt_EnableWakeup(),
Gpt_DisableWakeup() and Gpt_CheckWakeup() from the code
- if STD_ON, Gpt_SetMode(), Gpt_EnableWakeup(), Gpt_DisableWakeup() and
Gpt_CheckWakeup() can be used
- if STD_OFF, Gpt_SetMode(), Gpt_EnableWakeup(), Gpt_DisableWakeup() and
Gpt_CheckWakeup() can not be used
*/
#define GPT_WAKEUP_FUNCTIONALITY_API                      (STD_OFF)

/*
Configuration: GPT_ONESHOT_USED
The configuration contains oneshot mode channels
*/
#define GPT_ONESHOT_USED                                  (STD_OFF)

/*******************************************************************************
**                                Gpt Driver Usage                            **
*******************************************************************************/

/* Configuration: ResourceM
The configuration contains allocation of Gpt channels across cores.
- if STD_ON, atleast one Gpt channel is configured in the core.
- if STD_OFF, no Gpt channels are configured in the core. */
#define GPT_CONFIGURED_CORE0                              (STD_ON)
#define GPT_CONFIGURED_CORE1                              (STD_ON)
#define GPT_CONFIGURED_CORE2                              (STD_OFF)

#define GPT_CONFIGURED_CORE3                              (STD_OFF)

#define GPT_CONFIGURED_CORE4                              (STD_OFF)

#define GPT_CONFIGURED_CORE5                              (STD_OFF)



#define GPT_READ_ACROSS_CORES                            (STD_OFF)

/* Number of Cores confgiured for Gpt */
#define GPT_MAX_CORE_USED                                 (2U)

/* Number of channels configured as regular timers across all cores. */
#define GPT_MAX_CHANNELS                                  (2U)

/* Number of channels configured as regular timers per core */
#define GPT_MAX_CHANNELS_CORE0                            (1U)
#define GPT_MAX_CHANNELS_CORE1                            (1U)
#define GPT_MAX_CHANNELS_CORE2                            (0U)
#define GPT_MAX_CHANNELS_CORE3                            (0U)



/* Adds/removes the code related to 'TOM channels'
- if STD_ON, atleast one of the channel is using TOM channel
- if STD_OFF, none of the channels are using TOM channel */
#define GPT_TOM_USED                                      (STD_ON)

/* Adds/removes the code related to 'ATOM channels'
- if STD_ON, atleast one of the channel is using ATOM channel
- if STD_OFF, none of the channels are using ATOM channel */
#define GPT_ATOM_USED                                     (STD_ON)


#define GPT_GPT12_USED                                    (STD_OFF)
/*******************************************************************************
**                          Gpt Channel Symbolic Names                        **
*******************************************************************************/
/* Gpt Channel ID Enumerations for Channel Configuration. */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#ifndef GptConf_GptChannelConfiguration_GptChannelConfiguration_0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define GptConf_GptChannelConfiguration_GptChannelConfiguration_0  \
((Gpt_ChannelType)0U)
#endif
/* Gpt Channel ID Enumerations for Channel Configuration. */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#ifndef GptConf_GptChannelConfiguration_GptChannelConfiguration_1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define GptConf_GptChannelConfiguration_GptChannelConfiguration_1  \
((Gpt_ChannelType)1U)
#endif

/*******************************************************************************
**                          Resource Availability                             **
*******************************************************************************/

#define GPT_GTM_TOM_MODULE                                (5U)
#define GPT_GTM_TOM_CHANNELS_PER_TGC                      (8U)

#define GPT_GTM_ATOM_MODULE                               (9U)
#define GPT_GTM_ATOM_CHANNELS_PER_AGC                     (8U)

#endif /* GPT_CFG_H */
/* End Of File */
