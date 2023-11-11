/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2020)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : SchM_Eth_17_GEthMacV2.h                                    **
**                                                                            **
**  VERSION      : 2.0.0                                                      **
**                                                                            **
**  DATE         : 2020-08-27                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : SchM file for Eth driver                                   **
**                                                                            **
**  SPECIFICATION(S) : Specification of RTE, AUTOSAR Release 4.4.0            **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/

/*[cover parentID={B6F729CB-AFDC-4fc8-976A-030644A61E83}]
SchM_Eth_17_GEthMacV2_h [/cover]*/
#ifndef ETH_17_GETHMACV2_SCHM_H
#define ETH_17_GETHMACV2_SCHM_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/

/*******************************************************************************
** Traceability: [cover parentID]                                             **
** Syntax           : void SchM_Enter_Eth_17_GEthMacV2_TxDescData             **
** [/cover]                                                                   **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Enters Module exclusive area                            **
**                                                                            **
*******************************************************************************/
extern void SchM_Enter_Eth_17_GEthMacV2_TxDescData(void);

/*******************************************************************************
** Traceability: [cover parentID]                                             **
** Syntax           : void SchM_Exit_Eth_17_GEthMacV2_TxDescData              **
** [/cover]                                                                   **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Exits Module exclusive area                             **
**                                                                            **
*******************************************************************************/
extern void SchM_Exit_Eth_17_GEthMacV2_TxDescData(void);

/*******************************************************************************
** Traceability: [cover parentID]                                             **
** Syntax           : void SchM_Enter_Eth_17_GEthMacV2_TxBufIdx               **
** [/cover]                                                                   **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Enters Module exclusive area                            **
**                                                                            **
*******************************************************************************/
extern void SchM_Enter_Eth_17_GEthMacV2_TxBufIdx(void);

/*******************************************************************************
** Traceability: [cover parentID]                                             **
** Syntax           : void SchM_Exit_Eth_17_GEthMacV2_TxBufIdx                **
** [/cover]                                                                   **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Exits Module exclusive area                             **
**                                                                            **
*******************************************************************************/
extern void SchM_Exit_Eth_17_GEthMacV2_TxBufIdx(void);

/*******************************************************************************
** Traceability: [cover parentID]                                             **
** Syntax           : void SchM_Enter_Eth_17_GEthMacV2_TxDescDataISR          **
** [/cover]                                                                   **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Enters Module exclusive area.                           **
**                    This critical section is necessary only in case         **
**                    Ethernet transmit interrupt type is CAT2.               **
**                                                                            **
*******************************************************************************/
extern void SchM_Enter_Eth_17_GEthMacV2_TxDescDataISR(void);

/*******************************************************************************
** Traceability: [cover parentID]                                             **
** Syntax           : void SchM_Exit_Eth_17_GEthMacV2_TxDescDataISR           **
** [/cover]                                                                   **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Exits Module exclusive area                             **
**                    This critical section is necessary only in case         **
**                    Ethernet transmit interrupt type is CAT2.               **
**                                                                            **
*******************************************************************************/
extern void SchM_Exit_Eth_17_GEthMacV2_TxDescDataISR(void);

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax           : void Eth_17_GEthMacV2_MainFunction (void)               **
**                                                                            **
** Description      : The function checks for controller errors  and          **
**                    lost frames.                                            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x1c                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void Eth_17_GEthMacV2_MainFunction(void);

#endif /* ETH_17_GETHMACV2_SCHM_H */
