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
**  FILENAME     : Gtm_Irq.c                                                  **
**                                                                            **
**  VERSION      : 3.0.0                                                      **
**                                                                            **
**  DATE         : 2021-11-09                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : This file contains the interrupt frames for the Gtm.       **
**                                                                            **
**  SPECIFICATION(S) : Specification of Icu Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
/* Include GTM header file */
#include "Mcu_17_TimerIp.h"
/*Include Irq Module*/
#include "Irq.h"
#include "IFX_Os.h"
#ifdef  APP_SW
#if(APP_SW == TEST_APP)
  #include "Test_Main.h"
#endif
#endif
/*If Test module is gpt/pwm*/
#ifdef  APP_SW
#if((defined BASE_TEST_MODULE_ID) && ((BASE_TEST_MODULE_ID == 121) || (BASE_TEST_MODULE_ID == 100) || (BASE_TEST_MODULE_ID == 122) || (BASE_TEST_MODULE_ID == 125)) &&\
     (APP_SW == TEST_APP))
#include "Test_Time.h"
void Timer_DelayMs(uint32 ReqTimeMs);
void Timer_DelayTicks(uint32 ReqTimeTicks);
extern volatile uint8 u8g_Resilience_Delay_En;
#endif
#endif
#if (IRQ_GTM_EXIST == (STD_ON))
/******************************************************************************
** Syntax : void GTM_ISR_<MOD>[x]_SRy(void)                                  **
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
** Description : Service for GTM Service request for Sub Modules             **
**                                                                           **
******************************************************************************/

#if(IRQ_GTM_TOM0_EXIST == (STD_ON))
#if IRQ_GTM_TOM0_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM0_SR0_PRIO > 0) || (IRQ_GTM_TOM0_SR0_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM0_SR0_PRIO > 0) && (IRQ_GTM_TOM0_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM0SR0_ISR, 0, IRQ_GTM_TOM0_SR0_PRIO)
#elif IRQ_GTM_TOM0_SR0_CAT == IRQ_CAT2
ISR(GTMTOM0SR0_ISR)
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

  /*If Test module is gpt/pwm*/
  /*This piece of code introduces delay in isr for checking resilience
  against interrupt latency*/
  #ifdef  APP_SW
  #if(((defined BASE_TEST_MODULE_ID) && ((BASE_TEST_MODULE_ID == 121) || (BASE_TEST_MODULE_ID == 100))) &&\
      (APP_SW == TEST_APP))
  if(u8g_Resilience_Delay_En == 1)
  {
    Timer_DelayMs(1);
    u8g_Resilience_Delay_En = 0;
  }
  #endif
  #endif
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(0, 0);
}
#endif
#endif

#if IRQ_GTM_TOM0_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM0_SR1_PRIO > 0) || (IRQ_GTM_TOM0_SR1_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM0_SR1_PRIO > 0) && (IRQ_GTM_TOM0_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM0SR1_ISR, 0, IRQ_GTM_TOM0_SR1_PRIO)
#elif IRQ_GTM_TOM0_SR1_CAT == IRQ_CAT2
ISR(GTMTOM0SR1_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(0, 2);
}
#endif
#endif


#if IRQ_GTM_TOM0_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM0_SR2_PRIO > 0) || (IRQ_GTM_TOM0_SR2_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM0_SR2_PRIO > 0) && (IRQ_GTM_TOM0_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM0SR2_ISR, 0, IRQ_GTM_TOM0_SR2_PRIO)
#elif IRQ_GTM_TOM0_SR2_CAT == IRQ_CAT2
ISR(GTMTOM0SR2_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(0, 4);
}
#endif
#endif

#if IRQ_GTM_TOM0_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM0_SR3_PRIO > 0) || (IRQ_GTM_TOM0_SR3_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM0_SR3_PRIO > 0) && (IRQ_GTM_TOM0_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM0SR3_ISR, 0, IRQ_GTM_TOM0_SR3_PRIO)
#elif IRQ_GTM_TOM0_SR3_CAT == IRQ_CAT2
ISR(GTMTOM0SR3_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(0, 6);
}
#endif
#endif

#if IRQ_GTM_TOM0_SR4_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM0_SR4_PRIO > 0) || (IRQ_GTM_TOM0_SR4_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM0_SR4_PRIO > 0) && (IRQ_GTM_TOM0_SR4_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM0SR4_ISR, 0, IRQ_GTM_TOM0_SR4_PRIO)
#elif IRQ_GTM_TOM0_SR4_CAT == IRQ_CAT2
ISR(GTMTOM0SR4_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(0, 8);
}
#endif
#endif

#if IRQ_GTM_TOM0_SR5_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM0_SR5_PRIO > 0) || (IRQ_GTM_TOM0_SR5_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM0_SR5_PRIO > 0) && (IRQ_GTM_TOM0_SR5_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM0SR5_ISR, 0, IRQ_GTM_TOM0_SR5_PRIO)
#elif IRQ_GTM_TOM0_SR5_CAT == IRQ_CAT2
ISR(GTMTOM0SR5_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(0, 10);
}
#endif
#endif

#if IRQ_GTM_TOM0_SR6_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM0_SR6_PRIO > 0) || (IRQ_GTM_TOM0_SR6_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM0_SR6_PRIO > 0) && (IRQ_GTM_TOM0_SR6_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM0SR6_ISR, 0, IRQ_GTM_TOM0_SR6_PRIO)
#elif IRQ_GTM_TOM0_SR6_CAT == IRQ_CAT2
ISR(GTMTOM0SR6_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(0, 12);
}
#endif
#endif

#if IRQ_GTM_TOM0_SR7_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM0_SR7_PRIO > 0) || (IRQ_GTM_TOM0_SR7_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM0_SR7_PRIO > 0) && (IRQ_GTM_TOM0_SR7_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM0SR7_ISR, 0, IRQ_GTM_TOM0_SR7_PRIO)
#elif IRQ_GTM_TOM0_SR7_CAT == IRQ_CAT2
ISR(GTMTOM0SR7_ISR)
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

  /* Specific amount of Delay is provided to perform Resilience test based on the resilience flag selection */
  #ifdef  APP_SW
  #if((defined BASE_TEST_MODULE_ID) && ((BASE_TEST_MODULE_ID == 125) && (APP_SW == TEST_APP)))
    if(u8g_Resilience_Delay_En == 1)
    {
        Timer_DelayTicks(1000);
        u8g_Resilience_Delay_En = 0;
    }
    else if(u8g_Resilience_Delay_En == 2)
    {
        Timer_DelayTicks(5000);
        u8g_Resilience_Delay_En = 0;
    }
    else if(u8g_Resilience_Delay_En == 3)
    {
        Timer_DelayTicks(10000);
        u8g_Resilience_Delay_En = 0;
    }
    else
    {
        u8g_Resilience_Delay_En = 0;
    }
  #endif
  #endif

  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(0, 14);
}
#endif
#endif

#endif /* #if(IRQ_GTM_TOM0_EXIST == (STD_ON)) */

#if(IRQ_GTM_TOM1_EXIST == (STD_ON))

#if IRQ_GTM_TOM1_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM1_SR0_PRIO > 0) || (IRQ_GTM_TOM1_SR0_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM1_SR0_PRIO > 0) && (IRQ_GTM_TOM1_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM1SR0_ISR, 0, IRQ_GTM_TOM1_SR0_PRIO)
#elif IRQ_GTM_TOM1_SR0_CAT == IRQ_CAT2
ISR(GTMTOM1SR0_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(1, 0);
}
#endif
#endif

#if IRQ_GTM_TOM1_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM1_SR1_PRIO > 0) || (IRQ_GTM_TOM1_SR1_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM1_SR1_PRIO > 0) && (IRQ_GTM_TOM1_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM1SR1_ISR, 0, IRQ_GTM_TOM1_SR1_PRIO)
#elif IRQ_GTM_TOM1_SR1_CAT == IRQ_CAT2
ISR(GTMTOM1SR1_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(1, 2);
}
#endif
#endif

#if IRQ_GTM_TOM1_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM1_SR2_PRIO > 0) || (IRQ_GTM_TOM1_SR2_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM1_SR2_PRIO > 0) && (IRQ_GTM_TOM1_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM1SR2_ISR, 0, IRQ_GTM_TOM1_SR2_PRIO)
#elif IRQ_GTM_TOM1_SR2_CAT == IRQ_CAT2
ISR(GTMTOM1SR2_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(1, 4);
}
#endif
#endif

#if IRQ_GTM_TOM1_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM1_SR3_PRIO > 0) || (IRQ_GTM_TOM1_SR3_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM1_SR3_PRIO > 0) && (IRQ_GTM_TOM1_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM1SR3_ISR, 0, IRQ_GTM_TOM1_SR3_PRIO)
#elif IRQ_GTM_TOM1_SR3_CAT == IRQ_CAT2
ISR(GTMTOM1SR3_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(1, 6);
}
#endif
#endif

#if IRQ_GTM_TOM1_SR4_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM1_SR4_PRIO > 0) || (IRQ_GTM_TOM1_SR4_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM1_SR4_PRIO > 0) && (IRQ_GTM_TOM1_SR4_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM1SR4_ISR, 0, IRQ_GTM_TOM1_SR4_PRIO)
#elif IRQ_GTM_TOM1_SR4_CAT == IRQ_CAT2
ISR(GTMTOM1SR4_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(1, 8);
}
#endif
#endif

#if IRQ_GTM_TOM1_SR5_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM1_SR5_PRIO > 0) || (IRQ_GTM_TOM1_SR5_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM1_SR5_PRIO > 0) && (IRQ_GTM_TOM1_SR5_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM1SR5_ISR, 0, IRQ_GTM_TOM1_SR5_PRIO)
#elif IRQ_GTM_TOM1_SR5_CAT == IRQ_CAT2
ISR(GTMTOM1SR5_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(1, 10);
}
#endif
#endif

#if IRQ_GTM_TOM1_SR6_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM1_SR6_PRIO > 0) || (IRQ_GTM_TOM1_SR6_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM1_SR6_PRIO > 0) && (IRQ_GTM_TOM1_SR6_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM1SR6_ISR, 0, IRQ_GTM_TOM1_SR6_PRIO)
#elif IRQ_GTM_TOM1_SR6_CAT == IRQ_CAT2
ISR(GTMTOM1SR6_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(1, 12);
}
#endif
#endif

#if IRQ_GTM_TOM1_SR7_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM1_SR7_PRIO > 0) || (IRQ_GTM_TOM1_SR7_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM1_SR7_PRIO > 0) && (IRQ_GTM_TOM1_SR7_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM1SR7_ISR, 0, IRQ_GTM_TOM1_SR7_PRIO)
#elif IRQ_GTM_TOM1_SR7_CAT == IRQ_CAT2
ISR(GTMTOM1SR7_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(1, 14);
}
#endif
#endif

