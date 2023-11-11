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
**  FILENAME     : Eth_17_GEthMac.h                                           **
**                                                                            **
**  VERSION      : 27.0.0                                                     **
**                                                                            **
**  DATE         : 2023-05-22                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Eth Driver header definition file                          **
**                                                                            **
**  SPECIFICATION(S) :Specification of Ethernet Driver, AUTOSAR Release 4.2.2 **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/* [cover parentID={F631F291-6A02-4a81-92DC-7078BF5BC317}]
[/cover] */
#ifndef ETH_17_GETHMAC_H
#define ETH_17_GETHMAC_H

/*******************************************************************************
**                              Includes                                      **
*******************************************************************************/
/* [cover parentID={C2141F9A-E12A-4ed2-A8D6-33DC507061DA}]
[/cover] */
/* Inclusion of Platform_Types.h and Compiler.h */
/* [cover parentID={006C2A5F-5442-410f-8249-EDF5E2A7AF0F}]
[/cover] */
/* [cover parentID={3257A55C-7BD8-4acc-9DD6-3DE87A3873A2}]
[/cover] */
#include "Eth_17_GEthMac_Types.h"
/* Mcal_Wrapper header file */
/*As per requirement Mcal_Wrapper.h shall be included in Eth_17_GEthMac.c file. But
the Ethernet module configuration structure defined in Eth_17_GEthMac.h file
refer the data type Dem_EventIdType from Mcal_Wrapper module. Hence to avoid
compilation error, Mcal_Wrapper.h is included in Eth_17_GEthMac.h file. This is
an agreed deviation and same is captured in Ethernet User Manual*/
#include "Mcal_Wrapper.h"

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/* Service IDs which are used while reporting development errors. */
#define ETH_17_GETHMAC_SID_INIT                   ((uint8)0x01)
#define ETH_17_GETHMAC_SID_SETCONTROLLERMODE      ((uint8)0x03)
#define ETH_17_GETHMAC_SID_GETCONTROLLERMODE      ((uint8)0x04)
#define ETH_17_GETHMAC_SID_WRITEMII               ((uint8)0x05)
#define ETH_17_GETHMAC_SID_READMII                ((uint8)0x06)
#define ETH_17_GETHMAC_SID_GETPHYADDRESS          ((uint8)0x08)
#define ETH_17_GETHMAC_SID_PROVIDETXBUFFER        ((uint8)0x09)
#define ETH_17_GETHMAC_SID_TRANSMIT               ((uint8)0x0A)
#define ETH_17_GETHMAC_SID_RECEIVE                ((uint8)0x0B)
#define ETH_17_GETHMAC_SID_TXCONFIRMATION         ((uint8)0x0C)
#define ETH_17_GETHMAC_SID_GETVERSIONINFO         ((uint8)0x0D)
#define ETH_17_GETHMAC_SID_RXHANDLER              ((uint8)0x10)
#define ETH_17_GETHMAC_SID_TXHANDLER              ((uint8)0x11)
#define ETH_17_GETHMAC_SID_UPDATEFILTER           ((uint8)0x12)
#define ETH_17_GETHMAC_SID_SETPHYSADDRESS         ((uint8)0x13)
#define ETH_17_GETHMAC_SID_GETDROPCOUNT           ((uint8)0x14)
#define ETH_17_GETHMAC_SID_GETETHERSTATS          ((uint8)0x15)
#define ETH_17_GETHMAC_SID_GETCURRENTTIME         ((uint8)0x16)
#define ETH_17_GETHMAC_SID_ENABLEEGRESSTIMESTAMP  ((uint8)0x17)
#define ETH_17_GETHMAC_SID_GETEGRESSTIMESTAMP     ((uint8)0x18)
#define ETH_17_GETHMAC_SID_GETINGRESSTIMESTAMP    ((uint8)0x19)
#define ETH_17_GETHMAC_SID_SETCORRECTIONTIME      ((uint8)0x1a)
#define ETH_17_GETHMAC_SID_SETGLOBALTIME          ((uint8)0x1b)

/* Published parameters */
/* ETH Vendor ID - Vendor ID of the dedicated implementation of this
   module according to the AUTOSAR vendor list */
#define ETH_17_GETHMAC_VENDOR_ID       ((uint16)17)
/*ETH Module ID - Module ID of this module from Module List */
#define ETH_17_GETHMAC_MODULE_ID       ((uint16)88)
/* ETH Instance ID */
#define ETH_17_GETHMAC_INSTANCE_ID     ((uint8)ETH_17_GETHMAC_INDEX)

/* Error code for Development errors */
#define ETH_17_GETHMAC_E_DET_NO_ERR           ((uint8)0x00)
/* [cover parentID={CFD32D1F-72A8-46ef-9673-CE8B153C1CBF}][/cover] */
#define ETH_17_GETHMAC_E_INV_CTRL_IDX         ((uint8)0x01)
/* [cover parentID={8CB0D284-F6D3-4912-9A6B-8CE67A22D492}][/cover] */
#define ETH_17_GETHMAC_E_NOT_INITIALIZED      ((uint8)0x02)
/* [cover parentID={005A6888-4032-4490-A811-8B66B61D37DB}][/cover] */
#define ETH_17_GETHMAC_E_PARAM_POINTER        ((uint8)0x03)
/* [cover parentID={D724BE69-037F-422a-8AC2-6DD7FD7359C3}][/cover] */
#define ETH_17_GETHMAC_E_INV_PARAM            ((uint8)0x04)
/* [cover parentID={1F09E29E-E7C5-42a0-B7C3-40A67FD6DD9B}][/cover] */
#define ETH_17_GETHMAC_E_INV_MODE             ((uint8)0x05)
/* [cover parentID={1C966993-BF96-44c4-AAFA-A2D3B9FACAAD}][/cover] */
#define ETH_17_GETHMAC_E_INIT_FAILED          ((uint8)0x20)
/* [cover parentID={D32B4443-F290-4e58-823B-0D3FC15E3422}][/cover] */
#define ETH_17_GETHMAC_E_CORE_NOT_CONFIGURED  ((uint8)0x64)

/* Production error report Disable/Enable. */
#define ETH_17_GETHMAC_DISABLE_DEM_REPORT (0U)
#define ETH_17_GETHMAC_ENABLE_DEM_REPORT  (1U)

/* Enable/Disable Macro. */
#define ETH_17_GETHMAC_ENABLE             (1U)
#define ETH_17_GETHMAC_DISABLE            (0U)

#define ETH_17_GETHMAC_MCAL_SUPERVISOR    (0U)
#define ETH_17_GETHMAC_MCAL_USER1         (1U)

