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
**  FILENAME     : Crc.h                                                      **
**                                                                            **
**  VERSION      : 12.0.0                                                     **
**                                                                            **
**  DATE         : 2021-03-01                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Crc Driver header definition file                          **
**                                                                            **
**  SPECIFICATION(S) : Specification of CRC Driver, AUTOSAR Release 4.2.2     **
**                   : Specification of Crc Driver, AUTOSAR Release 4.4.0     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/* [cover parentID={BDE616FE-5D39-4b9d-9390-8351CC6C490C}]
[/cover] */
/* [cover parentID={C3614EB3-C9C9-4b17-8FAF-026924C2E58C}]
[/cover] */
#ifndef CRC_H
#define CRC_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* [cover parentID={586E54A0-2AAC-440d-959C-9E35505AE385}]
[/cover] */
/* Inclusion of Std_Types.h */
#include "Std_Types.h"
#include "Mcal_Compiler.h"

/* Pre-compile/static configuration parameters for CRC                        */
#include "Crc_Cfg.h"

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/* [cover parentID={6177EC5E-D0F1-4b2b-96F7-266EA6F8E040}]
[/cover] */
/* CRC VENDOR ID */
#define CRC_VENDOR_ID               ((uint16)17U)
/* CRC MODULE ID */
#define CRC_MODULE_ID               ((uint16)201U)

#if (CRC_SAFETYENABLE == STD_ON)
/* CRC INSTANCE ID */
#define CRC_INSTANCE_ID      (0U)

/*******************************Service ID's***********************************/
#define CRC_SID_CALCULATE_CRC8       ((uint8)0x01U)
#define CRC_SID_CALCULATE_CRC16      ((uint8)0x02U)
#define CRC_SID_CALCULATE_CRC32      ((uint8)0x03U)
#define CRC_SID_GETVERSIONINFO       ((uint8)0x04U)
#define CRC_SID_CALCULATE_CRC8H2F    ((uint8)0x05U)
#define CRC_SID_CALCULATE_CRC32P4    ((uint8)0x06U)
#define CRC_SID_CALCULATE_CRC64      ((uint8)0x07U)
#define CRC_SID_CALCULATE_CRC16ARC   ((uint8)0x08U)
#define CRC_SID_RESULT_CRCDMAISR     ((uint8)0x1EU)
#define CRC_SID_ERROR_CRCDMAISR      ((uint8)0x1FU)
/* ************************************************************************** */
#endif

/**********************************Safety error********************************/
#if (CRC_SAFETYENABLE == STD_ON)

/* Safety Error values  */
/* [cover parentID={E2F59094-3191-48c1-99E6-84A0FA74FAFB}]
[/cover] */
#define CRC_E_PARAM_POINTER        ((uint8)0xC8U)
/* [cover parentID={0919B3EB-452A-4ce6-BEB9-92097D6BB555}]
 * [/cover] */
#define CRC_E_PARAM_LENGTH         ((uint8)0xC9U)
/* [cover parentID={BC609582-5B20-45d1-9644-1335FB2E5BB2}]
 * [/cover] */
#define CRC_E_NOT_CONFIGURED       ((uint8)0xCBU)
/* [cover parentID={CF7CCC9C-1BB0-4197-BE09-C5924765838D}]
 * [/cover] */
#define CRC_E_INVALID_ISR          ((uint8)0xCCU)

#endif
/**************************************************************************** */

/* Mode of operation */
#define CRC_MCAL_SUPERVISOR          (0U)
#define CRC_MCAL_USER1               (1U)

/**********************************Global variable*****************************/
#if ((CRC_64_MODE == CRC_TABLE_MODE) || (CRC_32P4_MODE == CRC_TABLE_MODE))
#define CRC_TABLE_LENGTH             ((uint32)256U)
#endif

/*******************Safety error for DMA based non-AUTOSAR APIs***************/
/* [cover parentID={FAB8159A-8535-4ea8-A2C5-C4D583F5C582}]
 * [/cover] */
#if  ((CRC_8_DMAMODE != STD_OFF) || (CRC_16_DMAMODE != STD_OFF)||\
 (CRC_32_DMAMODE != STD_OFF) || (CRC_32P4_DMAMODE != STD_OFF))
typedef enum
{
   CRC_OK                  =  0x00U,
   CRC_CHANNEL_BUSY        =  0x01U,
   CRC_INVALID_ADDRESS     =  0x02U,
   CRC_INVALID_LENGTH      =  0x03U,
   CRC_INVALID_POINTER     =  0x04U,
   CRC_INVALID_CORE        =  0x05U
}Crc_DmaReturnType;
#endif
/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
#if (CRC_DMA_MAX_CHANNELS > 0U)
/* [cover parentID={18D9495A-D9D1-4abc-8430-889FCA24A405}]
 * [/cover] */
/* Type definition for Crc_ResNotificationPtrType */
typedef void (*const Crc_ResNotificationPtrType)(uint32 CrcResult);

