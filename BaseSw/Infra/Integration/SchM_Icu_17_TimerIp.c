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
**  FILENAME     : SchM_Icu_17_TimerIp.c                                      **
**                                                                            **
**  VERSION      : 6.0.0                                                      **
**                                                                            **
**  DATE         : 2018-10-15                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY : [cover parentID= {1300DA60-D908-45a6-A899-6339BE0101C5} ]  **
**                                                                            **
**  DESCRIPTION  : SchM file for Icu driver                                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of RTE, AUTOSAR Release 4.2.2            **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "IFX_Os.h"
#include "SchM_Icu_17_TimerIp.h"
#ifdef LATENCY_CALC_ICU
#if(LATENCY_CALC_ICU==1U)
#include "Test_Latency.h"
#endif
#endif
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
**                      Global Function Definitions                           **
*******************************************************************************/
/*******************************************************************************
** Traceability: [cover parentID={DE5ADE20-82DC-43ac-9E00-F2D266B5F1D0}]      **
**                                                                            **
** Syntax           : void SchM_Enter_Icu_17_TimerIp_ResetEdgeCount(void)     **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : Enters Module exclusive area                            **
**                                                                            **
*******************************************************************************/
void SchM_Enter_Icu_17_TimerIp_ResetEdgeCount(void)
{
  SuspendAllInterrupts();
  #ifdef LATENCY_CALC_ICU
  #if(LATENCY_CALC_ICU==1U)
  Measure_Start_Value(0);
  #endif
  #endif
}

/*******************************************************************************
** Traceability: [cover parentID={DE5ADE20-82DC-43ac-9E00-F2D266B5F1D0}]      **
**                                                                            **
** Syntax           : void SchM_Exit_Icu_17_TimerIp_ResetEdgeCount(void)      **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : none                                                    **
** [/cover]                                                                   **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : Exits Module exclusive area                             **
**                                                                            **
*******************************************************************************/
void SchM_Exit_Icu_17_TimerIp_ResetEdgeCount(void)
{
  #ifdef LATENCY_CALC_ICU
  #if(LATENCY_CALC_ICU==1U)
  Measure_End_Value(0);
  #endif
  #endif
  ResumeAllInterrupts();
}

/*******************************************************************************
** Traceability: [cover parentID={FBE391B2-0DA7-4152-BC44-943FC4B4B56F}]      **
**                                                                            **
** Syntax        : void SchM_Enter_Icu_17_TimerIp_SetActivationCondition(void)**
** [/cover]                                                                   **
**                                                                            **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : Enters Module exclusive area                            **
**                                                                            **
*******************************************************************************/
void SchM_Enter_Icu_17_TimerIp_SetActivationCondition(void)
{
  SuspendAllInterrupts();
  #ifdef LATENCY_CALC_ICU
  #if(LATENCY_CALC_ICU==1U)
  Measure_Start_Value(1);
  #endif
  #endif
}

/*******************************************************************************
** Traceability: [cover parentID={FBE391B2-0DA7-4152-BC44-943FC4B4B56F}]      **
**                                                                            **
** Syntax         : void SchM_Exit_Icu_17_TimerIp_SetActivationCondition(void)**
** [/cover]                                                                   **
**                                                                            **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : Exits Module exclusive area                             **
**                                                                            **
*******************************************************************************/
void SchM_Exit_Icu_17_TimerIp_SetActivationCondition(void)
{
  #ifdef LATENCY_CALC_ICU
  #if(LATENCY_CALC_ICU==1U)
  Measure_End_Value(1);
  #endif
  #endif
  ResumeAllInterrupts();
}

/*******************************************************************************
** Traceability: [cover parentID={253EA602-550A-4df4-8993-AE8373F79989}]      **
**                                                                            **
** Syntax           : void SchM_Enter_Icu_17_TimerIp_GtmEnableEdgeCount(void) **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : Enters Module exclusive area                            **
**                                                                            **
*******************************************************************************/
void SchM_Enter_Icu_17_TimerIp_GtmEnableEdgeCount(void)
{
  SuspendAllInterrupts();
  #ifdef LATENCY_CALC_ICU
  #if(LATENCY_CALC_ICU==1U)
  Measure_Start_Value(2);
  #endif
  #endif
}

/*******************************************************************************
** Traceability: [cover parentID={253EA602-550A-4df4-8993-AE8373F79989}]      **
**                                                                            **
** Syntax           : void SchM_Exit_Icu_17_TimerIp_GtmEnableEdgeCount(void)  **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : Exits Module exclusive area                             **
**                                                                            **
*******************************************************************************/
void SchM_Exit_Icu_17_TimerIp_GtmEnableEdgeCount(void)
{
  #ifdef LATENCY_CALC_ICU
  #if(LATENCY_CALC_ICU==1U)
  Measure_End_Value(2);
  #endif
  #endif
  ResumeAllInterrupts();
}

/*******************************************************************************
** Traceability: [cover parentID={945653E4-2B39-42d1-A365-BF27A9A5AA12}]      **
**                                                                            **
** Syntax           : void SchM_Enter_Icu_17_TimerIp_GtmGetDutyCycle(void)    **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : Enters Module exclusive area                            **
**                                                                            **
*******************************************************************************/
void SchM_Enter_Icu_17_TimerIp_GtmGetDutyCycle(void)
{
  SuspendAllInterrupts();
  #ifdef LATENCY_CALC_ICU
  #if(LATENCY_CALC_ICU==1U)
  Measure_Start_Value(3);
  #endif
  #endif
}

/*******************************************************************************
** Traceability: [cover parentID={945653E4-2B39-42d1-A365-BF27A9A5AA12}]      **
**                                                                            **
** Syntax           : void SchM_Exit_Icu_17_TimerIp_GtmGetDutyCycle(void)     **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : Exits Module exclusive area                             **
**                                                                            **
*******************************************************************************/
void SchM_Exit_Icu_17_TimerIp_GtmGetDutyCycle(void)
{
  #ifdef LATENCY_CALC_ICU
  #if(LATENCY_CALC_ICU==1U)
  Measure_End_Value(3);
  #endif
  #endif
  ResumeAllInterrupts();
}
