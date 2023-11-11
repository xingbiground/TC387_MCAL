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
**  FILENAME   : Uart_Demo.c                                                 **
**                                                                           **
**  VERSION    : 1.0.0                                                       **
**                                                                           **
**  DATE       : 2021-11-24                                                  **
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
**                - Demo application for Uart driver                         **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                     **
**                                                                           **
******************************************************************************/

/******************************************************************************
**                      Includes                                             **
******************************************************************************/
#include "Std_Types.h"

#include "IfxSrc_reg.h"

#include "Test_Print.h"
#include "Test_Time.h"
#include "DemoApp_Cfg.h"
#include "Irq.h"
#include "Uart.h"
#include "Uart_Demo.h"

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

#define UART_TX_DATA_COUNT        (20U)
#define UART_MAX_DATA_COUNT       (200U)
#define UART_CHANNEL_Id           (0U)
#define UART_SRC_SET_SRE          (1U)
#define UART_ZERO_U               (0U)
#define UART_ONE_U                (1U)
#define UART_TEN_U                (10U)
#define UART_BUFF_SIZE            (208U)
/*******************************************************************************
**                      Private Variable Declarations                         **
*******************************************************************************/

extern const Uart_ConfigType Uart_Config;

#define UART_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_8
#include "Uart_MemMap.h"

uint8 u8l_StreamFlag;
uint8 Uart_RxDataBuff[UART_BUFF_SIZE];
uint8 ArU8G_UART_CS1_RXDATA[UART_BUFF_SIZE];

#define UART_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_8
#include "Uart_MemMap.h"

#define UART_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
#include "Uart_MemMap.h"

static volatile uint32 StreamMode_RX_DataSize;
static uint32 App_idx;

#define UART_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
#include "Uart_MemMap.h"

#define UART_START_SEC_CONST_ASIL_B_LOCAL_8
#include "Uart_MemMap.h"

const uint8 Uart_TxDataBuff[UART_BUFF_SIZE] = \
{ 'I', 'n', 'f', 'i', 'n', 'e', 'o', 'n', 't',
  'e', 'c', 'h', 'n', 'o', 'l', 'o', 'g', 'i',
  'e', 's', 'p', 'r', 'i', 'v', 'a', 't', 'e',
  'l', 'i', 'm', 'i', 't', 'e', 'd', 'b', 'a',
  'n', 'g', 'a', 'l', 'o', 'r', 'e', 'I', 'n',
  'f', 'i', 'n', 'e', 'o', 'n', 't', 'e', 'c',
  'h', 'n', 'o', 'l', 'o', 'g', 'i', 'e', 's',
  'p', 'r', 'i', 'v', 'a', 't', 'e', 'l', 'i',
  'm', 'i', 't', 'e', 'd', 'b', 'a', 'n', 'g',
  'a', 'l', 'o', 'r', 'e', 'I', 'n', 'f', 'i',
  'e', 'c', 'h', 'n', 'o', 'l', 'o', 'g', 'i',
  'e', 's', 'p', 'r', 'i', 'v', 'a', 't', 'e',
  'l', 'i', 'm', 'i', 't', 'e', 'd', 'b', 'a',
  'n', 'g', 'a', 'l', 'o', 'r', 'e', 'I', 'n',
  'f', 'i', 'n', 'e', 'o', 'n', 't', 'e', 'c',
  'h', 'n', 'o', 'l', 'o', 'g', 'i', 'e', 's',
  'p', 'r', 'i', 'v', 'a', 't', 'e', 'l', 'i',
  'm', 'i', 't', 'e', 'd', 'b', 'a', 'n', 'g',
  'a', 'l', 'o', 'r', 'e', 'n', 'e', 'o', 'n',
  'e', 'c', 'h', 'n', 'o', 'l', 'o', 'g', 'i',
  'e', 's', 'p', 'r', 'i', 'v', 'a', 't', 'e',
  'l', 'i', 'm', 'i', 't', 'e', 'd', 'b', 'a',
  'n', 'g', 'a', 'l', 'o', 'r', 'e', 'I', 'n', 'f',
};

