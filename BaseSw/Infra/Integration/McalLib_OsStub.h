/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2019)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : McalLib_OsStub.h                                           **
**                                                                            **
**  VERSION      : 6.0.0                                                      **
**                                                                            **
**  DATE         : 2019-05-30                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY : [cover parentID={DD8F98D3-2665-43fc-A5BF-05EC9E6B7E26},    ** 
**                                 {A9BBFB04-E13A-42f9-A6F1-FD133B63A7C4}]    **
**                                                                            **
**  DESCRIPTION  : MCAL Library source file                                   **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
#ifndef MCAL_OSSTUB_H
#define MCAL_OSSTUB_H
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Os.h"
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/


#define  MCALLIB_WRITESAFETYENDINITPROTREG16(RegAdd,Data)\
                              TRUSTED_Mcal_WriteSafetyEndInitProtReg16(RegAdd,Data)
/* CPU ,Peripheral, Safety EndInit Protection functions always runs in SV mode*/
/*******************************************************************************
** Traceability     : [coverparentID={DD8F98D3-2665-43fc-A5BF-05EC9E6B7E26}]  **
**                                                                            **
** Syntax           : MCAL_LIB_WRITEPERIPENDINITPROTREG(RegAdd,Data)          **
**                                                                            **
** Description      : This API like macro will invoke a OS trusted call       **
                      defined in the upper layer in User Mode.                **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : NA                                                      **
**                                                                            **
** Reentrancy       : NA                                                      **
**                                                                            **
** Parameters(in)   : RegAdd - Endinit protected Register Address             **
**                    Data - Data to be written into endinit Register         **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
/* MISRA2012_RULE_4_9_JUSTIFICATION: No side effects foreseen by violating
 * this MISRA rule. */
#define  MCAL_LIB_WRITEPERIPENDINITPROTREG(RegAdd,Data)\
                              TRUSTED_Mcal_WritePeripEndInitProtReg(RegAdd,Data)
/*******************************************************************************
** Traceability     :[coverparentID={DD8F98D3-2665-43fc-A5BF-05EC9E6B7E26}]   **
**                                                                            **
** Syntax           : MCAL_LIB_WRITECPUENDINITPROTREG(RegAdd,Data)            **
**                                                                            **
** Description      : This API like macro will invoke a OS trusted call       **
                      defined in the upper layer in User Mode.                **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : NA                                                      **
**                                                                            **
** Reentrancy       : NA                                                      **
**                                                                            **
** Parameters(in)   : RegAdd - Endinit protected Register Address             **
**                    Data - Data to be written into endinit Register         **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
/* MISRA2012_RULE_4_9_JUSTIFICATION: No side effects foreseen by violating
 * this MISRA rule. */
#define  MCAL_LIB_WRITECPUENDINITPROTREG(RegAdd,Data)\
                              TRUSTED_Mcal_WriteCpuEndInitProtReg(RegAdd,Data)
/*******************************************************************************
** Traceability     : [coverparentID={DD8F98D3-2665-43fc-A5BF-05EC9E6B7E26}]  **
**                                                                            **
** Syntax           : MCAL_LIB_WRITESAFETYENDINITPROTREG(RegAdd,Data)         **
**                                                                            **
** Description      : This API like macro will invoke a OS trusted call       **
                      defined in the upper layer in User Mode.                **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : NA                                                      **
**                                                                            **
** Reentrancy       : NA                                                      **
**                                                                            **
** Parameters(in)   : RegAdd - Endinit protected Register Address             **
**                    Data - Data to be written into endinit Register         **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
/* MISRA2012_RULE_4_9_JUSTIFICATION: No side effects foreseen by violating
 * this MISRA rule. */
#define  MCAL_LIB_WRITESAFETYENDINITPROTREG(RegAdd,Data)\
                             TRUSTED_Mcal_WriteSafetyEndInitProtReg(RegAdd,Data)
/*******************************************************************************
** Traceability     :[coverparentID={DD8F98D3-2665-43fc-A5BF-05EC9E6B7E26}]   **
**                                                                            **
** Syntax           :MCAL_LIB_WRITESAFETYENDINITPROTREGMASK(RegAdd,Data,Mask) **
**                                                                            **
** Description      : This API like macro will invoke a OS trusted call       **
                      defined in the upper layer in User Mode.                **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : NA                                                      **
**                                                                            **
** Reentrancy       : NA                                                      **
**                                                                            **
** Parameters(in)   : RegAdd - Endinit protected Register Address             **
**                    Data - Data to be written into endinit Register         **
**                    Mask - Mask to Update Specific register bits            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
/* MISRA2012_RULE_4_9_JUSTIFICATION: No side effects foreseen by violating
 * this MISRA rule. */
