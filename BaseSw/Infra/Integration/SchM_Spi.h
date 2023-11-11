/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2021)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : SchM_Spi.h                                                 **
**                                                                            **
**  VERSION      : 4.0.0                                                      **
**                                                                            **
**  DATE         : 2021-03-08                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : SchM file for Spi driver                                   **
**                                                                            **
**  SPECIFICATION(S) : Specification of RTE, AUTOSAR Release                  **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
#ifndef SPI_SCHM_H
#define SPI_SCHM_H

/*******************************************************************************
** Traceability: [cover parentID={2382A5CE-AD34-4327-8FC5-5B06429341C0}]      **
**                                                                            **
** Syntax           : void SchM_Enter_Spi_Queue_Update(void)                  **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : Enters Module exclusive area                            **
**                                                                            **
*******************************************************************************/
extern void SchM_Enter_Spi_Queue_Update(void);

/*******************************************************************************
** Traceability: [cover parentID={2382A5CE-AD34-4327-8FC5-5B06429341C0}]      **
**                                                                            **
** Syntax           : void SchM_Exit_Spi_Queue_Update(void)                   **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : Exits Module exclusive area                             **
**                                                                            **
*******************************************************************************/
extern void SchM_Exit_Spi_Queue_Update(void);

/*******************************************************************************
** Traceability: [cover parentID={8A100D12-7FA7-419e-A536-40E49470C9D1}]      **
**                                                                            **
** Syntax           : void SchM_Enter_Spi_SyncLock(void)                      **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : Enters Module exclusive area                            **
**                                                                            **
*******************************************************************************/
extern void SchM_Enter_Spi_SyncLock(void);

/*******************************************************************************
** Traceability: [cover parentID={8A100D12-7FA7-419e-A536-40E49470C9D1}]      **
**                                                                            **
** Syntax           : void SchM_Exit_Spi_SyncLock(void)                       **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non - Reentrant                                         **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : Exits Module exclusive area                             **
**                                                                            **
*******************************************************************************/
extern void SchM_Exit_Spi_SyncLock(void);

/*******************************************************************************
** Traceability: [cover parentID={4AB3EF79-BAC0-4355-B85C-7A0D30152F39}]      **
**                                                                            **
** Syntax           : void  Spi_MainFunction_Handling                         **
**                    (                                                       **
**                      void                                                  **
**                    )                                                       **
**                                                                            **
** Service ID       : 0x10                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in)  : none                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Timing           : Fixed Cyclic                                            **
**                    The user has to determine the cycle rate depending upon **
**                    the baud rate of the transmission and frequency of the  **
**                    job scheduling required.                                **
**                                                                            **
** Description      : This function replaces the interrupt mechanism used     **
** to handle jobs on the bus. The function polls for the completion of a      **
** channel transmission (a DMA Tansaction) and calls the                      **
** function:SpilBusHandler. In addition this function also checks for errors  **
** (production) on the SPI bus and performs the needed error handling         **
** (calls                                                                     **
** Spi_lErrorHandler)                                                         **
*******************************************************************************/
extern void Spi_MainFunction_Handling(void);

#endif /* SPI_SCHM_H */
