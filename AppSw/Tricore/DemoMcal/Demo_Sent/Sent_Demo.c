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
**  FILENAME   : Sent_Demo.c                                                 **
**                                                                           **
**  VERSION    : 1.0.0                                                       **
**                                                                           **
**  DATE       : 2019-08-06                                                  **
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
**                - Demo application for SENT driver                         **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                     **
**                                                                           **
******************************************************************************/

/******************************************************************************
**                      Includes                                             **
******************************************************************************/
#include "Std_Types.h"
#include "Sent_Types.h"
#include "IfxSrc_reg.h"
#include "Test_Time.h"
#include "Test_Print.h"
#include "Irq.h"
#include "DemoApp_Cfg.h"
#include "Sent_Demo.h"
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
static void Sent_PollingHandler (void);
static void printChanState (Sent_ChanStateType State);
static uint32 getParamU32(char s[]);
static void Sent_StartChannelDemo(uint8 ChannelId);
static void Sent_ParseSensorData(uint32 Data);
const uint8 RangeValTable[4] = {200, 100, 50, 0};

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
Sent_ChanStatusType Sent_Stat;
uint32 Sent_RxData[SENT_HW_MAX_CHANNELS];
#if (SENT_SPC_USED == STD_ON)
Sent_SpcType Sent_Spc;
#endif
uint8 Sent_RxOverflowFlag[SENT_HW_MAX_CHANNELS];
uint8 Sent_TxUnderflowFlag[SENT_HW_MAX_CHANNELS];
uint8 Sent_ProtocolErrFlag[SENT_HW_MAX_CHANNELS];
uint8 Sent_WdgErrFlag[SENT_HW_MAX_CHANNELS];
uint8 Sent_TxSuccessFlag[SENT_HW_MAX_CHANNELS];
uint8 IgnoreCount = 0U;
uint8 AllowMenuPrint = 0U;
uint8 Sent_Init_Status = 0;

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
** Syntax : void Sent_Demo(void)                                              **
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
** Description : Demo App for SENT driver                                     **
**                                                                            **
*******************************************************************************/
void Sent_Demo(void)
{
  char szString[4];
  uint8 TempUSage = 0;

  if(!Sent_Init_Status)
  {
    IrqSent_Init();
    IrqStm_Init();

    /* Enable the SENT interrupt */
    MODULE_SRC.SENT.SENT[0].SR.B.SRE = 1U;
    MODULE_SRC.SENT.SENT[1].SR.B.SRE = 1U;

    /* Enable the STM interrupt */
    SRC_STM0SR1.B.SRE = 1;

    Sent_Init(&Sent_Config);

    Sent_Init_Status++;
  }
  /* Sent_PollingHandler to be called at 1ms at 100MHz */
  Test_Time_SetAlarm(1, 0, 1000, Sent_PollingHandler);

  while (TempUSage != 1U)
  {
    print_f("\n\n\n");
    print_f("\n/*********************************************************/\n");
    print_f("\n                SENT DRIVER DEMO APP                      \n ");
    print_f("\n                                                          \n ");
    print_f("     A.  Start Sent DemoApp                                 \n ");
    print_f("     x.  Back To Main Menu                                  \n ");
    print_f("                                                            \n ");
    print_f("\n/*********************************************************/\n");
    print_f("  Enter Your Option : ");

    getline(szString, sizeof (szString - 1));

    switch (*szString)
    {
      case 'a':
      case 'A':
      {
        uint8 ChannelId = 0U;

        print_f("\n  Enter Channel Num : ");
        getline(szString, 4);
        ChannelId = (uint8) getParamU32(szString);
        Sent_StartChannelDemo(ChannelId);
        break;
      }
      case 'x':
      case 'X':
        TempUSage = 1;
        break;
      default :
        print_f(" \n\n Invalid option \n ");
        break;
    }
  }

}

