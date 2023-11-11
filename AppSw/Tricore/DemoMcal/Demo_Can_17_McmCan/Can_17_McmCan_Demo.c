/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2021)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME   : Can_17_McmCan_Demo.c                                        **
**                                                                           **
**  VERSION    : 3.0.0                                                       **
**                                                                           **
**  DATE       : 2021-02-24                                                  **
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
**                - Demo application for CAN driver                          **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                     **
**                                                                           **
******************************************************************************/

/******************************************************************************
**                      Includes                                             **
******************************************************************************/
#include "IfxSrc_reg.h"
#include "Std_Types.h"
#include "Irq.h"
#include "Can_17_McmCan_Demo.h"
#include "Can_17_McmCan.h"
#include "Test_Print.h"
/* Include the declarations of Can functions and types */
#include "SchM_Can_17_McmCan.h"

/******************************************************************************
**                      Imported Compiler Switch Check                       **
******************************************************************************/

/******************************************************************************
**                      Private Macro Definitions                            **
******************************************************************************/
#define CAN_SRC_SET_SRE                 (0x00000400U)
/* Set CLRR to clear SRR bit and disable SRE bit */
#define CAN_SRC_SET_CLRR_DISABLE_SRE     (0x52000000U)
#define CAN_DATA_LENGTH_CODE             (8U)

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
uint32 SrcCan0Int[4] = {0};
uint32 SrcCan1Int[4] = {0};
uint8 CanRxDataBuff[20][64] = {{0}, {0}};

/* Global variables used for pass/fail criteria */
uint8 Test_RxConfirmCount = 0;
uint8 Test_TxConfirmCount = 0;
/******************************************************************************
**                      Private Constant Definitions                         **
******************************************************************************/

/* Data Bytes For CAN Frame */
uint8 tx_data_1[][10] = {
  {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 },
  {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18 },
  {0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28 },
  {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38 },
  {0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48 },
  {0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58 },
  {0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68 },
  {0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78 },
  {0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88 },
  {0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98 },
  {0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
  {0x11, 0x22, 0x33, 0x44, 0x44, 0x33, 0x22, 0x11 },
  {0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98 },
} ;

/* Data Bytes For CAN FD Frame */
uint8 tx_data_Fd[][64] = {
  {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0xA, 0xB, 0xC},
  { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0x11, 0x22, 0x33,
    0x44, 0x55, 0x66, 0x77
  },
  { 0x41, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0x11, 0x22, 0x33,
    0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0x01, 0x02
  },
  { 0x39, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0x11, 0x22, 0x33,
    0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0x01, 0x02, 0x15, 0x16, 0x17, 0x18, 0x91,
    0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98
  }
} ;

uint8 Can_Init_Status = 0;

/* CAN Frame PDU Info With Standard Identifier */
Can_PduType PduInfo_1[] =
{
  {8,  8, 0x123, tx_data_1[0] },
  {12, 8, 0x111, tx_data_1[1] },
  {9,  8, 0x456, tx_data_1[2] },
  {13, 8, 0x222, tx_data_1[3] }
};

/* CAN Frame PDU Info With Standard Identifier */
Can_PduType PduInfo_2[] =
{
  {8,  8, 0x123, tx_data_1[0] },
  {12, 8, 0x111, tx_data_1[1] },
  {10,  8, 0x81111111, tx_data_1[2] },
  {13, 8, 0x222, tx_data_1[3] }
};

/* CAN Frame PDU Info With Extended Identifier */
Can_PduType PduInfo_ExtId[] =
{
  {10, 8, 0x8AAAAAAA, tx_data_1[4]},
  {14, 8, 0x81111111, tx_data_1[5]}
};

/* CAN Frame PDU Info With Mixed Identifier */
Can_PduType PduInfo_1_Mixed[] =
{
  {15, 8, 0x00C,      tx_data_1[6] },
  {15, 8, 0x80300000, tx_data_1[7] }
};

Can_PduType PduInfo_2_Mixed[] =
{
  {11, 8, 0x00A,      tx_data_1[8] },
  {11, 8, 0x80280000, tx_data_1[9] }
};

/* CAN Frame PDU Info for Wakeup */
Can_PduType PduInfo_Wakeup[] =
{
  {9,  8, 0x456, tx_data_1[11] },
  {13, 8, 0x80280000, tx_data_1[11] }
};

/* CAN Frame PDU Info for Trigger transmit check */
Can_PduType PduInfo_TriggerTransmit[] =
{
  {20,  8, 0x123, tx_data_1[0] },
  {21, 8, 0x111, tx_data_1[0] },
  {22,  8, 0x456, tx_data_1[0] },
  {23, 8, 0x222, tx_data_1[0] }
};

/* CAN Frame PDU Info for FD */
Can_PduType PduInfo_FD[] =
{
  {8,  12, 0x40000123, tx_data_Fd[0] },
  {12, 16, 0x40000111, tx_data_Fd[1] },
  {9,  20, 0x40000456, tx_data_Fd[2] },
  {13, 32, 0x40000222, tx_data_Fd[3] }
};

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/

#define CAN_17_MCMCAN_START_SEC_CODE_QM_GLOBAL
#include "Can_17_McmCan_MemMap.h"

void Can_StandardFrameTx(void);
static void Can_ExtendedFrameTx(void);
static void Can_MixedModeSupport(void);
static void Can_TestEnableDisableInterrupt(void);
static void Can_SetBaudrateUsage(void);
static void Can_IcomUsage(void);
static void Can_TriggerTransmitCheck(void);
static void Can_FDMsgTxRx(void);
void Can_EnableServiceRequest(uint8 node);
static void Can_DisableServiceRequest(uint8 node);
static void Can_FlushRxDataBuff(uint8 MsgCnt);
static uint8 Can_TxRxDataCompare(uint8 MsgCnt, uint8 DemoOpt);

#define CAN_17_MCMCAN_STOP_SEC_CODE_QM_GLOBAL
#include "Can_17_McmCan_MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/

#define CAN_17_MCMCAN_START_SEC_CODE_QM_GLOBAL
#include "Can_17_McmCan_MemMap.h"

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
void Can_17_McmCan_Demo(void)
{
  char szString[80];
  volatile uint8 TempUSage = 0;

  if(!Can_Init_Status)
  {
    IrqCan_Init();
    Can_17_McmCan_Init(&Can_17_McmCan_Config);
    Can_EnableServiceRequest(2);
    Can_Init_Status++;
  }

  while (!TempUSage)
  {
    print_f("\n\n\n");
    print_f("\n/*********************************************************/\n");
    print_f("\n                CAN DRIVER DEMOAPP MENU                   \n ");
    print_f("\n                                                          \n ");
    print_f("     1.  Transfer of Standard Frame between CAN controllers \n ");
    print_f("     2.  Transfer of Extended Frame between CAN controllers \n ");
    print_f("     3.  Mixed Mode Support                                 \n ");
    print_f("     4.  Check Enabling and Disabling of Tx and Rx Interrupts\n ");
    print_f("     5.  Changing Baudrate using Can_SetBaudRate            \n ");
    print_f("     6.  Activation and Deactivation of Pretended networking\n ");
    print_f("     7.  Trigger transmit functionality                     \n ");
    print_f("     8.  FD frames transmission and reception               \n ");
    print_f("     x.  Back To Main Menu                                  \n ");
    print_f("                                                            \n ");
    print_f("\n/*********************************************************/\n");
    print_f("  Enter Your Option :: ");

    getline(szString, sizeof szString - 1);

    switch (*szString)
    {
      case '1':
      {
        Can_StandardFrameTx();
        break;
      }
      case '2' :
      {
        Can_ExtendedFrameTx();
        break;
      }
      case '3' :
      {
        Can_MixedModeSupport();
        break;
      }
      case '4' :
      {
        Can_TestEnableDisableInterrupt();
        break;
      }
      case '5' :
      {
        Can_SetBaudrateUsage();
        break;
      }
      case '6' :
      {
        Can_IcomUsage();
        break;
      }
      case '7' :
      {
        Can_TriggerTransmitCheck();
        break;
      }
      case '8' :
      {
        Can_FDMsgTxRx();
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
}/* Can_17_McmCan_Demo() */

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/
/*******************************************************************************
** Syntax : void Can_StandardFrameTx(void)                                    **
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
** Description : Transmission and Reception of CAN frames with Standard Id    **
**                                                                            **
*******************************************************************************/
void Can_StandardFrameTx(void)
{
  volatile uint32 Counter;
  uint8 Test_TxCount = 0, TxRxDataMismatch = 0;
  uint16 i;

  Test_TxConfirmCount = 0;
  Test_RxConfirmCount = 0;

  /* Can_17_McmCan_Init(&Can_ConfigRoot[0]); */

  /* Put the CAN controllers into started state */
  #if(MCAL_AR_VERSION == MCAL_AR_422)
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_T_START);
  #else
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_CS_STARTED);
  #endif
  #if(MCAL_AR_VERSION == MCAL_AR_422)
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_T_START);
  #else
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_CS_STARTED);
  #endif

  print_f("\n---------------------------------------------------------\n");
  print_f(" Standard Id Message Transfer Between Controller 0 and 1 \n");
  print_f("---------------------------------------------------------\n");

  for (i = 0; i < 2; i++)
  {
    /* Data transmission by Controller 0 to 1 */
    print_f("\n Standard Id Message Transfer From Controller 0 to 1 \n");
    Can_17_McmCan_Write(i + 8, &PduInfo_1[i * 2]) ;

    /* Increment transmit counter */
    Test_TxCount++ ;

    /* Delay */
    Counter = 0x5FFFF;
    while(Counter--)
    {}

    #if (CAN_17_MCMCAN_TX_POLLING_PROCESSING == STD_ON)
    Can_17_McmCan_MainFunction_Write();
    #endif
    #if (CAN_17_MCMCAN_RX_POLLING_PROCESSING == STD_ON)
    Can_17_McmCan_MainFunction_Read();
    #endif

    /* Data transmission by Controller 1 to 0 */
    print_f("\n Standard Id Message Transfer From Controller 1 to 0 \n");
    Can_17_McmCan_Write(i + 12, &PduInfo_1[(i * 2) + 1]) ;

    /* Increment transmit counter */
    Test_TxCount++ ;

    /* Delay */
    Counter = 0x5FFFF;
    while(Counter--)
    {}

    #if (CAN_17_MCMCAN_TX_POLLING_PROCESSING == STD_ON)
    Can_17_McmCan_MainFunction_Write();
    #endif
    #if (CAN_17_MCMCAN_RX_POLLING_PROCESSING == STD_ON)
    Can_17_McmCan_MainFunction_Read();
    #endif
  }

  /* Delay */
  Counter = 0x5FFFF;
  while(Counter--)
  {}

  /* Put the CAN controllers into stopped state */
  #if(MCAL_AR_VERSION == MCAL_AR_422)
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_T_STOP);
  #else
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_CS_STOPPED);
  #endif
  #if(MCAL_AR_VERSION == MCAL_AR_422)
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_T_STOP);
  #else
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_CS_STOPPED);
  #endif

  TxRxDataMismatch = Can_TxRxDataCompare(Test_TxCount, 1);

  if(((Test_TxConfirmCount != Test_TxCount) || (Test_RxConfirmCount != Test_TxCount)) && TxRxDataMismatch)
  {
    print_f("\nCAN message transfer didn't happen. \n");
    print_f("Number of transmits = %d \n", Test_TxCount);
    print_f("Number of transmit confirmations = %d \n", Test_TxConfirmCount);
    print_f("Number of receive indications = %d \n", Test_RxConfirmCount);
    StartResult();
    print_f("Result = Fail;");
    EndResult();
  }
  else
  {
    print_f("\nNumber of transmits = %d \n", Test_TxCount);
    print_f("Number of transmit confirmations = %d \n", Test_TxConfirmCount);
    print_f("Number of receive indications = %d \n", Test_RxConfirmCount);
    StartResult();
    print_f("Result = Pass;");
    EndResult();
  }

  Can_FlushRxDataBuff(Test_TxCount);
}