/* Macros for MAC Configuration Register - MAC_CONFIGURATION*/
#define ETH_17_GETHMAC_MAC_RX               (0x00000001U)
#define ETH_17_GETHMAC_RXENABLE             (0x00000001U)
#define ETH_17_GETHMAC_RXDISABLE            (0x00000000U)
#define ETH_17_GETHMAC_MAC_TX               (0x00000002U)
#define ETH_17_GETHMAC_TXENABLE             (0x00000002U)
#define ETH_17_GETHMAC_TXDISABLE            (0x00000000U)
#define ETH_17_GETHMAC_MACPREAMBLENGTH7     (0x00000000U)
#define ETH_17_GETHMAC_DEFERRALCHECKENABLE  (0x00000010U)
#define ETH_17_GETHMAC_DEFERRALCHECKDISABLE (0x00000000U)
#define ETH_17_GETHMAC_BACKOFFLIMIT         (0x00000060U)
#define ETH_17_GETHMAC_BACKOFFLIMIT3        (0x00000060U)
#define ETH_17_GETHMAC_BACKOFFLIMIT2        (0x00000040U)
#define ETH_17_GETHMAC_BACKOFFLIMIT1        (0x00000020U)
#define ETH_17_GETHMAC_BACKOFFLIMIT0        (0x00000000U)
#define ETH_17_GETHMAC_RETRYDISABLE         (0x00000100U)
#define ETH_17_GETHMAC_RETRYENABLE          (0x00000000U)
#define ETH_17_GETHMAC_DISABLERXOWN         (0x00000400U)
#define ETH_17_GETHMAC_ENABLERXOWN          (0x00000000U)
#define ETH_17_GETHMAC_LOOPBACKON           (0x00001000U)
#define ETH_17_GETHMAC_LOOPBACKOFF          (0x00000000U)
#define ETH_17_GETHMAC_FULLDUPLEX           (0x00002000U)
#define ETH_17_GETHMAC_HALFDUPLEX           (0x00000000U)
#define ETH_17_GETHMAC_JUMBOFRAMEENABLE     (0x00010000U)
#define ETH_17_GETHMAC_JUMBOFRAMEDISABLE    (0x00000000U)
#define ETH_17_GETHMAC_JABBERDISABLE        (0x00020000U)
#define ETH_17_GETHMAC_JABBERENABLE         (0x00000000U)
#define ETH_17_GETHMAC_PACKETBURSTENABLE    (0x00040000U)
#define ETH_17_GETHMAC_PACKETBURSTDISABLE   (0x00000000U)
#define ETH_17_GETHMAC_WATCHDOGDISABLE      (0x00080000U)
#define ETH_17_GETHMAC_WATCHDOGENABLE       (0x00000000U)
#define ETH_17_GETHMAC_PADCRCSTRIPENABLE    (0x00100000U)
#define ETH_17_GETHMAC_PADCRCSTRIPDISABLE   (0x00000000U)
#define ETH_17_GETHMAC_CRCSTRTPKTENABLE     (0x00200000U)
#define ETH_17_GETHMAC_CRCSTRTPKTDISABLE    (0x00000000U)
#define ETH_17_GETHMAC_INTERPACKGAP96BIT    (0x00000000U)
#define ETH_17_GETHMAC_INTERPACKGAP88BIT    (0x01000000U)
#define ETH_17_GETHMAC_INTERPACKGAP80BIT    (0x02000000U)
#define ETH_17_GETHMAC_INTERPACKGAP40BIT    (0x07000000U)

#define ETH_17_GETHMAC_PROMISC_ON           (0x00000001U)
#define ETH_17_GETHMAC_PROMISC_OFF          (0x00000000U)
#define ETH_17_GETHMAC_MULTICASTENABLE      (0x00000010U)
#define ETH_17_GETHMAC_MULTICASTDISABLE     (0x00000000U)
#define ETH_17_GETHMAC_BROADCASTDISABLE     (0x00000020U)
#define ETH_17_GETHMAC_BROADCASTENABLE      (0x00000000U)
#define ETH_17_GETHMAC_PASSCONTROL          (0x000000C0U)
#define ETH_17_GETHMAC_PASSCONTROL0         (0x00000000U)
#define ETH_17_GETHMAC_PASSCONTROL1         (0x00000040U)
#define ETH_17_GETHMAC_PASSCONTROL2         (0x00000080U)
#define ETH_17_GETHMAC_PASSCONTROL3         (0x000000C0U)
#define ETH_17_GETHMAC_RECEIVEALLOFF        (0x00000000U)
#define ETH_17_GETHMAC_RECEIVEALLON         (0x80000000U)

/* Macros for MAC MDIO Address Register - MAC_MDIO_ADDRESS*/
#define ETH_17_GETHMAC_GMIIBUSYSET          (0x00000001U)
#define ETH_17_GETHMAC_GMIIBUSYCLEAR        (0x00000000U)
#define ETH_17_GETHMAC_C45EENABLE           (0x00000002U)
#define ETH_17_GETHMAC_C45EDISABLE          (0x00000000U)
#define ETH_17_GETHMAC_WRITECOMMAND         (0x00000004U)
#define ETH_17_GETHMAC_POSTREADINCRC45      (0x00000008U)
#define ETH_17_GETHMAC_READCOMMAND          (0x0000000CU)
#define ETH_17_GETHMAC_CRPOSITION           (8U)

#define ETH_17_GETHMAC_REGADDRMASK          (0x001F0000U)
#define ETH_17_GETHMAC_REGADDRPOSITION      (16U)
#define ETH_17_GETHMAC_PHYLAYERADDRMASK     (0x03E00000U)
#define ETH_17_GETHMAC_PHYLAYERADDRPOSITION (21U)

/* Macros for MTL Operation Mode Register - MTL_OPERATION_MODE*/
#define ETH_17_GETHMAC_MTL_DTXTS_DISABLE    (0x00000000U)
#define ETH_17_GETHMAC_MTL_DTXTS_ENABLE     (0x00000002U)
#define ETH_17_GETHMAC_MTL_RAA_SP           (0x00000000U)
#define ETH_17_GETHMAC_MTL_RAA_WSP          (0x00000004U)
#define ETH_17_GETHMAC_MTL_SCHALG_WRR       (0x00000000U)
#define ETH_17_GETHMAC_MTL_SCHALG_SP        (0x00000060U)

/* Macros, MTL Queue0 Transmit Operation Mode Register-MTL_TXQ0_OPERATION_MODE*/
#define ETH_17_GETHMAC_MTL_FTQ              (0x00000001U)
#define ETH_17_GETHMAC_MTL_TSF              (0x00000002U)
#define ETH_17_GETHMAC_MTL_TXQEN            (0x00000008U)
#define ETH_17_GETHMAC_MTL_TXQS_256BYTES    (0x00000000U)
#define ETH_17_GETHMAC_MTL_TXQS_2048BYTES   (0x00070000U)
#define ETH_17_GETHMAC_MTL_TXQS_4096BYTES   (0x000F0000U)

/* Macros, MTL Queue 0 Receive Operation Mode Register-MTL_RXQ0_OPERATION_MODE*/
#define ETH_17_GETHMAC_MTL_FUP              (0x00000008U)
#define ETH_17_GETHMAC_MTL_FEP              (0x00000010U)
#define ETH_17_GETHMAC_MTL_RSF              (0x00000020U)
#define ETH_17_GETHMAC_MTL_DIS_TCP_EF       (0x00000040U)
#define ETH_17_GETHMAC_MTL_RQS_256BYTES     (0x00000000U)
#define ETH_17_GETHMAC_MTL_RQS_2048BYTES    (0x00700000U)
#define ETH_17_GETHMAC_MTL_RQS_4096BYTES    (0x00F00000U)
#define ETH_17_GETHMAC_MTL_RQS_8192BYTES    (0x01F00000U)

/* Macros for DMA Bus Mode Register - DMA_MODE*/
#define ETH_17_GETHMAC_DMA_SWR              (0x00000001U)
#define ETH_17_GETHMAC_DMA_TX_RX_ARB_WRR    (0x00000000U)
#define ETH_17_GETHMAC_DMA_TX_RX_ARB_FP     (0x00000002U)
#define ETH_17_GETHMAC_DMA_TAA_FP           (0x00000000U)
#define ETH_17_GETHMAC_DMA_TAA_WSP          (0x00000004U)
#define ETH_17_GETHMAC_DMA_TAA_WRB          (0x00000008U)
#define ETH_17_GETHMAC_DMA_TXPR_DISABLE     (0x00000000U)
#define ETH_17_GETHMAC_DMA_TXPR_ENABLE      (0x00000800U)
#define ETH_17_GETHMAC_DMA_INTM_ZERO        (0x00000000U)
#define ETH_17_GETHMAC_DMA_INTM_ONE         (0x00010000U)
#define ETH_17_GETHMAC_DMA_INTM_TWO         (0x00020000U)
#define ETH_17_GETHMAC_DMA_INTM_THREE       (0x00030000U)

