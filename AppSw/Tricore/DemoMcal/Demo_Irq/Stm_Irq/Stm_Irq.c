/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2018)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Stm_Irq.c                                                     **
**                                                                            **
**  VERSION   : 1.0.1                                                         **
**                                                                            **
**  DATE      : 2018-10-11                                                    **
**                                                                            **
**  VARIANT   : Post-Build                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION : This file contains the interrupt frames                     **
*                 for the WDG/STM Module.                                     **
**                                                                            **
**  SPECIFICATION(S) : Specification of Watchdog Driver, AUTOSAR Release 4.2.2**
**                                                                            **
**  MAY BE CHANGED BY USER : Yes                                              **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Inclusion of Platform_Types.h and Compiler.h */
#include "Std_Types.h"
#include "Mcu_17_TimerIp.h"
/* Module configuration */
#include "DemoApp_Cfg.h"
#if (WDG_DEMO_EN == STD_ON)
#include "Wdg_17_Scu.h"
#include "Wdg_17_Scu_Cbk.h"
#endif /* (WDG_DEMO_EN == STD_ON) */

#if (APP_SW == DEMO_APP)
#include "Dio.h"
#endif

/* Global functions like Enable/Disable interrupts */
#include "McalLib.h"
#include "Irq.h"
#include "IFX_Os.h"

#if (APP_SW == DEMO_APP)
#include "Test_Time.h"
#endif /*#if (APP_SW == DEMO_APP)*/

/* Inclusion of controller sfr file */
#include "IfxStm_reg.h"
#include "IfxSrc_reg.h"

#if (APP_SW == TEST_APP)
#include "Test_Stm_Irq.h"
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
#if (APP_SW == DEMO_APP)
extern volatile uint32 *Address_ptr_1;
extern volatile uint32 *Address_ptr_2;
#endif
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
#if (IRQ_STM0_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void STM0SR0_ISR(void)                                  **
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
** Description :     Service on STM0 match interrupt                         **
**                                                                           **
******************************************************************************/
#if IRQ_STM0_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_STM0_SR0_PRIO > 0) || (IRQ_STM0_SR0_CAT == IRQ_CAT2))
#if((IRQ_STM0_SR0_PRIO > 0) && (IRQ_STM0_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(STM0SR0_ISR, 0, IRQ_STM0_SR0_PRIO)
#elif (IRQ_STM0_SR0_CAT == IRQ_CAT2)
ISR(STM0SR0_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();

  #if (APP_SW == DEMO_APP)
  Dio_FlipChannel(DIO_CHANNEL_33_4);

  *Address_ptr_2 = STM0_TIM0.U;
  #endif /*#if (APP_SW == DEMO_APP)*/

  #if (((WDG_DEMO_EN == STD_ON) && (WDG_17_SCU_TRIG_SELECT == WDG_17_SCU_STM_TIMER)) || \
  (defined TEST_STM_ENABLE) || (STM_DEMO_EN == STD_ON))
  /* Call Wdg periodic processing function */
  Mcu_17_Stm_CompareMatchIsr(0U, 0U);

  *(volatile uint32 *)0xF0001040 = 0x01;/* clear interrupt iscr */

  #elif ((APP_SW == TEST_APP))
  Test_Stm0Sr0_CompareMatchIsr();
  #endif
}
#endif
#endif
/******************************************************************************
** Syntax :          void STM0SR1_ISR(void)                                  **
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
** Description :     Service on STM0 CM1 match interrupt                     **
**                                                                           **
******************************************************************************/
#if IRQ_STM0_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_STM0_SR1_PRIO > 0) || (IRQ_STM0_SR1_CAT == IRQ_CAT2))
#if((IRQ_STM0_SR1_PRIO > 0) && (IRQ_STM0_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(STM0SR1_ISR, 0, IRQ_STM0_SR1_PRIO)
#elif (IRQ_STM0_SR1_CAT == IRQ_CAT2)
ISR(STM0SR1_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
 
  #if (((APP_SW == DEMO_APP) && (STM_DEMO_EN == STD_ON)) || ((defined TEST_STM_ENABLE)))
  Mcu_17_Stm_CompareMatchIsr(0U, 1U);
  #elif (APP_SW == TEST_APP)
  Test_Stm0Sr1_CompareMatchIsr();
  #endif /* #if (APP_SW == TEST_APP) */
}
#endif
#endif
#endif /*#if (IRQ_STM0_EXIST == STD_ON)*/

