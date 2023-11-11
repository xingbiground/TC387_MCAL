/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2017)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME   : Bfx_Demo.c                                                  **
**                                                                           **
**  VERSION    : 0.0.1                                                       **
**                                                                           **
**  DATE       : 2018-07-04                                                  **
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
**                - Demo application for BFX driver                          **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                     **
**                                                                           **
******************************************************************************/

/******************************************************************************
**                      Includes                                             **
******************************************************************************/
#include "Std_Types.h"
#include "Bfx.h"
#include "Bfx_Demo.h"
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
** Syntax : void Bfx_Demo(void)                                              **
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
** Description : Bfx Demo functions are called                               **
******************************************************************************/
void Bfx_Demo(void)
{
  char szString[4U];
  uint8 TempUSage = 0U;

  uint8 DataU8 = 0U;
  boolean ResultValueU8 = (boolean)FALSE;
  uint8 RetU8 = 0U;

  while (TempUSage != 1U)
  {
    print_f("\n/***********************************************************/");
    print_f("\n                 Bfx DRIVER DEMOAPP MENU                   \n");
    print_f("\n< 1 > SetBit,GetBit and ClrBit functionality check         \n");
    print_f("\n< 2 > SetBits and GetBits functionality check              \n");
    print_f("\n< 3 > SetBitMask,ClrBitMask and TstBitMask functionality   \n");
    print_f("\n< 4 > Even Parity functionality check                      \n");
    print_f("\n< 5 > Left shift & right shift functionality check      \n");
    print_f("\n< 6 > Left rotate & right rotate functionality check       \n");
    print_f("\n< 7 > Toggle bit functionality check                      \n");
    print_f("\n< x > Back To Main Menu                                    \n");
    print_f("\n/***********************************************************/");
    print_f("\n Enter Your Option: ");

    getline(szString, sizeof szString - 1);

    switch (*szString)
    {
      case '1':
        DataU8 = 0U;
        print_f("\nInitial data : DataU8=0x%02X\n", DataU8);
        print_f("\nSetBit,Getbit and ClrBit functionalty check for bit position 0x02 \n");
        Bfx_SetBit_u8u8(&DataU8, 2);
        print_f("\nSetBit results : DataU8=0x%02X\n", DataU8);
        ResultValueU8 = Bfx_GetBit_u8u8_u8(DataU8, 2);
        print_f("\nGetbit results: ValueU8=%u\n", ResultValueU8);
        Bfx_ClrBit_u8u8(&DataU8, 2);
        print_f("\nClrBit results : DataU8=0x%02X\n", DataU8);
        if (DataU8 == 0U)
        {
          StartResult();
          print_f("\n Result = Pass");
          EndResult();
        }
        else
        {
          StartResult();
          print_f("\n Result = Fail");
          EndResult();
        }
        break;

      case '2' :
        DataU8 = 0U;
        print_f("\nInitial data : DataU8=0x%02X\n", DataU8);
        print_f("\nSetting status 1 to bit position 5,6,7 of input data \n");
        Bfx_SetBits_u8u8u8u8(&DataU8, 5, 3, 1);
        print_f("\nSetBits result :DataU8=0x%02X\n", DataU8);
        RetU8 = Bfx_GetBits_u8u8u8_u8(DataU8, 5, 3);
        print_f("\nReading the status of bits at bit position 5,6,7 \n");
        print_f("\nGetBits result :RetU8=0x%02X\n", RetU8);
        Bfx_SetBits_u8u8u8u8(&DataU8, 5, 3, 0);
        if (DataU8 == 0U)
        {
          StartResult();
          print_f("\n Result = Pass");
          EndResult();
        }
        else
        {
          StartResult();
          print_f("\n Result = Fail");
          EndResult();
        }
        break;

      case '3' :
        DataU8 = 0x03;
        print_f("\nIntial data : DataU8=0x%02X\n", DataU8);
        print_f("Setting status of bits to 1 according to mask value 0x30");
        Bfx_SetBitMask_u8u8(&DataU8, 0x30);
        print_f("\nSetBitMask results : DataU8=0x%02X\n", DataU8);
        ResultValueU8 =  Bfx_TstBitMask_u8u8_u8(DataU8, 0x33);        /*ResultValueU32 = True*/
        print_f("\nChecking if values are set according to mask\n");
        print_f("\nTstBitMask : ResultValueU8=%u\n", ResultValueU8);
        Bfx_ClrBitMask_u8u8(&DataU8, 0x30);                      /*DataU8 = 0x03*/
        print_f("\nClear status of bits to 0 according to mask value 0x30\n");
        print_f("\nClrBitMask results : DataU8=0x%02X\n", DataU8);
        if (DataU8 == 0x03)
        {
          StartResult();
          print_f("\n Result = Pass");
          EndResult();
        }
        else
        {
          StartResult();
          print_f("\n Result = Fail");
          EndResult();
        }
        break;

      case '4' :
        DataU8 = 0xAA;
        print_f("\nIntial data : DataU8=0x%02X\n", DataU8);
        ResultValueU8 = Bfx_TstParityEven_u8_u8(DataU8);           /*ResultValueU8=True*/

        print_f("\nParityEven results : ResultValueU8=%u\n", ResultValueU8);
        print_f("\nNumber of bits with status 1 in input data is even \n");
        if (ResultValueU8 == 1)
        {
          StartResult();
          print_f("\n Result = Pass");
          EndResult();
        }
        else
        {
          StartResult();
          print_f("\n Result = Fail");
          EndResult();
        }
        break;


      case '5' :
        DataU8 = 0x01U;

        print_f("\nIntial data : DataU8=0x%02X\n", DataU8);
        Bfx_ShiftBitLt_u8u8(&DataU8, 0x07);
        print_f("\nShifting bits to left for shift count 0x07\n");
        print_f("\nShift Bit  Left results : DataU8=0x%02X\n", DataU8);
        Bfx_ShiftBitRt_u8u8(&DataU8, 0x07);
        print_f("\nShifting bits to right for shift count 0x07\n");
        print_f("\nShift Bit Right results : DataU8=0x%02X\n", DataU8);
        if(DataU8 == 1U)
        {
          StartResult();
          print_f("\n Result = Pass");
          EndResult();
        }
        else
        {
          StartResult();
          print_f("\n Result = Fail");
          EndResult();
        }
        break;

      case '6' :
        DataU8 = 0x0FU;

        print_f("\nIntial data : DataU8=0x%02X\n", DataU8);
        Bfx_RotBitRt_u8u8(&DataU8, 0x04);
        print_f("\nRotating bits to right for shift count 0x04\n");
        print_f("\nRotate Bit Right results : DataU8=0x%02X\n", DataU8);
        Bfx_RotBitLt_u8u8(&DataU8, 0x04);
        print_f("\nRotating bits to left for shift count 0x04\n");
        print_f("\nRotate Bit Left results : DataU8=0x%02X\n", DataU8);
        if(DataU8 == 0x0FU)
        {
          StartResult();
          print_f("\n Result = Pass");
          EndResult();
        }
        else
        {
          StartResult();
          print_f("\n Result = Fail");
          EndResult();
        }
        break;


      case '7' :
        DataU8 = 0xAA;

        print_f("\nIntial data : DataU8=0x%02X\n", DataU8);
        Bfx_ToggleBits_u8(&DataU8);
        print_f("\nToggling all the bits of data \n");
        print_f("\nToggle Bits First time Results : DataU8=0x%02X\n", DataU8);
        Bfx_ToggleBits_u8(&DataU8);

        print_f("\nToggle Bits second time Results : DataU8=0x%02X\n", DataU8);
        if(DataU8 == 0xAA)
        {
          StartResult();
          print_f("\n Result = Pass");
          EndResult();
        }
        else
        {
          StartResult();
          print_f("\n Result = Fail");
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
}/* Bfx_Demo() */

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/

