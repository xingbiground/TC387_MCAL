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
**  FILENAME     : Dma.c                                                      **
**                                                                            **
**  VERSION      : 40.0.0                                                     **
**                                                                            **
**  DATE         : 2021-10-29                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Dma Driver source file                                     **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* [cover parentID={F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}][/cover] */
/* Inclusion of Dma.h header file */ 
#include "Dma.h"

/* Inclusion of Dma sfr file */
#include "IfxDma_reg.h"
#include "IfxDma_bf.h"

#include "IfxSrc_reg.h"
#include "IfxSrc_bf.h"

#if( (DMA_INIT_DEINIT_API_MODE     != DMA_MCAL_SUPERVISORMODE)||\
     (DMA_RUNTIME_API_MODE  != DMA_MCAL_SUPERVISORMODE) )
#include "McalLib_OsStub.h"
#endif

#if(DMA_DEV_ERROR_DETECT == STD_ON)
/* Inclusion of DET file */
#include "Det.h"
#endif

#if(DMA_SAFETY_ENABLE == STD_ON)
/* Inclusion of Safety errror file */
#include "Mcal_SafetyError.h"
#endif

/* Inclusion of Dma Schm file */
/* [cover parentID={28845613-6BC6-4efe-8C0A-8FF070992664}]
 * Schm
 * [/cover] */
#include "SchM_Dma.h"


/* [cover parentID= {E5EC7988-786F-4462-94DB-DBE2FDA99C77}]
Header inclusions
[/cover] */
/* [cover parentID= {FCE37B29-ADA7-4cb4-A1F1-44D825185DFA}]
C file
[/cover] */
/* [cover parentID= {A30D1C75-DEF8-4441-89FE-42122B3FB04F}]
C file
[/cover] */
/* [cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
* No callouts used
* [/cover]*/


/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/
/*************** SW Version Checks ***************/
#ifndef DMA_SW_MAJOR_VERSION
  #error "DMA_SW_MAJOR_VERSION is not defined."
#endif

#ifndef DMA_SW_MINOR_VERSION
  #error "DMA_SW_MINOR_VERSION is not defined."
#endif

#ifndef DMA_SW_PATCH_VERSION
  #error "DMA_SW_PATCH_VERSION is not defined."
#endif

/* Check for Correct inclusion of headers */
#if ( DMA_SW_MAJOR_VERSION != 20U )
  #error "DMA_SW_MAJOR_VERSION does not match."
#endif
#if ( DMA_SW_MINOR_VERSION != 10U )
  #error "DMA_SW_MINOR_VERSION does not match."
#endif
#if ( DMA_SW_PATCH_VERSION != 0U )
  #error "DMA_SW_PATCH_VERSION does not match."
#endif


/* Version check for Module */
/* [cover parentID={D8158051-C893-447f-AA84-C2D8ACCDC415}]
 * Version Check
 * [/cover]*/



/* Version check for DET module inclusion */
/* [cover parentID={40346454-FD0D-4a6d-B759-A5DA0012E157}]
 * Version Check
 * [/cover]*/

#if(DMA_DEV_ERROR_DETECT == STD_ON)

  #ifndef DET_AR_RELEASE_MAJOR_VERSION
    #error "DET_AR_RELEASE_MAJOR_VERSION is not defined."
  #endif

  #if (DET_AR_RELEASE_MAJOR_VERSION != DMA_AR_RELEASE_MAJOR_VERSION)
    #error "DET_AR_RELEASE_MAJOR_VERSION does not match."
  #endif

#endif

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

/************* USER MODE - SUPERVISOR MODE HANDLING MACROS ****************** */

/* ---- INIT DEINIT MACROS ---- */
#if DMA_INIT_DEINIT_API_MODE == DMA_MCAL_SUPERVISORMODE
  /* Library APIs  */

  /* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
   * 'DMA_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG'
   * defined for User mode support in code.
   * No side effects foreseen by violating this MISRA rule. */
  #define DMA_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(RegAdd,Data) \
  Mcal_WriteSafetyEndInitProtReg(RegAdd,Data)

  /* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
   * 'DMA_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG'
   * defined for User mode support in code.
   * No side effects foreseen by violating this MISRA rule. */
  #define DMA_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG(RegAdd,Data)   \
    Mcal_WritePeripEndInitProtReg(RegAdd,Data)

  /* Supervisory mode registers */
  /* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
   * 'DMA_SFR_INIT_DEINIT_WRITE32'
   * defined for User mode support in code.
   * No side effects foreseen by violating this MISRA rule. */
  #define  DMA_SFR_INIT_DEINIT_WRITE32(reg, value) ((*(reg)) = (uint32)(value));

#else

  /* User mode */

  /* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
   * 'DMA_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG'
   * defined for User mode support in code.
   * No side effects foreseen by violating this MISRA rule. */
  #define DMA_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(RegAdd,Data)    \
                MCAL_LIB_WRITESAFETYENDINITPROTREG(RegAdd,Data)

  /* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
   * 'DMA_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG'
   * defined for User mode support in code.
   * No side effects foreseen by violating this MISRA rule. */
  #define DMA_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG(RegAdd,Data)   \
            MCAL_LIB_WRITEPERIPENDINITPROTREG(RegAdd,Data)

  /* Supervisory mode registers */
  /* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
   * 'DMA_SFR_INIT_DEINIT_WRITE32'
   * defined for User mode support in code.
   * No side effects foreseen by violating this MISRA rule. */
  #define  DMA_SFR_INIT_DEINIT_WRITE32(reg, value)    \
                MCAL_SFR_OS_WRITE32(DMA_MODULE_ID, reg, value)

#endif

/* ---- RUNTIME MACROS ---- */
#if DMA_RUNTIME_API_MODE == DMA_MCAL_SUPERVISORMODE
  /* Library APIs  */
#if (DMA_CHDEINIT_API == STD_ON)
  /* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
   * 'DMA_LIB_RUNTIME_WRITESAFETYENDINITPROTREG'
   * defined for User mode support in code.
   * No side effects foreseen by violating this MISRA rule. */
  #define DMA_LIB_RUNTIME_WRITESAFETYENDINITPROTREG(RegAdd,Data) \
          Mcal_WriteSafetyEndInitProtReg(RegAdd,Data)
#endif
  /* Supervisory mode registers */
  /* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
   * 'DMA_SFR_RUNTIME_WRITE32'
   * defined for User mode support in code.
   * No side effects foreseen by violating this MISRA rule. */
  #define  DMA_SFR_RUNTIME_WRITE32(reg, value)     ((*(reg)) = (uint32)(value));

#else
  /* User Mode */

  /* Library APIs  */
#if (DMA_CHDEINIT_API == STD_ON) 
  /* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
   * 'DMA_LIB_RUNTIME_WRITESAFETYENDINITPROTREG'
   * defined for User mode support in code.
   * No side effects foreseen by violating this MISRA rule. */
  #define DMA_LIB_RUNTIME_WRITESAFETYENDINITPROTREG(RegAdd,Data)    \
          MCAL_LIB_WRITESAFETYENDINITPROTREG(RegAdd,Data)
#endif
  /* Supervisory mode registers */
  /* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
   * 'DMA_SFR_RUNTIME_WRITE32'
   * defined for User mode support in code.
   * No side effects foreseen by violating this MISRA rule. */
  #define  DMA_SFR_RUNTIME_WRITE32(reg, value)    \
           MCAL_SFR_OS_WRITE32(DMA_MODULE_ID, reg, value)

#endif
/* DMA_RUNTIME_API_MODE == DMA_MCAL_SUPERVISORMODE */

/******************************************************************************/

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'DMA_CH_STATE_LENGTH'defined for handling DMA channel bits.
 * No side effects foreseen by violating this MISRA rule. */
#define DMA_CH_STATE_LENGTH(noOfAllocation) ( ((noOfAllocation-(1U))/8U)+1U )


/******************************************************************************/

/* Macros for the fixed values */
#define DMA_BIT_CLEAR       (0x00U)
#define DMA_BIT_SET         (0x01U)

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'DMA_GET_CH_INITSTATE' for handling DMA channel init status.
 * No side effects foreseen by violating this MISRA rule. */
#define DMA_GET_CH_INITSTATE(Channel, lCoreId) \
  ((Dma_ChannelStatesPerCore[lCoreId][\
  ((Dma_kConfigPtr->Dma_ChannelMaps[Channel].\
                    Dma_ChannelConfIndexMap/(uint8)8))] >> \
  ((uint8)((Dma_kConfigPtr->Dma_ChannelMaps[Channel].\
                            Dma_ChannelConfIndexMap)%(uint8)8))) & DMA_BIT_SET)

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'DMA_GET_SETBIT_POS'is defined to get the position of the bit which is
 * set in the provided value. No side effects foreseen by
 * violating this MISRA rule. */
#define DMA_GET_SETBIT_POS(Value) ((uint8)(31u - Mcal_CountLeadingZeros(Value)))
#define DMA_TRL_WORD_OFFSET   ((uint8)32)
/******************************************************************************/
/* Core initialization state macros */

/* CPU core is initialized */
#define DMA_CPUCORE_INIT        ((uint8)0x01U)
/* CPU core is not initialized */
#define DMA_CPUCORE_UNINIT      ((uint8)0x00U)

/* CPU core is uninitializaton started */
#if (DMA_DEINIT_API == STD_ON)
#define DMA_UNINIT_STARTED      ((uint8)0x02U)
#endif

/* DMA channel initialized */
#define DMA_DRIVER_CHINIT       ((uint8)0x01U)

#if (DMA_BUFFER_SWITCH_API == STD_ON)
  /* Double Source Buffering      */
  #define DMA_DOUBLE_BUFFER_MODE_START (8U)
  /* Double Destination Buffering */
  #define DMA_DOUBLE_BUFFER_MODE_END   (11U)
#endif

/* DMA register default value */
#define DMA_REGISTER_RESET_VALUE    ((uint32)0x00000000U)

#if (DMA_DEINIT_API == STD_ON)
#define DMA_ACCENR0_REG_RESET       ((uint32)0xFFFFFFFFU)
#endif
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is used across the code in
Api deinit condition only.
Hence this macro will be unused in other pre-compile conditions */
#define DMA_ME_ERR_RESET            ((uint32)0x04030000U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is used across the code in
Api deinit condition only.
Hence this macro will be unused in other pre-compile conditions */
#define DMA_MODE_REG_RESET          ((uint32)0x00000001U)

#define DMA_CHCSR_CLEAR_VALUE       ((uint32)0x06000000U)
#define DMA_CHCSR_SCH_BIT_POS       ((uint32)0x80000000U)

#define DMA_CHANNEL_MAP_RESET_VALUE ((uint8)0xFF)

/* DMA MoveEngine 0 */
#define DMA_MOVE_ENGINE_0  ((uint8) 200U)
/* DMA MoveEngine 1 */
#define DMA_MOVE_ENGINE_1  ((uint8) 201U)

/* Mask to clear all Move engine error status */
#define DMA_CLEAR_ERROR_MASK ((uint32)0x07330000)

/* Dma Timeout value */
#define DMA_TIMEOUT         (0x0000FFFFU)

/* DMA Max link list nodes */
#define DMA_MAX_LINKED_LIST_NODE (0xFFU)

/* Mask for the TRL and ETRL bits */
#define DMA_TSR_ETRL_TRL_MASK \
          ( ((uint32)IFX_DMA_TSR_TRL_MSK  << IFX_DMA_TSR_TRL_OFF ) |\
            ((uint32)IFX_DMA_TSR_ETRL_MSK << IFX_DMA_TSR_ETRL_OFF) )

/* Shadow control settings
 * 0000b - Shadow Disabled. Source and destination registers written directly
 * 0001b - Source Address Buffering (Read Only)
 * 0010b - Destination Address Buffering (Read Only)
 * 0011b - Reserved. (DMA_SHADOW_ADDR_RES1_MASK)
 * 0100b - Reserved. (DMA_SHADOW_ADDR_RES2_MASK)
 * 0101b - Source Address Buffering (Direct Write)
 * 0110b - Destination Address Buffering (Direct Write)
 * 0111b - Reserved. (DMA_SHADOW_ADDR_RES3_MASK)
 * 1000b - Double Source Buffering. Software Switch Only
 * 1001b - Double Source Buffering. Automatic Hardware and Software Switch
 * 1010b - Double Destination Buffering. Software Switch Only
 * 1011b - Double Destination Buffering. Automatic Hardware and Software Switch
 * 1100b - DMA Linked List.
 * 1101b - Accumulated Linked List
 * 1110b - Safe Linked List
 * 1111b - Conditional Linked List
 */
#define DMA_SHADOW_ADDR_RES2_MASK       ((uint8)0x04U)
#define DMA_SHADOW_ADDR_RES3_MASK       ((uint8)0x07U)

#if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
  #define DMA_DBL_SRC_BUFF_SW_SWITCH      ((uint8)0x08U)
  #define DMA_DBL_SRC_BUFF_HW_SWITCH      ((uint8)0x09U)
  #define DMA_DBL_DEST_BUFF_SW_SWITCH     ((uint8)0x0AU)
  #define DMA_DBL_DEST_BUFF_HW_SWITCH     ((uint8)0x0BU)
  #define DMA_CONDITIONAL_LINKED_LIST     ((uint8)0x0FU)
#endif


/* MoveEngine error status mask */
#define DMA_ERROR_STATUS_MASK   \
               (( (uint32)DMA_BIT_SET << IFX_DMA_ME_ERRSR_DLLER_OFF ) |\
                ( (uint32)DMA_BIT_SET << IFX_DMA_ME_ERRSR_SLLER_OFF ) |\
                ( (uint32)DMA_BIT_SET << IFX_DMA_ME_ERRSR_RAMER_OFF ) |\
                ( (uint32)DMA_BIT_SET << IFX_DMA_ME_ERRSR_SRIER_OFF ) |\
                ( (uint32)DMA_BIT_SET << IFX_DMA_ME_ERRSR_SPBER_OFF ) |\
                ( (uint32)DMA_BIT_SET << IFX_DMA_ME_ERRSR_DER_OFF   ) |\
                ( (uint32)DMA_BIT_SET << IFX_DMA_ME_ERRSR_SER_OFF   ) )


/* Interrupt Type of Service */
#define DMA_GPSR_TOS_CPU0                  (0x0000)
#if MCAL_NO_OF_CORES > 0x01U
  #define DMA_GPSR_TOS_CPU1                (0x1000)
#endif
#if MCAL_NO_OF_CORES > 0x02U
  #define DMA_GPSR_TOS_CPU2                (0x1800)
#endif
#if MCAL_NO_OF_CORES > 0x03U
  #define DMA_GPSR_TOS_CPU3                (0x2000)
#endif
#if MCAL_NO_OF_CORES > 0x04U
  #define DMA_GPSR_TOS_CPU4                (0x2800)
#endif
#if MCAL_NO_OF_CORES > 0x05U
  #define DMA_GPSR_TOS_CPU5                (0x3000)
#endif


#define DMA_START_SEC_CONST_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Dma_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
#include "Dma_MemMap.h"

/* TOS and Core mapper */
/* MISRA2012_RULE_8_9_JUSTIFICATION: This constant is made used in ISRs
defined in Dma.c for the error interrupt handling. Since the variable
need to be allocated to the desired sections, it can't be made block
scope. No side effects foreseen by violating this MISRA rule. */
static const uint32 Dma_CoreTosMap[MCAL_NO_OF_CORES] =
{
    DMA_GPSR_TOS_CPU0,
  #if MCAL_NO_OF_CORES > 0x01U
    DMA_GPSR_TOS_CPU1,
  #endif
  #if MCAL_NO_OF_CORES > 0x02U
    DMA_GPSR_TOS_CPU2,
  #endif
  #if MCAL_NO_OF_CORES > 0x03U
    DMA_GPSR_TOS_CPU3,
  #endif
  #if MCAL_NO_OF_CORES > 0x04U
    DMA_GPSR_TOS_CPU4,
  #endif
  #if MCAL_NO_OF_CORES > 0x05U
    DMA_GPSR_TOS_CPU5
  #endif
};


#define DMA_STOP_SEC_CONST_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Dma_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'Dma_CoreTosMap' before
 * #include memap.h - Accepted deviation as per AUTOSAR */
#include "Dma_MemMap.h"

/* [cover parentID={1141483E-A61D-4050-A043-1C774DD96DF1}]
 * Memmap Section
 * [/cover]*/
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
 * Variable Section
 * [/cover]*/
/* [cover parentID={5E19FD63-33BC-464e-8FDE-61062DAD8F28}]
 * Variable Section
 * [/cover]*/
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'Dma_CoreTosMap' before
 * #include memap.h - Accepted deviation in AUTOSAR */
#define DMA_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Dma_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'Dma_CoreTosMap' before
 * #include memap.h - Accepted deviation as per AUTOSAR */
#include "Dma_MemMap.h"
static const Dma_ConfigType *Dma_kConfigPtr;
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'Dma_CoreTosMap' before
 * #include memap.h - Accepted deviation in AUTOSAR */
#define DMA_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Dma_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'Dma_kConfigPtr' and
 * 'Dma_CoreTosMap' before #include memap.h - Accepted deviation as per AUTOSAR */
#include "Dma_MemMap.h"


/* ************************************************************************** */
/* ******************** CORE SPECIFIC STATUS OF CHANNELS ******************** */
/* ************************************************************************** */

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going
 * beyond 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going
 * beyond 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going
 * beyond 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going
 * beyond 32 chars because of AS naming convention*/
#define DMA_START_SEC_VAR_CLEARED_ASIL_B_CORE0_8
/* MISRA2012_RULE_4_10_JUSTIFICATION: Dma_Memmap.h is
 * repeatedly included without include guard.
 * This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'Dma_kConfigPtr' and
 * 'Dma_CoreTosMap' before #include memap.h - Accepted deviation as per AUTOSAR */
#include "Dma_MemMap.h"

#if DMA_ALLOCATED_CHANNELS_CORE0 > (0U)
  static uint8 Dma_Core0ChannelState
              [DMA_CH_STATE_LENGTH(DMA_ALLOCATED_CHANNELS_CORE0)];
#endif
/* Initialization status of core 0*/
static uint8 Dma_CpuCore0State;
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going
 * beyond 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going
 * beyond 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going
 * beyond 32 chars because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going
 * beyond 32 chars because of AS naming convention*/
#define DMA_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_8
/* MISRA2012_RULE_4_10_JUSTIFICATION: Dma_Memmap.h is
 * repeatedly included without include guard.
 * This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'Dma_kConfigPtr' and
 * 'Dma_CoreTosMap' before #include memap.h - Accepted deviation as per AUTOSAR */
#include "Dma_MemMap.h"


#if MCAL_NO_OF_CORES > 0x01U
  /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  #define DMA_START_SEC_VAR_CLEARED_ASIL_B_CORE1_8
  /* MISRA2012_RULE_4_10_JUSTIFICATION: Dma_Memmap.h is
   * repeatedly included without include guard.
   * This is as per AUTOSAR */
  /* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of
   * 'Dma_kConfigPtr' and 'Dma_CoreTosMap' before #include
   * memap.h - Accepted deviation as per AUTOSAR */
  #include "Dma_MemMap.h"

  #if DMA_ALLOCATED_CHANNELS_CORE1 > (0U)
    static uint8 Dma_Core1ChannelState
            [DMA_CH_STATE_LENGTH(DMA_ALLOCATED_CHANNELS_CORE1)];
  #endif
  /* Initialization status of core 1*/
  static uint8 Dma_CpuCore1State;

  /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  #define DMA_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_8
  /* MISRA2012_RULE_4_10_JUSTIFICATION: Dma_Memmap.h is
   * repeatedly included without include guard.
   * This is as per AUTOSAR */
  /* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'Dma_kConfigPtr' and
   * 'Dma_CoreTosMap' before #include memap.h - Accepted
   * Accepted deviation as per AUTOSAR */
  #include "Dma_MemMap.h"
#endif


#if MCAL_NO_OF_CORES > 0x02U
  /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  #define DMA_START_SEC_VAR_CLEARED_ASIL_B_CORE2_8
  /* MISRA2012_RULE_4_10_JUSTIFICATION: Dma_Memmap.h is
   * repeatedly included without include guard.
   * This is as per AUTOSAR */
  /* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'Dma_kConfigPtr' and
   * 'Dma_CoreTosMap' before #include memap.h - Accepted deviation 
   * as per AUTOSAR */
  #include "Dma_MemMap.h"

  #if DMA_ALLOCATED_CHANNELS_CORE2 > (0U)
    static uint8 Dma_Core2ChannelState
              [DMA_CH_STATE_LENGTH(DMA_ALLOCATED_CHANNELS_CORE2)];
  #endif
  /* Initialization status of core 2*/
  static uint8 Dma_CpuCore2State;

  /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  #define DMA_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_8
  /* MISRA2012_RULE_4_10_JUSTIFICATION: Dma_Memmap.h is
   * repeatedly included without include guard.
   * This is as per AUTOSAR */
  /* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'Dma_kConfigPtr' and
   * 'Dma_CoreTosMap' before #include memap.h - Accepted deviation 
   * as per AUTOSAR */
  #include "Dma_MemMap.h"
#endif


#if MCAL_NO_OF_CORES > 0x03U
  /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  #define DMA_START_SEC_VAR_CLEARED_ASIL_B_CORE3_8
  /* MISRA2012_RULE_4_10_JUSTIFICATION: Dma_Memmap.h is
   * repeatedly included without include guard.
   * This is as per AUTOSAR */
  /* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'Dma_kConfigPtr' and
   * 'Dma_CoreTosMap' before #include memap.h - Accepted
   * deviation as per AUTOSAR */
  #include "Dma_MemMap.h"

  #if DMA_ALLOCATED_CHANNELS_CORE3 > (0U)
    static uint8 Dma_Core3ChannelState
                 [DMA_CH_STATE_LENGTH(DMA_ALLOCATED_CHANNELS_CORE3)];
  #endif
  /* Initialization status of core 3*/
  static uint8 Dma_CpuCore3State;

  /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  #define DMA_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_8
  /* MISRA2012_RULE_4_10_JUSTIFICATION: Dma_Memmap.h is
   * repeatedly included without include guard.
   * This is as per AUTOSAR */
  /* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'Dma_kConfigPtr' and
   * 'Dma_CoreTosMap' before #include memap.h -
   * Accepted deviation as per AUTOSAR */
  #include "Dma_MemMap.h"
#endif


#if MCAL_NO_OF_CORES > 0x04U
  /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  #define DMA_START_SEC_VAR_CLEARED_ASIL_B_CORE4_8
  /* MISRA2012_RULE_4_10_JUSTIFICATION: Dma_Memmap.h is
   * repeatedly included without include guard.
   * This is as per AUTOSAR */
  /* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'Dma_kConfigPtr' and
   * 'Dma_CoreTosMap' before #include memap.h -
   * Accepted deviation as per AUTOSAR */
  #include "Dma_MemMap.h"

  #if DMA_ALLOCATED_CHANNELS_CORE4 > (0U)
    static uint8 Dma_Core4ChannelState
               [DMA_CH_STATE_LENGTH(DMA_ALLOCATED_CHANNELS_CORE4)];
  #endif
  /* Initialization status of core 4*/
  static uint8 Dma_CpuCore4State;

  /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going
   * beyond 32 chars becadse of AS naming convention*/
  /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  #define DMA_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_8
  /* MISRA2012_RULE_4_10_JUSTIFICATION: Dma_Memmap.h is
   * repeatedly included without include guard.
   * This is as per AUTOSAR */
  /* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'Dma_kConfigPtr' and
   * 'Dma_CoreTosMap' before #include memap.h -
   * Accepted deviation as per AUTOSAR */
  #include "Dma_MemMap.h"
#endif


#if MCAL_NO_OF_CORES > 0x05U
  /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  #define DMA_START_SEC_VAR_CLEARED_ASIL_B_CORE5_8
  /* MISRA2012_RULE_4_10_JUSTIFICATION: Dma_Memmap.h is
   * repeatedly included without include guard.
   * This is as per AUTOSAR */
  /* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'Dma_kConfigPtr' and
   * 'Dma_CoreTosMap' before #include memap.h -
   * Accepted deviation as per AUTOSAR */
  #include "Dma_MemMap.h"

  #if DMA_ALLOCATED_CHANNELS_CORE5 > (0U)
    static uint8 Dma_Core5ChannelState
                [DMA_CH_STATE_LENGTH(DMA_ALLOCATED_CHANNELS_CORE5)];
  #endif
  /* Initialization status of core 5*/
  static uint8 Dma_CpuCore5State;

  /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going
   * beyond 32 chars because of AS naming convention*/
  #define DMA_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_8
  /* MISRA2012_RULE_4_10_JUSTIFICATION: Dma_Memmap.h is
   * repeatedly included without include guard.
   * This is as per AUTOSAR */
  /* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'Dma_kConfigPtr' and
   * 'Dma_CoreTosMap' before #include memap.h -
   * Accepted deviation as per AUTOSAR */
  #include "Dma_MemMap.h"
#endif


#define DMA_START_SEC_CONST_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Dma_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'Dma_kConfigPtr' and
 * 'Dma_CoreTosMap' before #include memap.h - Accepted deviation as per AUTOSAR */
#include "Dma_MemMap.h"
/* Channel States for all the cores */
static uint8* const Dma_ChannelStatesPerCore[MCAL_NO_OF_CORES] =
{
  #if DMA_ALLOCATED_CHANNELS_CORE0 > (0U)
    Dma_Core0ChannelState,
  #else
    NULL_PTR,
  #endif
  #if MCAL_NO_OF_CORES > 0x01U
    #if DMA_ALLOCATED_CHANNELS_CORE1 > (0U)
      Dma_Core1ChannelState,
    #else
      NULL_PTR,
    #endif
  #endif
  #if MCAL_NO_OF_CORES > 0x02U
    #if DMA_ALLOCATED_CHANNELS_CORE2 > (0U)
      Dma_Core2ChannelState,
    #else
      NULL_PTR,
    #endif
  #endif
  #if MCAL_NO_OF_CORES > 0x03U
    #if DMA_ALLOCATED_CHANNELS_CORE3 > (0U)
      Dma_Core3ChannelState,
    #else
      NULL_PTR,
    #endif
  #endif
  #if MCAL_NO_OF_CORES > 0x04U
    #if DMA_ALLOCATED_CHANNELS_CORE4 > (0U)
      Dma_Core4ChannelState,
    #else
      NULL_PTR,
    #endif
  #endif
  #if MCAL_NO_OF_CORES > 0x05U
    #if DMA_ALLOCATED_CHANNELS_CORE5 > (0U)
      Dma_Core5ChannelState,
    #else
      NULL_PTR,
    #endif
  #endif
};

static uint8* const Dma_CoreState[MCAL_NO_OF_CORES] =
{
    &Dma_CpuCore0State,
  #if MCAL_NO_OF_CORES > 0x01U
    &Dma_CpuCore1State,
  #endif
  #if MCAL_NO_OF_CORES > 0x02U
    &Dma_CpuCore2State,
  #endif
  #if MCAL_NO_OF_CORES > 0x03U
    &Dma_CpuCore3State,
  #endif
  #if MCAL_NO_OF_CORES > 0x04U
    &Dma_CpuCore4State,
  #endif
  #if MCAL_NO_OF_CORES > 0x05U
    &Dma_CpuCore5State,
  #endif
};
#define DMA_STOP_SEC_CONST_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Dma_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'Dma_kConfigPtr' and
 * 'Dma_CoreTosMap' before #include memap.h - Accepted deviation as per AUTOSAR */
#include "Dma_MemMap.h"

/*******************************************************************************
**                      Private Functions                                     **
*******************************************************************************/
/* [cover parentID={2FB25831-5390-4ca1-ACA3-F3EDA3C7E381}]
 * Code Section
 * [/cover]*/
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
 * Code Section
 * [/cover]*/
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
 * Code Section
 * [/cover]*/
#define DMA_START_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Dma_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'Dma_kConfigPtr' and
 * 'Dma_CoreTosMap' before #include memap.h - Accepted deviation as per AUTOSAR */
#include "Dma_MemMap.h"

static void Dma_lUpdateChannelReg
(
  const uint8 Channel,
  const Dma_ChConfigType* const ChCfgPtr
);
#if((MCAL_NO_OF_CORES > 1U) && (DMA_DEINIT_API == STD_ON)) && ((DMA_MULTICORE_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON))
LOCAL_INLINE Std_ReturnType Dma_lDeInitDetCheck(const uint32 CoreId);
#endif

#if(DMA_DEINIT_API == STD_ON)
static Std_ReturnType Dma_lChDeInit(const uint8 Channel);
#endif

static uint32 Dma_lGetGlobalAddress
(
  const uint32 CpuId,
  const uint32 LocalDsprAddress
);

#if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
static uint32 Dma_lDetCheck
(
  const uint8 ServiceId,
  const uint8 Channel
);
static void Dma_lReportError
(
  const uint8 ApiId,
  const uint8 ErrorId
);
#endif

#if ( (DMA_MULTICORE_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
static void Dma_lReportMulticoreError
(
  const uint8 ApiId,
  const uint8 ErrorId
);
#endif

LOCAL_INLINE Std_ReturnType Dma_lUpdateSelectedReg
(
  Ifx_DMA_CH* const lConfigPtr,
  const Dma_ConfigUpdateType* const Config
);

#if(DMA_INITCHECK_API == STD_ON)
LOCAL_INLINE uint32 Dma_lVerifyChannelReg
(
  const uint8 Channel,
  const Dma_ChConfigType* const ChCfgPtr
);
#endif

static uint32 Dma_lEvaluateMEError
(
  const Ifx_DMA_ME_ERRSR* const lMeErrRegPtr
  /* MISRA2012_RULE_19_2_JUSTIFICATION: Union based type definition for SFR
     access. Variable of SFR type defined for writing into register.
     No side effects foreseen by violating this MISRA rule.*/
);

static void Dma_lMEInterruptHandler
(
  const uint8  lErrorSource,
  const uint32 lErrorData
);


/* CYCLOMATIC_Dma_Init_JUSTIFICATION: This API provides various
   configuration options for which valid check is always needed */