#endif /* #if(IRQ_GTM_TOM1_EXIST == (STD_ON)) */

#if(IRQ_GTM_TOM2_EXIST == (STD_ON))

#if IRQ_GTM_TOM2_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM2_SR0_PRIO > 0) || (IRQ_GTM_TOM2_SR0_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM2_SR0_PRIO > 0) && (IRQ_GTM_TOM2_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM2SR0_ISR, 0, IRQ_GTM_TOM2_SR0_PRIO)
#elif IRQ_GTM_TOM2_SR0_CAT == IRQ_CAT2
ISR(GTMTOM2SR0_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(2, 0);
}
#endif
#endif

#if IRQ_GTM_TOM2_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM2_SR1_PRIO > 0) || (IRQ_GTM_TOM2_SR1_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM2_SR1_PRIO > 0) && (IRQ_GTM_TOM2_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM2SR1_ISR, 0, IRQ_GTM_TOM2_SR1_PRIO)
#elif IRQ_GTM_TOM2_SR1_CAT == IRQ_CAT2
ISR(GTMTOM2SR1_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(2, 2);
}
#endif
#endif

#if IRQ_GTM_TOM2_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM2_SR2_PRIO > 0) || (IRQ_GTM_TOM2_SR2_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM2_SR2_PRIO > 0) && (IRQ_GTM_TOM2_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM2SR2_ISR, 0, IRQ_GTM_TOM2_SR2_PRIO)
#elif IRQ_GTM_TOM2_SR2_CAT == IRQ_CAT2
ISR(GTMTOM2SR2_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(2, 4);
}
#endif
#endif

#if IRQ_GTM_TOM2_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM2_SR3_PRIO > 0) || (IRQ_GTM_TOM2_SR3_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM2_SR3_PRIO > 0) && (IRQ_GTM_TOM2_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM2SR3_ISR, 0, IRQ_GTM_TOM2_SR3_PRIO)
#elif IRQ_GTM_TOM2_SR3_CAT == IRQ_CAT2
ISR(GTMTOM2SR3_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(2, 6);
}
#endif
#endif

#if IRQ_GTM_TOM2_SR4_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM2_SR4_PRIO > 0) || (IRQ_GTM_TOM2_SR4_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM2_SR4_PRIO > 0) && (IRQ_GTM_TOM2_SR4_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM2SR4_ISR, 0, IRQ_GTM_TOM2_SR4_PRIO)
#elif IRQ_GTM_TOM2_SR4_CAT == IRQ_CAT2
ISR(GTMTOM2SR4_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(2, 8);
}
#endif
#endif

#if IRQ_GTM_TOM2_SR5_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM2_SR5_PRIO > 0) || (IRQ_GTM_TOM2_SR5_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM2_SR5_PRIO > 0) && (IRQ_GTM_TOM2_SR5_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM2SR5_ISR, 0, IRQ_GTM_TOM2_SR5_PRIO)
#elif IRQ_GTM_TOM2_SR5_CAT == IRQ_CAT2
ISR(GTMTOM2SR5_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(2, 10);
}
#endif
#endif

#if IRQ_GTM_TOM2_SR6_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM2_SR6_PRIO > 0) || (IRQ_GTM_TOM2_SR6_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM2_SR6_PRIO > 0) && (IRQ_GTM_TOM2_SR6_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM2SR6_ISR, 0, IRQ_GTM_TOM2_SR6_PRIO)
#elif IRQ_GTM_TOM2_SR6_CAT == IRQ_CAT2
ISR(GTMTOM2SR6_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(2, 12);
}
#endif
#endif

#if IRQ_GTM_TOM2_SR7_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM2_SR7_PRIO > 0) || (IRQ_GTM_TOM2_SR7_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM2_SR7_PRIO > 0) && (IRQ_GTM_TOM2_SR7_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM2SR7_ISR, 0, IRQ_GTM_TOM2_SR7_PRIO)
#elif IRQ_GTM_TOM2_SR7_CAT == IRQ_CAT2
ISR(GTMTOM2SR7_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(2, 14);
}
#endif
#endif

#endif /* #if(IRQ_GTM_TOM2_EXIST == (STD_ON)) */

#if(IRQ_GTM_TOM3_EXIST == (STD_ON))

#if IRQ_GTM_TOM3_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM3_SR0_PRIO > 0) || (IRQ_GTM_TOM3_SR0_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM3_SR0_PRIO > 0) && (IRQ_GTM_TOM3_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM3SR0_ISR, 0, IRQ_GTM_TOM3_SR0_PRIO)
#elif IRQ_GTM_TOM3_SR0_CAT == IRQ_CAT2
ISR(GTMTOM3SR0_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(3, 0);
}
#endif
#endif

#if IRQ_GTM_TOM3_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM3_SR1_PRIO > 0) || (IRQ_GTM_TOM3_SR1_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM3_SR1_PRIO > 0) && (IRQ_GTM_TOM3_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM3SR1_ISR, 0, IRQ_GTM_TOM3_SR1_PRIO)
#elif IRQ_GTM_TOM3_SR1_CAT == IRQ_CAT2
ISR(GTMTOM3SR1_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(3, 2);
}
#endif
#endif

#if IRQ_GTM_TOM3_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM3_SR2_PRIO > 0) || (IRQ_GTM_TOM3_SR2_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM3_SR2_PRIO > 0) && (IRQ_GTM_TOM3_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM3SR2_ISR, 0, IRQ_GTM_TOM3_SR2_PRIO)
#elif IRQ_GTM_TOM3_SR2_CAT == IRQ_CAT2
ISR(GTMTOM3SR2_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(3, 4);
}
#endif
#endif

#if IRQ_GTM_TOM3_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM3_SR3_PRIO > 0) || (IRQ_GTM_TOM3_SR3_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM3_SR3_PRIO > 0) && (IRQ_GTM_TOM3_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM3SR3_ISR, 0, IRQ_GTM_TOM3_SR3_PRIO)
#elif IRQ_GTM_TOM3_SR3_CAT == IRQ_CAT2
ISR(GTMTOM3SR3_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(3, 6);
}
#endif
#endif

#if IRQ_GTM_TOM3_SR4_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM3_SR4_PRIO > 0) || (IRQ_GTM_TOM3_SR4_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM3_SR4_PRIO > 0) && (IRQ_GTM_TOM3_SR4_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM3SR4_ISR, 0, IRQ_GTM_TOM3_SR4_PRIO)
#elif IRQ_GTM_TOM3_SR4_CAT == IRQ_CAT2
ISR(GTMTOM3SR4_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(3, 8);
}
#endif
#endif

#if IRQ_GTM_TOM3_SR5_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM3_SR5_PRIO > 0) || (IRQ_GTM_TOM3_SR5_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM3_SR5_PRIO > 0) && (IRQ_GTM_TOM3_SR5_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM3SR5_ISR, 0, IRQ_GTM_TOM3_SR5_PRIO)
#elif IRQ_GTM_TOM3_SR5_CAT == IRQ_CAT2
ISR(GTMTOM3SR5_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(3, 10);
}
#endif
#endif

#if IRQ_GTM_TOM3_SR6_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM3_SR6_PRIO > 0) || (IRQ_GTM_TOM3_SR6_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM3_SR6_PRIO > 0) && (IRQ_GTM_TOM3_SR6_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM3SR6_ISR, 0, IRQ_GTM_TOM3_SR6_PRIO)
#elif IRQ_GTM_TOM3_SR6_CAT == IRQ_CAT2
ISR(GTMTOM3SR6_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(3, 12);
}
#endif
#endif

#if IRQ_GTM_TOM3_SR7_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM3_SR7_PRIO > 0) || (IRQ_GTM_TOM3_SR7_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM3_SR7_PRIO > 0) && (IRQ_GTM_TOM3_SR7_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM3SR7_ISR, 0, IRQ_GTM_TOM3_SR7_PRIO)
#elif IRQ_GTM_TOM3_SR7_CAT == IRQ_CAT2
ISR(GTMTOM3SR7_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(3, 14);
}
#endif
#endif

#endif /* #if(IRQ_GTM_TOM3_EXIST == (STD_ON)) */

#if(IRQ_GTM_TOM4_EXIST == (STD_ON))

#if IRQ_GTM_TOM4_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM4_SR0_PRIO > 0) || (IRQ_GTM_TOM4_SR0_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM4_SR0_PRIO > 0) && (IRQ_GTM_TOM4_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM4SR0_ISR, 0, IRQ_GTM_TOM4_SR0_PRIO)
#elif IRQ_GTM_TOM4_SR0_CAT == IRQ_CAT2
ISR(GTMTOM4SR0_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(4, 0);
}
#endif
#endif

#if IRQ_GTM_TOM4_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM4_SR1_PRIO > 0) || (IRQ_GTM_TOM4_SR1_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM4_SR1_PRIO > 0) && (IRQ_GTM_TOM4_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM4SR1_ISR, 0, IRQ_GTM_TOM4_SR1_PRIO)
#elif IRQ_GTM_TOM4_SR1_CAT == IRQ_CAT2
ISR(GTMTOM4SR1_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(4, 2);
}
#endif
#endif

#if IRQ_GTM_TOM4_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM4_SR2_PRIO > 0) || (IRQ_GTM_TOM4_SR2_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM4_SR2_PRIO > 0) && (IRQ_GTM_TOM4_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM4SR2_ISR, 0, IRQ_GTM_TOM4_SR2_PRIO)
#elif IRQ_GTM_TOM4_SR2_CAT == IRQ_CAT2
ISR(GTMTOM4SR2_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(4, 4);
}
#endif
#endif

#if IRQ_GTM_TOM4_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM4_SR3_PRIO > 0) || (IRQ_GTM_TOM4_SR3_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM4_SR3_PRIO > 0) && (IRQ_GTM_TOM4_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM4SR3_ISR, 0, IRQ_GTM_TOM4_SR3_PRIO)
#elif IRQ_GTM_TOM4_SR3_CAT == IRQ_CAT2
ISR(GTMTOM4SR3_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(4, 6);
}
#endif
#endif

#if IRQ_GTM_TOM4_SR4_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM4_SR4_PRIO > 0) || (IRQ_GTM_TOM4_SR4_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM4_SR4_PRIO > 0) && (IRQ_GTM_TOM4_SR4_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM4SR4_ISR, 0, IRQ_GTM_TOM4_SR4_PRIO)
#elif IRQ_GTM_TOM4_SR4_CAT == IRQ_CAT2
ISR(GTMTOM4SR4_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(4, 8);
}
#endif
#endif

#if IRQ_GTM_TOM4_SR5_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM4_SR5_PRIO > 0) || (IRQ_GTM_TOM4_SR5_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM4_SR5_PRIO > 0) && (IRQ_GTM_TOM4_SR5_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM4SR5_ISR, 0, IRQ_GTM_TOM4_SR5_PRIO)
#elif IRQ_GTM_TOM4_SR5_CAT == IRQ_CAT2
ISR(GTMTOM4SR5_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(4, 10);
}
#endif
#endif