/* Macros for DMA System Bus Mode Register - DMA_SYSBUS_MODE*/
#define ETH_17_GETHMAC_DMA_FB_DISABLE       (0x00000000U)
#define ETH_17_GETHMAC_DMA_FB_ENABLE        (0x00000001U)
#define ETH_17_GETHMAC_DMA_AAL_DISABLE      (0x00000000U)
#define ETH_17_GETHMAC_DMA_AAL_ENABLE       (0x00001000U)
#define ETH_17_GETHMAC_DMA_MB_DISABLE       (0x00000000U)
#define ETH_17_GETHMAC_DMA_MB_ENABLE        (0x00004000U)

/* Macros for DMA Channel i Transmit Control Register - DMA_CHi_TX_CONTROL*/
#define ETH_17_GETHMAC_DMA_TX_CH_STOP       (0x00000000U)
#define ETH_17_GETHMAC_DMA_TX_CH_START      (0x00000001U)

/* Macros for DMA Channel i Receive Control Register - DMA_CHi_RX_CONTROL*/
#define ETH_17_GETHMAC_DMA_RX_CH_STOP       (0x00000000U)
#define ETH_17_GETHMAC_DMA_RX_CH_START      (0x00000001U)

/* Macros for DMA Channel i Status Register - DMA_CHi_STATUS*/
#define ETH_17_GETHMAC_DMA_CH_STAT_TI_SET             (0x00000001U)
#define ETH_17_GETHMAC_DMA_CH_STAT_TI_RESET           (0x00000001U)
#define ETH_17_GETHMAC_DMA_CH_STAT_RI_SET             (0x00000040U)
#define ETH_17_GETHMAC_DMA_CH_STAT_RI_RESET           (0x00000040U)
#define ETH_17_GETHMAC_DMA_CH_STAT_RBU_ERI_AIE_RESET  (0x00004880U)
#define ETH_17_GETHMAC_DMA_CH_STAT_NIS_RESET          (0x00008000U)
#define ETH_17_GETHMAC_DMA_CH_STAT_CLR_ALL            (0x0000FFC7U)

/* Macros for DMA Transmit Descriptor */
#define ETH_17_GETHMAC_DMA_TX_DESC_TS_DISABLE   (0xBFFFFFFFU)
#define ETH_17_GETHMAC_DMA_TX_DESC_TS_ENABLE    (0x40000000U)
#define ETH_17_GETHMAC_DMA_TX_DESC_TTSS_SET     (0x00020000U)
#define ETH_17_GETHMAC_DMA_TX_DESC_CTXT_SET     (0x40000000U)
#define ETH_17_GETHMAC_DMA_TX_DESC_FD_RESET     (0x00000000U)
#define ETH_17_GETHMAC_DMA_TX_DESC_FD_SET       (0x20000000U)
#define ETH_17_GETHMAC_DMA_TX_DESC_LD_RESET     (0x00000000U)
#define ETH_17_GETHMAC_DMA_TX_DESC_LD_SET       (0x10000000U)
#define ETH_17_GETHMAC_DMA_TX_DESC_CPC_ENABLE   (0x00000000U)
#define ETH_17_GETHMAC_DMA_TX_DESC_CIC_PSDO     (0x00030000U)
#define ETH_17_GETHMAC_DMA_TX_DESC_PAC_LEN_MASK (0x00007FFFU)
#define ETH_17_GETHMAC_DMA_TX_DESC_IOC_ENABLE   (0x80000000U)
#define ETH_17_GETHMAC_DMA_TX_DESC_OWN_SET      (0x80000000U)

/* Macros for DMA Receive Descriptor */
#define ETH_17_GETHMAC_DMA_RX_DESC_IOC_ENABLE   (0x40000000U)
#define ETH_17_GETHMAC_DMA_RX_DESC_BF1_VALID    (0x01000000U)
#define ETH_17_GETHMAC_DMA_RX_DESC_BF2_INVALID  (0x00000000U)
#define ETH_17_GETHMAC_DMA_RX_DESC_TSA_SET      (0x00004000U)
#define ETH_17_GETHMAC_DMA_RX_DESC_CTXT_SET     (0x40000000U)
#define ETH_17_GETHMAC_DMA_RX_DESC_FD_RESET     (0x00000000U)
#define ETH_17_GETHMAC_DMA_RX_DESC_FD_SET       (0x20000000U)
#define ETH_17_GETHMAC_DMA_RX_DESC_LD_RESET     (0x00000000U)
#define ETH_17_GETHMAC_DMA_RX_DESC_LD_SET       (0x10000000U)
#define ETH_17_GETHMAC_DMA_RX_DESC_PL_MASK      (0x00007FFFU)
#define ETH_17_GETHMAC_DMA_RX_DESC_OWN_SET      (0x80000000U)

/* Macros used for list of Ethernet statistics items to be returned from
Eth_GetEtherStats() APIs */
#define ETH_17_GETHMAC_STAT_DROP_EVENTS           (0U)
#define ETH_17_GETHMAC_STAT_OCTETS                (1U)
#define ETH_17_GETHMAC_STAT_PKTS                  (2U)
#define ETH_17_GETHMAC_STAT_BROADCAST_PKTS        (3U)
#define ETH_17_GETHMAC_STAT_MULTICAST_PKTS        (4U)
#define ETH_17_GETHMAC_STAT_CRC_ALIGN_ERRORS      (5U)
#define ETH_17_GETHMAC_STAT_UNDERSIZE_PKTS        (6U)
#define ETH_17_GETHMAC_STAT_OVERSIZE_PKTS         (7U)
#define ETH_17_GETHMAC_STAT_FRAGMENTS             (8U)
#define ETH_17_GETHMAC_STAT_JABBERS               (9U)
#define ETH_17_GETHMAC_STAT_COLLISIONS            (10U)
#define ETH_17_GETHMAC_STAT_PKTS_64_OCTETS        (11U)
#define ETH_17_GETHMAC_STAT_PKTS_65_127_OCTETS    (12U)
#define ETH_17_GETHMAC_STAT_PKTS_128_255_OCTETS   (13U)
#define ETH_17_GETHMAC_STAT_PKTS_256_511_OCTETS   (14U)
#define ETH_17_GETHMAC_STAT_PKTS_512_1023_OCTETS  (15U)
#define ETH_17_GETHMAC_STAT_PKTS_1024_1518_OCTETS (16U)

