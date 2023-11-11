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
**  FILENAME     : Wdg_17_Scu_Cbk.h                                           **
**                                                                            **
**  VERSION      : 7.0.0                                                      **
**                                                                            **
**  DATE         : 2020-03-31                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : This file contains call back function of WDG driver        **
**                                                                            **
**  SPECIFICATION(S) : Specification of Watchdog Driver, AUTOSAR Release      **
**                     4.2.2 and 4.4.0                                        **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/* [cover parentID={363B6CB7-B3D9-4b62-8375-ED4BD32D8379}][/cover] */
#ifndef WDG_17_SCU_CBK_H
#define WDG_17_SCU_CBK_H

/* Wdg Module Configuration header file */
#include "Std_Types.h"
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}][/cover] */
#define WDG_17_SCU_START_SEC_CODE_FAST_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
#include "Wdg_17_Scu_MemMap.h"

/*******************************************************************************
** Traceability     : [cover parentID={138600B4-44B8-48cb-8D86-9533DB237C27}] **
**                                                                            **
** Syntax           : void Wdg_17_Scu_Isr                                     **
**                   (const uint32 LogicalChId,const uint32 IsrStatus)        **
**                                                                            **
**                                                                            **
** Description      : Timer interrupt function for GTM/STM timer.             **
**                    This function is called if SRV timer is expired and     **
**                    triggers the Watchdog hardware timer if Timeout counter **
**                    value has not reached zero.                             **
**                    [/cover]                                                **
**                                                                            **
** Service ID       : 0x05                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : LogicalChId STM timer Id                                **
**                    IsrStatus indicates the interrupt source in case of GTM **
**                                                                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void Wdg_17_Scu_Isr(const uint32 LogicalChId, const uint32 IsrStatus);
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}][/cover] */
#define WDG_17_SCU_STOP_SEC_CODE_FAST_ASIL_B_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar guideline.*/
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
#include "Wdg_17_Scu_MemMap.h"

#endif /* WDG_17_SCU_CBK_H */
