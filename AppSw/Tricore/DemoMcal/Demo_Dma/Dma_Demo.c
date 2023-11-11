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
**  FILENAME   : Dma_Demo.c                                                  **
**                                                                           **
**  VERSION    : 0.0.2                                                       **
**                                                                           **
**  DATE       : 2016-12-16                                                  **
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
**                - Demo application for DMA driver                          **
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
#include "Dma_Demo.h"
#include "Dma.h"
#include "DemoApp_Cfg.h"
#include "IfxDma_reg.h"
/******************************************************************************
**                      Imported Compiler Switch Check                       **
******************************************************************************/
/******************************************************************************
**                      Private Macro Definitions                            **
******************************************************************************/
#define DMA_TEST_DATA_LENGTH   ((uint8)14U)
/******************************************************************************
**                      Private Type Definitions                             **
******************************************************************************/

/******************************************************************************
**                      Private Function Declarations                        **
******************************************************************************/
void DemoApp_Dma_Init(void);

/******************************************************************************
**                      Global Constant Definitions                          **
******************************************************************************/
#define DMA_START_SEC_CONST_ASIL_B_GLOBAL_32
/*
* Since channel data width to be used is 32bit so all variables will be 32bit aligned.
* If data width is changed then Dma_MemMap section might be needed to change accordingly.
* Here in this section const variables will be kept
* Inclusion of Dma_MemMap.h
*/
#include "Dma_MemMap.h"

const uint8 Dma_SourceBuffer[DMA_TEST_DATA_LENGTH] =
{'D', 'M', 'A', ' ', 'D', 'E', 'M', 'O', ' ', 'P', 'A', 'S', 'S', ' '};

static const uint8 DmaDemo_DefaultString[DMA_TEST_DATA_LENGTH] =
{'D', 'M', 'A', ' ', 'D', 'E', 'M', 'O', ' ', 'F', 'A', 'I', 'L', ' '};

#define DMA_STOP_SEC_CONST_ASIL_B_GLOBAL_32
#include "Dma_MemMap.h"
/*
* for 32bit non constant variables
* Inclusion of Dma_MemMap.h
*/


uint8 Dma_Destinationbuffer[DMA_TEST_DATA_LENGTH] =
{'D', 'M', 'A', ' ', 'D', 'E', 'M', 'O', ' ', 'F', 'A', 'I', 'L', ' '};


/******************************************************************************
 **                      Global Variable Definitions                         **
 *****************************************************************************/
#define DMA_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
#include "Dma_MemMap.h"

extern const Dma_ConfigType Dma_Config;

#define DMA_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
#include "Dma_MemMap.h"
/******************************************************************************
**                      Local Function Declarations                          **
******************************************************************************/
/******************************************************************************
** Syntax : void Dma_Demo(void)                                              **
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
** Description : Demo Tests for all the delivered Modules.                   **
******************************************************************************/

void Dma_Demo(void)
{
  uint16 tcount;
  uint8 i;
  uint8 Error_flag = 0;
  Dma_ConfigUpdateType lChConfig;
  /* Create configuration data structure to change post-build configuration of source and destination address*/
  /* Pointer to configuration data is passed as argument to Dma_ChUpdate() API  */
  lChConfig.SourceAddress = (uint32)&Dma_SourceBuffer[0U];
  lChConfig.DestAddress   = (uint32)&Dma_Destinationbuffer[0U];
  lChConfig.UpdateSourceAddress = 1;
  lChConfig.UpdateDestAddress  = 1;                    /* Should Destination address be updated?*/
  lChConfig.UpdateControlAdicr      = 0;               /* Should ADICR be updated? */
  lChConfig.UpdateConfig       = 0;                    /* Should CHCFG be updated? */
  lChConfig.UpdateShadowConfig = 0;                    /* Should SHADR be updated? */
  lChConfig.UpdateAddressCrc   = 0;                    /* Should SDCRC be updated? (needed in case of safeLinkedList) */
  lChConfig.UpdateAddressCrc = 0;                      /* Contents of SHADR */
  lChConfig.UpdateDataCrc = 0;                         /* Contents of SDCRC register */

  /* Call DMA driver initialization */
  if(E_OK != Dma_IsInitDone())
  {
    /* Init only for the First instance */
    DemoApp_Dma_Init();
  }

  tcount = (uint16)DMA_TEST_DATA_LENGTH;
  print_f("\n Source value= ");
  for (i = 0U; i < tcount; i++)
  {
    put_char(Dma_SourceBuffer[i]);
  }
  print_f("\n Original Destination value= ");
  for (i = 0U; i < tcount; i++)
  {
    Dma_Destinationbuffer[i] = DmaDemo_DefaultString[i];
    put_char(Dma_Destinationbuffer[i]);
    if(Dma_Destinationbuffer[i] != DmaDemo_DefaultString[i])
    {
      Error_flag = 1;
    }
  }

  /* Update source and destination address of channel 16 at Run time */
  Dma_ChUpdate(16, &lChConfig, NULL_PTR);
  /* Start software transaction for channel 16 */
  Dma_ChStartTransfer(16);

  print_f("\n Final Destination value = ");

  for (i = 0U; i < tcount; i++)
  {
    put_char(Dma_Destinationbuffer[i]);
  }
  print_f("\n\n");

  if(Error_flag == 1)
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

}/* end of Dma_Demo */

/******************************************************************************
** Syntax : void DemoApp_Dma_Init(void)                                      **
**                                                                           **
** Service ID:   : NA                                                        **
**                                                                           **
** Sync/Async:   : Synchronous                                               **
**                                                                           **
** Reentrancy:   : Reentrant                                                 **
**                                                                           **
** Parameters (in): none                                                     **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value: none                                                        **
**                                                                           **
** Description : Initialize DMA module                                       **
******************************************************************************/
void DemoApp_Dma_Init(void)
{
  const Dma_ConfigType * ConfigPtr = NULL_PTR;
  ConfigPtr = &Dma_Config;
  Dma_Init(ConfigPtr);
  /* Wait till the Initialization is over */
  while(Dma_IsInitDone() == TRUE)
  {}
}
