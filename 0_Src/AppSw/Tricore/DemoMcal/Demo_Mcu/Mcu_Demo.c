/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2016)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME   : Mcu_Demo.c                                                  **
**                                                                           **
**  VERSION    : 0.0.1                                                       **
**                                                                           **
**  DATE       : 2016-08-22                                                  **
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
**                - Demo application for DIO driver                          **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                     **
**                                                                           **
******************************************************************************/

/******************************************************************************
**                      Includes                                             **
******************************************************************************/
#include "Std_Types.h"
#include "Mcu.h"
#include "Mcu_Demo.h"
#include "Test_Print.h"

/******************************************************************************
**                      Imported Compiler Switch Check                       **
******************************************************************************/

/******************************************************************************
**                      Private Macro Definitions                            **
******************************************************************************/

/******************************************************************************
**                      Private Type Definitions                             **
******************************************************************************/

/******************************************************************************
**                      Private Function Declarations                        **
******************************************************************************/

/******************************************************************************
**                      Global Constant Definitions                          **
******************************************************************************/

/******************************************************************************
**                      Global Variable Definitions                          **
******************************************************************************/

/******************************************************************************
**                      Private Constant Definitions                         **
******************************************************************************/

/******************************************************************************
**                      Private Variable Definitions                         **
******************************************************************************/

/******************************************************************************
**                      Global Function Definitions                          **
******************************************************************************/

