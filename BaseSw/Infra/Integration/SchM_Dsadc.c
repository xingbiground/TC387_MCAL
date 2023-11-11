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
**  FILENAME  : Schm_Dsadc.c                                                  **
**                                                                            **
**  VERSION   : 3.0.0                                                         **
**                                                                            **
**  DATE      : 2021.09.08                                                    **
**                                                                            **
**  VARIANT   : Post-Build                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION : SchM file for Dsadc driver                                  **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
#include "IFX_Os.h"
#include "SchM_Dsadc.h"
#ifdef LATENCY_CALC_DSADC
#if(LATENCY_CALC_DSADC==1U)
#include "Test_Latency.h"
#endif
#endif

void SchM_Enter_Dsadc_ChannelData(void)
{
  SuspendAllInterrupts();
  #ifdef LATENCY_CALC_DSADC
  #if(LATENCY_CALC_DSADC==1U)
  Measure_Start_Value(0);
  #endif
  #endif
}

void SchM_Exit_Dsadc_ChannelData(void)
{
  #ifdef LATENCY_CALC_DSADC
  #if(LATENCY_CALC_DSADC==1U)
  Measure_End_Value(0);
  #endif
  #endif
  ResumeAllInterrupts();
}


void SchM_Enter_Dsadc_IntegratorRestart(void)
{
  SuspendAllInterrupts();
  #ifdef LATENCY_CALC_DSADC
  #if(LATENCY_CALC_DSADC==1U)
  Measure_Start_Value(0);
  #endif
  #endif
}

void SchM_Exit_Dsadc_IntegratorRestart(void)
{
  #ifdef LATENCY_CALC_DSADC
  #if(LATENCY_CALC_DSADC==1U)
  Measure_End_Value(0);
  #endif
  #endif
  ResumeAllInterrupts();
}