/* Macros used for list of Ethernet drop count items to be returned from
Eth_GetDropCount() APIs */
#define ETH_17_GETHMAC_DROP_PKTS_BUFOVERRUN       (0U)
#define ETH_17_GETHMAC_DROP_PKTS_CRCERROR         (1U)
#define ETH_17_GETHMAC_DROP_PKTS_UNDERSIZE        (2U)
#define ETH_17_GETHMAC_DROP_PKTS_OVERSIZE         (3U)
#define ETH_17_GETHMAC_DROP_PKTS_ALIGNERROR       (4U)
#define ETH_17_GETHMAC_DROP_PKTS_SQETESTERROR     (5U)
#define ETH_17_GETHMAC_DROP_PKTS_RECV_Q_OVERFLOW  (6U)
#define ETH_17_GETHMAC_DROP_ERRONEOUS_INB_PKTS    (7U)
#define ETH_17_GETHMAC_DROP_OUTB_PKTS             (8U)
#define ETH_17_GETHMAC_DROP_ERRONEOUS_OUTB_PKTS   (9U)
#define ETH_17_GETHMAC_SINGLE_COLLISION_PKTS      (10U)
#define ETH_17_GETHMAC_MULTIPLE_COLLISION_PKTS    (11U)
#define ETH_17_GETHMAC_DEFERRED_TRANSMISSION_PKTS (12U)
#define ETH_17_GETHMAC_LATE_COLLISION_PKTS        (13U)

/*******************************************************************************
**          Macros for Configuration Register Initial values                  **
*******************************************************************************/
/* Alternate input for Receive Clock for RGMII (RGMII can use ALT0 only).*/
#define ETH_17_GETHMAC_RXCLK_ALT0_INPUT    (0x00000000U)
/* Alternate input for Receive Data 0 for RGMII (RGMII can use ALT0 only) */
#define ETH_17_GETHMAC_RXDATA0_ALT0_INPUT  (0x00000000U)
/* Alternate input for Receive Data 1 for RGMII (RGMII can use ALT0 only) */
#define ETH_17_GETHMAC_RXDATA1_ALT0_INPUT  (0x00000000U)
/* Alternate input for Receive Data 2 for RGMII (RGMII can use ALT0 only) */
#define ETH_17_GETHMAC_RXDATA2_ALT0_INPUT  (0x00000000U)
/* Alternate input for Receive Data 3 for RGMII (RGMII can use ALT0 only) */
#define ETH_17_GETHMAC_RXDATA3_ALT0_INPUT  (0x00000000U)

/**** FULL DUPLEX MODE ****/
/* Init value for MAC configuration Register in Full-duplex mode. */
#define ETH_17_GETHMAC_MAC_INIT_CONF_FDX (\
    (ETH_17_GETHMAC_MACPREAMBLENGTH7     |\
     ETH_17_GETHMAC_DEFERRALCHECKDISABLE | ETH_17_GETHMAC_BACKOFFLIMIT2     |\
     ETH_17_GETHMAC_RETRYENABLE          | ETH_17_GETHMAC_ENABLERXOWN       |\
     ETH_17_GETHMAC_LOOPBACKOFF          | ETH_17_GETHMAC_JUMBOFRAMEDISABLE |\
     ETH_17_GETHMAC_JABBERDISABLE        |\
     ETH_17_GETHMAC_PACKETBURSTDISABLE   | ETH_17_GETHMAC_WATCHDOGENABLE    |\
     ETH_17_GETHMAC_PADCRCSTRIPDISABLE   |\
     ETH_17_GETHMAC_CRCSTRTPKTDISABLE    | ETH_17_GETHMAC_INTERPACKGAP96BIT |\
     ETH_17_GETHMAC_TXDISABLE            | ETH_17_GETHMAC_RXDISABLE         |\
     ETH_17_GETHMAC_FULLDUPLEX))

/**** HALF DUPLEX MODE   ****/
/* Init value for MAC configuration Register in Half-duplex mode. */
#define ETH_17_GETHMAC_MAC_INIT_CONF_HDX (\
    (ETH_17_GETHMAC_MACPREAMBLENGTH7     |\
     ETH_17_GETHMAC_DEFERRALCHECKDISABLE | ETH_17_GETHMAC_BACKOFFLIMIT2     |\
     ETH_17_GETHMAC_RETRYENABLE          | ETH_17_GETHMAC_ENABLERXOWN       |\
     ETH_17_GETHMAC_LOOPBACKOFF          | ETH_17_GETHMAC_JUMBOFRAMEDISABLE |\
     ETH_17_GETHMAC_JABBERDISABLE        |\
     ETH_17_GETHMAC_PACKETBURSTDISABLE   | ETH_17_GETHMAC_WATCHDOGENABLE    |\
     ETH_17_GETHMAC_PADCRCSTRIPDISABLE   |\
     ETH_17_GETHMAC_CRCSTRTPKTDISABLE    | ETH_17_GETHMAC_INTERPACKGAP96BIT |\
     ETH_17_GETHMAC_DEFERRALCHECKDISABLE | ETH_17_GETHMAC_HALFDUPLEX))

/**** MAC Registers   ****/
/* Init value for MAC Packet Filter Register. */
#define ETH_17_GETHMAC_MAC_PACKT_FILT_INIT_CONF (\
                                        (ETH_17_GETHMAC_PROMISC_OFF       |\
                                         ETH_17_GETHMAC_BROADCASTENABLE   |\
                                         ETH_17_GETHMAC_RECEIVEALLOFF     |\
                                         ETH_17_GETHMAC_PASSCONTROL0))

/*MAC Packet Filter Register value to completly open filter.*/
#define ETH_17_GETHMAC_MAC_PACKT_FILT_OPEN_CONF (\
                                        (ETH_17_GETHMAC_PROMISC_ON       |\
                                         ETH_17_GETHMAC_MULTICASTENABLE  |\
                                         ETH_17_GETHMAC_RECEIVEALLON))

/**** MTL Registers   ****/
/* Init value for MTL Operation Mode Register - Common for Tx and Rx. */
#define ETH_17_GETHMAC_MTL_OPERTN_MODE_INIT  (\
                                        (ETH_17_GETHMAC_MTL_DTXTS_DISABLE|\
                                         ETH_17_GETHMAC_MTL_RAA_SP       |\
                                         ETH_17_GETHMAC_MTL_SCHALG_SP))

/* Init value for MTL TX-Q Operation Mode Register. */
#define ETH_17_GETHMAC_MTL_TXQ0_OPERTN_MODE_INIT  (\
                                        (ETH_17_GETHMAC_MTL_TSF          |\
                                         ETH_17_GETHMAC_MTL_TXQEN        |\
                                         ETH_17_GETHMAC_MTL_TXQS_4096BYTES))

/* Init value for MTL RX-Q Operation Mode Register. */
#define ETH_17_GETHMAC_MTL_RX_Q0_OPERTN_MODE_INIT (\
                                        (ETH_17_GETHMAC_MTL_RSF          |\
                                         ETH_17_GETHMAC_MTL_RQS_8192BYTES))

/* Macro for RX-Q0 to DMA-channel-0 mapping. */
#define ETH_17_GETHMAC_MTL_RX_Q0_T0_DMA_MAP       (0x00U)

/* Macro to enable RX-Q0. */
#define ETH_17_GETHMAC_MTL_ENABLE_RX_Q            (0x02U)

/**** DMA Registers   ****/
/* Init value for DMA Bus Mode Register. Interrupt Mode(INTM) - 01 */
#define ETH_17_GETHMAC_DMA_BUS_MODE_INIT_CONF    (0x00010000U)

/* Init value for DMA System Bus Mode Register. */
#define ETH_17_GETHMAC_DMA_SYSBUS_MODE_INIT_CONF (\
                                          ETH_17_GETHMAC_DMA_FB_DISABLE  |\
                                          ETH_17_GETHMAC_DMA_AAL_DISABLE |\
                                          ETH_17_GETHMAC_DMA_MB_DISABLE)

/* Macto to configure DMA 8xPBL( 8x burst length) mode. */
#define ETH_17_GETHMAC_DMA_8X_BURST_LENGTH_MODE   (ETH_17_GETHMAC_DISABLE)

