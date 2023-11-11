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
**  FILENAME   : Spi_Demo.c                                                  **
**                                                                           **
**  VERSION    : 2.0.0                                                       **
**                                                                           **
**  DATE       : 2021-07-09                                                  **
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
**                - Demo application for SPI driver                          **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                     **
**                                                                           **
******************************************************************************/

/******************************************************************************
**                      Includes                                             **
******************************************************************************/
#include "IfxSrc_reg.h"
#include "Irq.h"
#include "Spi_Demo.h"
#include "Test_Print.h"
#include "Test_Time.h"

/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/

extern const Spi_ConfigType Spi_Config;

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/

/* Align Transmit and Receive Data Buffer to 4 byte boundary for DMA Operation*/
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE0_32
#include "Spi_MemMap.h"

/* IB/EB Buffer used to load & Read data bytes for Write */
volatile Spi_DataBufferType  SpiWrite_Data_Buffer[20u];
volatile Spi_DataBufferType  SpiRead_Data_Buffer[20u];

#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_32
#include "Spi_MemMap.h"

static volatile uint8 QSPI_Transfer_Status = TRUE;

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
#define SPI_START_SEC_CODE_ASIL_B_GLOBAL
#include "Spi_MemMap.h"

uint8 Spi_Synch_Demo(void);
uint8 Spi_Asynch_Demo(void);
void Spi_Dma_Irq_Init(void);

#define SPI_STOP_SEC_CODE_ASIL_B_GLOBAL
#include "Spi_MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define SPI_START_SEC_CODE_ASIL_B_GLOBAL
#include "Spi_MemMap.h"

