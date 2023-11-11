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
**  FILENAME     : Crc.c                                                      **
**                                                                            **
**  VERSION      : 30.0.0                                                     **
**                                                                            **
**  DATE         : 2022-06-16                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Crc Driver source file                                     **
**                                                                            **
**  SPECIFICATION(S) : Specification of CRC Driver, AUTOSAR Release 4.2.2     **
**                   : Specification of CRC Driver, AUTOSAR Release 4.4.0     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/


/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* [cover parentID={BDE616FE-5D39-4b9d-9390-8351CC6C490C}]
[/cover] */
/* [cover parentID={B5B329DB-513F-4a82-BB6A-B8A816951405}]
[/cover] */
/* [cover parentID={37FC0A70-411D-4557-9787-D56E29BB3B34}]
   CRC: Interrupt Control Registers.
[/cover] */

/* Include microcontroller SFR headers */
#include "IfxFce_reg.h"

/* Include McalLib functions */
#include "McalLib.h"

/* Include Crc.h header */
#include "Crc.h"

#if (CRC_DMA_MAX_CHANNELS > 0U)
/* Include Dma.h header */
#include "Dma.h"
/* Include Crc_Cbk.h header */
#include "Crc_Cbk.h"

#if (CRC_RUNTIME_API_MODE != CRC_MCAL_SUPERVISOR)
/*Include McalLib_OsStub.h */
#include "McalLib_OsStub.h"
#endif
#endif

/* Import of Safety functionality.*/
#if (CRC_SAFETYENABLE == STD_ON)
#include "Mcal_SafetyError.h"
#endif
/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/

/* AUTOSAR Specification File Version Check */
#ifndef CRC_AR_RELEASE_MAJOR_VERSION
#error "CRC_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

#ifndef CRC_AR_RELEASE_MINOR_VERSION
#error "CRC_AR_RELEASE_MINOR_VERSION is not defined. "
#endif

#ifndef CRC_AR_RELEASE_REVISION_VERSION
#error "CRC_AR_RELEASE_REVISION_VERSION is not defined. "
#endif

#ifndef CRC_SW_MAJOR_VERSION
#error "CRC_SW_MAJOR_VERSION is not defined. "
#endif

#ifndef CRC_SW_MINOR_VERSION
#error "CRC_SW_MINOR_VERSION is not defined. "
#endif

#ifndef CRC_SW_PATCH_VERSION
#error "CRC_SW_PATCH_VERSION is not defined."
#endif

/* Check for Correct inclusion of headers */
#if (CRC_SW_MAJOR_VERSION != 20U)
#error "CRC_SW_MAJOR_VERSION does not match. "
#endif

#if (CRC_SW_MINOR_VERSION != 20U)
#error "CRC_SW_MINOR_VERSION does not match. "
#endif

#if (CRC_SW_PATCH_VERSION != 0U)
#error "CRC_SW_PATCH_VERSION does not match."
#endif

/* Version check for Module */
/* [cover parentID={B570B431-86E0-4293-8B1F-CD58B339F06B}]
 * Version Check
 * [/cover]*/

#if ( CRC_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION )
#error "CRC_AR_RELEASE_MAJOR_VERSION does not match. "
#endif

#if ( CRC_AR_RELEASE_MINOR_VERSION != MCAL_AR_RELEASE_MINOR_VERSION )
#error "CRC_AR_RELEASE_MINOR_VERSION does not match. "
#endif

#if ( CRC_AR_RELEASE_REVISION_VERSION != MCAL_AR_RELEASE_REVISION_VERSION )
#error "CRC_AR_RELEASE_REVISION_VERSION does not match. "
#endif
/***************************************************************************/

/****************************************************************************
**                      Private Macro Definitions                          **
****************************************************************************/
/* ********** Macros - General ***********    */
#if (((CRC_8_MODE != STD_OFF)||(CRC_8H2F_MODE != STD_OFF) || \
  (CRC_16_MODE != STD_OFF)|| (CRC_16ARC_MODE != STD_OFF) || \
  (CRC_32_MODE != STD_OFF)||(CRC_32P4_MODE != STD_OFF) ||\
  (CRC_64_MODE != STD_OFF) ))
#define CRC_NOT_SUCCESS           ((uint8)0x00U)
#endif

#if ((CRC_SAFETYENABLE == STD_ON) && ((CRC_8_MODE != STD_OFF)||(CRC_8H2F_MODE != STD_OFF) || \
  (CRC_16_MODE != STD_OFF)|| (CRC_16ARC_MODE != STD_OFF) || \
  (CRC_32_MODE != STD_OFF)||(CRC_32P4_MODE != STD_OFF) ||\
  (CRC_64_MODE != STD_OFF) ))
#define CRC_SUCCESS               ((uint8)0x01U)
#endif

#if ((CRC_16_DMAMODE != STD_OFF) || ((CRC_SAFETYENABLE == STD_ON) &&\
  (CRC_DMA_MAX_CHANNELS > 0U)))
#define CRC_ALIGNLENGTH_16BIT     (2U)
#endif

#if ((CRC_32_DMAMODE != STD_OFF) || (CRC_32P4_DMAMODE != STD_OFF) ||\
     ((CRC_SAFETYENABLE == STD_ON) && (CRC_DMA_MAX_CHANNELS > 0U)))
#define CRC_ALIGNLENGTH_32BIT     (4U)
#endif

#if ((CRC_8_DMAMODE != STD_OFF)|| (CRC_16_DMAMODE != STD_OFF) ||\
 (CRC_32_DMAMODE != STD_OFF) || (CRC_32P4_DMAMODE != STD_OFF))
#define CRC_DMACH_FREE            (0x0U)
#define CRC_DMACH_BUSY            (0x1U)
#endif

#if  ((CRC_SAFETYENABLE == STD_ON) && (CRC_DMA_MAX_CHANNELS > 0U))
#define CRC_THREE_U               ((uint32)0x03U)
#endif

#if ((CRC_64_MODE != STD_OFF) || (CRC_32P4_MODE != STD_OFF))
#define CRC_BYTELENGTH_U          (8U)
#endif

#if (CRC_32P4_MODE == CRC_TABLE_MODE)
#define CRC_SHIFT_TWENTYFOUR      ((uint32)24U)
#define CRC_BITCNT_THIRTYTWO      (32U)
#endif

#if ((CRC_64_MODE != STD_OFF) || (CRC_32P4_MODE != STD_OFF) ||\
 (CRC_16ARC_MODE != STD_OFF))
#define CRC_BITCNT_EIGHT          ((uint8)8U)
#endif

#if (CRC_16ARC_MODE != STD_OFF)
#define CRC_BITCNT_SIXTEEN        (16U)
#endif

#if ((CRC_32P4_MODE != STD_OFF) || (CRC_32P4_DMAMODE != STD_OFF) ||\
  (CRC_32_DMAMODE != STD_OFF))
#define CRC_BITCNT_THIRTYTWO      (32U)
#endif

#if (CRC_32P4_MODE == CRC_RUNTIME_MODE)
#define CRC_CRC32_SIZE            (32U)
#define CRC_CRC32_MSB             ((uint32)0x80000000U)
#endif

#if (CRC_64_MODE != STD_OFF)
#define CRC_BITCNT_SIXTYFOUR      (64U)
#endif

#if (CRC_64_MODE == CRC_TABLE_MODE)
#define CRC_SHIFT_FIFTYSIX        ((uint32)56U)
#endif

#if (CRC_64_MODE == CRC_RUNTIME_MODE)
#define CRC_CRC64_SIZE            (64U)
#define CRC_CRC64_MSB             ((uint64)0x8000000000000000U)
#endif

#if (CRC_32P4_MODE == CRC_TABLE_MODE)
#define CRC_U32LSB_MASK           ((uint32)0xFFU)
#endif

#if (CRC_64_MODE == CRC_TABLE_MODE)
#define CRC_U64LSB_MASK           ((uint32)0xFFU)
#endif

/* ********** Macros - XOR values ********** */

/* These are the macros which hold the XOR values which are used
 * during the CRC computation. The values used here come from
 * the standard itself. Check the Autosar SWS for details. */

#if ((CRC_8_MODE != STD_OFF)||(CRC_8_DMAMODE != STD_OFF))
#define CRC_CRC8_XOR_VALUE        ((uint8)0xFFU)
#endif

#if (CRC_8H2F_MODE != STD_OFF)
#define CRC_CRC8H2F_XOR_VALUE     ((uint8)0xFFU)
#endif

#if ((CRC_16_MODE != STD_OFF)||(CRC_16_DMAMODE != STD_OFF))
#define CRC_CRC16_XOR_VALUE       ((uint16)0x0000U)
#endif

#if (CRC_16ARC_MODE != STD_OFF)
#define CRC_CRC16ARC_XOR_VALUE    ((uint16)0x0000U)
#endif

#if  (CRC_32_DMAMODE != STD_OFF)
#define CRC_CRC32_XOR_VALUE       ((uint32)0xFFFFFFFFU)
#endif

#if  ((CRC_32P4_MODE != STD_OFF)||(CRC_32P4_DMAMODE != STD_OFF))
#define CRC_CRC32P4_XOR_VALUE     ((uint32)0xFFFFFFFFU)
#endif

#if  (CRC_64_MODE != STD_OFF)
#define CRC_CRC64_XOR_VALUE       ((uint64)0xFFFFFFFFFFFFFFFFU)
#endif

/* ********** Macros - CRC polynomials ********** */

/* These are the different polynomials being used for the CRC computation.
 * The values are just as per the standard. The names which are used
 * are self explanatory. Refer the Autosar SWS for more details. */
#if (CRC_8_MODE != STD_OFF)
#define CRC_CRC8_POLYNOMIAL       ((uint8)0x1DU)
#endif

#if (CRC_8H2F_MODE != STD_OFF)
#define CRC_CRC8H2F_POLYNOMIAL    ((uint8)0x2FU)
#endif

#if (CRC_16_MODE != STD_OFF)
#define CRC_CRC16_POLYNOMIAL      ((uint16)0x1021U)
#endif

#if (CRC_16ARC_MODE != STD_OFF)
#define CRC_CRC16ARC_POLYNOMIAL   ((uint16)0x8005U)
#endif

#if (CRC_32P4_MODE == CRC_RUNTIME_MODE)
#define CRC_CRC32P4_POLYNOMIAL    ((uint32)0xF4ACFB13U)
#endif

#if (CRC_64_MODE == CRC_RUNTIME_MODE)
#define CRC_CRC64_POLYNOMIAL      ((uint64)0x42F0E1EBA9EA3693U)
#endif

/* ********** Macros for the CLC, CRC and CFG registers ********** */
#if (CRC_8_DMAMODE != STD_OFF)
#define CRC8_CFGREG_INITVAL       ((uint32)0x00030400U)
#endif

#if (CRC_16_DMAMODE != STD_OFF)
#define CRC16_CFGREG_INITVAL      ((uint32)0x00020800U)
#endif

#if (CRC_32_DMAMODE != STD_OFF)
#define CRC32_CFGREG_INITVAL      ((uint32)0x00000F00U)
#endif

#if (CRC_32P4_DMAMODE != STD_OFF)
#define CRC32P4_CFGREG_INITVAL    ((uint32)0x00010F00U)
#endif

#if ((CRC_8_DMAMODE != STD_OFF)|| (CRC_16_DMAMODE != STD_OFF) ||\
 (CRC_32_DMAMODE != STD_OFF) || (CRC_32P4_DMAMODE != STD_OFF))
#define CRC_CLC_INITVAL           ((uint32)0U)
#endif

/* ********** Macros for endinit protected writes ********** */
#if (CRC_DMA_MAX_CHANNELS > 0U)
/* [cover parentID={71E54B7C-10D3-423b-A217-5E8A41C2F4B8}]
 * User mode support by CRC driver[/cover] */
#if (CRC_RUNTIME_API_MODE  == CRC_MCAL_SUPERVISOR)
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'CRC_LIB_RUNTIME_WRITEPERIPENDINITPROTREG'
 * defined for supervisor mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define CRC_LIB_RUNTIME_WRITEPERIPENDINITPROTREG(RegAdd,Data)    \
                                    Mcal_WritePeripEndInitProtReg(RegAdd,Data)
#else
/* [cover parentID={1A65EADD-AFD0-4845-B2D2-8257E086DD67}] [/cover] */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'CRC_LIB_RUNTIME_WRITEPERIPENDINITPROTREG'
 * defined for User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define CRC_LIB_RUNTIME_WRITEPERIPENDINITPROTREG(RegAdd,Data)    \
                                  MCAL_LIB_WRITEPERIPENDINITPROTREG(RegAdd,Data)
#endif

#if  (CRC_SAFETYENABLE == STD_ON)
#define CRC_DMA_MAXLENGTH         (16383U)
#endif

#define CRC_DMA_ADICR             (0x08200008U)

#if (CRC_8_DMAMODE != STD_OFF)
#define CRC_DMA_8_CHCFGR          (0x00080000U)
#endif

#if (CRC_16_DMAMODE != STD_OFF)
#define CRC_DMA_16_CHCFGR         (0x00280000U)
#endif

#if ((CRC_32_DMAMODE != STD_OFF)||(CRC_32P4_DMAMODE != STD_OFF))
#define CRC_DMA_32_CHCFGR         (0x00480000U)
#endif
#endif

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/
#if (CRC_DMA_MAX_CHANNELS > 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
#define CRC_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
 * guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
 * without safeguard. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"

/*Array to hold the address of the configuration structure of type
Crc_ChannelConfigType*/
extern const Crc_ChannelConfigType *const Crc_ChannelConfig[6];

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
#define CRC_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
 * guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
 * without safeguard. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"
#endif

#if (CRC_32P4_MODE == CRC_TABLE_MODE)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond
 * 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond
 * 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond
 * 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond
 * 32 chars because of AS naming convention*/
#define CRC_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per
 * Autosar guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly
 * included without safegaurd. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"

/*Table array for CRC32P4 calculation*/
extern const uint32 Crc_Table32P4[CRC_TABLE_LENGTH];

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond
 * 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond
 * 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond
 * 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond
 * 32 chars because of AS naming convention*/
#define CRC_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per
 * Autosar guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly
 * included without safeguard. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"
#endif
/* #ifdef CRC_32P4_MODE == CRC_TABLE_MODE*/

#if (CRC_64_MODE == CRC_TABLE_MODE)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond
 * 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond
 * 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond
 * 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond
 * 32 chars because of AS naming convention*/
#define CRC_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_64
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per
 * Autosar guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly
 * included without safeguard. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"

/*Table array for CRC64 calculation*/
extern const uint64 Crc_Table64[CRC_TABLE_LENGTH];

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond
 * 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond
 * 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond
 * 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond
 * 32 chars because of AS naming convention*/
#define CRC_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_64
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per
 * Autosar guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly
 * included without safegaurd. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"
#endif
/* #ifdef CRC_64_MODE == CRC_TABLE_MODE*/

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/* [cover parentID={BDAFDFF4-C8DB-42c5-B2C1-78CB1AA30FF2}]
 * [/cover] */
/* This structure is to configure the parameter based on the selected polynomial
 * for the CRC calculation by CRCN CPU instruction.
 * Configuration will be done in each API using CRCN for CRC calculation.
 */
#if ((CRC_8_MODE != STD_OFF)||(CRC_8H2F_MODE != STD_OFF) || \
(CRC_16_MODE != STD_OFF)|| (CRC_16ARC_MODE != STD_OFF))
typedef struct
{
  /* 0 1 2 : input data width in the range [1:8]*/
  unsigned_int IpDataWidth:3;

  /* 3 4 5 6 7 :  unused*/
  unsigned_int Unused1:5;

  /* 8 : 1:Data input is little-endian
         0:Data input is Bigend-endian*/
  unsigned_int IpDataBitOrder:1;

  /* 9 : Reflection of result and seed value*/
  unsigned_int LogicalInversion:1;

  /* 10 11 : unused*/
  unsigned_int Unused2:2;

  /* 12 13 14 15: CRC width in the range [1:16]*/
  unsigned_int CrcWidth:4;

  /* 16 - 31 [16+N-1:16]: Polynomial for which the CRC has to be calculated*/
  unsigned_int Polynomial:16;
}Crc_ConfigParams_Bits;

/*union for bitwise access of the Crc_ConfigParams_Bits*/
typedef union
{
  uint32 U;
  Crc_ConfigParams_Bits B;

}Crc_ConfigParam;
#endif

/*******************************************************************************
**                 Private Function Declarations:                             **
*******************************************************************************/
/* Memory Map of the CRC Code */

#define CRC_START_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
 [/cover] */
/* [cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
 [/cover] */
/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
 [/cover] */
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
 [/cover] */
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
 [/cover] */
/* [cover parentID={07DD7AB2-AF63-4d8b-8FB9-0261F77B0ED4}]
 [/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
[/cover] */
#include "Crc_MemMap.h"

#if ((CRC_SAFETYENABLE == STD_ON) && ((CRC_8_MODE != STD_OFF)||\
 (CRC_8H2F_MODE != STD_OFF) || (CRC_16_MODE != STD_OFF)||\
 (CRC_16ARC_MODE != STD_OFF) || (CRC_32_MODE != STD_OFF)||\
 (CRC_32P4_MODE != STD_OFF) || (CRC_64_MODE != STD_OFF) ))