/*******************************************************************************
** Traceability: [cover parentID={6BE894B4-9A33-4410-9B62-2CAF5F1BDB3E}]      **
**                                                                            **
** Syntax : void Dma_Init(const Dma_ConfigType *ConfigPtr)                    **
**                                                                            **
** Description : Service for DMA initialization. This function initializes    **
**               all DMA move engine registers as well as registers of        **
**               configured channels, with the values of the structure        **
**               referenced by the parameter ConfigPtr.                       **
**               This function should be called before calling any other      **
**               Dma API                                                      **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x01                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  ConfigPtr - Pointer to DMA Driver configuration set     **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
void Dma_Init
(
  const Dma_ConfigType* const ConfigPtr
)
{
  const Dma_ChConfigType *lChannelCfgPtr; /* Dma channel configuration */
  uint8 lChIndex = 0U;    /* Channel config index within the RootConfig */
  uint8 lDmaChId = 0U;    /* Dma channel ID of the channel configuration */
  uint32 lCoreId = 0;     /* ID of core used for execution */
  /* MISRA2012_RULE_19_2_JUSTIFICATION: Union based type definition for SFR
     access. Variable of SFR type defined for writing into register.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_DMA_CLC lClcReg;
  uint8 lChState;

  /* [cover parentID={4771550F-9D89-43a4-96D0-4F9D474CD1BA}]
  DET or Safety Enabled
  [/cover] */
  #if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
  uint8 lErrorDetected = FALSE;   /* Status of any error detection */
  #endif

  /* Get the core ID of the core, where we are executing at this moment */
  lCoreId = Mcal_GetCpuIndex();

  #if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
  /* [cover parentID={0046C639-D946-495d-8FFA-6F48B9B66678}]
  Is Configpointer Null
  [/cover] */
  if(ConfigPtr == NULL_PTR)
  {
    /* [cover parentID={CCA94CA2-7E20-4577-9223-6799DDC11C8C}]
    Report DET or safety error for Null pointer
    [/cover] */

    /* Report DET on ConfigPtr error */
    Dma_lReportError( DMA_SID_INIT, DMA_E_NULL_POINTER );
  }
  else if(*(Dma_CoreState[lCoreId]) == DMA_CPUCORE_INIT)
  {
    /* [cover parentID={7A8D3C4F-18DB-4db4-A4D7-7D74E338840A}]
    Report DET or safety error for DMA already initialized
    [/cover] */
    /* [cover parentID={380F07F2-9062-464b-BB99-FDC2AFB8D56A}]
    Is the DMA driver already initialized?
    [/cover] */

    /**! Reaching here is an indication that the API has been invoked
     * again after one init, for the same core. This is not expected
     * and we need to raise a DET here. */

    /* Report DET on DriverState error*/
    Dma_lReportError( DMA_SID_INIT, DMA_E_ALREADY_INITIALIZED );
  }
  else
  #endif
  {
    /* [cover parentID={B3846E55-1A75-4149-A92E-9797432AA1CE}]
    Are we on the master core?
    [/cover] */
    if( MCAL_MASTER_COREID == lCoreId )
    {
      /* Enable DMA module clock */
      lClcReg.U = DMA_CLC.U;
      lClcReg.B.DISR = DMA_BIT_CLEAR;
      /* MISRA2012_RULE_11_3_JUSTIFICATION: Mcal requires the
       * parameter as uint32 const*, but this is a register type  */
      DMA_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG((uint32*)&(DMA_CLC),\
              lClcReg.U);

      /**! DISR: This is the module disable request bit. Here we decide
       * whether the module is enabled or not.
       * 0 - disable is not requested
       * 1 - disable is requested.
       * The hardware takes the action on the disable/enable request
       * here based on the request from the software. Since we are in
       * the init function, it is logical to go for removing any
       * disable requests. */

      /*
       * Proceed for further initialization if DMA clock has been enabled
       */

      /**! DISS: This is the module disable status bit.
       * 0 - DMA is enabled
       * 1 - DMA is disabled
       * Note that the bit status is actually indicating the 'disable'
       * status and not the enable status. Keep a note of this point! */

      if(MODULE_DMA.CLC.B.DISS == DMA_BIT_CLEAR)
      {
        /* [cover parentID={E1794142-0C67-486e-89F4-7317DF2F689B}]
        Is DMA module enabled?
        [/cover] */

        /* ********************************************************
         * ACCESS METHODS - USER MODE AND SUPERVISOR MODE
         * ********************************************************/
        /**! We need to configure the access methods now. The MODE
         * register can configure whether the resource partition
         * accesses the bus in the user mode or in the supervisor
         * mode. We configure this accordingly here. */
        /* MISRA2012_RULE_11_3_JUSTIFICATION: Mcal requires the
         * parameter as uint32 const*, but this is a register type  */
        DMA_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(\
                (uint32*)&(DMA_MODE0),\
                ConfigPtr->DmaHwResourcePartition.DmaHwResourceMode[0]);
        /* MISRA2012_RULE_11_3_JUSTIFICATION: Mcal requires the
         * parameter as uint32 const*, but this is a register type  */
        DMA_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(\
                (uint32*)&(DMA_MODE1),\
                ConfigPtr->DmaHwResourcePartition.DmaHwResourceMode[1]);
        /* MISRA2012_RULE_11_3_JUSTIFICATION: Mcal requires the
         * parameter as uint32 const*, but this is a register type  */
        DMA_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(\
                (uint32*)&(DMA_MODE2),\
                ConfigPtr->DmaHwResourcePartition.DmaHwResourceMode[2]);
        /* MISRA2012_RULE_11_3_JUSTIFICATION: Mcal requires the
         * parameter as uint32 const*, but this is a register type  */
        DMA_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(\
                (uint32*)&(DMA_MODE3),\
                ConfigPtr->DmaHwResourcePartition.DmaHwResourceMode[3]);
        /* [cover parentID={F669A555-712F-44ac-8FA4-29C844314A02}]
        Configure the Mode registers
        [/cover] */

        /* ********************************************************
         * PATTERN DETECTION REGISTERS CONFIGURATION
         * ********************************************************/
        /**! The pattern detection feature is not being used by
         * DMA. Clear those registers! */
        DMA_SFR_INIT_DEINIT_WRITE32(&(DMA_PRR0.U),
                DMA_REGISTER_RESET_VALUE);
        DMA_SFR_INIT_DEINIT_WRITE32(&(DMA_PRR1.U),
                DMA_REGISTER_RESET_VALUE);

        /* ********************************************************
         * ME ERROR NOTIFICATION CONFIGURATION
         * ********************************************************/
        /**! The error handling and notification for the move engine
         * needs to be updated for enabling and disabling the
         * errors. The different errors for the ME - Source error,
         * destination error, and linked list error gets configured
         * here. */
        DMA_SFR_INIT_DEINIT_WRITE32(&(DMA_EER0.U),
                ConfigPtr->DmaMovEngErr[0]);
        DMA_SFR_INIT_DEINIT_WRITE32(&(DMA_EER1.U),
                ConfigPtr->DmaMovEngErr[1]);

        /* ********************************************************
         * ME CLEAR ERROR REGISTERS CONFIGURATION
         * ********************************************************/
        /**! Clear the ME0 and ME1 errors flags using CLRE register
         * The different clear errors flags for the ME - Source error,
         * destination error, SPB errror, SRI error, RAM error,
         * SLL error and DLL error gets cleared here. */
        DMA_SFR_INIT_DEINIT_WRITE32(&(DMA_ME0_CLRE.U),DMA_CLEAR_ERROR_MASK);
        DMA_SFR_INIT_DEINIT_WRITE32(&(DMA_ME1_CLRE.U),DMA_CLEAR_ERROR_MASK);


        /* ********************************************************
         * ACCESS PROTECTION REGISTERS CONFIGURATION
         * ********************************************************/
        /* Access protection registers (0-3) are configured
         * here */
        /* MISRA2012_RULE_11_3_JUSTIFICATION: Mcal requires the
         * parameter as uint32 const*, but this is a register type  */
        DMA_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(\
                (uint32*)&(DMA_ACCEN0_ACCENR0),\
                ConfigPtr->\
                DmaHwResourcePartition.DmaHwResourceBusMasterAccess[0]);
        /* MISRA2012_RULE_11_3_JUSTIFICATION: Mcal requires the
         * parameter as uint32 const*, but this is a register type  */
        DMA_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(\
                (uint32*)&(DMA_ACCEN1_ACCENR0),\
                ConfigPtr->\
                DmaHwResourcePartition.DmaHwResourceBusMasterAccess[1]);
        /* MISRA2012_RULE_11_3_JUSTIFICATION: Mcal requires the
         * parameter as uint32 const*, but this is a register type  */
        DMA_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(\
                (uint32*)&(DMA_ACCEN2_ACCENR0),\
                ConfigPtr->\
                DmaHwResourcePartition.DmaHwResourceBusMasterAccess[2]);
        /* MISRA2012_RULE_11_3_JUSTIFICATION: Mcal requires the
         * parameter as uint32 const*, but this is a register type  */
        DMA_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(\
                (uint32*)&(DMA_ACCEN3_ACCENR0),\
                ConfigPtr->\
                DmaHwResourcePartition.DmaHwResourceBusMasterAccess[3]);
      }
      else
      {
        /**! DMA is not enabled. */;
        #if( (DMA_DEV_ERROR_DETECT == STD_ON) || \
             (DMA_SAFETY_ENABLE == STD_ON) )
        lErrorDetected = TRUE;
        #endif
      }
    }
    else
    {
      /* We are in the slave core, then. Let's do some basic checks
       * before we go ahead */

      /* [cover parentID={9A8CAE42-4633-4cf8-9F7E-A59C13C8A2A6}]
      DET Enabled
      [/cover] */

      #if( (DMA_MULTICORE_ERROR_DETECT == STD_ON) || \
           (DMA_SAFETY_ENABLE          == STD_ON) )
      /* Is the master core init not done? */
      if(*(Dma_CoreState[MCAL_MASTER_COREID]) != DMA_CPUCORE_INIT)
      {
        /* [cover parentID={15AAE64D-5F49-4730-85CF-FF7DF958B4B4}]
        Report DET for master core uninit
        [/cover] */
        /* [cover parentID={9A8CAE42-4633-4cf8-9F7E-A59C13C8A2A6}]
        DET Enabled
        [/cover] */
        /* [cover parentID={6D8432EA-8303-4c4a-AC59-BE7EF1D47613}]
        Before slave core init, was the Master core initialized?
        [/cover] */

        /* Raise a DET for this error! */
        Dma_lReportMulticoreError( DMA_SID_INIT, DMA_E_MASTER_UNINIT );

        /* Keep the error detected status to be checked later */
        lErrorDetected = TRUE;
      }
      else if(ConfigPtr->DmaCoreConfigPtr[lCoreId] == NULL_PTR)
      {
        /* Reaching here is an indication that the init has been called
         * from a core which does not have any resources allocated to
         * it. While that is not expected to do any harm whatsoever,
         * that is a sign that something is not right! We need to
         * report this as an error. */

        /* [cover parentID={4F8C09EF-FC6D-468d-B318-9EC6DB0BF694}]
        Report DET for master core uninit
        [/cover] */
        /* [cover parentID={9A8CAE42-4633-4cf8-9F7E-A59C13C8A2A6}]
        DET Enabled
        [/cover] */
        /* [cover parentID={70A90348-E1D9-47ab-954D-208F8BF60920}]
        Report DET or safety error for core not configured
        [/cover] */
        /* [cover parentID={120E962A-560F-480a-948A-BA055965DF3E}]
        Is the core config pointer NULL?
        [/cover] */
        /* [cover parentID={80F6E9B7-33A6-411d-93CE-56E26B5CF670}]
        Is the core config pointer NULL?
        [/cover] */

        /* Raise a DET for this error! */
        Dma_lReportMulticoreError( DMA_SID_INIT,
                                   DMA_E_CORE_NOT_CONFIGURED );

        /* Keep the error detected status to be checked later */
        lErrorDetected = TRUE;
      }
      else
      {
        /* Do nothing */
      }
      #endif
    }
    #if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
    if( lErrorDetected == FALSE )
    #endif
    {
      /* [cover parentID={17DD8741-4904-4641-BE3E-7ACC9AF32CCB}]
      Is there any error detected?
      [/cover] */

      if(ConfigPtr->DmaCoreConfigPtr[lCoreId] != NULL_PTR)
      {
        /* *********************************************************
         * CHANNEL CONFIGURATION - ALL IN ONE PLACE
         * *********************************************************/
        /* Configure DMA channel registers */
        for(lChIndex = 0U;
            lChIndex < ConfigPtr->DmaCoreConfigPtr[lCoreId]->
            DmaNumberofChConfiguredPerCore;
            lChIndex++)
        {
          /* Get the DMA channel number from the root config*/
          /**! Get the following from the configured values in the
           * tresos:
           * 1. The channel config pointer
           * 2. The DMA channel number.
           * We will link all these here. */
          lChannelCfgPtr = &(ConfigPtr->DmaCoreConfigPtr[lCoreId]->
                  DmaChConfigPtr[lChIndex]);
          lDmaChId = lChannelCfgPtr->DmaChNumber;

          /* Configure Channel Hardware Resource Register */
          /**! This is one single place where all the channel
           * configurations are taken and added to the channel
           * configuration registers. */
          /* [cover parentID={A5F36DD0-FE56-4aa2-8203-28F1C9779722}]
          Initialize the channel registers
          [/cover] */
          Dma_lUpdateChannelReg(lDmaChId, lChannelCfgPtr);

          /* Update DMA channel state */
          /**! Once all these configurations are done, the channel
           * is qualified to be called as 'initialized'. */
          lChState= DMA_DRIVER_CHINIT << (uint8)(lChIndex % (uint8)8);

          /* No null pointer check needed, since the core config
           * pointer exists indicating the channel presence! */
          (Dma_ChannelStatesPerCore[lCoreId])[lChIndex / (uint8)8]
                       |= lChState;

          /* [cover parentID={69D62A5B-01B4-4196-8EC6-9764349019C5}]
          Mark the channel as 'initialized'
          [/cover] */
        }
        /* Mark the core as 'initialized' */
        *(Dma_CoreState[lCoreId]) = DMA_CPUCORE_INIT;
      }
      else
      {
        /* The master core has to be marked as initialized,
         * regardless of the fact whether there was a channel
         * allocated to it */
        if( MCAL_MASTER_COREID == lCoreId )
        {
          /* [cover parentID={27B444A2-0837-47d4-83E3-A9F9AEB41F15}]
          Current core is master core?
          [/cover] */

          /* Mark the core as 'initialized' */
          *(Dma_CoreState[MCAL_MASTER_COREID]) = DMA_CPUCORE_INIT;
          /* [cover parentID={C7BCD80F-964D-4c4a-87B1-79942FE9C002}]
          Mark the master core as initialized
          [/cover] */
        }
      }

    }
    /* Store configuration pointer for future reference */
    Dma_kConfigPtr  = ConfigPtr;
  }
}
#if (DMA_DEINIT_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={022D6327-FC0C-4710-97ED-AD9E67C0C644}]      **
**                                                                            **
** Syntax : void Dma_DeInit(void)                                             **
**                                                                            **
** Description : Service for DMA deinitialization. This function deinitializes**
**               all DMA move engine registers as well as registers of        **
**               configured channels, with their reset value.                 **
**                                                                            **
** Service ID:   0x18                                                         **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
void Dma_DeInit(void)
{
  const Dma_ChConfigType *lChannelCfgPtr; /* Dma channel configuration */
  uint8 lChIndex = 0U;    /* Channel config index within the RootConfig */
  uint8 lDmaChId = 0U;    /* Dma channel ID of the channel configuration */
  uint32 lCoreId = 0U;     /* ID of core used for execution */
  Std_ReturnType ErrorVal = E_OK ;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: Union based type definition for SFR
     access. Variable of SFR type defined for writing into register.
     No side effects foreseen by violating this MISRA rule. */
  Ifx_DMA_CLC lClcReg;

  /* Get the core ID of the core, where we are executing at this moment */
  lCoreId = Mcal_GetCpuIndex();
  /* [cover parentID={2D12A135-6837-41d8-A722-E17D025ADFBA}]
     [/cover] */
  /*Is driver is not Uninit completed state for called core */
  if(*(Dma_CoreState[lCoreId]) != DMA_CPUCORE_UNINIT)  
  {   
    /*Multicore and DET is ON or SAFETY is ON*/
    #if(MCAL_NO_OF_CORES > 1U) && ((DMA_MULTICORE_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON))
    /* Check DET's for the API */
    ErrorVal = Dma_lDeInitDetCheck(lCoreId);
    /* If DET Error not Occured   */    
    /* [cover parentID={4FA423DE-6B1B-4669-B9E4-CF131C7F4AFD}]
       [/cover] */
    if(ErrorVal == E_OK)
    #endif
    {         
      /* set the driver state as uninitializaton started */
      *(Dma_CoreState[lCoreId]) = DMA_UNINIT_STARTED;
   
      /* Check if core is Configured   */      
      /* [cover parentID={327CF17E-820E-4002-9E1A-656F75F20660}]
         [/cover] */
      if(Dma_kConfigPtr->DmaCoreConfigPtr[lCoreId] != NULL_PTR)
      {
        /* Till the last available channel */
        for(
             lChIndex = 0U;
             lChIndex < Dma_kConfigPtr->DmaCoreConfigPtr[lCoreId]->DmaNumberofChConfiguredPerCore;
             lChIndex++
           )
        {        
          lChannelCfgPtr = &(Dma_kConfigPtr->DmaCoreConfigPtr[lCoreId]->DmaChConfigPtr[lChIndex]);
          lDmaChId = lChannelCfgPtr->DmaChNumber;
          /* Driver channel deinitialization */        
          ErrorVal = Dma_lChDeInit(lDmaChId); 
          if( ErrorVal == E_NOT_OK )
          {
            /* As un-initialization is not completed, it will go back to its
               initial state , i,e initialized */
            /* set the driver state as initialized */
            *(Dma_CoreState[lCoreId]) = DMA_CPUCORE_INIT;
            /* come out immediately in case of error */
            break;
          }
        }  
      }  
      /* [cover parentID={2DCB1D77-E5C4-40e7-8288-50DD42AB3C04}]
         [/cover] */
      /* Is CoreId equal to Master CoreId  and channel deinitialization done 
         successfully if channel registers are configured in master core*/
      if ((ErrorVal == E_OK) && (MCAL_MASTER_COREID == lCoreId))
      {
        /* ********************************************************
        *             ACCESS ENABLE REGISTERS 
        * ********************************************************/
        /* Access protection registers (0-3) are reset
        * here */
        /* MISRA2012_RULE_11_3_JUSTIFICATION: Mcal requires the
           parameter as uint32 const*, but this is a register type  */
        DMA_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG( \
            (uint32*)&(DMA_ACCEN0_ACCENR0),DMA_ACCENR0_REG_RESET);
        /* MISRA2012_RULE_11_3_JUSTIFICATION: Mcal requires the
        * parameter as uint32 const*, but this is a register type  */
        DMA_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG( \
            (uint32*)&(DMA_ACCEN1_ACCENR0),DMA_ACCENR0_REG_RESET);
        /* MISRA2012_RULE_11_3_JUSTIFICATION: Mcal requires the
        * parameter as uint32 const*, but this is a register type  */
        DMA_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG( \
            (uint32*)&(DMA_ACCEN2_ACCENR0),DMA_ACCENR0_REG_RESET);
        /* MISRA2012_RULE_11_3_JUSTIFICATION: Mcal requires the
        * parameter as uint32 const*, but this is a register type  */
        DMA_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG( \
            (uint32*)&(DMA_ACCEN3_ACCENR0),DMA_ACCENR0_REG_RESET);
                
        /* ********************************************************
        *           ME CLEAR ERROR REGISTER
        * ********************************************************/
        /** ME clear error register reset */
        DMA_SFR_INIT_DEINIT_WRITE32(&(DMA_ME0_CLRE.U),DMA_CLEAR_ERROR_MASK);
        DMA_SFR_INIT_DEINIT_WRITE32(&(DMA_ME1_CLRE.U),DMA_CLEAR_ERROR_MASK);

        /* ********************************************************
        *           ME ENABLE ERROR REGISTER
        * ********************************************************/
        /** Move engine enable error register reset */
        DMA_SFR_INIT_DEINIT_WRITE32(&(DMA_EER0.U),DMA_ME_ERR_RESET);
        DMA_SFR_INIT_DEINIT_WRITE32(&(DMA_EER1.U),DMA_ME_ERR_RESET);
         
        /* ********************************************************
        *          PATTERN DETECTION REGISTERS
        * ********************************************************/
        /**! The pattern detection register reset */
        DMA_SFR_INIT_DEINIT_WRITE32(&(DMA_PRR0.U),DMA_REGISTER_RESET_VALUE);
        DMA_SFR_INIT_DEINIT_WRITE32(&(DMA_PRR1.U),DMA_REGISTER_RESET_VALUE);
          
        /* ********************************************************
        *                   MODE REGISTER 
        * ********************************************************/
        /* MODE register is reset to supervisor mode */
        /* MISRA2012_RULE_11_3_JUSTIFICATION: Mcal requires the
        * parameter as uint32 const*, but this is a register type  */
        DMA_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG( \
            (uint32*)&(DMA_MODE0),DMA_MODE_REG_RESET);
        /* MISRA2012_RULE_11_3_JUSTIFICATION: Mcal requires the
        * parameter as uint32 const*, but this is a register type  */
        DMA_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG( \
            (uint32*)&(DMA_MODE1),DMA_MODE_REG_RESET);
        /* MISRA2012_RULE_11_3_JUSTIFICATION: Mcal requires the
        * parameter as uint32 const*, but this is a register type  */
        DMA_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG( \
            (uint32*)&(DMA_MODE2),DMA_MODE_REG_RESET);
        /* MISRA2012_RULE_11_3_JUSTIFICATION: Mcal requires the
        * parameter as uint32 const*, but this is a register type  */
        DMA_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG( \
            (uint32*)&(DMA_MODE3),DMA_MODE_REG_RESET);

        /* ********************************************************
        *                   CLOCK CONTROL REGISTER 
        * ********************************************************/                       
        /* Disable DMA module clock */
        lClcReg.U = DMA_CLC.U;
        lClcReg.B.DISR = DMA_BIT_SET;
        /* MISRA2012_RULE_11_3_JUSTIFICATION: Mcal requires the
        * parameter as uint32 const*, but this is a register type  */
        DMA_LIB_INIT_DEINIT_WRITEPERIPENDINITPROTREG((uint32*)&(DMA_CLC),lClcReg.U);

        /*Reset Config pointer to NULL */
        Dma_kConfigPtr = NULL_PTR;               
      }
      /* [cover parentID={2DE86A21-7186-4568-A6C6-7F846F01EC5A}]
         Is the core un-initialized successfully?
         [/cover] */
      if(ErrorVal == E_OK) 
      {        
        /* Mark the core as 'uninitialized' */
        *(Dma_CoreState[lCoreId]) = DMA_CPUCORE_UNINIT; 
      }        
    }
  }   
}
#endif
/*******************************************************************************
** Traceability: [cover parentID={74D7B875-DB94-45d5-B1E4-5C3EF2A2BB0A}]      **
**                                                                            **
** Syntax :  Std_ReturnType Dma_IsInitDone(void)                              **
**                                                                            **
** Description : Service to check if the DMA driver is initialized or not     **
**               for the core on which it is run at the moment.               **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x02                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant                                                     **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :   DMA driver state.                                      **
**                     E_OK  - DMA is initialized                             **
**                     E_NOT_OK - DMA is not initialized                      **
**                                                                            **
*******************************************************************************/
Std_ReturnType Dma_IsInitDone
(
  void
)
{
  Std_ReturnType lretVal;
  uint32 lCoreId = 0;

  lCoreId = Mcal_GetCpuIndex();

  if(*(Dma_CoreState[lCoreId]) == DMA_CPUCORE_UNINIT)
  {
    /* [cover parentID={13348C17-09DA-4c3d-B592-5AE665AAA9DB}]
    Get the Initialization status of DMA driver
    [/cover] */
    /* [cover parentID={D8CE7D64-37B6-432f-AD08-B5F8D4CA784B}]
    Is the DMA driver un-initialized?
    [/cover] */

    /* Driver is not initialized */
    lretVal = E_NOT_OK;
  }
  else
  {
    /* [cover parentID={8AC340B8-1D4A-4cdd-8E43-28D2660A93DA}]
    Return "Ok" as the status
    [/cover] */

    /* Driver is initialized */
    lretVal = E_OK;
  }

  return lretVal;
}

/*******************************************************************************
** Traceability: [cover parentID={3FE0DC84-E27F-46f0-B883-C2FA28C1D5F2}]      **
**                                                                            **
** Syntax : void Dma_ChInit(uint8 Channel)                                    **
**                                                                            **
** Description : Service for channel initialization with parameters defined   **
**               in DMAChannelTransactionSet container.                       **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x03                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Conditionally Reentrant - This API is re-entrant for          **
**              different DMA channels                                        **
**                                                                            **
** Parameters (in) :  Channel - DMA channel ID(0-127)                         **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
void Dma_ChInit
(
  const uint8 Channel
)
{
  const Dma_ChConfigType *ChConfig;   /* Channel config pointer */
  uint8 lChIndex = 0U;
  uint32 lCoreId = 0;         /* ID of core used for execution */
  uint8 chState;

  /* [cover parentID={6005149E-B896-4a0c-AF46-5ED6F5770772}]
  Get the core id on which this function is invoked
  [/cover] */

  /* Get the core ID of the core, where we are executing at this moment */
  lCoreId = Mcal_GetCpuIndex();

  /* [cover parentID={ACA48C08-E6A0-4253-AC69-410F1310329C}]
  DET or Safety Enabled
  [/cover] */
  /* [cover parentID={CA7E2C5B-AF23-4cd0-96B6-98138A34BF3E}]
  DET checks
  [/cover] */
  #if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
  if(*(Dma_CoreState[lCoreId]) == DMA_CPUCORE_UNINIT)
  { /* Before we proceed, is the DMA driver uninitialized for this
     * particular core? Here, we are not really bothered about the
     * other cores, actually! */

    /* [cover parentID={035DEB89-63F1-4bdb-B16C-F5A4543B42B5}]
    Report DET or safety error on init state
    [/cover] */
    /* [cover parentID={5184DF51-9913-425e-87B8-0376CC218F22}]
    Is the DMA driver initialized?
    [/cover] */

    /* That's an error! Report DET on DriverState error*/
    Dma_lReportError( DMA_SID_CHINIT, DMA_E_DRIVER_NOT_INITIALIZED );
  }
  else if(Channel >= (uint8)DMA_MAX_NUM_OF_CHANNELS)
  { /* Is the requested channel outside the valid range of channels
     * which the hardware can support? */

    /* [cover parentID={9BA72BB2-825C-42b0-9D9B-A02FA08CB224}]
    Report DET on invalid channel ID
    [/cover] */
    /* [cover parentID={8AC2106B-ED6E-45a7-888A-3EC76C90BAB8}]
    Is the number of channel greater than max no of
    allowed DMA channels?
    [/cover] */

    /* That's not good. Report DET on Channel ID error. */
    Dma_lReportError( DMA_SID_CHINIT, DMA_E_CHANNEL_INVALID_ID );
  }
  else if(Dma_kConfigPtr->Dma_ChannelMaps[Channel].
          Dma_ChannelConfIndexMap == DMA_CHANNEL_MAP_RESET_VALUE)
  {
    /* We have searched the entire root configuration, This
     * channel configuration doesn't exist. This is an error
     * and has to be reported via a DET */
    Dma_lReportError( DMA_SID_CHINIT, DMA_E_CHANNEL_INVALID_ID );
  }
  #if( (DMA_MULTICORE_ERROR_DETECT == STD_ON) ||\
       (DMA_SAFETY_ENABLE          == STD_ON) )
  else if(Dma_kConfigPtr->
          Dma_ChannelMaps[Channel].Dma_ChannelCoreMap != lCoreId)
  { /* Is the requested channel not assigned to this core? */

    /* [cover parentID={EEC4FA9E-1A86-437f-A72F-2994D59DE8BD}]
    Report error on core id mismatch
    [/cover] */
    /* [cover parentID={270F728A-4AFC-48f8-84B8-3AA85401F83E}]
    Is the channel assigned
    to this core?
    [/cover] */

    /* There is an issue with the way the channels are handled from the
     * caller. Report a DET */
    Dma_lReportMulticoreError(DMA_SID_CHINIT, DMA_E_CORE_CHANNEL_MISMATCH);
  }
  #endif
  else if(DMA_GET_CH_INITSTATE(Channel, lCoreId) == DMA_DRIVER_CHINIT)
  {
    /* Null pointer check not needed since channel core map check is
     * being performed */
    /* Is the requested channel already initialized and someone is
     * requesting again?*/

    /* [cover parentID={371F06CD-FBAF-4221-BC53-52D488AF27BE}]
    Report DET or safety error on already init channel
    [/cover] */
    /* [cover parentID={6000B781-F8E5-4df0-9982-C11675C629F1}]
    Is the channel already initialized?
    [/cover] */
    /* [cover parentID={DBECF04A-0F89-4a61-8485-5C21CBE0A9BB}]
    Is the channel already initialized?
    [/cover] */
    /* [cover parentID={93AB38B7-367F-486b-99BB-FE56AE3F3F2B}]
    Report DET or safety error on  Channel already initialized
    [/cover] */

    /* That's not right. Report DET on Channel ID error */
    Dma_lReportError( DMA_SID_CHINIT, DMA_E_CH_ALREADY_INITIALIZED );
  }
  else
  #endif
  {
    /* [cover parentID={A31DF5D8-3119-4b0a-AAEF-FC515985D427}]
    Is DET present?
    [/cover] */
    /* [cover parentID={5D99D6E6-63B4-44f4-95EB-195A2AB1F84F}]
    Critical Section - ChannelConfigUpdate
    [/cover] */
    /* [cover parentID={EBD2E2EC-BC1B-469a-A647-66499CBDC68A}]
    Critical Section - ChannelConfigUpdate
    [/cover] */
    /* [cover parentID={78EF9F05-3471-4cdc-8C20-9879C10CBD67}]
    Enter the critical section, by calling 'SchM_Enter_Dma_ChannelConfigUpdate'
    [/cover] */

    /* Lock entry for core */
    SchM_Enter_Dma_ChannelConfigUpdate();

    /* Get channel configuration from the root config by searching
     * the channel ID in the set which is allocated per core. */
    lChIndex = Dma_kConfigPtr->
               Dma_ChannelMaps[Channel].Dma_ChannelConfIndexMap;

    /* We have found the channel in the list. Now,
     * get the channel configuration and update the registers */
    ChConfig = &(Dma_kConfigPtr->DmaCoreConfigPtr[lCoreId]->
            DmaChConfigPtr[lChIndex]);

    /* [cover parentID={7C8153FC-6D38-4ce3-8FBF-CCF3F65D8561}]
    Update the selected DMA channel register
    [/cover] */

    Dma_lUpdateChannelReg(Channel, ChConfig);

    /* Are there any ME0 errors pertaining to this channel? */
    if( DMA_ME0_ERRSR.B.LEC == Channel )
    {
      /* [cover parentID={BADDB407-C2C0-4d00-9EA2-973240316E6B}]
      Clear the ME0 error
      [/cover] */
      /* [cover parentID={942FE004-B802-480b-93E7-F272763B0D4B}]
      Is there an ME0 error for this channel?
      [/cover] */

      /* Clear the ME error */
      DMA_SFR_RUNTIME_WRITE32(&(DMA_ME0_CLRE.U),DMA_CLEAR_ERROR_MASK);
    }

    /* Are there any ME1 errors pertaining to this channel? */
    if( DMA_ME1_ERRSR.B.LEC == Channel )
    {
      /* [cover parentID={16BEE173-929E-4e1c-9ECA-7A6A1EAA85EA}]
      Clear the ME1 error
      [/cover] */
      /* [cover parentID={B5A8FF59-F17E-486b-AA52-DA62B28C834A}]
      Is there an ME1 error for this channel?
      [/cover] */

      /* Clear the ME error */
      DMA_SFR_RUNTIME_WRITE32(&(DMA_ME1_CLRE.U),DMA_CLEAR_ERROR_MASK);
    }

    /* [cover parentID={4C17BC67-86B6-42e1-8194-BD26BDA228D8}]
    Mark the channel as "initialized"
    [/cover] */

    /* Update DMA channel state */
    chState = DMA_DRIVER_CHINIT << (uint8)(Dma_kConfigPtr->
      Dma_ChannelMaps[Channel].Dma_ChannelConfIndexMap % (uint8)8);

    /* No null pointer check needed, since the det checks already
     * covers the possibility */
    (Dma_ChannelStatesPerCore[lCoreId])[Dma_kConfigPtr->
      Dma_ChannelMaps[Channel].
      Dma_ChannelConfIndexMap / (uint8)8] |= chState;


    /* Lock exit for core */
    SchM_Exit_Dma_ChannelConfigUpdate();
    /* [cover parentID={D959A786-D7C9-4399-A23B-81CDFA74645B}]
    Leave the critical section, by calling
    'SchM_Exit_Dma_ChannelConfigUpdate'
    [/cover] */
    /* [cover parentID={EBD2E2EC-BC1B-469a-A647-66499CBDC68A}]
    Critical Section - ChannelConfigUpdate
    [/cover] */
  }
}