#if IRQ_GTM_TOM4_SR6_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM4_SR6_PRIO > 0) || (IRQ_GTM_TOM4_SR6_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM4_SR6_PRIO > 0) && (IRQ_GTM_TOM4_SR6_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM4SR6_ISR, 0, IRQ_GTM_TOM4_SR6_PRIO)
#elif IRQ_GTM_TOM4_SR6_CAT == IRQ_CAT2
ISR(GTMTOM4SR6_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(4, 12);
}
#endif
#endif

#if IRQ_GTM_TOM4_SR7_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM4_SR7_PRIO > 0) || (IRQ_GTM_TOM4_SR7_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM4_SR7_PRIO > 0) && (IRQ_GTM_TOM4_SR7_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM4SR7_ISR, 0, IRQ_GTM_TOM4_SR7_PRIO)
#elif IRQ_GTM_TOM4_SR7_CAT == IRQ_CAT2
ISR(GTMTOM4SR7_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(4, 14);
}
#endif
#endif

#endif /* #if(IRQ_GTM_TOM4_EXIST == (STD_ON)) */

#if(IRQ_GTM_TOM5_EXIST == (STD_ON))

#if IRQ_GTM_TOM5_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM5_SR0_PRIO > 0) || (IRQ_GTM_TOM5_SR0_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM5_SR0_PRIO > 0) && (IRQ_GTM_TOM5_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM5SR0_ISR, 0, IRQ_GTM_TOM5_SR0_PRIO)
#elif IRQ_GTM_TOM5_SR0_CAT == IRQ_CAT2
ISR(GTMTOM5SR0_ISR)
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

  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(5, 0);
}
#endif
#endif

#if IRQ_GTM_TOM5_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM5_SR1_PRIO > 0) || (IRQ_GTM_TOM5_SR1_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM5_SR1_PRIO > 0) && (IRQ_GTM_TOM5_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM5SR1_ISR, 0, IRQ_GTM_TOM5_SR1_PRIO)
#elif IRQ_GTM_TOM5_SR1_CAT == IRQ_CAT2
ISR(GTMTOM5SR1_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(5, 2);
}
#endif
#endif

#if IRQ_GTM_TOM5_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM5_SR2_PRIO > 0) || (IRQ_GTM_TOM5_SR2_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM5_SR2_PRIO > 0) && (IRQ_GTM_TOM5_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM5SR2_ISR, 0, IRQ_GTM_TOM5_SR2_PRIO)
#elif IRQ_GTM_TOM5_SR2_CAT == IRQ_CAT2
ISR(GTMTOM5SR2_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(5, 4);
}
#endif
#endif

#if IRQ_GTM_TOM5_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM5_SR3_PRIO > 0) || (IRQ_GTM_TOM5_SR3_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM5_SR3_PRIO > 0) && (IRQ_GTM_TOM5_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM5SR3_ISR, 0, IRQ_GTM_TOM5_SR3_PRIO)
#elif IRQ_GTM_TOM5_SR3_CAT == IRQ_CAT2
ISR(GTMTOM5SR3_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(5, 6);
}
#endif
#endif

#if IRQ_GTM_TOM5_SR4_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM5_SR4_PRIO > 0) || (IRQ_GTM_TOM5_SR4_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM5_SR4_PRIO > 0) && (IRQ_GTM_TOM5_SR4_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM5SR4_ISR, 0, IRQ_GTM_TOM5_SR4_PRIO)
#elif IRQ_GTM_TOM5_SR4_CAT == IRQ_CAT2
ISR(GTMTOM5SR4_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(5, 8);
}
#endif
#endif

#if IRQ_GTM_TOM5_SR5_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM5_SR5_PRIO > 0) || (IRQ_GTM_TOM5_SR5_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM5_SR5_PRIO > 0) && (IRQ_GTM_TOM5_SR5_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM5SR5_ISR, 0, IRQ_GTM_TOM5_SR5_PRIO)
#elif IRQ_GTM_TOM5_SR5_CAT == IRQ_CAT2
ISR(GTMTOM5SR5_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(5, 10);
}
#endif
#endif

#if IRQ_GTM_TOM5_SR6_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM5_SR6_PRIO > 0) || (IRQ_GTM_TOM5_SR6_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM5_SR6_PRIO > 0) && (IRQ_GTM_TOM5_SR6_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM5SR6_ISR, 0, IRQ_GTM_TOM5_SR6_PRIO)
#elif IRQ_GTM_TOM5_SR6_CAT == IRQ_CAT2
ISR(GTMTOM5SR6_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(5, 12);
}
#endif
#endif

#if IRQ_GTM_TOM5_SR7_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TOM5_SR7_PRIO > 0) || (IRQ_GTM_TOM5_SR7_CAT == IRQ_CAT2))
#if((IRQ_GTM_TOM5_SR7_PRIO > 0) && (IRQ_GTM_TOM5_SR7_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTOM5SR7_ISR, 0, IRQ_GTM_TOM5_SR7_PRIO)
#elif IRQ_GTM_TOM5_SR7_CAT == IRQ_CAT2
ISR(GTMTOM5SR7_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TomChannelIsr(5, 14);
}
#endif
#endif

#endif /* #if(IRQ_GTM_TOM5_EXIST == (STD_ON)) */

#if(IRQ_GTM_ATOM0_EXIST == (STD_ON))

#if IRQ_GTM_ATOM0_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM0_SR0_PRIO > 0) || (IRQ_GTM_ATOM0_SR0_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM0_SR0_PRIO > 0) && (IRQ_GTM_ATOM0_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM0SR0_ISR, 0, IRQ_GTM_ATOM0_SR0_PRIO)
#elif IRQ_GTM_ATOM0_SR0_CAT == IRQ_CAT2
ISR(GTMATOM0SR0_ISR)
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

  /* Specific amount of Delay is provided to perform Resilience test based on the resilience flag selection */
  #ifdef  APP_SW
  #if((defined BASE_TEST_MODULE_ID) &&((BASE_TEST_MODULE_ID == 125) && (APP_SW == TEST_APP)))
    if(u8g_Resilience_Delay_En == 1)
    {
        Timer_DelayTicks(1000);
        u8g_Resilience_Delay_En = 0;
    }
    else if(u8g_Resilience_Delay_En == 2)
    {
        Timer_DelayTicks(5000);
        u8g_Resilience_Delay_En = 0;
    }
    else if(u8g_Resilience_Delay_En == 3)
    {
        Timer_DelayTicks(10000);
        u8g_Resilience_Delay_En = 0;
    }
    else
    {
        u8g_Resilience_Delay_En = 0;
    }
  #endif
  #endif

  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(0, 0);
}
#endif
#endif

#if IRQ_GTM_ATOM0_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM0_SR1_PRIO > 0) || (IRQ_GTM_ATOM0_SR1_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM0_SR1_PRIO > 0) && (IRQ_GTM_ATOM0_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM0SR1_ISR, 0, IRQ_GTM_ATOM0_SR1_PRIO)
#elif IRQ_GTM_ATOM0_SR1_CAT == IRQ_CAT2
ISR(GTMATOM0SR1_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(0, 2);
}
#endif
#endif

#if IRQ_GTM_ATOM0_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM0_SR2_PRIO > 0) || (IRQ_GTM_ATOM0_SR2_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM0_SR2_PRIO > 0) && (IRQ_GTM_ATOM0_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM0SR2_ISR, 0, IRQ_GTM_ATOM0_SR2_PRIO)
#elif IRQ_GTM_ATOM0_SR2_CAT == IRQ_CAT2
ISR(GTMATOM0SR2_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(0, 4);
}
#endif
#endif

#if IRQ_GTM_ATOM0_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM0_SR3_PRIO > 0) || (IRQ_GTM_ATOM0_SR3_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM0_SR3_PRIO > 0) && (IRQ_GTM_ATOM0_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM0SR3_ISR, 0, IRQ_GTM_ATOM0_SR3_PRIO)
#elif IRQ_GTM_ATOM0_SR3_CAT == IRQ_CAT2
ISR(GTMATOM0SR3_ISR)
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

  /* Specific amount of Delay is provided to perform Resilience test based on the resilience flag selection */
  #ifdef  APP_SW
  #if((BASE_TEST_MODULE_ID == 125) && (APP_SW == TEST_APP))
    if(u8g_Resilience_Delay_En == 1)
    {
        Timer_DelayTicks(1000);
        u8g_Resilience_Delay_En = 0;
    }
    else if(u8g_Resilience_Delay_En == 2)
    {
        Timer_DelayTicks(5000);
        u8g_Resilience_Delay_En = 0;
    }
    else if(u8g_Resilience_Delay_En == 3)
    {
        Timer_DelayTicks(10000);
        u8g_Resilience_Delay_En = 0;
    }
    else
    {
        u8g_Resilience_Delay_En = 0;
    }
  #endif
  #endif

  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(0, 6);
}
#endif
#endif

#endif /* #if(IRQ_GTM_ATOM0_EXIST == (STD_ON)) */

#if(IRQ_GTM_ATOM1_EXIST == (STD_ON))

#if IRQ_GTM_ATOM1_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM1_SR0_PRIO > 0) || (IRQ_GTM_ATOM1_SR0_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM1_SR0_PRIO > 0) && (IRQ_GTM_ATOM1_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM1SR0_ISR, 0, IRQ_GTM_ATOM1_SR0_PRIO)
#elif IRQ_GTM_ATOM1_SR0_CAT == IRQ_CAT2
ISR(GTMATOM1SR0_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(1, 0);
}
#endif
#endif

#if IRQ_GTM_ATOM1_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM1_SR1_PRIO > 0) || (IRQ_GTM_ATOM1_SR1_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM1_SR1_PRIO > 0) && (IRQ_GTM_ATOM1_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM1SR1_ISR, 0, IRQ_GTM_ATOM1_SR1_PRIO)
#elif IRQ_GTM_ATOM1_SR1_CAT == IRQ_CAT2
ISR(GTMATOM1SR1_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(1, 2);
}
#endif
#endif

#if IRQ_GTM_ATOM1_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM1_SR2_PRIO > 0) || (IRQ_GTM_ATOM1_SR2_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM1_SR2_PRIO > 0) && (IRQ_GTM_ATOM1_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM1SR2_ISR, 0, IRQ_GTM_ATOM1_SR2_PRIO)
#elif IRQ_GTM_ATOM1_SR2_CAT == IRQ_CAT2
ISR(GTMATOM1SR2_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(1, 4);
}
#endif
#endif

#if IRQ_GTM_ATOM1_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM1_SR3_PRIO > 0) || (IRQ_GTM_ATOM1_SR3_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM1_SR3_PRIO > 0) && (IRQ_GTM_ATOM1_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM1SR3_ISR, 0, IRQ_GTM_ATOM1_SR3_PRIO)
#elif IRQ_GTM_ATOM1_SR3_CAT == IRQ_CAT2
ISR(GTMATOM1SR3_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(1, 6);
}
#endif
#endif

