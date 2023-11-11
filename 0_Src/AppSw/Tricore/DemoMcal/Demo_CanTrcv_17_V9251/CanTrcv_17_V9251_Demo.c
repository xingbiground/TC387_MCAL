/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2018)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME   : CanTrcv_17_V9251_Demo.c                                     **
**                                                                           **
**  VERSION    : 0.0.1                                                       **
**                                                                           **
**  DATE       : 2019-03-28                                                  **
**                                                                           **
**  VARIANT    : Variant PreCompile                                          **
**                                                                           **
**  PLATFORM   : Infineon AURIX2G                                            **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION : This file contains                                         **
**                - Demo application for CanTrcv V9251 driver                **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                     **
**                                                                           **
******************************************************************************/

/******************************************************************************
**                      Includes                                             **
******************************************************************************/
#include "Std_Types.h"

#include "IfxScu_reg.h"
#include "IfxSrc_reg.h"
#include "IfxStm_reg.h"

#include "Det.h"

#include "Port.h"
#include "Dio.h"
#include "CanIf_Cbk.h"
#include "Irq.h"

#include "McalLib.h"
#if(MCAL_AR_VERSION == MCAL_AR_422)
#include "EcuM_Cbk.h"
#else
#include "EcuM.h"
#include "EcuM_Externals.h"
#endif
#include "Can_GeneralTypes.h"
#include "CanTrcv_17_V9251.h"

#include "Test_Print.h"

#include "Icu_17_TimerIp.h"

#include "Can_17_McmCan.h"
#include "SchM_Can_17_McmCan.h"

#include "CanTrcv_17_V9251_Demo.h"

/******************************************************************************
**                      Imported Compiler Switch Check                       **
******************************************************************************/
/******************************************************************************
**                      Private Macro Definitions                            **
******************************************************************************/
#define     CANTRCV_TOTAL_CHANNELS                  (3U)
#define     CANTRCV_ZERO                            (0U)
#define     CANTRCV_ONE                             (1U)

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/
/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/

