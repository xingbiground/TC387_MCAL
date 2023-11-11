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
**  FILENAME  : Spi_Irq.c                                                     **
**                                                                            **
**  VERSION   : 3.0.0                                                         **
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
**  DESCRIPTION :  This file contains ISRs of SPI Handler driver              **
**                                                                            **
**  SPECIFICATION(S) : Specification of SPI Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : Yes                                              **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Inclusion of Platform_Types.h and Compiler.h */
#include "Std_Types.h"

/* Module header file inclusion */
#include "Spi.h"
/* MCAL driver utility functions for setting interrupt priority initialization
    and interrupt category */
#include "IFX_Os.h"
#include "Irq.h"
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
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

/******************************************************************************
** Syntax : void QSPIXERR_ISR(void)                                          **
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
** Description : Service for Error interrupt of QSPIx                        **
**                                                                           **
******************************************************************************/
/* Included to remove the GHS Warning */
#ifndef SPI_HW_QSPI5_USED
#define SPI_HW_QSPI5_USED 0x00u
#endif

/* This node is for QSPI0_ESRC */
#if ((SPI_HW_QSPI0_USED == STD_ON) && (SPI_LEVEL_DELIVERED != 0))
#if IRQ_QSPI0_ERR_TOS != IRQ_TOS_DMA
#if ((IRQ_QSPI0_ERR_PRIO > 0) || (IRQ_QSPI0_ERR_CAT == IRQ_CAT2))
#if ((IRQ_QSPI0_ERR_PRIO > 0) && (IRQ_QSPI0_ERR_CAT == IRQ_CAT1))
IFX_INTERRUPT(QSPI0ERR_ISR, 0, IRQ_QSPI0_ERR_PRIO)
#elif IRQ_QSPI0_ERR_CAT == IRQ_CAT2
ISR(QSPI0ERR_ISR)
#endif
{
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  #if (TEST_ACCESS_MODE_RT == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  /* Call QSPI0 Interrupt function */
  Spi_IsrQspiError(SPI_QSPI0_INDEX);
}
#endif
#endif
#endif

#if ((SPI_HW_QSPI1_USED == STD_ON) && (SPI_LEVEL_DELIVERED != 0))
/* This node is for QSPI1_ESRC */
#if IRQ_QSPI1_ERR_TOS != IRQ_TOS_DMA
#if ((IRQ_QSPI1_ERR_PRIO > 0) || (IRQ_QSPI1_ERR_CAT == IRQ_CAT2))
#if ((IRQ_QSPI1_ERR_PRIO > 0) && (IRQ_QSPI1_ERR_CAT == IRQ_CAT1))
IFX_INTERRUPT(QSPI1ERR_ISR, 0, IRQ_QSPI1_ERR_PRIO)
#elif IRQ_QSPI1_ERR_CAT == IRQ_CAT2
ISR(QSPI1ERR_ISR)
#endif
{
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  #if (TEST_ACCESS_MODE_RT == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  /* Call QSPI1 Interrupt function */
  Spi_IsrQspiError(SPI_QSPI1_INDEX);

}
#endif
#endif
#endif

/* This node is for QSPI2_ESRC */
#if ((SPI_HW_QSPI2_USED == STD_ON) && (SPI_LEVEL_DELIVERED != 0))
#if IRQ_QSPI2_ERR_TOS != IRQ_TOS_DMA
#if ((IRQ_QSPI2_ERR_PRIO > 0) || (IRQ_QSPI2_ERR_CAT == IRQ_CAT2))
#if ((IRQ_QSPI2_ERR_PRIO > 0) && (IRQ_QSPI2_ERR_CAT == IRQ_CAT1))
IFX_INTERRUPT(QSPI2ERR_ISR, 0, IRQ_QSPI2_ERR_PRIO)
#elif IRQ_QSPI2_ERR_CAT == IRQ_CAT2
ISR(QSPI2ERR_ISR)
#endif
{
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  #if (TEST_ACCESS_MODE_RT == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  /* Call QSPI2 Interrupt function */
  Spi_IsrQspiError(SPI_QSPI2_INDEX);

}
#endif
#endif
#endif

