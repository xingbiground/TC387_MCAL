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
**  FILENAME   : Can_17_McmCan_Demo.h                                        **
**                                                                           **
**  VERSION    : 2.0.0                                                       **
**                                                                           **
**  DATE       : 2021-02-24                                                  **
**                                                                           **
**  VARIANT    : NA                                                          **
**                                                                           **
**  PLATFORM   : Infineon AURIX2G                                            **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION : This file exports                                          **
**                - Demo application for CAN driver                          **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: yes                                     **
**                                                                           **
******************************************************************************/


/******************************************************************************
**                      Includes                                             **
******************************************************************************/

/******************************************************************************
** Syntax : void Can_17_McmCan_Demo(void)                                    **
**                                                                           **
** Service ID:   : NA                                                        **
**                                                                           **
** Sync/Async:   : Synchronous                                               **
**                                                                           **
** Reentrancy:   : Non Reentrant                                             **
**                                                                           **
** Parameters (in): none                                                     **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value: none                                                        **
**                                                                           **
** Description : DemoApp for CAN driver                                      **
**                                                                           **
******************************************************************************/
#define CAN_17_MCMCAN_START_SEC_CODE_QM_GLOBAL
#include "Can_17_McmCan_MemMap.h"

extern void Can_17_McmCan_Demo(void);

#define CAN_17_MCMCAN_STOP_SEC_CODE_QM_GLOBAL
#include "Can_17_McmCan_MemMap.h"