LOCAL_INLINE uint8 Crc_lSafetyChecks
(
  const uint8* const Crc_DataPtr,
  const uint8  Crc_ApiServiceID,
  const uint32 Crc_Length

);
#endif

#if ((CRC_8_MODE !=STD_OFF) || (CRC_8H2F_MODE != STD_OFF) ||\
  (CRC_16_MODE !=STD_OFF))
LOCAL_INLINE uint16 Crc_lCRCN
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint16 Crc_StartValue,
  const uint32 Crc_Config
);
#endif

#if ((CRC_16ARC_MODE !=STD_OFF) || (CRC_32P4_MODE != STD_OFF) ||\
  (CRC_32_DMAMODE != STD_OFF) ||(CRC_32P4_DMAMODE != STD_OFF) ||\
  (CRC_64_MODE != STD_OFF))
LOCAL_INLINE uint32 Crc_lCommonReflect
(
  const uint32 CRCData_32bit,
  const uint8 CRC_BitCount
);
#endif

#if(CRC_64_MODE !=STD_OFF)
static uint64 Crc_lReflect64
(
  const uint64 CRCData_64bit,
  const uint8 CRC_BitCount
);
#endif

#if (CRC_32P4_MODE == CRC_RUNTIME_MODE)
static uint32 Crc_lCalculateCRC32P4Runtime
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint32 Crc_StartValue32,
  const boolean Crc_IsFirstCall
);
#endif

#if (CRC_32P4_MODE == CRC_TABLE_MODE)
static uint32 Crc_lCalculateCRC32P4Table
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint32 Crc_StartValue32,
  const boolean Crc_IsFirstCall
);
#endif

#if (CRC_64_MODE == CRC_RUNTIME_MODE)
static uint64 Crc_lCalculateCRC64Runtime
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint64 Crc_StartValue64,
  const boolean Crc_IsFirstCall
);
#endif

#if (CRC_64_MODE == CRC_TABLE_MODE)
static uint64 Crc_lCalculateCRC64Table
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint64 Crc_StartValue64,
  const boolean Crc_IsFirstCall
);
#endif

#if  ((CRC_SAFETYENABLE == STD_ON) && (CRC_DMA_MAX_CHANNELS > 0U))
LOCAL_INLINE Crc_DmaReturnType Crc_lDmaSafetyChecks
(
  const uint8* const Crc_DataPtr,
  const uint8  Crc_NoOfBytes,
  const uint32 Crc_Length,
  const uint32 Crc_CoreId
);
#endif

#if (CRC_DMA_MAX_CHANNELS > 0U)
LOCAL_INLINE void Crc_lDmaChUpdateTransfer
(
  const uint32 DmaConfig,
  const uint8  DmaChannel,
  const uint32 MoveLength,
  const uint32 lSourceAddress,
  const uint32 lDestAddress
);
#endif


#define CRC_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"

/*****************************************************************************
**                      Global Constant Definitions                         **
*****************************************************************************/
#if (CRC_DMA_MAX_CHANNELS > 0U)
/*DMA channel flag for each core*/
#if (CRC_CONFIGURED_CORE0 == STD_ON)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
#define CRC_START_SEC_VAR_INIT_ASIL_B_CORE0_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"
static uint32 Crc_DmaBusyFlag_Core0 = CRC_DMACH_FREE;

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
#define CRC_STOP_SEC_VAR_INIT_ASIL_B_CORE0_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"
#endif

#if (CRC_CONFIGURED_CORE1 == STD_ON)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
#define CRC_START_SEC_VAR_INIT_ASIL_B_CORE1_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"
static uint32 Crc_DmaBusyFlag_Core1 = CRC_DMACH_FREE;

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
#define CRC_STOP_SEC_VAR_INIT_ASIL_B_CORE1_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"
#endif

#if (CRC_CONFIGURED_CORE2 == STD_ON)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
#define CRC_START_SEC_VAR_INIT_ASIL_B_CORE2_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"
static uint32 Crc_DmaBusyFlag_Core2 = CRC_DMACH_FREE;

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
#define CRC_STOP_SEC_VAR_INIT_ASIL_B_CORE2_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"
#endif

#if (CRC_CONFIGURED_CORE3 == STD_ON)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
#define CRC_START_SEC_VAR_INIT_ASIL_B_CORE3_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
 * guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"
static uint32 Crc_DmaBusyFlag_Core3 = CRC_DMACH_FREE;

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
#define CRC_STOP_SEC_VAR_INIT_ASIL_B_CORE3_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"
#endif

#if (CRC_CONFIGURED_CORE4 == STD_ON)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
#define CRC_START_SEC_VAR_INIT_ASIL_B_CORE4_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"
static uint32 Crc_DmaBusyFlag_Core4 = CRC_DMACH_FREE;

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
#define CRC_STOP_SEC_VAR_INIT_ASIL_B_CORE4_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"
#endif

#if (CRC_CONFIGURED_CORE5 == STD_ON)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
#define CRC_START_SEC_VAR_INIT_ASIL_B_CORE5_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
 * guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
 * without safeguard. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"
static uint32 Crc_DmaBusyFlag_Core5 = CRC_DMACH_FREE;

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
#define CRC_STOP_SEC_VAR_INIT_ASIL_B_CORE5_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
 * guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
 * without safeguard. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"
#endif

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
#define CRC_START_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"

/*Array holding the address of the status flag of the configured DMA channels*/
/* [cover parentID={167FF8F6-45DA-49e0-AC1E-FC8D691B47CF}]
[/cover] */
static uint32 *const Crc_DmaBusyFlag[6]=
{
  #if (CRC_CONFIGURED_CORE0 == STD_ON)
  &Crc_DmaBusyFlag_Core0,
  #else
  NULL_PTR,
  #endif
  #if (CRC_CONFIGURED_CORE1 == STD_ON)
  &Crc_DmaBusyFlag_Core1,
  #else
  NULL_PTR,
  #endif
  #if (CRC_CONFIGURED_CORE2 == STD_ON)
  &Crc_DmaBusyFlag_Core2,
  #else
  NULL_PTR,
  #endif
  #if (CRC_CONFIGURED_CORE3 == STD_ON)
  &Crc_DmaBusyFlag_Core3,
  #else
  NULL_PTR,
  #endif
  #if (CRC_CONFIGURED_CORE4 == STD_ON)
  &Crc_DmaBusyFlag_Core4,
  #else
  NULL_PTR,
  #endif
  #if (CRC_CONFIGURED_CORE5 == STD_ON)
  &Crc_DmaBusyFlag_Core5,
  #else
  NULL_PTR,
  #endif
};

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of naming convention*/
#define CRC_STOP_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"
#endif

/*******************************************************************************
**        Global Variable Definitions                                         **
*******************************************************************************/


/*******************************************************************************
**        Private Constant Definitions                                        **
*******************************************************************************/


/*******************************************************************************
**        Private Variable Definitions                                        **
*******************************************************************************/


/*******************************************************************************
**        Global Function Definitions                                         **
*******************************************************************************/
/* [cover parentID={55C2CC41-ABDB-45df-A1FF-6F9C5FB3435C}]
[/cover] */
/* Memory Map of the CRC Code */
#define CRC_START_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"

#if (CRC_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={4F55BFEA-0359-49c1-A254-83F3978261BF}]   **
**                                                                            **
** Syntax         : void Crc_GetVersionInfo                                   **
**                                 (Std_VersionInfoType *Versioninfo)         **
**                                                                            **
** Description    : This service returns the version information              **
**                  of this module.The version information includes :         **
**                  - Module Id                                               **
**                  - Vendor Id                                               **
**                  - Vendor specific version numbers                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : 0x04                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : None                                                      **
**                                                                            **
** Parameters(out): Versioninfo (Pointer to where to store the version        **
**                               information of this module)                  **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
void Crc_GetVersionInfo
(
  Std_VersionInfoType* const Versioninfo
)
{
  /* [cover parentID={CB52FE8D-792A-4d97-B0C0-1F8291105229}]
   * If safety check is enabled
   * [/cover] */
  /* Check if the passed parameter is a NULL_PTR */
  #if (CRC_SAFETYENABLE == STD_ON)
  /* [cover parentID={614B1344-B4B9-4110-BF6E-BB9B33D2669C}]
   * Is the passed pointer valid?
   * [/cover] */
  if ((Versioninfo) == NULL_PTR)
  {
    /* [cover parentID={5615A26C-8D6F-4603-937A-324DB2C79246}]
     * Report Mcal Safety Error
     * [/cover] */
    /* Report Safety error with CRC_E_PARAM_POINTER */
    Mcal_ReportSafetyError(CRC_MODULE_ID, CRC_INSTANCE_ID,
                           CRC_SID_GETVERSIONINFO, CRC_E_PARAM_POINTER);
  }
  else
  #endif
  {
    /* [cover parentID={C957528E-61F3-4926-8C57-C536A7FED827}]
     * Update vendor ID, module ID, SW major, SW minor and SW patch version values
     * to the passed pointer parameter.
     * [/cover] */
    /* Get CRC Vendor ID */
    ((Std_VersionInfoType*)(Versioninfo))->vendorID = CRC_VENDOR_ID;

    /* Get CRC Module ID */
    ((Std_VersionInfoType*)(Versioninfo))->moduleID = CRC_MODULE_ID;

    /* Get CRC module Software major version */
    ((Std_VersionInfoType*)(Versioninfo))->sw_major_version =
      (uint8)CRC_SW_MAJOR_VERSION;

    /* Get CRC module Software minor version */
    ((Std_VersionInfoType*)(Versioninfo))->sw_minor_version =
      (uint8)CRC_SW_MINOR_VERSION;

    /* Get CRC module Software patch version */
    ((Std_VersionInfoType*)(Versioninfo))->sw_patch_version =
      (uint8)CRC_SW_PATCH_VERSION;
  }
} /* End of Crc_GetVersionInfo() */

/******************************************************************************/
#endif
/* End of #if (CRC_VERSION_INFO_API == STD_ON) */

#if (CRC_8_MODE != STD_OFF)
/*******************************************************************************
** Traceability     : [cover parentID={F320531F-FD72-417d-AE1B-620B857DFD21}] **
**                                                                            **
** Syntax           : uint8 Crc_CalculateCRC8                                 **
**                      (                                                     **
**                          const uint8* const Crc_DataPtr,                   **
**                          const uint32 Crc_Length,                          **
**                          const uint8 Crc_StartValue8,                      **
**                          const boolean Crc_IsFirstCall                     **
**                      )                                                     **
**                                                                            **
** Description      : This function takes the value of input data pointer,    **
**                    start value and polynomial, calculates the crc taking   **
**                    the precomputed  and  xor value  and returns the        **
**                    CRC xored with XOR value                                **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x01                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : Crc_DataPtr  - Pointer to the start of the datablock    **
**                    Crc_Length - Length of the input data to be fetched     **
**                    Crc_StartValue8 -Start value for CRC Calculation        **
**                    Crc_IsFirstCall -Boolean to decIDe the start value      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : 8-bit result of CRC calculation                         **
**                                                                            **
*******************************************************************************/
uint8 Crc_CalculateCRC8
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint8 Crc_StartValue8,
  const boolean Crc_IsFirstCall
)
{
  uint8 Result = CRC_NOT_SUCCESS;
  uint8 StartValue8;

  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * this MISRA rule. Union usage is required for bitwise access to the 32-bit
   * Crc_ConfigParams_Bits structure. */
  Crc_ConfigParam Parameters_Crc8;
  /* [cover parentID={A1459FF8-9C4B-4826-9BEA-B12CF8F93E9D}]
   * If safety check is enabled
   * [/cover] */
  #if (CRC_SAFETYENABLE == STD_ON)

  uint8 SafetyResult;
  /* [cover parentID={9CABEDBB-7BF4-4cd4-A074-E24E3ED4BF35}]
   * Set CRC result to configured error value
   * [/cover] */
  Result = (uint8)CRC_8_CONFIGERROR_VAL;
  /* [cover parentID={69917B33-5EC0-491c-9BC6-7388B652D37A}]
   * Check Mcal Safety error
   * [/cover] */
  SafetyResult = Crc_lSafetyChecks(Crc_DataPtr, CRC_SID_CALCULATE_CRC8, Crc_Length);

  /* If all the checks are done successfully*/
  /* [cover parentID={746F67D2-89E6-4163-82BD-9633120A2EB0}]
   * If the return value is CRC_SUCCESS
   * [/cover] */
  if(SafetyResult == CRC_SUCCESS)
  #endif
  {
    /*Configuration for 8 bit CRC calculation*/
    /* [cover parentID={54AFC2B2-5603-45e0-A8DE-ABACDB3EBF6D}]
     * Configure Parameters_Crc8 variable for data width, bitorder, logical
     * inversion, crc width and polynomial
     * [/cover] */
    Parameters_Crc8.B.IpDataWidth = 7;
    Parameters_Crc8.B.Unused1=0;
    Parameters_Crc8.B.IpDataBitOrder = 0;
    Parameters_Crc8.B.LogicalInversion = 0;
    Parameters_Crc8.B.Unused2=0;
    Parameters_Crc8.B.CrcWidth = 7;
    Parameters_Crc8.B.Polynomial = CRC_CRC8_POLYNOMIAL;

    /* Is this the first call to compute the CRC? */
    /* [cover parentID={07560C98-18A7-4f9c-B8D9-1D77D134F390}]
     * Is this first call?
     * [/cover] */
    if(Crc_IsFirstCall == (boolean)TRUE)
    {
      /* [cover parentID={14C42FA7-640B-4bbf-A60F-4FC2045EBB22}]
       * Set Start Value to Initial value for 8 bit CRC
       * [/cover] */
      StartValue8 = (uint8)CRC_INITIAL_VALUE8;
    }
    else
    {
      /* [cover parentID={5BABC431-E251-4b7a-83D4-C109980CB856}]
       * XOR Start Value with XOR Value for the 8 bit CRC
       * [/cover] */
      StartValue8 = Crc_StartValue8 ^ CRC_CRC8_XOR_VALUE;
    }
    /* Crc_lCRCN function is called for the calculation by CRCN instruction*/
    /* [cover parentID={0D995FA1-D449-4136-9E57-5277FC94C5B4}]
     * Calculate CRC
     * [/cover] */
    StartValue8 = (uint8)Crc_lCRCN(Crc_DataPtr, Crc_Length, StartValue8, Parameters_Crc8.U);

    /* XOR Start Value with XOR Value for the 16 bit CRC */
    Result = StartValue8 ^ CRC_CRC8_XOR_VALUE;
  }
  return Result;
}
#endif
/* #if CRC_8_MODE */

#if CRC_8H2F_MODE != STD_OFF
/*******************************************************************************
** Traceability     : [cover parentID={D8F89B96-6BB3-4a12-BB8E-A51666324262}] **
**                                                                            **
** Syntax           : uint8 Crc_CalculateCRC8H2F                              **
**                      (                                                     **
**                          const uint8* const Crc_DataPtr,                   **
**                          const uint32 Crc_Length,                          **
**                          const uint8 Crc_StartValue8H2F,                   **
**                          const boolean Crc_IsFirstCall                     **
**                      )                                                     **
** Description      : This function takes the value of input data pointer,    **
**                    start value and polynomial, calculates the crc          **
**                    taking the precomputed and  xor value  and returns      **
**                    the CRC xored with XOR value                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x05                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : Crc_DataPtr  - Pointer to the start of the datablock    **
**                    Crc_Length - Length of the input data to be fetched     **
**                    Crc_StartValue8H2F -Start value for CRC Calculation     **
**                    Crc_IsFirstCall -Boolean to decide the start value      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : 8-bit result of CRC calculation                         **
**                                                                            **
*******************************************************************************/
uint8 Crc_CalculateCRC8H2F
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint8 Crc_StartValue8H2F,
  const boolean Crc_IsFirstCall
)
{
  uint8 Result = CRC_NOT_SUCCESS;
  uint8 StartValue8;

  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * this MISRA rule. Union usage is required for bitwise access to the 32-bit
   * Crc_ConfigParams_Bits structure. */
  Crc_ConfigParam Parameters_Crc8H2F;
  /* [cover parentID={1680ED3C-2C5E-4694-B97A-BFC6746848A3}]
   * If safety check is enabled
   * [/cover] */
  #if (CRC_SAFETYENABLE == STD_ON)

  uint8 SafetyResult;
  /* [cover parentID={1DB61D07-F46F-4fd3-B91A-D82AA471F1C6}]
   * Set CRC result to configured error value
   * [/cover] */
  Result = (uint8)CRC_8H2F_CONFIGERROR_VAL;

  /* [cover parentID={868DB9D7-1A29-4a11-BADE-FFA6F7AD3CC7}]
   * Check Mcal Safety error
   * [/cover] */
  SafetyResult = Crc_lSafetyChecks(Crc_DataPtr, CRC_SID_CALCULATE_CRC8H2F, Crc_Length);

  /* if all the checks are done successfully*/
  /* [cover parentID={6ADD12AA-A9B0-466c-858F-607D556F36A8}]
   * If the return value is CRC_SUCCESS
   * [/cover] */
  if(SafetyResult == CRC_SUCCESS)
  #endif
  {
    /*Configuration for 8 bit CRC calculation*/
    /* [cover parentID={BBE3A31A-B6F5-4109-9CC4-38D3623B1167}]
     * Configure Parameters_Crc8H2F variable for data width, bitorder, logical
     * inversion, crc width and polynomial
     * [/cover] */
    Parameters_Crc8H2F.B.IpDataWidth = 7;
    Parameters_Crc8H2F.B.Unused1=0;
    Parameters_Crc8H2F.B.IpDataBitOrder = 0;
    Parameters_Crc8H2F.B.LogicalInversion = 0;
    Parameters_Crc8H2F.B.Unused2=0;
    Parameters_Crc8H2F.B.CrcWidth = 7;
    Parameters_Crc8H2F.B.Polynomial = CRC_CRC8H2F_POLYNOMIAL;

    /* Is this the first call to compute the CRC? */
    /* [cover parentID={BBBAC514-6E95-437d-9715-91FFD7F01CCE}]
     * Is this first call?
     * [/cover] */
    if(Crc_IsFirstCall == (boolean)TRUE)
    {
      /* [cover parentID={5D8AEF79-BFC9-4b93-97BF-FDA74BB9F9FB}]
       * Set Start Value to Initial value for 8H2F bit CRC
       * [/cover] */
      StartValue8 = (uint8)CRC_INITIAL_VALUE8H2F;
    }
    else
    {
      /* [cover parentID={6A74B8E9-138B-4eb8-95ED-98F4B175A297}]
       * XOR Start Value with XOR Value for the 8 bit CRC
       * [/cover] */
      StartValue8 = Crc_StartValue8H2F ^ CRC_CRC8H2F_XOR_VALUE;
    }
    /* Crc_lCRCN function is called for the calculation by CRCN instruction*/
    /* [cover parentID={EF5B5170-486C-48b2-BD42-0CCA08735C20}]
     * Calculate CRC
     * [/cover] */
    StartValue8 = (uint8)Crc_lCRCN(Crc_DataPtr, Crc_Length, StartValue8, Parameters_Crc8H2F.U);

    /* [cover parentID={E49B83EB-AC65-4eb6-A2AE-F59E3D327528}]
     * XOR Start Value with XOR Value for the 16 bit CRC
     * [/cover] */
    Result = StartValue8 ^ CRC_CRC8H2F_XOR_VALUE;
  }
  return Result;
}
#endif
/* #if CRC_8H2F_MODE */