/*******************************************************************************
** Syntax : void Sent_StartChannelDemo(uint8 ChannelId)                       **
**                                                                            **
** Service ID:   : NA                                                         **
**                                                                            **
** Sync/Async:   : Synchronous                                                **
**                                                                            **
** Reentrancy:   : Non Reentrant                                              **
**                                                                            **
** Parameters (in): ChannelId - SENT logical channel number                   **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : API for Start Sent Channel Demo with configured Channel ID   **
**                                                                            **
*******************************************************************************/
static void Sent_StartChannelDemo(uint8 ChannelId)
{
  char szString[20];
  uint8 TempUSage = 0;

  while (TempUSage != 1U)
  {
    print_f("\n");
    print_f("\n/**************For Channel Id: %d*****************", ChannelId);
    print_f("\n/*********************************************************/\n");
    print_f("     1.  Enable SENT Channel                               \n");
    print_f("     2.  Disable SENT Channel                               \n");
    print_f("     3.  Get SENT Channel Data                              \n");
    print_f("     4.  Get SENT Channel Status                            \n");
    #if (SENT_SPC_USED == STD_ON)
    print_f("     5.  Start SPC Sync Master Pulse                        \n");
    #endif
    print_f("     x.  Back To SENT Main Menu                             \n");
    print_f("                                                            \n");
    print_f("\n/*********************************************************/\n");
    print_f("  Enter Your Option : ");

    AllowMenuPrint = 1U;

    getline(szString, sizeof (szString - 1));

    switch (*szString)
    {
      case '1':
      {
        Sent_SetChannel(ChannelId, SENT_ENABLE);
        IgnoreCount = 1U;
        break;
      }
      case '2' :
      {
        Sent_SetChannel(ChannelId, SENT_DISABLE);
        break;
      }
      case '3' :
      {
        print_f("\nSENT Channel Data: %x\n", Sent_RxData[ChannelId]);
        Sent_ParseSensorData(Sent_RxData[ChannelId]);
        break;
      }
      case '4' :
      {
        Sent_ReadChannelStatus(ChannelId, &Sent_Stat);
        print_f("\nSENT Channel State: ");
        printChanState (Sent_Stat.ChanStat);
        print_f("\nSENT Channel Timestamp: %x\n", Sent_Stat.RxTimeStamp);
        break;
      }
      #if (SENT_SPC_USED == STD_ON)
      case '5' :
      {
        Sent_Spc.Mode = SYNC_MODE;
        Sent_Spc.TriggerSource = PULSE_START_IMMED;
        Sent_Spc.TimeBase = PULSE_NOMINAL_FREQ;
        Sent_Spc.PulseLength = 3;
        Sent_Spc.Delay = 3;
        Sent_SpcGenPulse(ChannelId, &Sent_Spc);
        print_f("\nSENT Channel Data: %x\n", Sent_RxData[ChannelId]);
        Sent_ParseSensorData(Sent_RxData[ChannelId]);
        break;
      }
      #endif
      case 'x':
      case 'X':
        TempUSage = 1;
        break;
      default :
        print_f(" \n\n Invalid option \n ");
        break;
    }

    AllowMenuPrint = 0U;
  }

}

/*******************************************************************************
** Syntax : void Sent_PollingHandler (void)                                   **
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
** Description : API for checking Sent Channel events in Polling mode         **
**                                                                            **
*******************************************************************************/
static void Sent_PollingHandler (void)
{
  uint32 ChannelId;

  if (IgnoreCount > 0)
  {
    IgnoreCount--;
  }

  if (AllowMenuPrint == 0)
  {
    return;
  }

  for (ChannelId = 0; ChannelId < SENT_HW_MAX_CHANNELS; ChannelId++)
  {
    if (Sent_RxOverflowFlag[ChannelId] == 1U)
    {
      Sent_RxOverflowFlag[ChannelId] = 0;
      print_f("\nSENT Channel %d RX OVERFLOW occurred\n", ChannelId);
    }

    if (Sent_TxSuccessFlag[ChannelId] == 1U)
    {
      Sent_TxSuccessFlag[ChannelId] = 0;
      print_f("\nSENT Channel %d TX Transmit success occurred\n", ChannelId);
    }

    if (Sent_TxUnderflowFlag[ChannelId] == 1U)
    {
      Sent_TxUnderflowFlag[ChannelId] = 0;
      print_f("\nSENT Channel %d TX UNDERFLOW occurred\n", ChannelId);
    }

    if (Sent_ProtocolErrFlag[ChannelId] == 1U)
    {
      Sent_ProtocolErrFlag[ChannelId] = 0;
      print_f("\nSENT Channel %d protocol error occurred\n", ChannelId);
    }

    if (Sent_WdgErrFlag[ChannelId] == 1U)
    {
      Sent_WdgErrFlag[ChannelId] = 0;
      print_f("\nSENT Channel %d Watchdog error occurred\n", ChannelId);
    }
  }
}