#define  MCAL_LIB_WRITESAFETYENDINITPROTREGMASK(RegAdd,Data,Mask)\
                    TRUSTED_Mcal_WriteSafetyEndInitProtRegMask(RegAdd,Data,Mask)
/*******************************************************************************
** Traceability     : [coverparentID={DD8F98D3-2665-43fc-A5BF-05EC9E6B7E26}]  **
**                                                                            **
** Syntax           :MCAL_LIB_SETBITATOMIC(DataPtr,BitPos,BitLen,Data)        **
**                                                                            **
** Description      : This API like macro will invoke a OS trusted call       **
                      defined in the upper layer in User Mode.                **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : NA                                                      **
**                                                                            **
** Reentrancy       : NA                                                      **
**                                                                            **
** Parameters(in)   : DataPtr - Address of the register/variable that is to   **
**                              be modified.                                  **
**                    BitPos - Starting bit position where Data needs to      **
**                             be placed.                                     **
**                    BitLen - The length of the Data, starting the BitPos,   **
**                             which is to be replaced at location            **
**                             pointed by pointer DataPtr.                    **
**                    Data - Value that is to be modified in *DataPtr         **
** Parameters (out) : DataPtr - Address of the register/variable that         **
**                              got modified.                                 **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
/* MISRA2012_RULE_4_9_JUSTIFICATION: No side effects foreseen by violating
 * this MISRA rule. */
#define  MCAL_LIB_SETBITATOMIC(DataPtr,BitPos,BitLen,Data)\
                           TRUSTED_Mcal_SetBitAtomic(DataPtr,BitPos,BitLen,Data)
/*******************************************************************************
** Traceability     : [coverparentID={DD8F98D3-2665-43fc-A5BF-05EC9E6B7E26}]  **
**                                                                            **
** Syntax           : MCAL_SFR_OS_WRITE32(area,reg,value)                     **
**                                                                            **
** Description      : Performs accessing checks(There should be means         **
**                    to handle library functions which are supposed to run   **
**                    in "no user mode" (supervisor).                         **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : NA                                                      **
**                                                                            **
** Reentrancy       : NA                                                      **
**                                                                            **
** Parameters(in)   : area-Identifier of peripheral regions to the read from  **
**                    reg - Register where the value to be written            **
**                    value - Value to be written                             **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
/* MISRA2012_RULE_4_9_JUSTIFICATION: No side effects foreseen by violating
 * this MISRA rule. */
/* OS Read, Write, Modify */
#define MCAL_SFR_OS_WRITE32(area,reg,value)\
    osWritePeripheral32((area),(reg),(value))
/*******************************************************************************
** Traceability     : [coverparentID={DD8F98D3-2665-43fc-A5BF-05EC9E6B7E26}]  **
**                                                                            **
** Syntax           : MCAL_SFR_OS_READ32(area,reg)                            **
**                                                                            **
** Description      : Performs accessing checks(There should be means         **
**                    to handle library functions which are supposed to run   **
**                    in "no user mode" (supervisor).                         **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : NA                                                      **
**                                                                            **
** Reentrancy       : NA                                                      **
**                                                                            **
** Parameters(in)   : area -Identifier of peripheral regions to the read from **
**                    reg - Register where the value to be written            **
**                                                                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
#define MCAL_SFR_OS_READ32(area,reg)\
    osReadPeripheral32((area),(reg))
/*******************************************************************************
** Traceability     : [coverparentID={DD8F98D3-2665-43fc-A5BF-05EC9E6B7E26}]  **
**                                                                            **
** Syntax           : MCAL_SFR_OS_MODIFY32(area,reg,clearmask,setmask)        **
**                                                                            **
** Description      : Performs accessing checks(There should be means         **
**                    to handle library functions which are supposed to run   **
**                    in "no user mode" (supervisor).                         **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : NA                                                      **
**                                                                            **
** Reentrancy       : NA                                                      **
**                                                                            **
** Parameters(in)   : area -Identifier of peripheral regions to the read from **
**                    reg - Register where the value to be modify             **
**                    clearmask - Value to indicate which register bits need  **
**                                to be clear.                                **
**                    setmask - Value to indicate which register bits need    **
**                    to be updated.                                          **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
#define MCAL_SFR_OS_MODIFY32(area,reg,clearmask,setmask)\
  osModifyPeripheral32((area),(reg),\
           (clearmask),(setmask))

#endif /* MCAL_OSSTUB_H  */
