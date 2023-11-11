/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2021)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME   : Dma_Irq.c                                                   **
**                                                                           **
**  VERSION      : 3.0.0                                                     **
**                                                                           **
**  DATE         : 2021-11-09                                                **
**                                                                           **
**  VARIANT      : Variant PB                                                **
**                                                                           **
**  PLATFORM     : Infineon AURIX2G                                          **
**                                                                           **
**  AUTHOR       : DL-AUTOSAR-Engineering                                    **
**                                                                           **
**  VENDOR       : Infineon Technologies                                     **
**                                                                           **
**  DESCRIPTION  : This file contains the interrupt frames for the DMA.      **
**                                                                           **
**  SPECIFICATION(S) : NA                                                    **
**                                                                           **
**  MAY BE CHANGED BY USER : yes                                             **
**                                                                           **
******************************************************************************/

/******************************************************************************
**                      Includes                                             **
******************************************************************************/
#include "Dma.h"
#include "IFX_Os.h"
#include "Irq.h"

#ifdef  APP_SW
#if(APP_SW == TEST_APP)
#include "Test_Main.h"
#endif
#endif
/*******************************************************************************
**                      Private Macros Definitions                            **
*******************************************************************************/

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
/*If Test module is crc*/
#ifdef  APP_SW
#if((defined BASE_TEST_MODULE_ID) && ((BASE_TEST_MODULE_ID == 201)) &&\
     (APP_SW == TEST_APP))
#include "Test_Time.h"
void Timer_DelayMs(uint32 ReqTimeMs);
extern volatile uint8 u8g_Resilience_Delay_En;
#endif
#endif
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

