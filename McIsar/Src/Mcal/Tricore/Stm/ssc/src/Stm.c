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
**  FILENAME     : Stm.c                                                      **
**                                                                            **
**  VERSION      : 1.40.0_15.0.0                                              **
**                                                                            **
**  DATE         : 2019-11-07                                                 **
**                                                                            **
**  VARIANT      : Variant Precompile                                         **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : STM Driver source file                                     **
**                                                                            **
**  SPECIFICATION(S) : Specification of Stm Driver                            **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/


/* Inclusion of Stm header file */
#include "Stm.h"
#include "Stm_Cbk.h"

/* Inclusion of Stm reg file */
#include "IfxStm_reg.h"

/* Global functions like Set/Reset END INIT protection bit,
Enable/Disable interrupts, Automic write function */
#include "McalLib.h"

/* Conditional Inclusion of DEM */
#if (STM_E_CLC_ENABLE_ERR_DEM_REPORT == STM_ENABLE_DEM_REPORT)
#include "Dem.h"
#endif

/* Conditional Inclusion of Developement Error Tracer File */
#if (STM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif /* (STM_DEV_ERROR_DETECT == STD_ON) */

/* McalLib OsStub inclusion for the user mode */
#if(STM_RUN_TIME_API_MODE != STM_MCAL_SUPERVISOR)
#include "McalLib_OsStub.h"
#endif /* McalLib OsStub inclusion for the user mode */
/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/
#ifndef STM_SW_MAJOR_VERSION
#error "STM_SW_MAJOR_VERSION is not defined. "
#endif

#ifndef STM_SW_MINOR_VERSION
#error "STM_SW_MINOR_VERSION is not defined. "
#endif

#ifndef STM_SW_PATCH_VERSION
#error "STM_SW_PATCH_VERSION is not defined. "
#endif

/* Check for Correct inclusion of headers */
#if ( STM_SW_MAJOR_VERSION != 10U )
#error "STM_SW_MAJOR_VERSION does not match. "
#endif
#if ( STM_SW_MINOR_VERSION != 40U )
#error "STM_SW_MINOR_VERSION does not match. "
#endif
#if ( STM_SW_PATCH_VERSION != 0U )
#error "STM_SW_PATCH_VERSION does not match. "
#endif


#if (STM_DEV_ERROR_DETECT == STD_ON)

#ifndef DET_AR_RELEASE_MAJOR_VERSION
#error "DET_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif


#if ( DET_AR_RELEASE_MAJOR_VERSION != 4U )
#error "DET_AR_RELEASE_MAJOR_VERSION does not match."
#endif

#endif /*#if (STM_DEV_ERROR_DETECT == STD_ON)*/


#if (STM_E_CLC_ENABLE_ERR_DEM_REPORT == STM_ENABLE_DEM_REPORT)
#ifndef DEM_AR_RELEASE_MAJOR_VERSION
#error "DEM_AR_RELEASE_MAJOR_VERSION is not defined."
#endif

#if ( DEM_AR_RELEASE_MAJOR_VERSION != 4U )
#error "DEM_AR_RELEASE_MAJOR_VERSION does not match."
#endif

#endif /*#if (STM_E_CLC_ENABLE_ERR_DEM_REPORT == STM_ENABLE_DEM_REPORT)*/

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
#define STM_REGISTER_OFFSET                (0x100U)
#define STM_SET_MASK                       (0xFFFFFFFFU)
#define STM_REG_CLR_MASK                   (0x0U)
#define STM_TIM_ONESHOT_MODE               (0x0U)
#define STM_INTR_NOD_NUM                   (0x2U)
#define STM_MAX_TIMER_VAL_ONE              (0x1U)
#define STM_MAX_TIMER_VAL_TWO              (0x2U)
#define STM_MAX_TIMER_VAL_THREE            (0x3U)
#define STM_MAX_TIMER_VAL_FOUR             (0x4U)
#define STM_MAX_TIMER_VAL_FIVE             (0x5U)
#define STM_COMPARE_VAL                    (0x1U)
#define STM_MAX_SHIFT_VALUE                ((uint8)32)

#if (STM_DEV_ERROR_DETECT == STD_ON)
#define STM_MAX_TIMER_NUMBER               (0x6U)
#endif

#if(STM_DEV_ERROR_DETECT == STD_ON)
#define STM_CMCON_MSTART_MAX_SIZE          (0x1FU)
#define STM_CMCON_MSIZE_MAX_VAL            (0x1FU)
#define STM_MAX_VALID_TIMER_MODE_VAL       (0x1U)
#define STM_MAX_CMP_REG_NUM                (0x1U)
#endif /* (STM_DEV_ERROR_DETECT == STD_ON) */
#define STM_MODULE_ENABLE                  (0x0U)
#define STM_CLC_EDIS_SLEEP_CTRL            (0x3U)

/* Offset for STM_CMCON_Bits.MSIZE0 */
#define STM_CMCON_MSIZE0_OFF     0
/* Offset for STM_CMCON_Bits.MSTART0 */
#define STM_CMCON_MSTART0_OFF    8
/* Offset for STM_CMCON_Bits.MSIZE1 */
#define STM_CMCON_MSIZE1_OFF     16
/* Offset for STM_CMCON_Bits.MSTART1 */
#define STM_CMCON_MSTART1_OFF    24
/*  STM_CMCON number of bits required to enable CMP interrupt in
    Mcal_SetBitAtomic  function call  */
#define STM_CMCON_MSIZE_ENABLE_BIT_POS_COUNT   5
/*  STM_CMCON MSTART total bit position count used in
    Mcal_SetBitAtomic  function call  */
#define STM_CMCON_MSTART_TOTAL_BIT_POS_COUNT   5
/*  STM_CMCON value to enable CMP interrupt  */
#define STM_CMCON_MSIZE_MAX_ENABLE_VAL        31

/* Offset for STM_ICR_Bits.CMP0EN */
#define STM_ICR_CMP0EN_OFF       0
/* Offset for STM_ICR_Bits.CMP1EN */
#define STM_ICR_CMP1EN_OFF       4
/*  STM_ICR number of bits required to enable CMP interrupt in
    Mcal_SetBitAtomic function call */
#define STM_ICR_ENABLE_BIT_POS_COUNT    3
/*  STM_ICR value to enable CMP1 interrupt  */
#define STM_ICR_CMP1_INTR_ENABLE_VAL     5
/*  STM_ICR value to enable CMP0 interrupt  */
#define STM_ICR_CMP0_INTR_ENABLE_VAL    1
/* Mask for STM_ICR_Bits.CMP0EN disable */
#define STM_ICR_CMP0_DISABLE_MSK    1
/* Mask for STM_ICR_Bits.CMP1EN disable */
#define STM_ICR_CMP1_DISABLE_MSK    1
/* Value for STM_ICR_Bits.CMP0EN disable */
#define STM_ICR_CMP0_DISABLE_VAL    0
/* Value for STM_ICR_Bits.CMP1EN disable */
#define STM_ICR_CMP1_DISABLE_VAL    0


