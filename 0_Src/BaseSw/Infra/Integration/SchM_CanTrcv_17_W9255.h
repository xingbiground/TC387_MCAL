/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2020)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : SchM_CanTrcv_17_W9255.h                                    **
**                                                                            **
**  VERSION      : 3.0.0                                                      **
**                                                                            **
**  DATE         : 2020-10-14                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY : [cover parentID={979A163F-4653-474b-A72A-A1A3EF642F47}]    **
**                                                                            **
**  DESCRIPTION  : SchM file for CanTrcv_17_W9255 driver                      **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of RTE, AUTOSAR Release 4.2.2 and        **
**                                          AUTOSAR Release 4.4.0             **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
/* [cover parentID={CFC8F379-8006-46cb-A618-C485ED5235C3}] [/cover] */
#ifndef CANTRCV_17_W9255_SCHM_H
#define CANTRCV_17_W9255_SCHM_H

/* [cover parentID={E449CB8B-015C-4736-9989-A49B9718750B}] */
extern void SchM_Enter_CanTrcv_17_W9255_SpiStatusUpdate(void);
extern void SchM_Exit_CanTrcv_17_W9255_SpiStatusUpdate(void);

/******************************************************************************
** Syntax          : void CanTrcv_17_W9255_MainFunction ( void )             **
**                                                                           **
** Service ID      : 0x06                                                    **
**                                                                           **
** Sync/Async      : Synchronous                                             **
**                                                                           **
** Reentrancy      : Non-Reentrant                                           **
**                                                                           **
** Parameters (in) : None                                                    **
**                                                                           **
** Parameters (out): None                                                    **
**                                                                           **
** Return value    : None                                                    **
**                                                                           **
** Description     : This API scans all transceiver channels in Stand-by     **
**                   and Sleep modes for wake up events and sets a wake-up   **
**                   event flag to perform these events.                     **
**                                                                           **
******************************************************************************/

extern void CanTrcv_17_W9255_MainFunction(void);

#endif /* CANTRCV_17_W9255_SCHM_H */
