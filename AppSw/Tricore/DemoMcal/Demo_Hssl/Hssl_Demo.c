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
**  FILENAME   : Hssl_Demo.c                                                 **
**                                                                           **
**  VERSION    : 4.0.0                                                       **
**                                                                           **
**  DATE       : 2020-03-09                                                  **
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
**                - Demo application for HSSL driver                         **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                     **
**                                                                           **
******************************************************************************/

/******************************************************************************
**                      Includes                                             **
******************************************************************************/
#include "Std_Types.h"
#include "Test_Print.h"
#include "Test_Time.h"
#include "IfxHssl_reg.h"
#include "IfxSrc_reg.h"
#include "Dma.h"
#include "Irq.h"
#include "Port.h"
#include "Hssl_Demo.h"

/******************************************************************************
**                      Imported Compiler Switch Check                       **
******************************************************************************/

/******************************************************************************
**                      Private Macro Definitions                            **
******************************************************************************/
#define TOGGLE_DELAY                            1200U
#define BIT_TOGGLE_CNT_START_STREAM             10U
#define BIT_TOGGLE_CNT_STOP_STREAM              100U

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
extern const Dma_ConfigType Dma_Config;

/******************************************************************************
**                      Private Constant Definitions                         **
******************************************************************************/
/* Global Variable Declaration*/
const Hssl_ConfigType* const Address = NULL_PTR;

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/

volatile uint32 RetVal_HsslCh0_COK_CallBack = 0xFF;
volatile uint32 RetVal_HsslCh2_COK_CallBack = 0xFF;

Hssl_InstanceID id = HSSL0;

uint8 TimeoutErr = 0;
uint8 TransID = 0;
uint8 AckErr = 0;
uint16 DataSize = HSSL_DATA_SIZE_32BIT;
uint32 DataBuffer_DMA[8U];

Hssl_DataTemplateType WriteDataDMA[4U];
static Ifx_HSSL* const HSSL_Reg[] = {&MODULE_HSSL0};
volatile uint32 RetVal_MultiWriteAck =0x0FF;

#define HSSL_START_SEC_VAR_CLEARED_QM_LOCAL_256
#include "Hssl_MemMap.h"

uint32 DataAddress[32];
uint32 StreamReadDataBuffer[32];

#define HSSL_STOP_SEC_VAR_CLEARED_QM_LOCAL_256
#include "Hssl_MemMap.h"


Hssl_DataTemplateType ReadData_1;   
Hssl_DataTemplateType ReadData_2;   
Hssl_DataTemplateType ReadData_3;   
Hssl_DataTemplateType ReadData_4; 
uint32 ReadDataBuffer_1 = 0xABCD1234U;
uint32 JTAG_ID_Buffer;
Hssl_DataTemplateType WriteData;
/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
void Hssl0_MultiWrite_Callback_Function(Dma_EventsType Event);

void Hssl0_MultiWrite_Callback_Function (Dma_EventsType Event)
{
 RetVal_MultiWriteAck =0x01U;
}

/*Write Successful Interrupt*/  
IFX_NO_INLINE void HsslCh0_COK_CallBackFunction(uint32 Event)
{
    RetVal_HsslCh0_COK_CallBack = 0x01U;
}

/*Write Successful Interrupt*/  
IFX_NO_INLINE void HsslCh2_COK_CallBackFunction(uint32 Event)
{
    RetVal_HsslCh2_COK_CallBack = 0x01U;
}