#define UART_STOP_SEC_CONST_ASIL_B_LOCAL_8
#include "Uart_MemMap.h"


/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : void Streaming_Notification00                             **
**                  (                                                         **
**                    Uart_ErrorIdType Error, Uart_SizeType Stream_RxDataSize **
**                  )                                                         **
**                                                                            **
** Description    : This function triggers after every receive of data in     **
**                  Streaming Mode                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : Error             : Type of Error                         **
**                  Stream_RxDataSize : Number of received bytes              **
**                                                                            **
** Parameters(out): none                                                      **
**                                                                            **
** Return value   : none                                                      **
**                                                                            **
*******************************************************************************/

void Streaming_Notification00(Uart_ErrorIdType Error, Uart_SizeType Stream_RxDataSize)
{

  uint8 Buffidx = UART_ZERO_U;
  StreamMode_RX_DataSize += Stream_RxDataSize;

  while(StreamMode_RX_DataSize > App_idx)
  {
    /*Store the Reveived data in App buffer*/
    ArU8G_UART_CS1_RXDATA[App_idx] = Uart_RxDataBuff[Buffidx];
    Buffidx = Buffidx + UART_ONE_U;
    App_idx = App_idx + UART_ONE_U;
  }
}


/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : uint8 UartDemo_ValidateData                               **
**                  (                                                         **
**                    uint16 UartRxDataCnt                                    **
**                  )                                                         **
**                                                                            **
** Description    : This function to validate the recieved data in Read mode  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : UartRxDataCnt : Number of received bytes                  **
**                                                                            **
** Parameters(out): none                                                      **
**                                                                            **
** Return value   : Status of data validated                                  **
**                                                                            **
*******************************************************************************/

uint8 UartDemo_ValidateData(uint16 UartRxDataCnt)
{
  uint16 idx;
  uint8 RsltDataCheck = UART_ZERO_U;

  for(idx = 0; idx < UartRxDataCnt; idx++)
  {
    /*Compare Data Received with the Data Written for the Channel*/
    if(Uart_TxDataBuff[idx] == Uart_RxDataBuff[idx])
    {
      RsltDataCheck |= UART_ZERO_U;
    }
    else
    {
      RsltDataCheck = UART_ONE_U;
    }
  }

  /*Clear the App Rx Data Buffer for Next Operation*/
  for(idx = 0; idx < UartRxDataCnt; idx++)
  {
    Uart_RxDataBuff[idx] = UART_ZERO_U;
  }

  return RsltDataCheck;
}

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : uint8 UartDemo_ValidateData_Stream                        **
**                  (                                                         **
**                    uint16 UartRxDataCnt                                    **
**                  )                                                         **
**                                                                            **
** Description    : This function to validate the recieved data in Streaming  **
**                  mode                                                      **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : UartRxDataCnt : Number of received bytes                  **
**                                                                            **
** Parameters(out): none                                                      **
**                                                                            **
** Return value   : Status of data validated (Retun Value = 0 means data      **
                   validation is successful and 1 means not successful)       **
**                                                                            **
*******************************************************************************/
uint8 UartDemo_ValidateData_Stream(uint16 UartRxDataCnt)
{
  uint16 idx;
  uint8 RsltDataCheck = UART_ZERO_U;

  for(idx = 0; idx < UartRxDataCnt; idx++)
  {
    /*Compare Data Received with the Data Written for the Channel*/
    if(Uart_TxDataBuff[idx] == ArU8G_UART_CS1_RXDATA[idx])
    {
      RsltDataCheck |= UART_ZERO_U;
    }
    else
    {
      RsltDataCheck = UART_ONE_U;
    }
  }

  /*Clear the App Rx Data Buffer for Next Operation*/
  for(idx = 0; idx < UartRxDataCnt; idx++)
  {
    ArU8G_UART_CS1_RXDATA[idx] = UART_ZERO_U;
  }

  return RsltDataCheck;
}


