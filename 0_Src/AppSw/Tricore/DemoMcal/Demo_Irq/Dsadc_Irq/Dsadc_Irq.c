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
**  FILENAME     : Dsadc_Irq.c                                                **
**                                                                            **
**  VERSION      : 3.0.0                                                      **
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
**  DESCRIPTION  : This file contains the interrupt frames for the Dsadc.     **
**                                                                            **
**  SPECIFICATION(S) : Specification of DSADC Driver, AUTOSAR Release 4.2.2   **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/

#include "Irq.h"
#include "IFX_Os.h"
#include "Dsadc.h"
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  #include "Test_Main.h"
#endif
#endif

#if (IRQ_DSADC_EXIST == (STD_ON))

#if (IRQ_DSADC_SRM0_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void DSADC0SRGM_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     DSADC Channel 0 Main Service Request                    **
**                                                                           **
******************************************************************************/
#if((IRQ_DSADC_SRM0_PRIO > 0) || (IRQ_DSADC_SRM0_CAT == IRQ_CAT2))
#if((IRQ_DSADC_SRM0_PRIO > 0) && (IRQ_DSADC_SRM0_CAT == IRQ_CAT1))
IFX_INTERRUPT(DSADC0SRGM_ISR, 0, IRQ_DSADC_SRM0_PRIO)
#elif IRQ_DSADC_SRM0_CAT == IRQ_CAT2
ISR(DSADC0SRGM_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  #if (DSADC_RUN_TIME_API_MODE == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  #if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
  /* Call Dsadc Main Service request Interrupt function*/
  Dsadc_Isr(0);
  #endif
}
#endif
#endif
#if (IRQ_DSADC_SRM1_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void DSADC1SRGM_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     DSADC Channel 1 Main Service Request                    **
**                                                                           **
******************************************************************************/
#if((IRQ_DSADC_SRM1_PRIO > 0) || (IRQ_DSADC_SRM1_CAT == IRQ_CAT2))
#if((IRQ_DSADC_SRM1_PRIO > 0) && (IRQ_DSADC_SRM1_CAT == IRQ_CAT1))
IFX_INTERRUPT(DSADC1SRGM_ISR, 0, IRQ_DSADC_SRM1_PRIO)
#elif IRQ_DSADC_SRM1_CAT == IRQ_CAT2
ISR(DSADC1SRGM_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  #if (DSADC_RUN_TIME_API_MODE == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  #if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
  /* Call Dsadc Main Service request Interrupt function*/
  Dsadc_Isr(1);
  #endif
}
#endif

#endif
#if (IRQ_DSADC_SRM2_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void DSADC2SRGM_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     DSADC Channel 2 Main Service Request                    **
**                                                                           **
******************************************************************************/
#if((IRQ_DSADC_SRM2_PRIO > 0) || (IRQ_DSADC_SRM2_CAT == IRQ_CAT2))
#if((IRQ_DSADC_SRM2_PRIO > 0) && (IRQ_DSADC_SRM2_CAT == IRQ_CAT1))
IFX_INTERRUPT(DSADC2SRGM_ISR, 0, IRQ_DSADC_SRM2_PRIO)
#elif IRQ_DSADC_SRM2_CAT == IRQ_CAT2
ISR(DSADC2SRGM_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  #if (DSADC_RUN_TIME_API_MODE == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  #if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
  /* Call Dsadc Main Service request Interrupt function*/
  Dsadc_Isr(2);
  #endif
}
#endif

#endif
#if (IRQ_DSADC_SRM3_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void DSADC3SRGM_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     DSADC Channel 3 Main Service Request                    **
**                                                                           **
******************************************************************************/
#if((IRQ_DSADC_SRM3_PRIO > 0) || (IRQ_DSADC_SRM3_CAT == IRQ_CAT2))
#if((IRQ_DSADC_SRM3_PRIO > 0) && (IRQ_DSADC_SRM3_CAT == IRQ_CAT1))
IFX_INTERRUPT(DSADC3SRGM_ISR, 0, IRQ_DSADC_SRM3_PRIO)
#elif IRQ_DSADC_SRM3_CAT == IRQ_CAT2
ISR(DSADC3SRGM_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  #if (DSADC_RUN_TIME_API_MODE == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  #if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
  /* Call Dsadc Main Service request Interrupt function*/
  Dsadc_Isr(3);
  #endif
}
#endif

