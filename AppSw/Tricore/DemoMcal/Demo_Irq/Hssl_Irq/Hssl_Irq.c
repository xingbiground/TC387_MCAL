/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2017)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Hssl_Irq.c                                                    **
**                                                                            **
**  VERSION   : 1.0.0                                                         **
**                                                                            **
**  DATE      : 2017-10-12                                                    **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION : This file contains the interrupt frames for the HSSL Module **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : Yes                                              **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Std_Types.h"
#include "Irq.h"
#include "Hssl.h"
#include "IFX_Os.h"

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

#if (IRQ_HSSL0_EXIST == STD_ON)
/******************************************************************************
** Syntax : void HSSL0_ISR_COK0(void)                                        **
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
** Description : Service for COK0 interrupt of HSSL0                         **
**                                                                           **
******************************************************************************/
#if IRQ_HSSL0_COK0_TOS != IRQ_TOS_DMA
#if((IRQ_HSSL0_COK0_PRIO > 0) || (IRQ_HSSL0_COK0_CAT == IRQ_CAT2))
#if((IRQ_HSSL0_COK0_PRIO > 0) && (IRQ_HSSL0_COK0_CAT == IRQ_CAT1))
IFX_INTERRUPT(HSSL0_ISR_COK0, 0, IRQ_HSSL0_COK0_PRIO)
#elif IRQ_HSSL0_COK0_CAT == IRQ_CAT2
ISR(HSSL0_ISR_COK0)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  
  /* Call TX Interrupt funtion - call the HSSL callback function */ 
  Hssl_IsrCOK(HSSL0, 0U);
}
#endif
#endif

/******************************************************************************
** Syntax : void HSSL0_ISR_COK1(void)                                        **
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
** Description : Service for COK1 interrupt of HSSL0                         **
**                                                                           **
******************************************************************************/
#if IRQ_HSSL0_COK1_TOS != IRQ_TOS_DMA
#if((IRQ_HSSL0_COK1_PRIO > 0) || (IRQ_HSSL0_COK1_CAT == IRQ_CAT2))
#if((IRQ_HSSL0_COK1_PRIO > 0) && (IRQ_HSSL0_COK1_CAT == IRQ_CAT1))
IFX_INTERRUPT(HSSL0_ISR_COK1, 0, IRQ_HSSL0_COK1_PRIO)
#elif IRQ_HSSL0_COK1_CAT == IRQ_CAT2
ISR(HSSL0_ISR_COK1)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();

  /* Call TX Interrupt funtion - call the HSSL callback function */ 
   Hssl_IsrCOK(HSSL0, 1U);
}
#endif
#endif

/******************************************************************************
** Syntax : void HSSL0_ISR_COK2(void)                                        **
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
** Description : Service for COK2 interrupt of HSSL0                         **
**                                                                           **
******************************************************************************/
#if IRQ_HSSL0_COK2_TOS != IRQ_TOS_DMA
#if((IRQ_HSSL0_COK2_PRIO > 0) || (IRQ_HSSL0_COK2_CAT == IRQ_CAT2))
#if((IRQ_HSSL0_COK2_PRIO > 0) && (IRQ_HSSL0_COK2_CAT == IRQ_CAT1))
IFX_INTERRUPT(HSSL0_ISR_COK2, 0, IRQ_HSSL0_COK2_PRIO)
#elif IRQ_HSSL0_COK2_CAT == IRQ_CAT2
ISR(HSSL0_ISR_COK2)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();

  /* Call TX Interrupt funtion - call the HSSL callback function */ 
  Hssl_IsrCOK(HSSL0, 2U);
}
#endif
#endif

/******************************************************************************
** Syntax : void HSSL0_ISR_COK3(void)                                        **
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
** Description : Service for COK3 interrupt of HSSL0                         **
**                                                                           **
******************************************************************************/

#if IRQ_HSSL0_COK3_TOS != IRQ_TOS_DMA
#if((IRQ_HSSL0_COK3_PRIO > 0) || (IRQ_HSSL0_COK3_CAT == IRQ_CAT2))
#if((IRQ_HSSL0_COK3_PRIO > 0) && (IRQ_HSSL0_COK3_CAT == IRQ_CAT1))
IFX_INTERRUPT(HSSL0_ISR_COK3, 0, IRQ_HSSL0_COK3_PRIO)
#elif IRQ_HSSL0_COK3_CAT == IRQ_CAT2
ISR(HSSL0_ISR_COK3)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();

  /* Call TX Interrupt funtion - call the HSSL callback function */ 
  Hssl_IsrCOK(HSSL0, 3U);
}
#endif
#endif

