/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2019)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : Gpt_Demo.h                                                 **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2019-04-11                                                 **
**                                                                            **
**  VARIANT      : NA                                                         **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Demo application header file for GPT module                **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
#ifndef  GPT_DEMO_H
#define  GPT_DEMO_H

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
#define GPT_START_SEC_CODE_ASIL_B_GLOBAL
#include "Gpt_MemMap.h"

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : void Gpt_Demo(void)                                       **
**                                                                            **
** Description    : In this routine user options handling is done             **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : none                                                      **
**                                                                            **
** Parameters(out): none                                                      **
**                                                                            **
** Return value   : none                                                      **
**                                                                            **
*******************************************************************************/
extern void Gpt_Demo(void);
#if ( MCAL_NO_OF_CORES > 1U )
extern void Gpt_Demo_Multi(void);
#endif

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : void Gpt_Notification(void)                               **
**                                                                            **
** Description    : GPT channel notification functionality, turns ON/OFF LED  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : none                                                      **
**                                                                            **
** Parameters(out): none                                                      **
**                                                                            **
** Return value   : none                                                      **
**                                                                            **
*******************************************************************************/
// extern void IoHwAb_GptNotification0(void);

#define GPT_STOP_SEC_CODE_ASIL_B_GLOBAL
#include "Gpt_MemMap.h"

/*******************************************************************************
**                      Global In-line Function Definitions                   **
*******************************************************************************/
#endif /* GPT_DEMO_H */

