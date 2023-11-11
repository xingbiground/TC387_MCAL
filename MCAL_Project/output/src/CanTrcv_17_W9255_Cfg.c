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
**  FILENAME  : CanTrcv_17_W9255_Cfg.c                                        **
**                                                                            **
**  VERSION   : 6.0.0                                                         **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:31       !!!IGNORE-LINE!!!                  **
**                                                                            **
**  GENERATOR : Build b191017-0938           !!!IGNORE-LINE!!!                **
**                                                                            **
**  BSW MODULE DECRIPTION : CanTrcv_17_W9255.bmd                              **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : CanTrcv_17_W9255 configuration generated out of ECUC file  **
**                                                                            **
**  SPECIFICATION(S) : Specification of CanTrcv Driver, AUTOSAR Release 4.2.2 **
**                                                  and AUTOSAR Release 4.4.0 **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Includes                                       **
*******************************************************************************/
/* Include CanTrcv header file */
#include "CanTrcv_17_W9255.h"
/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define CANTRCV_17_W9255_START_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED

/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_W9255_MemMap.h"

const CanTrcv_17_W9255_ChannelConfigType CanTrcv_17_W9255_ChannelConfig[CANTRCV_17_W9255_CHANNELS_USED] =
{
  /* CanTransceiver Channel 0 Specific Information */
  {
    /* CAN Transceiver state after driver initialization */
    /* Command to write to MODE_CTRL register when the requested mode is STANDBY */
    0x8102U,

    /* CanTrcvWakeupSource reference */
    CANTRCV_17_W9255_WAKEUP_SOURCE_NOT_CONFIGURED,

    /* CanTrcvPorWakeupSource reference */
    CANTRCV_17_W9255_WAKEUP_SOURCE_NOT_CONFIGURED,

    /* CanTrcvSyserrWakeupSource reference */
    CANTRCV_17_W9255_WAKEUP_SOURCE_NOT_CONFIGURED,

    /* CAN Transceiver Channel Id */
    0U,

    /* Sequence Id used */
    1U,

    /* Spi Channel Id used */
    2U,

    /*
    Wake up by bus status
    - if STD_ON, Bus is used
    - if STD_OFF, Bus is not used
    */
    STD_OFF
  },
  /* CanTransceiver Channel 1 Specific Information */
  {
    /* CAN Transceiver state after driver initialization */
    /* Command to write to MODE_CTRL register when the requested mode is STANDBY */
    0x8102U,

    /* CanTrcvWakeupSource reference */
    CANTRCV_17_W9255_WAKEUP_SOURCE_NOT_CONFIGURED,

    /* CanTrcvPorWakeupSource reference */
    CANTRCV_17_W9255_WAKEUP_SOURCE_NOT_CONFIGURED,

    /* CanTrcvSyserrWakeupSource reference */
    CANTRCV_17_W9255_WAKEUP_SOURCE_NOT_CONFIGURED,

    /* CAN Transceiver Channel Id */
    1U,

    /* Sequence Id used */
    2U,

    /* Spi Channel Id used */
    3U,

    /*
    Wake up by bus status
    - if STD_ON, Bus is used
    - if STD_OFF, Bus is not used
    */
    STD_OFF
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
#define CANTRCV_17_W9255_STOP_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED

/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_W9255_MemMap.h"

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define CANTRCV_17_W9255_START_SEC_CONFIG_DATA_QM_LOCAL_8

/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_W9255_MemMap.h"

/* The following array gives information about the Channel state.
- if the Channel is enabled, the array member holds the Channel inex
- if the Channel is disabled, the array member holds value 0XFF
*/
const uint8 CanTrcv_17_W9255_ChannelUsed[CANTRCV_17_W9255_CHANNELS_CONFIGURED] =
{
  /* CAN Transceiver Channel Id 0 is used */
  0U,
  /* CAN Transceiver Channel Id 1 is used */
  1U
};

/* The following array gives information about the PN state.
- if PN is enabled for the Channel, the array member holds the Channel index
- if PN is disabled for the Channel, the array member holds value 0XFF
*/
const uint8 CanTrcv_17_W9255_PnConfigured[CANTRCV_17_W9255_CHANNELS_CONFIGURED] =
{
  /* PN for CAN Transceiver Channel Id 0 is not configured */
  0xFFU,
  /* PN for CAN Transceiver Channel Id 1 is configured */
  0U
};

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define CANTRCV_17_W9255_STOP_SEC_CONFIG_DATA_QM_LOCAL_8

/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_W9255_MemMap.h"

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define CANTRCV_17_W9255_START_SEC_CONFIG_DATA_QM_LOCAL_16

/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_W9255_MemMap.h"

/* Each command consists of 2 bytes out of which the Bits 0-7 represent data
and bits 8-15 represent address of the respective register */

/* PN configuration commands(Baudrate, CAN Id, CAN Id mask and DLC) of CAN Transceiver Channel Id 1 */
static const uint16 CanTrcv_17_W9255_Ch1PnIdInfo[] =
{
  /* Baud rate of the WUF */
  /* Command to write to SWK_CTRL_2 register with PN enabled, BR ratio 10 and Baud of 500kbps */
  0x8694U,

  /* CAN ID of the WUF */
  /* Command to write CAN ID to SWK_ID0_CTRL register */
  0x8a00U,
  /* Command to write CAN ID to SWK_ID1_CTRL register */
  0x8900U,
  /* Command to write CAN ID to SWK_ID2_CTRL register */
  0x88f4U,
  /* Command to write CAN ID to SWK_ID3_CTRL register */
  0x871fU,

  /* CAN ID Mask of the WUF */
  /* Command to write CAN Id mask to SWK_MASK_ID0_CTRL register */
  0x8e00U,
  /* Command to write CAN Id mask to SWK_MASK_ID1_CTRL register */
  0x8d00U,
  /* Command to write CAN Id mask to SWK_MASK_ID2_CTRL register */
  0x8cfcU,
  /* Command to write CAN Id mask to SWK_MASK_ID3_CTRL register */
  0x8b1fU,

  /* Data Length Code of the WUF */
  0x8f08U
};

/* PN data mask configuration of CAN Transceiver Channel Id 1 */
static const uint16 CanTrcv_17_W9255_Ch1PnDataInfo[] =
{
  /* Command to write Data mask to SWK_DATA0_CTRL register */
  0x9710U,
  /* Command to write Data mask to SWK_DATA1_CTRL register */
  0x9602U,
  /* Command to write Data mask to SWK_DATA2_CTRL register */
  0x9530U,
  /* Command to write Data mask to SWK_DATA3_CTRL register */
  0x9404U,
  /* Command to write Data mask to SWK_DATA4_CTRL register */
  0x9350U,
  /* Command to write Data mask to SWK_DATA5_CTRL register */
  0x9206U,
  /* Command to write Data mask to SWK_DATA6_CTRL register */
  0x9170U,
  /* Command to write Data mask to SWK_DATA7_CTRL register */
  0x9008U
};

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define CANTRCV_17_W9255_STOP_SEC_CONFIG_DATA_QM_LOCAL_16

/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_W9255_MemMap.h"
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define CANTRCV_17_W9255_START_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED

/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_W9255_MemMap.h"

/*MISRA2012_RULE_8_9_JUSTIFICATION: The variable CanTrcv_17_W9255_PNConfig cannot
be declared at block scope as it is generated from the configuration in the
configuration files and is used by the Init API of the driver. */
const CanTrcv_17_W9255_PNConfigType CanTrcv_17_W9255_PNConfig[CANTRCV_17_W9255_PN_CONFIGURED_CHANNELS] =
{
  /* PN configuration of CAN Transceiver Channel Id 1 */
  {
    /* Pointer to baudrate, Id, Id mask of the PN frame */
    CanTrcv_17_W9255_Ch1PnIdInfo,

    /* Pointer to data masks of the PN frame */
    CanTrcv_17_W9255_Ch1PnDataInfo,

    /* Data Length Code of the WUF */
    8U
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
#define CANTRCV_17_W9255_STOP_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED

/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_W9255_MemMap.h"
