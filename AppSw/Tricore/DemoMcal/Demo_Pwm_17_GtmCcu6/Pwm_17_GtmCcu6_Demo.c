/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2019)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME   : Pwm_17_GtmCcu6_Demo.c                                       **
**                                                                           **
**  VERSION    : 1.0.0                                                       **
**                                                                           **
**  DATE       : 2019-04-11                                                  **
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
**                - Demo application for PWM_17_GTM driver                   **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                     **
**                                                                           **
******************************************************************************/

/******************************************************************************
**                      Includes                                             **
******************************************************************************/
#include "Std_Types.h"
#include "Pwm_17_GtmCcu6.h"
#include "Pwm_17_GtmCcu6_Demo.h"
#include "Test_Print.h"
#include "DemoApp_Cfg.h"
#include "Port.h"

/******************************************************************************
**                      Imported Compiler Switch Check                       **
******************************************************************************/

/******************************************************************************
**                      Private Macro Definitions                            **
******************************************************************************/
/* defined due to the Symbolic Name change btw AS403 and AS321 */
#ifndef PwmChannel_0
#define PwmChannel_0 Pwm_17_GtmCcu6Conf_PwmChannel_PwmChannel_0
#endif

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

/* Macros */
#define PWM_PERIOD                    (0x7999U)
#define PWM_DUTY                      (0x4000U)

/* Duty Cycle for PWM */
uint32 DutyCycle = 50U;
volatile uint16 duty = 0;
uint8 Pwm_Init_Status = 0;

/* Parameter Function for the parMenu */
/*char* pszFunction = "PWM Duty Cycle";*/
char pszFunction[20] = "PWM Duty Cycle";

/* Parameter Option For PWM : DC */
static const PAR_t Pwm_DutyCyclePar[] =
{
  {
    PAR_TYP_DEC,                    /* uwType */ /*  for configuration 1 */
    sizeof(DutyCycle),              /* uwSize */
    &DutyCycle,                     /* pvData */
    0,                              /* uwMin */
    100,                            /* uwMax */
    "DutyCycle in Percent%",        /* szText */
    "%d"                            /* szOutputFormat */
  }
};

#define PWM_17_GTMCCU6_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
#include "Pwm_17_GtmCcu6_MemMap.h"
extern const Pwm_17_GtmCcu6_ConfigType Pwm_17_GtmCcu6_Config;
#define PWM_17_GTMCCU6_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
#include "Pwm_17_GtmCcu6_MemMap.h"
/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
/*******************************************************************************
** Syntax : void Can_17_McmCan_Demo (void)                                    **
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
** Description : DemoApp for CAN driver                                       **
**                                                                            **
*******************************************************************************/
void Pwm_17_GtmCcu6_Demo(void)
{
  char szString[80];
  volatile uint8 TempUSage = 0;

  if(!Pwm_Init_Status)
  {
    Pwm_17_GtmCcu6_Init(&Pwm_17_GtmCcu6_Config);
    Pwm_Init_Status++;
  }

  while (!TempUSage)
  {
    print_f("\n\n\n");
    print_f("\n/*********************************************************/\n");
    print_f("\n                PWM DRIVER DEMOAPP MENU                   \n ");
    print_f("\n                                                          \n ");
    print_f("\n     1.  PWM: Start PWM,Default DutyCycle :50%            \n ");
    print_f("\n     2.  PWM: Enter New DutyCycle as 0 NewDC:             \n ");
    print_f("\n     3.  PWM: Stop  PWM                                   \n ");
    print_f("\n     4.  Go to Main Menu                                  \n ");
    print_f("\n     Enter Your Option ::                                 \n ");
    print_f("\n/*********************************************************/\n");
    getline(szString, sizeof szString - 1);

    switch (*szString)
    {
      case '1':
      {
        Pwm_17_GtmCcu6_StartDemo();
        break;
      }
      case '2' :
      {
        Pwm_17_GtmCcu6_ChangeDutyDemo();
        break;
      }
      case '3' :
      {
        Pwm_17_GtmCcu6_DemoDeInit();
        break;
      }
      case '4':
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
}/* Pwm_17_GtmCcu6_Demo() */

/*******************************************************************************
** Syntax : void Pwm_17_GtmCcu6_StartDemo(void)                               **
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
** Description : Enables the notification and Starts PWM with 50% duty        **
**                                                                            **
*******************************************************************************/
void Pwm_17_GtmCcu6_StartDemo(void)
{
  /* Start PWM */
  Pwm_17_GtmCcu6_SetPeriodAndDuty(PwmChannel_0, PWM_PERIOD, PWM_DUTY);
  StartResult();
  print_f("Result = Pass;");
  EndResult();

}

/*******************************************************************************
** Syntax : void Pwm_17_GtmCcu6_ChangeDutyDemo(void)                          **
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
*******************************************************************************/
void Pwm_17_GtmCcu6_ChangeDutyDemo(void)
{

  /* Change Duty Cycle Of PWM */
  /*pszFunction = "PWM Duty Cycle";*/
  if (ParMenu(&pszFunction[0],
              (PAR_t *)Pwm_DutyCyclePar,
              sizeof Pwm_DutyCyclePar / sizeof Pwm_DutyCyclePar[0]
             ) != 'q')
  {

    duty = (uint16)(((0x8000U * DutyCycle) + 50U) / 100U ) ;
  }
  /* Set the PWM Duty */
  Pwm_17_GtmCcu6_SetDutyCycle(PwmChannel_0, duty);
  StartResult();
  print_f("Result = Pass;");
  EndResult();
}


/*******************************************************************************
** Syntax : void  Pwm_17_GtmCcu6_DemoDeInit(void)                    **
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
** Description :    Pwm_17_GtmCcu6_DemoDeInit                                 **
*******************************************************************************/
void Pwm_17_GtmCcu6_DemoDeInit(void)
{
  Pwm_17_GtmCcu6_DeInit();
  StartResult();
  print_f("Result = Pass;");
  EndResult();
}