#if ((SPI_HW_QSPI3_USED == STD_ON) && (SPI_LEVEL_DELIVERED != 0))
/* This node is for QSPI3_ESRC */
#if IRQ_QSPI3_ERR_TOS != IRQ_TOS_DMA
#if ((IRQ_QSPI3_ERR_PRIO > 0) || (IRQ_QSPI3_ERR_CAT == IRQ_CAT2))
#if ((IRQ_QSPI3_ERR_PRIO > 0) && (IRQ_QSPI3_ERR_CAT == IRQ_CAT1))
IFX_INTERRUPT(QSPI3ERR_ISR, 0, IRQ_QSPI3_ERR_PRIO)
#elif IRQ_QSPI3_ERR_CAT == IRQ_CAT2
ISR(QSPI3ERR_ISR)
#endif
{
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  #if (TEST_ACCESS_MODE_RT == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  /* Call QSPI3 Interrupt function */
  Spi_IsrQspiError(SPI_QSPI3_INDEX);

}
#endif
#endif
#endif

#if ((defined SPI_HW_QSPI4_USED) && (SPI_HW_QSPI4_USED == STD_ON) && (SPI_LEVEL_DELIVERED != 0))
/* This node is for QSPI4_ESRC */
#if IRQ_QSPI4_ERR_TOS != IRQ_TOS_DMA
#if ((IRQ_QSPI4_ERR_PRIO > 0) || (IRQ_QSPI4_ERR_CAT == IRQ_CAT2))
#if ((IRQ_QSPI4_ERR_PRIO > 0) && (IRQ_QSPI4_ERR_CAT == IRQ_CAT1))
IFX_INTERRUPT(QSPI4ERR_ISR, 0, IRQ_QSPI4_ERR_PRIO)
#elif IRQ_QSPI4_ERR_CAT == IRQ_CAT2
ISR(QSPI4ERR_ISR)
#endif
{
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  #if (TEST_ACCESS_MODE_RT == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  /* Call QSPI4 Interrupt function */
  Spi_IsrQspiError(SPI_QSPI4_INDEX);

}
#endif
#endif
#endif

#if ((SPI_HW_QSPI5_USED == STD_ON) && (SPI_LEVEL_DELIVERED != 0))
/* This node is for QSPI5_ESRC */
#if IRQ_QSPI5_ERR_TOS != IRQ_TOS_DMA
#if ((IRQ_QSPI5_ERR_PRIO > 0) || (IRQ_QSPI5_ERR_CAT == IRQ_CAT2))
#if ((IRQ_QSPI5_ERR_PRIO > 0) && (IRQ_QSPI5_ERR_CAT == IRQ_CAT1))
IFX_INTERRUPT(QSPI5ERR_ISR, 0, IRQ_QSPI5_ERR_PRIO)
#elif IRQ_QSPI5_ERR_CAT == IRQ_CAT2
ISR(QSPI5ERR_ISR)
#endif
{
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  #if (TEST_ACCESS_MODE_RT == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  /* Call QSPI5 Interrupt function */
  Spi_IsrQspiError(SPI_QSPI5_INDEX);

}
#endif
#endif
#endif

/******************************************************************************
** Syntax : void QSPIXPT_ISR(void)                                           **
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
** Description : Service for Phase transition interrupt (PT2) used by QSPIx  **
**                                                                           **
******************************************************************************/
#if ((SPI_HW_QSPI0_USED == STD_ON) && (SPI_LEVEL_DELIVERED != 0))
#if IRQ_QSPI0_PT_TOS != IRQ_TOS_DMA
#if ((IRQ_QSPI0_PT_PRIO > 0) || (IRQ_QSPI0_PT_CAT == IRQ_CAT2))
#if ((IRQ_QSPI0_PT_PRIO > 0) && (IRQ_QSPI0_PT_CAT == IRQ_CAT1))
IFX_INTERRUPT(QSPI0PT_ISR, 0, IRQ_QSPI0_PT_PRIO)
#elif IRQ_QSPI0_PT_CAT == IRQ_CAT2
ISR(QSPI0PT_ISR)
#endif
{
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  #if (TEST_ACCESS_MODE_RT == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  /* Call QSPI0 Interrupt function */
  Spi_IsrQspiPT2(SPI_QSPI0_INDEX);
}
#endif
#endif
#endif

#if ((SPI_HW_QSPI1_USED == STD_ON) && (SPI_LEVEL_DELIVERED != 0))
#if IRQ_QSPI1_PT_TOS != IRQ_TOS_DMA
#if ((IRQ_QSPI1_PT_PRIO > 0) || (IRQ_QSPI1_PT_CAT == IRQ_CAT2))
#if ((IRQ_QSPI1_PT_PRIO > 0) && (IRQ_QSPI1_PT_CAT == IRQ_CAT1))
IFX_INTERRUPT(QSPI1PT_ISR, 0, IRQ_QSPI1_PT_PRIO)
#elif IRQ_QSPI1_PT_CAT == IRQ_CAT2
ISR(QSPI1PT_ISR)
#endif
{
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  #if (TEST_ACCESS_MODE_RT == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  /* Call QSPI1 Interrupt function */
  Spi_IsrQspiPT2(SPI_QSPI1_INDEX);
}
#endif
#endif
#endif