/*******************************************************************************
** Syntax : static void Can_ExtendedFrameTx(void)                             **
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
** Description : Transmission and Reception of CAN frames with Extended Id    **
**                                                                            **
*******************************************************************************/
static void Can_ExtendedFrameTx(void)
{
  volatile uint32 Counter;
  uint8 Test_TxCount = 0, TxRxDataMismatch = 0;

  Test_TxConfirmCount = 0;
  Test_RxConfirmCount = 0;

  /* Put the CAN controllers into started state */
  #if(MCAL_AR_VERSION == MCAL_AR_422)
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_T_START);
  #else
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_CS_STARTED);
  #endif
  #if(MCAL_AR_VERSION == MCAL_AR_422)
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_T_START);
  #else
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_CS_STARTED);
  #endif

  print_f("\n--------------------------------------------------------\n");
  print_f(" Extended Id Message Transfer Between Controller 0 and 1 \n");
  print_f("--------------------------------------------------------\n");

  /* Data transmission by Controller 0 to 1 */
  print_f("\n Extended Id Message Transfer From Controller 0 to 1 \n");
  Can_17_McmCan_Write(10, &PduInfo_ExtId[0]) ;

  /* Increment transmit counter */
  Test_TxCount++ ;

  /* Delay */
  Counter = 0x5FFFF;
  while(Counter--)
  {}

  #if (CAN_17_MCMCAN_TX_POLLING_PROCESSING == STD_ON)
  Can_17_McmCan_MainFunction_Write();
  #endif
  #if (CAN_17_MCMCAN_RX_POLLING_PROCESSING == STD_ON)
  Can_17_McmCan_MainFunction_Read();
  #endif

  /* Data transmission by Controller 1 to 0 */
  print_f("\n Extended Id Message Transfer From Controller 1 to 0 \n");
  Can_17_McmCan_Write(14, &PduInfo_ExtId[1]) ;

  /* Increment transmit counter */
  Test_TxCount++ ;

  /* Delay */
  Counter = 0x5FFFF;
  while(Counter--)
  {}

  #if (CAN_17_MCMCAN_TX_POLLING_PROCESSING == STD_ON)
  Can_17_McmCan_MainFunction_Write();
  #endif
  #if (CAN_17_MCMCAN_RX_POLLING_PROCESSING == STD_ON)
  Can_17_McmCan_MainFunction_Read();
  #endif

  /* Put the CAN controllers into stopped state */
  #if(MCAL_AR_VERSION == MCAL_AR_422)
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_T_STOP);
  #else
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_CS_STOPPED);
  #endif
  #if(MCAL_AR_VERSION == MCAL_AR_422)
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_T_STOP);
  #else
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_CS_STOPPED);
  #endif

  TxRxDataMismatch = Can_TxRxDataCompare(Test_TxCount, 2);

  if(((Test_TxConfirmCount != Test_TxCount) || (Test_RxConfirmCount != Test_TxCount)) && TxRxDataMismatch)
  {
    print_f("\nCAN message transfer didn't happen. \n");
    print_f("Number of transmits = %d \n", Test_TxCount);
    print_f("Number of transmit confirmations = %d \n", Test_TxConfirmCount);
    print_f("Number of receive indications = %d \n", Test_RxConfirmCount);
    StartResult();
    print_f("Result = Fail;");
    EndResult();
  }
  else
  {
    print_f("\nNumber of transmits = %d \n", Test_TxCount);
    print_f("Number of transmit confirmations = %d \n", Test_TxConfirmCount);
    print_f("Number of receive indications = %d \n", Test_RxConfirmCount);
    StartResult();
    print_f("Result = Pass;");
    EndResult();
  }

  Can_FlushRxDataBuff(Test_TxCount);
}