#endif
#if (IRQ_DSADC_SRM4_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void DSADC4SRGM_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     DSADC Channel 4 Main Service Request                    **
**                                                                           **
******************************************************************************/
#if((IRQ_DSADC_SRM4_PRIO > 0) || (IRQ_DSADC_SRM4_CAT == IRQ_CAT2))
#if((IRQ_DSADC_SRM4_PRIO > 0) && (IRQ_DSADC_SRM4_CAT == IRQ_CAT1))
IFX_INTERRUPT(DSADC4SRGM_ISR, 0, IRQ_DSADC_SRM4_PRIO)
#elif IRQ_DSADC_SRM4_CAT == IRQ_CAT2
ISR(DSADC4SRGM_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  #if (DSADC_RUN_TIME_API_MODE == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  #if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
  /* Call Dsadc Main Service request Interrupt function*/
  Dsadc_Isr(4);
  #endif
}
#endif

#endif
#if (IRQ_DSADC_SRM5_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void DSADC5SRGM_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     DSADC Channel 5 Main Service Request                    **
**                                                                           **
******************************************************************************/
#if((IRQ_DSADC_SRM5_PRIO > 0) || (IRQ_DSADC_SRM5_CAT == IRQ_CAT2))
#if((IRQ_DSADC_SRM5_PRIO > 0) && (IRQ_DSADC_SRM5_CAT == IRQ_CAT1))
IFX_INTERRUPT(DSADC5SRGM_ISR, 0, IRQ_DSADC_SRM5_PRIO)
#elif IRQ_DSADC_SRM5_CAT == IRQ_CAT2
ISR(DSADC5SRGM_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  #if (DSADC_RUN_TIME_API_MODE == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  #if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
  /* Call Dsadc Main Service request Interrupt function*/
  Dsadc_Isr(5);
  #endif
}
#endif

#endif
#if (IRQ_DSADC_SRM6_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void DSADC6SRGM_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     DSADC Channel 6 Main Service Request                    **
**                                                                           **
******************************************************************************/
#if((IRQ_DSADC_SRM6_PRIO > 0) || (IRQ_DSADC_SRM6_CAT == IRQ_CAT2))
#if((IRQ_DSADC_SRM6_PRIO > 0) && (IRQ_DSADC_SRM6_CAT == IRQ_CAT1))
IFX_INTERRUPT(DSADC6SRGM_ISR, 0, IRQ_DSADC_SRM6_PRIO)
#elif IRQ_DSADC_SRM6_CAT == IRQ_CAT2
ISR(DSADC6SRGM_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  #if (DSADC_RUN_TIME_API_MODE == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  #if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
  /* Call Dsadc Main Service request Interrupt function*/
  Dsadc_Isr(6);
  #endif
}
#endif

#endif
#if (IRQ_DSADC_SRM7_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void DSADC7SRGM_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     DSADC Channel 7 Main Service Request                    **
**                                                                           **
******************************************************************************/
#if((IRQ_DSADC_SRM7_PRIO > 0) || (IRQ_DSADC_SRM7_CAT == IRQ_CAT2))
#if((IRQ_DSADC_SRM7_PRIO > 0) && (IRQ_DSADC_SRM7_CAT == IRQ_CAT1))
IFX_INTERRUPT(DSADC7SRGM_ISR, 0, IRQ_DSADC_SRM7_PRIO)
#elif IRQ_DSADC_SRM7_CAT == IRQ_CAT2
ISR(DSADC7SRGM_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  #if (DSADC_RUN_TIME_API_MODE == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  #if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
  /* Call Dsadc Main Service request Interrupt function*/
  Dsadc_Isr(7);
  #endif
}
#endif

