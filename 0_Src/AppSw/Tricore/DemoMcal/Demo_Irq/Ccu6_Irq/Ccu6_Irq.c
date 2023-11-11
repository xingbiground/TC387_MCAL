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
**  FILENAME     : Ccu6_Irq.c                                                 **
**                                                                            **
**  VERSION      : 2.0.0                                                      **
**                                                                            **
**  DATE         : 2021-11-08                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : This file contains the interrupt frames for the CCU6.      **
**                                                                            **
**  SPECIFICATION(S) : Specification of Icu Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* MCAL header file containing global macros, type definitions and functions
  needed by all MCAL drivers. */
#include "MCAL_Compiler.h"
#include "McalLib.h"
/*#include "IfxCpu_Intrinsics.h"*/
#include "IfxCcu6_reg.h"
/* Include MCU TIMERIP header file */
/* #include "Mcu_17_TimerIp.h"
   #include "IFX_Os.h"*/

#ifdef  APP_SW
#if(APP_SW == TEST_APP)
#include "Test_Main.h"
#endif
#endif

/* MCAL driver utility functions for setting interrupt priority initialization
  and interrupt category */
#include "IFX_Os.h"
#include "Irq.h"
#include "Mcu_17_TimerIp.h"

/*******************************************************************************
**                      Imported Compiler Switch Checks                       **
*******************************************************************************/

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
#define CCU6_KERNEL_0  0U
#define CCU6_KERNEL_1  1U
#define CCU6_KERNEL_2  2U
#define CCU6_KERNEL_3  2U

#define CCU6_CHANNEL_0  0U
#define CCU6_CHANNEL_1  1U
#define CCU6_CHANNEL_2  2U
#define CCU6_CHANNEL_3  3U
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

/*******************************************************************************
** Syntax:           void CCU60_ISR_SRN00(void)                               **
**                                                                            **
** Service ID:       NA                                                       **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant                                                **
**                                                                            **
** Parameters (in):  none                                                     **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
** Description :     This is Interrput Service request nodes 0 for the  CCU60.**
*******************************************************************************/
#if IRQ_CCU60_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_CCU60_SR0_PRIO > 0) || (IRQ_CCU60_SR0_CAT == IRQ_CAT2))
#if((IRQ_CCU60_SR0_PRIO > 0) && (IRQ_CCU60_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(CCU60SR0_ISR, 0, IRQ_CCU60_SR0_PRIO)
#elif IRQ_CCU60_SR0_CAT == IRQ_CAT2
ISR(CCU60SR0_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* Mcal_EnableAllInterrupts(); */
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
  #if (TEST_ACCESS_MODE_RT == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  Mcu_17_Ccu6_ChannelIsr(CCU6_KERNEL_0, CCU6_CHANNEL_0);

}

#endif
#endif

#if IRQ_CCU60_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_CCU60_SR1_PRIO > 0) || (IRQ_CCU60_SR1_CAT == IRQ_CAT2))
#if((IRQ_CCU60_SR1_PRIO > 0) && (IRQ_CCU60_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(CCU60SR1_ISR, 0, IRQ_CCU60_SR1_PRIO)
#elif IRQ_CCU60_SR1_CAT == IRQ_CAT2
ISR(CCU60SR1_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* Mcal_EnableAllInterrupts(); */
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
  #if (TEST_ACCESS_MODE_RT == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  Mcu_17_Ccu6_ChannelIsr(CCU6_KERNEL_0, CCU6_CHANNEL_1);

}

#endif
#endif

#if IRQ_CCU60_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_CCU60_SR2_PRIO > 0) || (IRQ_CCU60_SR2_CAT == IRQ_CAT2))
#if((IRQ_CCU60_SR2_PRIO > 0) && (IRQ_CCU60_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(CCU60SR2_ISR, 0, IRQ_CCU60_SR2_PRIO)
#elif IRQ_CCU60_SR2_CAT == IRQ_CAT2
ISR(CCU60SR2_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* Mcal_EnableAllInterrupts(); */
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
  #if (TEST_ACCESS_MODE_RT == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  Mcu_17_Ccu6_ChannelIsr(CCU6_KERNEL_0, CCU6_CHANNEL_2);

}

