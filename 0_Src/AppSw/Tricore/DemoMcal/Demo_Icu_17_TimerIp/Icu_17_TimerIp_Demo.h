/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2019)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME   : Icu_17_TimerIp_Demo.h                                       **
**                                                                           **
**  VERSION    : 1.0.0                                                       **
**                                                                           **
**  DATE       : 2019-04-11                                                  **
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
**                - Demo application for ICU driver                          **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: yes                                     **
**                                                                           **
******************************************************************************/

/******************************************************************************
**                      Includes                                             **
******************************************************************************/

#define ICU_17_TIMERIP_START_SEC_CODE_ASIL_B_GLOBAL
#include "Icu_17_TimerIp_MemMap.h"

extern void Icu_17_TimerIp_Demo_Init(void);
extern void Icu_17_TimerIp_Demo(void);

#define ICU_17_TIMERIP_STOP_SEC_CODE_ASIL_B_GLOBAL
#include "Icu_17_TimerIp_MemMap.h"
