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
**  FILENAME  : Adc_MemMap.h                                                      **
**                                                                            **
**  VERSION   :                                              **
**                                                                            **
**  DATE      :                                                             **
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
**  SPECIFICATION(S) : Specification of ADC Driver,                      **
**   AUTOSAR Release <4.2.2>                                                  **
**                                                                            **
**  MAY BE CHANGED BY USER : Yes                                              **
**                                                                            **
*******************************************************************************/
#define MEMMAP_ERROR

#if ((!defined(APP_SW)) || (APP_SW == DEMO_APP) || (APP_SW == TEST_APP))
/*DATA Section*/
/*To be used for all global or static variables.*/
/*Variable to be cleared at startup or reset is palced here - .bss*/
#if defined ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE0_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma section farbss "ClearedData.Cpu0.Unspecified"
#pragma align 4
#pragma section_name_with_symbol on
#elif defined _GNU_C_TRICORE_
#pragma section "ClearedData.Cpu0.Unspecified" aw 4
#elif defined _GHS_C_TRICORE_
#pragma ghs section bss = ".ClearedData.Cpu0.Unspecified"
#elif defined _DIABDATA_C_TRICORE_
#pragma section DATA "InitData.Cpu0.Unspecified" "ClearedData.Cpu0.Unspecified" far-absolute RW
#pragma align_variables 4
#endif
#undef  ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE0_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma align restore
#pragma section farbss restore
#pragma section_name_with_symbol off
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma align_variables
#pragma section
#endif
#undef  ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE1_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma section farbss "ClearedData.Cpu1.Unspecified"
#pragma align 4
#pragma section_name_with_symbol on
#elif defined _GNU_C_TRICORE_
#pragma section "ClearedData.Cpu1.Unspecified" aw 4
#elif defined _GHS_C_TRICORE_
#pragma ghs section bss = ".ClearedData.Cpu1.Unspecified"
#elif defined _DIABDATA_C_TRICORE_
#pragma section DATA "InitData.Cpu1.Unspecified" "ClearedData.Cpu1.Unspecified" far-absolute RW
#pragma align_variables 4
#endif
#undef  ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE1_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma align restore
#pragma section farbss restore
#pragma section_name_with_symbol off
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma align_variables
#pragma section
#endif
#undef  ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE2_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma section farbss "ClearedData.Cpu2.Unspecified"
#pragma align 4
#pragma section_name_with_symbol on
#elif defined _GNU_C_TRICORE_
#pragma section "ClearedData.Cpu2.Unspecified" aw 4
#elif defined _GHS_C_TRICORE_
#pragma ghs section bss = ".ClearedData.Cpu2.Unspecified"
#elif defined _DIABDATA_C_TRICORE_
#pragma section DATA "InitData.Cpu2.Unspecified" "ClearedData.Cpu2.Unspecified" far-absolute RW
#pragma align_variables 4
#endif
#undef  ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE2_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma align restore
#pragma section farbss restore
#pragma section_name_with_symbol off
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma align_variables
#pragma section
#endif
#undef  ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE3_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma section farbss "ClearedData.Cpu3.Unspecified"
#pragma align 4
#pragma section_name_with_symbol on
#elif defined _GNU_C_TRICORE_
#pragma section "ClearedData.Cpu3.Unspecified" aw 4
#elif defined _GHS_C_TRICORE_
#pragma ghs section bss = ".ClearedData.Cpu3.Unspecified"
#elif defined _DIABDATA_C_TRICORE_
#pragma section DATA "InitData.Cpu3.Unspecified" "ClearedData.Cpu3.Unspecified" far-absolute RW
#pragma align_variables 4
#endif
#undef  ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE3_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma align restore
#pragma section farbss restore
#pragma section_name_with_symbol off
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma align_variables
#pragma section
#endif
#undef  ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE4_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma section farbss "ClearedData.Cpu4.Unspecified"
#pragma align 4
#pragma section_name_with_symbol on
#elif defined _GNU_C_TRICORE_
#pragma section "ClearedData.Cpu4.Unspecified" aw 4
#elif defined _GHS_C_TRICORE_
#pragma ghs section bss = ".ClearedData.Cpu4.Unspecified"
#elif defined _DIABDATA_C_TRICORE_
#pragma section DATA "InitData.Cpu4.Unspecified" "ClearedData.Cpu4.Unspecified" far-absolute RW
#pragma align_variables 4
#endif
#undef  ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE4_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma align restore
#pragma section farbss restore
#pragma section_name_with_symbol off
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma align_variables
#pragma section
#endif
#undef  ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE5_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma section farbss "ClearedData.Cpu5.Unspecified"
#pragma align 4
#pragma section_name_with_symbol on
#elif defined _GNU_C_TRICORE_
#pragma section "ClearedData.Cpu5.Unspecified" aw 4
#elif defined _GHS_C_TRICORE_
#pragma ghs section bss = ".ClearedData.Cpu5.Unspecified"
#elif defined _DIABDATA_C_TRICORE_
#pragma section DATA "InitData.Cpu5.Unspecified" "ClearedData.Cpu5.Unspecified" far-absolute RW
#pragma align_variables 4
#endif
#undef  ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE5_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma align restore
#pragma section farbss restore
#pragma section_name_with_symbol off
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma align_variables
#pragma section
#endif
#undef  ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined ADC_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
#ifdef _TASKING_C_TRICORE_
#pragma section farbss "ClearedData.LmuNC.32bit"
#pragma align 4
#pragma section_name_with_symbol on
#elif defined _GNU_C_TRICORE_
#pragma section "ClearedData.LmuNC.32bit" aw 4
#elif defined _GHS_C_TRICORE_
#pragma ghs section bss = ".ClearedData.LmuNC.32bit"
#elif defined _DIABDATA_C_TRICORE_
#pragma section DATA "InitData.LmuNC.32bit" "ClearedData.LmuNC.32bit" far-absolute RW
#pragma align_variables 4
#endif
#undef  ADC_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
#ifdef _TASKING_C_TRICORE_
#pragma align restore
#pragma section farbss restore
#pragma section_name_with_symbol off
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma align_variables
#pragma section
#endif
#undef  ADC_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
#undef MEMMAP_ERROR

