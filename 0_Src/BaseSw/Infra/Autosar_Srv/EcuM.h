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
**  FILENAME     : EcuM.h                                                     **
**                                                                            **
**  VERSION      : 3.0.0                                                      **
**                                                                            **
**  DATE         : 2020-09-28                                                 **
**                                                                            **
**  VARIANT      : NA                                                         **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : This file provides ECUM types                              **
**                 This file is for Evaluation Purpose Only                   **
**                                                                            **
**  SPECIFICATION(S) : Specification of ECUM Driver, AUTOSAR Release 4.2.2    **
**                     and AUTOSAR Release 4.4.0                              **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/

#ifndef ECUM_H
#define ECUM_H
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Std_Types.h"
#include "Platform_Types.h"
#include "Mcal_Version.h"
#if (MCAL_AR_VERSION == MCAL_AR_422)
#include "EcuM_Types.h"
#endif
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
#if (MCAL_AR_VERSION == MCAL_AR_440)
/* Used in Gpt, Icu, Lin, CanTrnc Modules */
typedef uint32 EcuM_WakeupSourceType;
#endif
/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
extern void EcuM_SetWakeupEvent
(
  EcuM_WakeupSourceType events
);

#endif   /* #ifndef ECUM_H  */
