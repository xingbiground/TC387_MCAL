/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2013)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  $FILENAME   : Os.c $                                                     **
**                                                                           **
**  $CC VERSION : \main\14 $                                                 **
**                                                                           **
**  $DATE       : 2018-03-07 $                                               **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION : This file contains                                         **
**                - stub for OS functionality.                               **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                     **
**                                                                           **
******************************************************************************/

/******************************************************************************
**                      Includes                                             **
******************************************************************************/

/* Inclusion of Platform_Types.h and Compiler.h */
#include "Std_Types.h"

/* Inclusion of Tasking sfr file */
#include "IfxCpu_reg.h"

/* Include Mcal for Library */
#include "McalLib.h"

/* Inclusion for definition of ENABLE() & DISABLE() functions*/
#include "IFX_Os.h"

/******************************************************************************
**                      Imported Compiler Switch Checks                      **
******************************************************************************/

/******************************************************************************
**                      Private Macro Definitions                            **
******************************************************************************/

/******************************************************************************
**                      Private Type Definitions                             **
******************************************************************************/

/******************************************************************************
**                      Private Function Declarations                        **
******************************************************************************/

/******************************************************************************
**                      Global Constant Definitions                          **
******************************************************************************/

/******************************************************************************
**                      Global Variable Definitions                          **
******************************************************************************/

/******************************************************************************
**                      Private Constant Definitions                         **
******************************************************************************/

/******************************************************************************
**                      Private Variable Definitions                         **
******************************************************************************/
static volatile uint8 Os_IntSaveDisableCounter[MCAL_NO_OF_CORES];
static volatile sint32 Os_SavedIntLevelNested[MCAL_NO_OF_CORES];

/******************************************************************************
**                      Private Function Definitions                         **
******************************************************************************/

/******************************************************************************
**                      Global Function Definitions                          **
******************************************************************************/

/******************************************************************************
** Syntax           : void SuspendAllInterrupts(void)                        **
**                                                                           **
** Service ID       :  none                                                  **
**                                                                           **
** Sync/Async       : Synchronous                                            **
**                                                                           **
** Reentrancy       : non - reentrant                                        **
**                                                                           **
** Parameters(in)   : none                                                   **
**                                                                           **
** Parameters (out) : none                                                   **
**                                                                           **
** Return value     : none                                                   **
**                                                                           **
** Description      : This function Suspends all interrupts, nested          **
**                                                                           **
******************************************************************************/
void SuspendAllInterrupts(void)
{
  uint32 CoreId;

  /* Get the current core id */
  CoreId = Mcal_GetCpuIndex();

  if(Os_IntSaveDisableCounter[CoreId] == 0)
  {
    Os_SavedIntLevelNested[CoreId] = MFCR(CPU_ICR);/* disable interrupts */
    DISABLE();
  }
  Os_IntSaveDisableCounter[CoreId]++;
}
/******************************************************************************/

/*******************************************************************************
** Syntax           : void ResumeAllInterrupts(void)                          **
**                                                                            **
** Service ID       :  none                                                   **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : This function Resumes all interrupts, nested            **
**                                                                            **
*******************************************************************************/
void ResumeAllInterrupts(void)
{
  uint32 CoreId;

  /* Get the current core id */
  CoreId = Mcal_GetCpuIndex();

  if (Os_IntSaveDisableCounter[CoreId] > 0)
  {
    Os_IntSaveDisableCounter[CoreId]--;
  }

  if (Os_IntSaveDisableCounter[CoreId] == 0)
  {
    if (Os_SavedIntLevelNested[CoreId] & (0x00000001U << 15))
    {
      /* interrupts were enabled, enable again */
      ENABLE();
    }
  }
}