#if (CRC_16_MODE != STD_OFF)
/*******************************************************************************
** Traceability     : [cover parentID={3F6E6BD8-18DD-466d-8CEC-0178A138E548}] **
**                                                                            **
** Syntax           : uint16 Crc_CalculateCRC16                               **
**                    (                                                       **
**                     const uint8* const Crc_DataPtr,                        **
**                     const uint32 Crc_Length,                               **
**                     const const uint16 Crc_StartValue16,                   **
**                     const boolean Crc_IsFirstCall                          **
**                    )                                                       **
**                                                                            **
** Description      : This function takes the value of input data pointer,    **
**                    start value and polynomial, calculates the crc taking   **
**                    the precomputed                                         **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x02                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : Crc_DataPtr  - Pointer to the start of the datablock    **
**                    Crc_Length - Length of the input data to be fetched     **
**                    Crc_StartValue16 -Start value for CRC Calculation       **
**                    Crc_IsFirstCall -Boolean to decIDe the start value      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : 16-bit result of CRC calculation                        **
**                                                                            **
*******************************************************************************/
uint16 Crc_CalculateCRC16
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint16 Crc_StartValue16,
  const boolean Crc_IsFirstCall
)
{
  uint16 Result = CRC_NOT_SUCCESS;
  uint16 StartValue16;

  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * this MISRA rule. Union usage is required for bitwise access to the 32-bit
   * Crc_ConfigParams_Bits structure. */
  Crc_ConfigParam Parameters_Crc16;
  /* [cover parentID={4ED98803-4132-427e-A4A0-0FA8A3604173}]
   * If safety check is enabled
   * [/cover] */
  #if (CRC_SAFETYENABLE == STD_ON)

  uint8 SafetyResult;
  /* [cover parentID={D4922D8D-40CD-4757-A43F-348750B56B6A}]
   * Set CRC result to configured error value
   * [/cover] */
  Result = (uint16)CRC_16_CONFIGERROR_VAL;
  /* [cover parentID={BD02F69C-CF6C-407a-AEE4-CB96B0ED616D}]
   * Check Mcal Safety error
   * [/cover] */
  SafetyResult = Crc_lSafetyChecks(Crc_DataPtr, CRC_SID_CALCULATE_CRC16, Crc_Length);

  /* if all the checks are done successfully*/
  /* [cover parentID={4177D422-04EC-4854-BD19-6741EA43DEFC}]
   * If the return value is CRC_SUCCESS
   * [/cover] */
  if(SafetyResult == CRC_SUCCESS)
  #endif
  {
    /* Configuration for 8 bit CRC calculation*/
    /* [cover parentID={37332445-2CC8-4ad0-96FC-F938321A169D}]
     * Configure Parameters_Crc16 variable for data width, bitorder, logical
     * inversion, crc width and polynomial
     * [/cover] */
    Parameters_Crc16.B.IpDataWidth = 7;
    Parameters_Crc16.B.Unused1=0;
    Parameters_Crc16.B.IpDataBitOrder = 0;
    Parameters_Crc16.B.LogicalInversion = 0;
    Parameters_Crc16.B.Unused2=0;
    Parameters_Crc16.B.CrcWidth = 15;
    Parameters_Crc16.B.Polynomial = CRC_CRC16_POLYNOMIAL;

    /* Is this the first call to compute the CRC? */
    /* [cover parentID={DFDBB853-2041-4c42-8058-7A1F9E045D0C}]
     * Is this first call?
     * [/cover] */
    if(Crc_IsFirstCall == (boolean)TRUE)
    {
      /* [cover parentID={196FE552-C102-48f7-AF14-D5A969C3217A}]
       * Set Start Value to Initial value for 16 bit CRC
       * [/cover] */
      StartValue16 = (uint16)CRC_INITIAL_VALUE16;
    }
    else
    {
      /* [cover parentID={35B77A4E-5652-4961-90A2-8C4825B849AF}]
       * XOR Start Value with XOR Value for the 16 bit CRC
       * [/cover] */
      StartValue16 = Crc_StartValue16 ^ CRC_CRC16_XOR_VALUE;
    }
    /* Crc_lCRCN function is called for the calculation by CRCN instruction*/
    /* [cover parentID={FA47C97D-702A-436c-BFEF-7751E2DD9681}]
     * Calculate CRC
     * [/cover] */
    StartValue16 = Crc_lCRCN(Crc_DataPtr, Crc_Length, StartValue16, Parameters_Crc16.U);

    /* [cover parentID={F024D8F1-503B-4879-9E24-445A98451F22}]
     * XOR Start Value with XOR Value for the 16 bit CRC
     * [/cover] */
    Result = StartValue16 ^ CRC_CRC16_XOR_VALUE;
  }
  return Result;
}

#endif
/* #if CRC_16_MODE */

#if (CRC_16ARC_MODE != STD_OFF)
/*******************************************************************************
** Traceability     : [cover parentID={713A7A03-30F0-41a9-8A0A-EB9FD7F794C3}] **
**                                                                            **
** Syntax           : uint16 Crc_CalculateCRC16ARC                            **
**                    (                                                       **
**                     const uint8* const Crc_DataPtr,                        **
**                     const uint32 Crc_Length,                               **
**                     const const uint16 Crc_StartValue16ARC,                **
**                     const boolean Crc_IsFirstCall                          **
**                    )                                                       **
**                                                                            **
** Description      : This function takes the value of input data pointer,    **
**                    start value and polynomial, calculates the crc taking   **
**                    the precomputed                                         **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x08                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : Crc_DataPtr  - Pointer to the start of the datablock    **
**                    Crc_Length - Length of the input data to be fetched     **
**                    Crc_StartValue16 -Start value for CRC Calculation       **
**                    Crc_IsFirstCall -Boolean to decIDe the start value      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : 16-bit result of CRC calculation                        **
**                                                                            **
*******************************************************************************/
uint16 Crc_CalculateCRC16ARC
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint16 Crc_StartValue16,
  const boolean Crc_IsFirstCall
)
{
  uint16 Result = CRC_NOT_SUCCESS;
  uint16 StartValue16;
  uint16 TempVal;
  uint32 LoopCounter;

  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * this MISRA rule. Union usage is required for bitwise access to the 32-bit
   * Crc_ConfigParams_Bits structure. */
  Crc_ConfigParam Parameters_Crc16ARC;
  /* [cover parentID={B2047D69-F8FA-458d-B712-28B6057622B3}]
   * If safety check is enabled
   * [/cover] */
  #if (CRC_SAFETYENABLE == STD_ON)

  uint8 SafetyResult;
  /* [cover parentID={77E8E9CA-3440-4ca2-8777-60A46C5FA84C}]
   * Set CRC result to configured error value
   * [/cover] */
  Result = (uint16)CRC_16ARC_CONFIGERROR_VAL;

  /* [cover parentID={61D912E4-6F44-499f-B0BB-7D7520FDF47A}]
   * Check Mcal Safety error
   * [/cover] */
  SafetyResult = Crc_lSafetyChecks(Crc_DataPtr, CRC_SID_CALCULATE_CRC16ARC, Crc_Length);

  /* if all the checks are done successfully*/
  /* [cover parentID={67E3490D-9BE7-43dd-BFAA-B9ADE3483B99}]
   * If the return value is CRC_SUCCESS
   * [/cover] */
  if(SafetyResult == CRC_SUCCESS)
  #endif
  {
    /* Configuration for 8 bit CRC calculation*/
    /* [cover parentID={9FEB5DDC-7966-4671-AD7C-79CF07BE2E89}]
     * Configure Parameters_Crc16 variable for data width, bitorder, logical
     * inversion, crc width and polynomial
     * [/cover] */
    Parameters_Crc16ARC.B.IpDataWidth = 7;
    Parameters_Crc16ARC.B.Unused1=0;
    Parameters_Crc16ARC.B.IpDataBitOrder = 0;
    Parameters_Crc16ARC.B.LogicalInversion = 0;
    Parameters_Crc16ARC.B.Unused2=0;
    Parameters_Crc16ARC.B.CrcWidth = 15;
    Parameters_Crc16ARC.B.Polynomial = CRC_CRC16ARC_POLYNOMIAL;

    /* Is this the first call to compute the CRC? */
    /* [cover parentID={B2734BAD-4116-4c46-9346-DCA931529CCE}]
     * Is this first call?
     * [/cover] */
    if(Crc_IsFirstCall == (boolean)TRUE)
    {
      /* [cover parentID={F505343D-0864-4361-B75B-50E34B4E78B2}]
       * Set Start Value to Initial value for 16ARC bit CRC
       * [/cover] */
      StartValue16 = (uint16)CRC_INITIAL_VALUE16ARC;
    }
    else
    {
      /* XOR the Start Value with the XOR value for CRC16ARC */
      StartValue16 = Crc_StartValue16 ^ CRC_CRC16ARC_XOR_VALUE;
      /* Do a 16 bit reflection of the XORed value */
      /* [cover parentID={B723E252-CFCD-4db7-AA13-B9DC7C04B676}]
       * XOR the Start Value with the XOR value for CRC16ARC and reflected
       * [/cover] */
      StartValue16 = (uint16)(Crc_lCommonReflect(StartValue16,
                                 CRC_BITCNT_SIXTEEN));
    }
    /* [cover parentID={55E7C810-AA82-407d-9A11-2C5E4D3ED1C4}]
     * CCall the CPU instruction: CRCN
     * [/cover] */
    for (LoopCounter = 0U; LoopCounter < Crc_Length; LoopCounter++)
    {
      /* [cover parentID={5CBB09F9-FBA6-42dc-90AB-D02BEC5D3E4D}]
       * Reflect the input data
       * [/cover] */
      TempVal = (uint16)Crc_lCommonReflect(Crc_DataPtr[LoopCounter],
                                  CRC_BITCNT_EIGHT);
      /* Loop througgh each data byte to calculate CRC */
      /* [cover parentID={F938FBC9-F9BD-4c30-9C47-661CC28F0931}]
       * Call the CRCN CPU instrinsic instruction
       * [/cover] */
      /* MISRA2012_RULE_10_3_JUSTIFICATION: Expression assigned to different
       * essential type and data lose cannot occur since both types are 32bit length.
       * No side effects foreseen by violating this MISRA rule. */
      StartValue16 = CRCN(Parameters_Crc16ARC.U, StartValue16, TempVal);
    }
    /* [cover parentID={D00F6E90-B8A4-4d68-BC4F-730BF7698E24}]
     *  Reflect the StartValue and assign to result
     * [/cover] */
    StartValue16 = (uint16)Crc_lCommonReflect(StartValue16, CRC_BITCNT_SIXTEEN);

    Result = StartValue16;
  }

  return Result;
}
#endif
/* #if CRC_16ARC_MODE */

#if (CRC_32_MODE != STD_OFF)
/*******************************************************************************
** Traceability     : [cover parentID={468B97AE-C2C7-40f3-80D9-99053101EBBA}] **
** Syntax           : uint32 Crc_CalculateCRC32                               **
**                    (                                                       **
**                     const uint8* const Crc_DataPtr,                        **
**                     const uint32 Crc_Length,                               **
**                     const uint32 Crc_StartValue32,                         **
**                     const boolean Crc_IsFirstCall                          **
**                    )                                                       **
**                                                                            **
** Description      : This function takes the value of input data pointer,    **
**                    start value and polynomial, calculates the crc taking   **
**                    the precomputed and reversed xor value  and returns     **
**                    the CRC xored with XOR value                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x03                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Re-entrant                                              **
**                                                                            **
** Parameters(in)   : Crc_DataPtr  - Pointer to the start of the datablock    **
**                    Crc_Length - Length of the input data to be fetched     **
**                    Crc_StartValue32 -Start value for CRC Calculation       **
**                    Crc_IsFirstCall -Boolean to decIDe the start value      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : 32-bit result of CRC calculation                        **
**                                                                            **
*******************************************************************************/
uint32 Crc_CalculateCRC32
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint32 Crc_StartValue32,
  const boolean Crc_IsFirstCall
)
{
  uint32 Result = CRC_NOT_SUCCESS;
  uint32 LoopCounter;
  uint32 StartValue32;
  /* [cover parentID={1FC5CE90-74F1-4a50-849B-BA1A30246F32}]
   * If safety check is enabled
   * [/cover] */
  #if (CRC_SAFETYENABLE == STD_ON)

  uint8 SafetyResult;
  /* [cover parentID={84E27FEF-B84D-4614-AD39-4FF12A2CC560}]
   * Set CRC result to configured error value
   * [/cover] */
  Result = (uint32)CRC_32_CONFIGERROR_VAL;
  /* Error checks for input data pointer and input data length*/
  /* [cover parentID={BCDF0891-1466-4ffd-A3F6-D93C69C32A1C}]
   * Check Mcal Safety Error
   * [/cover] */
  SafetyResult = Crc_lSafetyChecks(Crc_DataPtr, CRC_SID_CALCULATE_CRC32, Crc_Length);
  /* [cover parentID={F5066267-4C41-4534-875A-2D1A64A9F67C}]
   * If the return value is E_OK
   * [/cover] */
  if(SafetyResult == CRC_SUCCESS)
  #endif
  {
    /* [cover parentID={2DEC93AE-ABFF-40d9-8266-12C57931AF4D}]
     * Check if this is first call
     * [/cover] */
    if(Crc_IsFirstCall == (boolean)TRUE)
    {
      /* If it is a first call, than the Startvalue is set to 0x00 as the
       * CRC32 instruction internally XOR the value and reflects making
       * it 0xFFFFFFFF, which is the initial value for CRC32 calculation.*/
      /* [cover parentID={0C409C70-1FD8-4b85-9673-E6927D50690F}]
       * Set Start Value to 0x00
       * [/cover] */
      StartValue32 = ((uint32)0x0U);
    }
    else
    {
      /* If is it not the first call than the start value is cofigured
       * with the previous start value */
      /* [cover parentID={08456C2D-8CCA-42df-982B-9BED270CE428}]
       * Assign the start value with the value passed as the parameter in
       * the API call
       * [/cover] */
      StartValue32 = Crc_StartValue32;
    }
    /* loop through each data byte to calculate CRC by calling CRC32
     * CPU instruction*/
    /* [cover parentID={94A7096F-5799-4d11-A57B-33024F1694C5}]
     * Call CPU instruction
     * [/cover] */
    for (LoopCounter = 0U; LoopCounter < Crc_Length;
         LoopCounter++)
    {
      /* [cover parentID={F5947583-F5E8-4d69-AAEC-AFA1C934AAC2}]
       * Call the CRC32 instruction and update the start value
       * [/cover] */
      /* CRC32 is an instruction which takes only initial value and input data as
       * an input.
       * The CRC polynomial used is CRC 32 IEEE 802.3 standard.
       *  The CRC result produced is bit reflected and inverted. */
      StartValue32 = CRC32B(StartValue32, Crc_DataPtr[LoopCounter]);
    }

    Result = StartValue32;
  }
  return Result;
}
#endif
/*#if (CRC_32_MODE != STD_OFF)*/

