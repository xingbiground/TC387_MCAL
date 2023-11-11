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
**  FILENAME  : Adc_Irq.c                                                     **
**                                                                            **
**  VERSION   : 2.0.0                                                         **
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
**  DESCRIPTION : This file contains the interrupt frames for the ADC Module. **
**                                                                            **
**  SPECIFICATION(S) : Specification of ADC Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : Yes                                              **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Adc.h"
#include "Irq.h"
#include "IFX_Os.h"
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
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

#if (IRQ_ADC0_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void ADC0SR0_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC0_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_ADC0_SR0_PRIO > 0) || (IRQ_ADC0_SR0_CAT == IRQ_CAT2))
#if((IRQ_ADC0_SR0_PRIO > 0) && (IRQ_ADC0_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC0SR0_ISR, 0, IRQ_ADC0_SR0_PRIO)
#elif IRQ_ADC0_SR0_CAT == IRQ_CAT2
ISR(ADC0SR0_ISR)
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
  /* Call Adc Interrupt function*/
  Adc_RS0EventInterruptHandler(0U);
}
#endif
#endif
/******************************************************************************
** Syntax :          void ADC0SR1_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC0_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_ADC0_SR1_PRIO > 0) || (IRQ_ADC0_SR1_CAT == IRQ_CAT2))
#if((IRQ_ADC0_SR1_PRIO > 0) && (IRQ_ADC0_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC0SR1_ISR, 0, IRQ_ADC0_SR1_PRIO)
#elif IRQ_ADC0_SR1_CAT == IRQ_CAT2
ISR(ADC0SR1_ISR)
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
  #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
  /* Call Adc Interrupt function*/
  Adc_RS1EventInterruptHandler(0U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ADC0SR2_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC0_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_ADC0_SR2_PRIO > 0) || (IRQ_ADC0_SR2_CAT == IRQ_CAT2))
#if((IRQ_ADC0_SR2_PRIO > 0) && (IRQ_ADC0_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC0SR2_ISR, 0, IRQ_ADC0_SR2_PRIO)
#elif IRQ_ADC0_SR2_CAT == IRQ_CAT2
ISR(ADC0SR2_ISR)
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
  #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
  /* Call Adc Interrupt function*/
  Adc_RS2EventInterruptHandler(0U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ADC0SR3_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC0_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_ADC0_SR3_PRIO > 0) || (IRQ_ADC0_SR3_CAT == IRQ_CAT2))
#if((IRQ_ADC0_SR3_PRIO > 0) && (IRQ_ADC0_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC0SR3_ISR, 0, IRQ_ADC0_SR3_PRIO)
#elif IRQ_ADC0_SR3_CAT == IRQ_CAT2
ISR(ADC0SR3_ISR)
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
  #if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
  /* Call Adc Interrupt function*/
  Adc_ChEventInterruptHandler(0U);
  #endif
}
#endif

#endif
#endif

#if (IRQ_ADC1_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void ADC1SR0_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC1_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_ADC1_SR0_PRIO > 0) || (IRQ_ADC1_SR0_CAT == IRQ_CAT2))
#if((IRQ_ADC1_SR0_PRIO > 0) && (IRQ_ADC1_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC1SR0_ISR, 0, IRQ_ADC1_SR0_PRIO)
#elif IRQ_ADC1_SR0_CAT == IRQ_CAT2
ISR(ADC1SR0_ISR)
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
  /* Call Adc Interrupt function*/
  Adc_RS0EventInterruptHandler(1U);

}
#endif
#endif

/******************************************************************************
** Syntax :          void ADC1SR1_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC1_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_ADC1_SR1_PRIO > 0) || (IRQ_ADC1_SR1_CAT == IRQ_CAT2))
#if((IRQ_ADC1_SR1_PRIO > 0) && (IRQ_ADC1_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC1SR1_ISR, 0, IRQ_ADC1_SR1_PRIO)
#elif IRQ_ADC1_SR1_CAT == IRQ_CAT2
ISR(ADC1SR1_ISR)
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
  #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
  /* Call Adc Interrupt function*/
  Adc_RS1EventInterruptHandler(1U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ADC1SR2_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC1_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_ADC1_SR2_PRIO > 0) || (IRQ_ADC1_SR2_CAT == IRQ_CAT2))