/*Macto to configure DMA PBL( burst length) for Tx-DMA-CH0*/
#define ETH_17_GETHMAC_DMA_CH_TXCTRL_CONF         (0x00080000U)

/*Macto to configure DMA PBL( burst length) for Rx-DMA-CH0*/
#define ETH_17_GETHMAC_DMA_CH0_RXPBL              (0x08U)

/**** DMA-Tx Descriptor ****/
/* Init value for TX- Descriptor TDES2. */
#define ETH_17_GETHMAC_DMA_TDES2_INIT    ETH_17_GETHMAC_DMA_TX_DESC_IOC_ENABLE

/**** DMA-Tx Descriptor ****/
/* Init value for RX- Descriptor RDES3. */
#define ETH_17_GETHMAC_DMA_RDES3_INIT    (\
                                  (ETH_17_GETHMAC_DMA_RX_DESC_OWN_SET     |\
                                   ETH_17_GETHMAC_DMA_RX_DESC_IOC_ENABLE  |\
                                   ETH_17_GETHMAC_DMA_RX_DESC_BF2_INVALID |\
                                   ETH_17_GETHMAC_DMA_RX_DESC_BF1_VALID))

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
/*Structure to store controller configuration data */
/* [cover parentID={302AB06B-C7CF-4716-A8A6-A90FDC59D31C}]
[/cover] */
typedef struct
{
  /*Specifies the Tx[0:3]/Rx[4:7] clock delay in RGMII mode for transmit
    skew timing*/
  uint32 EthSkewDelay;
  /* Element to store GETH_GPCTL register value for the controller */
  uint32 EthGptclRegVal;
  /* Recommended time to wait for back to back register write */
  uint32 EthBkRegWrWaitTime;
  /* Configured maximum receive buffer length (frame length) in bytes */
  uint16  EthCtrlRxBufLenByte;
  /* Maximum receive buffer length (frame length) aligned to 8 bytes */
  uint16  EthCtrlRxBufLenByteAligned;
  /* Configured maximum transmit buffer length (frame length) in bytes*/
  uint16  EthCtrlTxBufLenByte;
  /* Maximum transmit buffer length (frame length) aligned to 8 bytes*/
  uint16  EthCtrlTxBufLenByteAligned;
  /* Propertes of Ethernet Controller
     Bit[0] - Port Select(PS)
       0 for 1000Mbps
       1 for 10 or 100 Mbps
     Bit[1] - Speed(FES)
       0 for 10 Mbps when PS bit is 1 and 1 Gbps when PS bit is 0.
       1 for 100 Mbps when PS bit is 1.
     Bit[2:4] - PhyInterface (000-MII, 100-RMII, 001-RGMII).
     Bit[5] - Mode of the Controller. [0 - HALFDUPLEX, 1- FULLDUPLEX].
     Bit[6] - Tx Interrupt Enable/Disable [0 - Disabled, 1- Enabled].
     Bit[7] - Rx Interrupt Enable/Disable [0 - Disabled, 1- Enabled].
     Bit[8] - CRC Stripping Enable/Disable [0 - Disabled, 1- Enabled].
  */
  uint16 EthCntrlProperties;
  /* Configures the number of receive buffers. */
  uint8  EthRxBufTotal;
  /* Configures the number of transmit buffers */
  uint8  EthTxBufTotal;
  /* Default PHY MAC address in Network Byte order */
  uint8  EthMacAddress[6];
    /* Ethernet Controller Index */
  uint8  EthCntrlIdx;
  /* Clock configuration for MDC */
  uint8 EthMdcRegVal;
      /*DEM Id for ETH_E_ACCESS Failure.*/
  /* [cover parentID={7F26C03F-7232-41c7-B2A2-2674B4E11D13}][/cover] */
  Dem_EventIdType                EthDemAccess;
  /*DEM Id for ETH_E_RX_FRAMES_LOST Failure.*/
  /* [cover parentID={AD39B3B9-1A01-441a-B7E1-C0B90C5DC49A}][/cover] */
  Dem_EventIdType                EthDemFramesLost;
  /*DEM Id for ETH_E_ALIGNMENT Failure.*/
  /* [cover parentID={58C00BB7-2052-46e5-BD8E-F0FF248B2A03}][/cover] */
  Dem_EventIdType                EthDemAlignment;
  /*DEM Id for ETH_E_CRC Failure.*/
  /* [cover parentID={F6A4ED33-1F0D-4238-BEA8-EC1FB16B6B83}][/cover] */
  Dem_EventIdType                EthDemCRC;
  /*DEM Id for ETH_E_UNDERSIZEFRAME Failure.*/
  /* [cover parentID={7416B1F9-7139-4144-84C0-C31C67D4EFEA}][/cover] */
  Dem_EventIdType                EthDemUndersize;
  /*DEM Id for ETH_E_OVERSIZEFRAME Failure.*/
  /* [cover parentID={DE0FC630-0978-4dce-85E4-7187F48C2F19}][/cover] */
  Dem_EventIdType                EthDemOversize;
  /*DEM Id for ETH_E_SINGLE_COLLISION Failure.*/
  /* [cover parentID={306CDF5D-CA03-4bfe-BA95-FFC6DBB98224}][/cover] */
  Dem_EventIdType                EthDemSingleCollision;
  /*DEM Id for ETH_E_MULTIPLE_COLLISION Failure.*/
  /* [cover parentID={5C25B2B1-3400-4bdf-88C2-5688688B704E}][/cover] */
  Dem_EventIdType                EthDemMultipleCollision;
  /*DEM Id for ETH_E_LATE_COLLISION Failure.*/
  /* [cover parentID={25A75584-F192-423a-BC3C-BCF3327233FD}][/cover] */
  Dem_EventIdType                EthDemLateCollision;
}Eth_17_GEthMac_CoreCntrlConfigType;

/* Structure to store core configuration data */
/* [cover parentID={0BE34167-3E19-46db-B1F6-5AA60275D75D}] `
[/cover] */
typedef struct
{
  /* Element to store address of controller configuration for the current
     core */
  Eth_17_GEthMac_CoreCntrlConfigType* EthCoreCntrlPtr;
  /* Element to store maximum controllers allocated to current core */
  uint8                         EthMaxControllers;
}Eth_17_GEthMac_CoreConfigType;

/*Structure for Ethernet Post-Build configuration(for initialization) */
/* [cover parentID={A548EE9C-43A6-40f5-86F9-4B79EF243680}]
[/cover] */
typedef struct
{
  /* Array to store starting addresses of Core Configuration data*/
  Eth_17_GEthMac_CoreConfigType* EthCoreAdd[ETH_17_GETHMAC_MAX_CORES];
  /* Pointer to the array, Array value represents the index of the controller
     in the current core.*/
  uint8*                         EthNodeIdxmapPtr;
}Eth_17_GEthMac_ConfigType;

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
#define ETH_17_GETHMAC_START_SEC_CODE_QM_GLOBAL
#include "Eth_17_GEthMac_MemMap.h"

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax           : void Eth_17_GEthMac_TxDmaCh0IrqHdlr(const uint8 CtrlIdx)**
**                                                                            **
** Description      : IRQ handler for frame transmission completion           **
**                    interrupt from Transmit DMA channel-0.                  **
**                    Note: loop to check TI is required as no new interrupt  **
**                          is generated, if a new TX event occurs            **
**                          while NIS is still set                            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant for the same CtrlIdx,                     **
**                    reentrant for different                                 **
**                                                                            **
** Parameters (in)  : CtrlIdx - Controller Index                              **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void Eth_17_GEthMac_TxDmaCh0IrqHdlr(const uint8 CtrlIdx);

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax           : void Eth_17_GEthMac_RxDmaCh0IrqHdlr(const uint8 CtrlIdx)**
**                                                                            **
** Description      : IRQ handler for frame reception completion              **
**                    interrupts from Receive DMA channel-0                   **
**                    Note: loop to check RI is required as no new interrupt  **
**                          is generated, if a new RX event occurs            **
**                          while RI is still set                             **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant for the same CtrlIdx,                     **
**                    reentrant for different                                 **
**                                                                            **
** Parameters (in)  : CtrlIdx - Controller Index                              **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void Eth_17_GEthMac_RxDmaCh0IrqHdlr(const uint8 CtrlIdx);