/*******************************************************************************
** Syntax : static void Can_MixedModeSupport(void)                            **
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
** Description : Transmission and Reception of CAN frames with Mixed Id       **
**                                                                            **
*******************************************************************************/
static void Can_MixedModeSupport(void)
{
  volatile uint32 Counter;
  uint8 Test_TxCount = 0, TxRxDataMismatch = 0;

  Test_TxConfirmCount = 0;
  Test_RxConfirmCount = 0;

  /* Put the CAN controllers into started state */
  #if(MCAL_AR_VERSION == MCAL_AR_422)
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_T_START);
  #else
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_CS_STARTED);
  #endif
  #if(MCAL_AR_VERSION == MCAL_AR_422)
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_T_START);
  #else
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_CS_STARTED);
  #endif

  print_f("\n------------------------------------------------------\n");
  print_f(" Mixed Id Message Transfer Between Controller 0 and 1 \n");
  print_f("------------------------------------------------------\n");

  /* Data transmission by Controller 1 to 0 */
  print_f("\n Standard Id Message Transfer From Controller 1 to 0 \n");
  Can_17_McmCan_Write(15, &PduInfo_1_Mixed[0]) ;

  /* Increment transmit counter */
  Test_TxCount++ ;

  /* Delay */
  Counter = 0x5FFFF;
  while(Counter--)
  {}

  #if (CAN_17_MCMCAN_TX_POLLING_PROCESSING == STD_ON)
  Can_17_McmCan_MainFunction_Write();
  #endif
  #if (CAN_17_MCMCAN_RX_POLLING_PROCESSING == STD_ON)
  Can_17_McmCan_MainFunction_Read();
  #endif

  /* Data transmission by Controller 1 to 0 */
  print_f("\n Extended Id Message Transfer From Controller 1 to 0 \n");
  Can_17_McmCan_Write(15, &PduInfo_1_Mixed[1]) ;

  /* Increment transmit counter */
  Test_TxCount++ ;

  /* Delay */
  Counter = 0x5FFFF;
  while(Counter--)
  {}

  #if (CAN_17_MCMCAN_TX_POLLING_PROCESSING == STD_ON)
  Can_17_McmCan_MainFunction_Write();
  #endif
  #if (CAN_17_MCMCAN_RX_POLLING_PROCESSING == STD_ON)
  Can_17_McmCan_MainFunction_Read();
  #endif

  /* Data transmission by Controller 0 to 1 */
  print_f("\n Standard Id Message Transfer From Controller 0 to 1 \n");
  Can_17_McmCan_Write(11, &PduInfo_2_Mixed[0]) ;

  /* Increment transmit counter */
  Test_TxCount++ ;

  /* Delay */
  Counter = 0x5FFFF;
  while(Counter--)
  {}

  #if (CAN_17_MCMCAN_TX_POLLING_PROCESSING == STD_ON)
  Can_17_McmCan_MainFunction_Write();
  #endif
  #if (CAN_17_MCMCAN_RX_POLLING_PROCESSING == STD_ON)
  Can_17_McmCan_MainFunction_Read();
  #endif

  /* Data transmission by Controller 0 to 1 */
  print_f("\n Extended Id Message Transfer From Controller 0 to 1 \n");
  Can_17_McmCan_Write(11, &PduInfo_2_Mixed[1]) ;

  /* Increment transmit counter */
  Test_TxCount++ ;

  /* Delay */
  Counter = 0x5FFFF;
  while(Counter--)
  {}

  #if (CAN_17_MCMCAN_TX_POLLING_PROCESSING == STD_ON)
  Can_17_McmCan_MainFunction_Write();
  #endif
  #if (CAN_17_MCMCAN_RX_POLLING_PROCESSING == STD_ON)
  Can_17_McmCan_MainFunction_Read();
  #endif

  /* Put the CAN controllers into stopped state */
  #if(MCAL_AR_VERSION == MCAL_AR_422)
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_T_STOP);
  #else
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_CS_STOPPED);
  #endif
  #if(MCAL_AR_VERSION == MCAL_AR_422)
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_T_STOP);
  #else
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_CS_STOPPED);
  #endif

  TxRxDataMismatch = Can_TxRxDataCompare(Test_TxCount, 3);

  if(((Test_TxConfirmCount != Test_TxCount) || (Test_RxConfirmCount != Test_TxCount)) && TxRxDataMismatch)
  {
    print_f("\nCAN message transfer didn't happen. \n");
    print_f("Number of transmits = %d \n", Test_TxCount);
    print_f("Number of transmit confirmations = %d \n", Test_TxConfirmCount);
    print_f("Number of receive indications = %d \n", Test_RxConfirmCount);
    StartResult();
    print_f("Result = Fail;");
    EndResult();
  }
  else
  {
    print_f("\nNumber of transmits = %d \n", Test_TxCount);
    print_f("Number of transmit confirmations = %d \n", Test_TxConfirmCount);
    print_f("Number of receive indications = %d \n", Test_RxConfirmCount);
    StartResult();
    print_f("Result = Pass;");
    EndResult();
  }

  Can_FlushRxDataBuff(Test_TxCount);
}

