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
**  FILENAME   : EthIf_Cbk.h                                                 **
**                                                                           **
**  VERSION    : 4.0.0                                                       **
**                                                                           **
**  DATE       : 2021-11-08                                                  **
**                                                                           **
**  VARIANT    : NA                                                          **
**                                                                           **
**  PLATFORM   : Infineon AURIX2G                                            **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION  : This file exports ETH Interface functions.                **
**                  This file is for Evaluation Purpose Only                 **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: yes                                     **
**                                                                           **
******************************************************************************/

#ifndef ETHIF_CBK_H
#define ETHIF_CBK_H

#include "Std_Types.h"

#include "Eth_17_GEthMac.h"

#ifdef  APP_SW
#if (APP_SW == DEMO_APP)
#include "DemoApp_Cfg.h"
#include "Test_Print.h"

#endif
#endif

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

#define ETH_CRC_FIELD_LENGTH             (4U)
#define ETH_MAC_ADD_LEN                  (6U)
#define ETH_FRAMEHEADER_LEN              (14U)

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
extern volatile uint16 Test_EthTxConfirmCount[ETH_17_GETHMAC_MAX_CONTROLLERS];
extern volatile uint16 Test_EthRxConfirmCount[ETH_17_GETHMAC_MAX_CONTROLLERS];

extern void EthIf_RxIndication( uint8 CtrlIdx, Eth_FrameType FrameType, boolean IsBroadcast, const uint8* PhysAddrPtr, Eth_DataType* DataPtr, uint16 LenByte );
extern void EthIf_CtrlModeIndication( uint8 CtrlIdx, Eth_ModeType CtrlMode );
extern void EthIf_TxConfirmation( uint8 CtrlIdx, Eth_BufIdxType BufIdx );

#endif /* end of ETHIF_CBK_H */
