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
**  FILENAME     : Traps.c                                                    **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2018-02-02                                                 **
**                                                                            **
**  VARIANT      : NA                                                         **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Trap handler functions source file                         **
**                                                                            **
**  MAY BE CHANGED BY USER [yes/no]: Yes                                      **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Std_Types.h"
#include "IfxScu_reg.h"
#include "IfxCpu_reg.h"
#include "Test_Print.h"
#include "IFX_Os.h"
#include "Traps.h"
/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/

uint8 Trap_Status;

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

#define CPU_SPINLOCK_TIMEOUT_TRAP   (0xFFFFFFU)

#ifdef _TASKING_C_TRICORE_
#if (_TASKING_C_TRICORE_ == 1U)
#define DEBUG()  __debug()
#endif /* #if (_TASKING_C_TRICORE_ == 1U) */
#endif

#ifdef _GNU_C_TRICORE_
#if (_GNU_C_TRICORE_ == 1U)
#define DEBUG() __asm__ volatile ("debug")
#endif /* #if (_GNU_C_TRICORE_ == 1U) */
#endif

#ifdef _DIABDATA_C_TRICORE_
#if (_DIABDATA_C_TRICORE_ == 1U)
#define DEBUG() __debug()
#define __debug _debug
#endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
#endif
#ifdef _GHS_C_TRICORE_
#if (_GHS_C_TRICORE_ == 1U)
#define DEBUG() __debug()
#endif /* #if (_GNU_C_TRICORE_ == 1U) */
#endif

/******************************************************************************
**                      Private Variable Definitions                         **
******************************************************************************/

/******************************************************************************
**                      Private Type Definitions                             **
******************************************************************************/

/******************************************************************************
**                      Private Function Declarations                        **
******************************************************************************/
void _trap_0( void );
void _trap_1( void );
void _trap_2( void );
void _trap_3( void );
void _trap_4( void );
void _trap_5( void );
void _trap_6( void );
void _trap_7( void );
/******************************************************************************
**                      Global Constant Definitions                          **
******************************************************************************/

/******************************************************************************
**                      Global Variable Definitions                          **
******************************************************************************/
volatile uint32 SFR_Return_Value;
volatile uint32 SV_Return_Value;
static uint32 UVALCON0;
static volatile uint32 TrapIdentification[8][8];
volatile uint32 Trap_lock;
/******************************************************************************
**                      Global Function Definitions                          **
******************************************************************************/

/******************************************************************************
** Syntax : void _trap_0( void )                                             **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Sample Service for  class 0 trap                            **
**                                                                           **
******************************************************************************/
/* Trap class 0 handler. */
void _trap_0( void )
{
  uint32 tin;
  uint32 CoreId = Mcal_GetCpuIndex();

  __asm ("svlcx");

  __GETTIN (tin);

  TrapIdentification[0][tin] = 1;
  switch(tin)
  {
    case 0:
      Mcal_GetSpinlock(&Trap_lock, CPU_SPINLOCK_TIMEOUT_TRAP);
      print_f("\nCoreId = %d\n", CoreId);
      print_f("\nClass 0: Virtual Address Fill Trap occurred\n");
      Mcal_ReleaseSpinlock(&Trap_lock);
      get_char();
      break;

    case 1:
      Mcal_GetSpinlock(&Trap_lock, CPU_SPINLOCK_TIMEOUT_TRAP);
      print_f("\nCoreId = %d\n", CoreId);
      print_f("\nClass 0: Virtual Address Protection Trap occurred\n");
      Mcal_ReleaseSpinlock(&Trap_lock);
      get_char();
      break;

    default:
      /* Halt the execution if debug mode enabled.*/
      DEBUG();
      break;
  }
  __asm ("rslcx \n");
  __asm ("rfe \n");
}
/******************************************************************************
** Syntax : void _trap_1( void )                                             **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Sample handler for  class 1 trap                            **
**                                                                           **
******************************************************************************/
/* Trap class 1 handler. */
void _trap_1( void )
{
  uint32 tin;
  uint32 CoreId = Mcal_GetCpuIndex();
  __asm ("svlcx");

  __GETTIN (tin);

  TrapIdentification[1][tin] = 1;
  switch(tin)
  {
    case 1:
      Mcal_GetSpinlock(&Trap_lock, CPU_SPINLOCK_TIMEOUT_TRAP);
      print_f("\nCoreId = %d\n", CoreId);
      print_f("\nClass 1: Privilege Instruction Trap occurred\n");
      Mcal_ReleaseSpinlock(&Trap_lock);
      get_char();
      break;

    case 2:
      Mcal_GetSpinlock(&Trap_lock, CPU_SPINLOCK_TIMEOUT_TRAP);
      print_f("\nCoreId = %d\n", CoreId);
      print_f("\nClass 1: Memory Protection Read Trap occurred\n");
      Mcal_ReleaseSpinlock(&Trap_lock);
      get_char();
      break;

    case 3:
      Mcal_GetSpinlock(&Trap_lock, CPU_SPINLOCK_TIMEOUT_TRAP);
      print_f("\nCoreId = %d\n", CoreId);
      print_f("\nClass 1: Memory Protection Write Trap occurred\n");
      Mcal_ReleaseSpinlock(&Trap_lock);
      get_char();
      break;

    case 4:
      Mcal_GetSpinlock(&Trap_lock, CPU_SPINLOCK_TIMEOUT_TRAP);
      print_f("\nCoreId = %d\n", CoreId);
      print_f("\nClass 1: Memory Protection Execution Trap occurred\n");
      Mcal_ReleaseSpinlock(&Trap_lock);
      get_char();
      break;

    case 5:
      Mcal_GetSpinlock(&Trap_lock, CPU_SPINLOCK_TIMEOUT_TRAP);
      print_f("\nCoreId = %d\n", CoreId);
      print_f("\nClass 1: Memory Protection Peripheral Access Trap occurred\n");
      Mcal_ReleaseSpinlock(&Trap_lock);
      get_char();
      break;

    case 6:
      Mcal_GetSpinlock(&Trap_lock, CPU_SPINLOCK_TIMEOUT_TRAP);
      print_f("\nCoreId = %d\n", CoreId);
      print_f("\nClass 1: Memory Protection Null Address Trap occurred\n");
      Mcal_ReleaseSpinlock(&Trap_lock);
      get_char();
      break;

    case 7:
      Mcal_GetSpinlock(&Trap_lock, CPU_SPINLOCK_TIMEOUT_TRAP);
      print_f("\nCoreId = %d\n", CoreId);
      print_f("\nClass 1: Global Register Write Protection Trap occurred\n");
      Mcal_ReleaseSpinlock(&Trap_lock);
      get_char();
      break;

    default:
      /* Halt the execution if debug mode enabled.*/
      DEBUG();
      break;
  }
  __asm ("rslcx\n");
  __asm ("rfe \n");
}
/******************************************************************************
** Syntax : void _trap_2( void )                                             **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Sample handler for  class 2 trap                            **
**                                                                           **
******************************************************************************/
/* Trap class 2 handler. */
void _trap_2( void )
{
  uint32 tin;
  uint32 CoreId = Mcal_GetCpuIndex();

  __asm ("svlcx");

  __GETTIN (tin);

  TrapIdentification[2][tin] = 1;
  switch(tin)
  {
    case 1:
      Mcal_GetSpinlock(&Trap_lock, CPU_SPINLOCK_TIMEOUT_TRAP);
      print_f("\nCoreId = %d\n", CoreId);
      print_f("\nClass 2: Illegal Opcode Trap occurred\n");
      Mcal_ReleaseSpinlock(&Trap_lock);
      get_char();
      break;

    case 2:
      Mcal_GetSpinlock(&Trap_lock, CPU_SPINLOCK_TIMEOUT_TRAP);
      print_f("\nCoreId = %d\n", CoreId);
      print_f("\nClass 2: Unimplemented Opcode Trap occurred\n");
      Mcal_ReleaseSpinlock(&Trap_lock);
      get_char();
      break;

    case 3:
      Mcal_GetSpinlock(&Trap_lock, CPU_SPINLOCK_TIMEOUT_TRAP);
      print_f("\nCoreId = %d\n", CoreId);
      print_f("\nClass 2: Invalid Operand Specification Trap occurred\n");
      Mcal_ReleaseSpinlock(&Trap_lock);
      get_char();
      break;

    case 4:
      Mcal_GetSpinlock(&Trap_lock, CPU_SPINLOCK_TIMEOUT_TRAP);
      print_f("\nCoreId = %d\n", CoreId);
      print_f("\nClass 2: Data Address Alignment Trap occurred\n");
      Mcal_ReleaseSpinlock(&Trap_lock);
      get_char();
      break;

    case 5:
      Mcal_GetSpinlock(&Trap_lock, CPU_SPINLOCK_TIMEOUT_TRAP);
      print_f("\nCoreId = %d\n", CoreId);
      print_f("\nClass 2: Invalid Local Memory Address Trap occurred\n");
      Mcal_ReleaseSpinlock(&Trap_lock);
      get_char();
      break;

    default:
      /* Halt the execution if debug mode enabled.*/
      DEBUG();
      break;
  }
  __asm ("rslcx \n");
  __asm ("rfe \n");
}
/******************************************************************************
** Syntax : void _trap_3( void )                                             **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Sample handler for  class 3 trap                            **
**                                                                           **
******************************************************************************/