#if((IRQ_ADC1_SR2_PRIO > 0) && (IRQ_ADC1_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC1SR2_ISR, 0, IRQ_ADC1_SR2_PRIO)
#elif IRQ_ADC1_SR2_CAT == IRQ_CAT2
ISR(ADC1SR2_ISR)
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
  #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
  /* Call Adc Interrupt function*/
  Adc_RS2EventInterruptHandler(1U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ADC1SR3_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC1_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_ADC1_SR3_PRIO > 0) || (IRQ_ADC1_SR3_CAT == IRQ_CAT2))
#if((IRQ_ADC1_SR3_PRIO > 0) && (IRQ_ADC1_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC1SR3_ISR, 0, IRQ_ADC1_SR3_PRIO)
#elif IRQ_ADC1_SR3_CAT == IRQ_CAT2
ISR(ADC1SR3_ISR)
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
  #if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
  /* Call Adc Interrupt function*/
  Adc_ChEventInterruptHandler(1U);
  #endif
}
#endif

#endif
#endif

#if (IRQ_ADC2_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void ADC2SR0_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC2_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_ADC2_SR0_PRIO > 0) || (IRQ_ADC2_SR0_CAT == IRQ_CAT2))
#if((IRQ_ADC2_SR0_PRIO > 0) && (IRQ_ADC2_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC2SR0_ISR, 0, IRQ_ADC2_SR0_PRIO)
#elif IRQ_ADC2_SR0_CAT == IRQ_CAT2
ISR(ADC2SR0_ISR)
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

  /* Call Adc Interrupt function*/
  Adc_RS0EventInterruptHandler(2U);
}
#endif
#endif

/******************************************************************************
** Syntax :          void ADC2SR1_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC2_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_ADC2_SR1_PRIO > 0) || (IRQ_ADC2_SR1_CAT == IRQ_CAT2))
#if((IRQ_ADC2_SR1_PRIO > 0) && (IRQ_ADC2_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC2SR1_ISR, 0, IRQ_ADC2_SR1_PRIO)
#elif IRQ_ADC2_SR1_CAT == IRQ_CAT2
ISR(ADC2SR1_ISR)
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
  #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
  /* Call Adc Interrupt function*/
  Adc_RS1EventInterruptHandler(2U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ADC2SR2_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC2_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_ADC2_SR2_PRIO > 0) || (IRQ_ADC2_SR2_CAT == IRQ_CAT2))
#if((IRQ_ADC2_SR2_PRIO > 0) && (IRQ_ADC2_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC2SR2_ISR, 0, IRQ_ADC2_SR2_PRIO)
#elif IRQ_ADC2_SR2_CAT == IRQ_CAT2
ISR(ADC2SR2_ISR)
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
  #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
  /* Call Adc Interrupt function*/
  Adc_RS2EventInterruptHandler(2U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ADC2SR3_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC2_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_ADC2_SR3_PRIO > 0) || (IRQ_ADC2_SR3_CAT == IRQ_CAT2))
#if((IRQ_ADC2_SR3_PRIO > 0) && (IRQ_ADC2_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC2SR3_ISR, 0, IRQ_ADC2_SR3_PRIO)
#elif IRQ_ADC2_SR3_CAT == IRQ_CAT2
ISR(ADC2SR3_ISR)
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
  #if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
  /* Call Adc Interrupt function*/
  Adc_ChEventInterruptHandler(2U);
  #endif
}
#endif

#endif
#endif

#if (IRQ_ADC3_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void ADC3SR0_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC3_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_ADC3_SR0_PRIO > 0) || (IRQ_ADC3_SR0_CAT == IRQ_CAT2))
#if((IRQ_ADC3_SR0_PRIO > 0) && (IRQ_ADC3_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC3SR0_ISR, 0, IRQ_ADC3_SR0_PRIO)
#elif IRQ_ADC3_SR0_CAT == IRQ_CAT2
ISR(ADC3SR0_ISR)
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

  /* Call Adc Interrupt function*/
  Adc_RS0EventInterruptHandler(3U);
}
#endif
#endif

