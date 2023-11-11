/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2020)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME     : CanTrcv_17_W9255.h                                        **
**                                                                           **
**  VERSION      : 10.0.0                                                     **
**                                                                           **
**  DATE         : 2020-10-14                                                **
**                                                                           **
**  VARIANT      : Variant PC                                                **
**                                                                           **
**  PLATFORM     : Infineon AURIX2G                                          **
**                                                                           **
**  AUTHOR       : DL-AUTOSAR-Engineering                                    **
**                                                                           **
**  VENDOR       : Infineon Technologies                                     **
**                                                                           **
**  TRACEABILITY : [cover parentID={CF471269-6F4F-4871-903A-3BEA0C746825}]   **
**                 [cover parentID={F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}]   **
**                                                                           **
**  DESCRIPTION  : CAN Transceiver W9255 Driver header definition file       **
**                                                                           **
**  [/cover]                                                                 **
**                                                                           **
**  SPECIFICATION(S) : Specification of CanTrcv Driver,AUTOSAR Release 4.2.2 **
**                     and 4.4.0                                             **
**                                                                           **
**  MAY BE CHANGED BY USER : no                                              **
**                                                                           **
******************************************************************************/
/* [cover parentID={CFC8F379-8006-46cb-A618-C485ED5235C3}] [/cover] */
#ifndef CanTrcv_17_W9255_H
#define CanTrcv_17_W9255_H
/*[cover parentID={E2878637-D6D2-412e-A4CA-141FDE5BCC00}] File Structure
[/cover]*/
/******************************************************************************
**                      Includes                                             **
******************************************************************************/
/*
  Include Communication Stack Types
    This file includes
        - Std_Types.h
  Std_Types.h incldes
        - Compiler.h
        - Platform_Types.h
*/
#include "ComStack_Types.h"

#include "Can_GeneralTypes.h"

/* Inclusion of EcuM Module header file */
#include "EcuM.h"

#include "Spi.h"

/* Pre-compile configuration parameters for CanTrcv_17_W9255 */
#include "CanTrcv_17_W9255_Cfg.h"

/******************************************************************************
**                      Global Macro Definitions                             **
******************************************************************************/

/* Vendor ID and Module ID of CanTrcv_17_W9255 driver */
/*[cover parentID={71889316-F75E-4c88-919F-8D0D293D8A21}][/cover]*/
#define CANTRCV_17_W9255_VENDOR_ID       ((uint16)17)
#define CANTRCV_17_W9255_MODULE_ID       ((uint16)70)

#if (CANTRCV_17_W9255_DEV_ERROR_DETECT == STD_ON)
/* DET - Default Error Tracer IDs */

/* API Service called with invalid CAN transceiver Channel ID */
/*[cover parentID={D9D69820-7A0A-4b26-B914-EC464F36AF6F}][/cover]*/
#define CANTRCV_17_W9255_E_INVALID_TRANSCEIVER            ((uint8)0x01)
/* API Service called with null parameter */
/*[cover parentID={23DEEFCD-0C25-4174-8E1E-81DBAC784EA6}][/cover]*/
#define CANTRCV_17_W9255_E_PARAM_POINTER                  ((uint8)0x02)
/* API Service used without initialization */
/*[cover parentID={9625D67A-19C6-45ca-ACBA-446FF8A4B03F}][/cover]*/
#define CANTRCV_17_W9255_E_UNINIT                         ((uint8)0x11)
/* API service called in wrong operation mode */
/*[cover parentID={2F14C2C9-1818-44bb-8704-18C1D302ECF9}][/cover]*/
#define CANTRCV_17_W9255_E_TRCV_NOT_STANDBY               ((uint8)0x21)
/* API service called in wrong operation mode */
/*[cover parentID={B4B56C86-A145-4dcc-85CE-802524563773}][/cover]*/
#define CANTRCV_17_W9255_E_TRCV_NOT_NORMAL                ((uint8)0x22)
/* API service called with invalid parameter for TrcvWakeupMode */
/*[cover parentID={F448A2C3-0647-4072-92E7-987834F69D9B}][/cover]*/
#define CANTRCV_17_W9255_E_PARAM_TRCV_WAKEUP_MODE         ((uint8)0x23)
/* API service called with invalid Opmode */
/*[cover parentID={F3C6273A-779D-46fd-AACE-D265769C4903}][/cover]*/
#define CANTRCV_17_W9255_E_PARAM_TRCV_OPMODE              ((uint8)0x24)
/* Init API not called with NULL_PTR as parameter */
/*[cover parentID={EB0ECDCA-0D25-401f-856C-531C0B69E506}][/cover]*/
#define CANTRCV_17_WV9255_E_INIT_FAILED                   ((uint8)0x27)
#endif

