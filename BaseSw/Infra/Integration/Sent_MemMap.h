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
**  FILENAME     : Sent_MemMap.h                                              **
**                                                                            **
**  VERSION      : 1.30.0_6.0.0                                               **
**                                                                            **
**  DATE         : 2019-09-09                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : This file contains the mapping of Memory Section           **
**                                                                            **
**  SPECIFICATION(S) : Specification of Memory Mapping, AUTOSAR Release 4.2.2 **
**                                                                            **
**  MAY BE CHANGED BY USER : Yes                                              **
**                                                                            **
*******************************************************************************/
#define MEMMAP_ERROR
#if ((APP_SW == DEMO_APP) || (APP_SW == TEST_APP))
/*DATA Section*/
/*To be used for all global or static variables.*/
/*Variable to be cleared at startup or reset is palced here - .bss*/
#if defined SENT_START_SEC_VAR_CLEARED_QM_GLOBAL_8
#ifdef _TASKING_C_TRICORE_
#pragma section farbss "ClearedData.LmuNC.8bit"
#elif defined _GNU_C_TRICORE_
#pragma section "ClearedData.LmuNC.8bit" aw
#elif defined _GHS_C_TRICORE_
#pragma ghs section bss = ".ClearedData.LmuNC.8bit"
#elif defined _DIABDATA_C_TRICORE_
#pragma section DATA "InitData.LmuNC.8bit" "ClearedData.LmuNC.8bit" far-absolute RW
#endif
#undef  SENT_START_SEC_VAR_CLEARED_QM_GLOBAL_8
#undef MEMMAP_ERROR
#elif defined SENT_STOP_SEC_VAR_CLEARED_QM_GLOBAL_8
#ifdef _TASKING_C_TRICORE_
#pragma section farbss restore
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma section 
#endif
#undef  SENT_STOP_SEC_VAR_CLEARED_QM_GLOBAL_8
#undef MEMMAP_ERROR

#elif defined SENT_START_SEC_VAR_CLEARED_QM_GLOBAL_32
#ifdef _TASKING_C_TRICORE_
#pragma section farbss "ClearedData.LmuNC.32bit"
#pragma align 4
#elif defined _GNU_C_TRICORE_
#pragma section "ClearedData.LmuNC.32bit" aw 4
#elif defined _GHS_C_TRICORE_
#pragma ghs section bss = ".ClearedData.LmuNC.32bit"
#elif defined _DIABDATA_C_TRICORE_
#pragma section DATA "InitData.LmuNC.32bit" "ClearedData.LmuNC.32bit" far-absolute RW
#endif
#undef  SENT_START_SEC_VAR_CLEARED_QM_GLOBAL_32
#undef MEMMAP_ERROR
#elif defined SENT_STOP_SEC_VAR_CLEARED_QM_GLOBAL_32
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
#undef  SENT_STOP_SEC_VAR_CLEARED_QM_GLOBAL_32
#undef MEMMAP_ERROR