/******************************************************************************
** Syntax :          void ADC3SR1_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC3_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_ADC3_SR1_PRIO > 0) || (IRQ_ADC3_SR1_CAT == IRQ_CAT2))
#if((IRQ_ADC3_SR1_PRIO > 0) && (IRQ_ADC3_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC3SR1_ISR, 0, IRQ_ADC3_SR1_PRIO)
#elif IRQ_ADC3_SR1_CAT == IRQ_CAT2
ISR(ADC3SR1_ISR)
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
  #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
  /* Call Adc Interrupt function*/
  Adc_RS1EventInterruptHandler(3U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ADC3SR2_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC3_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_ADC3_SR2_PRIO > 0) || (IRQ_ADC3_SR2_CAT == IRQ_CAT2))
#if((IRQ_ADC3_SR2_PRIO > 0) && (IRQ_ADC3_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC3SR2_ISR, 0, IRQ_ADC3_SR2_PRIO)
#elif IRQ_ADC3_SR2_CAT == IRQ_CAT2
ISR(ADC3SR2_ISR)
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
  #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
  /* Call Adc Interrupt function*/
  Adc_RS2EventInterruptHandler(3U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ADC3SR3_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC3_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_ADC3_SR3_PRIO > 0) || (IRQ_ADC3_SR3_CAT == IRQ_CAT2))
#if((IRQ_ADC3_SR3_PRIO > 0) && (IRQ_ADC3_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC3SR3_ISR, 0, IRQ_ADC3_SR3_PRIO)
#elif IRQ_ADC3_SR3_CAT == IRQ_CAT2
ISR(ADC3SR3_ISR)
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
  #if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
  /* Call Adc Interrupt function*/
  Adc_ChEventInterruptHandler(3U);
  #endif
}
#endif

#endif
#endif

#if (IRQ_ADC4_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void ADC4SR0_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC4_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_ADC4_SR0_PRIO > 0) || (IRQ_ADC4_SR0_CAT == IRQ_CAT2))
#if((IRQ_ADC4_SR0_PRIO > 0) && (IRQ_ADC4_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC4SR0_ISR, 0, IRQ_ADC4_SR0_PRIO)
#elif IRQ_ADC4_SR0_CAT == IRQ_CAT2
ISR(ADC4SR0_ISR)
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

  /* Call Adc Interrupt function*/
  Adc_RS0EventInterruptHandler(4U);
}
#endif
#endif

/******************************************************************************
** Syntax :          void ADC4SR1_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC4_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_ADC4_SR1_PRIO > 0) || (IRQ_ADC4_SR1_CAT == IRQ_CAT2))
#if((IRQ_ADC4_SR1_PRIO > 0) && (IRQ_ADC4_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC4SR1_ISR, 0, IRQ_ADC4_SR1_PRIO)
#elif IRQ_ADC4_SR1_CAT == IRQ_CAT2
ISR(ADC4SR1_ISR)
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
  #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
  /* Call Adc Interrupt function*/
  Adc_RS1EventInterruptHandler(4U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ADC4SR2_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC4_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_ADC4_SR2_PRIO > 0) || (IRQ_ADC4_SR2_CAT == IRQ_CAT2))
#if((IRQ_ADC4_SR2_PRIO > 0) && (IRQ_ADC4_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC4SR2_ISR, 0, IRQ_ADC4_SR2_PRIO)
#elif IRQ_ADC4_SR2_CAT == IRQ_CAT2
ISR(ADC4SR2_ISR)
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
  #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
  /* Call Adc Interrupt function*/
  Adc_RS2EventInterruptHandler(4U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ADC4SR3_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC4_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_ADC4_SR3_PRIO > 0) || (IRQ_ADC4_SR3_CAT == IRQ_CAT2))
#if((IRQ_ADC4_SR3_PRIO > 0) && (IRQ_ADC4_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC4SR3_ISR, 0, IRQ_ADC4_SR3_PRIO)
#elif IRQ_ADC4_SR3_CAT == IRQ_CAT2
ISR(ADC4SR3_ISR)
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
  #if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
  /* Call Adc Interrupt function*/
  Adc_ChEventInterruptHandler(4U);
  #endif
}
#endif

#endif
#endif

#if (IRQ_ADC5_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void ADC5SR0_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC5_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_ADC5_SR0_PRIO > 0) || (IRQ_ADC5_SR0_CAT == IRQ_CAT2))
#if((IRQ_ADC5_SR0_PRIO > 0) && (IRQ_ADC5_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC5SR0_ISR, 0, IRQ_ADC5_SR0_PRIO)
#elif IRQ_ADC5_SR0_CAT == IRQ_CAT2
ISR(ADC5SR0_ISR)
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

  /* Call Adc Interrupt function*/
  Adc_RS0EventInterruptHandler(5U);
}
#endif
#endif