/* No/incorrect communication to the transceiver */
/*[cover parentID={0441BF70-F7A4-4b50-A32F-106C2F9F2DF9}][/cover]*/
#define CANTRCV_17_W9255_E_NO_TRCV_CONTROL                ((uint8)0x26)

/* API Service IDs */
/* API Service ID for CanTrcv_17_W9255_GetOpMode() */
#define CANTRCV_17_W9255_SID_GETOPMODE                    ((uint8)2)
/* API Service ID for CanTrcv_17_W9255_GetBusWuReason() */
#define CANTRCV_17_W9255_SID_GETBUSWUREASON               ((uint8)3)
/* API Service ID for CanTrcv_17_W9255_GetVersioninfo() */
#define CANTRCV_17_W9255_SID_GETVERSIONINFO               ((uint8)4)
/* API Service ID for CanTrcv_17_W9255_SetWakeupMode() */
#define CANTRCV_17_W9255_SID_SETWAKEUPMODE                ((uint8)5)
/* API Service ID for CanTrcv_17_W9255_GetTrcvSystemData() */
#define CANTRCV_17_W9255_SID_GETSYSTEMDATA                ((uint8)9)
/* API Service ID for CanTrcv_17_W9255_ClearTrcvWufFlag() */
#define CANTRCV_17_W9255_SID_CLEARWUFFLAG                 ((uint8)10)
/* API Service ID for CanTrcv_17_W9255_ReadTrcvTimeoutFlag() */
#define CANTRCV_17_W9255_SID_READTIMEOUTFLAG              ((uint8)11)
/* API Service ID for CanTrcv_17_W9255_ClearTrcvTimeoutFlag() */
#define CANTRCV_17_W9255_SID_CLEARTIMEOUTFLAG             ((uint8)12)
/* API Service ID for CanTrcv_17_W9255_ReadTrcvSilenceFlag() */
#define CANTRCV_17_W9255_SID_READSILENCEFLAG              ((uint8)13)
/* API Service ID for CanTrcv_17_W9255_SetPNActivationState() */
#define CANTRCV_17_W9255_SID_SETPNSTATE                   ((uint8)15)
/* API Service ID for CanTrcv_17_W9255_CheckWakeFlag() */
#define CANTRCV_17_W9255_SID_CHECKWAKEFLAG                ((uint8)14)
/* API Service ID for CanTrcv_17_W9255_CheckWakeup() */
#define CANTRCV_17_W9255_SID_CHECKWAKEUP                  ((uint8)7)
/* API Service ID for CanTrcv_17_W9255_MainFunction() */
#define CANTRCV_17_W9255_SID_MAINFUNCTION                 ((uint8)6)
/* API Service ID for CanTrcv_17_W9255_Init() */
#define CANTRCV_17_W9255_SID_INIT                         ((uint8)0)
/* API Service ID for CanTrcv_17_W9255_SetOpMode() */
#define CANTRCV_17_W9255_SID_SETOPMODE                    ((uint8)1)

/* Pending wakeup Set */
#define CANTRCV_17_W9255_PENWU_SET                        (1U)

/* CanTrcvWakeUpSupport modes */

/* CAN transceiver wakeup is supported by Polling */
#define CANTRCV_17_W9255_WAKE_UP_BY_POLLING              (1U)

/* CAN transceiver wakeup is supported by Interrupt */
#define CANTRCV_17_W9255_WAKE_UP_BY_INTERRUPT            (2U)