/******************************************************************************
** Syntax : void HSSL0_ISR_RDI0(void)                                        **
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
** Description : Service for RDI0 interrupt of HSSL0                         **
**                                                                           **
******************************************************************************/

#if IRQ_HSSL0_RDI0_TOS != IRQ_TOS_DMA
#if((IRQ_HSSL0_RDI0_PRIO > 0) || (IRQ_HSSL0_RDI0_CAT == IRQ_CAT2))
#if((IRQ_HSSL0_RDI0_PRIO > 0) && (IRQ_HSSL0_RDI0_CAT == IRQ_CAT1))
IFX_INTERRUPT(HSSL0_ISR_RDI0, 0, IRQ_HSSL0_RDI0_PRIO)
#elif IRQ_HSSL0_RDI0_CAT == IRQ_CAT2
ISR(HSSL0_ISR_RDI0)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  /* Call RDI Interrupt funtion - call the HSSL callback function */ 
  Hssl_IsrRDI(HSSL0,0U);
}
#endif
#endif
/******************************************************************************
** Syntax : void HSSL0_ISR_RDI1(void)                                        **
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
** Description : Service for RDI1 interrupt of HSSL0                         **
**                                                                           **
******************************************************************************/
#if IRQ_HSSL0_RDI1_TOS != IRQ_TOS_DMA
#if((IRQ_HSSL0_RDI1_PRIO > 0) || (IRQ_HSSL0_RDI1_CAT == IRQ_CAT2))
#if((IRQ_HSSL0_RDI1_PRIO > 0) && (IRQ_HSSL0_RDI1_CAT == IRQ_CAT1))
IFX_INTERRUPT(HSSL0_ISR_RDI1, 0, IRQ_HSSL0_RDI1_PRIO)
#elif IRQ_HSSL0_RDI1_CAT == IRQ_CAT2
ISR(HSSL0_ISR_RDI1)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();

  /* Call RDI Interrupt funtion - call the HSSL callback function */ 
  Hssl_IsrRDI(HSSL0,1U);
}
#endif
#endif

/******************************************************************************
** Syntax : void HSSL0_ISR_RDI2(void)                                        **
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
** Description : Service for RDI2 interrupt of HSSL0                         **
**                                                                           **
******************************************************************************/
#if IRQ_HSSL0_RDI2_TOS != IRQ_TOS_DMA
#if((IRQ_HSSL0_RDI2_PRIO > 0) || (IRQ_HSSL0_RDI2_CAT == IRQ_CAT2))
#if((IRQ_HSSL0_RDI2_PRIO > 0) && (IRQ_HSSL0_RDI2_CAT == IRQ_CAT1))
IFX_INTERRUPT(HSSL0_ISR_RDI2, 0, IRQ_HSSL0_RDI2_PRIO)
#elif IRQ_HSSL0_RDI2_CAT == IRQ_CAT2
ISR(HSSL0_ISR_RDI2)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();

  /* Call RDI Interrupt funtion - call the HSSL callback function */ 
  Hssl_IsrRDI(HSSL0,2U);
}
#endif
#endif

/******************************************************************************
** Syntax : void HSSL0_ISR_RDI3(void)                                        **
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
** Description : Service for RDI3 interrupt of HSSL0                         **
**                                                                           **
******************************************************************************/
#if IRQ_HSSL0_RDI3_TOS != IRQ_TOS_DMA
#if((IRQ_HSSL0_RDI3_PRIO > 0) || (IRQ_HSSL0_RDI3_CAT == IRQ_CAT2))
#if((IRQ_HSSL0_RDI3_PRIO > 0) && (IRQ_HSSL0_RDI3_CAT == IRQ_CAT1))
IFX_INTERRUPT(HSSL0_ISR_RDI3, 0, IRQ_HSSL0_RDI3_PRIO)
#elif IRQ_HSSL0_RDI3_CAT == IRQ_CAT2
ISR(HSSL0_ISR_RDI3)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();

  /* Call RDI Interrupt funtion - call the HSSL callback function */ 
  Hssl_IsrRDI(HSSL0,3U);
}
#endif
#endif

