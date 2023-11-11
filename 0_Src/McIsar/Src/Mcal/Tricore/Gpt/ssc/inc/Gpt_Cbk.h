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
**  FILENAME     : Gpt_Cbk.h                                                  **
**                                                                            **
**  VERSION      : 9.0.0                                                      **
**                                                                            **
**  DATE         : 2020-10-13                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY : [cover parentID={E2CD7B9C-9F84-4ba4-878C-4EAB20DCA9B5}]    **
**                                                                            **
**  DESCRIPTION  : GPT Driver Callback header definition file                 **
**                                                                            **
**  SPECIFICATION(S) : Specification of GPT Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/* [cover parentID={F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}][/cover] */

#ifndef  GPT_CBK_H
#define  GPT_CBK_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* GPT Module header file */
#include "Gpt.h"

/* [cover parentID={E2CD7B9C-9F84-4ba4-878C-4EAB20DCA9B5}]
[/cover] */
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
#define GPT_START_SEC_CODE_FAST_ASIL_B_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"

/*******************************************************************************
** Traceability   : [cover parentID=]                                         **
**                                                                            **
** Syntax         : void Gpt_Isr(const uint32 LogicalChId)                    **
**                                                                            **
** Description    : Interrupt service routine called on any timer event.      **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : LogicalChId - GPT Channel Number                          **
**                  StatusFlags - Source of ISR is CM0 or CM1                 **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
extern void Gpt_Isr(const uint32 LogicalChId, const uint32 StatusFlags);

/******************************************************************************/

#define GPT_STOP_SEC_CODE_FAST_ASIL_B_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"

/*******************************************************************************
**                      Global In-line Function Definitions                   **
*******************************************************************************/

#endif /* GPT_CBK_H */