#elif defined ADC_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_8
#ifdef _TASKING_C_TRICORE_
#pragma section farbss "ClearedData.LmuNC.8bit"
#pragma section_name_with_symbol on
#elif defined _GNU_C_TRICORE_
#pragma section "ClearedData.LmuNC.8bit" aw
#elif defined _GHS_C_TRICORE_
#pragma ghs section bss = ".ClearedData.LmuNC.8bit"
#elif defined _DIABDATA_C_TRICORE_
#pragma section DATA "InitData.LmuNC.8bit" "ClearedData.LmuNC.8bit" far-absolute RW
#endif
#undef  ADC_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_8
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_8
#ifdef _TASKING_C_TRICORE_
#pragma section farbss restore
#pragma section_name_with_symbol off
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma section
#endif
#undef  ADC_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_8
#undef MEMMAP_ERROR

#elif defined ADC_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_16
#ifdef _TASKING_C_TRICORE_
#pragma section farbss "ClearedData.LmuNC.16bit"
#pragma align 2
#pragma section_name_with_symbol on
#elif defined _GNU_C_TRICORE_
#pragma section "ClearedData.LmuNC.16bit" aw 2
#elif defined _GHS_C_TRICORE_
#pragma ghs section bss = ".ClearedData.LmuNC.16bit"
#elif defined _DIABDATA_C_TRICORE_
#pragma section DATA "InitData.LmuNC.16bit" "ClearedData.LmuNC.16bit" far-absolute RW
#pragma align_variables 2
#endif
#undef  ADC_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_16
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_16
#ifdef _TASKING_C_TRICORE_
#pragma align restore
#pragma section farbss restore
#pragma section_name_with_symbol off
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma align_variables
#pragma section
#endif
#undef  ADC_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_16
#undef MEMMAP_ERROR

#elif defined ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_8
#ifdef _TASKING_C_TRICORE_
#pragma section fardata "InitData.LmuNC.8bit"
#pragma section_name_with_symbol on
#elif defined _GNU_C_TRICORE_
#pragma section "InitData.LmuNC.8bit" aw
#elif defined _GHS_C_TRICORE_
#pragma ghs section data = ".InitData.LmuNC.8bit"
#elif defined _DIABDATA_C_TRICORE_
#pragma section DATA "InitData.LmuNC.8bit"  "ClearedData.LmuNC.8bit" far-absolute RW
#endif
#undef  ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_8
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_8
#ifdef _TASKING_C_TRICORE_
#pragma section fardata restore
#pragma section_name_with_symbol off
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma section
#endif
#undef  ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_8
#undef MEMMAP_ERROR

