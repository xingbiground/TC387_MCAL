/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2018)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : SchM_McalLib.h                                             **
**                                                                            **
**  VERSION      : 4.0.0                                                      **
**                                                                            **
**  DATE         : 2019-04-01                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : SchM file for McalLib                                      **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
/*[cover parentID={BCFD78E7-C2EF-4977-BA21-379BDEC4ECFF}][/cover]*/
#ifndef MCAL_LIB_SCHM_H
#define MCAL_LIB_SCHM_H
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/*******************************************************************************
** Traceability     : [cover parentID={22CD1792-494C-4366-AB98-235B438D35DA}] **
** [/cover]                                                                   **
** Syntax           : void SchM_Enter_McalLib_PeripheralEndInit(void)         **
**                                                                            **
** Description      : Enters Module exclusive area                            **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Not Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void SchM_Enter_McalLib_PeripheralEndInit(void);
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : void SchM_Exit_McalLib_PeripheralEndInit(void)          **
**                                                                            **
** Description      : Exit Module exclusive area                              **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Not Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void SchM_Exit_McalLib_PeripheralEndInit(void);
/*******************************************************************************
** Traceability     : [cover parentID={58B33909-7455-49a5-8259-C7144939461B}] **
** [/cover]                                                                   **
**                                                                            **
** Syntax           : void SchM_Enter_McalLib_SafetyEndInit(void)             **
**                                                                            **
** Description      : Enters Module exclusive area                            **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Not Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void SchM_Enter_McalLib_SafetyEndInit(void);
/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax           : void SchM_Exit_McalLib_SafetyEndInit(void)              **
**                                                                            **
** Description      : Exit Module exclusive area                              **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Not Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void SchM_Exit_McalLib_SafetyEndInit(void);
/*******************************************************************************
** Traceability     : [cover parentID={A9747D17-F4E7-46b6-9A62-FD0CEC272F73}] **
**                                                                            **
** Syntax           : void SchM_Enter_McalLib_CpuEndInit(void)                **
**                                                                            **
** Description      : Enters Module exclusive area                            **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Not Reentrant on same CPU, Reentrant on other CPUs      **
**                                                                            **
** Parameters(in)   : None                                                    **
** Parameters (out) : None                                                    **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void SchM_Enter_McalLib_CpuEndInit(void);
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : void SchM_Exit_McalLib_CpuEndInit(void)                 **
**                                                                            **
** Description      : Exit Module exclusive area                              **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Not Reentrant on same CPU, Reentrant on other CPUs      **
**                                                                            **
** Parameters(in)   : None                                                    **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void SchM_Exit_McalLib_CpuEndInit(void);
/*******************************************************************************
** Traceability     :[cover parentID={E2CAE3DF-6EAE-4328-8ECF-C2376A063D1C}]  **
**                                                                            **
** Syntax           : void SchM_Enter_McalLib_StmTimerResolution(void)        **
**                                                                            **
** Description      : Enters Module exclusive area                            **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Not Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void SchM_Enter_McalLib_StmTimerResolution(void);
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : void SchM_Exit_McalLib_StmTimerResolution(void)         **
**                                                                            **
** Description      : Exit Module exclusive area                              **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Not Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
extern void SchM_Exit_McalLib_StmTimerResolution(void);

#endif