/*******************************************************************************
** Syntax : static void Can_TestEnableDisableInterrupt(void)                  **
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
** Description : Usage of Can_17_McmCan_DisableControllerInterrupts and       **
**               Can_17_McmCan_EnableControllerInterrupts APIs                **
**                                                                            **
*******************************************************************************/
static void Can_TestEnableDisableInterrupt(void)
{
  #if((CAN_17_MCMCAN_TX_INTERRUPT_PROCESSING == STD_ON)&&(CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON))

  volatile uint32 Counter;
  uint8 DemoResult_2_Failed = 0;
  uint8 DemoDisableInt_Cntr[16] = {0};

  Test_TxConfirmCount = 0;
  Test_RxConfirmCount = 0;

  /* Put the CAN controllers into started state */
  #if(MCAL_AR_VERSION == MCAL_AR_422)
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_T_START);
  #else
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_CS_STARTED);
  #endif
  #if(MCAL_AR_VERSION == MCAL_AR_422)
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_T_START);
  #else
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_CS_STARTED);
  #endif

  print_f("\n---------------------------------------------\n");
  print_f(" Usage of APIs \n");
  print_f(" \t- Can_17_McmCan_DisableControllerInterrupts \n");
  print_f(" \t- Can_17_McmCan_EnableControllerInterrupts \n");
  print_f("---------------------------------------------\n");

  print_f("\n Disabling Controller 0 interrupts... \n");
  Can_17_McmCan_DisableControllerInterrupts(Can_17_McmCanConf_CanController_CanController_0);

  DemoDisableInt_Cntr[Can_17_McmCanConf_CanController_CanController_0]++;

  if( 1U == DemoDisableInt_Cntr[Can_17_McmCanConf_CanController_CanController_0])
  {
    Can_DisableServiceRequest(Can_17_McmCanConf_CanController_CanController_0);
  }


  print_f("\n Disabling Controller 0 interrupts one more time \n");
  Can_17_McmCan_DisableControllerInterrupts(Can_17_McmCanConf_CanController_CanController_0);

  DemoDisableInt_Cntr[Can_17_McmCanConf_CanController_CanController_0]++;

  if( 1U == DemoDisableInt_Cntr[Can_17_McmCanConf_CanController_CanController_0])
  {
    Can_DisableServiceRequest(Can_17_McmCanConf_CanController_CanController_0);
  }

  print_f("\n Controller 1 transmitting a message to Controller 0\n");
  print_f("\n No receive indication expected now\n");

  /* Controller 1 sends a message */
  Can_17_McmCan_Write(12, &PduInfo_1[1]) ;

  /* Delay */
  Counter = 0x5FFFF;
  while(Counter--)
  {}

  if((Test_TxConfirmCount != 1 ) || (Test_RxConfirmCount != 0))
  {
    DemoResult_2_Failed++ ;
  }

  print_f("\n Controller 0 transmitting a message to Controller 1\n");
  print_f("\n No transmit indication expected now\n");

  /* Controller 0 sends a message */
  Can_17_McmCan_Write(8, &PduInfo_1[0]) ;

  /* Delay */
  Counter = 0x5FFFF;
  while(Counter--)
  {}

  if((Test_TxConfirmCount != 1 ) || (Test_RxConfirmCount != 1))
  {
    DemoResult_2_Failed++ ;
  }

  print_f("\n Disabling Controller 1 interrupts... ");
  Can_17_McmCan_DisableControllerInterrupts(Can_17_McmCanConf_CanController_CanController_1);

  DemoDisableInt_Cntr[Can_17_McmCanConf_CanController_CanController_1]++;

  if( 1U == DemoDisableInt_Cntr[Can_17_McmCanConf_CanController_CanController_1])
  {
    Can_DisableServiceRequest(Can_17_McmCanConf_CanController_CanController_1);
  }

  print_f("\n Disabling Controller 1 interrupts one more time ");
  Can_17_McmCan_DisableControllerInterrupts(Can_17_McmCanConf_CanController_CanController_1);

  DemoDisableInt_Cntr[Can_17_McmCanConf_CanController_CanController_1]++;

  if( 1U == DemoDisableInt_Cntr[Can_17_McmCanConf_CanController_CanController_1])
  {
    Can_DisableServiceRequest(Can_17_McmCanConf_CanController_CanController_1);
  }

  print_f("\n No transmit and receive indications expected now\n");

  print_f("\n Controller 1 transmitting a message to Controller 0\n");

  /* Controller 1 sends a message */
  Can_17_McmCan_Write(9, &PduInfo_1[2]) ;

  print_f("\n Controller 0 transmitting a message to Controller 1\n");

  /* Controller 0 sends a message */
  Can_17_McmCan_Write(13, &PduInfo_1[3]) ;

  /* Delay */
  Counter = 0x5FFFF;
  while(Counter--)
  {}

  if((Test_TxConfirmCount != 1 ) || (Test_RxConfirmCount != 1))
  {
    DemoResult_2_Failed++ ;
  }

  print_f("\n Enabling interrupts ONCE for both controllers... ");
  Can_17_McmCan_EnableControllerInterrupts(Can_17_McmCanConf_CanController_CanController_0);

  DemoDisableInt_Cntr[Can_17_McmCanConf_CanController_CanController_0]--;

  if(!(DemoDisableInt_Cntr[Can_17_McmCanConf_CanController_CanController_0]))
  {
    Can_EnableServiceRequest(Can_17_McmCanConf_CanController_CanController_0);
  }

  Can_17_McmCan_EnableControllerInterrupts(Can_17_McmCanConf_CanController_CanController_1);

  DemoDisableInt_Cntr[Can_17_McmCanConf_CanController_CanController_1]--;

  if(!(DemoDisableInt_Cntr[Can_17_McmCanConf_CanController_CanController_1]))
  {
    Can_EnableServiceRequest(Can_17_McmCanConf_CanController_CanController_1);
  }

  print_f("\n Still there SHOULDN'T be any transmit or recieve indications");

  print_f("\n Controller 1 is transmitting a message to Controller 0\n");

  /* Controller 1 sends a message */
  Can_17_McmCan_Write(14, &PduInfo_ExtId[1]) ;

  /* Delay */
  Counter = 0x5FFFF;
  while(Counter--)
  {}

  print_f("\n Controller 0 is transmitting a message to Controller 1\n");

  /* Controller 0 sends a message */
  Can_17_McmCan_Write(10, &PduInfo_ExtId[0]) ;

  /* Delay */
  Counter = 0x5FFFF;
  while(Counter--)
  {}

  if((Test_TxConfirmCount != 1 ) || (Test_RxConfirmCount != 1))
  {
    DemoResult_2_Failed++ ;
  }

  print_f("\n Enabling interrupts SECOND TIME for both controllers... ");
  Can_17_McmCan_EnableControllerInterrupts(Can_17_McmCanConf_CanController_CanController_0);

  DemoDisableInt_Cntr[Can_17_McmCanConf_CanController_CanController_0]--;

  if(!(DemoDisableInt_Cntr[Can_17_McmCanConf_CanController_CanController_0]))
  {
    Can_EnableServiceRequest(Can_17_McmCanConf_CanController_CanController_0);
  }

  Can_17_McmCan_EnableControllerInterrupts(Can_17_McmCanConf_CanController_CanController_1);

  DemoDisableInt_Cntr[Can_17_McmCanConf_CanController_CanController_1]--;

  if(!(DemoDisableInt_Cntr[Can_17_McmCanConf_CanController_CanController_1]))
  {
    Can_EnableServiceRequest(Can_17_McmCanConf_CanController_CanController_1);
  }

  print_f("\n Pending transmit ok and receive indications ARE expected now\n");

  /* Delay */
  Counter = 0x5FFFF;
  while(Counter--)
  {}

  if((Test_TxConfirmCount != 6 ) || (Test_RxConfirmCount != 6))
  {
    DemoResult_2_Failed++ ;
  }

  print_f("\n\n Transmit and receive indications for new transmit requests");
  print_f("\n are expected as usual now.\n");
  print_f("\n Controller 1 is transmitting a message.\n");

  /* Controller 1 sends a message */
  Can_17_McmCan_Write(12, &PduInfo_1[1]) ;

  /* Delay */
  Counter = 0x5FFFF;
  while(Counter--)
  {}

  if((Test_TxConfirmCount != 7 ) || (Test_RxConfirmCount != 7))
  {
    DemoResult_2_Failed++ ;
  }

  print_f("\n Controller 0 is transmitting a message.\n");

  /* Controller 0 sends a message */
  Can_17_McmCan_Write(8, &PduInfo_1[0]) ;

  /* Delay */
  Counter = 0x5FFFF;
  while(Counter--)
  {}

  /* Put the CAN controllers into stopped state */
  #if(MCAL_AR_VERSION == MCAL_AR_422)
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_T_STOP);
  #else
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_CS_STOPPED);
  #endif
  #if(MCAL_AR_VERSION == MCAL_AR_422)
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_T_STOP);
  #else
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_CS_STOPPED);
  #endif

  if((Test_TxConfirmCount != 8 ) || (Test_RxConfirmCount != 8))
  {
    DemoResult_2_Failed++ ;
  }

  if(DemoResult_2_Failed)
  {
    StartResult();
    print_f("Result = Fail;");
    EndResult();
  }
  else
  {
    StartResult();
    print_f("Result = Pass;");
    EndResult();
  }

  #else

  print_f("\n For CAN controllers 0 and 1, both Tx and Rx ");
  print_f("processing should be interrupt mode\n");

  #endif
}