/*******************************************************************************
** Traceability: [cover parentID={E1E74706-993A-41cd-8601-AD22979B9AFF}]      **
**                                                                            **
** Syntax : void Dma_ChUpdate (uint8 Channel, Dma_ConfigUpdateType            **
**                                  *Config, uint32 * NodeAddress)            **
**                                                                            **
** Description : Service for channel initialization with parameters provided  **
**               by the user                                                  **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x04                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Conditionally Reentrant - This API is re-entrant for          **
**              different DMA channels                                        **
**                                                                            **
** Parameters (in) : Channel - DMA channel ID(0-127)                          **
**                   Dma_ConfigUpdateType - Channel update structure with     **
**                   channel configuration updated                            **
**                   NodeAddress - Start of a memory block which must be      **
**                   formatted with information in "Config" object            **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
void Dma_ChUpdate
(
  const uint8 Channel,
  const Dma_ConfigUpdateType* const Config,
  const uint32* const NodeAddress
)
{
  Ifx_DMA_CH* lConfigPtr = NULL_PTR;
  Std_ReturnType lStatus = E_OK;
  uint32 RemapAddress;
  uint32 lLoopCount = 0U;
  uint8 chStatus;
  uint32 lCoreId = 0;         /* ID of core used for execution */

  /* Get the core ID of the core, where we are executing at this moment */
  lCoreId = Mcal_GetCpuIndex();

  #if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )

  /* [cover parentID={3D914FAA-A2FD-4f62-9749-088108DDD1BC}]
  DET checks
  [/cover] */
  /* [cover parentID={2BF665BF-0B5C-4069-B8E3-0C4F1EBBCB0D}]
  DET is on
  [/cover] */

  if(Config == NULL_PTR)
  {
    /* [cover parentID={C11970C8-3D44-4dde-B231-74AEB94725E0}]
    Report DET or safety error for NULL pointer
    [/cover] */
    /* [cover parentID={1AD79E74-2A09-4c4c-9FCA-334F4627DB95}]
    Is the config pointer NULL?
    [/cover] */

    /* A null pointer?! We need a DET, right now! */
    Dma_lReportError( DMA_SID_CHUPDATE, DMA_E_NULL_POINTER );
  }
  else if(*(Dma_CoreState[lCoreId]) == DMA_CPUCORE_UNINIT)
  {
    /* [cover parentID={748FF1C6-90E4-4bc5-A015-5E54D607F3B5}]
    Is DMA uninitialized for current core?
    [/cover] */

    /* Well, the driver itself is not initialized for this core.
     * So, this call should not be coming here in the first place. Report
     * a DET! */
    /* [cover parentID={FDAA241C-9981-4513-963E-630F8668EB67}]
    Report DET or safety error for 'Not Initialized' state
    [/cover] */
    Dma_lReportError( DMA_SID_CHUPDATE, DMA_E_DRIVER_NOT_INITIALIZED );
  }
  else if(Channel >= (uint8)DMA_MAX_NUM_OF_CHANNELS)
  {
    /* [cover parentID={C26656B8-2028-4e3b-B70D-DD38DFBDB9BB}]
    Is the channel requested greater
    than the max DMA channels?
    [/cover] */

    /* Apparently, the channel requested is not within the valid range
     * of channels that DMA is built for. This situation demands
     * a DET error.  */
    /* [cover parentID={3385CA8F-F4E7-424f-AFA9-BFAB17458986}]
    Report DET or safety error for 'Invalid Channel ID'
    [/cover] */
    Dma_lReportError( DMA_SID_CHUPDATE, DMA_E_CHANNEL_INVALID_ID );
  }
  else if(Dma_kConfigPtr->Dma_ChannelMaps[Channel].
          Dma_ChannelConfIndexMap == DMA_CHANNEL_MAP_RESET_VALUE)
  {
    /* [cover parentID={A5287685-20DB-4059-8499-AB91E9211F4C}]
    Does the channel config exist?
    [/cover] */
    /* [cover parentID={30C03A01-2463-40ad-924E-27730EFE3AF9}]
    Report DET or safety error on invalid channel ID
    [/cover] */

    /* We have searched the entire root configuration, This
     * channel configuration doesn't exist. This is an error
     * and has to be reported via a DET */
    Dma_lReportError( DMA_SID_CHUPDATE, DMA_E_CHANNEL_INVALID_ID );
  }
  #if( (DMA_MULTICORE_ERROR_DETECT == STD_ON) || \
       (DMA_SAFETY_ENABLE          == STD_ON) )
  /* [cover parentID={71578E71-6477-47a5-854F-F543928B4E61}]
  DET or safety enabled
  [/cover] */
  else if(Dma_kConfigPtr->
          Dma_ChannelMaps[Channel].Dma_ChannelCoreMap != lCoreId)
  { /* Is the requested channel not assigned to this core? */

    /* [cover parentID={AB73656B-EBA9-4e47-A3C7-20E3E151BAF3}]
    Report DET or safety error for 'Core-Channel Mismatch'
    [/cover] */
    /* [cover parentID={1599FAEA-8623-4c51-8605-72914CDC204E}]
    Is the requested channel not assigned to this core?
    [/cover] */

    /* There is an issue with the way the channels are requested from
     * the caller. Report a DET! */
    Dma_lReportMulticoreError( DMA_SID_CHUPDATE,
                               DMA_E_CORE_CHANNEL_MISMATCH );
  }
  #endif
  else if(MODULE_DMA.TSR[Channel].B.CH != 0x00U)
  {
    /* [cover parentID={63155CF9-E279-4004-A184-4104BC66FCE9}]
    Report DET or safety error for 'Transfer in progress'
    [/cover] */
    /* [cover parentID={B4EBAD10-6C3D-43e5-8226-0E6535EAA7E0}]
    Is any transfer already in progress?
    [/cover] */

    /*Report DET data transfer is already in progress*/
    Dma_lReportError( DMA_SID_CHUPDATE, DMA_E_DATA_TRANSFER_IN_PROGRESS );
  }
  else
  #endif
  {
    /**! Everything looks okay, we'll proceed then! */

    /* Get TCS root note. Remember, TCS root node is always in the DMA
     * TCS registers */
    lConfigPtr = &(MODULE_DMA.CH[Channel]);

    /*
     * In case of linked list, NodeAddress must contain a valid address
     * Driver will create a valid TCS at this address as a linked list
     * node
     */

    /**! The NodeAddress pointer needs to be understood here. Now,
     * this pointer would be holding the value NULL when the first
     * data set in the linked list is updated. In this case, the
     * provided data is used to be update the TCS in the DMARAM.
     * After this, the caller has to be provide the node address
     * which is the address of the linked list location in the RAM.
     *
     * So, the invocation would be in the following fashion:
     * NodeAddress:
     * ** NULL          => the first data set for the linked list
     * ** ValidAddress  => Location where the config is to be stored
     *
     *  When the node address is a valid address, this means that the
     *  node has to be stored at the last node which is already
     *  available.
     *  */

    /* Lock entry for core */
    SchM_Enter_Dma_ChannelConfigUpdate();
    /* [cover parentID={42E35C0D-1A78-4be6-99EE-4B8333D1CB8A}]
    Enter the crtical section
    [/cover] */

    if(NodeAddress != NULL_PTR)
    {
      /* [cover parentID={4FC9A66F-BC9C-4c0c-8E23-D46D1AE1E758}]
      Is the node status okay?
      [/cover] */

      /* Now, we are not having a null pointer with us, which means
       * we have a TCS allocated somewhere in the memory. We need to
       * find the last TCS node, in the TCS linked list as of now
       * and connect the new TCS to it. */

      /* [cover parentID={DECB7739-57AC-4b23-AAA2-B655F5B7D45C}]
      Is the node status okay?
      [/cover] */
      /* [cover parentID={F281A24D-DB85-44e0-A8D6-EAE73E14BC42}]
      Is the node status okay?
      [/cover] */

      /* Go, find the last node of this list! */
      while((lConfigPtr->SHADR.U != 0x00U) &&
            (lLoopCount < (uint32)DMA_MAX_LINKED_LIST_NODE))
      {
        /* [cover parentID={F2CE4AB6-78A8-481b-B2DC-E35A901AD848}]
        Is the node not the last node AND the shadow address
        is not zero?
        [/cover] */

        /* MISRA2012_RULE_11_6_JUSTIFICATION: The shadow register value
         * needs to be casted to the channel address since it is a
         * linked list. */
        /* MISRA2012_RULE_11_4_JUSTIFICATION: The shadow address value
         * need to be converted to the channel address for the linked list */
        lConfigPtr = (Ifx_DMA_CH *)(lConfigPtr->SHADR.U);
        lLoopCount++;
      }

      if(lLoopCount == (uint32)DMA_MAX_LINKED_LIST_NODE)
      {
        /* [cover parentID={14FBAFBC-41D9-4b58-8EFC-2D9BECB10946}]
        Mark the node status as not okay
        [/cover] */
        /* [cover parentID={42ACA632-44C5-493e-8D87-82A1142EFE13}]
        Has the count reached
        the last node?
        [/cover] */

        /* DMA linked list limit has been exceeded */
        lStatus = E_NOT_OK;
      }
      else
      {
        /* [cover parentID={BA57F2FC-4848-401c-963F-C0DAEE379A64}]
        Mark the node status as okay
        [/cover] */

        lStatus = E_OK;
        /* Update last node's shadow address with new node address
         * provided by the user. */
        /* MISRA2012_RULE_11_4_JUSTIFICATION: The API expects address in
         * uint32 format. So the conversion is needed here. */
        /* MISRA2012_RULE_11_6_JUSTIFICATION: Mcal API expects
         * address as uint32, however in DMA address is pointer. */
        RemapAddress = (uint32)Dma_lGetGlobalAddress(\
                                           Mcal_GetCpuPhysicalId(),\
                                           (uint32)NodeAddress);
        /**! Now, the variable 'lConfigPtr' holds the address of
         * the last node of the existing linked list. We are going
         * to add the new linked list set to the end of this list.
         * */
        /* [cover parentID={25486E22-7B76-427e-8871-610368818D25}]
        Assign the reamapped address to the shadow address of last node
        [/cover] */

        DMA_SFR_RUNTIME_WRITE32(&(lConfigPtr->SHADR.U), RemapAddress);

        /* Now point to the leaf node which will be formatted by the
           driver */
        /* MISRA2012_RULE_1_3_JUSTIFICATION: lConfigPtr refers to
         * shadow register which ultimately hold the next TCS
         * address i.e. NodeAddress. Caller should make sure that
         * NodeAddress is a valid address */
        /* MISRA2012_RULE_11_3_JUSTIFICATION: lConfigPtr refers to
         * shadow register which ultimately hold the next TCS
         * address i.e. NodeAddress. Caller should make sure that
         * NodeAddress is a valid address */
        /* MISRA2012_RULE_11_8_JUSTIFICATION: lConfigPtr refers to
         * shadow register which ultimately hold the next TCS
         * address i.e. NodeAddress. Caller should make sure that
         * NodeAddress is a valid address */
        lConfigPtr = (Ifx_DMA_CH *)NodeAddress;
      }
    }

    /* Now, after the address of the TCS has been added to the linked
     * list, we can update the parameters of the TCS if needed. This
     * gives some flexibility to the user. The user can prepare the
     * TCS from user's side or can entrust the DMA to take the data
     * from the user and put them in the proper places. */

    if(lStatus != (uint8)E_NOT_OK)
    {
      lStatus = Dma_lUpdateSelectedReg(lConfigPtr, Config);

      if(lStatus != (uint8)E_NOT_OK)
      {
        /* [cover parentID={7D91256C-FB8C-4104-B3AC-B1BD94D442BB}]
        Mark the channel status as 'Initialized'
        [/cover] */
        chStatus = DMA_DRIVER_CHINIT << (uint8)(Dma_kConfigPtr->
        Dma_ChannelMaps[Channel].Dma_ChannelConfIndexMap%(uint8)8);

        /* Mark the channel as 'Initialized' */
        /* No null pointer check needed, since the det checks already
         * covers the possibility */
        (Dma_ChannelStatesPerCore[lCoreId])[Dma_kConfigPtr->
        Dma_ChannelMaps[Channel].Dma_ChannelConfIndexMap/(uint8)8]
                |= chStatus;
      }
    }

    /* Unlock entry for core */
    SchM_Exit_Dma_ChannelConfigUpdate();
    /* [cover parentID={079E6B4C-FE3A-4497-94D2-0662BCF3A006}]
    Enter the critical section
    [/cover] */
  }
}


#if (DMA_CHDEINIT_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={424A9149-0D0F-4c5d-82A6-4D690780FB35}]      **
**                                                                            **
** Syntax : void Dma_ChDeInit(uint8 Channel)                                  **
**                                                                            **
** Description : Driver channel deinitialization                              **
**               This function will deinitialize the DMA channel registers    **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x05                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Conditionally Reentrant - This API is re-entrant for          **
**              different DMA channels                                        **
**                                                                            **
** Parameters (in) :  Channel - DMA channel ID(0-127)                         **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
void Dma_ChDeInit
(
  const uint8 Channel
)
{
  uint32 lCoreId = 0;         /* ID of core used for execution */
  uint8  lChState;

  #if ((DMA_LINKED_LIST_ENABLE     == STD_ON) || \
       (DMA_DOUBLE_BUFFER_ENABLE   == STD_ON))
  /* MISRA2012_RULE_19_2_JUSTIFICATION: Union based type definition for SFR
     access. Variable of SFR type defined for writing into register.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_DMA_CH_ADICR lAdicr;
  #endif

  #if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
  /* [cover parentID={9E600AD6-2EDC-4eb9-A4AA-1357EFA57929}]
  DET or Safety Enabled
  [/cover] */

  uint32 lDetStatus;


  /* [cover parentID={6B68D40E-4FE4-4d62-BA24-652E38755883}]
  Check for any DET errors
  [/cover] */
  /* Check for any possible DETs */
  lDetStatus = Dma_lDetCheck(DMA_SID_CHDEINIT, Channel);

  /* [cover parentID={F47E4085-DC8A-4032-8CB8-746475F562B9}]
  Any errors present?
  [/cover] */
  if(lDetStatus == (uint32) FALSE)
  #endif
  {
    /* [cover parentID={BD400C4E-99DD-4db9-B334-8D91C66616A8}]
    Enter the critical section, by calling
     'SchM_Enter_Dma_ChannelConfigUpdate'
    [/cover] */

    /* Lock entry for core */
    SchM_Enter_Dma_ChannelConfigUpdate();

    /* Check if the channel is active */
    if( MODULE_DMA.TSR[Channel].B.CH == 0x00U )
    {
      /* [cover parentID={2131F988-B8DA-4f3a-AC48-F865E3E9B982}]
      Is any transfer already in progress?
      [/cover] */

      /* [cover parentID={CDF3C800-683E-405b-83AC-335F787C9B78}]
      Reset the TCS registers
      [/cover] */

      /* ********** Reset all the TCS registers ************ */

      #if ((DMA_LINKED_LIST_ENABLE     == STD_ON) || \
           (DMA_DOUBLE_BUFFER_ENABLE   == STD_ON))
      lAdicr.U = MODULE_DMA.CH[Channel].ADICR.U;

      if((lAdicr.B.SHCT >  DMA_SHADOW_ADDR_RES2_MASK) &&
         (lAdicr.B.SHCT != DMA_SHADOW_ADDR_RES3_MASK))
      {
        /* [cover parentID={7CFF36E8-6575-465b-B24D-7948F28A78D2}]
        Does the channel need a shadow register reset?
        [/cover] */

        /* [cover parentID={A53A61C3-8E03-41c0-AFF9-B00F66573949}]
        Reset the shadow register
        [/cover] */

        DMA_SFR_RUNTIME_WRITE32(&(MODULE_DMA.CH[Channel].SHADR.U),
                DMA_REGISTER_RESET_VALUE);
      }
      #endif

      DMA_SFR_RUNTIME_WRITE32(&(MODULE_DMA.CH[Channel].RDCRCR.U),
              DMA_REGISTER_RESET_VALUE);

      DMA_SFR_RUNTIME_WRITE32(&(MODULE_DMA.CH[Channel].SDCRCR.U),
              DMA_REGISTER_RESET_VALUE);

      DMA_SFR_RUNTIME_WRITE32(&(MODULE_DMA.CH[Channel].SADR.U),
              DMA_REGISTER_RESET_VALUE);

      DMA_SFR_RUNTIME_WRITE32(&(MODULE_DMA.CH[Channel].DADR.U),
              DMA_REGISTER_RESET_VALUE);

      DMA_SFR_RUNTIME_WRITE32(&(MODULE_DMA.CH[Channel].ADICR.U),
              DMA_REGISTER_RESET_VALUE);

      DMA_SFR_RUNTIME_WRITE32(&(MODULE_DMA.CH[Channel].CHCFGR.U),
              DMA_REGISTER_RESET_VALUE);

      DMA_SFR_RUNTIME_WRITE32(&(MODULE_DMA.CH[Channel].CHCSR.U),
              DMA_REGISTER_RESET_VALUE);

      DMA_SFR_RUNTIME_WRITE32(&(MODULE_DMA.TSR[Channel].U),
              DMA_REGISTER_RESET_VALUE);


      /* [cover parentID={C413E5D9-A5BA-42af-A7DF-9E695C94D582}]
      Reset the resource partition allocation, with safety
      end init protection
      [/cover] */

      /* ***** Reset the resource partition allocation ****** */
      /* MISRA2012_RULE_11_8_JUSTIFICATION: Mcal requires the
       * parameter as uint32 const*, but this is a register name
       * which is having a volatile qualifier  */
      /* MISRA2012_RULE_11_3_JUSTIFICATION: Mcal requires the
       * parameter as uint32 const*, but this is a register type  */
      DMA_LIB_RUNTIME_WRITESAFETYENDINITPROTREG(\
              (uint32*)&(MODULE_DMA.HRR[Channel].U),\
              DMA_REGISTER_RESET_VALUE);
      lCoreId=Dma_kConfigPtr->Dma_ChannelMaps[Channel].Dma_ChannelCoreMap;

      /* [cover parentID={0661FE58-70F2-4a99-BA20-33A2AD7792F3}]
      Update Dma_channel state as "Un-initialized"
      [/cover] */

      /* Keep the state of the channel as 'Uninitialized' */
      lChState = (uint8)0xFF ^ ((uint8)0x1 << (uint8)(Dma_kConfigPtr->
          Dma_ChannelMaps[Channel].Dma_ChannelConfIndexMap % (uint8)8));

      /* No null pointer check needed, since the det checks already
       * covers the possibility */
      (Dma_ChannelStatesPerCore[lCoreId])[Dma_kConfigPtr->
          Dma_ChannelMaps[Channel].Dma_ChannelConfIndexMap/(uint8)8]
                               &= lChState;

    }
    #if( (DMA_DEV_ERROR_DETECT == STD_ON) || \
         (DMA_SAFETY_ENABLE    == STD_ON) )
    else
    {
      /* [cover parentID={E91DF10B-3777-4f17-B879-72200FCF132D}]
      Report DET or safety error for 'Transfer in progress'
      [/cover] */

      Dma_lReportError( DMA_SID_CHDEINIT,
                        DMA_E_DATA_TRANSFER_IN_PROGRESS );
    }
    #endif

    /* [cover parentID={BE4C226B-7832-44ca-A57F-286AAF7965B0}]
    Leave the critical section,
    by calling 'SchM_Exit_Dma_ChannelConfigUpdate'
    [/cover] */
    /* Lock exit for core */
    SchM_Exit_Dma_ChannelConfigUpdate();

    /* [cover parentID={BE4C226B-7832-44ca-A57F-286AAF7965B0}]
    Leave the critical section, by calling
    'SchM_Exit_Dma_ChannelConfigUpdate'
    [/cover] */

  }
}
#endif

#if (DMA_SUSPEND_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={F78F0345-EF3B-4374-A2FE-59A203F9F24F}]      **
**                                                                            **
** Syntax : void Dma_ChTransferFreeze (uint8 Channel)                         **
**                                                                            **
** Description : Service to halt a channel. This function freezes the         **
**               ongoing channel transaction.                                 **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x06                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Conditionally Reentrant - This API is re-entrant for          **
**              different DMA channels                                        **
**                                                                            **
** Parameters (in) :  Channel - DMA channel ID(0-127)                         **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
void Dma_ChTransferFreeze
(
  const uint8 Channel
)
{
  uint32 lLoopCount = 0;

  #if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
  uint32 lDetStatus;

  /* [cover parentID={B3871608-776C-4431-96F7-3E377778C160}]
  Check for any DET errors
  [/cover] */
  /* [cover parentID={A544F97D-DD1E-4a03-B3B0-AD7E2AEBE86D}]
  Det is on
  [/cover] */
  lDetStatus = Dma_lDetCheck(DMA_SID_CHTRANSFERFREEZE, Channel);

  /* [cover parentID={1E57E7B5-6A8E-4ede-AEAE-15E739AF68FB}]
     Any errors present?
     [/cover] */
  /* Are there any DETs present? */
  if(lDetStatus == (uint32)FALSE)
  #endif
  {
    /* [cover parentID={DF88D05E-0627-43aa-90A7-F6AB138B7324}]
    Critical section - ChannelConfigUpdate
    [/cover] */
    /* [cover parentID={BAF817F2-5F60-4cc8-B386-D586F2EA669C}]
    Enter the critical section, by calling
    'SchM_Enter_Dma_ChannelConfigUpdate'
    [/cover] */

    /* Lock entry for core */
    SchM_Enter_Dma_ChannelConfigUpdate();
    /* [cover parentID={DF88D05E-0627-43aa-90A7-F6AB138B7324}]
    Critical section - FreezeUnfreeze
    [/cover] */
    /* [cover parentID={BAF817F2-5F60-4cc8-B386-D586F2EA669C}]
    Enter the critical section, by calling
    'SchM_Enter_Dma_ChannelConfigUpdate'
    [/cover] */

    /* Halt the channel only if something is really pending */
    /* [cover parentID={13F4DAE1-6464-4ee2-8795-335747BF2798}]
     * Halt the channel only if something is really pending
     * [/cover] */
    if(MODULE_DMA.CH[Channel].CHCSR.B.TCOUNT != 0x00U)
    {
      /* Check if channel is already in halt state */
      /* [cover parentID= {1828E5A9-1EF0-4719-8571-2E4719F28CF8}]
         Send halt request to DMA channel
         [/cover] */
      if(MODULE_DMA.TSR[Channel].B.HLTACK == (uint32)DMA_BIT_CLEAR)
      {
        /* Send halt request to DMA channel */
        /* [cover parentID= {438F8148-AC20-4bcf-82B6-A6E3BFD3CAD5}]
           Send halt request to DMA channel
           [/cover] */                    
        DMA_SFR_RUNTIME_WRITE32(&(MODULE_DMA.TSR[Channel].U),((MODULE_DMA.TSR[Channel].U)|
        ((uint32)DMA_BIT_SET << IFX_DMA_TSR_HLTREQ_OFF)));

        /* Wait for halt acknowledgment */
        /*Loop timeout will be (65535 * 3.33)ns = 2.18 * 10^5 ns.
          Writing HLTACK bit, time taken by hardware is approximately less than 
          30 SRI clock ticks , i,e 99.99 ns, which is less than loop time, 
          considering while loop taking minimum 4 instructions in assembly */
        while((MODULE_DMA.TSR[Channel].B.HLTACK==(uint32)DMA_BIT_CLEAR)
                &&
              (lLoopCount < (uint32)DMA_TIMEOUT))
        {
          lLoopCount++;
        }

        #if( (DMA_DEV_ERROR_DETECT == STD_ON) || \
                (DMA_SAFETY_ENABLE == STD_ON) )
        /* [cover parentID={D1077098-2F45-4230-B59E-ED77981F810B}]
        DET or Safety Enabled
        [/cover] */

        /* In case of timeout report i.e. acknowledgment is still
         * pending then report timeout DET */
        /* [cover parentID={B96B73A5-23A4-41df-BA67-38272B9BDD31}]
        Report Det for 'Timeout'
        [/cover] */
        if(MODULE_DMA.TSR[Channel].B.HLTACK == DMA_BIT_CLEAR)
        {
          /* [cover parentID={F6FF6296-3136-4ddc-92A2-E679BD76C37F}]
          Report Det for 'Timeout'
          [/cover] */
          Dma_lReportError( DMA_SID_CHTRANSFERFREEZE, DMA_E_TIMEOUT );
        }
        #endif
      }
      else
      {
        /* Do nothing, channel already halted. */
      }
    }
    #if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
    else
    {
      /* [cover parentID={B077D2EB-B60A-46de-9594-3CD583CE85A9}]
      Det is on
      [/cover] */
      /* [cover parentID={D566C58C-DB41-424c-9343-1BB52410B8D9}]
      Return det for 'no transfers pending'
      [/cover] */

      /*Report DET on DriverState error*/
      Dma_lReportError( DMA_SID_CHTRANSFERFREEZE,
                        DMA_E_NO_TRANSFERS_PENDING );
    }
    #endif

    /* Lock exit for core */
    SchM_Exit_Dma_ChannelConfigUpdate();
    /* [cover parentID={F7FD4778-7C29-4ea4-92C6-E186E20A3FB2}]
    Leave the critical section, by calling
    'SchM_Exit_Dma_ChannelConfigUpdate'
    [/cover] */
  }
}
#endif



#if (DMA_SUSPEND_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={F82D46B9-2329-4d45-8B28-BD63AE9A448F}]      **
**                                                                            **
** Syntax : void Dma_ChTransferResume(uint8 Channel)                          **
**                                                                            **
** Description : Service to resume a halted channel.                          **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x07                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Conditionally Reentrant - This API is re-entrant for          **
**              different DMA channels                                        **
**                                                                            **
** Parameters (in) :  Channel - DMA channel ID(0-127)                         **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
void Dma_ChTransferResume
(
  const uint8 Channel
)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: Union based type definition for SFR
     access. Variable of SFR type defined for writing into register.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_DMA_TSR lTsrReg;

  #if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
  uint32 lDetStatus = FALSE;

  /* [cover parentID={4628C978-C338-4614-B14A-3C365A3EE0F9}]
  DET is ON
  [/cover] */
  /* [cover parentID={595560F2-C257-4525-A894-269E2F68E4C1}]
  Check for any DET errors
  [/cover] */

  lDetStatus = Dma_lDetCheck(DMA_SID_CHTRANSFERRESUME, Channel);

  /* [cover parentID={FC9E8B6E-BFFF-4606-9C32-BF8CEA87CC4B}]
  Any errors present?
  [/cover] */
  if(lDetStatus == (uint32)FALSE)
  #endif
  {
    /* Lock entry for core */
    SchM_Enter_Dma_ChannelConfigUpdate();
    /* [cover parentID={3B068A50-E921-4a8a-AE0F-EA0118609D9F}]
    Critical section - ChannelConfigUpdate
    [/cover] */
    /* [cover parentID={027B7F3D-09E0-457c-AEC6-A48885BB8BD7}]
    Enter the critical section, by calling
    'SchM_Enter_Dma_ChannelConfigUpdate'
    [/cover] */

    lTsrReg = MODULE_DMA.TSR[Channel];

    /* [cover parentID={2444BE66-9A81-4a7b-A4AA-1F1E758C0AC5}]
    Is the DMA channel
    already in frozen state?
    [/cover] */

    /* check Dma channel is in halt state or not, resume in case of halt*/
    if(lTsrReg.B.HLTACK == DMA_BIT_SET)
    {
      /* [cover parentID={137C9559-0CBD-4bcc-8B3F-D903633EFBAC}]
      Update the TSR register to resume the DMA channel
      [/cover] */

      /* Channel is in halt state, let's resume now*/            
      DMA_SFR_RUNTIME_WRITE32(&(MODULE_DMA.TSR[Channel].U),((MODULE_DMA.TSR[Channel].U) 
      | ((uint32)DMA_BIT_SET << IFX_DMA_TSR_HLTCLR_OFF)));
    }
    #if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
    else
    {
      /* [cover parentID={0BEACD95-4238-4b12-B619-338BAB532F16}]
      DET is ON
      [/cover] */
      /* [cover parentID={8BA1201C-6937-4f20-AB6F-FCD4C3EA6451}]
      Report DET for not in freeze state
      [/cover] */
      /* [cover parentID={29C85FAF-2773-43d8-8894-D3345A487CB0}]
      Report DET or safety error for channel in freeze state
      [/cover] */

      /* Channel is already running, nothing to be resume */
      /*Report DET on DriverState error*/
      Dma_lReportError( DMA_SID_CHTRANSFERRESUME,
                        DMA_E_NOT_IN_FREEZE_STATE );
    }
    #endif

    /* Lock exit for core */
    SchM_Exit_Dma_ChannelConfigUpdate();
    /* [cover parentID={A70934C1-E293-4def-A124-7F37D6DD7DA5}]
    Leave the critical section, by calling
    'SchM_Exit_Dma_ChannelConfigUpdate'
    [/cover] */

  }
}
#endif



