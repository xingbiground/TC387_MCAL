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
**  FILENAME  : Stm_MemMap.h                                                  **
**                                                                            **
**  VERSION   :  2.0.0                                                        **
**                                                                            **
**  DATE      : 12/09/2018                                                    **
**                                                                            **
**  VARIANT   : NA                                                            **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY :                                                            **
**                                                                            **
**  DESCRIPTION  : This file contains the mapping of Memory Section           **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of STM Driver,                           **
**   AUTOSAR Release <4.2.2>                                                  **
**                                                                            **
**  MAY BE CHANGED BY USER : Yes                                              **
**                                                                            **
*******************************************************************************/
#define MEMMAP_ERROR
#if ((APP_SW == DEMO_APP) || (APP_SW == TEST_APP))
/*DATA Section*/
/*To be used for all global or static variables.*/
/*Variable to be cleared at startup or reset is palced here - .bss*/
#if defined STM_START_SEC_VAR_CLEARED_QM_CORE0_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma section farbss "ClearedData.Cpu0.Unspecified"
#pragma align 4
#elif defined _GNU_C_TRICORE_
#pragma section "ClearedData.Cpu0.Unspecified" aw 4
#elif defined _GHS_C_TRICORE_
#pragma ghs section bss = ".ClearedData.Cpu0.Unspecified"
#elif defined _DIABDATA_C_TRICORE_
#pragma section DATA "InitData.Cpu0.Unspecified" "ClearedData.Cpu0.Unspecified" far-absolute RW
#endif
#undef  STM_START_SEC_VAR_CLEARED_QM_CORE0_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined STM_STOP_SEC_VAR_CLEARED_QM_CORE0_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma align restore
#pragma section farbss restore
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma section
#endif
#undef  STM_STOP_SEC_VAR_CLEARED_QM_CORE0_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined STM_START_SEC_VAR_CLEARED_QM_CORE1_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma section farbss "ClearedData.Cpu1.Unspecified"
#pragma align 4
#elif defined _GNU_C_TRICORE_
#pragma section "ClearedData.Cpu1.Unspecified" aw 4
#elif defined _GHS_C_TRICORE_
#pragma ghs section bss = ".ClearedData.Cpu1.Unspecified"
#elif defined _DIABDATA_C_TRICORE_
#pragma section DATA "InitData.Cpu1.Unspecified" "ClearedData.Cpu1.Unspecified" far-absolute RW
#endif
#undef  STM_START_SEC_VAR_CLEARED_QM_CORE1_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined STM_STOP_SEC_VAR_CLEARED_QM_CORE1_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma align restore
#pragma section farbss restore
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma section
#endif
#undef  STM_STOP_SEC_VAR_CLEARED_QM_CORE1_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined STM_START_SEC_VAR_CLEARED_QM_CORE2_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma section farbss "ClearedData.Cpu2.Unspecified"
#pragma align 4
#elif defined _GNU_C_TRICORE_
#pragma section "ClearedData.Cpu2.Unspecified" aw 4
#elif defined _GHS_C_TRICORE_
#pragma ghs section bss = ".ClearedData.Cpu2.Unspecified"
#elif defined _DIABDATA_C_TRICORE_
#pragma section DATA "InitData.Cpu2.Unspecified" "ClearedData.Cpu2.Unspecified" far-absolute RW
#endif
#undef  STM_START_SEC_VAR_CLEARED_QM_CORE2_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined STM_STOP_SEC_VAR_CLEARED_QM_CORE2_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma align restore
#pragma section farbss restore
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma section
#endif
#undef  STM_STOP_SEC_VAR_CLEARED_QM_CORE2_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined STM_START_SEC_VAR_CLEARED_QM_CORE3_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma section farbss "ClearedData.Cpu3.Unspecified"
#pragma align 4
#elif defined _GNU_C_TRICORE_
#pragma section "ClearedData.Cpu3.Unspecified" aw 4
#elif defined _GHS_C_TRICORE_
#pragma ghs section bss = ".ClearedData.Cpu3.Unspecified"
#elif defined _DIABDATA_C_TRICORE_
#pragma section DATA "InitData.Cpu3.Unspecified" "ClearedData.Cpu3.Unspecified" far-absolute RW
#endif
#undef  STM_START_SEC_VAR_CLEARED_QM_CORE3_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined STM_STOP_SEC_VAR_CLEARED_QM_CORE3_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma align restore
#pragma section farbss restore
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma section
#endif
#undef  STM_STOP_SEC_VAR_CLEARED_QM_CORE3_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined STM_START_SEC_VAR_CLEARED_QM_CORE4_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma section farbss "ClearedData.Cpu4.Unspecified"
#pragma align 4
#elif defined _GNU_C_TRICORE_
#pragma section "ClearedData.Cpu4.Unspecified" aw 4
#elif defined _GHS_C_TRICORE_
#pragma ghs section bss = ".ClearedData.Cpu4.Unspecified"
#elif defined _DIABDATA_C_TRICORE_
#pragma section DATA "InitData.Cpu4.Unspecified" "ClearedData.Cpu4.Unspecified" far-absolute RW
#endif
#undef  STM_START_SEC_VAR_CLEARED_QM_CORE4_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined STM_STOP_SEC_VAR_CLEARED_QM_CORE4_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma align restore
#pragma section farbss restore
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma section
#endif
#undef  STM_STOP_SEC_VAR_CLEARED_QM_CORE4_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined STM_START_SEC_VAR_CLEARED_QM_CORE5_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma section farbss "ClearedData.Cpu5.Unspecified"
#pragma align 4
#elif defined _GNU_C_TRICORE_
#pragma section "ClearedData.Cpu5.Unspecified" aw 4
#elif defined _GHS_C_TRICORE_
#pragma ghs section bss = ".ClearedData.Cpu5.Unspecified"
#elif defined _DIABDATA_C_TRICORE_
#pragma section DATA "InitData.Cpu5.Unspecified" "ClearedData.Cpu5.Unspecified" far-absolute RW
#endif
#undef  STM_START_SEC_VAR_CLEARED_QM_CORE5_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined STM_STOP_SEC_VAR_CLEARED_QM_CORE5_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma align restore
#pragma section farbss restore
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma section
#endif
#undef  STM_STOP_SEC_VAR_CLEARED_QM_CORE5_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined STM_START_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma section farbss "ClearedData.LmuNC.Unspecified"
#pragma align 4
#elif defined _GNU_C_TRICORE_
#pragma section "ClearedData.LmuNC.Unspecified" aw 4
#elif defined _GHS_C_TRICORE_
#pragma ghs section bss = ".ClearedData.LmuNC.Unspecified"
#elif defined _DIABDATA_C_TRICORE_
#pragma section DATA "InitData.LmuNC.Unspecified" "ClearedData.LmuNC.Unspecified" far-absolute RW
#endif
#undef  STM_START_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined STM_STOP_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma align restore
#pragma section farbss restore
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma section
#endif
#undef  STM_STOP_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined STM_START_SEC_VAR_INIT_QM_GLOBAL_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma section fardata "InitData.LmuNC.32bit"
#pragma align 4
#elif defined _GNU_C_TRICORE_
#pragma section "InitData.LmuNC.32bit" aw 4
#elif defined _GHS_C_TRICORE_
#pragma ghs section data = ".InitData.LmuNC.32bit"
#elif defined _DIABDATA_C_TRICORE_
#pragma section DATA "InitData.LmuNC.32bit"  "ClearedData.LmuNC.32bit" far-absolute RW
#endif
#undef  STM_START_SEC_VAR_INIT_QM_GLOBAL_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined STM_STOP_SEC_VAR_INIT_QM_GLOBAL_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma align restore
#pragma section fardata restore
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma section
#endif
#undef  STM_STOP_SEC_VAR_INIT_QM_GLOBAL_UNSPECIFIED
#undef MEMMAP_ERROR
/***************** Static Global Constants Sections ************************/
#elif defined STM_START_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma section farrom  "Const.Cpu0.Unspecified"
#pragma align 4
#elif defined _GNU_C_TRICORE_
#pragma section  "Const.Cpu0.Unspecified" a 4
#elif defined _GHS_C_TRICORE_
#pragma ghs section rodata = ".Const.Cpu0.Unspecified"
#elif defined _DIABDATA_C_TRICORE_
#pragma section CONST "Const.Cpu0.Unspecified" far-absolute R
#endif
#undef  STM_START_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined STM_STOP_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma align restore
#pragma section farrom restore
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma section
#endif
#undef  STM_STOP_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#undef MEMMAP_ERROR