/******************************************************************************
** Syntax : void HSSL0_ISR_ERR0(void)                                        **
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
** Description : Service for Error0 interrupt of HSSL0                       **
**                                                                           **
******************************************************************************/
#if IRQ_HSSL0_ERR0_TOS != IRQ_TOS_DMA
#if((IRQ_HSSL0_ERR0_PRIO > 0) || (IRQ_HSSL0_ERR0_CAT == IRQ_CAT2))
#if((IRQ_HSSL0_ERR0_PRIO > 0) && (IRQ_HSSL0_ERR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(HSSL0_ISR_ERR0, 0, IRQ_HSSL0_ERR0_PRIO)
#elif IRQ_HSSL0_ERR0_CAT == IRQ_CAT2
ISR(HSSL0_ISR_ERR0)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();

  /* Call ERR Interrupt funtion - call the HSSL callback function */ 
  Hssl_IsrError(HSSL0,0U);
}
#endif
#endif

/******************************************************************************
** Syntax : void HSSL0_ISR_ERR1(void)                                        **
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
** Description : Service for Error1 interrupt of HSSL0                       **
**                                                                           **
******************************************************************************/
#if IRQ_HSSL0_ERR1_TOS != IRQ_TOS_DMA
#if((IRQ_HSSL0_ERR1_PRIO > 0) || (IRQ_HSSL0_ERR1_CAT == IRQ_CAT2))
#if((IRQ_HSSL0_ERR1_PRIO > 0) && (IRQ_HSSL0_ERR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(HSSL0_ISR_ERR1, 0, IRQ_HSSL0_ERR1_PRIO)
#elif IRQ_HSSL0_ERR1_CAT == IRQ_CAT2
ISR(HSSL0_ISR_ERR1)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  /* Call ERR Interrupt funtion - call the HSSL callback function */ 
  Hssl_IsrError(HSSL0,1U); 
}
#endif
#endif

/******************************************************************************
** Syntax : void HSSL0_ISR_ERR2(void)                                        **
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
** Description : Service for Error2 interrupt of HSSL0                       **
**                                                                           **
******************************************************************************/
#if IRQ_HSSL0_ERR2_TOS != IRQ_TOS_DMA
#if((IRQ_HSSL0_ERR2_PRIO > 0) || (IRQ_HSSL0_ERR2_CAT == IRQ_CAT2))
#if((IRQ_HSSL0_ERR2_PRIO > 0) && (IRQ_HSSL0_ERR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(HSSL0_ISR_ERR2, 0, IRQ_HSSL0_ERR2_PRIO)
#elif IRQ_HSSL0_ERR2_CAT == IRQ_CAT2
ISR(HSSL0_ISR_ERR2)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();

  /* Call ERR Interrupt funtion - call the HSSL callback function */ 
  Hssl_IsrError(HSSL0,2U); 
}
#endif
#endif

/******************************************************************************
** Syntax : void HSSL0_ISR_ERR3(void)                                        **
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
** Description : Service for Error3 interrupt of HSSL0                       **
**                                                                           **
******************************************************************************/
#if IRQ_HSSL0_ERR3_TOS != IRQ_TOS_DMA
#if((IRQ_HSSL0_ERR3_PRIO > 0) || (IRQ_HSSL0_ERR3_CAT == IRQ_CAT2))
#if((IRQ_HSSL0_ERR3_PRIO > 0) && (IRQ_HSSL0_ERR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(HSSL0_ISR_ERR3, 0, IRQ_HSSL0_ERR3_PRIO)
#elif IRQ_HSSL0_ERR3_CAT == IRQ_CAT2
ISR(HSSL0_ISR_ERR3)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();

  /* Call ERR Interrupt funtion - call the HSSL callback function */ 
  Hssl_IsrError(HSSL0,3U);
}
#endif
#endif

/******************************************************************************
** Syntax : void HSSL0_ISR_TRG0(void)                                        **
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
** Description : Service for Trigger0 interrupt of HSSL0                       **
**                                                                           **
******************************************************************************/
#if IRQ_HSSL0_TRG0_TOS != IRQ_TOS_DMA
#if((IRQ_HSSL0_TRG0_PRIO > 0) || (IRQ_HSSL0_TRG0_CAT == IRQ_CAT2))
#if((IRQ_HSSL0_TRG0_PRIO > 0) && (IRQ_HSSL0_TRG0_CAT == IRQ_CAT1))
IFX_INTERRUPT(HSSL0_ISR_TRG0, 0, IRQ_HSSL0_TRG0_PRIO)
#elif IRQ_HSSL0_TRG0_CAT == IRQ_CAT2
ISR(HSSL0_ISR_TRG0)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();

  /* Call TRG Interrupt funtion - call the HSSL callback function */
  /* HSSL_HANDLE_CALLBACK() */
  Hssl_IsrTrg(HSSL0,0U);
}
#endif
#endif

