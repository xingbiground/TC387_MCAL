/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2013)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  $FILENAME   : Crc_Demo.c $                                               **
**                                                                           **
**  $CC VERSION : \main\14 $                                                 **
**                                                                           **
**  $DATE       : 2021-11-23 $                                               **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION : This file contains demo application for CRC Library        **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: yes                                     **
**                                                                           **
******************************************************************************/
/******************************************************************************
**                      Includes                                             **
******************************************************************************/
#include "Std_Types.h"

#include "McalLib.h"
#include "Crc.h"
#include "Crc_Demo.h"

#include "Test_Print.h"
#include "Test_Time.h"


/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/


/*******************************************************************************
**                      Private Macro Definitions                             **
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
**                      Private Function Declarations                         **
*******************************************************************************/
#ifdef CRC_8_MODE
#if  CRC_8_MODE == 0x00000002
#define CRC_8_IMPLEMENTATION_MODE "Runtime"
#endif
#if  CRC_8_MODE == 0x00000003
#define CRC_8_IMPLEMENTATION_MODE "Table"
#endif
#if  CRC_8_MODE == 0x00000001
#define CRC_8_IMPLEMENTATION_MODE "Hardware"
#endif
#endif

#ifdef CRC_8H2F_MODE
#if  CRC_8H2F_MODE == 0x00000002
#define CRC_8H2F_IMPLEMENTATION_MODE "Runtime"
#endif
#if  CRC_8H2F_MODE == 0x00000003
#define CRC_8H2F_IMPLEMENTATION_MODE "Table"
#endif
#endif

#ifdef CRC_16_MODE
#if  CRC_16_MODE == 0x00000002
#define CRC_16_IMPLEMENTATION_MODE "Runtime"
#endif
#if  CRC_16_MODE == 0x00000003
#define CRC_16_IMPLEMENTATION_MODE "Table"
#endif
#if  CRC_16_MODE == 0x00000001
#define CRC_16_IMPLEMENTATION_MODE "Hardware"
#endif
#endif

#ifdef CRC_32_MODE
#if  CRC_32_MODE == 0x00000002
#define CRC_32_IMPLEMENTATION_MODE "Runtime"
#endif
#if  CRC_32_MODE == 0x00000003
#define CRC_32_IMPLEMENTATION_MODE "Table"
#endif
#if  CRC_32_MODE == 0x00000001
#define CRC_32_IMPLEMENTATION_MODE "Hardware"
#endif
#endif