#if ( ETH_17_GETHMAC_ENA_MII_API == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax           : Eth_ReturnType Eth_17_GEthMac_ReadMii(                  **
**                                   const uint8 CtrlIdx,                     **
**                                   const uint8 TrcvIdx,const uint8 RegIdx,  **
**                                   uint16 *const RegValPtr)                 **
**                                                                            **
** Description      : Reads a transceiver register                            **
**                                                                            **
*** [/cover]                                                                  **
**                                                                            **
** Service ID       : 0x06                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx - Index of the controller                       **
**                    TrcvIdx - Index of the transceiver on the MII           **
**                    RegIdx  - Index of the transceiver register on the MII  **
** Parameters (out) : *RegVal - Filled with the register content of the       **
**                              indexed register                              **
**                                                                            **
** Return value     : Eth_ReturnType                                          **
**                                                                            **
*******************************************************************************/
extern Eth_ReturnType Eth_17_GEthMac_ReadMii(const uint8 CtrlIdx,
                                             const uint8 TrcvIdx,
                                             const uint8 RegIdx,
                                             uint16* const RegValPtr);

/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax           : Eth_ReturnType Eth_17_GEthMac_WriteMii(                 **
**                                        const uint8 CtrlIdx,                **
**                                        const uint8 TrcvIdx,                **
**                                        const uint8 RegIdx,                 **
**                                        const uint16 RegVal)                **
**                                                                            **
** Description      : Configures a transceiver register or triggers a function**
**                    offered by the transceiver                              **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x05                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx - Index of the controller                       **
**                    TrcvIdx - Index of the transceiver on the MII           **
**                    RegIdx  - Index of the transceiver register on the MII  **
**                    RegVal  - Value to be written into the indexed register **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Eth_ReturnType                                          **
**                                                                            **
*******************************************************************************/
extern Eth_ReturnType Eth_17_GEthMac_WriteMii(const uint8 CtrlIdx,
                                              const uint8 TrcvIdx,
                                              const uint8 RegIdx,
                                              const uint16 RegVal);
#else

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Eth_17_GEthMac_ReadMii(CtrlIdx,TrcvIdx,RegIdx,RegValPtr) \
                             (ERROR_Eth_17_GEthMac_ReadMii_API_IS_NOT_SELECTED)

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Eth_17_GEthMac_WriteMii(CtrlIdx,TrcvIdx,RegIdx,RegVal) \
                            (ERROR_Eth_17_GEthMac_WriteMii_API_IS_NOT_SELECTED)

#endif /* End of ETH_17_GETHMAC_ENA_MII_API */

/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax           : void Eth_17_GEthMac_Init                                **
**                       (const Eth_17_GEthMac_ConfigType* const CfgPtr )     **
**                                                                            **
** Description      : The function Initializes the Ethernet Driver and        **
**                    store the access to the configuration                   **
**                    parameters for subsequent API calls.                    **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x01                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non- Reentrant                                          **
**                                                                            **
** Parameters (in)  : CfgPtr - Pointer to configuration set                   **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void Eth_17_GEthMac_Init(const Eth_17_GEthMac_ConfigType* const CfgPtr);

/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax           : BufReq_ReturnType Eth_17_GEthMac_ProvideTxBuffer(       **
**                             const uint8 CtrlIdx,                           **
**                             Eth_BufIdxType* const BufIdxPtr,               **
**                             uint8** const BufPtr,uint16* const LenBytePtr) **
**                                                                            **
** Description      : Provides access to reserved transmit buffer of indexed  **
**                    controller                                              **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x09                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx   - Index of the controller                     **
**                                                                            **
** Parameters (inout): LenBytePtr -In: desired length in bytes,               **
**                                 out: granted length in bytes               **
** Parameters (out) : BufIdxPtr - Index to the granted buffer resource        **
**                    BufPtr    - Pointer to the granted buffer               **
** Return value     : BUFREQ_OK       - Successfully granted buffer           **
**                    BUFREQ_E_NOT_OK - Development error detected            **
**                    BUFREQ_E_BUSY   - All Buffers are in USE                **
**                    BUFREQ_E_OVFL   - Requested buffer too large            **
**                                                                            **
*******************************************************************************/
extern BufReq_ReturnType Eth_17_GEthMac_ProvideTxBuffer(const uint8 CtrlIdx,
        Eth_BufIdxType* const BufIdxPtr, uint8** const BufPtr,
        uint16* const LenBytePtr);

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax           : Std_ReturnType Eth_17_GEthMac_Transmit(                 **
**                    const uint8 CtrlIdx, const uint8 BufIdx,                **
**                    const Eth_FrameType FrameType,                          **
**                    boolean TxConfirmation, const uint16 LenByte,           **
**                    const uint8* const PhysAddrPtr)                         **
**                                                                            **
** Description      : Triggers transmission of a previously                   **
**                    filled transmit buffer                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x0A                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx  - Index of the controller                      **
**                    BufIdx - Index of the buffer resource                   **
**                    FrameType- Ethernet frame type                          **
**                    TxConfirmation - Activates transmission confirmation    **
**                    LenByte - Data length in byte                           **
**                    PhysAddrPtr - Physical target address                   **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK     - Success                                      **
**                    E_NOT_OK - Transmission failed                          **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Eth_17_GEthMac_Transmit(
              const uint8 CtrlIdx, const Eth_BufIdxType BufIdx,
              const Eth_FrameType FrameType, const boolean TxConfirmation,
              const uint16 LenByte, const uint8* const PhysAddrPtr);

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax           : void Eth_17_GEthMac_Receive( const uint8 CtrlIdx,       **
**                                   Eth_RxStatusType* const RxStatusPtr )    **
**                                                                            **
** Description      : Triggers frame reception                                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x0B                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx  - Index of the controller                      **
**                                                                            **
** Parameters (out) : RxStatusPtr -  Indicates whether a frame has been       **
**                                   received and if so, whether more frames  **
**                                   are available or frames got lost.        **
**                                                                            **
*** Return value     : None                                                   **
**                                                                            **
*******************************************************************************/
extern void Eth_17_GEthMac_Receive(const uint8 CtrlIdx,
                                      Eth_RxStatusType* const RxStatusPtr);

/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax           : void Eth_17_GEthMac_GetPhysAddr( const uint8 CtrlIdx,   **
**                                             uint8* const PhysAddrPtr )     **
**                                                                            **
** Description      : Obtains the physical source address used by the         **
**                    indexed controller                                      **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x08                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non -Reentrant                                          **
**                                                                            **
** Parameters (in)  : CtrlIdx   - Index of the controller                     **
**                                                                            **
** Parameters (out) : Physical source address (MAC address) in network byte   **
**                    order.                                                  **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void Eth_17_GEthMac_GetPhysAddr(const uint8 CtrlIdx,
                                         uint8* const PhysAddrPtr);

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax           : void Eth_17_GEthMac_TxConfirmation(const uint8 CtrlIdx) **
**                                                                            **
** Description      : Triggers frame transmission confirmation                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x0C                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx  - Index of the controller                      **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void Eth_17_GEthMac_TxConfirmation( const uint8 CtrlIdx);