/******************* Config Data Sections *************************/
#elif defined STM_START_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma section farrom "Config.Cpu0.Unspecified"
#pragma align 4
#elif defined _GNU_C_TRICORE_
#pragma section "Config.Cpu0.Unspecified" a 4
#elif defined _GHS_C_TRICORE_
#pragma ghs section rodata = ".Config.Cpu0.Unspecified"
#elif defined _DIABDATA_C_TRICORE_
#pragma section CONST "Config.Cpu0.Unspecified" far-absolute R
#endif
#undef  STM_START_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined STM_STOP_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma align restore
#pragma section farrom restore
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma section
#endif
#undef  STM_STOP_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
#undef MEMMAP_ERROR

/* Code Sections */
/*
To be used for mapping code to application block, boot block, external flash etc.
codePeriod is the typical period time value and unit of the ExecutableEntitys in this MemorySection.
The name part _{codePeriod} is optional. Units are:
- US microseconds
- MS milli second
- S second
*/
#elif defined STM_START_SEC_CODE_QM_GLOBAL
#ifdef _TASKING_C_TRICORE_
#pragma section code "Code.Cpu0"
#elif defined _GNU_C_TRICORE_
#pragma section "Code.Cpu0" ax
#elif defined _GHS_C_TRICORE_
#pragma ghs section text = ".Code.Cpu0"
#elif defined _DIABDATA_C_TRICORE_
#pragma section CODE "Code.Cpu0" RX
#endif
#undef  STM_START_SEC_CODE_QM_GLOBAL
#undef MEMMAP_ERROR
#elif defined STM_STOP_SEC_CODE_QM_GLOBAL
#ifdef _TASKING_C_TRICORE_
#pragma section code restore
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma section
#endif
#undef  STM_STOP_SEC_CODE_QM_GLOBAL
#undef MEMMAP_ERROR

