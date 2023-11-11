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
**  FILENAME  : FlsLdr_ExclArea.c                                             **
**                                                                            **
**  VERSION   : 1.0.0                                                         **
**                                                                            **
**  DATE      : 2020-06-26                                                    **
**                                                                            **
**  VARIANT   : Post-Build                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION : File containing the prototype defination of the APIs        **
**                which handles the exclusive area of FlsLoader module        **
**                                                                            **
**  SPECIFICATION(S) : Specification of FlsLoader Driver, AUTOSAR             **
**                     Release 4.2.2, 4.4.0                                   **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
#include "IFX_Os.h"
#include "FlsLdr_ExclArea.h"

#ifdef LATENCY_CALC_FLSLDR
#if(LATENCY_CALC_FLSLDR==1U)
#include "Test_Latency.h"
#endif
#endif

/*******************************************************************************
**                                                                            **
** Syntax           : void FlsLdr_ExclArea_PfProg_Enter(void)                 **
**                                                                            **
** Description      : This API call is invoked by FlsLoader module to define  **
**                    the start of an exclusive area while performing PFlash  **
**                    program operation.                                      **
**                                                                            **
** Service ID       :                                                         **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : void                                                    **
**                                                                            **
*******************************************************************************/
void FlsLdr_ExclArea_PfProg_Enter(void)
{
  SuspendAllInterrupts();
  #ifdef LATENCY_CALC_FLSLDR
  #if(LATENCY_CALC_FLSLDR==1U)
  Measure_Start_Value(0);
  #endif
  #endif
}

/*******************************************************************************
**                                                                            **
** Syntax           : void FlsLdr_ExclArea_PfProg_Exit(void)                  **
**                                                                            **
** Description      : This API call is invoked by FlsLoader module to define  **
**                    the end of an exclusive area while performing PFlash    **
**                    program operation.                                      **
**                                                                            **
** Service ID       :                                                         **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : void                                                    **
**                                                                            **
*******************************************************************************/
void FlsLdr_ExclArea_PfProg_Exit(void)
{
  ResumeAllInterrupts();
  #ifdef LATENCY_CALC_FLSLDR
  #if(LATENCY_CALC_FLSLDR==1U)
  Measure_End_Value(0);
  #endif
  #endif
}

/*******************************************************************************
**                                                                            **
** Syntax           : void FlsLdr_ExclArea_PfErase_Enter(void)                **
**                                                                            **
** Description      : This API call is invoked by FlsLoader module to define  **
**                    the start of an exclusive area while performing PFlash  **
**                    erase operation.                                        **
**                                                                            **
** Service ID       :                                                         **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : void                                                    **
**                                                                            **
*******************************************************************************/
void FlsLdr_ExclArea_PfErase_Enter(void)
{
  SuspendAllInterrupts();
  #ifdef LATENCY_CALC_FLSLDR
  #if(LATENCY_CALC_FLSLDR==1U)
  Measure_Start_Value(1);
  #endif
  #endif
}

/*******************************************************************************
**                                                                            **
** Syntax           : void FlsLdr_ExclArea_PfErase_Exit(void)                 **
**                                                                            **
** Description      : This API call is invoked by FlsLoader module to define  **
**                    the end of an exclusive area while performing PFlash    **
**                    erase operation.                                        **
**                                                                            **
** Service ID       :                                                         **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : void                                                    **
**                                                                            **
*******************************************************************************/
void FlsLdr_ExclArea_PfErase_Exit(void)
{
  ResumeAllInterrupts();
  #ifdef LATENCY_CALC_FLSLDR
  #if(LATENCY_CALC_FLSLDR==1U)
  Measure_End_Value(1);
  #endif
  #endif
}