/******************************************************************************
** Syntax : void HSSL0_ISR_TRG1(void)                                        **
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
** Description : Service for Trigger1 interrupt of HSSL0                       **
**                                                                           **
******************************************************************************/
#if IRQ_HSSL0_TRG1_TOS != IRQ_TOS_DMA
#if((IRQ_HSSL0_TRG1_PRIO > 0) || (IRQ_HSSL0_TRG1_CAT == IRQ_CAT2))
#if((IRQ_HSSL0_TRG1_PRIO > 0) && (IRQ_HSSL0_TRG1_CAT == IRQ_CAT1))
IFX_INTERRUPT(HSSL0_ISR_TRG1, 0, IRQ_HSSL0_TRG1_PRIO)
#elif IRQ_HSSL0_TRG1_CAT == IRQ_CAT2
ISR(HSSL0_ISR_TRG1)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  /* Call TRG Interrupt funtion - call the HSSL callback function */
  /* HSSL_HANDLE_CALLBACK() */
  Hssl_IsrTrg(HSSL0,1U);
}
#endif
#endif

/******************************************************************************
** Syntax : void HSSL0_ISR_TRG2(void)                                        **
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
** Description : Service for Trigger2 interrupt of HSSL0                       **
**                                                                           **
******************************************************************************/
#if IRQ_HSSL0_TRG2_TOS != IRQ_TOS_DMA
#if((IRQ_HSSL0_TRG2_PRIO > 0) || (IRQ_HSSL0_TRG2_CAT == IRQ_CAT2))
#if((IRQ_HSSL0_TRG2_PRIO > 0) && (IRQ_HSSL0_TRG2_CAT == IRQ_CAT1))
IFX_INTERRUPT(HSSL0_ISR_TRG2, 0, IRQ_HSSL0_TRG2_PRIO)
#elif IRQ_HSSL0_TRG2_CAT == IRQ_CAT2
ISR(HSSL0_ISR_TRG2)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();

  /* Call TRG Interrupt funtion - call the HSSL callback function */
  /* HSSL_HANDLE_CALLBACK() */
    Hssl_IsrTrg(HSSL0,2U);
}
#endif
#endif

/******************************************************************************
** Syntax : void HSSL0_ISR_TRG3(void)                                        **
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
** Description : Service for Trigger3 interrupt of HSSL0                       **
**                                                                           **
******************************************************************************/
#if IRQ_HSSL0_TRG3_TOS != IRQ_TOS_DMA
#if((IRQ_HSSL0_TRG3_PRIO > 0) || (IRQ_HSSL0_TRG3_CAT == IRQ_CAT2))
#if((IRQ_HSSL0_TRG3_PRIO > 0) && (IRQ_HSSL0_TRG3_CAT == IRQ_CAT1))
IFX_INTERRUPT(HSSL0_ISR_TRG3, 0, IRQ_HSSL0_TRG3_PRIO)
#elif IRQ_HSSL0_TRG3_CAT == IRQ_CAT2
ISR(HSSL0_ISR_TRG3)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();

  /* Call TRG Interrupt funtion - call the HSSL callback function */
  /* HSSL_HANDLE_CALLBACK() */
    Hssl_IsrTrg(HSSL0,3U);
}
#endif
#endif

/******************************************************************************
** Syntax : void HSSL0_ISR_EXI0(void)                                        **
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
** Description : Service for Exception interrupt of HSSL0                    **
**                                                                           **
******************************************************************************/
#if IRQ_HSSL0_EXI0_TOS != IRQ_TOS_DMA
#if((IRQ_HSSL0_EXI0_PRIO > 0) || (IRQ_HSSL0_EXI0_CAT == IRQ_CAT2))
#if((IRQ_HSSL0_EXI0_PRIO > 0) && (IRQ_HSSL0_EXI0_CAT == IRQ_CAT1))
IFX_INTERRUPT(HSSL0_ISR_EXI0, 0, IRQ_HSSL0_EXI0_PRIO)
#elif IRQ_HSSL0_EXI0_CAT == IRQ_CAT2
ISR(HSSL0_ISR_EXI0)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();

  /* Call EXI Interrupt funtion - call the HSSL callback function */ 
  Hssl_IsrEXI(HSSL0);
}
#endif
#endif

