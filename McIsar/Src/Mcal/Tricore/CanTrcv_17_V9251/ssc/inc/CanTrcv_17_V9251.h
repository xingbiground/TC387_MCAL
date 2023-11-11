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
**  FILENAME     : CanTrcv_17_V9251.h                                         **
**                                                                            **
**  VERSION      : 8.0.0                                                      **
**                                                                            **
**  DATE         : 2020-09-24                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY :  [cover parentID={30E0AD47-7C67-49b5-8046-2597D28B6E7E},   **
**                                  {F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}]   **
**                                                                            **
**  DESCRIPTION  : CanTrcv Driver Header file                                 **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of CanTrcv Driver,AUTOSAR Release 4.2.2  **
**                                                 and AUTOSAR Release 4.4.0  **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef CANTRCV_17_V9251_H
#define CANTRCV_17_V9251_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/*[cover parentID={6AF440EA-FC8A-4548-BF8F-8A6370FBED49}]
Imported types [/cover]*/

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

/* Include Dio header file */
#include "Dio.h"
/* Pre-compile configuration parameters for CanTrcv */
#include "CanTrcv_17_V9251_Cfg.h"
/* Inclusion of EcuM Module header file*/
#include "EcuM.h"
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/* Vendor ID and Module ID of CanTrcv_17_V9251 driver */
/*[cover parentID={21DFE4D6-4CD8-4182-A954-2D87C1317A9D}][/cover]*/
#define CANTRCV_17_V9251_VENDOR_ID                        ((uint16)17)
#define CANTRCV_17_V9251_MODULE_ID                        ((uint16)70)

/* DET error code called with invalid CAN Network Parameter */
/*[cover parentID={FF56546A-32B7-4c90-8E23-D1975682C78D}][/cover]*/
#define CANTRCV_17_V9251_E_INVALID_TRANSCEIVER            ((uint8)0x01)
/* DET error code called with null parameter */
/* [cover parentID={97EFE262-2229-42bc-AD6C-4C9B0F9A7362}][/cover]*/
#define CANTRCV_17_V9251_E_PARAM_POINTER                  ((uint8)0x02)
/* DET error code used without initialization */
/*[cover parentID={7996D167-641D-44cf-95D8-C00D8577E52D}][/cover]*/
#define CANTRCV_17_V9251_E_UNINIT                         ((uint8)0x11)
/* DET error code called with invalid parameter for TrcvWakeupMode*/
/* [cover parentID={CEBF59C3-A877-4e77-A922-C9FED9EA28F2}][/cover] */
#define CANTRCV_17_V9251_E_PARAM_TRCV_WAKEUP_MODE         ((uint8)0x23)
/* DET error code called with invalid Opmode */
/*[cover parentID={A7E69693-B894-4f84-8687-23C28EDA72B6}][/cover] */
#define CANTRCV_17_V9251_E_PARAM_TRCV_OPMODE              ((uint8)0x24)
/* DET error code Module initialization has failed */
/*[cover parentID={BB752551-8450-4ec9-87FC-1738EB2580B1}][/cover] */
#define CANTRCV_17_V9251_E_INIT_FAILED                    ((uint8)0x27)
/*
  API Service ID's
*/
/* API Service ID for CanTrcv_17_V9251_Init() */
#define CANTRCV_17_V9251_SID_INIT                         ((uint8)0)
/* API Service ID for CanTrcv_17_V9251_SetOpMode() */
#define CANTRCV_17_V9251_SID_SETOPMODE                    ((uint8)1)
/* API Service ID for CanTrcv_17_V9251_GetOpMode() */
#define CANTRCV_17_V9251_SID_GETOPMODE                    ((uint8)2)
/* API Service ID for CanTrcv_17_V9251_GetBusWuReason() */
#define CANTRCV_17_V9251_SID_GETBUSWUREASON               ((uint8)3)
/* API Service ID for CanTrcv_17_V9251_GetVersioninfo() */
#define CANTRCV_17_V9251_SID_GETVERSIONINFO               ((uint8)4)
/* API Service ID for CanTrcv_17_V9251_SetWakeupMode() */
#define CANTRCV_17_V9251_SID_SETWAKEUPMODE                ((uint8)5)
/* API Service ID for CanTrcv_17_V9251_CheckWakeUp() */
#define CANTRCV_17_V9251_SID_CHECKWAKEUP                  ((uint8)7)


