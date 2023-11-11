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
**  FILENAME   : DsAdc_Demo.c                                                **
**                                                                           **
**  VERSION    : 0.0.1                                                       **
**                                                                           **
**  DATE       : 2016-02-08                                                  **
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
**                - Demo application for DSADC driver                        **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                     **
**                                                                           **
******************************************************************************/
/******************************************************************************
**                      Includes                                             **
******************************************************************************/
#include "Std_Types.h"
#include "Dsadc.h"
#include "Test_Print.h"
#include "Test_Time.h"
#include "Irq.h"

/* Inclusion of Tasking sfr file */
#include "IfxScu_reg.h"
#include "IfxStm_reg.h"
#include "IfxSrc_reg.h"
#include "Mcal_Compiler.h"
#include "IFX_Os.h"
#include "Ifx_Ssw_Infra.h"
#include "Mcu.h"
#include "IfxSrc_reg.h"
#include "IfxEdsadc_bf.h"
#include "Mcu_17_TimerIp.h"
#include "Dsadc_Demo.h"
/******************************************************************************
**                      Imported Compiler Switch Check                       **
******************************************************************************/
/*****************************************************************************
**                      Private Macro Definitions                            **
******************************************************************************/

/******************************************************************************
**                      Private Type Definitions                             **
******************************************************************************/
/******************************************************************************
**                      Private Function Declarations                        **
******************************************************************************/
void Timer_Delayus(uint32 ReqTimeus );
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
#define TEST_DSADC_INTRPT_EN       		(unsigned int)0x01 
volatile uint16 TestResult;
Std_ReturnType Dsadc_StrtModStatus ;
static sint16 User_Buffer[100],User_Buffer1[100];
Std_ReturnType PosDelayStatus, NegDelayStatus;
Std_ReturnType StartModRetA, StartDemodRetA;
Std_ReturnType ResEvRetA=E_NOT_OK;
Std_ReturnType ResultRetA;
Std_ReturnType CalibRetA;

uint8 TempUSage = 0U;
uint8 u8l_TestDsadc1stHwCh  = 0;
uint32 count = 0;

/********************************Beginning**************************************
 **                      Test_DsAdc Notification Function Definitions         **
*******************************************************************************/
void TestDsAdc_NewResultNotification(void){
  print_f("Demo App New Result Notification came ...\n ");
  Dsadc_DisableNotifications(0);
}

void TestDsAdc_BufferFullNotification (void)
{
  print_f("Demo App Buffer full Notification came ...\n ");
  Dsadc_DisableNotifications(0);
}

/******************************************************************************
**                      Global Function Definitions                          **
******************************************************************************/
/******************************************************************************
** Syntax : void Dsadc_SWDemo(void)                                          **
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
** Description : This routine will demonstarte the features of DSADC         **
**               as per the options. Channel0 and channel1 is being          **
**               used to show the following features of DSADC                **
**               1. Conversion Result of Channel0 with timestamp             **
**               2. Generating carrier signal in triangular/Sine/Square      **
**                  waveform                                                 **
******************************************************************************/
void Dsadc_Demo(void)
{
    char szString[4U];
  u8l_TestDsadc1stHwCh = 0;
  IrqDsadc_Init();
  SRC_DSADCSRM0.B.SRE = TEST_DSADC_INTRPT_EN; 
  Dsadc_Init(&Dsadc_Config);
  Timer_DelayMs(5);
  Dsadc_StartCalibration(u8l_TestDsadc1stHwCh);
  Timer_DelayMs(5);
  Dsadc_GetCalibrationStatus(u8l_TestDsadc1stHwCh);
  Timer_DelayMs(5);
      
    while (TempUSage != 1U)
      {
      print_f("\n\n");
    print_f("\n/********************************************************");
    print_f("******************/                                      \n");
    print_f("\n                  DSADC DRIVER DEMOAPP MENU            \n");
    print_f("                ENTER YOUR CHOICE FROM BELOW MENU:       \n");
    print_f("     < 1 > Start DSADC conversion result for Channel A  \n");
    print_f("     < 2 > Stop Conversion for channel A                 \n");
    print_f("     < 3 > Read OR Display Current Channel Status         \n");
    print_f("     < x > Go back to main menu                          \n");
    print_f("Enter Your Option: ");

  getline(szString, sizeof szString - 1);

  switch (*szString)
  {
    case '1':
    {
      Dsadc_SetupResultBuffer(u8l_TestDsadc1stHwCh,User_Buffer1,10);
      Dsadc_StrtModStatus = Dsadc_StartModulation(u8l_TestDsadc1stHwCh);
      print_f("\n start modulation %d \n",TestResult);
     // while(DSADC_RESULT_READY != Dsadc_GetStatus(u8l_TestDsadc1stHwCh));
      Timer_DelayMs(10);
      TestResult = Dsadc_GetStatus(u8l_TestDsadc1stHwCh);
      print_f("\n Dsadc_GetStatus  %d \n",TestResult);
      TestResult = Dsadc_ReadStreamResults(u8l_TestDsadc1stHwCh,&User_Buffer[0]);
      print_f("\n Conversion Result is %d \n",User_Buffer[0]);
      Timer_DelayMs(1);
	  if ((Dsadc_StrtModStatus == E_OK)&& (TestResult > 0U) && (TestResult < 65535U))
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
    }
    case '2':
    {
      TestResult = Dsadc_StopModulation(u8l_TestDsadc1stHwCh);
      print_f("\n stop modulation %d \n",TestResult);
	  if (TestResult == E_OK)
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
    }
    case '3':
    {
	  Dsadc_SetupResultBuffer(u8l_TestDsadc1stHwCh,User_Buffer1,10);
      TestResult = Dsadc_StartModulation(u8l_TestDsadc1stHwCh);
      TestResult = Dsadc_GetStatus(u8l_TestDsadc1stHwCh);
      print_f("\n Dsadc_GetStatus  %d \n",TestResult);
	  if (TestResult == DSADC_BUSY)
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
    }
      /* Go Back to Main Menu */
    case 'x':
    case 'X':
    TempUSage = 1U;
    break;
    
    default :
    {
        print_f("\n  Go Back to Main Menu \n ");
        print_f("\n Invalid Option Chosen \n ");
        TempUSage = 1U;
      break;
    }
  }

}
return;
} /* Dsadc_Demo */

/*****************************************************************************
This is a modified function with reference from Test_time.c. This adds up delay
 in microseconds instead of milli senconds as given in Test_time.c
*****************************************************************************/
void Timer_Delayus(uint32 ReqTimeus )
{
    volatile uint32 ReadStm;
    uint32 Delay_Count, Delay_Compare_Count;

    Delay_Count = Get_Counter_Value(ReqTimeus,US);

    Delay_Compare_Count = Delay_Count + STM0_TIM0.U;

    ReadStm = STM0_TIM0.U;

    while( Delay_Compare_Count >= ReadStm)
    {
        ReadStm = STM0_TIM0.U;
    }
}