/*******************************************************************************
** Syntax : static void Can_SetBaudrateUsage(void)                            **
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
** Description : Usage of Can_17_McmCan_SetBaudrate for changing baudrate     **
**                                                                            **
*******************************************************************************/
static void Can_SetBaudrateUsage(void)
{
  volatile uint32 Counter;
  uint8 Test_TxCount = 0, TxRxDataMismatch = 0;
  uint16 i;

  Test_TxCount = 0;
  Test_TxConfirmCount = 0;
  Test_RxConfirmCount = 0;

  print_f(" \n\n Current CAN communication baudrate is 500kbps \n");
  print_f(" \n CAN controllers should be in STOPPED state while changing ");
  print_f(" baudrate \n");

  print_f(" \n Set the CAN controller state to STOPPED state \n");
  /* Put the CAN controllers into stopped state */
  #if(MCAL_AR_VERSION == MCAL_AR_422)
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_T_STOP);
  #else
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_CS_STOPPED);
  #endif
  #if(MCAL_AR_VERSION == MCAL_AR_422)
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_T_STOP);
  #else
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_CS_STOPPED);
  #endif

  print_f(" \n\n Change the CAN controllers baudrate to 1Mbps \n");

  /* Set the baudrate */
  #if (CAN_17_MCMCAN_SET_BAUDRATE_API == STD_ON)
  Can_17_McmCan_SetBaudrate(Can_17_McmCanConf_CanController_CanController_0, 1);
  #endif

  /* Set the baudrate */
  #if (CAN_17_MCMCAN_SET_BAUDRATE_API == STD_ON)
  Can_17_McmCan_SetBaudrate(Can_17_McmCanConf_CanController_CanController_1, 1);
  #endif


  print_f(" \n Set the CAN controller state to STARTED state \n");
  /* Put the CAN controllers into started state */
  #if(MCAL_AR_VERSION == MCAL_AR_422)
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_T_START);
  #else
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_CS_STARTED);
  #endif
  #if(MCAL_AR_VERSION == MCAL_AR_422)
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_T_START);
  #else
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_CS_STARTED);
  #endif

  print_f("\n---------------------------------------------------------\n");
  print_f(" Standard Id Message Transfer Between Controller 0 and 1 \n");
  print_f("---------------------------------------------------------\n");

  for (i = 0; i < 2; i++)
  {
    /* Data transmission by Controller 0 to 1 */
    print_f("\n Standard Id Message Transfer From Controller 0 to 1 \n");
    Can_17_McmCan_Write(i + 8, &PduInfo_1[i * 2]) ;

    /* Increment transmit counter */
    Test_TxCount++ ;

    /* Delay */
    Counter = 0x5FFFF;
    while(Counter--)
    {}

    #if (CAN_17_MCMCAN_TX_POLLING_PROCESSING == STD_ON)
    Can_17_McmCan_MainFunction_Write();
    #endif
    #if (CAN_17_MCMCAN_RX_POLLING_PROCESSING == STD_ON)
    Can_17_McmCan_MainFunction_Read();
    #endif

    /* Data transmission by Controller 1 to 0 */
    print_f("\n Standard Id Message Transfer From Controller 1 to 0 \n");
    Can_17_McmCan_Write(i + 12, &PduInfo_1[(i * 2) + 1]) ;

    /* Increment transmit counter */
    Test_TxCount++ ;

    /* Delay */
    Counter = 0x5FFFF;
    while(Counter--)
    {}

    #if (CAN_17_MCMCAN_TX_POLLING_PROCESSING == STD_ON)
    Can_17_McmCan_MainFunction_Write();
    #endif
    #if (CAN_17_MCMCAN_RX_POLLING_PROCESSING == STD_ON)
    Can_17_McmCan_MainFunction_Read();
    #endif
  }

  /* Delay */
  Counter = 0x5FFFF;
  while(Counter--)
  {}

  /* Put the CAN controllers into stopped state */
  #if(MCAL_AR_VERSION == MCAL_AR_422)
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_T_STOP);
  #else
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_CS_STOPPED);
  #endif
  #if(MCAL_AR_VERSION == MCAL_AR_422)
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_T_STOP);
  #else
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_CS_STOPPED);
  #endif

  print_f(" \n\n Change the CAN controllers baudrate back to 500kbps \n");

  /* Set the baudrate back to default configured values*/
  #if (CAN_17_MCMCAN_SET_BAUDRATE_API == STD_ON)
  Can_17_McmCan_SetBaudrate(Can_17_McmCanConf_CanController_CanController_0, 0);
  #endif

  /* Set the baudrate back to default configured values*/
  #if (CAN_17_MCMCAN_SET_BAUDRATE_API == STD_ON)
  Can_17_McmCan_SetBaudrate(Can_17_McmCanConf_CanController_CanController_1, 0);
  #endif

  TxRxDataMismatch = Can_TxRxDataCompare(Test_TxCount, 5);

  if(((Test_TxConfirmCount != Test_TxCount) || (Test_RxConfirmCount != Test_TxCount)) && TxRxDataMismatch)
  {
    print_f("\nCAN message transfer didn't happen. \n");
    print_f("Number of transmits = %d \n", Test_TxCount);
    print_f("Number of transmit confirmations = %d \n", Test_TxConfirmCount);
    print_f("Number of receive indications = %d \n", Test_RxConfirmCount);
    StartResult();
    print_f("Result = Fail;");
    EndResult();
  }
  else
  {
    print_f("\nNumber of transmits = %d \n", Test_TxCount);
    print_f("Number of transmit confirmations = %d \n", Test_TxConfirmCount);
    print_f("Number of receive indications = %d \n", Test_RxConfirmCount);
    StartResult();
    print_f("Result = Pass;");
    EndResult();
  }

  Can_FlushRxDataBuff(Test_TxCount);
}