/* User1 Mode / Supervisor Mode */
#if (STM_RUN_TIME_API_MODE  == STM_MCAL_SUPERVISOR)
/* Library APIs  */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'STM_LIB_RUNTIME_WRITEPERIPENDINITPROTREG'
 * defined for User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define STM_LIB_RUNTIME_WRITEPERIPENDINITPROTREG(RegAdd,Data) \
                               Mcal_WritePeripEndInitProtReg(RegAdd,Data)
#else
/* Library APIs  */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'STM_LIB_RUNTIME_WRITEPERIPENDINITPROTREG'
 * defined for User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define STM_LIB_RUNTIME_WRITEPERIPENDINITPROTREG(RegAdd,Data) \
                              MCAL_LIB_WRITEPERIPENDINITPROTREG(RegAdd,Data)
#endif   /* #if (STM_RUN_TIME_API_MODE  == MCAL_SUPERVISOR) */


/*******************************************************************************
**                   Function like macro definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
#define STM_START_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* Declaration of Stm Pre Build Configuration */
#include "Stm_MemMap.h"
extern const Stm_ModuleType Stm_ModuleMap[STM_MAX_TIMERS];

#define STM_STOP_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* Declaration of Stm Pre Build Configuration */
#include "Stm_MemMap.h"

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/

#define STM_START_SEC_VAR_INIT_QM_GLOBAL_UNSPECIFIED
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline.*/
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Stm_MemMap.h"




  /*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define STM_STOP_SEC_VAR_INIT_QM_GLOBAL_UNSPECIFIED
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Stm_MemMap.h"

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
#if (STM_MAX_TIMERS > 0x0U)
#if (STM_CORE0_MAX_TIMERS != 0U)

#define STM_START_SEC_VAR_CLEARED_QM_CORE0_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Stm_MemMap.h"
static Stm_ModuleParameterType Stm_TimerAllocation_Core0;

#define STM_STOP_SEC_VAR_CLEARED_QM_CORE0_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Stm_MemMap.h"
#endif
#endif

#if (STM_MAX_TIMERS > STM_MAX_TIMER_VAL_ONE)
#if (STM_CORE1_MAX_TIMERS != 0x0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define STM_START_SEC_VAR_CLEARED_QM_CORE1_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Stm_MemMap.h"
static Stm_ModuleParameterType Stm_TimerAllocation_Core1;
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define STM_STOP_SEC_VAR_CLEARED_QM_CORE1_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Stm_MemMap.h"
#endif
#endif

#if (STM_MAX_TIMERS > STM_MAX_TIMER_VAL_TWO)
#if (STM_CORE2_MAX_TIMERS != 0x0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define STM_START_SEC_VAR_CLEARED_QM_CORE2_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Stm_MemMap.h"
static Stm_ModuleParameterType Stm_TimerAllocation_Core2;
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define STM_STOP_SEC_VAR_CLEARED_QM_CORE2_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Stm_MemMap.h"
#endif
#endif

#if (STM_MAX_TIMERS > STM_MAX_TIMER_VAL_THREE)
#if (STM_CORE3_MAX_TIMERS != 0x0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define STM_START_SEC_VAR_CLEARED_QM_CORE3_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Stm_MemMap.h"
static Stm_ModuleParameterType Stm_TimerAllocation_Core3;
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define STM_STOP_SEC_VAR_CLEARED_QM_CORE3_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Stm_MemMap.h"
#endif
#endif

#if (STM_MAX_TIMERS > STM_MAX_TIMER_VAL_FOUR)
#if (STM_CORE4_MAX_TIMERS != 0x0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define STM_START_SEC_VAR_CLEARED_QM_CORE4_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Stm_MemMap.h"
static Stm_ModuleParameterType Stm_TimerAllocation_Core4;
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define STM_STOP_SEC_VAR_CLEARED_QM_CORE4_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Stm_MemMap.h"
#endif
#endif

#if (STM_MAX_TIMERS > STM_MAX_TIMER_VAL_FIVE)
#if (STM_CORE5_MAX_TIMERS != 0x0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define STM_START_SEC_VAR_CLEARED_QM_CORE5_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Stm_MemMap.h"
static Stm_ModuleParameterType Stm_TimerAllocation_Core5;
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define STM_STOP_SEC_VAR_CLEARED_QM_CORE5_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Stm_MemMap.h"
#endif
#endif

/*MISRA2012_RULE_2_5_JUSTIFICATION: Used in multiple configuration combination*/
#define STM_START_SEC_CONST_QM_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Stm_MemMap.h"
/* MISRA2012_RULE_8_9_JUSTIFICATION: Global Constants not declared within block
   scope used in all API's. */
static Stm_ModuleParameterType* const Stm_TimerCoreAllocation[STM_MAX_TIMERS] =
{
  #if (STM_MAX_TIMERS > 0x0U)
  #if (STM_CORE0_MAX_TIMERS != 0x0U)
  (Stm_ModuleParameterType*)&Stm_TimerAllocation_Core0,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (STM_MAX_TIMERS > STM_MAX_TIMER_VAL_ONE)
  #if (STM_CORE1_MAX_TIMERS != 0x0U)
  (Stm_ModuleParameterType*)&Stm_TimerAllocation_Core1,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (STM_MAX_TIMERS > STM_MAX_TIMER_VAL_TWO)
  #if (STM_CORE2_MAX_TIMERS != 0x0U)
  (Stm_ModuleParameterType*)&Stm_TimerAllocation_Core2,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (STM_MAX_TIMERS > STM_MAX_TIMER_VAL_THREE)
  #if (STM_CORE3_MAX_TIMERS != 0x0U)
  (Stm_ModuleParameterType*)&Stm_TimerAllocation_Core3,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (STM_MAX_TIMERS > STM_MAX_TIMER_VAL_FOUR)
  #if (STM_CORE4_MAX_TIMERS != 0x0U)
  (Stm_ModuleParameterType*)&Stm_TimerAllocation_Core4,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (STM_MAX_TIMERS > STM_MAX_TIMER_VAL_FIVE)
  #if (STM_CORE5_MAX_TIMERS != 0x0U)
  (Stm_ModuleParameterType*)&Stm_TimerAllocation_Core5,
  #else
  NULL_PTR,
  #endif
  #endif
};


/*MISRA2012_RULE_2_5_JUSTIFICATION: Used in multiple configuration combination*/
#define STM_STOP_SEC_CONST_QM_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Stm_MemMap.h"


/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
/* Mapping the code */
#define STM_START_SEC_CODE_QM_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Stm_MemMap.h"

LOCAL_INLINE void Stm_lSetBit(uint8* Data, const uint8 BitPn);
LOCAL_INLINE void Stm_lClrBit(uint8* Data, const uint8 BitPn);
LOCAL_INLINE uint8 Stm_lGetBit(const uint8 Data, const uint8 BitPn);
LOCAL_INLINE void Stm_lCopyBit(const uint8 Source, uint8* DestinationData,
                               uint8 DestinationPosition);