#if (DMA_TRIGGER_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={8CC20C6F-9E1B-40f4-8B78-9B1F0F1D8E3B}]      **
**                                                                            **
** Syntax : void Dma_ChEnableHardwareTrigger(uint8 Channel)                   **
**                                                                            **
** Description : Service to enable hardware trigger for the channel           **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x08                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Conditionally Reentrant - This API is re-entrant for          **
**              different DMA channels                                        **
**                                                                            **
** Parameters (in) :  Channel - DMA channel ID(0-127)                         **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
void Dma_ChEnableHardwareTrigger
(
  const uint8 Channel
)
{

  /* MISRA2012_RULE_19_2_JUSTIFICATION: Union based type definition for SFR
   * access. Variable of SFR type defined for writing into register.
   * No side effects foreseen by violating this MISRA rule.*/
  Ifx_DMA_TSR lTsrReg;

  #if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
  /* [cover parentID={FBCFAC8E-7A1B-4c05-B087-0C2B48F97568}]
  DET or Safety Enabled
  [/cover] */
  /* [cover parentID={C7606662-CBA8-4935-81FB-154529603F9C}]
  Check for any DET or safety error
  [/cover] */

  uint32 lDetStatus;

  lDetStatus = Dma_lDetCheck(DMA_SID_CHENABLEHARDWARETRIGGER, Channel);

  /* [cover parentID={1EB53140-B033-4dbc-9219-E1E5D66EA55D}]
  Any errors present?
  [/cover] */
  /* [cover parentID={6C457ACD-5053-40e5-AC23-1E07B5F524FD}]
  Any errors present?
  [/cover] */


  if(lDetStatus == (uint32)FALSE)
  #endif
  {
    /* Lock entry for core */
    SchM_Enter_Dma_ChannelConfigUpdate();
    /* [cover parentID={8134E5CF-EB26-4886-8BDF-2C2D05023C57}]
    Critical section - ChannelConfigUpdate
    [/cover] */
    /* [cover parentID={DB9670A7-A71F-4b9c-9078-DFE7B6CF4BB7}]
    Enter the critical section, by calling
    'SchM_Enter_Dma_ChannelConfigUpdate'
    [/cover] */

    lTsrReg.U = MODULE_DMA.TSR[Channel].U;

    /* Check if the channel is active or frozen */
    /* [cover parentID={CAAA7BA0-8BA4-4cc8-B838-F3AF9018CDB0}]
       Is the channel active?
       [/cover] */
    /* [cover parentID={75770FED-E98D-4985-9EE1-D25D1946D465}]
       Is the channel in freeze state?
       [/cover] */
    if( (lTsrReg.B.CH     == 0x00U) &&
        (lTsrReg.B.HLTACK == 0x00U)     )
    {
      /* The channel is neither frozen nor active */

      /* [cover parentID={AB76BFAA-2197-4cf3-9512-917495C21D6B}]
      Enable hardware trigger by setting TSR.ECH bit
      [/cover] */

      /* Set the ECH bit atomically */   
      DMA_SFR_RUNTIME_WRITE32(&(MODULE_DMA.TSR[Channel].U),((MODULE_DMA.TSR[Channel].U)|
      ((uint32)DMA_BIT_SET << IFX_DMA_TSR_ECH_OFF)));
    }
    #if( (DMA_DEV_ERROR_DETECT == STD_ON) || \
         (DMA_SAFETY_ENABLE    == STD_ON) )
    /* [cover parentID={62F05BA4-809A-48e5-9D2A-42C7D3A6566E}]
      DET or Safety Enabled
      [/cover] */
    else
    {
      if( lTsrReg.B.CH != 0x00U )
      {
        /* [cover parentID={8A379250-D128-413c-B47B-DB2EAA0FB401}]
        Report DET or safety error for transfer in progress
        [/cover] */
        Dma_lReportError( DMA_SID_CHENABLEHARDWARETRIGGER,
                          DMA_E_DATA_TRANSFER_IN_PROGRESS );
      }

      if( lTsrReg.B.HLTACK != 0x00U )
      {
        /* [cover parentID={75770FED-E98D-4985-9EE1-D25D1946D465}]
        Is the channel in freeze state?
        [/cover] */
        /*Report DET data transfer is already in progress*/
        Dma_lReportError( DMA_SID_CHENABLEHARDWARETRIGGER,
                          DMA_E_FREEZE_STATE );
      }
    }
    #endif
    /* Lock exit for core */
    SchM_Exit_Dma_ChannelConfigUpdate();
    /* [cover parentID={64C2CE45-6898-4608-BEC9-429AC5831670}]
    Leave the critical section, by calling
    'SchM_Exit_Dma_ChannelConfigUpdate'
    [/cover] */
  }

}
#endif



#if (DMA_TRIGGER_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={D3A784B4-4322-4764-B438-16FE25C23869}]      **
**                                                                            **
** Syntax : void Dma_ChDisableHardwareTrigger (uint8 Channel)                 **
**                                                                            **
** Description : Service to disable hardware trigger for the channel          **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x09                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Conditionally Reentrant - This API is re-entrant for          **
**              different DMA channels                                        **
**                                                                            **
** Parameters (in) :  Channel - DMA channel ID(0-127)                         **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
void Dma_ChDisableHardwareTrigger
(
  const uint8 Channel
)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: Union based type definition for SFR
     access. Variable of SFR type defined for writing into register.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_DMA_TSR lTsrReg;

  #if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )


  /* [cover parentID={9BF25C00-C91F-4426-AA9C-3D93D5A7D202}]
  DET or Safety Enabled
  [/cover] */
  /* [cover parentID={D795163B-9B61-403b-BFFB-E5B8B2C8F1DE}]
  Check for any DET or safety error
  [/cover] */

  uint32 lDetStatus;

  lDetStatus = Dma_lDetCheck(DMA_SID_CHDISABLEHARDWARETRIGGER, Channel);

  if(lDetStatus == (uint32)FALSE)
  #endif
  {
    /* [cover parentID={F7CE3FAD-FE87-4874-A487-60FF58BE9921}]
    Any DET or safety error present?
    [/cover] */

    /* Lock entry for core */
    SchM_Enter_Dma_ChannelConfigUpdate();
    /* [cover parentID={AE0D8E13-01D6-4aac-A0FB-0E3BD68E1205}]
    Critical section - ChannelConfigUpdate
    [/cover] */
    /* [cover parentID={94EF76DA-72C5-4c59-8180-1E6224B3C2BA}]
    Enter the critical section, by calling
    'SchM_Enter_Dma_ChannelConfigUpdate'
    [/cover] */

    lTsrReg.U = MODULE_DMA.TSR[Channel].U;

    /* Check if the channel is active */
    /* [cover parentID={18A9AAA3-077B-469e-B733-16633DE1C258}]
       Is the channel active?
       [/cover] */
    /* [cover parentID={F8FDE417-037A-493d-8E05-BD699A63DA0D}]
       Is the channel in freeze state?
       [/cover] */
    if( (lTsrReg.B.CH     == 0x00U) &&
        (lTsrReg.B.HLTACK == 0x00U)     )
    {
      /* The channel is not active */

      /* [cover parentID={B9B90C74-290F-4173-8D86-858D7AFC8376}]
      Disable hardware trigger by setting TSR.DCH to 1
      [/cover] */

      /* Set the ECH bit atomically */
      DMA_SFR_RUNTIME_WRITE32(&(MODULE_DMA.TSR[Channel].U),((MODULE_DMA.TSR[Channel].U)|
      ((uint32)DMA_BIT_SET << IFX_DMA_TSR_DCH_OFF)));
    }
    #if( (DMA_DEV_ERROR_DETECT == STD_ON) || \
         (DMA_SAFETY_ENABLE    == STD_ON) )
    /* [cover parentID={79485A65-914C-4a0b-865E-0367CE333054}]
       DET or Safety Enabled
       [/cover] */
    else
    {
      if( lTsrReg.B.CH != 0x00U )
      {
        /* [cover parentID={8A379250-D128-413c-B47B-DB2EAA0FB401}]
        Report DET or safety error for transfer in progress
        [/cover] */

        Dma_lReportError( DMA_SID_CHDISABLEHARDWARETRIGGER,
                          DMA_E_DATA_TRANSFER_IN_PROGRESS );
      }
      if( lTsrReg.B.HLTACK != 0x00U )
      {
        /*Report DET data transfer is already in progress*/
        Dma_lReportError( DMA_SID_CHDISABLEHARDWARETRIGGER,
                          DMA_E_FREEZE_STATE );
      }
    }
    #endif
    /* Lock exit for core */
    SchM_Exit_Dma_ChannelConfigUpdate();
    /* [cover parentID={6D1AF19B-DC97-423f-8CDB-907B09D2F3C9}]
    Leave the critical section, by calling
    'SchM_Exit_Dma_ChannelConfigUpdate'
    [/cover] */
  }

}
#endif



/*******************************************************************************
** Traceability: [cover parentID={028F2860-2B74-4581-AD01-20C1A66B9D18}]      **
**                                                                            **
** Syntax : void Dma_ChStartTransfer (uint8 Channel)                          **
**                                                                            **
** Description : Service to start the transaction for the channel.            **
**               This function applies software trigger for the DMA transfer  **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x0A                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Conditionally Reentrant - This API is re-entrant for          **
**              different DMA channels                                        **
**                                                                            **
** Parameters (in) :  Channel - DMA channel ID(0-127)                         **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
void Dma_ChStartTransfer
(
  const uint8 Channel
)
{
  #if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
  /* [cover parentID={40B6A038-A6B1-4aa1-AA7D-BF91BDB991DB}]
  DET or Safety Enabled
  [/cover] */
  uint32 lDetStatus;

  /* [cover parentID={832F0DF6-28F9-41e6-950D-7B2D5E2FFBFF}]
  Check for errors
  [/cover] */
  /* [cover parentID={D65BE9A0-86CB-4d1f-BF18-8C614644BD31}]
  Are there any errors?
  [/cover] */
  lDetStatus = Dma_lDetCheck(DMA_SID_CHSTARTTRANSFER, Channel);
  if(lDetStatus == (uint32)FALSE)
  #endif
  {
    /* Lock entry for core */
    SchM_Enter_Dma_ChannelConfigUpdate();
    /* [cover parentID={C3853BC9-5FB9-40ed-A1C4-EC0B4712AEDD}]
    Enter the critical section, by calling
    'SchM_Enter_Dma_ChannelConfigUpdate'
    [/cover] */

    /* Start next transfer only when nothing pending for the channel */
    if(MODULE_DMA.TSR[Channel].B.CH == 0x00U)
    {
      /* [cover parentID={1B909CED-FA1B-4cdf-9144-29C44CE552E0}]
      Is any transfer pending?
      [/cover] */

      /* If channel is in Halt state, don't accept start request*/
      if(MODULE_DMA.TSR[Channel].B.HLTACK == FALSE)
      {
        /* [cover parentID={7340D0E7-2973-48b9-98F9-4D7637E53338}]
        Start transfer
        [/cover] */
        /* [cover parentID={EDF3887F-2E84-4d39-9241-BDF08A61698D}]
        Is channel already in HALT state?
        [/cover] */

        /* Set the ECH bit atomically */
        DMA_SFR_RUNTIME_WRITE32(&(MODULE_DMA.CH[Channel].CHCSR.U),((MODULE_DMA.CH[Channel].CHCSR.U)|
        ((uint32)DMA_BIT_SET << IFX_DMA_CH_CHCSR_SCH_OFF)));
      }
      #if( (DMA_DEV_ERROR_DETECT == STD_ON) || \
           (DMA_SAFETY_ENABLE    == STD_ON) )
      else
      {
        /* [cover parentID={63C26C5D-749D-4efd-B0AE-C1A94BB0B68C}]
        DET or Safety Enabled
        [/cover] */
        /* [cover parentID={0B28C935-EF79-4798-8181-C0B135F3E15C}]
        DET or Safety Enabled
        [/cover] */
        /* [cover parentID={F6B3FBCC-7ADD-4b6e-803E-1185FEE60346}]
        Report DET or safety error for 'channel in freeze state'
        [/cover] */

        /*Report DET channel is in halt state*/
        Dma_lReportError( DMA_SID_CHSTARTTRANSFER, DMA_E_FREEZE_STATE );
      }
      #endif
    }
    #if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
    else
    {

      /*Report DET data transfer is already in progress*/
      Dma_lReportError( DMA_SID_CHSTARTTRANSFER,
                        DMA_E_DATA_TRANSFER_IN_PROGRESS );
    }
    #endif

    /* Lock exit for core */
    SchM_Exit_Dma_ChannelConfigUpdate();

    /* [cover parentID={9A01AD02-1EC2-4dc3-B4EE-0CDEDF46D622}]
    Leave the critical section, by calling
    'SchM_Exit_Dma_ChannelConfigUpdate'
    [/cover] */
  }

}



/*******************************************************************************
** Traceability: [cover parentID={A878195B-FFD9-4174-B164-D2DD686E3C55}]      **
**                                                                            **
** Syntax : void Dma_ChStopTransfer (uint8 Channel)                           **
**                                                                            **
** Description : Service to stop/abort the transaction for the channel.       **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x0B                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Conditionally Reentrant - This API is re-entrant for          **
**              different DMA channels                                        **
**                                                                            **
** Parameters (in) :  Channel - DMA channel ID(0-127)                         **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
void Dma_ChStopTransfer
(
  const uint8 Channel
)
{
  uint32 lLoopCount = 0;
  uint32 lCoreId = 0;         /* ID of core used for execution */
  uint8  lChState;

  #if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
  uint32 lDetStatus;


  lDetStatus = Dma_lDetCheck(DMA_SID_CHSTOPTRANSFER, Channel);
  /* [cover parentID={1050FD22-8B09-4644-BD93-E8BE716B63F4}]
  Check for errors
  [/cover] */
  /* [cover parentID={BD1D8850-5F51-41fc-AB76-D2CF3E742AFA}]
  Are there any errors?
  [/cover] */
  if(lDetStatus == (uint32)FALSE)
  #endif
  {
    /* Lock entry for core */
    SchM_Enter_Dma_ChannelConfigUpdate();

    /* Set the DCH bit atomically and disable all the hardware
     * requests */
    DMA_SFR_RUNTIME_WRITE32(&(MODULE_DMA.TSR[Channel].U),((MODULE_DMA.TSR[Channel].U)|
    ((uint32)DMA_BIT_SET << IFX_DMA_TSR_DCH_OFF)));

    /* [cover parentID={E4692D43-3725-4c86-8B8D-2B0A4DC37AF8}]
    Reset the channel
    [/cover] */

    /* Trigger channel reset */
    DMA_SFR_RUNTIME_WRITE32((&(MODULE_DMA.TSR[Channel].U)),((uint32)DMA_BIT_SET << IFX_DMA_TSR_RST_OFF));

    /* [cover parentID={802F4271-E541-4e0f-8C26-95C87E9A99D6}]
    Wait till channel resets or till timeout expires
    [/cover] */

    /* RST bit will be cleared by the hardware on completion of Channel
     * Reset. Let's wait till reset completes */
    /* Loop timeout will be (65535 * 3.33)ns = 2.18 * 10^5 ns.
       Writing HLTACK bit, time taken by hardware is approximately less than 
       30 SRI clock ticks , i,e 99.99 ns, which is less than loop time, 
       considering while loop taking minimum 4 instructions in assembly */    
    while( (MODULE_DMA.TSR[Channel].B.RST != DMA_BIT_CLEAR)
           &&
           (lLoopCount < (uint32)DMA_TIMEOUT) )
    {
      lLoopCount++;
    }
    #if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
    /* [cover parentID={50D18F7D-00F8-4467-AFA6-6573B889D3B1}]
    DET or Safety Enabled
    [/cover] */
    /* [cover parentID={21F30284-F340-46dd-89BD-B1B34D55A5F7}]
    DET or Safety Enabled
    [/cover] */
    /* Report DET error in case of timeout */
    if(MODULE_DMA.TSR[Channel].B.RST != DMA_BIT_CLEAR)
    {
      /* [cover parentID={9F1E5655-8FE7-447f-92D7-A2568F8F52FF}]
      Did timeout occour, without channel reset?
      [/cover] */
      /* [cover parentID={388DE98D-ED2C-4ce8-8B55-0E3D85216142}]
      Report DET or safety error for 'Timeout'
      [/cover] */

      /*Report DET on DriverState error*/
      Dma_lReportError( DMA_SID_CHSTOPTRANSFER, DMA_E_TIMEOUT );
    }
    #endif
    lCoreId = Dma_kConfigPtr->Dma_ChannelMaps[Channel].Dma_ChannelCoreMap;

    /* Keep the state of the channel as 'Uninitialized' */
    /* [cover parentID={160F114B-D2C6-4c3a-AEB9-077E0BFB6718}]
    Update DMA channel state to 'Un-Initialized'
    [/cover] */
    lChState = (uint8)0xFF ^ ((uint8)0x1 << (uint8)((Dma_kConfigPtr->
            Dma_ChannelMaps[Channel].Dma_ChannelConfIndexMap) % (uint8)8));

    /* No null pointer check needed, since the det checks already
     * covers the possibility */
    (Dma_ChannelStatesPerCore[lCoreId])[Dma_kConfigPtr->
        Dma_ChannelMaps[Channel].Dma_ChannelConfIndexMap / (uint8)8]
                             &= lChState;
    /* Lock exit for core */
    SchM_Exit_Dma_ChannelConfigUpdate();
  }

}

#if (DMA_DATA_PENDING_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={B9782FA8-77FA-41a6-8589-237C35CA26AF}]      **
**                                                                            **
** Syntax : void Dma_ChGetRemainingData (uint8 Channel)                       **
**                                                                            **
** Description : Service to get Number of bytes remaining in the transaction  **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x0C                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Conditionally Reentrant - This API is re-entrant for          **
**              different DMA channels                                        **
**                                                                            **
** Parameters (in) :  Channel - DMA channel ID(0-127)                         **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Pending transfer count                                  **
**                                                                            **
*******************************************************************************/
uint32 Dma_ChGetRemainingData
(
  const uint8 Channel
)
{
  uint32 lRemainingData = 0xFFFFFFFFU;
  #if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
  /* [cover parentID={C95ACCD6-4F0D-4ba5-97F3-0D91DA549905}]
  DET or Safety Enabled
  [/cover] */
  /* [cover parentID={64923CB4-E156-4487-9196-5B24FE37DB33}]
  Check for any DET or safety errors
  [/cover] */

  uint32 lDetStatus;

  /*  Perform the DET checks */
  lDetStatus = Dma_lDetCheck(DMA_SID_CHGETREMAININGDATA, Channel);
  /* [cover parentID={572675AF-55F5-4fc1-A207-1BA398B51AA9}]
  Any errors present?
  [/cover] */
  if(lDetStatus == (uint32)FALSE)
  #endif
  {
    /* [cover parentID={382746C2-1C02-49fb-A763-4C0A734D064C}]
    Enter the critical section, by calling
    'SchM_Enter_Dma_ChannelConfigUpdate'
    [/cover] */

    /* Lock entry for core */
    SchM_Enter_Dma_ChannelConfigUpdate();

    if(MODULE_DMA.TSR[Channel].B.CH == 0x00U)
    {
      /* [cover parentID={2B122278-4374-43d5-915A-101215D7C38C}]
      Is the channel active?
      [/cover] */
      /* [cover parentID={ECC6289E-2ED5-465a-A56C-AF9928B4EEB0}]
      Get the remaining bytes to transmit
      [/cover] */

      lRemainingData = MODULE_DMA.CH[Channel].CHCSR.B.TCOUNT;
    }
    #if( (DMA_DEV_ERROR_DETECT == STD_ON) || \
         (DMA_SAFETY_ENABLE    == STD_ON) )
    /* [cover parentID={BDA77F37-78A7-4e5a-AEF8-547F3DF2198E}]
    DET or Safety Enabled
    [/cover] */
    else
    {
      /* [cover parentID={DF06D64E-1E84-47d8-8809-248F529046F9}]
      DET or Safety Enabled
      [/cover] */

      /* Report DET */
      Dma_lReportError( DMA_SID_CHGETREMAININGDATA,
                        DMA_E_DATA_TRANSFER_IN_PROGRESS );
    }
    #endif

    /* [cover parentID={42784595-7EF9-4375-B256-8E230199F099}]
    Leave the critical section, by calling
    'SchM_Exit_Dma_ChannelConfigUpdate'
    [/cover] */

    /* Lock exit for core */
    SchM_Exit_Dma_ChannelConfigUpdate();
  }

  return lRemainingData;
}
#endif



#if (DMA_BUFFER_SWITCH_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={6AA18613-28D4-48cf-B550-55BCFA690953}]      **
**                                                                            **
** Syntax : void Dma_ChSwitchBuffer (uint8 Channel)                           **
**                                                                            **
** Description : Service to redirect incoming data stream to the empty buffer **
**               in a double buffering scheme.                                **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x0D                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Conditionally Reentrant - This API is re-entrant for          **
**              different DMA channels                                        **
**                                                                            **
** Parameters (in) :  Channel - DMA channel ID(0-127)                         **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
void Dma_ChSwitchBuffer
(
  const uint8 Channel
)
{
  uint8 lDoubleBufferMode;

  #if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
  uint32 lDetStatus;

  /* [cover parentID={B9671F1F-4037-4329-9E8B-74D22E3139D1}]
  DET or Safety Enabled
  [/cover] */
  /* [cover parentID={9C2EBBE8-75A5-488a-A7D3-917D8F04F30F}]
  Check for any DET or safety errors
  [/cover] */

  lDetStatus = Dma_lDetCheck(DMA_SID_CHSWITCHBUFFER, Channel);

  if(lDetStatus == (uint32)FALSE)
  #endif
  {
    /* [cover parentID={0DF1EA2A-DB7F-4a77-92E5-C5A87978F51D}]
    Critical section - ChannelConfigUpdate
    [/cover] */
    /* [cover parentID={4695E807-6137-4c57-9EA8-B78B945028D4}]
    Enter the critical section, by calling 'SchM_Enter_Dma_ChannelConfigUpdate'
    [/cover] */
    /* Lock entry for core */
    SchM_Enter_Dma_ChannelConfigUpdate();

    /* Check if double buffer feature is configured or not. If not then
     * report a DET */
    lDoubleBufferMode = MODULE_DMA.CH[Channel].ADICR.B.SHCT;

    if((lDoubleBufferMode >= DMA_DOUBLE_BUFFER_MODE_START) &&
       (lDoubleBufferMode <= (uint8)DMA_DOUBLE_BUFFER_MODE_END))
    {
      /* [cover parentID={4051BB46-A723-4584-80F6-C9CE100BBF00}]
      Is double buffer feature configured?
      [/cover] */
      /* Check if the channel is active */
      /* [cover parentID={C5071D48-E1F2-4702-B4FF-C472EA02710A}]
         Is the channel active?
         [/cover] */
      if( MODULE_DMA.TSR[Channel].B.CH == 0x00U )
      {
        /* The channel is not active */

        /* [cover parentID={4FE9732A-5089-4cb3-B3FA-58E8ECBA7CDE}]
        Switch buffer by setting SWB bit of CHCSR to 1
        [/cover] */

        /* Switch the buffer */
        DMA_SFR_RUNTIME_WRITE32((&(MODULE_DMA.CH[Channel].CHCSR.U)),((uint32)DMA_BIT_SET << IFX_DMA_CH_CHCSR_SWB_OFF));
      }
      #if( (DMA_DEV_ERROR_DETECT == STD_ON) || \
           (DMA_SAFETY_ENABLE    == STD_ON) )
      else
      {
        /* [cover parentID={D51B17D4-1CE5-4f6e-AE98-88E6791B1377}]
        DET or Safety Enabled
        [/cover] */
        /* [cover parentID={ECCC00F6-38F2-4e62-8E5C-EF6E673D3A57}]
        Report DET or safety error for 'transfer in progress'
        [/cover] */

        /* Report DET */
        Dma_lReportError( DMA_SID_CHSWITCHBUFFER,
                          DMA_E_DATA_TRANSFER_IN_PROGRESS );
      }
      #endif

    }
    #if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
    else
    {
      /* [cover parentID={5952FF62-03C6-42d0-B7A0-A411616E1FC2}]
      Report DET or safety error for 'Invalid switch request'
      [/cover] */
      /* [cover parentID={4FFC7B80-D819-41ef-BA96-0EBAEC99C465}]
      DET or Safety Enabled
      [/cover] */

      /* Report DET for invalid switching request */
      Dma_lReportError( DMA_SID_CHSWITCHBUFFER,
                        DMA_E_CHANNEL_INVALID_SWITCH_REQ );
    }
    #endif

    /* [cover parentID={871CAB35-1B3B-433c-8AEE-8B577E812AA7}]
       Leave the critical section, by calling
       'SchM_Enter_Dma_ChannelConfigUpdate'
       [/cover] */
    /* Lock exit for core */
    SchM_Exit_Dma_ChannelConfigUpdate();
  }

}
#endif



/*******************************************************************************
** Traceability: [cover parentID={EFF604E0-5F6F-4fde-8371-C071A1E94D7F}]      **
**                                                                            **
** Syntax : void Dma_ChStatusClear (uint8 Channel,                            **
**                                  Dma_ChEventType Event)                    **
**                                                                            **
** Description : Service to clear channel Event                               **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x0F                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Conditionally Reentrant - This API is re-entrant for          **
**              different DMA channels                                        **
**                                                                            **
** Parameters (in) :  Channel - DMA channel ID(0-127)                         **
**                    Event   - Event to be cleared for assertion             **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
void Dma_ChStatusClear
(
  const uint8 Channel,
  const Dma_EventsType Event
)
{
  #if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
  uint32 lDetStatus;

  /* [cover parentID={76BDBFD3-421C-4392-98E4-B61ECFF37AB3}]
  DET or Safety Enabled
  [/cover] */
  /* [cover parentID={5C8DEE0E-75FA-421e-875E-5B6B9D9FFA98}]
  Check for any DET or safety errors
  [/cover] */

  lDetStatus = Dma_lDetCheck(DMA_SID_CHSTATUSCLEAR, Channel);

  /* [cover parentID={ECBE9703-0F50-4955-B102-46E5AA7CF1CF}]
  Any errors present?
  [/cover] */
  if(lDetStatus == (uint32)FALSE)
  #endif
  {
    SchM_Enter_Dma_ChannelConfigUpdate();

    /* [cover parentID={94CF1AF0-A833-4329-98C1-4233B7CA6A4B}]
    Is the channel active?
    [/cover] */
    if(MODULE_DMA.TSR[Channel].B.CH == 0x00U)
    {
      if((Event == DMA_EVENT_CH_TRANSFER_COMPLETE)||(Event == DMA_EVENT_CH_PATTERN_DETECTION))
      {
        /* [cover parentID={613BA06D-DBAC-4941-BC0D-085E7565B5EA}]
        Clear the interrupt, using the CICH bit of CHCSR register
        [/cover] */
        /* [cover parentID={26ED629E-B1DF-41a9-B0F6-CDAB86481195}]
        Is 'Transfer Complete' or 'pattern matching'
         event requested?
        [/cover] */

        /* Clear Interrupt for DMA Channel */
        DMA_SFR_RUNTIME_WRITE32(&(MODULE_DMA.CH[Channel].CHCSR.U),((MODULE_DMA.CH[Channel].CHCSR.U)|
        ((uint32)DMA_BIT_SET << IFX_DMA_CH_CHCSR_CICH_OFF)));
      }
      else if((Event == DMA_EVENT_CH_BUFFER_WRAP_SOURCE) ||
              (Event == DMA_EVENT_CH_BUFFER_WRAP_DEST))
      {
        /* [cover parentID={05229DE9-78ED-4a40-B545-9A3B2D304F9E}]
        Clear the interrupt, using the CWRP bit of CHCSR register
        [/cover] */
        /* [cover parentID={D2B053DF-5C36-4746-AACF-A86C60FFF740}]
        Is 'Wrap source/destination'
        event requested?
        [/cover] */

        /* Clear Wrap Buffer Interrupt */
        DMA_SFR_RUNTIME_WRITE32(&(MODULE_DMA.CH[Channel].CHCSR.U),((MODULE_DMA.CH[Channel].CHCSR.U)|
        ((uint32)DMA_BIT_SET << IFX_DMA_CH_CHCSR_CWRP_OFF)));
      }
      else
      {
        /* Do nothing */;
        #if( (DMA_DEV_ERROR_DETECT == STD_ON) || \
                (DMA_SAFETY_ENABLE == STD_ON) )
        /* [cover parentID={F5CDCA77-6450-48a0-ADAB-1FF76775632A}]
        DET or Safety Enabled
        [/cover] */
        /* [cover parentID={A87D0C40-AE3F-4fb2-A84F-6223E5611A4B}]
        Report DET or safety error for invalid event
        [/cover] */

        Dma_lReportError( DMA_SID_CHSTATUSCLEAR,
                          DMA_E_CHANNEL_INVALID_EVENT );
        #endif
      }
    }
    #if( (DMA_DEV_ERROR_DETECT == STD_ON) || \
         (DMA_SAFETY_ENABLE    == STD_ON) )
    /* [cover parentID={C06C5DEE-3A1C-463e-A888-5E33B9C23C5C}]
       DET or Safety Enabled
       [/cover] */
    else
    {
      /* [cover parentID={87E6745A-DD8A-4843-9691-24398060402F}]
         Report DET or safety error for 'transfer in progress'
         [/cover] */

      /* Report DET */
      Dma_lReportError( DMA_SID_CHSTATUSCLEAR,
                        DMA_E_DATA_TRANSFER_IN_PROGRESS );
    }
    #endif

    SchM_Exit_Dma_ChannelConfigUpdate();
  }
}



