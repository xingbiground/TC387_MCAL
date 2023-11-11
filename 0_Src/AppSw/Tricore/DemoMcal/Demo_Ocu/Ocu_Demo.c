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
**  FILENAME   : Ocu_Demo.c                                                  **
**                                                                           **
**  VERSION    : 0.0.3                                                       **
**                                                                           **
**  DATE       : 2019-09-18                                                  **
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
**                - Demo application for Ocu driver                          **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                     **
**                                                                           **
******************************************************************************/
/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 * V0.0.1: 2019-04-09, AbMa  : Initial Version.
 * V0.0.2: 2019-08-30, GS  : MemMap warnings are Fixed for variables initialized in VAR_CLEARED section.
 * V0.0.3: 2019-09-18, GS  : User is provided with the range of input value that can be passed for reference/threshold for Relative and Absolute APIs. Code indentation is Done.
 */
/******************************************************************************
**                      Includes                                             **
******************************************************************************/
#include "Std_Types.h"
#include "Ocu.h"
#include "Ocu_Demo.h"
#include "Test_Print.h"
#include "DemoApp_Cfg.h"
#include "IfxSrc_reg.h"
#include "Port.h"
#include "Dio.h"
#include "Irq.h"

/******************************************************************************
**                      Imported Compiler Switch Check                       **
******************************************************************************/

/******************************************************************************
**                      Private Macro Definitions                            **
******************************************************************************/
/* Macros */
/*device frequency in MHz */
#define OCU_CHANNEL_DEFAULT_THRESHOLD    (123456U)
#define OCU_SRE_ENABLE (1<<10)
/******************************************************************************
**                      Private Type Definitions                             **
******************************************************************************/

/******************************************************************************
**                      Private Function Declarations                        **
******************************************************************************/
/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
static uint32 Ocu_Demo_GetParamU32(char s[]);
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

#define OCU_START_SEC_VAR_CLEARED_ASIL_B_CORE0_32
#include "Ocu_MemMap.h"

static   uint32 OcuInitStatus;
static   uint32 OcuDemoFlagForNotification;
#if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
volatile uint32 Ocu_NotificationCounterCh0;
#endif /* (OCU_NOTIFICATION_SUPPORTED == STD_ON) */

#define OCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_32
#include "Ocu_MemMap.h"

#define OCU_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
#include "Ocu_MemMap.h"
extern const Ocu_ConfigType Ocu_Config;
#define OCU_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
#include "Ocu_MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
/*******************************************************************************
** Syntax : void Ocu_Demo (void)                                              **
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
** Description : DemoApp for OCU driver                                       **
**                                                                            **
*******************************************************************************/
void Ocu_Demo(void)
{
  char szString[80];
  volatile uint8 TempUSage = 0;

  if(OcuInitStatus == 0)
  {
    Ocu_Init(&Ocu_Config);
    OcuInitStatus++;
    IrqGtm_Init();
    SRC_GTMATOM02.U |= OCU_SRE_ENABLE;
    OcuDemoFlagForNotification = 0;
  }

  while (TempUSage == 0)
  {
    print_f("\n");
    print_f("\n/***************************************************************************/    \n");
    print_f("\n                      OCU DRIVER DEMOAPP MENU                                    \n ");
    print_f("\n                                                                                 \n ");
    print_f("  OCU Channels are configured to work with 100MHZ frequency.\n ");
    print_f("  Ticks values Needs to be Entered in range 0x0U to 0xFFFFFFU. \n");
    print_f("  Notification API prints current counter ticks on Notification execution \n");
    print_f("  Notification are Disabled and channel is put to stop state in the Notification callback. \n");
    print_f("\n     1. OCU: Start OCU,Default Threshold value :123456     \n ");
    print_f("\n     2. OCU: To check Relative Threshold. \n ");
    print_f("\n     3. OCU: To check Absolute Threshold. \n ");
    print_f("\n     4. OCU: To check Ocu Pin State. \n ");
    print_f("\n     5. OCU: To check Pin Action on Compare match :         \n ");
    print_f("\n     X. Go to Main Menu                                     \n ");
    print_f("\n     Enter Your Option ::                                    \n ");
    print_f("\n/*********************************************************/  \n");
    getline(szString, sizeof (szString) - 1);

    switch (*szString)
    {
      case '1':
      {
        Ocu_StartDemo();
        break;
      }
      case '2' :
      {
        Ocu_SetRelativeDemo();
        break;
      }
      case '3' :
      {
        Ocu_SetAbsoluteDemo();
        break;
      }
      case '4':
      {
        Ocu_SetPinStateDemo();
        break;
      }
      case '5':
      {
        Ocu_SetPinActionDemo();
        break;
      }
      case 'x':
      case 'X':
        OcuInitStatus = 0;
        Ocu_DeInit();
        TempUSage = 1;
        break;
      default :
        print_f(" \n\n Invalid Option...! \n ");
        StartResult();
        print_f("\n Result = Fail;");
        EndResult();
        break;
    }
  }
}/* Ocu_Demo() */

