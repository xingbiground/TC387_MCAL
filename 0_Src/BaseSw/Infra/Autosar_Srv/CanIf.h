/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2021)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME   : CanIf.h                                                     **
**                                                                           **
**  VERSION    : 7.0.0                                                       **
**                                                                           **
**  DATE       : 2021-11-08                                                  **
**                                                                           **
**  VARIANT    : NA                                                          **
**                                                                           **
**  PLATFORM   : Infineon AURIX2G                                            **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION  : This header file exports                                  **
**                    -  CAN interface function declaration                  **
**                 Note: This file is for Evaluation Purpose Only            **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: yes                                     **
**                                                                           **
******************************************************************************/

#ifndef CANIF_H
#define CANIF_H

/******************************************************************************
**                      Includes                                             **
******************************************************************************/
#include "CanIf_Types.h"
#include "Mcal_Version.h"
#include "EcuM.h"
/******************************************************************************
**                      Global Macro Definitions                             **
******************************************************************************/

/******************************************************************************
**                      Global Type Definitions                              **
******************************************************************************/

#define CANIF_AR_RELEASE_MAJOR_VERSION     (4U)
#define CANIF_AR_RELEASE_MINOR_VERSION     (2U)
#define CANIF_AR_RELEASE_REVISION_VERSION  (2U)
#define TEST_CANTRCV_MODULE_ID             (70U)  /* 0x46 */

#define CANIF_TRCV_WU_ERROR            ((CanIf_TrcvWakeupReasonType)(0))
#define CANIF_TRCV_WU_NOT_SUPPORTED    ((CanIf_TrcvWakeupReasonType)(1))
#define CANIF_TRCV_WU_BY_BUS           ((CanIf_TrcvWakeupReasonType)(2))
#define CANIF_TRCV_WU_INTERNALLY       ((CanIf_TrcvWakeupReasonType)(3))
#define CANIF_TRCV_WU_RESET            ((CanIf_TrcvWakeupReasonType)(4))
#define CANIF_TRCV_WU_POWER_ON         ((CanIf_TrcvWakeupReasonType)(5))
#define CANIF_TRCV_WU_BY_PIN           ((CanIf_TrcvWakeupReasonType)(6))
#define CANIF_TRCV_WU_BY_SYSERR        ((CanIf_TrcvWakeupReasonType)(7))
/* CanTrcv Modes */
#define CANIF_TRCV_MODE_NORMAL         ((CanIf_TransceiverModeType)(0))
#define CANIF_TRCV_MODE_STANDBY        ((CanIf_TransceiverModeType)(1))
#define CANIF_TRCV_MODE_SLEEP          ((CanIf_TransceiverModeType)(2))

#define CANIF_TRCV_WU_ENABLE           ((CanIf_TrcvWakeupModeType)(0))
#define CANIF_TRCV_WU_DISABLE          ((CanIf_TrcvWakeupModeType)(1))
#define CANIF_TRCV_WU_CLEAR            ((CanIf_TrcvWakeupModeType)(2))

#define CANIF_CONTROLLER_WAKEUP        ((CanIf_WakeupSourceType)(0))
#define CANIF_TRANSCEIVER_WAKEUP       ((CanIf_WakeupSourceType)(0))

#if (MCAL_AR_VERSION == MCAL_AR_422)
#define CANIF_CS_SLEEP    ((CanIf_ControllerModeType)0)
#define CANIF_CS_STARTED  ((CanIf_ControllerModeType)1)
#define CANIF_CS_STOPPED  ((CanIf_ControllerModeType)2)
#define CANIF_CS_UNINIT   ((CanIf_ControllerModeType)3)
#endif


/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/******************************************************************************
**                      Global Variable Declarations                         **
******************************************************************************/

/******************************************************************************
**                      Global Function Declarations                         **
******************************************************************************/

extern Std_ReturnType CanIf_CheckWakeup(EcuM_WakeupSourceType WakeupSource);

extern void CanIf_SetWakeupEvent(uint8 CanNetwork,
                                 CanIf_WakeupSourceType WakeupSource );

#if (MCAL_AR_VERSION == MCAL_AR_422)
/* Declaration of CanIf_ConfirmPnAvailability */
extern void CanIf_ConfirmPnAvailability(uint8 TransceiverId );

/* Declaration of CanIf_CheckTrcvWakeFlagIndication */
extern void CanIf_CheckTrcvWakeFlagIndication(uint8 TransceiverId);

/* Declaration of CanIf_TrcvModeIndication */
extern void CanIf_TrcvModeIndication(uint8 TransceiverId, CanTrcv_TrcvModeType TransceiverMode);

/* Declaration of CanIf_ClearTrcvWufFlagIndication */
extern void CanIf_ClearTrcvWufFlagIndication(uint8 TransceiverId);
#else

/* Declaration of CanIf_TriggerTransmit */
extern Std_ReturnType CanIf_TriggerTransmit(PduIdType TxPduId, PduInfoType* PduInfoPtr);

#endif

#ifdef  APP_SW
#if ( (APP_SW == TEST_APP) && (BASE_TEST_MODULE_ID == TEST_CANTRCV_MODULE_ID))
extern void CanIf_TestTrcvModeIndication(uint8 TransceiverId, CanTrcv_TrcvModeType TransceiverMode);
#endif
#endif
/******************************************************************************
**                      Global Inline Function Definitions                   **
******************************************************************************/

#endif
/*END OF  CANIF_H */