#endif /* #if(IRQ_GTM_ATOM1_EXIST == (STD_ON)) */
#if(IRQ_GTM_ATOM2_EXIST == (STD_ON))

#if IRQ_GTM_ATOM2_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM2_SR0_PRIO > 0) || (IRQ_GTM_ATOM2_SR0_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM2_SR0_PRIO > 0) && (IRQ_GTM_ATOM2_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM2SR0_ISR, 0, IRQ_GTM_ATOM2_SR0_PRIO)
#elif IRQ_GTM_ATOM2_SR0_CAT == IRQ_CAT2
ISR(GTMATOM2SR0_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(2, 0);
}
#endif
#endif

#if IRQ_GTM_ATOM2_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM2_SR1_PRIO > 0) || (IRQ_GTM_ATOM2_SR1_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM2_SR1_PRIO > 0) && (IRQ_GTM_ATOM2_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM2SR1_ISR, 0, IRQ_GTM_ATOM2_SR1_PRIO)
#elif IRQ_GTM_ATOM2_SR1_CAT == IRQ_CAT2
ISR(GTMATOM2SR1_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(2, 2);
}
#endif
#endif

#if IRQ_GTM_ATOM2_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM2_SR2_PRIO > 0) || (IRQ_GTM_ATOM2_SR2_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM2_SR2_PRIO > 0) && (IRQ_GTM_ATOM2_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM2SR2_ISR, 0, IRQ_GTM_ATOM2_SR2_PRIO)
#elif IRQ_GTM_ATOM2_SR2_CAT == IRQ_CAT2
ISR(GTMATOM2SR2_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(2, 4);
}
#endif
#endif

#if IRQ_GTM_ATOM2_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM2_SR3_PRIO > 0) || (IRQ_GTM_ATOM2_SR3_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM2_SR3_PRIO > 0) && (IRQ_GTM_ATOM2_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM2SR3_ISR, 0, IRQ_GTM_ATOM2_SR3_PRIO)
#elif IRQ_GTM_ATOM2_SR3_CAT == IRQ_CAT2
ISR(GTMATOM2SR3_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(2, 6);
}
#endif
#endif

#endif /* #if(IRQ_GTM_ATOM2_EXIST == (STD_ON)) */

#if(IRQ_GTM_ATOM3_EXIST == (STD_ON))

#if IRQ_GTM_ATOM3_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM3_SR0_PRIO > 0) || (IRQ_GTM_ATOM3_SR0_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM3_SR0_PRIO > 0) && (IRQ_GTM_ATOM3_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM3SR0_ISR, 0, IRQ_GTM_ATOM3_SR0_PRIO)
#elif IRQ_GTM_ATOM3_SR0_CAT == IRQ_CAT2
ISR(GTMATOM3SR0_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(3, 0);
}
#endif
#endif

#if IRQ_GTM_ATOM3_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM3_SR1_PRIO > 0) || (IRQ_GTM_ATOM3_SR1_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM3_SR1_PRIO > 0) && (IRQ_GTM_ATOM3_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM3SR1_ISR, 0, IRQ_GTM_ATOM3_SR1_PRIO)
#elif IRQ_GTM_ATOM3_SR1_CAT == IRQ_CAT2
ISR(GTMATOM3SR1_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(3, 2);
}
#endif
#endif

#if IRQ_GTM_ATOM3_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM3_SR2_PRIO > 0) || (IRQ_GTM_ATOM3_SR2_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM3_SR2_PRIO > 0) && (IRQ_GTM_ATOM3_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM3SR2_ISR, 0, IRQ_GTM_ATOM3_SR2_PRIO)
#elif IRQ_GTM_ATOM3_SR2_CAT == IRQ_CAT2
ISR(GTMATOM3SR2_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(3, 4);
}
#endif
#endif

#if IRQ_GTM_ATOM3_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM3_SR3_PRIO > 0) || (IRQ_GTM_ATOM3_SR3_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM3_SR3_PRIO > 0) && (IRQ_GTM_ATOM3_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM3SR3_ISR, 0, IRQ_GTM_ATOM3_SR3_PRIO)
#elif IRQ_GTM_ATOM3_SR3_CAT == IRQ_CAT2
ISR(GTMATOM3SR3_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(3, 6);
}
#endif
#endif

#endif /* #if(IRQ_GTM_ATOM3_EXIST == (STD_ON)) */

#if(IRQ_GTM_ATOM4_EXIST == (STD_ON))

#if IRQ_GTM_ATOM4_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM4_SR0_PRIO > 0) || (IRQ_GTM_ATOM4_SR0_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM4_SR0_PRIO > 0) && (IRQ_GTM_ATOM4_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM4SR0_ISR, 0, IRQ_GTM_ATOM4_SR0_PRIO)
#elif IRQ_GTM_ATOM4_SR0_CAT == IRQ_CAT2
ISR(GTMATOM4SR0_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(4, 0);
}
#endif
#endif

#if IRQ_GTM_ATOM4_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM4_SR1_PRIO > 0) || (IRQ_GTM_ATOM4_SR1_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM4_SR1_PRIO > 0) && (IRQ_GTM_ATOM4_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM4SR1_ISR, 0, IRQ_GTM_ATOM4_SR1_PRIO)
#elif IRQ_GTM_ATOM4_SR1_CAT == IRQ_CAT2
ISR(GTMATOM4SR1_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(4, 2);
}
#endif
#endif

#if IRQ_GTM_ATOM4_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM4_SR2_PRIO > 0) || (IRQ_GTM_ATOM4_SR2_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM4_SR2_PRIO > 0) && (IRQ_GTM_ATOM4_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM4SR2_ISR, 0, IRQ_GTM_ATOM4_SR2_PRIO)
#elif IRQ_GTM_ATOM4_SR2_CAT == IRQ_CAT2
ISR(GTMATOM4SR2_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(4, 4);
}
#endif
#endif

#if IRQ_GTM_ATOM4_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM4_SR3_PRIO > 0) || (IRQ_GTM_ATOM4_SR3_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM4_SR3_PRIO > 0) && (IRQ_GTM_ATOM4_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM4SR3_ISR, 0, IRQ_GTM_ATOM4_SR3_PRIO)
#elif IRQ_GTM_ATOM4_SR3_CAT == IRQ_CAT2
ISR(GTMATOM4SR3_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(4, 6);
}
#endif
#endif

#endif /* #if(IRQ_GTM_ATOM4_EXIST == (STD_ON)) */

#if(IRQ_GTM_ATOM5_EXIST == (STD_ON))

#if IRQ_GTM_ATOM5_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM5_SR0_PRIO > 0) || (IRQ_GTM_ATOM5_SR0_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM5_SR0_PRIO > 0) && (IRQ_GTM_ATOM5_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM5SR0_ISR, 0, IRQ_GTM_ATOM5_SR0_PRIO)
#elif IRQ_GTM_ATOM5_SR0_CAT == IRQ_CAT2
ISR(GTMATOM5SR0_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(5, 0);
}
#endif
#endif

#if IRQ_GTM_ATOM5_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM5_SR1_PRIO > 0) || (IRQ_GTM_ATOM5_SR1_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM5_SR1_PRIO > 0) && (IRQ_GTM_ATOM5_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM5SR1_ISR, 0, IRQ_GTM_ATOM5_SR1_PRIO)
#elif IRQ_GTM_ATOM5_SR1_CAT == IRQ_CAT2
ISR(GTMATOM5SR1_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(5, 2);
}
#endif
#endif

#if IRQ_GTM_ATOM5_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM5_SR2_PRIO > 0) || (IRQ_GTM_ATOM5_SR2_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM5_SR2_PRIO > 0) && (IRQ_GTM_ATOM5_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM5SR2_ISR, 0, IRQ_GTM_ATOM5_SR2_PRIO)
#elif IRQ_GTM_ATOM5_SR2_CAT == IRQ_CAT2
ISR(GTMATOM5SR2_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(5, 4);
}
#endif
#endif

#if IRQ_GTM_ATOM5_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM5_SR3_PRIO > 0) || (IRQ_GTM_ATOM5_SR3_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM5_SR3_PRIO > 0) && (IRQ_GTM_ATOM5_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM5SR3_ISR, 0, IRQ_GTM_ATOM5_SR3_PRIO)
#elif IRQ_GTM_ATOM5_SR3_CAT == IRQ_CAT2
ISR(GTMATOM5SR3_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(5, 6);
}
#endif
#endif

#endif /* #if(IRQ_GTM_ATOM5_EXIST == (STD_ON)) */

#if(IRQ_GTM_ATOM6_EXIST == (STD_ON))

#if IRQ_GTM_ATOM6_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM6_SR0_PRIO > 0) || (IRQ_GTM_ATOM6_SR0_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM6_SR0_PRIO > 0) && (IRQ_GTM_ATOM6_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM6SR0_ISR, 0, IRQ_GTM_ATOM6_SR0_PRIO)
#elif IRQ_GTM_ATOM6_SR0_CAT == IRQ_CAT2
ISR(GTMATOM6SR0_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(6, 0);
}
#endif
#endif

#if IRQ_GTM_ATOM6_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM6_SR1_PRIO > 0) || (IRQ_GTM_ATOM6_SR1_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM6_SR1_PRIO > 0) && (IRQ_GTM_ATOM6_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM6SR1_ISR, 0, IRQ_GTM_ATOM6_SR1_PRIO)
#elif IRQ_GTM_ATOM6_SR1_CAT == IRQ_CAT2
ISR(GTMATOM6SR1_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(6, 2);
}
#endif
#endif

#if IRQ_GTM_ATOM6_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM6_SR2_PRIO > 0) || (IRQ_GTM_ATOM6_SR2_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM6_SR2_PRIO > 0) && (IRQ_GTM_ATOM6_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM6SR2_ISR, 0, IRQ_GTM_ATOM6_SR2_PRIO)
#elif IRQ_GTM_ATOM6_SR2_CAT == IRQ_CAT2
ISR(GTMATOM6SR2_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(6, 4);
}
#endif
#endif

#if IRQ_GTM_ATOM6_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM6_SR3_PRIO > 0) || (IRQ_GTM_ATOM6_SR3_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM6_SR3_PRIO > 0) && (IRQ_GTM_ATOM6_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM6SR3_ISR, 0, IRQ_GTM_ATOM6_SR3_PRIO)
#elif IRQ_GTM_ATOM6_SR3_CAT == IRQ_CAT2
ISR(GTMATOM6SR3_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(6, 6);
}
#endif
#endif

#endif /* #if(IRQ_GTM_ATOM6_EXIST == (STD_ON)) */

#if(IRQ_GTM_ATOM7_EXIST == (STD_ON))