/******************* Config Data Sections *************************/
#elif defined SENT_START_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
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
#undef  SENT_START_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined SENT_STOP_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
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
#undef  SENT_STOP_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined SENT_START_SEC_CONFIG_DATA_QM_CORE0_UNSPECIFIED
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
#undef  SENT_START_SEC_CONFIG_DATA_QM_CORE0_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined SENT_STOP_SEC_CONFIG_DATA_QM_CORE0_UNSPECIFIED
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
#undef  SENT_STOP_SEC_CONFIG_DATA_QM_CORE0_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined SENT_START_SEC_CONFIG_DATA_QM_CORE1_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma section farrom "Config.Cpu1.Unspecified"
#pragma align 4
#elif defined _GNU_C_TRICORE_
#pragma section "Config.Cpu1.Unspecified" a 4
#elif defined _GHS_C_TRICORE_
#pragma ghs section rodata = ".Config.Cpu1.Unspecified"
#elif defined _DIABDATA_C_TRICORE_
#pragma section CONST "Config.Cpu1.Unspecified" far-absolute R
#endif
#undef  SENT_START_SEC_CONFIG_DATA_QM_CORE1_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined SENT_STOP_SEC_CONFIG_DATA_QM_CORE1_UNSPECIFIED
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
#undef  SENT_STOP_SEC_CONFIG_DATA_QM_CORE1_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined SENT_START_SEC_CONFIG_DATA_QM_CORE2_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma section farrom "Config.Cpu2.Unspecified"
#pragma align 4
#elif defined _GNU_C_TRICORE_
#pragma section "Config.Cpu2.Unspecified" a 4
#elif defined _GHS_C_TRICORE_
#pragma ghs section rodata = ".Config.Cpu2.Unspecified"
#elif defined _DIABDATA_C_TRICORE_
#pragma section CONST "Config.Cpu2.Unspecified" far-absolute R
#endif
#undef  SENT_START_SEC_CONFIG_DATA_QM_CORE2_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined SENT_STOP_SEC_CONFIG_DATA_QM_CORE2_UNSPECIFIED
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
#undef  SENT_STOP_SEC_CONFIG_DATA_QM_CORE2_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined SENT_START_SEC_CONFIG_DATA_QM_CORE3_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma section farrom "Config.Cpu3.Unspecified"
#pragma align 4
#elif defined _GNU_C_TRICORE_
#pragma section "Config.Cpu3.Unspecified" a 4
#elif defined _GHS_C_TRICORE_
#pragma ghs section rodata = ".Config.Cpu3.Unspecified"
#elif defined _DIABDATA_C_TRICORE_
#pragma section CONST "Config.Cpu3.Unspecified" far-absolute R
#endif
#undef  SENT_START_SEC_CONFIG_DATA_QM_CORE3_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined SENT_STOP_SEC_CONFIG_DATA_QM_CORE3_UNSPECIFIED
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
#undef  SENT_STOP_SEC_CONFIG_DATA_QM_CORE3_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined SENT_START_SEC_CONFIG_DATA_QM_CORE4_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma section farrom "Config.Cpu4.Unspecified"
#pragma align 4
#elif defined _GNU_C_TRICORE_
#pragma section "Config.Cpu4.Unspecified" a 4
#elif defined _GHS_C_TRICORE_
#pragma ghs section rodata = ".Config.Cpu4.Unspecified"
#elif defined _DIABDATA_C_TRICORE_
#pragma section CONST "Config.Cpu4.Unspecified" far-absolute R
#endif
#undef  SENT_START_SEC_CONFIG_DATA_QM_CORE4_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined SENT_STOP_SEC_CONFIG_DATA_QM_CORE4_UNSPECIFIED
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
#undef  SENT_STOP_SEC_CONFIG_DATA_QM_CORE4_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined SENT_START_SEC_CONFIG_DATA_QM_CORE5_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma section farrom "Config.Cpu5.Unspecified"
#pragma align 4
#elif defined _GNU_C_TRICORE_
#pragma section "Config.Cpu5.Unspecified" a 4
#elif defined _GHS_C_TRICORE_
#pragma ghs section rodata = ".Config.Cpu5.Unspecified"
#elif defined _DIABDATA_C_TRICORE_
#pragma section CONST "Config.Cpu5.Unspecified" far-absolute R
#endif
#undef  SENT_START_SEC_CONFIG_DATA_QM_CORE5_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined SENT_STOP_SEC_CONFIG_DATA_QM_CORE5_UNSPECIFIED
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
#undef  SENT_STOP_SEC_CONFIG_DATA_QM_CORE5_UNSPECIFIED
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
#elif defined SENT_START_SEC_CODE_QM_GLOBAL
#ifdef _TASKING_C_TRICORE_
#pragma section code "Code.Cpu0"
#elif defined _GNU_C_TRICORE_
#pragma section "Code.Cpu0" ax
#elif defined _GHS_C_TRICORE_
#pragma ghs section text = ".Code.Cpu0"
#elif defined _DIABDATA_C_TRICORE_
#pragma section CODE "Code.Cpu0" RX
#endif
#undef  SENT_START_SEC_CODE_QM_GLOBAL
#undef MEMMAP_ERROR
#elif defined SENT_STOP_SEC_CODE_QM_GLOBAL
#ifdef _TASKING_C_TRICORE_
#pragma section code restore
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma section 
#endif
#undef  SENT_STOP_SEC_CODE_QM_GLOBAL
#undef MEMMAP_ERROR

