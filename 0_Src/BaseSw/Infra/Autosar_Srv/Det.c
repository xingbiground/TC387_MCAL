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
**  FILENAME     : Det.c                                                      **
**                                                                            **
**  VERSION      : 4.0.0                                                      **
**                                                                            **
**  DATE         : 2021-11-08                                                 **
**                                                                            **
**  VARIANT      : NA                                                         **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : DET Driver source file                                     **
**                                                                            **
**  SPECIFICATION(S) : Specification of DET Driver,                           **
**                     AUTOSAR Release 4.2.2, AUTOSAR Release 4.4.0           **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Det.h"
#ifdef  APP_SW
#if (APP_SW == DEMO_APP)
#include "Test_Print.h"
#endif /*#if (APP_SW == DEMO_APP)*/
#if (APP_SW == TEST_APP)
#include "Test_Det.h"
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
Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId)
{
  Std_ReturnType RetVal = E_OK;
  #ifdef  APP_SW
  #if (APP_SW == DEMO_APP)
  print_f("\n DET OCCURED \n ");
  print_f("ModuleId:%d, InstanceId: %d, ApiId:%d, ErrorId:%d"
          , ModuleId, InstanceId, ApiId, ErrorId);
  #endif /* #if (APP_SW == DEMO_APP) */

  #if (APP_SW == TEST_APP)
  RetVal = Test_Det_ReportError(ModuleId, InstanceId, ApiId, ErrorId);
  #endif /*#if (APP_SW == TEST_APP)*/
  #endif
  return (RetVal);
}

Std_ReturnType  Det_ReportRuntimeError(uint16 ModuleId, uint8  InstanceId, uint8 ApiId,
                             uint8  ErrorId)
{
  Std_ReturnType RetVal = E_OK;
  #ifdef  APP_SW
  #if (APP_SW == DEMO_APP)
  print_f("\n Run Time Error OCCURED \n ");
  print_f("ModuleId:%d, InstanceId: %d, ApiId:%d, ErrorId:%d"
          , ModuleId, InstanceId, ApiId, ErrorId);
  #endif /* #if (APP_SW == DEMO_APP) */

  #if (APP_SW == TEST_APP)
  RetVal = Test_Det_ReportRuntimeError(ModuleId, InstanceId, ApiId, ErrorId);
  #endif /*#if (APP_SW == TEST_APP)*/
  #endif
  return (RetVal);
}

Std_ReturnType  Det_ReportTransientFault(uint16 ModuleId, uint8  InstanceId, uint8 ApiId,
                             uint8  ErrorId)
{
  Std_ReturnType RetVal = E_OK;
  #ifdef  APP_SW
  #if (APP_SW == DEMO_APP)
  print_f("\n Transient fault OCCURED \n ");
  print_f("ModuleId:%d, InstanceId: %d, ApiId:%d, ErrorId:%d"
          , ModuleId, InstanceId, ApiId, ErrorId);
  #endif /* #if (APP_SW == DEMO_APP) */

  #if (APP_SW == TEST_APP)
  RetVal = Test_Det_ReportTransientFault(ModuleId, InstanceId, ApiId, ErrorId);
  #endif /*#if (APP_SW == TEST_APP)*/
  #endif
  return (RetVal);
}