/*******************************************************************************
** Syntax : void Ocu_StartDemo(void)                                          **
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
** Description : Start Ocu channel with 123456 threshold tick counter value   **
**                                                                            **
*******************************************************************************/
void Ocu_StartDemo(void)
{
  Ocu_ValueType Ocu_Local_Counter = 0U;
  uint8 CompareMatchEventCount = 0;
  #if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
  /*Initializing the Notification counter to 0 */
  Ocu_NotificationCounterCh0 = 0U;
  /* Enable OCU channel notifications */
  Ocu_EnableNotification(OcuConf_OcuChannel_OCU_DEMO_CHANNEL);
  #else
  print_f("\n Please Enable Notification Support and re-run \n");
  #endif /* OCU_NOTIFICATION_SUPPORTED == STD_ON */

  /* Start OCU channel */
  Ocu_StartChannel(OcuConf_OcuChannel_OCU_DEMO_CHANNEL);

  #if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
  while((Ocu_NotificationCounterCh0 == 0U) && (CompareMatchEventCount != 2) )
  {
    #if (OCU_GET_COUNTER_API == STD_ON)
    Ocu_Local_Counter = Ocu_GetCounter(OcuConf_OcuChannel_OCU_DEMO_CHANNEL);
    #else
    print_f("\n Please Enable Ocu_GetCounter API and re-run \n");
    #endif
    if((Ocu_Local_Counter > (OCU_CHANNEL_DEFAULT_THRESHOLD - 100)) && (Ocu_Local_Counter < (OCU_CHANNEL_DEFAULT_THRESHOLD + 100)) )
    {
      CompareMatchEventCount++;
    }
    /* Loop to wait until counter is incremented from the notification */
  }
  #endif /* OCU_NOTIFICATION_SUPPORTED == STD_ON */

  StartResult();
  print_f("\n Result = Pass;");
  EndResult();
}

