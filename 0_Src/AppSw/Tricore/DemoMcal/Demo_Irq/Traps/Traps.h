/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2018)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME   : Traps.h                                                     **
**                                                                           **
**  VERSION    : 1.0.0                                                       **
**                                                                           **
**  DATE       : 2018-03-16                                                  **
**                                                                           **
**  VARIANT    : NA                                                          **
**                                                                           **
**  PLATFORM   : Infineon AURIX2G                                            **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION  : This file has all supporting information of Trap handler  **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                     **
**                                                                           **
******************************************************************************/
#ifndef TRAPS_H
#define TRAPS_H
/******************************************************************************
**                      Includes                                             **
******************************************************************************/
#include "McalLib.h"
#include "Std_Types.h"

#define MCAL_CALL_TIN_WRITE_PERIP_ENDINIT            (0U)
#define MCAL_CALL_TIN_WRITE_SAFETY_ENDINIT           (1U)
#define MCAL_CALL_TIN_WRITE_SAFETY_ENDINIT_MASK      (2U)
#define MCAL_CALL_TIN_WRITE_CPU_ENDINIT              (3U)
#define MCAL_CALL_TIN_SET_BIT_ATOMIC                 (4U)
#define MCAL_TIN_CALL_WRITE32                        (5U)
#define MCAL_TIN_CALL_MODIFY32                       (6U)
#define MCAL_TIN_CALL_READ32                         (7U)
#define MCAL_CALL_TIN_WRITE_SAFETY_ENDINIT_PROTREG16 (8U)

/* Macro to define the type of the implementaion
Following values for macro IFX_MCAL_RUN_MODE_DEFINE is permitted
0U MCAL runs in Supervisor mode
1U MCAL runs in User-1 mode without OS
2U MCAL runs in User-1 mode with OS
*/
/* This macro can also be defined via command line during compilation */
#ifndef IFX_MCAL_RUN_MODE_DEFINE
#define IFX_MCAL_RUN_MODE_DEFINE (0U)
#endif /* End For IFX_MCAL_RUN_MODE_DEFINE */
/* This macro can also be defined via command line during compilation */
#ifndef IFX_MCAL_TEST_USER_MODE_DEFINE
#define IFX_MCAL_TEST_USER_MODE_DEFINE (1U)
#endif /* End For IFX_MCAL_TEST_USER_MODE_DEFINE */

/*
GET_ADDRESS_REG : to read the data from a register to a variable
*/
#if defined _DIABDATA_C_TRICORE_
#if (_DIABDATA_C_TRICORE_ == 1U)

#define GET_ADDRESS_REG(reg,dummy) \
  __asm (" mov.d\t %d2,%"#reg""); \
  dummy = get_ret_val();

#define GET_DATA_REG(reg,dummy) \
  __asm (" mov\t %d2,%"#reg""); \
  dummy = get_ret_val();

/*
get_ret_val : ASM function to get the return value
*/
asm volatile int get_ret_val (void)
{
  !"%d2"
  mov  %d2, %d2
}
#endif
#endif

#endif /*END OF FILE TRAPS_H*/
