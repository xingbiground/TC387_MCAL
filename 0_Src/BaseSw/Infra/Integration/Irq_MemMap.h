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
**  FILENAME     : Irq_MemMap.h                                               **
**                                                                            **
**  VERSION      : 0.0.1                                                      **
**                                                                            **
**  DATE         : 2016-08-17                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Memory Mapping file for Irq driver                         **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
/*
The name part {_safety} shall contain the safety integrity level with at most
one of the strings QM, ASIL_A, ASIL_B, ASIL_C, ASIL_D. In case of QM the
name part may be omitted.
The name part {_coreScope} shall contain the core scope qualification with at
most one of the strings GLOBAL, LOCAL. In case of GLOBAL the name part
may be omitted.
*/

#define MEMMAP_ERROR

#if ((!defined(APP_SW)) || (APP_SW == DEMO_APP) || (APP_SW == TEST_APP))
/*DATA Section*/
/*To be used for all global or static variables.*/

/* Code Sections */
/*
To be used for mapping code to application block, boot block, external flash
etc.
{codePeriod} is the typical period time value and unit of the ExecutableEntitys
in this MemorySection. The name part _{codePeriod} is optional. Units are:
- US microseconds
- MS milli second
- S second
For example: 100US, 400US, 1MS, 5MS, 10MS, 20MS, 100MS, 1S
*/
#if defined IRQ_START_SEC_CODE_QM_GLOBAL
#ifdef _TASKING_C_TRICORE_
#pragma section code "Code.Cpu0"
//#pragma align 4
#elif defined _GNU_C_TRICORE_
#pragma section "Code.Cpu0" ax
#elif defined _DIABDATA_C_TRICORE_
#pragma section CODE "Code.Cpu0" RX
#endif
#undef IRQ_START_SEC_CODE_QM_GLOBAL
#undef MEMMAP_ERROR

#elif defined IRQ_STOP_SEC_CODE_QM_GLOBAL

#ifdef _TASKING_C_TRICORE_
#if(_TASKING_C_TRICORE_ == 1U)
#pragma section code restore
#endif
#elif defined _GNU_C_TRICORE_
#if(_GNU_C_TRICORE_ == 1U)
#pragma section
#endif
#endif

#undef IRQ_STOP_SEC_CODE_QM_GLOBAL
#undef MEMMAP_ERROR

#endif

#else /*#if ((!defined(APP_SW)) || (APP_SW == DEMO_APP) || (APP_SW == TEST_APP))*/

/*DATA Section*/
/*To be used for all global or static variables.*/

/* Code Sections */
/*
To be used for mapping code to application block, boot block, external flash
etc.
{codePeriod} is the typical period time value and unit of the ExecutableEntitys
in this MemorySection. The name part _{codePeriod} is optional. Units are:
- US microseconds
- MS milli second
- S second
For example: 100US, 400US, 1MS, 5MS, 10MS, 20MS, 100MS, 1S
*/
#if defined IRQ_START_SEC_CODE_QM_GLOBAL


#undef IRQ_START_SEC_CODE_QM_GLOBAL
#undef MEMMAP_ERROR

#elif defined IRQ_STOP_SEC_CODE_QM_GLOBAL


#undef IRQ_STOP_SEC_CODE_QM_GLOBAL
#undef MEMMAP_ERROR

#endif

#endif /*#if ((!defined(APP_SW)) || (APP_SW == DEMO_APP) || (APP_SW == TEST_APP))*/

#if defined MEMMAP_ERROR
#error "Irq_MemMap.h, wrong pragma command"
#endif
