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
**  FILENAME  : Can_17_McmCan_Irq.c                                           **
**                                                                            **
**  VERSION   : 7.0.0                                                         **
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
**  DESCRIPTION : This file contains the interrupt frames for the CAN Module. **
**                                                                            **
**  SPECIFICATION(S) : Specification of CAN Driver, AUTOSAR Release 4.2.2     **
**                                                              and 4.4.0     **
**  MAY BE CHANGED BY USER : Yes                                              **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Module header file inclusion */
#include "Can_17_McmCan.h"
/* MCAL driver utility functions for setting interrupt priority initialization
    and interrupt category */
#include "IFX_Os.h"
#include "Irq.h"
#ifdef  APP_SW
#if(APP_SW == TEST_APP)
  #include "Test_Main.h"
#endif
#endif
/*******************************************************************************
**                      Private Macros Definitions                            **
*******************************************************************************/

/* CONTROLLER 0 Configuration ID*/
#define CAN_17_MCMCAN_HWMCMCONTROLLER0_ID                                 (0U)

/* CONTROLLER 1 Configuration ID*/
#define CAN_17_MCMCAN_HWMCMCONTROLLER1_ID                                 (1U)

/* CONTROLLER 2 Configuration ID*/
#define CAN_17_MCMCAN_HWMCMCONTROLLER2_ID                                 (2U)

/* CONTROLLER 3 Configuration ID*/
#define CAN_17_MCMCAN_HWMCMCONTROLLER3_ID                                 (3U)

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

#if (IRQ_CAN0_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void CAN0SR0_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data Reception through Dedicated buffer  **
**                                                                           **
******************************************************************************/
#if((IRQ_CAN0_SR0_PRIO > 0) || (IRQ_CAN0_SR0_CAT == IRQ_CAT2))
#if((IRQ_CAN0_SR0_PRIO > 0) && (IRQ_CAN0_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN0SR0_ISR, 0, IRQ_CAN0_SR0_PRIO)
#elif (IRQ_CAN0_SR0_CAT == IRQ_CAT2)
ISR(CAN0SR0_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif

#if ((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx Interrupt function for dedicated buffer */
  Can_17_McmCan_IsrReceiveHandler(CAN_17_MCMCAN_HWMCMKERNEL0_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER0_ID);
#endif
}
#endif

/******************************************************************************
** Syntax :          void CAN0SR1_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service for the transmission completion new entry event **
**                   on TX FIFO Event                                        **
******************************************************************************/
#if((IRQ_CAN0_SR1_PRIO > 0) || (IRQ_CAN0_SR1_CAT == IRQ_CAT2))
#if((IRQ_CAN0_SR1_PRIO > 0) && (IRQ_CAN0_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN0SR1_ISR, 0, IRQ_CAN0_SR1_PRIO)
#elif (IRQ_CAN0_SR1_CAT == IRQ_CAT2)
ISR(CAN0SR1_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_TX_INTERRUPT_PROCESSING == STD_ON) ||(CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Tx Interrupt function*/
  Can_17_McmCan_IsrTransmitHandler(CAN_17_MCMCAN_HWMCMKERNEL0_ID, \
                                                      CAN_17_MCMCAN_HWMCMCONTROLLER0_ID);
#endif
}
#endif

/******************************************************************************
** Syntax :          void CAN0SR2_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN controller with in Bus Off mode          **
**                                                                           **
******************************************************************************/
#if((IRQ_CAN0_SR2_PRIO > 0) || (IRQ_CAN0_SR2_CAT == IRQ_CAT2))
#if((IRQ_CAN0_SR2_PRIO > 0) && (IRQ_CAN0_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN0SR2_ISR, 0, IRQ_CAN0_SR2_PRIO)
#elif (IRQ_CAN0_SR2_CAT == IRQ_CAT2)
ISR(CAN0SR2_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if(CAN_17_MCMCAN_BO_INTERRUPT_PROCESSING == STD_ON)
  /* Call CAN Bus off hanlder Interrupt function*/
  Can_17_McmCan_IsrBusOffHandler(CAN_17_MCMCAN_HWMCMKERNEL0_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER0_ID);
#endif
}
#endif

/******************************************************************************
** Syntax :          void CAN0SR3_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data reception through RXFIFO0 or        **
**                   RXFIFO1                                                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if((IRQ_CAN0_SR3_PRIO > 0) || (IRQ_CAN0_SR3_CAT == IRQ_CAT2))
#if((IRQ_CAN0_SR3_PRIO > 0) && (IRQ_CAN0_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN0SR3_ISR, 0, IRQ_CAN0_SR3_PRIO)
#elif (IRQ_CAN0_SR3_CAT == IRQ_CAT2)
ISR(CAN0SR3_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif

#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx FIFO Handler Interrupt function*/
  Can_17_McmCan_IsrRxFIFOHandler(CAN_17_MCMCAN_HWMCMKERNEL0_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER0_ID);
#endif
}
#endif

/******************************************************************************
** Syntax :          void CAN0SR4_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data Reception through Dedicated buffer  **
**                                                                           **
******************************************************************************/

