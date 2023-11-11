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
**  FILENAME     : IFX_Os.h                                                   **
**                                                                            **
**  VERSION      : 0.0.4                                                      **
**                                                                            **
**  DATE         : 2018-10-11                                                 **
**                                                                            **
**  VARIANT      : NA                                                         **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION : Stub header file for OS APIs                                **
**                                                                            **
**  SPECIFICATION(S) :  AUTOSAR Release 4.2.2                                 **
**                                                                            **
**  MAY BE CHANGED BY USER : YES                                              **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
*******************************************************************************/
#ifndef IFX_OS_H
#define IFX_OS_H

#include "Mcal_Compiler.h"

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
void SuspendAllInterrupts(void);
void ResumeAllInterrupts(void);


/*******************************************************************************
**                      Configuration data                                    **
*******************************************************************************/


/*
 Keyword for Interrupt
*/

#ifndef INTERRUPT
#ifdef _TASKING_C_TRICORE_
#if (_TASKING_C_TRICORE_ == 1U)
/*IFX_MISRA_RULE_19_04_STATUS=INTERRUPT cannot be expand to a braced
initialiser*/
#define INTERRUPT __interrupt
#endif
#endif
#ifdef _GNU_C_TRICORE_
#if (_GNU_C_TRICORE_ == 1U)
#define INTERRUPT __interrupt
#endif
#endif
#ifdef _DIABDATA_C_TRICORE_
#if (_DIABDATA_C_TRICORE_ == 1U)
#define INTERRUPT __interrupt
#endif
#endif
#ifdef _GHS_C_TRICORE_
#if (_GHS_C_TRICORE_ == 1U)
#define INTERRUPT __interrupt
#endif
#endif
#endif

#ifdef _DIABDATA_C_TRICORE_
#if (_DIABDATA_C_TRICORE_ == 1U)
asm volatile int get_res (void)
{
  !"%d2"
  mov  %d2, %d2
}
#endif
#endif
#ifdef _GHS_C_TRICORE_
#if ((_GHS_C_TRICORE_ == 1U))
asm int get_res (void)
{

  mov  %d2, %d2
}
#endif
#endif

/*
Inline qualifier, in case of GNU compiler extern is required
for inline function definition , if residing in header file.
Its not required for TASKING compiler.
Its defined to nothing.
*/

#ifndef _INLINEQUALIFIER_
#define _INLINEQUALIFIER_
#endif

#ifdef _TASKING_C_TRICORE_
#if (_TASKING_C_TRICORE_ == 1U)

/*
 * SYSCALL to generate system call trap
 */
/*IFX_MISRA_RULE_19_07_STATUS=Function like macro used to call the Tricore
intrinsic function*/
/*IFX_MISRA_RULE_19_04_STATUS=SYSCALL cannot be expand to a braced
 initialiser*/
#define SYSCALL(tin)   __syscall(tin)

/*
Tasking Intrinsic: Disable Global Interrupt Flag and return it
*/

/*IFX_MISRA_RULE_19_07_STATUS=Function like macro used to call the Tricore
intrinsic function*/
#define DISABLE_AND_SAVE() (__disable_and_save())


/*
Tasking Intrinsic: Restore Global Interrupt Flag
*/

/*IFX_MISRA_RULE_19_07_STATUS=Function like macro used to call the Tricore
intrinsic function*/
#define RESTORE(x) (__restore(x))

#endif
#endif

#ifdef _GNU_C_TRICORE_
#if (_GNU_C_TRICORE_ == 1U)


#define SYSCALL(tin)   _syscall(tin)

#endif
#endif

#ifdef _DIABDATA_C_TRICORE_
#if (_DIABDATA_C_TRICORE_ == 1U)


#define SYSCALL(tin)   _syscall(tin)

#endif
#endif

#ifdef _GHS_C_TRICORE_
#if (_GHS_C_TRICORE_ == 1U)

#define SYSCALL(tin)   __syscall(tin)

#endif
#endif

/*******************************************************************************
** Macro Syntax : __GETTIN(tin)                                               **
**                                                                            **
** Parameters (in) :  None                                                    **
** Parameters (out):  None                                                    **
** return value    : tin : trap number                                        **
** Description    : GETTIN is used to read the trap value from register       **
**                                                                            **
*******************************************************************************/
#ifdef _TASKING_C_TRICORE_
#if (_TASKING_C_TRICORE_ == 1U)

/*IFX_MISRA_RULE_19_07_STATUS=Function like macro used to call the get the tin
 function*/
/*IFX_MISRA_RULE_19_04_STATUS=__GETTIN cannot be expand to a braced
 initialiser*/
#define __GETTIN(tin) \
{ \
  __asm("mov %0,d15" : "=d"(tin)); \
}
#endif
#endif

#ifdef _GNU_C_TRICORE_
#if (_GNU_C_TRICORE_ == 1U)
/*IFX_MISRA_RULE_19_07_STATUS=Function like macro used to call the get the tin
 function*/
/*IFX_MISRA_RULE_19_04_STATUS=__GETTIN cannot be expand to a braced
 initialiser*/

#define __GETTIN(tin) \
{ \
  __asm__ ("mov \t%0,%%d15":"=d" (tin)); \
}
#endif
#endif