/******************************************************************************
** Syntax :          void ADC5SR1_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC5_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_ADC5_SR1_PRIO > 0) || (IRQ_ADC5_SR1_CAT == IRQ_CAT2))
#if((IRQ_ADC5_SR1_PRIO > 0) && (IRQ_ADC5_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC5SR1_ISR, 0, IRQ_ADC5_SR1_PRIO)
#elif IRQ_ADC5_SR1_CAT == IRQ_CAT2
ISR(ADC5SR1_ISR)
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
  #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
  /* Call Adc Interrupt function*/
  Adc_RS1EventInterruptHandler(5U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ADC5SR2_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC5_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_ADC5_SR2_PRIO > 0) || (IRQ_ADC5_SR2_CAT == IRQ_CAT2))
#if((IRQ_ADC5_SR2_PRIO > 0) && (IRQ_ADC5_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC5SR2_ISR, 0, IRQ_ADC5_SR2_PRIO)
#elif IRQ_ADC5_SR2_CAT == IRQ_CAT2
ISR(ADC5SR2_ISR)
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
  #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
  /* Call Adc Interrupt function*/
  Adc_RS2EventInterruptHandler(5U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ADC5SR3_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC5_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_ADC5_SR3_PRIO > 0) || (IRQ_ADC5_SR3_CAT == IRQ_CAT2))
#if((IRQ_ADC5_SR3_PRIO > 0) && (IRQ_ADC5_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC5SR3_ISR, 0, IRQ_ADC5_SR3_PRIO)
#elif IRQ_ADC5_SR3_CAT == IRQ_CAT2
ISR(ADC5SR3_ISR)
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
  #if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
  /* Call Adc Interrupt function*/
  Adc_ChEventInterruptHandler(5U);
  #endif
}
#endif
#endif

#endif

#if (IRQ_ADC6_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void ADC6SR0_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC6_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_ADC6_SR0_PRIO > 0) || (IRQ_ADC6_SR0_CAT == IRQ_CAT2))
#if((IRQ_ADC6_SR0_PRIO > 0) && (IRQ_ADC6_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC6SR0_ISR, 0, IRQ_ADC6_SR0_PRIO)
#elif IRQ_ADC6_SR0_CAT == IRQ_CAT2
ISR(ADC6SR0_ISR)
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

  /* Call Adc Interrupt function*/
  Adc_RS0EventInterruptHandler(6U);
}
#endif
#endif

/******************************************************************************
** Syntax :          void ADC6SR1_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC6_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_ADC6_SR1_PRIO > 0) || (IRQ_ADC6_SR1_CAT == IRQ_CAT2))
#if((IRQ_ADC6_SR1_PRIO > 0) && (IRQ_ADC6_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC6SR1_ISR, 0, IRQ_ADC6_SR1_PRIO)
#elif IRQ_ADC6_SR1_CAT == IRQ_CAT2
ISR(ADC6SR1_ISR)
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
  #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
  /* Call Adc Interrupt function*/
  Adc_RS1EventInterruptHandler(6U);
  #endif
}
#endif
#endif
/******************************************************************************
** Syntax :          void ADC6SR2_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC6_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_ADC6_SR2_PRIO > 0) || (IRQ_ADC6_SR2_CAT == IRQ_CAT2))
#if((IRQ_ADC6_SR2_PRIO > 0) && (IRQ_ADC6_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC6SR2_ISR, 0, IRQ_ADC6_SR2_PRIO)
#elif IRQ_ADC6_SR2_CAT == IRQ_CAT2
ISR(ADC6SR2_ISR)
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
  #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
  /* Call Adc Interrupt function*/
  Adc_RS2EventInterruptHandler(6U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ADC6SR3_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC6_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_ADC6_SR3_PRIO > 0) || (IRQ_ADC6_SR3_CAT == IRQ_CAT2))
#if((IRQ_ADC6_SR3_PRIO > 0) && (IRQ_ADC6_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC6SR3_ISR, 0, IRQ_ADC6_SR3_PRIO)
#elif IRQ_ADC6_SR3_CAT == IRQ_CAT2
ISR(ADC6SR3_ISR)
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
  #if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
  /* Call Adc Interrupt function*/
  Adc_ChEventInterruptHandler(6U);
  #endif
}
#endif
#endif