#if IRQ_GTM_ATOM7_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM7_SR0_PRIO > 0) || (IRQ_GTM_ATOM7_SR0_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM7_SR0_PRIO > 0) && (IRQ_GTM_ATOM7_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM7SR0_ISR, 0, IRQ_GTM_ATOM7_SR0_PRIO)
#elif IRQ_GTM_ATOM7_SR0_CAT == IRQ_CAT2
ISR(GTMATOM7SR0_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(7, 0);
}
#endif
#endif

#if IRQ_GTM_ATOM7_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM7_SR1_PRIO > 0) || (IRQ_GTM_ATOM7_SR1_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM7_SR1_PRIO > 0) && (IRQ_GTM_ATOM7_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM7SR1_ISR, 0, IRQ_GTM_ATOM7_SR1_PRIO)
#elif IRQ_GTM_ATOM7_SR1_CAT == IRQ_CAT2
ISR(GTMATOM7SR1_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(7, 2);
}
#endif
#endif

#if IRQ_GTM_ATOM7_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM7_SR2_PRIO > 0) || (IRQ_GTM_ATOM7_SR2_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM7_SR2_PRIO > 0) && (IRQ_GTM_ATOM7_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM7SR2_ISR, 0, IRQ_GTM_ATOM7_SR2_PRIO)
#elif IRQ_GTM_ATOM7_SR2_CAT == IRQ_CAT2
ISR(GTMATOM7SR2_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(7, 4);
}
#endif
#endif

#if IRQ_GTM_ATOM7_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM7_SR3_PRIO > 0) || (IRQ_GTM_ATOM7_SR3_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM7_SR3_PRIO > 0) && (IRQ_GTM_ATOM7_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM7SR3_ISR, 0, IRQ_GTM_ATOM7_SR3_PRIO)
#elif IRQ_GTM_ATOM7_SR3_CAT == IRQ_CAT2
ISR(GTMATOM7SR3_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(7, 6);
}
#endif
#endif

#endif /* #if(IRQ_GTM_ATOM7_EXIST == (STD_ON)) */

#if(IRQ_GTM_ATOM8_EXIST == (STD_ON))

#if IRQ_GTM_ATOM8_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM8_SR0_PRIO > 0) || (IRQ_GTM_ATOM8_SR0_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM8_SR0_PRIO > 0) && (IRQ_GTM_ATOM8_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM8SR0_ISR, 0, IRQ_GTM_ATOM8_SR0_PRIO)
#elif IRQ_GTM_ATOM8_SR0_CAT == IRQ_CAT2
ISR(GTMATOM8SR0_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(8, 0);
}
#endif
#endif

#if IRQ_GTM_ATOM8_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM8_SR1_PRIO > 0) || (IRQ_GTM_ATOM8_SR1_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM8_SR1_PRIO > 0) && (IRQ_GTM_ATOM8_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM8SR1_ISR, 0, IRQ_GTM_ATOM8_SR1_PRIO)
#elif IRQ_GTM_ATOM8_SR1_CAT == IRQ_CAT2
ISR(GTMATOM8SR1_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(8, 2);
}
#endif
#endif

#if IRQ_GTM_ATOM8_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM8_SR2_PRIO > 0) || (IRQ_GTM_ATOM8_SR2_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM8_SR2_PRIO > 0) && (IRQ_GTM_ATOM8_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM8SR2_ISR, 0, IRQ_GTM_ATOM8_SR2_PRIO)
#elif IRQ_GTM_ATOM8_SR2_CAT == IRQ_CAT2
ISR(GTMATOM8SR2_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(8, 4);
}
#endif
#endif

#if IRQ_GTM_ATOM8_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM8_SR3_PRIO > 0) || (IRQ_GTM_ATOM8_SR3_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM8_SR3_PRIO > 0) && (IRQ_GTM_ATOM8_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM8SR3_ISR, 0, IRQ_GTM_ATOM8_SR3_PRIO)
#elif IRQ_GTM_ATOM8_SR3_CAT == IRQ_CAT2
ISR(GTMATOM8SR3_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(8, 6);
}
#endif
#endif

#endif /* #if(IRQ_GTM_ATOM8_EXIST == (STD_ON)) */

#if(IRQ_GTM_ATOM9_EXIST == (STD_ON))

#if IRQ_GTM_ATOM9_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM9_SR0_PRIO > 0) || (IRQ_GTM_ATOM9_SR0_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM9_SR0_PRIO > 0) && (IRQ_GTM_ATOM9_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM9SR0_ISR, 0, IRQ_GTM_ATOM9_SR0_PRIO)
#elif IRQ_GTM_ATOM9_SR0_CAT == IRQ_CAT2
ISR(GTMATOM9SR0_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(9, 0);
}
#endif
#endif

#if IRQ_GTM_ATOM9_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM9_SR1_PRIO > 0) || (IRQ_GTM_ATOM9_SR1_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM9_SR1_PRIO > 0) && (IRQ_GTM_ATOM9_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM9SR1_ISR, 0, IRQ_GTM_ATOM9_SR1_PRIO)
#elif IRQ_GTM_ATOM9_SR1_CAT == IRQ_CAT2
ISR(GTMATOM9SR1_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(9, 2);
}
#endif
#endif

#if IRQ_GTM_ATOM9_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM9_SR2_PRIO > 0) || (IRQ_GTM_ATOM9_SR2_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM9_SR2_PRIO > 0) && (IRQ_GTM_ATOM9_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM9SR2_ISR, 0, IRQ_GTM_ATOM9_SR2_PRIO)
#elif IRQ_GTM_ATOM9_SR2_CAT == IRQ_CAT2
ISR(GTMATOM9SR2_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(9, 4);
}
#endif
#endif

#if IRQ_GTM_ATOM9_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM9_SR3_PRIO > 0) || (IRQ_GTM_ATOM9_SR3_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM9_SR3_PRIO > 0) && (IRQ_GTM_ATOM9_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM9SR3_ISR, 0, IRQ_GTM_ATOM9_SR3_PRIO)
#elif IRQ_GTM_ATOM9_SR3_CAT == IRQ_CAT2
ISR(GTMATOM9SR3_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(9, 6);
}
#endif
#endif

#endif /* #if(IRQ_GTM_ATOM9_EXIST == (STD_ON)) */

#if(IRQ_GTM_ATOM10_EXIST == (STD_ON))

#if IRQ_GTM_ATOM10_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM10_SR0_PRIO > 0) || (IRQ_GTM_ATOM10_SR0_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM10_SR0_PRIO > 0) && (IRQ_GTM_ATOM10_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM10SR0_ISR, 0, IRQ_GTM_ATOM10_SR0_PRIO)
#elif IRQ_GTM_ATOM10_SR0_CAT == IRQ_CAT2
ISR(GTMATOM10SR0_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(10, 0);
}
#endif
#endif

#if IRQ_GTM_ATOM10_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM10_SR1_PRIO > 0) || (IRQ_GTM_ATOM10_SR1_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM10_SR1_PRIO > 0) && (IRQ_GTM_ATOM10_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM10SR1_ISR, 0, IRQ_GTM_ATOM10_SR1_PRIO)
#elif IRQ_GTM_ATOM10_SR1_CAT == IRQ_CAT2
ISR(GTMATOM10SR1_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(10, 2);
}
#endif
#endif

#if IRQ_GTM_ATOM10_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM10_SR2_PRIO > 0) || (IRQ_GTM_ATOM10_SR2_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM10_SR2_PRIO > 0) && (IRQ_GTM_ATOM10_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM10SR2_ISR, 0, IRQ_GTM_ATOM10_SR2_PRIO)
#elif IRQ_GTM_ATOM10_SR2_CAT == IRQ_CAT2
ISR(GTMATOM10SR2_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(10, 4);
}
#endif
#endif

#if IRQ_GTM_ATOM10_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM10_SR3_PRIO > 0) || (IRQ_GTM_ATOM10_SR3_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM10_SR3_PRIO > 0) && (IRQ_GTM_ATOM10_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM10SR3_ISR, 0, IRQ_GTM_ATOM10_SR3_PRIO)
#elif IRQ_GTM_ATOM10_SR3_CAT == IRQ_CAT2
ISR(GTMATOM10SR3_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(10, 6);
}
#endif
#endif

#endif /* #if(IRQ_GTM_ATOM10_EXIST == (STD_ON)) */

#if(IRQ_GTM_ATOM11_EXIST == (STD_ON))

#if IRQ_GTM_ATOM11_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM11_SR0_PRIO > 0) || (IRQ_GTM_ATOM11_SR0_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM11_SR0_PRIO > 0) && (IRQ_GTM_ATOM11_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM11SR0_ISR, 0, IRQ_GTM_ATOM11_SR0_PRIO)
#elif IRQ_GTM_ATOM11_SR0_CAT == IRQ_CAT2
ISR(GTMATOM11SR0_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(11, 0);
}
#endif
#endif

#if IRQ_GTM_ATOM11_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM11_SR1_PRIO > 0) || (IRQ_GTM_ATOM11_SR1_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM11_SR1_PRIO > 0) && (IRQ_GTM_ATOM11_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM11SR1_ISR, 0, IRQ_GTM_ATOM11_SR1_PRIO)
#elif IRQ_GTM_ATOM11_SR1_CAT == IRQ_CAT2
ISR(GTMATOM11SR1_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(11, 2);
}
#endif
#endif

#if IRQ_GTM_ATOM11_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM11_SR2_PRIO > 0) || (IRQ_GTM_ATOM11_SR2_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM11_SR2_PRIO > 0) && (IRQ_GTM_ATOM11_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM11SR2_ISR, 0, IRQ_GTM_ATOM11_SR2_PRIO)
#elif IRQ_GTM_ATOM11_SR2_CAT == IRQ_CAT2
ISR(GTMATOM11SR2_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(11, 4);
}
#endif
#endif

#if IRQ_GTM_ATOM11_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_ATOM11_SR3_PRIO > 0) || (IRQ_GTM_ATOM11_SR3_CAT == IRQ_CAT2))
#if((IRQ_GTM_ATOM11_SR3_PRIO > 0) && (IRQ_GTM_ATOM11_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMATOM11SR3_ISR, 0, IRQ_GTM_ATOM11_SR3_PRIO)
#elif IRQ_GTM_ATOM11_SR3_CAT == IRQ_CAT2
ISR(GTMATOM11SR3_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_AtomChannelIsr(11, 6);
}
#endif
#endif

#endif /* #if(IRQ_GTM_ATOM11_EXIST == (STD_ON)) */