/******************************************************************************
** Syntax : void Hssl_Demo(void)                                             **
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
** Return value: none                                                        **
**                                                                           **
** Description : HSSL driver Demo function                                   **
******************************************************************************/
void Hssl_Demo(void)
{

  uint8 TempUSage = 1;
  char szString[80];

  while (TempUSage == 1)
  {
    print_f("\n");
    print_f("\n/*********************************************************/\n");
    print_f("\n           HSSL DRIVER DEMO MENU                          ");
    print_f("\n                                                         ");
    print_f("\n 1: Hssl Register Write");
    print_f("\n 2: Hssl Register Read");
    print_f("\n 3: Multiple Hssl Register Write");
    print_f("\n 4: Start Stream Data");
    print_f("\n 5: Stop Stream Data");
    print_f("\n 6: Read ID");
    print_f("\n x. Go back to Main Menu    ");
    print_f("\n  ENTER YOUR OPTION   : ");
    getline(szString, sizeof szString - 1);

    switch (*szString)
    {
      case '1':
        Hssl_RegisterWriteDemo();
        break;

      case '2':
        Hssl_RegisterReadDemo();
        break;
    
      case '3':
        Hssl_MultipleRegisterWriteDemo();
        break;
    
      case '4':
        Hssl_StartStreamingDemo();
        break;
    
      case '5':
        Hssl_StopStreamingDemo();
        break;

      case '6':
        Hssl_IDReadDemo();
        break;
    
      case 'x':
      case 'X':
        TempUSage = 0;
        print_f("\n\n/*************************************************/\n\n");
        break;
    
      default:
        print_f("\n\n  INVALID OPTION \n\n");
        break;
    }
  }

}

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/
/******************************************************************************
** Syntax : void Hssl_RegisterWriteDemo(void)                                **
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
** Return value: none                                                        **
**                                                                           **
** Description : This routine performs a direct write transfer.              **
******************************************************************************/
void Hssl_RegisterWriteDemo(void)
{
  print_f("\n Hssl Register Write Demo");

  uint8 Error_flag = 0;
  uint32 DataBuffer = 0xABCDEF01U;
  uint32 DataAddr=  0x70003420U;
  WriteData.Data = &DataBuffer;
  WriteData.Address = &DataAddr;
  Hssl_ChannelType Channel_Number;
  Channel_Number.Number = 0;
  Channel_Number.Timeout = 0xFFFFFFFFU;
  Std_ReturnType RetVal_WriteAck = 0xFF;
  
  /* Put HSSL in Init Mode */
  Hssl_Init (Address) ;
  Hssl_SetMode(id,1) ;
  Hssl_SetMode(id,2) ;
  Hssl_InitChannel(id, &Channel_Number, TimeoutErr, TransID, AckErr);

  SRC_HSSL0COK0.B.SRE = 0x1;
  SRC_HSSL0RDI0.B.SRE = 0x1;

  print_f ("\n Writing to address= %X Data = %X \n ", DataAddr, DataBuffer);

  Hssl_Write (id,&WriteData, HSSL_DATA_SIZE_32BIT, &Channel_Number, 0U);
  RetVal_WriteAck = Hssl_WriteAck(id, &Channel_Number); 
  
  if(RetVal_WriteAck != E_OK)
  {
    Error_flag = 1;
  }
  
   if(Error_flag == 1)
  {
    print_f("\n Data not written to the slave");

    StartResult();
    print_f("\n Result = Fail;");
    EndResult();
  }
  else
  {
    print_f("\n Data written to the slave");      

    StartResult();
    print_f("\n Result = Pass;");
    EndResult();
  }

  Hssl_Reset(id);
}

/*******************************************************************************
** Syntax : void Hssl_RegisterReadDemo(void)                                  **
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
** Description : This routine Reads Data from the microcontroller             **
*******************************************************************************/
void Hssl_RegisterReadDemo(void )
{
  print_f("\n Hssl Register Read Demo");

  uint8 Error_flag = 0;
  uint32 DataAddr=  0x70003420U;
  Hssl_ChannelType Channel_Number;
  Channel_Number.Number = 0;
  Channel_Number.Timeout = 0xFFFFFFFFU;
  Std_ReturnType RetVal_ReadRply = 0xFF;
  uint32 RetVal_ReadData = 0xFFU;
  Hssl_DataTemplateType ReadData;
  ReadData.Address = &DataAddr;
  uint32 ReadDataBuffer = 0xABCD1234U;
  ReadData.Data = &ReadDataBuffer;
  
  /* Put HSSL in Init Mode */
  Hssl_Init (Address) ;
  Hssl_SetMode(id,1) ;
  Hssl_SetMode(id,2) ;
  Hssl_InitChannel(id, &Channel_Number, TimeoutErr, TransID, AckErr);
 
  SRC_HSSL0COK0.B.SRE = 0x1;
  SRC_HSSL0RDI0.B.SRE = 0x1;

  print_f ("\n Reading to address= %X \n", DataAddr);

  Hssl_Read(id, &ReadData, DataSize, &Channel_Number, 0U);
  RetVal_ReadRply = Hssl_ReadRply(id, &Channel_Number); 

  if(RetVal_ReadRply == E_OK)
  {
      RetVal_ReadData = *ReadData.Data;
  }
    else
  {
    Error_flag = 1;
  }
  
   if(Error_flag == 1)
  {
    print_f("\n Data was not read from the Target");

    StartResult();
    print_f("\n Result = Fail;");
    EndResult();
  }
  else
  {
    print_f("\n Data read successfully from the Target");
    print_f("\n Read data value is : %X",RetVal_ReadData);

    StartResult();
    print_f("\n Result = Pass;");
    EndResult();
  }
  
    Hssl_Reset(id);
}