#ifdef CRC_32P4_MODE
#if  CRC_32P4_MODE == 0x00000002
#define CRC_32P4_IMPLEMENTATION_MODE "Runtime"
#endif
#if  CRC_32P4_MODE == 0x00000003
#define CRC_32P4_IMPLEMENTATION_MODE "Table"
#endif
#endif
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : void Crc_Demo(void)                                     **
**                                                                            **
**                                                                            **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : N/A                                                     **
**                                                                            **
** Reentrancy       : N/A                                                     **
**                                                                            **
** Parameters (in)  : none                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : uint32                                                  **
**                                                                            **
** Description      :This function is for demonstration of CRC 8 bit          **
**   (polynomial = 0x1D),CRC 8 bit(polynomial = 0x2F),CRC 16 bit(polynomial = **
**    0x1021),CRC 32 bit(polynomial = 0x04C11DB7) & CRC 32 bit(polynomial =   **
**     0xF4ACFB13)                                                            **
*******************************************************************************/
void Crc_Demo(void)
{
  #if (CRC_VERSION_INFO_API == (STD_ON))
  Std_VersionInfoType VerInfoPtr;
  #endif /* #if (CRC_VERSION_INFO_API == (STD_ON)) */
  const uint8 CrcMessage8[12] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, \
                                 0x39, 0x3A, 0x3B, 0x3C
                                };
  char szString[4];
  uint8 TempUSage = 0;
  uint8 i = 0x0;
  #ifdef CRC_8_IMPLEMENTATION_MODE
  uint8 Crc8Result;
  #endif
  #ifdef CRC_8H2F_IMPLEMENTATION_MODE
  uint8 Crc8H2FResult;
  #endif
  #ifdef CRC_16_IMPLEMENTATION_MODE
  uint16 Crc16Result;
  #endif
  #ifdef CRC_32_IMPLEMENTATION_MODE
  uint32 Crc32Result;
  #endif
  #ifdef CRC_32P4_IMPLEMENTATION_MODE
  uint32 Crc32P4Result;
  #endif

  while (TempUSage != 1)
  {
    print_f("\n\n\n");
    print_f("\n/******************************************************");
    print_f("*********************/\n");
    print_f("\n\t\t\t\tCRC DRIVER TEST MENU\t\t\t\t\n");
    print_f("ENTER YOUR OPTION:\n");

    #ifdef CRC_8_IMPLEMENTATION_MODE
    print_f("\t<1>CRC Driver Demo 8bitCRC with 0x1D polynomial and ");
    print_f("%s based method  Calculations \n", CRC_8_IMPLEMENTATION_MODE);
    #endif

    #ifdef CRC_8H2F_IMPLEMENTATION_MODE
    print_f("\t<2>CRC Driver Demo 8bitCRC with 0x2F polynomial and ");
    print_f("%s based method  Calculations \n", CRC_8H2F_IMPLEMENTATION_MODE);
    #endif

    #ifdef CRC_16_IMPLEMENTATION_MODE
    print_f("\t<3>CRC Driver Demo 16bitCRC with 0x1021 polynomial and ");
    print_f("%s based method  Calculations \n", CRC_16_IMPLEMENTATION_MODE);
    #endif

    #ifdef CRC_32_IMPLEMENTATION_MODE
    print_f("\t<4>CRC Driver Demo 32bitCRC with 0x04C11DB7 polynomial and ");
    print_f("%s based method  Calculations  \n", CRC_32_IMPLEMENTATION_MODE);
    #endif

    #ifdef CRC_32P4_IMPLEMENTATION_MODE
    print_f("\t<5>CRC Driver Demo 32bitCRC with 0xF4ACFB13 polynomial and ");
    print_f("%s based method  Calculations  \n", CRC_32P4_IMPLEMENTATION_MODE);
    #endif
    #if (CRC_VERSION_INFO_API == (STD_ON))
    print_f("\t<6>CRC version information \n");
    #endif

    print_f("\t<x>Back To Main Menu\t\t\n");
    print_f("\n/******************************************************");
    print_f("*********************/\n");
    print_f("Option: ");

    getline(szString, sizeof szString - 1);

    switch (*szString)
    {
      case '1':
        #ifdef CRC_8_IMPLEMENTATION_MODE
        print_f("\n CRC Driver Demo 8bit CRC with 0x1D polynomial and ");
        print_f("%s based method selected\n", CRC_8_IMPLEMENTATION_MODE);
        print_f("input data is:\t");

        for(i = 0; i < 12; i++)
        {
          print_f("0x%x,\t", CrcMessage8[i]);
        }
        Crc8Result = Crc_CalculateCRC8(CrcMessage8, 12, 0xFF, TRUE);
        print_f("\nCrc8 with 0x1D polynomial is : 0x%x", Crc8Result);
        if(Crc8Result == 0xAF)
        {
          StartResult();
          print_f("Result = Pass;");
          EndResult();
        }
        else
        {
          StartResult();
          print_f("Result = Fail;");
          EndResult();
        }
        #endif
        break;
      case '2' :
        #ifdef CRC_8H2F_IMPLEMENTATION_MODE
        print_f("\n CRC Driver Demo 8bit CRC with 0x2F polynomial  and ");
        print_f("%s based method selected", CRC_8H2F_IMPLEMENTATION_MODE);
        print_f("\n input data is:\t");
        for(i = 0; i < 12; i++)
        {
          print_f("0x%x,\t", CrcMessage8[i]);
        }
        Crc8H2FResult = Crc_CalculateCRC8H2F(CrcMessage8, 12, 0xFF, TRUE);
        print_f("\nCrc8 with 0x2F polynomial is :0x%x", Crc8H2FResult);
        if(Crc8H2FResult == 0xBB)
        {
          StartResult();
          print_f("Result = Pass;");
          EndResult();
        }
        else
        {
          StartResult();
          print_f("Result = Fail;");
          EndResult();
        }
        #endif
        break;

      case '3' :
        #ifdef CRC_16_IMPLEMENTATION_MODE
        print_f("\nCRC Driver Demo 16bit CRC with 0x1021 polynomial and ");
        print_f("%s based method selected\n", CRC_16_IMPLEMENTATION_MODE);
        print_f("input data is:\t");
        for(i = 0; i < 12; i++)
        {
          print_f("0x%x,\t", CrcMessage8[i]);
        }
        Crc16Result = Crc_CalculateCRC16((uint8*)CrcMessage8, 12, 0xFFFF, TRUE);
        print_f("\nCrc16 with 0x1021 polynomial is :0x%x", Crc16Result);
        if(Crc16Result == 0x19BF)
        {
          StartResult();
          print_f("Result = Pass;");
          EndResult();
        }
        else
        {
          StartResult();
          print_f("Result = Fail;");
          EndResult();
        }

        #endif
        break;

      case '4' :
        #ifdef CRC_32_IMPLEMENTATION_MODE
        print_f("\nCRC Driver Demo 32bit CRC with 0x04C11DB7 polynomial ");
        print_f("and %s based method selected\n", CRC_32_IMPLEMENTATION_MODE);
        print_f("input data is:\t");
        for(i = 0; i < 12; i++)
        {
          print_f("0x%x,\t", CrcMessage8[i]);
        }

        Crc32Result = Crc_CalculateCRC32((uint8 *)CrcMessage8, 12, \
                                         0xFFFFFFFF, TRUE);
        print_f("\nCrc32 with 0x04C11DB7 polynomial is :0x%x", Crc32Result);
        if(Crc32Result == 0x4DF4ABCD)
        {
          StartResult();
          print_f("Result = Pass;");
          EndResult();
        }
        else
        {
          StartResult();
          print_f("Result = Fail;");
          EndResult();
        }
        #endif
        break;

      case '5' :
        #ifdef CRC_32P4_IMPLEMENTATION_MODE
        print_f("\nCRC Driver Demo 32bit CRC with 0xF4ACFB13 polynomial ");
        print_f("and %s based method selected\n", CRC_32P4_IMPLEMENTATION_MODE);
        print_f("input data is:\t");
        for(i = 0; i < 12; i++)
        {
          print_f("0x%x,\t", CrcMessage8[i]);
        }
        Crc32P4Result = Crc_CalculateCRC32P4((uint8 *)CrcMessage8, 12, \
                                             0xFFFFFFFF, TRUE);
        print_f("\nCrc32 with 0xF4ACFB13 polynomial is:0x%x", Crc32P4Result);
        if(Crc32P4Result == 0xFB00863F)
        {
          StartResult();
          print_f("Result = Pass;");
          EndResult();
        }
        else
        {
          StartResult();
          print_f("Result = Fail;");
          EndResult();
        }
        #endif
        break;

      case '6' :
        #if (CRC_VERSION_INFO_API == (STD_ON))
        print_f("\n CRC Version Information API Demo selected\n ");
        Crc_GetVersionInfo(&VerInfoPtr);
        print_f("\nVendor ID=%d", VerInfoPtr.vendorID);
        print_f("\nModule ID=%d", VerInfoPtr.moduleID);
        print_f("\nSW Major Version ID=%d", VerInfoPtr.sw_major_version);
        print_f("\nSW Minor Version=%d", VerInfoPtr.sw_minor_version);
        print_f("\nSW Patch Version=%d", VerInfoPtr.sw_patch_version);
        StartResult();
        print_f("Result = Pass;");
        EndResult();
        #endif
        break;
      /* Go Back to Main Menu */
      case 'x':
      case 'X':
        TempUSage = 1;
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
}/* DemoApp_CRC() */
