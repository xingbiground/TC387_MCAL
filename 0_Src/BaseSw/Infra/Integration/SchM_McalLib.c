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
**  FILENAME     : SchM_McalLib.c                                             **
**                                                                            **
**  VERSION      : 2.0.0                                                      **
**                                                                            **
**  DATE         : 2018-10-15                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : SchM file for McalLib                                      **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "IFX_Os.h"
#include "SchM_McalLib.h"
#ifdef LATENCY_CALC_MCALLIB
#if(LATENCY_CALC_MCALLIB==1U)
#include "Test_Latency.h"
#endif
#endif
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : void SchM_Enter_McalLib_PeripheralEndInit(void)         **
**                                                                            **
** Description      : Enters Module exclusive area                            **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Not Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void SchM_Enter_McalLib_PeripheralEndInit(void)
{
  SuspendAllInterrupts();
  #ifdef LATENCY_CALC_MCALLIB
  #if(LATENCY_CALC_MCALLIB==1U)
  Measure_Start_Value(0);
  #endif
  #endif
}
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : void SchM_Exit_McalLib_PeripheralEndInit(void)          **
**                                                                            **
** Description      : Exit Module exclusive area                              **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Not Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void SchM_Exit_McalLib_PeripheralEndInit(void)
{
  #ifdef LATENCY_CALC_MCALLIB
  #if(LATENCY_CALC_MCALLIB==1U)
  Measure_End_Value(0);
  #endif
  #endif
  ResumeAllInterrupts();
}
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : void SchM_Enter_McalLib_SafetyEndInit(void)             **
**                                                                            **
** Description      : Enters Module exclusive area                            **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Not Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void SchM_Enter_McalLib_SafetyEndInit(void)
{
  SuspendAllInterrupts();
  #ifdef LATENCY_CALC_MCALLIB
  #if(LATENCY_CALC_MCALLIB==1U)
  Measure_Start_Value(1);
  #endif
  #endif
}
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : void SchM_Exit_McalLib_SafetyEndInit(void)              **
**                                                                            **
** Description      : Exit Module exclusive area                              **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Not Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void SchM_Exit_McalLib_SafetyEndInit(void)
{
  #ifdef LATENCY_CALC_MCALLIB
  #if(LATENCY_CALC_MCALLIB==1U)
  Measure_End_Value(1);
  #endif
  #endif
  ResumeAllInterrupts();
}
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : void SchM_Enter_McalLib_CpuEndInit(void)                **
**                                                                            **
** Description      : Enters Module exclusive area                            **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Not Reentrant on same CPU, Reentrant on other CPUs      **
**                                                                            **
** Parameters(in)   : None                                                    **
** Parameters (out) : None                                                    **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void SchM_Enter_McalLib_CpuEndInit(void)
{
  SuspendAllInterrupts();
  #ifdef LATENCY_CALC_MCALLIB
  #if(LATENCY_CALC_MCALLIB==1U)
  Measure_Start_Value(2);
  #endif
  #endif
}
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : void SchM_Exit_McalLib_CpuEndInit(void)                 **
**                                                                            **
** Description      : Exit Module exclusive area                              **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Not Reentrant on same CPU, Reentrant on other CPUs      **
**                                                                            **
** Parameters(in)   : None                                                    **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void SchM_Exit_McalLib_CpuEndInit(void)
{
  #ifdef LATENCY_CALC_MCALLIB
  #if(LATENCY_CALC_MCALLIB==1U)
  Measure_End_Value(2);
  #endif
  #endif
  ResumeAllInterrupts();
}
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : void SchM_Enter_McalLib_StmTimerResolution(void)        **
**                                                                            **
** Description      : Enters Module exclusive area                            **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Not Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void SchM_Enter_McalLib_StmTimerResolution(void)
{
  SuspendAllInterrupts();
  #ifdef LATENCY_CALC_MCALLIB
  #if(LATENCY_CALC_MCALLIB==1U)
  Measure_Start_Value(3);
  #endif
  #endif
}
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : void SchM_Exit_McalLib_StmTimerResolution(void)         **
**                                                                            **
** Description      : Exit Module exclusive area                              **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Not Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void SchM_Exit_McalLib_StmTimerResolution(void)
{
  #ifdef LATENCY_CALC_MCALLIB
  #if(LATENCY_CALC_MCALLIB==1U)
  Measure_End_Value(3);
  #endif
  #endif
  ResumeAllInterrupts();
}