#endif
#if (IRQ_DSADC_SRM8_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void DSADC8SRGM_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     DSADC Channel 8 Main Service Request                    **
**                                                                           **
******************************************************************************/
#if((IRQ_DSADC_SRM8_PRIO > 0) || (IRQ_DSADC_SRM8_CAT == IRQ_CAT2))
#if((IRQ_DSADC_SRM8_PRIO > 0) && (IRQ_DSADC_SRM8_CAT == IRQ_CAT1))
IFX_INTERRUPT(DSADC8SRGM_ISR, 0, IRQ_DSADC_SRM8_PRIO)
#elif IRQ_DSADC_SRM8_CAT == IRQ_CAT2
ISR(DSADC8SRGM_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  #if (DSADC_RUN_TIME_API_MODE == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  #if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
  /* Call Dsadc Main Service request Interrupt function*/
  Dsadc_Isr(8);
  #endif
}
#endif

#endif
#if (IRQ_DSADC_SRM9_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void DSADC9SRGM_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     DSADC Channel 9 Main Service Request                    **
**                                                                           **
******************************************************************************/
#if((IRQ_DSADC_SRM9_PRIO > 0) || (IRQ_DSADC_SRM9_CAT == IRQ_CAT2))
#if((IRQ_DSADC_SRM9_PRIO > 0) && (IRQ_DSADC_SRM9_CAT == IRQ_CAT1))
IFX_INTERRUPT(DSADC9SRGM_ISR, 0, IRQ_DSADC_SRM9_PRIO)
#elif IRQ_DSADC_SRM9_CAT == IRQ_CAT2
ISR(DSADC9SRGM_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  #if (DSADC_RUN_TIME_API_MODE == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  #if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
  /* Call Dsadc Main Service request Interrupt function*/
  Dsadc_Isr(9);
  #endif
}
#endif

#endif
#if (IRQ_DSADC_SRM10_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void DSADC10SRGM_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     DSADC Channel 10 Main Service Request                    **
**                                                                           **
******************************************************************************/
#if((IRQ_DSADC_SRM10_PRIO > 0) || (IRQ_DSADC_SRM10_CAT == IRQ_CAT2))
#if((IRQ_DSADC_SRM10_PRIO > 0) && (IRQ_DSADC_SRM10_CAT == IRQ_CAT1))
IFX_INTERRUPT(DSADC10SRGM_ISR, 0, IRQ_DSADC_SRM10_PRIO)
#elif IRQ_DSADC_SRM10_CAT == IRQ_CAT2
ISR(DSADC10SRGM_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  #if (DSADC_RUN_TIME_API_MODE == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  #if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
  /* Call Dsadc Main Service request Interrupt function*/
  Dsadc_Isr(10);
  #endif
}
#endif

#endif
#if (IRQ_DSADC_SRM11_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void DSADC11SRGM_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     DSADC Channel 11 Main Service Request                    **
**                                                                           **
******************************************************************************/
#if((IRQ_DSADC_SRM11_PRIO > 0) || (IRQ_DSADC_SRM11_CAT == IRQ_CAT2))
#if((IRQ_DSADC_SRM11_PRIO > 0) && (IRQ_DSADC_SRM11_CAT == IRQ_CAT1))
IFX_INTERRUPT(DSADC11SRGM_ISR, 0, IRQ_DSADC_SRM11_PRIO)
#elif IRQ_DSADC_SRM11_CAT == IRQ_CAT2
ISR(DSADC11SRGM_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  #if (DSADC_RUN_TIME_API_MODE == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  #if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
  /* Call Dsadc Main Service request Interrupt function*/
  Dsadc_Isr(11);
  #endif
}
#endif

#endif
#if (IRQ_DSADC_SRM12_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void DSADC12SRGM_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     DSADC Channel 12 Main Service Request                    **
**                                                                           **
******************************************************************************/
#if((IRQ_DSADC_SRM12_PRIO > 0) || (IRQ_DSADC_SRM12_CAT == IRQ_CAT2))
#if((IRQ_DSADC_SRM12_PRIO > 0) && (IRQ_DSADC_SRM12_CAT == IRQ_CAT1))
IFX_INTERRUPT(DSADC12SRGM_ISR, 0, IRQ_DSADC_SRM12_PRIO)
#elif IRQ_DSADC_SRM12_CAT == IRQ_CAT2
ISR(DSADC12SRGM_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  #if (DSADC_RUN_TIME_API_MODE == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  #if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
  /* Call Dsadc Main Service request Interrupt function*/
  Dsadc_Isr(12);
  #endif
}
#endif