/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax           : Std_ReturnType Eth_17_GEthMac_SetControllerMode(        **
**                                    const uint8 CtrlIdx,                    **
**                                    const Eth_ModeType CtrlMode )           **
**                                                                            **
** Description      : Enables / Disables the indexed controller               **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x03                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx   - Index of the controller                     **
**                    CtrlMode  - Controller Mode DOWN/ACTIVE                 **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK     - Successfully Set the requested mode          **
**                    E_NOT_OK - Controller mode could not be changed         **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Eth_17_GEthMac_SetControllerMode(const uint8 CtrlIdx,
                                                 const Eth_ModeType CtrlMode );

/*******************************************************************************
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax           : Std_ReturnType Eth_17_GEthMac_GetControllerMode(        **
**                        const uint8 CtrlIdx,Eth_ModeType* const CtrlModePtr)**
**                                                                            **
** Description      : Obtains the state of the indexed controller             **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x04                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx   - Index of the controller                     **
**                                                                            **
** Parameters (out) : CtrlModePtr  -Controller Mode DOWN/ACTIVE               **
**                                                                            **
** Return value     : E_OK     - Success                                      **
**                    E_NOT_OK - Controller mode could not be obtained        **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Eth_17_GEthMac_GetControllerMode(const uint8 CtrlIdx,
                                             Eth_ModeType* const CtrlModePtr);

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax           : void Eth_17_GEthMac_SetPhysAddr( const uint8 CtrlIdx,   **
**                                         const uint8* const PhysAddrPtr )   **
**                                                                            **
** Description      : Sets the controllers MAC address                        **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x13                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant for the same CtrlIdx,                     **
**                    reentrant for different                                 **
**                                                                            **
** Parameters (in)  : CtrlIdx  - Index of the controller                      **
**                    PhysAddrPtr - MAC address in network byte order         **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void Eth_17_GEthMac_SetPhysAddr(const uint8 CtrlIdx,
                                       const uint8* const PhysAddrPtr);

#if (ETH_17_GETHMAC_UPDATE_PHY_ADDR_FILTER_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax           : Std_ReturnType Eth_17_GEthMac_UpdatePhysAddrFilter(     **
**                      const uint8 CtrlIdx,const uint8* const PhysAddrPtr,   **
**                      const Eth_FilterActionType Action )                   **
**                                                                            **
** Description      : Adds or removes the MAC address from filter             **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x12                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Rentrant                                            **
**                                                                            **
** Parameters (in)  : CtrlIdx  - Index of the controller                      **
**                    PhysAddrPtr - MAC address in network byte order         **
**                    Action - Add or remove the MAC address from filter      **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK - Filter was successfully changed                  **
**                    E_NOT_OK - Filter could not be changed                  **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Eth_17_GEthMac_UpdatePhysAddrFilter(
                       const uint8 CtrlIdx, const uint8* const PhysAddrPtr,
                       const Eth_FilterActionType Action);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Eth_17_GEthMac_UpdatePhysAddrFilter(CtrlIdx,PhysAddrPtr,Action) \
                (ERROR_Eth_17_GEthMac_UpdatePhysAddrFilter_API_IS_NOT_SELECTED)
#endif /* End for ETH_17_GETHMAC_UPDATE_PHY_ADDR_FILTER_API */

#if (ETH_17_GETHMAC_GETDROPCOUNT_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax           : Std_ReturnType  Eth_17_GEthMac_GetDropCount(            **
**                                const uint8 CtrlIdx,const uint8 CountValues,**
**                                uint32* const DropCount)                    **
**                                                                            **
** Description      : Reads a list with drop counter values.                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x14                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx     - Index of Eth Controller within the        **
**                                  context of the Ethernet driver.           **
**                                                                            **
**                    DropCount   - Different Drop/Error count values         **
**                                  values is hardware dependent              **
**                                                                            **
**                    CountValues - Maximal number of values which can be     **
**                                  written from DropCount                    **
** Parameters (out) : CountValues - Not used as Out parameter due to          **
**                                  Autosar API definition limitation.        **
**                                                                            **
** Return value     : Std_ReturnType -  E_OK: success                         **
**                                      E_NOT_OK: drop counter could          **
**                                                not be obtained.            **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Eth_17_GEthMac_GetDropCount( const uint8 CtrlIdx,
                             const uint8 CountValues, uint32* const DropCount);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Eth_17_GEthMac_GetDropCount(CtrlIdx,CountValues,DropCount) \
                        (ERROR_Eth_17_GEthMac_GetDropCount_API_IS_NOT_SELECTED)

#endif/* End for ETH_17_GETHMAC_GETDROPCOUNT_API */

#if (ETH_17_GETHMAC_GETETHERSTATS_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax           : Std_ReturnType Eth_17_GEthMac_GetEtherStats(const uint8 **
**                                          CtrlIdx, uint32* const etherStats)**
**                                                                            **
** Description      : Returns the ethernet status list according to           **
**                    IETF RFC2819.The maximal possible value shall denote an **
**                    invalid value, e.g. if this counter is not available:   **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x15                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx    - Index of Eth Controller within the         **
**                                 context of the Ethernet driver.            **
**                                                                            **
**                                                                            **
** Parameters (out) : etherStats - List of values according to IETF RFC       **
**                                 2819 (Remote Network Monitoring Management **
**                                       Information Base)                    **
**                                                                            **
** Return value     : Std_ReturnType -  E_OK  : success                       **
**                                   -  E_NOT_OK : drop counter could not     **
**                                      be obtained                           **
**                                                                            **
*******************************************************************************/

extern Std_ReturnType Eth_17_GEthMac_GetEtherStats(const uint8 CtrlIdx,
                                                     uint32* const etherStats);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Eth_17_GEthMac_GetEtherStats(CtrlIdx,etherStats) \
                       (ERROR_Eth_17_GEthMac_GetEtherStats_API_IS_NOT_SELECTED)
#endif/* End for ETH_17_GETHMAC_GETETHERSTATS_API */