/******************************************************************************
** Syntax : void DMAERR0SR_ISR(void)                                         **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA error interrupts which can be due to Source **
**               ,destination, TCS, RAM or safelinked list checksum error.   **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_ERR0_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_ERR0_SR_PRIO > 0U) || (IRQ_DMA_ERR0_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_ERR0_SR_PRIO > 0U) && (IRQ_DMA_ERR0_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMAERR0SR_ISR, 0, IRQ_DMA_ERR0_SR_PRIO)
#elif IRQ_DMA_ERR0_SR_CAT == IRQ_CAT2
ISR(DMAERR0SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_MEInterruptDispatcher();
}
#endif
#endif
/******************************************************************************
** Syntax : void DMAERR1SR_ISR(void)                                         **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA error interrupts which can be due to Source **
**               ,destination, TCS, RAM or safelinked list checksum error.   **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_ERR1_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_ERR1_SR_PRIO > 0U) || (IRQ_DMA_ERR1_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_ERR1_SR_PRIO > 0U) && (IRQ_DMA_ERR1_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMAERR1SR_ISR, 0, IRQ_DMA_ERR1_SR_PRIO)
#elif IRQ_DMA_ERR1_SR_CAT == IRQ_CAT2
ISR(DMAERR1SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_MEInterruptDispatcher();
}
#endif
#endif

/******************************************************************************
** Syntax : void DMAERR2SR_ISR(void)                                         **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA error interrupts which can be due to Source **
**               ,destination, TCS, RAM or safelinked list checksum error.   **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_ERR2_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_ERR2_SR_PRIO > 0U) || (IRQ_DMA_ERR2_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_ERR2_SR_PRIO > 0U) && (IRQ_DMA_ERR2_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMAERR2SR_ISR, 0, IRQ_DMA_ERR2_SR_PRIO)
#elif IRQ_DMA_ERR2_SR_CAT == IRQ_CAT2
ISR(DMAERR2SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_MEInterruptDispatcher();
}
#endif
#endif
/******************************************************************************
** Syntax : void DMAERR3SR_ISR(void)                                         **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA error interrupts which can be due to Source **
**               ,destination, TCS, RAM or safelinked list checksum error.   **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_ERR3_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_ERR3_SR_PRIO > 0U) || (IRQ_DMA_ERR3_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_ERR3_SR_PRIO > 0U) && (IRQ_DMA_ERR3_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMAERR3SR_ISR, 0, IRQ_DMA_ERR3_SR_PRIO)
#elif IRQ_DMA_ERR3_SR_CAT == IRQ_CAT2
ISR(DMAERR3SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_MEInterruptDispatcher();
}
#endif
#endif
/******************************************************************************
** Syntax : void DMACH0SR_ISR(void)                                          **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel0 for service a node on Channel      **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL0_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL0_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL0_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL0_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL0_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH0SR_ISR, 0, IRQ_DMA_CHANNEL0_SR_PRIO)
#elif IRQ_DMA_CHANNEL0_SR_CAT == IRQ_CAT2
ISR(DMACH0SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(0U);
}
#endif
#endif
/******************************************************************************
** Syntax : void DMACH1SR_ISR(void)                                          **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel1 for service a node on Channel      **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL1_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL1_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL1_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL1_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL1_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH1SR_ISR, 0, IRQ_DMA_CHANNEL1_SR_PRIO)
#elif IRQ_DMA_CHANNEL1_SR_CAT == IRQ_CAT2
ISR(DMACH1SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
  /* Specific amount of Delay is provided to perform Resilience test based on the resilience flag selection */
  #if(((defined BASE_TEST_MODULE_ID) && ((BASE_TEST_MODULE_ID == 201))) &&\
      (APP_SW == TEST_APP))
  if(u8g_Resilience_Delay_En==1)
  {
    Timer_DelayMs(1);
    u8g_Resilience_Delay_En = 0;
  }
  #endif
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(1U);
}
#endif /* Channel 1 */
#endif
/******************************************************************************
** Syntax : void DMACH2SR_ISR(void)                                          **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel2 for service a node on Channel      **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL2_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL2_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL2_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL2_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL2_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH2SR_ISR, 0, IRQ_DMA_CHANNEL2_SR_PRIO)
#elif IRQ_DMA_CHANNEL2_SR_CAT == IRQ_CAT2
ISR(DMACH2SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(2U);
}
#endif /* Channel 2  */
#endif
/******************************************************************************
** Syntax : void DMACH3SR_ISR(void)                                          **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel3 for service a node on Channel      **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL3_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL3_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL3_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL3_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL3_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH3SR_ISR, 0, IRQ_DMA_CHANNEL3_SR_PRIO)
#elif IRQ_DMA_CHANNEL3_SR_CAT == IRQ_CAT2
ISR(DMACH3SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(3U);
}
#endif /* Channel 3  */
#endif
/******************************************************************************
** Syntax : void DMACH4SR_ISR(void)                                          **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel4 for service a node on Channel      **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL4_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL4_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL4_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL4_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL4_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH4SR_ISR, 0, IRQ_DMA_CHANNEL4_SR_PRIO)
#elif IRQ_DMA_CHANNEL4_SR_CAT == IRQ_CAT2
ISR(DMACH4SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(4U);
}
#endif /* Channel 4  */
#endif
/******************************************************************************
** Syntax : void DMACH5SR_ISR(void)                                          **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel5 for service a node on Channel      **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL5_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL5_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL5_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL5_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL5_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH5SR_ISR, 0, IRQ_DMA_CHANNEL5_SR_PRIO)
#elif IRQ_DMA_CHANNEL5_SR_CAT == IRQ_CAT2
ISR(DMACH5SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(5U);
}
#endif /* Channel 5  */
#endif
/******************************************************************************
** Syntax : void DMACH6SR_ISR(void)                                          **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel6 for service a node on Channel      **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL6_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL6_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL6_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL6_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL6_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH6SR_ISR, 0, IRQ_DMA_CHANNEL6_SR_PRIO)
#elif IRQ_DMA_CHANNEL6_SR_CAT == IRQ_CAT2
ISR(DMACH6SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(6U);
}
#endif /* Channel 6  */
#endif
/******************************************************************************
** Syntax : void DMACH7SR_ISR(void)                                          **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel7 for service a node on Channel      **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL7_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL7_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL7_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL7_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL7_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH7SR_ISR, 0, IRQ_DMA_CHANNEL7_SR_PRIO)
#elif IRQ_DMA_CHANNEL7_SR_CAT == IRQ_CAT2
ISR(DMACH7SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(7U);
}
#endif /* Channel 7   */
#endif
/******************************************************************************
** Syntax : void DMACH8SR_ISR(void)                                          **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel8 for service a node on Channel      **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL8_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL8_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL8_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL8_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL8_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH8SR_ISR, 0, IRQ_DMA_CHANNEL8_SR_PRIO)
#elif IRQ_DMA_CHANNEL8_SR_CAT == IRQ_CAT2
ISR(DMACH8SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(8U);
}
#endif /* Channel 8  */
#endif
/******************************************************************************
** Syntax : void DMACH9SR_ISR(void)                                          **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel9 for service a node on Channel      **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL9_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL9_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL9_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL9_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL9_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH9SR_ISR, 0, IRQ_DMA_CHANNEL9_SR_PRIO)
#elif IRQ_DMA_CHANNEL9_SR_CAT == IRQ_CAT2
ISR(DMACH9SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(9U);
}
#endif /* Channel 9   */
#endif
/******************************************************************************
** Syntax : void DMACH10SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel10 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL10_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL10_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL10_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL10_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL10_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH10SR_ISR, 0, IRQ_DMA_CHANNEL10_SR_PRIO)
#elif IRQ_DMA_CHANNEL10_SR_CAT == IRQ_CAT2
ISR(DMACH10SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(10U);
}
#endif /* Channel 10  */
#endif
/******************************************************************************
** Syntax : void DMACH11SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel11 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL11_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL11_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL11_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL11_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL11_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH11SR_ISR, 0, IRQ_DMA_CHANNEL11_SR_PRIO)
#elif IRQ_DMA_CHANNEL11_SR_CAT == IRQ_CAT2
ISR(DMACH11SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(11U);
}
#endif /* Channel 11  */
#endif
/******************************************************************************
** Syntax : void DMACH12SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel12 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL12_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL12_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL12_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL12_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL12_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH12SR_ISR, 0, IRQ_DMA_CHANNEL12_SR_PRIO)
#elif IRQ_DMA_CHANNEL12_SR_CAT == IRQ_CAT2
ISR(DMACH12SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(12U);
}
#endif /* Channel 12  */
#endif
/******************************************************************************
** Syntax : void DMACH13SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel13 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL13_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL13_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL13_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL13_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL13_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH13SR_ISR, 0, IRQ_DMA_CHANNEL13_SR_PRIO)
#elif IRQ_DMA_CHANNEL13_SR_CAT == IRQ_CAT2
ISR(DMACH13SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(13U);
}
#endif /* Channel 13   */
#endif
/******************************************************************************
** Syntax : void DMACH14SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel14 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL14_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL14_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL14_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL14_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL14_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH14SR_ISR, 0, IRQ_DMA_CHANNEL14_SR_PRIO)
#elif IRQ_DMA_CHANNEL14_SR_CAT == IRQ_CAT2
ISR(DMACH14SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(14U);
}
#endif /* Channel 14   */
#endif
/******************************************************************************
** Syntax : void DMACH15SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel15 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL15_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL15_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL15_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL15_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL15_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH15SR_ISR, 0, IRQ_DMA_CHANNEL15_SR_PRIO)
#elif IRQ_DMA_CHANNEL15_SR_CAT == IRQ_CAT2
ISR(DMACH15SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(15U);
}
#endif /* Channel 15   */
#endif
/******************************************************************************
** Syntax : void DMACH16SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel16 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL16_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL16_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL16_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL16_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL16_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH16SR_ISR, 0, IRQ_DMA_CHANNEL16_SR_PRIO)
#elif IRQ_DMA_CHANNEL16_SR_CAT == IRQ_CAT2
ISR(DMACH16SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(16U);
}
#endif /* Channel 16   */
#endif
/******************************************************************************
** Syntax : void DMACH17SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel17 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL17_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL17_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL17_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL17_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL17_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH17SR_ISR, 0, IRQ_DMA_CHANNEL17_SR_PRIO)
#elif IRQ_DMA_CHANNEL17_SR_CAT == IRQ_CAT2
ISR(DMACH17SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif
  Dma_ChInterruptHandler(17U);
}
#endif /* Channel 17   */
#endif
/******************************************************************************
** Syntax : void DMACH18SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel18 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL18_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL18_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL18_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL18_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL18_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH18SR_ISR, 0, IRQ_DMA_CHANNEL18_SR_PRIO)
#elif IRQ_DMA_CHANNEL18_SR_CAT == IRQ_CAT2
ISR(DMACH18SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(18U);
}
#endif /* Channel 18   */
#endif
/******************************************************************************
** Syntax : void DMACH19SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel19 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL19_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL19_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL19_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL19_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL19_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH19SR_ISR, 0, IRQ_DMA_CHANNEL19_SR_PRIO)
#elif IRQ_DMA_CHANNEL19_SR_CAT == IRQ_CAT2
ISR(DMACH19SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(19U);
}
#endif /* Channel 19   */
#endif
/******************************************************************************
** Syntax : void DMACH20SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel20 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL20_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL20_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL20_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL20_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL20_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH20SR_ISR, 0, IRQ_DMA_CHANNEL20_SR_PRIO)
#elif IRQ_DMA_CHANNEL20_SR_CAT == IRQ_CAT2
ISR(DMACH20SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
 #ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(20U);
}
#endif /* Channel 20   */
#endif
/******************************************************************************
** Syntax : void DMACH21SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel21 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL21_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL21_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL21_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL21_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL21_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH21SR_ISR, 0, IRQ_DMA_CHANNEL21_SR_PRIO)
#elif IRQ_DMA_CHANNEL21_SR_CAT == IRQ_CAT2
ISR(DMACH21SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(21U);
}
#endif /* Channel 21   */
#endif
/******************************************************************************
** Syntax : void DMACH22SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel22 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL22_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL22_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL22_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL22_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL22_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH22SR_ISR, 0, IRQ_DMA_CHANNEL22_SR_PRIO)
#elif IRQ_DMA_CHANNEL22_SR_CAT == IRQ_CAT2
ISR(DMACH22SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(22U);
}
#endif /* Channel 22   */
#endif
/******************************************************************************
** Syntax : void DMACH23SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel23 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL23_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL23_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL23_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL23_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL23_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH23SR_ISR, 0, IRQ_DMA_CHANNEL23_SR_PRIO)
#elif IRQ_DMA_CHANNEL23_SR_CAT == IRQ_CAT2
ISR(DMACH23SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(23U);
}
#endif /* Channel 23   */
#endif
/******************************************************************************
** Syntax : void DMACH24SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel24 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL24_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL24_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL24_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL24_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL24_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH24SR_ISR, 0, IRQ_DMA_CHANNEL24_SR_PRIO)
#elif IRQ_DMA_CHANNEL24_SR_CAT == IRQ_CAT2
ISR(DMACH24SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(24U);
}
#endif /* Channel 24   */
#endif
/******************************************************************************
** Syntax : void DMACH25SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel25 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL25_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL25_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL25_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL25_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL25_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH25SR_ISR, 0, IRQ_DMA_CHANNEL25_SR_PRIO)
#elif IRQ_DMA_CHANNEL25_SR_CAT == IRQ_CAT2
ISR(DMACH25SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(25U);
}
#endif /* Channel 25   */
#endif
/******************************************************************************
** Syntax : void DMACH26SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel26 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL26_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL26_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL26_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL26_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL26_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH26SR_ISR, 0, IRQ_DMA_CHANNEL26_SR_PRIO)
#elif IRQ_DMA_CHANNEL26_SR_CAT == IRQ_CAT2
ISR(DMACH26SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(26U);
}
#endif /* Channel 26   */
#endif
/******************************************************************************
** Syntax : void DMACH27SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel27 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL27_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL27_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL27_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL27_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL27_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH27SR_ISR, 0, IRQ_DMA_CHANNEL27_SR_PRIO)
#elif IRQ_DMA_CHANNEL27_SR_CAT == IRQ_CAT2
ISR(DMACH27SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(27U);
}
#endif /* Channel 27  */
#endif
/******************************************************************************
** Syntax : void DMACH28SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel28 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL28_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL28_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL28_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL28_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL28_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH28SR_ISR, 0, IRQ_DMA_CHANNEL28_SR_PRIO)
#elif IRQ_DMA_CHANNEL28_SR_CAT == IRQ_CAT2
ISR(DMACH28SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(28U);
}
#endif /* Channel 28   */
#endif
/******************************************************************************
** Syntax : void DMACH29SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel29 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL29_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL29_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL29_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL29_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL29_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH29SR_ISR, 0, IRQ_DMA_CHANNEL29_SR_PRIO)
#elif IRQ_DMA_CHANNEL29_SR_CAT == IRQ_CAT2
ISR(DMACH29SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(29U);
}
#endif /* Channel 29  */
#endif
/******************************************************************************
** Syntax : void DMACH30SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel30 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL30_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL30_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL30_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL30_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL30_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH30SR_ISR, 0, IRQ_DMA_CHANNEL30_SR_PRIO)
#elif IRQ_DMA_CHANNEL30_SR_CAT == IRQ_CAT2
ISR(DMACH30SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(30U);
}
#endif /* Channel 30  */
#endif
/******************************************************************************
** Syntax : void DMACH31SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel31 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL31_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL31_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL31_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL31_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL31_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH31SR_ISR, 0, IRQ_DMA_CHANNEL31_SR_PRIO)
#elif IRQ_DMA_CHANNEL31_SR_CAT == IRQ_CAT2
ISR(DMACH31SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(31U);
}
#endif /* Channel 31  */
#endif
/******************************************************************************
** Syntax : void DMACH32SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel32 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL32_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL32_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL32_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL32_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL32_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH32SR_ISR, 0, IRQ_DMA_CHANNEL32_SR_PRIO)
#elif IRQ_DMA_CHANNEL32_SR_CAT == IRQ_CAT2
ISR(DMACH32SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(32U);
}
#endif /* Channel 32  */
#endif
/******************************************************************************
** Syntax : void DMACH33SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel33 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL33_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL33_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL33_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL33_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL33_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH33SR_ISR, 0, IRQ_DMA_CHANNEL33_SR_PRIO)
#elif IRQ_DMA_CHANNEL33_SR_CAT == IRQ_CAT2
ISR(DMACH33SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(33U);
}
#endif /* Channel 33  */
#endif
/******************************************************************************
** Syntax : void DMACH34SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel34 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL34_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL34_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL34_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL34_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL34_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH34SR_ISR, 0, IRQ_DMA_CHANNEL34_SR_PRIO)
#elif IRQ_DMA_CHANNEL34_SR_CAT == IRQ_CAT2
ISR(DMACH34SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(34U);
}
#endif /* Channel 34  */
#endif
/******************************************************************************
** Syntax : void DMACH35SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel35 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL35_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL35_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL35_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL35_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL35_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH35SR_ISR, 0, IRQ_DMA_CHANNEL35_SR_PRIO)
#elif IRQ_DMA_CHANNEL35_SR_CAT == IRQ_CAT2
ISR(DMACH35SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(35U);
}
#endif /* Channel 35  */
#endif
/******************************************************************************
** Syntax : void DMACH36SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel36 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL36_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL36_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL36_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL36_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL36_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH36SR_ISR, 0, IRQ_DMA_CHANNEL36_SR_PRIO)
#elif IRQ_DMA_CHANNEL36_SR_CAT == IRQ_CAT2
ISR(DMACH36SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(36U);
}
#endif /* Channel 36  */
#endif
/******************************************************************************
** Syntax : void DMACH37SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel37 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL37_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL37_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL37_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL37_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL37_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH37SR_ISR, 0, IRQ_DMA_CHANNEL37_SR_PRIO)
#elif IRQ_DMA_CHANNEL37_SR_CAT == IRQ_CAT2
ISR(DMACH37SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(37U);
}
#endif /* Channel 37  */
#endif
/******************************************************************************
** Syntax : void DMACH38SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel38 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL38_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL38_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL38_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL38_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL38_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH38SR_ISR, 0, IRQ_DMA_CHANNEL38_SR_PRIO)
#elif IRQ_DMA_CHANNEL38_SR_CAT == IRQ_CAT2
ISR(DMACH38SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(38U);
}
#endif /* Channel 38  */
#endif
/******************************************************************************
** Syntax : void DMACH39SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel39 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL39_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL39_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL39_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL39_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL39_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH39SR_ISR, 0, IRQ_DMA_CHANNEL39_SR_PRIO)
#elif IRQ_DMA_CHANNEL39_SR_CAT == IRQ_CAT2
ISR(DMACH39SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(39U);
}
#endif /* Channel 39  */
#endif
/******************************************************************************
** Syntax : void DMACH40SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel40 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL40_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL40_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL40_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL40_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL40_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH40SR_ISR, 0, IRQ_DMA_CHANNEL40_SR_PRIO)
#elif IRQ_DMA_CHANNEL40_SR_CAT == IRQ_CAT2
ISR(DMACH40SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(40U);
}
#endif /* Channel 40  */
#endif
/******************************************************************************
** Syntax : void DMACH41SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel41 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL41_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL41_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL41_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL41_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL41_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH41SR_ISR, 0, IRQ_DMA_CHANNEL41_SR_PRIO)
#elif IRQ_DMA_CHANNEL41_SR_CAT == IRQ_CAT2
ISR(DMACH41SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(41U);
}
#endif /* Channel 41  */
#endif
/******************************************************************************
** Syntax : void DMACH42SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel42 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL42_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL42_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL42_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL42_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL42_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH42SR_ISR, 0, IRQ_DMA_CHANNEL42_SR_PRIO)
#elif IRQ_DMA_CHANNEL42_SR_CAT == IRQ_CAT2
ISR(DMACH42SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(42U);
}
#endif /* Channel 42  */
#endif
/******************************************************************************
** Syntax : void DMACH43SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel43 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL43_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL43_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL43_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL43_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL43_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH43SR_ISR, 0, IRQ_DMA_CHANNEL43_SR_PRIO)
#elif IRQ_DMA_CHANNEL43_SR_CAT == IRQ_CAT2
ISR(DMACH43SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(43U);
}
#endif /* Channel 43  */
#endif
/******************************************************************************
** Syntax : void DMACH44SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel44 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL44_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL44_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL44_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL44_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL44_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH44SR_ISR, 0, IRQ_DMA_CHANNEL44_SR_PRIO)
#elif IRQ_DMA_CHANNEL44_SR_CAT == IRQ_CAT2
ISR(DMACH44SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(44U);
}
#endif /* Channel 44 */
#endif
/******************************************************************************
** Syntax : void DMACH45SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel45 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL45_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL45_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL45_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL45_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL45_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH45SR_ISR, 0, IRQ_DMA_CHANNEL45_SR_PRIO)
#elif IRQ_DMA_CHANNEL45_SR_CAT == IRQ_CAT2
ISR(DMACH45SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(45U);
}
#endif /* Channel 45 */
#endif
/******************************************************************************
** Syntax : void DMACH46SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel46 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL46_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL46_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL46_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL46_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL46_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH46SR_ISR, 0, IRQ_DMA_CHANNEL46_SR_PRIO)
#elif IRQ_DMA_CHANNEL46_SR_CAT == IRQ_CAT2
ISR(DMACH46SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(46U);
}
#endif /* Channel 46 */
#endif
/******************************************************************************
** Syntax : void DMACH47SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel47 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL47_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL47_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL47_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL47_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL47_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH47SR_ISR, 0, IRQ_DMA_CHANNEL47_SR_PRIO)
#elif IRQ_DMA_CHANNEL47_SR_CAT == IRQ_CAT2
ISR(DMACH47SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(47U);
}
#endif /* Channel 47 */
#endif
/******************************************************************************
** Syntax : void DMACH48SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel48 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL48_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL48_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL48_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL48_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL48_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH48SR_ISR, 0, IRQ_DMA_CHANNEL48_SR_PRIO)
#elif IRQ_DMA_CHANNEL48_SR_CAT == IRQ_CAT2
ISR(DMACH48SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(48U);
}
#endif /* Channel 48 */
#endif
/******************************************************************************
** Syntax : void DMACH49SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel49 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL49_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL49_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL49_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL49_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL49_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH49SR_ISR, 0, IRQ_DMA_CHANNEL49_SR_PRIO)
#elif IRQ_DMA_CHANNEL49_SR_CAT == IRQ_CAT2
ISR(DMACH49SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(49U);
}
#endif /* Channel 49 */
#endif
/******************************************************************************
** Syntax : void DMACH50SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel50 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL50_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL50_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL50_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL50_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL50_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH50SR_ISR, 0, IRQ_DMA_CHANNEL50_SR_PRIO)
#elif IRQ_DMA_CHANNEL50_SR_CAT == IRQ_CAT2
ISR(DMACH50SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(50U);
}
#endif /* Channel 50 */
#endif
/******************************************************************************
** Syntax : void DMACH51SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel51 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL51_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL51_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL51_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL51_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL51_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH51SR_ISR, 0, IRQ_DMA_CHANNEL51_SR_PRIO)
#elif IRQ_DMA_CHANNEL51_SR_CAT == IRQ_CAT2
ISR(DMACH51SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(51U);
}
#endif /* Channel 51 */
#endif
/******************************************************************************
** Syntax : void DMACH52SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel52 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL52_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL52_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL52_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL52_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL52_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH52SR_ISR, 0, IRQ_DMA_CHANNEL52_SR_PRIO)
#elif IRQ_DMA_CHANNEL52_SR_CAT == IRQ_CAT2
ISR(DMACH52SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(52U);
}
#endif /* Channel 52 */
#endif
/******************************************************************************
** Syntax : void DMACH53SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel53 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL53_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL53_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL53_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL53_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL53_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH53SR_ISR, 0, IRQ_DMA_CHANNEL53_SR_PRIO)
#elif IRQ_DMA_CHANNEL53_SR_CAT == IRQ_CAT2
ISR(DMACH53SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(53U);
}
#endif /* Channel 53 */
#endif
/******************************************************************************
** Syntax : void DMACH54SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel54 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL54_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL54_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL54_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL54_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL54_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH54SR_ISR, 0, IRQ_DMA_CHANNEL54_SR_PRIO)
#elif IRQ_DMA_CHANNEL54_SR_CAT == IRQ_CAT2
ISR(DMACH54SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(54U);
}
#endif /* Channel 54 */
#endif
/******************************************************************************
** Syntax : void DMACH55SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel55 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL55_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL55_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL55_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL55_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL55_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH55SR_ISR, 0, IRQ_DMA_CHANNEL55_SR_PRIO)
#elif IRQ_DMA_CHANNEL55_SR_CAT == IRQ_CAT2
ISR(DMACH55SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(55U);
}
#endif /* Channel 55 */
#endif
/******************************************************************************
** Syntax : void DMACH56SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel56 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL56_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL56_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL56_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL56_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL56_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH56SR_ISR, 0, IRQ_DMA_CHANNEL56_SR_PRIO)
#elif IRQ_DMA_CHANNEL56_SR_CAT == IRQ_CAT2
ISR(DMACH56SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(56U);
}
#endif /* Channel 56 */
#endif
/******************************************************************************
** Syntax : void DMACH57SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel57 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL57_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL57_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL57_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL57_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL57_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH57SR_ISR, 0, IRQ_DMA_CHANNEL57_SR_PRIO)
#elif IRQ_DMA_CHANNEL57_SR_CAT == IRQ_CAT2
ISR(DMACH57SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(57U);
}
#endif /* Channel 57 */
#endif
/******************************************************************************
** Syntax : void DMACH58SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel58 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL58_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL58_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL58_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL58_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL58_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH58SR_ISR, 0, IRQ_DMA_CHANNEL58_SR_PRIO)
#elif IRQ_DMA_CHANNEL58_SR_CAT == IRQ_CAT2
ISR(DMACH58SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(58U);
}
#endif /* Channel 58 */
#endif
/******************************************************************************
** Syntax : void DMACH59SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel59 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL59_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL59_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL59_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL59_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL59_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH59SR_ISR, 0, IRQ_DMA_CHANNEL59_SR_PRIO)
#elif IRQ_DMA_CHANNEL59_SR_CAT == IRQ_CAT2
ISR(DMACH59SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(59U);
}
#endif /* Channel 59 */
#endif
/******************************************************************************
** Syntax : void DMACH60SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel60 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL60_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL60_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL60_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL60_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL60_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH60SR_ISR, 0, IRQ_DMA_CHANNEL60_SR_PRIO)
#elif IRQ_DMA_CHANNEL60_SR_CAT == IRQ_CAT2
ISR(DMACH60SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(60U);
}
#endif /* Channel 60 */
#endif
/******************************************************************************
** Syntax : void DMACH61SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel61 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL61_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL61_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL61_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL61_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL61_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH61SR_ISR, 0, IRQ_DMA_CHANNEL61_SR_PRIO)
#elif IRQ_DMA_CHANNEL61_SR_CAT == IRQ_CAT2
ISR(DMACH61SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(61U);
}
#endif /* Channel 61 */
#endif
/******************************************************************************
** Syntax : void DMACH62SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel62 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL62_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL62_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL62_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL62_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL62_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH62SR_ISR, 0, IRQ_DMA_CHANNEL62_SR_PRIO)
#elif IRQ_DMA_CHANNEL62_SR_CAT == IRQ_CAT2
ISR(DMACH62SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(62U);
}
#endif /* Channel 62 */
#endif
/******************************************************************************
** Syntax : void DMACH63SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel63 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL63_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL63_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL63_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL63_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL63_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH63SR_ISR, 0, IRQ_DMA_CHANNEL63_SR_PRIO)
#elif IRQ_DMA_CHANNEL63_SR_CAT == IRQ_CAT2
ISR(DMACH63SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(63U);
}
#endif /* Channel 63 */
#endif
/******************************************************************************
** Syntax : void DMACH64SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel64 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL64_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL64_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL64_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL64_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL64_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH64SR_ISR, 0, IRQ_DMA_CHANNEL64_SR_PRIO)
#elif IRQ_DMA_CHANNEL64_SR_CAT == IRQ_CAT2
ISR(DMACH64SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(64U);
}
#endif /* Channel 64 */
#endif
/******************************************************************************
** Syntax : void DMACH65SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel65 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL65_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL65_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL65_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL65_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL65_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH65SR_ISR, 0, IRQ_DMA_CHANNEL65_SR_PRIO)
#elif IRQ_DMA_CHANNEL65_SR_CAT == IRQ_CAT2
ISR(DMACH65SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(65U);
}
#endif /* Channel 65 */
#endif
/******************************************************************************
** Syntax : void DMACH66SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel66 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL66_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL66_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL66_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL66_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL66_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH66SR_ISR, 0, IRQ_DMA_CHANNEL66_SR_PRIO)
#elif IRQ_DMA_CHANNEL66_SR_CAT == IRQ_CAT2
ISR(DMACH66SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(66U);
}
#endif /* Channel 66 */
#endif
/******************************************************************************
** Syntax : void DMACH67SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel67 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL67_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL67_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL67_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL67_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL67_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH67SR_ISR, 0, IRQ_DMA_CHANNEL67_SR_PRIO)
#elif IRQ_DMA_CHANNEL67_SR_CAT == IRQ_CAT2
ISR(DMACH67SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(67U);
}
#endif /* Channel 67 */
#endif
/******************************************************************************
** Syntax : void DMACH68SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel68 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL68_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL68_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL68_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL68_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL68_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH68SR_ISR, 0, IRQ_DMA_CHANNEL68_SR_PRIO)
#elif IRQ_DMA_CHANNEL68_SR_CAT == IRQ_CAT2
ISR(DMACH68SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(68U);
}
#endif /* Channel 68 */
#endif
/******************************************************************************
** Syntax : void DMACH69SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel69 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL69_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL69_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL69_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL69_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL69_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH69SR_ISR, 0, IRQ_DMA_CHANNEL69_SR_PRIO)
#elif IRQ_DMA_CHANNEL69_SR_CAT == IRQ_CAT2
ISR(DMACH69SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(69U);
}
#endif /* Channel 69 */
#endif
/******************************************************************************
** Syntax : void DMACH70SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel70 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL70_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL70_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL70_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL70_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL70_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH70SR_ISR, 0, IRQ_DMA_CHANNEL70_SR_PRIO)
#elif IRQ_DMA_CHANNEL70_SR_CAT == IRQ_CAT2
ISR(DMACH70SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(70U);
}
#endif /* Channel 70 */
#endif
/******************************************************************************
** Syntax : void DMACH71SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel71 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL71_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL71_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL71_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL71_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL71_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH71SR_ISR, 0, IRQ_DMA_CHANNEL71_SR_PRIO)
#elif IRQ_DMA_CHANNEL71_SR_CAT == IRQ_CAT2
ISR(DMACH71SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(71U);
}
#endif /* Channel 71 */
#endif
/******************************************************************************
** Syntax : void DMACH72SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel72 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL72_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL72_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL72_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL72_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL72_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH72SR_ISR, 0, IRQ_DMA_CHANNEL72_SR_PRIO)
#elif IRQ_DMA_CHANNEL72_SR_CAT == IRQ_CAT2
ISR(DMACH72SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(72U);
}
#endif /* Channel 72 */
#endif
/******************************************************************************
** Syntax : void DMACH73SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel73 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL73_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL73_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL73_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL73_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL73_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH73SR_ISR, 0, IRQ_DMA_CHANNEL73_SR_PRIO)
#elif IRQ_DMA_CHANNEL73_SR_CAT == IRQ_CAT2
ISR(DMACH73SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(73U);
}
#endif /* Channel 73 */
#endif
/******************************************************************************
** Syntax : void DMACH74SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel74 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL74_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL74_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL74_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL74_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL74_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH74SR_ISR, 0, IRQ_DMA_CHANNEL74_SR_PRIO)
#elif IRQ_DMA_CHANNEL74_SR_CAT == IRQ_CAT2
ISR(DMACH74SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(74U);
}
#endif /* Channel 74 */
#endif
/******************************************************************************
** Syntax : void DMACH75SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel75 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL75_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL75_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL75_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL75_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL75_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH75SR_ISR, 0, IRQ_DMA_CHANNEL75_SR_PRIO)
#elif IRQ_DMA_CHANNEL75_SR_CAT == IRQ_CAT2
ISR(DMACH75SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(75U);
}
#endif /* Channel 75 */
#endif
/******************************************************************************
** Syntax : void DMACH76SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel76 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL76_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL76_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL76_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL76_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL76_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH76SR_ISR, 0, IRQ_DMA_CHANNEL76_SR_PRIO)
#elif IRQ_DMA_CHANNEL76_SR_CAT == IRQ_CAT2
ISR(DMACH76SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(76U);
}
#endif /* Channel 76 */
#endif
/******************************************************************************
** Syntax : void DMACH77SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel77 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL77_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL77_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL77_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL77_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL77_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH77SR_ISR, 0, IRQ_DMA_CHANNEL77_SR_PRIO)
#elif IRQ_DMA_CHANNEL77_SR_CAT == IRQ_CAT2
ISR(DMACH77SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(77U);
}
#endif /* Channel 77 */
#endif
/******************************************************************************
** Syntax : void DMACH78SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel78 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL78_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL78_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL78_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL78_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL78_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH78SR_ISR, 0, IRQ_DMA_CHANNEL78_SR_PRIO)
#elif IRQ_DMA_CHANNEL78_SR_CAT == IRQ_CAT2
ISR(DMACH78SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(78U);
}
#endif /* Channel 78 */
#endif
/******************************************************************************
** Syntax : void DMACH79SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel79 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL79_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL79_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL79_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL79_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL79_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH79SR_ISR, 0, IRQ_DMA_CHANNEL79_SR_PRIO)
#elif IRQ_DMA_CHANNEL79_SR_CAT == IRQ_CAT2
ISR(DMACH79SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(79U);
}
#endif /* Channel 79 */
#endif
/******************************************************************************
** Syntax : void DMACH80SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel80 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL80_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL80_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL80_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL80_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL80_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH80SR_ISR, 0, IRQ_DMA_CHANNEL80_SR_PRIO)
#elif IRQ_DMA_CHANNEL80_SR_CAT == IRQ_CAT2
ISR(DMACH80SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(80U);
}
#endif /* Channel 80 */
#endif
/******************************************************************************
** Syntax : void DMACH81SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel81 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL81_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL81_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL81_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL81_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL81_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH81SR_ISR, 0, IRQ_DMA_CHANNEL81_SR_PRIO)
#elif IRQ_DMA_CHANNEL81_SR_CAT == IRQ_CAT2
ISR(DMACH81SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(81U);
}
#endif /* Channel 81 */
#endif
/******************************************************************************
** Syntax : void DMACH82SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel82 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL82_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL82_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL82_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL82_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL82_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH82SR_ISR, 0, IRQ_DMA_CHANNEL82_SR_PRIO)
#elif IRQ_DMA_CHANNEL82_SR_CAT == IRQ_CAT2
ISR(DMACH82SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(82U);
}
#endif /* Channel 82 */
#endif
/******************************************************************************
** Syntax : void DMACH83SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel83 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL83_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL83_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL83_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL83_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL83_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH83SR_ISR, 0, IRQ_DMA_CHANNEL83_SR_PRIO)
#elif IRQ_DMA_CHANNEL83_SR_CAT == IRQ_CAT2
ISR(DMACH83SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(83U);
}
#endif /* Channel 83 */
#endif
/******************************************************************************
** Syntax : void DMACH84SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel84 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL84_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL84_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL84_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL84_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL84_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH84SR_ISR, 0, IRQ_DMA_CHANNEL84_SR_PRIO)
#elif IRQ_DMA_CHANNEL84_SR_CAT == IRQ_CAT2
ISR(DMACH84SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(84U);
}
#endif /* Channel 84 */
#endif
/******************************************************************************
** Syntax : void DMACH85SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel85 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL85_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL85_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL85_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL85_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL85_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH85SR_ISR, 0, IRQ_DMA_CHANNEL85_SR_PRIO)
#elif IRQ_DMA_CHANNEL85_SR_CAT == IRQ_CAT2
ISR(DMACH85SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(85U);
}
#endif /* Channel 85 */
#endif
/******************************************************************************
** Syntax : void DMACH86SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel86 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL86_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL86_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL86_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL86_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL86_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH86SR_ISR, 0, IRQ_DMA_CHANNEL86_SR_PRIO)
#elif IRQ_DMA_CHANNEL86_SR_CAT == IRQ_CAT2
ISR(DMACH86SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(86U);
}
#endif /* Channel 86 */
#endif
/******************************************************************************
** Syntax : void DMACH87SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel87 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL87_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL87_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL87_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL87_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL87_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH87SR_ISR, 0, IRQ_DMA_CHANNEL87_SR_PRIO)
#elif IRQ_DMA_CHANNEL87_SR_CAT == IRQ_CAT2
ISR(DMACH87SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(87U);
}
#endif /* Channel 87 */
#endif
/******************************************************************************
** Syntax : void DMACH88SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel88 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL88_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL88_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL88_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL88_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL88_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH88SR_ISR, 0, IRQ_DMA_CHANNEL88_SR_PRIO)
#elif IRQ_DMA_CHANNEL88_SR_CAT == IRQ_CAT2
ISR(DMACH88SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(88U);
}
#endif /* Channel 88 */
#endif
/******************************************************************************
** Syntax : void DMACH89SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel89 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL89_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL89_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL89_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL89_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL89_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH89SR_ISR, 0, IRQ_DMA_CHANNEL89_SR_PRIO)
#elif IRQ_DMA_CHANNEL89_SR_CAT == IRQ_CAT2
ISR(DMACH89SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(89U);
}
#endif /* Channel 89 */
#endif
/******************************************************************************
** Syntax : void DMACH90SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel90 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL90_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL90_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL90_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL90_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL90_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH90SR_ISR, 0, IRQ_DMA_CHANNEL90_SR_PRIO)
#elif IRQ_DMA_CHANNEL90_SR_CAT == IRQ_CAT2
ISR(DMACH90SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(90U);
}
#endif /* Channel 90 */
#endif
/******************************************************************************
** Syntax : void DMACH91SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel91 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL91_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL91_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL91_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL91_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL91_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH91SR_ISR, 0, IRQ_DMA_CHANNEL91_SR_PRIO)
#elif IRQ_DMA_CHANNEL91_SR_CAT == IRQ_CAT2
ISR(DMACH91SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(91U);
}
#endif /* Channel 91 */
#endif
/******************************************************************************
** Syntax : void DMACH92SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel92 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL92_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL92_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL92_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL92_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL92_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH92SR_ISR, 0, IRQ_DMA_CHANNEL92_SR_PRIO)
#elif IRQ_DMA_CHANNEL92_SR_CAT == IRQ_CAT2
ISR(DMACH92SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(92U);
}
#endif /* Channel 92 */
#endif
/******************************************************************************
** Syntax : void DMACH93SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel93 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL93_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL93_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL93_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL93_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL93_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH93SR_ISR, 0, IRQ_DMA_CHANNEL93_SR_PRIO)
#elif IRQ_DMA_CHANNEL93_SR_CAT == IRQ_CAT2
ISR(DMACH93SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(93U);
}
#endif /* Channel 93 */
#endif
/******************************************************************************
** Syntax : void DMACH94SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel94 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL94_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL94_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL94_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL94_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL94_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH94SR_ISR, 0, IRQ_DMA_CHANNEL94_SR_PRIO)
#elif IRQ_DMA_CHANNEL94_SR_CAT == IRQ_CAT2
ISR(DMACH94SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(94U);
}
#endif /* Channel 94 */
#endif
/******************************************************************************
** Syntax : void DMACH95SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel95 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL95_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL95_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL95_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL95_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL95_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH95SR_ISR, 0, IRQ_DMA_CHANNEL95_SR_PRIO)
#elif IRQ_DMA_CHANNEL95_SR_CAT == IRQ_CAT2
ISR(DMACH95SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(95U);
}
#endif /* Channel 95 */
#endif
/******************************************************************************
** Syntax : void DMACH96SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel96 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL96_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL96_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL96_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL96_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL96_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH96SR_ISR, 0, IRQ_DMA_CHANNEL96_SR_PRIO)
#elif IRQ_DMA_CHANNEL96_SR_CAT == IRQ_CAT2
ISR(DMACH96SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(96U);
}
#endif /* Channel 96 */
#endif
/******************************************************************************
** Syntax : void DMACH97SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel97 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL97_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL97_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL97_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL97_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL97_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH97SR_ISR, 0, IRQ_DMA_CHANNEL97_SR_PRIO)
#elif IRQ_DMA_CHANNEL97_SR_CAT == IRQ_CAT2
ISR(DMACH97SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(97U);
}
#endif /* Channel 97 */
#endif
/******************************************************************************
** Syntax : void DMACH98SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel98 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL98_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL98_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL98_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL98_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL98_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH98SR_ISR, 0, IRQ_DMA_CHANNEL98_SR_PRIO)
#elif IRQ_DMA_CHANNEL98_SR_CAT == IRQ_CAT2
ISR(DMACH98SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(98U);
}
#endif /* Channel 98 */
#endif
/******************************************************************************
** Syntax : void DMACH99SR_ISR(void)                                         **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel99 for service a node on Channel     **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL99_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL99_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL99_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL99_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL99_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH99SR_ISR, 0, IRQ_DMA_CHANNEL99_SR_PRIO)
#elif IRQ_DMA_CHANNEL99_SR_CAT == IRQ_CAT2
ISR(DMACH99SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(99U);
}
#endif /* Channel 99 */
#endif
/******************************************************************************
** Syntax : void DMACH100SR_ISR(void)                                        **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel100 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL100_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL100_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL100_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL100_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL100_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH100SR_ISR, 0, IRQ_DMA_CHANNEL100_SR_PRIO)
#elif IRQ_DMA_CHANNEL100_SR_CAT == IRQ_CAT2
ISR(DMACH100SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(100U);
}
#endif /* Channel 100 */
#endif
/******************************************************************************
** Syntax : void DMACH101SR_ISR(void)                                        **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel101 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL101_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL101_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL101_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL101_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL101_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH101SR_ISR, 0, IRQ_DMA_CHANNEL101_SR_PRIO)
#elif IRQ_DMA_CHANNEL101_SR_CAT == IRQ_CAT2
ISR(DMACH101SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(101U);
}
#endif /* Channel 101 */
#endif
/******************************************************************************
** Syntax : void DMACH102SR_ISR(void)                                        **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel102 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL102_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL102_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL102_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL102_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL102_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH102SR_ISR, 0, IRQ_DMA_CHANNEL102_SR_PRIO)
#elif IRQ_DMA_CHANNEL102_SR_CAT == IRQ_CAT2
ISR(DMACH102SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(102U);
}
#endif /* Channel 102 */
#endif
/******************************************************************************
** Syntax : void DMACH103SR_ISR(void)                                        **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel103 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL103_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL103_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL103_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL103_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL103_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH103SR_ISR, 0, IRQ_DMA_CHANNEL103_SR_PRIO)
#elif IRQ_DMA_CHANNEL103_SR_CAT == IRQ_CAT2
ISR(DMACH103SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(103U);
}
#endif /* Channel 103 */
#endif
/******************************************************************************
** Syntax : void DMACH104SR_ISR(void)                                        **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel104 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL104_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL104_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL104_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL104_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL104_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH104SR_ISR, 0, IRQ_DMA_CHANNEL104_SR_PRIO)
#elif IRQ_DMA_CHANNEL104_SR_CAT == IRQ_CAT2
ISR(DMACH104SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(104U);
}
#endif /* Channel 104 */
#endif
/******************************************************************************
** Syntax : void DMACH105SR_ISR(void)                                        **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel105 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL105_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL105_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL105_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL105_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL105_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH105SR_ISR, 0, IRQ_DMA_CHANNEL105_SR_PRIO)
#elif IRQ_DMA_CHANNEL105_SR_CAT == IRQ_CAT2
ISR(DMACH105SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(105U);
}
#endif /* Channel 105 */
#endif
/******************************************************************************
** Syntax : void DMACH106SR_ISR(void)                                        **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel106 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL106_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL106_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL106_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL106_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL106_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH106SR_ISR, 0, IRQ_DMA_CHANNEL106_SR_PRIO)
#elif IRQ_DMA_CHANNEL106_SR_CAT == IRQ_CAT2
ISR(DMACH106SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(106U);
}
#endif /* Channel 106 */
#endif
/******************************************************************************
** Syntax : void DMACH107SR_ISR(void)                                        **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel107 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL107_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL107_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL107_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL107_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL107_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH107SR_ISR, 0, IRQ_DMA_CHANNEL107_SR_PRIO)
#elif IRQ_DMA_CHANNEL107_SR_CAT == IRQ_CAT2
ISR(DMACH107SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(107U);
}
#endif /* Channel 107 */
#endif
/******************************************************************************
** Syntax : void DMACH108SR_ISR(void)                                        **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel108 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL108_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL108_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL108_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL108_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL108_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH108SR_ISR, 0, IRQ_DMA_CHANNEL108_SR_PRIO)
#elif IRQ_DMA_CHANNEL108_SR_CAT == IRQ_CAT2
ISR(DMACH108SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(108U);
}
#endif /* Channel 108 */
#endif
/******************************************************************************
** Syntax : void DMACH109SR_ISR(void)                                        **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel109 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL109_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL109_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL109_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL109_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL109_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH109SR_ISR, 0, IRQ_DMA_CHANNEL109_SR_PRIO)
#elif IRQ_DMA_CHANNEL109_SR_CAT == IRQ_CAT2
ISR(DMACH109SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(109U);
}
#endif /* Channel 109 */
#endif
/******************************************************************************
** Syntax : void DMACH110SR_ISR(void)                                        **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel110 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL110_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL110_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL110_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL110_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL110_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH110SR_ISR, 0, IRQ_DMA_CHANNEL110_SR_PRIO)
#elif IRQ_DMA_CHANNEL110_SR_CAT == IRQ_CAT2
ISR(DMACH110SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(110U);
}
#endif /* Channel 110 */
#endif
/******************************************************************************
** Syntax : void DMACH111SR_ISR(void)                                        **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel111 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL111_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL111_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL111_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL111_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL111_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH111SR_ISR, 0, IRQ_DMA_CHANNEL111_SR_PRIO)
#elif IRQ_DMA_CHANNEL111_SR_CAT == IRQ_CAT2
ISR(DMACH111SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(111U);
}
#endif /* Channel 111 */
#endif
/******************************************************************************
** Syntax : void DMACH112SR_ISR(void)                                        **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel112 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL112_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL112_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL112_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL112_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL112_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH112SR_ISR, 0, IRQ_DMA_CHANNEL112_SR_PRIO)
#elif IRQ_DMA_CHANNEL112_SR_CAT == IRQ_CAT2
ISR(DMACH112SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(112U);
}
#endif /* Channel 112 */
#endif
/******************************************************************************
** Syntax : void DMACH113SR_ISR(void)                                        **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel113 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL113_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL113_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL113_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL113_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL113_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH113SR_ISR, 0, IRQ_DMA_CHANNEL113_SR_PRIO)
#elif IRQ_DMA_CHANNEL113_SR_CAT == IRQ_CAT2
ISR(DMACH113SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(113U);
}
#endif /* Channel 113 */
#endif
/******************************************************************************
** Syntax : void DMACH114SR_ISR(void)                                        **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel114 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL114_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL114_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL114_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL114_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL114_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH114SR_ISR, 0, IRQ_DMA_CHANNEL114_SR_PRIO)
#elif IRQ_DMA_CHANNEL114_SR_CAT == IRQ_CAT2
ISR(DMACH114SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(114U);
}
#endif /* Channel 114 */
#endif
/******************************************************************************
** Syntax : void DMACH115SR_ISR(void)                                        **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel115 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL115_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL115_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL115_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL115_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL115_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH115SR_ISR, 0, IRQ_DMA_CHANNEL115_SR_PRIO)
#elif IRQ_DMA_CHANNEL115_SR_CAT == IRQ_CAT2
ISR(DMACH115SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(115U);
}
#endif /* Channel 115 */
#endif
/******************************************************************************
** Syntax : void DMACH116SR_ISR(void)                                        **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel116 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL116_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL116_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL116_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL116_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL116_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH116SR_ISR, 0, IRQ_DMA_CHANNEL116_SR_PRIO)
#elif IRQ_DMA_CHANNEL116_SR_CAT == IRQ_CAT2
ISR(DMACH116SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(116U);
}
#endif /* Channel 116 */
#endif
/******************************************************************************
** Syntax : void DMACH117SR_ISR(void)                                        **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel117 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL117_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL117_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL117_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL117_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL117_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH117SR_ISR, 0, IRQ_DMA_CHANNEL117_SR_PRIO)
#elif IRQ_DMA_CHANNEL117_SR_CAT == IRQ_CAT2
ISR(DMACH117SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(117U);
}
#endif /* Channel 117 */
#endif
/******************************************************************************
** Syntax : void DMACH118SR_ISR(void)                                        **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel118 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL118_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL118_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL118_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL118_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL118_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH118SR_ISR, 0, IRQ_DMA_CHANNEL118_SR_PRIO)
#elif IRQ_DMA_CHANNEL118_SR_CAT == IRQ_CAT2
ISR(DMACH118SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(118U);
}
#endif /* Channel 118 */
#endif
/******************************************************************************
** Syntax : void DMACH119SR_ISR(void)                                        **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel119 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL119_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL119_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL119_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL119_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL119_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH119SR_ISR, 0, IRQ_DMA_CHANNEL119_SR_PRIO)
#elif IRQ_DMA_CHANNEL119_SR_CAT == IRQ_CAT2
ISR(DMACH119SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(119U);
}
#endif /* Channel 119 */
#endif
/******************************************************************************
** Syntax : void DMACH120SR_ISR(void)                                        **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel120 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL120_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL120_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL120_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL120_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL120_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH120SR_ISR, 0, IRQ_DMA_CHANNEL120_SR_PRIO)
#elif IRQ_DMA_CHANNEL120_SR_CAT == IRQ_CAT2
ISR(DMACH120SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(120U);
}
#endif /* Channel 120 */
#endif
/******************************************************************************
** Syntax : void DMACH121SR_ISR(void)                                        **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel121 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL121_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL121_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL121_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL121_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL121_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH121SR_ISR, 0, IRQ_DMA_CHANNEL121_SR_PRIO)
#elif IRQ_DMA_CHANNEL121_SR_CAT == IRQ_CAT2
ISR(DMACH121SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(121U);
}
#endif /* Channel 121 */
#endif
/******************************************************************************
** Syntax : void DMACH122SR_ISR(void)                                        **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel122 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL122_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL122_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL122_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL122_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL122_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH122SR_ISR, 0, IRQ_DMA_CHANNEL122_SR_PRIO)
#elif IRQ_DMA_CHANNEL122_SR_CAT == IRQ_CAT2
ISR(DMACH122SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(122U);
}
#endif /* Channel 122 */
#endif
/******************************************************************************
** Syntax : void DMACH123SR_ISR(void)                                        **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel123 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL123_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL123_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL123_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL123_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL123_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH123SR_ISR, 0, IRQ_DMA_CHANNEL123_SR_PRIO)
#elif IRQ_DMA_CHANNEL123_SR_CAT == IRQ_CAT2
ISR(DMACH123SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(123U);
}
#endif /* Channel 123 */
#endif
/******************************************************************************
** Syntax : void DMACH124SR_ISR(void)                                        **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel124 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL124_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL124_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL124_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL124_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL124_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH124SR_ISR, 0, IRQ_DMA_CHANNEL124_SR_PRIO)
#elif IRQ_DMA_CHANNEL124_SR_CAT == IRQ_CAT2
ISR(DMACH124SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(124U);
}
#endif /* Channel 124 */
#endif
/******************************************************************************
** Syntax : void DMACH125SR_ISR(void)                                        **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel125 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL125_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL125_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL125_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL125_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL125_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH125SR_ISR, 0, IRQ_DMA_CHANNEL125_SR_PRIO)
#elif IRQ_DMA_CHANNEL125_SR_CAT == IRQ_CAT2
ISR(DMACH125SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(125U);
}
#endif /* Channel 125 */
#endif
/******************************************************************************
** Syntax : void DMACH126SR_ISR(void)                                        **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel126 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL126_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL126_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL126_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL126_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL126_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH126SR_ISR, 0, IRQ_DMA_CHANNEL126_SR_PRIO)
#elif IRQ_DMA_CHANNEL126_SR_CAT == IRQ_CAT2
ISR(DMACH126SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(126U);
}
#endif /* Channel 126 */
#endif
/******************************************************************************
** Syntax : void DMACH127SR_ISR(void)                                        **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA Channel127 for service a node on Channel    **
**               interrupt,Transaction lost Transmit interrupt, Move engine  **
**               interrupts,Wrap buffer interrupts                           **
**                                                                           **
******************************************************************************/
#if IRQ_DMA_CHANNEL127_SR_TOS != IRQ_TOS_DMA
#if((IRQ_DMA_CHANNEL127_SR_PRIO > 0U) || (IRQ_DMA_CHANNEL127_SR_CAT == IRQ_CAT2))
#if((IRQ_DMA_CHANNEL127_SR_PRIO > 0U) && (IRQ_DMA_CHANNEL127_SR_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMACH127SR_ISR, 0, IRQ_DMA_CHANNEL127_SR_PRIO)
#elif IRQ_DMA_CHANNEL127_SR_CAT == IRQ_CAT2
ISR(DMACH127SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_ChInterruptHandler(127U);
}
#endif /* Channel 127 */
#endif

/******************************************************************************
** Syntax : void DMAGPSR00SR_ISR(void)                                       **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for DMA error interrupts which can be due to Source **
**               ,destination, TCS, RAM or safelinked list checksum error    **
**               through GPSR00                                              **
******************************************************************************/
#if IRQ_GPSRGROUP0_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_GPSRGROUP0_SR0_PRIO > 0U) || (IRQ_GPSRGROUP0_SR0_CAT == IRQ_CAT2))
#if((IRQ_GPSRGROUP0_SR0_PRIO > 0U) && (IRQ_GPSRGROUP0_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMAGPSR00SR_ISR, 0, IRQ_GPSRGROUP0_SR0_PRIO)
#elif IRQ_GPSRGROUP0_SR0_CAT == IRQ_CAT2
ISR(DMAGPSR00SR_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#if (TEST_ACCESS_MODE_RT  == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
#endif
#endif
#endif

  Dma_MEInterruptDispatcher();
}
#endif
#endif