#if (CRC_32P4_MODE != STD_OFF)
/*******************************************************************************
** Traceability     : [cover parentID={9863DB3E-9C70-4c80-8426-6DA9015F5426}] **
** Syntax           : uint32 Crc_CalculateCRC32P4                             **
**                    (                                                       **
**                     const uint8* const Crc_DataPtr,                        **
**                     const uint32 Crc_Length,                               **
**                     const uint32 Crc_StartValue32,                         **
**                     const boolean Crc_IsFirstCall                          **
**                    )                                                       **
**                                                                            **
** Description      : This function takes the value of input data pointer,    **
**                    tart value and polynomial, calculates the crc taking    **
**                    the precomputed and reversed xor value  and returns     **
**                    the CRC xored with XOR value                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x06                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : reentrant                                               **
**                                                                            **
** Parameters(in)   : rc_DataPtr  - Pointer to the start of the datablock     **
**                    Crc_Length - Length of the input data to be fetched     **
**                    Crc_StartValue32 -Start value for CRC Calculation       **
**                    Crc_IsFirstCall -Boolean to decIDe the start value      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : 32-bit result of CRC calculation                        **
**                                                                            **
*******************************************************************************/
uint32 Crc_CalculateCRC32P4
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint32 Crc_StartValue32,
  const boolean Crc_IsFirstCall
)
{
  uint32 Result = CRC_NOT_SUCCESS;
  /* [cover parentID={6DA28B32-2C6C-47a5-AFB0-B3BF841EE438}]
   * If safety check is enabled
   * [/cover] */
  #if (CRC_SAFETYENABLE == STD_ON)

  uint8 SafetyResult;
  /* [cover parentID={67B05D14-F3FF-4af0-A69F-67915E4EB85E}]
   * Set CRC result to configured error value
   * [/cover] */
  Result = (uint32)CRC_32P4_CONFIGERROR_VAL;
  /* Error checks for input data pointer and input data length*/
  /* [cover parentID={53F99091-ED6E-45ae-8DE1-F1D1CE47539A}]
   * Check Mcal Safety Error
   * [/cover] */
  SafetyResult = Crc_lSafetyChecks(Crc_DataPtr, CRC_SID_CALCULATE_CRC32P4, Crc_Length);
  /* [cover parentID={9000079A-ECAA-4599-BC58-C8EC0C6A7C93}]
   * If the return value is E_OK
   * [/cover] */
  if(SafetyResult == CRC_SUCCESS)
  #endif
  {
    /* [cover parentID={FD081521-784E-4a20-9ECF-4975D7955124}]
    Check the configured mode for CRC calculation [/cover] */
    /* Depending on the chosen mode, the CRC would be calculated
     * using the runtime/table/hardware method. */
    /* [cover parentID={5B7FA068-8DB1-4a36-A496-BCF0C41302C2}]
    If configured mode is RunTime method [/cover] */
    #if  (CRC_32P4_MODE == CRC_RUNTIME_MODE)
    /* [cover parentID={43B98E8C-12B5-49b3-9FD1-CE2DF2A96254}]
    Calculate CRC using Runtime mode
    [/cover] */
    /* Lets calculate the CRC using the runtime method */
    Result = Crc_lCalculateCRC32P4Runtime( Crc_DataPtr, Crc_Length,
                                           Crc_StartValue32, Crc_IsFirstCall);

    /* [cover parentID={FE9879B7-A3CF-46d5-9BE2-45F4ADA34D2F}]
    If configured mode is Table method
    [/cover] */
    #elif (CRC_32P4_MODE == CRC_TABLE_MODE)
    /* [cover parentID={B7D19CE1-3FEA-417e-890C-8D4F5094D4FB}]
    Calculate CRC using Table mode
    [/cover] */
    /* Lets calculate the CRC using the table method */
    Result = Crc_lCalculateCRC32P4Table( Crc_DataPtr, Crc_Length,
                                         Crc_StartValue32, Crc_IsFirstCall);
    #endif
  }
  return Result;
}
#endif
/*#if (CRC_32P4_MODE != STD_OFF)*/


#if (CRC_64_MODE != STD_OFF)
/*******************************************************************************
** Traceability     : [cover parentID={6DF0AA3B-B4D7-4b2d-9DCF-9EFF69B09654}] **
**                                                                            **
** Syntax           : uint64 Crc_CalculateCRC64                               **
**                    (                                                       **
**                     const uint8* const Crc_DataPtr,                        **
**                     const uint32 Crc_Length,                               **
**                     const uint64 Crc_StartValue64,                         **
**                     const boolean Crc_IsFirstCall                          **
**                    )                                                       **
**                                                                            **
** Description      : This function takes the value of input data pointer,    **
**                    start value and polynomial, calculates the crc taking   **
**                    the precomputed and reversed xor value  and returns the **
**                    CRC xored with XOR value                                **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x07                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : Crc_DataPtr  - Pointer to the start of the datablock    **
**                    Crc_Length - Length of the input data to be fetched     **
**                    Crc_StartValue64 -Start value for CRC Calculation       **
**                    Crc_IsFirstCall -Boolean to decIDe the start value      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : 64 bit result of CRC calculation.                       **
**                                                                            **
*******************************************************************************/
uint64 Crc_CalculateCRC64
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint64 Crc_StartValue64,
  const boolean Crc_IsFirstCall
)
{
  uint64 Result = CRC_NOT_SUCCESS;
  /* [cover parentID={28EE4A0B-D08B-4e88-88B1-69DEAEB11FE6}]
   * If safety check is enabled
   * [/cover] */
  #if (CRC_SAFETYENABLE == STD_ON)

  uint8 SafetyResult;
  /* [cover parentID={8499468B-37E3-4054-B4A2-007519DBA6D1}]
   * Set CRC result to configured error value
   * [/cover] */
  Result = (uint64)CRC_64_CONFIGERROR_VAL;
  /* Error checks for input data pointer and input data length*/
  /* [cover parentID={D88B3979-5030-4e48-899E-1D73D89CD8B5}]
   * Check Mcal Safety Error
   * [/cover] */
  SafetyResult = Crc_lSafetyChecks(Crc_DataPtr, CRC_SID_CALCULATE_CRC64, Crc_Length);
  /* [cover parentID={29F0DEE7-2968-453b-B92C-FCC2B94779D7}]
   * If the return value is E_OK
   * [/cover] */
  if(SafetyResult == CRC_SUCCESS)
  #endif
  {
    /* [cover parentID={75AB1979-9F25-468f-ABBF-ACF10ED95CE5}]
     * Check the configured mode for CRC calculation [/cover] */
    /* Depending on the chosen mode, the CRC would be calculated
     * using the runtime/table/hardware method. */
    /* [cover parentID={60CFDD90-E2AD-40da-8A50-37D733D277BB}]
    If configured mode is RunTime method [/cover] */
    #if  (CRC_64_MODE == CRC_RUNTIME_MODE)
    /* [cover parentID={C83BE8D2-A3FD-40f2-8ED0-BA1E4DB023C1}]
     * Calculate CRC using Runtime mode
     * [/cover] */
    /* Lets calculate the CRC using the runtime method */
    Result = Crc_lCalculateCRC64Runtime( Crc_DataPtr, Crc_Length,
                                           Crc_StartValue64, Crc_IsFirstCall);

    /* [cover parentID={0CFE978A-2E58-40a8-9D99-C45E3C2B9D3E}]
     * If configured mode is Table method
     * [/cover] */
    #elif (CRC_64_MODE == CRC_TABLE_MODE)
    /* [cover parentID={3179417A-4A9C-459b-BA59-11E356352B91}]
     * Calculate CRC using Table mode
     * [/cover] */
    /* Lets calculate the CRC using the table method */
    Result = Crc_lCalculateCRC64Table( Crc_DataPtr, Crc_Length,
                                         Crc_StartValue64, Crc_IsFirstCall);
    #endif
  }
  return Result;
}
#endif
/*#if (CRC_64_MODE != STD_OFF)*/

#if (CRC_8_DMAMODE == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={6889B7C1-7101-4fb7-8D00-A730727B4957}] **
**                                                                            **
** Syntax           : Crc_DmaReturnType Crc_DmaCalculateCRC8                  **
**                      (                                                     **
**                          const uint8* const Crc_DataPtr,                   **
**                          const uint32 Crc_Length,                          **
**                          const uint8 Crc_StartValue8,                      **
**                          const boolean Crc_IsFirstCall                     **
**                      )                                                     **
**                                                                            **
** Description      : This function takes the value of input data pointer,    **
**                    input length, start value and first call, do the        **
**                    checks on the parameter, configure FCE clock calls      **
**                    the the local function the local function to update     **
**                    the configuration of DMA channel.                       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x1A                                                    **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant for different channels                        **
**                    (Non- Reentrant for same channel)                       **
**                                                                            **
** Parameters(in)   : Crc_DataPtr  - Pointer to the start of the datablock    **
**                    Crc_Length - Length of the input data to be fetched     **
**                    Crc_StartValue8 -Start value for CRC Calculation        **
**                    Crc_IsFirstCall -Boolean to decIDe the start value      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : CRC_INVALID_CORE: If the current executing core does    **
**                    not have FCE and DMA channel allocated to it.           **
**                    CRC_INVALID_POINTER: If the data pointer is NULL        **
**                    CRC_INVALID_LENGTH:In case,                             **
**                     a. If the length of the input data is zero.            **
**                     b. If the length of the input data exceeds             **
**                        16384 bytes.                                        **
**                    CRC_CHANNEL_BUSY: If the channel is busy.               **
**                    CRC_OK: If all the checks are successful.               **
**                                                                            **
*******************************************************************************/
Crc_DmaReturnType Crc_DmaCalculateCRC8
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint8 Crc_StartValue8,
  const boolean Crc_IsFirstCall
)
{
  Crc_DmaReturnType Result = CRC_CHANNEL_BUSY;
  /*assign the base address of FCE*/
  Ifx_FCE *FCERegBaseAddress = &MODULE_FCE;
  uint8 StartValue8 = Crc_StartValue8;
  uint32 CurrentCoreId;
  uint32 LockReturnValue;
  uint8 FceChannel;
  uint8 DmaChannel;

  /* Get the current core ID */
  CurrentCoreId = Mcal_GetCpuIndex();
  /* [cover parentID={AB735DE8-119F-4a1f-8EFC-015B7C58B734}]
   * If safety check is enabled
   * [/cover] */
  #if (CRC_SAFETYENABLE == STD_ON)

  Crc_DmaReturnType SafetyResult;
  /* [cover parentID={DEC93AE8-D8BC-4257-927A-10896236162B}]
   * Check Mcal Safety Error
   * [/cover] */
  SafetyResult = Crc_lDmaSafetyChecks(Crc_DataPtr, 1U, Crc_Length, CurrentCoreId);
  /* [cover parentID={311F4491-ADE4-4e13-9C32-9D477610B109}]
  If the return value is CRC_OK
  [/cover] */
  if(SafetyResult != CRC_OK)
  {
    /* [cover parentID={3D1E0D80-A8E5-4130-AE9B-3BF983571510}]
     * Set the result equal to return value from Crc_lSafetyChecks
     * [/cover] */
    Result = SafetyResult;
  }
  /* [cover parentID={311F4491-ADE4-4e13-9C32-9D477610B109}]
   * If the return value is CRC_OK
   * [/cover] */
  else
  #endif
  {
    /* [cover parentID={95A4DE4D-560D-4927-AD6F-DC169BF5E5AC}]
     * Get and update the status of the DMA channel by calling Mcal_CmpAndSwap CPU instruction
     * [/cover] */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: No side effects
     * foreseen by violating this MISRA rule, as the pointer to the
     * object type it is getting cast into is a known type. */
    /* MISRA2012_RULE_11_5_JUSTIFICATION: Intrinsic function used for
     * compare swap which require pointer conversion, no side effect seen
     * as pointer passed is always 32-bit aligned */
    LockReturnValue = Mcal_CmpAndSwap(Crc_DmaBusyFlag[CurrentCoreId], CRC_DMACH_BUSY, CRC_DMACH_FREE);

    /* [cover parentID={59DC8CED-2783-4787-9084-F752769C42B1}]
     * if the DMA channel assigned to the core is free
     * [/cover]
     */
    if( LockReturnValue == (uint32)CRC_DMACH_FREE)
    {
      FceChannel = Crc_ChannelConfig[CurrentCoreId]->Fce_Channel;
      DmaChannel = Crc_ChannelConfig[CurrentCoreId]->Dma_Channel;

      /* The FCE needs to be enabled
       */
      CRC_LIB_RUNTIME_WRITEPERIPENDINITPROTREG
      (&FCERegBaseAddress->CLC.U, CRC_CLC_INITVAL);

      /* Perform the init for the CFG registers */
      CRC_LIB_RUNTIME_WRITEPERIPENDINITPROTREG( \
          &FCERegBaseAddress->IN[FceChannel].CFG.U, CRC8_CFGREG_INITVAL);

      /* Is this the first call to compute the CRC? */
      /* [cover parentID={63C0E7C0-8B33-4b08-B6F7-C1005CED09D4}]
      Is this first call?
      [/cover] */
      if (Crc_IsFirstCall == (boolean)TRUE)
      {
        /* Load the CRC register with Initial CRC Value */
        /* [cover parentID={B7BEFA59-57B3-4fd5-8862-C4936D5C8F43}]
         * Update the IR register with initial value
         * [/cover] */
        FCERegBaseAddress->IN[FceChannel].CRC.U = CRC_INITIAL_VALUE8;
      }
      else
      {
        /* XOR the Start Value and Load this value to the  CRC register */
        StartValue8 = (uint8)(StartValue8 ^ CRC_CRC8_XOR_VALUE);
        /* [cover parentID={7D1D5191-329D-4816-B527-F4E127C6BA32}]
         * Update the IR register with previous start value
         * [/cover] */
        FCERegBaseAddress->IN[FceChannel].CRC.U = StartValue8;
      }
      /* [cover parentID={5EDC9559-AAFE-40ed-83EE-B595FEC03EF3}]
       * Update the DMA channel Configuration
       * [/cover] */
      /* MISRA2012_RULE_11_4_JUSTIFICATION: Typecast to be done for the source
       * address and destination address for the DMA channel configuration*/
      /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from pointer to unsigned long
       * is required for the destination address in DMA channel configuration. */
      Crc_lDmaChUpdateTransfer(CRC_DMA_8_CHCFGR, DmaChannel, Crc_Length, \
            (uint32)Crc_DataPtr,(uint32)&FCERegBaseAddress->IN[FceChannel].IR.U);

      /* return the status of the API*/
      Result = CRC_OK;
    }
  }
  return Result;
}
#endif
/*#if (CRC_8_DMAMODE != STD_OFF)*/