/*******************************************************************************
** Syntax : void Ocu_SetRelativeDemo(void)                                    **
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
** Description : Set relative threshold and wait for Notification to come     **
**                                                                            **
*******************************************************************************/
void Ocu_SetRelativeDemo(void)
{
  uint32 ChannelTicksValue;
  uint8 inputValueCheck = 0;
  uint8 CompareMatchEventCount = 0;
  Ocu_ValueType Ocu_Local_Counter = 0U;
  char szString[80];
  while(inputValueCheck == 0)
  {
    print_f("\n  Enter Relative Threshold value in Ticks in the range 0x0U to 0xFFFFFFU : ");
    getline(szString, 40);
    ChannelTicksValue = (uint32) Ocu_Demo_GetParamU32(szString);
    if(ChannelTicksValue <= 0xFFFFFFU)
    {
      inputValueCheck = 1;
    }
    else
    {
      print_f("\n  value Not in range");
    }
  }
  #if (OCU_SET_RELATIVE_THRESHOLD_API == STD_ON)
  (void)Ocu_SetRelativeThreshold(OcuConf_OcuChannel_OCU_DEMO_CHANNEL, (Ocu_ValueType)ChannelTicksValue);
  #else
  print_f("\n Enable relative threshold API and Re-run \n");
  #endif

  #if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
  /*Initializing the Notification counter to 0 */
  Ocu_NotificationCounterCh0 = 0U;
  /* Enable OCU channel notifications */
  Ocu_EnableNotification(OcuConf_OcuChannel_OCU_DEMO_CHANNEL);
  #else
  print_f("\n Enable Notification Support and re-run \n");
  #endif /* OCU_NOTIFICATION_SUPPORTED == STD_ON */

  /* Start OCU channel */
  Ocu_StartChannel(OcuConf_OcuChannel_OCU_DEMO_CHANNEL);

  #if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
  while((Ocu_NotificationCounterCh0 == 0U) && (CompareMatchEventCount != 2) )
  {
    #if (OCU_GET_COUNTER_API == STD_ON)
    Ocu_Local_Counter = Ocu_GetCounter(OcuConf_OcuChannel_OCU_DEMO_CHANNEL);
    #else
    print_f("\n Please Enable Ocu_GetCounter API and re-run \n");
    #endif
    if((Ocu_Local_Counter > (ChannelTicksValue - 100)) && (Ocu_Local_Counter < (ChannelTicksValue + 100)) )
    {
      CompareMatchEventCount++;
    }
    /* Loop to wait until counter is incremented from the notification */
  }
  #endif /* OCU_NOTIFICATION_SUPPORTED == STD_ON */

  StartResult();
  print_f("\n Result = Pass;");
  EndResult();
}

/*******************************************************************************
** Syntax : void Ocu_SetAbsoluteDemo(void)                                          **
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
** Description : Set Absolute threshold and wait for Notification to come     **
**                                                                            **
*******************************************************************************/
void Ocu_SetAbsoluteDemo(void)
{
  uint32 ChannelTicksValue;
  uint32 ChannelReferenceValue;
  uint8 inputValueCheck = 0;
  uint8 CompareMatchEventCount = 0;
  Ocu_ValueType Ocu_Local_Counter = 0U;
  char szString[80];

  while(inputValueCheck == 0)
  {
    print_f("\n  Enter Reference value in Ticks in the range 0x0U to 0xFFFFFFU : ");
    getline(szString, 40);
    ChannelReferenceValue = (uint32) Ocu_Demo_GetParamU32(szString);
    print_f("\n  Enter Absolute Threshold value in Ticks in the range 0x0U to 0xFFFFFFU : ");
    getline(szString, 40);
    ChannelTicksValue = (uint32) Ocu_Demo_GetParamU32(szString);

    if((ChannelTicksValue <= 0xFFFFFFU) && (ChannelReferenceValue <= 0xFFFFFFU))
    {
      inputValueCheck = 1;
    }
    else
    {
      print_f("\n  Values Not in range \n");
    }
  }
  #if (OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON)
  (void)Ocu_SetAbsoluteThreshold(OcuConf_OcuChannel_OCU_DEMO_CHANNEL, (Ocu_ValueType)ChannelReferenceValue, (Ocu_ValueType)ChannelTicksValue);
  #else
  print_f("\n Enable Absolute threshold API and Re-run \n");
  #endif

  #if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
  /*Initializing the Notification counter to 0 */
  Ocu_NotificationCounterCh0 = 0U;
  /* Enable OCU channel notifications */
  Ocu_EnableNotification(OcuConf_OcuChannel_OCU_DEMO_CHANNEL);
  #else
  print_f("\n Enable Notification Support and re-run \n");
  #endif /* OCU_NOTIFICATION_SUPPORTED == STD_ON */

  /* Start OCU channel */
  Ocu_StartChannel(OcuConf_OcuChannel_OCU_DEMO_CHANNEL);

  #if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
  while((Ocu_NotificationCounterCh0 == 0U) && (CompareMatchEventCount != 2) )
  {
    #if (OCU_GET_COUNTER_API == STD_ON)
    Ocu_Local_Counter = Ocu_GetCounter(OcuConf_OcuChannel_OCU_DEMO_CHANNEL);
    #else
    print_f("\n Please Enable Ocu_GetCounter API and re-run \n");
    #endif
    if((Ocu_Local_Counter > (ChannelTicksValue - 2)) && (Ocu_Local_Counter < (ChannelTicksValue + 2)) )
    {
      CompareMatchEventCount++;
    }
    /* Loop to wait until counter is incremented from the notification */
  }
  #endif /* OCU_NOTIFICATION_SUPPORTED == STD_ON */

  StartResult();
  print_f("\n Result = Pass;");
  EndResult();
}

