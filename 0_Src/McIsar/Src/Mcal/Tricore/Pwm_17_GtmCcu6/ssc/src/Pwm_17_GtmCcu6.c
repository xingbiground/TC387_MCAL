/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2022)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : Pwm_17_GtmCcu6.c                                           **
**                                                                            **
**  VERSION      : 67.0.0                                                     **
**                                                                            **
**  DATE         : 2022-06-21                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : PWM Driver source file                                     **
**                                                                            **
**  SPECIFICATION(S) : AUTOSAR Specification of Pwm Driver                    **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/******************************************************************************
**                      Includes                                             **
******************************************************************************/
/* [cover parentID={7AEB3ED0-6A5D-4f37-BBC4-D796BB890E57}]
  Pwm_17_GtmCcu6.c shall include Pwm_17_GtmCcu6.h, Pwm_17_GtmCcu6_MemMap.h
  and SchM_Pwm_17_GtmCcu6.h [/cover] */
#if defined(ACCESS)
#undef ACCESS
#endif
/* Include McalLib.h to import the library functions */
#include "McalLib.h"
/* [cover parentID={9BD8AF63-1196-4ff8-AA94-9DDEE8166CB6}]
Pwm Module header file, includes PWM Static configuration file also [/cover] */
#include "Pwm_17_GtmCcu6.h"

#if (PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
#include "IfxGtm_reg.h"
#include "IfxGtm_bf.h"
#endif

#if (PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
#include "IfxCcu6_reg.h"
#include "IfxCcu6_bf.h"
#endif

/* [cover parentID={03DE4315-790B-4da0-AD51-70A7422F02C6}]
  Include callback header definition [/cover] */
#include "Pwm_17_GtmCcu6_Cbk.h"

#if (PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON)
/* Includes Safety Error header definition */
#include "Mcal_SafetyError.h"
#endif

/* [cover parentID={55B30D82-089C-451b-BDB8-F0C5B5397EF5}]
 Pwm Critical section header file [/cover] */
#include "SchM_Pwm_17_GtmCcu6.h"

/* Includes Det header definition */ 
#if (PWM_17_GTMCCU6_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif
/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/
/* [cover parentID={F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}]
Autosar variant management [/cover] */
/* [cover parentID={4BF2823B-4863-48e2-B11A-1C75EDC09942}]
Check consistency of PWM ASR Major, Minor and Patch Version.[/cover] */
#ifndef PWM_17_GTMCCU6_AR_RELEASE_MAJOR_VERSION
#error "PWM_17_GTMCCU6_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

#if (PWM_17_GTMCCU6_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION)
#error "PWM_17_GTMCCU6_AR_RELEASE_MAJOR_VERSION does not match. "
#endif

#ifndef PWM_17_GTMCCU6_AR_RELEASE_MINOR_VERSION
#error "PWM_17_GTMCCU6_AR_RELEASE_MINOR_VERSION is not defined."
#endif

#if (PWM_17_GTMCCU6_AR_RELEASE_MINOR_VERSION != MCAL_AR_RELEASE_MINOR_VERSION)
#error "PWM_17_GTMCCU6_AR_RELEASE_MINOR_VERSION does not match."
#endif

#ifndef PWM_17_GTMCCU6_AR_RELEASE_REVISION_VERSION
#error "PWM_17_GTMCCU6_AR_RELEASE_REVISION_VERSION is not defined."
#endif

#if (PWM_17_GTMCCU6_AR_RELEASE_REVISION_VERSION != MCAL_AR_RELEASE_REVISION_VERSION)
#error "PWM_17_GTMCCU6_AR_RELEASE_REVISION_VERSION does not match."
#endif

/* [cover parentID={4BF2823B-4863-48e2-B11A-1C75EDC09942}]
   Check consistency of PWM SW Major, Minor and Patch Version.[/cover] */
#ifndef PWM_17_GTMCCU6_SW_MAJOR_VERSION
#error "PWM_17_GTMCCU6_SW_MAJOR_VERSION is not defined. "
#endif

#ifndef PWM_17_GTMCCU6_SW_MINOR_VERSION
#error "PWM_17_GTMCCU6_SW_MINOR_VERSION is not defined. "
#endif

#ifndef PWM_17_GTMCCU6_SW_PATCH_VERSION
#error "PWM_17_GTMCCU6_SW_PATCH_VERSION is not defined. "
#endif

#if (PWM_17_GTMCCU6_SW_MAJOR_VERSION != 20U)
#error "PWM_17_GTMCCU6_SW_MAJOR_VERSION does not match. "
#endif

#if (PWM_17_GTMCCU6_SW_MINOR_VERSION != 20U)
#error "PWM_17_GTMCCU6_SW_MINOR_VERSION does not match. "
#endif

#if (PWM_17_GTMCCU6_SW_PATCH_VERSION != 0U)
#error "PWM_17_GTMCCU6_SW_PATCH_VERSION does not match. "
#endif

/* [cover parentID={B3E0A6C4-C239-4c20-B35A-AC40F08DD992}]
Chek consistency of DET SW major version.[/cover] */
#if (PWM_17_GTMCCU6_DEV_ERROR_DETECT == STD_ON)
#ifndef DET_AR_RELEASE_MAJOR_VERSION
#error "DET_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

#if (DET_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION)
#error "DET_AR_RELEASE_MAJOR_VERSION does not match"
#endif
#endif

/******************************************************************************
**                      Private Macro Definitions                            **
******************************************************************************/
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled */
/* To shift by 15 to convert Relative value to an absolute value */
#define PWM_SHIFT_BY15             (32768U)

/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled */
/* To enable any bit of register or global channel variable */
#define PWM_BIT_SET                (1U)

/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled */
/* To disable any bit of register or global channel variable */
#define PWM_BIT_RESET              (0U)

/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled */
/* To reset SFR to application reset value */
#define PWM_TOM_SFR_RESET_VAL      (0x0U)

/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled */
/* To reset SFR to application reset value */
#define PWM_ATOM_SFR_RESET_VAL     (0x0U)

/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled */
/* To indicate error for DET and Safety related local functions */
#define PWM_ERROR_FOUND            ((uint32)1)

/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled*/
/* To indicate Maximum Duty Cycle value when duty is percentage */
#define PWM_MAX_DUTY               ((uint16)0x8000)

/* To get the Channel reset type */
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled */
#define PWM_RSTSHFT_POS            (0x5U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled */
#define PWM_RSTSHFTSTATE_MASK      ((uint16)0x1)

/* To get the Channel class type */
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled */
#define PWM_CHANNEL_CLASS_POS      ((uint32)0x3)
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled */
#define PWM_CHANNEL_CLASS_MASK     ((uint16)0x3)

/* To get the channel Coherency type */
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled */
#define PWM_COHERENCY_POS          (0x2U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled */
#define PWM_COHERENCY_MASK         ((uint16)0x1)

/* To get the channel Idle state */
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled */
#define PWM_IDLESTATE_POS          (0x1U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled */
#define PWM_IDLESTATE_MASK         ((uint16)0x1)

/* To get position of notification flag to trigger DSADC from GTM interrupts */
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled*/
#define PWM_DSADCNOTIF_POS         (0x6U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled*/
#define PWM_DSADCNOTIF_MASK        ((uint16)0x1)

/* To get polarity of PWM channel */
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled */
#define PWM_POLSTATE_MASK          ((uint16)0x1)
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled*/
#define PWM_POLSTATE_POS           (0x0U)

/* To get Notification status */
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled */
#define PWM_CCU6_NOTIFI_STATUS_POS (4)

/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled */
/* To get Notification type in the global channel variable */
#define PWM_NOTIFICATION_EDGE_MASK ((uint32)(0x00000006))

/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled */
/* Position of Notification Status in global channel variable */
#define PWM_NOTIFI_STATUS_POS      (0)

/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled */
/* Position of Notification edges in global channel variable */
#define PWM_NOTIFI_EDGE_POS        (1)

/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled */
/* Position of Duty update Flag in global channel variable */
#define PWM_DUTY_0_OR_100_UPDATE_FLGPOS (3)

/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled */
/* No of Notification Edge Bits in global channel variable */
#define PWM_NOTIFI_EDGE_BITS       (2)

/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled */
/* Mask to obtain Duty Update bit */
#define PWM_DUTY_0_OR_100_UPDATE_MASK ((uint32)(0x00000008))

/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled */
/* Mask to obtain Notification Status bit from global channel variable */
#define PWM_NOTIFI_STATUS_MASK     ((uint32)(0x00000001))

/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled.*/
/* To indicate the Notification handled Status */
#define PWM_PM_NOTIF_HANDLED       (1U)

/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled.*/
/* Mask to obtain the CCU6 channels */
#define PWM_CCU6_CH_MASK           (0xFFU)

/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled.*/
/* To indicate if notification was asked earlier */
#define PWM_NO_NOTIFICATION        ((Pwm_17_GtmCcu6_EdgeNotificationType)0)

/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled.*/
/* To Clear all pending interrupts */
#define PWM_CLR_PENDING_INTERRUPTS ((uint32)0x00000003U)

/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled.*/
/* To indicate Maximum Value of Timer for ATOM */
#define PWM_MAX_TIMER              ((uint32)0xFFFFFFU)

/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled.*/
/* To indicate Maximum Value of Timer for TOM */
#define PWM_MAX_TIMER_TOM          ((uint32)0xFFFFU)

/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled.*/
/* To indicate Maximum Value of Timer for CCU6 */
#define PWM_MAX_TIMER_CCU6         ((uint32)0xFFFFU)

/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled.*/
/* Mask to Set host trigger for configured TGC0 channels */
#define PWM_16BIT_MASK             ((uint32)0x0000FFFFU)

/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled.*/
/* Mask to Set host trigger for configured TGC1 channels */
#define PWM_16BIT_MASK_UPPER       ((uint32)0xFFFF0000U)

/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled.*/
/* Mask to Reset TOM or ATOM CTRL FREEZE,TRIGOUT, CLK_SRC_SR & RST_CCU0 bits */
#define PWM_TOM_CTRL_RST_MSK       ((uint32)0x7EEF8FFFU)
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled.*/
#define PWM_ATOM_CTRL_RST_MSK      ((uint32)0x7EEF8FFCU)

/* To indicate PWM initialized state */
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled */
#define PWM_INITIALIZED            ((uint32)1)
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled */
#define PWM_INITIALIZE_REQ         ((uint32)3)

/* To indicate PWM de-initailized */
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled */
#define PWM_DEINITIALIZED          ((uint32)0)
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled */
#define PWM_DEINITIALIZE_REQ       ((uint32)2)

/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled.*/
/* PWM Channel ID's status bits, used to change the status os the channel */
#define PWM_CHAN_ID_STAT_BITS      (1)

/* Generic Macros used in various functions */
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled */
#define PWM_CONST_1                (1U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled */
#define PWM_CONST_2                (2U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled */
#define PWM_CONST_3                (3U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled*/
#define PWM_CONST_4                (4U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled.*/
#define PWM_CONST_5                (5U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled*/
#define PWM_CONST_6                (6U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled*/
#define PWM_CONST_7                (7U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled */
#define PWM_CONST_8                (8U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled */
#define PWM_CONST_9                (9U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled */
#define PWM_CONST_16               (16U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled.*/
#define PWM_CONST_24               (24U)

/* Generic Macros used CCU6 functions */
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled*/
#define PWM_CCU6_TIMER_POS         (0x08U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled*/
#define PWM_CCU6_TIMER_MSK         (0xFFU)
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled*/
#define PWM_CCU6_COMPARATOR_POS    (0x10U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled*/
#define PWM_CCU6_COMPARATOR_MSK    (0xFFU)
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled*/
#define PWM_CCU6_KERNEL_MSK        (0xFFU)

#if (PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
GTM_TOM_CH_POINTER defined for easy readability in code.
No side effects foreseen by violating this MISRA rule. */
/* Macro to get the TOM channel base address */
#define PWM_GTM_TOM_CH_POINTER(Module,Channel) GTM_TOM_CH_POINTER(Module,Channel)

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
GTM_ATOM_CH_POINTER defined for easy readability in code.
No side effects foreseen by violating this MISRA rule. */
/* Macro to get the ATOM channel base address */
#define PWM_GTM_ATOM_CH_POINTER(Module,Channel) GTM_ATOM_CH_POINTER(Module,Channel)
#endif

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
PWM_GET_NOTIFICATION_KIND defined for easy readability in code.
No side effects foreseen by violating this MISRA rule. */
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled */
/* Function to get the Notification type in the global channel variable */
#define PWM_GET_NOTIFICATION_KIND(Channel,CoreID) \
    ((Pwm_17_GtmCcu6_EdgeNotificationType)((Pwm_CoreChannelStatus\
        [CoreId][Channel].Pwm_GlobChn)& PWM_NOTIFICATION_EDGE_MASK))

/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is referenced only when certain
precompile configuration switch is enabled */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
PWM_GET_POLARITY defined for easy readability in code.
No side effects foreseen by violating this MISRA rule. */
/* Macro to obtain the Polarity from PwmChannelInfo.*/
#define PWM_GET_POLARITY(Value) ((Pwm_17_GtmCcu6_OutputStateType)\
        (((uint16)(Value) >> PWM_POLSTATE_POS) & (PWM_POLSTATE_MASK)))

#if (PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
#if (PWM_17_GTMCCU6_INITCHECK_API == STD_ON)
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
GTM_ATOM_AGC_POINTER defined for easy readability in code.
No side effects foreseen by violating this MISRA rule. */
/* Macro to get the ATOM AGC base address*/
#define PWM_GTM_ATOM_AGC_POINTER(Module) GTM_ATOM_AGC_POINTER(Module)

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
GTM_TOM_TGC_POINTER defined for easy readability in code.
No side effects foreseen by violating this MISRA rule. */
/* Macro to get the TOM TGCx base address */
#define PWM_GTM_TOM_TGC_POINTER(Module,TomTgcIndex) \
                            GTM_TOM_TGC_POINTER(Module,TomTgcIndex)
#endif
#endif

/* [cover parentID={CB0369FB-D0C6-45b2-AB60-F1397D329697}]
ALL APIs are develped as per ASIL-D functionality [/cover] */
#define PWM_17_GTMCCU6_START_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Pwm_17_GtmCcu6_MemMap.h"
#if ((PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON) || \
     (PWM_17_GTMCCU6_DEV_ERROR_DETECT == STD_ON))
static uint8 Pwm_lInitDetCheck
(
  const Pwm_17_GtmCcu6_ConfigType *DetConfigPtr,
  const uint32 CoreId
);

#if((PWM_17_GTMCCU6_SET_DUTY_CYCLE_API == STD_ON)||\
   (PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON)|| \
   (PWM_17_GTMCCU6_SET_OUTPUT_TO_IDLE_API == STD_ON) || \
   (PWM_17_GTMCCU6_GET_OUTPUT_STATE_API == STD_ON))
static uint32 Pwm_lVerUnInitAndChannel
(
  const uint8 ServiceID,
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
);
#endif

#if((PWM_17_GTMCCU6_SET_DUTY_CYCLE_API == STD_ON)||\
   (PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON)||\
   (PWM_17_GTMCCU6_SET_OUTPUT_TO_IDLE_API == STD_ON) ||\
   (PWM_17_GTMCCU6_GET_OUTPUT_STATE_API == STD_ON) || \
   (PWM_17_GTMCCU6_DE_INIT_API == STD_ON) || \
   (PWM_17_GTMCCU6_SET_PERIOD_AND_DUTY_API == STD_ON))
static uint32 Pwm_lVerUnInit(const uint8 ServiceID,const uint8 CoreId);
#endif

#if((PWM_17_GTMCCU6_SET_DUTY_CYCLE_API == STD_ON) || \
    (PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON) || \
    (PWM_17_GTMCCU6_SET_OUTPUT_TO_IDLE_API == STD_ON) || \
    (PWM_17_GTMCCU6_GET_OUTPUT_STATE_API == STD_ON)|| \
    ((PWM_17_GTMCCU6_SET_PERIOD_AND_DUTY_API == STD_ON) &&\
    ((PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON) || \
    (PWM_17_GTMCCU6_DEV_ERROR_DETECT == STD_ON))))
static uint32 Pwm_lVerChannel
(
  const uint8 ServiceID,
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
);
#endif
#endif/*End of PWM_17_GTMCCU6_SAFETY_ENABLE or PWM_17_GTMCCU6_DEV_ERROR_DETECT*/

LOCAL_INLINE Pwm_17_GtmCcu6_ChannelClassType Pwm_lChanClass(const uint16 Value);

static void Pwm_lInitFixedPeriod
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
);
#if (PWM_17_GTMCCU6_INITCHECK_API == STD_ON)
static Std_ReturnType Pwm_lInitFixedPeriodCheck
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
);
#endif

static void Pwm_lInitVariablePeriod
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
);
#if (PWM_17_GTMCCU6_INITCHECK_API == STD_ON)
static Std_ReturnType Pwm_lInitVariablePeriodCheck
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
);
#endif

static void Pwm_lInitShiftedCentreAligned
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
);
#if (PWM_17_GTMCCU6_INITCHECK_API == STD_ON)
static Std_ReturnType Pwm_lInitShiftedCentreAlignedCheck
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
);
#endif

#if (PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
static void Pwm_lGtmResetOutEnEndisCtrl
(
  const uint8 TimerModuleNumber,
  const uint8 TimerChannelNumber,
  const Mcu_17_Gtm_TimerOutType PwmGtmTimerType
);
#if (PWM_17_GTMCCU6_INITCHECK_API == STD_ON)
static Std_ReturnType Pwm_lGtmResetOutEnEndisCtrlCheck
(
  const uint8 TimerModuleNumber,
  const uint8 TimerChannelNumber,
  const Mcu_17_Gtm_TimerOutType PwmGtmTimerType
);
#endif
static void Pwm_lGtmResetOutEnEndisStat
(
  const uint8 TimerModuleNumber,
  const uint8 TimerChannelNumber,
  const Mcu_17_Gtm_TimerOutType PwmGtmTimerType
);
#if (PWM_17_GTMCCU6_INITCHECK_API == STD_ON)
static Std_ReturnType Pwm_lGtmResetOutEnEndisStatCheck
(
  const uint8 TimerModuleNumber,
  const uint8 TimerChannelNumber,
  const Mcu_17_Gtm_TimerOutType PwmGtmTimerType
);
#endif
static void Pwm_lGtmStartChannelsInit
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
);
#if (PWM_17_GTMCCU6_INITCHECK_API == STD_ON)
static Std_ReturnType Pwm_lGtmStartChannelsInitCheck
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
);
#endif

static void Pwm_lGtmStartTomChannelsInit
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
);
static void Pwm_lGtmStartAtomChannelsInit
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
);
#if (PWM_17_GTMCCU6_INITCHECK_API == STD_ON)
static Std_ReturnType Pwm_lGtmStartTomChannelsInitCheck
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
);
static Std_ReturnType Pwm_lGtmStartAtomChannelsInitCheck
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
);
#endif
#endif /* End of PWM_17_GTMCCU6_GTM_TIMER_USED */

#if (PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
static void Pwm_lCcu6StartChannelsInit
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
);
#if (PWM_17_GTMCCU6_INITCHECK_API == STD_ON)
static Std_ReturnType Pwm_lCcu6StartChannelsInitCheck
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
);
#endif
#endif /* End of PWM_17_GTMCCU6_CCU6_TIMER_USED */

#if (PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
LOCAL_INLINE uint8 Pwm_lCoherency(const uint16 Value);
#endif

#if((PWM_17_GTMCCU6_SET_PERIOD_AND_DUTY_API == STD_ON) || \
    (PWM_17_GTMCCU6_SET_DUTY_CYCLE_API == STD_ON) || \
    (PWM_17_GTMCCU6_SET_OUTPUT_TO_IDLE_API == STD_ON))
#if (PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
LOCAL_INLINE uint8 Pwm_lChanResetType(const uint16 Value);
#endif
#endif

#if ((PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON)&&\
    (PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON))
static void Pwm_lGtmIrqModify(const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
                              const uint8 InterruptFlag, const uint8 CoreId);
#endif

#if( (PWM_17_GTMCCU6_DE_INIT_API == STD_ON) || \
     (PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON) )
#if (PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
static void Pwm_lCcu6IrqModify(const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
                               const uint8 InterruptFlag, const uint8 CoreId);
#endif
#endif

#if((PWM_17_GTMCCU6_DE_INIT_API == STD_ON) || \
    (PWM_17_GTMCCU6_SET_OUTPUT_TO_IDLE_API == STD_ON))
LOCAL_INLINE Pwm_17_GtmCcu6_OutputStateType Pwm_lIdle(const uint16 Value);
#endif

#if (PWM_17_GTMCCU6_DE_INIT_API == STD_ON)
#if (PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
static void Pwm_lTomDeInit(const uint8 TimerModuleNumber, \
      uint8 TimerChannelNumber, const Pwm_17_GtmCcu6_OutputStateType IdleState);
static void Pwm_lAtomDeInit(const uint8 TimerModuleNumber, \
const uint8 TimerChannelNumber, const Pwm_17_GtmCcu6_OutputStateType IdleState);
#endif
#endif

#if((PWM_17_GTMCCU6_SET_DUTY_CYCLE_API == STD_ON) || \
    (PWM_17_GTMCCU6_SET_PERIOD_AND_DUTY_API == STD_ON) || \
    (PWM_17_GTMCCU6_SET_OUTPUT_TO_IDLE_API == STD_ON))
/* To get absolute duty value as per period (used for edge aligned type) */
LOCAL_INLINE Pwm_17_GtmCcu6_PeriodType Pwm_lGetAbsvalEdge
(
  const Pwm_17_GtmCcu6_PeriodType Period,
  const uint32 Value
);
#endif

#if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
#if (PWM_17_GTMCCU6_SET_DUTY_CYCLE_API == STD_ON)
LOCAL_INLINE Pwm_17_GtmCcu6_PeriodType Pwm_lGetCenterLead
(
  const Pwm_17_GtmCcu6_PeriodType Period,
  const Pwm_17_GtmCcu6_PeriodType ScaledDuty
);
#endif
#endif

#if (PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON)
#if (PWM_17_GTMCCU6_SET_DUTY_CYCLE_API == STD_ON)
LOCAL_INLINE void Pwm_lHandleNotif(\
                            const Pwm_17_GtmCcu6_ChannelClassType ChannelKind,
                            const uint32 Period,
                            const uint32 DutyCycle,
                            const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
                            const uint8 CoreId);
#endif
LOCAL_INLINE void Pwm_lEnableQmNotif(\
                     const Pwm_17_GtmCcu6_ChannelClassType ChannelKind,
                     const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
                     const Pwm_17_GtmCcu6_EdgeNotificationType Notification,
                     const uint8 CoreId
                    );
#endif /* End of PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED */

#if (PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON)
#if (PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
LOCAL_INLINE uint8 Pwm_lHandlePeriodMatch(uint8 Ccu6Kernel,\
                                            uint8 Ccu6Comparator, uint8 CoreId);
#endif
#if (PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON)
LOCAL_INLINE uint32 Pwm_lUnInitChIdCheck(\
                        Pwm_17_GtmCcu6_ChannelType ChannelNumber, uint8 CoreId);
#endif

LOCAL_INLINE void Pwm_lSetNotificationEdges(\
    const Pwm_17_GtmCcu6_ChannelType Channel, \
    const Pwm_17_GtmCcu6_EdgeNotificationType Edge, const uint8 CoreId);

/* Function to Set Duty Notification status in the global channel variable */
LOCAL_INLINE void Pwm_lSetDuty_0_Or_100_Status(\
  const Pwm_17_GtmCcu6_ChannelType Channel, const uint8 CoreId);

#if (PWM_17_GTMCCU6_INITCHECK_API == STD_ON)
LOCAL_INLINE Std_ReturnType Pwm_lSetDuty_0_Or_100_StatusCheck(\
 const Pwm_17_GtmCcu6_ChannelType Channel, const uint8 CoreId);
#endif

LOCAL_INLINE void Pwm_lClearNotificationEdges(\
  const Pwm_17_GtmCcu6_ChannelType Channel, const uint8 CoreId);
#if ((PWM_17_GTMCCU6_SET_DUTY_CYCLE_API == STD_ON) || \
     ((PWM_17_GTMCCU6_SET_PERIOD_AND_DUTY_API == STD_ON) && \
     (PWM_17_GTMCCU6_NOTIF_FOR_100_0_ENABLE == STD_OFF)))
LOCAL_INLINE void Pwm_lClearDuty_0_Or_100_Status(\
 const Pwm_17_GtmCcu6_ChannelType Channel, const uint8 CoreId);
#endif

/* Function to Set the Notification status in the global channel variable */
LOCAL_INLINE void Pwm_lSetNotificationStatus(\
  Pwm_17_GtmCcu6_ChannelType Channel, uint8 CoreId);
LOCAL_INLINE void Pwm_lClearNotificationStatus(\
                          Pwm_17_GtmCcu6_ChannelType Channel, uint8 CoreId);
#endif /* End of PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED */

#if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
#if((PWM_17_GTMCCU6_SET_PERIOD_AND_DUTY_API == STD_ON) || \
    (PWM_17_GTMCCU6_SET_DUTY_CYCLE_API == STD_ON))
static void Pwm_lGtmStartChannel
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint32 Period,
  const uint32 Dutycycle,
  const uint32 Shift,
  const uint8 CoreId
);
#endif
#endif
#if(PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
static void Pwm_lCcu6StartChannel
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint32 Period,
  const uint32 Dutycycle,
  const uint8 CoreId
);
#endif
#if((PWM_17_GTMCCU6_SET_PERIOD_AND_DUTY_API == STD_ON) || \
    (PWM_17_GTMCCU6_SET_DUTY_CYCLE_API == STD_ON))
#if (PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
static void Pwm_lGtmStartTomChannel
(
  Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  uint32 Period,
  uint32 Dutycycle,
  uint32 Shift,
  uint8  CoreId
);

static void Pwm_lGtmStartAtomChannel
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint32 Period,
  const uint32 Dutycycle,
  const uint32 Shift,
  const uint8 CoreId
);
#endif
#endif
#if ((PWM_17_GTMCCU6_SET_PERIOD_AND_DUTY_API == STD_ON) && \
     ((PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON) || \
     (PWM_17_GTMCCU6_DEV_ERROR_DETECT == STD_ON)))
LOCAL_INLINE uint32 Pwm_lVerUnInitChanAndPer
(
  const uint8 ServiceID,
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
);
#endif
#if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
#if(PWM_17_GTMCCU6_SET_OUTPUT_TO_IDLE_API == STD_ON)
static void Pwm_lGtmStartChannelIdle
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint32 Period,
  const uint32 Dutycycle,
  const uint8 CoreId
);
static void Pwm_lGtmStartTomChannelIdle
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint32 Period,
  const uint32 Dutycycle,
  const uint8 CoreId
);
static void Pwm_lGtmStartAtomChannelIdle
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint32 Period,
  const uint32 Dutycycle,
  const uint8 CoreId
);
#endif
#endif

#if(PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
#if ((PWM_17_GTMCCU6_SET_OUTPUT_TO_IDLE_API == STD_ON) || \
     (PWM_17_GTMCCU6_DE_INIT_API == STD_ON) )
static void Pwm_lCcu6StartChannelIdle
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint32 Dutycycle,
  const uint8 CoreId
);
#endif
#endif
#if (PWM_17_GTMCCU6_GET_OUTPUT_STATE_API == STD_ON)
static boolean Pwm_lGetOutputState
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
);
#endif
#if ((((PWM_17_GTMCCU6_DE_INIT_API == STD_ON) && \
     (PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)) || \
     (PWM_17_GTMCCU6_SET_OUTPUT_TO_IDLE_API == STD_ON)) && \
     (PWM_17_GTMCCU6_DUTY_SHIFT_IN_TICKS == STD_ON))
LOCAL_INLINE uint32 Pwm_lMaxDuty(uint8 ChannelIdx, uint8 CoreId);
#endif
#if (PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
static void Pwm_lCcu6StartTimerSync(uint8 CoreId);
#if (PWM_17_GTMCCU6_INITCHECK_API == STD_ON)
static Std_ReturnType Pwm_lCcu6StartTimerSyncCheck(uint8 CoreId);
#endif
#endif

#if ((PWM_17_GTMCCU6_DEV_ERROR_DETECT == STD_ON) || \
     (PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON))
static void Pwm_lReportError(const uint8 ApiId, const uint8 ErrorId);
#endif

#if (PWM_17_GTMCCU6_MULTICORE_ERROR_DETECT == STD_ON) || \
    (PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON)
static void Pwm_lReportMulticoreError(const uint8 ApiId, const uint8 ErrorId);
#endif

#if ((PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON) && \
     ((PWM_17_GTMCCU6_SET_PERIOD_AND_DUTY_API == STD_ON)||\
     (PWM_17_GTMCCU6_SET_DUTY_CYCLE_API == STD_ON)))
LOCAL_INLINE uint32 Pwm_lDutyRangeCheck
(
  const uint8 ServiceID,
  const uint32 DutyCycle,
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
);
#endif
#if ((PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON) && \
     (PWM_17_GTMCCU6_SET_PERIOD_AND_DUTY_API == STD_ON))
LOCAL_INLINE uint32 Pwm_lDutyPeriodRangeCheck
(
  const uint8 ServiceID,
  const uint32 DutyCycle,
  const uint32 Period,
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
);
LOCAL_INLINE uint32 Pwm_lPeriodRangeCheck
(
  const uint8 ServiceID,
  const uint32 Period,
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
);
#endif
/* MemMap Definitions*/
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
Memory Mapping [/cover] */

/* [cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
Memory Mapping callout code Pwm module does not have
callout code [/cover] */

/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
Pwm module does not have constant data [/cover] */

#if ((PWM_17_GTMCCU6_SET_PERIOD_AND_DUTY_API == STD_ON) && \
     (PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON))
LOCAL_INLINE void Pwm_lDisableGtmCcu6Notif(const Pwm_17_GtmCcu6_ChannelType \
    ChannelNumber, const uint8 CoreId, const uint8 TimerType);
#endif
#define PWM_17_GTMCCU6_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* [cover parentID={AEC85C2C-9C88-4cdd-99F2-A30D90EE892A}]
memmap.h [/cover] */
#include "Pwm_17_GtmCcu6_MemMap.h"
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
Memory Mapping variables [/cover] */

#if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE0 != 0xFFU)
#if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE0 != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_START_SEC_VAR_CLEARED_ASIL_B_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Pwm_17_GtmCcu6_MemMap.h"
static Pwm_17_GtmCcu6_CoreStatusType PwmCoreStatus_Core0;
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Pwm_17_GtmCcu6_MemMap.h"
#endif
#endif

#if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE1 != 0xFFU)
#if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE1 != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_START_SEC_VAR_CLEARED_ASIL_B_CORE1_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Pwm_17_GtmCcu6_MemMap.h"
static Pwm_17_GtmCcu6_CoreStatusType PwmCoreStatus_Core1;
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Pwm_17_GtmCcu6_MemMap.h"
#endif
#endif

#if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE2 != 0xFFU)
#if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE2 != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_START_SEC_VAR_CLEARED_ASIL_B_CORE2_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Pwm_17_GtmCcu6_MemMap.h"
static Pwm_17_GtmCcu6_CoreStatusType PwmCoreStatus_Core2;
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Pwm_17_GtmCcu6_MemMap.h"
#endif
#endif

#if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE3 != 0xFFU)
#if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE3 != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_START_SEC_VAR_CLEARED_ASIL_B_CORE3_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Pwm_17_GtmCcu6_MemMap.h"
static Pwm_17_GtmCcu6_CoreStatusType PwmCoreStatus_Core3;
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Pwm_17_GtmCcu6_MemMap.h"
#endif
#endif

#if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE4 != 0xFFU)
#if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE4 != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_START_SEC_VAR_CLEARED_ASIL_B_CORE4_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Pwm_17_GtmCcu6_MemMap.h"
static Pwm_17_GtmCcu6_CoreStatusType PwmCoreStatus_Core4;
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Pwm_17_GtmCcu6_MemMap.h"
#endif
#endif

#if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE5 != 0xFFU)
#if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE5 != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_START_SEC_VAR_CLEARED_ASIL_B_CORE5_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Pwm_17_GtmCcu6_MemMap.h"
static Pwm_17_GtmCcu6_CoreStatusType PwmCoreStatus_Core5;
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Pwm_17_GtmCcu6_MemMap.h"
#endif
#endif
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_START_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Pwm_17_GtmCcu6_MemMap.h"
/* MISRA2012_RULE_8_9_JUSTIFICATION:PwmCoreStatusPtr is a global variable & will
 be accessed across all PWM APIs, hence this variable can't be in block scope */
/* Driver core specific Init Status Variable */
static Pwm_17_GtmCcu6_CoreStatusType* const \
PwmCoreStatusPtr[PWM_17_GTMCCU6_MAX_CORES] =
{
  #if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE0 != 0xFFU)
  #if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE0 != 0U)
  (Pwm_17_GtmCcu6_CoreStatusType*) &PwmCoreStatus_Core0,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE1 != 0xFFU)
  #if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE1 != 0U)
  (Pwm_17_GtmCcu6_CoreStatusType*) &PwmCoreStatus_Core1,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE2 != 0xFFU)
  #if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE2 != 0U)
  (Pwm_17_GtmCcu6_CoreStatusType*) &PwmCoreStatus_Core2,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE3 != 0xFFU)
  #if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE3 != 0U)
  (Pwm_17_GtmCcu6_CoreStatusType*) &PwmCoreStatus_Core3,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE4 != 0xFFU)
  #if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE4 != 0U)
  (Pwm_17_GtmCcu6_CoreStatusType*) &PwmCoreStatus_Core4,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE5 != 0xFFU)
  #if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE5 != 0U)
  (Pwm_17_GtmCcu6_CoreStatusType*) &PwmCoreStatus_Core5,
  #else
  NULL_PTR,
  #endif
  #endif
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_STOP_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Pwm_17_GtmCcu6_MemMap.h"

/******************************************************************************
**                      Private Variable Definitions                         **
******************************************************************************/
/* To store the PWM driver configuration pointer */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Pwm_17_GtmCcu6_MemMap.h"

static const Pwm_17_GtmCcu6_ConfigType *Pwm_ConfigPtr;

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Pwm_17_GtmCcu6_MemMap.h"

#if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE0 != 0xFFU)
#if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE0 != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_START_SEC_VAR_CLEARED_ASIL_B_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Pwm_17_GtmCcu6_MemMap.h"
static Pwm_17_GtmCcu6_ChannelStatusType \
Pwm_17_Gtm_ChannelStatus_Core0[PWM_17_GTMCCU6_MAX_CHANNELS_CORE0];
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Pwm_17_GtmCcu6_MemMap.h"
#endif
#endif

#if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE1 != 0xFFU)
#if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE1 != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_START_SEC_VAR_CLEARED_ASIL_B_CORE1_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Pwm_17_GtmCcu6_MemMap.h"

static Pwm_17_GtmCcu6_ChannelStatusType \
Pwm_17_Gtm_ChannelStatus_Core1[PWM_17_GTMCCU6_MAX_CHANNELS_CORE1];
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Pwm_17_GtmCcu6_MemMap.h"
#endif
#endif

#if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE2 != 0xFFU)
#if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE2 != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_START_SEC_VAR_CLEARED_ASIL_B_CORE2_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Pwm_17_GtmCcu6_MemMap.h"

static Pwm_17_GtmCcu6_ChannelStatusType \
Pwm_17_Gtm_ChannelStatus_Core2[PWM_17_GTMCCU6_MAX_CHANNELS_CORE2];
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Pwm_17_GtmCcu6_MemMap.h"
#endif
#endif

#if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE3 != 0xFFU)
#if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE3 != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_START_SEC_VAR_CLEARED_ASIL_B_CORE3_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Pwm_17_GtmCcu6_MemMap.h"

static Pwm_17_GtmCcu6_ChannelStatusType \
Pwm_17_Gtm_ChannelStatus_Core3[PWM_17_GTMCCU6_MAX_CHANNELS_CORE3];
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Pwm_17_GtmCcu6_MemMap.h"
#endif
#endif

#if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE4 != 0xFFU)
#if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE4 != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_START_SEC_VAR_CLEARED_ASIL_B_CORE4_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Pwm_17_GtmCcu6_MemMap.h"

static Pwm_17_GtmCcu6_ChannelStatusType \
Pwm_17_Gtm_ChannelStatus_Core4[PWM_17_GTMCCU6_MAX_CHANNELS_CORE4];
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Pwm_17_GtmCcu6_MemMap.h"
#endif
#endif

#if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE5 != 0xFFU)
#if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE5 != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_START_SEC_VAR_CLEARED_ASIL_B_CORE5_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Pwm_17_GtmCcu6_MemMap.h"

static Pwm_17_GtmCcu6_ChannelStatusType \
Pwm_17_Gtm_ChannelStatus_Core5[PWM_17_GTMCCU6_MAX_CHANNELS_CORE5];
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Pwm_17_GtmCcu6_MemMap.h"
#endif
#endif
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_START_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Pwm_17_GtmCcu6_MemMap.h"
/* Global array of pointers to store address of core status */
static Pwm_17_GtmCcu6_ChannelStatusType* const \
Pwm_CoreChannelStatus[PWM_17_GTMCCU6_MAX_CORES] =
{
  #if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE0 != 0xFFU)
  #if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE0 != 0U)
  (Pwm_17_GtmCcu6_ChannelStatusType*)Pwm_17_Gtm_ChannelStatus_Core0,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE1 != 0xFFU)
  #if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE1 != 0U)
  (Pwm_17_GtmCcu6_ChannelStatusType*)Pwm_17_Gtm_ChannelStatus_Core1,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE2 != 0xFFU)
  #if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE2 != 0U)
  (Pwm_17_GtmCcu6_ChannelStatusType*)Pwm_17_Gtm_ChannelStatus_Core2,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE3 != 0xFFU)
  #if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE3 != 0U)
  (Pwm_17_GtmCcu6_ChannelStatusType*)Pwm_17_Gtm_ChannelStatus_Core3,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE4 != 0xFFU)
  #if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE4 != 0U)
  (Pwm_17_GtmCcu6_ChannelStatusType*)Pwm_17_Gtm_ChannelStatus_Core4,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE5 != 0xFFU)
  #if (PWM_17_GTMCCU6_MAX_CHANNELS_CORE5 != 0U)
  (Pwm_17_GtmCcu6_ChannelStatusType*)Pwm_17_Gtm_ChannelStatus_Core5,
  #else
  NULL_PTR,
  #endif
  #endif
};
#if((PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON))
static Ifx_CCU6* const Pwm_17_GtmCcu6_Kernel[MCU_17_CCU6_NO_OF_KERNELS] =
{
  &MODULE_CCU60,
  #if ( MCU_17_CCU6_NO_OF_KERNELS > 1U )
  &MODULE_CCU61
  #endif
};
#endif
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define PWM_17_GTMCCU6_STOP_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Pwm_17_GtmCcu6_MemMap.h"

/******************************************************************************
**                      Private Function Declarations                        **
******************************************************************************/
/* [cover parentID={726B69EC-E5CD-4ec6-852A-9F9C0841D4D4}]
The source code of PWM driver is placed under single MemMap section.
It is possible to access the code from all CPU cores.[/cover] */
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
Memory Mapping code [/cover] */
#define PWM_17_GTMCCU6_START_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Pwm_17_GtmCcu6_MemMap.h"
/******************************************************************************
** Syntax : void Pwm_17_GtmCcu6_Init(const Pwm_17_GtmCcu6_ConfigType         **
**                                                                *ConfigPtr)**
**                                                                           **
** Service ID:      0x00                                                     **
**                                                                           **
** Sync/Async:      Synchronous                                              **
**                                                                           **
** Reentrancy:      Non Reentrant                                            **
**                                                                           **
** Parameters (in): ConfigPtr - Pointer to configuration set                 **
**                                                                           **
** Parameters (out):none                                                     **
**                                                                           **
** Return value:    none                                                     **
**                                                                           **
** Description : Driver Module Initialization                                **
**               1.This function will initialize all relevant registers of   **
**                 configured hardware (Assigned_HW_Unit) with the values of **
**                 structure given by ConfigPtr.                             **
**               2. This service will disable all notifications.             **
**               3. Resources that are not configured in the configuration   **
**                  file will not be changed.                                **
**               4. This function shall initialize all internals variables   **
**               5. After initialization the PWM driver will start generate  **
**                  PWM signal(s) with the configured default values         **
**               6. Service should not be called during a running operation. **
**                                                                           **
** Traceability   :  [cover parentID={E4EC3EA2-8E9F-4712-92C1-D3D5ACADE93E}] **
**                   [/cover]                                                **
**                                                                           **
******************************************************************************/
/*CYCLOMATIC_Pwm_17_GtmCcu6_Init_JUSTIFICATION:SHIFT_BY_OFFSET feature needs
   all GTM channels to be started synchronously. This indeed demands looping
   through all the TGC/AGCs and set host trigger for all configured TGCs */
/* [cover parentID={FD3466C9-7402-465e-A09C-DFF3DAC0BBF3}]
   API naming convention [/cover] */
void Pwm_17_GtmCcu6_Init
(
  const Pwm_17_GtmCcu6_ConfigType * const ConfigPtr
)
{
  #if (PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
  #if (PWM_17_GTMCCU6_HANDLE_SHIFT_BY_OFFSET == STD_ON)
  uint8 ModuleNo;
  uint32 PwmTomTrig[MCU_17_GTM_NO_OF_TOM_MODULES];
  uint16 PwmAtomTrig[MCU_17_GTM_NO_OF_ATOM_MODULES];
  uint16                                  TriggerVal;
  uint8                                   PwmTimerPos;
  #endif
  /* (PWM_17_GTMCCU6_HANDLE_SHIFT_BY_OFFSET == STD_ON) */
  Mcu_17_Gtm_TimerOutType                 PwmGtmTimerType;
  uint8                                   TimerChannelNumber;
  uint8                                   TimerModuleNumber;
  uint8                                   PwmTimerType;
  const Mcu_17_Gtm_TomAtomChConfigType    *PwmGtmTimerPtr;
  #endif
  /* (PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON) */
  Pwm_17_GtmCcu6_ChannelType              ChannelNumber;
  #if ((PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON) || \
       (PWM_17_GTMCCU6_DEV_ERROR_DETECT == STD_ON))
  uint8                                   ErrStatus;
  #endif
  const Pwm_17_GtmCcu6_CoreConfigType     *PwmCorePtr;
  Pwm_17_GtmCcu6_CoreStatusType           *LocalCoreStatusPtr;
  Pwm_17_GtmCcu6_ChannelStatusType        *LocalChannelStatusPtr;
  const Pwm_17_GtmCcu6_ChannelConfigType  *PwmChannelCfgPtr;
  uint32                                  CoreId;
  Pwm_17_GtmCcu6_ChannelClassType         ChannelKind;
  /* [cover parentID={7C2690E2-A26A-4abb-B2CA-33CFDF1DDF5F}]
  Get core ID [/cover] */
  CoreId = Mcal_GetCpuIndex();
  /* [cover parentID={47EA5C0E-DA0E-4287-A1FC-B229B5A72459}]
  Is DET OR Safety is enabled [/cover] */
  #if ((PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON) || \
       (PWM_17_GTMCCU6_DEV_ERROR_DETECT == STD_ON))
  /* [cover parentID={C54FDCDA-4432-43a3-B960-A314F59114FF}]
  Any error reported [/cover] */
  ErrStatus = Pwm_lInitDetCheck(ConfigPtr, CoreId);
  /* [cover parentID={C54FDCDA-4432-43a3-B960-A314F59114FF}]
  Any error reported [/cover] */
  if(ErrStatus == (uint8)E_OK)
  #endif
  {
    LocalCoreStatusPtr = PwmCoreStatusPtr[CoreId];
    LocalCoreStatusPtr->Pwm_CoreInitStatus = PWM_INITIALIZE_REQ;
    Pwm_ConfigPtr = ConfigPtr;
    PwmCorePtr = Pwm_ConfigPtr->PwmCoreAdd[CoreId];
    PwmChannelCfgPtr = PwmCorePtr->Pwm_ChannelConfigPtr;
    LocalChannelStatusPtr = Pwm_CoreChannelStatus[CoreId];
    #if (PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
    #if (PWM_17_GTMCCU6_HANDLE_SHIFT_BY_OFFSET == STD_ON)
    for(ModuleNo = 0U; ModuleNo < (uint32)(MCU_17_GTM_NO_OF_TOM_MODULES)\
        ; ModuleNo++)
    {
      PwmTomTrig[ModuleNo] = 0U;
    }
    for(ModuleNo = 0U; ModuleNo < (uint32)(MCU_17_GTM_NO_OF_ATOM_MODULES)\
        ; ModuleNo++)
    {
      PwmAtomTrig[ModuleNo] = 0U;
    }
    #endif
    #endif
    /* Initialize all configured channels for current core */
    /* [cover parentID={0C4FA828-9ADA-4607-A087-5528DDE156A6}]
    Initialize all channels configured for current core [/cover] */
    for (
      ChannelNumber = (Pwm_17_GtmCcu6_ChannelType)0;
      ChannelNumber < PwmCorePtr->MaxChannels;
      ChannelNumber++
    )
    {
      #if (PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
      /* [cover parentID={801204F8-47CD-4355-8788-BA53AB34C011}]
      PWM_17_GTMCCU6_HANDLE_SHIFT_BY_OFFSET == STD_ON [/cover] */
      #if (PWM_17_GTMCCU6_HANDLE_SHIFT_BY_OFFSET == STD_ON)
      PwmTimerType = PwmChannelCfgPtr->PwmTimerUsed;
      /* [cover parentID={39D5CCEA-E1B3-4b04-92E1-6C875A9B471B}]
      Initialize configured channel [/cover] */
      /* [cover parentID={4E122631-A519-40b3-8DB7-5FE310783E95}]
      If timer type is GTM [/cover] */
      if(PwmTimerType == PWM_17_GTMCCU6_GTM_TIMER)
      {
        /* MISRA2012_RULE_11_5_JUSTIFICATION: PwmTimerPtr is of
        type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
        by violating this MISRA rule.*/
        /* MISRA2012_RULE_11_3_JUSTIFICATION: PwmTimerPtr is of
        type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
        by violating this MISRA rule.*/
        PwmGtmTimerPtr = (const Mcu_17_Gtm_TomAtomChConfigType*)\
                         PwmChannelCfgPtr->PwmTimerPtr;
        TimerModuleNumber = (uint8)((PwmGtmTimerPtr->TimerId &\
                                   GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);
        TimerChannelNumber  = (uint8)((PwmGtmTimerPtr->TimerId &\
                                   GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);
        PwmGtmTimerType = PwmGtmTimerPtr->TimerType;
        PwmTimerPos = TimerChannelNumber * PWM_CONST_2;
        /* [cover parentID={813436CA-6763-4d0f-93CB-C7C4C585975E}]
        If timer type is TOM [/cover] */
        if(PwmGtmTimerType == MCU_GTM_TIMER_TOM)
        {
          /* [cover parentID={8D62215E-38F1-4f3c-8F01-D10EB607694E}]
          Store the TGC's which have to be triggered by Host trigger [/cover] */
          PwmTomTrig[TimerModuleNumber] |= ((uint32)PWM_CONST_2 << PwmTimerPos);
        }
        else
        {
          /* [cover parentID={C9CEA102-1671-442a-A58B-A3A172031F1D}]
          Store the AGC's which have to be triggered by Host trigger [/cover] */
          PwmAtomTrig[TimerModuleNumber] |=((uint16)PWM_CONST_2<<PwmTimerPos);
        }
      }
      #endif
      #endif
      /* Initialize global variable */
      LocalChannelStatusPtr->Pwm_GlobChn = 0U;
      ChannelKind = Pwm_lChanClass(PwmChannelCfgPtr->PwmChannelInfo);
      switch (ChannelKind)
      {
        case PWM_17_GTMCCU6_VARIABLE_PERIOD:
          /* [cover parentID={2F7C5C35-9C88-425b-9DB2-294165D08772}]
          If channel class is variable period [/cover] */
          Pwm_lInitVariablePeriod(ChannelNumber, (uint8)CoreId);
          break;
        case PWM_17_GTMCCU6_FIXED_PERIOD:
          /* [cover parentID={1BBE4AC4-F443-45b2-A3BA-F2D3567D2C3F}]
          If channel class is fixed period [/cover] */
          Pwm_lInitFixedPeriod(ChannelNumber, (uint8)CoreId);
          break;
        case PWM_17_GTMCCU6_FIXED_PERIOD_SHIFTED:
          /* [cover parentID={1BC41292-50F4-4cf6-8517-A9139EEF6D4F}]
          If channel class is fixed period shifted [/cover] */
          Pwm_lInitShiftedCentreAligned(ChannelNumber, (uint8)CoreId);
          break;
        default:
          /* [cover parentID={A0D6B62F-A233-4d66-B1C4-7D92C2C03691}]
          Initialize fixed period centre aligned [/cover] */
          Pwm_lInitShiftedCentreAligned(ChannelNumber, (uint8)CoreId);
          break;
      }
      PwmChannelCfgPtr++;
      LocalChannelStatusPtr++;
    }
    #if (PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
    /* [cover parentID={0A111610-4C52-4138-8CAD-40D0E696FDC8}]
    Is shift by offset enabled [/cover] */
    /* [cover parentID={A4D161C5-B196-4121-93C2-536DCA404799}]
    Is shift by offset enabled [/cover] */
    #if (PWM_17_GTMCCU6_HANDLE_SHIFT_BY_OFFSET == STD_ON)
    /* Set host trigger to configured TOM TGC */
    for(ModuleNo = 0U; ModuleNo < (uint32)(MCU_17_GTM_NO_OF_TOM_MODULES)\
        ; ModuleNo++)
    {
      TriggerVal = (uint16)(PwmTomTrig[ModuleNo] & PWM_16BIT_MASK);
      if(TriggerVal != 0U)
      {
        /* [cover parentID={674D5255-E15A-47d3-92FE-2203287EDA38}]
        Set host trigger for configured TGC channels [/cover] */
        /* Start TGC 0 of selected module */
        Mcu_17_Gtm_TomTriggerRequest(ModuleNo, 0U, TriggerVal);
      }
      TriggerVal = (uint16)((PwmTomTrig[ModuleNo] & PWM_16BIT_MASK_UPPER) >> \
                            PWM_CONST_16);
      if(TriggerVal != 0U)
      {
        /* Start TGC 1 of selected module */
        /* [cover parentID={674D5255-E15A-47d3-92FE-2203287EDA38}]
        Set host trigger for configured TGC channels [/cover] */
        Mcu_17_Gtm_TomTriggerRequest(ModuleNo, 1U, TriggerVal);
      }
    }
    for(ModuleNo = 0U; ModuleNo < (uint32)(MCU_17_GTM_NO_OF_ATOM_MODULES)\
        ; ModuleNo++)
    {
      TriggerVal = PwmAtomTrig[ModuleNo];
      if(TriggerVal != 0U)
      {
        /* [cover parentID={73618B72-7B8B-4696-B985-5619341CE381}]
        Set host triger for current AGC automatic write [/cover] */
        Mcu_17_Gtm_AtomTriggerRequest(ModuleNo, TriggerVal);
      }
    }
    #endif
    PwmChannelCfgPtr = PwmCorePtr->Pwm_ChannelConfigPtr;
    for (ChannelNumber = (Pwm_17_GtmCcu6_ChannelType)0;\
                  ChannelNumber < PwmCorePtr->MaxChannels; ChannelNumber++)
    {
      PwmTimerType = PwmChannelCfgPtr->PwmTimerUsed;
      /* MISRA2012_RULE_11_5_JUSTIFICATION: PwmTimerPtr is of
      type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
      by violating this MISRA rule.*/
      /* MISRA2012_RULE_11_3_JUSTIFICATION: PwmTimerPtr is of
      type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
      by violating this MISRA rule.*/
      PwmGtmTimerPtr = (const Mcu_17_Gtm_TomAtomChConfigType*)\
                       PwmChannelCfgPtr->PwmTimerPtr;

      /* [cover parentID={C990F905-992D-4293-ABB0-54CF30C44A30}]
        Is GTM timer used [/cover] */
      if(PwmTimerType == PWM_17_GTMCCU6_GTM_TIMER)
      {
        /* (PWM_17_GTMCCU6_HANDLE_SHIFT_BY_OFFSET == STD_ON) */
        TimerModuleNumber    = (uint8)((PwmGtmTimerPtr->TimerId &\
                                   GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);
        TimerChannelNumber   = (uint8)((PwmGtmTimerPtr->TimerId &\
                                   GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);
        PwmGtmTimerType      = PwmGtmTimerPtr->TimerType;
        /* OUTEN & ENDIS control should reset in Init for all the GTM channels
        after performing host trigger.If OUTEN and ENDIS bits are not reset 
        after init, Unintended shadow transfers may occur during runtime,
        leading to incorrect signal output.*/
        /* [cover parentID={73B86F20-17AC-47f5-A52E-225F848452B9}]
        Reset OUTEN and ENDIS control register [/cover] */
        Pwm_lGtmResetOutEnEndisCtrl(TimerModuleNumber, TimerChannelNumber, \
                                                              PwmGtmTimerType);
      }
      PwmChannelCfgPtr++;
    }
    #endif
    /*# if PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON */
    /* [cover parentID={3F3532F3-7278-44de-8C2B-5A9A3114B6B2}]
    If CCU6 Timer used [/cover] */
    #if (PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
    /* Start CCu6 timers */
    /* [cover parentID={CE6EB38F-0F33-4498-B23A-C53578C8414B}]
    Start CCU6 timers synchronously [/cover] */
    Pwm_lCcu6StartTimerSync((uint8)CoreId);
    #endif
    
    /* [cover parentID={6F5F5048-A6B1-42aa-8B94-BDDA655AB02F}]
    Set PWM initialization status flag for current core [/cover] */
    /* [cover parentID={6F5F5048-A6B1-42aa-8B94-BDDA655AB02F}]
    Set PWM initialization status flag for current core [/cover] */
    LocalCoreStatusPtr->Pwm_CoreInitStatus = PWM_INITIALIZED;
  }
}

#if (PWM_17_GTMCCU6_INITCHECK_API == STD_ON)
/******************************************************************************
** Syntax : void Pwm_17_GtmCcu6_InitCheck                                    **
**                   (                                                       **
**                     const Pwm_17_GtmCcu6_ConfigType *const ConfigPtr)     **
**                   )                                                       **
** Service ID:      0x10                                                     **
**                                                                           **
** Sync/Async:      Synchronous                                              **
**                                                                           **
** Reentrancy:      Non reentrant                                            **
**                                                                           **
** Parameters (in) :None                                                     **
**                                                                           **
** Parameters (out):None                                                     **
**                                                                           **
** Return value    :E_OK - Init Check Successfull                            **
**                  E_NOT_OK - Init Check Failed                             **
**                                                                           **
** Description : This routine verifies the Initialization of the PWM driver. **
**                                                                           **
** Traceability : [cover parentID={250135A0-1F3A-4c61-A8C7-1AA3E69EED55}]    **
**                      [/cover]                                             **
******************************************************************************/
/*CYCLOMATIC_Pwm_17_GtmCcu6_InitCheck_JUSTIFICATION: InitCheck feature needs to
   evaluate registers of configured GTM and CCU6 channels along with Config
   pointer and Initstatus. Breaking into multiple functions is not done for
   readability and maintainability.*/
Std_ReturnType Pwm_17_GtmCcu6_InitCheck
(
  const Pwm_17_GtmCcu6_ConfigType * const ConfigPtr
)
{
  uint32                                  CoreId;
  const Pwm_17_GtmCcu6_CoreConfigType     *PwmCorePtr;
  const Pwm_17_GtmCcu6_ChannelConfigType  *PwmChannelCfgPtr;
  const Pwm_17_GtmCcu6_CoreStatusType     *LocalCoreStatusPtr;
  Pwm_17_GtmCcu6_ChannelType              ChannelNumber;
  Pwm_17_GtmCcu6_ChannelClassType         ChannelKind;
  Std_ReturnType                          ErrorStatus = E_OK;
  #if (PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
  uint8                                   PwmTimerType;
  const Mcu_17_Gtm_TomAtomChConfigType    *PwmGtmTimerPtr;
  Mcu_17_Gtm_TimerOutType                 PwmGtmTimerType;
  uint8                                   TimerChannelNumber;
  uint8                                   TimerModuleNumber;
  #endif
  /* [cover parentID={9B6F2CD2-01B7-4911-8C98-2731590B9EAF}]
  Is configuration pointer is NULL
  [/cover] */
  if(NULL_PTR != ConfigPtr)
  {
    /* [cover parentID={3E25A685-A655-43fe-9EBD-9789BD3360DF}]
    Is configuration pointer not equal to the one used for 
    initialization [/cover] */
    if(ConfigPtr == Pwm_ConfigPtr)
    {
      CoreId = Mcal_GetCpuIndex();
      /* [cover parentID={077F56E6-D01D-4ef5-9CC5-AB602D6E163D}]
      Is core configured and initialized  [/cover] */
      LocalCoreStatusPtr = PwmCoreStatusPtr[CoreId];
      if(LocalCoreStatusPtr == NULL_PTR)
      {
        /* [cover parentID={FA075A0B-AD99-4acc-BCB1-B191AC86C6B6}]
        Set error status to E_NOT_OK [/cover] */
        ErrorStatus = E_NOT_OK;
      }
      else if (LocalCoreStatusPtr->Pwm_CoreInitStatus != PWM_INITIALIZED)
      {
        ErrorStatus = E_NOT_OK;
      }
      else
      {
        /* Do Nothing*/
      }
      /* [cover parentID={F2F2A7A1-91D0-4de2-A2C8-2290783F2555}]
      Is error status OK [/cover] */
      /* [cover parentID={AE5D2EB5-C954-4293-9C05-1BD1AFE08E05}][/cover] */
      if(ErrorStatus == E_OK)
      {
        PwmCorePtr = Pwm_ConfigPtr->PwmCoreAdd[CoreId];
        PwmChannelCfgPtr = PwmCorePtr->Pwm_ChannelConfigPtr;
        /* [cover parentID={3EA14A9F-2E7A-44df-A331-52997807E11C}]
        Init check for channel class [/cover] */
        for(ChannelNumber = (Pwm_17_GtmCcu6_ChannelType)0; \
           (ChannelNumber < PwmCorePtr->MaxChannels) && \
           (ErrorStatus != E_NOT_OK); ChannelNumber++)
        {
          ChannelKind = Pwm_lChanClass(PwmChannelCfgPtr->PwmChannelInfo);
          switch (ChannelKind)
          {
            /* [cover parentID={B90615FC-87AE-4ecc-8714-1F1E894E3002}]
            If channel class is variable period [/cover] */
            case PWM_17_GTMCCU6_VARIABLE_PERIOD:
              /* Variable Period */
              ErrorStatus = \
                    Pwm_lInitVariablePeriodCheck(ChannelNumber, (uint8)CoreId);
              break;
            /* [cover parentID={24E3369E-C8ED-4a0c-8990-7A6463201EA6}]
            If channel class is fixed period [/cover] */
            case PWM_17_GTMCCU6_FIXED_PERIOD:
              /* Fixed Period */
              ErrorStatus=Pwm_lInitFixedPeriodCheck(ChannelNumber,\
                                                                (uint8)CoreId);
              break;
            /* [cover parentID={778B9A32-07D7-4323-A0DC-C83F028EED59}]
            If channel class is fixed period shifted [/cover] */
            case PWM_17_GTMCCU6_FIXED_PERIOD_SHIFTED:
              ErrorStatus = \
               Pwm_lInitShiftedCentreAlignedCheck(ChannelNumber,(uint8)CoreId);
              break;
            /* [cover parentID={1F389931-9886-4790-AD2B-26500CE25BA3}]
            If channel class is center aligned [/cover] */
            default:
              /* Default: Init center aligned channels */
              ErrorStatus = \
               Pwm_lInitShiftedCentreAlignedCheck(ChannelNumber,(uint8)CoreId);
              break;
          }
          /* [cover parentID={4DC267D7-0172-401c-86F2-4D74D05BF66F}]
          Is GTM timer used [/cover] */
          #if (PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
          if(ErrorStatus == E_OK)
          {
            PwmTimerType = PwmChannelCfgPtr->PwmTimerUsed;
            /* Configure port pin for this timer channel */
            /* MISRA2012_RULE_11_5_JUSTIFICATION: PwmTimerPtr is of
            type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
            by violating this MISRA rule.*/
            /* MISRA2012_RULE_11_3_JUSTIFICATION: PwmTimerPtr is of
            type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
            by violating this MISRA rule.*/
            PwmGtmTimerPtr = (const Mcu_17_Gtm_TomAtomChConfigType*)\
                             PwmChannelCfgPtr->PwmTimerPtr;
            /* [cover parentID={D2DC5775-B726-4377-AF62-F44060B75406}]
            If timer used is GTM [/cover] */
            if(PwmTimerType == PWM_17_GTMCCU6_GTM_TIMER)
            {
              TimerModuleNumber  = (uint8)((PwmGtmTimerPtr->TimerId &\
                                     GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);
              TimerChannelNumber = (uint8)((PwmGtmTimerPtr->TimerId &\
                                   GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);
              PwmGtmTimerType    = PwmGtmTimerPtr->TimerType;
              /* [cover parentID={821556C1-3051-4525-B536-BA7267536EF6}]
              Check ENDIS and OUTEN reset state [/cover] */
              ErrorStatus = Pwm_lGtmResetOutEnEndisCtrlCheck(\
                       TimerModuleNumber, TimerChannelNumber, PwmGtmTimerType);
            }
          }
          #endif
          PwmChannelCfgPtr++;
        }
        /* [cover parentID={2F23A190-E903-44bd-A37C-49700CAE80A4}]
        Is CCU6 timer used [/cover] */
        #if (PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
        /* [cover parentID={7E656E70-87B3-456a-A483-BF299E2CF06C}]
        Is there error [/cover] */
        if(ErrorStatus == E_OK)
        {
          /* [cover parentID={75857A6C-1FA1-4bd1-988F-C7D4B778BD07}]
          Start CCU6 timers synchronously [/cover] */
          ErrorStatus = Pwm_lCcu6StartTimerSyncCheck((uint8)CoreId);
        }
        #endif
      }
    }
    else
    {
      /* [cover parentID={C56BAF28-3C49-40b7-AB25-5B14325D63DB}]
      Set error status to E_NOT_OK [/cover] */
      ErrorStatus = E_NOT_OK;
    }
  }
  else
  {
    /* [cover parentID={C56BAF28-3C49-40b7-AB25-5B14325D63DB}]
    Set error status to E_NOT_OK [/cover] */
    ErrorStatus = E_NOT_OK;
  }
  return ErrorStatus;
}
#endif

#if (PWM_17_GTMCCU6_DE_INIT_API == STD_ON)
/******************************************************************************
** Syntax : void Pwm_17_GtmCcu6_DeInit(void)                                 **
**                                                                           **
** Service ID: 0x01                                                          **
**                                                                           **
** Sync/Async: Synchronous                                                   **
**                                                                           **
** Reentrancy: Non reentrant                                                 **
**                                                                           **
** Parameters (in): none                                                     **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:none                                                         **
**                                                                           **
** Description : Service for PWM De-Initialization                           **
**               1.After the call of this service, the state of the used     **
**                 peripherals/registers will set to power on reset state.   **
**               2.This service will disable all used interrupts and         **
**                  notifications.                                           **
**               3.This service clear all pending interrupt flags            **
**               4.All global variables will get reset                       **
**               5.All channel output signal state will set to Idle State    **
**                                                                           **
** Traceability :[cover parentID={7C22B3DF-7411-470c-97B2-066CD2C77ADD}]     **
**                   [/cover]                                                **
******************************************************************************/
void Pwm_17_GtmCcu6_DeInit(void)
{
  const Pwm_17_GtmCcu6_ChannelConfigType  *PwmChannelCfgPtr;
  const Pwm_17_GtmCcu6_CoreConfigType     *PwmCorePtr;
  Pwm_17_GtmCcu6_CoreStatusType     *LocalCoreStatusPtr;
  const Pwm_17_GtmCcu6_CoreStatusType    *TempCoreStatusPtr;
  Pwm_17_GtmCcu6_ChannelStatusType        *LocalChannelStatusPtr;
  #if (PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
  const Mcu_17_Gtm_TomAtomChConfigType    *PwmGtmTimerPtr;
  Mcu_17_Gtm_TimerOutType                 PwmGtmTimerType;
  uint8 TimerChannelNumber;
  uint8 TimerModuleNumber;
  uint8 PwmTimerType;
  #endif
  Pwm_17_GtmCcu6_ChannelType              ChannelNumber;
  Pwm_17_GtmCcu6_OutputStateType          IdleState;
  uint32                                  CoreId;
  #if(PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
  uint8                                   Polarity;
  uint32                                  Duty;
  #endif
  uint32                                  CoreTemp;
  uint8                                   ClearConfigPtr = 0U;

  #if ((PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON) || \
      (PWM_17_GTMCCU6_DEV_ERROR_DETECT == STD_ON))
  uint8                              ErrStatus;
  #endif

  #if ((PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON) ||\
      (PWM_17_GTMCCU6_DEV_ERROR_DETECT == STD_ON))
  ErrStatus                 =        (uint8)E_OK;
  #endif
  CoreId = Mcal_GetCpuIndex();
  /* [cover parentID={8B0C9569-6CE2-4150-93D8-41922C661604}]
  If DET OR SAFETY is enabled [/cover] */
  #if ((PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON) || \
      (PWM_17_GTMCCU6_DEV_ERROR_DETECT == STD_ON))
  /* [cover parentID={A25B6AD6-DF80-41b9-90E4-4875034941F1}]
  Check current core initialization status [/cover] */
  /* [cover parentID={A46C66B6-EBE9-4c94-87EA-FEA678043881}]
  If any error reported [/cover] */
  if (PWM_ERROR_FOUND == Pwm_lVerUnInit(PWM_17_GTMCCU6_SID_DEINIT, \
                                        (uint8)CoreId))
  {
    /* Return without executing any of functionality */
    ErrStatus = (uint8)E_NOT_OK;
  }
  #endif
  /* [cover parentID={8B0C9569-6CE2-4150-93D8-41922C661604}]
  If DET OR SAFETY is enabled [/cover] */
  #if ((PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON) || \
      (PWM_17_GTMCCU6_DEV_ERROR_DETECT == STD_ON))
  /* [cover parentID={ED8BAB9F-906D-426a-BBED-1BEA20B3F395}]
  If error status is OK [/cover] */
  if(ErrStatus == (uint8)E_OK)
  #endif
  {
    /* Clear the Status to indicate that Deinitialization is done */
    /* [cover parentID={8BBD98A6-D9EB-4cae-9D1A-7A15194EFB01}]
      Set core Init status to Deinit requested [/cover] */
    LocalCoreStatusPtr = PwmCoreStatusPtr[CoreId];
    LocalCoreStatusPtr->Pwm_CoreInitStatus = PWM_DEINITIALIZE_REQ;
    /* Initialize PWM configured channel ROM pointer */
    PwmCorePtr = Pwm_ConfigPtr->PwmCoreAdd[CoreId];
    PwmChannelCfgPtr = PwmCorePtr->Pwm_ChannelConfigPtr;
    LocalChannelStatusPtr = Pwm_CoreChannelStatus[CoreId];
    /* [cover parentID={AE4FF5C0-E898-4f76-953A-E798298632F3}]
    De-initialize all channel of current core [/cover] */
    for ( ChannelNumber = (Pwm_17_GtmCcu6_ChannelType)0U;
          ChannelNumber < PwmCorePtr->MaxChannels;
          ChannelNumber++
        )
    {
      #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
      /* [cover parentID={4D1E45B6-F830-4591-BF10-D4A992E64ED5}]
      De-Initialize the channel [/cover] */
      PwmTimerType       = PwmChannelCfgPtr->PwmTimerUsed;
      #endif
      LocalChannelStatusPtr->Pwm_GlobChn = (uint32)0U;
      /* [cover parentID={20E46C6A-949E-4ff9-B64E-C0951206B8F5}]
      Set 0 in current period value [/cover] */
      LocalChannelStatusPtr->Pwm_CurrentPeriodVal = (uint32)0U;

      /* Extract IdleState,polarity*/
      IdleState = Pwm_lIdle(PwmChannelCfgPtr->PwmChannelInfo);
      #if (PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
      /* [cover parentID={E897E9B2-CB2E-4511-A6FE-EE1BFD7AE43D}]
      If timer type is GTM [/cover] */
      if(PwmTimerType == PWM_17_GTMCCU6_GTM_TIMER)
      {
        /* MISRA2012_RULE_11_5_JUSTIFICATION: PwmTimerPtr is of
        type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
        by violating this MISRA rule.*/
        /* MISRA2012_RULE_11_3_JUSTIFICATION: PwmTimerPtr is of
        type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
        by violating this MISRA rule.*/
        PwmGtmTimerPtr = (const Mcu_17_Gtm_TomAtomChConfigType*)\
                         PwmChannelCfgPtr->PwmTimerPtr;
        TimerModuleNumber    = (uint8)((PwmGtmTimerPtr->TimerId & \
                                 GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);
        TimerChannelNumber   = (uint8)((PwmGtmTimerPtr->TimerId & \
                                 GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);
        PwmGtmTimerType         = PwmGtmTimerPtr->TimerType;
        /* [cover parentID={75C59B0A-7B4A-43af-8024-2535BD4C9C50}]
        If GTM timer type is TOM [/cover] */
        if(PwmGtmTimerType == MCU_GTM_TIMER_TOM)
        {
          /* [cover parentID={7F76F45C-A9F1-43fe-BE38-6A573DB65A8C}]
          De-Initialize TOM timer [/cover] */
          Pwm_lTomDeInit(TimerModuleNumber, TimerChannelNumber, IdleState);
        }
        else
        {
          /* [cover parentID={462880E4-35C4-4610-89AA-5D8664A12CD7}]
          De-Initialize ATOM timer [/cover] */
          Pwm_lAtomDeInit(TimerModuleNumber, TimerChannelNumber, IdleState);
        }
      }
      else
      #endif
      /* [cover parentID={A274A0D9-9C5A-4a7c-9E06-AE5C9EEB2543}]
      If timer type is CCU6 [/cover] */
      {
        #if(PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
        Polarity = PWM_GET_POLARITY(Pwm_ConfigPtr->PwmCoreAdd\
                 [CoreId]->Pwm_ChannelConfigPtr[ChannelNumber].PwmChannelInfo);
        #if (PWM_17_GTMCCU6_DUTY_SHIFT_IN_TICKS == STD_ON)
        Duty = Pwm_lMaxDuty(ChannelNumber, (uint8)CoreId);
        #else
        /* [cover parentID={9B758363-98F4-478a-B5F2-C58BBABE858D}]
        Set duty to maximum [/cover] */
        Duty = PWM_MAX_TIMER_CCU6;
        #endif
        /*[cover parentID={9991920E-A88B-4f0c-8513-86B5BFF41E42}][/cover] */
        if (IdleState != Polarity)
        {
          /* Idle state and Polarity mismatches then 0 % duty desired */
          /* [cover parentID={49C9BDBD-1918-4fc2-9AE7-D7E7B1A4E0CB}]
          Set channel to idle state [/cover] */
          /* [cover parentID={5FD9D7C8-6BD1-411c-8969-A4B346070466}]
          Set duty to zero [/cover] */
          Duty = 0U;
        }
        /* [cover parentID={49C9BDBD-1918-4fc2-9AE7-D7E7B1A4E0CB}]
        Set channel to idle state [/cover] */
        Pwm_lCcu6StartChannelIdle
        (ChannelNumber, Duty, (uint8)CoreId);
        /* [cover parentID={A5DFFDFA-C242-4080-81EB-16173CCA9194}]
        Disable Interrupts for each CCU6 channel [/cover] */
        /* Disable Interrupts for each channel */
        Pwm_lCcu6IrqModify(ChannelNumber, 0U, (uint8)CoreId);
        #endif
      }
      PwmChannelCfgPtr++;
      LocalChannelStatusPtr++;
    }

    /* Clear the Status to indicate that Deinitialization is done */
    /* [cover parentID={32446FB5-F36D-4176-8B00-B97D8F546C9A}]
    Clear the Status to indicate that Deinitialization is done for current core
    [/cover] */
    LocalCoreStatusPtr->Pwm_CoreInitStatus = PWM_DEINITIALIZED;
    /* [cover parentID={4CBB1474-F789-4b89-A37F-575897A509D3}]
    Clear configuration pointer, If all cores are Deinitialized [/cover] */
    CoreTemp = 0U;
    #if(PWM_17_GTMCCU6_MAX_CORES > 1U)
    for (;CoreTemp < PWM_17_GTMCCU6_MAX_CORES; CoreTemp++)
    #endif
    {
      TempCoreStatusPtr = PwmCoreStatusPtr[CoreTemp];
      #if(PWM_17_GTMCCU6_MAX_CORES > 1U)
      if(TempCoreStatusPtr != NULL_PTR)
      #endif
      {
        if(TempCoreStatusPtr->Pwm_CoreInitStatus != PWM_DEINITIALIZED)
        {
          ClearConfigPtr = 1U;
        }
      }
    }
    if(ClearConfigPtr == 0U)
    {
      /* Clear ConfigPtr */
      Pwm_ConfigPtr = NULL_PTR;
    }
  }
}
#endif
#if (PWM_17_GTMCCU6_SET_DUTY_CYCLE_API == STD_ON)
/******************************************************************************
** Syntax : void Pwm_17_GtmCcu6_SetDutyCycle                                 **
**                 (                                                         **
**                   const Pwm_17_GtmCcu6_ChannelType ChannelNumber,         **
**                   uint16 DutyCycle                                        **
**                 )                                                         **
**                 Note: Duty cycle is uint32 if DutyCycle is given in ticks **
** Service ID:0x02                                                           **
**                                                                           **
** Sync/Async:Synchronous                                                    **
**                                                                           **
** Reentrancy:Reentrant for different channels                               **
**                                                                           **
** Parameters (in): ChannelNumber : Numeric identifier of the PWM channel    **
**                  DutyCycle     : To set Duty Cycle for a PWM channel      **
**                  Note:Range of Duty cycle varies based on STD_ON or       **
**                       STD_OFF of macro PWM_17_GTMCCU6_DUTY_SHIFT_IN_TICKS **
**                  When STD_OFF: Min=0x0000 and Max=0x8000                  **
**                  When STD_ON:  Min=0x0000 and Max=0xFFFF for TOM and CCU6 **
**                                Min=0x0000 and Max=0xFFFFFF for ATOM       **
** Parameters (out): none                                                    **
**                                                                           **
** Return value: none                                                        **
**                                                                           **
** Description : Service to set Duty cycle       :                           **
**               1.This service will allow to set the duty cycle of the PWM  **
**                 channel.                                                  **
**               2.If the duty cycle = 0% (value=0x0000), then the PWM output**
**                 state will set to opposite level of polarity.             **
**               3.If the duty cycle=100% (value=0x8000), then the PWM output**
**                 state will set to polarity level.                         **
**               4.If the duty cycle>100%(value>0x8000), then the PWM output **
**                 will be undefined behavior (recommended that, user not to **
**                 provide this range of value)                              **
**               5 If the duty cycle >0% and <100%,then the PWM output will  **
**                 set to active state according to duty cycle and period    **
**                 parameters , polarity state.                              **
**                                                                           **
** Traceability    :[cover parentID={44B3297C-CA25-4f5a-A905-B36555356ED8}]  **
**                   [/cover]                                                **
******************************************************************************/
#if (PWM_17_GTMCCU6_DUTY_SHIFT_IN_TICKS == STD_OFF)
void Pwm_17_GtmCcu6_SetDutyCycle
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint16 DutyCycle
)
#else
void Pwm_17_GtmCcu6_SetDutyCycle
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint32 DutyCycle
)
#endif
{
  #if ((PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON) || \
      (PWM_17_GTMCCU6_DEV_ERROR_DETECT == STD_ON))
  uint8                               ErrStatus;
  #endif
  Pwm_17_GtmCcu6_ChannelClassType     ChannelKind;
  const Pwm_17_GtmCcu6_ChannelConfigType  *LocalPwmChanPtr;
  uint32                              Period     = 0U;
  uint32                              ScaledDuty = 0U;
  #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
  uint32                              ShiftVal;
  #endif

  uint32                              CoreId;
  Pwm_17_GtmCcu6_ChannelStatusType        *LocalChannelStatusPtr;
  uint8 PwmCoreChIdx;

  CoreId = Mcal_GetCpuIndex();
  /* [cover parentID={F139598F-1E37-458f-8E03-EFDC867D45F8}]
  Is DET enabled [/cover] */
  #if ((PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON) || \
      (PWM_17_GTMCCU6_DEV_ERROR_DETECT == STD_ON))
  ErrStatus = (uint8)E_OK;
  /* [cover parentID={5A959A79-1A4D-4e17-8B37-21E5969A40F3}]
  Check for unint and wrong channel number [/cover] */
  if (PWM_ERROR_FOUND ==
      Pwm_lVerUnInitAndChannel(PWM_17_GTMCCU6_SID_SETDUTY, \
                               ChannelNumber, (uint8)CoreId))
  {
    /* Return without executing any of functionality */
    ErrStatus = (uint8)E_NOT_OK;
  }
  #if (PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={38AFF32A-ED3F-43b6-BEF6-65DA954A0878}][/cover] */
  else if (PWM_ERROR_FOUND ==
           Pwm_lDutyRangeCheck(PWM_17_GTMCCU6_SID_SETDUTY, DutyCycle, \
                               ChannelNumber, (uint8)CoreId))
  {
    /* [cover parentID={33F05AD0-7B1A-4376-B1EF-129FFF61DE95}]
    If any DET reported [/cover] */
    ErrStatus = (uint8)E_NOT_OK;
  }
  else
  {
    /* Do Nothing */
  }
  #endif
  /* [cover parentID={F45C51D1-3C5B-4672-AEDC-57AB4CED4ABE}]
  If error status is OK [/cover] */
  if(ErrStatus == (uint8)E_OK)
  #endif
  {
    /* Get Channel index within the core */
    PwmCoreChIdx = Pwm_ConfigPtr->PwmChannelIdxmapPtr[ChannelNumber];
    LocalPwmChanPtr = &(Pwm_ConfigPtr->PwmCoreAdd\
                        [CoreId]->Pwm_ChannelConfigPtr[PwmCoreChIdx]);
    LocalChannelStatusPtr = Pwm_CoreChannelStatus[CoreId];
    LocalChannelStatusPtr = &(LocalChannelStatusPtr[PwmCoreChIdx]);
    ChannelKind = Pwm_lChanClass(LocalPwmChanPtr->PwmChannelInfo);
    #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
    ShiftVal = 0U;
    #endif

    switch (ChannelKind)
    {
      case PWM_17_GTMCCU6_VARIABLE_PERIOD:
        /* [cover parentID={FAF042FD-62DA-4ee3-A238-CD252B4430E8}]
        If channel class is variable period [/cover] */
        Period = LocalChannelStatusPtr->Pwm_CurrentPeriodVal;
        ScaledDuty = (uint32)Pwm_lGetAbsvalEdge(Period, (uint32)DutyCycle);
        break;
      case PWM_17_GTMCCU6_FIXED_PERIOD:
        /* [cover parentID={4C8D3573-A219-427a-96B3-5B0B7F80B7C8}]
        If channel class is fixed period [/cover] */
        Period = LocalPwmChanPtr->PwmPeriodDefault;
        ScaledDuty = (uint32)Pwm_lGetAbsvalEdge(Period, (uint32)DutyCycle);
        break;
      case PWM_17_GTMCCU6_FIXED_PERIOD_SHIFTED:
        /* [cover parentID={44CB32C6-88AF-42ce-8280-81D28D540B4E}]
        If channel class is fixed shifted period [/cover] */
        Period = LocalPwmChanPtr->PwmPeriodDefault;
        /* Get Scale value of Duty according to period */
        ScaledDuty = (uint32)Pwm_lGetAbsvalEdge(Period, (uint32)DutyCycle);
        #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
        /* Get the Shift lead value */
        ShiftVal = LocalPwmChanPtr->PwmShiftValue;
        #endif
        break;
      default:
        Period = LocalPwmChanPtr->PwmPeriodDefault;
        /* Get Scale value of Duty according to period */
        ScaledDuty = (uint32)Pwm_lGetAbsvalEdge(Period, (uint32)DutyCycle);
        #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
        /* Get the Shift lead value */
        ShiftVal = (uint32)Pwm_lGetCenterLead(Period, ScaledDuty);
        #endif
        break;
    }
    /* [cover parentID={CBF09B80-DE63-4e11-AE40-77BCEEE7FCF8}]
    If notification supported [/cover] */
    #if (PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON)
    /* [cover parentID={5029C7EF-399F-49cf-AA27-082F913F53A7}]
    Enter critical section [/cover] */
    SchM_Enter_Pwm_17_GtmCcu6_HandleNotification();
    /* [cover parentID={ED25B08D-47E7-4d92-BA6B-E10D251E581F}]
    Set global variables for notifications [/cover] */
    Pwm_lHandleNotif(ChannelKind, Period,ScaledDuty,PwmCoreChIdx,(uint8)CoreId);
    /* [cover parentID={2811E968-D769-401a-AB15-EDCF9A15C2EA}]
    Exit critical section [/cover] */
    SchM_Exit_Pwm_17_GtmCcu6_HandleNotification();
    #endif
    /* [cover parentID={6DCF8835-31A5-4784-A3CD-557D539EB09B}]
    If timer used is GTM [/cover] */
    #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
    if(LocalPwmChanPtr->PwmTimerUsed == PWM_17_GTMCCU6_GTM_TIMER)
    {
      /* [cover parentID={296B8CF9-F5FF-4ba3-8E65-FDDE18599919}]
      Start GTM channel [/cover] */
      Pwm_lGtmStartChannel\
      (PwmCoreChIdx, Period, ScaledDuty, ShiftVal, (uint8)CoreId);
    }
    else
    #endif
    {
      #if(PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
      /* [cover parentID={B0B2AA62-7E13-4e98-9D7C-4F6AC6C5C305}]
      Start CCU6 channel [/cover] */
      Pwm_lCcu6StartChannel(PwmCoreChIdx, Period, ScaledDuty, (uint8)CoreId);
      #endif
    }
  }
}
#endif
#if (PWM_17_GTMCCU6_SET_PERIOD_AND_DUTY_API == STD_ON)
/******************************************************************************
** Syntax : void Pwm_17_GtmCcu6_SetPeriodAndDuty                             **
**                      (                                                    **
**                        const Pwm_17_GtmCcu6_ChannelType ChannelNumber,    **
**                        const Pwm_17_GtmCcu6_PeriodType  Period,           **
**                        const uint16 DutyCycle                             **
**                      )                                                    **
**                  Note: DutyCycle is uint32 if DutyCycle is given in ticks **
**                                                                           **
** Service ID: 0x03                                                          **
**                                                                           **
** Sync/Async: Synchronous                                                   **
**                                                                           **
** Reentrancy: Reentrant for different channels                              **
**                                                                           **
** Parameters (in): ChannelNumber : Numeric identifier of the PWM channel    **
**                  Period        : Period of the PWM signal                 **
**                  DutyCycle     : Duty Cycle of PWM channel                **
**                  Note:Range of period and duty varies based on STD_ON or  **
**                       STD_OFF of macro PWM_17_GTMCCU6_DUTY_SHIFT_IN_TICKS **
**                  When STD_OFF: For Duty Cycle                             **
**                                Min=0x0000 and Max=0x8000 for DutyCycle    **
**                                For Period                                 **
**                                Min=0x0000 and Max=0xFFFF for TOM and CCU6 **
**                                Min=0x0000 and Max=0xFFFFFF for ATOM       **
**                  When STD_ON : For Period and Duty Cycle                  **
**                                Min=0x0000 and Max=0xFFFF for TOM and CCU6 **
**                                Min=0x0000 and Max=0xFFFFFF for ATOM for   **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:  none                                                       **
**                                                                           **
** Description : Service to set period and Duty cycle                        **
**               1.This service will allow to set the Period and duty cycle  **
**                 of the PWM channel.                                       **
**               2.Valid only for variable period                            **
**               3.If the duty cycle=0% (value=0x8000), then the PWM output  **
**                 state will set to opposite of Polarity level.             **
**               4.If the duty cycle=100% (value=0x8000), then the PWM       **
**                 output state will set to Polarity level.                  **
**               5.If the duty cycle>100%(value>0x8000), then the PWM output **
**                 will be undefined behavior (recommended that, user not to **
**                 provide this range of value)                              **
**               6 If the duty cycle >0% and <100%,then the PWM output will  **
**                 set to active state according to duty cycle and period    **
**                 parameters Polarity state.                                **
**                                                                           **
** Traceability    :[cover parentID={561E5E4C-8552-42b1-8BF2-0E6C903C1DCC}]  **
**                   [/cover]                                                **
******************************************************************************/
/*CYCLOMATIC_Pwm_17_GtmCcu6_SetPeriodAndDuty_JUSTIFICATION: The complexity is
   due to the configuration specific code for CCU6 or GTM or both. Breaking into
   multiple functions is not done for readability or maintainability.*/
#if (PWM_17_GTMCCU6_DUTY_SHIFT_IN_TICKS == STD_OFF)
void Pwm_17_GtmCcu6_SetPeriodAndDuty
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const Pwm_17_GtmCcu6_PeriodType Period,
  const uint16 DutyCycle
)
#else
/*Duty cycle is uint32 when duty is given in ticks*/
void Pwm_17_GtmCcu6_SetPeriodAndDuty
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const Pwm_17_GtmCcu6_PeriodType Period,
  const uint32 DutyCycle
)
#endif
{
  #if ((PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON) || \
      (PWM_17_GTMCCU6_DEV_ERROR_DETECT == STD_ON))
  uint8 ErrStatus;
  #endif
  uint32 ScaledDuty;
  uint32 CoreId;
  #if (PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON)
  Pwm_17_GtmCcu6_EdgeNotificationType NotifValue;
  #endif
  Pwm_17_GtmCcu6_ChannelStatusType *LocalChannelStatusPtr;
  #if((PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)|| \
  (PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON))
  const Pwm_17_GtmCcu6_ChannelConfigType *PwmChannelCfgPtr;
  uint8 PwmTimerType;
  #endif
  uint8 PwmCoreChIdx;
  CoreId = Mcal_GetCpuIndex();
  /* [cover parentID={9FFF05CE-0507-4c9f-837F-BB2AD87324E3}]
  Is DET enabled OR Safety Enabled [/cover] */
  #if ((PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON) || \
      (PWM_17_GTMCCU6_DEV_ERROR_DETECT == STD_ON))
  ErrStatus = (uint8)E_OK;
  #endif
  #if ((PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON) || \
      (PWM_17_GTMCCU6_DEV_ERROR_DETECT == STD_ON))
  /* [cover parentID={AE4C9CA6-9312-4221-B2DD-C588C2CB5F6E}]
  Check for UnInit and wrong channel number [/cover] */
  if (PWM_ERROR_FOUND ==
      ( Pwm_lVerUnInitChanAndPer\
        ( PWM_17_GTMCCU6_SID_SET_PERIOD_DUTY, ChannelNumber, (uint8)CoreId))
       )
  {
    /* [cover parentID={C5A31944-14B3-45c7-8E13-14D8E2866603}]
    Any error reported [/cover] */
    /* Return without executing any of functionality */
    ErrStatus = (uint8)E_NOT_OK;
  }
  #if (PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={7E76FD39-261D-461d-ACEF-0876C9EB28A5}]
  Verify range for duty and period parameter [/cover] */
  else if (PWM_ERROR_FOUND ==
           Pwm_lDutyPeriodRangeCheck(PWM_17_GTMCCU6_SID_SET_PERIOD_DUTY, \
                              DutyCycle, Period, ChannelNumber, (uint8)CoreId))
  {
    /* [cover parentID={58A6C338-15F2-4d25-BFD2-1ADEFFD5332D}]
    If any error reported [/cover] */
    /* Return without executing any of functionality */
    ErrStatus = (uint8)E_NOT_OK;
  }
  else
  {
    /* Do Nothing */
  }
  #endif
  /* [cover parentID={B220279D-4329-4a50-B6D5-F9D89608A4D7}]
  If error status is OK
  [/cover] */
  if(ErrStatus == (uint8)E_OK)
  #endif
  {
    PwmCoreChIdx = Pwm_ConfigPtr->PwmChannelIdxmapPtr[ChannelNumber];
    #if((PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)|| \
    (PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON))
    PwmChannelCfgPtr = &(Pwm_ConfigPtr->PwmCoreAdd\
                         [CoreId]->Pwm_ChannelConfigPtr[PwmCoreChIdx]);
    PwmTimerType = PwmChannelCfgPtr->PwmTimerUsed;
    #endif
    LocalChannelStatusPtr = &(Pwm_CoreChannelStatus[CoreId][PwmCoreChIdx]);
    LocalChannelStatusPtr->Pwm_CurrentPeriodVal = Period;
    /* Extract scaled duty */
    ScaledDuty = (uint32)Pwm_lGetAbsvalEdge(Period, (uint32)DutyCycle);
    /* [cover parentID={A1DFC876-A1B1-40e8-9CEF-57CC8AAB3BFD}]
    Is notification supported [/cover] */
    #if (PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON)
    NotifValue = PWM_GET_NOTIFICATION_KIND(PwmCoreChIdx,CoreId);
    NotifValue = NotifValue >> PWM_NOTIFI_EDGE_POS;
    /* [cover parentID={5C0DEDBB-5842-46fd-AAB1-0E69D47F8C79}]
    Enter critical section [/cover] */
    SchM_Enter_Pwm_17_GtmCcu6_HandleNotification();
    /* [cover parentID={409A0F9B-498F-40a7-81DE-221DCD5DAE12}]
    Critical section [/cover] */
    /* [cover parentID={FC4B07A0-AC74-4912-ABB8-4877EC198221}]
    If period is 0 [/cover] */
    if(Period == 0U)
    {
      /* [cover parentID={CE9CF7FB-7350-422c-9B24-21E3F6896C6E}]
      Clear the interrupt if duty is 0% or 100% [/cover] */
      Pwm_lDisableGtmCcu6Notif(PwmCoreChIdx, (uint8)CoreId, PwmTimerType);
      /* Clear notification status in global register */
      Pwm_lClearNotificationStatus(PwmCoreChIdx, (uint8)CoreId);
      /* Set the flag in global register to indicate the duty is 0% or 100%*/
      Pwm_lSetDuty_0_Or_100_Status(PwmCoreChIdx, (uint8)CoreId);
    }
    else
    {
      /* [cover parentID={E1B5A381-8500-413d-9CD0-330DC2323F68}]
      Is notification for 0 or 100% duty is disabled [/cover] */
      #if (PWM_17_GTMCCU6_NOTIF_FOR_100_0_ENABLE == STD_OFF)
      /* [cover parentID={90A6EFB6-8CA3-490a-AA6A-8E5F294B5DAC}]
      Is Duty is 0 or 100% [/cover] */
      if ( (ScaledDuty == 0U) || (ScaledDuty == Period))
      {
        /* [cover parentID={3380E1B1-28D8-427d-8DF2-6E582EFE71DD}]
        Clear the interrupt if duty is 0% or 100% [/cover] */
        Pwm_lDisableGtmCcu6Notif(PwmCoreChIdx, (uint8)CoreId, PwmTimerType);
        /* Clear notification status in global register */
        Pwm_lClearNotificationStatus(PwmCoreChIdx, (uint8)CoreId);
        /* Set the flag in global register to indicate the duty is 0% or 100%*/
        Pwm_lSetDuty_0_Or_100_Status(PwmCoreChIdx, (uint8)CoreId);
      }
      else
      {
        /* [cover parentID={305E77E3-66D1-403b-81EE-45168B83FE89}]
        If notification was asked earlier [/cover] */
        if ( NotifValue != PWM_NO_NOTIFICATION )
        {
          /* Set the notification status since notification is asked*/
          Pwm_lSetNotificationStatus(PwmCoreChIdx, (uint8)CoreId);
          /* [cover parentID={46649647-295C-4498-8A9B-B4F186411E31}]
          If timer type is GTM [/cover] */
          #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
          if(PwmTimerType == PWM_17_GTMCCU6_GTM_TIMER)
          {
            /* [cover parentID={96FD481D-949C-403f-95A9-B42EFECDBDAB}]
            Enable notification if duty is 0% or 100% [/cover] */
            Pwm_lGtmIrqModify(PwmCoreChIdx, NotifValue, (uint8)CoreId);
          }
          else
          #endif
          {
            #if (PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
            /* Enable notification if duty is 0% or 100% */
            Pwm_lCcu6IrqModify(PwmCoreChIdx, NotifValue, (uint8)CoreId);
            #endif
          }
        }
        /* Clear the flag in global register to indicate the duty is
         not 0% or 100%*/
        Pwm_lClearDuty_0_Or_100_Status(PwmCoreChIdx, (uint8)CoreId);
      }
      #else
      /* [cover parentID={814E8EA4-A47D-465a-9503-6E76E41F365B}]
      Is notification for 0 or 100% duty is not enabled [/cover] */
      /* [cover parentID={483FA6C3-B6AC-4914-9BFF-B353BCBFAD85}]
      Is notification is asked earlier.[/cover] */
      if (NotifValue != PWM_NO_NOTIFICATION)
      {
        /* [cover parentID={2920B889-31B7-455d-8249-14AD73FEB3DE}]
        Set the notification status since notification is asked [/cover] */
        Pwm_lSetNotificationStatus(PwmCoreChIdx, (uint8)CoreId);
        /* Enable notification */
        #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
        /* [cover parentID={4D2D904D-63A1-4447-9A4D-88285FBA5619}]
        If timer type is GTM [/cover] */
        if(PwmTimerType == PWM_17_GTMCCU6_GTM_TIMER)
        {
          /* [cover parentID={F8A0738D-5B09-4401-ACA3-9FEA3A2605A5}]
          Enable Notification [/cover] */
          Pwm_lGtmIrqModify(PwmCoreChIdx, NotifValue, (uint8)CoreId);
        }
        else
        #endif
        {
          #if (PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
          /* [cover parentID={BEF59451-ACD5-4dd6-BA74-59EF4A269F09}]
          Enable notification [/cover] */
          Pwm_lCcu6IrqModify(PwmCoreChIdx, NotifValue, (uint8)CoreId);
          #endif
        }
      }
      #endif
      /* PWM_17_GTMCCU6_NOTIF_FOR_100_0_ENABLE == STD_OFF */
    }
    SchM_Exit_Pwm_17_GtmCcu6_HandleNotification();
    /* [cover parentID={89FC448B-BDE0-46e9-A808-F5B7487C5C8E}]
    Exit critical section
    [/cover] */
    #endif
    /* [cover parentID={C9032318-4180-4e73-86D6-04A28E15528F}]
    If timer type is GTM [/cover] */
    #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
    if(PwmTimerType == PWM_17_GTMCCU6_GTM_TIMER)
    {
      /* [cover parentID={89D00CE2-3E0A-49eb-AB1B-676FB8D6845B}]
      Start GTM channel [/cover] */
      Pwm_lGtmStartChannel\
      (PwmCoreChIdx, Period, ScaledDuty, 0U, (uint8)CoreId);
    }
    else
    #endif
    {
      #if(PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
      /* [cover parentID={E685AFA2-DD7E-46b6-982C-D7F732168C26}]
      Start CCU6 channel [/cover] */
      Pwm_lCcu6StartChannel\
      (PwmCoreChIdx, Period, ScaledDuty, (uint8)CoreId);
      #endif
    }
  }
}
#endif
#if (PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON)
/******************************************************************************
** Syntax : void Pwm_17_GtmCcu6_DisableNotification                          **
**                        (                                                  **
**                          const Pwm_17_GtmCcu6_ChannelType ChannelNumber   **
**                        )                                                  **
** Service ID: 0x06                                                          **
**                                                                           **
** Sync/Async: Synchronous                                                   **
**                                                                           **
** Reentrancy: Reentrant for different channels                              **
**                                                                           **
** Parameters (in): ChannelNumber : Numeric identifier of the PWM channel    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:  none                                                       **
**                                                                           **
** Description : This service will disable all PWM signal notifications of   **
**               the channel.                                                **
**                                                                           **
** Traceability:[cover parentID={81384B3D-DE20-4561-9CE0-FB4B90239E39}]      **
**                   [/cover]                                                **
******************************************************************************/
void Pwm_17_GtmCcu6_DisableNotification(\
                                const Pwm_17_GtmCcu6_ChannelType ChannelNumber)
{
  /* Local variables */
  #if ((PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON) || \
      (PWM_17_GTMCCU6_DEV_ERROR_DETECT == STD_ON))
  uint8 ErrStatus;
  #endif
  uint8 PwmCoreChIdx;
  uint32 CoreId;
  #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
  uint8 PwmTimerType;
  const Pwm_17_GtmCcu6_ChannelConfigType *PwmChannelCfgPtr;
  const Pwm_17_GtmCcu6_CoreConfigType *PwmCorePtr;
  #endif

  CoreId = Mcal_GetCpuIndex();
  /* [cover parentID={F1FAD98F-0B0E-4088-AAE4-8B69AF1F5928}]
  Is DET enabled [/cover] */
  #if ((PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON) || \
      (PWM_17_GTMCCU6_DEV_ERROR_DETECT == STD_ON))
  ErrStatus = (uint8)E_OK;
  #endif

  #if ((PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON) || \
      (PWM_17_GTMCCU6_DEV_ERROR_DETECT == STD_ON))
  /* [cover parentID={F26E1B8A-4F42-42e1-AD79-FA861B38AE3A}]
  Varify init has been called and channel number is valid [/cover] */
  /* [cover parentID={CC10BCB7-D46B-458d-9BF9-65C5B8FBA9C1}]
  Any error reported [/cover] */
  if ( PWM_ERROR_FOUND == Pwm_lVerUnInitAndChannel\
       (PWM_17_GTMCCU6_SID_DISABLENOTIFI, ChannelNumber, (uint8)CoreId)
     )
  {
    /* Return without executing any of functionality */
    ErrStatus = (uint8)E_NOT_OK;
  }
  #endif

  #if ((PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON) || \
      (PWM_17_GTMCCU6_DEV_ERROR_DETECT == STD_ON))
  /* [cover parentID={607B1493-55B3-49e3-BDB3-2B4C3F8318C8}]
  If error status OK [/cover] */
  if(ErrStatus == (uint8)E_OK)
  #endif
  {
    PwmCoreChIdx = Pwm_ConfigPtr->PwmChannelIdxmapPtr[ChannelNumber];
    #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
    PwmCorePtr = Pwm_ConfigPtr->PwmCoreAdd[CoreId];
    PwmChannelCfgPtr = &(PwmCorePtr->Pwm_ChannelConfigPtr[PwmCoreChIdx]);
    PwmTimerType       = PwmChannelCfgPtr->PwmTimerUsed;
    #endif
    /* [cover parentID={975AA332-7F61-4a9e-A1B4-B0BD0A344BAC}]
    Enter critical section [/cover] */
    SchM_Enter_Pwm_17_GtmCcu6_HandleNotification();
    #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
    /*[cover parentID={2C88BE9B-9F20-4403-87A1-D0060925EF9B}]
    Disable notifications[/cover]*/
    /*[cover parentID={306B2B0A-A4F2-420c-987C-EA1F955CC710}]
    Disable notifications[/cover]*/
    if(PwmTimerType == PWM_17_GTMCCU6_GTM_TIMER)
    {
      Pwm_lGtmIrqModify(PwmCoreChIdx, 0U, (uint8)CoreId);
    }
    else
    #endif
    {
      #if (PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
      /* Disable Interrupts for each channel */
      Pwm_lCcu6IrqModify(PwmCoreChIdx, 0U, (uint8)CoreId);
      #endif
    }
    /* Disable Notification */
    Pwm_lClearNotificationStatus(PwmCoreChIdx, (uint8)CoreId);
    /* Reset notification edges */
    Pwm_lClearNotificationEdges(PwmCoreChIdx, (uint8)CoreId);
    /* [cover parentID={DC61196C-B718-4c08-B369-A16344782B1A}]
    Exit critical section [/cover] */
    SchM_Exit_Pwm_17_GtmCcu6_HandleNotification();
  }
}
/******************************************************************************
** Syntax : void Pwm_17_GtmCcu6_EnableNotification                           **
**                  (                                                        **
**                    const Pwm_17_GtmCcu6_ChannelType ChannelNumber,        **
**                    const Pwm_17_GtmCcu6_EdgeNotificationType Notification **
**                  )                                                        **
** Service ID: 0x07                                                          **
**                                                                           **
** Sync/Async: Synchronous                                                   **
**                                                                           **
** Reentrancy: Reentrant for different channels                              **
**                                                                           **
** Parameters (in):  ChannelNumber : Numeric identifier of the PWM channel   **
**                   Notification  : PWM_17_GTMCCU6_RISING_EDGE or           **
**                                   PWM_17_GTMCCU6_FALLING_EDGE or          **
**                                   PWM_17_GTMCCU6_BOTH_EDGES               **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:  none                                                       **
**                                                                           **
** Description : This service will enable the PWM signal notification        **
**               according to notification parameter.                        **
**                                                                           **
** Traceability :    [cover parentID={30EE6CE5-9811-4dfc-8AA2-CBF10931BED0}] **
**                   [/cover]                                                **
******************************************************************************/
/*CYCLOMATIC_Pwm_17_GtmCcu6_EnableNotification_JUSTIFICATION: This Function has
  cyclomatic complexity >15. Multiple conditions needed to verify DSADC 
  triggered PWM channel notification .Further breakdown cannot be done in order
  to maintain readability.*/
void Pwm_17_GtmCcu6_EnableNotification
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const Pwm_17_GtmCcu6_EdgeNotificationType Notification
)
{
  /* Local variables */
  #if ((PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON) || \
      (PWM_17_GTMCCU6_DEV_ERROR_DETECT == STD_ON))
  uint8                       ErrStatus;
  uint32                      ErrVal = 0;
  #endif
  Pwm_17_GtmCcu6_ChannelClassType ChannelKind;
  uint8 Polarity;
  Pwm_17_GtmCcu6_EdgeNotificationType NotifVal;
  /* ROM pointer */
  const Pwm_17_GtmCcu6_ChannelConfigType *LocalPwmChanPtr = NULL_PTR; 
  uint8                             PwmCoreChIdx = 0;
  uint32                            CoreId = 0;
  #if (PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON)
  Pwm_17_GtmCcu6_EdgeNotificationType Dsadc_NotifVal = 0;
  #endif
  
  CoreId = Mcal_GetCpuIndex();

  /* [cover parentID={049DC1F9-8F69-47f6-8159-B8C4BFB18600}]
  Is DET enabled OR Safety is Enabled [/cover] */
  #if ((PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON) ||\
      (PWM_17_GTMCCU6_DEV_ERROR_DETECT == STD_ON))

  ErrStatus = (uint8)E_OK;
  /* [cover parentID={A065A39D-F566-4844-B254-67CCD793E902}]
  Verify init had called and channel number [/cover] */
  ErrVal = Pwm_lVerUnInitAndChannel\
       ( PWM_17_GTMCCU6_SID_ENABLENOTIFI, ChannelNumber, (uint8)CoreId);
  /* [cover parentID={D6D3EA53-1992-4005-9FD1-BD3B079DFF15}]
  PWM_17_GTMCCU6_SAFETY_ENABLE [/cover] */
  /* [cover parentID={805EEE5D-EE05-40c2-A43B-BEAB1AE8E66A}]
  Is error reported by lVerUnInitAndChannel [/cover] */
  if(ErrVal != PWM_ERROR_FOUND)
  #endif
  {
    #if (PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON)
    /* API Pwm_17_GtmCcu6_EnableNotification services called with
    invalid notification type.*/
    /* [cover parentID={D8E7D648-C154-4f52-A295-1EC2F9290FFF}]
    Is the function invoked with wrong notification value? [/cover] */
    if((Notification > PWM_CONST_3) || (Notification < PWM_CONST_1))
    {
      /* [cover parentID={AEA70633-88F3-4a55-836E-63D57B683AE3}]
      Report safety error and set Error Flag [/cover] */
      Mcal_ReportSafetyError(
        PWM_17_GTMCCU6_MODULE_ID,
        PWM_17_GTMCCU6_INSTANCE_ID,
        PWM_17_GTMCCU6_SID_ENABLENOTIFI,
        PWM_17_GTMCCU6_E_PARAM_NOTIFICATION);
        
        /* Update error status */
        ErrStatus = (uint8)E_NOT_OK;
    }
    else
    #endif
    {
      PwmCoreChIdx = Pwm_ConfigPtr->PwmChannelIdxmapPtr[ChannelNumber];
      /* Initialize PWM configured channel ROM pointer */
      LocalPwmChanPtr = &(Pwm_ConfigPtr->PwmCoreAdd \
                          [CoreId]->Pwm_ChannelConfigPtr[PwmCoreChIdx]);
      #if (PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON)
      Dsadc_NotifVal = ((Pwm_17_GtmCcu6_EdgeNotificationType)\
      (((uint16)(LocalPwmChanPtr->PwmChannelInfo) >> PWM_DSADCNOTIF_POS)\
      & (PWM_DSADCNOTIF_MASK)));
      #endif

      #if((PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON) && \
      (PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON))  
      if((Dsadc_NotifVal == PWM_CONST_1) && (Notification != PWM_CONST_3))
      {
        /* API Pwm_17_GtmCcu6_EnableNotification services called with
        invalid notification edge for Dsadc routed interrupt.*/
        /* [cover parentID={80C32794-7E64-4f1c-9206-7E676475FC2F}]
        Report Safety error and Set Error Flag [/cover] */
        /* [cover parentID={8C423989-0DA2-41ea-9402-99DA19ABE0BE}]
        Is DSADC notif bit is ON and notification is not for both edges?
        [/cover] */
        Mcal_ReportSafetyError(
          PWM_17_GTMCCU6_MODULE_ID,
          PWM_17_GTMCCU6_INSTANCE_ID,
          PWM_17_GTMCCU6_SID_ENABLENOTIFI,
          PWM_17_GTMCCU6_E_INVALID_EDGE_NOTIF);
          
          /* Update error status */
          ErrStatus = (uint8)E_NOT_OK;
      }
      #endif
    }
  }
  #if ((PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON) ||\
      (PWM_17_GTMCCU6_DEV_ERROR_DETECT == STD_ON))
  else
  {
    ErrStatus = (uint8)E_NOT_OK;
  }
  /* [cover parentID={46188FD5-7DDA-4320-AE07-76D69E3F289C}]
  If error status is OK [/cover] */
  if(ErrStatus == (uint8)E_OK)
  #endif
  {
    #if (PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON)
    /* If a callback notification is configured as
    Null pointer, no callback shall be executed. */
    /* [cover parentID={5DBC8057-47D5-4249-B4C6-8336A9D45263}]
    If a callback notification is not configured as null pointer [/cover] */
    if(((LocalPwmChanPtr->PwmNotification) != NULL_PTR)|| \
    (Dsadc_NotifVal == PWM_CONST_1))
    #endif
    {
      Polarity = PWM_GET_POLARITY(LocalPwmChanPtr->PwmChannelInfo);
      ChannelKind = Pwm_lChanClass(LocalPwmChanPtr->PwmChannelInfo);
      NotifVal = Notification;
      /* [cover parentID={38A8008D-40E6-40d9-BA31-A8B069801082}]
      polarity is LOW [/cover] */
      if( Polarity == PWM_17_GTMCCU6_LOW )
      {
        /* [cover parentID={67A1C158-E093-45f0-BB71-D1A3F427FB32}]
        polarity is low [/cover] */
        if((Notification == PWM_17_GTMCCU6_RISING_EDGE) || \
            (Notification == PWM_17_GTMCCU6_FALLING_EDGE))
        {
          NotifVal =
           ((Pwm_17_GtmCcu6_EdgeNotificationType)(~Notification) & PWM_CONST_3);
        }
      }
      /* [cover parentID={9CEB4C20-12B2-4678-9D17-5541E980CB6A}]
      Enter critical section [/cover] */
      SchM_Enter_Pwm_17_GtmCcu6_HandleNotification();
      /* [cover parentID={F47109A3-8AA8-4b18-826E-9AD19640F2E9}]
      Set notification [/cover] */
      Pwm_lSetNotificationEdges(PwmCoreChIdx, NotifVal, (uint8)CoreId);
      /* Enable notification if Duty is not equal to 0% or 100% */
      Pwm_lEnableQmNotif(ChannelKind, PwmCoreChIdx, NotifVal, (uint8)CoreId);
      /* [cover parentID={AFDDCE8F-A27C-46de-81A1-F38B5ADC34B4}]
      Exit critical section [/cover] */
      SchM_Exit_Pwm_17_GtmCcu6_HandleNotification();
    }
    #if (PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON)
    else
    {
      /* [cover parentID={FCCDEA41-61B1-404f-A4CD-4D9880000785}]
      Report error : No notification function is configured in tresos
      [/cover] */
      /* For API Pwm_EnableNotification this error is reported when no
      notification function is configured in tresos.*/
      Mcal_ReportSafetyError(
        PWM_17_GTMCCU6_MODULE_ID,
        PWM_17_GTMCCU6_INSTANCE_ID,
        PWM_17_GTMCCU6_SID_ENABLENOTIFI,
        PWM_17_GTMCCU6_E_NO_NOTIF_CONFIGURED);
    }
    #endif
  }
}
#endif

#if (PWM_17_GTMCCU6_SET_OUTPUT_TO_IDLE_API == STD_ON)
/******************************************************************************
** Syntax : void Pwm_17_GtmCcu6_SetOutputToIdle                              **
**                    (                                                      **
**                      const Pwm_17_GtmCcu6_ChannelType ChannelNumber       **
**                    )                                                      **
** Service ID: 0x04                                                          **
**                                                                           **
** Sync/Async: Synchronous                                                   **
**                                                                           **
** Reentrancy: Reentrant for different channels                              **
**                                                                           **
** Parameters (in):  ChannelNumber : Numeric identifier of the PWM channel   **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:  none                                                       **
**                                                                           **
** Description : Service sets the PWM output to configured Idle state        **
**                                                                           **
** Traceability :[cover parentID={9F0045F9-EDAB-4cfc-809E-1D0C35154DBC}]     **
**                   [/cover]                                                **
******************************************************************************/
void Pwm_17_GtmCcu6_SetOutputToIdle(\
                                const Pwm_17_GtmCcu6_ChannelType ChannelNumber)
{
  /* Local variables */
  #if ((PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON) || \
      (PWM_17_GTMCCU6_DEV_ERROR_DETECT == STD_ON))
  uint8                               ErrStatus;
  #endif
  Pwm_17_GtmCcu6_OutputStateType      IdleState;
  uint32                              Period;
  uint32                              ScaledDuty;
  uint32                              Duty;
  uint8                               Polarity;
  uint32                              CoreId;
  uint8                               PwmCoreChIdx;
  #if (PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON)
  #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
  uint8                               PwmTimerType;
  #endif
  #endif
  /* Local pointers */
  const Pwm_17_GtmCcu6_ChannelConfigType  *LocalPwmChanPtr;
  Pwm_17_GtmCcu6_ChannelStatusType        *LocalChannelStatusPtr;
  Pwm_17_GtmCcu6_ChannelClassType         ChannelKind;

  CoreId = Mcal_GetCpuIndex();
  /* [cover parentID={E96B547C-A085-4646-AA41-0A325AFE88B4}]
  Is DET enabled / Safety Enable [/cover] */
  #if ((PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON) || \
      (PWM_17_GTMCCU6_DEV_ERROR_DETECT == STD_ON))
  ErrStatus = (uint8)E_OK;
  /* [cover parentID={02BDE3CB-B4B9-4d8c-9D17-74973FA5C662}]
  Check for UnInit and wrong channel [/cover] */
  /* [cover parentID={37FC1A06-BD0B-4ea4-BA66-D0EB8579E811}][/cover] */
  if ( PWM_ERROR_FOUND == Pwm_lVerUnInitAndChannel(\
                 PWM_17_GTMCCU6_SID_SETOP2IDLE, ChannelNumber, (uint8)CoreId))
  {
    /* return on any errors found */
    ErrStatus = (uint8)E_NOT_OK;
  }
  /* [cover parentID={7C074AAD-A6E3-4af5-8D4D-6042998D17C2}]
  If Error status is OK [/cover] */
  if(ErrStatus == (uint8)E_OK)
  #endif
  {
    PwmCoreChIdx = Pwm_ConfigPtr->PwmChannelIdxmapPtr[ChannelNumber];
    /* Initialize ROM pointer */
    LocalPwmChanPtr = &(Pwm_ConfigPtr->PwmCoreAdd\
                        [CoreId]->Pwm_ChannelConfigPtr[PwmCoreChIdx]);

    /* [cover parentID={DA88ECD2-8431-4dc6-9520-C3CCA2170D89}]
    Is notification for 0 or 100% duty enabled or variable period is used
    [/cover] */
    #if (PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON)
    #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
    PwmTimerType          = LocalPwmChanPtr->PwmTimerUsed;
    #endif
    #endif
    /* Store OCM value */
    IdleState = Pwm_lIdle(LocalPwmChanPtr->PwmChannelInfo);
    Period = LocalPwmChanPtr->PwmPeriodDefault;
    ChannelKind = Pwm_lChanClass(LocalPwmChanPtr->PwmChannelInfo);
    Polarity = PWM_GET_POLARITY(LocalPwmChanPtr->PwmChannelInfo);

    LocalChannelStatusPtr = Pwm_CoreChannelStatus[CoreId];
    LocalChannelStatusPtr = &(LocalChannelStatusPtr[PwmCoreChIdx]);
    /* [cover parentID={0F374A74-A87E-4e43-896F-7F380ABE6C4B}]
    Is variable period used [/cover] */
    if(ChannelKind == PWM_17_GTMCCU6_VARIABLE_PERIOD)
    {
      Period = LocalChannelStatusPtr->Pwm_CurrentPeriodVal;
    }

    /* Initialize  Duty as 100 % */
    /* [cover parentID={CF2FBC19-5C58-4ede-A756-3CBA36A309FF}]
    If duty shifts is in ticks [/cover] */
    #if (PWM_17_GTMCCU6_DUTY_SHIFT_IN_TICKS == STD_ON)
    Duty = Pwm_lMaxDuty(PwmCoreChIdx, (uint8)CoreId);
    /* [cover parentID={B0877E2C-2576-41fb-A4F2-6BD96BCE5463}]
    If duty shifts is not in ticks [/cover] */
    #else
    Duty = PWM_MAX_DUTY;
    #endif
    /* [cover parentID={5FCFDC5C-1AED-46ff-9255-9CFBD1079075}]
    If Idle state and polarity mismatches [/cover] */
    if (IdleState != Polarity)
    {
      /* Idle state and Polarity mismatches then 0 % duty desired */
      Duty = 0U;
    }
    /* Get Scale value of Duty according to period */
    ScaledDuty = Pwm_lGetAbsvalEdge(Period, (uint32) Duty);
    /* [cover parentID={8E3727AD-CB5E-4d10-BC91-C497038C85AA}]
    If notification supported [/cover] */
    #if (PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON)
    /* [cover parentID={F2CED345-2923-40c8-B6CA-27283A3CC825}]
    Enter critical section [/cover] */
    SchM_Enter_Pwm_17_GtmCcu6_HandleNotification();
    /* [cover parentID={1811952C-6E30-4453-ACCC-970C0542AD1E}]
    If notification enabled for 0 or 100% duty [/cover] */
    /* [cover parentID={D25C50A4-FC25-46ef-A63A-D6C1CEA97F67}][/cover] */

    #if (PWM_17_GTMCCU6_NOTIF_FOR_100_0_ENABLE == STD_ON)
    if ((ChannelKind == PWM_17_GTMCCU6_FIXED_PERIOD_SHIFTED) || \
        (ChannelKind == PWM_17_GTMCCU6_FIXED_PERIOD_CENTER_ALIGNED))
    {
      #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
      /* Clear the interrupt since duty is 0% or 100% based on Idle state */
      /* [cover parentID={7B52A8D5-A885-4151-B68F-A43BB399948F}]
      If timer used is GTM [/cover] */
      if(PwmTimerType == PWM_17_GTMCCU6_GTM_TIMER)
      {
        /* [cover parentID={FEB04144-1E02-4a70-8596-A3BA25D1F5F5}]
        Disable interrupts for GTM [/cover] */
        Pwm_lGtmIrqModify(PwmCoreChIdx, 0U, (uint8)CoreId);
      }
      else
      #endif
      {
        #if (PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
        /* [cover parentID={D788FCB1-4530-48b9-8ADC-0C94D80A7F1F}]
        Disable interrupts for CCU6 [/cover] */
        Pwm_lCcu6IrqModify(PwmCoreChIdx, 0U, (uint8)CoreId);
        #endif
      }
      /* Clear notification status in global register */
      /* [cover parentID={E88088F9-4A10-4596-B0C7-0F4C7FE3C60F}]
      Clear notification status in global register [/cover] */
      Pwm_lClearNotificationStatus(PwmCoreChIdx, (uint8)CoreId);
      /* Set the flag in global register to indicate the duty is 0% or 100%*/
      Pwm_lSetDuty_0_Or_100_Status(PwmCoreChIdx, (uint8)CoreId);
    }
    /* [cover parentID={2F0E85EC-2BEF-45fe-B6B9-03E9C4A4889C}]
    If notification is not enabled for 0 or 100% duty [/cover] */
    #else
    {
      /* Clear the interrupt since duty is 0% or 100% based on Idle state */
      /* [cover parentID={6B30A5EB-08C9-4a4f-8B8B-6D80DB0782FD}]
      If timer used is GTM [/cover] */
      #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
      if(PwmTimerType == PWM_17_GTMCCU6_GTM_TIMER)
      {
        /* [cover parentID={AE9C39CF-85D9-4379-809D-93322DF5383B}]
        Disable interrupts for GTM [/cover] */
        Pwm_lGtmIrqModify(PwmCoreChIdx, 0U, (uint8)CoreId);
      }
      else
      #endif
      {
        #if (PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
        /* [cover parentID={C7B4FB4E-0373-4587-AF43-5C45ABF519FD}]
        Disable interrupts for CCU6 [/cover] */
        Pwm_lCcu6IrqModify(PwmCoreChIdx, 0U, (uint8)CoreId);
        #endif
      }
      /* [cover parentID={EEBED1A6-1347-4ace-B14D-532E6A7A0472}]
      Clear notification status in global register [/cover] */
      Pwm_lClearNotificationStatus(PwmCoreChIdx, (uint8)CoreId);
      /* Set the flag in global register to indicate the duty is 0% or 100%*/
      Pwm_lSetDuty_0_Or_100_Status(PwmCoreChIdx, (uint8)CoreId);
    }
    #endif
    /* [cover parentID={F9C9E788-E13C-46a0-970D-69CD9FE0B6E7}]
    Exit critical section [/cover] */
    SchM_Exit_Pwm_17_GtmCcu6_HandleNotification();
    #endif
    /* Make output immediate to Idle state */
    /* 100% duty with Polarity and 0 % duty with opposite of polarity
      will make the output to given Idlestate */
    /* Set Duty value to 0% */
    /* [cover parentID={9682604A-5B02-42d6-B6E8-18646441A56B}]
    If timer used is GTM [/cover] */
    #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
    if(LocalPwmChanPtr->PwmTimerUsed == PWM_17_GTMCCU6_GTM_TIMER)
    {
      /* Set output to configured Idle state for GTM timers */
      Pwm_lGtmStartChannelIdle(PwmCoreChIdx, Period, ScaledDuty,\
                                                           (uint8)CoreId);
    }
    else
    #endif
    {
      #if(PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
      /* Set output to configured Idle state for CCU6 timers */
      Pwm_lCcu6StartChannelIdle (PwmCoreChIdx, ScaledDuty, (uint8)CoreId);
      #endif
    }
  }
  return;
}
#endif
#if (PWM_17_GTMCCU6_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Syntax :          void Pwm_17_GtmCcu6_GetVersionInfo                       **
**                            (                                               **
**                              Std_VersionInfoType *const VersionInfoPtr     **
**                            )                                               **
** Service ID:       0x8                                                      **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):                                                           **
**                                                                            **
** Parameters (out): versioninfo : Pointer to store the version information   **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
** Description :  . This service will return the version infos of PWM driver  **
**                                                                            **
** Traceability :[cover parentID={EB5A344D-EB50-445a-A784-34501DA9517C}]      **
**                   [/cover]                                                 **
*******************************************************************************/
void Pwm_17_GtmCcu6_GetVersionInfo(Std_VersionInfoType *const VersionInfoPtr)
{
  #if ((PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON) || \
      (PWM_17_GTMCCU6_DEV_ERROR_DETECT == STD_ON))
  uint8 ErrStatus = E_OK;
  /* [cover parentID={606D4000-73E0-428b-A69A-8DEDBD79E5AE}]
  Is DET enabled [/cover] */
  /* [cover parentID={A4E77F23-9982-4272-9AD0-D1B0B7A9B0ED}]
  If given version info parameter is a null pointer [/cover] */
  if (VersionInfoPtr == NULL_PTR)
  {
    /* [cover parentID={FCC354A7-1B2F-4f79-9E98-FE05BB52EC0B}]
    Report Error [/cover] */
    Pwm_lReportError(
                     PWM_17_GTMCCU6_SID_GETVERSIONINFO,
                     PWM_17_GTMCCU6_E_PARAM_POINTER
                    );
    ErrStatus = (uint8)E_NOT_OK;
  }
  /* [cover parentID={A210A6CB-6C0D-482d-AF10-8FD9B9FC9471}]
  If error status OK [/cover] */
  if(ErrStatus == (uint8)E_OK)
  #endif
  {
    /* [cover parentID={066177DB-AED8-4311-A5DC-917EAF7CA394}]
    Set vendor ID, module ID, software major version, software minor version
    and software patch version in given pointer [/cover] */
    /* Vendor ID information */
    ((Std_VersionInfoType*)(VersionInfoPtr))->vendorID = \
        PWM_17_GTMCCU6_VENDOR_ID;
    /* Pwm module ID information */
    ((Std_VersionInfoType*)(VersionInfoPtr))->moduleID = \
        PWM_17_GTMCCU6_MODULE_ID;
    /* Pwm module Software major version information */
    ((Std_VersionInfoType*)(VersionInfoPtr))->sw_major_version =
      (uint8)PWM_17_GTMCCU6_SW_MAJOR_VERSION;
    /* Pwm module Software minor version information */
    ((Std_VersionInfoType*)(VersionInfoPtr))->sw_minor_version =
      (uint8)PWM_17_GTMCCU6_SW_MINOR_VERSION;
    /* Pwm module Software patch version information */
    ((Std_VersionInfoType*)(VersionInfoPtr))->sw_patch_version =
      (uint8)PWM_17_GTMCCU6_SW_PATCH_VERSION;
  }
}
#endif
#if (PWM_17_GTMCCU6_GET_OUTPUT_STATE_API == STD_ON)
/******************************************************************************
** Syntax : Pwm_17_GtmCcu6_OutputStateType Pwm_17_GtmCcu6_GetOutputState     **
**                       (                                                   **
**                         const Pwm_17_GtmCcu6_ChannelType ChannelNumber    **
**                       )                                                   **
**                                                                           **
** Service ID:  0x05                                                         **
**                                                                           **
** Sync/Async:  Synchronous                                                  **
**                                                                           **
** Reentrancy:  Reentrant for different channels                             **
**                                                                           **
** Parameters (in):  ChannelNumber : Numeric identifier of the PWM channel   **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     Pwm_17_GtmCcu6_OutputStateType                          **
**                                                                           **
** Description : Service to read the PWM output state                        **
**               1.If development error detection is enabled and an error is **
**                 detected the service returns PWM_17_GTMCCU6_LOW.          **
**               2.Output state of a PWM channel. Note that this will be read**
**                 from the output state on the TOM/ATOM Channel connected   **
**                 to the port pin. This will not be read directly from the  **
**                 Port Pin. However both will be the same                   **
**                                                                           **
** Traceability      :[cover parentID={A334C009-7404-44ab-9406-5C772EBB1F15}]**
**                   [/cover]                                                **
******************************************************************************/
Pwm_17_GtmCcu6_OutputStateType Pwm_17_GtmCcu6_GetOutputState
(const Pwm_17_GtmCcu6_ChannelType ChannelNumber)
{
  /* Service to get the Output State */
  #if ((PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON) || \
      (PWM_17_GTMCCU6_DEV_ERROR_DETECT == STD_ON))
  uint8                       ErrStatus;
  #endif
  uint32 CoreId;
  uint8  PwmCoreChIdx;
  Pwm_17_GtmCcu6_OutputStateType ReturnState;
  /* [cover parentID={A906C3F6-25F9-487c-998F-3B4B4BB06DCE}]
  Is DET OR Safety enabled [/cover] */
  #if ((PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON) || \
      (PWM_17_GTMCCU6_DEV_ERROR_DETECT == STD_ON))
  /* [cover parentID={B3A3FC0E-967D-49d6-8B27-AAD74DA3EC10}]
  Set output state to LOW and error status OK [/cover] */
  ReturnState = (Pwm_17_GtmCcu6_OutputStateType)STD_LOW;
  ErrStatus = (uint8)E_OK;
  #endif
  CoreId = Mcal_GetCpuIndex();
  #if ((PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON) || \
      (PWM_17_GTMCCU6_DEV_ERROR_DETECT == STD_ON))
  /* [cover parentID={A20F3113-FD97-48a0-9B8C-0E788C91AA2A}]
  Check for UnInit and wronf channel number [/cover] */
  /* [cover parentID={B2973219-8661-4ce6-BE14-3168222BC8AA}]
  If any error reported [/cover] */
  if ( PWM_ERROR_FOUND == Pwm_lVerUnInitAndChannel\
       (PWM_17_GTMCCU6_SID_GETOPSTATE, ChannelNumber, (uint8)CoreId)
     )
  {
    ErrStatus = (uint8)E_NOT_OK;
  }
  /* [cover parentID={214D2BF6-A781-44db-8AF2-931AA0D5A9C3}]
  If error status is OK [/cover] */
  if(ErrStatus == (uint8)E_OK)
  #endif
  {
    PwmCoreChIdx = Pwm_ConfigPtr->PwmChannelIdxmapPtr[ChannelNumber];
    ReturnState = Pwm_lGetOutputState(PwmCoreChIdx,(uint8)CoreId);
  }
  /* [cover parentID={D7DE79AF-5EAE-494d-9378-7BC6C22E6493}]
  Return output state [/cover] */
  return (ReturnState);
}
#endif

/******************************************************************************
**                      Private Function Definitions                         **
******************************************************************************/
#if ((PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON) || \
    (PWM_17_GTMCCU6_DEV_ERROR_DETECT == STD_ON))
/******************************************************************************
** Syntax : static uint8 Pwm_lInitDetCheck                                   **
**                            (                                              **
**                             const Pwm_17_GtmCcu6_ConfigType *DetConfigPtr,**
**                             const uint32 CoreId                           **
**                            )                                              **
** Service ID:        none                                                   **
**                                                                           **
** Sync/Async:        Synchronous                                            **
**                                                                           **
** Reentrancy:        Non Reentrant                                          **
**                                                                           **
** Parameters (in):   DetConfigPtr - Pointer to configuration set            **
**                    CoreId : Core Number                                   **
**                                                                           **
** Parameters (out):  none                                                   **
**                                                                           **
** Return value:      Error Status                                           **
**                                                                           **
** Description :      Service for DET check of PWM initialization function   **
**                                                                           **
** Traceability:     [cover parentID={E7A2CB7A-8C23-4c49-91F1-B979ACDA34BF}] **
**                     [/cover]                                              **
******************************************************************************/
static uint8 Pwm_lInitDetCheck( const Pwm_17_GtmCcu6_ConfigType *DetConfigPtr, 
                                const uint32 CoreId)
{
  uint8 ErrStatus;
  const Pwm_17_GtmCcu6_CoreStatusType *LocalCoreStatusPtr;
  #if ((PWM_17_GTMCCU6_MULTICORE_ERROR_DETECT == STD_ON)||\
      (PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON))
  const Pwm_17_GtmCcu6_CoreConfigType *PwmCorePtr;
  #endif

  ErrStatus = E_OK;

  /* [cover parentID={8233EF84-E0F0-4944-976F-6EA042BA6A86}]
  Check validity of configPtr [/cover] */
  if (NULL_PTR == DetConfigPtr )
  {
    /* [cover parentID={F46A6F7E-E2BF-4987-85DD-8E1CDD9FBB55}]
    Report to DET upon error, Init has been called with wrong
    parameter i.e. NULL Config Pointer [/cover] */
    Pwm_lReportError(PWM_17_GTMCCU6_SID_INIT, PWM_17_GTMCCU6_E_INIT_FAILED);
    ErrStatus = (uint8)E_NOT_OK;
  }
  /* [cover parentID={78CC6302-FC8C-4329-8459-EDB8A839C629}]
  If Error status is Ok [/cover] */
  if (ErrStatus == E_OK)
  {
    #if ((PWM_17_GTMCCU6_MULTICORE_ERROR_DETECT == STD_ON)||\
         (PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON))
    PwmCorePtr = DetConfigPtr->PwmCoreAdd[CoreId];
    /* [cover parentID={9A419028-92C0-4133-98F2-56166744EC75}]
    If core address is not configured [/cover] */
    if(PwmCorePtr == NULL_PTR)
    {
      /* [cover parentID={DC81B47A-F8A9-4378-9D44-01C0B23AA4CD}]
      Report DET PWM module not configured for this Core [/cover] */
      Pwm_lReportMulticoreError(PWM_17_GTMCCU6_SID_INIT,\
                                     PWM_17_GTMCCU6_E_CORE_NOT_CONFIGURED);
      ErrStatus = (uint8)E_NOT_OK;
    }
    else
    #endif
    {
      /* [cover parentID={1A923424-AB1A-45d7-BA68-D9D80AA63AD5}]
      If core is initialized [/cover] */
      LocalCoreStatusPtr = PwmCoreStatusPtr[CoreId];
      if(PWM_INITIALIZED == LocalCoreStatusPtr->Pwm_CoreInitStatus)
      {
        /* [cover parentID={32C09859-98F1-4986-9873-C9BE83AF3550}]
        Report error [/cover] */
        Pwm_lReportError(PWM_17_GTMCCU6_SID_INIT,\
                                         PWM_17_GTMCCU6_E_ALREADY_INITIALIZED);
        ErrStatus = (uint8)E_NOT_OK;
      }
    }
  }
  return (ErrStatus);
}
#endif
/******************************************************************************
** Syntax : static void Pwm_lInitFixedPeriod                                 **
**                   (                                                       **
**                     const Pwm_17_GtmCcu6_ChannelType ChannelNumber,       **
**                     const uint8 CoreId)                                   **
**                   )                                                       **
** Service ID:        none                                                   **
**                                                                           **
** Sync/Async:        Synchronous                                            **
**                                                                           **
** Reentrancy:        Non reentrant                                          **
**                                                                           **
** Parameters (in):   ChannelNumber : PWM Channel number                     **
**                    CoreId : Core Number                                   **
**                                                                           **
** Parameters (out):  none                                                   **
**                                                                           **
** Return value:      none                                                   **
**                                                                           **
** Description :      Service to initialize fixed period channel             **
**                                                                           **
** Traceability:      [cover parentID={661CA4C5-A7B1-4256-955E-1B0E501AA2BD}]**
**                      [/cover]                                             **
******************************************************************************/
static void Pwm_lInitFixedPeriod
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
)
{
  #if (PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON)
  #if (PWM_17_GTMCCU6_NOTIF_FOR_100_0_ENABLE == STD_OFF)
  uint32 Period;
  uint32 Duty;
  #endif
  #endif

  #if ((PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON) || \
       ((PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON) && \
       (PWM_17_GTMCCU6_NOTIF_FOR_100_0_ENABLE == STD_OFF)))
  const Pwm_17_GtmCcu6_ChannelConfigType *LocalPwmChanPtr;

  LocalPwmChanPtr = (const Pwm_17_GtmCcu6_ChannelConfigType*)&\
      (Pwm_ConfigPtr->PwmCoreAdd[CoreId]->Pwm_ChannelConfigPtr[ChannelNumber]);
  #endif

  /* Initialize PWM configured channel */
  /* [cover parentID={264974BA-A1F7-4ea8-AB48-FA7E84A73D08}]
  Is notification support enabled [/cover] */
  #if (PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON)
  /* [cover parentID={35FB022A-9D0C-4b92-BC58-BBDEC45C02DE}]
  Is Notification for 0% or 100% enabled [/cover] */
  #if (PWM_17_GTMCCU6_NOTIF_FOR_100_0_ENABLE == STD_OFF)
  Period = LocalPwmChanPtr->PwmPeriodDefault;
  Duty = LocalPwmChanPtr->PwmDutycycleDefault;
  /* [cover parentID={70B0B45D-3F60-4742-9DCA-6EFBF699CF20}]
  Is duty is 0% or 100% [/cover] */
  if ((Duty == 0U) || ( Duty == Period))
  {
    /* [cover parentID={01763D22-61FC-4b9c-A084-1B93A15919D9}]
    Set the flag in global register to indicate the duty is 0% or 100%
    [/cover] */
    Pwm_lSetDuty_0_Or_100_Status(ChannelNumber, CoreId);
  }
  #endif
  #endif
  #if (PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
  /* [cover parentID={EC8F9BD4-B774-4457-84DA-BFF08B03992F}]
  If timer used is GTM [/cover] */
  if(LocalPwmChanPtr->PwmTimerUsed == PWM_17_GTMCCU6_GTM_TIMER)
  {
    /* [cover parentID={63F4F84B-FD0A-4801-AC88-7D08E8419657}]
    Initialize GTM timer [/cover] */
    Pwm_lGtmStartChannelsInit(ChannelNumber, CoreId);
  }
  else
  #endif
  /* [cover parentID={EC8F9BD4-B774-4457-84DA-BFF08B03992F}]
  If timer used is CCU6 [/cover] */
  {
    #if (PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
    /* [cover parentID={8BED1278-ADB5-4b84-8E02-4E29735BFF34}]
    Initialize CCU6 timer [/cover] */
    Pwm_lCcu6StartChannelsInit(ChannelNumber, CoreId);
    #endif
  }
}
#if (PWM_17_GTMCCU6_INITCHECK_API == STD_ON)
/******************************************************************************
** Syntax : static Std_ReturnType Pwm_lInitFixedPeriodCheck                  **
**                    (                                                      **
**                      const Pwm_17_GtmCcu6_ChannelType ChannelNumber,      **
**                      const uint8 CoreId                                   **
**                    )                                                      **
** Service ID:        none                                                   **
**                                                                           **
** Sync/Async:        Synchronous                                            **
**                                                                           **
** Reentrancy:        Non Reentrant                                          **
**                                                                           **
** Parameters (in):   ChannelNumber : PWM Channel number                     **
**                    CoreId : Core Number                                   **
**                                                                           **
** Parameters (out):  none                                                   **
**                                                                           **
** Return value:      Std_ReturnType                                         **
**                                                                           **
** Description :      :Service to verify initialization of fixed period      **
**                     channel                                               **
**                                                                           **
** Traceability:      [cover parentID={D64C2627-6E5F-4d3b-8889-3E7D3F20D981}]**
**                      [/cover]                                             **
******************************************************************************/
static Std_ReturnType Pwm_lInitFixedPeriodCheck
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
)
{
  /* [cover parentID={D99D75D2-BD49-4aa3-AEDB-A10D6AC11CAF}]
  Set error status to E_OK [/cover] */
  Std_ReturnType ErrorStatus = E_OK;
  #if ((PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON) &&\
       (PWM_17_GTMCCU6_NOTIF_FOR_100_0_ENABLE == STD_OFF))
  uint32 Period;
  uint32 Duty;
  const Pwm_17_GtmCcu6_ChannelStatusType *LocalChannelStatusPtr;
  #endif

  const Pwm_17_GtmCcu6_ChannelConfigType *LocalPwmChanPtr;

  LocalPwmChanPtr = (const Pwm_17_GtmCcu6_ChannelConfigType*)&\
      (Pwm_ConfigPtr->PwmCoreAdd[CoreId]->Pwm_ChannelConfigPtr[ChannelNumber]);

  /* Verify PWM configured channels */
  #if ((PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON) &&\
       (PWM_17_GTMCCU6_NOTIF_FOR_100_0_ENABLE == STD_OFF))
  Period = LocalPwmChanPtr->PwmPeriodDefault;
  Duty = LocalPwmChanPtr->PwmDutycycleDefault;
  LocalChannelStatusPtr = Pwm_CoreChannelStatus[CoreId];
  /* [cover parentID={680D0779-096F-43f2-B738-D288BA440A94}]
  If duty is 0% or 100% [/cover] */
  if ((Duty == 0U) || ( Duty == Period))
  {
    /* [cover parentID={D32B0E22-E771-4c09-B9AE-A542D80DAA5F}]
    Verify the duty set status for 0% or 100% [/cover] */
    ErrorStatus = Pwm_lSetDuty_0_Or_100_StatusCheck(ChannelNumber, CoreId);
  }
  else
  {
    /* [cover parentID={8A099A62-A030-4c21-AD79-BA5C50C3AC16}]
    If notifications are not enabled for the channel [/cover] */
    if(LocalChannelStatusPtr[ChannelNumber].Pwm_GlobChn != 0U)
    {
      /* [cover parentID={7C910AEA-5092-4d94-B10B-76197BCCC5D9}]
      Set error status to NOT OK [/cover] */
      ErrorStatus = E_NOT_OK;
    }
  }
  /* [cover parentID={4500DE1E-B58E-46da-9093-87323C62D8A3}]
  Is error status E_OK [/cover] */
  if (ErrorStatus == E_OK)
  #endif
  {
    /* [cover parentID={C60006CB-71DB-42e8-AD3D-199E030577B3}]
    If used timer is GTM [/cover] */
    #if (PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
    if(LocalPwmChanPtr->PwmTimerUsed == PWM_17_GTMCCU6_GTM_TIMER)
    {
      /* [cover parentID={3571B2FE-4D88-47a0-B6B2-20188704E12F}]
      Check GTM channels init status [/cover] */
      ErrorStatus = Pwm_lGtmStartChannelsInitCheck(ChannelNumber, CoreId);
    }
    else
    #endif
    {
      /* [cover parentID={C60006CB-71DB-42e8-AD3D-199E030577B3}]
      If used timer is CCU6 [/cover] */
      #if (PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
      if(LocalPwmChanPtr->PwmTimerUsed == PWM_17_GTMCCU6_CCU6_TIMER)
      {
        /* [cover parentID={E9776A01-E0AA-4422-B04B-B7B201685495}]
        Check CCU6 channels init status [/cover] */
        ErrorStatus = Pwm_lCcu6StartChannelsInitCheck(ChannelNumber, CoreId);
      }
      #endif
    }
  }
  /* [cover parentID={0D92F403-F1FD-49b9-814D-067C5E0AE67A}]
  Return error status [/cover] */
  return ErrorStatus;
}
#endif
/******************************************************************************
** Syntax : static void Pwm_lInitVariablePeriod                              **
**                     (                                                     **
**                       const Pwm_17_GtmCcu6_ChannelType ChannelNumber,     **
**                       const uint8 CoreId                                  **
**                     )                                                     **
** Service ID:        none                                                   **
**                                                                           **
** Sync/Async:        Synchronous                                            **
**                                                                           **
** Reentrancy:        Non Reentrant                                          **
**                                                                           **
** Parameters (in):   ChannelNumber : PWM Channel number                     **
**                    CoreId : Core Number                                   **
**                                                                           **
** Parameters (out):  none                                                   **
**                                                                           **
** Return value:      none                                                   **
**                                                                           **
** Description :      Service to initialize variable period channel          **
**                                                                           **
** Traceability:   [cover parentID={6E16B4F8-07D8-4e08-A171-CE442ECD2AE1}]   **
**                  [/cover]                                                 **
******************************************************************************/
static void Pwm_lInitVariablePeriod
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
)
{
  const Pwm_17_GtmCcu6_ChannelConfigType *LocalPwmChanPtr;
  Pwm_17_GtmCcu6_ChannelStatusType *LocalChannelStatusPtr;

  uint32 Period;
  #if (PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON)
  #if (PWM_17_GTMCCU6_NOTIF_FOR_100_0_ENABLE == STD_OFF)
  uint32 Duty;
  #endif
  #endif

  /* Initialize PWM configured channel ROM pointer */
  LocalPwmChanPtr = (const Pwm_17_GtmCcu6_ChannelConfigType*)&\
      (Pwm_ConfigPtr->PwmCoreAdd[CoreId]->Pwm_ChannelConfigPtr[ChannelNumber]);
  Period = LocalPwmChanPtr->PwmPeriodDefault;
  LocalChannelStatusPtr = Pwm_CoreChannelStatus[CoreId];
  LocalChannelStatusPtr[ChannelNumber].Pwm_CurrentPeriodVal = Period;

  /* [cover parentID={782A1996-62A2-4eb3-A600-B5647D65BA5C}]
  Is notification support enabled [/cover] */
  #if (PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON)
  /* [cover parentID={80C6A192-B0CE-4a2e-BD98-3970D833117A}]
  Is notification for 0% and 100% duty enabled [/cover] */
  #if (PWM_17_GTMCCU6_NOTIF_FOR_100_0_ENABLE == STD_OFF)
  Duty = (uint32)LocalPwmChanPtr->PwmDutycycleDefault;
  /* [cover parentID={78E6C759-473A-4284-858A-46ED6040938E}]
  If duty is 0% or 100% [/cover] */
  if ((Duty == 0U) || (Duty == Period))
  {
    /* [cover parentID={866007CA-2308-4094-AFD9-010EB90088EE}] Set the flag
    in global register to indicate the duty is 0% or 100% [/cover] */
    Pwm_lSetDuty_0_Or_100_Status(ChannelNumber, CoreId);
  }
  #endif
  #endif
  #if (PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
  /* [cover parentID={768F1D47-01AA-4d2e-9894-2947A87BD6F7}]
  If timer used is GTM [/cover] */
  if(LocalPwmChanPtr->PwmTimerUsed == PWM_17_GTMCCU6_GTM_TIMER)
  {
    /* [cover parentID={33C67C7F-DCFD-4f7a-BF90-AFF576ACFD06}]
    Initialize GTM timer [/cover] */
    Pwm_lGtmStartChannelsInit(ChannelNumber, CoreId);
  }
  else
  #endif
  /* [cover parentID={768F1D47-01AA-4d2e-9894-2947A87BD6F7}]
  If timer used is CCU6 [/cover] */
  {
    #if (PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
    /* [cover parentID={5984D6C1-196E-4ae0-97B5-14218DD4AA3C}]
    Initialize CCU6 timer [/cover] */
    Pwm_lCcu6StartChannelsInit(ChannelNumber, CoreId);
    #endif
  }
}
#if (PWM_17_GTMCCU6_INITCHECK_API == STD_ON)
/******************************************************************************
** Syntax : static Std_ReturnType Pwm_lInitVariablePeriodCheck               **
**                    (                                                      **
**                      const Pwm_17_GtmCcu6_ChannelType ChannelNumber,      **
**                      const uint8 CoreId                                   **
**                    )                                                      **
**                                                                           **
** Service ID:        none                                                   **
**                                                                           **
** Sync/Async:        Synchronous                                            **
**                                                                           **
** Reentrancy:        Non Reentrant                                          **
**                                                                           **
** Parameters (in):   ChannelNumber : PWM Channel number                     **
**                    CoreId : Core Number                                   **
**                                                                           **
** Parameters (out):  none                                                   **
**                                                                           **
** Return value:      Std_ReturnType                                         **
**                                                                           **
** Description :      Service to verify the initialization of variable period**
**                    channel                                                **
** Traceability:   [cover parentID={DC3193AF-4AA9-4ce2-9403-B5464CEED08F}]   **
**                  [/cover]                                                 **
******************************************************************************/
static Std_ReturnType Pwm_lInitVariablePeriodCheck
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
)
{
  const Pwm_17_GtmCcu6_ChannelConfigType *LocalPwmChanPtr;
  const Pwm_17_GtmCcu6_ChannelStatusType *LocalChannelStatusPtr;
  Std_ReturnType ErrorStatus = E_OK;
  uint32 Period;
  #if (PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON)
  #if (PWM_17_GTMCCU6_NOTIF_FOR_100_0_ENABLE == STD_OFF)
  uint32 Duty;
  #endif
  #endif

  /* Verify the initialization of configured channel */
  LocalPwmChanPtr = (const Pwm_17_GtmCcu6_ChannelConfigType*)&\
     (Pwm_ConfigPtr->PwmCoreAdd[CoreId]->Pwm_ChannelConfigPtr[ChannelNumber]);
  Period = LocalPwmChanPtr->PwmPeriodDefault;
  LocalChannelStatusPtr = Pwm_CoreChannelStatus[CoreId];

  /* [cover parentID={48EC97C1-9C3C-4772-A111-D5ABDD6A7ED7}][/cover] */
  if(LocalChannelStatusPtr[ChannelNumber].Pwm_CurrentPeriodVal != Period)
  {
    /* [cover parentID={1F7A49E5-513F-47b9-8018-200B24ECF400}]
    Set error status to E_NOT_OK [/cover] */
    ErrorStatus = E_NOT_OK;
  }

  /* [cover parentID={F33E3B37-4A9E-47ea-97C8-4402DC96D658}] If notification
  enabled and notification for 0% or 100% duty enabled [/cover] */
  #if (PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON)
  #if (PWM_17_GTMCCU6_NOTIF_FOR_100_0_ENABLE == STD_OFF)
  /* [cover parentID={A3AAF655-F5C7-4256-B2CD-4A6D7361BB7D}]
  Is error status E_OK [/cover] */
  if(ErrorStatus == E_OK)
  {
    Duty = (uint32)LocalPwmChanPtr->PwmDutycycleDefault;
    /* [cover parentID={67941B5E-05AE-4e12-A4D6-2A1A0DF4C683}][/cover] */
    /* If duty is 0% or 100% */
    if((Duty == 0U) || (Duty == Period))
    {
      /* [cover parentID={E092DCF8-B8E8-4d26-A262-2455655F27D1}]
      Verify the duty set status for 0% or 100% [/cover] */
      ErrorStatus = Pwm_lSetDuty_0_Or_100_StatusCheck(ChannelNumber, CoreId);
    }
    /* [cover parentID={8717970A-6482-4be5-9D72-EE0A937221A9}]
    If notifications are not enabled for the channel [/cover] */
    else if(LocalChannelStatusPtr[ChannelNumber].Pwm_GlobChn != 0U)
    {
      /* [cover parentID={0152AD95-5EC6-4c85-A195-DD9B1B84F8BA}]
      Set error status to E_NOT_OK  [/cover] */
      ErrorStatus = E_NOT_OK;
    }
    else
    {
      /* Do nothing*/
    }
  }
  #endif
  #endif
  /* [cover parentID={F6B3F6AB-7A8E-49db-B1F1-12623E02E8D5}]
  Is error status E_OK [/cover] */
  if (ErrorStatus == E_OK)
  {
    /* [cover parentID={6D05A09A-74BB-432c-945A-FE1412E066EC}]
    Is GTM timer used [/cover] */
    #if (PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
    /* [cover parentID={6B66468F-B918-41c3-85FF-C59FB85A7760}]
    Is GTM timer used [/cover] */
    if(LocalPwmChanPtr->PwmTimerUsed == PWM_17_GTMCCU6_GTM_TIMER)
    {
      /* [cover parentID={C583D6BF-9C98-479e-A0B2-8EC99C67276B}]
      Check GTM channels init status [/cover] */
      ErrorStatus = Pwm_lGtmStartChannelsInitCheck(ChannelNumber, CoreId);
    }
    else
    #endif
    /* [cover parentID={0AD9D0EE-80B6-4f48-8E47-5A06DA50AF3A}]
    Is CCU6 timer used [/cover] */
    {
      #if (PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
      /* [cover parentID={9ED9A08D-C135-4cb4-AEED-8A653CC4ED00}]
      Check CCU6 channels init status [/cover] */
      ErrorStatus = Pwm_lCcu6StartChannelsInitCheck(ChannelNumber, CoreId);
      #endif
    }
  }
  /* [cover parentID={CFE54011-1144-4e67-9C53-F7713F0DEDEC}]
  Return error status [/cover] */
  return ErrorStatus;
}
#endif
/******************************************************************************
** Syntax : static void Pwm_lInitShiftedCentreAligned                        **
**                    (                                                      **
**                      const uint32 ChannelNumber,                          **
**                      const uint8 CoreId                                   **
**                    )                                                      **
** Service ID:        none                                                   **
**                                                                           **
** Sync/Async:        Synchronous                                            **
**                                                                           **
** Reentrancy:        Non Reentrant                                          **
**                                                                           **
** Parameters (in):   ChannelNumber : PWM Channel number                     **
**                    CoreId : Core Number                                   **
**                                                                           **
** Parameters (out):  none                                                   **
**                                                                           **
** Return value:      none                                                   **
**                                                                           **
** Description :      Service to initialize shifted & centre aligned channel **
**                                                                           **
** Traceability:   [cover parentID={A03F565B-08CB-4d94-A4C6-2F7155EC329F}]   **
**                 [/cover]                                                  **
******************************************************************************/
static void Pwm_lInitShiftedCentreAligned
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
)
{
  #if(PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON)
  uint32 Period;
  uint32 Duty;
  #endif

  #if ((PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON) || \
       (PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON))
  const Pwm_17_GtmCcu6_ChannelConfigType *LocalPwmChanPtr;

  LocalPwmChanPtr = (const Pwm_17_GtmCcu6_ChannelConfigType*)&\
      (Pwm_ConfigPtr->PwmCoreAdd[CoreId]->Pwm_ChannelConfigPtr[ChannelNumber]);
  #endif

  #if(PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON)
  Period = LocalPwmChanPtr->PwmPeriodDefault;
  Duty = (uint32)LocalPwmChanPtr->PwmDutycycleDefault;
  /* [cover parentID={3AB5F354-C954-416d-BE54-8C98A9FBCFA2}]
  If duty is 0% or 100% [/cover] */
  if ((Duty == 0U) || ( Duty == Period))
  {
    /* [cover parentID={828CE104-30B8-4591-BBD9-B83A6B808181}]
    Set flag in global register to indicate the duty is 0% or 100% [/cover] */
    Pwm_lSetDuty_0_Or_100_Status(ChannelNumber, CoreId);
  }
  #endif
  #if (PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
  /* [cover parentID={695FB1B5-5DF1-48e1-A526-F06AAF20D6C5}]
  If timer used is GTM [/cover] */
  if(LocalPwmChanPtr->PwmTimerUsed == PWM_17_GTMCCU6_GTM_TIMER)
  {
    /* [cover parentID={E1687E1B-E795-4484-82CA-F9DA8B87E576}]
    Initialize GTM timer [/cover] */
    Pwm_lGtmStartChannelsInit(ChannelNumber, CoreId);
  }
  else
  #endif
  /* [cover parentID={695FB1B5-5DF1-48e1-A526-F06AAF20D6C5}]
  If timer used is CCU6 [/cover] */
  {
    #if (PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
    /* [cover parentID={24A8892C-689F-4b0b-91C8-ACA8969D4831}]
    Initialize CCU6 timer [/cover] */
    Pwm_lCcu6StartChannelsInit(ChannelNumber, CoreId);
    #endif
  }
}
#if (PWM_17_GTMCCU6_INITCHECK_API == STD_ON)
/******************************************************************************
** Syntax : static Std_ReturnType Pwm_lInitShiftedCentreAlignedCheck         **
**                    (                                                      **
**                      const uint32 ChannelNumber,                          **
**                      const uint8 CoreId                                   **
**                    )                                                      **
** Service ID:        none                                                   **
**                                                                           **
** Sync/Async:        Synchronous                                            **
**                                                                           **
** Reentrancy:        Non Reentrant                                          **
**                                                                           **
** Parameters (in):   ChannelNumber : PWM Channel number                     **
**                    CoreId : Core Number                                   **
**                                                                           **
** Parameters (out):  none                                                   **
**                                                                           **
** Return value:      Std_ReturnType                                         **
**                                                                           **
** Description :      Service to verify the initialization of shifted and    **
**                    centre aligned channel                                 **
** Traceability:      [cover parentID={4B393B55-EBEA-4d43-85A8-9B965DA70BF9}]**
**                    [/cover]                                               **
******************************************************************************/
static Std_ReturnType Pwm_lInitShiftedCentreAlignedCheck
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
)
{
  /* [cover parentID={1220692F-1A78-4b37-B13F-D3A0CC66E39F}]
  Set error status to E_OK [/cover] */
  Std_ReturnType ErrorStatus = E_OK;
  #if(PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON)
  uint32 Period;
  uint32 Duty;
  const Pwm_17_GtmCcu6_ChannelStatusType *LocalChannelStatusPtr;
  #endif
  const Pwm_17_GtmCcu6_ChannelConfigType *LocalPwmChanPtr;

  LocalPwmChanPtr = (const Pwm_17_GtmCcu6_ChannelConfigType*)&\
      (Pwm_ConfigPtr->PwmCoreAdd[CoreId]->Pwm_ChannelConfigPtr[ChannelNumber]);

  #if(PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON)
  Period = LocalPwmChanPtr->PwmPeriodDefault;
  Duty = (uint32)LocalPwmChanPtr->PwmDutycycleDefault;
  LocalChannelStatusPtr = Pwm_CoreChannelStatus[CoreId];
  /* [cover parentID={1F97C97F-E968-45e1-86E8-B80204F55445}]
  If duty is 0% or 100% [/cover] */
  if ((Duty == 0U) || ( Duty == Period))
  {
    /* [cover parentID={C9CE75F8-808F-4e27-9673-A9D5F6C820B0}]
    Verify the duty set status for 0% or 100% [/cover] */
    ErrorStatus = Pwm_lSetDuty_0_Or_100_StatusCheck(ChannelNumber, CoreId);
  }
  else
  {
    /* [cover parentID={972BA0AA-0BB6-43e6-98C2-0266F8EBAEE5}]
    If notifications are not enabled for the channel [/cover] */
    if(LocalChannelStatusPtr[ChannelNumber].Pwm_GlobChn != 0U)
    {
      /* [cover parentID={A671E05A-51BD-4ede-BA85-197DF2F914C4}]
      Set error status to NOT OK [/cover] */
      ErrorStatus = E_NOT_OK;
    }
  }
  /* [cover parentID={A9B495DF-1FF7-4dce-A3B4-DFE0C0C47035}]
  Is error status E_OK [/cover] */
  if (ErrorStatus == E_OK)
  #endif
  {
    #if (PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
    /* [cover parentID={E84D2717-7EEE-4b66-8679-CE8DC3211F41}]
    If used timer is GTM [/cover] */
    if(LocalPwmChanPtr->PwmTimerUsed == PWM_17_GTMCCU6_GTM_TIMER)
    {
      /* [cover parentID={DE1D1E71-80B0-4d52-9FD5-693D72C5EB24}]
      Check GTM channels init status [/cover] */
      ErrorStatus = Pwm_lGtmStartChannelsInitCheck(ChannelNumber, CoreId);
    }
    else
    #endif
    {
      /* [cover parentID={E84D2717-7EEE-4b66-8679-CE8DC3211F41}]
      If used timer is CCU6 [/cover] */
      #if (PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
      if(LocalPwmChanPtr->PwmTimerUsed == PWM_17_GTMCCU6_CCU6_TIMER)
      {
        /* [cover parentID={013A3FCB-3164-452f-BD7F-59C32B7EB2A9}]
        Check CCU6 channels init status [/cover] */
        ErrorStatus = Pwm_lCcu6StartChannelsInitCheck(ChannelNumber, CoreId);
      }
      #endif
    }
  }
  /* [cover parentID={A666CC4F-79AD-4a04-805D-B22674A734CC}]
  Return error status [/cover] */
  return ErrorStatus;
}
#endif

/******************************************************************************
** Syntax :    LOCAL_INLINE Pwm_17_GtmCcu6_ChannelClassType Pwm_lChanClass   **
**                    (                                                      **
**                      const uint16 Value                                   **
**                    )                                                      **
** Service ID:        none                                                   **
**                                                                           **
** Sync/Async:        Synchronous                                            **
**                                                                           **
** Reentrancy:        Reentrant                                              **
**                                                                           **
** Parameters (in):   Value : PwmChannelInfo                                 **
**                                                                           **
** Parameters (out):  none                                                   **
**                                                                           **
** Return value:      Pwm_17_GtmCcu6_ChannelClassType                        **
**                                                                           **
** Description :      Function to obtain the channel class                   **
**                                                                           **
** Traceability :     [cover parentID={AF0CA4B7-829B-40ca-B4F3-605307634505}]**
**                  [/cover]                                                 **
*****************************************************************************/
LOCAL_INLINE Pwm_17_GtmCcu6_ChannelClassType Pwm_lChanClass(const uint16 Value)
{
  Pwm_17_GtmCcu6_ChannelClassType RetVal;

  RetVal = (Pwm_17_GtmCcu6_ChannelClassType) \
           (((uint16)(Value) >> PWM_CHANNEL_CLASS_POS) & \
            (PWM_CHANNEL_CLASS_MASK));
  return(RetVal);
}

#if (PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
/*******************************************************************************
** Syntax : static void Pwm_lGtmStartChannelsInit                             **
**                   (                                                        **
                        const Pwm_17_GtmCcu6_ChannelType ChannelNumber,       **
**                      const uint8 CoreId                                    **
**                   )                                                        **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Non Reentrant                                            **
**                                                                            **
** Parameters (in):  ChannelNumber: PWM Channel number                        **
**                   CoreId : Core Number                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     This function starts the PWM channel as given by the     **
**                   input parameters with the desired properties.            **
**                                                                            **
** Traceability :    [cover parentID={9FE81C76-1746-48ad-8B71-5B7776D8C6AB}]  **
**                    [/cover]                                                **
*******************************************************************************/
static void Pwm_lGtmStartChannelsInit
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
)
{
  Mcu_17_Gtm_TimerOutType PwmGtmTimerType;
  const Mcu_17_Gtm_TomAtomChConfigType *PwmGtmTimerPtr;
  /* MISRA2012_RULE_11_5_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  /* MISRA2012_RULE_11_3_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  PwmGtmTimerPtr = (const Mcu_17_Gtm_TomAtomChConfigType*)\
                   Pwm_ConfigPtr->PwmCoreAdd[CoreId]->Pwm_ChannelConfigPtr\
                   [ChannelNumber].PwmTimerPtr;
  PwmGtmTimerType = PwmGtmTimerPtr->TimerType;

  /* [cover parentID={80FD58CB-6F1E-4e1d-B9A8-18F4FF92CEC0}]
  If GTM timer type is TOM [/cover] */
  if(PwmGtmTimerType == MCU_GTM_TIMER_TOM)
  {
    /* [cover parentID={776D9E53-4127-47eb-A512-2F9525612702}]
    Initialize TOM channel [/cover] */
    Pwm_lGtmStartTomChannelsInit(ChannelNumber, CoreId);
  }
  /* [cover parentID={80FD58CB-6F1E-4e1d-B9A8-18F4FF92CEC0}]
  If GTM timer type is ATOM [/cover] */
  if(PwmGtmTimerType == MCU_GTM_TIMER_ATOM)
  {
    /* [cover parentID={205AF741-397E-44d0-88C9-A7A6CFF0B23B}]
    Initialize ATOM channel [/cover] */
    Pwm_lGtmStartAtomChannelsInit(ChannelNumber, CoreId);
  }
}
#if (PWM_17_GTMCCU6_INITCHECK_API == STD_ON)
/*******************************************************************************
** Syntax : static void Pwm_lGtmStartChannelsInitCheck                        **
**                   (                                                        **
                       const Pwm_17_GtmCcu6_ChannelType ChannelNumber,        **
**                     const uint8 CoreId                                     **
**                   )                                                        **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Non Rreentrant                                           **
**                                                                            **
** Parameters (in):  ChannelNumber: PWM Channel number                        **
**                   CoreId : Core Number                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     Std_ReturnType                                           **
**                                                                            **
** Description :     Function to verify the start of PWM channel as given by  **
**                   the Input parameters with the desired properties.        **
**                                                                            **
** Traceability:    [cover parentID={38AE583A-AB8D-4f44-B425-24D8ABC459B2}]   **
**                      [/cover]                                              **
*******************************************************************************/
static Std_ReturnType Pwm_lGtmStartChannelsInitCheck
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
)
{
  Mcu_17_Gtm_TimerOutType PwmGtmTimerType;
  Std_ReturnType ErrorStatus = E_OK;
  const Mcu_17_Gtm_TomAtomChConfigType *PwmGtmTimerPtr;
  /* MISRA2012_RULE_11_5_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  /* MISRA2012_RULE_11_3_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  PwmGtmTimerPtr = (const Mcu_17_Gtm_TomAtomChConfigType*)\
                   Pwm_ConfigPtr->PwmCoreAdd[CoreId]->Pwm_ChannelConfigPtr\
                   [ChannelNumber].PwmTimerPtr;
  PwmGtmTimerType = PwmGtmTimerPtr->TimerType;

  /* [cover parentID={283ED6DA-FA96-4dd7-BE92-AB4D2123EC21}]
  If timer type is TOM [/cover] */
  if(PwmGtmTimerType == MCU_GTM_TIMER_TOM)
  {
    /* [cover parentID={D9AFC15F-6A58-415d-90D8-F88DC72D4F81}]
    Start TOM channels init check [/cover] */
    ErrorStatus = Pwm_lGtmStartTomChannelsInitCheck(ChannelNumber, CoreId);
  }
  /* [cover parentID={283ED6DA-FA96-4dd7-BE92-AB4D2123EC21}]
  If timer type is ATOM [/cover] */
  if(PwmGtmTimerType == MCU_GTM_TIMER_ATOM)
  {
    /* [cover parentID={60B09FEF-12ED-4478-BDDD-A5EFE3DEDF9E}]
    Start ATOM channels init check [/cover] */
    ErrorStatus = Pwm_lGtmStartAtomChannelsInitCheck(ChannelNumber, CoreId);
  }
  /* [cover parentID={D66CE0F1-747B-4226-B3E6-DC185F2D3687}]
  Return status check result [/cover] */
  return ErrorStatus;
}
#endif
/*******************************************************************************
** Syntax : static void Pwm_lGtmStartTomChannelsInit                          **
**                   (                                                        **
**                     const Pwm_17_GtmCcu6_ChannelType ChannelNumber,        **
**                     const uint8 CoreId                                     **
**                   )                                                        **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Non Reentrant                                            **
**                                                                            **
** Parameters (in):  ChannelNumber:  PWM Channel number                       **
**                   CoreId : Core Number                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     Function starts the PWM channel as given by the Input    **
**                   parameters with the desired properties.                  **
**                                                                            **
** Traceability:     [cover parentID={7611FD19-04D4-486b-915B-9708BB0C9241}]  **
**                      [/cover]                                              **
*******************************************************************************/
static void Pwm_lGtmStartTomChannelsInit
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
)
{
  Ifx_GTM_TOM_CH* TomChannelRegPtr; /* Ptr to TOM Channel Reg */
  uint8 Coherency;
  uint8 TimerChannelNumber;
  uint8 TimerModuleNumber;
  const Pwm_17_GtmCcu6_ChannelConfigType  *PwmChannelCfgPtr;
  const Pwm_17_GtmCcu6_CoreConfigType     *PwmCorePtr;
  const Mcu_17_Gtm_TomAtomChConfigType    *PwmGtmTimerPtr;

  PwmCorePtr = Pwm_ConfigPtr->PwmCoreAdd[CoreId];
  PwmChannelCfgPtr = (const Pwm_17_GtmCcu6_ChannelConfigType *)\
                     &(PwmCorePtr->Pwm_ChannelConfigPtr[ChannelNumber]);
  /* MISRA2012_RULE_11_5_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  /* MISRA2012_RULE_11_3_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  PwmGtmTimerPtr = (const Mcu_17_Gtm_TomAtomChConfigType*)\
                   PwmChannelCfgPtr->PwmTimerPtr;
  TimerModuleNumber    = (uint8)((PwmGtmTimerPtr->TimerId &\
                                  GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);
  TimerChannelNumber   = (uint8)((PwmGtmTimerPtr->TimerId &\
                                  GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);
  Coherency          = Pwm_lCoherency(PwmChannelCfgPtr->PwmChannelInfo);

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TomChannelRegPtr = \
                 PWM_GTM_TOM_CH_POINTER(TimerModuleNumber, TimerChannelNumber);
  
  /* [cover parentID={EE32E8C1-DB79-481a-A0F5-C568829C2A63}]
  Disable channel and channel output directly to avoid signal level changes 
  during initialization [/cover] */
  Pwm_lGtmResetOutEnEndisStat(TimerModuleNumber, TimerChannelNumber, \
                                                            MCU_GTM_TIMER_TOM);
  /*Clear interrupts for the channel and disable interrupts for the channel*/
  /* [cover parentID={CC35D4CF-BD97-4b0d-8AB9-99497C5DB921}]
  Clear pending interrups and disable the channel [/cover] */
  TomChannelRegPtr->IRQ.NOTIFY.U = PWM_CLR_PENDING_INTERRUPTS;
  TomChannelRegPtr->IRQ.EN.U = 0U;

  /* Call GTM Library to Initialize TOM channel */
  /* [cover parentID={6EB7E407-A991-4701-A605-B9FCCBCD4219}]
   Clear notification during initialization [/cover] */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: PwmTimerPtr is of 
  type Mcu_17_Ccu6_TimerConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  /* MISRA2012_RULE_11_3_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  Mcu_17_Gtm_TomChannelInit(PwmGtmTimerPtr);
                                            
  /* [cover parentID={2791486E-C76D-4e8b-9E42-6B713EEC07D7}]
  If channel is of type Coherent [/cover] */
  if(Coherency == PWM_17_GTMCCU6_COHERENT)
  {
    /* [cover parentID={061D24EA-2896-4add-ABD1-199154ED8EE2}]
    Update Enable on reset of counter for channel of type Coherent [/cover] */
    Mcu_17_Gtm_TomChUpdateEnDis(TimerModuleNumber, TimerChannelNumber, \
                                                  MCU_GTM_TIMER_UPDATE_ENABLE);
  }
  
  /* [cover parentID={937D4243-2017-4322-B530-349BBC5C974C}]
  Copy of values from shadow registers, Compare values(duty, period) & Clock
  Source, of the specified TOM channel to its main timer registers [/cover]*/
  Mcu_17_Gtm_TomChannelShadowTransfer(TimerModuleNumber, TimerChannelNumber);
  
  #if (PWM_17_GTMCCU6_HANDLE_SHIFT_BY_OFFSET == STD_OFF)
  
  /* [cover parentID={8C530BAD-4690-4095-8DCD-DE3D52D07A04}]
  Enable channel [/cover] */
  Mcu_17_Gtm_TomChEndisStatUpdate(TimerModuleNumber, TimerChannelNumber, \
                                                         MCU_GTM_TIMER_ENABLE);
  /* [cover parentID={416DA007-0A66-446f-A4CB-B284752BF665}]
  Enable channel output [/cover] */
  Mcu_17_Gtm_TomChOutEnStatUpdate(TimerModuleNumber, TimerChannelNumber, \
                                                     MCU_GTM_TIMER_OUT_ENABLE);
  #else
  /* [cover parentID={4121283A-36E8-45af-8E65-6B43965F7505}]
  Enable TOM channel output control [/cover] */
  Mcu_17_Gtm_TomChOutEnCtrlUpdate(TimerModuleNumber, TimerChannelNumber, \
                                                    MCU_ENABLE_OUT_ON_TRIGGER);
  #endif
}
#if (PWM_17_GTMCCU6_INITCHECK_API == STD_ON)
/*******************************************************************************
** Syntax : static Std_ReturnType Pwm_lGtmStartTomChannelsInitCheck           **
**                   (                                                        **
**                     const Pwm_17_GtmCcu6_ChannelType ChannelNumber         **
**                     const uint8 CoreId                                     **
**                   )                                                        **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Non Reentrant                                            **
**                                                                            **
** Parameters (in):  ChannelNumber - PWM Channel number                       **
**                   CoreId : Core Number                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     E_OK: TOM initialization check passed                    **
**                   E_NOT_OK: TOM initialization check failed                **
**                                                                            **
** Description :     Function to verify the initialization of TOM channel     **
**                                                                            **
** Traceability:   [cover parentID={76D86AB3-739D-45a8-9FE2-C368AB88D3B4}]    **
**                  [/cover]                                                  **
*******************************************************************************/
static Std_ReturnType Pwm_lGtmStartTomChannelsInitCheck
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
)
{
  const Ifx_GTM_TOM_CH* TomChannelRegPtr; /* Ptr to TOM Channel Reg */
  const Mcu_17_Gtm_TomTgc* TomTgcRegPtr;  /* Ptr to TOM TGC Reg */
  uint8 BitPos;
  uint8 Coherency;
  uint8 TimerChannelNumber;
  uint8 TimerModuleNumber;
  Std_ReturnType ErrorStatus;
  uint8 GroupNumber;
  uint32 RegVal;
  const Pwm_17_GtmCcu6_ChannelConfigType  *PwmChannelCfgPtr;
  const Pwm_17_GtmCcu6_CoreConfigType     *PwmCorePtr;
  const Mcu_17_Gtm_TomAtomChConfigType    *PwmGtmTimerPtr;
  /* [cover parentID={E2213FBB-A881-4062-B0CB-FBF0F8174E68}]
  Get PWM channel configuration and GTM timer configuration of the core
  [/cover] */
  PwmCorePtr = Pwm_ConfigPtr->PwmCoreAdd[CoreId];
  PwmChannelCfgPtr = (const Pwm_17_GtmCcu6_ChannelConfigType *)\
                     &(PwmCorePtr->Pwm_ChannelConfigPtr[ChannelNumber]);
  /* MISRA2012_RULE_11_5_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  /* MISRA2012_RULE_11_3_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  PwmGtmTimerPtr = (const Mcu_17_Gtm_TomAtomChConfigType*)\
                   PwmChannelCfgPtr->PwmTimerPtr;
  TimerModuleNumber    = (uint8)((PwmGtmTimerPtr->TimerId &\
                                  GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);
  TimerChannelNumber   = (uint8)((PwmGtmTimerPtr->TimerId &\
                                  GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);
  GroupNumber        = TimerChannelNumber >> PWM_CONST_3;
  
  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TomChannelRegPtr = \
                  PWM_GTM_TOM_CH_POINTER(TimerModuleNumber, TimerChannelNumber);
  /* Verify the reset status of OUTEN and ENDIS stat registers */
  ErrorStatus = Pwm_lGtmResetOutEnEndisStatCheck(TimerModuleNumber, \
                                         TimerChannelNumber, MCU_GTM_TIMER_TOM);
  /* [cover parentID={B8552177-135E-4826-91AE-1B89B348E1DF}]
  Is error status is OK [/cover] */
  if(ErrorStatus == E_OK)
  {
    /* [cover parentID={9A50C82D-5E66-4f92-B6FA-BCBB9D6BC9B3}]
    If interrupts are not enabled [/cover] */
    if(TomChannelRegPtr->IRQ.EN.U != 0U)
    {
      ErrorStatus = E_NOT_OK;
    }
  }
  /* [cover parentID={1B8D408C-6C3D-456b-AF73-C2B22E51D2B7}]
  Is error status is OK [/cover] */
  if(ErrorStatus == E_OK)
  {
    /* MISRA2012_RULE_11_5_JUSTIFICATION: PwmTimerPtr is of
    type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
    by violating this MISRA rule.*/
    /* MISRA2012_RULE_11_3_JUSTIFICATION: PwmTimerPtr is of
    type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
    by violating this MISRA rule.*/
    /* [cover parentID={8A0B68D6-60D5-48b1-8FE6-10A3AE2A196E}]
    Check initialization status of GTM TOM channel [/cover] */
    ErrorStatus = Mcu_17_Gtm_TomChInitCheck(PwmGtmTimerPtr);
    /* [cover parentID={EB6782D8-F790-4bb4-BDD0-DA3549EB73AA}]
    Is initialization verification status is OK [/cover] */
    if(ErrorStatus == E_OK)
    {
      /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects
       * foreseen by violating this MISRA rule, as the pointer to the object
       * type it is getting cast into is a known type . */
      /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects
       * foreseen by violating this MISRA rule. */
      /* Verify enable update for the channel of type coherent */
      TomTgcRegPtr = PWM_GTM_TOM_TGC_POINTER(TimerModuleNumber, GroupNumber);
      Coherency          = Pwm_lCoherency(PwmChannelCfgPtr->PwmChannelInfo);
      /* [cover parentID={64B10BD2-5E7D-4b12-BFFA-EC7EEAB78CF0}]
      If channel of type coherent [/cover] */
      if(Coherency == PWM_17_GTMCCU6_COHERENT)
      {
        BitPos = PWM_CONST_16 + \
                 (PWM_CONST_2 * (TimerChannelNumber % GTM_TOM_CH_PER_TGC));
        RegVal = TomTgcRegPtr->TGC_GLB_CTRL.U;
        RegVal = ((RegVal >> BitPos) & PWM_CONST_3);
        /* [cover parentID={C0C20D0C-2DC3-41e1-BDC6-F91AA59529E0}]
        If TOM channel global control register update not enabled [/cover] */
        if(RegVal != PWM_CONST_3)
        {
          /* [cover parentID={AA898444-06EC-4ad5-8C2D-9BDC74008687}]
          Set error status to E_NOT_OK [/cover] */
          ErrorStatus = E_NOT_OK;
        }
      }
    }
  }
  /* [cover parentID={C58D7F62-49F3-4103-AEEF-5025DFF4F562}]
  Return error status [/cover] */
  return ErrorStatus;
}
#endif
/*******************************************************************************
** Syntax : static void Pwm_lGtmStartAtomChannelsInit                         **
**                   (                                                        **
                       const Pwm_17_GtmCcu6_ChannelType ChannelNumber,        **
**                     const uint8 CoreId                                     **
**                   )                                                        **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Non Reentrant                                            **
**                                                                            **
** Parameters (in):  ChannelNumber : PWM Channel number                       **
**                   CoreId : Core Number                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     Function starts the PWM channel as given by the Input    **
**                   parameters with the desired properties.                  **
**                                                                            **
** Traceability:   [cover parentID={A8793835-EC16-44f5-B937-5C729FE845BC}]    **
**                  [/cover]                                                  **
*******************************************************************************/
static void Pwm_lGtmStartAtomChannelsInit
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
)
{
  uint8 Coherency;
  uint8 TimerChannelNumber;
  uint8 TimerModuleNumber;
  Ifx_GTM_ATOM_CH* AtomChannelRegPtr; /* Ptr to ATOM Channel Reg  */
  const Pwm_17_GtmCcu6_ChannelConfigType  *PwmChannelCfgPtr;
  const Pwm_17_GtmCcu6_CoreConfigType     *PwmCorePtr;
  const Mcu_17_Gtm_TomAtomChConfigType    *PwmGtmTimerPtr;

  PwmCorePtr = Pwm_ConfigPtr->PwmCoreAdd[CoreId];
  PwmChannelCfgPtr = (const Pwm_17_GtmCcu6_ChannelConfigType *)&\
                     (PwmCorePtr->Pwm_ChannelConfigPtr[ChannelNumber]);
  /* MISRA2012_RULE_11_5_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Ccu6_TimerConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  /* MISRA2012_RULE_11_3_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  PwmGtmTimerPtr = (const Mcu_17_Gtm_TomAtomChConfigType*)\
                   PwmChannelCfgPtr->PwmTimerPtr;
  TimerModuleNumber    = (uint8)((PwmGtmTimerPtr->TimerId &\
                                  GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);
  TimerChannelNumber   = (uint8)((PwmGtmTimerPtr->TimerId &\
                                  GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);
  Coherency            = Pwm_lCoherency(PwmChannelCfgPtr->PwmChannelInfo);

  /* Configure the Irq Mode, Irq Enable and Channel Ctrl register */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  AtomChannelRegPtr = \
                 PWM_GTM_ATOM_CH_POINTER(TimerModuleNumber, TimerChannelNumber);
  
  /* [cover parentID={3EDF1625-22C0-445a-9D05-95AA146176C2}]
  Disable channel and channel output directly to avoid signal level changes 
  during initialization [/cover] */
  Pwm_lGtmResetOutEnEndisStat(TimerModuleNumber, TimerChannelNumber, \
                                                            MCU_GTM_TIMER_ATOM);
  
  /*Clear interrupts for the channel and disable interrupts for the channel*/
  /* [cover parentID={B4D42C0C-3273-45cf-987D-0303078D317B}]
  Clear pending interrupts and disable notification [/cover] */
  AtomChannelRegPtr->IRQ.NOTIFY.U = PWM_CLR_PENDING_INTERRUPTS;
  AtomChannelRegPtr->IRQ.EN.U = 0U;

  /* Call GTM Library to Initialize TOM channel */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Ccu6_TimerConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  /* MISRA2012_RULE_11_3_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  /* [cover parentID={6EB7E407-A991-4701-A605-B9FCCBCD4219}]
  Clear notification during initialization [/cover] */
  Mcu_17_Gtm_AtomChannelInit(PwmGtmTimerPtr);
  
  /* [cover parentID={57DDCA50-284C-4f6d-AD50-E701CF93C30E}]
  If channel is of type Coherent [/cover] */
  if(Coherency == PWM_17_GTMCCU6_COHERENT)
  {
    /* [cover parentID={89E0FCDF-ADB7-44d1-8DED-6B745A96D62E}]
    Enable update enable for channel if Coherent update is desired [/cover] */
    Mcu_17_Gtm_AtomChUpdateEnDis\
    (TimerModuleNumber, TimerChannelNumber, MCU_GTM_TIMER_UPDATE_ENABLE);
  }

  
  /* [cover parentID={06E68FB7-3D11-45a3-9885-52B8585964A5}]
  Copy of values from shadow registers, Compare values(duty, period) & Clock 
  Source, of the specified ATOM channel to its main timer registers [/cover]*/
  Mcu_17_Gtm_AtomChannelShadowTransfer(TimerModuleNumber, TimerChannelNumber);
  
  #if (PWM_17_GTMCCU6_HANDLE_SHIFT_BY_OFFSET == STD_OFF)
  
  /* [cover parentID={CDFB45C3-ADE4-409a-ABE5-06113F436575}]
  Enable channel directly [/cover] */
  Mcu_17_Gtm_AtomChEndisStatUpdate(TimerModuleNumber, TimerChannelNumber, \
                                   MCU_GTM_TIMER_ENABLE);
  /* [cover parentID={70823412-F901-4186-8B73-5F9DCCC5052A}]
  Enable channel output directly [/cover] */
  Mcu_17_Gtm_AtomChOutEnStatUpdate(TimerModuleNumber, TimerChannelNumber, \
                                   MCU_GTM_TIMER_OUT_ENABLE);
  #else
  /* [cover parentID={FBCF56A6-5E9B-4ed0-AC14-D9F642226B09}]
  Enable TOM Channel Output Control register [/cover] */
  Mcu_17_Gtm_AtomChOutEnCtrlUpdate(TimerModuleNumber, TimerChannelNumber, \
                                   MCU_ENABLE_OUT_ON_TRIGGER );
  #endif
}
#if (PWM_17_GTMCCU6_INITCHECK_API == STD_ON)
/*******************************************************************************
** Syntax : static Std_ReturnType Pwm_lGtmStartAtomChannelsInitCheck          **
**                   (                                                        **
                       const Pwm_17_GtmCcu6_ChannelType ChannelNumber,        **
**                     const uint8 CoreId                                     **
**                   )                                                        **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Non Reentrant                                            **
**                                                                            **
** Parameters (in):  ChannelNumber : PWM Channel number                       **
**                   CoreId : Core Number                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     E_OK: ATOM initialization check passed                   **
**                   E_NOT_OK: ATOM initialization check failed               **
**                                                                            **
** Description :     Function to verify the initialization of ATOM channel    **

**                                                                            **
** Traceability:  [cover parentID={5805BFD4-2A17-4797-B1F3-EA5F30CCD10D}]     **
**                  [/cover]                                                  **
*******************************************************************************/
static Std_ReturnType Pwm_lGtmStartAtomChannelsInitCheck
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
)
{
  uint8 Coherency;
  uint8 TimerChannelNumber;
  uint8 TimerModuleNumber;
  Std_ReturnType ErrorStatus;
  uint8 BitPos;
  const Ifx_GTM_ATOM_AGC* AtomRegPtr; /* Ptr to ATOM AGC Reg */
  const Ifx_GTM_ATOM_CH* AtomChannelRegPtr; /* Ptr to ATOM Channel Reg */
  const Pwm_17_GtmCcu6_ChannelConfigType  *PwmChannelCfgPtr;
  const Pwm_17_GtmCcu6_CoreConfigType     *PwmCorePtr;
  const Mcu_17_Gtm_TomAtomChConfigType    *PwmGtmTimerPtr;
  uint32 RegVal; /* For Temp storage of Reg Value */

  PwmCorePtr = Pwm_ConfigPtr->PwmCoreAdd[CoreId];
  PwmChannelCfgPtr = (const Pwm_17_GtmCcu6_ChannelConfigType *)&\
                     (PwmCorePtr->Pwm_ChannelConfigPtr[ChannelNumber]);
  /* MISRA2012_RULE_11_5_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Ccu6_TimerConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  /* MISRA2012_RULE_11_3_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  /* [cover parentID={5EEE8469-F3C8-476e-B61A-F31D8F807B92}]
  Get PWM channel configuration and GTM timer configuration of the core
  [/cover] */
  PwmGtmTimerPtr     = (const Mcu_17_Gtm_TomAtomChConfigType*)\
                                                PwmChannelCfgPtr->PwmTimerPtr;
  TimerModuleNumber  = (uint8)((PwmGtmTimerPtr->TimerId &\
                                    GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);
  TimerChannelNumber = (uint8)((PwmGtmTimerPtr->TimerId &\
                                  GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);
  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  AtomChannelRegPtr = \
                 PWM_GTM_ATOM_CH_POINTER(TimerModuleNumber, TimerChannelNumber);
  /* [cover parentID={C76ECC71-1C99-4af9-9061-DF714164D012}] Verify the 
  disabled state of OUTEN and ENDIS stat registers  [/cover] */
  ErrorStatus = Pwm_lGtmResetOutEnEndisStatCheck(TimerModuleNumber, \
                                        TimerChannelNumber, MCU_GTM_TIMER_ATOM);
  /* [cover parentID={44158C8E-55BA-4dfd-8773-6516BCDDD76B}]
  Is error status is OK [/cover] */
  if(ErrorStatus == E_OK)
  { 
    /* [cover parentID={A872D690-255B-42cd-AFE5-0CF3763D211C}]
    If interrupts are not enabled [/cover] */
    if(AtomChannelRegPtr->IRQ.EN.U != 0U)
    {
      /* [cover parentID={FDFCCA75-F15E-407a-9726-36FE00480A86}]
      Set error status to E_NOT_OK [/cover] */
      ErrorStatus = E_NOT_OK;
    }
  }
  /* [cover parentID={9A71E7B9-C003-412a-91E3-F161A54B6BD6}]
  Is error status is OK [/cover] */
  if(ErrorStatus == E_OK)
  {
    /* Call GTM Library to Initialize TOM channel */
    /* MISRA2012_RULE_11_5_JUSTIFICATION: PwmTimerPtr is of
    type Mcu_17_Ccu6_TimerConfigType. No side effects foreseen
    by violating this MISRA rule.*/
    /* MISRA2012_RULE_11_3_JUSTIFICATION: PwmTimerPtr is of
    type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
    by violating this MISRA rule.*/
    /* [cover parentID={6EB7E407-A991-4701-A605-B9FCCBCD4219}]
    Clear notification at initialization [/cover] */
    /* [cover parentID={A5641DBD-61F5-4473-8721-5378FC63C341}]
    Check initialization status of GTM ATOM channel [/cover] */
    ErrorStatus = Mcu_17_Gtm_AtomChInitCheck(PwmGtmTimerPtr);
    /* [cover parentID={88B7A965-6941-49da-9366-0E57D00044EC}]
    Is ATOM initialization status E_OK [/cover] */
    if(ErrorStatus == E_OK)
    {
      /* Verify enable update for the channel of type coherent */
      AtomRegPtr = PWM_GTM_ATOM_AGC_POINTER(TimerModuleNumber);
      Coherency = Pwm_lCoherency(PwmChannelCfgPtr->PwmChannelInfo);
      /* [cover parentID={E73BE735-33D4-4d24-B105-CFE3F7706120}]
      If channel is of type coherent [/cover] */
      if(Coherency == PWM_17_GTMCCU6_COHERENT)
      {
        BitPos = PWM_CONST_16 + (PWM_CONST_2 * TimerChannelNumber);
        RegVal = AtomRegPtr->GLB_CTRL.U;
        RegVal = ((RegVal >> BitPos) & PWM_CONST_3);
        /* [cover parentID={BF2B25BD-C18B-4d4b-AAB8-9E128A4AD1B2}]
        If ATOM channel global control register update not enabled
        [/cover] */
        if(RegVal != PWM_CONST_3)
        {
          /* [cover parentID={E3F6E9E3-7585-4ec8-8567-1DE6404D6B65}]
          Set error status to E_NOT_OK [/cover] */
          ErrorStatus = E_NOT_OK;
        }
      }
    }
  }
  /* [cover parentID={42267F17-312F-451e-BE09-AD08FF54CCF4}]
  Return error status [/cover] */
  return ErrorStatus;
}
#endif
/*******************************************************************************
** Syntax : static void Pwm_lGtmResetOutEnEndisCtrl                           **
**                   (                                                        **
                       const uint8 TimerModuleNumber,                         **
**                     const uint8 TimerChannelNumber,                        **
**                     const Mcu_17_Gtm_TimerOutType PwmGtmTimerType          **
**                   )                                                        **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Non Reentrant                                            **
**                                                                            **
** Parameters (in):  TimerModuleNumber  : Module Id                           **
**                   TimerChannelNumber : Channel Id                          **
**                   PwmGtmTimerType    : GTM Timer Type                      **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     Function reset OUTEN and ENDIS control register to       **
**                   protect from unintended shadow transfers which may occur **
**                   during runtime leading incorrect signal output           **
** Traceability:   [cover parentID={E41A496F-25EF-4281-9458-7E087DA8453D}]    **
**                  [/cover]                                                  **
*******************************************************************************/
static void Pwm_lGtmResetOutEnEndisCtrl
(
  const uint8 TimerModuleNumber,
  const uint8 TimerChannelNumber,
  const Mcu_17_Gtm_TimerOutType PwmGtmTimerType
)
{
  /* [cover parentID={355C6207-91E0-4b76-A4EF-953A50C80196}]
  If GTM timer is TOM [/cover] */
  if(PwmGtmTimerType == MCU_GTM_TIMER_TOM)
  {
    /* [cover parentID={F1841343-48BE-4bca-8981-3FDDBA42F252}]
    Disable TOM Channel Control register [/cover] */
    Mcu_17_Gtm_TomChEndisCtrlUpdate(TimerModuleNumber, TimerChannelNumber, \
                                    MCU_NOCHANGE_ON_TRIGGER);
    /* [cover parentID={C8C5700A-05D2-4119-AE9B-EDF7011865C2}]
    Disable TOM Channel Output Control register [/cover] */
    Mcu_17_Gtm_TomChOutEnCtrlUpdate(TimerModuleNumber, TimerChannelNumber, \
                                    MCU_NOCHANGE_OUT_ON_TRIGGER);
  }
  else
  {
    /* [cover parentID={856358C5-ED90-407b-ADD3-84F92B25CF50}]
    Disable ATOM Channel Control register [/cover] */
    Mcu_17_Gtm_AtomChEndisCtrlUpdate(TimerModuleNumber, TimerChannelNumber, \
                                    MCU_NOCHANGE_ON_TRIGGER);
    /* [cover parentID={95B821F6-E9CB-488d-B738-2BB81B0ADBA4}]
    Disable ATOM Channel Output Control register [/cover] */
    Mcu_17_Gtm_AtomChOutEnCtrlUpdate(TimerModuleNumber, TimerChannelNumber, \
                                    MCU_NOCHANGE_OUT_ON_TRIGGER);
  }
}
#if (PWM_17_GTMCCU6_INITCHECK_API == STD_ON)
/*******************************************************************************
** Syntax : static void Pwm_lGtmResetOutEnEndisCtrlCheck                      **
**                   (                                                        **
                       const uint8 TimerModuleNumber,                         **
**                     const uint8 TimerChannelNumber,                        **
**                     const Mcu_17_Gtm_TimerOutType PwmGtmTimerType          **
**                   )                                                        **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Non Reentrant                                            **
**                                                                            **
** Parameters (in):  TimerModuleNumber  : Module Id                           **
**                   TimerChannelNumber : Channel Id                          **
**                   PwmGtmTimerType    : GTM Timer Type                      **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     E_OK: Reset of ENDIS and OUTEN control register          **
**                         verification passed                                **
**                   E_NOT_OK: Reset of ENDIS and OUTEN control register      **
**                         verification failed                                **
** Description :     Function to verify reset of OUTEN and ENDIS control      **
**                   register                                                 **
** Traceability :  [cover parentID={7C00912A-B5D3-4a9d-A8B1-5C2995C2E96E}]    **
**                   [/cover]                                                 **
*******************************************************************************/
static Std_ReturnType Pwm_lGtmResetOutEnEndisCtrlCheck
(
  const uint8 TimerModuleNumber,
  const uint8 TimerChannelNumber,
  const Mcu_17_Gtm_TimerOutType PwmGtmTimerType
)
{
  uint8 GroupNumber;
  const Mcu_17_Gtm_TomTgc* TomTgcRegPtr;
  const Ifx_GTM_ATOM_AGC* AtomRegPtr;
  Std_ReturnType ErrorStatus = E_OK;
  uint8 BitPos;
  uint32 RegVal; /* For Temp storage of Reg Value */
  /* [cover parentID={7C05A007-8856-4bf5-8FA4-40B1795F9A6F}]
  If timer type is TOM [/cover] */
  if(PwmGtmTimerType == MCU_GTM_TIMER_TOM)
  {
    GroupNumber = TimerChannelNumber >> PWM_CONST_3;
    /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
     * by violating this MISRA rule, as the pointer to the object type
     * it is getting cast into is a known type . */
    /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
     * by violating this MISRA rule. */
    TomTgcRegPtr = PWM_GTM_TOM_TGC_POINTER(TimerModuleNumber, GroupNumber);
    BitPos = PWM_CONST_2 * (TimerChannelNumber % GTM_TOM_CH_PER_TGC);
    RegVal = TomTgcRegPtr->TGC_ENDIS_CTRL.U;
    /* [cover parentID={C09AB35D-B0F4-41a9-A47D-AB7464510319}]
    If ENDIS control value is not 0 [/cover] */
    if(((RegVal >> BitPos) & PWM_CONST_3) != 0U)
    {
      /* [cover parentID={FF828A1D-BCFD-4536-99DC-5B6E577181A9}]
      Set error status to E_NOT_OK [/cover] */
      ErrorStatus = E_NOT_OK;
    }
    RegVal = TomTgcRegPtr->TGC_OUTEN_CTRL.U;
    /* [cover parentID={999316E1-EF87-4370-8993-6E44E2DE61BF}]
    If the output for channel is disabled [/cover] */
    if(((RegVal >> BitPos) & PWM_CONST_3) != 0U)
    {
      /* [cover parentID={2FBC1C9A-F75D-4602-A382-FCA1F464439D}]
      Set error status to NOT OK [/cover] */
      ErrorStatus = E_NOT_OK;
    }
  }
  else
  {
    AtomRegPtr = PWM_GTM_ATOM_AGC_POINTER(TimerModuleNumber);
    BitPos = PWM_CONST_2 * TimerChannelNumber;
    RegVal = AtomRegPtr->ENDIS_CTRL.U;
    /* [cover parentID={B81155E3-325A-4b3b-B0AF-699B411A1BD1}]
    If ENDIS control value is not 0 [/cover] */
    if(((RegVal >> BitPos) & PWM_CONST_3) != 0U)
    {
      /* [cover parentID={CB48A570-8548-4144-A5D8-E32FC2BF8A88}]
      Set error status to E_NOT_OK [/cover] */
      ErrorStatus = E_NOT_OK;
    }
    RegVal = AtomRegPtr->OUTEN_CTRL.U;
    /* [cover parentID={0C28C6BE-F0D7-4a70-94B3-7052ABE38047}]
    If the output for channel is disabled [/cover] */
    if(((RegVal >> BitPos) & PWM_CONST_3) != 0U)
    {
      /* [cover parentID={6F607A6D-F5D3-44f7-BD85-49D478A2745C}]
      Set error status to E_NOT_OK [/cover] */
      ErrorStatus = E_NOT_OK;
    }
  }
  /* [cover parentID={A423C0F0-37D6-4da0-9350-08DFCE904AA2}]
  Return error status [/cover] */
  return ErrorStatus;
}
#endif
/*******************************************************************************
** Syntax : static void Pwm_lGtmResetOutEnEndisStat                           **
**                   (                                                        **
                       const uint8 TimerModuleNumber,                         **
**                     const uint8 TimerChannelNumber,                        **
**                     const Mcu_17_Gtm_TimerOutType PwmGtmTimerType          **
**                   )                                                        **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Non Reentrant                                            **
**                                                                            **
** Parameters (in):  TimerModuleNumber  : Timer Module Number                 **
**                   TimerChannelNumber : Timer Channel Number                **
**                   PwmGtmTimerType    : GTM Timer Type                      **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     Function resets ENDIS and OUTEN stat register to protect **
**                  from unintended signal output change during initialization**
**                                                                            **
** Traceability :  [cover parentID={0837E011-FE2A-46e1-9EA7-68FD306D36D1}]    **
**                   [/cover]                                                 **
*******************************************************************************/
static void Pwm_lGtmResetOutEnEndisStat
(
  const uint8 TimerModuleNumber,
  const uint8 TimerChannelNumber,
  const Mcu_17_Gtm_TimerOutType PwmGtmTimerType
)
{
  /* [cover parentID={0866CE99-3AF9-4b10-A178-BBF3DB3062C3}]
  If GTM timer is TOM [/cover] */
  if(PwmGtmTimerType == MCU_GTM_TIMER_TOM)
  {
    /* [cover parentID={C6D3F962-C7BF-4f97-8209-A3746CD9E305}]
    Disable TOM Channel stat register [/cover] */
    Mcu_17_Gtm_TomChEndisStatUpdate(TimerModuleNumber, TimerChannelNumber, \
                                    MCU_GTM_TIMER_DISABLE);
    /* [cover parentID={4E016391-0688-485d-B315-6F4B9AB740C8}]
    Disable TOM Channel Output stat register [/cover] */
    Mcu_17_Gtm_TomChOutEnStatUpdate(TimerModuleNumber, TimerChannelNumber, \
                                    MCU_GTM_TIMER_OUT_DISABLE);
  }
  else
  {
    /* [cover parentID={BC9B7F8D-32A0-4d88-BC96-AC26194B506A}]
    Disable ATOM Channel stat register [/cover] */
    Mcu_17_Gtm_AtomChEndisStatUpdate(TimerModuleNumber, TimerChannelNumber, \
                                    MCU_GTM_TIMER_DISABLE);
    /* [cover parentID={A3344B9D-30BA-4bfb-B6EF-637E4BF6F3E1}]
    Disable ATOM Channel Output stat register [/cover] */
    Mcu_17_Gtm_AtomChOutEnStatUpdate(TimerModuleNumber, TimerChannelNumber, \
                                    MCU_GTM_TIMER_OUT_DISABLE);
  }
}
#if (PWM_17_GTMCCU6_INITCHECK_API == STD_ON)
/*******************************************************************************
** Syntax : static Std_ReturnType Pwm_lGtmResetOutEnEndisStatCheck            **
**                   (                                                        **
                       const uint8 TimerModuleNumber,                         **
**                     const uint8 TimerChannelNumber,                        **
**                     const Mcu_17_Gtm_TimerOutType PwmGtmTimerType          **
**                   )                                                        **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Non Reentrant                                            **
**                                                                            **
** Parameters (in):  TimerModuleNumber  : Timer Module Number                 **
**                   TimerChannelNumber : Timer Channel Number                **
**                   PwmGtmTimerType    : GTM Timer Type                      **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     E_OK: Reset of ENDIS and OUTEN stat register             **
**                         verification passed                                **
**                   E_NOT_OK: Reset of ENDIS and OUTEN stat register         **
**                         verification failed                                **
** Description :     Function to verify reset of ENDIS and OUTEN stat register**
**                                                                            **
** Traceability :  [cover parentID={CE06DBC5-B91B-4de0-9639-C0CB5FB20D11}]    **
**                   [/cover]                                                 **
*******************************************************************************/
static Std_ReturnType Pwm_lGtmResetOutEnEndisStatCheck
(
  const uint8 TimerModuleNumber,
  const uint8 TimerChannelNumber,
  const Mcu_17_Gtm_TimerOutType PwmGtmTimerType
)
{
  uint8 GroupNumber;
  const Mcu_17_Gtm_TomTgc* TomTgcRegPtr;
  const Ifx_GTM_ATOM_AGC* AtomRegPtr;
  Std_ReturnType ErrorStatus = E_OK;
  uint8 BitPos;
  uint32 RegVal; /* For Temp storage of Reg Value */
  /* [cover parentID={C611D608-45C8-4b6b-8E3B-78746C0FC79E}]
  If timer type is TOM [/cover] */
  if(PwmGtmTimerType == MCU_GTM_TIMER_TOM)
  {
    GroupNumber = TimerChannelNumber >> PWM_CONST_3;
    /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
     * by violating this MISRA rule, as the pointer to the object type
     * it is getting cast into is a known type . */
    /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
     * by violating this MISRA rule. */
    /* [cover parentID={6758C5E8-E2EF-47be-BDBB-D94519647E2C}]
    Extract channels ENDIS stat value from register [/cover] */
    TomTgcRegPtr = PWM_GTM_TOM_TGC_POINTER(TimerModuleNumber, GroupNumber);
    BitPos = PWM_CONST_2 * (TimerChannelNumber % GTM_TOM_CH_PER_TGC);
    RegVal = TomTgcRegPtr->TGC_ENDIS_STAT.U;
    /* [cover parentID={F0C67BBF-1072-4c21-AFB5-C1F204D058FD}]
    If ENDIS stat for channel is not disabled [/cover] */
    if(((RegVal >> BitPos) & PWM_CONST_3) != PWM_CONST_3)
    {
      /* [cover parentID={BD1A6D96-BFBF-4a54-ADBB-C6828D53F35E}]
      Set error status to E_NOT_OK [/cover] */
      ErrorStatus = E_NOT_OK;
    }
    /* [cover parentID={B6638E16-24A0-4cca-BE2D-6024AD0C8845}]
    Extract channels OUTEN stat value from register [/cover] */
    RegVal = TomTgcRegPtr->TGC_OUTEN_STAT.U;
    /* [cover parentID={FC00B141-1FA8-4e76-8166-46663BB97D71}]
    If OUTEN stat for channel is not disabled [/cover] */
    if(((RegVal >> BitPos) & PWM_CONST_3) != PWM_CONST_3)
    {
      /* [cover parentID={A0650713-4DE4-4e50-9101-AA87A5AB7E95}]
      Set error status to NOT OK [/cover] */
      ErrorStatus = E_NOT_OK;
    }
  }
  else
  {
    /* [cover parentID={FABDB682-54B7-4ea0-84E8-893CAE67DF8C}]
    Extract channels ENDIS stat value from register [/cover] */
    AtomRegPtr = PWM_GTM_ATOM_AGC_POINTER(TimerModuleNumber);
    BitPos = PWM_CONST_2 * TimerChannelNumber;
    RegVal = AtomRegPtr->ENDIS_STAT.U;
    /* [cover parentID={EE0912C1-F531-42cc-8F77-76431F415B2C}]
    If ENDIS stat value is not disabled [/cover] */
    if(((RegVal >> BitPos) & PWM_CONST_3) != PWM_CONST_3)
    {
      /* [cover parentID={14980A76-E1E9-46e1-93FE-FBB35279C9D5}]
      Set error status to E_NOT_OK [/cover] */
      ErrorStatus = E_NOT_OK;
    }
    /* [cover parentID={C58BAFAD-BCFF-494f-AD68-D1FFFD6D0892}]
    Extract channels OUTEN stat value from register [/cover] */
    RegVal = AtomRegPtr->OUTEN_STAT.U;
    /* [cover parentID={C85DA552-1BA1-4ba4-A4DF-B5D6078EC996}]
    If the output for channel is disabled [/cover] */
    if(((RegVal >> BitPos) & PWM_CONST_3) != PWM_CONST_3)
    {
      /* [cover parentID={5ED5BFEB-06FE-4480-B275-2894AA5C7E5D}]
      Set error status to E_NOT_OK [/cover] */
      ErrorStatus = E_NOT_OK;
    }
  }
  /* [cover parentID={A423C0F0-37D6-4da0-9350-08DFCE904AA2}]
  Return error status [/cover] */
  return ErrorStatus;
}
#endif
#endif /* End of PWM_17_GTMCCU6_GTM_TIMER_USED */
#if (PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
/*******************************************************************************
** Syntax : static void Pwm_lCcu6StartChannelsInit                            **
**                   (                                                        **
**                     const Pwm_17_GtmCcu6_ChannelType ChannelNumber,        **
**                     const uint8 CoreId                                     **
**                   )                                                        **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Non Reentrant                                            **
**                                                                            **
** Parameters (in):  ChannelNumber : Channel number                           **
**                   CoreId : Core Number                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     Function starts the PWM channel as given by the Input    **
**                   parameters with the desired properties.                  **
** Traceability :     [cover parentID={32436CDE-CA69-40f9-94D7-BFA8C0E4A747}] **
**                   [/cover]                                                 **
*******************************************************************************/
static void Pwm_lCcu6StartChannelsInit
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
)
{
  const Mcu_17_Ccu6_TimerConfigType *PwmCcu6TimerPtr;
  const Pwm_17_GtmCcu6_ChannelConfigType  *LocalPwmChanPtr;
  uint8 Ccu6Comparator;
  uint8 Ccu6Kernel;
  uint32 Period = 0U;
  uint32 Duty = 0U;
  /* MISRA2012_RULE_11_5_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Ccu6_TimerConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  /* MISRA2012_RULE_11_3_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Ccu6_TimerConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  PwmCcu6TimerPtr = (const Mcu_17_Ccu6_TimerConfigType*)\
                    Pwm_ConfigPtr->PwmCoreAdd[CoreId]->Pwm_ChannelConfigPtr\
                    [ChannelNumber].PwmTimerPtr;
  Ccu6Comparator = (uint8)((PwmCcu6TimerPtr->TimerId >> \
                            PWM_CCU6_COMPARATOR_POS)& PWM_CCU6_COMPARATOR_MSK);
  LocalPwmChanPtr = &(Pwm_ConfigPtr->PwmCoreAdd\
                      [CoreId]->Pwm_ChannelConfigPtr[ChannelNumber]);
  Period = LocalPwmChanPtr->PwmPeriodDefault;
  Duty = LocalPwmChanPtr->PwmDutycycleDefault;
  /* [cover parentID={6EB7E407-A991-4701-A605-B9FCCBCD4219}]
  Clear notification at initialization [/cover] */
  /* [cover parentID={52F14C72-B201-4889-80B3-29AA9A93E50F}]
  Initialize CCU6 timer [/cover] */
  Mcu_17_Ccu6_TimerInit(PwmCcu6TimerPtr);

  Pwm_lCcu6StartChannel(ChannelNumber, Period, Duty, CoreId);
  /* [cover parentID={4ED6C3A4-7FF2-4df4-B98E-C7AD97A2E882}]
  If comparator is CCU63.[/cover] */
  if(Ccu6Comparator == PWM_CONST_3)
  {
    /* [cover parentID={90A43527-EE46-4130-9E75-1D13403D589E}]
    Set timer T13 to start on period zero match of T12 timer [/cover] */
    Ccu6Kernel = (uint8)((PwmCcu6TimerPtr->TimerId) & PWM_CCU6_KERNEL_MSK);
    Mcal_SetBitAtomic (&(Pwm_17_GtmCcu6_Kernel[Ccu6Kernel]->TCTR2.U),\
                                     IFX_CCU6_TCTR2_T13TEC_OFF, 3, PWM_CONST_6);
    Mcal_SetBitAtomic(&(Pwm_17_GtmCcu6_Kernel[Ccu6Kernel]->TCTR2.U),\
                                     IFX_CCU6_TCTR2_T13TED_OFF, 2, PWM_CONST_1);
  }
  /* MISRA2012_RULE_2_2_JUSTIFICATION: Ccu6Kernel value is used in
  Mcal_SetBitAtomic macro hence no dead code. */
}
#if (PWM_17_GTMCCU6_INITCHECK_API == STD_ON)
/*******************************************************************************
** Syntax : static Std_ReturnType Pwm_lCcu6StartChannelsInitCheck             **
**                   (                                                        **
**                     const Pwm_17_GtmCcu6_ChannelType ChannelNumber,        **
**                     const uint8 CoreId                                     **
**                   )                                                        **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Non Reentrant                                            **
**                                                                            **
** Parameters (in):  ChannelNumber : Channel number                           **
**                   CoreId : Core Number                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     Std_ReturnType                                           **
**                                                                            **
** Description :     Function to verify the CCU6 initialization               **
** Traceability :    [cover parentID={380AA40B-3837-4688-8450-B637C95C717D}] **
**                   [/cover]                                                 **
*******************************************************************************/
static Std_ReturnType Pwm_lCcu6StartChannelsInitCheck
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
)
{
  const Mcu_17_Ccu6_TimerConfigType *PwmCcu6TimerPtr;
  Mcu_17_Ccu6_TimerConfigType LocalPwmCcu6TimerCfg;
  uint8 Ccu6Comparator;
  uint8 Ccu6Kernel;
  Std_ReturnType ErrorStatus;
  uint32 RegVal;
  /* MISRA2012_RULE_11_5_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Ccu6_TimerConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  /* MISRA2012_RULE_11_3_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Ccu6_TimerConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  /* [cover parentID={0603BDA4-8FA3-4329-9733-4389A84AAF63}]
  Extract CCU6 timer configuration and comparator [/cover] */
  PwmCcu6TimerPtr = (const Mcu_17_Ccu6_TimerConfigType*)\
                    Pwm_ConfigPtr->PwmCoreAdd[CoreId]->Pwm_ChannelConfigPtr\
                    [ChannelNumber].PwmTimerPtr;
  Ccu6Comparator = (uint8)((PwmCcu6TimerPtr->TimerId >> \
                            PWM_CCU6_COMPARATOR_POS)& PWM_CCU6_COMPARATOR_MSK);

  /* [cover parentID={6EB7E407-A991-4701-A605-B9FCCBCD4219}]
  Clear notification at initialization [/cover] */
  /* [cover parentID={8622C91A-C8A7-4623-929B-268A6DA5681A}]
  Check CCU6 timer init status [/cover] */
  LocalPwmCcu6TimerCfg.TimerId = PwmCcu6TimerPtr->TimerId;
  LocalPwmCcu6TimerCfg.TimerCtrlReg0 = PwmCcu6TimerPtr->TimerCtrlReg0;
  LocalPwmCcu6TimerCfg.ModCtrlReg = PwmCcu6TimerPtr->ModCtrlReg;
  LocalPwmCcu6TimerCfg.PasStateLvlReg = PwmCcu6TimerPtr->PasStateLvlReg;
  LocalPwmCcu6TimerCfg.TimerCntReg = PwmCcu6TimerPtr->TimerCntReg;
  LocalPwmCcu6TimerCfg.TimerPeriodReg = PwmCcu6TimerPtr->TimerPeriodReg;
  LocalPwmCcu6TimerCfg.Ccu6ShadowReg = PwmCcu6TimerPtr->Ccu6ShadowReg;
  LocalPwmCcu6TimerCfg.TimerModeSelectReg = PwmCcu6TimerPtr->TimerModeSelectReg;
  LocalPwmCcu6TimerCfg.PortInSelReg0 = PwmCcu6TimerPtr->PortInSelReg0;
  LocalPwmCcu6TimerCfg.IntEnReg = PwmCcu6TimerPtr->IntEnReg;
  LocalPwmCcu6TimerCfg.IntNodePointerReg = PwmCcu6TimerPtr->IntNodePointerReg;
  /* [cover parentID={4BC6D644-0271-4c7d-8DCA-5C3560734828}] [/cover] */
  if((LocalPwmCcu6TimerCfg.TimerPeriodReg != 0U) && \
    (LocalPwmCcu6TimerCfg.TimerPeriodReg == LocalPwmCcu6TimerCfg.Ccu6ShadowReg))
  {
    LocalPwmCcu6TimerCfg.Ccu6ShadowReg = PWM_MAX_TIMER_CCU6;
  }
  /* [cover parentID={7E753AD3-DC86-4b9c-8CD1-EEA22ED798C2}] [/cover] */
  if(LocalPwmCcu6TimerCfg.TimerPeriodReg > 1U)
  {
    LocalPwmCcu6TimerCfg.TimerPeriodReg = \
                                      LocalPwmCcu6TimerCfg.TimerPeriodReg - 1U;
  }
  /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of variable LocalPwmCcu6TimerCfg
  is used inside Mcu_17_Ccu6_TimerInitCheck() to read the values only.
  The address is not used beyond the context of the API, hence it is not an
  issue. */
  ErrorStatus = Mcu_17_Ccu6_TimerInitCheck(&LocalPwmCcu6TimerCfg);
  /* [cover parentID={490BE727-C668-4831-8A11-6832C158B857}]
  Is CCU6 timer init status is OK [/cover] */
  if(ErrorStatus == E_OK)
  {
    /* [cover parentID={20ADEFA1-EB37-41a8-8086-2255B877791B}]
    Is comparator is CC63 [/cover] */
    if(Ccu6Comparator == PWM_CONST_3)
    {
      Ccu6Kernel = (uint8)((PwmCcu6TimerPtr->TimerId) & PWM_CCU6_KERNEL_MSK);
      RegVal = Pwm_17_GtmCcu6_Kernel[Ccu6Kernel]->TCTR2.U;
      RegVal = (uint32)((RegVal >> IFX_CCU6_TCTR2_T13TEC_OFF) & PWM_CONST_7);
      /* [cover parentID={29625C23-82C7-4366-837B-4DDFCF939671}]
      If T13 register is not set upon a zero-match of T12 [/cover] */
      if(RegVal != PWM_CONST_6)
      {
        /* [cover parentID={BCCDC230-B5ED-466e-B0F5-7A462B0CC642}]
        Set error status to E_NOT_OK [/cover] */
        ErrorStatus = E_NOT_OK;
      }
      RegVal = Pwm_17_GtmCcu6_Kernel[Ccu6Kernel]->TCTR2.U;
      RegVal = (uint32)((RegVal >> IFX_CCU6_TCTR2_T13TED_OFF) & PWM_CONST_3);
      /* [cover parentID={90E6BDA8-CFD6-4665-8A5C-7B045CAFE1CE}]
      If timer T13 trigger event direction is not independent on the count
      direction of T12 [/cover] */
      if(RegVal != PWM_CONST_1)
      {
        /* [cover parentID={48F08748-98F0-4e4c-B382-CD667CC889EF}]
        Set error status to E_NOT_OK [/cover] */
        ErrorStatus = E_NOT_OK;
      }
    }
  }
  return ErrorStatus;
}
#endif
#endif /* End of PWM_17_GTMCCU6_CCU6_TIMER_USED */
#if (PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
/******************************************************************************
** Syntax :  LOCAL_INLINE uint8 Pwm_lCoherency(                              **
**                    (                                                      **
**                      const uint16 Value                                   **
**                    )                                                      **
** Service ID:        none                                                   **
**                                                                           **
** Sync/Async:        Synchronous                                            **
**                                                                           **
** Reentrancy:        Reentrant                                              **
**                                                                           **
** Parameters (in):   Value : PwmChannelInfo                                 **
**                                                                           **
** Parameters (out):  none                                                   **
**                                                                           **
** Return value:      Returns Coherent or Non Coherent                       **
**                                                                           **
** Description :      Function to obtain the Coherency from PwmChannelInfo   **
**                                                                           **
** Traceability :     [cover parentID={D8C608B6-E263-4b29-A70B-BBA28AB3F53A}]**
**                   [/cover]                                                **
*******************************************************************************/
LOCAL_INLINE uint8 Pwm_lCoherency(const uint16 Value)
{
  uint8 RetVal;
  RetVal = (Pwm_17_GtmCcu6_OutputStateType) \
           ( ((uint16)(Value) >> PWM_COHERENCY_POS) & (PWM_COHERENCY_MASK) );
  return(RetVal);
}
#endif
#if((PWM_17_GTMCCU6_SET_PERIOD_AND_DUTY_API == STD_ON) || \
    (PWM_17_GTMCCU6_SET_DUTY_CYCLE_API == STD_ON) || \
    (PWM_17_GTMCCU6_SET_OUTPUT_TO_IDLE_API == STD_ON))
#if (PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
/******************************************************************************
** Syntax :           LOCAL_INLINE uint8 Pwm_lChanResetType                  **
**                    (                                                      **
**                      const uint16 Value                                   **
**                    )                                                      **
** Service ID:        none                                                   **
**                                                                           **
** Sync/Async:        Synchronous                                            **
**                                                                           **
** Reentrancy:        Reentrant                                              **
**                                                                           **
** Parameters (in):   Value : PWM channel information                        **
**                                                                           **
** Parameters (out):  none                                                   **
**                                                                           **
** Return value:      0 - Channel is non-reset type                          **
**                    1 - Channel is reset type                              **
** Description :      Function to get the reset type of channel              **
** Traceability :     [cover parentID={E5D588DA-9B76-4322-9B1B-D589F664CD3C}]**
**                   [/cover]                                                **
******************************************************************************/
LOCAL_INLINE uint8 Pwm_lChanResetType(const uint16 Value)
{
  uint8 RetVal;

  RetVal = (uint8) \
           (((uint16)(Value) >> PWM_RSTSHFT_POS) & (PWM_RSTSHFTSTATE_MASK));
  return(RetVal);
}
#endif
#endif
#if((PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON) || \
    (PWM_17_GTMCCU6_DEV_ERROR_DETECT == STD_ON))
#if((PWM_17_GTMCCU6_SET_DUTY_CYCLE_API == STD_ON) || \
    (PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON) || \
    (PWM_17_GTMCCU6_SET_OUTPUT_TO_IDLE_API == STD_ON) || \
    (PWM_17_GTMCCU6_GET_OUTPUT_STATE_API == STD_ON))
/******************************************************************************
** Syntax : static uint32 Pwm_lVerUnInitAndChannel                           **
**                    (                                                      **
**                      const uint8 ServiceID,                               **
**                      const Pwm_17_GtmCcu6_ChannelType ChannelNumber,      **
**                      const uint8 CoreId                                   **
**                    )                                                      **
** Service ID:        none                                                   **
**                                                                           **
** Sync/Async:        Synchronous                                            **
**                                                                           **
** Reentrancy:        Reentrant                                              **
**                                                                           **
** Parameters (in):   Service ID    : Service ID of an API                   **
**                    ChannelNumber : PWM Channel number                     **
**                    CoreId : Core Number                                   **
**                                                                           **
** Parameters (out):  none                                                   **
**                                                                           **
** Return value:      PWM_ERROR_FOUND: DET or Safety error occurred          **
**                    0: No DET or No Safety error occurred                  **
** Description :      Function to detect DET or Safety error of Pwm module   **
**                    initialization and validity of passed channel number   **
**                                                                           **
** Traceability :     [cover parentID={7EE04E45-5802-4355-9349-F713383B27B3}]**
**                    [/cover]                                               **
******************************************************************************/
static uint32 Pwm_lVerUnInitAndChannel
(
  const uint8 ServiceID,
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
)
{
  uint32 ErrorFlag;
  /* [cover parentID={C48E825D-5B9E-49d0-83A2-8F9A856FB8A3}]
  Verify whether Init has been called [/cover] */
  ErrorFlag = Pwm_lVerUnInit(ServiceID, CoreId);
  /* [cover parentID={44C31D00-EF63-4cd6-9E16-0847531B8EED}]
  If no error found [/cover] */
  if (ErrorFlag != PWM_ERROR_FOUND)
  {
    /* [cover parentID={23FFB6FE-D086-45db-B268-B1CE367B76B8}]
    Verify whether Invalid channel number passed [/cover] */
    ErrorFlag = Pwm_lVerChannel(ServiceID, ChannelNumber, CoreId);
  }
  return ErrorFlag;
}
#endif

#if((PWM_17_GTMCCU6_SET_DUTY_CYCLE_API == STD_ON)|| \
   (PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON)|| \
   (PWM_17_GTMCCU6_SET_OUTPUT_TO_IDLE_API == STD_ON) || \
   (PWM_17_GTMCCU6_GET_OUTPUT_STATE_API == STD_ON) || \
   (PWM_17_GTMCCU6_DE_INIT_API == STD_ON) || \
   (PWM_17_GTMCCU6_SET_PERIOD_AND_DUTY_API == STD_ON))
/******************************************************************************
** Syntax : LOCAL_INLINE uint32 Pwm_lVerUnInit                               **
**                    (                                                      **
**                      const uint8 ServiceID                                **
**                      const uint8 CoreId                                   **
**                    )                                                      **
** Service ID:        none                                                   **
**                                                                           **
** Sync/Async:        Synchronous                                            **
**                                                                           **
** Reentrancy:        Reentrant                                              **
**                                                                           **
** Parameters (in):   Service ID : Service ID of an API                      **
**                    CoreId : Core Number                                   **
**                                                                           **
** Parameters (out):  none                                                   **
**                                                                           **
** Return value:      PWM_ERROR_FOUND: UnInit DET or Safety error occurred   **
**                    0: No UnInit DET or Safety error occurred              **
**                                                                           **
** Description :      Function to check DET or Safety whether PWM module is  **
**                    initialized or not                                     **
** Traceability :     [cover parentID={F370A330-B6D7-40fc-8F9E-78DD61AA0713}]**
**                   [/cover]                                                **
******************************************************************************/
static uint32 Pwm_lVerUnInit(const uint8 ServiceID, const uint8 CoreId)
{
  uint32 ErrorFlag;
  const Pwm_17_GtmCcu6_CoreStatusType *LocalCoreStatusPtr;
  ErrorFlag = (uint32)0;
  /* [cover parentID={A4B2BBF2-07ED-4dd5-8419-A4FAB501938F}]
  If PWM module is not initialized or not for the core [/cover] */
  LocalCoreStatusPtr = PwmCoreStatusPtr[CoreId];
  if(LocalCoreStatusPtr == NULL_PTR)
  {
    /* [cover parentID={C62F9091-C2B4-4ba6-873F-A6AB1251CB11}]
    Report UNINIT DET error [/cover] */
    Pwm_lReportError(ServiceID, PWM_17_GTMCCU6_E_UNINIT);
    ErrorFlag = PWM_ERROR_FOUND; /* Set Error Flag */
  }
  else if (LocalCoreStatusPtr->Pwm_CoreInitStatus != PWM_INITIALIZED)
  {
    /* [cover parentID={C62F9091-C2B4-4ba6-873F-A6AB1251CB11}]
    Report UNINIT DET error [/cover] */
    Pwm_lReportError(ServiceID, PWM_17_GTMCCU6_E_UNINIT);
    ErrorFlag = PWM_ERROR_FOUND; /* Set Error Flag */
  }
  else
  {
    /* Do Nothing*/
  }
  return ErrorFlag;
}
#endif

#if((PWM_17_GTMCCU6_SET_DUTY_CYCLE_API == STD_ON) || \
    (PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON) || \
    (PWM_17_GTMCCU6_SET_OUTPUT_TO_IDLE_API == STD_ON) || \
    (PWM_17_GTMCCU6_GET_OUTPUT_STATE_API == STD_ON) || \
    (PWM_17_GTMCCU6_SET_PERIOD_AND_DUTY_API == STD_ON))
/******************************************************************************
** Syntax : static uint32 Pwm_lVerChannel                                    **
**                    (                                                      **
**                      const uint8 ServiceID,                               **
**                      const Pwm_17_GtmCcu6_ChannelType ChannelNumber       **
**                      const uint8 CoreId                                   **
**                    )                                                      **
** Service ID:        none                                                   **
**                                                                           **
** Sync/Async:        Synchronous                                            **
**                                                                           **
** Reentrancy:        Reentrant                                              **
**                                                                           **
** Parameters (in):   Service ID    : Service ID of an API                   **
**                    ChannelNumber : PWM Channel number                     **
**                    CoreId : Core Number                                   **
**                                                                           **
** Parameters (out):  none                                                   **
**                                                                           **
** Return value:      PWM_ERROR_FOUND: DET or Safety error occurred          **
**                    0: No DET or No Safety error occurred                  **
**                                                                           **
** Description :      Function to check DET or Safety for validity of passed **
**                    channel number                                         **
**                                                                           **
** Traceability :     [cover parentID={A432BE80-F0FB-4329-AC36-27FCD2B046C9}]**
**                    [/cover]                                               **
******************************************************************************/
static uint32 Pwm_lVerChannel
(
  const uint8 ServiceID,
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
)
{
  uint32 ErrorFlag = (uint32)0U;
  
  #if ((PWM_17_GTMCCU6_MULTICORE_ERROR_DETECT == STD_ON) || \
      (PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON))
  const Pwm_17_GtmCcu6_ChannelConfigType *PwmChannelCfgPtr;
  uint8 PwmCoreChIdx;
  const Pwm_17_GtmCcu6_CoreConfigType *PwmCorePtr;
  #endif

  /* [cover parentID={245D0C73-B6B0-4f30-9C92-1A81AA57ABEB}]
  Verify whether valid channel number is passed or not [/cover] */
  if ( ChannelNumber >= PWM_17_GTMCCU6_MAX_CHANNELS)
  {
    /* [cover parentID={5B3A9EEB-1485-4e7c-9CE4-550F67F06F50}]
    Report to DET on Error [/cover] */
    Pwm_lReportError(ServiceID, PWM_17_GTMCCU6_E_PARAM_CHANNEL);
    ErrorFlag = PWM_ERROR_FOUND; /* Set Error Flag */
  }
  /* [cover parentID={4ACB613B-85A4-4243-BF07-BDF45332AF8B}]
  If no error found [/cover] */
  if(ErrorFlag != PWM_ERROR_FOUND)
  {
    #if ((PWM_17_GTMCCU6_MULTICORE_ERROR_DETECT == STD_ON) || \
        (PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON))
    PwmCorePtr = Pwm_ConfigPtr->PwmCoreAdd[CoreId];
    PwmCoreChIdx = Pwm_ConfigPtr->PwmChannelIdxmapPtr[ChannelNumber];
    PwmChannelCfgPtr = &(PwmCorePtr->Pwm_ChannelConfigPtr[PwmCoreChIdx]);
    /* [cover parentID={1B26B841-2483-466b-88A7-5AC1C31B8B98}]
    If channel index is invalid or given channel number is not configured
    channel number [/cover] */
    if ((PwmCoreChIdx >= PwmCorePtr->MaxChannels) || \
          (PwmChannelCfgPtr->PwmChanneId != ChannelNumber))
    {
      /* Report DET when ChannelId not allocated to this core */
      Pwm_lReportMulticoreError(
        ServiceID,
        PWM_17_GTMCCU6_E_CORE_CHANNEL_MISMATCH);
      ErrorFlag = PWM_ERROR_FOUND; /* Set Error Flag */
    }
    #else
    UNUSED_PARAMETER(CoreId);
    #endif
  }
  return ErrorFlag;
}
#endif
#endif/*End of PWM_17_GTMCCU6_SAFETY_ENABLE or PWM_17_GTMCCU6_DEV_ERROR_DETECT*/

#if (PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON)
#if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
/*******************************************************************************
** Syntax :static void Pwm_lGtmIrqModify                                      **
**                   (                                                        **
**                     const Pwm_17_GtmCcu6_ChannelType ChannelNumber         **
**                     const uint8 InterruptFlag,                             **
**                     const uint8 CoreId                                     **
**                   )                                                        **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant                                                **
**                                                                            **
** Parameters (in):  ChannelNumber- PWM Channel Number                        **
**                   InterruptFlag - Interrupt bit to set or reset            **
**                   CoreId : Core number                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     Function to Enable or Disable TOM or ATOM Interrupt      **
**                                                                            **
** Traceability :     [cover parentID={5CDE22F5-9F62-42a1-9A3E-9CFFC77A5AFC}] **
**                    [/cover]                                                **
*******************************************************************************/
static void Pwm_lGtmIrqModify(const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
                              const uint8 InterruptFlag, const uint8 CoreId)
{
  Ifx_GTM_TOM_CH *TomChannelRegPtr;   /* Ptr to TOM Channel Register   */
  Ifx_GTM_ATOM_CH *AtomChannelRegPtr; /* Ptr to ATOM Channel Register  */
  Mcu_17_Gtm_TimerOutType PwmGtmTimerType;
  uint8 TimerChannelNumber;
  uint8 TimerModuleNumber;
  const Pwm_17_GtmCcu6_CoreConfigType     *PwmCorePtr;
  const Mcu_17_Gtm_TomAtomChConfigType    *PwmGtmTimerPtr;

  PwmCorePtr = Pwm_ConfigPtr->PwmCoreAdd[CoreId];
  /* MISRA2012_RULE_11_5_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Ccu6_TimerConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  /* MISRA2012_RULE_11_3_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  PwmGtmTimerPtr = (const Mcu_17_Gtm_TomAtomChConfigType*)\
                   PwmCorePtr->Pwm_ChannelConfigPtr[ChannelNumber].PwmTimerPtr;
  TimerModuleNumber    = (uint8)((PwmGtmTimerPtr->TimerId & \
                                  GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);
  TimerChannelNumber   = (uint8)((PwmGtmTimerPtr->TimerId & \
                                  GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);
  PwmGtmTimerType         = PwmGtmTimerPtr->TimerType;

  if(PwmGtmTimerType == MCU_GTM_TIMER_TOM)
  {
    /* [cover parentID={ACE51596-1569-44bc-AE1B-D53B362D639A}]
    If timer type is TOM [/cover] */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
     * by violating this MISRA rule, as the pointer to the object type
     * it is getting cast into is a known type . */
    /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
     * by violating this MISRA rule. */
    TomChannelRegPtr = \
                  PWM_GTM_TOM_CH_POINTER(TimerModuleNumber, TimerChannelNumber);
    /* [cover parentID={E80EAA0D-80A0-4f59-BBD5-BCAD0D3CCCCF}]
    Clear all pending interrupts [/cover] */
    /* [cover parentID={3EB0C005-540F-48f1-8C91-7BEF013D1972}]
    Clear all Pending Interrupts [/cover] */
    TomChannelRegPtr->IRQ.NOTIFY.U = PWM_CLR_PENDING_INTERRUPTS;
    TomChannelRegPtr->IRQ.EN.U = InterruptFlag;
  }
  else
  {
    /* [cover parentID={3EB0C005-540F-48f1-8C91-7BEF013D1972}]
    Clear all Pending Interrupts and Enable/Disable Interrupts [/cover] */
    /* [cover parentID={B08A4459-FC11-4a8c-9AF3-9701EB4877AA}]
    If timer type is ATOM [/cover] */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
     * by violating this MISRA rule, as the pointer to the object type
     * it is getting cast into is a known type . */
    /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
     * by violating this MISRA rule. */
    AtomChannelRegPtr = \
                PWM_GTM_ATOM_CH_POINTER(TimerModuleNumber, TimerChannelNumber);
    /* Clear all Pending Interrupts */
    AtomChannelRegPtr->IRQ.NOTIFY.U = PWM_CLR_PENDING_INTERRUPTS;
    AtomChannelRegPtr->IRQ.EN.U = InterruptFlag;
  }
}
#endif
#endif

#if( (PWM_17_GTMCCU6_DE_INIT_API == STD_ON) || \
    (PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON) )
#if (PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
/*******************************************************************************
** Syntax :static void Pwm_lCcu6IrqModify                                     **
**                   (                                                        **
**                     const Pwm_17_GtmCcu6_ChannelType ChannelNumber         **
**                     const uint8 InterruptFlag                              **
**                     const uint8 CoreId                                     **
**                   )                                                        **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant                                                **
**                                                                            **
** Parameters (in):  ChannelNumber- logical Channel Number                    **
**                   InterruptFlag - Interrupt bits to set or reset           **
**                   CoreId : Core Number                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     Function to Enable or Disable CCU0 or CCU1 Interrupt     **
** Traceability :     [cover parentID={07E5B47C-0437-442e-9ACF-D8D8C17D890E}] **
**                   [/cover]                                                 **
******************************************************************************/
static void Pwm_lCcu6IrqModify(const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
                               const uint8 InterruptFlag, const uint8 CoreId)
{
  const Mcu_17_Ccu6_TimerConfigType *PwmCcu6TimerPtr;
  const Pwm_17_GtmCcu6_ChannelConfigType  *LocalPwmChanPtr;
  Pwm_17_GtmCcu6_ChannelStatusType        *LocalChannelStatusPtr;
  const Pwm_17_GtmCcu6_CoreStatusType     *LocalCoreStatusPtr;
  Mcu_17_Ccu6_TimerChIdentifierType Ccu6TimerId;
  Mcu_17_Ccu6_TimerChIntType Ccu6IntConfig;
  uint32 InterruptVal;
  uint8 Ccu6Timer;
  uint8 Ccu6Comparator;
  uint8 BitPos;
  uint8 Polarity;
  uint8 Ccu6Kernel;
  uint32 Ccu6NotifStatus;
  /* MISRA2012_RULE_11_5_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Ccu6_TimerConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  /* MISRA2012_RULE_11_3_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  PwmCcu6TimerPtr = (const Mcu_17_Ccu6_TimerConfigType*)\
                    Pwm_ConfigPtr->PwmCoreAdd[CoreId]->Pwm_ChannelConfigPtr\
                    [ChannelNumber].PwmTimerPtr;
  LocalPwmChanPtr = &(Pwm_ConfigPtr->PwmCoreAdd\
                      [CoreId]->Pwm_ChannelConfigPtr[ChannelNumber]);
  LocalChannelStatusPtr = Pwm_CoreChannelStatus[CoreId];
  LocalChannelStatusPtr = &(LocalChannelStatusPtr[ChannelNumber]);
  LocalCoreStatusPtr = PwmCoreStatusPtr[CoreId];

  Polarity = PWM_GET_POLARITY(LocalPwmChanPtr->PwmChannelInfo);
  Ccu6TimerId =  PwmCcu6TimerPtr->TimerId;
  Ccu6Kernel = (uint8)((PwmCcu6TimerPtr->TimerId) & PWM_CCU6_KERNEL_MSK);
  Ccu6Timer = (uint8)((PwmCcu6TimerPtr->TimerId >> PWM_CCU6_TIMER_POS)\
                      & PWM_CCU6_TIMER_MSK);
  Ccu6Comparator = (uint8)((PwmCcu6TimerPtr->TimerId >> \
                            PWM_CCU6_COMPARATOR_POS)& PWM_CCU6_COMPARATOR_MSK);
  Ccu6IntConfig.TimerId = Ccu6TimerId;
  Ccu6IntConfig.IEnLen = PWM_CONST_1;
  /* [cover parentID={27C76A9C-607E-4715-BC43-E1761F0E7F4F}]
  If timer type is T12 [/cover] */
  if(Ccu6Timer == MCU_CCU6_TIMER_T12)
  {
    BitPos = PWM_CONST_2 * Ccu6Comparator;
    InterruptVal = ((uint32)((uint32)1 << IFX_CCU6_ISR_RT12PM_OFF) | \
                    (uint32)((uint32)1 << BitPos));
    Pwm_17_GtmCcu6_Kernel[Ccu6Kernel]->ISR.U = \
        (InterruptVal);
    /* [cover parentID={7BCD0C5A-C1A1-4b85-864A-B708257BCA75}]
    If polarity is low [/cover] */
    if (Polarity == PWM_17_GTMCCU6_LOW)
    {
      /* [cover parentID={88E073D6-10CC-432b-ADDE-5E3E760B2D0F}]
      If interrupt set for falling edge [/cover] */
      if((InterruptFlag & PWM_CONST_1) == PWM_CONST_1)
      {
        /* Enable Falling Edge  T12PM */
        Ccu6IntConfig.IEnBitPos = PWM_CONST_7;
        Ccu6IntConfig.RegVal = PWM_CONST_1;
        Ccu6NotifStatus = ((uint32)PWM_CONST_4 << PWM_CCU6_NOTIFI_STATUS_POS);
        LocalChannelStatusPtr->Pwm_GlobChn |= Ccu6NotifStatus;
        Mcal_SetBitAtomic\
        (&(LocalCoreStatusPtr->Pwm_CCU6PMStatus[Ccu6Kernel]),Ccu6Comparator,1, \
         PWM_CONST_1);
        /* [cover parentID={7FF6DCC9-C44E-4d36-9915-6DD5120D8400}]
        Enable falling edge [/cover] */
        /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of variable Ccu6IntConfig
          is used inside Mcu_17_Ccu6_TimerIntEnDis() to read the values only.
          The address is not used beyond the context of the API, hence it is not an
          issue. */
        Mcu_17_Ccu6_TimerIntEnDis(&Ccu6IntConfig);
      }
      else
      {
        /* Disable Falling Edge T12PM */
        Ccu6IntConfig.IEnBitPos = PWM_CONST_7;
        Ccu6IntConfig.RegVal = 0U;
        Ccu6NotifStatus = (~((uint32)PWM_CONST_4 << PWM_CCU6_NOTIFI_STATUS_POS));
        LocalChannelStatusPtr->Pwm_GlobChn &= Ccu6NotifStatus;
        Mcal_SetBitAtomic\
       (&(LocalCoreStatusPtr->Pwm_CCU6PMStatus[Ccu6Kernel]),Ccu6Comparator,1,0);

        /* [cover parentID={FBE6BBAE-8786-484d-A9AF-70AB54EC52DD}][/cover] */
        if(LocalCoreStatusPtr->Pwm_CCU6PMStatus[Ccu6Kernel] == 0U)
        {
          /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of variable Ccu6IntConfig
          is used inside Mcu_17_Ccu6_TimerIntEnDis() to read the values only.
          The address is not used beyond the context of the API, hence it is not an
          issue. */
          /* [cover parentID={1F11821F-8FA5-4681-96EE-B871E36D432B}]
          Disable falling edge [/cover] */
          Mcu_17_Ccu6_TimerIntEnDis(&Ccu6IntConfig);
        }
      }
      /* [cover parentID={6F778A38-C721-42bd-AF59-5336067D7F39}]
      If interrupt set for rising edge [/cover] */
      if((InterruptFlag & PWM_CONST_2) == PWM_CONST_2)
      {
        /* Enable Rising Edge  ENCC6xR */
        Ccu6IntConfig.IEnBitPos = BitPos;
        Ccu6IntConfig.RegVal = PWM_CONST_1;
        Ccu6NotifStatus = ((uint32)PWM_CONST_1 << \
                           PWM_CCU6_NOTIFI_STATUS_POS);
        LocalChannelStatusPtr->Pwm_GlobChn |= Ccu6NotifStatus;
        /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of variable Ccu6IntConfig
        is used inside Mcu_17_Ccu6_TimerIntEnDis() to read the values only.
        The address is not used beyond the context of the API, hence it is not an
        issue. */
        /* [cover parentID={AB7BF96B-D192-41c9-B714-6E2281ABC68F}]
        Enable Rising edge [/cover] */
        Mcu_17_Ccu6_TimerIntEnDis(&Ccu6IntConfig);
      }
      else
      {
        /* Disable Rising Edge ENCC6xR */
        Ccu6IntConfig.IEnBitPos = BitPos;
        Ccu6IntConfig.RegVal = 0U;
        Ccu6NotifStatus = (~((uint32)PWM_CONST_1 << \
                             PWM_CCU6_NOTIFI_STATUS_POS));
        LocalChannelStatusPtr->Pwm_GlobChn &= Ccu6NotifStatus;
        /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of variable Ccu6IntConfig
        is used inside Mcu_17_Ccu6_TimerIntEnDis() to read the values only.
        The address is not used beyond the context of the API, hence it is not an
        issue. */
        /* [cover parentID={C4BE97ED-5350-4a08-8591-E39A94A1A972}]
        Disable Rising edge [/cover] */
        Mcu_17_Ccu6_TimerIntEnDis(&Ccu6IntConfig);
      }
    }
    else
    {
      /* [cover parentID={DA233A3B-6787-475b-9484-C45030DF6AAE}]
      If interrupt set for Rising edge [/cover] */
      if((InterruptFlag & PWM_CONST_1) == PWM_CONST_1)
      {
        /* Enable Rising Edge  T12PM */
        Ccu6IntConfig.IEnBitPos = PWM_CONST_7;
        Ccu6IntConfig.RegVal = PWM_CONST_1;
        Ccu6NotifStatus = ((uint32)PWM_CONST_4 << PWM_CCU6_NOTIFI_STATUS_POS);
        LocalChannelStatusPtr->Pwm_GlobChn |= Ccu6NotifStatus;
        Mcal_SetBitAtomic\
        (&(LocalCoreStatusPtr->Pwm_CCU6PMStatus[Ccu6Kernel]),Ccu6Comparator,1, \
         PWM_CONST_1);
        /* [cover parentID={8B3195D4-0CCA-4aec-A76F-9E112E7E4F00}]
        Enable Rising edge [/cover] */
        /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of variable Ccu6IntConfig
        is used inside Mcu_17_Ccu6_TimerIntEnDis() to read the values only.
        The address is not used beyond the context of the API, hence it is not an
        issue. */
        Mcu_17_Ccu6_TimerIntEnDis(&Ccu6IntConfig);
      }
      else
      {
        /* Disable Rising Edge T12PM */
        Ccu6IntConfig.IEnBitPos = PWM_CONST_7;
        Ccu6IntConfig.RegVal = 0U;
        Ccu6NotifStatus = (~((uint32)PWM_CONST_4 << PWM_CCU6_NOTIFI_STATUS_POS));
        LocalChannelStatusPtr->Pwm_GlobChn &= Ccu6NotifStatus;
        Mcal_SetBitAtomic\
       (&(LocalCoreStatusPtr->Pwm_CCU6PMStatus[Ccu6Kernel]),Ccu6Comparator,1,0);
        if(LocalCoreStatusPtr->Pwm_CCU6PMStatus[Ccu6Kernel] == 0U)
        {
          /* [cover parentID={94F6DF7E-0FB2-4e81-9F9E-79D9C569B11A}]
          Disable Rising edge [/cover] */
          /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of variable Ccu6IntConfig
          is used inside Mcu_17_Ccu6_TimerIntEnDis() to read the values only.
          The address is not used beyond the context of the API, hence it is not an
          issue. */
          Mcu_17_Ccu6_TimerIntEnDis(&Ccu6IntConfig);
        }
      }
      /* [cover parentID={FC36C216-55FB-490c-AF59-4C5CD1ECDA74}]
      If interrupt set for Falling edge [/cover] */
      if((InterruptFlag & PWM_CONST_2) == PWM_CONST_2)
      {
        /* Enable Falling Edge  ENCC6xR */
        Ccu6IntConfig.IEnBitPos = BitPos;
        Ccu6IntConfig.RegVal = PWM_CONST_1;
        Ccu6NotifStatus = ((uint32)PWM_CONST_1 << PWM_CCU6_NOTIFI_STATUS_POS);
        LocalChannelStatusPtr->Pwm_GlobChn |= Ccu6NotifStatus;
        /* [cover parentID={81DE3743-1264-4d83-8827-A60F464420B9}]
        Enable falling edge [/cover] */

        /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of variable Ccu6IntConfig
        is used inside Mcu_17_Ccu6_TimerIntEnDis() to read the values only.
        The address is not used beyond the context of the API, hence it is not an
        issue. */
        Mcu_17_Ccu6_TimerIntEnDis(&Ccu6IntConfig);
      }
      else
      {
        /* Disable Falling Edge ENCC6xR */
        Ccu6IntConfig.IEnBitPos = BitPos;
        Ccu6IntConfig.RegVal = 0U;
        Ccu6NotifStatus = (~((uint32)PWM_CONST_1 << PWM_CCU6_NOTIFI_STATUS_POS));
        LocalChannelStatusPtr->Pwm_GlobChn &= Ccu6NotifStatus;
        /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of variable Ccu6IntConfig
        is used inside Mcu_17_Ccu6_TimerIntEnDis() to read the values only.
        The address is not used beyond the context of the API, hence it is not an
        issue. */
        /* [cover parentID={AAD2DEA6-ABA9-4b17-A58C-EF33F77F711A}]
        Disable falling edge [/cover] */
        Mcu_17_Ccu6_TimerIntEnDis(&Ccu6IntConfig);
      }
    }
  }
  else
  {
    InterruptVal = ((uint32)((uint32)1 << IFX_CCU6_ISR_RT13PM_OFF) | \
                    (uint32)((uint32)1 << IFX_CCU6_ISR_RT13CM_OFF));
    Pwm_17_GtmCcu6_Kernel[Ccu6Kernel]->ISR.U = \
        (InterruptVal);
    /* [cover parentID={32C8DEA1-BBB9-4607-82C1-361EACCA4A65}]
    If polarity is low [/cover] */
    if (Polarity == PWM_17_GTMCCU6_LOW)
    {
      /* [cover parentID={24C1DFB0-4247-4975-B361-AF0A48FFE31C}]
      If interrupt set for falling edge [/cover] */
      if((InterruptFlag & PWM_CONST_1) == PWM_CONST_1)
      {
        /* Enable Falling Edge  T13PM */
        Ccu6IntConfig.IEnBitPos = PWM_CONST_9;
        Ccu6IntConfig.RegVal = PWM_CONST_1;
        Ccu6NotifStatus = ((uint32)PWM_CONST_16 << PWM_CCU6_NOTIFI_STATUS_POS);
        LocalChannelStatusPtr->Pwm_GlobChn |= Ccu6NotifStatus;
        /* [cover parentID={6B01FB62-34B2-4742-A6A5-EAB75B68716B}]
        Enable falling edge [/cover] */
        /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of variable Ccu6IntConfig
        is used inside Mcu_17_Ccu6_TimerIntEnDis() to read the values only.
        The address is not used beyond the context of the API, hence it is not an
        issue. */
        Mcu_17_Ccu6_TimerIntEnDis(&Ccu6IntConfig);
      }
      else
      {
        /* Disable Falling Edge  T13PM */
        Ccu6IntConfig.IEnBitPos = PWM_CONST_9;
        Ccu6IntConfig.RegVal = 0U;
        Ccu6NotifStatus = (~((uint32)PWM_CONST_16 << PWM_CCU6_NOTIFI_STATUS_POS));
        LocalChannelStatusPtr->Pwm_GlobChn &= Ccu6NotifStatus;
        /* [cover parentID={1DF8FFC5-9BCA-44fa-901E-10E69475D9A6}]
        Disable falling edge [/cover] */
        /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of variable Ccu6IntConfig
        is used inside Mcu_17_Ccu6_TimerIntEnDis() to read the values only.
        The address is not used beyond the context of the API, hence it is not an
        issue. */
        Mcu_17_Ccu6_TimerIntEnDis(&Ccu6IntConfig);
      }
      /* configure Duty interrupt*/
      /* [cover parentID={2E8305E9-103C-4729-9E7B-4EEA29B3A904}]
      If interrupt set for rising edge [/cover] */
      if((InterruptFlag & PWM_CONST_2) == PWM_CONST_2)
      {
        /* Enable Rising Edge  T13CM */
        Ccu6IntConfig.IEnBitPos = PWM_CONST_8;
        Ccu6IntConfig.RegVal = PWM_CONST_1;
        Ccu6NotifStatus = ((uint32)PWM_CONST_8 << PWM_CCU6_NOTIFI_STATUS_POS);
        LocalChannelStatusPtr->Pwm_GlobChn |= Ccu6NotifStatus;
        /* [cover parentID={281B1E6F-3840-43ba-9C7E-57DF3D76763A}]
        Enable Rising edge [/cover] */
        /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of variable Ccu6IntConfig
        is used inside Mcu_17_Ccu6_TimerIntEnDis() to read the values only.
        The address is not used beyond the context of the API, hence it is not an
        issue. */
        Mcu_17_Ccu6_TimerIntEnDis(&Ccu6IntConfig);
      }
      else
      {
        /* Disable Rising Edge  T13CM */
        Ccu6IntConfig.IEnBitPos = PWM_CONST_8;
        Ccu6IntConfig.RegVal = 0U;
        Ccu6NotifStatus=(~((uint32)PWM_CONST_8 << PWM_CCU6_NOTIFI_STATUS_POS));
        LocalChannelStatusPtr->Pwm_GlobChn &= Ccu6NotifStatus;
        /* [cover parentID={D253F052-2850-4c0e-A3CE-66B7CACD9387}]
        Disable Rising edge [/cover] */
        /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of variable Ccu6IntConfig
        is used inside Mcu_17_Ccu6_TimerIntEnDis() to read the values only.
        The address is not used beyond the context of the API, hence it is not an
        issue. */
        Mcu_17_Ccu6_TimerIntEnDis(&Ccu6IntConfig);
      }
    }
    else
    {
      /* [cover parentID={50D5CFD4-9ECC-4417-89AB-5C7921341F79}]
      If interrupt set for falling edge [/cover] */
      if((InterruptFlag & PWM_CONST_1) == PWM_CONST_1)
      {
        /* Enable falling Edge  T13PM */
        Ccu6IntConfig.IEnBitPos = PWM_CONST_9;
        Ccu6IntConfig.RegVal = PWM_CONST_1;
        Ccu6NotifStatus = ((uint32)PWM_CONST_16 << PWM_CCU6_NOTIFI_STATUS_POS);
        LocalChannelStatusPtr->Pwm_GlobChn |= Ccu6NotifStatus;
        /* [cover parentID={0DD70F01-FA6D-4db7-A085-2B75A71E22C0}]
        Enable Rising edge [/cover] */
        /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of variable Ccu6IntConfig
        is used inside Mcu_17_Ccu6_TimerIntEnDis() to read the values only.
        The address is not used beyond the context of the API, hence it is not an
        issue. */
        Mcu_17_Ccu6_TimerIntEnDis(&Ccu6IntConfig);
      }
      else
      {
        /* Disable falling Edge  T13PM */
        Ccu6IntConfig.IEnBitPos = PWM_CONST_9;
        Ccu6IntConfig.RegVal = 0U;
        Ccu6NotifStatus = (~((uint32)PWM_CONST_16 << PWM_CCU6_NOTIFI_STATUS_POS));
        LocalChannelStatusPtr->Pwm_GlobChn &= Ccu6NotifStatus;
        /* [cover parentID={D291B797-B2B2-40e0-B608-CA59F67C5727}]
        Disable Rising edge [/cover] */
        /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of variable Ccu6IntConfig
        is used inside Mcu_17_Ccu6_TimerIntEnDis() to read the values only.
        The address is not used beyond the context of the API, hence it is not an
        issue. */
        Mcu_17_Ccu6_TimerIntEnDis(&Ccu6IntConfig);
      }
      /* [cover parentID={6CA38BA8-FE14-421e-81A1-EB505B20D511}]
      If interrupt set for rising edge [/cover] */
      if((InterruptFlag & PWM_CONST_2) == PWM_CONST_2)
      {
        /* Enable Falling Edge  T13CM */
        Ccu6IntConfig.IEnBitPos = PWM_CONST_8;
        Ccu6IntConfig.RegVal = PWM_CONST_1;
        Ccu6NotifStatus = ((uint32)PWM_CONST_8 << PWM_CCU6_NOTIFI_STATUS_POS);
        LocalChannelStatusPtr->Pwm_GlobChn |= Ccu6NotifStatus;
        /* [cover parentID={092C5E81-88AF-4896-9B35-38FF3F4D3634}]
        Enable falling edge [/cover] */
        /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of variable Ccu6IntConfig
        is used inside Mcu_17_Ccu6_TimerIntEnDis() to read the values only.
        The address is not used beyond the context of the API, hence it is not an
        issue. */
        Mcu_17_Ccu6_TimerIntEnDis(&Ccu6IntConfig);
      }
      else
      {
        /* Disable Falling Edge  T13CM */
        Ccu6IntConfig.IEnBitPos = PWM_CONST_8;
        Ccu6IntConfig.RegVal = 0U;
        Ccu6NotifStatus = (~((uint32)PWM_CONST_8 << PWM_CCU6_NOTIFI_STATUS_POS));
        LocalChannelStatusPtr->Pwm_GlobChn &= Ccu6NotifStatus;
        /* [cover parentID={2E747E32-35E2-4edd-9889-78C9A425DD1C}]
        Disable falling edge [/cover] */
        /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of variable Ccu6IntConfig
        is used inside Mcu_17_Ccu6_TimerIntEnDis() to read the values only.
        The address is not used beyond the context of the API, hence it is not an
        issue. */
        Mcu_17_Ccu6_TimerIntEnDis(&Ccu6IntConfig);
      }
    }
  }
}
#endif
#endif

#if((PWM_17_GTMCCU6_DE_INIT_API == STD_ON) || \
    (PWM_17_GTMCCU6_SET_OUTPUT_TO_IDLE_API == STD_ON))
/******************************************************************************
** Syntax :           LOCAL_INLINE Pwm_17_GtmCcu6_OutputStateType Pwm_lIdle  **
**                    (                                                      **
**                      const uint16 Value                                   **
**                    )                                                      **
** Service ID:        none                                                   **
**                                                                           **
** Sync/Async:        Synchronous                                            **
**                                                                           **
** Reentrancy:        Reentrant                                              **
**                                                                           **
** Parameters (in):   Value : PwmChannelInfo                                 **
**                                                                           **
** Parameters (out):  none                                                   **
**                                                                           **
** Return value:      Pwm_17_GtmCcu6_OutputStateType                         **
**                                                                           **
** Description :      Function to obtain the Idle state from PwmChannelInfo  **
**                                                                           **
** Traceability :     [cover parentID={E7F0DC98-905D-48cc-BA2A-4AA99E41D4CB}]**
**                   [/cover]                                                **
******************************************************************************/
LOCAL_INLINE Pwm_17_GtmCcu6_OutputStateType Pwm_lIdle(const uint16 Value)
{
  Pwm_17_GtmCcu6_OutputStateType RetVal;

  RetVal = (Pwm_17_GtmCcu6_OutputStateType)\
           (((uint16)(Value) >> PWM_IDLESTATE_POS) & (PWM_IDLESTATE_MASK));
  return(RetVal);
}
#endif

#if (PWM_17_GTMCCU6_DE_INIT_API == STD_ON)
#if (PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
/******************************************************************************
** Syntax : static void Pwm_lTomDeInit                                       **
**                  (                                                        **
**                    const uint8 TimerModuleNumber,                         **
**                    const uint8 TimerChannelNumber,                        **
                      const Pwm_17_GtmCcu6_OutputStateType IdleState         **
**                  )                                                        **
** Service ID:      none                                                     **
**                                                                           **
** Sync/Async:      Synchronous                                              **
**                                                                           **
** Reentrancy:      Non Reentrant                                            **
**                                                                           **
** Parameters (in): TimerModuleNumber : TOM module number                    **
**                  TimerChannelNumber: Channel Number                       **
**                  Idle State        : Idle State of the channel            **
** Parameters (out):none                                                     **
**                                                                           **
** Return value:    none                                                     **
**                                                                           **
** Description :    Service to disable TOM channel and change state to idle  **
** Traceability :     [cover parentID={F99583E2-329F-4eca-9A46-1F610338B4FA}]**
**                   [/cover]                                                **
******************************************************************************/
static void Pwm_lTomDeInit(const uint8 TimerModuleNumber, 
 const uint8 TimerChannelNumber, const Pwm_17_GtmCcu6_OutputStateType IdleState)
{
  Ifx_GTM_TOM_CH*  TomChannelRegPtr; /* Ptr to TOM Channel Reg */
  Pwm_17_GtmCcu6_OutputStateType LocalIdleState;

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TomChannelRegPtr = \
                  PWM_GTM_TOM_CH_POINTER(TimerModuleNumber, TimerChannelNumber);

  /* Set Channel State to IDLE Channel output is inverse of SL bit after
  channel is disabled */
  LocalIdleState = ((Pwm_17_GtmCcu6_OutputStateType)(~IdleState) & PWM_CONST_1);
  /* [cover parentID={8794E038-CABB-4f72-9521-B26EB565833B}]
  Set channel state to IDLE [/cover] */
  Mcal_SetBitAtomic\
  ((&TomChannelRegPtr->CTRL.U), \
   IFX_GTM_TOM_CH_CTRL_SL_OFF, 1, (uint32)LocalIdleState);
  
  /* Reset TOM CTRL FREEZE, TRIGOUT, CLK_SRC_SR and RST_CCU0 register bits */
  TomChannelRegPtr->CTRL.U &= PWM_TOM_CTRL_RST_MSK;

  /* [cover parentID={C720817F-43E7-4a9f-85C7-CE1771A4A090}]
  Update TOM channel status to DISABLE [/cover] */
  Mcu_17_Gtm_TomChEndisStatUpdate(TimerModuleNumber, TimerChannelNumber, \
                                  MCU_GTM_TIMER_DISABLE);
  /* [cover parentID={CFBEC3B7-9C9E-42a7-857A-23A29BB98784}]
  Disable TOM channel output status [/cover] */
  Mcu_17_Gtm_TomChOutEnStatUpdate(TimerModuleNumber, TimerChannelNumber, \
                                  MCU_GTM_TIMER_OUT_DISABLE);

  /* [cover parentID={9F4B9F02-EBDF-4a88-807D-9BCEC982AE43}]
  Disable Update Enable [/cover] */
  Mcu_17_Gtm_TomChUpdateEnDis(TimerModuleNumber, TimerChannelNumber, \
                              MCU_GTM_TIMER_UPDATE_DISABLE);
  
  /* [cover parentID={6B1F25B8-EBF5-4ae4-920A-18FF71A13F8F}]
  Clear all pending interrupts. Disable Interrupts [/cover] */
  TomChannelRegPtr->IRQ.NOTIFY.U = PWM_CLR_PENDING_INTERRUPTS;
  TomChannelRegPtr->IRQ.EN.U = 0;

  /* Reset CCU0 counter register */
  TomChannelRegPtr->CN0.U = PWM_TOM_SFR_RESET_VAL;

  /* [cover parentID={4C9161D1-58BE-40a5-99F1-D9F1B7586D80}]
    Enter critical section [/cover] */
  SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();

  /* Reset CCU0 and CCU1 compare registers */
  TomChannelRegPtr->CM0.U = PWM_TOM_SFR_RESET_VAL;
  TomChannelRegPtr->CM1.U = PWM_TOM_SFR_RESET_VAL;
  
  /* Reset CCU0 and CCU1 compare shadow registers */
  TomChannelRegPtr->SR0.U = PWM_TOM_SFR_RESET_VAL;
  TomChannelRegPtr->SR1.U = PWM_TOM_SFR_RESET_VAL;

  /* [cover parentID={BB8268CE-5CFE-45bc-A954-A064BD108D70}]
    Exit critical section [/cover] */
  SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
  
  /* Reset interrupt mode configuration register */
  TomChannelRegPtr->IRQ.MODE.U = PWM_TOM_SFR_RESET_VAL;
 
  /* MISRA2012_RULE_2_2_JUSTIFICATION: LocalIdleState value is used in
                                  Mcal_SetBitAtomic macro hence no dead code. */
  /* MISRA2012_RULE_2_2_JUSTIFICATION: TomChannelRegPtr value is used in
                                  Mcal_SetBitAtomic macro hence no dead code. */
}
/******************************************************************************
** Syntax : static void Pwm_lAtomDeInit                                      **
**                  (                                                        **
**                    const uint8 TimerModuleNumber,                         **
**                    const uint8 TimerChannelNumber,                        **
                      const Pwm_17_GtmCcu6_OutputStateType IdleState)        **
**                  )                                                        **
** Service ID:      None                                                     **
**                                                                           **
** Sync/Async:      Synchronous                                              **
**                                                                           **
** Reentrancy:      Non Reentrant                                            **
**                                                                           **
** Parameters (in): TimerModuleNumber : ATOM module number                   **
**                  TimerChannelNumber: ATOM Channel Number                  **
**                  Idle State        : Idle State of the channel            **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:    None                                                     **
**                                                                           **
** Description : Service to disable ATOM channel and change state to idle    **
**                                                                           **
** Traceability : [cover parentID={C2BD09A2-EEFC-450e-B9FA-0623552F2F54}]    **
**                 [/cover]                                                  **
******************************************************************************/
static void Pwm_lAtomDeInit(const uint8 TimerModuleNumber, 
 const uint8 TimerChannelNumber, const Pwm_17_GtmCcu6_OutputStateType IdleState)
{
  Ifx_GTM_ATOM_CH* AtomChannelRegPtr; /* Ptr to ATOM Channel Reg       */
  Pwm_17_GtmCcu6_OutputStateType LocalIdleState;

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  AtomChannelRegPtr = \
                 PWM_GTM_ATOM_CH_POINTER(TimerModuleNumber, TimerChannelNumber);

  /* Set Channel State to IDLE Channel output is inverse of SL bit after
  channel is disabled */
  LocalIdleState = ((Pwm_17_GtmCcu6_OutputStateType)(~IdleState) & PWM_CONST_1);
  /* [cover parentID={976C405E-C8EF-4eaa-8F78-12ECA3901321}]
  Set Channel State to IDLE [/cover] */
  Mcal_SetBitAtomic\
  ((&AtomChannelRegPtr->CTRL.U), \
   IFX_GTM_ATOM_CH_SOMI_SL_OFF, 1, (uint32)LocalIdleState);

  /* [cover parentID={AC1C3985-F76B-43d0-A5E2-5959F07978E1}]
  Update ATOM channel status to DISABLE [/cover] */
 /* Reset ATOM CTRL FREEZE,TRIGOUT,CLK_SRC_SR,MODE and RST_CCU0 register bits*/
  AtomChannelRegPtr->CTRL.U &= PWM_ATOM_CTRL_RST_MSK;

  Mcu_17_Gtm_AtomChEndisStatUpdate(TimerModuleNumber, TimerChannelNumber, \
                                   MCU_GTM_TIMER_DISABLE);
  /* [cover parentID={3F6A16FD-D333-4d1e-8A3C-F3A16C091439}]
  Disable ATOM channel output status [/cover] */
  Mcu_17_Gtm_AtomChOutEnStatUpdate(TimerModuleNumber, TimerChannelNumber, \
                                   MCU_GTM_TIMER_OUT_DISABLE);
  
  /* [cover parentID={647FC3B3-4067-4c39-9AA6-7C160C1B80CA}]
  Disable Update Enable [/cover] */
  Mcu_17_Gtm_AtomChUpdateEnDis(TimerModuleNumber, TimerChannelNumber, \
                               MCU_GTM_TIMER_UPDATE_DISABLE);
  /* [cover parentID={84FF27D6-7941-4ddd-AF68-83678AF47FCC}]
  Clear all pending interrupts. Disable Interrupts [/cover] */
  AtomChannelRegPtr->IRQ.NOTIFY.U = PWM_CLR_PENDING_INTERRUPTS;
  AtomChannelRegPtr->IRQ.EN.U = 0;

  /* Reset CCU0 counter register */
  AtomChannelRegPtr->CN0.U = PWM_ATOM_SFR_RESET_VAL;

 /* [cover parentID={148D77F0-DF2B-495f-AA5D-375423D41523}]
    Enter critical section [/cover] */
  SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
 
  /* Reset CCU0 and CCU1 compare registers */
  AtomChannelRegPtr->CM0.U = PWM_ATOM_SFR_RESET_VAL;
  AtomChannelRegPtr->CM1.U = PWM_ATOM_SFR_RESET_VAL;
  
  /* Reset CCU0 and CCU1 compare shadow registers */
  AtomChannelRegPtr->SR0.U = PWM_ATOM_SFR_RESET_VAL;
  AtomChannelRegPtr->SR1.U = PWM_ATOM_SFR_RESET_VAL;

 /* [cover parentID={25286B11-32E6-4ce8-9E9E-AEF867049728}]
    Exit critical section [/cover] */
  SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();

  /* Reset interrupt mode configuration register */
  AtomChannelRegPtr->IRQ.MODE.U = PWM_ATOM_SFR_RESET_VAL;
  
  /* MISRA2012_RULE_2_2_JUSTIFICATION: LocalIdleState value is used in
                                  Mcal_SetBitAtomic macro hence no dead code. */
  /* MISRA2012_RULE_2_2_JUSTIFICATION: AtomChannelRegPtr value is used in
                                  Mcal_SetBitAtomic macro hence no dead code. */
                                  
}
#endif
#endif

#if((PWM_17_GTMCCU6_SET_DUTY_CYCLE_API == STD_ON) || \
    (PWM_17_GTMCCU6_SET_PERIOD_AND_DUTY_API == STD_ON) || \
    (PWM_17_GTMCCU6_SET_OUTPUT_TO_IDLE_API == STD_ON))
/******************************************************************************
** Syntax : static Pwm_17_GtmCcu6_PeriodType Pwm_lGetAbsvalEdge              **
**                    (                                                      **
**                      const Pwm_17_GtmCcu6_PeriodType Period,              **
**                      const uint32 Value                                   **
**                    )                                                      **
** Service ID:        none                                                   **
**                                                                           **
** Sync/Async:        Synchronous                                            **
**                                                                           **
** Reentrancy:        Reentrant                                              **
**                                                                           **
** Parameters (in):   Period : Period Value in terms of Timer Count          **
**                    Value :  Relative Value when duty shift in ticks       **
**                             is ON or OFF                                  **
** Parameters (out):  none                                                   **
**                                                                           **
** Return value:      Absolute Value : Returns the converted value           **
**                                                                           **
** Description :      Local function : This function will convert the passed **
**                                    value to scaled value as per Period    **
**                                    This will be utilized for edge aligned **
**                                    Type PWM channels                      **
**                                                                           **
** Traceability:      [cover parentID={1F4A90CE-0142-4f56-B467-EA4D613119C2}]**
**                     [/cover]                                              **
******************************************************************************/
static Pwm_17_GtmCcu6_PeriodType Pwm_lGetAbsvalEdge  
                     (const Pwm_17_GtmCcu6_PeriodType Period,const uint32 Value)
{
  uint32 ScaledValue;
  #if (PWM_17_GTMCCU6_DUTY_SHIFT_IN_TICKS == STD_OFF)
  float32 LScaledValue;
  float32 Absval;
  #endif
  /* [cover parentID={4DDF511C-574E-4efd-9500-E72836B34E7C}]
  If period is zero [/cover] */
  if (Period == 0U)
  {
    /* Make scaled value zero for zero period */
    ScaledValue = 0U;
  }
  else
  {
    /* [cover parentID={78CEB49E-3757-4162-905B-D4BF594D3F84}]
    Is duty cycle shift in ticks enabled [/cover] */
    #if (PWM_17_GTMCCU6_DUTY_SHIFT_IN_TICKS == STD_ON)
    /* Dutycycle is in absolute ticks, use this directly */
    ScaledValue = Value;
    #else
    /* [cover parentID={0CCB237F-F48A-490b-9210-6A05E256D894}]
    IS duty cycle shift in ticks not enabled [/cover] */

    /* Dutycycle is in percentage */
    /* Convert the passed Relative value to absolute value as mentioned in SWS
    (AbsoluteDutyCycle=(((uint32)AbsolutePeriodTime *relativeDutyCycle)))>>15)*/
    Absval = ((float32)Period / (float32)PWM_SHIFT_BY15);
    LScaledValue = (Absval * (float32)Value);
    ScaledValue = (uint32) LScaledValue;
    #endif
    /* [cover parentID={6F5544B4-0FA5-4f59-8A9E-DE4F4B650984}]
    If period is less than scaled value [/cover] */
    if (Period <= ScaledValue)
    {
      /* Make scaled value with full range of timer max */
      ScaledValue = Period;
    }
  }
  return (ScaledValue);
}
#endif

#if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
#if (PWM_17_GTMCCU6_SET_DUTY_CYCLE_API == STD_ON)
/******************************************************************************
** Syntax : LOCAL_INLINE Pwm_17_GtmCcu6_PeriodType Pwm_lGetCenterLead        **
**                    (                                                      **
**                      const Pwm_17_GtmCcu6_PeriodType Period,              **
**                      const Pwm_17_GtmCcu6_PeriodType ScaledDuty           **
**                    )                                                      **
** Service ID:        none                                                   **
**                                                                           **
** Sync/Async:        Synchronous                                            **
**                                                                           **
** Reentrancy:        Reentrant                                              **
**                                                                           **
** Parameters (in):   Period : Period Value in terms of Timer Count          **
**                    ScaledDuty : Duty Value (Scaled as per Period)         **
**                                                                           **
** Parameters (out):  none                                                   **
**                                                                           **
** Return value:      Absolute Value : Returns the converted lead value      **
**                                                                           **
** Description :      Local function :This function will convert the passed **
**                                    scaled Duty value to Center aligned    **
**                                    Absolute lead value in scale of period **
**                                    passed. The value informs the leading  **
**                                    timer count to position the edge.      **
**                                    To get Scaled Center Lead value as per **
**                                    Period and ScaledDuty                  **
**                                                                           **
******************************************************************************/
LOCAL_INLINE Pwm_17_GtmCcu6_PeriodType Pwm_lGetCenterLead
(
  const Pwm_17_GtmCcu6_PeriodType Period,
  const Pwm_17_GtmCcu6_PeriodType ScaledDuty
)
{
  Pwm_17_GtmCcu6_PeriodType ScaledCenterLead;

  /* Initialize local variable with Max Timer */
  ScaledCenterLead = PWM_MAX_TIMER;
  /*[cover parentID={EEC76D44-8285-40c4-8115-A01611D7B41C}] [/cover]*/
  /* if Duty is less than period  */
  if ( ScaledDuty < (Period) )
  {
    /* Calculate the timer count for lead edge */
    ScaledCenterLead =
      (Pwm_17_GtmCcu6_PeriodType)(((Period) - (ScaledDuty)) >> PWM_CONST_1);
  }
  return ScaledCenterLead;
}
#endif
#endif

#if ((PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON)&& \
     (PWM_17_GTMCCU6_SET_DUTY_CYCLE_API == STD_ON))
/******************************************************************************
** Syntax :           LOCAL_INLINE void Pwm_lHandleNotif                     **
**                    (                                                      **
**                      const Pwm_17_GtmCcu6_ChannelClassType ChannelKind,   **
**                      const uint32 Period,                                 **
**                      const uint32 DutyCycle,                              **
**                      const Pwm_17_GtmCcu6_ChannelType ChannelNumber,      **
**                      const uint8 CoreId                                   **
**                    )                                                      **
** Service ID:        none                                                   **
**                                                                           **
** Sync/Async:        Synchronous                                            **
**                                                                           **
** Reentrancy:        Reentrant for different channels                       **
**                                                                           **
** Parameters (in):   ChannelKind  : Type of channel                         **
**                    Period       : Period value of Channel                 **
**                    DutyCycle    : Duty cycle value                        **
**                    ChannelNumber: PWM channel number                      **
**                    CoreId       : Core Number                             **
**                                                                           **
** Parameters (out):  none                                                   **
**                                                                           **
** Return value:      none                                                   **
**                                                                           **
** Description :      Function to Set the global variables for notification  **
**                                                                           **
** Traceability :     [cover parentID={ECEEFC78-5DD4-49b9-9C98-C8AF896559A7}]** 
**                    [/cover]                                               **
*****************************************************************************/
LOCAL_INLINE void Pwm_lHandleNotif(
  const Pwm_17_GtmCcu6_ChannelClassType ChannelKind,
  const uint32 Period,
  const uint32 DutyCycle,
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId)
{
  Pwm_17_GtmCcu6_EdgeNotificationType NotifValue;

  #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
  uint8 PwmTimerType;
  const Pwm_17_GtmCcu6_ChannelConfigType *PwmChannelCfgPtr;

  PwmChannelCfgPtr = &(Pwm_ConfigPtr->PwmCoreAdd[CoreId]->Pwm_ChannelConfigPtr\
                       [ChannelNumber]);
  PwmTimerType = PwmChannelCfgPtr->PwmTimerUsed;
  #endif
  /* Get the type of notification asked */
  NotifValue = PWM_GET_NOTIFICATION_KIND(ChannelNumber,CoreId);

  NotifValue = NotifValue >> PWM_NOTIFI_EDGE_POS;
  /* [cover parentID={9149327F-3A65-4bab-8292-62D2FCFECF22}]
  Is notification for duty 0 or 100 enabled [/cover] */
  #if (PWM_17_GTMCCU6_NOTIF_FOR_100_0_ENABLE == STD_ON)
  /* [cover parentID={417E34B9-D25F-4850-A29F-43EF87B676CA}]
  If channel kind is period shifted or period center aligned [/cover] */
  if ((ChannelKind == PWM_17_GTMCCU6_FIXED_PERIOD_SHIFTED) || \
      (ChannelKind == PWM_17_GTMCCU6_FIXED_PERIOD_CENTER_ALIGNED))
  {
    /* [cover parentID={158E4B08-2F64-4180-8388-BA9C3B1AB9B5}]
    if duty cycle is 0 or 100% [/cover] */
    if ( (DutyCycle == 0U) || (DutyCycle == Period) )
    {
      /* [cover parentID={45808621-E4BC-4110-997B-A4CCD4E0E196}]
      If timer type is GTM [/cover] */
      #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
      if(PwmTimerType == PWM_17_GTMCCU6_GTM_TIMER)
      {
        /* Disable notification if duty is 0% or 100% */
        Pwm_lGtmIrqModify(ChannelNumber, 0U, CoreId);
      }
      else
      #endif
      {
        #if (PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
        /* Disable notification if duty is 0% or 100% */
        Pwm_lCcu6IrqModify(ChannelNumber, 0U, CoreId);
        #endif
      }
      /* Clear the flag in global variable which indicates notification
         is enabled */
      Pwm_lClearNotificationStatus(ChannelNumber, CoreId);
      /* Set the flag to indicate Duty is 0% or 100% */
      Pwm_lSetDuty_0_Or_100_Status(ChannelNumber, CoreId);
    }
    else
    {
      /* [cover parentID={3AA5F2E3-219A-49b2-B0FA-BFC5CD1E996B}]
      If notification was asked earlier [/cover] */
      /* See whether notification was asked earlier */
      if ( NotifValue != PWM_NO_NOTIFICATION )
      {
        /* Set the flag in global variable which indicates notification
          is enabled*/
        Pwm_lSetNotificationStatus(ChannelNumber, CoreId);
        /* [cover parentID={2FC0C8E6-4F14-448b-A0C9-02402284EEB0}]
        If timer type is GTM [/cover] */
        #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
        if(PwmTimerType == PWM_17_GTMCCU6_GTM_TIMER)
        {
          /* Enable notification if duty is 0% or 100% */
          Pwm_lGtmIrqModify(ChannelNumber, NotifValue, CoreId);
        }
        else
        #endif
        {
          #if (PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
          /* Enable notification if duty is 0% or 100% */
          Pwm_lCcu6IrqModify(ChannelNumber, NotifValue, CoreId);
          #endif
        }
      }
      /* Clear the flag to indicate Duty is not 0% or 100% */
      Pwm_lClearDuty_0_Or_100_Status(ChannelNumber, CoreId);
    }
  }
  else
  {
    /* [cover parentID={4774C2E3-F2A2-4f80-82FD-F533E48E7AEA}]
    If notification was asked earlier [/cover] */
    if ( NotifValue != PWM_NO_NOTIFICATION )
    {
      /* Set the flag in global variable which indicates notification
         is enabled*/
      Pwm_lSetNotificationStatus(ChannelNumber, CoreId);
      /* [cover parentID={8F9D47DF-7E84-45c7-BB76-E76ABFBF1F27}]
      If timer type is GTM [/cover] */
      #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
      if(PwmTimerType == PWM_17_GTMCCU6_GTM_TIMER)
      {
        Pwm_lGtmIrqModify(ChannelNumber, NotifValue, CoreId);
      }
      else
      #endif
      {
        #if (PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
        /* Enable notification if duty is 0% or 100% */
        Pwm_lCcu6IrqModify(ChannelNumber, NotifValue, CoreId);
        #endif
      }
    }
    UNUSED_PARAMETER(Period);
    UNUSED_PARAMETER(DutyCycle);
  }
  #else
  {
    /* [cover parentID={3FCBD545-3C81-4c12-9603-0DE020AD8C6A}]
    If notification for duty 0% or 100% is not enabled [/cover] */
    /* [cover parentID={3DB94B62-20E7-4e79-B122-2749D5F4C8CC}]
    If duty is 0% or 100% [/cover] */
    if ( (DutyCycle == 0U) || (DutyCycle == Period) )
    {
        #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
      /* Disable notification if duty is 0% or 100% */
      /* [cover parentID={E98E9976-75D0-487a-A1AA-FC0D3E63F60C}]
      If timer type is GTM [/cover] */
      if(PwmTimerType == PWM_17_GTMCCU6_GTM_TIMER)
      {
        /* Disable notification if duty is 0% or 100% */
        Pwm_lGtmIrqModify(ChannelNumber, 0U, CoreId);
      }
      else
      #endif
      {
        #if (PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
        /* Disable notification if duty is 0% or 100% */
        Pwm_lCcu6IrqModify(ChannelNumber, 0U, CoreId);
        #endif
      }
      /* Clear the flag in global variable which indicates notification
         is enabled*/
      Pwm_lClearNotificationStatus(ChannelNumber, CoreId);
      /* Set the flag to indicate Duty is 0% or 100% */
      Pwm_lSetDuty_0_Or_100_Status(ChannelNumber, CoreId);
    }
    else
    {
      /* [cover parentID={F7554422-E766-4366-B130-3B34822E0EA7}]
      If notification was asked earlier [/cover] */
      /* See whether notification was asked earlier */
      if ( NotifValue != PWM_NO_NOTIFICATION)
      {
        /* Set the flag in global variable which indicates notification
           is enabled*/
        Pwm_lSetNotificationStatus(ChannelNumber, CoreId);
        #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
        /* [cover parentID={54D62FD6-6633-4ff9-9264-2AA42C76B076}]
        If timer type is GTM [/cover] */
        if(PwmTimerType == PWM_17_GTMCCU6_GTM_TIMER)
        {
          /* Enable notification if duty is 0% or 100% */
          Pwm_lGtmIrqModify(ChannelNumber, NotifValue, CoreId);
        }
        else
        #endif
        {
          #if (PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
          /* Enable notification if duty is 0% or 100% */
          Pwm_lCcu6IrqModify(ChannelNumber, NotifValue, CoreId);
          #endif
        }
      }
      /*Clear the flag to indicate Duty is 0% or 100%*/
      Pwm_lClearDuty_0_Or_100_Status(ChannelNumber, CoreId);
    }
    /* to remove unused param warning in GNU */
    UNUSED_PARAMETER(ChannelKind);
  }
  #endif
}
#endif
#if (PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON)
/******************************************************************************
** Syntax :     LOCAL_INLINE void Pwm_lSetDuty_0_Or_100_Status               **
**                    (                                                      **
**                         const Pwm_17_GtmCcu6_ChannelType Channel          **
**                         const uint8 CoreId                                **
**                    )                                                      **
** Service ID:        none                                                   **
**                                                                           **
** Sync/Async:        Synchronous                                            **
**                                                                           **
** Reentrancy:        Reentrant                                              **
**                                                                           **
** Parameters (in):   Channel : PWM Channel Number                           **
**                    CoreId : Core Number                                   **
**                                                                           **
** Parameters (out):  none                                                   **
**                                                                           **
** Return value:      none                                                   **
**                                                                           **
** Description :      Function to Set the Duty Notification status in the    **
**                    global channel variable                                **
**                                                                           **
** Traceability   : [cover parentID={8BE4A877-19F0-4a63-B124-D5AD529913AE}]  **
**                     [/cover]                                              **
******************************************************************************/
LOCAL_INLINE void Pwm_lSetDuty_0_Or_100_Status
(const Pwm_17_GtmCcu6_ChannelType Channel, 
 const uint8 CoreId)
{
  Pwm_17_GtmCcu6_ChannelStatusType *LocalPwmChanStatusPtr;
  LocalPwmChanStatusPtr = Pwm_CoreChannelStatus[CoreId];
  Mcal_SetBitAtomic(&(LocalPwmChanStatusPtr[Channel].Pwm_GlobChn),
                    PWM_DUTY_0_OR_100_UPDATE_FLGPOS,
                    (PWM_CHAN_ID_STAT_BITS),
                    (PWM_BIT_SET)
                   );
  /* MISRA2012_RULE_2_7_JUSTIFICATION: Parameter Channel is used as input to
     macro Mcal_SetBitAtomic, hence parameter is used.*/
  /* MISRA2012_RULE_8_13_JUSTIFICATION: Mcal_SetBitAtomic macro updates
     address pointer LocalPwmChanStatusPtr, hence it cannot be made const */
  /* MISRA2012_RULE_2_2_JUSTIFICATION: LocalPwmChanStatusPtr value is used in
                                  Mcal_SetBitAtomic macro hence no dead code.*/
}
#if (PWM_17_GTMCCU6_INITCHECK_API == STD_ON)
/******************************************************************************
** Syntax :     LOCAL_INLINE Std_ReturnType Pwm_lSetDuty_0_Or_100_StatusCheck**
**                        (                                                  **
**                          const Pwm_17_GtmCcu6_ChannelType Channel,        **
**                          const uint8 CoreId                               **
**                        )                                                  **
**                                                                           **
** Service ID:        none                                                   **
**                                                                           **
** Sync/Async:        Synchronous                                            **
**                                                                           **
** Reentrancy:        Non Reentrant                                          **
**                                                                           **
** Parameters (in):   Channel :PWM Channel Number                            **
**                    CoreId : Core Number                                   **
**                                                                           **
** Parameters (out):  none                                                   **
**                                                                           **
** Return value:      E_OK: Duty notification status check is passed         **
**                    E_NOT_OK: Duty notification status check is failed     **
**                                                                           **
** Description :      Function to verify Duty Notification status in the     **
**                    global channel variable                                **
**                                                                           **
** Traceability :     [cover parentID={C96B7E9D-50B0-48d2-A919-E0A45F4448AF}]**
**                   [/cover]                                                **
******************************************************************************/
LOCAL_INLINE Std_ReturnType Pwm_lSetDuty_0_Or_100_StatusCheck
(const Pwm_17_GtmCcu6_ChannelType Channel, 
 const uint8 CoreId)
{
  const Pwm_17_GtmCcu6_ChannelStatusType *LocalPwmChanStatusPtr;
  Std_ReturnType ErrorStatus = E_NOT_OK;
  uint32 NotifValue;

  LocalPwmChanStatusPtr = Pwm_CoreChannelStatus[CoreId];
  NotifValue = ((LocalPwmChanStatusPtr[Channel].Pwm_GlobChn >> \
              PWM_DUTY_0_OR_100_UPDATE_FLGPOS) & (uint32)PWM_CHAN_ID_STAT_BITS);
  if (NotifValue == PWM_CONST_1)
  {
    ErrorStatus = E_OK;
  }
  return ErrorStatus;
}
#endif

/******************************************************************************
** Syntax :           LOCAL_INLINE void Pwm_lSetNotificationEdges            **
**                    (                                                      **
**                      const Pwm_17_GtmCcu6_ChannelType Channel,            **
**                      const Pwm_17_GtmCcu6_EdgeNotificationType Edge       **
**                      const uint8 CoreId                                   **
**                    )                                                      **
**                                                                           **
** Service ID:        none                                                   **
**                                                                           **
** Sync/Async:        Synchronous                                            **
**                                                                           **
** Reentrancy:        Reentrant for different channels                       **
**                                                                           **
** Parameters (in):   Channel :PWM Channel Number                            **
**                    Edge : Notification edge                               **
**                    CoreId : Core Number                                   **
**                                                                           **
** Parameters (out):  none                                                   **
**                                                                           **
** Return value:      none                                                   **
**                                                                           **
** Description :      Function to set the Notification edges in the          **
**                                                 global channel variable   **
**                                                                           **
** Traceability :     [cover parentID={132A9243-184F-40a4-9C6E-540BC39F8C4E}]**
**                   [/cover]                                                **
******************************************************************************/
LOCAL_INLINE void Pwm_lSetNotificationEdges(
  const Pwm_17_GtmCcu6_ChannelType Channel, 
  const Pwm_17_GtmCcu6_EdgeNotificationType Edge, 
  const uint8 CoreId)
{
  Pwm_17_GtmCcu6_ChannelStatusType *LocalPwmChanStatusPtr;
  LocalPwmChanStatusPtr = Pwm_CoreChannelStatus[CoreId];
  Mcal_SetBitAtomic(&(LocalPwmChanStatusPtr[Channel].Pwm_GlobChn),
                    PWM_NOTIFI_EDGE_POS,
                    PWM_NOTIFI_EDGE_BITS,
                    (uint32)(Edge)
                   );
  /* MISRA2012_RULE_2_7_JUSTIFICATION: Parameters are updated to register in
     macro Mcal_SetBitAtomic, hence parameters are used.*/
  /* MISRA2012_RULE_8_13_JUSTIFICATION: Mcal_SetBitAtomic macro updates
     address pointer LocalPwmChanStatusPtr, hence it cannot be made const */
  /* MISRA2012_RULE_2_2_JUSTIFICATION: LocalPwmChanStatusPtr value is used in
                                  Mcal_SetBitAtomic macro hence no dead code. */
}

/******************************************************************************
** Syntax :         LOCAL_INLINE void Pwm_lClearNotificationStatus           **
**                    (                                                      **
**                      const Pwm_17_GtmCcu6_ChannelType Channel             **
**                      const uint8 CoreId                                   **
**                    )                                                      **
** Service ID:        none                                                   **
**                                                                           **
** Sync/Async:        Synchronous                                            **
**                                                                           **
** Reentrancy:        Reentrant for different channels                       **
**                                                                           **
** Parameters (in):   Channel :PWM Channel Number                            **
**                    CoreId : Core Number                                   **
**                                                                           **
** Parameters (out):  none                                                   **
**                                                                           **
** Return value:      none                                                   **
**                                                                           **
** Description :      Function to Clear the Notification status in the global**
**                                                      channel variable     **
** Traceability : [cover parentID={179607C4-4E96-4b04-9B4F-C6EC48110F8F}]    **
**                [/cover]                                                   **
******************************************************************************/
LOCAL_INLINE void Pwm_lClearNotificationStatus
(const Pwm_17_GtmCcu6_ChannelType Channel, 
 const uint8 CoreId)
{
  Pwm_17_GtmCcu6_ChannelStatusType *LocalPwmChanStatusPtr;
  LocalPwmChanStatusPtr = Pwm_CoreChannelStatus[CoreId];
  Mcal_SetBitAtomic(&(LocalPwmChanStatusPtr[Channel].Pwm_GlobChn),
                    PWM_NOTIFI_STATUS_POS,
                    (PWM_CHAN_ID_STAT_BITS),
                    (PWM_BIT_RESET)
                   );
  /* MISRA2012_RULE_2_7_JUSTIFICATION: Parameter Channel is used as input to
     macro Mcal_SetBitAtomic, hence parameter is used.*/
  /* MISRA2012_RULE_8_13_JUSTIFICATION: Mcal_SetBitAtomic macro updates
     address pointer LocalPwmChanStatusPtr, hence it cannot be made const */
  /* MISRA2012_RULE_2_2_JUSTIFICATION: LocalPwmChanStatusPtr value is used in
                                  Mcal_SetBitAtomic macro hence no dead code. */
}
/******************************************************************************
** Syntax :           LOCAL_INLINE void Pwm_lSetNotificationStatus           **
**                    (                                                      **
**                      const Pwm_17_GtmCcu6_ChannelType Channel             **
**                      const uint8 CoreId                                   **
**                    )                                                      **
** Service ID:        none                                                   **
**                                                                           **
** Sync/Async:        Synchronous                                            **
**                                                                           **
** Reentrancy:        Reentrant for different channels                       **
**                                                                           **
** Parameters (in):   Channel :PWM Channel Number                            **
**                    CoreId : Core Number                                   **
**                                                                           **
** Parameters (out):  none                                                   **
**                                                                           **
** Return value:      none                                                   **
**                                                                           **
** Description :      Function to Set the Notification status in the global  **
**                                                      channel variable     **
** Traceability      :[cover parentID={DDE9481C-86DC-419d-9F48-A0FAE1CBEDEC}]**
**                   [/cover]                                                **
*****************************************************************************/
LOCAL_INLINE void Pwm_lSetNotificationStatus(const Pwm_17_GtmCcu6_ChannelType
    Channel, const uint8 CoreId)
{
  Pwm_17_GtmCcu6_ChannelStatusType *LocalPwmChanStatusPtr;
  LocalPwmChanStatusPtr = Pwm_CoreChannelStatus[CoreId];
  Mcal_SetBitAtomic(&(LocalPwmChanStatusPtr[Channel].Pwm_GlobChn),
                    PWM_NOTIFI_STATUS_POS,
                    PWM_CHAN_ID_STAT_BITS,
                    PWM_BIT_SET
                   );
  /* MISRA2012_RULE_2_7_JUSTIFICATION: Parameter Channel is used as input to
   macro Mcal_SetBitAtomic, hence parameter is used.*/
  /* MISRA2012_RULE_8_13_JUSTIFICATION: Mcal_SetBitAtomic macro updates
     address pointer LocalPwmChanStatusPtr, hence it cannot be made const */
  /* MISRA2012_RULE_2_2_JUSTIFICATION: LocalPwmChanStatusPtr value is used in
                                  Mcal_SetBitAtomic macro hence no dead code. */
}
#if ((PWM_17_GTMCCU6_SET_DUTY_CYCLE_API == STD_ON) || \
     ((PWM_17_GTMCCU6_SET_PERIOD_AND_DUTY_API == STD_ON) && \
     (PWM_17_GTMCCU6_NOTIF_FOR_100_0_ENABLE == STD_OFF)))
/******************************************************************************
** Syntax :     LOCAL_INLINE void Pwm_lClearDuty_0_Or_100_Status             **
**                    (                                                      **
**                      const Pwm_17_GtmCcu6_ChannelType Channel             **
**                      const uint8 CoreId                                   **
**                    )                                                      **
** Service ID:        none                                                   **
**                                                                           **
** Sync/Async:        Synchronous                                            **
**                                                                           **
** Reentrancy:        Reentrant for different channels                       **
**                                                                           **
** Parameters (in):   Channel :PWM Channel Number                            **
**                    CoreId : Core Number                                   **
**                                                                           **
** Parameters (out):  none                                                   **
**                                                                           **
** Return value:      none                                                   **
**                                                                           **
** Description :      Function to clear the Duty Notification status in the  **
**                                                 global channel variable   **
** Traceability :  [cover parentID={9AA7833B-FB69-4e37-B42C-F76130711F6F}]   **
**                   [/cover]                                                **
*****************************************************************************/
LOCAL_INLINE void Pwm_lClearDuty_0_Or_100_Status 
(const Pwm_17_GtmCcu6_ChannelType Channel, 
 const uint8 CoreId)
{
  Pwm_17_GtmCcu6_ChannelStatusType *LocalPwmChanStatusPtr;
  LocalPwmChanStatusPtr = Pwm_CoreChannelStatus[CoreId];
  Mcal_SetBitAtomic(&(LocalPwmChanStatusPtr[Channel].Pwm_GlobChn),
                    PWM_DUTY_0_OR_100_UPDATE_FLGPOS,
                    (PWM_CHAN_ID_STAT_BITS),
                    (PWM_BIT_RESET)
                   );
  /* MISRA2012_RULE_2_7_JUSTIFICATION: Parameter Channel is used as input to
     macro Mcal_SetBitAtomic, hence parameter is used.*/
  /* MISRA2012_RULE_8_13_JUSTIFICATION: Mcal_SetBitAtomic macro updates
     address pointer LocalPwmChanStatusPtr, hence it cannot be made const */
  /* MISRA2012_RULE_2_2_JUSTIFICATION: LocalPwmChanStatusPtr value is used in
                                  Mcal_SetBitAtomic macro hence no dead code. */
}
#endif
/******************************************************************************
** Syntax :      LOCAL_INLINE void Pwm_lClearNotificationEdges               **
**                    (                                                      **
**                      const Pwm_17_GtmCcu6_ChannelType Channel             **
**                      const uint8 CoreId                                   **
**                    )                                                      **
** Service ID:        none                                                   **
**                                                                           **
** Sync/Async:        Synchronous                                            **
**                                                                           **
** Reentrancy:        Reentrant for different channels                       **
**                                                                           **
** Parameters (in):   Channel :PWM Channel Number                            **
**                    CoreId : Core Number                                   **
**                                                                           **
** Parameters (out):  none                                                   **
**                                                                           **
** Return value:      none                                                   **
**                                                                           **
** Description :      Function to clear the Notification edges in the        **
**                                                 global channel variable   **
** Traceability :     [cover parentID={C6CAE13A-6B0C-412e-9E78-2FCCD47D3D81}]**
**                     [/cover]                                              **
*****************************************************************************/
LOCAL_INLINE void Pwm_lClearNotificationEdges
(const Pwm_17_GtmCcu6_ChannelType Channel, 
 const uint8 CoreId)
{
  Pwm_17_GtmCcu6_ChannelStatusType *LocalPwmChanStatusPtr;
  LocalPwmChanStatusPtr = Pwm_CoreChannelStatus[CoreId];
  Mcal_SetBitAtomic(&(LocalPwmChanStatusPtr[Channel].Pwm_GlobChn),
                    PWM_NOTIFI_EDGE_POS,
                    PWM_NOTIFI_EDGE_BITS,
                    PWM_BIT_RESET
                   );
  /* MISRA2012_RULE_2_7_JUSTIFICATION: Parameter Channel is used as input to
     macro Mcal_SetBitAtomic, hence parameter is used.*/
  /* MISRA2012_RULE_8_13_JUSTIFICATION: Mcal_SetBitAtomic macro updates
     address pointer LocalPwmChanStatusPtr, hence it cannot be made const */
  /* MISRA2012_RULE_2_2_JUSTIFICATION: LocalPwmChanStatusPtr value is used in
                                  Mcal_SetBitAtomic macro hence no dead code. */
}
#endif /* End of PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED */

#if((PWM_17_GTMCCU6_SET_PERIOD_AND_DUTY_API == STD_ON) || \
    (PWM_17_GTMCCU6_SET_DUTY_CYCLE_API == STD_ON))
#if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
/*******************************************************************************
** Syntax : static void Pwm_lGtmStartChannel                                  **
**                   (                                                        **
**                     const Pwm_17_GtmCcu6_ChannelType ChannelNumber,        **
**                     const uint32 Period,                                   **
**                     const uint32 Dutycycle,                                **
**                     const uint32 Shift,                                    **
**                     const uint8 CoreId                                     **
**                   )                                                        **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant                                                **
**                                                                            **
** Parameters (in):  PwmChanneld - PWM Channel Number                         **
**                   period - Period of the PWM to be generated               **
**                   DutyCycle - Dutycycle of the PWM to be generated         **
**                   Shift - Amount of Phase shift for the channel            **
**                   CoreId - Core number                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     This function starts the PWM channel as given by the     **
**                   Input parameters with the desired properties.            **
**                                                                            **
** Traceability :    [cover parentID={869F8A0F-8405-4333-B20C-713C412E1BDA}]  **
**                   [/cover]                                                 **
*******************************************************************************/
static void Pwm_lGtmStartChannel
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint32 Period,
  const uint32 Dutycycle,
  const uint32 Shift,
  const uint8 CoreId
)
{
  Mcu_17_Gtm_TimerOutType PwmGtmTimerType;
  const Mcu_17_Gtm_TomAtomChConfigType *PwmGtmTimerPtr;
  /* MISRA2012_RULE_11_5_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  /* MISRA2012_RULE_11_3_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  PwmGtmTimerPtr = (const Mcu_17_Gtm_TomAtomChConfigType*)\
                   Pwm_ConfigPtr->PwmCoreAdd[CoreId]->Pwm_ChannelConfigPtr\
                   [ChannelNumber].PwmTimerPtr;
  /* [cover parentID={CF553597-2BBA-498d-970E-9E1E10414873}]
  Extract Gtm Timer Type [/cover] */
  PwmGtmTimerType = PwmGtmTimerPtr->TimerType;
  /* [cover parentID={CE2F90E0-E22E-4286-859D-781C841B32DE}]
  If sub-module type is TOM [/cover] */
  if(PwmGtmTimerType == MCU_GTM_TIMER_TOM)
  {
    /* [cover parentID={D9D0EB26-916F-4791-98D9-80BFE68B808C}]
    Start TOM channel [/cover] */
    Pwm_lGtmStartTomChannel(ChannelNumber, Period, Dutycycle, Shift, CoreId);
  }
  /* Detect the Sub-Module type is ATOM */
  else
  {
    /* [cover parentID={0D90F964-97FA-491c-BFC3-E1AA9A3D098C}]
    Start ATOM channel [/cover] */
    Pwm_lGtmStartAtomChannel(ChannelNumber, Period, Dutycycle, Shift, CoreId);
  }
}
#endif
#endif
#if(PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
/*******************************************************************************
** Syntax : static void Pwm_lCcu6StartChannel                                 **
**                  (                                                         **
**                    const Pwm_17_GtmCcu6_ChannelType ChannelNumber,         **
**                    const uint32 Period,                                    **
**                    const uint32 Dutycycle,                                 **
**                    const uint8 CoreId                                      **
**                  )                                                         **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant                                                **
**                                                                            **
** Parameters (in):  PwmChanneld - PWM Channel number                         **
**                   Period - Period of PWM to be generated                   **
**                   DutyCycle - Duty cycle of PWM to be generated            **
**                   CoreId : Core Id                                         **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     This function starts the PWM channel as given by the     **
**                   Input parameters with the desired properties.            **
**                                                                            **
** Traceability :    [cover parentID={B3B67A3B-F17F-48b2-A451-CFE4E605D3B6}]  **
**                     [/cover]                                               **
*******************************************************************************/
static void Pwm_lCcu6StartChannel
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint32 Period,
  const uint32 Dutycycle,
  const uint8 CoreId
)
{
  const Mcu_17_Ccu6_TimerConfigType *PwmCcu6TimerPtr;
  uint8 Ccu6Kernel;
  uint8 Ccu6Timer;
  uint8 Ccu6Comparator;
  uint32 TempPeriod;
  uint32 TempDutycycle;

  TempPeriod = Period;
  TempDutycycle = Dutycycle;
  /* MISRA2012_RULE_11_5_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Ccu6_TimerConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  /* MISRA2012_RULE_11_3_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Ccu6_TimerConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  PwmCcu6TimerPtr = (const Mcu_17_Ccu6_TimerConfigType*)\
                    Pwm_ConfigPtr->PwmCoreAdd[CoreId]->Pwm_ChannelConfigPtr\
                    [ChannelNumber].PwmTimerPtr;
  Ccu6Kernel = (uint8)((PwmCcu6TimerPtr->TimerId) & PWM_CCU6_KERNEL_MSK);
  Ccu6Timer = (uint8)((PwmCcu6TimerPtr->TimerId >> PWM_CCU6_TIMER_POS)\
                      & PWM_CCU6_TIMER_MSK);
  Ccu6Comparator =(uint8)((PwmCcu6TimerPtr->TimerId >> PWM_CCU6_COMPARATOR_POS)\
                           & PWM_CCU6_COMPARATOR_MSK);

  /* [cover parentID={ED508B7D-46D1-4ee6-BAC0-2EC72B975DDC}][/cover] */
  if((Period != 0U) && (Period == Dutycycle))
  {
    TempDutycycle = PWM_MAX_TIMER_CCU6;
  }
  /* [cover parentID={A0526DFF-FDBD-4cf1-9EA8-132AA96B7D3B}][/cover] */
  if(Period > 1U)
  {
    TempPeriod = Period - 1U;
  }
  /* [cover parentID={709FEA81-DCAD-43cf-AD5D-5F852CB065CA}] [/cover] */
  if(Ccu6Timer == MCU_CCU6_TIMER_T12)
  {
    /* [cover parentID={68E5FA7F-8E12-4edd-869F-DB4F1D97A523}]
    Enter critical section [/cover] */
    SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();

    /* [cover parentID={C56798CB-DEEA-4077-8F28-FEA490279AAD}]
    Set period and duty [/cover] */
    Pwm_17_GtmCcu6_Kernel[Ccu6Kernel]->CC6SR[Ccu6Comparator].U = TempDutycycle;
    Pwm_17_GtmCcu6_Kernel[Ccu6Kernel]->T12PR.U = TempPeriod;
    /* [cover parentID={090A8842-97F3-4087-B5B8-F82AAB81F18F}]
    Exit critical section [/cover] */
    SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
  }
  else
  {
    /* [cover parentID={2DE15CDC-56C3-424b-B232-2B94A5488B4C}]
    Enter critical section [/cover] */
    SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();

    /* [cover parentID={CF579D2A-E499-4e93-96CF-68DD8D823195}]
    Set period and duty [/cover] */
    Pwm_17_GtmCcu6_Kernel[Ccu6Kernel]->CC63SR.U = TempDutycycle;
    Pwm_17_GtmCcu6_Kernel[Ccu6Kernel]->T13PR.U = TempPeriod;
    /* [cover parentID={2961FC51-C7EC-40b9-B26D-CD238BF106FF}]
    Exit critical section [/cover] */
    SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
  }
  /* [cover parentID={D6B9A5B3-3177-43e6-B159-3B686B3A5131}]
  Enable shadow transfer [/cover] */
  Mcu_17_Ccu6_TimerShadowTransfer(PwmCcu6TimerPtr->TimerId);
}
#endif
#if((PWM_17_GTMCCU6_SET_PERIOD_AND_DUTY_API == STD_ON) || \
    (PWM_17_GTMCCU6_SET_DUTY_CYCLE_API == STD_ON))
#if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
/*******************************************************************************
** Syntax : static void Pwm_lGtmStartTomChannel                               **
**                  (                                                         **
**                    const Pwm_ChannelIdentifierType GlobalChannelId,        **
**                    const uint32 Period,                                    **
**                    const uint32 Dutycycle,                                 **
**                    const uint32 Shift,                                     **
**                    const uint8 CoreId                                      **
**                  )                                                         **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different timer channels                   **
**                                                                            **
** Parameters (in):  Channel Number - logical channel number                  **
**                   Period         - Desired Period value                    **
**                   Dutycycle      - Desired DutyCycle value                 **
**                   Shift          - Desired Shift value                     **
**                   CoreId         - Core Id                                 **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     This function starts the PWM channel as given by the     **
**                   Input parameters with the desired properties for TOM     **
**                   timers                                                   **
** Traceability :    [cover parentID={04198767-3D6E-4161-B72E-8F281213E01A}]  ** 
**                  [/cover]                                                  **
*******************************************************************************/
static void Pwm_lGtmStartTomChannel
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint32 Period,
  const uint32 Dutycycle,
  const uint32 Shift,
  const uint8 CoreId
)
{
  const Pwm_17_GtmCcu6_ChannelConfigType *LocalPwmChanPtr; /* ROM pointer */
  const Mcu_17_Gtm_TomAtomChConfigType    *PwmGtmTimerPtr;
  Ifx_GTM_TOM_CH* TomChannelRegPtr; /* Ptr to TOM Channel Reg */
  uint8 Coherency;
  uint8 TimerChannelNumber;
  uint8 TimerModuleNumber;
  uint8 ResetType;

  LocalPwmChanPtr = &(Pwm_ConfigPtr->PwmCoreAdd[CoreId]->\
                                          Pwm_ChannelConfigPtr[ChannelNumber]);
  /* MISRA2012_RULE_11_5_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  /* MISRA2012_RULE_11_3_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  PwmGtmTimerPtr = (const Mcu_17_Gtm_TomAtomChConfigType*)\
                   LocalPwmChanPtr->PwmTimerPtr;
  TimerModuleNumber = (uint8)((PwmGtmTimerPtr->TimerId &\
                                  GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);
  TimerChannelNumber = (uint8)((PwmGtmTimerPtr->TimerId &\
                                  GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);
  Coherency = Pwm_lCoherency(LocalPwmChanPtr->PwmChannelInfo);
  ResetType = Pwm_lChanResetType(LocalPwmChanPtr->PwmChannelInfo);
  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TomChannelRegPtr = \
                 PWM_GTM_TOM_CH_POINTER(TimerModuleNumber, TimerChannelNumber);
  /* [cover parentID={3F64A0E8-9F93-4798-A33B-439A60C9EC2C}]
  Reset type is 0 for Fixed period or Variable period channels [/cover] */
  if(ResetType == 0U)
  {
    /* [cover parentID={8D9DF36E-49C5-4c55-B639-B4F01702D776}]
    If duty cycle is not zero [/cover] */
    if (Dutycycle != 0U)
    {
      /* [cover parentID={4D6D6168-4FD0-48d7-8E92-D8B3F2903C6A}]
      If channel is non coherent [/cover] */
      if(Coherency == PWM_17_GTMCCU6_NON_COHERENT)
      {
        /* [cover parentID={DA3B2B7C-D626-433b-8A2D-CF781AEF31E0}]
        Start critical section [/cover] */
        SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
        /* Note - UPEN update is disabled, Hence no update of Compare match
        registers by shadow registers */
        /* [cover parentID={6E9AB265-E551-40f7-8A4E-A5936F69B0F8}]
        Update Compare match registers with period and
        duty values [/cover] */
        TomChannelRegPtr->CM0.U = Period;
        TomChannelRegPtr->CM1.U = Dutycycle;

        /* [cover parentID={EB091A25-4648-4e68-AC00-2310C2BCA9C7}]
        Exit critical section [/cover] */
        SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
      }
      else
      {
        /* [cover parentID={C2963147-2E57-454d-83B9-F582F2F0924D}]
        Start critical section [/cover] */
        SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
        /* [cover parentID={2966D2F2-E4C2-47b7-89F1-ED6F08F58955}]
        Disable shadow transfer [/cover] */
        Mcu_17_Gtm_TomChUpdateEnDis(TimerModuleNumber, TimerChannelNumber, \
                                    MCU_GTM_TIMER_UPDATE_DISABLE);
        /* [cover parentID={1A8F92E5-2C50-495d-B503-B384E6AE340A}]
        Update shadow register wih period and duty values [/cover] */
        TomChannelRegPtr->SR0.U = Period;
        TomChannelRegPtr->SR1.U = Dutycycle;
        /* [cover parentID={3F9FA279-D3CE-44cc-8D93-66C339EE01AE}]
        Enable shadow transfer [/cover] */
        Mcu_17_Gtm_TomChUpdateEnDis(TimerModuleNumber, TimerChannelNumber, \
                                    MCU_GTM_TIMER_UPDATE_ENABLE);
        /* [cover parentID={7A2EA750-9DBB-42e9-B217-05A713D0367F}]
        Exit Critical section [/cover] */
        SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
      }
    }
    else
    {
      /* [cover parentID={463FE00E-7545-4cbf-B172-06EB95D50B88}]
      If channel is non coherent [/cover] */
      if(Coherency == PWM_17_GTMCCU6_NON_COHERENT)
      {
        /* [cover parentID={DDB9411E-FEF1-4db9-9E71-F4BD4B646D51}]
        Start critical section [/cover] */
        SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
        
        /* Note - UPEN update is disabled, Hence no update of Compare match
        registers by shadow registers */
        /* [cover parentID={AF62CD44-04FA-4fdb-BD60-213866309A28}]
        Update compare match registers with duty and period value
        [/cover] */
        TomChannelRegPtr->CM1.U = 0U;
        TomChannelRegPtr->CM0.U = Period;
        /* [cover parentID={659E322D-9403-4680-9870-63E3783A1A23}]
        Exit critical section [/cover] */
        SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
      }
      else
      {
        /* [cover parentID={5058785D-199A-46f0-BFBC-C35D7BE0DB7D}]
         Start critical section [/cover] */
        SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
        /* [cover parentID={58B96E41-7AF1-4610-A9C2-9513751A38C8}]
        Update shadow registers with duty and period value
        [/cover] */
        Mcu_17_Gtm_TomChUpdateEnDis(TimerModuleNumber, TimerChannelNumber, \
                                    MCU_GTM_TIMER_UPDATE_DISABLE);
        TomChannelRegPtr->SR1.U = 0U;
        TomChannelRegPtr->SR0.U = Period;
        Mcu_17_Gtm_TomChUpdateEnDis(TimerModuleNumber, TimerChannelNumber, \
                                    MCU_GTM_TIMER_UPDATE_ENABLE);
        /* [cover parentID={876B8A59-514B-42d7-ABAE-D0922622A152}]
        Exit critical section [/cover] */
        SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
      }
    }
  }
  /* Reset type is 1 for Fixed period shifted or Center-aligned channels */
  else
  {
    /* [cover parentID={CAE01651-8ABE-49c0-96D9-BD7FF3A3DE69}]
    If channel is non coherent [/cover] */
    if(Coherency == PWM_17_GTMCCU6_NON_COHERENT)
    {
      /* [cover parentID={F9AA43D8-2CF5-489b-BA3C-A6C5A743D9C3}]
      If period is zero duty is set to zero [/cover] */
      /* [cover parentID={DC39EF9B-AEF8-4b9f-AC4B-31DEBDC3836C}]
      If duty cycle is zero [/cover] */
      if(Dutycycle == 0U)
      {
        /* [cover parentID={79640246-1C12-40af-85A6-DA64355464E8}]
        Start critical section  [/cover] */
        SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
        
        /* Note - UPEN update is disabled, Hence no update of Compare match
        registers by shadow registers */
        /* [cover parentID={5E55BD9E-D252-41f2-895D-5BE5981888A6}]
        Update compare match register wih period and duty values [/cover] */
        TomChannelRegPtr->CM0.U = PWM_MAX_TIMER_TOM;
        TomChannelRegPtr->CM1.U = 0U;
        
        /* [cover parentID={A7BF5075-BE47-4497-9283-36D4A6C53254}]
        Exit critical section  [/cover] */
        SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
      }
      else if (Dutycycle == Period)
      {
        /* [cover parentID={805D54F4-B764-41e6-86A4-90229EA64195}]
        If duty cycle is 100% [/cover] */
        /* [cover parentID={61A1B9CD-94A6-4352-9873-4DFFEAF025AC}]
        Start critical section [/cover] */
        SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
        /* Note - UPEN update is disabled, Hence no update of Compare match
        registers by shadow registers */
        /* [cover parentID={F3D40384-3F3C-4fcb-8BDD-D7E1AC3FBFDE}]
        Update compare match register wih period and duty values [/cover] */
        TomChannelRegPtr->CM0.U = 0U;
        TomChannelRegPtr->CM1.U = PWM_MAX_TIMER_TOM;
        /* [cover parentID={166A47D4-316B-40a0-9436-13389F78A624}]
        Exit critical section [/cover] */
        SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
      }
      else
      {
        /* [cover parentID={06A8254C-4DBA-4ecd-90A5-A8326BAD2308}]
         Start critical section [/cover] */
        SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
        /* Note - UPEN update is disabled, Hence no update of Compare match
        registers by shadow registers */
        /* [cover parentID={5ED5F455-2A18-4c01-86F0-8E2E3B756BD4}]
        Update compare match register period and duty with shift [/cover] */
        TomChannelRegPtr->CM0.U = Shift;
        /* MISRA2012_RULE_1_3_JUSTIFICATION: Condition of executing this case
          when period=0 will never occur, because when period is 0 duty is set
          to 0 in GetAbsvaledge API, and if duty is 0 if(Dutycycle == 0U)
          case is executed.*/
        TomChannelRegPtr->CM1.U = (Shift + Dutycycle) % Period;
        /* [cover parentID={0C220857-3A00-4211-99AE-F1F89EE81F13}]
        Exit critical section [/cover] */
        SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
      }
    }
    else
    {
      /* [cover parentID={F9AA43D8-2CF5-489b-BA3C-A6C5A743D9C3}]
      If duty is set to zero [/cover] */
      if(Dutycycle == 0U)
      {
        /* [cover parentID={66BE75EF-17F1-458f-857E-A9E533DDFF1A}]
        Start critical section  [/cover] */
        SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
        
        /* Disable shadow register */
        Mcu_17_Gtm_TomChUpdateEnDis(TimerModuleNumber, TimerChannelNumber, \
                                    MCU_GTM_TIMER_UPDATE_DISABLE);
        /* [cover parentID={094A6D28-3C19-44a9-9DDD-278CE3C99385}]
        Update period and duty shadow register to set 0%duty.[/cover] */
        TomChannelRegPtr->SR0.U = PWM_MAX_TIMER_TOM;
        TomChannelRegPtr->SR1.U = 0U;
        
        /* Enable shadow transfer */
        Mcu_17_Gtm_TomChUpdateEnDis(TimerModuleNumber, TimerChannelNumber, \
                                    MCU_GTM_TIMER_UPDATE_ENABLE);
        /* [cover parentID={1A4CA08F-7D32-4cc0-AF09-963F708EE750}]
        Exit critical section  [/cover] */
        SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
      }
      else if (Dutycycle == Period)
      {
        /* [cover parentID={34722933-F610-4aac-B9F8-34ADAFCB8B6A}]
        Duty is 100% [/cover] */
        /* [cover parentID={24C9F4F3-3A5B-4244-B81B-89E03EE0BFD1}]
        Start critical section [/cover] */
        SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
        /* [cover parentID={FF84BD00-13D6-42c2-9844-C68477CCBC72}]
        Disable shadow register [/cover] */
        Mcu_17_Gtm_TomChUpdateEnDis(TimerModuleNumber, TimerChannelNumber, \
                                    MCU_GTM_TIMER_UPDATE_DISABLE);
        /* [cover parentID={E732B7A8-176B-4876-8C1D-38579D2FA5C5}]
        Update shadow register with period and duty cycle [/cover] */
        TomChannelRegPtr->SR0.U = 0U;
        TomChannelRegPtr->SR1.U = PWM_MAX_TIMER_TOM;
        /* [cover parentID={B61700FA-9A68-4e15-A8BD-1630B4AA56D2}]
        Enable shadow transfer [/cover] */
        Mcu_17_Gtm_TomChUpdateEnDis(TimerModuleNumber, TimerChannelNumber, \
                                    MCU_GTM_TIMER_UPDATE_ENABLE);
        /* [cover parentID={076CD743-472E-4ab0-9B08-2576BC9D32FE}]
         Exit critical section [/cover] */
        SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
      }
      else
      {
        /* [cover parentID={B905AC3E-F57A-4d99-984A-9F6104D51E33}]
        Start critical section [/cover] */
        SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
        /* [cover parentID={BB8520F9-E3E2-4a99-956C-A9300950F47A}]
        Disable shadow transfer [/cover] */
        Mcu_17_Gtm_TomChUpdateEnDis(TimerModuleNumber, TimerChannelNumber, \
                                    MCU_GTM_TIMER_UPDATE_DISABLE);
        /* [cover parentID={69C7222C-B1A8-476c-89B4-91D73595E614}]
        Update shadow register with period and duty cycle [/cover] */
        TomChannelRegPtr->SR0.U = Shift;
        /* MISRA2012_RULE_1_3_JUSTIFICATION: Condition of executing this case
          when period=0 will never occur, Because when period is 0 duty is set
          to 0 in GetAbsvaledge API, and if duty is 0 if(Dutycycle == 0U)
          case is executed.*/
        TomChannelRegPtr->SR1.U = (Shift + Dutycycle) % Period;
        /* [cover parentID={40DF315D-67BA-43e0-BBE3-A02C334CCF02}]
        Enable shadow transfer [/cover] */
        Mcu_17_Gtm_TomChUpdateEnDis(TimerModuleNumber, TimerChannelNumber, \
                                    MCU_GTM_TIMER_UPDATE_ENABLE);
        /* [cover parentID={AEBDF09E-997F-4af5-B658-35869665C764}]
        Exit critical section [/cover] */
        SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
      }
    }
  }
}
/*******************************************************************************
** Syntax : static void Pwm_lGtmStartAtomChannel                              **
**                   (                                                        **
**                     const Pwm_17_GtmCcu6_ChannelType ChannelNumber,        **
**                     const uint32 Period,                                   **
**                     const uint32 Dutycycle,                                **
**                     const uint32 Shift,                                    **
**                     const uint8 CoreId                                     **
**                   )                                                        **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different timer channels                   **
**                                                                            **
** Parameters (in):  Channel Number - logical channel number                  **
**                   Period         - Desired Period value                    **
**                   Dutycycle      - Desired DutyCycle value                 **
**                   Shift          - Desired Shift value                     **
**                   CoreId :         Core Number                             **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     This function starts the PWM channel as given by the     **
**                   Input parameters with the desired properties for ATOM    **
**                   timers                                                   **
** Traceability :     [cover parentID={0CB84637-A8CD-43e7-A6DE-530E9D7860A3}] **
**                   [/cover]                                                 **
*******************************************************************************/
static void Pwm_lGtmStartAtomChannel
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint32 Period,
  const uint32 Dutycycle,
  const uint32 Shift,
  const uint8  CoreId
)
{
  const Pwm_17_GtmCcu6_ChannelConfigType *LocalPwmChanPtr; /* ROM pointer */
  const Mcu_17_Gtm_TomAtomChConfigType  *PwmGtmTimerPtr;
  Ifx_GTM_ATOM_CH* AtomChannelRegPtr; /* Ptr to ATOM Channel Reg */
  uint8 Coherency;
  uint8 TimerChannelNumber;
  uint8 TimerModuleNumber;
  uint8 ResetType;

  LocalPwmChanPtr = &(Pwm_ConfigPtr->PwmCoreAdd\
                         [CoreId]->Pwm_ChannelConfigPtr[ChannelNumber]);
  /* MISRA2012_RULE_11_5_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  /* MISRA2012_RULE_11_3_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  PwmGtmTimerPtr = (const Mcu_17_Gtm_TomAtomChConfigType*)\
                   LocalPwmChanPtr->PwmTimerPtr;
  TimerModuleNumber = (uint8)((PwmGtmTimerPtr->TimerId &\
                                  GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);
  TimerChannelNumber = (uint8)((PwmGtmTimerPtr->TimerId &\
                                  GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);
  Coherency = Pwm_lCoherency(LocalPwmChanPtr->PwmChannelInfo);
  ResetType = Pwm_lChanResetType(LocalPwmChanPtr->PwmChannelInfo);
  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  AtomChannelRegPtr = \
                 PWM_GTM_ATOM_CH_POINTER(TimerModuleNumber, TimerChannelNumber);
  /* [cover parentID={0A80D37B-6FA9-4f65-B841-F6B2696A16D1}]
  Reset type is 0 for Fixed period or Variable period channels [/cover] */
  if(ResetType == 0U)
  {
    /* [cover parentID={4783A049-46EE-4820-AA67-BB62408D850A}]
     Duty cycle is not 0 [/cover] */
    if (Dutycycle != 0U)
    {
      /* [cover parentID={A4380B95-5DA3-49ba-BF7F-4379FB36D306}]
      If channel is non-coherent [/cover] */
      if(Coherency == PWM_17_GTMCCU6_NON_COHERENT)
      {
        /* [cover parentID={E45595EE-04C8-4168-ACE4-69E08877FA36}]
        Enter critical section [/cover] */
        SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
        /* Note - UPEN update is disabled, Hence no update of Compare match
        registers by shadow registers */
        /* [cover parentID={753253D0-D44C-46c5-89B2-86643945E7EE}]
        Update compare match register with period and duty cycle [/cover] */
        AtomChannelRegPtr->CM0.U = Period;
        AtomChannelRegPtr->CM1.U = Dutycycle;

        /* [cover parentID={3D40FAE2-C391-4428-BF68-86A5AE9DD83F}]
        Exit critical section [/cover] */
        SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
      }
      else
      {
        /* [cover parentID={9D534BAC-627B-4663-8F24-FF1715C5932F}]
        Start critical section [/cover] */
        SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
        /* [cover parentID={5C5218EB-C334-44cc-98A9-8953205C5DF0}]
         Disable shadow transfer [/cover] */
        Mcu_17_Gtm_AtomChUpdateEnDis(TimerModuleNumber, TimerChannelNumber, \
                                     MCU_GTM_TIMER_UPDATE_DISABLE);
        /* [cover parentID={AE0D53DA-5820-4e54-B29A-F163282BDE29}]
        Update shadow register with period and duty [/cover] */
        AtomChannelRegPtr->SR0.U = Period;
        AtomChannelRegPtr->SR1.U = Dutycycle;
        /* [cover parentID={EAF5CC75-DC63-4556-8845-3FAFD8D3FA4E}]
        Enable shadow trasfer [/cover] */
        Mcu_17_Gtm_AtomChUpdateEnDis(TimerModuleNumber, TimerChannelNumber, \
                                     MCU_GTM_TIMER_UPDATE_ENABLE);
        /* [cover parentID={DFBBBA11-0C31-4f6a-A93F-1CA8DB6EDF31}]
        Exit critical section [/cover] */
        SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
      }
    }
    else
    {
      /* [cover parentID={4C8DDEB5-1F50-4419-BCCA-1F17BD9A8C21}]
      IF channel is non-coherent [/cover] */
      if(Coherency == PWM_17_GTMCCU6_NON_COHERENT)
      {
        /* [cover parentID={D512BC37-B5EE-49e5-B3AC-E332F34C3642}]
        Enter critical section [/cover] */
        SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
        /* Note - UPEN update is disabled, Hence no update of Compare match
        registers by shadow registers */
        /* [cover parentID={162CF64A-8154-4738-A874-32F8519F1041}]
        Update compare match register with 0 duty cycle and period 
        [/cover] */
        AtomChannelRegPtr->CM1.U = 0U;
        AtomChannelRegPtr->CM0.U = Period;
        /* [cover parentID={D86981C9-9FC9-4836-A957-7180052EABF2}]
        Exit critical section [/cover] */
        SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
      }
      else
      {
        /* [cover parentID={93125A14-377A-4b8e-9B1C-DF913AD00D28}]
        Enter critical section [/cover] */
        SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
        /* [cover parentID={0A9E9CA1-F391-4ad0-A8CB-91DC5EA21B16}]
        Update shadow registers with 0% duty cycle and period [/cover] */
        Mcu_17_Gtm_AtomChUpdateEnDis(TimerModuleNumber, TimerChannelNumber, \
                                     MCU_GTM_TIMER_UPDATE_DISABLE);
        AtomChannelRegPtr->SR1.U = 0U;
        AtomChannelRegPtr->SR0.U = Period;
        Mcu_17_Gtm_AtomChUpdateEnDis(TimerModuleNumber, TimerChannelNumber, \
                                     MCU_GTM_TIMER_UPDATE_ENABLE);
        /* [cover parentID={F6322FC6-7E60-446f-94AD-F2ED323CFC7A}]
        Exit critical section [/cover] */
        SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
      }
    }
  }
  /* Reset type is 1 for Fixed period shifted or Center-aligned channels */
  else
  {
    /* [cover parentID={46F9F919-0365-4e5b-B2A8-B7C21A8FD10B}]
    If channel is non-coherent [/cover] */
    if(Coherency == PWM_17_GTMCCU6_NON_COHERENT)
    {
      /* [cover parentID={94A6C931-F9BC-4824-BAE8-A4243FCA008F}]
      If period is zero duty is set to zero [/cover] */
      /* [cover parentID={94A6C931-F9BC-4824-BAE8-A4243FCA008F}]
      If duty cycle equals 0 [/cover] */
      if(Dutycycle == 0U)
      {
        /* [cover parentID={610460FA-1F80-47c7-A13F-B923764E516D}]
        Enter critical section [/cover] */
        SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
        /* Note - UPEN update is disabled, Hence no update of Compare match
        registers by shadow registers */
        /* [cover parentID={2601B958-B841-48bb-BFB7-5F94C106B2D7}]
        Update compare match register with max period & 0% duty value[/cover]*/
        AtomChannelRegPtr->CM0.U = PWM_MAX_TIMER;
        AtomChannelRegPtr->CM1.U = 0U;
        
        /* [cover parentID={131F9121-B3B5-4307-8659-1B248F734198}]
        Exit critical section [/cover] */
        SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
      }
      else if (Dutycycle == Period)
      {
        /* [cover parentID={9A303E75-F114-4471-BC2E-5E5C6046255B}]
        If duty cycle equals period [/cover] */
        /* [cover parentID={AAC1C74B-FDE0-4e46-A521-A329D2244F7F}]
        Enter critical section [/cover] */
        SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
        /* Note - UPEN update is disabled, Hence no update of Compare match
        registers by shadow registers */
        /* [cover parentID={6B44606E-43A1-4e3b-9ACC-BD3B30DD6733}]
        Update compare match register with 0 period & 100% duty value[/cover]*/
        AtomChannelRegPtr->CM0.U = 0U;
        AtomChannelRegPtr->CM1.U = PWM_MAX_TIMER;
        /* [cover parentID={4B8E269A-3F32-461c-8594-238450FBCB23}]
        Exit critical section [/cover] */
        SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
      }
      else
      {
        /* [cover parentID={FBE8EF51-EEA5-433c-B494-27599622CB31}]
        Start critical section [/cover] */
        SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
        /* Note - UPEN update is disabled, Hence no update of Compare match
        registers by shadow registers */
        AtomChannelRegPtr->CM0.U = Shift;
        /* MISRA2012_RULE_1_3_JUSTIFICATION: Condition of executing this case
          when period=0 will never occur, Because when period is 0 duty is set
          to 0 in GetAbsvaledge API, and if duty is 0 if(Dutycycle == 0U)
          case is executed.*/
        /* [cover parentID={DF2BB8C5-52E4-4aa3-8ED0-B738452C76E2}]
        Update compare match register with period and duty [/cover] */
        AtomChannelRegPtr->CM1.U = (Shift + Dutycycle) % Period;
        /* [cover parentID={FF5AC29B-0887-47c5-BD45-D178180BF62E}]
        Exit critical section [/cover] */
        SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
      }
    }
    else
    {
      /* [cover parentID={2BB5803A-2EF7-4967-9B7A-213E3F4928FE}]
      If period is zero duty is set to zero [/cover] */
      if(Dutycycle == 0U)
      {
        /* [cover parentID={C077DF43-CB4A-4950-A35E-A6527A60D620}]
        Start critical section [/cover] */
        SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
        
        /* Disable shadow transfer */
        Mcu_17_Gtm_AtomChUpdateEnDis(TimerModuleNumber, TimerChannelNumber, \
                                     MCU_GTM_TIMER_UPDATE_DISABLE);
        /* [cover parentID={96FA6C46-7074-4b14-9542-2FD41A11D480}]
        Update period and duty shadow register to set 0%duty. [/cover] */
        AtomChannelRegPtr->SR0.U = PWM_MAX_TIMER;
        AtomChannelRegPtr->SR1.U = 0U;
        
        /* Enable shadow transfer */
        Mcu_17_Gtm_AtomChUpdateEnDis(TimerModuleNumber, TimerChannelNumber, \
                                     MCU_GTM_TIMER_UPDATE_ENABLE);
        /* [cover parentID={A029EF85-723A-4571-8B89-FF80263D616E}]
        Exit critical section [/cover] */
        SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
      }
      else if (Dutycycle == Period)
      {
        /* [cover parentID={121FF107-FA34-4fd3-95F1-52A93D34D387}]
        100% duty [/cover] */
        /* [cover parentID={9D72DDE0-8DCB-4746-A705-CDD3E945E65A}]
        Enter critical sessaion [/cover] */
        SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
        /* [cover parentID={D3E7FF66-E62A-471b-AB5A-8C49761476B6}]
        Disable shadow transfer [/cover] */
        Mcu_17_Gtm_AtomChUpdateEnDis(TimerModuleNumber, TimerChannelNumber, \
                                     MCU_GTM_TIMER_UPDATE_DISABLE);
        /* [cover parentID={9426AF4D-54CB-4bd6-BBE3-74890F348E13}]
        Update shadow register wih period and duty [/cover] */
        AtomChannelRegPtr->SR0.U = 0U;
        AtomChannelRegPtr->SR1.U = PWM_MAX_TIMER;
        /* [cover parentID={3B7CAA33-85F6-4c04-9814-4A6A01DCE799}]
        Enable shadow transfer [/cover] */
        Mcu_17_Gtm_AtomChUpdateEnDis(TimerModuleNumber, TimerChannelNumber, \
                                     MCU_GTM_TIMER_UPDATE_ENABLE);
        /* [cover parentID={A7E7E35B-B12E-4969-93A6-F25BCCA40C05}]
        Exit Critical section [/cover] */
        SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
      }
      else
      {
        /* [cover parentID={11DDE221-746E-48ce-8587-94B725E9A4D0}]
        Enter critical section [/cover] */
        SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
        /* [cover parentID={ED3ADD0D-FDE6-4a21-9CDB-8E342A48D45D}]
        Enable shadow transfer [/cover] */
        Mcu_17_Gtm_AtomChUpdateEnDis(TimerModuleNumber, TimerChannelNumber, \
                                     MCU_GTM_TIMER_UPDATE_DISABLE);
        /* [cover parentID={CEF7F26B-CEF3-4946-B14C-EB1521012147}]
        Update shadow register with period and duty [/cover] */
        AtomChannelRegPtr->SR0.U = Shift;
        /* MISRA2012_RULE_1_3_JUSTIFICATION: Condition of executing this case
          when period=0 will never occur, Because when period is 0 duty is set
          to 0 in GetAbsvaledge API, and if duty is 0 if(Dutycycle == 0U)
          case is executed.*/
        AtomChannelRegPtr->SR1.U = (Shift + Dutycycle) % Period;
        /* [cover parentID={7F00E0F0-C3FE-48f7-8AB9-423B854C5355}]
        Disable shadow transfer [/cover] */
        Mcu_17_Gtm_AtomChUpdateEnDis(TimerModuleNumber, TimerChannelNumber, \
                                     MCU_GTM_TIMER_UPDATE_ENABLE);
        SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
      }
    }
  }
}
#endif
#endif

#if ((PWM_17_GTMCCU6_SET_PERIOD_AND_DUTY_API == STD_ON) && \
     ((PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON) || \
     (PWM_17_GTMCCU6_DEV_ERROR_DETECT == STD_ON)))
/******************************************************************************
** Syntax : LOCAL_INLINE uint32 Pwm_lVerUnInitChanAndPer                     **
**                    (                                                      **
**                      const uint8 ServiceID,                               **
**                      const Pwm_17_GtmCcu6_ChannelType ChannelNumber,      **
**                      const uint8 CoreId                                   **
**                    )                                                      **
** Service ID:        none                                                   **
**                                                                           **
** Sync/Async:        Synchronous                                            **
**                                                                           **
** Reentrancy:        Reentrant                                              **
**                                                                           **
** Parameters (in):   Service ID    : Service ID of an API                   **
**                    ChannelNumber : PWM Channel number                     **
**                    CoreId : Core Number                                   **
**                                                                           **
** Parameters (out):  none                                                   **
**                                                                           **
** Return value:      PWM_ERROR_FOUND: DET or Safety error occurred          **
**                    0: No DET or Safety error occurred                     **
**                                                                           **
** Description :      Service to verify DET or Safety error for UnInit,      **
**                    validity of channel number and non-variable period     **
** Traceability :     [cover parentID={6A8348F5-CDDB-4da7-BA1E-DD6852BA4E25}]**
**                       [/cover]                                            **
******************************************************************************/
LOCAL_INLINE uint32 Pwm_lVerUnInitChanAndPer
(
  const uint8 ServiceID,
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
)
{
  uint32 ErrorFlag;
  Pwm_17_GtmCcu6_ChannelClassType ChannelKind;
  uint16 LocalPwmChannelInfo;
  uint8  PwmCoreChIdx;

  /* [cover parentID={F8EC405D-E4CB-42d0-B8ED-453134C64903}]
  Verify whether Init has been called [/cover] */
  /* [cover parentID={3C5990B4-247B-4ffc-A510-BC09BCE9111A}]
  Check module initialized DET or SAFETY error [/cover] */
  ErrorFlag = Pwm_lVerUnInit(ServiceID, CoreId);
  /* [cover parentID={3C5990B4-247B-4ffc-A510-BC09BCE9111A}]
  If the module is initialized [/cover] */
  if (ErrorFlag != PWM_ERROR_FOUND)
  {
    /* [cover parentID={678A47DD-1561-4009-8545-235C416BE84D}]
    Verify whether Invalid channel number has been sent [/cover] */
    ErrorFlag = Pwm_lVerChannel(ServiceID, ChannelNumber, CoreId);
    /* [cover parentID={284B586B-9AFF-46c9-8B2A-57BA2553569C}]
    If the channel number is valid [/cover] */
    if (ErrorFlag != PWM_ERROR_FOUND)
    {
      PwmCoreChIdx = Pwm_ConfigPtr->PwmChannelIdxmapPtr[ChannelNumber];
      LocalPwmChannelInfo = Pwm_ConfigPtr->PwmCoreAdd[CoreId]->\
                        Pwm_ChannelConfigPtr[PwmCoreChIdx].PwmChannelInfo;
      /* Get the type of channel used */
      ChannelKind = Pwm_lChanClass(LocalPwmChannelInfo);
      /* Verify whether channel provided for non variable period */
      /* [cover parentID={72D3BC43-1F7C-4ed4-8B6A-CB70384771FE}]
      If the channel provided is not for variable period [/cover] */
      if ( PWM_17_GTMCCU6_VARIABLE_PERIOD != ChannelKind )
      {
        /* [cover parentID={7EEF608C-2E95-426d-9A4A-D0AB916559D3}]
        Report DET error [/cover] */
        Pwm_lReportError(ServiceID, PWM_17_GTMCCU6_E_PERIOD_UNCHANGEABLE);
        /* [cover parentID={8A1EE754-BA60-41ab-922F-10E619476457}]
        Set Error Flag [/cover] */
        ErrorFlag = PWM_ERROR_FOUND;
      }
    }
  }
  return ErrorFlag;
}
#endif

#if ((PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON) && \
     ((PWM_17_GTMCCU6_SET_PERIOD_AND_DUTY_API == STD_ON) || \
     (PWM_17_GTMCCU6_SET_DUTY_CYCLE_API == STD_ON)))
/******************************************************************************
** Syntax : LOCAL_INLINE uint32 Pwm_lDutyRangeCheck                          **
**                    (                                                      **
**                      const uint8 ServiceID,                               **
  **                    const uint32 DutyCycle,                              **
**                      const Pwm_17_GtmCcu6_ChannelType ChannelNumber,      **
**                      const uint8 CoreId                                   **
**                    )                                                      **
** Service ID:        none                                                   **
**                                                                           **
** Sync/Async:        Synchronous                                            **
**                                                                           **
** Reentrancy:        Reentrant                                              **
**                                                                           **
** Parameters (in):   Service ID   :Service ID of an API                     **
**                    DutyCycle : Duty Cycle for a PWM channel               **
**                    ChannelNumber: PWM channel number                      **
*8                    Core ID      : Core Number                             **
**                                                                           **
** Parameters (out):  none                                                   **
**                                                                           **
** Return value:      Error status                                           **
**                                                                           **
** Description :      Service to verify Range for Duty parameter             **
**                                                                           **
** Traceability :     [cover parentID={2744C660-A31D-4c9a-8469-5FF757C85838}]**
**                      [/cover]                                             **
******************************************************************************/
LOCAL_INLINE uint32 Pwm_lDutyRangeCheck
(
  const uint8 ServiceID,
  const uint32 DutyCycle,
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
)
{
  uint32 ErrorFlag;
  #if (PWM_17_GTMCCU6_DUTY_SHIFT_IN_TICKS == STD_ON)
  #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
  uint8  PwmCoreChIdx;
  const Pwm_17_GtmCcu6_ChannelConfigType  *PwmChannelCfgPtr;
  uint8 PwmTimerType;
  #endif
  #endif

  ErrorFlag = (uint32)0;
  #if (PWM_17_GTMCCU6_DUTY_SHIFT_IN_TICKS == STD_OFF)
  /* [cover parentID={6410F43A-3CE1-4778-B74A-D9155014AD7B}]
  Is duty shift in ticks is not enabled [/cover] */
  /* [cover parentID={D5560F07-4C0F-45be-B224-A77C2374692F}]
  If duty cycle is more than maximum duty [/cover] */
  if(DutyCycle > (uint32)PWM_MAX_DUTY)
  {
    ErrorFlag = PWM_ERROR_FOUND;
  }
  UNUSED_PARAMETER(ChannelNumber);
  UNUSED_PARAMETER(CoreId);
  #else
  /* [cover parentID={F5B990AF-7F49-43ef-A046-623421FA39D0}]
  Is duty shift in ticks is enabled [/cover] */
  #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
  PwmCoreChIdx = Pwm_ConfigPtr->PwmChannelIdxmapPtr[ChannelNumber];
  PwmChannelCfgPtr = &(Pwm_ConfigPtr->PwmCoreAdd\
                       [CoreId]->Pwm_ChannelConfigPtr[PwmCoreChIdx]);
  PwmTimerType  = PwmChannelCfgPtr->PwmTimerUsed;

  if(PwmTimerType == PWM_17_GTMCCU6_GTM_TIMER)
  {
    const Mcu_17_Gtm_TomAtomChConfigType *PwmGtmTimerPtr;
    Mcu_17_Gtm_TimerOutType PwmGtmTimerType;

    /* [cover parentID={7511CDF3-FAB4-4205-86A6-E82F3AA0BE29}]
    If GTM timer is used [/cover] */
    /* MISRA2012_RULE_11_5_JUSTIFICATION: PwmTimerPtr is of
    type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
    by violating this MISRA rule.*/
    /* MISRA2012_RULE_11_3_JUSTIFICATION: PwmTimerPtr is of
    type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
    by violating this MISRA rule.*/
    PwmGtmTimerPtr = (const Mcu_17_Gtm_TomAtomChConfigType*)\
                     PwmChannelCfgPtr->PwmTimerPtr;
    PwmGtmTimerType = PwmGtmTimerPtr->TimerType;
    /* [cover parentID={15A2AE53-1390-4d4d-B4A0-94D3711D9C79}]
    If used timer is TOM and duty cycele is greater than maximum TOM
    timer value [/cover] */
    if(PwmGtmTimerType == MCU_GTM_TIMER_TOM)
    {
      if(DutyCycle > PWM_MAX_TIMER_TOM)
      {
        ErrorFlag = PWM_ERROR_FOUND;
      }
    }
    else
    {
      /* [cover parentID={EBA53BF0-03DE-41e0-BC2E-7116E2ECAE52}]
      If duty cycele is greater than maximum ATOM timer value [/cover] */
      if(DutyCycle > PWM_MAX_TIMER)
      {
        ErrorFlag = PWM_ERROR_FOUND;
      }
    }
  }
  else
  #else
  UNUSED_PARAMETER(CoreId);
  UNUSED_PARAMETER(ChannelNumber);
  #endif
  {
    /* [cover parentID={2EEDF3F1-D9A3-4995-89E2-C5E6F9F9C354}]
    If duty cycle is greater than maximum CCU6 timer value [/cover] */
    if(DutyCycle > PWM_MAX_TIMER_CCU6)
    {
      ErrorFlag = PWM_ERROR_FOUND;
    }
  }
  #endif
  /* [cover parentID={4B59C4E6-BA07-4aef-81EA-116F768B00A9}]
  If error flag is set [/cover] */
  if(ErrorFlag == PWM_ERROR_FOUND)
  {
    /* [cover parentID={C66B0F65-0182-4484-82AF-BFF7FB651756}]
    Report safety error [/cover] */
    Mcal_ReportSafetyError(
      PWM_17_GTMCCU6_MODULE_ID,
      PWM_17_GTMCCU6_INSTANCE_ID,
      ServiceID,
      PWM_17_GTMCCU6_E_PARAM_DUTY);
  }
  return ErrorFlag;
}

#endif

#if ((PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON) && \
     (PWM_17_GTMCCU6_SET_PERIOD_AND_DUTY_API == STD_ON))
/******************************************************************************
** Syntax : LOCAL_INLINE uint32 Pwm_lDutyPeriodRangeCheck                    **
**                    (                                                      **
**                      const uint8 ServiceID,                               **
**                      const uint32 DutyCycle,                              **
**                      const uint32 Period,                                 **
**                      const Pwm_17_GtmCcu6_ChannelType ChannelNumber,      **
**                      const uint8 CoreId                                   **
**                    )                                                      **
** Service ID:        none                                                   **
**                                                                           **
** Sync/Async:        Synchronous                                            **
**                                                                           **
** Reentrancy:        Reentrant                                              **
**                                                                           **
** Parameters (in):   Service ID    : Service ID of an API                   **
**                    DutyCycle : Duty Cycle for a PWM channel               **
**                    Period    : New period for the channel                 **
**                    ChannelNumber: Logical Channel ID                      **
*8                    Core ID      : Core Number                             **
**                                                                           **
** Parameters (out):  none                                                   **
**                                                                           **
** Return value:      Error status                                           **
**                                                                           **
** Description :      Service to verify Range of Duty and Period parameter   **
**                                                                           **
** Traceability :     [cover parentID={4CB11E54-93F1-4678-A50A-C5C0BC910A4F}]**
**                      [/cover]                                             **
******************************************************************************/
LOCAL_INLINE uint32 Pwm_lDutyPeriodRangeCheck
(
  const uint8 ServiceID,
  const uint32 DutyCycle,
  const uint32 Period,
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
)
{
  uint32 ErrorFlag = PWM_BIT_RESET;
  /* [cover parentID={94E49F96-7ACC-422b-8923-7CC40871BE76}]
  Check duty range [/cover] */
  ErrorFlag = Pwm_lDutyRangeCheck(ServiceID, DutyCycle, ChannelNumber, \
                                  (uint8)CoreId);
  /* [cover parentID={126247FA-BC49-4ca4-BB77-3C724486E6DC}]
  If no errors are reported [/cover] */
  if (ErrorFlag != PWM_ERROR_FOUND)
  {
    /* [cover parentID={36C5292C-A652-49b1-9A58-0665D635EEF3}]
    Check period range [/cover] */
    /* Verify period range */
    ErrorFlag = Pwm_lPeriodRangeCheck(ServiceID, Period, ChannelNumber, \
                                      (uint8)CoreId);
  }
  return ErrorFlag;
}
/******************************************************************************
** Syntax : LOCAL_INLINE uint32 Pwm_lPeriodRangeCheck                        **
**                    (                                                      **
**                      const uint8 ServiceID,                               **
  **                    const uint32 Period,                                 **
**                      const Pwm_17_GtmCcu6_ChannelType ChannelNumber,      **
**                      const uint8 CoreId                                   **
**                    )                                                      **
** Service ID:        none                                                   **
**                                                                           **
** Sync/Async:        Synchronous                                            **
**                                                                           **
** Reentrancy:        Reentrant                                              **
**                                                                           **
** Parameters (in):   Service ID    : Service ID of an API                   **
**                    Period : Period for a PWM channel                      **
**                    ChannelNumber: Logical Channel ID                      **
*8                    Core ID      : Core Number                             **
**                                                                           **
** Parameters (out):  none                                                   **
**                                                                           **
** Return value:      Error status                                           **
**                                                                           **
** Description :      Service to verify Range  for Period parameter          **
**                                                                           **
** Traceability  :   [cover parentID={5EEC8309-AA84-4f16-AD6E-75EAC9B2F38A}] **
**                    [/cover]                                               **
******************************************************************************/
LOCAL_INLINE uint32 Pwm_lPeriodRangeCheck
(
  const uint8 ServiceID,
  const uint32 Period,
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
)
{
  uint32 ErrorFlag = 0U;
  #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
  uint8  PwmCoreChIdx;
  const Pwm_17_GtmCcu6_ChannelConfigType  *PwmChannelCfgPtr;
  uint8 PwmTimerType;
  #endif

  #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
  PwmCoreChIdx = Pwm_ConfigPtr->PwmChannelIdxmapPtr[ChannelNumber];
  PwmChannelCfgPtr = &(Pwm_ConfigPtr->PwmCoreAdd\
                       [CoreId]->Pwm_ChannelConfigPtr[PwmCoreChIdx]);
  PwmTimerType = PwmChannelCfgPtr->PwmTimerUsed;
  /* [cover parentID={4A2A822B-F37F-46a1-9716-C578745F3B3C}]
  Extract module, channel and group numbers and GTM timer type [/cover] */
  if(PwmTimerType == PWM_17_GTMCCU6_GTM_TIMER)
  {
    const Mcu_17_Gtm_TomAtomChConfigType    *PwmGtmTimerPtr;
    Mcu_17_Gtm_TimerOutType PwmGtmTimerType;

    /* [cover parentID={5FA80461-A77C-4113-A6C1-FA75AA3FCCFC}]
    If GTM timer is used [/cover] */
    /* MISRA2012_RULE_11_5_JUSTIFICATION: PwmTimerPtr is of
    type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
    by violating this MISRA rule.*/
    /* MISRA2012_RULE_11_3_JUSTIFICATION: PwmTimerPtr is of
    type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
    by violating this MISRA rule.*/
    PwmGtmTimerPtr = (const Mcu_17_Gtm_TomAtomChConfigType*)\
                     PwmChannelCfgPtr->PwmTimerPtr;
    PwmGtmTimerType = PwmGtmTimerPtr->TimerType;
    /* [cover parentID={D4A1AADC-7B8D-4cd1-AFA8-013C10DD3658}]
    If used timer is TOM and period is greater than maximum TOM timer value
    [/cover] */
    if(PwmGtmTimerType == MCU_GTM_TIMER_TOM)
    {
      if(Period > PWM_MAX_TIMER_TOM)
      {
        /* [cover parentID={593DE00C-CD30-45e1-A84A-8712F26112A4}]
        Set error flag [/cover] */
        ErrorFlag = PWM_ERROR_FOUND;
      }
    }
    else
    {
      /* [cover parentID={B430264A-C378-4984-A602-6C725FE2CD7A}]
      If period is greater than maximum ATOM timer value [/cover] */
      if(Period > PWM_MAX_TIMER)
      {
        /* [cover parentID={B33B2656-029B-4a27-ADD2-C714A1CE47C3}]
        Set error flag [/cover] */
        ErrorFlag = PWM_ERROR_FOUND;
      }
    }
  }
  else
  #else
  UNUSED_PARAMETER(CoreId);
  UNUSED_PARAMETER(ChannelNumber);
  #endif
  {
    /* [cover parentID={278C0D51-4811-4d60-84F4-897488CB548E}]
    If duty cycle is greater than maximum CCU6 timer value [/cover] */
    if(Period > PWM_MAX_TIMER_CCU6)
    {
      /* [cover parentID={EF1C84F9-C187-4c21-ACE5-6C09DA1FF167}]
      Set error flag [/cover] */
      ErrorFlag = PWM_ERROR_FOUND;
    }
  }
  /* [cover parentID={A3FE55E5-735B-427e-AF74-E2D18A359563}]
  If error flag is set [/cover] */
  if(ErrorFlag == PWM_ERROR_FOUND)
  {
    /* [cover parentID={760B2BDA-D5F3-48c1-B98D-D285538FC3CB}]
    Report safety error [/cover] */
    Mcal_ReportSafetyError(
      PWM_17_GTMCCU6_MODULE_ID,
      PWM_17_GTMCCU6_INSTANCE_ID,
      ServiceID,
      PWM_17_GTMCCU6_E_PARAM_PERIOD);
  }
  /* [cover parentID={3063FA71-ECA1-4aad-BD29-EEDE10EDC0C0}]
  Return error flag [/cover] */
  return ErrorFlag;
}
#endif

#if (PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON)
/******************************************************************************
** Syntax :         LOCAL_INLINE void Pwm_lEnableQmNotif                     **
**                  (                                                        **
**                    const Pwm_17_GtmCcu6_ChannelClassType ChannelKind,     **
**                    const Pwm_17_GtmCcu6_ChannelType ChannelNumber,        **
**                    const Pwm_17_GtmCcu6_EdgeNotificationType Notification,**
**                    const uint8 CoreId                                     **
**                  )                                                        **
** Service ID:        none                                                   **
**                                                                           **
** Sync/Async:        Synchronous                                            **
**                                                                           **
** Reentrancy:        Reentrant                                              **
**                                                                           **
** Parameters (in):   ChannelKind :Type of channel                           **
**                    ChannelNumber: Numeric identifier of the PWM channel   **
**                    Notification : Type of notification requested          **
**                    CoreId : Core Number                                   **
** Parameters (out):  none                                                   **
**                                                                           **
** Return value:      none                                                   **
**                                                                           **
** Description :      Function to Set the global variables for notification  **
*                     and enable notification                                **
**                                                                           **
** Traceability :     [cover parentID={1C2304F1-C557-4a93-B755-7FBBFF70B60F}]**
**                   [/cover]                                                **
*****************************************************************************/
LOCAL_INLINE void Pwm_lEnableQmNotif(
  const Pwm_17_GtmCcu6_ChannelClassType ChannelKind,
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const Pwm_17_GtmCcu6_EdgeNotificationType Notification,
  const uint8 CoreId
)
{
  const Pwm_17_GtmCcu6_ChannelStatusType *LocalPwmChanStatusPtr;
  uint32 Period;
  #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
  uint8 PwmTimerType;
  const Pwm_17_GtmCcu6_ChannelConfigType *PwmChannelCfgPtr;
  const Pwm_17_GtmCcu6_CoreConfigType *PwmCorePtr;

  PwmCorePtr = Pwm_ConfigPtr->PwmCoreAdd[CoreId];
  PwmChannelCfgPtr = &(PwmCorePtr->Pwm_ChannelConfigPtr[ChannelNumber]);
  PwmTimerType = PwmChannelCfgPtr->PwmTimerUsed;
  #endif
  LocalPwmChanStatusPtr = Pwm_CoreChannelStatus[CoreId];
  Period = LocalPwmChanStatusPtr[ChannelNumber].Pwm_CurrentPeriodVal;
  /* [cover parentID={BEB8C8A8-AE9E-4fc5-BF7C-63F0549C41ED}]
  If channel kind is Variable Period and period is zero [/cover] */
  if((ChannelKind == PWM_17_GTMCCU6_VARIABLE_PERIOD) && (Period == 0U))
  {
    /* Clear the interrupt if duty is 0% or 100%*/
    /* [cover parentID={1CF2990A-DFD5-477b-877D-0E54D5FEE432}]
    Disable Notification (GTM/CCu6), and clear notification status [/cover] */
    /* [cover parentID={D4A10067-A583-439d-81E3-4897720D157F}][/cover] */
    #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
    if(PwmTimerType == PWM_17_GTMCCU6_GTM_TIMER)
    {
      /* Disable notification if duty is 0% or 100% */
      Pwm_lGtmIrqModify(ChannelNumber, 0U, (uint8)CoreId);
    }
    else
    #endif
    {
      #if (PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
      /* Disable notification if duty is 0% or 100% */
      Pwm_lCcu6IrqModify(ChannelNumber, 0U, (uint8)CoreId);
      #endif
    }
    /* Clear notification status in global register */
    /*MISRA2012_RULE_2_2_JUSTIFICATION: function Pwm_lSetDuty_0_Or_100_Status
      is not empty,  macro Mcal_SetBitAtomic is used to set notification
      status hence no dead code. */
    Pwm_lClearNotificationStatus(ChannelNumber, (uint8)CoreId);
    /* Set the flag in global register to indicate the duty is 0% or 100%*/
    /*MISRA2012_RULE_2_2_JUSTIFICATION: function Pwm_lSetDuty_0_Or_100_Status
       is not empty,  macro Mcal_SetBitAtomic is used to set notification
       status hence no dead code. */
    Pwm_lSetDuty_0_Or_100_Status(ChannelNumber, (uint8)CoreId);
  }
  else
  {
    /* [cover parentID={BF3FD985-9FE8-497c-9F85-4ACB31D02C75}]
    Is notification for 0% or 100% enabled [/cover] */
    #if (PWM_17_GTMCCU6_NOTIF_FOR_100_0_ENABLE == STD_ON)
    /* [cover parentID={020EE2D0-217F-4ae4-8A8A-0C39F6BB4238}]
    If channel kind is neither fixed period shifted nor fixed period center aligned
    [/cover] */
    if ((ChannelKind != PWM_17_GTMCCU6_FIXED_PERIOD_SHIFTED) && \
        (ChannelKind != PWM_17_GTMCCU6_FIXED_PERIOD_CENTER_ALIGNED))
    {
      /* MISRA2012_RULE_2_2_JUSTIFICATION: function Pwm_lSetNotificationStatus
       is not empty,  macro Mcal_SetBitAtomic is used to set notification status
       hence no dead code. */
      /* [cover parentID={F831B842-0DDF-4b1a-B7F5-C3CA93D5A93A}]
      Enable or disable interrupt GTM/CCu6 [/cover] */
      /*Set the notification status in global channel variable*/
      Pwm_lSetNotificationStatus(ChannelNumber, CoreId);

      #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
      if(PwmTimerType == PWM_17_GTMCCU6_GTM_TIMER)
      {
        Pwm_lGtmIrqModify(ChannelNumber, Notification, CoreId);
      }
      else
      #endif
      {
        #if (PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
        /* Disable Interrupts for each channel */
        Pwm_lCcu6IrqModify(ChannelNumber, Notification, (uint8)CoreId);
        #endif
      }
    }
    else
    {
      if ((LocalPwmChanStatusPtr[ChannelNumber].Pwm_GlobChn\
           & PWM_DUTY_0_OR_100_UPDATE_MASK) == 0U)
      {
        /* [cover parentID={2076A84E-89EA-472d-8402-279812939B53}]
        If duty is not 0% or 100% [/cover] */
        /* MISRA2012_RULE_2_2_JUSTIFICATION: function Pwm_lSetNotificationStatus
         is not empty,  macro Mcal_SetBitAtomic is used to set notification
         status hence no dead code. */
        /* [cover parentID={7CF17F9A-AFB3-4f1b-8E17-E77F89D72CCA}]
        Set notification status in global channel variable [/cover] */
        Pwm_lSetNotificationStatus(ChannelNumber, CoreId);
        #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
        if(PwmTimerType == PWM_17_GTMCCU6_GTM_TIMER)
        {
          Pwm_lGtmIrqModify(ChannelNumber, Notification, CoreId);
        }
        else
        #endif
        {
          #if (PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
          /* Disable/Enable Interrupts for each channel */
          Pwm_lCcu6IrqModify(ChannelNumber, Notification, (uint8)CoreId);
          #endif
        }
      }
    }
    #else
    /* [cover parentID={74679180-DB71-45e7-AE4C-CD6F1E5F204A}]
    Is notification for 0% or 100% duty not enabled [/cover] */
    /* [cover parentID={F6A3586C-E814-44ac-B9AD-DF14A4EB12BE}]
    If duty is not 0% or 100% [/cover] */
    if ((LocalPwmChanStatusPtr[ChannelNumber].Pwm_GlobChn \
         & PWM_DUTY_0_OR_100_UPDATE_MASK) == 0U)
    {
      /* MISRA2012_RULE_2_2_JUSTIFICATION: function Pwm_lSetNotificationStatus
         is not empty,  macro Mcal_SetBitAtomic is used to set notification
         status hence no dead code. */
      /* [cover parentID={F7441612-B017-4055-97FF-799E4EF1F1EF}]
      Set notification status in global channel variable [/cover] */
      Pwm_lSetNotificationStatus(ChannelNumber, (uint8)CoreId);

      /* [cover parentID={1B422C02-CB0C-4be5-A104-26BD2D1A6178}]
      Is the timer GTM [/cover] */
      #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
      if(PwmTimerType == PWM_17_GTMCCU6_GTM_TIMER)
      {
        /* [cover parentID={22D926F9-AF76-47dc-A3DA-1354D4451176}]
        Disable or enable interrupts GTM/CCu6 [/cover] */
        Pwm_lGtmIrqModify(ChannelNumber, Notification, CoreId);
      }
      else
      #endif
      {
        #if (PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
        /* Disable/Enable Interrupts for each channel */
        Pwm_lCcu6IrqModify(ChannelNumber, Notification, (uint8)CoreId);
        #endif
      }
    }
    /* To remove unused param warning */
    UNUSED_PARAMETER(ChannelKind);
    #endif
  }
}
#endif
#if ((((PWM_17_GTMCCU6_DE_INIT_API == STD_ON)&& \
     (PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON))|| \
     (PWM_17_GTMCCU6_SET_OUTPUT_TO_IDLE_API == STD_ON))&& \
     (PWM_17_GTMCCU6_DUTY_SHIFT_IN_TICKS == STD_ON))
/******************************************************************************
** Syntax :         LOCAL_INLINE uint32 Pwm_lMaxDuty                         **
**                    (                                                      **
**                      const uint8 ChannelIdx,                              **
**                      const uint8 CoreId                                   **
**                    )                                                      **
** Service ID:        none                                                   **
**                                                                           **
** Sync/Async:        Synchronous                                            **
**                                                                           **
** Reentrancy:        Reentrant for different channels                       **
**                                                                           **
** Parameters (in):                                                          **
**                    ChannelIdx: Numeric identifier of the PWM channel      **
**                    CoreId : Core Number                                   **
**                                                                           **
**                                                                           **
** Parameters (out):  None                                                  **
**                                                                           **
** Return value:      Maximum duty for the requested channel                 **
**                                                                           **
** Description :      Function to get the maximum duty for the requested     **
**                    channel                                                **
** Traceability   :  [cover parentID={98FAAD04-0960-481e-A9B9-622218C02426}] **
**                     [/cover]                                              **
******************************************************************************/
LOCAL_INLINE uint32 Pwm_lMaxDuty(uint8 ChannelIdx, uint8 CoreId)
{
  uint32 Duty = 0U;
  #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
  uint8 PwmTimerType;
  const Pwm_17_GtmCcu6_ChannelConfigType *LocalPwmChanPtr;

  LocalPwmChanPtr = &(Pwm_ConfigPtr->PwmCoreAdd\
                      [CoreId]->Pwm_ChannelConfigPtr[ChannelIdx]);
  PwmTimerType = LocalPwmChanPtr->PwmTimerUsed;
  /* [cover parentID={AFF9CD9F-A8E5-45ca-9292-F5232BAD3A93}]
  If timer used is GTM [/cover] */
  if(PwmTimerType == PWM_17_GTMCCU6_GTM_TIMER)
  {
    const Mcu_17_Gtm_TomAtomChConfigType *PwmGtmTimerPtr;
    Mcu_17_Gtm_TimerOutType PwmGtmTimerType;
    /* MISRA2012_RULE_11_5_JUSTIFICATION: PwmTimerPtr is of
    type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
    by violating this MISRA rule.*/
    /* MISRA2012_RULE_11_3_JUSTIFICATION: PwmTimerPtr is of
    type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
    by violating this MISRA rule.*/
    PwmGtmTimerPtr = (const Mcu_17_Gtm_TomAtomChConfigType*)\
                     LocalPwmChanPtr->PwmTimerPtr;
    PwmGtmTimerType      = PwmGtmTimerPtr->TimerType;
    /* [cover parentID={CE888387-5435-40cf-BF16-22BDDB7F1B14}]
    If timer type is TOM [/cover] */
    if(PwmGtmTimerType == MCU_GTM_TIMER_TOM)
    {
      /* [cover parentID={C2129AEF-236A-4db4-B289-FA39C41B18DD}]
      Set duty to TOM maximum timer value
      [/cover] */
      Duty = PWM_MAX_TIMER_TOM;
    }
    else
    {
      /* [cover parentID={98BA311B-E543-4a35-8D0F-0059135EB565}]
      Set duty to maximum ATOM timer value [/cover] */
      Duty = PWM_MAX_TIMER;
    }
  }
  else
  #else
  UNUSED_PARAMETER(CoreId);
  UNUSED_PARAMETER(ChannelIdx);
  #endif
  {
    /* [cover parentID={7A8EE733-EBE2-4b74-9A77-A2014E0771B1}]
    Set duty to maximum CCU6 timer value [/cover] */
    Duty = PWM_MAX_TIMER_CCU6;
  }
  /* [cover parentID={453A5D02-2DF5-4cae-82DF-F239BD807F9A}]
  Return duty [/cover] */
  return Duty;
}
#endif
#if (PWM_17_GTMCCU6_SET_OUTPUT_TO_IDLE_API == STD_ON)
#if (PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
/*******************************************************************************
** Syntax : static void Pwm_lGtmStartChannelIdle                              **
**                   (                                                        **
**                     const Pwm_17_GtmCcu6_ChannelType ChannelNumber,        **
**                     const uint32 Period,                                   **
**                     const uint32 Dutycycle,                                **
**                     const uint8 CoreId                                     **
**                   )                                                        **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant                                                **
**                                                                            **
** Parameters (in):  PwmChanneld - PWM Channel number                         **
**                   period - Period of the PWM to be generated               **
**                   DutyCycle - Duty cycle of the PWM to be generated        **
**                   CoreId - Core Number                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     This function starts the PWM channel as given by the     **
**                   Input parameters with the desired properties for idle    **
** Traceability :  [cover parentID={84C3DE08-943B-4c73-8BA0-04640B19AFE3}]    **
**                     [/cover]                                               **
*******************************************************************************/
static void Pwm_lGtmStartChannelIdle
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint32 Period,
  const uint32 Dutycycle,
  const uint8 CoreId
)
{
  Mcu_17_Gtm_TimerOutType PwmGtmTimerType;
  const Mcu_17_Gtm_TomAtomChConfigType *PwmGtmTimerPtr;
  /* MISRA2012_RULE_11_5_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  /* MISRA2012_RULE_11_3_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  PwmGtmTimerPtr = (const Mcu_17_Gtm_TomAtomChConfigType*)\
                   Pwm_ConfigPtr->PwmCoreAdd[CoreId]->Pwm_ChannelConfigPtr\
                   [ChannelNumber].PwmTimerPtr;
  PwmGtmTimerType = PwmGtmTimerPtr->TimerType;

  /* [cover parentID={5C43C920-A07B-4023-9FD3-82DA6995E203}]
  If timer type is TOM [/cover]*/
  if(PwmGtmTimerType == MCU_GTM_TIMER_TOM)
  {
    /* [cover parentID={624C79C0-9F13-48c9-AFC0-0DDF61F543BC}]
    Set PWM channel to idle state for TOM [/cover] */
    Pwm_lGtmStartTomChannelIdle(ChannelNumber, Period, Dutycycle, CoreId);
  }
  /* If timer type is ATOM */
  else
  {
    /* [cover parentID={F841CC23-CD57-4682-B612-8DFF4005E876}]
    Set PWM channel to idle state for ATOM [/cover] */
    Pwm_lGtmStartAtomChannelIdle(ChannelNumber, Period, Dutycycle, CoreId);
  }
}
/*******************************************************************************
** Syntax : static void Pwm_lGtmStartTomChannelIdle                           **
**                   (                                                        **
**                     const Pwm_ChannelIdentifierType ChannelNumber,         **
**                     const uint32 Period,                                   **
**                     const uint32 Dutycycle,                                **
**                     const uint8 CoreId                                     **
**                   )                                                        **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different timer channels                   **
**                                                                            **
** Parameters (in):  Channel Number - PWM channel number                      **
**                   Period         - Period of the PWM to be generated       **
**                   Dutycycle      - Dutycycle of the PWM to be generated    **
**                   CoreId         - Core number                             **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     This function sets PWM channel to idle state for         **
**                   TOM channels                                             **
** Traceability :    [cover parentID={3F13CC9E-18E5-45fb-9623-532DEC76255C}]  **
**                     [/cover]                                               **
*******************************************************************************/
static void Pwm_lGtmStartTomChannelIdle
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint32 Period,
  const uint32 Dutycycle,
  const uint8 CoreId
)
{
  const Pwm_17_GtmCcu6_ChannelConfigType *LocalPwmChanPtr; /* ROM pointer */
  const Mcu_17_Gtm_TomAtomChConfigType    *PwmGtmTimerPtr;
  Ifx_GTM_TOM_CH* TomChannelRegPtr; /* Ptr to TOM Channel Reg */
  uint8 Coherency;
  uint8 TimerChannelNumber;
  uint8 TimerModuleNumber;
  uint8 ResetType;

  LocalPwmChanPtr = &(Pwm_ConfigPtr->PwmCoreAdd\
                         [CoreId]->Pwm_ChannelConfigPtr[ChannelNumber]);
  /* MISRA2012_RULE_11_5_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  /* MISRA2012_RULE_11_3_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  PwmGtmTimerPtr = (const Mcu_17_Gtm_TomAtomChConfigType*)\
                   LocalPwmChanPtr->PwmTimerPtr;
  TimerModuleNumber = (uint8)((PwmGtmTimerPtr->TimerId &\
                                  GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);
  TimerChannelNumber = (uint8)((PwmGtmTimerPtr->TimerId &\
                                  GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);
  Coherency = Pwm_lCoherency(LocalPwmChanPtr->PwmChannelInfo);
  ResetType = Pwm_lChanResetType(LocalPwmChanPtr->PwmChannelInfo);
  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TomChannelRegPtr = \
                  PWM_GTM_TOM_CH_POINTER(TimerModuleNumber, TimerChannelNumber);
  /* [cover parentID={A66ADBE0-B956-493e-9553-24BBA2048E5E}]
  Reset type is 0 for Fixed period or Variable period channels [/cover] */
  if(ResetType == 0U)
  {
    /* [cover parentID={746802FB-54D9-4cb8-846B-3612A85E2F55}]
    Enter critical section [/cover] */
    SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
    /* [cover parentID={8CB25E73-7D14-48db-995A-F4FE8E64CE89}]
    Update compare match and shadow register with period and duty [/cover] */
    TomChannelRegPtr->CM0.U = Period;
    TomChannelRegPtr->CM1.U = Dutycycle;
    TomChannelRegPtr->SR0.U = Period;
    TomChannelRegPtr->SR1.U = Dutycycle;
    /* [cover parentID={86FB9EAE-99C4-484f-8B64-5A142A75BD32}]
    Exit critical section [/cover] */
    SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
  }
  /* Reset type is 1 for Fixed period shifted or Center-aligned channels */
  else
  {
    /* [cover parentID={8C8DA4DF-92C9-41cf-B915-55089D19FB87}]
    If channel is non coherent [/cover] */
    if(Coherency == PWM_17_GTMCCU6_NON_COHERENT)
    {
      /* [cover parentID={6B69571D-1C39-45b0-BF36-890799221542}]
      If duty cycle is 0 [/cover] */
      if(Dutycycle == 0U)
      {
        /* [cover parentID={15596A9F-AFCC-4ee1-BE2C-BF60C11B107E}]
        Enter critical section [/cover] */
        SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
        /* Note - UPEN update is disabled, Hence no update of Compare match
        registers by shadow registers */
        /* [cover parentID={688F33E0-CD8B-4fff-BA49-685171C18D93}]
        Update compare match register with period and duty [/cover] */
        TomChannelRegPtr->CM0.U = PWM_MAX_TIMER_TOM;
        TomChannelRegPtr->CM1.U = 0U;
        
        /* [cover parentID={B06317C6-3B77-4f9a-B74A-4DDC9C060A60}]
        Exit critical section [/cover] */
        SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
      }
      else
      {
        /* [cover parentID={78D27AEB-669B-40b7-AFD5-2AC941FCFF53}]
        Enter critical section [/cover] */
        SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
        /* Note - UPEN update is disabled, Hence no update of Compare match
        registers by shadow registers */
        /* [cover parentID={8FE9C54C-07E1-4ad6-8DB0-29EE4172F4F0}]
        Update compare match register with period and duty [/cover] */
        TomChannelRegPtr->CM0.U = 0U;
        TomChannelRegPtr->CM1.U = PWM_MAX_TIMER_TOM;
        /* [cover parentID={039E672F-8B8F-46ad-8CE6-C8C33710387E}]
        Exit critical section [/cover] */
        SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
      }
    }
    else
    {
      /* [cover parentID={64176114-16CD-493f-91EA-7DD72C1AF3C5}]
      If duty cycle is 0 [/cover] */
      if(Dutycycle == 0U)
      {
        /* [cover parentID={74355437-4F6B-4acb-AF92-CEAB958F3926}]
        Enter critical section [/cover] */
        SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
        /* [cover parentID={418448BD-9C82-4d57-96D8-F12FDC3C14D2}]
        Disable shadow transfer [/cover] */
        Mcu_17_Gtm_TomChUpdateEnDis(TimerModuleNumber, TimerChannelNumber, \
                                    MCU_GTM_TIMER_UPDATE_DISABLE);
        /* [cover parentID={7B7C1058-0ED5-4b78-B1CC-A2D46FFDE389}]
        Update compare match register with period and duty [/cover] */
        TomChannelRegPtr->CM0.U = PWM_MAX_TIMER_TOM;
        TomChannelRegPtr->CM1.U = 0U;
        TomChannelRegPtr->SR0.U = PWM_MAX_TIMER_TOM;
        TomChannelRegPtr->SR1.U = 0U;
        /* [cover parentID={E2C140E5-00B3-4427-BD3E-A0BF19E15721}]
        Enable shadow transfer [/cover] */
        Mcu_17_Gtm_TomChUpdateEnDis(TimerModuleNumber, TimerChannelNumber, \
                                    MCU_GTM_TIMER_UPDATE_ENABLE);
        /* [cover parentID={C2A4BE74-AC09-43dd-B8E1-8B06CB47549D}]
        Exit critical section [/cover] */
        SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
      }
      else
      {
        /* [cover parentID={E93A3713-0919-45b4-823F-8D7EAF23DF3A}]
        Enter critical section [/cover] */
        SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
        /* [cover parentID={8081DC7A-3C0D-4748-8F97-C28A6D4447A8}]
        Disable shadow transfer [/cover] */
        Mcu_17_Gtm_TomChUpdateEnDis(TimerModuleNumber, TimerChannelNumber, \
                                    MCU_GTM_TIMER_UPDATE_DISABLE);
        /* [cover parentID={E1FBDBBB-1B24-4bf2-83BC-2807823F50F7}]
        Update compare match register with period and duty [/cover] */
        TomChannelRegPtr->CM0.U = 0U;
        TomChannelRegPtr->CM1.U = PWM_MAX_TIMER_TOM;
        TomChannelRegPtr->SR0.U = 0U;
        TomChannelRegPtr->SR1.U = PWM_MAX_TIMER_TOM;
        /* [cover parentID={8319C733-8391-442d-8D4A-72FFE4043A92}]
        Enable shadow transfer [/cover] */
        Mcu_17_Gtm_TomChUpdateEnDis(TimerModuleNumber, TimerChannelNumber, \
                                    MCU_GTM_TIMER_UPDATE_ENABLE);
        /* [cover parentID={334D30C4-89D8-4a51-B26D-5EDDCDEB7916}]
        Exit critical section [/cover] */
        SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
      }
    }
  }
}
/*******************************************************************************
** Syntax : static void Pwm_lGtmStartAtomChannelIdle                          **
**                   (                                                        **
**                     const Pwm_ChannelIdentifierType ChannelNumber,         **
**                     const uint32 Period,                                   **
**                     const uint32 Dutycycle,                                **
**                     const uint8 CoreId                                     **
**                   )                                                        **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant                                                **
**                                                                            **
** Parameters (in):  Channel Number - PWM channel number                      **
**                   Period         - Period of the PWM to be generated       **
**                   Dutycycle      - Dutycycle of the PWM to be generated    **
**                   CoreId : Core Number                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     This function sets PWM channel to Idle state for         **
**                   ATOM channels                                            **
** Traceability : [cover parentID={53A81270-06B4-4a6d-98BF-EED68DD1F6FD}]     **
**                     [/cover]                                               **
*******************************************************************************/
static void Pwm_lGtmStartAtomChannelIdle
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint32 Period,
  const uint32 Dutycycle,
  const uint8 CoreId
)
{
  const Pwm_17_GtmCcu6_ChannelConfigType *LocalPwmChanPtr; /* ROM pointer */
  const Mcu_17_Gtm_TomAtomChConfigType *PwmGtmTimerPtr;
  Ifx_GTM_ATOM_CH* AtomChannelRegPtr; /* Ptr to ATOM Channel Reg */
  uint8 Coherency;
  uint8 TimerChannelNumber;
  uint8 TimerModuleNumber;
  uint8 ResetType;

  LocalPwmChanPtr = &(Pwm_ConfigPtr->PwmCoreAdd\
                         [CoreId]->Pwm_ChannelConfigPtr[ChannelNumber]);
  /* MISRA2012_RULE_11_5_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  /* MISRA2012_RULE_11_3_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  PwmGtmTimerPtr = (const Mcu_17_Gtm_TomAtomChConfigType*)\
                   LocalPwmChanPtr->PwmTimerPtr;
  TimerModuleNumber = (uint8)((PwmGtmTimerPtr->TimerId &\
                                  GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);
  TimerChannelNumber = (uint8)((PwmGtmTimerPtr->TimerId &\
                                  GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);
  Coherency = Pwm_lCoherency(LocalPwmChanPtr->PwmChannelInfo);
  ResetType = Pwm_lChanResetType(LocalPwmChanPtr->PwmChannelInfo);
  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  AtomChannelRegPtr = PWM_GTM_ATOM_CH_POINTER(TimerModuleNumber, \
                      TimerChannelNumber);

  /* [cover parentID={536AA64C-5638-449b-9357-13B265C3EF48}]
  Reset type is 0 for Fixed period or Variable period channels [/cover] */
  if(ResetType == 0U)
  {
    /* [cover parentID={013D1EF8-71B5-4d91-8473-1F05D7C906DC}]
    Enter critical section [/cover] */
    SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
    /* [cover parentID={63E3F1DC-8393-42a3-A547-C58B60EBD3B9}]
    Update duty in compare match register and shadow register [/cover] */
    AtomChannelRegPtr->CM0.U = Period;
    AtomChannelRegPtr->CM1.U = Dutycycle;
    AtomChannelRegPtr->SR0.U = Period;
    AtomChannelRegPtr->SR1.U = Dutycycle;
    /* [cover parentID={F7A91DFF-D006-46f1-B373-CEB87BB01446}]
    Exit critical section [/cover] */
    SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
  }
  /* Reset type is 1 for Fixed period shifted or Center-aligned channels */
  else
  {
    /* [cover parentID={D9B24966-105D-45dd-B1E7-772F30B647BE}][/cover] */
    if(Coherency == PWM_17_GTMCCU6_NON_COHERENT)
    {
      /* [cover parentID={5569FB7B-7101-4e4b-AD56-CF6255AAE8C0}] 
      If duty cycle is zero [/cover] */
      if(Dutycycle == 0U)
      {
        /* [cover parentID={FE1871BA-F36B-4880-8809-840092CFD77B}] 
        Enter critical section [/cover]*/
        SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
        /* Note - UPEN update is disabled, Hence no update of Compare match
        registers by shadow registers */
        /* [cover parentID={95A59F3D-00E9-46a1-8CB4-840A417F3CCE}] 
        Update compare match register with max period and 0% duty [/cover] */
        AtomChannelRegPtr->CM0.U = PWM_MAX_TIMER;
        AtomChannelRegPtr->CM1.U = 0U;
        
        /* [cover parentID={976CC99A-03EA-4ebb-8A40-5D35D75675D9}]
        Exit critical section [/cover]*/
        SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
      }
      else
      {
        /* [cover parentID={29997D96-813D-49c4-9D7C-D6D00CABF9A3}]
        Enter critical section [/cover] */
        SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
        /* Note - UPEN update is disabled, Hence no update of Compare match
        registers by shadow registers */
        /* [cover parentID={2F38F1AE-F787-4268-81AC-A9DCBCF85297}] 
        Update compare match register with 0 period and 100% duty [/cover] */
        AtomChannelRegPtr->CM0.U = 0U;
        AtomChannelRegPtr->CM1.U = PWM_MAX_TIMER;
        
        /* [cover parentID={C85F8F95-CFD4-44d6-B896-DDEDE3F67299}]
        Exit critical section [/cover] */
        SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
      }
    }
    else
    {
      /* [cover parentID={36AD519A-C463-4673-818D-87ADF439FF50}]
      If duty cycle is zero [/cover] */
      if(Dutycycle == 0U)
      {
        /* [cover parentID={693FF792-564B-454f-BB86-D4DFE2318E32}]
        Enter critical section [/cover] */
        SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
        /* [cover parentID={EF59D430-3297-45c9-98AE-ED7359B42A88}]
        Enable shadow transfer [/cover] */
        Mcu_17_Gtm_AtomChUpdateEnDis(TimerModuleNumber, TimerChannelNumber, \
                                     MCU_GTM_TIMER_UPDATE_DISABLE);
        /* [cover parentID={CDED3E44-5B0A-4fba-B898-0804B9A175E8}]
        Update compare match & shadow register with max period & 0% Duty [/cover] */
        AtomChannelRegPtr->CM0.U = PWM_MAX_TIMER;
        AtomChannelRegPtr->CM1.U = 0U;
        AtomChannelRegPtr->SR0.U = PWM_MAX_TIMER;
        AtomChannelRegPtr->SR1.U = 0U;
        /* [cover parentID={08004227-5A47-4a48-ABDE-0B5636196025}]
        Disable ATOM shadow transfer [/cover] */
        Mcu_17_Gtm_AtomChUpdateEnDis(TimerModuleNumber, TimerChannelNumber, \
                                     MCU_GTM_TIMER_UPDATE_ENABLE);
        /* [cover parentID={A071D16B-7FDC-4e84-9EEC-E303FFEE994C}]
        Exit critical section [/cover] */
        SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
      }
      else
      {
        /* [cover parentID={E6B42AE8-5965-4188-BE78-DBF7CD317090}]
        Enter critical section [/cover] */
        SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
        /* [cover parentID={30F4C365-4831-4671-9697-3409A66F9902}]
        Enable shadow transfer [/cover] */
        Mcu_17_Gtm_AtomChUpdateEnDis(TimerModuleNumber, TimerChannelNumber, \
                                     MCU_GTM_TIMER_UPDATE_DISABLE);
        /* [cover parentID={9228B8FD-2E2C-4b1e-ACAE-913283EB6CB8}]
        Update compare match & shadow register with 0 period & 100% duty [/cover] */
        AtomChannelRegPtr->CM0.U = 0U;
        AtomChannelRegPtr->CM1.U = PWM_MAX_TIMER;
        AtomChannelRegPtr->SR0.U = 0U;
        AtomChannelRegPtr->SR1.U = PWM_MAX_TIMER;
        /* [cover parentID={E3F41337-E23F-4111-8E6C-529431CA631C}]
        Disable ATOM shadow transfer [/cover] */
        Mcu_17_Gtm_AtomChUpdateEnDis(TimerModuleNumber, TimerChannelNumber, \
                                     MCU_GTM_TIMER_UPDATE_ENABLE);
        /* [cover parentID={579FD04B-A0A2-4d3a-B5F4-531381A41D28}]
        Exit critical section [/cover] */
        SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
      }
    }
  }
}
#endif
#endif

#if(PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
#if ((PWM_17_GTMCCU6_SET_OUTPUT_TO_IDLE_API == STD_ON) || \
     (PWM_17_GTMCCU6_DE_INIT_API == STD_ON) )
/*******************************************************************************
** Syntax : static void Pwm_lCcu6StartChannelIdle                             **
**                   (                                                        **
**                     const Pwm_17_GtmCcu6_ChannelType ChannelNumber,        **
**                     const uint32 Dutycycle,                                **
**                     const uint8 CoreId                                     **
**                   )                                                        **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant                                                **
**                                                                            **
** Parameters (in):  Channel Number - PWM channel number                      **
**                   Dutycycle      - Desired DutyCycle value                 **
**                   CoreId : Core Number                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     This function sets PWM channel to Idle state for ccu6    **
**                   channels                                                 **
** Traceability: [cover parentID={B7E59D8E-08AE-4d10-A893-4B5B46ED1009}]      **
**          [/cover]                                                          **
*******************************************************************************/
static void Pwm_lCcu6StartChannelIdle
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint32 Dutycycle,
  const uint8 CoreId
)
{
  const Mcu_17_Ccu6_TimerConfigType *PwmCcu6TimerPtr;
  uint8 Ccu6Kernel;
  uint8 Ccu6Timer;
  uint8 Ccu6Comparator;

  /* MISRA2012_RULE_11_5_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Ccu6_TimerConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  /* MISRA2012_RULE_11_3_JUSTIFICATION: PwmTimerPtr is of
  type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
  by violating this MISRA rule.*/
  PwmCcu6TimerPtr = (const Mcu_17_Ccu6_TimerConfigType*)\
                    Pwm_ConfigPtr->PwmCoreAdd[CoreId]->Pwm_ChannelConfigPtr\
                    [ChannelNumber].PwmTimerPtr;
  Ccu6Kernel = (uint8)((PwmCcu6TimerPtr->TimerId) & PWM_CCU6_KERNEL_MSK) ;
  Ccu6Timer = (uint8)((PwmCcu6TimerPtr->TimerId >> PWM_CCU6_TIMER_POS)\
                      & PWM_CCU6_TIMER_MSK);
  Ccu6Comparator = (uint8)((PwmCcu6TimerPtr->TimerId >> \
                            PWM_CCU6_COMPARATOR_POS)& PWM_CCU6_COMPARATOR_MSK);
  /* [cover parentID={74BDA2E6-3EBA-4b62-8439-A643CAAE3792}]
  Enter critical section [/cover] */
  SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
  /* [cover parentID={1B969ECD-8AEF-4674-A5E8-E628F70ECA5C}]
  Stop CCU6 timer [/cover] */
  Mcu_17_Ccu6_TimerStop(PwmCcu6TimerPtr->TimerId);
  /* [cover parentID={18598AD2-31C0-4894-A3EA-A8F577266C0F}]
  If timer type is T12 [/cover] */
  if(Ccu6Timer == MCU_CCU6_TIMER_T12)
  {
    /* [cover parentID={026F0082-66B2-4c4f-A1C7-28F02A6F8462}]
    Set Duty cycle for timer T12 [/cover] */
    Pwm_17_GtmCcu6_Kernel[Ccu6Kernel]->CC6SR[Ccu6Comparator].U = Dutycycle;
  }
  else
  {
    Pwm_17_GtmCcu6_Kernel[Ccu6Kernel]->CC63SR.U = Dutycycle;
  }
  /* [cover parentID={770B7C7F-35AA-4d31-BF9A-947432FCD8F1}]
  Start CCU6 timer [/cover] */
  Mcu_17_Ccu6_TimerStart(PwmCcu6TimerPtr->TimerId);
  Mcu_17_Ccu6_TimerShadowTransfer(PwmCcu6TimerPtr->TimerId);
  /* [cover parentID={AAA881E1-E70D-480d-868A-D44174E2BE6B}]
  Exit critical section [/cover] */
  SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate();
}
#endif
#endif

#if (PWM_17_GTMCCU6_GET_OUTPUT_STATE_API == STD_ON)
/*******************************************************************************
** Syntax : boolean Pwm_lGetOutputState                                       **
**                   (                                                        **
**                     const Pwm_17_GtmCcu6_ChannelType ChannelNumber,        **
**                     const uint8 CoreId                                     **
**                   )                                                        **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant                                                **
**                                                                            **
** Parameters (in):  ChannelNumber - Channel number of PWM channel            **
**                   CoreId : Core Number                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     Function returns the output state of the channel         **
**                                                                            **
** Traceability   :  [cover parentID={C5C11FB7-8DB3-4871-BD2E-42698AA026CA}]  **
**                     [/cover]                                               **
******************************************************************************/
static boolean Pwm_lGetOutputState
(
  const Pwm_17_GtmCcu6_ChannelType ChannelNumber,
  const uint8 CoreId
)
{
  uint8 RetVal = 0U; /* Stores the output state */
  #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
  uint8 PwmTimerType;
  #endif
  const Pwm_17_GtmCcu6_ChannelConfigType *PwmChannelCfgPtr;

  PwmChannelCfgPtr = &(Pwm_ConfigPtr->PwmCoreAdd\
                       [CoreId]->Pwm_ChannelConfigPtr[ChannelNumber]);

  #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
  PwmTimerType = PwmChannelCfgPtr->PwmTimerUsed;
    /* [cover parentID={AD694162-9EE4-4354-8D09-D7E882784FBD}]
  If timer used is GTM [/cover] */
  if(PwmTimerType == PWM_17_GTMCCU6_GTM_TIMER)
  {
    const Mcu_17_Gtm_TomAtomChConfigType *PwmGtmTimerPtr;
    Mcu_17_Gtm_TimerOutType PwmGtmTimerType;
    const Ifx_GTM_TOM_CH* TomChannelRegPtr; /* Ptr to TOM Channel Reg */
    const Ifx_GTM_ATOM_CH* AtomChannelRegPtr; /* Ptr to ATOM Channel Reg */
    uint8 TimerChannelNumber;
    uint8 TimerModuleNumber;

    /* MISRA2012_RULE_11_5_JUSTIFICATION: PwmTimerPtr is of
    type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
    by violating this MISRA rule.*/
    /* MISRA2012_RULE_11_3_JUSTIFICATION: PwmTimerPtr is of
    type Mcu_17_Gtm_TomAtomChConfigType. No side effects foreseen
    by violating this MISRA rule.*/
    PwmGtmTimerPtr = (const Mcu_17_Gtm_TomAtomChConfigType*)\
                     (PwmChannelCfgPtr->PwmTimerPtr);
    TimerModuleNumber = (uint8)((PwmGtmTimerPtr->TimerId & GTM_MODULE_NO_MASK)\
                                 >> GTM_MODULE_NO_OFF);
    TimerChannelNumber = (uint8)((PwmGtmTimerPtr->TimerId & \
                                  GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);
    PwmGtmTimerType = PwmGtmTimerPtr->TimerType;
    /* [cover parentID={EE723547-1712-4793-A0D0-ADD6DBBB807D}]
    If timer type is TOM [/cover] */
    if(PwmGtmTimerType == MCU_GTM_TIMER_TOM)
    {
      /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
       * by violating this MISRA rule, as the pointer to the object type
       * it is getting cast into is a known type . */
      /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
       * by violating this MISRA rule. */
      TomChannelRegPtr = \
                  PWM_GTM_TOM_CH_POINTER(TimerModuleNumber, TimerChannelNumber);
      /* [cover parentID={18588186-1A22-4aa8-871A-3452A1ED61F3}]
      Set output state to OUT bit of TOM channel status [/cover] */
      RetVal = (uint8)\
       (((TomChannelRegPtr->STAT.U & 1UL) > 0UL) ? PWM_BIT_SET : PWM_BIT_RESET);
    }
    /* Detect the Sub-Module type ATOM */
    else
    {
      /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
       * by violating this MISRA rule, as the pointer to the object type
       * it is getting cast into is a known type . */
      /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
       * by violating this MISRA rule. */
      AtomChannelRegPtr = \
                 PWM_GTM_ATOM_CH_POINTER(TimerModuleNumber, TimerChannelNumber);
      /* [cover parentID={997A60A5-3937-4d21-BB1C-06A57583046A}]
      Set output state to OUT bit of ATOM channel status [/cover] */
      RetVal = (uint8)\
      (((AtomChannelRegPtr->STAT.U & 1UL) > 0UL) ? PWM_BIT_SET : PWM_BIT_RESET);
    }
  }
  else
  #endif
  {
    #if (PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
    /* Get CCU6 output state */
    const Mcu_17_Ccu6_TimerConfigType *PwmCcu6TimerPtr;
    uint8 Ccu6Kernel;
    uint8 Ccu6Timer;
    uint8 Ccu6Comparator;

    /* MISRA2012_RULE_11_5_JUSTIFICATION: PwmTimerPtr is of
    type Mcu_17_Ccu6_TimerConfigType. No side effects foreseen
    by violating this MISRA rule.*/
    /* MISRA2012_RULE_11_3_JUSTIFICATION: PwmTimerPtr is of
    type Mcu_17_Ccu6_TimerConfigType. No side effects foreseen
    by violating this MISRA rule.*/
    PwmCcu6TimerPtr = (const Mcu_17_Ccu6_TimerConfigType*)\
                      Pwm_ConfigPtr->PwmCoreAdd\
                      [CoreId]->Pwm_ChannelConfigPtr[ChannelNumber].PwmTimerPtr;
    Ccu6Kernel = (uint8)((PwmCcu6TimerPtr->TimerId) & PWM_CCU6_KERNEL_MSK);
    Ccu6Timer = (uint8)((PwmCcu6TimerPtr->TimerId >> \
                         PWM_CCU6_TIMER_POS)& PWM_CCU6_TIMER_MSK);
    Ccu6Comparator = (uint8)((PwmCcu6TimerPtr->TimerId >> \
                              PWM_CCU6_COMPARATOR_POS)& PWM_CCU6_COMPARATOR_MSK);
    /* [cover parentID={A08CC502-4DCC-4130-B424-9851DE3FDE23}]
    If CCU6 timer type is T12 [/cover] */
    if(Ccu6Timer == MCU_CCU6_TIMER_T12)
    {
      /* [cover parentID={3D48826F-2242-48b6-85F0-30EFEA2A5951}]
      Set output state to OUT bit of T12 channel status [/cover] */
      RetVal = (uint8)((Pwm_17_GtmCcu6_Kernel[Ccu6Kernel]->CMPSTAT.U >> \
                        Ccu6Comparator)& PWM_CONST_1);
    }
    else
    {
      /* [cover parentID={BD1E83BA-253D-4218-92D8-9F86F9C85AD9}]
      Set output state to OUT bit of T13 channel status [/cover] */
      RetVal = (uint8)((Pwm_17_GtmCcu6_Kernel[Ccu6Kernel]->CMPSTAT.U >> \
                        PWM_CONST_6)&PWM_CONST_1);
    }
    /* [cover parentID={F1154911-A9DF-4f4c-9E82-CFB4A8EB69E0}]
    Get polarity [/cover] */
    if(PWM_GET_POLARITY(PwmChannelCfgPtr->PwmChannelInfo) == \
            (uint8)PWM_17_GTMCCU6_HIGH)
    {
      /* [cover parentID={E198FBAB-E260-4de2-B1EE-4B9EF2A8CB83}]
      Is polarity HIGH [/cover] */
      RetVal = RetVal ^ (uint8)PWM_CONST_1;
    }
    #endif
  }
  return (RetVal);
}
#endif

#if (PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
/*******************************************************************************
** static void Pwm_lCcu6StartTimerSync(uint8 CoreId)                          **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Non reentrant                                            **
**                                                                            **
** Parameters (in):  CoreId                                                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     Function Starts CCU6 channels synchronously              **
** Traceability :    [cover parentID={83C08968-6673-48fc-BEC8-31C01BD9B040}]  **
**                     [/cover]                                               **
*******************************************************************************/
static void Pwm_lCcu6StartTimerSync(uint8 CoreId)
{
  const Pwm_17_GtmCcu6_ChannelConfigType  *PwmChannelCfgPtr;
  const Mcu_17_Ccu6_TimerConfigType       *PwmCcu6TimerPtr;
  const Pwm_17_GtmCcu6_CoreConfigType     *PwmCorePtr;
  Pwm_17_GtmCcu6_ChannelType              ChannelNumber;
  uint8                                   PwmTimerType;
  uint8                                   Ccu6Started = 0U;
  uint8                                   Ccu6Kernel;

  PwmCorePtr = Pwm_ConfigPtr->PwmCoreAdd[CoreId];
  PwmChannelCfgPtr = PwmCorePtr->Pwm_ChannelConfigPtr;
  /* [cover parentID={7CA25529-A343-40a6-BD18-A83ECA2A0E19}]
  Loop for all channels of current core [/cover] */
  for (
    ChannelNumber = (Pwm_17_GtmCcu6_ChannelType)0U;
    ChannelNumber < PwmCorePtr->MaxChannels;
    ChannelNumber++
  )
  {
    PwmTimerType = PwmChannelCfgPtr->PwmTimerUsed;
    if(PwmTimerType == PWM_17_GTMCCU6_CCU6_TIMER)
    {
      /* MISRA2012_RULE_11_5_JUSTIFICATION: PwmTimerPtr is of
      type Mcu_17_Ccu6_TimerConfigType. No side effects foreseen
      by violating this MISRA rule.*/
      /* MISRA2012_RULE_11_3_JUSTIFICATION: PwmTimerPtr is of
      type Mcu_17_Ccu6_TimerConfigType. No side effects foreseen
      by violating this MISRA rule.*/
      PwmCcu6TimerPtr = (const Mcu_17_Ccu6_TimerConfigType*)\
                        PwmChannelCfgPtr->PwmTimerPtr;
      Ccu6Kernel = (uint8)((PwmCcu6TimerPtr->TimerId) & PWM_CCU6_KERNEL_MSK);
      Ccu6Started = (uint8)Pwm_17_GtmCcu6_Kernel[Ccu6Kernel]->TCTR0.B.T12R;
      /* [cover parentID={4F3C71D6-6CDE-41df-A734-FAFEDA83506D}]
      If T12 timer is not started for the kernel [/cover] */
      if(Ccu6Started == 0U)
      {
        /* [cover parentID={EA0382C6-DC59-4f62-ACB2-CB83FF206024}]
        Enable T12 timer [/cover] */
        Mcal_SetBitAtomic(&(Pwm_17_GtmCcu6_Kernel\
              [Ccu6Kernel]->TCTR4.U), IFX_CCU6_TCTR4_T12RS_OFF, 2, PWM_CONST_3);
      }
    }
    PwmChannelCfgPtr++;
  }
}
#if (PWM_17_GTMCCU6_INITCHECK_API == STD_ON)
/*******************************************************************************
** static Std_ReturnType Pwm_lCcu6StartTimerSyncCheck(uint8 CoreId)           **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Non reentrant                                            **
**                                                                            **
** Parameters (in):  CoreId                                                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     E_OK: Synchronous start of CCU6 channel verification is  **
**                         passed                                             **
**                   E_NOT_OK: Synchronous start of CCU6 channel verification **
**                             is failed                                      **
**                                                                            **
** Description :     Function verify the CCU6 channels that are started       **
**                   synchronously                                            **
** Traceability :    [cover parentID={C56C2033-BC97-4c9b-8CA1-3602E1B0E3ED}]  **
**                      [/cover]                                              **
*******************************************************************************/
static Std_ReturnType Pwm_lCcu6StartTimerSyncCheck(uint8 CoreId)
{
  const Pwm_17_GtmCcu6_ChannelConfigType  *PwmChannelCfgPtr;
  const Mcu_17_Ccu6_TimerConfigType       *PwmCcu6TimerPtr;
  const Pwm_17_GtmCcu6_CoreConfigType     *PwmCorePtr;
  Pwm_17_GtmCcu6_ChannelType              ChannelNumber;
  uint8                                   PwmTimerType;
  uint8                                   Ccu6Started = 0U;
  uint8                                   Ccu6Kernel;
  uint8                                   Ccu6Timer;
  Std_ReturnType                          ErrorStatus = E_OK;
  /* [cover parentID={8AE7DC11-0EBD-42c4-9A84-17940BA21383}]
  Extract channel configuration [/cover] */
  PwmCorePtr = Pwm_ConfigPtr->PwmCoreAdd[CoreId];
  PwmChannelCfgPtr = PwmCorePtr->Pwm_ChannelConfigPtr;
  /* [cover parentID={24161AE0-45E6-48fb-91A3-6BF26073B8DE}]
  Till the last channel [/cover] */
  for (
    ChannelNumber = (Pwm_17_GtmCcu6_ChannelType)0U;
    ChannelNumber < PwmCorePtr->MaxChannels;
    ChannelNumber++
  )
  {
    PwmTimerType = PwmChannelCfgPtr->PwmTimerUsed;
    /* [cover parentID={DDD8AA53-F893-4e98-AA71-E0D0C15391F4}]
    If timer type is CCU6 [/cover] */
    if(PwmTimerType == PWM_17_GTMCCU6_CCU6_TIMER)
    {
      /* MISRA2012_RULE_11_5_JUSTIFICATION: PwmTimerPtr is of
      type Mcu_17_Ccu6_TimerConfigType. No side effects foreseen
      by violating this MISRA rule.*/
      /* MISRA2012_RULE_11_3_JUSTIFICATION: PwmTimerPtr is of
      type Mcu_17_Ccu6_TimerConfigType. No side effects foreseen
      by violating this MISRA rule.*/
      PwmCcu6TimerPtr = (const Mcu_17_Ccu6_TimerConfigType*)\
                        PwmChannelCfgPtr->PwmTimerPtr;
      Ccu6Kernel = (uint8)((PwmCcu6TimerPtr->TimerId) & PWM_CCU6_KERNEL_MSK);
      Ccu6Timer = (uint8)((PwmCcu6TimerPtr->TimerId >> PWM_CCU6_TIMER_POS)\
                          & PWM_CCU6_TIMER_MSK);
      /* [cover parentID={2C02B0E9-D007-4a2e-B74E-B843454F4936}]
      If CCU6 timer type is T12 [/cover] */
      if(Ccu6Timer == MCU_CCU6_TIMER_T12)
      {
        Ccu6Started = (uint8)Pwm_17_GtmCcu6_Kernel[Ccu6Kernel]->TCTR0.B.T12R;
      }
      else
      {
        Ccu6Started = (uint8)Pwm_17_GtmCcu6_Kernel[Ccu6Kernel]->TCTR0.B.T13R;
      }
      /* [cover parentID={A40E24B3-3C47-4832-83A6-42CD1264F207}]
      If CCU6 kernal started [/cover] */
      if(Ccu6Started != 1U)
      {
        /* [cover parentID={B6BBB43B-4815-4e2a-933B-B12DE26DCC34}]
        Set error status to E_NOT_OK [/cover] */
        ErrorStatus = E_NOT_OK;
      }
    }
    PwmChannelCfgPtr++;
  }
  /* [cover parentID={ACDE8543-0F90-40d6-8A31-C897B9E62093}]
  Return error status [/cover] */
  return ErrorStatus;
}
#endif
#endif /* End of PWM_17_GTMCCU6_CCU6_TIMER_USED */

#if (PWM_17_GTMCCU6_DEV_ERROR_DETECT == STD_ON)|| \
    (PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON)
/*******************************************************************************
**                                                                            **
** Syntax : static void Pwm_lReportError                                      **
**                   (                                                        **
**                     const uint8 ApiId,                                     **
**                     const uint8 ErrorId                                    **
**                   )                                                        **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant                                                **
**                                                                            **
** Parameters (in):  ApiId - Service ID of the API reporting an error         **
**                   ErrorId - ID of the error reported                       **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
** Description :     Function to report Safety and DETError                   **
** Traceability   : [cover parentID={A4D8B84F-BC61-4b50-A547-05CF63DB0C17}]   **
**                    [/cover]                                                **
*******************************************************************************/
static void Pwm_lReportError(const uint8 ApiId, const uint8 ErrorId)
{
  #if (PWM_17_GTMCCU6_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={3F04FB36-1F90-4e85-96D7-90010D0A49F7}]
  Report development error [/cover] */
  (void)Det_ReportError(
    PWM_17_GTMCCU6_MODULE_ID,
    PWM_17_GTMCCU6_INSTANCE_ID,
    ApiId,
    ErrorId);
  #endif
  /* [cover parentID={3E378734-4F23-4a61-8547-C7729878ECF1}]
  Is safety enabled [/cover] */
  #if (PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={5AEB0074-7B47-43c5-A969-518BF9B90352}]
  Report safety error [/cover] */
  Mcal_ReportSafetyError(
    PWM_17_GTMCCU6_MODULE_ID,
    PWM_17_GTMCCU6_INSTANCE_ID,
    ApiId,
    ErrorId);
  #endif
}
#endif

#if (PWM_17_GTMCCU6_MULTICORE_ERROR_DETECT == STD_ON)|| \
    (PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON)
/*******************************************************************************
**                                                                            **
** Syntax : static void Pwm_lReportMulticoreError( const uint8 ApiId,         **
**                                          const uint8 ErrorId)              **
**                                                                            **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant                                                **
**                                                                            **
** Parameters (in):  ApiId - Service ID of the API reporting an error         **
**                   ErrorId - ID of the error reported                       **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
** Description :     Function to report Safety and multicore DET error        **
*                                                                             **
** Traceability   :  [cover parentID={CA2EE905-9950-45cc-8C0B-8351D9E618C3}]  **
**                     [/cover]                                               **
******************************************************************************/
static void Pwm_lReportMulticoreError(const uint8 ApiId, 
                                      const uint8 ErrorId)
{
  /* [cover parentID={55C3EAE9-4317-49b9-B498-161D8E5EDBC6}]
  Is multicore error detect enabled [/cover] */
  #if (PWM_17_GTMCCU6_MULTICORE_ERROR_DETECT == STD_ON)
  /* [cover parentID={6A4EA1AF-DFD3-44d5-830C-D9E3079499B6}]
  Report DET error [/cover] */
  (void)Det_ReportError(
    PWM_17_GTMCCU6_MODULE_ID,
    PWM_17_GTMCCU6_INSTANCE_ID,
    ApiId,
    ErrorId);
  #endif
  /* [cover parentID={F43C7983-A564-4b56-BBC4-F0CCD8D96DD4}]
  Is safety enabled [/cover] */
  #if (PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={5F069E52-EBFA-41dc-B772-B648ED7F78BA}]
  Report safety error [/cover] */
  Mcal_ReportSafetyError(
    PWM_17_GTMCCU6_MODULE_ID,
    PWM_17_GTMCCU6_INSTANCE_ID,
    ApiId,
    ErrorId);
  #endif
}
#endif
#if ((PWM_17_GTMCCU6_SET_PERIOD_AND_DUTY_API == STD_ON) && \
     (PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON))
/*******************************************************************************
** Syntax : LOCAL_INLINE void Pwm_lDisableGtmCcu6Notif                        **
**                   (                                                        **
**                     const Pwm_17_GtmCcu6_ChannelType ChannelNumber,        **
**                     const uint8 CoreId,                                    **
                       const uint8 TimerType                                  **
**                   )                                                        **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant                                                **
**                                                                            **
** Parameters (in):  ChannelNumber -PWM channel number                        **
**                   CoreId - Core number                                     **
**                   TimerType - Timer used(GTM or CCU6)                      **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
** Description :     Function to Disable GTM and CCU6 Notif                   **
*                                                                             **
** Traceability   :  [cover parentID={47999929-19AB-47dc-97A3-03D4C69731F9}]  **
**                     [/cover]                                               **
*******************************************************************************/
LOCAL_INLINE void Pwm_lDisableGtmCcu6Notif(const Pwm_17_GtmCcu6_ChannelType \
    ChannelNumber, const uint8 CoreId, const uint8 TimerType)
{
  /* [cover parentID={741EDEA7-AE5F-4e81-92AD-A9C3D0E4000D}]
  If timer type is GTM [/cover] */
  #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
  /* Clear the interrupt if duty is 0% or 100%*/
  if(TimerType == PWM_17_GTMCCU6_GTM_TIMER)
  {
    /* [cover parentID={79424238-AE6D-407d-8D35-24392DC854AD}]
    Disable GTM notification if duty is 0% or 100% [/cover] */
    Pwm_lGtmIrqModify(ChannelNumber, 0U, (uint8)CoreId);
  }
  else
  #endif
  {
    UNUSED_PARAMETER(TimerType);
    #if (PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
    /* [cover parentID={EE96ADF8-9E9A-4753-8999-1CF05092E400}]
    Disable CCU6 notification if duty is 0% or 100% [/cover] */
    Pwm_lCcu6IrqModify(ChannelNumber, 0U, (uint8)CoreId);
    #endif
  }
}
#endif
#define PWM_17_GTMCCU6_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Pwm_17_GtmCcu6_MemMap.h"
#define PWM_17_GTMCCU6_START_SEC_CODE_FAST_ASIL_B_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Pwm_17_GtmCcu6_MemMap.h"
/******************************************************************************
** Syntax :          void Pwm_17_GtmCcu6_Isr                                 **
**                   (                                                       **
**                     const uint32 ChannelNumber,                           **
**                     const uint32 IsrStatus                                **
**                   )                                                       **
** Service ID:       0x09                                                    **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       Depends on the implementation of Notification function  **
**                                                                           **
** Parameters (in):  ChannelNumber : PWM Channel number which caused the     **
**                                          interrupt                        **
**                   IsrStatus: Parameter gives the information about the    **
**                   comparator which caused the interrupt.                  **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : 1. This service will be used only in an interrupt           **
**               2. In this service depending on conditions Notification will**
**                   be provided                                             **
**                                                                           **
** Traceability      :[cover parentID={FC51997C-6586-4548-A5A1-29CDD5A5AA04}]**
**                   [/cover]                                                **
******************************************************************************/
/*CYCLOMATIC_Pwm_17_GtmCcu6_Isr_JUSTIFICATION: This Function has cyclomatic
   Complexity >15. Multiple conditions needed to verify if channel notification
   needs to be provided for GTM and CCU6 channels. Further breakdown cannot be
   done in order to maintain readability.*/
void Pwm_17_GtmCcu6_Isr
(
  const uint32 ChannelNumber,
  const uint32 IsrStatus
)
{
  #if (PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON)
  #if (PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON)
  uint32 ErrorFlag = 0U;
  #endif
  uint8 PwmTimerType;
  const Pwm_17_GtmCcu6_ChannelConfigType *LocalPwmChanPtr; /* ROM pointer */
  const Pwm_17_GtmCcu6_ChannelStatusType *LocalPwmChanStatusPtr;
  uint8  PwmCoreChIdx;
  uint32 CoreId;
  uint8 NotifNeeded = 0U;
  #if(PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
  uint8 Ccu6Kernel;
  uint8 Ccu6Timer;
  uint8 Ccu6Comparator;
  const Mcu_17_Ccu6_TimerConfigType *PwmCcu6TimerPtr;
  uint8 HandlePMNotif;
  #endif

  CoreId = Mcal_GetCpuIndex();
  /* [cover parentID={20415B48-B7B6-403c-BFCE-275E9F387A37}]
  Safety is enabled [/cover] */
  #if (PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={86CEBA62-386B-4eb9-A86D-1DDEC8BE958E}]
    Verify whether Init has been called, and validity of channel [/cover] */
  ErrorFlag = Pwm_lUnInitChIdCheck((uint8)ChannelNumber,(uint8)CoreId);
  /* [cover parentID={CCEBEF5A-0EAB-465e-8924-AAF134E19A43}]
  If no errors are reported [/cover] */
  if (ErrorFlag != PWM_ERROR_FOUND)
  #endif
  {
    PwmCoreChIdx = Pwm_ConfigPtr->PwmChannelIdxmapPtr[(uint8)ChannelNumber];
    LocalPwmChanPtr = &(Pwm_ConfigPtr->PwmCoreAdd\
                        [CoreId]->Pwm_ChannelConfigPtr[PwmCoreChIdx]);
    LocalPwmChanStatusPtr = Pwm_CoreChannelStatus[CoreId];
    LocalPwmChanStatusPtr = &(LocalPwmChanStatusPtr[PwmCoreChIdx]);
    PwmTimerType = LocalPwmChanPtr->PwmTimerUsed;

    #if(PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
    /* [cover parentID={A7C5D1E6-175E-4eb4-B28C-92CE9E8A6C84}][/cover] */
    if(PwmTimerType != PWM_17_GTMCCU6_GTM_TIMER)
    {
      /* MISRA2012_RULE_11_5_JUSTIFICATION: PwmTimerPtr is of
      type Mcu_17_Ccu6_TimerConfigType. No side effects foreseen
      by violating this MISRA rule.*/
      /* MISRA2012_RULE_11_3_JUSTIFICATION: PwmTimerPtr is of
      type Mcu_17_Ccu6_TimerConfigType. No side effects foreseen
      by violating this MISRA rule.*/
      PwmCcu6TimerPtr = (const Mcu_17_Ccu6_TimerConfigType*)\
                        LocalPwmChanPtr->PwmTimerPtr;
      Ccu6Timer = (uint8)((PwmCcu6TimerPtr->TimerId >> PWM_CCU6_TIMER_POS)\
                          & PWM_CCU6_TIMER_MSK);

      /* [cover parentID={E8907376-C1DE-4aa6-925F-320D68961A4C}]
      Call notification depending on period match interrupt [/cover] */
      if((Ccu6Timer == MCU_CCU6_TIMER_T12) && ((IsrStatus & PWM_CONST_4) == \
                                                                  PWM_CONST_4))
      {
        Ccu6Kernel = (uint8)((PwmCcu6TimerPtr->TimerId) & PWM_CCU6_KERNEL_MSK);
        Ccu6Comparator = (uint8)((PwmCcu6TimerPtr->TimerId >> \
                            PWM_CCU6_COMPARATOR_POS)& PWM_CCU6_COMPARATOR_MSK);
        /* [cover parentID={E8907376-C1DE-4aa6-925F-320D68961A4C}]
        Call notification depending on period match interrupt [/cover] */
        HandlePMNotif = Pwm_lHandlePeriodMatch(Ccu6Kernel, Ccu6Comparator, \
                                                                (uint8)CoreId);
      }
      else
      {
        HandlePMNotif = 0U;
      }
    }
    else
    {
      HandlePMNotif = 0U;
    }
    #endif

    /* [cover parentID={FB12D60E-796F-46de-B001-D00CF54B100C}]
    Call notification depending on period match interrupt [/cover] */
    /* [cover parentID={073FAD6B-13C2-4355-92F5-C09A60F392DA}]
    If notification is enabled [/cover] */
    if(((LocalPwmChanStatusPtr->Pwm_GlobChn) & \
        PWM_NOTIFI_STATUS_MASK) == PWM_NOTIFI_STATUS_MASK)
    {
      /* [cover parentID={2167FE05-6BBB-4a7f-B2C3-45BBF5840D45}]
      GTM used [/cover] */
      #if(PWM_17_GTMCCU6_GTM_TIMER_USED == STD_ON)
      Pwm_17_GtmCcu6_EdgeNotificationType NotifValue;

      NotifValue = PWM_GET_NOTIFICATION_KIND(PwmCoreChIdx,(uint8)CoreId);

      NotifValue = NotifValue >> PWM_NOTIFI_EDGE_POS;

      if(PwmTimerType == PWM_17_GTMCCU6_GTM_TIMER)
      {
       /* [cover parentID={502CF639-6051-43ff-8D0B-5470E6B101B1}] [/cover] */
        if((NotifValue == PWM_CONST_3) && ((IsrStatus & PWM_CONST_3) != 0U))
        {
          NotifNeeded = 1U;
        }
        else if(NotifValue == (IsrStatus & PWM_CONST_3))
        {
          NotifNeeded = 1U;
        }
        else
        {
          /* Do nothing */
        }
      }
      else
      #endif
      {
        #if(PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
        uint32 ConfigStatus;
        /* [cover parentID={43EB395D-8370-4610-A0B5-7B7012CE5D85}]
        If notification is enabled for CCU6 and valid interrupt is raised
        for CCU6 [/cover] */
        ConfigStatus = LocalPwmChanStatusPtr->Pwm_GlobChn >> \
                       PWM_CCU6_NOTIFI_STATUS_POS;
        if(((ConfigStatus == PWM_CONST_5) || \
            (ConfigStatus == PWM_CONST_24)) && (IsrStatus != 0U))
        {
          NotifNeeded = 1U;
        }
        else if(ConfigStatus == IsrStatus)
        {
          /* [cover parentID={43EB395D-8370-4610-A0B5-7B7012CE5D85}]
          If notification is enabled for CCU6 and valid interrupt is raised
          [/cover] */
          NotifNeeded = 1U;
        }
        else
        {
          /* Do Nothing*/
        }
        #endif
      }
    }
    /* [cover parentID={18D1DA05-CB50-4bdf-B535-63B0D8C4312E}]
    If notification is needed for CCU6[/cover] */
    if(NotifNeeded == 1U)
    {
      /* [cover parentID={DBB4E018-E652-497f-8440-E0A1C7BE293A}]
       Provide Notification [/cover] */
      /* Call back functions has no parameters */
      (LocalPwmChanPtr->PwmNotification)();
    }
    else
    {
      /* Error reported when Pwm Isr is called with incorrect compare
      match interrupt.*/
      /* [cover parentID={9346DF88-C23C-4a1a-BC92-5581792E17CD}]
       Report Safety Error [/cover] */
      /* [cover parentID={641BE6CD-518B-4155-86C9-21AA81C547BF}]
      PWM_17_GTMCCU6_SAFETY_ENABLE [/cover] */
      /* [cover parentID={FEF3112D-C31E-4868-B40D-121431F24F42}]
      [/cover] */
      #if(PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
      if(HandlePMNotif != PWM_PM_NOTIF_HANDLED)
      #endif
      {
        #if (PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON)
        Mcal_ReportSafetyError(
        PWM_17_GTMCCU6_MODULE_ID,
        PWM_17_GTMCCU6_INSTANCE_ID,
        PWM_17_GTMCCU6_SID_ISR,
        PWM_17_GTMCCU6_E_INVALID_ISR);
        #endif
      }
    }
  }
  #else
  #if (PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={7AAF3979-3CB6-4bd7-A6B8-35E53FB4CDF6}]
  Notification not supported and safety enabled. [/cover] */
  /* [cover parentID={8E1A6922-2632-4d9b-A64F-2FB5D0844273}]
  Report Safety Error [/cover] */
  Mcal_ReportSafetyError(
    PWM_17_GTMCCU6_MODULE_ID,
    PWM_17_GTMCCU6_INSTANCE_ID,
    PWM_17_GTMCCU6_SID_ISR,
    PWM_17_GTMCCU6_E_INVALID_ISR);
  #endif
  /* Unused parameter when PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED is STD_OFF*/
  UNUSED_PARAMETER((uint8)ChannelNumber);
  UNUSED_PARAMETER(IsrStatus);
  #endif
}

#if (PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED == STD_ON)
#if (PWM_17_GTMCCU6_CCU6_TIMER_USED == STD_ON)
/******************************************************************************
** Syntax :          uint8 Pwm_lHandlePeriodMatch                            **
**                   (                                                       **
**                     uint8 Ccu6Kernel,                                     **
**                     uint8 Ccu6Comparator,                                 **
**                     uint8 CoreId                                          **
**                   )                                                       **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       Reentrant for different kernels                         **
**                                                                           **
** Parameters (in):  Ccu6Kernel - Kernel which triggered PWM Interrupt       **
**                   Ccu6Comparator-Comparator which trigger CCU6 interrupt, **
**                   CoreId - Core number                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     NotifDone - Variable to identify if period match        **
**                   notification was raised                                 **
**                                                                           **
** Description :    Function calls Notification for CCU6 channels depending  **
**                  on Period Match interrupt                                **
**                                                                           **
** Traceability :    [cover parentID={37EFBDF3-58A3-4880-A0F7-F991DB63F368}] **
**                   [/cover]                                                **
******************************************************************************/
LOCAL_INLINE uint8 Pwm_lHandlePeriodMatch(uint8 Ccu6Kernel, uint8 Ccu6Comparator,
    uint8 CoreId)
{
  uint8 Comp;
  uint8 CoreChIdx;
  uint8 ChannelIdx;
  uint32 NotifValTemp;
  uint8 BitPos;
  uint8 NotifDone = 0U;
  const Pwm_17_GtmCcu6_ChannelStatusType *LocalPwmChanStatusPtrTemp;
  const  Pwm_17_GtmCcu6_ChannelConfigType *LocalPwmChanPtrTemp;
  uint32 ConfigStatus;
  /* [cover parentID={7F39F0CD-E90B-4e22-BBB8-9AE3907CCB21}]
  Loop all comparators. [/cover] */
  for(Comp = 0; Comp <= PWM_CONST_2; Comp++)
  {
    /* [cover parentID={337BBA99-A416-4a84-9F7C-D189EDB14688}]
    If loop comparator is not interrupted [/cover] */
    if(Comp != Ccu6Comparator)
    {
      BitPos = Comp * PWM_CONST_8;
      ChannelIdx = (uint8)((Pwm_ConfigPtr->PwmCcu6ChIdx[Ccu6Kernel] >> \
                            BitPos) & PWM_CCU6_CH_MASK);
      /* Skip if channel is not configured */
      /* [cover parentID={ADF0B8C0-0244-452b-8BCC-F7319E7DCFD9}][/cover] */
      if(ChannelIdx != PWM_CCU6_CH_MASK)
      {
        CoreChIdx = Pwm_ConfigPtr->PwmChannelIdxmapPtr[ChannelIdx];
        LocalPwmChanPtrTemp = &(Pwm_ConfigPtr->PwmCoreAdd\
                                [CoreId]->Pwm_ChannelConfigPtr[CoreChIdx]);
        LocalPwmChanStatusPtrTemp = Pwm_CoreChannelStatus[CoreId];
        LocalPwmChanStatusPtrTemp = \
                                    &(LocalPwmChanStatusPtrTemp[CoreChIdx]);
        ConfigStatus = ((uint32)LocalPwmChanStatusPtrTemp->Pwm_GlobChn >> \
                        PWM_CCU6_NOTIFI_STATUS_POS) & PWM_CONST_4;
        NotifValTemp = (uint32)LocalPwmChanStatusPtrTemp->Pwm_GlobChn & \
                       PWM_NOTIFI_STATUS_MASK;
        /* [cover parentID={E184E5FB-8D50-4ab6-884F-CD26DE32624A}]
         If period match and notification are enabled [/cover] */
        if((NotifValTemp == PWM_NOTIFI_STATUS_MASK) && \
            (ConfigStatus == PWM_CONST_4))
        {
          /* [cover parentID={ABE4848D-14B3-4d8f-AD02-E17430769EF2}]
          Call notification [/cover] */
          (LocalPwmChanPtrTemp->PwmNotification)();
          NotifDone = PWM_PM_NOTIF_HANDLED;
        }
      }
    }
  }
  return NotifDone;
}
#endif
#if (PWM_17_GTMCCU6_SAFETY_ENABLE == STD_ON)
/******************************************************************************
** Syntax :         uint32 Pwm_lUnInitChIdCheck                              **
**                   (                                                       **
**                     Pwm_17_GtmCcu6_ChannelType ChannelNumber,             **
**                     uint8 CoreId                                          **
**                   )                                                       **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       Reentrant                                               **
**                                                                           **
** Parameters (in):  ChannelNumber - PWM channel number                      **
**                   CoreId - Core number                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     PWM_ERROR_FOUND: Initialization status and validity of  **
**                                    PWM channel number check is failed     **
**                   0: Initialization status and validity of PWM channel    **
**                      number check is passed                               **
**                                                                           **
** Description :     Function check Initialization status and validity of    **
**                   ChannelId                                               **
** Traceability :   [cover parentID={245F20B5-E902-4473-A923-22B5C2198E42}]  **
**                  [/cover]                                                 ** 
******************************************************************************/
LOCAL_INLINE uint32 Pwm_lUnInitChIdCheck(\
                        Pwm_17_GtmCcu6_ChannelType ChannelNumber, uint8 CoreId)
{
  uint32 ErrorFlag = 0U;
  const Pwm_17_GtmCcu6_CoreStatusType *LocalCoreStatusPtr;

  LocalCoreStatusPtr = PwmCoreStatusPtr[CoreId];
  /*[cover parentID={31D75B49-543B-4e92-A8A6-531E8ADC6685}][/cover] */
  if(LocalCoreStatusPtr == NULL_PTR)
  {
    /* Report Safety Error */
    Mcal_ReportSafetyError(
      PWM_17_GTMCCU6_MODULE_ID,
      PWM_17_GTMCCU6_INSTANCE_ID,
      PWM_17_GTMCCU6_SID_ISR,
      PWM_17_GTMCCU6_E_UNINIT);
      
      /* Update error status */
      ErrorFlag = PWM_ERROR_FOUND;
  }
  /*[cover parentID={34A66A2F-F9C8-4458-8DF2-D0DF5E7071BE}][/cover] */
  if (ErrorFlag != PWM_ERROR_FOUND)
  {
    if (LocalCoreStatusPtr->Pwm_CoreInitStatus != PWM_INITIALIZED)
    {
      /* [cover parentID={83ABA91C-0BF1-4231-B119-FBB920D0B157}][/cover] */
      if(LocalCoreStatusPtr->Pwm_CoreInitStatus != PWM_DEINITIALIZE_REQ)
      {
        /* Report Safety Error */
        Mcal_ReportSafetyError(
          PWM_17_GTMCCU6_MODULE_ID,
          PWM_17_GTMCCU6_INSTANCE_ID,
          PWM_17_GTMCCU6_SID_ISR,
          PWM_17_GTMCCU6_E_UNINIT);
      }
      ErrorFlag = PWM_ERROR_FOUND;
    }
    if (ErrorFlag != PWM_ERROR_FOUND)
    {
      ErrorFlag = Pwm_lVerChannel\
                  (PWM_17_GTMCCU6_SID_ISR, ChannelNumber, (uint8)CoreId);
    }
  }
  return ErrorFlag;
}
#endif
#endif /* End of PWM_17_GTMCCU6_NOTIFICATION_SUPPORTED */

#define PWM_17_GTMCCU6_STOP_SEC_CODE_FAST_ASIL_B_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Pwm_17_GtmCcu6_MemMap.h"
/***************** End of PWM driver module **********************************/

