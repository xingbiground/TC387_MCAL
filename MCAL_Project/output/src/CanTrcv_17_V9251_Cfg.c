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
**  FILENAME  : CanTrcv_17_V9251_Cfg.c                                        **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:32       !!!IGNORE-LINE!!!                  **
**                                                                            **
**  GENERATOR : Build b191017-0938           !!!IGNORE-LINE!!!                **
**                                                                            **
**  BSW MODULE DECRIPTION : CanTrcv_17_V9251.bmd                              **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION :  CanTrcv_17_V9251 configuration generated out of ECUC file  **
**                                                                            **
**  SPECIFICATION(S) : Specification of CanTrcv Driver, AUTOSAR Release 4.2.2 **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                             Includes                                       **
*******************************************************************************/
/* Include CanTrcv header file */
#include "CanTrcv_17_V9251.h"
/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

/*******************************************************************************
**                      Imported Global Constant Declaration                  **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/

/*******************************************************************************
**Information provided by elements of CanTrcv_17_V9251_ChannelConfig structure**
********************************************************************************
1.CanTrcv_17_V9251_NetworkMode : CAN Transceiver State after Initialization.
                                  - CanTrcvOpModeNormal
                                  - CanTrcvOpModeStandby

2.CanTrcv_17_V9251_WakeupSourceRef : EcuMWakeupSource Id, if configured.
                                WAKEUP_SOURCE_NOT_CONFIGURED, if not configured.

3.CanTrcv_17_V9251_DioChannel  : Choice Reference to a DIO Channel.

4.CanTrcv_17_V9251_DioPinLevel : Internal value for Initialization based on
                                  configured operating mode.
                                  CANTRCV_17_V9251_NORMAL_MODE,if NORMAL_MODE
                                  CANTRCV_17_V9251_STANDBY_MODE,if STANDBY_MODE

5.CanTrcv_17_V9251_ChannelId   : Channel Id of CanTrcv Channel.

6.CanTrcv_17_V9251_WakeupbyBus : Specifies wake up by bus is used or not.
                                  - if TRUE, is used
                                  - if FALSE, is not used
********************************************************************************
**                                                                            **
*******************************************************************************/
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define CANTRCV_17_V9251_START_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
/* [cover parentID={DC0F3BD1-1815-492a-8B3D-D19A2DBC37C6}]
    MemMap file  [/cover] */
/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
    MemMap for variables  [/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
    MemMap file  [/cover] */
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
    MemMap for const  [/cover] */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_V9251_MemMap.h"

/*[cover parentID={152B4BF1-9AF6-4cf8-B4D8-184F7B3C2E77}][/cover]*/

const CanTrcv_17_V9251_ChannelInfoType
CanTrcv_17_V9251_ChannelConfig[CANTRCV_17_V9251_CHANNELS_USED] =
{
  /* CanTransceiver Channel 0 Specific Information */
  {
    CANTRCV_TRCVMODE_NORMAL,
    WAKEUP_SOURCE_NOT_CONFIGURED,
    DioConf_DioChannel_DioChannel_2,
    CANTRCV_17_V9251_NORMAL_MODE,
    0U,
    FALSE
  },
  /* CanTransceiver Channel 1 Specific Information */
  {
    CANTRCV_TRCVMODE_NORMAL,
    WAKEUP_SOURCE_NOT_CONFIGURED,
    DioConf_DioChannel_OCU_CHANNEL_PIN,
    CANTRCV_17_V9251_NORMAL_MODE,
    1U,
    FALSE
  },
  /* CanTransceiver Channel 2 Specific Information */
  {
    CANTRCV_TRCVMODE_NORMAL,
    WAKEUP_SOURCE_NOT_CONFIGURED,
    DioConf_DioChannel_STB2,
    CANTRCV_17_V9251_NORMAL_MODE,
    2U,
    FALSE
  },
  /* CanTransceiver Channel 3 Specific Information */
  {
    CANTRCV_TRCVMODE_NORMAL,
    WAKEUP_SOURCE_NOT_CONFIGURED,
    DioConf_DioChannel_STB,
    CANTRCV_17_V9251_NORMAL_MODE,
    3U,
    FALSE
  }
};

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define CANTRCV_17_V9251_STOP_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
/* [cover parentID={DC0F3BD1-1815-492a-8B3D-D19A2DBC37C6}]
MemMap file  [/cover] */
/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
MemMap for variables  [/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
MemMap file  [/cover] */
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
MemMap for const  [/cover] */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_V9251_MemMap.h"

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define CANTRCV_17_V9251_START_SEC_CONFIG_DATA_QM_LOCAL_8
/* [cover parentID={DC0F3BD1-1815-492a-8B3D-D19A2DBC37C6}]
MemMap file  [/cover] */
/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
MemMap for variables  [/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
MemMap file  [/cover] */
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
MemMap for const  [/cover] */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_V9251_MemMap.h"

/* CanTrcv_17_V9251_ChannelUsed array contains Channel Index of configured Channel
- if ChannelIndex, is used
- if 0XFF, is not used
*/
/*[cover parentID={8CF0195E-4D53-4341-BD4A-BEBC304F1D80}][/cover]*/

const uint8 CanTrcv_17_V9251_ChannelUsed[CANTRCV_17_V9251_CHANNELS_CFG] =
{
  /* Index of CAN Transceiver Channel_0 is used */
  0U,
  /* Index of CAN Transceiver Channel_1 is used */
  1U,
  /* Index of CAN Transceiver Channel_2 is used */
  2U,
  /* Index of CAN Transceiver Channel_3 is used */
  3U
};

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define CANTRCV_17_V9251_STOP_SEC_CONFIG_DATA_QM_LOCAL_8
/* [cover parentID={DC0F3BD1-1815-492a-8B3D-D19A2DBC37C6}]
    MemMap file  [/cover] */
/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
    MemMap for variables  [/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
    MemMap file  [/cover] */
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
    MemMap for const  [/cover] */
 /*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
 guideline. */
 /*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
 without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_V9251_MemMap.h"
/*******************************************************************************
**                               End of File                                  **
*******************************************************************************/