#ifdef _DIABDATA_C_TRICORE_
#if (_DIABDATA_C_TRICORE_ == 1U)
/*IFX_MISRA_RULE_19_07_STATUS=Function like macro used to call the get the tin
 function*/
/*IFX_MISRA_RULE_19_04_STATUS=__GETTIN cannot be expand to a braced
 initialiser*/

#define __GETTIN(tin) \
{ \
  __asm (" mov\t %d2,%d15"); \
  tin = get_res();        \
}
#endif
#endif

#ifdef _GHS_C_TRICORE_
#if (_GHS_C_TRICORE_ == 1U)
/*IFX_MISRA_RULE_19_07_STATUS=Function like macro used to call the get the tin
 function*/
/*IFX_MISRA_RULE_19_04_STATUS=__GETTIN cannot be expand to a braced
 initialiser*/

#define __GETTIN(tin) \
{ \
  __asm (" mov\t %d2,%d15"); \
  tin = get_res();        \
}
#endif
#endif


/*******************************************************************************
** Macro Syntax : __trap_handler(puiAddress)                                  **
**                                                                            **
** Parameters (in) :  puiAddress : Address of trap handler                    **
** Parameters (out):  None                                                    **
** return value    : None                                                     **
** Description    : __trap_handler is used to call the trap handler           **
**                                                                            **
*******************************************************************************/
#ifdef _TASKING_C_TRICORE_
#if (_TASKING_C_TRICORE_ == 1U)

/*IFX_MISRA_RULE_19_07_STATUS=Function like macro used to call the trap handler
 function*/
/*IFX_MISRA_RULE_19_04_STATUS=__trap_handler cannot be expand to a braced
 initialiser*/
#define __trap_handler(puiAddress) \
  { __asm ("ji\t %0\n\trfe": :"a" (puiAddress)); }

#endif
#endif

#ifdef _GNU_C_TRICORE_
#if (_GNU_C_TRICORE_ == 1U)
/*IFX_MISRA_RULE_19_07_STATUS=Function like macro used to call the trap handler
 function*/
/*IFX_MISRA_RULE_19_04_STATUS=__trap_handler cannot be expand to a braced
 initialiser*/

#define __trap_handler(puiAddress) \
  { __asm ("ji\t %0\n\trfe": :"a" (puiAddress)); }

#endif
#endif

#ifdef _DIABDATA_C_TRICORE_
#if (_DIABDATA_C_TRICORE_ == 1U)
/*IFX_MISRA_RULE_19_07_STATUS=Function like macro used to call the trap handler
 function*/
/*IFX_MISRA_RULE_19_04_STATUS=__trap_handler cannot be expand to a braced
 initialiser*/
#define __trap_handler(puiAddress) \
{ __asm ("#$$bp"); \
  __asm (" movh.a\t %a15,"#puiAddress"@ha"); \
  __asm (" lea\t %a15,[%a15]"#puiAddress"@l"); \
  __asm (" ji %a15"); \
  __asm (" rfe"); \
  __asm ("#$$ep"); \
}
#endif
#endif

/*******************************************************************************
** Macro Syntax : __set_trapnum(trapnum)                                      **
**                                                                            **
** Parameters (in) :  trapnum : trap number                                   **
** Parameters (out):  None                                                    **
** return value    : None                                                     **
** Description    : __set_trapnum is used to set the trap number              **
**                                                                            **
*******************************************************************************/
#ifdef _TASKING_C_TRICORE_
#if (_TASKING_C_TRICORE_ == 1U)

/*IFX_MISRA_RULE_19_07_STATUS=Function like macro used to set the  trap number
 function*/
/*IFX_MISRA_RULE_19_04_STATUS=__set_trapnum cannot be expand to a braced
 initialiser*/
/*IFX_MISRA_RULE_19_13_STATUS=# used only to set the trap number.
There is no impact of order of evaluation with the # operator at this function*/
#define __set_trapnum(trapnum) \
    { __asm(" addi\t d4,d15,#"#trapnum""); }

#endif
#endif

#ifdef _GNU_C_TRICORE_
#if (_GNU_C_TRICORE_ == 1U)
/*IFX_MISRA_RULE_19_07_STATUS=Function like macro used to set the  trap number
 function*/
/*IFX_MISRA_RULE_19_04_STATUS=__set_trapnum cannot be expand to a braced
 initialiser*/
/*IFX_MISRA_RULE_19_13_STATUS=# used only to set the trap number.
There is no impact of order of evaluation with the # operator at this function*/

#define __set_trapnum(trapnum) \
    { __asm(" addi\t %d4,%d15,"#trapnum""); }

#endif
#endif

#ifdef _DIABDATA_C_TRICORE_
#if (_DIABDATA_C_TRICORE_ == 1U)
/*IFX_MISRA_RULE_19_07_STATUS=Function like macro used to set the  trap number
 function*/
/*IFX_MISRA_RULE_19_04_STATUS=__set_trapnum cannot be expand to a braced
 initialiser*/
/*IFX_MISRA_RULE_19_13_STATUS=# used only to set the trap number.
There is no impact of order of evaluation with the # operator at this function*/

#define __set_trapnum(trapnum) \
    { __asm(" addi\t %d4,%d15,"#trapnum""); }

#endif
#endif
#endif /* IFX_OS_H  */
