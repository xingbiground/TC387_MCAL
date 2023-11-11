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
**  FILENAME     : Mcal_Wrapper.c                                             **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2023-04-03                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Mcal Wrapper source file for Det Runtime and Dem functions **
**                 definitions                                                **
**                                                                            **
**  SPECIFICATION(S) : AUTOSAR Release 4.2.2, AUTOSAR Release 4.4.0           **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Mcal_Wrapper.h"

#ifndef DEM_AR_RELEASE_MAJOR_VERSION
  #error "DEM_AR_RELEASE_MAJOR_VERSION is not defined."
#endif

#if ( DEM_AR_RELEASE_MAJOR_VERSION != 4U )
  #error "DEM_AR_RELEASE_MAJOR_VERSION does not match."
#endif

#ifndef DET_AR_RELEASE_MAJOR_VERSION
  #error "DET_AR_RELEASE_MAJOR_VERSION is not defined."
#endif

#if (DET_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION)
  #error "DET_AR_RELEASE_MAJOR_VERSION does not match."
#endif

/*******************************************************************************
**                      Imported Compiler Switch Check                        **
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
**                      Global Function Definitions                           **
*******************************************************************************/

/*****************************************************************************
 Mcal_Wrapper_Det_ReportRuntimeError

  Function name:  Std_ReturnType Mcal_Wrapper_Det_ReportRuntimeError(
      uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId)

  Description:    Run time report error
  Parameter:
  Return value:
  Remarks:
*****************************************************************************/
Std_ReturnType Mcal_Wrapper_Det_ReportRuntimeError(uint16 ModuleId, \
                                   uint8 InstanceId, uint8 ApiId, uint8 ErrorId)
{

  /* The current call is for DET module interface, it can be replaced
  with a user defined safety interface as well */
  return Det_ReportRuntimeError(ModuleId, InstanceId, ApiId, ErrorId);

}
#if (MCAL_AR_VERSION == MCAL_AR_422)
/*****************************************************************************
 Mcal_Wrapper_Dem_ReportErrorStatus

  Function name:  void Mcal_Wrapper_Dem_ReportErrorStatus(Dem_EventIdType \
  EventId, Dem_EventStatusType EventStatus)

  Description:    Dem report error
  Parameter:
  Return value:
  Remarks:
*****************************************************************************/
void Mcal_Wrapper_Dem_ReportErrorStatus(Dem_EventIdType EventId, \
                                    Dem_EventStatusType EventStatus)
{
  /* The current call is for DEM module interface, it can be replaced 
  with a user defined safety interface as well */ 
  Dem_ReportErrorStatus(EventId, EventStatus);
}
#else
/*****************************************************************************
 Mcal_Wrapper_Dem_SetEventStatus

  Function name: Std_ReturnType Mcal_Wrapper_Dem_SetEventStatus(Dem_EventIdType \
  EventId, Dem_EventStatusType EventStatus)

  Description:    Dem report error
  Parameter:
  Return value:
  Remarks:
*****************************************************************************/
Std_ReturnType Mcal_Wrapper_Dem_SetEventStatus(Dem_EventIdType EventId, \
                                    Dem_EventStatusType EventStatus)
{
  /* The current call is for DEM module interface, it can be replaced
  with a user defined safety interface as well */
  return Dem_SetEventStatus ( (Dem_EventIdType) EventId, \
                                    (Dem_EventStatusType) EventStatus);
}
#endif
/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/