#if(IRQ_GTM_TIM0_EXIST == (STD_ON))
/******************** TIM 0 *************************************/
#if IRQ_GTM_TIM0_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM0_SR0_PRIO > 0) || (IRQ_GTM_TIM0_SR0_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM0_SR0_PRIO > 0) && (IRQ_GTM_TIM0_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM0SR0_ISR, 0, IRQ_GTM_TIM0_SR0_PRIO)
#elif IRQ_GTM_TIM0_SR0_CAT == IRQ_CAT2
ISR(GTMTIM0SR0_ISR)
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
  /*If Test module is ICU*/
  /*This piece of code introduces delay in isr for checking resilience
  against interrupt latency*/
  #ifdef  APP_SW
  #if((BASE_TEST_MODULE_ID == 122) &&\
      (APP_SW == TEST_APP))
  if(u8g_Resilience_Delay_En == 1)
  {
    Timer_DelayMs(1);
    u8g_Resilience_Delay_En = 0;
  }
  #endif
  #endif
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(0, 0);
}
#endif
#endif

#if IRQ_GTM_TIM0_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM0_SR1_PRIO > 0) || (IRQ_GTM_TIM0_SR1_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM0_SR1_PRIO > 0) && (IRQ_GTM_TIM0_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM0SR1_ISR, 0, IRQ_GTM_TIM0_SR1_PRIO)
#elif IRQ_GTM_TIM0_SR1_CAT == IRQ_CAT2
ISR(GTMTIM0SR1_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(0, 1);
}
#endif
#endif

#if IRQ_GTM_TIM0_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM0_SR2_PRIO > 0) || (IRQ_GTM_TIM0_SR2_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM0_SR2_PRIO > 0) && (IRQ_GTM_TIM0_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM0SR2_ISR, 0, IRQ_GTM_TIM0_SR2_PRIO)
#elif IRQ_GTM_TIM0_SR2_CAT == IRQ_CAT2
ISR(GTMTIM0SR2_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(0, 2);
}
#endif
#endif

#if IRQ_GTM_TIM0_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM0_SR3_PRIO > 0) || (IRQ_GTM_TIM0_SR3_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM0_SR3_PRIO > 0) && (IRQ_GTM_TIM0_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM0SR3_ISR, 0, IRQ_GTM_TIM0_SR3_PRIO)
#elif IRQ_GTM_TIM0_SR3_CAT == IRQ_CAT2
ISR(GTMTIM0SR3_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(0, 3);
}
#endif
#endif

#if IRQ_GTM_TIM0_SR4_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM0_SR4_PRIO > 0) || (IRQ_GTM_TIM0_SR4_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM0_SR4_PRIO > 0) && (IRQ_GTM_TIM0_SR4_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM0SR4_ISR, 0, IRQ_GTM_TIM0_SR4_PRIO)
#elif IRQ_GTM_TIM0_SR4_CAT == IRQ_CAT2
ISR(GTMTIM0SR4_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(0, 4);
}
#endif
#endif

#if IRQ_GTM_TIM0_SR5_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM0_SR5_PRIO > 0) || (IRQ_GTM_TIM0_SR5_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM0_SR5_PRIO > 0) && (IRQ_GTM_TIM0_SR5_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM0SR5_ISR, 0, IRQ_GTM_TIM0_SR5_PRIO)
#elif IRQ_GTM_TIM0_SR5_CAT == IRQ_CAT2
ISR(GTMTIM0SR5_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(0, 5);
}
#endif
#endif

#if IRQ_GTM_TIM0_SR6_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM0_SR6_PRIO > 0) || (IRQ_GTM_TIM0_SR6_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM0_SR6_PRIO > 0) && (IRQ_GTM_TIM0_SR6_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM0SR6_ISR, 0, IRQ_GTM_TIM0_SR6_PRIO)
#elif IRQ_GTM_TIM0_SR6_CAT == IRQ_CAT2
ISR(GTMTIM0SR6_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(0, 6);
}
#endif
#endif

#if IRQ_GTM_TIM0_SR7_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM0_SR7_PRIO > 0) || (IRQ_GTM_TIM0_SR7_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM0_SR7_PRIO > 0) && (IRQ_GTM_TIM0_SR7_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM0SR7_ISR, 0, IRQ_GTM_TIM0_SR7_PRIO)
#elif IRQ_GTM_TIM0_SR7_CAT == IRQ_CAT2
ISR(GTMTIM0SR7_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(0, 7);
}
#endif
#endif

#endif /* #if(IRQ_GTM_TIM0_EXIST == (STD_ON)) */

#if(IRQ_GTM_TIM1_EXIST == (STD_ON))

/******************** TIM 1 *************************************/
#if IRQ_GTM_TIM1_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM1_SR0_PRIO > 0) || (IRQ_GTM_TIM1_SR0_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM1_SR0_PRIO > 0) && (IRQ_GTM_TIM1_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM1SR0_ISR, 0, IRQ_GTM_TIM1_SR0_PRIO)
#elif IRQ_GTM_TIM1_SR0_CAT == IRQ_CAT2
ISR(GTMTIM1SR0_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(1, 0);
}
#endif
#endif

#if IRQ_GTM_TIM1_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM1_SR1_PRIO > 0) || (IRQ_GTM_TIM1_SR1_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM1_SR1_PRIO > 0) && (IRQ_GTM_TIM1_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM1SR1_ISR, 0, IRQ_GTM_TIM1_SR1_PRIO)
#elif IRQ_GTM_TIM1_SR1_CAT == IRQ_CAT2
ISR(GTMTIM1SR1_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(1, 1);
}
#endif
#endif

#if IRQ_GTM_TIM1_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM1_SR2_PRIO > 0) || (IRQ_GTM_TIM1_SR2_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM1_SR2_PRIO > 0) && (IRQ_GTM_TIM1_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM1SR2_ISR, 0, IRQ_GTM_TIM1_SR2_PRIO)
#elif IRQ_GTM_TIM1_SR2_CAT == IRQ_CAT2
ISR(GTMTIM1SR2_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(1, 2);
}
#endif
#endif

#if IRQ_GTM_TIM1_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM1_SR3_PRIO > 0) || (IRQ_GTM_TIM1_SR3_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM1_SR3_PRIO > 0) && (IRQ_GTM_TIM1_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM1SR3_ISR, 0, IRQ_GTM_TIM1_SR3_PRIO)
#elif IRQ_GTM_TIM1_SR3_CAT == IRQ_CAT2
ISR(GTMTIM1SR3_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(1, 3);
}
#endif
#endif

#if IRQ_GTM_TIM1_SR4_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM1_SR4_PRIO > 0) || (IRQ_GTM_TIM1_SR4_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM1_SR4_PRIO > 0) && (IRQ_GTM_TIM1_SR4_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM1SR4_ISR, 0, IRQ_GTM_TIM1_SR4_PRIO)
#elif IRQ_GTM_TIM1_SR4_CAT == IRQ_CAT2
ISR(GTMTIM1SR4_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(1, 4);
}
#endif
#endif

#if IRQ_GTM_TIM1_SR5_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM1_SR5_PRIO > 0) || (IRQ_GTM_TIM1_SR5_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM1_SR5_PRIO > 0) && (IRQ_GTM_TIM1_SR5_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM1SR5_ISR, 0, IRQ_GTM_TIM1_SR5_PRIO)
#elif IRQ_GTM_TIM1_SR5_CAT == IRQ_CAT2
ISR(GTMTIM1SR5_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(1, 5);
}
#endif
#endif

#if IRQ_GTM_TIM1_SR6_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM1_SR6_PRIO > 0) || (IRQ_GTM_TIM1_SR6_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM1_SR6_PRIO > 0) && (IRQ_GTM_TIM1_SR6_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM1SR6_ISR, 0, IRQ_GTM_TIM1_SR6_PRIO)
#elif IRQ_GTM_TIM1_SR6_CAT == IRQ_CAT2
ISR(GTMTIM1SR6_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(1, 6);
}
#endif
#endif

#if IRQ_GTM_TIM1_SR7_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM1_SR7_PRIO > 0) || (IRQ_GTM_TIM1_SR7_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM1_SR7_PRIO > 0) && (IRQ_GTM_TIM1_SR7_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM1SR7_ISR, 0, IRQ_GTM_TIM1_SR7_PRIO)
#elif IRQ_GTM_TIM1_SR7_CAT == IRQ_CAT2
ISR(GTMTIM1SR7_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(1, 7);
}
#endif
#endif

#endif /* #if(IRQ_GTM_TIM1_EXIST == (STD_ON)) */

#if(IRQ_GTM_TIM2_EXIST == (STD_ON))
/******************** TIM 2 *************************************/
#if IRQ_GTM_TIM2_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM2_SR0_PRIO > 0) || (IRQ_GTM_TIM2_SR0_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM2_SR0_PRIO > 0) && (IRQ_GTM_TIM2_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM2SR0_ISR, 0, IRQ_GTM_TIM2_SR0_PRIO)
#elif IRQ_GTM_TIM2_SR0_CAT == IRQ_CAT2
ISR(GTMTIM2SR0_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(2, 0);
}
#endif
#endif

#if IRQ_GTM_TIM2_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM2_SR1_PRIO > 0) || (IRQ_GTM_TIM2_SR1_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM2_SR1_PRIO > 0) && (IRQ_GTM_TIM2_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM2SR1_ISR, 0, IRQ_GTM_TIM2_SR1_PRIO)
#elif IRQ_GTM_TIM2_SR1_CAT == IRQ_CAT2
ISR(GTMTIM2SR1_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(2, 1);
}
#endif
#endif

#if IRQ_GTM_TIM2_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM2_SR2_PRIO > 0) || (IRQ_GTM_TIM2_SR2_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM2_SR2_PRIO > 0) && (IRQ_GTM_TIM2_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM2SR2_ISR, 0, IRQ_GTM_TIM2_SR2_PRIO)
#elif IRQ_GTM_TIM2_SR2_CAT == IRQ_CAT2
ISR(GTMTIM2SR2_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(2, 2);
}
#endif
#endif

#if IRQ_GTM_TIM2_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM2_SR3_PRIO > 0) || (IRQ_GTM_TIM2_SR3_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM2_SR3_PRIO > 0) && (IRQ_GTM_TIM2_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM2SR3_ISR, 0, IRQ_GTM_TIM2_SR3_PRIO)
#elif IRQ_GTM_TIM2_SR3_CAT == IRQ_CAT2
ISR(GTMTIM2SR3_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(2, 3);
}
#endif
#endif

#if IRQ_GTM_TIM2_SR4_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM2_SR4_PRIO > 0) || (IRQ_GTM_TIM2_SR4_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM2_SR4_PRIO > 0) && (IRQ_GTM_TIM2_SR4_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM2SR4_ISR, 0, IRQ_GTM_TIM2_SR4_PRIO)
#elif IRQ_GTM_TIM2_SR4_CAT == IRQ_CAT2
ISR(GTMTIM2SR4_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(2, 4);
}
#endif
#endif

#if IRQ_GTM_TIM2_SR5_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM2_SR5_PRIO > 0) || (IRQ_GTM_TIM2_SR5_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM2_SR5_PRIO > 0) && (IRQ_GTM_TIM2_SR5_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM2SR5_ISR, 0, IRQ_GTM_TIM2_SR5_PRIO)
#elif IRQ_GTM_TIM2_SR5_CAT == IRQ_CAT2
ISR(GTMTIM2SR5_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(2, 5);
}
#endif
#endif