/* CAN transceiver macro when EcuM reference is not configured */
#define CANTRCV_17_W9255_WAKEUP_SOURCE_NOT_CONFIGURED    (0XFFU)

/* Values to be written to the Mode control register */
/* Normal Mode */
#define  CANTRCV_17_W9255_NORMAL_VAL                    ((uint16)(0x8108U))
/* Stand By Mode */
#define  CANTRCV_17_W9255_STANDBY_VAL                   ((uint16)(0x8102U))
/* Sleep Mode */
#define  CANTRCV_17_W9255_SLEEP_VAL                     ((uint16)(0x8101U))
/*****************************************************************************
**                      Global Function like macros                         **
*****************************************************************************/


/*****************************************************************************
**                      Global Type Definitions                             **
*****************************************************************************/

/* Type Definition for CanTrcv_17_W9255_ConfigType */
/* [cover parentID={9A4D857A-7CDB-4d7e-9458-A2D22791B793}] */
typedef void CanTrcv_17_W9255_ConfigType;
/* [/cover] */

/* Type Definition for CanTrcv_17_W9255_ChannelConfigType */
/* [cover parentID={45FB6087-A3DD-4fac-A1E3-688065F611DA}] [/cover] */
typedef struct
{
  /* Mode of the transceiver after initialization */
  uint16 CanTrcvInitState;
  /* Reference to the wakeup source */
  EcuM_WakeupSourceType CanTrcvWakeupSourceRef;
  /* Reference to the wakeup source of the channel in case of POR */
  EcuM_WakeupSourceType CanTrcvPorWakeupSourceRef;
  /* Reference to the wakeup source of the channel in case of SYSERR */
  EcuM_WakeupSourceType CanTrcvSyserrWakeupSourceRef;
  /* Channel Id */
  uint8 CanTrcvChannelId;
  /* Spi Sequence Id used by the transceiver channel */
  Spi_SequenceType CanTrcvSpiSequence;
  /* Spi Channel Id used by the transceiver channel */
  Spi_ChannelType CanTrcvSpiChannel;
  /* Wake-up by bus status */
  boolean CanTrcvWakeupByBusEnable;
} CanTrcv_17_W9255_ChannelConfigType;

/* Type Definition for CanTrcv_17_W9255_PNConfigType */
/* [cover parentID={6CA51A30-3F2E-47c4-B45E-689A777339D4}] [/cover] */
typedef struct
{
  /* Baudrate, Id, Id mask of the PN frame */
  const uint16 *CanTrcvPnIdInfoPtr;
  /* Data masks of the PN frame */
  const uint16 *CanTrcvPnDataInfoPtr;
  /* DLC of the PN frame */
  uint16 CanTrcvPnDlc;
} CanTrcv_17_W9255_PNConfigType;

/* Type Definition for CanTrcv_17_W9255_PNActivationType */
/* [cover parentID={53D94B44-835B-4db4-A2DD-96741B164D69}] */
typedef enum
{
  CANTRCV_17_W9255_PN_DISABLED = 0,
  CANTRCV_17_W9255_PN_ENABLED
} CanTrcv_17_W9255_PNActivationType;
/*  [/cover] */

/* Type Definition for CanTrcv_17_W9255_TrcvFlagStateType */
/* [cover parentID={C2E52E66-16AD-4c51-9F7E-84AC3425C6AA}] */
typedef enum
{
  CANTRCV_17_W9255_FLAG_CLEARED = 0,
  CANTRCV_17_W9255_FLAG_SET
} CanTrcv_17_W9255_TrcvFlagStateType;
/*  [/cover] */
/******************************************************************************
**                      Global Constant Declarations                         **
******************************************************************************/
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define CANTRCV_17_W9255_START_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
#include "CanTrcv_17_W9255_MemMap.h"
extern const CanTrcv_17_W9255_ChannelConfigType
CanTrcv_17_W9255_ChannelConfig[CANTRCV_17_W9255_CHANNELS_USED];
#if (CANTRCV_17_W9255_PN_CONFIGURED_CHANNELS > 0U)
extern const CanTrcv_17_W9255_PNConfigType
CanTrcv_17_W9255_PNConfig[CANTRCV_17_W9255_PN_CONFIGURED_CHANNELS];
#endif
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define CANTRCV_17_W9255_STOP_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
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
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_W9255_MemMap.h"
extern const uint8
CanTrcv_17_W9255_ChannelUsed[CANTRCV_17_W9255_CHANNELS_CONFIGURED];
extern const uint8
CanTrcv_17_W9255_PnConfigured[CANTRCV_17_W9255_CHANNELS_CONFIGURED];
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define CANTRCV_17_W9255_STOP_SEC_CONFIG_DATA_QM_LOCAL_8
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_W9255_MemMap.h"
/******************************************************************************
**                      Global Variable Declarations                         **
******************************************************************************/
/******************************************************************************
**                      Global Function Declarations                         **
******************************************************************************/
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define CANTRCV_17_W9255_START_SEC_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: CanTrcv_17_W9255_MemMap.h is
repeatedly included without include guard. This is as per AUTOSAR */
#include "CanTrcv_17_W9255_MemMap.h"

