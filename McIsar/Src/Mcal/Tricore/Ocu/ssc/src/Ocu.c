/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2021)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : Ocu.c                                                      **
**                                                                            **
**  VERSION      : 32.0.0                                                     **
**                                                                            **
**  DATE         : 2021-10-20                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY : [cover parentID={DB55B3CD-8430-41f2-A91F-AADF1E1A10E3}]    **
**                                                                            **
**  DESCRIPTION  : Ocu Driver source file                                     **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) :Specification of OCU Driver,AUTOSAR Release 4.2.2&4.4.0 **
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

/* [cover parentID={F1734FD9-DFFF-4b6e-A533-2EE3E1B39AE7}] */
/* File inclusions */
/* [/cover] */

/* Global functions like Atomic write function and get CPU index */
#include "McalLib.h"


/* Ocu Module header file */
#include "Ocu.h"
#include "Ocu_Local.h"
#include "Ocu_Cbk.h"


/* Include SchM to import the critical section functions */
#include "SchM_Ocu.h"

/* this includes Gtm configuration file also */
#include "Mcu_17_TimerIp.h"



/* MISRA2012_RULE_20_5_JUSTIFICATION: ACCESS is undefined here to resolve the
 * conflict between macro 'ACCESS' (ObjectAccessType) used in OS module and the
 * structure member 'ACCESS'(Ifx_GTM_ARU) used in GTM SFR definitions. This is
 * to be done before including "IfxGtm_reg.h" */
#if defined(ACCESS)
#undef ACCESS
#endif
#include "IfxGtm_bf.h"



#if (OCU_DEV_ERROR_DETECT == STD_ON)
/* Import of DET functionality. */
#include "Det.h"
#endif
/* [cover parentID={1A65EADD-AFD0-4845-B2D2-8257E086DD67}]
    Safety Mechanism for reporting errors in ASIL B usecase [/cover] */
#if (OCU_SAFETY_ENABLE == STD_ON)
#include "Mcal_SafetyError.h"
#endif

/******************************************************************************
 **                      Imported Compiler Switch Check                        *
 ******************************************************************************/
/* [cover parentID={66A51B88-C209-4df8-A8B8-ED931300421A}]
   Check for definition of the AS Version
   [/cover] */
/* [cover parentID={2ABF3735-7A5D-4389-AB3B-66A5635D5A4A}]
   Modules version consistency check
   [/cover] */
#ifndef OCU_AR_RELEASE_MAJOR_VERSION
#error "OCU_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

#if ( OCU_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION )
#error "OCU_AR_RELEASE_MAJOR_VERSION does not match. "
#endif

#ifndef OCU_AR_RELEASE_MINOR_VERSION
#error "OCU_AR_RELEASE_MINOR_VERSION is not defined. "
#endif

#if ( OCU_AR_RELEASE_MINOR_VERSION != MCAL_AR_RELEASE_MINOR_VERSION  )
#error "OCU_AR_RELEASE_MINOR_VERSION does not match. "
#endif

#ifndef OCU_AR_RELEASE_REVISION_VERSION
#error "OCU_AR_RELEASE_REVISION_VERSION is not defined. "
#endif

#if ( OCU_AR_RELEASE_REVISION_VERSION != MCAL_AR_RELEASE_REVISION_VERSION  ) 
#error "OCU_AR_RELEASE_REVISION_VERSION does not match. "
#endif


/* Check for definition of SW version Information */
#ifndef OCU_SW_MAJOR_VERSION
#error "OCU_SW_MAJOR_VERSION is not defined. "
#endif

#ifndef OCU_SW_MINOR_VERSION
#error "OCU_SW_MINOR_VERSION is not defined. "
#endif

#ifndef OCU_SW_PATCH_VERSION
#error "OCU_SW_PATCH_VERSION is not defined. "
#endif
#if ( OCU_SW_MAJOR_VERSION != 20U )
#error "OCU_SW_MAJOR_VERSION does not match. "
#endif

#if ( OCU_SW_MINOR_VERSION != 10U )
#error "OCU_SW_MINOR_VERSION does not match. "
#endif

#if ( OCU_SW_PATCH_VERSION != 0U )
#error "OCU_SW_PATCH_VERSION does not match. "
#endif
/*
  Inter Module Checks to avoid integration of incompatible files
 */
/* [cover parentID={073CB121-9C91-401a-A434-49B6E191FB88}]
OCU Version check for DET module
[/cover] */
#if (OCU_DEV_ERROR_DETECT == STD_ON)

#ifndef  DET_AR_RELEASE_MAJOR_VERSION
#error "DET_AR_RELEASE_MAJOR_VERSION is not defined."
#endif

#if ( DET_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION )
#error "DET_AR_RELEASE_MAJOR_VERSION does not match."
#endif

#endif
/* End Of OCU_DEV_ERROR_DETECT */

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
#define OCU_CHANNEL_MSK                         (0xFFU)

/*******************************************************************************
 **                      Private Variable Definitions                         **
 ******************************************************************************/
#if (OCU_MAX_CHANNELS != 0U)

/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}] */
/* Memory mapping for variables */
/* [/cover] */
/* @@@@@@Core0 RAM*/
#if (OCU_MAX_CHANNELS_CORE0 > 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define OCU_START_SEC_VAR_CLEARED_ASIL_B_CORE0_32
/* [cover parentID={B4EF5A53-8526-484d-8EDA-8C95CAE0E18F}]
Ocu_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Ocu_MemMap.h"
static Ocu_ChannelVarType Ocu_ChannelVarCore0[OCU_MAX_CHANNELS_CORE0];

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define OCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_32
/* [cover parentID={B4EF5A53-8526-484d-8EDA-8C95CAE0E18F}]
Ocu_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Ocu_MemMap.h"
#endif

/* @@@@@@Core1 RAM*/
#if (OCU_MAX_CHANNELS_CORE1 > 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define OCU_START_SEC_VAR_CLEARED_ASIL_B_CORE1_32
/* [cover parentID={B4EF5A53-8526-484d-8EDA-8C95CAE0E18F}]
Ocu_MemMap.h file inclusion.
[/cover] */
/* [cover parentID={BFA49CD8-D650-4485-A345-854E3EF93CC6}]
OCU Multicore memory allocations.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Ocu_MemMap.h"
static Ocu_ChannelVarType Ocu_ChannelVarCore1[OCU_MAX_CHANNELS_CORE1];

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define OCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_32
/* [cover parentID={B4EF5A53-8526-484d-8EDA-8C95CAE0E18F}]
Ocu_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Ocu_MemMap.h"
#endif

/* @@@@@@Core2 RAM*/
#if (OCU_MAX_CHANNELS_CORE2 > 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define OCU_START_SEC_VAR_CLEARED_ASIL_B_CORE2_32
/* [cover parentID={B4EF5A53-8526-484d-8EDA-8C95CAE0E18F}]
Ocu_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Ocu_MemMap.h"
static Ocu_ChannelVarType Ocu_ChannelVarCore2[OCU_MAX_CHANNELS_CORE2];

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define OCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_32
/* [cover parentID={B4EF5A53-8526-484d-8EDA-8C95CAE0E18F}]
Ocu_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Ocu_MemMap.h"
#endif

/* @@@@@@Core3 RAM*/
#if (OCU_MAX_CHANNELS_CORE3 > 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define OCU_START_SEC_VAR_CLEARED_ASIL_B_CORE3_32
/* [cover parentID={B4EF5A53-8526-484d-8EDA-8C95CAE0E18F}]
Ocu_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Ocu_MemMap.h"
static Ocu_ChannelVarType Ocu_ChannelVarCore3[OCU_MAX_CHANNELS_CORE3];

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define OCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_32
/* [cover parentID={B4EF5A53-8526-484d-8EDA-8C95CAE0E18F}]
Ocu_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Ocu_MemMap.h"
#endif

/* @@@@@@Core4 RAM*/
#if (OCU_MAX_CHANNELS_CORE4 > 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define OCU_START_SEC_VAR_CLEARED_ASIL_B_CORE4_32
/* [cover parentID={B4EF5A53-8526-484d-8EDA-8C95CAE0E18F}]
Ocu_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Ocu_MemMap.h"
static Ocu_ChannelVarType Ocu_ChannelVarCore4[OCU_MAX_CHANNELS_CORE4];

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define OCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_32
/* [cover parentID={B4EF5A53-8526-484d-8EDA-8C95CAE0E18F}]
Ocu_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Ocu_MemMap.h"
#endif

/* @@@@@@Core5 RAM*/
#if (OCU_MAX_CHANNELS_CORE5 > 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define OCU_START_SEC_VAR_CLEARED_ASIL_B_CORE5_32
/* [cover parentID={B4EF5A53-8526-484d-8EDA-8C95CAE0E18F}]
Ocu_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Ocu_MemMap.h"
static Ocu_ChannelVarType Ocu_ChannelVarCore5[OCU_MAX_CHANNELS_CORE5];

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define OCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_32
/* [cover parentID={B4EF5A53-8526-484d-8EDA-8C95CAE0E18F}]
Ocu_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Ocu_MemMap.h"
#endif

#endif /* MAX_CHANNELS > 0*/

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define OCU_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
/* [cover parentID={B4EF5A53-8526-484d-8EDA-8C95CAE0E18F}]
Ocu_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Ocu_MemMap.h"
/* Variable Holds the Configuration Pointer given in Ocu_Init */
/*@@@@@@@@@@@ Common RAM*/
/* Root Config pointer */
static const Ocu_ConfigType *Ocu_ConfigPtr;
/* Initialize status for all cores. */
static uint32 Ocu_InitStatus;

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define OCU_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
/* [cover parentID={B4EF5A53-8526-484d-8EDA-8C95CAE0E18F}]
Ocu_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Ocu_MemMap.h"

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
#define OCU_START_SEC_CONST_ASIL_B_GLOBAL_32
/* [cover parentID={B4EF5A53-8526-484d-8EDA-8C95CAE0E18F}]
Ocu_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Ocu_MemMap.h"

/* Root variable list */
static Ocu_ChannelVarType* const Ocu_RootChannelVar[OCU_MAX_CORES] = {
  /* Core 0 */
  #if (OCU_MAX_CHANNELS_CORE0 > 0U)
  /* Variable list root pointer for Core 0*/
  Ocu_ChannelVarCore0
  #else
  NULL_PTR
  #endif
  /* Core 1 */
  #if (OCU_MAX_CHANNELS_CORE1 > 0U)
  /* Variable list root pointer for Core 1*/
  , Ocu_ChannelVarCore1
  #else
  , NULL_PTR
  #endif
  /* Core 2 */
  #if (OCU_MAX_CHANNELS_CORE2 > 0U)
  /* Variable list root pointer for Core 2*/
  , Ocu_ChannelVarCore2
  #else
  , NULL_PTR
  #endif
  /* Core 3 */
  #if (OCU_MAX_CHANNELS_CORE3 > 0U)
  /* Variable list root pointer for Core 3*/
  , Ocu_ChannelVarCore3
  #else
  , NULL_PTR
  #endif
  /* Core 4 */
  #if (OCU_MAX_CHANNELS_CORE4 > 0U)
  /* Variable list root pointer for Core 4*/
  , Ocu_ChannelVarCore4
  #else
  , NULL_PTR
  #endif
  /* Core 5 */
  #if (OCU_MAX_CHANNELS_CORE5 > 0U)
  /* Variable list root pointer for Core 5*/
  , Ocu_ChannelVarCore5
  #else
  , NULL_PTR
  #endif
};

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
   due to Autosar Naming constraints.*/
#define OCU_STOP_SEC_CONST_ASIL_B_GLOBAL_32
/* [cover parentID={B4EF5A53-8526-484d-8EDA-8C95CAE0E18F}]
Ocu_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Ocu_MemMap.h"
/* [cover parentID={A79C7BF6-562C-4c96-905C-98CDE1954FC2}]
   Code executable from any core.
   [/cover] */
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}] */
/* Memory mapping for code */
/* [/cover] */
#define OCU_START_SEC_CODE_ASIL_B_GLOBAL
/* [cover parentID={B4EF5A53-8526-484d-8EDA-8C95CAE0E18F}]
Ocu_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Ocu_MemMap.h"

/******************************************************************************
 **                      Exported Function Declarations                       **
 ******************************************************************************/


/*******************************************************************************
***                      Private Function Declarations                        **
*******************************************************************************/
#if (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON)
LOCAL_INLINE uint32 Ocu_lInitDetCheck(
  const Ocu_ConfigType *const ConfigPtr,
  const uint8 CoreId);
#endif



LOCAL_INLINE void Ocu_lChannelInit(const uint8 CoreId);

#if (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON)
static uint32 Ocu_lInitCallVerify(const uint8 ServiceId, const uint8 CoreId);
#endif

#if (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON)
static uint32 Ocu_lChannelVerify(
  const uint8 ServiceId,
  const Ocu_ChannelType Channel,
  const uint8 CoreId);
#endif

static uint8 Ocu_lGetAtomPinAction(
  const uint16 HwUnitNumber,
  const uint8 PinAction);

#if (OCU_SET_PIN_ACTION_API == STD_ON)
LOCAL_INLINE void Ocu_lSetAtomPinAction(
  const uint16 HwUnitNumber,
  const uint8 PinAction);
#endif

#if (OCU_DEV_ERROR_DETECT == STD_ON)|| (OCU_SAFETY_ENABLE == STD_ON)
static void Ocu_lReportError(const uint8 ApiId,
                             const uint8 ErrorId);
#endif

#if (OCU_MULTICORE_ERROR_DETECT == STD_ON)|| (OCU_SAFETY_ENABLE == STD_ON)

static void Ocu_lReportMulticoreError(const uint8 ApiId,
                                      const uint8 ErrorId);
#endif
#if (OCU_SAFETY_ENABLE == STD_ON)
LOCAL_INLINE uint32 Ocu_lIsrSafetyCheck(const Ocu_ChannelType Channel, \
                                        const uint8 CoreId);
#endif
#if ((OCU_DE_INIT_API == STD_ON) && ((OCU_DEV_ERROR_DETECT == STD_ON) \
|| (OCU_SAFETY_ENABLE == STD_ON)))
LOCAL_INLINE uint32 Ocu_lDeInitDETCheck(uint8 CoreId);
#endif


#if (OCU_INITCHECK_API == STD_ON)
LOCAL_INLINE Std_ReturnType Ocu_lPreInitCheck(
  const Ocu_ConfigType* const ConfigPtr, const uint8 CoreId);



LOCAL_INLINE Std_ReturnType Ocu_lInitCheck(
  const Ocu_ChannelConfigType *const LocalOcuChanPtr,
  const Ocu_ChannelVarType *const ChannelVarPtr);
#endif

static Ocu_ValueType Ocu_lGetCounter(
  const uint8 HwUnit,
  const uint16 HwUnitNumer,
  const uint8 ClockSource);


static uint32 Ocu_lGetReturnValue(
  const Ocu_ValueType CompareValue,
  const Ocu_ValueType CounterValue,
  const Ocu_ValueType ReferenceValue,
  const Ocu_ValueType MaxCounter);


static Ocu_ReturnType Ocu_lSetAtomCompare(
  const Ocu_ValueType CompareValue,
  const Ocu_ValueType ReferenceValue,
  const Ocu_ChannelConfigType *const ChanPtr,
  const uint8 PinAction,
  const Ocu_ChannelType Channel);

static void Ocu_lEnDisCCU1Irq(const uint8 HwUnit,
                              const uint16 HwUnitNumber,
                              const uint8 EnDis);

/********************* Interrupts **************************/



/*******************************************************************************
 **                      Exported Function Definitions                        **
 ******************************************************************************/

/*[cover parentID={79E7AD5F-B896-4dfb-BC7A-88A3F4B8FD0F}]
All the API in Ocu Module Supports Multicore
[/cover]*/

/*******************************************************************************
** Traceability: [cover parentID={AE26B887-701A-483a-8FC5-CC99835B1358}]      **
**                                                                            **
** Syntax : void Ocu_Init(const Ocu_ConfigType          *const ConfigPtr )    **
** Description : Driver Module Initialization                                 **
**               1.This function will initialize all relevant registers of    **
**               configured hardware (AssignedHWUnit) with the values of      **
**               structure referenced by the parameter ConfigPtr.             **
**               2. This service will disable all notifications.              **
**               3. Resources that are not configured in the configuration    **
**                  file will not be changed.                                 **
**               4. All OCU channel status is set to OCU_STOPPED              **
**               5. All used registers used by configuration will be          **
**                  initialized if Reset and Deinit API will not reset the    **
**                  registers                                                 **
**               6. Clearing of pending interrupt flags not done in this      **
**                  function.                                                 **
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
/*[cover parentID={7F5A4CE6-A065-494e-9B74-0654A5CB52D1}]
Safety Properties
[/cover]*/

void Ocu_Init(
  const Ocu_ConfigType *const ConfigPtr)
{
  uint8 CoreId;

  /* Get core id which is executing currently */
  CoreId = OCU_GETCOREID();

  /* [cover parentID={85E0478F-4F8B-4d91-BDD3-3E6678F00B75}]
  DET or Safety is enabled
  [/cover] */
  #if (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON)
  uint32 ErrorFlag;
  /* Perform the Init pre-requisite checks*/
  ErrorFlag = Ocu_lInitDetCheck (ConfigPtr, CoreId);
  /* [cover parentID={61F28243-9B0A-4968-94AB-4EB3679EE505}]
  Any DET occured
  [/cover] */
  if(OCU_ERROR_FOUND != ErrorFlag)
  #endif
  {

    /* [cover parentID={4FB33FAB-58D9-4ab1-9E9F-DB1CDAC4499C}]
    Store Config pointer
    [/cover] */
    Ocu_ConfigPtr = ConfigPtr;

    /* Verify for the configured channels */
    /* [cover parentID={4AEF8057-7B68-460d-A340-F1DD50BE97AA}]
    Initialize all the channels allocated to the core.
    [/cover] */
    Ocu_lChannelInit(CoreId);
    /* Set Status to indicate that initialization is done */
    Mcal_SetBitAtomic(&Ocu_InitStatus, \
                      (uint32) (CoreId * OCU_INIT_STATUS_SIZE), \
                      OCU_INIT_STATUS_SIZE, (uint32) (OCU_INITIALIZED) );

  }
  return;
  /* [cover parentID={DD15BFCB-9595-40fe-AC4C-93C9FEBCC9F2}]
    OCU Interrupt Control Registers.
  [/cover] */
}/* End of Ocu_Init() function */

#if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={F41C9FB6-47A2-49b3-89ED-E5B4A12BB306}]      **
**                                                                            **
** Syntax : void Ocu_EnableNotification( const Ocu_ChannelType ChannelNumber) **
**                                                                            **
** Description : This service will enable the OCU notification.               **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x0B                                                     **
*                                                                             **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  ChannelNumber - Numeric identifier of the OCU channel    **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={7F5A4CE6-A065-494e-9B74-0654A5CB52D1}]
Safety Properties
[/cover]*/
void Ocu_EnableNotification(const Ocu_ChannelType ChannelNumber)
{
  #if (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON)
  uint32 ErrorFlag;
  #endif
  const Ocu_ChannelConfigType *LocalOcuChanPtr; /* ROM pointer */
  uint32* ChannelStatusPtr;
  uint8 CoreId;
  uint8 CoreChIndex;
  /* Get core id which is executing currently */
  CoreId = OCU_GETCOREID();
  /* [cover parentID={955A859B-7D25-47b1-9752-5CD035B37AB7}]
  If DET or Safety is enabled
  [/cover] */
  #if (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={13EFA6F9-213F-4688-A3D7-8D409DB06E2A}]
  Verify if Ocu_Init is invoked.
  [/cover] */
  ErrorFlag = Ocu_lInitCallVerify(OCU_SID_ENABLENOTIFICATION, CoreId);
  /* [cover parentID={F08303D1-4312-4c38-AD7E-F9AAEC84023E}]
  Is channel valid
  [/cover] */
  if (ErrorFlag != OCU_ERROR_FOUND)
  {
    /* [cover parentID={E4EEC12E-CBB5-4b4b-8EF1-D8A84652998F}]
    Verify if channel is valid
    [/cover] */
    ErrorFlag = Ocu_lChannelVerify(OCU_SID_ENABLENOTIFICATION, ChannelNumber, CoreId);
  }
  /* [cover parentID={B7593791-4F73-4741-B9F4-963BBE89BB93}]
  Is channel valid
  [/cover] */
  if (ErrorFlag != OCU_ERROR_FOUND)
  #endif
    /* #if  (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON) */
  {
    #if (OCU_SINGLE_CORE == STD_OFF)
    /* Initialize OCU configured channel ROM pointer */
    CoreChIndex = (uint8)(Ocu_ConfigPtr->ChannelMapping[ChannelNumber] & \
                          OCU_CHNL_MAP_CHNL_INDEX_MASK);
    #else
    CoreChIndex = (uint8)ChannelNumber;
    #endif

    LocalOcuChanPtr = &((Ocu_ConfigPtr->CoreConfig[CoreId]->ChannelConfigPtr)\
                        [CoreChIndex]);
    /* Enable notification only if a valid notification function is
     * available.*/
    /* [cover parentID={F1739FE6-0E08-46c3-AA6B-5433B6410EEB}]
    Is the notification pointer NULL
    [/cover] */
    if (LocalOcuChanPtr->NotificationPointer == NULL_PTR )
    {
      #if (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON)
      /* [cover parentID={BCB687BF-0AB7-4439-84DE-E0D274802EB8}]
      Report error to indicate invalid notification pointer
      [/cover] */
      Ocu_lReportError(
        OCU_SID_ENABLENOTIFICATION,
        OCU_E_NO_VALID_NOTIF
      );/* End of report Error */
      #endif
    }
    else
    {
      /* Channel specific status variable */
      ChannelStatusPtr = &(Ocu_RootChannelVar[CoreId][CoreChIndex].Status);



      /* [cover parentID={269DFAB0-7891-485d-871E-4D59364A848A}]
      Are notifications disabled ?
      [/cover] */

      if (OCU_ENABLE_NOTIFICATION
          != Mcal_GetBitAtomic(*ChannelStatusPtr, OCU_CHNL_NOTIF_PRESENCE_POS,
                               OCU_CHNL_NOTIF_BIT_LENGTH))
      {

        /* Enter critical section */
        SchM_Enter_Ocu_EnDisCCU1Irq();

        /* [cover parentID={B57855CB-AD27-4a6c-9C6B-9B3FAFC74C61}]
            Is the channel in running state?
            [/cover] */
        if (OCU_CHANNEL_RUNNING
            == Mcal_GetBitAtomic(*ChannelStatusPtr, OCU_CHNL_STATUS_POS,
                                 OCU_CHNL_STATUS_BIT_LENGTH))
        {
          /* Enable interrupts to start issuing notifications */
          Ocu_lEnDisCCU1Irq(LocalOcuChanPtr->OcuProperties.AssignedHwUnit,
                            LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber, ENABLE_INTERRUPTS);
        }
        /* Enable notifications */
        /* [cover parentID={F8FA9CC6-03D8-4ad5-83E7-E9A305774157}]
        Enable the notifications atomically
        [/cover] */
        Mcal_SetBitAtomic((ChannelStatusPtr), OCU_CHNL_NOTIF_PRESENCE_POS,
                          OCU_CHNL_NOTIF_BIT_LENGTH, (uint32)OCU_ENABLE_NOTIFICATION);
        /*End Critical section */
        SchM_Exit_Ocu_EnDisCCU1Irq();
      }
    }
  }
  /* [cover parentID={DD15BFCB-9595-40fe-AC4C-93C9FEBCC9F2}]
    OCU Interrupt Control Registers.
  [/cover] */
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer ChannelStatusPtr is
   * accessed using assembly instruction. */
}/* End of Ocu_EnableNotification() function */
#endif
#if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={AC2D13D5-7017-43e4-9D15-B92D714A6D68}]      **
**                                                                            **
** Syntax : void Ocu_DisableNotification( const Ocu_ChannelType ChannelNumber)**
**                                                                            **
** Description : This service will disable the OCU notification.              **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x0A                                                     **
*                                                                             **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  ChannelNumber - Numeric identifier of the OCU channel    **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={7F5A4CE6-A065-494e-9B74-0654A5CB52D1}]
Safety Properties
[/cover]*/
void Ocu_DisableNotification( const Ocu_ChannelType ChannelNumber)
{
  #if (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON)
  uint32 ErrorFlag;
  #endif
  const Ocu_ChannelConfigType *LocalOcuChanPtr; /* ROM pointer */
  uint32* ChannelStatusPtr;
  uint8 CoreId;
  uint8 CoreChIndex;
  /* Get core id which is executing currently */
  CoreId = OCU_GETCOREID();
  /* [cover parentID={A06E51DF-C791-4966-928E-BA59E5281274}]
  DET or Safety is enabled
  [/cover] */
  #if (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={60F2C398-75AB-4eee-9CBC-90B48F9128AC}]
  Verify if Ocu_Init is invoked.
  [/cover] */
  ErrorFlag = Ocu_lInitCallVerify(OCU_SID_DISABLENOTIFICATION, CoreId);
  /* [cover parentID={40A8DD89-8CB9-4bf4-A2F9-2F1E7FCB9E36}]
  Is Ocu_Init invoked?
  [/cover] */
  if (ErrorFlag != OCU_ERROR_FOUND)
  {
    /* [cover parentID={5838D099-5FDC-4292-B475-BD92E3549C51}]
    Verify if channel is valid
    [/cover] */
    ErrorFlag = Ocu_lChannelVerify(OCU_SID_DISABLENOTIFICATION,
                                   ChannelNumber, CoreId);
  }
  /* [cover parentID={1600C395-FE3E-40fe-931A-B7ADEC14E177}]
  Is channel valid?
  [/cover] */
  if (ErrorFlag != OCU_ERROR_FOUND)
  #endif
  {
    #if (OCU_SINGLE_CORE == STD_OFF)
    /* Initialize OCU configured channel ROM pointer */
    CoreChIndex = (uint8)(Ocu_ConfigPtr->ChannelMapping[ChannelNumber] & \
                          OCU_CHNL_MAP_CHNL_INDEX_MASK);
    #else
    CoreChIndex = (uint8)ChannelNumber;
    #endif
    LocalOcuChanPtr = &((Ocu_ConfigPtr->CoreConfig[CoreId]->ChannelConfigPtr)\
                        [CoreChIndex]);

    /* Disable notification only if a valid notification function is
     * available.*/
    /* [cover parentID={9FFA3D9C-BEAC-4f51-9EEF-27CA1530B9CF}]
    Is the notification pointer NULL
    [/cover] */
    if (LocalOcuChanPtr->NotificationPointer == NULL_PTR )
    {

      #if (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON)
      /* [cover parentID={C12313E4-ADB5-4555-BFA1-DD2BE040976B}]
      Report error to indicate invalid notification pointer
      [/cover] */
      Ocu_lReportError(
        OCU_SID_DISABLENOTIFICATION,
        OCU_E_NO_VALID_NOTIF);/* End of report Error */

      #endif
    }
    else

    {
      /* Channel specific status variable */
      ChannelStatusPtr = &(Ocu_RootChannelVar[CoreId][CoreChIndex].Status);

      /* Enter critical section */
      SchM_Enter_Ocu_EnDisCCU1Irq();

      /* [cover parentID={0DF3B903-25C6-4d16-A7D4-6D8087F6E660}]
      Is channel valid?
      [/cover] */
      /* Are notifications enabled ? */
      if (OCU_ENABLE_NOTIFICATION
          == Mcal_GetBitAtomic(*ChannelStatusPtr, OCU_CHNL_NOTIF_PRESENCE_POS,
                               OCU_CHNL_NOTIF_BIT_LENGTH))
      {
        /* Disable interrupts to stop issuing notifications */
        Ocu_lEnDisCCU1Irq(LocalOcuChanPtr->OcuProperties.AssignedHwUnit,
                          LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber, DISABLE_INTERRUPTS);
        /* Disable notifications */
        Mcal_SetBitAtomic((ChannelStatusPtr),
                          OCU_CHNL_NOTIF_PRESENCE_POS, OCU_CHNL_NOTIF_BIT_LENGTH,
                          (uint32)OCU_DISABLE_NOTIFICATION);
      }

      /*End Critical section */
      SchM_Exit_Ocu_EnDisCCU1Irq();

    }
  }
  /* [cover parentID={DD15BFCB-9595-40fe-AC4C-93C9FEBCC9F2}]
    OCU Interrupt Control Registers.
  [/cover] */
  /* MISRA2012_RULE_2_2_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer ChannelStatusPtr is
   * accessed using assembly instruction. */
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer ChannelStatusPtr is
   * accessed using assembly instruction. */
}/* End of Ocu_DisableNotification() function */
#endif

