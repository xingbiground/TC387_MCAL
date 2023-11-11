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
**  FILENAME   : EthTrcv_Cbk.c                                            **
**                                                                           **
**  CC VERSION :  2.0.0                                                         **
**                                                                           **
**  $DATE       : 2021-11-08                                              **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION : This file contains                                         **
**                Implementation of ETH interface callback functions         **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                     **
**                                                                           **
******************************************************************************/

#include "EthTrcv_Cbk.h"
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
#include "Test_EthTrcv_Cbk.h"
#endif /*#if (APP_SW == TEST_APP)*/
#endif

void EthTrcv_WriteMiiIndication( uint8 CtrlIdx, uint8 TrcvIdx, uint8 RegIdx )
{
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  Test_EthTrcv_WriteMiiIndication(CtrlIdx,TrcvIdx,RegIdx);
  #endif /*#if (APP_SW == TEST_APP)*/
  #endif
}

void EthTrcv_ReadMiiIndication( uint8 CtrlIdx, uint8 TrcvIdx, uint8 RegIdx, uint8 RegVal )
{
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  Test_EthTrcv_ReadMiiIndication(CtrlIdx,TrcvIdx,RegIdx,RegVal);
  #endif /*#if (APP_SW == TEST_APP)*/
  #endif
}