/*******************************************************************************
** Syntax : static void Can_IcomUsage(void)                                   **
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
** Description : Usage of Can_17_McmCan_SetIcomConfiguration for              **
**               Activation/Deactivation of Pretended Networking              **
**                                                                            **
*******************************************************************************/
static void Can_IcomUsage(void)
{
  volatile uint32 Counter;
  #if(MCAL_AR_VERSION == MCAL_AR_422)
  Can_ReturnType RetVal;
  #else
  Std_ReturnType RetVal;
  #endif

  uint8 i;
  uint8 Test_TxCount;

  Test_TxCount = 0;
  Test_TxConfirmCount = 0;
  Test_RxConfirmCount = 0;

  print_f(" \n Set the CAN controller state to STARTED state \n");
  /* Put the CAN controllers into started state */
  #if(MCAL_AR_VERSION == MCAL_AR_422)
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_T_START);
  #else
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_CS_STARTED);
  #endif
  #if(MCAL_AR_VERSION == MCAL_AR_422)
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_T_START);
  #else
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_CS_STARTED);
  #endif

  print_f(" \n\n Activate the Pretended Networking in CAN controller 1 \n");
  /* Activate Pretended networking */
  #if (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON)
  Can_17_McmCan_SetIcomConfiguration (Can_17_McmCanConf_CanController_CanController_1, 1);
  #endif

  print_f("\n---------------------------------------------------------\n");
  print_f(" Message Transfer Between Controller 0 and 1 \n");
  print_f("---------------------------------------------------------\n");

  for (i = 0; i < 2; i++)
  {
    /* Data transmission by Controller 1 to 0 */
    print_f("\n Standard Id Message Transfer From Controller 1 to 0 \n");
    RetVal = Can_17_McmCan_Write(i + 12, &PduInfo_1[(i * 2) + 1]) ;

    if (CAN_BUSY == RetVal)
    {
      print_f("\n---------------------------------------------------------\n");
      print_f(" CAN Write status for CAN controller 1 is CAN_BUSY. \n");
      print_f(" Message transmission for CAN controller 1 is not possible when Pretended networking is activated  \n");
      print_f("---------------------------------------------------------\n");
    }

    /* Delay */
    Counter = 0x5FFFF;
    while(Counter--)
    {}

    #if (CAN_17_MCMCAN_TX_POLLING_PROCESSING == STD_ON)
    Can_17_McmCan_MainFunction_Write();
    #endif

    /* Data transmission by Controller 0 to 1 */
    print_f("\n---------------------------------------------------------\n");
    print_f(" Transmitting normal message from CAN controller 0 to 1  \n");
    print_f("---------------------------------------------------------\n");
    Can_17_McmCan_Write(i + 9, &PduInfo_2[i * 2]) ;

    /* Increment transmit counter */
    Test_TxCount++ ;

    /* Delay */
    Counter = 0x5FFFF;
    while(Counter--)
    {}

    #if (CAN_17_MCMCAN_TX_POLLING_PROCESSING == STD_ON)
    Can_17_McmCan_MainFunction_Write();
    #endif
    #if (CAN_17_MCMCAN_RX_POLLING_PROCESSING == STD_ON)
    Can_17_McmCan_MainFunction_Read();
    #endif

    /* Data transmission by Controller 0 to 1 */
    print_f("\n---------------------------------------------------------\n");
    print_f(" Transmitting wakeup message from CAN controller 0 to 1  \n");
    print_f("---------------------------------------------------------\n");
    Can_17_McmCan_Write(9, &PduInfo_Wakeup[0]) ;

    /* Increment transmit counter */
    Test_TxCount++ ;

    /* Delay */
    Counter = 0x5FFFF;
    while(Counter--)
    {}

    #if (CAN_17_MCMCAN_TX_POLLING_PROCESSING == STD_ON)
    Can_17_McmCan_MainFunction_Write();
    #endif
    #if (CAN_17_MCMCAN_RX_POLLING_PROCESSING == STD_ON)
    Can_17_McmCan_MainFunction_Read();
    #endif

  }

  /* Delay */
  Counter = 0x5FFFF;
  while(Counter--)
  {}

  if((Test_TxConfirmCount != Test_TxCount) || (Test_RxConfirmCount != (1)))
  {
    /* Put the CAN controllers into stopped state */
    #if(MCAL_AR_VERSION == MCAL_AR_422)
    Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_T_STOP);
    #else
    Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_CS_STOPPED);
    #endif
    #if(MCAL_AR_VERSION == MCAL_AR_422)
    Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_T_STOP);
    #else
    Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_CS_STOPPED);
    #endif
    print_f("\nCAN message transfer didn't happen. \n");
    print_f("Number of transmits = %d \n", Test_TxCount);
    print_f("Number of transmit confirmations = %d \n", Test_TxConfirmCount);
    print_f("Number of receive indications = %d \n", Test_RxConfirmCount);
    StartResult();
    print_f("Result = Fail;");
    EndResult();
  }
  else
  {
    print_f("\nNumber of transmits = %d \n", Test_TxCount);
    print_f("Number of transmit confirmations = %d \n", Test_TxConfirmCount);
    print_f("Number of CanIcomRxMessage reception required for Wakeup = %d \n");
    \
    // Can_17_McmCan_Config.CanIcomMsgConfigPtr[0].IcomCntrVal);
    print_f("Number of receive indications = %d \n", Test_RxConfirmCount);
    print_f("\n---------------------------------------------------------\n");
    print_f(" Wakeup message received and CanIf_RxIndication is called. \n");
    print_f("Deactivating Pretended Networking for CAN controller 1. \n");
    print_f("---------------------------------------------------------\n");
    /* Deactivate Pretended networking */
    #if (CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT == STD_ON)
    Can_17_McmCan_SetIcomConfiguration (Can_17_McmCanConf_CanController_CanController_1, 0);
    #endif
    /* Put the CAN controllers into stopped state */
    #if(MCAL_AR_VERSION == MCAL_AR_422)
    Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_T_STOP);
    #else
    Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_CS_STOPPED);
    #endif
    #if(MCAL_AR_VERSION == MCAL_AR_422)
    Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_T_STOP);
    #else
    Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_CS_STOPPED);
    #endif
    StartResult();
    print_f("Result = Pass;");
    EndResult();
  }
}

