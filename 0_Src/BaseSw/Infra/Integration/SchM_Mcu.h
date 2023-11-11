/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2019)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : SchM_Mcu.h                                                 **
**                                                                            **
**  VERSION      : 2.0.0                                                      **
**                                                                            **
**  DATE         : 2019-02-04                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : SchM file for Mcu                                          **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
/*[cover parentID={A1BC5DF7-EB0E-4ac0-8284-9E803CF88735}][/cover]*/
#ifndef MCU_SCHM_H
#define MCU_SCHM_H
/*******************************************************************************
** Traceability     : [cover parentID={02EC2514-8DF2-4874-914C-9FFE5A5AE438}] **
**                                                                            **
** Syntax           : void SchM_Enter_Mcu_TomTgcReg(void)                     **
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
extern void SchM_Enter_Mcu_TomTgcReg(void);

/*******************************************************************************
** Traceability     : [cover parentID={02EC2514-8DF2-4874-914C-9FFE5A5AE438}] **
**                                                                            **
** Syntax           : void SchM_Exit_Mcu_TomTgcReg(void)                      **
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
extern void SchM_Exit_Mcu_TomTgcReg(void);

/*******************************************************************************
** Traceability     : [cover parentID={8B9E963E-AC41-4ad2-9769-0B55DD407CBB}] **
**                                                                            **
** Syntax           : void SchM_Enter_Mcu_AtomAgcReg(void)                    **
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
extern void SchM_Enter_Mcu_AtomAgcReg(void);

/*******************************************************************************
** Traceability     : [cover parentID={8B9E963E-AC41-4ad2-9769-0B55DD407CBB}] **
**                                                                            **
** Syntax           : void SchM_Exit_Mcu_AtomAgcReg(void)                     **
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
extern void SchM_Exit_Mcu_AtomAgcReg(void);

#endif /* MCU_SCHM_H */
