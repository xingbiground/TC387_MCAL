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
**  FILENAME  : Compiler.h                                                    **
**                                                                            **
**  VERSION   : 13.0.0                                                        **
**                                                                            **
**  DATE      : 2020-10-13                                                    **
**                                                                            **
**  VARIANT   : NA                                                            **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID={FB97B5EA-8796-4991-B969-37114769C0BA}]    **
**                                                                            **
**  DESCRIPTION  : Compiler Abstraction Macros                                **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : AUTOSAR_SWS_CompilerAbstraction                        **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef COMPILER_H
#define COMPILER_H

/******************************************************************************
**                      Includes                                             **
******************************************************************************/
#include "Compiler_Cfg.h"

/******************************************************************************
**                      Global Macro Definitions                             **
******************************************************************************/
/*
 * Vendor ID of the dedicated implementation of this module according
 * to the AUTOSAR vendor list
 */
#define COMPILER_VENDOR_ID        (17u)

#if defined(__HIGHTEC__)
/* [cover parentID={7B6352C2-6B66-4cb3-A808-0CD29C03840E}] [/cover] */
#define _GNU_C_TRICORE_ 1U
/*
 * HIGHTEC V4.9.4.1
 */

#endif

#if defined (__TASKING__)
/* [cover parentID={18A1A871-0156-41b0-BAA1-57AB84C69ADB}] [/cover] */
#define _TASKING_C_TRICORE_ 1U
/*
 * TASKING V6.3R1P2
 */

#endif

#if defined(__DCC__)
/* [cover parentID={B16A5AFC-6E29-4bc4-996A-07376B94CA7B}] [/cover] */
#define _DIABDATA_C_TRICORE_ 1U
/*
 * WINDRIVER 5.9.7.0
 */

#endif

#if defined (__ghs__)
/* [cover parentID={098D039A-119A-46ee-BD68-09DB9230A71D}] [/cover] */
#define _GHS_C_TRICORE_ 1U
/*
 * GREEN HILLS V2018.1.5
 */

#endif

/*used for local non static variables*/
/* [cover parentID={FDC715B2-5915-4722-8606-5EC32B1EF450}] [/cover] */
#define AUTOMATIC

/* [cover parentID={C81F5B6B-AB18-4286-BCED-321435DA5608}] [/cover] */
#define TYPEDEF

/* [cover parentID={3AC610AD-FDF1-4c6f-96B4-7DB9715CE78A}] [/cover] */
#define NULL_PTR ((void *)0)

/*abstraction of the keyword inline in functions with static scope*/
#ifdef _GNU_C_TRICORE_

#ifndef INLINE
/* [cover parentID={3927BBA9-BF8E-41fd-B4E1-D7335F86093E}] [/cover] */
#define INLINE      __inline__
#endif

#ifndef LOCAL_INLINE
/* [cover parentID={79371FA6-DD93-4a09-8473-26642DDB5CF8}] [/cover] */
#define LOCAL_INLINE    static __inline__
#endif

#endif

#ifdef _TASKING_C_TRICORE_

#ifndef INLINE
#define INLINE      inline
#endif

#ifndef LOCAL_INLINE
#define LOCAL_INLINE    static inline
#endif

#endif

#ifdef _DIABDATA_C_TRICORE_

#ifndef INLINE
#define INLINE      __inline__
#endif

#ifndef LOCAL_INLINE
#define LOCAL_INLINE  static __inline__
#endif

#endif

#ifdef _GHS_C_TRICORE_

#ifndef INLINE
#define INLINE     __inline__
#endif

#ifndef LOCAL_INLINE
#define LOCAL_INLINE   static inline
#endif

#endif


/* Macros for compiler abstraction for declaration of variables,
constansts and functions*/

/* memclass is not used */
/* [cover parentID={9508C3F5-7C4E-45b8-A333-C83EF5657B28}] [/cover] */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined to comply
   with the AUTOSAR standard. This macro is not used in MCAL.*/
#define FUNC(rettype, memclass) rettype

/* memclass and ptrclass is not used */
/* [cover parentID={3D1E4249-7935-442a-BA40-B52F61DAD64C}] [/cover] */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined to comply
   with the AUTOSAR standard. This macro is not used in MCAL.*/
#define FUNC_P2CONST(rettype, ptrclass, memclass) const rettype *

/* memclass and ptrclass is not used */
/* [cover parentID={9225848B-5C67-430f-9197-FC503F59C857}] [/cover] */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined to comply
   with the AUTOSAR standard. This macro is not used in MCAL.*/
#define FUNC_P2VAR(rettype, ptrclass, memclass) rettype *

/* memclass and ptrclass is not used */
/* [cover parentID={27BD74E0-90BF-4343-A466-E089897CA66E}] [/cover] */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined to comply
   with the AUTOSAR standard. This macro is not used in MCAL.*/
#define P2VAR(ptrtype, memclass, ptrclass) ptrtype *

/* memclass and ptrclass is not used */
/* [cover parentID={F71EC95A-5ABD-4cd7-A676-3151C431A05F}] [/cover] */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined to comply
   with the AUTOSAR standard. This macro is not used in MCAL.*/
#define P2CONST(ptrtype, memclass, ptrclass) const ptrtype *

/* memclass and ptrclass is not used */
/* [cover parentID={E7D5109E-369A-47b6-883C-E0DAD4DB73C1}] [/cover] */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined to comply
   with the AUTOSAR standard. This macro is not used in MCAL.*/
#define CONSTP2VAR(ptrtype, memclass, ptrclass) ptrtype * const

/* memclass and ptrclass is not used */
/* [cover parentID={FCF10740-E5F5-4537-B508-A760A975204C}] [/cover] */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined to comply
   with the AUTOSAR standard. This macro is not used in MCAL.*/
#define CONSTP2CONST(ptrtype, memclass, ptrclass) const ptrtype * const

/* ptrclass is not used */
/* [cover parentID={1F5C1850-CDDF-49c8-BFE3-0A8A67481CAF}] [/cover] */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined to comply
   with the AUTOSAR standard. This macro is not used in MCAL.*/
#define P2FUNC(rettype, ptrclass, fctname) rettype (* fctname)

/* ptrclass is not used */
/* [cover parentID={A5BE5D1C-8BC6-4a2d-8DC5-E5AD324ADB27}] [/cover] */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined to comply
   with the AUTOSAR standard. This macro is not used in MCAL.*/
#define CONSTP2FUNC(rettype, ptrclass, fctname) rettype (* const fctname)

/* memclass is not used */
/* [cover parentID={F2AE0154-D544-44e5-B0B9-283C59F52F56}] [/cover] */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined to comply
   with the AUTOSAR standard. This macro is not used in MCAL.*/
#define CONST(type, memclass) const type

/* memclass is not used */
/* [cover parentID={CDC76B1F-E7D9-4571-9C12-7780F7FC8A39}] [/cover] */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined to comply
   with the AUTOSAR standard. This macro is not used in MCAL.*/
#define VAR(type, memclass) type

/******************************************************************************
**                      Global Type Definitions                              **
******************************************************************************/

/******************************************************************************
**                      Global Constant Declarations                         **
******************************************************************************/

/******************************************************************************
**                      Global Variable Declarations                         **
******************************************************************************/

/******************************************************************************
**                      Global Function Declarations                         **
******************************************************************************/
#endif /* } COMPILER_H  */