/*******************************************************************************
** Syntax : void Ocu_SetPinStateDemo(void)                                    **
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
** Description : Set the Pin state as requested for the OCU channel           **
**                                                                            **
*******************************************************************************/
void Ocu_SetPinStateDemo(void)
{

  uint8 inputValueCheck = 0;
  Ocu_PinStateType OcuPinStateInput;
  Dio_LevelType Ocu_Demo_Dio_PinLevel = 0U;
  char szString[80];
  while(inputValueCheck == 0)
  {
    print_f("\n  Enter Pin State to be set 0(LOW) and 1(HIGH) : ");
    getline(szString, 40);
    OcuPinStateInput = (Ocu_PinStateType) Ocu_Demo_GetParamU32(szString);

    if((OcuPinStateInput == 0U) ||  (OcuPinStateInput == 1U))
    {
      inputValueCheck = 1;
    }
    else
    {
      print_f("\n  Values Not in range");
    }
  }
  #if (OCU_SET_PIN_STATE_API == STD_ON)
  Ocu_SetPinState(OcuConf_OcuChannel_OCU_DEMO_CHANNEL, OcuPinStateInput);
  #else
  print_f("\n Enable SetPinState API and Re-run \n");
  #endif
  Ocu_Demo_Dio_PinLevel = Dio_ReadChannel(DioConf_DioChannel_OCU_CHANNEL_PIN);
  if(Ocu_Demo_Dio_PinLevel == 0U)
  {
    print_f("\n PinState Set to 0(LOW) : %d  \n", Ocu_Demo_Dio_PinLevel);
  }
  else
  {
    print_f("\n PinState Set to 1(HIGH) : %d  \n", Ocu_Demo_Dio_PinLevel);
  }

  StartResult();
  print_f("\n Result = Pass;");
  EndResult();
}

/*******************************************************************************
** Syntax : void Ocu_SetPinActionDemo(void)                                    **
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
** Description : Set Pin Action Requested                                     **
**                                                                            **
*******************************************************************************/
void Ocu_SetPinActionDemo(void)
{
  uint8 inputValueCheck = 0;
  Ocu_PinActionType OcuChannelPinAction = OCU_SET_HIGH;
  Dio_LevelType Ocu_Demo_Dio_PinLevel = 0U;
  /* flag to notify the Demo API is executing */
  OcuDemoFlagForNotification = 1U;
  char szString[80];
  /* Getting current Pin State of OCU channel */
  Ocu_Demo_Dio_PinLevel = Dio_ReadChannel(DioConf_DioChannel_OCU_CHANNEL_PIN);
  while(inputValueCheck == 0)
  {
    print_f("\n 2 Continuous compare match event with 2000 Ticks Relative threshold programmed to see Toggle.");
    print_f("\n Current Pin State is : %d ", Ocu_Demo_Dio_PinLevel);
    print_f("\n Enter Pin Action for Compare Match 0(DISABLE), 1(HIGH), 2(LOW), 3(TOGGLE): ");
    getline(szString, 40);
    OcuChannelPinAction = (Ocu_PinActionType) Ocu_Demo_GetParamU32(szString);
    if(OcuChannelPinAction < 4)
    {
      inputValueCheck = 1;
    }
    else
    {
      print_f("\n  Value Not in range \n");
    }
  }
  #if (OCU_SET_PIN_ACTION_API == STD_ON)
  Ocu_SetPinAction(OcuConf_OcuChannel_OCU_DEMO_CHANNEL, OcuChannelPinAction);
  #else
  print_f("\n Enable SetPinAction API and Re-run \n");
  #endif

  #if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
  /*Initializing the Notification counter to 0 */
  Ocu_NotificationCounterCh0 = 0U;
  /* Enable OCU channel notifications */
  Ocu_EnableNotification(OcuConf_OcuChannel_OCU_DEMO_CHANNEL);
  #else
  print_f("\n Enable Notification Support and re-run \n");
  #endif /* OCU_NOTIFICATION_SUPPORTED == STD_ON */

  #if (OCU_SET_RELATIVE_THRESHOLD_API == STD_ON)
  (void)Ocu_SetRelativeThreshold(OcuConf_OcuChannel_OCU_DEMO_CHANNEL, (Ocu_ValueType)2000);
  #else
  print_f("\n Enable relative threshold API and Re-run \n");
  #endif

  /* Start OCU channel */
  Ocu_StartChannel(OcuConf_OcuChannel_OCU_DEMO_CHANNEL);

  #if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
  while((Ocu_NotificationCounterCh0 < 3U))
  {
    /* Wait for 2 events to occur */
  }
  #endif /* OCU_NOTIFICATION_SUPPORTED == STD_ON */

  StartResult();
  print_f("\n Result = Pass;");
  EndResult();
}