/* Pending wakeup Set */
#define CANTRCV_17_V9251_PENWU_SET                        (1U)

/* CAN transceiver wakeup is supported by Interrupt */
#define  CANTRCV_17_V9251_WAKE_UP_BY_INTERRUPT            (1U)
/* CAN transceiver operation modes */
#define CANTRCV_17_V9251_NORMAL_MODE                      ((Dio_LevelType)(0U))
#define CANTRCV_17_V9251_STANDBY_MODE                     ((Dio_LevelType)(1U))

/* CAN transceiver macros when EcuM and ICU reference not configured */
#define WAKEUP_SOURCE_NOT_CONFIGURED                      (0xFFFFU)
#define ICU_REFERENCE_NOT_CONFIGURED                      (0xFFFFU)

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
/*
Type: CanTrcv_ConfigType
[cover parentID={5141BA5F-497F-4c32-92AD-7854A6FC4DF3}][/cover]
*/
typedef void CanTrcv_17_V9251_ConfigType;

/*
Type: CanTrcv_17_V9251_ChannelInfoType
[cover parentID={A2B28E4F-82D1-4ddb-AB14-9A7767AE9CE2}][/cover]
*/
typedef struct
{
  /* CAN Transceiver State after Initialization. */
  CanTrcv_TrcvModeType CanTrcv_17_V9251_NetworkMode;

  /* EcuMWakeupSource Id */
  EcuM_WakeupSourceType CanTrcv_17_V9251_WakeupSourceRef;

  /* Reference to a DIO Channel */
  Dio_ChannelType CanTrcv_17_V9251_DioChannel;

  /* Internal value for setting DIO Level based on CanTrcv mode */
  Dio_LevelType CanTrcv_17_V9251_DioPinLevel;

  /* Channel Id of Cantrcv Channel*/
  uint8 CanTrcv_17_V9251_ChannelId;

  /*Specifies wake up by bus Used/Not Used */
  boolean CanTrcv_17_V9251_WakeupbyBus;

} CanTrcv_17_V9251_ChannelInfoType;

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/
/* [cover parentID={DC0F3BD1-1815-492a-8B3D-D19A2DBC37C6}]
    MemMap file  [/cover] */
