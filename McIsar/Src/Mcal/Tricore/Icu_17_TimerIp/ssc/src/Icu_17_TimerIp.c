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
**  FILENAME     : Icu_17_TimerIp.c                                           **
**                                                                            **
**  VERSION      : 67.0.0                                                     **
**                                                                            **
**  DATE         : 2023-05-18                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY : [cover parentID={580D5E9C-33ED-43fa-B628-6817BF7977F7}]    **
**                                                                            **
**  DESCRIPTION  : Icu Driver source file                                     **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Icu Driver                            **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/******************************************************************************
 **                      Includes                                             **
 ******************************************************************************/
/* [cover parentID={F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}][/cover] */
/* [cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}] */
/* Covering MemMaps for call-out code as there is no call-out code in ICU */
/* [/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}] */
/* MemMaps */
/* [/cover] */

/* [cover parentID={25550CB8-B43D-43e8-AC12-E4BB14B7653C}] */
/* File inclusions */
/* [/cover] */

/* Icu Module header file */
#include "Icu_17_TimerIp.h"
#include "Icu_17_TimerIp_Local.h"
#include "Icu_17_TimerIp_Cbk.h"

/* Inclusion of sfr file */
#if defined(ACCESS)
#undef ACCESS
#endif
#if(ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
#include "IfxGtm_reg.h"
#endif
#include "IfxScu_reg.h"
#include "IfxCcu6_reg.h"
#include "IfxGpt12_reg.h"

/* Include SchM to import the critical section functions */
#include "SchM_Icu_17_TimerIp.h"

#if (ICU_17_TIMERIP_INIT_DEINIT_API_MODE == ICU_17_TIMERIP_MCAL_USER1) || \
(ICU_17_TIMERIP_RUNTIME_API_MODE == ICU_17_TIMERIP_MCAL_USER1)
/* Mode specific library wrappers.*/
#include "McalLib_OsStub.h"
#endif

#if ( (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)|| \
(ICU_17_TIMERIP_GPT12_USED == STD_ON)||\
(ICU_17_TIMERIP_CCU6_USED == STD_ON))
/* this includes Gtm configuration file also */
#include "Mcu_17_TimerIp.h"
#endif

#if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON)
/* Import of DET functionality. */
#include "Det.h"
#endif

#if (ICU_17_TIMERIP_RUNTIME_ERROR_DETECT == STD_ON)
/*Import Runtime Error reporting from Mcal_Wrapper Module*/
#include "Mcal_Wrapper.h"
#endif

#if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
#include "Mcal_SafetyError.h"
#endif

/* [cover parentID={1A65EADD-AFD0-4845-B2D2-8257E086DD67}]*/
/* User mode support */
/* [/cover] */
#if (ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON)
/* [cover parentID={5C36F1D7-FE28-4e7f-9673-488D4C2DEBDE}]*/
#if (ICU_17_TIMERIP_INIT_DEINIT_API_MODE == ICU_17_TIMERIP_MCAL_SUPERVISOR)
/* Library APIs  */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'ICU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREGMASK'
 * defined for User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define ICU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREGMASK(RegAdd,Data,Mask) \
                            Mcal_WriteSafetyEndInitProtRegMask(RegAdd,Data,Mask)
#else
/* Library APIs  */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'ICU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREGMASK'
 * defined for User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define ICU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREGMASK(RegAdd,Data,Mask) \
                        MCAL_LIB_WRITESAFETYENDINITPROTREGMASK(RegAdd,Data,Mask)
#endif

#if (ICU_17_TIMERIP_RUNTIME_API_MODE == ICU_17_TIMERIP_MCAL_SUPERVISOR)
/* Library APIs  */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'ICU_LIB_RUNTIME_WRITESAFETYENDINITPROTREGMASK'
 * defined for User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define ICU_LIB_RUNTIME_WRITESAFETYENDINITPROTREGMASK(RegAdd,Data,Mask) \
                            Mcal_WriteSafetyEndInitProtRegMask(RegAdd,Data,Mask)
#else
/* Library APIs  */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'ICU_LIB_RUNTIME_WRITESAFETYENDINITPROTREGMASK'
 * defined for User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define ICU_LIB_RUNTIME_WRITESAFETYENDINITPROTREGMASK(RegAdd,Data,Mask) \
                        MCAL_LIB_WRITESAFETYENDINITPROTREGMASK(RegAdd,Data,Mask)
#endif
/* [/cover] */
#endif


/******************************************************************************
 **                      Imported Compiler Switch Check                        *
 ******************************************************************************/
/* [cover parentID={BDE616FE-5D39-4b9d-9390-8351CC6C490C}]
   Autosar version check using macros published by McalLiB */
/* [cover parentID={9091FF52-55DE-49bc-A108-8423E25F39D9}] */
/* Check for definition of the AS Version */
/* Icu.c will check if the correct version of Icu.h is included */

#ifndef ICU_17_TIMERIP_AR_RELEASE_MAJOR_VERSION
#error "ICU_17_TIMERIP_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

#if ( ICU_17_TIMERIP_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION  )
#error "ICU_17_TIMERIP_AR_RELEASE_MAJOR_VERSION does not match. "
#endif

#ifndef ICU_17_TIMERIP_AR_RELEASE_MINOR_VERSION
#error "ICU_17_TIMERIP_AR_RELEASE_MINOR_VERSION is not defined. "
#endif

#if ( ICU_17_TIMERIP_AR_RELEASE_MINOR_VERSION != MCAL_AR_RELEASE_MINOR_VERSION  )
#error "ICU_17_TIMERIP_AR_RELEASE_MINOR_VERSION does not match. "
#endif

#ifndef ICU_17_TIMERIP_AR_RELEASE_REVISION_VERSION
#error "ICU_17_TIMERIP_AR_RELEASE_REVISION_VERSION is not defined. "
#endif

#if ( ICU_17_TIMERIP_AR_RELEASE_REVISION_VERSION != MCAL_AR_RELEASE_REVISION_VERSION  )
#error "ICU_17_TIMERIP_AR_RELEASE_REVISION_VERSION does not match. "
#endif


/* Check for definition of SW version Information */
#ifndef ICU_17_TIMERIP_SW_MAJOR_VERSION
#error "ICU_17_TIMERIP_SW_MAJOR_VERSION is not defined. "
#endif

#ifndef ICU_17_TIMERIP_SW_MINOR_VERSION
#error "ICU_17_TIMERIP_SW_MINOR_VERSION is not defined. "
#endif

#ifndef ICU_17_TIMERIP_SW_PATCH_VERSION
#error "ICU_17_TIMERIP_SW_PATCH_VERSION is not defined. "
#endif

#if ( ICU_17_TIMERIP_SW_MAJOR_VERSION != 20U )
#error "ICU_17_TIMERIP_SW_MAJOR_VERSION does not match. "
#endif

#if ( ICU_17_TIMERIP_SW_MINOR_VERSION != 25U )
#error "ICU_17_TIMERIP_SW_MINOR_VERSION does not match. "
#endif

#if ( ICU_17_TIMERIP_SW_PATCH_VERSION != 0U )
#error "ICU_17_TIMERIP_SW_PATCH_VERSION does not match. "
#endif

/*

 */
/* [cover parentID={A3E1E356-A1D9-4139-82E7-12F07D551FAF}] */
/* Inter Module Checks to avoid integration of incompatible files */
#if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON)

#ifndef DET_AR_RELEASE_MAJOR_VERSION
#error "DET_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

#if ( DET_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION  )
#error "DET_AR_RELEASE_MAJOR_VERSION does not match. "
#endif

#endif
/* End Of ICU_17_TIMERIP_DEV_ERROR_DETECT */
/* [/cover] */

/******************************************************************************
 **                      Private Variable Definitions                         **
 ******************************************************************************/
#if (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON) || \
(ICU_17_TIMERIP_TIMESTAMP_API == STD_ON) || \
(ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON) || \
(ICU_17_TIMERIP_INCREMENTAL_INTERFACE_API == STD_ON)
  #define ICU_17_TIMERIP_NOTIF_NEEDED (STD_ON)
#else
  #define ICU_17_TIMERIP_NOTIF_NEEDED (STD_OFF)
#endif
/* [cover parentID={FBDB07C8-7F08-4ebf-AE49-0278DE9C7535}] */
/* Memory allocation to support multicore */
/* [/cover] */
/* [cover parentID={314DBE9A-27AA-4b2f-B7FB-4C42867BB782}] */
/* Multicore support on each channel */
/* [/cover] */
/* [cover parentID={A82D2CB3-21E6-46ae-9D09-B053931097CD}] */
/* Channel flags to be accessed atomically. */
/* [/cover] */

#if (ICU_17_TIMERIP_MAX_CHANNELS != 0U)

/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}] */
/* Memory mapping for variables */
/* [/cover] */
/* Core0 RAM*/
#if (ICU_17_TIMERIP_MAX_CHANNELS_CORE0 > 0U)
#define ICU_17_TIMERIP_START_SEC_VAR_CLEARED_ASIL_B_CORE0_32
/* [cover parentID={14AF8E74-51FE-4399-8A99-5789F2CD773D}]
Icu_17_TimerIp_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"
static uint32 \
          Icu_17_TimerIp_GlbIndexStatusCore0[ICU_17_TIMERIP_MAX_CHANNELS_CORE0];
#if (ICU_17_TIMERIP_CHNL_DATA_MAX_CHANNELS_CORE0 > 0U)
/* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating this
 * MISRA rule,To implement efficiently IcuMeasaurementProperty as a post-build
 * parameter.Union is required*/
static Icu_17_TimerIp_ChannelData \
   Icu_17_TimerIp_ChannelDataCore0[ICU_17_TIMERIP_CHNL_DATA_MAX_CHANNELS_CORE0];
#endif
#define ICU_17_TIMERIP_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_32
/* [cover parentID={14AF8E74-51FE-4399-8A99-5789F2CD773D}]
Icu_17_TimerIp_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}] */
/* MemMaps for const data */
/* [/cover] */
#define ICU_17_TIMERIP_START_SEC_VAR_INIT_ASIL_B_CORE0_32
/* [cover parentID={14AF8E74-51FE-4399-8A99-5789F2CD773D}]
Icu_17_TimerIp_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"
static Icu_17_TimerIp_CoreType Icu_17_TimerIp_VarlistCore0 =
{
  Icu_17_TimerIp_GlbIndexStatusCore0,
  #if (ICU_17_TIMERIP_CHNL_DATA_MAX_CHANNELS_CORE0 > 0U)
    Icu_17_TimerIp_ChannelDataCore0,
  #else
    NULL_PTR,
  #endif
  #if (ICU_17_TIMERIP_REPORT_WAKEUP_SOURCE == STD_ON)
  0U,
  #endif
  ICU_17_TIMERIP_MODE_NORMAL
};
#define ICU_17_TIMERIP_STOP_SEC_VAR_INIT_ASIL_B_CORE0_32
/* [cover parentID={14AF8E74-51FE-4399-8A99-5789F2CD773D}]
Icu_17_TimerIp_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"
#endif

/* Core1 RAM*/
#if (ICU_17_TIMERIP_MAX_CHANNELS_CORE1 > 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
#define ICU_17_TIMERIP_START_SEC_VAR_CLEARED_ASIL_B_CORE1_32
/* [cover parentID={14AF8E74-51FE-4399-8A99-5789F2CD773D}]
Icu_17_TimerIp_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
    due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
    due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
    due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
    due to Autosar Naming constraints.*/
static uint32 \
          Icu_17_TimerIp_GlbIndexStatusCore1[ICU_17_TIMERIP_MAX_CHANNELS_CORE1];
#if (ICU_17_TIMERIP_CHNL_DATA_MAX_CHANNELS_CORE1 > 0U)
/* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating this
 * MISRA rule,To implement efficiently IcuMeasaurementProperty as a post-build
 * parameter.Union is required*/
static Icu_17_TimerIp_ChannelData \
   Icu_17_TimerIp_ChannelDataCore1[ICU_17_TIMERIP_CHNL_DATA_MAX_CHANNELS_CORE1];
#endif
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
#define ICU_17_TIMERIP_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_32
/* [cover parentID={14AF8E74-51FE-4399-8A99-5789F2CD773D}]
Icu_17_TimerIp_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}] */
/* MemMaps for const data */
/* [/cover] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
#define ICU_17_TIMERIP_START_SEC_VAR_INIT_ASIL_B_CORE1_32
/* [cover parentID={14AF8E74-51FE-4399-8A99-5789F2CD773D}]
Icu_17_TimerIp_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"
static Icu_17_TimerIp_CoreType Icu_17_TimerIp_VarlistCore1 =
{
  Icu_17_TimerIp_GlbIndexStatusCore1,
  #if (ICU_17_TIMERIP_CHNL_DATA_MAX_CHANNELS_CORE1 > 0U)
    Icu_17_TimerIp_ChannelDataCore1,
  #else
    NULL_PTR,
  #endif
  #if (ICU_17_TIMERIP_REPORT_WAKEUP_SOURCE == STD_ON)
  0U,
  #endif
  ICU_17_TIMERIP_MODE_NORMAL
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
#define ICU_17_TIMERIP_STOP_SEC_VAR_INIT_ASIL_B_CORE1_32
/* [cover parentID={14AF8E74-51FE-4399-8A99-5789F2CD773D}]
Icu_17_TimerIp_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"

#endif

/* Core2 RAM*/
#if (ICU_17_TIMERIP_MAX_CHANNELS_CORE2 > 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
#define ICU_17_TIMERIP_START_SEC_VAR_CLEARED_ASIL_B_CORE2_32
/* [cover parentID={14AF8E74-51FE-4399-8A99-5789F2CD773D}]
Icu_17_TimerIp_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
    due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
    due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
    due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
    due to Autosar Naming constraints.*/
static uint32 \
          Icu_17_TimerIp_GlbIndexStatusCore2[ICU_17_TIMERIP_MAX_CHANNELS_CORE2];
#if (ICU_17_TIMERIP_CHNL_DATA_MAX_CHANNELS_CORE2 > 0U)
/* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating this
 * MISRA rule,To implement efficiently IcuMeasaurementProperty as a post-build
 * parameter.Union is required*/
static Icu_17_TimerIp_ChannelData \
   Icu_17_TimerIp_ChannelDataCore2[ICU_17_TIMERIP_CHNL_DATA_MAX_CHANNELS_CORE2];
#endif
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
#define ICU_17_TIMERIP_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_32
/* [cover parentID={14AF8E74-51FE-4399-8A99-5789F2CD773D}]
Icu_17_TimerIp_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}] */
/* MemMaps for const data */
/* [/cover] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
#define ICU_17_TIMERIP_START_SEC_VAR_INIT_ASIL_B_CORE2_32
/* [cover parentID={14AF8E74-51FE-4399-8A99-5789F2CD773D}]
Icu_17_TimerIp_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"
static Icu_17_TimerIp_CoreType Icu_17_TimerIp_VarlistCore2 =
{
  Icu_17_TimerIp_GlbIndexStatusCore2,
  #if (ICU_17_TIMERIP_CHNL_DATA_MAX_CHANNELS_CORE2 > 0U)
    Icu_17_TimerIp_ChannelDataCore2,
  #else
    NULL_PTR,
  #endif
  #if (ICU_17_TIMERIP_REPORT_WAKEUP_SOURCE == STD_ON)
  0U,
  #endif
  ICU_17_TIMERIP_MODE_NORMAL
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
#define ICU_17_TIMERIP_STOP_SEC_VAR_INIT_ASIL_B_CORE2_32
/* [cover parentID={14AF8E74-51FE-4399-8A99-5789F2CD773D}]
Icu_17_TimerIp_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"
#endif
/* Core3 RAM*/
#if (ICU_17_TIMERIP_MAX_CHANNELS_CORE3 > 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
#define ICU_17_TIMERIP_START_SEC_VAR_CLEARED_ASIL_B_CORE3_32
/* [cover parentID={14AF8E74-51FE-4399-8A99-5789F2CD773D}]
Icu_17_TimerIp_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
    due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
    due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
    due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
    due to Autosar Naming constraints.*/
static uint32 \
          Icu_17_TimerIp_GlbIndexStatusCore3[ICU_17_TIMERIP_MAX_CHANNELS_CORE3];
#if (ICU_17_TIMERIP_CHNL_DATA_MAX_CHANNELS_CORE3 > 0U)
/* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating this
 * MISRA rule,To implement efficiently IcuMeasaurementProperty as a post-build
 * parameter.Union is required*/
static Icu_17_TimerIp_ChannelData \
   Icu_17_TimerIp_ChannelDataCore3[ICU_17_TIMERIP_CHNL_DATA_MAX_CHANNELS_CORE3];
#endif
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
#define ICU_17_TIMERIP_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_32
/* [cover parentID={14AF8E74-51FE-4399-8A99-5789F2CD773D}]
Icu_17_TimerIp_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}] */
/* MemMaps for const data */
/* [/cover] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
#define ICU_17_TIMERIP_START_SEC_VAR_INIT_ASIL_B_CORE3_32
/* [cover parentID={14AF8E74-51FE-4399-8A99-5789F2CD773D}]
Icu_17_TimerIp_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"
static Icu_17_TimerIp_CoreType Icu_17_TimerIp_VarlistCore3 =
{
  Icu_17_TimerIp_GlbIndexStatusCore3,
  #if (ICU_17_TIMERIP_CHNL_DATA_MAX_CHANNELS_CORE3 > 0U)
    Icu_17_TimerIp_ChannelDataCore3,
  #else
    NULL_PTR,
  #endif
  #if (ICU_17_TIMERIP_REPORT_WAKEUP_SOURCE == STD_ON)
  0U,
  #endif
  ICU_17_TIMERIP_MODE_NORMAL
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
#define ICU_17_TIMERIP_STOP_SEC_VAR_INIT_ASIL_B_CORE3_32
/* [cover parentID={14AF8E74-51FE-4399-8A99-5789F2CD773D}]
Icu_17_TimerIp_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"

#endif

/* Core4 RAM*/
#if (ICU_17_TIMERIP_MAX_CHANNELS_CORE4 > 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
#define ICU_17_TIMERIP_START_SEC_VAR_CLEARED_ASIL_B_CORE4_32
/* [cover parentID={14AF8E74-51FE-4399-8A99-5789F2CD773D}]
Icu_17_TimerIp_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
    due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
    due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
    due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
    due to Autosar Naming constraints.*/
static uint32 \
          Icu_17_TimerIp_GlbIndexStatusCore4[ICU_17_TIMERIP_MAX_CHANNELS_CORE4];
#if (ICU_17_TIMERIP_CHNL_DATA_MAX_CHANNELS_CORE4 > 0U)
/* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating this
 * MISRA rule,To implement efficiently IcuMeasaurementProperty as a post-build
 * parameter.Union is required*/
static Icu_17_TimerIp_ChannelData \
   Icu_17_TimerIp_ChannelDataCore4[ICU_17_TIMERIP_CHNL_DATA_MAX_CHANNELS_CORE4];
#endif
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
#define ICU_17_TIMERIP_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_32
/* [cover parentID={14AF8E74-51FE-4399-8A99-5789F2CD773D}]
Icu_17_TimerIp_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}] */
/* MemMaps for const data */
/* [/cover] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
#define ICU_17_TIMERIP_START_SEC_VAR_INIT_ASIL_B_CORE4_32
/* [cover parentID={14AF8E74-51FE-4399-8A99-5789F2CD773D}]
Icu_17_TimerIp_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"
static Icu_17_TimerIp_CoreType Icu_17_TimerIp_VarlistCore4 =
{
  Icu_17_TimerIp_GlbIndexStatusCore4,
  #if (ICU_17_TIMERIP_CHNL_DATA_MAX_CHANNELS_CORE4 > 0U)
    Icu_17_TimerIp_ChannelDataCore4,
  #else
    NULL_PTR,
  #endif
  #if (ICU_17_TIMERIP_REPORT_WAKEUP_SOURCE == STD_ON)
  0U,
  #endif
  ICU_17_TIMERIP_MODE_NORMAL
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
#define ICU_17_TIMERIP_STOP_SEC_VAR_INIT_ASIL_B_CORE4_32
/* [cover parentID={14AF8E74-51FE-4399-8A99-5789F2CD773D}]
Icu_17_TimerIp_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"

#endif
/* Core5 RAM*/
#if (ICU_17_TIMERIP_MAX_CHANNELS_CORE5 > 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
#define ICU_17_TIMERIP_START_SEC_VAR_CLEARED_ASIL_B_CORE5_32
/* [cover parentID={14AF8E74-51FE-4399-8A99-5789F2CD773D}]
Icu_17_TimerIp_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
    due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
    due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
    due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
    due to Autosar Naming constraints.*/
static uint32 \
          Icu_17_TimerIp_GlbIndexStatusCore5[ICU_17_TIMERIP_MAX_CHANNELS_CORE5];
#if (ICU_17_TIMERIP_CHNL_DATA_MAX_CHANNELS_CORE5 > 0U)
/* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating this
 * MISRA rule,To implement efficiently IcuMeasaurementProperty as a post-build
 * parameter.Union is required*/
static Icu_17_TimerIp_ChannelData \
   Icu_17_TimerIp_ChannelDataCore5[ICU_17_TIMERIP_CHNL_DATA_MAX_CHANNELS_CORE5];
#endif
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
#define ICU_17_TIMERIP_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_32
/* [cover parentID={14AF8E74-51FE-4399-8A99-5789F2CD773D}]
Icu_17_TimerIp_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}] */
/* MemMaps for const data */
/* [/cover] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
#define ICU_17_TIMERIP_START_SEC_VAR_INIT_ASIL_B_CORE5_32
/* [cover parentID={14AF8E74-51FE-4399-8A99-5789F2CD773D}]
Icu_17_TimerIp_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"
static Icu_17_TimerIp_CoreType Icu_17_TimerIp_VarlistCore5 =
{
  Icu_17_TimerIp_GlbIndexStatusCore5,
  #if (ICU_17_TIMERIP_CHNL_DATA_MAX_CHANNELS_CORE5 > 0U)
    Icu_17_TimerIp_ChannelDataCore5,
  #else
    NULL_PTR,
  #endif
  #if (ICU_17_TIMERIP_REPORT_WAKEUP_SOURCE == STD_ON)
  0U,
  #endif
  ICU_17_TIMERIP_MODE_NORMAL
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
#define ICU_17_TIMERIP_STOP_SEC_VAR_INIT_ASIL_B_CORE5_32
/* [cover parentID={14AF8E74-51FE-4399-8A99-5789F2CD773D}]
Icu_17_TimerIp_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"

#endif

#endif

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
#define ICU_17_TIMERIP_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
/* [cover parentID={14AF8E74-51FE-4399-8A99-5789F2CD773D}]
Icu_17_TimerIp_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"
/* Variable Holds the Configuration Pointer given in Icu_17_TimerIp_Init */
/* Common RAM*/
/* Root Config pointer */
static const Icu_17_TimerIp_ConfigType *Icu_17_TimerIp_ConfigPtr;
/* Initialize status for all cores. */
/* MISRA2012_RULE_8_9_JUSTIFICATION: No side effects foreseen
 * by violating this MISRA rule, as the variable is accessed via
 * assembly instructions */
static uint32 Icu_17_TimerIp_InitStatus;
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
#define ICU_17_TIMERIP_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
/* [cover parentID={14AF8E74-51FE-4399-8A99-5789F2CD773D}]
Icu_17_TimerIp_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"

/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}] */
/* MemMaps for const data */
/* [/cover] */
#define ICU_17_TIMERIP_START_SEC_CONST_ASIL_B_GLOBAL_32
/* [cover parentID={14AF8E74-51FE-4399-8A99-5789F2CD773D}]
Icu_17_TimerIp_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"
/* Root variable list */
static Icu_17_TimerIp_CoreType* const
  Icu_17_TimerIp_Varlist[ICU_17_TIMERIP_MAX_CORES] =
{
  #if (ICU_17_TIMERIP_MAX_CHANNELS_CORE0 > 0U)
    &Icu_17_TimerIp_VarlistCore0,
  #else
    NULL_PTR,
  #endif
  #if (ICU_17_TIMERIP_MAX_CHANNELS_CORE1 > 0U)
    &Icu_17_TimerIp_VarlistCore1,
  #else
    NULL_PTR,
  #endif
  #if (ICU_17_TIMERIP_MAX_CHANNELS_CORE2 > 0U)
    &Icu_17_TimerIp_VarlistCore2,
  #else
    NULL_PTR,
  #endif
  #if (ICU_17_TIMERIP_MAX_CHANNELS_CORE3 > 0U)
    &Icu_17_TimerIp_VarlistCore3,
  #else
    NULL_PTR,
  #endif
  #if (ICU_17_TIMERIP_MAX_CHANNELS_CORE4 > 0U)
    &Icu_17_TimerIp_VarlistCore4,
  #else
    NULL_PTR,
  #endif
  #if (ICU_17_TIMERIP_MAX_CHANNELS_CORE5 > 0U)
    &Icu_17_TimerIp_VarlistCore5,
  #else
    NULL_PTR,
  #endif
};
#define ICU_17_TIMERIP_STOP_SEC_CONST_ASIL_B_GLOBAL_32
/* [cover parentID={14AF8E74-51FE-4399-8A99-5789F2CD773D}]
Icu_17_TimerIp_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"


/* [cover parentID={FC34B5EF-D694-4d02-94A5-24C0607D5C4E}]
   Code executable from any core.
   [/cover] */
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}] */
/* Memory mapping for code */
/* [/cover] */
#define ICU_17_TIMERIP_START_SEC_CODE_ASIL_B_GLOBAL
/* [cover parentID={14AF8E74-51FE-4399-8A99-5789F2CD773D}]
Icu_17_TimerIp_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"

/******************************************************************************
 **                      Exported Function Declarations                       **
 ******************************************************************************/


/*******************************************************************************
***                      Private Function Declarations                        **
*******************************************************************************/
#if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
(ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
LOCAL_INLINE uint32 Icu_lInitDetCheck(
  const Icu_17_TimerIp_ConfigType * const IcuConfigPtr, const uint8 CoreId);
#endif

static void Icu_lResetGlobalVariables(const uint8 CoreId);

LOCAL_INLINE void Icu_lChannelInit(const uint8 CoreId);


#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
LOCAL_INLINE void Icu_lGtmChannelInit(
  const Icu_17_TimerIp_ChannelConfigType * const LocalIcuChanPtr);
#endif

#if (ICU_17_TIMERIP_CCU6_USED == STD_ON)
LOCAL_INLINE void Icu_lCcu6ChannelInit(
  const Icu_17_TimerIp_ChannelConfigType *const LocalIcuChanPtr);
#endif

#if (ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON)
LOCAL_INLINE void Icu_lEruInit(
  const Icu_17_TimerIp_ChannelConfigType *const LocalIcuChanPtr);
#endif

#if (ICU_17_TIMERIP_GPT12_USED == STD_ON)
LOCAL_INLINE void Icu_lGpt12Init(
  const Icu_17_TimerIp_ChannelConfigType *const LocalIcuChanPtr);
#endif


#if (ICU_17_TIMERIP_INITCHECK_API == STD_ON)
LOCAL_INLINE Std_ReturnType Icu_lResetGlobalVariablesCheck(
  const uint8 CoreId);
#endif

#if (ICU_17_TIMERIP_INITCHECK_API == STD_ON)
LOCAL_INLINE Std_ReturnType Icu_lPreInitCheck(
  const Icu_17_TimerIp_ConfigType* const ConfigPtr, const uint8 CoreId);
#endif

#if (ICU_17_TIMERIP_INITCHECK_API == STD_ON)
LOCAL_INLINE uint32 Icu_lChannelStatusCheckValue(
  const Icu_17_TimerIp_ChannelConfigType *const LocalIcuChanPtr);
#endif

#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) && \
(ICU_17_TIMERIP_INITCHECK_API == STD_ON)
LOCAL_INLINE Std_ReturnType Icu_lGtmChannelInitCheck(
  const Icu_17_TimerIp_ChannelConfigType *const LocalIcuChanPtr);
#endif

#if (ICU_17_TIMERIP_CCU6_USED == STD_ON) && \
(ICU_17_TIMERIP_INITCHECK_API == STD_ON)
LOCAL_INLINE Std_ReturnType Icu_lCcu6ChannelInitCheck(
  const Icu_17_TimerIp_ChannelConfigType *const LocalIcuChanPtr);
#endif

#if (ICU_17_TIMERIP_GPT12_USED == STD_ON) && \
(ICU_17_TIMERIP_INITCHECK_API == STD_ON)
LOCAL_INLINE Std_ReturnType Icu_lGpt12InitCheck(
  const Icu_17_TimerIp_ChannelConfigType *const LocalIcuChanPtr);
#endif

#if (ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON) && \
(ICU_17_TIMERIP_INITCHECK_API == STD_ON)
LOCAL_INLINE Std_ReturnType Icu_lEruInitCheck(
  const Icu_17_TimerIp_ChannelConfigType *const LocalIcuChanPtr);
#endif


#if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
(ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
static uint32 Icu_lNotifiDetCheck(
  const Icu_17_TimerIp_ChannelType Channel,
  const uint8 ServiceId ,
  const Icu_17_TimerIp_MeasurementModeType Mode,
  const uint8 CoreId,
  const uint8 SleepModeChk);
#endif

#if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
(ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
static uint32 Icu_lInitCallVerify(const uint8 ServiceId, const uint8 CoreId);
#endif

#if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
(ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
static uint32 Icu_lChannelVerify(
  const uint8 ServiceId,
  const Icu_17_TimerIp_ChannelType Channel,
  const uint8 CoreId);
#endif

#if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
(ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
LOCAL_INLINE uint32 Icu_lChannelCheckMode(
  const uint8 ServiceId,
  const Icu_17_TimerIp_ChannelType Channel,
  const Icu_17_TimerIp_MeasurementModeType Mode,
  const uint8 CoreId,
  const uint8 SleepModeChk);
#endif

#if (ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON) && \
(ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
LOCAL_INLINE void Icu_lGtmResetEdgeCount(
  const uint16 GlobalChannelNumber,
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * this MISRA rule,To implement efficiently IcuMeasaurementProperty as a
   * post-build parameter.Union is required*/
  Icu_17_TimerIp_ChannelData *const EdgeCountValuePtr);
#endif

#if (ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON) && \
(ICU_17_TIMERIP_GPT12_USED == STD_ON)
LOCAL_INLINE void Icu_lGpt12ResetEdgeCount(
  const uint16 GlobalChannelNumber,
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * this MISRA rule,To implement efficiently IcuMeasaurementProperty as a
   * post-build parameter.Union is required*/
  Icu_17_TimerIp_ChannelData *const EdgeCountValuePtr);
#endif

#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) && \
(ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON)
LOCAL_INLINE void Icu_lGtmEnableEdgeCount(
  const uint16 GlobalChannelNumber,
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * this MISRA rule,To implement efficiently IcuMeasaurementProperty as a
   * post-build parameter.Union is required*/
  Icu_17_TimerIp_ChannelData* const EdgeCountValuePtr);
#endif

#if ((ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON) || \
(ICU_17_TIMERIP_INCREMENTAL_INTERFACE_API == STD_ON)) && \
(ICU_17_TIMERIP_GPT12_USED == STD_ON)
LOCAL_INLINE void Icu_lGpt12EnableEdgeCount(
  const uint16 GlobalChannelNumber);
#endif

LOCAL_INLINE uint8 Icu_lGetCoreChIndex(uint8 Channel);

#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) && \
((ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON) || \
(ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON))
LOCAL_INLINE void Icu_lGtmDisableChnIrq(
  const uint16 GlobalChannelNumber);
#endif

#if ((ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON) || \
(ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON) || \
(ICU_17_TIMERIP_INCREMENTAL_INTERFACE_API == STD_ON)) && \
(ICU_17_TIMERIP_GPT12_USED == STD_ON)
static void Icu_lGpt12DisableChannel(
  const uint16 GlobalChannelNumber);
#endif

#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) && \
(ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON)
LOCAL_INLINE Icu_17_TimerIp_EdgeNumberType Icu_lGtmGetEdgeNumbers(
  const uint16 GlobalChannelNumber,
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * this MISRA rule,To implement efficiently IcuMeasaurementProperty as a
   * post-build parameter.Union is required*/
  const Icu_17_TimerIp_ChannelData* const EdgeCountValuePtr);
#endif

#if (ICU_17_TIMERIP_GPT12_USED == STD_ON) && \
(ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON)
LOCAL_INLINE Icu_17_TimerIp_EdgeNumberType Icu_lGpt12GetEdgeNumbers(
  const uint16 GlobalChannelNumber,
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * this MISRA rule,To implement efficiently IcuMeasaurementProperty as a
   * post-build parameter.Union is required*/
  const Icu_17_TimerIp_ChannelData* const EdgeCountValuePtr);
#endif

#if (ICU_17_TIMERIP_TIMESTAMP_API == STD_ON)
#if (ICU_17_TIMERIP_DEV_ERROR_DETECT ==  STD_ON) || \
(ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
LOCAL_INLINE uint32 Icu_lStartTimestampDetCheck(
  const Icu_17_TimerIp_ValueType * const BufferPtr, const uint16 BufferSize);
#endif
#endif

#if (ICU_17_TIMERIP_TIMESTAMP_API == STD_ON) && \
(ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
LOCAL_INLINE void Icu_lGtmStartTimeStamp(
  const uint16 GlobalChannelNumber);
#endif

#if (ICU_17_TIMERIP_TIMESTAMP_API == STD_ON) && \
(ICU_17_TIMERIP_CCU6_USED == STD_ON)
LOCAL_INLINE void Icu_lCcuStartTimeStamp(
    const uint16 CellUsed,
    const uint8 ActiveEdge);
#endif

#if (ICU_17_TIMERIP_TIMESTAMP_API == STD_ON) && \
(ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
LOCAL_INLINE void Icu_lGtmStopTimeStamp(
  const uint16 GlobalChannelNumber);
#endif

#if (ICU_17_TIMERIP_TIMESTAMP_API == STD_ON) && \
(ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
LOCAL_INLINE uint32 Icu_lGtmGetTimeStamp(const uint16 CellNum);
#endif

#if (ICU_17_TIMERIP_TIMESTAMP_API == STD_ON) && \
(ICU_17_TIMERIP_CCU6_USED == STD_ON)
LOCAL_INLINE uint32 Icu_lCcuGetTimeStamp(const uint16 CellUsed);
#endif

#if ((ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
(ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)) && \
((ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON) || \
(ICU_17_TIMERIP_TIMESTAMP_API == STD_ON)|| \
  (ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON) || \
  (ICU_17_TIMERIP_INCREMENTAL_INTERFACE_API == STD_ON))
static uint32 Icu_lEnDisNotificationDetCheck(
  const Icu_17_TimerIp_ChannelType Channel,
  const uint8 ServiceId, const uint8 CoreId);
#endif

#if (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON) || (ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON)
static void Icu_lEnableNotificationInterrupts(
  const uint32 IcuHwOption,
  const uint16 HwUnit,
  uint32* const GlbIndexStatusPtr);
#endif

#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)  && \
((ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON) || (ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON))
LOCAL_INLINE void Icu_lGtmClearIrqNotify(
  const uint16 GlobalChannelNumber,
  uint32* const GlbIndexStatusPtr);
#endif

#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) && \
((ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON) || (ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON))
static void Icu_lGtmIrqModify(const uint16 GlobalChannelNumber,
                              const uint8 InterruptFlag);
#endif

#if (ICU_17_TIMERIP_GPT12_USED == STD_ON) && \
(ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
static void Icu_lGpt12EnableNotification(
  const uint16 GlobalChannelNumber,
  uint32* const GlbIndexStatusPtr);
#endif

#if (ICU_17_TIMERIP_CCU6_USED == STD_ON) && \
(ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
LOCAL_INLINE void Icu_lCcu6EnableNotification(const uint16 CellUsed,
    const uint8 ActiveEdge,
    uint32* const GlbIndexStatusPtr);
#endif

#if(ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON)
static void Icu_lSetEruIgp( const uint16 EruIgcrUsed,
                            const uint8 Value);
#endif

#if (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON) || (ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON)
static void Icu_lDisableNotificationInterrupts(const uint32 IcuHwOption,
    const uint16 HwUnit);
#endif

#if (ICU_17_TIMERIP_CCU6_USED == STD_ON)  && \
(ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
LOCAL_INLINE void Icu_lCcu6CleaInterruptEnable(const uint16 CellUsed);
#endif

#if (ICU_17_TIMERIP_GPT12_USED == STD_ON) && \
(ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
LOCAL_INLINE void Icu_lGpt12DisableNotification(
  const uint16 GlobalChannelNumber);
#endif

#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) && \
(ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
LOCAL_INLINE void Icu_lGtmStartEdgeDetect(const uint16 GlobalChannelNumber);
#endif

#if (ICU_17_TIMERIP_CCU6_USED == STD_ON) && \
(ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
LOCAL_INLINE void Icu_lCcuEnableChannel(const uint16 CellUsed);
#endif

#if (ICU_17_TIMERIP_GPT12_USED == STD_ON) && \
(ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
static void Icu_lGpt12StartEdgeDetect(
  const uint16 GlobalChannelNumber, const uint16 Count);
#endif

#if (ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON)
LOCAL_INLINE void Icu_lSetEruEdge(const uint8 Edge,
                                  const uint8 EruEicrChannel);
#endif

#if (ICU_17_TIMERIP_CCU6_USED == STD_ON) && \
((ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON) || \
(ICU_17_TIMERIP_TIMESTAMP_API == STD_ON))
LOCAL_INLINE void Icu_lCcuDisableChannel(const uint16 CellUsed);
#endif

#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) && \
(ICU_17_TIMERIP_SIGNAL_MEASUREMENT_API == STD_ON)
LOCAL_INLINE uint8 Icu_lGtmStartSignalMeasurement(
  const uint16 GlobalChannelNumber,
  const uint8 SignalMode);
#endif

#if (ICU_17_TIMERIP_CCU6_USED == STD_ON) && \
(ICU_17_TIMERIP_SIGNAL_MEASUREMENT_API == STD_ON)
LOCAL_INLINE void Icu_lCcuSignalMeasHandler(
  const uint16 CellUsed,
  const uint8 SigKind,
  const uint8 CfgEdge);
#endif

#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) && \
(ICU_17_TIMERIP_SIGNAL_MEASUREMENT_API ==STD_ON)
LOCAL_INLINE void Icu_lGtmStopSignalMeasurement(
  const uint16 GlobalChannelNumber);
#endif

#if (ICU_17_TIMERIP_CCU6_USED == STD_ON) && \
(ICU_17_TIMERIP_SIGNAL_MEASUREMENT_API ==STD_ON)
LOCAL_INLINE void Icu_lCcuStopSignalMeas(const uint16 CellUsed);
#endif

#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) && \
(ICU_17_TIMERIP_GET_TIME_ELAPSED_API ==STD_ON)
LOCAL_INLINE Icu_17_TimerIp_ValueType Icu_lGtmGetTimeElapsed(
  const uint16 GlobalChannelNumber,
  uint32 *const GblIndexStatusPtr);
#endif

#if (ICU_17_TIMERIP_CCU6_USED == STD_ON) && \
(ICU_17_TIMERIP_GET_TIME_ELAPSED_API ==STD_ON)
LOCAL_INLINE Icu_17_TimerIp_ValueType Icu_lCcuGetTimeElapsed(
  const uint16 CellUsed,
  uint32 *const GblIndexStatusPtr);
#endif

#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) && \
(ICU_17_TIMERIP_GET_DUTY_CYCLE_VALUES_API ==STD_ON)
LOCAL_INLINE void Icu_lGtmGetDutyCycleValues(
  const uint16 GlobalChannelNumber,
  uint32 *const GlbIndexStatusPtr,
  Icu_17_TimerIp_DutyCycleType *const DutyCycleValues);
#endif

#if (ICU_17_TIMERIP_GET_INPUT_STATE_API == STD_ON)
#if (ICU_17_TIMERIP_DEV_ERROR_DETECT ==  STD_ON) || \
(ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
LOCAL_INLINE uint32 Icu_lGetInputStateDetCheck(
  const Icu_17_TimerIp_ChannelType Channel,
  const uint8 CoreId);
#endif
#endif

#if (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) || \
(ICU_17_TIMERIP_GPT12_USED == STD_ON)
#if (ICU_17_TIMERIP_DEV_ERROR_DETECT ==  STD_ON) || \
(ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
LOCAL_INLINE uint32 Icu_lEnableMultiEdgeDetCheck(
  const Icu_17_TimerIp_ChannelConfigType *const IcuChanPtr,
  const uint32 EdgeCount);
#endif
#endif
#endif

#if (ICU_17_TIMERIP_GTM_TIM_USED  == STD_ON) && \
(ICU_17_TIMERIP_GET_INPUT_STATE_API == STD_ON)
LOCAL_INLINE Icu_17_TimerIp_InputStateType Icu_lGtmGetInputState(
  const uint16 GlobalChannelNumber,
  uint32* const GlbIndexStatusPtr);
#endif

#if (ICU_17_TIMERIP_CCU6_USED == STD_ON) && \
(ICU_17_TIMERIP_GET_INPUT_STATE_API == STD_ON)
LOCAL_INLINE Icu_17_TimerIp_InputStateType Icu_lCcu6GetInputState(
  const uint16 CellUsed,
  uint32* const GlbIndexStatusPtr,
  const uint8 Mode,
  const uint8 Property);
#endif

#if (ICU_17_TIMERIP_GPT12_USED  == STD_ON) && \
(ICU_17_TIMERIP_GET_INPUT_STATE_API == STD_ON)
LOCAL_INLINE Icu_17_TimerIp_InputStateType Icu_lGpt12GetInputState(
  const uint16 GlobalChannelNumber,
  uint32* const  GlbIndexStatusPtr, const uint8 Mode);
#endif

#if (ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON) && \
(ICU_17_TIMERIP_GET_INPUT_STATE_API == STD_ON)
LOCAL_INLINE Icu_17_TimerIp_InputStateType Icu_lEruGetInputState(
  const uint16 HwUnit,
  uint32* const GlbIndexStatusPtr);
#endif

#if(ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
LOCAL_INLINE void Icu_lGtmChangeActiveEdge(
  const uint16 GlobalChannelNumber,
  const Icu_17_TimerIp_ActivationType ActiveEdge);
#endif

#if(ICU_17_TIMERIP_CCU6_USED == STD_ON)
LOCAL_INLINE void Icu_lCcu6SetActivationCondition(const uint16 CellUsed,
    const uint8 ActiveEdge);
#endif

#if(ICU_17_TIMERIP_GPT12_USED == STD_ON)
LOCAL_INLINE void Icu_lGpt12SetActivationCondition(const uint16 CellUsed,
    const Icu_17_TimerIp_ActivationType ActiveEdge, const uint8 TxClearFlag);
#endif

#if (ICU_17_TIMERIP_CCU6_USED == STD_ON)
LOCAL_INLINE uint8 Icu_lCcu6GetActiveEdge(
  const uint8 ActiveEdge);
#endif

#if ((ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
(ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON))
LOCAL_INLINE uint32 Icu_lSetActivationConditionDETCheck(const uint8 CoreId,
    const Icu_17_TimerIp_ChannelType Channel);
#endif

#if (ICU_17_TIMERIP_SET_MODE_API == STD_ON)
LOCAL_INLINE uint32 Icu_lSetModeBusyCheck(const uint8 CoreId);
#endif

#if (ICU_17_TIMERIP_SET_MODE_API == STD_ON) && \
(ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
LOCAL_INLINE void Icu_lChannelToSleep(
  const Icu_17_TimerIp_ChannelConfigType *const IcuChanPtr,
  uint32* const GlbIndexStatusPtr,
  const uint8 CoreId);
#endif

#if (ICU_17_TIMERIP_SET_MODE_API == STD_ON) && \
(ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
LOCAL_INLINE void Icu_lChannelToNormal(
  const Icu_17_TimerIp_ChannelConfigType *const IcuChanPtr,
  uint32* const GlbIndexStatusPtr,
  const uint8 CoreId);
#endif

#if (ICU_17_TIMERIP_CCU6_USED == STD_ON) && \
(ICU_17_TIMERIP_SIGNAL_MEASUREMENT_API ==STD_ON)
static uint16 Icu_lCcuSubtractWithOverflow(
  const uint16 SecondVal,
  const uint16 FirstVal);
#endif

#if (ICU_17_TIMERIP_DE_INIT_API == STD_ON)
#if ((ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
(ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON))
LOCAL_INLINE uint32 Icu_lDeInitDetCheck(
  const uint8 CoreId);
#endif
#endif

#if (ICU_17_TIMERIP_DE_INIT_API == STD_ON)
#if (ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON)
LOCAL_INLINE void Icu_lDeInitEru(
  const uint16 EruEicrChannel,
  const uint16 OguOutPut);
#endif
#endif

#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) && \
(ICU_17_TIMERIP_EDGE_DETECT_API ==STD_ON)
LOCAL_INLINE void Icu_lGtmStartMultiEdgeDetect
(const uint16 GlobalChannelNumber,
 const uint32 EdgeCount);
#endif

#if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
(ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
static void Icu_lReportError(const uint8 ApiId,
                             const uint8 ErrorId);
#endif
#if (ICU_17_TIMERIP_TIMESTAMP_API == STD_ON)
#if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON) || \
    (ICU_17_TIMERIP_RUNTIME_ERROR_DETECT == STD_ON) || \
    ((MCAL_AR_VERSION == MCAL_AR_422) && (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON))
static void Icu_lReportRuntimeDetError(const uint8 ApiId, const uint8 ErrorId);
#endif
#endif
#if (ICU_17_TIMERIP_MULTICORE_ERROR_DETECT == STD_ON)|| \
(ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
static void Icu_lReportMulticoreError(const uint8 ApiId,
                                      const uint8 ErrorId);
#endif

#if (ICU_17_TIMERIP_INCREMENTAL_INTERFACE_API == STD_ON)
LOCAL_INLINE void Icu_lGpt12SetCounter(const uint16 GlobalChannelNumber,
                                 const uint16 Count);
#endif

#if (ICU_17_TIMERIP_INCREMENTAL_INTERFACE_API == STD_ON)
LOCAL_INLINE uint16 Icu_lGpt12ReadCounter(const uint16 GlobalChannelNumber);
#endif

#if (ICU_17_TIMERIP_INCREMENTAL_INTERFACE_API == STD_ON)
LOCAL_INLINE Icu_17_TimerIp_EncCountDirType Icu_lGpt12ReadDir(
                                const uint16 GlobalChannelNumber);
#endif
#if (ICU_17_TIMERIP_TIMEOUT_DETECTION_API == STD_ON)
LOCAL_INLINE void Icu_lGtmSetTDUV(const uint16 GlobalChannelNumber,
    const uint32 TimeoutValue, const uint32 CTRLRegvalue);
#endif
/********************* Interrupts **************************/

#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
LOCAL_INLINE void Icu_lTim_Isr(
  const uint8 CoreChIndex, const uint32 StatusFlags);
#endif

#if (ICU_17_TIMERIP_CCU6_USED == STD_ON)
LOCAL_INLINE void Icu_lCcu_Isr(
  const uint8 CoreChIndex, const uint32 StatusFlags);
#endif

#if (ICU_17_TIMERIP_GPT12_USED == STD_ON)
LOCAL_INLINE void Icu_lGpt12_Isr(
  const uint8 CoreChIndex);
#endif

#if (ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON)
LOCAL_INLINE void Icu_lEru_Isr(
  const uint8 CoreChIndex);
#endif

#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) && \
(ICU_17_TIMERIP_EDGE_COUNT_API ==STD_ON)
LOCAL_INLINE void Icu_lGtmEdgeCountIsr(
  const uint8 ChIndex,
  const uint8 CoreId,
  const uint32* const GlbIndexStatusPtr);
#endif

#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) && \
(ICU_17_TIMERIP_SIGNAL_MEASUREMENT_API ==STD_ON)
LOCAL_INLINE void Icu_lGtmSignalMeasureIsr(
  const Icu_17_TimerIp_ChannelConfigType *const IcuChanPtr,
  uint32* const GlbIndexStatusPtr);
#endif

#if (ICU_17_TIMERIP_SIGNAL_MEASUREMENT_API ==STD_ON) && \
(ICU_17_TIMERIP_CCU6_USED ==STD_ON)
LOCAL_INLINE void Icu_lCcuSignalMeasure_Isr(
  const uint8 CoreId, uint32* const GlbIndexStatusPtr,
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr);
#endif

#if (ICU_17_TIMERIP_GPT12_USED == STD_ON) && \
(ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
LOCAL_INLINE void Icu_lGpt12EdgeDetectIsr(
  const uint16 GlobalChannelNumber, const uint16 Count);
#endif

#if (ICU_17_TIMERIP_GPT12_USED == STD_ON) && \
(ICU_17_TIMERIP_INCREMENTAL_INTERFACE_API == STD_ON)
LOCAL_INLINE void Icu_lGpt12IncrementalInterfaceIsr(
     const Icu_17_TimerIp_ChannelConfigType * const LocalIcuChanPtr)
    ;
#endif

#if (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
LOCAL_INLINE void Icu_lSignalEdgeNotification_Isr(
  const uint8 CoreId,
  const Icu_17_TimerIp_ChannelConfigType *const LocalIcuChanPtr,
  uint32 *const GlbIndexStatusPtr);
#endif

#if (ICU_17_TIMERIP_TIMESTAMP_API == STD_ON)
LOCAL_INLINE void Icu_lTimeStamp_Isr(
  const uint32 CoreId,
  const Icu_17_TimerIp_ChannelConfigType *const LocalIcuChanPtr,
  const uint32 *const GlbIndexStatusPtr);
#endif

#if (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON) || \
    (ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON)
#if (ICU_17_TIMERIP_TIMEOUT_DETECTION_API == STD_ON)
LOCAL_INLINE void Icu_lGtmTimeOutIsr(
    const Icu_17_TimerIp_ChannelConfigType * const LocalIcuChanPtr,
    uint32 * const GlbIndexStatusPtr);
#endif
#endif

/*******************************************************************************
 **                      Exported Function Definitions                        **
 ******************************************************************************/

/* Service for driver initialization */
/*******************************************************************************
** Traceability: [cover parentID= {CB34123E-B197-4592-B940-132D91A8DB57}]     **
**                                                                            **
** Syntax : void Icu_17_TimerIp_Init(const Icu_17_TimerIp_ConfigType          **
**                                                      *const ConfigPtr )    **
** Description : Driver Module Initialization                                 **
**               1.This function will initialize all relevant registers of    **
**               configured hardware (AssignedHWUnit) with the values of      **
**               structure referenced by the parameter ConfigPtr.             **
**               2. This service will disable all notifications.              **
**               3. Resources that are not configured in the configuration    **
**                  file will not be changed.                                 **
**               4. All ICU channel status is set to ICU_17_TIMERIP_IDLE      **
**               5. All used registers used by configuration will be          **
**                  initialized if Reset and Deinit API will not reset the    **
**                  registers                                                 **
**               6. Clearing of pending interrupt flags not done in this      **
**                  function.                                                 **
**               7. After initialization the mode is set to normal            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:      0x00                                                      **
**                                                                            **
** Sync/Async:      Synchronous                                               **
**                                                                            **
** Reentrancy:      Non Reentrant                                             **
**                                                                            **
** Parameters (in): ConfigPtr - Pointer to configuration set                  **
**                                                                            **
** Parameters (out):None                                                      **
**                                                                            **
** Return value:    None                                                      **
**                                                                            **
*******************************************************************************/
/*[cover parentID={8F04E18D-D28A-48c4-AF5F-42751A7C4910}]
Safety Properties
[/cover]*/
void Icu_17_TimerIp_Init(
  const Icu_17_TimerIp_ConfigType *const ConfigPtr)
{
  uint8 CoreId;

  /* Get core id which is executing currently */
  CoreId = (uint8)(Mcal_GetCpuIndex());

  /* [cover parentID={26FFBBB0-CD29-41ab-9D96-63F485D5BE1C}]
  DET or Safety is enabled
  [/cover] */
  #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON)|| \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  uint32 ErrorFlag;
  /* [cover parentID={FC54AEE3-2015-43e8-9C28-172FD3E7832A}]
  Check for DET of the API
  [/cover] */
  ErrorFlag = Icu_lInitDetCheck (ConfigPtr, CoreId);
  /* [cover parentID={4A6DB6FA-5E27-4e1c-9EC7-38EC90AB30A7}]
  Any DET occured?
  [/cover] */
  if(ICU_ERROR_FOUND != ErrorFlag)
  #endif
  {
    /* [cover parentID={92CED43A-4CD3-4134-84CB-B2DAFCD5FD27}]
    Store config pointer
    [/cover] */
    /* Store Config pointer */
    Icu_17_TimerIp_ConfigPtr = ConfigPtr;
    /* Check to identify if there is at least one channel allocated to that
     * core. This is required for master core with no channels */
    /* [cover parentID={BE7F0A03-CEBD-4a6f-BFD5-18D779D6952C}]
    Is the core configuration NULL?
    [/cover] */
    if(Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId] != NULL_PTR )
    {
      /* This function is primarily written to take care of
         variable that are directly used without assignment.
         In other words the variables that required to have a value
         of zero before Initialization. The variable that
         are assigned a value in Init are ignored in this function.
       */
      /* This function will reset all the required global variables
        that needs a zero input */
      /* [cover parentID={0EBD8081-473D-45b8-A534-2F6368E42473}]
      Reset all used global variables
      [/cover] */
      Icu_lResetGlobalVariables(CoreId);
      /* [cover parentID={D3D96CE1-7976-4b23-B24E-62D6D496A03A}]
      Initialize all the channels allocated to the core.
      [/cover] */
      Icu_lChannelInit(CoreId);
      /* [cover parentID={71685FD1-11A9-48f1-B3F3-DF403FD93164}]
      Make Icu Mode to Normal
      [/cover] */
      Icu_17_TimerIp_Varlist[CoreId]->GlobalMode = ICU_17_TIMERIP_MODE_NORMAL;
    }

    /* [cover parentID={143AADE8-34E2-4d8c-BDF4-8EE8A18F3E4D}]
    Set Status to indicate that initialization is done
    [/cover] */
    Mcal_SetBitAtomic(&Icu_17_TimerIp_InitStatus, \
                      (sint32) (CoreId * ICU_INIT_STAUS_SIZE), \
                      ICU_INIT_STAUS_SIZE, (uint32)ICU_INITIALIZED);
  }
  return;
  /* [cover parentID={5D0F49AF-3538-4586-9878-04FB9654D8D1}]
    ICU Interrupt Control Registers.
  [/cover] */
}/* End of Icu_17_TimerIp_Init() function */

#if (ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {E50652C4-DB11-427d-8F36-834197DF8CA9}]     **
**                                                                            **
** Syntax :          void Icu_17_TimerIp_EnableEdgeCount(                     **
**                               const Icu_17_TimerIp_ChannelType Channel)    **
**                                                                            **
** Description : 1. This service shall start the edge count mode.             **
**               2. The index of the channel is initialized in                **
**                  Icu_17_TimerIp_Init.                                      **
**               3. Icu_ActivityStarted Flag is set to true.                  **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x0D                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={8F04E18D-D28A-48c4-AF5F-42751A7C4910}]
Safety Properties
[/cover]*/
void Icu_17_TimerIp_EnableEdgeCount(const Icu_17_TimerIp_ChannelType Channel)
{
  /*Service to enable edge count measurement */
  /*Service available for edge count measurement */
  /*API available only in configuration ICU_17_TIMERIP_EDGE_COUNT_API */
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr; /* ROM pointer */
  #if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * this MISRA rule,To implement efficiently IcuMeasaurementProperty as a
   * post-build parameter.Union is required*/
  Icu_17_TimerIp_ChannelData* EdgeCountValuePtr;
  uint8 ChIndex;
  #endif
  uint32* GlbIndexStatusPtr;
  uint32 IcuOption;
  uint16 CellUsed;
  uint8 CoreChIndex;
  uint8 CoreId;
  /* Get core id which is executing currently */
  CoreId = (uint8)(Mcal_GetCpuIndex());
  /* [cover parentID={339D5393-D47E-4f48-85E7-3B0A3E771EEF}]
  DET or Safety is enabled
  [/cover] */
  #if (ICU_17_TIMERIP_DEV_ERROR_DETECT  == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  uint32 ErrorFlag;

  /* [cover parentID={66256C5D-2D81-4348-B713-5CFDB4C77CFD}]
  Preconditions check, sleep mode check and channel validation.
  [/cover] */
  ErrorFlag = Icu_lNotifiDetCheck(Channel,
                                  ICU_17_TIMERIP_SID_ENABLEEDGECOUNT,
                                  ICU_17_TIMERIP_MODE_EDGE_COUNTER,
                                  CoreId, ICU_FLAG_SET);
  /* Proceed only if no error was found */
  /* [cover parentID={1F23D513-590B-4596-861E-8E73D4BD82A9}]
  Any DET reported ?
  [/cover] */
  if (ICU_ERROR_FOUND != ErrorFlag)
  #endif
    /* #if (ICU_17_TIMERIP_DEV_ERROR_DETECT  == STD_ON) ||
     * (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON) */
  {
    /* Extract the Core Specific channel index */
    CoreChIndex = Icu_lGetCoreChIndex((uint8)Channel);
    /* Initialize ICU configured channel ROM pointer */
    LocalIcuChanPtr = &((Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->
                                                ChannelConfigPtr)[CoreChIndex]);
    #if ((ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_OFF) && \
    (ICU_17_TIMERIP_SAFETY_ENABLE == STD_OFF))
    /* [cover parentID={09503072-5305-4f0b-BF02-B895C3336A27}]
    Is the channel mode Edge Count?
    [/cover] */
    /* Check if the mode is valid */
    if((uint32)ICU_17_TIMERIP_MODE_EDGE_COUNTER ==
          LocalIcuChanPtr->IcuProperties.MeasurementMode)
    #endif
    {
      /* Extract the address to the channel status */
      GlbIndexStatusPtr =
        &((Icu_17_TimerIp_Varlist[CoreId]->GlbIndexStatusBasePtr)[CoreChIndex]);
      /* [cover parentID={BA31B49B-0170-4e13-A3BB-B18347730907}]
      Is the channel's edge counting activity started?
      [/cover] */
      /* Check if the Edge counting has already started */
      if(ICU_ACTIVITY_STARTED != Mcal_GetBitAtomic(
                          *GlbIndexStatusPtr, ICU_CHNL_ACTIVITY_STARTED_POS, 1))
      {
        CellUsed = (uint16)LocalIcuChanPtr->IcuProperties.AssignedHwUnitNumber;
        /* Perform the activity only if the channel is inactive previously */
        /* Depending on ICU option take action */
        IcuOption = (uint32)LocalIcuChanPtr->IcuProperties.AssignedHwUnit;
        switch(IcuOption)
        {
          /* for GTM - TIM signals */
          /* [cover parentID={1EB53173-0A41-4a61-A64A-9B07B6648FE3}]
          Is ICU option GTM?
          [/cover] */
          case ICU_17_TIMERIP_GTM_OPTION:
            /* [cover parentID={9F5600C8-22A9-40c5-879B-58396D588A31}]
            Enable GTM specific  Edge Count
            [/cover] */
            #if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) && \
            (ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON)
            /* Retrieve Mode specific channel index */
            ChIndex = LocalIcuChanPtr->ModeMappingIndex;
            /* Extract the Edge Count Value address */
            EdgeCountValuePtr =
              &((Icu_17_TimerIp_Varlist[CoreId]->ChannelDataBasePtr)[ChIndex]);
            /* Call the GTM specific Enable Edge Count internal function */
            Icu_lGtmEnableEdgeCount(CellUsed, EdgeCountValuePtr);
            #endif
            /*(ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) &&
              (ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON)*/
            break;
          default: /* ICU_17_TIMERIP_GPT12_OPTION */
            /* [cover parentID={25D6FA7A-0E84-4711-B22C-9A00B5502C0A}]
            Enable Edge Count for GPT12 channel
            [/cover] */
            #if (ICU_17_TIMERIP_GPT12_USED == STD_ON) && \
            (ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON)
            /* Call the GPT12 specific Enable Edge Count internal function */
            Icu_lGpt12EnableEdgeCount(CellUsed);
            #endif
            break;
        }
        /* Set the Edge Counting activity to started */
        Mcal_SetBitAtomic( \
            GlbIndexStatusPtr, (sint32)ICU_CHNL_ACTIVITY_STARTED_POS,\
            ICU_CHNL_ACTIVITY_BIT_LENGTH, (uint32)ICU_ACTIVITY_STARTED);
      }
      else
      {
        /* Edge counting is active */
        /* Nothing to do */
      }
    }
  }
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer GlbIndexStatusPtr is
   * accessed using assembly instruction. */
  /* [cover parentID={5D0F49AF-3538-4586-9878-04FB9654D8D1}]
    ICU Interrupt Control Registers.
  [/cover] */
}
/* End of function Icu_17_TimerIp_EnableEdgeCount */
#endif

#if (ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {598DE589-11F1-4357-A28F-7BB348317AED}]     **
**                                                                            **
** Syntax :          void Icu_17_TimerIp_DisableEdgeCount(                    **
**                                const Icu_17_TimerIp_ChannelType Channel )  **
**                                                                            **
** Description : 1. This service will stop the edge counting capability       **
**                  of a channel.                                             **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x0E                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={8F04E18D-D28A-48c4-AF5F-42751A7C4910}]
Safety Properties
[/cover]*/
void Icu_17_TimerIp_DisableEdgeCount(const Icu_17_TimerIp_ChannelType Channel)
{
  /*Service to disable the edge count */
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr; /* ROM pointer */
  uint16 CellUsed;
  uint32* GlbIndexStatusPtr;
  uint32 IcuOption;
  uint8 CoreChIndex;
  uint8 CoreId;
  /* Get core id which is executing currently */
  CoreId = (uint8)(Mcal_GetCpuIndex());
  /* [cover parentID={FA4B9F81-5B08-499c-BBC2-331F574D41A6}]
  DET or Safety is enabled
  [/cover] */
  #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  uint32 ErrorFlag;
  /* [cover parentID={251F1AAF-603F-4f79-97B6-81A2F635C84E}]
  Preconditions check, sleep mode check and channel validation
  [/cover] */
  /* Verify any error is there for DET */
  ErrorFlag = Icu_lNotifiDetCheck(Channel,
                                  ICU_17_TIMERIP_SID_DISABLEEDGECOUNT,
                                  ICU_17_TIMERIP_MODE_EDGE_COUNTER,
                                  CoreId, ICU_FLAG_SET);
  /* [cover parentID={50A442D5-E1F8-40c9-AF0E-5153A2E6CA47}]
  Any DET reported
  [/cover] */
  if(ICU_ERROR_FOUND != ErrorFlag)
  #endif
    /* #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) ||
     * (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON) */
  {
    /* Initialize ICU configured channel ROM pointer */
    CoreChIndex = Icu_lGetCoreChIndex((uint8)Channel);
    LocalIcuChanPtr = &((Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->
                                                ChannelConfigPtr)[CoreChIndex]);
    #if((ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_OFF) && \
    (ICU_17_TIMERIP_SAFETY_ENABLE == STD_OFF))
    /* Check if the mode is valid */
    /* [cover parentID={9D2E6B4A-5CC8-4ea8-AC28-EE4821B57286}]
    Is the channel mode Edge Count?
    [/cover] */
    if((uint32)ICU_17_TIMERIP_MODE_EDGE_COUNTER ==
          LocalIcuChanPtr->IcuProperties.MeasurementMode)
    #endif
    {
      /* Extract the actual cell number */
      CellUsed = (uint16)LocalIcuChanPtr->IcuProperties.AssignedHwUnitNumber;
      /* Extract the address to the Global Index Status value */
      GlbIndexStatusPtr =
        &((Icu_17_TimerIp_Varlist[CoreId]->GlbIndexStatusBasePtr)[CoreChIndex]);
      /* [cover parentID={DE2474C0-FEE6-4735-AC5A-7E706984E90A}]
      Is the channel's edge counting activity started?
      [/cover] */
      /* Perform the action only if the channel is active */
      if(ICU_ACTIVITY_STARTED ==
       Mcal_GetBitAtomic(*GlbIndexStatusPtr, ICU_CHNL_ACTIVITY_STARTED_POS, 1))
      {
        /* Depending on ICU option take action */
        IcuOption = (uint32)LocalIcuChanPtr->IcuProperties.AssignedHwUnit;
        switch(IcuOption)
        {
          /* [cover parentID={44B7B7EF-90CB-4761-8B54-1B2C659F05AC}]
          IF ICU option is GTM
          [/cover] */
          case ICU_17_TIMERIP_GTM_OPTION:
            /* [cover parentID={C4FBEDFD-A974-450f-ADED-98442905DB6B}]
            Deactivate the edges for configured HW resource
            [/cover] */
            #if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
            /* Deactivate the edges for configured HW resource */
            Icu_lGtmDisableChnIrq(CellUsed);
            /* Stop the activity started flag */
            /* bit 5 is activity started status */
            /* [cover parentID={AEB9499F-F843-42e2-8DF0-274AC38917E4}]
            Reset the activity started flag
            [/cover] */
            Mcal_SetBitAtomic( \
                GlbIndexStatusPtr, (sint32)ICU_CHNL_ACTIVITY_STARTED_POS,\
                ICU_CHNL_ACTIVITY_BIT_LENGTH, 0U);
            #endif
            break;
          default:
            /* [cover parentID={B2AD4C31-3CE5-4a4c-950F-D83B16ACC62F}]
            Deactivate the edges for configured GPT12 resource
            [/cover] */
            #if (ICU_17_TIMERIP_GPT12_USED == STD_ON)
            Icu_lGpt12DisableChannel(CellUsed);
            /* Stop the activity started flag */
            /* bit 5 is activity started status */
            /* [cover parentID={839C381E-29A3-45c8-A216-D9BC3B2E923C}]
            Reset the activity started flag
            [/cover] */
            Mcal_SetBitAtomic( \
                GlbIndexStatusPtr, (sint32)ICU_CHNL_ACTIVITY_STARTED_POS,\
                ICU_CHNL_ACTIVITY_BIT_LENGTH, 0U);
            #endif
            break;
        }
      }
      else
      {
        /* Nothing to do */
      }
    }
  }
  /* [cover parentID={5D0F49AF-3538-4586-9878-04FB9654D8D1}]
    ICU Interrupt Control Registers.
  [/cover] */
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer GlbIndexStatusPtr is
   * accessed using assembly instruction. */
}/* End of function Icu_17_TimerIp_DisableEdgeCount */
#endif

#if (ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {ACC9E9C3-8470-43db-8BD7-85AE21AEE37F}]     **
**                                                                            **
** Syntax :          void Icu_17_TimerIp_ResetEdgeCount(                      **
**                              const Icu_17_TimerIp_ChannelType Channel )    **
**                                                                            **
** Description : This service will set the edge counter variable to zero.     **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x0C                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={8F04E18D-D28A-48c4-AF5F-42751A7C4910}]
Safety Properties
[/cover]*/
void Icu_17_TimerIp_ResetEdgeCount(const Icu_17_TimerIp_ChannelType Channel)
{
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr; /* ROM pointer */
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * this MISRA rule,To implement efficiently IcuMeasaurementProperty as a
   * post-build parameter.Union is required*/
  Icu_17_TimerIp_ChannelData *EdgeCountValuePtr;
  uint32 IcuOption;
  uint16 CellUsed;
  uint8 ChIndex;
  uint8 CoreChIndex;
  uint8 CoreId;
  #if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
  const uint32 * GlbIndexStatusPtr;
  #endif

  /* Get core id which is executing currently */
  CoreId = (uint8)(Mcal_GetCpuIndex());
  /* [cover parentID={4267CB91-3670-485a-B15A-6BC599FF848F}]
  DET or Safety is enabled
  [/cover] */
  #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  uint32 ErrorFlag;
  /* Verify any error is there for DET */
  /* [cover parentID={4517C6CC-EA26-426b-8051-34045CF59879}]
  Preconditions check, sleep mode check and channel validation
  [/cover] */
  ErrorFlag = Icu_lNotifiDetCheck(Channel,
                                  ICU_17_TIMERIP_SID_RESETEDGECOUNT,
                                  ICU_17_TIMERIP_MODE_EDGE_COUNTER,
                                  CoreId, ICU_FLAG_SET);
  /* Proceed only if no error was found */
  /* [cover parentID={4A729CF2-4C5B-48b0-93EF-189D1A69FF53}]
  Is any error reported in previous call?
  [/cover] */
  if (ICU_ERROR_FOUND != ErrorFlag)
  #endif
    /* #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) ||
     * (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON) */
  {
    /* Extract the Core Specific channel index */
    CoreChIndex = Icu_lGetCoreChIndex((uint8)Channel);
    /* Channel Pointer is extracted */
    LocalIcuChanPtr = &((Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->
                                                ChannelConfigPtr)[CoreChIndex]);
    /* Retrieve the mode specific channel Index */
    ChIndex = LocalIcuChanPtr->ModeMappingIndex;
    /* Extract the actual cell number */
    CellUsed = (uint16)LocalIcuChanPtr->IcuProperties.AssignedHwUnitNumber;
    /* Extract the address to the edge count value */
    EdgeCountValuePtr =
           &((Icu_17_TimerIp_Varlist[CoreId]->ChannelDataBasePtr)[ChIndex]);
    /* Depending on ICU option take action */
    IcuOption = (uint32)LocalIcuChanPtr->IcuProperties.AssignedHwUnit;
    switch(IcuOption)
    {
      /* for GTM - TIM signals */
      /* [cover parentID={A0A5F7B5-9334-4f1c-A25A-A4A5545FAFA6}]
      If ICU option is GTM
      [/cover] */
      case ICU_17_TIMERIP_GTM_OPTION:
        #if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
        /* [cover parentID={CA8648E2-0631-4b5f-86ED-DD686C2B5919}]
        DET or safety is enabled
        [/cover] */
#if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
        /* [cover parentID={66059F5C-1EAF-44ae-A548-940F9802048E}]
        Is timeout feature exclusive?
        [/cover] */
        if((uint32)ICU_SET_BIT == LocalIcuChanPtr->IcuProperties.IsTimeOutExclusive)
        {
          ErrorFlag = (uint32) ICU_ERROR_FOUND;
          /* [cover parentID={F7F1DB36-88A9-4e0c-B8C4-A7D522D6ED54}]
          Report invalid channel
          [/cover] */
          Icu_lReportError(
            ICU_17_TIMERIP_SID_RESETEDGECOUNT,
            ICU_17_TIMERIP_E_PARAM_CHANNEL);
        }
        if (ICU_ERROR_FOUND != ErrorFlag)
#endif
        {
        GlbIndexStatusPtr =
        &((Icu_17_TimerIp_Varlist[CoreId]->GlbIndexStatusBasePtr)[CoreChIndex]);
        /*Reset in progress flag set to 1*/
        /* [cover parentID={DE8141D9-0B77-448a-BDDA-9DA50B7599CE}]
        Set Edge Count Reset Activity Started flag atomically
        [/cover] */
        Mcal_SetBitAtomic(GlbIndexStatusPtr, ICU_CHNL_RSTEDGE_STAT_POS, \
                          ICU_CHNL_RSTEDGE_STAT_BIT_LENGTH, (uint32 )1U);
        /* Reset the values to 0 */
        /* [cover parentID={5B14631A-CAA9-456b-9276-ADB2F8AAA98A}]
         Reset the counter for a GTM channel.
         [/cover] */
        /* Set the counters to zero */
        Icu_lGtmResetEdgeCount(CellUsed, EdgeCountValuePtr);
        /* [cover parentID={738BD050-529D-4b61-BE5C-52D1DF8979A9}]
        Reset Edge Count Reset Activity started flag atomically
        [/cover] */
        /*Reset in progress flag set to 0*/
        Mcal_SetBitAtomic(GlbIndexStatusPtr, ICU_CHNL_RSTEDGE_STAT_POS,
                          ICU_CHNL_RSTEDGE_STAT_BIT_LENGTH, (uint32 )0U);
        }
        #endif
        break;
      default: /* ICU_17_TIMERIP_GPT12_OPTION */
        /* for GPT12 signals */
        #if (ICU_17_TIMERIP_GPT12_USED == STD_ON)
        /* Set the counters to zero */
        /* [cover parentID={FF23AC6A-6EE1-47bf-957E-15628DE3A1AF}]
         Reset the counter for a GPT12 channel
         [/cover] */
        Icu_lGpt12ResetEdgeCount(CellUsed, EdgeCountValuePtr);
        #endif
        break;
    }
  }
  /* MISRA2012_RULE_2_2_JUSTIFICATION: No side effects foreseen
       * by violating this MISRA rule, as the variable GlbIndexStatusPtr is
       * accessed using assembly instruction. */
  /* [cover parentID={5D0F49AF-3538-4586-9878-04FB9654D8D1}]
    ICU Interrupt Control Registers.
  [/cover] */
}
/* End of function Icu_17_TimerIp_ResetEdgeCount */
#endif

#if (ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {0D016966-EE8E-4b3e-BB9F-4F9F32831278}]     **
**                                                                            **
** Syntax :Icu_17_TimerIp_EdgeNumberType Icu_17_TimerIp_GetEdgeNumbers(       **
**                                 const Icu_17_TimerIp_ChannelType Channel ) **
**                                                                            **
** Description : 1. This service will return the number of edges counted      **
**                  for the channel specified.                                **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x0F                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     Icu_17_TimerIp_EdgeNumberType : Current edge counter     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={8F04E18D-D28A-48c4-AF5F-42751A7C4910}]
Safety Properties
[/cover]*/
Icu_17_TimerIp_EdgeNumberType Icu_17_TimerIp_GetEdgeNumbers(
  const Icu_17_TimerIp_ChannelType Channel)
{
  /* Service to return the edge numbers */
  /* Configuration ICU_17_TIMERIP_EDGE_COUNT_API  */
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr; /* ROM pointer */
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * MISRA rule,To implement efficiently IcuMeasaurementProperty as a post-build
   * parameter.Union is required*/
  const Icu_17_TimerIp_ChannelData *EdgeCountValuePtr;
  Icu_17_TimerIp_EdgeNumberType RetVal;
  uint32 IcuOption;
  uint16 CellUsed;
  uint8 CoreChIndex;
  uint8 ChIndex;
  uint8 CoreId;
  /* Get core id which is executing currently */
  CoreId = (uint8)(Mcal_GetCpuIndex());
  /* [cover parentID={C21BAB2E-393E-46e6-916F-922E31488BE7}]
  DET or Safety is enabled
  [/cover] */
  #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  uint32 ErrorFlag;
  /* [cover parentID={7DA8CD51-6B53-460b-9289-BED8892B4FF3}]
  Preconditions check, sleep mode check and channel validation
  [/cover] */
  /* Verify any error is there for DET */
  ErrorFlag = Icu_lNotifiDetCheck(Channel,
                                  ICU_17_TIMERIP_SID_GETEDGENUMBERS,
                                  ICU_17_TIMERIP_MODE_EDGE_COUNTER,
                                  CoreId, ICU_FLAG_SET);
  /* [cover parentID={71BD3BDD-B410-4888-A826-8151F01ADC27}]
  Any DET reported
  [/cover] */
  if(ICU_ERROR_FOUND != ErrorFlag)
  #endif
    /* #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) ||
     * (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON) */
  {
    /* Initialize ICU configured channel ROM pointer */
    CoreChIndex = Icu_lGetCoreChIndex((uint8)Channel);
    /* Initialize ICU configured channel ROM pointer */
    LocalIcuChanPtr = &((Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->
                                                ChannelConfigPtr)[CoreChIndex]);
    /* Extract the actual cell number */
    CellUsed = (uint16)LocalIcuChanPtr->IcuProperties.AssignedHwUnitNumber;
    /* Extract the channel Index */
    ChIndex = LocalIcuChanPtr->ModeMappingIndex;
    /* Extract the address to the edge count value */
    EdgeCountValuePtr =
        &((Icu_17_TimerIp_Varlist[CoreId]->ChannelDataBasePtr)[ChIndex]);

    /* Depending on ICU option take action */
    IcuOption = (uint32)LocalIcuChanPtr->IcuProperties.AssignedHwUnit;

    /* [cover parentID={F097AD87-D1B1-450e-9680-EE3021767CA3}]
    Set edge number to zero
    [/cover] */
    RetVal =  (Icu_17_TimerIp_EdgeNumberType)0;
    /* Channel should be either GTM or GPT12 */
    #if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
    /* [cover parentID={868F3B3F-56C4-448f-A12F-349010192FA2}]
    If ICU option is GTM
    [/cover] */
    if(IcuOption == ICU_17_TIMERIP_GTM_OPTION)
    {
      /* [cover parentID={7AADB091-DDBC-4373-95BA-01F84D0DE662}]
      Det or safety is enabled
      [/cover] */
#if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
      /* [cover parentID={46F59BF4-2AA2-47c2-956E-9E07EBC5B56C}]
      Is timeout feature exclusive?
      [/cover] */
      if((uint32)ICU_SET_BIT == LocalIcuChanPtr->IcuProperties.IsTimeOutExclusive)
      {
        ErrorFlag = (uint32) ICU_ERROR_FOUND;
        /* [cover parentID={3BA7E0C2-B959-4a3b-8FCE-76C0F0EE8DD0}]
        Report invalid channel
        [/cover] */
        Icu_lReportError(
          ICU_17_TIMERIP_SID_GETEDGENUMBERS,
          ICU_17_TIMERIP_E_PARAM_CHANNEL);
      }
      if (ICU_ERROR_FOUND != ErrorFlag)
#endif
      {
        /* [cover parentID={F174B3F3-FF19-4c3f-A103-7F404DB02458}]
        Get edge number for GTM channel
        [/cover] */
        RetVal =  Icu_lGtmGetEdgeNumbers(CellUsed, EdgeCountValuePtr);
      }
    }
    #endif
    #if (ICU_17_TIMERIP_GPT12_USED == STD_ON)
      if(IcuOption == ICU_17_TIMERIP_GPT12_OPTION)
      {
        /* [cover parentID={01C18AA0-57BB-4cf0-AC7B-2930BED771AE}]
        Get edge numbers for GPT12 channel.
        [/cover] */
        RetVal =  Icu_lGpt12GetEdgeNumbers(CellUsed, EdgeCountValuePtr);
      }
    #endif
  }
  #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  else
  {
    /* [cover parentID={D724C54D-C2AC-476c-89D9-3B382C61B75F}]
    Set edge number to zero
    [/cover] */
    RetVal = (Icu_17_TimerIp_EdgeNumberType)0;
  }
  #endif
  /*   #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) */
  return (RetVal);
  /* [cover parentID={5D0F49AF-3538-4586-9878-04FB9654D8D1}]
    ICU Interrupt Control Registers.
  [/cover] */
}/* End of function Icu_17_TimerIp_GetEdgeNumbers */
#endif


#if (ICU_17_TIMERIP_TIMESTAMP_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {A3B8215B-1662-42c7-BBF2-C1B7655223BA}]     **
**                                                                            **
** Syntax :void Icu_17_TimerIp_StartTimestamp(                                **
**                                const Icu_17_TimerIp_ChannelType Channel,   **
**                               Icu_17_TimerIp_ValueType *const BufferPtr,   **
**                                                 const uint16 BufferSize,   **
**                                             const uint16 NotifyInterval)   **
**                                                                            **
** Description : 1. This service will start the TimeStamp Capture.            **
**               2. This service will also set the Notification Flag, if      **
**                  NotifyInterval is greater than zero.                      **
**               3. The Notifications is  done in ISR Only.                   **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x09                                                     **
**                                                                            **
** Sync/Async:       Asynchronous                                             **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                   BufferSize - Size of the Buffer                          **
**                   NotifyInterval - Interval for Timestamp Notifications    **
**                                                                            **
** Parameters (out):                                                          **
**                   BufferPtr - Starting address of Buffer, that will        **
**                               hold the timer capture values                **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={8F04E18D-D28A-48c4-AF5F-42751A7C4910}]
Safety Properties
[/cover]*/
void Icu_17_TimerIp_StartTimestamp(
  const Icu_17_TimerIp_ChannelType Channel,
  Icu_17_TimerIp_ValueType *const BufferPtr,
  const uint16 BufferSize,
  const uint16 NotifyInterval)
{
  /* Service to capture Timestamp values */
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr; /* ROM pointer */
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * MISRA rule,To implement efficiently IcuMeasaurementProperty as a post-build
   * parameter.Union is required*/
  Icu_17_TimerIp_ChannelData *ChannelDataPtr;
  uint32* GlbIndexStatusPtr;
  uint32 IcuOption;
  uint16 CellUsed;
  uint8 ChIndex; /* Local Ram Index */
  uint8 CoreChIndex;
  uint8 CoreId;

  /* Get core id which is executing currently */
  CoreId = (uint8)(Mcal_GetCpuIndex());
  /* [cover parentID={C5ACF265-5009-46bd-AEE5-145C9E87825A}]
  DET or Safety is enabled
  [/cover] */
  #if ((ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON))
  uint32 ErrorFlag;
  /* [cover parentID={C4E01271-A0BB-4e0c-BA03-931458FF4C09}]
  Preconditions check, sleep mode check and channel validation
  [/cover] */
  /* Verify any error is there for DET */
  ErrorFlag = Icu_lNotifiDetCheck(Channel,
                                  ICU_17_TIMERIP_SID_STARTTIMESTAMP,
                                  ICU_17_TIMERIP_MODE_TIMESTAMP,
                                  CoreId, ICU_FLAG_SET);
  /* [cover parentID={E8232CFD-8BF1-4743-B89B-055C5A3E8567}]
  If any DET reported
  [/cover] */
  if (ICU_ERROR_FOUND != ErrorFlag)
  {
    /* [cover parentID={B90611DA-3348-4592-8EF5-BC508DAE4D30}]
    Input parameter range check
    [/cover] */
    ErrorFlag = Icu_lStartTimestampDetCheck(BufferPtr, BufferSize);
  }
  /* [cover parentID={8B307573-086F-4dd3-85BA-AC0E8CE84145}]
  Any error detected?
  [/cover] */
  if (ICU_ERROR_FOUND != ErrorFlag)
  #endif
{
  /* Retrieve the Index stored in IndexStore */
    CoreChIndex = Icu_lGetCoreChIndex((uint8)Channel);
    /* Initialize ICU configured channel ROM pointer */
    LocalIcuChanPtr = &((Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->
                                                ChannelConfigPtr)[CoreChIndex]);
    #if ((ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_OFF) && \
    (ICU_17_TIMERIP_SAFETY_ENABLE == STD_OFF))
    /* Check if the mode is valid */
    /* [cover parentID={38240FDF-C76F-4686-BEEA-E813EC06EC84}]
    Is the channel mode timestamp?
    [/cover] */
    if ((uint32)ICU_17_TIMERIP_MODE_TIMESTAMP == \
          LocalIcuChanPtr->IcuProperties.MeasurementMode)
    #endif
    {
      /* [cover parentID={35C4D0BC-E9A3-45c8-B24D-A6F2B8289DE1}]
      DET or safety is enabled.
      [/cover] */
      #if ((ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
      (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON))
      /* [cover parentID={9A8FFF0A-A789-4a50-98E0-9F3F7F95B057}]
      Is Notification function available?
      [/cover] */
      if(NULL_PTR != LocalIcuChanPtr->NotificationPointer)
      {
        /* [cover parentID={77606516-3B5B-45bf-B8B1-44B488E3703C}]
        Is notify interval valid?
        [/cover] */
        if (NotifyInterval == (uint16)0U)
        {
          ErrorFlag = ICU_ERROR_FOUND;
          /* [cover parentID={D3A286EF-0DD1-43f8-A5D5-01F0C4EE2C59}]
          Report an error to indicate invalid notify interval.
          [/cover] */
          Icu_lReportError(
            ICU_17_TIMERIP_SID_STARTTIMESTAMP,
            ICU_17_TIMERIP_E_PARAM_NOTIFY_INTERVAL
          ); /* Report Error */
        }
        /* [cover parentID={FAB25210-6430-4502-9B8A-DCC9BAE45CFA}]
        Is safety enabled
        [/cover] */
        #if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
        /* [cover parentID={8A650A89-F11C-4824-A21F-69E9AC65A14C}]
          Is NotifyInterval larger than buffer size for a linear buffer type?
        [/cover] */
        /* NotifyInterval larger than buffer size for circular buffer is valid*/
        /* ErrorFlag is not required to check as ErrorFlag is set only if
           NotifyInterval is Zero. And if NotifyInterval is zero, it can never
           be equal to BufferSize which is noever zero.*/
        if((NotifyInterval > BufferSize) && \
            ((uint8)ICU_17_TIMERIP_LINEAR_BUFFER == \
             (uint8)(LocalIcuChanPtr->IcuProperties.MeasurementProperty)))
        {
          ErrorFlag = ICU_ERROR_FOUND;
          /* Report an error */
          /* [cover parentID={FDFC01CB-2572-4be1-9E04-A4AA1C3E547F}]
          Report an error to indicate implausible notify interval.
          [/cover] */
          Mcal_ReportSafetyError(
            ICU_17_TIMERIP_MODULE_ID,
            ICU_17_TIMERIP_INSTANCE_ID,
            ICU_17_TIMERIP_SID_STARTTIMESTAMP,
            ICU_17_TIMERIP_E_PARAM_IMPLAUSIBLE_NOTIFY_INTERVAL);
        }
        #endif
      }
      if (ICU_ERROR_FOUND != ErrorFlag)
      #endif
      {

        GlbIndexStatusPtr =
        &((Icu_17_TimerIp_Varlist[CoreId]->GlbIndexStatusBasePtr)[CoreChIndex]);
        /* [cover parentID={386114FB-A250-4267-ADD3-87E56CFE5BDB}]
        Reset the channel activity started flag to stop any previously
        started time stamping activity.
        [/cover] */
        /* Reset the ICU_ACTIVITY_STARTED flag */
        Mcal_SetBitAtomic( \
            GlbIndexStatusPtr, (sint32)ICU_CHNL_ACTIVITY_STARTED_POS,\
            1, (uint32)0);
        ChIndex = LocalIcuChanPtr->ModeMappingIndex;
        /* Calculate the address in a pointer variable */
        ChannelDataPtr =
               &((Icu_17_TimerIp_Varlist[CoreId]->ChannelDataBasePtr)[ChIndex]);
        /* Initialize the counter to zero */
        ChannelDataPtr->TimeCaptureParas.Counter = (uint16)0U;
        /* Initialize the Buffer size */
        ChannelDataPtr->TimeCaptureParas.Size = BufferSize;
        /* Initialize the Notify Interval to the structure member Notify */
        ChannelDataPtr->TimeCaptureParas.Notify = NotifyInterval;
        /* Notify Counter is also initialized with NotifyInterval,This value
         * will be changed to monitor the no of counters in order to fire the
         * Notifications*/
        ChannelDataPtr->TimeCaptureParas.NotifyCounter = NotifyInterval;
        /* Pointer to Buffer Pointer where values to be stored */
        ChannelDataPtr->TimeCaptureParas.Address = BufferPtr;
        CellUsed =(uint16)LocalIcuChanPtr->IcuProperties.
                AssignedHwUnitNumber;
        /* Depending on ICU option take action */
        IcuOption = (uint32)LocalIcuChanPtr->IcuProperties.AssignedHwUnit;
        switch(IcuOption)
        {
          /* [cover parentID={88BD0DC8-2769-430e-873F-CCB221E4A03E}]
          IF ICU option is GTM
          [/cover] */
          case ICU_17_TIMERIP_GTM_OPTION:
          #if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
            /* [cover parentID={078C4430-9638-466a-80B3-D8142CBB237D}]
            Start the TIM Channel
            [/cover] */
            Icu_lGtmStartTimeStamp(CellUsed);
          #endif
            break;
          default:
          #if (ICU_17_TIMERIP_CCU6_USED == STD_ON)
            /* [cover parentID={CD277E65-431C-4ec0-9AD8-177E2A8EE3C4}]
            Start the CCU Channel
            [/cover] */
            Icu_lCcuStartTimeStamp(CellUsed,
                  (uint8)Mcal_GetBitAtomic(*GlbIndexStatusPtr,
                  ICU_CHNL_EDGE_POS,ICU_CHNL_EDGE_BIT_LENGTH));
          #endif
            break;
        }
        /* [cover parentID={32FE0FFF-E9E6-4fb5-88BB-6355D4784D41}]
        Set the ICU_ACTIVITY_STARTED flag
        [/cover] */
        Mcal_SetBitAtomic( \
             GlbIndexStatusPtr, (sint32)ICU_CHNL_ACTIVITY_STARTED_POS,\
             ICU_CHNL_ACTIVITY_BIT_LENGTH, (uint32)ICU_ACTIVITY_STARTED);

      }
    }
  }
  /* [cover parentID={5D0F49AF-3538-4586-9878-04FB9654D8D1}]
    ICU Interrupt Control Registers.
  [/cover] */
  /* MISRA2012_RULE_2_2_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the variable GlbIndexStatusPtr is
   * accessed using assembly instruction. */
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer GlbIndexStatusPtr is
   * accessed using assembly instruction. */
}/* End of function Icu_17_TimerIp_StartTimestamp */
#endif

#if (ICU_17_TIMERIP_TIMESTAMP_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {DF190993-8F2D-4b88-B1D8-C0D38840C6BB}]     **
**                                                                            **
** Syntax :           void Icu_17_TimerIp_StopTimestamp(                      **
**                              const Icu_17_TimerIp_ChannelType Channel )    **
**                                                                            **
** Description : 1. This service will stop the TimeStamp Capture.             **
**               2. This service will also deactivate the interrupt flags.    **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x0A                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={8F04E18D-D28A-48c4-AF5F-42751A7C4910}]
Safety Properties
[/cover]*/
void Icu_17_TimerIp_StopTimestamp(
  const Icu_17_TimerIp_ChannelType Channel)
{
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr; /* ROM pointer */
  uint32* GlbIndexStatusPtr;
#if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON) || \
    (ICU_17_TIMERIP_RUNTIME_ERROR_DETECT == STD_ON) || \
    ((ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON))
  uint32 ErrorFlag = ICU_ERROR_NOT_FOUND;
#endif
  uint32 IcuOption;
  uint16 CellUsed;
  uint8 CoreChIndex;
  uint8 CoreId;

  /* Get core id which is executing currently */
  CoreId = (uint8)(Mcal_GetCpuIndex());
  /* [cover parentID={954E8EC6-BEB3-44b6-A0BE-766A655F8550}]
  DET or Safety is enabled
  [/cover] */
  #if ((ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON))
  /* Verify any error is there for DET */
  /* [cover parentID={F6733CFB-EFC3-4e8d-998D-8B19DAFA8109}]
  Preconditions check, sleep mode check and channel validation
  [/cover] */
  ErrorFlag = Icu_lNotifiDetCheck(Channel,
                                  ICU_17_TIMERIP_SID_STOPTIMESTAMP,
                                  ICU_17_TIMERIP_MODE_TIMESTAMP,
                                  CoreId, ICU_FLAG_SET);
  /* [cover parentID={F65FB5C5-40A4-491e-9BEA-2664EBA3D8FC}]
  Any DET reported
  [/cover] */
  if (ICU_ERROR_FOUND != ErrorFlag)
  #endif
  {
    /* Extract the Core Specific channel index */
    CoreChIndex = Icu_lGetCoreChIndex((uint8)Channel);
    /* Initialize ICU configured channel ROM pointer */
    LocalIcuChanPtr = &((Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->
                                                ChannelConfigPtr)[CoreChIndex]);
    #if ((ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_OFF) && \
    (ICU_17_TIMERIP_SAFETY_ENABLE == STD_OFF))
    /* Check if the mode is valid */
    /* [cover parentID={CFC20AF6-01CE-480a-9E71-EFC36B7CDB09}]
    Is the channel mode TIMESTAMP
    [/cover] */
    if((uint32)ICU_17_TIMERIP_MODE_TIMESTAMP ==
          LocalIcuChanPtr->IcuProperties.MeasurementMode)
    #endif
    {
      /* Extract the address to the Global Index Status value */
      GlbIndexStatusPtr =
        &((Icu_17_TimerIp_Varlist[CoreId]->GlbIndexStatusBasePtr)[CoreChIndex]);
      /* [cover parentID={E121A737-CA95-4906-9F9C-F6E27AEF251F}]
      Safety is enabled or Runtime error reporting is enabled or DET reporting is enabled in AS422
      [/cover] */
#if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON) || \
    (ICU_17_TIMERIP_RUNTIME_ERROR_DETECT == STD_ON) || \
    ((MCAL_AR_VERSION == MCAL_AR_422) && (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON))
      /* Check if the Time Stamp activity has been started for this channel */
      /* TO check for active channels */
      /* [cover parentID={6223CF06-4CF9-43ba-B922-3B5B9D766215}]
      Is the time stamping activity started?
      [/cover] */
      if((Mcal_GetBitAtomic(*GlbIndexStatusPtr, ICU_CHNL_ACTIVITY_STARTED_POS,
                         ICU_CHNL_ACTIVITY_BIT_LENGTH) != ICU_ACTIVITY_STARTED))
      {
        ErrorFlag = ICU_ERROR_FOUND;

        /* [cover parentID={D045F605-182B-4d77-8CA4-CBB08C797E38}]
        Report an error to indicate activity has not started.
        [/cover] */
        Icu_lReportRuntimeDetError(
          ICU_17_TIMERIP_SID_STOPTIMESTAMP,
          ICU_17_TIMERIP_E_NOT_STARTED); /* Report Error */
      }
      if (ICU_ERROR_FOUND != ErrorFlag)
#endif
      {
        /* Extract the actual HW cell number */
        CellUsed =(uint16)LocalIcuChanPtr->IcuProperties.AssignedHwUnitNumber;
        /* Depending on ICU option take action */
        IcuOption = (uint32)LocalIcuChanPtr->IcuProperties.AssignedHwUnit;
        switch(IcuOption)
        {
          /* [cover parentID={6ECF74BC-4459-4508-A950-05705BF44419}]
          IF ICU option is GTM
          [/cover] */
          case ICU_17_TIMERIP_GTM_OPTION:
          #if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
            /* [cover parentID={B35443AB-6509-4acd-AE55-DB54CC6386EF}]
            Call GTM stop time stamping.
            [/cover] */
            Icu_lGtmStopTimeStamp(CellUsed);
           #endif
            break;
          default:
          #if (ICU_17_TIMERIP_CCU6_USED == STD_ON)
            /* [cover parentID={EA92195C-5CCA-481f-85BC-4B19BF5AB6E3}]
            Call CCU stop time stamping.
            [/cover] */
            Icu_lCcuDisableChannel(CellUsed);
          #endif
            break;
        }
        /* [cover parentID={7DAB2E0B-EA41-44f3-81D2-94CA30D6551C}]
        Reset the channel activty status.
        [/cover] */
        /* Activity Start flag is set to zero */
        Mcal_SetBitAtomic( \
          GlbIndexStatusPtr, (sint32)ICU_CHNL_ACTIVITY_STARTED_POS,\
          ICU_CHNL_ACTIVITY_BIT_LENGTH, 0U);
      }
    }
  }
  /* [cover parentID={5D0F49AF-3538-4586-9878-04FB9654D8D1}]
    ICU Interrupt Control Registers.
  [/cover] */
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer GlbIndexStatusPtr is
   * accessed using assembly instruction. */
  /* MISRA2012_RULE_2_2_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the variable GlbIndexStatusPtr is
   * accessed using assembly instruction. */
}/* End of function Icu_17_TimerIp_StopTimestamp */
#endif

#if (ICU_17_TIMERIP_TIMESTAMP_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {D189DBAD-91B7-4450-82CA-535932895A36}]     **
**                                                                            **
** Syntax :Icu_17_TimerIp_IndexType Icu_17_TimerIp_GetTimestampIndex(         **
**                                  const Icu_17_TimerIp_ChannelType Channel) **
**                                                                            **
** Description : 1. This service will return the next index of the            **
**                  Buffer that will be written by the ISR.                   **
**               2. In case of a liner buffer and the buffer is filled the    **
**                  service will returns buffer size.                         **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x0B                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     Icu_17_TimerIp_IndexType : Index of next buffer          **
**                                              filling position.             **
**                                                                            **
*******************************************************************************/
/*[cover parentID={8F04E18D-D28A-48c4-AF5F-42751A7C4910}]
Safety Properties
[/cover]*/
Icu_17_TimerIp_IndexType Icu_17_TimerIp_GetTimestampIndex(
  const Icu_17_TimerIp_ChannelType Channel)
{
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr; /* ROM pointer */
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * MISRA rule,To implement efficiently IcuMeasaurementProperty as a post-build
   * parameter.Union is required*/
  const Icu_17_TimerIp_ChannelData *ChannelDataPtr;
  /* [cover parentID={E0A6D64C-1E31-4a04-B2D1-E4B5C1B2C347}]
  Set time stampindex to zero
  [/cover] */
  Icu_17_TimerIp_IndexType RetVal = (Icu_17_TimerIp_IndexType)0U;
  uint8 ChIndex;
  uint8 CoreChIndex;
  uint8 CoreId;

  /* Get core id which is executing currently */
  CoreId = (uint8)(Mcal_GetCpuIndex());
  /* [cover parentID={C1273793-B6D6-456c-A198-6D7EF0987FD9}]
  DET or Safety is enabled
  [/cover] */
  #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  uint32 ErrorFlag;
  /* [cover parentID={D6DEEDC4-CBDE-4a77-A17D-19A069879D89}]
  Preconditions check and channel validation
  [/cover] */
  /* Verify any error is there for DET */
  ErrorFlag = Icu_lNotifiDetCheck(Channel,
                                  ICU_17_TIMERIP_SID_GETTIMESTAMPINDEX,
                                  ICU_17_TIMERIP_MODE_TIMESTAMP,
                                  CoreId, ICU_FLAG_RESET);
  /* [cover parentID={3D1B1E15-1094-43a3-B82D-B798C58D2A97}]
  Any DET reported
  [/cover] */
  if(ICU_ERROR_FOUND != ErrorFlag)
  #endif
    /* (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) ||
     * (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON) */
  {
    CoreChIndex = Icu_lGetCoreChIndex((uint8)Channel);
    LocalIcuChanPtr = &((Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->
                                                ChannelConfigPtr)[CoreChIndex]);
    #if ((ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_OFF) && \
    (ICU_17_TIMERIP_SAFETY_ENABLE == STD_OFF))
    /* Check if the mode is valid */
    /* [cover parentID={FC053AC7-C434-4cae-9FA3-902457E8B0F7}]
    Is the channel in time stamp mode?
    [/cover] */
    if((uint32)ICU_17_TIMERIP_MODE_TIMESTAMP ==
          LocalIcuChanPtr->IcuProperties.MeasurementMode)
    #endif
    {
      ChIndex = LocalIcuChanPtr->ModeMappingIndex;
      /* Store the address in a pointer variable */
      ChannelDataPtr =
        &((Icu_17_TimerIp_Varlist[CoreId]->ChannelDataBasePtr)[ChIndex]);
      /* [cover parentID={411D08BE-03EB-4ce0-B888-5BA1092D4233}]
      Extract timestamp index
      [/cover] */
      RetVal = (ChannelDataPtr->TimeCaptureParas.Counter);
      /*  API under configuration ICU_17_TIMERIP_TIMESTAMP_API */
      /*  To return the next index to be written */
    }
  }
  /* [cover parentID={5D0F49AF-3538-4586-9878-04FB9654D8D1}]
    ICU Interrupt Control Registers.
  [/cover] */
  return(RetVal);
}/* End of function Icu_17_TimerIp_GetTimestampIndex */
#endif

/*******************************************************************************
** Traceability: [cover parentID= {D9732329-E95B-47ab-8A26-A1CEB39692F8}]     **
**                                                                            **
** Syntax : void Icu_17_TimerIp_EnableNotification(                           **
**                                const Icu_17_TimerIp_ChannelType Channel)   **
**                                                                            **
** Description : This service will enable the ICU signal notification,        **
**               activation edge depends on either DefaultStartEdge           **
*                Or activation by Icu_17_TimerIp_SetActivationCondition API.  **
**               This API affects both ICU_17_TIMERIP_MODE_SIGNAL_EDGE_DETECT **
**               and ICU_17_TIMERIP_MODE_TIMESTAMP Channels.                  **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x07                                                     **
*                                                                             **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={8F04E18D-D28A-48c4-AF5F-42751A7C4910}]
Safety Properties
[/cover]*/
void Icu_17_TimerIp_EnableNotification(
  const Icu_17_TimerIp_ChannelType Channel)
{
  /* [cover parentID={0CFC2DAB-6231-4dbe-8EA4-EC4CFCFB995F}]
  If edge detection, time stamping, edge counting or incremental interface api are available.
  [/cover] */
  #if (ICU_17_TIMERIP_NOTIF_NEEDED == STD_ON)
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr; /* ROM pointer */
  uint32* GlbIndexStatusPtr;
  uint8 CoreId;
  uint8 CoreChIndex;
  /* Get core id which is executing currently */
  CoreId = (uint8)(Mcal_GetCpuIndex());
  /* [cover parentID={8C6A8B43-DDA6-4e88-92DD-BDA97A7E7259}]
   DET or Safety is enabled
   [/cover] */
  #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  /* Verify any error is there for DET */
  uint32 ErrorFlag;
  /* [cover parentID={F19DDAE0-68AE-48ef-90F0-EEC4945A0AAC}]
  Preconditions check and channel validation
  [/cover] */
  ErrorFlag = Icu_lEnDisNotificationDetCheck(Channel,
              ICU_17_TIMERIP_SID_ENABLENOTIFICATION, CoreId);
  /* [cover parentID={BBFAABFC-4C89-4ea2-8B93-E46967D85166}]
  Any DET found
  [/cover] */
  if (ICU_ERROR_FOUND != ErrorFlag)
  #endif
    /* #if  (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) */
  {
    CoreChIndex = Icu_lGetCoreChIndex((uint8)Channel);
    /* Enable Notification for the corresponding channel if the pointer
     is not NULL */
    GlbIndexStatusPtr =
        &((Icu_17_TimerIp_Varlist[CoreId]->GlbIndexStatusBasePtr)[CoreChIndex]);
    /* Proceed only if notifications are disabled. Else skip execution and
     * return */
    /* No call should be executed if the function pointer is NULL */
    /* [cover parentID={744F43DD-E20F-40d1-8A76-00C034F950F3}]
    Is notification disabled?
    [/cover] */
    if (0U \
        == Mcal_GetBitAtomic(*GlbIndexStatusPtr, ICU_CHNL_NOTIF_PRESENCE_POS, \
                             ICU_CHNL_NOTIF_BIT_LENGTH))
    {
      /* Initialize ICU configured channel ROM pointer */
      LocalIcuChanPtr = &((Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->
                                                ChannelConfigPtr)[CoreChIndex]);
      /* Enable notification only if a valid notification function is
       * available.*/
      /* [cover parentID={CB8776EC-15EF-46a4-9C05-3057BD426321}]
       if ICU channel notification pointers are not null
       [/cover] */
      if ((LocalIcuChanPtr->NotificationPointer != NULL_PTR) ||
      (LocalIcuChanPtr->TimeOutNotificationPointer != NULL_PTR) ||
      (LocalIcuChanPtr->CntOvflNotificationPointer != NULL_PTR))
      {
        /* [cover parentID={B3BE0E89-7B63-45ca-87E9-567A1DF28485}]
        Is Edge Detection or edge counting enabled.
        [/cover] */
        #if (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON) || (ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON)
        /* Enable interrupts for edge detection mode */
        /* [cover parentID={386F0EB3-5831-4ec8-913D-878BA8CC7CB3}]
        Is channel mode is EDGE DETECT or EDGE COUNT
        [/cover] */
        if ((LocalIcuChanPtr->IcuProperties.MeasurementMode \
            == (uint32) ICU_17_TIMERIP_MODE_SIGNAL_EDGE_DETECT) ||
            (LocalIcuChanPtr->IcuProperties.MeasurementMode \
            == (uint32) ICU_17_TIMERIP_MODE_EDGE_COUNTER))
        {
          uint16 HwUnit;
          uint32 IcuOption;
          /* Initialize ICU configured channel ROM pointer */
          HwUnit =
            (uint16) (LocalIcuChanPtr->IcuProperties.AssignedHwUnitNumber);
          /* Depending on ICU option take action */
          IcuOption = (uint32) LocalIcuChanPtr->IcuProperties.AssignedHwUnit;
          /* [cover parentID={6A3695E8-F400-4b10-8FD0-7A809C167598}]
          If GPT12 is used and edge detect is enabled
          [/cover] */
          #if(ICU_17_TIMERIP_GPT12_USED == STD_ON) && (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
          /* for triggering notifications, interrupt is required on all edges */
          /* [cover parentID={D98A13C2-9858-40f8-ABAB-692C7B2CF9AB}]
          Is ICU option GPT12?
          [/cover] */
          if (IcuOption == ICU_17_TIMERIP_GPT12_OPTION)
          {
              uint32* MultiEdgeCountPtr;
            /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
             * MISRA rule,To implement efficiently IcuMeasaurementProperty as a post-build
             * parameter.Union is required*/
            Icu_17_TimerIp_ChannelData *ChnlDataPtr;
            uint8 ChIndex;
            /* Retrieve Mode specific channel index */
            ChIndex = LocalIcuChanPtr->ModeMappingIndex;
            /* Retrieve the multi edge Count value address */
            ChnlDataPtr =
              &((Icu_17_TimerIp_Varlist[CoreId]->ChannelDataBasePtr)[ChIndex]);
            MultiEdgeCountPtr = &(ChnlDataPtr->EdgeDetectParas.EdgeDetectCount);
            /* Update reload counter only if multiedge detection is disabled*/
            /* [cover parentID={F9D2F417-2A4A-4d7a-966A-5DC750FF852F}]
            Is the multi edge detection enabled?
            [/cover] */
            if (0U == Mcal_GetBitAtomic(*GlbIndexStatusPtr, \
                                        ICU_CHNL_MULTIEDGE_STAT_POS,
                                        ICU_CHNL_MULTIEDGE_STAT_BIT_LENGTH))
            {
              /* [cover parentID={814E828D-CF4E-497a-91FE-7E91E3F6FD94}]
              Set the multiedge counter to 1, to indicate that interrupt is
              needed on every edge.
              [/cover] */
              *MultiEdgeCountPtr = 1;
            }
          }
          #endif
          /* [cover parentID={E734F0AD-9C19-4edf-94A6-2B311F33BB7C}]
          Enable interrupt notification
          [/cover] */
          Icu_lEnableNotificationInterrupts(IcuOption, HwUnit,
                                            GlbIndexStatusPtr);
        }
        #endif
        /* [cover parentID={ECFE9E6D-9EC2-46ac-9198-250B0EC73C8E}]
         Enable Notification of the channel
         [/cover] */
        Mcal_SetBitAtomic(GlbIndexStatusPtr, ICU_CHNL_NOTIF_PRESENCE_POS,
                          ICU_CHNL_NOTIF_BIT_LENGTH, (uint32 )1U);
      }
      #if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
      else
      {
        /* [cover parentID={2F8CBA4D-DF16-4c27-8367-F991D24F786A}]
        Report Safety Error: Invalid Notif
        [/cover] */
        Mcal_ReportSafetyError(
          ICU_17_TIMERIP_MODULE_ID,
          ICU_17_TIMERIP_INSTANCE_ID,
          ICU_17_TIMERIP_SID_ENABLENOTIFICATION,
          ICU_17_TIMERIP_E_INVALID_NOTIF);/* End of report to Safety */
      }
      #endif
    }
  }
  /* [cover parentID={1B49DAB0-4A90-4beb-9410-C71B9B8CF6B4}]
  If both time stamping and edge detection api are not available.
  and Safet or DET reporting enabled
  [/cover] */
  #else
  /* [cover parentID={1B49DAB0-4A90-4beb-9410-C71B9B8CF6B4}]
  If both time stamping and edge detection api are not available
  [/cover] */
  UNUSED_PARAMETER(Channel);
  #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  /* Report Error */
  /* [cover parentID={50B8A488-A529-43c0-B786-D2ED529D66A3}]
  Report error indicating invalid channel
  [/cover] */
  Icu_lReportError(
    ICU_17_TIMERIP_SID_ENABLENOTIFICATION,
    ICU_17_TIMERIP_E_PARAM_CHANNEL);/* End of report to Safety */
  #endif
  #endif
  /* [cover parentID={5D0F49AF-3538-4586-9878-04FB9654D8D1}]
   ICU Interrupt Control Registers.
   [/cover] */
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer GlbIndexStatusPtr is
   * accessed using assembly instruction. */
}/* End of Icu_17_TimerIp_EnableNotification() function */

/*******************************************************************************
** Traceability: [cover parentID= {E737F468-9DE9-48d7-917F-5FCE5556CEB1}]     **
**                                                                            **
** Syntax : void Icu_17_TimerIp_DisableNotification(                          **
**                         const Icu_17_TimerIp_ChannelType Channel)          **
**                                                                            **
** Description : This service will disable  ICU signal notifications of       **
**               this channel.                                                **
**               This API affects both ICU_17_TIMERIP_MODE_SIGNAL_EDGE_DETECT **
**               and ICU_17_TIMERIP_MODE_TIMESTAMP Channels.                  **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x06                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={8F04E18D-D28A-48c4-AF5F-42751A7C4910}]
Safety Properties
[/cover]*/
void Icu_17_TimerIp_DisableNotification(
  const Icu_17_TimerIp_ChannelType Channel)
{
  /* [cover parentID={8D65CE82-342C-4de2-BA9C-3555155CA1DE}]
  If edge detection, time stamping, edge counting or incremental interface api are available.
  [/cover] */
  #if (ICU_17_TIMERIP_NOTIF_NEEDED == STD_ON)
  uint32* GlbIndexStatusPtr;
  uint8 CoreChIndex;
  uint8 CoreId;
  /* Get core id which is executing currently */
  CoreId = (uint8)(Mcal_GetCpuIndex());
  /* [cover parentID={C818B004-BC3C-4f12-93D5-76685B5BFA61}]
  DET or Safety is enabled
  [/cover] */
  #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  /* Verify any error is there for DET */
  uint32 ErrorFlag;
  /* [cover parentID={DDA3B320-EC03-4da4-917E-C690C643EF86}]
  Preconditions check and channel validation
  [/cover] */
  ErrorFlag = Icu_lEnDisNotificationDetCheck(
                Channel,
                ICU_17_TIMERIP_SID_DISABLENOTIFICATION, CoreId);
  /* [cover parentID={C3A91053-300B-4c76-8D6D-A75B3BB1C923}]
  Any DET found
  [/cover] */
  if (ICU_ERROR_FOUND != ErrorFlag)
  #endif
    /* #if  (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) ||
     * (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)*/
  {
    CoreChIndex = Icu_lGetCoreChIndex((uint8)Channel);
    GlbIndexStatusPtr =
        &((Icu_17_TimerIp_Varlist[CoreId]->GlbIndexStatusBasePtr)[CoreChIndex]);
    /* Proceed only if notifications are disabled. Else skip execution and
     * return */
    /* [cover parentID={826017F2-891A-486f-83A2-A8B7DAC53BAE}]
    Is notification enabled?
    [/cover] */
    if(1U == Mcal_GetBitAtomic(*GlbIndexStatusPtr,
        ICU_CHNL_NOTIF_PRESENCE_POS, ICU_CHNL_NOTIF_BIT_LENGTH))
    {
      #if (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON) || (ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON)
      const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr;
      uint16 HwUnit;
      uint32 IcuOption;
      LocalIcuChanPtr = &((Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->
                                                ChannelConfigPtr)[CoreChIndex]);
      /* [cover parentID={5396779A-4ECB-47e4-931A-A88579B2A342}]
      Is channel mode is EDGE DETECT or EDGE COUNT
      [/cover] */
      if ((LocalIcuChanPtr->IcuProperties.MeasurementMode
          == (uint32)ICU_17_TIMERIP_MODE_SIGNAL_EDGE_DETECT)||
            (LocalIcuChanPtr->IcuProperties.MeasurementMode \
            == (uint32) ICU_17_TIMERIP_MODE_EDGE_COUNTER))
      {
        /* Initialize ICU configured channel ROM pointer */
        HwUnit = (uint16)(LocalIcuChanPtr->IcuProperties.AssignedHwUnitNumber);
        /* Depending on ICU option take action */
        IcuOption = (uint32)LocalIcuChanPtr->IcuProperties.AssignedHwUnit;
        #if(ICU_17_TIMERIP_GPT12_USED == STD_ON) && (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
        /* for triggering notifications, interrupt is required on all edges */
        /* [cover parentID={EE54E690-B9DC-4c27-B936-EFE8F451F7B4}]
        Is ICU option GPT12?
        [/cover] */
        if (IcuOption == ICU_17_TIMERIP_GPT12_OPTION)
        {
          /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
           * MISRA rule,To implement efficiently IcuMeasaurementProperty as a post-build
           * parameter.Union is required*/
          Icu_17_TimerIp_ChannelData *ChnlDataPtr;
          uint32* MultiEdgeCountPtr;
          uint8 ChIndex;
          /* Retrieve Mode specific channel index */
          ChIndex = LocalIcuChanPtr->ModeMappingIndex;
          /* Retrieve the multi edge Count value address */
          ChnlDataPtr =
               &((Icu_17_TimerIp_Varlist[CoreId]->ChannelDataBasePtr)[ChIndex]);
          MultiEdgeCountPtr = &(ChnlDataPtr->EdgeDetectParas.EdgeDetectCount);
          /* Update the reload counter only if multiedge detection is disabled*/
          /* [cover parentID={B9B434DD-F8F8-48ed-B1FE-48684F1DA890}]
          Is the multi edge detection enabled?
          [/cover] */
          if(0U == Mcal_GetBitAtomic(*GlbIndexStatusPtr,
              ICU_CHNL_MULTIEDGE_STAT_POS, ICU_CHNL_MULTIEDGE_STAT_BIT_LENGTH))
          {
            /* [cover parentID={DEF6D3CF-7647-4b64-BAC6-87CB619C0268}]
            Set the multiedge counter to 0 to avoid interrupt on every edge
            [/cover] */
            *MultiEdgeCountPtr = 0;
            /* [cover parentID={F59A998C-564B-4acc-9C76-9CB13B6A52CD}]
            Disable interrupt notification
            [/cover] */
            Icu_lDisableNotificationInterrupts(IcuOption, HwUnit);
          }
        }
        else
        #endif
        {
          /* [cover parentID={A89B6641-47ED-407f-AE97-55CFB44EB132}]
          Disable interrupt notification
          [/cover] */
          Icu_lDisableNotificationInterrupts(IcuOption, HwUnit);
        }
      }/* EDGE_DETECT_MODE or edge count*/
      #endif
      /* [cover parentID={DDB95F2C-F45B-471c-934E-368A72B9F2C9}]
      Disable Notification of the channel
      [/cover] */
      Mcal_SetBitAtomic(GlbIndexStatusPtr, \
          ICU_CHNL_NOTIF_PRESENCE_POS,ICU_CHNL_NOTIF_BIT_LENGTH, \
          (uint32)0U);
    }/* NOTIFICATION check */
  }/*(ICU_ERROR_FOUND != ErrorFlag) */
  #else
  /* [cover parentID={FEA641FD-E78F-453b-9B0E-6A65A66B449D}]
  If both time stamping and edge detection api are not available and safety
  or DET error reporting is enabled
  [/cover] */
  UNUSED_PARAMETER(Channel);
  #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  /* report Error */
  /* [cover parentID={3987A4B7-4D77-4e97-8D19-94868D184616}]
  Report error indicating invalid channel
  [/cover] */
  Icu_lReportError(
    ICU_17_TIMERIP_SID_ENABLENOTIFICATION,
    ICU_17_TIMERIP_E_PARAM_CHANNEL);/* End of report to Safety */
  #endif
  #endif
  /* [cover parentID={5D0F49AF-3538-4586-9878-04FB9654D8D1}]
    ICU Interrupt Control Registers.
  [/cover] */
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer GlbIndexStatusPtr is
   * accessed using assembly instruction. */
}/* End of function Icu_17_TimerIp_DisableNotification */

/* precompile switch ICU_17_TIMERIP_EDGE_DETECT_API */
#if (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
/*This API is applicable to Autosar Version 3.2.1 also, based on Bugzila 29022*/
/*******************************************************************************
** Traceability: [cover parentID= {3D2225C3-0B2B-46d2-B2BF-6FC1EBE67F35}]     **
**                                                                            **
** Syntax : void Icu_17_TimerIp_EnableEdgeDetection(                          **
**                                const Icu_17_TimerIp_ChannelType Channel)   **
**                                                                            **
** Description : This service will Re enables the ICU signal edge detection   **
**               channel, activation edge depends on either DefaultStartEdge  **
**               Or activation by Icu_17_TimerIp_SetActivationCondition API.  **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x16                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={8F04E18D-D28A-48c4-AF5F-42751A7C4910}]
Safety Properties
[/cover]*/
void Icu_17_TimerIp_EnableEdgeDetection(
  const Icu_17_TimerIp_ChannelType Channel)
{
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr; /* ROM pointer */
  uint32* GlbIndexStatusPtr;
  #if(ICU_17_TIMERIP_GPT12_USED == STD_ON)
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * MISRA rule,To implement efficiently IcuMeasaurementProperty as a post-build
   * parameter.Union is required*/
  Icu_17_TimerIp_ChannelData *ChnlDataPtr;
  uint32* MultiEdgeCountPtr;
  uint8 ChIndex;
  #endif
  uint16 CellUsed;
  uint8 CoreChIndex;
  #if (ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON)
  uint8 EruLineUsed;
  uint8 L_Edge;
  #endif
  #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  uint32 ErrorFlag;
  #endif
  uint32 IcuOption;
  uint8 CoreId;

  /* Get core id which is executing currently */
  CoreId = (uint8)(Mcal_GetCpuIndex());
  /* [cover parentID={30B57E12-A341-468f-87E9-0F4FA00D293E}]
  DET or Safety is enabled
  [/cover] */
  #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  /* Verify any error is there for DET */
  /* [cover parentID={69ADE16E-13F0-4466-83A8-BF0B2C3E6E6F}]
  Preconditions check, sleep mode check and channel validation
  [/cover] */
  ErrorFlag = Icu_lNotifiDetCheck(Channel,
                                  ICU_17_TIMERIP_SID_ENABLEEDGEDETECTION,
                                  ICU_17_TIMERIP_MODE_SIGNAL_EDGE_DETECT,
                                  CoreId, ICU_FLAG_SET);
  /* [cover parentID={356C6AF5-489D-4c29-B7BC-07B030CD418B}]
  Any DET reported
  [/cover] */
  if (ICU_ERROR_FOUND != ErrorFlag)
  #endif
    /* (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) ||
    (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON) */
  {
    /* Extract the Core Specific channel index */
    CoreChIndex = Icu_lGetCoreChIndex((uint8)Channel);
    /* Initialize ICU configured channel ROM pointer */
    LocalIcuChanPtr = &((Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->
                                                ChannelConfigPtr)[CoreChIndex]);
    #if ((ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_OFF) && \
    (ICU_17_TIMERIP_SAFETY_ENABLE == STD_OFF))
    /* Check if the mode is valid */
    /* [cover parentID={68E142ED-74D7-4ff9-8484-0D9E05517AD2}]
    Is the channel in Edge Detection mode.
    [/cover] */
    if (LocalIcuChanPtr->IcuProperties.MeasurementMode
        == (uint32)ICU_17_TIMERIP_MODE_SIGNAL_EDGE_DETECT)
    #endif
    {
      /* Extract the address to the channel status */
      GlbIndexStatusPtr =
        &((Icu_17_TimerIp_Varlist[CoreId]->GlbIndexStatusBasePtr)[CoreChIndex]);
      /* Extract the HW cell assigned */
      CellUsed =
        (uint8)LocalIcuChanPtr->IcuProperties. AssignedHwUnitNumber;
      /* Depending on ICU option take action */
      IcuOption = (uint32)LocalIcuChanPtr->IcuProperties.AssignedHwUnit;
      /* [cover parentID={F37C0830-BD03-43f5-A1ED-8047935C6808}]
      Enable Edge Detection depending on HW
      [/cover] */
      switch(IcuOption)
      {
        /* [cover parentID={B0B849F8-3FB3-4b42-8556-430A5CAAEB7D}]
        Is HW used GTM TIM?
        [/cover] */
        case ICU_17_TIMERIP_GTM_OPTION:
          /*Start Signal Edge detect for TIM*/
          #if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) && \
          (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
          /* [cover parentID={E64BDCEA-39B0-410f-8FEF-BBCCA1E538CD}]
          Start Edge Detect
          [/cover] */
          Icu_lGtmStartEdgeDetect(CellUsed);
          #endif
          break;
        /* [cover parentID={3D0D3260-B3C8-40a4-B80B-1F3C44B0E570}]
        Is HW used CCU6?
        [/cover] */
        case ICU_17_TIMERIP_CCU_OPTION:
          /*Start Signal Edge detect for CCU6*/
          #if(ICU_17_TIMERIP_CCU6_USED == STD_ON)
          /* [cover parentID={E5E27F33-F128-40cf-8DD7-AEEF88FFB3FD}]
          Enable CCU channel
          [/cover] */
          Icu_lCcuEnableChannel(CellUsed);
          #endif
          break;
        /* [cover parentID={6DF87CFB-FAC9-40c2-ADA7-CA79D7D2B6D7}]
        Is HW used ERU?
        [/cover] */
        case ICU_17_TIMERIP_ERU_OPTION:
          /* Configure the Hardware resource as per the configured edges */
          /* [cover parentID={C66B2342-066A-4073-B904-287F722FCBE0}]
          Clear any pending flags for the ERU hardware and set the flag to
          indicate sigedge has started on ERU.
          [/cover] */
          #if(ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON)
          L_Edge = (uint8)Mcal_GetBitAtomic(*GlbIndexStatusPtr,
              ICU_CHNL_EDGE_POS,ICU_CHNL_EDGE_BIT_LENGTH);
          EruLineUsed = (((uint8)CellUsed ) & ICU_ERU_CHNL_MASK);
          /* Clear Service Request if any was in pending */
          MODULE_SCU.FMR.U = (((uint32)1UL) << (EruLineUsed + ICU_ERU_FCSTART));
          /* Enable the cell for notification */
          /* [cover parentID={8DA4597D-60AF-4166-BD4B-39792C7932B1}]
          Enable ERU channel to detect the edge configured
          [/cover] */
          Icu_lSetEruEdge( L_Edge, EruLineUsed );
          /* [cover parentID={D4C7A07D-7568-4d3e-AFEE-8616EDA57F28}]
          Set the ERU edge detection flag.
          [/cover] */
          Mcal_SetBitAtomic( \
            GlbIndexStatusPtr, (sint32)ICU_CHNL_ERU_GPT_SIGEDGE_STATUS_POS,\
            ICU_CHNL_ERU_GPT_SIGEDGE_STATUS_BIT_LENGTH, (uint32)1);
          #endif
          break;
        /* [cover parentID={5ACDA78B-BDAC-4543-A7EC-07281B6E3905}]
        Is HW used GPT12?
        [/cover] */
        default: /* ICU_17_TIMERIP_GPT12_OPTION */
          /* [cover parentID={FDB5025C-0445-4876-99ED-4FA8DBBC17EB}]
          Start edge detection on GPT12.
          [/cover] */
          /* Retrieve Mode specific channel index */
          #if (ICU_17_TIMERIP_GPT12_USED == STD_ON) && \
          (ICU_17_TIMERIP_EDGE_DETECT_API ==STD_ON)
          ChIndex = LocalIcuChanPtr->ModeMappingIndex;
          /* Retrieve the multi edge Count value address */
          ChnlDataPtr =
               &((Icu_17_TimerIp_Varlist[CoreId]->ChannelDataBasePtr)[ChIndex]);
          MultiEdgeCountPtr = &(ChnlDataPtr->EdgeDetectParas.EdgeDetectCount);
          /* Check if the notifications are enabled. */
          /* [cover parentID={46A04845-A2E8-47e0-BADB-0B78E20BDDF8}]
          Is notification enabled?
          [/cover] */
          if(1U == Mcal_GetBitAtomic(*GlbIndexStatusPtr,
              ICU_CHNL_NOTIF_PRESENCE_POS, ICU_CHNL_NOTIF_BIT_LENGTH))
          {
            /* If notifications are enabled, interrupt is required on every
             * edge*/
            /* [cover parentID={1DA8CE3F-992D-4812-8257-1CFFF3DC4D86}]
            Set the multi edge count value to 1
            [/cover] */
            *MultiEdgeCountPtr = 1U;
          }
          else
          {
            /* If notifications are disabled, interrupt should occur only after
             * counter roll over.*/
            /* Set the multi edge count value address to 0*/
            /* [cover parentID={D3CD0BB9-AA3E-476d-99AC-3FBCBDDCB7B5}]
            Set the multi edge count value to 0
            [/cover] */
            *MultiEdgeCountPtr = 0U;
          }
          /* Call GPT12 Start Edge Detect*/
          /* [cover parentID={B17C2EDB-BEEB-4e2d-8E51-587D23FB764B}]
          Start GPT12 timer counter with the multi edge counte
          [/cover] */
          Icu_lGpt12StartEdgeDetect(CellUsed, (uint16)*MultiEdgeCountPtr);
          /* [cover parentID={2819AEE3-6F59-450e-B6DF-F8EED1EAB59E}]
          Clear the multi edge detection flag of channel
          [/cover] */
          /* Set the Multi Edge Detection status to false. */
          Mcal_SetBitAtomic( \
            GlbIndexStatusPtr, (sint32)ICU_CHNL_MULTIEDGE_STAT_POS,\
            ICU_CHNL_MULTIEDGE_STAT_BIT_LENGTH, (uint32)0);
          /* Set the GPT Edge Detection status to true. */
          /* [cover parentID={BC5309C7-21BE-4e65-A08C-84FA8AB8BCC5}]
          Set the GPT12 edge detection flag.
          [/cover] */
          Mcal_SetBitAtomic( \
            GlbIndexStatusPtr, (sint32)ICU_CHNL_ERU_GPT_SIGEDGE_STATUS_POS,\
            ICU_CHNL_ERU_GPT_SIGEDGE_STATUS_BIT_LENGTH, (uint32)1);
          #endif
          break;
      }
      /* [cover parentID={7ACF0387-C4D6-47ac-9AEA-05ADE90266E2}]
      Set the channel active status to IDLE
      [/cover] */
      /* Set channel state to IDLE */
      Mcal_SetBitAtomic(GlbIndexStatusPtr, \
                        ICU_CHNL_STATUS_POS, ICU_CHNL_STATUS_BIT_LENGTH, \
                        (uint32)ICU_17_TIMERIP_IDLE);
    }
  }
  /* [cover parentID={5D0F49AF-3538-4586-9878-04FB9654D8D1}]
    ICU Interrupt Control Registers.
  [/cover] */
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer GlbIndexStatusPtr is
   * accessed using assembly instruction. */
  /* MISRA2012_RULE_2_2_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the variable GlbIndexStatusPtr is
   * accessed using assembly instruction. */
}/* End of Icu_17_TimerIp_EnableEdgeDetection() function */
#endif

#if (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
/*This API is applicable to Autosar Version 3.2.1 also, based on Bugzila 29022*/
/*******************************************************************************
** Traceability: [cover parentID= {37B8879F-4CA2-497d-B361-ECD29A9ACB9E}]     **
**                                                                            **
** Syntax : void Icu_17_TimerIp_DisableEdgeDetection(                         **
**                                const Icu_17_TimerIp_ChannelType Channel)   **
**                                                                            **
** Description : This service will disable the ICU signal edge detection      **
**                channel.                                                    **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x17                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={8F04E18D-D28A-48c4-AF5F-42751A7C4910}]
Safety Properties
[/cover]*/
void Icu_17_TimerIp_DisableEdgeDetection(
  const Icu_17_TimerIp_ChannelType Channel)
{
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr; /* ROM pointer */
  #if (ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON) || \
  (ICU_17_TIMERIP_GPT12_USED == STD_ON)
  uint32* GlbIndexStatusPtr;
  #endif
  uint16 CellUsed;
  uint32 IcuOption;
  uint8 CoreChIndex;
  #if (ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON)
  uint8 EruEicrChannel;
  #endif
  uint8 CoreId;
  /* Get core id which is executing currently */
  CoreId = (uint8)(Mcal_GetCpuIndex());
  /* [cover parentID={3CF0B614-B978-434f-8346-B37B7A05DD93}]
  DET or Safety is enabled
  [/cover] */
  #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON)|| \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  /* Verify any error is there for DET */
  uint32 ErrorFlag;
  /* [cover parentID={E85743D9-B42D-415f-96E5-F64D72F5A650}]
  Preconditions check, sleep mode check and channel validation
  [/cover] */
  /* Verify any error is there for DET */
  ErrorFlag = Icu_lNotifiDetCheck(Channel,
                                  ICU_17_TIMERIP_SID_DISABLEEDGEDETECTION,
                                  ICU_17_TIMERIP_MODE_SIGNAL_EDGE_DETECT,
                                  CoreId, ICU_FLAG_SET);
  /* [cover parentID={D3B8C7E8-4400-44ae-8794-77216E0F4FBD}]
  Any DET found
  [/cover] */
  if (ICU_ERROR_FOUND != ErrorFlag)
  #endif
  {
    CoreChIndex = Icu_lGetCoreChIndex((uint8)Channel);
    /* Initialize ICU configured channel ROM pointer */
    LocalIcuChanPtr = &((Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->
                                                ChannelConfigPtr)[CoreChIndex]);
    #if ((ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_OFF) && \
    (ICU_17_TIMERIP_SAFETY_ENABLE == STD_OFF))
    /* Check if the mode is valid */
    /* [cover parentID={2902A7D6-4BBD-4bea-958A-55BA82631C40}]
    Is the channel is in edge detection mode?
    [/cover] */
    if (LocalIcuChanPtr->IcuProperties.MeasurementMode
        == (uint32)ICU_17_TIMERIP_MODE_SIGNAL_EDGE_DETECT)
    #endif
    {
      /* Extract the HW unit assigned to the channel */
      CellUsed = (uint16)LocalIcuChanPtr->IcuProperties.
                 AssignedHwUnitNumber;
      /* Depending on ICU option take action */
      IcuOption = (uint32)LocalIcuChanPtr->IcuProperties.AssignedHwUnit;
      switch(IcuOption)
      {
        /* [cover parentID={6E4522BC-D740-4431-B02E-6E973BA8FDA4}]
        Is HW used GTM-TIM?
        [/cover] */
        case ICU_17_TIMERIP_GTM_OPTION:
          /* [cover parentID={E0F861F1-3369-45b3-A41F-96B9B7F64A68}]
          Stop edge detection
          [/cover] */
          #if(ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
          Icu_lGtmDisableChnIrq(CellUsed);
          #endif
          break;
        /* [cover parentID={29E48AFF-97BA-42d2-A79D-FC5819D17733}]
        Is HW used CCU?
        [/cover] */
        case ICU_17_TIMERIP_CCU_OPTION:
          /* [cover parentID={9E892294-8DCD-4008-8A64-9AF91D29DF20}]
          Disable CCU channel
          [/cover] */
          #if(ICU_17_TIMERIP_CCU6_USED == STD_ON)
          Icu_lCcuDisableChannel(CellUsed);
          #endif
          break;
        /* [cover parentID={469DC448-B178-40bd-AD78-5039B27F9359}]
        Is HW used ERU?
        [/cover] */
        case ICU_17_TIMERIP_ERU_OPTION:
          /*Disable ERU Channel*/
          #if(ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON)
          GlbIndexStatusPtr = &((Icu_17_TimerIp_Varlist[CoreId]->
                                           GlbIndexStatusBasePtr)[CoreChIndex]);
          EruEicrChannel = ((uint8)CellUsed & ICU_ERU_CHNL_MASK);
          /* [cover parentID={B85CAC1A-7D16-4d71-B2C9-2DDDBC98A669}]
          Disable the cell
          [/cover] */
          Icu_lSetEruEdge( (uint8)ICU_17_TIMERIP_NO_EDGE, EruEicrChannel );
          /* [cover parentID={DC5CAD7F-542E-4458-A53A-9D8B3A38D430}]
          Reset ERU edge detection flag.
          [/cover] */
          Mcal_SetBitAtomic( \
            GlbIndexStatusPtr, (sint32)ICU_CHNL_ERU_GPT_SIGEDGE_STATUS_POS,\
            ICU_CHNL_ERU_GPT_SIGEDGE_STATUS_BIT_LENGTH, (uint32)0);
          #endif
          break;
        /* [cover parentID={C21B97EA-DCD4-4341-8D20-72F4C9E15267}]
        Is HW used GPT12?
        [/cover] */
        default:
          /*Disable Gpt12 Channel*/
          #if(ICU_17_TIMERIP_GPT12_USED == STD_ON)
          /* [cover parentID={E3C3C259-042A-4752-9641-E784C9FDFA85}]
          Disable GPT12 channel
          [/cover] */
          Icu_lGpt12DisableChannel(CellUsed);
          GlbIndexStatusPtr = &((Icu_17_TimerIp_Varlist[CoreId]->
                                           GlbIndexStatusBasePtr)[CoreChIndex]);
          /* [cover parentID={F7782D48-2A7B-4568-8CA7-0E93EC42FCB1}]
          Reset the GPT edge detection flag.
          [/cover] */
          Mcal_SetBitAtomic(\
            GlbIndexStatusPtr, (sint32)ICU_CHNL_ERU_GPT_SIGEDGE_STATUS_POS,\
            ICU_CHNL_ERU_GPT_SIGEDGE_STATUS_BIT_LENGTH, (uint32)0);
          #endif
          break;
      }
    }/* End of if condition */
  }
  /* [cover parentID={5D0F49AF-3538-4586-9878-04FB9654D8D1}]
    ICU Interrupt Control Registers.
  [/cover] */
  /* MISRA2012_RULE_2_2_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the variable GlbIndexStatusPtr is
   * accessed using assembly instruction. */
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer GlbIndexStatusPtr is
   * accessed using assembly instruction. */
}/* End of Icu_17_TimerIp_DisableEdgeDetection() function */
#endif

/* Configuration of Icu_17_TimerIp_EnableWakeup API */
#if  (ICU_17_TIMERIP_ENABLE_WAKEUP_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {2154CCCA-1835-4a88-B6C6-F44496227DCE}]     **
**                                                                            **
** Syntax :          void Icu_17_TimerIp_EnableWakeup(                        **
**                           const Icu_17_TimerIp_ChannelType Channel)        **
**                                                                            **
** Description : 1 This service will re-enable /enable the wake-up capability **
**                 of ICU channel.                                            **
**               2.This service is only feasible for ICU channels configured  **
**                 as wake-up capable true. The signal measurement mode       **
**                 should be ICU_17_TIMERIP_MODE_SIGNAL_EDGE_DETECT.          **
**               3.From the call of Icu_17_TimerIp_Init() the channel which   **
**                 was configured as wakeup capable and the same capability   **
**                 was disabled by using service                              **
**                 Icu_17_TimerIp_DisableWakeup().                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x04                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  Channel : Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={8F04E18D-D28A-48c4-AF5F-42751A7C4910}]
Safety Properties
[/cover]*/
void Icu_17_TimerIp_EnableWakeup(const Icu_17_TimerIp_ChannelType Channel)
{
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr;
  uint32* GlbIndexStatusPtr;
  uint8 CoreChIndex;
  uint8 CoreId;
  /* Get core id which is executing currently */
  CoreId = (uint8)(Mcal_GetCpuIndex());
  /* STATIC CHECK: if DET or Safety error reporting is enabled */
  /* [cover parentID={B778630D-2342-4a31-9211-9FE79C4EA539}]
  DET or Safety is enabled
  [/cover] */
  #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  uint32 ErrorFlag;
  /* [cover parentID={FC6A605C-BA90-4f42-957C-05B546580717}]
  Preconditions check, sleep mode check and channel validation
  [/cover] */
  /* Check for valid channel, mode and core. Raise a DET/Safety Error as
   * applicable */
  ErrorFlag = Icu_lNotifiDetCheck(Channel, ICU_17_TIMERIP_SID_ENABLEWAKEUP,
                  ICU_17_TIMERIP_MODE_SIGNAL_EDGE_DETECT, CoreId, ICU_FLAG_SET);
  /* [cover parentID={D064BA7A-B744-43c7-82EF-1770ADBF5BEB}]
  Any DET found
  [/cover] */
  /* Check if there are any previous errors */
  if (ICU_ERROR_FOUND != ErrorFlag)
  #endif
    /* #if  (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) ||
     * (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON) */
  {
    /* Extract the Core Specific channel index */
    CoreChIndex = Icu_lGetCoreChIndex((uint8)Channel);
    /* Initialize ICU configured channel ROM pointer */
    LocalIcuChanPtr = &((Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->
                                                ChannelConfigPtr)[CoreChIndex]);
    /* [cover parentID={37ADD89D-16C1-48fc-9129-2D146A1AD7CE}]
    Det or safety is enabled
    [/cover] */
#if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
    /* [cover parentID={B3482D32-85BE-408d-9055-D04FC2BD4FED}]
    Is timeout feature exclusive?
    [/cover] */
    if((uint32)ICU_SET_BIT == LocalIcuChanPtr->IcuProperties.IsTimeOutExclusive)
    {
      ErrorFlag = (uint32) ICU_ERROR_FOUND;
      /* [cover parentID={84AA21F8-8BFD-42f0-8C49-4227E57CA243}]
      Report invalid channel
      [/cover] */
      Icu_lReportError(
        ICU_17_TIMERIP_SID_ENABLEWAKEUP,
        ICU_17_TIMERIP_E_PARAM_CHANNEL);
    }
    if (ICU_ERROR_FOUND != ErrorFlag)
    {
#endif
    /* Check configured wakeup capability */
    /* [cover parentID={B2E5A85E-3909-4c60-940A-1C4CC967503C}]
    Is channel configured wakeup capable
    [/cover] */
    if (LocalIcuChanPtr->IcuProperties.WakeupCapability == 1U)
    {
      /* Extract the address to the channel status flags */
      GlbIndexStatusPtr =
        &((Icu_17_TimerIp_Varlist[CoreId]->GlbIndexStatusBasePtr)[CoreChIndex]);
      /* check if the channel is already wakeup capable */
      /* [cover parentID={DABD469F-47B9-4513-B890-75C27DD03B69}]
      If the channel is already wakeup capable
      [/cover] */
      if(0U == Mcal_GetBitAtomic(*GlbIndexStatusPtr,
          ICU_CHNL_WAKEUP_CAPABLE_POS, ICU_CHNL_WAKEUP_BIT_LENGTH))
      {
        /* [cover parentID={0EDCB388-C5A2-4755-86C9-9EEF9A3F1DA9}]
        Set the Wakeup flag for the channel in the channel flags variable.
        [/cover] */
        /* Set the Wakeup flag for the channel */
        /* [cover parentID={0EDCB388-C5A2-4755-86C9-9EEF9A3F1DA9}]
        Set the Wakeup flag for the channel in the channel flags variable.
        [/cover] */
        Mcal_SetBitAtomic((GlbIndexStatusPtr), \
            ICU_CHNL_WAKEUP_CAPABLE_POS,ICU_CHNL_WAKEUP_BIT_LENGTH, \
            (uint32)1U);
      }
    }
    /* STATIC CHECK: if DET or Safety error reporting is enabled */
    /* [cover parentID={FAC35A5C-5654-4897-AFF4-4C57345993EA}]
    DET or Safety is enabled
    [/cover] */
    #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
    (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
    else
    {
      /* Report a DET/Safety Error if a channel is not configured wakeup
       * capable */
      /* [cover parentID={6F3DAFFC-DE94-40b0-ABBE-149EFB7C0831}]
      Report a DET/Safety Error to indicate a wrong input channel.
      [/cover] */
      Icu_lReportError(
        ICU_17_TIMERIP_SID_ENABLEWAKEUP,
        ICU_17_TIMERIP_E_PARAM_CHANNEL);/* End of report Error */
      }
    }
    #endif
    /*(ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) ||
    (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)*/
  }
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer GlbIndexStatusPtr is
   * accessed using assembly instruction. */
} /* End of function Icu_17_TimerIp_EnableWakeup */
#endif

/* Configuration for Disable Wakeup*/
#if (ICU_17_TIMERIP_DISABLE_WAKEUP_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {8221C022-B025-41c1-855B-CC1B66292235}]     **
**                                                                            **
** Syntax : void Icu_17_TimerIp_DisableWakeup(                                **
**                            const Icu_17_TimerIp_ChannelType Channel)       **
**                                                                            **
** Description : 1 This service will disable the wake-up capability of single **
**                 ICU channel for the following ICU mode selection(s).       **
**               2.This service is only feasible for ICU channels configured  **
**                 as wake-up capable true.                                   **
**               3.From the call of Icu_17_TimerIp_Init()channel which was    **
**                 configured as wakeup capable by using this service user can**
**                 disable the wakeup capability                              **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x03                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  Channel : Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={8F04E18D-D28A-48c4-AF5F-42751A7C4910}]
Safety Properties
[/cover]*/
void Icu_17_TimerIp_DisableWakeup(const Icu_17_TimerIp_ChannelType Channel)
{
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr;
  uint32* GlbIndexStatusPtr;
  uint8 CoreChIndex;
  uint8 CoreId;
  /* Get core id which is executing currently */
  CoreId = (uint8)(Mcal_GetCpuIndex());
  /* STATIC CHECK: if DET or Safety error reporting is enabled */
  /* [cover parentID={43A33134-3928-447a-8D5E-E260C7C3B6DE}]
  DET or Safety is enabled
  [/cover] */
  #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  uint32 ErrorFlag;
  /* Check for valid channel, mode and core. Raise a DET/Safety Error as
   * applicable */
  /* [cover parentID={52909F07-4FD5-475e-AAC4-E043E6B42AA1}]
  Preconditions check, sleep mode check and channel validation
  [/cover] */
  ErrorFlag = Icu_lNotifiDetCheck(Channel, ICU_17_TIMERIP_SID_DISABLEWAKEUP,
                  ICU_17_TIMERIP_MODE_SIGNAL_EDGE_DETECT, CoreId, ICU_FLAG_SET);
  /* [cover parentID={1C05A225-89CE-4cf4-82A0-844D4D55B22E}]
  If any DET occured
  [/cover] */
  if (ICU_ERROR_FOUND != ErrorFlag)
  #endif
  {
    /* Extract the Core Specific channel index */
    CoreChIndex = Icu_lGetCoreChIndex((uint8)Channel);
    /* Initialize ICU configured channel ROM pointer */
    LocalIcuChanPtr = &((Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->
                                                ChannelConfigPtr)[CoreChIndex]);
    /* Extract the address to the channel status flags */
    GlbIndexStatusPtr =
        &((Icu_17_TimerIp_Varlist[CoreId]->GlbIndexStatusBasePtr)[CoreChIndex]);
    /* [cover parentID={D58BECAB-7970-4b6a-85C1-9F7073FAE1C3}]
    Det or safety is enabled
    [/cover] */
#if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
    /* [cover parentID={23142B2F-A55A-48f8-AF18-DE19BAD2816C}]
    Is timeout feature exclusive?
    [/cover] */
    if((uint32)ICU_SET_BIT == LocalIcuChanPtr->IcuProperties.IsTimeOutExclusive)
    {
      ErrorFlag = (uint32) ICU_ERROR_FOUND;
      /* [cover parentID={3325B5A8-7CA5-4ac1-BE0D-5E10225AD83A}]
      Report invalid channel
      [/cover] */
      Icu_lReportError(
        ICU_17_TIMERIP_SID_DISABLEWAKEUP,
        ICU_17_TIMERIP_E_PARAM_CHANNEL);
    }
    if (ICU_ERROR_FOUND != ErrorFlag)
    {
#endif
    /* Check configured wakeup capability */
    /* [cover parentID={A604C38B-E2F7-4f90-8CC4-5519E3DA2D02}]
    Is configured wakeup capable
    [/cover] */
    if (LocalIcuChanPtr->IcuProperties.WakeupCapability == 1U)
    {
      /* check if the channel is wakeup capable */
      /* [cover parentID={0A51C171-A68B-4700-B723-0F734C43AF02}]
      if the channel is wakeup capable
      [/cover] */
      if(1U == Mcal_GetBitAtomic(*GlbIndexStatusPtr,
          ICU_CHNL_WAKEUP_CAPABLE_POS, ICU_CHNL_WAKEUP_BIT_LENGTH))
      {
        /* Don't Make Channel as Wakeup capable */
        /* Clear the Wakeup flag for the channel */
        /* [cover parentID={E1DA2FED-1992-4e6a-B967-15E9BB199524}]
        Reset bit at ICU_CHNL_WAKEUP_CAPABLE_POS atomically
        [/cover] */
        Mcal_SetBitAtomic(GlbIndexStatusPtr,
            ICU_CHNL_WAKEUP_CAPABLE_POS,ICU_CHNL_WAKEUP_BIT_LENGTH, \
            (uint32)0U);
      }
    }
    /* [cover parentID={6A8F5C95-6251-4351-8422-57476591A6E4}]
    DET or Safety is enabled.
    [/cover] */
    /* STATIC CHECK: if DET or Safety error reporting is enabled */
    #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
    (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
    else
    {
      /* Report a DET/Safety Error if a channel is not configured wakeup
       * capable */
      /* [cover parentID={5050D1EA-1683-49f5-9FFA-7D32EB90AAAA}]
      Report a DET to indicate that the channel is not valid.
      [/cover] */
      Icu_lReportError(
        ICU_17_TIMERIP_SID_DISABLEWAKEUP,
        ICU_17_TIMERIP_E_PARAM_CHANNEL);/* End of report Error */
      }
    }
    #endif
  }
  /* [cover parentID={5D0F49AF-3538-4586-9878-04FB9654D8D1}]
    ICU Interrupt Control Registers.
  [/cover] */
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer GlbIndexStatusPtr is
   * accessed using assembly instruction. */
}/* End of function Icu_17_TimerIp_DisableWakeup */
#endif

#if ((ICU_17_TIMERIP_WAKEUP_FUNCTIONALITY_API == STD_ON) && \
(ICU_17_TIMERIP_REPORT_WAKEUP_SOURCE == STD_ON))
/*******************************************************************************
** Traceability: [cover parentID= {0897A5BE-58B5-4947-AD97-CD98CCEFC2F5}]     **
**                                                                            **
** Syntax : void Icu_17_TimerIp_CheckWakeup(                                  **
**                           const EcuM_WakeupSourceType WakeupSource)        **
**                                                                            **
** Description : Checks if a wakeup capable ICU channel is the source for a   **
**               wakeup event and calls the ECU state manager service         **
**               EcuM_SetWakeupEvent in case of a valid ICU channel           **
**               wakeup event.                                                **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x15                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  WakeupSource-Information on wakeup source to be checked. **
**    The associated ICU channel can be determined from configuration data.   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={8F04E18D-D28A-48c4-AF5F-42751A7C4910}]
Safety Properties
[/cover]*/
void Icu_17_TimerIp_CheckWakeup(const EcuM_WakeupSourceType WakeupSource)
{

  uint8 CoreId;
  /* Get core id which is executing currently */
  CoreId = (uint8)(Mcal_GetCpuIndex());
  /* [cover parentID={D25689AF-AE03-4f2b-A478-57CBA65E0D61}]
  DET or Safety is enabled
  [/cover] */
  #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  uint32 ErrorFlag;
  /* [cover parentID={FE1A3E6B-7833-4ffa-9221-5256902DE40E}]
  Verify whether Init has been called
  [/cover] */
  /* Verify whether Init has been called */
  ErrorFlag = Icu_lInitCallVerify(ICU_17_TIMERIP_SID_CHECKWAKEUP, CoreId);
  /* [cover parentID={B6700728-DFC0-4085-B0A8-9D3A09CDB5CA}]
  Any DET reported
  [/cover] */
  if (ErrorFlag != ICU_ERROR_FOUND)
  #endif
    /*(ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON)*/
  {
    /* [cover parentID={1D1513A1-1DAD-49c1-AD5C-FECCDA645313}]
    If Wakeup info stored matches with input wakeup source
    [/cover] */
    /* Wakeup info stored matches with WakeupSource */
    if (Icu_17_TimerIp_Varlist[CoreId]->WakeupChannelInfo == WakeupSource)
    {
      /* [cover parentID={DFDE90B6-751C-45de-9E7B-B7307451CF69}]
      Call EcuM Setwakeup event.
      [/cover] */
      EcuM_SetWakeupEvent(WakeupSource);
    }
  }
  /* [cover parentID={5D0F49AF-3538-4586-9878-04FB9654D8D1}]
    ICU Interrupt Control Registers.
  [/cover] */
}/* End of Icu_17_TimerIp_CheckWakeup*/
#endif

#if (ICU_17_TIMERIP_SIGNAL_MEASUREMENT_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {2F5587A9-72BA-428c-8C6C-31896998345A}]     **
**                                                                            **
** Syntax :          void Icu_17_TimerIp_StartSignalMeasurement (             **
**                                 const Icu_17_TimerIp_ChannelType Channel)  **
**                                                                            **
** Description : 1. This service starts the measurement of signals beginning  **
**                  with the configured default start edge which occurs first **
**                  after the call of this service.                           **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x13                                                     **
**                                                                            **
** Sync/Async:       Asynchronous                                             **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  None                                                     **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={8F04E18D-D28A-48c4-AF5F-42751A7C4910}]
Safety Properties
[/cover]*/
void Icu_17_TimerIp_StartSignalMeasurement(
  const Icu_17_TimerIp_ChannelType Channel)
{
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr; /* ROM pointer */
  #if (ICU_17_TIMERIP_CCU6_USED == STD_ON)
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating this
   * MISRA rule,To implement efficiently IcuMeasaurementProperty as a post-build
   * parameter.Union is required*/
  Icu_17_TimerIp_ChannelData* SigMeasurePtr;
  #endif
  uint32* GlbIndexStatusPtr;
  uint16 CellUsed;
  uint8 CfgEdge = 0U;
  uint8 CoreChIndex;
  #if (ICU_17_TIMERIP_CCU6_USED == STD_ON)
  uint8 ChIndex;
  #endif
  #if(ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
  uint8 GtmSigKind;
  #endif
  uint8 SigKind = 0U;
  uint8 CoreId;
  /* Get core id which is executing currently */
  CoreId = (uint8)(Mcal_GetCpuIndex());
  /* [cover parentID={91639BC2-FCBF-49e9-A137-8D0750EC7EB5}]
  DET or Safety is enabled
  [/cover] */
  #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  uint32 ErrorFlag;

  /* [cover parentID={5507A207-CA1F-404f-B7F9-20D09F5FC335}]
  Preconditions check, sleep mode check and channel validation
  [/cover] */
  ErrorFlag = Icu_lNotifiDetCheck(Channel,
                                  ICU_17_TIMERIP_SID_STARTSIGNALMEASUREMENT,
                                  ICU_17_TIMERIP_MODE_SIGNAL_MEASUREMENT,
                                  CoreId, ICU_FLAG_SET);
  /* [cover parentID={AC49637A-B462-4e90-A778-2960C6344544}]
  Any DET reported
  [/cover] */
  if (ICU_ERROR_FOUND != ErrorFlag)
  #endif
    /* #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Initialize ICU configured channel ROM pointer */
    CoreChIndex = Icu_lGetCoreChIndex((uint8)Channel);
    LocalIcuChanPtr = &((Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->
                                                ChannelConfigPtr)[CoreChIndex]);
    #if ((ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_OFF) && \
    (ICU_17_TIMERIP_SAFETY_ENABLE == STD_OFF))
    /* Check if the mode is valid */
    /* [cover parentID={61616B9E-2721-4cfd-A26B-29D317C9E065}]
    Is the channel in signal measurement mode?
    [/cover] */
    if (LocalIcuChanPtr->IcuProperties.MeasurementMode
        == (uint32)ICU_17_TIMERIP_MODE_SIGNAL_MEASUREMENT)
    #endif
    {
      /* Extract the actual cell number */
      CellUsed = (uint16)LocalIcuChanPtr->IcuProperties.AssignedHwUnitNumber;
      /* The signal measure property is retrieved here */
      SigKind = LocalIcuChanPtr->IcuProperties.MeasurementProperty;
      /* get the channel flags register */
      GlbIndexStatusPtr =
        &((Icu_17_TimerIp_Varlist[CoreId]->GlbIndexStatusBasePtr)[CoreChIndex]);
      CfgEdge = (uint8)(Mcal_GetBitAtomic(*GlbIndexStatusPtr,\
         ICU_CHNL_EDGE_POS,ICU_CHNL_EDGE_BIT_LENGTH));
      /* Depending on ICU option take action */
      switch(LocalIcuChanPtr->IcuProperties.AssignedHwUnit)
      {
        /* [cover parentID={A25B40E8-2409-466c-A622-8223054AB589}]
        If ICU option is GTM
        [/cover] */
        case ICU_17_TIMERIP_GTM_OPTION:/* ICU ICU_17_TIMERIP_GTM_OPTION */
          #if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) && \
          (ICU_17_TIMERIP_SIGNAL_MEASUREMENT_API == STD_ON)
          /* [cover parentID={F8792900-ECDC-485d-9AD3-EF3E4C6119D3}]
          Identify the edge(rising/falling) to be configured as per the
          measurement mode and edge configured
          [/cover] */
          if(((uint8)ICU_17_TIMERIP_PERIOD_TIME == SigKind) || \
              (SigKind == (uint8)ICU_17_TIMERIP_DUTY_CYCLE))
          {
            if(CfgEdge == (uint8)ICU_17_TIMERIP_FALLING_EDGE)
            {
              GtmSigKind = 0U;
            }
            else if(CfgEdge == (uint8)ICU_17_TIMERIP_RISING_EDGE)
            {
              GtmSigKind = 1U;
            }
            else
            {
              GtmSigKind = (uint8)ICU_17_TIMERIP_BOTH_EDGES;
            }
          }
          else if(SigKind == (uint8)ICU_17_TIMERIP_HIGH_TIME)
          {
            GtmSigKind = (uint8)ICU_GTM_TIM_HIGH_LOW_TIME;
          }
          else /* ICU_17_TIMERIP_LOW_TIME */
          {
            GtmSigKind = (uint8)1U | (uint8)ICU_GTM_TIM_HIGH_LOW_TIME;
          }
          /* [cover parentID={636019AA-7809-40d2-833B-BA083F108556}]
          Start the TIM channel for Signal Measurement
          [/cover] */
          CfgEdge = Icu_lGtmStartSignalMeasurement(CellUsed, GtmSigKind);
          if(GtmSigKind == (uint8)ICU_17_TIMERIP_BOTH_EDGES)
          {
            Mcal_SetBitAtomic(GlbIndexStatusPtr, ICU_CHNL_EDGE_POS,
                              ICU_CHNL_EDGE_BIT_LENGTH, (uint32 )CfgEdge);
          }
          #endif
          break;
        /* [cover parentID={386E9527-A963-4b72-89C9-EA3E80567F93}]
        If ICU option CCU
        [/cover] */
        default:
          /* Store the address in a pointer variable */
          #if (ICU_17_TIMERIP_CCU6_USED == STD_ON)
          ChIndex = LocalIcuChanPtr->ModeMappingIndex;
          SigMeasurePtr =
               &((Icu_17_TimerIp_Varlist[CoreId]->ChannelDataBasePtr)[ChIndex]);
          SigMeasurePtr->SigMeasureParasCcu6.ActiveTime = 0U;
          SigMeasurePtr->SigMeasureParasCcu6.RegValue = 0U;
          SigMeasurePtr->SigMeasureParasCcu6.FirstEdgeFlag = 0U;
          /* [cover parentID={BB6B5209-7900-435d-8557-96F952FCD721}]
          Start signal measurement on CCU6 channel
          [/cover] */
          Icu_lCcuSignalMeasHandler(CellUsed, SigKind, CfgEdge);
          #endif
          break;
      }
      /* Set the ICU_ACTIVITY_STARTED flag */
      /* [cover parentID={06BCF4F3-461E-4075-BFA8-C482297369D8}]
      Set the flag to indicate activity started and active status to idle.
      [/cover] */
      Mcal_SetBitAtomic( \
          GlbIndexStatusPtr, (sint32)ICU_CHNL_ACTIVITY_STARTED_POS,\
          ICU_CHNL_ACTIVITY_BIT_LENGTH, (uint32)ICU_ACTIVITY_STARTED);
      /* Clear input state flag */
      Mcal_SetBitAtomic( \
          GlbIndexStatusPtr, (sint32)ICU_CHNL_STATUS_POS,\
          ICU_CHNL_STATUS_BIT_LENGTH, (uint32)ICU_17_TIMERIP_IDLE);
      /* Clear signal measure new value flag. */
      Mcal_SetBitAtomic( \
          GlbIndexStatusPtr, (sint32)ICU_SIGNALMESURE_INPUT_STAT_POS,\
          ICU_SIGNALMESURE_INPUT_STAT_LENGTH, (uint32)ICU_17_TIMERIP_IDLE);

    }
  }
  /* [cover parentID={5D0F49AF-3538-4586-9878-04FB9654D8D1}]
    ICU Interrupt Control Registers.
  [/cover] */
  /* MISRA2012_RULE_2_2_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the variable GlbIndexStatusPtr is
   * accessed using assembly instruction. */
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer GlbIndexStatusPtr is
   * accessed using assembly instruction. */
}
/* End of function Icu_17_TimerIp_StartSignalMeasurement */
#endif

#if (ICU_17_TIMERIP_SIGNAL_MEASUREMENT_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {6D24BC91-D5CF-46d6-8249-9EDEC0157A13}]     **
**                                                                            **
** Syntax :          void Icu_17_TimerIp_StopSignalMeasurement (              **
**                                 const Icu_17_TimerIp_ChannelType Channel)  **
**                                                                            **
** Description : 1. This service stops the measurement of signals on the      **
**                  given channel                                             **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x14                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  None                                                     **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={8F04E18D-D28A-48c4-AF5F-42751A7C4910}]
Safety Properties
[/cover]*/
void Icu_17_TimerIp_StopSignalMeasurement(
  const Icu_17_TimerIp_ChannelType Channel)
{
  /* Local pointers */
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr; /* ROM pointer */
  uint32* GlbIndexStatusPtr;
  uint16 CellUsed;
  uint8 CoreChIndex;
  uint8 CoreId;
  /* Get core id which is executing currently */
  CoreId = (uint8)(Mcal_GetCpuIndex());
  /* [cover parentID={9E9689E7-E9F7-40b6-B71C-96A6B2D85D48}]
  DET or Safety is enabled
  [/cover] */
  #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  uint32 ErrorFlag;
  /* Verify any error is there for DET */
  /* [cover parentID={8D780A4A-B356-4cbb-A161-AC070833516D}]
  Preconditions check, sleep mode check and channel validation
  [/cover] */
  ErrorFlag = Icu_lNotifiDetCheck(Channel,
                                  ICU_17_TIMERIP_SID_STOPSIGNALMEASUREMENT,
                                  ICU_17_TIMERIP_MODE_SIGNAL_MEASUREMENT,
                                  CoreId, ICU_FLAG_SET);
  /* [cover parentID={BA1FC5C7-385A-43e5-8245-31EE46ECA5A7}]
  Any DET reported
  [/cover] */
  if (ICU_ERROR_FOUND != ErrorFlag)
  #endif
  {
    /* Initialize ICU configured channel ROM pointer */
    CoreChIndex = Icu_lGetCoreChIndex((uint8)Channel);
    LocalIcuChanPtr = &((Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->
                                                ChannelConfigPtr)[CoreChIndex]);
    #if ((ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_OFF) && \
    (ICU_17_TIMERIP_SAFETY_ENABLE == STD_OFF))
    /* Check if the mode is valid */
    /* [cover parentID={EC7964A3-4385-4ba5-947C-66E614290F61}]
    Is the channel in signal measurement mode?
    [/cover] */
    if (LocalIcuChanPtr->IcuProperties.MeasurementMode
        == (uint32)ICU_17_TIMERIP_MODE_SIGNAL_MEASUREMENT)
    #endif
    {
      /* Extract the actual cell number */
      CellUsed = (uint16)LocalIcuChanPtr->IcuProperties.AssignedHwUnitNumber;
      /* Depending on ICU option take action */
      switch(LocalIcuChanPtr->IcuProperties.AssignedHwUnit)
      {
        /* [cover parentID={840F2E82-DA65-4656-9F30-2BB0A3D6FC68}]
        If ICU option is GTM
        [/cover] */
        case ICU_17_TIMERIP_GTM_OPTION:
          /* Stop the Signal Measurement */
          #if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) && \
          (ICU_17_TIMERIP_SIGNAL_MEASUREMENT_API ==STD_ON)
          /* [cover parentID={8C7B5F2E-A1CB-43c8-A896-69F15888A4F3}]
          Stop the Signal Measurement
          [/cover] */
          Icu_lGtmStopSignalMeasurement(CellUsed);
          #endif
          break;
        /* [cover parentID={9A5B7B36-EC1E-448b-936E-C4B090828873}]
        If ICU option is CCU
        [/cover] */
        default:
          /* CCU6 stop signal measure. */
          #if (ICU_17_TIMERIP_CCU6_USED == STD_ON) && \
          (ICU_17_TIMERIP_SIGNAL_MEASUREMENT_API ==STD_ON)
          /* [cover parentID={4C9986C7-5BDE-4837-BC5C-0060794B9907}]
          Stop the Signal Measurement
          [/cover] */
          Icu_lCcuStopSignalMeas(CellUsed);
          #endif
          break;
      }
      GlbIndexStatusPtr =
        &((Icu_17_TimerIp_Varlist[CoreId]->GlbIndexStatusBasePtr)[CoreChIndex]);
      /* [cover parentID={9772FAF2-EE30-404d-80F5-B62905903AB0}]
      Re-Set the ICU_ACTIVITY_STARTED flag
      [/cover] */
      Mcal_SetBitAtomic( \
        GlbIndexStatusPtr, (sint32)ICU_CHNL_ACTIVITY_STARTED_POS,\
        ICU_CHNL_ACTIVITY_BIT_LENGTH, 0U);
    }
  }
  /* [cover parentID={5D0F49AF-3538-4586-9878-04FB9654D8D1}]
    ICU Interrupt Control Registers.
  [/cover] */
  /* MISRA2012_RULE_2_2_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the variable GlbIndexStatusPtr is
   * accessed using assembly instruction. */
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer GlbIndexStatusPtr is
   * accessed using assembly instruction. */
}/* End of function Icu_17_TimerIp_StopSignalMeasurement */
#endif

#if (ICU_17_TIMERIP_GET_TIME_ELAPSED_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {7F661BDE-D141-4b12-ACA7-D3635DB4CFF1}]     **
**                                                                            **
** Syntax :         Icu_17_TimerIp_ValueType Icu_17_TimerIp_GetTimeElapsed (  **
**                                const Icu_17_TimerIp_ChannelType Channel )  **
**                                                                            **
** Description : 1. This service will return the latest time difference value **
**                  measured as per the configured type of measurement.       **
**                  The service shall measure the following measurement types **
**                  High Time, Low Time Or Period Time.                       **
**               2. The service shall return zero if there were no edges      **
**                  captured or the service has already read the same value.  **
**               3. For a successful read the service sets the Channel Status **
**                  to ICU_17_TIMERIP_IDLE.                                   **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x10                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     Icu_17_TimerIp_ValueType : measured value                **
**                                                                            **
*******************************************************************************/
/*[cover parentID={8F04E18D-D28A-48c4-AF5F-42751A7C4910}]
Safety Properties
[/cover]*/
Icu_17_TimerIp_ValueType Icu_17_TimerIp_GetTimeElapsed(
  const Icu_17_TimerIp_ChannelType Channel)
{
  /* API to read High Time, Low Time Or Period Time */
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr;
  #if (ICU_17_TIMERIP_CCU6_USED == STD_ON)
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * MISRA rule,To implement efficiently IcuMeasaurementProperty as a post-build
   * parameter.Union is required*/
  Icu_17_TimerIp_ChannelData* SigMeasurePtr;
  uint8 ChIndex;
  #endif
  #if (ICU_17_TIMERIP_CCU6_USED == STD_ON) || \
  (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  uint8 Measure = 0U;
  #endif
  Icu_17_TimerIp_ValueType Time;
  uint32* GlbIndexStatusPtr;
  uint16 CellUsed;
  uint8 CoreChIndex;
  uint8 Hwused;
  /* #if(ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) */
  uint8 CoreId;
  /* Get core id which is executing currently */
  CoreId = (uint8)(Mcal_GetCpuIndex());
  /* [cover parentID={7161C023-F438-4303-93E2-9844F3DEDB58}]
  DET or Safety is enabled
  [/cover] */
  #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  uint32 ErrorFlag;
  /* [cover parentID={60526F83-38B9-48c5-B105-0668800A48BC}]
  Preconditions check, sleep mode check and channel validation
  [/cover] */
  /* Verify any error is there for DET */
  /* Verify whether the channel number is valid,
     configured for Signal Measurement */
  ErrorFlag = Icu_lNotifiDetCheck(Channel,
                                  ICU_17_TIMERIP_SID_GETTIMEELAPSED,
                                  ICU_17_TIMERIP_MODE_SIGNAL_MEASUREMENT,
                                  CoreId, ICU_FLAG_SET);
  /* [cover parentID={203B07B4-DB1D-4b85-A33F-36ACBB8CC6C4}]
  Any DET reported
  [/cover] */
  if (ICU_ERROR_FOUND == ErrorFlag)
  {
    /* Return without executing any of functionality */
    Time = (Icu_17_TimerIp_ValueType)0;
  }
  else
  #endif
    /* #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) */
  {
    CoreChIndex = Icu_lGetCoreChIndex((uint8)Channel);
    LocalIcuChanPtr = &((Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->
                                                ChannelConfigPtr)[CoreChIndex]);
    Hwused = (uint8)LocalIcuChanPtr->IcuProperties.AssignedHwUnit;
    /* Extract the actual cell number */
    CellUsed = (uint16)LocalIcuChanPtr->IcuProperties.AssignedHwUnitNumber;
    #if (ICU_17_TIMERIP_CCU6_USED == STD_ON) || \
    (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
    (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
    /* Measurement property configured for this channel */
    Measure = (uint8)LocalIcuChanPtr->IcuProperties.MeasurementProperty;
    #endif

    /* [cover parentID={DEC6B186-622B-4412-A858-F13B5B825947}]
    DET or Safety is enabled
    [/cover] */
    #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
    (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
    /* [cover parentID={1D9C7CB9-E3BE-4f8e-8F50-D2CF22C01FA9}]
    If Measurement property is DutyCycle
    [/cover] */
    if(Measure == (uint8)ICU_17_TIMERIP_DUTY_CYCLE)
    {
      /* [cover parentID={BDF833D2-1DE7-4922-9D93-478C74605196}]
       Report Safety and DET Error for wrong measurement property
       [/cover] */
      /* Duty not supported  and a raise error*/
      Icu_lReportError(
        ICU_17_TIMERIP_SID_GETTIMEELAPSED,
        ICU_17_TIMERIP_E_PARAM_CHANNEL); /* Report Error */
      Time = (Icu_17_TimerIp_ValueType)0;
    }
    else
    #endif
    {
      /* Extract the address for the Global Index status */
      GlbIndexStatusPtr =
        &((Icu_17_TimerIp_Varlist[CoreId]->GlbIndexStatusBasePtr)[CoreChIndex]);
      /* Depending on ICU option take action */
      switch(Hwused)
      {
        /* [cover parentID={36022074-20A5-4055-A5C1-6D5C0921587C}]
        If hardware used is GTM
        [/cover] */
        case (uint8)ICU_17_TIMERIP_GTM_OPTION:
          /* Get the required value */
          #if(ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
          /* [cover parentID={BA9198DC-6BDB-406e-9B1F-871A4BA499F0}]
          Get the time elapsed
          [/cover] */
          Time = Icu_lGtmGetTimeElapsed(CellUsed, GlbIndexStatusPtr);
          /* Mask the measured value to 24 bit */
          /* [cover parentID={CF877A33-BBD7-402e-ADFD-BFFE724A4E44}]
          Mask the output value with 24bit vlaue for TIM
          [/cover] */
          Time = (Icu_17_TimerIp_ValueType) ((Time) & (ICU_24BIT_MASK));
          #else
          /* Elapsed time is initialized to 0 */
          /* [cover parentID={4229C1A2-FA76-46c4-BD70-E8604AC21330}]
          Set elapsed time to zero
          [/cover] */
          Time = (Icu_17_TimerIp_ValueType)0;
          #endif
          break;
        default:
          #if(ICU_17_TIMERIP_CCU6_USED == STD_ON)
          /* [cover parentID={737195C8-CD2E-4d0e-BAD9-7D04D26CE91C}]
          If the measurement property is period
          [/cover] */
          if(Measure == (uint8)ICU_17_TIMERIP_PERIOD_TIME)
          {
            /* [cover parentID={FE7BB800-D4B2-4fe6-B224-5CE8A6220C46}]
            Get the time elapsed
            [/cover] */
            Time = Icu_lCcuGetTimeElapsed(CellUsed, GlbIndexStatusPtr);
          }
          /* [cover parentID={0526BB39-A014-415d-ADC1-1005A5AFD34B}]
          if measurement property is low time or high time..
          [/cover] */
          else
          {
            ChIndex = LocalIcuChanPtr->ModeMappingIndex;
            /* Store the address in a pointer variable */
            SigMeasurePtr =
               &((Icu_17_TimerIp_Varlist[CoreId]->ChannelDataBasePtr)[ChIndex]);
            /* Read the time required and clear */
            /* [cover parentID={CBF58121-4A50-4e4b-8B9C-E1E2E2560C18}]
            Read the active time from the global variable and reset the global
             variable.
            [/cover] */
            /* MISRA2012_RULE_11_8_JUSTIFICATION: volatile variable access using
             * and assembly instruction. No side effect foreseen.*/
            /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between
              pointers of different object types inevitable as assembly
              instructions are used.*/
            Time = Mcal_Swap((&(SigMeasurePtr->SigMeasureParasCcu6.ActiveTime)),\
                             0U, ICU_SWAP_32BIT_MASK);
          }
          /* Mask the measured value to 16 bit */
          /* [cover parentID={9DFAE509-5251-4781-B974-C2011DE72335}]
          Mask the output value with 16bit vlaue
          [/cover] */
          Time = (Icu_17_TimerIp_ValueType) ((Time) & (ICU_CCU6_SIG_MEAS_MASK));
          #else
          /* Elapsed time is initialized to 0 */
          /* [cover parentID={4229C1A2-FA76-46c4-BD70-E8604AC21330}]
          Set elapsed time to zero
          [/cover] */
          Time = (Icu_17_TimerIp_ValueType)0;
          #endif
          break;
      }
    }
  }
  /* [cover parentID={5D0F49AF-3538-4586-9878-04FB9654D8D1}]
    ICU Interrupt Control Registers.
  [/cover] */
  return (Time);
}/* End of function Icu_17_TimerIp_GetTimeElapsed */
/* End of function Icu_17_TimerIp_GetTimeElapsed */
#endif
/* End of #if (ICU_17_TIMERIP_SIGNAL_MEASUREMENT_API == STD_ON) */

#if (ICU_17_TIMERIP_GET_DUTY_CYCLE_VALUES_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {68AA43ED-8A55-4857-8186-D50F39BDC4DC}]     **
**                                                                            **
** Syntax :          void Icu_17_TimerIp_GetDutyCycleValues (                 **
**                                 const Icu_17_TimerIp_ChannelType Channel,  **
**                      Icu_17_TimerIp_DutyCycleType *const DutyCycleValues ) **
**                                                                            **
** Description : 1. This service will return the latest high time             **
**                  and period time captured.                                 **
**               2. The service shall write zero in the given address         **
**                  if there were no edges captured or the                    **
**                  has already read the same value.                          **
**               3. A successful read puts the status to ICU_17_TIMERIP_IDLE  **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x11                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out): DutyCycleValues - Pointer to structure that could        **
**                                     hold high time and period time.        **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={8F04E18D-D28A-48c4-AF5F-42751A7C4910}]
Safety Properties
[/cover]*/
void Icu_17_TimerIp_GetDutyCycleValues(
  const Icu_17_TimerIp_ChannelType Channel,
  Icu_17_TimerIp_DutyCycleType *const DutyCycleValues)
{
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr;
  #if(ICU_17_TIMERIP_CCU6_USED == STD_ON)
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * MISRA rule,To implement efficiently IcuMeasaurementProperty as a post-build
   * parameter.Union is required*/
  Icu_17_TimerIp_ChannelData* SigMeasurePtr;
  #endif
  #if(ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
  uint32* GlbIndexStatusPtr;
  uint16 CellUsed;
  #endif
  uint32 IcuOption;
  uint8 CoreChIndex;
  #if(ICU_17_TIMERIP_CCU6_USED == STD_ON)
  uint32 IcuMeasTime;
  uint8 ChIndex;
  #endif
  uint8 Measure;
  uint8 CoreId;

  /* Get core id which is executing currently */
  CoreId = (uint8)(Mcal_GetCpuIndex());
  /* [cover parentID={75285AC3-C0F3-4f19-B58F-B21F76C72037}]
  DET or Safety is enabled
  [/cover] */
  #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  uint32 ErrorFlag;
  ErrorFlag = ICU_ERROR_NOT_FOUND;
  /* [cover parentID={CF014064-8C6A-4cd5-91B7-C131840A9958}]
  Is the output parameter NULL?
  [/cover] */
  if ( DutyCycleValues == NULL_PTR)
  {
    ErrorFlag = ICU_ERROR_FOUND;
    /* [cover parentID={7ED7BFD4-6700-4d1b-9D04-D54ADDBCADCD}]
    Report an error to indicate invalid input pointer
    [/cover] */
    Icu_lReportError(
      ICU_17_TIMERIP_SID_GETDUTYCYCLEVALUES,
      ICU_17_TIMERIP_E_PARAM_POINTER
    ); /* Report Error */
  }

  if (ICU_ERROR_FOUND != ErrorFlag)
  {
    /* Verify any error is there for DET */
    /* Verify whether the channel number is valid,
      configured for Signal Measurement */
    /* [cover parentID={ECCBAE0C-085B-410d-9B43-F930718E652D}]
    Preconditions check, sleep mode check and channel validation
    [/cover] */
    ErrorFlag = Icu_lNotifiDetCheck(Channel,
                                    ICU_17_TIMERIP_SID_GETDUTYCYCLEVALUES,
                                    ICU_17_TIMERIP_MODE_SIGNAL_MEASUREMENT,
                                    CoreId, ICU_FLAG_SET);
    /* [cover parentID={32E5E162-A53E-4e2d-B3C2-5904B8B20010}]
    Any DET reported?
    [/cover] */
    if (ICU_ERROR_FOUND == ErrorFlag)
    {
      /* Initialize all variable to zero */
      /* [cover parentID={AECCAB31-D3AA-4d22-98B0-C52F77B7F705}]
      Initialize duty cycle active time and period time to zero
      [/cover] */
      DutyCycleValues->ActiveTime = (Icu_17_TimerIp_ValueType)0U;
      DutyCycleValues->PeriodTime = (Icu_17_TimerIp_ValueType)0U;
    }
  }
  if (ICU_ERROR_FOUND != ErrorFlag)
  #endif
    /* #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) */
  {
    CoreChIndex = Icu_lGetCoreChIndex((uint8)Channel);
    LocalIcuChanPtr = &((Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->
                                                ChannelConfigPtr)[CoreChIndex]);
    /* Depending on ICU option take action */
    IcuOption = LocalIcuChanPtr->IcuProperties.AssignedHwUnit;
    #if(ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
    /* Extract the actual cell number */
    CellUsed = (uint8)LocalIcuChanPtr->IcuProperties.AssignedHwUnitNumber;
    #endif
    /* Signal Measurement property is taken
       bit 0, bit 1 holds the information */
    Measure = (uint8)(LocalIcuChanPtr->IcuProperties.MeasurementProperty);
    /* Initialize all variable to zero */
    DutyCycleValues->ActiveTime = (Icu_17_TimerIp_ValueType)0U;
    DutyCycleValues->PeriodTime = (Icu_17_TimerIp_ValueType)0U;
    /* [cover parentID={3A7C733E-5323-43be-9C90-B41A6348A77F}]
    Is measurement property duty cycle?
    [/cover] */
    if(Measure != (uint8)ICU_17_TIMERIP_DUTY_CYCLE)
    {
      /* [cover parentID={452598D1-05EF-46cf-98BE-99CD33F53997}]
      DET or Safety is enabled
      [/cover] */
      #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
      (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
      /* [cover parentID={5629D80E-82B3-4899-81CE-E89AB1C1BFA4}]
      Report error to  DET to indicate invalid channel mode.
      [/cover] */
      Icu_lReportError(
        ICU_17_TIMERIP_SID_GETDUTYCYCLEVALUES,
        ICU_17_TIMERIP_E_PARAM_CHANNEL
      ); /* Report Error */
      #endif
    }
    else
    {
      /* Depending on ICU option take action */
      switch(IcuOption)
      {
        /* [cover parentID={6E3F3CB3-6200-4294-8755-D93F448EDDEB}]
        If hardware used is GTM
        [/cover] */
        case ICU_17_TIMERIP_GTM_OPTION:
          #if(ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
          /* Extract the address for the Global Index status */
          GlbIndexStatusPtr =
        &((Icu_17_TimerIp_Varlist[CoreId]->GlbIndexStatusBasePtr)[CoreChIndex]);
          /* Get the required value */
          /* [cover parentID={D9CCAB50-5C0F-4340-B5A6-C41322772CC5}]
          Get duty cycle value for aTIM channel.
          [/cover] */
          Icu_lGtmGetDutyCycleValues(CellUsed,
                                     GlbIndexStatusPtr, DutyCycleValues);
          #endif
          break;
        /* [cover parentID={712EC443-9739-4b99-8311-02F1661F5353}]
        If hardware used is CCU6
        [/cover] */
        default:
          #if(ICU_17_TIMERIP_CCU6_USED == STD_ON)
          ChIndex = LocalIcuChanPtr->ModeMappingIndex;
          /* Store the address in a pointer variable */
          SigMeasurePtr =
            &((Icu_17_TimerIp_Varlist[CoreId]->ChannelDataBasePtr)[ChIndex]);
          /* [cover parentID={37EEF766-876F-4095-BE89-3E2AD892229E}]
            Extract duty cycle active time and period time with 16 bit mask
            from global variable and reset global variable.
          [/cover] */
          /* Read and clear the values */
          /* MISRA2012_RULE_11_8_JUSTIFICATION: volatile variable access using
           * and assembly instruction. No side effect foreseen.*/
          /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between
            pointers of different object types inevitable as assembly
            instructions are used.*/
          IcuMeasTime = Mcal_Swap(\
             ((uint32*)&(SigMeasurePtr->SigMeasureParasCcu6.ActiveTime)),0U,\
             ICU_SWAP_32BIT_MASK);
          /*Read Active and Period*/
          DutyCycleValues->PeriodTime = (uint32)(IcuMeasTime &
                                                 ICU_CCU6_SIG_MEAS_MASK);
          DutyCycleValues->ActiveTime = (uint32)((IcuMeasTime >>
                   ICU_CCU6_SIG_MEAS_ACTIVETIME_OFFSET)&ICU_CCU6_SIG_MEAS_MASK);
#endif
          break;
      }
    }
  }
  /* [cover parentID={5D0F49AF-3538-4586-9878-04FB9654D8D1}]
    ICU Interrupt Control Registers.
  [/cover] */
}
/* End of function Icu_17_TimerIp_GetDutyCycleValues */

#endif
/* End of #if (ICU_GET_DUTY_CYCLE_VALUES_API == STD_ON) */

#if (ICU_17_TIMERIP_GET_INPUT_STATE_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {4F5E5472-C0CB-4f37-B548-2EE449DED129}]     **
**                                                                            **
** Syntax :Icu_17_TimerIp_InputStateType Icu_17_TimerIp_GetInputState(        **
**                                const Icu_17_TimerIp_ChannelType Channel)   **
**                                                                            **
** Description : 1. This service returns the status of the ICU input.         **
**               2. If an activation edge has been detected this service will **
**                  return ICU_17_TIMERIP_ACTIVE.                             **
**               3. Once the service has returned the status                  **
**                  ICU_17_TIMERIP_ACTIVE the stored status will be set to    **
**                  ICU_17_TIMERIP_IDLE until the next edge is detected.      **
**               4. If no  edge has been detected this service will           **
**                  return ICU_17_TIMERIP_IDLE.                               **
**               5. If development error detection is enabled and an error is **
**                  detected the service returns ICU_17_TIMERIP_IDLE.         **
**               6. Signal edge detection channels                            **
**                  channels status is changed here.                          **
**               7. For a signal measurement channel only the status          **
**                  is returned and its not put to IDLE. A successful read    **
**                  of Icu_17_TimerIp_GetTimeElapsed or                       **
**                  Icu_17_TimerIp_GetDutyCycleValues                         **
**                  will set the state to ICU_17_TIMERIP_IDLE                 **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x08                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     Icu_17_TimerIp_InputStateType -                          **
**                   Returns the state of Channel                             **
**                                                                            **
*******************************************************************************/
/*[cover parentID={8F04E18D-D28A-48c4-AF5F-42751A7C4910}]
Safety Properties
[/cover]*/
Icu_17_TimerIp_InputStateType Icu_17_TimerIp_GetInputState(
  const Icu_17_TimerIp_ChannelType Channel)
{
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr;
  uint32* GlbIndexStatusPtr;
  uint16 CellUsed;
  Icu_17_TimerIp_InputStateType Status;
  uint8 CoreChIndex;
  uint32 IcuOption;

  uint8 CoreId;
  /* Get core id which is executing currently */
  CoreId = (uint8)(Mcal_GetCpuIndex());

  /* [cover parentID={33417D4A-C805-47ab-80AB-A549BC8A20FC}]
  DET and safety are disabled.
  [/cover] */
  #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  uint32 ErrorFlag;

  /* [cover parentID={27166EBA-C2EC-448c-B3C8-1B1680FED62F}]
  Initialize the state of channel to be returened to IDLE.
  [/cover] */
  Status = ICU_17_TIMERIP_IDLE;

  /* [cover parentID={26AAFAC4-7492-48c9-89D2-EBEB9C676C8E}]
  Preconditions check, sleep mode check and channel validation
  [/cover] */
  ErrorFlag = Icu_lGetInputStateDetCheck(Channel, CoreId);
  /* Perform action only if module is initialized and channel is valid */
  /* [cover parentID={55125E46-A619-48e3-9A04-BC162733ACA1}]
  Any DET found
  [/cover] */
  if (ICU_ERROR_FOUND != ErrorFlag)
  #endif
  {
    CoreChIndex = Icu_lGetCoreChIndex((uint8)Channel);
    LocalIcuChanPtr = &((Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->
                                                ChannelConfigPtr)[CoreChIndex]);
    GlbIndexStatusPtr =
        &((Icu_17_TimerIp_Varlist[CoreId]->GlbIndexStatusBasePtr)[CoreChIndex]);
    /* Extract the actual cell number */
    CellUsed = (uint16)LocalIcuChanPtr->IcuProperties.AssignedHwUnitNumber;

    /* Depending on ICU option take action */
    IcuOption = (uint32)LocalIcuChanPtr->IcuProperties.AssignedHwUnit;
    switch(IcuOption)
    {
      /* [cover parentID={9CF65634-87C6-46da-B724-60AD7095B15F}]
      If ICU option is GTM
      [/cover] */
      case ICU_17_TIMERIP_GTM_OPTION:/*Read Get input state for GTM*/
        /* [cover parentID={23C3BD79-1ABF-449a-8A3B-8BC21B6205F2}]
        Get GTM input state
        [/cover] */
        #if (ICU_17_TIMERIP_GTM_TIM_USED  == STD_ON)
        Status = Icu_lGtmGetInputState(CellUsed, GlbIndexStatusPtr);
        #else
        Status = ICU_17_TIMERIP_IDLE;
        #endif
        break;
      /* [cover parentID={86CD6339-F159-4cde-9458-2B43797BDB60}]
      If ICU option is CCU
      [/cover] */
      case ICU_17_TIMERIP_CCU_OPTION:/*Read Get input state for CCU*/
        /* [cover parentID={F115B14E-372D-4b88-8B01-67C4153A0446}]
        Get CCU input state
        [/cover] */
        #if (ICU_17_TIMERIP_CCU6_USED == STD_ON)
        Status = Icu_lCcu6GetInputState(CellUsed,GlbIndexStatusPtr,
            (uint8)(LocalIcuChanPtr->IcuProperties.MeasurementMode),
            (uint8)(LocalIcuChanPtr->IcuProperties.MeasurementProperty));
        #else
        Status = ICU_17_TIMERIP_IDLE;
        #endif
        break;
      /* [cover parentID={FEF6750F-366E-441f-A7D5-157413CB4C5F}]
      If ICU option is ERU
      [/cover] */
      case ICU_17_TIMERIP_ERU_OPTION:/*Read Get input state for ERU*/
        /* [cover parentID={66990E1B-800E-4c4a-8E5A-00E4FF222288}]
        Get ERU input state
        [/cover] */
        #if (ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON)
        Status = Icu_lEruGetInputState(CellUsed, GlbIndexStatusPtr);
        #else
        Status = ICU_17_TIMERIP_IDLE;
        #endif
        break;
      /* [cover parentID={7D26D257-F2FD-4759-BA29-1FCCF9818F86}]
      if ICU option is GPT12
      [/cover] */
      default:/*Read Get input state for GPT12*/
        /* [cover parentID={40941F89-2263-4d26-BD90-4B7867D53DC8}]
        Get GPT12 input state
        [/cover] */
        #if (ICU_17_TIMERIP_GPT12_USED == STD_ON)
        Status = Icu_lGpt12GetInputState(CellUsed, GlbIndexStatusPtr, \
                      (uint8)(Icu_17_TimerIp_Varlist[CoreId]->GlobalMode));
        #else
        Status = ICU_17_TIMERIP_IDLE;
        #endif
        break;
    }
  }
  /* This service returns the status of the ICU input*/
  return (Status);
  /* [cover parentID={5D0F49AF-3538-4586-9878-04FB9654D8D1}]
    ICU Interrupt Control Registers.
  [/cover] */
}/* End of function Icu_17_TimerIp_GetInputState */
#endif

/*******************************************************************************
** Traceability: [cover parentID= {E08C92CC-FF51-42db-8175-F57F464A4515}]     **
**                                                                            **
** Syntax : void Icu_17_TimerIp_SetActivationCondition(                       **
**                         const Icu_17_TimerIp_ChannelType Channel           **
**                         const Icu_17_TimerIp_ActivationType Activation)    **
**                                                                            **
** Description : 1 This service will set the required configured edge.        **
**               2.This service is only feasible for ICU channels configured  **
**                 as EdgeDetection,TimeStamp and EdgeCounter.                **
**               3.For Signal Measurement Only DefaultStartEdge to be Used    **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x05                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                   Activation - Active edge to be configured:               **
**                                ICU_17_TIMERIP_RISING_EDGE,                 **
**                                ICU_17_TIMERIP_FALLING_EDGE,                **
**                                ICU_17_TIMERIP_BOTH_EDGES                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={8F04E18D-D28A-48c4-AF5F-42751A7C4910}]
Safety Properties
[/cover]*/
void Icu_17_TimerIp_SetActivationCondition(
  const Icu_17_TimerIp_ChannelType   Channel,
  const Icu_17_TimerIp_ActivationType  Activation)
{
  /* This function is applicable for channels configured for all modes
   except Signal Measurement. Hence apart from the DET check, rest of the
   function is not needed for the case where the configuration only has
   signal measurement channels */
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr; /* ROM pointer */
  uint32* GlbIndexStatusPtr;
  uint32 IcuHwOption;
  uint16 CellUsed;
  uint8 CoreChIndex;
  uint8 CoreId;
  #if(ICU_17_TIMERIP_GPT12_USED == STD_ON)
  uint8 TxClearFlag;
  #endif
  #if (ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON)
  uint8 EruLineUsed;
  #endif
  /* Get core id which is executing currently */
  CoreId = (uint8)(Mcal_GetCpuIndex());
  /* STATIC CHECK: if DET or Safety error reporting is enabled */
  /* [cover parentID={6074738C-C502-45ce-AFA4-03E6E38BCAEB}]
   DET or Safety is enabled
   [/cover] */
  #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  uint32 ErrorFlag;
  /* [cover parentID={CD6E9208-BC9B-49eb-8052-9811E7C31AE7}]
  Precondition check
  [/cover] */
  ErrorFlag = Icu_lSetActivationConditionDETCheck(CoreId, Channel);
  /* [cover parentID={D7F1400F-6025-48f4-ACEC-9ACB3319C73E}]
  Any DET reported?
  [/cover] */
  if (ErrorFlag != ICU_ERROR_FOUND)
  {
    /*Check for valid activation parameter */
    /* [cover parentID={1B1ED7C7-3163-401e-A886-DF5C0F5B806E}]
    Is Activation Edge(input parameter) is valid?
    [/cover] */
    if ((uint32)Activation > (uint32)ICU_17_TIMERIP_BOTH_EDGES)
    {
      /* [cover parentID={EC95C0D2-298E-4c0e-95BD-38DBF4C82D56}]
      Report and error to indicate invalid parameter.
      [/cover] */
      ErrorFlag = ICU_ERROR_FOUND;
      Icu_lReportError(
        ICU_17_TIMERIP_SID_SETACTIVATIONCONDITION,
        ICU_17_TIMERIP_E_PARAM_ACTIVATION);
    }
  }
  /* Check if there are any previous errors */
  if (ErrorFlag != ICU_ERROR_FOUND)
  #endif
    /* #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) ||
     * (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)*/
  {
    /* Extract the Core Specific channel index */
    CoreChIndex = Icu_lGetCoreChIndex((uint8)Channel);
    /* Initialize ICU configured channel ROM pointer */
    LocalIcuChanPtr = &((Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->
                                                ChannelConfigPtr)[CoreChIndex]);
    /* Extract the address to the channel status flags */
    GlbIndexStatusPtr =
        &((Icu_17_TimerIp_Varlist[CoreId]->GlbIndexStatusBasePtr)[CoreChIndex]);
    /* Check the channel's mode */
    /* [cover parentID={0A1D6309-B6D9-4647-8EFE-BA21E3D727DE}]
    Is channel mode Signal measure or incremental interface mode?
    [/cover] */
    if ((LocalIcuChanPtr->IcuProperties.MeasurementMode
        == (uint32) ICU_17_TIMERIP_MODE_SIGNAL_MEASUREMENT) ||
        (LocalIcuChanPtr->IcuProperties.MeasurementMode
        == (uint32) ICU_17_TIMERIP_MODE_INCREMENTAL_INTERFACE))
    {
      /* This service shall support channels which are configured
       for the following IcuProperties.MeasurementMode:
       ICU_17_TIMERIP_MODE_SIGNAL_EDGE_DETECT
       ICU_17_TIMERIP_MODE_TIMESTAMP
       ICU_17_TIMERIP_MODE_EDGE_COUNTER */
      /* STATIC CHECK: if DET or Safety error reporting is enabled */
      /* [cover parentID={EB107C8D-18AB-4c91-AA65-C647AA4CAA93}]
       DET or Safety is enabled
       [/cover] */
      #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
      (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
      /* [cover parentID={C8E0AADA-4796-4bed-8D5C-05320C9AB14E}]
      Report Error
      [/cover] */
      Icu_lReportError(
        ICU_17_TIMERIP_SID_SETACTIVATIONCONDITION,
        ICU_17_TIMERIP_E_PARAM_CHANNEL);
      #endif
      /* #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) ||
                     (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)*/
    }
    /* [cover parentID={49833CF5-F0FF-4de1-978B-20970C1B0CF7}]
    Safety is enabled
    [/cover] */
    #if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
    /* [cover parentID={765287F8-E8FF-4aa1-B01A-64CC71F8FC79}]
    Is Activity Started on the channel?
    [/cover] */
    else if (ICU_ACTIVITY_STARTED
        == Mcal_GetBitAtomic(*GlbIndexStatusPtr, ICU_CHNL_ACTIVITY_STARTED_POS,
            ICU_CHNL_ACTIVITY_BIT_LENGTH))
    {
      /* Safety Error */
      /* [cover parentID={FC9CFB92-AABC-4758-BC63-E3C3197AFEBE}]
      Report Safety Error to indicate channel is busy
      [/cover] */
      Mcal_ReportSafetyError(
        ICU_17_TIMERIP_MODULE_ID,
        ICU_17_TIMERIP_INSTANCE_ID,
        ICU_17_TIMERIP_SID_SETACTIVATIONCONDITION,
        ICU_17_TIMERIP_E_BUSY_CHANNEL);
    }
    #endif
    /* End of report to Safety */
    else
    {
      /* Depending on ICU option take action */
      IcuHwOption = (uint32) LocalIcuChanPtr->IcuProperties.AssignedHwUnit;
      /* Extract the cell used.*/
      CellUsed = (uint16) LocalIcuChanPtr->IcuProperties.AssignedHwUnitNumber;
      /* switch depending on the HW used */
      /* [cover parentID={CF6279E1-322C-4d56-B441-9A514B506D70}]
       Perform action depending on HW configured.
       [/cover] */
      switch (IcuHwOption)
      {
        /* [cover parentID={D7E53A22-61C8-4c1a-8CE4-85293750BBA6}]
         If HW option is GTM
         [/cover] */
        case ICU_17_TIMERIP_GTM_OPTION:
          /* Set the hardware register for the new edge type */
          /* [cover parentID={041FCD3F-7BC5-4f2d-B8B4-D6BFF97FE977}]
          Set the hardware register for the new edge type
          [/cover] */
          #if(ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
          Icu_lGtmChangeActiveEdge(CellUsed, Activation);
          #endif
          break;
        /* [cover parentID={474501E1-5AF0-49f3-848C-8C0D5C60AAAD}]
        If HW option is CCU6
        [/cover] */
        case ICU_17_TIMERIP_CCU_OPTION:
          #if(ICU_17_TIMERIP_CCU6_USED == STD_ON)
          /* [cover parentID={1977A47B-760A-45bc-8A76-8504934090A0}]
          Set the CCU6 register for the new edge type
          [/cover] */
          Icu_lCcu6SetActivationCondition(CellUsed, (uint8) Activation);
          #endif
          break;
        /* [cover parentID={37BEF45A-23CD-44e1-BA35-C5E482436EE8}]
         If HW option is ERU
         [/cover] */
        case ICU_17_TIMERIP_ERU_OPTION:
          /* [cover parentID={676B2469-BDBF-47ef-9A24-A229B754A791}]
          Set ERU channel with new edge
          [/cover] */
          /*Critical section to updated REN and FEN*/
          /* [cover parentID={589356B2-D2BD-4de5-8B5C-75FC4C3E429F}]
          Critical Section
          [/cover] */
          #if (ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON)
          /* [cover parentID={D9EB6B05-8F3D-4571-98B9-D88B13EAA14F}]
          Enter critical section
          [/cover] */
          SchM_Enter_Icu_17_TimerIp_SetActivationCondition();
          /* [cover parentID={D09BFD1F-5260-493d-8CCF-7F823F0F8D59}]
          Is ERU edge detection enabled?
          [/cover] */
          if (1U
              == Mcal_GetBitAtomic(*GlbIndexStatusPtr,
                  ICU_CHNL_ERU_GPT_SIGEDGE_STATUS_POS,
                  ICU_CHNL_ERU_GPT_SIGEDGE_STATUS_BIT_LENGTH))
          {
            EruLineUsed = (((uint8) CellUsed) & ICU_ERU_CHNL_MASK);
            /* Clear Service Request if any was in pending */
            MODULE_SCU.FMR.U =
              (((uint32) 1UL) << (EruLineUsed + ICU_ERU_FCSTART));
            /* [cover parentID={04D18566-7B95-485f-8413-CCEA6B28D4A7}]
            Update the new edge in the HW register.
            [/cover] */
            /* Enable the cell for notification */
            Icu_lSetEruEdge((uint8) Activation, EruLineUsed);
          }
          Mcal_SetBitAtomic(GlbIndexStatusPtr, ICU_CHNL_EDGE_POS,
                        ICU_CHNL_EDGE_BIT_LENGTH, (uint32 )Activation);
          /*End Critical section to update REN and FEN*/
          /* [cover parentID={BF396311-AF43-401a-ADCF-964775DF62A2}]
          Exit critical section
          [/cover] */
          SchM_Exit_Icu_17_TimerIp_SetActivationCondition();
          #endif
          break;
        /* [cover parentID={30793C55-89B1-4a2b-ABD0-337634A24EE5}]
         If HW option is GPT12
         [/cover] */
        default:
          #if(ICU_17_TIMERIP_GPT12_USED == STD_ON)
          /* [cover parentID={367D3F3F-5617-430e-90DB-02088647C9AE}]
          Enter critical section.
          [/cover] */
          SchM_Enter_Icu_17_TimerIp_SetActivationCondition();
          /* [cover parentID={F9A35511-7E2F-4fe4-B97F-E90604B0897B}]
          Is the channel in edge counter mode or multiede detection or
          notifications are enabled?
          [/cover] */
          if ((LocalIcuChanPtr->IcuProperties.MeasurementMode
                  == (uint32) ICU_17_TIMERIP_MODE_EDGE_COUNTER) ||
          (((ICU_CHNL_MULTIEDGE_STAT_MASK | ICU_CHNL_NOTIF_PRESENCE_MASK) &
                                            *GlbIndexStatusPtr) != 0U))
          {
            /* [cover parentID={E3FF0A5D-4EE3-4504-8A09-594AA236B3B3}]
            Clear the GPT12 timer clear flag
            [/cover] */
            TxClearFlag = ICU_FLAG_RESET;
          }
          else
          {
            /* [cover parentID={A54552B0-9D9B-4b8c-95CF-C4AE2793EFE3}]
            Set the GPT12 timer clear flag
            [/cover] */
            TxClearFlag = ICU_FLAG_SET;
          }
          /* [cover parentID={57B8433B-03EE-40bb-B847-4AD13232123F}]
          Set the GPT12 register for the new edge type and clear timer as per
          the flag
          [/cover] */
          Icu_lGpt12SetActivationCondition(CellUsed, Activation, TxClearFlag);
          /* [cover parentID={20C425CE-1A16-471b-9722-8DC9B2C05603}]
          Exit critical section
          [/cover] */
          SchM_Exit_Icu_17_TimerIp_SetActivationCondition();
          #endif
          break;
      }
      /* [cover parentID={E64DF6B8-53BC-44f3-B536-24E9C926EE14}]
       Update Edge in Channel status variable
       [/cover] */
      Mcal_SetBitAtomic(GlbIndexStatusPtr, ICU_CHNL_EDGE_POS,
                        ICU_CHNL_EDGE_BIT_LENGTH, (uint32 )Activation);
      /* Set channel state to IDLE */
      /* [cover parentID={0BD2DBC6-9646-483e-B341-EB912AF42C6D}]
       Set channel state to IDLE
       [/cover] */
      Mcal_SetBitAtomic(GlbIndexStatusPtr, ICU_CHNL_STATUS_POS,
          ICU_CHNL_STATUS_BIT_LENGTH, (uint32 )ICU_17_TIMERIP_IDLE);
    }
  }
  /* [cover parentID={5D0F49AF-3538-4586-9878-04FB9654D8D1}]
   ICU Interrupt Control Registers.
   [/cover] */
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer GlbIndexStatusPtr is
   * accessed using assembly instruction. */
  /* MISRA2012_RULE_2_2_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the variable GlbIndexStatusPtr is
   * accessed using assembly instruction. */
}/* End of function Icu_17_TimerIp_SetActivationCondition */
#if (ICU_17_TIMERIP_SET_MODE_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {F23F5A46-AE69-4295-AACF-4B9165AAE53D}]     **
**                                                                            **
** Syntax : void Icu_17_TimerIp_SetMode(const Icu_17_TimerIp_ModeType Mode)   **
**                                                                            **
** Description : Service for ICU mode selection                               **
**               1.This service will set the operation mode to the given mode **
**                 parameter.                                                 **
**               2.In ICU_17_TIMERIP_MODE_NORMAL mode all notifications are   **
*                  available as configured and selected by the                **
*                  Icu_17_TimerIp_DisableNotification                         **
**                 and Icu_17_TimerIp_EnableNotification services before or   **
**                 after the call of Icu_17_TimerIp_SetMode.                  **
**               3.In ICU_17_TIMERIP_MODE_SLEEP mode only those notifications **
**                 are available which are configured as wake-up capable and  **
**                 that are not disabled via service .                        **
**                 Icu_17_TimerIp_DisableWakeup All other interrupts are      **
**                 disabled                                                   **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x02                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Non Reentrant                                            **
**                                                                            **
** Parameters (in):  Mode : ICU_17_TIMERIP_MODE_NORMAL or                     **
**                          ICU_17_TIMERIP_MODE_SLEEP                         **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={8F04E18D-D28A-48c4-AF5F-42751A7C4910}]
Safety Properties
[/cover]*/
void Icu_17_TimerIp_SetMode(const Icu_17_TimerIp_ModeType Mode)
{
  /* Local pointers */
  #if (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr; /* ROM pointer */
  uint32* GlbIndexStatusPtr;
  Icu_17_TimerIp_ChannelType Channel;
  #endif
  /* Verify any error is there for DET */
  uint32 ErrorFlag = ICU_ERROR_NOT_FOUND;
  Icu_17_TimerIp_ModeType PrevMode;
  uint8 CoreId;

  /* Get core id which is executing currently */
  CoreId = (uint8)(Mcal_GetCpuIndex());

  /* [cover parentID={22872266-EF25-4104-AAF7-E5744019612A}]
   DET or Safety is enabled
   [/cover] */
  /* STATIC CHECK: if DET or Safety error reporting is enabled */
  #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={BFF7EB69-1A24-4627-B12B-231A964D8651}]
  Check if the ICU is initialized.
  [/cover] */
  ErrorFlag = Icu_lInitCallVerify(ICU_17_TIMERIP_SID_SETMODE, CoreId);
  /* [cover parentID={D343F742-5266-4c9e-99A2-A776D243C027}]
  Any DET occured
  [/cover] */
  /* Check if there are any previous errors */
  if (ErrorFlag != ICU_ERROR_FOUND)
  #endif
  {
    /* STATIC CHECK: if DET or Safety error reporting is enabled */
    #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
    (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
    /* [cover parentID={98D1F5F2-1AA1-488e-87FA-7335DC6ECA78}]
    Check for invalid mode
    [/cover] */
    if (!((Mode == ICU_17_TIMERIP_MODE_NORMAL) || \
          (Mode == ICU_17_TIMERIP_MODE_SLEEP)))
    {
      /* [cover parentID={531CA155-FFF6-458a-B343-C4E5068F64B8}]
      Report an error to indicate that mode is invalid.
      [/cover] */
      Icu_lReportError(
        ICU_17_TIMERIP_SID_SETMODE,
        ICU_17_TIMERIP_E_PARAM_MODE);
    }
    else
    #endif
    {
      /* Read Current mode */
      PrevMode = Icu_17_TimerIp_Varlist[CoreId]->GlobalMode;
      /* [cover parentID={29EFB1B3-4D34-4d73-8800-C5EF88AFBE7A}]
      if a mode change is required
      [/cover] */
      /* Proceed only if a mode change is required */
      if (PrevMode != Mode)
      {
        /* For entering Sleep mode no channel should be active */
        /* [cover parentID={11A6267F-F1C2-47ba-8CEC-469163756BD0}]
        If the requested mode is SLEEP.
        [/cover] */
        if (Mode == ICU_17_TIMERIP_MODE_SLEEP)
        {
          /* [cover parentID={8F110A1D-F91E-469e-B887-94EB3E684F06}]
          Check if any channel is in active state.
          [/cover] */
          ErrorFlag = Icu_lSetModeBusyCheck(CoreId);
        }/* (Mode == ICU_17_TIMERIP_MODE_SLEEP) */
        /* [cover parentID={00792162-27FE-4d6b-A636-5EFCDE870DA1}]
        Check if there are any previous errors
        [/cover] */
        if (ErrorFlag != ICU_ERROR_FOUND)
        {
          #if (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
          /* Read the pointers for the core */
          /* Read Channel Status Flags pointer */
          GlbIndexStatusPtr =
            (Icu_17_TimerIp_Varlist[CoreId]->GlbIndexStatusBasePtr);
          /* Read Global channel RAM pointer */
          LocalIcuChanPtr =
            (Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->ChannelConfigPtr);
          /* Put the channels in SLEEP/Normal mode */
          /* Check if the mode is sleep */
          /* [cover parentID={1B1A0CA9-1620-48ba-BD40-21C35815CCC9}]
          Is SLEEP mode requested?
          [/cover] */
          if (Mode == ICU_17_TIMERIP_MODE_SLEEP)
          {
            /* Update the mode */
            /* [cover parentID={33F7E966-5C75-4a21-9A19-E23714793EC1}]
            Update the current mode to Sleep mode.
            [/cover] */
            Icu_17_TimerIp_Varlist[CoreId]->GlobalMode = \
                ICU_17_TIMERIP_MODE_SLEEP;
          }
          /* Loop for all the channels */
          for (Channel = (Icu_17_TimerIp_ChannelType) 0;
               Channel
               < (Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->MaxChannelCore);
               Channel = Channel + 1U)
          {
            /* [cover parentID={D85328F7-0869-43da-BF1B-3D7B546F5210}]
            Is the chnnel in Edge detect mode?
            [/cover] */
            /* Channels in Signal Edge Detection mode will be effected */
            if ((uint32) ICU_17_TIMERIP_MODE_SIGNAL_EDGE_DETECT
                == (LocalIcuChanPtr[Channel].IcuProperties.MeasurementMode))
            {
              /* Check if the mode is sleep */
              /* [cover parentID={6B77B6FC-0D23-432e-9C38-1230948F8010}]
              Is SLEEP mode requested?
              [/cover] */
              if (Mode == ICU_17_TIMERIP_MODE_SLEEP)
              {
                /* [cover parentID={62057183-86B8-4e4e-9AD2-509019384C37}]
                Put channel to SLEEP mode.
                [/cover] */
                Icu_lChannelToSleep(
                  &(LocalIcuChanPtr[Channel]),
                  &(GlbIndexStatusPtr[Channel]),
                  CoreId);
              }
              /* Normal mode */
              /* [cover parentID={33AB479C-6AD0-461d-B6B4-93170971BF46}]
              Is NORMAL mode requested?
              [/cover] */
              else
              {
                /* [cover parentID={739EFC2C-18B0-45ff-B235-E3E7CB70BF95}]
                Put channel in NORMAL mode.
                [/cover] */
                Icu_lChannelToNormal(
                  &(LocalIcuChanPtr[Channel]),
                  &(GlbIndexStatusPtr[Channel]),
                  CoreId);
              }
            }/* Mode other than edge detect can not be wake up capable */
            else
            {
              /* Nothing to do */
            }
          }/* Loop for all channels with respect to core */
          #endif
          /* Clear old wakeup info if the mode is sleep */
          /* [cover parentID={ABFCF872-8494-40a2-88C7-BC0ED00FA2CE}]
          Is SLEEP mode requested?
          [/cover] */
          if (Mode == ICU_17_TIMERIP_MODE_SLEEP)
          {
            /* [cover parentID={C43B7336-216F-464c-8177-7C94053B83AC}]
            Reset the wakeup channel info while entering SLEEP mode.
            [/cover] */
            #if (ICU_17_TIMERIP_REPORT_WAKEUP_SOURCE == STD_ON)
            Icu_17_TimerIp_Varlist[CoreId]->WakeupChannelInfo = 0U;
            #endif
          }
          else
          {
            /* Do nothing */
          }
          /* [cover parentID={EDA030EB-91CB-433b-8368-9C001DD4789C}]
          Update the current mode to requested mode.
          [/cover] */
          Icu_17_TimerIp_Varlist[CoreId]->GlobalMode = Mode;
        }/* No Error */
      }/* Same mode */
      else
      {
        /* Nothing to do */
      }
    }
  }
  /* [cover parentID={5D0F49AF-3538-4586-9878-04FB9654D8D1}]
   ICU Interrupt Control Registers.
   [/cover] */
}
#endif
/* end of #if (ICU_17_TIMERIP_SET_MODE_API == STD_ON) */

#if (ICU_17_TIMERIP_DE_INIT_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {D2D00A54-139F-4805-B53E-DAA1BAE8364D}]     **
**                                                                            **
** Syntax : void Icu_17_TimerIp_DeInit(void)                                  **
**                                                                            **
** Description : Service for ICU De-Initialization                            **
**               1.After the call of this service, the state of the used      **
**                 peripherals/registers will set to power on reset state.    **
**               2. This service will disable all used interrupts and         **
**                  notifications.                                            **
**               3. This service clear all pending interrupt flags            **
**               4. All global variables will set to reset value              **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x01                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Non Reentrant                                            **
**                                                                            **
** Parameters (in):  None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={8F04E18D-D28A-48c4-AF5F-42751A7C4910}]
Safety Properties
[/cover]*/
void Icu_17_TimerIp_DeInit(void)
{
  /* Local pointers */
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr; /* ROM pointer */
  uint32* GlbIndexStatusPtr;
  /* Local variables */
  #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  uint32 ErrorFlag;
  #endif
  uint32 IcuOption;
  #if (ICU_17_TIMERIP_CCU6_USED == STD_ON)
  uint32 TimerId; /* To hold CCU TimerID */
  #endif
  #if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) ||\
  (ICU_17_TIMERIP_CCU6_USED == STD_ON) \
  ||(ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON)
  uint16 CellUsed;
  #endif
  Icu_17_TimerIp_ChannelType Channel;
  #if (ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON)
  uint8 EruEicrChannel;
  uint8 OguOutPut;
  #endif
  uint8 CoreId;
  /* Get core id which is executing currently */
  CoreId = (uint8)(Mcal_GetCpuIndex());
  /* [cover parentID={C3AFCC4A-D6CB-43bf-8B4E-C8BAF7184553}]
  DET or Safety is enabled
  [/cover] */
  #if ((ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON))
  /* [cover parentID={6EF5E682-A919-4e65-876B-107C54A9F4C5}]
  Check for DET of the API and check if all slave cores are de-initialised
  for master core.
  [/cover] */
  ErrorFlag = Icu_lDeInitDetCheck(CoreId);
  /* [cover parentID={A3CE3EC5-1F5A-4b7c-8F85-4C2EC02B96EE}]
  Any DET occured
  [/cover] */
  if (ICU_ERROR_FOUND != ErrorFlag)
  #endif
  {
    /* [cover parentID={DA4C6A56-5125-4ad9-8235-EBE3AE6DE420}]
    Set the status to indicate the de-initialization has started.
    [/cover] */
    /* Set the Status to indicate that Deinitialization has started */
    Mcal_SetBitAtomic(&Icu_17_TimerIp_InitStatus, \
            (sint32) (CoreId * ICU_INIT_STAUS_SIZE), ICU_INIT_STAUS_SIZE, \
            (uint32) (ICU_DEINITPENDING));
    /* [cover parentID={20EDEEC5-4B3B-4407-9953-EF482063E33D}]
    Is the core configuration available?
    [/cover] */
    if(NULL_PTR != Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId])
    {
      /* Initialize ICU configured channel ROM pointer */
      LocalIcuChanPtr = \
          Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->ChannelConfigPtr;
      /* Read Channel Status Flags pointer */
      GlbIndexStatusPtr =
        (Icu_17_TimerIp_Varlist[CoreId]->GlbIndexStatusBasePtr);
      /* [cover parentID={D2C76C81-6D87-4415-AF7B-A0E2E9FABD1D}]
      Deinit the configured channels, registers , variables etc
      [/cover] */
      /* Run the for loop for all the channels */
      for (Channel = (Icu_17_TimerIp_ChannelType) 0;
           /* [cover parentID={FDFF2DB1-96CF-4830-A09A-DB0C3E379514}]
           Loop till the last channel of the core.
           [/cover] */
           Channel < \
           Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->MaxChannelCore;
           Channel = Channel + 1U)
      {
        /* [cover parentID={795C3E46-F8AB-4e88-9F62-4EF34ED0E8A9}]
        Deinit the configured channels, registers , variables.
        [/cover] */
        #if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) || \
        (ICU_17_TIMERIP_CCU6_USED == STD_ON) \
        ||(ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON)
        /* Extract the actual cell number */
        CellUsed = (uint16)LocalIcuChanPtr[Channel].IcuProperties.AssignedHwUnitNumber;
        #endif
        /* Depending on ICU option take action */
        IcuOption = (uint32) LocalIcuChanPtr[Channel].IcuProperties.AssignedHwUnit;
        /* Work on depending on ICU option chosen for each channel */
        /* [cover parentID={795C3E46-F8AB-4e88-9F62-4EF34ED0E8A9}]
        Deinit the configured channels, registers , variables.
        [/cover] */
        switch (IcuOption)
        {
          /* [cover parentID={6AC0D520-B834-4fb7-9AEF-A6225AAE9C03}]
          If chosen ICU option is GTM
          [/cover] */
          case ICU_17_TIMERIP_GTM_OPTION:
            /* [cover parentID={E469AC37-59A6-489d-B1BF-9C3478B231FC}]
            Deinitialize GTM TIM channel
            [/cover] */
            #if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
            /* Call the MCU GTM DeInit API */
            Mcu_17_Gtm_TimChannelDeInit(
              (uint8)((CellUsed / ICU_GTM_CHANNELS_PER_TIM_MODULE) \
                      & ICU_GTM_MODULE_NO_MSK),
              (uint8)(CellUsed % ICU_GTM_CHANNELS_PER_TIM_MODULE));
            #endif
            break;
          /* [cover parentID={E5789463-A7AE-4587-A2BF-0C53D47882D2}]
          If chosen ICU option is CCU
          [/cover] */
          case ICU_17_TIMERIP_CCU_OPTION:
            #if (ICU_17_TIMERIP_CCU6_USED == STD_ON)
            /* Timer ID depends on Kernel used and Comparator used.
             * For ICU only T12 is used*/
            /* [7:0] Kernel  [15:8] T12/T13  [23:16] Comparator */
            TimerId = ((uint32)CellUsed & ICU_CCU_GET_KERNEL);
            TimerId |= (((uint32)CellUsed & ICU_CCU_GET_COMPARATOR) <<
                        (ICU_MCU_CCU_COMPARATOR_POS - ICU_CCU_NIBBLE_SIZE));
            /* De-Initialize channel configured for CCU6 */
            /* [cover parentID={34C70930-B32D-413e-9468-F67E7871D1A9}]
            De-Initialize channel configured for CCU6
            [/cover] */
            Mcu_17_Ccu6_TimerDeInit(TimerId);
            #endif
            break;
          /* [cover parentID={64AA888E-B369-40d4-8B9C-30E28A42D94C}]
          If chosen ICU option is ERU
          [/cover] */
          case ICU_17_TIMERIP_ERU_OPTION:
            #if (ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON)
            /* Extract proper Eru Line */
            /*  ERU assigned hardware number is stored as follows
             Bits : 0-2 (3 bits)  ERS number
             Bits : 3-5 (3 bits) Input eru line number
             Bits : 6-8 (3 bits) OGU number  */
            /* To know which EICR to be used */
            EruEicrChannel = (uint8)(CellUsed & ICU_ERU_CHNL_MASK);
            OguOutPut = (uint8)((CellUsed >> ICU_ERU_OGU_CHNL_BIT_POS) &
                                ICU_ERU_CHNL_MASK);
            /* Deinit control register depending on ERU line used */
            /* [cover parentID={E5BEDC77-4DFE-4df7-AF9C-C078477C5A5D}]
            Deinit control register depending on ERU line used
            [/cover] */
            Icu_lDeInitEru(EruEicrChannel, OguOutPut);
            /* This service will disable notifications */
            /* [cover parentID={02F41463-986C-4ebb-9CDF-2D0E80CEF2AB}]
            Clear pending interrupts.
            [/cover] */
            MODULE_SCU.FMR.U = ((uint32)1UL) <<
                               (EruEicrChannel + ICU_ERU_FCSTART);
            #endif
            break;
          default:
            /* [cover parentID={A4582619-1866-4627-97C5-20CD0DA2E7C2}]
            De-Initialize channel configured for GPT12
            [/cover] */
            #if (ICU_17_TIMERIP_GPT12_USED == STD_ON)
            /* Initialize channel configured for GPT12 */
            Mcu_17_Gpt12_TimerDeInit( (Mcu_17_Gpt12_TimerChIdentifierType)\
                (LocalIcuChanPtr[Channel].IcuProperties.AssignedHwUnitNumber) \
                    & ICU_LOWER_NIBBLE);
            #endif
            break;
        }/* End of switch */
        /* clear GlbIndexStatus to clear all the flags */
        /* [cover parentID={3199944D-8AFB-4687-9D4F-18CFA0CE16C2}]
        Clear all channel flags.
        [/cover] */
        GlbIndexStatusPtr[Channel] = 0U;
      }/* End of for loop within Icu_17_TimerIp_DeInit() function */
    }
    /* [cover parentID={0B10D349-66B7-4a69-A6AB-19FC61C6A77B}]
    Master Core Specific De-Initializations.
    [/cover] */
    /* [cover parentID={8AB8A55A-F036-4a2d-83D9-26A0DD115742}]
    Is Master Core?
    [/cover] */
    if(CoreId == MCAL_MASTER_COREID)
    {
      /* [cover parentID={28CE65B3-7E53-40cf-A70D-B0D60212B201}]
      Stop CCU6 Kernel 0 T12.
      [/cover] */
      #if (ICU_17_TIMERIP_CCU6_KERNEL0_USED == STD_ON)
      Mcu_17_Ccu6_TimerStop(MCU_CCU6_KERNEL_0);
      #endif
      /* [cover parentID={F4B6FE6A-A89E-4308-B7DF-A3FA595D0BB4}]
      Stop CCU6 Kernel 1 T12.
      [/cover] */
      #if (ICU_17_TIMERIP_CCU6_KERNEL1_USED == STD_ON)
      Mcu_17_Ccu6_TimerStop(MCU_CCU6_KERNEL_1);
      #endif
    }
    /* [cover parentID={C83EA849-AF0A-4b6c-85E6-EB13FCC7B25C}]
    Set the status to indicate the de-initialization is done
    [/cover] */
    Mcal_SetBitAtomic(&Icu_17_TimerIp_InitStatus, \
        (sint32) (CoreId*ICU_INIT_STAUS_SIZE), ICU_INIT_STAUS_SIZE, \
        (uint32) (ICU_DEINITIALIZED));

  }/* Error not found */
  return;
  /* [cover parentID={5D0F49AF-3538-4586-9878-04FB9654D8D1}]
    ICU Interrupt Control Registers.
  [/cover] */
}/* End of Icu_17_TimerIp_DeInit() function */
#endif

#if (ICU_17_TIMERIP_GET_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {078E02BB-1529-4125-AB09-69BB4BA3C13A}]     **
**                                                                            **
** Syntax :          void Icu_17_TimerIp_GetVersionInfo (                     **
**                          Std_VersionInfoType* const versioninfo)           **
**                                                                            **
** Description : 1. This service will return the version infos of ICU driver  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x12                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant                                                **
**                                                                            **
** Parameters (in):  None                                                     **
**                                                                            **
** Parameters (out): versioninfo : Pointer to hold the version values         **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={8F04E18D-D28A-48c4-AF5F-42751A7C4910}]
Safety Properties
[/cover]*/
void Icu_17_TimerIp_GetVersionInfo(Std_VersionInfoType* const versioninfo)
{
  /* [cover parentID={BD02CED9-FEF3-4203-8ED4-21CF31DE7B9A}]
  Icu_17_TimerIp_GetVersionInfo
  [/cover] */
  /* [cover parentID={5DD02537-91CB-4c29-A12E-DE9C68D60D87}]
  DET or safety is enabled.
  [/cover] */
  #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  /* Check if the passed parameter is a NULL_PTR. */
  /* [cover parentID={7907A9D3-AA86-4172-890E-E641CA0E461C}]
  Is the passed pointer valid?
  [/cover] */
  if (versioninfo == NULL_PTR)
  {
    /* [cover parentID={3C9B6EEF-97CD-482f-89E8-18FE885AE8BC}]
    Report an error to indicate wrong pointer parameter.
    [/cover] */
    /* Issue a DET/Safety Error */
    Icu_lReportError(
      ICU_17_TIMERIP_SID_GETVERSIONINFO,
      ICU_17_TIMERIP_E_PARAM_VINFO);/* End of report to  DET/Safety */
  }
  else
  #endif
  {
    /* [cover parentID={8C7621FF-8FAB-4c12-B16C-BD2F19D37BBB}]
    Update vendor ID, module ID, SW major, SW minor and SW patch version
    values in the pointer parameter.
    [/cover] */
    /* Get ICU Vendor ID */
    versioninfo->vendorID = ICU_17_TIMERIP_VENDOR_ID;
    /* Get ICU Module ID */
    versioninfo->moduleID = ICU_17_TIMERIP_MODULE_ID;
    /* Get ICU module Software major version */
    versioninfo->sw_major_version = (uint8)ICU_17_TIMERIP_SW_MAJOR_VERSION;
    /* Get ICU module Software minor version */
    versioninfo->sw_minor_version = (uint8)ICU_17_TIMERIP_SW_MINOR_VERSION;
    /* Get ICU module Software patch version */
    versioninfo->sw_patch_version = (uint8)ICU_17_TIMERIP_SW_PATCH_VERSION;
  }
  /* [cover parentID={5D0F49AF-3538-4586-9878-04FB9654D8D1}]
    ICU Interrupt Control Registers.
  [/cover] */
}/* End of Icu_17_TimerIp_GetVersionInfo*/

#endif
/* (ICU_GET_VERSION_INFO_API == STD_ON) */

#if (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) || \
(ICU_17_TIMERIP_GPT12_USED == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {F015F87D-1E17-4827-9447-C1A765584B25}]     **
**                                                                            **
** Syntax : void Icu_17_TimerIp_EnableMultiEdgeDetection(                     **
**                                const Icu_17_TimerIp_ChannelType Channel    **
**                                const uint32 EdgeCount)                     **
**                                                                            **
** Description : This service will Re enables the ICU signal edge detection   **
**               channel, activation edge depends on either DefaultStartEdge  **
**               Or activation by Icu_17_TimerIp_SetActivationCondition API.  **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x19                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                   EdgeCount - Number of edges before interrupt occurs      **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={8F04E18D-D28A-48c4-AF5F-42751A7C4910}]
Safety Properties
[/cover]*/
void Icu_17_TimerIp_EnableMultiEdgeDetection(
  const Icu_17_TimerIp_ChannelType Channel,
  const uint32 EdgeCount)
{
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr; /* ROM pointer */
  uint32* GlbIndexStatusPtr;
  uint16 CellUsed;
  uint8 CoreChIndex;
  uint32 IcuOption;
  #if (ICU_17_TIMERIP_GPT12_USED == STD_ON) && \
  (ICU_17_TIMERIP_EDGE_DETECT_API ==STD_ON)
  uint8 ChIndex;
  uint32* MultiEdgeCountPtr;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * MISRA rule,To implement efficiently IcuMeasaurementProperty as a post-build
   * parameter.Union is required*/
  Icu_17_TimerIp_ChannelData *ChnlDataPtr;
  #endif
  #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  uint32 ErrorFlag;
  #endif
  uint8 CoreId;

  /* Get core id which is executing currently */
  CoreId = (uint8)(Mcal_GetCpuIndex());
  /* [cover parentID={CB0E8775-1E0B-46ae-B168-B877B44E18E0}]
  DET or Safety is enabled
  [/cover] */
  #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  CoreChIndex = 0;
  LocalIcuChanPtr = NULL_PTR;
  /* Verify any error is there for DET */
  /* [cover parentID={FD16B213-474A-44af-87A9-8877242CD4C3}]
  Preconditions check, sleep mode check and channel validation
  [/cover] */
  ErrorFlag = Icu_lNotifiDetCheck(Channel,
                                  ICU_17_TIMERIP_SID_ENABLEMULTIEDGEDETECTION,
                                  ICU_17_TIMERIP_MODE_SIGNAL_EDGE_DETECT,
                                  CoreId, ICU_FLAG_SET);
  /* [cover parentID={5F959E04-3C09-4fd1-B3BA-5CED1457316C}]
  Any DET reported
  [/cover] */
  if (ICU_ERROR_FOUND != ErrorFlag)
  {
    CoreChIndex = Icu_lGetCoreChIndex((uint8)Channel);
    LocalIcuChanPtr = &((Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->
                                                ChannelConfigPtr)[CoreChIndex]);
    /* [cover parentID={1025FF81-42A0-40e7-9489-20DC10AD81FE}]
    Input parameter check
    [/cover] */
    ErrorFlag = Icu_lEnableMultiEdgeDetCheck(LocalIcuChanPtr, EdgeCount);
  }
  /* [cover parentID={5FC5414B-1295-48fa-AC1C-D427B43A8FB8}]
  Any error occured?
  [/cover] */
  if (ICU_ERROR_FOUND != ErrorFlag)
  #else
  CoreChIndex = Icu_lGetCoreChIndex((uint8)Channel);
  LocalIcuChanPtr = &((Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->
                                              ChannelConfigPtr)[CoreChIndex]);
  /* Check if the mode is valid */
  /* [cover parentID={967907D1-948D-41a6-BD1E-527FA7396878}]
  If measurement mode is edge detect
  [/cover] */
  if (LocalIcuChanPtr->IcuProperties.MeasurementMode
      == (uint32)ICU_17_TIMERIP_MODE_SIGNAL_EDGE_DETECT)
  #endif
    /* (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) ||
     * (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON) */
  {
    /* Extract channel flags variable address */
    GlbIndexStatusPtr =
        &((Icu_17_TimerIp_Varlist[CoreId]->GlbIndexStatusBasePtr)[CoreChIndex]);
    CellUsed =
      (Icu_17_TimerIp_ChannelType)LocalIcuChanPtr->IcuProperties.
      AssignedHwUnitNumber;
    /* Change channel status to IDLE */
    Mcal_SetBitAtomic( \
                       GlbIndexStatusPtr, (sint32)ICU_CHNL_STATUS_POS, \
                       ICU_CHNL_STATUS_BIT_LENGTH, (uint32)ICU_17_TIMERIP_IDLE);
    /* Depending on ICU option take action */
    IcuOption = (uint32)LocalIcuChanPtr->IcuProperties.AssignedHwUnit;
    switch(IcuOption)
    {
      /* [cover parentID={EFF72643-7D6E-4d9c-A585-CA92084A8A57}]
      If ICU option is GTM
      [/cover] */
      case ICU_17_TIMERIP_GTM_OPTION:
        /* Enable GTM for multi edge detection */
        /* [cover parentID={49E2B9C8-48C4-4c63-B372-78A02568160A}]
        Start multi edge detect
        [/cover] */
        #if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) && \
        (ICU_17_TIMERIP_EDGE_DETECT_API ==STD_ON)
        Icu_lGtmStartMultiEdgeDetect(CellUsed, EdgeCount);
        #endif
        break;
      /* [cover parentID={7E73BBFD-E28E-48be-8198-49C9D5B9F030}]
      If ICU option is GPT12
      [/cover] */
      default:
        /* ICU_17_TIMERIP_GPT12_OPTION */
        #if (ICU_17_TIMERIP_GPT12_USED == STD_ON) && \
        (ICU_17_TIMERIP_EDGE_DETECT_API ==STD_ON)
        ChIndex = LocalIcuChanPtr->ModeMappingIndex;
        ChnlDataPtr =
            &((Icu_17_TimerIp_Varlist[CoreId]->ChannelDataBasePtr)[ChIndex]);
        MultiEdgeCountPtr = &(ChnlDataPtr->EdgeDetectParas.EdgeDetectCount);
        /* [cover parentID={A2FA19DE-19DF-40af-A078-3A94EC4AA8BE}]
        Store the edge count value for use in ISR
        [/cover] */
        /* Store the edge count value for use in ISR */
        *MultiEdgeCountPtr = (uint16)EdgeCount;
        /* GPT12 start multi edge detection */
        /* [cover parentID={026F7983-D5A7-4314-8EAE-C7408E94CB03}]
        Start GPT12 multi edge detection.
        [/cover] */
        Icu_lGpt12StartEdgeDetect(CellUsed, (uint16)EdgeCount);
        /* [cover parentID={BC1A89C1-E4B4-4c0a-80F0-E464C2CA09A7}]
        Set GPT edge detection and multi edge status
        [/cover] */
        /* Set the Multi Edge Detection status to true*/
        Mcal_SetBitAtomic( \
          GlbIndexStatusPtr, (sint32)ICU_CHNL_MULTIEDGE_STAT_POS,\
          ICU_CHNL_MULTIEDGE_STAT_BIT_LENGTH, (uint32)1);
        /* Set the GPT Edge Detection status to true. */
        Mcal_SetBitAtomic( \
          GlbIndexStatusPtr, (sint32)ICU_CHNL_ERU_GPT_SIGEDGE_STATUS_POS,\
          ICU_CHNL_ERU_GPT_SIGEDGE_STATUS_BIT_LENGTH, (uint32)1);
#endif
        break;
    }
    /* [cover parentID={205D5795-1534-47f6-A5E8-6A6DB9361FED}]
    Set channel status to IDLE.
    [/cover] */
    Mcal_SetBitAtomic(GlbIndexStatusPtr, \
                      ICU_CHNL_STATUS_POS, ICU_CHNL_STATUS_BIT_LENGTH, \
                      (uint32)ICU_17_TIMERIP_IDLE);
  }
  /* [cover parentID={5D0F49AF-3538-4586-9878-04FB9654D8D1}]
    ICU Interrupt Control Registers.
  [/cover] */
  /* MISRA2012_RULE_2_2_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the variable GlbIndexStatusPtr is
   * accessed using assembly instruction. */
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer GlbIndexStatusPtr is
   * accessed using assembly instruction. */
}/* End of Icu_17_TimerIp_EnableEdgeDetection() function */
#endif
/*(ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) ||
(ICU_17_TIMERIP_GPT12_USED == STD_ON)*/
#endif
/*(ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)*/

#if (ICU_17_TIMERIP_INITCHECK_API == STD_ON)
/*******************************************************************************
** Traceability : [cover parentID={99229577-FAD7-49d4-9156-300E945127C9}]     **
**                                                                            **
** Syntax : Std_ReturnType Icu_17_TimerIp_InitCheck(                          **
**                const Icu_17_TimerIp_ConfigType * const ConfigPtr )         **
**                                                                            **
** Service ID      :    None                                                  **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Non-Reentrant                                         **
**                                                                            **
** Parameters (in) :    ConfigPtr - Pointer to ICU Driver configuration set   **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    :    E_OK - if initialization comparison is success        **
**                      E_NOT_OK - if initialization comparison fails         **
**                                                                            **
** Description     : This routine verifies the initialization of ICU driver.  **
**                                                                            **
*******************************************************************************/
/*[cover parentID={8F04E18D-D28A-48c4-AF5F-42751A7C4910}]
Safety Properties
[/cover]*/
Std_ReturnType Icu_17_TimerIp_InitCheck(
  const Icu_17_TimerIp_ConfigType* const ConfigPtr)
{
  Std_ReturnType ErrorFlag;
  Icu_17_TimerIp_ChannelType Channel;
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtrBase; /* ROM pointer */
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr;     /* ROM pointer */
  const uint32* GlbIndexStatusPtrBase;
  const uint32* GlbIndexStatusPtr;
  uint8 CoreId;
  uint32 IcuOption;
  uint32 ExpectedStatusValue;

  /* Get core id which is executing currently */
  CoreId = (uint8)(Mcal_GetCpuIndex());
  /* [cover parentID={C9D2F2E3-2B65-48e5-A1A0-7859226A3389}]
  Check if the input parameter is NULL
  [/cover] */
  ErrorFlag = Icu_lPreInitCheck(ConfigPtr, CoreId);
  /* Proceed only if above checks are successful */
  /* [cover parentID={7ECE7281-B32C-4e16-8E8B-E201638B68D9}]
  Is previous check passed and configuration pointer non-NULL?
  [/cover] */
  if(E_OK == ErrorFlag)
  {
    /* [cover parentID={7ECE7281-B32C-4e16-8E8B-E201638B68D9}]
    Is previous check passed and configuration pointer non-NULL?
    [/cover] */
    if(Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId] != NULL_PTR )
    {
      /* [cover parentID={788C6550-9DE9-48d8-9C57-28FFB69121BB}]
       Is ErrorFlag E_OK and Icu mode is  in  Normal mode?
       [/cover] */
      if(Icu_17_TimerIp_Varlist[CoreId]->GlobalMode == ICU_17_TIMERIP_MODE_NORMAL)
      {
        /* [cover parentID={AE89E542-20BE-481a-ABEC-95D45C9A580F}]
        Check for Reset done for all used global variables
        [/cover] */
        ErrorFlag = Icu_lResetGlobalVariablesCheck(CoreId);
      }
      else
      {
        ErrorFlag = E_NOT_OK;
      }
      /* Proceed only if above checks are successful */
      /* [cover parentID={CACD697B-201F-4df2-A1D6-E46D212EF64E}]
       Is ErrorFlag E_OK?
      [/cover] */
      if(E_OK == ErrorFlag)
      {
          /* Get the channel config base pointer */
        LocalIcuChanPtrBase = \
          (Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->ChannelConfigPtr);
        GlbIndexStatusPtrBase =
          (Icu_17_TimerIp_Varlist[CoreId]->GlbIndexStatusBasePtr);
        /* Check for all channels */
        /* [cover parentID={FF054C55-E9AC-4060-B835-891CF0464E2B}]
        Check Init for each channel
        [/cover] */
        for (Channel = (Icu_17_TimerIp_ChannelType)0;
             (Channel < \
              Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->MaxChannelCore) &&
             (ErrorFlag != E_NOT_OK);
             Channel = Channel + 1U)
        {
          LocalIcuChanPtr = &LocalIcuChanPtrBase[Channel];
          GlbIndexStatusPtr = &GlbIndexStatusPtrBase[Channel];
          /* Work on depending on ICU option chosen for each channel */
          IcuOption = (uint32) LocalIcuChanPtr->IcuProperties.AssignedHwUnit;
          switch (IcuOption)
          {
            /* [cover parentID={96B4FBA8-5823-4eff-9DEE-CB075F2AEF42}]
            If ICU option is GTM
            [/cover] */
            case ICU_17_TIMERIP_GTM_OPTION:
              #if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
              /* [cover parentID={43EEC07A-F19D-424f-B23D-4F9DBB66DC22}]
              Check for GTM Init
              [/cover] */
              ErrorFlag = Icu_lGtmChannelInitCheck(LocalIcuChanPtr);
              #endif
              break;
            /* [cover parentID={B07488B9-97BF-44d3-94B6-BEB108829F8F}]
            If ICU option is CCU6
            [/cover] */
            case ICU_17_TIMERIP_CCU_OPTION:
              #if (ICU_17_TIMERIP_CCU6_USED == STD_ON)
              /* [cover parentID={1CE5BC3A-DFF6-4449-B7D6-87AAB68015D8}]
              Check for CCU Harware Init
              [/cover] */
              ErrorFlag = Icu_lCcu6ChannelInitCheck(LocalIcuChanPtr);
              #endif
              break;
            /* [cover parentID={870F42FA-7BA5-436f-812F-8A19A7F23D9C}]
            If ICU option is ERU
            [/cover] */
            case ICU_17_TIMERIP_ERU_OPTION:
              #if (ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON)
              /* [cover parentID={DAB59F9D-C7B0-44e6-B25F-3CBAA567A407}]
               Check for ERU Harware Init
              [/cover] */
              ErrorFlag = Icu_lEruInitCheck(LocalIcuChanPtr);
              #endif
              break;
            /* [cover parentID={F78EC1FD-4E90-4dc8-9377-233F851AADE3}]
            If ICU option is GPT12
            [/cover] */
            default:
              #if (ICU_17_TIMERIP_GPT12_USED == STD_ON)
              /* [cover parentID={FF905972-4A9A-49eb-A0B6-509F607CAE9A}]
              Check for GPT12 Harware Init
              [/cover] */
              ErrorFlag = Icu_lGpt12InitCheck(LocalIcuChanPtr);
              #endif
              break;
          }
          /* [cover parentID={3FC7E76E-8CFB-4fb2-B6D5-B6AECCBFC48A}]
          Is configured edge for channel for current core not the
          default edge and is Error Flag not E_NOT_OK?
          [/cover] */
          if(ErrorFlag != E_NOT_OK)
          {
            ExpectedStatusValue = Icu_lChannelStatusCheckValue(LocalIcuChanPtr);
            if(*GlbIndexStatusPtr != ExpectedStatusValue)
            {
              ErrorFlag = E_NOT_OK;
            }
          }
        }
      }
    }
  }
  return ErrorFlag;
}
#endif
/*#if (ICU_17_TIMERIP_INITCHECK_API == STD_ON)*/

#if (ICU_17_TIMERIP_INCREMENTAL_INTERFACE_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={01129404-A6F1-4050-AEA2-C129B6FBBC14}]      **
**                                                                            **
** Syntax : void Icu_17_TimerIp_StartIncInterface(                            **
**                                const  Icu_17_TimerIp_ChannelType Channel)  **
**                                                                            **
** Description : Starts the incremental interface mode activities.            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x21                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={8F04E18D-D28A-48c4-AF5F-42751A7C4910}]
Safety Properties
[/cover]*/
void Icu_17_TimerIp_StartIncInterface(const Icu_17_TimerIp_ChannelType Channel)
{
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr; /* ROM pointer */
  uint16 CellUsed;
  uint8 CoreChIndex;
  uint8 CoreId;
  uint32* GlbIndexStatusPtr;
  /* Get core id which is executing currently */
  CoreId = (uint8)(Mcal_GetCpuIndex());
  /* [cover parentID={EE1BAF46-ABA4-4e01-8EF8-BBD959795561}]
  DET or Safety is enabled
  [/cover] */
#if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON)|| \
    (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  /* Verify any error is there for DET */
  uint32 ErrorFlag;
  /* [cover parentID={3AE2F9BB-17AC-4378-ABBC-BDB9F726EC8D}]
  Preconditions check, sleep mode check and channel validation
  [/cover] */
  /* Verify any error is there for DET */
  ErrorFlag = Icu_lNotifiDetCheck(Channel,
      ICU_17_TIMERIP_SID_START_INC_INTERFACE,
      ICU_17_TIMERIP_MODE_INCREMENTAL_INTERFACE,
      CoreId, ICU_FLAG_SET);
  /* [cover parentID={781A98E9-57EE-4521-B8ED-5FCBD922E095}]
  Any DET reported ?
  [/cover] */
  if (ICU_ERROR_FOUND != ErrorFlag)
#endif
  {
    CoreChIndex = Icu_lGetCoreChIndex((uint8)Channel);
    /* Initialize ICU configured channel ROM pointer */
    LocalIcuChanPtr = &((Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->
                                                ChannelConfigPtr)[CoreChIndex]);
#if ((ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_OFF) && \
    (ICU_17_TIMERIP_SAFETY_ENABLE == STD_OFF))
    /* Check if the mode is valid */
    /* [cover parentID={9810C0B2-1B7A-4912-8238-8177236AAB07}]
    Is the channel in Incremental INterface Mode
    [/cover] */
    if (LocalIcuChanPtr->IcuProperties.MeasurementMode
        == (uint32)ICU_17_TIMERIP_MODE_INCREMENTAL_INTERFACE)
#endif
    {
      /* Extract the address to the channel status */
      GlbIndexStatusPtr =
        &((Icu_17_TimerIp_Varlist[CoreId]->GlbIndexStatusBasePtr)[CoreChIndex]);
      /* Check if the incremental interface has already started */
      /* [cover parentID={98B5F5BB-E154-4dfc-AE18-CED24166582F}]
      Is channel activity started?
      [/cover] */
      if(ICU_ACTIVITY_STARTED != Mcal_GetBitAtomic(
                          *GlbIndexStatusPtr, ICU_CHNL_ACTIVITY_STARTED_POS, 1))
      {
        /* [cover parentID={E206A2DB-6A67-40e6-88E3-CB8D2D98D469}]
        Start GPT12
        [/cover] */
        /* Extract the address to the channel status */
        CellUsed = (uint16)LocalIcuChanPtr->IcuProperties.
            AssignedHwUnitNumber;
        Icu_lGpt12EnableEdgeCount(CellUsed);
        /* Set the incremental interface activity to started */
        Mcal_SetBitAtomic( \
            GlbIndexStatusPtr, (sint32)ICU_CHNL_ACTIVITY_STARTED_POS,\
            ICU_CHNL_ACTIVITY_BIT_LENGTH, (uint32)ICU_ACTIVITY_STARTED);
      }
    }
  }
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer GlbIndexStatusPtr is
   * accessed using assembly instruction. */
}
#endif
/* (ICU_17_TIMERIP_INCREMENTAL_INTERFACE_API == STD_ON) */

#if (ICU_17_TIMERIP_INCREMENTAL_INTERFACE_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={602273A3-C207-4e50-B1F2-E0CF2E8BBAF5}]      **
**                                                                            **
** Syntax : void Icu_17_TimerIp_StopIncInterface(                             **
**                                const  Icu_17_TimerIp_ChannelType Channel)  **
**                                                                            **
** Description : Stop the incremental interface mode activities.              **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x22                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={8F04E18D-D28A-48c4-AF5F-42751A7C4910}]
Safety Properties
[/cover]*/
void Icu_17_TimerIp_StopIncInterface(const Icu_17_TimerIp_ChannelType Channel)
{
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr; /* ROM pointer */
  uint16 CellUsed;
  uint8 CoreChIndex;
  uint8 CoreId;
  uint32* GlbIndexStatusPtr;
  /* Get core id which is executing currently */
  CoreId = (uint8)(Mcal_GetCpuIndex());
  /* [cover parentID={E89FFAFA-56CE-47a4-B4CA-2FD4BB65B1A0}]
  DET or Safety is enabled
  [/cover] */
#if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON)|| \
    (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  /* Verify any error is there for DET */
  uint32 ErrorFlag;
  /* [cover parentID={A3E4BF52-BE10-4cf3-A5E9-731613B88CD1}]
  Preconditions check, sleep mode check and channel validation
  [/cover] */
  /* Verify any error is there for DET */
  ErrorFlag = Icu_lNotifiDetCheck(Channel,
      ICU_17_TIMERIP_SID_STOP_INC_INTERFACE,
      ICU_17_TIMERIP_MODE_INCREMENTAL_INTERFACE,
      CoreId, ICU_FLAG_SET);
  /* [cover parentID={BA9A8D2D-1EFD-4915-AFBE-5F3EEBFD6550}]
  Any DET reported ?
  [/cover] */
  if (ICU_ERROR_FOUND != ErrorFlag)
#endif
  {
    CoreChIndex = Icu_lGetCoreChIndex((uint8)Channel);
    /* Initialize ICU configured channel ROM pointer */
    LocalIcuChanPtr = &((Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->
                                                ChannelConfigPtr)[CoreChIndex]);
#if ((ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_OFF) && \
    (ICU_17_TIMERIP_SAFETY_ENABLE == STD_OFF))
    /* Check if the mode is valid */
    /* [cover parentID={3CE5A4E0-19BC-4c88-9E7F-E47AC323B581}]
    Is the channel in Incremental INterface Mode
    [/cover] */
    if (LocalIcuChanPtr->IcuProperties.MeasurementMode
        == (uint32)ICU_17_TIMERIP_MODE_INCREMENTAL_INTERFACE)
#endif
    {

      /* Extract the address to the channel status */
      GlbIndexStatusPtr =
        &((Icu_17_TimerIp_Varlist[CoreId]->GlbIndexStatusBasePtr)[CoreChIndex]);
      /* Check if the incremental interface has already started */
      /* [cover parentID={18776F0A-823F-4b35-8456-2C04CA482246}]
      Is channel activity started?
      [/cover] */
      if(ICU_ACTIVITY_STARTED == Mcal_GetBitAtomic(
                          *GlbIndexStatusPtr, ICU_CHNL_ACTIVITY_STARTED_POS, 1))
      {
        /* Extract the address to the channel status */
        /* [cover parentID={D46E456E-6478-4be0-8EAA-4D2FC59F85E9}]
        Stop GPT12
        [/cover] */
        CellUsed = (uint16)LocalIcuChanPtr->IcuProperties.
            AssignedHwUnitNumber;
        Icu_lGpt12DisableChannel(CellUsed);
        /* Set the incremental interface activity to stopped */
        Mcal_SetBitAtomic( \
            GlbIndexStatusPtr, (sint32)ICU_CHNL_ACTIVITY_STARTED_POS,\
            ICU_CHNL_ACTIVITY_BIT_LENGTH, 0U);
      }
    }
  }
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer GlbIndexStatusPtr is
   * accessed using assembly instruction. */
}
#endif
/* (ICU_17_TIMERIP_INCREMENTAL_INTERFACE_API == STD_ON) */

#if (ICU_17_TIMERIP_INCREMENTAL_INTERFACE_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={CA784191-BE6D-4705-9477-9E31862E5377}]      **
**                                                                            **
** Syntax : void Icu_17_TimerIp_CalibratePos(                                 **
**                                const  Icu_17_TimerIp_ChannelType Channel,  **
**                                const uint16 Position )                     **
**                                                                            **
** Description : Calibrate the start point for incremental interface mode     **
**               functionality.                                               **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x23                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                   Position - Start point to be set                         **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={8F04E18D-D28A-48c4-AF5F-42751A7C4910}]
Safety Properties
[/cover]*/
void Icu_17_TimerIp_CalibratePos( const Icu_17_TimerIp_ChannelType Channel,
    const uint16 Position)
{
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr; /* ROM pointer */
  uint16 CellUsed;
  uint8 CoreChIndex;
  uint8 CoreId;
  /* Get core id which is executing currently */
  CoreId = (uint8)(Mcal_GetCpuIndex());
  /* [cover parentID={DD809EE4-CA65-4c4b-ADFB-F1AA5AB20403}]
  DET or Safety is enabled
  [/cover] */
#if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON)|| \
    (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  /* Verify any error is there for DET */
  uint32 ErrorFlag;
  /* [cover parentID={ED8B621C-0A7C-4d14-84F8-914617390A5A}]
  Preconditions check, sleep mode check and channel validation
  [/cover] */
  /* Verify any error is there for DET */
  ErrorFlag = Icu_lNotifiDetCheck(Channel,
      ICU_17_TIMERIP_SID_CALIBRATE_POS,
      ICU_17_TIMERIP_MODE_INCREMENTAL_INTERFACE,
      CoreId, ICU_FLAG_SET);
  /* [cover parentID={4219C5F8-2010-4c6e-810B-C5BEB4A14451}]
  Any DET reported ?
  [/cover] */
  if (ICU_ERROR_FOUND != ErrorFlag)
#endif
  {
    CoreChIndex = Icu_lGetCoreChIndex((uint8)Channel);
    /* Initialize ICU configured channel ROM pointer */
    LocalIcuChanPtr = &((Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->
                                                ChannelConfigPtr)[CoreChIndex]);
#if ((ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_OFF) && \
    (ICU_17_TIMERIP_SAFETY_ENABLE == STD_OFF))
    /* Check if the mode is valid */
    /* [cover parentID={5911D0DB-3EFA-4842-A5EF-CB6D49CF5B46}]
    Is the channel mode Incremental interface?
    [/cover] */
    if (LocalIcuChanPtr->IcuProperties.MeasurementMode
        == (uint32)ICU_17_TIMERIP_MODE_INCREMENTAL_INTERFACE)
#endif
    {
      /* Extract the address to the channel status */
      /* [cover parentID={AD36E7F9-4584-4c26-A196-A2AF9077B2BF}]
      Update GPT12 counter
      [/cover] */
      CellUsed = (uint16)LocalIcuChanPtr->IcuProperties.
          AssignedHwUnitNumber;
      Icu_lGpt12SetCounter(CellUsed,Position);
    }
  }
}
#endif
/* (ICU_17_TIMERIP_INCREMENTAL_INTERFACE_API == STD_ON) */

#if (ICU_17_TIMERIP_INCREMENTAL_INTERFACE_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={345F0D7A-64CB-4e61-83AD-C5C0F8E96095}]      **
**                                                                            **
** Syntax : uint16 Icu_17_TimerIp_ReadEncCount(                               **
**                                const  Icu_17_TimerIp_ChannelType Channel)  **
**                                                                            **
** Description : read the current encoder count value                         **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x24                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     uint16: Encoder counter value                            **
**                                                                            **
*******************************************************************************/
/*[cover parentID={8F04E18D-D28A-48c4-AF5F-42751A7C4910}]
Safety Properties
[/cover]*/
uint16 Icu_17_TimerIp_ReadEncCount(const Icu_17_TimerIp_ChannelType Channel)
{
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr; /* ROM pointer */
  /* [cover parentID={9E2EE27A-1622-4a89-916F-796E6B550E70}]
  Initialize return value
  [/cover] */
  uint16 EncCount=0U;
  uint16 CellUsed;
  uint8 CoreChIndex;
  uint8 CoreId;
  /* Get core id which is executing currently */
  CoreId = (uint8)(Mcal_GetCpuIndex());
  /* [cover parentID={5D8B0CA9-6EB6-44dc-8B90-E3B506F7C11A}]
  DET or Safety is enabled
  [/cover] */
#if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON)|| \
    (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  /* Verify any error is there for DET */
  uint32 ErrorFlag;
  /* [cover parentID={A65DA5D9-10CC-4a32-BA58-776011F1A79B}]
  Preconditions check, sleep mode check and channel validation
  [/cover] */
  /* Verify any error is there for DET */
  ErrorFlag = Icu_lNotifiDetCheck(Channel,
      ICU_17_TIMERIP_SID_READ_ENC_COUNT,
      ICU_17_TIMERIP_MODE_INCREMENTAL_INTERFACE,
      CoreId, ICU_FLAG_SET);
  /* [cover parentID={249FAF15-68A5-4958-8208-E33170C24C12}]
  Any DET reported ?
  [/cover] */
  if (ICU_ERROR_FOUND != ErrorFlag)
#endif
  {
    CoreChIndex = Icu_lGetCoreChIndex((uint8)Channel);
    /* Initialize ICU configured channel ROM pointer */
    LocalIcuChanPtr = &((Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->
                                                ChannelConfigPtr)[CoreChIndex]);
#if ((ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_OFF) && \
    (ICU_17_TIMERIP_SAFETY_ENABLE == STD_OFF))
    /* Check if the mode is valid */
    /* [cover parentID={DFE9642D-3253-42ba-BFFB-EC3F5F93DAD0}]
    Is the channel in Incremental INterface Mode
    [/cover] */
    if (LocalIcuChanPtr->IcuProperties.MeasurementMode
        == (uint32)ICU_17_TIMERIP_MODE_INCREMENTAL_INTERFACE)
#endif
    {
      /* Extract the address to the channel status */
      /* [cover parentID={784EB22C-ABF1-4e74-A2A4-EB8ACB4FEE74}]
      Read GPT12 counter value
      [/cover] */
      CellUsed = (uint16)LocalIcuChanPtr->IcuProperties.
          AssignedHwUnitNumber;
      EncCount = Icu_lGpt12ReadCounter(CellUsed);
    }
  }
  return(EncCount);
}
#endif
/* (ICU_17_TIMERIP_INCREMENTAL_INTERFACE_API == STD_ON) */

#if (ICU_17_TIMERIP_INCREMENTAL_INTERFACE_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={AAC7A62B-17C7-47ff-A8C0-FD8E3ADE4AD6}]      **
**                                                                            **
** Syntax : Icu_17_TimerIp_EncCountDirType Icu_17_TimerIp_ReadEncCountDir(    **
**                                const  Icu_17_TimerIp_ChannelType Channel)  **
**                                                                            **
** Description : read the current encoder counting direcion                   **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x25                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     Icu_17_TimerIp_EncCountDirType: Counting direction       **
**                                                                            **
*******************************************************************************/
/*[cover parentID={8F04E18D-D28A-48c4-AF5F-42751A7C4910}]
Safety Properties
[/cover]*/
Icu_17_TimerIp_EncCountDirType Icu_17_TimerIp_ReadEncCountDir(
    const Icu_17_TimerIp_ChannelType Channel)
{
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr; /* ROM pointer */
  /* [cover parentID={33DD4D66-A06E-43d0-8CC9-112D6FBE2F33}]
  Initialize return value
  [/cover] */
  Icu_17_TimerIp_EncCountDirType EncDir = ICU_17_TIMERIP_ENC_COUNT_UP;
  uint16 CellUsed;
  uint8 CoreChIndex;
  uint8 CoreId;
  /* Get core id which is executing currently */
  CoreId = (uint8)(Mcal_GetCpuIndex());
  /* [cover parentID={1FA1D240-A0AA-4a8f-9117-B1E813FFEDB1}]
  DET or Safety is enabled
  [/cover] */
#if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON)|| \
    (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  /* Verify any error is there for DET */
  uint32 ErrorFlag;
  /* [cover parentID={BD085337-A1E6-4ed0-9646-991348990F3F}]
  Preconditions check, sleep mode check and channel validation
  [/cover] */
  /* Verify any error is there for DET */
  ErrorFlag = Icu_lNotifiDetCheck(Channel,
      ICU_17_TIMERIP_SID_READ_ENC_DIR,
      ICU_17_TIMERIP_MODE_INCREMENTAL_INTERFACE,
      CoreId, ICU_FLAG_SET);
  /* [cover parentID={8964D935-C2A1-41d4-9310-FFD17EBF84B8}]
  Any DET reported ?
  [/cover] */
  if (ICU_ERROR_FOUND != ErrorFlag)
#endif
  {
    CoreChIndex = Icu_lGetCoreChIndex((uint8)Channel);
    /* Initialize ICU configured channel ROM pointer */
    LocalIcuChanPtr = &((Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->
                                                ChannelConfigPtr)[CoreChIndex]);
#if ((ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_OFF) && \
    (ICU_17_TIMERIP_SAFETY_ENABLE == STD_OFF))
    /* Check if the mode is valid */
    /* [cover parentID={A67D42FB-A968-4b96-ACC6-A16A1039C1A1}]
    Is the channel in Incremental INterface Mode
    [/cover] */
    if (LocalIcuChanPtr->IcuProperties.MeasurementMode
        == (uint32)ICU_17_TIMERIP_MODE_INCREMENTAL_INTERFACE)
#endif
    {
      /* Extract the address to the channel status */
      /* [cover parentID={3F607119-D7A9-46df-BD80-BD0C0A92E537}]
      Read GPT12 counting direction
      [/cover] */
      CellUsed = (uint16)LocalIcuChanPtr->IcuProperties.
          AssignedHwUnitNumber;
      EncDir = Icu_lGpt12ReadDir(CellUsed);
    }
  }
  return(EncDir);
}
#endif
/* (ICU_17_TIMERIP_INCREMENTAL_INTERFACE_API == STD_ON) */
#if (ICU_17_TIMERIP_TIMEOUT_DETECTION_API == STD_ON)
/*******************************************************************************
 ** Traceability: [cover parentID= {4F00F274-F839-41e3-9047-21C168214E6C}]     **
 **                                                                            **
 ** Syntax : void Icu_17_TimerIp_SetTimeoutValue(                              **
 **                               const  Icu_17_TimerIp_ChannelType Channel    **
 **                               const  uint32 TimeoutValue)                  **
 **                                                                            **
 ** Description : This service will set the timeout value passed by the user.  **
 ** [/cover]                                                                   **
 **                                                                            **
 ** Service ID:       0x26                                                     **
 **                                                                            **
 ** Sync/Async:       Synchronous                                              **
 **                                                                            **
 ** Reentrancy:       Reentrant for different channel                          **
 **                                                                            **
 ** Parameters (in):  Channel - Numeric identifier of the ICU channel          **
 **                   TimeoutValue : Timeout value to be set                   **
 **                                                                            **
 ** Parameters (out): None                                                     **
 **                                                                            **
 ** Return value:     None                                                     **
 **                                                                            **
 *******************************************************************************/
/*[cover parentID={8F04E18D-D28A-48c4-AF5F-42751A7C4910}]
 Safety Properties
 [/cover]*/
void Icu_17_TimerIp_SetTimeoutValue(
    const Icu_17_TimerIp_ChannelType Channel,
    const uint32 TimeoutValue)
{
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr; /* ROM pointer */
  uint8 CoreChIndex;
  uint8 CoreId;
  CoreId = (uint8)(Mcal_GetCpuIndex());
/* [cover parentID={8B1BCE3D-379D-44c0-8617-955DE8F5E4E1}]
Det or safety is enabled
[/cover] */
#if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  uint32 ErrorFlag;
  /* [cover parentID={2F0421B0-C3DA-4bf1-B496-A84DE3E74A01}]
  Verify whether Init has been called
  [/cover] */
  ErrorFlag = Icu_lInitCallVerify(ICU_17_TIMERIP_SID_SETTIMEOUTVALUE, CoreId);
  /* [cover parentID={8208C906-337E-4422-895B-D64415F3D3E8}]
  Any DET reported?
  [/cover] */
  if (ErrorFlag != ICU_ERROR_FOUND)
  {
    /* [cover parentID={DECB964C-45BF-4898-B986-91716ECB6B34}]
    Check if the channel is valid
    [/cover] */
    ErrorFlag = Icu_lChannelVerify(ICU_17_TIMERIP_SID_SETTIMEOUTVALUE, Channel, CoreId);
  }

/* [cover parentID={99CC3005-66CF-4e3f-A672-E28581F4A8EB}]
If safety is enabled
[/cover] */
#if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={37D62704-F049-4563-97E5-8D695D7D915E}]
  Any DET reported?
  [/cover] */
  if (ICU_ERROR_FOUND != ErrorFlag)
  {
    /* [cover parentID={AB66C773-1812-4a5f-8160-98E80EBC09DD}]
    Is the Timeout  value valid?
    [/cover] */
    if(TimeoutValue > 0xFFFFFFUL)
    {
      /* [cover parentID={8AF00364-FB75-44a3-9F4B-04B3A47CD1EE}]
      Report error
      [/cover] */
      Mcal_ReportSafetyError(
        ICU_17_TIMERIP_MODULE_ID,
        ICU_17_TIMERIP_INSTANCE_ID,
        ICU_17_TIMERIP_SID_SETTIMEOUTVALUE,
        ICU_17_TIMERIP_E_PARAM_TIMEOUT);
      ErrorFlag = ICU_ERROR_FOUND;
    }
  }
  if (ICU_ERROR_FOUND != ErrorFlag)
  {
    /* [cover parentID={8E958726-4AE1-4eaf-A5BC-1D29A33B733E}]
      Is ICU in sleep mode
    [/cover] */
    if(Icu_17_TimerIp_Varlist[CoreId]->GlobalMode == ICU_17_TIMERIP_MODE_SLEEP)
    {
      /* [cover parentID={5D9879BD-AD3E-4627-9EDD-7DDA5A945208}]
      Report error
      [/cover] */
      Mcal_ReportSafetyError(
        ICU_17_TIMERIP_MODULE_ID,
        ICU_17_TIMERIP_INSTANCE_ID,
        ICU_17_TIMERIP_SID_SETTIMEOUTVALUE,
        ICU_17_TIMERIP_E_INVALID_MODE);/* End of report to Safety */
      ErrorFlag = (uint32) ICU_ERROR_FOUND;
    }
  }
#endif
  if (ICU_ERROR_FOUND != ErrorFlag)
#endif
  {
    CoreChIndex = Icu_lGetCoreChIndex((uint8)Channel);
    LocalIcuChanPtr = &((Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->
            ChannelConfigPtr)[CoreChIndex]);
    /* [cover parentID={709E2DAA-B5F4-4095-B982-B1156CFFDF51}]
    If Safety is enabled
    [/cover] */
#if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
    /* [cover parentID={05B42431-4249-40b2-8A74-B6D8AAC8D04E}]
    Is the channel configured for timeout functionality?
    [/cover] */
    if (LocalIcuChanPtr->IcuProperties.TimeOutEnabled
        == (uint32)ICU_FLAG_SET)
#endif
    {
      /* [cover parentID={4855F0D6-C0AE-45ca-A67F-66BB1C582C26}]
      Update timeout register
      [/cover] */
      Icu_lGtmSetTDUV(
          (uint16)LocalIcuChanPtr->IcuProperties.AssignedHwUnitNumber,
          TimeoutValue, LocalIcuChanPtr->IcuProperties.CTRLData);
    }
#if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
    else
    {
      /* [cover parentID={0CD63EE2-06FD-4165-94F6-02D13BEB0489}]
      Report error
      [/cover] */
      Icu_lReportError(
        ICU_17_TIMERIP_SID_SETTIMEOUTVALUE,
        ICU_17_TIMERIP_E_PARAM_CHANNEL );
    }
#endif
  }

}
#endif
/*******************************************************************************
 **                      Private Function Definitions                         **
 ******************************************************************************/

#if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
(ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {58A6CF35-4D41-4d97-990E-A7BED5F2E317}]     **
**                                                                            **
** Syntax :           LOCAL_INLINE uint32 Icu_lInitDetCheck(                  **
**                  const Icu_17_TimerIp_ConfigType *const IcuConfigPtr,      **
**                  const uint8 CoreId )                                      **
**                                                                            **
** Description :      Local function :Service to DET Check for Init           **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        None                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Reentrant                                               **
**                                                                            **
** Parameters (in):   IcuConfigPtr - Icu config pointer                       **
**                    CoreId  - Core which is calling this function           **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value:      uint32: status of DET.                                  **
**                            ICU_ERROR_NOT_FOUND/ICU_ERROR_FOUND             **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Icu_lInitDetCheck(
  const Icu_17_TimerIp_ConfigType *const IcuConfigPtr,
  const uint8 CoreId)
{
  uint32 ErrorFlag;
  ErrorFlag = (uint32)ICU_ERROR_NOT_FOUND;

  /* To verify whether Init has been called with wrong parameter */
  /* Det Check for NULL pointer  */
  /* [cover parentID={21A415C1-FD4B-4f21-A464-FE2992C4FC85}]
  Is the ConfigPtr Valid ?
  [/cover] */
  if (NULL_PTR == IcuConfigPtr )
  {
    /*Report Error, Init has been called with wrong parameter
      NULL Config Pointer */
    /* [cover parentID={594291DE-0882-43fa-8A96-BE7311F1D20D}]
    Report Error to indicate that the configuration pointer is not valid.
    [/cover] */
    Icu_lReportError(
      ICU_17_TIMERIP_SID_INIT,
      ICU_17_TIMERIP_E_INIT_FAILED
    ); /* Report Error */
    ErrorFlag = ICU_ERROR_FOUND;
  }
  /* [cover parentID={E99BC896-B60C-4886-96D5-6E97FF165A38}]
  If Safety  is enabled or MultiCore DET is On?
  [/cover] */
  #if ((ICU_17_TIMERIP_MULTICORE_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON))
  if(ErrorFlag != ICU_ERROR_FOUND)
  {
    /* [cover parentID={F78143D8-537B-4e79-8F2F-7817178A026E}]
    Is Master Core?
    [/cover] */
    if(MCAL_MASTER_COREID != CoreId)
    {
      /* [cover parentID={5662F67C-1426-422e-ADA8-986258B6A033}]
      Is master core initialized?
      [/cover] */
      if(ICU_INITIALIZED !=
          (Mcal_GetBitAtomic(Icu_17_TimerIp_InitStatus,\
              (MCAL_MASTER_COREID*((uint8)ICU_INIT_STAUS_SIZE)),\
              ICU_INIT_STAUS_SIZE)))
      {
        /* [cover parentID={CDD80136-CED3-47cc-BD1C-1DEED2FF79A8}]
        Report Error to indicate Slave core initialization requested before
        master core initialization.
        [/cover] */
        ErrorFlag = ICU_ERROR_FOUND;
        Icu_lReportMulticoreError(
          ICU_17_TIMERIP_SID_INIT,
          ICU_17_TIMERIP_E_MASTER_CORE_UNINIT
        ); /* Report Error */
      }
      /* Check if config ptr is same as master core */
      /* [cover parentID={8D594FE8-C82D-43c1-833A-FBEBE526D52E}]
      Are stored Config pointer and received config pointer same?
      [/cover] */
      if((Icu_17_TimerIp_ConfigPtr != IcuConfigPtr) && \
          (ErrorFlag != ICU_ERROR_FOUND))
      {
        ErrorFlag = ICU_ERROR_FOUND;
        /* [cover parentID={7371BE72-3BFA-4c7c-8C4C-261C03CEAAD8}]
        Report Error to indicate that master and slave core configuration
        pointers are different.
        [/cover] */
        Icu_lReportMulticoreError(
          ICU_17_TIMERIP_SID_INIT,
          ICU_17_TIMERIP_E_MASTER_CORE_UNINIT
        ); /* Report Error */
      }
      /* Check if core is configured */
      /* [cover parentID={4BC0FC5F-3350-4647-8B83-1427755029F1}]
      Is current core available in the configuration?
      [/cover] */
      if((ErrorFlag != ICU_ERROR_FOUND) && \
          (Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId] == NULL_PTR))
      {
        ErrorFlag = ICU_ERROR_FOUND;
        /* [cover parentID={AF8891D1-D7C2-438f-B9AB-66AD02A0C9A6}]
        Report Error to indicate that core is not configured for this channel
        [/cover] */
        Icu_lReportMulticoreError(
          ICU_17_TIMERIP_SID_INIT,
          ICU_17_TIMERIP_E_CORE_NOT_CONFIGURED
        ); /* Report Error */
      }
    }
  } /* ICU_17_TIMERIP_MULTICORE_ERROR_DETECT */
  #else
  UNUSED_PARAMETER(CoreId);
  #endif
  /* If DET is enabled and Icu_17_TimerIp_Init is called when the ICU
     driver already initialized, Icu_17_TimerIp_Init shall raise DET
     ICU_17_TIMERIP_E_ALREADY_INITIALIZED
     and return without any action. */
  if(ErrorFlag != ICU_ERROR_FOUND)
  {
    /* [cover parentID={40CAF681-5A84-4ff3-B3BB-05A11B4882B6}]
    If ICU driver already initialized
    [/cover] */
    if(ICU_INITIALIZED == \
        Mcal_GetBitAtomic(Icu_17_TimerIp_InitStatus,\
            (((sint32)CoreId)*(ICU_INIT_STAUS_SIZE)),ICU_INIT_STAUS_SIZE))
    {
      /* [cover parentID={E0A237A6-63C3-4c77-B1F4-E46527CCF81E}]
      Report error to indicate that initialization is already done.
      [/cover] */
      Icu_lReportError(
        ICU_17_TIMERIP_SID_INIT,
        ICU_17_TIMERIP_E_ALREADY_INITIALIZED );
      ErrorFlag = ICU_ERROR_FOUND; /* Set ErrorFlag */
    }
  }
  return(ErrorFlag);
}
#endif
/* End of #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) ||
 * (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON) */
/*******************************************************************************
** Traceability: [cover parentID= {79E677C1-B42D-4d89-A11C-EC21F17EC543}]     **
**                                                                            **
** Syntax :           LOCAL_INLINE void Icu_lResetGlobalVariables(            **
**                                                    const uint8 CoreId)     **
**                                                                            **
** Description :      Local function :Service to set all the required global  **
**                                   variables to zero.                       **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        None                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Non Reentrant                                           **
**                                                                            **
** Parameters (in):   CoreId  - Core which is calling this function           **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value:      None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lResetGlobalVariables(const uint8 CoreId)
{
  Icu_17_TimerIp_ChannelType Channel;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * this MISRA rule,To implement efficiently IcuMeasaurementProperty as a
   * post-build parameter.Union is required*/
  Icu_17_TimerIp_ChannelData* ChannelDataPtr;
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr; /* ROM pointer */
  /* Initialize the signal measure parameters to zero for all
   *  channels except ERU.*/
  ChannelDataPtr = Icu_17_TimerIp_Varlist[CoreId]->ChannelDataBasePtr;
  /* Get the channel config base pointer */
  LocalIcuChanPtr = \
      (Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->ChannelConfigPtr);
  for (Channel = (Icu_17_TimerIp_ChannelType) 0;
       Channel < \
       Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->MaxDataChannelCore;
       Channel++)
  {
    switch ((uint32) LocalIcuChanPtr[Channel].IcuProperties.MeasurementMode)
    {
      case (uint32) ICU_17_TIMERIP_MODE_SIGNAL_MEASUREMENT:
        ChannelDataPtr[Channel].SigMeasureParasCcu6.ActiveTime = 0U;
        ChannelDataPtr[Channel].SigMeasureParasCcu6.FirstEdgeFlag = 0U;
        ChannelDataPtr[Channel].SigMeasureParasCcu6.RegValue = 0U;
        break;

      case (uint32) ICU_17_TIMERIP_MODE_SIGNAL_EDGE_DETECT:
        ChannelDataPtr->EdgeDetectParas.EdgeDetectCount = 0U;
        break;

      case (uint32) ICU_17_TIMERIP_MODE_TIMESTAMP:
        ChannelDataPtr[Channel].TimeCaptureParas.Address =
          (Icu_17_TimerIp_ValueType *)0U;
        ChannelDataPtr[Channel].TimeCaptureParas.Counter = 0U;
        ChannelDataPtr[Channel].TimeCaptureParas.Notify = 0U;
        ChannelDataPtr[Channel].TimeCaptureParas.NotifyCounter = 0U;
        ChannelDataPtr[Channel].TimeCaptureParas.Size = 0U;
        break;

      default: /* ICU_17_TIMERIP_MODE_EDGE_COUNTER */
        ChannelDataPtr[Channel].EdgeCountParas.EdgeCounter = 0U;
        break;
    }
  }
  /* Clear the wake-up info for that core */
  #if ((ICU_17_TIMERIP_WAKEUP_FUNCTIONALITY_API == STD_ON) && \
  (ICU_17_TIMERIP_REPORT_WAKEUP_SOURCE == STD_ON))
  /* Clear the Variable to store the channel wake-up info due to which ICU
   woke up */
  Icu_17_TimerIp_Varlist[CoreId]->WakeupChannelInfo = 0U;
  #endif
}
/* End of Icu_lResetGlobalVariables */

/*******************************************************************************
** Traceability: [cover parentID= {9142DE6E-7BC9-4ffa-B2E1-EED724784B9E}]     **
**                                                                            **
** Syntax :           LOCAL_INLINE void Icu_lChannelInit(const uint8 CoreId)  **
**                                                                            **
** Description :      Local function :Service to initialize ICU channels      **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        None                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Non Reentrant                                           **
**                                                                            **
** Parameters (in):   CoreId - Core number in which it is called              **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value:      None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lChannelInit(const uint8 CoreId)
{
  /* Local pointers */
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtrBase; /* ROM pointer */
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr; /* ROM pointer */
  uint32* GlbIndexStatusPtrBase;
  uint32* GlbIndexStatusPtr;
  /* Local variables */
  uint32 IcuOption;
  Icu_17_TimerIp_ChannelType Channel;

  /* Get the channel config base pointer */
  LocalIcuChanPtrBase = \
      (Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->ChannelConfigPtr);
  GlbIndexStatusPtrBase =
    (Icu_17_TimerIp_Varlist[CoreId]->GlbIndexStatusBasePtr);
  /* Run the for loop for all the channels */
  /* [cover parentID={220B2A89-F335-4bee-BE2A-E10EDDD3E350}]
  Initialiaze  for all configure channel
  [/cover] */
  for(Channel = (Icu_17_TimerIp_ChannelType) 0;
      /* [cover parentID={4EA879D6-9E75-4c9e-982B-BF315DF62353}]
      Till last available channel of current core.
      [/cover] */
      Channel < Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->MaxChannelCore;
      Channel = Channel + 1U)
  {
    LocalIcuChanPtr = &LocalIcuChanPtrBase[Channel];
    GlbIndexStatusPtr = &GlbIndexStatusPtrBase[Channel];
    *GlbIndexStatusPtr = 0U;
    /* Depending on ICU option take action */
    IcuOption = (uint32) LocalIcuChanPtr->IcuProperties.AssignedHwUnit;
    /* Work on depending on ICU option chosen for each channel */
    switch (IcuOption)
    {
      /* [cover parentID={8BD962AC-AAEE-4fe3-96A6-4B6FB3C82B51}]
      If ICU option is GTM
      [/cover] */
      case ICU_17_TIMERIP_GTM_OPTION:
        /* [cover parentID={5EEFF065-7635-4ca2-9A1C-324DFB860E73}]
        Initialize channel configured for GTM and set timeuot flag if enabled.
        [/cover] */
        #if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
        /* Initialize channel configured for GTM */
        Icu_lGtmChannelInit(LocalIcuChanPtr);
        if(1U == (uint32 )(LocalIcuChanPtr->IcuProperties.TimeOutEnabled))
        {
          *GlbIndexStatusPtr |= ICU_TIMEOUT_STATUS_MASK;
          if((1U == (uint32 )(LocalIcuChanPtr->IcuProperties.IsTimeOutExclusive)) \
              || (LocalIcuChanPtr->IcuProperties.MeasurementMode == (uint32)ICU_17_TIMERIP_MODE_EDGE_COUNTER))
          {
            *GlbIndexStatusPtr |= ICU_TIMEOUT_EXC_STATUS_MASK;
          }
        }
        #endif
        break;
      /* [cover parentID={723AC0CA-034E-442c-8569-149B3D6A8E62}]
      If ICU option is CCU6
      [/cover] */
      case ICU_17_TIMERIP_CCU_OPTION:
        /* [cover parentID={48E81163-A429-4dbb-9638-CC10D30FC1AC}]
        Initialize channel configured for CCU6
        [/cover] */
        #if (ICU_17_TIMERIP_CCU6_USED == STD_ON)
        /* Initialize channel configured for CCU6 */
        Icu_lCcu6ChannelInit(LocalIcuChanPtr);
        #endif
        break;
      /* [cover parentID={D6C2A39A-7C31-4a31-80E6-B0ABFAE5DCC8}]
      If ICU option is ERU
      [/cover] */
      case ICU_17_TIMERIP_ERU_OPTION:
        /* [cover parentID={66C04F94-3171-4772-BA95-B6CC9E031D4F}]
        Initialize the ERU channel.
        [/cover] */
        #if (ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON)
        /* Initialize the ERU channel */
        Icu_lEruInit(LocalIcuChanPtr);
        /* [cover parentID={0EADE543-6686-448c-8433-C5A4E3E00C6C}]
        Set ERU edge detection flag.
        [/cover] */
        *GlbIndexStatusPtr = *GlbIndexStatusPtr |
            ICU_CHNL_ERU_GPT_SIGEDGE_STATUS_MASK;
#endif
        break;
      /* [cover parentID={CFC5261F-21B7-416f-B06D-6A43C23E1457}]
      If ICU option is GPT12
      [/cover] */
      default: /* ICU_17_TIMERIP_GPT12_OPTION */
        #if (ICU_17_TIMERIP_GPT12_USED == STD_ON)
        /* Initialize channel configured for GPT12 */
        /* [cover parentID={6B4C4A82-0254-4c8d-9961-BAEAB72C1466}]
        Initialize channel configured for GPT12
        [/cover] */
        Icu_lGpt12Init(LocalIcuChanPtr);
        if((uint32)ICU_17_TIMERIP_MODE_SIGNAL_EDGE_DETECT == \
            LocalIcuChanPtr->IcuProperties.MeasurementMode)
        {
          /* [cover parentID={0670CFA1-1C6C-4903-99FF-E7FAC82B6510}]
          Set GPT edge detection flag if the channel mode is edge detection.
          [/cover] */
          *GlbIndexStatusPtr = *GlbIndexStatusPtr |
              ICU_CHNL_ERU_GPT_SIGEDGE_STATUS_MASK;
        }
        #endif
        break;
    }
    /* [cover parentID={25B98525-8D10-49c8-BDD2-8AF9B7035663}]
    Copy the default start edge to channel status variable and clear all the
    flags
    [/cover] */
    *GlbIndexStatusPtr |= \
         (((uint32)(LocalIcuChanPtr->IcuProperties.DefaultStartEdge) \
            << ICU_CHNL_EDGE_POS) & ICU_CHNL_EDGE_MASK);
  }/* End of for loop */
}

#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {E4F15C78-6796-41da-9B8F-D32141C27A6A}]     **
**                                                                            **
** Syntax : LOCAL_INLINE void Icu_lGtmChannelInit(                            **
**            const Icu_17_TimerIp_ChannelConfigType *const LocalIcuChanPtr)  **
**                                                                            **
** Description :     Function to initialize ICU Channel. This function is     **
**                   needed to initialize GTM channel used by ICU. This is    **
**                   mainly needed while changing the PB configuration of ICU **
**                   while not changing the MCU configuration.                **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Non Reentrant                                            **
**                                                                            **
** Parameters (in):  LocalIcuChanPtr - Pointer to the Channel configuration   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lGtmChannelInit(
  const Icu_17_TimerIp_ChannelConfigType *const LocalIcuChanPtr)
{
  uint16 TimChannelNumber;
  Mcu_17_Gtm_TimChConfigType TimCfg;
  uint32 TempRegVal;
  uint8 ModuleNumber;
  uint8 ChannelNumber;

  /* Extract the GTM TIM channel number and module number */
  TimChannelNumber = (uint16) LocalIcuChanPtr->IcuProperties.
                     AssignedHwUnitNumber;
  /* Calculate Module Id of the TIM channel */
  ModuleNumber = (uint8)((TimChannelNumber / ICU_GTM_CHANNELS_PER_TIM_MODULE) \
                         & ICU_GTM_MODULE_NO_MSK);
  /* Calculate Channel number of the TIM channel */
  ChannelNumber = (uint8)(TimChannelNumber % ICU_GTM_CHANNELS_PER_TIM_MODULE);
  /* Disable Timeout */
  TempRegVal = LocalIcuChanPtr->IcuProperties.CTRLData &
          (~((uint32)IFX_GTM_TIM_CH_CTRL_TOCTRL_MSK << IFX_GTM_TIM_CH_CTRL_TOCTRL_OFF));
  /*  Preparing for GTM TIM channel registers initialization in the
   TimCfg structure  */
  TimCfg.TimChCtrlReg = TempRegVal;
  TimCfg.TimChFltRisingEdge =
    (uint32) (LocalIcuChanPtr->IcuProperties.TimChFilterTimeForRisingEdge);
  TimCfg.TimChFltFallingEdge =
    (uint32) (LocalIcuChanPtr->IcuProperties.TimChFilterTimeForFallingEdge);
  /* All interrupts are disabled after Init and only interrupt mode is set */
  TimCfg.TimChIntEnMode = (uint32) ((uint32) ICU_GTM_RESET_INTERRUPTS
      | ((uint32) (LocalIcuChanPtr->IcuProperties.InterruptMode)
          << ICU_GTM_TIM_INTERRUPTMODE_POS));
  /* ICU does not use Look-up table feature of GTM */
  TimCfg.TimChExtendedCtrlReg = LocalIcuChanPtr->IcuProperties.TimECTRLData;
  TimCfg.TimerId = (uint32)ChannelNumber;
  TimCfg.TimerId |= ((uint32)ModuleNumber) << ICU_MCU_TIM_MODULE_POS;
  TimCfg.TimChTduvReg = LocalIcuChanPtr->IcuProperties.TimTDUVData;
  /*call to GTM library API */
  /* [cover parentID={B2BFF9A7-B571-477c-AC87-15DA03BCBCB8}]
  Initialize GTM TIM channel registers
  [/cover] */
  /* MISRA2012_RULE_1_3_JUSTIFICATION: Local variable is passed as pointer to
  an MCU API which simply access but does not pass it further or store is global
  variables. */
  Mcu_17_Gtm_TimChannelInit(&TimCfg);
}
#endif
/* ICU_17_TIMERIP_GTM_TIM_USED */

#if (ICU_17_TIMERIP_INITCHECK_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={449F2120-136E-4d89-A26D-20B61B1275D6}]      **
**                                                                            **
** Syntax :           LOCAL_INLINE Std_ReturnType Icu_lPreInitCheck(          **
**                         const Icu_17_TimerIp_ConfigType* const ConfigPtr,  **
**                                  const uint8 CoreId     )                  **
**                                                                            **
** Description :  Local function to check if the core init is done            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        None                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant                                           **
**                                                                            **
** Parameters (in):   Configptr - configuration pointer against which to be   **
**                                verified                                    **
**                    CoreId - core in which function is called               **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value:      error flag status                                       **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Icu_lPreInitCheck( \
    const Icu_17_TimerIp_ConfigType* const  ConfigPtr, const uint8 CoreId)
{
  Std_ReturnType ErrorFlag;
  uint8 CoreIndex;
  CoreIndex = (CoreId * (uint8) (ICU_INIT_STAUS_SIZE));
  /* Check if the input parameter is NULL */
  /* [cover parentID={43F5D878-B3D6-4cd4-B195-DA98E0A09342}]
  Check if the input parameter is NULL and  config pointer stored is same as
  the required and the init status is set and ICU initialized
  [/cover] */
  if (NULL_PTR != ConfigPtr)
  {
    /* Check if the config pointer stored is same as the required and the init
     * status is set */
    if (Icu_17_TimerIp_ConfigPtr == ConfigPtr)
    {
      if (ICU_INITIALIZED
          != (Mcal_GetBitAtomic(Icu_17_TimerIp_InitStatus,
                                ((sint32 )(CoreIndex)), ICU_INIT_STAUS_SIZE)))
      {
        ErrorFlag = E_NOT_OK;
      }
      else
      {
        ErrorFlag = E_OK;
      }
    }
    else
    {
      ErrorFlag = E_NOT_OK;
    }
  }
  else
  {
    ErrorFlag = E_NOT_OK;
  }
  return ErrorFlag;
}

/*******************************************************************************
** Traceability: [cover parentID={7EF75293-DAC4-4b51-A563-904BB32A996A}]      **
**                                                                            **
** Syntax : LOCAL_INLINE unit32 Icu_lChannelStatusCheckValue(                 **
**            const Icu_17_TimerIp_ChannelConfigType *const LocalIcuChanPtr)  **
**                                                                            **
** Description :     Function to calculate the channel status value           **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Non Reentrant                                            **
**                                                                            **
** Parameters (in):  LocalIcuChanPtr - Pointer to the Channel configuration   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     channel status value                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Icu_lChannelStatusCheckValue(
  const Icu_17_TimerIp_ChannelConfigType *const LocalIcuChanPtr)
{
  uint32 StatusValue;
  uint32 IcuOption;
  /* Depending on ICU option take action */
  IcuOption = (uint32) LocalIcuChanPtr->IcuProperties.AssignedHwUnit;
  /* Work on depending on ICU option chosen for each channel */
  switch (IcuOption)
  {
    /* [cover parentID={17E4A303-5180-4635-82D0-640D6AB5F0D8}]
    If ICU option is GTM
    [/cover] */
    case ICU_17_TIMERIP_GTM_OPTION:
      #if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
      if(1U == (uint32 )(LocalIcuChanPtr->IcuProperties.TimeOutEnabled))
      {
        StatusValue = ICU_TIMEOUT_STATUS_MASK;
        if((1U == (uint32 )(LocalIcuChanPtr->IcuProperties.IsTimeOutExclusive))
            || (LocalIcuChanPtr->IcuProperties.MeasurementMode ==
                                      (uint32)ICU_17_TIMERIP_MODE_EDGE_COUNTER))
        {
          StatusValue |= ICU_TIMEOUT_EXC_STATUS_MASK;
        }
      }
      else
      {
        StatusValue = 0U;
      }
      #else
      StatusValue = 0U;
      #endif
      break;
    /* [cover parentID={82B321DD-3D7E-4e6c-89B1-9812085F59D6}]
    If ICU option is CCU6
    [/cover] */
    case ICU_17_TIMERIP_CCU_OPTION:
      StatusValue = 0U;
      break;
    /* [cover parentID={391087D8-F4DF-4c63-B2AB-1294FC18A5FE}]
    If ICU option is ERU
    [/cover] */
    case ICU_17_TIMERIP_ERU_OPTION:
      #if (ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON)
      StatusValue = ICU_CHNL_ERU_GPT_SIGEDGE_STATUS_MASK;
      #else
      StatusValue = 0U;
      #endif
      break;
    default: /* ICU_17_TIMERIP_GPT12_OPTION */
      #if (ICU_17_TIMERIP_GPT12_USED == STD_ON)
      if((uint32)ICU_17_TIMERIP_MODE_SIGNAL_EDGE_DETECT == \
          LocalIcuChanPtr->IcuProperties.MeasurementMode)
      {
        StatusValue = ICU_CHNL_ERU_GPT_SIGEDGE_STATUS_MASK;
      }
      else
      {
        StatusValue = 0U;
      }
      #else
      StatusValue = 0U;
      #endif
      break;
  }
  /* [cover parentID={00604A5B-FDC8-4802-86DE-88263CD2CD6F}]
  Copy the default start edge to channel status variable and clear all the
  flags
  [/cover] */
  StatusValue |= \
       (((uint32)(LocalIcuChanPtr->IcuProperties.DefaultStartEdge) \
          << ICU_CHNL_EDGE_POS) & ICU_CHNL_EDGE_MASK);
   return StatusValue;
}

/*******************************************************************************
** Traceability: [cover parentID={105DEAD7-0D3D-47b2-A007-193C8A02E6B8}]      **
**                                                                            **
** Syntax :           LOCAL_INLINE Std_ReturnType                             **
**                                Icu_lResetGlobalVariablesCheck(             **
**                                  const uint8 CoreId     )                  **
**                                                                            **
** Description :      Local function to check if the Global variables are     **
**                    reset properly.                                         **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        None                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Non Reentrant                                           **
**                                                                            **
** Parameters (in):   CoreId - core in which function is called               **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value:      error flag status                                       **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Icu_lResetGlobalVariablesCheck(const uint8 CoreId)
{
  Std_ReturnType ErrorFlag;
  uint16 CheckValue16;
  uint32 CheckValue32;
  ErrorFlag = E_OK;
  Icu_17_TimerIp_ChannelType Channel;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * MISRA rule,To implement efficiently IcuMeasaurementProperty as a post-build
   * parameter.Union is required*/
  const Icu_17_TimerIp_ChannelData* ChannelDataPtr;
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr; /* ROM pointer */
  /* Initialize the signal measure parameters to zero for all
   *  channels except ERU.*/
  ChannelDataPtr = Icu_17_TimerIp_Varlist[CoreId]->ChannelDataBasePtr;
  /* Get the channel config base pointer */
  LocalIcuChanPtr =
    (Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->ChannelConfigPtr);
  /* Check Initialize the signal measure parameters to zero for all channels
   * except ERU.*/
  for (Channel = (Icu_17_TimerIp_ChannelType) 0;
       (Channel
        < Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->MaxDataChannelCore)
       && (ErrorFlag == E_OK); Channel++)
  {
    /* [cover parentID={505BD5A3-3871-4010-8C4F-D49D878F8AD9}]
    If mesurement parameters corresponding to channels mode are not reset
    [/cover] */
    switch (LocalIcuChanPtr[Channel].IcuProperties.MeasurementMode)
    {
      case (uint32) ICU_17_TIMERIP_MODE_SIGNAL_MEASUREMENT:
        /* Check if the signal measure parameters are reset */
        CheckValue32 = ChannelDataPtr[Channel].SigMeasureParasCcu6.ActiveTime;
        CheckValue32 = CheckValue32 | \
                       ChannelDataPtr[Channel].SigMeasureParasCcu6.FirstEdgeFlag;
        CheckValue32 = CheckValue32 | \
                       ChannelDataPtr[Channel].SigMeasureParasCcu6.RegValue;
        if(CheckValue32 != 0U)
        {
          ErrorFlag = E_NOT_OK;
        }
        break;
      case (uint32) ICU_17_TIMERIP_MODE_SIGNAL_EDGE_DETECT:
        /* Check if the edge detect parameters are reset */
        if (ChannelDataPtr[Channel].EdgeDetectParas.EdgeDetectCount != 0U)
        {
          ErrorFlag = E_NOT_OK;
        }
        break;
      case (uint32) ICU_17_TIMERIP_MODE_TIMESTAMP:
        CheckValue16 = ChannelDataPtr[Channel].TimeCaptureParas.Counter;
        CheckValue16 = CheckValue16 | ChannelDataPtr[Channel].TimeCaptureParas.Notify;
        CheckValue16 = CheckValue16 | \
                       ChannelDataPtr[Channel].TimeCaptureParas.NotifyCounter;
        CheckValue16 = CheckValue16 | ChannelDataPtr[Channel].TimeCaptureParas.Size;
        if ((CheckValue16 != 0U) \
            || (ChannelDataPtr[Channel].TimeCaptureParas.Address != \
                (Icu_17_TimerIp_ValueType *)0U))
        {
          ErrorFlag = E_NOT_OK;
        }
        break;
      default: /* ICU_17_TIMERIP_MODE_EDGE_COUNTER */
        if(ChannelDataPtr[Channel].EdgeCountParas.EdgeCounter != 0U)
        {
          ErrorFlag = E_NOT_OK;
        }
        break;
    }
  }
  #if ((ICU_17_TIMERIP_WAKEUP_FUNCTIONALITY_API == STD_ON) && \
  (ICU_17_TIMERIP_REPORT_WAKEUP_SOURCE == STD_ON))
  /* Check if wakeup channel info is reset */
  if (Icu_17_TimerIp_Varlist[CoreId]->WakeupChannelInfo != 0U)
  {
    ErrorFlag = E_NOT_OK;
  }
  #endif
  return ErrorFlag;
}

#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={77DDCC49-7368-4b12-86F6-66137AB0ED12}]      **
**                                                                            **
** Syntax : LOCAL_INLINE Std_ReturnType Icu_lGtmChannelInitCheck(             **
**            const Icu_17_TimerIp_ChannelConfigType *const LocalIcuChanPtr)  **
**                                                                            **
** Description :     Function to check the initialization of TIM channel      **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Non Reentrant                                            **
**                                                                            **
** Parameters (in):  LocalIcuChanPtr - Pointer to the Channel configuration   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     error flag status                                        **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Icu_lGtmChannelInitCheck(
  const Icu_17_TimerIp_ChannelConfigType *const LocalIcuChanPtr)
{
  uint16 TimChannelNumber;
  Mcu_17_Gtm_TimChConfigType TimCfg;
  uint32 TempRegVal;
  uint8 ModuleNumber;
  uint8 ChannelNumber;
  Std_ReturnType ErrorFlag;

  /* Extract the GTM TIM channel number and module number */
  TimChannelNumber = (uint16) LocalIcuChanPtr->IcuProperties.
                     AssignedHwUnitNumber;
  /* Calculate Module Id of the TIM channel */
  ModuleNumber = (uint8)((TimChannelNumber / ICU_GTM_CHANNELS_PER_TIM_MODULE) \
                         & ICU_GTM_MODULE_NO_MSK);
  /* Calculate Channel number of the TIM channel */
  ChannelNumber = (uint8)(TimChannelNumber % ICU_GTM_CHANNELS_PER_TIM_MODULE);
  /* Disable Timeout */
  TempRegVal = LocalIcuChanPtr->IcuProperties.CTRLData &
          (~((uint32)IFX_GTM_TIM_CH_CTRL_TOCTRL_MSK << IFX_GTM_TIM_CH_CTRL_TOCTRL_OFF));
  /*  Preparing for GTM TIM channel registers initialization in the
   TimCfg structure  */
  TimCfg.TimChCtrlReg = TempRegVal;
  TimCfg.TimChFltRisingEdge =
    (uint32) (LocalIcuChanPtr->IcuProperties.TimChFilterTimeForRisingEdge);
  TimCfg.TimChFltFallingEdge =
    (uint32) (LocalIcuChanPtr->IcuProperties.TimChFilterTimeForFallingEdge);
  /* All interrupts are disabled after Init and only interrupt mode is set */
  TimCfg.TimChIntEnMode = (uint32) ((uint32) ICU_GTM_RESET_INTERRUPTS
                  | ((uint32) (LocalIcuChanPtr->IcuProperties.InterruptMode)
                                         << ICU_GTM_TIM_INTERRUPTMODE_POS));
  /* ICU does not use Look-up table feature of GTM */
  TimCfg.TimChExtendedCtrlReg = LocalIcuChanPtr->IcuProperties.TimECTRLData;
  TimCfg.TimerId = (uint32)ChannelNumber;
  TimCfg.TimerId |= ((uint32)ModuleNumber) << ICU_MCU_TIM_MODULE_POS;

  TimCfg.TimChTduvReg = LocalIcuChanPtr->IcuProperties.TimTDUVData;
  /*call to GTM library API */
  /* MISRA2012_RULE_1_3_JUSTIFICATION: Local variable is passed as pointer to
  an MCU API which simply access but does not pass it further or store is global
  variables. */
  /* [cover parentID={909E9167-5BA0-43bd-A727-900354BD0594}]
   Check GTM TIM channel registers configuration with respect to Timconfig
   Structure and set Error flag status based on that.
  [/cover] */
  ErrorFlag = Mcu_17_Gtm_TimChInitCheck(&TimCfg);
  return ErrorFlag;
}
#endif
/* ICU_17_TIMERIP_GTM_TIM_USED */


#if (ICU_17_TIMERIP_CCU6_USED == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={B18564C2-D248-406e-962E-F4B76A8B4554}]      **
**                                                                            **
** Syntax : LOCAL_INLINE Std_ReturnType Icu_lCcu6ChannelInitCheck(            **
**            const Icu_17_TimerIp_ChannelConfigType *const LocalIcuChanPtr)  **
**                                                                            **
** Description :     Function to initialize the CC6x registers by calling an  **
**                   MCU CCU timer API                                        **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Non Reentrant                                            **
**                                                                            **
** Parameters (in):  LocalIcuChanPtr - Pointer to the Channel configuration   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     error flag status                                        **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Icu_lCcu6ChannelInitCheck(
  const Icu_17_TimerIp_ChannelConfigType *const LocalIcuChanPtr)
{
  Mcu_17_Ccu6_TimerConfigType Ccu6Cfg;
  /* Variable to hold the current CCU6 address */
  volatile const Ifx_CCU6 *Ccu6RegPtr;
  uint32  Ccu6RegVal; /* Variable to hold the current CCU6 T12 reg value */
  Std_ReturnType ErrorFlag;
  uint16 CellUsed;

  /* Get the CCU6 kernel and comparator being used */
  CellUsed = LocalIcuChanPtr->IcuProperties.AssignedHwUnitNumber;
  Ccu6Cfg.TimerId = ((uint32)CellUsed & ICU_CCU_GET_KERNEL);
  Ccu6Cfg.TimerId |= (((uint32)CellUsed & ICU_CCU_GET_COMPARATOR) <<
                         (ICU_MCU_CCU_COMPARATOR_POS - ICU_CCU_NIBBLE_SIZE));
  /* ICU requires the T12 to be full scale, 0U - 0xFFFFU and hence maximum
   * value for period */
  Ccu6Cfg.TimerPeriodReg = ICU_CCU6_MAX_T12_TIMER_VAL;
  /* Shadow reg unused for ICU */
  Ccu6Cfg.Ccu6ShadowReg = 0U;
  /* Modulation Control unused by ICU */
  Ccu6Cfg.ModCtrlReg = 0U;
  /* Passive State level is unused by ICU */
  Ccu6Cfg.PasStateLvlReg = 0U;
  /* Start the T12 counter from 0 */
  Ccu6Cfg.TimerCntReg = 0U;
  /* T12 counter should be started after this call, T12 clock divider select
   * and pre-scaler enable from User */
  Ccu6Cfg.TimerCtrlReg0 =
    LocalIcuChanPtr->IcuProperties.TimChannelClockSelect;
  /* Pin selection from User */
  Ccu6Cfg.PortInSelReg0 = LocalIcuChanPtr->IcuProperties.PinSelection;
  /* no interrupts should be enabled after Init */
  Ccu6Cfg.IntEnReg = 0U;
  /* Interrupt node as chosen by User */
  Ccu6Cfg.IntNodePointerReg =
    (uint8)LocalIcuChanPtr->IcuProperties.InterruptMode;

  /* Select the Comparator mode depending on ICU channel mode */
  switch((uint32)LocalIcuChanPtr->IcuProperties.MeasurementMode)
  {
    case (uint32)ICU_17_TIMERIP_MODE_SIGNAL_MEASUREMENT:
      /* Signal measure Period measurement requires mode dependent on edge */
      if((uint8)ICU_17_TIMERIP_PERIOD_TIME == \
          (uint8)(LocalIcuChanPtr->IcuProperties.MeasurementProperty))
      {
        if((uint8)ICU_17_TIMERIP_RISING_EDGE == \
            (uint8)(LocalIcuChanPtr->IcuProperties.DefaultStartEdge))
        {
          Ccu6Cfg.TimerModeSelectReg = (uint8)ICU_CCU_CAPTURE_MODE2;
        }
        else
        {
          Ccu6Cfg.TimerModeSelectReg = (uint8)ICU_CCU_CAPTURE_MODE3;
        }
      }
      /* All other signal measure property requires MODE1*/
      else
      {
        Ccu6Cfg.TimerModeSelectReg = (uint8)0;
      }
      break;
    case (uint32) ICU_17_TIMERIP_MODE_TIMESTAMP:
      /* Mode is configured in Start time stamp */
      Ccu6Cfg.TimerModeSelectReg = (uint8)0;
      break;
    default: /* ICU_17_TIMERIP_MODE_SIGNAL_EDGE_DETECT */
      /* Any other mode is supported by Mode1 */
      Ccu6Cfg.TimerModeSelectReg = (uint8)ICU_CCU_CAPTURE_MODE1;
      break;
  }
  /*call to CCU6 library API */
  /* MISRA2012_RULE_1_3_JUSTIFICATION: Local variable is passed as pointer to
  an MCU API which simply access but does not pass it further or store is global
  variables. */
  /* [cover parentID={77ABFD47-7F7A-4f50-AAC4-E1B5DCAB75A0}]
     Check CCU6 Kernel registers configuration with respect
     to Ccuconfig Structure and set Error flag status.
   [/cover] */
  ErrorFlag = Mcu_17_Ccu6_TimerInitCheck(&Ccu6Cfg);

  /* Get the base address of the Kernal */
  Ccu6RegPtr = &(&MODULE_CCU60)[CellUsed & ICU_CCU_GET_KERNEL];

  /* Read the timer counter start for T12*/
  Ccu6RegVal = Ccu6RegPtr->TCTR0.B.T12R;
  /* Check the timer counter start for T12*/
  /* [cover parentID={850A11DD-F12D-4168-BA2D-F6387ADDEBD3}]
  Check if the timer counter start for T12 and No error is set
  [/cover] */
  if((ErrorFlag != E_NOT_OK) && (Ccu6RegVal != ICU_CCU6_T12_START))
  {
    ErrorFlag = E_NOT_OK;
  }
  return ErrorFlag;
}
#endif
/* #if (ICU_17_TIMERIP_CCU6_USED == STD_ON) */

#if (ICU_17_TIMERIP_GPT12_USED == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={0BF4FB09-998F-4289-A18A-E9CEBAFBB34A}]]     **
**                                                                            **
** Syntax : LOCAL_INLINE Std_ReturnType Icu_lGpt12InitCheck(                  **
**            const Icu_17_TimerIp_ChannelConfigType *const LocalIcuChanPtr)  **
**                                                                            **
** Description :     Function to initialize the GPT12Tx registers by calling  **
**                   MCU GPT12 timer API                                      **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Non Reentrant                                            **
**                                                                            **
** Parameters (in):  LocalIcuChanPtr - Pointer to the Channel configuration   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     error flag status                                        **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Icu_lGpt12InitCheck(
  const Icu_17_TimerIp_ChannelConfigType *const LocalIcuChanPtr)
{
  uint8 ChannelNo;                              /* Holds the GPT12 Tx Number  */
  Mcu_17_Gpt12_TimerConfigType Gpt12;
  Std_ReturnType ErrorFlag = E_NOT_OK;

  /* Extract Channel Number */
  ChannelNo = (uint8)(LocalIcuChanPtr->IcuProperties.AssignedHwUnitNumber) &
              ICU_LOWER_NIBBLE;
  /* Fill the User selected port */
  Gpt12.PortInSelReg = LocalIcuChanPtr->IcuProperties.PinSelection;
  /* Reset the Timer counter */
  Gpt12.TimerCntReg = 0U;

  Gpt12.TimerCtrlReg = LocalIcuChanPtr->IcuProperties.CTRLData;
  /* Fill the channel number */
  Gpt12.TimerId = ChannelNo;

  /* Call the Mcu API to check the init*/
  /* MISRA2012_RULE_1_3_JUSTIFICATION: Local variable is passed as pointer to
  an MCU API which simply access but does not pass it further or store is global
  variables. */
  /* [cover parentID={0B640A53-E3AB-4fc2-84FF-DA9556EF5CF5}]
  Check GPT12 channel registers/SFR configuration with respect to Gpt12
  Configuration Structure and set Error flag status.
  [/cover] */
  ErrorFlag = Mcu_17_Gpt12_TimerInitCheck(&Gpt12);

  return ErrorFlag;
}
#endif
/* ICU_17_TIMERIP_GPT12_USED */

#if (ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={3389D684-19E3-4db2-BBF6-716A08297722}]      **
**                                                                            **
** Syntax :           LOCAL_INLINE Std_ReturnType Icu_lEruInitCheck(          **
**            const Icu_17_TimerIp_ChannelConfigType *const LocalIcuChanPtr)  **
**                                                                            **
** Description :      To check initialize ERU hardware                        **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        None                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Non Reentrant                                           **
**                                                                            **
** Parameters (in):   LocalIcuChanPtr - Pointer to the Channel configuration  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value:      error flag status                                       **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Icu_lEruInitCheck(
  const Icu_17_TimerIp_ChannelConfigType *const LocalIcuChanPtr)
{
  uint32 RegValue;
  uint16 HwUsed;
  uint8 Edge;
  uint8 ExisValue;
  uint8 InpValue;
  uint8 EruPos;
  uint32 SfrVal;
  uint32 CmpVal = 0xFFFFFFFFU;
  Std_ReturnType ErrorFlag = E_NOT_OK;

  /* Read the Edge configured */
  Edge = LocalIcuChanPtr->IcuProperties.DefaultStartEdge;
  /* To calculate the value passed for FEN and REN setting */
  if(Edge == (uint8)ICU_17_TIMERIP_RISING_EDGE)
  {
    Edge = ICU_ERU_RISING_EDGE;
  }
  else if(Edge == (uint8)ICU_17_TIMERIP_FALLING_EDGE)
  {
    Edge = ICU_ERU_FALLING_EDGE;
  }
  else
  {
    Edge = ICU_ERU_BOTH_EDGE;
  }
  /* Read the HW used from configuration */
  HwUsed = LocalIcuChanPtr->IcuProperties.AssignedHwUnitNumber;
  /* Extract the EXIS and INP value */
  ExisValue = (uint8)((HwUsed >> ICU_ERU_EXIS_CHNL_BIT_POS) & ICU_ERU_CHNL_MASK);
  InpValue = (uint8)((HwUsed >> ICU_ERU_OGU_CHNL_BIT_POS) & ICU_ERU_CHNL_MASK);
  /* Populate the register value to write with EXIS, INP, FEN, REN, EIEN */
  RegValue = ((uint32)InpValue << ICU_ERU_INP0_POS);
  RegValue |= ((uint32)ExisValue << ICU_ERU_EXIS0_POS);
  RegValue |= ((uint32)Edge << ICU_ERU_FEN_0_POS);
  RegValue |= (uint32)ICU_ASSERT_EIEN;
  /* Get the Eicr register to be Checked */
  SfrVal =
    (MODULE_SCU.EICR[(HwUsed & ICU_ERU_CHNL_MASK) / ICU_ERU_CHNL_PAIR_COUNT].U);
  /* Get the Pos of Eicr register to be checked */
  EruPos = (uint8)(((HwUsed % ICU_ERU_CHNL_PAIR_COUNT) == 0U) ? \
                   ICU_EICR_LOWER_HALF_OFFSET : ICU_EICR_UPPER_HALF_OFFSET);

  /* Check  EICR register */
  if(EruPos != ICU_EICR_UPPER_HALF_OFFSET)
  {
    SfrVal = (SfrVal & ICU_EICR_LOWER_HALF_MASK);
  }
  else
  {
    /* Read the register value and sift to lower 16 bit position*/
    SfrVal = (SfrVal & ICU_EICR_UPPER_HALF_MASK);
    SfrVal = (uint32)SfrVal >> EruPos;
  }

  CmpVal &= ~(SfrVal ^ RegValue);
  /* [cover parentID={D637EBA5-798B-44ed-9FF9-839A7ACFCC2D}]
  Is Compare value equal to 0xFFFFFFFF?
  [/cover] */
  if(CmpVal == ICU_INITCHECK_NO_ERR_VAL)
  {
    ErrorFlag = E_OK;
  }
  return ErrorFlag;
}
#endif
/* #if (ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON) */
#endif
/* (ICU_17_TIMERIP_INITCHECK_API == STD_ON)*/

#if (ICU_17_TIMERIP_CCU6_USED == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {D1968127-EC6F-440f-B0E7-C15F7255C53D}]     **
**                                                                            **
** Syntax : LOCAL_INLINE void Icu_lCcu6ChannelInit(                           **
**            const Icu_17_TimerIp_ChannelConfigType *const LocalIcuChanPtr)  **
**                                                                            **
** Description :     Function to initialize the CC6x registers by calling an  **
**                   MCU CCU timer API                                        **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Non Reentrant                                            **
**                                                                            **
** Parameters (in):  LocalIcuChanPtr - Pointer to the Channel configuration   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lCcu6ChannelInit(
  const Icu_17_TimerIp_ChannelConfigType *const LocalIcuChanPtr)
{
  Mcu_17_Ccu6_TimerConfigType Ccu6Cfg;
  uint16 CellUsed;

  /* Get the CCU6 kernel and comparator being used */
  CellUsed = LocalIcuChanPtr->IcuProperties.AssignedHwUnitNumber;
  /* Fill the values as required by the Mcu API */
  /* Timer ID depends on Kernel used and Comparator used. For ICU only T12 is
   * getting used*/
  /* [7:0] - Kernel  [15:8] - T12/T13  [23:16] - Comparator */
  Ccu6Cfg.TimerId = ((uint32)CellUsed & ICU_CCU_GET_KERNEL);
  Ccu6Cfg.TimerId |= (((uint32)CellUsed & ICU_CCU_GET_COMPARATOR) <<
                         (ICU_MCU_CCU_COMPARATOR_POS - ICU_CCU_NIBBLE_SIZE));
  /* ICU requires the T12 to be full scale, 0U - 0xFFFFU and hence maximum
   * value for period */
  Ccu6Cfg.TimerPeriodReg = ICU_CCU6_MAX_T12_TIMER_VAL;
  /* Shadow reg unused for ICU */
  Ccu6Cfg.Ccu6ShadowReg = 0U;
  /* Modulation Control unused by ICU */
  Ccu6Cfg.ModCtrlReg = 0U;
  /* Passive State level is unused by ICU */
  Ccu6Cfg.PasStateLvlReg = 0U;
  /* Start the T12 counter from 0 */
  Ccu6Cfg.TimerCntReg = 0U;
  /* [cover parentID={1CDCBE93-1464-4331-9DC8-B4E1357F5A94}]
  Select T12 clock divider, pre-scaler enable and pin from configuration
  [/cover] */
  /* T12 counter should be started after this call, T12 clock divider select
   * and pre-scaler enable from User */
  Ccu6Cfg.TimerCtrlReg0 =
    LocalIcuChanPtr->IcuProperties.TimChannelClockSelect;
  /* Pin selection from User */
  Ccu6Cfg.PortInSelReg0 = LocalIcuChanPtr->IcuProperties.PinSelection;
  /* no interrupts should be enabled after Init */
  Ccu6Cfg.IntEnReg = 0U;
  /* Interrupt node as chosen by User */
  Ccu6Cfg.IntNodePointerReg =
    (uint8)LocalIcuChanPtr->IcuProperties.InterruptMode;

  /* Select the Comparator mode depending on ICU channel mode */
  switch(LocalIcuChanPtr->IcuProperties.MeasurementMode)
  {
    /* [cover parentID={220DE275-6DB7-4c32-99BA-5BDC5EBFB0A1}]
    If measurement mode is signal measurement
    [/cover] */
    case (uint32)ICU_17_TIMERIP_MODE_SIGNAL_MEASUREMENT:
      /* Signal measure Period measurement requires mode dependent on edge */
      /* [cover parentID={2919E50A-B74A-4dd9-A7F4-8AB6BB0FFD34}]
      If measurement property is period time
      [/cover] */
      if((uint8)ICU_17_TIMERIP_PERIOD_TIME == \
          (uint8)(LocalIcuChanPtr->IcuProperties.MeasurementProperty))
      {
        /* [cover parentID={2256B1D6-C9F4-4614-B935-99F838134233}]
        Is the default edge Rising edge?
        [/cover] */
        if((uint8)ICU_17_TIMERIP_RISING_EDGE == \
            (uint8)(LocalIcuChanPtr->IcuProperties.DefaultStartEdge))
        {
          Ccu6Cfg.TimerModeSelectReg = (uint8)ICU_CCU_CAPTURE_MODE2;
        }
        else
        {
          Ccu6Cfg.TimerModeSelectReg = (uint8)ICU_CCU_CAPTURE_MODE3;
        }
      }
      /* All other signal measure property requires to enable interrupt by
       * calling start signal measurement*/
      else
      {
        Ccu6Cfg.TimerModeSelectReg = (uint8)0;
      }
      break;
      /* [cover parentID={E83A1B0E-7EFC-4295-9CA1-8341DDF856DA}]
      If measurement mode is time stamping
      [/cover] */
    case (uint32) ICU_17_TIMERIP_MODE_TIMESTAMP:
      /* Mode is configured in Start time stamp */
      Ccu6Cfg.TimerModeSelectReg = (uint8)0;
      break;
      /* [cover parentID={0FDE9B73-832B-4a9f-AAF6-C3C9FBADEC75}]
      If measurement mode is edge detect
      [/cover] */
    default: /* ICU_17_TIMERIP_MODE_SIGNAL_EDGE_DETECT */
      /* Any other mode is supported by Mode1 */
      Ccu6Cfg.TimerModeSelectReg = (uint8)ICU_CCU_CAPTURE_MODE1;
      break;
  }
  /*call to CCU6 library API */
  /* [cover parentID={98683FC8-8545-4478-85A0-D1AF5F037077}]
  Initialize timer
  [/cover] */
  /* MISRA2012_RULE_1_3_JUSTIFICATION: Local variable is passed as pointer to
  an MCU API which simply access but does not pass it further or store is global
  variables. */
  Mcu_17_Ccu6_TimerInit(&Ccu6Cfg);

  /* Enable the T12 clock */
  /* [cover parentID={C3A03FA4-5B42-45f8-978B-5AF462489AEA}]
  Enable Timer clock
  [/cover] */
  Mcu_17_Ccu6_TimerShadowTransfer(Ccu6Cfg.TimerId);
  /* [cover parentID={90D4B163-8E51-4fa9-A42A-01271FB8C145}]
  Start Timer
  [/cover] */
  Mcu_17_Ccu6_TimerStart(Ccu6Cfg.TimerId);
}
#endif
/* #if (ICU_17_TIMERIP_CCU6_USED == STD_ON) */

#if (ICU_17_TIMERIP_GPT12_USED == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {12BA57BF-A546-420e-A4F3-06D7D9115FB2}]     **
**                                                                            **
** Syntax : LOCAL_INLINE void Icu_lGpt12Init(                                 **
**            const Icu_17_TimerIp_ChannelConfigType *const LocalIcuChanPtr)  **
**                                                                            **
** Description :     Function to initialize the GPT12Tx registers by calling  **
**                   MCU GPT12 timer API                                      **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Non Reentrant                                            **
**                                                                            **
** Parameters (in):  LocalIcuChanPtr - Pointer to the Channel configuration   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lGpt12Init(
  const Icu_17_TimerIp_ChannelConfigType *const LocalIcuChanPtr)
{
  uint8 ChannelNo;                              /* Holds the GPT12 Tx Number  */
  Mcu_17_Gpt12_TimerConfigType Gpt12;

  /* Extract Channel Number */
  ChannelNo = (uint8)(LocalIcuChanPtr->IcuProperties.AssignedHwUnitNumber) &
              ICU_LOWER_NIBBLE;
  /* [cover parentID={9F1CF02C-A845-477b-B01F-5DAC2CCAFF59}]
  Update the structure with port selection, timer selection,
  default active edge, timer counter set to zero, timer set to counter
  mode and timer set to run mode.
  [/cover] */
  /* Fill the User selected port */
  Gpt12.PortInSelReg = LocalIcuChanPtr->IcuProperties.PinSelection;
  /* Reset the Timer counter */
  Gpt12.TimerCntReg = 0U;
  Gpt12.TimerCtrlReg = LocalIcuChanPtr->IcuProperties.CTRLData;

  /* Fill the channel number */
  Gpt12.TimerId = ChannelNo;

  /* Call the Mcu API to initialize the timer */
  /* [cover parentID={E15E5BC1-2D44-4137-8131-2E7C0FAFB5EF}]
  Call MCU api to initialize the GPT12 timer.
  [/cover] */
  /* MISRA2012_RULE_1_3_JUSTIFICATION: Local variable is passed as pointer to
  an MCU API which simply access but does not pass it further or store is global
  variables. */
  Mcu_17_Gpt12_TimerInit(&Gpt12);

}
#endif
/* ICU_17_TIMERIP_GPT12_USED */

#if (ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {22E84E16-4330-49d7-8E8D-56F59EB8D254}]     **
**                                                                            **
** Syntax :           LOCAL_INLINE void Icu_lEruInit(                         **
**            const Icu_17_TimerIp_ChannelConfigType *const LocalIcuChanPtr)  **
**                                                                            **
** Description :      To initialize ERU hardware                              **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        None                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Non Reentrant                                           **
**                                                                            **
** Parameters (in):   LocalIcuChanPtr - Pointer to the Channel configuration  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value:      None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lEruInit(
  const Icu_17_TimerIp_ChannelConfigType *const LocalIcuChanPtr)
{

  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * MISRA rule.As IGCR register is EndInit protected, the address of EICR
   * register needs to be passed to a MCALLIB api to update. Hence to access
   * the register address the datatype is used. */
  volatile Ifx_SCU_EICR* Ptr;
  uint32 TempVal;
  uint32 Mask;
  uint16 RegValue;
  uint16 HwUsed;
  uint8 Edge;
  uint8 ExisValue;
  uint8 InpValue;
  uint8 EruPos;
  /* Read the Edge configured */
  Edge = LocalIcuChanPtr->IcuProperties.DefaultStartEdge;
  /* To calculate the value passed for FEN and REN setting */
  if(Edge == (uint8)ICU_17_TIMERIP_RISING_EDGE)
  {
    Edge = ICU_ERU_RISING_EDGE;
  }
  else if(Edge == (uint8)ICU_17_TIMERIP_FALLING_EDGE)
  {
    Edge = ICU_ERU_FALLING_EDGE;
  }
  else
  {
    Edge = ICU_ERU_BOTH_EDGE;
  }
  /* Read the HW used from configuration */
  HwUsed = LocalIcuChanPtr->IcuProperties.AssignedHwUnitNumber;
  /* Extract the EXIS and INP value */
  /* [cover parentID={E3419647-188B-4e3d-8F2F-0254A866745D}]
  Extract the ERU input channel used and the OGU used for this channel.
  [/cover] */
  ExisValue =
    (uint8)((HwUsed >> ICU_ERU_EXIS_CHNL_BIT_POS) & ICU_ERU_CHNL_MASK);
  InpValue = (uint8)((HwUsed >> ICU_ERU_OGU_CHNL_BIT_POS) & ICU_ERU_CHNL_MASK);
  /* Populate the register value to write with EXIS, INP, FEN, REN, EIEN */
  RegValue = ((uint16)InpValue << ICU_ERU_INP0_POS);
  RegValue |= ((uint16)ExisValue << ICU_ERU_EXIS0_POS);
  RegValue |= ((uint16)Edge << ICU_ERU_FEN_0_POS);
  RegValue |= (uint16)ICU_ASSERT_EIEN;
  /* Get the Eicr register to be updated */
  Ptr =
    &(MODULE_SCU.EICR[(HwUsed & ICU_ERU_CHNL_MASK) / ICU_ERU_CHNL_PAIR_COUNT]);

  /* Get the Pos of Eicr register to be updated and the mask required.*/
  EruPos = (uint8)(((HwUsed % ICU_ERU_CHNL_PAIR_COUNT) == 0U) ? \
                   ICU_EICR_LOWER_HALF_OFFSET : ICU_EICR_UPPER_HALF_OFFSET);
  Mask = (((HwUsed % ICU_ERU_CHNL_PAIR_COUNT) == 0U) ? \
          ICU_EICR_LOWER_HALF_MASK : ICU_EICR_UPPER_HALF_MASK);

  /* Prepare the register value to write */
  TempVal = (uint32)RegValue << EruPos;
  /* [cover parentID={8B697CD7-69E8-4d39-A6B6-C868C1DFEAEB}]
    Hardware register access.
  [/cover] */
  /* Update EICR register */
  /* [cover parentID={A8FE7658-3C94-44c6-96E4-86E5A17BC787}]
  Update the EICR register's upper or lower half depending on the ERU channel
  used with Input channel, Edge and OGU unit used.
  [/cover] */
  ICU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREGMASK(&(Ptr->U), TempVal, Mask);
}
#endif

#if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
(ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {02332661-1F1A-40c2-A0E3-DC7878F36C8F}]     **
**                                                                            **
** Syntax : static uint32 Icu_lNotifiDetCheck(                                **
**                             const Icu_17_TimerIp_ChannelType Channel,      **
**                             const uint8 ServiceId ,                        **
**                             const Icu_17_TimerIp_MeasurementModeType Mode, **
**                             const uint8 CoreId                             **
**                             const uint8 SleepModeChk                       **
**                                 )                                          **
**                                                                            **
** Description :     Local function :Service for DET check in  APIs where     **
**                    the API can be configured for only one Mode             **
**                    Used across all Timestamp and EdgeCount API's           **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        None                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Reentrant                                               **
**                                                                            **
** Parameters (in):   Channel - Numeric identifier of the ICU channel         **
**                    ServiceId - Id of the API                               **
**                    Mode - Measurement Mode                                 **
**                    CoreId - Core in which function is called.              **
**                    SleepModeChk - Flag to indicate if SLEEP mode check is  **
**                                   needed.                                  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value:   uint32: status of DET. ICU_ERROR_NOT_FOUND/ICU_ERROR_FOUND **
**                                                                            **
*******************************************************************************/
static uint32 Icu_lNotifiDetCheck(
  const Icu_17_TimerIp_ChannelType Channel,
  const uint8 ServiceId,
  const Icu_17_TimerIp_MeasurementModeType Mode,
  const uint8 CoreId,
  const uint8 SleepModeChk)
{
  uint32 ErrorFlag;

  /* Verify whether Init has been called */
  /* [cover parentID={7E0403EA-B6BE-4ad5-83D0-1025BFF8E2F1}]
  Check if init call is made
  [/cover] */
  ErrorFlag = Icu_lInitCallVerify(ServiceId, CoreId);
  /* [cover parentID={909DF169-CC09-462f-ACB0-FCE9492259C4}]
  Is init call made?
  [/cover] */
  if (ErrorFlag != ICU_ERROR_FOUND)
  {
    /* if UNINIT occurred then Icu_17_TimerIp_ConfigPtr is not valid.
     * So need not to check for other DET errors */
    /* Verify whether Invalid channel number has been sent */
    /* [cover parentID={F31BF0B3-6C6A-4e6d-8009-50B28B4949FE}]
    Check if the channel is valid
    [/cover] */
    ErrorFlag = Icu_lChannelVerify(ServiceId, Channel, CoreId);
    /* [cover parentID={9174407A-B2AF-4638-A17D-6BF7F7F64E69}]
    Is the channel valid?
    [/cover] */
    if (ErrorFlag != ICU_ERROR_FOUND)
    {
      /* [cover parentID={8C33B428-C7CE-42ff-A442-B9340740F8E7}]
      Check if the channel mode and the requested mode is same.
      [/cover] */
      ErrorFlag = Icu_lChannelCheckMode(ServiceId, Channel, Mode, CoreId,
                                                                  SleepModeChk);
    }
  }

  return (ErrorFlag);
} /* End of Icu_lNotifiDetCheck() function */
#endif

#if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
(ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {0066A50D-D2A8-4cfd-8867-9F52FE8E781B}]     **
**                                                                            **
** Syntax :  static  uint32 Icu_lInitCallVerify(                              **
**                                    const uint8 ServiceId,                  **
**                                    const uint8 CoreId)                     **
**                                                                            **
** Description :      Local function :Service to verify whether Init has been **
**                                    called or report DET error              **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        None                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Reentrant                                               **
**                                                                            **
** Parameters (in):   ServiceId - API Service Id number                       **
**                    CoreId - Core in which api is called                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value:   uint32: status of DET. ICU_ERROR_NOT_FOUND/ICU_ERROR_FOUND **
**                                                                            **
*******************************************************************************/
static uint32 Icu_lInitCallVerify(const uint8 ServiceId, const uint8 CoreId)
{
  uint8 ErrorFlag;
  uint8 CoreIndex;
  ErrorFlag = (uint8)ICU_ERROR_NOT_FOUND;
  /* Verify whether Init had been called,
      before calling Icu_17_TimerIp_DeInit()function */
  CoreIndex = (CoreId * (uint8)(ICU_INIT_STAUS_SIZE));
  /* [cover parentID={7E20E6B7-962E-45c9-8C26-FF93089F0639}]
  Is the core specific bit set in the global initialization status variable?
  [/cover] */
  if(ICU_INITIALIZED !=
      (Mcal_GetBitAtomic(Icu_17_TimerIp_InitStatus, \
                         ((sint32)(CoreIndex)), ICU_INIT_STAUS_SIZE)))
  {
    /* [cover parentID={699C6B3B-D861-4453-AFC3-B7CF1E025F39}]
    Report an Error indicating that inittialisation is not done.
    [/cover] */
    Icu_lReportError(
      ServiceId,
      ICU_17_TIMERIP_E_UNINIT
    );/* End of report error */
    ErrorFlag = (uint8)ICU_ERROR_FOUND;
  }
  return (ErrorFlag);
}/* End of Icu_lInitCallVerify() function */
#endif

#if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
(ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {89552A3F-AC4F-4b01-8AC9-E249BF58AA38}]     **
**                                                                            **
** Syntax :   static uint32 Icu_lChannelVerify(                               **
**                              const uint8 ServiceId,                        **
**                              const Icu_17_TimerIp_ChannelType Channel,     **
**                              const uint8 CoreId)                           **
**                                                                            **
** Description :      Local function :Service to verify whether proper        **
**                                    channel has been passed or              **
**                                    raise an error                          **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        None                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Reentrant                                               **
**                                                                            **
** Parameters (in):   ServiceId - API Service Id number                       **
**                    Channel - Channel number to verify                      **
**                    CoreId - Core in which function is called.              **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value:   uint32: status of DET. ICU_ERROR_NOT_FOUND/ICU_ERROR_FOUND **
**                                                                            **
*******************************************************************************/
static uint32 Icu_lChannelVerify(
  const uint8 ServiceId,
  const Icu_17_TimerIp_ChannelType Channel,
  const uint8 CoreId)
{
  uint32 ErrorFlag;
  #if ((ICU_17_TIMERIP_MULTICORE_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON))
  uint8 ExtractCoreId;
  #endif
  ErrorFlag = (uint32)ICU_ERROR_NOT_FOUND;
  /* Verify whether Invalid channel number has been sent */
  /* [cover parentID={A389BA07-97D3-45eb-9D9C-AD2970B5EDEF}]
  If invalid channel number has been sent
  [/cover] */
  if (Channel >= ((Icu_17_TimerIp_ChannelType) ICU_17_TIMERIP_MAX_CHANNELS ))
  {
    /* [cover parentID={3C0FDC6E-D05C-49ee-828C-305DD0BB37B9}]
    Report an error indicating invalid channel.
    [/cover] */
    Icu_lReportError(
      ServiceId,
      ICU_17_TIMERIP_E_PARAM_CHANNEL
    );/* End of report Error */
    ErrorFlag = (uint32)ICU_ERROR_FOUND;
  }
  /* [cover parentID={39A8D98D-2855-41b6-B6D0-95E48E66F8BC}]
  If Multicore error detect or Safety enable is on
  [/cover] */
  #if ((ICU_17_TIMERIP_MULTICORE_ERROR_DETECT == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON))
  else /* Channel is a valid channel */
  {
    #if (ICU_17_TIMERIP_SINGLE_CORE == STD_OFF)
    ExtractCoreId = \
        (uint8)((Icu_17_TimerIp_ConfigPtr->ChannelMapping[Channel] &
        (ICU_CHNL_MAP_CORE_ID_MASK)) >> ICU_CHNL_MAP_CORE_ID_OFFSET);
    #else
    ExtractCoreId = ICU_17_TIMERIP_SINGLE_CORE_ID;
    #endif
    /* Check if a channel is assigned to this core */
    /* [cover parentID={9B0821BB-1A56-4035-A89F-243A92D4759E}]
    Is the extracted core id and invoked core id same?
    [/cover] */
    if(ExtractCoreId != CoreId)
    {
      /* [cover parentID={B0C4FBD6-BD5B-45a4-9E0F-C52AFF1F36AE}]
      Report an error indicating that the channel is not allocated to current
      core.
      [/cover] */
      Icu_lReportMulticoreError(
        ServiceId,
        ICU_17_TIMERIP_E_CORE_CHANNEL_MISMATCH
      );/* End of report Error */
      ErrorFlag = (uint32)ICU_ERROR_FOUND;
    }
  }
  #else
  UNUSED_PARAMETER(CoreId);
  #endif
  return (ErrorFlag);
}/* End of Icu_ChannelVerify()*/
#endif

#if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON)|| \
(ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {4EF986CF-436E-4bae-AD60-7DEE796C1358}]     **
**                                                                            **
** Syntax :    LOCAL_INLINE uint32 Icu_lChannelCheckMode(                     **
**                           const uint8 ServiceId,                           **
**                           const Icu_17_TimerIp_ChannelType Channel         **
**                           const Icu_17_TimerIp_MeasurementModeType Mode,   **
**                                 const uint8 CoreId,                        **
**                             const uint8 SleepModeChk)                      **
** Description :     Local function :Service to verify whether proper channel **
**                     in proper mode has been passed or raise an error       **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        None                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Reentrant                                               **
**                                                                            **
** Parameters (in):   ServiceId - API Service Id number                       **
**                    Channel - Channel number to verify                      **
**                    Mode - Kind of Measurement that channel supports        **
**                    SleepModeChk - Flag to indicate if SLEEP mode check is  **
**                                   needed.                                  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value:   uint32: status of DET. ICU_ERROR_NOT_FOUND/ICU_ERROR_FOUND **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Icu_lChannelCheckMode(
  const uint8 ServiceId,
  const Icu_17_TimerIp_ChannelType Channel,
  const Icu_17_TimerIp_MeasurementModeType Mode,
  const uint8 CoreId,
  const uint8 SleepModeChk)
{
  const Icu_17_TimerIp_ChannelConfigType *DetLocalPtr;
  uint8 CoreChannelIndex;
  uint32 ErrorFlag;
  #if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  Icu_17_TimerIp_ModeType IcuMode;
  #endif
  ErrorFlag = (uint32)ICU_ERROR_NOT_FOUND;
  CoreChannelIndex = Icu_lGetCoreChIndex((uint8)Channel);
  /* Initialize local pointer to first configured channel structure */
  DetLocalPtr = &((Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->
                                           ChannelConfigPtr)[CoreChannelIndex]);
  /* [cover parentID={50A6D48F-A5D4-4982-9AD3-F24EE58CFA17}]
  Is configured measurement mode and requested measurement mode same?
  [/cover] */
  if ((uint32)Mode != DetLocalPtr->IcuProperties.MeasurementMode)
  {
    /* [cover parentID={DE261D44-6003-46fb-9843-06AA1D10D865}]
    Report an error that the channel is not valid as the configured mode is
    not matching.
    [/cover] */
    Icu_lReportError(
      ServiceId,
      ICU_17_TIMERIP_E_PARAM_CHANNEL
    );/* End of report Error */
    ErrorFlag = (uint32)ICU_ERROR_FOUND;
  }
  /* [cover parentID={D5099364-3D58-49bc-A67A-3EA6F1E00701}]
  If safety enable is on
  [/cover] */
  #if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  /*Read ICU Mode*/
  IcuMode = Icu_17_TimerIp_Varlist[CoreId]->GlobalMode;
  /* [cover parentID={3143B838-0ECC-484a-B907-12C9A6C1B514}]
  Is Sleep mode check needed and ICU measurement mode sleep and no previous
  error?
  [/cover] */
  if((ICU_17_TIMERIP_MODE_SLEEP == IcuMode) && (ErrorFlag != ICU_ERROR_FOUND)
    && (ICU_FLAG_SET == SleepModeChk))
  {
    /* [cover parentID={CFC2491C-CCB0-4004-AC0D-E6B4F761BCE3}]
     Report an Safety error that the ICU mode is not valid.
     [/cover] */
    Mcal_ReportSafetyError(
      ICU_17_TIMERIP_MODULE_ID,
      ICU_17_TIMERIP_INSTANCE_ID, ServiceId,
      ICU_17_TIMERIP_E_INVALID_MODE);/* End of report to Safety */
    ErrorFlag = (uint32) ICU_ERROR_FOUND;
  }
  #else
    UNUSED_PARAMETER(SleepModeChk);
  #endif

  return (ErrorFlag);
}/* End of Icu_ChannelCheckMode */
#endif

#if (ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON)
#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {F151B823-E044-4264-B36F-3F7C41D412EF}]     **
**                                                                            **
** Syntax : LOCAL_INLINE void Icu_lGtmResetEdgeCount  (                       **
**                            const uint16 GlobalChannelNumber,               **
**                            uint32 *const EdgeCountValuePtr)                **
**                                                                            **
** Description :     Function to reset the Edge Count value captured by the   **
**                   channel                                                  **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  GlobalChannelNumber - Channel Number                     **
**                   EdgeCountValuePtr -Stores the edge counter value at      **
**                   previous enable                                          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lGtmResetEdgeCount(
  const uint16 GlobalChannelNumber,
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * MISRA rule,To implement efficiently IcuMeasaurementProperty as a post-build
   * parameter.Union is required*/
  Icu_17_TimerIp_ChannelData *const EdgeCountValuePtr)
{
  /* Structure to get Module info  */
  Ifx_GTM_TIM_CH* TimChannelRegPtr;   /* Pointer to TIM Channel Reg    */
  uint8 ModuleNo;                            /* Holds the TIM module Number   */
  uint8 ChannelNo;                           /* Holds the TIM Channel Number  */

  /* Calculate Module Id of the TIM channel */
  ModuleNo = (uint8)((GlobalChannelNumber / ICU_GTM_CHANNELS_PER_TIM_MODULE) \
                     & ICU_GTM_MODULE_NO_MSK);
  /* Calculate Channel number of the TIM channel */
  ChannelNo = (uint8)(GlobalChannelNumber % ICU_GTM_CHANNELS_PER_TIM_MODULE);

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TimChannelRegPtr = GTM_TIM_CH_POINTER(ModuleNo, ChannelNo);
  /* Reset the previous Edge Count value */
  EdgeCountValuePtr->EdgeCountParas.EdgeCounter = 0UL;
  /* Enter the critical section to avoid missing any edges or receiving
   * additional edges if the below section is pre-empted */
  /* [cover parentID={9DCA2880-C870-4e9c-95DF-FDB31942C65D}]
    Critical section.
  [/cover] */
  /* [cover parentID={609CFF44-5FA4-450e-91D9-7530C62629F9}]
  Enter critical section
  [/cover] */
  SchM_Enter_Icu_17_TimerIp_ResetEdgeCount();
  {
    /* [cover parentID={B1FA857F-14E8-41b5-AD77-DC7E6F0AA35E}]
    Is the TIM channel enabled?
    [/cover] */
    if((TimChannelRegPtr->CTRL.U & ICU_GTM_TIM_ENABLE_CHANNEL) !=
        (uint32)0UL)
    {
      /* [cover parentID={AC16B2D8-4E94-4dd9-AE8F-5719FC8E617E}]
      Disable and re-enable the TIM channel.
      [/cover] */
      /* Channel is enabled, disable and enable */
      Mcal_SetBitAtomic(&TimChannelRegPtr->CTRL.U, ICU_GTM_TIM_EN_POS,
                        ICU_GTM_TIM_EN_LEN, (uint32)0U);
      Mcal_SetBitAtomic(&TimChannelRegPtr->CTRL.U, ICU_GTM_TIM_EN_POS,
                        ICU_GTM_TIM_EN_LEN, (uint32)1U);
    }
    else
    {
      /* [cover parentID={DC6E0A7D-1688-419a-8844-2F48D4B02A10}]
      Enable and disable the TIM channel.
      [/cover] */
      /* Channel is disabled, enable and disable */
      Mcal_SetBitAtomic(&TimChannelRegPtr->CTRL.U, ICU_GTM_TIM_EN_POS,
                        ICU_GTM_TIM_EN_LEN, (uint32)1U);
      Mcal_SetBitAtomic(&TimChannelRegPtr->CTRL.U, ICU_GTM_TIM_EN_POS,
                        ICU_GTM_TIM_EN_LEN, (uint32)0U);
    }
    /*[/cover] */
  }
  /* [cover parentID={C16072E9-8925-47a5-B62E-2FAB0EFE0FC6}]
  Exit critical section
  [/cover] */
  /*Exit from the critical section */
  SchM_Exit_Icu_17_TimerIp_ResetEdgeCount();
  /* Set the edge counter variable to 0-HW Counts */
  /* [cover parentID={FDA6F268-7592-45e5-BF3E-66CC6BD9792B}]
  Set the edge counter variable 0 - HW Counts
  [/cover] */
  EdgeCountValuePtr->EdgeCountParas.EdgeCounter =
                                                 0U - (TimChannelRegPtr->CNT.U);
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer TimChannelRegPtr is
   * accessed using assembly instruction. */
}
#endif
#endif
#if (ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON)
#if (ICU_17_TIMERIP_GPT12_USED == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {B7D6756E-15BF-4716-8260-5F838803FB7F}]     **
**                                                                            **
** Syntax : LOCAL_INLINE void Icu_lGpt12ResetEdgeCount  (                     **
**                            const uint16 GlobalChannelNumber,               **
**                            uint32 *const EdgeCountValuePtr)                **
**                                                                            **
** Description :     Function to reset the Edge Count value captured by a     **
**                   GPT12 Timer channel                                      **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  GlobalChannelNumber - Channel Number                     **
**                                                                            **
** Parameters (out): EdgeCountValuePtr - Stores the edge count value address  **
**                                       which will be cleared                **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lGpt12ResetEdgeCount(
  const uint16 GlobalChannelNumber,
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * MISRA rule,To implement efficiently IcuMeasaurementProperty as a post-build
   * parameter.Union is required*/
  Icu_17_TimerIp_ChannelData *const EdgeCountValuePtr)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
    MISRA rule. Union usage is required to access SFR data type and implement
    efficiently for accessing Timer registers */
  /* GPT12 Tx Register pointer to access T2...T6 */
  volatile Ifx_GPT12_T2* Gpt12TxRegPtr;
  Ifx_GPT12* Gpt12BasePtr;
  uint8 ChannelNo;                              /* Holds the GPT12 Tx Number  */

  /* Extract Channel Number */
  ChannelNo = (uint8)GlobalChannelNumber & ICU_LOWER_NIBBLE;
  Gpt12BasePtr = &MODULE_GPT120;
  Gpt12TxRegPtr = &(Gpt12BasePtr->T2);
  Gpt12TxRegPtr = &(Gpt12TxRegPtr[ChannelNo]);
  /* [cover parentID={029542F6-B9D1-44dc-B837-27C7442EFC95}]
  Reset Edge Counter value and GPT12 HW Count
  [/cover] */
  /* Reset the previous Edge Count value */
  EdgeCountValuePtr->EdgeCountParas.EdgeCounter = 0UL;
  /* Reset the GPT12 Tx Register */
  Gpt12TxRegPtr->U = 0UL;
}
#endif
#endif

#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) && \
(ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {E825EF3C-CDD8-46b8-9AD3-C864856E4CF3}]     **
**                                                                            **
** Syntax : LOCAL_INLINE void Icu_lGtmEnableEdgeCount  (                      **
**                      const uint16 GlobalChannelNumber,                     **
**                      uint32 *const EdgeCountValuePtr)                      **
**                                                                            **
** Description :     Function to enable the TIM channel to start counting     **
**                   edges. The previous edge count value is updated in the   **
**                   location given by EdgeCountValuePtr. TIM channel must be **
**                   in the disabled state before calling this function.      **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  GlobalChannelNumber - Channel Number                     **
**                                                                            **
** Parameters (in-out): EdgeCountValuePtr -Stores the edge counter value at   **
**                   previous enable                                          **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lGtmEnableEdgeCount(
  const uint16 GlobalChannelNumber,
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * MISRA rule,To implement efficiently IcuMeasaurementProperty as a post-build
   * parameter.Union is required*/
  Icu_17_TimerIp_ChannelData *const EdgeCountValuePtr)
{
  /* Structure to get Module info  */
  Ifx_GTM_TIM_CH* TimChannelRegPtr;   /* Pointer to TIM Channel Reg    */
  uint8 ModuleNo;                            /* Holds the TIM module Number   */
  uint8 ChannelNo;                           /* Holds the TIM Channel Number  */
  uint32 TimCntRegVal;                       /* Holds the TIM CNT value  */

  /* Calculate Module Id of the TIM channel */
  ModuleNo = (uint8)((GlobalChannelNumber / ICU_GTM_CHANNELS_PER_TIM_MODULE) \
                     & ICU_GTM_MODULE_NO_MSK);
  /* Calculate Channel number of the TIM channel */
  ChannelNo = (uint8)(GlobalChannelNumber % ICU_GTM_CHANNELS_PER_TIM_MODULE);

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TimChannelRegPtr = GTM_TIM_CH_POINTER(ModuleNo, ChannelNo);
  /* [cover parentID={6C0DB8B9-8818-4367-8447-7CF3AF1BDF9E}]
  Critical section
  [/cover] */
  SchM_Enter_Icu_17_TimerIp_GtmEnableEdgeCount();
  /* [cover parentID={E275864A-E202-44b4-9A91-D9191661AB48}]
  Increment the SW edge counter by amount of HW counter
  [/cover] */
  /* Store the current Edge counter value */
  TimCntRegVal = TimChannelRegPtr->CNT.U;
  EdgeCountValuePtr->EdgeCountParas.EdgeCounter += TimCntRegVal;
  /* [cover parentID={4806FE55-8CDB-48d0-B8B9-DE9FF03F4C7A}]
  Clear any pending interrupts and enable CNTOFL interrupt.
  [/cover] */
  /* Clear all pending interrupts */
  TimChannelRegPtr->IRQ.NOTIFY.U = ICU_GTM_CLEAR_INTERRUPTS;
  /* Enable the CNT overflow interrupt */
  TimChannelRegPtr->IRQ.EN.U |= (1UL << ICU_GTM_TIM_CNTOFL_IRQ);
  /* [cover parentID={A9F320D6-FB53-4d00-98B9-A721E0973EF0}]
  Enable the TIM channel.
  [/cover] */
  TimChannelRegPtr->CTRL.U |= ICU_GTM_TIM_ENABLE_CHANNEL ;
  SchM_Exit_Icu_17_TimerIp_GtmEnableEdgeCount();
}
#endif


#if ((ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON) || \
(ICU_17_TIMERIP_INCREMENTAL_INTERFACE_API == STD_ON)) && \
(ICU_17_TIMERIP_GPT12_USED == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {2EBB1E35-D106-4a0f-8ED6-6667CD21F9F8}]     **
**                                                                            **
** Syntax : LOCAL_INLINE void Icu_lGpt12EnableEdgeCount  (                    **
**                      const uint16 GlobalChannelNumber)                     **
**                                                                            **
** Description :     Function to enable the GPT12 channel to start counting   **
**                   edges. The previous edge count value is updated in the   **
**                   location given by EdgeCountValuePtr. GPT12 timer must be **
**                   in the disabled state before calling this function.      **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  GlobalChannelNumber - Channel Number                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lGpt12EnableEdgeCount(
  const uint16 GlobalChannelNumber)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
    MISRA rule. Union usage is required to access SFR data type and implement
    efficiently for accessing Timer registers */
  volatile Ifx_GPT12_T2CON* Gpt12TxConRegPtr;
  Ifx_GPT12* Gpt12BasePtr;
  uint8 ChannelNo;                              /* Holds the GPT12 Tx Number  */

  /* Extract Channel Number */
  ChannelNo = (uint8)GlobalChannelNumber & ICU_LOWER_NIBBLE;

  Gpt12BasePtr = &MODULE_GPT120;
  Gpt12TxConRegPtr = &(Gpt12BasePtr->T2CON);
  Gpt12TxConRegPtr = &(Gpt12TxConRegPtr[ChannelNo]);

  /* Enable the timer */
  Mcal_SetBitAtomic( \
                     Gpt12TxConRegPtr, (sint32)ICU_GPT12_TXCON_TXR_POS, \
                     ICU_GPT12_TXCON_TXR_LEN, (uint32)ICU_GPT12_TX_RUN);
  /* MISRA2012_RULE_2_2_JUSTIFICATION: No side effects foreseen
       * by violating this MISRA rule, as the variable Gpt12TxConRegPtr is
       * accessed using assembly instruction. */
}
#endif

#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) && \
((ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON) || \
 (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON))
/*******************************************************************************
** Traceability: [cover parentID= {5A3FE84F-5B91-4166-A287-AFF94147BCEA}]     **
**                                                                            **
** Syntax : static void Icu_lGtmDisableChnIrq  (                              **
**                            const uint16 GlobalChannelNumber)               **
**                                                                            **
** Description :     Function to disable the TIM channel from counting edges  **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  GlobalChannelNumber - Channel Number                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lGtmDisableChnIrq(
  const uint16 GlobalChannelNumber)
{
  /* Structure to get Module info  */
  Ifx_GTM_TIM_CH* TimChannelRegPtr;   /* Pointer to TIM Channel Reg    */
  uint8 ModuleNo;                            /* Holds the TIM module Number   */
  uint8 ChannelNo;                           /* Holds the TIM Channel Number  */


  /* Calculate Module Id of the TIM channel */
  ModuleNo = (uint8)((GlobalChannelNumber / ICU_GTM_CHANNELS_PER_TIM_MODULE) \
                     & ICU_GTM_MODULE_NO_MSK);
  /* Calculate Channel number of the TIM channel */
  ChannelNo = (uint8)(GlobalChannelNumber % ICU_GTM_CHANNELS_PER_TIM_MODULE);

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TimChannelRegPtr = GTM_TIM_CH_POINTER(ModuleNo, ChannelNo);
  /* Disable TIM channel */
  TimChannelRegPtr->CTRL.U &= ~ICU_GTM_TIM_ENABLE_CHANNEL ;
}
#endif

#if ((ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON) || \
(ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON) || \
(ICU_17_TIMERIP_INCREMENTAL_INTERFACE_API == STD_ON)) && \
(ICU_17_TIMERIP_GPT12_USED == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {554AA114-E8D7-4334-9BA7-4A362DEAB54E}]     **
**                                                                            **
** Syntax : static void Icu_lGpt12DisableChannel  (                           **
**                            const uint16 GlobalChannelNumber)               **
**                                                                            **
** Description :     Function to disable the GPT12 timer from counting edges  **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  GlobalChannelNumber - Channel Number                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
static void Icu_lGpt12DisableChannel(
  const uint16 GlobalChannelNumber)
{
  uint8 ChannelNo;                              /* Holds the GPT12 Tx Number  */
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
    MISRA rule. Union usage is required to access SFR data type and implement
    efficiently for accessing Timer control registers */
  volatile Ifx_GPT12_T2CON* Gpt12TxConRegPtr;
  Ifx_GPT12* Gpt12BasePtr;

  /* Extract Channel Number */
  ChannelNo = (uint8)GlobalChannelNumber & ICU_LOWER_NIBBLE;
  Gpt12BasePtr = &MODULE_GPT120;
  Gpt12TxConRegPtr = &(Gpt12BasePtr->T2CON);
  Gpt12TxConRegPtr = &(Gpt12TxConRegPtr[ChannelNo]);
  /* Disable the timer */
  Mcal_SetBitAtomic( \
                     Gpt12TxConRegPtr, (sint32)ICU_GPT12_TXCON_TXR_POS, \
                     ICU_GPT12_TXCON_TXR_LEN, (uint32)0);
  /* MISRA2012_RULE_2_2_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the variable Gpt12TxConRegPtr is
   * accessed using assembly instruction. */
}
#endif

#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) && \
(ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {F65ACEB1-EDC2-4479-9077-1E2BAE250FF5}]     **
**                                                                            **
** Syntax : LOCAL_INLINE Icu_17_TimerIp_EdgeNumberType Icu_lGtmGetEdgeNumbers(**
**                      const uint16 GlobalChannelNumber,                     **
**             const Icu_17_TimerIp_EdgeNumberType* const  EdgeCountValuePtr) **
**                                                                            **
** Description :     Function to return the Edge count as scanned by the      **
**                   channel                                                  **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  GlobalChannelNumber - Channel Number                     **
**                   EdgeCountValuePtr -Stores the edge counter value at      **
**                   previous enable                                          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:  Icu_17_TimerIp_EdgeNumberType : Edge counter value          **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Icu_17_TimerIp_EdgeNumberType Icu_lGtmGetEdgeNumbers(
  const uint16 GlobalChannelNumber,
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * MISRA rule,To implement efficiently IcuMeasaurementProperty as a post-build
   * parameter.Union is required*/
  const Icu_17_TimerIp_ChannelData* const EdgeCountValuePtr)
{
  /* Structure to get Module info  */
  const Ifx_GTM_TIM_CH *TimChannelRegPtr;    /* Pointer to TIM Channel Reg    */
  uint8 ModuleNo;                            /* Holds the TIM module Number   */
  uint8 ChannelNo;                           /* Holds the TIM Channel Number  */
  uint32 SwEdgeCount1;                       /* Holds the SW Edge Number      */
  uint32 SwEdgeCount2;                       /* Holds the SW Edge Number      */
  uint32 HwEdgeCount;                        /* Holds the HW Edge Number      */
  /* Calculate Module Id of the TIM channel */
  ModuleNo = (uint8)((GlobalChannelNumber / ICU_GTM_CHANNELS_PER_TIM_MODULE) \
                     & ICU_GTM_MODULE_NO_MSK);
  /* Calculate Channel number of the TIM channel */
  ChannelNo = (uint8)(GlobalChannelNumber % ICU_GTM_CHANNELS_PER_TIM_MODULE);

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TimChannelRegPtr = GTM_TIM_CH_POINTER(ModuleNo, ChannelNo);

  /*Safety check added for edge counter safety measure*/
  /* [cover parentID={5BE6F816-1873-422e-81D9-88E19943ACCC}]
  Read SW Edge Counter Value1
  [/cover] */
  SwEdgeCount1 = (EdgeCountValuePtr->EdgeCountParas.EdgeCounter);
  /* [cover parentID={6633EF2A-5063-471f-9B90-48690612A104}]
  Read Hardware Edge Counter Value
  [/cover] */
  HwEdgeCount = (TimChannelRegPtr->CNT.U);
  /* [cover parentID={95DE7338-84C3-45e4-AE78-9DE376F8AB0E}]
  Read SW Edge Counter Value2
  [/cover] */
  SwEdgeCount2 = (EdgeCountValuePtr->EdgeCountParas.EdgeCounter);
  /* [cover parentID={90FCD789-0ADF-4a3d-932C-F6C61AADD8BC}]
  Check if SW Edge Count value 1 and value 2 are not same.
  [/cover] */
  if(SwEdgeCount1 != SwEdgeCount2)
  {
    /* [cover parentID={02FC9600-DBCA-48ec-99AA-AE570DEB4F1B}]
    Read Hardware Edge Counter Value
    [/cover] */
    HwEdgeCount = (TimChannelRegPtr->CNT.U);
  }
  /* [cover parentID={6EA7A7D4-732D-4f35-A865-BACFE818D953}]
  Return Edge Number Value (HW+SW counts)
  [/cover] */
  return(SwEdgeCount2 + HwEdgeCount);
}
#endif

#if (ICU_17_TIMERIP_GPT12_USED == STD_ON) && \
(ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {4977A716-7923-4774-97B7-6CEA0FD25426}]     **
**                                                                            **
** Syntax : static Icu_17_TimerIp_EdgeNumberType Icu_lGpt12GetEdgeNumbers  (  **
**                      const uint16 GlobalChannelNumber,                     **
**               const Icu_17_TimerIp_EdgeNumberType* const EdgeCountValuePtr)**
**                                                                            **
** Description :     Function to return the Edge count as scanned by the      **
**                   channel                                                  **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  GlobalChannelNumber - Channel Number                     **
**                   EdgeCountValuePtr -Stores the edge counter value at      **
**                   previous enable                                          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:  Icu_17_TimerIp_EdgeNumberType : Edge counter value          **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Icu_17_TimerIp_EdgeNumberType Icu_lGpt12GetEdgeNumbers(
  const uint16 GlobalChannelNumber,
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * MISRA rule,To implement efficiently IcuMeasaurementProperty as a post-build
   * parameter.Union is required*/
  const Icu_17_TimerIp_ChannelData* const EdgeCountValuePtr)
{
  uint8 ChannelNo; /* Holds the GPT12 Tx Number  */
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
    MISRA rule. Union usage is required to access SFR data type and implement
    efficiently for accessing Timer registers */
  volatile Ifx_GPT12_T2* Gpt12TxRegPtr;
  Ifx_GPT12* Gpt12BasePtr;
  uint32 SwEdgeCount1; /* Holds the SW Edge Number      */
  uint32 SwEdgeCount2; /* Holds the SW Edge Number      */
  uint32 HwEdgeCount; /* Holds the HW Edge Number      */

  /* Extract Channel Number */
  ChannelNo = (uint8) GlobalChannelNumber & ICU_LOWER_NIBBLE;
  Gpt12BasePtr = &MODULE_GPT120;
  Gpt12TxRegPtr = &(Gpt12BasePtr->T2);
  Gpt12TxRegPtr = &(Gpt12TxRegPtr[ChannelNo]);

  /*Safety check added for edge counter safety measure*/
  /* [cover parentID={24E8E5BD-AF6D-4bbb-97D2-71992E84950E}]
   Read SW Edge Counter Value1
   [/cover] */
  SwEdgeCount1 = (EdgeCountValuePtr->EdgeCountParas.EdgeCounter);
  /* [cover parentID={6957E762-F340-4b78-906D-55F8F4942E5D}]
   Read Hardware Edge Counter Value
   [/cover] */
  HwEdgeCount = Gpt12TxRegPtr->U;
  /* [cover parentID={93BCDA0A-7EF6-4c44-90F1-9AEB890766D4}]
   Read SW Edge Counter Value2
   [/cover] */
  SwEdgeCount2 = (EdgeCountValuePtr->EdgeCountParas.EdgeCounter);
  /* [cover parentID={86419244-ED4A-49dd-B12C-EAA7F5841553}]
   Check if SW Edge Count value 1 and value 2 are not same.
   [/cover] */
  if (SwEdgeCount1 != SwEdgeCount2)
  {
    /* [cover parentID={775F5F96-40A5-4406-8BA9-B776708EE188}]
     Read Hardware Edge Counter Value
     [/cover] */
    HwEdgeCount = Gpt12TxRegPtr->U;
  }
  /* [cover parentID={B984DFA4-D94E-4061-9455-BA7BB18E625C}]
   Return Edge Number Value (HW+SW counts)
   [/cover] */
  return (SwEdgeCount2 + HwEdgeCount);
}
#endif

#if (ICU_17_TIMERIP_TIMESTAMP_API == STD_ON)
#if(ICU_17_TIMERIP_DEV_ERROR_DETECT ==  STD_ON) || \
(ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={04C3B064-F4E2-41e0-82C5-6CD63259A28F}]      **
**                                                                            **
** Syntax : LOCAL_INLINE uint32 Icu_lStartTimestampDetCheck(                  **
**              const Icu_17_TimerIp_ValueType *const BufferPtr,              **
**              const uint16 BufferSize)                                      **
**                                                                            **
** Description :      Local function :Service for DET check in                **
**                        Icu_17_TimerIp_StartTimestamp() function            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        None                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Reentrant for different channel                         **
**                                                                            **
** Parameters (in):   BufferPtr - Starting address of Buffer                  **
**                    BufferSize - Size of the Buffer                         **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value:      uint32: status of Error                                 **
**                            ICU_ERROR_NOT_FOUND/ICU_ERROR_FOUND             **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Icu_lStartTimestampDetCheck(
  const Icu_17_TimerIp_ValueType *const BufferPtr,
  const uint16 BufferSize)
{
  uint32 ErrorFlag = ICU_ERROR_NOT_FOUND;




  /* [cover parentID={CC1D127C-C933-442e-8DB5-82C602C88E8D}]
  Is buffer pointer valid?
  [/cover] */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  if (BufferPtr == (Icu_17_TimerIp_ValueType*) NULL_PTR)
  {
    ErrorFlag = ICU_ERROR_FOUND;
    /* [cover parentID={43AF6CEE-E5A7-438f-BEFB-7ED75AE2C2A9}]
    Report an error to indicate invalid pointer.
    [/cover] */
    Icu_lReportError(
      ICU_17_TIMERIP_SID_STARTTIMESTAMP,
      ICU_17_TIMERIP_E_PARAM_POINTER);/* End of report error */
  }
  else
  {
    /*  Check for invalid size */
    /* [cover parentID={6B971D9D-0338-412c-B759-40489407E54C}]
    Is buffer size valid?
    [/cover] */
    if (BufferSize == (uint16) 0U)
    {
      ErrorFlag = ICU_ERROR_FOUND;
      /* [cover parentID={882F1B30-AD12-445f-B26D-1F5FC4A01C18}]
      Report an error to indicate invalid buffer size.
      [/cover] */
      Icu_lReportError(
          ICU_17_TIMERIP_SID_STARTTIMESTAMP,
          ICU_17_TIMERIP_E_PARAM_BUFFER_SIZE); /* Report Error */
    }
  }
  return ErrorFlag;
}/* End of Icu_lStartTimestampDetCheck function*/
#endif
/*(ICU_17_TIMERIP_DEV_ERROR_DETECT ==  STD_ON) || \
    (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON) */
#endif
/* (ICU_17_TIMERIP_TIMESTAMP_API == STD_ON) */





#if (ICU_17_TIMERIP_TIMESTAMP_API == STD_ON) && \
(ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {26B68A15-BFC0-4886-86BB-2D27A25E5525}]     **
**                                                                            **
** Syntax : LOCAL_INLINE void Icu_lGtmStartTimeStamp(                         **
**                      const uint16 GlobalChannelNumber)                     **
**                                                                            **
** Description :     Function to configure a TIM Channel to start  capturing  **
**                   TBU Timestamps whenever an Edge given by "ActiveEdge" is **
**                   detected. The channel must be in the disabled state      **
**                   before calling this function                             **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  GlobalChannelNumber - Channel Number                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lGtmStartTimeStamp(
  const uint16 GlobalChannelNumber)
{
  /* Structure to get Module info  */
  Ifx_GTM_TIM_CH* TimChannelRegPtr;     /* Pointer to TIM Channel Reg    */
  uint8 ModuleNo;                            /* Holds the TIM module Number   */
  uint8 ChannelNo;                           /* Holds the TIM Channel Number  */

  /* Calculate Module Id of the TIM channel */
  ModuleNo = (uint8)((GlobalChannelNumber / ICU_GTM_CHANNELS_PER_TIM_MODULE) \
                     & ICU_GTM_MODULE_NO_MSK);
  /* Calculate Channel number of the TIM channel */
  ChannelNo = (uint8)(GlobalChannelNumber % ICU_GTM_CHANNELS_PER_TIM_MODULE);

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TimChannelRegPtr = GTM_TIM_CH_POINTER(ModuleNo, ChannelNo);
  /* Clear all Pending Interrupts */
  TimChannelRegPtr->IRQ.NOTIFY.U = ICU_GTM_CLEAR_INTERRUPTS;
  /* Enable the Newval IRQ */
  TimChannelRegPtr->IRQ.EN.U     = (1UL << ICU_GTM_TIM_NEWVAL_IRQ);
  /* Enable the TIM channel */
  TimChannelRegPtr->CTRL.U |= ICU_GTM_TIM_ENABLE_CHANNEL ;
}
#endif

#if (ICU_17_TIMERIP_TIMESTAMP_API == STD_ON) && \
    (ICU_17_TIMERIP_CCU6_USED == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={8D987C5C-2C83-48f4-BF2E-91B63DDA821B}]      **
**                                                                            **
** Syntax : LOCAL_INLINE void Icu_lCcuStartTimeStamp(                         **
**                      const uint16 CellUsed,                                **
**                      const uint8 ActiveEdge )                              **
**                                                                            **
** Description :     Function to configure a CCU Channel to start  capturing  **
**                   T12 Timestamps whenever an Edge given by "ActiveEdge" is **
**                   detected. The channel must be in the disabled state      **
**                   before calling this function                             **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  CellUsed - Channel Number                                **
**                   ActiveEdge - Configured Activation edge for the channel  **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lCcuStartTimeStamp(
    const uint16 CellUsed,
    const uint8 ActiveEdge)

{
  volatile Ifx_CCU6 *Ccu6RegPtr; /* Variable to hold the current CCU6 address */
  uint16 CcChannelNumber;    /* To hold the CC channel number */
  uint8 CcuActiveEdge;      /* To hold the CCU equivalent edge */

  /* Upper Nibble of AssignedHwUnitNumber holds the Channel Number */
  CcChannelNumber = (CellUsed & ICU_CCU_GET_COMPARATOR) >> ICU_BRING_TO_BIT_0;

  /* Get the base address of the Kernal */
  Ccu6RegPtr = &(&MODULE_CCU60)[CellUsed & ICU_CCU_GET_KERNEL];

  /* Clear any pending interrupt */
  Ccu6RegPtr->ISR.U = (uint32)(ICU_CCU_CLEAR_INTERRUPT <<
      (CcChannelNumber * (uint8)ICU_CCU_IS_BITS_PER_CHANNEL));

  CcuActiveEdge = Icu_lCcu6GetActiveEdge(ActiveEdge);
  /* Channel is configured to Capture Mode 0 */
  Mcal_SetBitAtomic((&Ccu6RegPtr->T12MSEL.U), \
    (CcChannelNumber * ICU_CCU_MSEL_BITS_PER_CHANNEL), \
    ICU_CCU_MSEL_BITS_PER_CHANNEL, \
    (uint32)(ICU_CCU_CAPTURE_MODE1|CcuActiveEdge));
  /* Enable interrupt for the channel */
  Mcal_SetBitAtomic((&Ccu6RegPtr->IEN.U),\
  (CcChannelNumber * ICU_CCU_IS_BITS_PER_CHANNEL),ICU_CCU_IS_BITS_PER_CHANNEL,\
    (uint32)CcuActiveEdge);
  /* MISRA2012_RULE_2_2_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the variable CcuActiveEdge is
   * accessed using assembly instruction. */
}
#endif

#if (ICU_17_TIMERIP_TIMESTAMP_API == STD_ON) && \
(ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {8E65CB94-0D21-4186-A851-E5D3B25A862B}]     **
**                                                                            **
** Syntax : LOCAL_INLINE void Icu_lGtmStopTimeStamp(                          **
**                      const uint16 GlobalChannelNumber  )                   **
**                                                                            **
** Description :     Function to configure a TIM Channel to stop  capturing   **
**                   TBU Timestamps                                           **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  GlobalChannelNumber - Channel Number                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lGtmStopTimeStamp(
  const uint16 GlobalChannelNumber)
{
  Ifx_GTM_TIM_CH* TimChannelRegPtr;   /* Pointer to TIM Channel Reg    */
  uint8 ModuleNo;                            /* Holds the TIM module Number   */
  uint8 ChannelNo;                           /* Holds the TIM Channel Number  */

  /* Calculate Module Id of the TIM channel */
  ModuleNo = (uint8)((GlobalChannelNumber / ICU_GTM_CHANNELS_PER_TIM_MODULE) \
                     & ICU_GTM_MODULE_NO_MSK);
  /* Calculate Channel number of the TIM channel */
  ChannelNo = (uint8)(GlobalChannelNumber % ICU_GTM_CHANNELS_PER_TIM_MODULE);

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TimChannelRegPtr = GTM_TIM_CH_POINTER(ModuleNo, ChannelNo);
  /* Disable TIM channel */
  TimChannelRegPtr->CTRL.U &= ~ICU_GTM_TIM_ENABLE_CHANNEL ;
  /* Disable IRQ */
  TimChannelRegPtr->IRQ.EN.U = 0UL;
}
#endif

#if (ICU_17_TIMERIP_TIMESTAMP_API == STD_ON) && \
(ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {8A42BB31-1353-42a8-A5E4-BAFAB4F5B8E2}]     **
**                                                                            **
** Syntax : LOCAL_INLINE uint32 Icu_lGtmGetTimeStamp  (                       **
**                            const uint16 GlobalChannelNumber           )    **
**                                                                            **
** Description :     Function to get  the timestamp value captured by the TIM **
**                   Channel                                                  **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  GlobalChannelNumber - Channel Number                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     uint32: Timestamp value                                  **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Icu_lGtmGetTimeStamp(const uint16 CellNum)
{
  /* Structure to get Module info  */
  const Ifx_GTM_TIM_CH* TimChannelRegPtr;    /* Pointer to TIM Channel Reg    */
  uint8 ModuleNo;                            /* Holds the TIM module Number   */
  uint8 ChannelNo;                           /* Holds the TIM Channel Number  */
  uint32 RegGpr0Value;

  /* Calculate Module Id of the TIM channel */
  ModuleNo = (uint8)((CellNum / ICU_GTM_CHANNELS_PER_TIM_MODULE) \
                     & ICU_GTM_MODULE_NO_MSK);
  /* Calculate Channel number of the TIM channel */
  ChannelNo = (uint8)(CellNum % ICU_GTM_CHANNELS_PER_TIM_MODULE);

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TimChannelRegPtr = GTM_TIM_CH_POINTER(ModuleNo, ChannelNo);
  /* Read GPR0 Value to get the Time Stamp */
  RegGpr0Value = (TimChannelRegPtr->GPR0.U & (uint32)ICU_GTM_TIMER_MASK);

  return(RegGpr0Value);

}

#endif
/* TIME_STAMP */

#if (ICU_17_TIMERIP_TIMESTAMP_API == STD_ON) && \
    (ICU_17_TIMERIP_CCU6_USED == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={DFC8AAAA-DC74-47b0-A47D-5EEE362EC959}]      **
**                                                                            **
** Syntax : LOCAL_INLINE uint32 Icu_lCcuGetTimeStamp  (                       **
**                            const uint16 CellUsed                      )    **
**                                                                            **
** Description :     Function to get  the timestamp value captured by the CCU **
**                   Channel                                                  **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  CellUsed - Channel Number                                **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     uint32: Timestamp value                                  **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Icu_lCcuGetTimeStamp(const uint16 CellUsed)
{
  volatile Ifx_CCU6 const *Ccu6RegPtr; /* Variable to hold the current CCU6 address */
  /* MISRA2012_RULE_19_2_JUSTIFICATION: Union based type defintion for SFR
     access. */
  volatile Ifx_CCU6_CC6SR const *CcuSrRegPtr; /* Pointer to SR registers of CCU */
  uint16 CcChannelNumber;    /* To hold the CC channel number */

  /* Get the base address of the Kernel */
  Ccu6RegPtr = &((&MODULE_CCU60)[CellUsed & ICU_CCU_GET_KERNEL]);
  /* Assign SR register base addresses */
  CcuSrRegPtr = &(Ccu6RegPtr->CC6SR[0]);
  /* Upper Nibble of AssignedHwUnitNumber holds the Channel Number */
  CcChannelNumber = ((CellUsed & ICU_CCU_GET_COMPARATOR) >> \
      ICU_BRING_TO_BIT_0);
  return(CcuSrRegPtr[CcChannelNumber].U);
}

#endif
/* TIME_STAMP */

#if ((ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
(ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)) && \
((ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON) || \
 (ICU_17_TIMERIP_TIMESTAMP_API == STD_ON)|| \
  (ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON) || \
  (ICU_17_TIMERIP_INCREMENTAL_INTERFACE_API == STD_ON))
/*******************************************************************************
** Traceability: [cover parentID= {04E18C64-B1E8-4a43-BBC7-1219051D8152}]     **
**                                                                            **
** Syntax : static uint32 Icu_lEnDisNotificationDetCheck(                     **
**                              const Icu_17_TimerIp_ChannelType Channel      **
**                              const uint8 ServiceId                         **
**                              const uint8 CoreId)                           **
**                                                                            **
** Description :      Local function :Service for DET check in                **
**                                   Icu_17_TimerIp_EnableNotification()      **
**                                   Icu_17_TimerIp_DisableNotification()     **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        None                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):   Channel - Numeric identifier of the ICU channel         **
**                    ServiceId - Id of the API                               **
**                    CoreId - Core in which this function is called          **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value:      ErrorFlag (uint32)                                      **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Icu_lEnDisNotificationDetCheck(
  const Icu_17_TimerIp_ChannelType Channel,
  const uint8 ServiceId,
  const uint8 CoreId)
{
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr; /* ROM pointer */
  uint16 CoreChIndex;
  /* Verify any error is there for DET */
  uint32 ErrorFlag;
  #if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  Icu_17_TimerIp_ModeType IcuMode;
  #endif
  /* [cover parentID={32315EF5-82B8-4dea-B9F2-96491DD6200B}]
  Check for initialization related DET
  [/cover] */
  ErrorFlag = Icu_lInitCallVerify(ServiceId, CoreId);
  /* [cover parentID={809C1010-742F-401d-B31A-728FE0758155}]
  Any DET reported
  [/cover] */
  if (ErrorFlag != ICU_ERROR_FOUND)
  {
    /* [cover parentID={9ADBB819-DDCF-435e-B837-75DDE9E8BECB}]
    Verify ICU channel for DET
    [/cover] */
    ErrorFlag = Icu_lChannelVerify(ServiceId, Channel, CoreId);
    /* [cover parentID={9B0C3F7F-8BE3-4351-853E-E24F4A27909A}]
    Any DET reported
    [/cover] */
    if (ErrorFlag != ICU_ERROR_FOUND)
    {
      /* Initialize ICU configured channel ROM pointer */
      CoreChIndex = Icu_lGetCoreChIndex((uint8)Channel);
      LocalIcuChanPtr = &((Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->
                                                ChannelConfigPtr)[CoreChIndex]);
      /* [cover parentID={5D1BC239-42D7-46b3-84B1-B4F5D77B0827}]
       Is channel measurement mode signal measurement?
       [/cover] */
      if (LocalIcuChanPtr->IcuProperties.MeasurementMode
              == (uint32) ICU_17_TIMERIP_MODE_SIGNAL_MEASUREMENT)
      {
        ErrorFlag = ICU_ERROR_FOUND;
        /* [cover parentID={E6C47DA7-D1A5-4273-BE78-75BCE4C6C792}]
         Report DET indicating invalid channel.
         [/cover] */
        Icu_lReportError(ServiceId,
                         ICU_17_TIMERIP_E_PARAM_CHANNEL);
      }
    }
  }
  /* [cover parentID={36CE1D3E-006C-4e0d-9167-CEF99253891A}]
  If safety enable is on
  [/cover] */
  #if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  if(ErrorFlag != ICU_ERROR_FOUND)
  {
    /*Read ICU Mode*/
    IcuMode = Icu_17_TimerIp_Varlist[CoreId]->GlobalMode;
    /* [cover parentID={EF318C2E-812B-4f13-A982-1D06E8917DA7}]
    Is ICU measurement mode sleep?
    [/cover] */
    if ((ICU_17_TIMERIP_MODE_SLEEP == IcuMode))
    {
      /* [cover parentID={FDDCE498-A3D3-4726-B036-A539C5BD9244}]
      Report an Safety error that the ICU mode is not valid.
      [/cover] */
      Mcal_ReportSafetyError(
        ICU_17_TIMERIP_MODULE_ID,
        ICU_17_TIMERIP_INSTANCE_ID, ServiceId,
        ICU_17_TIMERIP_E_INVALID_MODE);/* End of report to Safety */
      ErrorFlag = (uint32) ICU_ERROR_FOUND;
    }
  }
  #endif
  return (ErrorFlag);
}
#endif

#if (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)  || (ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {F93F4F6F-0631-4e26-AC62-EAF90B305322}]     **
**                                                                            **
** Syntax : static void Icu_lEnableNotificationInterrupts(                    **
**                          const uint32 IcuHwOption,                         **
**                          const uint16 HwUnit,                              **
**                          uint32* const GlbIndexStatusPtr)                  **
**                                                                            **
** Description : ICU local function to disable the interrupts                 **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  IcuHwOption : HW option used                             **
**                   HwUnit : Identifier for HW unit getting used             **
**                   GlbIndexStatusPtr : Pointer to channel status flags      **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
static void Icu_lEnableNotificationInterrupts(const uint32 IcuHwOption,
    const uint16 HwUnit,
    uint32* const GlbIndexStatusPtr)
{
  #if(ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON)
  uint32 FlagStatus;
  uint16 EruLineUsed;
  uint16 OguOutput;
  #endif
  /* switch depending on the HW used */
  switch(IcuHwOption)
  {
    /* [cover parentID={93CA757C-1B38-4458-8ADA-D833692D7069}]
    Is the HW used GTM-TIM?
    [/cover] */
    case ICU_17_TIMERIP_GTM_OPTION:
      /* [cover parentID={AE007F8A-F4DA-4dea-8F5C-5C06DF5206B2}]
      Clear TIM interrupt flags.
      [/cover] */
      #if(ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
      Icu_lGtmClearIrqNotify(HwUnit, GlbIndexStatusPtr);
      /* [cover parentID={66B412B3-26CE-4380-B7E2-FF912DB248E2}]
      Enable TIM NEWVAL interrupt. Enable TODET interrupt if timeout it enabled.
      [/cover] */
      if (1U
          == Mcal_GetBitAtomic(*GlbIndexStatusPtr, ICU_TIMEOUT_STATUS_POS,
              ICU_TIMEOUT_STATUS_LENGTH))
      {
        if (0U
          == Mcal_GetBitAtomic(*GlbIndexStatusPtr, ICU_TIMEOUT_EXC_STATUS_POS,
              ICU_TIMEOUT_EXC_STATUS_LENGTH))
        {
          Icu_lGtmIrqModify(HwUnit, \
            (uint8)((IFX_GTM_TIM_CH_IRQ_NOTIFY_TODET_MSK << IFX_GTM_TIM_CH_IRQ_NOTIFY_TODET_OFF) \
            | IFX_GTM_TIM_CH_IRQ_NOTIFY_NEWVAL_MSK));
        }
        else
        {
          Icu_lGtmIrqModify(HwUnit, \
            (uint8)((IFX_GTM_TIM_CH_IRQ_NOTIFY_TODET_MSK << IFX_GTM_TIM_CH_IRQ_NOTIFY_TODET_OFF)));
        }

      }
      else
      {
        Icu_lGtmIrqModify(HwUnit, IFX_GTM_TIM_CH_IRQ_NOTIFY_NEWVAL_MSK);
      }
      #endif
      break;
    /* [cover parentID={A6604B60-4B73-4e49-B67B-33BE0E8734C8}]
    Is the HW used CCU6?
    [/cover] */
    case ICU_17_TIMERIP_CCU_OPTION:
      /* [cover parentID={0131D37D-E0EE-409f-A2FD-701F5C82C8DC}]
      Enable CCU6 interrupts
      [/cover] */
      #if(ICU_17_TIMERIP_CCU6_USED == STD_ON) && (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
      Icu_lCcu6EnableNotification(HwUnit,
                              (uint8)(Mcal_GetBitAtomic(*GlbIndexStatusPtr, \
                                ICU_CHNL_EDGE_POS, ICU_CHNL_EDGE_BIT_LENGTH)),
                                GlbIndexStatusPtr);
      #endif
      break;
    /* [cover parentID={2B32365D-E33E-415f-BD90-CD81AE8D8303}]
    Is the HW used ERU?
    [/cover] */
    case ICU_17_TIMERIP_ERU_OPTION:
      /* Get ERU line used */
      #if(ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON) && (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
      EruLineUsed = ((HwUnit) & ICU_ERU_CHNL_MASK);
      /* Read any flags before clearing to set ICU_17_TIMERIP_ACTIVE */
      FlagStatus = Mcal_GetBitAtomic(MODULE_SCU.EIFR.U, EruLineUsed, 1U);
      /* Clear Service Request if any was in pending */
      MODULE_SCU.FMR.U = (((uint32)1UL) << (EruLineUsed + ICU_ERU_FCSTART));
      /* Get the OGU output channel getting used */
      OguOutput = ((HwUnit >> ICU_ERU_OGU_CHNL_BIT_POS) & ICU_ERU_CHNL_MASK);
      /* [cover parentID={3A04C8B6-3B4F-45c1-9185-5F6A544BBAA7}]
      Set IGP value to trigger interrupt on active edge.
      [/cover] */
      Icu_lSetEruIgp((uint8) OguOutput, ICU_ERU_IGP_BIT_VALUE);
      /* If the Flag was set, indicate in channel status flags */
      /* [cover parentID={697EFC7C-A311-4f30-8CD7-7E22BD98B076}]
      Is the read flag set?
      [/cover] */
      if(FlagStatus == 1U)
      {
        Mcal_SetBitAtomic( \
                           GlbIndexStatusPtr, (sint32)ICU_CHNL_STATUS_POS, \
                           1, (uint32)ICU_17_TIMERIP_ACTIVE);
      }
      #endif
      break;
    /* [cover parentID={51C3AFF7-9517-454a-920A-B90ECF834E9E}]
    Is the HW used GPT12?
    [/cover] */
    default: /* ICU_17_TIMERIP_GPT12_OPTION */
      /* [cover parentID={222DB903-8B12-4e65-BDFD-B0FE472B887C}]
      Enable notification for GPT12
      [/cover] */
      #if(ICU_17_TIMERIP_GPT12_USED == STD_ON) && (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
      if(0U ==
          Mcal_GetBitAtomic(*GlbIndexStatusPtr, ICU_CHNL_MULTIEDGE_STAT_POS,
                            ICU_CHNL_MULTIEDGE_STAT_BIT_LENGTH))
      {
        /* Enable GPT12 interrupts on each valid edge */
        Icu_lGpt12EnableNotification(HwUnit, GlbIndexStatusPtr);
      }
      #endif
      break;
  }
  /* MISRA2012_RULE_2_7_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the variable GlbIndexStatusPtr is
   * accessed using only assembly instruction in some configurations */
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer GlbIndexStatusPtr is
   * accessed using only assembly instruction in some configurations */
}

#endif

#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) && \
((ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON) || (ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON))
/*******************************************************************************
** Traceability: [cover parentID= {1F527C5F-1234-4b0b-9757-AE9C32E4FD2B}]     **
**                                                                            **
** Syntax : LOCAL_INLINE void Icu_lGtmClearIrqNotify (                        **
**                      const uint16 GlobalChannelNumber                      **
**                      uint32* const GlbIndexStatusPtr  )                    **
**                                                                            **
** Description :     Function to Clear TIM Interrupt Notifications            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  GlobalChannelNumber - Channel Number                     **
**                   GlbIndexStatusPtr : Pointer to channel status flags      **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lGtmClearIrqNotify(
  const uint16 GlobalChannelNumber,
  uint32* const GlbIndexStatusPtr)
{
  Ifx_GTM_TIM_CH* TimChannelRegPtr;          /* Pointer to TIM Channel Reg    */
  uint8 ModuleNo;                            /* Holds the TIM module Number   */
  uint8 ChannelNo;                           /* Holds the TIM Channel Number  */
  uint32 NotifyValue;

  /* Calculate Module Id of the TIM channel */
  ModuleNo = (uint8)((GlobalChannelNumber / ICU_GTM_CHANNELS_PER_TIM_MODULE) \
                     & ICU_GTM_MODULE_NO_MSK);
  /* Calculate Channel number of the TIM channel */
  ChannelNo = (uint8)(GlobalChannelNumber % ICU_GTM_CHANNELS_PER_TIM_MODULE);

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TimChannelRegPtr = GTM_TIM_CH_POINTER(ModuleNo, ChannelNo);
  /* Read and clear all Pending Interrupts */
  /* MISRA2012_RULE_11_8_JUSTIFICATION: SFR access. Since the input
   * argument for the API discards volatile keyword. No side effects foreseen
   * by violating this MISRA rule*/
  NotifyValue = Mcal_Swap( \
      (&(TimChannelRegPtr->IRQ.NOTIFY.U)),ICU_GTM_CLEAR_INTERRUPTS, \
                                                           ICU_SWAP_32BIT_MASK);

  /* Set the ICU_ACTIVITY_STARTED flag */
  if(1U == (NotifyValue & ICU_GTM_TIM_NEWVAL_MASK))
  {
    Mcal_SetBitAtomic( \
        GlbIndexStatusPtr, (sint32)ICU_CHNL_STATUS_POS,\
        ICU_CHNL_STATUS_BIT_LENGTH, (uint32)ICU_17_TIMERIP_ACTIVE);
  }
  /* MISRA2012_RULE_2_7_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the variable GlbIndexStatusPtr is
   * accessed using assembly instruction. */
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer GlbIndexStatusPtr is
   * accessed using assembly instruction. */
}
#endif

#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) && \
((ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON) || (ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON))
/*******************************************************************************
** Traceability: [cover parentID= {374FFCD4-5DF6-46d3-B79A-67BDADE4E4E4}]     **
**                                                                            **
** Syntax : static void Icu_lGtmIrqModify(                                    **
**                            const uint16 GlobalChannelNumber,               **
**                            const uint8 InterruptFlag)                      **
**                                                                            **
** Description :     Function to enable/Disable TIM Interrupts                **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  GlobalChannelNumber - Channel Number                     **
**                   InterruptFlag - Interrupt Enable bits to set             **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
static void Icu_lGtmIrqModify(const uint16 GlobalChannelNumber,
                              const uint8 InterruptFlag)
{
  Ifx_GTM_TIM_CH* TimChannelRegPtr;          /* Pointer to TIM Channel Reg    */
  uint8 ModuleNo;                            /* Holds the TIM module Number   */
  uint8 ChannelNo;                           /* Holds the TIM Channel Number  */


  /* Calculate Module Id of the TIM channel */
  ModuleNo = (uint8)((GlobalChannelNumber / ICU_GTM_CHANNELS_PER_TIM_MODULE) \
                     & ICU_GTM_MODULE_NO_MSK);
  /* Calculate Channel number of the TIM channel */
  ChannelNo = (uint8)(GlobalChannelNumber % ICU_GTM_CHANNELS_PER_TIM_MODULE);

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TimChannelRegPtr = GTM_TIM_CH_POINTER(ModuleNo, ChannelNo);
  /* Enable/Disable Interrupt */
  TimChannelRegPtr->IRQ.EN.U     = InterruptFlag;
}
#endif

#if (ICU_17_TIMERIP_GPT12_USED == STD_ON) && \
(ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {8BE46F9C-3382-494a-B4EB-A206BDFCB062}]     **
**                                                                            **
** Syntax : LOCAL_INLINE void Icu_lGpt12EnableNotification (                  **
**                      const uint16 GlobalChannelNumber                      **
**                      uint32* const GlbIndexStatusPtr  )                    **
**                                                                            **
** Description :     Function to Clear TIM Interrupt Notifications            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  GlobalChannelNumber - Channel Number                     **
**                   GlbIndexStatusPtr : Pointer to channel status flags      **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lGpt12EnableNotification(
  const uint16 GlobalChannelNumber,
  uint32* const GlbIndexStatusPtr)
{
  uint8 ChannelNo;                              /* Holds the GPT12 Tx Number  */
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
    MISRA rule. Union usage is required to access SFR data type and implement
    efficiently for accessing Timer registers */
  volatile Ifx_GPT12_T2* Gpt12TxRegPtr;
  uint32 TxRegValue;
  Ifx_GPT12* Gpt12BasePtr;
  /* Extract Channel Number */
  ChannelNo = (uint8)GlobalChannelNumber & ICU_LOWER_NIBBLE;

  Gpt12BasePtr = &MODULE_GPT120;
  Gpt12TxRegPtr = &(Gpt12BasePtr->T2);
  Gpt12TxRegPtr = &(Gpt12TxRegPtr[ChannelNo]);

  /* Store and Set the previous Edge counter Value */
  /* MISRA2012_RULE_11_8_JUSTIFICATION: SFR access. Since the input
   * argument for the API discards volatile keyword. No side effects foreseen
   * by violating this MISRA rule*/
  TxRegValue = Mcal_Swap(&(Gpt12TxRegPtr->U), ICU_GPT12_COUNTER_MAX, \
                         ICU_GPT12_COUNTER_MASK);
  if(TxRegValue > 0U)
  {
    /* Set flag for Get Input State */
    Mcal_SetBitAtomic( \
        GlbIndexStatusPtr, (sint32)ICU_CHNL_STATUS_POS,\
        ICU_CHNL_STATUS_BIT_LENGTH, (uint32)ICU_17_TIMERIP_ACTIVE);
  }
  else
  {
    /* No flag to be set*/
  }
  /* MISRA2012_RULE_2_7_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the variable GlbIndexStatusPtr is
   * accessed using assembly instruction. */
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer GlbIndexStatusPtr is
   * accessed using assembly instruction. */
}
#endif

#if (ICU_17_TIMERIP_CCU6_USED == STD_ON) && \
(ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {1F944F66-A306-4e16-A646-06B0EBE87612}]     **
**                                                                            **
** Syntax : LOCAL_INLINE void Icu_lCcu6EnableNotification(                    **
**                             const uint16 CellUsed,                         **
**                             const Icu_17_TimerIp_ActivationType ActiveEdge,**
**                             uint32* const GlbIndexStatusPtr)               **
**                                                                            **
** Description :     Function to set the IEN register according to the        **
**                   configured edge to enable the interrupts and update the  **
**                   SW flags according to the previous flag conditions.      **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  CellUsed - CCU6x Kernal and Channel Info                 **
**                   ActiveEdge - Configured Activation edge for the channel  **
**                   GlbIndexStatusPtr - Pointer to the channel flags         **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lCcu6EnableNotification(const uint16 CellUsed,
    const uint8 ActiveEdge,
    uint32* const GlbIndexStatusPtr)
{
  volatile Ifx_CCU6 *Ccu6RegPtr; /* Variable to hold the current CCU6 address */
  uint8 CcuActiveEdge;      /* To hold the CCU equivalent edge */
  uint8 CcChannelNumber;    /* To hold the CC channel number */
  uint32 FlagStatus;
  uint8 BitPos;
  /* Get the equivalent CCU Edge */
  CcuActiveEdge = Icu_lCcu6GetActiveEdge(ActiveEdge);

  /* Upper Nibble of AssignedHwUnitNumber holds the Channel Number */

  CcChannelNumber = (uint8)
      ((CellUsed & ICU_CCU_GET_COMPARATOR)>> ICU_BRING_TO_BIT_0);

  /* Get the base address of the Kernal */
  Ccu6RegPtr = &(&MODULE_CCU60)[CellUsed & ICU_CCU_GET_KERNEL];
  /* Read flag status before clearing */
  BitPos = CcChannelNumber * (uint8)ICU_CCU_IS_BITS_PER_CHANNEL;
  FlagStatus = Mcal_GetBitAtomic(Ccu6RegPtr->IS.U, BitPos, \
                                 ICU_CCU_IS_BITS_PER_CHANNEL);
  /* Clear any pending interrupt */
  Ccu6RegPtr->ISR.U = (uint32)(ICU_CCU_CLEAR_INTERRUPT <<
      (CcChannelNumber * (uint8)ICU_CCU_IS_BITS_PER_CHANNEL));
  /* Enable interrupt for the channel */
  Mcal_SetBitAtomic((&Ccu6RegPtr->IEN.U),\
  (CcChannelNumber * ICU_CCU_IS_BITS_PER_CHANNEL),ICU_CCU_IS_BITS_PER_CHANNEL,\
    (uint32)CcuActiveEdge);
  if(FlagStatus == CcuActiveEdge)
  {
    Mcal_SetBitAtomic( \
                       GlbIndexStatusPtr, (sint32)ICU_CHNL_STATUS_POS, \
                       1, (uint32)ICU_17_TIMERIP_ACTIVE);
  }
  /* MISRA2012_RULE_2_7_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the variable GlbIndexStatusPtr is
   * accessed using assembly instruction. */
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer GlbIndexStatusPtr is
   * accessed using assembly instruction. */
}
#endif

#if(ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON)
/* To set IGPx bit of IGCRx register*/
/*******************************************************************************
** Traceability: [cover parentID= {F4B3E466-30A9-4ef5-9593-5E3BE8A1ACA6}]     **
**                                                                            **
** Syntax :           static  void Icu_lSetEruIgp(                            **
**                    const uint16 EruIgcrUsed                                **
**                    const uint8 Value     )                                 **
**                                                                            **
** Description :      To set IGPx bit of IGCRx register                       **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        None                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Reentrant for different channel                         **
**                                                                            **
** Parameters (in):   EruIgcrUsed - IGCR register used                        **
**                    Value - Value to be written to IGP                      **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value:      None                                                    **
**                                                                            **
*******************************************************************************/
static void Icu_lSetEruIgp( const uint16 EruIgcrUsed,
                            const uint8 Value)
{
  uint32* Ptr;
  uint32 EruIgpPos;
  uint32 TempVal;
  uint32 Mask;

  /* Get the IGP position to be updated */
  EruIgpPos = (((EruIgcrUsed % ICU_ERU_CHNL_PAIR_COUNT) == 0U) ? \
               (uint32)ICU_ERU_IGP0_POS : (uint32)ICU_ERU_IGP1_POS);
  Mask = ICU_ERU_IGP_BIT_MASK << EruIgpPos;
  TempVal = (Value & ICU_ERU_IGP_BIT_MASK) << EruIgpPos;
  /* To extract IGCR0/IGCR1/IGCR2 or IGCR3 address depending
      on OGU line used */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_8_JUSTIFICATION: SFR access. Since the input
   * argument for the API discards volatile keyword. No side effects foreseen
   * by violating this MISRA rule*/
  Ptr = (uint32*)(&(MODULE_SCU.IGCR[EruIgcrUsed / ICU_ERU_CHNL_PAIR_COUNT].U));
  /* [cover parentID={8B697CD7-69E8-4d39-A6B6-C868C1DFEAEB}]
    Hardware register access.
  [/cover] */
  /* [cover parentID={0F90678E-58C6-49e4-8E4B-76826E17E924}]
  Update the IGCR at the IGP position with the input value atomically.
  [/cover] */
  ICU_LIB_RUNTIME_WRITESAFETYENDINITPROTREGMASK(Ptr, TempVal, Mask);
}
#endif

#if (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON) || (ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {7F30E35D-B486-4d2d-A5C2-2AAB00CEBF77}]     **
**                                                                            **
** Syntax : static void Icu_lDisableNotificationInterrupts(                   **
**                           const uint32 IcuHwOption,                        **
**                           const uint16 HwUnit)                             **
**                                                                            **
** Description : ICU local function to disable the interrupts                 **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  IcuHwOption : HW option used                             **
**                   HwUnit : Identifier for HW unit getting used             **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
static void Icu_lDisableNotificationInterrupts(
  const uint32 IcuHwOption,
  const uint16 HwUnit)
{
  #if(ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON)
  uint8 OguOutput;
  #endif
  /* switch depending on the HW used */
  switch(IcuHwOption)
  {
    /* [cover parentID={97F794D4-40E1-4e21-AD5B-C5E9C2679B7C}]
    Is HW used GTM-TIM?
    [/cover] */
    case ICU_17_TIMERIP_GTM_OPTION:
      /* Disable the GTM-TIM interrupts */
      /* [cover parentID={7AEB97F0-C157-40e9-8E89-B06AFFF9E190}]
      Disable GTM-TIM interrupts
      [/cover] */
      #if(ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
      Icu_lGtmIrqModify(HwUnit, 0U);
      #endif
      break;
    /* [cover parentID={E785EABD-A1D5-45d6-89A6-2B3F322CE50E}]
    Is HW used CCU6?
    [/cover] */
    case ICU_17_TIMERIP_CCU_OPTION:
      /* Disable CCU6 interrupts */
      /* [cover parentID={13692E17-BA46-4ff2-A649-6CE4DD2FBA27}]
      Disable CCU6 interrupts
      [/cover] */
      #if(ICU_17_TIMERIP_CCU6_USED == STD_ON) && (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
      Icu_lCcu6CleaInterruptEnable(HwUnit);
      #endif
      break;
    /* [cover parentID={5FD2D2EF-2810-461e-8552-F327586484B6}]
    Is HW used ERU?
    [/cover] */
    case ICU_17_TIMERIP_ERU_OPTION:
      /* Set IGP value to disable interrupts */
      /* [cover parentID={789A7970-5371-420e-9084-0D7FFAFEAD2E}]
      Disable OGU interrupts.
      [/cover] */
      #if(ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON)
      OguOutput =
              (uint8)((HwUnit >> ICU_ERU_OGU_CHNL_BIT_POS) & ICU_ERU_CHNL_MASK);
      Icu_lSetEruIgp((uint8) OguOutput, 0U);
      #endif
      break;
    /* [cover parentID={956D6F0C-DB98-4644-A641-8F3EB05AAEC8}]
    Is HW used GTP12?
    [/cover] */
    default: /* ICU_17_TIMERIP_GPT12_OPTION */
      /* [cover parentID={3473C2D6-4808-4d84-93BA-8ADE8F870871}]
      Disable GPT12 notification interrupts.
      [/cover] */
      #if(ICU_17_TIMERIP_GPT12_USED == STD_ON) && (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
      /* Disable the GPT12 interrupts for all edges */
      Icu_lGpt12DisableNotification(HwUnit);
      #endif
      break;
  }/*switch(IcuOption)*/
  #if (ICU_17_TIMERIP_EDGE_DETECT_API == STD_OFF) && (ICU_17_TIMERIP_GTM_TIM_USED == STD_OFF)
    UNUSED_PARAMETER(HwUnit);
  #endif
}
#endif

#if (ICU_17_TIMERIP_CCU6_USED == STD_ON) && \
(ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {5E2F3109-9916-44ce-8AA4-53A0EDF73333}]     **
**                                                                            **
** Syntax : LOCAL_INLINE void Icu_lCcu6CleaInterruptEnable(                   **
**                  const uint16 CellUsed)                                    **
**                                                                            **
** Description :     Function to clear the CCU6 interrupt enable              **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  CellUsed - CCU6 Kernel and channel information           **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lCcu6CleaInterruptEnable(const uint16 CellUsed)
{
  volatile Ifx_CCU6 *Ccu6RegPtr; /* Variable to hold the current CCU6 address */
  uint8 CcChannelNumber;    /* To hold the CC channel number */

  /* Upper Nibble of AssignedHwUnitNumber holds the Channel Number */
  CcChannelNumber = (uint8)
      ((CellUsed & ICU_CCU_GET_COMPARATOR)>> ICU_BRING_TO_BIT_0);

  /* Get the base address of the Kernel */
  Ccu6RegPtr = &(&MODULE_CCU60)[CellUsed & ICU_CCU_GET_KERNEL];

  /* Clear interrupt for the channel */
  Mcal_SetBitAtomic((&Ccu6RegPtr->IEN.U), \
                    (CcChannelNumber * ICU_CCU_IS_BITS_PER_CHANNEL), \
                    ICU_CCU_IS_BITS_PER_CHANNEL, \
                    (uint32)0);
  /* MISRA2012_RULE_2_2_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the variable Ccu6RegPtr is
   * accessed using assembly instruction. */
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer Ccu6RegPtr is
   * accessed using assembly instruction. */
}
#endif

#if (ICU_17_TIMERIP_GPT12_USED == STD_ON) && \
(ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {E4AD5EFE-D497-4339-9520-47F85F0B4A4B}]     **
**                                                                            **
** Syntax : LOCAL_INLINE void Icu_lGpt12DisableNotification (                 **
**                            const uint16 GlobalChannelNumber    )           **
**                                                                            **
** Description :     Function to disable GPT12 Interrupt Notifications        **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  GlobalChannelNumber - Channel Number                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lGpt12DisableNotification(
  const uint16 GlobalChannelNumber)
{
  uint8 ChannelNo;                              /* Holds the GPT12 Tx Number  */
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
    MISRA rule. Union usage is required to access SFR data type and implement
    efficiently for accessing Timer registers */
  volatile Ifx_GPT12_T2* Gpt12TxRegPtr;
  Ifx_GPT12* Gpt12BasePtr;
  /* Extract Channel Number */
  ChannelNo = (uint8)GlobalChannelNumber & ICU_LOWER_NIBBLE;

  Gpt12BasePtr = &MODULE_GPT120;
  Gpt12TxRegPtr = &(Gpt12BasePtr->T2);
  Gpt12TxRegPtr = &(Gpt12TxRegPtr[ChannelNo]);

  /* Set the Tx Register to 0 */
  Gpt12TxRegPtr->U = (uint32)0U;
}
#endif

#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) && \
(ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {14451732-2F75-40e1-86C3-BF955787FCB3}]     **
**                                                                            **
** Syntax : LOCAL_INLINE void Icu_lGtmStartEdgeDetect(                        **
**                           const uint16 GlobalChannelNumber)                **
**                                                                            **
** Description :     Function to configure TIM Channel given by               **
**                   GlobalChannelNumber to scan the input for the Active edge**
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  GlobalChannelNumber - Channel Number                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lGtmStartEdgeDetect(const uint16 GlobalChannelNumber)
{
  Ifx_GTM_TIM_CH* TimChannelRegPtr;          /* Pointer to TIM Channel Reg    */
  uint8 ModuleNo;                            /* Holds the TIM module Number   */
  uint8 ChannelNo;                           /* Holds the TIM Channel Number  */


  /* Calculate Module Id of the TIM channel */
  ModuleNo = (uint8)((GlobalChannelNumber / ICU_GTM_CHANNELS_PER_TIM_MODULE) \
                     & ICU_GTM_MODULE_NO_MSK);
  /* Calculate Channel number of the TIM channel */
  ChannelNo = (uint8)(GlobalChannelNumber % ICU_GTM_CHANNELS_PER_TIM_MODULE);

  /* Get the pointer to TIM Channel Register Structure */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TimChannelRegPtr = GTM_TIM_CH_POINTER(ModuleNo, ChannelNo);
  /* Disable the Channel */
  TimChannelRegPtr->CTRL.U &= ~ICU_GTM_TIM_ENABLE_CHANNEL ;
  /* Clear and Update mode to TIEM */
  TimChannelRegPtr->CTRL.U &=
    (~((uint32)ICU_ERU_CHNL_MASK << ICU_GTM_TIM_MODE_POS));
  TimChannelRegPtr->CTRL.U |=
    (uint32)((ICU_GTM_TIM_MODE_TIEM << ICU_GTM_TIM_MODE_POS));
  /* Clear all Pending Interrupts */
  TimChannelRegPtr->IRQ.NOTIFY.U = ICU_GTM_CLEAR_INTERRUPTS;
  /* Enable TIM channel */
  TimChannelRegPtr->CTRL.U |= ICU_GTM_TIM_ENABLE_CHANNEL ;
}
#endif

#if (ICU_17_TIMERIP_CCU6_USED == STD_ON) && \
(ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {027E15D2-F802-4f8b-8FB6-BDF95C3151D6}]     **
**                                                                            **
** Syntax : LOCAL_INLINE void Icu_lCcuEnableChannel(const uint16 CellUsed)    **
**                                                                            **
** Description :     Function to enable a CCU channel by changing the mode of **
**                   the channel to Mode 1 for Edge Detection                 **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  CellUsed - CCU6x Kernal and Channel information          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lCcuEnableChannel(const uint16 CellUsed)
{
  volatile Ifx_CCU6 *Ccu6RegPtr; /* Variable to hold the current CCU6 address */
  uint16 CcChannelNumber;    /* To hold the CC channel number */


  /* Upper Nibble of AssignedHwUnitNumber holds the Channel Number */
  CcChannelNumber = (CellUsed & ICU_CCU_GET_COMPARATOR) >> ICU_BRING_TO_BIT_0;

  /* Get the base address of the Kernal */
  Ccu6RegPtr = &(&MODULE_CCU60)[CellUsed & ICU_CCU_GET_KERNEL];

  /* Clear any pending interrupt */
  Ccu6RegPtr->ISR.U = (uint32)(ICU_CCU_CLEAR_INTERRUPT <<
                        (CcChannelNumber * (uint8)ICU_CCU_IS_BITS_PER_CHANNEL));

  /* Channel is configured to Capture Mode 0 */
  Mcal_SetBitAtomic((&Ccu6RegPtr->T12MSEL.U), \
                    (CcChannelNumber * ICU_CCU_MSEL_BITS_PER_CHANNEL), \
                    ICU_CCU_MSEL_BITS_PER_CHANNEL, \
                    (uint32)ICU_CCU_CAPTURE_MODE1);

}
#endif


#if (ICU_17_TIMERIP_GPT12_USED == STD_ON) && \
(ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {28D6C537-28E6-4ac8-A1A4-86B8ECA6AC0E}]     **
**                                                                            **
** Syntax : LOCAL_INLINE void Icu_lGpt12StartEdgeDetect (                     **
**                            const uint16 GlobalChannelNumber,               **
**                            const uint16 Count   )                          **
**                                                                            **
** Description :     Function to start the edge detection for a GPT12 channel **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  GlobalChannelNumber - Channel Number                     **
**                   Count - Number of edge to be passed before issuing       **
**                   notifications.                                           **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
static void Icu_lGpt12StartEdgeDetect(
  const uint16 GlobalChannelNumber, const uint16 Count)
{
  uint8 ChannelNo;                              /* Holds the GPT12 Tx Number  */
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
    MISRA rule. Union usage is required to access SFR data type and implement
    efficiently for accessing Timer registers */
  volatile Ifx_GPT12_T2* Gpt12TxRegPtr;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
    MISRA rule. Union usage is required to access SFR data type and implement
    efficiently for accessing Timer control registers */
  volatile Ifx_GPT12_T2CON* Gpt12TxConRegPtr;
  Ifx_GPT12* Gpt12BasePtr;

  /* Extract Channel Number */
  ChannelNo = (uint8)GlobalChannelNumber & ICU_LOWER_NIBBLE;

  Gpt12BasePtr = &MODULE_GPT120;
  Gpt12TxConRegPtr = &(Gpt12BasePtr->T2CON);
  Gpt12TxConRegPtr = &(Gpt12TxConRegPtr[ChannelNo]);
  Gpt12TxRegPtr = &(Gpt12BasePtr->T2);
  Gpt12TxRegPtr = &(Gpt12TxRegPtr[ChannelNo]);

  /* Set initial counter to get the interrupt after "count" edges */
  /* If the count is 0 interrupt will be generated after counter roll off */
  /* If the count is 1 interrupt will be generated on every edge for
   * generating notifications*/
  /* Any value other than 0 will also be used for multi edge detection */
  if(Count != 0U)
  {
    Gpt12TxRegPtr->U = (ICU_GPT12_COUNTER_MAX -
                      (((uint32)Count & ICU_GPT12_COUNTER_MAX) - 1U));
  }
  else
  {
    Gpt12TxRegPtr->U = 0U;
  }

  /* Enable the timer */
  Mcal_SetBitAtomic( \
                     Gpt12TxConRegPtr, (sint32)ICU_GPT12_TXCON_TXR_POS, \
                     1, (uint32)ICU_GPT12_TX_RUN);
  /* MISRA2012_RULE_2_2_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the variable Gpt12TxConRegPtr is
   * accessed using assembly instruction. */
}
#endif

#if (ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {2C82F26B-A138-4a82-B67B-42341427D64F}]     **
**                                                                            **
** Syntax :          LOCAL_INLINE void Icu_lSetEruEdge(                       **
**                           const uint8  Edge,                               **
**                           const uint8 EruEicrChannel )                     **
**                                                                            **
** Description :     Local function : Service to setup activations edges      **
**                                    so that notification can occur when     **
**                                    programmed edge occurs on the input pin **
** [/cover]                                                                   **
*                                                                             **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
*                                                                             **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  Edge - To know which kind of Activation asked            **
**                   EruEicrChannel - To know the Eru Line number             **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lSetEruEdge(const uint8 Edge,
                                  const uint8 EruEicrChannel)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * MISRA rule.As IGCR register is EndInit protected, the address of EICR
   * register needs to be passed to a MCALLIB api to update. Hence to access
   * the register address the datatype is used. */
  volatile Ifx_SCU_EICR* EruAddress;
  uint32 EruFenPos;
  uint32 L_Edge;
  uint32 TempVal;
  uint32 Mask;
  /* To calculate the value passed for FEN and REN setting */
  if(Edge == (uint8)ICU_17_TIMERIP_RISING_EDGE)
  {
    L_Edge = ICU_ERU_RISING_EDGE;
  }
  else if(Edge == (uint8)ICU_17_TIMERIP_FALLING_EDGE)
  {
    L_Edge = ICU_ERU_FALLING_EDGE;
  }
  else if (Edge == (uint8)ICU_17_TIMERIP_BOTH_EDGES)
  {
    L_Edge = ICU_ERU_BOTH_EDGE;
  }
  else
  {
    L_Edge = 0U;
  }
  /* Get EICR address */
  EruAddress = &(MODULE_SCU.EICR[EruEicrChannel / ICU_ERU_CHNL_PAIR_COUNT]);
  /* Get the FEN position to be udpated.*/
  EruFenPos = (uint32)(((EruEicrChannel % ICU_ERU_CHNL_PAIR_COUNT) == 0U) ? \
                       ICU_ERU_FEN_0_POS : ICU_ERU_FEN_1_POS);
  Mask = ICU_ERU_EDGE_MASK << EruFenPos;
  /* Set for Rising edge / Falling edge / Both edges */
  TempVal = L_Edge << EruFenPos;
  /* [cover parentID={579EEBA2-3B4F-44ec-A642-181378F96CB0}]
  Configure the EICR with the requested edge.
  [/cover] */
  /* [cover parentID={8B697CD7-69E8-4d39-A6B6-C868C1DFEAEB}]
    Hardware register access.
  [/cover] */
  ICU_LIB_RUNTIME_WRITESAFETYENDINITPROTREGMASK(\
      & (EruAddress->U), TempVal, Mask);
}/* End of Icu_lSetEruEdge*/
#endif

#if (ICU_17_TIMERIP_CCU6_USED == STD_ON) && \
((ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON) || \
(ICU_17_TIMERIP_TIMESTAMP_API == STD_ON))
/*******************************************************************************
** Traceability: [cover parentID= {84170109-90AF-4fc1-A628-8292C1D8099A}]     **
**                                                                            **
** Syntax : LOCAL_INLINE void Icu_lCcuDisableChannel(const uint16 CellUsed)   **
**                                                                            **
** Description :     Function to disable a CC channel by changing the compare **
**                   mode of the channel to no mode                           **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  CellUsed - CCU6x Kernal and Channel information          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lCcuDisableChannel(const uint16 CellUsed)
{
  volatile Ifx_CCU6 *Ccu6RegPtr; /* Variable to hold the current CCU6 address */
  uint8 CcChannelNumber;    /* To hold the CC channel number */


  /* Upper Nibble of AssignedHwUnitNumber holds the Channel Number */
  CcChannelNumber = (uint8)
                  ((CellUsed & ICU_CCU_GET_COMPARATOR) >> ICU_BRING_TO_BIT_0);

  /* Get the base address of the Kernal */
  Ccu6RegPtr = &(&MODULE_CCU60)[CellUsed & ICU_CCU_GET_KERNEL];

  /* Channel is configured to Capture Compare Mode Switched off */
  Mcal_SetBitAtomic((&Ccu6RegPtr->T12MSEL.U), \
                    (CcChannelNumber * ICU_CCU_MSEL_BITS_PER_CHANNEL), \
                    ICU_CCU_MSEL_BITS_PER_CHANNEL, \
                    (uint32)ICU_CCU_MSEL_RESET_VAL);
  /* MISRA2012_RULE_2_2_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the variable CcChannelNumber is
   * accessed using assembly instruction. */
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer Ccu6RegPtr is
   * accessed using assembly instruction. */
}
#endif


#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) && \
(ICU_17_TIMERIP_SIGNAL_MEASUREMENT_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {036B0CEC-09E8-470f-AD89-0673F55F7BC0}]     **
**                                                                            **
** Syntax : LOCAL_INLINE uint8 Icu_lGtmStartSignalMeasurement(                **
**                 const uint16 GlobalChannelNumber,                          **
**                 const uint8 SignalMode       )                             **
**                                                                            **
** Description :     Function to enable the channel to start measurement of   **
**                   the type given by SignalMode. TIM channel must be        **
**                   disabled before this function is called.                 **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  GlobalChannelNumber - Channel Number                     **
**                   SignalMode - To choose the measurement mode              **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     uint8 - edge configured for signal measurement           **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Icu_lGtmStartSignalMeasurement(
  const uint16 GlobalChannelNumber,
  const uint8 SignalMode)
{
  Ifx_GTM_TIM_CH* TimChannelRegPtr;   /* Pointer to TIM Channel Reg    */
  uint32 TempRegVal;
  uint32 Cictrlvalue;
  uint8 ConfigEdge;
  uint8 ModuleNo;                            /* Holds the TIM module Number   */
  uint8 ChannelNo;                           /* Holds the TIM Channel Number  */

  /* Calculate Module Id of the TIM channel */
  ModuleNo = (uint8)((GlobalChannelNumber / ICU_GTM_CHANNELS_PER_TIM_MODULE) \
                     & ICU_GTM_MODULE_NO_MSK);
  /* Calculate Channel number of the TIM channel */
  ChannelNo = (uint8)(GlobalChannelNumber % ICU_GTM_CHANNELS_PER_TIM_MODULE);

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TimChannelRegPtr = GTM_TIM_CH_POINTER(ModuleNo, ChannelNo);
  Cictrlvalue = (uint32)(((uint32)(TimChannelRegPtr->CTRL.U)) & \
                         (1UL << IFX_GTM_TIM_CH_CTRL_CICTRL_OFF));
  /* Clear all lower 16 bits */
  TempRegVal = (uint32)(TimChannelRegPtr->CTRL.U & \
                        ((uint32)~(ICU_TIM_GET_LOWER_15BITS)));

  if(SignalMode == (uint8)ICU_17_TIMERIP_BOTH_EDGES)
  {
    if(((TimChannelRegPtr->ECNT.U) & 1UL) == 1UL)
    {
      ConfigEdge = 0U;
    }
    else
    {
      ConfigEdge = 1U;
    }
  }
  else
  {
    ConfigEdge = SignalMode;
  }
  /* Mode, SL and DSL, GPR0_SEL, GPR1_SEL*/
  TempRegVal |= (uint32)(((uint32)(((uint32)((uint32)ConfigEdge) & \
             ICU_TIM_GET_LOWER_NIBBLE_UL) << ICU_TIM_CTRL_DSL_POS)) | \
             (uint32)((uint32)IFX_GTM_TIM_CH_CTRL_GPR0_SEL_MSK << IFX_GTM_TIM_CH_CTRL_GPR0_SEL_OFF) | \
             (uint32)((uint32)IFX_GTM_TIM_CH_CTRL_GPR1_SEL_MSK << IFX_GTM_TIM_CH_CTRL_GPR1_SEL_OFF)) ;
  /* Reloading Input channel select : Current chl or Previous chl value */
  TempRegVal |= Cictrlvalue;

  /* For measuring High time and Low time, Imm start should be considered */
  if((SignalMode & ICU_GTM_TIM_HIGH_LOW_TIME) == ICU_GTM_TIM_HIGH_LOW_TIME)
  {
    /* If the current input level and required time are not same, imm_start
       can be used.*/
    if(((TimChannelRegPtr->ECNT.U) & 1UL) == ((uint32)((uint32)SignalMode) & \
        ICU_TIM_GET_LOWER_NIBBLE_UL))
    {
      TimChannelRegPtr->ECTRL.U |= ICU_ECTRL_IMM_START;
    }
    else
    {
      TimChannelRegPtr->ECTRL.U &= ~ICU_ECTRL_IMM_START;
    }
  }
  /* Clear all pending interrupts */
  TimChannelRegPtr->IRQ.NOTIFY.U = ICU_GTM_CLEAR_INTERRUPTS;
  /* Enable the CNT overflow interrupt */
  TimChannelRegPtr->IRQ.EN.U = ICU_GTM_CNTOVFL_FLAG_SET;
  /* Channel is enabled */
  TimChannelRegPtr->CTRL.U = TempRegVal | ICU_GTM_TIM_ENABLE_CHANNEL ;
  return (ConfigEdge);
}
#endif

#if (ICU_17_TIMERIP_CCU6_USED == STD_ON) && \
(ICU_17_TIMERIP_SIGNAL_MEASUREMENT_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {CE88559A-2AF7-4c4a-AD57-FADA87472172}]     **
**                                                                            **
** Syntax : LOCAL_INLINE void  Icu_lCcuSignalMeasHandler(                     **
**              const uint16 CellUsed,                                        **
**              const unit8 SigKind,                                          **
**              const uint8 CfgEdge)                                          **
**                                                                            **
** Description :     Function to configure and start the channel in the       **
**                   configured signal measurement mode                       **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  CellUsed - CCU6x Kernal and Channel information          **
**                   SigKind - Signal Measurement property of the channel     **
**                   CfgEdge - Configured Active Edge for the channel         **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     uint8 edge Config for CCU6 Comaparator                   **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lCcuSignalMeasHandler(
  const uint16 CellUsed,
  const uint8 SigKind,
  const uint8 CfgEdge)
{
  volatile Ifx_CCU6 *Ccu6RegPtr; /* Variable to hold the current CCU6 address */
  /* MISRA2012_RULE_19_2_JUSTIFICATION: Union based type definition for SFR
     access. */
  volatile Ifx_CCU6_CC6SR * CcuSrRegPtr; /* Pointer to SR registers of CCU */
  uint8 CcChannelNumber;    /* To hold the CC channel number */
  uint8 CcuActiveEdge;      /* CCU relevant Edge */

  /* Upper Nibble of AssignedHwUnitNumber holds the Channel Number */
  CcChannelNumber = (uint8)
                  ((CellUsed & ICU_CCU_GET_COMPARATOR) >> ICU_BRING_TO_BIT_0);

  /* Get the base address of the Kernal */
  Ccu6RegPtr = &(&MODULE_CCU60)[CellUsed & ICU_CCU_GET_KERNEL];

  /* Assign SR register base addresses */
  CcuSrRegPtr = &(Ccu6RegPtr->CC6SR[0]);
  /* Disable CCU6 captures */
  Mcal_SetBitAtomic((&Ccu6RegPtr->T12MSEL.U), \
                  (CcChannelNumber * ICU_CCU_MSEL_BITS_PER_CHANNEL), \
                  ICU_CCU_MSEL_BITS_PER_CHANNEL, \
                  (uint32)ICU_CCU_CAPTURE_MODE_DISABLE);
  /* Clear the channels SR register */
  CcuSrRegPtr[CcChannelNumber].U = 0UL;
  /* [cover parentID={001A929B-01FB-49ef-9DE6-41CE88FF50D3}]
  Make a shadow transfer to clear R register with the contents of SR register.
  [/cover] */
  Mcu_17_Ccu6_TimerShadowTransfer(((uint32)CellUsed & ICU_CCU_GET_KERNEL)
      | (((uint32)CellUsed & ICU_CCU_GET_COMPARATOR) <<
      (ICU_MCU_CCU_COMPARATOR_POS - ICU_CCU_NIBBLE_SIZE)));

  /* Clear any pending interrupt */
  Ccu6RegPtr->ISR.U = (uint32)(ICU_CCU_CLEAR_INTERRUPT <<
      (CcChannelNumber * (uint8)ICU_CCU_IS_BITS_PER_CHANNEL));
  /* Select the interrupt type needed Rising/Falling/Both */
  /* [cover parentID={5568A6F0-E917-44f9-B4C5-8F8B799D64FD}]
  If signal measurement property is HIGH TIME
  [/cover] */
  if(SigKind == (uint8)ICU_17_TIMERIP_HIGH_TIME)
  {
    /* [cover parentID={8F431C58-D398-4d81-9094-CB90A6169019}]
    Interrupt needed on FALLING EDGE
    [/cover] */
    CcuActiveEdge = ICU_CCU_FALLING_EDGE;
  }
  /* [cover parentID={F64EE57A-0463-4c2f-B851-086C2C1D4F31}]
  If signal measurement property is LOW TIME
  [/cover] */
  else if(SigKind == (uint8)ICU_17_TIMERIP_LOW_TIME)
  {
    /* [cover parentID={F6E20B13-067A-44b5-AC9F-9BF25086A1FB}]
    Interrupt needed on RISING EDGE
    [/cover] */
    CcuActiveEdge = ICU_CCU_RISING_EDGE;
  }
  /* [cover parentID={33FF7FAA-7B24-417d-8472-9E8B0931780E}]
  If signal measurement property is duty cycle
  [/cover] */
  else if(SigKind == (uint8)ICU_17_TIMERIP_DUTY_CYCLE)
  {
    /* [cover parentID={358B1380-16D6-4245-A2D4-CD1E5D1634A3}]
    Interrupt selection for DUTY
    [/cover] */
    /* Interrupt needed on opposite of configured edge */
    if(CfgEdge == (uint8)ICU_17_TIMERIP_RISING_EDGE)
    {
      CcuActiveEdge = ICU_CCU_RISING_EDGE;
    }
    else if(CfgEdge == (uint8)ICU_17_TIMERIP_FALLING_EDGE)
    {
      CcuActiveEdge = ICU_CCU_FALLING_EDGE;
    }
    else
    {
      CcuActiveEdge = (uint8)(ICU_CCU_FALLING_EDGE | ICU_CCU_RISING_EDGE);
    }
  }
  /* [cover parentID={0840098F-8DA2-4e26-9139-FD4B7A5A7868}]
  If signal measurment property is PERIOD
  [/cover] */
  else /*if(SigKind == (uint8)ICU_17_TIMERIP_PERIOD_TIME)*/
  {
    /* No interrupt needed for Period calculation */
    CcuActiveEdge = 0U;
  }

  /* Enable the interupts required */
  /* [cover parentID={C747377B-465C-424d-8673-A694ABF9C5B3}]
  Enable the required interrupts
  [/cover] */
  Mcal_SetBitAtomic((&Ccu6RegPtr->IEN.U), \
                    (CcChannelNumber * ICU_CCU_IS_BITS_PER_CHANNEL), \
                    ICU_CCU_IS_BITS_PER_CHANNEL, \
                    (uint32)CcuActiveEdge);

  /* Identify the signal measurement property type of the channel */
  /* Mode for Period calculation is dependent on Edge. Mode2 for Rising.
   * Mode 2 for Falling. Both edge is invalid for Period.
   * All rest measurements use Mode 1*/
  /* T12MSEL should be updated atomically. */
  /* [cover parentID={7C078091-78FE-4007-B823-71F9932C66E1}]
  If signal measurement property is period time
  [/cover] */
  if(SigKind == (uint8)ICU_17_TIMERIP_PERIOD_TIME)
  {
    /* [cover parentID={B58AA904-5589-4150-9517-807EDE3D0404}]
    If configured active edge is rising edge
    [/cover] */
    if(CfgEdge == (uint8)ICU_17_TIMERIP_RISING_EDGE)
    {
      /* [cover parentID={CFF1A5C0-37C1-4bd2-9433-A2D5EDC45D83}]
      Channel is configured to Capture Mode 2
      [/cover] */
      Mcal_SetBitAtomic((&Ccu6RegPtr->T12MSEL.U), \
                        (CcChannelNumber * ICU_CCU_MSEL_BITS_PER_CHANNEL), \
                        ICU_CCU_MSEL_BITS_PER_CHANNEL, \
                        (uint32)ICU_CCU_CAPTURE_MODE2);
    }
    else
    {
      /* [cover parentID={46B6A26F-4F4F-473f-931F-8BCA94AEEC70}]
      Channel is configured to Capture Mode 3
      [/cover] */
      Mcal_SetBitAtomic((&Ccu6RegPtr->T12MSEL.U), \
                        (CcChannelNumber * ICU_CCU_MSEL_BITS_PER_CHANNEL), \
                        ICU_CCU_MSEL_BITS_PER_CHANNEL, \
                        (uint32)ICU_CCU_CAPTURE_MODE3);
    }
  }
  else
  {
    /* [cover parentID={718919FB-6562-45eb-BC91-1CAE069D312A}]
    Channel is configured to Capture Mode 1
    [/cover] */
    Mcal_SetBitAtomic((&Ccu6RegPtr->T12MSEL.U), \
                      (CcChannelNumber * ICU_CCU_MSEL_BITS_PER_CHANNEL), \
                      ICU_CCU_MSEL_BITS_PER_CHANNEL, \
                      (uint32)ICU_CCU_CAPTURE_MODE1);
  }
  /* MISRA2012_RULE_2_2_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the variable CcuActiveEdge is
   * accessed using assembly instruction. */
}
#endif

#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) && \
(ICU_17_TIMERIP_SIGNAL_MEASUREMENT_API ==STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {308DE50F-8796-4abe-BFDC-86162BF74E01}]     **
**                                                                            **
** Syntax : LOCAL_INLINE void Icu_lGtmStopSignalMeasurement(                  **
**                      const uint16 GlobalChannelNumber   )                  **
**                                                                            **
** Description :     Function to configure the channel to stop signal         **
**                   measurement                                              **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  GlobalChannelNumber - Channel Number                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lGtmStopSignalMeasurement(
  const uint16 GlobalChannelNumber)
{
  Ifx_GTM_TIM_CH* TimChannelRegPtr;   /* Pointer to TIM Channel Reg    */
  uint8 ModuleNo;                            /* Holds the TIM module Number   */
  uint8 ChannelNo;                           /* Holds the TIM Channel Number  */

  /* Calculate Module Id of the TIM channel */
  ModuleNo = (uint8)((GlobalChannelNumber / ICU_GTM_CHANNELS_PER_TIM_MODULE) \
                     & ICU_GTM_MODULE_NO_MSK);
  /* Calculate Channel number of the TIM channel */
  ChannelNo = (uint8)(GlobalChannelNumber % ICU_GTM_CHANNELS_PER_TIM_MODULE);

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TimChannelRegPtr = GTM_TIM_CH_POINTER(ModuleNo, ChannelNo);
  /* Channel is disabled */
  TimChannelRegPtr->CTRL.U &= ~ICU_GTM_TIM_ENABLE_CHANNEL ;

}
#endif

#if (ICU_17_TIMERIP_SIGNAL_MEASUREMENT_API == STD_ON)
#if (ICU_17_TIMERIP_CCU6_USED == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {949930E4-80CC-426a-B285-318FE3622861}]     **
**                                                                            **
** Syntax : LOCAL_INLINE void Icu_lCcuStopSignalMeas(const uint16 CellUsed)   **
**                                                                            **
** Description :     Function to disable a channel configured in signal       **
**                   measurement mode                                         **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  CellUsed - CCU6x Kernel and Channel information          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lCcuStopSignalMeas(const uint16 CellUsed)
{
  volatile Ifx_CCU6 *Ccu6RegPtr; /* Variable to hold the current CCU6 address */
  uint8 CcChannelNumber;    /* To hold the CC channel number */


  /* Upper Nibble of AssignedHwUnitNumber holds the Channel Number */
  CcChannelNumber = (uint8)
                  ((CellUsed & ICU_CCU_GET_COMPARATOR) >> ICU_BRING_TO_BIT_0);

  /* Get the base address of the Kernal */
  Ccu6RegPtr = &(&MODULE_CCU60)[CellUsed & ICU_CCU_GET_KERNEL];

  /* Disable interrupt for the channel */
  Mcal_SetBitAtomic((&Ccu6RegPtr->IEN.U), \
                    (CcChannelNumber * ICU_CCU_IS_BITS_PER_CHANNEL), \
                    ICU_CCU_IS_BITS_PER_CHANNEL, \
                    (uint32)0);

  /* Channel is configured to Capture Compare Mode Switched off */
  Mcal_SetBitAtomic((&Ccu6RegPtr->T12MSEL.U), \
                    (CcChannelNumber * ICU_CCU_MSEL_BITS_PER_CHANNEL), \
                    ICU_CCU_MSEL_BITS_PER_CHANNEL, \
                    (uint32)ICU_CCU_MSEL_RESET_VAL);
  /* MISRA2012_RULE_2_2_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the variable Ccu6RegPtr is
   * accessed using assembly instruction. */
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer Ccu6RegPtr is
   * accessed using assembly instruction. */
}
#endif
#endif

#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) && \
(ICU_17_TIMERIP_GET_TIME_ELAPSED_API ==STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {05C9A1D6-74C7-4060-A45E-8E2A0FC39635}]     **
**                                                                            **
** Syntax : LOCAL_INLINE Icu_17_TimerIp_ValueType Icu_lGtmGetTimeElapsed(     **
**           const uint16 GlobalChannelNumber,                                **
**           uint32 *const GblIndexStatusPtr    )                             **
** Description :     Function to get the High/Low/Period values of a channel  **
**                   running in Signal Measurement mode                       **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  GlobalChannelNumber - Channel Number                     **
**                   GblIndexStatusPtr - Pointer to the channel flags         **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     Icu_17_TimerIp_ValueType : High Time/Low Time or Period  **
**                   is returned depending on the signal mode parameter       **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Icu_17_TimerIp_ValueType Icu_lGtmGetTimeElapsed(
  const uint16 GlobalChannelNumber,
  uint32 *const GblIndexStatusPtr)
{
  Ifx_GTM_TIM_CH* TimChannelRegPtr;          /* Pointer to TIM Channel Reg    */
  uint32 RetVal;                             /* Return Value                  */
  uint8 ModuleNo;                            /* Holds the TIM module Number   */
  uint8 ChannelNo;                           /* Holds the TIM Channel Number  */

  /* Calculate Module Id of the TIM channel */
  ModuleNo = (uint8)((GlobalChannelNumber / ICU_GTM_CHANNELS_PER_TIM_MODULE) \
                     & ICU_GTM_MODULE_NO_MSK);
  /* Calculate Channel number of the TIM channel */
  ChannelNo = (uint8)(GlobalChannelNumber % ICU_GTM_CHANNELS_PER_TIM_MODULE);

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TimChannelRegPtr = GTM_TIM_CH_POINTER(ModuleNo, ChannelNo);
  /* [cover parentID={7F8649FD-0123-4593-8182-10C89AE0D9AE}]
  Set elapsed time to zero
  [/cover] */
  RetVal = 0U;
  /* [cover parentID={78BCC0CD-F5B4-4f36-991D-51E9B18863E9}]
  Check if a new value is available
  [/cover] */
  /* Check if a new value is available*/
  if(1U == ((TimChannelRegPtr->IRQ.NOTIFY.U) & ICU_GTM_NEWVAL_FLAG_SET))
  {
    /* [cover parentID={B094F714-9860-44eb-A6F6-67B1657BF02E}]
    Set a flag to indicate GetInputState
    [/cover] */
    Mcal_SetBitAtomic( GblIndexStatusPtr, (sint32)ICU_CHNL_STATUS_POS, \
                      ICU_CHNL_STATUS_BIT_LENGTH, (uint32)ICU_ACTIVITY_STARTED);
    /* Clear the flag */
    Mcal_SetBitAtomic( \
      GblIndexStatusPtr, (sint32)ICU_SIGNALMESURE_INPUT_STAT_POS,\
      ICU_SIGNALMESURE_INPUT_STAT_LENGTH, (uint32)0);
    /* Clear Newval IRQ notify */
    /* [cover parentID={3916A106-C301-4478-96A1-1B7EC0EC6F98}]
    Clear Newval IRQ notify
    [/cover] */
    TimChannelRegPtr->IRQ.NOTIFY.U = 1;
    /* [cover parentID={04171171-C332-4349-88B7-B3266E2FEEF6}]
    Calculate the elapsed time depending on mode.
    HIGH TIME/LOW TIME, PERIOD - GPR1
    [/cover] */
    RetVal = TimChannelRegPtr->GPR1.B.GPR1;
  }
  /* [cover parentID={07E2ACDF-AE94-49c5-A956-1631779563AB}]
  If a flag is set by GetInputState
  [/cover] */
  /* No new value available, check if a flag is set by GetInputState */
  else if(1U == Mcal_GetBitAtomic(*GblIndexStatusPtr,
            ICU_SIGNALMESURE_INPUT_STAT_POS,ICU_SIGNALMESURE_INPUT_STAT_LENGTH))
  {
    /* Clear the flag */
    /* [cover parentID={39C4631B-4F78-40c3-B252-CD9B4CC56FF1}]
    Clear the flag
    [/cover] */
    Mcal_SetBitAtomic( \
      GblIndexStatusPtr, (sint32)ICU_SIGNALMESURE_INPUT_STAT_POS,\
      ICU_SIGNALMESURE_INPUT_STAT_LENGTH, (uint32)0);
    /* [cover parentID={DB87715E-DAA4-49bd-A140-A2845BE85519}]
    Calculate the elapsed time depending on mode.
    HIGH TIME/LOW TIME, PERIOD - GPR1
    [/cover] */
    RetVal = TimChannelRegPtr->GPR1.B.GPR1;
  }
  else
  {
    /* No valid time available.*/
  }
  return(RetVal);
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer GblIndexStatusPtr is
   * accessed using assembly instruction. */
}
#endif

#if (ICU_17_TIMERIP_CCU6_USED == STD_ON) && \
(ICU_17_TIMERIP_GET_TIME_ELAPSED_API ==STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {2FD5A91F-05B4-4057-A054-C480CCD5B8B7}]     **
**                                                                            **
** Syntax : LOCAL_INLINE Icu_17_TimerIp_ValueType Icu_lCcuGetTimeElapsed(     **
**          const uint16 CellUsed,                                            **
**          uint32 *const GblIndexStatusPtr)                                  **
**                                                                            **
** Description :     Function to get the Period Time information of the       **
**                   signal measurement channel                               **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  CellUsed - CCU6x Kernel and Channel information          **
**                   GlbIndexStatusPtr - Pointer to the channel flags         **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     Icu_17_TimerIp_ValueType : Period value                  **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Icu_17_TimerIp_ValueType Icu_lCcuGetTimeElapsed(
  const uint16 CellUsed,
  uint32 *const GblIndexStatusPtr)
{
  volatile Ifx_CCU6 *Ccu6RegPtr; /* Variable to hold the current CCU6 address */
  /* MISRA2012_RULE_19_2_JUSTIFICATION: Union based type defintion for SFR
     access. */
  volatile Ifx_CCU6_CC6SR *CcuSrRegPtr; /* Pointer to SR registers of CCU */
  /* MISRA2012_RULE_19_2_JUSTIFICATION: Union based type defintion for SFR
     access. */
  volatile Ifx_CCU6_CC6R *CcuRRegPtr;   /* Pointer to R registers of CCU */
  Icu_17_TimerIp_ValueType ElapsedTime;/* Elapsed Time value */
  uint8 CcChannelNumber;    /* To hold the CC channel number */
  uint32 CcuCmpstatValue;   /* To hold CCU Kernel comparision status */
  uint16 CcuSrRegVal;
  uint16 CcuRRegVal;
  /* Elapsed time is initialized to 0 */
  /* [cover parentID={6C62F57C-AC35-42ac-99AE-537AB820179F}]
  Elapsed time is initialized to 0
  [/cover] */
  ElapsedTime = 0U;


  /* Upper Nibble of AssignedHwUniCcuSrRegValPtrtNumber holds the Chl Number */
  CcChannelNumber =
    ((uint8)CellUsed & ICU_CCU_GET_COMPARATOR) >> ICU_BRING_TO_BIT_0;

  /* Get the base address of the Kernel */
  Ccu6RegPtr = &(&MODULE_CCU60)[CellUsed & ICU_CCU_GET_KERNEL];

  /* Assign SR and R register base addresses */
  CcuSrRegPtr = &(Ccu6RegPtr->CC6SR[0]);
  CcuRRegPtr = &(Ccu6RegPtr->CC6R[0]);

  /* Read SR reg and R reg value
   * Check if both read values are same, if yes, then read the SR value again.
   * This is to also accommodate any edges occurred during this read */
  CcuSrRegVal = (uint16)CcuSrRegPtr[CcChannelNumber].U;
  CcuRRegVal = (uint16)CcuRRegPtr[CcChannelNumber].U;
  /* [cover parentID={54667A3E-A685-49ca-A74B-24DF90A915E3}]
  If both SR and R register values are same
  [/cover] */
  if(CcuSrRegVal == CcuRRegVal)
  {
    CcuSrRegVal = (uint16)CcuSrRegPtr[CcChannelNumber].U;
  }

  /* Read the Compare status flags */
  CcuCmpstatValue = Ccu6RegPtr->CMPSTAT.U;
  /* Extract the compare status flag of the channel */
  CcuCmpstatValue &= ((uint32)1U << (CcChannelNumber));

  /* Availability of a new value is ascertained by checking CcuRRegVal
     to be 0 */
  /* [cover parentID={FB623FE3-ABEC-4f64-8559-1CD24D92A4AA}]
  If atleast one period has passed.
  [/cover] */
  if(CcuRRegVal != (uint16)0U)
  {
    /* Check if a flag is set(HW or SW) to indicate an availability of
     * new value */
    /* [cover parentID={EE744317-52CA-4906-AF76-30B994EB305D}]
    If a flag is set indicting availability of new value
    [/cover] */
    if(0U != CcuCmpstatValue)
    {
      /* [cover parentID={6408B1A1-EF78-4da4-B9EB-2DDD20B35514}]
      Clear ST Flag(HW)
      [/cover] */
      /* Clear ST Flag(HW) */
      Ccu6RegPtr->CMPMODIF.U =
                              CcuCmpstatValue << ICU_CCU6_CMPMODIF_CLEAR_OFFSET;
      /* [cover parentID={FDA40C53-3DFD-45d4-8442-50879E68A9CE}]
      Determine elapsed time. R - SR
      [/cover] */
      ElapsedTime = Icu_lCcuSubtractWithOverflow(
                      CcuSrRegVal,
                      CcuRRegVal);
      /* [cover parentID={A5CAD2BE-A878-4d31-9581-ABCADE816DA1}]
      Set channel active status flag
      [/cover] */
      Mcal_SetBitAtomic( \
        GblIndexStatusPtr, (sint32)ICU_CHNL_STATUS_POS,\
        ICU_CHNL_STATUS_BIT_LENGTH, (uint32)ICU_ACTIVITY_STARTED);
      /* Clear the flag */
      Mcal_SetBitAtomic( \
        GblIndexStatusPtr, (sint32)ICU_SIGNALMESURE_INPUT_STAT_POS,\
        ICU_SIGNALMESURE_INPUT_STAT_LENGTH, (uint32)0);
    }
    /* [cover parentID={1F0CFD34-5C15-421e-96D9-ED916AB84008}]
    If a flag is set by GetInputState
    [/cover] */
    else if(1U == Mcal_GetBitAtomic(*GblIndexStatusPtr,
      ICU_SIGNALMESURE_INPUT_STAT_POS, ICU_SIGNALMESURE_INPUT_STAT_LENGTH))
    {
      /* [cover parentID={12DEBD3C-AA13-43db-8C6E-810F340E454D}]
      Clear the GetInputState flag
      [/cover] */
      /* Clear the flag */
      Mcal_SetBitAtomic( \
        GblIndexStatusPtr, (sint32)ICU_SIGNALMESURE_INPUT_STAT_POS,\
        ICU_SIGNALMESURE_INPUT_STAT_LENGTH, (uint32)0);
      /* [cover parentID={9F4C81EE-7FF4-4372-B423-3AF99B32C9A8}]
      Determine elapsed time. R - SR
      [/cover] */
      ElapsedTime = Icu_lCcuSubtractWithOverflow(
                      CcuSrRegVal,
                      CcuRRegVal);
    }
    else
    {
      /* Return 0*/
    }
  }
  else
  {
    /* Return 0*/
  }
  return(ElapsedTime);
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer GblIndexStatusPtr is
   * accessed using assembly instruction. */
}
#endif

#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) && \
(ICU_17_TIMERIP_GET_DUTY_CYCLE_VALUES_API ==STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {B055068D-716F-480a-B3F5-C7C290BEBBDB}]     **
**                                                                            **
** Syntax : LOCAL_INLINE void Icu_lGtmGetDutyCycleValues(                     **
**                      const uint16 GlobalChannelNumber,                     **
**                      uint32* const GlbIndexStatusPtr,                      **
**                      Icu_17_TimerIp_DutyCycleType *const DutyCycleValues)  **
**                                                                            **
** Description :     Function to get the Period and Duty Cycle value          **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  GlobalChannelNumber - Channel Number                     **
**                                                                            **
** Parameters (in-out): GlbIndexStatusPtr - Pointer to the channel flags      **
**                                                                            **
** Parameters (out): DutyCycleValues - Pointer to store Duty and Period       **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lGtmGetDutyCycleValues(
  const uint16 GlobalChannelNumber,
  uint32 *const GlbIndexStatusPtr,
  Icu_17_TimerIp_DutyCycleType *const DutyCycleValues)
{
  Ifx_GTM_TIM_CH *TimChannelRegPtr;   /* Pointer to TIM Channel Reg    */
  uint32 Gpr0Val;
  uint32 Gpr1Val;
  uint8 ModuleNo;                            /* Holds the TIM module Number   */
  uint8 ChannelNo;                           /* Holds the TIM Channel Number  */

  /* Initialize the read register values */
  /* [cover parentID={4C9F6628-ADA7-48c4-968F-041E11181C1C}]
  Consider GPR0 and GPR1 register values as 0.
  [/cover] */
  Gpr0Val = 0U;
  Gpr1Val = 0U;
  /* Calculate Module Id of the TIM channel */
  ModuleNo = (uint8)((GlobalChannelNumber / ICU_GTM_CHANNELS_PER_TIM_MODULE) \
                     & ICU_GTM_MODULE_NO_MSK);
  /* Calculate Channel number of the TIM channel */
  ChannelNo = (uint8)(GlobalChannelNumber % ICU_GTM_CHANNELS_PER_TIM_MODULE);

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TimChannelRegPtr = GTM_TIM_CH_POINTER(ModuleNo, ChannelNo);
  /* [cover parentID={EE733FBF-D8E2-49ee-92F7-EFEE72671F29}]
  If a new value is available inTIM channel
  [/cover] */
  /* Check if a new value is available*/
  if(0U != (TimChannelRegPtr->IRQ.NOTIFY.U & ICU_GTM_NEWVAL_FLAG_SET))
  {
    /* Set a flag to indicate for GetInputState */
    Mcal_SetBitAtomic( \
                       GlbIndexStatusPtr, (sint32)ICU_CHNL_STATUS_POS, \
                       1, (uint32)ICU_ACTIVITY_STARTED);
    /* Clear Newval IRQ notify */
    /* [cover parentID={AB65632C-5557-4760-8E29-B770B3C41543}]
    Clear Newval IRQ notify
    [/cover] */
    TimChannelRegPtr->IRQ.NOTIFY.U = 1;
    /* Clear the flag */
    Mcal_SetBitAtomic( \
      GlbIndexStatusPtr, (sint32)ICU_SIGNALMESURE_INPUT_STAT_POS,\
      ICU_SIGNALMESURE_INPUT_STAT_LENGTH, (uint32)0);
    /* ENTER CRITICAL SECTION */
    SchM_Enter_Icu_17_TimerIp_GtmGetDutyCycle();
    /* Calculate the retval depending on mode */
    Gpr0Val = TimChannelRegPtr->GPR0.U;
    Gpr1Val = TimChannelRegPtr->GPR1.U;
    if((Gpr0Val & ICU_TIM_EDGE_COUNT_INFO) !=
        (Gpr1Val & ICU_TIM_EDGE_COUNT_INFO))
    {
      Gpr0Val = TimChannelRegPtr->GPR0.U;
    }
    SchM_Exit_Icu_17_TimerIp_GtmGetDutyCycle();
    /* EXIT CRITICAL SECTION */
  }
  /* [cover parentID={0A095D16-C8D7-4679-A18E-4FA88CA07A9D}]
  If a flag is set by GetInputState
  [/cover] */
  /* No new value available, check if a flag is set by GetInputState */
  else if(1U == \
    Mcal_GetBitAtomic(*GlbIndexStatusPtr,
            ICU_SIGNALMESURE_INPUT_STAT_POS,ICU_SIGNALMESURE_INPUT_STAT_LENGTH))
  {
    /* [cover parentID={DD9A0FC3-F3D5-4694-BA1F-E0AC2B745FBB}]
    Clear the flag
    [/cover] */
    /* Clear the flag */
    Mcal_SetBitAtomic( \
      GlbIndexStatusPtr, (sint32)ICU_SIGNALMESURE_INPUT_STAT_POS,\
      ICU_SIGNALMESURE_INPUT_STAT_LENGTH, (uint32)0);
    /* Calculate the retval depending on mode */
    /* ENTER CRITICAL SECTION */
    SchM_Enter_Icu_17_TimerIp_GtmGetDutyCycle();
    /* Calculate the retval depending on mode */
    Gpr0Val = TimChannelRegPtr->GPR0.U;
    Gpr1Val = TimChannelRegPtr->GPR1.U;
    if((Gpr0Val & ICU_TIM_EDGE_COUNT_INFO) !=
        (Gpr1Val & ICU_TIM_EDGE_COUNT_INFO))
    {
      Gpr0Val = TimChannelRegPtr->GPR0.U;
    }
    SchM_Exit_Icu_17_TimerIp_GtmGetDutyCycle();
    /* EXIT CRITICAL SECTION */
  }
  else
  {
    /* No valid time available.*/
  }
  /* [cover parentID={8541F42F-7815-48a7-B0C9-F8B9019C0678}]
  Update the duty cycle as GPR0 and period as GPR1 with a mask of 24 bit.
  [/cover] */
  DutyCycleValues->ActiveTime = Gpr0Val & (ICU_24BIT_MASK);
  DutyCycleValues->PeriodTime = Gpr1Val & (ICU_24BIT_MASK);
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer GlbIndexStatusPtr is
   * accessed using assembly instruction. */
}
#endif

#if (ICU_17_TIMERIP_GET_INPUT_STATE_API == STD_ON)
#if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
(ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {8CFE817D-7678-49f5-B2FB-A53603B06737}]     **
**                                                                            **
** Syntax : LOCAL_INLINE uint32 Icu_lGetInputStateDetCheck (                  **
**                           const Icu_17_TimerIp_ChannelType Channel         **
**                           const uint8 CoreId   )                           **
** Description :      Local function :Service for DET check in                **
**                                   Icu_17_TimerIp_GetInputState() function  **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        None                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Reentrant for different channel                         **
**                                                                            **
** Parameters (in):   Channel - Numeric identifier of the ICU channel         **
**                    CoreId - Core id index                                  **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value:      ErrorFlag (uint32)                                      **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Icu_lGetInputStateDetCheck(
  const Icu_17_TimerIp_ChannelType Channel,
  const uint8 CoreId)
{
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr; /* ROM pointer */
  uint32 ErrorFlag = ICU_ERROR_NOT_FOUND;
  uint8 CoreChIndex;
  #if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  uint32* GlbIndexStatusPtr;
  uint32 WakeupStatus;
  Icu_17_TimerIp_ModeType IcuMode;
  #endif
  /* Verify whether Init has been called */
  /* [cover parentID={7ABDBD9B-27B9-4244-AFE4-8FF8310E1C46}]
  Varify any error is there for DET
  [/cover] */
  ErrorFlag = Icu_lInitCallVerify(ICU_17_TIMERIP_SID_GETINPUTSTATE, CoreId);
  /* [cover parentID={B1AEB953-7125-42fa-B77A-6500640F93F3}]
  Any DET reported
  [/cover] */
  if (ErrorFlag != ICU_ERROR_FOUND)
  {
    /* if UNINIT occurred then Icu_17_TimerIp_ConfigPtr is not valid.
       So need not to check  for other DET errors */
    /* Verify whether Invalid channel number has been sent */
    /* [cover parentID={F0E1770B-92A5-4bf1-A707-8831E97E5B71}]
    Verify whether Invalid channel number has been sent
    [/cover] */
    ErrorFlag = Icu_lChannelVerify(ICU_17_TIMERIP_SID_GETINPUTSTATE,
                                   Channel, CoreId);
    /* [cover parentID={F535FF38-E33B-4bb7-A2D3-5BFE8685955B}]
    Any DET reported
    [/cover] */
    if(ErrorFlag != ICU_ERROR_FOUND)
    {
      /* Initialize ICU configured channel ROM pointer */
      CoreChIndex = Icu_lGetCoreChIndex((uint8)Channel);
      LocalIcuChanPtr = &((Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->
                                                ChannelConfigPtr)[CoreChIndex]);
      /* [cover parentID={C22C40D4-5EB5-413e-8716-E55E2985A3BF}]
      Is channel mode signal measrement or edge detect?
      [/cover] */
      if (!( (LocalIcuChanPtr->IcuProperties.MeasurementMode
              == (uint32)ICU_17_TIMERIP_MODE_SIGNAL_MEASUREMENT) ||
             (LocalIcuChanPtr->IcuProperties.MeasurementMode
              == (uint32)ICU_17_TIMERIP_MODE_SIGNAL_EDGE_DETECT))
         )
      {
        /* [cover parentID={91A3A5C5-BD23-4b9e-BB00-F2DC2E3BE46E}]
        Report error to indicate that the channel is invalid and set error flag
        to error found.
        [/cover] */
        ErrorFlag = (uint32)ICU_ERROR_FOUND;
        /*  Icu_17_TimerIp_GetInputState is valid only for Signal
            Measurement
            and Signal Edge Detection.
         */
        Icu_lReportError(
          ICU_17_TIMERIP_SID_GETINPUTSTATE,
        ICU_17_TIMERIP_E_PARAM_CHANNEL);/* End of report error */
      }
      /* [cover parentID={5C06408E-9AFA-4074-AD5E-907D89312706}]
      Is timeout feature exclusive?
      [/cover] */
      else if((uint32)ICU_SET_BIT == LocalIcuChanPtr->IcuProperties.IsTimeOutExclusive)
      {
        ErrorFlag = (uint32) ICU_ERROR_FOUND;
        /* [cover parentID={F0442C6F-4BDC-415e-9DE1-03AE433C9397}]
        Report invalid channel
        [/cover] */
        Icu_lReportError(
          ICU_17_TIMERIP_SID_GETINPUTSTATE,
          ICU_17_TIMERIP_E_PARAM_CHANNEL);
      }
      else
      {
      #if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
        /* Extract the address to the channel status */
        GlbIndexStatusPtr =
        &((Icu_17_TimerIp_Varlist[CoreId]->GlbIndexStatusBasePtr)[CoreChIndex]);
        /*Read ICU Mode*/
        WakeupStatus = Mcal_GetBitAtomic(*GlbIndexStatusPtr, \
                       ICU_CHNL_WAKEUP_CAPABLE_POS, ICU_CHNL_WAKEUP_BIT_LENGTH);
        IcuMode = Icu_17_TimerIp_Varlist[CoreId]->GlobalMode;
        /* [cover parentID={F7CBC2FF-467C-4c4d-A086-C5DDA31FA48E}]
        Is the driver mode SLEEP and channel is not wakeup capable?
        [/cover] */
        if((ICU_17_TIMERIP_MODE_SLEEP == IcuMode) && (1U != WakeupStatus))
        {
          /* [cover parentID={8E3E8C12-04AE-49ba-B843-501AAECEE197}]
          Report invalid mode safety error and set error flag to error found.
          [/cover] */
          ErrorFlag = (uint32)ICU_ERROR_FOUND;
          Mcal_ReportSafetyError(
                ICU_17_TIMERIP_MODULE_ID,
                ICU_17_TIMERIP_INSTANCE_ID, ICU_17_TIMERIP_SID_GETINPUTSTATE,
                ICU_17_TIMERIP_E_INVALID_MODE);/* End of report to Safety */
        }
      #endif
      }
    }
  }
  return ErrorFlag;
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer GlbIndexStatusPtr is
   * accessed using assembly instruction. */
}/* End of Icu_lGetInputStateDetCheck() function */
#endif
#endif

#if (ICU_17_TIMERIP_GTM_TIM_USED  == STD_ON) && \
(ICU_17_TIMERIP_GET_INPUT_STATE_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {630A2FBB-3804-4084-A397-8D0659D2C18D}]     **
**                                                                            **
** Syntax : LOCAL_INLINE Icu_17_TimerIp_InputStateType Icu_lGtmGetInputState( **
**                 const uint16 GlobalChannelNumber,                          **
**                 uint32* const GlbIndexStatusPtr      )                     **
**                                                                            **
** Description :     Function to get the Input State of TIM channel           **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  GlobalChannelNumber - Channel Number                     **
**                   GlbIndexStatusPtr - Pointer to the channel flags         **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     ICU_17_TIMERIP_ACTIVE - A new value is available         **
**                   ICU_17_TIMERIP_IDLE - No new value is available          **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Icu_17_TimerIp_InputStateType Icu_lGtmGetInputState(
  const uint16 GlobalChannelNumber,
  uint32* const GlbIndexStatusPtr)
{
  Ifx_GTM_TIM_CH* TimChannelRegPtr;   /* Pointer to TIM Channel Reg    */
  Icu_17_TimerIp_InputStateType RetVal;
  uint8 ModuleNo;                            /* Holds the TIM module Number   */
  uint8 ChannelNo;                           /* Holds the TIM Channel Number  */
  uint32 NotifyValue;

  /* Calculate Module Id of the TIM channel */
  ModuleNo = (uint8)((GlobalChannelNumber / ICU_GTM_CHANNELS_PER_TIM_MODULE) \
                     & ICU_GTM_MODULE_NO_MSK);
  /* Calculate Channel number of the TIM channel */
  ChannelNo = (uint8)(GlobalChannelNumber % ICU_GTM_CHANNELS_PER_TIM_MODULE);

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TimChannelRegPtr = GTM_TIM_CH_POINTER(ModuleNo, ChannelNo);
  /* [cover parentID={C0C4190B-9BB3-45da-B995-3BEA270CDA9C}]
  Are the notifications enabled?
  [/cover] */
  if(1U != Mcal_GetBitAtomic(*GlbIndexStatusPtr,
                        ICU_CHNL_NOTIF_PRESENCE_POS, ICU_CHNL_NOTIF_BIT_LENGTH))
  {
    /* Read and clear all Pending Interrupts */
    /* [cover parentID={F5E527A4-343E-4698-B1D7-E88B3E2480AA}]
    Read notification flags and clear all flags.
    [/cover] */
    /* MISRA2012_RULE_11_8_JUSTIFICATION: SFR access. Since the input
     * argument for the API discards volatile keyword. No side effects foreseen
     * by violating this MISRA rule*/
    NotifyValue = Mcal_Swap(&(TimChannelRegPtr->IRQ.NOTIFY.U), \
                            ICU_GTM_CLEAR_INTERRUPTS, ICU_SWAP_32BIT_MASK);
    /* [cover parentID={145E2798-3812-48e0-AEED-F67A622EAE8F}]
    If there are any pending newval notifications
    [/cover] */
    if(1U == (NotifyValue & ICU_GTM_TIM_NEWVAL_MASK))
    {
      /* [cover parentID={E5B295FB-4B31-4607-BE33-4A4FFA29ED90}]
      Set input state active
      [/cover] */
      RetVal = ICU_17_TIMERIP_ACTIVE;
      /* [cover parentID={A170DDDE-2388-4d43-B637-ECF0EE8FC457}]
      Set a flag to indicate for GetTimeElapsed and GetDuty
      [/cover] */
      /* Set a flag to indicate for GetTimeElapsed and GetDuty */
      Mcal_SetBitAtomic( \
        GlbIndexStatusPtr, (sint32)ICU_SIGNALMESURE_INPUT_STAT_POS,\
        ICU_SIGNALMESURE_INPUT_STAT_LENGTH, (uint32)ICU_ACTIVITY_STARTED);
      /* Re-Set a flag */
      Mcal_SetBitAtomic( \
        GlbIndexStatusPtr, (sint32)ICU_CHNL_STATUS_POS,\
        ICU_CHNL_STATUS_BIT_LENGTH, (uint32)ICU_17_TIMERIP_IDLE);
    }
    /* [cover parentID={C6BC2FFC-4DAB-40f2-935E-4FE6E9E9757E}]
    Is channel active status flag set?
    [/cover] */
    else if(1U == Mcal_GetBitAtomic(*GlbIndexStatusPtr, ICU_CHNL_STATUS_POS,
                                    ICU_CHNL_STATUS_BIT_LENGTH))
    {
      /* [cover parentID={133C4AAB-9439-4a45-A35F-8F40563CB047}]
      Set input state active
      [/cover] */
      RetVal = ICU_17_TIMERIP_ACTIVE;
      /* [cover parentID={B8D46D0C-0011-483a-BEB8-3B20AD7C3C44}]
      Re-Set the flag
      [/cover] */
      /* Re-Set a flag */
      Mcal_SetBitAtomic( \
        GlbIndexStatusPtr, (sint32)ICU_CHNL_STATUS_POS,\
        ICU_CHNL_STATUS_BIT_LENGTH, (uint32)ICU_17_TIMERIP_IDLE);
    }
    else
    {
      RetVal = ICU_17_TIMERIP_IDLE;
    }
  }
  /* [cover parentID={D13D836E-3432-4cba-8A06-EBC09F1B92F0}]
  Is the channel status active?
  [/cover] */
  else if(1U == Mcal_GetBitAtomic(*GlbIndexStatusPtr, ICU_CHNL_STATUS_POS,
                                  ICU_CHNL_STATUS_BIT_LENGTH))
  {
    /* [cover parentID={3F9235E3-3907-4b0a-A045-18B4263F04B6}]
    Set input state active.
    [/cover] */
    RetVal = ICU_17_TIMERIP_ACTIVE;
    /* [cover parentID={541CEF54-14DF-4c1f-ACD9-01E3B0A25581}]
      Reset channel active flag atomically.
    [/cover] */
    /* Re-Set a flag */
    Mcal_SetBitAtomic( \
                       GlbIndexStatusPtr, (sint32)ICU_CHNL_STATUS_POS, \
                       1, (uint32)ICU_17_TIMERIP_IDLE);
  }
  else
  {
    /* [cover parentID={8A6EF790-014B-46b9-97A3-3934FD321DE9}]
    Initialize input state to IDLE.
    [/cover] */
    RetVal = ICU_17_TIMERIP_IDLE;
  }
  return(RetVal);
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer GlbIndexStatusPtr is
   * accessed using assembly instruction. */
}
#endif

#if (ICU_17_TIMERIP_CCU6_USED == STD_ON) && \
(ICU_17_TIMERIP_GET_INPUT_STATE_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {B180D5AD-AEEC-4f7c-9BA0-DEF6664D9942}]     **
**                                                                            **
** Syntax : LOCAL_INLINE Icu_17_TimerIp_InputStateType Icu_lCcu6GetInputState(**
**                const uint16 CellUsed,                                      **
**                uint32* const GlbIndexStatusPtr,                            **
**                const uint8 Mode,                                           **
**                const uint8 Property)                                       **
**                                                                            **
** Description :     Function to get the Input State for CCU6 channel         **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  CellUsed - CCU6x Kernel and Channel information.         **
**                   GlbIndexStatusPtr - Pointer to the channel flags         **
**                   Mode - Measurement mode of the Channel                   **
**                   Property - Measurement Property type                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     ICU_17_TIMERIP_ACTIVE - A new value is available         **
**                   ICU_17_TIMERIP_IDLE - No new value is available          **
*******************************************************************************/
LOCAL_INLINE Icu_17_TimerIp_InputStateType Icu_lCcu6GetInputState(
  const uint16 CellUsed,
  uint32* const GlbIndexStatusPtr,
  const uint8 Mode,
  const uint8 Property)
{
  Icu_17_TimerIp_InputStateType RetVal;
  volatile Ifx_CCU6 *Ccu6RegPtr; /* Variable to hold the current CCU6 address */
  uint8 CcChannelNumber;    /* To hold the CC channel number */
  uint8 CmpStatValue;
  uint8 NotifStatus;

  /* Upper Nibble of AssignedHwUnitNumber holds the Channel Number */
  CcChannelNumber = (uint8)
      ((CellUsed & ICU_CCU_GET_COMPARATOR)>> ICU_BRING_TO_BIT_0);

  /* Get the base address of the Kernal */
  Ccu6RegPtr = &(&MODULE_CCU60)[CellUsed & ICU_CCU_GET_KERNEL];
  NotifStatus = (uint8)Mcal_GetBitAtomic(*GlbIndexStatusPtr,
      ICU_CHNL_NOTIF_PRESENCE_POS, ICU_CHNL_NOTIF_BIT_LENGTH);
  CmpStatValue =
    (uint8)Mcal_GetBitAtomic(Ccu6RegPtr->CMPSTAT.U, CcChannelNumber, 1) ;
  /* ST flag for Signal Measurement(Period) and Edge Detection */
  /* [cover parentID={B18255B9-091E-4a56-8480-2FC82DEA5EA3}]
  Is the compare status HW flag set in case of Edge detect channel with
  notifications enabled and Signal Measurement Period type channel?
  [/cover] */
  if((1U == CmpStatValue) &&
    (((uint8)ICU_17_TIMERIP_PERIOD_TIME == Property) ||
    (((uint8)ICU_17_TIMERIP_MODE_SIGNAL_EDGE_DETECT == Mode) &&
    (1U != NotifStatus))))
  {
    /* Return Active */
    /* [cover parentID={DAC60ABF-16F9-43af-9A3B-91012F3754B5}]
    Set input state ACTIVE
    [/cover] */
    RetVal = ICU_17_TIMERIP_ACTIVE;
    if((uint8)ICU_17_TIMERIP_MODE_SIGNAL_MEASUREMENT == Mode)
    {
      /* [cover parentID={B641EF4B-75C0-42a0-A82D-5D809D79D3FE}]
      Set bit7 of channel flags variable, to indicate new period is available.
      [/cover] */
      Mcal_SetBitAtomic( \
        GlbIndexStatusPtr, (sint32)ICU_SIGNALMESURE_INPUT_STAT_POS,\
        ICU_SIGNALMESURE_INPUT_STAT_LENGTH, (uint32)1);
    }
    /* [cover parentID={441946B4-0210-41a0-ADEB-B8E85127B441}]
    Clear ST flag
    [/cover] */
    /* Clear ST flag */
    Ccu6RegPtr->CMPMODIF.U = ((uint32)1U <<
                     ((uint8)ICU_CCU6_CMPMODIF_CLEAR_OFFSET + CcChannelNumber));
    /* Re-Set a flag */
    Mcal_SetBitAtomic( \
                       GlbIndexStatusPtr, (sint32)ICU_CHNL_STATUS_POS, \
                       ICU_CHNL_NOTIF_BIT_LENGTH, (uint32)ICU_17_TIMERIP_IDLE);
  }
  /* [cover parentID={C44B55A0-AAE6-4316-B0AA-654480170399}]
  If channel is Active
  [/cover] */
  else if(1U == Mcal_GetBitAtomic(*GlbIndexStatusPtr, ICU_CHNL_STATUS_POS,
                                  ICU_CHNL_STATUS_BIT_LENGTH))
  {
    /* [cover parentID={736C5910-41CE-4903-8CBB-D9E044B3040A}]
    Set input state ACTIVE
    [/cover] */
    RetVal = ICU_17_TIMERIP_ACTIVE;
    /* [cover parentID={D8E2B573-B46D-45d4-A0E2-49EE3309380E}]
    Reset channel active status flag.
    [/cover] */
    /* Re-Set a bit 0 */
    Mcal_SetBitAtomic( \
                       GlbIndexStatusPtr, (sint32)ICU_CHNL_STATUS_POS, \
                       ICU_CHNL_STATUS_BIT_LENGTH, (uint32)ICU_17_TIMERIP_IDLE);
  }
  else
  {
    /* [cover parentID={E213C0F4-9C10-4e36-AFE8-60967143DE04}]
    Set input state IDLE
    [/cover] */
    RetVal = ICU_17_TIMERIP_IDLE;
  }
  return(RetVal);
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer GlbIndexStatusPtr is
   * accessed using assembly instruction. */
}
#endif

#if (ICU_17_TIMERIP_GPT12_USED  == STD_ON) && \
(ICU_17_TIMERIP_GET_INPUT_STATE_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {814D37E0-0253-476a-B343-72B15942B1DA}]     **
**                                                                            **
** Syntax : LOCAL_INLINE Icu_17_TimerIp_InputStateType                        **
**                  Icu_lGpt12GetInputState(                                  **
**                const uint16 GlobalChannelNumber,                           **
**                uint32* const GlbIndexStatusPtr,                            **
**                const uint8 Mode)                                           **
**                                                                            **
** Description :     Function to get the Input State for GPT12 channel        **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  CellUsed - GPT12 Channel information.                    **
**                   Mode - Mode of the ICU(normal/sleep)                     **
**                                                                            **
** Parameters (in-out): GlbIndexStatusPtr - Pointer to the channel flags      **
**                                                                            **
** Return value:     ICU_17_TIMERIP_ACTIVE - A new value is available         **
**                   ICU_17_TIMERIP_IDLE - No new value is available          **
*******************************************************************************/
LOCAL_INLINE Icu_17_TimerIp_InputStateType Icu_lGpt12GetInputState(
  const uint16 GlobalChannelNumber,
  uint32* const GlbIndexStatusPtr,
  const uint8 Mode)
{
  Icu_17_TimerIp_InputStateType RetVal;
  uint8 ChannelNo; /* Holds the GPT12 Tx Number  */
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
    MISRA rule. Union usage is required to access SFR data type and implement
    efficiently for accessing Timer registers */
  volatile Ifx_GPT12_T2* Gpt12TxRegPtr;
  Ifx_GPT12* Gpt12BasePtr;
  uint8 WakeupStatus;
  uint8 NotifStatus;
  uint8 MultiEdgeStatus;
  uint32 IcuTxRegValue;
  /* Extract Channel Number */
  ChannelNo = (uint8) GlobalChannelNumber & ICU_LOWER_NIBBLE;
  Gpt12BasePtr = &MODULE_GPT120;
  Gpt12TxRegPtr = &(Gpt12BasePtr->T2);
  Gpt12TxRegPtr = &(Gpt12TxRegPtr[ChannelNo]);

  /* Check if Notification is enabled in NORMAL mode or Wakeup is enabled in
   Sleep mode */
  WakeupStatus = (uint8) Mcal_GetBitAtomic(*GlbIndexStatusPtr, \
                 ICU_CHNL_WAKEUP_CAPABLE_POS, ICU_CHNL_WAKEUP_BIT_LENGTH);
  NotifStatus = (uint8) Mcal_GetBitAtomic(*GlbIndexStatusPtr, \
      ICU_CHNL_NOTIF_PRESENCE_POS, ICU_CHNL_NOTIF_BIT_LENGTH);
  MultiEdgeStatus = (uint8) Mcal_GetBitAtomic(*GlbIndexStatusPtr, \
      ICU_CHNL_MULTIEDGE_STAT_POS, ICU_CHNL_MULTIEDGE_STAT_BIT_LENGTH);
  /* [cover parentID={695D764E-7EA1-4c9c-BAD8-8E9571628B8C}]
   If Notification is enabled in NORMAL mode or Wakeup is enabled in Sleep mode
   or multi edge detection is enabled.
   [/cover] */
  if (((1U == NotifStatus) && (Mode == (uint8) ICU_17_TIMERIP_MODE_NORMAL)) \
      || ((1U == WakeupStatus) && (Mode == (uint8) ICU_17_TIMERIP_MODE_SLEEP)) \
      || (1U == MultiEdgeStatus))
  {
    /* [cover parentID={3D8818A2-3D9A-4cf5-8AB6-473A820EED70}]
     If channel status is active
     [/cover] */
    /* check bit 0 for active status filled from ISR */
    if (1U == Mcal_GetBitAtomic(*GlbIndexStatusPtr, ICU_CHNL_STATUS_POS, 1))
    {
      /* [cover parentID={D3AD313F-0B30-4aa0-8A6B-C516E8968C21}]
       set input state ACTIVE
       [/cover] */
      /* Return Active */
      RetVal = ICU_17_TIMERIP_ACTIVE;
      /* Re-Set a flag */
      /* [cover parentID={9E436232-0966-432f-8E4C-DCBD274E5C8E}]
       Set channel status to IDLE
       [/cover] */
      Mcal_SetBitAtomic(GlbIndexStatusPtr, (sint32)ICU_CHNL_STATUS_POS, \
          ICU_CHNL_STATUS_BIT_LENGTH, (uint32 )ICU_17_TIMERIP_IDLE);
    }
    else
    {
      /* [cover parentID={A6D225E4-CF8E-4cc4-BE8C-8BAD231E4DBC}]
       Set input state IDLE
       [/cover] */
      /* Return Idle */
      RetVal = ICU_17_TIMERIP_IDLE;
    }
  }
  /* [cover parentID={3DFA23D4-5820-4c70-8135-1687F408E750}]
   If ICU channel is active
   [/cover] */
  /* check bit 0 for active status filled from ISR due to Tx overflow */
  else if (1U == Mcal_GetBitAtomic(*GlbIndexStatusPtr, ICU_CHNL_STATUS_POS,
                                   ICU_CHNL_STATUS_BIT_LENGTH))
  {
    /* [cover parentID={739A0BF2-CC97-4d42-859D-3A136BDAAF1B}]
     Set input state active
     [/cover] */
    /* Return Active */
    RetVal = ICU_17_TIMERIP_ACTIVE;
    /* [cover parentID={DEF24A92-22B8-4512-A36F-5B6ACDCF3CCE}]
     Reset channel status flag and count register
     [/cover] */
    /* Re-Set a flag */
    Mcal_SetBitAtomic(GlbIndexStatusPtr, (sint32)ICU_CHNL_STATUS_POS, 1, \
                      (uint32 )ICU_17_TIMERIP_IDLE);
    Gpt12TxRegPtr->U = 0;
  }
  else
  {
    /* [cover parentID={C8B55588-27EE-4938-BD9A-98722DC633A3}]
     Reset timer count register
     [/cover] */
    /* Re-Set the Tx Register to 0 */
    /* MISRA2012_RULE_11_8_JUSTIFICATION: SFR access. Since the input
     * argument for the API discards volatile keyword. No side effects foreseen
     * by violating this MISRA rule*/
    /* MISRA2012_RULE_4_6_JUSTIFICATION: Basic numerical type - int/unsigned int
     * is used while invoking compiler intrinsic functions. These compiler
     * intrinsic functions are implemented specific to tricore. Hence to align
     * with compiler declaration use of unsigned int is mandatory*/
    IcuTxRegValue = Mcal_Swap(&(Gpt12TxRegPtr->U), 0U, ICU_SWAP_16BIT_MASK);
    /* [cover parentID={67BDC29F-1BD5-4a0a-A92F-8EACF07EA0E9}]
     If there is any valid edge detected
     [/cover] */
    if (IcuTxRegValue > 0U)
    {
      /* [cover parentID={4748D38F-424B-44c8-9AB8-7E68E83298EF}]
       Set input state ACTIVE
       [/cover] */
      /* Tx register is non zero indicating some edges, return Active*/
      RetVal = ICU_17_TIMERIP_ACTIVE;
    }
    else
    {
      /* [cover parentID={8CBC1F71-B740-4e0d-A4B0-55564B416DEC}]
       Set input state IDLE
       [/cover] */
      /* Return Idle */
      RetVal = ICU_17_TIMERIP_IDLE;
    }
  }
  return (RetVal);
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer GlbIndexStatusPtr is
   * accessed using assembly instruction. */

}
#endif

#if (ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON) && \
(ICU_17_TIMERIP_GET_INPUT_STATE_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {3EE8C884-1A97-401e-8B81-F20B36BE8904}]     **
**                                                                            **
** Syntax : LOCAL_INLINE Icu_17_TimerIp_InputStateType Icu_lEruGetInputState( **
**                      const uint16 HwUnit,                                  **
**                      uint32* const GlbIndexStatusPtr)                      **
**                                                                            **
** Description :     Function to get the Input State for ERU channel          **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  HwUnit - ERU Channel information.                        **
**                   GlbIndexStatusPtr - Pointer to the channel flags         **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     ICU_17_TIMERIP_ACTIVE - A new value is available         **
**                   ICU_17_TIMERIP_IDLE - No new value is available          **
*******************************************************************************/
LOCAL_INLINE Icu_17_TimerIp_InputStateType Icu_lEruGetInputState(
  const uint16 HwUnit,
  uint32* const GlbIndexStatusPtr)
{
  Icu_17_TimerIp_InputStateType RetVal;
  uint8 FlagStatus;
  uint8 EruLineUsed;
  EruLineUsed =  (uint8)((HwUnit ) & ICU_ERU_CHNL_MASK);
  RetVal = ICU_17_TIMERIP_IDLE;
  /* [cover parentID={02037F68-21A6-4d53-ACCF-4C61543CEDC9}]
  If channel status is active
  [/cover] */
  if(1U == Mcal_GetBitAtomic(*GlbIndexStatusPtr, ICU_CHNL_STATUS_POS, 1))
  {
    /* [cover parentID={BDD3444F-FCE5-423e-9A1A-D8600B5E7EA6}]
    Set input state ACTIVE
    [/cover] */
    RetVal = ICU_17_TIMERIP_ACTIVE;
    /* Re-Set a flag */
    /* [cover parentID={38C66398-BD12-4062-B86B-EE368058C3E7}]
    Set Input state IDLE
    [/cover] */
    Mcal_SetBitAtomic( \
      GlbIndexStatusPtr, (sint32)ICU_CHNL_STATUS_POS,\
      ICU_CHNL_STATUS_BIT_LENGTH, (uint32)ICU_17_TIMERIP_IDLE);
    /* Clear interrupt flag if any was set */
    MODULE_SCU.FMR.U = ((uint32)1UL) << (EruLineUsed + ICU_ERU_FCSTART);
  }
  /* [cover parentID={CFA1068C-D5B0-41de-B5A8-1C8C638B8BBB}]
  Are the notifications enabled?
  [/cover] */
  else if(1U != Mcal_GetBitAtomic(*GlbIndexStatusPtr,ICU_CHNL_NOTIF_PRESENCE_POS,
                                                     ICU_CHNL_NOTIF_BIT_LENGTH))
  {
    /* Read any flags before clearing to set ICU_17_TIMERIP_ACTIVE */
    FlagStatus = (uint8)Mcal_GetBitAtomic(MODULE_SCU.EIFR.U, EruLineUsed, 1U);
    /* [cover parentID={259556F6-06BC-4880-9EEB-D27B5F310CA4}]
    If any flags are set
    [/cover] */
    if(1U == FlagStatus)
    {
      /* [cover parentID={8CB4C5B6-A07C-4b49-8C0A-C3CB9E07674F}]
      Set input state ACTIVE
      [/cover] */
      RetVal = ICU_17_TIMERIP_ACTIVE;
      /* [cover parentID={F205139C-6AFE-4225-B004-1A7A2E44D425}]
      Clear the ERU flag for that channel.
      [/cover] */
      /* Clear Service Request if any was in pending */
      MODULE_SCU.FMR.U = ((uint32)1UL) << (EruLineUsed + ICU_ERU_FCSTART);
    }
  }
  else
  {
    /* [cover parentID={FAECC3DF-85B7-4e8c-9723-9770DAF0ADED}]
    Set channel status to idle
    [/cover] */
    RetVal = ICU_17_TIMERIP_IDLE;
  }
  return(RetVal);
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer GlbIndexStatusPtr is
   * accessed using assembly instruction. */
}
#endif

#if(ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {6C7C551C-A5BD-459c-B7FD-B662E4AA0749}]     **
**                                                                            **
** Syntax : LOCAL_INLINE void Icu_lGtmChangeActiveEdge(                       **
**                            const uint16 GlobalChannelNumber,               **
**                            const Icu_17_TimerIp_ActivationType ActiveEdge) **
**                                                                            **
** Description :     Function to change the Edge configured for a TIM Channel **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  GlobalChannelNumber - Channel Number                     **
**                   ActiveEdge - Edge to be detected                         **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lGtmChangeActiveEdge(
  const uint16 GlobalChannelNumber,
  const Icu_17_TimerIp_ActivationType ActiveEdge)
{
  Ifx_GTM_TIM_CH* TimChannelRegPtr;   /* Pointer to TIM Channel Reg    */
  uint32 TempRegVal;
  uint8 ModuleNo;                            /* Holds the TIM module Number   */
  uint8 ChannelNo;                           /* Holds the TIM Channel Number  */
  uint8 LactiveEdge;

  /* Calculate Module Id of the TIM channel */
  ModuleNo = (uint8)((GlobalChannelNumber / ICU_GTM_CHANNELS_PER_TIM_MODULE) \
                     & ICU_GTM_MODULE_NO_MSK);
  /* Calculate Channel number of the TIM channel */
  ChannelNo = (uint8)(GlobalChannelNumber % ICU_GTM_CHANNELS_PER_TIM_MODULE);

  if(ActiveEdge == ICU_17_TIMERIP_RISING_EDGE)
  {
    LactiveEdge = 1U;
  }
  else if(ActiveEdge == ICU_17_TIMERIP_FALLING_EDGE)
  {
    LactiveEdge = 0U;
  }
  else
  {
    LactiveEdge = (uint8)ICU_17_TIMERIP_BOTH_EDGES;
  }
  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TimChannelRegPtr = GTM_TIM_CH_POINTER(ModuleNo, ChannelNo);
  /* Clear all Pending Interrupts */
  TimChannelRegPtr->IRQ.NOTIFY.U = ICU_GTM_CLEAR_INTERRUPTS;
  /* Clear the previous Edge Value */
  TempRegVal = TimChannelRegPtr->CTRL.U;
  TempRegVal &= (uint32)~(ICU_TIM_CTRL_DSL_MASK << ICU_TIM_CTRL_DSL_POS);
  TempRegVal |= (uint32)(((uint32)LactiveEdge) << ICU_TIM_CTRL_DSL_POS) ;
  TimChannelRegPtr->CTRL.U = TempRegVal;
}
#endif

#if(ICU_17_TIMERIP_CCU6_USED == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {2B83C33F-69E0-45a8-AB4E-42DA8A198AEC}]     **
**                                                                            **
** Syntax : LOCAL_INLINE void Icu_lCcu6SetActivationCondition(                **
**                  const uint16 CellUsed,                                    **
**                  const uint8 ActiveEdge)                                   **
**                                                                            **
** Description : Function to set the IEN register according to the configured **
**               edge only if IEN was set previously                          **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  CellUsed - CCU6 Kernel and channel information           **
**                   ActiveEdge - Configured Activation edge for the channel  **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lCcu6SetActivationCondition(
  const uint16 CellUsed,
  const uint8 ActiveEdge)
{
  volatile Ifx_CCU6 *Ccu6RegPtr; /* Variable to hold the current CCU6 address */
  uint8 CcuActiveEdge;      /* To hold the CCU equivalent edge */
  uint8 CcChannelNumber;    /* To hold the CC channel number */
  uint8 BitPos;
  /* Upper Nibble of AssignedHwUnitNumber holds the Channel Number */
  CcChannelNumber = (uint8)
                  ((CellUsed & ICU_CCU_GET_COMPARATOR) >> ICU_BRING_TO_BIT_0);

  /* Get the base address of the Kernal */
  Ccu6RegPtr = &(&MODULE_CCU60)[CellUsed & ICU_CCU_GET_KERNEL];
  /* [cover parentID={42533D90-9166-4d44-AA88-26D1C7D4ED63}]
  Clear the pending interrupt
  [/cover] */
  /* Clear any pending interrupt */
  Ccu6RegPtr->ISR.U = (uint32)(ICU_CCU_CLEAR_INTERRUPT <<
      (CcChannelNumber * (uint8)ICU_CCU_IS_BITS_PER_CHANNEL));
  /* Check if the interrupts are enabled. Modify only if the interrupts are
    enabled as interrupts are needed only if notifications are needed */
  BitPos = CcChannelNumber * (uint8)ICU_CCU_IS_BITS_PER_CHANNEL;
  Ccu6RegPtr->CMPMODIF.U = ((uint32)1U <<
                   ((uint8)ICU_CCU6_CMPMODIF_CLEAR_OFFSET + CcChannelNumber));
  /* [cover parentID={3C18EA59-4F0B-4a2c-A3FA-7F3CCF0C6152}]
  Critical section
  [/cover] */
  SchM_Enter_Icu_17_TimerIp_SetActivationCondition();
  /* [cover parentID={2B10F6E4-0105-4921-B5D7-1EDB7DD0FF87}]
  Is the CCU6 ISR enabled?
  [/cover] */
  if(0U != \
      Mcal_GetBitAtomic(Ccu6RegPtr->IEN.U, BitPos, \
                        ICU_CCU_IS_BITS_PER_CHANNEL))
  {
    /* [cover parentID={E1071562-E171-4b4d-B648-1D6570D5970F}]
    Get Active Edge for CCU6
    [/cover] */
    CcuActiveEdge = Icu_lCcu6GetActiveEdge(ActiveEdge);
    /* Enable interrupt for the channel as per the new edge */
    /* [cover parentID={0239FABE-CE27-4e37-A32B-97D0957C7D44}]
    Enable interrupt for the channel as per the new edge
    [/cover] */
    Mcal_SetBitAtomic((&Ccu6RegPtr->IEN.U), \
                      (CcChannelNumber * (uint8)ICU_CCU_IS_BITS_PER_CHANNEL), \
                      ICU_CCU_IS_BITS_PER_CHANNEL, \
                      (uint32)CcuActiveEdge);
  }
  else
  {
    /* Nothing to do */
  }
  SchM_Exit_Icu_17_TimerIp_SetActivationCondition();
  /* MISRA2012_RULE_2_2_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the variable CcuActiveEdge is
   * accessed using assembly instruction. */
}
#endif

#if(ICU_17_TIMERIP_GPT12_USED == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {91B20187-6A8A-4d6c-BB38-1A2A052319BC}]     **
**                                                                            **
** Syntax :   LOCAL_INLINE void Icu_lGpt12SetActivationCondition(             **
**                            const uint16 CellUsed,                          **
**                            const Icu_17_TimerIp_ActivationType ActiveEdge, **
**                            const uint8 TxClearFlag)                        **
**                                                                            **
** Description :     Function to update the GPT12 timer active edge           **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters(in)   :CellUsed - GPT12 timer information. Lower Nibble is Timer**
**                              Used (T2/T3/T4/T5/T6).                        **
**                   ActiveEdge - Configured Activation edge for the channel  **
**                   TxClearFlag - Flag to indicate clearing of timer counter **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lGpt12SetActivationCondition(
  const uint16 CellUsed,
  const Icu_17_TimerIp_ActivationType ActiveEdge,
  const uint8 TxClearFlag)
{
  uint8 ChannelNo;                              /* Holds the GPT12 Tx Number  */
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
    MISRA rule. Union usage is required to access SFR data type and implement
    efficiently for accessing Timer control registers */
  volatile Ifx_GPT12_T2CON* Gpt12TxConRegPtr;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
    MISRA rule. Union usage is required to access SFR data type and implement
    efficiently for accessing Timer control registers */
  volatile Ifx_GPT12_T2* Gpt12TxRegPtr;
  uint32 LActiveEdge;
  Ifx_GPT12* Gpt12BasePtr;

  /* Extract Channel Number */
  ChannelNo = (uint8)CellUsed & ICU_LOWER_NIBBLE;

  /* [cover parentID={05C9BB1A-5247-4164-B949-3382898211E9}]
  Calculate Active edge based on Config edge for  GPT12 HW
  [/cover] */
  LActiveEdge = (uint32)ActiveEdge + 1U;

  Gpt12BasePtr = &MODULE_GPT120;
  Gpt12TxRegPtr = &(Gpt12BasePtr->T2);
  Gpt12TxConRegPtr = &(Gpt12BasePtr->T2CON);

  Gpt12TxConRegPtr = &(Gpt12TxConRegPtr[ChannelNo]);
  Gpt12TxRegPtr = &(Gpt12TxRegPtr[ChannelNo]);
  /* [cover parentID={4C6F6A6E-77D0-4866-8FA3-B44B684A3EA0}]
  Is the timer clear requested?
  [/cover] */
  if(ICU_FLAG_SET == TxClearFlag)
  {
    /* Clear the previous Edge counter Value */
    Gpt12TxRegPtr->U = 0;
  }
  /* Set TxCon according the edge */
  /* [cover parentID={B271A65B-B63A-4f58-9E61-52E9F336E712}]
  Set TxCON Register based on Confirured edge.
  [/cover] */
  Mcal_SetBitAtomic( Gpt12TxConRegPtr, (sint32)ICU_GPT12_TxI_POS, \
                     ICU_GPT12_TxI_LEN, (uint32)LActiveEdge);
  /* MISRA2012_RULE_2_2_JUSTIFICATION: No side effects foreseen
       * by violating this MISRA rule, as the variable LActiveEdge is
       * accessed using assembly instruction. */
  /* MISRA2012_RULE_2_2_JUSTIFICATION: No side effects foreseen
       * by violating this MISRA rule, as the variable Gpt12TxConRegPtr is
       * accessed using assembly instruction. */
}
#endif

#if (ICU_17_TIMERIP_CCU6_USED == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {EE07F50B-B758-4a47-8239-4E6619FF7D49}]     **
**                                                                            **
** Syntax :   LOCAL_INLINE uint8 Icu_lCcu6GetActiveEdge(                      **
**                            const uint8 ActiveEdge)                         **
**                                                                            **
** Description :     Function to get the Active Edge equivalent for CCU6x     **
**                   hardware                                                 **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant                                                **
**                                                                            **
** Parameters (in):  ActiveEdge - Configured Activation edge for the channel  **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     RetVal - Activation Edge corresponding to CCU6x Hardware **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Icu_lCcu6GetActiveEdge(
  const uint8 ActiveEdge)
{
  uint8 RetVal;  /* Equivalent edge value in CCU6 convention */

  switch(ActiveEdge)
  {
    /* Convert the Activation edge in the form suited for CCU */
    case (uint8)ICU_17_TIMERIP_RISING_EDGE:
      RetVal = ICU_CCU_RISING_EDGE;
      break;
    case (uint8)ICU_17_TIMERIP_FALLING_EDGE:
      RetVal = ICU_CCU_FALLING_EDGE;
      break;
    default: /*Default case Edge Type ICU_17_TIMERIP_BOTH_EDGES */
      RetVal = ICU_CCU_BOTH_EDGES;
      break;
  }
  return (RetVal);

}
#endif

#if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
(ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={D1CBD6B9-86E1-40b4-B74D-D24F0FD4B8A2}]      **
**                                                                            **
** Syntax :      LOCAL_INLINE uint32 Icu_lSetActivationConditionDETCheck(     **
**                  const uint8 CoreId,                                       **
**                              const Icu_17_TimerIp_ChannelType Channel)     **
**                                                                            **
** Description :      Local function :Service for DET check in                **
**                          Icu_17_TimerIp_SetActivationCondition() function  **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        None                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Reentrant                                               **
**                                                                            **
** Parameters (in):   CoreId  - Core which is calling this function           **
**                    Channel - Channel number to verify                      **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value:      uint32: status of DET.                                  **
**                            ICU_ERROR_NOT_FOUND/ICU_ERROR_FOUND             **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Icu_lSetActivationConditionDETCheck(const uint8 CoreId,
    const Icu_17_TimerIp_ChannelType Channel)
{
  uint32 ErrorFlag;
  /* [cover parentID={CAB81A75-9BAB-40f8-921E-19348054607D}]
   Check whether Init has been earlier called or not
  [/cover] */
  ErrorFlag = Icu_lInitCallVerify(ICU_17_TIMERIP_SID_SETACTIVATIONCONDITION,
                                  CoreId);
  /* Check if there are any previous errors */
  /* [cover parentID={D519EA9F-BD85-4657-BD1B-7F5EBCE3226B}]
  Any DET found
  [/cover] */
  if (ErrorFlag != ICU_ERROR_FOUND)
  {
    /* [cover parentID={B1D180A7-F07F-4cf8-B508-3424EAC1298C}]
    Check for channel validity.
    [/cover] */
    ErrorFlag = Icu_lChannelVerify(ICU_17_TIMERIP_SID_SETACTIVATIONCONDITION,
                                   Channel, CoreId);
    /* Check if there are any previous errors */
  }
  /* [cover parentID={8713E043-BF3D-454c-8F21-16477B751F73}]
  Safety is enabled
  [/cover] */
  #if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  /* Check if there are any previous errors */
  /* [cover parentID={63FC5F7D-F739-4f4d-B49C-76ACF3C8105D}]
  Any DET found
  [/cover] */
  if (ErrorFlag != ICU_ERROR_FOUND)
  {
    /* [cover parentID={344724A7-DD56-4bc2-A09A-35BBC004F3D5}]
    Is ICU in SLEEP mode?
    [/cover] */
    if(ICU_17_TIMERIP_MODE_SLEEP == Icu_17_TimerIp_Varlist[CoreId]->GlobalMode)
    {
      /* [cover parentID={92335747-16D0-4bd0-8680-4B908C5F040A}]
      Report Safety Error to invalid mode
      [/cover] */
      Mcal_ReportSafetyError(
        ICU_17_TIMERIP_MODULE_ID,
        ICU_17_TIMERIP_INSTANCE_ID,
        ICU_17_TIMERIP_SID_SETACTIVATIONCONDITION,
        ICU_17_TIMERIP_E_INVALID_MODE);/* End of report to Safety */
      ErrorFlag = (uint32) ICU_ERROR_FOUND;
    }
  }
  #endif
  return ErrorFlag;
}
#endif
#if (ICU_17_TIMERIP_SET_MODE_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={182A153A-6138-4980-B918-F44EA78EC6FC}]      **
**                                                                            **
** Syntax :      LOCAL_INLINE uint32 Icu_lSetModeBusyCheck(                   **
**                  const uint8 CoreId )                                      **
**                                                                            **
** Description :      Local function :check if any channel is active before   **
**                    entering SLEEP mode.                                    **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        None                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Non Reentrant                                           **
**                                                                            **
** Parameters (in):   CoreId  - Core which is calling this function           **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value:      uint32: status of DET.                                  **
**                            ICU_ERROR_NOT_FOUND/ICU_ERROR_FOUND             **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Icu_lSetModeBusyCheck(const uint8 CoreId)
{
  /* Verify any error is there for DET */
  uint32 ErrorFlag = ICU_ERROR_NOT_FOUND;
  const uint32* GlbIndexStatusPtr;
  Icu_17_TimerIp_ChannelType Channel;

  /* Read Channel Status Flags pointer */
  GlbIndexStatusPtr =
    (Icu_17_TimerIp_Varlist[CoreId]->GlbIndexStatusBasePtr);

  /* Loop all channels to check for any active channels until an
   * error is found */
  /* [cover parentID={5456E01E-F438-474f-97F7-AAB0921CBD73}]
  Loop all channels to check if there are any active channels.
  [/cover] */
  for (Channel = (Icu_17_TimerIp_ChannelType) 0;
       (Channel
        < (Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->MaxChannelCore))
       && (ErrorFlag != ICU_ERROR_FOUND); Channel = Channel + 1U)
  {
    /* [cover parentID={50EABC58-7541-4a5b-AB36-71880D0AD6D5}]
    Is channel active?
    [/cover] */
    if (ICU_ACTIVITY_STARTED
        == Mcal_GetBitAtomic(GlbIndexStatusPtr[Channel],
            ICU_CHNL_ACTIVITY_STARTED_POS, ICU_CHNL_ACTIVITY_BIT_LENGTH))
    {
      /* Set a error flag to end the loop */
      ErrorFlag = ICU_ERROR_FOUND;
      /* [cover parentID={0A1DE2C0-FC3E-47c2-B6D9-9E76E5C95A5A}]
      DET or Safety is enabled.
      [/cover] */
      /* STATIC CHECK: if DET or Safety error reporting is enabled */
      #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
      (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
      /* [cover parentID={457FDC14-C57F-4a76-B599-C8EB50ED04F9}]
      Raise an error to indicate one of the channel is busy.
      [/cover] */
      /* Raise an error */
      Icu_lReportError(
        ICU_17_TIMERIP_SID_SETMODE,
        ICU_17_TIMERIP_E_BUSY_OPERATION);
      #endif
    }
  }
  return (ErrorFlag);
}
#endif
/*#if (ICU_17_TIMERIP_SET_MODE_API == STD_ON) */
#if (ICU_17_TIMERIP_SET_MODE_API == STD_ON) && \
(ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={D0D5CB31-D676-48fd-9040-E5F1752272B5}]      **
**                                                                            **
** Syntax : LOCAL_INLINE void Icu_lChannelToSleep (                           **
**            const Icu_17_TimerIp_ChannelConfigType *IcuChanPtr              **
**            uint32 *const GblIndexStatusPtr                                 **
**            const uint8 CoreId)                                             **
**                                                                            **
** Description :      Local function to put a channel to sleep.               **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        None                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Non Reentrant                                           **
**                                                                            **
** Parameters (in):   IcuChanPtr - Pointer to the Channel configuration       **
**                    CoreId  - Core which is calling this function           **
**                    GlbIndexStatusPtr - Pointer to the channel flags        **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value:      None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lChannelToSleep(
  const Icu_17_TimerIp_ChannelConfigType *const IcuChanPtr,
  uint32* const GlbIndexStatusPtr,
  const uint8 CoreId)
{
  uint16 HwUnit;
  uint32 IcuHwOption;
  #if(ICU_17_TIMERIP_GPT12_USED == STD_ON)
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * MISRA rule,To implement efficiently IcuMeasaurementProperty as a post-build
   * parameter.Union is required*/
  Icu_17_TimerIp_ChannelData* MultiEdgeCountPtr;
  uint8 ChIndex;
  #else
  UNUSED_PARAMETER(CoreId);
  #endif
  Mcal_SetBitAtomic(GlbIndexStatusPtr, ICU_TIMEOUT_STATUS_POS,
      ICU_TIMEOUT_STATUS_LENGTH, (uint32 )(0U));
  /* Depending on ICU option take action */
  IcuHwOption =
    (uint32) IcuChanPtr->IcuProperties.AssignedHwUnit;
  /* check if the channel is wakeup capable */
  /* [cover parentID={DBFA9716-E6B5-4d8d-A449-8690C70A7881}]
  Is the channel wakeup capable?
  [/cover] */
  if (1U
      == Mcal_GetBitAtomic(*GlbIndexStatusPtr,
          ICU_CHNL_WAKEUP_CAPABLE_POS, ICU_CHNL_WAKEUP_BIT_LENGTH))
  {
    /* Enable the Interrupts if notification is disabled because
     if notification was enabled, interrupts are already enabled.*/
    /* [cover parentID={1B8276F0-BB3F-4b95-9353-5F3385F41AC5}]
    Is the channels notifications enabled? If the channels notifications were
    enabled, there is no need to re-enable them.
    [/cover] */
    if (1U
        == Mcal_GetBitAtomic(*GlbIndexStatusPtr,
            ICU_CHNL_NOTIF_PRESENCE_POS, ICU_CHNL_NOTIF_BIT_LENGTH))
    {
      /* Nothing to do */
    }
    else
    {
      /* Enable the interrupt */
      /* Initialize ICU configured channel ROM pointer */
      HwUnit =
        (uint16) (IcuChanPtr->IcuProperties.AssignedHwUnitNumber);
      #if(ICU_17_TIMERIP_GPT12_USED == STD_ON)
      /* for triggering notifications, interrupt is required on
       * all edges */
      /* [cover parentID={055F7A4D-9674-469b-AC2E-9300B30FD8E8}]
      Is HW used if GPT12?
      [/cover] */
      if (IcuHwOption == ICU_17_TIMERIP_GPT12_OPTION)
      {
        /* Retrieve Mode specific channel index */
        ChIndex = IcuChanPtr->ModeMappingIndex;
        /* Retrieve the multi edge Count value address */
        MultiEdgeCountPtr =
               &((Icu_17_TimerIp_Varlist[CoreId]->ChannelDataBasePtr)[ChIndex]);
        /* Update the reload counter only if multiedge detection
         * is disabled*/
        /* [cover parentID={4F99B1D0-8B3A-4a7f-AD31-632FDC4CFDC8}]
        Extract the multi edge detection status
        [/cover] */
        /* [cover parentID={AE7EF25C-6AC1-4e36-B825-F779B0515C23}]
        Is multi edge detection enabled?
        [/cover] */
        if (0U
            == Mcal_GetBitAtomic(*GlbIndexStatusPtr,
               ICU_CHNL_MULTIEDGE_STAT_POS, ICU_CHNL_MULTIEDGE_STAT_BIT_LENGTH))
        {
          /* [cover parentID={49E5CE82-F7E2-40f0-A5A9-9AD4960F7979}]
          Set multi edge counter to 1 to enable interrupt on every edge.
          [/cover] */
          (MultiEdgeCountPtr->EdgeDetectParas.EdgeDetectCount) = \
              1;
        }
      }
      #endif
      /* [cover parentID={9677AD8D-E94D-4eb1-8609-D3EEBFC8E19A}]
      Enable notification interrupts for wakeup channels.
      [/cover] */
      Icu_lEnableNotificationInterrupts(IcuHwOption, HwUnit,
                                        GlbIndexStatusPtr);
    }
  }
  /* Wakeup is disabled. Check if Notification is enabled */
  /* [cover parentID={BB01908A-3D6A-4495-8DA0-CB62D0F69A59}]
  Is the channels notifications enabled? Wakeup capable channels are taken
  care of but if the channel is not wakeup capable and notifications are
  enabled, notification interrupts should be disabled in SLEEP mode.
  [/cover] */
  else if (1U
      == Mcal_GetBitAtomic(*GlbIndexStatusPtr,
          ICU_CHNL_NOTIF_PRESENCE_POS, ICU_CHNL_NOTIF_BIT_LENGTH))
  {
    /* Disable the Interrupts */
    /* Initialize ICU configured channel ROM pointer */
    HwUnit = (uint16) \
             (IcuChanPtr->IcuProperties.AssignedHwUnitNumber);
    #if(ICU_17_TIMERIP_GPT12_USED == STD_ON)
    /* [cover parentID={A1963AE6-11AF-4174-B157-97BE6F15DCB2}]
    Is HW used GPT12?
    [/cover] */
    if (IcuHwOption == ICU_17_TIMERIP_GPT12_OPTION)
    {
      /* Mark activity as started and disable channel */
      Mcal_SetBitAtomic(GlbIndexStatusPtr, \
          (sint32)ICU_CHNL_ACTIVITY_STARTED_POS, ICU_CHNL_ACTIVITY_BIT_LENGTH, \
          (uint32)ICU_ACTIVITY_STARTED);
      /* [cover parentID={4E05ADF5-A94C-40b3-A042-747B41293AD3}]
      Disable GPT12 channel.
      [/cover] */
      Icu_lGpt12DisableChannel(HwUnit);
    }
    else
    #endif
    {
      /* [cover parentID={39765AAE-11E4-43de-83E1-52A8E62C5505}]
      Disable the notification interrupts as they are not required in SLEEP
      mode.
      [/cover] */
      Icu_lDisableNotificationInterrupts(IcuHwOption, HwUnit);
    }
  }
  #if(ICU_17_TIMERIP_GPT12_USED == STD_ON)
  /* [cover parentID={C1AF22B8-3BED-485c-94DC-814A95C7A025}]
  Is the GPT channel edge detection enabled?
  [/cover] */
  else if ((1U
            == Mcal_GetBitAtomic(*GlbIndexStatusPtr,
                                 ICU_CHNL_ERU_GPT_SIGEDGE_STATUS_POS,
                                 ICU_CHNL_ERU_GPT_SIGEDGE_STATUS_BIT_LENGTH))
           && (IcuHwOption == ICU_17_TIMERIP_GPT12_OPTION))
  {
    /* Initialize ICU configured channel ROM pointer */
    HwUnit = (uint16) \
             (IcuChanPtr->IcuProperties.AssignedHwUnitNumber);
    /* Mark activity as started and disable channel */
    Mcal_SetBitAtomic( GlbIndexStatusPtr, (sint32)ICU_CHNL_ACTIVITY_STARTED_POS,
                       ICU_CHNL_ACTIVITY_BIT_LENGTH,
                       (uint32)ICU_ACTIVITY_STARTED);
    /* [cover parentID={D73F02E0-9D63-4dd5-BEBE-3003EA93E299}]
    Disable GPT12 channel.
    [/cover] */
    Icu_lGpt12DisableChannel(HwUnit);
  }
  #endif
  else
  {
    /* Nothing to do */
  }
}
#endif
/*#if (ICU_17_TIMERIP_SET_MODE_API == STD_ON) &&
(ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)*/
#if (ICU_17_TIMERIP_SET_MODE_API == STD_ON) && \
(ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={D091169C-F57C-4fa8-81D2-AC23FC6ACD85}]      **
**                                                                            **
** Syntax : LOCAL_INLINE void Icu_lChannelToNormal (                          **
**            const Icu_17_TimerIp_ChannelConfigType *IcuChanPtr              **
**            uint32 *const GblIndexStatusPtr                                 **
**            const uint8 CoreId)                                             **
**                                                                            **
** Description :      Local function to put a channel to normal.              **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        None                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Non Reentrant                                           **
**                                                                            **
** Parameters (in):   IcuChanPtr - Pointer to the Channel configuration       **
**                    CoreId  - Core which is calling this function           **
**                    GlbIndexStatusPtr - Pointer to the channel flags        **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value:      None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lChannelToNormal(
  const Icu_17_TimerIp_ChannelConfigType *const IcuChanPtr,
  uint32* const GlbIndexStatusPtr,
  const uint8 CoreId)
{
  uint16 HwUnit;
  uint32 IcuHwOption;
  #if(ICU_17_TIMERIP_GPT12_USED == STD_ON)
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * MISRA rule,To implement efficiently IcuMeasaurementProperty as a post-build
   * parameter.Union is required*/
  const Icu_17_TimerIp_ChannelData* MultiEdgeCountPtr;
  uint8 ChIndex;
  uint8 ActiveStatus;
  #else
  UNUSED_PARAMETER(CoreId);
  #endif
  Mcal_SetBitAtomic(GlbIndexStatusPtr, ICU_TIMEOUT_STATUS_POS,
      ICU_TIMEOUT_STATUS_LENGTH,
      (uint32 )(IcuChanPtr->IcuProperties.TimeOutEnabled));
  /* check if the channel's notification is enabled */
  /* [cover parentID={D9F4693C-58C0-4583-A7AE-7E295B99A18D}]
  Is the channel's notification enabled and wakeup is disabled?
  All the notification interrupts disabled
  while entering sleep mode should be re-enabled.
  [/cover] */
  if (1U
      == Mcal_GetBitAtomic(*GlbIndexStatusPtr,
          ICU_CHNL_NOTIF_PRESENCE_POS, ICU_CHNL_NOTIF_BIT_LENGTH))
  {
    if (1U
        != Mcal_GetBitAtomic(*GlbIndexStatusPtr,
             ICU_CHNL_WAKEUP_CAPABLE_POS, ICU_CHNL_WAKEUP_BIT_LENGTH))
    {
      /* Enable the interrupt */
      /* Initialize ICU configured channel ROM pointer */
      HwUnit =
        (uint8) (IcuChanPtr->IcuProperties.AssignedHwUnitNumber);
      /* Depending on ICU option take action */
      IcuHwOption =
        (uint32) IcuChanPtr->IcuProperties.AssignedHwUnit;
      /* [cover parentID={9B8AC25E-B728-4f0f-BE8B-D926BF71E3CB}]
      Enable the notification interrupts.
      [/cover] */
      Icu_lEnableNotificationInterrupts(IcuHwOption, HwUnit,
                                        GlbIndexStatusPtr);
      #if(ICU_17_TIMERIP_GPT12_USED == STD_ON)
      /* Check if the GPT12 channel is enabled before entering
       * sleep mode.*/
      ActiveStatus = (uint8) Mcal_GetBitAtomic(*GlbIndexStatusPtr,
                   ICU_CHNL_ACTIVITY_STARTED_POS, ICU_CHNL_ACTIVITY_BIT_LENGTH);
      /* [cover parentID={F81DDC93-B6A0-4dbd-ADC1-2B8551BE2538}]
      Is HW used is GPT12 and the activity started flag set?
      [/cover] */
      if ((IcuHwOption == ICU_17_TIMERIP_GPT12_OPTION) && \
          ((uint8)ICU_17_TIMERIP_ACTIVE == ActiveStatus))
      {
        /* reset activity started and enable the gpt12 channel */
        /* [cover parentID={F9333155-16C3-4eb1-A271-7F441FC4C947}]
        Reset activity started flag and extract the multi edge
        count variable pointer.
        [/cover] */
        Mcal_SetBitAtomic(GlbIndexStatusPtr,
                          (sint32)ICU_CHNL_ACTIVITY_STARTED_POS,
                          ICU_CHNL_ACTIVITY_BIT_LENGTH,
                          (uint32 )0);
        /* Retrieve Mode specific channel index */
        ChIndex = IcuChanPtr->ModeMappingIndex;
        /* Retrieve the multi edge Count value address */
        MultiEdgeCountPtr =
               &((Icu_17_TimerIp_Varlist[CoreId]->ChannelDataBasePtr)[ChIndex]);
        /* Call GPT12 Start Edge Detect*/
        /* [cover parentID={23B1DD71-1488-4c23-B657-6B109CA57726}]
        Start GPT12 timer for edge detection.
        [/cover] */
        Icu_lGpt12StartEdgeDetect(HwUnit,
            (uint16)(MultiEdgeCountPtr->EdgeDetectParas.EdgeDetectCount));
      }
      #endif
    }
  }
  /* Notification is disabled. Check if  wakeup is enabled */
  /* [cover parentID={72105604-CE63-4ee7-87D0-D631C67F78AE}]
  Is the channels wakeup capability enabled? If the channels notifications are
  disabled and the channel is wakeup capable, the interrupts are not required
  in NORMAL mode.
  [/cover] */
  else if (1U
      == Mcal_GetBitAtomic(*GlbIndexStatusPtr,
          ICU_CHNL_WAKEUP_CAPABLE_POS, ICU_CHNL_WAKEUP_BIT_LENGTH))
  {
    /* Disable the Interrupts */
    /* Initialize ICU configured channel ROM pointer */
    HwUnit =
      (uint16) (IcuChanPtr->IcuProperties.AssignedHwUnitNumber);
    /* Depending on ICU option take action */
    IcuHwOption =
      (uint32) IcuChanPtr->IcuProperties.AssignedHwUnit;
    #if(ICU_17_TIMERIP_GPT12_USED == STD_ON)
    /* If GPT multi edge detection is enabled, do not disable the
     * interrupts. For all the remaining cases, notifications
     * need to be disabled.*/
    /* [cover parentID={B209FC33-5086-414e-9503-7180F5B62A38}]
    Is the GPT multi edge detection enabled?
    [/cover] */
    if (1U
        != Mcal_GetBitAtomic(*GlbIndexStatusPtr,
            ICU_CHNL_MULTIEDGE_STAT_POS, ICU_CHNL_MULTIEDGE_STAT_BIT_LENGTH))
    #endif
    {
      /* [cover parentID={10885FAB-1C3F-4a4f-A070-77170DE48160}]
      Disable the notification interrupts
      [/cover] */
      Icu_lDisableNotificationInterrupts(IcuHwOption, HwUnit);
    }
  }
  #if (ICU_17_TIMERIP_GPT12_USED == STD_ON) && \
  (ICU_17_TIMERIP_EDGE_DETECT_API ==STD_ON)
  /* [cover parentID={6893E108-4CB3-4d30-82AE-60E3BE3144A4}]
  Is the activity started flag set?
  [/cover] */
  else if (1U
      == Mcal_GetBitAtomic(*GlbIndexStatusPtr,
          ICU_CHNL_ACTIVITY_STARTED_POS, ICU_CHNL_ACTIVITY_BIT_LENGTH))
  {
    /* Initialize ICU configured channel ROM pointer */
    HwUnit =
      (uint16) (IcuChanPtr->IcuProperties.AssignedHwUnitNumber);
    /* Check if the GPT12 channel is enabled before entering
     * sleep mode.*/
    /* reset activity started and enable the gpt12 channel */
    Mcal_SetBitAtomic(GlbIndexStatusPtr, \
                      (sint32)ICU_CHNL_ACTIVITY_STARTED_POS, 1, \
                      (uint32 )0);
    /* Retrieve Mode specific channel index */
    ChIndex = IcuChanPtr->ModeMappingIndex;
    /* Retrieve the multi edge Count value address */
    MultiEdgeCountPtr =
        &((Icu_17_TimerIp_Varlist[CoreId]->ChannelDataBasePtr)[ChIndex]);
    /* Call GPT12 Start Edge Detect*/
    /* [cover parentID={F1E2A7BF-0A61-4c63-A095-FB59B9323CE3}]
    Start GPT12 timer for edge detection.
    [/cover] */
    Icu_lGpt12StartEdgeDetect(HwUnit, \
        (uint16)MultiEdgeCountPtr->EdgeDetectParas.EdgeDetectCount);
  }
  #endif
  else
  {
    /* Nothing to do */
  }
}
#endif
/*#if (ICU_17_TIMERIP_SET_MODE_API == STD_ON) &&
   (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)*/

#if (ICU_17_TIMERIP_CCU6_USED == STD_ON) && \
(ICU_17_TIMERIP_SIGNAL_MEASUREMENT_API ==STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {0ABB6DFF-9423-47a4-95A2-0718F996A8B8}]     **
**                                                                            **
** Syntax : static Icu_17_TimerIp_ValueType Icu_lCcuSubtractWithOverflow(     **
**                               const uint16 SecondVal,                      **
**                               const uint16 FirstVal)                       **
**                                                                            **
** Description :     Function to perform subtraction of the form              **
**                   SecondVal - FirstVal considering the T12 Timer overflow  **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant                                                **
**                                                                            **
** Parameters (in):  SecondVal - Second value in Subtraction                  **
**                   FirstVal - First value in Subtraction                    **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     uint16 - Subtracted value                                **
**                                                                            **
*******************************************************************************/
static uint16 Icu_lCcuSubtractWithOverflow(
  const uint16 SecondVal,
  const uint16 FirstVal)
{
  uint16 RetVal;

  /* Check if the overflow has happened */
  if(FirstVal < SecondVal)
  {
    /* If both the values are within the same cycle of T12 before overflow,
       perform a direct subtraction */
    RetVal = SecondVal - FirstVal;
  }
  else
  {
    /* If both the values are in consecutive cycles of T12 after overflow,
       overflow is considered during subtraction */
    RetVal = (uint16)((uint16)((uint16)ICU_CCU6_MAX_T12_TIMER_VAL - \
                               (FirstVal - SecondVal)) + (uint16)1UL);
  }
  return(RetVal);
}
#endif

#if (ICU_17_TIMERIP_DE_INIT_API == STD_ON)
#if ((ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON) || \
(ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={2E57C3AB-F853-41a2-9E48-748C407EFAFA}]      **
**                                                                            **
** Syntax : LOCAL_INLINE uint32 Icu_lDeInitDetCheck(                          **
**                  const uint8 CoreId)                                       **
**                                                                            **
** Description :      Local function :Service for DET check in                **
**                        Icu_17_TimerIp_DeInit() function                    **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        None                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Reentrant                                               **
**                                                                            **
** Parameters (in):   CoreId  - Core which is calling this function           **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value:      uint32: status of Error                                 **
**                            ICU_ERROR_NOT_FOUND/ICU_ERROR_FOUND             **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Icu_lDeInitDetCheck(
  const uint8 CoreId)
{
  uint32 ErrorFlag = ICU_ERROR_NOT_FOUND;
  /* [cover parentID={43E742E9-780C-44b2-9536-0350A8CA2586}]
  If Muticore error detection of safety is enabled and atleast one channel
  allocated to slave core.
  [/cover] */
  #if ((ICU_17_TIMERIP_MULTICORE_ERROR_DETECT == STD_ON) || \
    (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON))
  #if !((ICU_17_TIMERIP_SINGLE_CORE == STD_ON) && \
    (ICU_17_TIMERIP_SINGLE_CORE_ID == MCAL_MASTER_COREID))
  /* [cover parentID={B815757E-5A45-487a-A653-2BA15A48A15B}]
  Is master core?
  [/cover] */
  if (MCAL_MASTER_COREID == CoreId)
  {
    /* [cover parentID={CB1A70AB-CE89-4cc6-897A-71CED2FE4F25}]
    Are there any other core still initialized?
    [/cover] */
    if (0U != (Icu_17_TimerIp_InitStatus & \
               (uint32)(~((uint32)ICU_INIT_STAUS_MASK << (MCAL_MASTER_COREID * \
                          ((uint8)ICU_INIT_STAUS_SIZE))))))
    {
      ErrorFlag = ICU_ERROR_FOUND;
      /* [cover parentID={2CAE2230-A923-4026-8223-8DCA99211113}]
      Report an error to indicate that master de-initialization is initiated
      before all the slave cores are de-initialized.
      [/cover] */
      Icu_lReportMulticoreError(
        ICU_17_TIMERIP_SID_DEINIT,
        ICU_17_TIMERIP_E_SLAVE_CORE_INIT); /* Report Error */
    }
    else
    {
      ErrorFlag = ICU_ERROR_NOT_FOUND;
    }
  }
  if(ICU_ERROR_NOT_FOUND == ErrorFlag)
  #endif
  #endif
  {
    /* [cover parentID={3B52EC8B-A5A5-4913-93DD-7EDE516EF455}]
    Check and issue DET if Init is not called
    [/cover] */
    ErrorFlag = Icu_lInitCallVerify(ICU_17_TIMERIP_SID_DEINIT, CoreId);
  }
  return ErrorFlag;
}
#endif
#endif

#if (ICU_17_TIMERIP_DE_INIT_API == STD_ON)
#if (ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {10EB9434-C2E4-4f64-837D-9CD0ABA247DC}]     **
**                                                                            **
** Syntax : LOCAL_INLINE void Icu_lDeInitEru(                                 **
**               const uint16 EruEicrChannel,                                 **
**               const uint16 OguOutPut)                                      **
**                                                                            **
** Description :      Local function :Service to disable the ERU line         **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        None                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Reentrant for different channel                         **
**                                                                            **
** Parameters (in):   EruEicrChannel: ERU channel Configured                  **
**                    OguOutPut: OGU channel Configured                       **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value:      None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lDeInitEru(
  const uint16 EruEicrChannel,
  const uint16 OguOutPut)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * MISRA rule.As IGCR register is EndInit protected, the address of EICR
   * register needs to be passed to a MCALLIB api to update. Hence to access
   * the register address the datatype is used. */
  volatile Ifx_SCU_EICR* EruAddress;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * MISRA rule.As IGCR register is EndInit protected, the address of IGCR
   * register needs to be passed to a MCALLIB api to update. Hence to access
   * the register address the datatype is used. */
  volatile Ifx_SCU_IGCR* EruIgcrAddress;
  uint32 Mask;

  /* To extract EICR0/EICR1/EICR2 or EICR3 address depending on ERU line used*/
  EruAddress = &(MODULE_SCU.EICR[EruEicrChannel / ICU_ERU_CHNL_PAIR_COUNT]);
  /* Use mask depending on the channel. Even channel uses lower 16 bits and odd
   *  channel uses upper 16 bits.*/
  Mask = (((EruEicrChannel % ICU_ERU_CHNL_PAIR_COUNT) == 0U) ? \
          ICU_EICR_LOWER_HALF_MASK : ICU_EICR_UPPER_HALF_MASK);
  /* [cover parentID={9D0BFE7A-3A52-443d-A30F-6EB435B1A028}]
  Clear the ERU channel's OGU selection and input selection. (EICR register)
  [/cover] */
  /* [cover parentID={8B697CD7-69E8-4d39-A6B6-C868C1DFEAEB}]
    Hardware register access.
  [/cover] */
  ICU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREGMASK(&(EruAddress->U), 0, Mask);

  /* Use mask depending on the channel. Even channel uses lower 16 bits and odd
   *  channel uses upper 16 bits.*/
  Mask = (((OguOutPut % ICU_ERU_CHNL_PAIR_COUNT) == 0U) ? \
          ICU_EICR_LOWER_HALF_MASK : ICU_EICR_UPPER_HALF_MASK);
  EruIgcrAddress = &(MODULE_SCU.IGCR[OguOutPut / ICU_ERU_CHNL_PAIR_COUNT]);
  /* [cover parentID={D60D81E8-6C62-4489-B83A-CF538C024F0E}]
  Disable the interrupts(IGCR register).
  [/cover] */
  /* [cover parentID={8B697CD7-69E8-4d39-A6B6-C868C1DFEAEB}]
    Hardware register access.
  [/cover] */
  ICU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREGMASK(\
      & (EruIgcrAddress->U), 0, Mask);
}/* end of function Icu_lDeInitEru */
#endif
#endif

#if (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) || \
(ICU_17_TIMERIP_GPT12_USED == STD_ON)
#if (ICU_17_TIMERIP_DEV_ERROR_DETECT ==  STD_ON) || \
(ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={70C2374F-3A21-4602-B9D4-47F700DAF379}]      **
**                                                                            **
** Syntax : LOCAL_INLINE uint32 Icu_lEnableMultiEdgeDetCheck (                **
**            const Icu_17_TimerIp_ChannelConfigType *const IcuChanPtr        **
**            const uint32 EdgeCount)                                         **
**                                                                            **
** Description :      Local function :Service for DET check in                **
**                        Icu_17_TimerIp_EnableMultiEdgeDetection() function  **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        None                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Reentrant                                               **
**                                                                            **
** Parameters (in):   LocalIcuChanPtr - Local Channel Ptr                     **
**                    EgdeCount - Number of EgdeCounts                        **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value:      uint32: status of Error                                 **
**                            ICU_ERROR_NOT_FOUND/ICU_ERROR_FOUND             **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Icu_lEnableMultiEdgeDetCheck(
  const Icu_17_TimerIp_ChannelConfigType *const IcuChanPtr, \
  const uint32 EdgeCount)
{
  uint32 ErrorFlag = ICU_ERROR_NOT_FOUND;
  /* [cover parentID={F6E775F1-4B72-4738-83FB-61113F737581}]
  If assigned hardware unit is GTM or GPT12
  [/cover] */
  if (((uint32) (IcuChanPtr->IcuProperties.AssignedHwUnit) !=
       ICU_17_TIMERIP_GTM_OPTION)
      && ((uint32) (IcuChanPtr->IcuProperties.AssignedHwUnit) !=
          ICU_17_TIMERIP_GPT12_OPTION))
  {
    ErrorFlag = ICU_ERROR_FOUND;
    /* [cover parentID={F43D1E33-3EE6-45e2-8407-D12F3E740905}]
    Report an error to indicate invalid channel.
    [/cover] */
    Icu_lReportError(
      ICU_17_TIMERIP_SID_ENABLEMULTIEDGEDETECTION,
      ICU_17_TIMERIP_E_PARAM_CHANNEL); /* Report Error */
  }
  /* [cover parentID={B3987C84-484D-45ef-8329-F457E8A36134}]
  Is input edge count non zero?
  [/cover] */
  else if (EdgeCount == 0U)
  {
    ErrorFlag = ICU_ERROR_FOUND;
    /* [cover parentID={9E7AC677-0456-4aba-970A-8FE28FA3039E}]
    Report an error to indicate wrong edge number value.
    [/cover] */
    Icu_lReportError(
      ICU_17_TIMERIP_SID_ENABLEMULTIEDGEDETECTION,
      ICU_17_TIMERIP_E_PARAM_EDGE_NUMBER); /* Report Error */
  }
  /* [cover parentID={859D517D-21C4-4c0b-9294-412E8E5F4818}]
  Is the edge count within limits?
  [/cover] */
  else if ((EdgeCount > ICU_GPT12_COUNTER_MAX)
           && ((uint32) (IcuChanPtr->IcuProperties.AssignedHwUnit) ==
               ICU_17_TIMERIP_GPT12_OPTION))
  {
    ErrorFlag = ICU_ERROR_FOUND;
    /* [cover parentID={577C22EB-394E-4619-894B-02AA30E849C3}]
    Report error to indicate that the Edge number is not valid.
    [/cover] */
    Icu_lReportError(
      ICU_17_TIMERIP_SID_ENABLEMULTIEDGEDETECTION,
      ICU_17_TIMERIP_E_PARAM_EDGE_NUMBER); /* Report Error */
  }
  /* Check for GTM is implicit and not required.*/
  else if ((EdgeCount > ICU_GTM_TIMER_MAX))
  {
    ErrorFlag = ICU_ERROR_FOUND;
    /* [cover parentID={577C22EB-394E-4619-894B-02AA30E849C3}]
    Report error to indicate that the Edge number is not valid.
    [/cover] */
    Icu_lReportError(
      ICU_17_TIMERIP_SID_ENABLEMULTIEDGEDETECTION,
      ICU_17_TIMERIP_E_PARAM_EDGE_NUMBER); /* Report Error */
  }
  else
  {
    /*Parameters valid.*/
  }
  return ErrorFlag;
}
#endif
/* End of Icu_lEnableMultiEdgeDetChheck() function */
#endif
#endif

#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) && \
(ICU_17_TIMERIP_EDGE_DETECT_API ==STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {CCCD39DA-9C74-4def-8310-A289272126F1}]     **
**                                                                            **
** Syntax : LOCAL_INLINE void Icu_lGtmStartMultiEdgeDetect(                   **
**                           const uint16 GlobalChannelNumber,                **
**                           const uint32 EdgeCount)                          **
**                                                                            **
** Description :    Function to configure TIM Channel given by                **
**                  GlobalChannelNumber to scan the input .This function      **
**                  should be called with a disabled TIM Channel              **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  GlobalChannelNumber - Channel Number                     **
**                   EdgeCount - Number of edges for detection                **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
*                                                                             **
*******************************************************************************/
LOCAL_INLINE void Icu_lGtmStartMultiEdgeDetect(
  const uint16 GlobalChannelNumber,
  const uint32 EdgeCount)
{
  Ifx_GTM_TIM_CH* TimChannelRegPtr;   /* Pointer to TIM Channel Reg    */
  uint8 ModuleNo;                          /* Holds the TIM module Number   */
  uint8 ChannelNo;                           /* Holds the TIM Channel Number  */

  /* Calculate Module Id of the TIM channel */
  ModuleNo = (uint8)((GlobalChannelNumber / ICU_GTM_CHANNELS_PER_TIM_MODULE) \
                     & ICU_GTM_MODULE_NO_MSK);
  /* Calculate Channel number of the TIM channel */
  ChannelNo = (uint8)(GlobalChannelNumber % ICU_GTM_CHANNELS_PER_TIM_MODULE);

  /* Get the pointer to TIM Channel Register Structure */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TimChannelRegPtr = GTM_TIM_CH_POINTER(ModuleNo, ChannelNo);
  /* Disable the Channel */
  TimChannelRegPtr->CTRL.U &= ~ICU_GTM_TIM_ENABLE_CHANNEL ;
  /* Clear all Pending Interrupts */
  TimChannelRegPtr->IRQ.NOTIFY.U = ICU_GTM_CLEAR_INTERRUPTS;
  /* Set TIM channel mode to TIPM */
  TimChannelRegPtr->CTRL.U |=
    (uint32)((ICU_GTM_TIM_MODE_TIPM << ICU_GTM_TIM_MODE_POS));
  /* Set the Edge Count value in CNTS register */
  TimChannelRegPtr->CNTS.U = (uint32)(EdgeCount - 1UL);
  /* Enable the TIM channel to start multiple edge detection */
  TimChannelRegPtr->CTRL.U |= ICU_GTM_TIM_ENABLE_CHANNEL ;
}
#endif

#if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON)|| \
(ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {A772B2E1-7555-4c15-A8FF-5251F991E63B}]     **
**                                                                            **
** Syntax : static void Icu_lReportError( const uint8 ApiId,                  **
**                                          const uint8 ErrorId)              **
**                                                                            **
** Description :    Function to report Safety Error and DET                   **
** [/cover]                                                                   **
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
*                                                                             **
*******************************************************************************/
static void Icu_lReportError(const uint8 ApiId,
                             const uint8 ErrorId)
{
  /* [cover parentID={7148A879-E6F0-415e-B1A6-C15B09114B47}]
  If DET reporting is enabled
  [/cover] */
  #if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={31B8E346-72AE-4677-ADA0-5F5E1DEE49F0}]
  Report DET
  [/cover] */
  (void)Det_ReportError(
    ICU_17_TIMERIP_MODULE_ID,
    ICU_17_TIMERIP_INSTANCE_ID,
    ApiId,
    ErrorId);/* End of report to DET */
  #endif
  /* [cover parentID={02AA937B-B749-4f7a-AF59-09774E88C5D3}]
  If Safety error reporting is enabled.
  [/cover] */
  #if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={05EC866C-354A-4f64-AB9C-0CDEDA0D0449}]
  Report Safety Error
  [/cover] */
  Mcal_ReportSafetyError(
    ICU_17_TIMERIP_MODULE_ID,
    ICU_17_TIMERIP_INSTANCE_ID,
    ApiId,
    ErrorId);/* End of report to Safety */
  #endif
}
#endif
#if (ICU_17_TIMERIP_TIMESTAMP_API == STD_ON)
#if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON) || \
    (ICU_17_TIMERIP_RUNTIME_ERROR_DETECT == STD_ON) || \
    ((MCAL_AR_VERSION == MCAL_AR_422) && (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON))
/*******************************************************************************
 ** Traceability: [cover parentID= {FF9563A1-6628-47bd-8B09-905A3F4C68A1}]     **
 **                                                                            **
 ** Syntax : static void Icu_lReportRuntimeDetError( const uint8 ApiId,        **
 **                                          const uint8 ErrorId)              **
 **                                                                            **
 ** Description :    Function to report runtime Error or safety and DET        **
 ** [/cover]                                                                   **
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
 *                                                                             **
 *******************************************************************************/
static void Icu_lReportRuntimeDetError(const uint8 ApiId, const uint8 ErrorId)
{
/* [cover parentID={47EBEF6B-54EC-48b7-B382-1253BF4DE8B1}]
If Runtime error detection enabled
[/cover] */
#if (ICU_17_TIMERIP_RUNTIME_ERROR_DETECT == STD_ON)
  /* [cover parentID={AA58CBC2-5CD5-4042-B376-150882B92DF4}]
  Report runtime error
  [/cover] */
  (void)Mcal_Wrapper_Det_ReportRuntimeError(
    ICU_17_TIMERIP_MODULE_ID,
    ICU_17_TIMERIP_INSTANCE_ID, ApiId, ErrorId);
#elif (MCAL_AR_VERSION == MCAL_AR_422)
/* [cover parentID={54CBD61B-385D-4e7e-A975-834D1C456281}]
If DET reporting enabled?
[/cover] */
#if (ICU_17_TIMERIP_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={A44ACEA8-A3B7-4e8b-94D4-A505BB445998}]
  Report DET
  [/cover] */
  (void)Det_ReportError(
    ICU_17_TIMERIP_MODULE_ID,
    ICU_17_TIMERIP_INSTANCE_ID, ApiId, ErrorId);/* End of report to DET */
#endif
/* [cover parentID={8DE80CAE-AECA-4ee5-B2AD-B0F5DE1BC2B1}]
Safety error reporting is enabled
[/cover] */
#if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={C012F9E3-EB65-4a2b-A8A1-D2E2ED911950}]
  Report Safety error
  [/cover] */
  Mcal_ReportSafetyError(
    ICU_17_TIMERIP_MODULE_ID,
    ICU_17_TIMERIP_INSTANCE_ID, ApiId, ErrorId);/* End of report to Safety */
#endif
#endif
}
#endif
#endif

#if (ICU_17_TIMERIP_INCREMENTAL_INTERFACE_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={A669D886-CFA5-4b2d-A5DC-DB0F448A5383}]      **
**                                                                            **
** Syntax : LOCAL_INLINE void Icu_lGpt12SetCounter (                          **
**                            const uint16 GlobalChannelNumber                **
**                            const uint16 Count)                             **
**                                                                            **
** Description :     Function to Set the GPT12 timer count                    **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  GlobalChannelNumber - Channel Number                     **
**                   Count -  Counter value to be set                         **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lGpt12SetCounter(const uint16 GlobalChannelNumber,
                                 const uint16 Count)
{
  uint8 ChannelNo;                              /* Holds the GPT12 Tx Number  */
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
    MISRA rule. Union usage is required to access SFR data type and implement
    efficiently for accessing Timer control registers */
  volatile Ifx_GPT12_T2* Gpt12TxRegPtr;
  Ifx_GPT12* Gpt12BasePtr;

  /* Extract Channel Number */
  ChannelNo = (uint8)GlobalChannelNumber & ICU_LOWER_NIBBLE;
  Gpt12BasePtr = &MODULE_GPT120;
  Gpt12TxRegPtr = &(Gpt12BasePtr->T2);
  Gpt12TxRegPtr = &(Gpt12TxRegPtr[ChannelNo]);

  /* Set the Tx Register to input count value */
  Gpt12TxRegPtr->U = (uint32)Count;
}
#endif

#if (ICU_17_TIMERIP_INCREMENTAL_INTERFACE_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={382E02DD-8F93-4d7d-A07B-FFA9F11513C9}]      **
**                                                                            **
** Syntax : LOCAL_INLINE uint16 Icu_lGpt12ReadCounter (                       **
**                            const uint16 GlobalChannelNumber )              **
**                                                                            **
** Description :     Function to read the GPT12 timer count                   **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  GlobalChannelNumber - Channel Number                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     uint16 : Counter value                                   **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint16 Icu_lGpt12ReadCounter(const uint16 GlobalChannelNumber)
{
  uint8 ChannelNo;                              /* Holds the GPT12 Tx Number  */
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
    MISRA rule. Union usage is required to access SFR data type and implement
    efficiently for accessing Timer control registers */
  volatile Ifx_GPT12_T2* Gpt12TxRegPtr;
  Ifx_GPT12* Gpt12BasePtr;

  /* Extract Channel Number */
  ChannelNo = (uint8)GlobalChannelNumber & ICU_LOWER_NIBBLE;
  Gpt12BasePtr = &MODULE_GPT120;
  Gpt12TxRegPtr = &(Gpt12BasePtr->T2);
  Gpt12TxRegPtr = &(Gpt12TxRegPtr[ChannelNo]);

  return((uint16)(Gpt12TxRegPtr->U));
}
#endif

#if (ICU_17_TIMERIP_INCREMENTAL_INTERFACE_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={1A1F7D43-9DED-4541-95A4-75E8F5DF0A15}]      **
**                                                                            **
** Syntax : LOCAL_INLINE Icu_17_TimerIp_EncCountDirType Icu_lGpt12ReadDir (   **
**                            const uint16 GlobalChannelNumber )              **
**                                                                            **
** Description :     Function to get the GPT12 timer count direction          **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  GlobalChannelNumber - Channel Number                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     uint16 : Counter value                                   **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Icu_17_TimerIp_EncCountDirType Icu_lGpt12ReadDir(
      const uint16 GlobalChannelNumber)
{
  Icu_17_TimerIp_EncCountDirType ReturnDir;
  uint8 ChannelNo;                              /* Holds the GPT12 Tx Number  */
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
    MISRA rule. Union usage is required to access SFR data type and implement
    efficiently for accessing Timer control registers */
  volatile Ifx_GPT12_T2CON* Gpt12TxConRegPtr;
  Ifx_GPT12* Gpt12BasePtr;

  /* Extract Channel Number */
  ChannelNo = (uint8)GlobalChannelNumber & ICU_LOWER_NIBBLE;
  Gpt12BasePtr = &MODULE_GPT120;
  Gpt12TxConRegPtr = &(Gpt12BasePtr->T2CON);
  Gpt12TxConRegPtr = &(Gpt12TxConRegPtr[ChannelNo]);
  if((Mcal_GetBitAtomic(Gpt12TxConRegPtr->U,IFX_GPT12_T2CON_T2RDIR_OFF,\
          IFX_GPT12_T2CON_T2RDIR_LEN) & IFX_GPT12_T2CON_T2RDIR_LEN) != 0U)
  {
    ReturnDir=ICU_17_TIMERIP_ENC_COUNT_DOWN;
  }
  else
  {
    ReturnDir=ICU_17_TIMERIP_ENC_COUNT_UP;
  }
  return(ReturnDir);
}
#endif

#if (ICU_17_TIMERIP_TIMEOUT_DETECTION_API == STD_ON)
/*******************************************************************************
 ** Traceability: [cover parentID= {09FED1DB-11CA-4566-B6B2-2750BE70C26F}]     **
 **                                                                            **
 ** Syntax : LOCAL_INLINE void Icu_lGtmSetTDUV(                                **
 **                           const uint16 GlobalChannelNumber,                **
 **                           const uint32 TimeoutValue )                      **
 **                                                                            **
 ** Description :     Function to configure timeout for a TIM Channel          **
 ** [/cover]                                                                   **
 **                                                                            **
 ** Service ID:       None                                                     **
 **                                                                            **
 ** Sync/Async:       Synchronous                                              **
 **                                                                            **
 ** Reentrancy:       Reentrant for different channel                          **
 **                                                                            **
 ** Parameters (in):  GlobalChannelNumber - Channel Number                     **
 **                   TimeoutValue : Timeout value to be set                   **
 **                                                                            **
 ** Parameters (out): None                                                     **
 **                                                                            **
 ** Return value:     None                                                     **
 **                                                                            **
 *******************************************************************************/
LOCAL_INLINE void Icu_lGtmSetTDUV(const uint16 GlobalChannelNumber,
    const uint32 TimeoutValue, const uint32 CTRLRegvalue)
{
  Ifx_GTM_TIM_CH* TimChannelRegPtr; /* Pointer to TIM Channel Reg    */
  uint8 ModuleNo; /* Holds the TIM module Number   */
  uint8 ChannelNo; /* Holds the TIM Channel Number  */
  uint32 TDUVRegvalue;
  /* Calculate Module Id of the TIM channel */
  ModuleNo = (uint8)((GlobalChannelNumber / ICU_GTM_CHANNELS_PER_TIM_MODULE)
      & ICU_GTM_MODULE_NO_MSK);
  /* Calculate Channel number of the TIM channel */
  ChannelNo = (uint8)(GlobalChannelNumber % ICU_GTM_CHANNELS_PER_TIM_MODULE);

  /* Get the pointer to TIM Channel Register Structure */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TimChannelRegPtr = GTM_TIM_CH_POINTER(ModuleNo, ChannelNo);
  /* To disable the timeout when timeout value is 0, disable in CTRL */
  if(TimeoutValue == 0U)
  {
    TimChannelRegPtr->CTRL.U = TimChannelRegPtr->CTRL.U &
          (~((uint32)IFX_GTM_TIM_CH_CTRL_TOCTRL_MSK << IFX_GTM_TIM_CH_CTRL_TOCTRL_OFF));
  }
  else
  {
    TimChannelRegPtr->CTRL.U = TimChannelRegPtr->CTRL.U |
                    (CTRLRegvalue & ((uint32)IFX_GTM_TIM_CH_CTRL_TOCTRL_MSK
                                    << IFX_GTM_TIM_CH_CTRL_TOCTRL_OFF));
  }
  TDUVRegvalue = TimChannelRegPtr->TDUV.U;
  TDUVRegvalue = TDUVRegvalue & (~(ICU_TIMEOUT_MASK));
  TDUVRegvalue = TDUVRegvalue | (TimeoutValue & ICU_TIMEOUT_MASK);
  TimChannelRegPtr->TDUV.U = TDUVRegvalue;

}
#endif


#if (ICU_17_TIMERIP_MULTICORE_ERROR_DETECT == STD_ON)|| \
(ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={76950998-FABA-4c5f-B9C1-6892EE9E1061}]      **
**                                                                            **
** Syntax : static void Icu_lReportMulticoreError( const uint8 ApiId,         **
**                                          const uint8 ErrorId)              **
**                                                                            **
** Description :    Function to report Multicore Safety Error and DET         **
** [/cover]                                                                   **
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
*                                                                             **
*******************************************************************************/
static void Icu_lReportMulticoreError(const uint8 ApiId,
                                      const uint8 ErrorId)
{
  /* [cover parentID={D04778E3-C27F-4f82-ADB6-A49483AFE6A5}]
  If Multicore DET reporting is enabled
  [/cover] */
  #if (ICU_17_TIMERIP_MULTICORE_ERROR_DETECT == STD_ON)
  /* [cover parentID={C7FACEE8-1C8B-45df-8F33-CA1B57244F43}]
  Report MultiCore DET
  [/cover] */
  (void)Det_ReportError(
    ICU_17_TIMERIP_MODULE_ID,
    ICU_17_TIMERIP_INSTANCE_ID,
    ApiId,
    ErrorId);/* End of report to DET */
  #endif
  /* [cover parentID={56B65529-6DB3-4807-B5F6-3C08486E9784}]
  If Safety error reporting is enabled.
  [/cover] */
  #if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={94BB2B72-4F23-440b-B883-809667B4D25F}]
  Report Safety Error
  [/cover] */
  Mcal_ReportSafetyError(
    ICU_17_TIMERIP_MODULE_ID,
    ICU_17_TIMERIP_INSTANCE_ID,
    ApiId,
    ErrorId);/* End of report to Safety */
  #endif
}
#endif
/*******************************************************************************
**                      Interrupt Function Definitions                        **
 ******************************************************************************/

/*******************************************************************************
** Traceability: [cover parentID= {EDAD13A1-8001-416b-90EE-DF96FCEB90FD}]     **
**                                                                            **
** Syntax : void Icu_17_TimerIp_Timer_Isr(                                    **
**   const uint32 Channel, const uint32 StatusFlags)                          **
**                                                                            **
** Description : Callback from MCU to service Timer interrupts                **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  None                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant for different channel                               **
**                                                                            **
** Parameters (in): Channel - Logical Channel Identifier                      **
**                  StatusFlags - Interrupt flag status                       **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value: None                                                         **
**                                                                            **
*******************************************************************************/
void Icu_17_TimerIp_Timer_Isr (const uint32 Channel, const uint32 StatusFlags)
{
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr;     /* ROM pointer */
  uint8 CoreId;
  uint8 CoreChIndex;
  #if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  uint8 ExtractCoreId;
  uint8 CoreIndex;
  uint8 ErrorFlag;
  #endif

  /* Get core id which is executing currently */
  CoreId = (uint8)(Mcal_GetCpuIndex());
  /* [cover parentID={9BF74E6C-7569-4dd0-8951-B135BF5A509C}]
  If Safety is enabled
  [/cover] */
  #if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  /* Initialize error flag to not error found */
  ErrorFlag = (uint8) ICU_ERROR_NOT_FOUND;
  CoreIndex = (CoreId * (uint8) (ICU_INIT_STAUS_SIZE));
  /* [cover parentID={C2A738AA-3422-4838-AD6B-DB4CD1A416A8}]
  Is the module initialization done?
  [/cover] */
  if (ICU_INITIALIZED \
      != (Mcal_GetBitAtomic(Icu_17_TimerIp_InitStatus, ((sint32 )(CoreIndex)), \
                            ICU_INIT_STAUS_SIZE)))
  {
    ErrorFlag = (uint8) ICU_ERROR_FOUND;
  }

  /* channel validation */
  /* [cover parentID={E2FBF681-4998-44fe-9B48-44760F73AF63}]
  Is the channel id valid?
  [/cover] */
  if((Channel < ICU_17_TIMERIP_MAX_CHANNELS) && (ErrorFlag != ICU_ERROR_FOUND))
  {
    #if (ICU_17_TIMERIP_SINGLE_CORE == STD_OFF)
    ExtractCoreId = \
                    (uint8)((Icu_17_TimerIp_ConfigPtr->ChannelMapping[Channel] &
                             (ICU_CHNL_MAP_CORE_ID_MASK)) >> ICU_CHNL_MAP_POS);
    #else
    ExtractCoreId = ICU_17_TIMERIP_SINGLE_CORE_ID;
    #endif
    /* Core validation */
    /* [cover parentID={18EB341A-4D3D-413d-88C9-51BFDF8EF325}]
    Is the current core and core to which channel is allocated same?
    [/cover] */
    if(ExtractCoreId != CoreId)
    {
      /* Safety Error */
      /* [cover parentID={0B63DFCA-64B0-4528-B792-3B5F02571121}]
      Report Safety Error
      [/cover] */
      /* [cover parentID={AFC24552-14D4-4aa9-B432-6705AAA7F231}]
      Report Safety Error
      [/cover] */
      Mcal_ReportSafetyError(
        ICU_17_TIMERIP_MODULE_ID,
        ICU_17_TIMERIP_INSTANCE_ID,
        ICU_17_TIMERIP_SID_ISR,
        ICU_17_TIMERIP_E_INVALID_ISR);
    }
    else
  #endif
      /* end report safety */
    {
      /* Extract core specific channel index */
      CoreChIndex = Icu_lGetCoreChIndex((uint8)Channel);
      /* Initialize ICU configured channel ROM pointer */
      LocalIcuChanPtr = &((Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->
                                                ChannelConfigPtr)[CoreChIndex]);
      /* Call the hardware specific ISR */
      switch (LocalIcuChanPtr->IcuProperties.AssignedHwUnit)
      {
        /* GTM-TIM ISR handler */
        /* [cover parentID={6DC636F6-FFAF-4198-809D-AE32A66CA6B1}]
        Is the chanel using GTM HW?
        [/cover] */
        case ICU_17_TIMERIP_GTM_OPTION:
          /* [cover parentID={DF0910D9-161D-4c81-AE0F-9656CC519BB1}]
          Call GTM-TIM ISR
          [/cover] */
          #if(ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
          Icu_lTim_Isr((Icu_17_TimerIp_ChannelType)CoreChIndex, StatusFlags);
          #endif
          break;

        /* CCU6 ISR handler */
        /* [cover parentID={DC62797A-6228-4a6e-A389-C6DF9EB2E512}]
        Is the chanel using CCU6 HW?
        [/cover] */
        case ICU_17_TIMERIP_CCU_OPTION:
          /* [cover parentID={BA53B102-5C23-496d-BAD3-7D17BE2370F7}]
          Call CCU6 ISR
          [/cover] */
          #if(ICU_17_TIMERIP_CCU6_USED == STD_ON)
          Icu_lCcu_Isr((Icu_17_TimerIp_ChannelType)CoreChIndex, StatusFlags);
          #endif
          break;
        /* ERU ISR handler */
        /* [cover parentID={1A783D5F-B302-44b7-A8DD-23D1B84E7816}]
        Is the chanel using ERU HW?
        [/cover] */
        case ICU_17_TIMERIP_ERU_OPTION:
          /* [cover parentID={79A4D9BB-BC96-40ba-8936-BC08D4E7B6C7}]
          Call ERU ISR
          [/cover] */
          #if(ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON)
          Icu_lEru_Isr((Icu_17_TimerIp_ChannelType)CoreChIndex);
          #endif
          break;
        default:
          /* [cover parentID={BB794F32-1D6B-4bf3-9A17-A97F511690C9}]
          Is the chanel using GPT12 HW?
          [/cover] */
          /* GPT12 ISR handler */
          #if(ICU_17_TIMERIP_GPT12_USED == STD_ON)
          /* [cover parentID={DFEA7707-465D-4529-9CD0-C25CDFE18412}]
          Call GPT12 ISR
          [/cover] */
          Icu_lGpt12_Isr((Icu_17_TimerIp_ChannelType)CoreChIndex);
          #endif
          break;
      }
    }
    /* [cover parentID={94FB6680-D902-480a-A061-FC81D48AAA25}]
    If Safety is enabled
    [/cover] */
    #if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  }
  else
  {
    /* Spurious Interrupt */
    /* [cover parentID={9D7176E3-8448-4e63-BF1E-5CBBD58FFF87}]
    Report Safety Error
    [/cover] */
    Mcal_ReportSafetyError(
      ICU_17_TIMERIP_MODULE_ID,
      ICU_17_TIMERIP_INSTANCE_ID,
      ICU_17_TIMERIP_SID_ISR,
      ICU_17_TIMERIP_E_INVALID_ISR);
  }
    #endif
  #if (ICU_17_TIMERIP_GTM_TIM_USED == STD_OFF) || \
  (ICU_17_TIMERIP_CCU6_USED == STD_OFF)
  UNUSED_PARAMETER(StatusFlags);
  #endif
}


#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {1000709D-F03B-4b58-857A-72E37A261915}]     **
**                                                                            **
** Syntax : LOCAL_INLINE void Icu_lTim_Isr (                                  **
**   const uint8 CoreChIndex, const uint32 StatusFlags )                      **
**                                                                            **
** Description : Interrupt Service Routine for ICU GTM-TIM channel            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  CoreChIndex - Core specific channel index                **
**                   StatusFlags -  ISR Status flag                           **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lTim_Isr(
  const uint8 CoreChIndex, const uint32 StatusFlags)
{
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr; /* ROM pointer */
  uint32* GlbIndexStatusPtr;
  #if (ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON)
  uint32 CntStsOverflow;
  #endif
  #if (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON) || \
      (ICU_17_TIMERIP_TIMESTAMP_API == STD_ON)
  uint32 NewvalSts;
  #endif
  #if (ICU_17_TIMERIP_TIMEOUT_DETECTION_API == STD_ON)
  #if (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON) || \
      (ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON)
  uint32 TDUSts;
  #endif
  #endif
  #if (ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON)
  uint8 ChIndex;
  #endif
  uint8 CoreId;
  /* Get core id which is executing currently */
  CoreId = (uint8)(Mcal_GetCpuIndex());

  #if (ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON)
  /*Read Interrupt overflow status bits from status flag*/
  CntStsOverflow = (StatusFlags & ICU_GTM_CNTOVFL_FLAG_SET);
  #endif
  #if (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON) || \
      (ICU_17_TIMERIP_TIMESTAMP_API == STD_ON)
  /*Read Interrupt new_val status bits from status flag*/
  NewvalSts = (StatusFlags & ICU_GTM_NEWVAL_FLAG_SET);
  #endif
  #if (ICU_17_TIMERIP_TIMEOUT_DETECTION_API == STD_ON)
  #if (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON) || \
      (ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON)
  TDUSts = (StatusFlags & ICU_GTM_TDU_FLAG_SET);
  #endif
  #endif
  /* Initialize ICU configured channel ROM pointer */
  LocalIcuChanPtr = &((Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->
                                                ChannelConfigPtr)[CoreChIndex]);
  GlbIndexStatusPtr =
        &((Icu_17_TimerIp_Varlist[CoreId]->GlbIndexStatusBasePtr)[CoreChIndex]);
  switch (LocalIcuChanPtr->IcuProperties.MeasurementMode)
  {
    /* [cover parentID={51BB2888-DFDB-4f4e-8A6F-288136F1F3A2}]
    If signal measurement mode is edge detect
    [/cover] */
    case (uint32) ICU_17_TIMERIP_MODE_SIGNAL_EDGE_DETECT:
      #if (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
      /* [cover parentID={B5D33AC5-4523-4d72-A319-1637517AA08A}]
      Saftery error reporting enabled
      [/cover] */
      /* [cover parentID={1A2927F5-B75D-489f-8174-77D0266BC2F1}]
      Is NEWVAL flag set?
      [/cover] */
      if (NewvalSts == ICU_GTM_NEWVAL_FLAG_SET)
      {
        /* [cover parentID={B7F4B3E5-392E-47d9-A7FC-7A941E693289}]
        Call edge notification ISR
        [/cover] */
        Icu_lSignalEdgeNotification_Isr(CoreId, LocalIcuChanPtr,
                                        GlbIndexStatusPtr);
      }
      #if (ICU_17_TIMERIP_TIMEOUT_DETECTION_API == STD_ON)
      /* [cover parentID={4B873C7E-5A33-46b7-93EA-FD130FF07FF5}]
      Is TDU flag set?
      [/cover] */
      else if (TDUSts == ICU_GTM_TDU_FLAG_SET)
      {
        /* [cover parentID={87D35C81-198C-4067-B6D7-E7D45F8872C3}]
        TIM Timeout ISR
        [/cover] */
        Icu_lGtmTimeOutIsr(LocalIcuChanPtr, GlbIndexStatusPtr);
      }
      #endif
      else
      {
#if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
        /* [cover parentID={E1547DBB-FC7B-4d70-9CCD-F98A647C7790}]
        Report Safety error
        [/cover] */
        Mcal_ReportSafetyError(
          ICU_17_TIMERIP_MODULE_ID,
          ICU_17_TIMERIP_INSTANCE_ID,
          ICU_17_TIMERIP_SID_ISR,
          ICU_17_TIMERIP_E_INVALID_ISR);
#endif
      }
      /* End of report to Safety */
      #endif
      break;
    /* [cover parentID={E88D0102-631D-468c-94DE-BB18FA294AD2}]
    If the measurement mode is signal measuremet
    [/cover] */
    case (uint32) ICU_17_TIMERIP_MODE_SIGNAL_MEASUREMENT:
      /*Signal measurement mode*/
      #if (ICU_17_TIMERIP_SIGNAL_MEASUREMENT_API == STD_ON)
      /* Check if ISR is valid */
      /* [cover parentID={A1D6C712-5BA0-45ae-82A1-A257253D820F}]
      Is CNTOFL or NEWVAL flag set?
      [/cover] */
      if((StatusFlags & (ICU_GTM_CNTOVFL_FLAG_SET | ICU_GTM_NEWVAL_FLAG_SET)) != 0U)
      /*if ((CntStsOverflow == ICU_GTM_CNTOVFL_FLAG_SET)
          || (NewvalSts == ICU_GTM_NEWVAL_FLAG_SET))*/
      {
        /* [cover parentID={0C153145-E4F6-4ded-8310-E0ABC1DFC746}]
        Call signal measurement ISR
        [/cover] */
        Icu_lGtmSignalMeasureIsr( LocalIcuChanPtr, GlbIndexStatusPtr);
        /* [cover parentID={5D879868-7065-4fcc-B754-40FB3C7ACD6D}]
        Saftery error reporting enabled
        [/cover] */
      }
      else
      {
#if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
        /* [cover parentID={8B8A496E-DFF4-42e6-AAF6-606817334F0E}]
        Report Safety error
        [/cover] */
        /* Safety Error */
        Mcal_ReportSafetyError(
          ICU_17_TIMERIP_MODULE_ID,
          ICU_17_TIMERIP_INSTANCE_ID,
          ICU_17_TIMERIP_SID_ISR,
          ICU_17_TIMERIP_E_INVALID_ISR);
#endif
      }
      /* End of report to Safety */
      #endif
      break;
    /* [cover parentID={1FBE7C31-FA77-46ec-8DC5-78E4DFCA0CAE}]
    If the measurement mode is timestamp
    [/cover] */
    case (uint32) ICU_17_TIMERIP_MODE_TIMESTAMP:
      /* [cover parentID={D5B6F662-B455-4d5e-B811-0FACCC1E3841}]
       If Time stamp API are available
       [/cover] */
      #if (ICU_17_TIMERIP_TIMESTAMP_API == STD_ON)
      /* [cover parentID={E278AAA9-32E2-4ea4-B1CF-F2F45B8F3B31}]
      Is the Newval flag set?
      [/cover] */
      if (NewvalSts == ICU_GTM_NEWVAL_FLAG_SET)
      {
        /* [cover parentID={D58BABB3-03BA-4bd1-9555-9330F0F2CE21}]
        Timestamp for Gtm
        [/cover] */
        Icu_lTimeStamp_Isr(CoreId, LocalIcuChanPtr, GlbIndexStatusPtr);
        /* [cover parentID={D0EF60A2-82CE-4597-BFDB-6B9B4EDD4BA8}]
        Safety reporting error enabled
        [/cover] */
      }
      else
      {
#if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
        /* [cover parentID={8F0315D1-C4AE-47cd-B193-53EB23F7FFB3}]
        Report Safety Error to indicate invalid ISR
        [/cover] */
        Mcal_ReportSafetyError(
          ICU_17_TIMERIP_MODULE_ID,
          ICU_17_TIMERIP_INSTANCE_ID,
          ICU_17_TIMERIP_SID_ISR,
          ICU_17_TIMERIP_E_INVALID_ISR);/* End of report to Safety */
#endif
      }
        #endif
      break;
    /* [cover parentID={AC4A5C9C-BCDF-4629-8D54-55AFF22F6BBA}]
    If the measurement mode is edge counter
    [/cover] */
    default:/*Edge count mode*/
      #if (ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON)
      /* Extract the mode specific index */
      /* [cover parentID={5D794929-0B77-4909-9EC9-D44355851E65}]
      Is the CNTOFL flag set?
      [/cover] */
      if (CntStsOverflow == ICU_GTM_CNTOVFL_FLAG_SET)
      {
        ChIndex = LocalIcuChanPtr->ModeMappingIndex;
        /* [cover parentID={8C121766-873E-45c5-A074-710B5FF3B26A}]
        EdgeCount for Gtm
        [/cover] */
        Icu_lGtmEdgeCountIsr(ChIndex, CoreId, GlbIndexStatusPtr);
      }
      #if (ICU_17_TIMERIP_TIMEOUT_DETECTION_API == STD_ON)
      /* [cover parentID={D1F42928-5D1B-4e81-A9D7-D10419464B7A}]
      Is TDU flag set?
      [/cover] */
      else if (TDUSts == ICU_GTM_TDU_FLAG_SET)
      {
        /* [cover parentID={2C8827DB-B7FC-4947-A257-A303127430BD}]
        TIM timeout ISR
        [/cover] */
        Icu_lGtmTimeOutIsr(LocalIcuChanPtr, GlbIndexStatusPtr);
      }
      #endif
      else
      {
        /* [cover parentID={40CC37FC-83D7-41f8-AAA6-21F70E3CCF4A}]
        Safety reporting error enabled
        [/cover] */
#if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
        /* [cover parentID={5752B43B-5D8F-4a27-BD57-96F303DC9109}]
        Report Safety Error to indicate invalid ISR
        [/cover] */
        /* Safety Error */
        Mcal_ReportSafetyError(
          ICU_17_TIMERIP_MODULE_ID,
          ICU_17_TIMERIP_INSTANCE_ID,
          ICU_17_TIMERIP_SID_ISR,
          ICU_17_TIMERIP_E_INVALID_ISR);
#endif
      }
      /* End of report to Safety */
      #endif
      break;
  }
  #if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_OFF)
  UNUSED_PARAMETER(StatusFlags);
  #endif
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer GlbIndexStatusPtr is
   * accessed using assembly instruction. */
}/* #if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) */
/* [/cover]  */
#endif

#if (ICU_17_TIMERIP_CCU6_USED == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {B11B06DB-B352-4086-82EC-BB7CF6D21D0A}]     **
**                                                                            **
** Syntax:           LOCAL_INLINE void Icu_lCcu_Isr(                          **
**                    const uint8 CoreChIndex, const uint32 StatusFlags )     **
**                                                                            **
** Description :     This is Interrupt Routine Functions for the CCU lines    **
**                   lines. When interrupt occurs corresponding CCU line      **
**                   Service request will be invoked.                         **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  CoreChIndex - Core specific channel index                **
**                   StatusFlags- interrupt Status Flag from MCU              **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lCcu_Isr(
  const uint8 CoreChIndex, const uint32 StatusFlags)
{
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr;
  uint32* GlbIndexStatusPtr;
  uint8 CoreId;
  #if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  uint32 Ccu6ConfigEgde;
  uint32 IsrStatusFlag;

  /*Read ISR Flags from StausFlag*/
  IsrStatusFlag = (StatusFlags & ICU_CCU6_ISR_FLAGS_MASK);
  #else
  UNUSED_PARAMETER(StatusFlags);
  #endif
  /* Get core id which is executing currently */
  CoreId = (uint8)(Mcal_GetCpuIndex());
  /* Initialize ICU configured channel ROM pointer */
  LocalIcuChanPtr = &((Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->
                                                ChannelConfigPtr)[CoreChIndex]);
  /* Extract the address for the Global Index status */
  GlbIndexStatusPtr =
        &((Icu_17_TimerIp_Varlist[CoreId]->GlbIndexStatusBasePtr)[CoreChIndex]);
  #if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
   /*Read Configured egde from config for this channel*/
  Ccu6ConfigEgde = (uint32)(Mcal_GetBitAtomic(*GlbIndexStatusPtr,\
        ICU_CHNL_EDGE_POS,ICU_CHNL_EDGE_BIT_LENGTH));
  #endif
  switch((uint32)LocalIcuChanPtr->IcuProperties.MeasurementMode)
  {
    /* [cover parentID={18304AA2-F8B1-4043-BC08-E1C2A11F2F52}]
    Is the mode if channel Edge detection?
    [/cover] */
    case (uint32)ICU_17_TIMERIP_MODE_SIGNAL_EDGE_DETECT:
      /* [cover parentID={00CA7D1A-7CCC-4193-B836-289D89B7C466}]
      Call ISR for edge detect channel.
      [/cover] */
      #if (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
      /* [cover parentID={857D66F8-3AB2-4c51-842A-3AE19A6ACD20}]
      If ISR status is same as configured edge
      [/cover] */
      #if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
      if((IsrStatusFlag & (Ccu6ConfigEgde + 1U)) != 0U)
      #endif
      {
        /* [cover parentID={00CA7D1A-7CCC-4193-B836-289D89B7C466}]
        Call ISR for edge detect channel.
        [/cover] */
        Icu_lSignalEdgeNotification_Isr(CoreId, LocalIcuChanPtr, \
                                        GlbIndexStatusPtr);
      }
      /* [cover parentID={845F1461-B557-4814-AA4E-205BB70B55D0}]
      If Safety is enabled
      [/cover] */
      #if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
      else
      {
        /* [cover parentID={E45EFCC4-6ACE-42df-8B31-1AB245FA50A6}]
        Report Safety error
        [/cover] */
        /* Safety Error */
        Mcal_ReportSafetyError(
          ICU_17_TIMERIP_MODULE_ID,
          ICU_17_TIMERIP_INSTANCE_ID,
          ICU_17_TIMERIP_SID_ISR,
          ICU_17_TIMERIP_E_INVALID_ISR);
      }
      #endif
      /* End of report to Safety */
      #endif
      /*(ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)*/
      break;
    /* [cover parentID={33C3C9AE-325B-46c2-8577-136E07D905AB}]
    Is the mode if channel Edge detection?
    [/cover] */
    case (uint32) ICU_17_TIMERIP_MODE_TIMESTAMP:
      #if (ICU_17_TIMERIP_TIMESTAMP_API ==STD_ON)
      #if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
      /* [cover parentID={44FE3A00-0895-418c-8A6A-4115D45E6D3D}]
      Check if activity started
      [/cover] */
      if ((ICU_ACTIVITY_STARTED ==
        Mcal_GetBitAtomic(*GlbIndexStatusPtr,
        ICU_CHNL_ACTIVITY_STARTED_POS,ICU_CHNL_ACTIVITY_BIT_LENGTH)) && \
        ((IsrStatusFlag & (Ccu6ConfigEgde + 1U)) != 0U))
      #endif
      {
        /* [cover parentID={5A14FFF1-6908-4e7d-9895-15FA90FBB458}]
        Call the Timestamp ISR.
        [/cover] */
        Icu_lTimeStamp_Isr(CoreId,LocalIcuChanPtr,GlbIndexStatusPtr);
      }
      /* [cover parentID={860DB68D-58D9-4c1b-AAD4-55864A8BC09F}]
      If Safety enabled ?
      [/cover] */
      #if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
      else
      {
        /* [cover parentID={F1B3CCC5-2652-45db-9636-59423A793176}]
        Report Safety Error
        [/cover] */
        /* Safety Error */
        Mcal_ReportSafetyError(
            ICU_17_TIMERIP_MODULE_ID,
            ICU_17_TIMERIP_INSTANCE_ID,
            ICU_17_TIMERIP_SID_ISR,
            ICU_17_TIMERIP_E_INVALID_ISR);
      }
      #endif
      /* End of report to Safety */
      #endif
      /*(ICU_17_TIMERIP_TIMESTAMP_API == STD_ON)*/
      break;
    /* [cover parentID={308A068E-660C-4198-A7E8-CAC7583D7D60}]
    Is the mode of the channel Signal measurement ?
    [/cover] */
    default:/* CCU6 Signal Measure*/
      #if (ICU_17_TIMERIP_SIGNAL_MEASUREMENT_API ==STD_ON)
      /* [cover parentID={B8DD7590-2504-47be-A679-74D30ACB7CB9}]
      Check if activity started
      [/cover] */
      /* Check if the activity has started */
      #if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
      if ((ICU_ACTIVITY_STARTED ==
        Mcal_GetBitAtomic(*GlbIndexStatusPtr,
        ICU_CHNL_ACTIVITY_STARTED_POS,ICU_CHNL_ACTIVITY_BIT_LENGTH)) && \
        ((IsrStatusFlag & (Ccu6ConfigEgde + 1U)) != 0U))
      #endif
      {
        /* [cover parentID={4FCA3C30-1683-4cff-8026-1E5549F5206F}]
        Call the CCU specific signal measure ISR.
        [/cover] */
        Icu_lCcuSignalMeasure_Isr(CoreId, GlbIndexStatusPtr, LocalIcuChanPtr);
      }
      /* [cover parentID={9E027071-2200-433f-B372-08DD98B8A881}]
      If Safety enabled ?
      [/cover] */
      #if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
      else
      {
        /* [cover parentID={B7C6578F-3138-4fbe-85A2-260AEA77144F}]
        Report Safety Error
        [/cover] */
        /* Safety Error */
        Mcal_ReportSafetyError(
          ICU_17_TIMERIP_MODULE_ID,
          ICU_17_TIMERIP_INSTANCE_ID,
          ICU_17_TIMERIP_SID_ISR,
          ICU_17_TIMERIP_E_INVALID_ISR);
      }
      #endif
      /* End of report to Safety */
      #endif
      /*(ICU_17_TIMERIP_SIGNAL_MEASUREMENT_API == STD_ON)*/
      break;
  }
  /* Flags are cleared by McalLib */
}
#endif

#if (ICU_17_TIMERIP_GPT12_USED == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {9793AA2B-C5A6-4c68-8F85-E7DFDA269682}]     **
**                                                                            **
** Syntax:           LOCAL_INLINE void Icu_lGpt12_Isr(                        **
**                    const uint8 CoreChIndex)                                **
**                                                                            **
** Description :     This is Interrupt Routine Functions for the GPT12 lines  **
**                   lines. When interrupt occurs corresponding GPT12 line    **
**                   Service request will be invoked.                         **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  CoreChIndex - Core specific channel index                **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lGpt12_Isr(
  const uint8 CoreChIndex)
{
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr;
  #if (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON) || \
  (ICU_17_TIMERIP_INCREMENTAL_INTERFACE_API == STD_ON)
  uint32* GlbIndexStatusPtr;
  #endif
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * MISRA rule,To implement efficiently IcuMeasaurementProperty as a post-build
   * parameter.Union is required*/
  Icu_17_TimerIp_ChannelData* ChannelDataPtr;
  #if(ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
  const uint32 *CountPtr;
  uint16 CellUsed;
  #endif
  uint8 CoreId;
  uint8 ChIndex;
  /* Get core id which is executing currently */
  CoreId = (uint8)(Mcal_GetCpuIndex());
  /* Initialize ICU configured channel ROM pointer */
  LocalIcuChanPtr = &((Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->
                                                ChannelConfigPtr)[CoreChIndex]);
  /* Extract the mode specific index */
  ChIndex = LocalIcuChanPtr->ModeMappingIndex;
  #if (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON) || \
  (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON) || \
  (ICU_17_TIMERIP_INCREMENTAL_INTERFACE_API == STD_ON)
  /* Extract the address for the Global Index status */
  GlbIndexStatusPtr =
        &((Icu_17_TimerIp_Varlist[CoreId]->GlbIndexStatusBasePtr)[CoreChIndex]);
  #endif
  switch(LocalIcuChanPtr->IcuProperties.MeasurementMode)
  {
    case (uint32)ICU_17_TIMERIP_MODE_SIGNAL_EDGE_DETECT:
      /* [cover parentID={B965D907-DE73-492d-B981-7223EBBC8181}]
      If measurement mode is edge detect
      [/cover] */
      #if (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
      /* [cover parentID={E2B98AF2-95E0-4ca1-94B3-7A1499F3F210}]
      Is the GPT12 edge detection enabled?
      [/cover] */
      #if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
      if(1U == Mcal_GetBitAtomic(*GlbIndexStatusPtr,
                                 ICU_CHNL_ERU_GPT_SIGEDGE_STATUS_POS, \
                                 ICU_CHNL_ERU_GPT_SIGEDGE_STATUS_BIT_LENGTH))
      #endif
      {
        CellUsed =
          (uint16)LocalIcuChanPtr->IcuProperties.AssignedHwUnitNumber;
        /* Extract the pointer which store the offset edge count */
        ChannelDataPtr =
              &((Icu_17_TimerIp_Varlist[CoreId]->ChannelDataBasePtr)[ChIndex]);
        CountPtr = &(ChannelDataPtr->EdgeDetectParas.EdgeDetectCount);
        /* reload the timer counter */
        /* [cover parentID={4065BA9B-861A-4aa6-BF62-5D1A518F3483}]
        Call GPT12 edge detection ISR
        [/cover] */
        Icu_lGpt12EdgeDetectIsr(CellUsed, (uint16)*CountPtr);
        /* Edge notification/wakeup should only be invoked if the counter is
        non-zero indicating the ISR is used.*/
        /* [cover parentID={5990FC2C-E96E-4592-8D2C-9305E87666ED}]
        Is the offset counter non-zero?
        [/cover] */
        if((uint16)0 != *CountPtr)
        {
          /* [cover parentID={D54600A2-7F37-4d66-AA83-229E0580958F}]
          Call signal edge notification ISR
          [/cover] */
          Icu_lSignalEdgeNotification_Isr(CoreId, LocalIcuChanPtr,
                                          GlbIndexStatusPtr);
        }
        else
        {
          /* Set channel status to active to indicate Getinput state */
          /* [cover parentID={B395947B-9F53-4a96-BD5C-8F27D1490273}]
          Set channel status to active to indicate get input state.
          [/cover] */
          Mcal_SetBitAtomic(GlbIndexStatusPtr, (sint32)ICU_CHNL_STATUS_POS, \
            ICU_CHNL_STATUS_BIT_LENGTH, \
            (uint32 )ICU_17_TIMERIP_ACTIVE);
        }
      }
      /* [cover parentID={92ADABDC-858B-45b6-834C-FF7F69C6D56F}]
      If Safety is enabled
      [/cover] */
      #if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
      else
      {
        /* Safety Error */
        /* [cover parentID={088C992B-FA85-4019-9656-9FA9D863E766}]
        Report safety error indicating an invalid ISR.
        [/cover] */
        Mcal_ReportSafetyError(
          ICU_17_TIMERIP_MODULE_ID,
          ICU_17_TIMERIP_INSTANCE_ID,
          ICU_17_TIMERIP_SID_ISR,
          ICU_17_TIMERIP_E_INVALID_ISR);
      }
      #endif
      /* End of report to Safety */
      #endif
      break;
    case (uint32) ICU_17_TIMERIP_MODE_INCREMENTAL_INTERFACE:
#if (ICU_17_TIMERIP_INCREMENTAL_INTERFACE_API == STD_ON)
      /* [cover parentID={7C5E05B2-6D5A-4bb4-A964-3CAFED7DC35D}]
      If Safety is enabled
      [/cover] */
#if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
      /* [cover parentID={D4E0F2CB-5DF6-41bd-81F8-4D027B334A9F}]
      Is the channel activity started?
      [/cover] */
      if (ICU_ACTIVITY_STARTED
          == Mcal_GetBitAtomic(*GlbIndexStatusPtr,
              ICU_CHNL_ACTIVITY_STARTED_POS, ICU_CHNL_ACTIVITY_BIT_LENGTH))
#endif
      {
        if ((ICU_ENABLE_NOTIFICATION
        == Mcal_GetBitAtomic(*GlbIndexStatusPtr, ICU_CHNL_NOTIF_PRESENCE_POS,
        ICU_CHNL_NOTIF_BIT_LENGTH)))
        {
          /* [cover parentID={4207973E-1C2C-48d6-BA75-2F9A7DB92314}]
          Call Incremental Interface ISR
          [/cover] */
          Icu_lGpt12IncrementalInterfaceIsr(LocalIcuChanPtr);
        }
      }
#if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
      else
      {
        /* [cover parentID={FFC2D4D6-488B-4fba-A00B-C06669B9379B}]
        Report safety error indicating an invalid ISR.
        [/cover] */
        /* Safety Error */
        Mcal_ReportSafetyError(
        ICU_17_TIMERIP_MODULE_ID,
        ICU_17_TIMERIP_INSTANCE_ID,
        ICU_17_TIMERIP_SID_ISR,
        ICU_17_TIMERIP_E_INVALID_ISR);
      }
#endif
#endif
      break;
    /* [cover parentID={65F12CA7-A396-4d91-A689-1C6C21E199C7}]
    If measurement mode is edge counter
    [/cover] */
    default:
      /* [cover parentID={66B75845-AF65-439a-8855-9DB261C04AA1}]
      Is the channel activity started?
      [/cover] */
      /* Check if the activity has started */
      #if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
      if (ICU_ACTIVITY_STARTED ==
          Mcal_GetBitAtomic(*GlbIndexStatusPtr,
                   ICU_CHNL_ACTIVITY_STARTED_POS, ICU_CHNL_ACTIVITY_BIT_LENGTH))
      #endif
      {
        /* Extract the pointer which store the offset edge count */
        ChannelDataPtr =
              &((Icu_17_TimerIp_Varlist[CoreId]->ChannelDataBasePtr)[ChIndex]);
        /* [cover parentID={4A5C4556-AF08-4b33-89BA-A4D9D8EBEEA4}]
        Add 16-bit value to indicate a Tx overflow as timer is a 16 bit timer
        [/cover] */
        /* Add 16-bit value to indicate Tx overflow as timer is 16 bit timer */
        ChannelDataPtr->EdgeCountParas.EdgeCounter = \
            ChannelDataPtr->EdgeCountParas.EdgeCounter + ICU_GPT12_OVFL_OFFSET;
      }
      /* [cover parentID={F27CACC6-FE34-4d86-958F-FD1A9811F9F3}]
      If Safety is enabled
      [/cover] */
      #if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
      else
      {
        /* [cover parentID={80F95A9B-3B2C-4e30-A71A-030C8B92C28A}]
        Report safety error indicating an invalid ISR.
        [/cover] */
        /* Safety Error */
        Mcal_ReportSafetyError(
          ICU_17_TIMERIP_MODULE_ID,
          ICU_17_TIMERIP_INSTANCE_ID,
          ICU_17_TIMERIP_SID_ISR,
          ICU_17_TIMERIP_E_INVALID_ISR);
      }
      #endif
      /* End of report to Safety */
      break;
  }
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer GlbIndexStatusPtr is
   * accessed modified in the invoked local function */
}
#endif

#if (ICU_17_TIMERIP_ERU_SIGEDGE_USED == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={0FA39C4C-6C5F-414e-9555-EFE32D9EE3E2}]      **
**                                                                            **
** Syntax:           LOCAL_INLINE void Icu_lEru_Isr(                          **
**                    const uint8 CoreChIndex)                                **
**                                                                            **
** Description :     This is Interrupt Routine Functions for the ERUlines     **
**                   lines. When interrupt occurs corresponding ERU line      **
**                   Service request will be invoked.                         **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  CoreChIndex - Core specific channel index                **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lEru_Isr(
  const uint8 CoreChIndex)
{
  const Icu_17_TimerIp_ChannelConfigType *LocalIcuChanPtr;
  uint32* GlbIndexStatusPtr;
  uint8 CoreId;

  /* Get core id which is executing currently */
  CoreId = (uint8)(Mcal_GetCpuIndex());

  /* Initialize ICU configured channel ROM pointer */
  LocalIcuChanPtr = &((Icu_17_TimerIp_ConfigPtr->CoreConfig[CoreId]->
                                                ChannelConfigPtr)[CoreChIndex]);
  /* Extract the address for the Global Index status */
  GlbIndexStatusPtr =
        &((Icu_17_TimerIp_Varlist[CoreId]->GlbIndexStatusBasePtr)[CoreChIndex]);
  /* [cover parentID={9841D2C8-E767-402f-8525-4F75FD8C9BB7}]
   Signal edge notification
   [/cover] */
  Icu_lSignalEdgeNotification_Isr(CoreId, LocalIcuChanPtr, GlbIndexStatusPtr);
}/* End of function Icu_lEru_Isr */
#endif
/* end of #if ICU_17_TIMERIP_ERU_SIGEDGE_USED */

#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) && \
(ICU_17_TIMERIP_SIGNAL_MEASUREMENT_API ==STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {86E113D3-C43E-45a8-BBB9-6D38A56E104B}]     **
**                                                                            **
** Syntax : LOCAL_INLINE void Icu_lGtmSignalMeasureIsr(                       **
**                  const Icu_17_TimerIp_ChannelConfigType *const IcuChanPtr, **
**                                         uint32* const GlbIndexStatusPtr)   **
**                                                                            **
** Description :     GTM TIM Signal Measure ISR to identify overflow of       **
**                    counter in case of measured value larger than 24 bit.   **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  IcuChanPtr - Channel configuration pointer               **
**                   GlbIndexStatusPtr - Pointer to the channel flags         **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
/*For HIGH TIME and LOW TIME measurement:
Overflow interrupt on a inactive phase can be ignored. But on an active phase
it will be considered and subsequent NEWVAL interrupt is enabled to clear the
NEWVAL status.

In the process it is possible that the Overflow interrupt happened on an
inactive phase and the ISR is executed on active phase. To identify this case,
CNTS value is checked against the threshold and if within threshold a flag is
set to indicate in the next NEWVAL interrupt.
Nonetheless the NEWVAL interrupt is enabled and in NEWVAL ISR, overflow flag
and the flag will be checked to identify any overflow of active phase.

In the other situation, where the overflow happened on an active phase but ISR
is executed on Inactive phase, GPR1 Value is checked. If the GPR1 value is
within threshold, the previously measured active phase value has overflowed and
the channel status is reset. But still the interrupt is enabled on OVERFLOW.
*/
LOCAL_INLINE void Icu_lGtmSignalMeasureIsr(
  const Icu_17_TimerIp_ChannelConfigType *const IcuChanPtr,
  uint32* const GlbIndexStatusPtr)
{
  Ifx_GTM_TIM_CH *TimChannelRegPtr; /* Pointer to TIM Channel Reg    */
  uint32 NotifyValue;
  uint32 ECNTVal;
  uint32 CNTSVal;
  uint32 GPRVal;
  uint32 OVFLFlagStatus;
  uint16 CellNum;
  uint8 ChannelNumber;
  uint8 ModuleNo;

  CellNum = (uint16) (IcuChanPtr->IcuProperties.AssignedHwUnitNumber);
  ChannelNumber = (uint8) (CellNum % ICU_GTM_CHANNELS_PER_TIM_MODULE);
  ModuleNo = (uint8) (CellNum / ICU_GTM_CHANNELS_PER_TIM_MODULE);

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TimChannelRegPtr = GTM_TIM_CH_POINTER(ModuleNo, ChannelNumber);
  /* Check if the activity has started */
  /* [cover parentID={A9AF2F08-BD17-476b-AECF-E394A60ECF76}]
  Is the channel activity started?
  [/cover] */
  if (ICU_ACTIVITY_STARTED
      == Mcal_GetBitAtomic(*GlbIndexStatusPtr, ICU_CHNL_ACTIVITY_STARTED_POS,
                           ICU_CHNL_ACTIVITY_BIT_LENGTH))
  {
    /* [cover parentID={F02F689F-0E45-42b3-9695-FAE6C41F46E1}]
    If TIM channel counter overflow IRQ is enabled
    [/cover] */
    if (1U == TimChannelRegPtr->IRQ.EN.B.CNTOFL_IRQ_EN)
    {
      /* Read and clear newval flag */
      /* MISRA2012_RULE_11_8_JUSTIFICATION: SFR access. Since the input
       * argument for the API discards volatile keyword. No side effects foreseen
       * by violating this MISRA rule*/
      NotifyValue = Mcal_Swap(&(TimChannelRegPtr->IRQ.NOTIFY.U), \
                              ICU_GTM_NEWVAL_FLAG_SET, ICU_SWAP_32BIT_MASK);
      /* [cover parentID={0C795594-8A99-491f-A76E-39F6D96D8D4E}]
      If a newval was detected
      [/cover] */
      if (1U == (NotifyValue & 1U))
      {

        /* Set a flag to indicate for GetInputState */
        /* [cover parentID={9AE7A0A7-7890-48fb-AB2C-910F249DEF98}]
        Set a flag to indicate for GetInputState
        [/cover] */
        Mcal_SetBitAtomic(GlbIndexStatusPtr, (sint32)ICU_CHNL_STATUS_POS, \
                          ICU_CHNL_STATUS_BIT_LENGTH,
                          (uint32 )ICU_17_TIMERIP_ACTIVE);
        /* [cover parentID={59BC9FF0-1CF2-4518-8899-C21DA3A89F74}]
        Set a flag to indicate for GetTimeElapsed and GetDuty
        [/cover] */
        /* Set a flag to indicate for GetTimeElapsed and GetDuty */
        Mcal_SetBitAtomic(GlbIndexStatusPtr,
                          (sint32)ICU_SIGNALMESURE_INPUT_STAT_POS,
                          ICU_SIGNALMESURE_INPUT_STAT_LENGTH,
                          (uint32)ICU_ACTIVITY_STARTED);
      }
      /* [cover parentID={CC73AD53-176E-4481-972D-1B9D2887674F}]
      Is HIGH/LOW time measurement needed?
      [/cover] */
      if(((uint32)IcuChanPtr->IcuProperties.MeasurementProperty ==
          (uint32)ICU_17_TIMERIP_HIGH_TIME) ||
          ((uint32)IcuChanPtr->IcuProperties.MeasurementProperty ==
           (uint32)ICU_17_TIMERIP_LOW_TIME))
      {
        ECNTVal = TimChannelRegPtr->ECNT.U;
        CNTSVal = TimChannelRegPtr->CNTS.U;
        GPRVal = TimChannelRegPtr->GPR1.U;
        GPRVal = GPRVal & ICU_GTM_TIMER_MASK;
        CNTSVal = CNTSVal & ICU_GTM_TIMER_MASK;
        /* [cover parentID={2A2AABD5-DF33-4fe0-83B4-EB07E68A7FC9}]
        Is the current level of input signal active phase?
        [/cover] */
        if((ECNTVal & 1U) != (uint32)IcuChanPtr->IcuProperties.DefaultStartEdge)
        {
          /* overflow ISR executing on inactive phase */
          /* check if the last edge is within threshold */
          /* [cover parentID={0D574140-D468-4f4c-AD91-9D612ED5F1BC}]
          Is GPR1 Value with in threshold?
          [/cover] */
          if(GPRVal < IcuChanPtr->IcuProperties.OverflowISRThreshold)
          {
            /* [cover parentID={59695920-9E06-435e-8A2C-3684B0B81A98}]
            Clear the channel status as the overflow happened during active
            phase but the ISR is invoked on inactive phase.
            [/cover] */
            /* overflow happened on active phase but ISR is invoked on inactive
              phase */
            /* Last measured value is not valid */
            /* Re-Set a flag to indicate for GetInputState */
            Mcal_SetBitAtomic(GlbIndexStatusPtr, (sint32)ICU_CHNL_STATUS_POS, \
                              ICU_CHNL_STATUS_BIT_LENGTH,
                              (uint32 )ICU_17_TIMERIP_IDLE);
            /* [cover parentID={93743960-4C1F-46d3-863E-0083DF039D46}]
            Re-Set a flag to indicate for GetTimeElapsed and GetDuty
            [/cover] */
            /* Re-Set a flag to indicate for GetTimeElapsed and GetDuty */
            Mcal_SetBitAtomic(GlbIndexStatusPtr,
                              (sint32)ICU_SIGNALMESURE_INPUT_STAT_POS, \
                              ICU_SIGNALMESURE_INPUT_STAT_LENGTH, (uint32 )0U);
          }
          else
          {
            /* No action required as overflow happened on inactive phase and
               the old measured value is still valid.*/
          }
        }
        else
        {
          /* overflow ISR executing on active phase */
          /* [cover parentID={AB4773E1-6722-43d1-9CCA-7368B1CB2769}]
          Is CNTS Value with in threshold?
          [/cover] */
          if (CNTSVal >= IcuChanPtr->IcuProperties.OverflowISRThreshold)
          {
            /* Overflow is due to active phase. */
            /* Set a flag to identify that the active phase is not valid */
            /* [cover parentID={6AD36D45-4314-4cde-AC35-3105801C9FEC}]
            Set a flag to indicate a valid overflow
            [/cover] */
            Mcal_SetBitAtomic(GlbIndexStatusPtr, (sint32)ICU_OVFL_ISR_STAT_POS,
                              ICU_OVFL_ISR_STAT_LENGTH,
                              (uint32 )ICU_SET_BIT);
          }
          /* [cover parentID={5BFEB614-A3DD-42e0-80D4-23072E49E990}]
          reset the counter overflow interrupt enable and set newval interrupt
          enable
          [/cover] */
          /* Enable the NEW VAL interrupt to clear the channel status */
          TimChannelRegPtr->IRQ.EN.B.CNTOFL_IRQ_EN = 0U;
          TimChannelRegPtr->IRQ.EN.B.NEWVAL_IRQ_EN = 1U;
        }
      }
      else
      {
        /* [cover parentID={08921F1F-6F03-438c-B307-B5227DB424FA}]
        reset the counter overflow interrupt enable and set newval interrupt
        enable
        [/cover] */
        TimChannelRegPtr->IRQ.EN.B.CNTOFL_IRQ_EN = 0U;
        TimChannelRegPtr->IRQ.EN.B.NEWVAL_IRQ_EN = 1U;
      }
    }
    else
    {
      /* [cover parentID={FF33E8CE-13C3-486d-ACE6-A9D72B9AC9D8}]
      Is HIGH/LOW time measurement needed?
      [/cover] */
      if(((uint32)IcuChanPtr->IcuProperties.MeasurementProperty ==
          (uint32)ICU_17_TIMERIP_HIGH_TIME) ||
          ((uint32)IcuChanPtr->IcuProperties.MeasurementProperty ==
           (uint32)ICU_17_TIMERIP_LOW_TIME))
      {
        /* Read and clear CNTOFL flag */
        /* MISRA2012_RULE_11_8_JUSTIFICATION: SFR access. Since the input
         * argument for the API discards volatile keyword. No side effects foreseen
         * by violating this MISRA rule*/
        NotifyValue = Mcal_Swap(&(TimChannelRegPtr->IRQ.NOTIFY.U), \
                                ICU_GTM_CNTOVFL_FLAG_SET, ICU_SWAP_32BIT_MASK);
        OVFLFlagStatus = Mcal_GetBitAtomic(*GlbIndexStatusPtr,
                      (sint32)ICU_OVFL_ISR_STAT_POS, ICU_OVFL_ISR_STAT_LENGTH);
        /* [cover parentID={B0DB91AF-39C1-4134-BD9B-2DEC074CA92B}]
        Is overflow flag set or the flag to indicate overflow of active phase
        is set?
        [/cover] */
        if((ICU_GTM_CNTOVFL_FLAG_SET ==
            (NotifyValue & ICU_GTM_CNTOVFL_FLAG_SET)) ||
            (OVFLFlagStatus == (uint32 )ICU_SET_BIT))
        {
          /*
            Re-Set channel status flag to indicate for GetInputState
          */
          /* Re-Set a flag to indicate for GetInputState */
          Mcal_SetBitAtomic(GlbIndexStatusPtr, (sint32)ICU_CHNL_STATUS_POS, \
                            ICU_CHNL_STATUS_BIT_LENGTH,
                            (uint32 )ICU_17_TIMERIP_IDLE);
          /*
          Re-Set a flag to indicate for GetTimeElapsed and GetDuty
          */
          /* Re-Set a flag to indicate for GetTimeElapsed and GetDuty */
          Mcal_SetBitAtomic(GlbIndexStatusPtr,
                            (sint32)ICU_SIGNALMESURE_INPUT_STAT_POS, \
                            ICU_SIGNALMESURE_INPUT_STAT_LENGTH, (uint32 )0U);
          /* Re-Set a flag to identify that the active phase is not valid */
          Mcal_SetBitAtomic(GlbIndexStatusPtr, (sint32)ICU_OVFL_ISR_STAT_POS, \
                            ICU_OVFL_ISR_STAT_LENGTH,
                            (uint32 )0UL);
        }
      }
      else
      {
        /* [cover parentID={8CA1268E-E642-441f-8D3B-DA01011BB654}]
        Re-Set channel status flag to indicate for GetInputState
        [/cover] */
        /* Re-Set a flag to indicate for GetInputState */
        Mcal_SetBitAtomic(GlbIndexStatusPtr, (sint32)ICU_CHNL_STATUS_POS, \
                          ICU_CHNL_STATUS_BIT_LENGTH,
                          (uint32 )ICU_17_TIMERIP_IDLE);
        /* [cover parentID={93743960-4C1F-46d3-863E-0083DF039D46}]
        Re-Set a flag to indicate for GetTimeElapsed and GetDuty
        [/cover] */
        /* Re-Set a flag to indicate for GetTimeElapsed and GetDuty */
        Mcal_SetBitAtomic(GlbIndexStatusPtr,
                          (sint32)ICU_SIGNALMESURE_INPUT_STAT_POS, \
                          ICU_SIGNALMESURE_INPUT_STAT_LENGTH, (uint32 )0U);
      }
      /* [cover parentID={4579BC77-1A33-4f8f-B742-55F2E99070BF}]
      Clear Newval irq and enable counter overflow irq
      [/cover] */
      /* Clear Newval irq and enable cntofl irq */
      TimChannelRegPtr->IRQ.EN.B.NEWVAL_IRQ_EN = 0U;
      TimChannelRegPtr->IRQ.EN.B.CNTOFL_IRQ_EN = 1U;
    }
  }
  /* [cover parentID={57E06A77-94A9-4682-B70F-BFFCD86BA717}]
  If Safety is enabled
  [/cover] */
  #if(ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  else
  {
    /* Safety Error */
    /* [cover parentID={CC0DA5D5-4206-48ed-9664-BE547E126A61}]
    Report a safety error to indicate invalid isr.
    [/cover] */
    Mcal_ReportSafetyError(
      ICU_17_TIMERIP_MODULE_ID,
      ICU_17_TIMERIP_INSTANCE_ID,
      ICU_17_TIMERIP_SID_ISR,
      ICU_17_TIMERIP_E_INVALID_ISR);
  }
  #endif
  /* End of report to Safety */
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer GlbIndexStatusPtr is
   * accessed using assembly instruction. */
}
#endif

#if (ICU_17_TIMERIP_GTM_TIM_USED == STD_ON) && \
(ICU_17_TIMERIP_EDGE_COUNT_API ==STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={232DFC47-E3AE-4d61-8815-B53F12305450}]      **
**                                                                            **
** Syntax : LOCAL_INLINE void Icu_lGtmEdgeCountIsr(const uint8 ChIndex,       **
**                                         const uint8 CoreId,                **
**                                   const uint32* const GlbIndexStatusPtr)   **
**                                                                            **
** Description :     GTM TIM Edge Count  ISR to identify overflow of          **
**                    counter in case of measured value larger than 24 bit.   **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  ChIndex - TIM Channel Index                              **
**                   CoreId - Core Id Index                                   **
**                   GlbIndexStatusPtr - Pointer to the channel flags         **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lGtmEdgeCountIsr(
  const uint8 ChIndex,
  const uint8 CoreId,
  const uint32* const GlbIndexStatusPtr)
{

  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * MISRA rule.To implement efficiently IcuMeasaurementProperty as a post-build
   * parameter Union is required*/
  Icu_17_TimerIp_ChannelData* ChannelDataPtr;
  uint32 GlbIndexChStatus;

  GlbIndexChStatus = *GlbIndexStatusPtr;
  GlbIndexChStatus = GlbIndexChStatus \
                   & (((ICU_ACTIVITY_STARTED << ICU_CHNL_ACTIVITY_STARTED_POS) \
                         | ((uint32) (ICU_RSTEDCNT_ACTIVITY_STARTED) \
                            << ICU_CHNL_RSTEDGE_STAT_POS)));
  /* Check if the activity has started */
  /* [cover parentID={CE8A1E4C-B1C4-44b0-809E-CA886461E29A}]
  Is activity started and Reset activity not in progress?
  [/cover] */
  if (GlbIndexChStatus == (uint32) \
      (((uint32)ICU_ACTIVITY_STARTED << ICU_CHNL_ACTIVITY_STARTED_POS)))
  {
    /* Extract the pointer which store the offset edge count */
    ChannelDataPtr =
              &((Icu_17_TimerIp_Varlist[CoreId]->ChannelDataBasePtr)[ChIndex]);
    /* Add 24-bit value to indicate a CNTOFL as CNT is a 24 bit timer */
    /* [cover parentID={1C25117A-6C4C-4e17-A008-4BBA37E76A0D}]
    Increment the Edge counter variable by a 24bit value(0x1000000U)
    [/cover] */
    ChannelDataPtr->EdgeCountParas.EdgeCounter = \
        ChannelDataPtr->EdgeCountParas.EdgeCounter + ICU_TIM_CNTOFL_OFFSET;
  }
  /* [cover parentID={526EF902-2F6C-479b-B7E5-1EBDEC0ADED1}]
  Safety error reporting enabled
  [/cover] */
  #if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  /* Get channel avtivity status */
  GlbIndexChStatus = (Mcal_GetBitAtomic(*GlbIndexStatusPtr,
                  ICU_CHNL_ACTIVITY_STARTED_POS, ICU_CHNL_ACTIVITY_BIT_LENGTH));
  /* Report safety error if channel is not active*/
  /* [cover parentID={AE22D6F7-E2C0-45fc-B136-7D51D93E82AE}]
  Is the channel activity started?
  [/cover] */
  if (GlbIndexChStatus == 0U)
  {
    /* [cover parentID={80E7A354-66BD-420c-AB24-0F6202A731DB}]
    Report Safety Error
    [/cover] */
    /* Safety Error */
    Mcal_ReportSafetyError(
      ICU_17_TIMERIP_MODULE_ID,
      ICU_17_TIMERIP_INSTANCE_ID,
      ICU_17_TIMERIP_SID_ISR,
      ICU_17_TIMERIP_E_INVALID_ISR);
  }
  #endif
  /* End of report to Safety */
}
#endif
#if (ICU_17_TIMERIP_SIGNAL_MEASUREMENT_API ==STD_ON) && \
(ICU_17_TIMERIP_CCU6_USED ==STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {340B1EC4-F787-43a8-90E2-1D3103EF2A52}]     **
**                                                                            **
** Syntax : LOCAL_INLINE void Icu_lCcuSignalMeasure_Isr(const uint8 CoreId,   **
**                                uint32* const GlbIndexStatusPtr,            **
**           const Icu_17_TimerIp_ChannelConfigType *const LocalIcuChanPtr)   **
**                                                                            **
** Description :     CCU6 Signal Measure ISR to calculate the requested value.**
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  CoreId - Core from which this function is called.        **
**                   LocalIcuChanPtr - Pointer to the Channel configuration   **
**                                                                            **
** Parameters (in-out): GlbIndexStatusPtr - Pointer to the channel flags      **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lCcuSignalMeasure_Isr(
  const uint8 CoreId,
  uint32* const GlbIndexStatusPtr,
  const Icu_17_TimerIp_ChannelConfigType *const LocalIcuChanPtr)
{
  uint16 CellUsed;
  uint32 SigKind = 0U;
  uint32 CfgEdge;
  uint16 CcuSrRegVal;
  uint16 CcuRRegVal;
  uint16 CcuDutyRegVal;
  uint16 CcuPeriodRegVal;
  uint32 CcuActiveTime;
  uint32 CcuPeriod;
  uint8 ChIndex;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * MISRA rule,To implement efficiently IcuMeasaurementProperty as a post-build
   * parameter.Union is required*/
  Icu_17_TimerIp_ChannelData* ChannelDataPtr;
  volatile Ifx_CCU6 *Ccu6RegPtr; /* Variable to hold the current CCU6 address */
  /* MISRA2012_RULE_19_2_JUSTIFICATION: Union based type defintion for SFR
     access. */
  volatile Ifx_CCU6_CC6SR *CcuSrRegPtr; /* Pointer to SR registers of CCU */
  volatile Ifx_CCU6_CC6R *CcuRRegPtr; /* Pointer to R registers of CCU */
  uint8 CcChannelNumber;    /* To hold the CC channel number */
  /* Extract the actual cell number */
  CellUsed = (uint16)LocalIcuChanPtr->IcuProperties.AssignedHwUnitNumber;
  /* Get the base address of the Kernel */
  Ccu6RegPtr = &((&MODULE_CCU60)[CellUsed & ICU_CCU_GET_KERNEL]);
  /* The signal measure property is retrieved here */
  SigKind =  LocalIcuChanPtr->IcuProperties.MeasurementProperty;
  CfgEdge =  (uint32)(Mcal_GetBitAtomic(*GlbIndexStatusPtr, \
                                  ICU_CHNL_EDGE_POS, ICU_CHNL_EDGE_BIT_LENGTH));
  /* Upper Nibble of AssignedHwUnitNumber holds the Channel Number */
  CcChannelNumber = ((uint8)(CellUsed & ICU_CCU_GET_COMPARATOR) >> \
                     ICU_BRING_TO_BIT_0);
  /* Assign SR and R register base addresses */
  CcuSrRegPtr = &(Ccu6RegPtr->CC6SR[0]);
  CcuRRegPtr = &(Ccu6RegPtr->CC6R[0]);
  /* Read SR and R register values */
  CcuSrRegVal = (uint16)CcuSrRegPtr[CcChannelNumber].U;
  CcuRRegVal = (uint16)CcuRRegPtr[CcChannelNumber].U;

  {
    /* Mode specific channel Identifier */
    ChIndex = LocalIcuChanPtr->ModeMappingIndex;
    /* Store the address in a pointer variable */
    ChannelDataPtr =
              &((Icu_17_TimerIp_Varlist[CoreId]->ChannelDataBasePtr)[ChIndex]);
    switch(SigKind)
    {
      /* [cover parentID={14D814BD-FD98-4348-BCB6-CEFA21760829}]
      If signal measuer property is low time
      [/cover] */
      case (uint32)ICU_17_TIMERIP_LOW_TIME:
        /* [cover parentID={024CC7D2-2BB9-4f3b-BCD1-BD4F73499C6F}]
        Are the read SR and R values non zero?
        [/cover] */
        if((CcuRRegVal != 0U) && (CcuSrRegVal != 0U))
        {
          /* Calculate LOW Time */
          /* [cover parentID={500ACF26-B9EB-42e4-8E29-66186BEB26F1}]
          Calculate and update low time
          [/cover] */
          ChannelDataPtr->SigMeasureParasCcu6.ActiveTime =
            Icu_lCcuSubtractWithOverflow(CcuRRegVal, CcuSrRegVal);
          /* Set a flag to indicate for GetInputState */
          /* [cover parentID={D37232D7-AAFC-4a49-BA65-5EC79DC3EBE4}]
          Set a flag to indicate for GetInputState
          [/cover] */
          Mcal_SetBitAtomic( \
                             GlbIndexStatusPtr, (sint32)ICU_CHNL_STATUS_POS, \
                             1, (uint32)ICU_17_TIMERIP_ACTIVE);
        }
        break;
      /* [cover parentID={1358F289-E274-4d04-A6BE-FA94EACCCFD6}]
      If signal measure property is high time
      [/cover] */
      case (uint32)ICU_17_TIMERIP_HIGH_TIME:
        /* [cover parentID={3C83B5E7-37FD-4d61-8D3D-82BEFA4F6B08}]
        Are the read SR and R values non zero?
        [/cover] */
        if((CcuRRegVal != 0U) && (CcuSrRegVal != 0U))
        {
          /* Calculate HIGH Time */
          /* [cover parentID={EDB95A74-5E17-4f79-A2E4-4B3955C4746A}]
           Calculate and update HIGH Time
           [/cover] */
          ChannelDataPtr->SigMeasureParasCcu6.ActiveTime = \
              Icu_lCcuSubtractWithOverflow(CcuSrRegVal, CcuRRegVal);
          /* Set a flag to indicate for GetInputState */
          /* [cover parentID={41E7BFFD-2C9D-4356-A184-E9C65B789BC7}]
           Set a flag to indicate for GetInputState
           [/cover] */
          Mcal_SetBitAtomic(GlbIndexStatusPtr, (sint32)ICU_CHNL_STATUS_POS, \
                            ICU_CHNL_STATUS_BIT_LENGTH, \
                            (uint32 )ICU_17_TIMERIP_ACTIVE);
        }
        break;
      /* [cover parentID={D586A0F2-3C7E-4ebe-A255-46713F709A62}]
      If signal measure property is duty cycle
      [/cover] */
      case (uint32)ICU_17_TIMERIP_DUTY_CYCLE:
        /* Identify the Active edge time stamp for calculations */
        if(CfgEdge == (uint32)ICU_17_TIMERIP_FALLING_EDGE)
        {
          CcuDutyRegVal = CcuRRegVal;
          CcuPeriodRegVal = CcuSrRegVal;
        }
        else /*if(CfgEdge == ICU_17_TIMERIP_RISING_EDGE)*/
        {
          CcuDutyRegVal = CcuSrRegVal;
          CcuPeriodRegVal = CcuRRegVal;
        }
        /* [cover parentID={6988A298-5C02-4c81-A6DD-9DD326511903}]
        Is the first edge falg set?
        [/cover] */
        if(ChannelDataPtr->SigMeasureParasCcu6.FirstEdgeFlag == 0U)
        {
          ChannelDataPtr->SigMeasureParasCcu6.RegValue = CcuPeriodRegVal;
          ChannelDataPtr->SigMeasureParasCcu6.FirstEdgeFlag = 1U;
          /* [cover parentID={AC6CDF2B-0C4F-4bc8-A800-E5818CB26350}]
          Is the edge configured both edges?
          [/cover] */
          if(CfgEdge == (uint32)ICU_17_TIMERIP_BOTH_EDGES)
          {
            if(CcuSrRegVal != 0U)
            {
              ChannelDataPtr->SigMeasureParasCcu6.RegValue = CcuSrRegVal;
              Mcal_SetBitAtomic(GlbIndexStatusPtr, ICU_CHNL_EDGE_POS,
                ICU_CHNL_EDGE_BIT_LENGTH, (uint32 )ICU_17_TIMERIP_FALLING_EDGE);
              Mcal_SetBitAtomic((&Ccu6RegPtr->IEN.U),
                                (CcChannelNumber * ICU_CCU_IS_BITS_PER_CHANNEL),
                                ICU_CCU_IS_BITS_PER_CHANNEL,
                                (uint32)ICU_CCU_FALLING_EDGE);
            }
            else
            {
              ChannelDataPtr->SigMeasureParasCcu6.RegValue = CcuRRegVal;
              Mcal_SetBitAtomic(GlbIndexStatusPtr, ICU_CHNL_EDGE_POS,
                 ICU_CHNL_EDGE_BIT_LENGTH, (uint32 )ICU_17_TIMERIP_RISING_EDGE);
              Mcal_SetBitAtomic((&Ccu6RegPtr->IEN.U),
                                (CcChannelNumber * ICU_CCU_IS_BITS_PER_CHANNEL),
                                ICU_CCU_IS_BITS_PER_CHANNEL,
                                (uint32)ICU_CCU_RISING_EDGE);
            }
          }
        }
        else
        {
          /* [cover parentID={68D37282-91B5-4096-BFFC-E35CB4818BE3}]
          Calculate and update active time and period
          [/cover] */
          /* Calculate Active Time and period */
          CcuActiveTime = (uint16)Icu_lCcuSubtractWithOverflow(CcuDutyRegVal,
                          (uint16)ChannelDataPtr->SigMeasureParasCcu6.RegValue);
          CcuPeriod = (uint16)Icu_lCcuSubtractWithOverflow( CcuPeriodRegVal,
                          (uint16)ChannelDataPtr->SigMeasureParasCcu6.RegValue);
          ChannelDataPtr->SigMeasureParasCcu6.ActiveTime = \
                      (uint32)((CcuActiveTime << ICU_CCU6_ACTIVETIME_OFFSET) |
                      (CcuPeriod));
          /* [cover parentID={70D74B42-3137-4db2-A7BB-9C3D014F643E}]
          Set a flag to indicate for GetInputState
          [/cover] */
          /* Set a flag to indicate for GetInputState */
          Mcal_SetBitAtomic( GlbIndexStatusPtr, (sint32)ICU_CHNL_STATUS_POS, \
                     ICU_CHNL_STATUS_BIT_LENGTH, (uint32)ICU_17_TIMERIP_ACTIVE);
          /* [cover parentID={CF196358-EA87-4e49-B22F-6424DCA2F9F3}]
          Store period time stamp for next edge
          [/cover] */
          ChannelDataPtr->SigMeasureParasCcu6.RegValue = CcuPeriodRegVal;
        }
        break;
      default:
        /* Interrupt is not expected. Possible safety error. */
        break;
    }
  }
  /* MISRA2012_RULE_2_7_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the variable GlbIndexStatusPtr is
   * accessed using assembly instruction. */
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer GlbIndexStatusPtr is
   * accessed using assembly instruction. */
}
#endif
/*(ICU_17_TIMERIP_CCU6_USED == STD_ON)*/

#if (ICU_17_TIMERIP_GPT12_USED == STD_ON) && \
(ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {086DF1C8-FBE0-45a4-AFBC-99517FB57969}]     **
**                                                                            **
** Syntax : static void Icu_lGpt12EdgeDetectIsr(                              **
**                            const uint16 GlobalChannelNumber,               **
**                            const uint16 Count  )                           **
**                                                                            **
** Description :     Function to service the GPT12 edge detect ISR            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel                          **
**                                                                            **
** Parameters (in):  GlobalChannelNumber - GPT12 channel number               **
**                   Count - Multiedge count, will be "1" for a normal edge   **
**                   detect channel.                                          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lGpt12EdgeDetectIsr(
  const uint16 GlobalChannelNumber, const uint16 Count)
{
  uint8 ChannelNo;                              /* Holds the GPT12 Tx Number  */
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
    MISRA rule. Union usage is required to access SFR data type and implement
    efficiently for accessing Timer registers */
  volatile Ifx_GPT12_T2* Gpt12TxRegPtr;
  Ifx_GPT12* Gpt12BasePtr;

  /* Extract Channel Number */
  ChannelNo = (uint8)GlobalChannelNumber & ICU_LOWER_NIBBLE;

  Gpt12BasePtr = &MODULE_GPT120;
  Gpt12TxRegPtr = &(Gpt12BasePtr->T2);
  Gpt12TxRegPtr = &(Gpt12TxRegPtr[ChannelNo]);

  /* Set the Tx Reg for next edge/multiedge detection  */
  Gpt12TxRegPtr->U = ((ICU_GPT12_OVFL_OFFSET -
                       ((uint32)Count)) & ICU_GPT12_COUNTER_MASK);
}
#endif

#if (ICU_17_TIMERIP_GPT12_USED == STD_ON) && \
(ICU_17_TIMERIP_INCREMENTAL_INTERFACE_API == STD_ON)
/*******************************************************************************
 ** Traceability: [cover parentID= {C2DA898A-8745-488d-A882-67255309DCAF}]     **
 **                                                                            **
 ** Syntax : static void Icu_lGpt12IncrementalInterfaceIsr(                    **
 **              const Icu_17_TimerIp_ChannelConfigType *const LocalIcuChanPtr)**
 **                                                                            **
 ** Description :     Function to service the GPT12 incremental interface ISR  **
 ** [/cover]                                                                   **
 **                                                                            **
 ** Service ID:       None                                                     **
 **                                                                            **
 ** Sync/Async:       Synchronous                                              **
 **                                                                            **
 ** Reentrancy:       Reentrant for different channel                          **
 **                                                                            **
 ** Parameters (in):  LocalIcuChanPtr - channel configuration pointer          **
 **                                                                            **
 ** Parameters (out): None                                                     **
 **                                                                            **
 ** Return value:     None                                                     **
 **                                                                            **
 *******************************************************************************/
LOCAL_INLINE void Icu_lGpt12IncrementalInterfaceIsr(
     const Icu_17_TimerIp_ChannelConfigType * const LocalIcuChanPtr)
{
  uint8 ChannelNo; /* Holds the GPT12 Tx Number  */
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   MISRA rule. Union usage is required to access SFR data type and implement
   efficiently for accessing Timer registers */
  volatile Ifx_GPT12_T2CON* Gpt12TxConRegPtr;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   MISRA rule. Union usage is required to access SFR data type and implement
   efficiently for accessing Timer registers */
  volatile Ifx_GPT12_T2* Gpt12TxRegPtr;
  Ifx_GPT12* Gpt12BasePtr;
#if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  uint32 TxEdgeValue;
#endif
  uint32 TxValue;
  uint32 TxDirValue;

  /* Extract Channel Number */
  ChannelNo = (uint8) (LocalIcuChanPtr->IcuProperties.AssignedHwUnitNumber)
                                          & ICU_LOWER_NIBBLE;

  Gpt12BasePtr = &MODULE_GPT120;
  Gpt12TxConRegPtr = &(Gpt12BasePtr->T2CON);
  Gpt12TxConRegPtr = &(Gpt12TxConRegPtr[ChannelNo]);
  Gpt12TxRegPtr = &(Gpt12BasePtr->T2);
  Gpt12TxRegPtr = &(Gpt12TxRegPtr[ChannelNo]);

  /* Read and clear TxCON register for TxEDGE bit  */
#if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  /* MISRA2012_RULE_4_6_JUSTIFICATION: Basic numerical type -
   * int/unsigned int is used while invoking compiler intrinsic
   * functions. These compiler intrinsic functions are implemented
   * specific to tricore. Hence to align with compiler declaration use
   * of unsigned int is mandatory*/
  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  TxEdgeValue = Mcal_Swap((uint32*)Gpt12TxConRegPtr,0U,ICU_GPT12_TxEDGE_MASK);
#endif
  TxDirValue = (Gpt12TxConRegPtr->U)&ICU_GPT12_TxDIR_MASK;
  TxValue = Gpt12TxRegPtr->U;
/* [cover parentID={74EC35F0-988C-432b-AC85-0C592AC7DAFA}]
if safety is enabled
[/cover] */
#if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  TxEdgeValue = TxEdgeValue & ICU_GPT12_TxEDGE_MASK;
  /* [cover parentID={A2ADE720-A2FC-4a73-B69E-ACB0EB415602}]
  Is TxEDGE bit set?
  [/cover] */
  if(TxEdgeValue != 0U)
#endif
  {
    /* Notification for new count edge */
    if(NULL_PTR != LocalIcuChanPtr->NotificationPointer)
    {

        /* [cover parentID={05C97339-5ADD-4555-ADCE-0B653AB91586}]
      Provide count edge notification
      [/cover] */
      LocalIcuChanPtr->NotificationPointer();
    }
    /* [cover parentID={B44EE0CC-53D7-4bb2-84E9-97E91F044058}]
    Is the counter overflowed?
    [/cover] */
    if(((TxValue == 0U) && (TxDirValue == 0U)) ||
      ((TxValue == ICU_GPT12_COUNTER_MAX) &&
      (TxDirValue == ICU_GPT12_TxDIR_MASK)))
    {
      /* Notification for counter overflow */
      if(NULL_PTR != LocalIcuChanPtr->CntOvflNotificationPointer)
      {
        /* [cover parentID={B92A1FD5-CF63-44a2-BB9C-C7E5CF655286}]
        Provide Counter overflow notification.
        [/cover] */
        LocalIcuChanPtr->CntOvflNotificationPointer();
      }
    }
  }
#if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  else
  {
    /* [cover parentID={63AF8AEE-5067-4948-B596-EA085066C89F}]
    Report safety error for invallid ISR
    [/cover] */
    /* Safety Error */
    Mcal_ReportSafetyError(
    ICU_17_TIMERIP_MODULE_ID,
    ICU_17_TIMERIP_INSTANCE_ID,
    ICU_17_TIMERIP_SID_ISR,
    ICU_17_TIMERIP_E_INVALID_ISR);
  }
#endif
}
#endif
#if (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID= {43F6B328-73A0-4069-B2A3-F22D90EAF74C}]     **
**                                                                            **
** Syntax :           LOCAL_INLINE void Icu_lSignalEdgeNotification_Isr(      **
**                    const uint8 CoreId                                      **
**              const Icu_17_TimerIp_ChannelConfigType *const LocalIcuChanPtr **
**                    uint32 *const GlbIndexStatusPtr)                        **
**                                                                            **
** Description :      This routine is called from an ISR only. the service is **
**                    executed for Signal edge detection / Notification       **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        None                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Reentrant for different channel                         **
**                                                                            **
** Parameters (in):   CoreId - core in which function is called               **
**                    LocalIcuChanPtr - To call the notification function     **
**                    GlbIndexStatusPtr - Pointer to channel flags            **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value:      None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lSignalEdgeNotification_Isr(const uint8 CoreId,
    const Icu_17_TimerIp_ChannelConfigType * const LocalIcuChanPtr,
    uint32 * const GlbIndexStatusPtr)
{
  uint32 WakeupStatus;

  /* [cover parentID={AA39C210-AE20-42b9-9EBF-06EBC0D2E6DE}]
  Is ICU in SLEEP mode?
  [/cover] */
  if (ICU_17_TIMERIP_MODE_SLEEP == Icu_17_TimerIp_Varlist[CoreId]->GlobalMode)
  {

    /* A wakeup event occurs on a wakeup capable ICU Channel */
    /* Wakeup event is set in Icu_17_TimerIp_EnableWakeup and a check is needed
     to know whether the module is in sleep mode or not */
    /* During sleep mode its not possible for a non-wakeup capable channel
     to raise an interrupt because it is taken care in Icu_17_TimerIp_SetMode */
    /* However Running Channels are an exception till new API's are
     designed for Signal Measurement, still those channels does not
     have the capability to enter this routine due to its measurement mode. */
    WakeupStatus = Mcal_GetBitAtomic(*GlbIndexStatusPtr, \
        ICU_CHNL_WAKEUP_CAPABLE_POS, ICU_CHNL_WAKEUP_BIT_LENGTH);
    /* [cover parentID={5A0E3409-90DD-44bf-BC7D-883764E73716}]
    Is channel wakeup capable?
    [/cover] */
    if (1U == WakeupStatus)
    {
      /* [cover parentID={16C04575-D8A9-4a72-A2B5-0103820AE54E}]
       Set the ICU_17_TIMERIP_ACTIVE flag
       [/cover] */
      Mcal_SetBitAtomic(GlbIndexStatusPtr, (sint32)ICU_CHNL_STATUS_POS, \
          ICU_CHNL_STATUS_BIT_LENGTH, \
          (uint32 )ICU_17_TIMERIP_ACTIVE);
    /* [cover parentID={D7365F38-6450-4cb6-8315-FD9D2D487CE4}]
     Wakeup Source reporting enabled
     [/cover] */
#if (ICU_17_TIMERIP_REPORT_WAKEUP_SOURCE == STD_ON)
      /* Update wakeup channel info to identify in CheckWakeup */
      /* As wakeup channel info is common for all the channels of ICU atomic
       operation is required.*/
      /* [cover parentID={E1A3918A-D085-4a74-BE27-AC53A6A64D8B}]
      Update wakeup channel information
      [/cover] */
      Mcal_SetBitAtomic(&Icu_17_TimerIp_Varlist[CoreId]->WakeupChannelInfo, \
          (sint32 )LocalIcuChanPtr->ChannelWakeupInfo.EcuMWakeupInfo, 1, \
          (uint32 )1U);
      /* [cover parentID={76CFED89-70F0-4871-B428-BF2E12563D36}]
       EcuM call back
       [/cover] */
      EcuM_CheckWakeup( \
          1UL << (LocalIcuChanPtr->ChannelWakeupInfo.EcuMWakeupInfo));
#endif
      /* [cover parentID={AADC7783-E61F-4254-9DE4-D53D9A23C143}]
      Is notification for the channel enabled?
      [/cover] */
      if ((ICU_ENABLE_NOTIFICATION \
           == Mcal_GetBitAtomic(*GlbIndexStatusPtr, ICU_CHNL_NOTIF_PRESENCE_POS,
                                ICU_CHNL_NOTIF_BIT_LENGTH)))
      {
        /* Only these edge notifications will be provided which are
         supported by hardware.*/
        /* The callback notifications have no parameters and no return
         value*/
        /* [cover parentID={FD339443-C43C-4c3d-94FB-F3980D0A7071}]
        Provide Notification
        [/cover] */
        (LocalIcuChanPtr->NotificationPointer)();
      }
    }
    /* [cover parentID={743805DF-5EA6-4acc-AFBB-610F0736170C}]
    Safety reporting is enabled
    [/cover] */
    #if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
    else
    {
      /* [cover parentID={82CA614D-2CB6-447a-A9C4-3AEF6A7F0BC6}]
      Safety Error
      [/cover] */
      Mcal_ReportSafetyError( \
                              ICU_17_TIMERIP_MODULE_ID, \
                              ICU_17_TIMERIP_INSTANCE_ID, \
                              ICU_17_TIMERIP_SID_ISR, \
                              ICU_17_TIMERIP_E_INVALID_ISR);
    }
    #endif
    /* End of report to Safety */
  }
  else
  {
    /* Verify whether Notification required */
    /* [cover parentID={7C51CBBF-CF1A-4b46-A6AE-BC59041A3468}]
    Is notification for the channel enabled?
    [/cover] */
    if ((ICU_ENABLE_NOTIFICATION \
         == Mcal_GetBitAtomic(*GlbIndexStatusPtr, ICU_CHNL_NOTIF_PRESENCE_POS, \
                              ICU_CHNL_NOTIF_BIT_LENGTH)))
    {
      /* [cover parentID={EB8C14C9-E546-4af9-B261-E3C7B5E00E9C}]
       Set the ICU_17_TIMERIP_ACTIVE flag
       [/cover] */
      Mcal_SetBitAtomic(GlbIndexStatusPtr, (sint32)ICU_CHNL_STATUS_POS, \
          ICU_CHNL_STATUS_BIT_LENGTH, \
          (uint32 )ICU_17_TIMERIP_ACTIVE);
      /* Only these edge notifications will be provided which are
       supported by hardware.*/
      /* The callback notifications have no parameters and no return
       value*/
      /* [cover parentID={7501787A-82A2-4038-BDE7-FE9E5D720F28}]
      Provide Notification
      [/cover] */
      (LocalIcuChanPtr->NotificationPointer)();
    }
    /* [cover parentID={27A127B0-763C-4c37-8671-14943B67D0FE}]
    Is multi edge detection enabled?
    [/cover] */
    else if (ICU_FLAG_SET
        == Mcal_GetBitAtomic(*GlbIndexStatusPtr,
            ICU_CHNL_MULTIEDGE_STAT_POS, ICU_CHNL_MULTIEDGE_STAT_BIT_LENGTH))
    {
      /* [cover parentID={B424A1F7-912E-4c29-85B8-F279C164C400}]
      Set ICU_ACTIVE flag
      [/cover] */
      Mcal_SetBitAtomic(GlbIndexStatusPtr, (sint32)ICU_CHNL_STATUS_POS, \
          ICU_CHNL_STATUS_BIT_LENGTH, \
          (uint32 )ICU_17_TIMERIP_ACTIVE);
    }
    else
    {
      /* [cover parentID={B95416C1-FB16-490f-97CD-3BE646A3030E}]
      Safety is enabled
      [/cover] */
      #if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
      /* [cover parentID={8EB127D6-7E02-454c-9FF8-9BDD00FE83C7}]
      Report Safety Error
      [/cover] */
      /* Safety Error */
      Mcal_ReportSafetyError( \
                              ICU_17_TIMERIP_MODULE_ID, \
                              ICU_17_TIMERIP_INSTANCE_ID, \
                              ICU_17_TIMERIP_SID_ISR, \
                              ICU_17_TIMERIP_E_INVALID_ISR);
                              /* End of report to Safety */
      #endif
    }
    /* #if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON) */
  }
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer GlbIndexStatusPtr is
   * accessed using assembly instruction. */
}
#endif


#if (ICU_17_TIMERIP_EDGE_DETECT_API == STD_ON) || \
    (ICU_17_TIMERIP_EDGE_COUNT_API == STD_ON)
#if (ICU_17_TIMERIP_TIMEOUT_DETECTION_API == STD_ON)
/*******************************************************************************
 ** Traceability: [cover parentID={F6368D94-F55B-42d7-89F1-FD47488DC4C8}]      **
 **                                                                            **
 ** Syntax :           LOCAL_INLINE void Icu_lGtmTimeOutIsr(                   **
 **              const Icu_17_TimerIp_ChannelConfigType *const LocalIcuChanPtr **
 **              const uint32 *const GlbIndexStatusPtr)                        **
 **                                                                            **
 ** Description :      This routine is called from an ISR only. the service is **
 **                    executed for Timeout notification                       **
 ** [/cover]                                                                   **
 **                                                                            **
 ** Service ID:        None                                                    **
 **                                                                            **
 ** Sync/Async:        Synchronous                                             **
 **                                                                            **
 ** Reentrancy:        Reentrant for different channel                         **
 **                                                                            **
 ** Parameters (in):   GlbIndexStatusPtr - Pointer to channel flags            **
 **                    LocalIcuChanPtr - To call the notification function     **
 **                                                                            **
 ** Parameters (out):  None                                                    **
 **                                                                            **
 ** Return value:      None                                                    **
 **                                                                            **
 *******************************************************************************/
LOCAL_INLINE void Icu_lGtmTimeOutIsr(
    const Icu_17_TimerIp_ChannelConfigType * const LocalIcuChanPtr,
    uint32 * const GlbIndexStatusPtr)
{
  uint32 TimeOutStatus;
  TimeOutStatus = Mcal_GetBitAtomic(*GlbIndexStatusPtr, ICU_TIMEOUT_STATUS_POS,
      ICU_TIMEOUT_STATUS_LENGTH);

  /* [cover parentID={E4A105FB-943A-4596-8DEB-018CD5ECF06C}]
  Is the timeout feature enabled?
  [/cover] */
  if (1U == TimeOutStatus)
  {
    /* [cover parentID={D7DA5856-650B-40d8-8C69-7937A11F7B6E}]
    Invoke user configured timeout notification of the channel
    [/cover] */
    (LocalIcuChanPtr->TimeOutNotificationPointer)();
  }
/* [cover parentID={924E0D4A-5D42-40d0-8BC4-2064D7B1100B}]
Safety is enabled
[/cover] */
#if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  else
  {
    /* [cover parentID={E561B513-03BD-41e9-AB1C-1FDF0B736139}]
    Report safety error
    [/cover] */
    Mcal_ReportSafetyError(
    ICU_17_TIMERIP_MODULE_ID,
    ICU_17_TIMERIP_INSTANCE_ID,
    ICU_17_TIMERIP_SID_ISR,
    ICU_17_TIMERIP_E_INVALID_ISR);
  }
#endif
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer GlbIndexStatusPtr is
   * accessed using assembly instruction. */
}
#endif
#endif
#if (ICU_17_TIMERIP_TIMESTAMP_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={17FC0EF3-8D6F-4cdc-9BA5-564185E0135A}]      **
**                                                                            **
** Syntax :           LOCAL_INLINE void Icu_lTimeStamp_Isr(                   **
**                    const uint8 CoreId                                      **
**              const Icu_17_TimerIp_ChannelConfigType *const LocalIcuChanPtr **
**              const uint32 *const GlbIndexStatusPtr)                        **
**                                                                            **
** Description :      This routine is called from an ISR only. the service is **
**                    executed for GTM Time Stamp measurement                 **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        None                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Reentrant for different channel                         **
**                                                                            **
** Parameters (in):   CoreId - core in which function is called               **
**                    LocalIcuChanPtr - To call the notification function     **
**                    GlbIndexStatusPtr - Pointer to channel flags            **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value:      None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Icu_lTimeStamp_Isr( \
    const uint32 CoreId, \
    const Icu_17_TimerIp_ChannelConfigType *const LocalIcuChanPtr, \
    const uint32 *const GlbIndexStatusPtr)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * MISRA rule.To implement efficiently IcuMeasaurementProperty as a post-build
   * parameter Union is required*/
  Icu_17_TimerIp_ChannelData* ChannelDataPtr;
  uint8 ChIndex;
  uint16 CellNum;
  uint16 NotifyCounter;
  uint16 Counter;
  uint32 NotifRequested = 0U;
  #if(ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
  uint32 IcuOption;
  #endif

  CellNum = (uint16) (LocalIcuChanPtr->IcuProperties.AssignedHwUnitNumber);
  #if(ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
  /* Depending on ICU option take action */
  IcuOption = (uint32)LocalIcuChanPtr->IcuProperties.AssignedHwUnit;
  #endif
  /* Check if the activity has started */
  #if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={0C265137-5F62-4ac2-B746-3EA30DC8015D}]
  Check if the activity has started
  [/cover] */
  if (ICU_ACTIVITY_STARTED \
      == Mcal_GetBitAtomic(*GlbIndexStatusPtr, ICU_CHNL_ACTIVITY_STARTED_POS, \
                           ICU_CHNL_ACTIVITY_BIT_LENGTH))
  #endif
  {
    /* Extract the mode specific index */
    ChIndex = LocalIcuChanPtr->ModeMappingIndex;
    /* Store the address in a pointer variable */
    ChannelDataPtr =
              &((Icu_17_TimerIp_Varlist[CoreId]->ChannelDataBasePtr)[ChIndex]);
    #if(ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
    /* [cover parentID={3A7EFACF-D985-412f-AF56-699A7EDDD4D1}]
    Is the channel GTM?
    [/cover] */
    if(IcuOption == ICU_17_TIMERIP_GTM_OPTION)
    {
      /* [cover parentID={6395286B-F96C-49c9-AC79-C93B88C29004}]
      Update buffer with the new time stamp.
      [/cover] */
      ChannelDataPtr->TimeCaptureParas.Address \
        [ChannelDataPtr->TimeCaptureParas.Counter] = \
        Icu_lGtmGetTimeStamp(CellNum);
    }
    else
    #endif
    {
      #if(ICU_17_TIMERIP_CCU6_USED == STD_ON)
      /* [cover parentID={57ADC3D0-CB57-4fab-BF6D-C8720886D25A}]
      Update buffer with the new time stamp.
      [/cover] */
      ChannelDataPtr->TimeCaptureParas.Address \
        [ChannelDataPtr->TimeCaptureParas.Counter] = \
        Icu_lCcuGetTimeStamp(CellNum);
      #endif
    }

    /* [cover parentID={CEC37E07-82FE-45ed-88CB-E7E3FD628E9C}]
    Increment buffer counter.
    [/cover] */
    ChannelDataPtr->TimeCaptureParas.Counter = \
        ChannelDataPtr->TimeCaptureParas.Counter + 1U;
    /* [cover parentID={659D1868-E6BB-4749-80E4-640F0B79ACD4}]
    Has buffer index counter reached notification counter and notify interval
    non zero?
    [/cover] */
    NotifyCounter = ChannelDataPtr->TimeCaptureParas.NotifyCounter;
    Counter = ChannelDataPtr->TimeCaptureParas.Counter;
    /* If Notify is Zero, Notify counter and counter can never be equal.
       Hence check for non-zero notify is not required. */
    if ((NotifyCounter == Counter))
    {
      /* [cover parentID={4524EF93-6588-4547-BF00-7CDFACD5838F}]
      Increment notify counter by notify interval
      [/cover] */
      ChannelDataPtr->TimeCaptureParas.NotifyCounter = \
          ChannelDataPtr->TimeCaptureParas.NotifyCounter
          + ChannelDataPtr->TimeCaptureParas.Notify;
      /* [cover parentID={0A122DFB-178F-47e4-8946-B254FDEB7251}]
      Is notification enabled?
      [/cover] */
      if (ICU_ENABLE_NOTIFICATION \
          == Mcal_GetBitAtomic(*GlbIndexStatusPtr, ICU_CHNL_NOTIF_PRESENCE_POS,
                               ICU_CHNL_NOTIF_BIT_LENGTH))
      {
        /* Call of Notification function if the
         Notify interval is counted */
        NotifRequested = ICU_SET_BIT;
      }
    }
    /* [cover parentID={CC9C0D01-F87B-4a9a-987D-1D788BC36234}]
    Is the buffer LINEAR?
    [/cover] */
    if ((uint8) ICU_17_TIMERIP_LINEAR_BUFFER \
        == (uint8) (LocalIcuChanPtr->IcuProperties.MeasurementProperty))
    {
      /* [cover parentID={BEE8E7AB-09F3-48c4-BA86-755E995046F1}]
      Has the counter reached size of buffer?
      [/cover] */
      if (ChannelDataPtr->TimeCaptureParas.Counter \
          == ChannelDataPtr->TimeCaptureParas.Size)
      {
        #if(ICU_17_TIMERIP_GTM_TIM_USED == STD_ON)
        /* Terminate */
        /* [cover parentID={5C659B65-D85D-451b-BE25-DA3CCCD4A0EC}]
        Is the channel GTM?
        [/cover] */
        if(IcuOption == ICU_17_TIMERIP_GTM_OPTION)
        {
          /* [cover parentID={DFC4515A-C96A-4f38-9A79-86A5D9569F72}]
          Stop time stamping activity.
          [/cover] */
          Icu_lGtmStopTimeStamp(CellNum);
        }
        else
        #endif
        {
          #if(ICU_17_TIMERIP_CCU6_USED == STD_ON)
          /* MISRA2012_RULE_2_2_JUSTIFICATION: No side effects foreseen
           * by violating this MISRA rule, as the called function 
           * (Icu_lCcuDisableChannel) performs action using
           * assembly instructions */
          /* [cover parentID={C3266ABF-F7B2-4626-B55A-D33F5BDADAAD}]
          Stop time stamping activity.
          [/cover] */
          Icu_lCcuDisableChannel(CellNum);
          #endif
        }
        /* [cover parentID={CF7812C6-9412-4c28-802E-A238FF25C97D}]
        Reset channel activity started bit.
        [/cover] */
        /* Activity Start flag is set to zero */
        Mcal_SetBitAtomic(GlbIndexStatusPtr, \
                          (sint32)ICU_CHNL_ACTIVITY_STARTED_POS, \
                          ICU_CHNL_ACTIVITY_BIT_LENGTH, 0U);
        /* Reset notify counter */
        /* [cover parentID={47325B76-0693-4278-A66C-63DFE7637596}]
        Reset Notify Counter.
        [/cover] */
        ChannelDataPtr->TimeCaptureParas.NotifyCounter = 0U;
      }
    }
    else
    {
      /* [cover parentID={A595ED6D-C402-4717-9ED6-5B8C21650283}]
      Has the counter reached size of buffer?
      [/cover] */
      if (ChannelDataPtr->TimeCaptureParas.Counter \
          == ChannelDataPtr->TimeCaptureParas.Size)
      {
        /* [cover parentID={81E598D1-6FC7-427b-B80B-465000756FAC}]
        Reset buffer counter to '0' and adjust the notify counter.
        [/cover] */
        /* Restart the buffer form 0th index */
        /* Reset the counter */
        ChannelDataPtr->TimeCaptureParas.Counter = 0U;
        /* Rescale the notify check counter */
        ChannelDataPtr->TimeCaptureParas.NotifyCounter = \
            ChannelDataPtr->TimeCaptureParas.NotifyCounter \
            - ChannelDataPtr->TimeCaptureParas.Size;
      }
    }
    if(NotifRequested == ICU_SET_BIT)
    {
      /* Call of notification function for timestamp */
      /* Notification has no parameter and no return value */
      (LocalIcuChanPtr->NotificationPointer)();
    }
  }
  /* Report safety error if activity is not started as spurious ISR */
  /* [cover parentID={F95DB4F7-DF64-46b6-9775-09D5E991DDFC}]
  Safety error reporting enabled
  [/cover] */
  #if (ICU_17_TIMERIP_SAFETY_ENABLE == STD_ON)
  else
  {
    /* [cover parentID={1313A58A-C304-48c1-BCDC-238EE9C64108}]
    Report Safety Error
    [/cover] */
    /* Safety Error */
    Mcal_ReportSafetyError( \
                            ICU_17_TIMERIP_MODULE_ID, \
                            ICU_17_TIMERIP_INSTANCE_ID, \
                            ICU_17_TIMERIP_SID_ISR, \
                            ICU_17_TIMERIP_E_INVALID_ISR);
  }
  #endif
  /* End of report to Safety */
}
#endif

/*******************************************************************************
** Traceability: [cover parentID={2F00B548-B1BF-469f-B7FA-145F6AA4B211}]      **
**                                                                            **
** Syntax :           LOCAL_INLINE uint8                                      **
**                                Icu_lGetCoreChIndex(                        **
**                                  const uint8 Channel     )                 **
**                                                                            **
** Description :      Local function to extract core specific channel index   **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        None                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Reentrant                                               **
**                                                                            **
** Parameters (in):   Channel - ICU channel ID                                **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value:      Core specific channe index                              **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Icu_lGetCoreChIndex(const uint8 Channel)
{
  uint8 CoreChIndex;
  #if (ICU_17_TIMERIP_SINGLE_CORE == STD_OFF)
  CoreChIndex = (uint8)(Icu_17_TimerIp_ConfigPtr->ChannelMapping[Channel] & \
                          ICU_CHNL_MAP_CHNL_INDEX_MASK);
  #else
  CoreChIndex = (uint8)Channel;
  #endif
  return CoreChIndex;
}
/* [cover parentID={FC34B5EF-D694-4d02-94A5-24C0607D5C4E}]
   Code executable from any core.
   [/cover] */

#define ICU_17_TIMERIP_STOP_SEC_CODE_ASIL_B_GLOBAL
/* [cover parentID={14AF8E74-51FE-4399-8A99-5789F2CD773D}]
Icu_17_TimerIp_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"