#elif defined STM_START_SEC_CODE_FAST_QM_GLOBAL
#ifdef _TASKING_C_TRICORE_
#pragma section code "Code.Cpu0"
#elif defined _GNU_C_TRICORE_
#pragma section "Code.Cpu0" ax
#elif defined _GHS_C_TRICORE_
#pragma ghs section text = ".Code.Cpu0"
#elif defined _DIABDATA_C_TRICORE_
#pragma section CODE "Code.Cpu0" RX
#endif
#undef  STM_START_SEC_CODE_FAST_QM_GLOBAL
#undef MEMMAP_ERROR
#elif defined STM_STOP_SEC_CODE_FAST_QM_GLOBAL
#ifdef _TASKING_C_TRICORE_
#pragma section code restore
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma section
#endif
#undef  STM_STOP_SEC_CODE_FAST_QM_GLOBAL
#undef MEMMAP_ERROR

#endif

#else  /*#if ((APP_SW == DEMO_APP) || (APP_SW == TEST_APP))*/
/***********************************EMPTY SECTIONS***********************************/
#if defined STM_START_SEC_VAR_CLEARED_QM_CORE0_UNSPECIFIED
#undef  STM_START_SEC_VAR_CLEARED_QM_CORE0_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined STM_STOP_SEC_VAR_CLEARED_QM_CORE0_UNSPECIFIED
#undef  STM_STOP_SEC_VAR_CLEARED_QM_CORE0_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined STM_START_SEC_VAR_CLEARED_QM_CORE1_UNSPECIFIED
#undef  STM_START_SEC_VAR_CLEARED_QM_CORE1_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined STM_STOP_SEC_VAR_CLEARED_QM_CORE1_UNSPECIFIED
#undef  STM_STOP_SEC_VAR_CLEARED_QM_CORE1_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined STM_START_SEC_VAR_CLEARED_QM_CORE2_UNSPECIFIED
#undef  STM_START_SEC_VAR_CLEARED_QM_CORE2_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined STM_STOP_SEC_VAR_CLEARED_QM_CORE2_UNSPECIFIED
#undef  STM_STOP_SEC_VAR_CLEARED_QM_CORE2_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined STM_START_SEC_VAR_CLEARED_QM_CORE3_UNSPECIFIED
#undef  STM_START_SEC_VAR_CLEARED_QM_CORE3_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined STM_STOP_SEC_VAR_CLEARED_QM_CORE3_UNSPECIFIED
#undef  STM_STOP_SEC_VAR_CLEARED_QM_CORE3_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined STM_START_SEC_VAR_CLEARED_QM_CORE4_UNSPECIFIED
#undef  STM_START_SEC_VAR_CLEARED_QM_CORE4_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined STM_STOP_SEC_VAR_CLEARED_QM_CORE4_UNSPECIFIED
#undef  STM_STOP_SEC_VAR_CLEARED_QM_CORE4_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined STM_START_SEC_VAR_CLEARED_QM_CORE5_UNSPECIFIED
#undef  STM_START_SEC_VAR_CLEARED_QM_CORE5_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined STM_STOP_SEC_VAR_CLEARED_QM_CORE5_UNSPECIFIED
#undef  STM_STOP_SEC_VAR_CLEARED_QM_CORE5_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined STM_START_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED
#undef  STM_START_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined STM_STOP_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED
#undef  STM_STOP_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined STM_START_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#undef  STM_START_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined STM_STOP_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#undef  STM_STOP_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined STM_START_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
#undef  STM_START_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined STM_STOP_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
#undef  STM_STOP_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined STM_START_SEC_CODE_QM_GLOBAL
#undef  STM_START_SEC_CODE_QM_GLOBAL
#undef MEMMAP_ERROR
#elif defined STM_STOP_SEC_CODE_QM_GLOBAL
#undef  STM_STOP_SEC_CODE_QM_GLOBAL
#undef MEMMAP_ERROR
#elif defined STM_START_SEC_CODE_FAST_QM_GLOBAL
#undef  STM_START_SEC_CODE_FAST_QM_GLOBAL
#undef MEMMAP_ERROR
#elif defined STM_STOP_SEC_CODE_FAST_QM_GLOBAL
#undef  STM_STOP_SEC_CODE_FAST_QM_GLOBAL
#undef MEMMAP_ERROR
#elif defined STM_START_SEC_VAR_INIT_QM_GLOBAL_UNSPECIFIED
#undef  STM_START_SEC_VAR_INIT_QM_GLOBAL_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined STM_STOP_SEC_VAR_INIT_QM_GLOBAL_UNSPECIFIED
#undef  STM_STOP_SEC_VAR_INIT_QM_GLOBAL_UNSPECIFIED
#undef MEMMAP_ERROR
#endif

#endif /*#if ((APP_SW == DEMO_APP) || (APP_SW == TEST_APP))*/

#if defined MEMMAP_ERROR
#error "Stm_MemMap.h, wrong pragma command"
#endif