/*******************************************************************************
** Syntax : void Hssl_MultipleRegisterWriteDemo(void)                         **
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
** Description : This routine does direct transfer of multiple set of data    **
*******************************************************************************/
void Hssl_MultipleRegisterWriteDemo(void )
{
  print_f("\n Hssl Multiple Register Write Demo\n" );

  uint8 Error_flag = 0;
  Hssl_ChannelType Channel_Number;
  volatile Ifx_HSSL_I_ICON *CtrlRegPtr;
  Channel_Number.Number = 0;
  Channel_Number.Timeout = 0xFFFFFFFFU;
  uint8 TimeoutErr = 0;
  uint8 TransID = 0;
  uint8 AckErr = 0;
  uint16 DataSize = HSSL_DATA_SIZE_32BIT;
  uint16 NumCmd  = 4;
  uint16 InjectedError = 0;

  Std_ReturnType RetVal_Read_1 = 0xFF;
  Std_ReturnType RetVal_Read_2 = 0xFF;
  Std_ReturnType RetVal_Read_3 = 0xFF;
  Std_ReturnType RetVal_Read_4 = 0xFF;
  #if (HSSL_OPERATING_MODE == HSSL_POLLING_MODE)
  Std_ReturnType RetVal_ReadRply_1 = 0xFF;
  Std_ReturnType RetVal_ReadRply_2 = 0xFF;
  Std_ReturnType RetVal_ReadRply_3 = 0xFF;
  Std_ReturnType RetVal_ReadRply_4 = 0xFF;
  #endif
  uint32 RetVal_ReadData_1 = 0xFF;
  uint32 RetVal_ReadData_2 = 0xFF;
  uint32 RetVal_ReadData_3 = 0xFF;
  uint32 RetVal_ReadData_4 = 0xFF;
  
  uint32 DataAddr_1=  0x70003420U;
  ReadData_1.Address = &DataAddr_1;
  ReadData_1.Data = &ReadDataBuffer_1;    
  
  uint32 ReadDataBuffer_2 = 0xABCD1234U;
  uint32 DataAddr_2 =  0x70003430U;
  ReadData_2.Address = &DataAddr_2;
  ReadData_2.Data = &ReadDataBuffer_2;
  
  uint32 ReadDataBuffer_3 = 0xABCD1234U;
  uint32 DataAddr_3=  0x70003440U;
  ReadData_3.Address = &DataAddr_3;
  ReadData_3.Data = &ReadDataBuffer_3;
  
  uint32 ReadDataBuffer_4 = 0xABCD1234U;
  uint32 DataAddr_4=  0x70003450U;
  ReadData_4.Address = &DataAddr_4;
  ReadData_4.Data = &ReadDataBuffer_4;

  DataBuffer_DMA[0U] = 0x11111111U;
  DataBuffer_DMA[1U] = 0x70003420U;
  DataBuffer_DMA[2U] = 0x22222222U;
  DataBuffer_DMA[3U] = 0x70003430U;
  DataBuffer_DMA[4U] = 0x33333333U;
  DataBuffer_DMA[5U] = 0x70003440U;
  DataBuffer_DMA[6U] = 0x44444444U;
  DataBuffer_DMA[7U] = 0x70003450U;
  
  WriteDataDMA[0U].Data = &DataBuffer_DMA[0U] ;
  WriteDataDMA[0U].Address = &DataBuffer_DMA[1U];
  WriteDataDMA[1U].Data = &DataBuffer_DMA[2U] ;
  WriteDataDMA[1U].Address = &DataBuffer_DMA[3U];
  WriteDataDMA[2U].Data = &DataBuffer_DMA[4U] ;
  WriteDataDMA[2U].Address = &DataBuffer_DMA[5U];
  WriteDataDMA[3U].Data = &DataBuffer_DMA[6U] ;
  WriteDataDMA[3U].Address = &DataBuffer_DMA[7U];
              
  Dma_Init(&Dma_Config);
  Port_Init(&Port_Config);

  IrqDma_Init();
  IrqHssl_Init();

  SRC_DMACH3.B.SRE = 1;
  MODULE_SRC.DMA.DMA[0].ERR[0].B.SRE = 1;
  MODULE_SRC.DMA.DMA[0].ERR[1].B.SRE = 1;
      
  SRC_HSSL0COK0.B.SRE = 0x1;
  SRC_HSSL0RDI0.B.SRE = 0x1;
  
 
  /* Writing data to target */
  Hssl_Init(Address);
  Hssl_SetMode(id, 1);
  Hssl_SetMode(id, 2);
  Hssl_InitChannel(id, &Channel_Number, TimeoutErr, TransID, AckErr);
  Hssl_MultiWrite(id, (Hssl_DataTemplateType *)WriteDataDMA, DataSize, NumCmd, &Channel_Number, InjectedError);
  
  CtrlRegPtr = (&HSSL_Reg[id]->I[Channel_Number.Number].ICON);

  while(CtrlRegPtr->B.BSY != 0U)
  {
  }

  Channel_Number.Number = 1;  
  /* Hssl_InitChannel(id, Channel_Number, TimeoutErr, TransID, AckErr); */
  
  /*Single Read operatin */
  RetVal_Read_1 = Hssl_Read(id, &ReadData_1, DataSize, &Channel_Number, InjectedError);

  if(RetVal_Read_1 == E_OK)
  {
      #if (HSSL_OPERATING_MODE == HSSL_POLLING_MODE)
      RetVal_ReadRply_1 = Hssl_ReadRply(id, &Channel_Number); 

      if(RetVal_ReadRply_1 == E_OK)
      {
          RetVal_ReadData_1 = *ReadData_1.Data;
      }
      #endif
  }

  /*Single Read operatin */
  RetVal_Read_2 = Hssl_Read(id, &ReadData_2, DataSize, &Channel_Number, InjectedError);

  if(RetVal_Read_2 == E_OK)
  {
      #if (HSSL_OPERATING_MODE == HSSL_POLLING_MODE)
      RetVal_ReadRply_2 = Hssl_ReadRply(id, &Channel_Number); 

      if(RetVal_ReadRply_2 == E_OK)
      {
          RetVal_ReadData_2 = *ReadData_2.Data;
      }
      #endif
  }

  /*Single Read operatin */
  RetVal_Read_3 = Hssl_Read(id, &ReadData_3, DataSize, &Channel_Number, InjectedError);

  if(RetVal_Read_3 == E_OK)
  {
      #if (HSSL_OPERATING_MODE == HSSL_POLLING_MODE)
      RetVal_ReadRply_3 = Hssl_ReadRply(id, &Channel_Number); 

      if(RetVal_ReadRply_3 == E_OK)
      {
          RetVal_ReadData_3 = *ReadData_3.Data;
      }
      #endif
  }


  /*Single Read operatin */
  RetVal_Read_4 = Hssl_Read(id, &ReadData_4, DataSize, &Channel_Number, InjectedError);

  if(RetVal_Read_4 == E_OK)
  {
      #if (HSSL_OPERATING_MODE == HSSL_POLLING_MODE)
      RetVal_ReadRply_4 = Hssl_ReadRply(id, &Channel_Number); 

      if(RetVal_ReadRply_4 == E_OK)
      {
          RetVal_ReadData_4 = *ReadData_4.Data;
      }
      #endif
  }
         
  if((RetVal_ReadData_1 != 0x11111111U) && (RetVal_ReadData_4 != 0x44444444U))
  {
    Error_flag = 1;
  }  

  if(Error_flag == 1)
  {
    print_f ("\n Data is not written to the target") ;

    StartResult();
    print_f(" \n Result = Fail;");
    EndResult();
  }
  else
  {
    print_f("\n Multiple data values are written successfully to the Target");
    print_f("\n Read back values from slave\n");
    print_f("Value 1: %X \n",RetVal_ReadData_1);
    print_f("Value 2: %X \n",RetVal_ReadData_2);
    print_f("Value 3: %X \n",RetVal_ReadData_3);
    print_f("Value 4: %X \n",RetVal_ReadData_4);

    StartResult();
    print_f(" Result = Pass; \n");
    EndResult();
  }

  Hssl_Reset(id);
}