/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : void UartDemo_GetChStatus(void)                           **
**                                                                            **
**                                                                            **
** Description    : This function to Get the UART Channel Status              **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : none                                                      **
**                                                                            **
** Parameters(out): none                                                      **
**                                                                            **
** Return value   : none                                                      **
**                                                                            **
*******************************************************************************/
void UartDemo_GetChStatus(void)
{
  Uart_StatusType ChStatus;

  ChStatus = Uart_GetStatus(UART_CHANNEL_Id);

  switch (ChStatus)
  {
    case UART_IDLE:
    {
      print_f("\n--------------- Uart Channel 0 is IDLE ---------------\n");
      StartResult();
      print_f("Result = Pass;");
      EndResult();
      break;
    }
    default:
    {
      print_f("\n--------------- Uart Channel 0 is BUSY ---------------\n");
      break;
    }
  }
}


/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : void UartDemo_StreamWrite(void)                           **
**                                                                            **
**                                                                            **
** Description    : This function to Transmit and Recieve Data in streaming   **
**                  mode                                                      **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : none                                                      **
**                                                                            **
** Parameters(out): none                                                      **
**                                                                            **
** Return value   : none                                                      **
**                                                                            **
*******************************************************************************/
void UartDemo_StreamWrite(void)
{
  Uart_ReturnType RetStreamApi, RetWriteApi;
  uint8 DataCheck;
  Uart_SizeType TxDataCount = UART_TX_DATA_COUNT;

  /*Avoid calling Uart_StartStreaming multiple time*/
  if(u8l_StreamFlag == UART_ZERO_U)
  {
    print_f("\n---------- Calling Stream function----------\n");

    RetStreamApi = Uart_StartStreaming(UART_CHANNEL_Id, (Uart_MemType*)Uart_RxDataBuff, TxDataCount);

    if (RetStreamApi == UART_E_OK)
    {
      print_f("\n Streaming Operation Initiated successfully \n");
    }
    else
    {
      print_f("\n Streaming Operation Initiation was unsuccessful \n");
    }

    u8l_StreamFlag = UART_ONE_U;
  }


  App_idx = UART_ZERO_U;
  StreamMode_RX_DataSize = UART_ZERO_U;

  print_f("\n--------- Calling Write function [Channel 0 to Write %d bytes] \
  -----------\n", TxDataCount);

  RetWriteApi = Uart_Write(UART_CHANNEL_Id, (Uart_MemType*)Uart_TxDataBuff, TxDataCount);

  if (RetWriteApi == UART_E_OK)
  {
    print_f("\n Write Operation Initiated successfully \n");
  }
  else
  {
    print_f("\n Write Operation Initiation was unsuccessful \n");
  }

  do
  {
    /*Do Nothing*/
  } while(StreamMode_RX_DataSize != TxDataCount);

  Timer_DelayMs(UART_TEN_U);

  DataCheck = UartDemo_ValidateData_Stream(TxDataCount);

  if (DataCheck == 0)
  {
    print_f("\n Data Transfer is SUCCESSFULL \n");
    UartDemo_GetChStatus();
    StartResult();
    print_f("Result = Pass;");
    EndResult();
  }
  else
  {
    print_f("\n Data Transfer is UNSUCCESSFULL \n");
  }

}

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : void UartDemo_StopStream(void)                            **
**                                                                            **
**                                                                            **
** Description    : This function to Stop streaming Receive                   **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : none                                                      **
**                                                                            **
** Parameters(out): none                                                      **
**                                                                            **
** Return value   : none                                                      **
**                                                                            **
*******************************************************************************/
void UartDemo_StopStream(void)
{

  Uart_ReturnType Ret_StopStreamApi;

  Ret_StopStreamApi = Uart_StopStreaming(UART_CHANNEL_Id);

  if(Ret_StopStreamApi == UART_E_OK)
  {
    print_f("\n Stop the Streaming Receive \n");
    u8l_StreamFlag = UART_ZERO_U;
    /*Checking Status after call of Stopstreaming*/
    UartDemo_GetChStatus();
  }
  else
  {
    print_f("\n UART Stop Operation couldn't be Initiated as UART Streaming \
		is not Initiated \n");
  }
}

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : void UartDemo_StopStreamWrite(void)                       **
**                                                                            **
**                                                                            **
** Description    : This function to Stop the On-Going Data Reception in      **
**                  Streaming                                                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : none                                                      **
**                                                                            **
** Parameters(out): none                                                      **
**                                                                            **
** Return value   : none                                                      **
**                                                                            **
*******************************************************************************/
void UartDemo_StopStreamWrite(void)
{
  Uart_ReturnType RetStreamApi, RetWriteApi;
  Uart_ReturnType Ret_StopStreamApi;
  Uart_SizeType TxDataCount, RxDataCount;


  TxDataCount = UART_MAX_DATA_COUNT;
  RxDataCount = UART_MAX_DATA_COUNT;

  print_f("\n---------- Calling Stream function ----------\n");

  RetStreamApi = Uart_StartStreaming(UART_CHANNEL_Id, (Uart_MemType*)Uart_RxDataBuff, RxDataCount);

  if (RetStreamApi == UART_E_OK)
  {
    print_f("\n Streaming Operation Initiated successfully \n");
  }
  else
  {
    print_f("\n Streaming Operation Initiation was unsuccessful \n");
  }

  App_idx = UART_ZERO_U;
  StreamMode_RX_DataSize = UART_ZERO_U;

  print_f("\n--------- Calling Write function -----------\n");

  RetWriteApi = Uart_Write(UART_CHANNEL_Id, (Uart_MemType*)Uart_TxDataBuff, TxDataCount);

  if (RetWriteApi == UART_E_OK)
  {
    print_f("\n Write Operation Initiated successfully \n");
  }
  else
  {
    print_f("\n Write Operation Initiation was unsuccessful \n");
  }

  Timer_DelayMs(UART_TEN_U);

  Ret_StopStreamApi = Uart_StopStreaming(UART_CHANNEL_Id);

  if(Ret_StopStreamApi == UART_E_OK)
  {
    print_f("\n STOP STREAMING SUCCESSFUL :Bytes Received before\
   stop the operation = %d \n", StreamMode_RX_DataSize);
    StartResult();
    print_f("Result = Pass;");
    EndResult();
  }
  else
  {
    print_f("\n UART Stop Operation couldn't be Initiated as UART Streaming \
	is not Initiated \n");
  }

}


