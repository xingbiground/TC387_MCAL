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
**  FILENAME    : Sent_Demo.h                                                **
**                                                                           **
**  VERSION     : 1.0.0                                                      **
**                                                                           **
**  DATE        : 2019-08-06                                                 **
**                                                                           **
**  VARIANT     : NA                                                         **
**                                                                           **
**  PLATFORM    : Infineon AURIX2G                                           **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION : This file exports                                          **
**                - Demo application for SENT driver                         **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                     **
**                                                                           **
******************************************************************************/

#ifndef SENT_DEMO_H
#define SENT_DEMO_H

/******************************************************************************
**                      Includes                                             **
******************************************************************************/
#include "Sent.h"

/******************************************************************************
**                      Global Macro Definitions                             **
******************************************************************************/

/******************************************************************************
**                      Global Type Definitions                              **
******************************************************************************/

/******************************************************************************
**                      Global Constant Declarations                         **
******************************************************************************/

/******************************************************************************
**                      Global Variable Declarations                         **
******************************************************************************/

/******************************************************************************
**                      Global Function Declarations                         **
******************************************************************************/
// extern void Sent_StartDemo(void);
extern void Sent_Demo(void);
extern void Sent_DemoAppCbk (Sent_ChannelIdxType ChannelId, uint32 Stat);
extern void Sent_Callout_Chan0 (Sent_ChannelIdxType ChannelId, Sent_NotifType Stat);
extern void Sent_Callout_Chan1 (Sent_ChannelIdxType ChannelId, Sent_NotifType Stat);
#endif
