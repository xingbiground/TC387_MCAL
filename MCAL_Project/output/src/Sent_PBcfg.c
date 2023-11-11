/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2019)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Sent_PBCfg.c                                                  **
**                                                                            **
**  VERSION   : 8.0.0                                                         **
**                                                                            **
**  DATE, TIME: 2023-11-11, 18:11:55   !!!IGNORE-LINE!!!                      **
**                                                                            **
**  GENERATOR : Build b200227-0222       !!!IGNORE-LINE!!!                    **
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
**  DESCRIPTION  : Sent configuration generated out of ECUC file              **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                       Includes                                             **
*******************************************************************************/
#include "Sent_Cfg.h"
/* Module header file */
#include "Sent.h"
/*******************************************************************************
**                      Private Macro definition                              **
*******************************************************************************/

/*******************************************************************************
**                      Configuration Options                                 **
*******************************************************************************/

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Global Funtion Declarations                           **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
/******************* CORE0 CHANNEL CONFIGURATION MEMMAP SECTION *************/
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define SENT_START_SEC_CONFIG_DATA_QM_CORE0_UNSPECIFIED
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
guideline.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Sent_MemMap.h"
/*Channel Structure for selected Core*/
static const Sent_ChannelCfgType Sent_ChanConfig_Core0[SENT_CHANNEL_COUNT_CORE0] =
{
  {
    /* Channel:SentChannelConfigSet_0 */
    /* SENT_RCRx register value */
    (0x00000600U),
    /* SENT_IOCRx register value */
    (0x00000000U),
    /* SENT_VIEWx register value */
    (0x76543210U),
    /* SENT_CPDRx register value */
    (0x00000007U),
    /* SENT_CFDRx reg value (Baudrate tick time derived is Infinity(us)) */
    (0x00000898U),
    /* Frame length */
    (6U),
    /* SENT Physical Channel Id arranged corewise */
    (0U),
    /*Callback function ptr */
    NULL_PTR,
    /*Channel interrupt node */
    0x0
  }
,
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define SENT_STOP_SEC_CONFIG_DATA_QM_CORE0_UNSPECIFIED
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
guideline.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Sent_MemMap.h"
/******************* CORE0 CHANNEL CONFIGURATION MEMMAP SECTION END*************/
/******************* CORE0 CHANNEL CONFIGURATION MEMMAP SECTION *************/
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* Code data Structure for selected Core*/
#define SENT_START_SEC_CONFIG_DATA_QM_CORE0_UNSPECIFIED
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
guideline.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Sent_MemMap.h"
static const Sent_CoreConfigType Sent_CoreConfigCore0 =
{
  (Sent_ChannelIdxType)1U,
  Sent_ChanConfig_Core0
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define SENT_STOP_SEC_CONFIG_DATA_QM_CORE0_UNSPECIFIED
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
guideline.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Sent_MemMap.h"
/******************* CORE0 CHANNEL CONFIGURATION MEMMAP SECTION END*************/
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define SENT_START_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Sent_MemMap.h"
/* Data structure to hold core channel index map */
/* Allocation of the channels to different cores */
static const Sent_ChannelMapType Sent_ChannelLookUp[1] =
{
  /*CoreID, ChannelIndex*/
  {0x0U,0x0U}
};
/* Physical to Logical channel mapping */
/* physical channel id is the index value of Sent_ChannelId and corresponding 
logical channel id in the channel configuration is stored */
static const Sent_ChannelIdxType Sent_LogicalChannelId[SENT_HW_MAX_CHANNELS] =
{
  0U,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU
};
/* Logical to physical channel mapping */
/* Logical id is the index value hardware channel id and
physical id is the mapping to the configured channel in sequence */
static const Sent_ChannelIdxType Sent_PhyChannelId[SENT_MAX_CHANNELS_CONFIGURED] =
{
  0U
};
/* SENT Module Configuration */
const Sent_ConfigType Sent_Config =
{
  {
    &Sent_CoreConfigCore0,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR
  },
  /* Module clock divider */
  (0x100U),
  /* Module Fractional step divider */
  (1023U),
  /* SENT channels configured */
  (1U),
  /* Channel Id to the core sequence mapping */
  Sent_ChannelLookUp,
  /* Physical to Logical Id mapping */
  Sent_LogicalChannelId,
  /* Logical to Physical ID mapping */
  Sent_PhyChannelId
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define SENT_STOP_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Sent_MemMap.h"
