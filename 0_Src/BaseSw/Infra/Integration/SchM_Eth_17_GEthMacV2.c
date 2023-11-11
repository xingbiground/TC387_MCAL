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
**  FILENAME     : SchM_Eth_17_GEthMacV2.c                                    **
**                                                                            **
**  VERSION      : 2.0.0                                                      **
**                                                                            **
**  DATE         : 2020-08-27                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : SchM file for Eth driver                                   **
**                                                                            **
**  SPECIFICATION(S) : Specification of RTE, AUTOSAR Release 4.4.0            **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "IFX_Os.h"
#include "SchM_Eth_17_GEthMacV2.h"
#ifdef LATENCY_CALC_ETH
#if(LATENCY_CALC_ETH==1U)
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
**                      Global Function Declarations                          **
*******************************************************************************/

/*******************************************************************************
** Syntax           : void SchM_Enter_Eth_17_GEthMacV2_TxDescData             **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Enters Module exclusive area                            **
**                                                                            **
*******************************************************************************/
void SchM_Enter_Eth_17_GEthMacV2_TxDescData(void)
{
  SuspendAllInterrupts();
  #ifdef LATENCY_CALC_ETH
  #if(LATENCY_CALC_ETH==1U)
  Measure_Start_Value(0);
  #endif
  #endif
}

/*******************************************************************************
** Syntax           : void SchM_Exit_Eth_17_GEthMacV2_TxDescData              **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Exits Module exclusive area                             **
**                                                                            **
*******************************************************************************/
void SchM_Exit_Eth_17_GEthMacV2_TxDescData(void)
{
 #ifdef LATENCY_CALC_ETH
  #if(LATENCY_CALC_ETH==1U)
  Measure_End_Value(0);
  #endif
  #endif
  ResumeAllInterrupts();
}

/*******************************************************************************
** Syntax           : void SchM_Enter_Eth_17_GEthMacV2_TxBufIdx               **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Enters Module exclusive area                            **
**                                                                            **
*******************************************************************************/
void SchM_Enter_Eth_17_GEthMacV2_TxBufIdx(void)
{
  SuspendAllInterrupts();
  #ifdef LATENCY_CALC_ETH
  #if(LATENCY_CALC_ETH==1U)
  Measure_Start_Value(0);
  #endif
  #endif
}

/*******************************************************************************
** Syntax           : void SchM_Exit_Eth_17_GEthMacV2_TxBufIdx                **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Exits Module exclusive area                             **
**                                                                            **
*******************************************************************************/
void SchM_Exit_Eth_17_GEthMacV2_TxBufIdx(void)
{
 #ifdef LATENCY_CALC_ETH
  #if(LATENCY_CALC_ETH==1U)
  Measure_End_Value(0);
  #endif
  #endif
  ResumeAllInterrupts();
}

/*******************************************************************************
** Syntax           : void SchM_Enter_Eth_17_GEthMacV2_TxDescDataISR          **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Enters Module exclusive area                            **
**                    This critical section is necessary only in case         **
**                    Ethernet transmit interrupt type is CAT2.               **
**                                                                            **
*******************************************************************************/
void SchM_Enter_Eth_17_GEthMacV2_TxDescDataISR(void)
{
  SuspendAllInterrupts();
  #ifdef LATENCY_CALC_ETH
  #if(LATENCY_CALC_ETH==1U)
  Measure_Start_Value(0);
  #endif
  #endif
}

/*******************************************************************************
** Syntax           : void SchM_Exit_Eth_17_GEthMacV2_TxDescDataISR           **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Exits Module exclusive area                             **
**                    This critical section is necessary only in case         **
**                    Ethernet transmit interrupt type is CAT2.               **
**                                                                            **
*******************************************************************************/
void SchM_Exit_Eth_17_GEthMacV2_TxDescDataISR(void)
{
 #ifdef LATENCY_CALC_ETH
  #if(LATENCY_CALC_ETH==1U)
  Measure_End_Value(0);
  #endif
  #endif
  ResumeAllInterrupts();
}