/*******************************************************************************
** Syntax : void Hssl_IDReadDemo(void)                                        **
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
** Description : This routine Reads the JTAG ID                               **
*******************************************************************************/
void Hssl_IDReadDemo(void )
{
  print_f("\n Hssl ID Demo \n");

  uint8 Error_flag = 0;
  Hssl_ChannelType Channel_Number;
  Channel_Number.Number = 0;

  Channel_Number.Timeout = 0xFF;
  Std_ReturnType RetVal_Hssl_Id = 0xFF;
 
  /*Initialising HSSL module, setting the operating mode to run and initialising the channel*/
  Hssl_Init(Address);
  Hssl_SetMode(id, 1);
  Hssl_SetMode(id, 2);
  
  /*Request to read JTAG ID of the Target*/
  RetVal_Hssl_Id = Hssl_Id(id, &JTAG_ID_Buffer, &Channel_Number);
  
  if((RetVal_Hssl_Id != E_OK) || (JTAG_ID_Buffer != 0xABCDEF06))
  {
      Error_flag = 1;
  }
  
  if(Error_flag == 1)
  {
    print_f("\n Unable to read HSSL ID");

    StartResult();
    print_f("\n Result = Fail;");
    EndResult();
  }
  else
  {
    print_f("\n HSSL_ID is read from the Target");
    print_f("\n HSSL ID Value is: %X",JTAG_ID_Buffer);

    StartResult();
    print_f("\n Result = Pass;");
    EndResult();
  }
  
  Hssl_Reset(id);
}