/* Trap class 3 handler. */
void _trap_3( void )
{
  /* No local variables used in this function */
  /* No function calls to be performed */
  uint32 tin;
  uint32 CoreId = Mcal_GetCpuIndex();

  __asm ("svlcx");

  __GETTIN (tin);

  TrapIdentification[3][tin] = 1;

  UVALCON0  = (uint32) SCU_WDTCPU0_CON0.U;
  SCU_WDTCPU0_CON0.U = SCU_WDTCPU0_CON0.U & ~0x00000001 ;

  UVALCON0 |=  0x000000F1;       /*  set HWPW1 = 1111b */
  UVALCON0 &= ~0x00000002;       /*  set WDTLCK = 0 */
  UVALCON0 &= ~0x0000000C;       /*  set HWPW0 = 00b */

  SCU_WDTCPU0_CON0.U =  UVALCON0;          /*  unlock access */

  SCU_WDTCPU0_CON0.U  |=  0x000000F2;      /*  set HWPW1 = 1111b and WDTLCK = 1 */
  SCU_WDTCPU0_CON0.U  &= ~0x0000000C;      /*  set HWPW0 = 00b */

  switch(tin)
  {
    case 1:
    /* Free context list depletion trap */
    case 2:
    /* Call depth overflow trap occurred */

    case 3:
    /* Call depth underflow trap occurred */
    case 4:
    /* Free context list underflow trap */
    case 5:
    /* call stack underflow trap */
    case 6:
    /* context type trap */
    case 7:
      /* Nesting error */
      /* Perform reset */
      Mcal_GetSpinlock(&Trap_lock, CPU_SPINLOCK_TIMEOUT_TRAP);
      print_f("\nCoreId = %d\n", CoreId);
      Mcal_ReleaseSpinlock(&Trap_lock);
      SCU_SWRSTCON.B.SWRSTREQ = 1U;
      break;
    default:
      /* Halt the execution if debug mode enabled.*/
      DEBUG();
      break;
  }
  __asm ("rslcx \n");
  __asm ("rfe \n");

  /* The return statement here intentionally removed because compiler will
     generate SVLCX instruction in the beginning of trap3 handler which again
     results in trap3 because there is no free CSA, so the warning generated by
     compiler here should be ignored */
}

/******************************************************************************
** Syntax : void _trap_4( void )                                             **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Sample handler for  class 4 trap                            **
**                                                                           **
******************************************************************************/
/* Trap class 4 handler. */
void _trap_4( void )
{
  uint32 tin;
  uint32 CoreId = Mcal_GetCpuIndex();

  __asm ("svlcx\n");

  __GETTIN (tin);

  TrapIdentification[4][tin] = 1;
  switch(tin)
  {
    case 1:
      Mcal_GetSpinlock(&Trap_lock, CPU_SPINLOCK_TIMEOUT_TRAP);
      print_f("\nCoreId = %d\n", CoreId);
      print_f("\nClass 4: Program Fetch Synchronous Error Trap occurred\n");
      Mcal_ReleaseSpinlock(&Trap_lock);
      get_char();
      break;

    case 2:
      Mcal_GetSpinlock(&Trap_lock, CPU_SPINLOCK_TIMEOUT_TRAP);
      print_f("\nCoreId = %d\n", CoreId);
      print_f("\nClass 4: Data Access Synchronous Error Trap occurred\n");
      Mcal_ReleaseSpinlock(&Trap_lock);
      get_char();
      break;

    case 3:
      Mcal_GetSpinlock(&Trap_lock, CPU_SPINLOCK_TIMEOUT_TRAP);
      print_f("\nCoreId = %d\n", CoreId);
      print_f("\nClass 4: Data Access Asynchronous Error Trap occurred\n");
      Mcal_ReleaseSpinlock(&Trap_lock);
      get_char();
      break;

    case 4:
      Mcal_GetSpinlock(&Trap_lock, CPU_SPINLOCK_TIMEOUT_TRAP);
      print_f("\nCoreId = %d\n", CoreId);
      print_f("\nClass 4: Co-processor Trap Asynchronous Error Trap occurred\n");
      Mcal_ReleaseSpinlock(&Trap_lock);
      get_char();
      break;

    case 5:
      Mcal_GetSpinlock(&Trap_lock, CPU_SPINLOCK_TIMEOUT_TRAP);
      print_f("\nCoreId = %d\n", CoreId);
      print_f("\nClass 4: Program Memory Integrity Error Trap occurred\n");
      Mcal_ReleaseSpinlock(&Trap_lock);
      get_char();
      break;

    case 6:
    /*Compiler switch is used to Disable/Ignore Data Memory Integrity Error Trap, when a test case executed intentionally to read data from Flash location which has no data in it*/
      #if defined (FLSLDR_DIE_TRAP_DIS) && (FLSLDR_DIE_TRAP_DIS == 1)
      #else
      Mcal_GetSpinlock(&Trap_lock, CPU_SPINLOCK_TIMEOUT_TRAP);
      print_f("\nCoreId = %d\n", CoreId);
      print_f("\nClass 4: Data Memory Integrity Error Trap occurred\n");
      Mcal_ReleaseSpinlock(&Trap_lock);
      get_char();
      #endif
      break;

    case 7:
      Mcal_GetSpinlock(&Trap_lock, CPU_SPINLOCK_TIMEOUT_TRAP);
      print_f("\nCoreId = %d\n", CoreId);
      print_f("\nClass 4: Temporal Asynchronous Error Trap occurred\n");
      Mcal_ReleaseSpinlock(&Trap_lock);
      get_char();
      break;

    default:
      /* Halt the execution if debug mode enabled.*/
      DEBUG();
      break;
  }
  __asm ("rslcx \n");
  __asm ("rfe \n");
}
/******************************************************************************
** Syntax : void _trap_5( void )                                             **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Sample handler for  class 5 trap                            **
**                                                                           **
******************************************************************************/
/* Trap class 5 handler. */
void _trap_5( void )
{
  uint32 tin;
  uint32 CoreId = Mcal_GetCpuIndex();

  __asm ("svlcx");

  __GETTIN (tin);

  TrapIdentification[5][tin] = 1;
  switch(tin)
  {
    case 1:
      Mcal_GetSpinlock(&Trap_lock, CPU_SPINLOCK_TIMEOUT_TRAP);
      print_f("\nCoreId = %d\n", CoreId);
      print_f("\nClass 5: Arithmetic Overflow Trap occurred\n");
      Mcal_ReleaseSpinlock(&Trap_lock);
      get_char();
      break;

    case 2:
      Mcal_GetSpinlock(&Trap_lock, CPU_SPINLOCK_TIMEOUT_TRAP);
      print_f("\nCoreId = %d\n", CoreId);
      print_f("\nClass 5: Sticky Arithmetic Overflow Trap occurred\n");
      Mcal_ReleaseSpinlock(&Trap_lock);
      get_char();
      break;

    default:
      /* Halt the execution if debug mode enabled.*/
      DEBUG();
      break;
  }
  __asm ("rslcx \n");
  __asm ("rfe \n");
}

/******************************************************************************
** Syntax : void _trap_6( void )                                             **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Sample handler for  class 6 trap                            **
**                                                                           **
******************************************************************************/

/* *INDENT-OFF* */


