/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2021)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME   : Fls_17_Dmu_ac.h                                             **
**                                                                           **
**  VERSION    :  7.0.0                                                      **
**                                                                           **
**  DATE       :  2021-02-26                                                 **
**                                                                           **
**  VARIANT    : Variant PB                                                  **
**                                                                           **
**  PLATFORM   : Infineon AURIX2G                                            **
**                                                                           **
**  AUTHOR     : DL-AUTOSAR-Engineering                                      **
**                                                                           **
**  VENDOR     : Infineon Technologies                                       **
**                                                                           **
**  DESCRIPTION: This file exports command sequences of Flash driver         **
**                                                                           **
**  SPECIFICATION(S) : Specification of FLS Driver,                          **
**                           AUTOSAR Release 4.2.2 and 4.4.0                 **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: No                                      **
**                                                                           **
******************************************************************************/
/* [cover parentID={6971D4B6-B1DA-4b0c-BE12-26474C5174C3}]
[/cover] */

#ifndef  FLS_17_DMU_AC_H
#define  FLS_17_DMU_AC_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Fls_17_Dmu_Cfg.h"


/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/*  The following macros are used in the command cycles.*/
#define CYCLE_5554  ((uint32)(0x00005554U))
#define CYCLE_AAA8  ((uint32)(0x0000AAA8U))
#define CYCLE_55F0  ((uint32)(0x000055F0U))
#define CYCLE_AA50  ((uint32)(0x0000AA50U))
#define CYCLE_AA58  ((uint32)(0x0000AA58U))

#define MASK_HIGHER4_NIBBLES     ((uint32)0xFFFF0000U)
#define POSITION_0               ((uint32)0)

/* The following values are used in the command cycles */
#define VALUE_80    ((uint32)(0x00000080U))
#define VALUE_F0    ((uint32)(0x000000F0U))
#define VALUE_A0    ((uint32)(0x000000A0U))
#define VALUE_5D    ((uint32)(0x0000005DU))
#define VALUE_A6    ((uint32)(0x000000A6U))
#define VALUE_00    ((uint32)(0x00000000U))
#define VALUE_FA    ((uint32)(0x000000FAU))
#define VALUE_50    ((uint32)(0x00000050U))
#define VALUE_70    ((uint32)(0x00000070U))
#define VALUE_CC    ((uint32)(0x000000CCU))
#define VALUE_AA    ((uint32)(0x000000AAU))
#define VALUE_60    ((uint32)(0x00000060U))
#define VALUE_14    ((uint32)(0x00000014U))

#define FLS_NUMSECTORS_PERNVM  (128U)
#define USER_LEVEL0           (0U)

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

#define FLS_17_DMU_START_SEC_CODE_ASIL_B_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. Even though the memmap
   header is included multiple times, the contents of the file are protected
   from multiple definition / inclusion. */
#include "Fls_17_Dmu_MemMap.h"
void Fls_lResetReadCmdCycle(void);

void Fls_lClearStatusCmdCycle(void);

void Fls_lCallEraseCommand(uint32 PhysicalAddress);
void Fls_lCallWriteCommand(uint32 PhysicalAddress,
                          const Fls_17_Dmu_StateType *StatePtr,
                          uint8 WriteMode);
void Fls_lResumeEraseCmdCycle(uint32 EraseAddress);
void Fls_lUserContentCountCmdCycle(uint32 WordLineAddress);

/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/



/*******************************************************************************
**                      Local Constant Definitions                            **
*******************************************************************************/


/*******************************************************************************
**                      Local Variable Definitions                            **
*******************************************************************************/
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_STOP_SEC_CODE_ASIL_B_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. Even though the memmap
   header is included multiple times, the contents of the file are protected
   from multiple definition / inclusion. */
#include "Fls_17_Dmu_MemMap.h"

#endif
