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
**  FILENAME   : EthIf_Cbk.c                                                 **
**                                                                           **
**  VERSION    : 4.0.0                                                       **
**                                                                           **
**  DATE       : 2021-11-09                                                  **
**                                                                           **
**  VARIANT    : NA                                                          **
**                                                                           **
**  PLATFORM   : Infineon AURIX2G                                            **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION : Implementation of ETH Interface callback functions         **
**                  This file is for Evaluation Purpose Only                 **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                     **
**                                                                           **
******************************************************************************/

/******************************************************************************
**                      Includes                                             **
******************************************************************************/
#include "EthIf_Cbk.h"
#ifdef  APP_SW
#if(APP_SW == TEST_APP)
#include "Test_EthIf_Cbk.h"
#endif
#endif

volatile uint16 Test_EthTxConfirmCount[ETH_17_GETHMAC_MAX_CONTROLLERS];
volatile uint16 Eth_RxFrame_Length[ETH_17_GETHMAC_MAX_CONTROLLERS];
volatile uint16 Test_EthRxConfirmCount[ETH_17_GETHMAC_MAX_CONTROLLERS];

#ifdef  APP_SW
#if (APP_SW == DEMO_APP)
extern uint32 Src_IPaddress;
extern uint8 ArpReply;
extern uint8 PromiscuousCheck;
extern uint8 Ret_MacAddr[ETH_MAC_ADD_LEN];
#endif
#endif

void EthIf_RxIndication( uint8 CtrlIdx, Eth_FrameType FrameType, boolean IsBroadcast, const uint8* PhysAddrPtr, Eth_DataType* DataPtr, uint16 LenByte )
{
  #ifdef  APP_SW
  #if (APP_SW == DEMO_APP)
  uint16 i;
  uint32 lSrcipadd = 0;
  uint8 Eth_DestSrcAddrMismatch = 1;

  if ( FrameType == 0xABCD)
  {
    print_f("\n Received Raw Frame from PC");
  }
  else if( FrameType == 0x0806)
  {
    for (i = 0; i < 4; i++)
    {
      lSrcipadd <<= 8;
      lSrcipadd |= (*(DataPtr + 14 + i));
    }
    if(lSrcipadd == Src_IPaddress )
    {
      ArpReply = 1;
      print_f("\n Given IP address is at Mac Address - %x :%x :%x :%x :%x :%x ", (*(PhysAddrPtr + 0)), (*(PhysAddrPtr + 1)), (*(PhysAddrPtr + 2)), (*(PhysAddrPtr + 3)), (*(PhysAddrPtr + 4)), (*(PhysAddrPtr + 5)));
    }
  }
  else
  {
    for (i = 0; i < ETH_MAC_ADD_LEN; i++)
    {
      if(Ret_MacAddr[i] != *(DataPtr - ETH_FRAMEHEADER_LEN + i))
      {
        Eth_DestSrcAddrMismatch++;
      }
    }

    if((Eth_DestSrcAddrMismatch) && (0 == IsBroadcast))
    {
      PromiscuousCheck = 1;
    }

    print_f("\n\n Received Protocol is: 0x%x ", (FrameType));
    print_f("\n Received Payload Size is: %d \n ", (LenByte -  ETH_CRC_FIELD_LENGTH ));
  }
  Test_EthRxConfirmCount[CtrlIdx]++ ;

  #elif(APP_SW == TEST_APP)
    Test_EthIf_RxIndication(CtrlIdx,FrameType,IsBroadcast,PhysAddrPtr,DataPtr,LenByte);
  #endif
  #endif
}

void EthIf_TxConfirmation( uint8 CtrlIdx, Eth_BufIdxType BufIdx )
{
  #ifdef  APP_SW
  #if(APP_SW == TEST_APP)
  Test_EthIf_TxConfirmation(CtrlIdx, BufIdx);
  #endif
  #endif
  Test_EthTxConfirmCount[CtrlIdx]++ ;
}

void EthIf_CtrlModeIndication( uint8 CtrlIdx, Eth_ModeType CtrlMode )
{
  #ifdef  APP_SW
  #if(APP_SW == TEST_APP)
  Test_EthIf_CtrlModeIndication(CtrlIdx);
  #endif
  #endif
}