#if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
/*******************************************************************************
** Syntax : void  Ocu_Notification_Channel0(void)                             **
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
** Description :    The Notification API getting called on each compare match **
**                  event of OCU channel.                                     **
*******************************************************************************/
void Ocu_Notification_Channel0 (void)
{
  Ocu_ValueType CurrentOcuCounterValue = 0;
  Dio_LevelType Ocu_Demo_Dio_PinLevel = 0U;
  Ocu_NotificationCounterCh0++;

  #if (OCU_GET_COUNTER_API == STD_ON)
  CurrentOcuCounterValue = Ocu_GetCounter(OcuConf_OcuChannel_OCU_DEMO_CHANNEL);
  #endif
  /* printing the counter value when OCU Notification is executed */
  print_f(" \n Ocu Notification API called at  = %d    ticks \n", CurrentOcuCounterValue);
  if((Ocu_NotificationCounterCh0 == 1) && (OcuDemoFlagForNotification != 1))
  {
    #if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
    Ocu_DisableNotification(OcuConf_OcuChannel_OCU_DEMO_CHANNEL);
    #endif
    Ocu_StopChannel(OcuConf_OcuChannel_OCU_DEMO_CHANNEL);
    print_f(" \n  Channel is Stopped. \n");
  }
  else
  {
    Ocu_Demo_Dio_PinLevel = Dio_ReadChannel(DioConf_DioChannel_OCU_CHANNEL_PIN);
    if(Ocu_Demo_Dio_PinLevel == 0U)
    {
      print_f("\n PinState Set to 0(LOW) : %d  \n", Ocu_Demo_Dio_PinLevel);
    }
    else
    {
      print_f("\n PinState Set to 1(HIGH) : %d  \n", Ocu_Demo_Dio_PinLevel);
    }
    (void)Ocu_SetRelativeThreshold(OcuConf_OcuChannel_OCU_DEMO_CHANNEL, (Ocu_ValueType)2000);
    if(Ocu_NotificationCounterCh0 == 3)
    {
      #if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
      Ocu_DisableNotification(OcuConf_OcuChannel_OCU_DEMO_CHANNEL);
      #endif
      Ocu_StopChannel(OcuConf_OcuChannel_OCU_DEMO_CHANNEL);
      OcuDemoFlagForNotification = 0;
      print_f(" \n  Channel is Stopped. \n");
    }
  }
}
#endif /* OCU_NOTIFICATION_SUPPORTED == STD_ON */

/*******************************************************************************
** Syntax : uint32 Ocu_Demo_GetParamU32(char s[])                             **
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
** Description :    API for getting the input data extract from string of     **
**                  console.                                                  **
*******************************************************************************/
static uint32 Ocu_Demo_GetParamU32(char s[])
{
  uint32 i, n;
  n = 0U;

  for (i = 0U; (s[i] >= '0') && (s[i] <= '9'); ++i)
  {
    n = 10 * n + (s[i] - '0');
  }

  return n;
}