/* Trap class 6 handler. */
void _trap_6( void )
{
    uint32 CoreId = Mcal_GetCpuIndex();
    uint8 tin;
  __asm ("svlcx");

  __GETTIN (tin);

  /* TIN can be any number between 0 and 255.
   * storing the tin number in
   * TrapIdentification[6][0]
   */
  TrapIdentification[6][0] = tin;

  if ((MCAL_TIN_CALL_WRITE32 == tin))
  {
    #if defined _DIABDATA_C_TRICORE_
    #if (_DIABDATA_C_TRICORE_ == 1U)
    uint32 TempAddress;
    #endif
    #endif
    uint32 *SFR=NULL;
    uint32 Value=0;

    #ifdef _TASKING_C_TRICORE_
    #if (_TASKING_C_TRICORE_ == 1U)
      __asm("mov.aa %0,a4" : "=a"(SFR));
      __asm("mov %0,d5" : "=d"(Value));
    #endif
    #elif defined _GNU_C_TRICORE_
    #if (_GNU_C_TRICORE_ == 1U)
      __asm__("mov.aa %0,%%a4" : "=a"(SFR));
      __asm__("mov %0,%%d5" : "=d"(Value));
    #endif
    #elif defined _DIABDATA_C_TRICORE_
    #if (_DIABDATA_C_TRICORE_ == 1U)
      GET_ADDRESS_REG(a4,TempAddress);
      GET_DATA_REG(d5,Value);
      SFR = (uint32 * )TempAddress;
    #endif
	#elif defined _GHS_C_TRICORE_
    #if (_GHS_C_TRICORE_ == 1U)
      __asm("mov.aa %0,a4" : "=a"(SFR));
      __asm("mov %0,d5" : "=d"(Value));
    #endif
    #endif
    *SFR = Value;
  }
  else if ((MCAL_CALL_TIN_WRITE_PERIP_ENDINIT == tin))
  {
    #if defined _DIABDATA_C_TRICORE_
    #if (_DIABDATA_C_TRICORE_ == 1U)
    uint32 TempAddress;
    #endif
    #endif
    uint32 *SFR=NULL;
    uint32 Value=0;
    #ifdef _TASKING_C_TRICORE_
    #if (_TASKING_C_TRICORE_ == 1U)
      __asm("mov.aa %0,a4" : "=a"(SFR));
      __asm("mov %0,d4" : "=d"(Value));
    #endif
    #elif defined _GNU_C_TRICORE_
    #if (_GNU_C_TRICORE_ == 1U)
      __asm__("mov.aa %0,%%a4" : "=a"(SFR));
      __asm__("mov %0,%%d4" : "=d"(Value));
    #endif
    #elif defined _DIABDATA_C_TRICORE_
    #if (_DIABDATA_C_TRICORE_ == 1U)
      GET_ADDRESS_REG(a4,TempAddress);
      GET_DATA_REG(d4,Value);
      SFR = (uint32 * )TempAddress;
    #endif
	#elif defined _GHS_C_TRICORE_
    #if (_GHS_C_TRICORE_ == 1U)
      __asm("mov.aa %0,a4" : "=a"(SFR));
      __asm("mov %0,d4" : "=d"(Value));
    #endif
    #endif
    Mcal_WritePeripEndInitProtReg(SFR, Value);
  }
  else if ((MCAL_CALL_TIN_WRITE_SAFETY_ENDINIT == tin))
  {
    #if defined _DIABDATA_C_TRICORE_
    #if (_DIABDATA_C_TRICORE_ == 1U)
    uint32 TempAddress;
    #endif
    #endif
    uint32 *SFR=NULL;
    uint32 Value=0;
    #ifdef _TASKING_C_TRICORE_
    #if (_TASKING_C_TRICORE_ == 1U)
      __asm("mov.aa %0,a4" : "=a"(SFR));
      __asm("mov %0,d4" : "=d"(Value));
    #endif
    #elif defined _GNU_C_TRICORE_
    #if (_GNU_C_TRICORE_ == 1U)
      __asm__("mov.aa %0,%%a4" : "=a"(SFR));
      __asm__("mov %0,%%d4" : "=d"(Value));
    #endif
    #elif defined _DIABDATA_C_TRICORE_
    #if (_DIABDATA_C_TRICORE_ == 1U)
      GET_ADDRESS_REG(a4,TempAddress);
      GET_DATA_REG(d4,Value);
      SFR = (uint32 * )TempAddress;
    #endif
	#elif defined _GHS_C_TRICORE_
    #if (_GHS_C_TRICORE_ == 1U)
      __asm("mov.aa %0,a4" : "=a"(SFR));
      __asm("mov %0,d4" : "=d"(Value));
    #endif
    #endif
    Mcal_WriteSafetyEndInitProtReg(SFR, Value);
  }
  else if ((MCAL_CALL_TIN_WRITE_SAFETY_ENDINIT_MASK == tin))
  {
    #if defined _DIABDATA_C_TRICORE_
    #if (_DIABDATA_C_TRICORE_ == 1U)
    uint32 TempAddress;
    #endif
    #endif
    uint32 *SFR=NULL;
    uint32 Value=0;
    uint32 Mask=0;
    #ifdef _TASKING_C_TRICORE_
    #if (_TASKING_C_TRICORE_ == 1U)
      __asm("mov.aa %0,a4" : "=a"(SFR));
      __asm("mov %0,d4" : "=d"(Value));
      __asm("mov %0,d5" : "=d"(Mask));
    #endif
    #elif defined _GNU_C_TRICORE_
    #if (_GNU_C_TRICORE_ == 1U)
      __asm__("mov.aa %0,%%a4" : "=a"(SFR));
      __asm__("mov %0,%%d4" : "=d"(Value));
      __asm__("mov %0,%%d5" : "=d"(Mask));
    #endif
    #elif defined _DIABDATA_C_TRICORE_
    #if (_DIABDATA_C_TRICORE_ == 1U)
      GET_ADDRESS_REG(a4,TempAddress);
      GET_DATA_REG(d4,Value);
      GET_DATA_REG(d5,Mask);
      SFR = (uint32 * )TempAddress;
    #endif
	#elif defined _GHS_C_TRICORE_
    #if (_GHS_C_TRICORE_ == 1U)
      __asm("mov.aa %0,a4" : "=a"(SFR));
      __asm("mov %0,d4" : "=d"(Value));
      __asm("mov %0,d5" : "=d"(Mask));
    #endif
    #endif
    Mcal_WriteSafetyEndInitProtRegMask(SFR, Value, Mask);
  }
  else if ((MCAL_CALL_TIN_WRITE_CPU_ENDINIT == tin))
  {
    #if defined _DIABDATA_C_TRICORE_
    #if (_DIABDATA_C_TRICORE_ == 1U)
    uint32 TempAddress;
    #endif
    #endif
    uint32 *SFR=NULL;
    uint32 Value=0;
    #ifdef _TASKING_C_TRICORE_
    #if (_TASKING_C_TRICORE_ == 1U)
      __asm("mov.aa %0,a4" : "=a"(SFR));
      __asm("mov %0,d4" : "=d"(Value));
    #endif
    #elif defined _GNU_C_TRICORE_
    #if (_GNU_C_TRICORE_ == 1U)
      __asm__("mov.aa %0,%%a4" : "=a"(SFR));
      __asm__("mov %0,%%d4" : "=d"(Value));
    #endif
    #elif defined _DIABDATA_C_TRICORE_
    #if (_DIABDATA_C_TRICORE_ == 1U)
      GET_ADDRESS_REG(a4,TempAddress);
      GET_DATA_REG(d4,Value);
      SFR = (uint32 * )TempAddress;
    #endif
	#elif defined _GHS_C_TRICORE_
    #if (_GHS_C_TRICORE_ == 1U)
      __asm("mov.aa %0,a4" : "=a"(SFR));
      __asm("mov %0,d4" : "=d"(Value));
    #endif
    #endif
    Mcal_WriteCpuEndInitProtReg(SFR, Value);
  }
  else  if ((MCAL_TIN_CALL_MODIFY32 == tin))
  {
    #if defined _DIABDATA_C_TRICORE_
    #if (_DIABDATA_C_TRICORE_ == 1U)
    uint32 TempAddress;
    #endif
    #endif
    uint32 *SFR=NULL;
    uint32 SetMask=0;
    uint32 ClearMask=0;
    uint32 Value=0;
    #ifdef _TASKING_C_TRICORE_
    #if (_TASKING_C_TRICORE_ == 1U)
      __asm("mov.aa %0,a4" : "=a"(SFR));
      __asm("mov %0,d5" : "=d"(ClearMask));
      __asm("mov %0,d6" : "=d"(SetMask));
    #endif
    #elif defined _GNU_C_TRICORE_
    #if (_GNU_C_TRICORE_ == 1U)
      __asm__("mov.aa %0,%%a4" : "=a"(SFR));
      __asm__("mov %0,%%d5" : "=d"(ClearMask));
      __asm__("mov %0,%%d6" : "=d"(SetMask));
    #endif
    #elif defined _DIABDATA_C_TRICORE_
    #if (_DIABDATA_C_TRICORE_ == 1U)
      GET_ADDRESS_REG(a4,TempAddress);
      GET_DATA_REG(d5,ClearMask);
      GET_DATA_REG(d6,SetMask);
      SFR = (uint32 * )TempAddress;
    #endif
	#elif defined _GHS_C_TRICORE_
    #if (_GHS_C_TRICORE_ == 1U)
      __asm("mov.aa %0,a4" : "=a"(SFR));
      __asm("mov %0,d5" : "=d"(ClearMask));
      __asm("mov %0,d6" : "=d"(SetMask));
    #endif
    #endif
    Value = ((*SFR)& (ClearMask));
    *SFR = ((Value)|(SetMask));
  }
  else  if ((MCAL_TIN_CALL_READ32 == tin))
  {
    #if defined _DIABDATA_C_TRICORE_
    #if (_DIABDATA_C_TRICORE_ == 1U)
    uint32 TempAddress;
    #endif
    #endif
    uint32 *SFR=NULL;
    #ifdef _TASKING_C_TRICORE_
    #if (_TASKING_C_TRICORE_ == 1U)
      __asm("mov.aa %0,a4" : "=a"(SFR));
    #endif
    #elif defined _GNU_C_TRICORE_
    #if (_GNU_C_TRICORE_ == 1U)
      __asm__("mov.aa %0,%%a4" : "=a"(SFR));
    #endif
    #elif defined _DIABDATA_C_TRICORE_
    #if (_DIABDATA_C_TRICORE_ == 1U)
      GET_ADDRESS_REG(a4,TempAddress);
      SFR = (uint32 * )TempAddress;
    #endif
	#elif defined _GHS_C_TRICORE_
    #if (_GHS_C_TRICORE_ == 1U)
      __asm("mov.aa %0,a4" : "=a"(SFR));
    #endif
    #endif
    SFR_Return_Value = *SFR;
  }
  else if ((MCAL_CALL_TIN_WRITE_SAFETY_ENDINIT_PROTREG16 == tin))
  {
    #if defined _DIABDATA_C_TRICORE_
    #if (_DIABDATA_C_TRICORE_ == 1U)
    uint32 TempAddress;
    #endif
    #endif
    uint32 *SFR=NULL;
    uint16 Value=0;
    #ifdef _TASKING_C_TRICORE_
    #if (_TASKING_C_TRICORE_ == 1U)
      __asm("mov.aa %0,a4" : "=a"(SFR));
      __asm("mov %0,d4" : "=d"(Value));
    #endif
    #elif defined _GNU_C_TRICORE_
    #if (_GNU_C_TRICORE_ == 1U)
      __asm__("mov.aa %0,%%a4" : "=a"(SFR));
      __asm__("mov %0,%%d4" : "=d"(Value));
    #endif
    #elif defined _DIABDATA_C_TRICORE_
    #if (_DIABDATA_C_TRICORE_ == 1U)
      GET_ADDRESS_REG(a4,TempAddress);
      GET_DATA_REG(d4,Value);
      SFR = (uint32 * )TempAddress;
    #endif
	#elif defined _GHS_C_TRICORE_
    #if (_GHS_C_TRICORE_ == 1U)
      __asm("mov.aa %0,a4" : "=a"(SFR));
      __asm("mov %0,d4" : "=d"(Value));
    #endif
    #endif
    Mcal_WriteSafetyEndInitProtReg16(SFR, Value);
  }
   else if ((MCAL_CALL_TIN_SET_BIT_ATOMIC == tin))
  {
    volatile sint32* DataPtr =NULL;
    volatile uint32 Data=0;
    volatile sint32 BitPos=0;
    volatile uint32 BitLen=0;
#ifdef _TASKING_C_TRICORE_
#if (_TASKING_C_TRICORE_ == 1)
      __asm("mov.aa %0,a4" : "=a"(DataPtr));
      __asm("mov %0,d6" : "=d"(Data));
      __asm("mov %0,d4" : "=d"(BitPos));
      __asm("mov %0,d5" : "=d"(BitLen));
#endif /* #if (_TASKING_C_TRICORE_ == 1U) */
#elif defined _GNU_C_TRICORE_
#if (_GNU_C_TRICORE_ == 1U)
      __asm("mov.aa %0,%%a4" : "=a"(DataPtr));
      __asm("mov %0,%%d6" : "=d"(Data));
      __asm("mov %0,%%d4" : "=d"(BitPos));
      __asm("mov %0,%%d5" : "=d"(BitLen));
#endif /* #if (_GNU_C_TRICORE_ == 1U) */
#elif defined _DIABDATA_C_TRICORE_
#if (_DIABDATA_C_TRICORE_ == 1U)
      uint32 tempaddress;
      GET_ADDRESS_REG(a4,tempaddress);
      DataPtr= (sint32*)tempaddress;
      GET_DATA_REG(d6,Data);
      GET_DATA_REG(d4,BitPos);
      GET_DATA_REG(d5,BitLen);
#endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
#elif defined _GHS_C_TRICORE_
#if (_GHS_C_TRICORE_ == 1)
      __asm("mov.aa %0,a4" : "=a"(DataPtr));
      __asm("mov %0,d6" : "=d"(Data));
      __asm("mov %0,d4" : "=d"(BitPos));
      __asm("mov %0,d5" : "=d"(BitLen));
#endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
#endif
  switch(BitLen)
   {
     case 1:
       IMASKLDMST((sint32*)(void*)(DataPtr),(Data),(BitPos),1);
      break;
     case 2:
       IMASKLDMST((sint32*)(void*)(DataPtr),(Data),(BitPos),2);
      break;      
     case 3:
       IMASKLDMST((sint32*)(void*)(DataPtr),(Data),(BitPos),3);
      break;    
      case 4:
       IMASKLDMST((sint32*)(void*)(DataPtr),(Data),(BitPos),4);
      break;  
     case 8:
       IMASKLDMST((sint32*)(void*)(DataPtr),(Data),(BitPos),8);
      break;
     case 12:
       IMASKLDMST((sint32*)(void*)(DataPtr),(Data),(BitPos),12);
      break;      
     case 16:
       IMASKLDMST((sint32*)(void*)(DataPtr),(Data),(BitPos),16);
      break; 
     default:
     break;
   }     
  }
  else
  {
    Mcal_GetSpinlock(&Trap_lock,CPU_SPINLOCK_TIMEOUT_TRAP);
    print_f("\nCoreId = %d\n", CoreId);   
    print_f("\nClass 6: System Call Trap occurred\n");
    Mcal_ReleaseSpinlock(&Trap_lock);
    get_char();
  }

  __asm ("rslcx \n");
  __asm ("rfe \n");
}

