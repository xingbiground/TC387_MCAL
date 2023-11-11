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
**  FILENAME     : SchM_Icu_17_TimerIp.h                                      **
**                                                                            **
**  VERSION      : 4.0.0                                                      **
**                                                                            **
**  DATE         : 2018-08-08                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY : [cover parentID= {1300DA60-D908-45a6-A899-6339BE0101C5} ]  **
**                                                                            **
**  DESCRIPTION  : SchM file for Icu driver                                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of RTE, AUTOSAR Release 4.2.2            **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
#ifndef ICU_17_TIMERIP_SCHM_H
#define ICU_17_TIMERIP_SCHM_H

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
** Traceability: [cover parentID={DE5ADE20-82DC-43ac-9E00-F2D266B5F1D0}]      **
** Syntax           : void SchM_Enter_Icu_17_TimerIp_ResetEdgeCount(void)     **
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
extern void SchM_Enter_Icu_17_TimerIp_ResetEdgeCount(void);

/*******************************************************************************
** Traceability: [cover parentID={DE5ADE20-82DC-43ac-9E00-F2D266B5F1D0}]      **
** Syntax           : void SchM_Exit_Icu_17_TimerIp_ResetEdgeCount(void)      **
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
extern void SchM_Exit_Icu_17_TimerIp_ResetEdgeCount(void);

/*******************************************************************************
** Traceability: [cover parentID={FBE391B2-0DA7-4152-BC44-943FC4B4B56F}]      **
** Syntax           : void SchM_Enter_Icu_17_TimerIp_SetActivationCondition(  **
**                                                                 void)      **
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
extern void SchM_Enter_Icu_17_TimerIp_SetActivationCondition(void);

/*******************************************************************************
** Traceability: [cover parentID={FBE391B2-0DA7-4152-BC44-943FC4B4B56F}]      **
** Syntax           : void SchM_Exit_Icu_17_TimerIp_SetActivationCondition(   **
**                                                   void)                    **
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
extern void SchM_Exit_Icu_17_TimerIp_SetActivationCondition(void);

/*******************************************************************************
** Traceability: [cover parentID={253EA602-550A-4df4-8993-AE8373F79989}]      **
** Syntax           : void SchM_Enter_Icu_17_TimerIp_GtmEnableEdgeCount(void) **
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
extern void SchM_Enter_Icu_17_TimerIp_GtmEnableEdgeCount(void);

/*******************************************************************************
** Traceability: [cover parentID={253EA602-550A-4df4-8993-AE8373F79989}]      **
** Syntax           : void SchM_Exit_Icu_17_TimerIp_GtmEnableEdgeCount(void)  **
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
extern void SchM_Exit_Icu_17_TimerIp_GtmEnableEdgeCount(void);

/*******************************************************************************
** Traceability: [cover parentID={945653E4-2B39-42d1-A365-BF27A9A5AA12}]      **
** Syntax           : void SchM_Enter_Icu_17_TimerIp_GtmGetDutyCycle(void)    **
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
extern void SchM_Enter_Icu_17_TimerIp_GtmGetDutyCycle(void);

/*******************************************************************************
** Traceability: [cover parentID={945653E4-2B39-42d1-A365-BF27A9A5AA12}]      **
** Syntax           : void SchM_Exit_Icu_17_TimerIp_GtmGetDutyCycle(void)     **
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
extern void SchM_Exit_Icu_17_TimerIp_GtmGetDutyCycle(void);
#endif /* End of ICU_17_TIMERIP_SCHM_H */