#elif defined ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_16
#ifdef _TASKING_C_TRICORE_
#pragma section fardata "InitData.LmuNC.16bit"
#pragma align 2
#pragma section_name_with_symbol on
#elif defined _GNU_C_TRICORE_
#pragma section "InitData.LmuNC.16bit" aw 2
#elif defined _GHS_C_TRICORE_
#pragma ghs section data = ".InitData.LmuNC.16bit"
#elif defined _DIABDATA_C_TRICORE_
#pragma section DATA "InitData.LmuNC.16bit"  "ClearedData.LmuNC.16bit" far-absolute RW
#pragma align_variables 2
#endif
#undef  ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_16
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_16
#ifdef _TASKING_C_TRICORE_
#pragma align restore
#pragma section fardata restore
#pragma section_name_with_symbol off
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma align_variables
#pragma section
#endif
#undef  ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_16
#undef MEMMAP_ERROR

#elif defined ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_32
#ifdef _TASKING_C_TRICORE_
#pragma section fardata "InitData.LmuNC.32bit"
#pragma align 4
#pragma section_name_with_symbol on
#elif defined _GNU_C_TRICORE_
#pragma section "InitData.LmuNC.32bit" aw 4
#elif defined _GHS_C_TRICORE_
#pragma ghs section data = ".InitData.LmuNC.32bit"
#elif defined _DIABDATA_C_TRICORE_
#pragma section DATA "InitData.LmuNC.32bit"  "ClearedData.LmuNC.32bit" far-absolute RW
#pragma align_variables 4
#endif
#undef  ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_32
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_32
#ifdef _TASKING_C_TRICORE_
#pragma align restore
#pragma section fardata restore
#pragma section_name_with_symbol off
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma align_variables
#pragma section
#endif
#undef  ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_32
#undef MEMMAP_ERROR

/***************** Static Global Constants Sections ************************/
#elif defined ADC_START_SEC_CONST_ASIL_B_GLOBAL_8
#ifdef _TASKING_C_TRICORE_
#pragma section farrom  "Const.Cpu0.8bit"
#pragma section_name_with_symbol on
#elif defined _GNU_C_TRICORE_
#pragma section  "Const.Cpu0.8bit" a
#elif defined _GHS_C_TRICORE_
#pragma ghs section rodata = ".Const.Cpu0.8bit"
#elif defined _DIABDATA_C_TRICORE_
#pragma section CONST "Const.Cpu0.8bit" far-absolute R
#endif
#undef  ADC_START_SEC_CONST_ASIL_B_GLOBAL_8
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_CONST_ASIL_B_GLOBAL_8
#ifdef _TASKING_C_TRICORE_
#pragma section farrom restore
#pragma section_name_with_symbol off
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma section
#endif
#undef  ADC_STOP_SEC_CONST_ASIL_B_GLOBAL_8
#undef MEMMAP_ERROR

#elif defined ADC_START_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma section farrom  "Const.Cpu0.Unspecified"
#pragma align 4
#pragma section_name_with_symbol on
#elif defined _GNU_C_TRICORE_
#pragma section  "Const.Cpu0.Unspecified" a 4
#elif defined _GHS_C_TRICORE_
#pragma ghs section rodata = ".Const.Cpu0.Unspecified"
#elif defined _DIABDATA_C_TRICORE_
#pragma section CONST "Const.Cpu0.Unspecified" far-absolute R
#pragma align_variables 4
#endif
#undef  ADC_START_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma align restore
#pragma section farrom restore
#pragma section_name_with_symbol off
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma align_variables
#pragma section
#endif
#undef  ADC_STOP_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
#undef MEMMAP_ERROR