#endif

#if (IRQ_ADC7_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void ADC7SR0_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC7_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_ADC7_SR0_PRIO > 0) || (IRQ_ADC7_SR0_CAT == IRQ_CAT2))
#if((IRQ_ADC7_SR0_PRIO > 0) && (IRQ_ADC7_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC7SR0_ISR, 0, IRQ_ADC7_SR0_PRIO)
#elif IRQ_ADC7_SR0_CAT == IRQ_CAT2
ISR(ADC7SR0_ISR)
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

  /* Call Adc Interrupt function*/
  Adc_RS0EventInterruptHandler(7U);
}
#endif
#endif
/******************************************************************************
** Syntax :          void ADC7SR1_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC7_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_ADC7_SR1_PRIO > 0) || (IRQ_ADC7_SR1_CAT == IRQ_CAT2))
#if((IRQ_ADC7_SR1_PRIO > 0) && (IRQ_ADC7_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC7SR1_ISR, 0, IRQ_ADC7_SR1_PRIO)
#elif IRQ_ADC7_SR1_CAT == IRQ_CAT2
ISR(ADC7SR1_ISR)
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
  #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
  /* Call Adc Interrupt function*/
  Adc_RS1EventInterruptHandler(7U);
  #endif
}
#endif
#endif
/******************************************************************************
** Syntax :          void ADC7SR2_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC7_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_ADC7_SR2_PRIO > 0) || (IRQ_ADC7_SR2_CAT == IRQ_CAT2))
#if((IRQ_ADC7_SR2_PRIO > 0) && (IRQ_ADC7_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC7SR2_ISR, 0, IRQ_ADC7_SR2_PRIO)
#elif IRQ_ADC7_SR2_CAT == IRQ_CAT2
ISR(ADC7SR2_ISR)
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
  #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
  /* Call Adc Interrupt function*/
  Adc_RS2EventInterruptHandler(7U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ADC7SR3_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC7_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_ADC7_SR3_PRIO > 0) || (IRQ_ADC7_SR3_CAT == IRQ_CAT2))
#if((IRQ_ADC7_SR3_PRIO > 0) && (IRQ_ADC7_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC7SR3_ISR, 0, IRQ_ADC7_SR3_PRIO)
#elif IRQ_ADC7_SR3_CAT == IRQ_CAT2
ISR(ADC7SR3_ISR)
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
  #if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
  /* Call Adc Interrupt function*/
  Adc_ChEventInterruptHandler(7U);
  #endif
}
#endif
#endif

#endif

#if (IRQ_ADC8_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void ADC8SR0_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC8_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_ADC8_SR0_PRIO > 0) || (IRQ_ADC8_SR0_CAT == IRQ_CAT2))
#if((IRQ_ADC8_SR0_PRIO > 0) && (IRQ_ADC8_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC8SR0_ISR, 0, IRQ_ADC8_SR0_PRIO)
#elif IRQ_ADC8_SR0_CAT == IRQ_CAT2
ISR(ADC8SR0_ISR)
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

  /* Call Adc Interrupt function*/
  Adc_RS0EventInterruptHandler(8U);
}
#endif
#endif
/******************************************************************************
** Syntax :          void ADC8SR1_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC8_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_ADC8_SR1_PRIO > 0) || (IRQ_ADC8_SR1_CAT == IRQ_CAT2))
#if((IRQ_ADC8_SR1_PRIO > 0) && (IRQ_ADC8_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC8SR1_ISR, 0, IRQ_ADC8_SR1_PRIO)
#elif IRQ_ADC8_SR1_CAT == IRQ_CAT2
ISR(ADC8SR1_ISR)
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
  #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
  /* Call Adc Interrupt function*/
  Adc_RS1EventInterruptHandler(8U);
  #endif
}
#endif
#endif
/******************************************************************************
** Syntax :          void ADC8SR2_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC8_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_ADC8_SR2_PRIO > 0) || (IRQ_ADC8_SR2_CAT == IRQ_CAT2))
#if((IRQ_ADC8_SR2_PRIO > 0) && (IRQ_ADC8_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC8SR2_ISR, 0, IRQ_ADC8_SR2_PRIO)
#elif IRQ_ADC8_SR2_CAT == IRQ_CAT2
ISR(ADC8SR2_ISR)
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
  #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
  /* Call Adc Interrupt function*/
  Adc_RS2EventInterruptHandler(8U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ADC8SR3_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC8_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_ADC8_SR3_PRIO > 0) || (IRQ_ADC8_SR3_CAT == IRQ_CAT2))