#if (CRC_16_DMAMODE != STD_OFF)
/*******************************************************************************
** Traceability     : [cover parentID={865F0B27-81C5-4cb0-8328-D1C3F238C992}] **
**                                                                            **
** Syntax           : Crc_DmaReturnType Crc_DmaCalculateCRC16                 **
**                      (                                                     **
**                          const uint8* const Crc_DataPtr,                   **
**                          const uint32 Crc_Length,                          **
**                          const uint16 Crc_StartValue16,                    **
**                          const boolean Crc_IsFirstCall                     **
**                      )                                                     **
**                                                                            **
** Description      : This function takes the value of input data pointer,    **
**                    input length, start value and first call, do the        **
**                    checks on the parameter, configure FCE clock calls      **
**                    the the local function the local function.              **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x1B                                                    **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant for different channels                        **
**                    (Non- Reentrant for same channel)                       **
**                                                                            **
** Parameters(in)   : Crc_DataPtr  - Pointer to the start of the datablock    **
**                    Crc_Length - Length of the input data to be fetched     **
**                    Crc_StartValue16 -Start value for CRC Calculation       **
**                    Crc_IsFirstCall -Boolean to decIDe the start value      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : CRC_INVALID_CORE: If the current executing core does    **
**                    not have FCE and DMA channel allocated to it.           **
**                    CRC_INVALID_POINTER: If the data pointer is NULL        **
**                    CRC_INVALID_LENGTH: In case,                            **
**                     a. If the length of the input data is zero.            **
**                     b. If the length of the input data exceeds             **
**                        16384 bytes.                                        **
**                     c. If the input data stream is not aligned to 16-bit   **
**                        word boundary.                                      **
**                    CRC_INVALID_ADDRESS: If the address of the data pointer **
**                    does not align to 16-bit address boundary.              **
**                    CRC_CHANNEL_BUSY: If the channel is busy.               **
**                    CRC_OK: If all the checks are successful.               **
**                                                                            **
*******************************************************************************/
Crc_DmaReturnType Crc_DmaCalculateCRC16
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint16 Crc_StartValue16,
  const boolean Crc_IsFirstCall
)
{
  Crc_DmaReturnType Result = CRC_CHANNEL_BUSY;
  /*assign the base address of FCE*/
  Ifx_FCE *FCERegBaseAddress = &MODULE_FCE;
  uint16 StartValue16 = Crc_StartValue16;
  uint32 CurrentCoreId;
  uint32 LockReturnValue;
  uint8 FceChannel;
  uint8 DmaChannel;
  uint32 AlignedLength;

  /* Get the current core ID */
  CurrentCoreId = Mcal_GetCpuIndex();

  /* [cover parentID={BB8193FA-52E8-4f3a-B9B4-C4036D0C2C59}]
   * If safety check is enabled
   * [/cover] */
  #if (CRC_SAFETYENABLE == STD_ON)

  Crc_DmaReturnType SafetyResult;
  /* [cover parentID={C2F96601-6F75-495e-9D43-E674668D844F}]
   * Check Mcal Safety Error
   * [/cover] */
  SafetyResult = Crc_lDmaSafetyChecks(Crc_DataPtr,((uint8)CRC_ALIGNLENGTH_16BIT) , Crc_Length, CurrentCoreId);

  /* [cover parentID={49B674ED-C814-4a0d-9908-94BED8E13E65}]
   * If the return value is CRC_OK
   * [/cover] */
  if(SafetyResult != CRC_OK)
  {
    /* [cover parentID={D1EB74F4-88D5-40e7-A987-E2284D7DF49F}]
     * Set the result equal to return value from Crc_lSafetyChecks
     * [/cover] */
    Result = SafetyResult;
  }
  /* [cover parentID={49B674ED-C814-4a0d-9908-94BED8E13E65}]
   * If the return value is CRC_OK
   * [/cover] */
  else
  #endif
  {
    /* [cover parentID={891B4138-5D5A-4b3e-B172-9606E2DE14EF}]
     * Get and update the status of the DMA channel by calling Mcal_CmpAndSwap CPU instruction
     * [/cover]  */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: No side effects
     * foreseen by violating this MISRA rule, as the pointer to the
     * object type it is getting cast into is a known type. */
    /* MISRA2012_RULE_11_5_JUSTIFICATION: Intrinsic function used for
     * compare swap which require pointer conversion, no side effect seen
     * as pointer passed is always 32-bit aligned */
    LockReturnValue = Mcal_CmpAndSwap(Crc_DmaBusyFlag[CurrentCoreId], CRC_DMACH_BUSY, CRC_DMACH_FREE);

    /* [cover parentID={62518211-63F0-4db5-A38E-7C0B53CF934D}]
     * if the DMA channel assigned to the core is free
     * [/cover] */
    if( LockReturnValue == (uint32)CRC_DMACH_FREE)
    {
      FceChannel = Crc_ChannelConfig[CurrentCoreId]->Fce_Channel;
      DmaChannel = Crc_ChannelConfig[CurrentCoreId]->Dma_Channel;
      /* The FCE needs to be enabled       */
      CRC_LIB_RUNTIME_WRITEPERIPENDINITPROTREG
      (&FCERegBaseAddress->CLC.U, CRC_CLC_INITVAL);

      /* Perform the init for the CFG registers */
      CRC_LIB_RUNTIME_WRITEPERIPENDINITPROTREG( \
          &FCERegBaseAddress->IN[FceChannel].CFG.U, CRC16_CFGREG_INITVAL);
      /* Is first Call ? */
      /* Is this the first call to compute the CRC? */
      /* [cover parentID={E40A9FE1-070F-4c66-A350-0C404F10CDAB}]
       * Is this first call?
       * [/cover] */
      if (Crc_IsFirstCall == (boolean)TRUE)
      {
        /* Load the CRC register with Initial CRC Value */
        /* [cover parentID={14F612EE-F526-433e-B9F7-30267B5623DD}]
         * Update the IR register with initial value
         * [/cover] */
        FCERegBaseAddress->IN[FceChannel].CRC.U = CRC_INITIAL_VALUE16;
      }
      else
      {
        /* XOR the Start Value and Load this value to the  CRC register */
        StartValue16 = StartValue16 ^ CRC_CRC16_XOR_VALUE;
        /* [cover parentID={803268B5-2A3D-4134-AC50-BF3A400BA18E}]
         * Update the IR register with the start value
         * [/cover] */
        FCERegBaseAddress->IN[FceChannel].CRC.U = StartValue16;
      }
      /* Calculate move length for the DMA channel*/
      AlignedLength = Crc_Length/CRC_ALIGNLENGTH_16BIT;

      /* [cover parentID={B74EA3C0-DC07-4204-8463-9CA0CCF45C80}]
       * Update the DMA channel Configuration
       * [/cover]
       */
      /* MISRA2012_RULE_11_4_JUSTIFICATION: Typecast to be done for the source
       * address and destination address for the DMA channel configuration*/
      /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from pointer to unsigned long
       * is required for the destination address in DMA channel configuration. */
      Crc_lDmaChUpdateTransfer(CRC_DMA_16_CHCFGR, DmaChannel, AlignedLength, \
            (uint32)Crc_DataPtr, (uint32)&FCERegBaseAddress->IN[FceChannel].IR.U);
      /*return the status of the API*/
      Result = CRC_OK;
    }
  }
  return Result;
}
#endif
/*#if (CRC_16_DMAMODE != STD_OFF)*/

#if (CRC_32_DMAMODE != STD_OFF)
/*******************************************************************************
** Traceability     : [cover parentID={1BC56F07-4435-4bcb-9B1A-FFFA1D3EFF22}] **
**                                                                            **
** Syntax           : Crc_DmaReturnType Crc_DmaCalculateCRC32                 **
**                      (                                                     **
**                          const uint8* const Crc_DataPtr,                   **
**                          const uint32 Crc_Length,                          **
**                          const uint32 Crc_StartValue32,                    **
**                          const boolean Crc_IsFirstCall                     **
**                      )                                                     **
**                                                                            **
** Description      : This function takes the value of input data pointer,    **
**                    input length, start value and first call, do the        **
**                    checks on the parameter, configure FCE clock calls      **
**                    the the local function to update the configuration      **
**                    of DMA channel.                                         **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x1C                                                    **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant for different channels                        **
**                    (Non- Reentrant for same channel)                       **
**                                                                            **
** Parameters(in)   : Crc_DataPtr  - Pointer to the start of the datablock    **
**                    Crc_Length - Length of the input data to be fetched     **
**                    Crc_StartValue32 -Start value for CRC Calculation       **
**                    Crc_IsFirstCall -Boolean to decIDe the start value      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : CRC_INVALID_CORE: If the current executing core does    **
**                    not have FCE and DMA channel allocated to it.           **
**                    CRC_INVALID_POINTER: If the data pointer is NULL        **
**                    CRC_INVALID_LENGTH: In case,                            **
**                     a. If the length of the input data is zero.            **
**                     b. If the length of the input data exceeds             **
**                        16384 bytes.                                        **
**                     c. If the input data stream is not aligned to 32-bit   **
**                        word boundary.                                      **
**                    CRC_INVALID_ADDRESS: If the address of the data         **
**                    pointer does not align to 32-bit address boundary.      **
**                    CRC_CHANNEL_BUSY: If the channel is busy.               **
**                    CRC_OK: If all the checks are successful.               **
**                                                                            **
*******************************************************************************/
Crc_DmaReturnType Crc_DmaCalculateCRC32
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint32 Crc_StartValue32,
  const boolean Crc_IsFirstCall
)
{
  Crc_DmaReturnType Result = CRC_CHANNEL_BUSY;
  /* Assign the base address of FCE*/
  Ifx_FCE *FCERegBaseAddress = &MODULE_FCE;
  uint32 StartValue32 = Crc_StartValue32;
  uint32 CurrentCoreId;
  uint32 LockReturnValue;
  uint8 FceChannel;
  uint8 DmaChannel;
  uint32 AlignedLength;
  uint32 Reflectedword;

  /* Get the current core ID */
  CurrentCoreId = Mcal_GetCpuIndex();
  /* [cover parentID={0829B966-A370-4434-8D28-93D1052B918C}]
   * If safety check is enabled
   * [/cover] */
  #if (CRC_SAFETYENABLE == STD_ON)

  Crc_DmaReturnType SafetyResult;
  /* [cover parentID={3303E1E9-A11C-448c-B9AE-50633B6C66DF}]
   * Check Mcal Safety Error
   * [/cover] */
  SafetyResult = Crc_lDmaSafetyChecks(Crc_DataPtr, \
                              ((uint8)CRC_ALIGNLENGTH_32BIT), Crc_Length, CurrentCoreId);
  /* [cover parentID={FE4720E6-D5BD-4a9d-937E-E74696C3FF7A}]
   * If the return value is CRC_OK
   * [/cover] */
  if(SafetyResult != CRC_OK)
  {
    /* [cover parentID={881F409F-7E75-4d3b-B5E8-D73AB67627F8}]
     * Set the result equal to return value from Crc_lSafetyChecks
     * [/cover] */
    Result = SafetyResult;
  }
  /* [cover parentID={FE4720E6-D5BD-4a9d-937E-E74696C3FF7A}]
   * If the return value is CRC_OK
   * [/cover] */
  else
  #endif
  {
    /* [cover parentID={ABAF7B64-C2B4-49f0-AFBF-8CE8E44EA9A8}]
     * Get and update the status of the DMA channel by calling Mcal_CmpAndSwap CPU instruction
     * [/cover] */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: No side effects
     * foreseen by violating this MISRA rule, as the pointer to the
     * object type it is getting cast into is a known type.  */
    /* MISRA2012_RULE_11_5_JUSTIFICATION: Intrinsic function used for
     * compare swap which require pointer conversion, no side effect seen
     * as pointer passed is always 32-bit aligned */
    LockReturnValue = Mcal_CmpAndSwap(Crc_DmaBusyFlag[CurrentCoreId], CRC_DMACH_BUSY, CRC_DMACH_FREE);

    /* [cover parentID={926466A5-98A3-4c50-BFEB-21324216B46F}]
     * if the DMA channel assigned to the core is free
     * [/cover] */
    if( LockReturnValue == (uint32)CRC_DMACH_FREE)
    {
      FceChannel = Crc_ChannelConfig[CurrentCoreId]->Fce_Channel;
      DmaChannel = Crc_ChannelConfig[CurrentCoreId]->Dma_Channel;
      /* The FCE needs to be enabled       */
      CRC_LIB_RUNTIME_WRITEPERIPENDINITPROTREG
      (&FCERegBaseAddress->CLC.U, CRC_CLC_INITVAL);

      /* Perform the init for the CFG registers */
      CRC_LIB_RUNTIME_WRITEPERIPENDINITPROTREG( \
          &FCERegBaseAddress->IN[FceChannel].CFG.U, CRC32_CFGREG_INITVAL);

      /* Is this the first call to compute the CRC? */
      /* [cover parentID={03ED8A6E-1F6F-4068-8728-5065C9ADA472}]
       * Is this first call?
       * [/cover] */
      if (Crc_IsFirstCall == (boolean)TRUE)
      {
        /* Load the CRC register with Initial CRC Value*/
        /* [cover parentID={00E2E14C-4CD9-4f76-A259-B0F95E1B67B2}]
         * Update the IR register with initial value
         * [/cover] */
        FCERegBaseAddress->IN[FceChannel].CRC.U = CRC_INITIAL_VALUE32;
      }
      else
      {
        /* XOR the Start Value and Load this value to the CRC register */
        StartValue32 = StartValue32 ^ CRC_CRC32_XOR_VALUE;
        /* Do a 32 bit reflection of the XORed value */
        /* [cover parentID={D346AD22-C7DD-4449-B6B0-2C71DB4D2DB0}]
         * Update the IR register with previous start value XORed with XOR
         * value for CRC32P4 and Reflected
         * [/cover] */
        Reflectedword = (uint32)(Crc_lCommonReflect(StartValue32,
                                 CRC_BITCNT_THIRTYTWO));
        FCERegBaseAddress->IN[FceChannel].CRC.U = Reflectedword;
      }
      /* Calculate move length for the DMA channel*/
      AlignedLength = Crc_Length/CRC_ALIGNLENGTH_32BIT;
      /* [cover parentID={2A09FB53-40CA-4b30-A4C9-BA7F0D9A07C6}]
       * Update the DMA channel Configuration
       * [/cover] */
      /* MISRA2012_RULE_11_4_JUSTIFICATION: Typecast to be done for the source
       * address and destination address for the DMA channel configuration*/
      /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from pointer to unsigned long
       * is required for the destination address in DMA channel configuration. */
      Crc_lDmaChUpdateTransfer(CRC_DMA_32_CHCFGR, DmaChannel, AlignedLength, \
            (uint32)Crc_DataPtr, (uint32)&FCERegBaseAddress->IN[FceChannel].IR.U);
      Result = CRC_OK;
    }
  }
  return Result;
}
#endif
/*#if (CRC_32_DMAMODE != STD_OFF)*/

#if (CRC_32P4_DMAMODE != STD_OFF)
/*******************************************************************************
** Traceability     : [cover parentID={4ADF6188-4FB8-4ca2-8ED3-03D496D4C9C1}] **
**                                                                            **
** Syntax           : Crc_DmaReturnType Crc_DmaCalculateCRC32P4               **
**                      (                                                     **
**                          const uint8* const Crc_DataPtr,                   **
**                          const uint32 Crc_Length,                          **
**                          const uint32 Crc_StartValue32,                    **
**                          const boolean Crc_IsFirstCall                     **
**                      )                                                     **
**                                                                            **
** Description      : This function takes the value of input data pointer,    **
**                    input length, start value and first call, do the        **
**                    checks on the parameter, configure FCE clock calls      **
**                    the the local function to update the configuration      **
**                    of DMA channel.                                         **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x1D                                                    **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant for different channels                        **
**                    (Non- Reentrant for same channel)                       **
**                                                                            **
** Parameters(in)   : Crc_DataPtr  - Pointer to the start of the datablock    **
**                    Crc_Length - Length of the input data to be fetched     **
**                    Crc_StartValue32 -Start value for CRC Calculation       **
**                    Crc_IsFirstCall -Boolean to decIDe the start value      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : CRC_INVALID_CORE: If the current executing core does    **
**                    not have FCE and DMA channel allocated to it.           **
**                    CRC_INVALID_POINTER: If the data pointer is NULL        **
**                    CRC_INVALID_LENGTH: In case,                            **
**                     a. If the length of the input data is zero.            **
**                     b. If the length of the input data exceeds             **
**                        16384 bytes.                                        **
**                     c. If the input data stream is not aligned to 32-bit   **
**                        word boundary.                                      **
**                    CRC_INVALID_ADDRESS: If the address of the data         **
**                    pointer does not align to 32-bit address boundary.      **
**                    CRC_CHANNEL_BUSY: If the channel is busy.               **
**                    CRC_OK: If all the checks are successful.               **
**                                                                            **
*******************************************************************************/
Crc_DmaReturnType Crc_DmaCalculateCRC32P4
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint32 Crc_StartValue32,
  const boolean Crc_IsFirstCall
)
{
  Crc_DmaReturnType Result = CRC_CHANNEL_BUSY;
  /* Assign the base address of FCE*/
  Ifx_FCE *FCERegBaseAddress = &MODULE_FCE;
  uint32 StartValue32P4 = Crc_StartValue32;
  uint32 CurrentCoreId;
  uint32 LockReturnValue;
  uint8 FceChannel;
  uint8 DmaChannel;
  uint32 Reflectedword;
  uint32 AlignedLength;

  /* Get the current core ID */
  CurrentCoreId = Mcal_GetCpuIndex();
  /* [cover parentID={FAEB210A-7062-4275-BC99-86ADBA7BC3C8}]
   * If safety check is enabled
   * [/cover] */
  #if (CRC_SAFETYENABLE == STD_ON)

  Crc_DmaReturnType SafetyResult;
  /* [cover parentID={E337F592-79AB-4b4b-BA48-4A13A8D8E4C6}]
   * Check Mcal Safety Error
   * [/cover] */
  SafetyResult = Crc_lDmaSafetyChecks(Crc_DataPtr, \
                              ((uint8)CRC_ALIGNLENGTH_32BIT), Crc_Length, CurrentCoreId);
  /* [cover parentID={FE4720E6-D5BD-4a9d-937E-E74696C3FF7A}]
   * If the return value is CRC_OK
   * [/cover] */
  if(SafetyResult != CRC_OK)
  {
    /* [cover parentID={4ECE5E6D-4FD5-42e6-8AC1-FDF166F8CBAC}]
     * Set the result equal to return value from Crc_lSafetyChecks
     * [/cover] */
    Result = SafetyResult;
  }
  /* [cover parentID={155FCB4F-0141-4a1e-9C55-55D5D84BED66}]
   * If the return value is CRC_OK
   * [/cover] */
  else
  #endif
  {
    /* [cover parentID={C6C47436-6EFD-46b4-8192-E0710D5F2E93}]
     * Get and update the status of the DMA channel by calling Mcal_CmpAndSwap CPU instruction
     * [/cover] */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: No side effects
     * foreseen by violating this MISRA rule, as the pointer to the
     * object type it is getting cast into is a known type. */
    /* MISRA2012_RULE_11_5_JUSTIFICATION: Intrinsic function used for
     * compare swap which require pointer conversion, no side effect seen
     * as pointer passed is always 32-bit aligned */
    LockReturnValue = Mcal_CmpAndSwap(Crc_DmaBusyFlag[CurrentCoreId], CRC_DMACH_BUSY, CRC_DMACH_FREE);
    /* [cover parentID={35711A48-CA24-478c-AAFC-ED4198168041}]
     * if the DMA channel assigned to the core is free
     * [/cover]  */
    if( LockReturnValue == (uint32)CRC_DMACH_FREE)
    {
      FceChannel = Crc_ChannelConfig[CurrentCoreId]->Fce_Channel;
      DmaChannel = Crc_ChannelConfig[CurrentCoreId]->Dma_Channel;
      /* The FCE needs to be enabled */
      CRC_LIB_RUNTIME_WRITEPERIPENDINITPROTREG
      (&FCERegBaseAddress->CLC.U, CRC_CLC_INITVAL);
      /* Perform the init for the CFG registers */
      CRC_LIB_RUNTIME_WRITEPERIPENDINITPROTREG( \
          &FCERegBaseAddress->IN[FceChannel].CFG.U, CRC32P4_CFGREG_INITVAL);

      /* Is this the first call to compute the CRC? */
      /* [cover parentID={D494EC90-E123-4003-83BD-8DA87AAEC0AB}]
       * Is this first call?
       * [/cover] */
      if (Crc_IsFirstCall == (boolean)TRUE)
      {
        /* Load the CRC register with Initial CRC Value */
        /* [cover parentID={4456A17E-B0E4-4581-B9B9-E9C65CAF6B8B}]
         * Update the IR register with initial value
         * [/cover] */
        FCERegBaseAddress->IN[FceChannel].CRC.U = CRC_INITIAL_VALUE32;
      }
      else
      {
        /* XOR the Start Value and Load this value to the CRC register */
        StartValue32P4 = StartValue32P4 ^ CRC_CRC32P4_XOR_VALUE;
        /* Do a 32 bit reflection of the XORed value */
        /* [cover parentID={4456A17E-B0E4-4581-B9B9-E9C65CAF6B8B}]
         * Update the IR register with previous start value XORed with XOR
         * value for CRC32P4 and Reflected
         * [/cover] */
        Reflectedword = (uint32)(Crc_lCommonReflect(StartValue32P4,
                                 CRC_BITCNT_THIRTYTWO));

        FCERegBaseAddress->IN[FceChannel].CRC.U = Reflectedword;
      }
      /* Calculate move length for the DMA channel*/
      AlignedLength = Crc_Length/CRC_ALIGNLENGTH_32BIT;

      /* [cover parentID={19297D94-A548-48dd-9C29-296455141616}]
       * Update the DMA channel Configuration
       * [/cover] */
      /* MISRA2012_RULE_11_4_JUSTIFICATION: Typecast to be done for the source
       * address and destination address for the DMA channel configuration*/
      /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from pointer to unsigned long
       * is required for the destination address in DMA channel configuration. */
      Crc_lDmaChUpdateTransfer(CRC_DMA_32_CHCFGR, DmaChannel, AlignedLength, \
            (uint32)Crc_DataPtr, (uint32)&FCERegBaseAddress->IN[FceChannel].IR.U);

      /* Update the status of the API and return the value*/
      Result = CRC_OK;
    }
  }
  return Result;
}
#endif
/*#if (CRC_32P4_DMAMODE != STD_OFF)*/