/******************************************************************************
** Syntax : void _trap_7( void )                                             **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Sample handler for  class 7 trap                            **
**                                                                           **
******************************************************************************/

/* Trap class 7 handler. */
void _trap_7( void )
{
  uint32 tin;
  uint32 CoreId = Mcal_GetCpuIndex();

  __asm ("svlcx");
  __GETTIN (tin);

  TrapIdentification[7][tin] = 1;

  switch(tin)
   {
     case 0:
      Trap_Status = 5;
            Mcal_GetSpinlock(&Trap_lock,CPU_SPINLOCK_TIMEOUT_TRAP);
            print_f("\nCoreId = %d\n", CoreId);   
            print_f("\nClass 7: Non-Maskable Interrupt Trap occurred\n");
            Mcal_ReleaseSpinlock(&Trap_lock);            
          break;

     default:
          /* Halt the execution if debug mode enabled.*/
          DEBUG();
          break;
   }
  __asm ("rslcx \n");
  __asm ("rfe \n");
}

/******************************************************************************
** Syntax : void traptab_cpu0 (void)                                         **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Sample handler for  Cpu0 trap                               **
**                                                                           **
******************************************************************************/
#if defined __TASKING__
#pragma section code="traptab_cpu0"
#pragma align 4
#pragma protect
#elif defined __HIGHTEC__ 
#pragma section ".traptab_cpu0" ax 32
#elif defined _GHS_C_TRICORE_
#pragma ghs section text = ".traptab_cpu0"
#elif defined _DIABDATA_C_TRICORE_   
#if (_DIABDATA_C_TRICORE_ == 1U)
#pragma section CODE ".traptab_cpu0" X
#pragma align_functions 32
#endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
#endif

#ifdef __TASKING__

void traptab_cpu0 (void)
{
  __asm (".align 256");
  /* Class 0, MMU Traps: */
  __asm("j       _trap_0");/*  Jump to the trap handler */

  __asm (".align 32");
    /* Class 1, Internal Protection Traps */
  __asm("j       _trap_1");/*  Jump to the trap handler */

  __asm (".align 32");
  /* Class 2, Instruction Error Traps */
  __asm("j       _trap_2");/*  Jump to the trap handler */

  __asm (".align 32");
  /* Class 3, Context Management Traps */
  __asm("j       _trap_3");/*  Jump to the trap handler   */

  __asm (".align 32");
  /* Class 4, System Bus and Peripheral Error Traps */
  __asm("j       _trap_4");/*  Jump to the trap handler   */

  __asm (".align 32");
  /* Class 5, Assertion Traps */
  __asm("j       _trap_5");/*  Jump to the trap handler     */

  __asm (".align 32");
  /* Class 6, System Call Trap */
  __asm("j       _trap_6");/*  Jump to the trap handler     */

 __asm (".align 32");
  /* Class 7, Non Maskable Interrupt Traps */
  __asm("j       _trap_7");/*  Jump to the trap handler       */
}
#endif /* __TASKING__ */

#ifdef __HIGHTEC__
void traptab_cpu0 (void)
{
 /* ; Special trap table used during the Trap test: */

  /* ; Class 0, MMU Traps: */
  __asm (".align 8");
  __asm("j       _trap_0"); /*        ; Jump to the trap handler */

  /* ; Class 1, Internal Protection Traps: */
  __asm(".align 5");
  __asm("j       _trap_1"); /*        ; Jump to the trap handler */

  /* ; Class 2, Instruction Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_2"); /*        ; Jump to the trap handler */

  /* ; Class 3, Context Management Traps: */
  __asm(".align 5");
  __asm("j       _trap_3"); /*        ; Jump to the trap handler */

  /* ; Class 4, System Bus and Peripheral Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_4"); /*        ; Jump to the trap handler */

  /* ; Class 5, Assertion Traps: */
  __asm(".align 5");
  __asm("j       _trap_5"); /*        ; Jump to the trap handler */

  /* ; Class 6, System Call Trap: */
  __asm(".align 5");
  __asm("j       _trap_6"); /*        ; Jump to the trap handler */

  /* ; Class 7, Non Maskable Interrupt Traps: */
  __asm(".align 5");
  __asm("j       _trap_7"); /*        ; Jump to the trap handler */

}
#endif /* __HIGHTEC__ */

