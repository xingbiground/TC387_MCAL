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
**  FILENAME     : SchM_Mcu.c                                                 **
**                                                                            **
**  VERSION      : 3.0.0                                                      **
**                                                                            **
**  DATE         : 2018-02-04                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : SchM file for Mcu                                          **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
#include "IFX_Os.h"
#include "SchM_Mcu.h"
#ifdef LATENCY_CALC_MCU
#if(LATENCY_CALC_MCU==1U)
#include "Test_Latency.h"
#endif
#endif

/*******************************************************************************
** Traceability     : [cover parentID={02EC2514-8DF2-4874-914C-9FFE5A5AE438}] **
**                                                                            **
** Syntax           : void SchM_Enter_Mcu_TomTgcReg(void)                     **
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
void SchM_Enter_Mcu_TomTgcReg(void)
{
  SuspendAllInterrupts();
  #ifdef LATENCY_CALC_MCU
  #if(LATENCY_CALC_MCU==1U)
  Measure_Start_Value(0);
  #endif
  #endif
}

/*******************************************************************************
** Traceability     : [cover parentID={02EC2514-8DF2-4874-914C-9FFE5A5AE438}] **
**                                                                            **
** Syntax           : void SchM_Exit_Mcu_TomTgcReg(void)                      **
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
void SchM_Exit_Mcu_TomTgcReg(void)
{
  #ifdef LATENCY_CALC_MCU
  #if(LATENCY_CALC_MCU==1U)
  Measure_End_Value(0);
  #endif
  #endif
  ResumeAllInterrupts();
}

/*******************************************************************************
** Traceability     : [cover parentID={02EC2514-8DF2-4874-914C-9FFE5A5AE438}] **
**                                                                            **
** Syntax           : void SchM_Enter_Mcu_AtomAgcReg(void)                    **
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
void SchM_Enter_Mcu_AtomAgcReg(void)
{
  SuspendAllInterrupts();
  #ifdef LATENCY_CALC_MCU
  #if(LATENCY_CALC_MCU==1U)
  Measure_Start_Value(1);
  #endif
  #endif
}

/*******************************************************************************
** Traceability     : [cover parentID={02EC2514-8DF2-4874-914C-9FFE5A5AE438}] **
**                                                                            **
** Syntax           : void SchM_Exit_Mcu_AtomAgcReg(void)                     **
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
void SchM_Exit_Mcu_AtomAgcReg(void)
{
  #ifdef LATENCY_CALC_MCU
  #if(LATENCY_CALC_MCU==1U)
  Measure_End_Value(1);
  #endif
  #endif
  ResumeAllInterrupts();
}
