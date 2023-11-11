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
**  FILENAME     : SchM_Uart.h                                                 **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2020-10-15                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY : [cover parentID={EC956978-C139-4eca-A38C-7A6842695287}]    **
**                                                                            **
**  DESCRIPTION  : SchM file for Uart driver                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of RTE, AUTOSAR Release 4.2.2 and 4.4.0  **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
#ifndef UART_SCHM_H
#define UART_SCHM_H

/*******************************************************************************
** Syntax : void Uart_MainFunction_Read(void)                                 **
**                                                                            **
** Service ID      : 224                                                      **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant.                                           **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
** Description     : Schedule function to handle receives operation in        **
**                                                            polling mode.   **
**                                                                            **
*******************************************************************************/
extern void Uart_MainFunction_Read(void);

/*******************************************************************************
** Syntax : void Uart_MainFunction_Write(void)                                **
**                                                                            **
** Service ID      : 225                                                      **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant.                                           **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
** Description     : Schedule function to handle transmits operation in       **
**                                                             polling mode.  **
**                                                                            **
*******************************************************************************/
extern void Uart_MainFunction_Write(void);

#endif /* End of UART_SCHM_H */
