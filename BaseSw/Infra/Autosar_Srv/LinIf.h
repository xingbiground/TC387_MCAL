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
**  FILENAME   : LinIf.h                                                      **
**                                                                            **
**  VERSION    : 4.0.0                                                        **
**                                                                            **
**  DATE       : 2020-11-13                                                   **
**                                                                            **
**  VARIANT    : NA                                                           **
**                                                                            **
**  PLATFORM   : Infineon AURIX2G                                             **
**                                                                            **
**  AUTHOR      : DL-AUTOSAR-Engineering                                      **
**                                                                            **
**  VENDOR      : Infineon Technologies                                       **
**                                                                            **
**  DESCRIPTION  : This header file exports                                   **
**                    -  LIN interface function declaration                   **
**                 Note: This file is for Evaluation Purpose Only             **
**                                                                            **
**  MAY BE CHANGED BY USER [yes/no]: yes                                      **
**                                                                            **
*******************************************************************************/

#ifndef LINIF_H
#define LINIF_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Mcal_Version.h"
#if (MCAL_AR_VERSION == MCAL_AR_422)
#include "EcuM_Cbk.h"
#else
#include "EcuM.h"
#endif
#include "Lin_17_AscLin.h"

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
extern void LinIf_CheckWakeup
( 
   EcuM_WakeupSourceType WakeupSource
);

#if (MCAL_AR_VERSION == MCAL_AR_440)
extern void LinIf_WakeupConfirmation
(
   EcuM_WakeupSourceType WakeupSource
);

extern Std_ReturnType LinIf_HeaderIndication
(
   NetworkHandleType Channel,
   Lin_PduType* PduPtr
);

extern void LinIf_TxConfirmation
(
   NetworkHandleType Channel
);

extern void LinIf_LinErrorIndication
(
  NetworkHandleType Channel,
  Lin_SlaveErrorType ErrorStatus
);

extern void LinIf_RxIndication
(
  NetworkHandleType Channel,
  uint8* Lin_SduPtr
);
#endif
/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/

#endif /* END OF  LINIF_H */

