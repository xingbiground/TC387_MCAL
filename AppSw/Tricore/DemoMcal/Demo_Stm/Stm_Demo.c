/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2018)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME   : Stm_Demo.c                                                  **
**                                                                           **
**  VERSION    : 1.0.0                                                       **
**                                                                           **
**  DATE       : 2018-10-09                                                  **
**                                                                           **
**  VARIANT    : NA                                                          **
**                                                                           **
**  PLATFORM   : Infineon AURIX2G                                            **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION : This file contains                                         **
**                - Demo application for STM driver                          **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                     **
**                                                                           **
******************************************************************************/

/******************************************************************************
**                      Includes                                             **
******************************************************************************/
#if defined _GHS_C_TRICORE_
#pragma ghs nowarning 1729
#include "Std_Types.h"
#pragma ghs endnowarning 1729
#else
#include "Std_Types.h"
#endif
#include "Test_Print.h"
#include "Dio.h"
#include "Irq.h"
#include "IfxStm_reg.h"
#include "IfxSrc_reg.h"
#include "Stm.h"
#include "Stm_Demo.h"

/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
#ifndef TRB_LED
#define TRB_LED DioConf_DioChannel_TRB_LED
#endif

#define STM_Timer0      (0U)
#define STM_Timer1      (1U)
#define STM_0_Cmp0      (0U)
#define STM_0_Cmp1      (1U)
#define STM_Cont_Mode   (1U)

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
static uint32 GetParamU32(char s[]);

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/

volatile uint32 Stm_Toggle = 0;
static void Stm_DemoAppCbk(void);
uint32 Stm_Ticksvalue = 0U;
/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/

/*******************************************************************************
** Syntax : void Stm_Demo(void)                                               **
**                                                                            **
** Service ID:   : NA                                                         **
**                                                                            **
** Sync/Async:   : Synchronous                                                **
**                                                                            **
** Reentrancy:   : Non Reentrant                                              **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description :                                                              **
**                                                                            **
*******************************************************************************/
void Stm_Demo(void)
{
  char szString[40];
  uint8 Stm_TempUSage = 0;

  while (Stm_TempUSage != 1U)
  {
    print_f("\n\n\n");
    print_f("\n/*********************************************************/\n");
    print_f("\n                STM DRIVER TEST MENU                      \n ");
    print_f("\n                                                          \n ");
    print_f("     1. Stm_EnableAlarm(): Enter ticks value for LED blinking\n ");
    print_f("     2. Stm_DisableAlarm(): To stop the LED blinking\n ");
    print_f("     x.  Back To Main Menu                                  \n ");
    print_f("                                                            \n ");
    print_f("\n/*********************************************************/\n");
    print_f("  Enter Your Option :: ");

    getline(szString, sizeof (szString - 1));

    switch (*szString)
    {
      case '1':
      {
        print_f("\n/*********************************************************/\n");
        print_f("\n               Ticks Values to be Entered                 \n ");
        print_f("STM Timer works with 100MHZ frequency. To observe LED BLINKING\n ");
        print_f("       Known Amount of Ticks values Needs to be Entered.       \n");
        print_f("1. Enter 100000000 to get LED BLINKING with period of 1 Sec\n ");
        print_f("2. Enter 50000000 to get LED BLINKING with period of 0.5 Sec\n ");
        print_f("3. Enter 200000000 to get LED BLINKING with period of 2 Secs\n ");
        print_f("\n/*********************************************************/\n");
        print_f("\n  Enter Ticks Value : ");
        getline(szString, 40);
        Stm_Ticksvalue = (uint32) GetParamU32(szString);
        /* Enable the STM module for interrupt mapping*/
        Stm_EnableModule(STM_Timer0);
        /*Initialization of STM IRQ service*/
        IrqStm_Init();
        /*SRE bit needs to be set to enable interrupts*/
        SRC_STM0SR1.B.SRE = 1U;
        /*service to invoke a Call-back function after the elapse of
        given amount of time (scheduling a function) */
        Stm_EnableAlarm(STM_Timer0, STM_0_Cmp1, STM_Cont_Mode, Stm_Ticksvalue, Stm_DemoAppCbk);
        break;
      }
      case '2':
      {
        Dio_WriteChannel (TRB_LED, STD_LOW);
        Stm_DisableAlarm(STM_Timer0, STM_0_Cmp1);
        break;
      }
      case 'x':
      case 'X':
        Stm_TempUSage = 1;
        break;
      default :
        print_f(" \n\n Invalid option \n ");
        break;
    }
  }
}

/*********************************************************************************
** Syntax : void Stm_DemoAppCbk(void)                                           **
**                                                                              **
** Service ID:   : NA                                                           **
**                                                                              **
** Sync/Async:   : Synchronous                                                  **
**                                                                              **
** Reentrancy:   : NA                                                           **
**                                                                              **
** Parameters (in): none                                                        **
**                                                                              **
** Parameters (out): none                                                       **
**                                                                              **
** Return value: none                                                           **
**                                                                              **
** Description : This is a CallBack Function Invoked when an interrupt is raised**
**                                                                              **
*********************************************************************************/
static void Stm_DemoAppCbk(void)
{
  if(Stm_Toggle == 1)
  {
    Dio_WriteChannel (TRB_LED, STD_HIGH);
    Stm_Toggle = 0;
  }
  else
  {
    Dio_WriteChannel (TRB_LED, STD_LOW);
    Stm_Toggle = 1;
  }
}

/**********************************************************************************
** Syntax : void Stm_DemoAppCbk(void)                                            **
**                                                                               **
** Service ID:   : NA                                                            **
**                                                                               **
** Sync/Async:   : Synchronous                                                   **
**                                                                               **
** Reentrancy:   : NA                                                            **
**                                                                               **
** Parameters (in): none                                                         **
**                                                                               **
** Parameters (out): none                                                        **
**                                                                               **
** Return value: none                                                            **
**                                                                               **
** Description : This is a Function to take Ticks value as input from the console**
**                                                                               **
**********************************************************************************/
static uint32 GetParamU32(char s[])
{
  uint32 i, n;
  n = 0U;

  for (i = 0U; (s[i] >= '0') && (s[i] <= '9'); ++i)
  {
    n = 10 * n + (s[i] - '0');
  }

  return n;
}