/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
    MemMap for variables  [/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
    MemMap file  [/cover] */
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
    MemMap for const  [/cover] */
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define CANTRCV_17_V9251_START_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
#include "CanTrcv_17_V9251_MemMap.h"

extern const CanTrcv_17_V9251_ChannelInfoType
CanTrcv_17_V9251_ChannelConfig[CANTRCV_17_V9251_CHANNELS_USED];
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
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_V9251_MemMap.h"

extern const uint8 CanTrcv_17_V9251_ChannelUsed[CANTRCV_17_V9251_CHANNELS_CFG];
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
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_V9251_MemMap.h"
/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/
/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
#define CANTRCV_17_V9251_START_SEC_CODE_QM_LOCAL
/* [cover parentID={DC0F3BD1-1815-492a-8B3D-D19A2DBC37C6}]
    MemMap file  [/cover] */
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
    MemMap file  [/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
    MemMap file  [/cover] */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_V9251_MemMap.h"


/*******************************************************************************
** Traceability      :                                                        **
**                                                                            **
**                                                                            **
** Syntax            : void CanTrcv_17_V9251_Init                             **
**                                  (const CanTrcv_ConfigType* ConfigPtr)     **
**                                                                            **
**                                                                            **
** Description       : This API initializes the CanTrcv_17_V9251 module by    **
**                     setting CAN transceiver hardware to the mode           **
**                     configured by the configuration parameter              **
**                     CanTrcvInitState.                                      **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID        :  0x00                                                  **
**                                                                            **
** Sync/Async        :  Synchronous                                           **
**                                                                            **
** Reentrancy        :  non reentrant                                         **
**                                                                            **
** Parameters (in)   :  ConfigPtr - Pointer to driver configuration.          **
**                                                                            **
**                      Note: Since CanTrcv_17_V9251 module is pre-compile    **
**                      module, NULL_PTR must be passed as the parameter for  **
**                      CanTrcv_17_V9251_Init API.                            **
**                                                                            **
** Parameters (out)  :  none                                                  **
**                                                                            **
** Return value      :  none                                                  **
**                                                                            **
*******************************************************************************/
extern void CanTrcv_17_V9251_Init(const CanTrcv_17_V9251_ConfigType*
                                                              const ConfigPtr);


/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
**                                                                            **
** Syntax           : Std_ReturnType CanTrcv_17_V9251_SetOpMode               **
**                     (const uint8 Transceiver, const CanTrcv_TrcvModeType   **
**                                                                   OpMode)  **
**                                                                            **
**                                                                            **
** Description      : This API sets the mode of the CAN transceiver given     **
**                                                      the value OpMode.     **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x01                                                    **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant for different transceiver.                    **
**                                                                            **
** Parameters (in)  : Transceiver -CAN Transceiver to which API call has      **
**                                 to be applied.                             **
**                    OpMode - This parameter contains the desired operating  **
**                                                                    mode.   **
**                                                                            **
** Parameters (out) :  none                                                   **
**                                                                            **
** Return value     :  E_OK: CAN Transceiver state have been changed to       **
**                           requested mode.                                  **
**                     E_NOT_OK: CAN Transceiver state change failed or the   **
**                               parameter is out of the allowed range.       **
**                                                                            **
*******************************************************************************/

extern Std_ReturnType CanTrcv_17_V9251_SetOpMode
(
  const uint8 Transceiver, const CanTrcv_TrcvModeType OpMode
);

/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
**                                                                            **
** Syntax           : Std_ReturnType CanTrcv_17_V9251_GetOpMode               **
**                     (const uint8 Transceiver, CanTrcv_TrcvModeType* const  **
**                                                                   OpMode)  **
**                                                                            **
**                                                                            **
** Description      : This API reads the mode of the CAN transceiver and      **
**                                    returns it in the parameter OpMode.     **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x02                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different transceiver.                    **
**                                                                            **
** Parameters (in)  : Transceiver -CAN Transceiver to which API call has      **
**                                 to be applied.                             **
**                                                                            **
** Parameters (out) :  OpMode - Pointer to operation mode of the applied      **
**                              CAN transceiver.                              **
**                                                                            **
** Return value     :  E_OK : Operation mode read successfully.               **
**                     E_NOT_OK : Operation mode was not detected.            **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType CanTrcv_17_V9251_GetOpMode
(
  const uint8 Transceiver, CanTrcv_TrcvModeType* const OpMode
);

/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
**                                                                            **
**                                                                            **
** Syntax           : Std_ReturnType CanTrcv_17_V9251_GetBusWuReason          **
**                    (const uint8 Transceiver,CanTrcv_TrcvWakeupReasonType*  **
**                                                            const reason)   **
**                                                                            **
** Description      : This API reads the wakeup reason for the CAN            **
**                    transceiver and returns it in the parameter reason.     **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       :  0x03                                                   **
**                                                                            **
** Sync/Async       :  Synchronous                                            **
**                                                                            **
** Reentrancy       :  Reentrant for different transceivers.                  **
**                                                                            **
** Parameters (in)  :  Transceiver -CAN transceiver to which API call has     **
**                                  to be applied.                            **
**                                                                            **
** Parameters (out) :  reason - Pointer to wake up reason of the applied      **
**                              CAN transceiver.                              **
**                                                                            **
** Return value     :  E_OK: Transceiver wakeup reason was provided           **
**                           successfully.                                    **
**                     E_NOT_OK : If no wake up reason is available or if     **
**                                the service request failed due to           **
**                                development errors.                         **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType CanTrcv_17_V9251_GetBusWuReason
(
  const uint8 Transceiver, CanTrcv_TrcvWakeupReasonType* const reason
);

#if (CANTRCV_17_V9251_GET_VERSION_INFO == STD_ON)
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
**                                                                            **
**                                                                            **
** Syntax           : void CanTrcv_17_V9251_GetVersionInfo                    **
**                             (Std_VersionInfoType* const VersionInfoPtr)    **
**                                                                            **
**                                                                            **
** Description      : This API returns the version information of this module.**
**                    Note: This API is available only when                   **
**                    CanTrVersionInfoApi is configured as true.              **
** [/cover]                                                                   **
**                                                                            **
** Service ID       :  0x04                                                   **
**                                                                            **
** Sync/Async       :  Synchronous                                            **
**                                                                            **
** Reentrancy       :  reentrant                                              **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : versioninfo - Pointer to where to store the version     **
**                                  information of this module                **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void CanTrcv_17_V9251_GetVersionInfo
(
  Std_VersionInfoType* const versioninfo
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define CanTrcv_17_V9251_GetVersionInfo(versioninfo)                          \
                    (ERROR_CanTrcv_17_V9251_GetVersionInfo_API_IS_NOT_SELECTED)
#endif/*#if (CANTRCV_17_V9251_GET_VERSION_INFO == STD_ON) */

/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
**                                                                            **
**                                                                            **
** Syntax           : Std_ReturnType CanTrcv_17_V9251_SetWakeupMode           **
**                    (const uint8 Transceiver, const                         **
**                               CanTrcv_TrcvWakeupModeType TrcvWakeupMode)   **
**                                                                            **
** Description      : This API enables/disables/clears the wake-up events     **
**                    of the CAN transceiver according to parameter           **
**                    TrcvWakeupMode.                                         **
** [/cover]                                                                   **
**                                                                            **
** Service ID       :  0x05                                                   **
**                                                                            **
** Sync/Async       :  Synchronous                                            **
**                                                                            **
** Reentrancy       :  Reentrant for different transceivers                   **
**                                                                            **
** Parameters (in)  : Transceiver - CAN transceiver to which API call has     **
**                                   to be applied.                           **
**                    TrcvWakeupMode - Requested CAN transceiver wakeup mode. **
**                                                                            **
** Parameters (out) :  none                                                   **
**                                                                            **
** Return value     :  E_OK: Wakeup state changed to the requested mode.      **
**                     E_NOT_OK : Wakeup state change has failed or the       **
**                                parameter is out of the allowed range.      **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType CanTrcv_17_V9251_SetWakeupMode
(
  const uint8 Transceiver, const CanTrcv_TrcvWakeupModeType TrcvWakeupMode
);

/*******************************************************************************
** Traceability    :                                                          **
**                                                                            **
**                                                                            **
**                                                                            **
** Syntax          : Std_ReturnType CanTrcv_17_V9251_CheckWakeup              **
**                                                (const uint8 Transceiver)   **
** [/cover]                                                                   **
** Description     : This API service is called by underlying CANIF module    **
**                   in case a wake up interrupt is detected.                 **
**                   This API validates the wake up by checking the           **
**                   current mode of CAN Transceiver and                      **
**                   CanTrcvWakeupByBusUsed configuration parameter.          **
**                                                                            **
**                                                                            **
** Service ID      : 0x07                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : non reentrant                                            **
**                                                                            **
** Parameters (in) : Transceiver - Transceiver to which the API               **
**                               call has to be applied.                      **
** Parameters (out):                                                          **
**                                                                            **
** Return value    : E_OK :when a valid interrupt is detected                 **
**                   E_NOT_OK : when a no interrupt is detected or            **
**                                             due to DET error               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType CanTrcv_17_V9251_CheckWakeup(const uint8 Transceiver);

#define CANTRCV_17_V9251_STOP_SEC_CODE_QM_LOCAL
/* [cover parentID={DC0F3BD1-1815-492a-8B3D-D19A2DBC37C6}]
    MemMap file  [/cover] */
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
    MemMap file  [/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
    MemMap file  [/cover] */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_V9251_MemMap.h"

#endif /* CANTRCV_17_V9251_H */

/*******************************************************************************
**                               End of File                                  **
*******************************************************************************/
