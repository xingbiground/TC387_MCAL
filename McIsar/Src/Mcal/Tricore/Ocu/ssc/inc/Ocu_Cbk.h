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
**  FILENAME     : Ocu_Cbk.h                                                  **
**                                                                            **
**  VERSION      : 7.0.0                                                      **
**                                                                            **
**  DATE         : 2020-07-15                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Ocu Driver Callback header definition file                 **
**                                                                            **
**  SPECIFICATION(S) :Specification of OCU Driver,AUTOSAR Release 4.2.2&4.4.0 **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/* [cover parentID={F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}][/cover] */
/* [cover parentID={D51722F3-5304-420a-828C-83B6D725D9C0}] */
/*  [/cover] */
#ifndef OCU_CBK_H
#define OCU_CBK_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Ocu Module header file */
#include "Ocu.h"

/******************************************************************************
**                      Callback Function Declarations                        **
******************************************************************************/
#define OCU_START_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Ocu_MemMap.h"
/*******************************************************************************
**                                                                            **
** Syntax : void Ocu_Timer_Isr  (const uint32 Channel)                        **
**                                                                            **
** Description : Callback from MCU to service Timer interrupts                **
**                                                                            **
** Service ID:  none                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant for different channels                              **
**                                                                            **
** Parameters (in): Channel - logical channel number                          **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
*******************************************************************************/
extern void Ocu_Timer_Isr (const uint32 Channel, uint32 flags);

#define OCU_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Ocu_MemMap.h"

#endif /* OCU_CBK_H */
