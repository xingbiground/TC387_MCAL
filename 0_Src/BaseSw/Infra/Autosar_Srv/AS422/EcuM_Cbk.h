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
**  FILENAME     : EcuM_Cbk.h                                                 **
**                                                                            **
**  VERSION      : 2.0.0                                                      **
**                                                                            **
**  DATE         : 2020-08-05                                                 **
**                                                                            **
**  VARIANT      : NA                                                         **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : This file provides ECUM callback/callout declarations      **
**                 This file is for Evaluation Purpose Only                   **
**                                                                            **
**  SPECIFICATION(S) : Specification of ECUM Driver, AUTOSAR Release 4.2.2    **
**                     and AUTOSAR Release 4.4.0                              **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/

#ifndef ECUMCBK_H
#define ECUMCBK_H
#include "EcuM_Types.h"
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Type Definitions                               **
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

/* Wake Up Related APIs. Used in Gpt,Icu, Can Drivers */

extern void EcuM_SetWakeupEvent
(
  EcuM_WakeupSourceType events
);

extern void EcuM_ValidateWakeupEvent
(
  EcuM_WakeupSourceType events
);

extern void EcuM_CheckWakeup
(
  EcuM_WakeupSourceType wakeupSource
);
#endif   /* #ifndef ECUMCBK_H  */
