/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2020)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME   : Lin_17_AscLin_Demo.c                                        **
**                                                                           **
**  VERSION    : 3.0.0                                                       **
**                                                                           **
**  DATE       : 2020-08-14                                                  **
**                                                                           **
**  VARIANT    : NA                                                          **
**                                                                           **
**  PLATFORM   : Infineon AURIX2G                                            **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION : Demo application for LIN module                            **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: yes                                     **
**                                                                           **
******************************************************************************/

/******************************************************************************
**                      Includes                                             **
******************************************************************************/
#include "Std_Types.h"
#include "Test_Print.h"
#include "Test_Time.h"
#include "Irq.h"
#include "Lin_17_AscLin.h"
#include "Lin_17_AscLin_Demo.h"
#include "DemoApp_Cfg.h"
#include "IfxCpu_reg.h"
#include "IfxSrc_reg.h"
#include "IfxSrc_bf.h"

#define MAX_WAIT_LOOP           (0xFFF0)
#define LIN_CHANNELID0_CONFIG0  (0U)
#define LIN_SRC_SET_SRE         (1U)
#define LIN_OPERATIONAL         (9U)
#define LIN_CH_SLEEP            (10U)

/*******************************************************************************
**                      Private Variable Declarations                         **
*******************************************************************************/

#define LIN_17_ASCLIN_START_SEC_VAR_INIT_QM_GLOBAL_U8
#include "Lin_17_AscLin_MemMap.h"
uint8 UserData[8] = {0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55};
#define LIN_17_ASCLIN_STOP_SEC_VAR_INIT_QM_GLOBAL_U8
#include "Lin_17_AscLin_MemMap.h"

#define LIN_17_ASCLIN_START_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
#include "Lin_17_AscLin_MemMap.h"
extern const Lin_17_AscLin_ConfigType Lin_17_AscLin_Config;
#define LIN_17_ASCLIN_STOP_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
#include "Lin_17_AscLin_MemMap.h"

volatile uint8 *SlaveSduPtr = UserData;
uint8 Lin_Init_Status;
/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
static Lin_StatusType Lin_GoToSleepDemo(void);
static Lin_StatusType Lin_GoToSleepInternalDemo(void);
static Lin_StatusType Lin_WakeupDemo(void);
static Lin_StatusType Lin_GoToSleepInternalDemo(void);
static void Lin_EnableServiceRequest(void);

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/

static Lin_StatusType Lin_GoToSleepDemo(void)
{
  Lin_StatusType retval;
  uint32 WaitLoop;

  Lin_17_AscLin_GoToSleep(LIN_CHANNELID0_CONFIG0);
  WaitLoop = 0;
  while( (LIN_CH_SLEEP != (Lin_17_AscLin_GetStatus(LIN_CHANNELID0_CONFIG0, (uint8 **)&SlaveSduPtr))) && (WaitLoop < MAX_WAIT_LOOP))
  {
    WaitLoop++;
  };

  if(WaitLoop == MAX_WAIT_LOOP)
  {
    print_f("Sleep command is not sent within given time interval %d \n", WaitLoop);
  }
  else
  {
    print_f("LIN channel is set to SLEEP state\n");
  }
  
  retval = Lin_17_AscLin_GetStatus(LIN_CHANNELID0_CONFIG0, (uint8 **)&SlaveSduPtr);
  return retval;
}

static Lin_StatusType Lin_GoToSleepInternalDemo(void)
{
  Lin_StatusType retval;
  uint32 WaitLoop = 0;
  /* Internal Sleep : Lin_GoToSleepInternal */
  Lin_17_AscLin_GoToSleepInternal(LIN_CHANNELID0_CONFIG0);
  while( (LIN_CH_SLEEP != (Lin_17_AscLin_GetStatus(LIN_CHANNELID0_CONFIG0, (uint8 **)&SlaveSduPtr))) && (WaitLoop < MAX_WAIT_LOOP))
  {
    WaitLoop++;
  };
  retval = Lin_17_AscLin_GetStatus(LIN_CHANNELID0_CONFIG0, (uint8 **)&SlaveSduPtr);
  return retval;
}