#if ((CRC_SAFETYENABLE == STD_ON) && ((CRC_8_MODE != STD_OFF)||\
 (CRC_8H2F_MODE != STD_OFF) || (CRC_16_MODE != STD_OFF)||\
 (CRC_16ARC_MODE != STD_OFF) || (CRC_32_MODE != STD_OFF)||\
 (CRC_32P4_MODE != STD_OFF) || (CRC_64_MODE != STD_OFF) ))
/*******************************************************************************
** Traceability     : [cover parentID={DAC05029-9FEE-47ec-A8E6-B7F29B6DE460}] **
**                                                                            **
** Syntax           : static uint8 Crc_lSafetyChecks                          **
**                    (                                                       **
**                      const uint8* const Crc_DataPtr,                       **
**                        const uint8  Crc_ApiServiceID,                      **
**                      const uint32 Crc_Length                               **
**                    )                                                       **
**                                                                            **
** Description      : This function takes the data pointer, length of the data**
**                    as an input, checks if the data pointer is not NULL and **
**                    if the data length is not zero.                         **
**                    This function is local to the library module and is not **
**                    for the user of CRC Library                             **
**                                                                            **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : reentrant                                               **
**                                                                            **
** Parameters (in)  : Crc_DataPtr -Data pointer of input data                 **
**                    Crc_ApiServiceID - Service ID of the API which invokes  **
**                    the function                                            **
**                    Crc_Length -Lenght of the input data                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK if no safety error is found,                       **
**                    CRC_E_PARAM_POINTER for NULL_PTR error,                 **
**                    CRC_E_PARAM_LENGTH if the length is zero                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Crc_lSafetyChecks
(
  const uint8* const Crc_DataPtr,
  const uint8  Crc_ApiServiceID,
  const uint32 Crc_Length
)
{
  uint8 Result;
  /* Check for the Null pointer of input data */
  /* [cover parentID={4B87E453-C341-48c8-9631-AEA22CFE16FF}]
   * If the length is NULL
   * [/cover] */
  if(Crc_DataPtr == NULL_PTR)
  {
    /* [cover parentID={0D6B0A51-C54F-4694-97C3-175BA57DA70B}]
     * Update the result to CRC_E_PARAM_POINTER and report Mcal safety error
     * [/cover] */
    Result =  CRC_E_PARAM_POINTER;
    Mcal_ReportSafetyError(CRC_MODULE_ID, CRC_INSTANCE_ID,
                           Crc_ApiServiceID, CRC_E_PARAM_POINTER);
  }
  /* Check on input data length*/
  /* [cover parentID={F67C5DB9-8FA9-4b07-995D-607979A15E89}]
   * If the length is zero
   * [/cover] */
  else if(Crc_Length == 0U)
  {
    /* [cover parentID={4D7371EF-761E-44c4-8429-876737B2A2CE}]
     * Update the result to CRC_E_PARAM_LENGTH and report Mcal safety error
     * [/cover] */
    Result =  CRC_E_PARAM_LENGTH;
    Mcal_ReportSafetyError(CRC_MODULE_ID, CRC_INSTANCE_ID,
                           Crc_ApiServiceID, CRC_E_PARAM_LENGTH);
  }
  /* [cover parentID={2DE31F64-A8A5-485e-8F58-22E8CC3ED9D1}]
   * [/cover] */
  else
  {
    /*The result will be CRC_SUCCESS*/
    Result =  CRC_SUCCESS;
  }
  return Result;
}
#endif
/*#if  ((CRC_8_MODE != STD_OFF)||(CRC_8H2F_MODE != STD_OFF) || \
  (CRC_16_MODE != STD_OFF)|| (CRC_16ARC_MODE != STD_OFF) || \
  (CRC_32_MODE != STD_OFF)||(CRC_32P4_MODE != STD_OFF) ||\
  (CRC_64_MODE != STD_OFF) )*/

#if ((CRC_8_MODE !=STD_OFF) || (CRC_8H2F_MODE != STD_OFF) ||\
 (CRC_16_MODE !=STD_OFF))
/*******************************************************************************
** Traceability     : [cover parentID={C39AD8BB-8E2D-4807-AACA-6D769FEC0189}] **
** Syntax           : uint8 Crc_CalculateCRC8                                 **
**                    (                                                       **
**                        const uint8* const Crc_DataPtr,                     **
**                        const uint32 Crc_Length,                            **
**                        const uint8 Crc_StartValue,                         **
**                        const uint32 Crc_Config                             **
**                    )                                                       **
**                                                                            **
** Description      : This function takes the value of input data pointer,    **
**                    Crc_Length, StartValue, and Crc_Config as the input     **
**                    parameter.For each data byte, the CRCN CPU instruction  **
**                    is invoked.                                             **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : Crc_DataPtr  - Pointer to the start of the datablock    **
**                    Crc_Length - Length of the input data to be fetched     **
**                    Crc_StartValue8 -Start value for CRC Calculation        **
**                    Crc_Config -Configuration value for CRCN instruction    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : Calculated CRC result for the input data.               **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint16 Crc_lCRCN
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint16 Crc_StartValue,
  const uint32 Crc_Config
)
{
  uint16 StartValue = Crc_StartValue;
  uint32 LoopCounter;

  /* [cover parentID={E20D7E22-E0C0-4b76-83F6-1CB8A47EFB2E}]
   * Call the CPU instruction
   * [/cover] */
  for (LoopCounter = 0U; LoopCounter < Crc_Length;
       LoopCounter++)
  {
    /* Loop througgh each data byte to calculate CRC */
    /* [cover parentID={15104D80-5741-4b73-B24B-92DC9F8ACC5E}]
     * Call the CRCN instruction and update the start value
     * [/cover] */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: Expression assigned to different
     * essential type and data lose cannot occur since both types are 32bit length.
     * No side effects foreseen by violating this MISRA rule. */
    StartValue = CRCN(Crc_Config, StartValue, Crc_DataPtr[LoopCounter]);
  }

  return StartValue;
}
#endif
/*#if ((CRC_8_MODE !=STD_OFF) || (CRC_8H2F_MODE != STD_OFF) ||\
 (CRC_16_MODE !=STD_OFF) || (CRC_16ARC_MODE != STD_OFF))*/

#if ((CRC_16ARC_MODE !=STD_OFF) || (CRC_32P4_MODE != STD_OFF) ||\
  (CRC_32_DMAMODE != STD_OFF) ||(CRC_32P4_DMAMODE != STD_OFF) ||\
  (CRC_64_MODE != STD_OFF))
/*******************************************************************************
** Traceability     : [cover parentID={A98176E4-853F-4b26-872D-108AA85EC918}] **
**                                                                            **
** Syntax           : LOCAL_INLINE uint32 Crc_lCommonReflect                  **
**                    (                                                       **
**                      const uint32 CRCData_32bit,                           **
**                      const uint8 CRC_BitCount                              **
**                    )                                                       **
**                                                                            **
** Description      : This function takes the 32bit crc data and length of    **
**                    the data, calculates reverses it and return back.       **
**                    This function is local to the library module and is     **
**                    not for the user of CRC Library                         **
**                                                                            **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : reentrant                                               **
**                                                                            **
** Parameters (in)  : CRCData_32bit -Start value for CRC Calculation          **
**                    CRC_BitCount -Boolean to decide the start value         **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : Return the reversed data                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Crc_lCommonReflect
(
  const uint32 CRCData_32bit,
  const uint8 CRC_BitCount
)
{
  uint32 ReversedData = 0U;
  uint8  MsgBit;
  uint32 Data32bit = CRCData_32bit;

  /* Cycle through each of the bit in the parameter passed to the
   * function and reverse the bits. i.e. after the processing done by
   * this function, the data bits in the result would be in
   * the reverse order. */
  /* [cover parentID={E08E1280-A34E-4aea-B6E3-0308DE51B868}]
   * Reverse the bits and store in a 32bit variable
   * [/cover] */
  for (MsgBit = 0U; MsgBit < CRC_BitCount; MsgBit++)
  {
    /* [cover parentID={C82EF063-235D-4420-A318-2D1F541744C7}]
     * Store the bits in reverse order
     * [/cover] */
    /* Start cycling through each bit of the data */
    if( (Data32bit & 1U) == 1U )
    {
      /* [cover parentID={36CBFCB8-CCF1-4c3d-9FE5-B510BDE1318C}]
       * Write 1 to the corresponding bit so that the bit is stored in
       * reverse order in the variable which will hold the reverse value
       * [/cover] */
      /* If a bit '1' is detected, set the bit at the opposite
       * end of the data so that we can reverse the information. */
      ReversedData |= (uint32)((uint32)1U <<
                               ((CRC_BitCount - 1U) - MsgBit));
    }
    /* Shift the data to the right by one bit */
    Data32bit = (uint32)((uint32)Data32bit >> (uint32)1U);

  }
  return ReversedData;
}
#endif
/* #if((CRC_16ARC_MODE !=STD_OFF) || (CRC_32P4_MODE != STD_OFF) ||\
  (CRC_32_DMAMODE != STD_OFF) ||(CRC_32P4_DMAMODE != STD_OFF) ||\
   (CRC_64_MODE != STD_OFF))*/

#if(CRC_64_MODE !=STD_OFF)
/*******************************************************************************
** Traceability     : [cover parentID={6A5349E1-7B09-42f0-9E13-CA182ED2219A}] **
**                                                                            **
** Syntax           : static uint64 Crc_lReflect64                            **
**                    (                                                       **
**                      const uint64 CRCData_64bit,                           **
**                      const uint8 CRC_BitCount                              **
**                    )                                                       **
**                                                                            **
** Description      : This function takes the 32bit crc data and length of    **
**                    the data, calculates reverses it and return back.       **
**                    This function is local to the library module and is     **
**                    not for the user of CRC Library                         **
**                                                                            **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : reentrant                                               **
**                                                                            **
** Parameters (in)  : CRCData_64bit -Start value for CRC Calculation          **
**                    CRC_BitCount -Boolean to decide the start value         **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : Return the reversed data                                **
**                                                                            **
*******************************************************************************/
static uint64 Crc_lReflect64
(
  const uint64 CRCData_64bit,
  const uint8 CRC_BitCount
)
{
  uint64 ReversedData = 0U;
  uint8  MsgBit;
  uint64 Data64bit = CRCData_64bit;

  /* Cycle through each of the bit in the parameter passed to the
   * function and reverse the bits. i.e. after the processing done by
   * this function, the data bits in the result would be in
   * the reverse order. */
  /* [cover parentID={EA7FE783-53D3-4d6b-A61A-D58681796E32}]
   * Reverse the bits and store in a 32bit variable
   * [/cover] */
  for (MsgBit = 0U; MsgBit < CRC_BitCount; MsgBit++)
  {
    /* [cover parentID={0A91EF0F-AAE2-4675-9BC7-8E099F67B449}]
     * Store the bits in reverse order
     * [/cover] */
    /* Start cycling through each bit of the data */
    if( (Data64bit & 1U) == 1U )
    {
      /* [cover parentID={2E3A984E-A9E4-4865-B4BF-44A2279F5596}]
       * Write 1 to the corresponding bit so that the bit is stored in
       * reverse order in the variable which will hold the reverse value
       * [/cover] */
      /* If a bit '1' is detected, set the bit at the opposite
       * end of the data so that we can reverse the information. */
      ReversedData |= (uint64)((uint64)1U <<
                               ((CRC_BitCount - 1U) - MsgBit));
    }
    /* Shift the data to the right by one bit */
    Data64bit = (uint64)((uint64)Data64bit >> (uint64)1U);

  }
  return ReversedData;
}
#endif
/*#if (CRC_64_MODE !=STD_OFF)*/

#if  (CRC_32P4_MODE == CRC_RUNTIME_MODE)
/*******************************************************************************
** Traceability     : [cover parentID={4DB33E44-4AF4-4329-BB36-823122E64D58}] **
**                                                                            **
** Syntax           : static uint32 Crc_lCalculateCRC32P4Runtime              **
**                    (                                                       **
**                      const uint8* const Crc_DataPtr,                       **
**                      const uint32 Crc_Length,                              **
**                      const uint32 Crc_StartValue32,                        **
**                      const boolean Crc_IsFirstCall                         **
**                    )                                                       **
**                                                                            **
** Description      : This function takes the value of input data pointer,    **
**                    start value and polynomial, calculates the CRC value    **
**                    and returns the CRC xored with XOR value                **
**                    This function is local to the library module and is not **
**                    for the user ofCRC Library                              **
**                                                                            **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : reentrant                                               **
**                                                                            **
** Parameters (in)  : Crc_DataPtr  - Pointer to the start of the datablock    **
**                    Crc_Length - Length of the input data to be fetched     **
**                    Crc_StartValue32 -Start value for CRC Calculation       **
**                    Crc_IsFirstCall -Boolean to decide the start value      **
**          *                                                                 **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : Result of 32bit CRC calculation                         **
**                                                                            **
*******************************************************************************/
static uint32 Crc_lCalculateCRC32P4Runtime
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint32 Crc_StartValue32,
  const boolean Crc_IsFirstCall
)
{
  uint32 LoopCounter;
  uint32 TempVal;
  uint8 MessageBit;
  /* code for CRC 32P4 runtime calculation with 0xF4ACFB13 polynomial*/
  uint32 StartValue32P4 = Crc_StartValue32;
  /* [cover parentID={2481D997-81D8-48ff-8DD4-1A68B4A24EEC}]
   * Is this first call?
   * [/cover] */
  /* if it is first call assign initial value to the start value */
  if(Crc_IsFirstCall == (boolean)TRUE)
  {
    /* [cover parentID={CD2B992E-EBE6-40cc-AABD-D43B6170BDAF}]
     * Set Start Value to Initial value for 32 bit P4 CRC
     * [/cover] */
    /* First call, assign the initial value needed. */
    StartValue32P4 = CRC_INITIAL_VALUE32P4;

  }
  else
  {
    /* [cover parentID={4A11219C-2EE2-4f67-B680-7A4830DAE9BD}]
     * XOR Start Value with XOR Value for the 32 bit P4 CRC
     * [/cover] */
    /* Not a first call. So, take the start value, XOR with the needed
     * value and proceed. */
    StartValue32P4 = StartValue32P4 ^ CRC_CRC32P4_XOR_VALUE;

    /* Reverse the data bits in the start value. This is as per the
     * specification of the CRC32P4 */
    /* [cover parentID={0E79849A-5827-477d-A225-2071C0D71847}]
     * Reflect the Start Value
     * [/cover] */
    StartValue32P4 = (uint32)Crc_lCommonReflect(StartValue32P4,
                                       CRC_BITCNT_THIRTYTWO);

  }

  /* Cycle through each byte of the data provided. This loop would
   * run till the complete CRC is computed. Yes, this is a blocking call,
   * but that's the best way possible with the interfaces
   * defined by AUTOSAR. */
  /* [cover parentID={96AA6BA4-9D52-455d-9D45-B576331151B3}]
   *  Do an XOR division on the binary data to calculate the CRC.
   * [/cover] */
  for (LoopCounter = 0U;
       LoopCounter < Crc_Length; LoopCounter++)
  {
    /* [cover parentID={A042DF06-0228-4042-9BA5-BE16BDA49B96}]
     * Get the reflection of input data
     * [/cover] */
    /* The input data needs to be 'reflected'. */
    TempVal = (uint32)Crc_lCommonReflect((uint32)Crc_DataPtr[LoopCounter],
                                CRC_BITCNT_EIGHT);

    /* Shift the 8 bit data to the MSB of the 32 bit variable */
    StartValue32P4 ^=  TempVal << (CRC_CRC32_SIZE - CRC_BYTELENGTH_U);

    /* [cover parentID={3D482621-87A5-40ee-8457-A9751CAFEA8C}]
     * Do the division bit wise
     * [/cover] */
    /* Cycle through each bit of the data */
    for( MessageBit = CRC_BYTELENGTH_U;
         MessageBit > 0U; MessageBit--)
    {
      /* [cover parentID={5F9C7769-AD63-4ff5-8DEF-AEFACF3CB242}]
       * Is the MSB bit 1 ?
       * [/cover] */
      /* Check if the MSB is set */
      if((StartValue32P4 & CRC_CRC32_MSB) == CRC_CRC32_MSB)
      {
        /* [cover parentID={60C99C36-D7CC-4b54-9B46-4E3838634C71}]
         * Left shift Start Value once and XOR with the Polynomial
         * [/cover] */
        /* If MSB is 1 then left shift and X-OR with polynomial*/
        StartValue32P4 =
          (StartValue32P4 << 1u) ^ CRC_CRC32P4_POLYNOMIAL;
      }
      else
      { /* [cover parentID={E8B955EF-573A-4ae2-B110-AD71AB71FA7A}]
        Left shift Start Value once
        [/cover] */
        /* If MSB is 0 then left shift and skip the XOR operation */
        StartValue32P4 = (StartValue32P4 << 1u);
      }

    }

  }
  /* [cover parentID={0636F5F6-A2E1-459f-ACE4-CDB9F6713D28}]
   * Reflect the output
   * [/cover] */
  /* The output data also should be reflected */
   StartValue32P4 =
    (uint32)Crc_lCommonReflect(StartValue32P4, CRC_BITCNT_THIRTYTWO);

  /* The output data should be XORed with the needed value */
  StartValue32P4 = CRC_CRC32P4_XOR_VALUE ^ StartValue32P4;

  return StartValue32P4;
}