#endif

#if (IRQ_HSSL1_EXIST == STD_ON)
/******************************************************************************
** Syntax : void HSSL1_ISR_COK0(void)                                        **
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
** Description : Service for COK0 interrupt of HSSL1                         **
**                                                                           **
******************************************************************************/
#if IRQ_HSSL1_COK0_TOS != IRQ_TOS_DMA
#if((IRQ_HSSL1_COK0_PRIO > 0) || (IRQ_HSSL1_COK0_CAT == IRQ_CAT2))
#if((IRQ_HSSL1_COK0_PRIO > 0) && (IRQ_HSSL1_COK0_CAT == IRQ_CAT1))
IFX_INTERRUPT(HSSL1_ISR_COK0, 0, IRQ_HSSL1_COK0_PRIO)
#elif IRQ_HSSL1_COK0_CAT == IRQ_CAT2
ISR(HSSL1_ISR_COK0)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  
  /* Call TX Interrupt funtion - call the HSSL callback function */ 
  Hssl_IsrCOK(HSSL1, 0U);
}
#endif
#endif

/******************************************************************************
** Syntax : void HSSL1_ISR_COK1(void)                                        **
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
** Description : Service for COK1 interrupt of HSSL1                         **
**                                                                           **
******************************************************************************/
#if IRQ_HSSL1_COK1_TOS != IRQ_TOS_DMA
#if((IRQ_HSSL1_COK1_PRIO > 0) || (IRQ_HSSL1_COK1_CAT == IRQ_CAT2))
#if((IRQ_HSSL1_COK1_PRIO > 0) && (IRQ_HSSL1_COK1_CAT == IRQ_CAT1))
IFX_INTERRUPT(HSSL1_ISR_COK1, 0, IRQ_HSSL1_COK1_PRIO)
#elif IRQ_HSSL1_COK1_CAT == IRQ_CAT2
ISR(HSSL1_ISR_COK1)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();

  /* Call TX Interrupt funtion - call the HSSL callback function */ 
   Hssl_IsrCOK(HSSL1, 1U);
}
#endif
#endif

/******************************************************************************
** Syntax : void HSSL1_ISR_COK2(void)                                        **
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
** Description : Service for COK2 interrupt of HSSL1                         **
**                                                                           **
******************************************************************************/
#if IRQ_HSSL1_COK2_TOS != IRQ_TOS_DMA
#if((IRQ_HSSL1_COK2_PRIO > 0) || (IRQ_HSSL1_COK2_CAT == IRQ_CAT2))
#if((IRQ_HSSL1_COK2_PRIO > 0) && (IRQ_HSSL1_COK2_CAT == IRQ_CAT1))
IFX_INTERRUPT(HSSL1_ISR_COK2, 0, IRQ_HSSL1_COK2_PRIO)
#elif IRQ_HSSL1_COK2_CAT == IRQ_CAT2
ISR(HSSL1_ISR_COK2)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();

  /* Call TX Interrupt funtion - call the HSSL callback function */ 
  Hssl_IsrCOK(HSSL1, 2U);
}
#endif
#endif

/******************************************************************************
** Syntax : void HSSL1_ISR_COK3(void)                                        **
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
** Description : Service for COK3 interrupt of HSSL1                         **
**                                                                           **
******************************************************************************/

#if IRQ_HSSL1_COK3_TOS != IRQ_TOS_DMA
#if((IRQ_HSSL1_COK3_PRIO > 0) || (IRQ_HSSL1_COK3_CAT == IRQ_CAT2))
#if((IRQ_HSSL1_COK3_PRIO > 0) && (IRQ_HSSL1_COK3_CAT == IRQ_CAT1))
IFX_INTERRUPT(HSSL1_ISR_COK3, 0, IRQ_HSSL1_COK3_PRIO)
#elif IRQ_HSSL1_COK3_CAT == IRQ_CAT2
ISR(HSSL1_ISR_COK3)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();

  /* Call TX Interrupt funtion - call the HSSL callback function */ 
  Hssl_IsrCOK(HSSL1, 3U);
}
#endif
#endif

/******************************************************************************
** Syntax : void HSSL1_ISR_RDI0(void)                                        **
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
** Description : Service for RDI0 interrupt of HSSL1                         **
**                                                                           **
******************************************************************************/

