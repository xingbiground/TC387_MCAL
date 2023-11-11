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
**  FILENAME     : Fee_Cbk.h                                                  **
**                                                                            **
**  VERSION      : 4.0.0                                                      **
**                                                                            **
**  DATE         : 2020-07-02                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Fee Driver file that exports callback functions            **
**                                                                            **
**  SPECIFICATION(S) : Specification of Fee Driver,                           **
**                     AUTOSAR Release 4.2.2 and 4.4.0                        **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/* [cover parentID={31ED7217-C69B-45fb-BEB4-532265FF310A}]
[/cover] */
#ifndef  FEE_CBK_H
#define  FEE_CBK_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Function Like Macro Definitions                       **
*******************************************************************************/
 
/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/


/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/


/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

 
/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/

/*******************************************************************************
** Syntax : void Fee_JobEndNotification(void)                                 **
**                                                                            **
** Service ID: 16                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This routine shall be called by the underlying flash         **
** driver to report the successful end of an asynchronous operation.          **
*******************************************************************************/
extern void Fee_JobEndNotification(void);


/*******************************************************************************
** Syntax : void Fee_JobErrorNotification(void)                               **
**                                                                            **
** Service ID: 17                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This routine shall be called by the underlying flash         **
** driver to report the failure of an asynchronous operation.                 **
*******************************************************************************/
extern void Fee_JobErrorNotification(void);


/*******************************************************************************
** Syntax : void Fee_17_IllegalStateNotification(void)                        **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This routine shall be called by the underlying flash         **
**                  driver upon reaching the illegal state                    **
*******************************************************************************/
extern void Fee_17_IllegalStateNotification(void);

/*******************************************************************************
** TRACEABILITY: TBD                                                          **
**                                                                            **
** Syntax : void Fee_17_JobEraseErrorNotification(void)                       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : This routine shall be called by the underlying flash         **
** driver to report the failure Erase operation only due EVR bit set          **
*******************************************************************************/
extern void Fee_17_JobEraseErrorNotification(void);



/*******************************************************************************
** TRACEABILITY: TBD                                                          **
**                                                                            **
** Syntax : void Fee_17_JobProgErrorNotification(void)                     **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x30                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : Service to report to FEE module if Program Verify Error      **
**  occurred while programming/writing.                                       **
*******************************************************************************/
extern void Fee_17_JobProgErrorNotification(void);

#endif  /* FEE_CBK_H */

