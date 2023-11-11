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
**  FILENAME     : SchM_Gpt.c                                                 **
**                                                                            **
**  VERSION      : 3.0.0                                                      **
**                                                                            **
**  DATE         : 2019-05-31                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY : [cover parentID=]                                          **
**                                                                            **
**  DESCRIPTION  : SchM file for Gpt driver                                   **
**                                                                            **
**  [/cover]                                                                  **
**  SPECIFICATION(S) : Specification of RTE, AUTOSAR Release 4.2.2            **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "IFX_Os.h"
#include "SchM_Gpt.h"

#ifdef LATENCY_CALC_GPT
#if(LATENCY_CALC_GPT==1U)
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
** Syntax           : void SchM_Enter_Gpt_Get1UsPredefTimerValue(void)        **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Enters Module exclusive area                            **
**                                                                            **
*******************************************************************************/
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
void SchM_Enter_Gpt_Get1UsPredefTimerValue(void)
{
  SuspendAllInterrupts();
  #ifdef LATENCY_CALC_GPT
  #if(LATENCY_CALC_GPT==1U)
  Measure_Start_Value(0);
  #endif
  #endif
}

/*******************************************************************************
** Syntax           : void SchM_Exit_Gpt_Get1UsPredefTimerValue(void)         **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Exits Module exclusive area                             **
**                                                                            **
*******************************************************************************/
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
void SchM_Exit_Gpt_Get1UsPredefTimerValue(void)
{
  #ifdef LATENCY_CALC_GPT
  #if(LATENCY_CALC_GPT==1U)
  Measure_End_Value(0);
  #endif
  #endif
  ResumeAllInterrupts();
}

/*******************************************************************************
** Syntax           : void SchM_Enter_Gpt_Get100UsPredefTimerValue(void)      **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Enters Module exclusive area                            **
**                                                                            **
*******************************************************************************/
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
void SchM_Enter_Gpt_Get100UsPredefTimerValue(void)
{
  SuspendAllInterrupts();
  #ifdef LATENCY_CALC_GPT
  #if(LATENCY_CALC_GPT==1U)
  Measure_Start_Value(1);
  #endif
  #endif
}

/*******************************************************************************
** Syntax           : void SchM_Exit_Gpt_Get100UsPredefTimerValue(void)       **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Exits Module exclusive area                             **
**                                                                            **
*******************************************************************************/
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
void SchM_Exit_Gpt_Get100UsPredefTimerValue(void)
{
  #ifdef LATENCY_CALC_GPT
  #if(LATENCY_CALC_GPT==1U)
  Measure_End_Value(1);
  #endif
  #endif
  ResumeAllInterrupts();
}

/*******************************************************************************
** Syntax           : void SchM_Enter_Gpt_GtmStartTimer(void)                 **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Enters Module exclusive area                            **
**                                                                            **
*******************************************************************************/
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
void SchM_Enter_Gpt_GtmStartTimer(void)
{
  SuspendAllInterrupts();
  #ifdef LATENCY_CALC_GPT
  #if(LATENCY_CALC_GPT==1U)
  Measure_Start_Value(1);
  #endif
  #endif
}

/*******************************************************************************
** Syntax           : void SchM_Exit_Gpt_GtmStartTimer(void)                  **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Exits Module exclusive area                             **
**                                                                            **
*******************************************************************************/
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
void SchM_Exit_Gpt_GtmStartTimer(void)
{
  #ifdef LATENCY_CALC_GPT
  #if(LATENCY_CALC_GPT==1U)
  Measure_End_Value(1);
  #endif
  #endif
  ResumeAllInterrupts();
}

/*******************************************************************************
** Syntax           : void SchM_Enter_Gpt_Gpt12StartTimer(void)               **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Enters Module exclusive area                            **
**                                                                            **
*******************************************************************************/
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
void SchM_Enter_Gpt_Gpt12StartTimer(void)
{
  SuspendAllInterrupts();
  #ifdef LATENCY_CALC_GPT
  #if(LATENCY_CALC_GPT==1U)
  Measure_Start_Value(1);
  #endif
  #endif
}

/*******************************************************************************
** Syntax           : void SchM_Exit_Gpt_Gpt12StartTimer(void)                  **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Exits Module exclusive area                             **
**                                                                            **
*******************************************************************************/
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
void SchM_Exit_Gpt_Gpt12StartTimer(void)
{
  #ifdef LATENCY_CALC_GPT
  #if(LATENCY_CALC_GPT==1U)
  Measure_End_Value(1);
  #endif
  #endif
  ResumeAllInterrupts();
}
