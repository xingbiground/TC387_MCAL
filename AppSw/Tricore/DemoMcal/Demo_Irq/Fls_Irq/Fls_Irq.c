/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2021)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Fls_Irq.c                                                     **
**                                                                            **
**  VERSION   : 2.0.0                                                         **
**                                                                            **
**  DATE      : 2021-11-08                                                    **
**                                                                            **
**  VARIANT   : Post-Build                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION : This file contains the interrupt for the FLS Module.        **
**                                                                            **
**  SPECIFICATION(S) : Specification of FLS Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : Yes                                              **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Irq.h"
/* Own header file, this includes own configuration file also */
#include "Fls_17_Dmu.h"
#include "IFX_Os.h"
/* Inclusion of Platform_Types.h and Compiler.h */
#include "Std_Types.h"

#ifdef  APP_SW
#if(APP_SW == TEST_APP)
 #include "Test_Main.h"
#endif
#endif

/*******************************************************************************
**                      Imported Compiler Switch Checks                       **
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
**                      Private Function Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/

#define IRQ_START_SEC_CODE_QM_GLOBAL
#include "Irq_MemMap.h"
#if (IRQ_DMU_EXIST == STD_ON)
/*******************************************************************************
** Syntax:           void DMU0HOST_ISR(void)                                  **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Non-reentrant                                            **
**                                                                            **
** Parameters (in):  none                                                     **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
** Description :     This is the Interrput Service Routine for DMU0 Host      **
*******************************************************************************/
#if IRQ_DMU_HOST_TOS != IRQ_TOS_DMA
#if((IRQ_DMU_HOST_PRIO > 0) || (IRQ_DMU_HOST_CAT == IRQ_CAT2))
#if((IRQ_DMU_HOST_PRIO > 0) && (IRQ_DMU_HOST_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMUHOST_ISR, 0, IRQ_DMU_HOST_PRIO)
#elif IRQ_DMU_HOST_CAT == IRQ_CAT2
ISR(DMUHOST_ISR)
#endif
/* Enable Global Interrupts */
{
  #if (IRQ_DMU_HOST_CAT == IRQ_CAT1)
  ENABLE();
  #endif
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
  #if (TEST_ACCESS_MODE_RT == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif

  #if( FLS_17_DMU_USE_INTERRUPTS == STD_ON)
  /* Call to Flash Interrupt funtion */
  Fls_17_Dmu_Isr();
  #endif
}
#endif
#endif
/*******************************************************************************
** Syntax:           void DMU0FSI_ISR(void)                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Non-reentrant                                            **
**                                                                            **
** Parameters (in):  none                                                     **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
** Description :     This is the Interrput Service Routine for DMU0 FSI       **
*******************************************************************************/
#if IRQ_DMU_FSI_TOS != IRQ_TOS_DMA
#if((IRQ_DMU_FSI_PRIO > 0) || (IRQ_DMU_FSI_CAT == IRQ_CAT2))
#if((IRQ_DMU_FSI_PRIO > 0) && (IRQ_DMU_FSI_CAT == IRQ_CAT1))
IFX_INTERRUPT(DMUFSI_ISR, 0, IRQ_DMU_FSI_PRIO)
#elif IRQ_DMU_FSI_CAT == IRQ_CAT2
ISR(DMUFSI_ISR)
#endif
{
  /* Enable Global Interrupts */
  #if (IRQ_DMU_FSI_CAT == IRQ_CAT1)
  ENABLE();
  #endif
}
#endif
#endif
#endif/*#if (IRQ_DMU_EXIST == STD_ON)*/
#define IRQ_STOP_SEC_CODE_QM_GLOBAL
#include "Irq_MemMap.h"
