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
**  FILENAME     : SchM_Can_17_McmCan.c                                       **
**                                                                            **
**  VERSION      : 4.0.0                                                      **
**                                                                            **
**  DATE         : 2021-02-24                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY : [cover parentID={C687AA66-91F6-4aa6-8F32-1AE0562C9A47}]    **
**                                                                            **
**  DESCRIPTION  : SchM file for Can driver                                   **
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
#include "SchM_Can_17_McmCan.h"
#ifdef LATENCY_CALC_CAN
#if(LATENCY_CALC_CAN==1U)
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
** Syntax           : void SchM_Enter_Can_17_McmCan_IcomMsgCntrVal(void)      **
**                                                                            **
** Service ID       : NA                                                      **
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
void SchM_Enter_Can_17_McmCan_IcomMsgCntrVal(void)
{
  SuspendAllInterrupts();
  #ifdef LATENCY_CALC_CAN
  #if(LATENCY_CALC_CAN==1U)
  Measure_Start_Value(0);
  #endif
  #endif
}

/*******************************************************************************
** Syntax           : void SchM_Exit_Can_17_McmCan_IcomMsgCntrVal(void)       **
**                                                                            **
** Service ID       : NA                                                      **
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
void SchM_Exit_Can_17_McmCan_IcomMsgCntrVal(void)
{
  #ifdef LATENCY_CALC_CAN
  #if(LATENCY_CALC_CAN==1U)
  Measure_End_Value(0);
  #endif
  #endif
  ResumeAllInterrupts();
}

/*******************************************************************************
** Syntax           : void SchM_Enter_Can_17_McmCan_CanWrMO(void)             **
**                                                                            **
** Service ID       : NA                                                      **
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
void SchM_Enter_Can_17_McmCan_CanWrMO(void)
{
  SuspendAllInterrupts();
  #ifdef LATENCY_CALC_CAN
  #if(LATENCY_CALC_CAN==1U)
  Measure_Start_Value(1);
  #endif
  #endif
}

/*******************************************************************************
** Syntax           : void SchM_Exit_Can_17_McmCan_CanWrMO(void)              **
**                                                                            **
** Service ID       : NA                                                      **
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
void SchM_Exit_Can_17_McmCan_CanWrMO(void)
{
  #ifdef LATENCY_CALC_CAN
  #if(LATENCY_CALC_CAN==1U)
  Measure_End_Value(1);
  #endif
  #endif
  ResumeAllInterrupts();
}

