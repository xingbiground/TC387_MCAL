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
**  FILENAME     : Icu_17_TimerIp_Cbk.h                                       **
**                                                                            **
**  VERSION      : 5.0.0                                                      **
**                                                                            **
**  DATE         : 2020-03-09                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Icu Driver Callback header definition file                 **
**                                                                            **
**  SPECIFICATION(S) : Specification of Icu Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/* [cover parentID={49DDF4FA-CB7A-4837-B5C6-93980EC67B21}] */
/*  [/cover] */
#ifndef ICU_17_TIMERIP_CBK_H
#define ICU_17_TIMERIP_CBK_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Icu Module header file */
#include "Icu_17_TimerIp.h"

/******************************************************************************
**                      Callback Function Declarations                        **
******************************************************************************/
#define ICU_17_TIMERIP_START_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"
/*******************************************************************************
**                                                                            **
** Syntax : void Icu_17_TimerIp_Timer_Isr                                     **
** (const uint32 Channel ,const uint32 StatusFlags)                           **
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
**                  StatusFlags - interrupt rising or falling info            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
*******************************************************************************/
/* [cover parentID={E363508D-565D-419f-98F2-D783050350BD}] */
/* Interrupt source check  - done by MCU which calls the ISR */
/*  [/cover] */
extern void Icu_17_TimerIp_Timer_Isr(const uint32 Channel, \
                                     const uint32 StatusFlags);

#define ICU_17_TIMERIP_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Icu_17_TimerIp_MemMap.h"

#endif /* ICU_17_TIMERIP_CBK_H */
