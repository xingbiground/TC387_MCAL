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
**  FILENAME     : FlsLdr_ExclArea.h                                          **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2020-06-26                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY :                                                            **
**                                                                            **
**  DESCRIPTION : Header file containing the prototype of the APIs to define  **
**                the start and the end of an exclusive area of FlsLoader     **
**                module.                                                     **
**                                                                            **
**  SPECIFICATION(S) : Specification of RTE, AUTOSAR Release 4.2.2, 4.4.0     **
**                                                                            **
**  MAY BE CHANGED BY USER : No                                               **
**                                                                            **
*******************************************************************************/

#ifndef FLSLDR_EXCLAREA_H
#define FLSLDR_EXCLAREA_H

/*******************************************************************************
**                                                                            **
** Syntax           : void FlsLdr_ExclArea_PfProg_Enter(void)                 **
**                                                                            **
** Description      : This API call is invoked by FlsLoader module to define  **
**                    the start of an exclusive area while performing PFlash  **
**                    program operation.                                      **
**                                                                            **
** Service ID       :                                                         **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : void                                                    **
**                                                                            **
*******************************************************************************/
extern void FlsLdr_ExclArea_PfProg_Enter(void);

/*******************************************************************************
**                                                                            **
** Syntax           : void FlsLdr_ExclArea_PfProg_Exit(void)                  **
**                                                                            **
** Description      : This API call is invoked by FlsLoader module to define  **
**                    the end of an exclusive area while performing PFlash    **
**                    program operation.                                      **
**                                                                            **
** Service ID       :                                                         **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : void                                                    **
**                                                                            **
*******************************************************************************/
extern void FlsLdr_ExclArea_PfProg_Exit(void);

/*******************************************************************************
**                                                                            **
** Syntax           : void FlsLdr_ExclArea_PfErase_Enter(void)                **
**                                                                            **
** Description      : This API call is invoked by FlsLoader module to define  **
**                    the start of an exclusive area while performing PFlash  **
**                    erase operation.                                        **
**                                                                            **
** Service ID       :                                                         **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : void                                                    **
**                                                                            **
*******************************************************************************/
extern void FlsLdr_ExclArea_PfErase_Enter(void);

/*******************************************************************************
**                                                                            **
** Syntax           : void FlsLdr_ExclArea_PfErase_Exit(void)                 **
**                                                                            **
** Description      : This API call is invoked by FlsLoader module to define  **
**                    the end of an exclusive area while performing PFlash    **
**                    erase operation.                                        **
**                                                                            **
** Service ID       :                                                         **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : void                                                    **
**                                                                            **
*******************************************************************************/
extern void FlsLdr_ExclArea_PfErase_Exit(void);

#endif /* FLSLDR_EXCLAREA_H */