/* CanTrcv_17_W9255_Init API  */
/******************************************************************************
** Syntax          : void  CanTrcv_17_W9255_Init(                            **
**                      const CanTrcv_ConfigType * const ConfigPtr)          **
**                                                                           **
** Service ID      : 0x00                                                    **
**                                                                           **
** Sync/Async      :  Synchronous                                            **
**                                                                           **
** Reentrancy      :  Non reentrant                                          **
**                                                                           **
** Parameters (in) : ConfigPtr : Pointer to driver configuration             **
**                                                                           **
** Parameters (out):  none                                                   **
**                                                                           **
** Return value    :  None                                                   **
**                                                                           **
** Description     : This API initializes the CAN Transceiver module. The    **
**                   registers of the TLE9255W hardware are initialized as   **
**                   per the configuration. The CAN Transceiver              **
**                   initialization status is set at the end of the          **
**                   initialization function execution.                      **
**                                                                           **
******************************************************************************/

extern void CanTrcv_17_W9255_Init(
                          const CanTrcv_17_W9255_ConfigType* const ConfigPtr);

/* CanTrcv_17_W9255_SetOpMode API  */
/******************************************************************************
** Syntax          : Std_ReturnType  CanTrcv_17_W9255_SetOpMode (            **
**                     const uint8 Transceiver,                              **
**                     const CanTrcv_TrcvModeType OpMode)                    **
**                                                                           **
**                                                                           **
** Service ID      : 0x01                                                    **
**                                                                           **
** Sync/Async      : Asynchronous                                            **
**                                                                           **
** Reentrancy      : Reentrant for different transceivers                    **
**                                                                           **
** Parameters (in) : OpMode - This parameter contains the desired            **
**                           operating mode                                  **
**                   Transceiver - CAN transceiver to which API call         **
**                                has to be applied                          **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value    : E_OK : will be returned if the request for transceiver  **
**                       mode change has been accepted                       **
**                   E_NOT_OK : will be returned if the request for          **
**                       transceiver mode change has not been accepted or    **
**                        any parameter is out of the allowed range          **
**                                                                           **
** Description     : Sets the mode of the Transceiver to the value OpMode    **
**                                                                           **
******************************************************************************/

extern Std_ReturnType  CanTrcv_17_W9255_SetOpMode(
    const uint8 Transceiver,
    const CanTrcv_TrcvModeType OpMode);

/* CanTrcv_17_W9255_GetOpMode API  */
/******************************************************************************
** Syntax          : Std_ReturnType  CanTrcv_17_W9255_GetOpMode(             **
**                       const uint8 Transceiver,                            **
**                       CanTrcv_TrcvModeType * const OpMode)                **
**                                                                           **
** Service ID      : 0x02                                                    **
**                                                                           **
** Sync/Async      : Synchronous                                             **
**                                                                           **
** Reentrancy      : Reentrant                                               **
**                                                                           **
** Parameters (in) : Transceiver - CAN transceiver to which API call has     **
**                                 to be applied                             **
**                                                                           **
**                                                                           **
** Parameters (out): OpMode - Pointer to operation mode of the transceiver   **
**                            the API is applied to                          **
**                                                                           **
** Return value    : E_OK : will be returned if the operation mode           **
**                          was detected                                     **
**                   E_NOT_OK : will be returned if the operation mode       **
**                              was not detected                             **
**                                                                           **
** Description     : Gets the mode of the Transceiver and returns it in      **
**                   parameter OpMode                                        **
******************************************************************************/