#if (OCU_SET_PIN_ACTION_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={915DA69E-C200-4659-A88C-4EA01E155149}]      **
**                                                                            **
** Syntax : void Ocu_SetPinAction( const Ocu_ChannelType ChannelNumber,       **
**                                 const Ocu_PinActionType PinAction)         **
**                                                                            **
** Description : This service will set the pin action to be performed on next **
**               compare match                                                **
**                                                                            **
**                                                                            **
** [/cover]                                                                   **
** Service ID:       0x05                                                     **
*                                                                             **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  ChannelNumber - Numeric identifier of the OCU channel    **
**                   PinAction - Pin action to be performed on next compare   **
**                               match                                        **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={7F5A4CE6-A065-494e-9B74-0654A5CB52D1}]
Safety Properties
[/cover]*/
void Ocu_SetPinAction( const Ocu_ChannelType ChannelNumber,
                       const Ocu_PinActionType PinAction)
{
  #if (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON)
  uint32 ErrorFlag;
  #endif
  const Ocu_ChannelConfigType *LocalOcuChanPtr; /* ROM pointer */
  uint32* ChannelStatusPtr;
  uint8 CoreId;
  uint8 CoreChIndex;

  /* Get core id which is executing currently */
  CoreId = OCU_GETCOREID();
  /* [cover parentID={A4CAFA85-6643-448b-9A96-FFD4461B8716}]
  If DET or Safety is enabled
  [/cover] */
  #if (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={D79F518B-5D42-464f-BD5C-D8E118F85BC9}]
  Verify if Ocu_Init is invoked.
  [/cover] */
  ErrorFlag = Ocu_lInitCallVerify(OCU_SID_SETPINACTION, CoreId);
  /* [cover parentID={99C28CD3-CFFF-4b14-9D91-3145A94C6320}]
  Is Ocu_Init invoked
  [/cover] */
  if (ErrorFlag != OCU_ERROR_FOUND)
  {
    /* [cover parentID={AE8FB6B7-0054-4310-BBBB-FE26958B236F}]
    Verify if channel is valid
    [/cover] */
    ErrorFlag = Ocu_lChannelVerify(OCU_SID_SETPINACTION, ChannelNumber, CoreId);
  }
  /* [cover parentID={503DD49B-5F1E-48f2-A48E-AC66E868B964}]
  Is channel valid
  [/cover] */
  /* [cover parentID={1CCB422B-538E-4182-B4DB-2F88909674A9}]
  Is the pin action valid
  [/cover] */
  if ((ErrorFlag != OCU_ERROR_FOUND) && ((uint32)PinAction > (uint32)OCU_TOGGLE))
  {
    /* [cover parentID={900AF6F0-6244-401b-B145-99889FBAA37A}]
    Report error to indicate the invalid action.
    [/cover] */
    Ocu_lReportError(
      OCU_SID_SETPINACTION,
      OCU_E_PARAM_INVALID_ACTION);/* End of report Error */
    ErrorFlag = OCU_ERROR_FOUND;
  }
  if (ErrorFlag != OCU_ERROR_FOUND)
  #endif
  {
    #if (OCU_SINGLE_CORE == STD_OFF)
    /* Initialize OCU configured channel ROM pointer */
    CoreChIndex = (uint8)(Ocu_ConfigPtr->ChannelMapping[ChannelNumber] & \
                          OCU_CHNL_MAP_CHNL_INDEX_MASK);
    #else
    CoreChIndex = (uint8)ChannelNumber;
    #endif




    LocalOcuChanPtr = &((Ocu_ConfigPtr->CoreConfig[CoreId]->ChannelConfigPtr)\
                        [CoreChIndex]);
    #if (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON)
    /* [cover parentID={510C7A1E-E1D8-4d68-B610-A3DE0C745E04}]
    Is the channel assigned a pin
    [/cover] */
    if (LocalOcuChanPtr->OcuProperties.PinUsed == FALSE)
    {
      /* [cover parentID={D0B86095-8B85-4512-A1B5-86E44D9D4E21}]
      Report an error to indicate that channel has not assigned a pin.
      [/cover] */
      Ocu_lReportError(
        OCU_SID_SETPINACTION,
        OCU_E_PARAM_NO_PIN);/* End of report Error */
    }
    else
    #endif
    {
      /* Channel specific status variable */
      ChannelStatusPtr = &(Ocu_RootChannelVar[CoreId][CoreChIndex].Status);

      /* [cover parentID={3C4390BB-89D0-4abd-A0C8-FD8DA5C46E3C}]
      Enter critical section
      [/cover] */
      SchM_Enter_Ocu_SetPinAction();

      /* [cover parentID={1444988E-2105-4f55-A8E5-1B30EADD6F25}]
      * If the channel is RUNNING update pin action as per the HW
      * configuration
      [/cover] */

      if(OCU_CHANNEL_RUNNING ==
          Mcal_GetBitAtomic(*ChannelStatusPtr, OCU_CHNL_STATUS_POS, \
                            OCU_CHNL_STATUS_BIT_LENGTH))
      {

        /* [cover parentID={267C14D5-FA9A-425b-B7EA-317CDA1CB949}]
               If the channel's next compare match is not for reprogramming
        [/cover] */
        if (OCU_BIT_SET
            != Mcal_GetBitAtomic(*ChannelStatusPtr, OCU_CHNL_ATOM_RE_PROG_ISR_POS,
                                 OCU_CHNL_ATOM_RE_PROG_ISR_BIT_LENGTH))
        {
          /* Update ACB for compare match */
          Ocu_lSetAtomPinAction(\
                                LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber, \
                                (uint8)PinAction);
        }
      }

      /* [cover parentID={454F9F5D-7C4A-4fa7-A8A9-7DC5217698DE}]
        Update the channel Status register with PinAction
        [/cover] */
      /* Update pin action */
      Mcal_SetBitAtomic((ChannelStatusPtr),
                        OCU_CHNL_PIN_ACTION_POS, OCU_CHNL_PIN_ACTION_BIT_LENGTH, \
                        (uint32)PinAction);


      /*End Critical section to update ACB for compare match */
      /* Exit critical section*/

      SchM_Exit_Ocu_SetPinAction();

    }
  }
  /* [cover parentID={DD15BFCB-9595-40fe-AC4C-93C9FEBCC9F2}]
    OCU Interrupt Control Registers.
  [/cover] */
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer ChannelStatusPtr is
   * accessed using assembly instruction. */
  /* MISRA2012_RULE_2_2_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the variable AcbValue is
   * accessed using assembly instruction. */
}/* End of Ocu_SetPinAction() function */
#endif

