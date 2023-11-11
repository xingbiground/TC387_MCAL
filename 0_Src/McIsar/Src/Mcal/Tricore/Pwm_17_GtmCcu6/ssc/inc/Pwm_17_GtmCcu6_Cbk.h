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
**  FILENAME     : Pwm_17_GtmCcu6_Cbk.h                                       **
**                                                                            **
**  VERSION      : 5.0.0                                                      **
**                                                                            **
**  DATE         : 2020-05-08                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Pwm Driver Callback header definition file                 **
**                                                                            **
**  SPECIFICATION(S) : AUTOSAR Specification of Pwm Driver                    **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

#ifndef  PWM_17_GTMCCU6_CBK_H
#define  PWM_17_GTMCCU6_CBK_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* PWM Module header file */
#include "Pwm_17_GtmCcu6.h"
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
#define PWM_17_GTMCCU6_START_SEC_CODE_FAST_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Pwm_17_GtmCcu6_MemMap.h"

/******************************************************************************
** Syntax :          void Pwm_17_GtmCcu6_Isr                                 **
**                   (                                                       **
**                     const uint32 ChannelNumber,                           **
**                     const uint32 IsrStatus                                **
**                   )                                                       **
** Service ID:       0x09                                                    **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       Depends on the implementation of Notification function  **
**                                                                           **
** Parameters (in):  ChannelNumber : PWM Channel number which caused the     **
**                                          interrupt                        **
**                   IsrStatus: Parameter gives the information about the    **
**                   comparator which caused the interrupt.                  **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : 1. This service will be used only in an interrupt           **
**               2. In this service depending on conditions Notification will**
**                   be provided                                             **
**                                                                           **
** Traceabilty      :                                                        **
******************************************************************************/
extern void Pwm_17_GtmCcu6_Isr
(
  const uint32 ChannelNumber,
  const uint32 IsrStatus
);
/******************************************************************************/

#define PWM_17_GTMCCU6_STOP_SEC_CODE_FAST_ASIL_B_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Pwm_17_GtmCcu6_MemMap.h"

/*******************************************************************************
**                      Global In-line Function Definitions                   **
*******************************************************************************/

#endif /* PWM_17_GTMCCU6_CBK_H */