extern Std_ReturnType  CanTrcv_17_W9255_GetOpMode(
    const uint8 Transceiver,
    CanTrcv_TrcvModeType * const OpMode);

/* CanTrcv_17_W9255_GetBusWuReason API  */
/******************************************************************************
** Syntax          : Std_ReturnType  CanTrcv_17_W9255_GetBusWuReason(        **
**                        const uint8 Transceiver,                           **
**                        CanTrcv_TrcvWakeupReasonType * const reason)       **
**                                                                           **
** Service ID      : 0x03                                                    **
**                                                                           **
** Sync/Async      : Synchronous                                             **
**                                                                           **
** Reentrancy      : Reentrant                                               **
**                                                                           **
** Parameters (in) : Transceiver - CAN transceiver to which API call has to  **
**                                 be applied                                **
**                                                                           **
** Parameters (out): reason - Pointer to wake up reason of the bus the API   **
**                            is applied to                                  **
**                                                                           **
** Return value    : E_OK : will be returned if the transceiver wakeup       **
**                          reason was provided                              **
**                   E_NOT_OK : will be returned if no wake up reason is     **
**                              available or if the service request failed   **
**                              due to development errors                    **
**                                                                           **
** Description     : Gets the wakeup reason for the Transceiver and returns  **
**                   it in parameter Reason                                  **
**                                                                           **
******************************************************************************/

extern Std_ReturnType  CanTrcv_17_W9255_GetBusWuReason(
    const uint8 Transceiver,
    CanTrcv_TrcvWakeupReasonType * const reason);

#if (CANTRCV_17_W9255_GET_VERSION_INFO == STD_ON)
/* CanTrcv_17_W9255_GetVersionInfo API  */
/*******************************************************************************
** Syntax          : void  CanTrcv_17_W9255_GetVersionInfo (                  **
**                        Std_VersionInfoType * const versioninfo )           **
**                                                                            **
** Service ID      : 0x04                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): versioninfo - Pointer to where to store version          **
**                                 information of this module                 **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : Gets the version of the module and returns it in         **
**                   versioninfo                                              **
**                                                                            **
*******************************************************************************/

extern void CanTrcv_17_W9255_GetVersionInfo(
    Std_VersionInfoType* const versioninfo);

#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define CanTrcv_17_W9255_GetVersionInfo(versioninfo)                          \
                    (ERROR_CanTrcv_17_W9255_GetVersionInfo_API_IS_NOT_SELECTED)
#endif
/******************************************************************************/
/* CanTrcv_17_W9255_SetWakeupMode API  */
/******************************************************************************
** Syntax          : Std_ReturnType  CanTrcv_17_W9255_SetWakeupMode (        **
**                    const uint8 Transceiver,                               **
**                    const CanTrcv_TrcvWakeupModeType TrcvWakeupMode)       **
**                                                                           **
**                                                                           **
** Service ID      : 0x05                                                    **
**                                                                           **
** Sync/Async      : Synchronous                                             **
**                                                                           **
** Reentrancy      : Reentrant for different transceivers                    **
**                                                                           **
** Parameters (in) : TrcvWakeupMode - Requested Transceiver Wakeup Mode      **
**                   Transceiver - CAN transceiver to which API call has     **
**                                to be applied                              **
**                                                                           **
** Parameters (out): None                                                    **
**                                                                           **
** Return value    : E_OK : Wakeup state changed to the requested mode       **
**                   E_NOT_OK : Wakeup state change has failed or the        **
**                              parameter is out of the allowed range. The   **
**                              previous state has not been changed.         **
**                                                                           **
** Description     : This function enables, disables and clears the          **
**                   notification for wake up events of the Transceiver      **
**                   according to the parameter TrcvWakeupMode               **
**                                                                           **
******************************************************************************/