LOCAL_INLINE Stm_ModuleParameterType* Stm_lGetModNumStatusPtr(void);
LOCAL_INLINE Stm_TotalTimerCaptureType Stm_lReadTotalTimer(const uint8 
ModuleNumber);

#if (STM_DEV_ERROR_DETECT == STD_ON)
LOCAL_INLINE Std_ReturnType
Stm_lModnumAndCmpregDetCheck(const uint8 ModuleNumber,
    const uint8 CompareRegisterId, const uint8 ServiceId, const uint32 CoreId);

LOCAL_INLINE Std_ReturnType Stm_lModnumberDetCheck
(const uint8 ModuleNumber, const uint8 ServiceId, const uint32 CoreId);

LOCAL_INLINE void Stm_lReportError(const uint8 ApiId, const uint8 ErrorId);
#endif

#define STM_STOP_SEC_CODE_QM_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Stm_MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
/* Mapping the code */
#define STM_START_SEC_CODE_QM_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Stm_MemMap.h"

/*******************************************************************************
** Traceability      : [cover parentID=DS_NAS_STM_PR1730_PR1731]              **
**                                                                            **
** Syntax           : void Stm_EnableModule(const uint8 ModuleNumber)         **
**                                                                            **
** Service ID       : 0xC7                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non reentrant                                           **
**                                                                            **
** Parameters(in)   : ModuleNumber - Stm Peripheral number                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : This function enables the STM interrupts and interrupt  **
**                     node mapping                                           **
*******************************************************************************/
void Stm_EnableModule(const uint8 ModuleNumber)
{
  Stm_ModuleParameterType        *StmkernelStatusPtr;
  uint32                             CoreId;
  CoreId = Mcal_GetCpuIndex();
  #if (STM_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType                     ErrStatus;

  /* Check for the validity of Module number */
  ErrStatus = Stm_lModnumberDetCheck(ModuleNumber, STM_SID_ENABLEMODULE, CoreId)
  
;

  /* Check No DET Present */
  if(ErrStatus == (Std_ReturnType)E_OK)
  #endif
    /*(STM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Enable the STM module clock, by default STM clock is enabled */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: casting of register address to
       corresponding structure pointer   */
    /* MISRA2012_RULE_11_8_JUSTIFICATION: A cast shall not remove any const
     or volatile qualification from the type pointed to by a pointer   */
    STM_LIB_RUNTIME_WRITEPERIPENDINITPROTREG((uint32*) \
        (&STM_BASE[ModuleNumber].CLC.U), STM_REG_CLR_MASK);

    if(STM_MODULE_ENABLE == STM_BASE[ModuleNumber].CLC.B.DISS)
    {
      #if(STM_E_CLC_ENABLE_ERR_DEM_REPORT == STM_ENABLE_DEM_REPORT)
      /*Report DEM for STM enable passed*/
      Dem_ReportErrorStatus(STM_E_CLC_ENABLE_ERR, DEM_EVENT_STATUS_PASSED);
      #endif

      /* Get the STM peripheral core allocation pointer */
      /* MISRA2012_RULE_11_3_JUSTIFICATION: casting of register address to
       corresponding structure pointer   */
      StmkernelStatusPtr = Stm_lGetModNumStatusPtr();

      /* CMP0 used or CMP0 and CMP1 both are used */
      if((Stm_ModuleMap[CoreId].CmpRegId == STM_CMP0_USED) || \
          (Stm_ModuleMap[CoreId].CmpRegId == STM_CMP0_CMP1_USED))
      {
        /* Compare register value is assigned its reset value */
        STM_BASE[ModuleNumber].CMP[0].U = STM_REG_CLR_MASK;

        /* Configure the compare match control register in such a way
        that all the 32 bits of CMP registers are used to compare
        with first 32 bit values of 64 bit STM */
        Mcal_SetBitAtomic((&STM_BASE[ModuleNumber].CMCON.U), \
                   STM_CMCON_MSIZE0_OFF, STM_CMCON_MSIZE_ENABLE_BIT_POS_COUNT, \
                   STM_CMCON_MSIZE_MAX_ENABLE_VAL);

        /* Configure the interrupt system to handle interrupts from STM */
        Mcal_SetBitAtomic((&STM_BASE[ModuleNumber].ICR.U), STM_ICR_CMP0EN_OFF, \
                    STM_ICR_ENABLE_BIT_POS_COUNT, STM_ICR_CMP0_INTR_ENABLE_VAL);

        /* Initialise the compare register value holding RAM variable
           corresponding to the STM module number */
        StmkernelStatusPtr->CompareRegValue[0] = 0x0U;
      
      }
      /* CMP1 used or CMP0 and CMP1 both are used */
      if((Stm_ModuleMap[CoreId].CmpRegId == STM_CMP1_USED) || \
          (Stm_ModuleMap[CoreId].CmpRegId == STM_CMP0_CMP1_USED))
      {
        /* Compare register value is assigned its reset value */
        STM_BASE[ModuleNumber].CMP[STM_COMPARE_VAL].U = STM_REG_CLR_MASK;
        /* Configure the compare match control register in such a way
        that all the 32 bits of CMP registers are used to compare
        with first 32 bit values of 64 bit STM */
        Mcal_SetBitAtomic((&STM_BASE[ModuleNumber].CMCON.U), \
                  STM_CMCON_MSIZE1_OFF, STM_CMCON_MSIZE_ENABLE_BIT_POS_COUNT, \
                  STM_CMCON_MSIZE_MAX_ENABLE_VAL);
        /* Configure the interrupt system to handle interrupts from STM */
        Mcal_SetBitAtomic((&STM_BASE[ModuleNumber].ICR.U), STM_ICR_CMP1EN_OFF, \
                    STM_ICR_ENABLE_BIT_POS_COUNT, STM_ICR_CMP1_INTR_ENABLE_VAL);
        /* Initialise the compare register value holding RAM variable
           corresponding to the STM module number */
        StmkernelStatusPtr->CompareRegValue[STM_COMPARE_VAL] = 0x0U;
      
      }
      /* Initialize the timermode value with one shot mode */
      StmkernelStatusPtr->TimerMode = STM_TIM_ONESHOT_MODE;
      /* Initialize the Interrupt Node RAM variable */
      StmkernelStatusPtr->InterruptNodeMap = STM_INTR_NOD_NUM;
    }
    else
    {
      #if(STM_E_CLC_ENABLE_ERR_DEM_REPORT == STM_ENABLE_DEM_REPORT)
      /*Report DEM for STM CLC enable error*/
      Dem_ReportErrorStatus(STM_E_CLC_ENABLE_ERR, DEM_EVENT_STATUS_FAILED);
      #endif
    }
  }
}

