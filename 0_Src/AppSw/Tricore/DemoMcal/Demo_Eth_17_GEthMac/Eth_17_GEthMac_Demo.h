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
**  FILENAME   : Eth_17_GEthMacV2_Demo.h                                     **
**                                                                           **
**  VERSION    : 1.0.0                                                       **
**                                                                           **
**  DATE       : 2020-09-16                                                  **
**                                                                           **
**  VARIANT    : NA                                                          **
**                                                                           **
**  PLATFORM   : Infineon AURIX2G                                            **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION : This file exports                                          **
**                - ETH application for ETH driver                           **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                     **
**                                                                           **
******************************************************************************/
#include "McalLib.h"
#if(MCAL_AR_VERSION == MCAL_AR_440)
#ifndef     ETH_17_GETHMACV2_DEMO_H
#define     ETH_17_GETHMACV2_DEMO_H

/******************************************************************************
**                      Includes                                             **
******************************************************************************/
typedef enum ETH_PHY_STATUS
{
  ETH_PHY_STATUS_OK = 0,             /**< OK. All is fine! */
  ETH_PHY_STATUS_BUSY = -1,          /**< Busy */
  ETH_PHY_STATUS_ERROR = -2,         /**< Error */
  ETH_PHY_STATUS_ERROR_ID = -3,      /**< Error in device identifier */
  ETH_PHY_STATUS_ERROR_TIMEOUT = -4, /**< Time-out error */  
  ETH_PHY_STATUS_ERROR_IF = -5,       /**< Interface mode not supported */
  ETH_PHY_STATUS_ERROR_PHYANEG = -6,
  ETH_PHY_STATUS_ERROR_SPEED = -7,
  ETH_PHY_STATUS_ERROR_PHYREMRX = -8
} ETH_PHY_STATUS_t;

typedef enum ETH_PHY_LINK_STATUS
{
  ETH_PHY_LINK_STATUS_DOWN,
  ETH_PHY_LINK_STATUS_UP,
  ETH_PHY_LINK_STATUS_UNKNOWN,
} ETH_PHY_LINK_STATUS_t;

/******************************************************************************
**                      Global Functions                                     **
******************************************************************************/

#define ETH_17_GETHMACV2_START_SEC_CODE_QM_GLOBAL
#include "Eth_17_GEthMacV2_MemMap.h"

/******************************************************************************
** Syntax : void Eth_17_Demo(void)                                           **
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
** Description : Ethernet driver demo                                        **
**                                                                           **
******************************************************************************/
extern void EthV2_17_Demo(void);


#define ETH_17_GETHMACV2_STOP_SEC_CODE_QM_GLOBAL
#include "Eth_17_GEthMacV2_MemMap.h"

#endif /* ETH_17_ETHMACV2_DEMO_H */
#endif

#if(MCAL_AR_VERSION == MCAL_AR_422)
#ifndef     ETH_17_GETHMAC_DEMO_H
#define     ETH_17_GETHMAC_DEMO_H

/******************************************************************************
**                      Includes                                             **
******************************************************************************/
typedef enum ETH_PHY_STATUS
{
  ETH_PHY_STATUS_OK = 0,             /**< OK. All is fine! */
  ETH_PHY_STATUS_BUSY = -1,          /**< Busy */
  ETH_PHY_STATUS_ERROR = -2,         /**< Error */
  ETH_PHY_STATUS_ERROR_ID = -3,      /**< Error in device identifier */
  ETH_PHY_STATUS_ERROR_TIMEOUT = -4, /**< Time-out error */  
  ETH_PHY_STATUS_ERROR_IF = -5,       /**< Interface mode not supported */
  ETH_PHY_STATUS_ERROR_PHYANEG = -6,
  ETH_PHY_STATUS_ERROR_SPEED = -7,
  ETH_PHY_STATUS_ERROR_PHYREMRX = -8
} ETH_PHY_STATUS_t;

typedef enum ETH_PHY_LINK_STATUS
{
  ETH_PHY_LINK_STATUS_DOWN,
  ETH_PHY_LINK_STATUS_UP,
  ETH_PHY_LINK_STATUS_UNKNOWN,
} ETH_PHY_LINK_STATUS_t;

/******************************************************************************
**                      Global Functions                                     **
******************************************************************************/
#define ETH_17_GETHMAC_START_SEC_CODE_QM_GLOBAL
#include "Eth_17_GEthMac_MemMap.h"
/******************************************************************************
** Syntax : void Eth_17_Demo(void)                                           **
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
** Description : Ethernet driver demo                                        **
**                                                                           **
******************************************************************************/
extern void Eth_17_Demo(void);


#define ETH_17_GETHMAC_STOP_SEC_CODE_QM_GLOBAL
#include "Eth_17_GEthMac_MemMap.h"


#endif /* ETH_17_ETHMAC_DEMO_H */
#endif