#if (IRQ_STM1_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void STM1SR0_ISR(void)                                  **
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
** Description :     Service on STM1 match interrupt                         **
**                                                                           **
******************************************************************************/
#if IRQ_STM1_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_STM1_SR0_PRIO > 0) || (IRQ_STM1_SR0_CAT == IRQ_CAT2))
#if((IRQ_STM1_SR0_PRIO > 0) && (IRQ_STM1_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(STM1SR0_ISR, 0, IRQ_STM1_SR0_PRIO)
#elif (IRQ_STM1_SR0_CAT == IRQ_CAT2)
ISR(STM1SR0_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();

  #if(((defined WDG_17_SCU_TRIG_SELECT)&&(defined WDG_17_SCU_STM_TIMER)&& \
  (WDG_17_SCU_TRIG_SELECT == WDG_17_SCU_STM_TIMER)) || ((defined TEST_STM_ENABLE) \
  && (TEST_STM_ENABLE==STD_ON)))
  Mcu_17_Stm_CompareMatchIsr(1U, 0U);

  *(volatile uint32 *)0xF0001040 = 0x01;/* clear interrupt iscr */
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void STM1SR1_ISR(void)                                  **
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
** Description :     Service on STM1 CM1 match interrupt                     **
**                                                                           **
******************************************************************************/
#if IRQ_STM1_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_STM1_SR1_PRIO > 0) || (IRQ_STM1_SR1_CAT == IRQ_CAT2))
#if((IRQ_STM1_SR1_PRIO > 0) && (IRQ_STM1_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(STM1SR1_ISR, 0, IRQ_STM1_SR1_PRIO)
#elif (IRQ_STM1_SR1_CAT == IRQ_CAT2)
ISR(STM1SR1_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  #if((defined TEST_STM_ENABLE)&& (TEST_STM_ENABLE==STD_ON))
  Mcu_17_Stm_CompareMatchIsr(1U, 1U);
  #endif
}
#endif
#endif
#endif /*#if (IRQ_STM1_EXIST == STD_ON)*/

#if (IRQ_STM2_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void STM2SR0_ISR(void)                                  **
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
** Description :     Service on STM2 match interrupt                         **
**                                                                           **
******************************************************************************/
#if IRQ_STM2_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_STM2_SR0_PRIO > 0) || (IRQ_STM2_SR0_CAT == IRQ_CAT2))
#if((IRQ_STM2_SR0_PRIO > 0) && (IRQ_STM2_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(STM2SR0_ISR, 0, IRQ_STM2_SR0_PRIO)
#elif (IRQ_STM2_SR0_CAT == IRQ_CAT2)
ISR(STM2SR0_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();

  #if(((defined WDG_17_SCU_TRIG_SELECT)&&(defined WDG_17_SCU_STM_TIMER)&& \
  (WDG_17_SCU_TRIG_SELECT == WDG_17_SCU_STM_TIMER)) || ((defined TEST_STM_ENABLE) \
  && (TEST_STM_ENABLE==STD_ON)))
  Mcu_17_Stm_CompareMatchIsr(2U, 0U);

  *(volatile uint32 *)0xF0001040 = 0x01;/* clear interrupt iscr */
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void STM2SR1_ISR(void)                                  **
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
** Description :     Service on STM2 CM1 match interrupt                     **
**                                                                           **
******************************************************************************/
#if IRQ_STM2_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_STM2_SR1_PRIO > 0) || (IRQ_STM2_SR1_CAT == IRQ_CAT2))
#if((IRQ_STM2_SR1_PRIO > 0) && (IRQ_STM2_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(STM2SR1_ISR, 0, IRQ_STM2_SR1_PRIO)
#elif (IRQ_STM2_SR1_CAT == IRQ_CAT2)
ISR(STM2SR1_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();

  #if((defined TEST_STM_ENABLE)&& (TEST_STM_ENABLE==STD_ON))
  Mcu_17_Stm_CompareMatchIsr(2U, 1U);
  #endif
}
#endif
#endif
#endif /*#if (IRQ_STM2_EXIST == STD_ON)*/

#if (IRQ_STM3_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void STM3SR0_ISR(void)                                  **
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
** Description :     Service on STM3 match interrupt                         **
**                                                                           **
******************************************************************************/
#if IRQ_STM3_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_STM3_SR0_PRIO > 0) || (IRQ_STM3_SR0_CAT == IRQ_CAT2))
#if((IRQ_STM3_SR0_PRIO > 0) && (IRQ_STM3_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(STM3SR0_ISR, 0, IRQ_STM3_SR0_PRIO)
#elif (IRQ_STM3_SR0_CAT == IRQ_CAT2)
ISR(STM3SR0_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();

  #if(((defined WDG_17_SCU_TRIG_SELECT)&&(defined WDG_17_SCU_STM_TIMER)&& \
  (WDG_17_SCU_TRIG_SELECT == WDG_17_SCU_STM_TIMER)) || ((defined TEST_STM_ENABLE) \
  && (TEST_STM_ENABLE==STD_ON)))
  Mcu_17_Stm_CompareMatchIsr(3U, 0U);

  *(volatile uint32 *)0xF0001040 = 0x01;/* clear interrupt iscr */
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void STM3SR1_ISR(void)                                  **
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
** Description :     Service on STM3 CM1 match interrupt                     **
**                                                                           **
******************************************************************************/
#if IRQ_STM3_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_STM3_SR1_PRIO > 0) || (IRQ_STM3_SR1_CAT == IRQ_CAT2))
#if((IRQ_STM3_SR1_PRIO > 0) && (IRQ_STM3_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(STM3SR1_ISR, 0, IRQ_STM3_SR1_PRIO)
#elif (IRQ_STM3_SR1_CAT == IRQ_CAT2)
ISR(STM3SR1_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  #if((defined TEST_STM_ENABLE)&& (TEST_STM_ENABLE==STD_ON))
  Mcu_17_Stm_CompareMatchIsr(3U, 1U);
  #endif
}
#endif
#endif
#endif /*#if (IRQ_STM3_EXIST == STD_ON)*/