#elif  (CRC_32P4_MODE == CRC_TABLE_MODE)
/*******************************************************************************
** Traceability      : [cover parentID={279A74DC-64A6-4225-AF8E-1BB24519E0A3}]**
**                                                                            **
** Syntax            : static uint32 Crc_lCalculateCRC32P4Table               **
**                     (                                                      **
**                       const uint8* const Crc_DataPtr,                      **
**                       const uint32 Crc_Length,                             **
**                       const uint32 Crc_StartValue32,                       **
**                       const boolean Crc_IsFirstCall                        **
**                     )                                                      **
**                                                                            **
** Description      : This function takes the value of input data pointer,    **
**                    start value and polynomial, calculates the crc taking   **
**                    the precomputed and reversed xor value  and returns the **
**                    CRC xored with XOR value                                **
**                    This function is local to the library module and is not **
**                    for the user of CRC Library                             **
**                                                                            **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : reentrant                                               **
**                                                                            **
** Parameters (in)  : Crc_DataPtr  - Pointer to the start of the datablock    **
**                    Crc_Length - Length of the input data to be fetched     **
**                    Crc_StartValue32 -Start value for CRC Calculation       **
**                    Crc_IsFirstCall -Boolean to decide the start value      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : Result of 32bit CRC32P4 calculation                     **
**                                                                            **
*******************************************************************************/
static uint32 Crc_lCalculateCRC32P4Table
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint32 Crc_StartValue32,
  const boolean Crc_IsFirstCall
)
{
  /* code for crc 32 table based calculation with 0x04C11DB7 polynomial*/
  uint32 LoopCounter ;
  uint32 Temp32;
  uint32 StartValue32P4 = Crc_StartValue32;

  /* [cover parentID={D58DA465-D27F-4111-9D6F-EBED5D2AE53D}]
   * Check if this is first call
   * [/cover] */
  if(Crc_IsFirstCall == (boolean)TRUE)
  {
    /* [cover parentID={41B50AF3-A853-48c7-A002-CF5C2DF20AB2}]
     * Set Start Value to Initial value for 32 bit P4 CRC
     * [/cover] */
    StartValue32P4 = CRC_INITIAL_VALUE32P4;
  }
  else
  {
    /* [cover parentID={254DD0C6-FCAE-4469-89C5-307DFEC62A38}]
     * XOR Start Value with XOR Value for the 32 bit P4 CRC
     * [/cover] */
    StartValue32P4 = StartValue32P4 ^ CRC_CRC32P4_XOR_VALUE;
    /* [cover parentID={3EF8C922-AB92-4729-A61B-547C1233BE73}]
     * Reflect the Start Value
     * [/cover] */
    StartValue32P4 = (uint32)Crc_lCommonReflect(StartValue32P4,
                                       CRC_BITCNT_THIRTYTWO);
  }

  /* ********************************************************************
   * Now, the runtime method is a slow and inefficient method to compute
   * the CRC, obviously. Parsing each bit from the message to compute the
   * CRC can be a nightmare when the volume of the data becomes bigger.
   * The lookup table method aims to accelerate the computation by
   * providing lookup values for the possible data combinations. This
   * would eliminate all the bit handling stuff and we can start thinking
   * on the byte level, instead of bits!
   * ******************************************************************** */

  /* Extract each byte from the message, fetch the value from lookup
   * table and XOR with the crc value*/
  /* [cover parentID={B884C8A2-41A9-4a10-880A-E49B17133217}]
   * Parse each byte from the message
   * [/cover] */
  for(LoopCounter = 0U; LoopCounter < Crc_Length;
      LoopCounter++)
  {
    /* [cover parentID={F20E2DA5-3817-46cd-99E4-AAB10D34BB80}]
     * XOR the Byte with Start Value, fetch the value from lookup table using
     * the XOR result, XOR the fetched value with Start Value shifted 8 times
     * right and store in Start Value
     * [/cover] */
    Temp32 = (uint32)Crc_lCommonReflect((uint32)Crc_DataPtr[LoopCounter],
                               CRC_BITCNT_EIGHT);

    Temp32 =
      ((uint32) ((uint32)StartValue32P4 >> CRC_SHIFT_TWENTYFOUR) ^
       Temp32) & CRC_U32LSB_MASK;

    StartValue32P4 =
      (uint32)((uint32)StartValue32P4 << CRC_BYTELENGTH_U) ^
      Crc_Table32P4[Temp32];

  }
  /* [cover parentID={19832151-E3D2-45d6-AC90-1DC450F47DDB}]
   * Reflect the output
   * [/cover] */
  StartValue32P4 = (uint32)Crc_lCommonReflect(StartValue32P4,
                                     CRC_BITCNT_THIRTYTWO);

  StartValue32P4 = CRC_CRC32P4_XOR_VALUE ^ StartValue32P4;


  return StartValue32P4;
}
#endif
/* #if  CRC_32P4_MODE == ** */

#if  (CRC_64_MODE == CRC_RUNTIME_MODE)
/*******************************************************************************
** Traceability     : [cover parentID={9B480B91-E7AF-41d0-BB56-9F539FBE867F}] **
**                                                                            **
** Syntax           : static uint64 Crc_lCalculateCRC64Runtime                **
**                    (                                                       **
**                      const uint8* const Crc_DataPtr,                       **
**                      const uint32 Crc_Length,                              **
**                      const uint64 Crc_StartValue64,                        **
**                      const boolean Crc_IsFirstCall                         **
**                    )                                                       **
**                                                                            **
** Description      : This function takes the value of input data pointer,    **
**                    start value and polynomial, calculates the CRC value    **
**                    and returns the CRC xored with XOR value                **
**                    This function is local to the library module and is not **
**                    for the user of CRC Library                             **
**                                                                            **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : reentrant                                               **
**                                                                            **
** Parameters (in)  : Crc_DataPtr  - Pointer to the start of the datablock    **
**                    Crc_Length - Length of the input data to be fetched     **
**                    Crc_StartValue64 -Start value for CRC Calculation       **
**                    Crc_IsFirstCall -Boolean to decide the start value      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : Result of 64 bit runtime calculation                    **
**                                                                            **
*******************************************************************************/
static uint64 Crc_lCalculateCRC64Runtime
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint64 Crc_StartValue64,
  const boolean Crc_IsFirstCall
)
{
  uint32 LoopCounter;
  uint64 TempVal;
  uint8 MessageBit;
  /* code for CRC 32P4 runtime calculation with 0xF4ACFB13 polynomial*/
  uint64 StartValue64 = Crc_StartValue64;
  /* [cover parentID={AD45758F-AC4B-4a8d-9ECA-CD16D321B121}]
   * Is this first call?
   * [/cover] */
  /* if it is first call assign initial value to the start value */
  if(Crc_IsFirstCall == (boolean)TRUE)
  {
    /* [cover parentID={3AA53DAA-680C-49ff-9BEA-1AABD0B19B76}]
     * Set Start Value to Initial value for 32 bit P4 CRC
     * [/cover] */
    /* First call, assign the initial value needed. */
    StartValue64 = CRC_INITIAL_VALUE64;

  }
  else
  {
    /* [cover parentID={D4FBD211-7182-4153-A728-8492CF084FA0}]
     * XOR Start Value with XOR Value for 64CRC
     * [/cover] */
    /* Not a first call. So, take the start value, XOR with the needed
     * value and proceed. */
    StartValue64 = StartValue64 ^ CRC_CRC64_XOR_VALUE;

    /* Reverse the data bits in the start value. This is as per the
     * specification of the CRC32P4 */
    /* [cover parentID={856D92D2-E563-4874-B936-1E3B99B214D6}]
     * Reflect the Start Value
     * [/cover] */
    StartValue64 = Crc_lReflect64(StartValue64,
                                       CRC_BITCNT_SIXTYFOUR);
  }

  /* Cycle through each byte of the data provided. This loop would
   * run till the complete CRC is computed. Yes, this is a blocking call,
   * but that's the best way possible with the interfaces
   * defined by AUTOSAR. */
  /* [cover parentID={36E7A694-D1AD-4904-9EB5-B00C89AEDC70}]
   * Do an XOR division on the binary data to calculate the CRC.
   * [/cover] */
  for (LoopCounter = 0U;
       LoopCounter < Crc_Length; LoopCounter++)
  {
    /* [cover parentID={2313D80B-9ED2-4d7b-BC90-BB35E2C87B83}]
     * Get the reflection of input data
     * [/cover] */
    /* The input data needs to be 'reflected'. */
    TempVal = (uint64)Crc_lCommonReflect(Crc_DataPtr[LoopCounter],
                                CRC_BITCNT_EIGHT);

    /* Shift the 8 bit data to the MSB of the 64 bit variable */
    StartValue64 ^=  TempVal << (CRC_CRC64_SIZE - CRC_BYTELENGTH_U);

    /* [cover parentID={24F9606E-DBBB-446a-8891-09FF55F622B0}]
     * Do the division bit wise
     * [/cover] */
    /* Cycle through each bit of the data */
    for( MessageBit = CRC_BYTELENGTH_U;
         MessageBit > 0U; MessageBit--)
    {
      /* [cover parentID={050B01B0-8E72-4388-9DB9-8AAAD2C3E505}]
       * Is the MSB bit 1 ?
       * [/cover] */
      /* Check if the MSB is set */
      if((StartValue64 & CRC_CRC64_MSB) == CRC_CRC64_MSB)
      {
        /* [cover parentID={9EC9CA9A-08D9-4585-9D9A-C0F9C65C3B52}]
         * Left shift Start Value once and XOR with the Polynomial
         * [/cover] */
        /* If MSB is 1 then left shift and X-OR with polynomial*/
        StartValue64 =
          (StartValue64 << 1u) ^ CRC_CRC64_POLYNOMIAL;
      }
      else
      { /* [cover parentID={BE1823D4-2323-48ae-AD9D-D53ED8124321}]
         * Left shift Start Value once
         * [/cover] */
        /* If MSB is 0 then left shift and skip the XOR operation */
        StartValue64 = (StartValue64 << 1u);
      }

    }

  }
  /* [cover parentID={730F8330-C4AF-43ba-ABE5-728558D71748}]
   * Reflect the output
   * [/cover] */
  /* The output data also should be reflected */
  StartValue64 =
    Crc_lReflect64(StartValue64, CRC_BITCNT_SIXTYFOUR);

  /* The output data should be XORed with the needed value */
  StartValue64 = CRC_CRC64_XOR_VALUE ^ StartValue64;

  return StartValue64;
}
/*#if (CRC_64_MODE == CRC_RUNTIME_MODE)*/

#elif  (CRC_64_MODE == CRC_TABLE_MODE)
/*******************************************************************************
** Traceability     : [cover parentID={AB8CC6D3-CD05-47bc-88E2-9B5156DC8693}] **
**                                                                            **
** Syntax           : static uint64 Crc_lCalculateCRC64P4Table                **
**                    (                                                       **
**                      const uint8* const Crc_DataPtr,                       **
**                      const uint32 Crc_Length,                              **
**                      const uint64 Crc_StartValue64,                        **
**                      const boolean Crc_IsFirstCall                         **
**                    )                                                       **
**                                                                            **
** Description      : This function takes the value of input data pointer,    **
**                    start value and polynomial, calculates the crc taking   **
**                    the precomputed and reversed xor value  and returns     **
**                    the CRC xored with XOR value                            **
**                    This function is local to the library module and is not **
**                    for the user of CRC Library                             **
**                                                                            **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : reentrant                                               **
**                                                                            **
** Parameters (in)  : Crc_DataPtr  - Pointer to the start of the datablock    **
**                    Crc_Length - Length of the input data to be fetched     **
**                    Crc_StartValue64 -Start value for CRC Calculation       **
**                    Crc_IsFirstCall -Boolean to decide the start value      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : Result of 64 bit Table calculation                      **                             **
**                                                                            **
*******************************************************************************/
static uint64 Crc_lCalculateCRC64Table
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint64 Crc_StartValue64,
  const boolean Crc_IsFirstCall
)
{
  /* code for crc 32 table based calculation with 0x04C11DB7 polynomial*/
  uint32 LoopCounter ;
  uint64 Temp64;
  uint64 StartValue64 = Crc_StartValue64;

  /* [cover parentID={1D0EC9D6-8A71-46a1-95FE-B44E4984564F}]
   * If it is a first call?
   * [/cover] */
  if(Crc_IsFirstCall == (boolean)TRUE)
  {
    /* [cover parentID={C14CAB65-A375-4fee-8ED3-221F867D7863}]
     * Set Start Value to Initial value for 32 bit P4 CRC
     * [/cover] */
    StartValue64 = (uint64)CRC_INITIAL_VALUE64;
  }
  else
  {
    /* [cover parentID={572BF748-3C12-4310-9409-D74D5AFCD8CB}]
     * XOR Start Value with XOR Value for the 32 bit P4 CRC
     * [/cover] */
    StartValue64 = StartValue64 ^ CRC_CRC64_XOR_VALUE;
    /* [cover parentID={EA98F5DD-ED82-4f6b-909D-3787C78E6D6E}]
     * Reflect the Start Value
     * [/cover] */
    StartValue64 = Crc_lReflect64(StartValue64,
                                       CRC_BITCNT_SIXTYFOUR);
  }

  /* ********************************************************************
   * Now, the runtime method is a slow and inefficient method to compute
   * the CRC, obviously. Parsing each bit from the message to compute the
   * CRC can be a nightmare when the volume of the data becomes bigger.
   * The lookup table method aims to accelerate the computation by
   * providing lookup values for the possible data combinations. This
   * would eliminate all the bit handling stuff and we can start thinking
   * on the byte level, instead of bits!
   * ******************************************************************** */

  /* Extract each byte from the message, fetch the value from lookup
   * table and XOR with the crc value*/
  /* [cover parentID={02D425AB-1C5E-47e3-8997-5699C1835CC8}]
   * Parse each byte from the message
   * [/cover] */
  for(LoopCounter = 0U; LoopCounter < Crc_Length;
      LoopCounter++)
  {
    /* [cover parentID={DBD0C1F6-0C92-4bd3-97D8-E295D2CF576E}]
     * XOR the Byte with Start Value, fetch the value from lookup table using
     * the XOR result, XOR the fetched value with Start Value shifted 8 times
     * right and store in Start Value
     * [/cover] */
    Temp64 = (uint64)Crc_lCommonReflect(Crc_DataPtr[LoopCounter],
                               CRC_BITCNT_EIGHT);

    Temp64 =
      ((uint64) ((uint64)StartValue64 >> CRC_SHIFT_FIFTYSIX) ^
       Temp64) & CRC_U64LSB_MASK;

    StartValue64 =
      (uint64)((uint64)StartValue64 << CRC_BYTELENGTH_U) ^
      Crc_Table64[Temp64];

  }
  /* [cover parentID={56F7DCBF-A1BC-4e95-AE72-855E4BF258FB}]
   * Reflect the output
   * [/cover] */
  StartValue64 = Crc_lReflect64(StartValue64,
                                     CRC_BITCNT_SIXTYFOUR);


  /* XOR the Start Value with the XOR Value for CRC64*/
  StartValue64 = CRC_CRC64_XOR_VALUE ^ StartValue64;


  return StartValue64;
}
#endif
/* #if  CRC_64_MODE == ** */

