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
**  FILENAME     : SchM_Smu.h                                                 **
**                                                                            **
**  VERSION      : 4.0.0                                                      **
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
**  DESCRIPTION  : SchM file for Smu driver                                   **
**                                                                            **
**  SPECIFICATION(S) : Specification of RTE, AUTOSAR Release 4.2.2            **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/

#include "IFX_Os.h"
#include "SchM_Smu.h"
#ifdef LATENCY_CALC_SMU
#if(LATENCY_CALC_SMU==1U)
#include "Test_Latency.h"
#endif
#endif
void SchM_Enter_Smu_CmdAccess(void)
{
  SuspendAllInterrupts();
  #ifdef LATENCY_CALC_SMU
  #if(LATENCY_CALC_SMU==1U)
  Measure_Start_Value(0);
  #endif
  #endif
}
void SchM_Exit_Smu_CmdAccess(void)
{
  #ifdef LATENCY_CALC_SMU
  #if(LATENCY_CALC_SMU==1U)
  Measure_End_Value(0);
  #endif
  #endif
  ResumeAllInterrupts();
}

void SchM_Enter_Smu_DriverAccess(void)
{
  SuspendAllInterrupts();
  #ifdef LATENCY_CALC_SMU
  #if(LATENCY_CALC_SMU==1U)
  Measure_Start_Value(1);
  #endif
  #endif
}

void SchM_Exit_Smu_DriverAccess(void)
{
  #ifdef LATENCY_CALC_SMU
  #if(LATENCY_CALC_SMU==1U)
  Measure_End_Value(1);
  #endif
  #endif
  ResumeAllInterrupts();
}