#if (IRQ_STM4_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void STM4SR0_ISR(void)                                  **
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
** Description :     Service on STM4 match interrupt                         **
**                                                                           **
******************************************************************************/
#if IRQ_STM4_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_STM4_SR0_PRIO > 0) || (IRQ_STM4_SR0_CAT == IRQ_CAT2))
#if((IRQ_STM4_SR0_PRIO > 0) && (IRQ_STM4_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(STM4SR0_ISR, 0, IRQ_STM4_SR0_PRIO)
#elif (IRQ_STM4_SR0_CAT == IRQ_CAT2)
ISR(STM4SR0_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();

  #if(((defined WDG_17_SCU_TRIG_SELECT)&&(defined WDG_17_SCU_STM_TIMER)&& \
  (WDG_17_SCU_TRIG_SELECT == WDG_17_SCU_STM_TIMER)) || ((defined TEST_STM_ENABLE) \
  && (TEST_STM_ENABLE==STD_ON)))
  Mcu_17_Stm_CompareMatchIsr(4U, 0U);

  *(volatile uint32 *)0xF0001040 = 0x01;/* clear interrupt iscr */
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void STM4SR1_ISR(void)                                  **
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
** Description :     Service on STM4 CM1 match interrupt                     **
**                                                                           **
******************************************************************************/
#if IRQ_STM4_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_STM4_SR1_PRIO > 0) || (IRQ_STM4_SR1_CAT == IRQ_CAT2))
#if((IRQ_STM4_SR1_PRIO > 0) && (IRQ_STM4_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(STM4SR1_ISR, 0, IRQ_STM4_SR1_PRIO)
#elif (IRQ_STM4_SR1_CAT == IRQ_CAT2)
ISR(STM4SR1_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  #if((defined TEST_STM_ENABLE)&& (TEST_STM_ENABLE==STD_ON))
  Mcu_17_Stm_CompareMatchIsr(4U, 1U);
  #endif
}
#endif
#endif
#endif /*#if (IRQ_STM4_EXIST == STD_ON)*/

#if (IRQ_STM5_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void STM5SR0_ISR(void)                                  **
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
** Description :     Service on STM5 match interrupt                         **
**                                                                           **
******************************************************************************/
#if IRQ_STM5_SR0_TOS != IRQ_TOS_DMA
#if((IRQ_STM5_SR0_PRIO > 0) || (IRQ_STM5_SR0_CAT == IRQ_CAT2))
#if((IRQ_STM5_SR0_PRIO > 0) && (IRQ_STM5_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(STM5SR0_ISR, 0, IRQ_STM5_SR0_PRIO)
#elif (IRQ_STM5_SR0_CAT == IRQ_CAT2)
ISR(STM5SR0_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();

  #if(((defined WDG_17_SCU_TRIG_SELECT)&&(defined WDG_17_SCU_STM_TIMER)&& \
  (WDG_17_SCU_TRIG_SELECT == WDG_17_SCU_STM_TIMER)) || ((defined TEST_STM_ENABLE) \
  && (TEST_STM_ENABLE==STD_ON)))
  Mcu_17_Stm_CompareMatchIsr(5U, 0U);

  *(volatile uint32 *)0xF0001040 = 0x01;/* clear interrupt iscr */
  #endif
}
#endif
#endif

/******************************************************************************
** Syntax :          void STM5SR1_ISR(void)                                  **
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
** Description :     Service on STM5 CM1 match interrupt                     **
**                                                                           **
******************************************************************************/
#if IRQ_STM5_SR1_TOS != IRQ_TOS_DMA
#if((IRQ_STM5_SR1_PRIO > 0) || (IRQ_STM5_SR1_CAT == IRQ_CAT2))
#if((IRQ_STM5_SR1_PRIO > 0) && (IRQ_STM5_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(STM5SR1_ISR, 0, IRQ_STM5_SR1_PRIO)
#elif (IRQ_STM5_SR1_CAT == IRQ_CAT2)
ISR(STM5SR1_ISR)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  #if((defined TEST_STM_ENABLE)&& (TEST_STM_ENABLE==STD_ON))
  Mcu_17_Stm_CompareMatchIsr(5U, 1U);
  #endif
}
#endif
#endif
#endif /*#if (IRQ_STM5_EXIST == STD_ON)*/