uint8 u8gTestCanTrcv9251_OpModeArrayTrcvIf[CANTRCV_17_V9251_CHANNELS_CFG];
uint8 u8gTestCanTrcv9251_Transceiver_Id[CANTRCV_17_V9251_CHANNELS_CFG];
uint8 Can_Init_Status_1 = 0;

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
** Syntax : void CanTrcv_17_V9251_Demo(void)                                  **
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
** Description : DemoApp for CanTrcv V9251  Driver                            **
**                                                                            **
*******************************************************************************/
void CanTrcv_17_V9251_Demo(void)
{
  char szString[4U];
  uint8 TempUSage = 0U;

  /* Local Variables */
  Std_ReturnType u8lCanTrcv9251_SetOpModeRetArray[CANTRCV_TOTAL_CHANNELS] = {E_NOT_OK, E_NOT_OK, E_NOT_OK};
  Std_ReturnType u8lCanTrcv9251_GetOpModeRetArray[CANTRCV_TOTAL_CHANNELS] = {E_NOT_OK, E_NOT_OK, E_NOT_OK};
  
  CanTrcv_TrcvModeType OpModeVal = CANTRCV_TRCVMODE_NORMAL;   
  CanTrcv_TrcvModeType u8lCanTrcv9251_OpModeArray[CANTRCV_TOTAL_CHANNELS];


  while (TempUSage != 1U)
  {
    print_f("\n\n\n");
    print_f("\n/***************************************************************************************");
    print_f("*********************/\n");
    print_f("\n                     CANTRCV 9251 DRIVER DEMOAPP MENU                                 \n");
    print_f("       ENTER YOUR OPTION:                                                               \n");
    print_f("       < 1 >  Set the OpModes of CanTrcv Channels 0 & 1 to NORMAL and to send and receive ");
	print_f("the CAN Frames on the BUS                                                               \n");
    print_f("       < 2 >  Get the OpModes of CanTrcv Channels 0 & 1                                 \n");
    print_f("       < x >  Back To Main Menu                                                         \n");
    print_f("\n/***************************************************************************************");
    print_f("*********************/\n");
    print_f("Enter Your Option: ");

    /* Initialize all the configured channels */
    
  if(!Can_Init_Status_1)
  {
    CanTrcv_17_V9251_Init(NULL);
    IrqCan_Init();
    Can_17_McmCan_Init(&Can_17_McmCan_Config);
    Can_EnableServiceRequest(2);
    Can_Init_Status_1++;
  }

    getline(szString, sizeof szString - 1);

    switch (*szString)
    {
        case '1': /* Set Opmode */
          u8lCanTrcv9251_SetOpModeRetArray[0] = CanTrcv_17_V9251_SetOpMode(((uint8)CANTRCV_ZERO), CANTRCV_TRCVMODE_NORMAL);
          u8lCanTrcv9251_SetOpModeRetArray[1] = CanTrcv_17_V9251_SetOpMode(((uint8)CANTRCV_ONE), CANTRCV_TRCVMODE_NORMAL);
  
         
  
          if((u8lCanTrcv9251_SetOpModeRetArray[0] == E_OK) &&(u8lCanTrcv9251_SetOpModeRetArray[1] == E_OK))
          {
			Can_StandardFrameTx();
            print_f("\n Opmodes are set to NORMAL respectively CanTrcv channels 0 & 1 is Successful.. \n ");
            StartResult();
            print_f("\n Result = Pass \n");
            EndResult();
          }
          else
          {
            StartResult();
            print_f("\n Result = Fail \n");
            EndResult();
          }
          break;
        
        case '2': /* Get Opmode */

         
            u8lCanTrcv9251_GetOpModeRetArray[0] = CanTrcv_17_V9251_GetOpMode(((uint8)CANTRCV_ZERO), &OpModeVal);
            u8lCanTrcv9251_OpModeArray[0] = OpModeVal;

            u8lCanTrcv9251_GetOpModeRetArray[1] = CanTrcv_17_V9251_GetOpMode(((uint8)CANTRCV_ONE), &OpModeVal);
            u8lCanTrcv9251_OpModeArray[1] = OpModeVal;
          
  
          if((u8lCanTrcv9251_OpModeArray[0] == CANTRCV_TRCVMODE_NORMAL) && (u8lCanTrcv9251_GetOpModeRetArray[0] == E_OK) && (u8lCanTrcv9251_OpModeArray[1] == CANTRCV_TRCVMODE_NORMAL) && (u8lCanTrcv9251_GetOpModeRetArray[1] == E_OK))
          {
            print_f("\n Cuurent Opmodes of CanTrcv channels 0 & 1 are NORMAL : Verification Successful.. \n ");
            StartResult();
            print_f("\n Result = Pass \n");
            EndResult();
          }
          else
          {
            StartResult();
            print_f("\n Result = Fail \n");
            EndResult();
          }
          break;
        
   
        case 'x':
        case 'X':
          TempUSage = 1U;
          break;
        
        default :
        {
          print_f("\n Invalid Option...Please Try again.. \n ");
          break;
        }
    }
  }
} /* End of CanTrcv_17_V9251_Demo() */



/*******************************************************************************
** Syntax/Name : CanIf_TestTrcvModeIndication()                               **
** Description :                                                              **
*******************************************************************************/
void CanIf_TestTrcvModeIndication(uint8 Transceiver, \
                                  CanTrcv_TrcvModeType TransceiverMode)
{
    /* Both Transcv mode and TRcv are limited uint8 value, so type cast is ok */
    u8gTestCanTrcv9251_OpModeArrayTrcvIf[Transceiver] = ((uint8)TransceiverMode); 
    u8gTestCanTrcv9251_Transceiver_Id[Transceiver] = ((uint8)Transceiver);
}