extern Std_ReturnType  CanTrcv_17_W9255_SetWakeupMode(
    const uint8 Transceiver,
    const CanTrcv_TrcvWakeupModeType TrcvWakeupMode);

/* CanTrcv_17_W9255_CheckWakeup API  */
/*******************************************************************************
** Syntax          : Std_ReturnType  CanTrcv_17_W9255_CheckWakeup (           **
**                    const uint8 Transceiver )                               **
**                                                                            **
** Service ID      : 0x07                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : Transceiver - CAN transceiver to which API call has      **
**                                 to be applied                              **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value    : E_OK  : API call has been accepted                       **
**                   E_NOT_OK  : API call has not been accepted               **
**                                                                            **
** Description     : This service is called by the underlying CanIf, both in  **
**                   cases of polling and interrupt mode. This API validates  **
**                   wake-up event and if true, reports it to EcuM.           **
**                                                                            **
*******************************************************************************/

extern Std_ReturnType  CanTrcv_17_W9255_CheckWakeup(
    const uint8 Transceiver);

/* CanTrcv_17_W9255_CheckWakeFlag API  */
/*******************************************************************************
** Syntax          : Std_ReturnType  CanTrcv_17_W9255_CheckWakeFlag (         **
**                   const uint8 Transceiver )                                **
**                                                                            **
**                                                                            **
** Service ID      : 0x0e                                                     **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : Transceiver - CAN transceiver to which API call has      **
**                                 to be applied                              **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK  : Will be returned, if the request for checking the**
**                          wakeup flag has been accepted                     **
**                   E_NOT_OK  : Will be returned, if the request for checking**
**                          the wakeup flag has not been accepted             **
**                                                                            **
** Description     : This API checks the status of the wake-up flags from the **
**                   transceiver hardware and if set, clears them and reports **
**                   the wake-up event to the EcuM. The driver also informs   **
**                   the CanIf with the callback notification                 **
**                   CanIf_CheckTrcvWakeFlagIndication, that the wake flags   **
**                   of the CAN transceiver with the corresponding Transceiver**
**                   ID has been checked.                                     **
**                                                                            **
*******************************************************************************/

extern Std_ReturnType  CanTrcv_17_W9255_CheckWakeFlag(
    const uint8 Transceiver);

/* CanTrcv_17_W9255_ClearTrcvTimeoutFlag API  */
/******************************************************************************
** Syntax          : Std_ReturnType  CanTrcv_17_W9255_ClearTrcvTimeoutFlag ( **
**                    const uint8 Transceiver)                               **
**                                                                           **
** Service ID      : 0x0c                                                    **
**                                                                           **
** Sync/Async      : Synchronous                                             **
**                                                                           **
** Reentrancy      : Non Reentrant                                           **
**                                                                           **
** Parameters (in) : Transceiver - CAN transceiver to which API call has     **
**                                 to be applied                             **
**                                                                           **
** Parameters (out): None                                                    **
**                                                                           **
** Return value    : E_OK  : Will be returned, if the timeout flag is        **
**                           successfully cleared.                           **
**                   E_NOT_OK  : Will be returned, if the timeout flag could **
**                               not be cleared.                             **
**                                                                           **
** Description     : This API clears the status of the timeout flag in the   **
**                   transceiver hardware. Since the configuration parameter **
**                   CanTrcvHwPnSupport is always TRUE, the availability of  **
**                   this API is not dependent on the configuration          **
**                   parameter. The timeout flag indicates whether or not    **
**                   the TLE9255W hardware has entered the Selective Sleep   **
**                   Sub-Mode at least once.                                 **
**                                                                           **
******************************************************************************/

extern Std_ReturnType  CanTrcv_17_W9255_ClearTrcvTimeoutFlag(
    const uint8 Transceiver);

