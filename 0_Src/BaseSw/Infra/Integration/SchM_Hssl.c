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
**  FILENAME     : SchM_Hssl.c                                                 **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2019-05-15                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : SchM file for HSSL driver                                   **
**                                                                            **
**  SPECIFICATION(S) : Specification of RTE, AUTOSAR Release 4.2.2            **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
#include "IFX_Os.h"
#include "SchM_Hssl.h"

#ifdef LATENCY_CALC_HSSL
#if(LATENCY_CALC_HSSL==1U)
    #include "Test_Latency.h"
#endif
#endif
void SchM_Enter_Hssl_ChannelStatusLock(void)
{
    SuspendAllInterrupts();
    #ifdef LATENCY_CALC_HSSL
    #if(LATENCY_CALC_HSSL==1U)
        Measure_Start_Value(0);
    #endif
    #endif
}

void SchM_Exit_Hssl_ChannelStatusLock(void)
{
    #ifdef LATENCY_CALC_HSSL
    #if(LATENCY_CALC_HSSL==1U)
        Measure_End_Value(0);
    #endif
    #endif
    ResumeAllInterrupts();
}

void SchM_Enter_Hssl_ActivateSlave(void)
{
    SuspendAllInterrupts();
    #ifdef LATENCY_CALC_HSSL
    #if(LATENCY_CALC_HSSL==1U)
        Measure_Start_Value(1);
    #endif
    #endif
}

void SchM_Exit_Hssl_ActivateSlave(void)
{
    #ifdef LATENCY_CALC_HSSL
    #if(LATENCY_CALC_HSSL==1U)
        Measure_End_Value(1);
    #endif
    #endif
    ResumeAllInterrupts();
}

void SchM_Enter_Hssl_DeactivateSlave(void)
{
    SuspendAllInterrupts();
    #ifdef LATENCY_CALC_HSSL
    #if(LATENCY_CALC_HSSL==1U)
        Measure_Start_Value(2);
    #endif
    #endif
}

void SchM_Exit_Hssl_DeactivateSlave(void)
{
    #ifdef LATENCY_CALC_HSSL
    #if(LATENCY_CALC_HSSL==1U)
        Measure_End_Value(2);
    #endif
    #endif
    ResumeAllInterrupts();
}

void SchM_Enter_Hssl_DmaOperatedCmdQueue(void)
{
    SuspendAllInterrupts();
    #ifdef LATENCY_CALC_HSSL
    #if(LATENCY_CALC_HSSL==1U)
        Measure_Start_Value(3);
    #endif
    #endif
}

void SchM_Exit_Hssl_DmaOperatedCmdQueue(void)
{
    #ifdef LATENCY_CALC_HSSL
    #if(LATENCY_CALC_HSSL==1U)
        Measure_End_Value(3);
    #endif
    #endif
    ResumeAllInterrupts();
}