/*******************************************************************************
** Syntax : void Spi_Demo (void)                                              **
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
** Description : DemoApp for SPI driver                                       **
**                                                                            **
*******************************************************************************/
void Spi_Demo(void)
{
  char szString[80];
  volatile uint8 TempUSage = 0;

  uint8 QSPI_Transfer_Result = 0U;
  
  #if ((SPI_LEVEL_DELIVERED == 1U)||(SPI_LEVEL_DELIVERED == 2U))
  /* Enable QSPI and DMA Irqs */
  Spi_Dma_Irq_Init();
  #endif
  
  Spi_Init(&Spi_Config);

  while (!TempUSage)
  {
    print_f("\n\n\n");
    print_f("\n/*********************************************************/\n");
    print_f("\n                SPI DRIVER DEMOAPP MENU                   \n ");
    print_f("\n                                                          \n ");
    print_f("     1.  Transfer IB data over QSPI0 using Synch Sequence   \n ");
    print_f("     2.  Transfer EB data over QSPI2 using Asynch Sequence  \n ");
    print_f("     x.  Back To Main Menu                                  \n ");
    print_f("                                                            \n ");
    print_f("\n/*********************************************************/\n");
    print_f("  Enter Your Option :: ");

    getline(szString, sizeof szString - 1);

    switch (*szString)
    {
      case '1':
      {
        QSPI_Transfer_Result = Spi_Synch_Demo();
        
        if(QSPI_Transfer_Result == FALSE) 
        {
          print_f("\n QSPI Synch Mode Communication Failure \n");

          StartResult();
          print_f("Result = FAIL;");
          EndResult();
        }
        else
        {
          print_f("\n QSPI Synch Mode Communication Success \n");
          StartResult();
          print_f("Result = PASS;");
          EndResult();
        }
        break;
      }
      case '2':
      {
        QSPI_Transfer_Result = Spi_Asynch_Demo();
        
        if(QSPI_Transfer_Result == FALSE) 
        {
          print_f("\n QSPI Asynch Mode Communication Failure \n");

          StartResult();
          print_f("Result = FAIL;");
          EndResult();
        }
        else
        {
          print_f("\n QSPI Asynch Mode Communication Success \n");
          StartResult();
          print_f("Result = PASS;");
          EndResult();
        }
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
} /* SPI_Demo() */

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/
/*******************************************************************************
** Syntax       : uint8 Spi_Synch_Demo(void)                                  **
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
** Description : This routine will start the SPI configured for sequence ID 0 **
**               Transmit mode     : Synchronous                              **
**               LevelDelivered    : 02                                       **
**               External Devices  : QSPI0                                    **
**               CS Selection      : CS_VIA_PERIPHERAL_ENGINE                 **
**               QSPI0 Pins used   : P20.08(CS-0),P20.13(SCLK),P20.14(MTSR)   **
**                                   P20.12(MRTS)                             **
*******************************************************************************/
uint8 Spi_Synch_Demo(void)
{
  volatile uint8 Transmit_Data_incr;
  volatile uint8 Receive_Data_incr;
  QSPI_Transfer_Status = TRUE;
  
  print_f ("\n Internal data buffer transmitted on QSPI0 : \n");
  
  for(Transmit_Data_incr = 0; Transmit_Data_incr < 20; Transmit_Data_incr++) 
  {
    SpiWrite_Data_Buffer[Transmit_Data_incr] = Transmit_Data_incr;
    print_f ("\n Write IB[%d] : %d \n ", Transmit_Data_incr, SpiWrite_Data_Buffer[Transmit_Data_incr]);
  }

  Spi_WriteIB(SpiConf_SpiChannel_SpiChannel_0, (uint8 *) &SpiWrite_Data_Buffer[0u]);
  Spi_WriteIB(SpiConf_SpiChannel_SpiChannel_1, (uint8 *) &SpiWrite_Data_Buffer[10u]);

  Spi_SyncTransmit(SpiConf_SpiSequence_SpiSequence_0);
  while(Spi_GetSequenceResult(SpiConf_SpiSequence_SpiSequence_0) != SPI_SEQ_OK)
  {
    /* Wait till write is finished */
  }
  Spi_ReadIB(SpiConf_SpiChannel_SpiChannel_0, (uint8 *)&SpiRead_Data_Buffer[0u]);
  Spi_ReadIB(SpiConf_SpiChannel_SpiChannel_1, (uint8 *)&SpiRead_Data_Buffer[10u]);

  print_f ("\n Internal data buffer Received on QSPI0 : \n");
  
  /* Evaluate the Recieved Buffer data */
  for(Receive_Data_incr = 0; Receive_Data_incr < 20; Receive_Data_incr++) 
  {
    print_f ("\n ReadIB[%d] : %d \n ", Receive_Data_incr, SpiRead_Data_Buffer[Receive_Data_incr]);

    if(SpiRead_Data_Buffer[Receive_Data_incr] != SpiWrite_Data_Buffer[Receive_Data_incr])
    {
      QSPI_Transfer_Status = FALSE;
      break;
    }
  }

  return QSPI_Transfer_Status;
}

/*******************************************************************************
** Syntax       : uint8 Spi_Asynch_Demo(void)                                 **
**                                                                            **
** Service ID   : NA                                                          **
**                                                                            **
** Sync/Async   : Synchronous                                                **
**                                                                            **
** Reentrancy   : Non Reentrant                                               **
**                                                                            **
** Parameters (in) : none                                                     **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value    : none                                                     **
**                                                                            **
** Description : This routine will start the SPI configured for sequence ID 1 **
**               Transmit mode     : Asynchronous                             **
**               LevelDelivered    : 02                                       **
**               External Devices  : QSPI2                                    **
**               CS Selection      : CS_VIA_PERIPHERAL_ENGINE                 **
*******************************************************************************/
uint8 Spi_Asynch_Demo(void)
{
  volatile uint8 Transmit_Data_incr;
  volatile uint8 Receive_Data_incr;
  QSPI_Transfer_Status = TRUE;
  
  print_f ("\n External data buffer transmitted on QSPI2 : \n");
  
  for(Transmit_Data_incr = 0; Transmit_Data_incr < 20; Transmit_Data_incr++) 
  {
    SpiWrite_Data_Buffer[Transmit_Data_incr] = 50 + Transmit_Data_incr;
    print_f ("\n EB Data Written [%d] : %d \n ", Transmit_Data_incr, SpiWrite_Data_Buffer[Transmit_Data_incr]);
  }

  #if((SPI_LEVEL_DELIVERED == 1U)||(SPI_LEVEL_DELIVERED == 2U))
  if(E_OK != Dma_IsInitDone())
  {
    /* Init only for the First instance */
    Dma_Init(&Dma_Config);
  }
  #endif

  #if (SPI_HW_QSPI2_USED == STD_ON)
  Spi_ControlLoopBack(SPI_QSPI2_INDEX, SPI_LOOPBACK_ENABLE);
  #endif

  #if(SPI_LEVEL_DELIVERED == 2U)
  Spi_SetAsyncMode((Spi_AsyncModeType)1u);
  #endif

  Spi_SetupEB(SpiConf_SpiChannel_SpiChannel_2, (uint8 *) &SpiWrite_Data_Buffer[0], (uint8 *)&SpiRead_Data_Buffer[0], 20);

  Spi_AsyncTransmit(SpiConf_SpiSequence_SpiSequence_1);

  #if (SPI_HW_QSPI2_USED == STD_ON)  
  if((Spi_GetHWUnitStatus(SPI_QSPI2_INDEX)== SPI_BUSY)&&(Spi_GetStatus()== SPI_BUSY))
  {
    Timer_DelayMs(4);
    print_f ("\n QSPI2 HW & SPI Driver are BUSY with Data Transfer\n");
  }
  #endif

  while(Spi_GetSequenceResult(SpiConf_SpiSequence_SpiSequence_1) != SPI_SEQ_OK)
  {
    /* Wait till write is finished */
  }

  print_f ("\n External data buffer Received on QSPI2 : \n");
  
  /* Evaluate the Recieved Buffer data */
  for(Receive_Data_incr = 0; Receive_Data_incr < 20; Receive_Data_incr++) 
  {
    print_f ("\n EB Data Read[%d] : %d \n ", Receive_Data_incr, SpiRead_Data_Buffer[Receive_Data_incr]);
    
    if(SpiRead_Data_Buffer[Receive_Data_incr] != SpiWrite_Data_Buffer[Receive_Data_incr])
    {
      QSPI_Transfer_Status = FALSE;
      break;
    }
  }

  #if (SPI_HW_QSPI2_USED == STD_ON)  
  if((Spi_GetHWUnitStatus(SPI_QSPI2_INDEX)!= SPI_IDLE)||(Spi_GetStatus()!= SPI_IDLE))
  {
      print_f ("\n QSPI2 HW and SPI Driver are Still BUSY \n");
      QSPI_Transfer_Status = FALSE;
  }
  else
  {
      print_f ("\n QSPI2 HW and SPI Driver are IDLE Now \n");
  }
  #endif
  
  return QSPI_Transfer_Status;
}

/*******************************************************************************
** Syntax       : void Spi_Dma_Irq_Init(void)                                 **
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
** Description : Enable Interrupts for SPI & DMA module                        **
*******************************************************************************/
void Spi_Dma_Irq_Init()
{
  /* SPI Kernel Interrupt specific Enablers */
  IrqSpi_Init();
  
  /* QSPI2 Kernel Service Request Enable */
  SRC_QSPI2RX.B.SRE = 1;
  SRC_QSPI2TX.B.SRE = 1;
  SRC_QSPI2ERR.B.SRE = 1;
  SRC_QSPI2PT.B.SRE = 1;

  /* DMA Kernel Interrupt specific Enablers */
  IrqDma_Init();

  /* DMA Channels 6 & 7 are used for SPI */  
  SRC_DMACH6.B.SRE = 1;
  SRC_DMACH7.B.SRE = 1;
}

#define SPI_STOP_SEC_CODE_ASIL_B_GLOBAL
#include "Spi_MemMap.h"