/*******************************************************************************
** Traceability: [cover parentID={C45E5999-3486-446c-B00C-42A45A9CAF00}]      **
**                                                                            **
** Syntax : void Dma_ChInterruptEnable (uint8 Channel,                        **
**                                     Dma_ChEventType Event)                 **
**                                                                            **
** Description : Service to enable channel interrupt                          **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x10                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Conditionally Reentrant - This API is re-entrant for          **
**              different DMA channels                                        **
**                                                                            **
** Parameters (in) :  Channel - DMA channel ID(0-127)                         **
**                    Event   - channel interrupt to be enabled               **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
void Dma_ChInterruptEnable
(
  const uint8 Channel,
  const Dma_EventsType Event
)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: Union based type definition for SFR
     access. Variable of SFR type defined for writing into register.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_DMA_TSR lTsrReg;

  #if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
  uint32 lDetStatus;
  uint32 lCoreId = 0;         /* ID of core used for execution */

  /* The channel index for accessing the settings */
  uint8 lChIndex;


  /* [cover parentID={61299BDE-2CBB-4f06-9C49-D7FD0026ED37}]
  DET or Safety Enabled
  [/cover] */
  /* [cover parentID={ED788203-3942-4976-9C25-2D0E9EDFA982}]
  Check for any DET or safety errors
  [/cover] */

  lDetStatus = Dma_lDetCheck(DMA_SID_CHINTERRUPTENABLE, Channel);

  /* Get the core ID of the core, where we are executing at this moment */
  lCoreId = Mcal_GetCpuIndex();

  /* [cover parentID={FE22CEFA-1415-4bea-B89F-5752245228C7}]
  Any errors present?
  [/cover] */
  if(lDetStatus == FALSE)
  {
    /* Get the channel configuration index */
    lChIndex = Dma_kConfigPtr->
               Dma_ChannelMaps[Channel].Dma_ChannelConfIndexMap;

    if( Dma_kConfigPtr->DmaCoreConfigPtr[lCoreId]->
                        DmaChConfigPtr[lChIndex].DmaChNotifPtr == NULL_PTR )
    {
      /* [cover parentID={C658E61C-2636-488b-BE9D-96A7D14F2CCC}]
      Report DET or safety error for no notification pointer
      [/cover] */
      /* [cover parentID={9F081347-6C62-4215-B856-589F738F4734}]
      Is notification a null pointer?
      [/cover] */

      /* Report DET for the null pointer in interrupt handler */
      Dma_lReportError( DMA_SID_CHINTERRUPTENABLE,
                        DMA_E_CH_NO_NOTIFICATION_CONFIGURED );

      lDetStatus = TRUE;
    }
    else
    {
      /* Do nothing */
    }
  }

  if(lDetStatus == (uint32)FALSE)
  #endif
  {
    /* [cover parentID={CC0EB67E-5DC3-400a-9F82-82DEAF854B99}]
    Critical Section - ChannelConfigUpdate
    [/cover] */
    /* [cover parentID={600DD0C4-A381-44d0-ACE5-6A5E31C310FD}]
    Enter the critical section, by calling
    'SchM_Enter_Dma_ChannelConfigUpdate'
    [/cover] */

    SchM_Enter_Dma_ChannelConfigUpdate();

    lTsrReg.U = MODULE_DMA.TSR[Channel].U;

    if( (lTsrReg.B.CH       == 0x00U) &&
        (lTsrReg.B.HLTACK   == 0x00U) )
    {

      if(Event == DMA_EVENT_CH_TRANSFER_COMPLETE)
      {
        /* [cover parentID={935D65A0-9F2B-431f-B3CA-FB2CCAB1C4BB}]
        Clear the previous transfer interrupt
        [/cover] */

        /* Clear any past interrupts of the channel, first */
        DMA_SFR_RUNTIME_WRITE32(&(MODULE_DMA.CH[Channel].CHCSR.U),((MODULE_DMA.CH[Channel].CHCSR.U)|
        ((uint32)DMA_BIT_SET << IFX_DMA_CH_CHCSR_CICH_OFF)));

        /* [cover parentID={E700C757-4EBD-436f-88A6-DA62B8D89150}]
        Enable Channel Interrupt trigger,
        by setting INTCT bits, of ADICR register
        [/cover] */
        /* [cover parentID={C1285423-6A19-4ce2-BBFF-4A950BFEE878}]
        Is 'Transfer Complete' 
        event requested?
        [/cover] */

        /* Clear Interrupt for DMA Channel first */
        DMA_SFR_RUNTIME_WRITE32(&(MODULE_DMA.CH[Channel].ADICR.U),((MODULE_DMA.CH[Channel].ADICR.U)|
        ((uint32)DMA_BIT_SET << ((uint8)(IFX_DMA_CH_ADICR_INTCT_OFF+1u)))));
      }
      else if(Event == DMA_EVENT_CH_BUFFER_WRAP_SOURCE)
      {
        /* [cover parentID={D64E5EE5-8C63-4505-81C5-0F29AC1B7446}]
        Is 'Wrap Source'
        event requested?
        [/cover] */

        /* Clear any past wrap buffer interrupts */
        DMA_SFR_RUNTIME_WRITE32(&(MODULE_DMA.CH[Channel].CHCSR.U),((MODULE_DMA.CH[Channel].CHCSR.U)|
        ((uint32)DMA_BIT_SET << IFX_DMA_CH_CHCSR_CWRP_OFF)));

        /* [cover parentID={621D482B-B495-421d-8202-4C9D6CFAEC2D}]
        Enable wrap source interrupt, using WRPSE bit
        [/cover] */
        /* Enable the wrap buffer interrupt */
        DMA_SFR_RUNTIME_WRITE32(&(MODULE_DMA.CH[Channel].ADICR.U),((MODULE_DMA.CH[Channel].ADICR.U)|
        ((uint32)DMA_BIT_SET << IFX_DMA_ME_ADICR_WRPSE_OFF)));
      }
      else if(Event == DMA_EVENT_CH_BUFFER_WRAP_DEST)
      {
        /* [cover parentID={A3410818-6EFF-485c-BD7A-BDE742C9B1EF}]
        Clear the previous wrap destination interrupt
        [/cover] */
        /* [cover parentID={25AA28AB-608C-4533-BF69-05FAF354F605}]
        Is 'Wrap Destination'
        event requested?
        [/cover] */

        /* Clear any past wrap buffer interrupts */
        DMA_SFR_RUNTIME_WRITE32(&(MODULE_DMA.CH[Channel].CHCSR.U),((MODULE_DMA.CH[Channel].CHCSR.U)|
        ((uint32)DMA_BIT_SET << IFX_DMA_CH_CHCSR_CWRP_OFF)));

        /* [cover parentID={4A9FDB52-2E7C-4129-AB0D-EFE00A0B42BF}]
        Enable wrap destination interrupt, using WRPDE bit
        [/cover] */

        /* Enable the wrap destination interrupt */
        DMA_SFR_RUNTIME_WRITE32(&(MODULE_DMA.CH[Channel].ADICR.U),((MODULE_DMA.CH[Channel].ADICR.U)|
        ((uint32)DMA_BIT_SET << IFX_DMA_ME_ADICR_WRPDE_OFF)));
      }      
      else
      {
        #if( (DMA_DEV_ERROR_DETECT == STD_ON) || \
             (DMA_SAFETY_ENABLE    == STD_ON) )
        /* [cover parentID={D9367097-9D5E-4e4e-9BB5-C8D66C940258}]
        Return DET or safety error for invalid event
        [/cover] */
        /* [cover parentID={82BC166C-DF62-41be-9BF3-AA1C7CFA56F3}]
        DET or Safety Enabled
        [/cover] */

        /*Report DET for Invalid event*/
        Dma_lReportError( DMA_SID_CHINTERRUPTENABLE,
                          DMA_E_CHANNEL_INVALID_EVENT );
        #endif
        /* Do nothing */
      }
    }
    #if( (DMA_DEV_ERROR_DETECT == STD_ON) || \
         (DMA_SAFETY_ENABLE    == STD_ON) )
    /* [cover parentID={1B72A726-1D28-43ca-9F5A-64D8995C7A95}]
    DET or Safety Enabled
    [/cover] */
    else
    {
      if(lTsrReg.B.HLTACK == (uint32)DMA_BIT_SET)
      {
        /* [cover parentID={EECF61AB-50C4-4e6c-B5C8-BDD02FED4528}]
        Is the channel in freeze state?
        [/cover] */

        /* Report DET data transfer is already in progress*/
        /* [cover parentID={C24CD4C9-4FF4-4d23-90FB-3DB980C019B1}]
        Report DET or safety error for channel in freeze state
        [/cover] */
        Dma_lReportError( DMA_SID_CHINTERRUPTENABLE,
                          DMA_E_FREEZE_STATE );
      }

      if(lTsrReg.B.CH == (uint32)DMA_BIT_SET)
      {
        /* [cover parentID={68169C18-87B0-494a-AFD4-004098CE6ADA}]
        Is the channel active?
        [/cover] */
        /* Report DET */
        Dma_lReportError( DMA_SID_CHINTERRUPTENABLE,
                          DMA_E_DATA_TRANSFER_IN_PROGRESS );
      }
    }
    #endif

    /* [cover parentID={A1D2C8BF-2C03-4c60-A749-67EC1422B6BD}]
    Exit the critical section, by calling 'SchM_Exit_Dma_ChannelConfigUpdate'
    [/cover] */
    SchM_Exit_Dma_ChannelConfigUpdate();
  }
}



/*******************************************************************************
** Traceability: [cover parentID={99B1D618-E9A4-4fbd-BE28-43E916446A90}]      **
**                                                                            **
** Syntax : void Dma_ChInterruptDisable (uint8 Channel,                       **
**                                       Dma_ChEventType Event)               **
**                                                                            **
** Description : Service to disable channel interrupt                         **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x11                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Conditionally Reentrant - This API is re-entrant for          **
**              different DMA channels                                        **
**                                                                            **
** Parameters (in) :  Channel - DMA channel ID(0-127)                         **
**                    Event   - channel interrupt to be disabled              **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
void Dma_ChInterruptDisable
(
  const uint8 Channel,
  const Dma_EventsType Event
)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: Union based type definition for SFR
     access. Variable of SFR type defined for writing into register.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_DMA_TSR lTsrReg;

  #if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
  uint32 lDetStatus;

  /* [cover parentID={E9AB3885-D3BC-4634-B847-5D58B0C59238}]
  DET or Safety Enabled
  [/cover] */
  /* [cover parentID={76AFA8B0-A2EC-4b00-9BBA-B1E61ECEE3EE}]
  Check for any DET or safety errors
  [/cover] */

  lDetStatus = Dma_lDetCheck(DMA_SID_CHINTERRUPTDISABLE, Channel);

  /* [cover parentID={C9FD63B9-49F8-4f87-8CBA-2800F22211F1}]
  Any errors present?
  [/cover] */

  if(lDetStatus == (uint32)FALSE)
  #endif
  {
    /* [cover parentID={727C4C2F-E1D7-41c4-B626-24C212BCE2B0}]
    Enter the critical section, by calling 'SchM_Enter_Dma_ChannelConfigUpdate'
    [/cover] */

    SchM_Enter_Dma_ChannelConfigUpdate();

    lTsrReg.U = MODULE_DMA.TSR[Channel].U;

    if( (lTsrReg.B.CH       == 0x00U) &&
        (lTsrReg.B.HLTACK   == 0x00U) )
    {
      if(Event == DMA_EVENT_CH_TRANSFER_COMPLETE)
      {
        /* [cover parentID={0212C3E8-33CF-45f0-B869-077F9B7AA3C6}]
        Disable Channel Interrupt trigger,
        by clearing INTCT bits, of ADICR register
        [/cover] */
        /* [cover parentID={580E59CE-F6BF-4622-898F-F4C7BF489B37}]
        Is 'Transfer Complete' 
        event requested?
        [/cover] */

        /* Disable the channel interrupt */
        DMA_SFR_RUNTIME_WRITE32(&(MODULE_DMA.CH[Channel].ADICR.U),((MODULE_DMA.CH[Channel].ADICR.U)&
        (~((uint32)DMA_BIT_SET << ((uint8)(IFX_DMA_CH_ADICR_INTCT_OFF+1u))))));
      }
      else if(Event == DMA_EVENT_CH_BUFFER_WRAP_SOURCE)
      {
        /* [cover parentID={C30DDBEB-83BD-4594-8A58-382C94037A7F}]
        Disable wrap source interrupt, using WRPSE bit
        [/cover] */
        /* [cover parentID={18E10C19-99D6-40ae-9B8B-1A99A5065C40}]
        Is 'Wrap Source'
        event requested?
        [/cover] */

        /* Disable the wrap source interrupt */
        DMA_SFR_RUNTIME_WRITE32(&(MODULE_DMA.CH[Channel].ADICR.U),((MODULE_DMA.CH[Channel].ADICR.U)&
        (~((uint32)DMA_BIT_SET << IFX_DMA_CH_ADICR_WRPSE_OFF))));
      }
      else if(Event == DMA_EVENT_CH_BUFFER_WRAP_DEST)
      {
        /* [cover parentID={5B9E90E6-9D47-44ef-80C0-EBE9F1553595}]
        Disable wrap destination interrupt, using WRPDE bit
        [/cover] */
        /* [cover parentID={04E15641-65B0-49c8-903F-9413DB7AB3AD}]
        Is 'Wrap Destination'
        event requested?
        [/cover] */

        /* Disable the wrap destination interrupt */
        DMA_SFR_RUNTIME_WRITE32(&(MODULE_DMA.CH[Channel].ADICR.U),((MODULE_DMA.CH[Channel].ADICR.U)&
        (~((uint32)DMA_BIT_SET << IFX_DMA_CH_ADICR_WRPDE_OFF))));
      }
      else
      {
        /* Do nothing */
        #if( (DMA_DEV_ERROR_DETECT == STD_ON) || \
                (DMA_SAFETY_ENABLE == STD_ON) )
        /* [cover parentID={B5D2CCCE-065E-455a-8A51-EA8B2AAF1CDC}]
        Return DET or safety error for invalid event
        [/cover] */
        /* [cover parentID={0C18B88C-064A-47a6-B22B-48998F1A6AF4}]
        DET or Safety Enabled
        [/cover] */

        /*Report DET for Invalid event*/
        Dma_lReportError( DMA_SID_CHINTERRUPTDISABLE,
                          DMA_E_CHANNEL_INVALID_EVENT );
        #endif
      }
    }
    #if( (DMA_DEV_ERROR_DETECT == STD_ON) || \
         (DMA_SAFETY_ENABLE    == STD_ON) )
    /* [cover parentID={51C1081C-5031-4239-977F-145B1F433D40}]
     DET or Safety Enabled
     [/cover] */
    else
    {
      if(lTsrReg.B.HLTACK == (uint32)DMA_BIT_SET)
      {
        /* [cover parentID={BEA93BF9-2E01-4418-9BA1-7F96763D9770}]
        Is the channel active?
        [/cover] */
        /* [cover parentID={918B65FC-82EF-4e77-8DE8-D613B75A9D5F}]
           Report DET or safety error for channel in freeze state
           [/cover] */
        /* Report DET data transfer is already in progress*/
        Dma_lReportError( DMA_SID_CHINTERRUPTDISABLE,
                          DMA_E_FREEZE_STATE );
      }

      if(lTsrReg.B.CH == (uint32)DMA_BIT_SET)
      {
        /* [cover parentID={0CDC82E5-133D-4b47-A209-42187C6759A5}]
        Is the channel active?
        [/cover] */
        /* [cover parentID={D1EB94DB-7A52-49db-8EA8-7C670AC1B357}]
        Report DET or safety error for 'transfer in progress'
        [/cover] */
        /* Report DET */
        Dma_lReportError( DMA_SID_CHINTERRUPTDISABLE,
                          DMA_E_DATA_TRANSFER_IN_PROGRESS );
      }
    }
    #endif

    /* [cover parentID={278AA0D4-F125-4ad9-91F2-6380A7204B1B}]
    Exit the critical section, by calling 'SchM_Exit_Dma_ChannelConfigUpdate'
    [/cover] */
    SchM_Exit_Dma_ChannelConfigUpdate();
  }
}


#if (DMA_GETVERSIONINFO_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={195144AC-FCE7-4e39-9C66-79775418B016}]      **
**                                                                            **
** Syntax : void Dma_GetVersionInfo (Std_VersionInfoType * VersionInfoPtr)    **
**                                                                            **
** Description : Service to get DMA driver version                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x12                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant                                                     **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  VersionInfoPtr -  Pointer to store version ID by driver **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
void Dma_GetVersionInfo
(
  Std_VersionInfoType* const VersionInfoPtr
)
{
  /* [cover parentID={261EDA17-B08B-4f4d-B993-E305B61AD562}]
  Dma_GetVersionInfo
  [/cover] */

  #if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
  /* [cover parentID={32B82076-D466-41f8-A4C3-962FAD8AA0DA}]
  DET or Safety Enabled
  [/cover] */

  /* Did we get a null pointer? */
  if(VersionInfoPtr == NULL_PTR)
  {
    /* [cover parentID={6418ED9E-0F28-48e3-844A-369791B4B379}]
    Report DET or safety error for null pointer
    [/cover] */
    /* [cover parentID={9C94A550-A0C7-4e28-B25C-C4E6CBC314BF}]
    Is the version info
    pointer null?
    [/cover] */

    /*Report DET on Null pointer error*/
    Dma_lReportError( DMA_SID_CHGETVERSIONINFO, DMA_E_NULL_POINTER );
  }
  else
  #endif
  {
    /* [cover parentID={180B570C-1EAA-4b45-A912-71E6D5495582}]
    Store the module ID, SW version and Vendor ID to the provided pointer
    [/cover] */

    /* Provide the module ID, vendor ID and the SW version */
    VersionInfoPtr->moduleID         = DMA_MODULE_ID;
    VersionInfoPtr->sw_major_version = DMA_SW_MAJOR_VERSION;
    VersionInfoPtr->sw_minor_version = DMA_SW_MINOR_VERSION;
    VersionInfoPtr->sw_patch_version = DMA_SW_PATCH_VERSION;
    VersionInfoPtr->vendorID         = DMA_VENDOR_ID;
  }
}
#endif



/*******************************************************************************
** Traceability: [cover parentID={919CF77C-4A6C-4e65-A530-AA0D79126C62}]      **
**                                                                            **
** Syntax : uint32 Dma_GetEvents( uint8 Channel )                             **
**                                                                            **
** Description : Service to get list of all events happened on a DMA channel, **
**               including the channel events and error events.               **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x0E                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Conditionally Reentrant - This API is re-entrant for          **
**              different DMA channels                                        **
**                                                                            **
** Parameters (in) :  Channel - Dma Channel ID                                **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Status word containing consolidated channel events      **
**                                                                            **
*******************************************************************************/
uint32 Dma_GetEvents
(
  const uint8 Channel
)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: Union based type definition for SFR
   * access. Variable of SFR type defined for writing into register.
   * No side effects foreseen by violating this MISRA rule.*/
  Ifx_DMA_CH_CHCSR lChcsrReg;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: Union based type definition for SFR
   * access. Variable of SFR type defined for writing into register.
   * No side effects foreseen by violating this MISRA rule.*/
  Ifx_DMA_ME_ERRSR lMeErrReg;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: Union based type definition for SFR
   * access. Variable of SFR type defined for writing into register.
   * No side effects foreseen by violating this MISRA rule.*/
  Ifx_DMA_ME_ERRSR lMe0ErrReg;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: Union based type definition for SFR
   * access. Variable of SFR type defined for writing into register.
   * No side effects foreseen by violating this MISRA rule.*/
  Ifx_DMA_ME_ERRSR lMe1ErrReg;
  Std_ReturnType lChannelStatus = FALSE;
  uint32 lRetVal = 0x00;
  lMeErrReg.U = 0x00;

  /* [cover parentID={7B511974-14AF-48b5-A807-31CC3CDF4C89}]
  Read the events information and store locally
  [/cover] */
  /* [cover parentID={45CE7866-632E-461a-A3DC-4FD9696633C3}]
  Get the Move Engine errors
  [/cover] */


  #if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
  uint32 lDetStatus;

  /* [cover parentID={FBD55F0C-E676-4be6-81E1-18F19C62CCC7}]
  DET or Safety Enabled
  [/cover] */

  /* [cover parentID={7C90B6FB-5F9A-4aea-ACA7-8C6B7F4F259D}]
  Check for any DET or safety errors
  [/cover] */

  /* Check for any DETs */
  lDetStatus = Dma_lDetCheck(DMA_SID_GETEVENTS, Channel);

  /* Any DETs present? */
  /* [cover parentID={53DB26ED-76E0-46b9-A309-A58B26A6D1FB}]
  Any errors present?
  [/cover] */
  if(lDetStatus == (uint32)FALSE)
  #endif
  {
    /* Get the events info */
    lChcsrReg  = MODULE_DMA.CH[Channel].CHCSR;
    lMe0ErrReg = DMA_ME0_ERRSR;
    lMe1ErrReg = DMA_ME1_ERRSR;

    /* Is channel active? */
    if(MODULE_DMA.TSR[Channel].B.CH == 0x00U)
    {
      /* [cover parentID={44037B2D-89A1-479c-9A39-3DDB3DD650F8}]
      Is the channel active?
      [/cover] */
      if(lChcsrReg.B.ICH == DMA_BIT_SET)
      {
        /* [cover parentID={BEDD1B3F-C384-4984-83CE-C6C8E55C8D54}]
        Is there a 'transfer complete' event?
        [/cover] */
        /* [cover parentID={BF58B6D3-7687-4ad2-A178-93E05CB63367}]
        Mark the event as 'Transfer complete'
        [/cover] */
        lRetVal = (uint32)DMA_EVENT_CH_TRANSFER_COMPLETE;
      }

      if(lChcsrReg.B.WRPD == DMA_BIT_SET)
      {
        /* [cover parentID={125367DE-6CEA-4ec1-8F34-06965B79B51A}]
        Is there a 'wrap destination' event?
        [/cover] */
        /* [cover parentID={CD8326E7-3391-4aad-906C-ED3D80D09EA0}]
        Mark the event as 'Wrap Destination'
        [/cover] */
        lRetVal |= (uint32)DMA_EVENT_CH_BUFFER_WRAP_DEST;
      }

      if(lChcsrReg.B.WRPS == DMA_BIT_SET)
      {
        /* [cover parentID={0A11D2EF-ECFE-45b1-9C2D-9ADAA0E780AE}]
        Is there a 'wrap source' event?
        [/cover] */
        /* [cover parentID={F476655C-8D18-42ad-8C29-D0234D59A2B3}]
        Mark the event as 'Wrap Source'
        [/cover] */
        lRetVal |= (uint32)DMA_EVENT_CH_BUFFER_WRAP_SOURCE;
      }
   
       if(lChcsrReg.B.IPM == DMA_BIT_SET)
      {
        /* [cover parentID={051BEFF4-6411-478e-B1F2-DB9C7B4A1A1A}]
        Is there a 'Pattern detection' event?
        [/cover] */       
        /* 
        Mark the event as 'Pattern detection'
        [/cover] */
        lRetVal |= (uint32)DMA_EVENT_CH_PATTERN_DETECTION;
      }

      /* Check if any event is available on ME 0 */
      if((lMe0ErrReg.U & DMA_ERROR_STATUS_MASK) != 0x00U)
      {
        /* [cover parentID={1938755D-855B-405b-BCFE-453C8A36A4D1}]
        Is there an ME error present?
        [/cover] */
        /* [cover parentID={E9589940-C784-414d-8391-866DB4616C05}]
        Is there an ME0 error?
        [/cover] */

        /* Verify that event set on this ME is for the
         * required channel */
        if(lMe0ErrReg.B.LEC == Channel)
        {
          /* [cover parentID={76D2085C-E831-4795-BA21-12ECB0C2596F}]
          Is the error for the
          requested channel?
          [/cover] */
          /* [cover parentID={53DC8982-C328-40d0-9AED-7019FC21C8A1}]
          Mark the ME status as 'error present'
          [/cover] */
          lChannelStatus = TRUE;
          lMeErrReg = lMe0ErrReg;
        }
      }

      /* In case We are not able to find the Channel event on ME0 then
       * check if there is any event pending on ME1 */
      if( ((lMe1ErrReg.U & DMA_ERROR_STATUS_MASK) != 0x00U) &&
          (lChannelStatus == FALSE) )
      {
        /* [cover parentID={C1B89804-9529-4080-9865-1A579136D5AA}]
        Is there no ME0 error and is there an ME1 error?
        [/cover] */

        /* Verify that event set on this ME is for the
         * required channel */
        if(lMe1ErrReg.B.LEC == Channel)
        {
          /* [cover parentID={CDCD4112-0E33-4f6d-9D16-66A4D0C74DF4}]
          Is the error for the
          requested channel?
          [/cover] */
          /* [cover parentID={2442A1A6-E2AB-421d-BA2D-1BF1011E89CB}]
          Mark the ME status as 'error present'
          [/cover] */
          lChannelStatus = TRUE;
          lMeErrReg = lMe1ErrReg;
        }
      }

      if(lChannelStatus == TRUE)
      {
        /* MISRA2012_RULE_1_3_JUSTIFICATION: Local function Dma_lEvaluateMEError
           with address of variable lMeErrReg has been created for 
           maintainability and readability of the code, no address manipulation 
           has been performed. The auto variable lMeErrReg is only in read only 
           mode in the local called function. Hence, it is not an issue. 
        */
        lRetVal |= Dma_lEvaluateMEError(&lMeErrReg);
      }

      if(MODULE_DMA.TSR[Channel].B.TRL == DMA_BIT_SET)
      {
        /* [cover parentID={E633CAD7-6034-47d9-A33F-0EED681A65AC}]
        Is there
        a TRL error?
        [/cover] */
        /* [cover parentID={DEB0811E-197B-449b-992C-78C656681E71}]
        Mark the error as 'TRL error'
        [/cover] */

        /*  Transaction Lost event */
        lRetVal |= (uint32)DMA_EVENT_CH_TRL_ERROR;
      }
    }
    else
    {
      /* [cover parentID={D62DE0E0-657E-4cdb-9B0E-E7B07F0F8EAE}]
      Mark the channel as active
      [/cover] */
      lRetVal = (uint32)DMA_EVENT_CH_RUNNING;
    }

  }
  /* [cover parentID={519424AC-7B29-4022-B2FE-4751A707A9E6}]
  Return the error information
  [/cover] */
  return lRetVal;
}


/* CYCLOMATIC_Dma_GetCrcValue_JUSTIFICATION: This API checks for all
the CRC modes which causes extra checks in the code. */
/*******************************************************************************
** Traceability: [cover parentID={C12260FC-604B-4366-A703-E154F893A7CC}]      **
**                                                                            **
** Syntax : Std_ReturnType Dma_GetCrcValue(uint8 ChannelId,                   **
**                                         uint32 CrcType,                    **
**                                         uint32* CrcBuffer)                 **
**                                                                            **
** Description : Service to read the CRC value calculated by the DMA hardware **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x17                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant                                                     **
**                                                                            **
** Parameters (in) :  ChannelId - DMA channel ID                              **
**                    CrcType   - Address CRC or Data CRC selection           **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  CRC value calculated by the hardware                    **
**                                                                            **
*******************************************************************************/
uint32 Dma_GetCrcValue
(
  const uint8 ChannelId,
  const Dma_CrcType CrcType
)
{
  /* The CRC value to be given back to the caller */
  uint32 CrcValue = 0;

  #if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
  /* [cover parentID={EF753F15-6C55-4c0a-BF02-309E88756A4E}]
  DET or safety checks enabled
  [/cover] */

  /* ADICR register value */
  /* MISRA2012_RULE_19_2_JUSTIFICATION: Union based type definition for SFR
     access. Variable of SFR type defined for writing into register.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_DMA_CH_ADICR lAdicr;

  /* The result of the DET checks */
  uint32 lDetStatus;

  /* [cover parentID={0970E23C-73AC-4ac9-9FF1-3766D5A3FC08}]
  Check for regular set of errors
  [/cover] */

  /* Regular DET checks */
  lDetStatus = Dma_lDetCheck(DMA_SID_GETCRCVALUE, ChannelId);

  /* [cover parentID={946EF8FB-0B6E-4959-8BC0-1A84BE78E45F}]
  Are any errors detected?
  [/cover] */
  if( lDetStatus == FALSE ) /* No DETs present */
  #endif
  {
    SchM_Enter_Dma_ChannelConfigUpdate();

    #if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
    /* [cover parentID={53373E12-4B0E-46ea-8D7E-1F80FF1D963E}]
    DET or Safety Enabled
    [/cover] */

    lAdicr.U = MODULE_DMA.CH[ChannelId].ADICR.U;

    /* Is the CRC type invalid? */
    if( (CrcType != DMA_DATA_CRC_TYPE)
        &&
        (CrcType != DMA_ADDRESS_CRC_TYPE) )
    {
      /* [cover parentID={418F2300-BD4D-4154-9C15-28AC4DD35F68}]
      Is the address CRC requested?
      [/cover] */
      /* [cover parentID={24042816-8237-4778-99B5-0D87E19204D9}]
      Check if the CRC type is invalid
      [/cover] */
      /* [cover parentID={EDC63B7C-B57C-4d96-9ADF-243997CD9CDB}]
      Report invalid CRC type error
      [/cover] */

      /* Raise DET for invalid CRC type request */
      Dma_lReportError( DMA_SID_GETCRCVALUE, DMA_E_INVALID_CRC_TYPE_REQ );
    }
    else if( (lAdicr.B.SHCT ==  DMA_DBL_SRC_BUFF_SW_SWITCH ) ||
             (lAdicr.B.SHCT ==  DMA_DBL_SRC_BUFF_HW_SWITCH ) ||
             (lAdicr.B.SHCT ==  DMA_DBL_DEST_BUFF_SW_SWITCH) ||
             (lAdicr.B.SHCT ==  DMA_DBL_DEST_BUFF_HW_SWITCH) ||
             (lAdicr.B.SHCT ==  DMA_CONDITIONAL_LINKED_LIST)      )
    {
      /* [cover parentID={FDC201E5-8368-4f14-8833-ADFEDCFDFCE5}]
      CRC specific error checks
      [/cover] */
      /* [cover parentID={DB87486C-C50C-4f15-A1FB-BD89A565FEFF}]
      Report invalid mode error
      [/cover] */

      /* The requested channel is not configured for the modes
       * supporting CRC calculation? */

      /* We are getting a request for getting the CRC from a channel
       * which does not support the CRC calculation. This is not
       * correct. Raise a DET!
       * DET reason - invalid mode for CRC request */
      Dma_lReportError( DMA_SID_GETCRCVALUE, DMA_E_CRC_NOT_SUPPORTED );
    }
    else
    #endif
    {
      if(MODULE_DMA.TSR[ChannelId].B.CH == 0x00U)
      {
        /* [cover parentID={6B63CA49-649A-4705-842D-70E7E1BECC80}]
        Is the channel active?
        [/cover] */
        if(MODULE_DMA.TSR[ChannelId].B.HLTACK == FALSE)
        {
          /* [cover parentID={3BFBB064-1835-4911-8809-2EC11D308138}]
          Is the channel frozen?
          [/cover] */

          /* The error checks are done. Proceed with the
           * functionality. */
          if( CrcType == DMA_ADDRESS_CRC_TYPE )
          {
            /*[cover parentID={9D0A1D52-DF32-45d9-9C9C-91461CB13BC6}]
             Get the address CRC from the SDCRCRn register
             and store the CRC
             [/cover] */

            /* Request is for address CRC? */

            /* Get the value from the SDCRCRn register and
             * store into the CRC buffer provided */
            CrcValue = MODULE_DMA.CH[ChannelId].SDCRCR.U;
          }
          else
          {
            /*[cover parentID={438F5902-A3A7-4270-916C-F45A5A265C05}]
             Get the data CRC from the RDCRCRn register and
             store the CRC
             [/cover] */

            /* The request is for data CRC */

            /* Get the value from the RDCRCRn register and
             * store into the CRC buffer provided */
            CrcValue = MODULE_DMA.CH[ChannelId].RDCRCR.U;
          }
        }
        #if( (DMA_DEV_ERROR_DETECT == STD_ON) || \
             (DMA_SAFETY_ENABLE    == STD_ON) )
        /* [cover parentID={AB7D5F00-8BF9-4754-9405-F5E62CFB19F7}]
        DET or safty checks enabled
        [/cover] */
        else
        {
          /* [cover parentID={A910147E-A16A-4fff-B8C0-BC24C2843BB6}]
          Report DET or safety error for 'freeze state'
          [/cover] */

          /* Report DET */
          Dma_lReportError( DMA_SID_GETCRCVALUE, DMA_E_FREEZE_STATE );
        }
        #endif
      }
      #if( (DMA_DEV_ERROR_DETECT == STD_ON) || \
           (DMA_SAFETY_ENABLE    == STD_ON) )
      /* [cover parentID={CB897393-FB54-4142-A9E7-01FBA72BF1CE}]
       DET enabled
      [/cover] */
      else
      {
        /* Report DET */
        Dma_lReportError( DMA_SID_GETCRCVALUE,
                          DMA_E_DATA_TRANSFER_IN_PROGRESS );
        /* [cover parentID={DA6CB54C-D2DC-448f-AE83-2813743E4405}]
        Report DET or safety error for 'transfer in progress'
        [/cover] */

      }
      #endif
    }

    SchM_Exit_Dma_ChannelConfigUpdate();
  }

  /* Return the API status */
  return CrcValue;
}


