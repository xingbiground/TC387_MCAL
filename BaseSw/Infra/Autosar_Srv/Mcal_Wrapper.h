/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2023)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : Mcal_Wrapper.h                                             **
**                                                                            **
**  VERSION      : 2.0.0                                                      **
**                                                                            **
**  DATE         : 2023-06-19                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Mcal wrapper header definition file for Dem and Det        **
**                 Runtime Functions                                          **
**                                                                            **
**  SPECIFICATION(S) : AUTOSAR Release 4.2.2, AUTOSAR Release 4.4.0           **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/

#ifndef MCAL_WRAPPER_H
#define MCAL_WRAPPER_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"

#include "Det.h"

#include "Dem.h"

#include "Mcal_Version.h"
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
**                      Global Function Declarations                          **
*******************************************************************************/
extern Std_ReturnType Mcal_Wrapper_Det_ReportRuntimeError(uint16 ModuleId, \
uint8 InstanceId, uint8 ApiId, uint8 ErrorId);

#if (MCAL_AR_VERSION == MCAL_AR_422)
extern void Mcal_Wrapper_Dem_ReportErrorStatus(Dem_EventIdType EventId, \
                                     Dem_EventStatusType EventStatus);

#else
extern Std_ReturnType Mcal_Wrapper_Dem_SetEventStatus(Dem_EventIdType EventId, \
                                    Dem_EventStatusType EventStatus);
#endif

#endif /* end of MCAL_WRAPPER_H */
