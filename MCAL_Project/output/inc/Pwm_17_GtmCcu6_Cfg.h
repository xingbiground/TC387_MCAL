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
**  FILENAME  : Pwm_17_GtmCcu6_Cfg.h                                          **
**                                                                            **
**  VERSION   : 12.0.0                                                        **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:31       !!!IGNORE-LINE!!!                  **
**                                                                            **
**  GENERATOR : Build b191017-0938         !!!IGNORE-LINE!!!                  **
**                                                                            **
**  BSW MODULE DECRIPTION : Pwm.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Pwm configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : AUTOSAR Specification of Pwm Driver                    **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef PWM_17_GTMCCU6_CFG_H
#define PWM_17_GTMCCU6_CFG_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/*******************************************************************************
**                      Global Macro Definitions                              **
** Traceabilty      :                                                         **
*******************************************************************************/


#define PWM_17_GTMCCU6_AR_RELEASE_MAJOR_VERSION  (4U)

#define PWM_17_GTMCCU6_AR_RELEASE_MINOR_VERSION  (2U)

#define PWM_17_GTMCCU6_AR_RELEASE_REVISION_VERSION  (2U)

#define PWM_17_GTMCCU6_SW_MAJOR_VERSION  (20U)

#define PWM_17_GTMCCU6_SW_MINOR_VERSION  (20U)

#define PWM_17_GTMCCU6_SW_PATCH_VERSION  (0U)
/*
-------------------- Container:PwmGeneral --------------------
*/
/*
Configuration: PWM_17_GTMCCU6_DEV_ERROR_DETECT :
Configuration of Development Error Detection 
API Parameter Checking is enabled if this compiler
switch is STD_ON.
All errors are reported to Det_ReportError if the
switch is STD_ON.
Adds/removes the Development error detection 
from the code 
- if STD_ON, Development error detection is enabled
- if STD_OFF, Development error detection is disabled
*/

#define PWM_17_GTMCCU6_DEV_ERROR_DETECT (STD_ON)
/*
Configuration: PWM_17_GTMCCU6_MULTICORE_ERROR_DETECT :
Adds/removes the Multicore error detection and reporting 
from the code 
- if STD_ON, Multicore error detection and reporting is enabled
- if STD_OFF, Multicore error detection and reporting is disabled
*/

#define PWM_17_GTMCCU6_MULTICORE_ERROR_DETECT (STD_ON)

/* Instance ID for PWM_17_Gtm module */
#define PWM_17_GTMCCU6_INSTANCE_ID         ((uint8)0U)
/*
Configuration: PWM_17_GTMCCU6_DE_INIT_API
Configuration of Pwm_DeInit API
Adds/removes the service Pwm_DeInit() 
from the code 
- if STD_ON, Pwm_DeInit() can be used
- if STD_OFF, Pwm_DeInit() cannot be used
*/

#define PWM_17_GTMCCU6_DE_INIT_API (STD_ON)
/*
Configuration: PWM_17_GTMCCU6_GET_OUTPUT_STATE_API
Configuration of PWM_17_GTMCCU6_GET_OUTPUT_STATE_API
Adds/removes the service Pwm_GetOutputState() 
from the code 
- if STD_ON, Pwm_GetOutputState() can be used
- if STD_OFF, Pwm_GetOutputState() cannot be used
*/

#define PWM_17_GTMCCU6_GET_OUTPUT_STATE_API (STD_OFF)
/*
Configuration: PWM_17_GTMCCU6_SET_DUTY_CYCLE_API
Configuration of PWM_17_GTMCCU6_SET_DUTY_CYCLE_API
Adds/removes the service Pwm_GetOutputState() 
from the code 
- if STD_ON, Pwm_SetDutyCycle() can be used
- if STD_OFF,Pwm_SetDutyCycle() cannot be used
*/

#define PWM_17_GTMCCU6_SET_DUTY_CYCLE_API (STD_ON)
/*
Configuration: PWM_17_GTMCCU6_SET_OUTPUT_TO_IDLE_API
Configuration of PWM_17_GTMCCU6_SET_OUTPUT_TO_IDLE_API
Adds/removes the service Pwm_SetOutputToIdle() 
from the code 
- if STD_ON, Pwm_SetOutputToIdle() can be used
- if STD_OFF,Pwm_SetOutputToIdle() cannot be used
*/