#if((IRQ_CAN0_SR4_PRIO > 0) || (IRQ_CAN0_SR4_CAT == IRQ_CAT2))
#if((IRQ_CAN0_SR4_PRIO > 0) && (IRQ_CAN0_SR4_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN0SR4_ISR, 0, IRQ_CAN0_SR4_PRIO)
#elif (IRQ_CAN0_SR4_CAT == IRQ_CAT2)
ISR(CAN0SR4_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if ((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx Interrupt function for dedicated buffer */
  Can_17_McmCan_IsrReceiveHandler(CAN_17_MCMCAN_HWMCMKERNEL0_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER1_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN0SR5_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service for the transmission completion new entry event **
**                   on TX FIFO Event                                        **
******************************************************************************/
#if((IRQ_CAN0_SR5_PRIO > 0) || (IRQ_CAN0_SR5_CAT == IRQ_CAT2))
#if((IRQ_CAN0_SR5_PRIO > 0) && (IRQ_CAN0_SR5_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN0SR5_ISR, 0, IRQ_CAN0_SR5_PRIO)
#elif (IRQ_CAN0_SR5_CAT == IRQ_CAT2)
ISR(CAN0SR5_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_TX_INTERRUPT_PROCESSING == STD_ON) ||(CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Tx Interrupt function*/
  Can_17_McmCan_IsrTransmitHandler(CAN_17_MCMCAN_HWMCMKERNEL0_ID, \
                                                      CAN_17_MCMCAN_HWMCMCONTROLLER1_ID);
#endif

}
#endif


/******************************************************************************
** Syntax :          void CAN0SR6_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN controller with in Bus Off mode          **
**                                                                           **
******************************************************************************/

#if((IRQ_CAN0_SR6_PRIO > 0) || (IRQ_CAN0_SR6_CAT == IRQ_CAT2))
#if((IRQ_CAN0_SR6_PRIO > 0) && (IRQ_CAN0_SR6_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN0SR6_ISR, 0, IRQ_CAN0_SR6_PRIO)
#elif (IRQ_CAN0_SR6_CAT == IRQ_CAT2)
ISR(CAN0SR6_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if(CAN_17_MCMCAN_BO_INTERRUPT_PROCESSING == STD_ON)
  /* Call CAN Bus off hanlder Interrupt function*/
  Can_17_McmCan_IsrBusOffHandler(CAN_17_MCMCAN_HWMCMKERNEL0_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER1_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN0SR7_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data reception through RXFIFO0 or        **
**                   RXFIFO1                                                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/

#if((IRQ_CAN0_SR7_PRIO > 0) || (IRQ_CAN0_SR7_CAT == IRQ_CAT2))
#if((IRQ_CAN0_SR7_PRIO > 0) && (IRQ_CAN0_SR7_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN0SR7_ISR, 0, IRQ_CAN0_SR7_PRIO)
#elif (IRQ_CAN0_SR7_CAT == IRQ_CAT2)
ISR(CAN0SR7_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif

#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx FIFO Handler Interrupt function*/
  Can_17_McmCan_IsrRxFIFOHandler(CAN_17_MCMCAN_HWMCMKERNEL0_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER1_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN0SR8_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data Reception through Dedicated buffer  **
**                                                                           **
******************************************************************************/

#if((IRQ_CAN0_SR8_PRIO > 0) || (IRQ_CAN0_SR8_CAT == IRQ_CAT2))
#if((IRQ_CAN0_SR8_PRIO > 0) && (IRQ_CAN0_SR8_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN0SR8_ISR, 0, IRQ_CAN0_SR8_PRIO)
#elif (IRQ_CAN0_SR8_CAT == IRQ_CAT2)
ISR(CAN0SR8_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if ((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx Interrupt function for dedicated buffer */
  Can_17_McmCan_IsrReceiveHandler(CAN_17_MCMCAN_HWMCMKERNEL0_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER2_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN0SR9_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service for the transmission completion new entry event **
**                   on TX FIFO Event                                        **
******************************************************************************/
#if((IRQ_CAN0_SR9_PRIO > 0) || (IRQ_CAN0_SR9_CAT == IRQ_CAT2))
#if((IRQ_CAN0_SR9_PRIO > 0) && (IRQ_CAN0_SR9_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN0SR9_ISR, 0, IRQ_CAN0_SR9_PRIO)
#elif (IRQ_CAN0_SR9_CAT == IRQ_CAT2)
ISR(CAN0SR9_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_TX_INTERRUPT_PROCESSING == STD_ON) ||(CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Tx Interrupt function*/
  Can_17_McmCan_IsrTransmitHandler(CAN_17_MCMCAN_HWMCMKERNEL0_ID, \
                                                      CAN_17_MCMCAN_HWMCMCONTROLLER2_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN0SR10_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN controller with in Bus Off mode          **
**                                                                           **
******************************************************************************/

#if((IRQ_CAN0_SR10_PRIO > 0) || (IRQ_CAN0_SR10_CAT == IRQ_CAT2))
#if((IRQ_CAN0_SR10_PRIO > 0) && (IRQ_CAN0_SR10_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN0SR10_ISR, 0, IRQ_CAN0_SR10_PRIO)
#elif (IRQ_CAN0_SR10_CAT == IRQ_CAT2)
ISR(CAN0SR10_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if(CAN_17_MCMCAN_BO_INTERRUPT_PROCESSING == STD_ON)
  /* Call CAN Bus off hanlder Interrupt function*/
  Can_17_McmCan_IsrBusOffHandler(CAN_17_MCMCAN_HWMCMKERNEL0_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER2_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN0SR11_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data reception through RXFIFO0 or        **
**                   RXFIFO1                                                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if((IRQ_CAN0_SR11_PRIO > 0) || (IRQ_CAN0_SR11_CAT == IRQ_CAT2))
#if((IRQ_CAN0_SR11_PRIO > 0) && (IRQ_CAN0_SR11_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN0SR11_ISR, 0, IRQ_CAN0_SR11_PRIO)
#elif (IRQ_CAN0_SR11_CAT == IRQ_CAT2)
ISR(CAN0SR11_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif

#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx FIFO Handler Interrupt function*/
  Can_17_McmCan_IsrRxFIFOHandler(CAN_17_MCMCAN_HWMCMKERNEL0_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER2_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN0SR12_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data Reception through Dedicated buffer  **
**                                                                           **
******************************************************************************/
#if((IRQ_CAN0_SR12_PRIO > 0) || (IRQ_CAN0_SR12_CAT == IRQ_CAT2))
#if((IRQ_CAN0_SR12_PRIO > 0) && (IRQ_CAN0_SR12_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN0SR12_ISR, 0, IRQ_CAN0_SR12_PRIO)
#elif (IRQ_CAN0_SR12_CAT == IRQ_CAT2)
ISR(CAN0SR12_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx Interrupt function for dedicated buffer */
  Can_17_McmCan_IsrReceiveHandler(CAN_17_MCMCAN_HWMCMKERNEL0_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER3_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN0SR13_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service for the transmission completion new entry event **
**                   on TX FIFO Event                                        **
******************************************************************************/
#if((IRQ_CAN0_SR13_PRIO > 0) || (IRQ_CAN0_SR13_CAT == IRQ_CAT2))
#if((IRQ_CAN0_SR13_PRIO > 0) && (IRQ_CAN0_SR13_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN0SR13_ISR, 0, IRQ_CAN0_SR13_PRIO)
#elif (IRQ_CAN0_SR13_CAT == IRQ_CAT2)
ISR(CAN0SR13_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_TX_INTERRUPT_PROCESSING == STD_ON) ||(CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Tx Interrupt function*/
  Can_17_McmCan_IsrTransmitHandler(CAN_17_MCMCAN_HWMCMKERNEL0_ID, \
                                                      CAN_17_MCMCAN_HWMCMCONTROLLER3_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN0SR14_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN controller with in Bus Off mode          **
**                                                                           **
******************************************************************************/

#if((IRQ_CAN0_SR14_PRIO > 0) || (IRQ_CAN0_SR14_CAT == IRQ_CAT2))
#if((IRQ_CAN0_SR14_PRIO > 0) && (IRQ_CAN0_SR14_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN0SR14_ISR, 0, IRQ_CAN0_SR14_PRIO)
#elif (IRQ_CAN0_SR14_CAT == IRQ_CAT2)
ISR(CAN0SR14_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if(CAN_17_MCMCAN_BO_INTERRUPT_PROCESSING == STD_ON)
  /* Call CAN Bus off hanlder Interrupt function*/
  Can_17_McmCan_IsrBusOffHandler(CAN_17_MCMCAN_HWMCMKERNEL0_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER3_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN0SR15_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data reception through RXFIFO0 or        **
**                   RXFIFO1                                                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if((IRQ_CAN0_SR15_PRIO > 0) || (IRQ_CAN0_SR15_CAT == IRQ_CAT2))
#if((IRQ_CAN0_SR15_PRIO > 0) && (IRQ_CAN0_SR15_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN0SR15_ISR, 0, IRQ_CAN0_SR15_PRIO)
#elif (IRQ_CAN0_SR15_CAT == IRQ_CAT2)
ISR(CAN0SR15_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif

#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx FIFO Handler Interrupt function*/
  Can_17_McmCan_IsrRxFIFOHandler(CAN_17_MCMCAN_HWMCMKERNEL0_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER3_ID);
#endif
}
#endif
#endif

#if (IRQ_CAN1_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void CAN1SR0_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data Reception through Dedicated buffer  **
**                                                                           **
******************************************************************************/
#if((IRQ_CAN1_SR0_PRIO > 0) || (IRQ_CAN1_SR0_CAT == IRQ_CAT2))
#if((IRQ_CAN1_SR0_PRIO > 0) && (IRQ_CAN1_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN1SR0_ISR, 0, IRQ_CAN1_SR0_PRIO)
#elif (IRQ_CAN1_SR0_CAT == IRQ_CAT2)
ISR(CAN1SR0_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx Interrupt function for dedicated buffer */
  Can_17_McmCan_IsrReceiveHandler(CAN_17_MCMCAN_HWMCMKERNEL1_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER0_ID);
#endif
}
#endif

/******************************************************************************
** Syntax :          void CAN1SR1_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service for the transmission completion new entry event **
**                   on TX FIFO Event                                        **
******************************************************************************/
#if((IRQ_CAN1_SR1_PRIO > 0) || (IRQ_CAN1_SR1_CAT == IRQ_CAT2))
#if((IRQ_CAN1_SR1_PRIO > 0) && (IRQ_CAN1_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN1SR1_ISR, 0, IRQ_CAN1_SR1_PRIO)
#elif (IRQ_CAN1_SR1_CAT == IRQ_CAT2)
ISR(CAN1SR1_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_TX_INTERRUPT_PROCESSING == STD_ON) ||(CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Tx Interrupt function*/
  Can_17_McmCan_IsrTransmitHandler(CAN_17_MCMCAN_HWMCMKERNEL1_ID, \
                                                      CAN_17_MCMCAN_HWMCMCONTROLLER0_ID);
#endif
}
#endif

/******************************************************************************
** Syntax :          void CAN1SR2_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN controller with in Bus Off mode          **
**                                                                           **
******************************************************************************/
#if((IRQ_CAN1_SR2_PRIO > 0) || (IRQ_CAN1_SR2_CAT == IRQ_CAT2))
#if((IRQ_CAN1_SR2_PRIO > 0) && (IRQ_CAN1_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN1SR2_ISR, 0, IRQ_CAN1_SR2_PRIO)
#elif (IRQ_CAN1_SR2_CAT == IRQ_CAT2)
ISR(CAN1SR2_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if(CAN_17_MCMCAN_BO_INTERRUPT_PROCESSING == STD_ON)
  /* Call CAN Bus off hanlder Interrupt function*/
  Can_17_McmCan_IsrBusOffHandler(CAN_17_MCMCAN_HWMCMKERNEL1_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER0_ID);
#endif
}
#endif

/******************************************************************************
** Syntax :          void CAN1SR3_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data reception through RXFIFO0 or        **
**                   RXFIFO1                                                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if((IRQ_CAN1_SR3_PRIO > 0) || (IRQ_CAN1_SR3_CAT == IRQ_CAT2))
#if((IRQ_CAN1_SR3_PRIO > 0) && (IRQ_CAN1_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN1SR3_ISR, 0, IRQ_CAN1_SR3_PRIO)
#elif (IRQ_CAN1_SR3_CAT == IRQ_CAT2)
ISR(CAN1SR3_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif

#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx FIFO Handler Interrupt function*/
  Can_17_McmCan_IsrRxFIFOHandler(CAN_17_MCMCAN_HWMCMKERNEL1_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER0_ID);
#endif
}
#endif

/******************************************************************************
** Syntax :          void CAN1SR4_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data Reception through Dedicated buffer  **
**                                                                           **
******************************************************************************/
#if((IRQ_CAN1_SR4_PRIO > 0) || (IRQ_CAN1_SR4_CAT == IRQ_CAT2))
#if((IRQ_CAN1_SR4_PRIO > 0) && (IRQ_CAN1_SR4_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN1SR4_ISR, 0, IRQ_CAN1_SR4_PRIO)
#elif (IRQ_CAN1_SR4_CAT == IRQ_CAT2)
ISR(CAN1SR4_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx Interrupt function for dedicated buffer */
  Can_17_McmCan_IsrReceiveHandler(CAN_17_MCMCAN_HWMCMKERNEL1_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER1_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN1SR5_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service for the transmission completion new entry event **
**                   on TX FIFO Event                                        **
******************************************************************************/
#if((IRQ_CAN1_SR5_PRIO > 0) || (IRQ_CAN1_SR5_CAT == IRQ_CAT2))
#if((IRQ_CAN1_SR5_PRIO > 0) && (IRQ_CAN1_SR5_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN1SR5_ISR, 0, IRQ_CAN1_SR5_PRIO)
#elif (IRQ_CAN1_SR5_CAT == IRQ_CAT2)
ISR(CAN1SR5_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_TX_INTERRUPT_PROCESSING == STD_ON) ||(CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Tx Interrupt function*/
  Can_17_McmCan_IsrTransmitHandler(CAN_17_MCMCAN_HWMCMKERNEL1_ID, \
                                                      CAN_17_MCMCAN_HWMCMCONTROLLER1_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN1SR6_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN controller with in Bus Off mode          **
**                                                                           **
******************************************************************************/

#if((IRQ_CAN1_SR6_PRIO > 0) || (IRQ_CAN1_SR6_CAT == IRQ_CAT2))
#if((IRQ_CAN1_SR6_PRIO > 0) && (IRQ_CAN1_SR6_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN1SR6_ISR, 0, IRQ_CAN1_SR6_PRIO)
#elif (IRQ_CAN1_SR6_CAT == IRQ_CAT2)
ISR(CAN1SR6_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if(CAN_17_MCMCAN_BO_INTERRUPT_PROCESSING == STD_ON)
  /* Call CAN Bus off hanlder Interrupt function*/
  Can_17_McmCan_IsrBusOffHandler(CAN_17_MCMCAN_HWMCMKERNEL1_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER1_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN1SR7_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data reception through RXFIFO0 or        **
**                   RXFIFO1                                                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if((IRQ_CAN1_SR7_PRIO > 0) || (IRQ_CAN1_SR7_CAT == IRQ_CAT2))
#if((IRQ_CAN1_SR7_PRIO > 0) && (IRQ_CAN1_SR7_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN1SR7_ISR, 0, IRQ_CAN1_SR7_PRIO)
#elif (IRQ_CAN1_SR7_CAT == IRQ_CAT2)
ISR(CAN1SR7_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif

#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx FIFO Handler Interrupt function*/
  Can_17_McmCan_IsrRxFIFOHandler(CAN_17_MCMCAN_HWMCMKERNEL1_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER1_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN1SR8_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data Reception through Dedicated buffer  **
**                                                                           **
******************************************************************************/

#if((IRQ_CAN1_SR8_PRIO > 0) || (IRQ_CAN1_SR8_CAT == IRQ_CAT2))
#if((IRQ_CAN1_SR8_PRIO > 0) && (IRQ_CAN1_SR8_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN1SR8_ISR, 0, IRQ_CAN1_SR8_PRIO)
#elif (IRQ_CAN1_SR8_CAT == IRQ_CAT2)
ISR(CAN1SR8_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx Interrupt function for dedicated buffer */
  Can_17_McmCan_IsrReceiveHandler(CAN_17_MCMCAN_HWMCMKERNEL1_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER2_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN1SR9_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service for the transmission completion new entry event **
**                   on TX FIFO Event                                        **
******************************************************************************/
#if((IRQ_CAN1_SR9_PRIO > 0) || (IRQ_CAN1_SR9_CAT == IRQ_CAT2))
#if((IRQ_CAN1_SR9_PRIO > 0) && (IRQ_CAN1_SR9_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN1SR9_ISR, 0, IRQ_CAN1_SR9_PRIO)
#elif (IRQ_CAN1_SR9_CAT == IRQ_CAT2)
ISR(CAN1SR9_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_TX_INTERRUPT_PROCESSING == STD_ON) ||(CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Tx Interrupt function*/
  Can_17_McmCan_IsrTransmitHandler(CAN_17_MCMCAN_HWMCMKERNEL1_ID, \
                                                      CAN_17_MCMCAN_HWMCMCONTROLLER2_ID);
#endif
}
#endif



/******************************************************************************
** Syntax :          void CAN1SR10_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN controller with in Bus Off mode          **
**                                                                           **
******************************************************************************/

#if((IRQ_CAN1_SR10_PRIO > 0) || (IRQ_CAN1_SR10_CAT == IRQ_CAT2))
#if((IRQ_CAN1_SR10_PRIO > 0) && (IRQ_CAN1_SR10_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN1SR10_ISR, 0, IRQ_CAN1_SR10_PRIO)
#elif (IRQ_CAN1_SR10_CAT == IRQ_CAT2)
ISR(CAN1SR10_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if(CAN_17_MCMCAN_BO_INTERRUPT_PROCESSING == STD_ON)
  /* Call CAN Bus off hanlder Interrupt function*/
  Can_17_McmCan_IsrBusOffHandler(CAN_17_MCMCAN_HWMCMKERNEL1_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER2_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN1SR11_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data reception through RXFIFO0 or        **
**                   RXFIFO1                                                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if((IRQ_CAN1_SR11_PRIO > 0) || (IRQ_CAN1_SR11_CAT == IRQ_CAT2))
#if((IRQ_CAN1_SR11_PRIO > 0) && (IRQ_CAN1_SR11_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN1SR11_ISR, 0, IRQ_CAN1_SR11_PRIO)
#elif (IRQ_CAN1_SR11_CAT == IRQ_CAT2)
ISR(CAN1SR11_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif

#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx FIFO Handler Interrupt function*/
  Can_17_McmCan_IsrRxFIFOHandler(CAN_17_MCMCAN_HWMCMKERNEL1_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER2_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN1SR12_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data Reception through Dedicated buffer  **
**                                                                           **
******************************************************************************/

#if((IRQ_CAN1_SR12_PRIO > 0) || (IRQ_CAN1_SR12_CAT == IRQ_CAT2))
#if((IRQ_CAN1_SR12_PRIO > 0) && (IRQ_CAN1_SR12_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN1SR12_ISR, 0, IRQ_CAN1_SR12_PRIO)
#elif (IRQ_CAN1_SR12_CAT == IRQ_CAT2)
ISR(CAN1SR12_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx Interrupt function for dedicated buffer */
  Can_17_McmCan_IsrReceiveHandler(CAN_17_MCMCAN_HWMCMKERNEL1_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER3_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN1SR13_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service for the transmission completion new entry event **
**                   on TX FIFO Event                                        **
******************************************************************************/
#if((IRQ_CAN1_SR13_PRIO > 0) || (IRQ_CAN1_SR13_CAT == IRQ_CAT2))
#if((IRQ_CAN1_SR13_PRIO > 0) && (IRQ_CAN1_SR13_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN1SR13_ISR, 0, IRQ_CAN1_SR13_PRIO)
#elif (IRQ_CAN1_SR13_CAT == IRQ_CAT2)
ISR(CAN1SR13_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_TX_INTERRUPT_PROCESSING == STD_ON) ||(CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Tx Interrupt function*/
  Can_17_McmCan_IsrTransmitHandler(CAN_17_MCMCAN_HWMCMKERNEL1_ID, \
                                                      CAN_17_MCMCAN_HWMCMCONTROLLER3_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN1SR14_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN controller with in Bus Off mode          **
**                                                                           **
******************************************************************************/

#if((IRQ_CAN1_SR14_PRIO > 0) || (IRQ_CAN1_SR14_CAT == IRQ_CAT2))
#if((IRQ_CAN1_SR14_PRIO > 0) && (IRQ_CAN1_SR14_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN1SR14_ISR, 0, IRQ_CAN1_SR14_PRIO)
#elif (IRQ_CAN1_SR14_CAT == IRQ_CAT2)
ISR(CAN1SR14_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if(CAN_17_MCMCAN_BO_INTERRUPT_PROCESSING == STD_ON)
  /* Call CAN Bus off hanlder Interrupt function*/
  Can_17_McmCan_IsrBusOffHandler(CAN_17_MCMCAN_HWMCMKERNEL1_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER3_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN1SR15_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data reception through RXFIFO0 or        **
**                   RXFIFO1                                                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if((IRQ_CAN1_SR15_PRIO > 0) || (IRQ_CAN1_SR15_CAT == IRQ_CAT2))
#if((IRQ_CAN1_SR15_PRIO > 0) && (IRQ_CAN1_SR15_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN1SR15_ISR, 0, IRQ_CAN1_SR15_PRIO)
#elif (IRQ_CAN1_SR15_CAT == IRQ_CAT2)
ISR(CAN1SR15_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif

#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx FIFO Handler Interrupt function*/
  Can_17_McmCan_IsrRxFIFOHandler(CAN_17_MCMCAN_HWMCMKERNEL1_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER3_ID);
#endif
}
#endif

#endif

#if (IRQ_CAN2_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void CAN2SR0_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data Reception through Dedicated buffer  **
**                                                                           **
******************************************************************************/
#if((IRQ_CAN2_SR0_PRIO > 0) || (IRQ_CAN2_SR0_CAT == IRQ_CAT2))
#if((IRQ_CAN2_SR0_PRIO > 0) && (IRQ_CAN2_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN2SR0_ISR, 0, IRQ_CAN2_SR0_PRIO)
#elif (IRQ_CAN2_SR0_CAT == IRQ_CAT2)
ISR(CAN2SR0_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx Interrupt function for dedicated buffer */
  Can_17_McmCan_IsrReceiveHandler(CAN_17_MCMCAN_HWMCMKERNEL2_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER0_ID);
#endif
}
#endif

/******************************************************************************
** Syntax :          void CAN2SR1_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service for the transmission completion new entry event **
**                   on TX FIFO Event                                        **
******************************************************************************/
#if((IRQ_CAN2_SR1_PRIO > 0) || (IRQ_CAN2_SR1_CAT == IRQ_CAT2))
#if((IRQ_CAN2_SR1_PRIO > 0) && (IRQ_CAN2_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN2SR1_ISR, 0, IRQ_CAN2_SR1_PRIO)
#elif (IRQ_CAN2_SR1_CAT == IRQ_CAT2)
ISR(CAN2SR1_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_TX_INTERRUPT_PROCESSING == STD_ON) ||(CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Tx Interrupt function*/
  Can_17_McmCan_IsrTransmitHandler(CAN_17_MCMCAN_HWMCMKERNEL2_ID, \
                                                      CAN_17_MCMCAN_HWMCMCONTROLLER0_ID);
#endif
}
#endif

/******************************************************************************
** Syntax :          void CAN2SR2_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN controller with in Bus Off mode          **
**                                                                           **
******************************************************************************/

#if((IRQ_CAN2_SR2_PRIO > 0) || (IRQ_CAN2_SR2_CAT == IRQ_CAT2))
#if((IRQ_CAN2_SR2_PRIO > 0) && (IRQ_CAN2_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN2SR2_ISR, 0, IRQ_CAN2_SR2_PRIO)
#elif (IRQ_CAN2_SR2_CAT == IRQ_CAT2)
ISR(CAN2SR2_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if(CAN_17_MCMCAN_BO_INTERRUPT_PROCESSING == STD_ON)
  /* Call CAN Bus off hanlder Interrupt function*/
  Can_17_McmCan_IsrBusOffHandler(CAN_17_MCMCAN_HWMCMKERNEL2_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER0_ID);
#endif
}
#endif

/******************************************************************************
** Syntax :          void CAN2SR3_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data reception through RXFIFO0 or        **
**                   RXFIFO1                                                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if((IRQ_CAN2_SR3_PRIO > 0) || (IRQ_CAN2_SR3_CAT == IRQ_CAT2))
#if((IRQ_CAN2_SR3_PRIO > 0) && (IRQ_CAN2_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN2SR3_ISR, 0, IRQ_CAN2_SR3_PRIO)
#elif (IRQ_CAN2_SR3_CAT == IRQ_CAT2)
ISR(CAN2SR3_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif

#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx FIFO Handler Interrupt function*/
  Can_17_McmCan_IsrRxFIFOHandler(CAN_17_MCMCAN_HWMCMKERNEL2_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER0_ID);
#endif
}
#endif

/******************************************************************************
** Syntax :          void CAN2SR4_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data Reception through Dedicated buffer  **
**                                                                           **
******************************************************************************/

#if((IRQ_CAN2_SR4_PRIO > 0) || (IRQ_CAN2_SR4_CAT == IRQ_CAT2))
#if((IRQ_CAN2_SR4_PRIO > 0) && (IRQ_CAN2_SR4_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN2SR4_ISR, 0, IRQ_CAN2_SR4_PRIO)
#elif (IRQ_CAN2_SR4_CAT == IRQ_CAT2)
ISR(CAN2SR4_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx Interrupt function for dedicated buffer */
  Can_17_McmCan_IsrReceiveHandler(CAN_17_MCMCAN_HWMCMKERNEL2_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER1_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN2SR5_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service for the transmission completion new entry event **
**                   on TX FIFO Event                                        **
******************************************************************************/
#if((IRQ_CAN2_SR5_PRIO > 0) || (IRQ_CAN2_SR5_CAT == IRQ_CAT2))
#if((IRQ_CAN2_SR5_PRIO > 0) && (IRQ_CAN2_SR5_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN2SR5_ISR, 0, IRQ_CAN2_SR5_PRIO)
#elif (IRQ_CAN2_SR5_CAT == IRQ_CAT2)
ISR(CAN2SR5_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_TX_INTERRUPT_PROCESSING == STD_ON) ||(CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Tx Interrupt function*/
  Can_17_McmCan_IsrTransmitHandler(CAN_17_MCMCAN_HWMCMKERNEL2_ID, \
                                                      CAN_17_MCMCAN_HWMCMCONTROLLER1_ID);
#endif
}
#endif

/******************************************************************************
** Syntax :          void CAN2SR6_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN controller with in Bus Off mode          **
**                                                                           **
******************************************************************************/

#if((IRQ_CAN2_SR6_PRIO > 0) || (IRQ_CAN2_SR6_CAT == IRQ_CAT2))
#if((IRQ_CAN2_SR6_PRIO > 0) && (IRQ_CAN2_SR6_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN2SR6_ISR, 0, IRQ_CAN2_SR6_PRIO)
#elif (IRQ_CAN2_SR6_CAT == IRQ_CAT2)
ISR(CAN2SR6_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if(CAN_17_MCMCAN_BO_INTERRUPT_PROCESSING == STD_ON)
  /* Call CAN Bus off hanlder Interrupt function*/
  Can_17_McmCan_IsrBusOffHandler(CAN_17_MCMCAN_HWMCMKERNEL2_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER1_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN2SR7_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data reception through RXFIFO0 or        **
**                   RXFIFO1                                                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if((IRQ_CAN2_SR7_PRIO > 0) || (IRQ_CAN2_SR7_CAT == IRQ_CAT2))
#if((IRQ_CAN2_SR7_PRIO > 0) && (IRQ_CAN2_SR7_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN2SR7_ISR, 0, IRQ_CAN2_SR7_PRIO)
#elif (IRQ_CAN2_SR7_CAT == IRQ_CAT2)
ISR(CAN2SR7_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif

#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx FIFO Handler Interrupt function*/
  Can_17_McmCan_IsrRxFIFOHandler(CAN_17_MCMCAN_HWMCMKERNEL2_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER1_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN2SR8_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data Reception through Dedicated buffer  **
**                                                                           **
******************************************************************************/

#if((IRQ_CAN2_SR8_PRIO > 0) || (IRQ_CAN2_SR8_CAT == IRQ_CAT2))
#if((IRQ_CAN2_SR8_PRIO > 0) && (IRQ_CAN2_SR8_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN2SR8_ISR, 0, IRQ_CAN2_SR8_PRIO)
#elif (IRQ_CAN2_SR8_CAT == IRQ_CAT2)
ISR(CAN2SR8_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx Interrupt function for dedicated buffer */
  Can_17_McmCan_IsrReceiveHandler(CAN_17_MCMCAN_HWMCMKERNEL2_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER2_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN2SR9_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service for the transmission completion new entry event **
**                   on TX FIFO Event                                        **
******************************************************************************/
#if((IRQ_CAN2_SR9_PRIO > 0) || (IRQ_CAN2_SR9_CAT == IRQ_CAT2))
#if((IRQ_CAN2_SR9_PRIO > 0) && (IRQ_CAN2_SR9_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN2SR9_ISR, 0, IRQ_CAN2_SR9_PRIO)
#elif (IRQ_CAN2_SR9_CAT == IRQ_CAT2)
ISR(CAN2SR9_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_TX_INTERRUPT_PROCESSING == STD_ON) ||(CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Tx Interrupt function*/
  Can_17_McmCan_IsrTransmitHandler(CAN_17_MCMCAN_HWMCMKERNEL2_ID, \
                                                      CAN_17_MCMCAN_HWMCMCONTROLLER2_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN2SR10_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN controller with in Bus Off mode          **
**                                                                           **
******************************************************************************/

#if((IRQ_CAN2_SR10_PRIO > 0) || (IRQ_CAN2_SR10_CAT == IRQ_CAT2))
#if((IRQ_CAN2_SR10_PRIO > 0) && (IRQ_CAN2_SR10_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN2SR10_ISR, 0, IRQ_CAN2_SR10_PRIO)
#elif (IRQ_CAN2_SR10_CAT == IRQ_CAT2)
ISR(CAN2SR10_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if(CAN_17_MCMCAN_BO_INTERRUPT_PROCESSING == STD_ON)
  /* Call CAN Bus off hanlder Interrupt function*/
  Can_17_McmCan_IsrBusOffHandler(CAN_17_MCMCAN_HWMCMKERNEL2_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER2_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN2SR11_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data reception through RXFIFO0 or        **
**                   RXFIFO1                                                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if((IRQ_CAN2_SR11_PRIO > 0) || (IRQ_CAN2_SR11_CAT == IRQ_CAT2))
#if((IRQ_CAN2_SR11_PRIO > 0) && (IRQ_CAN2_SR11_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN2SR11_ISR, 0, IRQ_CAN2_SR11_PRIO)
#elif (IRQ_CAN2_SR11_CAT == IRQ_CAT2)
ISR(CAN2SR11_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif

#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx FIFO Handler Interrupt function*/
  Can_17_McmCan_IsrRxFIFOHandler(CAN_17_MCMCAN_HWMCMKERNEL2_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER2_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN2SR12_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data Reception through Dedicated buffer  **
**                                                                           **
******************************************************************************/

#if((IRQ_CAN2_SR12_PRIO > 0) || (IRQ_CAN2_SR12_CAT == IRQ_CAT2))
#if((IRQ_CAN2_SR12_PRIO > 0) && (IRQ_CAN2_SR12_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN2SR12_ISR, 0, IRQ_CAN2_SR12_PRIO)
#elif (IRQ_CAN2_SR12_CAT == IRQ_CAT2)
ISR(CAN2SR12_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx Interrupt function for dedicated buffer */
  Can_17_McmCan_IsrReceiveHandler(CAN_17_MCMCAN_HWMCMKERNEL2_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER3_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN2SR13_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service for the transmission completion new entry event **
**                   on TX FIFO Event                                        **
******************************************************************************/
#if((IRQ_CAN2_SR13_PRIO > 0) || (IRQ_CAN2_SR13_CAT == IRQ_CAT2))
#if((IRQ_CAN2_SR13_PRIO > 0) && (IRQ_CAN2_SR13_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN2SR13_ISR, 0, IRQ_CAN2_SR13_PRIO)
#elif (IRQ_CAN2_SR13_CAT == IRQ_CAT2)
ISR(CAN2SR13_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_TX_INTERRUPT_PROCESSING == STD_ON) ||(CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Tx Interrupt function*/
  Can_17_McmCan_IsrTransmitHandler(CAN_17_MCMCAN_HWMCMKERNEL2_ID, \
                                                      CAN_17_MCMCAN_HWMCMCONTROLLER3_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN2SR14_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN controller with in Bus Off mode          **
**                                                                           **
******************************************************************************/

#if((IRQ_CAN2_SR14_PRIO > 0) || (IRQ_CAN2_SR14_CAT == IRQ_CAT2))
#if((IRQ_CAN2_SR14_PRIO > 0) && (IRQ_CAN2_SR14_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN2SR14_ISR, 0, IRQ_CAN2_SR14_PRIO)
#elif (IRQ_CAN2_SR14_CAT == IRQ_CAT2)
ISR(CAN2SR14_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if(CAN_17_MCMCAN_BO_INTERRUPT_PROCESSING == STD_ON)
  /* Call CAN Bus off hanlder Interrupt function*/
  Can_17_McmCan_IsrBusOffHandler(CAN_17_MCMCAN_HWMCMKERNEL2_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER3_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN2SR15_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data reception through RXFIFO0 or        **
**                   RXFIFO1                                                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if((IRQ_CAN2_SR15_PRIO > 0) || (IRQ_CAN2_SR15_CAT == IRQ_CAT2))
#if((IRQ_CAN2_SR15_PRIO > 0) && (IRQ_CAN2_SR15_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN2SR15_ISR, 0, IRQ_CAN2_SR15_PRIO)
#elif (IRQ_CAN2_SR15_CAT == IRQ_CAT2)
ISR(CAN2SR15_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif

#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx FIFO Handler Interrupt function*/
  Can_17_McmCan_IsrRxFIFOHandler(CAN_17_MCMCAN_HWMCMKERNEL2_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER3_ID);
#endif
}
#endif

#endif


#if (IRQ_CAN3_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void CAN3SR0_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data Reception through Dedicated buffer  **
**                                                                           **
******************************************************************************/
#if((IRQ_CAN3_SR0_PRIO > 0) || (IRQ_CAN3_SR0_CAT == IRQ_CAT2))
#if((IRQ_CAN3_SR0_PRIO > 0) && (IRQ_CAN3_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN3SR0_ISR, 0, IRQ_CAN3_SR0_PRIO)
#elif (IRQ_CAN3_SR0_CAT == IRQ_CAT2)
ISR(CAN3SR0_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx Interrupt function for dedicated buffer */
  Can_17_McmCan_IsrReceiveHandler(CAN_17_MCMCAN_HWMCMKERNEL3_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER0_ID);
#endif
}
#endif

/******************************************************************************
** Syntax :          void CAN3SR1_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service for the transmission completion new entry event **
**                   on TX FIFO Event                                        **
******************************************************************************/
#if((IRQ_CAN3_SR1_PRIO > 0) || (IRQ_CAN3_SR1_CAT == IRQ_CAT2))
#if((IRQ_CAN3_SR1_PRIO > 0) && (IRQ_CAN3_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN3SR1_ISR, 0, IRQ_CAN3_SR1_PRIO)
#elif (IRQ_CAN3_SR1_CAT == IRQ_CAT2)
ISR(CAN3SR1_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_TX_INTERRUPT_PROCESSING == STD_ON) ||(CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Tx Interrupt function*/
  Can_17_McmCan_IsrTransmitHandler(CAN_17_MCMCAN_HWMCMKERNEL3_ID, \
                                                      CAN_17_MCMCAN_HWMCMCONTROLLER0_ID);
#endif
}
#endif

/******************************************************************************
** Syntax :          void CAN3SR2_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN controller with in Bus Off mode          **
**                                                                           **
******************************************************************************/
#if((IRQ_CAN3_SR2_PRIO > 0) || (IRQ_CAN3_SR2_CAT == IRQ_CAT2))
#if((IRQ_CAN3_SR2_PRIO > 0) && (IRQ_CAN3_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN3SR2_ISR, 0, IRQ_CAN3_SR2_PRIO)
#elif (IRQ_CAN3_SR2_CAT == IRQ_CAT2)
ISR(CAN3SR2_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if(CAN_17_MCMCAN_BO_INTERRUPT_PROCESSING == STD_ON)
  /* Call CAN Bus off hanlder Interrupt function*/
  Can_17_McmCan_IsrBusOffHandler(CAN_17_MCMCAN_HWMCMKERNEL3_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER0_ID);
#endif
}
#endif

/******************************************************************************
** Syntax :          void CAN3SR3_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data reception through RXFIFO0 or        **
**                   RXFIFO1                                                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if((IRQ_CAN3_SR3_PRIO > 0) || (IRQ_CAN3_SR3_CAT == IRQ_CAT2))
#if((IRQ_CAN3_SR3_PRIO > 0) && (IRQ_CAN3_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN3SR3_ISR, 0, IRQ_CAN3_SR3_PRIO)
#elif (IRQ_CAN3_SR3_CAT == IRQ_CAT2)
ISR(CAN3SR3_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif

#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx FIFO Handler Interrupt function*/
  Can_17_McmCan_IsrRxFIFOHandler(CAN_17_MCMCAN_HWMCMKERNEL3_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER0_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN3SR4_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data Reception through Dedicated buffer  **
**                                                                           **
******************************************************************************/

#if((IRQ_CAN3_SR4_PRIO > 0) || (IRQ_CAN3_SR4_CAT == IRQ_CAT2))
#if((IRQ_CAN3_SR4_PRIO > 0) && (IRQ_CAN3_SR4_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN3SR4_ISR, 0, IRQ_CAN3_SR4_PRIO)
#elif (IRQ_CAN3_SR4_CAT == IRQ_CAT2)
ISR(CAN3SR4_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx Interrupt function for dedicated buffer */
  Can_17_McmCan_IsrReceiveHandler(CAN_17_MCMCAN_HWMCMKERNEL3_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER1_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN3SR5_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service for the transmission completion new entry event **
**                   on TX FIFO Event                                        **
******************************************************************************/
#if((IRQ_CAN3_SR5_PRIO > 0) || (IRQ_CAN3_SR5_CAT == IRQ_CAT2))
#if((IRQ_CAN3_SR5_PRIO > 0) && (IRQ_CAN3_SR5_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN3SR5_ISR, 0, IRQ_CAN3_SR5_PRIO)
#elif (IRQ_CAN3_SR5_CAT == IRQ_CAT2)
ISR(CAN3SR5_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_TX_INTERRUPT_PROCESSING == STD_ON) ||(CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Tx Interrupt function*/
  Can_17_McmCan_IsrTransmitHandler(CAN_17_MCMCAN_HWMCMKERNEL3_ID, \
                                                      CAN_17_MCMCAN_HWMCMCONTROLLER1_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN3SR6_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN controller with in Bus Off mode          **
**                                                                           **
******************************************************************************/

#if((IRQ_CAN3_SR6_PRIO > 0) || (IRQ_CAN3_SR6_CAT == IRQ_CAT2))
#if((IRQ_CAN3_SR6_PRIO > 0) && (IRQ_CAN3_SR6_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN3SR6_ISR, 0, IRQ_CAN3_SR6_PRIO)
#elif (IRQ_CAN3_SR6_CAT == IRQ_CAT2)
ISR(CAN3SR6_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if(CAN_17_MCMCAN_BO_INTERRUPT_PROCESSING == STD_ON)
  /* Call CAN Bus off hanlder Interrupt function*/
  Can_17_McmCan_IsrBusOffHandler(CAN_17_MCMCAN_HWMCMKERNEL3_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER1_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN3SR7_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data reception through RXFIFO0 or        **
**                   RXFIFO1                                                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if((IRQ_CAN3_SR7_PRIO > 0) || (IRQ_CAN3_SR7_CAT == IRQ_CAT2))
#if((IRQ_CAN3_SR7_PRIO > 0) && (IRQ_CAN3_SR7_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN3SR7_ISR, 0, IRQ_CAN3_SR7_PRIO)
#elif (IRQ_CAN3_SR7_CAT == IRQ_CAT2)
ISR(CAN3SR7_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif

#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx FIFO Handler Interrupt function*/
  Can_17_McmCan_IsrRxFIFOHandler(CAN_17_MCMCAN_HWMCMKERNEL3_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER1_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN3SR8_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data Reception through Dedicated buffer  **
**                                                                           **
******************************************************************************/

#if((IRQ_CAN3_SR8_PRIO > 0) || (IRQ_CAN3_SR8_CAT == IRQ_CAT2))
#if((IRQ_CAN3_SR8_PRIO > 0) && (IRQ_CAN3_SR8_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN3SR8_ISR, 0, IRQ_CAN3_SR8_PRIO)
#elif (IRQ_CAN3_SR8_CAT == IRQ_CAT2)
ISR(CAN3SR8_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx Interrupt function for dedicated buffer */
  Can_17_McmCan_IsrReceiveHandler(CAN_17_MCMCAN_HWMCMKERNEL3_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER2_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN3SR9_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service for the transmission completion new entry event **
**                   on TX FIFO Event                                        **
******************************************************************************/
#if((IRQ_CAN3_SR9_PRIO > 0) || (IRQ_CAN3_SR9_CAT == IRQ_CAT2))
#if((IRQ_CAN3_SR9_PRIO > 0) && (IRQ_CAN3_SR9_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN3SR9_ISR, 0, IRQ_CAN3_SR9_PRIO)
#elif (IRQ_CAN3_SR9_CAT == IRQ_CAT2)
ISR(CAN3SR9_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_TX_INTERRUPT_PROCESSING == STD_ON) ||(CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Tx Interrupt function*/
  Can_17_McmCan_IsrTransmitHandler(CAN_17_MCMCAN_HWMCMKERNEL3_ID, \
                                                      CAN_17_MCMCAN_HWMCMCONTROLLER2_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN3SR10_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN controller with in Bus Off mode          **
**                                                                           **
******************************************************************************/

#if((IRQ_CAN3_SR10_PRIO > 0) || (IRQ_CAN3_SR10_CAT == IRQ_CAT2))
#if((IRQ_CAN3_SR10_PRIO > 0) && (IRQ_CAN3_SR10_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN3SR10_ISR, 0, IRQ_CAN3_SR10_PRIO)
#elif (IRQ_CAN3_SR10_CAT == IRQ_CAT2)
ISR(CAN3SR10_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if(CAN_17_MCMCAN_BO_INTERRUPT_PROCESSING == STD_ON)
  /* Call CAN Bus off hanlder Interrupt function*/
  Can_17_McmCan_IsrBusOffHandler(CAN_17_MCMCAN_HWMCMKERNEL3_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER2_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN3SR11_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data reception through RXFIFO0 or        **
**                   RXFIFO1                                                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if((IRQ_CAN3_SR11_PRIO > 0) || (IRQ_CAN3_SR11_CAT == IRQ_CAT2))
#if((IRQ_CAN3_SR11_PRIO > 0) && (IRQ_CAN3_SR11_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN3SR11_ISR, 0, IRQ_CAN3_SR11_PRIO)
#elif (IRQ_CAN3_SR11_CAT == IRQ_CAT2)
ISR(CAN3SR11_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif

#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx FIFO Handler Interrupt function*/
  Can_17_McmCan_IsrRxFIFOHandler(CAN_17_MCMCAN_HWMCMKERNEL3_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER2_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN3SR12_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data Reception through Dedicated buffer  **
**                                                                           **
******************************************************************************/

#if((IRQ_CAN3_SR12_PRIO > 0) || (IRQ_CAN3_SR12_CAT == IRQ_CAT2))
#if((IRQ_CAN3_SR12_PRIO > 0) && (IRQ_CAN3_SR12_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN3SR12_ISR, 0, IRQ_CAN3_SR12_PRIO)
#elif (IRQ_CAN3_SR12_CAT == IRQ_CAT2)
ISR(CAN3SR12_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx Interrupt function for dedicated buffer */
  Can_17_McmCan_IsrReceiveHandler(CAN_17_MCMCAN_HWMCMKERNEL3_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER3_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN3SR13_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service for the transmission completion new entry event **
**                   on TX FIFO Event                                        **
******************************************************************************/
#if((IRQ_CAN3_SR13_PRIO > 0) || (IRQ_CAN3_SR13_CAT == IRQ_CAT2))
#if((IRQ_CAN3_SR13_PRIO > 0) && (IRQ_CAN3_SR13_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN3SR13_ISR, 0, IRQ_CAN3_SR13_PRIO)
#elif (IRQ_CAN3_SR13_CAT == IRQ_CAT2)
ISR(CAN3SR13_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_TX_INTERRUPT_PROCESSING == STD_ON) ||(CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Tx Interrupt function*/
  Can_17_McmCan_IsrTransmitHandler(CAN_17_MCMCAN_HWMCMKERNEL3_ID, \
                                                      CAN_17_MCMCAN_HWMCMCONTROLLER3_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN3SR14_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN controller with in Bus Off mode          **
**                                                                           **
******************************************************************************/

#if((IRQ_CAN3_SR14_PRIO > 0) || (IRQ_CAN3_SR14_CAT == IRQ_CAT2))
#if((IRQ_CAN3_SR14_PRIO > 0) && (IRQ_CAN3_SR14_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN3SR14_ISR, 0, IRQ_CAN3_SR14_PRIO)
#elif (IRQ_CAN3_SR14_CAT == IRQ_CAT2)
ISR(CAN3SR14_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if(CAN_17_MCMCAN_BO_INTERRUPT_PROCESSING == STD_ON)
  /* Call CAN Bus off hanlder Interrupt function*/
  Can_17_McmCan_IsrBusOffHandler(CAN_17_MCMCAN_HWMCMKERNEL3_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER3_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN3SR15_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data reception through RXFIFO0 or        **
**                   RXFIFO1                                                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/

#if((IRQ_CAN3_SR15_PRIO > 0) || (IRQ_CAN3_SR15_CAT == IRQ_CAT2))
#if((IRQ_CAN3_SR15_PRIO > 0) && (IRQ_CAN3_SR15_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN3SR15_ISR, 0, IRQ_CAN3_SR15_PRIO)
#elif (IRQ_CAN3_SR15_CAT == IRQ_CAT2)
ISR(CAN3SR15_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif

#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx FIFO Handler Interrupt function*/
  Can_17_McmCan_IsrRxFIFOHandler(CAN_17_MCMCAN_HWMCMKERNEL3_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER3_ID);
#endif
}
#endif

#endif



#if (IRQ_CAN4_EXIST == STD_ON)
/******************************************************************************
** Syntax :          void CAN4SR0_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data Reception through Dedicated buffer  **
**                                                                           **
******************************************************************************/
#if((IRQ_CAN4_SR0_PRIO > 0) || (IRQ_CAN4_SR0_CAT == IRQ_CAT2))
#if((IRQ_CAN4_SR0_PRIO > 0) && (IRQ_CAN4_SR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN4SR0_ISR, 0, IRQ_CAN4_SR0_PRIO)
#elif (IRQ_CAN4_SR0_CAT == IRQ_CAT2)
ISR(CAN4SR0_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx Interrupt function for dedicated buffer */
  Can_17_McmCan_IsrReceiveHandler(CAN_17_MCMCAN_HWMCMKERNEL4_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER0_ID);
#endif
}
#endif

/******************************************************************************
** Syntax :          void CAN4SR1_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service for the transmission completion new entry event **
**                   on TX FIFO Event                                        **
******************************************************************************/
#if((IRQ_CAN4_SR1_PRIO > 0) || (IRQ_CAN4_SR1_CAT == IRQ_CAT2))
#if((IRQ_CAN4_SR1_PRIO > 0) && (IRQ_CAN4_SR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN4SR1_ISR, 0, IRQ_CAN4_SR1_PRIO)
#elif (IRQ_CAN4_SR1_CAT == IRQ_CAT2)
ISR(CAN4SR1_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_TX_INTERRUPT_PROCESSING == STD_ON) ||(CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Tx Interrupt function*/
  Can_17_McmCan_IsrTransmitHandler(CAN_17_MCMCAN_HWMCMKERNEL4_ID, \
                                                      CAN_17_MCMCAN_HWMCMCONTROLLER0_ID);
#endif
}
#endif

/******************************************************************************
** Syntax :          void CAN4SR2_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN controller with in Bus Off mode          **
**                                                                           **
******************************************************************************/

#if((IRQ_CAN4_SR2_PRIO > 0) || (IRQ_CAN4_SR2_CAT == IRQ_CAT2))
#if((IRQ_CAN4_SR2_PRIO > 0) && (IRQ_CAN4_SR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN4SR2_ISR, 0, IRQ_CAN4_SR2_PRIO)
#elif (IRQ_CAN4_SR2_CAT == IRQ_CAT2)
ISR(CAN4SR2_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if(CAN_17_MCMCAN_BO_INTERRUPT_PROCESSING == STD_ON)
  /* Call CAN Bus off hanlder Interrupt function*/
  Can_17_McmCan_IsrBusOffHandler(CAN_17_MCMCAN_HWMCMKERNEL4_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER0_ID);
#endif
}
#endif

/******************************************************************************
** Syntax :          void CAN4SR3_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data reception through RXFIFO0 or        **
**                   RXFIFO1                                                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if((IRQ_CAN4_SR3_PRIO > 0) || (IRQ_CAN4_SR3_CAT == IRQ_CAT2))
#if((IRQ_CAN4_SR3_PRIO > 0) && (IRQ_CAN4_SR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN4SR3_ISR, 0, IRQ_CAN4_SR3_PRIO)
#elif (IRQ_CAN4_SR3_CAT == IRQ_CAT2)
ISR(CAN4SR3_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif

#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx FIFO Handler Interrupt function*/
  Can_17_McmCan_IsrRxFIFOHandler(CAN_17_MCMCAN_HWMCMKERNEL4_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER0_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN4SR4_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data Reception through Dedicated buffer  **
**                                                                           **
******************************************************************************/

#if((IRQ_CAN4_SR4_PRIO > 0) || (IRQ_CAN4_SR4_CAT == IRQ_CAT2))
#if((IRQ_CAN4_SR4_PRIO > 0) && (IRQ_CAN4_SR4_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN4SR4_ISR, 0, IRQ_CAN4_SR4_PRIO)
#elif (IRQ_CAN4_SR4_CAT == IRQ_CAT2)
ISR(CAN4SR4_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx Interrupt function for dedicated buffer */
  Can_17_McmCan_IsrReceiveHandler(CAN_17_MCMCAN_HWMCMKERNEL4_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER1_ID);
#endif
}
#endif
/******************************************************************************
** Syntax :          void CAN4SR5_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service for the transmission completion new entry event **
**                   on TX FIFO Event                                        **
******************************************************************************/

#if((IRQ_CAN4_SR5_PRIO > 0) || (IRQ_CAN4_SR5_CAT == IRQ_CAT2))
#if((IRQ_CAN4_SR5_PRIO > 0) && (IRQ_CAN4_SR5_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN4SR5_ISR, 0, IRQ_CAN4_SR5_PRIO)
#elif (IRQ_CAN4_SR5_CAT == IRQ_CAT2)
ISR(CAN4SR5_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_TX_INTERRUPT_PROCESSING == STD_ON) ||(CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Tx Interrupt function*/
  Can_17_McmCan_IsrTransmitHandler(CAN_17_MCMCAN_HWMCMKERNEL4_ID, \
                                                      CAN_17_MCMCAN_HWMCMCONTROLLER1_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN4SR6_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN controller with in Bus Off mode          **
**                                                                           **
******************************************************************************/

#if((IRQ_CAN4_SR6_PRIO > 0) || (IRQ_CAN4_SR6_CAT == IRQ_CAT2))
#if((IRQ_CAN4_SR6_PRIO > 0) && (IRQ_CAN4_SR6_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN4SR6_ISR, 0, IRQ_CAN4_SR6_PRIO)
#elif (IRQ_CAN4_SR6_CAT == IRQ_CAT2)
ISR(CAN4SR6_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if(CAN_17_MCMCAN_BO_INTERRUPT_PROCESSING == STD_ON)
  /* Call CAN Bus off hanlder Interrupt function*/
  Can_17_McmCan_IsrBusOffHandler(CAN_17_MCMCAN_HWMCMKERNEL4_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER1_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN4SR7_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data reception through RXFIFO0 or        **
**                   RXFIFO1                                                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if((IRQ_CAN4_SR7_PRIO > 0) || (IRQ_CAN4_SR7_CAT == IRQ_CAT2))
#if((IRQ_CAN4_SR7_PRIO > 0) && (IRQ_CAN4_SR7_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN4SR7_ISR, 0, IRQ_CAN4_SR7_PRIO)
#elif (IRQ_CAN4_SR7_CAT == IRQ_CAT2)
ISR(CAN4SR7_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif

#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx FIFO Handler Interrupt function*/
  Can_17_McmCan_IsrRxFIFOHandler(CAN_17_MCMCAN_HWMCMKERNEL4_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER1_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN4SR8_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data Reception through Dedicated buffer  **
**                                                                           **
******************************************************************************/
#if((IRQ_CAN4_SR8_PRIO > 0) || (IRQ_CAN4_SR8_CAT == IRQ_CAT2))
#if((IRQ_CAN4_SR8_PRIO > 0) && (IRQ_CAN4_SR8_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN4SR8_ISR, 0, IRQ_CAN4_SR8_PRIO)
#elif (IRQ_CAN4_SR8_CAT == IRQ_CAT2)
ISR(CAN4SR8_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx Interrupt function for dedicated buffer */
  Can_17_McmCan_IsrReceiveHandler(CAN_17_MCMCAN_HWMCMKERNEL4_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER2_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN4SR9_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service for the transmission completion new entry event **
**                   on TX FIFO Event                                        **
******************************************************************************/
#if((IRQ_CAN4_SR9_PRIO > 0) || (IRQ_CAN4_SR9_CAT == IRQ_CAT2))
#if((IRQ_CAN4_SR9_PRIO > 0) && (IRQ_CAN4_SR9_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN4SR9_ISR, 0, IRQ_CAN4_SR9_PRIO)
#elif (IRQ_CAN4_SR9_CAT == IRQ_CAT2)
ISR(CAN4SR9_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_TX_INTERRUPT_PROCESSING == STD_ON) ||(CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Tx Interrupt function*/
  Can_17_McmCan_IsrTransmitHandler(CAN_17_MCMCAN_HWMCMKERNEL4_ID, \
                                                      CAN_17_MCMCAN_HWMCMCONTROLLER2_ID);
#endif
}
#endif

/******************************************************************************
** Syntax :          void CAN4SR10_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN controller with in Bus Off mode          **
**                                                                           **
******************************************************************************/

#if((IRQ_CAN4_SR10_PRIO > 0) || (IRQ_CAN4_SR10_CAT == IRQ_CAT2))
#if((IRQ_CAN4_SR10_PRIO > 0) && (IRQ_CAN4_SR10_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN4SR10_ISR, 0, IRQ_CAN4_SR10_PRIO)
#elif (IRQ_CAN4_SR10_CAT == IRQ_CAT2)
ISR(CAN4SR10_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if(CAN_17_MCMCAN_BO_INTERRUPT_PROCESSING == STD_ON)
  /* Call CAN Bus off hanlder Interrupt function*/
  Can_17_McmCan_IsrBusOffHandler(CAN_17_MCMCAN_HWMCMKERNEL4_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER2_ID);
#endif
}
#endif

/******************************************************************************
** Syntax :          void CAN4SR11_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data reception through RXFIFO0 or        **
**                   RXFIFO1                                                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if((IRQ_CAN4_SR11_PRIO > 0) || (IRQ_CAN4_SR11_CAT == IRQ_CAT2))
#if((IRQ_CAN4_SR11_PRIO > 0) && (IRQ_CAN4_SR11_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN4SR11_ISR, 0, IRQ_CAN4_SR11_PRIO)
#elif (IRQ_CAN4_SR11_CAT == IRQ_CAT2)
ISR(CAN4SR11_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif

#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx FIFO Handler Interrupt function*/
  Can_17_McmCan_IsrRxFIFOHandler(CAN_17_MCMCAN_HWMCMKERNEL4_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER2_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN4SR12_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data Reception through Dedicated buffer  **
**                                                                           **
******************************************************************************/

#if((IRQ_CAN4_SR12_PRIO > 0) || (IRQ_CAN4_SR12_CAT == IRQ_CAT2))
#if((IRQ_CAN4_SR12_PRIO > 0) && (IRQ_CAN4_SR12_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN4SR12_ISR, 0, IRQ_CAN4_SR12_PRIO)
#elif (IRQ_CAN4_SR12_CAT == IRQ_CAT2)
ISR(CAN4SR12_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx Interrupt function for dedicated buffer */
  Can_17_McmCan_IsrReceiveHandler(CAN_17_MCMCAN_HWMCMKERNEL4_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER3_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN4SR13_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service for the transmission completion new entry event **
**                   on TX FIFO Event                                        **
******************************************************************************/
#if((IRQ_CAN4_SR13_PRIO > 0) || (IRQ_CAN4_SR13_CAT == IRQ_CAT2))
#if((IRQ_CAN4_SR13_PRIO > 0) && (IRQ_CAN4_SR13_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN4SR13_ISR, 0, IRQ_CAN4_SR13_PRIO)
#elif (IRQ_CAN4_SR13_CAT == IRQ_CAT2)
ISR(CAN4SR13_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if((CAN_17_MCMCAN_TX_INTERRUPT_PROCESSING == STD_ON) ||(CAN_17_MCMCAN_TX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Tx Interrupt function*/
  Can_17_McmCan_IsrTransmitHandler(CAN_17_MCMCAN_HWMCMKERNEL4_ID, \
                                                      CAN_17_MCMCAN_HWMCMCONTROLLER3_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN4SR14_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN controller with in Bus Off mode          **
**                                                                           **
******************************************************************************/
#if((IRQ_CAN4_SR14_PRIO > 0) || (IRQ_CAN4_SR14_CAT == IRQ_CAT2))
#if((IRQ_CAN4_SR14_PRIO > 0) && (IRQ_CAN4_SR14_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN4SR14_ISR, 0, IRQ_CAN4_SR14_PRIO)
#elif (IRQ_CAN4_SR14_CAT == IRQ_CAT2)
ISR(CAN4SR14_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif
#if(CAN_17_MCMCAN_BO_INTERRUPT_PROCESSING == STD_ON)
  /* Call CAN Bus off hanlder Interrupt function*/
  Can_17_McmCan_IsrBusOffHandler(CAN_17_MCMCAN_HWMCMKERNEL4_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER3_ID);
#endif
}
#endif


/******************************************************************************
** Syntax :          void CAN4SR15_ISR(void)                                  **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       non reentrant                                           **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description :     Service on CAN data reception through RXFIFO0 or        **
**                   RXFIFO1                                                 **
**                   service request                                         **
**                                                                           **
******************************************************************************/
#if((IRQ_CAN4_SR15_PRIO > 0) || (IRQ_CAN4_SR15_CAT == IRQ_CAT2))
#if((IRQ_CAN4_SR15_PRIO > 0) && (IRQ_CAN4_SR15_CAT == IRQ_CAT1))
IFX_INTERRUPT(CAN4SR15_ISR, 0, IRQ_CAN4_SR15_PRIO)
#elif (IRQ_CAN4_SR15_CAT == IRQ_CAT2)
ISR(CAN4SR15_ISR)
#endif
{
  /* Enable Global Interrupts */
   ENABLE();
#ifdef  APP_SW
#if (APP_SW == TEST_APP)
  /* To Set ISR Execution in USER1 mode */
#if (TEST_ACCESS_MODE_INIT == TEST_MCAL_USER1)
    Mcal_SetModetoUser();
#endif
#endif
#endif

#if((CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING == STD_ON)||(CAN_17_MCMCAN_RX_MIXED_PROCESSING == STD_ON))
  /* Call CAN Rx FIFO Handler Interrupt function*/
  Can_17_McmCan_IsrRxFIFOHandler(CAN_17_MCMCAN_HWMCMKERNEL4_ID, \
  CAN_17_MCMCAN_HWMCMCONTROLLER3_ID);
#endif
}
#endif

#endif
