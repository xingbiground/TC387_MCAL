/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2016)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : SchM_Dma.c                                                 **
**                                                                            **
**  VERSION      : 2.0.0                                                      **
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
**  DESCRIPTION  : SchM file for Dma driver                                   **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
#include "IFX_Os.h"
#include "SchM_Dma.h"
#ifdef LATENCY_CALC_DMA
#if(LATENCY_CALC_DMA==1U)
#include "Test_Latency.h"
#endif
#endif


void SchM_Enter_Dma_ChannelConfigUpdate(void)
{
  SuspendAllInterrupts();
  #ifdef LATENCY_CALC_DMA
  #if(LATENCY_CALC_DMA==1U)
  Measure_Start_Value(0);
  #endif
  #endif
}

void SchM_Exit_Dma_ChannelConfigUpdate(void)
{
  #ifdef LATENCY_CALC_DMA
  #if(LATENCY_CALC_DMA==1U)
  Measure_End_Value(0);
  #endif
  #endif
  ResumeAllInterrupts();
}