/******************* Config Data Sections *************************/
#elif defined ADC_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma section farrom "Config.Cpu0.Unspecified"
#pragma align 4
#pragma section_name_with_symbol on
#elif defined _GNU_C_TRICORE_
#pragma section "Config.Cpu0.Unspecified" a 4
#elif defined _GHS_C_TRICORE_
#pragma ghs section rodata = ".Config.Cpu0.Unspecified"
#elif defined _DIABDATA_C_TRICORE_
#pragma section CONST "Config.Cpu0.Unspecified" far-absolute R
#pragma align_variables 4
#endif
#undef  ADC_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma align restore
#pragma section farrom restore
#pragma section_name_with_symbol off
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma align_variables
#pragma section
#endif
#undef  ADC_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma section farrom "Config.Cpu0.Unspecified"
#pragma align 4
#pragma section_name_with_symbol on
#elif defined _GNU_C_TRICORE_
#pragma section "Config.Cpu0.Unspecified" a 4
#elif defined _GHS_C_TRICORE_
#pragma ghs section rodata = ".Config.Cpu0.Unspecified"
#elif defined _DIABDATA_C_TRICORE_
#pragma section CONST "Config.Cpu0.Unspecified" far-absolute R
#pragma align_variables 4
#endif
#undef  ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma align restore
#pragma section farrom restore
#pragma section_name_with_symbol off
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma align_variables
#pragma section
#endif
#undef  ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma section farrom "Config.Cpu1.Unspecified"
#pragma align 4
#pragma section_name_with_symbol on
#elif defined _GNU_C_TRICORE_
#pragma section "Config.Cpu1.Unspecified" a 4
#elif defined _GHS_C_TRICORE_
#pragma ghs section rodata = ".Config.Cpu1.Unspecified"
#elif defined _DIABDATA_C_TRICORE_
#pragma section CONST "Config.Cpu1.Unspecified" far-absolute R
#pragma align_variables 4
#endif
#undef  ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma align restore
#pragma section farrom restore
#pragma section_name_with_symbol off
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma align_variables
#pragma section
#endif
#undef  ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma section farrom "Config.Cpu2.Unspecified"
#pragma align 4
#pragma section_name_with_symbol on
#elif defined _GNU_C_TRICORE_
#pragma section "Config.Cpu2.Unspecified" a 4
#elif defined _GHS_C_TRICORE_
#pragma ghs section rodata = ".Config.Cpu2.Unspecified"
#elif defined _DIABDATA_C_TRICORE_
#pragma section CONST "Config.Cpu2.Unspecified" far-absolute R
#pragma align_variables 4
#endif
#undef  ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma align restore
#pragma section farrom restore
#pragma section_name_with_symbol off
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma align_variables
#pragma section
#endif
#undef  ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma section farrom "Config.Cpu3.Unspecified"
#pragma align 4
#pragma section_name_with_symbol on
#elif defined _GNU_C_TRICORE_
#pragma section "Config.Cpu3.Unspecified" a 4
#elif defined _GHS_C_TRICORE_
#pragma ghs section rodata = ".Config.Cpu3.Unspecified"
#elif defined _DIABDATA_C_TRICORE_
#pragma section CONST "Config.Cpu3.Unspecified" far-absolute R
#pragma align_variables 4
#endif
#undef  ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma align restore
#pragma section farrom restore
#pragma section_name_with_symbol off
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma align_variables
#pragma section
#endif
#undef  ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma section farrom "Config.Cpu4.Unspecified"
#pragma align 4
#pragma section_name_with_symbol on
#elif defined _GNU_C_TRICORE_
#pragma section "Config.Cpu4.Unspecified" a 4
#elif defined _GHS_C_TRICORE_
#pragma ghs section rodata = ".Config.Cpu4.Unspecified"
#elif defined _DIABDATA_C_TRICORE_
#pragma section CONST "Config.Cpu4.Unspecified" far-absolute R
#pragma align_variables 4
#endif
#undef  ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma align restore
#pragma section farrom restore
#pragma section_name_with_symbol off
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma align_variables
#pragma section
#endif
#undef  ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma section farrom "Config.Cpu5.Unspecified"
#pragma align 4
#pragma section_name_with_symbol on
#elif defined _GNU_C_TRICORE_
#pragma section "Config.Cpu5.Unspecified" a 4
#elif defined _GHS_C_TRICORE_
#pragma ghs section rodata = ".Config.Cpu5.Unspecified"
#elif defined _DIABDATA_C_TRICORE_
#pragma section CONST "Config.Cpu5.Unspecified" far-absolute R
#pragma align_variables 4
#endif
#undef  ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
#ifdef _TASKING_C_TRICORE_
#pragma align restore
#pragma section farrom restore
#pragma section_name_with_symbol off
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma align_variables
#pragma section
#endif
#undef  ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
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
#elif defined ADC_START_SEC_CODE_ASIL_B_GLOBAL
#ifdef _TASKING_C_TRICORE_
#pragma section code "Code.Cpu0"
#pragma section_name_with_symbol on
#elif defined _GNU_C_TRICORE_
#pragma section "Code.Cpu0" ax
#elif defined _GHS_C_TRICORE_
#pragma ghs section text = ".Code.Cpu0"
#elif defined _DIABDATA_C_TRICORE_
#pragma section CODE "Code.Cpu0" RX
#endif
#undef  ADC_START_SEC_CODE_ASIL_B_GLOBAL
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_CODE_ASIL_B_GLOBAL
#ifdef _TASKING_C_TRICORE_
#pragma section code restore
#pragma section_name_with_symbol off
#elif defined _GNU_C_TRICORE_
#pragma section
#elif defined _GHS_C_TRICORE_
#pragma ghs section
#elif defined _DIABDATA_C_TRICORE_
#pragma section
#endif
#undef  ADC_STOP_SEC_CODE_ASIL_B_GLOBAL
#undef MEMMAP_ERROR

