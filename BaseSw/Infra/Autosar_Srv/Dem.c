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
**  FILENAME     : Dem.c                                                      **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2021-11-09                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Dem Driver source file                                     **
**                                                                            **
**  SPECIFICATION(S) : Specification of Dem Driver,                           **
**                     AUTOSAR Release 4.2.2, AUTOSAR Release 4.4.0           **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Dem.h"
#ifdef  APP_SW
#if (APP_SW == DEMO_APP)
#include "Test_Print.h"
#endif /*#if (APP_SW == DEMO_APP)*/
#if (APP_SW == TEST_APP)
#include "Test_Dem.h"
#endif /*#if (APP_SW == TEST_APP)*/
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
 Dem_ReportErrorStatus

  Function name:  void Dem_ReportErrorStatus(Dem_EventIdType EventId,
  Dem_EventStatusType EventStatus)

  Description:    This is only a function stub for Eg Application
  Parameter:
  Return value:
  Remarks:
*****************************************************************************/
void Dem_ReportErrorStatus(Dem_EventIdType EventId,
                           Dem_EventStatusType EventStatus)
{
  #ifdef  APP_SW
  #if (APP_SW == DEMO_APP)
  if(DEM_EVENT_STATUS_FAILED == EventStatus)
  {
    print_f("\n DEM EVENT FAILED \n");
    print_f("EventId:%d", EventId);
  }
  if(DEM_EVENT_STATUS_PASSED == EventStatus)
  {
    print_f("\n DEM EVENT PASSED \n");
    print_f("EventId:%d", EventId);
  }
  #endif /*#if (APP_SW == DEMO_APP)*/

  #if (APP_SW == TEST_APP)
  #if (AUTOSAR_VERSION_UNDER_TEST == TEST_AUTOSAR422)
  Test_Dem_ReportErrorStatus(EventId, EventStatus);
  #endif /*#if (AUTOSAR_VERSION_UNDER_TEST == TEST_AUTOSAR422)*/
  #endif /*#if (APP_SW == TEST_APP)*/
  #endif
}

/*****************************************************************************
 Dem_SetEventStatus

  Function name:  Std_ReturnType Dem_SetEventStatus(Dem_EventIdType EventId,
  Dem_EventStatusType EventStatus)

  Description:    This is only a function stub for Eg Application
  Parameter:
  Return value:
  Remarks:
*****************************************************************************/
Std_ReturnType Dem_SetEventStatus(Dem_EventIdType EventId,
                           Dem_EventStatusType EventStatus)
{
  Std_ReturnType RetVal = E_OK;
  #ifdef  APP_SW
  #if (APP_SW == DEMO_APP)
  if(DEM_EVENT_STATUS_FAILED == EventStatus)
  {
    print_f("\n DEM EVENT FAILED \n");
    print_f("EventId:%d", EventId);
  }
  if(DEM_EVENT_STATUS_PASSED == EventStatus)
  {
    print_f("\n DEM EVENT PASSED \n");
    print_f("EventId:%d", EventId);
  }
  #endif /*#if (APP_SW == DEMO_APP)*/

  #if (APP_SW == TEST_APP)
  #if (AUTOSAR_VERSION_UNDER_TEST == TEST_AUTOSAR440)
  RetVal = Test_Dem_SetEventStatus(EventId, EventStatus);
  #endif /*#if (AUTOSAR_VERSION_UNDER_TEST == TEST_AUTOSAR440)*/
  #endif /*#if (APP_SW == TEST_APP)*/
  #endif

  return (RetVal);
}

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/
