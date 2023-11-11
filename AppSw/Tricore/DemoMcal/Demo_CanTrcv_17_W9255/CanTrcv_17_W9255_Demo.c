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
**  FILENAME   : CanTrcv_17_W9255_Demo.c                                     **
**                                                                           **
**  VERSION    : 1.0.0                                                       **
**                                                                           **
**  DATE       : 2019-04-07                                                  **
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
**                - Demo application for CAN Transceiver W9255 driver        **
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
#include "CanTrcv_17_W9255_Demo.h"
#include "Can_17_McmCan.h"
#include "Test_Print.h"
#include "SchM_Can_17_McmCan.h"
#include "Port.h"
#include "McalLib.h"
#include "Spi.h"
#include "Icu_17_TimerIp.h"
#include "CanTrcv_17_W9255.h"
/******************************************************************************
**                      Imported Compiler Switch Check                       **
******************************************************************************/

/******************************************************************************
**                      Private Macro Definitions                            **
******************************************************************************/
#define CAN_SRC_SET_SRE          (0x00000400U)
#define INVALID_PNFRAMECANID      ((uint8)(0x01))
#define INVALID_PNFRAMEDLC        ((uint8)(0x02))
#define INVALID_PNFRAMEDATA       ((uint8)(0x03))
#define CAN_TXHWOBJECTID_STANDARD    ((uint8)(16))
#define CANTRCV_EXTRACT_BIT0        (1<<0))>>0
#define COM_DELAY_VAL               (100000U)
#define CAN_CTRL_NUM               (2U)
#define CANTRCV_NODE1_TX              (0U)
#define CANTRCV_NODE2_RX              (1U)
#define CANTRCV_ZERO_U              (0U)
#define CANTRCV_ONE_U               (1U)
#define CANTRCV_TWO_U               (2U)
#define CANTRCV_THREE_U             (3U)
#define VALID_FRM_NOM_CANID_NOM_VLDDATA (1U)
#define CANTRCV_TEN_U               (10U)
#define CANTRCV_TWELVE_U              (12U)
#define CANTRCV_WUF_BIT_POS         (16U)
#define CANTRCV_MASK_WAKE_STAT_REG_U     ((uint32) 0x00010000)
#define CAN_KERNEL_0              (1U)
#define CAN_KERNEL_1              (2U)
#define CAN_KERNEL_2              (4U)
#define CAN_CTRL_0              (0U)
#define CAN_CTRL_1              (1U)
#define CAN_CTRL_2              (2U)
#define CAN_CTRL_3              (3U)
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
#if 0	/* Code Snippet for reference shall not be enabled and used */
extern uint8 Can_Init_Status;
#endif
/******************************************************************************
**                      Private Constant Definitions                         **
******************************************************************************/
#if 0	/* Code Snippet for reference shall not be enabled and used */