#endif

#else  /*#if ((APP_SW == DEMO_APP) || (APP_SW == TEST_APP))*/ 
/***********************************EMPTY SECTIONS***********************************/
#if defined SENT_START_SEC_VAR_CLEARED_QM_GLOBAL_8
#undef  SENT_START_SEC_VAR_CLEARED_QM_GLOBAL_8
#undef MEMMAP_ERROR
#elif defined SENT_STOP_SEC_VAR_CLEARED_QM_GLOBAL_8
#undef  SENT_STOP_SEC_VAR_CLEARED_QM_GLOBAL_8
#undef MEMMAP_ERROR
#elif defined SENT_START_SEC_VAR_CLEARED_QM_GLOBAL_32
#undef  SENT_START_SEC_VAR_CLEARED_QM_GLOBAL_32
#undef MEMMAP_ERROR
#elif defined SENT_STOP_SEC_VAR_CLEARED_QM_GLOBAL_32
#undef  SENT_STOP_SEC_VAR_CLEARED_QM_GLOBAL_32
#undef MEMMAP_ERROR
#elif defined SENT_START_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
#undef  SENT_START_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined SENT_STOP_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
#undef  SENT_STOP_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined SENT_START_SEC_CONFIG_DATA_QM_CORE0_UNSPECIFIED
#undef  SENT_START_SEC_CONFIG_DATA_QM_CORE0_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined SENT_STOP_SEC_CONFIG_DATA_QM_CORE0_UNSPECIFIED
#undef  SENT_STOP_SEC_CONFIG_DATA_QM_CORE0_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined SENT_START_SEC_CONFIG_DATA_QM_CORE1_UNSPECIFIED
#undef  SENT_START_SEC_CONFIG_DATA_QM_CORE1_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined SENT_STOP_SEC_CONFIG_DATA_QM_CORE1_UNSPECIFIED
#undef  SENT_STOP_SEC_CONFIG_DATA_QM_CORE1_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined SENT_START_SEC_CONFIG_DATA_QM_CORE2_UNSPECIFIED
#undef  SENT_START_SEC_CONFIG_DATA_QM_CORE2_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined SENT_STOP_SEC_CONFIG_DATA_QM_CORE2_UNSPECIFIED
#undef  SENT_STOP_SEC_CONFIG_DATA_QM_CORE2_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined SENT_START_SEC_CONFIG_DATA_QM_CORE3_UNSPECIFIED
#undef  SENT_START_SEC_CONFIG_DATA_QM_CORE3_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined SENT_STOP_SEC_CONFIG_DATA_QM_CORE3_UNSPECIFIED
#undef  SENT_STOP_SEC_CONFIG_DATA_QM_CORE3_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined SENT_START_SEC_CONFIG_DATA_QM_CORE4_UNSPECIFIED
#undef  SENT_START_SEC_CONFIG_DATA_QM_CORE4_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined SENT_STOP_SEC_CONFIG_DATA_QM_CORE4_UNSPECIFIED
#undef  SENT_STOP_SEC_CONFIG_DATA_QM_CORE4_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined SENT_START_SEC_CONFIG_DATA_QM_CORE5_UNSPECIFIED
#undef  SENT_START_SEC_CONFIG_DATA_QM_CORE5_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined SENT_STOP_SEC_CONFIG_DATA_QM_CORE5_UNSPECIFIED
#undef  SENT_STOP_SEC_CONFIG_DATA_QM_CORE5_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined SENT_START_SEC_CODE_QM_GLOBAL
#undef  SENT_START_SEC_CODE_QM_GLOBAL
#undef MEMMAP_ERROR
#elif defined SENT_STOP_SEC_CODE_QM_GLOBAL
#undef  SENT_STOP_SEC_CODE_QM_GLOBAL
#undef MEMMAP_ERROR
#endif

#endif /*#if ((APP_SW == DEMO_APP) || (APP_SW == TEST_APP))*/ 

#if defined MEMMAP_ERROR
#error "Sent_MemMap.h, wrong pragma command"
#endif
