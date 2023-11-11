/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2018)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : Stm_Cbk.h                                                  **
**                                                                            **
**  VERSION      : 2.0.0                                                      **
**                                                                            **
**  DATE         : 2018-09-18                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Stm Driver Callback header definition file                 **
**                                                                            **
**  SPECIFICATION(S) : Specification of Stm Driver                            **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

#ifndef  STM_CBK_H
#define  STM_CBK_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Stm Module header file */
#include "Stm.h"

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
**                      Callback Function Declarations                        **
*******************************************************************************/
#define STM_START_SEC_CODE_FAST_QM_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Stm_MemMap.h"

/*******************************************************************************
** Traceability   : [cover parentID=]                                         **
**                                                                            **
** Syntax         : void Stm_Isr(const Stm_ChannelType LogicalChId)           **
**                                                                            **
** Description    : Interrupt service routine called on any timer event.      **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : NA                                                        **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : LogicalChId - Stm Channel Number                          **
**                  StatusFlags - Source of ISR is CM0 or CM1                 **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
extern void Stm_Isr(const uint8 ModuleNumber, const uint32 InterruptNode);

/******************************************************************************/

#define STM_STOP_SEC_CODE_FAST_QM_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Stm_MemMap.h"

/*******************************************************************************
**                      Global In-line Function Definitions                   **
*******************************************************************************/

#endif /* STM_CBK_H */