/* CanTrcv_17_W9255_ClearTrcvWufFlag API  */
/******************************************************************************
** Syntax          : Std_ReturnType  CanTrcv_17_W9255_ClearTrcvWufFlag (     **
**                     const uint8 Transceiver)                              **
**                                                                           **
** Service ID      : 0x0a                                                    **
**                                                                           **
** Sync/Async      : Synchronous                                             **
**                                                                           **
** Reentrancy      : Reentrant for different transceivers                    **
**                                                                           **
** Parameters (in) : Transceiver - CAN transceiver to which API call has     **
**                                 to be applied                             **
**                                                                           **
** Parameters (out): None                                                    **
**                                                                           **
** Return value    : E_OK  : will be returned if the WUF flag has been       **
**                           cleared                                         **
**                   E_NOT_OK  : will be returned if the WUF flag has not    **
**                               been cleared or a development error occurred**
**                                                                           **
** Description     : This API clears the WUF flag in the transceiver         **
**                   hardware. Since the configuration parameter             **
**                   CanTrcvHwPnSupport is always TRUE, the availability of  **
**                   this API is not dependent on the configuration          **
**                   parameter.                                              **
**                                                                           **
******************************************************************************/

extern Std_ReturnType  CanTrcv_17_W9255_ClearTrcvWufFlag(
    const uint8 Transceiver);

/* CanTrcv_17_W9255_GetTrcvSystemData API */
/******************************************************************************
** Syntax          : Std_ReturnType  CanTrcv_17_W9255_GetTrcvSystemData(     **
**                   const uint8 Transceiver,                                **
**                   uint32 * const TrcvSysData)                             **
**                                                                           **
**                                                                           **
** Service ID      : 0x09                                                    **
**                                                                           **
** Sync/Async      : Synchronous                                             **
**                                                                           **
** Reentrancy      : Non Reentrant                                           **
**                                                                           **
** Parameters (in) : Transceiver - CAN transceiver to which API call has     **
**                                 to be applied                             **
**                                                                           **
** Parameters(out) : TrcvSysData - This parameter holds the selective wake   **
**                                 status, error status, transceiver status  **
**                                 and wake-up event status information. The **
**                                 first 8 bits of LSB contain the data      **
**                                 stored in TRANS_STAT register, the next 8 **
**                                 bits contain the data in ERR_STAT         **
**                                 register, the next 8 bits depict the data **
**                                 stored in WAKE_STAT register and the last **
**                                 8 bits contain the data stored in SWK_STAT**
**                                 register                                  **
**                                                                           **
** Return value    : E_OK  : will be returned if the transceiver status is   **
**                           successfully read                               **
**                   E_NOT_OK  : will be returned if the transceiver status  **
**                               data is not available or a development error**
**                               occurs                                      **
**                                                                           **
** Description     : This API reads the transceiver status data and returns  **
**                   it through parameter TrcvSysData. Since the             **
**                   configuration parameter CanTrcvHwPnSupport is always    **
**                   TRUE, the availability of this API is not dependent on  **
**                   the configuration parameter.                            **
**                                                                           **
******************************************************************************/

extern Std_ReturnType  CanTrcv_17_W9255_GetTrcvSystemData(
    const uint8 Transceiver,
          uint32 * const TrcvSysData);

/* CanTrcv_17_W9255_ReadTrcvSilenceFlag API */
/******************************************************************************
** Syntax          : Std_ReturnType  CanTrcv_17_W9255_ReadTrcvSilenceFlag (  **
**                     const uint8 Transceiver,                              **
**                     CanTrcv_17_W9255_TrcvFlagStateType * const FlagState) **
**                                                                           **
**                                                                           **
** Service ID      : 0x0d                                                    **
**                                                                           **
** Sync/Async      : Synchronous                                             **
**                                                                           **
** Reentrancy      : Non Reentrant                                           **
**                                                                           **
** Parameters (in) : Transceiver - CAN transceiver to which API call has     **
**                                 to be applied                             **
**                                                                           **
** Parameters (out): FlagState - State of the silence flag                   **
**                                                                           **
** Return value    : E_OK  : Will be returned, if status of the silence flag **
**                           is successfully read                            **
**                   E_NOT_OK  : Will be returned, if status of the silence  **
**                               flag could not be read                      **
**                                                                           **
** Description     : This API reads the status of the silence flag from the  **
**                   transceiver hardware. Since the configuration parameter **
**                   CanTrcvHwPnSupport is always TRUE, the availability of  **
**                   this API is not dependent on the configuration          **
**                   parameter. The silence flag, if set, indicates that     **
**                   there is no communication on the CAN bus for a specified**
**                   period of time (0.6 - 1.2 seconds). It helps to identify**
**                   whether or not the TLE9255W hardware is in the          **
**                   Selective Sleep Sub-Mode.                               **
**                                                                           **
******************************************************************************/