#define PWM_17_GTMCCU6_SET_OUTPUT_TO_IDLE_API (STD_OFF)
/*
Configuration: PWM_17_GTMCCU6_SET_PERIOD_AND_DUTY_API
Configuration of PWM_17_GTMCCU6_SET_PERIOD_AND_DUTY_API
Adds/removes the service Pwm_SetPeriodAndDuty() 
from the code 
- if STD_ON, Pwm_SetPeriodAndDuty() can be used
- if STD_OFF,Pwm_SetPeriodAndDuty() cannot be used
*/

#define PWM_17_GTMCCU6_SET_PERIOD_AND_DUTY_API (STD_ON)
/* Enables the handling of Shifted channel by offset
- if STD_ON, Shifted channel is handled by offset
- if STD_OFF, Shifted channel handled by trigger from 
referenced Fixed period channel
*/

#define PWM_17_GTMCCU6_HANDLE_SHIFT_BY_OFFSET (STD_OFF)
/*
Configuration: PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED
Adds/removes the service Pwm_EnableNotification()
and Pwm_DisableNotification() from the code 
- if STD_ON, Notification API's can be used
- if STD_OFF, Notification API's cannot be used
*/

#define PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED (STD_OFF)
/*
Configuration: PWM_NOTIFICATION_FOR_0_AND_100
Enable Notification for 0% and 100% duty 
- if STD_ON, Notification for 0% and 100% duty is supported
- if STD_OFF, Notification for 0% and 100% duty is not supported
*/

#define PWM_17_GTMCCU6_NOTIF_FOR_100_0_ENABLE           (STD_OFF)
/*
Configuration: PWM_17_GTMCCU6_DUTYCYCLE_UPDATED_ENDPERIOD
Feature to have the duty cycle change, whether to update
the duty at the end period or not.
*/

#define PWM_17_GTMCCU6_DUTYCYCLE_UPDATED_ENDPERIOD (STD_OFF)

/*
Configuration: PWM_DUTY_PERIOD_UPDATED_ENDPERIOD
Applicable for Variable Period Channel Class.
Feature to have the duty cycle / period change, whether to update
the duty / period at the end period or not.
*/
#define PWM_17_GTMCCU6_DUTY_PERIOD_UPDATED_ENDPERIOD (STD_OFF)

#define PWM_17_GTMCCU6_SAFETY_ENABLE (STD_ON)

#define PWM_17_GTMCCU6_INITCHECK_API (STD_OFF)
/*
Configuration: PWM_17_GTMCCU6_VERSION_INFO_API
Adds/removes the service Pwm_GetVersionInfo() 
from the code 
- if STD_ON, Pwm_GetVersionInfo() can be used
- if STD_OFF, Pwm_GetVersionInfo() cannot be used
*/

#define PWM_17_GTMCCU6_VERSION_INFO_API (STD_OFF)
/* Configuration : PwmDutyShiftInTicks
This parameter enables the user to enter the duty cycle and 
shift value in absolute ticks, instead of percentage
*/

#define PWM_17_GTMCCU6_DUTY_SHIFT_IN_TICKS (STD_OFF)
/* Configured PWM Channels Symbolic Names */

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#ifndef Pwm_17_GtmCcu6Conf_PwmChannel_PwmChannel_0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define Pwm_17_GtmCcu6Conf_PwmChannel_PwmChannel_0     ((Pwm_17_GtmCcu6_ChannelType)0)
#endif

/* Configuration:Max channels configured for Pwm, max channelas are same across variants.*/

#define PWM_17_GTMCCU6_MAX_CHANNELS         ((Pwm_17_GtmCcu6_ChannelType)1)

#define PWM_17_GTMCCU6_MAX_CORES            (4U)
/* Loop for all the cores */

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_MAX_CHANNELS_CORE0               (1U)

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_MAX_CHANNELS_CORE1               (0U)

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_MAX_CHANNELS_CORE2               (0U)

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_MAX_CHANNELS_CORE3               (0U)

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_MAX_CHANNELS_CORE4               (255U)

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_MAX_CHANNELS_CORE5               (255U)

#define PWM_17_GTMCCU6_GTM_TIMER_USED              (STD_ON)

#define PWM_17_GTMCCU6_CCU6_TIMER_USED             (STD_OFF)
/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/
#endif