/*******************************************************************************
** Syntax : void Hssl_StartStreamingDemo(void)                                **
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
** Description : This routine starts a streaming transfer                     **
*******************************************************************************/
void Hssl_StartStreamingDemo(void)
{
  print_f("\n Hssl Write Stream Demo \n ");

  uint8 Error_flag = 0;
  Hssl_ChannelType Channel_1;
  Channel_1.Number = 1U;
  Channel_1.Timeout = 0xFFFFFFFFU;
  uint16 InjectedError = 0U;
  
  uint32 Index =0;
  uint32 Dst_Addr = 0x70003450U;
  uint32 *DestinationAddressStart = &Dst_Addr;
  Std_ReturnType RetVal_Read = 0xFF;
  #if (HSSL_OPERATING_MODE == HSSL_POLLING_MODE)
  Std_ReturnType RetVal_ReadRply = 0xFF;
  #endif
  uint16 DataSize = HSSL_DATA_SIZE_32BIT;
  uint32 ReadDataBuffer = 0x00000000U;
  
  Hssl_DataTemplateType ReadData;
  ReadData.Data = &ReadDataBuffer;

  Hssl_Init(Address);
  IrqHssl_Init();
  Hssl_SetMode(id, 1);
  Hssl_SetMode(id, 2);
  
  SRC_HSSL0COK2.B.SRE = 0x1;

  #if (HSSL1_CONFIGURRED == STD_ON) 
  SRC_HSSL1COK2.B.SRE = 0x1;
  #endif  
              
  for(Index = 0U; Index < 32U; Index++)
  {
      DataAddress[Index] = 0xABCDEF00+Index;
  }
              
  Hssl_StartStream(id, (&DataAddress[0]), (uint32*)*DestinationAddressStart, 4, InjectedError);
  
  while(RetVal_HsslCh2_COK_CallBack !=1)
  {
    /*Waiting for the COK callback to confirm successful completion of write stream*/
    Timer_DelayTicks(5000);
    break;
  }
  
  /*Reading back all the data written by streaming */
  for(Index = 0U; Index < 32U; Index++)
  {
    uint32 DataAddr = 0x70003440 + 4*Index;
    ReadData.Address = &DataAddr;

    RetVal_Read = Hssl_Read(id, &ReadData, DataSize, &Channel_1, InjectedError);

    if(RetVal_Read == E_OK)
    {
        #if (HSSL_OPERATING_MODE == HSSL_POLLING_MODE)
        RetVal_ReadRply = Hssl_ReadRply(id, &Channel_1); 

        if(RetVal_ReadRply == E_OK)
        {
            StreamReadDataBuffer[Index] = *ReadData.Data;
        }
        #endif
    }
  }

  for(Index = 0U; Index < 32U; Index++)
  {
      if(StreamReadDataBuffer[Index] != DataAddress[Index])
      {
        /*Error Flag is set if Data Read back Mismatches to the 
         data transfered during Stream Transfer Mode*/
          Error_flag = 1;
      }
  }

  if(Error_flag == 1)
  {
    print_f(" \n Write operation in Stream mode has Failed");

    StartResult();
    print_f("\n Result = Fail;");
    EndResult();
  }
  else
  {
    print_f(" \n Write operation in Stream mode has completed successfully");

    StartResult();
    print_f(" \n Result = Pass;");
    EndResult();
  }
    Hssl_Reset(id);
}