/*******************************************************************************
** Traceability      :                                                        **
**                                                                            **
** Syntax           : void Stm_EnableAlarm(const uint8 ModuleNumber,          **
**                    const uint8 CompareRegisterId,const uint8 TimerMode,    **
**    const uint32 Ticks, const Stm_CallbackFnPtrType Stm_Applicationfunction)**
**                                                                            **
** Service ID       : 0xC8                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different STM timer                       **
**                                                                            **
** Parameters(in)   : ModuleNumber - Stm Peripheral number                    **
**                    CompareRegisterId - Compare register number             **
**                    TimerMode - One shot(0) or continuous(1)                **
**                    Ticks - Timer ticks with respect to selected timer      **
**                    void (*Stm_Applicationfunction)(void)) -                **
**                    Functon pointer used for Call-back function             **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : This function provides service to invoke a Call-back    **
                      function after the elapse of configured                 **
                      amount of time(scheduling a function)                   **
*******************************************************************************/
void Stm_EnableAlarm(const uint8 ModuleNumber,
       const uint8 CompareRegisterId, const uint8 TimerMode, const uint32 Ticks,
       const Stm_CallbackFnPtrType Stm_Applicationfunction)
{
  Stm_ModuleParameterType        *StmkernelStatusPtr;
  uint8 MatchStartBit;
  uint32 Cmpval;
  Stm_TotalTimerCaptureType Stm_64Bit_Timer_Value;
  uint8 shiftval; 

  #if (STM_DEV_ERROR_DETECT == STD_ON)
  uint32                             CoreId;
  Std_ReturnType                     ErrStatus;

  /* Get the core id */
  CoreId = Mcal_GetCpuIndex();

  /* Check for the validity of Module number and cmp register */
  ErrStatus = Stm_lModnumAndCmpregDetCheck(ModuleNumber,
              CompareRegisterId, STM_SID_ENABLEALARM, CoreId);

  /* Check No DET present */
  if(ErrStatus == E_OK)
  {
    /* Check Timer mode is one shot mode or continuos */
    if(TimerMode > STM_MAX_VALID_TIMER_MODE_VAL)
    {
      /* Call local function to report timer mode passed is invalid */
      Stm_lReportError(STM_SID_ENABLEALARM, STM_E_TIMER_MODE_FAILED);
      /* Update ErrStatus with E_NOT_OK */
      ErrStatus = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
      /* Check notification function is valid */
      if(Stm_Applicationfunction == NULL_PTR)
      {
        /*  Call local function to DET if passed function is NULL_PTR */
        Stm_lReportError(STM_SID_ENABLEALARM, STM_E_PARAM_POINTER);
        /* Update ErrStatus with E_NOT_OK */
        ErrStatus = (Std_ReturnType)E_NOT_OK;
      }
    }
  }

  /* Check No DET Present */
  if(ErrStatus == (Std_ReturnType)E_OK)
  #endif
  /* (STM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the STM peripheral core allocation pointer */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: casting of register address to
       corresponding structure pointer   */
    StmkernelStatusPtr = Stm_lGetModNumStatusPtr();

    /* TimerMode can be one shot/continuous copy the same to RAM variable */
    Stm_lCopyBit(TimerMode, &StmkernelStatusPtr->TimerMode, CompareRegisterId);
    /* Update the RAM variable with requested timer ticks */
    StmkernelStatusPtr->CompareRegValue[CompareRegisterId] = Ticks;

    /* Copy the Call-back function to be invoked */
    StmkernelStatusPtr->Stm_ArrayFunctionPtr[CompareRegisterId]
      = Stm_Applicationfunction;
   
   /* Checking  CompareRegisterId and slecting MSTART value */
   MatchStartBit = (CompareRegisterId == 0x0U) ?(STM_BASE[ModuleNumber].CMCON.B.
   MSTART0):(STM_BASE[ModuleNumber].CMCON.B.MSTART1);
   
   /* load 64 bits timer value */
   Stm_64Bit_Timer_Value= Stm_lReadTotalTimer(ModuleNumber);
   
   shiftval = STM_MAX_SHIFT_VALUE - MatchStartBit;
   
   /* Load the compare register with given ticks */
   Cmpval = StmkernelStatusPtr->CompareRegValue[CompareRegisterId]
             + (((Stm_64Bit_Timer_Value.LowerPart) >> MatchStartBit) |
             ((Stm_64Bit_Timer_Value.UpperPart) << shiftval));
   
   STM_BASE[ModuleNumber].CMP[CompareRegisterId].U  = (Cmpval & STM_SET_MASK);

    if(CompareRegisterId == 0x0U)
    {
      /* Configure the interrupt system to handle interrupts from STM */
      Mcal_SetBitAtomic((&STM_BASE[ModuleNumber].ICR.U), STM_ICR_CMP0EN_OFF, \
                    STM_ICR_ENABLE_BIT_POS_COUNT, STM_ICR_CMP0_INTR_ENABLE_VAL);
    }
    else
    {
      /* Configure the interrupt system to handle interrupts from STM */
      Mcal_SetBitAtomic((&STM_BASE[ModuleNumber].ICR.U), STM_ICR_CMP1EN_OFF, \
                    STM_ICR_ENABLE_BIT_POS_COUNT, STM_ICR_CMP1_INTR_ENABLE_VAL);
    }
  }
}

/*******************************************************************************
** Traceability      :                                                        **
**                                                                            **
** Syntax           : void Stm_DisableAlarm(const uint8 ModuleNumber,         **
**                                              const uint8 CompareRegisterId)**
** Service ID       : 0xC9                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different STM timer                       **
**                                                                            **
** Parameters(in)   : ModuleNumber - Stm Peripheral number                    **
**                    CompareRegisterId - Compare register number             **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : This function stops the invoke of a Call-back function  **
**                                                                            **
*******************************************************************************/
void Stm_DisableAlarm(const uint8 ModuleNumber, const uint8 CompareRegisterId)
{
  Stm_ModuleParameterType        *StmkernelStatusPtr;
  #if (STM_DEV_ERROR_DETECT == STD_ON)
  uint32                              CoreId;
  Std_ReturnType                      ErrStatus;

  CoreId = Mcal_GetCpuIndex();

  /* Check for the validity of Module number and cmp register */
  ErrStatus = Stm_lModnumAndCmpregDetCheck(ModuleNumber, CompareRegisterId,
              STM_SID_DISABLEALARM, CoreId);
  /* Check No DET present */
  if(ErrStatus == (Std_ReturnType)E_OK)
  #endif /*(STM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the STM peripheral core allocation pointer */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: casting of register address to
       corresponding structure pointer   */
    StmkernelStatusPtr = Stm_lGetModNumStatusPtr();

    if(CompareRegisterId == 0x0U)
    {
      /* Disable the  requested STM service request  */
      Mcal_SetBitAtomic((&STM_BASE[ModuleNumber].ICR.U), STM_ICR_CMP0EN_OFF, \
                        STM_ICR_ENABLE_BIT_POS_COUNT, 0);
    }
    else
    {
      /* Disable the  requested STM service request  */
      Mcal_SetBitAtomic((&STM_BASE[ModuleNumber].ICR.U), STM_ICR_CMP1EN_OFF, \
                        STM_ICR_ENABLE_BIT_POS_COUNT, 0);
    }
    /* Stm_ArrayFunction pointer is updated to NULL_PTR */
    StmkernelStatusPtr->Stm_ArrayFunctionPtr[CompareRegisterId] = NULL_PTR;
    /* Unused ModuleNumber */
    UNUSED_PARAMETER(ModuleNumber);
  }
}