extern Std_ReturnType  CanTrcv_17_W9255_ReadTrcvSilenceFlag(
    const uint8 Transceiver,
    CanTrcv_17_W9255_TrcvFlagStateType * const FlagState);

/* CanTrcv_17_W9255_ReadTrcvTimeoutFlag API */
/******************************************************************************
** Syntax          : Std_ReturnType  CanTrcv_17_W9255_ReadTrcvTimeoutFlag (  **
**                     const uint8 Transceiver,                              **
**                     CanTrcv_17_W9255_TrcvFlagStateType * const FlagState) **
**                                                                           **
**                                                                           **
** Service ID      : 0x0b                                                    **
**                                                                           **
** Sync/Async      : Synchronous                                             **
**                                                                           **
** Reentrancy      : Non Reentrant                                           **
**                                                                           **
** Parameters (in) : Transceiver - CAN transceiver to which API call has     **
**                                 to be applied                             **
**                                                                           **
** Parameters (out): FlagState - State of the timeout flag                   **
**                                                                           **
** Return value    : E_OK  : Will be returned, if status of the timeout flag **
**                           is successfully read                            **
**                   E_NOT_OK  : Will be returned, if status of the          **
**                               timeout flag could not be read              **
**                                                                           **
** Description     : This API reads the status of the timeout flag from the  **
**                   transceiver hardware. Since the configuration parameter **
**                   CanTrcvHwPnSupport is always TRUE, the availability of  **
**                   this API is not dependent on the configuration          **
**                   parameter. The timeout flag indicates whether or not    **
**                   the TLE9255W hardware has entered the Selective Sleep   **
**                   Sub-Mode at least once.                                 **
**                                                                           **
******************************************************************************/

extern Std_ReturnType  CanTrcv_17_W9255_ReadTrcvTimeoutFlag(
    const uint8 Transceiver,
    CanTrcv_17_W9255_TrcvFlagStateType * const FlagState);

/* CanTrcv_17_W9255_SetPNActivationState API */
/******************************************************************************
** Syntax          : Std_ReturnType  CanTrcv_17_W9255_SetPNActivationState(  **
**                   const CanTrcv_17_W9255_PNActivationType ActivationState)**
**                                                                           **
**                                                                           **
** Service ID      : 0x0f                                                    **
**                                                                           **
** Sync/Async      : Synchronous                                             **
**                                                                           **
** Reentrancy      : Non Reentrant                                           **
**                                                                           **
** Parameters (in) : ActivationState - CANTRCV_17_W9255_PN_ENABLED: PN       **
**                                     wakeup functionality in CanTrcv shall **
**                                     be enabled                            **
**                                     CANTRCV_17_W9255_PN_DISABLED: PN      **
**                                     wakeup functionality in CanTrcv shall **
**                                     be disabled                           **
** Parameters (out): None                                                    **
**                                                                           **
** Return value    : E_OK  : Will be returned, if the PN has been changed    **
**                       to the requested configuration                      **
**                   E_NOT_OK  : Will be returned, if the PN configuration   **
**                          change has failed. The previous configuration    **
**                          has not been changed                             **
**                                                                           **
** Description     : This API enables/disables selective wake-up             **
**                   functionality of the transceiver.                       **
**                                                                           **
******************************************************************************/

extern Std_ReturnType  CanTrcv_17_W9255_SetPNActivationState(
    const CanTrcv_17_W9255_PNActivationType ActivationState);
/******************************************************************************
**                      Global Inline Function Definitions                    *
******************************************************************************/
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define CANTRCV_17_W9255_STOP_SEC_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: CanTrcv_17_W9255_MemMap.h is repeatedly
included without include guard. This is as per AUTOSAR */
#include "CanTrcv_17_W9255_MemMap.h"
#endif
