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
**  FILENAME     : SchM_Eth_17_GEthMac.h                                      **
**                                                                            **
**  VERSION      : 4.0.0                                                      **
**                                                                            **
**  DATE         : 2020-10-20                                                 **
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
**  SPECIFICATION(S) : Specification of RTE, AUTOSAR Release 4.2.2            **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/

#ifndef ETH_17_GETHMAC_SCHM_H
#define ETH_17_GETHMAC_SCHM_H

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
** Traceability: [cover parentID={9124EAE6-F9C0-4f86-AC52-39802626B391}]      **
** Syntax           : void SchM_Enter_Eth_17_GEthMac_TransmitData             **
** [/cover]                                                                   **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   :                                                         **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : Enters Module exclusive area                            **
**                                                                            **
*******************************************************************************/
extern void SchM_Enter_Eth_17_GEthMac_TransmitData(void);

/*******************************************************************************
** Traceability: [cover parentID={9124EAE6-F9C0-4f86-AC52-39802626B391}]      **
** Syntax           : void SchM_Exit_Eth_17_GEthMac_TransmitData              **
** [/cover]                                                                   **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : Exits Module exclusive area                             **
**                                                                            **
*******************************************************************************/
extern void SchM_Exit_Eth_17_GEthMac_TransmitData(void);

/*******************************************************************************
** Traceability: [cover parentID={A937E9AB-AE1F-4ca6-87EF-C1F2E474C0AC}]      **
** Syntax           : void SchM_Enter_Eth_17_GEthMac_UpdateGlobalTime         **
** [/cover]                                                                   **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   :                                                         **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : Enters Module exclusive area                            **
**                                                                            **
*******************************************************************************/
extern void SchM_Enter_Eth_17_GEthMac_UpdateGlobalTime(void);
/*******************************************************************************
** Traceability: [cover parentID={A937E9AB-AE1F-4ca6-87EF-C1F2E474C0AC}]      **
** Syntax           : void SchM_Exit_Eth_17_GEthMac_UpdateGlobalTime          **
** [/cover]                                                                   **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : Exits Module exclusive area                             **
**                                                                            **
*******************************************************************************/
extern void SchM_Exit_Eth_17_GEthMac_UpdateGlobalTime(void);

/*******************************************************************************
**                                                                            **
** Traceability    : [cover parentID]                                         **
**                                                                            **
** Syntax           : void Eth_17_GEthMac_MainFunction (void)                 **
**                                                                            **
** Description      : The function checks for controller errors  and          **
**                    lost frames.                                            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x20                                                    **
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
extern void Eth_17_GEthMac_MainFunction(void);

#endif /* ETH_17_GETHMAC_SCHM_H */
