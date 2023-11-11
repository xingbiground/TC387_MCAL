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
**  FILENAME     : SchM_Spi.c                                                 **
**                                                                            **
**  VERSION      : 3.1.0                                                      **
**                                                                            **
**  DATE         : 2021-03-08                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : SchM file for Spi driver                                   **
**                                                                            **
**  SPECIFICATION(S) : Specification of RTE, AUTOSAR Release                  **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
#include "IFX_Os.h"
#include "SchM_Spi.h"
#ifdef LATENCY_CALC_SPI
#if(LATENCY_CALC_SPI==1U)
#include "Test_Latency.h"
#endif
#endif

/*******************************************************************************
** Traceability: [cover parentID={2382A5CE-AD34-4327-8FC5-5B06429341C0}]      **
**                                                                            **
** Syntax           : void SchM_Enter_Spi_Queue_Update(void)                  **
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
void SchM_Enter_Spi_Queue_Update(void)
{
  SuspendAllInterrupts();
  #ifdef LATENCY_CALC_SPI
  #if(LATENCY_CALC_SPI==1U)
  Measure_Start_Value(0);
  #endif
  #endif
}

/*******************************************************************************
** Traceability: [cover parentID={2382A5CE-AD34-4327-8FC5-5B06429341C0}]      **
**                                                                            **
** Syntax           : void SchM_Exit_Spi_Queue_Update(void)                   **
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
** Description      : Exits Module exclusive area                             **
**                                                                            **
*******************************************************************************/
void SchM_Exit_Spi_Queue_Update(void)
{
  #ifdef LATENCY_CALC_SPI
  #if(LATENCY_CALC_SPI==1U)
  Measure_End_Value(0);
  #endif
  #endif
  ResumeAllInterrupts();
}

/*******************************************************************************
** Traceability: [cover parentID={8A100D12-7FA7-419e-A536-40E49470C9D1}]      **
**                                                                            **
** Syntax           : void SchM_Enter_Spi_SyncLock(void)                      **
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
void SchM_Enter_Spi_SyncLock(void)
{
  SuspendAllInterrupts();
  #ifdef LATENCY_CALC_SPI
  #if(LATENCY_CALC_SPI==1U)
  Measure_Start_Value(1);
  #endif
  #endif
}

/*******************************************************************************
** Traceability: [cover parentID={8A100D12-7FA7-419e-A536-40E49470C9D1}]      **
**                                                                            **
** Syntax           : void SchM_Exit_Spi_SyncLock(void)                       **
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
** Description      : Exits Module exclusive area                             **
**                                                                            **
*******************************************************************************/
void SchM_Exit_Spi_SyncLock(void)
{
  #ifdef LATENCY_CALC_SPI
  #if(LATENCY_CALC_SPI==1U)
  Measure_End_Value(1);
  #endif
  #endif
  ResumeAllInterrupts();
}