static Lin_StatusType Lin_WakeupDemo(void)
{
  Lin_StatusType retval;
  uint32 WaitLoop = 0;
  /* Send Wakeup : Lin_17_AscLin_Wakeup */
  Lin_17_AscLin_Wakeup(LIN_CHANNELID0_CONFIG0);
  while( (LIN_OPERATIONAL != (Lin_17_AscLin_GetStatus(LIN_CHANNELID0_CONFIG0, (uint8 **)&SlaveSduPtr))) && (WaitLoop < MAX_WAIT_LOOP))
  {
    WaitLoop++;
  };
  retval = Lin_17_AscLin_GetStatus(LIN_CHANNELID0_CONFIG0, (uint8 **)&SlaveSduPtr);
  return retval;
}

static Lin_StatusType Lin_WakeupInternalDemo(void)
{
  Lin_StatusType retval;
  uint32 WaitLoop = 0;
  /* Validate WakeupInternal - Lin_17_AscLin_WakeupInternal */
  Lin_17_AscLin_WakeupInternal(LIN_CHANNELID0_CONFIG0);
  while( (LIN_OPERATIONAL != (Lin_17_AscLin_GetStatus(LIN_CHANNELID0_CONFIG0, (uint8 **)&SlaveSduPtr))) && (WaitLoop < MAX_WAIT_LOOP))
  {
    WaitLoop++;
  };
  retval = Lin_17_AscLin_GetStatus(LIN_CHANNELID0_CONFIG0, (uint8 **)&SlaveSduPtr);
  return retval;
}

/*******************************************************************************
** Syntax : void Lin_17_AscLin_Demo(void)                                     **
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
** Description : DemoApp for LIN driver                                       **
*******************************************************************************/
void Lin_17_AscLin_Demo(void)
{
  char szString[80];
  int loopvar = 0;
  Lin_StatusType retval;
  if(!Lin_Init_Status)
  {
    IrqAsclin_Init();
    Lin_EnableServiceRequest();
    Lin_17_AscLin_Init(&Lin_17_AscLin_Config);
    #if(MCAL_AR_VERSION == MCAL_AR_440)
    Lin_17_AscLin_WakeupInternal(LIN_CHANNELID0_CONFIG0);
    #endif
    Lin_Init_Status++;
  }

  print_f("\n---------------  Start of LIN driver demo ---------------\n");

  do {
    print_f("\n---------------  LIN driver Demo Menu---------------\n");
    print_f("\n  1: Set LIN channel to SLEEP state : Lin_GoToSleep");
    print_f("\n  2: Set LIN channel to OPERATIONAL state : Lin_WakeUp");
    print_f("\n  3: Internal Sleep : Lin_GoToSleepInternal ");
    print_f("\n  4: Internal WakeUp : Lin_WakeupInternal ");
    print_f("\n  <.>Back To Main Menu");
    print_f("\n Enter Your Option:  ");
    getline(szString, sizeof szString - 1);
    print_f("\n");

    switch (*szString)
    {
      case '1':
      {
        retval = Lin_GoToSleepDemo();
        if (retval == LIN_CH_SLEEP)
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
        break;
      }
      case '2':
      {
        retval = Lin_WakeupDemo();
        if (retval == LIN_OPERATIONAL)
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
        break;
      }
      
      case '3':
      {
        retval = Lin_GoToSleepInternalDemo();
        if (retval == LIN_CH_SLEEP)
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
        break;
      }
      case '4':
      {
        retval = Lin_WakeupInternalDemo();
        if (retval == LIN_OPERATIONAL)
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
        break;
      }
      case '.':
      {
        loopvar = 1;
        break;
      }
    }
  } while(loopvar == 0);
  
} /* end of LIN driver demo */

/*******************************************************************************
**                  Lin_EnableServiceRequest                                  **
*******************************************************************************/
static void Lin_EnableServiceRequest()
{
  SRC_ASCLIN1TX.B.SRE = LIN_SRC_SET_SRE;
  SRC_ASCLIN1RX.B.SRE = LIN_SRC_SET_SRE;
  SRC_ASCLIN1ERR.B.SRE = LIN_SRC_SET_SRE;
}