/*******************************************************************************
** Traceability: [cover parentID={416D3361-BC31-4cde-9EA7-888723D1A918}]      **
**                                                                            **
** Syntax : Std_ReturnType Dma_GetCurrentTimeStamp(void)                      **
**                                                                            **
** Description : Service to read the current time stamp in DMA                **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x18                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant                                                     **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  Current time stamp                                      **
**                                                                            **
*******************************************************************************/
uint32 Dma_GetCurrentTimeStamp
(
  void
)
{
  uint32 TimeBuffer = 0;

  #if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
  /* [cover parentID={AB2FC970-4F5B-4716-9968-5ECCC6B790C6}]
  DET or safety checks enabled
  [/cover] */
  /* ID of core used for execution */
  uint32 lCoreId = 0;

  /* Regular DET checks not needed, since there is nothing related to
   * the channel. Only the time stamp register needs to be sent. */

  /* Get the core ID of the core, where we are executing at this moment */
  lCoreId = Mcal_GetCpuIndex();

  if(*(Dma_CoreState[lCoreId]) != DMA_CPUCORE_INIT)
  {
    /* [cover parentID={F44F955F-E4F7-43cc-99DC-789134504E56}]
    Report driver not initialized error
    [/cover] */
    /* [cover parentID={D046B572-8A93-4e66-91E1-2053F555D9C4}]
    Is the DMA driver initialized on current core?
    [/cover] */

    /*Report DET on DriverState error*/
    Dma_lReportError(DMA_SID_GETTIMESTAMP, DMA_E_DRIVER_NOT_INITIALIZED);
  }
  else
  #endif
  {
    /* [cover parentID={86325DDD-1798-4ec9-915D-994DDCCA1229}]
    Get the time value from the TIME register and store it
    into the time stamp buffer provided by the user
    [/cover] */

    /* Get the time value from the 'TIME' register and store it into
     * the time stamp buffer provided by the user */
    TimeBuffer = MODULE_DMA.TIME.U;
  }

  /* Return the 'return status' */
  return TimeBuffer;
}

/*******************************************************************************
** Traceability: [cover parentID={C52995C0-8A3E-4422-BF9C-91023BDF629D}]      **
**                                                                            **
** Syntax : Std_ReturnType Dma_IsChannelInitDone(uint8 ChannelId)             **
**                                                                            **
** Description : Service to read the init status of a channel                 **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x19                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant                                                     **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): ChannelId - The channel id                               **
**                                                                            **
** Return value    :  E_OK      - Channel is initialized                      **
**                    E_NOT_OK  - Channel is not initialized                  **
**                                                                            **
*******************************************************************************/
Std_ReturnType Dma_IsChannelInitDone
(
  const uint8 ChannelId
)
{
  /* Return status of the function */
  Std_ReturnType InitStatus = E_NOT_OK;
  /* [cover parentID={DE3C9AC1-A1FC-4a5a-AB30-E20CBF29692D}]
  Mark the return status as E_NOT_OK
  [/cover] */
  uint32 lCoreId = 0;                 /* ID of core used for execution */

  /* Get the core ID of the core, where we are executing at this moment */
  lCoreId = Mcal_GetCpuIndex();

  #if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
  /* [cover parentID={1A10CD9B-CD4D-4082-B90F-2DF8AF026668}]
  DET or Safety checks enabled
  [/cover] */


  if(*(Dma_CoreState[lCoreId]) != DMA_CPUCORE_INIT)
  {
    /* The driver is not initialized for the core on which we are on! */

    /* [cover parentID={1856C3B6-0BB5-4c95-BBF4-0E99AEAFF37C}]
    Report driver not initialized error
    [/cover] */
    /* [cover parentID={2B44CEFD-C8CC-4dc2-8506-8265300DD192}]
    Is the channel initialized?
    [/cover] */
    /* [cover parentID={32129F70-5E69-44ed-AD69-A03787FC51B2}]
    Is the DMA driver initialized on current core?
    [/cover] */

    /*Report DET on DriverState error*/
    Dma_lReportError(DMA_SID_ISCHINITDONE, DMA_E_DRIVER_NOT_INITIALIZED);
  }
  else if(ChannelId >= (uint8)DMA_MAX_NUM_OF_CHANNELS)
  {
    /* The channel number is exceeding the max channels that the driver
    * is actually built for! */

    /* [cover parentID={455CC781-1945-413f-9D16-BF8065CB22E2}]
    Report invalid channel ID error
    [/cover] */
    /* [cover parentID={328F85CA-FBC6-469a-AB22-C65AAA83FC56}]
    Is the channel number in valid range for
    maximum number of allowed DMA channels?
    [/cover] */

    /*Report DET on Channel ID error*/
    Dma_lReportError(DMA_SID_ISCHINITDONE, DMA_E_CHANNEL_INVALID_ID);
  }
  else if(Dma_kConfigPtr->Dma_ChannelMaps[ChannelId].
          Dma_ChannelConfIndexMap == DMA_CHANNEL_MAP_RESET_VALUE)
  {
    /* [cover parentID={9496302D-E3B3-4fa9-88A2-134DFFDC64C0}]
    Does the configuration exist for this channel?
    [/cover] */
    /* [cover parentID={7B07793F-3CF0-482a-8722-88687CE764A7}]
    Report invalid channel id
    [/cover] */

    /* We have searched the entire root configuration, This
     * channel configuration doesn't exist. This is an error
     * and has to be reported via a DET */
    Dma_lReportError( DMA_SID_ISCHINITDONE, DMA_E_CHANNEL_INVALID_ID );
  }
  #if( (DMA_MULTICORE_ERROR_DETECT == STD_ON) || \
       (DMA_SAFETY_ENABLE          == STD_ON) )
  else if(Dma_kConfigPtr->
          Dma_ChannelMaps[ChannelId].Dma_ChannelCoreMap != lCoreId)
  { /* Is the requested channel not assigned to this core? */

    /* There is an issue with the way the channels are handled from the
    * caller */

    /* [cover parentID={CF7225D8-4D1B-451f-ABE9-A70892ED3343}]
    Report core mismatch error
    [/cover] */
    /* [cover parentID={1EC7AF9F-45BA-4da0-884A-B7B42FF79BC8}]
    Is the requested channel assigned to current core?
    [/cover] */

    /* Report a DET! */
    Dma_lReportMulticoreError( DMA_SID_ISCHINITDONE,
                               DMA_E_CORE_CHANNEL_MISMATCH );
  }
  #endif
  else
  #endif
  {
    /* Null pointer check not needed here as the det checks cover
     * the possibility */
    if(DMA_GET_CH_INITSTATE(ChannelId, lCoreId) == DMA_DRIVER_CHINIT )
    {
      /* [cover parentID={DBF8C156-AB61-4438-A576-0A8ECF9ECBCC}]
      Get the channel initialization status of the channel
      [/cover] */
      /* [cover parentID={34A49C96-9939-4773-BBDA-1E282614FEF5}]
      Mark the return status as E_OK
      [/cover] */
      InitStatus = E_OK;
    }
  }

  return InitStatus;
}

/*******************************************************************************
** Traceability: [cover parentID={D3BC52C0-DD4A-4382-8AD3-6B6CA4771E85}]      **
**                                                                            **
** Syntax : void Dma_MEStatusClear(Dma_MoveEngineListType                     **
**                                 const MoveEngineNumber)                    **
**                                                                            **
** Description : Service to Clear all MoveEngine events                       **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x15                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant                                                     **
**                                                                            **
** Parameters (in) :  MoveEngineNumber - The move engine number               **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :   E_OK     - The clearing was successful                 **
**                     E_NOT_OK - The clearing was not successful             **
**                                                                            **
*******************************************************************************/
Std_ReturnType Dma_MEStatusClear
(
  Dma_MoveEngineListType const MoveEngineNumber
)
{
  Std_ReturnType lMeClearStatus = E_NOT_OK;
  #if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
  /* DET or safety check enabled */
  /* Get the core ID of the core, where we are executing at this moment */
  uint32 lCoreId = Mcal_GetCpuIndex();  
  /* [cover parentID={D8CFB605-D5C4-4784-ADF8-3E20C56ADC4A}]
     Is the DMA driver not initialized on current core?
     [/cover] */
  if(*(Dma_CoreState[lCoreId]) != DMA_CPUCORE_INIT)
  { 
    /*Report DET on Invalid initialized*/
    Dma_lReportError(DMA_SID_MESTATUSCLEAR, DMA_E_DRIVER_NOT_INITIALIZED); 
  }
  else
  #endif
  {
    #if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
    /* [cover parentID={1B901EE5-6E16-4889-8C99-F2DD65B2570D}]
    DET or safety check enabled
    [/cover] */
    if( (MoveEngineNumber != DMA_ME_0) && (MoveEngineNumber != DMA_ME_1) &&
        (MoveEngineNumber != DMA_ME_ALL) )
    {
      /* [cover parentID={0ED61198-7ED7-44c9-8206-E678D4E0BDA8}]
      Is the specified move engine ID invalid?
      [/cover] */
      /* [cover parentID={E3434DBD-6ABE-4e17-9D73-2E4D15CD7009}]
      Report Invalid ME ID error
      [/cover] */
      /*Report DET on Invalid ME ID error*/
      Dma_lReportError(DMA_SID_MESTATUSCLEAR, DMA_E_MOVE_ENGINE_INVALID_ID);
    }
    else
    #endif
    {
      /* [cover parentID={F3748062-5671-4992-9A75-E95E5C63E339}]
      Critical Section - ChannelConfigUpdate
      [/cover] */
      /* [cover parentID={4B1DD145-3040-477d-BC13-2509BC2D2FBE}]
      Enter the critical section, by calling
      'SchM_Enter_Dma_ChannelConfigUpdate'
      [/cover] */
      SchM_Enter_Dma_ChannelConfigUpdate();

      if(MoveEngineNumber == DMA_ME_0)
      {
        /* [cover parentID={C4598CC6-E2C2-4e77-9FAD-3FDBF87CE987}]
        Does the specified move engine ID correspond to move engine 0?
        [/cover] */
        /* [cover parentID={57913861-AC40-476e-A11A-E67FEADE586A}]
        Clear the ME0 errors using CLRE register
        [/cover] */
        DMA_SFR_RUNTIME_WRITE32(&(DMA_ME0_CLRE.U), DMA_CLEAR_ERROR_MASK);

        lMeClearStatus = E_OK;
      }
      else if(MoveEngineNumber == DMA_ME_1)
      {
        /* [cover parentID={692D6297-90AE-401f-BAEF-558203F8CF5F}]
        Does the specified move engine ID correspond to move engine 1?
        [/cover] */
        /* [cover parentID={70CF4F47-FED6-4415-9A2C-027C10D1F168}]
        Clear the ME1 errors using CLRE register
        [/cover] */
        DMA_SFR_RUNTIME_WRITE32(&(DMA_ME1_CLRE.U), DMA_CLEAR_ERROR_MASK);

        lMeClearStatus = E_OK;
      }
      else
      {
        /* [cover parentID={C9461614-AE83-4784-9CC6-49BF5473971D}]
        Clear both the ME errors using CLRE register
        [/cover] */
        DMA_SFR_RUNTIME_WRITE32(&(DMA_ME0_CLRE.U), DMA_CLEAR_ERROR_MASK);
        DMA_SFR_RUNTIME_WRITE32(&(DMA_ME1_CLRE.U), DMA_CLEAR_ERROR_MASK);

        lMeClearStatus = E_OK;
      }

      /* [cover parentID={78FB67F7-E566-404d-9084-23C5B85064CD}]
      Exit the critical section, by calling
      'SchM_Exit_Dma_ChannelConfigUpdate'
      [/cover] */
      SchM_Exit_Dma_ChannelConfigUpdate();
    }  
  }    
  return lMeClearStatus;
}

/* CYCLOMATIC_Dma_ChInterruptHandler_JUSTIFICATION: This API identifies the 
cause of all kind of interrupt and clears the status, which causes extra checks 
in the code. */
/*******************************************************************************
** Traceability: [cover parentID={8E4D2E8B-5A55-4e24-B063-EB3C71DFBD71}]      **
**                                                                            **
** Syntax : void Dma_ChInterruptHandler (const uint8 Channel)                 **
**                                                                            **
** Description : This is the interrupt service routine of a channel interrupt **
**               invoked by the interrupt frame (installed in the interrupt   **
**               vector table).                                               **
**               It identifies the cause of the interrupt, clears the status  **
**               and invokes registered notification routines                 **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x1A                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  Channel - DMA channel ID(0-127)                         **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
void Dma_ChInterruptHandler
(
  const uint8 Channel
)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: Union based type definition for SFR
     access. Variable of SFR type defined for writing into register.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_DMA_CH_CHCSR lChcsrReg;
  uint32 lEvent   = (uint32)DMA_EVENT_NONE;
  uint32 lCoreId  = 0;     /* ID of core used for execution */
  uint8  lChIndex = 0U;

  /* Get the core ID of the core, where we are executing at this moment */
  lCoreId = Mcal_GetCpuIndex();

  /* [cover parentID={149220B8-1575-45fb-8A95-0608A4BBD4D2}]
  Does this channel belong to this core and the config pointer is not NULL?
  [/cover] */

  /* Was the configuration of this channel found in this core? */
  if( (Dma_kConfigPtr != NULL_PTR) &&
      (Channel < (uint8)DMA_MAX_NUM_OF_CHANNELS) )
  {
    if((Dma_kConfigPtr->
        Dma_ChannelMaps[Channel].Dma_ChannelCoreMap == lCoreId) &&
        (Dma_kConfigPtr->DmaCoreConfigPtr[lCoreId] != NULL_PTR) )
    {
      /* [cover parentID={7B998A62-A927-4b23-95D8-811ACA16415B}]
      Is the core config pointer NULL?
      [/cover] */
      
      /* Keep the local copy of register value */
      lChcsrReg.U = MODULE_DMA.CH[Channel].CHCSR.U;
                    
      /* Clear Wrap Buffer and Channel Interrupt flag for DMA Channel */
      DMA_SFR_RUNTIME_WRITE32(&(MODULE_DMA.CH[Channel].CHCSR.U),
      (lChcsrReg.U|(((uint32)DMA_BIT_SET << IFX_DMA_CH_CHCSR_CICH_OFF)|
      ((uint32)DMA_BIT_SET << IFX_DMA_CH_CHCSR_CWRP_OFF))));
      
      /* Find the index at which this channel is present in the
       * configuration */
      lChIndex = Dma_kConfigPtr->
              Dma_ChannelMaps[Channel].Dma_ChannelConfIndexMap;
      /* [cover parentID={DEFFEE08-A59F-4aeb-B36C-63D73E5F893C}]
      Get the config index
      [/cover] */

      /* Proceed, if we were indeed able to find a valid
       * channel here */
      if(lChIndex != DMA_CHANNEL_MAP_RESET_VALUE)
      {
        /* [cover parentID={3A7B7CC6-2CCA-4345-BA00-23724790F8DC}]
        Is the index valid?
        [/cover] */

        /* We are able to identify the channel configuration set */
        const Dma_ChannelNotificationPtrType lChNotify =
                Dma_kConfigPtr->DmaCoreConfigPtr[lCoreId]->
                DmaChConfigPtr[lChIndex].DmaChNotifPtr;

        if(lChNotify != NULL_PTR)
        {
          /*[cover parentID={92375189-5893-429c-AE93-9CED0488E183}]
           Is the notification pointer NULL?
           [/cover] */

          /*[cover parentID={332E21C2-03C8-465c-861C-E533C4D03301}]
            Has a transfer interrupt or Pattern detection occured?
            [/cover] */ 
          /* Check for channel transfer Interrupt or Pattern detection */
          if((lChcsrReg.B.ICH == DMA_BIT_SET) || (lChcsrReg.B.IPM == DMA_BIT_SET))
          {                      
            /*[cover parentID={C07082A9-A1A4-4645-8E39-D6E5031344B1}]
                 Has a transfer interrupt
                 occured?
              [/cover] */
                
            if(lChcsrReg.B.ICH == DMA_BIT_SET)
            {
              /* Keep the information of the event */
              /*[cover parentID={989BA53E-21D0-41c2-94EB-1488139A1410}]
                Mark as transfer interrupt 
                [/cover] */
              lEvent |= (uint32)DMA_EVENT_CH_TRANSFER_COMPLETE;
            }
            #if (DMA_SETPATTERN_API == STD_ON)
            /* Check for Pattern detection */
            /*[cover parentID={48F9C17A-BFA4-4496-8D3E-3756E820A3DE}]
                 Has a Pattern detection
                 occured?
              [/cover] */
            if(lChcsrReg.B.IPM == DMA_BIT_SET)
            {
              /*DET or Safety Enabled */
              #if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )              
              /*[cover parentID={957A9D67-B74D-44cb-89CB-7A9CC781E702}]
                Is channel for pattern is invalid 
                [/cover] */           
              if((Dma_kConfigPtr->DmaPatternCh[0] != Channel)&&(Dma_kConfigPtr->DmaPatternCh[1] != Channel))
              {    
                /*Report DET or safety error for 'invalid channel' */
                Dma_lReportError( DMA_SID_CHINTERRUPTHANDLER, DMA_E_CH_INT_PLAUSIBILITY ); 
              }
              else
              #endif
              {
                /* Keep the information of the event */
                lEvent |= (uint32)DMA_EVENT_CH_PATTERN_DETECTION;     
              }                        
            }
            #endif       
          }
          /* Check Wrap buffer interrupt */
          if(lChcsrReg.B.WRPD == DMA_BIT_SET)
          {
            /* [cover parentID={0C9157AD-A241-4855-BB03-6A088E62520F}]
                  Has a wrap destination
                  interrupt occured?
                  [/cover] */
            /* [cover parentID={5A13076F-9021-45a2-B763-FB5B34421A14}]
                  Mark as Wrap Dest interrupt
                  [/cover] */
            /* [cover parentID={0C9157AD-A241-4855-BB03-6A088E62520F}]
                  Has a wrap destination
                  interrupt occured?
                  [/cover] */

            /* Keep the information of the event */
            lEvent |= (uint32)DMA_EVENT_CH_BUFFER_WRAP_DEST;
          }
          if(lChcsrReg.B.WRPS == DMA_BIT_SET)
          {
            /* [cover parentID={98EE47B1-A53A-4dcc-BE5F-B41042A42416}]
                  Has a wrap source
                  interrupt occured?
                  [/cover] */
            /* [cover parentID={DBD59C8C-8C6B-4d3e-8F02-2B63CF077217}]
                  Mark as Wrap Source interrupt
                  [/cover] */
            /* [cover parentID={98EE47B1-A53A-4dcc-BE5F-B41042A42416}]
                  Has a wrap source
                  interrupt occured?
                  [/cover] */

            /* Keep the information of the event */
            lEvent |= (uint32)DMA_EVENT_CH_BUFFER_WRAP_SOURCE;
          }
          if(lEvent == (uint32)DMA_EVENT_NONE)
          {
            /* [cover parentID={059F3E7F-33AE-4898-9C6B-70930C8D53FF}]
                  None of the above Event?
                  [/cover] */            
            /*[cover parentID={841622AC-B7F8-4fc1-9B0F-BEDC661C78A1}]
                 Mark as 'Unknown Source' of interrupt
                 [/cover] */

            /* Well, none of the status flags are set! This can
             * also be due to the flags getting cleared during
             * the usage of linked list. So, let's inform the
             * caller that an event has occurred. Unfortunately,
             * we don't have a reason to pass on. So, it would
             * be an unknown event. */
            lEvent = (uint32)DMA_EVENT_CH_UNKNOWN_EVENT;
          }
          /* [cover parentID={392799CA-A768-4f77-BE46-BA5D3A4CDDB5}]
            Call the error notification function
            [/cover] */
          /* Call the notification function configured by
           * the user */
          lChNotify(Channel, lEvent);
        }
      }
    }
  }
}



/*******************************************************************************
** Traceability: [cover parentID={2E3242CD-A09B-42e3-BB7C-4A12F2DED94C}]      **
**                                                                            **
** Syntax : void Dma_MEInterruptDispatcher (void)                             **
**                                                                            **
** Description : This is the Level-2 interrupt dispatcher meant to be called  **
**                by the interrupt service routine (installed in the          **
**                interrupt vector table). The handler identifies the ME      **
**                responsible for the error interrupt and calls the interrupt **
**                handler                                                     **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  None                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
void Dma_MEInterruptDispatcher
(
  void
)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: Union based type definition for SFR
     access. Variable of SFR type defined for writing into register.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_DMA_ME_ERRSR ME0_ErrorStatus, ME1_ErrorStatus;
  uint32 lTsrReg;
  uint32 lEtrlStatus = 0;
  uint8 lTrlIndex = 0;
  uint8 lChannelPos = 0;
  uint8 lChannelFound = 0;
  uint8 lChannelId = 0;

  if( Dma_kConfigPtr != NULL_PTR )
  { 
    ME0_ErrorStatus.U = DMA_ME0_ERRSR.U;
    ME1_ErrorStatus.U = DMA_ME1_ERRSR.U;
    /* [cover parentID={95BAD878-372C-4720-9302-DECDADB73643}]
    Store locally the ME errors of ME0
    [/cover] */
    /* [cover parentID={E2C98E01-93D8-4450-9959-A9DD075C28F8}]
    Store locally the ME errors of ME1
    [/cover] */
    /* [cover parentID={1C98CECC-4293-43fd-B8EE-E638A1FF2DBC}]
    Is the config pointer null?
    [/cover] */

    /* Check for the ME0 error status */
    if((ME0_ErrorStatus.U & DMA_ERROR_STATUS_MASK) != 0x00U)
    {
      /* [cover parentID={AB30E78B-1389-4981-AFBB-62159682ED0F}]
      Call interrupt handler for ME0
      [/cover] */
      /* [cover parentID={E6908C9B-D843-4547-96E0-3CE08CFD43F5}]
      Are there any errors
      on Move Engine 1?
      [/cover] */

      /* Error handling for the  */
      Dma_lMEInterruptHandler(DMA_MOVE_ENGINE_0, ME0_ErrorStatus.U);
    }

    /* Check for the ME1 error status */
    if((ME1_ErrorStatus.U & DMA_ERROR_STATUS_MASK) != 0x00U)
    {
      /* [cover parentID={49D865A8-FB05-49c0-AB11-2BB532A37AE0}]
      Call interrupt handler for ME1
      [/cover] */
      /* [cover parentID={ECFE86F7-0CC0-492d-93CB-8213BB473A61}]
      Are there any errors
      on Move Engine 0?
      [/cover] */

      Dma_lMEInterruptHandler(DMA_MOVE_ENGINE_1, ME1_ErrorStatus.U);
    }

    while( (lTrlIndex < DMA_MAX_TRLCHANNELS) && (lChannelFound == (uint8)0) )
    {
      lEtrlStatus = Dma_kConfigPtr->DmaChTrlEnabled[lTrlIndex];
      while( (lEtrlStatus != (uint8)0) && (lChannelFound == (uint8)0) )
      {
        lChannelPos = DMA_GET_SETBIT_POS(lEtrlStatus);
        lEtrlStatus &= (~((uint32)0x01 << lChannelPos));
        lChannelId = lChannelPos + (DMA_TRL_WORD_OFFSET * lTrlIndex);
        lTsrReg = MODULE_DMA.TSR[lChannelId].U;

        if( (lTsrReg & DMA_TSR_ETRL_TRL_MASK) == DMA_TSR_ETRL_TRL_MASK )
        {
          /* [cover parentID={086DFEFC-978D-4151-BC4E-47703749CF20}]
          Was the ETRL bit for the channel enabled?
          [/cover] */
          /* [cover parentID={992C47F2-25A3-42ac-9DFB-9CA151AD3D6A}]
          Are there any TRL errors in any of the DMA channels?
          [/cover] */
          lChannelFound = 1;
          Dma_lMEInterruptHandler(lChannelId, 0);
          /* [cover parentID={9D8C7272-C90E-4597-94CB-C8D0F0399CC9}]
          Call interrupt handler for channel TRL event
          [/cover] */
        }
      }
      lTrlIndex++;
    }
  }
}

#if (DMA_SETPATTERN_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={D49BA544-B0BD-4baf-A2B7-1BCCBD01C120}]      **
**                                                                            **
** Syntax : Std_ReturnType  Dma_SetPattern (const uint8 Channel,              **
**                                       const uint32 Pattern )               **
**                                                                            **
** Description : This API allows the user to set or change the pattern which  **
**               should be used for the pattern detection/conditional linked  **
**               list feature.                                                **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x19                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  reentrant                                                     **
**                                                                            **
** Parameters (in) : Channel - Channel number for which the pattern is        **
**                             intended.                                      **
**                   Pattern   - The specific pattern which is to be set to   **
**                               the PRR register.                            **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  E_OK - Pattern was programmed into the register         **
**                           successfully                                     **
**                    E_NOT_OK - Pattern was not programmed into the register,** 
**                               if error detected in Dma_lDetCheck or        **
**                               Channel not configured for pattern or        **
**                               Channel is in progress                       **
**                                                                            **
*******************************************************************************/
Std_ReturnType  Dma_SetPattern (const uint8 Channel, const uint32 Pattern ) 
{
  Std_ReturnType lStatus;
  uint32 lTsrRead; 
  /* DET or safety checks enabled */
  #if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
  /*Check DET for channel */
  lStatus = (Std_ReturnType)(Dma_lDetCheck( DMA_SID_SETPATTERN, Channel ));
  /* If there is no DET error for channel */
  /* [cover parentID={C21B3FC0-55EC-4d58-B2E8-0A88C9E3ADF0}]
     [/cover] */  
  if(lStatus == E_OK) 
  #endif
  {
    lTsrRead = MODULE_DMA.TSR[Channel].B.CH ;
    /* Check if the channel is active */
    /* [cover parentID={0EDEC234-BA6F-465f-B231-E6B7673C6A8C}]
       [/cover] */
    if( lTsrRead == 0x00U )
    {
      /*[cover parentID={0FB09258-B040-4175-8377-F802ADFBA0C0}]
        [/cover] */
      /*Is channel for pattern0 is valid */
      if(Dma_kConfigPtr->DmaPatternCh[0] == Channel)
      {      
        /* write pattern on PRR0 */
        DMA_SFR_RUNTIME_WRITE32(&(MODULE_DMA.PRR0.U),Pattern);
        /* update status as E_OK */
        lStatus = E_OK;
      }
      /* [cover parentID={56466C65-1580-4053-8DD4-F7F63AB06770}]
      [/cover] */    
      /*Is channel for pattern1 is valid */    
      else if(Dma_kConfigPtr->DmaPatternCh[1] == Channel)
      {     
        /* write pattern on PRR1 */
        DMA_SFR_RUNTIME_WRITE32(&(MODULE_DMA.PRR1.U),Pattern);
        /* update status as E_OK */
        lStatus = E_OK;
      } 
      else /* for invalid pattern */
      {
        #if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
        /* Raise a DET for this error! */
        Dma_lReportError( DMA_SID_SETPATTERN, DMA_E_CH_PATTERN_INVALID_REQ );
        #endif 
        /* upadting status as E_NOT_OK */
        lStatus = E_NOT_OK;
      }     
    }
    else
    {
      #if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE    == STD_ON) )
      /* Report DET or safety error for 'Transfer in progress'*/
      Dma_lReportError( DMA_SID_SETPATTERN,DMA_E_DATA_TRANSFER_IN_PROGRESS );
      #endif
      /* upadting status as E_NOT_OK */
      lStatus = E_NOT_OK;
    }       
  }  
  return lStatus;  
}
#endif