#ifdef _DIABDATA_C_TRICORE_
#if (_DIABDATA_C_TRICORE_ == 1U)
void traptab_cpu0 (void)
{
   /* ; Special trap table used during the Trap test: */

  /* ; Class 0, MMU Traps: */
  __asm (".align 8");
  __asm("j       _trap_0"); /*        ; Jump to the trap handler */

  /* ; Class 1, Internal Protection Traps: */
  __asm(".align 5");
  __asm("j       _trap_1"); /*        ; Jump to the trap handler */

  /* ; Class 2, Instruction Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_2"); /*        ; Jump to the trap handler */

  /* ; Class 3, Context Management Traps: */
  __asm(".align 5");
  __asm("j       _trap_3"); /*        ; Jump to the trap handler */

  /* ; Class 4, System Bus and Peripheral Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_4"); /*        ; Jump to the trap handler */

  /* ; Class 5, Assertion Traps: */
  __asm(".align 5");
  __asm("j       _trap_5"); /*        ; Jump to the trap handler */

  /* ; Class 6, System Call Trap: */
  __asm(".align 5");
  __asm("j       _trap_6"); /*        ; Jump to the trap handler */

  /* ; Class 7, Non Maskable Interrupt Traps: */
  __asm(".align 5");
  __asm("j       _trap_7"); /*        ; Jump to the trap handler */

}
#endif/* #if (_DIABDATA_C_TRICORE_ == 1U) */
#endif /* _DIABDATA_C_TRICORE_ */

#ifdef _GHS_C_TRICORE_
void traptab_cpu0 (void)
{
    __asm (".align 256");
  /* Class 0, MMU Traps: */
  __asm("j       _trap_0");/*  Jump to the trap handler */

  __asm (".align 32");
    /* Class 1, Internal Protection Traps */
  __asm("j       _trap_1");/*  Jump to the trap handler */

  __asm (".align 32");
  /* Class 2, Instruction Error Traps */
  __asm("j       _trap_2");/*  Jump to the trap handler */

  __asm (".align 32");
  /* Class 3, Context Management Traps */
  __asm("j       _trap_3");/*  Jump to the trap handler   */

  __asm (".align 32");
  /* Class 4, System Bus and Peripheral Error Traps */
  __asm("j       _trap_4");/*  Jump to the trap handler   */

  __asm (".align 32");
  /* Class 5, Assertion Traps */
  __asm("j       _trap_5");/*  Jump to the trap handler     */

  __asm (".align 32");
  /* Class 6, System Call Trap */
  __asm("j       _trap_6");/*  Jump to the trap handler     */

 __asm (".align 32");
  /* Class 7, Non Maskable Interrupt Traps */
  __asm("j       _trap_7");/*  Jump to the trap handler       */

}
#endif /* _GHS_C_TRICORE_ */


#if defined __TASKING__
    #pragma section code restore
   #pragma align 4
    #pragma endprotect
#elif defined __HIGHTEC__ 
    #pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section text = default
#elif defined _DIABDATA_C_TRICORE_   
    #if (_DIABDATA_C_TRICORE_ == 1U)
        #pragma align_functions 0
        #pragma section CODE X
    #endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
#endif

#if (MCAL_NO_OF_CORES > 1U)	
/******************************************************************************
** Syntax : void traptab_cpu1 (void)                                         **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Sample handler for  Cpu1 trap                               **
**                                                                           **
******************************************************************************/
#if defined __TASKING__
#pragma section code="traptab_cpu1"
#pragma align 4
#pragma protect
#elif defined __HIGHTEC__ 
#pragma section ".traptab_cpu1" ax 32
#elif defined _GHS_C_TRICORE_
#pragma ghs section text = ".traptab_cpu1"
#elif defined _DIABDATA_C_TRICORE_   
#if (_DIABDATA_C_TRICORE_ == 1U)
#pragma section CODE ".traptab_cpu1" X
#pragma align_functions 32
#endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
#endif

#ifdef __TASKING__

void traptab_cpu1 (void)
{
  __asm (".align 256");
  /* Class 0, MMU Traps: */
  __asm("j       _trap_0");/*  Jump to the trap handler */

  __asm (".align 32");
    /* Class 1, Internal Protection Traps */
  __asm("j       _trap_1");/*  Jump to the trap handler */

  __asm (".align 32");
  /* Class 2, Instruction Error Traps */
  __asm("j       _trap_2");/*  Jump to the trap handler */

  __asm (".align 32");
  /* Class 3, Context Management Traps */
  __asm("j       _trap_3");/*  Jump to the trap handler   */

  __asm (".align 32");
  /* Class 4, System Bus and Peripheral Error Traps */
  __asm("j       _trap_4");/*  Jump to the trap handler   */

  __asm (".align 32");
  /* Class 5, Assertion Traps */
  __asm("j       _trap_5");/*  Jump to the trap handler     */

  __asm (".align 32");
  /* Class 6, System Call Trap */
  __asm("j       _trap_6");/*  Jump to the trap handler     */

 __asm (".align 32");
  /* Class 7, Non Maskable Interrupt Traps */
  __asm("j       _trap_7");/*  Jump to the trap handler       */
}
#endif /* __TASKING__ */

#ifdef __HIGHTEC__
void traptab_cpu1 (void)
{
 /* ; Special trap table used during the Trap test: */

  /* ; Class 0, MMU Traps: */
  __asm (".align 8");
  __asm("j       _trap_0"); /*        ; Jump to the trap handler */

  /* ; Class 1, Internal Protection Traps: */
  __asm(".align 5");
  __asm("j       _trap_1"); /*        ; Jump to the trap handler */

  /* ; Class 2, Instruction Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_2"); /*        ; Jump to the trap handler */

  /* ; Class 3, Context Management Traps: */
  __asm(".align 5");
  __asm("j       _trap_3"); /*        ; Jump to the trap handler */

  /* ; Class 4, System Bus and Peripheral Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_4"); /*        ; Jump to the trap handler */

  /* ; Class 5, Assertion Traps: */
  __asm(".align 5");
  __asm("j       _trap_5"); /*        ; Jump to the trap handler */

  /* ; Class 6, System Call Trap: */
  __asm(".align 5");
  __asm("j       _trap_6"); /*        ; Jump to the trap handler */

  /* ; Class 7, Non Maskable Interrupt Traps: */
  __asm(".align 5");
  __asm("j       _trap_7"); /*        ; Jump to the trap handler */

}
#endif /* __HIGHTEC__ */

#ifdef _DIABDATA_C_TRICORE_
#if (_DIABDATA_C_TRICORE_ == 1U)
void traptab_cpu1 (void)
{
   /* ; Special trap table used during the Trap test: */

  /* ; Class 0, MMU Traps: */
  __asm (".align 8");
  __asm("j       _trap_0"); /*        ; Jump to the trap handler */

  /* ; Class 1, Internal Protection Traps: */
  __asm(".align 5");
  __asm("j       _trap_1"); /*        ; Jump to the trap handler */

  /* ; Class 2, Instruction Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_2"); /*        ; Jump to the trap handler */

  /* ; Class 3, Context Management Traps: */
  __asm(".align 5");
  __asm("j       _trap_3"); /*        ; Jump to the trap handler */

  /* ; Class 4, System Bus and Peripheral Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_4"); /*        ; Jump to the trap handler */

  /* ; Class 5, Assertion Traps: */
  __asm(".align 5");
  __asm("j       _trap_5"); /*        ; Jump to the trap handler */

  /* ; Class 6, System Call Trap: */
  __asm(".align 5");
  __asm("j       _trap_6"); /*        ; Jump to the trap handler */

  /* ; Class 7, Non Maskable Interrupt Traps: */
  __asm(".align 5");
  __asm("j       _trap_7"); /*        ; Jump to the trap handler */

}
#endif/* #if (_DIABDATA_C_TRICORE_ == 1U) */
#endif /* _DIABDATA_C_TRICORE_ */

#ifdef _GHS_C_TRICORE_
void traptab_cpu1 (void)
{
  __asm (".align 256");
  /* Class 0, MMU Traps: */
  __asm("j       _trap_0");/*  Jump to the trap handler */

  __asm (".align 32");
    /* Class 1, Internal Protection Traps */
  __asm("j       _trap_1");/*  Jump to the trap handler */

  __asm (".align 32");
  /* Class 2, Instruction Error Traps */
  __asm("j       _trap_2");/*  Jump to the trap handler */

  __asm (".align 32");
  /* Class 3, Context Management Traps */
  __asm("j       _trap_3");/*  Jump to the trap handler   */

  __asm (".align 32");
  /* Class 4, System Bus and Peripheral Error Traps */
  __asm("j       _trap_4");/*  Jump to the trap handler   */

  __asm (".align 32");
  /* Class 5, Assertion Traps */
  __asm("j       _trap_5");/*  Jump to the trap handler     */

  __asm (".align 32");
  /* Class 6, System Call Trap */
  __asm("j       _trap_6");/*  Jump to the trap handler     */

 __asm (".align 32");
  /* Class 7, Non Maskable Interrupt Traps */
  __asm("j       _trap_7");/*  Jump to the trap handler       */
}
#endif /* _GHS_C_TRICORE_ */