/*******************************************************************************
** Syntax : static void Can_TriggerTransmitCheck(void)                        **
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
** Description : To check if CanIf_TriggerTransmit API is called              **
**                                                                            **
*******************************************************************************/
static void Can_TriggerTransmitCheck(void)
{
  volatile uint32 Counter;
  uint8 Test_TxCount = 0, TxRxDataMismatch = 0;
  uint16 i;

  Test_TxConfirmCount = 0;
  Test_RxConfirmCount = 0;

  /* Put the CAN controllers into started state */
  #if(MCAL_AR_VERSION == MCAL_AR_422)
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_T_START);
  #else
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_CS_STARTED);
  #endif
  #if(MCAL_AR_VERSION == MCAL_AR_422)
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_T_START);
  #else
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_CS_STARTED);
  #endif

  print_f("\n---------------------------------------------------------\n");
  print_f(" Standard Id Message Transfer Between Controller 0 and 1 \n");
  print_f("---------------------------------------------------------\n");

  for (i = 0; i < 2; i++)
  {
    /* Data transmission by Controller 0 to 1 */
    print_f("\n Standard Id Message Transfer From Controller 0 to 1 \n");
    Can_17_McmCan_Write(i + 8, &PduInfo_TriggerTransmit[i * 2]) ;

    /* Increment transmit counter */
    Test_TxCount++ ;

    /* Delay */
    Counter = 0x5FFFF;
    while(Counter--)
    {}

    #if (CAN_17_MCMCAN_TX_POLLING_PROCESSING == STD_ON)
    Can_17_McmCan_MainFunction_Write();
    #endif
    #if (CAN_17_MCMCAN_RX_POLLING_PROCESSING == STD_ON)
    Can_17_McmCan_MainFunction_Read();
    #endif

    /* Data transmission by Controller 1 to 0 */
    print_f("\n Standard Id Message Transfer From Controller 1 to 0 \n");
    Can_17_McmCan_Write(i + 12, &PduInfo_TriggerTransmit[(i * 2) + 1]) ;

    /* Increment transmit counter */
    Test_TxCount++ ;

    /* Delay */
    Counter = 0x5FFFF;
    while(Counter--)
    {}
    #if (CAN_17_MCMCAN_TX_POLLING_PROCESSING == STD_ON)
    Can_17_McmCan_MainFunction_Write();
    #endif
    #if (CAN_17_MCMCAN_RX_POLLING_PROCESSING == STD_ON)
    Can_17_McmCan_MainFunction_Read();
    #endif
  }

  /* Delay */
  Counter = 0x5FFFF;
  while(Counter--)
  {}

  /* Put the CAN controllers into stopped state */
  #if(MCAL_AR_VERSION == MCAL_AR_422)
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_T_STOP);
  #else
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_CS_STOPPED);
  #endif
  #if(MCAL_AR_VERSION == MCAL_AR_422)
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_T_STOP);
  #else
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_CS_STOPPED);
  #endif

  TxRxDataMismatch = Can_TxRxDataCompare(Test_TxCount, 7);

  if(((Test_TxConfirmCount != Test_TxCount) || (Test_RxConfirmCount != Test_TxCount)) && TxRxDataMismatch)
  {
    print_f("\nCAN message transfer didn't happen. \n");
    print_f("Number of transmits = %d \n", Test_TxCount);
    print_f("Number of transmit confirmations = %d \n", Test_TxConfirmCount);
    print_f("Number of receive indications = %d \n", Test_RxConfirmCount);
    StartResult();
    print_f("Result = Fail;");
    EndResult();
  }
  else
  {
    print_f("\nNumber of transmits = %d \n", Test_TxCount);
    print_f("Number of transmit confirmations = %d \n", Test_TxConfirmCount);
    print_f("Number of receive indications = %d \n", Test_RxConfirmCount);
    StartResult();
    print_f("Result = Pass;");
    EndResult();
  }

  Can_FlushRxDataBuff(Test_TxCount);
}

/*******************************************************************************
** Syntax : static void Can_FDMsgTxRx(void)                                   **
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
** Description : Transmission and Reception of CAN FD frames                  **
**                                                                            **
*******************************************************************************/
static void Can_FDMsgTxRx(void)
{
  volatile uint32 Counter;
  uint8 Test_TxCount = 0, TxRxDataMismatch = 0;
  uint16 i;

  Test_TxConfirmCount = 0;
  Test_RxConfirmCount = 0;

  /* Put the CAN controllers into started state */
  #if(MCAL_AR_VERSION == MCAL_AR_422)
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_T_START);
  #else
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_CS_STARTED);
  #endif
  #if(MCAL_AR_VERSION == MCAL_AR_422)
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_T_START);
  #else
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_CS_STARTED);
  #endif

  print_f("\n---------------------------------------------------------\n");
  print_f(" FD Message Transfer Between Controller 0 and 1 \n");
  print_f("---------------------------------------------------------\n");

  for (i = 0; i < 2; i++)
  {
    /* Data transmission by Controller 0 to 1 */
    print_f("\n FD Message Transfer From Controller 0 to 1 \n");
    Can_17_McmCan_Write(i + 8, &PduInfo_FD[i * 2]) ;

    /* Increment transmit counter */
    Test_TxCount++ ;

    /* Delay */
    Counter = 0x5FFFF;
    while(Counter--)
    {}

    #if (CAN_17_MCMCAN_TX_POLLING_PROCESSING == STD_ON)
    Can_17_McmCan_MainFunction_Write();
    #endif
    #if (CAN_17_MCMCAN_RX_POLLING_PROCESSING == STD_ON)
    Can_17_McmCan_MainFunction_Read();
    #endif

    /* Data transmission by Controller 1 to 0 */
    print_f("\n FD Message Transfer From Controller 1 to 0 \n");
    Can_17_McmCan_Write(i + 12, &PduInfo_FD[(i * 2) + 1]) ;

    /* Increment transmit counter */
    Test_TxCount++ ;

    /* Delay */
    Counter = 0x5FFFF;
    while(Counter--)
    {}

    #if (CAN_17_MCMCAN_TX_POLLING_PROCESSING == STD_ON)
    Can_17_McmCan_MainFunction_Write();
    #endif
    #if (CAN_17_MCMCAN_RX_POLLING_PROCESSING == STD_ON)
    Can_17_McmCan_MainFunction_Read();
    #endif
  }

  /* Delay */
  Counter = 0x5FFFF;
  while(Counter--)
  {}

  /* Put the CAN controllers into stopped state */
  #if(MCAL_AR_VERSION == MCAL_AR_422)
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_T_STOP);
  #else
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_0, CAN_CS_STOPPED);
  #endif
  #if(MCAL_AR_VERSION == MCAL_AR_422)
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_T_STOP);
  #else
  Can_17_McmCan_SetControllerMode (Can_17_McmCanConf_CanController_CanController_1, CAN_CS_STOPPED);
  #endif

  TxRxDataMismatch = Can_TxRxDataCompare(Test_TxCount, 8);

  if(((Test_TxConfirmCount != Test_TxCount) || (Test_RxConfirmCount != Test_TxCount)) && TxRxDataMismatch)
  {
    print_f("\nCAN message transfer didn't happen. \n");
    print_f("Number of transmits = %d \n", Test_TxCount);
    print_f("Number of transmit confirmations = %d \n", Test_TxConfirmCount);
    print_f("Number of receive indications = %d \n", Test_RxConfirmCount);
    StartResult();
    print_f("Result = Fail;");
    EndResult();
  }
  else
  {
    print_f("\nNumber of transmits = %d \n", Test_TxCount);
    print_f("Number of transmit confirmations = %d \n", Test_TxConfirmCount);
    print_f("Number of receive indications = %d \n", Test_RxConfirmCount);
    StartResult();
    print_f("Result = Pass;");
    EndResult();
  }

  Can_FlushRxDataBuff(Test_TxCount);
}

