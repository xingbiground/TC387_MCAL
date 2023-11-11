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
**  FILENAME     : SchM_Ocu.c                                                 **
**                                                                            **
**  VERSION      : 2.0.0                                                      **
**                                                                            **
**  DATE         : 2019-04-08                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY : [cover parentID={8304E13E-A9F9-4df1-B706-199E9074774C}]    **
**                                                                            **
**  DESCRIPTION  : SchM file for Ocu driver                                   **
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
#include "SchM_Ocu.h"
#ifdef LATENCY_CALC_OCU
#if(LATENCY_CALC_OCU==1U)
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
** Traceability: [cover parentID={60552A04-15D1-4d0e-85A8-BD93736D55BF}]      **
**                                                                            **
** Syntax           : void SchM_Enter_Ocu_SetPinAction(void)                  **
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

void SchM_Enter_Ocu_SetPinAction(void)
{
  SuspendAllInterrupts();
  #ifdef LATENCY_CALC_OCU
  #if(LATENCY_CALC_OCU==1U)
  Measure_Start_Value(0);
  #endif
  #endif
}

/*******************************************************************************
** Traceability: [cover parentID={60552A04-15D1-4d0e-85A8-BD93736D55BF}]      **
**                                                                            **
** Syntax           : void SchM_Exit_Ocu_SetPinAction(void)                   **
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
void SchM_Exit_Ocu_SetPinAction(void)
{
  #ifdef LATENCY_CALC_OCU
  #if(LATENCY_CALC_OCU==1U)
  Measure_End_Value(0);
  #endif
  #endif
  ResumeAllInterrupts();
}

/*******************************************************************************
** Traceability: [cover parentID={13B92880-E836-49c4-9DC8-E94328C67CBE}]      **
**                                                                            **
** Syntax           : void SchM_Enter_Ocu_SetThresholdValue(void)                  **
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

void SchM_Enter_Ocu_SetThresholdValue(void)
{
  SuspendAllInterrupts();
  #ifdef LATENCY_CALC_OCU
  #if(LATENCY_CALC_OCU==1U)
  Measure_Start_Value(1);
  #endif
  #endif
}

/*******************************************************************************
** Traceability: [cover parentID={13B92880-E836-49c4-9DC8-E94328C67CBE}]      **
**                                                                            **
** Syntax           : void SchM_Exit_Ocu_SetThresholdValue(void)              **
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
void SchM_Exit_Ocu_SetThresholdValue(void)
{
  #ifdef LATENCY_CALC_OCU
  #if(LATENCY_CALC_OCU==1U)
  Measure_End_Value(1);
  #endif
  #endif
  ResumeAllInterrupts();
}


/*******************************************************************************
** Traceability: [cover parentID={23E6E12B-8B3D-4e89-9B5B-4E5218AEE272}]      **
**                                                                            **
** Syntax           : void SchM_Enter_Ocu_EnDisCCU1Irq(void)                  **
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

void SchM_Enter_Ocu_EnDisCCU1Irq(void)
{
  SuspendAllInterrupts();
  #ifdef LATENCY_CALC_OCU
  #if(LATENCY_CALC_OCU==1U)
  Measure_Start_Value(2);
  #endif
  #endif
}

/*******************************************************************************
** Traceability: [cover parentID={23E6E12B-8B3D-4e89-9B5B-4E5218AEE272}]      **
**                                                                            **
** Syntax           : void SchM_Exit_Ocu_EnDisCCU1Irq(void)                   **
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
void SchM_Exit_Ocu_EnDisCCU1Irq(void)
{
  #ifdef LATENCY_CALC_OCU
  #if(LATENCY_CALC_OCU==1U)
  Measure_End_Value(2);
  #endif
  #endif
  ResumeAllInterrupts();
}

