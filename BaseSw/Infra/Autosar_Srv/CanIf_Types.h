/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2016)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  $FILENAME   : CanIf_Types.h $                                            **
**                                                                           **
**  $CC VERSION : \main\1 $                                                  **
**                                                                           **
**  $DATE       : 2020-06-26 $                                               **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION : This file contains general types of CAN.                   **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: yes                                     **
**                                                                           **
******************************************************************************/

#ifndef CANIF_TYPES_H
#define CANIF_TYPES_H

/******************************************************************************
**                      Includes                                             **
******************************************************************************/
#include "ComStack_Types.h"
#include "Can_GeneralTypes.h"

/******************************************************************************
**                      Global Macro Definitions                             **
******************************************************************************/

/******************************************************************************
**                      Global Type Definitions                              **
******************************************************************************/

/* definition of CanIf_TrcvWakeupReasonType */
typedef uint8 CanIf_TrcvWakeupReasonType;

/* definition of CanIf_TransceiverModeType */
typedef uint8 CanIf_TransceiverModeType;

/* definition of CanIf_TrcvWakeupModeType */
typedef uint8 CanIf_TrcvWakeupModeType;

/* definition of CanIf_WakeupSourceType */
typedef uint8 CanIf_WakeupSourceType;

#if (MCAL_AR_VERSION == MCAL_AR_422)
typedef uint8 CanIf_ControllerModeType;
#endif
/******************************************************************************
**                      Global Constant Declarations                         **
******************************************************************************/
/******************************************************************************
**                      Global Variable Declarations                         **
******************************************************************************/

/******************************************************************************
**                      Global Function Declarations                         **
******************************************************************************/

/******************************************************************************
**                      Global Inline Function Definitions                   **
******************************************************************************/
#endif /* #ifndef CANIF_TYPES_H */

