/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2021)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : Dsadc_Cbk.h                                                **
**                                                                            **
**  VERSION      : 9.0.0                                                      **
**                                                                            **
**  DATE         : 2021-02-26                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY : [cover parentID={98B4E0C1-4AFC-4d33-89D6-6BBD4A50844B}]    **
**                                                                            **
**  DESCRIPTION  : Dsadc Driver Callback header definition file               **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of DSADC Driver                          **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

#ifndef DSADC_CBK_H
#define DSADC_CBK_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Dsadc Module header file */
#include "Dsadc.h"

/*******************************************************************************
**                      Callback Function Declarations                        **
*******************************************************************************/

#define DSADC_START_SEC_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
  without safegaurd. It complies to Autosar guidelines. */
#include "Dsadc_MemMap.h"

#if((DSADC_GTMTRIGGER_USED == STD_ON) || (DSADC_ERUTRIGGER_USED == STD_ON))
/*******************************************************************************
** Traceability     : [cover parentID]                                        **
**                                                                            **
** Syntax           : void Dsadc_TimerIsr                                     **
**                    (                                                       **
**                      const Dsadc_ChannelMaskType ChannelId,                **
**                      const uint32 StatusFlag                               **
**                    )                                                       **
**                                                                            **
** Description      : Callback function from MCU to Service the Timer         **
**                    interrupts. Both GTM and ERU interrupts are serviced in **
**                    this callback function.                                 **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x2B                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant for same channel, reentrant  for other    **
**                    channels                                                **
**                                                                            **
** Parameters(in)   : ChannelId - DSADC channel ID                            **
**                    StatusFlag - Source for this Callback                   **
**                    For GTM -> (CCU0 or CCU1 from GTM TOM or ATOM)          **
**                    For ERU -> Pattern Match(1) or Pattern Miss(0)          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : void                                                    **
*******************************************************************************/
extern void Dsadc_TimerIsr(const Dsadc_ChannelMaskType ChannelId, \
                                                  const uint32 StatusFlag);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an function is called but the related functionality 
  is disabled */
#define Dsadc_TimerIsr(ChannelId, StatusFlag) \
                                     (ERROR_Dsadc_TimerIsr_API_IS_NOT_SELECTED)
#endif

#define DSADC_STOP_SEC_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
  without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
  guideline.*/
#include "Dsadc_MemMap.h"

#endif /* DSADC_CBK_H */