/* [cover parentID={96E4FAFD-81CA-4a8a-ADBD-73E0318F7135}]
 * [/cover] */
/* Type definition for Crc_ErrNotificationPtrType */
typedef void (*const Crc_ErrNotificationPtrType)(void);

/* [cover parentID={64FA8415-5FCC-4867-99AB-D045559CF529}]
 * [/cover] */
/* Type definition for Crc_ChannelConfigType
 * The following structure holds the configuration of a particular FCE channel*/
typedef struct
{
  uint8 Fce_Channel;
  uint8 Dma_Channel;
  Crc_ResNotificationPtrType ResNotificationPtr;
  Crc_ErrNotificationPtrType ErrNotificationPtr;
}Crc_ChannelConfigType;
#endif

/*******************************************************************************
**                        Initial register values                             **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/
/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
/* Memory Map of the CRC Code */
#define CRC_START_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
 * without safeguard. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"

/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : void Crc_GetVersionInfo                                 **
**                                   (Std_VersionInfoType *Versioninfo)       **
**                                                                            **
** Description      : This service returns the version information            **
**                    of this module.The version information includes :       **
**                    - Module Id                                             **
**                    - Vendor Id                                             **
**                    - Vendor specific version numbers                       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x04                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters(out)  : Versioninfo (Pointer to where to store the version      **
**                                 information of this module)                **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
#if (CRC_VERSION_INFO_API == STD_ON)
extern void Crc_GetVersionInfo(Std_VersionInfoType* const Versioninfo);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Crc_GetVersionInfo(Versioninfo)\
                                 (ERROR_Crc_GetVersionInfo_API_IS_NOT_SELECTED)
#endif

