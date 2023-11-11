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
**  FILENAME  : Schm_CanTrcv_17_W9255.c                                       **
**                                                                            **
**  VERSION   : 3.0.0                                                         **
**                                                                            **
**  DATE      : 2021-02-25                                                    **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION : This file contains                                          **
**                - SchM sections of CanTrcv_17_W9255 module -                **
**                                                 To be updated by user      **
**                                                                            **
**  SPECIFICATION(S) : Specification of CanTrcv_17_W9255 Driver,              **
**                     AUTOSAR Release 4.2.2                                  **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
#include "IFX_Os.h"
#include "SchM_CanTrcv_17_W9255.h"
#ifdef LATENCY_CALC_CANTRCV_17_W9255
#if(LATENCY_CALC_CANTRCV_17_W9255==1U)
#include "Test_Latency.h"
#endif
#endif

void SchM_Enter_CanTrcv_17_W9255_SpiStatusUpdate(void)
{
  SuspendAllInterrupts();
  #ifdef LATENCY_CALC_CANTRCV_17_W9255
  #if(LATENCY_CALC_CANTRCV_17_W9255==1U)
  Measure_Start_Value(1);
  #endif
  #endif
}

void SchM_Exit_CanTrcv_17_W9255_SpiStatusUpdate(void)
{
  #ifdef LATENCY_CALC_CANTRCV_17_W9255
  #if(LATENCY_CALC_CANTRCV_17_W9255==1U)
  Measure_End_Value(1);
  #endif
  #endif
  ResumeAllInterrupts();
}
