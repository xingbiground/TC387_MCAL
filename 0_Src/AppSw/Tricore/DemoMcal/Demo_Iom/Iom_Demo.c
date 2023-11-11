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
**  FILENAME   : Iom_Demo.c                                                  **
**                                                                           **
**  VERSION    : 1.0.0                                                       **
**                                                                           **
**  DATE       : 2020-01-21                                                  **
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
**                - Demo application for IOM driver                          **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                     **
**                                                                           **
******************************************************************************/

/******************************************************************************
**                      Includes                                             **
******************************************************************************/
#include "Std_Types.h"
#include "IfxSrc_reg.h"
#include "Iom.h"
#include "Port.h"
#include "IfxPort_reg.h"
#include "Test_Print.h"
#include "DemoApp_Cfg.h"


/******************************************************************************
**                      Imported Compiler Switch Check                       **
******************************************************************************/
/******************************************************************************
**                      Private Macro Definitions                            **
******************************************************************************/
/******************************************************************************
**                      Private Type Definitions                             **
******************************************************************************/
/******************************************************************************
**                      Private Function Declarations                        **
******************************************************************************/
void Iom_Demo(void);

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

/******************************************************************************
**                      Global Function Definitions                          **
******************************************************************************/

/******************************************************************************
** Syntax : void Iom_Demo(void)                                              **
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
** Description : Demo Application for IOM :Verify that the 
    Iom_GetFpcEdgeStatus() API shall provide service to clear the FPC cell edge 
   status based on provided FPC cell number and edge type.                   **
******************************************************************************/
void Iom_Demo(void)
{

  /*Local Variables Inputs and Outputs */  
  uint8 Var_FpcNo = (uint8)0;
  uint8 Var_Edge  = (uint8)1;
  uint8 FPC_Edge_Status;
  uint8 FPC_Edge_Status_1;
  
  
  print_f("\n *******************************************************\n");
  print_f("\n Demo to check service to clear the FPC cell edgeond threshold\n");
  print_f("\n *******************************************************\n");
  
 
  /* configure P33.3 as output pin  */
  P33_IOCR0.B.PC3 = 0x10;   
  /* configure P33.0 as input pin  */
  P33_IOCR0.B.PC0 = 0x00;

  /*Body of Test Case*/
  Iom_Init(&Iom_Config);
  
  /*Simulating a glitch  */
  P33_OUT.B.P3=1;
  P33_OUT.B.P3=0;
  P33_OUT.B.P3=1;


  FPC_Edge_Status = Iom_GetFpcEdgeStatus(Var_FpcNo,Var_Edge);
  
  Iom_ClrFpcEdgeStatus(Var_FpcNo,Var_Edge);
  
  FPC_Edge_Status_1 = Iom_GetFpcEdgeStatus(Var_FpcNo,Var_Edge);
  
  Iom_DeInit();
  
  if ((FPC_Edge_Status ==1) && (FPC_Edge_Status_1 == 0))
  {
     StartResult();
     print_f("Result = Pass;");
     EndResult();
  }
  
  else 
  {
     StartResult();
     print_f("Result = Fail;");
     EndResult();
  }
  

}