#if defined __TASKING__
    #pragma section code restore
   #pragma align 4
    #pragma endprotect
#elif defined __HIGHTEC__ 
    #pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section text = default
#elif defined _DIABDATA_C_TRICORE_   
    #if (_DIABDATA_C_TRICORE_ == 1U)
        #pragma align_functions 0
        #pragma section CODE X
    #endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
#endif
#endif /*#if (MCAL_NO_OF_CORES > 1U)*/

#if (MCAL_NO_OF_CORES > 2U)
/******************************************************************************
** Syntax : void traptab_cpu2 (void)                                         **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Sample handler for  Cpu2 trap                               **
**                                                                           **
******************************************************************************/
#if defined __TASKING__
#pragma section code="traptab_cpu2"
#pragma align 4
#pragma protect
#elif defined __HIGHTEC__ 
#pragma section ".traptab_cpu2" ax 32
#elif defined _GHS_C_TRICORE_
#pragma ghs section text = ".traptab_cpu2"
#elif defined _DIABDATA_C_TRICORE_   
#if (_DIABDATA_C_TRICORE_ == 1U)
#pragma section CODE ".traptab_cpu2" X
#pragma align_functions 32
#endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
#endif

#ifdef __TASKING__

void traptab_cpu2 (void)
{
  __asm (".align 256");
  /* Class 0, MMU Traps: */
  __asm("j       _trap_0");/*  Jump to the trap handler */

  __asm (".align 32");
    /* Class 1, Internal Protection Traps */
  __asm("j       _trap_1");/*  Jump to the trap handler */

  __asm (".align 32");
  /* Class 2, Instruction Error Traps */
  __asm("j       _trap_2");/*  Jump to the trap handler */

  __asm (".align 32");
  /* Class 3, Context Management Traps */
  __asm("j       _trap_3");/*  Jump to the trap handler   */

  __asm (".align 32");
  /* Class 4, System Bus and Peripheral Error Traps */
  __asm("j       _trap_4");/*  Jump to the trap handler   */

  __asm (".align 32");
  /* Class 5, Assertion Traps */
  __asm("j       _trap_5");/*  Jump to the trap handler     */

  __asm (".align 32");
  /* Class 6, System Call Trap */
  __asm("j       _trap_6");/*  Jump to the trap handler     */

 __asm (".align 32");
  /* Class 7, Non Maskable Interrupt Traps */
  __asm("j       _trap_7");/*  Jump to the trap handler       */
}
#endif /* __TASKING__ */

#ifdef __HIGHTEC__
void traptab_cpu2 (void)
{
 /* ; Special trap table used during the Trap test: */

  /* ; Class 0, MMU Traps: */
  __asm (".align 8");
  __asm("j       _trap_0"); /*        ; Jump to the trap handler */

  /* ; Class 1, Internal Protection Traps: */
  __asm(".align 5");
  __asm("j       _trap_1"); /*        ; Jump to the trap handler */

  /* ; Class 2, Instruction Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_2"); /*        ; Jump to the trap handler */

  /* ; Class 3, Context Management Traps: */
  __asm(".align 5");
  __asm("j       _trap_3"); /*        ; Jump to the trap handler */

  /* ; Class 4, System Bus and Peripheral Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_4"); /*        ; Jump to the trap handler */

  /* ; Class 5, Assertion Traps: */
  __asm(".align 5");
  __asm("j       _trap_5"); /*        ; Jump to the trap handler */

  /* ; Class 6, System Call Trap: */
  __asm(".align 5");
  __asm("j       _trap_6"); /*        ; Jump to the trap handler */

  /* ; Class 7, Non Maskable Interrupt Traps: */
  __asm(".align 5");
  __asm("j       _trap_7"); /*        ; Jump to the trap handler */

}
#endif /* __HIGHTEC__ */

#ifdef _DIABDATA_C_TRICORE_
#if (_DIABDATA_C_TRICORE_ == 1U)
void traptab_cpu2 (void)
{
   /* ; Special trap table used during the Trap test: */

  /* ; Class 0, MMU Traps: */
  __asm (".align 8");
  __asm("j       _trap_0"); /*        ; Jump to the trap handler */

  /* ; Class 1, Internal Protection Traps: */
  __asm(".align 5");
  __asm("j       _trap_1"); /*        ; Jump to the trap handler */

  /* ; Class 2, Instruction Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_2"); /*        ; Jump to the trap handler */

  /* ; Class 3, Context Management Traps: */
  __asm(".align 5");
  __asm("j       _trap_3"); /*        ; Jump to the trap handler */

  /* ; Class 4, System Bus and Peripheral Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_4"); /*        ; Jump to the trap handler */

  /* ; Class 5, Assertion Traps: */
  __asm(".align 5");
  __asm("j       _trap_5"); /*        ; Jump to the trap handler */

  /* ; Class 6, System Call Trap: */
  __asm(".align 5");
  __asm("j       _trap_6"); /*        ; Jump to the trap handler */

  /* ; Class 7, Non Maskable Interrupt Traps: */
  __asm(".align 5");
  __asm("j       _trap_7"); /*        ; Jump to the trap handler */

}
#endif/* #if (_DIABDATA_C_TRICORE_ == 1U) */
#endif /* _DIABDATA_C_TRICORE_ */

#ifdef _GHS_C_TRICORE_
void traptab_cpu2 (void)
{
  __asm (".align 256");
  /* Class 0, MMU Traps: */
  __asm("j       _trap_0");/*  Jump to the trap handler */

  __asm (".align 32");
    /* Class 1, Internal Protection Traps */
  __asm("j       _trap_1");/*  Jump to the trap handler */

  __asm (".align 32");
  /* Class 2, Instruction Error Traps */
  __asm("j       _trap_2");/*  Jump to the trap handler */

  __asm (".align 32");
  /* Class 3, Context Management Traps */
  __asm("j       _trap_3");/*  Jump to the trap handler   */

  __asm (".align 32");
  /* Class 4, System Bus and Peripheral Error Traps */
  __asm("j       _trap_4");/*  Jump to the trap handler   */

  __asm (".align 32");
  /* Class 5, Assertion Traps */
  __asm("j       _trap_5");/*  Jump to the trap handler     */

  __asm (".align 32");
  /* Class 6, System Call Trap */
  __asm("j       _trap_6");/*  Jump to the trap handler     */

 __asm (".align 32");
  /* Class 7, Non Maskable Interrupt Traps */
  __asm("j       _trap_7");/*  Jump to the trap handler       */

}
#endif /* _GHS_C_TRICORE_ */

#if defined __TASKING__
    #pragma section code restore
   #pragma align 4
    #pragma endprotect
#elif defined __HIGHTEC__ 
    #pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section text = default
#elif defined _DIABDATA_C_TRICORE_   
    #if (_DIABDATA_C_TRICORE_ == 1U)
        #pragma align_functions 0
        #pragma section CODE X
    #endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
#endif
#endif /*#if (MCAL_NO_OF_CORES > 2U)*/

#if (MCAL_NO_OF_CORES > 3U)
/******************************************************************************
** Syntax : void traptab_cpu3 (void)                                         **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Sample handler for  Cpu3 trap                               **
**                                                                           **
******************************************************************************/
#if defined __TASKING__
#pragma section code="traptab_cpu3"
#pragma align 4
#pragma protect
#elif defined __HIGHTEC__ 
#pragma section ".traptab_cpu3" ax 32
#elif defined _GHS_C_TRICORE_
#pragma ghs section text = ".traptab_cpu3"
#elif defined _DIABDATA_C_TRICORE_   
#if (_DIABDATA_C_TRICORE_ == 1U)
#pragma section CODE ".traptab_cpu3" X
#pragma align_functions 32
#endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
#endif

#ifdef __TASKING__

void traptab_cpu3 (void)
{
  __asm (".align 256");
  /* Class 0, MMU Traps: */
  __asm("j       _trap_0");/*  Jump to the trap handler */

  __asm (".align 32");
    /* Class 1, Internal Protection Traps */
  __asm("j       _trap_1");/*  Jump to the trap handler */

  __asm (".align 32");
  /* Class 2, Instruction Error Traps */
  __asm("j       _trap_2");/*  Jump to the trap handler */

  __asm (".align 32");
  /* Class 3, Context Management Traps */
  __asm("j       _trap_3");/*  Jump to the trap handler   */

  __asm (".align 32");
  /* Class 4, System Bus and Peripheral Error Traps */
  __asm("j       _trap_4");/*  Jump to the trap handler   */

  __asm (".align 32");
  /* Class 5, Assertion Traps */
  __asm("j       _trap_5");/*  Jump to the trap handler     */

  __asm (".align 32");
  /* Class 6, System Call Trap */
  __asm("j       _trap_6");/*  Jump to the trap handler     */

 __asm (".align 32");
  /* Class 7, Non Maskable Interrupt Traps */
  __asm("j       _trap_7");/*  Jump to the trap handler       */
}
#endif /* __TASKING__ */