/*******************************************************************************
** Syntax : void Can_EnableServiceRequest(uint8 node)                         **
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
** Description : Enable Service Request for a particular Controller           **
**                                                                            **
*******************************************************************************/
void Can_EnableServiceRequest(uint8 node)
{
  if((0U == node) || (2U == node))
  {
    SRC_CAN_CAN0_INT0.U |= CAN_SRC_SET_SRE ;
    SRC_CAN_CAN0_INT1.U |= CAN_SRC_SET_SRE ;
    SRC_CAN_CAN0_INT2.U |= CAN_SRC_SET_SRE ;
    SRC_CAN_CAN0_INT3.U |= CAN_SRC_SET_SRE ;

    if(0U == node)
    {
      SRC_CAN_CAN0_INT0.U |= SrcCan0Int[0] ;
      SRC_CAN_CAN0_INT1.U |= SrcCan0Int[1] ;
      SRC_CAN_CAN0_INT2.U |= SrcCan0Int[2] ;
      SRC_CAN_CAN0_INT3.U |= SrcCan0Int[3] ;
    }
  }
  #ifdef SRC_CAN_CAN1_INT0
  if((1U == node) || (2U == node))
  {
    SRC_CAN_CAN1_INT0.U |= CAN_SRC_SET_SRE ;
    SRC_CAN_CAN1_INT1.U |= CAN_SRC_SET_SRE ;
    SRC_CAN_CAN1_INT2.U |= CAN_SRC_SET_SRE ;
    SRC_CAN_CAN1_INT3.U |= CAN_SRC_SET_SRE ;

    if(1U == node)
    {
      SRC_CAN_CAN1_INT0.U |= SrcCan1Int[0] ;
      SRC_CAN_CAN1_INT1.U |= SrcCan1Int[1] ;
      SRC_CAN_CAN1_INT2.U |= SrcCan1Int[2] ;
      SRC_CAN_CAN1_INT3.U |= SrcCan1Int[3] ;
    }
  }
 #else
  if((1U == node) || (2U == node))
  {
    SRC_CAN_CAN0_INT12.U |= CAN_SRC_SET_SRE ;
    SRC_CAN_CAN0_INT13.U |= CAN_SRC_SET_SRE ;
    SRC_CAN_CAN0_INT14.U |= CAN_SRC_SET_SRE ;
    SRC_CAN_CAN0_INT15.U |= CAN_SRC_SET_SRE ;

    if(1U == node)
    {
      SRC_CAN_CAN0_INT12.U |= SrcCan1Int[0] ;
      SRC_CAN_CAN0_INT13.U |= SrcCan1Int[1] ;
      SRC_CAN_CAN0_INT14.U |= SrcCan1Int[2] ;
      SRC_CAN_CAN0_INT15.U |= SrcCan1Int[3] ;
    }
  }
  #endif
}

/*******************************************************************************
** Syntax : static void Can_DisableServiceRequest(uint8 node)                 **
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
** Description : Disable Service Request for a particular Controller          **
**                                                                            **
*******************************************************************************/
static void Can_DisableServiceRequest(uint8 node)
{
  if((0U == node) || (2U == node))
  {
    SrcCan0Int[0] = SRC_CAN_CAN0_INT0.U ;
    SrcCan0Int[1] = SRC_CAN_CAN0_INT1.U ;
    SrcCan0Int[2] = SRC_CAN_CAN0_INT2.U ;
    SrcCan0Int[3] = SRC_CAN_CAN0_INT3.U ;

    SRC_CAN_CAN0_INT0.U = CAN_SRC_SET_CLRR_DISABLE_SRE ;
    SRC_CAN_CAN0_INT1.U = CAN_SRC_SET_CLRR_DISABLE_SRE ;
    SRC_CAN_CAN0_INT2.U = CAN_SRC_SET_CLRR_DISABLE_SRE ;
    SRC_CAN_CAN0_INT3.U = CAN_SRC_SET_CLRR_DISABLE_SRE ;
  }
 #ifdef SRC_CAN_CAN1_INT0
 if((1U == node) || (2U == node))
  {
    SrcCan1Int[0] = SRC_CAN_CAN1_INT0.U ;
    SrcCan1Int[1] = SRC_CAN_CAN1_INT1.U ;
    SrcCan1Int[2] = SRC_CAN_CAN1_INT2.U ;
    SrcCan1Int[3] = SRC_CAN_CAN1_INT3.U ;

    SRC_CAN_CAN1_INT0.U = CAN_SRC_SET_CLRR_DISABLE_SRE ;
    SRC_CAN_CAN1_INT1.U = CAN_SRC_SET_CLRR_DISABLE_SRE ;
    SRC_CAN_CAN1_INT2.U = CAN_SRC_SET_CLRR_DISABLE_SRE ;
    SRC_CAN_CAN1_INT3.U = CAN_SRC_SET_CLRR_DISABLE_SRE ;
  }
#else
  if((1U == node) || (2U == node))
  {
    SrcCan1Int[0] = SRC_CAN_CAN0_INT12.U ;
    SrcCan1Int[1] = SRC_CAN_CAN0_INT13.U ;
    SrcCan1Int[2] = SRC_CAN_CAN0_INT14.U ;
    SrcCan1Int[3] = SRC_CAN_CAN0_INT15.U ;

    SRC_CAN_CAN0_INT12.U = CAN_SRC_SET_CLRR_DISABLE_SRE ;
    SRC_CAN_CAN0_INT13.U = CAN_SRC_SET_CLRR_DISABLE_SRE ;
    SRC_CAN_CAN0_INT14.U = CAN_SRC_SET_CLRR_DISABLE_SRE ;
    SRC_CAN_CAN0_INT15.U = CAN_SRC_SET_CLRR_DISABLE_SRE ;
  }
#endif
}

/*******************************************************************************
** Syntax : static void Can_FlushRxDataBuff(uint8 MsgCnt)                     **
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
** Description : Flush Rx Data Buffer                                         **
**                                                                            **
*******************************************************************************/
static void Can_FlushRxDataBuff(uint8 MsgCnt)
{
  uint8 i, j;

  for ( i = 0 ; i < MsgCnt ; i++)
  {
    for ( j = 0; j < CAN_DATA_LENGTH_CODE ; j++)
    {
      CanRxDataBuff[i][j] = 0;
    }
  }
}

/*******************************************************************************
** Syntax : static uint8 Can_TxRxDataCompare(uint8 MsgCnt,uint8 DemoOpt)      **
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
** Description : Tx Rx Data Compare                                           **
**                                                                            **
*******************************************************************************/
static uint8 Can_TxRxDataCompare(uint8 MsgCnt, uint8 DemoOpt)
{
  uint8 i, j, Tx_Data = 0;
  uint8 TxRxDataCmpRslt = 0;

  for ( i = 0 ; i < MsgCnt ; i++)
  {
    for ( j = 0; j < CAN_DATA_LENGTH_CODE ; j++)
    {
      if((1U == DemoOpt) || (5U == DemoOpt))
      {
        Tx_Data = PduInfo_1[i].sdu[j];
      }
      else if(2U == DemoOpt)
      {
        Tx_Data = PduInfo_ExtId[i].sdu[j];
      }
      else if(3U == DemoOpt)
      {
        Tx_Data = PduInfo_1_Mixed[i].sdu[j];
      }
      else if(7U == DemoOpt)
      {
        Tx_Data = PduInfo_TriggerTransmit[i].sdu[j];
      }
      else if(8U == DemoOpt)
      {
        Tx_Data = PduInfo_FD[i].sdu[j];
      }

      if ( CanRxDataBuff[i][j] == Tx_Data)
      {
        TxRxDataCmpRslt = 0;
      }

      else
      {
        TxRxDataCmpRslt = 1;
        break;
      }

    }
    if(TxRxDataCmpRslt == 1)
    {
      break;
    }
  }

  return TxRxDataCmpRslt;
}

#define CAN_17_MCMCAN_STOP_SEC_CODE_QM_GLOBAL
#include "Can_17_McmCan_MemMap.h"
