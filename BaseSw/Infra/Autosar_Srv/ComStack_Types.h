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
**  FILENAME     : ComStack_Types.h                                           **
**                                                                            **
**  VERSION      : 4.0.0                                                      **
**                                                                            **
**  DATE         : 2020-06-28                                                 **
**                                                                            **
**  VARIANT      : NA                                                         **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Type Definition for Com Stack                              **
**                                                                            **
**  SPECIFICATION(S) : AUTOSAR_SWS_CommunicationStackTypes.pdf, AUTOSAR       **
**                     Release 4.2.2 and 4.4.0                                **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
/* Traceability:
 [cover parentID={6EFE97CB-F5F0-460e-B4C5-1D143599991E}]
 Files inclusion
 [/cover]*/

#ifndef COMSTACK_TYPES_H
#define COMSTACK_TYPES_H

/*****************************************************************************
**                      Include Section                                     **
*****************************************************************************/
/* Traceability:
 [cover parentID={B6DD2FBA-E4D7-4e6f-9065-124B8D8B5F50}]
 [/cover]*/
#include "Std_Types.h"                  /* standard AUTOSAR types           */
#include "ComStack_Cfg.h"
#include "McalLib.h"
/*****************************************************************************
**                      Global Symbols                                      **
*****************************************************************************/

/*****************************************************************************
**                      Global Data Types (ECU independent)                 **
*****************************************************************************/
/* The Icom configuration ID */

typedef uint8  IcomConfigIdType;

/* Used to store the identifier of a partial network cluster. */
typedef uint8  PNCHandleType;

/* Variables of this type shall be used to return the bus status
   evaluated by a transceiver. */
typedef uint8  BusTrcvErrorType;
#define BUSTRCV_OK ((BusTrcvErrorType)0x00u)
#define BUSTRCV_E_ERROR ((BusTrcvErrorType)0x01u)

typedef uint8 NetworkHandleType;

/* The type for errors which can occur when activating or
deactivating Pretended Networking. */
typedef enum
{
  ICOM_SWITCH_E_OK,
  ICOM_SWITCH_E_FAILED
} IcomSwitch_ErrorType;

#if (MCAL_AR_VERSION == MCAL_AR_422)
/* Basic information about a PDU of any type */
typedef struct
{
  uint8          *SduDataPtr;
  PduLengthType   SduLength;
} PduInfoType;
#else
  /* Basic information about a PDU of any type */
typedef struct
{
  uint8          *SduDataPtr;
  uint8          *MetaDataPtr;
  PduLengthType   SduLength;
} PduInfoType;
#endif
  
/* Variables of this type shall be used to store the result of a buffer request. */
typedef enum
{
  BUFREQ_OK,
  BUFREQ_E_NOT_OK,
  BUFREQ_E_BUSY,
  BUFREQ_E_OVFL
} BufReq_ReturnType;

/*****************************************************************************
**                      Global Data                                         **
*****************************************************************************/


/*****************************************************************************
**                      Global Functions                                    **
*****************************************************************************/


#endif /* COMSTACK_TYPES_H */