/******************************************************************************
** Syntax : void DemoApp_Mcu(void)                                           **
**                                                                           **
** Service ID:   : NA                                                        **
**                                                                           **
** Sync/Async:   : Synchronous                                               **
**                                                                           **
** Reentrancy:   : Non Reentrant                                             **
**                                                                           **
** Parameters (in): none                                                     **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value    : none                                                    **
**                                                                           **
** Timing         : Fixed Cyclic/Variable Cyclic                             **
**                                                                           **
** Description : Mcu Demo functions are called                               **
******************************************************************************/
void Mcu_Demo(void)
{
  char szString[4U];
  uint8 TempUSage = 0U;

  while (TempUSage != 1U)
  {
    print_f("\n\n\n");
    print_f("\n/******************************************************");
    print_f("*********************/\n");
    print_f("\n                 MCU DRIVER DEMOAPP MENU                \n");
    print_f("                   ENTER YOUR OPTION                      \n");
    print_f("              < 1 >  Perform Software Reset               \n");
    print_f("              < 2 >  Get Reset Reason                     \n");
    print_f("              < x >  Back To Main Menu                    \n");
    print_f("\n/******************************************************");
    print_f("*********************/\n");
    print_f("Enter Your Option: ");

    getline(szString, sizeof szString - 1);

    switch (*szString)
    {
      case '1':
        Mcu_SWResetDemo();
        break;

      case '2' :
        Mcu_GetResetReasonDemo();
        break;
      /* Go Back to Main Menu */
      case 'x':
      case 'X':
        TempUSage = 1U;
        break;

      default :
      {
        print_f("\n Invalid Option Choosen \n ");
        StartResult();
        print_f("Result = Fail;");
        EndResult();
        break;
      }
    }
  }
}/* DemoApp_Mcu() */
/*******************************************************************************
** Syntax : void Mcu_SWResetDemo(void)                                        **
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
** Description : This routine calls Mcu_PerformReset , calls for the SW reset **
*******************************************************************************/
void Mcu_SWResetDemo(void)
{
  #if (MCU_CLR_COLD_RESET_STAT_API == STD_ON)
  Mcu_ClearColdResetStatus();
  #endif

  #if (MCU_PERFORM_RESET_API==STD_ON)
  Mcu_PerformReset();
  #endif
}
/*******************************************************************************
** Syntax : void Mcu_GetResetReasonDemo(void)                                 **
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
** Description : This routine checks for one of the folowing reset reson      **
                  1.MCU_ESR0_RESET                                            **
                  2.MCU_ESR1_RESET                                            **
                  3.MCU_WATCHDOG_RESET                                        **
                  4.MCU_SW_RESET                                              **
                  5.MCU_POWER_ON_RESET                                        **
                  6.MCU_RESET_UNDEFINED                                       **
*******************************************************************************/
void Mcu_GetResetReasonDemo(void)
{
  uint32 ResetValue, ResetValueTemp;
  uint32 ResetReasonBitPosition = 32;
  /*Mcu_ResetType ResetReason;*/

  ResetValue = Mcu_GetResetRawValue();
  /*ResetReason = Mcu_GetResetReason( );*/
  print_f("\nRaw Value = 0x%x \n", ResetValue);
  /*print_f("Reset Reason = %d \n", ResetReason);*/

  /* If more than 1 bit set, print the different reset reasons */

  while (ResetReasonBitPosition)
  {
    ResetValueTemp = (ResetValue) & ((uint32)0x1U << (ResetReasonBitPosition - 1));
    ResetReasonBitPosition--;
    if(ResetValueTemp > 0)
    {
      switch (ResetValueTemp)
      {
        case 0x00000001U:
        {
          print_f("MCU_ESR0_RESET Occured\n");
          break;
        }
        case 0x00000002U:
        {
          print_f("MCU_ESR1_RESET Occured\n");
          break;
        }
        case 0x00000008U:
        {
          print_f("MCU_SMU_RESET Occured\n");
          break;
        }
        case 0x00000010U:
        {
          print_f("MCU_SW_RESET Occured\n");
          StartResult();
          print_f("Result = Pass;");
          EndResult();
          break;
        }
        case 0x00000020U:
        {
          print_f("MCU_STM0_RESET Occured\n");
          break;
        }
        case 0x00000040U:
        {
          print_f("MCU_STM1_RESET Occured\n");
          break;
        }
        case 0x00000080U:
        {
          print_f("MCU_STM2_RESET Occured\n");
          break;
        }
        case 0x00000100U:
        {
          print_f("MCU_STM3_RESET Occured\n");
          break;
        }
        case 0x00000200U:
        {
          print_f("MCU_STM4_RESET Occured\n");
          break;
        }
        case 0x00000400U:
        {
          print_f("MCU_STM5_RESET Occured\n");
          break;
        }
        case 0x00010000U:
        {
          print_f("MCU_POWER_ON_RESET Occured\n");
          break;
        }
        case 0x00040000U:
        {
          print_f("MCU_CB0_RESET Occured\n");
          break;
        }
        case 0x00080000U:
        {
          print_f("MCU_CB1_RESET Occured\n");
          break;
        }
        case 0x00100000U:
        {
          print_f("MCU_CB3_RESET Occured\n");
          break;
        }
        case 0x00800000U:
        {
          print_f("MCU_EVRC_RESET Occured\n");
          break;
        }
        case 0x01000000U:
        {
          print_f("MCU_EVR33_RESET Occured\n");
          break;
        }
        case 0x02000000U:
        {
          print_f("MCU_SUPPLY_WDOG_RESET Occured\n");
          break;
        }
        case 0x10000000U:
        {
          print_f("MCU_STBYR_RESET Occured\n");
          break;
        }
        case 0x20000000U:
        {
          print_f("MCU_RBBF0_RESET Occured\n");
          break;
        }
        case 0x40000000U:
        {
          print_f("MCU_RBBF1_RESET Occured\n");
          break;
        }
        case 0x00000004U:
        case 0x00000800U:
        case 0x00001000U:
        case 0x00002000U:
        case 0x00004000U:
        case 0x00008000U:
        case 0x00020000U:
        case 0x00200000U:
        case 0x00400000U:
        case 0x04000000U:
        case 0x08000000U:
        case 0x80000000U:
        default:
        {
          print_f("Undefined RESET Occured \n" );
          break;
        }
      }
    }
  }
}
/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/



void Mcu_GotoStandbyDemoMenu(void)
{
}