#ifdef __HIGHTEC__
void traptab_cpu3 (void)
{
 /* ; Special trap table used during the Trap test: */

  /* ; Class 0, MMU Traps: */
  __asm (".align 8");
  __asm("j       _trap_0"); /*        ; Jump to the trap handler */

  /* ; Class 1, Internal Protection Traps: */
  __asm(".align 5");
  __asm("j       _trap_1"); /*        ; Jump to the trap handler */

  /* ; Class 2, Instruction Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_2"); /*        ; Jump to the trap handler */

  /* ; Class 3, Context Management Traps: */
  __asm(".align 5");
  __asm("j       _trap_3"); /*        ; Jump to the trap handler */

  /* ; Class 4, System Bus and Peripheral Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_4"); /*        ; Jump to the trap handler */

  /* ; Class 5, Assertion Traps: */
  __asm(".align 5");
  __asm("j       _trap_5"); /*        ; Jump to the trap handler */

  /* ; Class 6, System Call Trap: */
  __asm(".align 5");
  __asm("j       _trap_6"); /*        ; Jump to the trap handler */

  /* ; Class 7, Non Maskable Interrupt Traps: */
  __asm(".align 5");
  __asm("j       _trap_7"); /*        ; Jump to the trap handler */

}
#endif /* __HIGHTEC__ */

#ifdef _DIABDATA_C_TRICORE_
#if (_DIABDATA_C_TRICORE_ == 1U)
void traptab_cpu3 (void)
{
   /* ; Special trap table used during the Trap test: */

  /* ; Class 0, MMU Traps: */
  __asm (".align 8");
  __asm("j       _trap_0"); /*        ; Jump to the trap handler */

  /* ; Class 1, Internal Protection Traps: */
  __asm(".align 5");
  __asm("j       _trap_1"); /*        ; Jump to the trap handler */

  /* ; Class 2, Instruction Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_2"); /*        ; Jump to the trap handler */

  /* ; Class 3, Context Management Traps: */
  __asm(".align 5");
  __asm("j       _trap_3"); /*        ; Jump to the trap handler */

  /* ; Class 4, System Bus and Peripheral Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_4"); /*        ; Jump to the trap handler */

  /* ; Class 5, Assertion Traps: */
  __asm(".align 5");
  __asm("j       _trap_5"); /*        ; Jump to the trap handler */

  /* ; Class 6, System Call Trap: */
  __asm(".align 5");
  __asm("j       _trap_6"); /*        ; Jump to the trap handler */

  /* ; Class 7, Non Maskable Interrupt Traps: */
  __asm(".align 5");
  __asm("j       _trap_7"); /*        ; Jump to the trap handler */

}
#endif/* #if (_DIABDATA_C_TRICORE_ == 1U) */
#endif /* _DIABDATA_C_TRICORE_ */

#ifdef _GHS_C_TRICORE_
void traptab_cpu3 (void)
{
  __asm (".align 256");
  /* Class 0, MMU Traps: */
  __asm("j       _trap_0");/*  Jump to the trap handler */

  __asm (".align 32");
    /* Class 1, Internal Protection Traps */
  __asm("j       _trap_1");/*  Jump to the trap handler */

  __asm (".align 32");
  /* Class 2, Instruction Error Traps */
  __asm("j       _trap_2");/*  Jump to the trap handler */

  __asm (".align 32");
  /* Class 3, Context Management Traps */
  __asm("j       _trap_3");/*  Jump to the trap handler   */

  __asm (".align 32");
  /* Class 4, System Bus and Peripheral Error Traps */
  __asm("j       _trap_4");/*  Jump to the trap handler   */

  __asm (".align 32");
  /* Class 5, Assertion Traps */
  __asm("j       _trap_5");/*  Jump to the trap handler     */

  __asm (".align 32");
  /* Class 6, System Call Trap */
  __asm("j       _trap_6");/*  Jump to the trap handler     */

 __asm (".align 32");
  /* Class 7, Non Maskable Interrupt Traps */
  __asm("j       _trap_7");/*  Jump to the trap handler       */

}
#endif /* _GHS_C_TRICORE_ */

#if defined __TASKING__
    #pragma section code restore
   #pragma align 4
    #pragma endprotect
#elif defined __HIGHTEC__ 
    #pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section text = default   
#elif defined _DIABDATA_C_TRICORE_   
    #if (_DIABDATA_C_TRICORE_ == 1U)
        #pragma align_functions 0
        #pragma section CODE X
    #endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
#endif
#endif /*#if (MCAL_NO_OF_CORES > 3U)*/

#if (MCAL_NO_OF_CORES > 4U)
/******************************************************************************
** Syntax : void traptab_cpu4 (void)                                         **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Sample handler for  Cpu4 trap                               **
**                                                                           **
******************************************************************************/
#if defined __TASKING__
#pragma section code="traptab_cpu4"
#pragma align 4
#pragma protect
#elif defined __HIGHTEC__ 
#pragma section ".traptab_cpu4" ax 32
#elif defined _GHS_C_TRICORE_
#pragma ghs section text = ".traptab_cpu4"
#elif defined _DIABDATA_C_TRICORE_   
#if (_DIABDATA_C_TRICORE_ == 1U)
#pragma section CODE ".traptab_cpu4" X
#pragma align_functions 32
#endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
#endif

#ifdef __TASKING__

void traptab_cpu4 (void)
{
  __asm (".align 256");
  /* Class 0, MMU Traps: */
  __asm("j       _trap_0");/*  Jump to the trap handler */

  __asm (".align 32");
    /* Class 1, Internal Protection Traps */
  __asm("j       _trap_1");/*  Jump to the trap handler */

  __asm (".align 32");
  /* Class 2, Instruction Error Traps */
  __asm("j       _trap_2");/*  Jump to the trap handler */

  __asm (".align 32");
  /* Class 3, Context Management Traps */
  __asm("j       _trap_3");/*  Jump to the trap handler   */

  __asm (".align 32");
  /* Class 4, System Bus and Peripheral Error Traps */
  __asm("j       _trap_4");/*  Jump to the trap handler   */

  __asm (".align 32");
  /* Class 5, Assertion Traps */
  __asm("j       _trap_5");/*  Jump to the trap handler     */

  __asm (".align 32");
  /* Class 6, System Call Trap */
  __asm("j       _trap_6");/*  Jump to the trap handler     */

 __asm (".align 32");
  /* Class 7, Non Maskable Interrupt Traps */
  __asm("j       _trap_7");/*  Jump to the trap handler       */
}
#endif /* __TASKING__ */

#ifdef __HIGHTEC__
void traptab_cpu4 (void)
{
 /* ; Special trap table used during the Trap test: */

  /* ; Class 0, MMU Traps: */
  __asm (".align 8");
  __asm("j       _trap_0"); /*        ; Jump to the trap handler */

  /* ; Class 1, Internal Protection Traps: */
  __asm(".align 5");
  __asm("j       _trap_1"); /*        ; Jump to the trap handler */

  /* ; Class 2, Instruction Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_2"); /*        ; Jump to the trap handler */

  /* ; Class 3, Context Management Traps: */
  __asm(".align 5");
  __asm("j       _trap_3"); /*        ; Jump to the trap handler */

  /* ; Class 4, System Bus and Peripheral Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_4"); /*        ; Jump to the trap handler */

  /* ; Class 5, Assertion Traps: */
  __asm(".align 5");
  __asm("j       _trap_5"); /*        ; Jump to the trap handler */

  /* ; Class 6, System Call Trap: */
  __asm(".align 5");
  __asm("j       _trap_6"); /*        ; Jump to the trap handler */

  /* ; Class 7, Non Maskable Interrupt Traps: */
  __asm(".align 5");
  __asm("j       _trap_7"); /*        ; Jump to the trap handler */

}
#endif /* __HIGHTEC__ */

#ifdef _DIABDATA_C_TRICORE_
#if (_DIABDATA_C_TRICORE_ == 1U)
void traptab_cpu4 (void)
{
   /* ; Special trap table used during the Trap test: */

  /* ; Class 0, MMU Traps: */
  __asm (".align 8");
  __asm("j       _trap_0"); /*        ; Jump to the trap handler */

  /* ; Class 1, Internal Protection Traps: */
  __asm(".align 5");
  __asm("j       _trap_1"); /*        ; Jump to the trap handler */

  /* ; Class 2, Instruction Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_2"); /*        ; Jump to the trap handler */

  /* ; Class 3, Context Management Traps: */
  __asm(".align 5");
  __asm("j       _trap_3"); /*        ; Jump to the trap handler */

  /* ; Class 4, System Bus and Peripheral Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_4"); /*        ; Jump to the trap handler */

  /* ; Class 5, Assertion Traps: */
  __asm(".align 5");
  __asm("j       _trap_5"); /*        ; Jump to the trap handler */

  /* ; Class 6, System Call Trap: */
  __asm(".align 5");
  __asm("j       _trap_6"); /*        ; Jump to the trap handler */

  /* ; Class 7, Non Maskable Interrupt Traps: */
  __asm(".align 5");
  __asm("j       _trap_7"); /*        ; Jump to the trap handler */

}
#endif/* #if (_DIABDATA_C_TRICORE_ == 1U) */
#endif /* _DIABDATA_C_TRICORE_ */

