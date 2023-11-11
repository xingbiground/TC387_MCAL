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
**  FILENAME   : Smu_Demo.c                                                  **
**                                                                           **
**  VERSION    : 0.0.1                                                       **
**                                                                           **
**  DATE       : 2017-11-14                                                  **
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
**                - Demo application for SMU driver                          **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                     **
**                                                                           **
******************************************************************************/

/******************************************************************************
**                      Includes                                             **
******************************************************************************/
#include "Smu_Demo.h"
#include "Test_Print.h"

/******************************************************************************
**                      Imported Compiler Switch Check                       **
******************************************************************************/

/******************************************************************************
**                      Private Macro Definitions                            **
******************************************************************************/

/******************************************************************************
**                      Global Constant Definitions                          **
******************************************************************************/

/******************************************************************************
**                      Global Variable Definitions                          **
******************************************************************************/
#define SMU_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
#include "Smu_MemMap.h"
extern const Smu_ConfigType Smu_Config;
#define SMU_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
#include "Smu_MemMap.h"

#define SMU_START_SEC_VAR_INIT_ASIL_B_GLOBAL_32
#include "Smu_MemMap.h"
static volatile uint8 smu_isr_status = 0xEE;
#define SMU_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_32
#include "Smu_MemMap.h"

/******************************************************************************
**                      Private Constant Definitions                         **
******************************************************************************/

/******************************************************************************
**                      Private Variable Definitions                         **
******************************************************************************/

/******************************************************************************
**                      Local Function Definitions                           **
******************************************************************************/

/*SMU ISR routine*/
IFX_INTERRUPT(SMU0_ISR, 0, 0x1)
{
  /* Enable Global Interrupts */
  ENABLE();
  smu_isr_status = 1;
  print_f("\nSMU0_ISR occured !!");
}

/*Routine to initialize the IRQ SFR */
static void IrqSmu_Init()
{
  IRQ_SFR_MODIFY32 (SRC_SMU0.U,  0xFFFFFFFF, (0x0000 | 0x1));
  IRQ_SFR_MODIFY32 (SRC_SMU1.U,  0xFFFFFFFF, (0x0000 | 0x0));
  IRQ_SFR_MODIFY32 (SRC_SMU2.U,  0xFFFFFFFF, (0x0000 | 0x0));

  SRC_SMU0.B.SRE = 1;
  SRC_SMU1.B.SRE = 0;
  SRC_SMU2.B.SRE = 0;
}

/*Routine to trigger the SW Alarm*/
static void Smu_Trigger_SW_Alarm(const uint8 AlarmNum )
{
  volatile int i;

  Mcal_WriteSafetyEndInitProtReg((uint32*)&SMU_CMD.U, ((uint32)SMU_ALARM_COMMAND | ((uint32)AlarmNum << 4)));
  for(i = 0; i < 0xFFF; i++)
  {}
}

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/

/******************************SMU-TestCases***********************************/
/******************************************************************************/
/*******************************************************************************
** Syntax : void Smu_Demo (void)                                              **
**                                                                            **
** Service ID   : NA                                                          **
**                                                                            **
** Sync/Async   : Synchronous                                                 **
**                                                                            **
** Reentrancy   : Non Reentrant                                               **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : DemoApp for SMU driver                                       **
**                                                                            **
*******************************************************************************/
void Smu_Demo(void)
{
  char szString[80];
  volatile uint8 TempUSage = 0;

  while (!TempUSage)
  {
    print_f("\n\n\n");
    print_f("\n/*********************************************************/\n");
    print_f("\n                SMU DRIVER DEMOAPP MENU                   \n ");
    print_f("\n                                                          \n ");
    print_f("     1.  Trigger SWAlarm10[0] to send the SMU Interrupt Req0\n ");
    print_f("     x.  Back To Main Menu                                  \n ");
    print_f("                                                            \n ");
    print_f("\n/*********************************************************/\n");
    print_f("  Enter Your Option :: ");

    getline(szString, sizeof szString - 1);

    switch (*szString)
    {
      case '1':
      {
        Smu_Demo1();
        break;
      }
      case 'x':
      case 'X':
        TempUSage = 1;
        break;
      default :
        print_f(" \n\n Invalid option \n ");
        StartResult();
        print_f("Result = Fail;");
        EndResult();
        break;
    }
  }
}/* SMU_Demo() */

/*******************************************************************************
** Syntax       : void Smu_Demo1(void)                                        **
**                                                                            **
** Service ID   : NA                                                          **
**                                                                            **
** Sync/Async   : Synchronous                                                 **
**                                                                            **
** Reentrancy   : Non Reentrant                                               **
**                                                                            **
** Parameters (in) : none                                                     **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value    : none                                                     **
**                                                                            **
** Timing          :                                                          **
**                                                                            **
** Description : This routine will trigger the SW alarm 0 , to generate &     **
**               verify the SMU Interrupt Request 0                           **
*******************************************************************************/
void Smu_Demo1()
{
  /*Local Variables*/
  volatile int i;
  uint32 AlarmExecStatus;

  smu_isr_status = 0;

  /*Initialize the SMU Interrupt Request0*/
  IrqSmu_Init();

  /*Initialize the Smu Config Structure*/
  Smu_Init(&Smu_Config);
  Smu_InitCheck(&Smu_Config);

  print_f("\nSwitch the FSP to the 'Fault-Free' State");
  P33_IOCR8.B.PC8 = 0x10;
  Smu_SetupErrorPin();
  Smu_ReleaseFSP();
  for(i = 0; i < 0xFFFF; i++)
  {}

  print_f("\nSwitch the SMU_Core State Machine to 'RUN' State");
  Smu_ActivateRunState(SMU_RUN_COMMAND);

  print_f("\nTrigger the Software Alarm 10[0]");
  Smu_Trigger_SW_Alarm(SMU_ALARM_0);

  /*Read the execution status of SMU IRQ0*/
  Smu_GetAlarmExecutionStatus(0, &AlarmExecStatus);
  if((AlarmExecStatus == 1) && (smu_isr_status == 1))
  {
    print_f("\nIRQ0 Request is serviced Correctly\n");
    StartResult();
    print_f("Result = Pass;");
    EndResult();
    Smu_ClearAlarmExecutionStatus(0);

  }
  else
  {
    StartResult();
    print_f("Result = Fail;");
    EndResult();
  }

  /*De-Initialize the Smu Config Structure*/
  Smu_DeInit();
}