#if IRQ_GTM_TIM2_SR6_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM2_SR6_PRIO > 0) || (IRQ_GTM_TIM2_SR6_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM2_SR6_PRIO > 0) && (IRQ_GTM_TIM2_SR6_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM2SR6_ISR, 0, IRQ_GTM_TIM2_SR6_PRIO)
#elif IRQ_GTM_TIM2_SR6_CAT == IRQ_CAT2
ISR(GTMTIM2SR6_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(2, 6);
}
#endif
#endif

#if IRQ_GTM_TIM2_SR7_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM2_SR7_PRIO > 0) || (IRQ_GTM_TIM2_SR7_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM2_SR7_PRIO > 0) && (IRQ_GTM_TIM2_SR7_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM2SR7_ISR, 0, IRQ_GTM_TIM2_SR7_PRIO)
#elif IRQ_GTM_TIM2_SR7_CAT == IRQ_CAT2
ISR(GTMTIM2SR7_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(2, 7);
}
#endif
#endif

#endif /* #if(IRQ_GTM_TIM2_EXIST == (STD_ON)) */

#if(IRQ_GTM_TIM3_EXIST == (STD_ON))
/******************** TIM 3 *************************************/

#if IRQ_GTM_TIM3_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM3_SR0_PRIO > 0) || (IRQ_GTM_TIM3_SR0_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM3_SR0_PRIO > 0) && (IRQ_GTM_TIM3_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM3SR0_ISR, 0, IRQ_GTM_TIM3_SR0_PRIO)
#elif IRQ_GTM_TIM3_SR0_CAT == IRQ_CAT2
ISR(GTMTIM3SR0_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(3, 0);
}
#endif
#endif

#if IRQ_GTM_TIM3_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM3_SR1_PRIO > 0) || (IRQ_GTM_TIM3_SR1_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM3_SR1_PRIO > 0) && (IRQ_GTM_TIM3_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM3SR1_ISR, 0, IRQ_GTM_TIM3_SR1_PRIO)
#elif IRQ_GTM_TIM3_SR1_CAT == IRQ_CAT2
ISR(GTMTIM3SR1_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(3, 1);
}
#endif
#endif

#if IRQ_GTM_TIM3_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM3_SR2_PRIO > 0) || (IRQ_GTM_TIM3_SR2_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM3_SR2_PRIO > 0) && (IRQ_GTM_TIM3_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM3SR2_ISR, 0, IRQ_GTM_TIM3_SR2_PRIO)
#elif IRQ_GTM_TIM3_SR2_CAT == IRQ_CAT2
ISR(GTMTIM3SR2_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(3, 2);
}
#endif
#endif

#if IRQ_GTM_TIM3_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM3_SR3_PRIO > 0) || (IRQ_GTM_TIM3_SR3_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM3_SR3_PRIO > 0) && (IRQ_GTM_TIM3_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM3SR3_ISR, 0, IRQ_GTM_TIM3_SR3_PRIO)
#elif IRQ_GTM_TIM3_SR3_CAT == IRQ_CAT2
ISR(GTMTIM3SR3_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(3, 3);
}
#endif
#endif

#if IRQ_GTM_TIM3_SR4_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM3_SR4_PRIO > 0) || (IRQ_GTM_TIM3_SR4_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM3_SR4_PRIO > 0) && (IRQ_GTM_TIM3_SR4_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM3SR4_ISR, 0, IRQ_GTM_TIM3_SR4_PRIO)
#elif IRQ_GTM_TIM3_SR4_CAT == IRQ_CAT2
ISR(GTMTIM3SR4_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(3, 4);
}
#endif
#endif

#if IRQ_GTM_TIM3_SR5_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM3_SR5_PRIO > 0) || (IRQ_GTM_TIM3_SR5_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM3_SR5_PRIO > 0) && (IRQ_GTM_TIM3_SR5_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM3SR5_ISR, 0, IRQ_GTM_TIM3_SR5_PRIO)
#elif IRQ_GTM_TIM3_SR5_CAT == IRQ_CAT2
ISR(GTMTIM3SR5_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(3, 5);
}
#endif
#endif

#if IRQ_GTM_TIM3_SR6_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM3_SR6_PRIO > 0) || (IRQ_GTM_TIM3_SR6_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM3_SR6_PRIO > 0) && (IRQ_GTM_TIM3_SR6_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM3SR6_ISR, 0, IRQ_GTM_TIM3_SR6_PRIO)
#elif IRQ_GTM_TIM3_SR6_CAT == IRQ_CAT2
ISR(GTMTIM3SR6_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(3, 6);
}
#endif
#endif

#if IRQ_GTM_TIM3_SR7_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM3_SR7_PRIO > 0) || (IRQ_GTM_TIM3_SR7_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM3_SR7_PRIO > 0) && (IRQ_GTM_TIM3_SR7_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM3SR7_ISR, 0, IRQ_GTM_TIM3_SR7_PRIO)
#elif IRQ_GTM_TIM3_SR7_CAT == IRQ_CAT2
ISR(GTMTIM3SR7_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(3, 7);
}
#endif
#endif

#endif /* #if(IRQ_GTM_TIM3_EXIST == (STD_ON)) */

#if(IRQ_GTM_TIM4_EXIST == (STD_ON))
/******************** TIM 4 *************************************/
#if IRQ_GTM_TIM4_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM4_SR0_PRIO > 0) || (IRQ_GTM_TIM4_SR0_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM4_SR0_PRIO > 0) && (IRQ_GTM_TIM4_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM4SR0_ISR, 0, IRQ_GTM_TIM4_SR0_PRIO)
#elif IRQ_GTM_TIM4_SR0_CAT == IRQ_CAT2
ISR(GTMTIM4SR0_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(4, 0);
}
#endif
#endif

#if IRQ_GTM_TIM4_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM4_SR1_PRIO > 0) || (IRQ_GTM_TIM4_SR1_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM4_SR1_PRIO > 0) && (IRQ_GTM_TIM4_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM4SR1_ISR, 0, IRQ_GTM_TIM4_SR1_PRIO)
#elif IRQ_GTM_TIM4_SR1_CAT == IRQ_CAT2
ISR(GTMTIM4SR1_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(4, 1);
}
#endif
#endif

#if IRQ_GTM_TIM4_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM4_SR2_PRIO > 0) || (IRQ_GTM_TIM4_SR2_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM4_SR2_PRIO > 0) && (IRQ_GTM_TIM4_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM4SR2_ISR, 0, IRQ_GTM_TIM4_SR2_PRIO)
#elif IRQ_GTM_TIM4_SR2_CAT == IRQ_CAT2
ISR(GTMTIM4SR2_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(4, 2);
}
#endif
#endif

#if IRQ_GTM_TIM4_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM4_SR3_PRIO > 0) || (IRQ_GTM_TIM4_SR3_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM4_SR3_PRIO > 0) && (IRQ_GTM_TIM4_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM4SR3_ISR, 0, IRQ_GTM_TIM4_SR3_PRIO)
#elif IRQ_GTM_TIM4_SR3_CAT == IRQ_CAT2
ISR(GTMTIM4SR3_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(4, 3);
}
#endif
#endif

#if IRQ_GTM_TIM4_SR4_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM4_SR4_PRIO > 0) || (IRQ_GTM_TIM4_SR4_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM4_SR4_PRIO > 0) && (IRQ_GTM_TIM4_SR4_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM4SR4_ISR, 0, IRQ_GTM_TIM4_SR4_PRIO)
#elif IRQ_GTM_TIM4_SR4_CAT == IRQ_CAT2
ISR(GTMTIM4SR4_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(4, 4);
}
#endif
#endif

#if IRQ_GTM_TIM4_SR5_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM4_SR5_PRIO > 0) || (IRQ_GTM_TIM4_SR5_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM4_SR5_PRIO > 0) && (IRQ_GTM_TIM4_SR5_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM4SR5_ISR, 0, IRQ_GTM_TIM4_SR5_PRIO)
#elif IRQ_GTM_TIM4_SR5_CAT == IRQ_CAT2
ISR(GTMTIM4SR5_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(4, 5);
}
#endif
#endif

#if IRQ_GTM_TIM4_SR6_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM4_SR6_PRIO > 0) || (IRQ_GTM_TIM4_SR6_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM4_SR6_PRIO > 0) && (IRQ_GTM_TIM4_SR6_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM4SR6_ISR, 0, IRQ_GTM_TIM4_SR6_PRIO)
#elif IRQ_GTM_TIM4_SR6_CAT == IRQ_CAT2
ISR(GTMTIM4SR6_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(4, 6);
}
#endif
#endif

#if IRQ_GTM_TIM4_SR7_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM4_SR7_PRIO > 0) || (IRQ_GTM_TIM4_SR7_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM4_SR7_PRIO > 0) && (IRQ_GTM_TIM4_SR7_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM4SR7_ISR, 0, IRQ_GTM_TIM4_SR7_PRIO)
#elif IRQ_GTM_TIM4_SR7_CAT == IRQ_CAT2
ISR(GTMTIM4SR7_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(4, 7);
}
#endif
#endif

#endif /* #if(IRQ_GTM_TIM4_EXIST == (STD_ON)) */

#if(IRQ_GTM_TIM5_EXIST == (STD_ON))
/******************** TIM 5 *************************************/

#if IRQ_GTM_TIM5_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM5_SR0_PRIO > 0) || (IRQ_GTM_TIM5_SR0_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM5_SR0_PRIO > 0) && (IRQ_GTM_TIM5_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM5SR0_ISR, 0, IRQ_GTM_TIM5_SR0_PRIO)
#elif IRQ_GTM_TIM5_SR0_CAT == IRQ_CAT2
ISR(GTMTIM5SR0_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(5, 0);
}
#endif
#endif

#if IRQ_GTM_TIM5_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM5_SR1_PRIO > 0) || (IRQ_GTM_TIM5_SR1_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM5_SR1_PRIO > 0) && (IRQ_GTM_TIM5_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM5SR1_ISR, 0, IRQ_GTM_TIM5_SR1_PRIO)
#elif IRQ_GTM_TIM5_SR1_CAT == IRQ_CAT2
ISR(GTMTIM5SR1_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(5, 1);
}
#endif
#endif

#if IRQ_GTM_TIM5_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM5_SR2_PRIO > 0) || (IRQ_GTM_TIM5_SR2_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM5_SR2_PRIO > 0) && (IRQ_GTM_TIM5_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM5SR2_ISR, 0, IRQ_GTM_TIM5_SR2_PRIO)
#elif IRQ_GTM_TIM5_SR2_CAT == IRQ_CAT2
ISR(GTMTIM5SR2_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(5, 2);
}
#endif
#endif