/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : void UartDemo_ReadWrite(void)                             **
**                                                                            **
**                                                                            **
** Description    : This function to Transmit and Recieve Data in Read Mode   **
**                                                                            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : none                                                      **
**                                                                            **
** Parameters(out): none                                                      **
**                                                                            **
** Return value   : none                                                      **
**                                                                            **
*******************************************************************************/
void UartDemo_ReadWrite(void)
{
  Uart_ReturnType RetReadApi, RetWriteApi;
  uint8 DataCheck;
  Uart_StatusType ChStatus;
  Uart_SizeType TxDataCount = UART_TX_DATA_COUNT;

  print_f("\n---------- Calling Read function [Channel 0 to read %d bytes] \
  ----------\n", TxDataCount);

  RetReadApi = Uart_Read(UART_CHANNEL_Id, (Uart_MemType*)Uart_RxDataBuff, TxDataCount);

  if (RetReadApi == UART_E_OK)
  {
    print_f("\n Read Operation Initiated successfully \n");
  }
  else
  {
    print_f("\n Read Operation Initiation was unsuccessful \n");
  }

  print_f("\n--------- Calling Write function [Channel 0 to Write %d bytes] \
  -----------\n", TxDataCount);

  RetWriteApi = Uart_Write(UART_CHANNEL_Id, (Uart_MemType*)Uart_TxDataBuff, TxDataCount);

  if (RetWriteApi == UART_E_OK)
  {
    print_f("\n Write Operation Initiated successfully \n");
  }
  else
  {
    print_f("\n Write Operation Initiation was unsuccessful \n");
  }

  do
  {
    ChStatus = Uart_GetStatus(UART_CHANNEL_Id);
  } while(ChStatus != UART_IDLE);


  Timer_DelayMs(UART_TEN_U);

  DataCheck = UartDemo_ValidateData(TxDataCount);

  if (DataCheck == 0)
  {
    print_f("\n Data Transfer is SUCCESSFULL \n");
    UartDemo_GetChStatus();
  }
  else
  {
    print_f("\n Data Transfer is UNSUCCESSFULL \n");
  }

}

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : void UartDemo_GetDataTxnInfo(void)                        **
**                                                                            **
**                                                                            **
** Description    : This function to Get Data Transfer Info(Data Txd/Rxd      **
**                  before Last Abort Api Call)                               **
**                                                                            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : none                                                      **
**                                                                            **
** Parameters(out): none                                                      **
**                                                                            **
** Return value   : none                                                      **
**                                                                            **
*******************************************************************************/
void UartDemo_GetDataTxnInfo()
{

  Uart_SizeType  RetAbortWrite;

  Uart_SizeType RetAbortRead;

  print_f("\n--------------- Calling AbortWrite function ---------------\n");

  RetAbortWrite = Uart_AbortWrite(UART_CHANNEL_Id);

  print_f("\n Number of bytes transmitted before Aborting the\
  Write Operation= %d \n", RetAbortWrite);


  print_f("\n--------------- Calling AbortRead function ---------------\n");

  RetAbortRead = Uart_AbortRead(UART_CHANNEL_Id);

  print_f("\n Number of bytes received before Aborting the\
  Read Operation= %d \n", RetAbortRead);


  UartDemo_GetChStatus();
}

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : void UartDemo_AbortReadWrite(void)                        **
**                                                                            **
**                                                                            **
** Description    : This function to Abort On-Going Data Transmission and     **
**                  Reception                                                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : none                                                      **
**                                                                            **
** Parameters(out): none                                                      **
**                                                                            **
** Return value   : none                                                      **
**                                                                            **
*******************************************************************************/
void UartDemo_AbortReadWrite(void)
{
  Uart_ReturnType RetReadApi, RetWriteApi;
  Uart_SizeType TxDataCount, RxDataCount;

  Uart_SizeType  RetAbortWrite;

  Uart_SizeType RetAbortRead;


  TxDataCount = UART_MAX_DATA_COUNT;
  RxDataCount = UART_MAX_DATA_COUNT;

  print_f("\n------------ Calling Read function ------------\n");

  RetReadApi = Uart_Read(UART_CHANNEL_Id, (Uart_MemType*)Uart_RxDataBuff, RxDataCount);

  if (RetReadApi == UART_E_OK)
  {
    print_f("\n Read Operation Initiated Successfully \n");
  }
  else
  {
    print_f("\n Read function call is not Successful \n");
  }

  print_f("\n------------ Calling Write function ------------\n");

  RetWriteApi = Uart_Write(UART_CHANNEL_Id, (Uart_MemType*)Uart_TxDataBuff, TxDataCount);

  Timer_DelayMs(UART_TEN_U);

  RetAbortWrite = Uart_AbortWrite(UART_CHANNEL_Id);

  Timer_DelayMs(UART_TEN_U);

  RetAbortRead = Uart_AbortRead(UART_CHANNEL_Id);

  if(RetWriteApi == UART_E_OK)
  {
    print_f("\n Initiated UART Write Operation of %d bytes \n", TxDataCount);
    StartResult();
    print_f("Result = Pass;");
    EndResult();
  }
  else if(RetWriteApi == UART_E_NOT_OK)
  {
    print_f("\n UART Write Operation UNSUCCESSFUL \n");
  }
  else if(RetWriteApi == UART_E_BUSY)
  {
    print_f("\n UART Write Operation couldn't be Initiated as UART HW \
              is BUSY with some other Operation \n");
  }


  print_f("\n ABORT WRITE SUCCESSFUL :Bytes Transmitted before\
   aborting the operation = %d \n", RetAbortWrite);



  print_f("\n ABORT READ SUCCESSFUL :Bytes Received before\
   aborting the operation = %d \n", RetAbortRead);

}