#if(ETH_17_GETHMAC_GLOBALTIMESUPPORT == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax           : Std_ReturnType Eth_17_GEthMac_GetCurrentTime(           **
**                              const uint8 CtrlIdx,                          **
**                              Eth_TimeStampQualType* const timeQualPtr,     **
**                              Eth_TimeStampType* const timeStampPtr)        **
**                                                                            **
** Description      : Returns a time value out of the HW registers.           **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x16                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx      -  Index of Eth Controller within the      **
**                                    context of the Ethernet driver.         **
**                                                                            **
** Parameters (out) : timeQualPtr  -  Quality of HW time stamp, e.g.          **
**                    based on current drift                                  **
**                    timeStampPtr -  current time stamp                      **
**                                                                            **
** Return value     : Std_ReturnType -  E_OK  : Success                       **
**                                   -  E_NOT_OK : Failed                     **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Eth_17_GEthMac_GetCurrentTime(const uint8 CtrlIdx,
              Eth_TimeStampQualType* const timeQualPtr, Eth_TimeStampType*
                                                      const timeStampPtr);
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax           : void Eth_17_GEthMac_EnableEgressTimeStamp               **
**                               (const uint8 CtrlIdx, const uint8 BufIdx)    **
**                                                                            **
** Description      : The function activates timestamp for the specific       **
**                    transmit frame                                          **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x17                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx       -  Index of Eth Controller within the     **
**                                     context of the Ethernet driver.        **
**                    BufIdx        -  Index of the message buffer, where     **
**                                     application expects egress             **
**                                     time stamping                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void Eth_17_GEthMac_EnableEgressTimeStamp(const uint8 CtrlIdx,
                                                       const uint8 BufIdx);
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax           : void Eth_17_GEthMac_GetEgressTimeStamp                  **
**                                 (const uint8 CtrlIdx, const uint8 BufIdx,  **
**                                  Eth_TimeStampQualType* const timeQualPtr, **
**                                  Eth_TimeStampType* const timeStampPtr)    **
**                                                                            **
** Description      : Reads back the egress time stamp on a dedicated message **
**                    object. It must be called within the TxConfirmation()   **
**                    function.                                               **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x18                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx       -  Index of Eth Controller within the     **
**                                     context of the Ethernet driver.        **
**                    BufIdx        -  Index of the message buffer, where     **
**                                     Application expects egress             **
**                                     time stamping                          **
**                                                                            **
** Parameters (out) : timeQualPtr  -  quality of HW time stamp, e.g.          **
**                                    based on current drift                  **
**                    timeStampPtr -  current time stamp                      **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void Eth_17_GEthMac_GetEgressTimeStamp(const uint8 CtrlIdx,
        const uint8 BufIdx, Eth_TimeStampQualType* const timeQualPtr,
        Eth_TimeStampType* const timeStampPtr);
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax           : void Eth_17_GEthMac_GetIngressTimeStamp                 **
**                                (const uint8 CtrlIdx,                       **
**                                 const Eth_DataType* const DataPtr,         **
**                                 Eth_TimeStampQualType* const timeQualPtr   **
**                                 Eth_TimeStampType* const timeStampPtr)     **
**                                                                            **
** Description      : Reads back the ingress time stamp on a dedicated        **
**                    message object. It must be called within the            **
**                    RxIndication() function.                                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x18                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx       -  Index of Eth Controller within the     **
**                                     context of the Ethernet driver.        **
**                    DataPtr       -  Index of the message buffer, where     **
**                                     Application expects Ingress            **
**                                     time stamping.                         **
**                                     This parameter is not used in ETH      **
**                                     driver design                          **
**                                                                            **
** Parameters (out) : timeQualPtr  -  quality of HW time stamp, e.g.          **
**                                    based on current drift                  **
**                    timeStampPtr -  current time stamp                      **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void Eth_17_GEthMac_GetIngressTimeStamp(const uint8 CtrlIdx,
                                   const Eth_DataType* const DataPtr,
                                   Eth_TimeStampQualType* const timeQualPtr,
                                   Eth_TimeStampType* const timeStampPtr);
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax           : void Eth_17_GEthMac_SetCorrectionTime(                  **
**                           const uint8 CtrlIdx,                             **
**                           const Eth_TimeIntDiffType* const timeOffsetPtr,  **
**                           const Eth_RateRatioType* const rateRatioPtr)     **
**                                                                            **
** Description      : Allows the Time Slave to adjust the local               **
**                    ETH Reference clock in HW.                              **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x1a                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx       -  Index of Eth Controller within the     **
**                                     context of the Ethernet driver.        **
**                    timeOffsetPtr -  offset between time stamp grandmaster  **
**                                     and time stamp by local clock:         **
**                                     (OriginTimeStampSync -                 **
**                                     IngressTimeStampSync) + Pdelay         **
**                    rateRatioPtr  -  time elements to calculate and to      **
**                                     modify the ratio of the frequency      **
**                                     of the grandmaster in relation to      **
**                                     the frequency of the Local Clock       **
**                                     with: ratio = OriginTimeStampDelta     **
**                                     / IngressTimeStampDelta                **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void Eth_17_GEthMac_SetCorrectionTime( const uint8 CtrlIdx,
        const Eth_TimeIntDiffType* const timeOffsetPtr,
        const Eth_RateRatioType* const rateRatioPtr );
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax           : Std_ReturnType Eth_17_GEthMac_SetGlobalTime             **
**                              (const uint8 CtrlIdx,                         **
**                              const Eth_TimeStampType* const timeStampPtr)  **
**                                                                            **
** Description      : Allows the Time Master to adjust the global ETH         **
**                    Reference clock in HW. We can use this method to        **
**                    set a global time base on ETH in general or to          **
**                    synchronize the global ETH time base with another       **
**                    time base, e.g. FlexRay.                                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x1b                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx       -  Index of Eth Controller within the     **
**                                     context of the Ethernet driver.        **
**                    timeStampPtr  -  new time stamp                         **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Std_ReturnType - E_OK: successful                       **
**                                     E_NOT_OK: failed                       **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Eth_17_GEthMac_SetGlobalTime( const uint8 CtrlIdx,
        const Eth_TimeStampType* const timeStampPtr );
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Eth_17_GEthMac_GetCurrentTime(CtrlIdx,timeQualPtr,timeStampPtr) \
                      (ERROR_Eth_17_GEthMac_GetCurrentTime_API_IS_NOT_SELECTED)

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Eth_17_GEthMac_EnableEgressTimeStamp(CtrlIdx,BufIdx) \
               (ERROR_Eth_17_GEthMac_EnableEgressTimeStamp_API_IS_NOT_SELECTED)

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Eth_17_GEthMac_GetEgressTimeStamp(CtrlIdx,BufIdx,timeQualPtr, \
                                                        timeStampPtr) \
                 (ERROR_Eth_17_GEthMac_GetEgressTimeStamp_API_IS_NOT_SELECTED)

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Eth_17_GEthMac_GetIngressTimeStamp(CtrlIdx,DataPtr,timeQualPtr, \
                                                        timeStampPtr)\
               (ERROR_Eth_17_GEthMac_GetIngressTimeStamp_API_IS_NOT_SELECTED)

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Eth_17_GEthMac_SetCorrectionTime(CtrlIdx,timeOffsetPtr,rateRatioPtr) \
                   (ERROR_Eth_17_GEthMac_SetCorrectionTime_API_IS_NOT_SELECTED)

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Eth_17_GEthMac_SetGlobalTime(CtrlIdx,timeStampPtr) \
                      (ERROR_Eth_17_GEthMac_SetGlobalTime_API_IS_NOT_SELECTED)

#endif/* End for ETH_17_GETHMAC_GLOBALTIMESUPPORT */

#if(ETH_17_GETHMAC_VERSION_INFO_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax :          void Eth_17_GEthMac_GetVersionInfo                       **
**                             (Std_VersionInfoType * const VersionInfoPtr)   **
**                                                                            **
** Description :     This service will return the version infos of ETH driver **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       0x0D                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant                                                **
**                                                                            **
** Parameters (in):  None                                                     **
**                                                                            **
** Parameters (out): VersionInfoPtr : Pointer to hold the version values      **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
*******************************************************************************/
extern void Eth_17_GEthMac_GetVersionInfo(Std_VersionInfoType*
                                            const VersionInfoPtr);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Eth_17_GEthMac_GetVersionInfo(VersionInfoPtr) \
                      (ERROR_Eth_17_GEthMac_GetVersionInfo_API_IS_NOT_SELECTED)
#endif /* End for ETH_17_GETHMAC_VERSION_INFO_API */

#define ETH_17_GETHMAC_STOP_SEC_CODE_QM_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Eth_17_GEthMac_MemMap.h"

#include "Eth_17_GEthMac_PBcfg.h"

#endif /* ETH_17_GETHMAC_H */