#if (OCU_SET_PIN_STATE_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={D868CE53-D17B-4d11-8A19-507BE32D6FA0}]      **
**                                                                            **
** Syntax : void Ocu_SetPinState( const Ocu_ChannelType ChannelNumber,        **
**                                 const Ocu_PinStateType PinAction)          **
**                                                                            **
** Description : This service will set the pin state immediately              **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x04                                                     **
*                                                                             **
**                                                                            **
** Reentrancy:       Reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  ChannelNumber - Numeric identifier of the OCU channel    **
**                   PinState - Pin state to be set                           **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
** Sync/Async:       Synchronous                                              **
**                                                                            **
*******************************************************************************/
/*[cover parentID={7F5A4CE6-A065-494e-9B74-0654A5CB52D1}]
Safety Properties
[/cover]*/
void Ocu_SetPinState( const Ocu_ChannelType ChannelNumber,
                      const Ocu_PinStateType PinState)
{
  #if (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON)
  uint32 ErrorFlag;
  uint32* ChannelStatusPtr;
  #endif
  const Ocu_ChannelConfigType *LocalOcuChanPtr; /* ROM pointer */
  uint8 CoreId;
  uint8 CoreChIndex;
  /* Pointer to ATOM channel Register */
  Ifx_GTM_ATOM_CH *AtomChannelRegPtr;
  /* Get core id which is executing currently */
  CoreId = OCU_GETCOREID();
  /* [cover parentID={0660169D-94D9-44dd-AD5D-9AED13696CAE}]
  If DET or Safety is enabled
  [/cover] */
  #if (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={1EBAE801-54DE-4504-9F49-E1DF5253391F}]
  Verify if Ocu_Init is invoked.
  [/cover] */
  ErrorFlag = Ocu_lInitCallVerify(OCU_SID_SETPINSTATE, CoreId);
  /* [cover parentID={FF47311B-7B37-4f1e-AC60-F56A59FD15D5}]
  Is Ocu_Init invoked
  [/cover] */
  if (ErrorFlag != OCU_ERROR_FOUND)
  {
    /* [cover parentID={C9B6CB32-1A8B-4bf5-863C-6A9339A99E72}]
    Verify if channel is valid
    [/cover] */
    ErrorFlag = Ocu_lChannelVerify(OCU_SID_SETPINSTATE, ChannelNumber, CoreId);
  }
  /* [cover parentID={31A4909B-7D90-4bf4-9E8D-AF8C22652E1E}]
  Is channel valid
  [/cover] */
  /* [cover parentID={FCF23FE9-EFDD-47b7-AB7F-9F7DBB3B182D}]
  Is the pin state valid
  [/cover] */
  if ((ErrorFlag != OCU_ERROR_FOUND) && ((uint32)PinState > (uint32)OCU_HIGH))
  {
    /* [cover parentID={AE15E9BE-0067-496d-B58C-0582624C4AFC}]
    Report error to indicate the invalid state
    [/cover] */
    Ocu_lReportError(
      OCU_SID_SETPINSTATE,
      OCU_E_PARAM_INVALID_STATE);/* End of report Error */
    ErrorFlag = OCU_ERROR_FOUND;
  }
  if (ErrorFlag != OCU_ERROR_FOUND)
  #endif
    /* #if  (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON) */
  {
    #if (OCU_SINGLE_CORE == STD_OFF)
    /* Initialize OCU configured channel ROM pointer */
    CoreChIndex = (uint8)(Ocu_ConfigPtr->ChannelMapping[ChannelNumber] & \
                          OCU_CHNL_MAP_CHNL_INDEX_MASK);
    #else
    CoreChIndex = (uint8)ChannelNumber;
    #endif




    LocalOcuChanPtr = &((Ocu_ConfigPtr->CoreConfig[CoreId]->ChannelConfigPtr)\
                        [CoreChIndex]);
    #if (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON)
    /* [cover parentID={97AC5781-9CF3-4001-A41F-489EFB34273A}]
    Is the channel assigned a pin?
    [/cover] */
    if (LocalOcuChanPtr->OcuProperties.PinUsed == FALSE)
    {
      /* [cover parentID={C66F2095-981D-4e72-9B2A-638DD7DDC3C9}]
      Report an error to indicate that channel has not assigned a pin.
      [/cover] */
      Ocu_lReportError(
        OCU_SID_SETPINSTATE,
        OCU_E_PARAM_NO_PIN);/* End of report Error */
    }
    else
    #endif
    {
      /* Channel specific status variable */
      #if (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON)
      ChannelStatusPtr = &(Ocu_RootChannelVar[CoreId][CoreChIndex].Status);
      /* Is the channel state RUNNING */
      /* [cover parentID={1BA8E884-14A3-4d01-A0AF-3E743B1B644F}]
      Is the channel started
      [/cover] */
      if(OCU_CHANNEL_RUNNING ==
          Mcal_GetBitAtomic(*ChannelStatusPtr, OCU_CHNL_STATUS_POS, \
                            OCU_CHNL_STATUS_BIT_LENGTH))
      {
        /* [cover parentID={FFBB0A40-3B14-4ca0-ACD9-515742059107}]
        Report an error to indicate invalid channel state
        [/cover] */
        Ocu_lReportError(
          OCU_SID_SETPINSTATE,
          OCU_E_PARAM_INVALID_STATE);/* End of report Error */
      }
      else
      #endif
      {
        /* Set the pin state of TOM/ATOM channel */
        /* MISRA2012_RULE_11_3_JUSTIFICATION: GTM_ATOM_CH_POINTER does a typecast
         * to void and then to specific Mcu datatype Mcu_17_Gtm_AtomChArray to 
         * index to the proper ATOM channel's SFR from the base GTM SFR. 
         * No side effects seen by violating this MISRA */
        /* MISRA2012_RULE_11_5_JUSTIFICATION: GTM_ATOM_CH_POINTER does a typecast
         * to void and then to specific Mcu datatype Mcu_17_Gtm_AtomChArray to 
         * index to the proper ATOM channel's SFR from the base GTM SFR. 
         * No side effects seen by violating this MISRA */



        AtomChannelRegPtr = GTM_ATOM_CH_POINTER((uint8)(\
                                                (LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber & \
                                                    GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF), \
                                                (uint8)((LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber & \
                                                    GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF));


        /* Update SL to change the pin state */
        Mcal_SetBitAtomic(&(AtomChannelRegPtr->SOMC.U),
                          OCU_GTM_ATOM_SL_BIT_POS, OCU_GTM_ATOM_SL_LENGTH,
                          ((uint32)PinState & 1U));
      }
    }
  }
  
  UNUSED_PARAMETER(PinState);
  
  /* [cover parentID={DD15BFCB-9595-40fe-AC4C-93C9FEBCC9F2}]
    OCU Interrupt Control Registers.
  [/cover] */
  /* MISRA2012_RULE_2_2_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer AtomChannelRegPtr is
   * accessed using assembly instruction. */
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer ChannelStatusPtr is
   * accessed using assembly instruction. */
}/* End of Ocu_SetPinState() function */
#endif

/*******************************************************************************
** Traceability: [cover parentID={FDEC58BE-7455-4e5b-84A4-95D77993E7AE}]      **
**                                                                            **
** Syntax : void Ocu_StartChannel( const Ocu_ChannelType ChannelNumber)       **
**                                                                            **
** Description : This service will start the OCU channel                      **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x02                                                     **
*                                                                             **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  ChannelNumber - Numeric identifier of the OCU channel    **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={7F5A4CE6-A065-494e-9B74-0654A5CB52D1}]
Safety Properties
[/cover]*/
void Ocu_StartChannel( const Ocu_ChannelType ChannelNumber)
{
  const Ocu_ChannelConfigType *LocalOcuChanPtr; /* ROM pointer */
  uint32* ChannelStatusPtr;
  #if (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON)
  uint32 ErrorFlag;
  #endif
  Ocu_ValueType CounterValue;
  Ocu_ValueType AbsoluteValue;
  uint8 CoreId;
  uint8 CoreChIndex;
  uint8 PinAction;
  /* Pointer to ATOM channel Register */
  Ifx_GTM_ATOM_CH *AtomChannelRegPtr;
  /* Get core id which is executing currently */
  CoreId = OCU_GETCOREID();
  /* [cover parentID={FDA18B1B-468F-49bc-B1FA-7DE87F4E1A76}]
  If DET or Safety is enabled
  [/cover] */
  #if (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={240985AE-CDFF-4516-99A6-0A4D019670DA}]
  Verify if Ocu_Init is invoked.
  [/cover] */
  ErrorFlag = Ocu_lInitCallVerify(OCU_SID_STARTCHANNEL, CoreId);
  /* [cover parentID={6DAD71FA-51F6-4171-A08B-C2063AB3F3E2}]
  Is Ocu_Init invoked
  [/cover] */
  if (ErrorFlag != OCU_ERROR_FOUND)
  {
    /* [cover parentID={1EDF6789-B31C-4c8b-AF19-B2AC337F7C16}]
    Verify if channel is valid
    [/cover] */
    ErrorFlag = Ocu_lChannelVerify(OCU_SID_STARTCHANNEL, ChannelNumber, CoreId);
  }
  /* [cover parentID={EF503E5F-0C87-4283-AF20-EDBA4E07D70E}]
  Is channel valid
  [/cover] */
  if (ErrorFlag != OCU_ERROR_FOUND)
  #endif
    /* #if  (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON) */
  {
    #if (OCU_SINGLE_CORE == STD_OFF)
    /* Initialize OCU configured channel ROM pointer */
    CoreChIndex = (uint8)(Ocu_ConfigPtr->ChannelMapping[ChannelNumber] & \
                          OCU_CHNL_MAP_CHNL_INDEX_MASK);
    #else
    CoreChIndex = (uint8)ChannelNumber;
    #endif




    LocalOcuChanPtr = &((Ocu_ConfigPtr->CoreConfig[CoreId]->ChannelConfigPtr)\
                        [CoreChIndex]);
    /* Channel specific status variable */
    ChannelStatusPtr = &(Ocu_RootChannelVar[CoreId][CoreChIndex].Status);
    #if (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON)
    /* [cover parentID={5BA9D753-C3CD-4371-9AFE-CCE8DF1CE2AE}]
    Is the channel started
    [/cover] */
    if(OCU_CHANNEL_RUNNING ==
        Mcal_GetBitAtomic(*ChannelStatusPtr, OCU_CHNL_STATUS_POS, \
                          OCU_CHNL_STATUS_BIT_LENGTH))
    {
      /* [cover parentID={96867152-7247-4ea6-97D0-758C157BEED0}]
      Report error to indicate the channel is busy
      [/cover] */
      Ocu_lReportError(
        OCU_SID_STARTCHANNEL,
        OCU_E_BUSY);/* End of report Error */
    }
    else
    #endif
    {
      Mcal_SetBitAtomic((ChannelStatusPtr), \
                        OCU_CHNL_STATUS_POS, OCU_CHNL_STATUS_BIT_LENGTH, \
                        (uint32)OCU_CHANNEL_START_IN_PROGRESS);

      /* [cover parentID={C3FBFFC2-FCBB-459d-B5AA-66C3FC09D447}]
      Is the channel using ATOM with shared counter or
      TOM/ATOM - SOMP Mode
      [/cover] */
      switch(LocalOcuChanPtr->OcuProperties.AssignedHwUnit)
      {
        case OCU_GTM_ATOM_SHARED:
          /* calculate HW pin action */
          PinAction = (uint8)(Mcal_GetBitAtomic(*ChannelStatusPtr, \
                                                OCU_CHNL_PIN_ACTION_POS, OCU_CHNL_PIN_ACTION_BIT_LENGTH));

          /* Start ATOM-SOMC compare matches */
          AbsoluteValue = Ocu_RootChannelVar[CoreId][CoreChIndex].CompareValue;


        /* MISRA2012_RULE_11_3_JUSTIFICATION: GTM_ATOM_CH_POINTER does a typecast
         * to void and then to specific Mcu datatype Mcu_17_Gtm_AtomChArray to 
         * index to the proper ATOM channel's SFR from the base GTM SFR. 
         * No side effects seen by violating this MISRA */
        /* MISRA2012_RULE_11_5_JUSTIFICATION: GTM_ATOM_CH_POINTER does a typecast
         * to void and then to specific Mcu datatype Mcu_17_Gtm_AtomChArray to 
         * index to the proper ATOM channel's SFR from the base GTM SFR. 
         * No side effects seen by violating this MISRA */



          AtomChannelRegPtr = GTM_ATOM_CH_POINTER((uint8)(\
                                                  (LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber & \
                                                      GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF), \
                                                  (uint8)((LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber & \
                                                      GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF));
          /* Clear ATOM channel interrupt notification flag*/
          AtomChannelRegPtr->IRQ.NOTIFY.U = GTM_CLR_PENDING_IRQ; /* Clear flags */

          /* Enter critical section*/
          SchM_Enter_Ocu_SetThresholdValue();


          CounterValue = Ocu_lGetCounter(
                           LocalOcuChanPtr->OcuProperties.AssignedHwUnit,
                           LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber,
                           LocalOcuChanPtr->OcuProperties.ClockSelect);

          /* [cover parentID={692920FC-7073-482a-99AF-FC17FC02FD00}]
          Is the compare value within the past half range of counter value?
          [/cover] */
          if(((CounterValue - AbsoluteValue) & (ATOM_MASK_LSB_24BITS)) >= CNT_BORDER_VAL_BT_PAST_FUTURE)
          {
            Mcal_SetBitAtomic((ChannelStatusPtr), \
                              OCU_CHNL_ATOM_RE_PROG_ISR_POS, \
                              OCU_CHNL_ATOM_RE_PROG_ISR_BIT_LENGTH, \
                              (uint32)OCU_BIT_RESET);
            /* Set a compare match at compare value */
            (void)Ocu_lSetAtomCompare(AbsoluteValue, 0, LocalOcuChanPtr, \
                                      PinAction, ChannelNumber);
          }
          else
          {
            /* Set a flag to indicate a re-programming of channel is needed in
             * ISR.*/
            Mcal_SetBitAtomic((ChannelStatusPtr), \
                              OCU_CHNL_ATOM_RE_PROG_ISR_POS, \
                              OCU_CHNL_ATOM_RE_PROG_ISR_BIT_LENGTH, (uint32)OCU_BIT_SET);
            /* Set a compare match at an intermediate value */
            (void)Ocu_lSetAtomCompare(\
                                      ((AbsoluteValue + CNT_BORDER_VAL_BT_PAST_FUTURE) & \
                                       (ATOM_MASK_LSB_24BITS)), \
                                      0, LocalOcuChanPtr, (uint8)OCU_DISABLE,
                                      ChannelNumber);
          }
          /*End Critical section */
          SchM_Exit_Ocu_SetThresholdValue();
          /* Enable ATOM Channel */
          Mcu_17_Gtm_AtomChEndisCtrlUpdate( \
                                            (uint8)((LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber & \
                                                GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF), \
                                            (uint8)((LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber & \
                                                GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF),
                                            MCU_ENABLE_ON_TRIGGER);

          Mcu_17_Gtm_AtomChEndisStatUpdate( \
                                            (uint8)((LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber & \
                                                GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF), \
                                            (uint8)((LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber & \
                                                GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF),
                                            MCU_GTM_TIMER_ENABLE);
          /* Set channel to running state atomically*/
          Mcal_SetBitAtomic((ChannelStatusPtr), \
                            OCU_CHNL_STATUS_POS, OCU_CHNL_STATUS_BIT_LENGTH, \
                            (uint32)OCU_CHANNEL_RUNNING);
          break;
        default:
          /* Enter critical section */
          SchM_Enter_Ocu_EnDisCCU1Irq();
          /* If notification is enabled or DMA is configured,
           * interrupts are required */
          /* [cover parentID={CC8017A6-09C5-4241-AE8A-3BF63F53C572}]
          Are notifications enabled or DMA configured for the channel
          [/cover] */
          if((OCU_ENABLE_NOTIFICATION == Mcal_GetBitAtomic(*ChannelStatusPtr, \
              OCU_CHNL_NOTIF_PRESENCE_POS, OCU_CHNL_NOTIF_BIT_LENGTH)) || \
              (TRUE == LocalOcuChanPtr->OcuProperties.DmaUsed))
          {
            /* Enable interrupts to start issuing notifications or triggering
             * DMA*/
            Ocu_lEnDisCCU1Irq(LocalOcuChanPtr->OcuProperties.AssignedHwUnit, \
                              LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber, ENABLE_INTERRUPTS);
          }
          /* Set channel to running state atomically*/
          Mcal_SetBitAtomic((ChannelStatusPtr), \
                            OCU_CHNL_STATUS_POS, OCU_CHNL_STATUS_BIT_LENGTH, \
                            (uint32)OCU_CHANNEL_RUNNING);

          /*End Critical section */
          SchM_Exit_Ocu_EnDisCCU1Irq();

          break;
      }


    }
  }
  /* [cover parentID={DD15BFCB-9595-40fe-AC4C-93C9FEBCC9F2}]
    OCU Interrupt Control Registers.
  [/cover] */
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer ChannelStatusPtr is
   * accessed using assembly instruction. */
}/* End of Ocu_StartChannel() function */

/*******************************************************************************
** Traceability: [cover parentID={6E3578E9-D4D6-41cd-BFD9-0260AFE2F143}]      **
**                                                                            **
** Syntax : void Ocu_StopChannel( const Ocu_ChannelType ChannelNumber)        **
**                                                                            **
** Description : This service will stop the OCU channel                       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x03                                                     **
*                                                                             **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  ChannelNumber - Numeric identifier of the OCU channel    **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={7F5A4CE6-A065-494e-9B74-0654A5CB52D1}]
Safety Properties
[/cover]*/
void Ocu_StopChannel( const Ocu_ChannelType ChannelNumber)
{
  #if (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON)
  uint32 ErrorFlag;
  #endif
  const Ocu_ChannelConfigType *LocalOcuChanPtr; /* ROM pointer */
  uint32* ChannelStatusPtr;
  uint8 CoreId;
  uint8 CoreChIndex;
  /* Pointer to ATOM channel Register */
  Ifx_GTM_ATOM_CH *AtomChannelRegPtr;
  /* Get core id which is executing currently */
  CoreId = OCU_GETCOREID();
  /* [cover parentID={63B5E135-4AD4-4555-B6FC-90D6F8A09EF8}]
  If DET or Safety is enabled
  [/cover] */
  #if (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={4A9412C6-29E7-4ee0-BFDE-8916F0ED5AC8}]
  Verify if Ocu_Init is invoked.
  [/cover] */

  ErrorFlag = Ocu_lInitCallVerify(OCU_SID_STOPCHANNEL, CoreId);
  /* [cover parentID={EF70AA93-6466-41a7-AAF5-F34A70877BAD}]
  Is Ocu_Init invoked
  [/cover] */
  if (ErrorFlag != OCU_ERROR_FOUND)
  {
    /* [cover parentID={47DD9499-B47A-498b-8C21-2464934919B0}]
    Verify if channel is valid
    [/cover] */
    ErrorFlag = Ocu_lChannelVerify(OCU_SID_STOPCHANNEL, ChannelNumber, CoreId);
  }
  /* [cover parentID={A8F5C497-1342-4a96-B803-878F94A56660}]
  Is channel valid
  [/cover] */
  if (ErrorFlag != OCU_ERROR_FOUND)
  #endif
  {
    #if (OCU_SINGLE_CORE == STD_OFF)
    /* Initialize OCU configured channel ROM pointer */
    CoreChIndex = (uint8)(Ocu_ConfigPtr->ChannelMapping[ChannelNumber] & \
                          OCU_CHNL_MAP_CHNL_INDEX_MASK);
    #else
    CoreChIndex = (uint8)ChannelNumber;
    #endif




    LocalOcuChanPtr = &((Ocu_ConfigPtr->CoreConfig[CoreId]->ChannelConfigPtr)\
                        [CoreChIndex]);
    /* Channel specific status variable */
    ChannelStatusPtr = &(Ocu_RootChannelVar[CoreId][CoreChIndex].Status);
    /* [cover parentID={1C4425EC-D4F1-4d3d-A159-E23A24D60047}]
    Is the channel started
    [/cover] */
    if(OCU_CHANNEL_RUNNING ==
        Mcal_GetBitAtomic(*ChannelStatusPtr, OCU_CHNL_STATUS_POS, \
                          OCU_CHNL_STATUS_BIT_LENGTH))
    {
      /* Stop TOM/ATOM channel. TOM and ATOM-SOMP, disable the interrupts
       * ATOM-SOMC disable interrupts and set ACB to 0x1C*/
      /* Start TOM/ATOM channel */

      /* [cover parentID={DAE48B9A-52F8-469f-8E0C-EFCA4BC1FC9E}]
        Is the channel using ATOM with shared counter or
      TOM/ATOM - SOMP Mode
      [/cover] */
      switch(LocalOcuChanPtr->OcuProperties.AssignedHwUnit)
      {
        case OCU_GTM_ATOM_SHARED:
          /* MISRA2012_RULE_11_3_JUSTIFICATION: GTM_ATOM_CH_POINTER does a typecast
           * to void and then to specific Mcu datatype Mcu_17_Gtm_AtomChArray to 
           * index to the proper ATOM channel's SFR from the base GTM SFR. 
           * No side effects seen by violating this MISRA */
          /* MISRA2012_RULE_11_5_JUSTIFICATION: GTM_ATOM_CH_POINTER does a typecast
           * to void and then to specific Mcu datatype Mcu_17_Gtm_AtomChArray to 
           * index to the proper ATOM channel's SFR from the base GTM SFR. 
           * No side effects seen by violating this MISRA */



          AtomChannelRegPtr = GTM_ATOM_CH_POINTER((uint8)(\
                                                  (LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber & \
                                                      GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF), \
                                                  (uint8)((LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber & \
                                                      GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF));
          /*Disable compare operation*/
          Mcal_SetBitAtomic(&(AtomChannelRegPtr->SOMC.U), \
                            OCU_ATOM_SOMC_ACB_4_3_2_POS, OCU_ATOM_SOMC_ACB_4_3_2_LEN, \
                            OCU_ATOM_SOMC_ACB_CANCEL_COMPARISIONS);
          AtomChannelRegPtr->IRQ.NOTIFY.U = GTM_CLR_PENDING_IRQ; /* Clear flags */
          /*To avoide Output Signal Level change/glitch - Modify the SL */
          /*bit according to the OL(output signal level )               */
          if(AtomChannelRegPtr->STAT.B.OL == OCU_BIT_SET)
          {
            Mcal_SetBitAtomic(&(AtomChannelRegPtr->SOMC.U),
                              OCU_GTM_ATOM_SL_BIT_POS, OCU_GTM_ATOM_SL_LENGTH,
                              OCU_BIT_SET);
          }
          else
          {
            Mcal_SetBitAtomic(&(AtomChannelRegPtr->SOMC.U),
                              OCU_GTM_ATOM_SL_BIT_POS, OCU_GTM_ATOM_SL_LENGTH,
                              OCU_BIT_RESET);
          }
          /* Disable ATOM Channel */
          Mcu_17_Gtm_AtomChEndisCtrlUpdate( \
                                            (uint8)((LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber & \
                                                GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF), \
                                            (uint8)((LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber & \
                                                GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF),
                                            MCU_DISABLE_ON_TRIGGER);
          Mcu_17_Gtm_AtomChEndisStatUpdate( \
                                            (uint8)((LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber & \
                                                GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF), \
                                            (uint8)((LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber & \
                                                GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF),
                                            MCU_GTM_TIMER_DISABLE);
          /* [cover parentID={3303E358-3A83-4e07-9A14-FBB6DCC7043E}]
              Set channel state to STOPPED atomically
              [/cover] */
          Mcal_SetBitAtomic((ChannelStatusPtr), \
                            OCU_CHNL_STATUS_POS, OCU_CHNL_STATUS_BIT_LENGTH, \
                            (uint32)OCU_CHANNEL_STOPPED);
          break;
        default:
          /* Enter critical section */
          SchM_Enter_Ocu_EnDisCCU1Irq();
          /* ATOM SOMP and TOM */
          /* Disable interrupts to stop issuing interrupts */
          Ocu_lEnDisCCU1Irq(LocalOcuChanPtr->OcuProperties.AssignedHwUnit, \
                            LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber, DISABLE_INTERRUPTS);


          /* [cover parentID={3303E358-3A83-4e07-9A14-FBB6DCC7043E}]
              Set channel state to STOPPED atomically
              [/cover] */
          Mcal_SetBitAtomic((ChannelStatusPtr), \
                            OCU_CHNL_STATUS_POS, OCU_CHNL_STATUS_BIT_LENGTH, \
                            (uint32)OCU_CHANNEL_STOPPED);


          /*End Critical section */
          SchM_Exit_Ocu_EnDisCCU1Irq();

          break;
      }
    }
  }
  /* [cover parentID={DD15BFCB-9595-40fe-AC4C-93C9FEBCC9F2}]
    OCU Interrupt Control Registers.
  [/cover] */
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer ChannelStatusPtr is
   * accessed using assembly instruction. */
}/* End of Ocu_StopChannel() function */

#if (OCU_GET_COUNTER_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={2CA341B3-1178-45a0-A1E3-C9534EC37AB5}]      **
**                                                                            **
** Syntax : Ocu_ValueType Ocu_GetCounter( const Ocu_ChannelType ChannelNumber)**
**                                                                            **
** Description : This service will return current counter value               **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x06                                                     **
*                                                                             **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  ChannelNumber - Numeric identifier of the OCU channel    **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     Ocu_ValueType - Counter value                            **
**                                                                            **
*******************************************************************************/
/*[cover parentID={7F5A4CE6-A065-494e-9B74-0654A5CB52D1}]
Safety Properties
[/cover]*/
Ocu_ValueType Ocu_GetCounter( const Ocu_ChannelType ChannelNumber)
{
  #if (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON)
  uint32 ErrorFlag;
  #endif
  const Ocu_ChannelConfigType *LocalOcuChanPtr; /* ROM pointer */
  Ocu_ValueType CounterValue;
  uint8 CoreId;
  uint8 CoreChIndex;
  /* Get core id which is executing currently */
  CoreId = OCU_GETCOREID();
  /* [cover parentID={C067E6F3-CAC7-4eea-9A3F-690CDB9001C7}]
  If DET or Safety is enabled
  [/cover] */
  #if (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={5E719493-7CA7-48fe-A2E3-C159BF1266D3}]
  Initialize the return value to zero
  [/cover] */
  CounterValue = 0U;
  /* [cover parentID={69ED2CFC-90BD-43e4-AD2C-90F3312AA1A6}]
  Verify if Ocu_Init is invoked.
  [/cover] */
  ErrorFlag = Ocu_lInitCallVerify(OCU_SID_GETCOUNTER, CoreId);
  /* [cover parentID={57850264-3A74-449d-97FA-7F3116F7A428}]
  Is Ocu_Init invoked
  [/cover] */
  if (ErrorFlag != OCU_ERROR_FOUND)
  {
    /* [cover parentID={B393E19E-B535-4273-8669-520D4AC99667}]
    Verify if channel is valid
    [/cover] */
    ErrorFlag = Ocu_lChannelVerify(OCU_SID_GETCOUNTER, ChannelNumber, CoreId);
  }
  /* [cover parentID={740B3CA0-876A-4179-9BDA-D5046E277852}]
  Is channel valid
  [/cover] */
  if (ErrorFlag != OCU_ERROR_FOUND)
  #endif
  {
    #if (OCU_SINGLE_CORE == STD_OFF)
    /* Initialize OCU configured channel ROM pointer */
    CoreChIndex = (uint8)(Ocu_ConfigPtr->ChannelMapping[ChannelNumber] & \
                          OCU_CHNL_MAP_CHNL_INDEX_MASK);
    #else
    CoreChIndex = (uint8)ChannelNumber;
    #endif




    LocalOcuChanPtr = &((Ocu_ConfigPtr->CoreConfig[CoreId]->ChannelConfigPtr)\
                        [CoreChIndex]);
    /* Read counter for TOM/ATOM channel */
    CounterValue =
      Ocu_lGetCounter(LocalOcuChanPtr->OcuProperties.AssignedHwUnit,
                      LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber,
                      LocalOcuChanPtr->OcuProperties.ClockSelect);
  }
  return (CounterValue);
  /* [cover parentID={DD15BFCB-9595-40fe-AC4C-93C9FEBCC9F2}]
    OCU Interrupt Control Registers.
  [/cover] */
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer ChannelStatusPtr is
   * accessed using assembly instruction. */
}/* End of Ocu_GetCounter() function */
#endif

#if (OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={CD61C85B-C24A-40a7-89C8-0360BAE7EBD3}]      **
**                                                                            **
** Syntax : Ocu_ValueType Ocu_SetAbsoluteThreshold(                           **
**                                   const Ocu_ChannelType ChannelNumber,     **
**                                   const Ocu_ValueType ReferenceValue,      **
**                                   const Ocu_ValueType AbsoluteValue )      **
**                                                                            **
** Description : This service will set the threshold using the absolute values**
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x07                                                     **
*                                                                             **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  ChannelNumber - Numeric identifier of the OCU channel    **
**                   ReferenceValue - Reference to identify if the compare    **
**                                    match occurs in the given interval      **
**                   AbsoluteValue - new compare value                        **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     Ocu_ReturnType - to indicate if the compare match occurs **
**                                    in reference interval.                  **
**                                                                            **
*******************************************************************************/
/*[cover parentID={7F5A4CE6-A065-494e-9B74-0654A5CB52D1}]
Safety Properties
[/cover]*/
Ocu_ReturnType Ocu_SetAbsoluteThreshold( const Ocu_ChannelType ChannelNumber,
    const Ocu_ValueType ReferenceValue, const Ocu_ValueType AbsoluteValue )
{
  #if (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON)
  uint32 ErrorFlag;
  #endif

  const Ocu_ChannelConfigType *LocalOcuChanPtr; /* ROM pointer */
  uint32* ChannelStatusPtr;
  /* Initialize return value to 0 */
  Ocu_ReturnType ReturnValue = OCU_CM_OUT_REF_INTERVAL;
  uint32 ReturnValue1;
  uint32 ReturnValue2;

  uint8 CoreId;
  uint8 CoreChIndex;
  Ocu_ValueType CounterValueRead1;
  Ocu_ValueType CounterValueRead2;
  Ocu_ValueType CounterValue;
  /* Pointer to ATOM channel Register */
  Ifx_GTM_ATOM_CH *AtomChannelRegPtr;
  /* Pointer to TOM channel Register */
  Ifx_GTM_TOM_CH *TomChannelRegPtr;
  /* Get core id which is executing currently */
  CoreId = OCU_GETCOREID();
  /* [cover parentID={9992BB6B-B4AE-47c2-AED1-2FA3733F160D}]
  If DET or Safety is enabled
  [/cover] */
  #if (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON)
  /* Verify any error is there for DET */
  ErrorFlag = Ocu_lInitCallVerify(OCU_SID_SETABSOLUTETHRESHOLD, CoreId);

  /* [cover parentID={FEEB81C9-583D-4d6d-B7C8-87B56B6BC6A1}]
  Is the Ocu_Init invoked?
  [/cover] */
  if (ErrorFlag != OCU_ERROR_FOUND)
  {
    ErrorFlag = Ocu_lChannelVerify(OCU_SID_SETABSOLUTETHRESHOLD, \
                                   ChannelNumber, CoreId);
  }
  /* [cover parentID={FADB828D-D6B0-41e1-8189-70BB928E7AF1}]
  Is channel valid and channel Initialized ?
  [/cover] */
  if (ErrorFlag != OCU_ERROR_FOUND)
  #endif
  {
    #if (OCU_SINGLE_CORE == STD_OFF)
    /* Initialize OCU configured channel ROM pointer */
    CoreChIndex = (uint8)(Ocu_ConfigPtr->ChannelMapping[ChannelNumber] & \
                          OCU_CHNL_MAP_CHNL_INDEX_MASK);
    #else
    CoreChIndex = (uint8)ChannelNumber;
    #endif




    LocalOcuChanPtr = &((Ocu_ConfigPtr->CoreConfig[CoreId]->ChannelConfigPtr)\
                        [CoreChIndex]);

    #if (OCU_SAFETY_ENABLE == STD_ON)
    /* [cover parentID={2F7C9BD9-0F9C-48d3-85FB-D49798A4E5CD}]
    Are RefernceValue and AbsoluteValue greater than MaxCounterValue?
    [/cover] */
    /* [cover parentID={6AA07C4B-E9A4-4e36-8C2D-0B453B581ECC}]
    Safety measures reporting safety errors
    [/cover] */
    /* [cover parentID={36D99C23-96C0-4b84-BFB3-E8BBB4DDAC4D}]
    Range check for input parameters
    [/cover] */


    if(ReferenceValue > LocalOcuChanPtr->MaxCounterValue)
    {

      Mcal_ReportSafetyError(
        OCU_MODULE_ID,
        OCU_INSTANCE_ID,
        OCU_SID_SETABSOLUTETHRESHOLD,
        (uint8)OCU_E_PARAM_REF_VALUE);/* End of report to Safety */
    }
    else if (AbsoluteValue > LocalOcuChanPtr->MaxCounterValue)
    {
      Mcal_ReportSafetyError(
        OCU_MODULE_ID,
        OCU_INSTANCE_ID,
        OCU_SID_SETABSOLUTETHRESHOLD,
        (uint8)OCU_E_PARAM_COMPARE_VALUE);/* End of report to Safety */
    }
    else
    #endif
    {
      /* Channel specific status variable */
      ChannelStatusPtr = &(Ocu_RootChannelVar[CoreId][CoreChIndex].Status);
      /* calculate and configure new absolute threshold */
      switch(LocalOcuChanPtr->OcuProperties.AssignedHwUnit)
      {
        /* For TOM & ATOM: counter value > new compare value,
         * set in shadow or else in CM1 */
        /* [cover parentID={07F046D1-A11B-4119-862D-CAFE7BDCCA9C}]
        Is the channel using TOM ?
        [/cover] */
        case OCU_GTM_TOM:
          /* MISRA2012_RULE_11_3_JUSTIFICATION: GTM_TOM_CH_POINTER does a typecast
           * to void and then to specific Mcu datatype Mcu_17_Gtm_TomChArray to 
           * index to the proper TOM channel's SFR from the base GTM SFR. 
           * No side effects seen by violating this MISRA */
          /* MISRA2012_RULE_11_5_JUSTIFICATION: GTM_TOM_CH_POINTER does a typecast
           * to void and then to specific Mcu datatype Mcu_17_Gtm_TomChArray to 
           * index to the proper TOM channel's SFR from the base GTM SFR. 
           * No side effects seen by violating this MISRA */
          TomChannelRegPtr = GTM_TOM_CH_POINTER( \
                                                 (uint8)((LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber & \
                                                     GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF), \
                                                 (uint8)((LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber & \
                                                     GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF));


          /* [cover parentID={A08BD4DA-40AF-421d-BC9F-9670B0141A21}]
          Enter critical section
          [/cover] */
          SchM_Enter_Ocu_SetThresholdValue();

          /* Read current counter value */
          CounterValueRead1 = TomChannelRegPtr->CN0.U;

          /* [cover parentID={D6C70CDF-BC1B-4a0e-B2A5-01DFF6D95A92}]
          Has the counter crossed compare value
          [/cover] */
          if(CounterValueRead1 > AbsoluteValue)
          {
            /* [cover parentID={B90D6A70-17F3-4559-B9AA-B5F289C5D846}]
            Update SR1 with Absolute value
            [/cover] */
            /* Update the TOM shadow register */
            TomChannelRegPtr->SR1.U = AbsoluteValue;
          }
          else
          {
            /* [cover parentID={CD1FECA5-28DC-42f7-B080-C5D0AC35174F}]
            Update CM1 and SR1 with Absolute value
            [/cover] */
            /* Update the TOM compare and shadow register */
            TomChannelRegPtr->SR1.U = AbsoluteValue;
            TomChannelRegPtr->CM1.U = AbsoluteValue;
          }

          /* Read current counter value */
          CounterValueRead2 = TomChannelRegPtr->CN0.U;
          /*End Critical section */
          SchM_Exit_Ocu_SetThresholdValue();


          ReturnValue1 = Ocu_lGetReturnValue(AbsoluteValue,
                                             CounterValueRead1, ReferenceValue,
                                             LocalOcuChanPtr->MaxCounterValue);

          ReturnValue2 = Ocu_lGetReturnValue(AbsoluteValue, CounterValueRead2, \
                                             ReferenceValue, LocalOcuChanPtr->MaxCounterValue);

          /* [cover parentID={C055A324-E062-48b1-81E8-7E01B28E8D46}]
           safety mechanisms for identifing the return value.
          [/cover] */
          /* [cover parentID={E2C1F899-31EF-411f-92D7-73D87FAEB8AC}]
          Identify and return if the compare match occurs in current reference inteval
          [/cover] */

          if((ReturnValue1 | ReturnValue2) == TRUE)
          {
            ReturnValue = OCU_CM_IN_REF_INTERVAL;
          }

          break;
        /* [cover parentID= {2E0E9F40-50BC-4998-AA05-CA8B718755C7}]
         Is the channel using ATOM ?
         [/cover] */

        case OCU_GTM_ATOM:
          /* MISRA2012_RULE_11_3_JUSTIFICATION: GTM_ATOM_CH_POINTER does a typecast
          * to void and then to specific Mcu datatype Mcu_17_Gtm_AtomChArray to 
          * index to the proper ATOM channel's SFR from the base GTM SFR. 
          * No side effects seen by violating this MISRA */
         /* MISRA2012_RULE_11_5_JUSTIFICATION: GTM_ATOM_CH_POINTER does a typecast
          * to void and then to specific Mcu datatype Mcu_17_Gtm_AtomChArray to 
          * index to the proper ATOM channel's SFR from the base GTM SFR. 
          * No side effects seen by violating this MISRA */



          AtomChannelRegPtr = GTM_ATOM_CH_POINTER( \
                              (uint8)((LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber & \
                                       GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF), \
                              (uint8)((LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber & \
                                       GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF));

          /* [cover parentID={D17E932E-FFC1-4f1a-A08A-11E8F90C61FC}]
          Enter critical section
          [/cover] */
          SchM_Enter_Ocu_SetThresholdValue();


          /* Read current counter value */
          CounterValueRead1 = AtomChannelRegPtr->CN0.U;


          /* [cover parentID={ADB3AEB9-FED3-4339-AFE7-21DDD7A90555}]
          Has the counter crossed compare value
          [/cover] */
          if(CounterValueRead1 > AbsoluteValue)
          {
            /* [cover parentID={087E6D95-A5B3-4e30-BEB7-F862F444E25D}]
            Update SR1 with Absolute value
            [/cover] */
            /* Update the ATOM shadow register */
            AtomChannelRegPtr->SR1.U = AbsoluteValue;
          }
          else
          {
            /* [cover parentID={8509BE2F-2894-4b4e-A21A-BE7E3CC33E6B}]
            Update CM1 and SR1 with Absolute value
            [/cover] */
            /* Update the ATOM compare and shadow register */
            AtomChannelRegPtr->CM1.U = AbsoluteValue;
            AtomChannelRegPtr->SR1.U = AbsoluteValue;
          }


          /* Read current counter value */
          CounterValueRead2 = AtomChannelRegPtr->CN0.U;
          /*End Critical section */
          SchM_Exit_Ocu_SetThresholdValue();
          /* [cover parentID={C055A324-E062-48b1-81E8-7E01B28E8D46},
                 {CB5915FE-7BFE-40a7-9459-DD0DC1F060FA}]
            Identify and return if the compare match occurs in current reference inteval
            [/cover] */
          ReturnValue1 = Ocu_lGetReturnValue(AbsoluteValue, CounterValueRead1, \
                                             ReferenceValue, LocalOcuChanPtr->MaxCounterValue);

          ReturnValue2 = Ocu_lGetReturnValue(AbsoluteValue, CounterValueRead2, \
                                             ReferenceValue, LocalOcuChanPtr->MaxCounterValue);

          if((ReturnValue1 | ReturnValue2) == TRUE)
          {
            ReturnValue = OCU_CM_IN_REF_INTERVAL;
          }

          break;
        default:
          /*Enter critical section*/
          SchM_Enter_Ocu_SetThresholdValue();
          /* For ATOM shared:
           * counter value - new compare value & 0xFFFFFFFF > 0x800000,
           * update CM0/1 else update newval+0x800000 to CM0/1 and in ISR to
           * SR0/1 + 0x800000*/
          CounterValue = Ocu_lGetCounter(
                           LocalOcuChanPtr->OcuProperties.AssignedHwUnit,
                           LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber,
                           LocalOcuChanPtr->OcuProperties.ClockSelect);

          /* [cover parentID={25BD0D00-7BB5-4395-989D-98DABEF64ED4}]
          compare value is in past ?
          [/cover] */
          if(((CounterValue - AbsoluteValue) & (ATOM_MASK_LSB_24BITS)) >= CNT_BORDER_VAL_BT_PAST_FUTURE)
          {
            /* [cover parentID={D04976FA-7AD1-45dd-847D-15D5E3A4F033}]
            Program the actual compare value with required pin-action
            [/cover] */
            Mcal_SetBitAtomic((ChannelStatusPtr), \
                              OCU_CHNL_ATOM_RE_PROG_ISR_POS, \
                              OCU_CHNL_ATOM_RE_PROG_ISR_BIT_LENGTH, \
                              (uint32)OCU_BIT_RESET);
            ReturnValue = Ocu_lSetAtomCompare(AbsoluteValue, ReferenceValue, \
                                              LocalOcuChanPtr, (uint8)Mcal_GetBitAtomic(*ChannelStatusPtr, \
                                                  OCU_CHNL_PIN_ACTION_POS, OCU_CHNL_PIN_ACTION_BIT_LENGTH), \
                                              ChannelNumber);
          }
          else
          {
            /* [cover parentID={F13EB358-EA28-4820-BE3C-13D6F5921245}]
            Program the incrementel compare value with no pin-action
            [/cover] */
            Mcal_SetBitAtomic((ChannelStatusPtr), \
                              OCU_CHNL_ATOM_RE_PROG_ISR_POS, \
                              OCU_CHNL_ATOM_RE_PROG_ISR_BIT_LENGTH, \
                              (uint32)OCU_BIT_SET);
            ReturnValue = Ocu_lSetAtomCompare(
                            ((AbsoluteValue + CNT_BORDER_VAL_BT_PAST_FUTURE) \
                             & (ATOM_MASK_LSB_24BITS)), \
                            ReferenceValue, LocalOcuChanPtr, (uint8)OCU_DISABLE, \
                            ChannelNumber);
          }
          Ocu_RootChannelVar[CoreId][CoreChIndex].CompareValue = AbsoluteValue;
          /*End Critical section */
          SchM_Exit_Ocu_SetThresholdValue();
          break;
      }
    }
  }
  /* [cover parentID={DD15BFCB-9595-40fe-AC4C-93C9FEBCC9F2}]
    OCU Interrupt Control Registers.
  [/cover] */
  /* MISRA2012_RULE_2_2_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer ChannelStatusPtr is
   * accessed using assembly instruction. */
  return (ReturnValue);
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer ChannelStatusPtr is
   * accessed using assembly instruction. */
}/* End of Ocu_SetAbsoluteThreshold() function */
#endif

#if (OCU_SET_RELATIVE_THRESHOLD_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={0F4DF58E-1021-411d-9623-3FAEAC9BB27D}]      **
**                                                                            **
** Syntax : Ocu_ValueType Ocu_SetRelativeThreshold(                           **
**                                   const Ocu_ChannelType ChannelNumber,     **
**                                   const Ocu_ValueType RelativeValue )      **
**                                                                            **
** Description : This service will set the threshold using the relatives      **
**               values                                                       **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x08                                                     **
*                                                                             **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant for different channel numbers                  **
**                                                                            **
** Parameters (in):  ChannelNumber - Numeric identifier of the OCU channel    **
**                   RelativeValue - Relative threshold w.r.t. current counter**
**                   value.                                                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     Ocu_ReturnType - to indicate if the compare match occurs **
**                                    in this cycle.                          **
**                                                                            **
*******************************************************************************/
/*[cover parentID={7F5A4CE6-A065-494e-9B74-0654A5CB52D1}]
Safety Properties
[/cover]*/
Ocu_ReturnType Ocu_SetRelativeThreshold( const Ocu_ChannelType ChannelNumber,
    const Ocu_ValueType RelativeValue )
{
  #if (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON)
  uint32 ErrorFlag;

  #endif


  const Ocu_ChannelConfigType *LocalOcuChanPtr; /* ROM pointer */
  uint32* ChannelStatusPtr;
  /* Initialize return counter to 0 */
  Ocu_ReturnType ReturnValue = OCU_CM_OUT_REF_INTERVAL;
  uint32 ReturnValue1;
  uint32 ReturnValue2;
  Ocu_ValueType CompareValue;
  Ocu_ValueType ReferenceValue;
  Ocu_ValueType CounterValue;
  Ocu_ValueType CounterValueRead1;
  Ocu_ValueType CounterValueRead2;
  uint8 CoreId;
  uint8 CoreChIndex;
  /* Pointer to ATOM channel Register */
  Ifx_GTM_ATOM_CH *AtomChannelRegPtr;
  /* Pointer to TOM channel Register */
  Ifx_GTM_TOM_CH *TomChannelRegPtr;
  /* Get core id which is executing currently */
  CoreId = OCU_GETCOREID();
  /* If DET or Safety is enabled*/
  #if (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON)
  /* Verify any error is there for DET */
  ErrorFlag = Ocu_lInitCallVerify(OCU_SID_SETRELATIVETHRESHOLD, CoreId);
  /* Channel specific DET checks */
  /* [cover parentID={C30346EE-8CBE-443f-87D5-A2406F945AA3}]
  Is the Ocu_Init invoked?
  [/cover] */

  if (ErrorFlag != OCU_ERROR_FOUND)
  {
    ErrorFlag = Ocu_lChannelVerify(OCU_SID_SETRELATIVETHRESHOLD, \
                                   ChannelNumber, CoreId);
  }
  /* [cover parentID={CEA498BB-E07C-414f-970B-2586E9BBD4AE}]
  Is channel valid and channel Initialized ?
  [/cover] */
  if (ErrorFlag != OCU_ERROR_FOUND)
  #endif
  {
    #if (OCU_SINGLE_CORE == STD_OFF)
    /* Initialize OCU configured channel ROM pointer */
    CoreChIndex = (uint8)(Ocu_ConfigPtr->ChannelMapping[ChannelNumber] & \
                          OCU_CHNL_MAP_CHNL_INDEX_MASK);
    #else
    CoreChIndex = (uint8)ChannelNumber;
    #endif




    LocalOcuChanPtr = &((Ocu_ConfigPtr->CoreConfig[CoreId]->ChannelConfigPtr)\
                        [CoreChIndex]);

    #if (OCU_SAFETY_ENABLE == STD_ON)


    /* [cover parentID={8A2535BD-75CB-4c3c-B9F9-C21E2D6DCE37}]
     Are RefernceValue greater than MaxCounterValue?
    [/cover] */
    /* [cover parentID={6AA07C4B-E9A4-4e36-8C2D-0B453B581ECC}]
    Safety measures reporting safety errors
    [/cover] */
    /* [cover parentID={36D99C23-96C0-4b84-BFB3-E8BBB4DDAC4D}]
    Range check for input parameters
    [/cover] */
    if(RelativeValue > LocalOcuChanPtr->MaxCounterValue)
    {
      Mcal_ReportSafetyError(
        OCU_MODULE_ID,
        OCU_INSTANCE_ID,
        OCU_SID_SETRELATIVETHRESHOLD,
        (uint8)OCU_E_PARAM_COMPARE_VALUE);/* End of report to Safety */
    }
    else
    #endif
    {

      /* Channel specific status variable */
      ChannelStatusPtr = &(Ocu_RootChannelVar[CoreId][CoreChIndex].Status);
      /* calculate and configure new relative threshold */

      /* Read counter for TOM/ATOM channel to calculate the new compare value */
      ReferenceValue = Ocu_lGetCounter(
                         LocalOcuChanPtr->OcuProperties.AssignedHwUnit,
                         LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber,
                         LocalOcuChanPtr->OcuProperties.ClockSelect);
      CompareValue = ReferenceValue + RelativeValue;
      if(CompareValue > LocalOcuChanPtr->MaxCounterValue)
      {
        CompareValue = CompareValue - LocalOcuChanPtr->MaxCounterValue;
      }

      switch(LocalOcuChanPtr->OcuProperties.AssignedHwUnit)
      {
        /* For TOM & ATOM: counter value > new compare value, set in shadow or else in CM1 */
        /* [cover parentID= {C2A23B69-5A5D-44e2-890D-F0FFA16997CA}]
             Is the channel using TOM ?
             [/cover] */
        case OCU_GTM_TOM:
          /* MISRA2012_RULE_11_3_JUSTIFICATION: GTM_TOM_CH_POINTER does a typecast
           * to void and then to specific Mcu datatype Mcu_17_Gtm_TomChArray to 
           * index to the proper TOM channel's SFR from the base GTM SFR. 
           * No side effects seen by violating this MISRA */
          /* MISRA2012_RULE_11_5_JUSTIFICATION: GTM_TOM_CH_POINTER does a typecast
           * to void and then to specific Mcu datatype Mcu_17_Gtm_TomChArray to 
           * index to the proper TOM channel's SFR from the base GTM SFR. 
           * No side effects seen by violating this MISRA */

          TomChannelRegPtr = GTM_TOM_CH_POINTER((uint8)(\
                                                (LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber & \
                                                 GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF), \
                                                (uint8)((LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber & \
                                                    GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF));

          /* Enter critical section */

          SchM_Enter_Ocu_SetThresholdValue();



          /* Read current counter value */
          CounterValueRead1 = TomChannelRegPtr->CN0.U;

          /* [cover parentID={99F91847-0C5F-44e8-A5ED-A677DA53259C}]
               Is the compare value larger than current value.
               [/cover] */

          if(CounterValueRead1 > CompareValue)
          {
            /* [cover parentID={9A12F0FB-0829-43d8-91EF-7D0CE7157E37}]
            Update SR1 with Absolute value
            [/cover] */
            TomChannelRegPtr->SR1.U = CompareValue;
          }
          else
          {
            /* [cover parentID={86EE7273-42ED-4256-B4F6-EEB38B266DD6}]
            Update CM1 and SR1 with Absolute value
            [/cover] */
            TomChannelRegPtr->SR1.U = CompareValue;
            TomChannelRegPtr->CM1.U = CompareValue;
          }
          /* Read current counter value */
          CounterValueRead2 = TomChannelRegPtr->CN0.U;
          /*End Critical section */
          SchM_Exit_Ocu_SetThresholdValue();


          ReturnValue1 = Ocu_lGetReturnValue(CompareValue, CounterValueRead1, \
                                             ReferenceValue, LocalOcuChanPtr->MaxCounterValue);

          ReturnValue2 = Ocu_lGetReturnValue(CompareValue, CounterValueRead2, \
                                             ReferenceValue, LocalOcuChanPtr->MaxCounterValue);


          /* [cover parentID={14BD24B5-2FC2-4ac8-996E-3296D12EEAB3}]
          Identify and return if the compare match occurs in current reference inteval
          [/cover] */
          if((ReturnValue1 | ReturnValue2) == TRUE)
          {
            ReturnValue = OCU_CM_IN_REF_INTERVAL;
          }



          break;
        /* [cover parentID= {C0001F28-4B49-4131-AA75-2A55043FD093}]
         Is the channel using ATOM ?
         [/cover] */
        case OCU_GTM_ATOM:
          /* MISRA2012_RULE_11_3_JUSTIFICATION: GTM_ATOM_CH_POINTER does a typecast
           * to void and then to specific Mcu datatype Mcu_17_Gtm_AtomChArray to 
           * index to the proper ATOM channel's SFR from the base GTM SFR. 
           * No side effects seen by violating this MISRA */
          /* MISRA2012_RULE_11_5_JUSTIFICATION: GTM_ATOM_CH_POINTER does a typecast
           * to void and then to specific Mcu datatype Mcu_17_Gtm_AtomChArray to 
           * index to the proper ATOM channel's SFR from the base GTM SFR. 
           * No side effects seen by violating this MISRA */



          AtomChannelRegPtr = GTM_ATOM_CH_POINTER((uint8)(\
                                                  (LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber & \
                                                      GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF), \
                                                  (uint8)((LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber & \
                                                      GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF));

          /* Enter critical section */

          SchM_Enter_Ocu_SetThresholdValue();


          /* Read current counter value */
          CounterValueRead1 = AtomChannelRegPtr->CN0.U;

          /* [cover parentID={37F6EF0E-1165-4aa1-B37F-D76EF613E8F3}]
               Is the compare value larger than current value.
               [/cover] */
          if(CounterValueRead1 > CompareValue)
          {
            /* [cover parentID={BD26C7A4-E345-4481-9304-9D4BCB0F9AD4}]
            Update SR1 with Absolute value
            [/cover] */
            AtomChannelRegPtr->SR1.U = CompareValue;
          }
          else
          {
            /* [cover parentID={B1182647-D400-4e18-8CFC-69DB1281FC01}]
            Update CM1 and SR1 with Absolute value
            [/cover] */
            AtomChannelRegPtr->CM1.U = CompareValue;
            AtomChannelRegPtr->SR1.U = CompareValue;
          }
          /* Read current counter value */
          CounterValueRead2 = AtomChannelRegPtr->CN0.U;
          /*End Critical section */
          SchM_Exit_Ocu_SetThresholdValue();


          ReturnValue1 = Ocu_lGetReturnValue(CompareValue, CounterValueRead1, \
                                             ReferenceValue, LocalOcuChanPtr->MaxCounterValue);

          ReturnValue2 = Ocu_lGetReturnValue(CompareValue, CounterValueRead2, \
                                             ReferenceValue, LocalOcuChanPtr->MaxCounterValue);


          /* [cover parentID={0C256D11-3113-48dd-B4BE-D75252E46A59}]
          Identify and return if the compare match occurs in current reference inteval
          [/cover] */

          if((ReturnValue1 | ReturnValue2) == TRUE)
          {
            ReturnValue = OCU_CM_IN_REF_INTERVAL;
          }




          break;
        default:
          /* Enter critical section */
          SchM_Enter_Ocu_SetThresholdValue();
          /* For ATOM shared:
           * (counter value - new compare value) & 0xFFFFFFFF > 0x800000,
           * update CM0/1 else update newval+0x800000 to CM0/1 and in ISR to
           * SR0/1 + 0x800000*/

          CounterValue = Ocu_lGetCounter(
                           LocalOcuChanPtr->OcuProperties.AssignedHwUnit,
                           LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber,
                           LocalOcuChanPtr->OcuProperties.ClockSelect);


          /* [cover parentID={1283912F-6827-43dc-9835-1CDD6211CF3E}]
          compare value is in past ?
          [/cover] */
          if(((CounterValue - CompareValue) & (ATOM_MASK_LSB_24BITS)) >= CNT_BORDER_VAL_BT_PAST_FUTURE)
          {
            /* [cover parentID={D5DD0CCC-5759-482d-B0A1-D02B2DE81F73}]
            Program the actual compare value with required pin-action
            [/cover] */
            Mcal_SetBitAtomic((ChannelStatusPtr), \
                              OCU_CHNL_ATOM_RE_PROG_ISR_POS, \
                              OCU_CHNL_ATOM_RE_PROG_ISR_BIT_LENGTH, \
                              (uint32)OCU_BIT_RESET);
            ReturnValue = Ocu_lSetAtomCompare(CompareValue, ReferenceValue, LocalOcuChanPtr,
                                              (uint8)Mcal_GetBitAtomic(*ChannelStatusPtr, \
                                                  OCU_CHNL_PIN_ACTION_POS, OCU_CHNL_PIN_ACTION_BIT_LENGTH), \
                                              ChannelNumber);
          }
          else
          {
            /* [cover parentID={8991EA67-AD6F-4bbb-ABC4-DBE23B91E250}]
            Program the incrementel compare value with no pin-action
            [/cover] */
            Mcal_SetBitAtomic((ChannelStatusPtr), \
                              OCU_CHNL_ATOM_RE_PROG_ISR_POS, \
                              OCU_CHNL_ATOM_RE_PROG_ISR_BIT_LENGTH, \
                              (uint32)OCU_BIT_SET);
            ReturnValue = Ocu_lSetAtomCompare( \
                                               ((CompareValue + CNT_BORDER_VAL_BT_PAST_FUTURE) \
                                                & (ATOM_MASK_LSB_24BITS)), \
                                               ReferenceValue, LocalOcuChanPtr, (uint8)OCU_DISABLE, \
                                               ChannelNumber);
          }
          Ocu_RootChannelVar[CoreId][CoreChIndex].CompareValue = CompareValue;
          /*End Critical section */
          SchM_Exit_Ocu_SetThresholdValue();
          break;
      }
    }
  }
  /* [cover parentID={DD15BFCB-9595-40fe-AC4C-93C9FEBCC9F2}]
    OCU Interrupt Control Registers.
  [/cover] */
  /* MISRA2012_RULE_2_2_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer ChannelStatusPtr is
   * accessed using assembly instruction. */
  return (ReturnValue);
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer ChannelStatusPtr is
   * accessed using assembly instruction. */
}/* End of Ocu_SetRelativeThreshold() function */
#endif

#if (OCU_DE_INIT_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={FCEECF29-AFA2-4bc9-A2E1-3982A7C33341}]      **
**                                                                            **
** Syntax : void Ocu_DeInit(void)                                             **
**                                                                            **
** Description : Service for OCU De-Initialization                            **
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
/*[cover parentID={7F5A4CE6-A065-494e-9B74-0654A5CB52D1}]
Safety Properties
[/cover]*/
void Ocu_DeInit(void)
{
  /* Local pointers */
  const Ocu_ChannelConfigType *LocalOcuChanPtr; /* ROM pointer */
  /* Local variables */
  #if (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON)
  uint32 ErrorFlag;
  #endif
  uint32 OcuOption;
  uint32 HwUnitNumber;

  Ocu_ChannelType Channel;
  uint8 CoreId;
  /* Get core id which is executing currently */
  CoreId = OCU_GETCOREID();


  /* [cover parentID={B8ED808E-23DB-48dc-A004-6790E4A546B0}]
  DET or Safety is enabled
  [/cover] */
  #if (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={F0F86A55-8EEC-402a-8648-6161F44DD5DC}]
  Check if init is invoked and all the channels in stopped state.
  [/cover] */
  ErrorFlag = Ocu_lDeInitDETCheck(CoreId);
  /* [cover parentID={9AAE1D2E-01E9-4642-97AD-0FC570437F1B}]
  Any DET occured
  [/cover] */
  if (OCU_ERROR_FOUND != ErrorFlag)
  #endif
  {
    /* [cover parentID={D6B176A8-40D6-4115-9C07-7D6B7A7354CA}]
    Set the status to indicate the de-initialization has started.
    [/cover] */
    Mcal_SetBitAtomic(&Ocu_InitStatus,
                      (sint32) (CoreId * OCU_INIT_STATUS_SIZE), OCU_INIT_STATUS_SIZE, \
                      (uint32) (OCU_DEINITPENDING));
    /* Initialize OCU configured channel ROM pointer */
    LocalOcuChanPtr = \
                      Ocu_ConfigPtr->CoreConfig[CoreId]->ChannelConfigPtr;
    /* [cover parentID={2F0683F3-B759-4c2b-B832-CFE8A6333E93}]
    Deinit the configured channels, registers , variables etc
    [/cover] */
    /* Run the for loop for all the channels */
    for (Channel = (Ocu_ChannelType) 0;
         /* [cover parentID={C92C4808-CE9B-4aff-823F-4A00C1B72BEF}]
         Loop till the last channel of the core.
         [/cover] */
         Channel < Ocu_ConfigPtr->CoreConfig[CoreId]->MaxChannelCore;
         Channel = Channel + 1U)
    {
      /* Depending on OCU option take action */
      OcuOption = (uint32) LocalOcuChanPtr->OcuProperties.AssignedHwUnit;
      HwUnitNumber = \
                     (uint32) LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber;
      /* Work on depending on OCU option chosen for each channel */
      /* [cover parentID=]
      Deinit the configured channels, registers , variables.
      [/cover] */
      switch (OcuOption)
      {
        /* [cover parentID={6029BE50-A607-49e6-9188-78378F9C83EC}]
        Is the channel using TOM
        [/cover] */
        case OCU_GTM_TOM:
          /* [cover parentID={6C35E4CA-F626-4644-AD8D-A5222AD1D620}]
          De-Init TOM channel
          [/cover] */
          Mcu_17_Gtm_TomChannelDeInit( \
                                       (uint8)((HwUnitNumber & GTM_MODULE_NO_MASK) >> \
                                               GTM_MODULE_NO_OFF), \
                                       (uint8)((HwUnitNumber & GTM_CHANNEL_NO_MASK) >> \
                                               GTM_CHANNEL_NO_OFF));


          Mcu_17_Gtm_TomChannelDisable( \
                                        (uint8)((HwUnitNumber & GTM_MODULE_NO_MASK) >> \
                                                GTM_MODULE_NO_OFF), \
                                        (uint8)((HwUnitNumber & GTM_CHANNEL_NO_MASK) >> \
                                                GTM_CHANNEL_NO_OFF));


          /*Disable the update of CM1 register by the corresponding shadow register *
           * SR1 on reset of CN0*/
          Mcu_17_Gtm_TomChUpdateEnDis(\
                                      (uint8)((HwUnitNumber & GTM_MODULE_NO_MASK) >> \
                                              GTM_MODULE_NO_OFF), \
                                      (uint8)((HwUnitNumber & GTM_CHANNEL_NO_MASK) >> \
                                              GTM_CHANNEL_NO_OFF), 0U);

          break;
        default: /* ATOM Channel */
          /* [cover parentID={467DDD6B-C8BC-4889-9A40-FE19B08D421B}]
          De-Init ATOM channel
          [/cover] */
          Mcu_17_Gtm_AtomChannelDeInit( \
                                        (uint8)((HwUnitNumber & GTM_MODULE_NO_MASK) >> \
                                                GTM_MODULE_NO_OFF), \
                                        (uint8)((HwUnitNumber & GTM_CHANNEL_NO_MASK) >> \
                                                GTM_CHANNEL_NO_OFF));

          Mcu_17_Gtm_AtomChannelDisable( \
                                         (uint8)((HwUnitNumber & GTM_MODULE_NO_MASK) >> \
                                                 GTM_MODULE_NO_OFF), \
                                         (uint8)((HwUnitNumber & GTM_CHANNEL_NO_MASK) >> \
                                                 GTM_CHANNEL_NO_OFF));

          /*Disable the update of CM1 register by the corresponding shadow register *
           * SR1 on reset of CN0*/
          Mcu_17_Gtm_AtomChUpdateEnDis(\
                                       (uint8)((HwUnitNumber & GTM_MODULE_NO_MASK) >> \
                                               GTM_MODULE_NO_OFF), \
                                       (uint8)((HwUnitNumber & GTM_CHANNEL_NO_MASK) >> \
                                               GTM_CHANNEL_NO_OFF), 0U);


          break;
      }/* End of switch */
      /* clear STATUS variable to clear all the flags */
      Ocu_RootChannelVar[CoreId][Channel].Status = 0U;
      /* Increment the pointers */
      /* MISRA2012_RULE_18_4_JUSTIFICATION: Different OCU Channels are
         associated.to make it easier to understand, pointer arithmetic
         other than array indexing used is being used. no side effect
         has been seen*/
      LocalOcuChanPtr = LocalOcuChanPtr + 1U;
    }/* End of for loop within Ocu_DeInit() function */
    /* Set the Status to indicate that Deinitialization is done */
    Mcal_SetBitAtomic(&Ocu_InitStatus,
                      (uint32) (CoreId * OCU_INIT_STATUS_SIZE), OCU_INIT_STATUS_SIZE, \
                      (uint32) (OCU_DEINITIALIZED));
    /* [cover parentID={8B2010C7-E607-4c4c-86C9-D169D739449B}]
    check if all the cores are Uninitialize
    [/cover] */
    if(Ocu_InitStatus == 0u)
    {
      Ocu_ConfigPtr = NULL_PTR;
    }


  }/* Error not found */
  return;
  /* [cover parentID={DD15BFCB-9595-40fe-AC4C-93C9FEBCC9F2}]
    OCU Interrupt Control Registers.
  [/cover] */
}/* End of Ocu_DeInit() function */
#endif


#if (OCU_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={30E3020F-D1E9-4cc5-96F2-6F222AB37090}]      **
**                                                                            **
** Syntax :          void Ocu_GetVersionInfo (                                **
**                          Std_VersionInfoType* const versioninfo)           **
**                                                                            **
** Description : 1. This service will return the version infos of OCU driver  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x09                                                     **
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
/*[cover parentID={7F5A4CE6-A065-494e-9B74-0654A5CB52D1}]
Safety Properties
[/cover]*/
void Ocu_GetVersionInfo(Std_VersionInfoType* const versioninfo)
{
  /* [cover parentID={E19D546E-196D-4c5c-A601-BFD9E06BED73}]
  Ocu_GetVersionInfo
  [/cover] */
  /* [cover parentID={188B0A0A-5B33-4234-A6D5-1D34DBC46D07}]
  DET or safety is enabled.
  [/cover] */
  #if (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={53D0CF98-97FB-4896-9B70-BCBA8797A783}]
  Is the passed pointer valid?
  [/cover] */
  if ((versioninfo) == (NULL_PTR))
  {
    /* Issue a DET/Safety Error */
    Ocu_lReportError(
      OCU_SID_GETVERSIONINFO,
      OCU_E_PARAM_POINTER);/* End of report to  DET/Safety */
  }
  else
  #endif
  {
    /* [cover parentID={44D368FF-25DD-4c45-8291-D953E8914E2E}]
    Update vendor ID, module ID, SW major, SW minor and SW patch version values
    in the pointer parameter.
    [/cover] */
    /* Get OCU Vendor ID */
    versioninfo->vendorID = OCU_VENDOR_ID;
    /* Get OCU Module ID */
    versioninfo->moduleID = OCU_MODULE_ID;
    /* Get OCU module Software major version */
    versioninfo->sw_major_version = (uint8)OCU_SW_MAJOR_VERSION;
    /* Get OCU module Software minor version */
    versioninfo->sw_minor_version = (uint8)OCU_SW_MINOR_VERSION;
    /* Get OCU module Software patch version */
    versioninfo->sw_patch_version = (uint8)OCU_SW_PATCH_VERSION;
  }
  /* [cover parentID={DD15BFCB-9595-40fe-AC4C-93C9FEBCC9F2}]
    OCU Interrupt Control Registers.
  [/cover] */
}/* End of Ocu_GetVersionInfo*/
#endif /* (OCU_VERSION_INFO_API == STD_ON) */

#if (OCU_INITCHECK_API == STD_ON)
/*******************************************************************************
** Traceability : [cover parentID={A44CEAFF-A56C-4e6a-8E12-3B6700BA53F4}]     **
**                                                                            **
** Syntax : Std_ReturnType Ocu_InitCheck(                                     **
**                const Ocu_ConfigType * const ConfigPtr )                    **
**                                                                            **
** Service ID      :    0x0C                                                  **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Non Reentrant                                         **
**                                                                            **
** Parameters (in) :    ConfigPtr - Pointer to OCU Driver configuration set   **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    :    E_OK - if initialization comparison is success        **
**                      E_NOT_OK - if initialization comparison fails         **
**                                                                            **
** Description     : This routine verifies the initialization of OCU driver.  **
**                                                                            **
*******************************************************************************/
/*[cover parentID={7F5A4CE6-A065-494e-9B74-0654A5CB52D1}]
Safety Properties
[/cover]*/
Std_ReturnType Ocu_InitCheck(
  const Ocu_ConfigType* const ConfigPtr)
{

  uint8 CoreId;
  Std_ReturnType ErrorFlag;

  /* Local pointers */
  const Ocu_ChannelConfigType *LocalOcuChanPtrBase; /* ROM pointer */
  const Ocu_ChannelConfigType *LocalOcuChanPtr; /* ROM pointer */
  const Ocu_ChannelVarType* ChannelVarPtr;

  /* Local variables */
  Ocu_ChannelType Channel;
  /* Get core id which is executing currently */
  CoreId = OCU_GETCOREID();
  /* [cover parentID={75856AD4-C170-43aa-8352-131073B02B5B}]
  Check if the input parameter is NULL
  [/cover] */
  ErrorFlag = Ocu_lPreInitCheck(ConfigPtr, CoreId);


  /* Proceed only if above checks are successful */
  /* [cover parentID={287234C2-81A1-4b1c-A040-1DF543E67AEC}]
  Is previous check passed and configuration pointer non-NULL?
  [/cover] */
  if(E_OK == ErrorFlag)
  {
    /* Get the channel config base pointer */
    LocalOcuChanPtrBase = \
                          (Ocu_ConfigPtr->CoreConfig[CoreId]->ChannelConfigPtr);


    /* Channel specific status variable */
    ChannelVarPtr = &(Ocu_RootChannelVar[CoreId][0]);

    /* [cover parentID={E603C68E-5277-4d24-8A04-36E56D6C0482}]
    Initialize all channels
    [/cover] */
    for(Channel = (Ocu_ChannelType) 0;
        /* Till last available channel of current core. */
        (Channel < Ocu_ConfigPtr->CoreConfig[CoreId]->MaxChannelCore) &&
        (ErrorFlag != E_NOT_OK);
        Channel = Channel + 1U)
    {
      /* Channel specific configuration pointer */
      LocalOcuChanPtr = &LocalOcuChanPtrBase[Channel];

      ErrorFlag = Ocu_lInitCheck(LocalOcuChanPtr, ChannelVarPtr);

      ChannelVarPtr++;
    }
  }
  return ErrorFlag;
}
#endif
/*******************************************************************************
 **                      Private Function Definitions                         **
 ******************************************************************************/

#if (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={412E0490-3C32-42d9-A425-62B7958069B3}]      **
**                                                                            **
** Syntax :           LOCAL_INLINE uint32 Ocu_lInitDetCheck(                  **
**                 const Ocu_ConfigType *const ConfigPtr,                     **
**                 const uint8 CoreId )                                       **
**                                                                            **
** Description :      Local function :Performs the Init pre-requisite checks  **
                      and report development error to DET module.             **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        None                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Non Reentrant                                           **
**                                                                            **
** Parameters (in):   ConfigPtr - Ocu config pointer                          **
**                    CoreId  - Core which is calling this function           **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value:      uint32: status of Init pre-requisite check              **
**                            OCU_ERROR_NOT_FOUND/OCU_ERROR_FOUND             **
**                                                                            **
*******************************************************************************/
/*[cover parentID={7F5A4CE6-A065-494e-9B74-0654A5CB52D1}]
Safety Properties
[/cover]*/
LOCAL_INLINE uint32 Ocu_lInitDetCheck(
  const Ocu_ConfigType *const ConfigPtr,
  const uint8 CoreId)
{
  uint32 ErrorFlag;
  ErrorFlag = (uint32)OCU_ERROR_NOT_FOUND;

  /* To verify whether Init has been called with wrong parameter */
  /* Det Check for NULL pointer  */
  /* [cover parentID={36D99C23-96C0-4b84-BFB3-E8BBB4DDAC4D},
                   {0B4F6CBA-F172-4858-AE7E-FF29917CC33E}]
  Range check for input parameters
  [/cover] */
  if (NULL_PTR == ConfigPtr )
  {
    /* [cover parentID={1CF003C5-172D-4ab2-8C35-59F5EB1796EE}]
    Report Error to indicate that the configuration pointer is not valid.
    [/cover] */
    Ocu_lReportError(
      OCU_SID_INIT,
      OCU_E_INIT_FAILED);
    /* Report Error */
    /* [cover parentID={5AA95633-0E59-4121-B710-2BEE46D65060}]
    Set the error flag.
    [/cover] */
    ErrorFlag = OCU_ERROR_FOUND;
  }
  #if (OCU_MULTICORE_ERROR_DETECT == STD_ON)|| (OCU_SAFETY_ENABLE == STD_ON)
  if(ErrorFlag != OCU_ERROR_FOUND)
  {


    /* [cover parentID={F94FA389-501D-4632-9962-C8142D7B1E27}]
       Check if core is configured
      [/cover] */
    if(ConfigPtr->CoreConfig[CoreId] == NULL_PTR)
    {
      ErrorFlag = OCU_ERROR_FOUND;
      Ocu_lReportMulticoreError(
        OCU_SID_INIT,
        OCU_E_CORE_NOT_CONFIGURED); /* Report Error */
    }

  }
  #endif

  /* [cover parentID={E4D6ED2F-101F-4b52-AAC0-30D7D274F26D}]
  If OCU driver already initialized
  [/cover] */
  if(ErrorFlag != OCU_ERROR_FOUND)
  {
    if(OCU_INITIALIZED == \
        Mcal_GetBitAtomic(Ocu_InitStatus, \
                          (((sint32)CoreId) * (OCU_INIT_STATUS_SIZE)),
                          OCU_INIT_STATUS_SIZE))
    {
      /* [cover parentID={AAF9E7FC-E4CD-41a0-BA0E-D9EAED2AE81E}]
      Report error to indicate that initialization is already done.
      [/cover] */
      Ocu_lReportError(
        OCU_SID_INIT,
        OCU_E_ALREADY_INITIALIZED);
      /* [cover parentID={5AA95633-0E59-4121-B710-2BEE46D65060}]
      Set the error flag.
      [/cover] */
      ErrorFlag = OCU_ERROR_FOUND; /* Set ErrorFlag */
    }
  }
  return(ErrorFlag);
}
#endif
/* End of #if (OCU_DEV_ERROR_DETECT == STD_ON) ||
 * (OCU_SAFETY_ENABLE == STD_ON) */


/*******************************************************************************
** Traceability: [cover parentID={C8E8C756-273B-485d-8F1B-698541112FA2}]      **
**                                                                            **
** Syntax :           LOCAL_INLINE void Ocu_lChannelInit(const uint8 CoreId)  **
**                                                                            **
** Description :      Local function :Service to initialize OCU channels      **
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
/*[cover parentID={7F5A4CE6-A065-494e-9B74-0654A5CB52D1}]
Safety Properties
[/cover]*/
LOCAL_INLINE void Ocu_lChannelInit(const uint8 CoreId)
{
  /* Local pointers */
  const Ocu_ChannelConfigType *LocalOcuChanPtrBase; /* ROM pointer */
  const Ocu_ChannelConfigType *LocalOcuChanPtr; /* ROM pointer */
  Ocu_ChannelVarType* ChannelVarPtr;
  /* Local variables */
  Ocu_ChannelType Channel;
  Mcu_17_Gtm_TomAtomChConfigType TimerConfigPtr;
  /* Pointer to ATOM channel Register */
  Ifx_GTM_ATOM_CH *AtomChannelRegPtr;
  /* Pointer to TOM TGC Register */
  Mcu_17_Gtm_TomTgc * TomTgcRegPtr;
  /* Pointer to ATOM AGC Register */
  Ifx_GTM_ATOM_AGC  * AtomAgcRegPtr;
  uint8 TomTgcIndex;
  uint8 ChannelNum;
  uint8 ModuleNum;

  /* Get the channel config base pointer */
  LocalOcuChanPtrBase = \
                        (Ocu_ConfigPtr->CoreConfig[CoreId]->ChannelConfigPtr);
  /* Channel specific status variable */
  ChannelVarPtr = &(Ocu_RootChannelVar[CoreId][0]);

  /* [cover parentID={3AAA972D-0271-4f42-BAD8-B2DA9CFFA244}]
  Initialize all channels
  [/cover] */
  for(Channel = (Ocu_ChannelType) 0;
      /* [cover parentID={0FA61E7D-3B99-4ed0-A64F-BC84722435A4}]
      Till last available channel of current core.
      [/cover] */
      Channel < Ocu_ConfigPtr->CoreConfig[CoreId]->MaxChannelCore;
      Channel = Channel + 1U)
  {

    /* Clear the channel status bits */
    /* [cover parentID={19C73DBF-BBEE-4cc1-A6EF-247FC3605D22}]
    Disable notification, set channel state to stopped and default pin action
    to OCU_DISABLE
    [/cover] */
    ChannelVarPtr->Status = 0U;

    /* Channel specific configuration pointer */
    LocalOcuChanPtr = &LocalOcuChanPtrBase[Channel];
    TimerConfigPtr.TimerChCM0Reg = LocalOcuChanPtr->MaxCounterValue;
    TimerConfigPtr.TimerChCM1Reg = LocalOcuChanPtr->DefaultThreshold;
    TimerConfigPtr.TimerChCN0Reg = 0U;
    /* Pulse Notify interrupt mode */
    TimerConfigPtr.TimerChIntEnMode = IRQ_PULSE_NOTIFY_MODE << GTM_TOM_IRQ_MODE_POS;
    TimerConfigPtr.TimerChSR0Reg = LocalOcuChanPtr->MaxCounterValue;
    TimerConfigPtr.TimerChSR1Reg = LocalOcuChanPtr->DefaultThreshold;
    TimerConfigPtr.TimerId = \
                             LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber;
    ModuleNum = (uint8)((LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber & GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);
    ChannelNum = (uint8)((LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber & GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);

    /* [cover parentID={B5801BB8-ED10-47b9-925F-B3C1C1318AAC}]
    Is the HW used TOM?
    [/cover] */
    if(LocalOcuChanPtr->OcuProperties.AssignedHwUnit == OCU_GTM_TOM)
    {
      TimerConfigPtr.TimerType = MCU_GTM_TIMER_TOM;
      TimerConfigPtr.TimerChCtrlReg = \
                                      (((uint32)LocalOcuChanPtr->OcuProperties.ClockSelect << \
                                        OCU_GTM_CLKSELECT_BIT_POS));

      /* Disable TOM FUPD before initialization, since MCU API does not ensure disabling FUPD after use. */
      TomTgcIndex = (ChannelNum / (uint8)GTM_TOM_CH_PER_TGC);

      /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
      * by violating this MISRA rule, as the pointer to the object type
      * it is getting cast into is a known type . */
      /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
      * by violating this MISRA rule. */
      TomTgcRegPtr = GTM_TOM_TGC_POINTER(ModuleNum, TomTgcIndex);

      /* Disable force update of CM0, CM1 and CRK_SRC registers for the
      * input TOM channel. */
      TomTgcRegPtr->TGC_FUPD_CTRL.U = ((uint32)GTM_TOM_FORCE_UPDATE_DISABLE <<
                                       ((uint32)GTM_TOM_BITS_PER_CHAN *
                                        (uint32)((uint32)ChannelNum & GTM_TGC_CHANNEL_MASK)));

      /* [cover parentID={19E19FA6-DA37-4951-A980-2F6401C1F451}]
      Initialize TOM channel
      [/cover] */
      /* MISRA2012_RULE_1_3_JUSTIFICATION: Mcu function invoked with address of local
         variable TimerConfigPtr since the auto variable TimerConfigPtr is passed as 
         const and only read in the local called function. Hence, it is not an issue.*/
      Mcu_17_Gtm_TomChannelInit(&TimerConfigPtr);

      /*Force update of register CM0, CM1 and CLK_SRC. CLK_SRC is reloaded with its
        shadow register CLK_SRC_SR */
      Mcu_17_Gtm_TomChannelShadowTransfer(\
                                          (uint8)((TimerConfigPtr.TimerId & GTM_MODULE_NO_MASK) >> \
                                                  GTM_MODULE_NO_OFF), \
                                          (uint8)((TimerConfigPtr.TimerId & GTM_CHANNEL_NO_MASK) >> \
                                                  GTM_CHANNEL_NO_OFF));
      /*Enable the update of CM1 register by the corresponding shadow register *
       * SR1 on reset of CN0*/
      Mcu_17_Gtm_TomChUpdateEnDis(\
                                  (uint8)((TimerConfigPtr.TimerId & GTM_MODULE_NO_MASK) >> \
                                          GTM_MODULE_NO_OFF), \
                                  (uint8)((TimerConfigPtr.TimerId & GTM_CHANNEL_NO_MASK) >> \
                                          GTM_CHANNEL_NO_OFF), GTM_TOM_CH_UPDATE_ENABLE);

      /* [cover parentID={C4746BB7-6014-445c-BB74-FFC258419E87}]
      Enable TOM channel with disabled output
      [/cover] */
      Mcu_17_Gtm_TomChannelEnable( \
                                   (uint8)((TimerConfigPtr.TimerId & GTM_MODULE_NO_MASK) >> \
                                           GTM_MODULE_NO_OFF), \
                                   (uint8)((TimerConfigPtr.TimerId & GTM_CHANNEL_NO_MASK) >> \
                                           GTM_CHANNEL_NO_OFF), 0U);

    }
    else
    {
      TimerConfigPtr.TimerType = MCU_GTM_TIMER_ATOM;
      /* [cover parentID={4E8AAC14-75A6-4bdd-BF5B-5C16370B2898}]
      Is the channel clock one of TBU clock?
      [/cover] */
      if((LocalOcuChanPtr->OcuProperties.ClockSelect & OCU_GTM_TBU_MASK) == \
          OCU_GTM_TBU_MASK)
      {
       /* MISRA2012_RULE_11_3_JUSTIFICATION: GTM_ATOM_CH_POINTER does a typecast
        * to void and then to specific Mcu datatype Mcu_17_Gtm_AtomChArray to 
        * index to the proper ATOM channel's SFR from the base GTM SFR. 
        * No side effects seen by violating this MISRA */
       /* MISRA2012_RULE_11_5_JUSTIFICATION: GTM_ATOM_CH_POINTER does a typecast
        * to void and then to specific Mcu datatype Mcu_17_Gtm_AtomChArray to 
        * index to the proper ATOM channel's SFR from the base GTM SFR. 
        * No side effects seen by violating this MISRA */
       /* MISRA2012_RULE_18_4_JUSTIFICATION: To effectively access different ATOM
        * channels. Since the Module and channel values are
        * validated by the user, no side effects are foreseen */
       AtomChannelRegPtr = GTM_ATOM_CH_POINTER( \
                                                (uint8)((TimerConfigPtr.TimerId & GTM_MODULE_NO_MASK) >> \
                                                        GTM_MODULE_NO_OFF), \
                                                (uint8)((TimerConfigPtr.TimerId & GTM_CHANNEL_NO_MASK) >> \
                                                        GTM_CHANNEL_NO_OFF));              
        /* Shared counter set acb to 0x1C with pin*/
        if(LocalOcuChanPtr->OcuProperties.ClockSelect == OCU_GTM_TBU_TS2)/*TS2*/
        {
          /*SOMC mode & TBU_TS2*/
          TimerConfigPtr.TimerChCtrlReg = OCU_GTM_ATOM_ACB_NO_ACTION | \
                                          OCU_GTM_ATOM_MODE_SOMC | OCU_GTM_ATOM_TBU_TS2;
          TimerConfigPtr.TimerChCM0Reg = 0U;
          TimerConfigPtr.TimerChCM1Reg = LocalOcuChanPtr->DefaultThreshold;
          /* Only CCU1 interrupt needed */
          TimerConfigPtr.TimerChIntEnMode = \
                                            TimerConfigPtr.TimerChIntEnMode | ATOM_CCU1_IRQ_EN;
        }
        else if(LocalOcuChanPtr->OcuProperties.ClockSelect == OCU_GTM_TBU_TS1)
        {
          TimerConfigPtr.TimerChCtrlReg = \
                                          OCU_GTM_ATOM_ACB_NO_ACTION | OCU_GTM_ATOM_MODE_SOMC;/*SOMC mode */
          TimerConfigPtr.TimerChCM0Reg = 0U;
          TimerConfigPtr.TimerChCM1Reg = LocalOcuChanPtr->DefaultThreshold;
          /* Only CCU1 interrupt needed */
          TimerConfigPtr.TimerChIntEnMode = \
                                            TimerConfigPtr.TimerChIntEnMode | ATOM_CCU1_IRQ_EN;
        }
        else
        {
          TimerConfigPtr.TimerChCtrlReg = \
                                          OCU_GTM_ATOM_ACB_NO_ACTION | OCU_GTM_ATOM_MODE_SOMC;/*SOMC mode */

          TimerConfigPtr.TimerChCM0Reg = LocalOcuChanPtr->DefaultThreshold;
          TimerConfigPtr.TimerChCM1Reg = 0U;
          /* Only CCU0 interrupt needed */
          TimerConfigPtr.TimerChIntEnMode = \
                                            TimerConfigPtr.TimerChIntEnMode | ATOM_CCU0_IRQ_EN;
        }
        
        /* Set the Freeze bit of the Atom Channel */
        AtomChannelRegPtr->SOMC.U |= OCU_ATOM_SOMC_ENABLE_FREEZE;
        
        /* [cover parentID={01B86EA4-A151-4f43-875E-2F1EA7BC905B}]
        Is the channel using Pin?
        [/cover] */

        if(LocalOcuChanPtr->OcuProperties.PinUsed == OCU_BIT_SET)
        {
          /*  ATOM channel - Output Enabled*/

          Mcu_17_Gtm_AtomChOutEnStatUpdate( \
                                            (uint8)((TimerConfigPtr.TimerId & GTM_MODULE_NO_MASK) >> \
                                                GTM_MODULE_NO_OFF), \
                                            (uint8)((TimerConfigPtr.TimerId & GTM_CHANNEL_NO_MASK) >> \
                                                GTM_CHANNEL_NO_OFF), 1U);

          Mcu_17_Gtm_AtomChOutEnCtrlUpdate( \
                                            (uint8)((TimerConfigPtr.TimerId & GTM_MODULE_NO_MASK) >> \
                                                GTM_MODULE_NO_OFF), \
                                            (uint8)((TimerConfigPtr.TimerId & GTM_CHANNEL_NO_MASK) >> \
                                                GTM_CHANNEL_NO_OFF), MCU_NOCHANGE_OUT_ON_TRIGGER);

        }
        else
        {
          /* [cover parentID={E4E11E3D-6B20-4779-A4B2-B5B1810B54AD}]
          Is the channel using ADC?
          [/cover] */
          if(LocalOcuChanPtr->OcuProperties.AdcUsed == OCU_BIT_SET)
          {
            /*ATOM channel - Output Enabled*/

            Mcu_17_Gtm_AtomChOutEnStatUpdate( \
                                              (uint8)((TimerConfigPtr.TimerId & GTM_MODULE_NO_MASK) >> \
                                                  GTM_MODULE_NO_OFF), \
                                              (uint8)((TimerConfigPtr.TimerId & GTM_CHANNEL_NO_MASK) >> \
                                                  GTM_CHANNEL_NO_OFF), 1U);

            Mcu_17_Gtm_AtomChOutEnCtrlUpdate( \
                                              (uint8)((TimerConfigPtr.TimerId & GTM_MODULE_NO_MASK) >> \
                                                  GTM_MODULE_NO_OFF), \
                                              (uint8)((TimerConfigPtr.TimerId & GTM_CHANNEL_NO_MASK) >> \
                                                  GTM_CHANNEL_NO_OFF), MCU_NOCHANGE_OUT_ON_TRIGGER);
            /* [cover parentID={1D7C8B55-8BB6-44cd-8419-8635450B2AA7}]
            Update the OL Signal/ADC Trigger to Toggle on each compare match
            [/cover] */
            Mcal_SetBitAtomic(&(ChannelVarPtr->Status),
                              OCU_CHNL_PIN_ACTION_POS, OCU_CHNL_PIN_ACTION_BIT_LENGTH, \
                              (uint32)OCU_TOGGLE);
          }
        }
        
        TimerConfigPtr.TimerChCtrlReg = \
                                        (((uint32)LocalOcuChanPtr->OcuProperties.PinDefaultState << \
                                          OCU_GTM_ATOM_SL_BIT_POS)) | TimerConfigPtr.TimerChCtrlReg \
                                          | OCU_ATOM_SOMC_ENABLE_FREEZE;

        /* [cover parentID={3B2C043B-A879-44d7-8FA8-11A3ABFA10A8}]
        Initialize ATOM channel
        [/cover] */
        /* MISRA2012_RULE_1_3_JUSTIFICATION: Mcu function invoked with address of local
          variable TimerConfigPtr since the auto variable TimerConfigPtr is passed as 
          const and only read in the local called function. Hence, it is not an issue.*/
        Mcu_17_Gtm_AtomChannelInit(&TimerConfigPtr);        
        
        /* Clear the Freeze bit of the Atom Channel */
        AtomChannelRegPtr->SOMC.U &= OCU_ATOM_SOMC_DISABLE_FREEZE;

      }
      else
      {
        /* exclusive counter */
        TimerConfigPtr.TimerChCtrlReg = OCU_GTM_ATOM_MODE_SOMP;
        /* Clock selection */
        TimerConfigPtr.TimerChCtrlReg = \
                                        (((uint32)LocalOcuChanPtr->OcuProperties.ClockSelect << \
                                          OCU_GTM_CLKSELECT_BIT_POS))  | TimerConfigPtr.TimerChCtrlReg;

        /* Disable ATOM FUPD before initialization, since MCU API does not ensure disabling FUPD after use. */
        AtomAgcRegPtr = GTM_ATOM_AGC_POINTER(ModuleNum);
        /* Disable force update of CM0, CM1 and CRK_SRC registers for
        * the input ATOM channel */
        AtomAgcRegPtr->FUPD_CTRL.U = ((uint32)GTM_ATOM_FORCE_UPDATE_DISABLE <<
                                      ((uint32)GTM_ATOM_BITS_PER_CHAN * (uint32)ChannelNum));

        /* [cover parentID={3B2C043B-A879-44d7-8FA8-11A3ABFA10A8}]
        Initialize ATOM channel
        [/cover] */
        /* MISRA2012_RULE_1_3_JUSTIFICATION: Mcu function invoked with address of local
           variable TimerConfigPtr since the auto variable TimerConfigPtr is passed as 
           const and only read in the local called function. Hence, it is not an issue.*/
        Mcu_17_Gtm_AtomChannelInit(&TimerConfigPtr);

        /*Force update of register CM0, CM1 and CLK_SRC. CLK_SRC is reloaded with its
          shadow register CLK_SRC_SR */
        Mcu_17_Gtm_AtomChannelShadowTransfer(\
                                             (uint8)((TimerConfigPtr.TimerId & GTM_MODULE_NO_MASK) >> \
                                                     GTM_MODULE_NO_OFF), \
                                             (uint8)((TimerConfigPtr.TimerId & GTM_CHANNEL_NO_MASK) >> \
                                                     GTM_CHANNEL_NO_OFF));

        /*Enable the update of CM1 register by the corresponding shadow register *
          * SR1 on reset of CN0*/
        Mcu_17_Gtm_AtomChUpdateEnDis( \
                                      (uint8)((TimerConfigPtr.TimerId & GTM_MODULE_NO_MASK) >> \
                                              GTM_MODULE_NO_OFF), \
                                      (uint8)((TimerConfigPtr.TimerId & GTM_CHANNEL_NO_MASK) >> \
                                              GTM_CHANNEL_NO_OFF), GTM_ATOM_CH_UPDATE_ENABLE);

        /* [cover parentID={09813B13-924F-4130-AFBB-0E1966568D7B}]
        Enable ATOM channel with output disabled.
        [/cover] */
        Mcu_17_Gtm_AtomChannelEnable( \
                                      (uint8)((TimerConfigPtr.TimerId & GTM_MODULE_NO_MASK) >> \
                                              GTM_MODULE_NO_OFF), \
                                      (uint8)((TimerConfigPtr.TimerId & GTM_CHANNEL_NO_MASK) >> \
                                              GTM_CHANNEL_NO_OFF), 0U);

      }
    }
    /* Update the default compare value */
    ChannelVarPtr->CompareValue = LocalOcuChanPtr->DefaultThreshold;

    ChannelVarPtr++;
  }/* End of for loop */
}

#if (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={7792C321-88E7-4bbd-93FB-D34C606A2307}]      **
**                                                                            **
** Syntax :  static  uint32 Ocu_lInitCallVerify(                              **
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
** Return value:   uint32: Ocu Module is Initialized for the current core     **
**                         return OCU_ERROR_NOT_FOUND. Ocu Module is NOT      **
**                         Initialized for the current core return            **
**                         OCU_ERROR_FOUND                                    **
**                                                                            **
*******************************************************************************/
/*[cover parentID={7F5A4CE6-A065-494e-9B74-0654A5CB52D1}]
Safety Properties
[/cover]*/
static uint32 Ocu_lInitCallVerify(const uint8 ServiceId, const uint8 CoreId)
{
  uint32 ErrorFlag;
  uint32 CoreStatusPos;
  ErrorFlag = (uint32)OCU_ERROR_NOT_FOUND;
  CoreStatusPos = ((uint32)CoreId * (uint32)OCU_INIT_STATUS_SIZE);
  /* Verify whether Init had been called */
  /* [cover parentID={D1EE7FDE-0B37-4c56-BDDB-02BE6AF05358}]
  Is the core specific bit set in the global initialization status variable
  [/cover] */
  if(OCU_INITIALIZED != Mcal_GetBitAtomic(Ocu_InitStatus, \
                                          CoreStatusPos, OCU_INIT_STATUS_SIZE))
  {
    /* [cover parentID={ABA45981-8489-4053-A4D2-6F87D667136C}]
    Report an Error indicating that initialisation is not done.
    [/cover] */
    Ocu_lReportError(
      ServiceId,
      OCU_E_UNINIT);/* End of report error */
    /* [cover parentID={FC931E5B-A7F8-49a4-B478-639FCC8BE248}]
    Return an error flag indicating an error has occured.
    [/cover] */
    ErrorFlag = (uint32)OCU_ERROR_FOUND;
  }
  return (ErrorFlag);
}/* End of Ocu_lInitCallVerify() function */
#endif

#if (OCU_DEV_ERROR_DETECT == STD_ON) || (OCU_SAFETY_ENABLE == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={D2C75463-DDC9-4a0e-9C19-F0885262AC86}]      **
**                                                                            **
** Syntax :   static uint32 Ocu_lChannelVerify(                               **
**                              const uint8 ServiceId,                        **
**                              const Ocu_ChannelType Channel,                **
**                              const uint8 CoreId)                           **
**                                                                            **
** Description :      Local function :Service to verify whether proper        **
**                                    channel has been passed or              **
**                                    raise an error                          **
** [/cover]                                                                   **
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
** Return value:   uint32: If channel is valid return OCU_ERROR_NOT_FOUND.    **
**                         else OCU_ERROR_FOUND                               **
*******************************************************************************/
/*[cover parentID={7F5A4CE6-A065-494e-9B74-0654A5CB52D1}]
Safety Properties
[/cover]*/
static uint32 Ocu_lChannelVerify(
  const uint8 ServiceId,
  const Ocu_ChannelType Channel,
  const uint8 CoreId)
{
  uint32 ErrorFlag;
  #if (OCU_MULTICORE_ERROR_DETECT == STD_ON)   
  uint8 ExtractCoreId;
  #endif
  ErrorFlag = (uint32)OCU_ERROR_NOT_FOUND;
  /* [cover parentID={FB8B1FDC-0F0D-486c-BFE4-BB98B4B2E59D}]
  If invalid channel number has been sent
  [/cover] */
  if (Channel >= ((Ocu_ChannelType) OCU_MAX_CHANNELS ))
  {
    /* [cover parentID={F86B7B96-F548-43c5-8AF2-6FF92C5B0834}]
    Report an error indicating invalid channel.
    [/cover] */
    Ocu_lReportError(
      ServiceId,
      OCU_E_PARAM_INVALID_CHANNEL);/* End of report Error */
    /* [cover parentID={27C91E83-3119-47e9-80F4-B926E9D8D6E8}]
    Set error flag to return indicating an error in channel validation.
    [/cover] */
    ErrorFlag = (uint32)OCU_ERROR_FOUND;
  }
  #if (OCU_MULTICORE_ERROR_DETECT == STD_ON)
  else /* Channel is a valid channel */
  { 
        
    #if (OCU_SINGLE_CORE == STD_OFF)
    ExtractCoreId = \
                    (uint8)((Ocu_ConfigPtr->ChannelMapping[Channel] &
                             (OCU_CHNL_MAP_CORE_ID_MASK)) >> OCU_CHNL_MAP_CORE_ID_OFFSET);
    #else
    ExtractCoreId = OCU_SINGLE_CORE_ID;
    #endif
    /* Check if a channel is assigned to this core */
    /* [cover parentID={6A14284E-234A-44ad-95F0-AE694A954C01}]
    Is the extracted core id and invoked core id same
    [/cover] */
    if(ExtractCoreId != CoreId)
    {
      /* [cover parentID={7974F1F5-6D63-4cf8-B22B-790FA961BD3B}]
      Report an error indicating that the channel is not allocated to current
      core.
      [/cover] */
      Ocu_lReportMulticoreError(
        ServiceId,
        OCU_E_CORE_CHANNEL_MISMATCH);/* End of report Error */
      /* [cover parentID={27C91E83-3119-47e9-80F4-B926E9D8D6E8}]
      Set error flag to return indicating an error in channel validation.
      [/cover] */
      ErrorFlag = (uint32)OCU_ERROR_FOUND;
    }
  }
  #else
  UNUSED_PARAMETER(CoreId);
  #endif
  return (ErrorFlag);
}/* End of Ocu_lChannelVerify()*/
#endif

/*******************************************************************************
** Traceability: [cover parentID={9B005C97-37E0-45a4-9568-D5C5DB55C990}]      **
**                                                                            **
** Syntax :   static uint8 Ocu_lGetAtomPinAction(const uint16 HwUnitNumber    **
**                              const uint8 PinAction)                        **
**                                                                            **
** Description :      Local function :Get the pin action corresponding to HW  **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        None                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Reentrant                                               **
**                                                                            **
** Parameters (in):   PinAction - PinAction to be configured                  **
**                    HwUnitNumer - Hardware module and channel number        **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value:      uint8: PinAction(ACB Value with respect SL)             **
                             value to be configured in HW                     **
**                                                                            **
*******************************************************************************/
/*[cover parentID={7F5A4CE6-A065-494e-9B74-0654A5CB52D1}]
Safety Properties
[/cover]*/
static uint8 Ocu_lGetAtomPinAction(
  const uint16 HwUnitNumber,
  const uint8 PinAction)
{
  /* Pointer to ATOM channel Register */
  Ifx_GTM_ATOM_CH const *AtomChannelRegPtr;
  uint8 lPinAction;
  /* MISRA2012_RULE_11_3_JUSTIFICATION: GTM_ATOM_CH_POINTER does a typecast
   * to void and then to specific Mcu datatype Mcu_17_Gtm_AtomChArray to 
   * index to the proper ATOM channel's SFR from the base GTM SFR. 
   * No side effects seen by violating this MISRA */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: GTM_ATOM_CH_POINTER does a typecast
   * to void and then to specific Mcu datatype Mcu_17_Gtm_AtomChArray to 
   * index to the proper ATOM channel's SFR from the base GTM SFR. 
   * No side effects seen by violating this MISRA */



  AtomChannelRegPtr = GTM_ATOM_CH_POINTER( \
                      (uint8)((HwUnitNumber & GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF), \
                      (uint8)((HwUnitNumber & GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF));
  /* [cover parentID={469FC4AE-57AE-404f-A748-AAAC4B33E011}]
  Is the SL bit of the channel set?
  [/cover] */
  if(AtomChannelRegPtr->SOMC.B.SL == OCU_BIT_SET)
  {
    switch (PinAction)
    {
      /* [cover parentID={B2BB5D2B-7F8C-415a-83EA-19F170C51561}]
        Is the requested PinAction is to SET_HIGH
      [/cover] */
      case (uint8)OCU_SET_HIGH:
        lPinAction = ACB_SET_HIGH;
        break;
      /* [cover parentID={7C2D5066-1AA4-40db-A717-9D3CC04A072A}]
      Is the requested PinAction is to SET_LOW
      [/cover] */
      case (uint8)OCU_SET_LOW:
        lPinAction = ACB_SET_LOW;
        break;
      default:
        lPinAction = (uint8)PinAction;
        break;
    }
  }
  else
  {
    lPinAction = (uint8)PinAction;
  }
  return lPinAction;
}
#if (OCU_SET_PIN_ACTION_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={C411756E-5ED9-4c74-B411-66B319EA6015}]      **
**                                                                            **
** Syntax :   static void Ocu_lSetAtomPinAction(const uint16 HwUnitNumber,    **
**                              const uint8 PinAction)                        **
**                                                                            **
** Description :      Local function :Set the pin action corresponding to HW  **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        None                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Reentrant for different channels                        **
**                                                                            **
** Parameters (in):   PinAction - PinAction to be configured                  **
**                    HwUnitNumer - Hardware module and channel number        **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value:      None                                                    **
**                                                                            **
*******************************************************************************/
/*[cover parentID={7F5A4CE6-A065-494e-9B74-0654A5CB52D1}]
Safety Properties
[/cover]*/
LOCAL_INLINE void Ocu_lSetAtomPinAction(
  const uint16 HwUnitNumber,
  const uint8 PinAction)
{
  /* Pointer to ATOM channel Register */
  Ifx_GTM_ATOM_CH const *AtomChannelRegPtr;
  uint8 AcbValue;
   /* MISRA2012_RULE_11_3_JUSTIFICATION: GTM_ATOM_CH_POINTER does a typecast
    * to void and then to specific Mcu datatype Mcu_17_Gtm_AtomChArray to 
    * index to the proper ATOM channel's SFR from the base GTM SFR. 
    * No side effects seen by violating this MISRA */
   /* MISRA2012_RULE_11_5_JUSTIFICATION: GTM_ATOM_CH_POINTER does a typecast
    * to void and then to specific Mcu datatype Mcu_17_Gtm_AtomChArray to 
    * index to the proper ATOM channel's SFR from the base GTM SFR. 
    * No side effects seen by violating this MISRA */



  AtomChannelRegPtr = GTM_ATOM_CH_POINTER( \
                      (uint8)((HwUnitNumber & GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF), \
                      (uint8)((HwUnitNumber & GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF));

  /*Calculate the pin action as per the current pin level*/
  AcbValue = Ocu_lGetAtomPinAction( \
                                    HwUnitNumber, \
                                    (uint8)PinAction);
  /* Update ACB value for next compare match */
  Mcal_SetBitAtomic((&(AtomChannelRegPtr->SOMC.U)), \
                    OCU_ATOM_SOMC_ACB_1_0_POS, \
                    OCU_ATOM_SOMC_ACB_1_0_LEN, \
                    (uint32)(AcbValue & OCU_ATOM_SOMC_ACB_1_0_MASK));

  /* MISRA2012_RULE_2_2_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer AtomChannelRegPtr is
   * accessed using assembly instruction. */
  /* MISRA2012_RULE_2_7_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the variable PinAction is
   * accessed using assembly instruction. */
}
#endif
/*******************************************************************************
** Traceability: [cover parentID={C6FFC98A-FCE3-4233-8D10-AFF4E4833B76}]      **
**                                                                            **
** Syntax :   static Ocu_ValueType Ocu_lGetCounter(                           **
**                              const uint8 HwUnit,                           **
**                              const uint16 HwUnitNumer,                     **
**                              const uint8 ClockSource)                      **
**                                                                            **
** Description :      Local function :Service to read current counter value   **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        None                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Reentrant                                               **
**                                                                            **
** Parameters (in):   HwUnit - Type of hardware used                          **
**                    HwUnitNumer - Hardware module and channel number        **
**                    ClockSource - Clock source selected for that HW Unit    **
**                                                                            **
** Parameters (out):  Ocu_ValueType                                           **
**                                                                            **
** Return value:   Ocu_ValueType: Current counter value                       **
**                                                                            **
*******************************************************************************/
/*[cover parentID={7F5A4CE6-A065-494e-9B74-0654A5CB52D1}]
Safety Properties
[/cover]*/
static Ocu_ValueType Ocu_lGetCounter(
  const uint8 HwUnit,
  const uint16 HwUnitNumer,
  const uint8 ClockSource)
{
  Ocu_ValueType CounterValue;
  /* Pointer to ATOM channel Register */
  const Ifx_GTM_ATOM_CH *AtomChannelRegPtr;
  /* Pointer to TOM channel Register */
  const Ifx_GTM_TOM_CH *TomChannelRegPtr;
  switch(HwUnit)
  {
    /* [cover parentID={6A0787D9-9E10-409b-9E8A-4531725B97DA}]
    Is the channel using TOM?
    [/cover] */

    case OCU_GTM_TOM:
      /* MISRA2012_RULE_11_3_JUSTIFICATION: GTM_TOM_CH_POINTER does a typecast
       * to void and then to specific Mcu datatype Mcu_17_Gtm_TomChArray to 
       * index to the proper TOM channel's SFR from the base GTM SFR. 
       * No side effects seen by violating this MISRA */
      /* MISRA2012_RULE_11_5_JUSTIFICATION: GTM_TOM_CH_POINTER does a typecast
       * to void and then to specific Mcu datatype Mcu_17_Gtm_TomChArray to 
       * index to the proper TOM channel's SFR from the base GTM SFR. 
       * No side effects seen by violating this MISRA */

      TomChannelRegPtr = GTM_TOM_CH_POINTER( \
                                             (uint8)((HwUnitNumer & GTM_MODULE_NO_MASK) >> \
                                                 GTM_MODULE_NO_OFF), \
                                             (uint8)((HwUnitNumer & GTM_CHANNEL_NO_MASK) >> \
                                                 GTM_CHANNEL_NO_OFF));
      CounterValue = TomChannelRegPtr->CN0.U;
      /* [cover parentID={3F058B85-88E8-418d-9E6B-7CB435F698E6}]
      Read free running counter value and mask with 16bit value
      [/cover] */
      CounterValue = CounterValue & TOM_MASK_LSB_16BITS;
      /* No critical section is needed between the two reads(CN0 and CM0) as
        CN0 isfree running and CM0 is modified only in INIT and not anywhere
        else.*/
      break;
    /* [cover parentID={6193E538-9259-43a0-8BA3-B8C358874665}]
      Is the channel using Atom ?
      [/cover] */
    case OCU_GTM_ATOM:
      /* MISRA2012_RULE_11_3_JUSTIFICATION: GTM_ATOM_CH_POINTER does a typecast
       * to void and then to specific Mcu datatype Mcu_17_Gtm_AtomChArray to 
       * index to the proper ATOM channel's SFR from the base GTM SFR. 
       * No side effects seen by violating this MISRA */
      /* MISRA2012_RULE_11_5_JUSTIFICATION: GTM_ATOM_CH_POINTER does a typecast
       * to void and then to specific Mcu datatype Mcu_17_Gtm_AtomChArray to 
       * index to the proper ATOM channel's SFR from the base GTM SFR. 
       * No side effects seen by violating this MISRA */



      AtomChannelRegPtr = GTM_ATOM_CH_POINTER( \
                          (uint8)((HwUnitNumer & GTM_MODULE_NO_MASK) >> \
                                  GTM_MODULE_NO_OFF), \
                          (uint8)((HwUnitNumer & GTM_CHANNEL_NO_MASK) >> \
                                  GTM_CHANNEL_NO_OFF));
      CounterValue = AtomChannelRegPtr->CN0.U;
      /* Masking unwanted bits */
      CounterValue = CounterValue & ATOM_MASK_LSB_24BITS;
      /* No critical section is needed between the two reads(CN0 and CM0) as
        CN0 isfree running and CM0 is modified only in INIT and not anywhere
        else.*/
      break;
    default:/*OCU_GTM_ATOM_SHARED*/
      /* [cover parentID={34BAA6B2-031D-4f9d-A869-BE1408A2B431}]
        Is the counter TBU_TS0 ?
        [/cover] */
      if(ClockSource == OCU_GTM_TBU_TS0)/*TS0*/
      {
        /* [cover parentID={85CB907F-DB10-44fe-BD42-508DE78D2F2C}]
        Read free running counter TBU_TS0 value depending on the resolution
        configured and mask with 24bit value,
        [/cover] */
        CounterValue = GTM_TBU_CH0_BASE.U;
        /* [cover parentID={20DC6E54-40D2-4dd0-8089-119E466A8943}]
        Is the counter TBU_TS1?
        [/cover] */
        /* Masking unwanted bits */
        if(GTM_TBU_CH0_CTRL.B.LOW_RES == OCU_TBU_LOW_RES)
        {
          /* TBU channel uses lower counter bits (bit 0 to 23) */
          CounterValue = CounterValue & ATOM_MASK_LSB_24BITS;
        }
        else
        {
          /* TBU channel uses upper counter bits (bit 3 to 26)  */
          CounterValue = ((CounterValue >> LOW_RES_BIT_SHIFT) \
                          & ATOM_MASK_LSB_24BITS);
        }
      }
      /* [cover parentID={3F058B85-88E8-418d-9E6B-7CB435F698E6}]
        Read free running counter value and mask with 16bit value
        [/cover] */
      else if(ClockSource == OCU_GTM_TBU_TS1)/*TS1*/
      {
        /* [cover parentID={45F681A5-F60D-4309-9DB6-56C1DD976D4D}]
        Read free running counter TBU_TS1 and mask with 24bit value.
        [/cover] */
        CounterValue = GTM_TBU_CH1_BASE.U;
        /* Masking unwanted bits */
        CounterValue = CounterValue & ATOM_MASK_LSB_24BITS;
      }
      else
      {
        /* [cover parentID={0ADD740C-947A-49e7-8191-5042F2AD6EE6}]
        Read free running counter TBU_TS1 value and mask with 24bit value
        [/cover] */
        CounterValue = GTM_TBU_CH2_BASE.U;
        /* Masking unwanted bits */
        CounterValue = CounterValue & ATOM_MASK_LSB_24BITS;
      }
      break;
  }
  return CounterValue;
}/* End of Ocu_lGetCounter()*/


/*******************************************************************************
** Traceability: [cover parentID={768AB65C-71F0-4cfc-AA56-1133D73CEA3A}]      **
**                                                                            **
** Syntax :   static Ocu_ReturnType Ocu_lGetReturnValue(                      **
**                              const Ocu_ValueType CompareValue,             **
**                              const Ocu_ValueType CounterValue,             **
**                              const Ocu_ValueType ReferenceValue,           **
**                              const Ocu_ValueType MaxCounter)               **
**                                                                            **
** Description :      Local function :Service to calculate the return value   **
**                    for SetAbosluteThreshold and SetRealativeThreshold      **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        None                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Reentrant                                               **
**                                                                            **
** Parameters (in):   CompareValue - value to mark end of ref. interval       **
**                    CounterValue - counter value at the time of writing     **
**                    ReferenceValue - value to mark start of ref. interval   **
**                    MaxCounter - counter maximum value                      **
**                                                                            **
** Parameters (out):  Ocu_ReturnType                                          **
**                                                                            **
** Return value:   Ocu_ReturnType: compare value IN/OUT reference interval    **
**                                                                            **
*******************************************************************************/
/*[cover parentID={7F5A4CE6-A065-494e-9B74-0654A5CB52D1}]
Safety Properties
[/cover]*/
static uint32 Ocu_lGetReturnValue(
  const Ocu_ValueType CompareValue,
  const Ocu_ValueType CounterValue,
  const Ocu_ValueType ReferenceValue,
  const Ocu_ValueType MaxCounter)
{
  uint32 ReturnValue;
  Ocu_ValueType lCompareValue;
  Ocu_ValueType lCounterValue;

  lCounterValue = CounterValue;
  /* [cover parentID={0B9F922B-B274-4706-9AB2-A5FC8F0A5AA4}]
  Is the compare value in past ? (i.e.,)
  Is Compare value less than Reference Value ?
  [/cover] */
  if(CompareValue < ReferenceValue)
  {
    lCompareValue = CompareValue + MaxCounter;
    if(CounterValue < CompareValue)
    {
      lCounterValue = CounterValue + MaxCounter;
    }
  }
  else
  {
    lCompareValue = CompareValue;
  }

  /* [cover parentID={38407688-E7A8-4246-B2F9-C344B1A6B903}]
  Is the counter value within the reference interval?
  [/cover] */
  if(((lCounterValue - lCompareValue)) > \
      ((lCounterValue - ReferenceValue)))
  {
    /* [cover parentID={37C3213F-4C5C-4717-9FB8-C1536EAE3562}]
    Return OCU_CM_IN_REF_INTERVAL
    [/cover] */
    ReturnValue = 1U;
  }
  else
  {
    /* [cover parentID={998E9422-3393-4eab-92C1-D82203B38B89}]
    Return OCU_CM_OUT_REF_INTERVAL
    [/cover] */
    ReturnValue = 0U;
  }
  return (ReturnValue);
}


/*******************************************************************************
** Traceability: [cover parentID={3B49A102-50F6-43d7-8F92-1DE3B293C441}]      **
**                                                                            **
** Syntax :   static Ocu_ValueType Ocu_lSetAtomCompare(                       **
**                              const Ocu_ValueType CompareValue,             **
**                              const Ocu_ValueType ReferenceValue,           **
**                              const Ocu_ChannelConfigType *const ChanPtr,   **
**                              const uint8 PinAction,                        **
**                              const Ocu_ChannelType Channel)                **
**                                                                            **
** Description :      Local function :Service to set compare value for atom   **
**                                    channel                                 **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        None                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Reentrant for different channels                        **
**                                                                            **
** Parameters (in):   CompareValue - New compare value to be updated          **
**                    ReferenceValue - Reference to identify if the compare   **
**                                    match occurs in the given interval      **
**                    ChanPtr - Pointer to channel configuration              **
**                    PinAction - Pinaction required on next compare match    **
**                    ChannelNumber - Numeric identifier of the OCU channel   **
**                                                                            **
** Parameters (out):  Ocu_ValueType                                           **
**                                                                            **
** Return value:   Ocu_ValueType: Current counter value                       **
**                                                                            **
*******************************************************************************/
/*[cover parentID={7F5A4CE6-A065-494e-9B74-0654A5CB52D1}]
Safety Properties
[/cover]*/
static Ocu_ReturnType Ocu_lSetAtomCompare(
  const Ocu_ValueType CompareValue,
  const Ocu_ValueType ReferenceValue,
  const Ocu_ChannelConfigType *const ChanPtr,
  const uint8 PinAction,
  const Ocu_ChannelType Channel)
{
  /* Pointer to ATOM channel Register */
  Ifx_GTM_ATOM_CH *AtomChannelRegPtr;
  Ocu_ValueType CounterValueRead1;
  Ocu_ValueType CounterValueRead2;
  Ocu_ReturnType ReturnValue = OCU_CM_OUT_REF_INTERVAL;
  uint32 ReturnValue1;
  uint32 ReturnValue2;
  const uint32* ChannelStatusPtr;
  uint32 lCompareValue = CompareValue;

  uint8 AcbValue;
  volatile uint32 dummy1;
  volatile uint32 dummy2;
  uint8 CoreId;
  uint8 CoreChIndex;
  /* Get core id which is executing currently */
  CoreId = OCU_GETCOREID();

  #if (OCU_SINGLE_CORE == STD_OFF)
  /* Initialize OCU configured channel ROM pointer */
  CoreChIndex = (uint8)(Ocu_ConfigPtr->ChannelMapping[Channel] & \
                        OCU_CHNL_MAP_CHNL_INDEX_MASK);
  #else
  CoreChIndex = (uint8)Channel;
  #endif

  /* Channel specific status variable */
  ChannelStatusPtr = &(Ocu_RootChannelVar[CoreId][CoreChIndex].Status);

  /*Calculate the pin action as per the current pin level*/
  AcbValue = Ocu_lGetAtomPinAction( \
                                    ChanPtr->OcuProperties.AssignedHwUnitNumber, \
                                    (uint8)PinAction);
   /* MISRA2012_RULE_11_3_JUSTIFICATION: GTM_ATOM_CH_POINTER does a typecast
    * to void and then to specific Mcu datatype Mcu_17_Gtm_AtomChArray to 
    * index to the proper ATOM channel's SFR from the base GTM SFR. 
    * No side effects seen by violating this MISRA */
   /* MISRA2012_RULE_11_5_JUSTIFICATION: GTM_ATOM_CH_POINTER does a typecast
    * to void and then to specific Mcu datatype Mcu_17_Gtm_AtomChArray to 
    * index to the proper ATOM channel's SFR from the base GTM SFR. 
    * No side effects seen by violating this MISRA */



  AtomChannelRegPtr = GTM_ATOM_CH_POINTER( \
                      (uint8)((ChanPtr->OcuProperties.AssignedHwUnitNumber & \
                               GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF), \
                      (uint8)((ChanPtr->OcuProperties.AssignedHwUnitNumber & \
                               GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF));
  switch(ChanPtr->OcuProperties.ClockSelect)
  {
    /* [cover parentID={A321C730-EDEC-407c-9BB3-DA6CB9601A94}]
    Is the reference clock TBU_TS0?
    [/cover] */
    case OCU_GTM_TBU_TS0: /* TS0 */

      /* Read current counter value */
      CounterValueRead1 = Ocu_lGetCounter(ChanPtr->OcuProperties.AssignedHwUnit,
                                          ChanPtr->OcuProperties.AssignedHwUnitNumber,
                                          ChanPtr->OcuProperties.ClockSelect);
      dummy1 = AtomChannelRegPtr->SR0.U;
      dummy2 = AtomChannelRegPtr->SR1.U;
      AtomChannelRegPtr->SOMC.B.ACB_4_3_2 = ATOM_COMPARE_CCU0;
      AtomChannelRegPtr->SOMC.B.ACB_1_0 = AcbValue;
      AtomChannelRegPtr->CM0.U = CompareValue;
      AtomChannelRegPtr->CM1.U = 0U;
      CounterValueRead2 = Ocu_lGetCounter(ChanPtr->OcuProperties.AssignedHwUnit,
                                          ChanPtr->OcuProperties.AssignedHwUnitNumber,
                                          ChanPtr->OcuProperties.ClockSelect);

      break;
    /* [cover parentID={3F3FA6C2-DAA0-486e-AE60-C6CDFA67C4A9}]
    Is the reference clock TBU_TS1?
    [/cover] */
    case OCU_GTM_TBU_TS1: /* TS1 */

      /* Read current counter value */
      CounterValueRead1 = Ocu_lGetCounter(ChanPtr->OcuProperties.AssignedHwUnit,
                                          ChanPtr->OcuProperties.AssignedHwUnitNumber,
                                          ChanPtr->OcuProperties.ClockSelect);
      dummy1 = AtomChannelRegPtr->SR0.U;
      dummy2 = AtomChannelRegPtr->SR1.U;
      AtomChannelRegPtr->SOMC.B.ACB_4_3_2 = ATOM_COMPARE_CCU1;
      AtomChannelRegPtr->CM0.U = 0U;
      AtomChannelRegPtr->CM1.U = CompareValue;

      AtomChannelRegPtr->SOMC.B.ACB_1_0 = AcbValue;
      CounterValueRead2 = Ocu_lGetCounter(ChanPtr->OcuProperties.AssignedHwUnit,
                                          ChanPtr->OcuProperties.AssignedHwUnitNumber,
                                          ChanPtr->OcuProperties.ClockSelect);

      break;
    default: /* TS2 */
      /* Read current counter value */
      CounterValueRead1 = Ocu_lGetCounter(ChanPtr->OcuProperties.AssignedHwUnit,
                                          ChanPtr->OcuProperties.AssignedHwUnitNumber,
                                          ChanPtr->OcuProperties.ClockSelect);
      dummy1 = AtomChannelRegPtr->SR0.U;
      dummy2 = AtomChannelRegPtr->SR1.U;
      AtomChannelRegPtr->SOMC.B.ACB_4_3_2 = ATOM_COMPARE_CCU1;
      AtomChannelRegPtr->CM0.U = 0U;
      AtomChannelRegPtr->CM1.U = CompareValue;

      AtomChannelRegPtr->SOMC.B.ACB_1_0 = AcbValue;
      CounterValueRead2 = Ocu_lGetCounter(ChanPtr->OcuProperties.AssignedHwUnit,
                                          ChanPtr->OcuProperties.AssignedHwUnitNumber,
                                          ChanPtr->OcuProperties.ClockSelect);
      break;
  }
  /* [cover parentID={81F55DFA-634C-453b-B791-AFA486360355}]
  If the channel's next compare match is for reprogramming
  [/cover] */  
  if (OCU_BIT_SET
      == Mcal_GetBitAtomic(*ChannelStatusPtr, OCU_CHNL_ATOM_RE_PROG_ISR_POS,
                           OCU_CHNL_ATOM_RE_PROG_ISR_BIT_LENGTH))
  {
    lCompareValue = (CompareValue + CNT_BORDER_VAL_BT_PAST_FUTURE) & \
                    (ATOM_MASK_LSB_24BITS);

  }
  ReturnValue1 = Ocu_lGetReturnValue(lCompareValue, CounterValueRead1,
                                     ReferenceValue, ChanPtr->MaxCounterValue);


  ReturnValue2 = Ocu_lGetReturnValue(lCompareValue, CounterValueRead2,
                                     ReferenceValue, ChanPtr->MaxCounterValue);

  /* [cover parentID={121BC70B-C850-460d-BAA5-C50FC6A98260}]
  Identify and return if the compare match occurs in current reference inteval
  [/cover] */
  if((ReturnValue1 | ReturnValue2) == TRUE)
  {
    ReturnValue = OCU_CM_IN_REF_INTERVAL;
  }

  UNUSED_PARAMETER(dummy1);
  UNUSED_PARAMETER(dummy2);

  return (ReturnValue);
}

/*******************************************************************************
** Traceability: [cover parentID={DCDF2C6A-9E2E-4a74-9302-A91DD2F0DC9E}]      **
**                                                                            **
** Syntax :   static void Ocu_lEnDisCCU1Irq( const uint8 HwUnit,              **
**                              const uint16 HwUnitNumer,                     **
**                              const uint8 EnDis)                            **
**                                                                            **
** Description :      Local function :Service to enable or disable CCU1       **
**                    interrupt for a TOM or ATOM channel                     **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        None                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Reentrant for different channels                        **
**                                                                            **
** Parameters (in):   HwUnit - Type of hardware used                          **
**                    HwUnitNumer - Hardware module and channel number        **
**                    EnDis - Enable/Disable input                            **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value:   None                                                       **
**                                                                            **
*******************************************************************************/
/*[cover parentID={7F5A4CE6-A065-494e-9B74-0654A5CB52D1}]
Safety Properties
[/cover]*/
static void Ocu_lEnDisCCU1Irq(const uint8 HwUnit,
                              const uint16 HwUnitNumber,
                              const uint8 EnDis)
{
  /* Pointer to ATOM channel Register */
  Ifx_GTM_ATOM_CH *AtomChannelRegPtr;
  /* Pointer to TOM channel Register */
  Ifx_GTM_TOM_CH *TomChannelRegPtr;
  /* Enable/Disable interrupts */
  switch(HwUnit)
  {
    /* [cover parentID={D4B74D99-C747-4e61-A10B-A789F593E814}]
      Is the channel using TOM?
      [/cover] */

    case OCU_GTM_TOM:
      /* MISRA2012_RULE_11_3_JUSTIFICATION: GTM_TOM_CH_POINTER does a typecast
       * to void and then to specific Mcu datatype Mcu_17_Gtm_TomChArray to 
       * index to the proper TOM channel's SFR from the base GTM SFR. 
       * No side effects seen by violating this MISRA */
      /* MISRA2012_RULE_11_5_JUSTIFICATION: GTM_TOM_CH_POINTER does a typecast
       * to void and then to specific Mcu datatype Mcu_17_Gtm_TomChArray to 
       * index to the proper TOM channel's SFR from the base GTM SFR. 
       * No side effects seen by violating this MISRA */

      TomChannelRegPtr = GTM_TOM_CH_POINTER( \
                                             (uint8)((HwUnitNumber & GTM_MODULE_NO_MASK) >> \
                                                 GTM_MODULE_NO_OFF), \
                                             (uint8)((HwUnitNumber & GTM_CHANNEL_NO_MASK) >> \
                                                 GTM_CHANNEL_NO_OFF));

      if(EnDis == ENABLE_INTERRUPTS)
      {
        /* [cover parentID={880CFEFB-FAA5-436c-9CA1-F72F2607F851}]
        Clear interrupt flags if enabling of interrupts is requested.
        [/cover] */
        TomChannelRegPtr->IRQ.NOTIFY.U = OCU_CLR_PENDING_NOTIFICATION_FLAGS;


      }


      TomChannelRegPtr->IRQ.EN.B.CCU1TC_IRQ_EN = EnDis;
      break;
    /* [cover parentID={1E293CF0-DC2D-460e-B9EF-F2FF59FFCA49}]
    Is the channel using ATOM?
    [/cover] */
    case OCU_GTM_ATOM:
      /* MISRA2012_RULE_11_3_JUSTIFICATION: GTM_ATOM_CH_POINTER does a typecast
       * to void and then to specific Mcu datatype Mcu_17_Gtm_AtomChArray to 
       * index to the proper ATOM channel's SFR from the base GTM SFR. 
       * No side effects seen by violating this MISRA */
      /* MISRA2012_RULE_11_5_JUSTIFICATION: GTM_ATOM_CH_POINTER does a typecast
       * to void and then to specific Mcu datatype Mcu_17_Gtm_AtomChArray to 
       * index to the proper ATOM channel's SFR from the base GTM SFR. 
       * No side effects seen by violating this MISRA */



      AtomChannelRegPtr = GTM_ATOM_CH_POINTER( \
                          (uint8)((HwUnitNumber & GTM_MODULE_NO_MASK) >> \
                                  GTM_MODULE_NO_OFF), \
                          (uint8)((HwUnitNumber & GTM_CHANNEL_NO_MASK) >> \
                                  GTM_CHANNEL_NO_OFF));

      if(EnDis == ENABLE_INTERRUPTS)
      {
        /* [cover parentID={D5BEB593-EA42-4100-B704-2502A7086A71}]
        Clear interrupt flags if enabling of interrupts is requested.
        [/cover] */
        AtomChannelRegPtr->IRQ.NOTIFY.U = OCU_CLR_PENDING_NOTIFICATION_FLAGS;


      }

      AtomChannelRegPtr->IRQ.EN.B.CCU1TC_IRQ_EN = EnDis;
      break;
    default:/*OCU_GTM_ATOM_SHARED*/
      /* No action needed */
      break;
  }
}

#if (OCU_DEV_ERROR_DETECT == STD_ON)|| (OCU_SAFETY_ENABLE == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={EEB371E3-904D-40c8-84C9-FE053EB43C09}]      **
**                                                                            **
** Syntax : static void Ocu_lReportError( const uint8 ApiId,                  **
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
/*[cover parentID={7F5A4CE6-A065-494e-9B74-0654A5CB52D1}]
Safety Properties
[/cover]*/
static void Ocu_lReportError(const uint8 ApiId,
                             const uint8 ErrorId)
{
  /* [cover parentID={0BB214E2-1D6B-450e-B2E1-31AB44B66347}]
  If DET reporting is enabled
  [/cover] */
  #if (OCU_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={097372D0-8CB0-4173-A7B8-C7CEA09BFA64}]
  Report DET
  [/cover] */
  (void)Det_ReportError(
    OCU_MODULE_ID,
    OCU_INSTANCE_ID,
    ApiId,
    ErrorId);/* End of report to DET */
  #endif
  #if (OCU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={8A3310AB-4EF5-4075-98D1-AD3A3B20D2B1}]
  Report Safety Error
  [/cover] */
  Mcal_ReportSafetyError(
    OCU_MODULE_ID,
    OCU_INSTANCE_ID,
    ApiId,
    ErrorId);/* End of report to Safety */
  #endif
}
#endif

#if (OCU_MULTICORE_ERROR_DETECT == STD_ON)|| (OCU_SAFETY_ENABLE == STD_ON)

/*******************************************************************************
** Traceability: [cover parentID={DFC88B2A-87E0-4ea3-82AC-82734D60CD45}]      **
**                                                                            **
** Syntax : static void Ocu_lReportMulticoreError( const uint8 ApiId,         **
**                                          const uint8 ErrorId)              **
**                                                                            **
** Description :    Function to report Safety Error and Multicore DET         **
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
/*[cover parentID={7F5A4CE6-A065-494e-9B74-0654A5CB52D1}]
Safety Properties
[/cover]*/
static void Ocu_lReportMulticoreError(const uint8 ApiId,
                                      const uint8 ErrorId)
{
  #if (OCU_MULTICORE_ERROR_DETECT == STD_ON)
  /* [cover parentID={77EDFB3C-BE90-4cc5-95DD-52AFB533868C}]
  Report DET
  [/cover] */
  (void)Det_ReportError(
    OCU_MODULE_ID,
    OCU_INSTANCE_ID,
    ApiId,
    ErrorId);/* End of report to DET */
  #endif
  #if (OCU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={D771FD3F-072A-4e70-8063-9E178335040C}]
  Report Safety Error
  [/cover] */
  Mcal_ReportSafetyError(
    OCU_MODULE_ID,
    OCU_INSTANCE_ID,
    ApiId,
    ErrorId);/* End of report to Safety */
  #endif
}
#endif

/*******************************************************************************
**                      Interrupt Function Definitions                        **
 ******************************************************************************/

/*******************************************************************************
** Traceability: [cover parentID={BD077DF6-DCFE-4332-830F-8E6170E01DAB}]      **
**                                                                            **
** Syntax : void Ocu_Timer_Isr(const uint32 LogicalChannelId)                 **
**                                                                            **
** Description : Callback from MCU to service Timer interrupts                **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x20                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant for different channels                              **
**                                                                            **
** Parameters (in): LogicalChannelId - Logical Channel Identifier             **
**                  flags   - Status of IRQ_NOTIFY flag                       **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value: None                                                         **
**                                                                            **
*******************************************************************************/
void Ocu_Timer_Isr (const uint32 LogicalChannelId, uint32 flags)
/*MISRA2012_RULE_8_3_JUSTIFICATION:LogicalChannelId parameter name is different 
  from prior declaration. Since parameters type is same to the declaration, No
  side effects foreseen by violating this MISRA rule*/
{
  const Ocu_ChannelConfigType *LocalOcuChanPtr; /* ROM pointer */
  uint8 CoreId;
  #if (OCU_SAFETY_ENABLE == STD_ON)
  uint8 ExtractCoreId;
  uint32 ErrorFlag;
  uint32 ChannelStatusFlag;
  #endif
  uint32* ChannelStatusPtr;
  uint8 CoreChIndex;
  Ocu_ValueType AbsoluteValue;
  /* Get core id which is executing currently */
  CoreId = OCU_GETCOREID();
  Ocu_ChannelType Channel = (Ocu_ChannelType)(LogicalChannelId & OCU_CHANNEL_MSK);
  
  #if (OCU_SAFETY_ENABLE == STD_ON)

  /*Perform pre-ISR checks(Init and channel validity)*/
  /* [cover parentID={6AA07C4B-E9A4-4e36-8C2D-0B453B581ECC}]
  Safety measures reporting safety errors
  [/cover] */
  ErrorFlag = Ocu_lIsrSafetyCheck(Channel, CoreId);
  /* [cover parentID={26FB44D6-F52C-4ddb-9132-F040A16717B1}]
     Are pre-ISR check passed?
     [/cover] */

  if ((ErrorFlag != OCU_ERROR_FOUND))
  {
    #if (OCU_SINGLE_CORE == STD_OFF)
    ExtractCoreId = (uint8) ((Ocu_ConfigPtr->ChannelMapping[Channel]
                              & (OCU_CHNL_MAP_CORE_ID_MASK)) >> 8U);
    #else
    ExtractCoreId = OCU_SINGLE_CORE_ID;
    #endif
    /* [cover parentID={19B3AFE7-9895-4c70-8876-88B9FC1405F9}]
       Core validation
       [/cover] */
    if (ExtractCoreId != CoreId)
    {
      /* [cover parentID={E758523A-9B65-479e-9F63-8512C778CD2F}]
         Report a safety error to indicate invalid ISR
         [/cover] */
      Mcal_ReportSafetyError(
        OCU_MODULE_ID,
        OCU_INSTANCE_ID, OCU_SID_ISR,
        (uint8)OCU_E_INVALID_ISR_CHANNEL_CORE_MISMATCH);/* End of report error */
      ErrorFlag = (uint32) OCU_ERROR_FOUND;
    }
  }
  if (ErrorFlag != OCU_ERROR_FOUND)
  #endif
  {
    /* Extract core specific channel index */
    #if (OCU_SINGLE_CORE == STD_OFF)
    CoreChIndex = ((uint8) (Ocu_ConfigPtr->ChannelMapping[Channel]) &
                   OCU_CHNL_MAP_CHNL_INDEX_MASK);
    #else
    CoreChIndex = Channel;
    #endif




    LocalOcuChanPtr = &((Ocu_ConfigPtr->CoreConfig[CoreId]->ChannelConfigPtr)\
                        [CoreChIndex]);
    /* Channel specific status variable */
    ChannelStatusPtr = &(Ocu_RootChannelVar[CoreId][CoreChIndex].Status);
    #if (OCU_SAFETY_ENABLE == STD_ON)
    ChannelStatusFlag = Mcal_GetBitAtomic(*ChannelStatusPtr, OCU_CHNL_STATUS_POS, \
                                          OCU_CHNL_STATUS_BIT_LENGTH);

    /* [cover parentID={4CB15F0B-E5AD-455b-B6BA-3A882C1AFA9C}]
       Is the channel in RUNNING state?
       [/cover] */

    if ((OCU_CHANNEL_STOPPED != ChannelStatusFlag))
    #endif
    {
      /* Call the hardware specific ISR */
      switch (LocalOcuChanPtr->OcuProperties.AssignedHwUnit)
      {
        /* [cover parentID={AF19FB56-C105-4e01-868F-A4F99B7356DA}]
        Is the channel using ATOM-Shared counter mode?
        [/cover] */
        case OCU_GTM_ATOM_SHARED:

          /* [cover parentID={9BEB105B-652E-4f82-8BA1-91D07395D4FD}]
          If notification required
          [/cover] */
          if (((LocalOcuChanPtr->OcuProperties.ClockSelect == OCU_GTM_TBU_TS0)
               && ((flags & CCU0_INT_NOTIFY_SET) == CCU0_INT_NOTIFY_SET))
              || (((LocalOcuChanPtr->OcuProperties.ClockSelect == OCU_GTM_TBU_TS1)
                   || (LocalOcuChanPtr->OcuProperties.ClockSelect == OCU_GTM_TBU_TS2))
                  && ((flags & CCU1_INT_NOTIFY_SET) == CCU1_INT_NOTIFY_SET)))
          {

            AbsoluteValue =
              Ocu_RootChannelVar[CoreId][CoreChIndex].CompareValue;
            /* [cover parentID={A0A57347-AB31-4abd-8702-0A551947CF47}]
            Is the channel re-program flag set?
            [/cover] */
            if (OCU_BIT_SET
                == Mcal_GetBitAtomic(*ChannelStatusPtr,
                                     OCU_CHNL_ATOM_RE_PROG_ISR_POS,
                                     OCU_CHNL_ATOM_RE_PROG_ISR_BIT_LENGTH))
            {

              /* Reprogram ATOM-SOMC compare matches */
              Mcal_SetBitAtomic((ChannelStatusPtr),
                                OCU_CHNL_ATOM_RE_PROG_ISR_POS,
                                OCU_CHNL_ATOM_RE_PROG_ISR_BIT_LENGTH, (uint32)OCU_BIT_RESET);


              (void) Ocu_lSetAtomCompare(AbsoluteValue, 0, LocalOcuChanPtr,
                                         (uint8) Mcal_GetBitAtomic(*ChannelStatusPtr,
                                             OCU_CHNL_PIN_ACTION_POS, OCU_CHNL_PIN_ACTION_BIT_LENGTH),
                                         (uint8)Channel);
            }
            else
            {
              Mcal_SetBitAtomic((ChannelStatusPtr),
                                OCU_CHNL_ATOM_RE_PROG_ISR_POS,
                                OCU_CHNL_ATOM_RE_PROG_ISR_BIT_LENGTH, (uint32)OCU_BIT_SET);
              (void) Ocu_lSetAtomCompare(
                ((AbsoluteValue + CNT_BORDER_VAL_BT_PAST_FUTURE) & \
                 (ATOM_MASK_LSB_24BITS)), 0, LocalOcuChanPtr, \
                (uint8) OCU_DISABLE, (uint8)Channel);
              /* Verify whether Notification required */
              /* [cover parentID={63264110-9873-488d-9E81-876FB0AEA22B}]
               If notification required
               [/cover] */
              if (OCU_ENABLE_NOTIFICATION
                  == Mcal_GetBitAtomic(*ChannelStatusPtr,
                                       OCU_CHNL_NOTIF_PRESENCE_POS, OCU_CHNL_NOTIF_BIT_LENGTH))
              {
                /* [cover parentID={AA682B90-EDB8-4278-A357-10A47D3A364F}]
                 Call Notification required
                 [/cover] */
                (LocalOcuChanPtr->NotificationPointer)();
              }
            }
          }
          #if (OCU_SAFETY_ENABLE == STD_ON)
          else
          {
            Mcal_ReportSafetyError(
              OCU_MODULE_ID,
              OCU_INSTANCE_ID, OCU_SID_ISR,
              (uint8) OCU_E_INVALID_ISR_COMP_INVALID);
            /* End of report error */
          }
          #endif
          break;
        default: /*OCU_GTM_ATOM AND OCU_GTM_TOM*/
          /* Verify whether Notification required */
          /* [cover parentID={11E7802F-9472-420a-950B-A0AEF5025537}]
           If notification required
           [/cover] */
          if ((OCU_ENABLE_NOTIFICATION
               == Mcal_GetBitAtomic(*ChannelStatusPtr, OCU_CHNL_NOTIF_PRESENCE_POS,
                                    OCU_CHNL_NOTIF_BIT_LENGTH)) && (flags == CCU1_INT_NOTIFY_SET))
          {

            /* [cover parentID={A85A71F3-D215-44e9-BBAE-402E9530BBF6}]
             Call Notification required
             [/cover] */
            (LocalOcuChanPtr->NotificationPointer)();
          }
          #if (OCU_SAFETY_ENABLE == STD_ON)
          else
          {
            /* [cover parentID={B7BDBFCE-79AE-4419-AB4E-5C0CB0FDFAEC}]
               Report a safety error to indicate invalid ISR
               [/cover] */

            Mcal_ReportSafetyError(
              OCU_MODULE_ID,
              OCU_INSTANCE_ID, OCU_SID_ISR,
              (uint8) OCU_E_INVALID_ISR_COMP_INVALID);
            /* End of report error */
          }
          #endif
          break;
      }
    }
    #if (OCU_SAFETY_ENABLE == STD_ON)
    else
    {
      /* [cover parentID={27EA3014-98B1-42e5-805E-F63D34304F99}]
         Report a safety error to indicate invalid ISR
         [/cover] */

      Mcal_ReportSafetyError(
        OCU_MODULE_ID,
        OCU_INSTANCE_ID, OCU_SID_ISR,
        (uint8) OCU_E_INVALID_ISR_INACTIVE_CHANNEL);
      /* End of report error */
    }
    #endif
  }
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer ChannelStatusPtr is
   * accessed using assembly instruction. */
}



#if (OCU_SAFETY_ENABLE == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={E4B5EC4C-7FAC-48d1-A9F1-17DE9B9A3514}]      **
**                                                                            **
** Syntax :           LOCAL_INLINE uint32 Ocu_lIsrSafetyCheck(                **
**                               const Ocu_ChannelType Channel,               **
**                               const uint8 CoreId )                         **
**                                                                            **
** Description :      Local function :Service to check channel validity and   **
**                                    if Init has been invoked                **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        None                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Reentrant                                               **
**                                                                            **
** Parameters (in):   Channel - Channel number to verify                      **
**                    CoreId  - Core which is calling this function           **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value:      uint32: Error flag status                               **
**                            OCU_ERROR_NOT_FOUND/OCU_ERROR_FOUND             **
**                                                                            **
*******************************************************************************/
/*[cover parentID={7F5A4CE6-A065-494e-9B74-0654A5CB52D1}]
Safety Properties
[/cover]*/
LOCAL_INLINE uint32 Ocu_lIsrSafetyCheck(const Ocu_ChannelType Channel, \
                                        const uint8 CoreId)
{
  uint32 ErrorFlag;
  uint32 CoreStatusPos;
  ErrorFlag = (uint32) OCU_ERROR_NOT_FOUND;
  CoreStatusPos = ((uint32) CoreId * (uint32) OCU_INIT_STATUS_SIZE);
  /* [cover parentID={04D7E7C5-2C20-4572-8E2A-13FD82B9E798}
              {36C8D6F0-9845-4df3-91F9-F4E0FA31FC3E}]
  Verify whether Init had been called
  [/cover] */

  if (OCU_INITIALIZED
      != Mcal_GetBitAtomic(Ocu_InitStatus, CoreStatusPos, OCU_INIT_STATUS_SIZE))
  {
    /* [cover parentID={D8DD4E29-9313-4be6-8273-27C8D7CF24F0}]
    Report a safety error to indicate Invalid ISR
    [/cover] */
    Mcal_ReportSafetyError(
      OCU_MODULE_ID,
      OCU_INSTANCE_ID, OCU_SID_ISR,
      (uint8) OCU_E_INVALID_ISR_UNINIT);/* End of report error */
    ErrorFlag = (uint32) OCU_ERROR_FOUND;
  }
  /* [cover parentID={5B2CF427-2963-4145-93B6-7914B6885673}]
  channel validation
  [/cover] */
  if ((ErrorFlag != OCU_ERROR_FOUND) && (Channel >= OCU_MAX_CHANNELS))
  {
    /* [cover parentID={063F9FDC-F44C-4bfe-ADDF-E2026EB71085}]
    Report a safety error to indicate Invalid ISR
    [/cover] */
    Mcal_ReportSafetyError(
      OCU_MODULE_ID,
      OCU_INSTANCE_ID, OCU_SID_ISR,
      (uint8) OCU_E_INVALID_ISR_CHANNEL_INVALID);/* End of report error */
    ErrorFlag = (uint32) OCU_ERROR_FOUND;
  }
  return ErrorFlag;
}
#endif
#if ((OCU_DE_INIT_API == STD_ON) && ((OCU_DEV_ERROR_DETECT == STD_ON) || \
(OCU_SAFETY_ENABLE == STD_ON)))
/*******************************************************************************
** Traceability: [cover parentID={DF19D6AB-F216-430d-A09E-6D29DB112A17}]      **
**                                                                            **
** Syntax :           LOCAL_INLINE uint32 Ocu_lDeInitDETCheck(                **
**                 const uint8 CoreId )                                       **
**                                                                            **
** Description :      Local function :Service to DET Check for De-Init        **
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
** Return value:      uint32: Error flag status                               **
**                            OCU_ERROR_NOT_FOUND/OCU_ERROR_FOUND             **
**                                                                            **
*******************************************************************************/
/*[cover parentID={7F5A4CE6-A065-494e-9B74-0654A5CB52D1}]
Safety Properties
[/cover]*/
LOCAL_INLINE uint32 Ocu_lDeInitDETCheck(uint8 CoreId)
{
  uint32 ErrorFlag;
  const uint32* ChannelStatusPtr;
  Ocu_ChannelType Channel;
  /* [cover parentID={601CADF8-A9D9-4ad3-A898-13ACBB2AA049}]
  Check if Initialization happened?
  [/cover] */
  ErrorFlag = Ocu_lInitCallVerify(OCU_SID_DEINIT, CoreId);

  /* [cover parentID={5953D7A6-D484-418b-A0FB-EEAA73101DFE}]
  Is Ocu Initialized?
  [/cover] */
  if(ErrorFlag == OCU_ERROR_NOT_FOUND)
  {
    /* [cover parentID={056263E9-7805-4c42-B790-E2A16D34920E}]
    Check configured channels, registers , variables etc
    [/cover] */
    for (Channel = (Ocu_ChannelType) 0;
         (Channel < Ocu_ConfigPtr->CoreConfig[CoreId]->MaxChannelCore) && \
         (ErrorFlag != OCU_ERROR_FOUND);
         Channel = Channel + 1U)
    {
      ChannelStatusPtr = &(Ocu_RootChannelVar[CoreId][Channel].Status);
      /* [cover parentID={F46E6499-F3B5-4b7a-B776-1D7B0527C756}]
      Is the channel running?
      [/cover] */
      if (OCU_CHANNEL_RUNNING
          == Mcal_GetBitAtomic(*ChannelStatusPtr, OCU_CHNL_STATUS_POS,
                               OCU_CHNL_STATUS_BIT_LENGTH))
      {
        /* [cover parentID={F7529F8B-7149-4996-8968-DB493F2CB3B8}]
        Mark as error found
        [/cover] */
        ErrorFlag = OCU_ERROR_FOUND;
        /* [cover parentID={CAB7ECD4-E560-435d-A0A1-AA8676FC78EF}]
        Report an error to indicate invalid state of channel for de-initialization.
        [/cover] */
        Ocu_lReportError(OCU_SID_DEINIT, OCU_E_PARAM_INVALID_STATE);
      }
    }
  }
  return ErrorFlag;
}
#endif



#if (OCU_INITCHECK_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={47480D47-0B18-43ab-BC37-DB0DE2338755}]      **
**                                                                            **
** Syntax :           LOCAL_INLINE Std_ReturnType Ocu_lPreInitCheck(          **
**                         const Ocu_ConfigType* const ConfigPtr,             **
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
/*[cover parentID={7F5A4CE6-A065-494e-9B74-0654A5CB52D1}]
Safety Properties
[/cover]*/
LOCAL_INLINE Std_ReturnType Ocu_lPreInitCheck( \
    const Ocu_ConfigType* const ConfigPtr, const uint8 CoreId)
{
  Std_ReturnType ErrorFlag = E_NOT_OK;
  uint8 CoreIndex;
  CoreIndex = (CoreId * (uint8) (OCU_INIT_STATUS_SIZE));
  /* [cover parentID={A4E2C51F-3387-489d-A880-73DA2FC297BD}]
   Check if the input parameter is NULL
  [/cover] */
  if (NULL_PTR != ConfigPtr)
  {
    /* Check if the config pointer stored is same as the required and the init
     * status is set */
    if (Ocu_ConfigPtr == ConfigPtr)
    {
      if (OCU_INITIALIZED
          == (Mcal_GetBitAtomic(Ocu_InitStatus,
                                ((sint32 )(CoreIndex)), OCU_INIT_STATUS_SIZE)))
      {
        ErrorFlag = E_OK;
      }
    }
  }
  return ErrorFlag;
}
#endif



#if (OCU_INITCHECK_API == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={55A716DB-11EB-4a4d-BEF9-33CE70F415CC}] **
**                                                                            **
** Syntax : LOCAL_INLINE Std_ReturnType           Ocu_lInitCheck(             **
**            const Ocu_ChannelConfigType *const LocalOcuChanPtr)             **
**            const Ocu_ChannelVarType *const ChannelVarPtr                   **
**                                                                            **
** Description :     Function to check the initialization of TOM/ATOM channel **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Non Reentrant                                            **
**                                                                            **
** Parameters (in):  LocalOcuChanPtr - Pointer to the Channel configuration   **
**                  ChannelVarPtr - Pointer to the Channel Status register and**
**                  compare value                                             **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     error flag status                                        **
**                                                                            **
*******************************************************************************/
/*[cover parentID={7F5A4CE6-A065-494e-9B74-0654A5CB52D1}]
Safety Properties
[/cover]*/
LOCAL_INLINE Std_ReturnType Ocu_lInitCheck(
  const Ocu_ChannelConfigType *const LocalOcuChanPtr,
  const Ocu_ChannelVarType *const ChannelVarPtr)
{

  Mcu_17_Gtm_TomAtomChConfigType TimerConfigPtr;
  const Mcu_17_Gtm_TomTgc * TomTgcRegPtr;
  volatile uint32 CmpFlag;
  uint32 ConfigVal;
  uint32 SfrVal;
  const Ifx_GTM_ATOM_AGC * AtomAgcRegPtr;     /* Ptr to ATOM AGC Reg */
  const Ifx_GTM_ATOM_CH * AtomChannelRegPtr; /* Pointer to ATOM channel Register */
  Std_ReturnType  RetVal;
  uint8 TomTgcIndex;
  uint8 Module;
  uint8 Channel;
  uint8 BitPos;
  uint8 ErrorFlag;
  /*Initialization*/
  RetVal  = E_NOT_OK;
  CmpFlag = 0xFFFFFFFFU;


  /*Load the Structure "TimerConfigPtr" with configuration values*/
  TimerConfigPtr.TimerChCM0Reg = LocalOcuChanPtr->MaxCounterValue;
  TimerConfigPtr.TimerChCM1Reg = LocalOcuChanPtr->DefaultThreshold;
  TimerConfigPtr.TimerChCN0Reg = 0U;
  /* Pulse Notify interrupt mode */
  TimerConfigPtr.TimerChIntEnMode = IRQ_PULSE_NOTIFY_MODE << GTM_TOM_IRQ_MODE_POS;
  TimerConfigPtr.TimerChSR0Reg = LocalOcuChanPtr->MaxCounterValue;
  TimerConfigPtr.TimerChSR1Reg = LocalOcuChanPtr->DefaultThreshold;
  TimerConfigPtr.TimerId = \
                           LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber;
  /* [cover parentID={AA763452-7758-4ea8-99AA-714312D1B07F}]
  Is the HW used is TOM ?
  [/cover] */
  if(LocalOcuChanPtr->OcuProperties.AssignedHwUnit == OCU_GTM_TOM)
  {
    TimerConfigPtr.TimerChCtrlReg = \
                                    (((uint32)LocalOcuChanPtr->OcuProperties.ClockSelect << \
                                      OCU_GTM_CLKSELECT_BIT_POS));
    /* MISRA2012_RULE_1_3_JUSTIFICATION: Mcu function invoked with address of local
      variable TimerConfigPtr since the auto variable TimerConfigPtr is passed as 
      const and only read in the local called function. Hence, it is not an issue.*/
    /* Check initialization status of GTM TOM channel*/
    ErrorFlag = Mcu_17_Gtm_TomChInitCheck( (const Mcu_17_Gtm_TomAtomChConfigType*) \
                                           &TimerConfigPtr);


    /* Retrieve the TOM module index value */
    Module = (uint8)((LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber & \
                      GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);

    /* Retrieve the TOM module channel number */
    Channel = (uint8)((LocalOcuChanPtr->OcuProperties.AssignedHwUnitNumber \
                       & GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);
    /*Calculate the Bit Position according the to retrieved Channel Number*/
    BitPos  = ((uint8)IFX_GTM_TOM_TGC_ENDIS_STAT_ENDIS_STAT0_LEN * \
               (Channel & GTM_TGC_CHANNEL_MASK));
    /*Each TGC register contains information of 8(GTM_TOM_CH_PER_TGC) \
     * channel */
    TomTgcIndex = (Channel / (uint8)GTM_TOM_CH_PER_TGC);

    /* MISRA2012_RULE_11_3_JUSTIFICATION: GTM_TOM_TGC_POINTER does a typecast
     * to void and then to specific Mcu datatype Mcu_17_Gtm_TomTgcArray to
     * index to the proper TOM channel's SFR from the base GTM SFR.
     * No side effects seen by violating this MISRA */
    /* MISRA2012_RULE_11_5_JUSTIFICATION: GTM_TOM_TGC_POINTER does a typecast
     * to void and then to specific Mcu datatype Mcu_17_Gtm_TomTgcArray to
     * index to the proper TOM channel's SFR from the base GTM SFR.
     * No side effects seen by violating this MISRA */
    /* MISRA2012_RULE_18_4_JUSTIFICATION: To effectively access different TOM
     * modules. Since the Module values are
     * validated by the user, no side effects are foreseen */
    TomTgcRegPtr = GTM_TOM_TGC_POINTER(Module, TomTgcIndex);

    /* Verify TOMi TGC FUPD SFR values are according to the configuration. */
    SfrVal = (uint8)Mcal_GetBitAtomic(TomTgcRegPtr->TGC_FUPD_CTRL.U, \
                                      BitPos, GTM_TOM_TGC_FUPD_CTRL_FUPD_CTRL_LEN);

    ConfigVal = 0U;

    CmpFlag  &= ~(SfrVal ^ ConfigVal);

    /*Verify TOMi TGC enable/disable Status SFR values are according to the \
     * configuration*/
    SfrVal = (uint8)Mcal_GetBitAtomic(TomTgcRegPtr->TGC_ENDIS_STAT.U, \
                                      BitPos, GTM_TOM_TGC_ENDIS_STAT_ENDIS_STAT_LEN);

    ConfigVal = GTM_TOM_CH_ENABLE_READ;

    CmpFlag &= ~(SfrVal ^ ConfigVal);

    /*Verify TOMi TGC enable/disable Control SFR values are according to the \
     * configuration*/
    SfrVal = (uint8)Mcal_GetBitAtomic(TomTgcRegPtr->TGC_ENDIS_CTRL.U, \
                                      BitPos, GTM_TOM_TGC_ENDIS_CTRL_ENDIS_CTRL_LEN);
    ConfigVal = GTM_TOM_CH_STAT_NO_UPDATE;

    CmpFlag &= ~(SfrVal ^ ConfigVal);

    /*Verify TOMi TGC Output Enable Status SFR values are according to the \
     * configuration*/
    SfrVal = (uint8)Mcal_GetBitAtomic(TomTgcRegPtr->TGC_OUTEN_STAT.U, \
                                      BitPos, GTM_TOM_TGC_OUTEN_STAT_OUTEN_STAT_LEN);
    ConfigVal = GTM_TOM_CH_OUT_DISABLE_READ;

    CmpFlag &= ~(SfrVal ^ ConfigVal);

    /*Verify TOMi TGC Output Enable Control SFR values are according to the \
     * configuration*/
    SfrVal = (uint8)Mcal_GetBitAtomic(TomTgcRegPtr->TGC_OUTEN_CTRL.U, \
                                      BitPos, GTM_TOM_TGC_OUTEN_CTRL_OUTEN_CTRL_LEN);
    ConfigVal = GTM_TOM_CH_STAT_NO_UPDATE;

    CmpFlag &= ~(SfrVal ^ ConfigVal);


    BitPos =  (((uint8)IFX_GTM_TOM_TGC_GLB_CTRL_UPEN_CTRL0_LEN * \
                (Channel & GTM_TGC_CHANNEL_MASK)) + \
               IFX_GTM_TOM_TGC_GLB_CTRL_UPEN_CTRL0_OFF);

    /*Verify Update Enable SFR values are according to the \
     * configuration*/
    SfrVal = (uint8)Mcal_GetBitAtomic(TomTgcRegPtr->TGC_GLB_CTRL.U, \
                                      BitPos, IFX_GTM_TOM_TGC_GLB_CTRL_UPEN_CTRL0_LEN);

    ConfigVal = GTM_TOM_CH_UPDATE_ENABLE_READ;

    CmpFlag &= ~(SfrVal ^ ConfigVal);


  }
  else
  {
    /* Retrieve the ATOM module index value */
    Module = (uint8)((TimerConfigPtr.TimerId & GTM_MODULE_NO_MASK) >> \
                     GTM_MODULE_NO_OFF);
    /* Retrieve the ATOM module channel number */
    Channel = (uint8)((TimerConfigPtr.TimerId & GTM_CHANNEL_NO_MASK) >> \
                      GTM_CHANNEL_NO_OFF);

    /*Calculate the Bit Position according the to retrieved Channel Number*/
    BitPos = (((uint8)IFX_GTM_ATOM_AGC_OUTEN_CTRL_OUTEN_CTRL0_LEN) * \
              Channel);


    /* MISRA2012_RULE_18_4_JUSTIFICATION: To effectively access different ATOM
     * modules. Since the Module values are validated by the user,
     * no side effects are foreseen \
     * Retrieve the ATOM AGC SFR register address*/
    AtomAgcRegPtr =  GTM_ATOM_AGC_POINTER(Module);

    /* [cover parentID={CF11C145-5536-40ed-ABEA-6EC2490E507D}]
    Is the channel clock one of TBU clock?
    [/cover] */

    if((LocalOcuChanPtr->OcuProperties.ClockSelect & OCU_GTM_TBU_MASK) == \
        OCU_GTM_TBU_MASK)
    {
      /* Shared counter set acb to 0x1C with pin*/
      if(LocalOcuChanPtr->OcuProperties.ClockSelect == OCU_GTM_TBU_TS2)/*TS2*/
      {
        /*SOMC mode & TBU_TS2*/
        TimerConfigPtr.TimerChCtrlReg = OCU_GTM_ATOM_ACB_NO_ACTION | \
                                        OCU_GTM_ATOM_MODE_SOMC | OCU_GTM_ATOM_TBU_TS2;
        TimerConfigPtr.TimerChCM0Reg = 0U;
        TimerConfigPtr.TimerChCM1Reg = LocalOcuChanPtr->DefaultThreshold;                                       
        /* Only CCU1 interrupt needed */
        TimerConfigPtr.TimerChIntEnMode = \
                                          TimerConfigPtr.TimerChIntEnMode | ATOM_CCU1_IRQ_EN;
      }
      else if(LocalOcuChanPtr->OcuProperties.ClockSelect == OCU_GTM_TBU_TS1)
      {
        TimerConfigPtr.TimerChCtrlReg = \
                                        OCU_GTM_ATOM_ACB_NO_ACTION | OCU_GTM_ATOM_MODE_SOMC;/*SOMC mode */

        TimerConfigPtr.TimerChCM0Reg = 0U;
        TimerConfigPtr.TimerChCM1Reg = LocalOcuChanPtr->DefaultThreshold;                                       
        /* Only CCU1 interrupt needed */
        TimerConfigPtr.TimerChIntEnMode = \
                                          TimerConfigPtr.TimerChIntEnMode | ATOM_CCU1_IRQ_EN;
      }
      else
      {
        TimerConfigPtr.TimerChCtrlReg = \
                                        OCU_GTM_ATOM_ACB_NO_ACTION | OCU_GTM_ATOM_MODE_SOMC;/*SOMC mode */
                                        
        TimerConfigPtr.TimerChCM0Reg = LocalOcuChanPtr->DefaultThreshold;
        TimerConfigPtr.TimerChCM1Reg = 0U;                                      
        /* Only CCU0 interrupt needed */
        TimerConfigPtr.TimerChIntEnMode = \
                                          TimerConfigPtr.TimerChIntEnMode | ATOM_CCU0_IRQ_EN;
      }
      TimerConfigPtr.TimerChCtrlReg = \
                                      (((uint32)LocalOcuChanPtr->OcuProperties.PinDefaultState << \
                                        OCU_GTM_ATOM_SL_BIT_POS)) | TimerConfigPtr.TimerChCtrlReg;

    /* MISRA2012_RULE_1_3_JUSTIFICATION: Mcu function invoked with address of local
      variable TimerConfigPtr since the auto variable TimerConfigPtr is passed as 
      const and only read in the local called function. Hence, it is not an issue.*/
      /* [cover parentID=]
      Initialize Check for TOM channel
      [/cover] */
      ErrorFlag = Mcu_17_Gtm_AtomChInitCheck((const Mcu_17_Gtm_TomAtomChConfigType*) \
                                             &TimerConfigPtr);

      /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
      * by violating this MISRA rule, as the pointer to the object type
      * it is getting cast into is a known type . */
      /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
      * by violating this MISRA rule. */
      AtomChannelRegPtr = GTM_ATOM_CH_POINTER(Module, Channel);
      /* Verify IRQ_NOTIFY register's contents are as per configuration */
      SfrVal    = (uint32)AtomChannelRegPtr->IRQ.NOTIFY.U;
      /* Written with GTM_ATOM_CLR_PENDING_IRQ in Ocu_Init.
       Since, its a write to clear register, it is read as 0. */
      ConfigVal = 0U;
      CmpFlag  &= ~(SfrVal ^ ConfigVal);

      /* [cover parentID={E038889C-194F-4206-A97D-8F7A089CBF0E}]
        Is the channel using pin?
      [/cover] */
      /*Whether Port Pin is Enabled/Configured to get triggered on Output compare \
       *  match ?*/
      if(LocalOcuChanPtr->OcuProperties.PinUsed == OCU_BIT_SET)
      {

        /*Verify ATOMi AGC Output Enable Status SFR values are according to the \
         * configuration*/
        SfrVal = (uint8)Mcal_GetBitAtomic(AtomAgcRegPtr->OUTEN_STAT.U, BitPos, \
                                          GTM_ATOM_AGC_OUTEN_STAT_OUTEN_STAT_LEN);


        ConfigVal = GTM_ATOM_CH_OUT_ENABLE_READ;

        CmpFlag &= ~(SfrVal ^ ConfigVal);

        /*Verify ATOMi AGC Output Enable Control SFR values are according to the \
         * configuration*/
        SfrVal = (uint8)Mcal_GetBitAtomic(AtomAgcRegPtr->OUTEN_CTRL.U, \
                                          BitPos, GTM_ATOM_AGC_OUTEN_CTRL_OUTEN_CTRL_LEN);

        ConfigVal = GTM_ATOM_CH_STAT_NO_UPDATE;

        CmpFlag &= ~(SfrVal ^ ConfigVal);

      }
      else
      {
        /* [cover parentID={3A61E178-A047-4e3f-A36F-517CA403515D}]
        Is the Channel is using ADC?
        [/cover] */

        if(LocalOcuChanPtr->OcuProperties.AdcUsed == OCU_BIT_SET)
        {

          /*Verify ATOMi AGC Output Enable Status SFR values are according to the \
           * configuration*/
          SfrVal = (uint8)Mcal_GetBitAtomic(AtomAgcRegPtr->OUTEN_STAT.U, \
                                            BitPos, GTM_ATOM_AGC_ENDIS_CTRL_ENDIS_CTRL_LEN);

          ConfigVal = GTM_ATOM_CH_OUT_ENABLE_READ;

          CmpFlag &= ~(SfrVal ^ ConfigVal);

          /*Verify ATOMi AGC Output Enable Control SFR values are according to the \
           * configuration*/
          SfrVal = (uint8)Mcal_GetBitAtomic(AtomAgcRegPtr->OUTEN_CTRL.U, \
                                            BitPos, GTM_ATOM_AGC_OUTEN_CTRL_OUTEN_CTRL_LEN);

          ConfigVal = GTM_ATOM_CH_STAT_NO_UPDATE;

          CmpFlag &= ~(SfrVal ^ ConfigVal);

          /* Verify Channel Status is Initilized as per the configuration*/
          SfrVal = ChannelVarPtr->Status;

          ConfigVal = ((uint32)OCU_TOGGLE << OCU_CHNL_PIN_ACTION_POS);

          CmpFlag &= ~(SfrVal ^ ConfigVal);

        }
      }
    }
    else
    {
      /* exclusive counter */
      TimerConfigPtr.TimerChCtrlReg = OCU_GTM_ATOM_MODE_SOMP;
      /* Clock selection */
      TimerConfigPtr.TimerChCtrlReg = \
                                      (((uint32)LocalOcuChanPtr->OcuProperties.ClockSelect << \
                                        OCU_GTM_CLKSELECT_BIT_POS))  | TimerConfigPtr.TimerChCtrlReg;

    /* MISRA2012_RULE_1_3_JUSTIFICATION: Mcu function invoked with address of local
      variable TimerConfigPtr since the auto variable TimerConfigPtr is passed as 
      const and only read in the local called function. Hence, it is not an issue.*/
      /* [cover parentID=]
      Initialize Check for TOM channel
      [/cover] */
      ErrorFlag = Mcu_17_Gtm_AtomChInitCheck((const Mcu_17_Gtm_TomAtomChConfigType*) \
                                             &TimerConfigPtr);

      /* Verify ATOMi AGC FUPD SFR values are according to the configuration. */
      SfrVal = (uint8)Mcal_GetBitAtomic(AtomAgcRegPtr->FUPD_CTRL.U, \
                                        BitPos, GTM_ATOM_AGC_FUPD_CTRL_FUPD_CTRL_LEN);

      ConfigVal = 0U;

      CmpFlag  &= ~(SfrVal ^ ConfigVal);

      /*Verify ATOMi AGC enable/disable Status SFR values are according to the \
       * configuration*/
      SfrVal = (uint8)Mcal_GetBitAtomic(AtomAgcRegPtr->ENDIS_STAT.U, \
                                        BitPos, GTM_ATOM_AGC_ENDIS_STAT_ENDIS_CTRL_LEN);

      ConfigVal = GTM_ATOM_CH_ENABLE_READ;

      CmpFlag &= ~(SfrVal ^ ConfigVal);

      /*Verify ATOMi AGC enable/disable Control SFR values are according to the \
       * configuration*/
      SfrVal = (uint8)Mcal_GetBitAtomic(AtomAgcRegPtr->ENDIS_CTRL.U, \
                                        BitPos, GTM_ATOM_AGC_ENDIS_CTRL_ENDIS_CTRL_LEN);

      ConfigVal = GTM_ATOM_CH_STAT_NO_UPDATE;

      CmpFlag &= ~(SfrVal ^ ConfigVal);

      /*Verify ATOMi AGC Output Enable Status SFR values are according to the \
       * configuration*/
      SfrVal = (uint8)Mcal_GetBitAtomic(AtomAgcRegPtr->OUTEN_STAT.U, \
                                        BitPos, GTM_ATOM_AGC_ENDIS_CTRL_ENDIS_CTRL_LEN);

      ConfigVal = GTM_ATOM_CH_OUT_DISABLE_READ;

      CmpFlag &= ~(SfrVal ^ ConfigVal);

      /*Verify ATOMi AGC Output Enable Control SFR values are according to the \
       * configuration*/
      SfrVal = (uint8)Mcal_GetBitAtomic(AtomAgcRegPtr->OUTEN_CTRL.U, \
                                        BitPos, GTM_ATOM_AGC_OUTEN_CTRL_OUTEN_CTRL_LEN);

      ConfigVal = GTM_ATOM_CH_STAT_NO_UPDATE;

      CmpFlag &= ~(SfrVal ^ ConfigVal);



      BitPos    = ((((uint8)IFX_GTM_ATOM_AGC_GLB_CTRL_UPEN_CTRL0_LEN) * \
                    Channel) + \
                   GTM_ATOM_AGC_GLB_CTRL_UPEN_CTRL0_OFF);

      /*Verify ATOMi AGC Update Enable SFR values are according to the \
       * configuration*/
      SfrVal = (uint8)Mcal_GetBitAtomic(AtomAgcRegPtr->GLB_CTRL.U, \
                                        BitPos, IFX_GTM_ATOM_AGC_GLB_CTRL_UPEN_CTRL0_LEN);

      ConfigVal = GTM_ATOM_CH_UPDATE_ENABLE_READ;

      CmpFlag &= ~(SfrVal ^ ConfigVal);

    }
  }
  /* [cover parentID={BBF7740A-DE3E-40c3-8FE5-18E2CFF0EE58}]
  Is the Channel is not using ADC?
  [/cover] */
  if(LocalOcuChanPtr->OcuProperties.AdcUsed != OCU_BIT_SET)
  {

    /* Verify Channel Status is Initilized 0u*/
    SfrVal = ChannelVarPtr->Status;

    ConfigVal = 0U;

    CmpFlag &= ~(SfrVal ^ ConfigVal);

  }


  /* Verify Compare Value is initialized to Default Threshold Value */
  SfrVal = ChannelVarPtr->CompareValue;

  ConfigVal = LocalOcuChanPtr->DefaultThreshold;

  CmpFlag &= ~(SfrVal ^ ConfigVal);

  /* [cover parentID={E80C5BCF-38A1-4ec3-A38F-B6E0C178EB6E}]
  Are all the Verifications Successful ?
  [/cover] */
  if((CmpFlag == 0xFFFFFFFFU) && (ErrorFlag == 0u))
  {
    RetVal = E_OK;
  }
  return RetVal;
}
#endif



#define OCU_STOP_SEC_CODE_ASIL_B_GLOBAL
/* [cover parentID={B4EF5A53-8526-484d-8EDA-8C95CAE0E18F}]
Ocu_MemMap.h file inclusion.
[/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Ocu_MemMap.h"