/* Data Bytes For CAN Frame */
static uint8 u8gTestTrcv_CANTxData[][8] = {
  {0x10, 0x02, 0x30, 0x04, 0x50, 0x06, 0x70, 0x08},
  {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
};

/* Valid CAN Frame PDU Info with Standard Identifier */
static Can_PduType PduType_ValidStandardFrame[2] =
{
  /* Pdu Handle, DLC, CanFrameId(Standard), D0, D1, D2, D3, D4, D5, D6, D7} */
  {21, 8, 0x7FD, u8gTestTrcv_CANTxData[0]},  /* VALID_FRM_NOM_CANID_NOM_VLDDATA */
  {22, 8, 0x400, u8gTestTrcv_CANTxData[0]}  /* VALID_FRM_MIN_CANID_NOM_VLDDATA */
};

/* Invalid CAN Frame PDU Info with Standard Identifier */
static Can_PduType PduType_InValidStandardFrame[3] =
{
  {27, 8, 0,   u8gTestTrcv_CANTxData[0]},      /* Invalid CANID */
  {28, 5, 0x7FD, u8gTestTrcv_CANTxData[1]},    /* Invalid DLC   */
  {29, 8, 0x7FD, u8gTestTrcv_CANTxData[2]}     /* Invalid DATA  */
};

uint8 u8gTestCanTrcv_InitStatus = 0;
#endif
/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
#if 0	/* Code Snippet for reference shall not be enabled and used */

const Can_17_McmCan_ConfigType* TestCan_ConfigPtr = &Can_17_McmCan_Config; 
static void CanTrcv_CheckPNWakeUp(void);
static void CanTrcv_NoCANFrameTx(void);
static void CanTrcv_NoWakeUpOnInvalidFrame(void);
static void Can_EnableServiceRequest(uint8 KrnlHwId, uint8 CtrlHwId);
static void lSend_ValidStandardWakeUpFrame(const uint8 u8gTestTrcv_PNFrameOffset);
static void lSend_InValidStandardWakeUpFrame(const uint8 u8gTestTrcv_PNFrameErrorType);
#endif
/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
/*******************************************************************************
** Syntax : void CanTrcv_17_W9255_Demo (void)                                 **
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
** Description : DemoApp for CAN Transceiver W9255 driver                     **
**                                                                            **
*******************************************************************************/
void CanTrcv_17_W9255_Demo(void)
{
  char szString[80];
  volatile uint8 TempUSage = 0;
   #if 0	/* Enabler Code Transciever externally connected */
  if(!u8gTestCanTrcv_InitStatus)
  {
   uint8 EnCanKrnl = CANTRCV_ZERO_U, EnCanCtrl = CANTRCV_ZERO_U;

   Spi_Init(&Spi_Config);
  
   IrqScu_Init();
   MODULE_SRC.SCU.SCUERU[CANTRCV_ZERO_U].U |= (uint32) (CANTRCV_ONE_U << CANTRCV_TEN_U);
   MODULE_SRC.SCU.SCUERU[CANTRCV_ONE_U].U |= (uint32) (CANTRCV_ONE_U << CANTRCV_TEN_U);
   MODULE_SRC.SCU.SCUERU[CANTRCV_TWO_U].U |= (uint32) (CANTRCV_ONE_U << CANTRCV_TEN_U);
   MODULE_SRC.SCU.SCUERU[CANTRCV_THREE_U].U |= (uint32) (CANTRCV_ONE_U << CANTRCV_TEN_U);
   Icu_17_TimerIp_Init(&Icu_17_TimerIp_Config);
   CanTrcv_17_W9255_Init(NULL_PTR);  
   EnCanKrnl = CAN_KERNEL_0;
   EnCanCtrl = CAN_CTRL_1;   
   u8gTestCanTrcv_InitStatus++;
   Can_EnableServiceRequest(EnCanKrnl, EnCanCtrl); 
  }
  
 
    if(!Can_Init_Status)
  {
    IrqCan_Init();
    Can_17_McmCan_Init(&Can_17_McmCan_Config);    
    Can_Init_Status++;
  }
  #endif

  while (!TempUSage)
  {
    print_f("\n\n\n");
    print_f("\n/***********************************************************************/\n");
    print_f("\n               CAN TRANSCEIVER W9255 DRIVER DEMOAPP MENU                \n ");
    print_f("\n                                                                        \n ");
	#if 0	
	print_f("     1.  Check PN Wake-Up when VALID CAN Frame Received                   \n ");
    print_f("     2.  Check NO CAN Frame Trasmission when Node in SLEEP/STANDBY Mode   \n ");
    print_f("     3.  Check NO PN Wake-Up when INVALID CAN Frame Received              \n ");
    #endif 
    print_f("     x.  Back To Main Menu                                                \n ");
	print_f("\n   CAN Transciever not populated on Triboard,hence Demo App not enabled  \n ");
    print_f("\n                                                                        \n ");
    print_f("\n/***********************************************************************/\n");
    print_f("  Enter Your Option :: ");

    getline(szString, sizeof szString - 1);

    switch (*szString)
    {
	  #if 0	/* Code Snippet for reference shall not be enabled and used */
	  case '1':
      {
        CanTrcv_CheckPNWakeUp();
        break;
      }
      case '2' :
      {
        CanTrcv_NoCANFrameTx();
        break;
      }
      case '3' :
      {
        CanTrcv_NoWakeUpOnInvalidFrame();
        break;
      }
      #endif 

      /* Go Back to Main Menu */
      case 'x':
      case 'X':
        TempUSage = 1U;
        break;

      default :
      {
        print_f("\n Invalid Option Choosen \n ");
        break;
      }
	  
    }
  }
}

#if 0	/* Code Snippet for reference shall not be enabled and used */

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/
/*******************************************************************************
** Syntax : static void CanTrcv_CheckPNWakeUp(void)                           **
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
** Description : Check PN Wake-Up when VALID CAN Frame Received               **
**                                                                            **
*******************************************************************************/
static void CanTrcv_CheckPNWakeUp(void)
{
  /*Local Variables*/
  uint8 u8lTestTrcv_WUFBitStatus = CANTRCV_ZERO_U;
  uint32  u32lTestTrcv_TempVal = CANTRCV_ZERO_U, u32lTestTrcv_TrcvSystemData = CANTRCV_ZERO_U;
  uint32 * const u32lTestTrcv_TrcvSysData = &u32lTestTrcv_TempVal; 
  
  /* Call CanTrcv_17_W9255_SetOpMode() for Node1 and pass opMode = CANTRCV_TRCVMODE_NORMAL */
  CanTrcv_17_W9255_SetOpMode(CANTRCV_NODE1_TX, CANTRCV_TRCVMODE_NORMAL);
  print_f("\n Node1 Mode changed to NORMAL Mode \n");
  /* Call CanTrcv_17_W9255_SetOpMode() for Node2 and pass opMode = CANTRCV_TRCVMODE_STANDBY */
  CanTrcv_17_W9255_SetOpMode(CANTRCV_NODE2_RX, CANTRCV_TRCVMODE_STANDBY);
  print_f("\n Node2 Mode changed to STANDBY Mode \n");
  
  /* Send Valid Standard Wake-Up Frame (WUF) on Node2 from Node1 */
  lSend_ValidStandardWakeUpFrame(VALID_FRM_NOM_CANID_NOM_VLDDATA);

  /* Call CanTrcv_17_W9255_GetTrcvSystemData() API to Read Wake-Up Frame (WUF) flag Bit Status from Node2 */
  CanTrcv_17_W9255_GetTrcvSystemData(CANTRCV_NODE2_RX, u32lTestTrcv_TrcvSysData);
  u32lTestTrcv_TrcvSystemData = (uint32) * u32lTestTrcv_TrcvSysData;
  /* Mask WAKE_STAT register bits to read WUF Bit Status */ 
  u8lTestTrcv_WUFBitStatus = (uint8)((u32lTestTrcv_TrcvSystemData & CANTRCV_MASK_WAKE_STAT_REG_U) >> CANTRCV_WUF_BIT_POS);
  
  if(CANTRCV_ZERO_U  == u8lTestTrcv_WUFBitStatus)
  {  
    print_f("\nWake-Up Frame (WUF) Bit Status = %d\n", u8lTestTrcv_WUFBitStatus);
    print_f("\nWake-Up NOT Successful \n");
    StartResult();
    print_f("Result = Fail;");
    EndResult();
  }
  else
  {
    print_f("\nWake-Up Frame (WUF) Bit Status = %d\n", u8lTestTrcv_WUFBitStatus);
    print_f("\nWake-Up Successful \n");
    StartResult();
    print_f("Result = Pass;");
    EndResult();
  }
  CanTrcv_17_W9255_ClearTrcvWufFlag(CANTRCV_NODE2_RX);
}

/*******************************************************************************
** Syntax : static void CanTrcv_NoCANFrameTx(void)                            **
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
** Description : Check NO CAN Frame Trasmission when Node in SLEEP/STANDBY Mode**
**                                                                            **
*******************************************************************************/
static void CanTrcv_NoCANFrameTx(void)
{
  /*Local Variables*/
  uint8 u8lTestTrcv_WUFBitStatus = CANTRCV_ZERO_U;
  uint32  u32lTestTrcv_TempVal = CANTRCV_ZERO_U, u32lTestTrcv_TrcvSystemData = CANTRCV_ZERO_U;
  uint32 * const u32lTestTrcv_TrcvSysData = &u32lTestTrcv_TempVal;  
  
  /* Call CanTrcv_17_W9255_SetOpMode() for Node1 and pass opMode = CANTRCV_TRCVMODE_STANDBY */
  CanTrcv_17_W9255_SetOpMode(CANTRCV_NODE1_TX, CANTRCV_TRCVMODE_STANDBY);
  print_f("\n Node1 Mode changed to STANDBY mode \n");
  /* Call CanTrcv_17_W9255_SetOpMode() for Node2 and pass opMode = CANTRCV_TRCVMODE_STANDBY */
  CanTrcv_17_W9255_SetOpMode(CANTRCV_NODE2_RX, CANTRCV_TRCVMODE_STANDBY);
  print_f("\n Node2 Mode changed to STANDBY mode \n");
  
  /* Send Valid Standard Wake-Up Frame (WUF) on Node2 from Node1 */
  lSend_ValidStandardWakeUpFrame(VALID_FRM_NOM_CANID_NOM_VLDDATA);

  /* Call CanTrcv_17_W9255_GetTrcvSystemData() API to Read Wake-Up Frame (WUF) flag Bit Status from Node2 */
  CanTrcv_17_W9255_GetTrcvSystemData(CANTRCV_NODE2_RX, u32lTestTrcv_TrcvSysData);
  u32lTestTrcv_TrcvSystemData = (uint32) * u32lTestTrcv_TrcvSysData;
  /* Mask WAKE_STAT register bits to read WUF Bit Status */ 
  u8lTestTrcv_WUFBitStatus = (uint8)((u32lTestTrcv_TrcvSystemData & CANTRCV_MASK_WAKE_STAT_REG_U) >> CANTRCV_WUF_BIT_POS);
  
  if(CANTRCV_ZERO_U == u8lTestTrcv_WUFBitStatus)
  {  
    print_f("\nWake-Up Frame (WUF) Bit Status = %d\n", u8lTestTrcv_WUFBitStatus);
    print_f("\nWake-Up NOT Successful \n");
    StartResult();
    print_f("Result = Pass;");
    EndResult();
  }
  else
  {
    print_f("\nWake-Up Frame (WUF) Bit Status = %d\n", u8lTestTrcv_WUFBitStatus);
    print_f("\nWake-Up Successful \n");
    StartResult();
    print_f("Result = Fail;");
    EndResult();
  }
}


/*******************************************************************************
** Syntax : static void CanTrcv_NoWakeUpOnInvalidFrame(void)                  **
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
** Description : Check NO PN Wake-Up when INVALID CAN Frame Received          **
**                                                                            **
*******************************************************************************/
static void CanTrcv_NoWakeUpOnInvalidFrame(void)
{
  /*Local Variables*/
  uint8 u8lTestTrcv_WUFBitStatus = CANTRCV_ZERO_U;
  uint32  u32lTestTrcv_TempVal = CANTRCV_ZERO_U, u32lTestTrcv_TrcvSystemData = CANTRCV_ZERO_U;
  uint32 * const u32lTestTrcv_TrcvSysData = &u32lTestTrcv_TempVal; 
  
  /* Call CanTrcv_17_W9255_SetOpMode() for Node1 and pass opMode = CANTRCV_TRCVMODE_NORMAL */
  CanTrcv_17_W9255_SetOpMode(CANTRCV_NODE1_TX, CANTRCV_TRCVMODE_NORMAL);
  print_f("\n Node1 Mode changed to NORMAL mode \n");
  /* Call CanTrcv_17_W9255_SetOpMode() for Node2 and pass opMode = CANTRCV_TRCVMODE_STANDBY */
  CanTrcv_17_W9255_SetOpMode(CANTRCV_NODE2_RX, CANTRCV_TRCVMODE_STANDBY);
  print_f("\n Node2 Mode changed to STANDBY mode \n");
  
  /* Send In-Valid Standard Wake-Up Frame (WUF) on Node2 from Node1 */
  lSend_InValidStandardWakeUpFrame(INVALID_PNFRAMEDLC);

  /* Call CanTrcv_17_W9255_GetTrcvSystemData() API to Read Wake-Up Frame (WUF) flag Bit Status from Node2 */
  CanTrcv_17_W9255_GetTrcvSystemData(CANTRCV_NODE2_RX, u32lTestTrcv_TrcvSysData);
  u32lTestTrcv_TrcvSystemData = (uint32) * u32lTestTrcv_TrcvSysData;
  /* Mask WAKE_STAT register bits to read WUF Bit Status */ 
  u8lTestTrcv_WUFBitStatus = (uint8)((u32lTestTrcv_TrcvSystemData & CANTRCV_MASK_WAKE_STAT_REG_U) >> CANTRCV_WUF_BIT_POS);
  
  if(CANTRCV_ZERO_U == u8lTestTrcv_WUFBitStatus)
  {  
    print_f("\nWake-Up Frame (WUF) Bit Status = %d\n", u8lTestTrcv_WUFBitStatus);
  print_f("\nWake-Up NOT Successful \n");
    StartResult();
    print_f("Result = Pass;");
    EndResult();
  }
  else
  {
    print_f("\nWake-Up Frame (WUF) Bit Status = %d\n", u8lTestTrcv_WUFBitStatus);
    print_f("\nWake-Up Successful \n");
    StartResult();
    print_f("Result = Fail;");
    EndResult();
  }
}


/*******************************************************************************
** Syntax/Name     : static void Can_EnableServiceRequest                     **
**                   (uint8 KrnlHwId, uint8 CtrlHwId)                         **
**                                                                            **
**                                                                            **
** Description     : Enable Service Request for a particular Controller       **
*******************************************************************************/
static void Can_EnableServiceRequest(uint8 KrnlHwId, uint8 CtrlHwId)
{
  /* Enter Critical Section */
  SchM_Enter_Can_17_McmCan_CanIntCtrl();

  if((CAN_KERNEL_0 == (KrnlHwId & CAN_KERNEL_0)) && \
      (CAN_CTRL_1 == (CtrlHwId & CAN_CTRL_1)))
  {
    SRC_CAN_CAN0_INT4.U |= CAN_SRC_SET_SRE ;
    SRC_CAN_CAN0_INT5.U |= CAN_SRC_SET_SRE ;
    SRC_CAN_CAN0_INT6.U |= CAN_SRC_SET_SRE ;
    SRC_CAN_CAN0_INT7.U |= CAN_SRC_SET_SRE ;
  }

  /* Exit Critical Section */
  SchM_Exit_Can_17_McmCan_CanIntCtrl();
}


/*******************************************************************************
** Syntax/Name     : void lSend_ValidStandardWakeUpFrame                      **
**                   (const uint8 u8gTestTrcv_PNFrameOffset)                  **
**                                                                            **
**                                                                            **
** Description     : Send Valid Standard Wake-Up Frame                        **
*******************************************************************************/
static void lSend_ValidStandardWakeUpFrame(const uint8 u8gTestTrcv_PNFrameOffset)
{
  volatile uint32 u32lTestTrcv_DelayCounter;
  uint8 u8lTestTrcv_PNFrameOffset = CANTRCV_ZERO_U;

  /* Data transmission by Controller 01 */
  u8lTestTrcv_PNFrameOffset = (u8gTestTrcv_PNFrameOffset - CANTRCV_ONE_U);

  /* Put the CAN controller into started state */
  Can_17_McmCan_SetControllerMode (CAN_CTRL_NUM, CAN_T_START);
  Can_17_McmCan_Write(CAN_TXHWOBJECTID_STANDARD, &PduType_ValidStandardFrame[(u8lTestTrcv_PNFrameOffset)]);
  print_f("Valid CAN Frame Transmitted from CAN Node...\n");
  /* Communication Delay */
  u32lTestTrcv_DelayCounter = COM_DELAY_VAL;
  while(u32lTestTrcv_DelayCounter--);
  /* Put the CAN controllers into stopped state */
  Can_17_McmCan_SetControllerMode (CAN_CTRL_NUM, CAN_T_STOP);
}


/*******************************************************************************
** Syntax/Name     : void lSend_InValidStandardWakeUpFrame                    **
**                   (const uint8 u8gTestTrcv_PNFrameErrorType)               **
**                                                                            **
**                                                                            **
** Description     : Send InValid Standard Wake-Up Frame                      **
*******************************************************************************/
static void lSend_InValidStandardWakeUpFrame(const uint8 u8gTestTrcv_PNFrameErrorType)
{
  volatile uint32 u32lTestTrcv_DelayCounter;

  /* Put the CAN controller into started state */
  Can_17_McmCan_SetControllerMode (CAN_CTRL_NUM, CAN_T_START);

  switch(u8gTestTrcv_PNFrameErrorType)
  {
   case INVALID_PNFRAMECANID:
   Can_17_McmCan_Write(CAN_TXHWOBJECTID_STANDARD, &PduType_InValidStandardFrame[(INVALID_PNFRAMECANID - CANTRCV_ONE_U)]);
   print_f("Invalid CAN Frame (INVALID_PNFRAMECANID) Transmitted from CAN Node...\n");
   break;

   case INVALID_PNFRAMEDLC:
   Can_17_McmCan_Write(CAN_TXHWOBJECTID_STANDARD, &PduType_InValidStandardFrame[(INVALID_PNFRAMEDLC - CANTRCV_ONE_U)]);
   print_f("Invalid CAN Frame (INVALID_PNFRAMEDLC) Transmitted from CAN Node...\n"); 
   break;

   case INVALID_PNFRAMEDATA:
   Can_17_McmCan_Write(CAN_TXHWOBJECTID_STANDARD, &PduType_InValidStandardFrame[(INVALID_PNFRAMEDATA - CANTRCV_ONE_U)]);
   print_f("Invalid CAN Frame (INVALID_PNFRAMEDATA) Transmitted from CAN Node...\n");   
   break;

   default:
   break;
  }
  /* Delay */
  u32lTestTrcv_DelayCounter = COM_DELAY_VAL;
  while(u32lTestTrcv_DelayCounter--);

  /* Put the CAN controllers into stopped state */
  Can_17_McmCan_SetControllerMode (CAN_CTRL_NUM, CAN_T_STOP);
}

#endif