/*******************************************************************************
** Traceability     :                                                         **
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
#if (CRC_8_MODE != STD_OFF)
extern uint8 Crc_CalculateCRC8
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint8 Crc_StartValue8,
  const boolean Crc_IsFirstCall
) ;
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Crc_CalculateCRC8(Crc_DataPtr, Crc_Length, Crc_StartValue8, \
                  Crc_IsFirstCall) (ERROR_Crc_CalculateCRC8_API_IS_NOT_SELECTED)
#endif

/*******************************************************************************
** Traceability     :                                                         **
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
#if (CRC_8H2F_MODE!=STD_OFF)
extern uint8 Crc_CalculateCRC8H2F
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint8 Crc_StartValue8H2F,
  const boolean Crc_IsFirstCall
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Crc_CalculateCRC8H2F(Crc_DataPtr, Crc_Length, Crc_StartValue8H2F, \
               Crc_IsFirstCall) (ERROR_Crc_CalculateCRC8H2F_API_IS_NOT_SELECTED)
#endif

/*******************************************************************************
** Traceability                                                               **
**                                                                            **
** Syntax           : uint16 Crc_CalculateCRC16                               **
**                     (                                                      **
**                      const uint8* const Crc_DataPtr,                       **
**                      const uint32 Crc_Length,                              **
**                      const uint16 Crc_StartValue16,                        **
**                      const boolean Crc_IsFirstCall                         **
**                     )                                                      **
**                                                                            **
** Description      : This function takes the value of input data pointer,    **
**                    start value and polynomial, calculates the crc taking   **
**                    the precomputed                                         **
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
#if (CRC_16_MODE!=STD_OFF)
extern uint16 Crc_CalculateCRC16
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint16 Crc_StartValue16,
  const boolean Crc_IsFirstCall
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Crc_CalculateCRC16(Crc_DataPtr, Crc_Length, Crc_StartValue16, \
                 Crc_IsFirstCall) (ERROR_Crc_CalculateCRC16_API_IS_NOT_SELECTED)
#endif

/*******************************************************************************
** Traceability                                                               **
** Syntax           : uint16 Crc_CalculateCRC16ARC                            **
**                    (                                                       **
**                     const uint8* const Crc_DataPtr,                        **
**                     const uint32 Crc_Length,                               **
**                     const uint16 Crc_StartValue16,                         **
**                     const boolean Crc_IsFirstCall                          **
**                    )                                                       **
**                                                                            **
** Description      : This function takes the value of input data pointer,    **
**                    start value and polynomial, calculates the crc taking   **
**                    the precomputed                                         **
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
#if (CRC_16ARC_MODE!=STD_OFF)
extern uint16 Crc_CalculateCRC16ARC
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint16 Crc_StartValue16,
  const boolean Crc_IsFirstCall
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Crc_CalculateCRC16ARC(Crc_DataPtr, Crc_Length, Crc_StartValue16, \
              Crc_IsFirstCall) (ERROR_Crc_CalculateCRC16ARC_API_IS_NOT_SELECTED)
#endif

/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : uint32 Crc_CalculateCRC32                               **
**                     (                                                      **
**                      const uint8* Crc_DataPtr,                             **
**                      const uint32 Crc_Length,                              **
**                      const uint32 Crc_StartValue32,                        **
**                      const boolean Crc_IsFirstCall                         **
**                     )                                                      **
**                                                                            **
** Description      : This function takes the value of input data pointer,    **
**                    start value and polynomial, calculates the crc taking   **
**                    the precomputed and reversed xor value  and returns     **
**                    the CRC xored with XOR value                            **
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
#if (CRC_32_MODE!=STD_OFF)
extern uint32 Crc_CalculateCRC32
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint32 Crc_StartValue32,
  const boolean Crc_IsFirstCall
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Crc_CalculateCRC32(Crc_DataPtr, Crc_Length, Crc_StartValue32, \
                 Crc_IsFirstCall) (ERROR_Crc_CalculateCRC32_API_IS_NOT_SELECTED)
#endif

/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : uint32 Crc_CalculateCRC32P4                             **
**                     (                                                      **
**                      const uint8* const Crc_DataPtr,                       **
**                      const uint32 Crc_Length,                              **
**                      const uint32 Crc_StartValue32,                        **
**                      const boolean Crc_IsFirstCall                         **
**                     )                                                      **
**                                                                            **
** Description      : This function takes the value of input data pointer,    **
**                    tart value and polynomial, calculates the crc taking    **
**                    the precomputed and reversed xor value  and returns     **
**                    the CRC xored with XOR value                            **
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
#if (CRC_32P4_MODE!=STD_OFF)
extern uint32 Crc_CalculateCRC32P4
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint32 Crc_StartValue32,
  const boolean Crc_IsFirstCall
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Crc_CalculateCRC32P4(Crc_DataPtr, Crc_Length, Crc_StartValue32, \
               Crc_IsFirstCall) (ERROR_Crc_CalculateCRC32P4_API_IS_NOT_SELECTED)
#endif

/*******************************************************************************
** Traceability     :                                                         **
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
#if (CRC_64_MODE!=STD_OFF)
extern uint64 Crc_CalculateCRC64
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint64 Crc_StartValue64,
  const boolean Crc_IsFirstCall
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Crc_CalculateCRC64(Crc_DataPtr, Crc_Length, Crc_StartValue64, \
                 Crc_IsFirstCall) (ERROR_Crc_CalculateCRC64_API_IS_NOT_SELECTED)
#endif

/*******************************************************************************
** Traceability     :                                                         **
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
#if (CRC_8_DMAMODE != STD_OFF)
extern Crc_DmaReturnType Crc_DmaCalculateCRC8
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint8 Crc_StartValue8,
  const boolean Crc_IsFirstCall
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Crc_DmaCalculateCRC8(Crc_DataPtr, Crc_Length, Crc_StartValue8, \
               Crc_IsFirstCall) (ERROR_Crc_DmaCalculateCRC8_API_IS_NOT_SELECTED)
#endif

/*******************************************************************************
** Traceability     :                                                         **
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
#if (CRC_16_DMAMODE != STD_OFF)
extern Crc_DmaReturnType Crc_DmaCalculateCRC16
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint16 Crc_StartValue16,
  const boolean Crc_IsFirstCall
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Crc_DmaCalculateCRC16(Crc_DataPtr, Crc_Length, Crc_StartValue16, \
              Crc_IsFirstCall) (ERROR_Crc_DmaCalculateCRC16_API_IS_NOT_SELECTED)
#endif

/*******************************************************************************
** Traceability     :                                                         **
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
#if (CRC_32_DMAMODE != STD_OFF)
extern Crc_DmaReturnType Crc_DmaCalculateCRC32
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint32 Crc_StartValue32,
  const boolean Crc_IsFirstCall
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Crc_DmaCalculateCRC32(Crc_DataPtr, Crc_Length, Crc_StartValue32, \
              Crc_IsFirstCall) (ERROR_Crc_DmaCalculateCRC32_API_IS_NOT_SELECTED)
#endif

/*******************************************************************************
** Traceability     :                                                         **
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
#if (CRC_32P4_DMAMODE != STD_OFF)
extern Crc_DmaReturnType Crc_DmaCalculateCRC32P4
(
  const uint8* const Crc_DataPtr,
  const uint32 Crc_Length,
  const uint32 Crc_StartValue32,
  const boolean Crc_IsFirstCall
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Crc_DmaCalculateCRC32P4(Crc_DataPtr, Crc_Length, Crc_StartValue32, \
            Crc_IsFirstCall) (ERROR_Crc_DmaCalculateCRC32P4_API_IS_NOT_SELECTED)
#endif

/******************************************************************************/
#define CRC_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
 * without safeguard. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"

/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/

/*******************************************************************************
**                            LOW Level Driver Definitions                    **
*******************************************************************************/

/*******************************************************************************
**                            LOW Level Driver Definitions                    **
*******************************************************************************/

#endif /* End for CRC_H */
