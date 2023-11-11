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
**  FILENAME     : Eth_17_GEthMac.c                                           **
**                                                                            **
**  VERSION      : 48.0.0                                                     **
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
**  DESCRIPTION  : Eth Driver source file                                     **
**                                                                            **
**  SPECIFICATION(S) : Specification of Ethernet Driver,AUTOSAR Release 4.2.2 **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/* [cover parentID={64396541-ADF7-4d33-9D4B-786C597C5036}]
[/cover] */
/* [cover parentID={BD607180-6DDB-4175-9E75-6DCCAEBFBD5C}]
[/cover] */
/* [cover parentID={2A39EC90-23ED-4bbc-AABC-1AD846380145}]
[/cover] */
/* [cover parentID={781260A6-01AA-46e5-82B8-ADEA8BA4A533}]
[/cover] */
/* [cover parentID={5B8615B5-0D0D-4200-A852-810FCCDE7E3C}]
[/cover] */
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
[/cover] */
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
[/cover] */
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
[/cover] */
/* [cover parentID={3257A55C-7BD8-4acc-9DD6-3DE87A3873A2}]
[/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
MemMap
[/cover] */
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
Callout Memory section not used in ETH driver
[/cover]*/
/*******************************************************************************
**                      Includes                                             **
*******************************************************************************/
/* Inclusion of ETH header file, this includes ETH configuration file also */
#include "Eth_17_GEthMac.h"
/* Inclusion of GETH MAC Register file */
#include "IfxGeth_reg.h"
#include "IfxGeth_bf.h"
/* Inclusion of SchM header file */
#include "SchM_Eth_17_GEthMac.h"
/* Inclusion of Mcal Specific Global Header File */
#include "McalLib.h"

#if((ETH_17_GETHMAC_INIT_API_MODE != ETH_17_GETHMAC_MCAL_SUPERVISOR)||\
    (ETH_17_GETHMAC_RUNTIME_API_MODE != ETH_17_GETHMAC_MCAL_SUPERVISOR))
#include "McalLib_OsStub.h"
#endif

/* Conditional Inclusion of Development Error Tracer File */
#if (ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif /* (ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON) */

/* Inclusion of EthIf and EthTrcv header file */
#include "EthIf_Cbk.h"
#include "EthTrcv_Cbk.h"

/*******************************************************************************
**                      Imported Compiler Switch Checks                       **
*******************************************************************************/
/* ETH Header File Version Check */
#ifndef ETH_17_GETHMAC_SW_MAJOR_VERSION
  #error "ETH_17_GETHMAC_SW_MAJOR_VERSION is not defined. "
#endif

#ifndef ETH_17_GETHMAC_SW_MINOR_VERSION
  #error "ETH_17_GETHMAC_SW_MINOR_VERSION is not defined. "
#endif

#ifndef ETH_17_GETHMAC_SW_PATCH_VERSION
  #error "ETH_17_GETHMAC_SW_PATCH_VERSION is not defined. "
#endif

/* AUTOSAR Secification File Version Check */
#ifndef ETH_17_GETHMAC_AR_RELEASE_MAJOR_VERSION
  #error "ETH_17_GETHMAC_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif
  /* [cover parentID={43D08B7F-389B-4d43-88F1-BE673A9F9773}]
  Version check across files of Ethernet module
  [/cover] */
#if (ETH_17_GETHMAC_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION)
  #error "ETH_17_GETHMAC_AR_RELEASE_MAJOR_VERSION does not match. "
#endif

#if (ETH_17_GETHMAC_AR_RELEASE_MINOR_VERSION != MCAL_AR_RELEASE_MINOR_VERSION)
  #error "ETH_17_GETHMAC_AR_RELEASE_MINOR_VERSION does not match. "
#endif

#if (ETH_17_GETHMAC_SW_MAJOR_VERSION != 20U)
  #error "ETH_17_GETHMAC_SW_MAJOR_VERSION does not match. "
#endif

#if (ETH_17_GETHMAC_SW_MINOR_VERSION != 25U)
  #error "ETH_17_GETHMAC_SW_MINOR_VERSION does not match. "
#endif

#if (ETH_17_GETHMAC_SW_PATCH_VERSION != 0U)
  #error "ETH_17_GETHMAC_SW_PATCH_VERSION does not match."
#endif

  /* [cover parentID={CB709481-57CF-4f90-961E-F9B6BC9F7E2B}]
  Inter module consistency checks
  [/cover] */
  /*
  VERSION CHECK FOR DET MODULE INCLUSION
  */
#if (ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)

#ifndef DET_AR_RELEASE_MAJOR_VERSION
  #error "DET_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

#if ( DET_AR_RELEASE_MAJOR_VERSION != 4U )
  #error "DET_AR_RELEASE_MAJOR_VERSION does not match. "
#endif

#endif/* End Of ETH_17_GETHMAC_DEV_ERROR_DETECT */


/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
#if(ETH_17_GETHMAC_GLOBALTIMESUPPORT == STD_ON)
/* Macro to mask Nanosecond Update from register*/
#define ETH_17_GETHMAC_NANOSEC_UPDATE_MASK    (0x7FFFFFFFU)
#endif

#if(ETH_17_GETHMAC_GETDROPCOUNT_API == STD_ON)
/* Maximum number of drop counts from API  */
#define ETH_17_GETHMAC_MAX_DROP_COUNTER_NUM   (14U)
#endif

#if((ETH_17_GETHMAC_GETETHERSTATS_API == STD_ON) || \
   (ETH_17_GETHMAC_GETDROPCOUNT_API == STD_ON))
/* To indicate that drop count or Ether status is not available. */
#define ETH_17_GETHMAC_COUNTER_NOT_AVAILABLE  (0xFFFFFFFFU)
#endif

#if(ETH_17_GETHMAC_GLOBALTIMESUPPORT == STD_ON)
/* Number of microseconds increments per clock or overflow */
#define ETH_17_GETHMAC_SUB_SEC_INCREMENT_VAL (20U)
#endif

/* Macro to mask and get position of Missed and Overflow packet
   count from and from register*/
#define ETH_17_GETHMAC_MISPKTCNT_MASK        (0x0FFF0000U)
#define ETH_17_GETHMAC_MISPKTCNT_POSITION    (16U)
#define ETH_17_GETHMAC_OVFPKTCNT_MASK        (0x00000FFFU)

/*Used to enable the ETH module, GETH_CLC.B.DISR = ETH_17_GETHMAC_MOD_ENABLE. */
#define ETH_17_GETHMAC_MOD_ENABLE            (0U)
/* To indicate that, valid time stamp is not available for the packet. */
#define ETH_17_GETHMAC_TIMESTAMP_NA          (0xFFU)

#if(ETH_17_GETHMAC_GLOBALTIMESUPPORT == STD_ON)
/* To check if the time stamp value provided by hardware is corrupted. */
#define ETH_17_GETHMAC_INGRESS_TS_CORRUPT    (0xFFFFFFFFU)
#endif

/* Ethernet frame's Header field length. */
#define ETH_17_GETHMAC_FRAMEHEADER_LENGTH    (14U)
/* Ethernet frame's checksum field length. */
#define ETH_17_GETHMAC_FRAMECHKSUM_LENGTH    (4U)

/* Macros to Mask Interrupts which are enabled in default. */
#define ETH_17_GETHMAC_DISABLE_MMC_TX_INTPT      (0x0FFFFFFFU)
#define ETH_17_GETHMAC_DISABLE_MMC_RX_INTPT      (0x0FFFFFFFU)
#define ETH_17_GETHMAC_DISABLE_MMC_IPC_RX_INTPT  (0x3FFF3FFFU)

/* Macro to Enable Address filtering in Mac Address register. */
#define ETH_17_GETHMAC_MACADDRRESS_ENABLE        (0x80000000U)

#define ETH_17_GETHMAC_BUFFER_NOTUSED            (0U)
#define ETH_17_GETHMAC_BUFFER_USED               (1U)

/* Macro for MAC address length. */
#define ETH_17_GETHMAC_MACADDRESS_LEN            (6U)

  /* Macro for max number of Tx and Rx pending interrupt check loops in ISR. */
  #define ETH_17_GETHMAC_TXRX_INT_PENDG_MAXLOOPCNT  (5U)

/* Macro for default value to load in MAC Address register 0 to 31. */
#define ETH_17_GETHMAC_FILT0_DEF_HIGH_VAL        (0x8000FFFFU)
#define ETH_17_GETHMAC_FILT0_DEF_LOW_VAL         (0xFFFFFFFFU)
#define ETH_17_GETHMAC_FILT_1_31_DEF_HIGH_VAL    (0x0000FFFFU)
#define ETH_17_GETHMAC_FILT_1_31_DEF_LOW_VAL     (0xFFFFFFFFU)

/* Number of Hardware MAC address filter registers available. */
#define ETH_17_GETHMAC_NO_OF_FILTER_REGISTERS    (32U)

#if (ETH_17_GETHMAC_UPDATE_PHY_ADDR_FILTER_API == STD_ON)
#define ETH_17_GETHMAC_INVALID_FILTER_VALUE      (0xFFU)
#endif

/* Macros for Ethernet Frame fields. */
#define ETH_17_GETHMAC_FRAME_DESTADDR_POS        (0U)
#define ETH_17_GETHMAC_FRAME_SRCADDR_POS         (6U)
#define ETH_17_GETHMAC_FRAME_TYPE_POS_MSB        (12U)
#define ETH_17_GETHMAC_FRAME_TYPE_POS_LSB        (13U)
#define ETH_17_GETHMAC_FRAME_PAYLOAD_POS         (14U)

#if ((ETH_17_GETHMAC_IPV4_CHECKSUMOFFLOAD_ENABLE == STD_ON) || \
     (ETH_17_GETHMAC_TCP_CHECKSUMOFFLOAD_ENABLE  == STD_ON) || \
     (ETH_17_GETHMAC_UDP_CHECKSUMOFFLOAD_ENABLE  == STD_ON) || \
     (ETH_17_GETHMAC_ICMP_CHECKSUMOFFLOAD_ENABLE == STD_ON))
#define ETH_17_GETHMAC_IPV4_ICMP_PROTOCOL        (0x01U)
#define ETH_17_GETHMAC_IPV4_FRAMETYPE            (0x0800U)
#define ETH_17_GETHMAC_FRAME_ICMP_CRC_POS        (36U)
#define ETH_17_GETHMAC_FRAME_IPV4TYPE_POS        (23U)

/* Macro to enable the MAC checksum offload */
#define ETH_17_GETHMAC_MAC_CHKSM_OFFLD_ENBL      (0x08000000U)
#endif

/* Macro to Mask Buffer 1 Length field in Tx-Descriptro-TDES2(Bit 0 to 13) */
#define ETH_17_GETHMAC_MASK_TDES2_BUF1LENGTH     (0xFFFFC000U)

/* Macros used for number of bits shifts and Byte Mask. */
#define ETH_17_GETHMAC_SHIFT_8BIT                (8U)
#define ETH_17_GETHMAC_SHIFT_16BIT               (16U)
#define ETH_17_GETHMAC_SHIFT_24BIT               (24U)
#define ETH_17_GETHMAC_BYTE0_MASK                (0x000000FFU)
#define ETH_17_GETHMAC_BYTE_MASK                 (0xFFU)

#if (ETH_17_GETHMAC_UPDATE_PHY_ADDR_FILTER_API == STD_ON)
#define ETH_17_GETHMAC_MASK_LSB                  (0x00FFU)
#endif

#if ( ETH_17_GETHMAC_GLOBALTIMESUPPORT == STD_ON)
/* 50MHz represented in Hz*/
#define ETH_17_GETHMAC_50MHZ                     (50000000U)
/* Value - (2^32) - 1 */
#define ETH_17_GETHMAC_32BITMAX                  (0xFFFFFFFFU)
/* Value of One second in Nano seconds - That is 10^9 */
#define ETH_17_GETHMAC_ONE_SEC_TO_NANOSEC        (1000000000U)
/* Value - 2^32 */
#define ETH_17_GETHMAC_TWO_POW_32_VAL            (4294967296U)

/* Enable timestamp for Tx and Rx  */
#define ETH_17_GETHMAC_TS_ENABLE                 (0x01U)
#endif

/* Macro to represent Duplex modes. */
#define ETH_17_GETHMAC_FULL_DUPLEX               (1U)
#define ETH_17_GETHMAC_HALF_DUPLEX               (0U)

/* Macro for Numbers. */
#define ETH_17_GETHMAC_ZERO                      (0U)
#define ETH_17_GETHMAC_ONE                       (1U)
#define ETH_17_GETHMAC_TWO                       (2U)
#define ETH_17_GETHMAC_THREE                     (3U)
#define ETH_17_GETHMAC_FOUR                      (4U)
#define ETH_17_GETHMAC_SEVEN                     (7U)

#define ETH_17_GETHMAC_GPTCL_PHY_POS             (22U)
#define ETH_17_GETHMAC_PHYINT_POS                (2U)
#define ETH_17_GETHMAC_OPMODE_POS                (5U)
#define ETH_17_GETHMAC_OPMODE_MSK                (1U)
#define ETH_17_GETHMAC_TXINT_POS                 (6U)
#define ETH_17_GETHMAC_TXRXINT_POS               (6U)
#define ETH_17_GETHMAC_RXINT_POS                 (7U)
#define ETH_17_GETHMAC_CRCS_POS                  (8U)
#define ETH_17_GETHMAC_TXSKEW_MASK               (0x0FU)
#define ETH_17_GETHMAC_RXSKEW_MASK               (0xF0U)
#define ETH_17_GETHMAC_FES_POS                   (1U)

/* Macro for Maximum STM tick for overflow to happen. */
#define ETH_17_GETHMAC_STM_TICK_OVERFLOW         (0xFFFFFFFFU)

/* Macro for RBSZ_13_y bit-field that indicates the buffer size*/
#define ETH_17_GETHMAC_RBSZ_13_Y                 (2U)

/* Macros for core init / deinit state */
#define ETH_17_GETHMAC_CORE_UNINIT               (0x0U)
#define ETH_17_GETHMAC_CORE_INIT                 (0x1U)

/* Macro to disable the MAC Transmission and Reception */
#define ETH_17_GETHMAC_MAC_TXRX_DISABLEMASK      (0xFFFFFFFCU)

/* Macro to enable the MAC Transmission and Reception */
#define ETH_17_GETHMAC_MAC_TXRX_ENABLEMASK       (0x00000003U)

#if (ETH_17_GETHMAC_GLOBALTIMESUPPORT == STD_ON)
/* Macro to add in epsilon value to remove Tasking compiler warning TCVX-44339*/
#define ETH_17_GETHMAC_EPSILON_FLOAT_VALUE       ((float64)0.000000001)
#endif

/*******************************************************************************
**                         User Mode Macros                                   **
*******************************************************************************/

  /* [cover parentID={1A65EADD-AFD0-4845-B2D2-8257E086DD67}]
  [/cover] */
/* User and Supervisory mode related macros for Intialization API */
#if ETH_17_GETHMAC_INIT_API_MODE  == ETH_17_GETHMAC_MCAL_SUPERVISOR
  /* Library APIs  */
  /* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
   *'ETH_17_GETHMAC_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG'
   *defined for User mode support in code.
   *No side effects foreseen by violating this MISRA rule. */
  #define ETH_17_GETHMAC_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG(RegAdd,Data) \
                                      Mcal_WritePeripEndInitProtReg(RegAdd,Data)
  /* Supervisory mode registers */
  /* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
   *'ETH_17_GETHMAC_SFR_INIT_DEINIT_WRITE32'
   *defined for User mode support in code.
   *No side effects foreseen by violating this MISRA rule. */
  #define  ETH_17_GETHMAC_SFR_INIT_DEINIT_WRITE32(reg,value) \
                                                 ((*(reg)) = (uint32)(value))
#else

  /* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
   *'ETH_17_GETHMAC_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG'
   *defined for User mode support in code.
   *No side effects foreseen by violating this MISRA rule. */
  #define ETH_17_GETHMAC_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG(RegAdd,Data) \
                              MCAL_LIB_WRITEPERIPENDINITPROTREG(RegAdd,Data)

  /* Supervisory mode registers */
  /* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
   *'ETH_17_GETHMAC_SFR_INIT_DEINIT_WRITE32'
   *defined for User mode support in code.
   *No side effects foreseen by violating this MISRA rule. */
  #define  ETH_17_GETHMAC_SFR_INIT_DEINIT_WRITE32(reg,value) \
                  MCAL_SFR_OS_WRITE32(ETH_17_GETHMAC_MODULE_ID,reg,value)
#endif

/* To configure TX/RX Clock delay for skew timing, in RGMII mode,*/
/*User and Supervisory mode related macros for Run time APIs */
#if ETH_17_GETHMAC_RUNTIME_API_MODE  == ETH_17_GETHMAC_MCAL_SUPERVISOR

  /* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
   *'ETH_17_GETHMAC_LIB_RUNTIME_WRITEPERIPENDINITPROTREG'
   *defined for supervisor/ User mode support in code.
   *No side effects foreseen by violating this MISRA rule. */
  #define ETH_17_GETHMAC_LIB_RUNTIME_WRITEPERIPENDINITPROTREG(RegAdd,Data) \
                                     Mcal_WritePeripEndInitProtReg(RegAdd,Data)

  /* Supervisory mode registers */
  /* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
   * 'ETH_17_GETHMAC_SFR_RUNTIME_WRITE32'
   * defined for User mode support in code.
   * No side effects foreseen by violating this MISRA rule. */
  #define  ETH_17_GETHMAC_SFR_RUNTIME_WRITE32(reg,value) \
                                  ((*(reg)) = (uint32)(value))
#else

  /* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
   *'ETH_17_GETHMAC_LIB_RUNTIME_WRITEPERIPENDINITPROTREG'
   *defined for supervisor/ User mode support in code.
   *No side effects foreseen by violating this MISRA rule. */
  #define ETH_17_GETHMAC_LIB_RUNTIME_WRITEPERIPENDINITPROTREG(RegAdd,Data) \
                              MCAL_LIB_WRITEPERIPENDINITPROTREG(RegAdd,Data)

  /* Supervisory mode registers */
  /* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
   * 'ETH_17_GETHMAC_SFR_RUNTIME_WRITE32'
   * defined for User mode support in code.
   * No side effects foreseen by violating this MISRA rule. */
  #define  ETH_17_GETHMAC_SFR_RUNTIME_WRITE32(reg,value) \
                   MCAL_SFR_OS_WRITE32(ETH_17_GETHMAC_MODULE_ID,reg,value)
#endif

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/
/* Data Type for Controller Initialization Status */
/* [cover parentID={3D371C73-6A1F-4b28-9AE4-D8AFF6E6F282}]
[/cover] */
typedef enum
{
  ETH_17_GETHMAC_CNTRL_NOT_INITIALIZED  = 0x0U,
  ETH_17_GETHMAC_CNTRL_INITIALIZED      = 0x1U
}Eth_17_GEthMac_CntrlConfigStatusType;

/* Structure for Trasmit buffer table,
   contains Tx status of each Tx buffer index. */
/* BuffLengthReqstd - Buffer length requested by the application */
/* BuffStatus - Buffer status free or used(0 means free, 1 means used)*/
/* Whether Tx confirmation requested or not(0 means confirmation not needed)*/
/* Whether frame transmission initiated or not(0 means not initiated)*/
/* [cover parentID={0260E1A0-15D6-4e70-9488-B80D97A4D815}]
  [/cover] */
typedef struct
{
  uint16 BuffLengthReqstd;
  uint8  BuffStatus;
  uint8  TxConfirmReq;
  uint8  FrameTxInitiated;
}Eth_17_GEthMac_TxBuffTableType;

/* Structure for Transmit Descriptor*/
/*** Read Format  - Read by DMA and Written by software  ***/
/*Tx Descriptor 0 - Buffer 1 address */
/*Tx Descriptor 1 - Buffer 2 Address */
/*Tx Descriptor 2 - IOC,TTSE,Buffer 1 and Buffer 2 Length*/
/*Tx Descriptor 3 - OWN,CTXT,FD,LD,CPC,CIC,TPL */

/*** Write Format - Written by DMA controller and Read by software ***/
/*Tx Descriptor 0 - Transmit Packet's Timestamp Low */
/*Tx Descriptor 1 - Transmit Packet's Timestamp High */
/*Tx Descriptor 2 - Reserved */
/*Tx Descriptor 3 - OWN,CTXT,FD,LD,Tx Timestamp Status */
/* [cover parentID={67A66C3D-26A7-4fcb-A910-91AD06E7E5D7}]
  [/cover] */
typedef struct
{
  volatile uint32 TDES0;
  volatile uint32 TDES1;
  volatile uint32 TDES2;
  volatile uint32 TDES3;
}Eth_17_GEthMac_DmaTxDescType;

/* Structure for Receive Descriptor*/
/*** Read Format  - Read by DMA and Written by software  ***/
/*Rx Descriptor 0 - Buffer 1 address */
/*Rx Descriptor 1 - Reserved */
/*Rx Descriptor 2 - Buffer 2 address */
/*Rx Descriptor 3 - OWN,IOC,Buffer1 valid and Buffer2 valid */

/*** Write Format - Written by DMA controller and Read by software ***/
/*Rx Descriptor 0 - IVT,OVT (VLAN)*/
/*Rx Descriptor 1 - Timestamp Dropped,Timestamp Available etc..*/
/*Rx Descriptor 2 - L3L4FM,L4FM etc.. */
/*Rx Descriptor 3 - OWN,CTXT,FD,LD,Length/Type,Packet Length(PL)*/

/*** Context Descriptor - Written by DMA controller and Read by software ***/
/*Rx Descriptor 0 - Receive Packet's Timestamp Low */
/*Rx Descriptor 1 - Receive Packet's Timestamp High */
/*Rx Descriptor 2 - Reserved */
/*Rx Descriptor 3 - OWN,CTXT */
/* [cover parentID={1697BFBE-4BCA-4221-9588-5CEA31723E3F}]
  [/cover] */
typedef struct
{
  volatile uint32 RDES0;
  volatile uint32 RDES1;
  volatile uint32 RDES2;
  volatile uint32 RDES3;
}Eth_17_GEthMac_DmaRxDescType;

/* Structure for MAC Address registers 1 to 31, HIGH and LOW */
/* [cover parentID={E7308961-0448-45f8-8FBC-ADB6295E5541}]
[/cover] */
typedef volatile struct
{
  Ifx_GETH_MAC_ADDRESS_HIGH AddrHigh;
  Ifx_GETH_MAC_ADDRESS_LOW  AddrLow;
}Eth_17_GEthMac_MacAddr_1_31Type;

/* Structure to hold run-time operational data of ETH Controller*/
/* [cover parentID={4DD1FB0F-B98E-464b-B81B-3262F08494EE}]
[/cover] */
typedef struct
{
#if(ETH_17_GETHMAC_GLOBALTIMESUPPORT == STD_ON)
  /* Frequency compensation value which is loaded last time in Time
  ADDEND register. */
   float64 EthPrevFreqCompensationValue0;
#endif
  /* To store current Controller mode */
  Eth_ModeType EthControllerMode;
  /* To store previous controller mode */
  Eth_ModeType PrevEthControllerMode;
  /* Controller Initialization status */
  Eth_17_GEthMac_CntrlConfigStatusType CntrlConfigStatus;
  /* Rx index used for storing currently scanning Rx-DMA descriptor. */
  uint8 CurrRxDmaDescIdx;
  /* Rx-DMA descriptor index where Ingress Timestamp has to be read. */
  uint8 RxDmaDesIdxForIngTimStamp;
  /* Tx index used for storing currently scanning Tx-DMA descriptor & Tx Table*/
  uint8 CurrTxIdx;
  /* Tx index used for storing Buffer idx for Tx confirmation. */
  uint8 ConfirmTxBufIdx;
  /* To store status of Address filter, is open or not*/
  boolean AddressFilterOpenStat;
  /* To store controller's unique unicast MAC address */
  uint8 EthUnicastMacAddress[6];
}Eth_17_GEthMac_RunTimeOpertnDataType;

/*Structure for DemReportedCount*/
/* [cover parentID={4FBB521B-FDD4-4685-A4AD-6D46FA2977B7}]
  [/cover] */
typedef struct
{
  uint32 Count;
  uint32 DemReportedCount;

}Eth_17_GEthMac_StatsCounterDemReportStatType;

/*Structure to record statistics count on undersize, oversize, CRC, alignment
failures and collision errors */
/* [cover parentID={5C3D11B2-0E89-41fb-96AC-767E5AB70B2B}]
  [/cover] */
typedef struct
{
  Eth_17_GEthMac_StatsCounterDemReportStatType CRCErrorFrameCounter;
  Eth_17_GEthMac_StatsCounterDemReportStatType UnderSizeFrameCounter;
  Eth_17_GEthMac_StatsCounterDemReportStatType OverSizeFrameCounter;
  Eth_17_GEthMac_StatsCounterDemReportStatType AlignmentErrorFrameCounter;
  Eth_17_GEthMac_StatsCounterDemReportStatType SingleCollisionCounter;
  Eth_17_GEthMac_StatsCounterDemReportStatType MultipleCollisionCounter;
  Eth_17_GEthMac_StatsCounterDemReportStatType LateCollisionCounter;
} Eth_17_GEthMac_StatisticsCounterType;

/* [cover parentID={EEDCCD72-C38E-4d67-8C77-1BA6D5756F21}]
  [/cover] */
typedef struct
{
  /* Pointer to Ethernet Tx Buffer table contains Tx status of each Tx buffer */
  Eth_17_GEthMac_TxBuffTableType *EthTxBuffTablePtr;
  /* Pointer to Transmit Descriptors list. One descriptor for each Tx Buffer. */
  Eth_17_GEthMac_DmaTxDescType *EthDmaTxDescPtr;
  /* Pointer to receive Descriptors list. One descriptor for each Rx Buffer. */
  Eth_17_GEthMac_DmaRxDescType *EthDmaRxDescPtr;
  /* Pointer to Rx Buffer*/
  uint8 *EthRxBufferPtr;
  /* Pointer to Tx Buffer*/
  uint8 *EthTxBufferPtr;
}Eth_17_GEthMac_BuffDescType;

/* [cover parentID={3630A958-AE6D-49f2-8DA1-B1A8BDA23BB8}]
  [/cover] */
typedef struct
{
  /* Variable to hold run-time operational data of ETH driver*/
  Eth_17_GEthMac_RunTimeOpertnDataType EthRunTimeOpertnData;
  /* Data structure to store statitics counter values. */
  Eth_17_GEthMac_StatisticsCounterType EthStatisticsCounters;
  /* Pointer to Buffers and Descriptors for the current controller */
  Eth_17_GEthMac_BuffDescType* EthBuffDecPtr;
}Eth_17_GEthMac_CntrlStatusType;
/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
#if (ETH_17_GETHMAC_MAX_CNTRL_CORE0 != 0xFFU)
#if (ETH_17_GETHMAC_MAX_CNTRL_CORE0 != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_CLEARED_QM_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"
/* Global variable to store status of the controller(s) allocated to core0*/
static Eth_17_GEthMac_CntrlStatusType \
                          Eth_CntrlStatusCore0[ETH_17_GETHMAC_MAX_CNTRL_CORE0];
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_CLEARED_QM_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_CLEARED_QM_CORE0_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"
/* Global variable to store initialization status of core0*/
static uint32 Eth_CoreInitStatusCore0;
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_CLEARED_QM_CORE0_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"
#endif
#endif

#if (ETH_17_GETHMAC_MAX_CNTRL_CORE1 != 0xFFU)
#if (ETH_17_GETHMAC_MAX_CNTRL_CORE1 != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_CLEARED_QM_CORE1_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"
/* Global variable to store status of the controller(s) allocated to core1 */
static Eth_17_GEthMac_CntrlStatusType \
                          Eth_CntrlStatusCore1[ETH_17_GETHMAC_MAX_CNTRL_CORE1];
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_CLEARED_QM_CORE1_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_CLEARED_QM_CORE1_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"
/* Global variable to store initialization status of core1 */
static uint32 Eth_CoreInitStatusCore1;
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_CLEARED_QM_CORE1_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"
#endif
#endif

#if (ETH_17_GETHMAC_MAX_CNTRL_CORE2 != 0xFFU)
#if (ETH_17_GETHMAC_MAX_CNTRL_CORE2 != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_CLEARED_QM_CORE2_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"
/* Global variable to store status of the controller(s) allocated to core2 */
static Eth_17_GEthMac_CntrlStatusType \
                          Eth_CntrlStatusCore2[ETH_17_GETHMAC_MAX_CNTRL_CORE2];
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_CLEARED_QM_CORE2_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_CLEARED_QM_CORE2_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"
/* Global variable to store initialization status of core2 */
static uint32 Eth_CoreInitStatusCore2;
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_CLEARED_QM_CORE2_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"
#endif
#endif

#if (ETH_17_GETHMAC_MAX_CNTRL_CORE3 != 0xFFU)
#if (ETH_17_GETHMAC_MAX_CNTRL_CORE3 != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_CLEARED_QM_CORE3_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"
/* Global variable to store status of the controller(s) allocated to core3 */
static Eth_17_GEthMac_CntrlStatusType \
                          Eth_CntrlStatusCore3[ETH_17_GETHMAC_MAX_CNTRL_CORE3];
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_CLEARED_QM_CORE3_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_CLEARED_QM_CORE3_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"
/* Global variable to store initialization status of core3 */
static uint32 Eth_CoreInitStatusCore3;
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_CLEARED_QM_CORE3_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"
#endif
#endif

#if (ETH_17_GETHMAC_MAX_CNTRL_CORE4 != 0xFFU)
#if (ETH_17_GETHMAC_MAX_CNTRL_CORE4 != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_CLEARED_QM_CORE4_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"
/* Global variable to store status of the controller(s) allocated to core4 */
static Eth_17_GEthMac_CntrlStatusType \
                          Eth_CntrlStatusCore4[ETH_17_GETHMAC_MAX_CNTRL_CORE4];
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_CLEARED_QM_CORE4_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_CLEARED_QM_CORE4_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"
/* Global variable to store initialization status of core4 */
static uint32 Eth_CoreInitStatusCore4;
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_CLEARED_QM_CORE4_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"
#endif
#endif


#if (ETH_17_GETHMAC_MAX_CNTRL_CORE5 != 0xFFU)
#if (ETH_17_GETHMAC_MAX_CNTRL_CORE5 != 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_CLEARED_QM_CORE5_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"
/* Global variable to store status of the controller(s) allocated to core5 */
static Eth_17_GEthMac_CntrlStatusType \
                          Eth_CntrlStatusCore5[ETH_17_GETHMAC_MAX_CNTRL_CORE5];
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_CLEARED_QM_CORE5_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_CLEARED_QM_CORE5_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"
/* Global variable to store initialization status of core5 */
static uint32 Eth_CoreInitStatusCore5;
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_CLEARED_QM_CORE5_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"
#endif
#endif

#ifdef ETH_17_GETHMAC_CNTRL0_CONFIGURED
#if defined ETH_17_GETHMAC_CNTRL0_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_TXBUFFER_CLEARED_QM_CORE0_32
#elif defined ETH_17_GETHMAC_CNTRL0_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_TXBUFFER_CLEARED_QM_CORE1_32
#elif defined ETH_17_GETHMAC_CNTRL0_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_TXBUFFER_CLEARED_QM_CORE2_32
#elif defined ETH_17_GETHMAC_CNTRL0_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_TXBUFFER_CLEARED_QM_CORE3_32
#elif defined ETH_17_GETHMAC_CNTRL0_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_TXBUFFER_CLEARED_QM_CORE4_32
#elif defined ETH_17_GETHMAC_CNTRL0_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_TXBUFFER_CLEARED_QM_CORE5_32
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"
/* Global variable to store Tx buffer status for controller 0 */
static Eth_17_GEthMac_TxBuffTableType \
                   Eth_TxBuffTableCntrl0[ETH_17_GETHMAC_CNTRL0_TXBUFFER_COUNT];
/* Global variable to store Tx Descriptor status for controller 0 */
static Eth_17_GEthMac_DmaTxDescType \
                     Eth_DmaTxDescCntrl0[ETH_17_GETHMAC_CNTRL0_TXBUFFER_COUNT];
/* Transmit buffer for controller 0 */
static uint8 Eth_TxBufferCntrl0[ETH_17_GETHMAC_CNTRL0_TXBUFFER_SIZE];

#if defined ETH_17_GETHMAC_CNTRL0_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_TXBUFFER_CLEARED_QM_CORE0_32
#elif defined ETH_17_GETHMAC_CNTRL0_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_TXBUFFER_CLEARED_QM_CORE1_32
#elif defined ETH_17_GETHMAC_CNTRL0_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_TXBUFFER_CLEARED_QM_CORE2_32
#elif defined ETH_17_GETHMAC_CNTRL0_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_TXBUFFER_CLEARED_QM_CORE3_32
#elif defined ETH_17_GETHMAC_CNTRL0_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_TXBUFFER_CLEARED_QM_CORE4_32
#elif defined ETH_17_GETHMAC_CNTRL0_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_TXBUFFER_CLEARED_QM_CORE5_32
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"

#if defined ETH_17_GETHMAC_CNTRL0_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_RXBUFFER_CLEARED_QM_CORE0_32
#elif defined ETH_17_GETHMAC_CNTRL0_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_RXBUFFER_CLEARED_QM_CORE1_32
#elif defined ETH_17_GETHMAC_CNTRL0_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_RXBUFFER_CLEARED_QM_CORE2_32
#elif defined ETH_17_GETHMAC_CNTRL0_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_RXBUFFER_CLEARED_QM_CORE3_32
#elif defined ETH_17_GETHMAC_CNTRL0_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_RXBUFFER_CLEARED_QM_CORE4_32
#elif defined ETH_17_GETHMAC_CNTRL0_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_RXBUFFER_CLEARED_QM_CORE5_32
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"
/* Global variable to store Rx Descriptor status for controller 0 */
static Eth_17_GEthMac_DmaRxDescType \
                     Eth_DmaRxDescCntrl0[ETH_17_GETHMAC_CNTRL0_RXBUFFER_COUNT];
 /* Receive buffer for controller 0 */
static uint8 Eth_RxBufferCntrl0[ETH_17_GETHMAC_CNTRL0_RXBUFFER_SIZE];

#if defined ETH_17_GETHMAC_CNTRL0_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_RXBUFFER_CLEARED_QM_CORE0_32
#elif defined ETH_17_GETHMAC_CNTRL0_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_RXBUFFER_CLEARED_QM_CORE1_32
#elif defined ETH_17_GETHMAC_CNTRL0_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_RXBUFFER_CLEARED_QM_CORE2_32
#elif defined ETH_17_GETHMAC_CNTRL0_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_RXBUFFER_CLEARED_QM_CORE3_32
#elif defined ETH_17_GETHMAC_CNTRL0_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_RXBUFFER_CLEARED_QM_CORE4_32
#elif defined ETH_17_GETHMAC_CNTRL0_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_RXBUFFER_CLEARED_QM_CORE5_32
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"

#if defined ETH_17_GETHMAC_CNTRL0_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_INIT_QM_CORE0_UNSPECIFIED
#elif defined ETH_17_GETHMAC_CNTRL0_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_INIT_QM_CORE1_UNSPECIFIED
#elif defined ETH_17_GETHMAC_CNTRL0_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_INIT_QM_CORE2_UNSPECIFIED
#elif defined ETH_17_GETHMAC_CNTRL0_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_INIT_QM_CORE3_UNSPECIFIED
#elif defined ETH_17_GETHMAC_CNTRL0_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_INIT_QM_CORE4_UNSPECIFIED
#elif defined ETH_17_GETHMAC_CNTRL0_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_INIT_QM_CORE5_UNSPECIFIED
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"
/* Variable to store starting address of Buffertable, Tx/Rx descriptors and
   Tx/Rx Buffers. (Controller0) */
static Eth_17_GEthMac_BuffDescType Eth_BuffDecCntrl0 =
{
  Eth_TxBuffTableCntrl0,
  Eth_DmaTxDescCntrl0,
  Eth_DmaRxDescCntrl0,
  Eth_RxBufferCntrl0,
  Eth_TxBufferCntrl0
};
#if defined ETH_17_GETHMAC_CNTRL0_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_INIT_QM_CORE0_UNSPECIFIED
#elif defined ETH_17_GETHMAC_CNTRL0_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_INIT_QM_CORE1_UNSPECIFIED
#elif defined ETH_17_GETHMAC_CNTRL0_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_INIT_QM_CORE2_UNSPECIFIED
#elif defined ETH_17_GETHMAC_CNTRL0_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_INIT_QM_CORE3_UNSPECIFIED
#elif defined ETH_17_GETHMAC_CNTRL0_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_INIT_QM_CORE4_UNSPECIFIED
#elif defined ETH_17_GETHMAC_CNTRL0_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_INIT_QM_CORE5_UNSPECIFIED
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"
#endif /*ETH_17_GETHMAC_CNTRL0_CONFIGURED*/

#ifdef ETH_17_GETHMAC_CNTRL1_CONFIGURED
#if defined ETH_17_GETHMAC_CNTRL1_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_TXBUFFER_CLEARED_QM_CORE0_32
#elif defined ETH_17_GETHMAC_CNTRL1_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_TXBUFFER_CLEARED_QM_CORE1_32
#elif defined ETH_17_GETHMAC_CNTRL1_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_TXBUFFER_CLEARED_QM_CORE2_32
#elif defined ETH_17_GETHMAC_CNTRL1_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_TXBUFFER_CLEARED_QM_CORE3_32
#elif defined ETH_17_GETHMAC_CNTRL1_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_TXBUFFER_CLEARED_QM_CORE4_32
#elif defined ETH_17_GETHMAC_CNTRL1_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_TXBUFFER_CLEARED_QM_CORE5_32
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"
/* Global variable to store Tx buffer status for controller 1 */
/*[cover parentID={3993FC8A-2CBC-4eec-BFBD-70A415CEDD3C}]
[/cover]*/
/*[cover parentID={6FB77BAA-D705-41dc-B4B5-FFFABA7846F3}]
[/cover]*/
/*[cover parentID={6FB77BAA-D705-41dc-B4B5-FFFABA7846F3}]
[/cover]*/
static Eth_17_GEthMac_TxBuffTableType \
                   Eth_TxBuffTableCntrl1[ETH_17_GETHMAC_CNTRL1_TXBUFFER_COUNT];
/* Global variable to store Tx Descriptor status for controller 1 */
static Eth_17_GEthMac_DmaTxDescType \
                     Eth_DmaTxDescCntrl1[ETH_17_GETHMAC_CNTRL1_TXBUFFER_COUNT];
/* Transmit buffer for controller 1 */
static uint8 Eth_TxBufferCntrl1[ETH_17_GETHMAC_CNTRL1_TXBUFFER_SIZE];

#if defined ETH_17_GETHMAC_CNTRL1_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_TXBUFFER_CLEARED_QM_CORE0_32
#elif defined ETH_17_GETHMAC_CNTRL1_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_TXBUFFER_CLEARED_QM_CORE1_32
#elif defined ETH_17_GETHMAC_CNTRL1_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_TXBUFFER_CLEARED_QM_CORE2_32
#elif defined ETH_17_GETHMAC_CNTRL1_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_TXBUFFER_CLEARED_QM_CORE3_32
#elif defined ETH_17_GETHMAC_CNTRL1_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_TXBUFFER_CLEARED_QM_CORE4_32
#elif defined ETH_17_GETHMAC_CNTRL1_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_TXBUFFER_CLEARED_QM_CORE5_32
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"

#if defined ETH_17_GETHMAC_CNTRL1_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_RXBUFFER_CLEARED_QM_CORE0_32
#elif defined ETH_17_GETHMAC_CNTRL1_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_RXBUFFER_CLEARED_QM_CORE1_32
#elif defined ETH_17_GETHMAC_CNTRL1_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_RXBUFFER_CLEARED_QM_CORE2_32
#elif defined ETH_17_GETHMAC_CNTRL1_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_RXBUFFER_CLEARED_QM_CORE3_32
#elif defined ETH_17_GETHMAC_CNTRL1_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_RXBUFFER_CLEARED_QM_CORE4_32
#elif defined ETH_17_GETHMAC_CNTRL1_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_RXBUFFER_CLEARED_QM_CORE5_32
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"
/* Global variable to store Rx Descriptor status for controller 1 */
/*[cover parentID={7A8AF4C7-971A-4942-8E0E-E325242B37A7}]
[/cover]*/
/*[cover parentID={6059A6A2-960D-4900-9B07-4FA603098D83}]
[/cover]*/
static Eth_17_GEthMac_DmaRxDescType \
                     Eth_DmaRxDescCntrl1[ETH_17_GETHMAC_CNTRL1_RXBUFFER_COUNT];
/* Receive buffer for controller 1 */
static uint8 Eth_RxBufferCntrl1[ETH_17_GETHMAC_CNTRL1_RXBUFFER_SIZE];
#if defined ETH_17_GETHMAC_CNTRL1_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_RXBUFFER_CLEARED_QM_CORE0_32
#elif defined ETH_17_GETHMAC_CNTRL1_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_RXBUFFER_CLEARED_QM_CORE1_32
#elif defined ETH_17_GETHMAC_CNTRL1_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_RXBUFFER_CLEARED_QM_CORE2_32
#elif defined ETH_17_GETHMAC_CNTRL1_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_RXBUFFER_CLEARED_QM_CORE3_32
#elif defined ETH_17_GETHMAC_CNTRL1_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_RXBUFFER_CLEARED_QM_CORE4_32
#elif defined ETH_17_GETHMAC_CNTRL1_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_RXBUFFER_CLEARED_QM_CORE5_32
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"
#if defined ETH_17_GETHMAC_CNTRL1_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_INIT_QM_CORE0_UNSPECIFIED
#elif defined ETH_17_GETHMAC_CNTRL1_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_INIT_QM_CORE1_UNSPECIFIED
#elif defined ETH_17_GETHMAC_CNTRL1_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_INIT_QM_CORE2_UNSPECIFIED
#elif defined ETH_17_GETHMAC_CNTRL1_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_INIT_QM_CORE3_UNSPECIFIED
#elif defined ETH_17_GETHMAC_CNTRL1_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_INIT_QM_CORE4_UNSPECIFIED
#elif defined ETH_17_GETHMAC_CNTRL1_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_START_SEC_VAR_INIT_QM_CORE5_UNSPECIFIED
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"
/* Variable to store starting address of Buffertable, Tx/Rx descriptors and
   Tx/Rx Buffers. (Controller1) */
/* [cover parentID={6059A6A2-960D-4900-9B07-4FA603098D83}]
[/cover] */
/* [cover parentID={0B5A6D75-C348-4339-9A84-C0BC825BFDCF}]
[/cover] */
static Eth_17_GEthMac_BuffDescType Eth_BuffDecCntrl1 =
{
  Eth_TxBuffTableCntrl1,
  Eth_DmaTxDescCntrl1,
  Eth_DmaRxDescCntrl1,
  Eth_RxBufferCntrl1,
  Eth_TxBufferCntrl1
};

#if defined ETH_17_GETHMAC_CNTRL1_CORE0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_INIT_QM_CORE0_UNSPECIFIED
#elif defined ETH_17_GETHMAC_CNTRL1_CORE1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_INIT_QM_CORE1_UNSPECIFIED
#elif defined ETH_17_GETHMAC_CNTRL1_CORE2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_INIT_QM_CORE2_UNSPECIFIED
#elif defined ETH_17_GETHMAC_CNTRL1_CORE3
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_INIT_QM_CORE3_UNSPECIFIED
#elif defined ETH_17_GETHMAC_CNTRL1_CORE4
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_INIT_QM_CORE4_UNSPECIFIED
#elif defined ETH_17_GETHMAC_CNTRL1_CORE5
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_INIT_QM_CORE5_UNSPECIFIED
#endif
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"

#endif /* ETH_17_GETHMAC_CNTRL1_CONFIGURED */

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/

#define ETH_17_GETHMAC_START_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"
/* Array contains pointers to core initialization status */
static const Eth_17_GEthMac_ConfigType* Eth_ConfigSetPtr;
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMAC_STOP_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"

#define ETH_17_GETHMAC_START_SEC_CONST_QM_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"

static uint32* const Eth_17_GEthMac_CoreInitStatus[ETH_17_GETHMAC_MAX_CORES] =
{
  #if (ETH_17_GETHMAC_MAX_CNTRL_CORE0 != 0xFFU)
  #if (ETH_17_GETHMAC_MAX_CNTRL_CORE0 != 0U)
  &Eth_CoreInitStatusCore0,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (ETH_17_GETHMAC_MAX_CNTRL_CORE1 != 0xFFU)
  #if (ETH_17_GETHMAC_MAX_CNTRL_CORE1 != 0U)
  &Eth_CoreInitStatusCore1,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (ETH_17_GETHMAC_MAX_CNTRL_CORE2 != 0xFFU)
  #if (ETH_17_GETHMAC_MAX_CNTRL_CORE2 != 0U)
  &Eth_CoreInitStatusCore2,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (ETH_17_GETHMAC_MAX_CNTRL_CORE3 != 0xFFU)
  #if (ETH_17_GETHMAC_MAX_CNTRL_CORE3 != 0U)
  &Eth_CoreInitStatusCore3,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (ETH_17_GETHMAC_MAX_CNTRL_CORE4 != 0xFFU)
  #if (ETH_17_GETHMAC_MAX_CNTRL_CORE4 != 0U)
  &Eth_CoreInitStatusCore4,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (ETH_17_GETHMAC_MAX_CNTRL_CORE5 != 0xFFU)
  #if (ETH_17_GETHMAC_MAX_CNTRL_CORE5 != 0U)
  &Eth_CoreInitStatusCore5,
  #else
  NULL_PTR,
  #endif
  #endif
};
/* Array contains pointers to Controller status of the core */
static Eth_17_GEthMac_CntrlStatusType* const \
                                     Eth_CntrlStatus[ETH_17_GETHMAC_MAX_CORES]=
{
  #if (ETH_17_GETHMAC_MAX_CNTRL_CORE0 != 0xFFU)
  #if (ETH_17_GETHMAC_MAX_CNTRL_CORE0 != 0U)
  Eth_CntrlStatusCore0,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (ETH_17_GETHMAC_MAX_CNTRL_CORE1 != 0xFFU)
  #if (ETH_17_GETHMAC_MAX_CNTRL_CORE1 != 0U)
  Eth_CntrlStatusCore1,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (ETH_17_GETHMAC_MAX_CNTRL_CORE2 != 0xFFU)
  #if (ETH_17_GETHMAC_MAX_CNTRL_CORE2 != 0U)
  Eth_CntrlStatusCore2,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (ETH_17_GETHMAC_MAX_CNTRL_CORE3 != 0xFFU)
  #if (ETH_17_GETHMAC_MAX_CNTRL_CORE3 != 0U)
  Eth_CntrlStatusCore3,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (ETH_17_GETHMAC_MAX_CNTRL_CORE4 != 0xFFU)
  #if (ETH_17_GETHMAC_MAX_CNTRL_CORE4 != 0U)
  Eth_CntrlStatusCore4,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (ETH_17_GETHMAC_MAX_CNTRL_CORE5 != 0xFFU)
  #if (ETH_17_GETHMAC_MAX_CNTRL_CORE5 != 0U)
  Eth_CntrlStatusCore5,
  #else
  NULL_PTR,
  #endif
  #endif
};
/* Stores the base address of the ethernet controllers */
static Ifx_GETH* const Eth_GEthMacCntrl[ETH_17_GETHMAC_MAX_CONTROLLERS] =
{
  &MODULE_GETH,
  #if ( ETH_17_GETHMAC_MAX_CONTROLLERS > 1U )
  &MODULE_GETH1
  #endif
};
/* Array contains pointers to controller buffers/descriptors */
/* MISRA2012_RULE_8_9_JUSTIFICATION: Eth_BuffDecPtrAddr is
  initialized(copy table) with the value generated from the configuration.
  Later the global status variable is initialized with this value in init
  function, Hence the variable cannot be defined in the local scope. No side
  effects foreseen by violating this MISRA rule */
static Eth_17_GEthMac_BuffDescType * const \
                           Eth_BuffDecPtrAddr[ETH_17_GETHMAC_MAX_CONTROLLERS] =
{
#ifdef ETH_17_GETHMAC_CNTRL0_CONFIGURED
  &Eth_BuffDecCntrl0,
#else
  NULL_PTR,
#endif
#if ( ETH_17_GETHMAC_MAX_CONTROLLERS > 1U )
#ifdef ETH_17_GETHMAC_CNTRL1_CONFIGURED
  &Eth_BuffDecCntrl1
#else
  NULL_PTR
#endif
#endif
};

/*Array to hold the base of the HIGH and low registers for Dual controllers*/
/* MISRA2012_RULE_8_9_JUSTIFICATION: No side effects foreseen
 * by violating this MISRA rule, as the variable is accessed via pointer by
 * different API's. */
static volatile Ifx_GETH_MAC_ADDRESS_HIGH* const \
                           Eth_HighBaseAddress[ETH_17_GETHMAC_MAX_CONTROLLERS]=
{
#ifdef ETH_17_GETHMAC_CNTRL0_CONFIGURED
/*Base Address for MAC address register 1- High and Low for GETH*/
&(GETH_MAC_ADDRESS1_HIGH),
#else
  NULL_PTR,
#endif
#if ( ETH_17_GETHMAC_MAX_CONTROLLERS > 1U )
#ifdef ETH_17_GETHMAC_CNTRL1_CONFIGURED
/*Base Address for MAC address register 1- High and Low for GETH*/
&(GETH1_MAC_ADDRESS1_HIGH)
#else
NULL_PTR
#endif
#endif
/* MISRA2012_RULE_19_2_JUSTIFICATION:Union used for register type definition.
   No side effects foreseen by violating this MISRA rule*/
};

#define ETH_17_GETHMAC_STOP_SEC_CONST_QM_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
#include "Eth_17_GEthMac_MemMap.h"

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
/* Memory Map of the Eth Code */
#define ETH_17_GETHMAC_START_SEC_CODE_QM_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Eth_17_GEthMac_MemMap.h"

static uint32 Eth_17_lDetCheckMode(const uint8 ServiceId, const uint8 CtrlIdx);
#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
static uint32 Eth_17_lDetCheckNoInit(const uint8 ServiceId, const uint8
                                                                      CtrlIdx);
static uint32 Eth_17_lInitDetCheck( const Eth_17_GEthMac_ConfigType * const
                                             DetConfigPtr, const uint32 CoreId);
static uint32 Eth_17_lDetCheckInvalidCtrlIdx(const uint8 CtrlIdx,
                                                    const uint8 ServiceId);
static uint32 Eth_17_lDetCheckInvalidPointer(const void * const Ptr,
                                              const uint8 ServiceId);
static uint32 Eth_17_lDetCheckNoInitStage1(const uint8 ServiceId);
static uint32 Eth_17_lDetCheckInvalidMode(const Eth_ModeType CtrlMode);
#endif /*ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON*/

static boolean Eth_17_lDemtimeout(const boolean Timeout,const Dem_EventIdType
                                                                  EthDemAccess);
static void Eth_17_lDemReportStatisticsCounterValues(void);
static void Eth_17_lDemReportHalfDuplStatCountValues(const
                   Eth_17_GEthMac_CoreCntrlConfigType* const EthCntrlCfgPtr
                 ,Eth_17_GEthMac_CntrlStatusType * const EthLocalCoreStatusPtr);
static void Eth_17_lUpdateEthStatisticsCounterValues(void);
static void Eth_17_lDemReportAllErrorPass(const
                     Eth_17_GEthMac_CoreCntrlConfigType* const EthCntrlCfgPtr);
static void Eth_17_lInitGethController(const
                     Eth_17_GEthMac_CoreCntrlConfigType* const EthCntrlCfgPtr);
static Std_ReturnType Eth_17_lResetGethCore(const
                      Eth_17_GEthMac_CoreCntrlConfigType* const EthCntrlCfgPtr);
static void Eth_17_lDisableGethInterrupt(const
                     Eth_17_GEthMac_CoreCntrlConfigType* const EthCntrlCfgPtr);
static void Eth_17_lEnableGethInterrupt(const
                     Eth_17_GEthMac_CoreCntrlConfigType* const EthCntrlCfgPtr);
static void Eth_17_lGethCoreInit(const Eth_17_GEthMac_CoreCntrlConfigType*
                                                         const EthCntrlCfgPtr);
static void Eth_17_lInitGlobalVar(const Eth_17_GEthMac_CoreCntrlConfigType*
  const EthCntrlCfgPtr,Eth_17_GEthMac_CntrlStatusType* const EthCoreStatusPtr);
LOCAL_INLINE void Eth_17_lPhyIfModeSkewCfg(const
                     Eth_17_GEthMac_CoreCntrlConfigType* const EthCntrlCfgPtr);
static Std_ReturnType Eth_17_lResetDma(const uint8 CtrlIdx);
static void Eth_17_lResetTxRxStatus(const Eth_17_GEthMac_CoreCntrlConfigType*
                                                         const EthCntrlCfgPtr);
static void Eth_17_lMacCoreInit(const Eth_17_GEthMac_CoreCntrlConfigType*
                                                         const EthCntrlCfgPtr);
static void Eth_17_lClearAllAddressFilters(const uint8 CtrlIdx);
static void Eth_17_lMtlCoreInit(const uint8 CtrlIdx);
static void Eth_17_lDmaCoreInit(const Eth_17_GEthMac_CoreCntrlConfigType*
                                                         const EthCntrlCfgPtr);
static void Eth_17_lDmaTxDescriptorInit(const
                     Eth_17_GEthMac_CoreCntrlConfigType* const EthCntrlCfgPtr);
static void Eth_17_lDmaRxDescriptorInit(const
                     Eth_17_GEthMac_CoreCntrlConfigType* const EthCntrlCfgPtr);
static Eth_ModeType Eth_17_lGetMode(const uint8 CtrlIdx);
static void Eth_17_lStartTxRx(const uint8 CtrlIdx);
static void Eth_17_lStopTxRx(const uint8 CtrlIdx);
static void Eth_17_lTransmit(
             const uint8 CtrlIdx,
             const Eth_BufIdxType BufIdx, const Eth_FrameType FrameType,
             const boolean TxConfirmation, const uint16 LenByte,
             const uint8* const PhysAddrPtr);
static void Eth_17_lConfirmTxFrames (const uint8 CtrlIdx);
static uint32 Eth_17_lReceiveFrames(const uint8 CtrlIdx);
LOCAL_INLINE void Eth_17_lSetPhysAddr(const uint8* const MacAddr, const
                                                                uint8 CtrlIdx);
LOCAL_INLINE void Eth_17_lGetPhysAddr(uint8* const MacAddr, const uint8
                                                                      CtrlIdx);
LOCAL_INLINE boolean Eth_17_lIsBroadcastAddress(const uint8* const MacAddr);
LOCAL_INLINE uint8 Eth_17_lIncrTxBufIdx(const uint8 TxBufIdx, const uint8
                                                                EthTxBufTotal);
LOCAL_INLINE uint8 Eth_17_lIncrRxBufIdx (const uint8 RxBufIdx, const uint8
                                                                EthRxBufTotal);
static void Eth_17_lCheckForCtrlModeChange(Eth_17_GEthMac_CntrlStatusType
                           * const EthLocalCoreStatusPtr, const uint8 CtrlIdx);
#if (ETH_17_GETHMAC_UPDATE_PHY_ADDR_FILTER_API == STD_ON)
LOCAL_INLINE boolean Eth_17_lIsAllZeroAddress(const uint8* const MacAddr);
static Std_ReturnType Eth_17_lAddToFilter(const uint8* const MacAddr,
                                                          const uint8 CtrlIdx);
static Std_ReturnType Eth_17_lRemoveFromFilter(const uint8* const MacAddr,
                                                          const uint8 CtrlIdx);
static uint16 Eth_17_lCheckFilterPresent(const uint8* const MacAddr,
                                                          const uint8 CtrlIdx);
#endif /* End for ETH_17_GETHMAC_UPDATE_PHY_ADDR_FILTER_API*/

#if(ETH_17_GETHMAC_GLOBALTIMESUPPORT == STD_ON)
static void Eth_17_lSetCorrectionTime( const uint8 CtrlIdx,
                              const Eth_TimeIntDiffType* const timeOffsetPtr,
                              const Eth_RateRatioType* const rateRatioPtr);
static Std_ReturnType Eth_17_lSetGlobalTime( const uint8 CtrlIdx,
                                 const Eth_TimeStampType* const timeStampPtr);
static Std_ReturnType Eth_17_lTimerInit(const uint32 EthOpetnFreq,const
                     Eth_17_GEthMac_CoreCntrlConfigType* const EthCntrlCfgPtr);
static boolean Eth_17_lTsAdRegTimeout(const uint32 WaitTicks,
                                                          const uint8 CtrlIdx);
static boolean Eth_17_lTsInitTimeout(const uint32 WaitTicks,
                                                          const uint8 CtrlIdx);
static boolean Eth_17_lTsUpdtTimeout(const uint32 WaitTicks,
                                                          const uint8 CtrlIdx);
#endif /*end of ETH_17_GETHMAC_GLOBALTIMESUPPORT */

static void Eth_17_lBkToBkRegWrInsrtDly(const uint32 BkToBkDelayTime);

#if ((ETH_17_GETHMAC_IPV4_CHECKSUMOFFLOAD_ENABLE == STD_ON  ) || \
     (ETH_17_GETHMAC_TCP_CHECKSUMOFFLOAD_ENABLE  == STD_ON  ) || \
     (ETH_17_GETHMAC_UDP_CHECKSUMOFFLOAD_ENABLE  == STD_ON  ) || \
     (ETH_17_GETHMAC_ICMP_CHECKSUMOFFLOAD_ENABLE == STD_ON  ))
static void Eth_17_lCheckForICMPV4Frame(const Eth_BufIdxType BufIdx,
                                        const Eth_FrameType FrameType,
           const Eth_17_GEthMac_CntrlStatusType * const EthLocalCoreStatusPtr);
#endif
static boolean Eth_17_lIsNextFrameAvailable( const uint8 CtrlIdx);
static Eth_17_GEthMac_CntrlStatusType* Eth_17_lGetCtrlStatusPtr
                                                        ( const uint8 CtrlIdx);
static Eth_17_GEthMac_CoreCntrlConfigType* Eth_17_lGetCtrlConfigPtr
                                                        ( const uint8 CtrlIdx);
/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/

/*******************************************************************************
** Traceability    : [cover parentID={3D829D8B-4053-4d2b-9F78-19EE0D0A12E2}]  **
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
void Eth_17_GEthMac_Init(const Eth_17_GEthMac_ConfigType* const CfgPtr )
{
  uint32 RegVal;
  Std_ReturnType RetValue;
  uint32 CoreId;
  const Eth_17_GEthMac_CoreConfigType *EthLocalCoreCfgPtr;
  const Eth_17_GEthMac_CoreCntrlConfigType *EthLocalCntrlCfgPtr;
  Eth_17_GEthMac_CntrlStatusType *EthLocalCoreStatusPtr;
  uint8 ControllerIdx;
  Ifx_GETH *EthCntrlAdd;
  #if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
  #endif

  CoreId = Mcal_GetCpuIndex();
  RetValue = E_OK;
/* [cover parentID={B743E869-5A64-4756-811C-CA6198FE42A1}]
DET is Enabled
[/cover] */
#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={1BD86FC1-296D-4262-925F-094E10BE0B79}]
  If No NULL Ptr DET
  [/cover] */
  DevError = Eth_17_lInitDetCheck(CfgPtr, CoreId);
  /* [cover parentID={B743E869-5A64-4756-811C-CA6198FE42A1}]
   DET is Enabled[/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
#endif /* End of ETH_17_GETHMAC_DEV_ERROR_DETECT */
  {
    /* [cover parentID={A0E7DCAF-DD27-4fe4-936B-8F9743BBF02A}]
     Retrieve the core, controller configuration data and
     controller status of the current core.
     Store Ethernet config set pointer for later use
     [/cover] */
    Eth_ConfigSetPtr = CfgPtr;
    /* Get pointer to Core Configuration data */
    EthLocalCoreCfgPtr = Eth_ConfigSetPtr->EthCoreAdd[CoreId];
    /* Get pointer to controller Configuration data */
    EthLocalCntrlCfgPtr = EthLocalCoreCfgPtr->EthCoreCntrlPtr;
    /* Get pointer to controller status of current core */
    EthLocalCoreStatusPtr = Eth_CntrlStatus[CoreId];
    *(Eth_17_GEthMac_CoreInitStatus[CoreId]) =
                                    (uint32)ETH_17_GETHMAC_CORE_UNINIT;
    /* Loop through all controllers allocated to current core.*/
    for(ControllerIdx = 0; ((ControllerIdx < EthLocalCoreCfgPtr->\
                   EthMaxControllers) && (RetValue == E_OK)); ControllerIdx++)
    {
      /* Initialize Buffer Descriptor pointer for the current controller */
      EthLocalCoreStatusPtr->EthBuffDecPtr = Eth_BuffDecPtrAddr\
                                            [EthLocalCntrlCfgPtr->EthCntrlIdx];
      /* Initialise global variables for current controller */
      Eth_17_lInitGlobalVar(EthLocalCntrlCfgPtr,EthLocalCoreStatusPtr);
      /* get base address of the controller */
      EthCntrlAdd = Eth_GEthMacCntrl[EthLocalCntrlCfgPtr->EthCntrlIdx];
      /* Enable the clock */
      /* [cover parentID={0931D852-9F9E-469f-9D3A-D5161B8B304C}]
       Enable the GETH MAC Module
       [/cover] */
      ETH_17_GETHMAC_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG \
                       (&(EthCntrlAdd->CLC),(uint32)ETH_17_GETHMAC_MOD_ENABLE);
      RegVal = (uint32) EthCntrlAdd->CLC.B.DISS;
      /* [cover parentID={54398F34-02C4-49cd-9298-8206DAB36EF0}]
        GETH MAC Enabled
        [/cover] */
      /* Check if GETH is enabled, if not, report DEM_E_ACCESS error. */
      if(RegVal != (uint32) ETH_17_GETHMAC_MOD_ENABLE)
      {
        /* [cover parentID={9753DAF6-9CE8-4d8f-AB79-480411B622A7}][/cover] */
        if(EthLocalCntrlCfgPtr->EthDemAccess != \
                                            ETH_17_GETHMAC_DISABLE_DEM_REPORT)
        {
          /* [cover parentID={E0D09020-C4AF-480d-96F2-7DE34E753878}]
             Report Production Error (Hardware Access failure) as DEM_EVENT_STATUS_PREFAILED
             [/cover] */
          /*Production Error should be reported only if Production Error has been enabled  */
          Mcal_Wrapper_Dem_ReportErrorStatus(EthLocalCntrlCfgPtr->EthDemAccess, \
                                       DEM_EVENT_STATUS_PREFAILED);
        }
        RetValue = E_NOT_OK;
      }
      else
      {
        /* Configure the external PHY interface and the alternate inputs
           to be used */
        ETH_17_GETHMAC_SFR_INIT_DEINIT_WRITE32(&EthCntrlAdd->GPCTL.U,
          (uint32)(((((uint32)EthLocalCntrlCfgPtr->EthCntrlProperties >>
            (uint32)ETH_17_GETHMAC_PHYINT_POS) & (uint32)ETH_17_GETHMAC_SEVEN)
            << (uint32)ETH_17_GETHMAC_GPTCL_PHY_POS) |
            (uint32)EthLocalCntrlCfgPtr->EthGptclRegVal));

        /*Production Error should be reported only if Production Error has been enabled  */
        /* [cover parentID={50CDE701-1C40-496d-B0FE-0D33DF01289A}][/cover] */
        if(EthLocalCntrlCfgPtr->EthDemAccess !=
                                          ETH_17_GETHMAC_DISABLE_DEM_REPORT)
        {
          /* [cover parentID={F0DA4CD1-932A-4dbe-A1D9-216F05A4DACC}]
             Report Production Error (Hardware Access failure) as DEM_EVENT_STATUS_PREPASSED
             [/cover] */
          Mcal_Wrapper_Dem_ReportErrorStatus(EthLocalCntrlCfgPtr->EthDemAccess,
                                        DEM_EVENT_STATUS_PREPASSED);
        }
      }
      EthLocalCntrlCfgPtr++;
      EthLocalCoreStatusPtr++;
    }
    /* Set Core status to INITIALIZED if no Production Error is reported */
    /* [cover parentID={A1283A8A-E513-43ed-8174-4438232DF872}]
     [/cover] */
    if(RetValue == E_OK)
    {
       /* [cover parentID={00C29C67-C776-4fe1-B569-B689B020DDAD}]
         [/cover] */
      *(Eth_17_GEthMac_CoreInitStatus[CoreId]) =
                                        (uint32)ETH_17_GETHMAC_CORE_INIT;
    }
  }
}

/*******************************************************************************
** Traceability    : [cover parentID={8DCF5DC0-7CC3-49ee-82EE-2006AA5AB0C9}]  **
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
/*CYCLOMATIC_Eth_17_GEthMac_ProvideTxBuffer_JUSTIFICATION: Function performs
  DET check for Init, Controller Init, Invalid Cntrl Index, Buffer Index
  pointer, Invalid buffer pointer and Invalid Length byte pointer. Additionally
  functional checks are added to enable schms for interrupt mode and allocating
  the requested buffer. For better readability and understanding, it is decided
  to keep all the checks and functionality within the same function */
BufReq_ReturnType Eth_17_GEthMac_ProvideTxBuffer(const uint8 CtrlIdx,
                                             Eth_BufIdxType* const BufIdxPtr,
                                             uint8** const BufPtr,
                                             uint16* const LenBytePtr)
{
  /* [cover parentID={FA0182E6-2E98-4d56-B6EF-1B1AEF6E605D}]
  In Default, Set BufferStatus = BUFREQ_E_BUSY(To Return)
  [/cover] */
  BufReq_ReturnType BufferStatus = BUFREQ_E_BUSY;
  Eth_17_GEthMac_TxBuffTableType *CurrTxBuffTablePtr;
  uint32 DescStatus;
  uint16 TxBufLengthConfig;
  const Eth_17_GEthMac_CoreCntrlConfigType *EthLocalCntrlCfgPtr;
  Eth_17_GEthMac_CntrlStatusType *EthLocalCoreStatusPtr;
  uint8 IntEnabled;
  #if (ETH_17_GETHMAC_GLOBALTIMESUPPORT == STD_ON)
  const volatile uint8 *TxBuffBasePtr;
  uint16 TxBufLengthAligned;
  #endif

#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
  /* Check if Eth_17_GEthMac_Init is sucessfull */
  /* [cover parentID={563663D8-0E56-4e26-8E18-CC1E35F232C6}]
  Check if driver is initialized
  [/cover] */
  DevError = Eth_17_lDetCheckNoInitStage1(ETH_17_GETHMAC_SID_PROVIDETXBUFFER);
  /* [cover parentID={C96F2493-9513-4b4c-934D-B262FBEC0984}]
  If driver is initialized
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* [cover parentID={E6EE1AA2-7068-4740-A120-9FC1CD64D6C8}]
     Validate CtrlIdx
     [/cover] */
    DevError = Eth_17_lDetCheckInvalidCtrlIdx( \
                                  CtrlIdx, ETH_17_GETHMAC_SID_PROVIDETXBUFFER);
  }
  /* [cover parentID={98885AD7-CA30-46f8-8729-5FAA15FE8F0E}]
  Valid Controller Index
  [/cover] */
  /* ETH_17_GETHMAC_E_NOT_INITIALIZED */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* Check if controller init is Sucessfull in
                                           Eth_17_GEthMac_SetControllerMode */
    /* [cover parentID={46A326B3-7FBA-4fa5-8582-E1F9F3FA6CF2}][/cover] */
    DevError = Eth_17_lDetCheckNoInit(ETH_17_GETHMAC_SID_PROVIDETXBUFFER, \
                                                                      CtrlIdx);
  /* [cover parentID={3D4AA4A8-64D9-450a-91A3-DB51F9930D79}]
     Controller Initialized
  [/cover] */
  }
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* [cover parentID={177B5BDC-1E1B-4f79-9F6F-727F8F755CE8}]
     [/cover] */
    /* ETH_17_GETHMAC_E_PARAM_POINTER Check if BufIdxPtr is valid */
    DevError = Eth_17_lDetCheckInvalidPointer( \
                             BufIdxPtr, ETH_17_GETHMAC_SID_PROVIDETXBUFFER);
  }
  /* [cover parentID={D70BC1A5-4CC3-4aa0-B911-061CE6DD0A68}]
  Valid BufIdxPtr
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* [cover parentID={89F95FD5-DF12-43cd-A6CA-1DE5488CD225}]
    [/cover] */
    /* ETH_17_GETHMAC_E_PARAM_POINTER Check if BufPtr is valid */
    DevError = Eth_17_lDetCheckInvalidPointer(\
                              (BufPtr), ETH_17_GETHMAC_SID_PROVIDETXBUFFER);
  }
  /* [cover parentID={3956DC35-DE21-423f-8FBA-719E4497E991}]
  Valid BufPtr
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* [cover parentID={B0757C9F-90A4-4b0c-9C8F-86F11FDB63C6}]
    [/cover] */
    /* ETH_17_GETHMAC_E_PARAM_POINTER Check if LenBytePtr is valid*/
    DevError = Eth_17_lDetCheckInvalidPointer( \
                              LenBytePtr, ETH_17_GETHMAC_SID_PROVIDETXBUFFER);
  }
  /* [cover parentID={504168B1-CCA8-461d-A2C7-F0D538137CBA}]
  Valid LenBytePtr
  [/cover] */
  if(DevError != ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* [cover parentID={F2E47FA4-2735-4dfd-83F9-86D81C7F6D31}]
    [/cover] */
    BufferStatus = BUFREQ_E_NOT_OK;
  }
  /* [cover parentID={B484A71E-0F2B-4b73-B7E4-E5F81E4F6A33}]
  Merge
  [/cover] */
  /* [cover parentID={BC08E901-2630-4d59-80B5-DE5A1320A535}]
  Merge
  [/cover] */
  else
#endif /* End of ETH_17_GETHMAC_DEV_ERROR_DETECT */
  {
    /* Get controller configuration data */
    EthLocalCntrlCfgPtr = Eth_17_lGetCtrlConfigPtr(CtrlIdx);
    /* Get controller status */
    EthLocalCoreStatusPtr = Eth_17_lGetCtrlStatusPtr(CtrlIdx);
    IntEnabled = (uint8)((EthLocalCntrlCfgPtr->EthCntrlProperties >>\
    ETH_17_GETHMAC_TXINT_POS) & ETH_17_GETHMAC_ONE);
    /* [cover parentID={2D2CB365-DE7E-4360-A35C-23D7B7D529A8}]
      If Tx interrupt is enabled
      [/cover] */
    if(IntEnabled == ETH_17_GETHMAC_ONE)
    {

      /* [cover parentID={5D9BFDDF-71BE-4101-9982-41E37D5788E7}]
      [/cover] */
      /* [cover parentID={B44FCC26-14D5-4c15-B1E0-C2B4C20E04AB}]
      [/cover] */
      SchM_Enter_Eth_17_GEthMac_TransmitData();
    }

    /* Get current TxBuffTable index which are in scanning to check buffer
       status */
    CurrTxBuffTablePtr=&(EthLocalCoreStatusPtr->EthBuffDecPtr->\
    EthTxBuffTablePtr[EthLocalCoreStatusPtr->EthRunTimeOpertnData.CurrTxIdx]);

    /* Get configured buffer length */
    TxBufLengthConfig = EthLocalCntrlCfgPtr->EthCtrlTxBufLenByte;

    /* Check that,if buffer status is used, transmission is done and Tx
       confirmation is not requested by application.So releae buffer. */
    /* [cover parentID={741C095D-3BE2-4602-9B9B-815EAAB1EF22}]
    Corresponding to current "TxBufferTable" pointer, Buffer status is USED
    and Frame transmission is initiated and Tx confirmation is not needed
    [/cover] */

    if((CurrTxBuffTablePtr->BuffStatus == ETH_17_GETHMAC_BUFFER_USED) && \
        (CurrTxBuffTablePtr->FrameTxInitiated == ETH_17_GETHMAC_ONE) && \
        (CurrTxBuffTablePtr->TxConfirmReq == ETH_17_GETHMAC_ZERO))
    {
      DescStatus=EthLocalCoreStatusPtr->EthBuffDecPtr->EthDmaTxDescPtr\
                [EthLocalCoreStatusPtr->EthRunTimeOpertnData.CurrTxIdx].TDES3;

      /* Check if Buffer is released by DMA by checking OWN bit.*/
      /* [cover parentID={1496F522-A42D-4a22-A841-A7869BAF5C9F}]
      Buffer is released by DMA(check OWN bit of current Tx Descriptor)
      [/cover] */
      if((DescStatus & ((uint32)ETH_17_GETHMAC_DMA_TX_DESC_OWN_SET)) \
                                                     == ETH_17_GETHMAC_ZERO)
      {
        /* buffer has been transmitted, release buffer now. */
        /* [cover parentID={42ACFEEB-327E-4955-856A-8AFF71E0E575}]
        Corresponding to current "TxBufferTable" pointer, Mark Buffer
        status as FREE and Frame transmission initiated as NO
        [/cover] */
        CurrTxBuffTablePtr->FrameTxInitiated = ETH_17_GETHMAC_ZERO;
        CurrTxBuffTablePtr->BuffStatus = ETH_17_GETHMAC_BUFFER_NOTUSED;

        /* If this buffer is the next one to wait for being confirmed */
        /* [cover parentID={407C6ABD-67C0-4ab7-9BEB-892ACCF607C9}]
        Current Tx  Confirmation Buffer Index  is  Current Tx Index
        [/cover] */

        if(EthLocalCoreStatusPtr->EthRunTimeOpertnData.ConfirmTxBufIdx == \
            EthLocalCoreStatusPtr->EthRunTimeOpertnData.CurrTxIdx)
        {
          /* Implicitly confirmed, therefore move to next buffer */
          /* [cover parentID={87F71D0E-5241-4d21-A427-80A4D7EDF66B}]
          Increment Current Tx Confirmation Buffer Index
          [/cover] */
          EthLocalCoreStatusPtr->EthRunTimeOpertnData.ConfirmTxBufIdx = \
            Eth_17_lIncrTxBufIdx(EthLocalCoreStatusPtr->EthRunTimeOpertnData.\
            ConfirmTxBufIdx, EthLocalCntrlCfgPtr->EthTxBufTotal);
        }
      }
    }
    /* [cover parentID={C8AFB3B1-1634-49d7-B837-43F403877987}]
    Allocated Tx Buffer Size <= Frame header and CRC size
    [/cover] */
    /* Allocated Tx Buffer Size should not be less than or equal to
    ETH total Frame Header = Header(14) + Frame CRC(4)
    That is reserved size (header and frame CRC) is 18 bytes */
    if(TxBufLengthConfig <=
      ((uint16)(ETH_17_GETHMAC_FRAMEHEADER_LENGTH +
       ETH_17_GETHMAC_FRAMECHKSUM_LENGTH)))
    {
      /* [cover parentID={3E5564C7-1E6B-45ce-8553-07BB9A4E2741}]
      Fill output parameter 'LenBytePtr' as Zero
      ( No buffer allocated for data in frame)
      [/cover] */
      /* No Buffer allcated to hold Ethernet frame data bytes*/
      *LenBytePtr = (uint16)(ETH_17_GETHMAC_ZERO);
      /* [cover parentID={FC0F1A15-E703-4f29-91FC-05D5C4CB063D}]
      BufferStatus = BUFREQ_E_OVFL ( To Return)- That is, requested buffer
      too large
      [/cover] */
      BufferStatus = BUFREQ_E_OVFL;
    }
    /* [cover parentID={30C86B75-F640-48fe-975F-6159BD0ACD9D}]
    Requested Lenght of Buffer Size is <= Allocated Tx Buffer
    Size - Frame Header and  CRC
    [/cover] */
    /* The requested buffer size should not exceed Configured
    Tx Buffer - ETH total Frame Header.
    ETH total Frame Header = Header(14) + Frame CRC(4)
    That is reserved size (header and frame CRC) is 18 bytes */
    else if((uint16)(*LenBytePtr) > (TxBufLengthConfig -
        ((uint16)(ETH_17_GETHMAC_FRAMEHEADER_LENGTH +
                  ETH_17_GETHMAC_FRAMECHKSUM_LENGTH))))
    {
      /* [cover parentID={10B72E0B-16B3-45f1-BC64-449B15344CAF}]
      Fill output parameter 'LenBytePtr' as
      Allocated Tx Buffer Size - Frame Header and  CRC)
      [/cover] */
      *LenBytePtr = TxBufLengthConfig -
      ((uint16)(ETH_17_GETHMAC_FRAMEHEADER_LENGTH +
                ETH_17_GETHMAC_FRAMECHKSUM_LENGTH));
      /* [cover parentID={FC0F1A15-E703-4f29-91FC-05D5C4CB063D}]
      BufferStatus = BUFREQ_E_OVFL ( To Return)- That is, requested buffer
      too large
      [/cover] */
      BufferStatus = BUFREQ_E_OVFL;
    }
    else
    {
      /* [cover parentID={495EE374-FE8E-41b4-AD28-8A7E2DA83FEE}]
      Corresponding to current "TxBufferTable" pointer, Buffer status is FREE
      [/cover] */
      /* Check if Buffer status is Unused. */
      if(CurrTxBuffTablePtr->BuffStatus == ETH_17_GETHMAC_BUFFER_NOTUSED)
      {
        /*If timestamp is enabled, the Tx Descriptor will be overwritten by
        the HW to capture the timestamp.Hence, re-initialize Tx Descriptor if
        timestamp is enabled.*/
        #if (ETH_17_GETHMAC_GLOBALTIMESUPPORT == STD_ON)
        TxBufLengthAligned = EthLocalCntrlCfgPtr->EthCtrlTxBufLenByteAligned;

        /*Get Start Address of Tx Buffer*/
        TxBuffBasePtr = &(EthLocalCoreStatusPtr->EthBuffDecPtr->\
                                       EthTxBufferPtr[ETH_17_GETHMAC_ZERO]);
        /*Assign the TDES0 to the current buffer pointer*/
        /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between integer to a
        pointer type is performed to access the buffer address from DMA
        descriptor. This is the intended design and valid as per DMA hardware
        design. There are no side effects seen by violating this rule.*/
        /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from unsigned long to pointer
        is performed to access the buffer address from DMA descriptor.
        This is the intended design and valid as per DMA hardware design.
        There are no side effects seen by violating this rule.*/
        /* MISRA2012_RULE_10_8_JUSTIFICATION: Impermissible cast of composite
        expression is performed to access the buffer address from DMA
        descriptor. This is the intended design and valid as per DMA hardware
        design. There are no side effects seen by violating this rule.*/
        /* MISRA2012_RULE_18_4_JUSTIFICATION: pointer arithmetic is performed
        using '+' operator to configure the RAM address in DMA descriptors.
        This is the intended design and valid as per DMA hardware
        design. There are no side effects seen by violating this rule.*/
        EthLocalCoreStatusPtr->EthBuffDecPtr->EthDmaTxDescPtr\
        [EthLocalCoreStatusPtr->EthRunTimeOpertnData.CurrTxIdx].TDES0 = \
        (uint32)(TxBuffBasePtr + ((uint32)EthLocalCoreStatusPtr->\
                EthRunTimeOpertnData.CurrTxIdx * (uint32)TxBufLengthAligned));

        /* Re-initialize TDES1 to zero */
        EthLocalCoreStatusPtr->EthBuffDecPtr->EthDmaTxDescPtr\
            [EthLocalCoreStatusPtr->EthRunTimeOpertnData.CurrTxIdx].TDES1 = \
                                                   (uint32)ETH_17_GETHMAC_ZERO;

        /* Enable Interrupt on transmission completion.
        Buffer length/Packet length in TDES2 and TDES3 will be updated
        during Transmit request. Previously enabled TTSE bit is disabled*/
        EthLocalCoreStatusPtr->EthBuffDecPtr->EthDmaTxDescPtr\
             [EthLocalCoreStatusPtr->EthRunTimeOpertnData.CurrTxIdx].TDES2 = \
                                         (uint32)ETH_17_GETHMAC_DMA_TDES2_INIT;
        #endif

        /* [cover parentID={06CDFE3E-6E66-44a4-9125-03C94B8CB209}]
        Corresponding to current "TxBufferTable" pointer, Mark Buffer status as
        USED, Frame transmission initiated as NO and Tx confirmation
        requested as NO
        [/cover] */
        /* Provide Buffer index and buffer pointer to application
           Set buffer used, Transmission not yet requested, no confirmation. */
        *BufIdxPtr = EthLocalCoreStatusPtr->EthRunTimeOpertnData.CurrTxIdx;

        CurrTxBuffTablePtr->FrameTxInitiated = ETH_17_GETHMAC_ZERO;
        CurrTxBuffTablePtr->TxConfirmReq = ETH_17_GETHMAC_ZERO;
        CurrTxBuffTablePtr->BuffStatus = ETH_17_GETHMAC_BUFFER_USED;

        /*Store requested buffer length to check during Transmit API */
        CurrTxBuffTablePtr->BuffLengthReqstd = *LenBytePtr;
        /* [cover parentID={2E45F990-DDBB-4b40-80BC-581D8587E354}]
        Provide Buffer Index and Buffer Pointer to Application
        (Fill output parameters BufIdxPtr with Current Tx index and BufPtr with
        buffer address from Current Tx Descriptor )
        [/cover] */
        /* Ethernet Packet format is,
        MAC Destination Address(6) + MAC Source Address(6) + Type/Length(2)+
        Payload/Data(46-1500) + FCS(4)*/
        /* Upper layer only fill the data(Payload),Frame Header has to be filled
        by Eth_Transmit function so BufPtr points Payload Pointer*/

        /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between integer to a
        pointer type is performed to access the buffer address from DMA
        descriptor. This is the intended design and valid as per DMA hardware
        design. There are no side effects seen by violating this rule.*/
        /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from unsigned long to pointer
        is performed to access the buffer address from DMA descriptor.
        This is the intended design and valid as per DMA hardware design.
        There are no side effects seen by violating this rule.*/
        /* MISRA2012_RULE_10_8_JUSTIFICATION: Impermissible cast of composite
        expression is performed to access the buffer address from DMA
        descriptor. This is the intended design and valid as per DMA hardware
        design. There are no side effects seen by violating this rule.*/
        *BufPtr = (uint8*) \
        (EthLocalCoreStatusPtr->EthBuffDecPtr->EthDmaTxDescPtr\
        [EthLocalCoreStatusPtr->EthRunTimeOpertnData.CurrTxIdx].TDES0 + \
                                          ETH_17_GETHMAC_FRAMEHEADER_LENGTH);

        /* Move the scanning to next buffer index */
        EthLocalCoreStatusPtr->EthRunTimeOpertnData.CurrTxIdx = \
            Eth_17_lIncrTxBufIdx(EthLocalCoreStatusPtr->EthRunTimeOpertnData.\
                                CurrTxIdx, EthLocalCntrlCfgPtr->EthTxBufTotal);

        /* [cover parentID={53D46AF0-2BB6-4ae7-8F82-C461AA3219CE}]
        BufferStatus = BUFREQ_OK ( To Return)
        [/cover] */
        BufferStatus = BUFREQ_OK;
      }
    }
    /* [cover parentID={DB05B5D4-025A-42e6-935B-215B93082698}]
     [/cover] */
    if(IntEnabled == ETH_17_GETHMAC_ONE)
    {
        /* [cover parentID={AC5FD0D9-152E-4885-BAE6-988F91EEBEA1}]
          [/cover] */
        SchM_Exit_Eth_17_GEthMac_TransmitData();
    }
  }
   /* [cover parentID={E15260ED-BB6F-44d7-9FFF-1AF7237C9B34}]
   [/cover] */
  return BufferStatus;
}
/*******************************************************************************
** Traceability    : [cover parentID={3B191C72-E5F6-4b08-8934-C12BAA81BC57}]  **
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
Std_ReturnType Eth_17_GEthMac_SetControllerMode(const uint8 CtrlIdx,
                                                  const Eth_ModeType CtrlMode )
{
  Eth_ModeType CurrentMode;
  uint32 RegVal;
  const Eth_17_GEthMac_CoreCntrlConfigType *EthLocalCntrlCfgPtr;
  Eth_17_GEthMac_CntrlStatusType *EthLocalCoreStatusPtr;
  const Ifx_GETH *EthCntrlAdd;
  Std_ReturnType RetValue = E_NOT_OK;

#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError = ETH_17_GETHMAC_E_DET_NO_ERR;
  /* Check if Eth_17_GEthMac_Init is successful */
  /* [cover parentID={E7BAD778-DE8F-4752-B657-BB2E228626A3}][/cover] */
  DevError = Eth_17_lDetCheckNoInitStage1(ETH_17_GETHMAC_SID_SETCONTROLLERMODE);
  /* [cover parentID={71236659-3338-4710-A06C-1496668A5E73}]
  Eth_17_GEthMac_Init is successful
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* [cover parentID={5A7D1F05-2DC8-4d8a-AAF3-8F44D6765606}]
     ETH_17_GETHMAC_E_INV_CTRL_IDX Check if CtrlIdx is valid
    [/cover] */
    DevError = Eth_17_lDetCheckInvalidCtrlIdx(
                              CtrlIdx, ETH_17_GETHMAC_SID_SETCONTROLLERMODE);
  }
  /* [cover parentID={B690C1BA-E3C2-47c3-9C1B-5C38CBC41BF5}]
  Valid Controller Index
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* Check the paramter CtrlMode is valid  */
    /* [cover parentID={3EE6BF8F-83C2-441d-89DB-F96746F0C774}]
     Validate CtrlMode
     [/cover] */
    DevError =  Eth_17_lDetCheckInvalidMode(CtrlMode);
  }
  /* [cover parentID={BDD68897-EE2A-4adf-86C1-CB2BE916F7FA}]
  Valid CtrlMode
  [/cover] */
  if(DevError != ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* [cover parentID={1B6D1DE7-B359-4b29-B3AB-569E710115D3}]
    Set RetValue = E_OK
    [/cover] */
    RetValue = E_NOT_OK;
  }
  /* [cover parentID={BDD68897-EE2A-4adf-86C1-CB2BE916F7FA}]
  Valid CtrlMode
  [/cover] */
  /* [cover parentID={BC022E1A-176D-47df-9BDB-21FD1B258818}]
  Merge
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
#endif /* End of ETH_17_GETHMAC_DEV_ERROR_DETECT */
  {
    /* Get controller configuration data */
    EthLocalCntrlCfgPtr = Eth_17_lGetCtrlConfigPtr(CtrlIdx);
    /* Get controller status */
    EthLocalCoreStatusPtr = Eth_17_lGetCtrlStatusPtr(CtrlIdx);
    /* Get base address of the indexed controller */
    EthCntrlAdd = Eth_GEthMacCntrl[EthLocalCntrlCfgPtr->EthCntrlIdx];
    /*Check if GETH IP is enabled*/
    RegVal = (uint32) EthCntrlAdd->CLC.B.DISS;
    /* [cover parentID={A5D9419B-4D09-4a9a-8E12-7E73048512FA}]
    GETH MAC is enabled
    [/cover] */
    /* DEM_E_ACCESS error detection */
    if(RegVal != (uint32) ETH_17_GETHMAC_MOD_ENABLE)
    {
      /* [cover parentID={80F2F0DD-FA71-4a5d-955A-59DDF156FABA}]
      GETH MAC is enabled
      [/cover] */
      if(EthLocalCntrlCfgPtr->EthDemAccess != ETH_17_GETHMAC_DISABLE_DEM_REPORT)
      {
        /* [cover parentID={312CBD59-33ED-44ab-8562-48E145489943}]
        Report Production Error (Hardware Access failure) as DEM_EVENT_STATUS_PREFAILED
        [/cover] */
        /* Production Error should be reported only if Production Error has
        been enabled. */
        Mcal_Wrapper_Dem_ReportErrorStatus(EthLocalCntrlCfgPtr->EthDemAccess,
                                      DEM_EVENT_STATUS_PREFAILED);
      }
      RetValue = E_NOT_OK;
    }
    else
    {
      /* [cover parentID={3849484B-9645-44a5-8676-2DA0B80CFEE2}]
      Init Stage-1 is done and MII interface Configuration status is NOT
      CONFIGURED
      [/cover] */
      if(EthLocalCoreStatusPtr->EthRunTimeOpertnData.CntrlConfigStatus
                                       == ETH_17_GETHMAC_CNTRL_NOT_INITIALIZED)
      {
        /*Complete controller Initialization */
        /*Info: If controller Initialization(Init Stage-2) completed
        successfully, then CntrlConfigStatus will be set as
        ETH_17_GETHMAC_CNTRL_INITIALIZED from called function*/
        /*Info:Any error during Init Stage-2, will cause to raise
         Hardware Access failure Production Error from called function*/
        Eth_17_lInitGethController(EthLocalCntrlCfgPtr);
      }
      /* [cover parentID={E2713A50-30C9-4a5c-B639-C1AEE268283B}]
      If Controller is initialized
      [/cover] */
      /* Try operating to change controller mode( ACTIVE/DOWN) only if
      CntrlConfigStatus is ETH_17_GETHMAC_CNTRL_INITIALIZED*/
      if(EthLocalCoreStatusPtr->EthRunTimeOpertnData.CntrlConfigStatus == \
                                              ETH_17_GETHMAC_CNTRL_INITIALIZED)
      {
        /* [cover parentID={EF6EE2FF-5C2C-4b0f-8246-BC80D32D7CE1}]
        Requested Controller Mode (ACTIVE)
        [/cover] */
        /* If Requested mode is to Set to ACTIVE. */
        if(CtrlMode == ETH_MODE_ACTIVE)
        {
          /* Get current mode, ACTIVE or DOWN */
          /* [cover parentID={5045D4D0-4A4D-4117-90E8-DCA27CAA25BF}]
          [/cover] */
          CurrentMode = Eth_17_lGetMode(CtrlIdx);

          /* If current mode is DOWN. */
          /* [cover parentID={32D7688C-7460-4741-8BC3-0AB7C786B741}]
          Current Mode is DOWN
          [/cover] */
          if(CurrentMode == ETH_MODE_DOWN)
          {
            /* [cover parentID={C2AE12F9-7277-406e-B459-FA814EFEB349}]
            Reset all Tx and Rx status and Buffers
            [/cover] */
            /* Reset Tx/Rx status,Buffers.*/
            Eth_17_lResetTxRxStatus(EthLocalCntrlCfgPtr);

            /* Enable interrupt before setting controller to Acitve mode */
            Eth_17_lEnableGethInterrupt(EthLocalCntrlCfgPtr);

            /* [cover parentID={54244432-D66A-46f4-99A2-3DF7CD336063}]
            Start Tx and Rx in MAC and DMA
            [/cover] */
            /* start Tx and Rx in MAC and DMA core.*/
            Eth_17_lStartTxRx(CtrlIdx);

            EthLocalCoreStatusPtr->EthRunTimeOpertnData.EthControllerMode = \
                                                               ETH_MODE_ACTIVE;
            /* [cover parentID={91782AE8-C0E2-4509-89D4-D9DFE7F7DE2A}]
            [/cover] */
            if(EthLocalCntrlCfgPtr->EthDemAccess != \
                                  ETH_17_GETHMAC_DISABLE_DEM_REPORT)
            {
              /* Production error should be reported only if Production error
              has been enabled. */
              /* [cover parentID={59268AC7-85CF-4555-8A56-5AAF3E6BBEED}]
              Report Production error (Hardware Access failure) as
              DEM_EVENT_STATUS_PREPASSED
              [/cover] */
              Mcal_Wrapper_Dem_ReportErrorStatus(
              EthLocalCntrlCfgPtr->EthDemAccess, DEM_EVENT_STATUS_PREPASSED);
            }
            /* [cover parentID={4F5F17D9-1EC4-4f16-963D-3F7EB789DADD}]
            Set RetValue = E_OK
            [/cover] */
            RetValue = E_OK;
          }
          /* [cover parentID={32D7688C-7460-4741-8BC3-0AB7C786B741}]
          Current Mode is ACTIVE
          [/cover] */
          else
          {
            /*Controller is already in ACTIVE State.*/
            EthLocalCoreStatusPtr->EthRunTimeOpertnData.EthControllerMode = \
                                                               ETH_MODE_ACTIVE;
            /* [cover parentID={16DEC74C-BD50-4c68-B251-9CF782138AB3}]
            [/cover] */
            if(EthLocalCntrlCfgPtr->EthDemAccess != \
                                   ETH_17_GETHMAC_DISABLE_DEM_REPORT)
            {
              /* [cover parentID={59268AC7-85CF-4555-8A56-5AAF3E6BBEED}]
              Report Production error (Hardware Access failure) as
              DEM_EVENT_STATUS_PREPASSED
              [/cover] */
              /* Production error should be reported only if Production error
              has been enabled. */
              Mcal_Wrapper_Dem_ReportErrorStatus(
              EthLocalCntrlCfgPtr->EthDemAccess, DEM_EVENT_STATUS_PREPASSED);
            }
            /* [cover parentID={203C6F3B-9CB3-452c-9E7D-16AAEFF97A0D}]
            Set RetValue = E_OK ( controller is already ACTIVE)
            [/cover] */
            RetValue = E_OK;
          }
        }
        /* [cover parentID={EF6EE2FF-5C2C-4b0f-8246-BC80D32D7CE1}]
         Requested Controller Mode (DOWN)
        [/cover] */
        else if(CtrlMode == ETH_MODE_DOWN)
        {
          /* [cover parentID={5994761B-A31A-448d-B641-D479EB7EF92C}]
          Stop Tx and Rx in MAC and DMA
          [/cover] */
          /* Requested mode is set to DOWN. */
          Eth_17_lStopTxRx(CtrlIdx);

          EthLocalCoreStatusPtr->EthRunTimeOpertnData.EthControllerMode = \
                                                                ETH_MODE_DOWN;

          /* [cover parentID={4A9FCE7E-A81E-48a6-9809-C939D688DF8A}]
          Reset all Tx and Rx status and Buffers
          [/cover] */
          /* Reset Tx/Rx status,Buffers.*/
          Eth_17_lResetTxRxStatus(EthLocalCntrlCfgPtr);

          /* [cover parentID={BA69331F-D5B6-4a1e-88FF-0E31486AC3A3}]
          Set RetValue = E_OK
          [/cover] */
          RetValue = E_OK;
          /* [cover parentID={D37C67D9-D2C8-42dd-A114-825AC3A21C69}]
          Report Production error (Hardware Access failure) as
          DEM_EVENT_STATUS_PREPASSED
          [/cover] */
          if(EthLocalCntrlCfgPtr->EthDemAccess != \
                                  ETH_17_GETHMAC_DISABLE_DEM_REPORT)
          {
            /* Production error should be reported only if Production error
            has been enabled. */
            Mcal_Wrapper_Dem_ReportErrorStatus(
            EthLocalCntrlCfgPtr->EthDemAccess, DEM_EVENT_STATUS_PREPASSED);
          }
        }
        /* [cover parentID={EF6EE2FF-5C2C-4b0f-8246-BC80D32D7CE1}]
        Requested Controller Mode (INVALID)
        [/cover] */
        else
        {
#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_OFF)
          /* Requested mode is unknown (in paramter CtrlMode) */
          RetValue = E_NOT_OK;
#endif /*ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_OFF*/
        }

        /* [cover parentID={B38BD2ED-426D-47c4-A73A-CDAF473BE517}]
        Check Controller mode and if so, indicate the same
        (Inform application about State change)
        [/cover] */
        /* Check Controller mode and if so, indicate the same */
        Eth_17_lCheckForCtrlModeChange(EthLocalCoreStatusPtr, CtrlIdx);
      }
      else
      {
        /* Controller is not initialized */
        RetValue = E_NOT_OK;
      }
    }
  }
  return RetValue;
}
/*******************************************************************************
** Traceability    : [cover parentID={91ABF442-56CF-49e3-ACC9-4AECA724A0AA}]  **
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
Std_ReturnType Eth_17_GEthMac_GetControllerMode(const uint8 CtrlIdx,
                                               Eth_ModeType* const CtrlModePtr)
{
  Std_ReturnType RetValue = E_NOT_OK;

  /* [cover parentID={09106C39-63F5-42f9-8D6B-AA07B1D318F3}]
  DET is enabled
  [/cover] */
#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
  /* Check if Eth_17_GEthMac_Init is successful */
  /* [cover parentID={4F86F872-EBE6-4197-BD19-4E02990F7FD7}]
   Check Driver is initialized
  [/cover] */
  DevError = Eth_17_lDetCheckNoInitStage1(ETH_17_GETHMAC_SID_GETCONTROLLERMODE);
  /* [cover parentID={3B979707-7312-4359-8A5E-69018BC2E4CB}]
  Driver Initialized
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* ETH_17_GETHMAC_E_INV_CTRL_IDX Check if CtrlIdx is valid */
    /* [cover parentID={574609E7-739E-4387-A2A9-B94FD2E2A189}]
    Validate Controller Index
    [/cover] */
    DevError = Eth_17_lDetCheckInvalidCtrlIdx( \
                                 CtrlIdx, ETH_17_GETHMAC_SID_GETCONTROLLERMODE);
  }
  /* ETH_17_GETHMAC_E_NOT_INITIALIZED */
  /* [cover parentID={5B7571F2-0A02-4c4f-BEE8-74AB99614624}]
  Valid Controller Index
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* Check if controller init is Successful in
    Eth_17_GEthMac_SetControllerMode */
    /* [cover parentID={DFD73531-4BCE-4ab7-B2BD-18CF12D1D66A}]
    Check if controller is initialized
    [/cover] */
    DevError = Eth_17_lDetCheckNoInit(ETH_17_GETHMAC_SID_GETCONTROLLERMODE, \
                                                                      CtrlIdx);
  }
  /* [cover parentID={DEFBBFF9-7647-4013-88B0-B43983CE66A8}]
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* [cover parentID={A7ED20B2-41CC-422b-9E4C-C113604DBD04}]
    Validate Controller Mode Pointer
    [/cover] */
    /*  ETH_17_GETHMAC_E_PARAM_POINTER */
    DevError = Eth_17_lDetCheckInvalidPointer(
                            CtrlModePtr, ETH_17_GETHMAC_SID_GETCONTROLLERMODE);
  }
  /* [cover parentID={D5E12E65-5C65-4053-BA43-ECBB9D65AEC4}]
  Valid Controller Mode Pointer
  [/cover] */
  if(DevError != ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* [cover parentID={6F1A4059-F196-4d86-8FE0-5555A20CF206}]
    Set Return Value = E_NOT_OK
    [/cover] */
    RetValue = E_NOT_OK;
  }
  /* [cover parentID={9894DF73-EE71-4891-ADAB-6526D4970E78}]
  Merge
  [/cover] */
  else
#endif /* End of ETH_17_GETHMAC_DEV_ERROR_DETECT */
  {
    /* [cover parentID={D500156D-DA34-4302-9CA5-3E680ADE9D41}]
    Get Current controller mode and fill parameter Controller Mode pointer
    [/cover] */
    /* Get Current controller mode and fill CtrlModePtr value. */
    *CtrlModePtr = Eth_17_lGetMode(CtrlIdx);

    /* [cover parentID={227A4D16-F828-4d43-AC68-B3A8F000E4DB}]
    Set Return Value = E_OK
    [/cover] */
    RetValue = E_OK;
  }
return RetValue;
}

/*******************************************************************************
** Traceability    : [cover parentID={DF2F7C10-89DC-4b31-A21F-1206FC94A3AC}]  **
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
void Eth_17_GEthMac_GetPhysAddr( const uint8 CtrlIdx, uint8* const PhysAddrPtr)
{
#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;

  /* [cover parentID={DC168D59-2BE7-4158-A781-E759FE0A5F30}]
  Validate Physical Address Pointer parameter
  [/cover] */
  /* ETH_17_GETHMAC_E_PARAM_POINTER */
  DevError = Eth_17_lDetCheckInvalidPointer(
                              PhysAddrPtr, ETH_17_GETHMAC_SID_GETPHYADDRESS);
  /* Check if a development error occurred */
  /* [cover parentID={FD0263D2-EB11-4a27-819A-ECE51997439C}]
  Valid Physical Address Pointer
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* Check if Eth_17_GEthMac_Init is successful */
    /* [cover parentID={6198BF65-E63B-41d9-A796-71FF6FC865C0}]
     Check Driver is initialized
     [/cover] */
    DevError = Eth_17_lDetCheckNoInitStage1(ETH_17_GETHMAC_SID_GETPHYADDRESS);
  }
  /* [cover parentID={AAE60EA8-FB51-4929-9CA9-A13C68B973E8}]
   Driver Initialized
   [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* ETH_17_GETHMAC_E_INV_CTRL_IDX Check if CtrlIdx is valid */
    /* [cover parentID={BA98D573-8FD1-4dfa-B753-D9957F214A4D}]
     Validate Controller Index
     [/cover] */
    DevError = Eth_17_lDetCheckInvalidCtrlIdx( \
                                  CtrlIdx, ETH_17_GETHMAC_SID_GETPHYADDRESS);
  }
  /* [cover parentID={5CD54CCA-9DD0-4ba7-AE3C-B31E465652CB}]
  If Ctrl Idx is Valid
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* Check if controller init is Successful in
    Eth_17_GEthMac_SetControllerMode */
    /* [cover parentID={87B7C6D3-55AE-4d78-8061-0537F731C28C}]
    [/cover] */
    DevError = Eth_17_lDetCheckNoInit(ETH_17_GETHMAC_SID_GETPHYADDRESS, \
                                                                      CtrlIdx);
  }
  /* [cover parentID={FE2A62E0-7AA8-4466-B6EC-970333041A2E}]
   If controller is initialized
   [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
#endif /* End of ETH_17_GETHMAC_DEV_ERROR_DETECT */
  {
    /* [cover parentID={95EFCF47-CAF4-4649-AB7E-C847E25672B4}]
    Get the Controller Physical source Address( MAC address) and fill
    in physical address pointer parameter
    [/cover] */
    Eth_17_lGetPhysAddr(PhysAddrPtr,CtrlIdx);
  }
  /* [cover parentID={50BE9477-ACF0-4fd6-90C0-5D7AA6770CF5}]
   Merge
   [/cover] */
}

#if ( ETH_17_GETHMAC_ENA_MII_API == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID={30FB16C2-A016-4694-BDDF-2EDA936F18B9}]  **
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
Eth_ReturnType Eth_17_GEthMac_WriteMii(const uint8 CtrlIdx,
                                       const uint8 TrcvIdx,
                                       const uint8 RegIdx, const uint16 RegVal)
{
  uint32 AddressRegVal;
  uint32 GmiiBusyBitVal;
  uint32 GmiiBusyBitWaitTicks;
  uint32 BaseSTMTick;
  uint32 CurrSTMTick;
  uint32 DelayTickResolution;
  uint8 LocalMdcRegVal;
  boolean IsTimeExpired;
  const Eth_17_GEthMac_CoreCntrlConfigType *EthLocalCntrlCfgPtr;
#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
#endif
  Ifx_GETH *EthCntrlAdd;
  /* [cover parentID={DA74EEEF-D237-439c-A21E-9AD69FA9E04F}]
  Set RetVal = ETH_E_NOT_OK
  [/cover] */
  Eth_ReturnType Eth_Status = ETH_E_NOT_OK;

/* [cover parentID={BEA0549C-EE63-4c2a-A120-1C76E3E8438F}]
DET is enabled
[/cover] */
#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={3D1F7E5B-3065-4d3f-867C-082EE41F6DD4}]
  Check Eth_Init is successfully executed before
  [/cover] */
  DevError = Eth_17_lDetCheckNoInitStage1(ETH_17_GETHMAC_SID_WRITEMII);
  /* [cover parentID={267B078A-6B3E-4b46-A1D2-F7D0A470EC7E}]
  Driver Initialized
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* [cover parentID={10A2E390-0BB0-4378-8828-5AB8EA80FCAC}]
    Validate Controller Index
    [/cover] */
    /*  ETH_17_GETHMAC_E_INV_CTRL_IDX */
    DevError = Eth_17_lDetCheckInvalidCtrlIdx(CtrlIdx, \
                          ETH_17_GETHMAC_SID_WRITEMII);
  }
  /* [cover parentID={527FF5F3-0A20-43cf-8BAC-DA183B0A1580}]
  Valid Controller Index
  [/cover] */
  /* [cover parentID={17D9C4A5-984A-4640-9A56-A44BB1D2033A}]
  Merge
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
#endif /* End of ETH_17_GETHMAC_DEV_ERROR_DETECT */
  {
    /* Get base address of the indexed controller */
    EthCntrlAdd = Eth_GEthMacCntrl[CtrlIdx];
    /* Get controller configuration data */
    EthLocalCntrlCfgPtr = Eth_17_lGetCtrlConfigPtr(CtrlIdx);
    /*Get the Configured Divider value*/
    LocalMdcRegVal = EthLocalCntrlCfgPtr->EthMdcRegVal;
    /* Update 16-bit data value which is to be written to the PHY
       in upcoming write operation */
    EthCntrlAdd->MAC_MDIO_DATA.U = (uint32)RegVal;
    /* [cover parentID={EE5F0E94-A35F-4404-833A-22300E9AB629}]
    Update MDIO Address Register for Write Operation ( Update MDIO address
    register-with Transceiver Index, with Register Index and as  WRITE COMMAND)
    [/cover] */
    /* Update MDIO Address register for write operation */
    AddressRegVal = (uint32)
     ((((uint32)TrcvIdx << (uint32)ETH_17_GETHMAC_PHYLAYERADDRPOSITION) &
                               (uint32)ETH_17_GETHMAC_PHYLAYERADDRMASK) |
     (((uint32)RegIdx << (uint32)ETH_17_GETHMAC_REGADDRPOSITION) &
                             (uint32)ETH_17_GETHMAC_REGADDRMASK) |
     ((uint32)((uint32)LocalMdcRegVal << ETH_17_GETHMAC_CRPOSITION))|
     (uint32)ETH_17_GETHMAC_WRITECOMMAND | (uint32) ETH_17_GETHMAC_GMIIBUSYSET);

    EthCntrlAdd->MAC_MDIO_ADDRESS.U =(uint32)AddressRegVal;

    /* Wait until Write is completed */
    /* Get STM timer current resolution and calculate number of ticks to wait*/
    DelayTickResolution = Mcal_DelayTickResolution();
    GmiiBusyBitWaitTicks  = \
                     (ETH_17_GETHMAC_MAXTIMEOUT_COUNT / DelayTickResolution);
    /* Do not allow ticks to wait to be zero, if STM timer resolution is lower*/
    if(GmiiBusyBitWaitTicks == ETH_17_GETHMAC_ZERO)
    {
      GmiiBusyBitWaitTicks++;
    }
    /*Get current STM tick*/
    CurrSTMTick         = Mcal_DelayGetTick();
    BaseSTMTick         = CurrSTMTick;
    IsTimeExpired       = FALSE;
    do
    {
      GmiiBusyBitVal = (uint32)EthCntrlAdd->MAC_MDIO_ADDRESS.B.GB;
      /* Check wait time is reached at maximum timeout configured*/
      if((((uint32)((CurrSTMTick - BaseSTMTick) & \
             ETH_17_GETHMAC_STM_TICK_OVERFLOW)) >= \
            GmiiBusyBitWaitTicks) && \
           (GmiiBusyBitVal == (uint32)ETH_17_GETHMAC_ONE))
      {
        /*Timeout Happend and write is not completed yet*/
        IsTimeExpired = TRUE;
      }
      /*Get current STM tick*/
      CurrSTMTick = Mcal_DelayGetTick();
    }while((GmiiBusyBitVal == (uint32)ETH_17_GETHMAC_ONE) && \
           (IsTimeExpired == FALSE));

    /*Check Timeout error in case of Hardware issue*/
    /* [cover parentID={59BFFB76-02FF-443f-96F3-52E3EC2B7C3D}]
    Timeout Elapsed
    [/cover] */
    if(IsTimeExpired == FALSE)
    {
      /* [cover parentID={4508C28D-22BA-4e77-8DA9-5B83D5CF09D9}]
      Indicate Write confirmation to Ethernet transceiver driver
      [/cover] */
      /* Provide Write confirmation to Eth transceiver driver .*/
      EthTrcv_WriteMiiIndication(CtrlIdx, TrcvIdx, RegIdx);
      /* [cover parentID={8FDC7477-3F05-4caa-8A10-3AB070CA96AB}]
      Set RetVal =  ETH_OK
      [/cover] */
      Eth_Status = ETH_OK;
    }
    else
    {
      /* [cover parentID={43D8778F-D096-4917-9D73-6D77986C4FBA}]
      Set RetVal = ETH_E_NO_ACCESS
      [/cover] */
      Eth_Status = ETH_E_NO_ACCESS;
    }
  }
  return Eth_Status;
}

/*******************************************************************************
** Traceability    : [cover parentID={8A713443-861E-48a0-A01D-D79A366C5992}]  **
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
Eth_ReturnType Eth_17_GEthMac_ReadMii(const uint8 CtrlIdx,
                                      const uint8 TrcvIdx,
                                      const uint8 RegIdx,
                                      uint16* const RegValPtr)
{
  uint32 AddressRegVal;
  uint32 GmiiBusyBitVal;
  uint32 GmiiBusyBitWaitTicks;
  uint32 BaseSTMTick;
  uint32 CurrSTMTick;
  uint32 DelayTickResolution;
  uint8 LocalMdcRegVal;
  boolean IsTimeExpired;
  const Eth_17_GEthMac_CoreCntrlConfigType *EthLocalCntrlCfgPtr;
#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
#endif
  Ifx_GETH *EthCntrlAdd;
  /* [cover parentID={6583192E-A91A-4137-A76D-089B012362E3}]
  Set RetVal = ETH_E_NOT_OK
  [/cover] */
  Eth_ReturnType Eth_Status = ETH_E_NOT_OK;

#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={42E26D26-4C3D-4e57-B2D5-DE6A97EFD266}]
  Check if driver has initialized
  [/cover] */
  DevError = Eth_17_lDetCheckNoInitStage1(ETH_17_GETHMAC_SID_READMII);
  /* [cover parentID={B6374749-041E-4c7c-B95A-1BE5E385944E}]
  Driver Initialized
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* [cover parentID={A9F499F2-6ABF-4897-A354-9E169D7830FA}]
    Validate Controller Index
    [/cover] */
    /*  ETH_17_GETHMAC_E_INV_CTRL_IDX */
    DevError = Eth_17_lDetCheckInvalidCtrlIdx(CtrlIdx, \
                                              ETH_17_GETHMAC_SID_READMII);
  }
  /* [cover parentID={A4CC9234-A41B-41ae-8DD2-836EE36FD2F1}]
  Valid Controller Index
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* [cover parentID={F75311BC-AA60-4a4a-82FC-A858CE2ABA04}]
    Validate Register Value Pointer
    [/cover] */
    /* ETH_17_GETHMAC_E_PARAM_POINTER. */
    DevError = Eth_17_lDetCheckInvalidPointer(RegValPtr, \
                                              ETH_17_GETHMAC_SID_READMII);
  }
  /* [cover parentID={8903C42B-7973-4461-BC03-2CDC696D6F5B}]
  Valid Register Value Pointer
  [/cover] */
  /* [cover parentID={599343C3-89E4-454e-9168-327737FC64BA}]
  Merge
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
#endif /* End of ETH_17_GETHMAC_DEV_ERROR_DETECT */
  {
    /* get base address of the indexed controller */
    EthCntrlAdd = Eth_GEthMacCntrl[CtrlIdx];
    /*Get the Configured Divider value*/
    EthLocalCntrlCfgPtr = Eth_17_lGetCtrlConfigPtr(CtrlIdx);
    LocalMdcRegVal = EthLocalCntrlCfgPtr->EthMdcRegVal;
    /* Update MDIO Address register for read operation */
    AddressRegVal = (uint32)
      ((((uint32)TrcvIdx << (uint32)ETH_17_GETHMAC_PHYLAYERADDRPOSITION) &
                                     (uint32)ETH_17_GETHMAC_PHYLAYERADDRMASK) |
      (((uint32)RegIdx <<  (uint32)ETH_17_GETHMAC_REGADDRPOSITION) &
                                    (uint32)ETH_17_GETHMAC_REGADDRMASK) |
      ((uint32)((uint32)LocalMdcRegVal << ETH_17_GETHMAC_CRPOSITION))|
      (uint32)ETH_17_GETHMAC_READCOMMAND | (uint32) ETH_17_GETHMAC_GMIIBUSYSET);

    EthCntrlAdd->MAC_MDIO_ADDRESS.U= (uint32)AddressRegVal;

    /* Wait until Read is completed */
    /* [cover parentID={285BFD4C-5BE6-4d68-9F07-C287FEA29659}]
    Wait until Read Operation Completed ( By polling GMII Busy bit)
    or Timeout elapsed
    [/cover] */
    /* Get STM timer current resolution and calculate number of ticks to wait*/
    DelayTickResolution = Mcal_DelayTickResolution();
    GmiiBusyBitWaitTicks  = \
                       (ETH_17_GETHMAC_MAXTIMEOUT_COUNT / DelayTickResolution);
    /* Do not allow ticks to wait to be zero, if STM timer resolution is lower*/
    if(GmiiBusyBitWaitTicks == ETH_17_GETHMAC_ZERO)
    {
      GmiiBusyBitWaitTicks++;
    }
    /*Get current STM tick*/
    CurrSTMTick         = Mcal_DelayGetTick();
    BaseSTMTick         = CurrSTMTick;
    IsTimeExpired       = FALSE;
    do
    {
      GmiiBusyBitVal = (uint32)EthCntrlAdd->MAC_MDIO_ADDRESS.B.GB;
      /* Check wait time is reached at maxmum timeout configured*/
      if((((uint32)((CurrSTMTick - BaseSTMTick) & \
             ETH_17_GETHMAC_STM_TICK_OVERFLOW)) >= \
          GmiiBusyBitWaitTicks) && \
         (GmiiBusyBitVal == (uint32)ETH_17_GETHMAC_ONE))
      {
        /*Timeout Happend and read is not completed yet*/
        IsTimeExpired = TRUE;
      }
      /*Get current STM tick*/
      CurrSTMTick = Mcal_DelayGetTick();
    }while((GmiiBusyBitVal == (uint32)ETH_17_GETHMAC_ONE) && \
           (IsTimeExpired == FALSE));

    /*Check if Timeout error happend in case of Hardware issue*/
    /* [cover parentID={96C40F89-2E6F-4727-99FF-867ED3C3337E}]
    Timeout Elapsed
    [/cover] */
    if(IsTimeExpired == FALSE)
    {
      /* [cover parentID={F7128C64-FFEB-4fb5-9064-DA8C3837ADE6}]
      Read data from MDIO Data Register to and copy to Register Value Pointer
      (function output parameter)
      [/cover] */
      /*Read is successful. Read register value and stor to out parameter */
      /* After Successful read from PHY, Data available at WORD Register*/
      *RegValPtr = (uint16)(EthCntrlAdd->MAC_MDIO_DATA.B.GD);

      /* [cover parentID={4A38020B-D9CE-4583-878C-0CE1F7F8CFD9}]
      Indicate/Provide  read register value to Ethernet transceiver driver
      [/cover] */
      /*Return read register value to Ethernet transceiver driver */
      EthTrcv_ReadMiiIndication(CtrlIdx,TrcvIdx,  RegIdx,(uint8)*RegValPtr);

      /* [cover parentID={E66CC5BD-FEE8-432f-BAB1-AA8FCE2F9EE7}]
      Set RetVal = ETH_OK
      [/cover] */
      Eth_Status = ETH_OK;
    }
    else
    {
      /* [cover parentID={0E3EAEC6-B174-4fbe-B3E4-BA527985A64C}]
      Set RetVal = ETH_E_NO_ACCESS
      [/cover] */
      Eth_Status = ETH_E_NO_ACCESS;
    }
  }
  return Eth_Status;
}
#endif /* End of ETH_17_GETHMAC_ENA_MII_API */

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={E9B31DBF-82AD-479d-8FAB-CC1DB7C6C189}]  **
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
void Eth_17_GEthMac_TxConfirmation(const uint8 CtrlIdx)
{
  uint8 IntEnabled;
  const Eth_17_GEthMac_CoreCntrlConfigType *EthLocalCntrlCfgPtr;
#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError ;
  /* Check if Eth_17_GEthMac_Init is sucessfull */
  /* [cover parentID={5B7F2FEB-B490-4956-8BF3-278A874C75B2}]
  [/cover] */
  DevError = Eth_17_lDetCheckNoInitStage1(ETH_17_GETHMAC_SID_TXCONFIRMATION);
  /* [cover parentID={A97B3752-6EB9-467c-8B9F-D96B4DC30F51}]
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* ETH_17_GETHMAC_E_INV_CTRL_IDX Check if CtrlIdx is valid */
    /* [cover parentID={3EF69222-9AE4-4ce7-82EC-FCA3002D93D0}]
    [/cover] */
    DevError = Eth_17_lDetCheckInvalidCtrlIdx( \
                                  CtrlIdx, ETH_17_GETHMAC_SID_TXCONFIRMATION);
  }

  /* [cover parentID={0C4892CF-5D4B-47c1-9B66-A54E2FA7FCAB}]
  If Ctrl idx is Valid
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* Check if controller init is Sucessfull in
    Eth_17_GEthMac_SetControllerMode */
    /* [cover parentID={E4F4CE7F-E08C-4269-9F0D-477BD5897D9A}]
    [/cover] */
    DevError = Eth_17_lDetCheckNoInit(ETH_17_GETHMAC_SID_TXCONFIRMATION, \
                                                                      CtrlIdx);
  }
  /* [cover parentID={9BB662DE-F279-42c0-B48F-FDFD8F9E21A8}]
  If controller is initialized
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* [cover parentID={8BE3C5C4-F6AB-4ff4-ADB4-E5E4736F364C}]
    Validate Controller Mode
    [/cover] */
    /*  ETH_17_GETHMAC_E_INV_MODE */
    DevError = Eth_17_lDetCheckMode(ETH_17_GETHMAC_SID_TXCONFIRMATION, CtrlIdx);
  }
  /* [cover parentID={82B0FBDD-36E2-4f11-8425-40D4E906D0F0}]
  Valid Controller Mode
  [/cover] */
  /* [cover parentID={F3E2D118-417A-45f2-A199-653916E73998}]
  Merge
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
#endif /* End of ETH_17_GETHMAC_DEV_ERROR_DETECT */
  {
    /* Get controller configuration data */
    EthLocalCntrlCfgPtr = Eth_17_lGetCtrlConfigPtr(CtrlIdx);
    /* If Tx Isr is enabled then confirmation is done in ISR */
    IntEnabled = (uint8)((EthLocalCntrlCfgPtr->EthCntrlProperties >>\
          ETH_17_GETHMAC_TXINT_POS) & ETH_17_GETHMAC_ONE);
    /*If Tx interrupt is enabled*/
    /* [cover parentID={AFC03DF4-899E-4d2a-A579-95089C1EE1EE}][/cover] */
    if(IntEnabled == ETH_17_GETHMAC_ZERO)
    {   /* Local function to confirm all successfully trasmitted frames */
        /* [cover parentID={A9FE88EC-974B-42bb-8ECA-0AE4936A50A5}][/cover] */
        Eth_17_lConfirmTxFrames(CtrlIdx);
    }
  }
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={543D64FD-CF7F-4dda-97EE-6B93519CA98E}]  **
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
/*******************************************************************************
                           Ethernet Frame Format
+----------+-------------+--------------+-----------------------+--------------+
+  DesAddr +  SourceAddr + FrameLen /   + Frame Data /          +   CheckSum   +
+ (6Bytes) +   (6Bytes)  + Type(2Bytes) + Payload(46-1500Bytes) +    (4Bytes)  +
+----------+-------------+--------------+-----------------------+--------------+
*******************************************************************************/
/*CYCLOMATIC_Eth_17_GEthMac_Transmit_JUSTIFICATION: Function performs DET check
   for Init, Controller Init, Invalid Cntrl Index, Outof bound Buffer Index,
   Invalid Buffer Index, Invalid Length and Invalid Physical address pointer.
   For better readability and understanding, it is decided
   to keep all the checks within the same function. */
Std_ReturnType Eth_17_GEthMac_Transmit(
             const uint8 CtrlIdx, const Eth_BufIdxType BufIdx,
             const Eth_FrameType FrameType, const boolean TxConfirmation,
             const uint16 LenByte, const uint8* const PhysAddrPtr)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint32 DevError = ETH_17_GETHMAC_E_DET_NO_ERR;
#if((ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON) || \
                        (ETH_17_GETHMAC_IPV4_CHECKSUMOFFLOAD_ENABLE == STD_ON))
  const Eth_17_GEthMac_CntrlStatusType *EthLocalCoreStatusPtr;
#endif
#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
  const Eth_17_GEthMac_CoreCntrlConfigType *EthLocalCntrlCfgPtr;
  uint8 TxBufTotal;
#endif
#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
  /* Check if Eth_17_GEthMac_Init is sucessfull */
  /* [cover parentID={DE007D68-E3F4-4e32-AA7B-C9DFB91B83A9}]
  [/cover] */
  DevError = Eth_17_lDetCheckNoInitStage1(ETH_17_GETHMAC_SID_TRANSMIT);
  /* [cover parentID={D6A6414F-8AC1-461c-B836-9EFE884C20B0}]
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /*  ETH_17_GETHMAC_E_INV_CTRL_IDX  Validate Controller Index*/
    /* [cover parentID={6F98FB15-A6AA-442d-B8AC-9E44DFD7279C}]
    [/cover] */
    DevError = Eth_17_lDetCheckInvalidCtrlIdx( \
                                  CtrlIdx, ETH_17_GETHMAC_SID_TRANSMIT);
  }
  /*If Ctrl idx is Valid*/
  /* [cover parentID={54C8ED67-4B95-4447-A0AB-6752F8CF9EEB}]
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* Check if controller init is Sucessfull in
     Eth_17_GEthMac_SetControllerMode */
    /* [cover parentID={43B8B1A8-533E-409f-B4E8-5DD4E5061ECF}]
    [/cover] */
    DevError = Eth_17_lDetCheckNoInit(ETH_17_GETHMAC_SID_TRANSMIT, CtrlIdx);
  }
  /* [cover parentID={F831EB09-1CE6-4476-B12C-5D1A7B6AA652}]
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* Get controller configuration data */
    EthLocalCntrlCfgPtr = Eth_17_lGetCtrlConfigPtr(CtrlIdx);
    /* Get controller status */
    EthLocalCoreStatusPtr = Eth_17_lGetCtrlStatusPtr(CtrlIdx);
    TxBufTotal = EthLocalCntrlCfgPtr->EthTxBufTotal;
    /* [cover parentID={7F455B9B-25D6-4af2-BF4E-75C4377A44CC}]
    BufIdx(Input parameter) less than Total Tx buffer allocated
    [/cover] */
    /* ETH_17_GETHMAC_E_INV_PARAM if the BufIdx is greater then Tx buff total */
    if(BufIdx >= (Eth_BufIdxType)TxBufTotal)
    {
      /* [cover parentID={179CA8F1-DA8A-420e-8B37-9FCB4A11D468}]
      Report DET error ( Invalid Parameter)
      [/cover] */
      (void)Det_ReportError(ETH_17_GETHMAC_MODULE_ID,ETH_17_GETHMAC_INSTANCE_ID,
                      ETH_17_GETHMAC_SID_TRANSMIT,ETH_17_GETHMAC_E_INV_PARAM);
      DevError = ETH_17_GETHMAC_E_INV_PARAM;
    }
    /* [cover parentID={415246C1-DAB6-4d80-81E2-1F0D086B4D72}]
    BufIdx(Input parameter) is the one allocated to application
    ( Buffer status is USED
    [/cover] */
    /* Check BufIdx is the one which is allocated to application*/
    else if(EthLocalCoreStatusPtr->EthBuffDecPtr->EthTxBuffTablePtr[BufIdx].\
                                      BuffStatus != ETH_17_GETHMAC_BUFFER_USED)
    {
      /* [cover parentID={179CA8F1-DA8A-420e-8B37-9FCB4A11D468}]
      Report DET error ( Invalid Parameter)
      [/cover] */
      (void)Det_ReportError(ETH_17_GETHMAC_MODULE_ID,ETH_17_GETHMAC_INSTANCE_ID,
                      ETH_17_GETHMAC_SID_TRANSMIT,ETH_17_GETHMAC_E_INV_PARAM);
      DevError = ETH_17_GETHMAC_E_INV_PARAM;
    }
    /* [cover parentID={C14C84C0-4EDC-4064-A7A0-44D16158E8B6}]
    [/cover] */
    else if(LenByte > EthLocalCoreStatusPtr->EthBuffDecPtr->\
                                  EthTxBuffTablePtr[BufIdx].BuffLengthReqstd)
    {
      /* Check if LenByte parameter values is greater than buffer length allocated
      to this BufIdx, in ProvideTxBuffer API  */
      /* [cover parentID={179CA8F1-DA8A-420e-8B37-9FCB4A11D468}]
      Report DET error ( Invalid Parameter)
      [/cover] */
      (void)Det_ReportError(ETH_17_GETHMAC_MODULE_ID,ETH_17_GETHMAC_INSTANCE_ID,
                      ETH_17_GETHMAC_SID_TRANSMIT,ETH_17_GETHMAC_E_INV_PARAM);
      DevError = ETH_17_GETHMAC_E_INV_PARAM;
    }
    else
    {
      /*Do nothing. No actions required*/
    }
  }
  /* [cover parentID={52C0788F-C7B7-46eb-B3C8-D359976E6819}]
  No DET
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* [cover parentID={D1671162-0EFF-47d9-98B3-00DA5564FDAC}]
    Validate PhysAddrPtr Pointer
    [/cover] */
    /*  ETH_17_GETHMAC_E_PARAM_POINTER */
    DevError = Eth_17_lDetCheckInvalidPointer(PhysAddrPtr,
                                                   ETH_17_GETHMAC_SID_TRANSMIT);
  }

#endif /* End of ETH_17_GETHMAC_DEV_ERROR_DETECT */

#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={55E06B65-33F1-4726-9DB3-2FE7205C5923}]
  Valid PhysAddrPtr Pointer
  [/cover] */
  /* [cover parentID={4225D012-A5CE-4315-B4DC-18B8FDA0D9C6}]
  Merge
  [/cover] */
  /* [cover parentID={A810AF69-BA07-4387-B830-F7CB78E521C7}]
  Merge
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
#endif
  {
    /* [cover parentID={F7653609-CA75-458f-9190-86EA8D2442BD}]
    Validate Controller Mode
    [/cover] */
    /* ETH_17_GETHMAC_E_INV_MODE */
    DevError = Eth_17_lDetCheckMode(ETH_17_GETHMAC_SID_TRANSMIT,CtrlIdx);
  }
  /* [cover parentID={7683E776-2A4F-4508-AF72-EB228D5F03FD}]
  Valid Controller Mode
  [/cover] */
  if( DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
#if ((ETH_17_GETHMAC_IPV4_CHECKSUMOFFLOAD_ENABLE == STD_ON  ) || \
     (ETH_17_GETHMAC_TCP_CHECKSUMOFFLOAD_ENABLE  == STD_ON  ) || \
     (ETH_17_GETHMAC_UDP_CHECKSUMOFFLOAD_ENABLE  == STD_ON  ) || \
     (ETH_17_GETHMAC_ICMP_CHECKSUMOFFLOAD_ENABLE == STD_ON  ))
      /* Get controller status */
      EthLocalCoreStatusPtr = Eth_17_lGetCtrlStatusPtr(CtrlIdx);
    Eth_17_lCheckForICMPV4Frame(BufIdx,FrameType,EthLocalCoreStatusPtr);
#endif
    Eth_17_lTransmit(CtrlIdx, BufIdx, FrameType,TxConfirmation, LenByte, \
                                                                  PhysAddrPtr);
    /* [cover parentID={1EF38345-324C-4199-9A48-C9ECF0300863}]
    Set RetValue = E_OK
    [/cover] */
    RetVal = E_OK;
  }
  else
  {
    /* [cover parentID={2637FB0B-D144-4154-955F-DA63CAA36B20}]
    Set RetValue = E_NOT_OK
    [/cover] */
    /* Controller mode is Not ACTIVE */
    RetVal = E_NOT_OK;
  }
  return RetVal;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={0424ED48-50C5-4171-BCF5-EF09D2166ABA}]  **
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

/*******************************************************************************
                           Ethernet Frame Format
+----------+-------------+--------------+-----------------------+--------------+
+  DesAddr +  SourceAddr + FrameLen /   + Frame Data /          +   CheckSum   +
+ (6Bytes) +   (6Bytes)  + Type(2Bytes) + Payload(46-1500Bytes) +    (4Bytes)  +
+----------+-------------+--------------+-----------------------+--------------+
*******************************************************************************/
void Eth_17_GEthMac_Receive(const uint8 CtrlIdx,
                            Eth_RxStatusType* const RxStatusPtr)
{
  uint32 FrameNofityStatus;
  const Eth_17_GEthMac_CoreCntrlConfigType *EthLocalCntrlCfgPtr;
  const Eth_17_GEthMac_CntrlStatusType *EthLocalCoreStatusPtr;
  Ifx_GETH *EthCntrlAdd;
  uint8 IntEnabled;

#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
  /* Check if Eth_17_GEthMac_Init is sucessfull */
  /* [cover parentID={9FA9E1BE-272C-4b81-B590-11AA74EC04BD}]
  [/cover] */
  DevError = Eth_17_lDetCheckNoInitStage1(ETH_17_GETHMAC_SID_RECEIVE);
  /* [cover parentID={7F1B9561-DA87-4cfe-8479-AC54B11433D0}]
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* ETH_17_GETHMAC_E_INV_CTRL_IDX Check if CtrlIdx is valid */
    /* [cover parentID={D770157B-240E-4204-8B56-9A8FDBF8352F}]
    [/cover] */
    DevError = Eth_17_lDetCheckInvalidCtrlIdx( \
                                  CtrlIdx, ETH_17_GETHMAC_SID_RECEIVE);
  }
  /* ETH_17_GETHMAC_E_NOT_INITIALIZED */
  /* [cover parentID={A22B9E94-7BEA-4d91-873A-E21A16A2969E}]
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* Check if controller init is Sucessfull in
                                           Eth_17_GEthMac_SetControllerMode */
    /* [cover parentID={A922CE8F-B2E0-4fdd-93F6-08663CDB90BC}]
    [/cover] */
    DevError = Eth_17_lDetCheckNoInit(ETH_17_GETHMAC_SID_RECEIVE, CtrlIdx);
  }
  /* [cover parentID={93912332-14D7-4c1b-9CB4-FF25A5D50C45}]
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* [cover parentID={518893E9-3212-478e-90A4-6EAA578BA975}]
    Validate Controller Mode
    [/cover] */
    /* ETH_17_GETHMAC_E_INV_MODE */
    DevError = Eth_17_lDetCheckMode(ETH_17_GETHMAC_SID_RECEIVE,CtrlIdx);
  }

  /* [cover parentID={E652311C-5214-4270-ADAE-2977BCA70CEF}]
  Valid Controller Mode
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* ETH_17_GETHMAC_E_PARAM_POINTER */
    /* [cover parentID={81203E14-35D8-485f-ADA3-31174F222078}]
    NULL pointer check
    [/cover] */
    DevError = Eth_17_lDetCheckInvalidPointer(RxStatusPtr, \
                                              ETH_17_GETHMAC_SID_RECEIVE);
  }

  /* [cover parentID={AC04B36D-C20B-4139-91D9-B9DC813FC7C0}]
  Valid RxStatusPtr Pointer
  [/cover] */
  /* [cover parentID={4C97735C-2CF4-45e8-9BD4-67083AFB88BA}]
  Merge
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
#endif/* End of ETH_17_GETHMAC_DEV_ERROR_DETECT */
  {
    /*initialize the RxStatusPtr to ETH_NOT_RECEIVED*/
    *RxStatusPtr = ETH_NOT_RECEIVED;
    /* Get controller configuration data */
    EthLocalCntrlCfgPtr = Eth_17_lGetCtrlConfigPtr(CtrlIdx);
    /* Get controller status */
    EthLocalCoreStatusPtr = Eth_17_lGetCtrlStatusPtr(CtrlIdx);
    /* get base address of the indexed controller */
    EthCntrlAdd = Eth_GEthMacCntrl[EthLocalCntrlCfgPtr->EthCntrlIdx];
    IntEnabled = (uint8)((EthLocalCntrlCfgPtr->EthCntrlProperties >> \
                           ETH_17_GETHMAC_RXINT_POS) & ETH_17_GETHMAC_ONE);
    /* If Rx ISR is enabled then Polling mode disabled */
    /* [cover parentID={A3473375-B2BF-40a3-B8D5-BD68CD710A6D}]
    Rx Interrupt Enabled
    [/cover] */
    if(IntEnabled == ETH_17_GETHMAC_ZERO)
    {
      /* [cover parentID={5C9DEC98-0844-4639-85C7-B9A5446DE31D}]
      Check if New frame received and indicate to EtfIf driver
      [/cover] */
      FrameNofityStatus = Eth_17_lReceiveFrames(CtrlIdx);
      /* [cover parentID={E0A716E2-41C2-49ce-95CA-B306E7B17ABD}]
      New Frame received
      [/cover] */
      if(ETH_17_GETHMAC_ONE == FrameNofityStatus)
      {
        /* [cover parentID={CA7BF4AF-7FD4-4709-A3AA-EF92EDCC2659}]
        Some more frames available
        [/cover] */
        if((Eth_17_lIsNextFrameAvailable(CtrlIdx)) == TRUE)
        {
          /* [cover parentID={811C4CA0-7743-4524-BE5A-5B8CD76E6573}]
          Fill output parameter RxStatusPtr as MORE_DATA_AVAILABLE
          [/cover] */
          *RxStatusPtr = ETH_RECEIVED_MORE_DATA_AVAILABLE;
        }
        else
        {
          /* [cover parentID={2C090E69-21A6-4d2e-842F-B3B194E9CFF1}]
          Fill output parameter RxStatusPtr as RECEIVED
          (But no more data available)
          [/cover] */
          *RxStatusPtr = ETH_RECEIVED;
        }
      }
      else
      {
        /* [cover parentID={F728CB0F-2B6E-4700-9FF6-601B3E7D7AE4}]
        Fill output parameter RxStatusPtr as NOT_RECEIVED
        [/cover] */
        *RxStatusPtr = ETH_NOT_RECEIVED;
      }
    }
    /*Update Rx- DMA-CH0 Descriptor tail pointer to issue poll demand command*/
    /* [cover parentID={2A2034DA-98BB-4826-9FC0-2754682039D4}][/cover] */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion pointer to a
     integer type is performed to assign last buffer address to tail pointer
     register. This is the intended design and valid as per DMA hardware
     design. There are no side effects seen by violating this rule.*/
    /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from pointer to unsigned long
      is performed to to assign last buffer address to tail pointer
     register. This is the intended design and valid as per DMA hardware
     design. There are no side effects seen by violating this rule.*/
    EthCntrlAdd->DMA_CH[0].RXDESC_TAIL_POINTER.U = \
            (uint32)(&(EthLocalCoreStatusPtr->EthBuffDecPtr->\
                        EthDmaRxDescPtr[EthLocalCntrlCfgPtr->EthRxBufTotal]));
  }
}

#if (ETH_17_GETHMAC_UPDATE_PHY_ADDR_FILTER_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={DB99BA9F-2C50-47f8-A634-B3FA5DD62E91}]  **
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
Std_ReturnType Eth_17_GEthMac_UpdatePhysAddrFilter( const uint8 CtrlIdx,
                             const uint8* const PhysAddrPtr,
                             const Eth_FilterActionType Action)
{
  Std_ReturnType RetVal = E_NOT_OK;
  Ifx_GETH *EthCntrlAdd;
  const Eth_17_GEthMac_CoreCntrlConfigType *EthLocalCntrlCfgPtr;
  Eth_17_GEthMac_CntrlStatusType *EthLocalCoreStatusPtr;

#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
  /* Check if Eth_17_GEthMac_Init is sucessfull */
  /* [cover parentID={8B1F69A8-CDEC-40ce-A465-437B01C3D092}]
  [/cover] */
  DevError = Eth_17_lDetCheckNoInitStage1(ETH_17_GETHMAC_SID_UPDATEFILTER);
  /* [cover parentID={00F69D98-48FF-421b-8AD4-6F236FEDAD27}]
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* ETH_17_GETHMAC_E_INV_CTRL_IDX Check if CtrlIdx is valid */
    /* [cover parentID={CB64499A-9B52-4cb8-87C6-15FB8CD59271}]
    [/cover] */
    DevError = Eth_17_lDetCheckInvalidCtrlIdx( \
                                  CtrlIdx, ETH_17_GETHMAC_SID_UPDATEFILTER);
  }

  /* [cover parentID={2E0D6FD2-52F1-4628-8305-EED2D7659203}]
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
     /* Check if controller init is Sucessfull in
     Eth_17_GEthMac_SetControllerMode */
     /* [cover parentID={2AACA8E4-80C1-4473-86E3-87719F784CE8}]
     [/cover] */
    DevError = Eth_17_lDetCheckNoInit(ETH_17_GETHMAC_SID_UPDATEFILTER, \
                                                                      CtrlIdx);
  }
  /* [cover parentID={24A84B47-8ED9-48ec-A769-5D4045336CC4}]
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* [cover parentID={C7D8670C-2A03-4fff-82B8-40B685D5AD83}]
    Validate Physical Address Pointer
    [/cover] */
    /*  ETH_17_GETHMAC_E_PARAM_POINTER. */
    DevError = Eth_17_lDetCheckInvalidPointer(PhysAddrPtr,
                                              ETH_17_GETHMAC_SID_UPDATEFILTER);
  }
  /* [cover parentID={270B6400-983D-4326-A437-2A7421C36B9F}]
  Valid Physical Address Pointer
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* Check the paramter Action is valid    */
    /* [cover parentID={E9CD4714-9FCA-464f-BA78-C5186E3B76E3}]
    Paramter Action is not valid
    [/cover] */
    if((Action != ETH_ADD_TO_FILTER) && (Action != ETH_REMOVE_FROM_FILTER))
    {
      /* [cover parentID={0B8C3F03-A400-420d-8EA6-F65BC476C28A}]
      [/cover] */
      (void)Det_ReportError(ETH_17_GETHMAC_MODULE_ID,ETH_17_GETHMAC_INSTANCE_ID,
                    ETH_17_GETHMAC_SID_UPDATEFILTER,ETH_17_GETHMAC_E_INV_PARAM);
      DevError = ETH_17_GETHMAC_E_INV_PARAM;
    }
  }
  /* [cover parentID={E9CD4714-9FCA-464f-BA78-C5186E3B76E3}]
  Paramter Action is valid
  [/cover] */
  /* [cover parentID={9068375D-10B5-4ced-9EA1-8699D3E8B197}]
  Merge
  [/cover] */
  if(DevError != ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    RetVal = E_NOT_OK;
  }
  else
#endif /* End of ETH_17_GETHMAC_DEV_ERROR_DETECT */
  {
    /* Get controller configuration data */
    EthLocalCntrlCfgPtr = Eth_17_lGetCtrlConfigPtr(CtrlIdx);
    /* Get controller status */
    EthLocalCoreStatusPtr = Eth_17_lGetCtrlStatusPtr(CtrlIdx);
    /* get base address of the controller */
    EthCntrlAdd = Eth_GEthMacCntrl[EthLocalCntrlCfgPtr->EthCntrlIdx];
    /* [cover parentID={E9E9EF42-AAA8-43a9-9598-6F82AE949761}]
    Check if Physical address is Broadcast address
    [/cover] */
    /* [cover parentID={ABF9A36F-F7FE-4b9b-A09F-3ED36765D9B2}]
    Physical Address is broadcast address
    [/cover] */
    if(Eth_17_lIsBroadcastAddress(PhysAddrPtr) == TRUE)
    {
      /* [cover parentID={EB8B8EEF-2525-4b37-935B-8C89B0D7729C}]
      Open filter completely to receive all frames
      [/cover] */
      /* Open filter completely to receive all frames */
      EthCntrlAdd->MAC_PACKET_FILTER.U = \
                         (uint32)(ETH_17_GETHMAC_MAC_PACKT_FILT_OPEN_CONF);
      Eth_17_lClearAllAddressFilters(CtrlIdx);
      /* Set FilterOpenStatus as TRUE*/
      EthLocalCoreStatusPtr->EthRunTimeOpertnData.AddressFilterOpenStat = TRUE;
      RetVal = E_OK;
    }
    /* [cover parentID={FB2C3C93-90C4-4661-A807-B5B0F6FD021D}]
    Check if Physical address is all Zeros
    [/cover] */
    /* [cover parentID={2DB38013-6B42-4b04-BE71-3669ED9AA102}]
    Physical Address is all Zeros
    [/cover] */
    else if(Eth_17_lIsAllZeroAddress(PhysAddrPtr) == TRUE)
    {
      /* [cover parentID={B7F31366-8566-4cd6-8A43-00991A1D79CF}]
      Limit MAC filter to the controllers unique unicast MAC address and Set
      FilterOpenStatus as FALSE
      [/cover] */
      /*  Limit MAC filter to the controllers unique unicast MAC address*/
      EthCntrlAdd->MAC_PACKET_FILTER.U = \
                              (uint32)ETH_17_GETHMAC_MAC_PACKT_FILT_INIT_CONF;
      Eth_17_lClearAllAddressFilters(CtrlIdx);

      /* Insert delay for back to back register writes */
      Eth_17_lBkToBkRegWrInsrtDly(EthLocalCntrlCfgPtr->EthBkRegWrWaitTime);

      /* Set the configured MAC address in MAC Address register 0 */
      Eth_17_lSetPhysAddr((uint8*)EthLocalCoreStatusPtr->EthRunTimeOpertnData.\
                        EthUnicastMacAddress,EthLocalCntrlCfgPtr->EthCntrlIdx);
      /* Set FilterOpenStatus as FALSE*/
      EthLocalCoreStatusPtr->EthRunTimeOpertnData.AddressFilterOpenStat = \
                                                                         FALSE;
      RetVal = E_OK;
    }
    /* [cover parentID={51041157-92A9-4f9c-AC4D-56B07F8595A4}]
    FilterOpenStatus is TRUE
    [/cover] */
    else if(EthLocalCoreStatusPtr->EthRunTimeOpertnData.AddressFilterOpenStat\
                                                                       == TRUE)
    {
      /* Filter is in Open state and hence it is error case*/
      RetVal = E_NOT_OK;
    }
    /* [cover parentID={996427DA-CD08-4346-8E99-B142F670ED3A}]
    Action Is "Add to Filter"
    [/cover] */
    else if(ETH_ADD_TO_FILTER == Action)
    {
      /* [cover parentID={7192EB58-5F86-4884-930E-6A70098E6E8B}]
      Set RetValue = E_OK
      [/cover] */
      /* [cover parentID={BF1E934C-B15C-4225-B0F3-F0F4479FDC0F}]
      Add the address to the filter
      [/cover] */
      /* Add more address to the filter */
      RetVal = Eth_17_lAddToFilter(PhysAddrPtr,CtrlIdx);
      /* [cover parentID={F7429293-08BD-4ace-900A-5A6B5F0E970E}]
      [/cover] */
      if(RetVal == E_OK)
      {
        /* Configure Mac filter register */
        EthCntrlAdd->MAC_PACKET_FILTER.U = \
                                       ETH_17_GETHMAC_MAC_PACKT_FILT_INIT_CONF;
      }
    }
    /* [cover parentID={5A1AE821-40E6-4c6e-A39A-A920D6732F4C}]
    Action Is "Remove from Filter"
    [/cover] */
    else if(ETH_REMOVE_FROM_FILTER == Action)
    {
      RetVal = Eth_17_lRemoveFromFilter(PhysAddrPtr,CtrlIdx);
    }
    else
    {

#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_OFF)
      /* Requested Action is unknown */
      /* [cover parentID={8C9BBFD9-86BC-411c-B81C-02D6EE7EBAB9}]
      Set RetValue = E_NOT_OK
      [/cover] */
      RetVal = E_NOT_OK;
#endif /*ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_OFF*/

    }
  }
  return RetVal ;
}
#endif /* End for ETH_17_GETHMAC_UPDATE_PHY_ADDR_FILTER_API */

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={A3576DC6-E6A2-48da-8670-4C36BCCFDCF4}]  **
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
void Eth_17_GEthMac_SetPhysAddr( const uint8 CtrlIdx,
                                 const uint8* const PhysAddrPtr)
{
  uint8 LoopCount;
  Eth_17_GEthMac_CntrlStatusType *EthLocalCoreStatusPtr;

#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
  /* Check if Eth_17_GEthMac_Init is sucessfull */
  /* [cover parentID={6A4D9B97-5D87-4b8d-9E82-B673C2E74CC2}][/cover] */
  DevError = Eth_17_lDetCheckNoInitStage1(ETH_17_GETHMAC_SID_SETPHYSADDRESS);
  /* [cover parentID={349CA852-1312-494a-827A-063232A74D66}][/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* ETH_17_GETHMAC_E_INV_CTRL_IDX Check if CtrlIdx is valid */
    /* [cover parentID={882434E7-B164-4f34-B3BC-4F5D8DABC81B}][/cover] */
    DevError = Eth_17_lDetCheckInvalidCtrlIdx( \
                                  CtrlIdx, ETH_17_GETHMAC_SID_SETPHYSADDRESS);
  }

  /* [cover parentID={C4D5EBD6-7B10-4619-B154-C5315D758E84}]
  If controller Index is Valid
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* Check if controller init is Sucessfull in
    Eth_17_GEthMac_SetControllerMode */
    /* [cover parentID={66EEB077-31E9-4ffa-89AC-12303899721F}]
    Check controller initialization
    [/cover] */
    DevError = Eth_17_lDetCheckNoInit(ETH_17_GETHMAC_SID_SETPHYSADDRESS, \
                                                                      CtrlIdx);
  }
  /* [cover parentID={42D0552C-1CA9-4372-9C06-67241B9F8B57}]
    if controller initialization successful
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* [cover parentID={62FABE05-9346-4bb4-8B6B-FC4D7F40905E}]
    Validate Physical Address Pointer
    [/cover] */
    DevError = Eth_17_lDetCheckInvalidPointer(PhysAddrPtr,\
                                            ETH_17_GETHMAC_SID_SETPHYSADDRESS);
  }
  /* [cover parentID={6607DDDE-6266-4c58-B4E6-3742C5D46E26}]
  Valid Physical Address Pointer
  [/cover] */
  /* [cover parentID={B7A0E76C-F331-40f0-BF93-57F57A7C3DC8}]
  Merge
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
#endif /* End of ETH_17_GETHMAC_DEV_ERROR_DETECT */
  {
    /* Get controller status */
    EthLocalCoreStatusPtr = Eth_17_lGetCtrlStatusPtr(CtrlIdx);
    /* Copy the MAC address, which will be used to restore controllers
    unique unicast MAC address while ending promiscuous mode, using API
    Eth_UpdatePhysAddrFilter().*/
    for(LoopCount = ETH_17_GETHMAC_ZERO; \
        LoopCount < ETH_17_GETHMAC_MACADDRESS_LEN; LoopCount++)
    {
      EthLocalCoreStatusPtr->EthRunTimeOpertnData.\
                      EthUnicastMacAddress[LoopCount] = PhysAddrPtr[LoopCount];
    }
    /* [cover parentID={F6DA845D-6823-42b2-B2D9-556B539B78D8}]
    Set the Controller Physical source Address( MAC address)
    [/cover] */
    Eth_17_lSetPhysAddr(PhysAddrPtr,CtrlIdx);
  }
}

#if (ETH_17_GETHMAC_GETDROPCOUNT_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={750F960D-BCAC-4abb-BD92-49AEEA922536}]  **
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
Std_ReturnType Eth_17_GEthMac_GetDropCount( const uint8 CtrlIdx,
                                            const uint8 CountValues,
                                            uint32* const DropCount)
{
  /* [cover parentID={8724DF53-0DC8-41c3-B0BA-52381D1AFBF0}]
  Set RetValue = E_NOT_OK
  [/cover] */
  Std_ReturnType RetValue = E_NOT_OK;
  uint32 LocalDropCountValues[ETH_17_GETHMAC_MAX_DROP_COUNTER_NUM];
  uint32 CountIndex;
  uint32 MissPackOverflowCnt;
  uint32 TotalErronInbPkts;
  uint32 TotalErronOutbPkts;
  const Ifx_GETH *EthCntrlAdd;
  uint8 EthOpMode;
  const Eth_17_GEthMac_CoreCntrlConfigType *EthLocalCntrlCfgPtr;

#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
#endif

#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
  /* Check if Eth_17_GEthMac_Init is sucessfull */
  /* [cover parentID={4F1B4670-4D49-474b-BE2F-5A2542F6128D}]
   Check Driver is initialized
   [/cover] */
  DevError = Eth_17_lDetCheckNoInitStage1(ETH_17_GETHMAC_SID_GETDROPCOUNT);
  /* [cover parentID={5BBD38B1-D8C0-41b2-8F1B-CA6ADB09A04D}]
   Driver Initialized
   [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* [cover parentID={1DEE8D19-C475-4028-AB94-1E6D4E4FB784}]
     Validate Controller Index
     [/cover] */
    /* ETH_17_GETHMAC_E_INV_CTRL_IDX Check if CtrlIdx is valid */
    DevError = Eth_17_lDetCheckInvalidCtrlIdx( \
                                  CtrlIdx, ETH_17_GETHMAC_SID_GETDROPCOUNT);
  }
   /* [cover parentID={D5E820E1-4A3D-4e16-8360-83844914D288}]
   Valid Controller Index
   [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
     /* Check if controller init is Sucessfull in
     Eth_17_GEthMac_SetControllerMode */
    /* [cover parentID={7810EC54-0137-40b2-BA4A-57E8525B04C3}]
    [/cover] */
    DevError = Eth_17_lDetCheckNoInit(ETH_17_GETHMAC_SID_GETDROPCOUNT, CtrlIdx);
  }
  /* [cover parentID={DFC8F4F1-6CE9-4efd-A262-974DE2670DC6}]
   If controller init is successful
   [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* [cover parentID={7164BBE0-5EEC-4a68-8C1E-44DBF5E1A658}]
    Validate DropCount Pointer
    [/cover] */
    /* ETH_17_GETHMAC_E_PARAM_POINTER */
    DevError = Eth_17_lDetCheckInvalidPointer(DropCount, \
               ETH_17_GETHMAC_SID_GETDROPCOUNT);
  }
  /* [cover parentID={9C60A682-E3D5-4315-99E3-2692AC501429}]
  Valid DropCount Pointer
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
#endif /* End of ETH_17_GETHMAC_DEV_ERROR_DETECT */
  {
    EthCntrlAdd = Eth_GEthMacCntrl[CtrlIdx];
    /* Get controller configuration data */
    EthLocalCntrlCfgPtr = Eth_17_lGetCtrlConfigPtr(CtrlIdx);
    EthOpMode = (uint8)((EthLocalCntrlCfgPtr->EthCntrlProperties) >> \
                               ETH_17_GETHMAC_OPMODE_POS) & ETH_17_GETHMAC_ONE;

    /*Info : Reading this register will clear the register*/
    MissPackOverflowCnt =  EthCntrlAdd->MTL_RXQ0.MISSED_PACKET_OVERFLOW_CNT.U;

    /* [cover parentID={05CCFC94-78E0-4c18-8E78-B479005FAAF2}]
    Read corresponding MAC management counter registers and fill DropCount[]
    array(function output parameter) until
    'CountValues'(function input parameter) elements
    [/cover] */

    /*NO:1 --Dropped packets due to buffer overrun. That is, DMA discards the
    packet because of because of Receive queue overflow.
    Info: Counter Clears on register read
    Info: Bit0 to Bit10 indicates count. Hence,Maximum count is 2^11.
    If bit11 is set, it indicates that counter crossed maximum limit.*/
    LocalDropCountValues[ETH_17_GETHMAC_DROP_PKTS_BUFOVERRUN] = (uint32)\
                         (MissPackOverflowCnt & ETH_17_GETHMAC_OVFPKTCNT_MASK);

    /*NO:2 --Dropped packets due to CRC errors. That is, number of
    packets received with CRC error.
    Info: Counter does not clears on register read*/
    LocalDropCountValues[ETH_17_GETHMAC_DROP_PKTS_CRCERROR] = \
                  (uint32)EthCntrlAdd->RX_CRC_ERROR_PACKETS.B.RXCRCERR;

    /*NO:3 --Number of undersize packets which were less than 64 octets long.
    That is packets received with length less than 64 bytes,
    without any errors
    Info: Counter does not clears on register read*/
    LocalDropCountValues[ETH_17_GETHMAC_DROP_PKTS_UNDERSIZE] = \
                   (uint32)EthCntrlAdd->RX_UNDERSIZE_PACKETS_GOOD.B.RXUNDERSZG;

    /*NO:4 --Number of oversize packets which are longer than 1518 octets.
    That is received without errors, with length greater than the maxsize.
    Info: Counter does not clears on register read*/
    LocalDropCountValues[ETH_17_GETHMAC_DROP_PKTS_OVERSIZE] = \
                    (uint32)EthCntrlAdd->RX_OVERSIZE_PACKETS_GOOD.B.RXOVERSZG;

    /*NO:5 --Number of alignment errors, i.e. packets which are received
    and are not an integral number of octets in length and do not pass the CRC.
    That is number of packets received with alignment (dribble) error.
    Info:It is valid only in 10/100 mode.
    Info: Counter does not clears on register read*/
    LocalDropCountValues[ETH_17_GETHMAC_DROP_PKTS_ALIGNERROR] = \
                  (uint32)EthCntrlAdd->RX_ALIGNMENT_ERROR_PACKETS.B.RXALGNERR;

    /*NO:6 -SQE test error.
    Info: This error counter is not available from Hardware*/
    LocalDropCountValues[ETH_17_GETHMAC_DROP_PKTS_SQETESTERROR] = \
                                          ETH_17_GETHMAC_COUNTER_NOT_AVAILABLE;

    /*NO:7 --Number of inbound packets which were chosen to be discarded even
    though no errors had been detected. One possible reason for discarding such
    a packet could be to free up buffer space.
    Info: This item is filled with count that the number of packets discarded
    because of Receive queue overflow. That is Receive queue overflow is only
    reason considered.
    Hence, currently this item and
    LocalDropCountValues[ETH_17_GETHMAC_DROP_PKTS_BUFOVERRUN]
    will be having same value.
    Info: Counter Clears on register read*/
    LocalDropCountValues[ETH_17_GETHMAC_DROP_PKTS_RECV_Q_OVERFLOW] = (uint32)\
                         (MissPackOverflowCnt & ETH_17_GETHMAC_OVFPKTCNT_MASK);

    /*NO:8 -Total number of erroneous inbound packets.
    Info:This item is filled with counter that wihch is addition of all receive
    error counters available from hardware*/
    TotalErronInbPkts = (uint32)(EthCntrlAdd->RX_CRC_ERROR_PACKETS.B.RXCRCERR);
    TotalErronInbPkts = (uint32)(TotalErronInbPkts + \
                      EthCntrlAdd->RX_ALIGNMENT_ERROR_PACKETS.B.RXALGNERR);
    TotalErronInbPkts = (uint32)(TotalErronInbPkts + \
                           EthCntrlAdd->RX_RUNT_ERROR_PACKETS.B.RXRUNTERR);
    TotalErronInbPkts = (uint32)(TotalErronInbPkts + \
                          EthCntrlAdd->RX_JABBER_ERROR_PACKETS.B.RXJABERR);
    TotalErronInbPkts = (uint32)(TotalErronInbPkts + \
                          EthCntrlAdd->RX_LENGTH_ERROR_PACKETS.B.RXLENERR);
    TotalErronInbPkts = (uint32)(TotalErronInbPkts + \
                   EthCntrlAdd->RX_OUT_OF_RANGE_TYPE_PACKETS.B.RXOUTOFRNG);
    TotalErronInbPkts = (uint32)(TotalErronInbPkts + \
                        EthCntrlAdd->RX_RECEIVE_ERROR_PACKETS.B.RXRCVERR);
    LocalDropCountValues[ETH_17_GETHMAC_DROP_ERRONEOUS_INB_PKTS]= \
                                                        TotalErronInbPkts;

    /*NO:9 -The number of outbound packets which were chosen to be discarded
    even though no errors had been detected.
    Info: This item is filled with number of packets aborted because of packets
    underflow error*/
    LocalDropCountValues[ETH_17_GETHMAC_DROP_OUTB_PKTS] = \
                (uint32)EthCntrlAdd->TX_UNDERFLOW_ERROR_PACKETS.B.TXUNDRFLW;

    /*NO:10 -Total number of erroneous outbound packets.
    Info: This item is filled with counter that which is addition of all
    transmit error counters available from hardware*/
    TotalErronOutbPkts = (uint32)(EthCntrlAdd->TX_LATE_COLLISION_PACKETS.B.\
                                                                    TXLATECOL);
    TotalErronOutbPkts = (uint32)(TotalErronOutbPkts + \
                       EthCntrlAdd->TX_EXCESSIVE_COLLISION_PACKETS.B.TXEXSCOL);
    TotalErronOutbPkts = (uint32)(TotalErronOutbPkts + \
                               EthCntrlAdd->TX_CARRIER_ERROR_PACKETS.B.TXCARR);
    TotalErronOutbPkts = (uint32)(TotalErronOutbPkts + \
                          EthCntrlAdd->TX_EXCESSIVE_DEFERRAL_ERROR.B.TXEXSDEF);
    LocalDropCountValues[ETH_17_GETHMAC_DROP_ERRONEOUS_OUTB_PKTS] = \
                                                            TotalErronOutbPkts;

    /* [cover parentID={4E9990E5-B71F-46aa-95C3-1C1F6B8B9B91}]
    Read Half Duplex corresponding MAC management counter registers and fill
    DropCount[] array( Function output parameter)
    [/cover] */
   if( EthOpMode == ETH_17_GETHMAC_HALF_DUPLEX)
   {
     /*NO:11 -Single collision frames. That is,Number of successfully
     transmitted packets after a single collision.
     Info: This error counter is applicable only in Half Duplex mode
     Info: Counter does not clears on register read*/
     LocalDropCountValues[ETH_17_GETHMAC_SINGLE_COLLISION_PKTS] = \
            (uint32)EthCntrlAdd->TX_SINGLE_COLLISION_GOOD_PACKETS.B.TXSNGLCOLG;

     /*NO:12 -Multiple collision frames.
     That is,Number of successfully transmitted packets after multiple
     collision. Info: This error counter is applicable only in Half Duplex mode
     Info: Counter does not clears on register read*/
     LocalDropCountValues[ETH_17_GETHMAC_MULTIPLE_COLLISION_PKTS] = \
          (uint32)EthCntrlAdd->TX_MULTIPLE_COLLISION_GOOD_PACKETS.B.TXMULTCOLG;

     /*NO:13 -Number of deferred transmission.First transmission attempt on a
     particular interface is delayed because the medium is busy.
     That is,Number of successfully transmitted packets after a deferral.
     Info: This error counter is applicable only in Half Duplex mode
     Info: Counter does not clears on register read*/
     LocalDropCountValues[ETH_17_GETHMAC_DEFERRED_TRANSMISSION_PKTS] = \
                            (uint32)EthCntrlAdd->TX_DEFERRED_PACKETS.B.TXDEFRD;

     /*NO:14 -Number of late collisions.
     That is,Number of packets aborted because of late collision error.
     Info: This error counter is applicable only in Half Duplex mode
     Info: Counter does not clears on register read*/
     LocalDropCountValues[ETH_17_GETHMAC_LATE_COLLISION_PKTS] = \
                    (uint32)EthCntrlAdd->TX_LATE_COLLISION_PACKETS.B.TXLATECOL;
   }
   else
   {
     /* NO:11 to 14 are not available in Full Duplex mode. */
     LocalDropCountValues[ETH_17_GETHMAC_SINGLE_COLLISION_PKTS] = \
                                          ETH_17_GETHMAC_COUNTER_NOT_AVAILABLE;
     LocalDropCountValues[ETH_17_GETHMAC_MULTIPLE_COLLISION_PKTS] = \
                                          ETH_17_GETHMAC_COUNTER_NOT_AVAILABLE;
     LocalDropCountValues[ETH_17_GETHMAC_DEFERRED_TRANSMISSION_PKTS] = \
                                          ETH_17_GETHMAC_COUNTER_NOT_AVAILABLE;
     LocalDropCountValues[ETH_17_GETHMAC_LATE_COLLISION_PKTS] = \
                                          ETH_17_GETHMAC_COUNTER_NOT_AVAILABLE;
   }
    /* [cover parentID={05CCFC94-78E0-4c18-8E78-B479005FAAF2}]
    Read corresponding MAC management counter registers and fill DropCount[]
    array(function output parameter) until
    'CountValues'(function input parameter) elements
    [/cover] */
    /* [cover parentID={4E9990E5-B71F-46aa-95C3-1C1F6B8B9B91}]
    Read Half Duplex corresponding MAC management counter registers and fill
    DropCount[] array( Function output parameter)
    [/cover] */
    /* Fill out parameter DropCount[] array with Error count values, until
    number of CountValues (input parameter)*/
    for(CountIndex = ETH_17_GETHMAC_ZERO; \
       ((CountIndex < CountValues) && \
       (CountIndex < ETH_17_GETHMAC_MAX_DROP_COUNTER_NUM)); CountIndex++)
    {
      DropCount[CountIndex] = LocalDropCountValues[CountIndex];
    }
    /* [cover parentID={5E6DB25A-0F38-48b3-B870-92265E065C23}]
    Input parameter'CountValues' > ETH_17_GETHMAC_MAX_DROP_COUNTER_NUM (14)
    [/cover] */
    if ( CountValues > (uint8)ETH_17_GETHMAC_MAX_DROP_COUNTER_NUM)
    {
      /*Fill rest of DropCount[] array as ETH_17_GETHMAC_COUNTER_NOT_AVAILABLE*/
      for(CountIndex = ETH_17_GETHMAC_MAX_DROP_COUNTER_NUM; \
          CountIndex < CountValues; CountIndex++)
      {
       /* [cover parentID={BCCAB357-302B-41c1-8D38-903F472D042D}]
        Fill reset of the elements of DropCount[] array
        as ETH_17_GETHMAC_COUNTER_NOT_AVAILABLE
        [/cover] */
        DropCount[CountIndex] = ETH_17_GETHMAC_COUNTER_NOT_AVAILABLE;
      }
    }
    /* [cover parentID={F7627624-A957-40d1-A314-A89DB91A326E}]
    Set RetValue = E_OK
    [/cover] */
    RetValue = E_OK;
  }
   /* [cover parentID={DDCBAB4D-6DB0-4045-9975-877C83CC37BB}]
   Merge
   [/cover] */
  return RetValue;
}
#endif/* End for ETH_17_GETHMAC_GETDROPCOUNT_API */

#if (ETH_17_GETHMAC_GETETHERSTATS_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={7127DA4D-FABC-409e-A84F-2BD8877C2D6B}]  **
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
Std_ReturnType Eth_17_GEthMac_GetEtherStats(const uint8 CtrlIdx,
                                            uint32* const etherStats)
{
  /* [cover parentID={80A34A31-0592-4e3d-8129-C8EB8F74B97B}]
  Set RetValue = E_NOT_OK
  [/cover] */
  Std_ReturnType RetValue = E_NOT_OK;
  uint32 MissPackOverflowCnt;
  const Ifx_GETH *EthCntrlAdd;
  uint8 EthOpMode;
  const Eth_17_GEthMac_CoreCntrlConfigType *EthLocalCntrlCfgPtr;
  uint32 EthStatsTotalCollisions;

#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
#endif

#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
  /* Check if Eth_17_GEthMac_Init is sucessfull */
  /* [cover parentID={4DA67753-3033-41b2-B2CD-1035E71CC662}]
   Check Driver is initialized
   [/cover] */
  DevError = Eth_17_lDetCheckNoInitStage1(ETH_17_GETHMAC_SID_GETETHERSTATS);
  /* [cover parentID={E95B6750-5740-4f14-906E-015E058E8BBC}]
   Driver Initialized
   [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* ETH_17_GETHMAC_E_INV_CTRL_IDX Check if CtrlIdx is valid */
    /* [cover parentID={53A8FF9A-F953-4991-ACC2-F984785B4BF8}]
     Validate Controller Index
     [/cover] */
    DevError = Eth_17_lDetCheckInvalidCtrlIdx( \
                                  CtrlIdx, ETH_17_GETHMAC_SID_GETETHERSTATS);
  }
  /* Check if controller init is Sucessfull in Eth_17_GEthMac_SetControllerMode */
  /* [cover parentID={52209829-5F73-4128-9F39-D9527DF1697A}]
   Valid Controller Index
   [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  { /* [cover parentID={615252E2-35AC-4e38-9C3F-EC27FE756252}]
     [/cover] */
    DevError = Eth_17_lDetCheckNoInit(ETH_17_GETHMAC_SID_GETETHERSTATS, \
                                                                      CtrlIdx);
  }
   /* [cover parentID={4403C4AB-3023-4ed9-A405-72FEAE425720}]
   If Controller init is successful
   [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
   /* [cover parentID={9ADDDD7B-ECF3-4d7b-95DB-90CF724E40A9}]
    Validate etherStats Pointer
    [/cover] */
    /* ETH_17_GETHMAC_E_PARAM_POINTER */
    DevError = Eth_17_lDetCheckInvalidPointer(etherStats, \
                                             ETH_17_GETHMAC_SID_GETETHERSTATS);
  }
  /* [cover parentID={20B862DC-6C74-4ed3-BE58-AD4D07AD68AF}]
  Valid etherStats Pointer
  [/cover] */
  /* [cover parentID={E087F441-7425-4ddc-B22A-A26DC819E032}]
  Merge
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
#endif /* End of ETH_17_GETHMAC_DEV_ERROR_DETECT */
  {
    EthCntrlAdd = Eth_GEthMacCntrl[CtrlIdx];
    /* Get controller configuration data */
    EthLocalCntrlCfgPtr = Eth_17_lGetCtrlConfigPtr(CtrlIdx);
    EthOpMode = (uint8)((EthLocalCntrlCfgPtr->EthCntrlProperties) >> \
                               ETH_17_GETHMAC_OPMODE_POS) & ETH_17_GETHMAC_ONE;
    MissPackOverflowCnt =  EthCntrlAdd->MTL_RXQ0.MISSED_PACKET_OVERFLOW_CNT.U;

    /* [cover parentID={B8FC0531-8B73-4d2f-B617-48297AD74CD7}]
    Read corresponding MAC management counter registers and fill etherStats[]
    array( Function output parameter)
    [/cover] */
    /*NO:1 --etherStatsDropEvents.
    That is,this counter is addition of( from Q0),
    number of packes DMA discards because of buffer unavailability and
    number of packets discarded because of Receive queue overflow.
    Info: Counter Clears on register read.*/
    etherStats[ETH_17_GETHMAC_STAT_DROP_EVENTS] = \
              (uint32)(MissPackOverflowCnt & ETH_17_GETHMAC_OVFPKTCNT_MASK);
    etherStats[ETH_17_GETHMAC_STAT_DROP_EVENTS] = \
                              (etherStats[ETH_17_GETHMAC_STAT_DROP_EVENTS]+ \
             ((uint32)((MissPackOverflowCnt & ETH_17_GETHMAC_MISPKTCNT_MASK)\
                                       >> ETH_17_GETHMAC_MISPKTCNT_POSITION)));

    /*NO:2 --etherStatsOctets.
    That is number of bytes received, exclusive of preamble, in good and
    bad packets.
    Info: Counter does not clears on register read*/
    etherStats[ETH_17_GETHMAC_STAT_OCTETS] = \
                                (uint32)EthCntrlAdd->RX_OCTET_COUNT_GOOD_BAD.U;

    /*NO:3 --etherStatsPkts.
    That is number of good and bad packets received.
    Info: Counter does not clears on register read*/
    etherStats[ETH_17_GETHMAC_STAT_PKTS] = \
                      (uint32)EthCntrlAdd->RX_PACKETS_COUNT_GOOD_BAD.B.RXPKTGB;

    /*NO:4 --etherStatsBroadcastPkts.
    That is number of good broadcast packets received.
    Info: Counter does not clears on register read*/
    etherStats[ETH_17_GETHMAC_STAT_BROADCAST_PKTS] = \
                    (uint32)EthCntrlAdd->RX_BROADCAST_PACKETS_GOOD.B.RXBCASTG;

    /*NO:5 --etherStatsMulticastPkts.
    That is number of good multicast packets received.
    Info: Counter does not clears on register read*/
    etherStats[ETH_17_GETHMAC_STAT_MULTICAST_PKTS] = \
                    (uint32)EthCntrlAdd->RX_MULTICAST_PACKETS_GOOD.B.RXMCASTG;

    /*NO:6 --etherStatsCrcAlignErrors.
    This counter is addition of,
    number of packets received with CRC error and
    number of packets received with alignment(dribble) error.
    Info: Alignment Error is valid only in 10/100 mode.
    Info: Counter does not clears on register read*/
    etherStats[ETH_17_GETHMAC_STAT_CRC_ALIGN_ERRORS] = \
                         (uint32)EthCntrlAdd->RX_CRC_ERROR_PACKETS.B.RXCRCERR;
    etherStats[ETH_17_GETHMAC_STAT_CRC_ALIGN_ERRORS] = \
                     (etherStats[ETH_17_GETHMAC_STAT_CRC_ALIGN_ERRORS]+\
                ((uint32)EthCntrlAdd->RX_ALIGNMENT_ERROR_PACKETS.B.RXALGNERR));

    /*NO:7 --etherStatsUndersizePkts.
    That is, number of packets received with length less than 64 bytes,
    without any errors.
    Info: Counter does not clears on register read*/
    etherStats[ETH_17_GETHMAC_STAT_UNDERSIZE_PKTS] = \
                   (uint32)EthCntrlAdd->RX_UNDERSIZE_PACKETS_GOOD.B.RXUNDERSZG;

    /*NO:8 --etherStatsOversizePkts.
    That is, number of packets received without errors, with length
    greater than the maxsize (1,518 bytes or 1,522 bytes for VLAN tagged
    packets.
    Info: Counter does not clears on register read*/
    etherStats[ETH_17_GETHMAC_STAT_OVERSIZE_PKTS] = \
                     (uint32)EthCntrlAdd->RX_OVERSIZE_PACKETS_GOOD.B.RXOVERSZG;
    /*NO:9 --etherStatsFragments.
    As per RFC 2819, the etherStatsFragments is the total number of packets
    received that were less than 64 octets in length (excluding framing bits
    but including FCS octets) and had either a bad Frame Check Sequence
    (FCS) with an integral number of octets (FCS Error) or a bad FCS with
    a non-integral number of octets (Alignment Error).
    The hardware provided count is used, which indicates the number of
    packets received with runt (length less than
    64 bytes and CRC error) error.*/
    etherStats[ETH_17_GETHMAC_STAT_FRAGMENTS] = \
                       (uint32)EthCntrlAdd->RX_RUNT_ERROR_PACKETS.B.RXRUNTERR;

    /*NO:10 --etherStatsJabbers.
    That is, number of giant packets received with length (including CRC)
    greater than 1,518 bytes (1,522 bytes for VLAN tagged) and with CRC error.
    Info: Counter does not clears on register read*/
    etherStats[ETH_17_GETHMAC_STAT_JABBERS] = \
                     (uint32)EthCntrlAdd->RX_JABBER_ERROR_PACKETS.B.RXJABERR;

    /* [cover parentID={ED4C54E6-3929-436f-852E-1C0D807076ED}]
     Read Half Duplex corresponding MAC management counter registers and fill
     etherStats[] array( Function output parameter)
     [/cover] */
    /* [cover parentID={697D8D0C-7DB5-4278-9B4C-B1A3047A07E9}][/cover] */
    if( EthOpMode == ETH_17_GETHMAC_HALF_DUPLEX)
    {
      /*NO:11 --etherStatsCollisions.
      This counter is addition of,
      number of successfully transmitted packets after a single collision,
      number of successfully transmitted packets after multiple collisions and
      number of packets aborted because of late collision error
      Info: This counter is valid only in Half Duplex mode.
      Info: Counter does not clears on register read*/
      EthStatsTotalCollisions = (uint32)\
                             (EthCntrlAdd->TX_SINGLE_COLLISION_GOOD_PACKETS.B.\
                                                                   TXSNGLCOLG);
      EthStatsTotalCollisions = (uint32)(EthStatsTotalCollisions + \
                        EthCntrlAdd->TX_MULTIPLE_COLLISION_GOOD_PACKETS.B.\
                                                                   TXMULTCOLG);
      EthStatsTotalCollisions = (uint32)(EthStatsTotalCollisions + \
                        EthCntrlAdd->TX_LATE_COLLISION_PACKETS.B.TXLATECOL);
      etherStats[ETH_17_GETHMAC_STAT_COLLISIONS] = EthStatsTotalCollisions;
    }
    else
    { /* [cover parentID={6F8671B6-C547-4b81-8EBE-4BA0EA572ACE}][/cover] */
      /* NO:11 is not available in Full Duplex mode. */
      etherStats[ETH_17_GETHMAC_STAT_COLLISIONS] = \
                                          ETH_17_GETHMAC_COUNTER_NOT_AVAILABLE;
    }
    /*NO:12 --etherStatsPkts64Octets.
    That is,number of good and bad packets received with length 64 bytes,
    exclusive of the preamble.
    Info: Counter does not clears on register read*/
    etherStats[ETH_17_GETHMAC_STAT_PKTS_64_OCTETS] = \
                    (uint32)EthCntrlAdd->RX_64OCTETS_PACKETS_GOOD_BAD.B.\
                                                                     RX64OCTGB;
    /*NO:13 --etherStatsPkts65to127Octets.
    That is,number of good and bad packets received with length between
    65 and 127 (inclusive) bytes, exclusive of the preamble
    Info: Counter does not clears on register read*/
    etherStats[ETH_17_GETHMAC_STAT_PKTS_65_127_OCTETS] = \
          (uint32)EthCntrlAdd->RX_65TO127OCTETS_PACKETS_GOOD_BAD.B.\
                                                                 RX65_127OCTGB;

    /*NO:14 --etherStatsPkts128to255Octets.
    That is,number of good and bad packets received with length between
    128 and 255 (inclusive) bytes, exclusive of the preamble.
    Info: Counter does not clears on register read*/
    etherStats[ETH_17_GETHMAC_STAT_PKTS_128_255_OCTETS] = \
        (uint32)EthCntrlAdd->RX_128TO255OCTETS_PACKETS_GOOD_BAD.B.\
                                                                RX128_255OCTGB;

    /*NO:15 --etherStatsPkts256to511Octets.
    That is,number of good and bad packets received with length between
    256 and 511 (inclusive) bytes, exclusive of the preamble.
    Info: Counter does not clears on register read*/
    etherStats[ETH_17_GETHMAC_STAT_PKTS_256_511_OCTETS] = \
        (uint32)EthCntrlAdd->RX_256TO511OCTETS_PACKETS_GOOD_BAD.B.\
                                                                RX256_511OCTGB;

    /*NO:16 --etherStatsPkts512to1023Octets.
    That is,number of good and bad packets received with length between
    512 and 1023 (inclusive) bytes, exclusive of the preamble.
    Info: Counter does not clears on register read*/
    etherStats[ETH_17_GETHMAC_STAT_PKTS_512_1023_OCTETS] = \
      (uint32)EthCntrlAdd->RX_512TO1023OCTETS_PACKETS_GOOD_BAD.B.\
                                                               RX512_1023OCTGB;

    /*NO:17 --etherStatsPkts1024to1518Octets.
    That is,number of good and bad packets received with length between
    1024 and maxsize (inclusive) bytes, exclusive of the preamble.
    Info: This counter covers from 1024 to Max, not only 1024 to 1518
    Info: Counter does not clears on register read*/
    etherStats[ETH_17_GETHMAC_STAT_PKTS_1024_1518_OCTETS] = \
       (uint32)EthCntrlAdd->RX_1024TOMAXOCTETS_PACKETS_GOOD_BAD.B.\
                                                               RX1024_MAXOCTGB;
   /* [cover parentID={EA6ACA6D-B981-4736-9ED8-C044F28B2255}]
   Set RetValue = E_OK
   [/cover] */
    RetValue = E_OK;
  }
  return RetValue;
}
#endif/* End for ETH_17_GETHMAC_GETETHERSTATS_API */

#if(ETH_17_GETHMAC_GLOBALTIMESUPPORT == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={B476FC78-C1FE-48d4-B940-D7647617A843}]  **
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
Std_ReturnType Eth_17_GEthMac_GetCurrentTime(const uint8 CtrlIdx,
                                Eth_TimeStampQualType* const timeQualPtr,
                                Eth_TimeStampType* const timeStampPtr)
{
/* [cover parentID={6A283B9B-DD21-452d-831E-705122BD689E}]
In default, Set RetValue = E_NOT_OK
[/cover] */
  Std_ReturnType RetValue = E_NOT_OK;
  const Ifx_GETH *EthCntrlAdd;
#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
#endif
/* [cover parentID={EAE2A01F-7FAB-45fe-B9E8-9DC6455B7680}]
DET is enabled
[/cover] */
#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)

  /* [cover parentID={3FC8F627-54F8-4fb8-B76A-048AE22E4740}]
   Validate Time stamp Quality pointer (Output parameter)
   [/cover] */
  /* ETH_17_GETHMAC_E_PARAM_POINTER */
  DevError = Eth_17_lDetCheckInvalidPointer(timeQualPtr, \
                                            ETH_17_GETHMAC_SID_GETCURRENTTIME);
  /* [cover parentID={8EBE741F-F617-4c47-BDF6-26BB766E0521}]
  Valid Timestamp Quality Pointer
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* In default Assign time quality as Invalid,if timeQualPtr is not NULL */
    *timeQualPtr = ETH_INVALID;
    /* [cover parentID={04DB96BF-0990-4a88-BFAA-B7851768A419}]
     Validate Time stamp pointer( Output parameter)
     [/cover] */
    /* ETH_17_GETHMAC_E_PARAM_POINTER */
    DevError = Eth_17_lDetCheckInvalidPointer(timeStampPtr, \
                                             ETH_17_GETHMAC_SID_GETCURRENTTIME);
  }
    /* [cover parentID={627236D5-95B3-4c13-B76F-D6AAFF697020}]
     Valid Timestamp Pointer
     [/cover] */
    if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {

    /* [cover parentID={2EFE2FD6-99B7-4122-BD06-691FB66C5D97}]
     Check Driver is initialized
     [/cover] */
    /* Check if Eth_17_GEthMac_Init is sucessfull */
    DevError = Eth_17_lDetCheckNoInitStage1(ETH_17_GETHMAC_SID_GETCURRENTTIME);
  }
  /* [cover parentID={1C1FCD7C-D4D3-4d8e-A4AC-4186DDF3B552}]
   Driver Initialized
   [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* [cover parentID={B615F77A-E83A-4621-B82F-5DF056416C25}]
     Validate Controller Index
     [/cover] */
    /*  ETH_17_GETHMAC_E_INV_CTRL_IDX Check if CtrlIdx is valid */
    DevError = Eth_17_lDetCheckInvalidCtrlIdx( \
                                  CtrlIdx, ETH_17_GETHMAC_SID_GETCURRENTTIME);
  }
  /* [cover parentID={93BF72B7-8018-4b42-90D2-6A012AAAA146}]
   Valid Controller Index
   [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* Check if controller init is Sucessfull in
                                           Eth_17_GEthMac_SetControllerMode */
    /* [cover parentID={72D57C8E-001F-4442-933D-70EB4FF5240E}]
    [/cover] */
    DevError = Eth_17_lDetCheckNoInit(ETH_17_GETHMAC_SID_GETCURRENTTIME, \
                                                                      CtrlIdx);
  }
  /* [cover parentID={B385A828-0D18-4f35-A947-1FDFC7201472}]
   If controller init successful
   [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
#endif /* End of ETH_17_GETHMAC_DEV_ERROR_DETECT */
  {
    /* get base address of the controller */
    EthCntrlAdd = Eth_GEthMacCntrl[CtrlIdx];
    /* [cover parentID={9AFD8B78-B1A5-487f-8CAE-9EE33EC27D3A}]
     Set Time stamp Quality as VALID
     [/cover] */
    *timeQualPtr = ETH_VALID;
    /* [cover parentID={7A26080D-116A-4566-A7E4-41F744A8E22C}]
     Read Time from Timer(Hardware Timer in GETH) and fill in
     timeStampPtr (output parameter)
     [/cover] */
    /* Return Higher word second, second and nano second value */

    timeStampPtr->seconds = EthCntrlAdd->MAC_SYSTEM_TIME_SECONDS.U;
    timeStampPtr->secondsHi = EthCntrlAdd->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS.\
                                                                       B.TSHWR;
    timeStampPtr->nanoseconds = EthCntrlAdd->MAC_SYSTEM_TIME_NANOSECONDS.B.\
                                                                          TSSS;
    /* [cover parentID={E99A8B85-DB79-4f5f-A76D-D2571449C559}]
      Set RetValue = E_OK
     [/cover] */
    RetValue = E_OK;
  }
  /* [cover parentID={D3B79900-5C53-4ed7-B694-6CB26F6781C7}]
   Merge
   [/cover] */
  return RetValue;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={9668CC8F-3E41-412f-A138-632AB7432DBB}]  **
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
void Eth_17_GEthMac_EnableEgressTimeStamp(const uint8 CtrlIdx,
                                                            const uint8 BufIdx)
{
  const Eth_17_GEthMac_CntrlStatusType *EthLocalCoreStatusPtr;

#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
  uint8 TxBufTotal;
  const Eth_17_GEthMac_CoreCntrlConfigType *EthLocalCntrlCfgPtr;
#endif
/* [cover parentID={4C39A094-D952-40de-8312-585CBBD90DE3}]
DET is enabled
[/cover] */
#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
  /* Check if Eth_17_GEthMac_Init is successful */
  /* [cover parentID={C8DDF1EF-7307-4183-B2A4-B97C350D3338}]
  [/cover] */
  DevError = Eth_17_lDetCheckNoInitStage1\
                                    (ETH_17_GETHMAC_SID_ENABLEEGRESSTIMESTAMP);
  /* [cover parentID={48909803-9C3D-43bd-BD60-C3B0E6A919F8}]
   Driver Initialized
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* ETH_17_GETHMAC_E_INV_CTRL_IDX Check if CtrlIdx is valid */
    /* [cover parentID={B601641E-0412-42ae-97B9-BB6C4C3AD643}]
    Check Controller Index is Valid
    [/cover] */
    DevError = Eth_17_lDetCheckInvalidCtrlIdx( \
                            CtrlIdx, ETH_17_GETHMAC_SID_ENABLEEGRESSTIMESTAMP);
  }
  /* ETH_17_GETHMAC_E_NOT_INITIALIZED */
  /* [cover parentID={B992501F-F1F4-4797-B2A4-A7ED57851BD0}]
  Valid Controller Index
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* Check if controller init is successful in
    Eth_17_GEthMac_SetControllerMode */
    /* [cover parentID={DD9C6FCD-B134-44e6-9C1E-9FF37CCE2D51}]
    Check controller is initialized
    [/cover] */
    DevError = Eth_17_lDetCheckNoInit(ETH_17_GETHMAC_SID_ENABLEEGRESSTIMESTAMP,\
                                                                      CtrlIdx);
  }
  /* [cover parentID={04721867-43E9-42b0-A414-AB82FDD92288}]
  If controller is initialized
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* Get controller status */
    EthLocalCoreStatusPtr = Eth_17_lGetCtrlStatusPtr(CtrlIdx);
    /* Get controller configuration data */
    EthLocalCntrlCfgPtr = Eth_17_lGetCtrlConfigPtr(CtrlIdx);
    TxBufTotal = EthLocalCntrlCfgPtr->EthTxBufTotal;
    /* ETH_17_GETHMAC_E_INV_PARAM if the BufIdx is greater then Tx buff total */
    /* [cover parentID={B90F4393-1024-42e0-BB81-58A45FA93E63}]
    BufIdx(Input parameter) less than Total Tx buffer allocated
    [/cover] */
    if(BufIdx >= (Eth_BufIdxType)TxBufTotal)
    {
      /* [cover parentID={AC97C678-1963-4a19-9EDA-8CE42B7CEF17}]
      Report DET error ( Invalid Parameter)
      [/cover] */
      (void)Det_ReportError(ETH_17_GETHMAC_MODULE_ID,ETH_17_GETHMAC_INSTANCE_ID,
           ETH_17_GETHMAC_SID_ENABLEEGRESSTIMESTAMP,ETH_17_GETHMAC_E_INV_PARAM);
      DevError = ETH_17_GETHMAC_E_INV_PARAM;
    }
    /* Check BufIdx is the one which is allocated to application*/
    /* [cover parentID={719D1122-DA25-4799-92C6-8518BE3752FF}]
    BufIdx(Input parameter) is the one allocated to application
    [/cover] */
    else if(EthLocalCoreStatusPtr->EthBuffDecPtr->EthTxBuffTablePtr[BufIdx].\
                                      BuffStatus != ETH_17_GETHMAC_BUFFER_USED)
    {
      /* [cover parentID={AC97C678-1963-4a19-9EDA-8CE42B7CEF17}]
      Report DET error ( Invalid Parameter)
      [/cover] */
      (void)Det_ReportError(ETH_17_GETHMAC_MODULE_ID,ETH_17_GETHMAC_INSTANCE_ID,
           ETH_17_GETHMAC_SID_ENABLEEGRESSTIMESTAMP,ETH_17_GETHMAC_E_INV_PARAM);
      DevError = ETH_17_GETHMAC_E_INV_PARAM;
    }
    else
    {
      /*Do nothing. No actions required*/
    }
  }

  /* [cover parentID={E49F8DCC-E7E9-4833-9762-22C6A483B394}]
  Merge
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
#endif /* End of ETH_17_GETHMAC_DEV_ERROR_DETECT */
  {
    /* Get controller status */
    EthLocalCoreStatusPtr = Eth_17_lGetCtrlStatusPtr(CtrlIdx);
    /* [cover parentID={7AB71796-D7CE-4280-A733-3FA6942406E9}]
    Enable Transmit Time stamp in Tx Descriptor of requested Buffer Index
    [/cover] */
    /* Set the TTSE Bit of transmit descriptor*/
    EthLocalCoreStatusPtr->EthBuffDecPtr->EthDmaTxDescPtr[BufIdx].TDES2=\
    (uint32)(((EthLocalCoreStatusPtr->EthBuffDecPtr->EthDmaTxDescPtr[BufIdx].\
                       TDES2)|((uint32)ETH_17_GETHMAC_DMA_TX_DESC_TS_ENABLE)));
  }
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={FFDE75C1-4B79-45f0-8AE7-EEEFFE1E9AB4}]  **
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
void Eth_17_GEthMac_GetEgressTimeStamp(const uint8 CtrlIdx,
                const uint8 BufIdx, Eth_TimeStampQualType* const timeQualPtr,
                Eth_TimeStampType* const timeStampPtr)
{


  const Eth_17_GEthMac_CntrlStatusType *EthLocalCoreStatusPtr;
  const Eth_17_GEthMac_DmaTxDescType *EthLocalDmaTxDescPtr;
  const Ifx_GETH                              *EthCntrlAdd;
#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
  const Eth_17_GEthMac_CoreCntrlConfigType *EthLocalCntrlCfgPtr;
  uint8 TxBufTotal;
#endif

#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={76D90146-ED93-40a7-B79F-CBBC5F3BFB04}]
  Validate Time stamp Quality pointer (Output parameter)
  [/cover] */
  /* ETH_17_GETHMAC_E_PARAM_POINTER */
  DevError = Eth_17_lDetCheckInvalidPointer(timeQualPtr, \
                                         ETH_17_GETHMAC_SID_GETEGRESSTIMESTAMP);
  /* [cover parentID={CF9B0549-CD6D-4b68-A572-A6B9B4594762}]
  Valid Timestamp Quality Pointer
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* In default Assign time quality as Invalid,if timeQualPtr is not NULL */
    *timeQualPtr = ETH_INVALID;

    /* [cover parentID={EE2E368F-24D2-4197-AB85-566102C87F25}]
    Validate Time stamp pointer( Output parameter)
    [/cover] */
    /* ETH_17_GETHMAC_E_PARAM_POINTER */
    DevError = Eth_17_lDetCheckInvalidPointer(timeStampPtr, \
                                         ETH_17_GETHMAC_SID_GETEGRESSTIMESTAMP);
  }
  /* [cover parentID={2096BF7C-F92C-457d-8748-3FF4C2D43471}]
  Valid Timestamp Pointer
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* [cover parentID={468EC420-4D03-4867-B1D3-50D7DFEB1312}]
     Check Driver is initialized
     [/cover] */
    /* Check if Eth_17_GEthMac_Init is successfully */
    DevError = Eth_17_lDetCheckNoInitStage1\
                                       (ETH_17_GETHMAC_SID_GETEGRESSTIMESTAMP);
  }
  /* [cover parentID={425DEF80-593A-4caf-968E-4B558082D9B7}]
   Driver Initialized
   [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* [cover parentID={49446206-D4B1-43ec-A685-79630CA93540}]
      Validate Controller Index
      [/cover] */
    /*  ETH_17_GETHMAC_E_INV_CTRL_IDX Check if CtrlIdx is valid */
    DevError = Eth_17_lDetCheckInvalidCtrlIdx( \
                               CtrlIdx, ETH_17_GETHMAC_SID_GETEGRESSTIMESTAMP);
  }
  /* [cover parentID={452572EF-7E15-4bc5-BD3B-D94360324712}]
   Valid Controller Index
   [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* Check if controller init is Successfully in
                                           Eth_17_GEthMac_SetControllerMode */
    /* [cover parentID={79CB7857-DD7B-4fef-BA6C-23D3FF5514DC}]
     [/cover] */
    DevError = Eth_17_lDetCheckNoInit(ETH_17_GETHMAC_SID_GETEGRESSTIMESTAMP, \
                                                                      CtrlIdx);
  }
   /* [cover parentID={E0279035-0592-46e4-B74B-02DF9C63B564}]
   If controller is initialized
   [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* Get controller status */
    EthLocalCoreStatusPtr = Eth_17_lGetCtrlStatusPtr(CtrlIdx);
    /* Get controller configuration data */
    EthLocalCntrlCfgPtr = Eth_17_lGetCtrlConfigPtr(CtrlIdx);
    TxBufTotal = EthLocalCntrlCfgPtr->EthTxBufTotal;
    /* [cover parentID={DA947A21-97A1-43ff-9B49-C5F5FFE1E982}]
     BufIdx(Input parameter) less than Total Tx buffer allocated
     [/cover] */
    /* ETH_17_GETHMAC_E_INV_PARAM if the BufIdx is greater then Tx buff total */
    if(BufIdx >= (Eth_BufIdxType)TxBufTotal)
    {
      /* [cover parentID={19834F82-56D0-4329-918A-D03CC521EB57}]
      Report DET error ( Invalid Parameter)
      [/cover] */
      (void)Det_ReportError(ETH_17_GETHMAC_MODULE_ID,ETH_17_GETHMAC_INSTANCE_ID,
            ETH_17_GETHMAC_SID_GETEGRESSTIMESTAMP,ETH_17_GETHMAC_E_INV_PARAM);
      DevError = ETH_17_GETHMAC_E_INV_PARAM;
    }
    /* [cover parentID={944DEEBA-77B6-4125-8988-3D9E1EC2BCDB}]
    BufIdx(Input parameter) is the one allocated to application
    [/cover] */
    /* Check BufIdx is the one which is allocated to application*/
    else if(EthLocalCoreStatusPtr->EthBuffDecPtr->EthTxBuffTablePtr[BufIdx].\
                                      BuffStatus != ETH_17_GETHMAC_BUFFER_USED)
    {
      /* [cover parentID={19834F82-56D0-4329-918A-D03CC521EB57}]
      Report DET error ( Invalid Parameter)
      [/cover] */
      (void)Det_ReportError(ETH_17_GETHMAC_MODULE_ID,ETH_17_GETHMAC_INSTANCE_ID,
            ETH_17_GETHMAC_SID_GETEGRESSTIMESTAMP,ETH_17_GETHMAC_E_INV_PARAM);
      DevError = ETH_17_GETHMAC_E_INV_PARAM;
    }
    else
    {
      /*Do nothing. No actions required*/
    }
  }
  /* [cover parentID={755A6AF6-7062-48fe-9FA8-317CE6AB7D45}]
  Merge
  [/cover] */
  /* [cover parentID={D325E18D-2F22-4290-BBBC-6DCEB93BFF9B}]
  Merge
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
#endif /* End of ETH_17_GETHMAC_DEV_ERROR_DETECT */
  {
    /* get base address of the indexed controller */
    EthCntrlAdd = Eth_GEthMacCntrl[CtrlIdx];
     /* Get controller status */
    EthLocalCoreStatusPtr = Eth_17_lGetCtrlStatusPtr(CtrlIdx);
    /* Check if the requested descriptor's LD bit(Last Descriptor) is set */
    /* [cover parentID={144395C8-1057-4254-BDE8-6B19086ECECD}]
    Requested frame's ( Buffer Index's) end of packet is received
    [/cover] */
    EthLocalDmaTxDescPtr = EthLocalCoreStatusPtr->EthBuffDecPtr->\
                                                              EthDmaTxDescPtr;
    if((EthLocalDmaTxDescPtr[BufIdx].TDES3 & \
      ((uint32)ETH_17_GETHMAC_DMA_TX_DESC_LD_SET)) == \
      (uint32)ETH_17_GETHMAC_DMA_TX_DESC_LD_SET)
    {
      /* Check if timestamp has been captured for the corresponding
      transmit packet.*/
      /* [cover parentID={3CBC22E1-0615-463d-A216-A86FE9F4CC22}]
      Timestamp has been captured by hardware for the requested frame
      [/cover] */
      if((EthLocalDmaTxDescPtr[BufIdx].TDES3 & \
                   ((uint32)ETH_17_GETHMAC_DMA_TX_DESC_TTSS_SET)) == \
                   (uint32)ETH_17_GETHMAC_DMA_TX_DESC_TTSS_SET)
      {
        /* [cover parentID={8C1EAD37-0820-4792-BC65-BD2283748B84}]
        Set Time stamp Quality as VALID
        [/cover] */
        *timeQualPtr = ETH_VALID;

        /* [cover parentID={6569EE53-5CC0-46d4-BFCD-3933447B8304}]
        Read Time stamp form Tx descriptor of Buffer Index and HIGHER WORD
        SECONDS register and copy to time StampPointer (output parameter)
        [/cover] */
        /* Copy packet time stamp to timeStampPtr.*/
        /* Info: Overflow of MAC_SYSTEM_TIME_SECONDS register will happen
         * only once in 130 years. Hence MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS
         * directly coped to SecondHi value */
        timeStampPtr->secondsHi = \
                    (uint16)EthCntrlAdd->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS.U;

        timeStampPtr->seconds = \
                         (EthLocalDmaTxDescPtr[BufIdx].TDES1);
        timeStampPtr->nanoseconds = \
                         (EthLocalDmaTxDescPtr[BufIdx].TDES0);
      }
      else
      {
        /* [cover parentID={985CDA58-2B89-4b3c-89AB-206C69F59E50}]
        Set Time stamp Quality as INVALID
        [/cover] */
        *timeQualPtr = ETH_INVALID;
      }
    }
    else
    {
      /* [cover parentID={985CDA58-2B89-4b3c-89AB-206C69F59E50}]
      Set Time stamp Quality as INVALID
      [/cover] */
      *timeQualPtr = ETH_INVALID;
    }
  }
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={76309114-F93B-46f2-B8DB-9122EB574F31}]  **
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
void Eth_17_GEthMac_GetIngressTimeStamp(const uint8 CtrlIdx,
                                 const Eth_DataType* const DataPtr,
                                 Eth_TimeStampQualType* const timeQualPtr,
                                 Eth_TimeStampType* const timeStampPtr)
{

  Eth_17_GEthMac_CntrlStatusType *EthLocalCoreStatusPtr;
  const Eth_17_GEthMac_DmaRxDescType *EthLocalDmaRxDescPtr;
  const Ifx_GETH *EthCntrlAdd;
#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;

  /* [cover parentID={A53C529E-E365-4e21-BB03-72CF3E5552EC}]
  Validate Time stamp Quality pointer (Output parameter)
  [/cover] */
  /* ETH_17_GETHMAC_E_PARAM_POINTER */
  DevError = Eth_17_lDetCheckInvalidPointer(timeQualPtr, \
                                        ETH_17_GETHMAC_SID_GETINGRESSTIMESTAMP);
  /* [cover parentID={43ECB23F-9D27-4ed5-82E7-8A22470FFABC}]
  Valid Timestamp Quality Pointer
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* In default Assign time quality as Invalid,if timeQualPtr is not NULL */
    /* [cover parentID={D9E3FD31-9853-4b8e-9E4D-BE718F88F85C}]
     [/cover] */
    *timeQualPtr = ETH_INVALID;

    /* [cover parentID={787142EA-0467-4071-81F4-C5154F06C378}]
    Validate Time stamp pointer( Output parameter)
    [/cover] */
    /* ETH_17_GETHMAC_E_PARAM_POINTER */
     DevError = Eth_17_lDetCheckInvalidPointer(timeStampPtr, \
                                        ETH_17_GETHMAC_SID_GETINGRESSTIMESTAMP);
  }
  /* [cover parentID={050CA4B2-D37B-48aa-BE24-F9BD22CF7BBD}]
  Valid Timestamp Pointer
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* Check if Eth_17_GEthMac_Init is sucessfull */
    /* [cover parentID={EEB7DDA9-6075-4b36-8123-D58F47B77912}]
     Check Driver is initialized
     [/cover] */
    DevError = Eth_17_lDetCheckNoInitStage1\
                                      (ETH_17_GETHMAC_SID_GETINGRESSTIMESTAMP);
  }
  /* [cover parentID={F3501F69-2215-4b78-A051-AAF981D92EB6}]
   Driver Initialized
   [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* ETH_17_GETHMAC_E_INV_CTRL_IDX Check if CtrlIdx is valid */
    /* [cover parentID={89E87F8F-2B24-4e2b-ADD2-B67768DC96F8}]
     Validate Controller Index
     [/cover] */
    DevError = Eth_17_lDetCheckInvalidCtrlIdx( \
                               CtrlIdx, ETH_17_GETHMAC_SID_GETINGRESSTIMESTAMP);
  }
  /* ETH_17_GETHMAC_E_NOT_INITIALIZED */
  /* [cover parentID={92C574D2-A862-40d2-B2C3-ABA2B79B90FA}]
   Valid Controller Index
   [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
     /* Check if controller init is Sucessfull in
                                           Eth_17_GEthMac_SetControllerMode */
    /* [cover parentID={F836702B-7E7C-4f47-A73C-522D52FB3B23}]
     Check if controller init is successful
     [/cover] */
    DevError = Eth_17_lDetCheckNoInit(ETH_17_GETHMAC_SID_GETINGRESSTIMESTAMP, \
                                                                      CtrlIdx);
  }
  /* [cover parentID={E272C58A-B577-4b38-8B5E-2DA1FE3FBBB9}]
   If controller init was successful
   [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* [cover parentID={D14DE311-CBE4-49f6-A572-0B2051D3D7A8}]
    Validate DataPtr pointer
    [/cover] */
    /* ETH_17_GETHMAC_E_PARAM_POINTER */
     DevError = Eth_17_lDetCheckInvalidPointer(DataPtr, \
                                        ETH_17_GETHMAC_SID_GETINGRESSTIMESTAMP);
  }
  /* [cover parentID={6B7687F3-05BE-4b7a-A9A0-DC4CBB734CB4}]
  Valid DataPtr
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
#else
  if(DataPtr != NULL_PTR)
  {
    UNUSED_PARAMETER(*DataPtr);
  }
#endif /* End of ETH_17_GETHMAC_DEV_ERROR_DETECT */
  {
    /* Get controller status */
    EthLocalCoreStatusPtr = Eth_17_lGetCtrlStatusPtr(CtrlIdx);
    /* get base address of the indexed controller */
    EthCntrlAdd = Eth_GEthMacCntrl[CtrlIdx];
    /* Check if Time stamp is available for the packet*/
    /* [cover parentID={5FB6CADA-D165-45fb-B5A6-6BF5F85732C5}]
    Time stamp is available for Requested frame (For this, Check
    'Eth_RxDmaDesIdxForIngTimStamp' variable is not a invalid value)
    [/cover] */
    if(EthLocalCoreStatusPtr->EthRunTimeOpertnData.RxDmaDesIdxForIngTimStamp\
                                                != ETH_17_GETHMAC_TIMESTAMP_NA)
    {
      /* [cover parentID={2011D4B8-816E-4850-832D-3E1E1D284B37}]
      Read Time stamp form Rx descriptor of
      'EthRunTimeOpertnData.RxDmaDesIdxForIngTimStamp'
      index and HIGHER WORD SECONDS register and copy to time StampPointer
      (output parameter)
      [/cover] */
      /* Copy packet time stamp to timeStampPtr.*/
      /* Info: Overflow of MAC_SYSTEM_TIME_SECONDS register will happeno
      only once in 130 years. Hence MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS
      directly coped to SecondHi value */
      EthLocalDmaRxDescPtr = EthLocalCoreStatusPtr->EthBuffDecPtr->\
                                                              EthDmaRxDescPtr;
      timeStampPtr->secondsHi    = \
                    (uint16)EthCntrlAdd->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS.U;
      timeStampPtr->seconds = (EthLocalDmaRxDescPtr[EthLocalCoreStatusPtr->\
                       EthRunTimeOpertnData.RxDmaDesIdxForIngTimStamp].RDES1);
      timeStampPtr->nanoseconds = (EthLocalDmaRxDescPtr[EthLocalCoreStatusPtr->\
                       EthRunTimeOpertnData.RxDmaDesIdxForIngTimStamp].RDES0);
      /* Check time stamp quality by checking is it corrupted. */
      /* [cover parentID={1F5DC937-9D11-48ce-95A1-41CBF1FEFF1F}]
        Time Stamp corrupted
        [/cover] */
      if((timeStampPtr->seconds == ETH_17_GETHMAC_INGRESS_TS_CORRUPT) && \
           (timeStampPtr->nanoseconds == ETH_17_GETHMAC_INGRESS_TS_CORRUPT))
      {
        *timeQualPtr = ETH_INVALID;
      }
      else
      {
        /* [cover parentID={E87392BF-CE60-4745-94EE-5323A8E03771}]
        Set Time stamp Quality as VALID
        [/cover] */
        *timeQualPtr = ETH_VALID;
      }
      /* Reset time stamp availability as Not Available*/
      EthLocalCoreStatusPtr->EthRunTimeOpertnData.RxDmaDesIdxForIngTimStamp = \
                                     ETH_17_GETHMAC_TIMESTAMP_NA;
    }
  }
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={7993D639-080F-4da0-8729-76F71E79BCC6}]  **
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
void Eth_17_GEthMac_SetCorrectionTime(const uint8 CtrlIdx,
                             const Eth_TimeIntDiffType* const timeOffsetPtr,
                             const Eth_RateRatioType* const rateRatioPtr)
{
#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
  /* Check if Eth_17_GEthMac_Init is sucessful */
  /* [cover parentID={3315DA03-D8EA-4d1e-B025-C12CBACAC7E3}]
  Check if init was successful
  [/cover] */
  DevError = Eth_17_lDetCheckNoInitStage1(ETH_17_GETHMAC_SID_SETCORRECTIONTIME);
  /* [cover parentID={CEDE0E3F-37FC-4e46-804A-9A7E27A7B501}]
  Driver Initialized
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /*  ETH_17_GETHMAC_E_INV_CTRL_IDX Check if CtrlIdx is valid  */
    /* [cover parentID={70E63739-880E-4e66-91AE-2730E7D319A0}]
    Validate Controller Index
    [/cover] */
    DevError = Eth_17_lDetCheckInvalidCtrlIdx( \
                                CtrlIdx, ETH_17_GETHMAC_SID_SETCORRECTIONTIME);
  }
  /* ETH_17_GETHMAC_E_NOT_INITIALIZED */
  /* [cover parentID={71841FEA-888E-455b-AA1A-BE21080F3C5B}]
  Valid Controller Index
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* Check if controller init is Sucessfull in
                                           Eth_17_GEthMac_SetControllerMode */
    /* [cover parentID={F836702B-7E7C-4f47-A73C-522D52FB3B23}]
    Check if controller init is successful
    [/cover] */
    DevError = Eth_17_lDetCheckNoInit(ETH_17_GETHMAC_SID_SETCORRECTIONTIME, \
                                                                      CtrlIdx);
  }
  /* [cover parentID={32ADC8B8-3D73-405d-9716-D1237BC9EA6D}]
  if controller init is successful
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* [cover parentID={4E30D745-84BA-450b-B05A-5FFCCFA1083A}]
    Validate timeOffsetPtr (Input parameter)
    [/cover] */
    /* ETH_17_GETHMAC_E_PARAM_POINTER */
    DevError = Eth_17_lDetCheckInvalidPointer(timeOffsetPtr, \
                                          ETH_17_GETHMAC_SID_SETCORRECTIONTIME);
  }
  /* [cover parentID={E33C6469-D867-42af-9DE1-A106D7FEE91B}]
  Valid timeOffsetPtr
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* ETH_17_GETHMAC_E_PARAM_POINTER */
    /* [cover parentID={B4953763-2458-4cab-958E-F1475030F1CF}]
    Validate rateRatioPtr
    [/cover] */
    DevError = Eth_17_lDetCheckInvalidPointer(rateRatioPtr, \
                                          ETH_17_GETHMAC_SID_SETCORRECTIONTIME);
  }
  /* [cover parentID={1AE5509C-50B6-4568-B5B4-2CB647A39DF3}]
  Valid rateRatioPtr
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
#endif /* End of ETH_17_GETHMAC_DEV_ERROR_DETECT */
  {
    /* [cover parentID={C2BEE4E6-D83E-4431-BF64-485D54DB4E5E}]
    Enter Critical Section
    [/cover] */
    SchM_Enter_Eth_17_GEthMac_UpdateGlobalTime();
    /* [cover parentID={03390EB3-F662-474a-B60C-B37092B77A02}]
    Perfrom Time Correction, by updating Offset and Frequency Compensation
    [/cover] */
    Eth_17_lSetCorrectionTime(CtrlIdx,timeOffsetPtr, rateRatioPtr);

    /* [cover parentID={644C814F-EDE9-4136-99D9-92602072B2A4}]
    Exit Critical Section
    [/cover] */
    SchM_Exit_Eth_17_GEthMac_UpdateGlobalTime();

  }
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={0CC425E3-DC66-46d8-AB0B-587E1C70CDEA}]  **
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
Std_ReturnType Eth_17_GEthMac_SetGlobalTime(const uint8 CtrlIdx, const
                                        Eth_TimeStampType* const timeStampPtr)
{
  Std_ReturnType RetValue= E_NOT_OK;
#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
  /* Check if Eth_17_GEthMac_Init is sucessfull */
  /* [cover parentID={58726459-BEB0-4260-AA8C-C4C08046B39F}]
  Check if init was successfull
  [/cover] */
  DevError = Eth_17_lDetCheckNoInitStage1(ETH_17_GETHMAC_SID_SETGLOBALTIME);
  /* [cover parentID={0E333A6A-D869-4a94-B007-77534F124078}]
  Driver Initialized
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /*  ETH_17_GETHMAC_E_INV_CTRL_IDX Check if CtrlIdx is valid */
    /* [cover parentID={C1F4C9C2-6F5D-44d0-83EC-1037DD0A63D1}]
    Validate CtrlIdx
    [/cover] */
    DevError = Eth_17_lDetCheckInvalidCtrlIdx( \
                                  CtrlIdx, ETH_17_GETHMAC_SID_SETGLOBALTIME);
  }
  /* [cover parentID={370DF8B7-381F-456a-8138-55DA9DE339CE}]
    Valid CtrlIdx
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* Check if controller init is Sucessfull in
    Eth_17_GEthMac_SetControllerMode */
    /* [cover parentID={A4D7D94C-DCCD-48c2-9794-6813836A86C0}]
    Check if controller is initialized
    [/cover] */
    DevError = Eth_17_lDetCheckNoInit(ETH_17_GETHMAC_SID_SETGLOBALTIME, \
                                                                      CtrlIdx);
  }
  /* [cover parentID={748B4061-644E-4589-BCCB-3604B9AAC674}]
   if controller is initialized
   [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* [cover parentID={A35C8BDD-D327-4dcf-8B0E-083D6C687143}]
    Validate Time stamp pointer (Input parameter)
    [/cover] */
    /* ETH_17_GETHMAC_E_PARAM_POINTER */
    DevError = Eth_17_lDetCheckInvalidPointer(timeStampPtr,\
                                              ETH_17_GETHMAC_SID_SETGLOBALTIME);
  }
  /* [cover parentID={7F39B661-3EC7-4f5e-B56D-26BB4AEB5054}]
  Valid Timestamp Pointer
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
#endif /* End of ETH_17_GETHMAC_DEV_ERROR_DETECT */
  {
    /* [cover parentID={62006E61-BAC2-465a-B24C-D3BF2C4E8164}]
    [/cover] */
    SchM_Enter_Eth_17_GEthMac_UpdateGlobalTime();

    /* [cover parentID={0D980890-C4CF-4fbc-9CB1-CEC17033631C}]
    Set Time Value and Update RetVal (RetValue = Eth_17_lSetGlobalTime)
    [/cover] */
    RetValue = Eth_17_lSetGlobalTime(CtrlIdx,timeStampPtr);

    /* [cover parentID={F14769D1-C72C-41e0-B3FF-941B5272DC21}]
    [/cover] */
    SchM_Exit_Eth_17_GEthMac_UpdateGlobalTime();
  }
  return RetValue;
}
#endif

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={696DC298-84D8-4fa4-A249-9084C88B5D7C}]  **
**                                                                            **
** Syntax           : void Eth_17_GEthMac_MainFunction (void)                 **
**                                                                            **
** Description      : The function checks for controller errors  and          **
**                    lost frames.                                            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x20                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void Eth_17_GEthMac_MainFunction(void)
{
  uint32 CoreId;
  CoreId = Mcal_GetCpuIndex();
  /* [cover parentID={7D35B5A6-ED35-4507-896B-A929CE7D75D1}]
  Eth_17_GEthMac_MainFunction
  [/cover] */
  /* [cover parentID={0FBAFE7D-E599-4724-B3D4-534FAB8442F0}]
  Check Ethernet Driver is initialized
  [/cover] */
  /* [cover parentID={CC5A9212-CFD4-4eb8-9AE2-978A61CCBD63}]
  Ethernet Main Function Return without performing any function
  [/cover] */
  /* [cover parentID={043AD31E-F824-4607-BAFC-2DA7CB2D6A98}]
  Driver Initialized
  [/cover] */
  /* If ETH driver is not initialized, return immediately without performing
  any functionality and without raising any errors.*/
  if(*(Eth_17_GEthMac_CoreInitStatus[CoreId]) ==
                                        (uint32)ETH_17_GETHMAC_CORE_INIT)
  {
    /* [cover parentID={2F293D1A-097A-46d8-974A-08739EB6699E}]
    Updates Statistics counter values
    [/cover] */
    Eth_17_lUpdateEthStatisticsCounterValues();

    /* [cover parentID={DE5F0AB5-0D1E-4046-A54B-D2DA5322CDA2}]
    Report Production error to Mcal_Wrapper for Statistics Counter values
    [/cover] */
    Eth_17_lDemReportStatisticsCounterValues();
  }
}

#if(ETH_17_GETHMAC_VERSION_INFO_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={3127B115-79CE-40a0-9636-03DAA9C7E633}]  **
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
void Eth_17_GEthMac_GetVersionInfo(Std_VersionInfoType* const VersionInfoPtr)
{
  /* [cover parentID={767A6351-DABF-4d72-9325-F1ECA75D49DD}]
  Eth_17_GEthMac_GetVersionInfo
  [/cover] */
  #if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
  /* [cover parentID={4D5C601B-4E14-43c5-895A-40EF23B1FC3E}]
   Check for NULL pointer
   [/cover] */
  /* ETH_17_GETHMAC_E_PARAM_POINTER */
  DevError = Eth_17_lDetCheckInvalidPointer(VersionInfoPtr, \
                                             ETH_17_GETHMAC_SID_GETVERSIONINFO);
  /* [cover parentID={21C6E1F3-5E6F-4cb4-BD1F-226349BF1D55}]
   If No DET
   [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  #endif /* End for ETH_17_GETHMAC_DEV_ERROR_DETECT */
  {
    /* [cover parentID={76F0C1EA-AAA4-4690-BC9C-526EF2F73513}]
    Write the values of Module ID, Vendor ID, SW Major, Minor and Patch
    version to the Version Info Pointer
    [/cover] */
    VersionInfoPtr->vendorID         = (uint16)ETH_17_GETHMAC_VENDOR_ID;
    VersionInfoPtr->moduleID         = (uint16)ETH_17_GETHMAC_MODULE_ID;
    VersionInfoPtr->sw_major_version = (uint8)ETH_17_GETHMAC_SW_MAJOR_VERSION;
    VersionInfoPtr->sw_minor_version = (uint8)ETH_17_GETHMAC_SW_MINOR_VERSION;
    VersionInfoPtr->sw_patch_version = (uint8)ETH_17_GETHMAC_SW_PATCH_VERSION;
  }
}
#endif /* End for ETH_17_GETHMAC_VERSION_INFO_API */

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={158E38EC-31FF-4970-AEB2-0B2C0C28F3E9}]  **
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
void Eth_17_GEthMac_TxDmaCh0IrqHdlr(const uint8 CtrlIdx)
{
  uint8 MaxLoops = ETH_17_GETHMAC_ZERO;
  Ifx_GETH *EthCntrlAdd;

#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
  /* Check if Eth_17_GEthMac_Init is sucessfull */
  /* [cover parentID={D12912A4-F706-4afc-9AA3-598E99F2686D}]
  [/cover] */
  DevError = Eth_17_lDetCheckNoInitStage1(ETH_17_GETHMAC_SID_TXHANDLER);
  /* [cover parentID={0D12AD30-D71F-454f-A2BB-ED34459630D6}]
  If init was successful
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /*  ETH_17_GETHMAC_E_INV_CTRL_IDX Check if CtrlIdx is valid */
    /* [cover parentID={9F279DE3-A73D-4739-9843-C4ED9DE19B63}]
    [/cover] */
    DevError = Eth_17_lDetCheckInvalidCtrlIdx( \
                                  CtrlIdx, ETH_17_GETHMAC_SID_TXHANDLER);
  }
    /* Check if controller init is Sucessfull in
    Eth_17_GEthMac_SetControllerMode */
  /* [cover parentID={9A68101B-C271-4047-80E2-4217A8843449}]
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* [cover parentID={8EAB2349-9066-46e0-8802-992BD2CC4090}]
    If Ctrl Idx is valid
    [/cover] */
    DevError = Eth_17_lDetCheckNoInit(ETH_17_GETHMAC_SID_TXHANDLER, \
                                                                      CtrlIdx);
  }
  /* [cover parentID={6B026A8A-6FA0-47b4-B432-5636D047CD5B}]
  If controller init was successful
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
#endif /* End of ETH_17_GETHMAC_DEV_ERROR_DETECT */
  {
    EthCntrlAdd = Eth_GEthMacCntrl[CtrlIdx];
    /* [cover parentID={00DF8358-BD67-4782-8A97-7D3FCB9526B4}]
    Tx Interrupt(TI) bit is set in DMA_CH0_STATUS register
    [/cover] */
    /* Read DMA channel-0 Status to check Transmit Interrupt bit .And loop this
    check for multiple times to check that, new Tx event occurred during
    the processing of this ISR routine.This ensure fast processing of packets */
    while(EthCntrlAdd->DMA_CH[0].STATUS.B.TI == ETH_17_GETHMAC_ONE)
    {
      /* clear signalled TX interrupt */
      EthCntrlAdd->DMA_CH[0].STATUS.U = (uint32)\
                                 ((uint32)ETH_17_GETHMAC_DMA_CH_STAT_TI_RESET |\
                                  (uint32)ETH_17_GETHMAC_DMA_CH_STAT_NIS_RESET);
      /* [cover parentID={A530E1EA-DD1B-450b-81DA-1972D0676B19}]
      Confirm all successfully trasmitted frames to application
      [/cover] */
      /* Local function to confirm all successfully trasmitted frames */
      Eth_17_lConfirmTxFrames(CtrlIdx);

      MaxLoops++;

      /* [cover parentID={D9D7E5BD-A472-4787-B967-9544AC184AEA}]
      DMA_CH0_STATUS register is read for
      ETH_17_GETHMAC_TXRX_INT_PENDG_MAXLOOPCNT times
      [/cover] */
      /* limit the check loops to avoid endless loop in case TI does not
       reset (due to any HW failure) */
      if (MaxLoops > ETH_17_GETHMAC_TXRX_INT_PENDG_MAXLOOPCNT)
      {
        /* Break While loop. */
        break;
      }
    }
  }
}
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={0218E794-92CD-464a-B23D-FD857AB8C876}]  **
**                                                                            **
** Syntax           : void Eth_17_GEthMac_RxDmaCh0IrqHdlr(const uint8 CtrlIdx)**
**                                                                            **
** Description      : IRQ handler for frame reception completion              **
**                    interrupts and and receive buffer unavailable interrupt **
                      from Receive DMA channel-0.                             **
**                    Note: loop to check RI or RBU is required as no new     **
**                          interrupt is generated, if a new RX event occurs  **
**                          while RI or RBU is still set                      **
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
void Eth_17_GEthMac_RxDmaCh0IrqHdlr(const uint8 CtrlIdx)
{
  Ifx_GETH *EthCntrlAdd;
  const Eth_17_GEthMac_CntrlStatusType *EthLocalCoreStatusPtr;
  const Eth_17_GEthMac_CoreCntrlConfigType *EthLocalCntrlCfgPtr;
  uint8 MaxLoops = ETH_17_GETHMAC_ZERO;
#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
  uint32 DevError;
  /* Check if Eth_17_GEthMac_Init is successful */
  /* [cover parentID={3F8EDCCA-4EE6-4f9d-B010-EB16B4CEBB4D}]
  [/cover] */
  DevError = Eth_17_lDetCheckNoInitStage1(ETH_17_GETHMAC_SID_RXHANDLER);
  /* [cover parentID={C52F7088-F89C-4119-9925-A389847E7997}]
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* ETH_17_GETHMAC_E_INV_CTRL_IDX Check if CtrlIdx is valid */
    /* [cover parentID={FD9A3D26-A330-4fc8-9820-AF24D4E69AC0}]
    [/cover] */
    DevError = Eth_17_lDetCheckInvalidCtrlIdx( \
                                  CtrlIdx, ETH_17_GETHMAC_SID_RXHANDLER);
  }
  /* [cover parentID={FBB4407B-EFBE-4162-AAB6-B45869A454A1}]
  If CtrlIdx is Valid
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* Check if controller init is Successful in
    Eth_17_GEthMac_SetControllerMode */
    /* [cover parentID={2916F676-581F-4669-BC49-06803DCAF06F}]
    [/cover] */
    DevError = Eth_17_lDetCheckNoInit(ETH_17_GETHMAC_SID_RXHANDLER, \
                                                                      CtrlIdx);
  }
  /* [cover parentID={402958B8-601A-409e-A355-AC65ABE9CA6B}]
  If Controller init is successful
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
#endif /* End of ETH_17_GETHMAC_DEV_ERROR_DETECT */
  {
    EthCntrlAdd = Eth_GEthMacCntrl[CtrlIdx];
    /* Get controller status */
    EthLocalCoreStatusPtr = Eth_17_lGetCtrlStatusPtr(CtrlIdx);
    /* Get controller configuration data */
    EthLocalCntrlCfgPtr = Eth_17_lGetCtrlConfigPtr(CtrlIdx);

    /* [cover parentID={F3338199-48BE-4dd0-9F08-11B96BFB845A}]
    Loop until Rx Interrupt(RI) bit or Receive buffer unavailable(RBU) bit
    is set in DMA_CH0_STATUS register
    [/cover] */
    /* MISRA2012_RULE_13_5_JUSTIFICATION: Or operator required to check the RI
    and RBU bits of the SFR.This warning is due to the volatile
    qualifier in the SFRs and no side-affect foreseen by violation.*/
    /* Read DMA channel-0 Status to check Receive Interrupt bit. And loop this
    check for multiple times to check that, new Rx event occurred during
    the processing of this ISR routine.This ensure fast processing of packets */
    while((EthCntrlAdd->DMA_CH[0].STATUS.B.RI == ETH_17_GETHMAC_ONE)||\
    (EthCntrlAdd->DMA_CH[0].STATUS.B.RBU == ETH_17_GETHMAC_ONE))
    {
      /* clear signalled RX interrupt or RBU interrupt */
      EthCntrlAdd->DMA_CH[0].STATUS.U = (uint32)\
                          ((uint32)ETH_17_GETHMAC_DMA_CH_STAT_RI_RESET |\
                           (uint32)ETH_17_GETHMAC_DMA_CH_STAT_NIS_RESET|\
                          (uint32)ETH_17_GETHMAC_DMA_CH_STAT_RBU_ERI_AIE_RESET);

      /* [cover parentID={81975596-CB53-42bf-A922-EAC3124355BD}]
      Notify about received frames to application
      [/cover] */
      /* Local function to notify received frames */
      /* The return value from the function Eth_17_lReceiveFrames is not
       * required to be checked here as it is required only in polling mode to
       * indicate whether a frame is received or not.
       * Rx Interrupt is generated when a frame is received. */
      (void)Eth_17_lReceiveFrames(CtrlIdx);

      /*Update Rx- DMA-CH0 Descriptor tail pointer to issue
       poll demand command*/
     /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion pointer to a
     integer type is performed to align last buffer address to tail pointer
     register. This is the intended design and valid as per DMA hardware
     design. There are no side effects seen by violating this rule.*/
     /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from pointer to unsigned long
      is performed to to assign last buffer address to tail pointer
     register. This is the intended design and valid as per DMA hardware
     design. There are no side effects seen by violating this rule.*/
      EthCntrlAdd->DMA_CH[0].RXDESC_TAIL_POINTER.U = \
                         (uint32)(&EthLocalCoreStatusPtr->EthBuffDecPtr->\
                         EthDmaRxDescPtr[EthLocalCntrlCfgPtr->EthRxBufTotal]);

      MaxLoops++;
      /* [cover parentID={FD3A9616-9738-4d17-BFDF-7CDFD3F504F1}]
      DMA_CH0_STATUS register is read for
      ETH_17_GETHMAC_TXRX_INT_PENDG_MAXLOOPCNT times
      [/cover] */
      /* limit the check loops to avoid endless loop in case RI does not
       reset (due to any HW failure) */
      if (MaxLoops > ETH_17_GETHMAC_TXRX_INT_PENDG_MAXLOOPCNT)
      {
        /* Break While loop. */
        break;
      }
    }
  }

}
/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={C929AAA6-AE64-4819-AAE5-FF4442E847AF}]  **
**                                                                            **
** Syntax           : static Eth_ModeType Eth_17_lGetMode(const uint8 CtrlIdx)**
*                                                                             **
** Description      : Get the mode of controller                              **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx - Controller Index                              **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : ETH_MODE_ACTIVE - Controller is in active state         **
**                    ETH_MODE_DOWN   - Controler is down                     **
**                                                                            **
*******************************************************************************/
static Eth_ModeType Eth_17_lGetMode(const uint8 CtrlIdx)
{
  Eth_ModeType Status;
  uint32 MacMode;
  uint32 DmaTxMode;
  uint32 DmaRxMode;
  const Ifx_GETH *EthCntrlAdd;
  EthCntrlAdd = Eth_GEthMacCntrl[CtrlIdx];

  /* Get MAC status. */
  MacMode = (uint32)(EthCntrlAdd->MAC_CONFIGURATION.U);

  /* Get DMA Tx status. */
  DmaTxMode = (uint32)(EthCntrlAdd->DMA_CH[0].TX_CONTROL.U);

  /* Get DMA Rx status. */
  DmaRxMode = (uint32)(EthCntrlAdd->DMA_CH[0].RX_CONTROL.U);

  /* [cover parentID={218D595C-1CEF-4679-B99A-31B77C648AAF}]
  MAC Tx & Rx are enabled and Tx DMA & Rx DMA are started
  [/cover] */
  /* Check if MAC Tx & Rx are enabled and DMA Tx & DMA Rx are started. */
  if(((MacMode & ((uint32)ETH_17_GETHMAC_MAC_TX | \
                  (uint32)ETH_17_GETHMAC_MAC_RX)) == \
                  ((uint32)ETH_17_GETHMAC_TXENABLE | \
                   (uint32) ETH_17_GETHMAC_RXENABLE)) && \
      ((DmaTxMode & ((uint32)ETH_17_GETHMAC_DMA_TX_CH_START)) == \
                    ((uint32)ETH_17_GETHMAC_DMA_TX_CH_START)) && \
      ((DmaRxMode & ((uint32)ETH_17_GETHMAC_DMA_RX_CH_START)) == \
                    ((uint32)ETH_17_GETHMAC_DMA_RX_CH_START)))
  {
      /* [cover parentID={CD6C4459-7EB7-4ac6-ABD2-26663B1CB1AD}]
      Set the mode to active
      [/cover] */
      Status = ETH_MODE_ACTIVE;
  }
  else
  {
      /* [cover parentID={3FEF6629-E80F-4833-8B3E-459EF5BE54C7}]
      Set the mode to down
      [/cover] */
      Status = ETH_MODE_DOWN;
  }
  return Status ;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={2D73F8B8-B3BC-4577-93AE-8F41A4BF6C73}]  **
**                                                                            **
** Syntax           : static void Eth_17_lStartTxRx(const uint8 CtrlIdx)      **
**                                                                            **
** Description      : Function to start Tx and Rx in MAC and DMA core         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx - Controller Index                              **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_lStartTxRx(const uint8 CtrlIdx)
{
  Ifx_GETH *EthCntrlAdd;
  const Eth_17_GEthMac_CoreCntrlConfigType *EthLocalCntrlCfgPtr;

  /* Get controller configuration data */
  EthLocalCntrlCfgPtr = Eth_17_lGetCtrlConfigPtr(CtrlIdx);

  EthCntrlAdd = Eth_GEthMacCntrl[CtrlIdx];

  /* Start Receive on DMA Channel-0  */
  EthCntrlAdd->DMA_CH[0].RX_CONTROL.B.SR = ETH_17_GETHMAC_ONE;

  /* Insert delay for back to back register writes */
  Eth_17_lBkToBkRegWrInsrtDly(EthLocalCntrlCfgPtr->EthBkRegWrWaitTime);

  /* Disable the queue packet flush after starting the receive process */
  EthCntrlAdd->DMA_CH[0].RX_CONTROL.B.RPF = ETH_17_GETHMAC_ZERO;

  /* Start Transmission on DMA Channel-0  */
  EthCntrlAdd->DMA_CH[0].TX_CONTROL.B.ST = ETH_17_GETHMAC_ONE;

  /* Enable MAC Transmitter and Receiver */
  EthCntrlAdd->MAC_CONFIGURATION.U = (EthCntrlAdd->MAC_CONFIGURATION.U |
                               (uint32)ETH_17_GETHMAC_MAC_TXRX_ENABLEMASK);
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={36D82DE9-5100-4b34-9736-4B8AB3FD0954}]  **
**                                                                            **
** Syntax           : static void Eth_17_lStopTxRx(const uint8 CtrlIdx)       **
**                                                                            **
** Description      : Function to stop Tx and Rx in MAC and DMA core          **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx - Controller Index                              **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_lStopTxRx(const uint8 CtrlIdx)
{
  Ifx_GETH *EthCntrlAdd;
  const Eth_17_GEthMac_CoreCntrlConfigType *EthLocalCntrlCfgPtr;

  /* Get controller configuration data */
  EthLocalCntrlCfgPtr = Eth_17_lGetCtrlConfigPtr(CtrlIdx);

  EthCntrlAdd = Eth_GEthMacCntrl[CtrlIdx];

  /* Stop Transmission on DMA Channel-0  */
  EthCntrlAdd->DMA_CH[0].TX_CONTROL.B.ST = ETH_17_GETHMAC_ZERO;

  /* Initiate the transmit queue flush operation */
  EthCntrlAdd->MTL_TXQ0.OPERATION_MODE.B.FTQ = ETH_17_GETHMAC_ONE;

  /* Disable MAC Transmitter and Receiver */
  EthCntrlAdd->MAC_CONFIGURATION.U = (EthCntrlAdd->MAC_CONFIGURATION.U &
                              (uint32)ETH_17_GETHMAC_MAC_TXRX_DISABLEMASK);

  /* Enable the receive queue packet flush operation */
  /* This packet flush operation flushes the packet from the Rx queue
  destined to the DMA Rx channel 0 when it is stopped. Also, the packets in
  the Rx Queue that were received when the Rx DMA Ch0 was stopped,
  get flushed out when the Rx DMA is re-started */
  EthCntrlAdd->DMA_CH[0].RX_CONTROL.B.RPF = ETH_17_GETHMAC_ONE;

  /* Insert delay for back to back register writes */
  Eth_17_lBkToBkRegWrInsrtDly(EthLocalCntrlCfgPtr->EthBkRegWrWaitTime);

  /* Stop Receive on DMA Channel-0  */
  EthCntrlAdd->DMA_CH[0].RX_CONTROL.B.SR = ETH_17_GETHMAC_ZERO;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={A1875415-4EA4-4f48-A588-FD243AFD4472}]  **
**                                                                            **
** Syntax           : static void Eth_17_lCheckForCtrlModeChange (            **
**                    Eth_17_GEthMac_CntrlStatusType *                        **
**                    const EthLocalCoreStatusPtr, const uint8 CtrlIdx )      **
**                                                                            **
** Description      : The function checks polling state changes.              **
**                    Calls EthIf_CtrlModeIndication when the                 **
**                    controller mode changed.                                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : EthLocalCoreStatusPtr - Pointer to controller status    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_lCheckForCtrlModeChange(Eth_17_GEthMac_CntrlStatusType
                            * const EthLocalCoreStatusPtr, const uint8 CtrlIdx)
{
  /* [cover parentID={66BB4C31-1859-40b8-8084-97BA8CD493AC}]
  Current Controller mode Not Equal to  Previous Controller mode
  [/cover] */

  if (EthLocalCoreStatusPtr->EthRunTimeOpertnData.EthControllerMode != \
      EthLocalCoreStatusPtr->EthRunTimeOpertnData.PrevEthControllerMode)
  {
    /* [cover parentID={3263DA91-37FB-4691-B82C-6ACADE11C618}]
    [/cover] */
    EthIf_CtrlModeIndication(CtrlIdx,EthLocalCoreStatusPtr->\
                                       EthRunTimeOpertnData.EthControllerMode);
    EthLocalCoreStatusPtr->EthRunTimeOpertnData.PrevEthControllerMode = \
        EthLocalCoreStatusPtr->EthRunTimeOpertnData.EthControllerMode;
  }
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={602B4D07-5109-4f0d-8F9F-63E9C4FE1369}]  **
**                                                                            **
** Syntax           : static void Eth_17_lConfirmTxFrames(const uint8 CtrlIdx)**
**                                                                            **
** Description      : check transmit buffers and confirm transmitted frames   **
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
static void Eth_17_lConfirmTxFrames(const uint8 CtrlIdx)
{
  Eth_17_GEthMac_TxBuffTableType *CurrTxBuffTablePtr;
  uint32 DescStatus;
  uint8 Count;
  uint8 TxBufTotal;
  const Eth_17_GEthMac_CoreCntrlConfigType *EthLocalCntrlCfgPtr;
  Eth_17_GEthMac_CntrlStatusType *EthLocalCoreStatusPtr;

  /* Get controller configuration data */
  EthLocalCntrlCfgPtr = Eth_17_lGetCtrlConfigPtr(CtrlIdx);
  /* Get controller status */
  EthLocalCoreStatusPtr = Eth_17_lGetCtrlStatusPtr(CtrlIdx);

  TxBufTotal = EthLocalCntrlCfgPtr->EthTxBufTotal;

  /* [cover parentID={4C5EF2C0-10CE-45e5-A45B-9D96C05828B6}]
  Scan status of all Tx Buffers from Tx Buffer Table and Tx Descriptors
  [/cover] */
  /* Start scanning all Tx Buffers. */
  for (Count=ETH_17_GETHMAC_ZERO; Count < TxBufTotal; Count++)
  {
    DescStatus = EthLocalCoreStatusPtr->EthBuffDecPtr->EthDmaTxDescPtr\
           [EthLocalCoreStatusPtr->EthRunTimeOpertnData.ConfirmTxBufIdx].TDES3;
    CurrTxBuffTablePtr = &(EthLocalCoreStatusPtr->EthBuffDecPtr->\
    EthTxBuffTablePtr[EthLocalCoreStatusPtr->EthRunTimeOpertnData.\
                                                             ConfirmTxBufIdx]);
    /* [cover parentID={38C278AD-431C-4186-A1F1-74E2EF87840B}]
    Buffer Status is 'USED' and Transmission is "INITIATED" and Buffer
    is 'RELEASED' by DMA
    [/cover] */
    if((CurrTxBuffTablePtr->BuffStatus == ETH_17_GETHMAC_BUFFER_USED) && \
       (CurrTxBuffTablePtr->FrameTxInitiated == ETH_17_GETHMAC_ONE)&& \
       ((DescStatus & (uint32)ETH_17_GETHMAC_DMA_TX_DESC_OWN_SET) == \
                                                          ETH_17_GETHMAC_ZERO))
    {
      /* [cover parentID={A8AE4067-13CB-451a-B462-6DB44D2CC759}]
      Tx confirmation requested status in buffer table is "REQUESTED"
      [/cover] */
      /* Check if confirmation requested before in Eth_Transmit() API.*/
      if (CurrTxBuffTablePtr->TxConfirmReq == ETH_17_GETHMAC_ONE)
      {
        /* [cover parentID={B7642CCC-7231-4422-9285-6280BFC47B16}]
        Call function to EthIf for Tx Confirmation for "ConfirmTx Buffer Index"
        [/cover] */
        /* Call Back function to EthIf for Tx Confirmation */
        EthIf_TxConfirmation(CtrlIdx, \
               (Eth_BufIdxType)EthLocalCoreStatusPtr->EthRunTimeOpertnData.\
                                                              ConfirmTxBufIdx);
        /* Reset Tx confirmation request. */
        CurrTxBuffTablePtr->TxConfirmReq = ETH_17_GETHMAC_ZERO;
      }

      /* [cover parentID={5638FE58-0447-4462-A97A-C15FEAD261FE}]
      Reset Frame Tx Request status as Transmission 'NOT INITIATED' and Set
      Buffer status as 'FREE'
      [/cover] */
      /*Clear Frame Tx Request Indication */
      CurrTxBuffTablePtr->FrameTxInitiated = ETH_17_GETHMAC_ZERO;
      /* Release the buffer to application use */
      CurrTxBuffTablePtr->BuffStatus = ETH_17_GETHMAC_BUFFER_NOTUSED;
      /* Point to next buffer in the buffer ring */
      EthLocalCoreStatusPtr->EthRunTimeOpertnData.ConfirmTxBufIdx = \
      Eth_17_lIncrTxBufIdx(EthLocalCoreStatusPtr->EthRunTimeOpertnData.\
                                                   ConfirmTxBufIdx,TxBufTotal);
    }
    else
    {
      /* Buffer unused or not released by DMA, break for Loop */
      break;
    }
  }
}
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={9138DCE0-663B-4fca-B99C-01F569C7A337}]  **
**                                                                            **
** Syntax           : static uint32 Eth_17_lReceiveFrames(const uint8 CtrlIdx)**
**                                                                            **
** Description      : Function to scan all Rx Buffers for new Frames          **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx - Controller Index                              **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : ApplIndication-                                         **
                         ETH_17_GETHMAC_ONE: EthIf_RxIndication called        **
**                       ETH_17_GETHMAC_ZERO: EthIf_RxIndication not called   **
**                                                                            **
*******************************************************************************/
static uint32 Eth_17_lReceiveFrames(const uint8 CtrlIdx)
{
  uint32 ApplIndication;
  uint32 DescStatRDES1;
  uint32 DescStatRDES3;
  uint32 ConxtDescRDES3;
  uint16 RxLength;
  uint16 FrameType;
  uint8 ConxtDescPosition;
  uint8 BufferCount;
  uint8 TempVar;
  uint8 RxBufferClearStartIdx;
  uint8 RxBufTotal;
  boolean BroadcastState;
  const Eth_17_GEthMac_CoreCntrlConfigType *EthLocalCntrlCfgPtr;
  Eth_17_GEthMac_CntrlStatusType *EthLocalCoreStatusPtr;
  Eth_17_GEthMac_DmaRxDescType *EthLocalDmaRxDescPtr;
  uint8 IntEnabled;
  const volatile uint8 *RxBuffBasePtr;
  uint16 RxBufLengthAligned;
  uint8 CrcStripEnabled;
  uint8* CurrentBufferPtr;
  uint8 BufferClearCount;
  /*ApplIndication is set to zero*/
  ApplIndication = (uint32)ETH_17_GETHMAC_ZERO;
  /* Get controller configuration data */
  EthLocalCntrlCfgPtr = Eth_17_lGetCtrlConfigPtr(CtrlIdx);
  /* Get controller status */
  EthLocalCoreStatusPtr = Eth_17_lGetCtrlStatusPtr(CtrlIdx);
  EthLocalDmaRxDescPtr = EthLocalCoreStatusPtr->EthBuffDecPtr->\
                                                              EthDmaRxDescPtr;
  RxBufTotal = EthLocalCntrlCfgPtr->EthRxBufTotal;
  IntEnabled = (uint8)((EthLocalCntrlCfgPtr->EthCntrlProperties >> \
                           ETH_17_GETHMAC_RXINT_POS) & ETH_17_GETHMAC_ONE);
  RxBufLengthAligned = EthLocalCntrlCfgPtr->EthCtrlRxBufLenByteAligned;

  RxBuffBasePtr = &(EthLocalCoreStatusPtr->EthBuffDecPtr->\
                                         EthRxBufferPtr[ETH_17_GETHMAC_ZERO]);
  /* Info: Fror receive operation descriptors are configured to store exactly
     one ethernet frame.
     i.e received frames are not spread across multiple descriptors, If length
     of the recevied frame is greater than length of the descriptor then these
     frames are not received. */
  /* [cover parentID={AF4DC9F6-4D81-492a-B8EF-7E2B275917A0}]
  Loop to scan all Rx buffers
  [/cover] */
  for(BufferCount = ETH_17_GETHMAC_ZERO;BufferCount < RxBufTotal;BufferCount++)
  {
    /* Read DMA Rx Descriptor status from RDES3 of Eth_CurrRxDmaDescIdx. */
    DescStatRDES3 = EthLocalDmaRxDescPtr\
    [EthLocalCoreStatusPtr->EthRunTimeOpertnData.CurrRxDmaDescIdx].RDES3;
    /* Check if Rx buffer of current Eth_CurrRxDmaDescIdx is released by DMA.
    Info: In polling mode, only one Rx notification is given per call of
    Eth_Receive.
    Note: In interrupt mode, Rx notification is given for all received packet
    currently */
    /* BufferClearCount variable counts number of bufers to be released.
    Initialised to zero here */
    BufferClearCount = 0U;
    /* [cover parentID={42A70085-C7DD-4ad4-A8E4-FF860B5C245B}]
    [/cover] */
    if(((DescStatRDES3 & (uint32)ETH_17_GETHMAC_DMA_RX_DESC_OWN_SET) == \
     ETH_17_GETHMAC_ZERO) && (((IntEnabled == ETH_17_GETHMAC_ZERO) && \
     (ApplIndication == ETH_17_GETHMAC_ZERO)) || \
     (IntEnabled == ETH_17_GETHMAC_ONE)))
    {
      /* BufferClearCount inceremented to release one descriptor */
      BufferClearCount++;
      RxBufferClearStartIdx = EthLocalCoreStatusPtr->EthRunTimeOpertnData.\
                                                             CurrRxDmaDescIdx;
      /* Check if first Descriptor bit (FD) and Last Descriptor bit (LD)
                                           is set for Eth_CurrRxDmaDescIdx.*/
      /* [cover parentID={C2D36C35-D560-49fa-9122-9361F4251DFD}]
      [/cover] */
      if(((DescStatRDES3 & (uint32)ETH_17_GETHMAC_DMA_RX_DESC_FD_SET) == \
      (uint32)ETH_17_GETHMAC_DMA_RX_DESC_FD_SET) && ((DescStatRDES3 & \
                       (uint32)ETH_17_GETHMAC_DMA_RX_DESC_LD_SET) == \
                               (uint32)ETH_17_GETHMAC_DMA_RX_DESC_LD_SET))
      {
        /*Read RDES1 to get time stamp availability status */
        /* [cover parentID={12BB54B7-532C-4e75-9E24-02EED3E7CE14}]
        [/cover] */
        DescStatRDES1 = EthLocalDmaRxDescPtr[RxBufferClearStartIdx].RDES1;
        /* Get length of the received frame */
        RxLength = (uint16)(DescStatRDES3 & \
                              (uint32)ETH_17_GETHMAC_DMA_RX_DESC_PL_MASK);
        CrcStripEnabled = (uint8)((EthLocalCntrlCfgPtr->EthCntrlProperties >> \
                          ETH_17_GETHMAC_CRCS_POS) & ETH_17_GETHMAC_ONE);
        /* [cover parentID={DB45F5B0-FF80-4e48-96AE-083145E61013}]
        If CRC stripping is enabled
        [/cover] */
        if(CrcStripEnabled == ETH_17_GETHMAC_ONE)
        {
          /* [cover parentID={04891CDB-6993-4a4a-B4F1-E29730E3BD24}]
          update the Rx frame length
          [/cover] */
          RxLength = RxLength - \
                   ((uint16)(ETH_17_GETHMAC_FRAMEHEADER_LENGTH + \
                                        ETH_17_GETHMAC_FRAMECHKSUM_LENGTH));
        }
        else
        {
          /* [cover parentID={791E2487-160A-4ef2-9054-31E84F4B66AD}]
          update the Rx frame length
          [/cover] */
          RxLength = RxLength - (uint16)ETH_17_GETHMAC_FRAMEHEADER_LENGTH;
        }
        /* get pointer to the received data buffer */
        /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between integer to a
        pointer type is performed to fetch buffer address from DMA
        descriptor. This is the intended design and valid as per DMA hardware
        design. There are no side effects seen by violating this rule.*/
        /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from unsigned long to pointer
        is performed to access the buffer address from DMA descriptor.
        This is the intended design and valid as per DMA hardware design.
        There are no side effects seen by violating this rule.*/
        /* [cover parentID={BA499FCE-42E0-4900-8EC2-C8B316D1169B}]
        Extract packet length, frame type, broadcast state
        and time stamp availability status
        [/cover] */
        CurrentBufferPtr = (uint8*)EthLocalDmaRxDescPtr\
                                                 [RxBufferClearStartIdx].RDES0;
        /* Get Frame Type of he received frame */
        FrameType = ((uint16)(((uint16)(((uint16)CurrentBufferPtr\
        [ETH_17_GETHMAC_FRAME_TYPE_POS_MSB]) << (ETH_17_GETHMAC_SHIFT_8BIT)))\
        |((uint16)CurrentBufferPtr[ETH_17_GETHMAC_FRAME_TYPE_POS_LSB])));
        /* Check if frame received is broadcast */
        BroadcastState = Eth_17_lIsBroadcastAddress(&(CurrentBufferPtr\
                                        [ETH_17_GETHMAC_FRAME_DESTADDR_POS]));
        /* Check if the time stamp is available for the current frame.*/
        /* [cover parentID={06D64487-78E2-42fa-A716-DB183E547F5A}]
        [/cover] */
        if((DescStatRDES1 & (uint32)ETH_17_GETHMAC_DMA_RX_DESC_TSA_SET) == \
                                   (uint32)ETH_17_GETHMAC_DMA_RX_DESC_TSA_SET)
        {
          /* Increment Eth_CurrRxDmaDescIdx,next is a context descriptor
          Info :Context descriptor is used only for time stamp storage,
          Buffer assigned to this descriptor will not be used. Next packet
          will be stored to buffer of descriptor after this context
          descriptor. Hence,increment Current Rx Dma descriptor index*/
          ConxtDescPosition = \
            Eth_17_lIncrRxBufIdx(RxBufferClearStartIdx, RxBufTotal);
          ConxtDescRDES3 = EthLocalDmaRxDescPtr[ConxtDescPosition].RDES3;
          EthLocalCoreStatusPtr->EthRunTimeOpertnData.CurrRxDmaDescIdx =\
                                                            ConxtDescPosition;
          /* BufferClearCount inceremented to release context descriptor */
          BufferClearCount ++;
          /* Check if timestamp is available in the context descriptor */
          /* [cover parentID={64DBBF0D-BE64-4175-A72C-149175DA9C24}]
          [/cover] */
          if((ConxtDescRDES3 & (uint32)ETH_17_GETHMAC_DMA_RX_DESC_CTXT_SET)\
                            == (uint32)ETH_17_GETHMAC_DMA_RX_DESC_CTXT_SET)
          {

            /*For time stamp retrieval, mark the Rx Descriptor index.*/
            /* [cover parentID={72463052-5A3A-4916-8237-B52170239B71}]
            For time stamp retrieval, mark the Rx Descriptor index
            [/cover] */
            EthLocalCoreStatusPtr->EthRunTimeOpertnData.\
                                RxDmaDesIdxForIngTimStamp = ConxtDescPosition;
          }
          else
          {
            /* Reset time stamp availability as Not Available*/
            /* [cover parentID={FC696905-E01A-40b9-8F79-7DA941F711CD}]
            Reset time stamp availability as Not Available
            [/cover] */
            EthLocalCoreStatusPtr->EthRunTimeOpertnData.\
                                              RxDmaDesIdxForIngTimStamp = \
                                               ETH_17_GETHMAC_TIMESTAMP_NA;
          }
        }
        else
        {
           /* Reset time stamp availability as Not Available*/
           /* [cover parentID={A36224DA-2D94-4ce1-9214-731D329AE3F3}]
           [/cover] */
           EthLocalCoreStatusPtr->EthRunTimeOpertnData.\
                                              RxDmaDesIdxForIngTimStamp = \
                                               ETH_17_GETHMAC_TIMESTAMP_NA;
        }
        /* [cover parentID={7F85C673-5370-4c3d-AFA5-9A7BD22081E8}]
        Indicate Application about Rx frame
        Eth_17_lRemoveFromFilter[/cover] */
        /* Application indication of Rx frame */
        EthIf_RxIndication(CtrlIdx,FrameType,BroadcastState, \
        &(CurrentBufferPtr[ETH_17_GETHMAC_FRAME_SRCADDR_POS]),(uint8 *)&\
        (CurrentBufferPtr[ETH_17_GETHMAC_FRAME_PAYLOAD_POS]),RxLength);
        /* Mark one indication to application done - used in poilling mode*/
        ApplIndication = ETH_17_GETHMAC_ONE;
      }

      /*Free all Descriptors holding the Ethernet frame to DMA.*/
      /* [cover parentID={5CA35061-D881-417e-8464-C06DF1C5EBE8}]
      [/cover] */
      for(TempVar=ETH_17_GETHMAC_ZERO; TempVar < BufferClearCount; TempVar++)
      {
        /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between integer to a
          pointer type is performed to access the buffer address from DMA
          descriptor. This is the intended design and valid as per DMA hardware
          design. There are no side effects seen by violating this rule.*/
        /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from unsigned long to pointer
          is performed to access the buffer address from DMA descriptor.
          This is the intended design and valid as per DMA hardware design.
          There are no side effects seen by violating this rule.*/
        /* MISRA2012_RULE_10_8_JUSTIFICATION: Impermissible cast of composite
          expression is performed to access the buffer address from DMA
          descriptor. This is the intended design and valid as per DMA hardware
          design. There are no side effects seen by violating this rule.*/
        /* MISRA2012_RULE_18_4_JUSTIFICATION: pointer arithmetic is performed
        using '+' operator to configure the RAM address in DMA descriptors.
        This is the intended design and valid as per DMA hardware
        design. There are no side effects seen by violating this rule.*/
        EthLocalDmaRxDescPtr[RxBufferClearStartIdx].RDES0 =\
          (uint32)(RxBuffBasePtr + \
          (((uint32)(RxBufferClearStartIdx)) * ((uint32)RxBufLengthAligned)));

        EthLocalDmaRxDescPtr[RxBufferClearStartIdx].RDES1 = \
                                                      ETH_17_GETHMAC_ZERO;
        /* Descriptor Buffer2 poiter not used */
        EthLocalDmaRxDescPtr[RxBufferClearStartIdx].RDES2 = \
                                                      ETH_17_GETHMAC_ZERO;
        /* Info :While releasing each time, Buffer 1 valid to be set*/
        EthLocalDmaRxDescPtr[RxBufferClearStartIdx].RDES3 = (uint32)
                        (((uint32)ETH_17_GETHMAC_DMA_RX_DESC_BF1_VALID) | \
                        ((uint32)ETH_17_GETHMAC_DMA_RX_DESC_BF2_INVALID)| \
                        ((uint32)ETH_17_GETHMAC_DMA_RX_DESC_IOC_ENABLE) | \
                        ((uint32)ETH_17_GETHMAC_DMA_RX_DESC_OWN_SET));
        RxBufferClearStartIdx = Eth_17_lIncrRxBufIdx(RxBufferClearStartIdx,\
                                                                  RxBufTotal);
      }
      /* Increment Current Rx Dma descriptor index */
      EthLocalCoreStatusPtr->EthRunTimeOpertnData.CurrRxDmaDescIdx = \
                               Eth_17_lIncrRxBufIdx(EthLocalCoreStatusPtr->\
                           EthRunTimeOpertnData.CurrRxDmaDescIdx,RxBufTotal);
    }
    else
    {
      /* Descriptor still owned by DMA or One application indication done
      break the loop */
      /* [cover parentID={5BBF3A1A-444F-426e-AB03-C7153C144E61}]
      Descriptor still owned by DMA or One application indication
      done break the loop
      [/cover] */
      break;
    }
  }
  return ApplIndication;
}
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={9B7F6A5C-ADD3-438d-8DAD-ED06DB87D147}]  **
**                                                                            **
** Syntax           : LOCAL_INLINE void Eth_17_lSetPhysAddr(                  **
**                              uint8* const MacAddr, const uint8 CtrlIdx )   **
**                                                                            **
** Description      : Sets the physical source address for the controller     **
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
** Parameters (in)  : MacAddr  - Physical source address (MAC address) in     **
**                    network byte order.                                     **
**                    CtrlIdx - Controller Index                              **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Eth_17_lSetPhysAddr(const uint8* const MacAddr,
                                                           const uint8 CtrlIdx)
{
  uint32 DataVal;
  Ifx_GETH *EthCntrlAdd;
  /* Get base address of the indexed controller */
  EthCntrlAdd = Eth_GEthMacCntrl[CtrlIdx];

  /* Extract Byte 5 and Byte 6. */
  DataVal = ((((uint32)MacAddr[5])<<ETH_17_GETHMAC_SHIFT_8BIT) | \
             ((uint32)MacAddr[4]) | (ETH_17_GETHMAC_MACADDRRESS_ENABLE));
  /* Write upper 16 bit of Physical address to MAC Address0 High Register */
  EthCntrlAdd->MAC_ADDRESS_HIGH0.U = (uint32)DataVal;

  /* Extract Byte 1,2,3 and 4. */
  DataVal = (uint32)((((uint32)MacAddr[3]) << ETH_17_GETHMAC_SHIFT_24BIT) |\
                     (((uint32)MacAddr[2]) << ETH_17_GETHMAC_SHIFT_16BIT) |\
                     (((uint32)MacAddr[1]) << ETH_17_GETHMAC_SHIFT_8BIT)  |\
                       MacAddr[0]);
  /*Write lower 4 bytes of Physical address to MAC Address0 low Register*/
  EthCntrlAdd->MAC_ADDRESS_LOW0.U = (uint32)DataVal;
}
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={D0CA86BE-3822-4705-8B21-0BE35320CA0A}]  **
**                                                                            **
** Syntax           : LOCAL_INLINE void Eth_17_lGetPhysAddr                   **
**                             (uint8* const MacAddr, const uint8 CtrlIdx )   **
**                                                                            **
** Description      : Obtains the physical source address used by the         **
**                    controller                                              **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : MacAddr  - Physical source address (MAC address) in     **
**                    network byte order.                                     **
**                    CtrlIdx - Controller Index                              **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Eth_17_lGetPhysAddr(uint8* const MacAddr, const uint8 CtrlIdx)
{
  uint32 DataVal;
  const Ifx_GETH *EthCntrlAdd;
  /* [cover parentID={A535A3CA-2480-4eca-9CFC-16F9BE7E7D23}]
  Read Physical Source Address from MAC Address Register 0 and write into
  Physical Address Pointer
  [/cover] */
  /* Get base address of the indexed controller */
  EthCntrlAdd = Eth_GEthMacCntrl[CtrlIdx];
  DataVal = (uint32)(EthCntrlAdd->MAC_ADDRESS_HIGH0.U);
  /* Extract Byte 5 and Byte 6. */
  MacAddr[5] = (uint8)((DataVal >> ETH_17_GETHMAC_SHIFT_8BIT) & \
                                       ETH_17_GETHMAC_BYTE0_MASK);
  MacAddr[4] = (uint8)(DataVal & ETH_17_GETHMAC_BYTE0_MASK);

  /* Extract Byte 1,2,3 and 4. */
  DataVal = (uint32)(EthCntrlAdd->MAC_ADDRESS_LOW0.U);

  MacAddr[3] =(uint8)((DataVal >> ETH_17_GETHMAC_SHIFT_24BIT) & \
                                       ETH_17_GETHMAC_BYTE0_MASK);
  MacAddr[2] =(uint8)((DataVal >> ETH_17_GETHMAC_SHIFT_16BIT) & \
                                       ETH_17_GETHMAC_BYTE0_MASK);
  MacAddr[1] =(uint8)((DataVal >> ETH_17_GETHMAC_SHIFT_8BIT) & \
                                       ETH_17_GETHMAC_BYTE0_MASK);
  MacAddr[0] =(uint8)(DataVal & ETH_17_GETHMAC_BYTE0_MASK);
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={1E24863A-5AD0-4b64-ABA8-96A87F9A8486}]  **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Eth_17_lIncrRxBufIdx                 **
**                                                     (const uint8 RxBufIdx )**
**                                                                            **
** Description      : Move RX buffer index to next index in ring buffer       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : RxBufIdx - Current Rx Buffer Index                      **
**                    EthRxBufTotal - Rx Buffer Length Total                  **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Next Rx index in ring buffer                            **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Eth_17_lIncrRxBufIdx (const uint8 RxBufIdx,
                                                     const uint8 EthRxBufTotal)
{
  return ((RxBufIdx+1U) % (EthRxBufTotal));
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={38D92E39-2BA9-4c61-88A4-D8ABC9545667}]  **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Eth_17_lIncrTxBufIdx                 **
**                                                      (const uint8 TxBufIdx)**
**                                                                            **
** Description      : Move TX buffer index to next index in ring buffer       **
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
** Parameters (in)  : TxBufIdx - Current Tx Buffer Index                      **
**                    EthTxBufTotal - Tx Buffer Length Total                  **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Next Tx index in ring buffer                            **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Eth_17_lIncrTxBufIdx(const uint8 TxBufIdx,
                                                     const uint8 EthTxBufTotal)
{
  return ((TxBufIdx+1U) % (EthTxBufTotal));
}
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={21D82E6E-F0D1-4937-A775-F18683A98F98}]  **
**                                                                            **
** Syntax           : LOCAL_INLINE boolean Eth_17_lIsBroadcastAddress(        **
**                                               const uint8* const MacAddr)  **
**                                                                            **
** Description      : This function returns TRUE if the MAC address is a      **
**                    broadcast address                                       **
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
** Parameters (in)  : MacAddr - MAC address                                   **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : TRUE - MAC adderess is a broadcast address              **
**                    FALSE - MAC adderess is not a broadcast address         **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE boolean Eth_17_lIsBroadcastAddress(const uint8* const MacAddr)
{
  boolean RetVal;

  if( (MacAddr[0] == 0xFFU)&&(MacAddr[1] == 0xFFU)&&\
      (MacAddr[2] == 0xFFU)&&(MacAddr[3] == 0xFFU)&&\
      (MacAddr[4] == 0xFFU)&&(MacAddr[5] == 0xFFU) )
  {
    /* MAC address is a broadcase address. */
    RetVal = TRUE;
  }
  else
  {
    /*If any byte of MAC address is not FF return false */
    RetVal = FALSE;
  }
return RetVal;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={8F5C8EB4-8E01-4544-8953-0B1B28CE5B86}]  **
**                                                                            **
** Syntax           : static boolean Eth_17_lIsNextFrameAvailable(const uint8 **
**                                                             CtrlIdx)       **
**                                                                            **
** Description      : This function returns TRUE if next frame is availabe    **
**                    in buffers.                                             **
**                    This local API is required only in polling mode of Rx   **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx - Controller Index                              **
**                                                                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : TRUE - Next frame available                             **
**                    FALSE - Next frame not available                        **
**                                                                            **
*******************************************************************************/
static boolean Eth_17_lIsNextFrameAvailable(const uint8 CtrlIdx)
{
  uint32 DescStatus,LoopExit;
  uint8 RxBufferScanIdx;
  uint8 LoopCount;
  uint8 RxBufTotal;
  boolean RetVal = FALSE;
  const Eth_17_GEthMac_CoreCntrlConfigType *EthLocalCntrlCfgPtr;
  const Eth_17_GEthMac_CntrlStatusType     *EthLocalCoreStatusPtr;

  /* Get controller configuration data */
  EthLocalCntrlCfgPtr = Eth_17_lGetCtrlConfigPtr(CtrlIdx);
  /* Get controller status */
  EthLocalCoreStatusPtr = Eth_17_lGetCtrlStatusPtr(CtrlIdx);
  /* Read Rx DMA descriptor status by reading RDES3 */
  DescStatus = EthLocalCoreStatusPtr->EthBuffDecPtr->EthDmaRxDescPtr\
         [EthLocalCoreStatusPtr->EthRunTimeOpertnData.CurrRxDmaDescIdx].RDES3;
  LoopExit = ETH_17_GETHMAC_ZERO;
  RxBufTotal = EthLocalCntrlCfgPtr->EthRxBufTotal;

  /* [cover parentID={5DE21AA5-AD6B-4a1f-81AF-208A8DEC0D73}]
  Rx Descriptor is released by DMA and FD bit (First descriptor bit) is
  set in descriptor
  [/cover] */
  /*Check if Desc is not owned by DMA , FD bit is set for the received frame */
  if(((DescStatus & (uint32)ETH_17_GETHMAC_DMA_RX_DESC_OWN_SET) == \
                                                   ETH_17_GETHMAC_ZERO) && \
       ((DescStatus & (uint32)ETH_17_GETHMAC_DMA_RX_DESC_FD_SET) ==\
                          (uint32)ETH_17_GETHMAC_DMA_RX_DESC_FD_SET))
  {
    /* Started receiving next packet, mark desc of start of packet */
    RxBufferScanIdx = EthLocalCoreStatusPtr->EthRunTimeOpertnData.\
                                                              CurrRxDmaDescIdx;

    /* [cover parentID={89D6BF02-14EE-422c-A321-47BFC4E77932}]
    Loop to Scan all Rx descriptors until LD(Last Descriptor) bit is found Set
    [/cover] */
    /* Loop for number total Rx buffer and until LD bit set*/
    for(LoopCount = ETH_17_GETHMAC_ZERO; LoopCount < RxBufTotal; LoopCount++)
    {
      /* Read Rx DMA descriptor status by reading RDES3 */
      DescStatus = EthLocalCoreStatusPtr->EthBuffDecPtr->\
                                       EthDmaRxDescPtr[RxBufferScanIdx].RDES3;
      /* [cover parentID={8CA9C5D6-2F67-4200-B5D0-6215E92D71BD}]
      Descriptor  is released by DMA
      [/cover] */
      /*Check if Desc is not owned by DMA and LS bit is set for the
      received frame */
      if((DescStatus & (uint32)ETH_17_GETHMAC_DMA_RX_DESC_OWN_SET) == \
                                                            ETH_17_GETHMAC_ZERO)
      {
        /* [cover parentID={D347157D-4568-4008-B04D-45705077391F}]
        LD (Last descriptor) bit is set
        [/cover] */
        if((DescStatus & (uint32)ETH_17_GETHMAC_DMA_RX_DESC_LD_SET) ==\
                             (uint32)ETH_17_GETHMAC_DMA_RX_DESC_LD_SET)
        {
          /* Only if FS and LS bits are set, a complete frame is available */
          RetVal = TRUE;
          LoopExit = ETH_17_GETHMAC_ONE;
        }
      }
      else
      {
        /*Buffers are still owned by DMA, end of frame not received*/
        LoopExit = ETH_17_GETHMAC_ONE;
      }
      /* [cover parentID={625A230E-D3D1-4218-A0EE-4337144F5FBB}]
      Loop Exit is TRUE
      [/cover] */
      if(ETH_17_GETHMAC_ONE == LoopExit)
      {
        break;
      }
      /* Move to next to check if LS bit is set */
      RxBufferScanIdx = Eth_17_lIncrRxBufIdx(RxBufferScanIdx,RxBufTotal);
    }
  }
  else
  {
    /* Do nothing Return False,indicating next frame not available.
    Because Buffers are still owned by DMA.   */
  }
  return RetVal;
}
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={5DCA53D4-3491-460e-BF76-6AFC3E5E555A}]  **
**                                                                            **
** Syntax           : static void Eth_17_lClearAllAddressFilters(const uint8  **
**                                                                 CtrlIdx)   **
**                                                                            **
** Description      : This function clears all MAC filters register           **
**                    from 0 to 31                                            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx - Controller Index                              **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_lClearAllAddressFilters(const uint8 CtrlIdx)
{
  uint32 Count;
  uint32 NumberOfFilters;
  Ifx_GETH *EthCntrlAdd;
  Eth_17_GEthMac_MacAddr_1_31Type *EthMacFilterAdd;
  EthCntrlAdd = Eth_GEthMacCntrl[CtrlIdx];

  /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between pointers to a
     different object types is performed for SFR access. There are no side
     effects seen by violating this rule. */
  /* Base Address for MAC address register 1- High and Low for the ETH
  controller */
  EthMacFilterAdd = \
  ((Eth_17_GEthMac_MacAddr_1_31Type*)Eth_HighBaseAddress[CtrlIdx]);
  /* Set default value to Address register 0. */
  /* Info: Address register 0 is always enabled. */
  /* [cover parentID={42A326CA-0943-4aa7-A24F-40C1475E2D8B}]
  [/cover] */
  EthCntrlAdd->MAC_ADDRESS_HIGH0.U = ETH_17_GETHMAC_FILT0_DEF_HIGH_VAL;
  EthCntrlAdd->MAC_ADDRESS_LOW0.U = ETH_17_GETHMAC_FILT0_DEF_LOW_VAL;

  /* First MAC address filter register is already initialized.
     Hence reduce 1.*/
  NumberOfFilters = ETH_17_GETHMAC_NO_OF_FILTER_REGISTERS - ETH_17_GETHMAC_ONE;
  /* Clear all Filter registers from 1 to 31 and disable the register */
  /* [cover parentID={64F137B2-1A5B-4e41-869B-78068EAA1A2E}]
  [/cover] */
  for(Count = ETH_17_GETHMAC_ZERO; Count < NumberOfFilters; Count++)
  {
    EthMacFilterAdd[Count].AddrHigh.U = \
    (uint32)ETH_17_GETHMAC_FILT_1_31_DEF_HIGH_VAL;

    EthMacFilterAdd[Count].AddrLow.U = \
    (uint32)ETH_17_GETHMAC_FILT_1_31_DEF_LOW_VAL;
  }
}
/* Local API's for Update PHY Filters */
#if (ETH_17_GETHMAC_UPDATE_PHY_ADDR_FILTER_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={31F08BE4-1FE4-4215-B314-CBA577556447}]  **
**                                                                            **
** Syntax           : LOCAL_INLINE boolean Eth_17_lIsAllZeroAddress(          **
**                                                const uint8* const MacAddr) **
**                                                                            **
** Description      : This function returns TRUE if the MAC address is        **
**                    all Zeros                                               **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : MAC address                                             **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : TRUE - MAC adderess is all Zeros                        **
**                    FALSE - MAC adderess is not all Zeros                   **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE boolean Eth_17_lIsAllZeroAddress(const uint8* const MacAddr)
{
  boolean RetVal;

  if((MacAddr[0] == ETH_17_GETHMAC_ZERO)&&(MacAddr[1] == ETH_17_GETHMAC_ZERO)&&\
     (MacAddr[2] == ETH_17_GETHMAC_ZERO)&&(MacAddr[3] == ETH_17_GETHMAC_ZERO)&&\
     (MacAddr[4] == ETH_17_GETHMAC_ZERO)&&(MacAddr[5] == ETH_17_GETHMAC_ZERO))
  {
    /* If any byte of MAC address is non-zero return false*/
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }
  return RetVal;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={88F2DB77-A56A-4437-9611-2D534ABC8ED4}]  **
**                                                                            **
** Syntax           : static Std_ReturnType Eth_17_lAddToFilter(              **
**                    const uint8* const MacAddr,const uint8 CtrlIdx)         **
**                                                                            **
** Description      : This function adds a MAC address to filter              **
**                    This local API is required only if filters are supported**
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : MacAddr - Mac Address                                   **
**                    CtrlIdx - Controller Index                              **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK - Address is successfully added to filter          **
**                    E_NOT_OK - Address could not be added to filter         **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Eth_17_lAddToFilter(const uint8* const MacAddr,
                                                           const uint8 CtrlIdx)
{
  uint32 MacAdrressLow;
  uint32 MacAddressHigh;
  uint16 FilterPresenceStatus;
  uint8 IsAddPresent;
  uint8 FreeFilterIdx;
  Std_ReturnType RetVal = E_NOT_OK;
  Eth_17_GEthMac_MacAddr_1_31Type *EthMacFilterAdd;
  /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between pointers to a
    different object types is performed for SFR access. There are no side
    effects seen by violating this rule. */
  /* Base Address for MAC address register 1- High and Low for the ETH
  controller */
  EthMacFilterAdd = \
  (Eth_17_GEthMac_MacAddr_1_31Type*)Eth_HighBaseAddress[CtrlIdx];
  /* Check filter is present already, if not,get free filter register index. */
  FilterPresenceStatus = Eth_17_lCheckFilterPresent(MacAddr,CtrlIdx);
  IsAddPresent = (uint8)(FilterPresenceStatus & \
                          ((uint16)ETH_17_GETHMAC_MASK_LSB));

  /* [cover parentID={6FA91C7E-ECC5-4977-A31C-100824B0F9BC}]
  Filter address is already present
  [/cover] */
  /* Check if same address is not already present in the filter */
  if(IsAddPresent == (uint8)ETH_17_GETHMAC_INVALID_FILTER_VALUE)
  {
    /* Extract free filter register index from FilterPresenceStatus. */
    FreeFilterIdx = (uint8)(FilterPresenceStatus >> ETH_17_GETHMAC_SHIFT_8BIT);

    MacAdrressLow = (uint32)\
                    ((((uint32)MacAddr[3]) << ETH_17_GETHMAC_SHIFT_24BIT) |\
                     (((uint32)MacAddr[2]) << ETH_17_GETHMAC_SHIFT_16BIT) |\
                     (((uint32)MacAddr[1]) << ETH_17_GETHMAC_SHIFT_8BIT)  |\
                     (uint32)MacAddr[0]);

    MacAddressHigh = (uint32)(((uint32)MacAddr[5] << \
                              ETH_17_GETHMAC_SHIFT_8BIT) | (uint32)MacAddr[4]);
    /* [cover parentID={FCDBBCBC-CF9E-4ee4-A606-317DC261C4BF}]
    Free filter register index is valid
    [/cover] */
    /* If free filter register index is valid, update filter address.
    0 to 30 is valid index. */
    if(FreeFilterIdx != ETH_17_GETHMAC_INVALID_FILTER_VALUE)
    {
      /* [cover parentID={D226BBFB-0724-43c9-9F2E-13F847BFD106}]
      Write Physical address in free MAC address filter register
      [/cover] */
      EthMacFilterAdd[FreeFilterIdx].AddrHigh.U = \
                (uint32)(MacAddressHigh|ETH_17_GETHMAC_MACADDRRESS_ENABLE);

      EthMacFilterAdd[FreeFilterIdx].AddrLow.U = (uint32)MacAdrressLow;
      RetVal = E_OK;
    }
    else
    {
      RetVal = E_NOT_OK;
    }
  }
return RetVal;
}
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={172E58ED-464F-49f6-920E-4950BE1C72D4}]  **
**                                                                            **
** Syntax           : static Std_ReturnType Eth_17_lRemoveFromFilter          **
**                        (const uint8* const MacAddr, const uint8 CtrlIdx)   **
**                                                                            **
** Description      : This function removes a MAC address from filter         **
**                    This local API is required only if filters are supported**
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : MacAddr - Mac Address                                   **
**                    CtrlIdx - Controller Index                              **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK - Address is successfully removed from filter      **
**                    E_NOT_OK - Address could not be removed from filter     **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Eth_17_lRemoveFromFilter(const uint8* const MacAddr,
                                                           const uint8 CtrlIdx)
{
  uint16 FilterPresenceStatus;
  uint8 FilterPresentIdx;
  Std_ReturnType RetVal = E_NOT_OK;
  Eth_17_GEthMac_MacAddr_1_31Type *EthMacFilterAdd;
  /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between pointers to a
   different object types is performed for SFR access. There are no side
   effects seen by violating this rule. */
  /* Base Address for MAC address register 1- High and Low for the ETH
  controller */
  EthMacFilterAdd = \
  (Eth_17_GEthMac_MacAddr_1_31Type*)Eth_HighBaseAddress[CtrlIdx];

  /* [cover parentID={0FE6EAA8-6E70-4a1d-94BE-513B922ECE8D}]
  Check if the MAC physical address exists in the filter set
  (The function return filter present status with as filter register index,
  where the filter is present)
  [/cover] */
  /* Check if the MAC address exists in the filter set */
  FilterPresenceStatus = Eth_17_lCheckFilterPresent(MacAddr,CtrlIdx);
  FilterPresentIdx = (uint8)(FilterPresenceStatus & \
                                            ((uint16)ETH_17_GETHMAC_MASK_LSB));

  /* [cover parentID={68AA411A-FE1C-449f-9CEA-667EEB34D003}]
  Remove address from filter register ( where address is present) and
  fill the address register with reset value
  [/cover] */
  /* [cover parentID={336DF574-8C3A-4f8e-A11C-65D4203C34F7}]
  Address present in filter set
  [/cover] */
  /* If FilterPresentIdx is valid, update that address register with default.
     0 to 30 is valid index. */
  if(FilterPresentIdx != ETH_17_GETHMAC_INVALID_FILTER_VALUE)
  {
    EthMacFilterAdd[FilterPresentIdx].AddrHigh.U = \
                        (uint32)ETH_17_GETHMAC_FILT_1_31_DEF_HIGH_VAL;

    EthMacFilterAdd[FilterPresentIdx].AddrLow.U = \
                        (uint32)ETH_17_GETHMAC_FILT_1_31_DEF_LOW_VAL;
    RetVal = E_OK;
  }
  else
  {
    /*FilterPresentIdx value is invalid or out of range */
    RetVal = E_NOT_OK;
  }
  return RetVal;
}
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={57D81105-7602-4309-A623-F7A51C649FA2}]  **
**                                                                            **
** Syntax           : static uint16 Eth_17_lCheckFilterPresent(               **
**                    const uint8* const MacAddr,const uint8 CtrlIdx)         **
**                                                                            **
** Description      : This function returns the filter index where the address**
**                    is present.If address is not present,it return free     **
**                    filter register index, where new filter value can be    **
**                    programmed.                                             **
**                    This local API is required only if filters are supported**
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : MacAddr - Mac Address                                   **
**                    CtrlIdx - Controller Index                              **
**                                                                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Byte 0 - If address already present,index of it.        **
**                    Byte 1 - If address already not present,index of free   **
**                             filter register index.                         **
**                    If Byte 0 is 0xFF means - address not already present   **
**                    If Byte 1 is 0xFF means - no free free filter register  **
**                                                                            **
*******************************************************************************/
static uint16 Eth_17_lCheckFilterPresent(const uint8* const MacAddr,
                                                           const uint8 CtrlIdx)
{
  uint32 DataValHigh,DataValLow,DataValLowReg,DataValHighReg;
  uint8 Count;
  uint16 RetVal;
  uint8 FreeFilterIdx = ETH_17_GETHMAC_INVALID_FILTER_VALUE;
  uint8 IsAddPresent = ETH_17_GETHMAC_INVALID_FILTER_VALUE;
  uint8 NumberOfFilters;
  const Eth_17_GEthMac_MacAddr_1_31Type *EthMacFilterAdd;
  /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between pointers to a
    different object types is performed for SFR access. There are no side
    effects seen by violating this rule. */
  /* Base Address for MAC address register 1- High and Low for the ETH
  controller */
  EthMacFilterAdd = \
  (Eth_17_GEthMac_MacAddr_1_31Type*)Eth_HighBaseAddress[CtrlIdx];
  /* Exclude first MAC address filter register.*/
  NumberOfFilters = (uint8)\
                   (ETH_17_GETHMAC_NO_OF_FILTER_REGISTERS - ETH_17_GETHMAC_ONE);

  DataValHigh = (uint32)(ETH_17_GETHMAC_MACADDRRESS_ENABLE | \
                        ((uint32)MacAddr[5] << ETH_17_GETHMAC_SHIFT_8BIT) | \
                         (uint32)MacAddr[4]);
  DataValLow = (uint32)((((uint32)MacAddr[3]) << ETH_17_GETHMAC_SHIFT_24BIT) | \
                        (((uint32)MacAddr[2]) << ETH_17_GETHMAC_SHIFT_16BIT) | \
                        (((uint32)MacAddr[1]) << ETH_17_GETHMAC_SHIFT_8BIT)  | \
                          (uint32)MacAddr[0]);
  /* [cover parentID={79EA58CD-347B-490f-8ADE-B3BEADCEE330}]
  Loop to scan MAC filter address registers 1 to 31
  [/cover] */
  /* Scan address filter registers from 1 to 31. */
  for(Count = ETH_17_GETHMAC_ZERO; Count < NumberOfFilters; Count++)
  {
    /* [cover parentID={B72BFA92-BD61-4cc6-87FC-2C35E9DB60F4}]
    MAC filter address register is enabled
    [/cover] */
    if(EthMacFilterAdd[Count].AddrHigh.B.AE == ETH_17_GETHMAC_ONE)
    {
      /* [cover parentID={C68F6730-BD02-43b3-9D58-34AA7287C69F}]
      Is address in filter register equal to physical address to be added
      [/cover] */
      /* If Filter register is enabled, check address is already programmed.*/
      DataValHighReg = (uint32)EthMacFilterAdd[Count].AddrHigh.U;

      DataValLowReg = (uint32)EthMacFilterAdd[Count].AddrLow.U;

      if((DataValHighReg == DataValHigh)&&(DataValLowReg == DataValLow))
      {
        /* Filter already applied */
        IsAddPresent = Count;
        break;
      }
    }
    else
    {
      /* [cover parentID={125EF457-DBD3-4ea6-9FA1-721456299878}]
      Is Free filter index value INVALID
      [/cover] */
      /* Filter is free. Now  assign FreeFilterIdx only if not done already.*/
      if(FreeFilterIdx == ETH_17_GETHMAC_INVALID_FILTER_VALUE)
      {
        FreeFilterIdx = Count;
      }
    }
  }
  RetVal  = (uint16)((uint16)FreeFilterIdx << ETH_17_GETHMAC_SHIFT_8BIT);
  RetVal |= (uint16)IsAddPresent;
  return RetVal;
}
#endif /* End of ETH_17_GETHMAC_UPDATE_PHY_ADDR_FILTER_API*/

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={9DF16AAB-4249-41d0-917B-A0F795DF31F8}]  **
**                                                                            **
** Syntax           : static void Eth_17_lDisableGethInterrupt(const          **
**                   Eth_17_GEthMac_CoreCntrlConfigType* const EthCntrlCfgPtr)**
**                                                                            **
** Description      : Clear interrupt status and mask interrupts which are    **
**                    enabled in default                                      **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : NA                                                      **
**                                                                            **
** Parameters (in)  : EthCntrlCfgPtr- Pointer to ethernet Controller          **
**                    Configuration.                                          **
**                                                                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_lDisableGethInterrupt(const
                      Eth_17_GEthMac_CoreCntrlConfigType* const EthCntrlCfgPtr)
{

  Ifx_GETH *EthCntrlAdd;
  uint8 IntEnabled;
  /* Get base address of the indexed controller */
  EthCntrlAdd = Eth_GEthMacCntrl[EthCntrlCfgPtr->EthCntrlIdx];

  /* Mask all interrupts which are enabled in default. */
  EthCntrlAdd->MMC_RX_INTERRUPT_MASK.U = \
                                   (uint32)ETH_17_GETHMAC_DISABLE_MMC_RX_INTPT;

  EthCntrlAdd->MMC_TX_INTERRUPT_MASK.U = \
                                   (uint32)ETH_17_GETHMAC_DISABLE_MMC_TX_INTPT;

  EthCntrlAdd->MMC_IPC_RX_INTERRUPT_MASK.U = \
                               (uint32)ETH_17_GETHMAC_DISABLE_MMC_IPC_RX_INTPT;

  /* If Transmit or Receive Interrupt is enabled in configuration then
     Disable it*/
  IntEnabled = (uint8)((EthCntrlCfgPtr->EthCntrlProperties >>\
                           ETH_17_GETHMAC_TXRXINT_POS) & ETH_17_GETHMAC_THREE);
  /* [cover parentID={45CA2158-C2E2-41a0-8143-A9773D067F42}]
  If Tx or Rx interrupt in enabled
  [/cover] */
  if(IntEnabled!= 0U)
  {
    /* [cover parentID={E3132E6D-08EA-4c49-AA52-010E4CE585BD}]
    [/cover] */
    /* Clear all DMA Channel-0 Interrupt status */
    EthCntrlAdd->DMA_CH[0].STATUS.U = \
                                    (uint32)ETH_17_GETHMAC_DMA_CH_STAT_CLR_ALL;
    /* Disable all DMA Channel-0 Interrupt */
    EthCntrlAdd->DMA_CH[0].INTERRUPT_ENABLE.U = (uint32)ETH_17_GETHMAC_ZERO;
  }
  else
  {
    /* [cover parentID={A0D38071-BC23-47c3-9995-C7DD1910087A}]
    [/cover] */
    /* Clear all DMA Channel-0 Interrupt status */
    EthCntrlAdd->DMA_CH[0].STATUS.U = \
                               (uint32)ETH_17_GETHMAC_DMA_CH_STAT_CLR_ALL;
  }
}

/*******************************************************************************
**                                                                            **
** Traceability     : [cover parentID={B24BEFFA-C842-401d-B44D-01A8CC758B5D}] **
**                                                                            **
** Syntax           : static void Eth_17_lEnableGethInterrupt(const           **
**                  Eth_17_GEthMac_CoreCntrlConfigType* const EthCntrlCfgPtr) **
**                                                                            **
** Description      : Enable DMA Channel-0 Tx and Rx Interrupt                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : NA                                                      **
**                                                                            **
** Parameters (in)  : EthCntrlCfgPtr- Pointer to ethernet Controller          **
**                    Configuration.                                          **
**                                                                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_lEnableGethInterrupt(const
                      Eth_17_GEthMac_CoreCntrlConfigType* const EthCntrlCfgPtr)
{
  uint8 IntEnabled;
  Ifx_GETH *EthCntrlAdd;

  /* Get base address of the indexed controller */
  EthCntrlAdd = Eth_GEthMacCntrl[EthCntrlCfgPtr->EthCntrlIdx];
  IntEnabled = (uint8)((EthCntrlCfgPtr->EthCntrlProperties >> \
                           ETH_17_GETHMAC_TXRXINT_POS) & ETH_17_GETHMAC_THREE);
  /*Clear DMA channel-0 interrupt status bits.*/
  EthCntrlAdd->DMA_CH[0].STATUS.U = (uint32)ETH_17_GETHMAC_DMA_CH_STAT_CLR_ALL;

  /* Enable DMA Channel-0 Interrupt. */
  /* [cover parentID={2BB26295-5E9B-413a-B2D3-32E7A048861A}]
  If Tx and Rx Interrupt is not enabled
  [/cover] */
  if(IntEnabled != ETH_17_GETHMAC_ZERO)
  {
    /* If Transmit or Receive Interrupt is configured, then Enable Normal
    Interrupt- This has to be enabled for Tx and Rx interrupt*/
    /* [cover parentID={7173E569-2F16-437e-91DE-909AC9727123}]
    Enable Normal Interrupt of DMA Channel 0
    [/cover] */
    EthCntrlAdd->DMA_CH[0].INTERRUPT_ENABLE.B.NIE = \
                                            (uint8)ETH_17_GETHMAC_ENABLE;
    /* [cover parentID={576E713E-C36D-4ceb-9B18-6DD6D81C9EBD}]
    If Tx interrupt is enabled
    [/cover] */
    if((IntEnabled & ETH_17_GETHMAC_ONE) == ETH_17_GETHMAC_ONE)
    {
      /* Enable DMA Channel-0 Tx Interrupt. */
      /* [cover parentID={1B5F9860-1C8D-4a2d-91B7-ABD6E1C508FD}]
      Enable DMA Channel 0 Transmit Interrupt
      [/cover] */
      EthCntrlAdd->DMA_CH[0].INTERRUPT_ENABLE.B.TIE = \
                                            (uint8)ETH_17_GETHMAC_ENABLE;
    }
    /* [cover parentID={65F090C7-F761-4b39-8DCD-51D3F80A3982}]
    If Rx Interrupt is enabled
    [/cover] */
    if((IntEnabled & ETH_17_GETHMAC_TWO) == ETH_17_GETHMAC_TWO)
    {
      /* Enable DMA Channel-0 RIE, RBUE and AIE bits. */
      /* [cover parentID={7565BA17-A94F-4c76-BDA8-2C6CF2BA5450}]
      Enable DMA Channel-0 RIE, RBUE and AIE bits
      [/cover] */
      EthCntrlAdd->DMA_CH[0].INTERRUPT_ENABLE.B.RIE = \
                                            (uint8)ETH_17_GETHMAC_ENABLE;
      EthCntrlAdd->DMA_CH[0].INTERRUPT_ENABLE.B.RBUE = \
                                            (uint8)ETH_17_GETHMAC_ENABLE;
      EthCntrlAdd->DMA_CH[0].INTERRUPT_ENABLE.B.AIE = \
                                            (uint8)ETH_17_GETHMAC_ENABLE;
    }
  }
}
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={1115C5E7-FC19-4720-BDC6-30CCDC21A98E}]  **
**                                                                            **
** Syntax           : static Std_ReturnType Eth_17_lResetGethCore(const       **
**                  Eth_17_GEthMac_CoreCntrlConfigType* const EthCntrlCfgPtr) **
**                                                                            **
** Description      : Reset the GETH Core                                     **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : NA                                                      **
**                                                                            **
** Parameters (in)  : EthCntrlCfgPtr- Pointer to ethernet Controller          **
**                    Configuration.                                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK     - Kernel reset successful                      **
**                    E_NOT_OK - Kernel reset failed                          **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Eth_17_lResetGethCore(const
                       Eth_17_GEthMac_CoreCntrlConfigType* const EthCntrlCfgPtr)
{
  Std_ReturnType RetValue = E_NOT_OK;
  uint32 ResetStatus;
  uint32 NumberWaitTicks;
  uint32 BaseSTMTick;
  uint32 CurrSTMTick;
  uint32 DelayTickResolution;
  boolean IsTimeExpired;
  Ifx_GETH *EthCntrlAdd;

  /* Get base address of the indexed controller */
  EthCntrlAdd = Eth_GEthMacCntrl[EthCntrlCfgPtr->EthCntrlIdx];

  /* Issue command to reset the GETH Core(GETH Kernel). */
  /* Reset End Init Protection to access registers */
  ETH_17_GETHMAC_LIB_RUNTIME_WRITEPERIPENDINITPROTREG \
                       (&(EthCntrlAdd->KRST0),(uint32)ETH_17_GETHMAC_ONE);

  ETH_17_GETHMAC_LIB_RUNTIME_WRITEPERIPENDINITPROTREG \
                       (&(EthCntrlAdd->KRST1),(uint32)ETH_17_GETHMAC_ONE);

  /* Check whether a GETH reset was executed or not, wait only until timeout.*/
  /* Get STM timer current resolution and calculate number of ticks to wait*/
  DelayTickResolution = Mcal_DelayTickResolution();
  NumberWaitTicks  = (ETH_17_GETHMAC_MAXTIMEOUT_COUNT / DelayTickResolution);
  /* Do not allow ticks to wait to be zero, if STM timer resolution is lower*/
  /* [cover parentID={9B2D92B1-02D1-47f4-BCD6-4D3A8D57B832}]
  [/cover] */
  if(NumberWaitTicks == ETH_17_GETHMAC_ZERO)
  {
    /* [cover parentID={9B2D92B1-02D1-47f4-BCD6-4D3A8D57B832}]
    Increment the ticks
    [/cover] */
    NumberWaitTicks++;
  }
  /*Get current STM tick*/
  CurrSTMTick         = Mcal_DelayGetTick();
  BaseSTMTick         = CurrSTMTick;
  IsTimeExpired       = FALSE;
  /* [cover parentID={9B2D92B1-02D1-47f4-BCD6-4D3A8D57B832}]
  wait until kernal reset is done or time ahs elapsed
  [/cover] */
  do
  {
    ResetStatus = (uint32)EthCntrlAdd->KRST0.B.RSTSTAT;
    /* Check wait time is reached at maxmum timeout configured*/
    if((((uint32)((CurrSTMTick - BaseSTMTick) & \
          ETH_17_GETHMAC_STM_TICK_OVERFLOW)) >= \
          NumberWaitTicks) && (ResetStatus == ETH_17_GETHMAC_ZERO))
    {
      /*Timeout Happend and reset is not completed yet*/
      IsTimeExpired = TRUE;
    }
    /*Get current STM tick*/
    CurrSTMTick = Mcal_DelayGetTick();
  }while((ResetStatus == ETH_17_GETHMAC_ZERO) && (IsTimeExpired == FALSE));
  /* [cover parentID={F0BCA2C9-89CA-4b2f-B4C5-3512A50CB9A0}]
  if time has not elapsed
  [/cover] */
  /* [cover parentID={68E138CA-7CAF-4e18-900B-01339294DE1E}]
  [/cover] */
  if(Eth_17_lDemtimeout(IsTimeExpired,EthCntrlCfgPtr->EthDemAccess) == FALSE)
  {
    /* [cover parentID={E06A5C52-321B-430a-8B07-7006A2B9C33E}]
    Check whether RGMII mode is configured
    [/cover] */
    if(((EthCntrlCfgPtr->EthCntrlProperties>>ETH_17_GETHMAC_PHYINT_POS)
                              & ETH_17_GETHMAC_SEVEN) == ETH_17_GETHMAC_ONE)
    {
      /* Calculate number of ticks to wait for RGMII mode */
      NumberWaitTicks = (ETH_17_GETHMAC_KRNLRST_RGMII_WAITCNT/
                                                        DelayTickResolution);
    }
    else
    {
      /* Calculate number of ticks to wait for MII/ RMII mode */
      NumberWaitTicks = (ETH_17_GETHMAC_KRNLRST_MII_WAITCNT/
                                                        DelayTickResolution);
    }

    /* Do not allow ticks to wait to be zero, if STM timer resolution is lower*/
    /* [cover parentID={9B2D92B1-02D1-47f4-BCD6-4D3A8D57B832}]
    [/cover] */
    if(NumberWaitTicks == ETH_17_GETHMAC_ZERO)
    {
      /* [cover parentID={9B2D92B1-02D1-47f4-BCD6-4D3A8D57B832}]
      Increment the ticks
      [/cover] */
      NumberWaitTicks++;
    }
    /*Get current STM tick*/
    CurrSTMTick         = Mcal_DelayGetTick();
    BaseSTMTick         = CurrSTMTick;
    IsTimeExpired       = FALSE;

    /* Wait until necessary time has elapsed */
    do
    {
      /* Check wait time has reached maximum timeout configured */
      if(((uint32)((CurrSTMTick - BaseSTMTick) &
           ETH_17_GETHMAC_STM_TICK_OVERFLOW)) >= NumberWaitTicks)
      {
        /* Necessary time has elapsed */
        IsTimeExpired = TRUE;
      }
      /*Get current STM tick*/
      CurrSTMTick = Mcal_DelayGetTick();
    }while(IsTimeExpired == FALSE);

    /* [cover parentID={4491746B-FA13-4a9f-AA97-0694DD1BFBBC}]
    Clear GETH Reset Status
    [/cover] */
    ETH_17_GETHMAC_LIB_RUNTIME_WRITEPERIPENDINITPROTREG \
                       (&(EthCntrlAdd->KRSTCLR),(uint32)ETH_17_GETHMAC_ONE);
    RetValue = E_OK;
  }
  else
  {
     /* [cover parentID={BFFD82B2-FF56-48bf-9233-65EF5B1B6C3E}]
     Set return value E_NOT_OK
     [/cover] */
     RetValue = E_NOT_OK;
  }
  return (RetValue);
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={7F83C593-8E8A-4fb4-8C1B-E91160C0B6B7}]  **
**                                                                            **
** Syntax           : static void Eth_17_lInitGethController(const            **
**       Eth_17_GEthMac_CoreCntrlConfigType* const EthCntrlCfgPtr)            **
**                                                                            **
** Description      : Apply reset to DMA to select MII  and complete          **
**                    Ethernet controller initialization process              **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non- Reentrant                                          **
**                                                                            **
** Parameters (in)  : EthCntrlCfgPtr- Pointer to ethernet controller          **
**                    configuration.                                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_lInitGethController(const
                      Eth_17_GEthMac_CoreCntrlConfigType* const EthCntrlCfgPtr)
{
  Std_ReturnType RetValue = E_NOT_OK;
  Ifx_GETH *EthCntrlAdd;

  /* Get base address of the indexed controller */
  EthCntrlAdd = Eth_GEthMacCntrl[EthCntrlCfgPtr->EthCntrlIdx];

  /* Flush the transmit Queue */
  EthCntrlAdd->MTL_TXQ0.OPERATION_MODE.B.FTQ = 1U;

  /* Flush the receive Queue */
  EthCntrlAdd->DMA_CH[0].RX_CONTROL.B.RPF = 1U;

  /* Reset interrupt status and mask the interrupts */
  Eth_17_lDisableGethInterrupt(EthCntrlCfgPtr);

  /* [cover parentID={460E537E-ABCA-4ce3-A510-D278CDCF5AD2}]
  Check whether RGMII mode is configured
  [/cover] */
  if (((EthCntrlCfgPtr->EthCntrlProperties>>ETH_17_GETHMAC_PHYINT_POS)
                            & ETH_17_GETHMAC_SEVEN) == ETH_17_GETHMAC_ONE)
  {
    /* [cover parentID={B1532E59-55D2-4dc6-AD71-C12ACB773999}]
    Set the Phy Interface to MII mode and retain the alternate input values
    [/cover] */
    ETH_17_GETHMAC_SFR_RUNTIME_WRITE32(&EthCntrlAdd->GPCTL.U,
                              (uint32)EthCntrlCfgPtr->EthGptclRegVal);

    /* In RGMII mode, initialize the timing skew to zero */
    ETH_17_GETHMAC_SFR_RUNTIME_WRITE32(&(EthCntrlAdd->SKEWCTL.U),
                                                   ETH_17_GETHMAC_ZERO);
  }

  /* [cover parentID={9BDAC7C1-9770-496a-A975-699FC34B9C25}]
    Apply GETH MAC Kernel Reset
    [/cover] */
  RetValue = Eth_17_lResetGethCore(EthCntrlCfgPtr);
  /* Check if Kernal Reset is successful.*/
  /* If Kernal Reset is failed due to hardware access failure, RetValue
    will be E_NOT_OK and Hardware Access failure Production error will be
    reported from called function*/
  /* [cover parentID={9A71F8DF-C505-41fa-9C99-C899A19D8268}]
    Kernel Reset Successful
    [/cover] */
  if (RetValue == E_OK)
  {
    /* [cover parentID={A1AB6ACE-73A9-4ed1-888E-120C231A6CE2}]
      Configure selected PHY interface in register and select Alternative
      inputs
      [/cover] */
    /*Info: In Init function, only MDIO/MII pins preparation is done.
      Rest of Init part will be done in SetController mode, when the API is
      called for first time */
    Eth_17_lPhyIfModeSkewCfg(EthCntrlCfgPtr);

    /* Apply software reset to DMA.*/
    /* PHY interface is selected by DMA_reset.*/
    /*Info: It is assumed, that PHY is already configured by Ethernet
    Transceiver  driver and input clock from PHY is available*/
    RetValue = Eth_17_lResetDma(EthCntrlCfgPtr->EthCntrlIdx);

    /* [cover parentID={D4523FF1-DF5B-46f7-9AD3-BDF51876194F}]
    DMA Reset is successful
    [/cover] */
    /* Check DMA Reset is successful.*/
    /* If DMA Reset is not successful, it means PHY interface could not be
    configured.Function will return E_NOT_OK and also Hardware Access failure
    Production error will be reported from called function */
    if(RetValue == E_OK)
    {
      /* [cover parentID={11C5C7D3-A6C3-4e7f-A71C-2430D766EF8A}]
      Start Ethernet controller Initialization, stage-2
      [/cover] */
      /* Initialize the GETH Core- MAC,MTL and DMA initialization*/
      Eth_17_lGethCoreInit(EthCntrlCfgPtr);
    }
    /* [cover parentID={D05C10C8-DA76-4864-9968-1D35748406EA}]
    If DMA Reset is failed due to any hardware access failure,
    Hardware Access failure Production error will be reported from called
    function. Hence no action needed here.
    [/cover] */
  }
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={5A61C248-C86E-4d8c-8751-B8CF389B3269}]  **
**                                                                            **
** Syntax           : static void Eth_17_lGethCoreInit                        **
**                           (const Eth_17_GEthMac_CoreCntrlConfigType*       **
**                                                     const EthCntrlCfgPtr)  **
**                                                                            **
** Description      : Configure MAC,MTL and DMA as per config root            **
**                    parameters                                              **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non- Reentrant                                          **
**                                                                            **
** Parameters (in)  : EthCntrlCfgPtr- Pointer to ethernet Controller          **
**                    Configuration.                                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_lGethCoreInit(const Eth_17_GEthMac_CoreCntrlConfigType*
                                                          const EthCntrlCfgPtr)
{
#if (ETH_17_GETHMAC_GLOBALTIMESUPPORT == STD_ON)
  Std_ReturnType RetValue = E_NOT_OK;
#endif
  Eth_17_GEthMac_CntrlStatusType *EthLocalCoreStatusPtr;

  /* Get controller status */
  EthLocalCoreStatusPtr = Eth_17_lGetCtrlStatusPtr(EthCntrlCfgPtr->EthCntrlIdx);

  /* Stop MAC transmission and reception */
  Eth_GEthMacCntrl[EthCntrlCfgPtr->EthCntrlIdx]->MAC_CONFIGURATION.U =
    (uint32)(Eth_GEthMacCntrl[EthCntrlCfgPtr->EthCntrlIdx]->MAC_CONFIGURATION.U
                        & (uint32)ETH_17_GETHMAC_MAC_TXRX_DISABLEMASK);

  /* Do DMA (Sub block of GETH IP)configuration.*/
  Eth_17_lDmaCoreInit(EthCntrlCfgPtr);

  /* Do MTL core (Sub block of GETH IP)configuration.*/
  Eth_17_lMtlCoreInit(EthCntrlCfgPtr->EthCntrlIdx);

  /* Do MAC core(Sub block of GETH IP) configuration.*/
  Eth_17_lMacCoreInit(EthCntrlCfgPtr);

#if (ETH_17_GETHMAC_GLOBALTIMESUPPORT == STD_ON)
  /* Initialize timer for MAC Timestamp feature for clock synchronization
  as per IEEE 1588-2008 PTP.*/
  /* If Timer Init is not successful,the function will return E_NOT_OK and
  also Hardware Access failure Production error will be reported from
  called function */
  RetValue = Eth_17_lTimerInit((uint32)ETH_17_GETHMAC_FGETH_IN_HZ,
                                                               EthCntrlCfgPtr);
  /* [cover parentID={EB24063B-EF55-471d-B427-734760F242E0}]
  RetVal = E_OK (If time support enabled, then RetVal is from
  TimerInit function.Else in default RetVal is E_OK)
  [/cover] */
  if(RetValue == E_OK)
#endif
  {
    /* [cover parentID={0AE6D96E-28A6-4935-A245-80150FB4A595}]
    Set Controller init State as INITIALIZED
    [/cover] */
    EthLocalCoreStatusPtr->EthRunTimeOpertnData.CntrlConfigStatus =
                                            ETH_17_GETHMAC_CNTRL_INITIALIZED;

    /* Ethernet controller is successfully initialized Report Pass to
    Mcal_Wrapper*/
    /* [cover parentID={4FC52A3F-5428-436d-8D5F-9C7055CA40D9}]
    Report Pre Pass to Mcal_Wrapper for all Production Errors
    [/cover] */
    /* Report all Production error as prepass (except ETH_E_ACCESS) */
    Eth_17_lDemReportAllErrorPass(EthCntrlCfgPtr);
  }
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={BFF7901C-A812-4899-B6D8-00CCAF56D420}]  **
**                                                                            **
** Syntax           : static void Eth_17_lInitGlobalVar                       **
**                   (const Eth_17_GEthMac_CoreCntrlConfigType* const         **
**  EthCntrlCfgPtr,Eth_17_GEthMac_CntrlStatusType* const EthCoreStatusPtr)    **
**                                                                            **
** Description      : Initialize global variables                             **
**                                                                            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non- Reentrant                                          **
**                                                                            **
** Parameters (in)  : EthCntrlCfgPtr- Pointer to ethernet controller          **
**                    configuration.                                          **
**                   EthCoreStatusPtr-: Pointer to ethernet controller status **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_lInitGlobalVar(const Eth_17_GEthMac_CoreCntrlConfigType*
   const EthCntrlCfgPtr,Eth_17_GEthMac_CntrlStatusType* const EthCoreStatusPtr)
{
  uint8 LoopCount;
  uint8 EthOpMode;

  EthOpMode = (uint8)((EthCntrlCfgPtr->EthCntrlProperties) >> \
                               ETH_17_GETHMAC_OPMODE_POS) & ETH_17_GETHMAC_ONE;
  /*Initialize Statistics Counter structure*/
  EthCoreStatusPtr->EthStatisticsCounters.CRCErrorFrameCounter.Count =\
                                                           ETH_17_GETHMAC_ZERO;
  EthCoreStatusPtr->EthStatisticsCounters.UnderSizeFrameCounter.Count      =\
                                                           ETH_17_GETHMAC_ZERO;
  EthCoreStatusPtr->EthStatisticsCounters.OverSizeFrameCounter.Count       =\
                                                           ETH_17_GETHMAC_ZERO;
  EthCoreStatusPtr->EthStatisticsCounters.AlignmentErrorFrameCounter.Count =\
                                                           ETH_17_GETHMAC_ZERO;

  EthCoreStatusPtr->EthStatisticsCounters.CRCErrorFrameCounter.\
                                       DemReportedCount  = ETH_17_GETHMAC_ZERO;
  EthCoreStatusPtr->EthStatisticsCounters.UnderSizeFrameCounter.\
                                        DemReportedCount = ETH_17_GETHMAC_ZERO;
  EthCoreStatusPtr->EthStatisticsCounters.OverSizeFrameCounter.\
                                       DemReportedCount  = ETH_17_GETHMAC_ZERO;
  EthCoreStatusPtr->EthStatisticsCounters.AlignmentErrorFrameCounter.\
                                        DemReportedCount = ETH_17_GETHMAC_ZERO;

  if(EthOpMode == ETH_17_GETHMAC_HALF_DUPLEX)
  {
    EthCoreStatusPtr->EthStatisticsCounters.SingleCollisionCounter.Count =\
                                                           ETH_17_GETHMAC_ZERO;
    EthCoreStatusPtr->EthStatisticsCounters.MultipleCollisionCounter.Count =\
                                                           ETH_17_GETHMAC_ZERO;
    EthCoreStatusPtr->EthStatisticsCounters.LateCollisionCounter.Count =\
                                                           ETH_17_GETHMAC_ZERO;
    EthCoreStatusPtr->EthStatisticsCounters.SingleCollisionCounter.\
                                      DemReportedCount   = ETH_17_GETHMAC_ZERO;
    EthCoreStatusPtr->EthStatisticsCounters.MultipleCollisionCounter.\
                                        DemReportedCount = ETH_17_GETHMAC_ZERO;
    EthCoreStatusPtr->EthStatisticsCounters.LateCollisionCounter.\
                                      DemReportedCount   = ETH_17_GETHMAC_ZERO;
  }

  EthCoreStatusPtr->EthRunTimeOpertnData.CurrRxDmaDescIdx =\
                                                           ETH_17_GETHMAC_ZERO;

  /*Irrespective of Timestamp support,Initialize Rx Bufer Index for Time
  stamp.availability as Not Available*/
  EthCoreStatusPtr->EthRunTimeOpertnData.RxDmaDesIdxForIngTimStamp = \
                                                   ETH_17_GETHMAC_TIMESTAMP_NA;

  /* Initialize all Tx Index to 0 */
  EthCoreStatusPtr->EthRunTimeOpertnData.CurrTxIdx = ETH_17_GETHMAC_ZERO;
  EthCoreStatusPtr->EthRunTimeOpertnData.ConfirmTxBufIdx = ETH_17_GETHMAC_ZERO;

    /* Initialize stored MAC address as 0 */
  for(LoopCount = ETH_17_GETHMAC_ZERO; \
      LoopCount < ETH_17_GETHMAC_MACADDRESS_LEN; LoopCount++)
  {
    EthCoreStatusPtr->EthRunTimeOpertnData.EthUnicastMacAddress[LoopCount] =\
                                                          ETH_17_GETHMAC_ZERO;
  }

  /* Set Controller Mode as DOWN in default. */
  EthCoreStatusPtr->EthRunTimeOpertnData.EthControllerMode = ETH_MODE_DOWN;

  /* Set Previous Controller Mode as DOWN in default. */
  EthCoreStatusPtr->EthRunTimeOpertnData.PrevEthControllerMode = ETH_MODE_DOWN;

  /* Set the Mii interface configuration status as Not configured. */
  EthCoreStatusPtr->EthRunTimeOpertnData.CntrlConfigStatus =\
                                          ETH_17_GETHMAC_CNTRL_NOT_INITIALIZED;

  /* Set FilterOpenStatus as FALSE*/
  EthCoreStatusPtr->EthRunTimeOpertnData.AddressFilterOpenStat = FALSE;

  /* Initialize Frequency compensation value as 0 */
  #if(ETH_17_GETHMAC_GLOBALTIMESUPPORT == STD_ON)
  EthCoreStatusPtr->EthRunTimeOpertnData.EthPrevFreqCompensationValue0 = \
                                              (float64)ETH_17_GETHMAC_ZERO;
  #endif

}
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={83475B80-2EC8-457f-9A22-03D92E8D56AE}]  **
**                                                                            **
** Syntax           : LOCAL_INLINE void Eth_17_lPhyIfModeSkewCfg(const        **
**                    Eth_17_GEthMac_CoreCntrlConfigType*                     **
**                    const EthCntrlCfgPtr)                                   **
**                                                                            **
** Description      : This function configures GPCTL register to choose the   **
**                    selected PHY interface and the alternate inputs.        **
**                    Also configures the timing skew in RGMII mode.          **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non- Reentrant                                          **
**                                                                            **
** Parameters (in)  : EthCntrlCfgPtr- Pointer to ethernet controller          **
**                    configuration.                                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Eth_17_lPhyIfModeSkewCfg(const
                      Eth_17_GEthMac_CoreCntrlConfigType* const EthCntrlCfgPtr)
{
  Ifx_GETH *EthCntrlAdd;
  uint32 GptclValue;

  /*Before starting this function, all Port/Pin configuration should completed*/
  /* Info: Port Configuration is done by Port driver. */
  EthCntrlAdd = Eth_GEthMacCntrl[EthCntrlCfgPtr->EthCntrlIdx];

  /* [cover parentID={9513DBBE-B82B-4aef-B7F5-B73DE0CF282C}]
  Configure Physical interface MII, RMII or RGMII and alternate inputs
  [/cover] */
  GptclValue = (((((uint32)EthCntrlCfgPtr->
  EthCntrlProperties >> (uint32)ETH_17_GETHMAC_PHYINT_POS) &
  (uint32)ETH_17_GETHMAC_SEVEN) << (uint32)ETH_17_GETHMAC_GPTCL_PHY_POS) |
                                      (uint32) EthCntrlCfgPtr->EthGptclRegVal);

  ETH_17_GETHMAC_SFR_RUNTIME_WRITE32(&EthCntrlAdd->GPCTL.U, GptclValue);

  /* In RGMII mode, configure TX/RX Clock delay for skew timing */
  /* [cover parentID={F14C4B3E-85C3-4068-88AB-FB8FFD7D336D}]
  Check whether RGMII mode is configured
  [/cover] */
  if(((EthCntrlCfgPtr->EthCntrlProperties>>ETH_17_GETHMAC_PHYINT_POS)&
                                 ETH_17_GETHMAC_SEVEN) == ETH_17_GETHMAC_ONE)
  {
    /* [cover parentID={5D139FAE-13DC-4876-A0B2-BA404AF69D06}]
    Configure skew control register to the specified Tx and Rx skew timing
    [/cover] */
    ETH_17_GETHMAC_SFR_RUNTIME_WRITE32(&(EthCntrlAdd->SKEWCTL.U),
    (((uint32)((uint32)(EthCntrlCfgPtr->EthSkewDelay &
    ETH_17_GETHMAC_TXSKEW_MASK) << (uint32) IFX_GETH_SKEWCTL_TXCFG_OFF)) |
    ((uint32)((uint32)((EthCntrlCfgPtr->EthSkewDelay &
                      ETH_17_GETHMAC_RXSKEW_MASK) <<ETH_17_GETHMAC_FOUR)))));
  }
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={A8570073-6FF2-457c-ACBA-15F1B37956E9}]  **
**                                                                            **
** Syntax           : static Std_ReturnType Eth_17_lResetDma                  **
**                      (const uint8 CtrlIdx)                                 **
**                                                                            **
* Description      : Apply software reset to DMA                              **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : NA                                                      **
**                                                                            **
** Parameters (in)  : CtrlIdx       -  Index of Eth Controller within the     **
**                                     context of the Ethernet driver.        **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK     - DMA Reset finished successfully              **
**                    E_NOT_OK - DMA Reset is not successful                  **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Eth_17_lResetDma(const uint8 CtrlIdx)
{
  Std_ReturnType RetValue;
  uint32 NoOfSpbCyclesToWait;
  uint32 DmaResetFinished;
  uint32 DmaResetWaitTicks;
  uint32 BaseSTMTick;
  uint32 CurrSTMTick;
  uint32 DelayTickResolution;
  boolean IsTimeExpired;
  Ifx_GETH *EthCntrlAdd;
  const Eth_17_GEthMac_CoreCntrlConfigType *EthLocalCntrlCfgPtr;

  EthCntrlAdd = Eth_GEthMacCntrl[CtrlIdx];

  EthLocalCntrlCfgPtr = Eth_17_lGetCtrlConfigPtr(CtrlIdx);

  /*In default set RetVal is E_NOT_OK */
  /* [cover parentID={84450E92-0E78-4086-92FB-B16E9225C5F3}]
  [/cover] */
  RetValue = E_NOT_OK;

  /* hardware Errata/Application Hint - GETH_AI.H001( Preparation
  for Software Reset) is implemented below.
  That is, after applying DMA reset, wait for atleast 4 fSPB cycles,
  then check if DMA_MODE.SWR = 0B*/
  /* Get STM timer current resolution*/
  DelayTickResolution = Mcal_DelayTickResolution();

  /* Calculate SPB cycles in nanosecond to wait after DMA reset. */
  NoOfSpbCyclesToWait = (uint32)(ETH_17_GETHMAC_DMA_RESET_WAITCYCLE *
                                    ETH_17_GETHMAC_FSPB_PERIOD_IN_NANOSEC);

  /* Calculate number of ticks to wait */
  DmaResetWaitTicks  = (NoOfSpbCyclesToWait / DelayTickResolution);

  /* Do not allow ticks to wait to be zero, if STM timer resolution is lower*/
  /* [cover parentID={5104CDB1-A94F-4a38-BDBB-743CF4C204E4}]
  If Stm resolution is zero
  [/cover] */
  if(DmaResetWaitTicks == ETH_17_GETHMAC_ZERO)
  {
    /* [cover parentID={F01378E4-20D3-4e75-9045-0F11945D969B}]
    Increment the ticks.
    [/cover] */
    DmaResetWaitTicks++;
  }

  /* Apply Software Reset to DMA. */
  /* [cover parentID={71B450B4-C079-4632-8FCF-0AAC03A8ACDE}][/cover] */
  EthCntrlAdd->DMA_MODE.B.SWR = (uint8)ETH_17_GETHMAC_DMA_SWR;

  /*Get current STM tick*/
  CurrSTMTick         = Mcal_DelayGetTick();
  BaseSTMTick         = CurrSTMTick;
  IsTimeExpired       = FALSE;

  /* Wait for 4 fSPB cycles before reading back SWR bit. */
  /* [cover parentID={8454EE84-CBBD-4db8-A2E2-0F3C23E3BE40}]
  [/cover] */
  do
  {
    /* Check wait time is reached at DMA reset wait time*/
    if(((uint32)((CurrSTMTick - BaseSTMTick) & \
         ETH_17_GETHMAC_STM_TICK_OVERFLOW)) >= DmaResetWaitTicks)
    {
      /*4 fSPB cycles is elapsed*/
      IsTimeExpired = TRUE;
    }
    /*Get current STM tick*/
    CurrSTMTick = Mcal_DelayGetTick();
  }while(IsTimeExpired == FALSE);

  /* Calculate number of ticks to wait,until DMA reset is finished*/
  DmaResetWaitTicks  = (ETH_17_GETHMAC_MAXTIMEOUT_COUNT / DelayTickResolution);
  /* Do not allow ticks to wait to be zero, if STM timer resolution is lower*/
  /* [cover parentID={5104CDB1-A94F-4a38-BDBB-743CF4C204E4}]
  [/cover] */
  if(DmaResetWaitTicks == ETH_17_GETHMAC_ZERO)
  {
    /* [cover parentID={F01378E4-20D3-4e75-9045-0F11945D969B}]
    Increment the ticks
    [/cover] */
    DmaResetWaitTicks++;
  }
  /*Get current STM tick*/
  CurrSTMTick         = Mcal_DelayGetTick();
  BaseSTMTick         = CurrSTMTick;
  IsTimeExpired       = FALSE;

  /*Checking in a time out loop if DMA reset if completed. */
  /* [cover parentID={FF6C1322-D2AE-4cf7-8E1A-F8F8BC3520A3}]
  [/cover] */
  do
  {
    /* If DMA reset is finished, zero should be read in the SWR bit. */
    DmaResetFinished = (uint32)(EthCntrlAdd->DMA_MODE.B.SWR);

    /* Check wait time is reached at maximum timeout configured*/
    if((((uint32)((CurrSTMTick - BaseSTMTick) & \
                                        ETH_17_GETHMAC_STM_TICK_OVERFLOW)) >= \
     DmaResetWaitTicks) && (DmaResetFinished == (uint32)ETH_17_GETHMAC_DMA_SWR))
    {
      /*Timeout Happened and DMA reset is not finished yet*/
      IsTimeExpired = TRUE;
    }
    /*Get current STM tick*/
    CurrSTMTick = Mcal_DelayGetTick();
  }while((DmaResetFinished == (uint32)ETH_17_GETHMAC_DMA_SWR) && \
                                   (IsTimeExpired == FALSE));

  /* [cover parentID={2B84E831-F3F3-4291-88D0-EE6007020D66}]
  Timeout elapsed
  [/cover] */
    /* [cover parentID={4766CC4B-00AA-4705-9777-4AF445D655CA}]
  check if time has elapsed
  [/cover] */
  /*Report Production error if timeout happened. */
  if(Eth_17_lDemtimeout(IsTimeExpired,EthLocalCntrlCfgPtr->EthDemAccess)
                                                                == FALSE)
  {
    /* [cover parentID={3EFA9174-D8CA-4361-93A9-557391C3A684}]
    set return value E_OK
    [/cover] */
    RetValue = E_OK;
  }

  return (RetValue);
}


/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={F7B7B02C-1DAE-42f7-BA7E-FA30418092FC}]  **
**                                                                            **
** Syntax           : static void Eth_17_lMacCoreInit                         **
**                   (const Eth_17_GEthMac_ConfigType* const EthCntrlCfgPtr)  **
**                                                                            **
** Description      : Configure MAC as per config root                        **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non- Reentrant                                          **
**                                                                            **
** Parameters (in)  : EthCntrlCfgPtr- Pointer to ethernet Controller          **
**                    Configuration.                                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_lMacCoreInit(const Eth_17_GEthMac_CoreCntrlConfigType*
                                                          const EthCntrlCfgPtr)
{
  Ifx_GETH *EthCntrlAdd;
  Eth_17_GEthMac_CntrlStatusType *EthLocalCoreStatusPtr;
  uint32 MacConfigVal;
  uint8 LoopCount;
  uint8 EthOpMode;

  /* Get controller status */
  EthLocalCoreStatusPtr = Eth_17_lGetCtrlStatusPtr(EthCntrlCfgPtr->EthCntrlIdx);

  EthCntrlAdd = Eth_GEthMacCntrl[EthCntrlCfgPtr->EthCntrlIdx];

  /* Ethernet Speed Selection based on Ethspeed(10/100/1000 Mbps)
     configuration*/
  MacConfigVal = ((uint32)EthCntrlCfgPtr->EthCntrlProperties &
                   IFX_GETH_MAC_CONFIGURATION_PS_MSK) <<
                        IFX_GETH_MAC_CONFIGURATION_PS_OFF;

  MacConfigVal |= (((uint32)EthCntrlCfgPtr->EthCntrlProperties >>
                  ETH_17_GETHMAC_FES_POS) & IFX_GETH_MAC_CONFIGURATION_FES_MSK)
                  << IFX_GETH_MAC_CONFIGURATION_FES_OFF;

  EthOpMode = (uint8)((EthCntrlCfgPtr->EthCntrlProperties) >>
                    ETH_17_GETHMAC_OPMODE_POS) & ETH_17_GETHMAC_OPMODE_MSK;

  /* Initialize MAC config and Tx/Rx flow control registers. */
  /* [cover parentID={37E8E920-78C4-4591-8898-92453D7A3269}]
  If FULL DUPLEX opmode
  [/cover] */
  if(EthOpMode == ETH_17_GETHMAC_FULL_DUPLEX)
  {
    /* Full duplex default configuration */
    /* [cover parentID={A358DD8B-124E-4316-9B3A-9BD6CA2EC972}]
    [/cover] */
    MacConfigVal |= (uint32)(ETH_17_GETHMAC_MAC_INIT_CONF_FDX);
  }
  else
  {
    /* Half duplex default configuration  */
    /* [cover parentID={FBEE86AB-FCDD-4188-B493-4572F77199CB}]
    If HALF DUPLEX mode, update the MAC Configuration
    [/cover] */
    MacConfigVal |= (uint32)(ETH_17_GETHMAC_MAC_INIT_CONF_HDX);
  }

  /* Configure Mac Packet filter register. */
  EthCntrlAdd->MAC_PACKET_FILTER.U = ETH_17_GETHMAC_MAC_PACKT_FILT_INIT_CONF;

  /* Clear MAC Address filter Registers 0 to 31 */
  Eth_17_lClearAllAddressFilters(EthCntrlCfgPtr->EthCntrlIdx);

  /* Set the configured MAC address in MAC Address register 0 */
  Eth_17_lSetPhysAddr(EthCntrlCfgPtr->EthMacAddress,
                      EthCntrlCfgPtr->EthCntrlIdx);

  /* Copy configured MAC address, which will be used to restore controllers
     unique unicast MAC address while ending promiscuous mode, using API
     Eth_UpdatePhysAddrFilter().*/
  /* [cover parentID={54439DF3-D631-42d7-8CA2-40D95C07CDBB}]
  [/cover] */
  for(LoopCount = 0U; LoopCount < ETH_17_GETHMAC_MACADDRESS_LEN; LoopCount++)
  {
    EthLocalCoreStatusPtr->EthRunTimeOpertnData.EthUnicastMacAddress
                        [LoopCount] = EthCntrlCfgPtr->EthMacAddress[LoopCount];
  }

  /* [cover parentID={42C18E06-A317-41fc-85DE-30AE6E8F0F44}]
  Checksum Offload  Enabled
  [/cover] */
#if((ETH_17_GETHMAC_IPV4_CHECKSUMOFFLOAD_ENABLE == STD_ON ) ||\
    (ETH_17_GETHMAC_TCP_CHECKSUMOFFLOAD_ENABLE  == STD_ON ) ||\
    (ETH_17_GETHMAC_UDP_CHECKSUMOFFLOAD_ENABLE  == STD_ON ) ||\
    (ETH_17_GETHMAC_ICMP_CHECKSUMOFFLOAD_ENABLE == STD_ON ))

  /* [cover parentID={91A3D4EC-6DB9-462a-A57B-DCF65D6FB978}]
  Enable Checksum Offload for IPv4 header checksum and IPv4 or IPv6 TCP, UDP,
  or ICMP payload checksum
  [/cover] */
  /*Enable Checksum Offload for IPv4 header checksum and
  IPv4 or IPv6 TCP, UDP, or ICMP payload checksum.*/
  MacConfigVal |= ETH_17_GETHMAC_MAC_CHKSM_OFFLD_ENBL;
#endif

  EthCntrlAdd->MAC_CONFIGURATION.U = MacConfigVal;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={A6D57E7B-2CB3-41a2-8B9B-38423F1F32E7}]  **
**                                                                            **
** Syntax           : static void Eth_17_lMtlCoreInit(const uint8 CtrlIdx)    **
**                                                                            **
** Description      : Configure MTL core (MAC Transaction Layer)              **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non- Reentrant                                          **
**                                                                            **
** Parameters (in)  : CtrlIdx- Controller Index                               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_lMtlCoreInit(const uint8 CtrlIdx)
{
  Ifx_GETH *EthCntrlAdd;
  EthCntrlAdd = Eth_GEthMacCntrl[CtrlIdx];

  /* Configure MTL Operation mode( Common for Tx and Rx).*/
  EthCntrlAdd->MTL_OPERATION_MODE.U = ETH_17_GETHMAC_MTL_OPERTN_MODE_INIT;

  /* Configure MTL Operation mode for TX Queue-0.*/
  EthCntrlAdd->MTL_TXQ0.OPERATION_MODE.U = \
                                      ETH_17_GETHMAC_MTL_TXQ0_OPERTN_MODE_INIT;

  /* Configure MTL Operation mode for RX Queue-0.*/
  EthCntrlAdd->MTL_RXQ0.OPERATION_MODE.U = \
                                     ETH_17_GETHMAC_MTL_RX_Q0_OPERTN_MODE_INIT;

  /*Map RX Queue-0 to DMA channel-0 */
  EthCntrlAdd->MTL_RXQ_DMA_MAP0.U = (uint8)ETH_17_GETHMAC_MTL_RX_Q0_T0_DMA_MAP;

  /*Enable RX Queue-0*/
  EthCntrlAdd->MAC_RXQ_CTRL0.U |= (uint8)ETH_17_GETHMAC_MTL_ENABLE_RX_Q;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={45D42C8C-E374-4c26-B030-F8E6841B1F9C}]  **
**                                                                            **
** Syntax           : static void Eth_17_lDmaCoreInit(const                   **
**                   Eth_17_GEthMac_CoreCntrlConfigType* const EthCntrlCfgPtr)**
**                                                                            **
** Description      : Configure DMA channel                                   **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non- Reentrant                                          **
**                                                                            **
** Parameters (in)  : EthCntrlCfgPtr- Pointer to ethernet controller          **
**                    configuration.                                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_lDmaCoreInit(const Eth_17_GEthMac_CoreCntrlConfigType*
                                                          const EthCntrlCfgPtr)
{
  Ifx_GETH *EthCntrlAdd;

  /* Get controller status */
  EthCntrlAdd = Eth_GEthMacCntrl[EthCntrlCfgPtr->EthCntrlIdx];

  /* Configure DMA Bus mode register. */
  EthCntrlAdd->DMA_MODE.U = ETH_17_GETHMAC_DMA_BUS_MODE_INIT_CONF;

  /* Configure DMA system bus mode register. */
  EthCntrlAdd->DMA_SYSBUS_MODE.U = ETH_17_GETHMAC_DMA_SYSBUS_MODE_INIT_CONF;

  /* Configure Tx PBL (Transmit burst length) */
  EthCntrlAdd->DMA_CH[0].TX_CONTROL.U = ETH_17_GETHMAC_DMA_CH_TXCTRL_CONF;

  /* Configure Rx PBL (Receive burst length).*/
  EthCntrlAdd->DMA_CH[0].RX_CONTROL.B.RXPBL =
                                  (uint8)ETH_17_GETHMAC_DMA_CH0_RXPBL;

  /* Configure Tx and Rx Transfer burst and beat length. */
  EthCntrlAdd->DMA_CH[0].CONTROL.B.PBLX8 =
                                (uint8)ETH_17_GETHMAC_DMA_8X_BURST_LENGTH_MODE;

  /*Configure Tx Descriptors. */
  Eth_17_lDmaTxDescriptorInit(EthCntrlCfgPtr);

  /*Configure Rx Descriptors. */
  Eth_17_lDmaRxDescriptorInit(EthCntrlCfgPtr);

  /* Enable DMA Channel-0 Tx and Rx Interrupt */
  Eth_17_lEnableGethInterrupt(EthCntrlCfgPtr);
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={DDB3E8F3-695F-45e4-BBBA-9BA594EDA598}]  **
**                                                                            **
** Syntax           : static void Eth_17_lDmaTxDescriptorInit(const           **
**                  Eth_17_GEthMac_CoreCntrlConfigType* const EthCntrlCfgPtr) **
** Description      : Configure DMA Transmit Descriptors list                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non- Reentrant                                          **
**                                                                            **
** Parameters (in)  : EthCntrlCfgPtr- Pointer to ethernet Controller          **
**                    Configuration.                                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_lDmaTxDescriptorInit(const
                      Eth_17_GEthMac_CoreCntrlConfigType* const EthCntrlCfgPtr)
{
  const volatile uint8 *TxBuffBasePtr;
  uint32 LoopCount;
  uint32 BufferSize;
  uint8  i;
  uint8 TxBufTotal;
  uint8 *BuffPtr;
  uint16 TxBufLengthAligned;
  Eth_17_GEthMac_CntrlStatusType *EthLocalCoreStatusPtr;
  Eth_17_GEthMac_TxBuffTableType *EthLocalTxBuffTablePtr;
  Eth_17_GEthMac_DmaTxDescType *EthLocalDmaTxDescPtr;
  Ifx_GETH *EthCntrlAdd;

  /* Get controller status */
  EthLocalCoreStatusPtr = Eth_17_lGetCtrlStatusPtr(EthCntrlCfgPtr->EthCntrlIdx);
  /* Get base address of the indexed controller */
  EthCntrlAdd = Eth_GEthMacCntrl[EthCntrlCfgPtr->EthCntrlIdx];

  TxBufLengthAligned = EthCntrlCfgPtr->EthCtrlTxBufLenByteAligned;

  TxBufTotal  = EthCntrlCfgPtr->EthTxBufTotal;

  BufferSize = (uint32)((uint32)EthCntrlCfgPtr->EthCtrlTxBufLenByteAligned *\
                            (uint32)EthCntrlCfgPtr->EthTxBufTotal);

  BuffPtr = &(EthLocalCoreStatusPtr->EthBuffDecPtr->\
                                         EthTxBufferPtr[ETH_17_GETHMAC_ZERO]);

  /*Total Tx Buffer allocated as linear array (TxBufTotal*TxBufLenByte)*/
  /*Initialize the Tx buffer with value zero*/
  /* [cover parentID={D321CE7A-5CA2-4291-8101-E0AF615C8DFC}]
  Initialize all Transmit Buffers to zero
  [/cover] */
  for(LoopCount = ETH_17_GETHMAC_ZERO; LoopCount < BufferSize; LoopCount++)
  {
    BuffPtr[LoopCount] = (uint8)ETH_17_GETHMAC_ZERO;
  }
  /*Get Start Address of Tx Buffer*/
  TxBuffBasePtr = &(EthLocalCoreStatusPtr->EthBuffDecPtr->\
                                         EthTxBufferPtr[ETH_17_GETHMAC_ZERO]);
  EthLocalTxBuffTablePtr = EthLocalCoreStatusPtr->EthBuffDecPtr->\
                                                            EthTxBuffTablePtr;
  EthLocalDmaTxDescPtr = EthLocalCoreStatusPtr->EthBuffDecPtr->\
                                                              EthDmaTxDescPtr;

  /* [cover parentID={6A4B38FB-33C9-46e4-AEA0-3091D52CCB81}]
  Loop till last Tx buffer table and last Tx descriptor index
  [/cover] */
  for(i = ETH_17_GETHMAC_ZERO; i < TxBufTotal; i++)
  {
    /* Clear Buffer Table Parameters */
    EthLocalTxBuffTablePtr[i].BuffStatus = ETH_17_GETHMAC_BUFFER_NOTUSED;
    EthLocalTxBuffTablePtr[i].TxConfirmReq= ETH_17_GETHMAC_ZERO;
    EthLocalTxBuffTablePtr[i].FrameTxInitiated = ETH_17_GETHMAC_ZERO;

    /* Start Initializing Tx Descriptors */
    /* Assign the Tx Buffer pointer to the Descriptor buffer1 pointer */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between integer to a
    pointer type is performed to access the buffer address from DMA
    descriptor. This is the intended design and valid as per DMA hardware
    design. There are no side effects seen by violating this rule.*/
    /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from unsigned long to pointer
    is performed to access the buffer address from DMA descriptor.
    This is the intended design and valid as per DMA hardware design.
    There are no side effects seen by violating this rule.*/
    /* MISRA2012_RULE_10_8_JUSTIFICATION: Impermissible cast of composite
    expression is performed to access the buffer address from DMA
    descriptor. This is the intended design and valid as per DMA hardware
    design. There are no side effects seen by violating this rule.*/
    /* MISRA2012_RULE_18_4_JUSTIFICATION: pointer arithmetic is performed
    using '+' operator to configure the RAM address in DMA descriptors.
    This is the intended design and valid as per DMA hardware
    design. There are no side effects seen by violating this rule.*/
    EthLocalDmaTxDescPtr[i].TDES0 = \
       (uint32)(TxBuffBasePtr + ((uint32)i*(uint32)TxBufLengthAligned));

    /* Descriptor Buffer2 poiter not used */
    EthLocalDmaTxDescPtr[i].TDES1 = (uint32)ETH_17_GETHMAC_ZERO;

    /* Enable Interrupt on transmission completion. Buffer length/Packet length
    in TDES2 and TDES3 will be updated during Tranmit request*/
    EthLocalDmaTxDescPtr[i].TDES2 = (uint32)ETH_17_GETHMAC_DMA_TDES2_INIT;
  }

  /* Configure Tx- DMA-CH0 Descriptor tail pointer with start of DmaTxDesc
  array address. During each transmission request, descriptor tail pointer
  will be advanced*/
   /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion pointer to a
     integer type is performed to assign last buffer address to tail pointer
     register. This is the intended design and valid as per DMA hardware
     design. There are no side effects seen by violating this rule.*/
   /* MISRA2012_RULE_11_6_JUSTIFICATION:  cast from pointer to unsigned long is
     performed to assign last buffer address to tail pointer register. This is
     the intended design and valid as per DMA hardware design. There are no
     side effects seen by violating this rule.*/
  EthCntrlAdd->DMA_CH[0].TXDESC_TAIL_POINTER.U = \
                (uint32)(&EthLocalDmaTxDescPtr[ETH_17_GETHMAC_ZERO]);

  /* Configure TX- DMA-CH0 Descriptor list address with start
     of DmaTxDesc array address.*/
   /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion pointer to a
     integer type is performed to assign last buffer address to list address
     register. This is the intended design and valid as per DMA hardware
     design. There are no side effects seen by violating this rule.*/
   /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from pointer to unsigned long
      is performed to to assign last buffer address to list address
     register. This is the intended design and valid as per DMA hardware
     design. There are no side effects seen by violating this rule.*/
  EthCntrlAdd->DMA_CH[0].TXDESC_LIST_ADDRESS.U = \
                (uint32)(&EthLocalDmaTxDescPtr[ETH_17_GETHMAC_ZERO]);

  /* Configure TX- DMA-CH0 Descriptor ring length with total number
     of Tx descriptor minus 1*/
  EthCntrlAdd->DMA_CH[0].TXDESC_RING_LENGTH.U = \
  (uint32)((uint32)EthCntrlCfgPtr->EthTxBufTotal - (uint32)ETH_17_GETHMAC_ONE);

  /* Initialize all Tx Index to 0 */
  EthLocalCoreStatusPtr->EthRunTimeOpertnData.CurrTxIdx = ETH_17_GETHMAC_ZERO;
  EthLocalCoreStatusPtr->EthRunTimeOpertnData.ConfirmTxBufIdx = \
                                                           ETH_17_GETHMAC_ZERO;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={D9318387-B16A-42ab-BA34-764F3122DE6F}]  **
**                                                                            **
** Syntax           : static void Eth_17_lDmaRxDescriptorInit(const           **
**                  Eth_17_GEthMac_CoreCntrlConfigType* const EthCntrlCfgPtr) **
**                                                                            **
** Description      : Configure DMA Receive Descriptors list                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non- Reentrant                                          **
**                                                                            **
** Parameters (in)  : EthCntrlCfgPtr- Pointer to ethernet Controller          **
**                    Configuration.                                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_lDmaRxDescriptorInit(const
                      Eth_17_GEthMac_CoreCntrlConfigType* const EthCntrlCfgPtr)
{
  uint32 LoopCount;
  uint8 RxBufTotal;
  uint8 *BuffPtr;
  uint32 BufferSize;
  uint8  i;
  uint16 RxBufLengthAligned;
  Eth_17_GEthMac_CntrlStatusType *EthLocalCoreStatusPtr;
  Eth_17_GEthMac_DmaRxDescType *EthLocalDmaRxDescPtr;
  Ifx_GETH *EthCntrlAdd;

  RxBufLengthAligned = EthCntrlCfgPtr->EthCtrlRxBufLenByteAligned;
  RxBufTotal = EthCntrlCfgPtr->EthRxBufTotal;
  /* Get controller status */
  EthLocalCoreStatusPtr = Eth_17_lGetCtrlStatusPtr(EthCntrlCfgPtr->EthCntrlIdx);
  /* Get base address of the indexed controller */
  EthCntrlAdd = Eth_GEthMacCntrl[EthCntrlCfgPtr->EthCntrlIdx];

  EthLocalDmaRxDescPtr = EthLocalCoreStatusPtr->\
                                              EthBuffDecPtr->EthDmaRxDescPtr;

  BufferSize = (uint32)((uint32)EthCntrlCfgPtr->EthCtrlRxBufLenByteAligned * \
                           (uint32)EthCntrlCfgPtr->EthRxBufTotal);
  BuffPtr = &(EthLocalCoreStatusPtr->EthBuffDecPtr->\
                                         EthRxBufferPtr[ETH_17_GETHMAC_ZERO]);
  /*Total Rx Buffer allocated as linear array (RxBufTotal*RxBufLenByte)*/
  /*Initialize the Rx buffer with zeros*/
  /* [cover parentID={30D0F9D0-D209-47fd-AE62-7CE42016094F}]
  [/cover] */
  for(LoopCount = ETH_17_GETHMAC_ZERO; LoopCount< BufferSize; LoopCount++)
  {
    BuffPtr[LoopCount] = (uint8)ETH_17_GETHMAC_ZERO;
  }
  /* [cover parentID={432D6A24-9379-4d63-A3D2-1023AEA7C53F}]
  Loop till last Rx DMA descriptor index
  [/cover] */
  for(i = ETH_17_GETHMAC_ZERO; i < RxBufTotal; i++)
  {
    /* Start Initializing Rx Descriptors */
    /* Assign the Receive Buffer pointer to the Descriptor buffer1 pointer */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between integer to a
    pointer type is performed to access the buffer address from DMA
    descriptor. This is the intended design and valid as per DMA hardware
    design. There are no side effects seen by violating this rule.*/
    /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from unsigned long to pointer
    is performed to access the buffer address from DMA descriptor.
    This is the intended design and valid as per DMA hardware design.
    There are no side effects seen by violating this rule.*/
    /* MISRA2012_RULE_10_8_JUSTIFICATION: Impermissible cast of composite
    expression is performed to access the buffer address from DMA
    descriptor. This is the intended design and valid as per DMA hardware
    design. There are no side effects seen by violating this rule.*/
    /* MISRA2012_RULE_18_4_JUSTIFICATION: pointer arithmetic is performed
    using '+' operator to configure the RAM address in DMA descriptors.
    This is the intended design and valid as per DMA hardware
    design. There are no side effects seen by violating this rule.*/
    EthLocalDmaRxDescPtr[i].RDES0 =\
            (uint32)(EthLocalCoreStatusPtr->EthBuffDecPtr->EthRxBufferPtr + \
              (((uint32)(i)) * ((uint32)RxBufLengthAligned)));

    /* Descriptor Buffer2 poiter not used */
    EthLocalDmaRxDescPtr[i].RDES2 = ETH_17_GETHMAC_ZERO;

    /* Set OWN bit, Enable Interrupt on completion, Set Buffer1 valid */
    EthLocalDmaRxDescPtr[i].RDES3= (uint32)ETH_17_GETHMAC_DMA_RDES3_INIT;
  }

  /* Configure Size of one Rx buffer (which is RxBufLenByteAligned)*/
  EthCntrlAdd->DMA_CH[0].RX_CONTROL.B.RBSZ_13_Y = (uint16)(RxBufLengthAligned \
                                                  >> ETH_17_GETHMAC_RBSZ_13_Y);

  /*Configure RX- DMA-CH0 Descriptor list address with start
    of DmaRxDesc array address.*/
       /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion pointer to a
     integer type is performed to assign last buffer address to list address
     register. This is the intended design and valid as per DMA hardware
     design. There are no side effects seen by violating this rule.*/
     /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from pointer to unsigned long
      to assign last buffer address to list address register. This is the
      intended design and valid as per DMA hardware design. There are no side
      effects seen by violating this rule.*/
  EthCntrlAdd->DMA_CH[0].RXDESC_LIST_ADDRESS.U = \
                      (uint32)(&EthLocalDmaRxDescPtr[ETH_17_GETHMAC_ZERO]);
  /*Configure Rx- DMA-CH0 Descriptor tail pointer with last Rx desciptor
    address plus 1*/
       /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion pointer to a
     integer type is performed to assign last buffer address to tail pointer
     register. This is the intended design and valid as per DMA hardware
     design. There are no side effects seen by violating this rule.*/
    /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from pointer to unsigned long
        to assign last buffer address to list address
     register. This is the intended design and valid as per DMA hardware
     design. There are no side effects seen by violating this rule.*/
  EthCntrlAdd->DMA_CH[0].RXDESC_TAIL_POINTER.U = \
                (uint32)(&EthLocalDmaRxDescPtr[EthCntrlCfgPtr->EthRxBufTotal]);
  /*Configure Rx- DMA-CH0 Descriptor ring length with total number
    of Rx descriptor minus 1*/
  EthCntrlAdd->DMA_CH[0].RXDESC_RING_LENGTH.U = \
  (uint32)((uint32)EthCntrlCfgPtr->EthRxBufTotal - (uint32)ETH_17_GETHMAC_ONE);
  EthLocalCoreStatusPtr->EthRunTimeOpertnData.CurrRxDmaDescIdx = \
                                                           ETH_17_GETHMAC_ZERO;
}
#if (ETH_17_GETHMAC_GLOBALTIMESUPPORT == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={30641203-8DB3-41d0-A679-0E4646C561FF}]  **
**                                                                            **
** Syntax           : static Std_ReturnType Eth_17_lTimerInit                 **
**                                          (const uint32 EthOpetnFreq,       **
**                  Eth_17_GEthMac_CoreCntrlConfigType* const EthCntrlCfgPtr) **
**                                                                            **
** Description      : The function Initialises Timer Registers for            **
**                                 IEEE 1588 Timestamp Support                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non- Reentrant                                          **
**                                                                            **
** Parameters (in)  : EthOpetnFreq - Ethernet Operation Frequency             **
**                    EthCntrlCfgPtr- Pointer to ethernet Controller          **
**                    Configuration.                                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK     - Timer Init finished successfully             **
**                    E_NOT_OK - Timer Init is not successful                 **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Eth_17_lTimerInit(const uint32 EthOpetnFreq,
                 const Eth_17_GEthMac_CoreCntrlConfigType* const EthCntrlCfgPtr)
{
  Std_ReturnType RetValue = E_NOT_OK;
  float32 FreqDivisionRatio;
  uint32 TimerInitWaitTicks;
  uint32 DelayTickResolution;
  boolean IsTimeExpired;
  Ifx_GETH *EthCntrlAdd;
  Eth_17_GEthMac_CntrlStatusType *EthLocalCoreStatusPtr;

  /* Get base address of the indexed controller */
  EthCntrlAdd = Eth_GEthMacCntrl[EthCntrlCfgPtr->EthCntrlIdx];

  /* Get controller status */
  EthLocalCoreStatusPtr = Eth_17_lGetCtrlStatusPtr(EthCntrlCfgPtr->EthCntrlIdx);

  /* Get STM timer current resolution and calculate maximum number of ticks
  to wait before expected hardware behaviour is occurred- That timer init*/
  DelayTickResolution = Mcal_DelayTickResolution();

  TimerInitWaitTicks  = (ETH_17_GETHMAC_MAXTIMEOUT_COUNT / DelayTickResolution);

  /* Do not allow ticks to wait to be zero, if STM timer resolution is lower*/
  /* [cover parentID={4A0AD8AF-8102-426f-BAD3-F829B3BD3DB6}]
  If STM resolution is zero
  [/cover] */
  if(TimerInitWaitTicks == ETH_17_GETHMAC_ZERO)
  {
    /* [cover parentID={ADCBA065-AD05-4e1b-9EB7-EEFA5EA8BA28}]
    Increment the ticks
    [/cover] */
    TimerInitWaitTicks++;
  }

  /* Disable Processing of PTP frames Sent over IPv4-UDP.
     In default, it is enabled.*/
  /* [cover parentID={EA3D3BA3-4AA3-478c-8C42-1CFB551541E3}]
  Enable Timestamp feature
  [/cover] */
  EthCntrlAdd->MAC_TIMESTAMP_CONTROL.U = ETH_17_GETHMAC_TS_ENABLE;

  /* Insert delay for back to back register writes */
  Eth_17_lBkToBkRegWrInsrtDly(EthCntrlCfgPtr->EthBkRegWrWaitTime);

  /* Initialize system time higher word second with ZERO.*/
  EthCntrlAdd->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS.B.TSHWR = 0U;

  /* Initialize system time(Second and Nanosecond part) to ZERO.*/
  /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
  characters due to SFR Naming constraints. Since compiler support
  more than 32 characters, no side effects seen.*/
  /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
  characters due to SFR Naming constraints. Since compiler support
   more than 32 characters, no side effects seen.*/
  /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
  characters due to SFR Naming constraints. Since compiler support
  more than 32 characters, no side effects seen.*/
  /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
  characters due to SFR Naming constraints. Since compiler support
   more than 32 characters, no side effects seen.*/
  EthCntrlAdd->MAC_SYSTEM_TIME_SECONDS_UPDATE.U = 0U;

  /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
   characters due to SFR Naming constraints. Since compiler support
   more than 32 characters, no side effects seen.*/
  /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
  characters due to SFR Naming constraints. Since compiler support
   more than 32 characters, no side effects seen.*/
  /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
  characters due to SFR Naming constraints. Since compiler support
  more than 32 characters, no side effects seen.*/
  /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
  characters due to SFR Naming constraints. Since compiler support
   more than 32 characters, no side effects seen.*/
  EthCntrlAdd->MAC_SYSTEM_TIME_NANOSECONDS_UPDATE.U = 0U;

  /*      ------------------------------------------------------------
   *                       TIME - COARSE UPDATE
   *      ------------------------------------------------------------
   *                (Not used currently in this function,
   *                described here just for information )
   *
   *   Consider for 50 Mhz Peripheral Bus frequency ,
   *                   PTP clock frequency = 50 Mhz.
   *
   *   Time period = 1/(50 * 10^6) seconds = (10^9)/(50 * 10^6) nanoseconds
   *   = (10^3)/50 nanoseconds = 1000/50 ns = 20 ns.
   *
   *   Value loaded  in GETH_MAC_SUB_SECOND_INCREMENT.B.SSINC register is
   *   added to nano second on every ptp clock cycle.
   *
   *   Hence Min resolution = 20 ns. That is, 20 counts should be loaded in
   *   GETH_MAC_SUB_SECOND_INCREMENT.B.SSINC register.
   *
   *   General formula for value to be
   *   loaded in GETH_MAC_SUB_SECOND_INCREMENT.B.SSINC = 1000/ EthOpetnFreq,
   *   where EthOpetnFreq is Ethernet Peripheral operation frequency in MHz. ;
   *
   *     ------------------------------------------------------------
   *                        TIME - FINE UPDATE
   *     ------------------------------------------------------------
   *                   (Used currently in this function )
   *
   *   System Time Update logic requires a 50-MHz clock frequency to
   *   achieve 20-ns accuracy, 50MHz clock is internal to GETH-IP.
   *
   *   Here on every ptp clock cycle(which is Ethernet Peripheral
   *   Bus frequency) Accumulator register( which is internal to GETH IP) is
   *   added with the contents of MAC_TIMESTAMP_ADDEND register.
   *   The arithmetic carry(Due to overflow of Accumulator ) that the
   *   Accumulator generates is used as a pulse to increment the system time
   *   counter. Everytime pulse is generated, it represents 20 ns as per below
   *   calculated addend value ,so always value to  be initialised to
   *   GETH_MAC_SUB_SECOND_INCREMENT.B.SSINC is 20
   *
   *   Value to be loaded to MAC_TIMESTAMP_ADDEND register =
   *                                              2^32/FreqDivisionRatio
   *
   *   where FreqDivisionRatio = PTP clock frequency/ 50 = EthOpetnFreq/50
   *
   * */

  FreqDivisionRatio = ((float32)EthOpetnFreq/(float32)ETH_17_GETHMAC_50MHZ);

  EthLocalCoreStatusPtr->EthRunTimeOpertnData.EthPrevFreqCompensationValue0 =
             ((float64)ETH_17_GETHMAC_32BITMAX / (float64)FreqDivisionRatio);

  /*Update SSINC value.*/
  EthCntrlAdd->MAC_SUB_SECOND_INCREMENT.B.SSINC =
                                        ETH_17_GETHMAC_SUB_SEC_INCREMENT_VAL;

  /*Update ADDEND register */
  EthCntrlAdd->MAC_TIMESTAMP_ADDEND.U = (uint32)
     EthLocalCoreStatusPtr->EthRunTimeOpertnData.EthPrevFreqCompensationValue0;

  /* Wait until Update Addend Register bit is Reset.*/
  IsTimeExpired = Eth_17_lTsAdRegTimeout(TimerInitWaitTicks,
                                         EthCntrlCfgPtr->EthCntrlIdx);

  /* [cover parentID={7F0E1C73-5D01-491b-9AC2-047871B09891}]
  Timeout happened
  [/cover] */
  if(Eth_17_lDemtimeout(IsTimeExpired,EthCntrlCfgPtr->EthDemAccess) == FALSE)
  {
    /* [cover parentID={78415636-C6C4-4e81-89A0-EC8143125AE6}]
    [/cover] */
    /* Set Update Addend Register bit to update content of the
    Timestamp Addend register.*/
    /* Time stamp Fine update */
    /* Timestamp digital roll over control for 1 nanosecond accuracy
       That is, each value in nanosecond register represent 1ns */
    EthCntrlAdd->MAC_TIMESTAMP_CONTROL.U |= (((uint32)ETH_17_GETHMAC_ENABLE
        << IFX_GETH_MAC_TIMESTAMP_CONTROL_TSCFUPDT_OFF) |
        ((uint32)ETH_17_GETHMAC_ENABLE <<
         IFX_GETH_MAC_TIMESTAMP_CONTROL_TSADDREG_OFF) |
        ((uint32)ETH_17_GETHMAC_ENABLE <<
         IFX_GETH_MAC_TIMESTAMP_CONTROL_TSCTRLSSR_OFF));

    /* Insert delay for back to back register writes */
    Eth_17_lBkToBkRegWrInsrtDly(EthCntrlCfgPtr->EthBkRegWrWaitTime);

    /* The Update Addend Register bit is cleared when the update is
    completed.Wait until Update Addend Register bit is cleared*/
    IsTimeExpired = Eth_17_lTsAdRegTimeout(TimerInitWaitTicks,
                                           EthCntrlCfgPtr->EthCntrlIdx);

    /* [cover parentID={F4E11944-7F79-4fb3-B3D9-9C803F10D08D}]
    Timeout happened
    [/cover] */
    if(Eth_17_lDemtimeout(IsTimeExpired,EthCntrlCfgPtr->EthDemAccess) == FALSE)
    {
      /* Wait for TSINIT bit is Reset to start Timestamp Initialization*/
      /* [cover parentID={C7ABA192-DA6D-429b-9807-B6FD21B7F75D}][/cover] */
      IsTimeExpired = Eth_17_lTsInitTimeout(TimerInitWaitTicks,
                                            EthCntrlCfgPtr->EthCntrlIdx);

      /* [cover parentID={260091F8-E295-473f-A001-0F28979EBBC7}]
      Timeout happened
      [/cover] */
      if(Eth_17_lDemtimeout(IsTimeExpired,EthCntrlCfgPtr->EthDemAccess)
                                                              == FALSE)
      {
        /* [cover parentID={6865F898-0B72-458c-B882-837BBB60DB75}]
        [/cover] */
        /* Initialize Time stamp.*/
        /* Add time stamp for all frames */
        EthCntrlAdd->MAC_TIMESTAMP_CONTROL.U |=
          (((uint32)ETH_17_GETHMAC_ENABLE <<
            IFX_GETH_MAC_TIMESTAMP_CONTROL_TSINIT_OFF) |
              ((uint32)ETH_17_GETHMAC_ENABLE <<
               IFX_GETH_MAC_TIMESTAMP_CONTROL_TSENALL_OFF));

        /* The TSINIT Register bit is cleared when when the initialization is
        completed. Wait until TSINIT Register bit is cleared */
        IsTimeExpired = Eth_17_lTsInitTimeout(TimerInitWaitTicks,
                                              EthCntrlCfgPtr->EthCntrlIdx);

        /* [cover parentID={21CA36F5-25D7-4c73-9572-179364CC4F3C}]
        Timeout happened
        [/cover] */
        if(Eth_17_lDemtimeout(IsTimeExpired,EthCntrlCfgPtr->EthDemAccess) ==
                                                                         FALSE)
        {
         /* [cover parentID={4712EE10-19C8-4533-B4F1-9A8C6CACDBA2}]
         Update return value as E_OK
         [/cover] */
          RetValue = E_OK;
        }
      }
    }
  }
  /* [cover parentID={92835D2F-FFE9-49af-BDB3-53420378C436}]
  [/cover] */
  return RetValue;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={9BC03B7C-52F8-4c1e-949C-F32CB9A1D77D}]  **
**                                                                            **
**                                                                            **
** Syntax           : void Eth_17_lSetCorrectionTime( const uint8 CtrlIdx,    **
**                           const Eth_TimeIntDiffType* const timeOffsetPtr,  **
**                           const Eth_RateRatioType* const rateRatioPtr )    **
**                                                                            **
** Description      : Allows the Time Slave to adjust the local               **
**                    ETH Reference clock in HW.                              **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx       -  Index of Eth Controller within the     **
**                                     context of the Ethernet driver.        **
**                    timeOffsetPtr -  offset between time stamp grandmaster  **
**                                     and time stamp by local clock:         **
**                                     (OriginTimeStampSync[FUP]-             **
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
static void Eth_17_lSetCorrectionTime(const uint8 CtrlIdx,
                              const Eth_TimeIntDiffType* const timeOffsetPtr,
                              const Eth_RateRatioType* const rateRatioPtr)
{
  float64 FreqCompensationValue0;
  float64 IngressTimeStampDelta;
  float64 OriginTimeStampDelta;
  float64 FreqScaleFactor;
  uint32  TimerCorrectnWaitTicks;
  uint32  DelayTickResolution;
  boolean IsTimeExpired;
  uint32 CurrentTimeSeconds;
  uint16 CurrentTimeHigSeconds;
  Ifx_GETH *EthCntrlAdd;
  Eth_17_GEthMac_CntrlStatusType *EthLocalCoreStatusPtr;
  const Eth_17_GEthMac_CoreCntrlConfigType *EthLocalCntrlCfgPtr;

  /* Get controller status and configuration data*/
  EthLocalCoreStatusPtr = Eth_17_lGetCtrlStatusPtr(CtrlIdx);
  EthLocalCntrlCfgPtr = Eth_17_lGetCtrlConfigPtr(CtrlIdx);
  /* Get base address of the indexed controller */
  EthCntrlAdd = Eth_GEthMacCntrl[CtrlIdx];
  /* Get STM timer current resolution and calculate maximum number of ticks
  to wait before expected hardware behaviour is occurd- That timer correcttion*/
  DelayTickResolution = Mcal_DelayTickResolution();
  TimerCorrectnWaitTicks  = \
                      (ETH_17_GETHMAC_MAXTIMEOUT_COUNT / DelayTickResolution);
  /* Do not allow ticks to wait to be zero, if STM timer resolution is lower*/
  /* [cover parentID={195D5666-7C76-486d-A91C-6937F3D59F22}]
  [/cover] */
  if(TimerCorrectnWaitTicks == ETH_17_GETHMAC_ZERO)
  {
    /* [cover parentID={ADC4F690-6F38-40ab-9EEC-03A0099AC80C}]
    [/cover] */
    TimerCorrectnWaitTicks++;
  }

  /* Wait until TSUPDT bit is zero, before starting system time update */
  /* [cover parentID={41D51976-AD50-47a3-8E46-B63E6DDD33F6}]
  [/cover] */
  IsTimeExpired = Eth_17_lTsUpdtTimeout(TimerCorrectnWaitTicks, CtrlIdx);

  /* [cover parentID={FADA5DFE-C5B1-45aa-AD7C-EDF79FFC1634}]
  Timeout happened
  [/cover] */
  /* Check if timeout happened  while waiting for TSUPDT bit is zero.If not,
  Add or subtract Second, Nanosecond and second higher word */
  if(Eth_17_lDemtimeout(IsTimeExpired,EthLocalCntrlCfgPtr->\
                                                        EthDemAccess) == FALSE)
  { /* [cover parentID={7E4D7111-0C48-42d1-AEEE-228908F1AEA4}][/cover] */
    if(timeOffsetPtr->sign == FALSE)
    {
      /* Sign is false, means Subtract or Negative time*/
      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond
      32 characters due to SFR Naming constraints. Since compiler support
      more than 32 characters, no side effects seen.*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond
      32 characters due to SFR Naming constraints. Since compiler support
      more than 32 characters, no side effects seen.*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond
      32 characters due to SFR Naming constraints. Since compiler support
      more than 32 characters, no side effects seen.*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond
      32 characters due to SFR Naming constraints. Since compiler support
      more than 32 characters, no side effects seen.*/
      EthCntrlAdd->MAC_SYSTEM_TIME_SECONDS_UPDATE.U = \
        (uint32) \
        ((uint64)ETH_17_GETHMAC_TWO_POW_32_VAL - \
              (uint64)timeOffsetPtr->diff.seconds);

      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond
      32 characters due to SFR Naming constraints. Since compiler support
      more than 32 characters, no side effects seen.*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond
      32 characters due to SFR Naming constraints. Since compiler support
      more than 32 characters, no side effects seen.*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond
      32 characters due to SFR Naming constraints. Since compiler support
      more than 32 characters, no side effects seen.*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond
      32 characters due to SFR Naming constraints. Since compiler support
      more than 32 characters, no side effects seen.*/
      EthCntrlAdd->MAC_SYSTEM_TIME_NANOSECONDS_UPDATE.B.TSSS = \
      (uint32)\
      (ETH_17_GETHMAC_ONE_SEC_TO_NANOSEC - timeOffsetPtr->diff.nanoseconds);

      /* Read current time (seconds)*/
      CurrentTimeSeconds = EthCntrlAdd->MAC_SYSTEM_TIME_SECONDS.U;
      /* Read current time (High word seconds)*/
      CurrentTimeHigSeconds = EthCntrlAdd->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS.\
                                                                       B.TSHWR;
      /* Check if current timer (seconds) is greater than requested seconds
      offset to be reduced from current seconds. If not, High seconds has to
      be reduced additionally 1. This is due to that, when updating seconds
      time, if seconds underflow happens, hardware will not automatically
      reduce High seconds. Hence it is taken care in ETH driver */
      /* [cover parentID={7E4D7111-0C48-42d1-AEEE-228908F1AEA4}][/cover] */
      if((timeOffsetPtr->diff.seconds > CurrentTimeSeconds) && \
         (CurrentTimeHigSeconds != (uint16)ETH_17_GETHMAC_ZERO))
      {
        EthCntrlAdd->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS.B.TSHWR = \
                 (EthCntrlAdd->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS.B.TSHWR - \
                                                   (uint16)ETH_17_GETHMAC_ONE);
      }

      /* Insert delay for back to back register writes */
      Eth_17_lBkToBkRegWrInsrtDly(EthLocalCntrlCfgPtr->EthBkRegWrWaitTime);

      EthCntrlAdd->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS.B.TSHWR = \
          EthCntrlAdd->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS.B.TSHWR-\
                                        timeOffsetPtr->diff.secondsHi;

      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond
      32 characters due to SFR Naming constraints. Since compiler support
      more than 32 characters, no side effects seen.*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond
      32 characters due to SFR Naming constraints. Since compiler support
      more than 32 characters, no side effects seen.*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond
      32 characters due to SFR Naming constraints. Since compiler support
      more than 32 characters, no side effects seen.*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond
      32 characters due to SFR Naming constraints. Since compiler support
      more than 32 characters, no side effects seen.*/
      EthCntrlAdd->MAC_SYSTEM_TIME_NANOSECONDS_UPDATE.B.ADDSUB = \
                                                            ETH_17_GETHMAC_ONE;
    }
    else
    {
      /* [cover parentID={7E4D7111-0C48-42d1-AEEE-228908F1AEA4}][/cover] */
      /* Sign is positive, means Add or Positive time*/
      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
      characters due to SFR Naming constraints. Since compiler support
      more than 32 characters, no side effects seen.*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
      characters due to SFR Naming constraints. Since compiler support
      more than 32 characters, no side effects seen.*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
      characters due to SFR Naming constraints. Since compiler support
      more than 32 characters, no side effects seen.*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
      characters due to SFR Naming constraints. Since compiler support
      more than 32 characters, no side effects seen.*/
      EthCntrlAdd->MAC_SYSTEM_TIME_SECONDS_UPDATE.U =\
                                             timeOffsetPtr->diff.seconds;

      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond
      32 characters due to SFR Naming constraints. Since compiler support
      more than 32 characters, no side effects seen.*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond
      32 characters due to SFR Naming constraints. Since compiler support
      more than 32 characters, no side effects seen.*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond
      32 characters due to SFR Naming constraints. Since compiler support
      more than 32 characters, no side effects seen.*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond
      32 characters due to SFR Naming constraints. Since compiler support
      more than 32 characters, no side effects seen.*/
      EthCntrlAdd->MAC_SYSTEM_TIME_NANOSECONDS_UPDATE.B.TSSS = \
               timeOffsetPtr->diff.nanoseconds;

      /* Insert delay for back to back register writes */
      Eth_17_lBkToBkRegWrInsrtDly(EthLocalCntrlCfgPtr->EthBkRegWrWaitTime);

      EthCntrlAdd->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS.B.TSHWR = \
          EthCntrlAdd->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS.B.TSHWR +\
                                    timeOffsetPtr->diff.secondsHi;

      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond
      32 characters due to SFR Naming constraints. Since compiler support
      more than 32 characters, no side effects seen.*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond
      32 characters due to SFR Naming constraints. Since compiler support
      more than 32 characters, no side effects seen.*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond
      32 characters due to SFR Naming constraints. Since compiler support
      more than 32 characters, no side effects seen.*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond
      32 characters due to SFR Naming constraints. Since compiler support
      more than 32 characters, no side effects seen.*/
      EthCntrlAdd->MAC_SYSTEM_TIME_NANOSECONDS_UPDATE.B.ADDSUB = \
                                                           ETH_17_GETHMAC_ZERO;
    }

    /* Set TSUPDT bit, Hence, Time update process starts.*/
    EthCntrlAdd->MAC_TIMESTAMP_CONTROL.B.TSUPDT = ETH_17_GETHMAC_ONE;

    /* Insert delay for back to back register writes */
    Eth_17_lBkToBkRegWrInsrtDly(EthLocalCntrlCfgPtr->EthBkRegWrWaitTime);

    /*Wait until TSUPDT bit reset. It means time update is finished.*/
    IsTimeExpired = Eth_17_lTsUpdtTimeout(TimerCorrectnWaitTicks, CtrlIdx);

    /* [cover parentID={C3EC8624-1D80-43d5-9D48-84DCD4865321}]
    Timeout happened
    [/cover] */
    /* Check if timeout happened. */
    if(Eth_17_lDemtimeout(IsTimeExpired,EthLocalCntrlCfgPtr->EthDemAccess) ==\
                                                                         FALSE)
    {
      /* Convert OriginTimeStampDelta to nanoseconds.It is converted to float64
      to hold maximum value of this parameter.
      float64 range can hold maximum value*/
      OriginTimeStampDelta = (float64)rateRatioPtr->OriginTimeStampDelta.\
                                                                diff.secondsHi;
      /* Left shit by 32 to place Hi second value at 5th and 6th Byte position*/
      OriginTimeStampDelta = OriginTimeStampDelta * \
                              (float64)ETH_17_GETHMAC_TWO_POW_32_VAL;
      /* Place Second value at 1st, 2nd, 3rd and 4th byte. Hence Hi second and
      Seconds value are combined*/
      OriginTimeStampDelta = OriginTimeStampDelta + \
                             ((float64)rateRatioPtr->OriginTimeStampDelta.diff.\
                                                                      seconds);
      /* Convert the combine second value to Nanoseconds */
      OriginTimeStampDelta = OriginTimeStampDelta * \
                              (float64)ETH_17_GETHMAC_ONE_SEC_TO_NANOSEC;
      /* Add Nano second part of the parameter to last result. Hence total time
      is converted to Nanoseconds*/
      OriginTimeStampDelta = OriginTimeStampDelta + \
                             ((float64)rateRatioPtr->OriginTimeStampDelta.diff.\
                               nanoseconds);

      /* Convert IngressTimeStampDelta to nanoseconds.It is converted to
      float64 to hold maximum value of this parameter.
      float64 range can hold maximum value*/
      IngressTimeStampDelta = (float64)rateRatioPtr->IngressTimeStampDelta.\
                                diff.secondsHi;
      /* Left shit by 32 to place Hi second value at 5th and 6th Byte position*/
      IngressTimeStampDelta = IngressTimeStampDelta * \
                                (float64)ETH_17_GETHMAC_TWO_POW_32_VAL;
      /* Place Second value at 1st, 2nd, 3rd and 4th byte. Hence Hi second and
      Seconds value are combined*/
      IngressTimeStampDelta = IngressTimeStampDelta + \
                            ((float64)rateRatioPtr->IngressTimeStampDelta.diff.\
                               seconds);
      /* Convert the combine second value to Nanoseconds */
      IngressTimeStampDelta = IngressTimeStampDelta * \
                                (float64)ETH_17_GETHMAC_ONE_SEC_TO_NANOSEC;
      /* Add Nano second part of the parameter to last result. Hence total time
      is converted to Nanoseconds*/
      IngressTimeStampDelta  = IngressTimeStampDelta + \
                            ((float64)rateRatioPtr->IngressTimeStampDelta.diff.\
                               nanoseconds);

      /* [cover parentID={1C2580EF-DC17-429a-BB84-F0BF3D703BC3}]
      IngressTimeStampDelta(from rateRatioPtr) is ZERO
      [/cover] */
      /* Changes in condition incorporated to remove Tasking compiler warning
      TCVX-44339 */
      if (IngressTimeStampDelta > ETH_17_GETHMAC_EPSILON_FLOAT_VALUE)
      {
        /* [cover parentID={307264DF-D6DB-4d11-9603-609E3D7C39F4}]
        Calculate the freq scale factor
        [/cover] */
        FreqScaleFactor = \
        (((float64)ETH_17_GETHMAC_TWO * OriginTimeStampDelta) - \
           IngressTimeStampDelta) / IngressTimeStampDelta;
        /* Check the correction factor is greater than zero. Zero or Negative
        value is not a valid correction factor*/
        /* [cover parentID={438F4C81-5013-47ba-BD3F-D9BD1F9CC052}]
        Calculated FreqScaleFactor is  <=  0
        [/cover] */
        /* Changes in condition incorporated to remove Tasking compiler warning
        TCVX-44339 */
        if(FreqScaleFactor < ETH_17_GETHMAC_EPSILON_FLOAT_VALUE)
        {
          /* [cover parentID={235C9C54-31DA-4ba6-9654-C89AAD5EF4F4}]
          Set the frequency scale factor to 1
          [/cover] */
          FreqScaleFactor = (float64)1.0;
        }
      }
      else
      {
        /* [cover parentID={A3B9E54D-506D-4e85-AAF4-A3073B0313C9}]
        Set the frequency scale factor to 1
        [/cover] */
        FreqScaleFactor = (float64)1.0;
      }

      FreqCompensationValue0 = EthLocalCoreStatusPtr->EthRunTimeOpertnData.\
                               EthPrevFreqCompensationValue0 * FreqScaleFactor;
      /* [cover parentID={196A74C8-DD5D-46e1-A6A8-B0B9FE21470F}]
      Frequency Compensation Value is less than (2^32)
      [/cover] */
      if(FreqCompensationValue0 < (float64)ETH_17_GETHMAC_32BITMAX )
      {
        /* [cover parentID={D42D65F8-D54B-470f-B402-6A914147CF4A}]
        Update the ADDEND register
        [/cover] */
        EthCntrlAdd->MAC_TIMESTAMP_ADDEND.U= (uint32)FreqCompensationValue0;
      }
      else
      {
        /* [cover parentID={72325FE2-2996-4ab3-9C90-36C0407F7047}]
        Update the ADDEND register
        [/cover] */
        EthCntrlAdd->MAC_TIMESTAMP_ADDEND.U = \
                      (uint32)(ETH_17_GETHMAC_32BITMAX - ETH_17_GETHMAC_ONE);
      }
      /* Wait until Update Addend Register bit is Reset.*/
      IsTimeExpired = Eth_17_lTsAdRegTimeout(TimerCorrectnWaitTicks, CtrlIdx);
      /* [cover parentID={8B0B5EA1-FCFF-4189-BD69-7C979ED98B4D}]
      Timeout happend
      [/cover] */
      if(Eth_17_lDemtimeout(IsTimeExpired,EthLocalCntrlCfgPtr->EthDemAccess) ==\
                                                                         FALSE)
      {
        /* [cover parentID={80BF498C-3668-4f55-892D-A4A1818C9225}]
        [/cover] */
        /* Set Update Addend Register bit to update content of the
        Timestamp Addend register.
        Info :When this bit is set, the content of the Timestamp Addend
        register is updated in the PTP block for fine correction*/
        EthCntrlAdd->MAC_TIMESTAMP_CONTROL.B.TSADDREG = ETH_17_GETHMAC_ONE;
        /* The Update Addend Register bit bit is cleared when the update is
        completed.Wait until Addend Register bit bit is cleared*/
        IsTimeExpired = Eth_17_lTsAdRegTimeout(TimerCorrectnWaitTicks, CtrlIdx);
        /* [cover parentID={FEF5AC82-3525-4ec8-8F68-CCD29BBE903A}]
        Timeout happend
        [/cover] */
        if(Eth_17_lDemtimeout(IsTimeExpired,EthLocalCntrlCfgPtr->EthDemAccess)\
                                                                      == FALSE)
        {
          /* [cover parentID={34699423-4038-4610-A766-F46A770CFBC6}]
          update the freq compensation value for the next time correction
          [/cover] */
          EthLocalCoreStatusPtr->EthRunTimeOpertnData.\
                        EthPrevFreqCompensationValue0 = FreqCompensationValue0;
        }
      }
    }
  }
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={A58F2E93-1FDC-477b-BE03-E80A5B8A7249}]  **
**                                                                            **
** Syntax           : Std_ReturnType Eth_17_lSetGlobalTime                    **
**                           (uint8 CtrlIdx,                                  **
**                            const Eth_TimeStampType* const timeStampPtr)    **
**                                                                            **
** Description      : Allows the Time Master to adjust the global ETH         **
**                    Reference clock in HW. We can use this method to        **
**                    set a global time base on ETH in general or to          **
**                    synchronize the global ETH time base with another       **
**                    time base, e.g. FlexRay.                                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
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
                                       E_NOT_OK: failed                       **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Eth_17_lSetGlobalTime(const uint8 CtrlIdx, const
                                         Eth_TimeStampType* const timeStampPtr)
{
  Std_ReturnType RetValue = E_NOT_OK;
  uint32 TimerSetWaitTicks;
  uint32 DelayTickResolution;
  boolean IsTimeExpired;
  Ifx_GETH *EthCntrlAdd;
  const Eth_17_GEthMac_CoreCntrlConfigType *EthLocalCntrlCfgPtr;

  /* Get controller configuration data */
  EthLocalCntrlCfgPtr = Eth_17_lGetCtrlConfigPtr(CtrlIdx);
  /* Get base address of the indexed controller */
  EthCntrlAdd = Eth_GEthMacCntrl[CtrlIdx];
  /* Get STM timer current resolution and calculate maximum number of ticks
  to wait before expected hardware behaviour is occurd- That is Set timer*/
  DelayTickResolution = Mcal_DelayTickResolution();
  TimerSetWaitTicks  = (ETH_17_GETHMAC_MAXTIMEOUT_COUNT / DelayTickResolution);
  /* Do not allow ticks to wait to be zero, if STM timer resolution is lower*/
  /* [cover parentID = {AAEB3DC0-5F39-461d-9142-A8682B9D5522}]
  [/cover] */
  if(TimerSetWaitTicks == ETH_17_GETHMAC_ZERO)
  {
    /* [cover parentID={861778CC-4112-40dc-B455-A4526D1DFB61}]
    Increment the ticks
    [/cover] */
    TimerSetWaitTicks++;
  }

  /* Wait for TSINIT bit is is read as zero to start Timestamp Initialization*/
  /* [cover parentID={5213FFA6-303D-4c6c-8EDE-D4D2CE8651E0}]
  [/cover] */
  IsTimeExpired = Eth_17_lTsInitTimeout(TimerSetWaitTicks, CtrlIdx);

  /* [cover parentID={2BA7763A-D7C6-4e60-AF97-D323A4BB27F6}]
  Timeout happend
  [/cover] */
  /* Check if timeout not happend. */
  if(Eth_17_lDemtimeout(IsTimeExpired,EthLocalCntrlCfgPtr->EthDemAccess) \
                                                                      == FALSE)
  {
    /* Update Second, Nanosecond and second higher word*/
    /* [cover parentID={F3548EF9-2240-428e-9CA8-5799B6A5079D}]
    [/cover] */
    /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
    characters due to SFR Naming constraints. Since compiler support
    more than 32 characters, no side effects seen.*/
    /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
    characters due to SFR Naming constraints. Since compiler support
     more than 32 characters, no side effects seen.*/
    /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
    characters due to SFR Naming constraints. Since compiler support
    more than 32 characters, no side effects seen.*/
    /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
    characters due to SFR Naming constraints. Since compiler support
    more than 32 characters, no side effects seen.*/
    EthCntrlAdd->MAC_SYSTEM_TIME_SECONDS_UPDATE.U = timeStampPtr->seconds;

    /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
    characters due to SFR Naming constraints. Since compiler support
    more than 32 characters, no side effects seen.*/
    /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
    characters due to SFR Naming constraints. Since compiler support
     more than 32 characters, no side effects seen.*/
    /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
    characters due to SFR Naming constraints. Since compiler support
    more than 32 characters, no side effects seen.*/
    /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
    characters due to SFR Naming constraints. Since compiler support
    more than 32 characters, no side effects seen.*/

    EthCntrlAdd->MAC_SYSTEM_TIME_NANOSECONDS_UPDATE.B.TSSS = \
       (uint32)(timeStampPtr->nanoseconds & ETH_17_GETHMAC_NANOSEC_UPDATE_MASK);
    EthCntrlAdd->MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS.B.TSHWR = \
          (uint16)timeStampPtr->secondsHi;
    /* Set TSINIT bit to start initializing timer values */
    EthCntrlAdd->MAC_TIMESTAMP_CONTROL.B.TSINIT = ETH_17_GETHMAC_ONE;
    /* Wait until TSINIT bit is read as zero. So Initialization is finished */
    IsTimeExpired = Eth_17_lTsInitTimeout(TimerSetWaitTicks, CtrlIdx);
    /* [cover parentID={857E735D-8177-4753-9CF7-DD53668A76F4}]
    Timeout happend
    [/cover] */
    /* Check if timeout not happend. */
    if (Eth_17_lDemtimeout(IsTimeExpired,EthLocalCntrlCfgPtr->EthDemAccess)\
                                                                      == FALSE)
    {
      /* [cover parentID={0AC8BCF5-20A4-426f-904C-058803F90438}]
      Set Ret value to E_OK
      [/cover] */
      RetValue = E_OK;
    }
    else
    {
      /* [cover parentID={5A042BE8-D2E4-4ce1-AF98-3C96408509EF}]
      Set Ret value to E_NOT_OK
      [/cover] */
      RetValue = E_NOT_OK;
    }
  }
 return RetValue;
}
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={D5FFEC3E-FC98-4577-AE3B-2CB39B18A1AB}]  **
**                                                                            **
** Syntax           : static boolean Eth_17_lTsAdRegTimeout(                  **
**                                         const uint32 WaitTicks,            **
**                                         const uint8 CtrlIdx)               **
**                                                                            **
** Description      : Function to check that MAC_TIMESTAMP_CONTROL.TSADDREG   **
**                    bit is cleared before timeout happens                   **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : NA                                                      **
**                                                                            **
** Parameters (in)  : WaitTicks - Number of ticks to wait for timeout         **
**                    CtrlIdx - Controller Index.                             **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FALSE - Register Bit cleared and no timeout detected    **
**                    TRUE -  Register Bit not cleared and timeout detected   **
**                                                                            **
*******************************************************************************/
static boolean Eth_17_lTsAdRegTimeout(const uint32 WaitTicks,
                                                           const uint8 CtrlIdx)
{
  uint32 BaseSTMTick;
  uint32 CurrSTMTick;
  boolean IsTimeExpired;
  uint32 RegVal;
  const Ifx_GETH *EthCntrlAdd;
  /* Get base address of the indexed controller */
  EthCntrlAdd = Eth_GEthMacCntrl[CtrlIdx];
  /* Wait until Update Addend Register bit is cleared.*/
  /*Get current STM tick*/
  CurrSTMTick         = Mcal_DelayGetTick();
  BaseSTMTick         = CurrSTMTick;
  IsTimeExpired       = FALSE;
  do
  {
    /* [cover parentID={AF51B27C-9805-4a54-9EF0-0D029234071D}]
    Read the ADDEND register
      [/cover] */
    RegVal = (uint32)EthCntrlAdd->MAC_TIMESTAMP_CONTROL.B.TSADDREG;
    /* [cover parentID={CAC6746C-5C99-4de9-BBA7-F11BCBDA9CD1}]
    (current tick - first time tick) < Maximum time to wait for
    Hardware time out error
    [/cover] */
    /* Check wait time is reached at maxmum timeout configured*/
    if((((uint32)((CurrSTMTick - BaseSTMTick) & \
          ETH_17_GETHMAC_STM_TICK_OVERFLOW)) >= \
          WaitTicks) && (RegVal == (uint32)ETH_17_GETHMAC_ONE))
    {
      /*Timeout Happend and Update Addend Register bit is not cleared yet*/
      /* [cover parentID={2CA1EE61-93F3-4829-8C61-A67D1947CC43}]
      [/cover] */
      IsTimeExpired = TRUE;
    }
    /*Get current STM tick*/
    CurrSTMTick = Mcal_DelayGetTick();
    /* [cover parentID={0D97C7F7-13BA-4da9-B3C2-008290CB84D7}]
    Update Addend Register bit is cleared
    [/cover] */
  }while((RegVal == (uint32)ETH_17_GETHMAC_ONE) && (IsTimeExpired == FALSE));
  /* [cover parentID={3AD691A4-6062-4429-9902-32D378E2436C}]
  Return the time expired status
  [/cover] */
  return IsTimeExpired;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={77902FB9-EABE-4539-9016-F96CCB26C600}]  **
**                                                                            **
** Syntax           : static boolean Eth_17_lTsInitTimeout(                   **
**                                         const uint32 WaitTicks,            **
**                                         const uint8 CtrlIdx)               **
**                                                                            **
** Description      : Function to check that MAC_TIMESTAMP_CONTROL.TSINIT     **
**                    bit is cleared before timeout happens                   **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : NA                                                      **
**                                                                            **
** Parameters (in)  : WaitTicks - Number of ticks to wait for timeout         **
**                    CtrlIdx - Controller Index.                             **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FALSE - Register Bit cleared and no timeout detected    **
**                    TRUE -  Register Bit not cleared and timeout detected   **
**                                                                            **
*******************************************************************************/
static boolean Eth_17_lTsInitTimeout(const uint32 WaitTicks,
                                                           const uint8 CtrlIdx)
{
  uint32 BaseSTMTick;
  uint32 CurrSTMTick;
  boolean IsTimeExpired;
  uint32 RegVal;
  const Ifx_GETH *EthCntrlAdd;
  /* Get base address of the indexed controller */
  EthCntrlAdd = Eth_GEthMacCntrl[CtrlIdx];
  /* Wait for TSINIT bit is cleared */
  /*Get current STM tick*/
  CurrSTMTick         = Mcal_DelayGetTick();
  BaseSTMTick         = CurrSTMTick;
  IsTimeExpired       = FALSE;
  do
  {
    /* [cover parentID={30C22CB5-AD3F-41e5-851D-E15B7FC6C2E5}]
    Read the TSINIT bit
    [/cover] */
    RegVal = (uint32)EthCntrlAdd->MAC_TIMESTAMP_CONTROL.B.TSINIT;
    /* [cover parentID={20EA14D8-8433-4c49-9814-051B4FFD61C2}]
    (current tick - first time tick) < Maximum time to wait for
    Hardware time out error
    [/cover] */
    /* Check wait time is reached at maxmum timeout configured*/
    if((((uint32)((CurrSTMTick - BaseSTMTick) & \
          ETH_17_GETHMAC_STM_TICK_OVERFLOW)) >= \
          WaitTicks) && (RegVal == (uint32)ETH_17_GETHMAC_ONE))
    {
      /*Timeout Happend and TSINIT bit is not cleared yet*/
      /* [cover parentID={41BD61F0-933B-454b-937B-132BA12F749E}]
      [/cover] */
      IsTimeExpired = TRUE;
    }
    /*Get current STM tick*/
    CurrSTMTick = Mcal_DelayGetTick();
    /* [cover parentID={BE78F97E-46B6-47f2-87CB-17CFC35AD10F}]
    TSINIT Register bit is cleared
    [/cover] */
  }while((RegVal == (uint32)ETH_17_GETHMAC_ONE) && (IsTimeExpired == FALSE));
  /* [cover parentID={3F42204A-9BD9-40eb-8775-E9206B6C50AB}]
  Retur the time espired status
  [/cover] */
  return IsTimeExpired;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={9FB8E170-1AED-4882-B0A9-88D67ADA2C3E}]  **
**                                                                            **
** Syntax           : static boolean Eth_17_lTsUpdtTimeout(                   **
**                                         const uint8 CtrlIdx,               **
**                                         const uint32 WaitTicks)            **
**                                                                            **
** Description      : Function to check that MAC_TIMESTAMP_CONTROL.TSUPDT     **
**                    bit is cleared before timeout happens                   **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : NA                                                      **
**                                                                            **
** Parameters (in)  : CtrlIdx - Controller Index.                             **
**                    WaitTicks - Number of ticks to wait for timeout         **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : FALSE - Register Bit cleared and no timeout detected    **
**                    TRUE -  Register Bit not cleared and timeout detected   **
**                                                                            **
*******************************************************************************/
static boolean Eth_17_lTsUpdtTimeout(const uint32 WaitTicks,const uint8 CtrlIdx)
{
  uint32 BaseSTMTick;
  uint32 CurrSTMTick;
  boolean IsTimeExpired;
  uint32 RegVal;
  const Ifx_GETH *EthCntrlAdd;
  /* Get base address of the indexed controller */
  EthCntrlAdd = Eth_GEthMacCntrl[CtrlIdx];
  /* Wait for TSUPDT bit is cleared */
  /*Get current STM tick*/
  CurrSTMTick         = Mcal_DelayGetTick();
  BaseSTMTick         = CurrSTMTick;
  IsTimeExpired       = FALSE;
  do
  {
    /* [cover parentID={72280211-31AF-42c7-822E-C352FB4EBADC}]
    Read the TSUPDT bit.
    [/cover] */
    RegVal = (uint32)EthCntrlAdd->MAC_TIMESTAMP_CONTROL.B.TSUPDT;

    /* [cover parentID={DCA68AB5-EAF4-4249-B044-234E2C495EB9}]
    (current tick - first time tick) < Maximum time to wait for
    Hardware time out error
    [/cover] */
    /* Check wait time is reached at maxmum timeout configured*/
    if((((uint32)((CurrSTMTick - BaseSTMTick) & \
         ETH_17_GETHMAC_STM_TICK_OVERFLOW)) >= \
         WaitTicks) && (RegVal == (uint32)ETH_17_GETHMAC_ONE))
    {
      /*Timeout Happend and TSUPDT bit is not cleared yet*/
      /* [cover parentID={D2610F73-C264-4837-AE65-E52776CB0988}]
      [/cover] */
      IsTimeExpired = TRUE;
    }
    /*Get current STM tick*/
    CurrSTMTick = Mcal_DelayGetTick();
    /* [cover parentID={16CB1227-FD36-44e1-B26B-939B830173FD}]
    TSUPDT Register bit is cleared
    [/cover] */
  }while((RegVal == (uint32)ETH_17_GETHMAC_ONE) && (IsTimeExpired == FALSE));
  /* [cover parentID={FD32E058-8FF9-4785-802B-FE7BD569450C}]
  Return the time expiry status
  [/cover] */
  return IsTimeExpired;
}

#endif /*end of ETH_17_GETHMAC_GLOBALTIMESUPPORT */


/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={5B7B4CA7-B689-4d32-9513-E706A599B999}]  **
**                                                                            **
** Syntax           : static void Eth_17_lTransmit( const uint8 CtrlIdx,      **
**                       const uint8 BufIdx,                                  **
**                       const Eth_FrameType FrameType,                       **
**                       const boolean TxConfirmation,                        **
**                       const uint16 LenByte, const uint8* const PhysAddrPtr)**
**                                                                            **
** Description      :Triggers transmission of a previously                    **
**                   filled transmit buffer                                   **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx - Controller Index.                             **
**                    BufIdx - Index of the buffer resource                   **
**                    FrameType- Ethernet frame type                          **
**                    TxConfirmation - Activates transmission confirmation    **
**                    LenByte - Data length in byte                           **
**                    PhysAddrPtr - Physical target address                   **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
                           Ethernet Frame Format
+----------+-------------+--------------+-----------------------+--------------+
+  DesAddr +  SourceAddr + FrameLen /   + Frame Data /          +   CheckSum   +
+ (6Bytes) +   (6Bytes)  + Type(2Bytes) + Payload(46-1500Bytes) +    (4Bytes)  +
+----------+-------------+--------------+-----------------------+--------------+
*******************************************************************************/
static void Eth_17_lTransmit(
             const uint8 CtrlIdx,
             const Eth_BufIdxType BufIdx, const Eth_FrameType FrameType,
             const boolean TxConfirmation, const uint16 LenByte,
             const uint8* const PhysAddrPtr)
{
  uint8* TxBufferAddress;
  uint32 TxLength;
  uint32 LoopCount;
  const Eth_17_GEthMac_CntrlStatusType *EthLocalCoreStatusPtr;
  const Eth_17_GEthMac_CoreCntrlConfigType *EthLocalCntrlCfgPtr;
  Ifx_GETH *EthCntrlAdd;
  uint8 IntEnabled;

  /* Get controller status */
  EthLocalCoreStatusPtr = Eth_17_lGetCtrlStatusPtr(CtrlIdx);
  /* Get base address of the indexed controller */
  EthCntrlAdd = Eth_GEthMacCntrl[CtrlIdx];
  /* Get controller configuration data */
  EthLocalCntrlCfgPtr = Eth_17_lGetCtrlConfigPtr(CtrlIdx);
  /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between integer to a
  pointer type is performed to fetch buffer address from DMA
  descriptor. This is the intended design and valid as per DMA hardware
  design. There are no side effects seen by violating this rule.*/
  /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from unsigned long to pointer
    is performed to access the buffer address from DMA descriptor.
    This is the intended design and valid as per DMA hardware design.
    There are no side effects seen by violating this rule.*/
  TxBufferAddress = (uint8*)(EthLocalCoreStatusPtr->EthBuffDecPtr->\
                    EthDmaTxDescPtr[BufIdx].TDES0);
  IntEnabled = (uint8)((EthLocalCntrlCfgPtr->EthCntrlProperties >>\
      ETH_17_GETHMAC_TXINT_POS) & ETH_17_GETHMAC_ONE);
  /* [cover parentID={D9BFFF78-94B0-4038-B116-1A46538A217B}]
  Fill the Destination MAC Address in Tx Buffer
  [/cover] */
  /* Fill the Destination MAC Address in TX Buffer */
  for(LoopCount=(uint32)ETH_17_GETHMAC_ZERO; \
      LoopCount < (uint32)ETH_17_GETHMAC_MACADDRESS_LEN; LoopCount++)
  {
    TxBufferAddress[LoopCount] = (uint8)PhysAddrPtr[LoopCount];
  }

  /* [cover parentID={35ACBB68-75FF-457a-94BC-74B997CE4DE6}]
  Fill the Source MAC address in Tx  buffer
  [/cover] */
  /* Copy source MAC address in TX buffer */
  /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic is performed
  using '+' operator to access the MAC address position in Ethernet packet from
  from the reserved RAM address which is configured in DMA descriptors. Since it
  is accessing the pointer to data type uint8,there are no side
  effects seen by violating this rule.*/
  Eth_17_lGetPhysAddr(TxBufferAddress + ETH_17_GETHMAC_FRAME_SRCADDR_POS,\
                                                                      CtrlIdx);

  /* [cover parentID={318A313F-780A-4178-8AC9-2B948BE0D622}]
  Fill the Frame Type in Tx Buffer
  [/cover] */
  /* Fill the Frame Type in TX Buffer */
  TxBufferAddress[ETH_17_GETHMAC_FRAME_TYPE_POS_MSB] = \
   (uint8)((FrameType >> ETH_17_GETHMAC_SHIFT_8BIT) & ETH_17_GETHMAC_BYTE_MASK);
  TxBufferAddress[ETH_17_GETHMAC_FRAME_TYPE_POS_LSB] = \
                   (uint8)(FrameType & ETH_17_GETHMAC_BYTE_MASK);

  /*Buffer2 size would be zero, single buffer and single frame at the time.
  Here Header length(ETH_17_GETHMAC_FRAMEHEADER_LENGTH) is added because
  provideTxbuffer API only provides the Payload buffer.*/
  TxLength = (uint32)(((uint32)LenByte + ETH_17_GETHMAC_FRAMEHEADER_LENGTH) & \
                  (uint32)ETH_17_GETHMAC_DMA_TX_DESC_PAC_LEN_MASK);

  /* Critical Section As Global Variables used in ISR also. */
  /* [cover parentID={032E908E-1432-4d68-84F7-2B6295E4441A}]
  If tx interrupt in enabled
  [/cover] */
  if(IntEnabled == ETH_17_GETHMAC_ONE)
  {
    /* [cover parentID={93E87DA2-AAB3-45a0-8C7C-2123F78C2FEC}]
    Enter critical section
    [/cover] */
    SchM_Enter_Eth_17_GEthMac_TransmitData();
  }

  /* [cover parentID={4406B8F0-2B1D-4fc6-B9CD-89841CD037E5}]
  Tx Confirmation Needed
  [/cover] */
  if(TxConfirmation == (boolean)TRUE)
  {
    /* Tx confirmation request is updated in BuffTable,Based on this
    buffer status will be cleared during Eth_Txconfirmation Call */
    /* [cover parentID={A44352CC-D8B8-475d-B2C6-4D7C41186EAE}][/cover] */
    EthLocalCoreStatusPtr->EthBuffDecPtr->EthTxBuffTablePtr[BufIdx].\
                                              TxConfirmReq= ETH_17_GETHMAC_ONE;
  }
  else
  {
    /* [cover parentID={7E980DB2-85D8-468e-9ED3-D362F7B95420}]
    Set Tx Confirmation as NOT NEEDED in Tx Buffer Table( at BufIdx location)
    [/cover] */
    EthLocalCoreStatusPtr->EthBuffDecPtr->EthTxBuffTablePtr[BufIdx].\
                                            TxConfirmReq = ETH_17_GETHMAC_ZERO;
  }

  /*Update Tx descriptor - TDES3, with packet length.*/
  EthLocalCoreStatusPtr->EthBuffDecPtr->EthDmaTxDescPtr[BufIdx].\
                                                              TDES3 = TxLength;
/* [cover parentID={907D4DBC-CFD4-434b-B396-A239280B8FF3}]
Checksum Insertion Enabled
[/cover] */
#if ((ETH_17_GETHMAC_IPV4_CHECKSUMOFFLOAD_ENABLE == STD_ON ) || \
     (ETH_17_GETHMAC_TCP_CHECKSUMOFFLOAD_ENABLE  == STD_ON ) || \
     (ETH_17_GETHMAC_UDP_CHECKSUMOFFLOAD_ENABLE  == STD_ON ) || \
     (ETH_17_GETHMAC_ICMP_CHECKSUMOFFLOAD_ENABLE == STD_ON ))
  /* [cover parentID={F3923D2B-635B-4eeb-BA35-B07D22B2F252}]
  Enable Checksum Insertion in Tx descriptor
  (at BufIdx location of Tx descriptor)
  [/cover] */
  /* Enable Checksum Insertion in Tx descriptor.*/
  EthLocalCoreStatusPtr->EthBuffDecPtr->EthDmaTxDescPtr[BufIdx].TDES3 |= \
                                   (uint32)ETH_17_GETHMAC_DMA_TX_DESC_CIC_PSDO;
#endif

  /* [cover parentID={2DF3E59A-3DB2-4eb9-A8EA-57EB373625DF}]
  Update Tx descriptor for fields, packet length, Buffer1 Length
  (as packet length),FD as set, LD as set and OWM bit as set
  [/cover] */
  /*Update Tx descriptor - TDES3, with first descriptor (FD) bit set.*/
  EthLocalCoreStatusPtr->EthBuffDecPtr->EthDmaTxDescPtr[BufIdx].TDES3 |= \
                                     (uint32)ETH_17_GETHMAC_DMA_TX_DESC_FD_SET;

  /*Update Tx descriptor - TDES2.Buffer 1 Length, with Packet length to be
  transmitted*/
  /*Info: Both buffer length in TDES2 and and packet length in TDES3 should
  be same*/

  EthLocalCoreStatusPtr->EthBuffDecPtr->EthDmaTxDescPtr[BufIdx].TDES2 = \
  ((uint32)(EthLocalCoreStatusPtr->EthBuffDecPtr->EthDmaTxDescPtr[BufIdx].\
  TDES2 & ((uint32)ETH_17_GETHMAC_MASK_TDES2_BUF1LENGTH))) | \
                                                          ((uint32)(TxLength));

  /*Update Tx descriptor - TDES3, with last descriptor (LD) bit set.*/
  EthLocalCoreStatusPtr->EthBuffDecPtr->EthDmaTxDescPtr[BufIdx].TDES3 |= \
                                     (uint32)ETH_17_GETHMAC_DMA_TX_DESC_LD_SET;
  /* Release buffer to DMA by setting OWN bit*/
  EthLocalCoreStatusPtr->EthBuffDecPtr->EthDmaTxDescPtr[BufIdx].TDES3 |= \
                                  (uint32)(ETH_17_GETHMAC_DMA_TX_DESC_OWN_SET);
  /* Frame Transmit Request is done*/
  EthLocalCoreStatusPtr->EthBuffDecPtr->EthTxBuffTablePtr[BufIdx].\
                                         FrameTxInitiated = ETH_17_GETHMAC_ONE;

  /* [cover parentID={FB22DBF9-DF07-4698-B0D1-88E70363D443}]
  Issue poll demand command for Channel-0 Tx- DMA
  [/cover] */
  /*Update Tx- DMA-CH0 Descriptor tail pointer to issue poll demand command*/
   /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion pointer to a
     integer type is performed to assign last buffer address to tail pointer
     register. This is the intended design and valid as per DMA hardware
     design. There are no side effects seen by violating this rule.*/
   /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from pointer to unsigned long to
     assign last buffer address to tail pointer register. This is the intended
     design and valid as per DMA hardware design. There are no side effects
     seen by violating this rule.*/
  EthCntrlAdd->DMA_CH[0].TXDESC_TAIL_POINTER.U = \
              (uint32)(&EthLocalCoreStatusPtr->EthBuffDecPtr->\
                         EthDmaTxDescPtr[EthLocalCntrlCfgPtr->EthTxBufTotal]);
  /* [cover parentID={5BC26184-FA27-4508-A82B-87780D780216}]
  If Tx interrupt is enabled
  [/cover] */
  if(IntEnabled == ETH_17_GETHMAC_ONE)
  {
    /* [cover parentID={50ABE9BE-3AF3-40bc-8D34-4A4B62D3A600}]
    Exit critical section
    [/cover] */
    SchM_Exit_Eth_17_GEthMac_TransmitData();
  }
}
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={33763DC2-C2CE-4550-AA93-C4AD6B007084}]  **
**                                                                            **
** Syntax           : static void Eth_17_lResetTxRxStatus(const               **
**                  Eth_17_GEthMac_CoreCntrlConfigType* const EthCntrlCfgPtr) **
**                                                                            **
** Description      : Function to Reset all Tx and Rx status                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : NA                                                      **
**                                                                            **
** Parameters (in)  : EthCntrlCfgPtr- Pointer to ethernet controller          **
**                    configuration.                                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_lResetTxRxStatus(const Eth_17_GEthMac_CoreCntrlConfigType*
                                                          const EthCntrlCfgPtr)
{
  /* Reset interrupt status and mask the interrupt which are
  enabled in default.*/
  Eth_17_lDisableGethInterrupt(EthCntrlCfgPtr);

  /* Keep Tx DMA Descriptors in Init state, hence buffers are released.*/
  Eth_17_lDmaTxDescriptorInit(EthCntrlCfgPtr);

  /* Keep Rx DMA Descriptors in Init state, hence buffers are released.*/
  Eth_17_lDmaRxDescriptorInit(EthCntrlCfgPtr);
}

#if ((ETH_17_GETHMAC_IPV4_CHECKSUMOFFLOAD_ENABLE == STD_ON) || \
     (ETH_17_GETHMAC_TCP_CHECKSUMOFFLOAD_ENABLE  == STD_ON) || \
     (ETH_17_GETHMAC_UDP_CHECKSUMOFFLOAD_ENABLE  == STD_ON) || \
     (ETH_17_GETHMAC_ICMP_CHECKSUMOFFLOAD_ENABLE == STD_ON))
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={8FF95876-09F0-4d74-9286-30DF20EB955C}]  **
**                                                                            **
** Syntax           : static void Eth_17_lCheckForICMPV4Frame(                **
**                                const Eth_BufIdxType BufIdx,                **
**                                const Eth_FrameType FrameType,              **
**              Eth_17_GEthMac_CntrlStatusType * const EthLocalCoreStatusPtr) **
** Description      : This functions checks for ICMP V4 frame type, and       **
**                    replaces the ICMP checksum field of the payload to      **
**                    0x00.Since for ICMP-over-IPv4 packets ETHMAC requires   **
**                    the Checksum field in the ICMP packet to be always      **
**                    16'h0000.If it is not equal to 16'h0000 ,               **
**                    an incorrect checksum may be inserted into the packet.  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : BufIdx - Index of the buffer resource                   **
**                    FrameType- Ethernet frame type                          **
**                    EthLocalCoreStatusPtr- Pointer to Controller Status     **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_lCheckForICMPV4Frame(const Eth_BufIdxType BufIdx,
                                        const Eth_FrameType FrameType,
            const Eth_17_GEthMac_CntrlStatusType * const EthLocalCoreStatusPtr)
{
  uint8* TxBufferAddress;
  /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between integer to a pointer
  type is performed to access the buffer address from DMA descriptor. This is
  the intended design and valid as per DMA hardware design. There are no side
  effects seen by violating this rule.*/
  /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from unsigned long to pointer
  is performed to access the buffer address from DMA descriptor. This is the
  intended design and valid as per DMA hardware design.There are no side
  effects seen by violating this rule.*/
  TxBufferAddress = (uint8*)(EthLocalCoreStatusPtr->EthBuffDecPtr->\
                                               EthDmaTxDescPtr[BufIdx].TDES0);
  if(FrameType == ETH_17_GETHMAC_IPV4_FRAMETYPE)
  {
    if(TxBufferAddress[ETH_17_GETHMAC_FRAME_IPV4TYPE_POS] == \
                  ETH_17_GETHMAC_IPV4_ICMP_PROTOCOL)
    {
      TxBufferAddress[ETH_17_GETHMAC_FRAME_ICMP_CRC_POS] = ETH_17_GETHMAC_ZERO;
      TxBufferAddress[ETH_17_GETHMAC_FRAME_ICMP_CRC_POS+1U] = \
                                                           ETH_17_GETHMAC_ZERO;
    }
  }
}
#endif

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={EC80822D-518E-4103-88EE-1029FB1B2200}]  **
**                                                                            **
** Syntax           : static void Eth_17_lUpdateEthStatisticsCounterValues    **
**                                                                 ( void )   **
**                                                                            **
** Description      : Updates statistics counter values                       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_lUpdateEthStatisticsCounterValues(void)
{
  const Ifx_GETH *EthCntrlAdd;
  uint32    CoreId;
  uint8 ControllerIdx;
  uint8 EthOpMode;
  Eth_17_GEthMac_CntrlStatusType *EthLocalCoreStatusPtr;
  const Eth_17_GEthMac_CoreConfigType *EthLocalCoreCfgPtr;
  const Eth_17_GEthMac_CoreCntrlConfigType *EthLocalCntrlCfgPtr;

  CoreId = Mcal_GetCpuIndex();
  EthLocalCoreCfgPtr = Eth_ConfigSetPtr->EthCoreAdd[CoreId];
  EthLocalCntrlCfgPtr = EthLocalCoreCfgPtr->EthCoreCntrlPtr;
  EthLocalCoreStatusPtr = Eth_CntrlStatus[CoreId];

  /* [cover parentID={54634D7E-5BA4-4fa0-BC09-E26636FF2CA4}]
  Loop until ctrl Idx is less than available controllers
  [/cover] */
  for(ControllerIdx = 0; ControllerIdx < EthLocalCoreCfgPtr->EthMaxControllers;\
                                                               ControllerIdx++)
  {
    /* Get base address of the indexed controller */
    EthCntrlAdd = Eth_GEthMacCntrl[EthLocalCntrlCfgPtr->EthCntrlIdx];
    EthOpMode = (uint8)((EthLocalCntrlCfgPtr->EthCntrlProperties) >> \
                               ETH_17_GETHMAC_OPMODE_POS) & ETH_17_GETHMAC_ONE;
    /* [cover parentID={0E7138E3-4FE6-4abc-B30C-055A9668A326}]
    CRC error is greater than zero
    [/cover] */
    /*Check if number of packets received with CRC error is greater than zero*/
    if((uint32)EthCntrlAdd->RX_CRC_ERROR_PACKETS.B.RXCRCERR > 0U)
    {
      /* Update CRC error Count */
      EthLocalCoreStatusPtr->EthStatisticsCounters.CRCErrorFrameCounter.\
      Count = ((uint32)EthCntrlAdd->RX_CRC_ERROR_PACKETS.B.RXCRCERR) - \
      EthLocalCoreStatusPtr->EthStatisticsCounters.CRCErrorFrameCounter.\
      DemReportedCount;
    }

    /* [cover parentID={F4DD41A5-DAB0-43aa-A27C-A1A1F8395382}]
    Undersize packets greater than zero
    [/cover] */
    /*Check if number of packets received with length less than 64 bytes,without
    any errors, is greater than zero*/
    if((uint32)EthCntrlAdd->RX_UNDERSIZE_PACKETS_GOOD.B.RXUNDERSZG > 0U)
    {
      /* Update undersize good packets Count */
      EthLocalCoreStatusPtr->EthStatisticsCounters.UnderSizeFrameCounter.\
      Count = ((uint32)EthCntrlAdd->RX_UNDERSIZE_PACKETS_GOOD.B.RXUNDERSZG) - \
      EthLocalCoreStatusPtr->EthStatisticsCounters.UnderSizeFrameCounter.\
      DemReportedCount;
    }

    /* [cover parentID={8544B813-C9F5-4783-93E0-856FAEDDAD15}]
    Oversize packets greater than zero
    [/cover] */
    /*Check if number of packets received without errors, with length greater
      than the maxsize,is greater than zero*/

     if((uint32)EthCntrlAdd->RX_OVERSIZE_PACKETS_GOOD.B.RXOVERSZG > 0U)
    {
      /* Update oversize good packets Count */
      EthLocalCoreStatusPtr->EthStatisticsCounters.OverSizeFrameCounter.Count\
      = ((uint32)EthCntrlAdd->RX_OVERSIZE_PACKETS_GOOD.B.RXOVERSZG) - \
      EthLocalCoreStatusPtr->EthStatisticsCounters.OverSizeFrameCounter.\
      DemReportedCount;
    }

    /* [cover parentID={5B1F742A-BEEC-483d-8BA2-BD88EF321734}]
    Alignment error is greater than zero
    [/cover] */
    /*Check if number of packets received with alignment (dribble) error is
    greater than zero
    Info: It is valid only in 10/100 mode */

    if((uint32)EthCntrlAdd->RX_ALIGNMENT_ERROR_PACKETS.B.RXALGNERR > 0U)
    {
      /*Update Alignment Error Count */
      EthLocalCoreStatusPtr->EthStatisticsCounters.AlignmentErrorFrameCounter.\
      Count = ((uint32)EthCntrlAdd->RX_ALIGNMENT_ERROR_PACKETS.B.RXALGNERR) - \
      EthLocalCoreStatusPtr->EthStatisticsCounters.AlignmentErrorFrameCounter.\
      DemReportedCount;
    }
    /* [cover parentID={CBF43F0D-1A1D-4821-A156-44D815551DBF}]
     If OpMode is HALF DUPLEX
    [/cover] */
    if  ( EthOpMode == ETH_17_GETHMAC_HALF_DUPLEX)
    {
      /*Check if number of successfully transmitted packets after a single
        collision is greater than zero
        Info: It is valid only half-duplex mode*/
      /* [cover parentID={489A49CB-7B8B-43d0-87EF-BF9F8F412FCF}]
      [/cover] */
      if((uint32)EthCntrlAdd->TX_SINGLE_COLLISION_GOOD_PACKETS.B.TXSNGLCOLG \
                                                                          > 0U)
      {
        /*Update Single Collision Count */
        EthLocalCoreStatusPtr->EthStatisticsCounters.SingleCollisionCounter.\
        Count = ((uint32)EthCntrlAdd->TX_SINGLE_COLLISION_GOOD_PACKETS.B.\
        TXSNGLCOLG) - EthLocalCoreStatusPtr->EthStatisticsCounters.\
        SingleCollisionCounter.DemReportedCount;
      }

      /*Check if number of successfully transmitted packets after multiple
        collision is greater than zero
        Info: It is valid only half-duplex mode*/
      /* [cover parentID={91FFE8FE-009C-4d33-B08D-77AC082F7973}]
      [/cover] */
      if((uint32)EthCntrlAdd->TX_MULTIPLE_COLLISION_GOOD_PACKETS.B.TXMULTCOLG\
                                                                          > 0U)
      {
        /*Update Multiple Collision Count */
        EthLocalCoreStatusPtr->EthStatisticsCounters.MultipleCollisionCounter.\
        Count = ((uint32)EthCntrlAdd->TX_MULTIPLE_COLLISION_GOOD_PACKETS.B.\
        TXMULTCOLG)- EthLocalCoreStatusPtr->EthStatisticsCounters.\
        MultipleCollisionCounter.DemReportedCount;
      }
      /*Check if number of packets aborted because of late collision error
        is greater than zero
        Info: It is valid only half-duplex mode*/
      /* [cover parentID={EC85207F-C314-4c79-BB74-48F0FFEF673A}]
      [/cover] */
      if((uint32)EthCntrlAdd->TX_LATE_COLLISION_PACKETS.B.TXLATECOL > 0U)
      {
        /*Update Late Collision Count */
        EthLocalCoreStatusPtr->EthStatisticsCounters.LateCollisionCounter.\
        Count = ((uint32)EthCntrlAdd->TX_LATE_COLLISION_PACKETS.B.TXLATECOL) - \
        EthLocalCoreStatusPtr->EthStatisticsCounters.LateCollisionCounter.\
        DemReportedCount;
      }
    }
    /* [cover parentID={E3802933-B6F9-4155-B3EA-9BE21FE177D2}]
    Increment the pointers to check for the next controller
    [/cover] */
    EthLocalCntrlCfgPtr++;
    EthLocalCoreStatusPtr++;
  }
}

/*******************************************************************************
**                        Functions for Production error Report               **
*******************************************************************************/

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={FD8792F8-A0EB-4644-8388-A02C910D14D7}]  **
**                                                                            **
** Syntax           : static void Eth_17_lDemReportStatisticsCounterValues    **
**                                                                   (void)   **
**                                                                            **
** Description      : Raise Production error for Statistics Counter values    **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_lDemReportStatisticsCounterValues(void)
{
  uint32 MissPackOverflowCnt;
  uint32 OverflowCnt;
  uint32 TotalOverMissCnt;
  const Ifx_GETH *EthCntrlAdd;
  uint32    CoreId;
  uint8 ControllerIdx;
  Eth_17_GEthMac_CntrlStatusType *EthLocalCoreStatusPtr;
  const Eth_17_GEthMac_CoreConfigType *EthLocalCoreCfgPtr;
  const Eth_17_GEthMac_CoreCntrlConfigType *EthLocalCntrlCfgPtr;
  uint8 EthOpMode;

  CoreId = Mcal_GetCpuIndex();
  EthLocalCoreCfgPtr = Eth_ConfigSetPtr->EthCoreAdd[CoreId];
  EthLocalCntrlCfgPtr = EthLocalCoreCfgPtr->EthCoreCntrlPtr;
  EthLocalCoreStatusPtr = Eth_CntrlStatus[CoreId];
  /* [cover parentID={3D1A1C87-82C2-494d-BDCB-9D4A60A361B2}]
  [/cover] */
  for(ControllerIdx = 0; ControllerIdx < EthLocalCoreCfgPtr->EthMaxControllers;\
                                                               ControllerIdx++)
  {
    EthOpMode = (uint8)((EthLocalCntrlCfgPtr->EthCntrlProperties) >> \
                                ETH_17_GETHMAC_OPMODE_POS) & ETH_17_GETHMAC_ONE;
    /* Get base address of the indexed controller */
    EthCntrlAdd = Eth_GEthMacCntrl[EthLocalCntrlCfgPtr->EthCntrlIdx];
    /*--Reporting of ETH_E_RX_FRAMES_LOST
    This counter is addition of( from Q0),
    number of packes DMA discards because of buffer unavailability and
    number of packets discarded because of Receive queue overflow.
    Info: Counter Clears on register read.*/
    MissPackOverflowCnt = EthCntrlAdd->MTL_RXQ0.MISSED_PACKET_OVERFLOW_CNT.U;

    OverflowCnt = (uint32)(MissPackOverflowCnt & ETH_17_GETHMAC_OVFPKTCNT_MASK);
    TotalOverMissCnt  = (OverflowCnt + \
           ((uint32)((MissPackOverflowCnt & ETH_17_GETHMAC_MISPKTCNT_MASK) >> \
                                           ETH_17_GETHMAC_MISPKTCNT_POSITION)));
    /* [cover parentID={A444F2D2-44D4-40f6-9307-22BC73CD12C7}]
    [/cover] */
    if(TotalOverMissCnt > ETH_17_GETHMAC_ZERO)
    {
      if(EthLocalCntrlCfgPtr->EthDemFramesLost !=\
                                             ETH_17_GETHMAC_DISABLE_DEM_REPORT)
      {
        /*Production error should be reported only if Production error has
        been enabled */
        /* [cover parentID={EFEA775C-032E-4a38-8CC3-2A5A108BA384}]
        [/cover] */
        Mcal_Wrapper_Dem_ReportErrorStatus(
        EthLocalCntrlCfgPtr->EthDemFramesLost, DEM_EVENT_STATUS_PREFAILED);
      }
    }
    /* [cover parentID={3BBB78EC-162C-4891-858A-57A2C85AB079}]
    [/cover] */
    /*--Reporting of ETH_E_CRC */
    if(EthLocalCoreStatusPtr->EthStatisticsCounters.\
                              CRCErrorFrameCounter.Count > ETH_17_GETHMAC_ZERO)
    {
      if(EthLocalCntrlCfgPtr->EthDemCRC != ETH_17_GETHMAC_DISABLE_DEM_REPORT)
      {
        /*Production error should be reported only if Production error
        has been enabled */
        /* [cover parentID={5B4B2658-1A04-4c62-92C8-9FCF5E60799D}]
        [/cover] */
        Mcal_Wrapper_Dem_ReportErrorStatus(EthLocalCntrlCfgPtr->EthDemCRC,
                                           DEM_EVENT_STATUS_PREFAILED);
        EthLocalCoreStatusPtr->EthStatisticsCounters.CRCErrorFrameCounter.\
        DemReportedCount = EthLocalCoreStatusPtr->EthStatisticsCounters.\
        CRCErrorFrameCounter.DemReportedCount + \
        EthLocalCoreStatusPtr->EthStatisticsCounters.\
        CRCErrorFrameCounter.Count;
      }
    }
    /* [cover parentID={E10DEBA4-4500-4fbd-BC10-3B93CA3DED7F}]
    [/cover] */
    /*--Reporting of ETH_E_UNDERSIZEFRAME*/
    if(EthLocalCoreStatusPtr->EthStatisticsCounters.\
                             UnderSizeFrameCounter.Count > ETH_17_GETHMAC_ZERO)
    {
      if(EthLocalCntrlCfgPtr->EthDemUndersize !=\
                                             ETH_17_GETHMAC_DISABLE_DEM_REPORT)
      {
        /*Production error should be reported only if Production error
        has been enabled  */
        /* [cover parentID={FCBCD27E-FE77-4bd4-A5B7-1E9A7DA941C1}]
        [/cover] */
        Mcal_Wrapper_Dem_ReportErrorStatus(
        EthLocalCntrlCfgPtr->EthDemUndersize, DEM_EVENT_STATUS_PREFAILED);
        EthLocalCoreStatusPtr->EthStatisticsCounters.UnderSizeFrameCounter.\
        DemReportedCount = EthLocalCoreStatusPtr->EthStatisticsCounters.\
        UnderSizeFrameCounter.DemReportedCount + EthLocalCoreStatusPtr->\
        EthStatisticsCounters.UnderSizeFrameCounter.Count;
      }
    }

    /* [cover parentID={9F61391A-CD03-48b0-BDD2-C5FDBFAEC556}]
    [/cover] */
    /*--Reporting of ETH_E_OVERSIZEFRAME*/
    if(EthLocalCoreStatusPtr->EthStatisticsCounters.OverSizeFrameCounter.\
                                                   Count > ETH_17_GETHMAC_ZERO)
    {
      if(EthLocalCntrlCfgPtr->EthDemOversize != \
                                             ETH_17_GETHMAC_DISABLE_DEM_REPORT)
      {
        /*Production error should be reported only if Production error
        has been enabled */
        /* [cover parentID={B0F8064C-4031-4862-94C2-E522849182B1}]
        [/cover] */
        Mcal_Wrapper_Dem_ReportErrorStatus(EthLocalCntrlCfgPtr->EthDemOversize,
                                              DEM_EVENT_STATUS_PREFAILED);
        EthLocalCoreStatusPtr->EthStatisticsCounters.OverSizeFrameCounter.\
        DemReportedCount = EthLocalCoreStatusPtr->EthStatisticsCounters.\
        OverSizeFrameCounter.DemReportedCount + EthLocalCoreStatusPtr->\
        EthStatisticsCounters.OverSizeFrameCounter.Count;
      }
    }
    /*--Reporting of ETH_E_ALIGNMENT*/
    /* [cover parentID={61BB5702-5E0D-41c0-BDA7-80FB0AABF235}]
      [/cover] */
    if(EthLocalCoreStatusPtr->EthStatisticsCounters.\
                        AlignmentErrorFrameCounter.Count > ETH_17_GETHMAC_ZERO)
    {
      if(EthLocalCntrlCfgPtr->EthDemAlignment != \
                                             ETH_17_GETHMAC_DISABLE_DEM_REPORT)
      {
        /*Production error should be reported only if Production error
        has been enabled */
        /* [cover parentID={66A29613-5CF8-4d9c-AE82-FC09772A1CA2}]
        [/cover] */
        Mcal_Wrapper_Dem_ReportErrorStatus(
        EthLocalCntrlCfgPtr->EthDemAlignment, DEM_EVENT_STATUS_PREFAILED);
        EthLocalCoreStatusPtr->EthStatisticsCounters.\
        AlignmentErrorFrameCounter.DemReportedCount = EthLocalCoreStatusPtr->\
        EthStatisticsCounters.AlignmentErrorFrameCounter.DemReportedCount + \
        EthLocalCoreStatusPtr->EthStatisticsCounters.\
        AlignmentErrorFrameCounter.Count;
      }
    }
    /* [cover parentID={F9C5713C-C77B-4643-A2C9-61F3B694E250}]
    [/cover] */
    if(EthOpMode == ETH_17_GETHMAC_HALF_DUPLEX)
    {
      /* [cover parentID={9F79117E-1B12-486f-AF70-954232474C47}]
      [/cover] */
      Eth_17_lDemReportHalfDuplStatCountValues(EthLocalCntrlCfgPtr,\
                                                        EthLocalCoreStatusPtr);
    }
    /* [cover parentID={33C63553-0190-44bc-B34E-CB08B7BCD5A3}]
    Increment the pointers to check for the next controller
    [/cover] */
    EthLocalCntrlCfgPtr++;
    EthLocalCoreStatusPtr++;
  }
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={ADA21D3E-620C-4787-8609-24BE1B7563D2}]  **
**                                                                            **
** Syntax           : static void Eth_17_lDemReportHalfDuplStatCountValues    **
**                    (const Eth_17_GEthMac_CoreCntrlConfigType*              **
**                    const EthCntrlCfgPtr Eth_17_GEthMac_CntrlStatusType *   **
**                    const EthLocalCoreStatusPtr)                            **
**                                                                            **
** Description      : Raise Production error for Half Duplex Statistics       **
**                    Counter values                                          **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_lDemReportHalfDuplStatCountValues(const
                    Eth_17_GEthMac_CoreCntrlConfigType* const EthCntrlCfgPtr
                  ,Eth_17_GEthMac_CntrlStatusType * const EthLocalCoreStatusPtr)
{

    /* [cover parentID={0F673C1A-D673-46e3-B315-3A9C6E8DBFFD}]
    If Single collision count > 0 and Production error is enabled
    [/cover] */
    if(EthLocalCoreStatusPtr->EthStatisticsCounters.SingleCollisionCounter.\
                                                   Count > ETH_17_GETHMAC_ZERO)
    {
      if(EthCntrlCfgPtr->EthDemSingleCollision != \
                                        ETH_17_GETHMAC_DISABLE_DEM_REPORT)
      {
        /*Production error should be reported only if Production error has
        been enabled  */
        /* [cover parentID={AF99EA20-ED3F-4845-A346-65BE4E4203CF}]
        Report ETH_E_SINGLECOLLISION
        [/cover] */
        Mcal_Wrapper_Dem_ReportErrorStatus(
        EthCntrlCfgPtr->EthDemSingleCollision, DEM_EVENT_STATUS_PREFAILED);
        EthLocalCoreStatusPtr->EthStatisticsCounters.SingleCollisionCounter.\
        DemReportedCount = EthLocalCoreStatusPtr->EthStatisticsCounters.\
        SingleCollisionCounter.DemReportedCount + \
        EthLocalCoreStatusPtr->EthStatisticsCounters.\
        SingleCollisionCounter.Count;
      }
    }
    /* [cover parentID={55EF52F0-E134-45b8-AC4E-AF658F126CE7}]
    Multiple collision count > 0 and Production error is enabled
    [/cover] */
    /*--Reporting of ETH_E_MULTIPLECOLLISION*/
    if(EthLocalCoreStatusPtr->EthStatisticsCounters.\
                          MultipleCollisionCounter.Count > ETH_17_GETHMAC_ZERO)
    {
      if(EthCntrlCfgPtr->EthDemMultipleCollision != \
                                         ETH_17_GETHMAC_DISABLE_DEM_REPORT)
      {
        /*Production error should be reported only if Production error
        has been enabled */
        /* [cover parentID={020E420A-4FA6-43af-A690-816D805AD7D2}]
        Report ETH_E_MULTIPLECOLLISION
        [/cover] */
        Mcal_Wrapper_Dem_ReportErrorStatus(
        EthCntrlCfgPtr->EthDemMultipleCollision, DEM_EVENT_STATUS_PREFAILED);
        EthLocalCoreStatusPtr->EthStatisticsCounters.\
        MultipleCollisionCounter.DemReportedCount = \
        EthLocalCoreStatusPtr->EthStatisticsCounters.MultipleCollisionCounter.\
        DemReportedCount + EthLocalCoreStatusPtr->EthStatisticsCounters.\
        MultipleCollisionCounter.Count;
      }
    }
    /* [cover parentID={9254279D-EF9A-461b-BC47-172EDEEF1FA6}]
    Late collision count > 0 and Production error is enabled
    [/cover] */
    /*--Reporting of ETH_E_LATECOLLISION*/
    if(EthLocalCoreStatusPtr->EthStatisticsCounters.LateCollisionCounter.\
                                                   Count > ETH_17_GETHMAC_ZERO)
    {
      if(EthCntrlCfgPtr->EthDemLateCollision != \
                                      ETH_17_GETHMAC_DISABLE_DEM_REPORT)
      {
        /*Production error should be reported only if Production error has
        been enabled */
        /* [cover parentID={DAA0CBD5-CEB0-4c5a-A52D-35A1851E4046}]
        Report ETH_E_LATECOLLISION
        [/cover] */
        Mcal_Wrapper_Dem_ReportErrorStatus(EthCntrlCfgPtr->EthDemLateCollision,
                                              DEM_EVENT_STATUS_PREFAILED);
        EthLocalCoreStatusPtr->EthStatisticsCounters.LateCollisionCounter.\
        DemReportedCount = EthLocalCoreStatusPtr->EthStatisticsCounters.\
        LateCollisionCounter.DemReportedCount + EthLocalCoreStatusPtr->\
        EthStatisticsCounters.LateCollisionCounter.Count;
      }
    }
}
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={CF73E008-4955-425a-8379-7AA0BCC8C9A0}]  **
**                                                                            **
** Syntax           : static void Eth_17_lDemReportAllErrorPass(const         **
**                  Eth_17_GEthMac_CoreCntrlConfigType* const EthCntrlCfgPtr) **
**                                                                            **
** Description      : Report all Production errors as Pass to Mcal_Wrapper    **
**                    module                                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non- Reentrant                                          **
**                                                                            **
** Parameters (in)  : EthCntrlCfgPtr- Pointer to ethernet Controller          **
**                    Configuration.                                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_lDemReportAllErrorPass(const
                      Eth_17_GEthMac_CoreCntrlConfigType* const EthCntrlCfgPtr)
{
  /* [cover parentID={8EEA15C8-16BC-491e-9330-3C38B70CD269}]
  If DEM id for corresponding Production error is enabled
  [/cover] */
  /* [cover parentID={74AB6821-C064-4141-84B3-30CAED0B51FE}]
  Report Production error as DEM_EVENT_STATUS_PREPASSED ( except for
  ETH_E_ACCESS)
  [/cover] */
  if(EthCntrlCfgPtr->EthDemFramesLost != ETH_17_GETHMAC_DISABLE_DEM_REPORT)
  {
    Mcal_Wrapper_Dem_ReportErrorStatus(EthCntrlCfgPtr->EthDemFramesLost,
                                             DEM_EVENT_STATUS_PREPASSED);
  }

  if(EthCntrlCfgPtr->EthDemCRC != ETH_17_GETHMAC_DISABLE_DEM_REPORT)
  {
    Mcal_Wrapper_Dem_ReportErrorStatus(EthCntrlCfgPtr->EthDemCRC,
                                            DEM_EVENT_STATUS_PREPASSED);
  }

  if(EthCntrlCfgPtr->EthDemUndersize != ETH_17_GETHMAC_DISABLE_DEM_REPORT)
  {
    Mcal_Wrapper_Dem_ReportErrorStatus(EthCntrlCfgPtr->EthDemUndersize,
                                            DEM_EVENT_STATUS_PREPASSED);
  }

  if(EthCntrlCfgPtr->EthDemOversize != ETH_17_GETHMAC_DISABLE_DEM_REPORT)
  {
    Mcal_Wrapper_Dem_ReportErrorStatus(EthCntrlCfgPtr->EthDemOversize,
                                           DEM_EVENT_STATUS_PREPASSED);
  }

  if(EthCntrlCfgPtr->EthDemAlignment != ETH_17_GETHMAC_DISABLE_DEM_REPORT)
  {
    Mcal_Wrapper_Dem_ReportErrorStatus(EthCntrlCfgPtr->EthDemAlignment,
                                         DEM_EVENT_STATUS_PREPASSED);
  }
  /* [cover parentID={F8ADF8B9-C0AD-48d2-B927-C76B45107C1C}]
  If DEM id for corresponding Production error of Half Duplex  is enabled
  [/cover] */
  /* [cover parentID={EBE38236-8D9E-40dd-B421-59C776040A98}]
  Report corresponding Production error as DEM_EVENT_STATUS_PREPASSED
  [/cover] */
  if(EthCntrlCfgPtr->EthDemSingleCollision != \
                                         ETH_17_GETHMAC_DISABLE_DEM_REPORT)
  {
    Mcal_Wrapper_Dem_ReportErrorStatus(EthCntrlCfgPtr->EthDemSingleCollision,
                                                DEM_EVENT_STATUS_PREPASSED);
  }

  if(EthCntrlCfgPtr->EthDemMultipleCollision != \
                                         ETH_17_GETHMAC_DISABLE_DEM_REPORT)
  {
    Mcal_Wrapper_Dem_ReportErrorStatus(EthCntrlCfgPtr->EthDemMultipleCollision,
                                               DEM_EVENT_STATUS_PREPASSED);
  }

  if(EthCntrlCfgPtr->EthDemLateCollision != \
                                         ETH_17_GETHMAC_DISABLE_DEM_REPORT)
  {
    Mcal_Wrapper_Dem_ReportErrorStatus(EthCntrlCfgPtr->EthDemLateCollision,
                                              DEM_EVENT_STATUS_PREPASSED);
  }
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={EA44AB9D-40F4-4f19-AE4B-A5CEFF119ED2}]  **
**                                                                            **
** Syntax           : static boolean Eth_17_lDemtimeout                       **
**                    (const uint32 Timeout, ,const Dem_EventIdType           **
**                                                          EthDemAccess)     **
**                                                                            **
** Description      : Report Hardware Access Production error if timeout      **
**                    happened                                                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : Timeout - Timeout occured status                        **
**                    EthDemAccess - Production error Enable/Disable Status   **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : TRUE  - Timeout happend                                 **
**                    FALSE - Timeout not happend                             **
**                                                                            **
*******************************************************************************/
static boolean Eth_17_lDemtimeout(const boolean Timeout,const Dem_EventIdType
                                                                  EthDemAccess)
{
  boolean RetVal = FALSE;
  /* [cover parentID={7D1DFC4F-A16E-41a7-8B0A-E0223AF54AEE}]
  Detect timeout condition and report Production error
  [/cover] */
  /* Check if timeout happened */
  if(Timeout == TRUE)
  {
    /* Set Return value TRUE, it means timeout happened*/
    RetVal=TRUE;
    /* [cover parentID={7D1DFC4F-A16E-41a7-8B0A-E0223AF54AEE}]
    Detect timeout condition and report Production error
    [/cover] */
    /* Report DEM_E_ACCESS error */
    if(EthDemAccess != ETH_17_GETHMAC_DISABLE_DEM_REPORT)
    {
      /*Production error should be reported only if Production error has been
      enabled  */
      /* [cover parentID={54565432-2DD7-40b8-BDA0-60341CA1EDEA}]
      [/cover] */
      Mcal_Wrapper_Dem_ReportErrorStatus(EthDemAccess,
                                         DEM_EVENT_STATUS_PREFAILED);
    }
  }
return RetVal;
}

/*******************************************************************************
**                        Functions for DET checks                            **
*******************************************************************************/
#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={589E378C-D60C-4b55-A130-1FFC9EB9117E}]  **
**                                                                            **
** Syntax           : static uint32 Eth_17_lDetCheckInvalidPointer            **
**                             (const void * const Ptr,const uint8 ServiceId) **
**                                                                            **
** Description      : DET check for ETH_17_GETHMAC_E_PARAM_POINTER            **
**                    This local API is required only if DET is enabled       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Ptr- Pointer to be checked                              **
**                    ServiceId- ServiceId of API                             **
**                                                                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : ETH_17_GETHMAC_E_DET_NO_ERR     - Valid pointer         **
**                    ETH_17_GETHMAC_E_PARAM_POINTER  - NULL pointer          **
**                                                                            **
*******************************************************************************/
static uint32 Eth_17_lDetCheckInvalidPointer( const void* const Ptr,
                                                         const uint8 ServiceId)
{
  uint8 DevError;
  /* [cover parentID={CB82EEF3-AAC2-49a9-A26B-EBA49E298EB6}][/cover] */
  DevError = ETH_17_GETHMAC_E_DET_NO_ERR;
  /* [cover parentID={AA38CCB7-70F1-4786-9683-09E09281E629}]
  If input parameter is NULL
  [/cover] */
  if(Ptr == NULL_PTR)
  {
    DevError = ETH_17_GETHMAC_E_PARAM_POINTER;
    /* [cover parentID={14AA83E1-9A7C-4abd-9270-3EA32335B835}]
    Report DET as Invalid Pointer with Service ID
    [/cover] */
    (void)Det_ReportError(ETH_17_GETHMAC_MODULE_ID, ETH_17_GETHMAC_INSTANCE_ID,
                    ServiceId, DevError);
  }
  return DevError;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={435B5E18-1302-4c29-9BD1-8FECAC6CB1FF}]  **
**                                                                            **
** Syntax           : static uint32 Eth_17_lDetCheckInvalidCtrlIdx            **
**                                     (const uint8 CtrlIdx,                  **
**                                      const uint8 ServiceId)                **
**                                                                            **
** Description      : DET check for ETH_17_GETHMAC_E_INV_CTRL_IDX             **
**                    This local API is required only if DET is enabled       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlIdx- Controller Index to be checked                 **
**                    ServiceId- ServiceId of API                             **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : ETH_17_GETHMAC_E_DET_NO_ERR   - Valid controller index  **
**                    ETH_17_GETHMAC_E_INV_CTRL_IDX - Invalid controller index**
**                                                                            **
*******************************************************************************/
static uint32 Eth_17_lDetCheckInvalidCtrlIdx(const uint8 CtrlIdx,
                                                        const uint8 ServiceId)
{
  uint32 DevError;
  const Eth_17_GEthMac_CoreConfigType *EthLocalCoreCfgPtr;
  const Eth_17_GEthMac_CoreCntrlConfigType *EthLocalCntrlCfgPtr;
  uint8                          CoreCntrlIdx;
  uint32 CoreId;
  CoreId = Mcal_GetCpuIndex();
  DevError = ETH_17_GETHMAC_E_DET_NO_ERR;
  /* [cover parentID={8A063D35-E922-44d7-95F4-546665E8661C}]
  If Controller Index is greater or equal to max controllers
  [/cover] */
  /* Check if controller index greater than max controller */
  if (CtrlIdx >= ETH_17_GETHMAC_MAX_CONTROLLERS)
  {
    /* [cover parentID={E26F2C86-E1EC-4909-85AA-C695A093F4D1}]
    Report DET as Invalid Controller Index with Service ID
    [/cover] */
    (void)Det_ReportError(ETH_17_GETHMAC_MODULE_ID, ETH_17_GETHMAC_INSTANCE_ID,
                    ServiceId, ETH_17_GETHMAC_E_INV_CTRL_IDX);
    DevError = ETH_17_GETHMAC_E_INV_CTRL_IDX;
  }
  /* [cover parentID={2128F8E2-CE21-4f86-BA60-9DECE59C8F24}]
  If Ctrl Idx is Valid
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    EthLocalCoreCfgPtr = Eth_ConfigSetPtr->EthCoreAdd[CoreId];
    CoreCntrlIdx = Eth_ConfigSetPtr->EthNodeIdxmapPtr[CtrlIdx];
    /* [cover parentID={CF0C9B99-ECDD-4515-8FAD-61322A8D64F7}]
    If Ctrl Idx is greater than what is allocated to the current core
    [/cover] */
    if (CoreCntrlIdx >= EthLocalCoreCfgPtr->EthMaxControllers)
    {
      /* [cover parentID={5223072A-D4F2-4e9c-B305-6826F2D6ABE0}]
      Report DET as Controller Index is not allocated to current core
      [/cover] */
      (void)Det_ReportError(ETH_17_GETHMAC_MODULE_ID,ETH_17_GETHMAC_INSTANCE_ID,
                      ServiceId, ETH_17_GETHMAC_E_INV_CTRL_IDX);
      DevError = ETH_17_GETHMAC_E_INV_CTRL_IDX;
    }
    /* [cover parentID={C9A34F3F-22B5-4251-8209-560E690C1DDB}]
    If NO DET
    [/cover] */
    if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
    {
      EthLocalCntrlCfgPtr = EthLocalCoreCfgPtr->EthCoreCntrlPtr;
      EthLocalCntrlCfgPtr = &(EthLocalCntrlCfgPtr[CoreCntrlIdx]);
      /* [cover parentID={C141A3E1-52F5-4b8e-848E-76D16FA350E6}]
      If the controller index is valid but not allocated to the current core
      [/cover] */
      if(EthLocalCntrlCfgPtr->EthCntrlIdx != CtrlIdx)
      {
        /* [cover parentID={C4AFB0F6-EFC9-4499-80DC-8BEB50003BA5}]
        Report DET as Controller Index is not allocated to current core
        [/cover] */
        (void)Det_ReportError(ETH_17_GETHMAC_MODULE_ID,
          ETH_17_GETHMAC_INSTANCE_ID, ServiceId, ETH_17_GETHMAC_E_INV_CTRL_IDX);
        DevError = ETH_17_GETHMAC_E_INV_CTRL_IDX;
      }
    }
  }
  return DevError ;
}
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={E50A2320-50E2-440d-B967-49D184E00737}]  **
**                                                                            **
** Syntax : static uint8 Eth_17_lInitDetCheck                                 **
**                            (const Eth_17_GEthMac_ConfigType * const        **
**                            DetConfigPtr, const uint32 CoreId)              **
** [/cover]                                                                   **
** Service ID:        none                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Reentrant                                               **
**                                                                            **
** Parameters (in):   DetConfigPtr - Pointer to configuration set             **
**                    CoreId : Core Number                                    **
**                                                                            **
** Parameters (out):  none                                                    **
**                                                                            **
** Return value:      ErrorFlag (uint32)                                      **
**                                                                            **
** Description :      Local function :Service for DET check in Ethernet Init  **
**                                    function                                **
**                                                                            **
** Traceability:                                                              **
******************************************************************************/
static uint32 Eth_17_lInitDetCheck( const Eth_17_GEthMac_ConfigType * const
                                             DetConfigPtr, const uint32 CoreId)
{
  uint32 DevError = ETH_17_GETHMAC_E_DET_NO_ERR;
  #if (ETH_17_GETHMAC_MULTICORE_ERROR_DETECT == STD_ON)
  const Eth_17_GEthMac_CoreConfigType *EthLocalCoreCfgPtr;
  #endif
  /* [cover parentID={D62FF3D3-3DD3-4e53-8364-21BD3617D8D6}]
    If Config Ptr is NULL
    [/cover] */
  if(DetConfigPtr == NULL_PTR)
  {
    DevError = ETH_17_GETHMAC_E_INIT_FAILED;
    /* [cover parentID={F1824725-D255-4d1d-9FC6-E4F8D8CE9441}]
    Report DET
    [/cover] */
    (void)Det_ReportError(ETH_17_GETHMAC_MODULE_ID, ETH_17_GETHMAC_INSTANCE_ID,
    ETH_17_GETHMAC_SID_INIT,(uint8)DevError);
  }
#if (ETH_17_GETHMAC_MULTICORE_ERROR_DETECT == STD_ON)
  /* [cover parentID={7BB67B6B-45D9-4282-AB80-C4809C72EBC0}]
  If no DET
  [/cover] */
  if(DevError == ETH_17_GETHMAC_E_DET_NO_ERR)
  {
    /* Report DET -
    Init failed as No controller is configured to current core*/
    EthLocalCoreCfgPtr = DetConfigPtr->EthCoreAdd[CoreId];
    /* [cover parentID={7BB67B6B-45D9-4282-AB80-C4809C72EBC0}]
    If controller is configured to current core
    [/cover] */
    if(EthLocalCoreCfgPtr == NULL_PTR)
    {
      DevError = ETH_17_GETHMAC_E_CORE_NOT_CONFIGURED;
      /* [cover parentID={5843BBDB-0F75-4924-BD84-E0061367E45A}]
      Report DET
      [/cover] */
      (void)Det_ReportError(ETH_17_GETHMAC_MODULE_ID,ETH_17_GETHMAC_INSTANCE_ID,
      ETH_17_GETHMAC_SID_INIT,(uint8)DevError);
    }
   /* [cover parentID={92B6D0B9-DC2C-4ae7-B6B4-E2ACBA2F5030}]
   No DETs
   [/cover] */
  }
#else
   UNUSED_PARAMETER(CoreId);
#endif
return DevError;
}
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={99C34B60-0FD9-40ba-A2D7-40A5360101AB}]  **
**                                                                            **
** Syntax           : static uint32 Eth_17_lDetCheckNoInit                    **
**                                 (const uint8 ServiceIdconst uint8 CtrlIdx) **
**                                                                            **
** Description      : DET check for ETH_17_GETHMAC_E_NOT_INITIALIZED          **
**                    This local API is required only if DET is enabled       **
**                    This local API is verifies if the controller init       **
**                      is successful                                         **
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
** Parameters (in)  : ServiceId- ServiceId of API                             **
**                                                                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : ETH_17_GETHMAC_E_DET_NO_ERR       - Init is sucessful   **
**                    ETH_17_GETHMAC_E_NOT_INITIALIZED  - Init is failed      **
**                                                                            **
*******************************************************************************/
static uint32 Eth_17_lDetCheckNoInit(const uint8 ServiceId, const uint8 CtrlIdx)
{
  uint32 DevError;
  const Eth_17_GEthMac_CntrlStatusType *EthLocalCoreStatusPtr;
  DevError = ETH_17_GETHMAC_E_DET_NO_ERR;
  /* Get controller status */
  EthLocalCoreStatusPtr = Eth_17_lGetCtrlStatusPtr(CtrlIdx);
  /* [cover parentID={CD7EEE43-3631-4919-A8D2-98885BF51D31}]
  If controller initialization was successful
  [/cover] */
  /* Check if Eth_17_GEthMac_SetControllerMode API is called and controller
  initialization was successful. */
  if(EthLocalCoreStatusPtr->EthRunTimeOpertnData.CntrlConfigStatus == \
                                      ETH_17_GETHMAC_CNTRL_NOT_INITIALIZED)
  {
    DevError = ETH_17_GETHMAC_E_NOT_INITIALIZED;
    /* [cover parentID={99D70C1B-524F-41a2-A73D-4D260397B183}]
    Report DET as Not Initialized with Service ID
    [/cover] */
    (void)Det_ReportError(ETH_17_GETHMAC_MODULE_ID, ETH_17_GETHMAC_INSTANCE_ID,
                    ServiceId, ETH_17_GETHMAC_E_NOT_INITIALIZED);
  }
return DevError;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={4AC0BD3C-F141-42da-9E54-56531586B896}]  **
**                                                                            **
** Syntax           : static uint32 Eth_17_lDetCheckNoInitStage1              **
**                    (const uint8 ServiceId)                                 **
**                                                                            **
** Description      : DET check for Eth_Init is successfully executed         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : ServiceId - Service ID of API                           **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : ETH_17_GETHMAC_E_DET_NO_ERR  - Init Stage1 is success   **
**                    ETH_17_GETHMAC_E_NOT_INITIALIZED - No Init Stage1 Error **
**                                                                            **
*******************************************************************************/
static uint32 Eth_17_lDetCheckNoInitStage1(const uint8 ServiceId)
{
  uint32 DevError;
  uint32 CoreId;
  CoreId = Mcal_GetCpuIndex();
  DevError = ETH_17_GETHMAC_E_DET_NO_ERR;
  /*Check if the controller is configured to the core*/
  /* [cover parentID={9A27B7FA-A54C-4d96-9A81-DFAEA4C3608E}]
  [/cover] */
  if(Eth_17_GEthMac_CoreInitStatus[CoreId]!= NULL_PTR)
  {
  /* [cover parentID={D14D9690-AEDC-44bb-A7CC-F3A693DC6BA3}]
  Eth_Init is not successfully executed before
  [/cover] */
  /* Check if Eth_Init is successfully executed before */
  if(*(Eth_17_GEthMac_CoreInitStatus[CoreId]) !=
                                        (uint32)ETH_17_GETHMAC_CORE_INIT)
    {
      DevError = ETH_17_GETHMAC_E_NOT_INITIALIZED;
      /* [cover parentID={64F7A3FE-81F6-4f66-ADCA-AB6F63A14D48}]
      Report DET
      [/cover] */
      (void)Det_ReportError(ETH_17_GETHMAC_MODULE_ID,ETH_17_GETHMAC_INSTANCE_ID,
                    ServiceId, ETH_17_GETHMAC_E_NOT_INITIALIZED);
    }
  }
  else
  {
    DevError = ETH_17_GETHMAC_E_NOT_INITIALIZED;
    /* [cover parentID={52D2F092-36A3-4cfd-A3D5-F99A49492B4B}]
    Report DET
    [/cover] */
    (void)Det_ReportError(ETH_17_GETHMAC_MODULE_ID, ETH_17_GETHMAC_INSTANCE_ID,
                    ServiceId, ETH_17_GETHMAC_E_NOT_INITIALIZED);
  }
  return DevError;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={DDD68CA6-3943-47b3-A571-53B6368DC2E6}]  **
**                                                                            **
** Syntax           : static uint32 Eth_17_lDetCheckInvalidMode               **
**                                             (const Eth_ModeType CtrlMode)  **
**                                                                            **
** Description      : DET check for the paramter CtrlMode is valid            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : CtrlMode - Controller Mode                              **
**                                                                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : ETH_17_GETHMAC_E_DET_NO_ERR - CtrlMode param is valid   **
**                    ETH_17_GETHMAC_E_INV_PARAM  - CtrlMode param is invalid **
**                                                                            **
*******************************************************************************/
static uint32 Eth_17_lDetCheckInvalidMode(const Eth_ModeType CtrlMode)
{
  uint32 DevError;
  DevError = ETH_17_GETHMAC_E_DET_NO_ERR;

  /* [cover parentID={0E5A5758-8223-41c9-9A0B-3E9CCD60AADA}]
  Paramter CtrlMode is valid .
  That is CtrlMode != ETH_MODE_ACTIVE  &&  CtrlMode != ETH_MODE_DOWN
  [/cover] */
  /* Check the paramter CtrlMode is valid */
  if((CtrlMode != ETH_MODE_ACTIVE) && (CtrlMode != ETH_MODE_DOWN))
  {
    DevError = ETH_17_GETHMAC_E_INV_PARAM;
    /* [cover parentID={C7D1BA6A-E7A0-415c-AB22-B356E3FCCBFC}]
    Report DET as Invalid Parameter with Service ID of SetControllerMode API
    [/cover] */
    (void)Det_ReportError(ETH_17_GETHMAC_MODULE_ID, ETH_17_GETHMAC_INSTANCE_ID,
               ETH_17_GETHMAC_SID_SETCONTROLLERMODE,ETH_17_GETHMAC_E_INV_PARAM);
  }
  return DevError;
}
#endif /*ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON*/
/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={74147D45-9688-4e90-B8FF-2EDD8F387D96}]  **
**                                                                            **
** Syntax           : static uint32 Eth_17_lDetCheckMode                      **
**                               (const uint8 ServiceId, const uint8 CtrlIdx) **
**                                                                            **
** Description      : DET check for ETH_17_GETHMAC_E_INV_MODE                 **
**                    This local API is required only if DET is enabled       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : ServiceId- ServiceId of API                             **
**                    CtrlIdx- Controller Id                                  **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : ETH_17_GETHMAC_E_DET_NO_ERR   - Valid Controller mode   **
**                    ETH_17_GETHMAC_E_INV_MODE     - Invalid Controller mode **
**                                                                            **
*******************************************************************************/
static uint32 Eth_17_lDetCheckMode(const uint8 ServiceId, const uint8 CtrlIdx)
{
  uint32 DevError;
  uint32 MacMode;
  uint32 DmaTxMode;
  uint32 DmaRxMode;
  const Ifx_GETH *EthCntrlAdd;
  EthCntrlAdd = Eth_GEthMacCntrl[CtrlIdx];
  DevError = ETH_17_GETHMAC_E_DET_NO_ERR;
  /* Read MAC, DMA-Tx and DMA-Rx modes */

  MacMode = (uint32)(EthCntrlAdd->MAC_CONFIGURATION.U);
  DmaTxMode = (uint32)(EthCntrlAdd->DMA_CH[0].TX_CONTROL.U);
  DmaRxMode = (uint32)(EthCntrlAdd->DMA_CH[0].RX_CONTROL.U);

  /* [cover parentID={5BE37D25-8C4D-43ee-8A61-3778E5250774}]
  Transmit and Receive engine is enabled in MAC,Tx DMA & Rx DMA
  [/cover] */
  /* Check configuration register, whether the Transmit and Receive engine is
  enabled to decide the Mode of the Driver */
  if(!(((MacMode & ((uint32)ETH_17_GETHMAC_MAC_TX | \
                    (uint32)ETH_17_GETHMAC_MAC_RX)) == \
                    ((uint32)ETH_17_GETHMAC_TXENABLE | \
                     (uint32) ETH_17_GETHMAC_RXENABLE)) && \
       ((DmaTxMode & ((uint32)ETH_17_GETHMAC_DMA_TX_CH_START)) ==\
                    ((uint32)ETH_17_GETHMAC_DMA_TX_CH_START))&&\
       ((DmaRxMode & ((uint32)ETH_17_GETHMAC_DMA_RX_CH_START)) ==\
                    ((uint32)ETH_17_GETHMAC_DMA_RX_CH_START))))
  {
    DevError = ETH_17_GETHMAC_E_INV_MODE;

#if(ETH_17_GETHMAC_DEV_ERROR_DETECT == STD_ON)
    /* [cover parentID={9B566A5F-419D-4a14-8C7B-DEB28E34F574}]
    Report DET as Invalid Mode with Service ID
    [/cover] */
    (void)Det_ReportError(ETH_17_GETHMAC_MODULE_ID, ETH_17_GETHMAC_INSTANCE_ID,
                    ServiceId, ETH_17_GETHMAC_E_INV_MODE);
#else
    UNUSED_PARAMETER(ServiceId);
#endif
  }
  return DevError;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={34698490-C553-436b-A104-03194BEF930E}]  **
**                                                                            **
** Syntax : Eth_17_GEthMac_CoreCntrlConfigType* Eth_17_lGetCtrlConfigPtr      **
**                                                    ( const uint8 CtrlIdx)  **
**                                                                            **
** Description :      Get pointer to controller config data                   **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        none                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant for the same CtrlIdx,                     **
**                    reentrant for different                                 **
**                                                                            **
** Parameters (in):   CtrlIdx - Controller Id                                 **
**                                                                            **
** Parameters (out):  none                                                    **
**                                                                            **
** Return value:      CtrlCfgPtr- Pointer to controller configuration         **
**                                                                            **
******************************************************************************/
static Eth_17_GEthMac_CoreCntrlConfigType* Eth_17_lGetCtrlConfigPtr
                                                         ( const uint8 CtrlIdx)
{
  uint32 CoreId;
  uint8 CoreCntrlIdx;
  const Eth_17_GEthMac_CoreConfigType *EthLocalCoreCfgPtr;
  Eth_17_GEthMac_CoreCntrlConfigType *EthLocalCntrlCfgPtr;
  /*Get the current core Id*/
  CoreId = Mcal_GetCpuIndex();
  EthLocalCoreCfgPtr = Eth_ConfigSetPtr->EthCoreAdd[CoreId];
  CoreCntrlIdx = Eth_ConfigSetPtr->EthNodeIdxmapPtr[CtrlIdx];
  /*Obtain the pointer to controller configuration for the current core*/
  EthLocalCntrlCfgPtr = EthLocalCoreCfgPtr->EthCoreCntrlPtr;
  EthLocalCntrlCfgPtr = &(EthLocalCntrlCfgPtr[CoreCntrlIdx]);

  return EthLocalCntrlCfgPtr;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={E05A83D5-D2B0-4428-83AF-AC018CCCEC18}]  **
**                                                                            **
** Syntax : Eth_17_GEthMac_CntrlStatusType* Eth_17_lGetCtrlStatusPtr          **
**                                                    ( const uint8 CtrlIdx)  **
**                                                                            **
** Description :      Get pointer to controller status                        **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:        none                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant for the same CtrlIdx,                     **
**                    reentrant for different                                 **
**                                                                            **
** Parameters (in):   CtrlIdx - Controller Id                                 **
**                                                                            **
** Parameters (out):  none                                                    **
**                                                                            **
** Return value:      CtrlCfgPtr- Pointer to controller Status                **
**                                                                            **
******************************************************************************/
static Eth_17_GEthMac_CntrlStatusType* Eth_17_lGetCtrlStatusPtr
                                                         ( const uint8 CtrlIdx)
{
  uint32 CoreId;
  uint8 CoreCntrlIdx;
  Eth_17_GEthMac_CntrlStatusType *EthLocalCoreStatusPtr;
  /*Get the current core Id*/
  CoreId = Mcal_GetCpuIndex();
  CoreCntrlIdx = Eth_ConfigSetPtr->EthNodeIdxmapPtr[CtrlIdx];
  /*Obtain the pointer to controller status for the current core*/
  EthLocalCoreStatusPtr = Eth_CntrlStatus[CoreId];
  EthLocalCoreStatusPtr = &(EthLocalCoreStatusPtr[CoreCntrlIdx]);
  return EthLocalCoreStatusPtr;
}

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID={A9C5E3A3-2FD0-4261-BA6F-A5D9DFFBFDEF}]  **
**                                                                            **
** Syntax          : void Eth_17_lBkToBkRegWrInsrtDly (const uint32           **
**                                                     BkToBkDelayTime)       **
**                                                                            **
** Description     : Inserts the required delay for back to back register     **
**                    write operations                                        **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      :  None                                                    **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Reentrant                                               **
**                                                                            **
** Parameters (in) :  BkToBkDelayTime - Wait time in ns to be inserted for    **
**                      back to back register writes                          **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
static void Eth_17_lBkToBkRegWrInsrtDly(const uint32 BkToBkDelayTime)
{
  uint32 NumberWaitTicks;
  uint32 BaseSTMTick;
  uint32 CurrSTMTick;
  uint32 DelayTickResolution;
  boolean IsTimeExpired;

  /* Get STM timer current resolution and calculate number of ticks to wait*/
  DelayTickResolution = Mcal_DelayTickResolution();

  NumberWaitTicks = (BkToBkDelayTime / DelayTickResolution);

  /* Do not allow ticks to wait to be zero, if STM timer resolution is lower*/
  /* [cover parentID={0DF84DE8-3BB6-423f-A945-E74A6B3BF4C5}]
  If the number of ticks is zero
  [/cover] */
  if(NumberWaitTicks == 0U)
  {
    /* Increment the tick */
    NumberWaitTicks++;
  }

  /*Get current STM tick*/
  CurrSTMTick = Mcal_DelayGetTick();
  BaseSTMTick = CurrSTMTick;
  IsTimeExpired = FALSE;

  /* Wait until necessary time has elapsed */
  do
  {
    /* Check wait time has reached maximum timeout configured */
    /* [cover parentID={ECD3AA09-BAB2-4340-BBD3-E6670593396B}]
    Has the necessary time elapsed?
    [/cover] */
    if(((uint32)((CurrSTMTick - BaseSTMTick) &
         ETH_17_GETHMAC_STM_TICK_OVERFLOW)) >= NumberWaitTicks)
    {
      /* Necessary time has elapsed */
      IsTimeExpired = TRUE;
    }

    /*Get current STM tick*/
    CurrSTMTick = Mcal_DelayGetTick();
  }while(IsTimeExpired == FALSE);
}

#define ETH_17_GETHMAC_STOP_SEC_CODE_QM_GLOBAL
 /* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
  guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Eth_17_GEthMac_MemMap.h"

/*******************************************************************************
**                               End of File                                  **
*******************************************************************************/