/*******************************************************************************
** Traceability      :                                                        **
**                                                                            **
** Syntax           : void Stm_SetCompareMatchControl(const uint8 ModuleNumber**
**   const uint8 CompareRegisterId,const uint8 Mstart,const uint8 MSize)      **
**                                                                            **
** Service ID       : 0xCA                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different STM timer                       **
**                                                                            **
** Parameters(in)   : ModuleNumber - Stm Peripheral number                    **
**                    CompareRegisterId - Compare register number             **
**                    Mstart - The lowest bit number of the 64-bit STM        **
**                    MSize - Number of bits in register CMPx                 **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : This function provides service to write into the        **
**                    CMPx register.                                          **
**                                                                            **
*******************************************************************************/
void Stm_SetCompareMatchControl(const uint8 ModuleNumber,
          const uint8 CompareRegisterId, const uint8 Mstart, const uint8 MSize)
{
  #if (STM_DEV_ERROR_DETECT == STD_ON)
  uint32                              CoreId;
  Std_ReturnType                      ErrStatus;

  CoreId = Mcal_GetCpuIndex();

  /* Check for the validity of Module number and cmp register */
  ErrStatus = Stm_lModnumAndCmpregDetCheck(ModuleNumber, CompareRegisterId,
              STM_SID_SETCOMPAREMATCH_CTRL, CoreId);
         
  /* Check No DET present */
  if(ErrStatus == E_OK)
  {
    /* Check MStart input value is valid */
    if(Mstart > STM_CMCON_MSTART_MAX_SIZE)
    {
      /* Call local function to report DET invalid MStart is passed */
      Stm_lReportError(STM_SID_SETCOMPAREMATCH_CTRL, STM_E_MSTART_FAILED);
      /* Update ErrStatus with E_NOT_OK */
      ErrStatus = (Std_ReturnType)E_NOT_OK;
    }
  }

  /* Check No DET present */
  if(ErrStatus == E_OK)
  {
    /* Check MSize value is valid */
    if(MSize > STM_CMCON_MSIZE_MAX_VAL)
    {
      /* Call local function to report DET invalid MSize is passed */
      Stm_lReportError(STM_SID_SETCOMPAREMATCH_CTRL, STM_E_MSIZE_FAILED);
      /* Update ErrStatus with E_NOT_OK */
      ErrStatus = (Std_ReturnType)E_NOT_OK;
     
    }
  }

  /* Check No DET present */
  if(ErrStatus == (Std_ReturnType)E_OK)
  #endif
  /* (STM_DEV_ERROR_DETECT == STD_ON) */
  {
    

      if (CompareRegisterId == 0x0U)
      {
        /* CMCON register Mstart updates */
        Mcal_SetBitAtomic((&STM_BASE[ModuleNumber].CMCON.U), \
           STM_CMCON_MSTART0_OFF, STM_CMCON_MSTART_TOTAL_BIT_POS_COUNT, Mstart);

        /* CMCON register CMP0 Msize updates */
        Mcal_SetBitAtomic((&STM_BASE[ModuleNumber].CMCON.U), \
           STM_CMCON_MSIZE0_OFF, STM_CMCON_MSIZE_ENABLE_BIT_POS_COUNT, MSize);
      }
      else
      {
        /* CMCON register Mstart updates */
        Mcal_SetBitAtomic((&STM_BASE[ModuleNumber].CMCON.U), \
           STM_CMCON_MSTART1_OFF, STM_CMCON_MSTART_TOTAL_BIT_POS_COUNT, Mstart);

        /* CMCON register CMP1 Msize updates */
        Mcal_SetBitAtomic((&STM_BASE[ModuleNumber].CMCON.U), \
           STM_CMCON_MSIZE1_OFF, STM_CMCON_MSIZE_ENABLE_BIT_POS_COUNT, MSize);
      }
      /* Unused parameters */
      UNUSED_PARAMETER(MSize);
      UNUSED_PARAMETER(Mstart); 
      UNUSED_PARAMETER(ModuleNumber);      
  
  }
}

/*******************************************************************************
** Traceability      :                                                        **
**                                                                            **
** Syntax           : uint32 Stm_ReadTimerValue(constuint8 ModuleNumber,      **
**                                              constuint8 TimerNumber)       **
** Service ID       : 0xCB                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different STM timer                       **
**                                                                            **
** Parameters(in)   : ModuleNumber - stm periheral number                     **
**                    TimerNumber - The TimerNumber values shall be           **
**                                  0,1,2,3,4,5 and 6                         **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : uint32 - Current running timer value in ticks           **
**                                                                            **
** Description      : This function returns individual TIM value of a         **
**                    particular STM module                                   **
**                                                                            **
*******************************************************************************/
uint32 Stm_ReadTimerValue(const uint8 ModuleNumber, const uint8 TimerNumber)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION:
  Union used for register type definition */
  const Ifx_STM_TIM0 *Timer0BaseaddressPtr;
  uint32 Timvalue = E_NOT_OK;
  #if (STM_DEV_ERROR_DETECT == STD_ON)
  uint32                              CoreId;
  Std_ReturnType                      ErrStatus;

  CoreId = Mcal_GetCpuIndex();

  /* Check for the validity of Module number */
  ErrStatus = \
             Stm_lModnumberDetCheck(ModuleNumber, STM_SID_READTIMERVAL, CoreId);

  /* Check No DET present */
  if(ErrStatus == E_OK)
  {
    /* Check TimerNumber is valid */
    if(TimerNumber > STM_MAX_TIMER_NUMBER)
    {
      /* Call local function to report DET invalid Timer number */
      Stm_lReportError(STM_SID_READTIMERVAL, STM_E_INV_TIMER_NUMBER);
      /* Update ErrStatus with E_NOT_OK */
      ErrStatus = (Std_ReturnType)E_NOT_OK;
    }
  }

  /* Check No DET present */
  if(ErrStatus == (Std_ReturnType)E_OK)
  #endif
  /* (STM_DEV_ERROR_DETECT == STD_ON) */
  {
    /*Returns TIMx register value based on requested TimerNumber & Mod num */
    /* MISRA2012_RULE_18_4_JUSTIFICATION:Agreed only for SFR access with
       Pointer arithmetic */
    Timer0BaseaddressPtr = (Ifx_STM_TIM0*) (&STM0_TIM0 + \
                           ((STM_REGISTER_OFFSET * (uint32)ModuleNumber)/ \
                           STM_MAX_TIMER_VAL_FOUR));

    /* MISRA2012_RULE_18_4_JUSTIFICATION:
       Agreed for SFR access with Pointer arithmetic */
    Timvalue = (Timer0BaseaddressPtr + TimerNumber)->U;
  }
  return Timvalue;
}