#if IRQ_GTM_TIM5_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM5_SR3_PRIO > 0) || (IRQ_GTM_TIM5_SR3_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM5_SR3_PRIO > 0) && (IRQ_GTM_TIM5_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM5SR3_ISR, 0, IRQ_GTM_TIM5_SR3_PRIO)
#elif IRQ_GTM_TIM5_SR3_CAT == IRQ_CAT2
ISR(GTMTIM5SR3_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(5, 3);
}
#endif
#endif

#if IRQ_GTM_TIM5_SR4_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM5_SR4_PRIO > 0) || (IRQ_GTM_TIM5_SR4_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM5_SR4_PRIO > 0) && (IRQ_GTM_TIM5_SR4_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM5SR4_ISR, 0, IRQ_GTM_TIM5_SR4_PRIO)
#elif IRQ_GTM_TIM5_SR4_CAT == IRQ_CAT2
ISR(GTMTIM5SR4_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(5, 4);
}
#endif
#endif

#if IRQ_GTM_TIM5_SR5_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM5_SR5_PRIO > 0) || (IRQ_GTM_TIM5_SR5_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM5_SR5_PRIO > 0) && (IRQ_GTM_TIM5_SR5_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM5SR5_ISR, 0, IRQ_GTM_TIM5_SR5_PRIO)
#elif IRQ_GTM_TIM5_SR5_CAT == IRQ_CAT2
ISR(GTMTIM5SR5_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(5, 5);
}
#endif
#endif

#if IRQ_GTM_TIM5_SR6_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM5_SR6_PRIO > 0) || (IRQ_GTM_TIM5_SR6_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM5_SR6_PRIO > 0) && (IRQ_GTM_TIM5_SR6_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM5SR6_ISR, 0, IRQ_GTM_TIM5_SR6_PRIO)
#elif IRQ_GTM_TIM5_SR6_CAT == IRQ_CAT2
ISR(GTMTIM5SR6_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(5, 6);
}
#endif
#endif

#if IRQ_GTM_TIM5_SR7_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM5_SR7_PRIO > 0) || (IRQ_GTM_TIM5_SR7_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM5_SR7_PRIO > 0) && (IRQ_GTM_TIM5_SR7_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM5SR7_ISR, 0, IRQ_GTM_TIM5_SR7_PRIO)
#elif IRQ_GTM_TIM5_SR7_CAT == IRQ_CAT2
ISR(GTMTIM5SR7_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(5, 7);
}
#endif
#endif
#endif /* #if(IRQ_GTM_TIM5_EXIST == (STD_ON)) */

#if(IRQ_GTM_TIM6_EXIST == (STD_ON))
/******************** TIM 0 *************************************/
#if IRQ_GTM_TIM6_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM6_SR0_PRIO > 0) || (IRQ_GTM_TIM6_SR0_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM6_SR0_PRIO > 0) && (IRQ_GTM_TIM6_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM6SR0_ISR, 0, IRQ_GTM_TIM6_SR0_PRIO)
#elif IRQ_GTM_TIM6_SR0_CAT == IRQ_CAT2
ISR(GTMTIM6SR0_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(6, 0);
}
#endif
#endif

#if IRQ_GTM_TIM6_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM6_SR1_PRIO > 0) || (IRQ_GTM_TIM6_SR1_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM6_SR1_PRIO > 0) && (IRQ_GTM_TIM6_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM6SR1_ISR, 0, IRQ_GTM_TIM6_SR1_PRIO)
#elif IRQ_GTM_TIM6_SR1_CAT == IRQ_CAT2
ISR(GTMTIM6SR1_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(6, 1);
}
#endif
#endif

#if IRQ_GTM_TIM6_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM6_SR2_PRIO > 0) || (IRQ_GTM_TIM6_SR2_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM6_SR2_PRIO > 0) && (IRQ_GTM_TIM6_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM6SR2_ISR, 0, IRQ_GTM_TIM6_SR2_PRIO)
#elif IRQ_GTM_TIM6_SR2_CAT == IRQ_CAT2
ISR(GTMTIM6SR2_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(6, 2);
}
#endif
#endif

#if IRQ_GTM_TIM6_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM6_SR3_PRIO > 0) || (IRQ_GTM_TIM6_SR3_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM6_SR3_PRIO > 0) && (IRQ_GTM_TIM6_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM6SR3_ISR, 0, IRQ_GTM_TIM6_SR3_PRIO)
#elif IRQ_GTM_TIM6_SR3_CAT == IRQ_CAT2
ISR(GTMTIM6SR3_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(6, 3);
}
#endif
#endif

#if IRQ_GTM_TIM6_SR4_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM6_SR4_PRIO > 0) || (IRQ_GTM_TIM6_SR4_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM6_SR4_PRIO > 0) && (IRQ_GTM_TIM6_SR4_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM6SR4_ISR, 0, IRQ_GTM_TIM6_SR4_PRIO)
#elif IRQ_GTM_TIM6_SR4_CAT == IRQ_CAT2
ISR(GTMTIM6SR4_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(6, 4);
}
#endif
#endif

#if IRQ_GTM_TIM6_SR5_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM6_SR5_PRIO > 0) || (IRQ_GTM_TIM6_SR5_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM6_SR5_PRIO > 0) && (IRQ_GTM_TIM6_SR5_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM6SR5_ISR, 0, IRQ_GTM_TIM6_SR5_PRIO)
#elif IRQ_GTM_TIM6_SR5_CAT == IRQ_CAT2
ISR(GTMTIM6SR5_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(6, 5);
}
#endif
#endif

#if IRQ_GTM_TIM6_SR6_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM6_SR6_PRIO > 0) || (IRQ_GTM_TIM6_SR6_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM6_SR6_PRIO > 0) && (IRQ_GTM_TIM6_SR6_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM6SR6_ISR, 0, IRQ_GTM_TIM6_SR6_PRIO)
#elif IRQ_GTM_TIM6_SR6_CAT == IRQ_CAT2
ISR(GTMTIM6SR6_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(6, 6);
}
#endif
#endif

#if IRQ_GTM_TIM6_SR7_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM6_SR7_PRIO > 0) || (IRQ_GTM_TIM6_SR7_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM6_SR7_PRIO > 0) && (IRQ_GTM_TIM6_SR7_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM6SR7_ISR, 0, IRQ_GTM_TIM6_SR7_PRIO)
#elif IRQ_GTM_TIM6_SR7_CAT == IRQ_CAT2
ISR(GTMTIM6SR7_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(6, 7);
}
#endif
#endif

#endif /* #if(IRQ_GTM_TIM6_EXIST == (STD_ON)) */

#if(IRQ_GTM_TIM7_EXIST == (STD_ON))
/******************** TIM 0 *************************************/
#if IRQ_GTM_TIM7_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM7_SR0_PRIO > 0) || (IRQ_GTM_TIM7_SR0_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM7_SR0_PRIO > 0) && (IRQ_GTM_TIM7_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM7SR0_ISR, 0, IRQ_GTM_TIM7_SR0_PRIO)
#elif IRQ_GTM_TIM7_SR0_CAT == IRQ_CAT2
ISR(GTMTIM7SR0_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(7, 0);
}
#endif
#endif

#if IRQ_GTM_TIM7_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM7_SR1_PRIO > 0) || (IRQ_GTM_TIM7_SR1_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM7_SR1_PRIO > 0) && (IRQ_GTM_TIM7_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM7SR1_ISR, 0, IRQ_GTM_TIM7_SR1_PRIO)
#elif IRQ_GTM_TIM7_SR1_CAT == IRQ_CAT2
ISR(GTMTIM7SR1_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(7, 1);
}
#endif
#endif

#if IRQ_GTM_TIM7_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM7_SR2_PRIO > 0) || (IRQ_GTM_TIM7_SR2_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM7_SR2_PRIO > 0) && (IRQ_GTM_TIM7_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM7SR2_ISR, 0, IRQ_GTM_TIM7_SR2_PRIO)
#elif IRQ_GTM_TIM7_SR2_CAT == IRQ_CAT2
ISR(GTMTIM7SR2_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(7, 2);
}
#endif
#endif

#if IRQ_GTM_TIM7_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM7_SR3_PRIO > 0) || (IRQ_GTM_TIM7_SR3_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM7_SR3_PRIO > 0) && (IRQ_GTM_TIM7_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM7SR3_ISR, 0, IRQ_GTM_TIM7_SR3_PRIO)
#elif IRQ_GTM_TIM7_SR3_CAT == IRQ_CAT2
ISR(GTMTIM7SR3_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(7, 3);
}
#endif
#endif

#if IRQ_GTM_TIM7_SR4_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM7_SR4_PRIO > 0) || (IRQ_GTM_TIM7_SR4_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM7_SR4_PRIO > 0) && (IRQ_GTM_TIM7_SR4_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM7SR4_ISR, 0, IRQ_GTM_TIM7_SR4_PRIO)
#elif IRQ_GTM_TIM7_SR4_CAT == IRQ_CAT2
ISR(GTMTIM7SR4_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(7, 4);
}
#endif
#endif

#if IRQ_GTM_TIM7_SR5_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM7_SR5_PRIO > 0) || (IRQ_GTM_TIM7_SR5_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM7_SR5_PRIO > 0) && (IRQ_GTM_TIM7_SR5_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM7SR5_ISR, 0, IRQ_GTM_TIM7_SR5_PRIO)
#elif IRQ_GTM_TIM7_SR5_CAT == IRQ_CAT2
ISR(GTMTIM7SR5_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(7, 5);
}
#endif
#endif

#if IRQ_GTM_TIM7_SR6_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM7_SR6_PRIO > 0) || (IRQ_GTM_TIM7_SR6_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM7_SR6_PRIO > 0) && (IRQ_GTM_TIM7_SR6_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM7SR6_ISR, 0, IRQ_GTM_TIM7_SR6_PRIO)
#elif IRQ_GTM_TIM7_SR6_CAT == IRQ_CAT2
ISR(GTMTIM7SR6_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(7, 6);
}
#endif
#endif

#if IRQ_GTM_TIM7_SR7_TOS != IRQ_TOS_DMA
#if((IRQ_GTM_TIM7_SR7_PRIO > 0) || (IRQ_GTM_TIM7_SR7_CAT == IRQ_CAT2))
#if((IRQ_GTM_TIM7_SR7_PRIO > 0) && (IRQ_GTM_TIM7_SR7_CAT == IRQ_CAT1))
IFX_INTERRUPT(GTMTIM7SR7_ISR, 0, IRQ_GTM_TIM7_SR7_PRIO)
#elif IRQ_GTM_TIM7_SR7_CAT == IRQ_CAT2
ISR(GTMTIM7SR7_ISR)
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
  /* Parameter is Channel Number */
  Mcu_17_Gtm_TimChannelIsr(7, 7);
}
#endif
#endif

#endif /* #if(IRQ_GTM_TIM7_EXIST == (STD_ON)) */
#endif