#if ((SPI_HW_QSPI2_USED == STD_ON) && (SPI_LEVEL_DELIVERED != 0))
#if IRQ_QSPI2_PT_TOS != IRQ_TOS_DMA
#if ((IRQ_QSPI2_PT_PRIO > 0) || (IRQ_QSPI2_PT_CAT == IRQ_CAT2))
#if ((IRQ_QSPI2_PT_PRIO > 0) && (IRQ_QSPI2_PT_CAT == IRQ_CAT1))
IFX_INTERRUPT(QSPI2PT_ISR, 0, IRQ_QSPI2_PT_PRIO)
#elif IRQ_QSPI2_PT_CAT == IRQ_CAT2
ISR(QSPI2PT_ISR)
#endif
{
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  #if (TEST_ACCESS_MODE_RT == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  /* Call QSPI2 Interrupt function */
  Spi_IsrQspiPT2(SPI_QSPI2_INDEX);
}
#endif
#endif
#endif

#if ((SPI_HW_QSPI3_USED == STD_ON) && (SPI_LEVEL_DELIVERED != 0))
#if IRQ_QSPI3_PT_TOS != IRQ_TOS_DMA
#if ((IRQ_QSPI3_PT_PRIO > 0) || (IRQ_QSPI3_PT_CAT == IRQ_CAT2))
#if ((IRQ_QSPI3_PT_PRIO > 0) && (IRQ_QSPI3_PT_CAT == IRQ_CAT1))
IFX_INTERRUPT(QSPI3PT_ISR, 0, IRQ_QSPI3_PT_PRIO)
#elif IRQ_QSPI3_PT_CAT == IRQ_CAT2
ISR(QSPI3PT_ISR)
#endif
{
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  #if (TEST_ACCESS_MODE_RT == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  /* Call QSPI3 Interrupt function */
  Spi_IsrQspiPT2(SPI_QSPI3_INDEX);
}
#endif
#endif
#endif

#if ((defined SPI_HW_QSPI4_USED) && (SPI_HW_QSPI4_USED == STD_ON) && (SPI_LEVEL_DELIVERED != 0))
#if IRQ_QSPI4_PT_TOS != IRQ_TOS_DMA
#if ((IRQ_QSPI4_PT_PRIO > 0) || (IRQ_QSPI4_PT_CAT == IRQ_CAT2))
#if ((IRQ_QSPI4_PT_PRIO > 0) && (IRQ_QSPI4_PT_CAT == IRQ_CAT1))
IFX_INTERRUPT(QSPI4PT_ISR, 0, IRQ_QSPI4_PT_PRIO)
#elif IRQ_QSPI4_PT_CAT == IRQ_CAT2
ISR(QSPI4PT_ISR)
#endif
{
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  #if (TEST_ACCESS_MODE_RT == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  /* Call QSPI4 Interrupt function */
  Spi_IsrQspiPT2(SPI_QSPI4_INDEX);
}
#endif
#endif
#endif

#if ((SPI_HW_QSPI5_USED == STD_ON) && (SPI_LEVEL_DELIVERED != 0))
#if IRQ_QSPI5_PT_TOS != IRQ_TOS_DMA
#if ((IRQ_QSPI5_PT_PRIO > 0) || (IRQ_QSPI5_PT_CAT == IRQ_CAT2))
#if ((IRQ_QSPI5_PT_PRIO > 0) && (IRQ_QSPI5_PT_CAT == IRQ_CAT1))
IFX_INTERRUPT(QSPI5PT_ISR, 0, IRQ_QSPI5_PT_PRIO)
#elif IRQ_QSPI5_PT_CAT == IRQ_CAT2
ISR(QSPI5PT_ISR)
#endif
{
  ENABLE();
  #ifdef  APP_SW
  #if (APP_SW == TEST_APP)
  #if (TEST_ACCESS_MODE_RT == TEST_MCAL_USER1)
  Mcal_SetModetoUser();
  #endif
  #endif
  #endif
  /* Call QSPI5 Interrupt function */
  Spi_IsrQspiPT2(SPI_QSPI5_INDEX);
}
#endif
#endif
#endif
