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
**  FILENAME     : SchM_Fr_17_Eray.h                                          **
**                                                                            **
**  VERSION      : 3.0.0                                                      **
**                                                                            **
**  DATE         : 2020-06-30                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : SchM file for Fr driver                                    **
**                                                                            **
**  SPECIFICATION(S) : Specification of RTE, AUTOSAR Release 4.2.2            **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
#ifndef FR_17_ERAY_SCHM_H
#define FR_17_ERAY_SCHM_H

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
** Traceability    : [cover parentID={261640D2-77D0-45ba-A607-C550B333E62E}]  **
**                                                                            **
** Syntax           : SchM_Enter_Fr_17_Eray_ConfigLockKey                     **
**                                                                            **
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
** Description      : Enters Module exclusive area for Lock sequence to leave **
**                    "CONFIG" state by writing to SUCC1.CMD commands READY   **
*******************************************************************************/
extern void SchM_Enter_Fr_17_Eray_ConfigLockKey(void);

/*******************************************************************************
** Traceability    : [cover parentID={261640D2-77D0-45ba-A607-C550B333E62E}]  **
**                                                                            **
** Syntax           : SchM_Exit_Fr_17_Eray_ConfigLockKey                      **
**                                                                            **
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
** Description      : Exits Module exclusive area for Lock sequence to leave  **
**                    "CONFIG" state by writing to SUCC1.CMD commands READY   **
**                                                                            **
*******************************************************************************/
extern void SchM_Exit_Fr_17_Eray_ConfigLockKey(void);

#endif /* FR_17_ERAY_SCHM_H */
