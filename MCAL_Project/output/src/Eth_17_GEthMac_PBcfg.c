
/******************************************************************************
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
**  FILENAME  : Eth_17_GEthMac_PBCfg.c                                        **
**                                                                            **
**  VERSION   : 19.0.0                                                        **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:31     !!!IGNORE-LINE!!!                     **
**                                                                            **
**  GENERATOR : Build b191017-0938       !!!IGNORE-LINE!!!                      **
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
**  DESCRIPTION  : Eth configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of Eth Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Include ETH Module File */
#include "Eth_17_GEthMac.h"
/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/
/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/
/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safeguard. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration of notification function
before MemMap inclusion It complies to Autosar guidelines. */
#include "Eth_17_GEthMac_MemMap.h"
/*Array to store index of the controller in the allocated core.*/
static const uint8 Eth_17_GEthMac_ControllerIndexMap [1] =
{
  0x0U,
};

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safeguard. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration of notification function
before MemMap inclusion It complies to Autosar guidelines. */
#include "Eth_17_GEthMac_MemMap.h"

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_CONFIG_DATA_QM_CORE0_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safeguard. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration of notification function
before MemMap inclusion It complies to Autosar guidelines. */
#include "Eth_17_GEthMac_MemMap.h"
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/*  Structure to store controller configuration data for Core0 */
static const Eth_17_GEthMac_CoreCntrlConfigType Eth_17_GEthMac_CoreCntrlConfigCore0[1]=
{
  {
    /*Specifies the Tx[0:3]/Rx[4:7] clock delay in RGMII mode for transmit
    skew timing*/
    (uint32)0,
    /* Element to store GETH_GPCTL register value for current controller */
    (uint32)2,
    /* Recommended time(in ns) to wait for back to back register write */
    (uint32)60,
    (uint16)1522U,  /*Configured Receive Buffer Length*/
    (uint16)1528U,  /*Receive Buffer Length 8 byte aligned*/
    (uint16)1522U,  /*Configured Transmit Buffer Length*/
    (uint16)1528U,  /*Transmit Buffer Length 8 byte aligned*/
    /* Properties of Ethernet Controller
    Bit[0] - Port Select(PS)
    0 for 1000Mbps
    1 for 10 or 100 Mbps
    Bit[1] - Speed(FES)
    0 for 10 Mbps when PS bit is 1 and 1 Gbps when PS bit is 0
    1 for 100 Mbps when PS bit is 1
    Bit[2:4] - PhyInterface (000-MII, 100-RMII,001-RGMII)
    Bit[5] - Mode of the Controller [0 - HALFDUPLEX, 1- FULLDUPLEX]
    Bit[6] - Tx Interrupt Enable/Disable [0 - Disabled, 1- Enabled]
    Bit[7] - Rx Interrupt Enable/Disable [0 - Disabled, 1- Enabled]
    Bit[8] - CRC Stripping Enable/Disable [0 - Disabled, 1- Enabled]
    */
    (uint16)36,
    (uint8)4U,         /*Total Receive Buffer*/
    (uint8)4U,         /*Total Transmit Buffer*/
    /* MAC address of the controller in network byte order */
    {
    (uint8)0x00U,
    (uint8)0x03U,
    (uint8)0x19U,
    (uint8)0x00U,
    (uint8)0x00U,
    (uint8)0x01U
    },
    /* Eth Controller Index */
    (uint8)0,
    /* Clock configuration for MDC */
    (uint8)0x0U,
    /*DEM Id for Ethernet controller hardware test failure*/
    DemConf_DemEventParameter_ETH_E_ACCESS,
    /*DEM Id for Ethernet controller Frames Lost Error*/
    DemConf_DemEventParameter_ETH_E_RX_FRAMESLOST,
    /*DEM Id for Ethernet controller Frames Alignment Error*/
    DemConf_DemEventParameter_ETH_E_ALIGNMENT,
    /*DEM Id for Ethernet controller Frames CRC Error*/
    DemConf_DemEventParameter_ETH_E_CRC,
    /*DEM Id for Ethernet controller  Undersize frame Error*/
    DemConf_DemEventParameter_ETH_E_UNDERSIZEFRAME,
    /*DEM Id for Ethernet controller  Oversize frame Error*/
    DemConf_DemEventParameter_ETH_E_OVERSIZEFRAME,
    /*DEM Id for Ethernet controller Single collision Error*/
    DemConf_DemEventParameter_ETH_E_SINGLECOLLISION,
    /*DEM Id for Ethernet controller Multiple collision Error*/
    DemConf_DemEventParameter_ETH_E_MULTIPLECOLLISION,
    /*DEM Id for Ethernet controller Late collision Error*/
    DemConf_DemEventParameter_ETH_E_LATECOLLISION,
  },
};
/* Structure to store core0 configuration data */
static const Eth_17_GEthMac_CoreConfigType Eth_17_GEthMac_ConfigCore0 =
{
  /* Starting address of the controller configuration for core0 */
  /* MISRA2012_RULE_11_8_JUSTIFICATION: No side effects foreseen
  * by violating this MISRA rule */
  /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  (Eth_17_GEthMac_CoreCntrlConfigType*)Eth_17_GEthMac_CoreCntrlConfigCore0,
  1U /* Maximum controllers allocated to core0 */
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_CONFIG_DATA_QM_CORE0_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safeguard. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration of notification function
before MemMap inclusion It complies to Autosar guidelines. */
#include "Eth_17_GEthMac_MemMap.h"

/*
Ethernet driver configuration root structure
*/
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safeguard. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Eth_17_GEthMac_MemMap.h"
const Eth_17_GEthMac_ConfigType Eth_17_GEthMac_Config =
{
  /* starting address of Core<x> Configuration data */
  {
    /* MISRA2012_RULE_11_8_JUSTIFICATION: No side effects foreseen
    * by violating this MISRA rule */
    (Eth_17_GEthMac_CoreConfigType*)&Eth_17_GEthMac_ConfigCore0,
    /* MISRA2012_RULE_11_8_JUSTIFICATION: No side effects foreseen
    * by violating this MISRA rule */
    NULL_PTR,
    NULL_PTR,
    NULL_PTR
  },
  /* Address of index mapping array */
  (uint8*)Eth_17_GEthMac_ControllerIndexMap
  /* MISRA2012_RULE_11_8_JUSTIFICATION: No side effects foreseen
  * by violating this MISRA rule */
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safeguard. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Eth_17_GEthMac_MemMap.h"

