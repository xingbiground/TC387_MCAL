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
**  FILENAME     : Os.c                                                       **
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
**  DESCRIPTION : This file contains                                          **
**                 OS functionality.                                          **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : Yes                                              **
**                                                                            **
*******************************************************************************/
/*[cover parentID={DD8F98D3-2665-43fc-A5BF-05EC9E6B7E26}][/cover] */
/*[cover parentID={A9BBFB04-E13A-42f9-A6F1-FD133B63A7C4}][/cover] */

#include "Os.h"

#ifdef  APP_SW
#if ((APP_SW == TEST_APP) || (APP_SW == DEMO_APP))
#include "Traps.h"
#endif
#endif
#include "IFX_Os.h"
#include "McalLib.h"

/*This counter in incremented when any syscall is called by driver in user mode.
in supervisory mode this will not be called and value will remain 1.*/
uint32 U32g_OsFuncCall_Count = 1;

extern volatile uint32 SFR_Return_Value;
void TRUSTED_Mcal_WriteSafetyEndInitProtReg16\
(volatile void* const RegAddress, const uint16 DataValue)
{
  /*function to enter supervisory mode*/
  /*functionality for WritePeripEndInitProtReg16*/
  #ifdef  APP_SW
  #if ((APP_SW == TEST_APP) || (APP_SW == DEMO_APP))
  SYSCALL(MCAL_CALL_TIN_WRITE_SAFETY_ENDINIT_PROTREG16);
  UNUSED_PARAMETER(RegAddress);
  UNUSED_PARAMETER(DataValue);
  #endif
  #endif
}

void TRUSTED_Mcal_WritePeripEndInitProtReg
( volatile void* const RegAddress, const uint32 DataValue)
{
  /*function to enter supervisory mode*/
  /*functionality for WritePeripEndInitProtReg*/
  #ifdef  APP_SW
  #if ((APP_SW == TEST_APP) || (APP_SW == DEMO_APP))
  U32g_OsFuncCall_Count++;
  SYSCALL(MCAL_CALL_TIN_WRITE_PERIP_ENDINIT);
  UNUSED_PARAMETER(RegAddress);
  UNUSED_PARAMETER(DataValue);
  #endif
  #endif
}
void TRUSTED_Mcal_WriteSafetyEndInitProtReg
( volatile void* const RegAddress, const uint32 DataValue)
{
  /*function to enter supervisory mode*/
  /*functionality for WriteSafetyEndInitProtReg*/
  #ifdef  APP_SW
  #if ((APP_SW == TEST_APP) || (APP_SW == DEMO_APP))
  U32g_OsFuncCall_Count++;
  SYSCALL(MCAL_CALL_TIN_WRITE_SAFETY_ENDINIT);
  UNUSED_PARAMETER(RegAddress);
  UNUSED_PARAMETER(DataValue);
  #endif
  #endif
}

void TRUSTED_Mcal_WriteSafetyEndInitProtRegMask
(volatile void* const RegAdd, const uint32 Data, uint32 Mask)
{
  /*function to enter supervisory mode*/
  /*functionality for WriteSafetyEndInitProtReg*/
  #ifdef  APP_SW
  #if ((APP_SW == TEST_APP) || (APP_SW == DEMO_APP))
  U32g_OsFuncCall_Count++;
  SYSCALL(MCAL_CALL_TIN_WRITE_SAFETY_ENDINIT_MASK);
  UNUSED_PARAMETER(RegAdd);
  UNUSED_PARAMETER(Data);
  UNUSED_PARAMETER(Mask);
  #endif
  #endif
}
void TRUSTED_Mcal_WriteCpuEndInitProtReg
(volatile void* const RegAdd, const uint32 Data)
{
  /*function to enter supervisory mode*/
  /*functionality for WriteCpuEndInitProtReg*/
  #ifdef  APP_SW
  #if ((APP_SW == TEST_APP) || (APP_SW == DEMO_APP))
  U32g_OsFuncCall_Count++;
  SYSCALL(MCAL_CALL_TIN_WRITE_CPU_ENDINIT);
  UNUSED_PARAMETER(RegAdd);
  UNUSED_PARAMETER(Data);
  #endif
  #endif
}
void TRUSTED_Mcal_SetBitAtomic
(volatile void* DataPtr, uint8 BitPos, uint8 BitLen, uint32 Data)
{
  /*function to enter supervisory mode*/
  /*functionality for SetBitAtomic*/
  #ifdef  APP_SW
  #if ((APP_SW == TEST_APP) || (APP_SW == DEMO_APP))
  U32g_OsFuncCall_Count++;
  SYSCALL(MCAL_CALL_TIN_SET_BIT_ATOMIC);
  UNUSED_PARAMETER(DataPtr);
  UNUSED_PARAMETER(BitPos);
  UNUSED_PARAMETER(BitLen);
  UNUSED_PARAMETER(Data);
  #endif
  #endif
}
void osWritePeripheral32
(uint32 Area, volatile void* Address, uint32 value)
{
  /*function to enter supervisory mode*/
  /*functionality for OS_WritePeripheral32*/
  #ifdef  APP_SW
  #if ((APP_SW == TEST_APP) || (APP_SW == DEMO_APP))
  U32g_OsFuncCall_Count++;
  SYSCALL(MCAL_TIN_CALL_WRITE32);
  UNUSED_PARAMETER(Area);
  UNUSED_PARAMETER(Address);
  UNUSED_PARAMETER(value);
  #endif
  #endif
}
uint32 osReadPeripheral32
(uint32 Area, volatile void* Address)
{
  /*function to enter supervisory mode*/
  /*functionality for OS_ReadPeripheral32*/
  volatile uint32 value = 0U;
  #ifdef  APP_SW
  #if ((APP_SW == TEST_APP) || (APP_SW == DEMO_APP))
  U32g_OsFuncCall_Count++;
  SYSCALL(MCAL_TIN_CALL_READ32);
  value = SFR_Return_Value;
  UNUSED_PARAMETER(Area);
  UNUSED_PARAMETER(Address);
  #endif
  #endif
  return value;

}
void osModifyPeripheral32
(uint32 Area, volatile void* Address, uint32 clearmask, uint32 setmask)
{
  /*function to enter supervisory mode*/
  /*functionality for OS_ModifyPeripheral32*/
  #ifdef  APP_SW
  #if ((APP_SW == TEST_APP) || (APP_SW == DEMO_APP))
  U32g_OsFuncCall_Count++;
  SYSCALL(MCAL_TIN_CALL_MODIFY32);
  UNUSED_PARAMETER(Area);
  UNUSED_PARAMETER(Address);
  UNUSED_PARAMETER(clearmask);
  UNUSED_PARAMETER(setmask);
  #endif
  #endif
}