#if IRQ_HSSL1_RDI0_TOS != IRQ_TOS_DMA
#if((IRQ_HSSL1_RDI0_PRIO > 0) || (IRQ_HSSL1_RDI0_CAT == IRQ_CAT2))
#if((IRQ_HSSL1_RDI0_PRIO > 0) && (IRQ_HSSL1_RDI0_CAT == IRQ_CAT1))
IFX_INTERRUPT(HSSL1_ISR_RDI0, 0, IRQ_HSSL1_RDI0_PRIO)
#elif IRQ_HSSL1_RDI0_CAT == IRQ_CAT2
ISR(HSSL1_ISR_RDI0)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  /* Call RDI Interrupt funtion - call the HSSL callback function */ 
  Hssl_IsrRDI(HSSL1,0U);
}
#endif
#endif
/******************************************************************************
** Syntax : void HSSL1_ISR_RDI1(void)                                        **
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
** Description : Service for RDI1 interrupt of HSSL1                         **
**                                                                           **
******************************************************************************/
#if IRQ_HSSL1_RDI1_TOS != IRQ_TOS_DMA
#if((IRQ_HSSL1_RDI1_PRIO > 0) || (IRQ_HSSL1_RDI1_CAT == IRQ_CAT2))
#if((IRQ_HSSL1_RDI1_PRIO > 0) && (IRQ_HSSL1_RDI1_CAT == IRQ_CAT1))
IFX_INTERRUPT(HSSL1_ISR_RDI1, 0, IRQ_HSSL1_RDI1_PRIO)
#elif IRQ_HSSL1_RDI1_CAT == IRQ_CAT2
ISR(HSSL1_ISR_RDI1)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();

  /* Call RDI Interrupt funtion - call the HSSL callback function */ 
  Hssl_IsrRDI(HSSL1,1U);
}
#endif
#endif

/******************************************************************************
** Syntax : void HSSL1_ISR_RDI2(void)                                        **
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
** Description : Service for RDI2 interrupt of HSSL1                         **
**                                                                           **
******************************************************************************/
#if IRQ_HSSL1_RDI2_TOS != IRQ_TOS_DMA
#if((IRQ_HSSL1_RDI2_PRIO > 0) || (IRQ_HSSL1_RDI2_CAT == IRQ_CAT2))
#if((IRQ_HSSL1_RDI2_PRIO > 0) && (IRQ_HSSL1_RDI2_CAT == IRQ_CAT1))
IFX_INTERRUPT(HSSL1_ISR_RDI2, 0, IRQ_HSSL1_RDI2_PRIO)
#elif IRQ_HSSL1_RDI2_CAT == IRQ_CAT2
ISR(HSSL1_ISR_RDI2)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();

  /* Call RDI Interrupt funtion - call the HSSL callback function */ 
  Hssl_IsrRDI(HSSL1,2U);
}
#endif
#endif

/******************************************************************************
** Syntax : void HSSL1_ISR_RDI3(void)                                        **
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
** Description : Service for RDI3 interrupt of HSSL1                         **
**                                                                           **
******************************************************************************/
#if IRQ_HSSL1_RDI3_TOS != IRQ_TOS_DMA
#if((IRQ_HSSL1_RDI3_PRIO > 0) || (IRQ_HSSL1_RDI3_CAT == IRQ_CAT2))
#if((IRQ_HSSL1_RDI3_PRIO > 0) && (IRQ_HSSL1_RDI3_CAT == IRQ_CAT1))
IFX_INTERRUPT(HSSL1_ISR_RDI3, 0, IRQ_HSSL1_RDI3_PRIO)
#elif IRQ_HSSL1_RDI3_CAT == IRQ_CAT2
ISR(HSSL1_ISR_RDI3)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();

  /* Call RDI Interrupt funtion - call the HSSL callback function */ 
  Hssl_IsrRDI(HSSL1,3U);
}
#endif
#endif

/******************************************************************************
** Syntax : void HSSL1_ISR_ERR0(void)                                        **
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
** Description : Service for Error0 interrupt of HSSL1                       **
**                                                                           **
******************************************************************************/
#if IRQ_HSSL1_ERR0_TOS != IRQ_TOS_DMA
#if((IRQ_HSSL1_ERR0_PRIO > 0) || (IRQ_HSSL1_ERR0_CAT == IRQ_CAT2))
#if((IRQ_HSSL1_ERR0_PRIO > 0) && (IRQ_HSSL1_ERR0_CAT == IRQ_CAT1))
IFX_INTERRUPT(HSSL1_ISR_ERR0, 0, IRQ_HSSL1_ERR0_PRIO)
#elif IRQ_HSSL1_ERR0_CAT == IRQ_CAT2
ISR(HSSL1_ISR_ERR0)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();

  /* Call ERR Interrupt funtion - call the HSSL callback function */ 
  Hssl_IsrError(HSSL1,0U);
}
#endif
#endif