#ifdef _GHS_C_TRICORE_
void traptab_cpu4 (void)
{
  __asm (".align 256");
  /* Class 0, MMU Traps: */
  __asm("j       _trap_0");/*  Jump to the trap handler */

  __asm (".align 32");
    /* Class 1, Internal Protection Traps */
  __asm("j       _trap_1");/*  Jump to the trap handler */

  __asm (".align 32");
  /* Class 2, Instruction Error Traps */
  __asm("j       _trap_2");/*  Jump to the trap handler */

  __asm (".align 32");
  /* Class 3, Context Management Traps */
  __asm("j       _trap_3");/*  Jump to the trap handler   */

  __asm (".align 32");
  /* Class 4, System Bus and Peripheral Error Traps */
  __asm("j       _trap_4");/*  Jump to the trap handler   */

  __asm (".align 32");
  /* Class 5, Assertion Traps */
  __asm("j       _trap_5");/*  Jump to the trap handler     */

  __asm (".align 32");
  /* Class 6, System Call Trap */
  __asm("j       _trap_6");/*  Jump to the trap handler     */

 __asm (".align 32");
  /* Class 7, Non Maskable Interrupt Traps */
  __asm("j       _trap_7");/*  Jump to the trap handler       */
}
#endif /* _GHS_C_TRICORE_ */

#if defined __TASKING__
    #pragma section code restore
   #pragma align 4
    #pragma endprotect
#elif defined __HIGHTEC__ 
    #pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section text = default
#elif defined _DIABDATA_C_TRICORE_   
    #if (_DIABDATA_C_TRICORE_ == 1U)
        #pragma align_functions 0
        #pragma section CODE X
    #endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
#endif
#endif /*#if (MCAL_NO_OF_CORES > 4U)*/

#if (MCAL_NO_OF_CORES > 5U)
/******************************************************************************
** Syntax : void traptab_cpu5 (void)                                         **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Sample handler for  Cpu5 trap                               **
**                                                                           **
******************************************************************************/
#if defined __TASKING__
#pragma section code="traptab_cpu5"
#pragma align 4
#pragma protect
#elif defined __HIGHTEC__ 
#pragma section ".traptab_cpu5" ax 32
#elif defined _GHS_C_TRICORE_
#pragma ghs section text = ".traptab_cpu5"
#elif defined _DIABDATA_C_TRICORE_   
#if (_DIABDATA_C_TRICORE_ == 1U)
#pragma section CODE ".traptab_cpu5" X
#pragma align_functions 32
#endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
#endif

#ifdef __TASKING__

void traptab_cpu5 (void)
{
  __asm (".align 256");
  /* Class 0, MMU Traps: */
  __asm("j       _trap_0");/*  Jump to the trap handler */

  __asm (".align 32");
    /* Class 1, Internal Protection Traps */
  __asm("j       _trap_1");/*  Jump to the trap handler */

  __asm (".align 32");
  /* Class 2, Instruction Error Traps */
  __asm("j       _trap_2");/*  Jump to the trap handler */

  __asm (".align 32");
  /* Class 3, Context Management Traps */
  __asm("j       _trap_3");/*  Jump to the trap handler   */

  __asm (".align 32");
  /* Class 4, System Bus and Peripheral Error Traps */
  __asm("j       _trap_4");/*  Jump to the trap handler   */

  __asm (".align 32");
  /* Class 5, Assertion Traps */
  __asm("j       _trap_5");/*  Jump to the trap handler     */

  __asm (".align 32");
  /* Class 6, System Call Trap */
  __asm("j       _trap_6");/*  Jump to the trap handler     */

 __asm (".align 32");
  /* Class 7, Non Maskable Interrupt Traps */
  __asm("j       _trap_7");/*  Jump to the trap handler       */
}
#endif /* __TASKING__ */

#ifdef __HIGHTEC__
void traptab_cpu5 (void)
{
 /* ; Special trap table used during the Trap test: */

  /* ; Class 0, MMU Traps: */
  __asm (".align 8");
  __asm("j       _trap_0"); /*        ; Jump to the trap handler */

  /* ; Class 1, Internal Protection Traps: */
  __asm(".align 5");
  __asm("j       _trap_1"); /*        ; Jump to the trap handler */

  /* ; Class 2, Instruction Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_2"); /*        ; Jump to the trap handler */

  /* ; Class 3, Context Management Traps: */
  __asm(".align 5");
  __asm("j       _trap_3"); /*        ; Jump to the trap handler */

  /* ; Class 4, System Bus and Peripheral Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_4"); /*        ; Jump to the trap handler */

  /* ; Class 5, Assertion Traps: */
  __asm(".align 5");
  __asm("j       _trap_5"); /*        ; Jump to the trap handler */

  /* ; Class 6, System Call Trap: */
  __asm(".align 5");
  __asm("j       _trap_6"); /*        ; Jump to the trap handler */

  /* ; Class 7, Non Maskable Interrupt Traps: */
  __asm(".align 5");
  __asm("j       _trap_7"); /*        ; Jump to the trap handler */

}
#endif /* __HIGHTEC__ */

#ifdef _DIABDATA_C_TRICORE_
#if (_DIABDATA_C_TRICORE_ == 1U)
void traptab_cpu5 (void)
{
   /* ; Special trap table used during the Trap test: */

  /* ; Class 0, MMU Traps: */
  __asm (".align 8");
  __asm("j       _trap_0"); /*        ; Jump to the trap handler */

  /* ; Class 1, Internal Protection Traps: */
  __asm(".align 5");
  __asm("j       _trap_1"); /*        ; Jump to the trap handler */

  /* ; Class 2, Instruction Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_2"); /*        ; Jump to the trap handler */

  /* ; Class 3, Context Management Traps: */
  __asm(".align 5");
  __asm("j       _trap_3"); /*        ; Jump to the trap handler */

  /* ; Class 4, System Bus and Peripheral Error Traps: */
  __asm(".align 5");
  __asm("j       _trap_4"); /*        ; Jump to the trap handler */

  /* ; Class 5, Assertion Traps: */
  __asm(".align 5");
  __asm("j       _trap_5"); /*        ; Jump to the trap handler */

  /* ; Class 6, System Call Trap: */
  __asm(".align 5");
  __asm("j       _trap_6"); /*        ; Jump to the trap handler */

  /* ; Class 7, Non Maskable Interrupt Traps: */
  __asm(".align 5");
  __asm("j       _trap_7"); /*        ; Jump to the trap handler */

}
#endif/* #if (_DIABDATA_C_TRICORE_ == 1U) */
#endif /* _DIABDATA_C_TRICORE_ */

#ifdef _GHS_C_TRICORE_
void traptab_cpu5 (void)
{
  __asm (".align 256");
  /* Class 0, MMU Traps: */
  __asm("j       _trap_0");/*  Jump to the trap handler */

  __asm (".align 32");
    /* Class 1, Internal Protection Traps */
  __asm("j       _trap_1");/*  Jump to the trap handler */

  __asm (".align 32");
  /* Class 2, Instruction Error Traps */
  __asm("j       _trap_2");/*  Jump to the trap handler */

  __asm (".align 32");
  /* Class 3, Context Management Traps */
  __asm("j       _trap_3");/*  Jump to the trap handler   */

  __asm (".align 32");
  /* Class 4, System Bus and Peripheral Error Traps */
  __asm("j       _trap_4");/*  Jump to the trap handler   */

  __asm (".align 32");
  /* Class 5, Assertion Traps */
  __asm("j       _trap_5");/*  Jump to the trap handler     */

  __asm (".align 32");
  /* Class 6, System Call Trap */
  __asm("j       _trap_6");/*  Jump to the trap handler     */

 __asm (".align 32");
  /* Class 7, Non Maskable Interrupt Traps */
  __asm("j       _trap_7");/*  Jump to the trap handler       */

}
#endif /* _GHS_C_TRICORE_ */

#if defined __TASKING__
    #pragma section code restore
   #pragma align 4
    #pragma endprotect
#elif defined __HIGHTEC__ 
    #pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section text = default
#elif defined _DIABDATA_C_TRICORE_   
    #if (_DIABDATA_C_TRICORE_ == 1U)
        #pragma align_functions 0
        #pragma section CODE X
    #endif /* #if (_DIABDATA_C_TRICORE_ == 1U) */
#endif
#endif /*#if (MCAL_NO_OF_CORES > 5U)*/