#endif

#else  /*#if ((!defined(APP_SW)) || (APP_SW == DEMO_APP) || (APP_SW == TEST_APP))*/
/************************EMPTY SECTIONS***************************************/
#if defined ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE0_UNSPECIFIED
#undef  ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE0_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_UNSPECIFIED
#undef  ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE1_UNSPECIFIED
#undef  ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE1_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_UNSPECIFIED
#undef  ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE2_UNSPECIFIED
#undef  ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE2_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_UNSPECIFIED
#undef  ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE3_UNSPECIFIED
#undef  ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE3_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_UNSPECIFIED
#undef  ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE4_UNSPECIFIED
#undef  ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE4_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_UNSPECIFIED
#undef  ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE5_UNSPECIFIED
#undef  ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE5_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_UNSPECIFIED
#undef  ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
#undef  ADC_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
#undef  ADC_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
#undef MEMMAP_ERROR
#elif defined ADC_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_8
#undef  ADC_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_8
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_8
#undef  ADC_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_8
#undef MEMMAP_ERROR
#elif defined ADC_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_16
#undef  ADC_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_16
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_16
#undef  ADC_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_16
#undef MEMMAP_ERROR
#elif defined ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_8
#undef  ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_8
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_8
#undef  ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_8
#undef MEMMAP_ERROR
#elif defined ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_16
#undef  ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_16
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_16
#undef  ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_16
#undef MEMMAP_ERROR
#elif defined ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_32
#undef  ADC_START_SEC_VAR_INIT_ASIL_B_GLOBAL_32
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_32
#undef  ADC_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_32
#undef MEMMAP_ERROR
#elif defined ADC_START_SEC_CONST_ASIL_B_GLOBAL_8
#undef  ADC_START_SEC_CONST_ASIL_B_GLOBAL_8
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_CONST_ASIL_B_GLOBAL_8
#undef  ADC_STOP_SEC_CONST_ASIL_B_GLOBAL_8
#undef MEMMAP_ERROR
#elif defined ADC_START_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
#undef  ADC_START_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
#undef  ADC_STOP_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
#undef  ADC_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
#undef  ADC_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
#undef  ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
#undef  ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
#undef  ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
#undef  ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
#undef  ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
#undef  ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE2_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
#undef  ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
#undef  ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE3_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
#undef  ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
#undef  ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE4_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
#undef  ADC_START_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
#undef  ADC_STOP_SEC_CONFIG_DATA_ASIL_B_CORE5_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined ADC_START_SEC_CODE_ASIL_B_GLOBAL
#undef  ADC_START_SEC_CODE_ASIL_B_GLOBAL
#undef MEMMAP_ERROR
#elif defined ADC_STOP_SEC_CODE_ASIL_B_GLOBAL
#undef  ADC_STOP_SEC_CODE_ASIL_B_GLOBAL
#undef MEMMAP_ERROR
#endif

#endif /*#if ((!defined(APP_SW)) || (APP_SW == DEMO_APP) || (APP_SW == TEST_APP))*/

#if defined MEMMAP_ERROR
#error "Adc_MemMap.h, wrong pragma command"
#endif
