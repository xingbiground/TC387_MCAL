/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2018)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : Os.h                                                       **
**                                                                            **
**  VERSION      : 2.0.0                                                      **
**                                                                            **
**  DATE         : 2018-03-28                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION : This file contains OS functionality.                        **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
#include "Std_Types.h"
/*This counter in incremented when any syscall is called by driver in user mode.
in supervisory mode this will not be called and value will remain 1.*/
extern uint32 U32g_OsFuncCall_Count;
extern void TRUSTED_Mcal_WriteSafetyEndInitProtReg16\
(volatile void* const RegAdd, const uint16 Data);
/* Extern declaration of Trusted APIs*/
extern void TRUSTED_Mcal_WritePeripEndInitProtReg\
(volatile void* const RegAdd, const uint32 Data);
extern void TRUSTED_Mcal_WriteSafetyEndInitProtReg\
(volatile void* const RegAdd, const uint32 Data);
extern void TRUSTED_Mcal_WriteSafetyEndInitProtRegMask\
(volatile void* const RegAdd, const uint32 Data, uint32 Mask);
extern void TRUSTED_Mcal_WriteCpuEndInitProtReg\
(volatile void* const RegAdd, const uint32 Data);
extern void TRUSTED_Mcal_SetBitAtomic(volatile void* DataPtr, uint8 BitPos, \
                                      uint8 BitLen, uint32 Data);
extern void osWritePeripheral32\
(uint32 Area, volatile void* Address, uint32 value);
extern uint32 osReadPeripheral32\
(uint32 Area, volatile void* Address);
extern void osModifyPeripheral32\
(uint32 Area, volatile void* Address, uint32 clearmask, uint32 setmask);

