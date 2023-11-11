/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2016)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME   : CanIf.c                                                      **
**                                                                            **
**  VERSION    : 2.0.0                                                        **
**                                                                            **
**  DATE       : 2020-06-26                                                   **
**                                                                            **
**  VARIANT    : NA                                                           **
**                                                                            **
**  PLATFORM   : Infineon AURIX2G                                             **
**                                                                            **
**  AUTHOR      : DL-AUTOSAR-Engineering                                      **
**                                                                            **
**  VENDOR      : Infineon Technologies                                       **
**                                                                            **
**  DESCRIPTION : This file contains CAN Interface (CanIf) function           **
**                definitions                                                 **
**                Note : This file is for Evaluation Purpose Only             **
**                                                                            **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                      **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Inclusion of CanIf module header file  */
#include "CanIf.h"
#include "CanIf_Cbk.h"
#include "McalLib.h"

/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/

/*******************************************************************************
** Syntax : void CanIf_SetWakeupEvent(uint8 CanNetwork,                       **
**                                    CanIf_WakeupSourceType WakeupSource )   **
**                                                                            **
** Service ID: none                                                           **
**                                                                            **
** Sync/Async:  none                                                          **
**                                                                            **
** Reentrancy:  none                                                          **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Parameters (out):  none                                                    **
**                                                                            **
** Return value:  none                                                        **
**                                                                            **
** Description : This function is called in CanTrcv_MainFunction or           **
**               CanTrcv_CB_WakeupByBus function.                             **
**                                                                            **
*******************************************************************************/
void CanIf_SetWakeupEvent(uint8 CanNetwork,
                          CanIf_WakeupSourceType WakeupSource )
{
}

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/