/*******************************************************************************
** Traceability   : [cover parentID= ]                                        **
**                                                                            **
** Syntax         : void Uart_Demo(void)                                      **
**                                                                            **
**                                                                            **
** Description    : UART driver DemoApp menu                                  **
**                                                                            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:    : NA                                                        **
**                                                                            **
** Sync/Async:    : Synchronous                                               **
**                                                                            **
** Reentrancy:    : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : none                                                      **
**                                                                            **
** Parameters(out): none                                                      **
**                                                                            **
** Return value   : none                                                      **
**                                                                            **
*******************************************************************************/
void Uart_Demo(void)
{
  char szString[80];
  uint8 UartLoopVar = 0;
  const Uart_ConfigType * ConfigPtr = &Uart_Config;
  Uart_Init(ConfigPtr);
  IrqAsclin_Init();

  SRC_ASCLIN2TX.B.SRE = UART_SRC_SET_SRE;
  SRC_ASCLIN2RX.B.SRE = UART_SRC_SET_SRE;
  SRC_ASCLIN2ERR.B.SRE = UART_SRC_SET_SRE;

  do
  {
    print_f("\n\n");
    print_f("\n/********************************************************************");
    print_f("*************/\n");
    print_f("\n                 UART DRIVER DEMOAPP MENU                 		  \n");
    print_f("                      ENTER YOUR OPTION                       			");
    print_f("\n     <1>  Get UART Channel Status                           			");
    print_f("\n     <2>  Transmit and Receive Data on the UART Channel in Read    	");
    print_f("\n     <3>  Abort After Data Transmission and Reception       			");
    print_f("\n     <4>  Abort On-Going Data Transmission and Reception    		    ");
    print_f("\n     <5>  Transmit and Receive Data on the UART Channel in Streaming ");
    print_f("\n     <6>  Stop Streaming Mode						    			");
    print_f("\n     <7>  Stop Streaming On-Going Data Reception                     ");
    print_f("\n     <.>  Back To Main Menu                                 			");
    print_f("\n/********************************************************************");
    print_f("*************/\n");
    print_f("Enter Your Option: ");

    getline(szString, sizeof szString - 1);
    print_f("\n\n");

    switch (*szString)
    {
      case '1':
      {
        UartDemo_GetChStatus();
        break;
      }

      case '2':
      {
        UartDemo_ReadWrite();
        break;
      }

      case '3':
      {
        UartDemo_GetDataTxnInfo();
        break;
      }

      case '4':
      {
        UartDemo_AbortReadWrite();
        break;
      }

      case '5':
      {
        UartDemo_StreamWrite();
        break;
      }

      case '6':
      {
        UartDemo_StopStream();
        break;
      }

      case '7':
      {
        UartDemo_StopStreamWrite();
        break;
      }

      case '.':
      {
        UartLoopVar = 1;
        break;
      }
    }
  } while(UartLoopVar == 0);

  print_f("\n---------------  End of UART Driver Demo ---------------\n");
}