#if((IRQ_ADC8_SR3_PRIO > 0) && (IRQ_ADC8_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC8SR3_ISR, 0, IRQ_ADC8_SR3_PRIO)
#elif IRQ_ADC8_SR3_CAT == IRQ_CAT2
ISR(ADC8SR3_ISR)
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
  #if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
  /* Call Adc Interrupt function*/
  Adc_ChEventInterruptHandler(8U);
  #endif
}
#endif
#endif

#endif

#if (IRQ_ADC9_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void ADC9SR0_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC9_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_ADC9_SR0_PRIO > 0) || (IRQ_ADC9_SR0_CAT == IRQ_CAT2))
#if((IRQ_ADC9_SR0_PRIO > 0) && (IRQ_ADC9_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC9SR0_ISR, 0, IRQ_ADC9_SR0_PRIO)
#elif IRQ_ADC9_SR0_CAT == IRQ_CAT2
ISR(ADC9SR0_ISR)
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

  /* Call Adc Interrupt function*/
  Adc_RS0EventInterruptHandler(9U);
}
#endif
#endif

/******************************************************************************
** Syntax :          void ADC9SR1_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC9_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_ADC9_SR1_PRIO > 0) || (IRQ_ADC9_SR1_CAT == IRQ_CAT2))
#if((IRQ_ADC9_SR1_PRIO > 0) && (IRQ_ADC9_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC9SR1_ISR, 0, IRQ_ADC9_SR1_PRIO)
#elif IRQ_ADC9_SR1_CAT == IRQ_CAT2
ISR(ADC9SR1_ISR)
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
  #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
  /* Call Adc Interrupt function*/
  Adc_RS1EventInterruptHandler(9U);
  #endif
}
#endif
#endif
/******************************************************************************
** Syntax :          void ADC9SR2_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC9_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_ADC9_SR2_PRIO > 0) || (IRQ_ADC9_SR2_CAT == IRQ_CAT2))
#if((IRQ_ADC9_SR2_PRIO > 0) && (IRQ_ADC9_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC9SR2_ISR, 0, IRQ_ADC9_SR2_PRIO)
#elif IRQ_ADC9_SR2_CAT == IRQ_CAT2
ISR(ADC9SR2_ISR)
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
  #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
  /* Call Adc Interrupt function*/
  Adc_RS2EventInterruptHandler(9U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ADC9SR3_ISR(void)                                  **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC9_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_ADC9_SR3_PRIO > 0) || (IRQ_ADC9_SR3_CAT == IRQ_CAT2))
#if((IRQ_ADC9_SR3_PRIO > 0) && (IRQ_ADC9_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC9SR3_ISR, 0, IRQ_ADC9_SR3_PRIO)
#elif IRQ_ADC9_SR3_CAT == IRQ_CAT2
ISR(ADC9SR3_ISR)
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
  #if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
  /* Call Adc Interrupt function*/
  Adc_ChEventInterruptHandler(9U);
  #endif
}
#endif
#endif

#endif

#if (IRQ_ADC10_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void ADC10SR0_ISR(void)                                 **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC10_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_ADC10_SR0_PRIO > 0) || (IRQ_ADC10_SR0_CAT == IRQ_CAT2))
#if((IRQ_ADC10_SR0_PRIO > 0) && (IRQ_ADC10_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC10SR0_ISR, 0, IRQ_ADC10_SR0_PRIO)
#elif IRQ_ADC10_SR0_CAT == IRQ_CAT2
ISR(ADC10SR0_ISR)
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

  /* Call Adc Interrupt function*/
  Adc_RS0EventInterruptHandler(10U);
}
#endif
#endif
/******************************************************************************
** Syntax :          void ADC10SR1_ISR(void)                                 **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC10_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_ADC10_SR1_PRIO > 0) || (IRQ_ADC10_SR1_CAT == IRQ_CAT2))
#if((IRQ_ADC10_SR1_PRIO > 0) && (IRQ_ADC10_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC10SR1_ISR, 0, IRQ_ADC10_SR1_PRIO)
#elif IRQ_ADC10_SR1_CAT == IRQ_CAT2
ISR(ADC10SR1_ISR)
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
  #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
  /* Call Adc Interrupt function*/
  Adc_RS1EventInterruptHandler(10U);
  #endif
}
#endif
#endif
/******************************************************************************
** Syntax :          void ADC10SR2_ISR(void)                                 **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC10_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_ADC10_SR2_PRIO > 0) || (IRQ_ADC10_SR2_CAT == IRQ_CAT2))
#if((IRQ_ADC10_SR2_PRIO > 0) && (IRQ_ADC10_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC10SR2_ISR, 0, IRQ_ADC10_SR2_PRIO)
#elif IRQ_ADC10_SR2_CAT == IRQ_CAT2
ISR(ADC10SR2_ISR)
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
  #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
  /* Call Adc Interrupt function*/
  Adc_RS2EventInterruptHandler(10U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ADC10SR3_ISR(void)                                 **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC10_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_ADC10_SR3_PRIO > 0) || (IRQ_ADC10_SR3_CAT == IRQ_CAT2))