#endif
#if (IRQ_DSADC_SRM13_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void DSADC13SRGM_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     DSADC Channel 13 Main Service Request                    **
**                                                                           **
******************************************************************************/
#if((IRQ_DSADC_SRM13_PRIO > 0) || (IRQ_DSADC_SRM13_CAT == IRQ_CAT2))
#if((IRQ_DSADC_SRM13_PRIO > 0) && (IRQ_DSADC_SRM13_CAT == IRQ_CAT1))
IFX_INTERRUPT(DSADC13SRGM_ISR, 0, IRQ_DSADC_SRM13_PRIO)
#elif IRQ_DSADC_SRM13_CAT == IRQ_CAT2
ISR(DSADC13SRGM_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  #if (DSADC_RUN_TIME_API_MODE == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  #if(DSADC_ALL_CH_RESULT_HANDLING_DMA != STD_ON)
  /* Call Dsadc Main Service request Interrupt function*/
  Dsadc_Isr(13);
  #endif
}
#endif

#endif
#if (IRQ_DSADC_SRA0_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void DSADC0SRGA_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     DSADC Channel 0 Auxiliary Service Request               **
**                                                                           **
******************************************************************************/
#if((IRQ_DSADC_SRA0_PRIO > 0) || (IRQ_DSADC_SRA0_CAT == IRQ_CAT2))
#if((IRQ_DSADC_SRA0_PRIO > 0) && (IRQ_DSADC_SRA0_CAT == IRQ_CAT1))
IFX_INTERRUPT(DSADC0SRGA_ISR, 0, IRQ_DSADC_SRA0_PRIO)
#elif IRQ_DSADC_SRA0_CAT == IRQ_CAT2
ISR(DSADC0SRGA_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  /* Call Dsadc Aux Service request Interrupt function*/
}
#endif
#endif
#if (IRQ_DSADC_SRA1_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void DSADC1SRGA_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     DSADC Channel 1 Auxiliary Service Request               **
**                                                                           **
******************************************************************************/
#if((IRQ_DSADC_SRA1_PRIO > 0) || (IRQ_DSADC_SRA1_CAT == IRQ_CAT2))
#if((IRQ_DSADC_SRA1_PRIO > 0) && (IRQ_DSADC_SRA1_CAT == IRQ_CAT1))
IFX_INTERRUPT(DSADC1SRGA_ISR, 0, IRQ_DSADC_SRA1_PRIO)
#elif IRQ_DSADC_SRA1_CAT == IRQ_CAT2
ISR(DSADC1SRGA_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  /* Call Dsadc Aux Service request Interrupt function*/
}
#endif
#endif
#if (IRQ_DSADC_SRA2_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void DSADC2SRGA_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     DSADC Channel 2 Auxiliary Service Request               **
**                                                                           **
******************************************************************************/
#if((IRQ_DSADC_SRA2_PRIO > 0) || (IRQ_DSADC_SRA2_CAT == IRQ_CAT2))
#if((IRQ_DSADC_SRA2_PRIO > 0) && (IRQ_DSADC_SRA2_CAT == IRQ_CAT1))
IFX_INTERRUPT(DSADC2SRGA_ISR, 0, IRQ_DSADC_SRA2_PRIO)
#elif IRQ_DSADC_SRA2_CAT == IRQ_CAT2
ISR(DSADC2SRGA_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  /* Call Dsadc Aux Service request Interrupt function*/
}
#endif
#endif
#if (IRQ_DSADC_SRA3_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void DSADC3SRGA_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     DSADC Channel 3 Auxiliary Service Request               **
**                                                                           **
******************************************************************************/
#if((IRQ_DSADC_SRA3_PRIO > 0) || (IRQ_DSADC_SRA3_CAT == IRQ_CAT2))
#if((IRQ_DSADC_SRA3_PRIO > 0) && (IRQ_DSADC_SRA3_CAT == IRQ_CAT1))
IFX_INTERRUPT(DSADC3SRGA_ISR, 0, IRQ_DSADC_SRA3_PRIO)
#elif IRQ_DSADC_SRA3_CAT == IRQ_CAT2
ISR(DSADC3SRGA_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  /* Call Dsadc Aux Service request Interrupt function*/
}
#endif
#endif
#if (IRQ_DSADC_SRA4_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void DSADC4SRGA_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     DSADC Channel 4 Auxiliary Service Request               **
**                                                                           **
******************************************************************************/
#if((IRQ_DSADC_SRA4_PRIO > 0) || (IRQ_DSADC_SRA4_CAT == IRQ_CAT2))
#if((IRQ_DSADC_SRA4_PRIO > 0) && (IRQ_DSADC_SRA4_CAT == IRQ_CAT1))
IFX_INTERRUPT(DSADC4SRGA_ISR, 0, IRQ_DSADC_SRA4_PRIO)
#elif IRQ_DSADC_SRA4_CAT == IRQ_CAT2
ISR(DSADC4SRGA_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  /* Call Dsadc Aux Service request Interrupt function*/
}
#endif
#endif
#if (IRQ_DSADC_SRA5_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void DSADC5SRGA_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     DSADC Channel 5 Auxiliary Service Request               **
**                                                                           **
******************************************************************************/
#if((IRQ_DSADC_SRA5_PRIO > 0) || (IRQ_DSADC_SRA5_CAT == IRQ_CAT2))
#if((IRQ_DSADC_SRA5_PRIO > 0) && (IRQ_DSADC_SRA5_CAT == IRQ_CAT1))
IFX_INTERRUPT(DSADC5SRGA_ISR, 0, IRQ_DSADC_SRA5_PRIO)
#elif IRQ_DSADC_SRA5_CAT == IRQ_CAT2
ISR(DSADC5SRGA_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  /* Call Dsadc Aux Service request Interrupt function*/
}
#endif
#endif
#if (IRQ_DSADC_SRA6_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void DSADC6SRGA_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     DSADC Channel 6 Auxiliary Service Request               **
**                                                                           **
******************************************************************************/
#if((IRQ_DSADC_SRA6_PRIO > 0) || (IRQ_DSADC_SRA6_CAT == IRQ_CAT2))
#if((IRQ_DSADC_SRA6_PRIO > 0) && (IRQ_DSADC_SRA6_CAT == IRQ_CAT1))
IFX_INTERRUPT(DSADC6SRGA_ISR, 0, IRQ_DSADC_SRA6_PRIO)
#elif IRQ_DSADC_SRA6_CAT == IRQ_CAT2
ISR(DSADC6SRGA_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  /* Call Dsadc Aux Service request Interrupt function*/
}
#endif
#endif
#if (IRQ_DSADC_SRA7_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void DSADC7SRGA_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     DSADC Channel 7 Auxiliary Service Request               **
**                                                                           **
******************************************************************************/
#if((IRQ_DSADC_SRA7_PRIO > 0) || (IRQ_DSADC_SRA7_CAT == IRQ_CAT2))
#if((IRQ_DSADC_SRA7_PRIO > 0) && (IRQ_DSADC_SRA7_CAT == IRQ_CAT1))
IFX_INTERRUPT(DSADC7SRGA_ISR, 0, IRQ_DSADC_SRA7_PRIO)
#elif IRQ_DSADC_SRA7_CAT == IRQ_CAT2
ISR(DSADC7SRGA_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  /* Call Dsadc Aux Service request Interrupt function*/
}
#endif
#endif
#if (IRQ_DSADC_SRA8_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void DSADC8SRGA_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     DSADC Channel 8 Auxiliary Service Request               **
**                                                                           **
******************************************************************************/
#if((IRQ_DSADC_SRA8_PRIO > 0) || (IRQ_DSADC_SRA8_CAT == IRQ_CAT2))
#if((IRQ_DSADC_SRA8_PRIO > 0) && (IRQ_DSADC_SRA8_CAT == IRQ_CAT1))
IFX_INTERRUPT(DSADC8SRGA_ISR, 0, IRQ_DSADC_SRA8_PRIO)
#elif IRQ_DSADC_SRA8_CAT == IRQ_CAT2
ISR(DSADC8SRGA_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  /* Call Dsadc Aux Service request Interrupt function*/
}
#endif
#endif
#if (IRQ_DSADC_SRA9_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void DSADC9SRGA_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     DSADC Channel 9 Auxiliary Service Request               **
**                                                                           **
******************************************************************************/
#if((IRQ_DSADC_SRA9_PRIO > 0) || (IRQ_DSADC_SRA9_CAT == IRQ_CAT2))
#if((IRQ_DSADC_SRA9_PRIO > 0) && (IRQ_DSADC_SRA9_CAT == IRQ_CAT1))
IFX_INTERRUPT(DSADC9SRGA_ISR, 0, IRQ_DSADC_SRA9_PRIO)
#elif IRQ_DSADC_SRA9_CAT == IRQ_CAT2
ISR(DSADC9SRGA_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  /* Call Dsadc Aux Service request Interrupt function*/
}
#endif
#endif
#if (IRQ_DSADC_SRA10_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void DSADC10SRGA_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     DSADC Channel 10 Auxiliary Service Request               **
**                                                                           **
******************************************************************************/
#if((IRQ_DSADC_SRA10_PRIO > 0) || (IRQ_DSADC_SRA10_CAT == IRQ_CAT2))
#if((IRQ_DSADC_SRA10_PRIO > 0) && (IRQ_DSADC_SRA10_CAT == IRQ_CAT1))
IFX_INTERRUPT(DSADC10SRGA_ISR, 0, IRQ_DSADC_SRA10_PRIO)
#elif IRQ_DSADC_SRA10_CAT == IRQ_CAT2
ISR(DSADC10SRGA_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  /* Call Dsadc Aux Service request Interrupt function*/
}
#endif
#endif
#if (IRQ_DSADC_SRA11_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void DSADC11SRGA_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     DSADC Channel 11 Auxiliary Service Request               **
**                                                                           **
******************************************************************************/
#if((IRQ_DSADC_SRA11_PRIO > 0) || (IRQ_DSADC_SRA11_CAT == IRQ_CAT2))
#if((IRQ_DSADC_SRA11_PRIO > 0) && (IRQ_DSADC_SRA11_CAT == IRQ_CAT1))
IFX_INTERRUPT(DSADC11SRGA_ISR, 0, IRQ_DSADC_SRA11_PRIO)
#elif IRQ_DSADC_SRA11_CAT == IRQ_CAT2
ISR(DSADC11SRGA_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  /* Call Dsadc Aux Service request Interrupt function*/
}
#endif
#endif
#if (IRQ_DSADC_SRA12_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void DSADC12SRGA_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     DSADC Channel 12 Auxiliary Service Request               **
**                                                                           **
******************************************************************************/
#if((IRQ_DSADC_SRA12_PRIO > 0) || (IRQ_DSADC_SRA12_CAT == IRQ_CAT2))
#if((IRQ_DSADC_SRA12_PRIO > 0) && (IRQ_DSADC_SRA12_CAT == IRQ_CAT1))
IFX_INTERRUPT(DSADC12SRGA_ISR, 0, IRQ_DSADC_SRA12_PRIO)
#elif IRQ_DSADC_SRA12_CAT == IRQ_CAT2
ISR(DSADC12SRGA_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  /* Call Dsadc Aux Service request Interrupt function*/
}
#endif
#endif
#if (IRQ_DSADC_SRA13_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void DSADC13SRGA_ISR(void)                              **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     DSADC Channel 13 Auxiliary Service Request               **
**                                                                           **
******************************************************************************/
#if((IRQ_DSADC_SRA13_PRIO > 0) || (IRQ_DSADC_SRA13_CAT == IRQ_CAT2))
#if((IRQ_DSADC_SRA13_PRIO > 0) && (IRQ_DSADC_SRA13_CAT == IRQ_CAT1))
IFX_INTERRUPT(DSADC13SRGA_ISR, 0, IRQ_DSADC_SRA13_PRIO)
#elif IRQ_DSADC_SRA13_CAT == IRQ_CAT2
ISR(DSADC13SRGA_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  /* Call Dsadc Aux Service request Interrupt function*/
}
#endif
#endif

#endif