/*******************************************************************************
** Traceability      :                                                        **
**                                                                            **
** Syntax           : Stm_TotalTimerCaptureType                               **
**                     Stm_ReadTotalTimerValue(const uint8 ModuleNumber)      **
**                                                                            **
** Service ID       : 0xCC                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different STM timer                       **
**                                                                            **
** Parameters(in)   : ModuleNumber - Stm Peripheral number                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : Stm_TotalTimerCaptureType : Holds the lower and upper   **
**                    32-bit values of a 64-bit STM timer                     **
**                                                                            **
** Description      : This function returns complete 64 bit STM Timer value   **
**                    of a particular STM module                              **
**                                                                            **
*******************************************************************************/
Stm_TotalTimerCaptureType Stm_ReadTotalTimerValue(const uint8 ModuleNumber)
{
  Stm_TotalTimerCaptureType TotalTimerCapture;
  TotalTimerCapture.LowerPart = 0x0U;
  TotalTimerCapture.UpperPart = 0x0U;
  
  #if (STM_DEV_ERROR_DETECT == STD_ON)
  uint32                              CoreId;
  Std_ReturnType                      ErrStatus;

  CoreId = Mcal_GetCpuIndex();

  /* Check for the validity of Module number */
  ErrStatus = \
        Stm_lModnumberDetCheck(ModuleNumber, STM_SID_READTOTALTIMERVAL, CoreId);

  /* Check No DET present */
  if(ErrStatus == (Std_ReturnType)E_OK)
  #endif
    /* (STM_DEV_ERROR_DETECT == STD_ON) */
  {
     /* Returns the total timer value */
     TotalTimerCapture = Stm_lReadTotalTimer(ModuleNumber);
  }
  return TotalTimerCapture;
}


/*******************************************************************************
** Traceability      :                                                        **
**                                                                            **
** Syntax           : void Stm_SleepModeHandle(constuint8 ModuleNumber,       **
                                       constuint8 SleepmodeControl)           **
**                                                                            **
** Service ID       : 0xCD                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non reentrant                                           **
**                                                                            **
** Parameters(in)   : ModuleNumber - Stm Peripheral number                    **
**                    SleepmodeControl - 0 or 1                               **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : This function:                                          **
**                    To enable/disable of STM during controller sleep mode   **
**                                                                            **
*******************************************************************************/
void Stm_SleepModeHandle(const uint8 ModuleNumber, const uint8 SleepmodeControl)
{
  #if (STM_DEV_ERROR_DETECT == STD_ON)
  uint32                              CoreId;
  Std_ReturnType                      ErrStatus;

  CoreId = Mcal_GetCpuIndex();

  /* Check for the validity of Module number */
  ErrStatus = \
           Stm_lModnumberDetCheck(ModuleNumber, STM_SID_SLEEPMODHANDLE, CoreId);

  /* Check No DET present */
  if(ErrStatus == E_OK)
  {
    /* Check Sleepmodecontrol is valid */
    if(SleepmodeControl > STM_COMPARE_VAL)
    {
      /* Call local function to report DET invalid sleep mode control */
      Stm_lReportError(STM_SID_SLEEPMODHANDLE, STM_E_SLEEP_MODE_FAILED);
      /* Update ErrStatus with E_NOT_OK */
      ErrStatus = (Std_ReturnType)E_NOT_OK;
    }
  }
  /* Check No DET Present */
  if(ErrStatus == (Std_ReturnType)E_OK)
  #endif
  /* (STM_DEV_ERROR_DETECT == STD_ON)  */
  {
    /* Enable/disable the requested STM during Controller sleep mode */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: casting of register address to
       corresponding structure pointer   */
    /* MISRA2012_RULE_11_8_JUSTIFICATION: A cast shall not remove any const
       or volatile qualification from the type pointed to by a pointer   */
    STM_LIB_RUNTIME_WRITEPERIPENDINITPROTREG((uint32*) \
        &STM_BASE[ModuleNumber].CLC.U, ((uint32)SleepmodeControl << \
                                        STM_CLC_EDIS_SLEEP_CTRL));
  }
}

/* Enable / Disable the use of the function */
#if (STM_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax :void Stm_GetVersionInfo                                            **
**                    (                                                       **
**                      Std_VersionInfoType *versioninfo                      **
**                    )                                                       **
**                                                                            **
** Description :  This Api:                                                   **
**   - This function returns the version information of this module           **
**     The version information include : Module ID, Vendor ID,                **
**     Vendor specific version numbers                                        **
**   - This function is available if the STM_VERSION_INFO_API is              **
**     set ON                                                                 **
**                                                                            **
** Service ID:  0xCE                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant                                                     **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
**                                                                            **
** Parameters (out):  versioninfo - Pointer to store the                      **
**                    version information of this module.                     **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
void Stm_GetVersionInfo(Std_VersionInfoType *versioninfo)
{

  #if (STM_DEV_ERROR_DETECT == STD_ON)
  /* Check for DET: versioninfo is valid */
  if (versioninfo == NULL_PTR)
  {
    /* Call local function to report DET if service called with NULL_PTR */
    Stm_lReportError(STM_SID_GETVERSIONINFO, STM_E_PARAM_POINTER);
  }
  else
  #endif /* #if (STM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Vendor ID information */
    ((Std_VersionInfoType*)(versioninfo))->vendorID = STM_VENDOR_ID;
    /* Stm module ID information */
    ((Std_VersionInfoType*)(versioninfo))->moduleID = STM_MODULE_ID;
    /* Stm module Software major version information */
    ((Std_VersionInfoType*)(versioninfo))->sw_major_version =
      (uint8)STM_SW_MAJOR_VERSION;
    /* Stm module Software minor version information */
    ((Std_VersionInfoType*)(versioninfo))->sw_minor_version =
      (uint8)STM_SW_MINOR_VERSION;
    /* Stm module Software patch version information */
    ((Std_VersionInfoType*)(versioninfo))->sw_patch_version =
      (uint8)STM_SW_PATCH_VERSION;
  }
}
#endif /*(STM_VERSION_INFO_API == STD_ON)*/
/*******************************************************************************
** Traceability      :                                                        **
**                                                                            **
** Syntax           : LOCAL_INLINE void Stm_lSetBit                           **
**                                   (uint8* Data,const uint8 BitPn)          **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : Data - Input variable                                   **
**                    BitPn - Bit number                                      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : This function:                                          **
**                    Set the respective bit in the variable                  **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Stm_lSetBit(uint8* Data, const uint8 BitPn)
{
  *Data |= (uint8)(STM_COMPARE_VAL << BitPn);
}

/*******************************************************************************
** Traceability      :                                                        **
**                                                                            **
** Syntax           : LOCAL_INLINE void Stm_lClrBit(                          **
**                                     uint8* Data,const uint8 BitPn)         **
**                                                                            **
** Service ID       :   NA                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : Data - Input variable                                   **
**                    BitPn - Bit number                                      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : This function:                                          **
**                    Clear the respective bit in the variable                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Stm_lClrBit(uint8* Data, const uint8 BitPn)
{
  *Data &= (~(uint8)(STM_COMPARE_VAL << BitPn));
}

/*******************************************************************************
** Traceability      : [cover parentID=]                                      **
**                                                                            **
** Syntax           : LOCAL_INLINE void Stm_lGetBit(                          **
**                                    const uint8 Data,const uint8 BitPn)     **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : Data - Input variable                                   **
**                    BitPn - Bit number                                      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : Returns the respective bit                              **
**                                                                            **
** Description      : This function:                                          **
**                    Get the respective bit in the variable                  **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Stm_lGetBit(const uint8 Data, const uint8 BitPn)
{
  uint8 Value;
  Value = (((uint8)Data >> BitPn) & STM_COMPARE_VAL);
  return Value;
}

/*******************************************************************************
** Traceability      : [cover parentID=]                                      **
**                                                                            **
** Syntax           : LOCAL_INLINE void Stm_lCopyBit(const uint8 Source,      **
**                        uint8* DestinationData, uint8 DestinationPosition)  **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : Source - Input variable                                 **
**                    DestinationData - Output variable                       **
**                    DestinationPosition - Bit position in output variable   **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : This function:                                          **
**                    copy the respective bit in the output variable          **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Stm_lCopyBit(const uint8 Source, uint8* DestinationData,
                               uint8 DestinationPosition)
{
  if(Source == STM_COMPARE_VAL)
  {
    /* Set the passed input value in the passed bit position  */
    Stm_lSetBit(DestinationData, DestinationPosition);
  }
  else
  {
    /* clears the passed input value from the passed bit position */
    Stm_lClrBit(DestinationData, DestinationPosition);
  }
}