/******************************************************************************
** Syntax : void HSSL1_ISR_ERR1(void)                                        **
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
** Description : Service for Error1 interrupt of HSSL1                       **
**                                                                           **
******************************************************************************/
#if IRQ_HSSL1_ERR1_TOS != IRQ_TOS_DMA
#if((IRQ_HSSL1_ERR1_PRIO > 0) || (IRQ_HSSL1_ERR1_CAT == IRQ_CAT2))
#if((IRQ_HSSL1_ERR1_PRIO > 0) && (IRQ_HSSL1_ERR1_CAT == IRQ_CAT1))
IFX_INTERRUPT(HSSL1_ISR_ERR1, 0, IRQ_HSSL1_ERR1_PRIO)
#elif IRQ_HSSL1_ERR1_CAT == IRQ_CAT2
ISR(HSSL1_ISR_ERR1)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  /* Call ERR Interrupt funtion - call the HSSL callback function */ 
  Hssl_IsrError(HSSL1,1U); 
}
#endif
#endif

/******************************************************************************
** Syntax : void HSSL1_ISR_ERR2(void)                                        **
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
** Description : Service for Error2 interrupt of HSSL1                       **
**                                                                           **
******************************************************************************/
#if IRQ_HSSL1_ERR2_TOS != IRQ_TOS_DMA
#if((IRQ_HSSL1_ERR2_PRIO > 0) || (IRQ_HSSL1_ERR2_CAT == IRQ_CAT2))
#if((IRQ_HSSL1_ERR2_PRIO > 0) && (IRQ_HSSL1_ERR2_CAT == IRQ_CAT1))
IFX_INTERRUPT(HSSL1_ISR_ERR2, 0, IRQ_HSSL1_ERR2_PRIO)
#elif IRQ_HSSL1_ERR2_CAT == IRQ_CAT2
ISR(HSSL1_ISR_ERR2)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();

  /* Call ERR Interrupt funtion - call the HSSL callback function */ 
  Hssl_IsrError(HSSL1,2U); 
}
#endif
#endif

/******************************************************************************
** Syntax : void HSSL1_ISR_ERR3(void)                                        **
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
** Description : Service for Error3 interrupt of HSSL1                       **
**                                                                           **
******************************************************************************/
#if IRQ_HSSL1_ERR3_TOS != IRQ_TOS_DMA
#if((IRQ_HSSL1_ERR3_PRIO > 0) || (IRQ_HSSL1_ERR3_CAT == IRQ_CAT2))
#if((IRQ_HSSL1_ERR3_PRIO > 0) && (IRQ_HSSL1_ERR3_CAT == IRQ_CAT1))
IFX_INTERRUPT(HSSL1_ISR_ERR3, 0, IRQ_HSSL1_ERR3_PRIO)
#elif IRQ_HSSL1_ERR3_CAT == IRQ_CAT2
ISR(HSSL1_ISR_ERR3)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();

  /* Call ERR Interrupt funtion - call the HSSL callback function */ 
  Hssl_IsrError(HSSL1,3U);
}
#endif
#endif

/******************************************************************************
** Syntax : void HSSL0_ISR_TRG0(void)                                        **
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
** Description : Service for Trigger0 interrupt of HSSL0                       **
**                                                                           **
******************************************************************************/
#if IRQ_HSSL1_TRG0_TOS != IRQ_TOS_DMA
#if((IRQ_HSSL1_TRG0_PRIO > 0) || (IRQ_HSSL0_TRG0_CAT == IRQ_CAT2))
#if((IRQ_HSSL1_TRG0_PRIO > 0) && (IRQ_HSSL0_TRG0_CAT == IRQ_CAT1))
IFX_INTERRUPT(HSSL1_ISR_TRG0, 0, IRQ_HSSL1_TRG0_PRIO)
#elif IRQ_HSSL0_TRG0_CAT == IRQ_CAT2
ISR(HSSL1_ISR_TRG0)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();

  /* Call TRG Interrupt funtion - call the HSSL callback function */
  /* HSSL_HANDLE_CALLBACK() */
  Hssl_IsrTrg(HSSL1,0U);
}
#endif
#endif