#endif
#endif

#if IRQ_CCU60_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_CCU60_SR3_PRIO > 0) || (IRQ_CCU60_SR3_CAT == IRQ_CAT2))
#if((IRQ_CCU60_SR3_PRIO > 0) && (IRQ_CCU60_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(CCU60SR3_ISR, 0, IRQ_CCU60_SR3_PRIO)
#elif IRQ_CCU60_SR3_CAT == IRQ_CAT2
ISR(CCU60SR3_ISR)
#endif
{
  /* Enable Global Interrupts */
  /* Mcal_EnableAllInterrupts(); */
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
  #if (TEST_ACCESS_MODE_RT == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  Mcu_17_Ccu6_ChannelIsr(CCU6_KERNEL_0, CCU6_CHANNEL_3);

}

#endif
#endif

/*******************************************************************************
** Syntax:           void CCU61_ISR_SRN00(void)                               **
**                                                                            **
** Service ID:       NA                                                       **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant                                                **
**                                                                            **
** Parameters (in):  none                                                     **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
** Description :     This is Interrput Service request nodes 0 for the  CCU61.**
*******************************************************************************/
#if IRQ_CCU61_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_CCU61_SR0_PRIO > 0) || (IRQ_CCU61_SR0_CAT == IRQ_CAT2))
#if((IRQ_CCU61_SR0_PRIO > 0) && (IRQ_CCU61_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(CCU61SR0_ISR, 0, IRQ_CCU61_SR0_PRIO)
#elif IRQ_CCU61_SR0_CAT == IRQ_CAT2
ISR(CCU61SR0_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
  #if (TEST_ACCESS_MODE_RT == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  Mcu_17_Ccu6_ChannelIsr(CCU6_KERNEL_1, CCU6_CHANNEL_0);
}
#endif
#endif

#if IRQ_CCU61_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_CCU61_SR1_PRIO > 0) || (IRQ_CCU61_SR1_CAT == IRQ_CAT2))
#if((IRQ_CCU61_SR1_PRIO > 0) && (IRQ_CCU61_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(CCU61SR1_ISR, 0, IRQ_CCU61_SR1_PRIO)
#elif IRQ_CCU61_SR1_CAT == IRQ_CAT2
ISR(CCU61SR1_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
  #if (TEST_ACCESS_MODE_RT == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  Mcu_17_Ccu6_ChannelIsr(CCU6_KERNEL_1, CCU6_CHANNEL_1);
}
#endif
#endif

#if IRQ_CCU61_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_CCU61_SR2_PRIO > 0) || (IRQ_CCU61_SR2_CAT == IRQ_CAT2))
#if((IRQ_CCU61_SR2_PRIO > 0) && (IRQ_CCU61_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(CCU61SR2_ISR, 0, IRQ_CCU61_SR2_PRIO)
#elif IRQ_CCU61_SR2_CAT == IRQ_CAT2
ISR(CCU61SR2_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
  #if (TEST_ACCESS_MODE_RT == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  Mcu_17_Ccu6_ChannelIsr(CCU6_KERNEL_1, CCU6_CHANNEL_2);
}
#endif
#endif

#if IRQ_CCU61_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_CCU61_SR3_PRIO > 0) || (IRQ_CCU61_SR3_CAT == IRQ_CAT2))
#if((IRQ_CCU61_SR3_PRIO > 0) && (IRQ_CCU61_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(CCU61SR3_ISR, 0, IRQ_CCU61_SR3_PRIO)
#elif IRQ_CCU61_SR3_CAT == IRQ_CAT2
ISR(CCU61SR3_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
  #if (TEST_ACCESS_MODE_RT == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  Mcu_17_Ccu6_ChannelIsr(CCU6_KERNEL_1, CCU6_CHANNEL_3);
}
#endif
#endif
