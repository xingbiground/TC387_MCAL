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
**  FILENAME     : SchM_Fr_17_Eray.c                                          **
**                                                                            **
**  VERSION      : 4.0.0                                                      **
**                                                                            **
**  DATE         : 2020-06-30                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : SchM file for Fr driver                                    **
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
#include "SchM_Fr_17_Eray.h"

#ifdef LATENCY_CALC_FR
#if(LATENCY_CALC_FR==1U)
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
** Traceability    : [cover parentID={261640D2-77D0-45ba-A607-C550B333E62E}]  **
**                                                                            **
** Syntax           : SchM_Enter_Fr_17_Eray_ConfigLockKey                     **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : Enters Module exclusive area for Lock sequence to leave **
**                    "CONFIG" state by writing to SUCC1.CMD commands READY   **
*******************************************************************************/
void SchM_Enter_Fr_17_Eray_ConfigLockKey(void)
{
  SuspendAllInterrupts();
  #ifdef LATENCY_CALC_FR
  #if(LATENCY_CALC_FR==1U)
  Measure_Start_Value(0);
  #endif
  #endif
}

/*******************************************************************************
** Traceability    : [cover parentID={261640D2-77D0-45ba-A607-C550B333E62E}]  **
**                                                                            **
** Syntax           : SchM_Exit_Fr_17_Eray_ConfigLockKey                      **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : Exits Module exclusive area for Lock sequence to leave  **
**                    "CONFIG" state by writing to SUCC1.CMD commands READY   **
**                                                                            **
*******************************************************************************/
void SchM_Exit_Fr_17_Eray_ConfigLockKey(void)
{
  #ifdef LATENCY_CALC_FR
  #if(LATENCY_CALC_FR==1U)
  Measure_End_Value(0);
  #endif
  #endif
  ResumeAllInterrupts();
}
