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
**  FILENAME   : I2c_Demo.c                                                  **
**                                                                           **
**  VERSION    : 2.0.0                                                       **
**                                                                           **
**  DATE       : 2020-05-18                                                  **
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
**                - Demo application for I2C driver                          **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                     **
**                                                                           **
******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Std_Types.h"
#include "Test_Print.h"
#include "Test_Time.h"
#include "I2c.h"
#include "Irq.h"
#include "IfxSrc_reg.h"
#include "I2c_Demo.h"

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

#define I2C_SLAVE_ADDRESS   (0x50)
#define I2C_SIZE_8_BYTE     (8U)
#define I2C_CHANNEL_0       (0U)
#define I2C_ZERO            ((uint8)0U)
#define I2C_ONE             ((uint8)1U)

/*******************************************************************************
**                      Private Variable Declarations                         **
*******************************************************************************/
I2c_ChannelType ChannelId = I2C_CHANNEL_0;
I2c_SizeType Size = I2C_SIZE_8_BYTE;
I2c_SlaveAddrType SlaveAddress = I2C_SLAVE_ADDRESS;
I2c_DataType Buffer[I2C_SIZE_8_BYTE];
I2c_ErrorType Error_value;
I2c_DataType ReadBuffer[I2C_SIZE_8_BYTE] = {0};
volatile uint32 Notif_count = 0U;

extern const I2c_ConfigType I2c_Config;
uint32 TempVal;
volatile static I2c_ErrorType Sync_SlaveBusy_Check;
static volatile uint8 Check_Slave_Busy_Synch = 0;

/*******************************************************************************
**                      Private Register Declarations                         **
*******************************************************************************/

void I2c_NotifFunctionPtrfun(I2c_ErrorType ErrorId);
void I2c_Check_Slave_Busy_Sync(void);

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/

/*******************************************************************************
** Syntax : void I2c_Demo(void)                                               **
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
** Description : Writes and Reads data from EEPROM synchronously using I2C   **
*******************************************************************************/
void I2c_Demo(void)
{
  uint8 LoopCount;
  uint8 data = 0;
  uint8 Count = 0;
  volatile I2c_ErrorType RetValI2c_SyncWrite;

  IrqI2c_Init();

  SRC_I2C0DTR.B.SRE = 0x0;
  SRC_I2C0ERR.B.SRE = 0x0;
  SRC_I2C0P.B.SRE = 0x0;

  I2c_Init(&I2c_Config);

  print_f("\n------ Start of I2C demo ------\n");

  for (LoopCount = I2C_ZERO; LoopCount < I2C_SIZE_8_BYTE; LoopCount++)
  {
    Buffer[LoopCount] = data;
    data = data + 1;
  }

  print_f ("\n Writing into EEPROM started\n");

  RetValI2c_SyncWrite = I2c_SyncWrite(ChannelId, Buffer, I2C_SIZE_8_BYTE, SlaveAddress);

  print_f ("\n Writing into EEPROM Successfull\n");

  while(RetValI2c_SyncWrite != I2C_NO_ERR) {}

  I2c_Check_Slave_Busy_Sync();

  I2c_SyncRead(ChannelId, ReadBuffer, I2C_SIZE_8_BYTE, SlaveAddress);

  for(LoopCount = I2C_ZERO ; LoopCount < 7 ; LoopCount++)
  {
    if(Buffer[LoopCount + 1] == ReadBuffer[LoopCount])
    {
      Count = 0;
    }
    else
    {
      Count = Count + 1;
    }
  }

  if(Count == 0)
  {
    print_f("\n Sent and Recieved data matched... Read Successfull...\n");
    print_f ("\n Reading from EEPROM Successfull and the data is matching\n");
    print_f("\n");
    StartResult();
    print_f("\nResult = Pass;");
    EndResult();
  }
  else
  {

    print_f("\n Sent and Recieved data missmatched... Read Unsuccessfull...\n");
    print_f ("\n Reading from EEPROM failed and data is mismatched\n");
    print_f("\n");
    StartResult();
    print_f("\nResult = Fail;");
    EndResult();
  }

  print_f("\n");

  print_f("------ End of I2C Demo------\n");
}

/*******************************************************************************
** Syntax : void I2c_NotifFunctionPtrfun(I2c_ErrorType ErrorId)               **
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
** Description : DemoApp Function for Notification from ISR                   **
*******************************************************************************/
void I2c_NotifFunctionPtrfun(I2c_ErrorType ErrorId)
{
  Notif_count++;
}

/*******************************************************************************
** Syntax : void I2c_Check_Slave_Busy_Sync(void)                              **
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
** Description : Function to wait untill Slave is Busy with operation         **
*******************************************************************************/
void I2c_Check_Slave_Busy_Sync(void)
{
  I2c_ChannelType ChannelId = I2C_CHANNEL_0;
  I2c_DataType NodeAddr[I2C_SIZE_8_BYTE];
  I2c_SlaveAddrType SlaveAddress = I2C_SLAVE_ADDRESS;
  NodeAddr[0] = 0x00u;

  do
  {
    Sync_SlaveBusy_Check = I2c_SyncWrite(ChannelId, NodeAddr, I2C_ONE, SlaveAddress);

    if (Sync_SlaveBusy_Check != I2C_NO_ERR)
    {
      Check_Slave_Busy_Synch =  TRUE;
      Timer_DelayMs(1);
    }
    else if(Sync_SlaveBusy_Check == I2C_NO_ERR)
    {
      Check_Slave_Busy_Synch = FALSE;
      Timer_DelayMs(1);
    }
    else
    {

    }
  } while(Check_Slave_Busy_Synch == TRUE);

  Check_Slave_Busy_Synch = FALSE;
}