#if((IRQ_ADC10_SR3_PRIO > 0) && (IRQ_ADC10_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC10SR3_ISR, 0, IRQ_ADC10_SR3_PRIO)
#elif IRQ_ADC10_SR3_CAT == IRQ_CAT2
ISR(ADC10SR3_ISR)
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
  #if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
  /* Call Adc Interrupt function*/
  Adc_ChEventInterruptHandler(10U);
  #endif
}
#endif
#endif

#endif

#if (IRQ_ADC11_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void ADC11SR0_ISR(void)                                 **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC11_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_ADC11_SR0_PRIO > 0) || (IRQ_ADC11_SR0_CAT == IRQ_CAT2))
#if((IRQ_ADC11_SR0_PRIO > 0) && (IRQ_ADC11_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC11SR0_ISR, 0, IRQ_ADC11_SR0_PRIO)
#elif IRQ_ADC11_SR0_CAT == IRQ_CAT2
ISR(ADC11SR0_ISR)
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

  /* Call Adc Interrupt function*/
  Adc_RS0EventInterruptHandler(11U);
}
#endif
#endif
/******************************************************************************
** Syntax :          void ADC11SR1_ISR(void)                                 **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC11_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_ADC11_SR1_PRIO > 0) || (IRQ_ADC11_SR1_CAT == IRQ_CAT2))
#if((IRQ_ADC11_SR1_PRIO > 0) && (IRQ_ADC11_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC11SR1_ISR, 0, IRQ_ADC11_SR1_PRIO)
#elif IRQ_ADC11_SR1_CAT == IRQ_CAT2
ISR(ADC11SR1_ISR)
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
  #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
  /* Call Adc Interrupt function*/
  Adc_RS1EventInterruptHandler(11U);
  #endif
}
#endif
#endif
/******************************************************************************
** Syntax :          void ADC11SR2_ISR(void)                                 **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC11_SR2_TOS != IRQ_TOS_DMA
#if((IRQ_ADC11_SR2_PRIO > 0) || (IRQ_ADC11_SR2_CAT == IRQ_CAT2))
#if((IRQ_ADC11_SR2_PRIO > 0) && (IRQ_ADC11_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC11SR2_ISR, 0, IRQ_ADC11_SR2_PRIO)
#elif IRQ_ADC11_SR2_CAT == IRQ_CAT2
ISR(ADC11SR2_ISR)
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
  #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
  /* Call Adc Interrupt function*/
  Adc_RS2EventInterruptHandler(11U);
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void ADC11SR3_ISR(void)                                 **
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
** Description :     Service on ADC Request source conversion complete       **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if IRQ_ADC11_SR3_TOS != IRQ_TOS_DMA
#if((IRQ_ADC11_SR3_PRIO > 0) || (IRQ_ADC11_SR3_CAT == IRQ_CAT2))
#if((IRQ_ADC11_SR3_PRIO > 0) && (IRQ_ADC11_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(ADC11SR3_ISR, 0, IRQ_ADC11_SR3_PRIO)
#elif IRQ_ADC11_SR3_CAT == IRQ_CAT2
ISR(ADC11SR3_ISR)
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
  #if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
  /* Call Adc Interrupt function*/
  Adc_ChEventInterruptHandler(11U);
  #endif
}
#endif
#endif

#endif