#if (STM_DEV_ERROR_DETECT == STD_ON)
/*******************************************************************************
** Syntax : LOCAL_INLINE Std_ReturnType Stm_lModnumAndCmpregDetCheck          **
**      (const uint8 ModuleNumber,const uint8 CompareRegisterId,              **
**                             const uint8 ServiceId,const uint32 CoreId)     **
**                                                                            **
** Service ID:        none                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Reentrant                                               **
**                                                                            **
** Parameters(in)   : ModuleNumber - Stm Peripheral number                    **
**                    CompareRegisterId - Compare register number             **
**                                                                            **
** Parameters (out):  none                                                    **
**                                                                            **
** Return value:      ErrStatus (Std_ReturnType)                              **
**                                                                            **
** Description :  Local function to check the module number and compare       **
**                register values are valid and report DET in case of wrong   **
**                parameter is passed                                         **
**                                                                            **
** Traceability:                                                              **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Stm_lModnumAndCmpregDetCheck
(
   const uint8 ModuleNumber, const uint8 CompareRegisterId, 
   const uint8 ServiceId, const uint32 CoreId
)
{
  Std_ReturnType                      ErrStatus;
  ErrStatus = Stm_lModnumberDetCheck(ModuleNumber, ServiceId, CoreId);

  /* Check No DET present */
  if (ErrStatus == E_OK)
  {
    /* Check CMP Register value is valid */
    if ((Stm_ModuleMap[CoreId].CmpRegId == STM_CMP0_CMP1_USED) && \
        (CompareRegisterId > STM_MAX_CMP_REG_NUM))
    {
      /* Call local function to report DET for invalid CMP reg id is passed */
      Stm_lReportError(ServiceId, STM_E_CMPREG_FAILED);
      /* Update ErrStatus with E_NOT_OK */
      ErrStatus = (Std_ReturnType)E_NOT_OK;
    }
    else if(Stm_ModuleMap[CoreId].CmpRegId == STM_CMP0_CMP1_UNUSED)
    {
      /* Call local function to report DET for invalid CMP reg id is passed */
      Stm_lReportError(ServiceId, STM_E_CMPREG_FAILED);
      /* Update ErrStatus with E_NOT_OK */
      ErrStatus = (Std_ReturnType)E_NOT_OK;
    }
    else if(((Stm_ModuleMap[CoreId].CmpRegId == STM_CMP0_USED) &&  \
             (CompareRegisterId != 0x0U)) || \
             ((Stm_ModuleMap[CoreId].CmpRegId == STM_CMP1_USED) && \
             (CompareRegisterId != STM_COMPARE_VAL)))
    {
      /* Call local function to report DET for invalid CMP reg id is passed */
      Stm_lReportError(ServiceId, STM_E_CMPREG_FAILED);
      /* Update ErrStatus with E_NOT_OK */
      ErrStatus = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
      /* added for MISRA */
    }
  }
  return (ErrStatus);
} /* End of Stm_lModnumAndCmpregDetCheck() function */



/*******************************************************************************
** Syntax : LOCAL_INLINE Std_ReturnType Stm_lModnumberDetCheck(               **
**      const uint8 ModuleNumber,const uint8 ServiceId, const uint32 CoreId)  **
**                                                                            **
** Service ID:        none                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Reentrant                                               **
**                                                                            **
** Parameters(in)   : ModuleNumber - Stm Peripheral number                    **
**                                                                            **
** Parameters (out):  none                                                    **
**                                                                            **
** Return value:      ErrStatus (Std_ReturnType)                              **
**                                                                            **
** Description :  Local function to check the module number is valid and      **
**                call DET report error in case of wrong parameter is passed  **
**                                                                            **
** Traceability:                                                              **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Stm_lModnumberDetCheck
(
  const uint8 ModuleNumber,const uint8 ServiceId,const uint32 CoreId
)
{
  Std_ReturnType  ErrStatus;
  ErrStatus = E_OK;

  /* Check STM timer number is matching with timer allocated in core */
  if ((ModuleNumber != Stm_ModuleMap[CoreId].StmModID) || \
      (ModuleNumber == STM_TIMER_UNUSED))
  {
    /* Call local function to report DET STM module not 
       configured for this Core*/
    Stm_lReportError(ServiceId, STM_E_CORE_TIMER_MISMATCH );
    /* Update ErrStatus with E_NOT_OK */
    ErrStatus = (Std_ReturnType)E_NOT_OK;
  }
  return (ErrStatus);
} /* End of Stm_lModnumberDetCheck() function */