/*******************************************************************************
** Traceability: [cover parentID={DE44DEB7-DEFE-41ca-BA95-3C2A575C76EB}]      **
**                                                                            **
** Syntax : void Dma_lMEInterruptHandler (const uint8 MoveEngine,             **
**                                       const uint32 lErrorData )            **
**                                                                            **
** Description : Local function for handling Move engine error interrupts     **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  None                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : lErrorSource - The ME number or channel number of error  **
**                   lErrorData   - Reason for the error                      **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
static void Dma_lMEInterruptHandler
(
  const uint8  lErrorSource,
  const uint32 lErrorData
)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: Union based type definition for SFR
   access. Variable of SFR type defined for writing into register.
   No side effects foreseen by violating this MISRA rule.*/
  volatile Ifx_DMA_ME_CLRE *lMeClrReg = NULL_PTR;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: Union based type definition for SFR
   access. Variable of SFR type defined for writing into register.
   No side effects foreseen by violating this MISRA rule.*/
  Ifx_DMA_ME_ERRSR lMeErrReg;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: Union based type definition for SFR
   access. Variable of SFR type defined for writing into register.
   No side effects foreseen by violating this MISRA rule.*/
  Ifx_DMA_TSR lTsrReg;
  uint32 lSrcReg;
  uint8 lChannelId;
  uint32 lMeErrEvent = (uint32)DMA_EVENT_NONE;
  uint32 lCurrentCoreId = 0;         /* ID of core used for execution */
  uint32 lChannelCoreOwnerId = 0;    /* ID of core, of the channel */
  uint8 lChIndex = 0;

  lMeErrReg.U = lErrorData;

  /* Get the core ID of the core, where we are executing at this moment */
  lCurrentCoreId = Mcal_GetCpuIndex();
  /* [cover parentID={C0B0550A-BAE6-4375-933E-4D719758E713}]
  Get the core id on which this function is invoked
  [/cover] */

  /* Error source is a channel? */
  if( (lErrorSource != DMA_MOVE_ENGINE_0) && (lErrorSource != DMA_MOVE_ENGINE_1) )
  {
    /* [cover parentID={6C43A0A5-9E8E-408b-A3A2-599A4B12F99D}]
    Is the error from a channel?
    [/cover] */

    /* [cover parentID={13F506C8-93AB-49a4-88B2-A9133BACED24}]
    Store the channel id of error source
    [/cover] */
    /* [cover parentID={BA2F2CB2-2318-4115-8D13-35EDE71C38D3}]
    Store the channel index
    [/cover] */

    /* Store the channel id received */
    lChannelId = lErrorSource;
  }
  else
  {
    if(lErrorSource == DMA_MOVE_ENGINE_0)
    {
      /* [cover parentID={B6D81414-B85F-4693-9DEC-E61385A41E27}]
      Is the error source ME0?
      [/cover] */

      /* [cover parentID={60BE584C-DA25-4645-BCC6-63BCD5540E44}]
      Store the error source as ME0
      [/cover] */

      lMeClrReg = &(DMA_ME0_CLRE);
    }
    else /* DMA_MOVE_ENGINE_1 */
    {
      /* [cover parentID={7C405180-46D8-4556-9E1B-6BF5D8D8B22F}]
      Is the error source ME1?
      [/cover] */

      /* [cover parentID={4E8A4C20-F4DE-4d29-89E5-B32386CBA758}]
      Store the error source as ME1
      [/cover] */

      lMeClrReg = &(DMA_ME1_CLRE);
    }

    /* Get the channel ID for for which this error has occurred */
    lChannelId = lMeErrReg.B.LEC;
  }

  /* Get the core id, on which the channel is authorized to run */
  lChannelCoreOwnerId = Dma_kConfigPtr->
          Dma_ChannelMaps[lChannelId].Dma_ChannelCoreMap;

  /* Do they match? Are we on the right core or we need to pass the info
   * to another core? */
  if(lCurrentCoreId != lChannelCoreOwnerId)
  {
    /* [cover parentID={F9FF5070-9044-4884-8E31-E75F1CEB9D87}]
    Is the current core the
    required one for this channel?
    [/cover] */

    /* No. There is a mismatch. This means that the execution
     * has to happen on another core. We need to trigger
     * the handling via a GPSR. */

    lSrcReg = SRC_GPSR_GPSR0_SR0.U;

    lSrcReg &= (~((uint32)IFX_SRC_SRCR_TOS_MSK << IFX_SRC_SRCR_TOS_OFF));

    /* Update the TOS, SRE bit for the particular interrupt */
    lSrcReg |= ( Dma_CoreTosMap[lChannelCoreOwnerId] |
                 ((uint32)IFX_SRC_SRCR_SETR_MSK << IFX_SRC_SRCR_SETR_OFF) |
                 ((uint32)IFX_SRC_SRCR_SRE_MSK  << IFX_SRC_SRCR_SRE_OFF ) );

    /* [cover parentID={BE05E662-D33E-44fb-A8A3-354142F491C9}]
    Trigger the GPSR
    [/cover] */

    /* Write to the register */
    DMA_SFR_RUNTIME_WRITE32(&(SRC_GPSR_GPSR0_SR0.U),lSrcReg);

  }
  else
  {
    /* Yes. They match. So, we proceed for the execution
     * of the handler */
    if(Dma_kConfigPtr->
       DmaCoreConfigPtr[lChannelCoreOwnerId] != NULL_PTR)
    {
      /* [cover parentID={21FAE7B1-FCA4-4b73-B830-F84F5482A7AC}]
      Is the core config pointer NULL?
      [/cover] */

      /* Find the index at which this channel is present in the
       * configuration */
      lChIndex = Dma_kConfigPtr->
              Dma_ChannelMaps[lChannelId].Dma_ChannelConfIndexMap;

      /* Proceed, if we were indeed able to find a valid
       * channel here */
      if(lChIndex != DMA_CHANNEL_MAP_RESET_VALUE)
      {
        /* Get the notification function, from the configuration */
          const Dma_MoveEngineErrorNotificationPtrType lMeNotify  =
                     Dma_kConfigPtr->
                     DmaCoreConfigPtr[lChannelCoreOwnerId]->
                     DmaChConfigPtr[lChIndex].DmaMEErrorNotifPtr;

        /* If we dont have an interrupt function configured by the
         * user, it does not make any sense to clear the
         * interrupt flags. */
        if(lMeNotify != NULL_PTR)
        {
          /* [cover parentID={E0D7258F-17D1-420a-9AF9-4C497DA225A8}]
            Is the notification
            function pointer NULL?
            [/cover] */

          /* [cover parentID={5F5039BF-DD90-42d5-8C11-95B5959469CF}]
            Is the notification pointer null?
            [/cover] */

          /* Error source is ME? */
          if( (lErrorSource == DMA_MOVE_ENGINE_0) ||
              (lErrorSource == DMA_MOVE_ENGINE_1) )
          {
            /* [cover parentID={DE94A406-8B65-4584-BE90-832D14273175}]
                  Is the error source an ME?
                  [/cover] */
            /* MISRA2012_RULE_1_3_JUSTIFICATION: Local function Dma_lEvaluateMEError
               with address of variable lMeErrReg has been created for 
               maintainability and readability of the code, no address manipulation 
               has been performed. The auto variable lMeErrReg is only in read only 
               mode in the local called function. Hence, it is not an issue. 
            */
            lMeErrEvent = Dma_lEvaluateMEError(&lMeErrReg);

            /* Clear the ME errors */
            DMA_SFR_RUNTIME_WRITE32(&(lMeClrReg->U),DMA_CLEAR_ERROR_MASK);
          }
          else
          {
            if(MODULE_DMA.TSR[lChannelId].B.TRL == DMA_BIT_SET)
            {
              /* [cover parentID={054B1832-6CB8-4947-A256-F545B194B9B3}]
                        Is there a TRL error?
                        [/cover] */
              /* [cover parentID={5E421D60-DF77-43f3-8217-97CDDE591204}]
                        Mark the event cause as 'TRL Error'
                        [/cover] */
              lTsrReg.U = MODULE_DMA.TSR[lChannelId].U;
              lTsrReg.B.CTL = DMA_BIT_SET;
              DMA_SFR_RUNTIME_WRITE32(&( MODULE_DMA.TSR[lChannelId].U),lTsrReg.U);
              lMeErrEvent |= (uint32)DMA_EVENT_CH_TRL_ERROR;
            }
          }
          if (lMeErrEvent != (uint32)DMA_EVENT_NONE)
          {
            /* Now that we have found all the reasons behind this
             * interrupt, we can call the notification function
             * configured by the user. */
            /* [cover parentID={5E8D4BE9-8849-4f21-B706-2261D1367C79}]
               Call the error notification function
               [/cover] */         
            lMeNotify(lChannelId, lMeErrEvent);
          }
        }
      }
    }
  }
}

#if(DMA_INITCHECK_API == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={9DEE7D00-F286-4c3d-9A03-A4051B68256E}] **
**                                                                            **
** Syntax           : Std_ReturnType Dma_InitCheck (const Dma_ConfigType*     **
**                    const ConfigPtr)                                        **
**                                                                            **
** Description      : This API can be used to check the whether the           **
**                    initialization happened correctly for the DMA driver.   **
**                    The basic idea is to check whether the variables        **
**                    and the SFRs which were initialized are holding the     **
**                    same values that they were initialized with.            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x16                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Re-entrant                                          **
**                                                                            **
** Parameters(in)   : ConfigPtr - Pointer to the DMA configuration for        **
**                                  initialization                            **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK - Operation successfully performed                 **
**                    E_NOT_OK - Operation failed                             **
**                                                                            **
*******************************************************************************/
Std_ReturnType Dma_InitCheck
(
  const Dma_ConfigType* const ConfigPtr
)
{
  Std_ReturnType lRetVal = E_NOT_OK;  /* Return value of the API */
  const Dma_ChConfigType *lChannelCfgPtr; /* Dma channel configuration */
  uint32 lCoreId = 0;                 /* ID of core used for execution */
  uint32 lCheckerResult = 0;          /* Result of the comparisons */
  uint32 lSfrValue = 0;               /* Value read from SFR */
  uint32 lConfiguredValue = 0;        /* Value in the configuration */
  uint8  lLoopIndex = 0;              /* Loop variable */
  uint8  lDmaChId = 0U;    /* Dma channel ID of the channel configuration */
  /* MISRA2012_RULE_19_2_JUSTIFICATION: Union based type definition for SFR
     access. Variable of SFR type defined for writing into register.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_DMA_CLC  lClcEnable;
  uint8 chState;


  /* Get the core ID of the core, where we are executing at this moment */
  lCoreId = Mcal_GetCpuIndex();

  lClcEnable.U = MODULE_DMA.CLC.U;

  /* We need to check somethings before we go ahead.
   * 1. Is the config pointer provided to the function a null pointer?
   * 2. Is the config pointer maintained by the driver different from
   *    the one provided to this function?
   * 3. Is the master core not initialized?
   * 4. Is the current core not initialized?
   * 5. Is the DMA clock enabled?
   * If we have a problem with any of these, there is no point in going
   * further. */
  if( (ConfigPtr != NULL_PTR)                                     &&
      (Dma_kConfigPtr == ConfigPtr)                               &&
      (*(Dma_CoreState[MCAL_MASTER_COREID]) == DMA_CPUCORE_INIT)  &&
      (*(Dma_CoreState[lCoreId]) == DMA_CPUCORE_INIT)             &&
      (lClcEnable.B.DISS == DMA_BIT_CLEAR)                                 )
  {
    /* [cover parentID={D69938BD-7B48-45de-A9AF-A71F5368B06E}]
    Is the config pointer provided to the function a null pointer AND
    is it different from the one maintained by the driver AND
    is the master or current core not initialized AND
    Is the CLC DISS bit zero?
    [/cover] */

    /* Well, everything looks good! Let's proceed. */

    if( MCAL_MASTER_COREID == lCoreId )
    {
      /* [cover parentID={8D0C5CC1-14E7-468c-B461-577D69FC7E01}]
      Is the currrent core master core?
      [/cover] */

      /* We are on the master core. Let's check the registers
       * which are initialized by the master core. */

      /* [cover parentID={740BD27E-085F-4038-B70B-9519643EBD7B}]
      Xor the content of all the four access mode registers against
      their respective configured values
      [/cover] */

      /* Access mode registers */
      lConfiguredValue = ConfigPtr->
              DmaHwResourcePartition.DmaHwResourceMode[0];
      lSfrValue = DMA_MODE0.U;
      lCheckerResult |= lConfiguredValue ^ lSfrValue;

      lConfiguredValue = ConfigPtr->
              DmaHwResourcePartition.DmaHwResourceMode[1];
      lSfrValue = DMA_MODE1.U;
      lCheckerResult |= lConfiguredValue ^ lSfrValue;

      lConfiguredValue = ConfigPtr->
              DmaHwResourcePartition.DmaHwResourceMode[2];
      lSfrValue = DMA_MODE2.U;
      lCheckerResult |= lConfiguredValue ^ lSfrValue;

      lConfiguredValue = ConfigPtr->
              DmaHwResourcePartition.DmaHwResourceMode[3];
      lSfrValue = DMA_MODE3.U;
      lCheckerResult |= lConfiguredValue ^ lSfrValue;

      /* [cover parentID={BEAD8B3B-7EA1-4a1b-A889-7B4E1A27B967}]
      Xor the content of both of the pattern detection registers
      against the reset value of DMA registers
      [/cover] */

      /* Pattern Detection registers */
      lSfrValue = DMA_PRR0.U;
      lCheckerResult |= DMA_REGISTER_RESET_VALUE ^ lSfrValue;

      lSfrValue = DMA_PRR1.U;
      lCheckerResult |= DMA_REGISTER_RESET_VALUE ^ lSfrValue;

      /* [cover parentID={B51A259C-3B7A-4ae7-885F-29ABA46E2F73}]
      Xor the content of both of the error notification registers
      against the respective configured values of DMA move engine errors
      [/cover] */

      /* Error notification registers */
      lConfiguredValue = ConfigPtr->DmaMovEngErr[0];
      lSfrValue = DMA_EER0.U;
      lCheckerResult |= lConfiguredValue ^ lSfrValue;

      lConfiguredValue = ConfigPtr->DmaMovEngErr[1];
      lSfrValue = DMA_EER1.U;
      lCheckerResult |= lConfiguredValue ^ lSfrValue;

      /* Xor the content of both of the ME error status registers
      against the reset value of DMA registers */

      /* ME Error status registers */
      lSfrValue = DMA_ME0_ERRSR.U;
      lCheckerResult |= DMA_REGISTER_RESET_VALUE ^ lSfrValue;

      lSfrValue = DMA_ME1_ERRSR.U;
      lCheckerResult |= DMA_REGISTER_RESET_VALUE ^ lSfrValue;

      /* [cover parentID={D96C48B0-838B-4aab-9C4D-631D2809992A}]
      Xor the content of all of the four access protection registers
      against their respective configured values
      [/cover] */

      /* Access protection registers */
      lConfiguredValue = ConfigPtr->
              DmaHwResourcePartition.DmaHwResourceBusMasterAccess[0];
      lSfrValue = DMA_ACCEN0_ACCENR0.U;
      lCheckerResult |= lConfiguredValue ^ lSfrValue;

      lConfiguredValue = ConfigPtr->
              DmaHwResourcePartition.DmaHwResourceBusMasterAccess[1];

      lSfrValue = DMA_ACCEN1_ACCENR0.U;
      lCheckerResult |= lConfiguredValue ^ lSfrValue;

      lConfiguredValue = ConfigPtr->
              DmaHwResourcePartition.DmaHwResourceBusMasterAccess[2];
      lSfrValue = DMA_ACCEN2_ACCENR0.U;
      lCheckerResult |= lConfiguredValue ^ lSfrValue;

      lConfiguredValue = ConfigPtr->
              DmaHwResourcePartition.DmaHwResourceBusMasterAccess[3];
      lSfrValue = DMA_ACCEN3_ACCENR0.U;
      lCheckerResult |= lConfiguredValue ^ lSfrValue;

    } /* Master core specific stuff ends here */

    if( lCheckerResult == (uint32)0 )
    {
      /* [cover parentID={FA23303B-434D-4049-A9D3-60CBE67F5C1B}]
       * Is the result of all comparison checks okay?
       [/cover] */
      /* There are no errors yet. We can proceed then! */
      if(ConfigPtr->DmaCoreConfigPtr[lCoreId] != NULL_PTR)
      {
        /* [cover parentID={5BF3CDA3-0222-4134-89C0-3B43D004B7E6}]
        Is the config pointer provided to the function for
        current core a null pointer?
        [/cover] */
        for(lLoopIndex = 0;
            lLoopIndex < ConfigPtr->DmaCoreConfigPtr[lCoreId]->
                                    DmaNumberofChConfiguredPerCore;
            lLoopIndex++)
        {
          /* [cover parentID={E0D20F09-C407-4425-A1EA-E31DE320D162}]
          Verify all the channel registers
          [/cover] */

          /* Get the channel's config pointer */
          lChannelCfgPtr = &(ConfigPtr->DmaCoreConfigPtr[lCoreId]->
                                        DmaChConfigPtr[lLoopIndex]);

          /* Get the channel ID */
          lDmaChId = lChannelCfgPtr->DmaChNumber;

          /* Now, everything till now looks fine. Let's see if the
           * channel registers are set correctly. Take the help of
           * the local function 'Dma_lVerifyChannelReg()' to do
           * that! */
          lCheckerResult |= Dma_lVerifyChannelReg( lDmaChId,
                                                   lChannelCfgPtr );

          /* Well, with all that looking good, was the channel
           * marked as 'initialized'? */
          /* Null pointer is not needed as the core config
           * pointer is also not null */
          chState = DMA_GET_CH_INITSTATE(lDmaChId, lCoreId);
          lCheckerResult |=  ((uint32)(chState) ^
                              (uint32)(DMA_DRIVER_CHINIT));
          /* [cover parentID={34577464-2433-41c6-BD59-D14A9B529A8B}]
          Check initialization status of all channels
          configured for current core
          [/cover] */
          /* [cover parentID={4DCA72BF-D6DA-42ef-ABD9-D11CDF3025CF}]
          Verify that the channel is marked as initialized
          [/cover] */

        }
      }

      /* Were there any problems? */
      if( lCheckerResult == (uint32)0 )
      {
        /* [cover parentID={D82DE107-225F-4c30-9089-538E1FB49BCB}]
        Is the result of all comparison checks okay?
        [/cover] */

        /* No problems? All is well! Let's mark the status so as to
         * indicate to the user that we are going good! */
        lRetVal = E_OK;
      }
    }
  }
  return lRetVal;
}

/*******************************************************************************
** Traceability     : [cover parentID={582809E6-9514-412d-B9BD-32A9706F7C42}] **
**                                                                            **
** Syntax           : void Dma_lVerifyChannelReg(const uint8 Channel,         **
**                    const Dma_ChConfigType* const ChannelCfgPtr)            **
**                                                                            **
** Description      : This function is used to verify the SFR values          **
**                    configured in the channel specific registers            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Conditionally Reentrant - This function is re-entrant   **
**                    for different DMA channels                              **
**                                                                            **
** Parameters(in)   : Channel  - DMA channel ID(0-127)                        **
**                    ChCfgPtr - Pointer to channel configuration             **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : The result of the comparison checks                     **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Dma_lVerifyChannelReg
(
  const uint8 Channel,
  const Dma_ChConfigType* const ChCfgPtr
)
{
  /* Local variables */
  uint32 lCheckerResult = 0;
  uint32 RemapAddress;
  #if ((DMA_LINKED_LIST_ENABLE     == STD_ON) || \
       (DMA_DOUBLE_BUFFER_ENABLE   == STD_ON))
  /* MISRA2012_RULE_19_2_JUSTIFICATION: Union based type definition for SFR
     access. Variable of SFR type defined for writing into register.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_DMA_CH_ADICR lAdicr;
  #endif

  uint32 CoreId = Mcal_GetCpuPhysicalId();

  /* The SFR values have to be verified against the configured values
   * provided in the post build configuration data. Each SFR, which
   * should hold a particular value is being cross checked here. */

  /* [cover parentID={2413A49F-AA36-4e24-AA22-70244F771653}]
  Xor the HRR register content against the resource partition configuration
  [/cover] */

  /* HRR register - The resource partition configuration */
  lCheckerResult |= MODULE_DMA.HRR[Channel].U ^
                    ChCfgPtr->DmaChHwPartitionConfig;

  /* [cover parentID={169C8E8D-E27A-4fca-931F-32C250BADE8C}]
  DMA linked-list ON ?
  [/cover] */
  #if (DMA_LINKED_LIST_ENABLE == STD_ON)
  /* [cover parentID={90A144D4-3C8C-4078-81A8-B6A52E422568}]
  Xor the RDCRC and SDCRC register content against configured data CRC
  [/cover] */
  /* RDCRC register - The data CRC  */
  lCheckerResult |= MODULE_DMA.CH[Channel].RDCRCR.U ^
                    (uint32)ChCfgPtr->DmaChTCSPtr->DmaReadDataCrc;

  /* SDCRC register - The address CRC */
  lCheckerResult |= MODULE_DMA.CH[Channel].SDCRCR.U ^
                    (uint32)ChCfgPtr->DmaChTCSPtr->DmaSourceDestAddressCrc;    
  #else
  /* [cover parentID={EB34D50C-D496-44bc-B605-967A9F8B9C0D}]
  Xor the RDCRC and SDCRC register content against reset value CRC
  [/cover] */

  /* RDCRC register - The data CRC  */
  lCheckerResult |= MODULE_DMA.CH[Channel].RDCRCR.U ^
                    DMA_REGISTER_RESET_VALUE;

  /* SDCRC register - The address CRC */
  lCheckerResult |= MODULE_DMA.CH[Channel].SDCRCR.U ^
                    DMA_REGISTER_RESET_VALUE;
                    
  #endif                  
        
  /* SADR register - The source address */

  /* Get the global address, if the address provided is not global */
  /* MISRA2012_RULE_11_4_JUSTIFICATION: The API expects the address to be
   * in uint32 format. So the casting needs to be done. */
  /* MISRA2012_RULE_11_6_JUSTIFICATION: Mcal API expects
   * address as uint32, however in DMA address is pointer */
  RemapAddress = Dma_lGetGlobalAddress( CoreId,\
                   ((uint32)(ChCfgPtr->DmaChTCSPtr->DmaSourceAddress)) );

  /* Verify the configured value */
  lCheckerResult |= MODULE_DMA.CH[Channel].SADR.U ^ RemapAddress;


  /* DADR register - The destination register */

  /* Get the global address, if the address provided is not global */
  /* MISRA2012_RULE_11_4_JUSTIFICATION: The API expects the address to be
   * in uint32 format. So the casting needs to be done. */
  /* MISRA2012_RULE_11_6_JUSTIFICATION: Mcal API expects
   * address as uint32, however in DMA address is pointer */
  RemapAddress = Dma_lGetGlobalAddress( CoreId,\
                    (uint32)ChCfgPtr->DmaChTCSPtr->DmaDestinationAddress);

  /* Verify the configured value */
  lCheckerResult |= MODULE_DMA.CH[Channel].DADR.U ^ RemapAddress;

  /* ADICR register */
  lCheckerResult |= MODULE_DMA.CH[Channel].ADICR.U ^
                    ChCfgPtr->DmaChTCSPtr->DmaAddressInterruptControl;

  /* CHCFGR register */
  lCheckerResult |= MODULE_DMA.CH[Channel].CHCFGR.U ^
                    ChCfgPtr->DmaChTCSPtr->DmaChannelConfig;

  /* SHADR register, if we are in the required mode */
  #if ((DMA_LINKED_LIST_ENABLE     == STD_ON) || \
       (DMA_DOUBLE_BUFFER_ENABLE   == STD_ON))
  /* MISRA2012_RULE_11_4_JUSTIFICATION: The API expects the address to be
   * in uint32 format. So the casting needs to be done. */
  /* MISRA2012_RULE_11_6_JUSTIFICATION: Mcal API expects
   * address as uint32, however in DMA address is pointer */
  RemapAddress = Dma_lGetGlobalAddress( CoreId,\
                     (uint32)ChCfgPtr->DmaChTCSPtr->DmaShadowAddress);

  lAdicr.U = MODULE_DMA.CH[Channel].ADICR.U;
  if( (lAdicr.B.SHCT >  DMA_SHADOW_ADDR_RES2_MASK) &&
      (lAdicr.B.SHCT != DMA_SHADOW_ADDR_RES3_MASK) )
  {
    /* [cover parentID={5D73C574-F32C-4205-81A6-11BE5F254D05}]
    Are we in a mode which
    needs shadow register?
    [/cover] */
    /* [cover parentID={6A2AF29B-0076-4981-B164-AC18306CEEC9}]
    Xor the SHADR register content against global address of
    the configured shadow  address
    [/cover] */

    lCheckerResult |= MODULE_DMA.CH[Channel].SHADR.U ^ RemapAddress;
  }
  #endif

  /* CHCSR register */
  lCheckerResult |= MODULE_DMA.CH[Channel].CHCSR.U ^ DMA_REGISTER_RESET_VALUE;

  /* TSR register */
  lCheckerResult |= MODULE_DMA.TSR[Channel].U ^ ChCfgPtr->DmaTsrConfig;

  /* Return the result */
  return lCheckerResult;
}
#endif


#if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
/* [cover parentID={FC0852F0-67EC-42e2-A84D-88C13AFC0D14}]
DET enabled
[/cover] */
/*******************************************************************************
** Traceability: [cover parentID={A796322A-7D95-4309-B224-955290943DD7}]      **
**                                                                            **
** Syntax : uint32 Dma_lDetCheck(const uint32 ServiceId,                      **
**                                    const uint8 Channel)                    **
**                                                                            **
** Description : Service to detect DET error for a channel                    **
**                                                                            **
**                                                                            **
** Service ID:  NA                                                            **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant                                                     **
**                                                                            **
** Parameters (in) :  ServiceId - Caller function's ID                        **
**                    Channel - DMA channel ID(0-127)                         **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  FALSE - No DET error                                    **
**                    TRUE  - DET errors are present                          **
**                                                                            **
*******************************************************************************/
static uint32 Dma_lDetCheck
(
  const uint8 ServiceId,
  const uint8 Channel
)
{
  uint32 lRetVal;
  uint32 lCoreId = 0;         /* ID of core used for execution */

  /* Get the core ID of the core, where we are executing at this moment */
  lCoreId = Mcal_GetCpuIndex();

  if(*(Dma_CoreState[lCoreId]) != DMA_CPUCORE_INIT)
  {
    /* [cover parentID={A3B08660-3C80-4b72-A30A-C396A04C0768}]
    Is the DMA driver uninitialized?
    [/cover] */

    /* The driver is not initialized for the core on which we are on! */
    lRetVal = TRUE;

    /* [cover parentID={17B96D64-88B7-4a8b-B6D3-50AABD950576}]
    Report error for uninitialized DMA
    [/cover] */

    /*Report DET on DriverState error*/
    Dma_lReportError(ServiceId, DMA_E_DRIVER_NOT_INITIALIZED);
  }
  else if(Channel >= (uint8)DMA_MAX_NUM_OF_CHANNELS)
  {
    /* [cover parentID={1246305E-3DF4-4893-822D-C8E2780638D0}]
    Is the channel number invalid?
    [/cover] */

    /* The channel number is exceeding the max channels that the driver
     * is actually built for! */
    lRetVal = TRUE;

    /* [cover parentID={1A0E6EE9-D131-4f76-A454-79498BB0C53A}]
    Report error for invalid channel
    [/cover] */

    /*Report DET on Channel ID error*/
    Dma_lReportError(ServiceId, DMA_E_CHANNEL_INVALID_ID);
  }
  else if(Dma_kConfigPtr->Dma_ChannelMaps[Channel].
          Dma_ChannelConfIndexMap == DMA_CHANNEL_MAP_RESET_VALUE)
  {
    /* [cover parentID={4570D08A-C9C9-4fe3-863F-B1EA1760B5C4}]
    Does this channel configuration exist?
    [/cover] */
    /* [cover parentID={9AB80AC1-111B-402b-9B12-76AE36507FA1}]
    Report DET or safety error on invalid channel ID
    [/cover] */

    /* This is an invalid channel */
    lRetVal = TRUE;

    /* We have searched the entire root configuration, This
     * channel configuration doesn't exist. This is an error
     * and has to be reported via a DET */
    Dma_lReportError(ServiceId, DMA_E_CHANNEL_INVALID_ID );
  }
  #if( (DMA_MULTICORE_ERROR_DETECT == STD_ON) || \
       (DMA_SAFETY_ENABLE          == STD_ON) )
  /* [cover parentID={BF0CE8BC-31F4-4a8a-A843-DF5BAEDF042A}]
  Multicore enabled
  [/cover] */
  else if(Dma_kConfigPtr->\
          Dma_ChannelMaps[Channel].Dma_ChannelCoreMap != lCoreId)
  { /* Is the requested channel not assigned to this core? */

    /* There is an issue with the way the channels are handled from the
     * caller */
    lRetVal = TRUE;

    /* [cover parentID={E2F9C8FB-4778-410c-B8C0-206C3FF89CBC}]
    Report error for core mismatch
    [/cover] */
    /* [cover parentID={36A1A226-6018-4bcd-BE24-40E8D5E38ED9}]
    Is the channel assigned to this core?
    [/cover] */

    /* Report a DET! */
    Dma_lReportMulticoreError(ServiceId, DMA_E_CORE_CHANNEL_MISMATCH);
  }
  #endif
  else if(DMA_GET_CH_INITSTATE(Channel, lCoreId) != DMA_DRIVER_CHINIT)
  {
    /* Null pointer check not needed since channel core map check is
     * being performed */
    /* [cover parentID={F7CC0964-1F69-4664-8FC3-3FB9F6A9B6CC}]
    Is the requested DMA channel, uninitialized?
    [/cover] */

    /* The channel is not initialized! */
    lRetVal = TRUE;

    /* [cover parentID={68A92536-7047-4886-B424-2656C9C6CE12}]
    Report DET for uninitialized channel
    [/cover] */

    /*Report DET on Channel ID error*/
    Dma_lReportError(ServiceId, DMA_E_CHANNEL_NOT_INITIALIZED);
  }
  else
  {
    lRetVal = FALSE;
  }
  return lRetVal;
}
#endif