/*******************************************************************************
** Syntax : Sent_DemoAppCbk (Sent_ChannelIdxType ChannelId,                   **
**                                         Sent_NotifType Stat)               **
**                                                                            **
** Service ID:   : NA                                                         **
**                                                                            **
** Sync/Async:   : Synchronous                                                **
**                                                                            **
** Reentrancy:   : Non Reentrant                                              **
**                                                                            **
** Parameters (in): ChannelId - SENT logical channel number                   **
**                  Stat - Interrupt Status                                   **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : API for checking Sent Channel events in interrupt mode       **
**                                                                            **
*******************************************************************************/
void Sent_DemoAppCbk (Sent_ChannelIdxType ChannelId, Sent_NotifType Stat)
{
  uint16 IntFlagEnabled;

  IntFlagEnabled = (uint16)Stat;

  while (IntFlagEnabled)
  {
    /* Loop through all the enabled bits */
    switch (IntFlagEnabled & ((uint16)~(IntFlagEnabled - 1U)))
    {
      case SENT_INT_RDI_EVENT:
        /* Ignore RDI bit, useful only when Frame Length is greater than
         * 8 nibbles since it can indicate that end of frame
         */
        break;
      case SENT_INT_RSI_EVENT:
        Sent_RxData[ChannelId] = Sent_ReadData(ChannelId);
        break;

      case SENT_INT_RBI_EVENT:
        Sent_RxOverflowFlag[ChannelId] = 1U;
        break;

        #if (SENT_SPC_USED == STD_ON)
      case SENT_INT_TDI_EVENT:
        Sent_TxSuccessFlag[ChannelId] = 1U;
        break;

      case SENT_INT_TBI_EVENT:
        /* If Transmit successful, then ignore Underflow since it is expected
         * in our SPC use case
         */
        if (Sent_TxSuccessFlag[ChannelId] == 0U)
        {
          Sent_TxUnderflowFlag[ChannelId] = 1U;
        }
        break;

        #endif /* SENT_SPC_USED == STD_ON */

      case SENT_INT_SDI_EVENT:
        /* Do nothing since no sensor usecase */
        break;

      case SENT_INT_WDI_EVENT:
        /* Ignore since sensor would be already sending some data */
        if (IgnoreCount == 0)
        {
          Sent_WdgErrFlag[ChannelId] = 1U;
        }
        break;

      case SENT_TRANS_INPROGRESS_EVENT:
        /* Do nothing */
        break;

      default:
        /* Any other will be flagged as protocol error */
        /* Ignore since sensor would be already sending some data */
        if (IgnoreCount == 0)
        {
          Sent_ProtocolErrFlag[ChannelId] = 1U;
        }
        break;
    } /* end of switch */

    /* Clear the rightmost bit */
    IntFlagEnabled &= (IntFlagEnabled - 1U);
  }; /* end of while */
}

/*******************************************************************************
** Syntax : void printChanState (Sent_ChanStateType State)                    **
**                                                                            **
** Service ID:   : NA                                                         **
**                                                                            **
** Sync/Async:   : Synchronous                                                **
**                                                                            **
** Reentrancy:   : Non Reentrant                                              **
**                                                                            **
** Parameters (in): State - Channel Status                                    **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description :                                                              **
**                                                                            **
*******************************************************************************/
static void printChanState (Sent_ChanStateType State)
{
  switch (State)
  {
    case SENT_STOP:
      print_f("STOP\n");
      break;

    case (Sent_ChanStateType) SENT_INITIALIZED:
      print_f("INITIALIZED\n");
      break;

    case SENT_RUNNING:
      print_f("RUNNING\n");
      break;

    case SENT_SYNCHRONIZED:
      print_f("SYNCHRONIZED\n");
      break;
  }
}

/*******************************************************************************
** Syntax : uint32 getParamU32(char s[])                                      **
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
** Description : API for getting the input data extract from string of        **
**               console                                                      **
*******************************************************************************/
static uint32 getParamU32(char s[])
{
  uint32 i, n;

  n = 0U;

  for (i = 0U; ((s[i] >= '0') && (s[i] <= '9')); ++i)
  {
    n = 10 * n + (s[i] - '0');
  }

  return n;
}

/*******************************************************************************
** Syntax :  void Sent_ParseSensorData(uint32 Data)                           **
**                                                                            **
** Service ID:   : NA                                                         **
**                                                                            **
** Sync/Async:   : Synchronous                                                **
**                                                                            **
** Reentrancy:   : Non Reentrant                                              **
**                                                                            **
** Parameters (in): Data - Data read from the Sent Channel                    **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value: none                                                         **
**                                                                            **
** Description : API for calculating Temperature Sensor value from            **
**               Sent_ReadData                                                **
*******************************************************************************/
static void Sent_ParseSensorData(uint32 Data)
{
  uint16 Temperature = 0;

  Data = (((Data & 0x00FFFFF0)>>20) | ((Data <<4) & 0x00FFFFFF));
  Temperature = ((uint16)((Data >> 16) & 0x00FF) - 55);

  print_f("\nTemperature data T = %d DegreeC", Temperature);
}

/* Call-out function for Channel 0 */
void Sent_Callout_Chan0 (Sent_ChannelIdxType ChannelId, Sent_NotifType Stat)
{
  Sent_DemoAppCbk(ChannelId, (uint32) Stat);
}

/* Call-out function for Channel 1 */
void Sent_Callout_Chan1 (Sent_ChannelIdxType ChannelId, Sent_NotifType Stat)
{
  Sent_DemoAppCbk(ChannelId, (uint32) Stat);
}
