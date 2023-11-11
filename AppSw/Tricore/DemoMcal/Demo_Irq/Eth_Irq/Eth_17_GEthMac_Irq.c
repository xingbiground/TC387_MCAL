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
**  FILENAME  : Eth_17_GEthMac_Irq.c                                          **
**                                                                            **
**  VERSION   : 7.0.0                                                         **
**                                                                            **
**  DATE      : 2021-11-09                                                    **
**                                                                            **
**  VARIANT   : Post-Build                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION : This file contains the interrupt frames for the ETH Module. **
**                                                                            **
**  SPECIFICATION(S) : Specification of ETH Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : Yes                                              **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Include Eth header file Eth.h */
#include "Eth_17_GEthMac.h"
/*Include Irq Module*/
#include "Irq.h"

#include "IFX_Os.h"
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  #include "Test_Main.h"
#endif
#endif

/*******************************************************************************
**                      Imported Compiler Switch Checks                       **
*******************************************************************************/

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#if (IRQ_GETH0_EXIST == STD_ON)
/*******************************************************************************
** Syntax           : void GETH-SR0_ISR(void)                                 **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Receive Buffer unavailble interrupt handler for         **
**                    Controller 0 Channel-0 Rx-DMA                           **
**                                                                            **
*******************************************************************************/
#if((IRQ_GETH_SR0_PRIO > 0) || (IRQ_GETH_SR0_CAT == IRQ_CAT2))
#if((IRQ_GETH_SR0_PRIO > 0) && (IRQ_GETH_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(ETHSR0_ISR, 0, IRQ_GETH_SR0_PRIO)
#elif IRQ_GETH_SR0_CAT == IRQ_CAT2
ISR(ETHSR0_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  #if(TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  /* Invoke Irq handler from GETH module file  */
  Eth_17_GEthMac_RxDmaCh0IrqHdlr(0);
}
#endif

/*******************************************************************************
** Syntax           : void GETH-SR2_ISR(void)                                 **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Frame transmission completion interrupt handler for     **
**                    Controller 0 Channel-0 Tx-DMA                           **
**                                                                            **
*******************************************************************************/
#if((IRQ_GETH_SR2_PRIO > 0) || (IRQ_GETH_SR2_CAT == IRQ_CAT2))
#if((IRQ_GETH_SR2_PRIO > 0) && (IRQ_GETH_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(ETHSR2_ISR, 0, IRQ_GETH_SR2_PRIO)
#elif IRQ_GETH_SR2_CAT == IRQ_CAT2
ISR(ETHSR2_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  #if(TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  /* Invoke Irq handler from GETH module file  */
  Eth_17_GEthMac_TxDmaCh0IrqHdlr(0);
}
#endif

/*******************************************************************************
** Syntax           : void GETH-SR6_ISR(void)                                 **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Frame reception completion interrupt handler for        **
**                    Controller 0 Channel-0 Rx-DMA                           **
**                                                                            **
*******************************************************************************/
#if((IRQ_GETH_SR6_PRIO > 0) || (IRQ_GETH_SR6_CAT == IRQ_CAT2))
#if((IRQ_GETH_SR6_PRIO > 0) && (IRQ_GETH_SR6_CAT == IRQ_CAT1))
IFX_INTERRUPT(ETHSR6_ISR, 0, IRQ_GETH_SR6_PRIO)
#elif IRQ_GETH_SR6_CAT == IRQ_CAT2
ISR(ETHSR6_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  #if(TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  /* Invoke Irq handler from GETH module file  */
  Eth_17_GEthMac_RxDmaCh0IrqHdlr(0);
}
#endif

#endif /*IRQ_GETH_EXIST == STD_ON */

#if (IRQ_GETH1_EXIST == STD_ON)
/*******************************************************************************
** Syntax           : void GETH1-SR0_ISR(void)                                 **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Receive Buffer unavailble interrupt handler for         **
**                    Controller 1 Channel-0 Rx-DMA                           **
**                                                                            **
*******************************************************************************/
#if((IRQ_GETH1_SR0_PRIO > 0) || (IRQ_GETH1_SR0_CAT == IRQ_CAT2))
#if((IRQ_GETH1_SR0_PRIO > 0) && (IRQ_GETH1_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(ETHSR10_ISR, 0, IRQ_GETH1_SR0_PRIO)
#elif IRQ_GETH1_SR0_CAT == IRQ_CAT2
ISR(ETHSR10_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  #if(TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  /* Invoke Irq handler from GETH module file  */
  Eth_17_GEthMac_RxDmaCh0IrqHdlr(1);
}
#endif
/*******************************************************************************
** Syntax           : void GETH1-SR2_ISR(void)                                 **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Frame transmission completion interrupt handler for     **
**                    Controller 1 Channel-0 Tx-DMA                           **
**                                                                            **
*******************************************************************************/
#if((IRQ_GETH1_SR2_PRIO > 0) || (IRQ_GETH1_SR2_CAT == IRQ_CAT2))
#if((IRQ_GETH1_SR2_PRIO > 0) && (IRQ_GETH1_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(ETHSR12_ISR, 0, IRQ_GETH1_SR2_PRIO)
#elif IRQ_GETH1_SR2_CAT == IRQ_CAT2
ISR(ETHSR12_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  #if(TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  /* Invoke Irq handler from GETH module file  */
  Eth_17_GEthMac_TxDmaCh0IrqHdlr(1);
}
#endif
/*******************************************************************************
** Syntax           : void GETH1-SR6_ISR(void)                                 **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Frame reception completion interrupt handler for        **
**                    Controller 1 Channel-0 Rx-DMA                           **
**                                                                            **
*******************************************************************************/
#if((IRQ_GETH1_SR6_PRIO > 0) || (IRQ_GETH1_SR6_CAT == IRQ_CAT2))
#if((IRQ_GETH1_SR6_PRIO > 0) && (IRQ_GETH1_SR6_CAT == IRQ_CAT1))
IFX_INTERRUPT(ETHSR16_ISR, 0, IRQ_GETH1_SR6_PRIO)
#elif IRQ_GETH1_SR16_CAT == IRQ_CAT2
ISR(ETHSR16_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  #if(TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  /* Invoke Irq handler from GETH module file  */
  Eth_17_GEthMac_RxDmaCh0IrqHdlr(1);
}
#endif
#endif /*IRQ_GETH_EXIST == STD_ON */