/*******************************************************************************
** Traceability: [cover parentID={CD3A7B8A-6AD9-4dab-8AB3-3ED90BF3F618}]      **
**                                                                            **
** Syntax: void Dma_lUpdateDmaReg(const uint8 Channel,                        **
**                                const Dma_ChConfigType* const ChannelCfgPtr)**
**                                                                            **
** Description : Service to update channel TCS register and hardware resource **
**               register.                                                    **
**                                                                            **
** Service ID:  NA                                                            **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Conditionally Reentrant - This function is re-entrant for     **
**              different DMA channels                                        **
**                                                                            **
** Parameters (in) :  Channel - DMA channel ID(0-127)                         **
**                    ChCfgPtr- Pointer to channel configuration              **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
static void Dma_lUpdateChannelReg
(
  const uint8 Channel,
  const Dma_ChConfigType* const ChCfgPtr
)
{
  #if ((DMA_LINKED_LIST_ENABLE     == STD_ON) || \
       (DMA_DOUBLE_BUFFER_ENABLE   == STD_ON))
  /* MISRA2012_RULE_19_2_JUSTIFICATION: Union based type definition for SFR
     access. Variable of SFR type defined for writing into register.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_DMA_CH_ADICR lAdicr;
  #endif
  uint32 RemapAddress;
  uint32 CpuId;

  CpuId = Mcal_GetCpuPhysicalId();

  /* [cover parentID={11DD91FA-7455-4999-A3E8-7A6A0AE673B1}]
  Assign the resource partition for the channel, with safety
   endinit protection
  [/cover] */

  /* Configure Channel Hardware Resource Register */
  /**! *******************************************************
   * RESOURCE PARTITION ALLOCATION
   * *********************************************************/
  /**! HRR register - This register holds the configuration information
   * as to the resource partition to which the channel belongs to */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: Mcal requires the
   * parameter as uint32 const*, but this is a register type  */
  DMA_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(\
          (uint32*)&(MODULE_DMA.HRR[Channel]),\
          ChCfgPtr->DmaChHwPartitionConfig);                

  /**! *******************************************************
   * CRC REGISTERS - RESETTING THE REGISTERS
   * *********************************************************/
  #if (DMA_LINKED_LIST_ENABLE == STD_ON)
  /* Update channel transaction control set registers */
  /* Reset Channel Read Data CRC Register */
  DMA_SFR_INIT_DEINIT_WRITE32(&(MODULE_DMA.CH[Channel].RDCRCR.U),
          (uint32)ChCfgPtr->DmaChTCSPtr->DmaReadDataCrc);
  /* Reset Channel Address CRC Register */
  DMA_SFR_INIT_DEINIT_WRITE32(&(MODULE_DMA.CH[Channel].SDCRCR.U),
          (uint32)ChCfgPtr->DmaChTCSPtr->DmaSourceDestAddressCrc);
  #else
  /* Update channel transaction control set registers */
  /* Reset Channel Read Data CRC Register */
  DMA_SFR_INIT_DEINIT_WRITE32(&(MODULE_DMA.CH[Channel].RDCRCR.U),
                              DMA_REGISTER_RESET_VALUE);
  /* Reset Channel Address CRC Register */
  DMA_SFR_INIT_DEINIT_WRITE32(&(MODULE_DMA.CH[Channel].SDCRCR.U),
                              DMA_REGISTER_RESET_VALUE);
  #endif


  /**! *******************************************************
   * SOURCE ADDRESS CONFIGURATION
   * *********************************************************/
  /* Configure Source address */
  /* MISRA2012_RULE_11_4_JUSTIFICATION: The API expects the address to be
   * in uint32 format. So the casting needs to be done. */
  /* MISRA2012_RULE_11_6_JUSTIFICATION: Mcal API expects
   * address as uint32, however in DMA, address is pointer. */
  RemapAddress = \
          Dma_lGetGlobalAddress(CpuId, \
                   (uint32)ChCfgPtr->DmaChTCSPtr->DmaSourceAddress);
  DMA_SFR_INIT_DEINIT_WRITE32(&(MODULE_DMA.CH[Channel].SADR.U), RemapAddress);

  /**! *******************************************************
   * DESTINATION ADDRESS CONFIGURATION
   * *********************************************************/
  /* Configure destination address */
  /* MISRA2012_RULE_11_4_JUSTIFICATION: The API expects the address to be
   * in uint32 format. So the casting needs to be done. */
  /* MISRA2012_RULE_11_6_JUSTIFICATION: Mcal API expects
   * address as uint32, however in DMA address is pointer */
  RemapAddress = \
          Dma_lGetGlobalAddress(CpuId,\
                        (uint32)ChCfgPtr->DmaChTCSPtr->DmaDestinationAddress);
  DMA_SFR_INIT_DEINIT_WRITE32(&(MODULE_DMA.CH[Channel].DADR.U), RemapAddress);

  /**! *******************************************************
   * ADDRESS MODIFICATION AND INTERRUPT HANDLING CONFIGURATION FOR CHANNEL
   * *********************************************************/
  /* Configure address and interrupt control settings */
  DMA_SFR_INIT_DEINIT_WRITE32(&(MODULE_DMA.CH[Channel].ADICR.U),
          ChCfgPtr->DmaChTCSPtr->DmaAddressInterruptControl);

  /**! *******************************************************
   * CHANNEL CONFIGURATION - MOVE SIZE, MODE ETC
   * *********************************************************/
  /* Configure the channel configuration settings */
  DMA_SFR_INIT_DEINIT_WRITE32(&(MODULE_DMA.CH[Channel].CHCFGR.U),
          ChCfgPtr->DmaChTCSPtr->DmaChannelConfig);

  #if ((DMA_LINKED_LIST_ENABLE     == STD_ON) || \
       (DMA_DOUBLE_BUFFER_ENABLE   == STD_ON))
  /* MISRA2012_RULE_11_4_JUSTIFICATION: The API expects the address to be
   * in uint32 format. So the casting needs to be done. */
  /* MISRA2012_RULE_11_6_JUSTIFICATION: Mcal API expects
   * address as uint32, however in DMA address is pointer */
  RemapAddress = \
          Dma_lGetGlobalAddress(CpuId,\
                         (uint32)ChCfgPtr->DmaChTCSPtr->DmaShadowAddress);

  lAdicr.U = MODULE_DMA.CH[Channel].ADICR.U;
  if((lAdicr.B.SHCT >  DMA_SHADOW_ADDR_RES2_MASK) &&
     (lAdicr.B.SHCT != DMA_SHADOW_ADDR_RES3_MASK))
  {
    /* [cover parentID={086D1986-30F4-4101-A9DE-41F4356B561A}]
    Is the shadow register to be updated?
    [/cover] */
    /* [cover parentID={E0E00723-8EBE-4cb7-83CA-A17F2A6D1A9A}]
    Assign the shadow address register with the shadow address
    [/cover] */

    DMA_SFR_INIT_DEINIT_WRITE32(&(MODULE_DMA.CH[Channel].SHADR.U),
                                RemapAddress);
  }
  #endif

  /* Reset Channel Control and Status Register */
  DMA_SFR_INIT_DEINIT_WRITE32(&(MODULE_DMA.CH[Channel].CHCSR.U),
                                DMA_CHCSR_CLEAR_VALUE);

  /* Set the TSR Register */
  DMA_SFR_INIT_DEINIT_WRITE32(&(MODULE_DMA.TSR[Channel].U),
                              ChCfgPtr->DmaTsrConfig);
}

#if(DMA_DEINIT_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={4EBD2D37-25DE-4fb7-B846-D2472C9B59E6}]      **
**                                                                            **
** Syntax : Std_ReturnType Dma_lChDeInit(uint8 Channel)                       **
**                                                                            **
** Description : Driver channel deinitialization                              **
**               This local function will deinitialize the DMA channel        **
**               registers                                                    **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Conditionally Reentrant - This function  is re-entrant for    **
**              different DMA channels                                        **
**                                                                            **
** Parameters (in) :  Channel - DMA channel ID(0-127)                         **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  E_OK      - Channel is deinitialized                    **
**                    E_NOT_OK  - Channel is not deinitialized                **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Dma_lChDeInit(const uint8 Channel)
{
  uint32 lCoreId = 0;         /* ID of core used for execution */
  uint8  lChState;
  Std_ReturnType lStatus = E_OK;
  
  /* Get the core ID of the core, where we are executing at this moment */
  lCoreId = Mcal_GetCpuIndex();  
  /* [cover parentID={D90EE2FC-7B20-447b-986A-2D10776BDA89}]
     Is the requested DMA channel, initialized?
     [/cover] */
  /* Is the requested DMA channel, initialized? */  
  if(DMA_GET_CH_INITSTATE(Channel, lCoreId) == DMA_DRIVER_CHINIT)
  {   
    /* Check if the channel is active */
    /* [cover parentID={F1365038-99EF-4050-B0D2-22CE6CC12CF4}]
       [/cover] */
    if( MODULE_DMA.TSR[Channel].B.CH == 0x00U )
    {
      /* Is any transfer already in progress? */

      /* Reset the TCS registers */

      /* ********** Reset all the TCS registers ************ */

      #if ((DMA_LINKED_LIST_ENABLE     == STD_ON) || \
           (DMA_DOUBLE_BUFFER_ENABLE   == STD_ON))
      /* MISRA2012_RULE_19_2_JUSTIFICATION: Union based type definition for SFR
         access. Variable of SFR type defined for writing into register.
         No side effects foreseen by violating this MISRA rule.*/
      Ifx_DMA_CH_ADICR lAdicr;
      lAdicr.U = MODULE_DMA.CH[Channel].ADICR.U;

      if((lAdicr.B.SHCT >  DMA_SHADOW_ADDR_RES2_MASK) &&
         (lAdicr.B.SHCT != DMA_SHADOW_ADDR_RES3_MASK))
      {
        /* [cover parentID={97C72C08-4195-4771-9725-C46130DB60A7}]
        [/cover] */        
        /*Does the channel need a shadow register reset?*/
        /*Reset the shadow register*/
        DMA_SFR_INIT_DEINIT_WRITE32(&(MODULE_DMA.CH[Channel].SHADR.U),
                DMA_REGISTER_RESET_VALUE);
      }
      #endif

      DMA_SFR_INIT_DEINIT_WRITE32(&(MODULE_DMA.CH[Channel].RDCRCR.U),
              DMA_REGISTER_RESET_VALUE);

      DMA_SFR_INIT_DEINIT_WRITE32(&(MODULE_DMA.CH[Channel].SDCRCR.U),
              DMA_REGISTER_RESET_VALUE);

      DMA_SFR_INIT_DEINIT_WRITE32(&(MODULE_DMA.CH[Channel].SADR.U),
              DMA_REGISTER_RESET_VALUE);

      DMA_SFR_INIT_DEINIT_WRITE32(&(MODULE_DMA.CH[Channel].DADR.U),
              DMA_REGISTER_RESET_VALUE);

      DMA_SFR_INIT_DEINIT_WRITE32(&(MODULE_DMA.CH[Channel].ADICR.U),
              DMA_REGISTER_RESET_VALUE);

      DMA_SFR_INIT_DEINIT_WRITE32(&(MODULE_DMA.CH[Channel].CHCFGR.U),
              DMA_REGISTER_RESET_VALUE);

      DMA_SFR_INIT_DEINIT_WRITE32(&(MODULE_DMA.CH[Channel].CHCSR.U),
              DMA_REGISTER_RESET_VALUE);

      DMA_SFR_INIT_DEINIT_WRITE32(&(MODULE_DMA.TSR[Channel].U),
              DMA_REGISTER_RESET_VALUE);


      /* Reset the resource partition allocation, with safety
      end init protection*/

      /* ***** Reset the resource partition allocation ****** */
      /* MISRA2012_RULE_11_8_JUSTIFICATION: Mcal requires the
       * parameter as uint32 const*, but this is a register name
       * which is having a volatile qualifier  */
      /* MISRA2012_RULE_11_3_JUSTIFICATION: Mcal requires the
       * parameter as uint32 const*, but this is a register type  */
      DMA_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(\
              (uint32*)&(MODULE_DMA.HRR[Channel].U),\
              DMA_REGISTER_RESET_VALUE);
      lCoreId=Dma_kConfigPtr->Dma_ChannelMaps[Channel].Dma_ChannelCoreMap;

      /*Update Dma_channel state as "Un-initialized"*/

      /* Keep the state of the channel as 'Uninitialized' */
      lChState = (uint8)0xFF ^ ((uint8)0x1 << (uint8)(Dma_kConfigPtr->
          Dma_ChannelMaps[Channel].Dma_ChannelConfIndexMap % (uint8)8));

      /* No null pointer check needed, since the det checks already
       * covers the possibility */
      (Dma_ChannelStatesPerCore[lCoreId])[Dma_kConfigPtr->
          Dma_ChannelMaps[Channel].Dma_ChannelConfIndexMap/(uint8)8]
                               &= lChState;
    }   
    else
    {
      #if( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE    == STD_ON) )
      /*Report DET or safety error for 'Transfer in progress' */
      Dma_lReportError( DMA_SID_DEINIT, DMA_E_DATA_TRANSFER_IN_PROGRESS );
      #endif
      
      /* Mark the update status as not okay */                 
      lStatus = E_NOT_OK;                 
    }
   
  }
return lStatus;
}
#endif


#if((MCAL_NO_OF_CORES > 1U) && (DMA_DEINIT_API == STD_ON)) && ((DMA_MULTICORE_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={C080CACE-EA83-4225-9D6F-8EFC34394D0F}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE Std_ReturnType Dma_lDeInitDetCheck         **
**                    (                                                       **
**                       const uint32 CoreId                                  **
**                    )                                                       **
**                                                                            **
** Description      :This function is to check all the DETs for Dma_DeInit API**
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different CPU core                        **
**                                                                            **
** Parameters(in)   : CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK      - no DET error                                **
**                    E_NOT_OK  - DET error                                   **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Dma_lDeInitDetCheck(const uint32 CoreId)
{
  Std_ReturnType lErrVal = E_OK;  
  uint32 lCore;
  /* [cover parentID={4F88336E-D245-44be-BFC9-F18A18BE8546}]           
     [/cover] */  
  /* Is CoreId is equal to Master CoreId  */
  if (MCAL_MASTER_COREID == CoreId)
  {
    /* Till the last available Core */
    for (lCore = 0U; lCore < MCAL_NO_OF_CORES; lCore++)
    {      
      /* [cover parentID={84FCD507-5C75-4ecc-A435-52FE2A49415C}]           
         [/cover] */  
      /*Is Core not equal to Master Core & Core is in initialized state */
      if ((MCAL_MASTER_COREID != lCore) && (*(Dma_CoreState[lCore]) != DMA_CPUCORE_UNINIT))
      {
        /* Report DMA_E_SLAVE_INIT DET  */       
        /* [cover parentID={9E647A87-B20B-459b-B0A9-90BEFE02F721}]
           Store the received address as the return value
           [/cover] */
        Dma_lReportMulticoreError(DMA_SID_DEINIT, DMA_E_SLAVE_INIT); 
        lErrVal = E_NOT_OK;
        break;
      }
    }
  }
  return(lErrVal); 
}
#endif 
  
/*******************************************************************************
** Traceability: [cover parentID={CEB24ABD-C7D0-4e63-9E29-188FC2955FEF}]      **
**                                                                            **
** Syntax : uint32 Dma_lGetGlobalAddress(const uint32 CpuId,                  **
**                                       const uint32 LocalDsprAddress)       **
**                                                                            **
** Description : Service to get gobal address from the local address          **
** [/]                                                                        **
**                                                                            **
** Service ID:  NA                                                            **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant                                                     **
**                                                                            **
** Parameters (in) :  CpuId - CPU physical ID                                 **
**                    LocalDsprAddress- Address                               **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  GlobalAddress                                           **
**                                                                            **
*******************************************************************************/
static uint32 Dma_lGetGlobalAddress
(
  const uint32 CpuId,
  const uint32 LocalDsprAddress
)
{
  /**! *********** Why do we need this function at all? ***************
   * The local DSPR of the core is accessible by using the 'D' segment
   * addresses. But, for the DMA we need the absolute addresses. For this,
   * we are using the core id and converting the address to the absolute
   * address which can be starting with 7,6,5,4,3,1 segments. For more
   * details, refer to the section "5.8.1.1 Local and Global Addressing"
   * This holds the keys to most of the questions which are popping up in
   * your mind at this particular point.
   *
   * In case if the address does not have any of the mapping issues that
   * is related to the DSPR, the address is passed onto the caller
   * as it is. */

  uint32 lRetAddr = Mcal_GetGlobalDsprAddress(CpuId, LocalDsprAddress);

  /* [cover parentID={C401CC74-B53A-4246-A8CF-3DDD5867FAEA}]
  Store the received address as the return value
  [/cover] */
  /* [cover parentID={F0398CDD-59B6-498c-A86B-EE5BEEBEDC36}]
  Store the received address as the return value
  [/cover] */
  if(lRetAddr == (uint32)0x00U)
  {
    /* [cover parentID={2698D92E-5F9D-4ae6-8F5F-51E9D3A115C4}]
    Is the address received 'zero'?
    [/cover] */
    lRetAddr = LocalDsprAddress;
  }

  /* [cover parentID={0E60DEBD-C362-4448-996C-1D33921CE243}]
  Keep the caller provided address as the return value
  [/cover] */
  return lRetAddr;
}

#if ( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
/*******************************************************************************
** Traceability     :[cover parentID={5F0E834F-2BFC-4223-A21B-194289D2FA72}]  **
**                                                                            **
** Syntax           : LOCAL_INLINE void Dma_lReportError                      **
**                     (const uint8 ApiId,const uint8 ErrorId)                **
**                                                                            **
** Description      : Function to report Safety Error and/or DET              **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : ApiId - Service ID of the API reporting an error        **
**                    ErrorId - ID of the error reported                      **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*                                                                             **
*******************************************************************************/
static void Dma_lReportError
(
  const uint8 ApiId,
  const uint8 ErrorId
)
{

  /* [cover parentID={C401CC74-B53A-4246-A8CF-3DDD5867FAEA}]
  DET enabled
  [/cover] */
  /* We have a DET. Call the DET function and report the error. */
  #if (DMA_DEV_ERROR_DETECT == STD_ON)
  (void) Det_ReportError(DMA_MODULE_ID, DMA_MODULE_INSTANCE,
                ApiId,ErrorId);
  #endif
  /* [cover parentID={8DAA3F8D-0224-40d6-8B9D-EECA10850201}]
  Report DET for the given error
  [/cover] */
  /* [cover parentID={E066DE30-CC93-47c0-A420-3AD4D64C4585}]
  Safety checks enabled
  [/cover] */
  /* We have a safety error. Call the function to report the error.  */
  #if (DMA_SAFETY_ENABLE == STD_ON)
  Mcal_ReportSafetyError(DMA_MODULE_ID, DMA_MODULE_INSTANCE,
                         ApiId, ErrorId);
  #endif
  /* [cover parentID={75F17032-0A98-452b-925D-7C29D78C637E}]
  Report the safety error according to the specified error ID
  [/cover] */
}
#endif


#if ( (DMA_MULTICORE_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
/*******************************************************************************
** Traceability     : [cover parentID={809E88E4-1476-4e97-BD63-799372C569BA}] **
**                                                                            **
** Syntax           : LOCAL_INLINE void Dma_lReportMulticoreError             **
**                     (const uint8 ApiId,const uint8 ErrorId)                **
**                                                                            **
** Description      : Function to report multicore errors                     **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : ApiId - Service ID of the API reporting an error        **
**                    ErrorId - ID of the error reported                      **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*                                                                             **
*******************************************************************************/
static void Dma_lReportMulticoreError
(
  const uint8 ApiId,
  const uint8 ErrorId
)
{
  /* [cover parentID={07AB406F-4983-44a6-B756-9A649F34BDAC}]
  MultiCore Error or DET enabled
  [/cover] */
  #if( (DMA_MULTICORE_ERROR_DETECT == STD_ON) && \
       (DMA_DEV_ERROR_DETECT       == STD_ON) )
  (void) Det_ReportError( DMA_MODULE_ID, DMA_MODULE_INSTANCE, ApiId, ErrorId);
  #endif
  /* [cover parentID={9ED8BF5B-D67F-4da8-B49F-1C082CC1B7F1}]
  Report DET for the given error
  [/cover] */
  /* [cover parentID={337CFDE2-387C-4e79-9908-2129C80B82D0}]
  Report Safety Error for the given error
  [/cover] */
  #if (DMA_SAFETY_ENABLE == STD_ON)
  Mcal_ReportSafetyError( DMA_MODULE_ID, DMA_MODULE_INSTANCE, ApiId, ErrorId);
  #endif
  /* [cover parentID={C6A91BF3-FF18-4bac-87A6-E373FEBFF48C}]
  Safety enabled
  [/cover] */
}
#endif


/*******************************************************************************
** Traceability     :[cover parentID={534DD505-D3F1-4e60-869A-B21CA664A39E}]  **
**                                                                            **
** Syntax           : void Dma_lUpdateSelectedReg(                            **
**                          Ifx_DMA_CH* const lConfigPtr,                     **
**                          const Dma_ConfigUpdateType* const Config)         **
**                                                                            **
** Description      : Function to update the selected DMA channel registers   **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : lConfigPtr - The pointer to the DMA channel registers   **
**                    Config - The structure holding the values to update     **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*                                                                             **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Dma_lUpdateSelectedReg
(
  Ifx_DMA_CH* const lConfigPtr,
  const Dma_ConfigUpdateType* const Config
)
{
  uint32 RemapAddress;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: Union based type definition for SFR
     access. Variable of SFR type defined for writing into register.
     No side effects foreseen by violating this MISRA rule.*/
  Ifx_DMA_CH_ADICR lAdicr;
  Std_ReturnType lStatus = E_OK;

  if(Config->UpdateControlChcsr == (uint8)DMA_BIT_SET)
  {
    /* [cover parentID={5BDA82E6-A167-4a80-9A03-C2CDEAC0F002}]
    Update CHCSR register with provided value
    [/cover] */
    /* [cover parentID={37AFA576-098C-4568-99DD-6CFAC03FCF8D}]
    Is there a request to
    update CHCSR register?
    [/cover] */

    if((Config->ControlChcsr & DMA_CHCSR_SCH_BIT_POS) == (uint32)DMA_BIT_CLEAR)
    {
      /* [cover parentID={F5669CBE-768B-4976-A9C0-13DD90B2B813}]
      Is the SCH bit set?
      [/cover] */
      /* Configure address and interrupt control settings */
      DMA_SFR_RUNTIME_WRITE32(&(lConfigPtr->CHCSR.U),
                              Config->ControlChcsr);
    }
    else
    {
      /* [cover parentID={C61EDAB5-8017-4257-BBEB-9364412A3FE6}]
      DET or safety check enabled
      [/cover] */
      #if( (DMA_DEV_ERROR_DETECT == STD_ON) || \
           (DMA_SAFETY_ENABLE    == STD_ON) )
      /* [cover parentID={1E694807-AE1C-4cd2-AF11-F0224ABCCCA2}]
      Report error for SCH bit being set in request
      [/cover] */
      Dma_lReportError(DMA_SID_CHUPDATE, DMA_E_CHANNEL_INVALID_START_REQ);
      #endif
      lStatus = (uint8)E_NOT_OK;
      /* [cover parentID={1821B407-9A12-4089-8486-ED50EDBA2A64}]
      Mark the update status as not okay
      [/cover] */
    }
  }

  if(Config->UpdateControlAdicr == (uint8)DMA_BIT_SET)
  {
    /* [cover parentID={EC0D3C65-168E-40df-8047-C73906E313F0}]
    Update ADICR register with provided value
    [/cover] */
    /* [cover parentID={40C13A34-6B91-4ed6-867E-8BAD387C59DC}]
    Is there a request to
    update ADICR register?
    [/cover] */


    /* Configure address and interrupt control settings */
    DMA_SFR_RUNTIME_WRITE32(&(lConfigPtr->ADICR.U),
                            Config->ControlAdicr);
  }

  if(Config->UpdateShadowConfig == (uint8)DMA_BIT_SET)
  {
    /* [cover parentID={113E25AD-8DCC-40a7-AB67-02CE56F46CA1}]
    Is there a request to
    update Shadow register?
    [/cover] */

    lAdicr = lConfigPtr->ADICR;

    if( (lAdicr.B.SHCT >  DMA_SHADOW_ADDR_RES2_MASK) &&
        (lAdicr.B.SHCT != DMA_SHADOW_ADDR_RES3_MASK) )
    {
      /* [cover parentID={C817432E-6EE3-42bb-9A0F-593F07C30310}]
      Are we in a mode which
      needs shadow register?
      [/cover] */
      /* [cover parentID={38E01627-5F0C-42d5-BC4C-F99BEE96896C}]
      Update the shadow register with provided value
      [/cover] */

      DMA_SFR_RUNTIME_WRITE32(&(lConfigPtr->SHADR.U),
              Dma_lGetGlobalAddress(
              Mcal_GetCpuPhysicalId(),
              Config->ShadowConfig));
    }
    else
    {
      #if( (DMA_DEV_ERROR_DETECT == STD_ON) || \
           (DMA_SAFETY_ENABLE    == STD_ON) )
      /* [cover parentID={B1CE8E81-963E-47ec-B574-A18783FF3F53}]
      DET or safety check enabled
      [/cover] */
      /* [cover parentID={BB7D5954-5A1F-4e0a-8C7F-9014A4CB8E51}]
      Report error for Shadow configuration request
      [/cover] */
      /*Report DET on the shadow configuration error*/
      Dma_lReportError(DMA_SID_CHUPDATE, DMA_E_INVALID_SHADOW_CONFIG_REQ);
      #endif
      lStatus = (uint8)E_NOT_OK;
      /* [cover parentID={2FF2EC1D-711F-42de-BE2F-AA4B522A84F1}]
      Mark the node status as not okay
      [/cover] */
    }
  }

  if(lStatus == (uint8)E_OK)
  {
    /* [cover parentID={A96FAADB-EA64-4e53-8738-8BC8651680F2}]
    Is the update status not okay?
    [/cover] */
    if(Config->UpdateDataCrc == (uint8)DMA_BIT_SET)
    {
      /* [cover parentID={E336CCF1-24CF-495b-B452-1FA0B361F67A}]
      Update Data CRC register with provided value
      [/cover] */
      /* [cover parentID={4D7EE606-B2EB-4759-828B-C38F7A013848}]
      Is there a request to
      update Data CRC?
      [/cover] */

      /* Update the Channel Read Data CRC Register */
      DMA_SFR_RUNTIME_WRITE32(&(lConfigPtr->RDCRCR.U),
              Config->DataCrc);
    }

    if(Config->UpdateAddressCrc == (uint8)DMA_BIT_SET)
    {
      /* [cover parentID={3605C532-9702-4afe-A466-1245A2B5CFBA}]
      Is there a request to
      update Address CRC?
      [/cover] */
      /* [cover parentID={435630E9-E495-466f-A0FA-99E7FD051A8A}]
      Update Address CRC register with provided value
      [/cover] */

      /* Update the Channel Address CRC Register */
      DMA_SFR_RUNTIME_WRITE32(&(lConfigPtr->SDCRCR.U),
                              Config->AddressCrc);
    }

    if(Config->UpdateSourceAddress == (uint8)DMA_BIT_SET)
    {
      /* [cover parentID={C36FEBF6-1E78-44c9-AEE5-E5FBADA79196}]
      Is there a request to
      update Source Address?
      [/cover] */

      /* Configure Source address */
      RemapAddress = Dma_lGetGlobalAddress(
                                      Mcal_GetCpuPhysicalId(),
                                      Config->SourceAddress);
      /* [cover parentID={6086D37A-E40C-40e3-AD31-3A636F76AF60}]
      Update Source Address register with provided value
      [/cover] */

      DMA_SFR_RUNTIME_WRITE32(&(lConfigPtr->SADR.U), RemapAddress);
    }

    if(Config->UpdateDestAddress == (uint8)DMA_BIT_SET)
    {
      /* [cover parentID={6DF5A9EB-61CA-4dd5-A6E1-405B5DCD0F68}]
      Is there a request to
      update Destination Address?
      [/cover] */

      /* Configure destination address */
      RemapAddress = Dma_lGetGlobalAddress(
                                         Mcal_GetCpuPhysicalId(),
                                         Config->DestAddress);

      /* [cover parentID={FD64F425-62CA-4ac8-BD82-8A2D3B70307F}]
      Update Destination Address register with provided value
      [/cover] */
      DMA_SFR_RUNTIME_WRITE32(&(lConfigPtr->DADR.U), RemapAddress);
    }

    if(Config->UpdateConfig == (uint8)DMA_BIT_SET)
    {
      /* [cover parentID={43F96B50-7E17-4c88-8BF4-141D5D126D7C}]
      Update CHCFGR register with provided value
      [/cover] */
      /* [cover parentID={4B4A58F7-DF46-4fe3-846F-3ED8BE12AD9E}]
      Is there a request to
      update CHCFGR register?
      [/cover] */

      /* Configure the channel configuration settings */
      DMA_SFR_RUNTIME_WRITE32(&(lConfigPtr->CHCFGR.U),
                              Config->Config);
    }
  }

  return lStatus;
}

/*******************************************************************************
** Traceability     :[cover parentID={129B27CF-AB95-4baf-B00F-8C0CF84FCFB2}]  **
**                                                                            **
** Syntax           :void Dma_lEvaluateMEError(const Ifx_DMA_ME_ERRSR* const  **
**                                               lMeErrRegPtr)                **
**                                                                            **
** Description      : Function to evaluate the ME errors                      **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : lMeErrRegPtr - The pointer to the ME register           **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : The ME errors provided in bit field format              **
**                                                                            **
*******************************************************************************/
static uint32 Dma_lEvaluateMEError
(
  const Ifx_DMA_ME_ERRSR* const lMeErrRegPtr 
  /* MISRA2012_RULE_19_2_JUSTIFICATION: Union based type definition for SFR
     access. Variable of SFR type defined for writing into register.
     No side effects foreseen by violating this MISRA rule.*/
)
{
  /* Return value for providing the status of the error */
  uint32 lRetVal = 0x00U;

  if(lMeErrRegPtr->B.SER == DMA_BIT_SET)
  {
    /* [cover parentID={779F1DAB-9095-403e-AA44-B35C8FC2AFEB}]
    Mark the error as 'Source error'
    [/cover] */
    /* [cover parentID={F4DD536B-C123-4371-BA49-CFB15A036E65}]
    Is it a 'source error'?
    [/cover] */
    lRetVal = (uint32)DMA_EVENT_ME_SOURCE_ERROR;
  }

  if(lMeErrRegPtr->B.DER == DMA_BIT_SET)
  {
    /* [cover parentID={E3C396DE-F92E-4b4a-922F-CCFBCE1C5912}]
    Mark the error as 'Destination error'
    [/cover] */
    /* [cover parentID={DAD27FA5-DD45-477f-84ED-AC12475AFF34}]
    Is it a 'destination error'?
    [/cover] */
    lRetVal |= (uint32)DMA_EVENT_ME_DESTINATION_ERROR;
  }

  if(lMeErrRegPtr->B.RAMER == DMA_BIT_SET)
  {
    /* [cover parentID={449235AE-F9B1-4842-ACA3-611C78CB15FC}]
    Mark the error as 'RAM error'
    [/cover] */
    /* [cover parentID={61E6B59E-FA02-4dec-93C7-A1AE82370BFD}]
    Is it a 'RAM error'?
    [/cover] */
    lRetVal |= (uint32)DMA_EVENT_ME_RAM_ERROR;
  }

  if(lMeErrRegPtr->B.SLLER == DMA_BIT_SET)
  {
    /* [cover parentID={2629BD5A-5AE9-46c2-842E-8A566F304FDE}]
    Mark the error as 'SAFLL error'
    [/cover] */
    /* [cover parentID={10CD6C97-58BE-4060-8D8E-63663E0ACA1F}]
    Is it a 'safe linked list error'?
    [/cover] */
    lRetVal |= (uint32)DMA_EVENT_ME_SAFE_LINKEDLIST_ERROR;
  }

  if(lMeErrRegPtr->B.DLLER == DMA_BIT_SET)
  {
    /* [cover parentID={5BA309B4-1A93-4447-847F-B70A2B9BFD01}]
    Mark the error as 'DMALL error'
    [/cover] */
    /* [cover parentID={87FA4AD7-0B66-4ded-B5B2-0856CFFAE5A4}]
    Is it a 'DMA Linked list' error?
    [/cover] */
    lRetVal |= (uint32)DMA_EVENT_ME_DMA_LINKEDLIST_ERROR;
  }

  if(lMeErrRegPtr->B.SPBER == DMA_BIT_SET)
  {
    /* [cover parentID={BD00AEE0-9645-4654-BB68-171F7F230F28}]
    Mark the error as 'SPB error'
    [/cover] */
    /* [cover parentID={6342D0F6-6985-4969-A6B4-DC9819420CA2}]
    Is it an SPB error?
    [/cover] */
    lRetVal |= (uint32)DMA_EVENT_ME_SPB_ERROR;
  }

  if(lMeErrRegPtr->B.SRIER == DMA_BIT_SET)
  {
    /* [cover parentID={785967AC-055A-42cf-B2D2-3C31B53ECF6D}]
    Mark the error as 'SRI error'
    [/cover] */
    /* [cover parentID={27E4FF3F-A7BE-4488-A390-CB518DF6EA75}]
    Is it an SRI error?
    [/cover] */
    lRetVal |= (uint32)DMA_EVENT_ME_SRI_ERROR;
  }

  return lRetVal;
}



/* [cover parentID={2FB25831-5390-4ca1-ACA3-F3EDA3C7E381}]
 * Code Section
 * [/cover]*/
#define DMA_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Dma_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of 'Dma_kConfigPtr' and
 * 'Dma_CoreTosMap' before #include memap.h - Accepted deviation as per AUTOSAR */
#include "Dma_MemMap.h"

