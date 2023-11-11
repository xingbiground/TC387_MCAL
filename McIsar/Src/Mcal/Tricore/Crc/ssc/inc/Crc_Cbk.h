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
**  FILENAME     : Crc_Cbk.h                                                  **
**                                                                            **
**  VERSION      : 3.0.0                                                      **
**                                                                            **
**  DATE         : 2021-03-01                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY :                                                            **
**                                                                            **
**  DESCRIPTION  : Crc Driver Callback header definition file                 **
**                                                                            **
**  SPECIFICATION(S) : Specification of Crc Driver, AUTOSAR Release 4.2.2     **
**                   : Specification of Crc Driver, AUTOSAR Release 4.4.0     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/* [cover parentID={1FD81F21-0E56-4106-AE5E-A8A09B2AD468}]
[/cover] */
#ifndef  CRC_CBK_H
#define  CRC_CBK_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Crc Module header file */
#include "Crc.h"


/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

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
**                      Callback Function Declarations                        **
*******************************************************************************/
#define CRC_START_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"

#if (CRC_DMA_MAX_CHANNELS > 0U)
/*******************************************************************************
** Traceability   : [cover parentID={8D6C28A0-F00C-468b-A87E-2ECEFF351C9B}]   **
**                                                                            **
** Syntax         : extern void Crc_DmaTransferIsr                            **
**                  (const uint8 Channel, const uint32 lEvent)                **
**                                                                            **
** Description    : Interrupt service routine called on an event.             **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : Channel -  Channel Number                                 **
**                  Event   -  The Event of the DMA channel                   **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
extern void Crc_DmaTransferIsr
(
  const uint8 Channel,
  const uint32 Event
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Crc_DmaTransferIsr(Crc_DataPtr, Event) \
                                  (ERROR_Crc_DmaTransferIsr_API_IS_NOT_SELECTED)
#endif

#if (CRC_DMA_MAX_CHANNELS > 0U)
/*******************************************************************************
** Traceability   : [cover parentID={DFAF0027-96DB-40c9-AA49-EDE2BA7C4C12}]   **
**                                                                            **
** Syntax         : extern void Crc_DmaErrorIsr                               **
**                  (const uint8 Channel, const uint32 Event)                 **
**                                                                            **
** Description    : Interrupt service routine called on an event.             **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : Channel -  Channel Number                                 **
**                  Event   -  The Event of the DMA channel                   **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
extern void Crc_DmaErrorIsr
(
  const uint8 Channel,
  const uint32 Event
);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Crc_DmaErrorIsr(Crc_DataPtr, Event)\
                                     (ERROR_Crc_DmaErrorIsr_API_IS_NOT_SELECTED)
#endif

/******************************************************************************/
#define CRC_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Crc_MemMap.h"
/*******************************************************************************
**                      Global In-line Function Definitions                   **
*******************************************************************************/

#endif /* CRC_CBK_H */