/*******************************************************************************
** Syntax : void Hssl_StopStreamingDemo(void)                                 **
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
** Description : This routine Stops the streaming transfer                    **
*******************************************************************************/
void Hssl_StopStreamingDemo(void )
{
  print_f("\n Hssl Stop Streaming Demo \n" );

  uint32 RetVal_StopStream = 0xFF;
  uint8 Error_flag = 0;
  uint16 InjectedError = 0U;
  
  volatile uint16 MFlags_IMB_Val1 = 0U;
  volatile uint16 MFlags_IMB_Val2 = 0U;
  volatile uint32 Index =0;
  volatile uint32 Bit_NO_Toogle_Err_Cnt =0;
  volatile uint32 Bit_Toogle_Cnt_Start_Stream =0;
  volatile uint32 Bit_Toogle_Cnt_Stop_stream =0;
  uint32 Dst_Addr = 0x70003440U;
  uint32 *DestinationAddressStart = &Dst_Addr;

  Hssl_Init(Address);
  Hssl_SetMode(id, 1);
  Hssl_SetMode(id, 2);
  
  SRC_HSSL0COK2.B.SRE = 0x1;
              
  for(Index = 0U; Index < 32U; Index++)
  {
      DataAddress[Index] = 0xABCDEF00 + Index;
  }
       
  /*Start the stream operation*/           
  Hssl_StartStream(id, (&DataAddress[0]), (uint32*)*DestinationAddressStart, 4, InjectedError);
   
  Index=0;

 /* Ensure that IMB Bit Toggling is happening contionously after Starting Streaming Mode*/
  while(Index < BIT_TOGGLE_CNT_START_STREAM)   
  {
      MFlags_IMB_Val1 = HSSL_Reg[id]->MFLAGS.B.IMB;
      
      Timer_DelayTicks(TOGGLE_DELAY);  /* Delay provided to allow the bit to toggle */
      
      MFlags_IMB_Val2 = HSSL_Reg[id]->MFLAGS.B.IMB;
      
      if(MFlags_IMB_Val1 != MFlags_IMB_Val2)
      {
         /* Increment Bit_Toogle_Cnt_Stop_stream to indicate that Bit toggling is Happening */
          Bit_Toogle_Cnt_Start_Stream += 1;  
          Index++;
      }
  }   
    
  /*Stop the Ongoing write stream*/
  RetVal_StopStream = Hssl_StopStream(id);
    
  Index=0;
  
  /*Check if IMB Bit Toggling has Stopped after Stopping of the Streaming Mode*/
  while(Index < BIT_TOGGLE_CNT_STOP_STREAM)
  {
      MFlags_IMB_Val1 = HSSL_Reg[id]->MFLAGS.B.IMB;

      Timer_DelayTicks(TOGGLE_DELAY);  /* Delay provided to allow the bit to toggle */

      MFlags_IMB_Val2 = HSSL_Reg[id]->MFLAGS.B.IMB;
      
      if(MFlags_IMB_Val1 == MFlags_IMB_Val2) 
      {
          Bit_NO_Toogle_Err_Cnt+= 1;
          Index++;
      }
      
      if(MFlags_IMB_Val1 != MFlags_IMB_Val2)
      {
         /* Increment Bit_Toogle_Cnt_Stop_stream to indicate that bit toggling has not stopped */
          Bit_Toogle_Cnt_Stop_stream += 1;
      }
  }
  
  /*TSE and ISB bits will be zero after stream operation is stopped*/
  if((HSSL_Reg[id]->MFLAGS.B.TSE != 0U) || (HSSL_Reg[id]->MFLAGS.B.ISB != 0U)
    || (RetVal_StopStream != E_OK) || (Bit_Toogle_Cnt_Stop_stream != 0))
  {
     Error_flag = 1;
  }
    
  if(Error_flag == 1)
  {
    print_f("\n Stopping the Write operation in Stream mode has Failed");

    StartResult();
    print_f("\n Result = Fail;");
    EndResult();
  }
  else
  {
    print_f("\n Stopping the Write operation in Stream mode has been successfull");

    StartResult();
    print_f("\n Result = Pass;");
    EndResult();
  }
  
  Hssl_Reset(id);
}