/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax : LOCAL_INLINE void Stm_lReportError( const uint8 ApiId,            **
**                                          const uint8 ErrorId)              **
**                                                                            **
** Description :    Function to report DET                                    **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant                                                **
**                                                                            **
** Parameters (in):  ApiId - Service ID of the API reporting an error         **
**                   ErrorId - ID of the error reported                       **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :  Local function to report DET error                          **
**                                                                            **
** Traceability:  NA                                                          **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Stm_lReportError(const uint8 ApiId,
                                   const uint8 ErrorId)
{
  #if (STM_DEV_ERROR_DETECT == STD_ON)
  Det_ReportError(
    STM_MODULE_ID,
    STM_INSTANCE_ID,
    ApiId,
    ErrorId);/* End of report to DET */
  #endif
}
#endif /* (STM_DEV_ERROR_DETECT == STD_ON) */

/*******************************************************************************
** Syntax             : LOCAL_INLINE Stm_ModuleParameterType* \               **
**                           Stm_lGetModNumStatusPtr(void)                    **
**                                                                            **
** Service ID:        none                                                    **
**                                                                            **
** Sync/Async:        Synchronous                                             **
**                                                                            **
** Reentrancy:        Reentrant                                               **
**                                                                            **
** Parameters(in)   : ModuleNumber - Stm Peripheral number                    **
**                                                                            **
** Parameters (out):  none                                                    **
**                                                                            **
** Return value:  Stm_ModuleParameterType*)Stm_TimerCoreAllocation            **
**                                                                            **
** Description :  Local function :Get the STM peripheral core allocation ptr  **
**                                                                            **
** Traceability:                                                              **
*******************************************************************************/
LOCAL_INLINE  Stm_ModuleParameterType* Stm_lGetModNumStatusPtr(void)
{
  uint32 CoreId;
  CoreId = Mcal_GetCpuIndex();
  /* MISRA2012_RULE_11_3_JUSTIFICATION: This rule  violation is agreed as
     we need to store the address passed is in the called function in
     many scenarios.   */
  /* MISRA2012_RULE_11_8_JUSTIFICATION: A cast shall not remove any const
     or volatile qualification from the type pointed to by a pointer   */
  return Stm_TimerCoreAllocation[CoreId];
}

/*******************************************************************************
** Traceability      :                                                        **
**                                                                            **
** Syntax           : Stm_TotalTimerCaptureType                               **
**                     Stm_lReadTotalTimer(const uint8 ModuleNumber)      **
**                                                                            **
** Service ID       : NA                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                       **
**                                                                            **
** Parameters(in)   : ModuleNumber - Stm Peripheral number                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : Stm_TotalTimerCaptureType : Holds the lower and upper   **
**                    32-bit values of a 64-bit STM timer                     **
**                                                                            **
** Description      : This function returns complete 64 bit STM Timer value   **
**                    of a particular STM module                              **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Stm_TotalTimerCaptureType Stm_lReadTotalTimer(const uint8 
ModuleNumber)
{
  Stm_TotalTimerCaptureType TotalTimerCapture;
  TotalTimerCapture.LowerPart = 0x0U;
  TotalTimerCapture.UpperPart = 0x0U;
 
  /* Returns the TIM0 and CAP register values based on requested Mod num */

  TotalTimerCapture.LowerPart = STM_BASE[ModuleNumber].TIM0.U;
  TotalTimerCapture.UpperPart = STM_BASE[ModuleNumber].CAP.U;
  
  return TotalTimerCapture;
}


/*******************************************************************************
**                                                                            **
** Syntax           : void Stm_Isr(const uint8 ModuleNumber,                  **
**                                              const uint32 InterruptNode)   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : ModuleNumber - Stm Peripheral number                    **
**                    InterruptNode - 0 or 1                                  **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : This function:                                          **
**                      - is the interrupt handler and collects the interrupt **
**                        node and invoke the call-back function              **
*******************************************************************************/
void Stm_Isr(const uint32 ModuleNumber, const uint32 InterruptNode)
{
  const Stm_ModuleParameterType      *StmkernelStatusPtr;
  uint8 CompareRegisterId;
  uint8 MatchStartBit;
  uint32 Cmpval;
  uint8 shiftval;
  Stm_TotalTimerCaptureType Stm_64Bit_Timer_Value;
  /* Get the STM peripheral core allocation pointer */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: casting of register address to
     corresponding structure pointer   */
  StmkernelStatusPtr = Stm_lGetModNumStatusPtr();

  /* Identify the Compare register ID mapped to the invoked interrupt node */
  CompareRegisterId =
    Stm_lGetBit(StmkernelStatusPtr->InterruptNodeMap, (uint8)InterruptNode);
  /* In continuous mode CMP value is udpated and call back notification
       is given continuously */
  if(Stm_lGetBit(StmkernelStatusPtr->TimerMode,
                 CompareRegisterId) == STM_COMPARE_VAL)
  {
    /* Reload the compare register again as the request is to invoke the call
       back function in continuous mode */
    MatchStartBit = (CompareRegisterId == 0x0U) ?(STM_BASE[ModuleNumber].
    CMCON.B.MSTART0):(STM_BASE[ModuleNumber].CMCON.B.MSTART1);
   
    /* load 64 bits timer value */
    Stm_64Bit_Timer_Value= Stm_lReadTotalTimer((uint8)ModuleNumber);
   
    shiftval = STM_MAX_SHIFT_VALUE - MatchStartBit;
  
    Cmpval = StmkernelStatusPtr->CompareRegValue[CompareRegisterId]
             + (((Stm_64Bit_Timer_Value.LowerPart) >> MatchStartBit) | 
             ((Stm_64Bit_Timer_Value.UpperPart) << shiftval));
    
    STM_BASE[ModuleNumber].CMP[CompareRegisterId].U  = (Cmpval & STM_SET_MASK);
    
  }
  /* In one shot mode, interrupt is disabled, notification is given once */
  else
  {
    if(CompareRegisterId == 0x0U)
    {
      /* Requested for one shot mode, So disable the service request */
      Mcal_SetBitAtomic((&STM_BASE[ModuleNumber].ICR.U), STM_ICR_CMP0EN_OFF, \
                        STM_ICR_CMP0_DISABLE_MSK, STM_ICR_CMP0_DISABLE_VAL);
    }
    else
    {
      /* Requested for one shot mode, So disable the service request */
      Mcal_SetBitAtomic((&STM_BASE[ModuleNumber].ICR.U), STM_ICR_CMP1EN_OFF, \
                        STM_ICR_CMP1_DISABLE_MSK, STM_ICR_CMP1_DISABLE_VAL);
    }
  }

  /* Check and invoke the call-back Function */
  if (StmkernelStatusPtr->Stm_ArrayFunctionPtr[CompareRegisterId] != NULL_PTR)
  {
    StmkernelStatusPtr->Stm_ArrayFunctionPtr[CompareRegisterId]();
  }
}

/*Memory Map of the STM Code*/
#define STM_STOP_SEC_CODE_QM_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Stm_MemMap.h"
