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
**  FILENAME  : Lin_17_AscLin_PBcfg.c                                         **
**                                                                            **
**  VERSION   : 8.0.0                                                         **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:30      !!!IGNORE-LINE!!!               **
**                                                                            **
**  GENERATOR : Build b191017-0938          !!!IGNORE-LINE!!!               **
**                                                                            **
**  BSW MODULE DECRIPTION : Lin.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Lin configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of Lin Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Inclusion of Lin Header file */
#include "Lin_17_AscLin.h"
/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
/* <!-- [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] --> */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define LIN_17_ASCLIN_START_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safegaurd.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"
/*******************************************************************************
**                      Configuration Options                                 **
*******************************************************************************/
/******************************************************************************/
/*
    Container: LinChannelConfiguration
*/
/*
    To be used for global or static constants (unspecified size)
    ASCLIN HwUnit to the logical channel mapping
    - if the channel is configured, array member holds the Logical channel Id
    - if the channel is not configured, array member holds 0xFF
*/
/*
    INDEX-> Hw-Unit(ASCLIN Kernel)
    Vaule within the array -> Logical ChannelId
*/
static const uint8 Lin_17_AscLin_Hw_To_ChannelIdMap[LIN_17_ASCLIN_MAX_HW_UNIT] =
{
    0xFFU,
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
    0xFFU
};

/*
    To be used for Channel allocation to the core mapping
*/
/*
    INDEX-> ChannelId
    Vaule within the array -> channel assignment in core
*/
static const uint8 Lin_17_AscLin_Channel_To_Core_SpecificArray[LIN_17_ASCLIN_MAXIMUM_CHANNEL_CONFIGURED] =
{
    0x0U    /*0 index belongs to Core0*/

};

#define LIN_17_ASCLIN_STOP_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED

/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safegaurd.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define LIN_17_ASCLIN_START_SEC_CONFIG_DATA_QM_CORE0_UNSPECIFIED

/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safegaurd.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"

static const Lin_17_AscLin_ChannelType  Lin_kChannelConfigurationCore0[1] =
{
  /* LIN Channel ID: 0 Configuration */
  {
    /* BaudRate : 19200 Hz  */
    {
        341U,  /* BRG.NUMERATOR value */
        1000U,    /* BRG.DENOMINATOR value */
        110U,  /* BITCON.PRESCALAR value */
        234U,  /* Prescalar value for wakeup detection */
        0U, /* Inter byte or response space value */
        63U /* IOCR DEPTH value for wakeup detection */
    },
    0xFFU,                            /* EcuM Wakeup Source ID */
    LIN_17_ASCLIN1,   /* Hw Module used */
    LIN_17_ASCLIN_CHANNEL_WAKEUP_ENABLED,     /* Wakeup Support */
    LIN_17_ASCLIN_SELECT_A,  /*Rx alternate pin select */
    0U,   /*Logical channel Id */
    LIN_17_ASCLIN_MASTER_NODE  /*Channel node type */
  }
};

static const Lin_17_AscLin_CoreConfigType Lin_CoreConfigCore0 =
{
    1U,    /* The maximum no of the channels allocated to the core */
    (const Lin_17_AscLin_ChannelType*)&Lin_kChannelConfigurationCore0[0]
};

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/

#define LIN_17_ASCLIN_STOP_SEC_CONFIG_DATA_QM_CORE0_UNSPECIFIED

/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration of notification function
before MemMap inclusion It complies to Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"

/* <!-- [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] --> */

#define LIN_17_ASCLIN_START_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED

/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safegaurd.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"
/*
    The over all initialization data for the LIN driver.
    The user configured Lin driver initialization structure.
*/
/* MISRA2012_RULE_8_7_JUSTIFICATION: Module configuration data structure
declaration as per Autosar guidelines. This data structure may be needed
by SW units using Port Driver APIs */
/* MISRA2012_RULE_8_4_JUSTIFICATION: Definition is as per Autosar guidelines */
const Lin_17_AscLin_ConfigType  Lin_17_AscLin_Config =
{
  {
    /* MISRA2012_RULE_11_8_JUSTIFICATION: No side effects foreseen
    * by violating this MISRA rule */
    (Lin_17_AscLin_CoreConfigType*)&Lin_CoreConfigCore0,
    /* MISRA2012_RULE_11_8_JUSTIFICATION: No side effects foreseen
    * by violating this MISRA rule */
    /* MISRA2012_RULE_11_8_JUSTIFICATION: No side effects foreseen
    * by violating this MISRA rule */
    NULL_PTR,
    /* MISRA2012_RULE_11_8_JUSTIFICATION: No side effects foreseen
    * by violating this MISRA rule */
    NULL_PTR,
    /* MISRA2012_RULE_11_8_JUSTIFICATION: No side effects foreseen
    * by violating this MISRA rule */
    NULL_PTR
  },
  &Lin_17_AscLin_Channel_To_Core_SpecificArray[0],
  &Lin_17_AscLin_Hw_To_ChannelIdMap[0]
};

#define LIN_17_ASCLIN_STOP_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED

/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safegaurd.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"
/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/
/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/