/******************************************************************************
** Syntax : void HSSL0_ISR_TRG1(void)                                        **
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
** Description : Service for Trigger1 interrupt of HSSL0                       **
**                                                                           **
******************************************************************************/
#if IRQ_HSSL1_TRG1_TOS != IRQ_TOS_DMA
#if((IRQ_HSSL1_TRG1_PRIO > 0) || (IRQ_HSSL0_TRG1_CAT == IRQ_CAT2))
#if((IRQ_HSSL1_TRG1_PRIO > 0) && (IRQ_HSSL0_TRG1_CAT == IRQ_CAT1))
IFX_INTERRUPT(HSSL1_ISR_TRG1, 0, IRQ_HSSL1_TRG1_PRIO)
#elif IRQ_HSSL0_TRG1_CAT == IRQ_CAT2
ISR(HSSL1_ISR_TRG1)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();
  /* Call TRG Interrupt funtion - call the HSSL callback function */
  /* HSSL_HANDLE_CALLBACK() */
  Hssl_IsrTrg(HSSL1,1U);
}
#endif
#endif

/******************************************************************************
** Syntax : void HSSL0_ISR_TRG2(void)                                        **
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
** Description : Service for Trigger2 interrupt of HSSL0                       **
**                                                                           **
******************************************************************************/
#if IRQ_HSSL1_TRG2_TOS != IRQ_TOS_DMA
#if((IRQ_HSSL1_TRG2_PRIO > 0) || (IRQ_HSSL0_TRG2_CAT == IRQ_CAT2))
#if((IRQ_HSSL1_TRG2_PRIO > 0) && (IRQ_HSSL0_TRG2_CAT == IRQ_CAT1))
IFX_INTERRUPT(HSSL1_ISR_TRG2, 0, IRQ_HSSL1_TRG2_PRIO)
#elif IRQ_HSSL0_TRG2_CAT == IRQ_CAT2
ISR(HSSL1_ISR_TRG2)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();

  /* Call TRG Interrupt funtion - call the HSSL callback function */
  /* HSSL_HANDLE_CALLBACK() */
    Hssl_IsrTrg(HSSL1,2U);
}
#endif
#endif

/******************************************************************************
** Syntax : void HSSL0_ISR_TRG3(void)                                        **
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
** Description : Service for Trigger3 interrupt of HSSL0                       **
**                                                                           **
******************************************************************************/
#if IRQ_HSSL1_TRG3_TOS != IRQ_TOS_DMA
#if((IRQ_HSSL1_TRG3_PRIO > 0) || (IRQ_HSSL0_TRG3_CAT == IRQ_CAT2))
#if((IRQ_HSSL1_TRG3_PRIO > 0) && (IRQ_HSSL0_TRG3_CAT == IRQ_CAT1))
IFX_INTERRUPT(HSSL1_ISR_TRG3, 0, IRQ_HSSL1_TRG3_PRIO)
#elif IRQ_HSSL0_TRG3_CAT == IRQ_CAT2
ISR(HSSL1_ISR_TRG3)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();

  /* Call TRG Interrupt funtion - call the HSSL callback function */
  /* HSSL_HANDLE_CALLBACK() */
    Hssl_IsrTrg(HSSL1,3U);
}
#endif
#endif

/******************************************************************************
** Syntax : void HSSL1_ISR_EXI0(void)                                        **
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
** Description : Service for Exception interrupt of HSSL1                    **
**                                                                           **
******************************************************************************/
#if IRQ_HSSL1_EXI0_TOS != IRQ_TOS_DMA
#if((IRQ_HSSL1_EXI0_PRIO > 0) || (IRQ_HSSL1_EXI0_CAT == IRQ_CAT2))
#if((IRQ_HSSL1_EXI0_PRIO > 0) && (IRQ_HSSL1_EXI0_CAT == IRQ_CAT1))
IFX_INTERRUPT(HSSL1_ISR_EXI0, 0, IRQ_HSSL1_EXI0_PRIO)
#elif IRQ_HSSL1_EXI0_CAT == IRQ_CAT2
ISR(HSSL1_ISR_EXI0)
#endif
{
  /* Enable Global Interrupts */
  ENABLE();

  /* Call EXI Interrupt funtion - call the HSSL callback function */ 
  Hssl_IsrEXI(HSSL1);
}
#endif
#endif

#endif