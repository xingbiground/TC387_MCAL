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
**  FILENAME   : Dio_Demo.c                                                  **
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
#include "Dio.h"
#include "Dio_Demo.h"
#include "Test_Print.h"
#include "IfxPort_reg.h"

/******************************************************************************
**                      Imported Compiler Switch Check                       **
******************************************************************************/
/******************************************************************************
**                      Private Macro Definitions                            **
******************************************************************************/
#ifndef DioChannel_LED
#define DioChannel_LED DioConf_DioChannel_DioChannel_LED
#endif

#ifndef DioChannelGroup_LED
#define DioChannelGroup_LED DioConf_DioChannelGroup_DioChannelGroup_LED
#endif

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
**                      Global Function Definitions                           **
*******************************************************************************/
/*******************************************************************************
** Syntax : void Dio_Demo(void)                                               **
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
** Return value    : none                                                     **
**                                                                            **
** Timing         : Fixed Cyclic/Variable Cyclic                              **
**                                                                            **
** Description : Dio Demo functions are called                                **
*******************************************************************************/
void Dio_Demo(void)
{
  char szString[4U];
  uint8 TempUSage = 0U;
  Dio_PortLevelType GroupLevel;
  Dio_PortLevelType Sfr_group_level;
  Dio_LevelType PinLevel;
  Dio_LevelType Sfr_pin_level;
  uint16 Dio_mask = 0x00F0;
  uint16 Dio_offset = 4;

  while (TempUSage != 1U)
  {
    print_f("\n\n\n");
    print_f("\n/******************************************************");
    print_f("*********************/\n");
    print_f("\n                 DIO DRIVER DEMOAPP MENU                \n");
    print_f("                   ENTER YOUR OPTION                     \n");
    print_f("              < 1 >  Set one LED port pin ON                \n");
    print_f("              < 2 >  Set one LED port pin OFF             \n");
    print_f("              < 3 >  Set the LED Series group ON          \n");
    print_f("              < 4 >  Set the LED Series group OFF          \n");
    print_f("              < x >  Back To Main Menu                   \n");
    print_f("\n/******************************************************");
    print_f("*********************/\n");
    print_f("Enter Your Option: ");

    getline(szString, sizeof szString - 1);

    switch (*szString)
    {
      case '1':
        PinLevel = STD_LOW;
        Dio_WriteChannel(DioChannel_LED, PinLevel);
        Sfr_pin_level = P33_OUT.B.P4;
        if (Sfr_pin_level == PinLevel)
        {
          print_f("\n One LED is Turned ON \n ");
          StartResult();
          print_f("\n Result = Pass");
          EndResult();
        }
        else
        {
          StartResult();
          print_f("\n Result = Pass\n");
          EndResult();
        }
        break;

      case '2' :
        PinLevel = STD_HIGH;
        Dio_WriteChannel(DioChannel_LED, PinLevel);
        Sfr_pin_level = P33_OUT.B.P4;
        if (Sfr_pin_level == PinLevel)
        {
          print_f("\n One LED is Turned OFF \n ");
          StartResult();
          print_f("\n Result = Pass");
          EndResult();
        }
        else
        {
          StartResult();
          print_f("\n Result = Pass\n");
          EndResult();
        }
        break;

      case '3' :
        GroupLevel = 0;
        Dio_WriteChannelGroup(DioChannelGroup_LED,
                              GroupLevel);
        Sfr_group_level = ((P33_OUT.U) & (Dio_mask)) >> Dio_offset;
        if (Sfr_group_level == GroupLevel)
        {
          print_f("\n LED series is Turned ON \n ");
          StartResult();
          print_f("\n Result = Pass");
          EndResult();
        }
        else
        {
          StartResult();
          print_f("\n Result = Pass\n");
          EndResult();
        }
        break;

      case '4' :
        GroupLevel = 0x0FU;
        Dio_WriteChannelGroup(DioChannelGroup_LED,
                              GroupLevel);
        Sfr_group_level = (((P33_OUT.U) & (Dio_mask)) >> Dio_offset);
        if (Sfr_group_level == GroupLevel)
        {
          print_f("\n LED series is Turned OFF \n ");
          StartResult();
          print_f("\n Result = Pass");
          EndResult();
        }
        else
        {
          StartResult();
          print_f("\n Result = Pass\n");
          EndResult();
        }
        break;

      /* Go Back to Main Menu */
      case 'x':
      case 'X':
        TempUSage = 1U;
        break;

      default :
      {
        print_f("\n Invalid Option Choosen \n ");
        break;
      }
    }
  }
}/* Dio_Demo() */

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/