#if  ((CRC_SAFETYENABLE == STD_ON) && (CRC_DMA_MAX_CHANNELS > 0U))
/*******************************************************************************
** Traceability    : [cover parentID={894A8249-2A64-4765-97AA-86BCF73F9C9E}]  **
**                                                                            **
** Syntax          : static Crc_DmaReturnType Crc_lDmaSafetyChecks            **
**                   (                                                        **
**                     const uint8* const Crc_DataPtr,                        **
**                     const uint8  Crc_NoOfBytes,                            **
**                     const uint32 Crc_Length                                **
**                     const uint32 CurrentCoreId                             **
**                   )                                                        **
**                                                                            **
** Description     : This function takes the data pointer, length of the      **
**                   data, Number of bytes as an input, checks if the data    **
**                   pointer is not NULL, if the data length is not zero,     **
**                   if the length is aligned to 16bit (in 16 bit CRC) or     **
**                   32bit (in 32 bit CRC) and if the address is aligned to   **
**                   16bit address word(in 16bit CRC) or 32bit (in 32bit CRC).**
**                                                                            **
**                  - This function is local to the library module and is     **
**                    not for the user of CRC Library                         **
**                                                                            **
** Service ID      : none                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : reentrant                                                **
**                                                                            **
** Parameters (in) : Crc_DataPtr -Data pointer of input data                  **
**                   Crc_Length -Lenght of the input data                     **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value    : CRC_INVALID_CORE: If the current executing core does not **
**                   have FCE and DMA channel allocated to it.                **
**                   CRC_INVALID_POINTER: If the data pointer is NULL.        **
**                   CRC_INVALID_LENGTH: In case,                             **
**                    a. If the length of the input data is zero.             **
**                    b. If the length of the input data exceeds 16384 bytes. **
**                    c. If the input data stream is not aligned to 16-bit    **
**                       word or 32-bit boundary in calculation of CRC for    **
**                       16-bit and 32-bit respectively.                      **
**                   CRC_INVALID_ADDRESS: If the address of the data pointer  **
**                   does not align to 16-bit or 32-bit boundary in           **
**                   calculation of CRC for 16-bit and 32-bit respectively.   **
**                   CRC_CHANNEL_BUSY: If the channel is busy.                **
**                   CRC_OK: If all the checks are done successful.           **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Crc_DmaReturnType Crc_lDmaSafetyChecks
(
  const uint8* const Crc_DataPtr,
  const uint8  Crc_NoOfBytes,
  const uint32 Crc_Length,
  const uint32 Crc_CoreId
)
{
  Crc_DmaReturnType Result;
  uint32 AlignedLength;

  /*Aligned length based on degree of the polynomial*/
  AlignedLength = Crc_Length/Crc_NoOfBytes;

  /* Check for the core configuration */
  /* [cover parentID={C0BEBA17-C271-4c7e-B91E-C1C1BA4EDEB4}]
   * If the configuration for core is NULL
   * [/cover] */
  if (Crc_ChannelConfig[Crc_CoreId] == NULL_PTR)
  {
    Result = CRC_INVALID_CORE;
  }
  /* Check for the Null pointer of input data*/
  /* [cover parentID={EAC48536-C595-46c4-BF21-7E8FF318032B}]
   * If the data pointer is NULL
   * [/cover] */
  else if(Crc_DataPtr == NULL_PTR)
  {
    Result = CRC_INVALID_POINTER;
  }
  /* Check on input data length
   * - If the length is zero
   * - If the length is greater than maximum length transfered by DMA channel*/
  /* [cover parentID={113D669E-00BF-46b9-9F8C-CB0DE8987B8F}]
   * If the length is zero or greater than 16384U
   * [/cover] */
  else if ((Crc_Length == 0U) || (AlignedLength > CRC_DMA_MAXLENGTH))
  {
    Result = CRC_INVALID_LENGTH;
  }
  /* Check on the data length for 16bit or 32bit CRC calculation
   * - Alignment to 16bit(2 byte) word boundary
   * - Alignment to 32bit(4 byte) word boundary*/
  /* [cover parentID={16729E7F-3711-4dd7-94B9-B6B22F0D76FB}]
   * If the length is not aligned with CRC bytes (2byte or 4byte).
   * [/cover] */
  else if((Crc_Length%Crc_NoOfBytes) != 0U)
  {
    Result = CRC_INVALID_LENGTH;
  }
  /* MISRA2012_RULE_10_4_JUSTIFICATION: cast from pointer to unsigned long
   * is required to check the value of the address of data buffer alignment.
   * The implicit conversion will only compare the value*/
  /* MISRA2012_RULE_11_4_JUSTIFICATION: Conversion between pointer and integer
   * type is done as the address is compared agaisnt 32-bit variable*/
  /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from pointer to unsigned long
   * is required for checking the Crc_DataPtr address*/
  /* [cover parentID={6EA87B27-CBFD-4bab-8FC6-092966B2A865}]
   * If the CRC calculation is for 16 bit and address is not aligned to
   * 16-bit address word.
   * [/cover] */
  else if((Crc_NoOfBytes == ((uint8)CRC_ALIGNLENGTH_16BIT)) && (((uint32)Crc_DataPtr & 1U) != 0U))
  {
    Result = CRC_INVALID_ADDRESS;
  }
  /* MISRA2012_RULE_10_4_JUSTIFICATION: cast from pointer to unsigned long
   * is required to check the value of the address of data buffer alignment.
   * The implicit conversion will only compare the value*/
  /* MISRA2012_RULE_11_4_JUSTIFICATION: Conversion between pointer and integer
   * type is done as the address is compared agaisnt 32-bit variable*/
  /* MISRA2012_RULE_11_6_JUSTIFICATION: cast from pointer to unsigned long
   * is required for checking the Crc_DataPtr address*/
  /* [cover parentID={88C3866F-0FB5-4283-9CE9-696E20DDC527}]
   * If the CRC calculation is for 32 bit and address is not aligned to 32-bit address word
   * [/cover] */
  else if((Crc_NoOfBytes == ((uint8)CRC_ALIGNLENGTH_32BIT)) && (((uint32)Crc_DataPtr & CRC_THREE_U) != 0U))
  {
    Result = CRC_INVALID_ADDRESS;
  }
  else
  {
    /*The result will be CRC_OK*/

    Result =  CRC_OK;
  }
  return Result;
}
#endif

#if (CRC_DMA_MAX_CHANNELS > 0U)
/*******************************************************************************
** Traceability     : [cover parentID={5B35DDC5-C351-402c-871D-D4897F3931B4}] **
**                                                                            **
** Syntax           : LOCAL_INLINE void Crc_lDmaChUpdateTransfer              **
**                      (                                                     **
**                        const uint32 DmaConfig                              **
**                        const uint8 DmaChannel,                             **
**                        const uint32 MoveLength,                            **
**                        const uint32  lSourceAddress,                       **
**                        const uint32 lDestAddress                           **
**                      )                                                     **
**                                                                            **
** Description      : This function takes the Polynomialsize, Dma channel,    **
**                    Move length, Source address and Destination address     **
**                    as an input, updates the DMA channel configuration by   **
**                    invoking Dma_ChUpdate DMA API and start the data        **
**                    transfer by invoking Dma_ChStartTransfer DMA API.       **
**                                                                            **
**                    This function is local to the library module and is     **
                      not for the user of CRC Library.                        **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : DmaConfig - Config parameter for DMA channel            **
**                    based on the bits of calculation                        **
**                    DmaChannel - Dma Channel number                         **
**                    MoveLength - How many bits will to transfered by DMA    **
**                    channel at a time                                       **
**                    lSourceAddress - Data pointer                           **
**                    lDestAddress - FCE channel IR register                  **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : void                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Crc_lDmaChUpdateTransfer
(
  const uint32 DmaConfig,
  const uint8  DmaChannel,
  const uint32 MoveLength,
  const uint32 lSourceAddress,
  const uint32 lDestAddress
)
{
  /* DMA channel configuration is updated */
  Dma_ConfigUpdateType DmaCrcChConfig;
  DmaCrcChConfig.SourceAddress = lSourceAddress;
  DmaCrcChConfig.DestAddress  = lDestAddress;
  DmaCrcChConfig.ControlAdicr = CRC_DMA_ADICR;
  DmaCrcChConfig.ControlChcsr = 0U;
  DmaCrcChConfig.Config = DmaConfig | MoveLength;
  DmaCrcChConfig.ShadowConfig = 0U;
  DmaCrcChConfig.AddressCrc = 0U;
  DmaCrcChConfig.DataCrc = 0U;
  DmaCrcChConfig.UpdateSourceAddress = 1U;
  DmaCrcChConfig.UpdateDestAddress = 1U;
  DmaCrcChConfig.UpdateControlAdicr = 1U;
  DmaCrcChConfig.UpdateControlChcsr = 1U;
  DmaCrcChConfig.UpdateConfig = 1U;
  DmaCrcChConfig.UpdateShadowConfig = 0U;
  DmaCrcChConfig.UpdateAddressCrc = 0U;
  DmaCrcChConfig.UpdateDataCrc = 0U;

  /* [cover parentID={6E231011-9390-41fe-9FB0-43B5F29217EB}]
   * Update the DMA channel configuration
   * [/cover] */
  /* DMA API Dma_ChUpdate is called to update the configuration of the DMA
   * channel under consideration*/
  /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable DmaCrcChConfig
   * is used inside Dma_ChUpdate() to read the values. The address is not used
   * beyond the context of the API, hence it is not an issue */
  Dma_ChUpdate(DmaChannel, &DmaCrcChConfig, NULL_PTR);

  /* Once the configurations of the channel is updated, call DMA API
   * Dma_ChStartTransfer to trigger the data transfer*/
  /* [cover parentID={A0FE3286-A8A0-4098-91C8-C831D3F74063}]
   *  Trigger DMA transfer
   * [/cover] */
  Dma_ChStartTransfer(DmaChannel);
}
#endif

#if (CRC_DMA_MAX_CHANNELS > 0U)
/*******************************************************************************
** Traceability     : [cover parentID={8D6C28A0-F00C-468b-A87E-2ECEFF351C9B}] **
** Syntax           : void Crc_DmaTransferIsr                                 **
**                    (                                                       **
**                        const uint8 Channel,                                **
**                        const uint32 Event                                  **
**                    )                                                       **
**                                                                            **
** Description      : This function is invoked by the DMA channel on          **
**                    successful DMA transaction.                             **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x1E                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : Channel  - Channel under consideration                  **
**                    Event - Event associated with the channel               **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : void                                                    **
**                                                                            **
*******************************************************************************/
void Crc_DmaTransferIsr
(
  const uint8 Channel,
  const uint32 Event
)
{
  uint8 FceChannel;
  uint32 CurrentCoreId;
  uint32 Result;

  /* Assign the base address of FCE*/
  const Ifx_FCE *FCERegBaseAddress = &MODULE_FCE;
  /* Get the core ID of the core, where we are executing at this moment */
  CurrentCoreId = Mcal_GetCpuIndex();
  /* [cover parentID={09B1F369-A4EC-4008-975B-F952F99B4641}]
  If safety check is enabled
  [/cover] */
  #if (CRC_SAFETYENABLE == STD_ON)
  /* Check if the channel of DMA currently under use is same as received channel*/
  /* [cover parentID={798A32D5-5B73-4074-8DC8-154679BE4171}]
   * If the DMA channel is Invalid
   * [/cover] */
  if(Channel != Crc_ChannelConfig[CurrentCoreId]->Dma_Channel)
  {
    /* Report Mcal Safety Error - invalid channel */
    /* [cover parentID={63407E80-E10F-4614-B6BE-5774AC7C524E}]
     * Report CRC_E_NOT_CONFIGURED
     * [/cover] */
    Mcal_ReportSafetyError(CRC_MODULE_ID, CRC_INSTANCE_ID,
                           CRC_SID_RESULT_CRCDMAISR, CRC_E_NOT_CONFIGURED);
  }
  /* Check if DMA has done the complete transfer */
  /* [cover parentID={98356DD8-AA3A-4d42-877F-853190FB5D33}]
   * If the Event is not DMA_EVENT_CH_TRANSFER_COMPLETE
   * [/cover] */
  else if(((uint32)Event & (uint32)DMA_EVENT_CH_TRANSFER_COMPLETE) !=
                    (uint32)DMA_EVENT_CH_TRANSFER_COMPLETE)
  {
    /* Report Mcal Safety Error - invalid event */
    /* [cover parentID={45763C77-0622-4473-9C53-F1314C9B5E2F}]
     * Report CRC_E_INVALID_ISR
     * [/cover] */
    Mcal_ReportSafetyError(CRC_MODULE_ID, CRC_INSTANCE_ID,
                           CRC_SID_RESULT_CRCDMAISR, CRC_E_INVALID_ISR);
  }
  else
  #else
    UNUSED_PARAMETER(Channel);
    UNUSED_PARAMETER(Event);
  #endif
  {
    /* Check if the callback function is configured by user or not*/
    /* [cover parentID={5E42B5E6-9D9D-4fa0-A8D5-A0D0FE394010}]
    * If the callback pointer is NULL
    * [/cover] */
    if (NULL_PTR != Crc_ChannelConfig[CurrentCoreId]->ResNotificationPtr)
    {
      FceChannel = Crc_ChannelConfig[CurrentCoreId]->Fce_Channel;
      Result = (FCERegBaseAddress->IN[FceChannel].RES.U);

      /* Read the RES register for the FCE channel under consideration.
       * Note: Result is 32bit*/
      /* [cover parentID={2E2CA531-A28F-4f37-A3F6-0EFBFB5038D5}]
       *  Call the configured CRC callback[/
       * [/cover] */
      (Crc_ChannelConfig[CurrentCoreId]->ResNotificationPtr)(Result);

      /* Set the DMA channel of the current core as free */
      *Crc_DmaBusyFlag[CurrentCoreId] = CRC_DMACH_FREE;
    }
  }
}
#endif

#if (CRC_DMA_MAX_CHANNELS > 0U)
/*******************************************************************************
** Traceability     : [cover parentID={DFAF0027-96DB-40c9-AA49-EDE2BA7C4C12}] **
** Syntax           : void Crc_DmaErrorIsr                                    **
**                    (                                                       **
**                      const uint8 Channel,                                  **
**                      const uint32 Event                                    **
**                    )                                                       **
**                                                                            **
** Description      : This function is invoked by the DMA channel is an       **
**                    error has occured during the DMA transaction            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x1F                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : Channel  - Channel under consideration                  **
**                    Event - Event associated with the channel               **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : void                                                    **
**                                                                            **
*******************************************************************************/
void Crc_DmaErrorIsr
(
  const uint8 Channel,
  const uint32 Event
)
{
  uint32 CurrentCoreId;
  UNUSED_PARAMETER(Event);
  /* Get the core ID of the core, where we are executing at this moment */
  CurrentCoreId = Mcal_GetCpuIndex();
  /* [cover parentID={4315C361-F49C-4fc0-98EC-11C1F344AB3D}]
   * If safety check is enabled
   * [/cover] */
  #if (CRC_SAFETYENABLE == STD_ON)
  /* Check if the channel of DMA currently under use is same as received channel*/
  /* [cover parentID={6279A57B-3DB2-45d6-B43F-96798D1D362D}]
   * If DMA channel is Invalid
   * [/cover] */
  if(Channel != Crc_ChannelConfig[CurrentCoreId]->Dma_Channel)
  {
    /* Report Mcal Safety Error - invalid channel */
    /* [cover parentID={3E2A5D01-6F7D-405d-8740-DB601DB35D86}]
     *  Report CRC_E_NOT_CONFIGURED
     * [/cover] */
    Mcal_ReportSafetyError(CRC_MODULE_ID, CRC_INSTANCE_ID,
                           CRC_SID_ERROR_CRCDMAISR, CRC_E_NOT_CONFIGURED);
  }
  else
  #endif
  {
    /* Disable DMA channel */
    /* [cover parentID={CCB1B8A4-ECD4-4f52-A2B0-C6A916369475}]
     *  Stop further data transfer by DMA channel
     * [/cover] */
    Dma_ChStopTransfer(Channel);
    /* Check if the callback function is configured by user or not*/
    /* [cover parentID={269EF4A7-7832-4c41-888A-74BA76F078BB}]
     *  If the Isr for the allocated DMA channel is NULL
     * [/cover] */
    if (NULL_PTR != Crc_ChannelConfig[CurrentCoreId]->ErrNotificationPtr)
    {
      /* Call Error Notification to inform the user about the move engine error
       * that have occured during the data transfer*/
      /* [cover parentID={FE59400F-1211-4343-9228-B46D8D984617}]
       *  Call the configured CRC callback[/
       * [/cover] */
      (Crc_ChannelConfig[CurrentCoreId]->ErrNotificationPtr)();

      /* Set the DMA channel of the current core as free */
      *Crc_DmaBusyFlag[CurrentCoreId] = CRC_DMACH_FREE;
    }
  }
}
#endif

#define CRC_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
 * guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
 * without safegaurd. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"

