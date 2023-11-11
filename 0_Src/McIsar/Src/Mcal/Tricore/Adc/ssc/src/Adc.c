/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2023)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : Adc.c                                                      **
**                                                                            **
**  VERSION      : 40.0.0                                                     **
**                                                                            **
**  DATE         : 2023-05-18                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY : [cover parentID={898E18F0-71B4-4e5b-9D37-46B8135C292E}]    **
**                                                                            **
**  DESCRIPTION  : Adc Driver source file                                     **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of ADC Driver,                           **
**                     AUTOSAR Release 4.2.2 and 4.4.0                        **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/*[cover parentID={B2A31D0F-3CF7-47d9-BD9E-36AE5295CFEF}] File Structure
[/cover]*/

/*[cover parentID={5A3ADFAA-3D3E-4c98-9E2B-B3BF1BD77BB9}] Adc_Irq.c File to be
developed by user [/cover] */
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/*[cover parentID={DE6EB695-89E0-4a47-B354-EFE3CADF580B}]
Imported Interfaces [/cover]*/
#include "Mcal_Compiler.h"
#include "Adc.h"
/*[cover parentID={90DAD596-ABB0-4e8c-A0F6-DDD50B853D79},
{8790813B-BDC0-4356-A4E2-F7D8C4308EEA}] Exclusive Usage of EVADC
register [/cover]*/

#include "IfxEvadc_bf.h"
#include "IfxEvadc_reg.h"
#include "IfxScu_bf.h"
#include "IfxScu_reg.h"
#include "IfxSrc_bf.h"
#include "IfxSrc_reg.h"
#include "SchM_Adc.h"
#if ((ADC_CLC_FAILURE_DEM_NOTIF == ADC_ENABLE_DEM_REPORT)||\
     (ADC_CONV_STOP_TIME_DEM_NOTIF == ADC_ENABLE_DEM_REPORT)||\
	 (ADC_RUNTIME_ERROR_DETECT == STD_ON))
#include "Mcal_Wrapper.h"
#endif
#if (ADC_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif
/* [cover parentID={A5B1DAC2-4EA6-4fe3-A61E-A351E74D6639}]
    Safety Mechanism for reporting errors in ASIL B usecase [/cover] */
#if (ADC_SAFETY_ENABLE == STD_ON)
#include "Mcal_SafetyError.h"
#endif
#if( (ADC_INIT_DEINIT_API_MODE != ADC_MCAL_SUPERVISOR)||\
     (ADC_RUN_TIME_API_MODE != ADC_MCAL_SUPERVISOR) )
#include "McalLib_OsStub.h"
#endif
/*[/cover]*/

/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/
#ifndef ADC_AR_RELEASE_MAJOR_VERSION
  #error "ADC_AR_RELEASE_MAJOR_VERSION is not defined."
#endif

#ifndef ADC_AR_RELEASE_MINOR_VERSION
  #error "ADC_AR_RELEASE_MINOR_VERSION is not defined."
#endif

#ifndef ADC_AR_RELEASE_REVISION_VERSION
  #error "ADC_AR_RELEASE_REVISION_VERSION is not defined."
#endif

/*[cover parentID={57675972-EF57-41f1-A663-665E62D0DD60},
                  {F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}]
                  Modules version consistency check [/cover]*/
#if ( ADC_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION)
  #error "ADC_AR_RELEASE_MAJOR_VERSION does not match."
#endif

#if ( ADC_AR_RELEASE_MINOR_VERSION != MCAL_AR_RELEASE_MINOR_VERSION)
  #error "ADC_AR_RELEASE_MINOR_VERSION does not match."
#endif

#if ( ADC_AR_RELEASE_REVISION_VERSION != MCAL_AR_RELEASE_REVISION_VERSION)
  #error "ADC_AR_RELEASE_REVISION_VERSION does not match."
#endif

#ifndef ADC_SW_MAJOR_VERSION
  #error "ADC_SW_MAJOR_VERSION is not defined."
#endif

#ifndef ADC_SW_MINOR_VERSION
  #error "ADC_SW_MINOR_VERSION is not defined."
#endif

#ifndef ADC_SW_PATCH_VERSION
  #error "ADC_SW_PATCH_VERSION is not defined."
#endif

/*[cover parentID={57675972-EF57-41f1-A663-665E62D0DD60}] Modules version
consistency check [/cover]*/
#if ( ADC_SW_MAJOR_VERSION != 20U )
  #error "ADC_SW_MAJOR_VERSION does not match."
#endif

#if ( ADC_SW_MINOR_VERSION != 25U )
  #error "ADC_SW_MINOR_VERSION does not match."
#endif

#if ( ADC_SW_PATCH_VERSION != 0U )
  #error "ADC_SW_PATCH_VERSION does not match."
#endif

/*[cover parentID={D9C75887-D938-4689-BDD4-B8BD24AB1711}] Version Check for DET
[/cover]*/
#if (ADC_DEV_ERROR_DETECT == STD_ON)

  #ifndef DET_AR_RELEASE_MAJOR_VERSION
    #error "DET_AR_RELEASE_MAJOR_VERSION is not defined."
  #endif

  #if (DET_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION)
    #error "DET_AR_RELEASE_MAJOR_VERSION does not match."
  #endif

#endif /* End for ADC_DEV_ERROR_DETECT */

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
#define ADC_ONE_U                       (1U)

#define ADC_INVALID_GROUP_ID            ((Adc_GroupType)0xFFU)
#define ADC_INVALID_CHANNEL_ID          ((Adc_ChannelType)0xFFU)
#if (ADC_SYNC_CONV_ENABLE == STD_ON)
#define ADC_INVALID_KERNEL_ID           ((uint8)0xFFU)
#endif /* End for ADC_SYNC_CONV_ENABLE */
#if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
#define ADC_INVALID_RS_ID               ((uint8)0xFFU)
#if ( ((ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
      ((MCAL_AR_VERSION == MCAL_AR_422) && (ADC_DEV_ERROR_DETECT == STD_ON))) \
      && (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) )
#define ADC_MAX_PRIORITY_LVL            ((Adc_GroupPriorityType)0xFFU)
#endif
#endif /* End for ADC_PRIORITY_IMPLEMENTATION */
#define ADC_RS0_ID                       ((uint8)0U)
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
#define ADC_RS1_ID                       ((uint8)1U)
#define ADC_RS2_ID                       ((uint8)2U)
#endif
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
#define ADC_LIMIT_CHECK_SRN              ((uint8)3U)
#endif

#define ADC_KERNEL_ID_START_POS         (5U)
#define ADC_KERNEL_ID_NO_OF_BITS        (11U)
#define ADC_GROUP_ID_MASK               (0x1FU)
#if (ADC_HW_TRIGGER_API == STD_ON)
#define ADC_ERU_EICR_REG_SEL_MASK       (3U)
#define ADC_ERU_IGCR_REG_SEL_MASK       (3U)
#define ADC_ERU_CH_CFG_BIT_POS_SHIFT    (4U)
#define ADC_INIT_DEINIT                 (0U)
#define ADC_RUNTIME                     (1U)
#endif
#if (ADC_STARTUP_CALIB_API == STD_ON)
#define ADC_STARTUP_CAL_STARTED         (1U)
#endif
#define ADC_PRIMARY_CONV_CHANNEL_COUNT     (8U)
#define ADC_SECONDARY_CONV_CHANNEL_COUNT   (16U)
#define ADC_MAX_RESULT_REGISTERS           (16U)

#define ADC_TARGET_POWER_STATE_MASK     (0x00000003U)
#if(ADC_LOW_POWER_STATE_SUPPORT == STD_ON)
#define ADC_BITS_PER_POWER_STATE        (3)
#define ADC_INVALID_POWER_STATE         ((uint8)0xFFU)
#endif

#if(ADC_RESULT_HANDLING_IMPLEMENTATION != ADC_DMA_MODE_RESULT_HANDLING)
#if (ADC_RESULT_ALIGNMENT == ADC_ALIGN_RIGHT)
#define ADC_12BIT_RESULT_MASK  (0x00000FFFU)
#else
#define ADC_12BIT_RESULT_MASK  (0x0000FFF0U)
#endif
#endif

#if (ADC_TRIGGER_ONE_CONV_ENABLE == STD_ON)
#define ADC_WAIT_FOR_DUMMY_CONV (0x00005000U)
#endif /* End for ADC_TRIGGER_ONE_CONV_ENABLE */

#if ((ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) ||\
     (ADC_SYNC_CONV_ENABLE == STD_ON))
#define ADC_CHANNEL_RESULT_CLR_MASK     ((uint16)0xFFFFU)
#endif
#define ADC_CLR_VALID_FLAG_REG          ((uint32)0x0000FFFFU)
#define ADC_REQTM_RESET_VALUE           ((uint32)0xFFC00000U)
#define ADC_CLR_SOURCE_EVENT            ((uint32)0x00000007U)
#define ADC_CLR_RESULT_EVENT            ((uint32)0x0000FFFFU)
#define ADC_CLR_PRIMARY_CH_EVENT        ((uint32)0x000000FFU)
#if (ADC_SECONDARY_KERNEL_AVAILABLE == STD_ON)
#define ADC_CLR_SECONDARY_CH_EVENT      ((uint32)0x0000FFFFU)
#endif
#define ADC_ANCFG_DEFAULT_VALUE         ((uint32)0x00300004U)
#if (ADC_DEINIT_API == STD_ON)
#define ADC_CLC_DEFAULT_VALUE           ((uint32)0x00000001U)
#endif
#define ADC_ALIAS_DEFAULT_VALUE         ((uint32)0x00000100U)
#if (ADC_HW_TRIGGER_API == STD_ON)
#define ADC_ERU_WR_MASK                 ((uint32)0x0000FFFFU)
#endif
#if (ADC_RUN_TIME_API_MODE != ADC_MCAL_SUPERVISOR)
#define ADC_CLR_SRC_MASK                ((uint32)0xFFFFFFFFU)
#endif
#define ADC_SEVNP_INIT_CFG_VALUE        ((uint32)0x00000210U)

#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
#define ADC_CEVNP_INIT_CFG_VALUE        ((uint32)0x33333333U)
#else
#define ADC_CEVNP_INIT_CFG_VALUE        ((uint32)0U)
#endif

#if(ADC_RESULT_HANDLING_IMPLEMENTATION == ADC_DMA_MODE_RESULT_HANDLING)
#define ADC_REVNP_INIT_CFG_VALUE        ((uint32)0x33333333U)
#else
#define ADC_REVNP_INIT_CFG_VALUE        ((uint32)0U)
#endif

#if ((ADC_HW_TRIGGER_API == STD_ON) && (ADC_INIT_CHECK_API == STD_ON) && \
(ADC_GTM_AVAILABLE == STD_ON))
#define ADC_TOM_ATOM_CH_CNTRL_REG_RST_VAL ((uint32)0x00000800U)
#endif
#define ADC_Q_CTRL_WRITE_PROTECT_MSK    ((uint32)(\
                           ((uint32)ADC_ONE_U<<IFX_EVADC_G_Q_QCTRL_TMWC_OFF)|\
                           ((uint32)ADC_ONE_U<<IFX_EVADC_G_Q_QCTRL_GTWC_OFF)|\
                           ((uint32)ADC_ONE_U<<IFX_EVADC_G_Q_QCTRL_XTWC_OFF)))

#define ADC_GLOBCFG_WRITE_PROTECT_MSK    (\
                           (uint32)ADC_ONE_U<<IFX_EVADC_GLOBCFG_CPWC_OFF)

#define ADC_GLOBTF_WRITE_PROTECT_MSK   ((uint32)(\
                           ((uint32)ADC_ONE_U<<IFX_EVADC_GLOB_TF_MDWC_OFF)|\
                           ((uint32)ADC_ONE_U<<IFX_EVADC_GLOB_TF_CDWC_OFF)))
#if ((ADC_TRIGGER_ONE_CONV_ENABLE == STD_ON) || \
    (ADC_ENABLE_START_STOP_GROUP_API == STD_ON))
#define ADC_START_SW_TRIG_CONV         ((uint32)(\
                           ((uint32)ADC_ONE_U<<IFX_EVADC_G_Q_QMR_ENGT_OFF)|\
                           ((uint32)ADC_ONE_U<<IFX_EVADC_G_Q_QMR_TREV_OFF)))
#endif

#if(ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
#define ADC_ARBPR_PRIO_MSK            ((uint32)(\
        ((uint32)IFX_EVADC_G_ARBPR_PRIO0_MSK<<IFX_EVADC_G_ARBPR_PRIO0_OFF)|\
        ((uint32)IFX_EVADC_G_ARBPR_PRIO1_MSK<<IFX_EVADC_G_ARBPR_PRIO1_OFF)|\
        ((uint32)IFX_EVADC_G_ARBPR_PRIO2_MSK<<IFX_EVADC_G_ARBPR_PRIO2_OFF)))

#define ADC_ARBPR_ASEN_MSK            ((uint32)(\
        ((uint32)IFX_EVADC_G_ARBPR_ASEN0_MSK<<IFX_EVADC_G_ARBPR_ASEN0_OFF)|\
        ((uint32)IFX_EVADC_G_ARBPR_ASEN1_MSK<<IFX_EVADC_G_ARBPR_ASEN1_OFF)|\
        ((uint32)IFX_EVADC_G_ARBPR_ASEN2_MSK<<IFX_EVADC_G_ARBPR_ASEN2_OFF)))
#endif /* End for ADC_PRIORITY_IMPLEMENTATION */

#if(ADC_EMUX_ENABLE == STD_ON)
#define ADC_EMUX_SEQUENCE_MODE       (uint32)(3U)
#define ADC_EMUX_GRAYCODE_ENABLED    (uint32)(1U)
#define ADC_EMUX_STCE_ENABLED        (uint32)(1U)
#define ADC_EMUX_ARB_CH_SEL_STYLE    (uint32)(0U)
#define ADC_EMUX_IDLE                (uint8)(0U)

#if ((ADC_RESULT_HANDLING_IMPLEMENTATION != ADC_DMA_MODE_RESULT_HANDLING) ||\
    (ADC_GRP_NOTIF_CAPABILITY == STD_ON))
#define ADC_EMUX_COMPLETED           (uint8)(1U)
#endif/*End for Interrupt Mode Handling or Notification capability*/

#if (ADC_RESULT_HANDLING_IMPLEMENTATION != ADC_DMA_MODE_RESULT_HANDLING)
#define ADC_EMUX_STREAM_COMPLETED    (uint8)(2U)
#endif/*End for Interrupt Mode Handling*/

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
#define ADC_EMUX_RESULT_NOTIF_STATUS (uint8)(0U)
#endif/*End for Notification capability*/

/* This macro is used to program the dummy EMUX mode */
#define ADC_EMUX_DUMMY_MODE_PROGRAM ((uint32)(\
        ((uint32)ADC_EMUX_GRAYCODE_ENABLED<<IFX_EVADC_G_EMUXCTR_EMXCOD_OFF)|\
        ((uint32)ADC_EMUX_STCE_ENABLED<<IFX_EVADC_G_EMUXCTR_EMXST_OFF)|\
        ((uint32)ADC_EMUX_ARB_CH_SEL_STYLE<<IFX_EVADC_G_EMUXCTR_EMXCSS_OFF)|\
        ((uint32)ADC_ONE_U<<IFX_EVADC_G_EMUXCTR_EMXWC_OFF)))

/* This macro is used to program the actual EMUX mode */
#define ADC_EMUX_SEQUENCE_MODE_PROGRAM ((uint32)(\
        ((uint32)ADC_EMUX_SEQUENCE_MODE<<IFX_EVADC_G_EMUXCTR_EMUXMODE_OFF)|\
        ((uint32)ADC_EMUX_GRAYCODE_ENABLED<<IFX_EVADC_G_EMUXCTR_EMXCOD_OFF)|\
        ((uint32)ADC_EMUX_STCE_ENABLED<<IFX_EVADC_G_EMUXCTR_EMXST_OFF)|\
        ((uint32)ADC_EMUX_ARB_CH_SEL_STYLE<<IFX_EVADC_G_EMUXCTR_EMXCSS_OFF)|\
        ((uint32)ADC_ONE_U<<IFX_EVADC_G_EMUXCTR_EMXWC_OFF)))
#endif /* End for EMUX feature */
/*******************************************************************************
**                         User Mode Macros                                   **
*******************************************************************************/
/*[cover parentID={1A65EADD-AFD0-4845-B2D2-8257E086DD67}] User Mode Support via
OS function calls Macros [/cover] */
/* [cover parentID={8699AFA6-421D-4ee0-BA97-AA99A3FB4974}]
Precompile Time support for User Mode
[/cover] */
#if(ADC_INIT_DEINIT_API_MODE == ADC_MCAL_SUPERVISOR)
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for
   User mode support in code. No side effects foreseen by violating this MISRA
   rule. */
  #define ADC_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(RegAdd,Data)   \
    Mcal_WritePeripEndInitProtReg(RegAdd,Data)

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for
   User mode support in code. No side effects foreseen by violating this MISRA
   rule. */
/* MISRA2012_RULE_2_5_JUSTIFICATION: A Generic function like macro is defined
   to use in the code for user mode support. No side effects foreseen by
   violating this MISRA rule. */
  #define ADC_INIT_DEINIT_WRITE_SAFETY_ENDINIT_PROTREGMASK(RegAdd,Data,Mask)   \
    Mcal_WriteSafetyEndInitProtRegMask(RegAdd,Data,Mask)

#else

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for
   User mode support in code. No side effects foreseen by violating this MISRA
   rule. */
  #define ADC_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(RegAdd,Data)   \
    MCAL_LIB_WRITEPERIPENDINITPROTREG(RegAdd,Data)
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for
   User mode support in code. No side effects foreseen by violating this MISRA
   rule. */
/* MISRA2012_RULE_2_5_JUSTIFICATION: A Generic function like macro is defined
   to use in the code for user mode support. No side effects foreseen by
   violating this MISRA rule. */
  #define ADC_INIT_DEINIT_WRITE_SAFETY_ENDINIT_PROTREGMASK(RegAdd,Data,Mask)   \
    MCAL_LIB_WRITESAFETYENDINITPROTREGMASK(RegAdd,Data,Mask)
#endif

/* [cover parentID={8699AFA6-421D-4ee0-BA97-AA99A3FB4974}]
Precompile Time support for User Mode
[/cover] */
#if (ADC_RUN_TIME_API_MODE == ADC_MCAL_SUPERVISOR)
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for
   User mode support in code. No side effects foreseen by violating this MISRA
   rule. */
/* MISRA2012_RULE_2_5_JUSTIFICATION: A Generic function like macro is defined
   to use in the code for user mode support. No side effects foreseen by
   violating this MISRA rule. */
  #define ADC_RUNTIME_WRITE_SAFETY_ENDINIT_PROTREGMASK(RegAdd,Data,Mask)    \
  Mcal_WriteSafetyEndInitProtRegMask(RegAdd,Data,Mask)
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for
   User mode support in code. No side effects foreseen by violating this MISRA
   rule. */
  #define ADC_RUNTIME_OS_MODIFY32(ModuleId, RegAdd, ClearMask, SetMask)        \
                         ((RegAdd->U) = ((RegAdd->U)|(SetMask)))
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for
   User mode support in code. No side effects foreseen by violating this MISRA
   rule. */
/* MISRA2012_RULE_2_5_JUSTIFICATION: A Generic function like macro is defined
   to use in the code for user mode support. No side effects foreseen by
   violating this MISRA rule. */
  #define ADC_RUNTIME_WRITE_SAFETY_ENDINIT_PROTREGMASK(RegAdd,Data,Mask)    \
  MCAL_LIB_WRITESAFETYENDINITPROTREGMASK(RegAdd,Data,Mask)
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for
   User mode support in code. No side effects foreseen by violating this MISRA
   rule. */
  #define ADC_RUNTIME_OS_MODIFY32(ModuleId,RegAdd,ClearMask,SetMask)  \
  MCAL_SFR_OS_MODIFY32(ModuleId, RegAdd, ClearMask, SetMask)

#endif

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/
/*Type Definition for  Adc_QueueDataType*/
#if((ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) ||\
    (ADC_ENABLE_QUEUING == STD_ON))
/* [cover parentID={D2B0DFB9-22B0-4701-9A79-C8F6F5395F39}]  [/cover]*/
typedef struct
{
  Adc_GroupType PreviousGroup;
  Adc_GroupType NextGroup;
} Adc_QueueDataType;
#endif

/* [cover parentID={A9A0357F-AEFA-49b9-BD7F-1D59EF9A3238}]  [/cover]*/
typedef struct
{
  Adc_GroupType ActiveGroupId;
  Adc_ChannelType ActiveLimitChkCh;
  #if((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW) ||\
      (ADC_ENABLE_QUEUING == STD_ON))
  Adc_QueueDataType QueueOfSwGroup[ADC_MAX_GROUPS];
  Adc_GroupType PopGroupId;
  Adc_GroupType PushGroupId;
  #endif
  uint8 IsrNoServiceFlag;
} Adc_RSDataType;

/* [cover parentID={8B9BC580-36C9-4ad6-A9E5-536F89214AAE}]  [/cover]*/
typedef struct
{
  #if(ADC_RESULT_HANDLING_IMPLEMENTATION != ADC_DMA_MODE_RESULT_HANDLING)
  Adc_ValueGroupType *GrpResBuffer[ADC_MAX_GROUPS];
  #endif
  uint32 GrpStatus;
  uint32 GrpResultStatus;
  uint32 GrpBufferEndResultStatus;
  uint32 GrpNotifStatus;
  #if(ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
  Adc_QueueDataType QueueOfSwGroup[ADC_MAX_GROUPS];
  Adc_GroupType PopGroupId;
  Adc_GroupType PushGroupId;
  #endif
  Adc_RSDataType RSData[ADC_REQSRC_USED_COUNT];
  uint16 AllRunningChannels;
  uint16 AllRunningResReg;
  #if(ADC_RESULT_HANDLING_IMPLEMENTATION != ADC_DMA_MODE_RESULT_HANDLING)
  Adc_StreamNumSampleType NumofValidConRes[ADC_MAX_GROUPS];
  #endif
  #if(ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
  #if(ADC_ENABLE_LIMIT_CHECK==STD_ON)
  uint8 LimitChkActiveFlag;
  #endif
  uint8 AliasActiveFlag;
  #endif
  #if(ADC_EMUX_ENABLE == STD_ON)
  uint8 EmuxConversionActiveFlag;
  #endif
} Adc_GlobalDataType;

#if((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON) ||\
    (ADC_INIT_CHECK_API == STD_ON))
/* [cover parentID={D32920D5-83CC-42b1-8ED8-13F77188534C}]  [/cover]*/
typedef enum
{
  ADC_UNINIT_COMPLETED = 0U,
  ADC_UNINIT_STARTED = 1U,
  ADC_INITIALIZED = 2U
} Adc_InitStateType;
#endif

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
Code Memory section naming as per AS [/cover]*/
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}] Memory mapping
support [/cover] */
/*[cover parentID={37748051-6EE3-4713-A929-15FE090C4A8E}]
MemMap_h file to be developed by user [/cover]*/
#define ADC_START_SEC_CODE_ASIL_B_GLOBAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Adc_MemMap.h"

LOCAL_INLINE uint32 Adc_lGetAdcKernel(const Adc_GroupType GroupId);
LOCAL_INLINE Adc_GroupType Adc_lGetKernelGroupId(const Adc_GroupType GroupId);
LOCAL_INLINE Adc_GlobalDataType* Adc_lGetKernelDataAddress(\
                             const uint32 KernelId, const uint32 CoreId);
#if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
LOCAL_INLINE uint8 Adc_lGetGrpReqSrc(const uint32 KernelId,\
                                     const Adc_GroupType GroupId,\
                                     const uint32 CoreId);
#endif

/************** Local APIs for Group Status - Start **************/
LOCAL_INLINE void Adc_lSetGroupStatusBusyAtomic(\
        Adc_GlobalDataType * const KernelDataPtr,const Adc_GroupType GroupId);
LOCAL_INLINE void Adc_lSetGroupResultAtomic(\
       Adc_GlobalDataType *const KernelDataPtr, const Adc_GroupType GroupId);
LOCAL_INLINE void Adc_lSetResBuffEndStatusAtomic(\
          Adc_GlobalDataType *const KernelDataPtr, const Adc_GroupType GroupId);
#if (ADC_STARTUP_CALIB_API == STD_ON)
LOCAL_INLINE void Adc_lSetStartupCalStatusAtomic(void);
#endif
LOCAL_INLINE void Adc_lClrGroupStatusBusyAtomic(\
              Adc_GlobalDataType * const KernelDataPtr, \
              const Adc_GroupType GroupId);
LOCAL_INLINE void Adc_lClrGroupResultAtomic(\
              Adc_GlobalDataType * const KernelDataPtr, \
              const Adc_GroupType GroupId);
LOCAL_INLINE void Adc_lClrResBuffEndStatusAtomic(\
              Adc_GlobalDataType * const KernelDataPtr, \
              const Adc_GroupType GroupId);

#if (ADC_STARTUP_CALIB_API == STD_ON)
LOCAL_INLINE void Adc_lClrStartupCalStatusAtomic(void);
#endif

LOCAL_INLINE uint32 Adc_lGetGroupStatus(\
        const Adc_GlobalDataType * const KernelDataPtr, \
        const Adc_GroupType GroupId);
LOCAL_INLINE uint32 Adc_lGetGroupResultStatus(\
        const Adc_GlobalDataType * const KernelDataPtr, \
        const Adc_GroupType GroupId);
LOCAL_INLINE uint32 Adc_lGetResBuffEndStatus(\
        const Adc_GlobalDataType * const KernelDataPtr, \
        const Adc_GroupType GroupId);
#if (ADC_STARTUP_CALIB_API == STD_ON)
LOCAL_INLINE uint32 Adc_lGetStartupCalStatusAtomic(void);
#endif

#if( (ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
     ((MCAL_AR_VERSION == MCAL_AR_422) && (ADC_DEV_ERROR_DETECT == STD_ON)) )
LOCAL_INLINE uint32 Adc_lGetAllGroupStatus(const uint32 CoreId);
#endif

#if ((ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) ||\
     (ADC_SYNC_CONV_ENABLE == STD_ON))
static void Adc_lSetRunningChAndResReg(const uint32 KernelId,\
                                    const Adc_GroupCfgType * const GrpCfgPtr,\
                                    const uint32 CoreId);
static void Adc_lClrRunningChAndResReg(const uint32 KernelId,\
                                     const Adc_GroupCfgType * const GrpCfgPtr,\
                                     const uint32 CoreId);
#endif

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
LOCAL_INLINE void Adc_lSetGrpNotifAtomic(\
              Adc_GlobalDataType * const KernelDataPtr, \
              const Adc_GroupType GroupId);
LOCAL_INLINE void Adc_lClrGrpNotifAtomic(\
              Adc_GlobalDataType * const KernelDataPtr, \
              const Adc_GroupType GroupId);
LOCAL_INLINE uint32 Adc_lGetGroupNotifStatus(\
        const Adc_GlobalDataType * const KernelDataPtr, \
        const Adc_GroupType GroupId);
#endif

/************** Local APIs for Group Status - End **************/

LOCAL_INLINE void Adc_lInit(const uint32 CoreId);
LOCAL_INLINE void Adc_lResetGlobalSfr(void);
static void Adc_lResetCoreGlobalVars(const uint32 CoreId);
LOCAL_INLINE void Adc_lKernelInit(const Adc_HwUnitCfgType * const KernelCfgPtr,\
                                  const uint32 KernelId);
static void Adc_lKernelDeInit(const Adc_HwUnitCfgType * const KernelCfgPtr, \
                              const uint32 KernelId);

static void Adc_lPrepareGrpForStart(const uint32 KernelId,\
                              const Adc_GroupType GroupId, const uint32 CoreId);
#if (ADC_SYNC_CONV_ENABLE == STD_ON)
static void Adc_lEnableSyncCh(const uint32 KernelId,\
                              const Adc_ChannelType AnChannelNum,\
                              const uint32 ChctrValue,\
                              const Adc_ResultRegType ResReg,\
                              const uint32 CoreId);
static void Adc_lClearSyncCh(const uint32 KernelId,\
                              const Adc_ChannelType AnChannelNum,\
                              const Adc_ResultRegType ResReg);
#endif

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
static void Adc_lStartSwConversion(const Adc_GroupCfgType * const GrpPtr,\
                                   const uint32 KernelId,\
                                   const uint8 ReqSrc);
#endif

#if (ADC_SYNC_CONV_ENABLE == STD_ON)
LOCAL_INLINE void Adc_lClearSlaveEvents(const Adc_GroupCfgType * const GrpPtr,\
                                        const uint32 KernelId);
#endif

#if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
LOCAL_INLINE void Adc_lAdjustRsPriorities(const uint32 KernelId);
#endif

#if(((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW) ||\
(ADC_ENABLE_QUEUING == STD_ON)) && (ADC_ENABLE_START_STOP_GROUP_API == STD_ON))
LOCAL_INLINE void Adc_lPushToQueue(const uint32 KernelId,\
                                   const Adc_GroupType GroupId,\
                                   const uint32 CoreId);
static void Adc_lScheduleFromQueue(const uint32 KernelId,\
                                   const uint32 CoreId,\
                                   const uint8 ReqSrc);
#endif

#if((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW) ||\
   (ADC_ENABLE_QUEUING == STD_ON))
static void Adc_lPopFromQueue(const uint32 KernelId,\
                              const Adc_GroupType GroupId,\
                              const uint32 CoreId);
LOCAL_INLINE void Adc_lRemoveFromQueue(const uint32 KernelId,\
        Adc_GlobalDataType * const KernelDataPtr, const Adc_GroupType GroupId,\
        const uint32 CoreId);
#endif

#if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
LOCAL_INLINE uint8 Adc_lGetReqSrcForGrp(const uint32 KernelId,\
                              const Adc_GroupType GroupId, const uint32 CoreId);
LOCAL_INLINE void Adc_lPushToScheduler(const uint32 KernelId,\
                                       const Adc_GroupType GroupId,\
                                       const uint32 CoreId,\
                                       const uint8 PriorityBoost);
static void Adc_lSchedulerOnStart(const uint32 KernelId,\
                                  const Adc_GroupType GroupId,\
                                  const uint32 CoreId);
#if(ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
LOCAL_INLINE Adc_GroupType Adc_lPopFromScheduler(const uint32 KernelId,\
                                                 const uint32 CoreId);
static void Adc_lScheduleNext(const uint32 KernelId,\
                              const uint32 CoreId,\
                              const uint8 ReqSrc);
#endif
static void Adc_lSchedulerOnStop(const uint32 KernelId,\
                                 const Adc_GroupType GroupId,\
                                 const uint32 CoreId);
#endif

static void Adc_lStopConvRequest(const Adc_GroupCfgType * const GrpPtr,\
                                 const uint32 KernelId,\
                                 const uint8 ReqSrc);
static void Adc_lClearGroupSfr(const Adc_GroupCfgType * const GrpPtr,\
                               const uint32 KernelId,\
                               const uint8 ReqSrc);
LOCAL_INLINE void Adc_lRemoveActiveGroup(\
                                     Adc_GlobalDataType * const KernelDataPtr,\
                                     const Adc_GroupCfgType * const GrpPtr,\
                                     const uint8 ReqSrc);

#if (ADC_HW_TRIGGER_API == STD_ON)
LOCAL_INLINE void Adc_lResetHwTrigger(const Adc_GroupCfgType * const GrpPtr,\
                                      const uint8 Mode);
LOCAL_INLINE void Adc_lSetHwTrigger(const Adc_GroupCfgType * const GrpPtr);
LOCAL_INLINE void Adc_lStartHwConversion(const Adc_GroupCfgType * const GrpPtr,\
                                         const uint32 KernelId,\
                                         const uint8 ReqSrc);
#if (ADC_GTM_AVAILABLE == STD_ON)
LOCAL_INLINE void Adc_lGtmChannelInit(\
                 const Mcu_17_Gtm_TomAtomChConfigType * const GtmChannelCfgPtr);
LOCAL_INLINE void Adc_lGtmChannelDeInit(\
                 const Mcu_17_Gtm_TomAtomChConfigType * const GtmChannelCfgPtr);
#endif
LOCAL_INLINE void Adc_lEruChannelInit(\
                          const Adc_EruChannelCfgType * const EruChannelCfgPtr);
LOCAL_INLINE void Adc_lEruChannelDeInit(\
        const Adc_EruChannelCfgType * const EruChannelCfgPtr, const uint8 Mode);
#endif

#if(ADC_RESULT_HANDLING_IMPLEMENTATION != ADC_DMA_MODE_RESULT_HANDLING)
static void Adc_lUpdateResBuffer(const uint32 KernelId,\
                                 const Adc_GroupType GroupId,\
                                 const uint32 CoreId);
static void Adc_lGrpSequenceHandler(const uint32 KernelId,\
         const Adc_GroupType GroupId, const uint8 ReqSrc, const uint32 CoreId);
#if(ADC_EMUX_ENABLE == STD_ON)
static void Adc_lUpdateEmuxResBuffer(const uint32 KernelId,\
                                 const Adc_GroupType GroupId,\
                                 const uint32 CoreId);
#endif
#endif

#if (ADC_SYNC_CONV_ENABLE == STD_ON)
static void Adc_lUpdateSlaveResult(const uint32 KernelId,\
                                   const Adc_GroupType GroupId,\
                                   Adc_ValueGroupType * const CurrentResBufPtr,\
                                   const uint32 CoreId);
#endif

#if ((ADC_READ_GROUP_API == STD_ON) &&\
     (ADC_RESULT_HANDLING_IMPLEMENTATION != ADC_DMA_MODE_RESULT_HANDLING) &&\
     (ADC_SYNC_CONV_ENABLE == STD_ON))
static void Adc_lReadSlaveResult(const uint32 KernelId,\
                                 const Adc_GroupCfgType* const GrpCfgPtr,\
                                 const Adc_ValueGroupType* const ResultBufPtr,\
                                 Adc_ValueGroupType* const DataBufPtr,\
                                 const uint32 CoreId);
#endif

static void Adc_lRSEventHandler(const uint32 KernelId, const uint8 RequestSrc,\
                                const uint32 CoreId);

#if (ADC_ENABLE_LIMIT_CHECK==STD_ON)
static void Adc_lLimitChkEventHandler(const uint32 KernelId,\
          const Adc_GroupType GroupId, const uint32 CoreId, const uint8 ReqSrc);
#endif

#if (ADC_TRIGGER_ONE_CONV_ENABLE == STD_ON)
static Std_ReturnType Adc_lTriggerOneConversion(void);
#endif

#if(ADC_LOW_POWER_STATE_SUPPORT == STD_ON)
static uint8 Adc_lGetCurrentPwrState(const uint8 ServiceId,const uint32 CoreId);
#endif

/************** Local APIs for DET checks - Start**************/
#if ((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))
LOCAL_INLINE uint8 Adc_lInitDetCheck(const Adc_ConfigType * const ConfigPtr,\
                                     const uint32 CoreId);
#endif

#if (((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON)) &&\
     (ADC_RESULT_HANDLING_IMPLEMENTATION != ADC_DMA_MODE_RESULT_HANDLING))
LOCAL_INLINE uint8 Adc_lSetupResBufDetCheck(const uint32 KernelId,\
  const Adc_GroupType GroupId, const Adc_ValueGroupType * const DataBufferPtr,\
  const uint32 CoreId);
#endif

#if(((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON)) && \
                                                      (ADC_DEINIT_API ==STD_ON))
LOCAL_INLINE uint8 Adc_lDeInitDetCheck(const uint32 CoreId);
#endif

#if(((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON)) && \
                                              (ADC_STARTUP_CALIB_API == STD_ON))
LOCAL_INLINE uint8 Adc_lTrigStartupCalDetCheck(void);
#endif

#if((ADC_SAFETY_ENABLE == STD_ON) && (ADC_STARTUP_CALIB_API == STD_ON))
LOCAL_INLINE uint8 Adc_lCheckStartupCalibOngoingDet(const uint32 KernelId,\
                                                    const uint8 ServiceId);
#endif

#if(((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON)) && \
                                      (ADC_ENABLE_START_STOP_GROUP_API==STD_ON))
LOCAL_INLINE uint8 Adc_lStartGrpConvDetCheck(const uint32 KernelId,\
                             const Adc_GroupType GroupId, const uint32 CoreId);
LOCAL_INLINE uint8 Adc_lStopGrpConvDetCheck(const uint32 KernelId,\
                              const Adc_GroupType GroupId, const uint32 CoreId);
#endif

#if( ((ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
     ((MCAL_AR_VERSION == MCAL_AR_422) && (ADC_DEV_ERROR_DETECT == STD_ON))) \
      && (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) )
LOCAL_INLINE uint8 Adc_lCheckGrpPrioSwDet(const uint32 KernelId,\
                              const Adc_GroupType GroupId, const uint32 CoreId);
LOCAL_INLINE uint8 Adc_lCheckGrpPrioHwDet(const uint32 KernelId,\
                              const Adc_GroupType GroupId, const uint32 CoreId);
#endif

#if(((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON)) && \
                                                   (ADC_READ_GROUP_API==STD_ON))
LOCAL_INLINE uint8 Adc_lReadGrpDetCheck(\
       const Adc_ValueGroupType * const DataBufferPtr, const uint32 KernelId,\
       const Adc_GroupType GroupId, const uint32 CoreId);
#endif

#if((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))
LOCAL_INLINE uint8 Adc_lGetGrpStatusDetCheck(const uint32 KernelId,\
                              const Adc_GroupType GroupId, const uint32 CoreId);
#endif

#if (((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON)) &&\
     (ADC_RESULT_HANDLING_IMPLEMENTATION != ADC_DMA_MODE_RESULT_HANDLING))
LOCAL_INLINE uint8 Adc_lGetStrmPtrDetCheck(const uint32 KernelId,\
  const Adc_GroupType GroupId, Adc_ValueGroupType ** const PtrToSamplePtr,\
  const uint32 CoreId);
#endif

#if (((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON)) && \
                                           (ADC_GRP_NOTIF_CAPABILITY == STD_ON))
LOCAL_INLINE uint8 Adc_lEnGrpNotifDetCheck(const uint32 KernelId,\
                              const Adc_GroupType GroupId, const uint32 CoreId);
LOCAL_INLINE uint8 Adc_lDisGrpNotifDetCheck(const uint32 KernelId,\
                              const Adc_GroupType GroupId, const uint32 CoreId);
#endif

#if(((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON)) && \
                                                   (ADC_HW_TRIGGER_API==STD_ON))
LOCAL_INLINE uint8 Adc_lEnHwTriggerDetCheck(const uint32 KernelId,\
                               const Adc_GroupType GroupId,const uint32 CoreId);
LOCAL_INLINE uint8 Adc_lDisHwTriggerDetCheck(const uint32 KernelId,\
                              const Adc_GroupType GroupId,const uint32 CoreId);
#endif

#if((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))
LOCAL_INLINE uint8 Adc_lCheckUnInitDet(const uint8 ServiceId,\
                                       const uint32 CoreId);
#endif

#if((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))
LOCAL_INLINE uint8 Adc_lCheckParamGrpDet(const uint32 KernelId,\
       const Adc_GroupType GroupId, const uint8 ServiceId, const uint32 CoreId);
#endif

#if((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))
LOCAL_INLINE uint8 Adc_lCheckWrongTrigSrcDet(const uint32 KernelId,\
         const Adc_GroupType GroupId,const uint8 ServiceId,const uint32 CoreId);
#endif

#if(((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON)) && \
    (ADC_RESULT_HANDLING_IMPLEMENTATION != ADC_DMA_MODE_RESULT_HANDLING))
LOCAL_INLINE uint8 Adc_lCheckBufferUnInitDet(const uint32 KernelId,\
         const Adc_GroupType GroupId,const uint8 ServiceId,const uint32 CoreId);
#endif

#if((ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
     ((MCAL_AR_VERSION == MCAL_AR_422) && (ADC_DEV_ERROR_DETECT == STD_ON)))
LOCAL_INLINE uint8 Adc_lCheckGrpIdleDet(const uint32 KernelId,\
       const Adc_GroupType GroupId, const uint8 ServiceId, const uint32 CoreId);
#endif

#if((ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
     ((MCAL_AR_VERSION == MCAL_AR_422) && (ADC_DEV_ERROR_DETECT == STD_ON)))
LOCAL_INLINE uint8 Adc_lCheckGrpBusyDet(const uint32 KernelId,\
       const Adc_GroupType GroupId, const uint8 ServiceId, const uint32 CoreId);
LOCAL_INLINE uint8 Adc_lChkStartGrpConvGrpBusyDet(const uint32 KernelId,\
  const Adc_GroupType GroupId, const Adc_GlobalDataType * const KernelDataPtr,\
  const uint32 CoreId);
LOCAL_INLINE uint8 Adc_lChkEnHwTrigGrpBusyDet(const uint32 KernelId,\
  const Adc_GroupType GroupId, const Adc_GlobalDataType * const KernelDataPtr,\
  const uint32 CoreId);
#endif

#if( ((ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
     ((MCAL_AR_VERSION == MCAL_AR_422) && (ADC_DEV_ERROR_DETECT == STD_ON))) \
      && (ADC_SYNC_CONV_ENABLE == STD_ON) )
LOCAL_INLINE uint8 Adc_lCheckSlaveGrpBusyDet(const uint32 KernelId,\
                                             const Adc_GroupType GroupId,\
                                             const uint32 CoreId,\
                                             const uint8 ApiId);
#endif

#if(((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON)) && \
                                            (ADC_GRP_NOTIF_CAPABILITY ==STD_ON))
LOCAL_INLINE uint8 Adc_lCheckNotifCapableDet(const uint32 KernelId,\
       const Adc_GroupType GroupId, const uint8 ServiceId, const uint32 CoreId);
#endif

#if(((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON)) && \
                                                   (ADC_HW_TRIGGER_API==STD_ON))
LOCAL_INLINE uint8 Adc_lCheckWrongConvModeDet(const uint32 KernelId,\
       const Adc_GroupType GroupId, const uint8 ServiceId, const uint32 CoreId);
#endif

#if((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))
LOCAL_INLINE uint8 Adc_lCheckParamPointerDet( const void * const Ptr,\
                                              const uint8 ServiceId );
#endif

#if(((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON)) && \
                                        (ADC_LOW_POWER_STATE_SUPPORT == STD_ON))
LOCAL_INLINE uint8 Adc_lPreparePowerStateDetCheck(\
     const Adc_PowerStateType PowerState,\
     Adc_PowerStateRequestResultType * const Result,const uint32 CoreId);
LOCAL_INLINE uint8 Adc_lSetPowerStateDetCheck(\
            Adc_PowerStateRequestResultType * const Result,const uint32 CoreId,\
            const uint32 TargetPwrState);
LOCAL_INLINE uint8 Adc_lGetPowerStateDetCheck(\
                     const Adc_PowerStateType * const PowerState,\
                     Adc_PowerStateRequestResultType * const Result,
                     const uint8 ServiceId,  const uint32 CoreId);
LOCAL_INLINE uint8 Adc_lCheckPowerStateNotSuppDet(\
                const Adc_PowerStateType PowerState,const uint8 ServiceId );
LOCAL_INLINE uint8 Adc_lCheckPeripheralPreparedDet(const uint32 TargetPwrState,\
                                                   const uint8 ServiceId);
LOCAL_INLINE uint8 Adc_lCheckConverterOffDet(const uint32 KernelId,\
                                             const uint8 ServiceId);
#endif

#if( ((ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
     ((MCAL_AR_VERSION == MCAL_AR_422) && (ADC_DEV_ERROR_DETECT == STD_ON))) \
      && (ADC_LOW_POWER_STATE_SUPPORT == STD_ON) )
LOCAL_INLINE uint8 Adc_lCheckHwUnitDisEngagedDet(const uint8 ServiceId,\
                                                 const uint32 CoreId);
#endif

#if((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))
static void Adc_lReportError(const uint8 ApiId, const uint8 ErrorId);
#endif

#if( (ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
     ((MCAL_AR_VERSION == MCAL_AR_422) && (ADC_DEV_ERROR_DETECT == STD_ON)) )
static void Adc_lReportRuntimeDetError(const uint8 ApiId, const uint8 ErrorId);
#endif

#if( (ADC_MULTICORE_ERROR_DETECT == STD_ON) || \
     ((ADC_SAFETY_ENABLE == STD_ON) && (MCAL_NO_OF_CORES > ADC_ONE_U)) )
static void Adc_lReportMulticoreError(const uint8 ApiId, const uint8 ErrorId);
#endif

#if ((ADC_CLC_FAILURE_DEM_NOTIF == ADC_ENABLE_DEM_REPORT)||\
     (ADC_CONV_STOP_TIME_DEM_NOTIF == ADC_ENABLE_DEM_REPORT))
static void Adc_lReportDemError(const Dem_EventIdType EventId,
const Dem_EventStatusType EventStatus);
#endif

/********************* Local APIs for Init Check - Start***********************/
#if (ADC_INIT_CHECK_API == STD_ON)
LOCAL_INLINE Std_ReturnType Adc_lInitCheck(const uint32 CoreId);
LOCAL_INLINE uint32 Adc_lCheckKernelSfr(\
             const Adc_HwUnitCfgType *const KernelCfgPtr, \
             const uint32 KernelId, const uint32 CompareFlag);
LOCAL_INLINE uint32 Adc_lCheckGlobalSfr(const uint32 CompareFlag);
LOCAL_INLINE uint32 Adc_lCheckGlobalCoreVars(const uint32 CoreId, \
                                             const uint32 CompareFlag);
#endif

#if ((ADC_HW_TRIGGER_API == STD_ON) && (ADC_INIT_CHECK_API == STD_ON))
#if (ADC_GTM_AVAILABLE == STD_ON)
LOCAL_INLINE uint32 Adc_lCheckGtmSfr (\
                   const Adc_HwUnitCfgType *const KernelCfgPtr, \
                   const uint32 CompareFlag);
#endif
LOCAL_INLINE uint32 Adc_lCheckEruSfr (\
            const Adc_HwUnitCfgType *const KernelCfgPtr, \
            const uint32 CompareFlag);
LOCAL_INLINE uint32 Adc_lCheckEruChannelDeInit(\
                     const Adc_EruChannelCfgType * const EruChannelCfgPtr, \
                     const uint32 CompareFlag);
#endif
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
Code Memory section naming as per AS
[/cover]*/
#define ADC_STOP_SEC_CODE_ASIL_B_GLOBAL
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Adc_MemMap.h"

/************** Local APIs for DET checks - End**************/

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
/*[cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
Variables Memory section as per AS
[/cover]*/
#if (ADC_KERNEL_USED_COUNT_CORE0 > 0U)
#define ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE0_UNSPECIFIED
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Adc_MemMap.h"
static Adc_GlobalDataType Adc_KernelData_Core0[ADC_KERNEL_USED_COUNT_CORE0];

#define ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_UNSPECIFIED
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Adc_MemMap.h"
#endif

#if (MCAL_NO_OF_CORES > 1U)
#if (ADC_KERNEL_USED_COUNT_CORE1 > 0U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE1_UNSPECIFIED
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Adc_MemMap.h"
static Adc_GlobalDataType Adc_KernelData_Core1[ADC_KERNEL_USED_COUNT_CORE1];

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_UNSPECIFIED
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Adc_MemMap.h"
#endif
#endif

#if (MCAL_NO_OF_CORES > 2U)
#if (ADC_KERNEL_USED_COUNT_CORE2 > 0U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE2_UNSPECIFIED
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Adc_MemMap.h"
static Adc_GlobalDataType Adc_KernelData_Core2[ADC_KERNEL_USED_COUNT_CORE2];

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_UNSPECIFIED
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Adc_MemMap.h"
#endif
#endif

#if (MCAL_NO_OF_CORES > 3U)
#if (ADC_KERNEL_USED_COUNT_CORE3 > 0U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE3_UNSPECIFIED
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Adc_MemMap.h"
static Adc_GlobalDataType Adc_KernelData_Core3[ADC_KERNEL_USED_COUNT_CORE3];

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_UNSPECIFIED
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Adc_MemMap.h"
#endif
#endif

#if (MCAL_NO_OF_CORES > 4U)
#if (ADC_KERNEL_USED_COUNT_CORE4 > 0U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE4_UNSPECIFIED
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Adc_MemMap.h"
static Adc_GlobalDataType Adc_KernelData_Core4[ADC_KERNEL_USED_COUNT_CORE4];

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_UNSPECIFIED
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Adc_MemMap.h"
#endif
#endif

#if (MCAL_NO_OF_CORES > 5U)
#if (ADC_KERNEL_USED_COUNT_CORE5 > 0U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define ADC_START_SEC_VAR_CLEARED_ASIL_B_CORE5_UNSPECIFIED
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Adc_MemMap.h"
static Adc_GlobalDataType Adc_KernelData_Core5[ADC_KERNEL_USED_COUNT_CORE5];

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define ADC_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_UNSPECIFIED
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Adc_MemMap.h"
#endif
#endif

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define ADC_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Adc_MemMap.h"

static const Adc_ConfigType *Adc_ConfigPtr;

#if((ADC_DEV_ERROR_DETECT == STD_ON) || \
    (ADC_SAFETY_ENABLE == STD_ON) || \
    (ADC_INIT_CHECK_API == STD_ON))
static Adc_InitStateType Adc_InitStatus[MCAL_NO_OF_CORES];
#endif

#if(ADC_STARTUP_CALIB_API == STD_ON)
static uint32 Adc_StartupCalStatus;
#endif

#if(ADC_LOW_POWER_STATE_SUPPORT == STD_ON)
static uint32 Adc_PowerStateTransitionRequestBit;
#endif

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define ADC_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Adc_MemMap.h"
/*[cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
Variables Memory section as per AS
[/cover]*/

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
Constant Memory section as per AS
[/cover]*/
#define ADC_START_SEC_CONST_ASIL_B_GLOBAL_8
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline.*/
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Adc_MemMap.h"
/*MISRA2012_RULE_8_9_JUSTIFICATION: Variable not defined at block scope.
The size of this array is derived from a configuration constant.
The function uses this returns the address of this variable,
and the content of the variable is changed from different APIs'*/
static const uint8 Adc_kKernelDataIndex[MCAL_NO_OF_CORES][ADC_MAX_KERNEL_ID] =\
{
  { ADCX_KERNEL_INDEX_CORE0 }
  #if (MCAL_NO_OF_CORES > 1U)
  , { ADCX_KERNEL_INDEX_CORE1 }
  #endif
  #if (MCAL_NO_OF_CORES > 2U)
  , { ADCX_KERNEL_INDEX_CORE2 }
  #endif
  #if (MCAL_NO_OF_CORES > 3U)
  , { ADCX_KERNEL_INDEX_CORE3 }
  #endif
  #if (MCAL_NO_OF_CORES > 4U)
  , { ADCX_KERNEL_INDEX_CORE4 }
  #endif
  #if (MCAL_NO_OF_CORES > 5U)
  , { ADCX_KERNEL_INDEX_CORE5 }
  #endif
};

/*MISRA2012_RULE_8_9_JUSTIFICATION: This constant cannot be defined at block
scope, since it is used in multiple functions. Also, since memmap pragmas cannot
be used at block scope it is necessary to keep this declaration at file scope.*/
static const uint8 Adc_kKernelUsedCount[MCAL_NO_OF_CORES] =
{
  ADC_KERNEL_USED_COUNT_CORE0
  #if (MCAL_NO_OF_CORES > 1U)
  , ADC_KERNEL_USED_COUNT_CORE1
  #endif
  #if (MCAL_NO_OF_CORES > 2U)
  , ADC_KERNEL_USED_COUNT_CORE2
  #endif
  #if (MCAL_NO_OF_CORES > 3U)
  , ADC_KERNEL_USED_COUNT_CORE3
  #endif
  #if (MCAL_NO_OF_CORES > 4U)
  , ADC_KERNEL_USED_COUNT_CORE4
  #endif
  #if (MCAL_NO_OF_CORES > 5U)
  , ADC_KERNEL_USED_COUNT_CORE5
  #endif
};
/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
Constant Memory section as per AS
[/cover]*/
#define ADC_STOP_SEC_CONST_ASIL_B_GLOBAL_8
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Adc_MemMap.h"

/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
Constant Memory section as per AS
[/cover]*/
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define ADC_START_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline.*/
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Adc_MemMap.h"
static Adc_GlobalDataType * const Adc_kKernelData[MCAL_NO_OF_CORES] =
{
  #if (ADC_KERNEL_USED_COUNT_CORE0 > 0U)
  &Adc_KernelData_Core0[0U]
  #else
  (Adc_GlobalDataType*)0U
  #endif
  #if (MCAL_NO_OF_CORES > 1U)
  #if (ADC_KERNEL_USED_COUNT_CORE1 > 0U)
  , &Adc_KernelData_Core1[0U]
  #else
  , (Adc_GlobalDataType*)0U
  #endif
  #endif
  #if (MCAL_NO_OF_CORES > 2U)
  #if (ADC_KERNEL_USED_COUNT_CORE2 > 0U)
  , &Adc_KernelData_Core2[0U]
  #else
  , (Adc_GlobalDataType*)0U
  #endif
  #endif
  #if (MCAL_NO_OF_CORES > 3U)
  #if (ADC_KERNEL_USED_COUNT_CORE3 > 0U)
  , &Adc_KernelData_Core3[0U]
  #else
  , (Adc_GlobalDataType*)0U
  #endif
  #endif
  #if (MCAL_NO_OF_CORES > 4U)
  #if (ADC_KERNEL_USED_COUNT_CORE4 > 0U)
  , &Adc_KernelData_Core4[0U]
  #else
  , (Adc_GlobalDataType*)0U
  #endif
  #endif
  #if (MCAL_NO_OF_CORES > 5U)
  #if (ADC_KERNEL_USED_COUNT_CORE5 > 0U)
  , &Adc_KernelData_Core5[0U]
  #else
  , (Adc_GlobalDataType*)0U
  #endif
  #endif
};

/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
Constant Memory section as per AS
[/cover]*/
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define ADC_STOP_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Adc_MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
Code Memory section naming as per AS
[/cover]*/
/*[cover parentID={BA6EFE0D-B9E6-4630-BF56-93FFA7D4CB7F}]
Code Memory section executable by all cores
[/cover]*/
#define ADC_START_SEC_CODE_ASIL_B_GLOBAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Adc_MemMap.h"
/*******************************************************************************
** Traceability: [cover parentID={71F84EBA-6E78-4178-8A14-339C88B58F59},
                                 {BA6EFE0D-B9E6-4630-BF56-93FFA7D4CB7F}]      **
**                                                                            **
** Syntax           : void Adc_Init                                           **
**                    (                                                       **
**                      const Adc_ConfigType * const ConfigPtr                **
**                    )                                                       **
**                                                                            **
** Description      : This API initializes the ADC hardware units and clear   **
**                    global variables to their reset state. The SFRs of the  **
**                    configured kernels are first reset to default values and**
**                    then initialized as per the configuration.              **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x00                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different CPU core                        **
**                                                                            **
** Parameters(in)   : ConfigPtr - Pointer to ADC configuration Set            **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : void                                                    **
**                                                                            **
*******************************************************************************/
void Adc_Init(const Adc_ConfigType * const ConfigPtr)
{
  uint32 lClcReadBack;
  uint32 lCoreId;
  uint32 lClcDemErr = 0U;

  /* [cover parentID={265B2B2A-70F9-4640-8FF7-B4DFF47A79FC}]
  DET is ON or SAFETY is ON [/cover] */
  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))
  uint8 lDetVal;
  #endif

  /* Get the core Id from which it is called */
  lCoreId = Mcal_GetCpuIndex();

  /* [cover parentID={265B2B2A-70F9-4640-8FF7-B4DFF47A79FC}]
  DET is ON or SAFETY is ON [/cover] */
  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))
  /* Check DET's for the API */
  lDetVal = Adc_lInitDetCheck(ConfigPtr, lCoreId);
  /* [cover parentID={0F45BB53-CBC2-4ea9-A568-68B0DCBC9FD6}]
  Init DET Error occured [/cover] */
  if(ADC_E_NO_ERR == lDetVal)
  #endif
  {
    /* [cover parentID={B0535324-DA26-4b89-B672-BB4B60F5F2CE}]
    Is CoreId is equal to Master CoreId [/cover] */
    if (MCAL_MASTER_COREID == lCoreId)
    {
      /* [cover parentID={43914327-20BF-482c-90FA-8640C7819CF1}]
      Enable module clock via CLC [/cover] */
      ADC_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(&MODULE_EVADC.CLC, \
          ((uint32)ADC_SLEEP_MODE_CFG << IFX_EVADC_CLC_EDIS_OFF));

      /* Time required to set Safety Endinit should be sufficient for CLC
       to be enabled*/
      lClcReadBack = (uint32)MODULE_EVADC.CLC.U;

      /* [cover parentID={DCB12A31-B477-4f5d-B9BE-622F30A22561}]
         Clock Enabled [/cover] */
      if((lClcReadBack &\
          ((uint32)IFX_EVADC_CLC_DISS_MSK << IFX_EVADC_CLC_DISS_OFF)) == \
          (uint32)0U)
      {
        /* [cover parentID={9AE22EA1-E7A0-4bf4-8070-4463F89E2F22}]
           Production Error NOTIFY is ON or SAFETY is ON [/cover] */
        #if (ADC_CLC_FAILURE_DEM_NOTIF == ADC_ENABLE_DEM_REPORT)
        /* [cover parentID={3ED1D538-A90C-47be-937A-E329380EACC9}]
        Report Production error PASS when CLC enabling is successful [/cover] */
        Adc_lReportDemError(ADC_E_CLC_FAILURE, DEM_EVENT_STATUS_PASSED);
        #endif
        /* Store the config pointer passed */
        Adc_ConfigPtr = ConfigPtr;
      }
      else
      {
        #if (ADC_CLC_FAILURE_DEM_NOTIF == ADC_ENABLE_DEM_REPORT)
        /* [cover parentID={260003D2-19DE-4254-B9CD-CBE0CED64AEC}]
        Report Production error FAIL when CLC enabling fails [/cover] */
        Adc_lReportDemError(ADC_E_CLC_FAILURE, DEM_EVENT_STATUS_FAILED);
        #endif
        lClcDemErr = (uint32)ADC_ONE_U;
      }
    }
    /* [cover parentID={5E3D5269-76D2-4513-BDDE-A8C7133D22C4}]
    Production Error [/cover] */
    if(0U == lClcDemErr)
    {
      /* [cover parentID={163DEC39-F738-41af-BA81-9C2989887BEA}]
         Initialize Module(Initialize all kernels on slave cores) [/cover] */
      Adc_lInit(lCoreId);

      /* [cover parentID={D7A46752-B8C0-451b-B12D-DB11CF2D43F2}]
      DET is ON or SAFETY is ON or InitCheck is ON [/cover] */
      #if((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON) ||\
           (ADC_INIT_CHECK_API == STD_ON))
      /* [cover parentID={38B9C750-90E1-416a-8103-3C3C6DA6A951}]
      Set Driver state to Initialized after complete intialization is done
      [/cover] */
      Adc_InitStatus[lCoreId] = ADC_INITIALIZED;
      #endif
    }
  }
}

#if (ADC_INIT_CHECK_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={17FDEC48-F0CE-4e73-84BE-035E6D26D973},
                                 {BA6EFE0D-B9E6-4630-BF56-93FFA7D4CB7F}]      **
**                                                                            **
** Syntax           : Std_ReturnType Adc_InitCheck                            **
**                    (                                                       **
**                      const Adc_ConfigType * const ConfigPtr                **
**                    )                                                       **
**                                                                            **
** Description      : This API returns the status of the modules              **
**                    initialization in context to the core from where the    **
**                    API is invoked. The API is available when safety is     **
**                    enabled or initialization check is explicitly enabled   **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x32                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different CPU core                        **
**                                                                            **
** Parameters(in)   : ConfigPtr - Pointer to ADC configuration Set            **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK: Initialization verification passed                **
**                    E_NOT_OK: Initialization verification failed            **
**                                                                            **
*******************************************************************************/
Std_ReturnType Adc_InitCheck(const Adc_ConfigType * const ConfigPtr)
{
  Std_ReturnType lRetVal;
  uint32 lCoreId, lSfrVal, lCfgVal;
  uint32 lCompareFlag = 0xFFFFFFFFU;

  /* Get the core Id from which it is called */
  lCoreId = Mcal_GetCpuIndex();

  /* [cover parentID={08AB50A2-7A67-4897-8791-1F5AD50EDF45}]
  Config Ptr is NULL or ADC module is not initialized [/cover] */
  if((ConfigPtr == NULL_PTR) || (Adc_InitStatus[lCoreId] != ADC_INITIALIZED))
  {
    /* Update E_NOT_OK if Configuration pointer is NULL pointer */
    lRetVal = E_NOT_OK;
  }
  else
  {
    /* [cover parentID={4ECC285C-8347-415b-8AE9-74F960574971}]
    Compare global clock control register with configuration value & Update
    flag as per result [/cover] */
    lSfrVal = ((uint32)MODULE_EVADC.CLC.U);
    lCfgVal = ((uint32)ADC_SLEEP_MODE_CFG << IFX_EVADC_CLC_EDIS_OFF);
    lCompareFlag &= ~(lSfrVal ^ lCfgVal);

    /* [cover parentID={481847AE-B054-477f-B64A-C5F2B4721CA1}]
    Is global clock control regiter initialized properly [/cover] */
    if (lCompareFlag == 0xFFFFFFFFU)
    {
      /* [cover parentID={33F11E5D-0539-4d40-842A-DA5E3DA0F3E6}]
      Perform Initialization check for all kernels on slave cores [/cover] */
      lRetVal = Adc_lInitCheck(lCoreId);
    }
    else
    {
      /* [cover parentID={EFD20EAF-760A-4aba-A712-7F7F9ADDD92C}]
      Update return value with E_NOT_OK [/cover] */
      lRetVal = E_NOT_OK;
    }
  }
  return(lRetVal);
}
#endif

#if(ADC_RESULT_HANDLING_IMPLEMENTATION != ADC_DMA_MODE_RESULT_HANDLING)
/*******************************************************************************
** Traceability: [cover parentID={71C95AFB-3C66-4bb7-A52E-7A871CE34B6C},
                                 {BA6EFE0D-B9E6-4630-BF56-93FFA7D4CB7F}]      **
**                                                                            **
** Syntax           : Std_ReturnType Adc_SetupResultBuffer                    **
**                    (                                                       **
**                      const Adc_GroupType Group,                            **
**                      const Adc_ValueGroupType *const DataBufferPtr         **
**                    )                                                       **
**                                                                            **
** Description      : This API sets up the start address of group specific    **
**                    result buffers, where the conversion results will be    **
**                    stored. The application has to ensure that the          **
**                    application buffer, where DataBufferPtr points to, can  **
**                    hold all the conversion results of the specified group. **
**                    Note: This API is not available when                    **
**                    AdcResultHandlingImplementation is set to DMA mode of   **
**                    result handling. In this scenario the start of the      **
**                    application result buffer is provided via DMA channels  **
**                    destination address.                                    **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x0C                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : Group - Numeric ID of requested ADC channel group.,     **
**                  DataBufferPtr - Pointer to the start of result data buffer**
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : Std_ReturnType                                          **
**                                                                            **
*******************************************************************************/
Std_ReturnType Adc_SetupResultBuffer(const Adc_GroupType Group,\
                                const Adc_ValueGroupType * const DataBufferPtr)
{
  Adc_GlobalDataType *lKernelDataPtr;
  Std_ReturnType lRetVal;
  uint32 lKernelId, lCoreId;
  Adc_GroupType lGroupId;
  #if((ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
     (ADC_DEV_ERROR_DETECT == STD_ON))
  uint8 lErrVal;
  #endif
  
  /* Get the core Id from which it is called */
  lCoreId = Mcal_GetCpuIndex();

  /* Extract Kernel ID from Group */
  lKernelId = Adc_lGetAdcKernel(Group);
  /* Extract Kernel specific GroupID from Group*/
  lGroupId = Adc_lGetKernelGroupId(Group);

  /* [cover parentID={C4FA5630-B542-4d4e-A511-5E3D858A0872}]
  DET is ON or SAFETY is ON [/cover] */
  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))
  /* Check DET's for the API */
  lErrVal = Adc_lSetupResBufDetCheck(lKernelId,lGroupId,DataBufferPtr,lCoreId);
  /* [cover parentID={3E1EB63D-A4FF-4308-9D51-DA8792EE97AB}]
  DET or Safety Error Occured [/cover] */
  if(ADC_E_NO_ERR != lErrVal)
  {
    /* [cover parentID={05F4AF9B-F7AD-4e27-A7E5-3102F3BEEE59}]
    Return value as E_NOT_OK  [/cover] */
    lRetVal = E_NOT_OK;
  }
  else
  #endif
  {
    /* [cover parentID={0748CF11-2366-498e-8A2F-DF2E61C8E666}]
    DET is ON for AUTOSAR version 4.2.2 or SAFETY is ON or Runtime Error
    Detection is ON [/cover] */
    #if((ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
        ((MCAL_AR_VERSION == MCAL_AR_422) && (ADC_DEV_ERROR_DETECT == STD_ON)))
    /* Group should be IDLE mode to set up the result buffer*/
    /* [cover parentID={0C8821B8-6060-4357-A28B-CC4E3E758829},
    {184D4C05-26C3-48f1-9F79-00A963B97CB1}] Start of Critcal Section [/cover] */
    SchM_Enter_Adc_KernelData();

    /* Check Group Busy Development or Safety or Runtime Error */
    lErrVal = Adc_lCheckGrpBusyDet(lKernelId, lGroupId, \
                                 ADC_SID_SETUP_RESULT_BUFFER, lCoreId);
    /* [cover parentID={32D4AD11-D8C4-4e2e-B459-765AF13034B6}]
    DET Error or Safety Error or Runtime Error Occured [/cover] */
    if(ADC_E_NO_ERR != lErrVal)
    {
      /* [cover parentID={B177E473-BA16-4f24-9C30-4A7F0E54E39D}]
      End of Critical Section [/cover] */
      SchM_Exit_Adc_KernelData();
      
      /* [cover parentID={05F4AF9B-F7AD-4e27-A7E5-3102F3BEEE59}]
      Return value as E_NOT_OK  [/cover] */
      lRetVal = E_NOT_OK;
    }
    else
    #endif
    {
      /* Get global state data location for the Kernel */
      lKernelDataPtr = Adc_lGetKernelDataAddress(lKernelId, lCoreId);

      /*Since the group result pointer and No of valid conversion are
      updated in ISR, they are accessed under critical section*/
      /* [cover parentID={C42C87AC-7CDC-48db-A190-A366A337A3EC}]
      Critical Section   [/cover] */
      /* AUTOSAR version is 4.2.2 */
      #if (MCAL_AR_VERSION == MCAL_AR_422)
      /* [cover parentID={C942C156-DD60-4cfd-8DD0-56048F102B70}]
      DET is OFF and Safety is OFF when Autosar version is 4.2.2 [/cover] */
      #if((ADC_SAFETY_ENABLE == STD_OFF) && (ADC_DEV_ERROR_DETECT == STD_OFF))
      /* [cover parentID={DA73DEAE-5FA5-455a-898A-8EA4AC80FFE2}]
      Start of Critical Section [/cover] */
          SchM_Enter_Adc_KernelData();
      #endif
      /* AUTOSAR version is 4.4.0 */
      #else
      /* [cover parentID={C942C156-DD60-4cfd-8DD0-56048F102B70}]
      Runtime error detection is OFF and Safety is OFF when Autosar version is
      4.4.0 [/cover] */
      #if((ADC_SAFETY_ENABLE==STD_OFF) && (ADC_RUNTIME_ERROR_DETECT==STD_OFF))
      /* [cover parentID={DA73DEAE-5FA5-455a-898A-8EA4AC80FFE2}]
      Start of Critical Section [/cover] */
          SchM_Enter_Adc_KernelData();
      #endif
      #endif

      /* MISRA2012_RULE_11_8_JUSTIFICATION: The address of the buffer pointer
      is received as a const, so that it cannot be modified in the APIs context.
      The address is stored to a pointer variable, and the pointer is later used
      in the ISR to update the results to the intial buffer address passed.
      Hence, the pointer variable cannot be made as a pointer to a const and the
      type cast is required*/
      /* [cover parentID={D295EE51-F0BC-4526-AE5A-E8D808B18F72}]
      Initialize the Result buffer pointer in the Kernel data pointer with
      buffer address passed [/cover] */
      lKernelDataPtr->GrpResBuffer[lGroupId] \
       = (Adc_ValueGroupType *)DataBufferPtr;
      /* Reset Next Buffer Position and Valid Result count to 0*/
      lKernelDataPtr->NumofValidConRes[lGroupId] = (Adc_StreamNumSampleType)0U;

      /* [cover parentID={CA863247-EC61-44e5-BA74-EDDD2A2F9519}]
      End of Critical Section [/cover] */
      SchM_Exit_Adc_KernelData();

      /* [cover parentID={FA7C9F21-8DC6-4d1f-AFE3-4CE8DFEEF8D4}]
      Return value as E_OK  [/cover] */
      lRetVal = E_OK;
    }
  }
  return(lRetVal);
}
#endif

#if (ADC_DEINIT_API == STD_ON)
/*CYCLOMATIC_Adc_DeInit_JUSTIFICATION: This API resets all SFRs of the kernels
configured by Adc_Init to their reset states and performs the DET or Safety or
Multi-core DET or Runtime Error check for AR422 and AR440 based on the enable
of pre-compile macros. The different if conditions cause the complexity to
increase, but actually during run-time out of all if conditions many will be
pre-compile time removed*/
/*******************************************************************************
** Traceability: [cover parentID={D9AF4C1E-0A23-422b-BA5D-C5AC306804D6},
                                 {BA6EFE0D-B9E6-4630-BF56-93FFA7D4CB7F}]      **
**                                                                            **
** Syntax           : void Adc_DeInit                                         **
**                    (                                                       **
**                      void                                                  **
**                    )                                                       **
**                                                                            **
** Description      : This API resets all SFRs of the kernels                 **
**                    configured by Adc_Init to their reset states. It also   **
**                    resets the global SFR's (common to all Kernels) of the  **
**                    EVADC IP.                                               **
**                    Note: SFRs of kernels not configured by Adc_Init are    **
**                    not de-initialized by this API                          **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x01                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different CPU core                        **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : void                                                    **
**                                                                            **
*******************************************************************************/
void Adc_DeInit(void)
{

  uint32 lKernelCount, lCoreId;
  #if((ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
     (ADC_DEV_ERROR_DETECT == STD_ON))
  uint8 lErrVal;
  #endif
  
  /* Get the core Id from which it is called */
  lCoreId = Mcal_GetCpuIndex();

  /* [cover parentID={74107589-AA9E-4602-B8FD-77A09A071DB8}]
  DET is ON or SAFETY is ON [/cover] */
  #if((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))
  /* Check DET's for the API */
  lErrVal = Adc_lDeInitDetCheck(lCoreId);
  /* [cover parentID={3F5A3FD1-8A86-47f8-9EB5-2CE3122062F1}]
  DET Error Occured  [/cover] */
  if(ADC_E_NO_ERR == lErrVal)
  #endif
  {
    /* [cover parentID={3EEB6BC4-5154-4769-92EC-5D2887C311DF}]
    DET is ON for AUTOSAR version 4.2.2 or SAFETY is ON or Runtime Error
    Detection is ON [/cover] */
    #if((ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
        ((MCAL_AR_VERSION == MCAL_AR_422) && (ADC_DEV_ERROR_DETECT == STD_ON)))
    /* [cover parentID={813CE5A2-A62C-481b-95A0-C06467FF15B5}]
    Check Group Busy Development or Runtime Error [/cover] */
    lErrVal = Adc_lCheckGrpBusyDet((uint32)0U, (Adc_GroupType)0U, \
                                   ADC_SID_DEINIT, lCoreId);
    /* [cover parentID={0C748293-212B-4db9-987A-A2BE108F6E82}]
    Error Occured  [/cover] */
    if(ADC_E_NO_ERR == lErrVal)
    #endif
    {
      /* [cover parentID={0B994985-FF23-40d5-BA48-AA1402CE5936}]
      InitCheck is ON [/cover] */
      #if((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON) ||\
           (ADC_INIT_CHECK_API == STD_ON))
      /* [cover parentID={4610E680-11B9-445e-AACA-DE381AF68623}]
      Set driver state to uninitialization started  [/cover] */
      Adc_InitStatus[lCoreId] = ADC_UNINIT_STARTED;
      #endif
      /* [cover parentID={A039D7F2-BF9F-4b72-9F2A-3C053ED8B417}]
      Till the last available Kernel [/cover] */
      for(lKernelCount = (uint32)0U; lKernelCount < ADC_MAX_KERNEL_ID; \
          lKernelCount++)
      {
        /* [cover parentID={DF5B2276-B58A-4d33-A1E8-0F499DE4817E}]
        Check if Kernel is Configured   [/cover] */
        if(Adc_ConfigPtr->CoreCfgPtr[lCoreId]->HwUnitCfgPtr[lKernelCount] != \
            NULL_PTR)
        {
          /* [cover parentID={8D0724BF-AD7C-4f3c-BE10-D2BFC02F535A}]
          De-Initialize the Kernels  [/cover] */
          Adc_lKernelDeInit(Adc_ConfigPtr->CoreCfgPtr[lCoreId]->\
                            HwUnitCfgPtr[lKernelCount], lKernelCount);
        }
      }
      
      Adc_lResetCoreGlobalVars(lCoreId);
      
      /* [cover parentID={A4EC70D5-D95E-4d22-9957-F3109043EBF6}]
      Is CoreId is equal to Master CoreId  [/cover] */
      if (MCAL_MASTER_COREID == lCoreId)
      {
        Adc_lResetGlobalSfr();
        /* [cover parentID={F0F424B3-F905-448c-9E3C-4EA662D0968D}]
        Disable the Module clock [/cover] */
        ADC_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(&MODULE_EVADC.CLC,\
                         ((uint32)ADC_CLC_DEFAULT_VALUE));
      
        /* Store Config pointer locally & Reset Config pointer to NULL */
        Adc_ConfigPtr = NULL_PTR;
      
        /* [cover parentID={CF45F919-D987-49a5-B581-368572475EC3}]
        ADC StartUp Calib API is ON [/cover] */
        #if (ADC_STARTUP_CALIB_API == STD_ON)
        /* [cover parentID={66ED1E1A-B9D4-4591-A122-F22588CB474C}]
        Clear Start-up Calibration status   [/cover] */
        Adc_lClrStartupCalStatusAtomic();
        #endif
      }
      
      /* [cover parentID={77CC7F2A-640E-46ef-983E-53B31D538FD7}]
      DET is on or Safety is on or InitCheck is ON [/cover] */
      #if ((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON) ||\
           (ADC_INIT_CHECK_API == STD_ON))
      /* [cover parentID={23F60A58-3CC8-41a4-8F83-6CFE1C0815CA}]
      Set driver state to uninitialization completed  [/cover] */
      Adc_InitStatus[lCoreId] = ADC_UNINIT_COMPLETED;
      #endif
    }
  }
}
#endif

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={418D22C8-F770-43f0-81B4-E682075DB2FB},
                                 {BA6EFE0D-B9E6-4630-BF56-93FFA7D4CB7F}]      **
**                                                                            **
** Syntax           : void Adc_StartGroupConversion                           **
**                    (                                                       **
**                      const Adc_GroupType Group                             **
**                    )                                                       **
**                                                                            **
** Description      : This API setups the group for conversion and starts the **
**                    conversion of the requested ADC Channel group           **
**                    Note: This API is available only when                   **
**                    AdcEnableStartStopGroupApi is configured as true.       **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x02                                                    **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant for channel groups executing on different     **
**                    ADC hardware groups                                     **
**                                                                            **
** Parameters(in)   : Group - Numeric ID of requested ADC Channel group.      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : void                                                    **
**                                                                            **
*******************************************************************************/
void Adc_StartGroupConversion(const Adc_GroupType Group)
{
  uint32 lKernelId;
  uint32 lCoreId;
  Adc_GroupType lGroupId;
  #if((ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
     (ADC_DEV_ERROR_DETECT == STD_ON))
  uint8 lErrVal;
  #endif
  
  /* Get the core Id from which it is called */
  lCoreId = Mcal_GetCpuIndex();

  /* Extract Kernel ID from Group */
  lKernelId = Adc_lGetAdcKernel(Group);
  /* Extract Kernel specific GroupID from Group*/
  lGroupId = Adc_lGetKernelGroupId(Group);

  /* [cover parentID={DCAEA4B1-7EF7-4faa-A4D4-92FBDB7EF1EC}]
  DET is ON or SAFETY is ON [/cover] */
  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))
  /* Check DET's for the API */
  lErrVal = Adc_lStartGrpConvDetCheck(lKernelId, lGroupId, lCoreId);
  /* [cover parentID={0FD80C79-2495-4a40-8FC1-FF8FC4D7F58B}]
  Start Group Conversion DET Error [/cover] */
  if(ADC_E_NO_ERR == lErrVal)
  #endif
  {
    /* [cover parentID={6985491E-5295-4f78-99E7-AFBBD2AA4161}]
    DET is ON for AUTOSAR version 4.2.2 or SAFETY is ON or Runtime Error
    Detection is ON [/cover] */
    #if((ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
        ((MCAL_AR_VERSION == MCAL_AR_422) && (ADC_DEV_ERROR_DETECT == STD_ON)))
    /* [cover parentID={E429EE92-D946-4277-BBDD-0C2730124703}]
    Critical Section [/cover] */
    /* [cover parentID={C2F4CCFB-3F72-4022-98BF-91CB610407B2}]
    Start of Critical Section [/cover] */
    SchM_Enter_Adc_KernelData();
    /* [cover parentID={0D36E639-7F77-45c4-ABCC-0877ACCE83A6}]
    Check Group Busy Development or Runtime Error [/cover] */
    lErrVal = Adc_lCheckGrpBusyDet(lKernelId, lGroupId, \
                                   ADC_SID_START_GROUP_CONVERSION, lCoreId);
    /* [cover parentID={33ED6712-5BBD-45d0-957E-2F73F9D44BEB}]
    Group Busy DET Error or Runtime Error occurred  [/cover] */
    if(ADC_E_NO_ERR != lErrVal)
    {
      /* [cover parentID={03F1F210-F323-480c-BD91-A59042F8078B}]
      End of Critical Section - DET Fails   [/cover] */
      SchM_Exit_Adc_KernelData();
    }
    else
    #endif
    {
      /* [cover parentID={DDBC41ED-57D8-40dd-A755-093C4D882733}]
      Is QUEUE mode is ON or Prioirty mode is ON? [/cover] */
      /* [cover parentID={F2316B53-0A22-46f6-92F3-3A6D00F5347A}]
      Priority is ON or Queueing Mode is ON [/cover] */
      /* [cover parentID={0F8BD0DA-0610-4000-BA24-345BF5CF286C}]
      Critical Section   [/cover] */
      #if((ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) ||\
        (ADC_ENABLE_QUEUING == STD_ON))
      /* AUTOSAR version is 4.2.2 */
      #if (MCAL_AR_VERSION == MCAL_AR_422)
      /* [cover parentID={FD9EAFBA-FD62-44f6-931F-6136F02FFE81}]
      DET is OFF and Safety is OFF when Autosar version is 4.2.2 [/cover] */
      #if((ADC_SAFETY_ENABLE == STD_OFF) && (ADC_DEV_ERROR_DETECT == STD_OFF))
      /* [cover parentID={0809F1F3-E9D6-4cbe-B3BB-AB712BCB05F2}]
      Start of Critical Section [/cover] */
          SchM_Enter_Adc_KernelData();
      #endif
      /* AUTOSAR version is 4.4.0 */
      #else
      /* [cover parentID={FD9EAFBA-FD62-44f6-931F-6136F02FFE81}]
      Runtime error detection is OFF and Safety is OFF when Autosar version is
      4.4.0 [/cover] */
      #if((ADC_SAFETY_ENABLE==STD_OFF) && (ADC_RUNTIME_ERROR_DETECT==STD_OFF))
      /* [cover parentID={0809F1F3-E9D6-4cbe-B3BB-AB712BCB05F2}]
      Start of Critical Section [/cover] */
          SchM_Enter_Adc_KernelData();
      #endif
      #endif

      /* [cover parentID={5E6A4B52-D00B-4ed3-A330-125384143CF1}]
      HW-SW Priority mode is ON [/cover] */
      #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
      /* [cover parentID={202CCC8E-3ECF-49eb-8C44-ACA3C71EB606}]
      Start or Push the group to pending queue. Group is started immediately
      if group priority is high enough. Otherwise pushed to queue.[/cover]*/
      Adc_lSchedulerOnStart(lKernelId,lGroupId,lCoreId);
      #else
      /* [cover parentID={4C7F40DF-D777-448b-BCA9-CE3A2944BBC2}]
      If Priority mode is not HW-SW [/cover] */
      /* [cover parentID={7C54FA60-7BD6-40ac-849F-449C2F159585}]
      Push the group on to the SW queue,groups is started immediately if the
      SW queue is currently empty [/cover] */
      Adc_lPushToQueue(lKernelId,lGroupId,lCoreId);
      #endif
      /* [cover parentID={94F5EFF2-C8D9-4489-8760-05D0599F1D49}]
      End of Critical Section [/cover] */
      SchM_Exit_Adc_KernelData();
      #else
        /* [cover parentID={7601EE44-4702-48e5-81D3-4F5F858EB687}]
        Critical Section [/cover] */
        /* [cover parentID={06321113-3138-4d36-BDA0-C63267164A34}]
        Priority is OFF and Queueing Mode is OFF [/cover] */
        Adc_GlobalDataType *lKernelDataPtr;
        const Adc_GroupCfgType *lGrpCfgPtr;

        /* Get global state data location for the Kernel */
        lKernelDataPtr = Adc_lGetKernelDataAddress(lKernelId,lCoreId);
        /* Get group configuration address */
        lGrpCfgPtr =  &(Adc_ConfigPtr->CoreCfgPtr[lCoreId]->\
                      HwUnitCfgPtr[lKernelId]->GrpCfgPtr[lGroupId]);
        /* AUTOSAR version is 4.2.2 */
        #if (MCAL_AR_VERSION == MCAL_AR_422)
        /* [cover parentID={A83AB12D-DCF7-4068-8982-57CE604230AA}]
        DET is OFF and Safety is OFF when Autosar version is 4.2.2 [/cover] */
        #if((ADC_SAFETY_ENABLE == STD_OFF) && (ADC_DEV_ERROR_DETECT == STD_OFF))
        /* [cover parentID={317E77C4-6A4C-4651-AF6F-A8326BAEA08D}]
        Start of Critical Section [/cover] */
            SchM_Enter_Adc_KernelData();
        #endif
        /* AUTOSAR version is 4.4.0 */
        #else
        /* [cover parentID={A83AB12D-DCF7-4068-8982-57CE604230AA}]
        Runtime error detection is OFF and Safety is OFF when Autosar version
        is 4.4.0 [/cover] */
        #if((ADC_SAFETY_ENABLE==STD_OFF) && (ADC_RUNTIME_ERROR_DETECT==STD_OFF))
        /* [cover parentID={317E77C4-6A4C-4651-AF6F-A8326BAEA08D}]
        Start of Critical Section [/cover] */
            SchM_Enter_Adc_KernelData();
        #endif
        #endif

        /* [cover parentID={5FB9F609-8602-4f3e-B2F8-825BDB0C3A15}]
        Update group status to Busy  [/cover] */
        Adc_lSetGroupStatusBusyAtomic(lKernelDataPtr,lGroupId);
        /* [cover parentID={CF8926FF-AA60-47f5-AE94-CA6848C8F031}]
        Clear Group Result [/cover] */
        Adc_lClrGroupResultAtomic(lKernelDataPtr,lGroupId);
        /* [cover parentID={50225A65-95E3-4b43-BEE5-D9A95E21206B}]
        Clear Result Buffer End Status [/cover] */
        Adc_lClrResBuffEndStatusAtomic(lKernelDataPtr,lGroupId);
        /* [cover parentID={E9AB2CCE-378C-458c-96E1-92183075AD4C}]
        DMA Mode Result handling is OFF [/cover] */
        #if (ADC_RESULT_HANDLING_IMPLEMENTATION != ADC_DMA_MODE_RESULT_HANDLING)
        /* [cover parentID={E0DC4985-586E-443c-879B-BF1002A56C73}]
        Reset conversion result count to 0  [/cover] */
        lKernelDataPtr->NumofValidConRes[lGroupId]=(Adc_StreamNumSampleType)0U;
        #endif
        /* Update the Active group ID to RS runtime data */
        lKernelDataPtr->RSData[lGrpCfgPtr->GrpPriority].ActiveGroupId=lGroupId;
        /* [cover parentID={07586FF7-EBDA-4f0f-8B4F-6FE357CA9D28}]
        Sync Conversion is ON [/cover] */
        #if (ADC_SYNC_CONV_ENABLE == STD_ON)

        /* [cover parentID={BDF33F98-09C5-4083-8252-3B3DC2C036F9}]
        Set flags for used channels and result registers [/cover] */
        Adc_lSetRunningChAndResReg(lKernelId, lGrpCfgPtr, lCoreId);
        #endif

        /* [cover parentID={36F6A462-B4BD-4799-BF09-4BE4F5AB7436}]
        Limit check is ON [/cover] */
        #if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
        if((uint8)ADC_ONE_U == lGrpCfgPtr->LimitCheckGroup)
        {
          /* [cover parentID={C69539FF-5198-44a4-B790-00AB467A7290}]
          Update Analog channel to Active limit check channel  [/cover] */
          lKernelDataPtr->RSData[lGrpCfgPtr->GrpPriority].ActiveLimitChkCh=\
             lGrpCfgPtr->GroupDefinition[0U].AnalogChannelNo;
        }
        #endif

        /* [cover parentID={C769C69D-B8A2-44e2-A578-65AF23708650}]
        End of Critical Section [/cover] */
        SchM_Exit_Adc_KernelData();

        /* [cover parentID={C51653C3-9C21-47ce-97C1-48D697467DC7}]
        Prepare Group to Start Conversion [/cover] */
        Adc_lPrepareGrpForStart(lKernelId,lGroupId,lCoreId);

        /* Enable ISR servicing for the request source */
        lKernelDataPtr->RSData[lGrpCfgPtr->GrpPriority].IsrNoServiceFlag =\
                                                                     (uint8)0U;

        /* [cover parentID={95CF0562-D281-4675-AB91-B896428C7B90}]
        Start Software Conversion [/cover] */
        Adc_lStartSwConversion(lGrpCfgPtr,lKernelId,lGrpCfgPtr->GrpPriority);
      #endif
    }
  }
}
#endif

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={84B9A797-BC16-44b2-8F17-4DCF01C31957},
                                 {BA6EFE0D-B9E6-4630-BF56-93FFA7D4CB7F}]      **
**                                                                            **
** Syntax           : void Adc_StopGroupConversion                            **
**                    (                                                       **
**                      const Adc_GroupType Group                             **
**                    )                                                       **
**                                                                            **
** Description      : This API stops the conversion of the requested ADC      **
**                    Channel group                                           **
**                    Note: This API is available only when                   **
**                    AdcEnableStartStopGroupApi is configured as true.       **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x03                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for channel groups executing on different     **
**                    ADC hardware groups                                     **
**                                                                            **
** Parameters(in)   : Group - Numeric ID of requested ADC Channel group.      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : void                                                    **
**                                                                            **
*******************************************************************************/
void Adc_StopGroupConversion(const Adc_GroupType Group)
{
  uint32 lKernelId;
  uint32 lCoreId;
  Adc_GroupType lGroupId;
  #if((ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
     (ADC_DEV_ERROR_DETECT == STD_ON))
  uint8 lErrVal;
  #endif
  
  /* Get the core Id from which it is called */
  lCoreId = Mcal_GetCpuIndex();

  /* Extract Kernel ID from Group */
  lKernelId = Adc_lGetAdcKernel(Group);
  /* Extract Kernel specific GroupID from Group*/
  lGroupId = Adc_lGetKernelGroupId(Group);

  /* [cover parentID={7516362E-46BF-46a1-BC5C-09CEF6D0530E}]
  DET is ON or SAFETY is ON [/cover] */
  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))
  /* Check DET's for the API */
  lErrVal = Adc_lStopGrpConvDetCheck(lKernelId, lGroupId, lCoreId);
  /* [cover parentID={61E9A506-8660-4ed7-A71B-9D31E297905E}]
  Stop Group Conversion DET Error [/cover] */
  if(ADC_E_NO_ERR == lErrVal)
  #endif
  {
    /* [cover parentID={91E623DE-8F0C-481a-BD19-AADA54315192}]
    DET is ON for AUTOSAR version 4.2.2 or SAFETY is ON or Runtime Error
    Detection is ON [/cover] */
    #if((ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
        ((MCAL_AR_VERSION == MCAL_AR_422) && (ADC_DEV_ERROR_DETECT == STD_ON)))
    /* [cover parentID={9C5A9F2E-7FBD-450d-B75D-06782D8AD650}]
    Critcal Section [/cover] */
    /* [cover parentID={F60DC1A1-E90D-46d0-910D-BC0D27A7C353}]
    Start of Critical Section [/cover] */
    SchM_Enter_Adc_KernelData();
    /* [cover parentID={85852DB9-A183-4bae-AAFF-4745D38748AC}]
    Check Group Idle Development or Runtime Error [/cover] */
    lErrVal = Adc_lCheckGrpIdleDet(lKernelId,lGroupId,\
                                   ADC_SID_STOP_GROUP_CONVERSION,lCoreId);
    /* [cover parentID={92F4E292-D415-4e86-8CD9-00400CB73753}]
    Group Idle DET Error  [/cover] */
    if(ADC_E_NO_ERR != lErrVal)
    {
      /* [cover parentID={DABB487C-5EF8-47dd-BFB5-2398EBE14C9A}]
      End of Critical Section [/cover] */
      SchM_Exit_Adc_KernelData();
    }
    else
    #endif
    {
      /* [cover parentID={0937961C-E815-47ae-B16C-0FAE5192EDA0}]
      Is QUEUE mode is ON or Prioirty mode is ON? [/cover] */
      /* [cover parentID={EA723BE7-2E7D-4b4f-9C4D-5AA1AC644536}]
      Priority is ON or Queueing Mode is ON [/cover] */
      /* [cover parentID={CF3DB727-B8A7-4f49-BC41-97F36E2702CA}]
      Critcal Section [/cover] */
      #if((ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) ||\
          (ADC_ENABLE_QUEUING == STD_ON))
        /* Pop/remove the group on to the SW queue,
           groups has to be stopped if the group is at the currently
           converting*/
        /* AUTOSAR version is 4.2.2 */
        #if (MCAL_AR_VERSION == MCAL_AR_422)
        /* [cover parentID={30A9E5E8-7CB4-4144-ABB3-E79C4D6B5912}]
        DET is OFF and Safety is OFF when Autosar version is 4.2.2 [/cover] */
        #if((ADC_SAFETY_ENABLE == STD_OFF) && (ADC_DEV_ERROR_DETECT == STD_OFF))
        /* [cover parentID={0784FC96-97DD-4f70-9E6E-46C21CA6966E}]
        Start of Critical Section [/cover] */
            SchM_Enter_Adc_KernelData();
        #endif
        /* AUTOSAR version is 4.4.0 */
        #else
        /* [cover parentID={30A9E5E8-7CB4-4144-ABB3-E79C4D6B5912}]
        Runtime error detection is OFF and Safety is OFF when Autosar version
        is 4.4.0 [/cover] */
        #if((ADC_SAFETY_ENABLE==STD_OFF) && (ADC_RUNTIME_ERROR_DETECT==STD_OFF))
        /* [cover parentID={0784FC96-97DD-4f70-9E6E-46C21CA6966E}]
        Start of Critical Section [/cover] */
            SchM_Enter_Adc_KernelData();
        #endif
        #endif
        /* [cover parentID={6B7AE267-786F-42bb-A978-EF5C65D502CE}]
        HW-SW Priority mode is ON [/cover] */
        #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
        /* [cover parentID={6146A481-1118-4316-B0FA-52E4C373D8C6}]
        Stop the current executing Group [/cover] */
        Adc_lSchedulerOnStop(lKernelId,lGroupId,lCoreId);
        #else
        /* [cover parentID={BC357ECE-3BED-4e56-AA15-FA30DE028735}]
        If priority mode is not HW-SW [/cover] */
        /* [cover parentID={C31902EF-0257-43ef-9116-7EC0EE7F6BB8}]
        Pop from Queue   [/cover] */
        Adc_lPopFromQueue(lKernelId,lGroupId,lCoreId);
        #endif
        /* [cover parentID={81AAB971-B0F4-4d87-AE21-A09AD5C66031}]
        Stop of Critical Section [/cover] */
        SchM_Exit_Adc_KernelData();
      #else
        /* [cover parentID={68AF9EAC-B422-4c3e-A183-4E1D175191CE}]
        Critcal Section [/cover] */
        /* [cover parentID={93DCFB11-EDB3-413a-8150-755D307240E9}]
        Priority is OFF and Queueing Mode is OFF [/cover] */
        Adc_GlobalDataType *lKernelDataPtr;
        const Adc_GroupCfgType *lGrpCfgPtr;

        /* Get global state data location for the Kernel */
        lKernelDataPtr = Adc_lGetKernelDataAddress(lKernelId, lCoreId);
        /* Get group configuration address */
        lGrpCfgPtr =  &(Adc_ConfigPtr->CoreCfgPtr[lCoreId]->\
                    HwUnitCfgPtr[lKernelId]->GrpCfgPtr[lGroupId]);
        /* [cover parentID={68AF9EAC-B422-4c3e-A183-4E1D175191CE}]
        Critical Section   [/cover] */
        /* AUTOSAR version is 4.2.2 */
        #if (MCAL_AR_VERSION == MCAL_AR_422)
        /* [cover parentID={CEE10FF2-5117-4290-A990-06E850D970ED}]
        DET is OFF and Safety is OFF when Autosar version is 4.2.2 [/cover] */
        #if((ADC_SAFETY_ENABLE == STD_OFF) && (ADC_DEV_ERROR_DETECT == STD_OFF))
        /* [cover parentID={460AA140-A6AE-4ff4-82FD-0428DB769B1E}]
        Start of Critical Section [/cover] */
            SchM_Enter_Adc_KernelData();
        #endif
        /* AUTOSAR version is 4.4.0 */
        #else
        /* [cover parentID={CEE10FF2-5117-4290-A990-06E850D970ED}]
        Runtime error detection is OFF and Safety is OFF when Autosar version
        is 4.4.0 [/cover] */
        #if((ADC_SAFETY_ENABLE==STD_OFF) && (ADC_RUNTIME_ERROR_DETECT==STD_OFF))
        /* [cover parentID={460AA140-A6AE-4ff4-82FD-0428DB769B1E}]
        Start of Critical Section [/cover] */
            SchM_Enter_Adc_KernelData();
        #endif
        #endif

        /* [cover parentID={0F079DF2-1084-4f77-A50B-55D33D100925}]
        Is Group BUSY [/cover] */
        if(Adc_lGetGroupStatus(lKernelDataPtr, lGroupId) == (uint32)ADC_ONE_U)
        {
          /* Disable ISR servicing for the request source */
          lKernelDataPtr->RSData[lGrpCfgPtr->GrpPriority].IsrNoServiceFlag = \
              (uint8)ADC_ONE_U;
          /* [cover parentID={8337A4D3-13C8-4b99-A434-512B59190A88}]
          End of Critical Section [/cover] */
          SchM_Exit_Adc_KernelData();
          /* [cover parentID={9289BE75-94A0-474e-A387-90C626497108}]
          Stop the ongoing conversions  [/cover] */
          Adc_lStopConvRequest(lGrpCfgPtr, lKernelId, lGrpCfgPtr->GrpPriority);
          /* Remove Active Group ID from the Global Kernel Data */
          Adc_lRemoveActiveGroup(lKernelDataPtr, lGrpCfgPtr, \
                                 lGrpCfgPtr->GrpPriority);
          /* [cover parentID={3B38E039-C5D0-42f6-8AFD-7FA6DB4605FF}]
          Sync Conversion is ON [/cover] */
          #if (ADC_SYNC_CONV_ENABLE == STD_ON)
          /* [cover parentID={C4461D25-A160-4829-9411-5BB53A325FE1}]
          Critcal Section [/cover] */
          /* [cover parentID={EF1BED9C-EF61-494f-A2B2-4B2B3498E815}]
          Start of Critcal Section [/cover] */
          SchM_Enter_Adc_KernelData();
          /* [cover parentID={55A455D7-F417-4ab4-B3A9-FC9BC8789CD8}]
          Clear channels & Result registers flags [/cover] */
          Adc_lClrRunningChAndResReg(lKernelId, lGrpCfgPtr, lCoreId);
          /* [cover parentID={661B00D5-69DE-46c7-8615-53F5219B9714}]
          Stop of Critcal Section [/cover] */
          SchM_Exit_Adc_KernelData();
          #endif
        }
        else
        {
          /* [cover parentID={003549AB-BBC9-4ba3-86E2-36A4C8FEC2AB}]
          End of Critical Section [/cover] */
          SchM_Exit_Adc_KernelData();
        }
        /* [cover parentID={78724D8F-29AA-44d3-ADE4-9C961C963946}]
        Critcal Section [/cover] */
        /* [cover parentID={650AEEB7-D0EB-4819-85E0-53F71698E4F0}]
        Start of Critical Section [/cover] */
        SchM_Enter_Adc_KernelData();
        /*Restore group status to IDLE*/
        /* [cover parentID={9B2933E7-7ADB-41ed-8E5F-8AB94A0BB545}]
        Clear Group Status busy [/cover] */
        Adc_lClrGroupStatusBusyAtomic(lKernelDataPtr, lGroupId);
        /* [cover parentID={10818040-27C2-4431-A4BB-B9DFBF0D22D6}]
        Clear Group Result [/cover] */
        Adc_lClrGroupResultAtomic(lKernelDataPtr, lGroupId);
        /* [cover parentID={43348CDF-11D8-483b-AB54-8603AE2622B1}]
        Clear Result Buffer End Status [/cover] */
        Adc_lClrResBuffEndStatusAtomic(lKernelDataPtr, lGroupId);
        /* [cover parentID={70526CB9-929B-4274-9FBB-9760DAE6BECC}]
        DMA Mode Result handling is OFF [/cover] */
        #if (ADC_RESULT_HANDLING_IMPLEMENTATION != ADC_DMA_MODE_RESULT_HANDLING)
        /* [cover parentID={456AAED6-3818-4a05-8494-0CD92A303E46}]
        Reset conversion result count to 0 [/cover] */
        lKernelDataPtr->NumofValidConRes[lGroupId] \
          = (Adc_StreamNumSampleType)0U;
        #endif
        /* [cover parentID={4EE741C1-1CC9-4645-A953-08206478559A}]
        Group Notify Capability is ON [/cover] */
        #if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
        /* [cover parentID={8D487EC3-401A-45bc-B648-1ECB956680C3}]
        Disable group notification [/cover] */
        Adc_lClrGrpNotifAtomic(lKernelDataPtr, lGroupId);
        #endif
        
        /* [cover parentID={953A283E-7D52-4863-A87A-29A7B989B5C3}]
        End of Critical Section [/cover] */
        SchM_Exit_Adc_KernelData();
      #endif
    }
  }
}
#endif

#if ((ADC_READ_GROUP_API == STD_ON) &&\
     (ADC_RESULT_HANDLING_IMPLEMENTATION != ADC_DMA_MODE_RESULT_HANDLING))
/*CYCLOMATIC_Adc_ReadGroup_JUSTIFICATION: This API reads the group conversion
results and performs the DET or Safety or Runtime Error check for AR422 and
AR440 based on the enable of pre-compile macros and also reads the result of
slave kernels if ADC_SYNC_CONV_ENABLE pre-compile macro is enabled. The
different if conditions cause the complexity to increase, but actually during
run-time out of all if conditions many will be pre-compile time removed*/
/*******************************************************************************
** Traceability: [cover parentID={2851AF0C-C875-445f-8096-2D0576BF2580},
                                 {BA6EFE0D-B9E6-4630-BF56-93FFA7D4CB7F}]      **
**                                                                            **
** Syntax           : Std_ReturnType Adc_ReadGroup                            **
**                    (                                                       **
**                      const Adc_GroupType Group                             **
**                      Adc_ValueGroupType * const DataBufferPtr              **
**                    )                                                       **
**                                                                            **
** Description      : This API reads the group conversion result of the last  **
**                    completed conversion round of the requested group and   **
**                    stores the channel's conversion value starting from     **
**                    DataBufferPtr address. The channel's conversion values  **
**                    are stored in ascending channel number order            **
**                    Note:                                                   **
**                    1. This API is available only when AdcReadGroupApi      **
**                       is configured as true.                               **
**                    2. This API is not available when                       **
**                       AdcResultHandlingImplementation is set to DMA mode of**
**                       result handling                                      **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x04                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different AdcChannel Groups               **
**                                                                            **
** Parameters(in)   : Group - Numeric ID of requested ADC Channel group.      **
**                                                                            **
** Parameters(in-out): DataBufferPtr -Location to store the requested Group's **
**                     channels conversion result                             **
**                                                                            **
** Return value     : E_OK - Results are available and written to the data    **
**                           buffer                                           **
**                    E_NOT_OK - No results are available or development      **
**                               error occurred                               **
**                                                                            **
*******************************************************************************/
Std_ReturnType Adc_ReadGroup(const Adc_GroupType Group,
                             Adc_ValueGroupType * const DataBufferPtr)
{
  const Adc_GroupCfgType *lGrpCfgPtr;
  Adc_GlobalDataType *lKernelDataPtr;
  const Adc_ValueGroupType *lCurrentResultPtr;
  uint32 lKernelId, lBusyFlag, lResultFlag, lCoreId;
  Std_ReturnType lRetVal;
  Adc_GroupType lGroupId;
  Adc_StreamNumSampleType lNoofValidConv, lNumOfSamples;
  uint8 lNoOfChannels, lCount;
  #if((ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
     (ADC_DEV_ERROR_DETECT == STD_ON))
  uint8 lErrVal;
  #endif
  
  /* Get the core Id from which it is called */
  lCoreId = Mcal_GetCpuIndex();

  /* Extract Kernel ID from Group */
  lKernelId = Adc_lGetAdcKernel(Group);
  /* Extract Kernel specific GroupID from Group*/
  lGroupId = Adc_lGetKernelGroupId(Group);

  /* [cover parentID={FDD1B6D9-5E86-457e-9FBE-B72D90B7CCAA}]
  DET is ON or SAFETY is ON [/cover] */
  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))
  /* Check DET's for the API */
  lErrVal = Adc_lReadGrpDetCheck(DataBufferPtr, lKernelId, lGroupId, lCoreId);
  /* [cover parentID={F06737E7-47F0-451d-BB4F-97BC609DC694}]
  Read Group DET Error [/cover] */
  if(ADC_E_NO_ERR != lErrVal)
  {
    /* [cover parentID={961FA51A-79B5-4b62-A8C5-E1B2CFB9CF7E}]
    Return status as E_NOT_OK [/cover] */
    lRetVal = E_NOT_OK;
  }
  else
  #endif
  {
    /* [cover parentID={801FD9D7-A9AD-4265-A281-BC2DB0B21B7A}]
    DET is ON for AUTOSAR version 4.2.2 or SAFETY is ON or Runtime Error
    Detection is ON [/cover] */
    #if((ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
        ((MCAL_AR_VERSION == MCAL_AR_422) && (ADC_DEV_ERROR_DETECT == STD_ON)))
    /* [cover parentID={B1CD0210-76F6-4abe-BC66-CD3640719BB4}]
    Critical Section [/cover] */
    /* [cover parentID={FFB56F32-61D2-4cac-ADD3-25092D4246B8}]
    Start of Critical Section [/cover] */
    SchM_Enter_Adc_KernelData();
    
    /* [cover parentID={9948FC74-682F-4a27-9F84-C8C2718E6B45}]
    Check Group Idle Development or Runtime Error [/cover] */
    lErrVal = Adc_lCheckGrpIdleDet(lKernelId, lGroupId, ADC_SID_READ_GROUP, \
                                   lCoreId);
    /* [cover parentID={232B978F-858C-4b69-BF51-5ECE5FF9F142}]
    Group Idle DET Error  [/cover] */
    if(ADC_E_NO_ERR != lErrVal)
    {
      /* [cover parentID={98D7E543-8FC1-4cd1-BBAD-339ED5EE40B3}]
      End of Critical Section [/cover] */
      SchM_Exit_Adc_KernelData();
      
      /* [cover parentID={961FA51A-79B5-4b62-A8C5-E1B2CFB9CF7E}]
      Return status as E_NOT_OK [/cover] */
      lRetVal = E_NOT_OK;
    }
    else
    #endif
    {
      /* Get global state data location for the Kernel */
      lKernelDataPtr = Adc_lGetKernelDataAddress(lKernelId, lCoreId);
      /* Get group configuration address */
      lGrpCfgPtr = &(Adc_ConfigPtr->CoreCfgPtr[lCoreId]->\
                     HwUnitCfgPtr[lKernelId]->GrpCfgPtr[lGroupId]);
      
      /* Get number of samples per Channel*/
      lNumOfSamples = lGrpCfgPtr->NumOfSamples;

      /* [cover parentID={A74AF51E-C5AA-44bf-B338-B953B943743A}]
      EMUX mode is ON [/cover]*/
      #if(ADC_EMUX_ENABLE == STD_ON)
      uint8 lEmuxGrp;
      
      /* Get the Emux data of the Group */
      lEmuxGrp = (ADC_ONE_U & (lGrpCfgPtr->GrpEmuxCfg));
      /* [cover parentID={68266C61-D8CD-43c9-B103-3FAEE57A5EAA}]
      Is Group configured with the EMUX channel [/cover]*/
      if(lEmuxGrp == ADC_ONE_U)
      {
        /* [cover parentID={8544CBEC-6F6F-4f52-85AE-6F8630856900}]
        Get Number of channels configured for EMUX group
        i.e. Maximum selected channel + 1 */
        lNoOfChannels = ((lGrpCfgPtr->GrpEmuxCfg) >> ADC_ONE_U);
        lNoOfChannels = lNoOfChannels + (uint8)1U;
      }
      else
      #endif

      {
        /* [cover parentID={7389A097-CA96-432f-BACF-DA5BEC7F50D0}]
        Get Number of channels configured for the group */
        lNoOfChannels = lGrpCfgPtr->NoOfChannels;
      }

      /*Critical Section is protecting the result copy to application.
        Since, for continuous conversion groups with 1 streaming sample,
        the same result buffer position will be written in ISR and read from
        this API. Hence, while the read is ON, the write from ISR should be
        protected, to get a consistent result set for all the channels*/
        /* [cover parentID={894BD85D-A869-4b20-85C7-E57CA486718D}]
        Critical Section   [/cover] */
        /* AUTOSAR version is 4.2.2 */
        #if (MCAL_AR_VERSION == MCAL_AR_422)
        /* [cover parentID={24D82E1C-3C75-455c-A907-849B8806EE98}]
        DET is OFF and Safety is OFF when Autosar version is 4.2.2 [/cover] */
        #if((ADC_SAFETY_ENABLE == STD_OFF) && (ADC_DEV_ERROR_DETECT == STD_OFF))
        /* [cover parentID={FAF60D79-C34A-4b90-A356-1483023416DC}]
        Start of Critical Section [/cover] */
            SchM_Enter_Adc_KernelData();
        #endif
        /* AUTOSAR version is 4.4.0 */
        #else
        /* [cover parentID={24D82E1C-3C75-455c-A907-849B8806EE98}]
        Runtime error detection is OFF and Safety is OFF when Autosar version
        is 4.4.0 [/cover] */
        #if((ADC_SAFETY_ENABLE==STD_OFF) && (ADC_RUNTIME_ERROR_DETECT==STD_OFF))
        /* [cover parentID={FAF60D79-C34A-4b90-A356-1483023416DC}]
        Start of Critical Section [/cover] */
            SchM_Enter_Adc_KernelData();
        #endif
        #endif
      
      /* Get group status flags */
      lBusyFlag = Adc_lGetGroupStatus(lKernelDataPtr, lGroupId);
      lResultFlag = Adc_lGetGroupResultStatus(lKernelDataPtr, lGroupId);
      /* [cover parentID={B60EE688-EC33-49f0-98BA-E43016C41632}]
      Read the number of valid results available [/cover] */
      lNoofValidConv = lKernelDataPtr->NumofValidConRes[lGroupId];
      
      /* [cover parentID={6D1DC85B-1F58-4860-B5A6-D45636FC9D54}]
      Group is busy with no results [/cover] */
      if((lBusyFlag == (uint32)1U) && (lResultFlag == (uint32)0U))
      {
        /* [cover parentID={961FA51A-79B5-4b62-A8C5-E1B2CFB9CF7E}]
        Return status as E_NOT_OK [/cover] */
        lRetVal = E_NOT_OK;
      }
      else
      {
        /*
         Application Result Buffer organisation for
         a)
         - 5 Channels - CH9, CH1, CH2, CH3 and CH4
         - 3 streaming samples for each channel
         - No synchronous conversion kernels
      
          Result Buffer:
          Buffer Start                                       Buffer End
          +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
          |CH9|CH9|CH9|CH1|CH1|CH1|CH2|CH2|CH2|CH3|CH3|CH3|CH4|CH4|CH4|
          +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
      
          Data Buffer (DataBufferPtr):
          Buffer Start                                       Buffer End
          +---+---+---+---+---+
          |CH9|CH1|CH2|CH3|CH4|
          +---+---+---+---+---+
      
          b)
         - 3 Channels - CH9, CH1, and CH2
         - 2 streaming samples for each channel
         - Kernel K0 synchronization master, kernel K1 and K2 synchronization
           slaves
         - Channels CH9 and CH2 enabled for synchronous conversion
      
          Result Buffer:
          Buffer Start
          +-----+-----+-----+-----+-----+-----+    +-----+-----+-----+-----+
          |K0CH9|K0CH9|K0CH1|K0CH1|K0CH2|K0CH2| => |K1CH9|K1CH9|K1CH2|K1CH2| =>
          +-----+-----+-----+-----+-----+-----+    +-----+-----+-----+-----+
      
                            Buffer End
             +-----+-----+-----+-----+
          => |K2CH9|K2CH9|K2CH1|K2CH1|
             +-----+-----+-----+-----+
      
          Data Buffer (DataBufferPtr):
          Buffer Start                                       Buffer End
          +-----+-----+-----+-----+-----+-----+-----+
          |K0CH9|K0CH1|K0CH2|K1CH9|K1CH2|K2CH9|K2CH1|
          +-----+-----+-----+-----+-----+-----+-----+
      
          c)
         - 3 Channels - CH9, CH1, and CH2
         - 2 streaming samples for each channel
         - Kernel K1 synchronization master, kernel K0 and K3 synchronization
           slaves
         - Channels CH1 and CH2 enabled for synchronous conversion
      
          Result Buffer:
          Buffer Start
          +-----+-----+-----+-----+-----+-----+    +-----+-----+-----+-----+
          |K1CH9|K1CH9|K1CH1|K1CH1|K1CH2|K1CH2| => |K0CH1|K0CH1|K0CH2|K0CH2| =>
          +-----+-----+-----+-----+-----+-----+    +-----+-----+-----+-----+
      
                            Buffer End
             +-----+-----+-----+-----+
          => |K3CH1|K3CH1|K3CH2|K3CH2|
             +-----+-----+-----+-----+
      
          Data Buffer (DataBufferPtr):
          Buffer Start                                       Buffer End
          +-----+-----+-----+-----+-----+-----+-----+
          |K1CH9|K1CH1|K1CH2|K0CH1|K0CH2|K2CH1|K2CH2|
          +-----+-----+-----+-----+-----+-----+-----+
        */
      
        /* [cover parentID={C58F9673-A3E4-4569-B64D-D2BB92B6785F}]
        Get pointer to the latest result sample set available [/cover] */
        lCurrentResultPtr = lKernelDataPtr->GrpResBuffer[lGroupId];
        lCurrentResultPtr = &lCurrentResultPtr[lNoofValidConv - \
                                               (Adc_StreamNumSampleType)1U];
        /* [cover parentID={03BD01DD-B048-4b0f-85F4-950A04B21A33}]
        Till the last available channel [/cover] */
        for(lCount = 0U; lCount < lNoOfChannels; lCount++)
        {
          /* [cover parentID={0AD1D3D1-03EE-4b1b-BC62-A34C05948CED}]
          Copy results to data buffer pointer [/cover] */
          DataBufferPtr[lCount] = \
                   lCurrentResultPtr[(uint32)lCount*(uint32)lNumOfSamples];
        }
      
        /* [cover parentID={3A28A59E-4A9F-40a1-8A8A-30F78A12C71A}]
        Sync Conversion is ON [/cover] */
        #if (ADC_SYNC_CONV_ENABLE == STD_ON)
        if (lGrpCfgPtr->SyncChannelMask != (uint16)0U)
        {
          lCurrentResultPtr = &lCurrentResultPtr[(uint32)lNoOfChannels *
                                 (uint32)lNumOfSamples];
          /* [cover parentID={DBEF38CF-C43E-4a89-8657-A78EDBB64355}]
          Read result of Slave Kernels [/cover] */
          Adc_lReadSlaveResult(lKernelId, lGrpCfgPtr, lCurrentResultPtr, \
                               &DataBufferPtr[lNoOfChannels], lCoreId);
        }
        #endif
      
        /* [cover parentID={8D0A348D-FEAF-4c6e-9510-191A2B7BB55D}]
        Clear Group result status [/cover] */
        Adc_lClrGroupResultAtomic(lKernelDataPtr, lGroupId);
        /* [cover parentID={0D432239-0A5D-484a-8801-4905C297BDF2}]
        Clear Result buffer end status [/cover] */
        Adc_lClrResBuffEndStatusAtomic(lKernelDataPtr, lGroupId);
        /* [cover parentID={05431D66-9239-445e-BDB1-622C6B83AC9B}]
        Groups which are not converting - implicitly stopped are put to IDLE
        state & Reset the Number of valid conversion to ZERO   [/cover] */
        if(lBusyFlag == (uint32)0U)
        {
          /* [cover parentID={05431D66-9239-445e-BDB1-622C6B83AC9B}]
          For implicitly stopped groups, Clear the valid number of samples for
          implicity stopped group [/cover] */
          lKernelDataPtr->NumofValidConRes[lGroupId] = \
                                                 (Adc_StreamNumSampleType)0U;
        }
        /* [cover parentID={9F7FA04E-CDC1-438c-AD81-0E881117C245}]
        Return status as E_OK [/cover] */
        lRetVal = E_OK;
      }
      /* [cover parentID={814F3F63-82C1-426c-A42D-1BF3A70068EB}]
      End of Critical Section [/cover] */
      SchM_Exit_Adc_KernelData();
    }
  }
  return(lRetVal);
}
#endif

#if (ADC_HW_TRIGGER_API == STD_ON)
/*CYCLOMATIC_Adc_EnableHardwareTrigger_JUSTIFICATION: This API enables the
hardware trigger for the requested ADC Group for different modes of ADC
operation (No priority,Queuing,HW priority & HW-SW priority) and performs the
DET or Safety or Runtime Error check for AR422 and AR440 based on the enable
of pre-compile macros. The different if conditions in different operating
modes cause the complexity to increase, but actually during run-time out of
all if conditions many will be pre-compile time removed*/
/*******************************************************************************
** Traceability: [cover parentID={60737F4B-61A1-4ca9-B525-132F23E5533C},
                                 {BA6EFE0D-B9E6-4630-BF56-93FFA7D4CB7F}]      **
**                                                                            **
** Syntax           : void Adc_EnableHardwareTrigger                          **
**                    (                                                       **
**                      const Adc_GroupType Group                             **
**                    )                                                       **
**                                                                            **
** Description      : This API setups the group for conversion and enables    **
**                    the hardware trigger for the requested ADC Group.       **
**                    Note: This API is available only when AdcHwTriggerApi   **
**                    is configured as true.                                  **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x05                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for channel groups executing on different     **
**                    ADC hardware groups                                     **
**                                                                            **
** Parameters(in)   : Group - Numeric ID of requested ADC Channel group.      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : void                                                    **
**                                                                            **
*******************************************************************************/
void Adc_EnableHardwareTrigger(const Adc_GroupType Group)
{
  #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_HW_SW)
  Adc_GlobalDataType *lKernelDataPtr;
  const Adc_GroupCfgType *lGrpCfgPtr;
  #endif
  uint32 lKernelId;
  uint32 lCoreId;
  Adc_GroupType lGroupId;
  #if((ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
      (ADC_DEV_ERROR_DETECT == STD_ON))
  uint8 lErrVal;
  #endif
  
  /* Get the core Id from which it is called */
  lCoreId = Mcal_GetCpuIndex();

  /* Extract Kernel ID from Group */
  lKernelId = Adc_lGetAdcKernel(Group);
  /* Extract Kernel specific GroupID from Group*/
  lGroupId = Adc_lGetKernelGroupId(Group);

  /* [cover parentID={7B137ADE-6A92-4a29-8422-E6A6174DEFC7}]
  DET is ON or SAFETY is ON [/cover] */
  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))
  /* Check DET's for the API */
  lErrVal = Adc_lEnHwTriggerDetCheck(lKernelId, lGroupId, lCoreId);
  /* [cover parentID={CE410160-E3A3-43f4-8627-FC457677869C}]
  Enable Hardware Trigger DET Error [/cover] */
  if(ADC_E_NO_ERR == lErrVal)
  #endif
  {
    /* [cover parentID={DBBE310C-B75E-4c96-AEBE-5F2BFBBFB234}]
    DET is ON for AUTOSAR version 4.2.2 or SAFETY is ON or Runtime Error
    Detection is ON [/cover] */
    #if((ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
         ((MCAL_AR_VERSION == MCAL_AR_422) && (ADC_DEV_ERROR_DETECT == STD_ON)))
    /* [cover parentID={EFD46631-0639-462d-98B3-376EC63FB984}]
    Critcal Section [/cover] */
    /* [cover parentID={2D03377A-4B71-4834-9273-3530709E5E15}]
    Start of Critical Section [/cover] */
    SchM_Enter_Adc_KernelData();
    
    /* [cover parentID={70FB7153-862A-4ebc-B976-C35DA904C624}]
    Check Group Busy Development or Runtime Error [/cover] */
    lErrVal = Adc_lCheckGrpBusyDet(lKernelId, lGroupId, \
                                   ADC_SID_ENABLE_HARDWARE_TRIGGER,lCoreId);
    /* [cover parentID={95C1D1F1-456D-4628-B5A7-72572A5220ED}]
    Group Busy Error  [/cover] */
    if(ADC_E_NO_ERR != lErrVal)
    {
      /* [cover parentID={9BE3E4B5-6914-4d89-A856-64D4F2AB27ED}]
      End of Critical Section [/cover] */
      SchM_Exit_Adc_KernelData();
    }
    else
    #endif
    {
      /* [cover parentID={997603AF-0AB5-4575-9B52-89B047A7B385}]
      Critical Section   [/cover] */
      /* AUTOSAR version is 4.2.2 */
      #if (MCAL_AR_VERSION == MCAL_AR_422)
      /* [cover parentID={DC178EB9-5D74-47a0-90E3-272E87868CE4}]
      DET is OFF and Safety is OFF when Autosar version is 4.2.2 [/cover] */
      #if((ADC_SAFETY_ENABLE == STD_OFF) && (ADC_DEV_ERROR_DETECT == STD_OFF))
      /* [cover parentID={64E177C2-C3B3-4edf-B352-220D2693A753}]
      Start of Critical Section [/cover] */
          SchM_Enter_Adc_KernelData();
      #endif
      /* AUTOSAR version is 4.4.0 */
      #else
      /* [cover parentID={DC178EB9-5D74-47a0-90E3-272E87868CE4}]
      Runtime error detection is OFF and Safety is OFF when Autosar version is
      4.4.0 [/cover] */
      #if((ADC_SAFETY_ENABLE==STD_OFF) && (ADC_RUNTIME_ERROR_DETECT==STD_OFF))
      /* [cover parentID={64E177C2-C3B3-4edf-B352-220D2693A753}]
      Start of Critical Section [/cover] */
          SchM_Enter_Adc_KernelData();
      #endif
      #endif
      /* [cover parentID={63955155-6166-434f-9288-EFE53CE3E7C7}]
      HW-SW Priority mode is ON [/cover] */
      #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
        /* [cover parentID={A48447EE-A83D-4188-AB4D-D06DC745C1B7}]
        Schedule the group for start [/cover] */
        Adc_lSchedulerOnStart(lKernelId, lGroupId, lCoreId);
      
        /* [cover parentID={C776C3DA-F7AD-402d-9AEC-FACF2C3DC9BA}]
        End of Critical Section [/cover] */
        SchM_Exit_Adc_KernelData();
      #else
        /* [cover parentID={DCF95BD2-5953-4792-A5A4-5F798657018F}]
        HW-SW Priority mode is OFF [/cover] */
        /* Get global state data location for the Kernel */
        lKernelDataPtr = Adc_lGetKernelDataAddress(lKernelId, lCoreId);
        /* Get group configuration address */
        lGrpCfgPtr =  &(Adc_ConfigPtr->CoreCfgPtr[lCoreId]->\
                        HwUnitCfgPtr[lKernelId]->GrpCfgPtr[lGroupId]);
        /* [cover parentID={F0275002-2640-43c1-A441-9FDDDE4BAD60}]
        Priority mode is Hw or Queue Mode is ON [/cover] */
        #if((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW) ||\
            (ADC_ENABLE_QUEUING == STD_ON))
        /* Since, the SW queue is empty, place the group on Queue head
        Further calls to to start SW Triggered group will be queued and
        will be started when current HW triggered groups is stopped */
        /* [cover parentID={FCEB490C-D0D2-4ddf-B4DA-2B17399E7EBC}]
        Push Group ID and Pop Group ID to current Group [/cover] */
        lKernelDataPtr->RSData[lGrpCfgPtr->GrpPriority].PushGroupId = lGroupId;
        lKernelDataPtr->RSData[lGrpCfgPtr->GrpPriority].PopGroupId = lGroupId;
        #endif
        
        /* [cover parentID={DFBFF5D8-B7E2-4065-BB41-5550ECA7A4B8}]
        Set Group Status to Busy    [/cover] */
        Adc_lSetGroupStatusBusyAtomic(lKernelDataPtr, lGroupId);
        /* [cover parentID={1ECF5A4E-C68D-4288-91E6-C97CD9E054A9}]
        Clear Group Result [/cover] */
        Adc_lClrGroupResultAtomic(lKernelDataPtr, lGroupId);
        /* [cover parentID={0F69F691-CF60-4944-B77F-208E277CBDE8}]
        Clear Result Buffer End Status [/cover] */
        Adc_lClrResBuffEndStatusAtomic(lKernelDataPtr, lGroupId);
        /* [cover parentID={7A58AEA1-7C8E-4d26-B813-84CAEBC4CDFA}]
        DMA Result handling is OFF [/cover] */
        #if (ADC_RESULT_HANDLING_IMPLEMENTATION != ADC_DMA_MODE_RESULT_HANDLING)
        /* [cover parentID={49D933C9-96D0-4530-98B7-42EAD2E24942}]
        Reset  the Conversion result count to ZERO    [/cover] */
        lKernelDataPtr->NumofValidConRes[lGroupId] \
          = (Adc_StreamNumSampleType)0U;
        #endif
        /* [cover parentID={9F3F77E9-344D-46e3-894D-C6A78E4813F2}]
        Update Active Group ID to the corresponding Request Source data
        [/cover] */
        lKernelDataPtr->RSData[lGrpCfgPtr->GrpPriority].ActiveGroupId \
          = lGroupId;

        /* [cover parentID={07FC9F8A-E7A5-4c11-B995-BEFC0B97EA8D}]
        Priority mode is HW or Sync Conversion is ON [/cover] */
        #if ((ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) ||\
             (ADC_SYNC_CONV_ENABLE == STD_ON))
        /* [cover parentID={79542019-5D1A-4ed3-8FEF-872D4B87FC76}]
        Set flags for used channels and result registers [/cover] */
        Adc_lSetRunningChAndResReg(lKernelId, lGrpCfgPtr, lCoreId);
        #endif

        /* [cover parentID={CC63809D-AF08-43da-B655-20550DB324AC}]
        Limit Check is ON [/cover] */
        #if (ADC_ENABLE_LIMIT_CHECK==STD_ON)
        if((uint8)ADC_ONE_U == lGrpCfgPtr->LimitCheckGroup)
        {
          /* [cover parentID={249BAE3C-8A52-4c1c-9462-7D104B2FB828}]
          Set the limit check group [/cover] */
          lKernelDataPtr->RSData[lGrpCfgPtr->GrpPriority].ActiveLimitChkCh=\
                lGrpCfgPtr->GroupDefinition[0U].AnalogChannelNo;
        }
        #endif

        /* [cover parentID={3D1A1A91-A862-44c3-A451-317A13184CB1}]
        Priority Mode is Hardware [/cover] */
        #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /* [cover parentID={1B50E6F1-6FCD-47b3-A7D1-5DB743F275DD}]
        Limit Check is ON [/cover] */
        #if (ADC_ENABLE_LIMIT_CHECK==STD_ON)
        /* [cover parentID={CEBA17F4-B6D6-430c-A9F9-F0D6F0EB47E2}]
        Is group enabled with limit check [/cover] */
        if ((uint8)ADC_ONE_U == lGrpCfgPtr->LimitCheckGroup)
        {
          /* [cover parentID={CEBA17F4-B6D6-430c-A9F9-F0D6F0EB47E2}]
          Set the limit check group active flag [/cover] */
          lKernelDataPtr->LimitChkActiveFlag = (uint8)ADC_ONE_U;
        }
        #endif
        /* [cover parentID={8D751053-F019-4fe3-9723-77FC1A6A8A53}]
        Is group enabled with Alias [/cover] */
        if (ADC_ALIAS_DEFAULT_VALUE != lGrpCfgPtr->AliasChCfg)
        {
          /* [cover parentID={8D751053-F019-4fe3-9723-77FC1A6A8A53}]
          Set the alias group active flag [/cover] */
          lKernelDataPtr->AliasActiveFlag = (uint8)ADC_ONE_U;
        }
        #endif

        /* [cover parentID={C9692026-DE64-4bf8-9FDA-40BDE0E75171}]
        End of Critical Section [/cover] */
        SchM_Exit_Adc_KernelData();

        /* [cover parentID={11DC401C-3F2A-4395-84A1-80FA115CE6FF}]
        Prepare channels and result registers [/cover] */
        Adc_lPrepareGrpForStart(lKernelId, lGroupId, lCoreId);
        
        /* Enable ISR servicing for the request source */
        lKernelDataPtr->RSData[lGrpCfgPtr->GrpPriority].IsrNoServiceFlag \
          =(uint8)0U;

        /* [cover parentID={FB9D8412-7C98-48e5-8581-6594F90AE04B}]
        Prepare queue and Enable Hardware trigger peripheral conversion
        [/cover] */
        Adc_lStartHwConversion(lGrpCfgPtr, lKernelId, lGrpCfgPtr->GrpPriority);
      #endif
    }
  }
}
#endif

#if (ADC_HW_TRIGGER_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={6DE6E72B-D488-4665-8302-4801AAA6C11F},
                                 {BA6EFE0D-B9E6-4630-BF56-93FFA7D4CB7F}]      **
**                                                                            **
** Syntax           : void Adc_DisableHardwareTrigger                         **
**                    (                                                       **
**                      const Adc_GroupType Group                             **
**                    )                                                       **
**                                                                            **
** Description      : This function  stops the ongoing conversion and disables**
**                    hardware trigger for the requested ADC Channel group.   **
**                    Note: This API is available only when AdcHwTriggerApi   **
**                    is configured as true.                                  **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x06                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for channel groups executing on different     **
**                    ADC hardware groups                                     **
**                                                                            **
** Parameters(in)   : Group - Numeric ID of requested ADC Channel group.      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : void                                                    **
**                                                                            **
*******************************************************************************/
void Adc_DisableHardwareTrigger(const Adc_GroupType Group)
{
  uint32 lKernelId, lCoreId;
  Adc_GroupType lGroupId;
  #if((ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
      (ADC_DEV_ERROR_DETECT == STD_ON))
  uint8 lErrVal;
  #endif

  /* Get the core Id from which it is called */
  lCoreId = Mcal_GetCpuIndex();

  /* Extract Kernel ID from Group */
  lKernelId = Adc_lGetAdcKernel(Group);
  /* Extract Kernel specific GroupID from Group*/
  lGroupId = Adc_lGetKernelGroupId(Group);
  /* [cover parentID={9DBA16F5-A65C-4935-999E-A595B4A722B7}]
  DET is ON or SAFETY is ON [/cover] */
  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))
  /* Check DET's for the API */
  lErrVal = Adc_lDisHwTriggerDetCheck(lKernelId, lGroupId, lCoreId);
  /* [cover parentID={AFA59FD4-1BBD-46fe-B457-CC17A1D0C485}]
  Disable Hardware Trigger DET Error [/cover] */
  if(ADC_E_NO_ERR == lErrVal)
  #endif
  {
    /* [cover parentID={CB4C4760-8666-448b-9B61-F1CF44156EC7}]
    DET is ON for AUTOSAR version 4.2.2 or SAFETY is ON or Runtime Error
    Detection is ON [/cover] */
    #if((ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
         ((MCAL_AR_VERSION == MCAL_AR_422) && (ADC_DEV_ERROR_DETECT == STD_ON)))
    /* [cover parentID={4CB7CB24-8CBE-4fbc-A8C7-196A8A9C7E22}]
    Critcal Section [/cover] */
    /* [cover parentID={283048CA-2BBB-49bf-AB96-40169319E65A}]
    Start of Critical Section [/cover] */
    SchM_Enter_Adc_KernelData();
    
    /* [cover parentID={BFA2B421-2D78-4442-8D11-71ABA28DEACF}]
    Check Group Idle Development or Runtime Error [/cover] */
    lErrVal = Adc_lCheckGrpIdleDet(lKernelId,lGroupId,\
                                   ADC_SID_DISABLE_HARDWARE_TRIGGER,lCoreId);
    /* [cover parentID={41FE7B88-72A6-43f0-B7D0-07DD3B5F8CCB}]
    Group Idle Error [/cover] */
    if(ADC_E_NO_ERR != lErrVal)
    {
      /* [cover parentID={437D992F-BE41-4732-A0CD-EC314E550371}]
      End of Critical Section [/cover] */
      SchM_Exit_Adc_KernelData();
    }
    else
    #endif
    {
      /* [cover parentID={E1ADE6F3-5111-4bb0-AE41-4ED80117EBFC}]
      Is QUEUE mode is ON or Prioirty mode is ON? [/cover] */
      /* [cover parentID={A0E5A739-A65B-4017-AE99-537291BED1D6}]
      Priority Mode is ON or Queueing Mode is ON [/cover] */
      /* [cover parentID={BD98810D-E2B8-4bca-8693-753D9F7460CD}]
      Critcal Section [/cover] */
      #if((ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) ||\
          (ADC_ENABLE_QUEUING == STD_ON))
        /* AUTOSAR version is 4.2.2 */
        #if (MCAL_AR_VERSION == MCAL_AR_422)
        /* [cover parentID={68570614-413B-41ef-BC15-F8C981EF9547}]
        DET is OFF and Safety is OFF when Autosar version is 4.2.2 [/cover] */
        #if((ADC_SAFETY_ENABLE == STD_OFF) && (ADC_DEV_ERROR_DETECT == STD_OFF))
        /* [cover parentID={5FD8EA13-987D-411e-9549-F9ABBBD2648F}]
        Start of Critical Section [/cover] */
            SchM_Enter_Adc_KernelData();
        #endif
        /* AUTOSAR version is 4.4.0 */
        #else
        /* [cover parentID={68570614-413B-41ef-BC15-F8C981EF9547}]
        Runtime error detection is OFF and Safety is OFF when Autosar version
        is 4.4.0 [/cover] */
        #if((ADC_SAFETY_ENABLE==STD_OFF) && (ADC_RUNTIME_ERROR_DETECT==STD_OFF))
        /* [cover parentID={5FD8EA13-987D-411e-9549-F9ABBBD2648F}]
        Start of Critical Section [/cover] */
            SchM_Enter_Adc_KernelData();
        #endif
        #endif
        /* [cover parentID={D5A96981-9062-46c5-8C81-49855C1607AC}]
        HW-SW Priority is ON [/cover] */
        #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
          /* [cover parentID={07607915-FF37-40ca-8BB7-D15D8C760601}]
          Stop group or remove it from queue of pending groups [/cover] */
          Adc_lSchedulerOnStop(lKernelId,lGroupId,lCoreId);
        #else
          /* [cover parentID={1F72FBDD-BD75-4ebe-B685-F6AA2C6728A0}]
          HW-SW Priority is OFF [/cover] */
          /* [cover parentID={E1E45B0A-E0C2-4bda-A480-88B9E838BAE6}]
          Pop from the Queue  [/cover] */
          Adc_lPopFromQueue(lKernelId,lGroupId,lCoreId);
        #endif
        /* [cover parentID={DB6DAE87-3250-4434-9540-4F8E27C2CA48}]
        End of Critical Section [/cover] */
        SchM_Exit_Adc_KernelData();
      #else
        /* [cover parentID={01C07362-3EEB-473a-B68E-32C35628152D}]
        Priority is OFF and Queueing Mode is OFF [/cover] */
        /* [cover parentID={A6CAA948-17B5-4d40-A5BE-0933098A5737}]
        Critical Section [/cover] */
        Adc_GlobalDataType *lKernelDataPtr;
        const Adc_GroupCfgType *lGrpCfgPtr;

        /* Get global state data location for the Kernel */
        lKernelDataPtr = Adc_lGetKernelDataAddress(lKernelId,lCoreId);
        /* Get group configuration address */
        lGrpCfgPtr =  &(Adc_ConfigPtr->CoreCfgPtr[lCoreId]->\
                        HwUnitCfgPtr[lKernelId]->GrpCfgPtr[lGroupId]);
        /* [cover parentID={36745ABA-9E53-45fb-AF09-6FFFCE26D974}]
        Critical Section   [/cover] */
        /* AUTOSAR version is 4.2.2 */
        #if (MCAL_AR_VERSION == MCAL_AR_422)
        /* [cover parentID={36745ABA-9E53-45fb-AF09-6FFFCE26D974}]
        DET is OFF and Safety is OFF when Autosar version is 4.2.2 [/cover] */
        #if((ADC_SAFETY_ENABLE == STD_OFF) && (ADC_DEV_ERROR_DETECT == STD_OFF))
        /* [cover parentID={DB89E451-EAE7-4595-A1BE-8D5F5863AFDE}]
        Start of Critical Section [/cover] */
            SchM_Enter_Adc_KernelData();
        #endif
        /* AUTOSAR version is 4.4.0 */
        #else
        /* [cover parentID={36745ABA-9E53-45fb-AF09-6FFFCE26D974}]
        Runtime error detection is OFF and Safety is OFF when Autosar version
        is 4.4.0 [/cover] */
        #if((ADC_SAFETY_ENABLE==STD_OFF) && (ADC_RUNTIME_ERROR_DETECT==STD_OFF))
        /* [cover parentID={DB89E451-EAE7-4595-A1BE-8D5F5863AFDE}]
        Start of Critical Section [/cover] */
            SchM_Enter_Adc_KernelData();
        #endif
        #endif
        /* [cover parentID={505A9EFB-B97D-434c-967D-C90D5B9022FE}]
        Is Group Busy [/cover] */
        if(Adc_lGetGroupStatus(lKernelDataPtr,lGroupId) == (uint32)ADC_ONE_U)
        {
          /* [cover parentID={3142EDC9-A29A-4ea0-82D9-C85AFA46EE6B}]
          Disable ISR servicing for the Request Source [/cover] */
          lKernelDataPtr->RSData[lGrpCfgPtr->GrpPriority].IsrNoServiceFlag =\
                                                               (uint8)ADC_ONE_U;
          /* [cover parentID={C7651E50-F2E8-46ff-8626-713118FDECB7}]
          End of Critical Section [/cover] */
          SchM_Exit_Adc_KernelData();
          /* [cover parentID={F006871C-B584-44f3-8F5D-FAD0AF47F585}]
          Stop the ongoing conversions [/cover] */
          Adc_lStopConvRequest(lGrpCfgPtr,lKernelId,lGrpCfgPtr->GrpPriority);
          /* Remove Active Group ID from the Global Kernel Data */
          Adc_lRemoveActiveGroup(lKernelDataPtr,lGrpCfgPtr,\
                                 lGrpCfgPtr->GrpPriority);
          /* [cover parentID={AF8ECF6E-A7D7-4ce6-8C1D-E7A29BB89CB2}]
          Sync Conversion is ON [/cover] */
          #if (ADC_SYNC_CONV_ENABLE == STD_ON)
          /* [cover parentID={DBF50E82-A5ED-48fa-9E99-352F95D5632B}]
          Critical Section [/cover] */
          /* [cover parentID={A25AC1DE-FEFF-4878-81A5-B517747FA4D5}]
          Start of Critical Section [/cover] */
          SchM_Enter_Adc_KernelData();
          /* [cover parentID={1394231A-36C0-4b6b-B3C7-2851187B0A0B}]
          Clear all running channels & Registers [/cover] */
          Adc_lClrRunningChAndResReg(lKernelId,lGrpCfgPtr,lCoreId);
          /* [cover parentID={F2120D8B-713D-41ee-906B-A7A3F5C9E8D3}]
          Start of Critical Section [/cover] */
          SchM_Exit_Adc_KernelData();
          #endif
        }
        else
        {
          /* [cover parentID={9EC4626C-D43E-4d4e-847E-AA67C5E20015}]
          End of Critical Section [/cover] */
          SchM_Exit_Adc_KernelData();
        }

        /* [cover parentID={057C4D45-A5D9-4c15-A114-8CB1F397ED31}]
        Critcal Section [/cover] */
        /* [cover parentID={4275311F-FDBC-4d1e-B7DF-2DF4D9FE21D3}]
        Start of Critical Section [/cover] */
        SchM_Enter_Adc_KernelData();
        /*Restore group status to IDLE*/
        /* [cover parentID={B378BCDC-9726-4502-AC63-EBACA074157B}]
        Clear Group Busy Status  [/cover] */
        Adc_lClrGroupStatusBusyAtomic(lKernelDataPtr,lGroupId);
        /* [cover parentID={8EDF33D8-8823-44f0-85D2-B49CB0EB6C17}]
        Clear Group Result [/cover] */
        Adc_lClrGroupResultAtomic(lKernelDataPtr,lGroupId);
        /* [cover parentID={096C1317-F043-4fbd-9C7C-9C213B2C1764}]
        Clear Result Buffer End Status [/cover] */
        Adc_lClrResBuffEndStatusAtomic(lKernelDataPtr,lGroupId);
        /* [cover parentID={53FB2EB0-9DBE-449a-959B-BB1EC416712C}]
        DMA Mode Result handling is OFF [/cover] */
        #if (ADC_RESULT_HANDLING_IMPLEMENTATION != ADC_DMA_MODE_RESULT_HANDLING)
        /* [cover parentID={B5C50125-B212-43c8-9ECB-D3A2D4307250}]
        Reset conversion result count to 0 [/cover] */
        lKernelDataPtr->NumofValidConRes[lGroupId] \
          = (Adc_StreamNumSampleType)0U;
        #endif
        /* [cover parentID={E5B6E623-E8EC-455a-A572-4902914F9E30}]
        Group Notify Capability is ON [/cover] */
        #if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
        /* [cover parentID={7A677A53-0259-4378-B847-3A3C3F38F741}]
        Disable Group Notification if Enabled  [/cover] */
        Adc_lClrGrpNotifAtomic(lKernelDataPtr,lGroupId);
        #endif

        /* [cover parentID={4D7A90B2-BE4A-49fb-AD79-23293C8FED6B}]
        End of Critical Section [/cover] */
        SchM_Exit_Adc_KernelData();
      #endif
    }
  }
}
#endif

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={7A184FF1-BFEB-4a52-BCC6-C68AD3B1B12C},
                                 {BA6EFE0D-B9E6-4630-BF56-93FFA7D4CB7F}]      **
**                                                                            **
** Syntax           : void Adc_EnableGroupNotification                        **
**                    (                                                       **
**                      const Adc_GroupType Group                             **
**                    )                                                       **
**                                                                            **
** Description      : This API enables the notification mechanism for the     **
**                    requested ADC Channel group.                            **
**                    Note: This API is only available when                   **
**                    AdcGrpNotifCapability is configures as true.            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x07                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different channel groups                  **
**                                                                            **
** Parameters(in)   : Group - Numeric ID of requested ADC Channel group.      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : void                                                    **
**                                                                            **
*******************************************************************************/
void Adc_EnableGroupNotification(const Adc_GroupType Group)
{
  Adc_GlobalDataType *lKernelDataPtr;
  uint32 lKernelId;
  uint32 lCoreId;
  Adc_GroupType lGroupId;

  /* Get the core Id from which it is called */
  lCoreId = Mcal_GetCpuIndex();

  /* Extract Kernel ID from Group */
  lKernelId = Adc_lGetAdcKernel(Group);
  /* Extract Kernel specific GroupID from Group*/
  lGroupId = Adc_lGetKernelGroupId(Group);

  /* [cover parentID={7C163C3C-4DD8-4fe4-BD6D-6514BFA6AC72}]
  DET is ON or SAFETY is ON [/cover] */
  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))

  uint8 lDetVal;
  /* Check DET's for the API */
  lDetVal = Adc_lEnGrpNotifDetCheck(lKernelId, lGroupId, lCoreId);
  /* [cover parentID={02F4CE7C-B9A4-4e79-B601-6F88DF959F50}]
  Enable Group Notify DET Error  [/cover] */
  if(ADC_E_NO_ERR == lDetVal)
  #endif
  {
    /* Get global state data location for the Kernel */
    lKernelDataPtr = Adc_lGetKernelDataAddress(lKernelId, lCoreId);
    /* [cover parentID={5E3A08FE-9DA9-434a-B4C9-DE3FBCBC6A1D}]
    Enable Group Notifications [/cover] */
    Adc_lSetGrpNotifAtomic(lKernelDataPtr, lGroupId);
  }
}
#endif

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={4470141E-4BB1-498e-ABB4-7F1E009E1FC9},
                                 {BA6EFE0D-B9E6-4630-BF56-93FFA7D4CB7F}]      **
**                                                                            **
** Syntax           : void Adc_DisableGroupNotification                       **
**                    (                                                       **
**                      const Adc_GroupType Group                             **
**                    )                                                       **
**                                                                            **
** Description      : This API disables the notification mechanism for the    **
**                    requested ADC Channel group.                            **
**                    Note: This API is only available when                   **
**                    AdcGrpNotifCapability is configures as true.            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x08                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different channel groups                  **
**                                                                            **
** Parameters(in)   : Group - Numeric ID of requested ADC Channel group.      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : void                                                    **
**                                                                            **
*******************************************************************************/
void Adc_DisableGroupNotification(const Adc_GroupType Group)
{
  Adc_GlobalDataType *lKernelDataPtr;
  uint32 lKernelId, lCoreId;
  Adc_GroupType lGroupId;

  /* Get the core Id from which it is called */
  lCoreId = Mcal_GetCpuIndex();

  /* Extract Kernel ID from Group */
  lKernelId = Adc_lGetAdcKernel(Group);
  /* Extract Kernel specific GroupID from Group */
  lGroupId = Adc_lGetKernelGroupId(Group);

  /* [cover parentID={C2703D75-5E4A-46a4-A498-AF283C03FACD}]
  DET is ON or SAFETY is ON [/cover] */
  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))

  uint8 lDetVal;
  /* Check DET's for the API */
  lDetVal = Adc_lDisGrpNotifDetCheck(lKernelId, lGroupId, lCoreId);
  /* [cover parentID={BEF0E7C8-99B1-40ac-8E06-BD7A2E05B23A}]
  Disable Group Notify DET Error  [/cover] */
  if(ADC_E_NO_ERR == lDetVal)
  #endif
  {
    /* Get global state data location for the Kernel */
    lKernelDataPtr = Adc_lGetKernelDataAddress(lKernelId, lCoreId);
    /* [cover parentID={9B2B6A79-69C8-4bad-BF8E-0A80375A8A51}]
    Disable Group Notification [/cover] */
    Adc_lClrGrpNotifAtomic(lKernelDataPtr, lGroupId);
  }
}
#endif

/*******************************************************************************
** Traceability: [cover parentID={27A8A099-530D-4a3f-988C-47EB6F8C7D00},
                                 {BA6EFE0D-B9E6-4630-BF56-93FFA7D4CB7F}]      **
**                                                                            **
** Syntax           : Adc_StatusType Adc_GetGroupStatus                       **
**                    (                                                       **
**                      const Adc_GroupType Group                             **
**                    )                                                       **
**                                                                            **
** Description      : This API returns the conversion status of the requested **
**                    ADC Channel group.                                      **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x09                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different channel groups                  **
**                                                                            **
** Parameters(in)   : Group - Numeric ID of requested ADC Channel group.      **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : Adc_StatusType                                          **
**                    Conversion status for the requested group               **
**                                                                            **
*******************************************************************************/
Adc_StatusType Adc_GetGroupStatus(const Adc_GroupType Group)
{
  const Adc_GlobalDataType *lKernelDataPtr;
  uint32 lKernelId, lStrmCompletedFlag, lResultFlag, lBusyFlag, lCoreId;
  Adc_GroupType lGroupId;
  Adc_StatusType lRetVal;

  /* Get the core Id from which it is called */
  lCoreId = Mcal_GetCpuIndex();

  /* Extract Kernel ID from Group */
  lKernelId = Adc_lGetAdcKernel(Group);
  /* Extract Kernel specific GroupID from Group*/
  lGroupId = Adc_lGetKernelGroupId(Group);

  /* [cover parentID={5C7C41B7-A07C-42ba-85B6-35AC8CA97EDC}]
  DET is ON or SAFETY is ON [/cover] */
  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))

  uint8 lDetVal;
  /* Check DET's for the API */
  lDetVal = Adc_lGetGrpStatusDetCheck(lKernelId, lGroupId, lCoreId);
  /* [cover parentID={3B62AF23-670C-438a-8262-7590544DAC21}]
  Group Status DET Error [/cover] */
  if(ADC_E_NO_ERR != lDetVal)
  {
    /* Return status as IDLE in case of DET */
    lRetVal = ADC_IDLE;
  }
  else
  #endif
  {
    /* Get global state data location for the Kernel */
    lKernelDataPtr = Adc_lGetKernelDataAddress(lKernelId, lCoreId);

    /* [cover parentID={0196B5F2-1419-49a5-8C5A-7BD2DEB09EF6}]
    Critcal Section   [/cover] */
    /* [cover parentID={5A4BA557-0414-4403-97DE-10A43EA04F93}]
    Start of Critical Section [/cover] */
    SchM_Enter_Adc_KernelData();

    /* [cover parentID={8E42CE39-314B-478f-B513-0E9744F6E5DA}]
    Read Result Buffer End Status [/cover] */
    lStrmCompletedFlag = Adc_lGetResBuffEndStatus(lKernelDataPtr, lGroupId);
    /* [cover parentID={027E4F95-FA66-4b64-8C40-796067AB399B}]
    Read Group Result Status [/cover] */
    lResultFlag = Adc_lGetGroupResultStatus(lKernelDataPtr, lGroupId);
    /* [cover parentID={70F6F60D-581A-498f-AFAD-941A4ED4129A}]
    Read Group Status [/cover] */
    lBusyFlag = Adc_lGetGroupStatus(lKernelDataPtr, lGroupId);

    /* [cover parentID={385400E5-AE2D-47e6-AA58-F649F3EA021C}]
    End of Critical Section [/cover] */
    SchM_Exit_Adc_KernelData();

    /* [cover parentID={6049AC9B-9BD4-495e-B019-B1352A306085}]
    Result Buffer End status is True [/cover] */
    if((uint32)ADC_ONE_U == lStrmCompletedFlag)
    {
      /* [cover parentID={E51BA18A-CBEA-4743-BC24-EE91FBC8AE72}]
      Update return value as Adc Stream Completed   [/cover] */
      lRetVal = ADC_STREAM_COMPLETED;
    }
    /* [cover parentID={D605F55F-1D0F-4c5c-8941-60722136CC1D}]
    Group Result status is True [/cover] */
    else if((uint32)ADC_ONE_U == lResultFlag)
    {
      /* [cover parentID={AE9CD3D2-B80C-462e-83D8-95F5ADBF2F30}]
      Update return value as Adc Completed     [/cover] */
      lRetVal = ADC_COMPLETED;
    }
    /* [cover parentID={1D6A5632-E2CA-4dff-9CC3-694DF27AD606}]
    Group status is True [/cover] */
    else if((uint32)ADC_ONE_U == lBusyFlag)
    {
      /* [cover parentID={B74DD191-2A38-4b9f-901B-0A4DD4AD30E2}]
      Update return value as Adc Busy [/cover] */
      lRetVal = ADC_BUSY;
    }
    else
    {
      /* [cover parentID={D4EA1640-B061-4dc4-92C6-A567CFE8F5DD}]
      Update return value as Adc Idle    [/cover] */
      lRetVal = ADC_IDLE;
    }
  }
  return(lRetVal);
}

#if(ADC_RESULT_HANDLING_IMPLEMENTATION != ADC_DMA_MODE_RESULT_HANDLING)
/*CYCLOMATIC_Adc_GetStreamLastPointer_JUSTIFICATION: This API returns the number
of valid samples per channel and pointer to the result buffer containing the
latest available conversion results and performs the DET or Safety or Runtime
Error check for AR422 and AR440 based on the enable of pre-compile macros.
The different if conditions cause the complexity to increase, but actually
during run-time out of all if conditions many will be pre-compile time removed*/
/*******************************************************************************
** Traceability: [cover parentID={55DAAA3E-BD02-466d-A350-DB68D50EE588},
                                 {BA6EFE0D-B9E6-4630-BF56-93FFA7D4CB7F}]      **
**                                                                            **
** Syntax           : Adc_StreamNumSampleType Adc_GetStreamLastPointer        **
**                    (                                                       **
**                      const Adc_GroupType Group                             **
**                      Adc_ValueGroupType ** const PtrToSamplePtr            **
**                    )                                                       **
**                                                                            **
** Description      : This API returns the number of valid samples per channel**
**                    stored in the result buffer. It also returns a pointer  **
**                    to the result buffer containing the latest available    **
**                    conversion results.                                     **
**                    Refer Adc_ReadGroup API for a description of the buffer **
**                    layout.                                                 **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x0b                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different AdcChannel Groups               **
**                                                                            **
** Parameters(in)   : Group - Numeric ID of requested ADC Channel group.      **
**                                                                            **
** Parameters (out) : PtrToSamplePtr - Pointer to the last acquired value.    **
**                                                                            **
** Return value     : Adc_StreamNumSampleType                                 **
**                    Number of valid samples per channel.                    **
**                                                                            **
*******************************************************************************/
Adc_StreamNumSampleType Adc_GetStreamLastPointer(\
       const Adc_GroupType Group,  Adc_ValueGroupType ** const PtrToSamplePtr)
{
  const Adc_GroupCfgType *lGrpCfgPtr;
  Adc_GlobalDataType *lKernelDataPtr;
  Adc_StreamNumSampleType lNoOfValidConv;
  uint32 lKernelId, lBusyFlag, lStrmCompletedFlag, lResultFlag, lCoreId;
  Adc_GroupType lGroupId;
  #if((ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
      (ADC_DEV_ERROR_DETECT == STD_ON))
  uint8 lErrVal;
  #endif

  /* Get the core Id from which it is called */
  lCoreId = Mcal_GetCpuIndex();

  /* Extract Kernel ID from Group */
  lKernelId = Adc_lGetAdcKernel(Group);
  /* Extract Kernel specific GroupID from Group*/
  lGroupId = Adc_lGetKernelGroupId(Group);
  /* [cover parentID={7C3114B9-5997-4029-9DB2-D28900629690}]
  DET is ON or SAFETY is ON [/cover] */
  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))
  /* Check DET's for the API */
  lErrVal = Adc_lGetStrmPtrDetCheck(lKernelId, lGroupId,PtrToSamplePtr,lCoreId);
  /* [cover parentID={8261AD0B-B4C8-4a0c-AF95-1E0E5E4D294C}]
  DET Error occurred [/cover] */
  if(ADC_E_NO_ERR != lErrVal)
  {
    /* [cover parentID={F577EF05-3617-4319-811F-6A88433E21C7}]
    Update Number of valid conversion to ZERO [/cover] */
    lNoOfValidConv = (Adc_StreamNumSampleType)0U;
    /* [cover parentID={849147A1-CF31-408b-B8CF-3CEDB5638239}]
    Pointer to Sample pointer is a NULL pointer [/cover] */
    if(PtrToSamplePtr != NULL_PTR)
    {
      /* [cover parentID={28BEE7CF-935B-40b0-8735-9DFBCF7558D4}]
      Update pointer to sample pointer with a NULL pointer [/cover] */
      *PtrToSamplePtr = NULL_PTR;
    }
  }
  else
  #endif
  {
    /* [cover parentID={91CB0882-047B-4e0f-ACFD-9ABD656D8052}]
    DET is ON for AUTOSAR version 4.2.2 or SAFETY is ON or Runtime Error
    Detection is ON [/cover] */
    #if((ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
         ((MCAL_AR_VERSION == MCAL_AR_422) && (ADC_DEV_ERROR_DETECT == STD_ON)))
    /* [cover parentID={A602615D-05D6-4ddb-BECF-B25387278200}]
    Critcal Section [/cover] */
    /* [cover parentID={9D0A2FD1-472E-4bb6-BB82-F01DD724CCF5}]
    Start of Critical Section [/cover] */
    SchM_Enter_Adc_KernelData();

    /* [cover parentID={1A860E47-8ECD-4b9a-A0AA-98DB1ED515BA}]
    Check Group Idle Error [/cover] */
    lErrVal = Adc_lCheckGrpIdleDet(lKernelId, lGroupId, \
                                   ADC_SID_GET_STREAM_LAST_POINTER, lCoreId);
    /* [cover parentID={B7116175-0BA6-4a51-BF5E-E9F08C8CDED5}]
    Group Idle Error   [/cover] */
    if(ADC_E_NO_ERR != lErrVal)
    {
      /* [cover parentID={B0304201-C355-4889-A748-F4E380649148}]
      End of Critical Section [/cover] */
      SchM_Exit_Adc_KernelData();

      /* [cover parentID={F577EF05-3617-4319-811F-6A88433E21C7}]
      Update Number of valid conversion to ZERO [/cover] */
      lNoOfValidConv = (Adc_StreamNumSampleType)0U;

      /* [cover parentID={28BEE7CF-935B-40b0-8735-9DFBCF7558D4}]
      Update pointer to sample pointer with a NULL pointer [/cover] */
      *PtrToSamplePtr = NULL_PTR;
    }
    else
    #endif
    {
      /* [cover parentID={AB0B9310-22C1-4866-BEE0-3C82E6C0F4BD}]
      Critcal Section [/cover] */
      /* Get global state data location for the Kernel */
      lKernelDataPtr = Adc_lGetKernelDataAddress(lKernelId, lCoreId);
      /* Get group configuration address */
      lGrpCfgPtr = &(Adc_ConfigPtr->CoreCfgPtr[lCoreId]->\
                     HwUnitCfgPtr[lKernelId]->GrpCfgPtr[lGroupId]);

      /*The status flags and number of valid results are read in critical
      section. The calculation of the last result set pointer location need not
      be in critical section*/
      /* AUTOSAR version is 4.2.2 */
      #if (MCAL_AR_VERSION == MCAL_AR_422)
      /* [cover parentID={C7E8D32F-38C0-49d3-B621-22812053B1BF}]
      DET is OFF and Safety is OFF when Autosar version is 4.2.2 [/cover] */
      #if((ADC_SAFETY_ENABLE == STD_OFF) && (ADC_DEV_ERROR_DETECT == STD_OFF))
      /* [cover parentID={FB052376-D0DB-4796-BE35-A9A3192149C9}]
      Start of Critical Section [/cover] */
          SchM_Enter_Adc_KernelData();
      #endif
      /* AUTOSAR version is 4.4.0 */
      #else
      /* [cover parentID={C7E8D32F-38C0-49d3-B621-22812053B1BF}]
      Runtime error detection is OFF and Safety is OFF when Autosar version is
      4.4.0 [/cover] */
      #if((ADC_SAFETY_ENABLE==STD_OFF) && (ADC_RUNTIME_ERROR_DETECT==STD_OFF))
      /* [cover parentID={FB052376-D0DB-4796-BE35-A9A3192149C9}]
      Start of Critical Section [/cover] */
          SchM_Enter_Adc_KernelData();
      #endif
      #endif

      /* [cover parentID={F6A7EA0E-0317-4e11-9A18-6177D4ED1987}]
      Read Result Buffer End Status [/cover] */
      lStrmCompletedFlag = Adc_lGetResBuffEndStatus(lKernelDataPtr, lGroupId);
      lResultFlag = Adc_lGetGroupResultStatus(lKernelDataPtr, lGroupId);
      lBusyFlag = Adc_lGetGroupStatus(lKernelDataPtr, lGroupId);
      lNoOfValidConv = lKernelDataPtr->NumofValidConRes[lGroupId];

      /* [cover parentID={7250C8FA-697D-436e-A833-39FB0B5341A7}]
      Is Group busy with no results [/cover] */
      if((lBusyFlag == (uint32)1U) && (lResultFlag == (uint32)0U))
      {
        /* [cover parentID={575629CF-B4CC-4d48-BB34-30DFC90A65E9}]
        Conversion ongoing but No result set availabe yet [/cover] */
        /* [cover parentID={15DF6302-8D78-4eaf-BE05-1DF86B6C8DBC}]
        End of Critical Section [/cover] */
        SchM_Exit_Adc_KernelData();
        /* [cover parentID={F577EF05-3617-4319-811F-6A88433E21C7}]
        Update Number of valid conversion to ZERO & NULL pointer for pointer to
        sample pointer [/cover] */
        lNoOfValidConv = (Adc_StreamNumSampleType)0U;
        *PtrToSamplePtr = NULL_PTR;
      }
      else
      {
        /* [cover parentID={B7593182-0F99-4610-A568-17F78E821CF6}]
        Clear Group Result  [/cover] */
        Adc_lClrGroupResultAtomic(lKernelDataPtr, lGroupId);
        /* [cover parentID={750080D2-CC24-469e-AB65-6579A7686066}]
        Clear Result Buffer End Status [/cover] */
        Adc_lClrResBuffEndStatusAtomic(lKernelDataPtr, lGroupId);

        /* [cover parentID={F6366990-9AED-47c8-B6B8-7B50C78D7D03}]
        Put Groups to Idle state,which are not converting and are implicitly
        stopped [/cover] */
        if(lBusyFlag == (uint32)0U)
        {
          /* [cover parentID={D868F88A-EA66-4982-A7D9-D061B79DDF55}]
          Read number of Valid conversion counts [/cover] */
          lKernelDataPtr->NumofValidConRes[lGroupId] = \
                                               (Adc_StreamNumSampleType)0U;
        }
        /* [cover parentID={0AF8010C-70E8-432d-A9AE-D82C3E0871F8}]
        End of Critical Section [/cover] */
        SchM_Exit_Adc_KernelData();

        /* [cover parentID={131FD8E2-56FE-463d-830D-01B717AE4311}]
        Update current valid result position to pointer to sample pointer
        [/cover] */
        *PtrToSamplePtr = &((lKernelDataPtr->GrpResBuffer[lGroupId])\
        [lNoOfValidConv - (Adc_StreamNumSampleType)1U]);

        /* [cover parentID={EB656AD9-60A8-4c39-B095-D37808B79107}]
        Stream Samples Completed [/cover] */
        if(lStrmCompletedFlag == (uint32)ADC_ONE_U)
        {
          /* [cover parentID={74CA7590-F584-4b29-BF9D-5DCD6B64536A}]
          No of Valid conversions are equal to No of configured Samples
          [/cover]*/
          lNoOfValidConv = lGrpCfgPtr->NumOfSamples;
        }
      }
    }
  }
  return(lNoOfValidConv);
}
#endif

#if(ADC_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={072F1443-09A2-4b4b-A538-85815FA2E68C},      **
**                               {BA6EFE0D-B9E6-4630-BF56-93FFA7D4CB7F}]      **
**                                                                            **
** Syntax           : void Adc_GetVersionInfo                                 **
**                    (                                                       **
**                      Std_VersionInfoType * const versioninfo               **
**                    )                                                       **
**                                                                            **
** Description      : This API returns the version information of this module.**
**                    Note: This API is available only when AdcVersionInfoApi **
**                    is configured as true.                                  **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x0a                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : versioninfo -  Pointer to where to store the version    **
**                    information of this module                              **
**                                                                            **
** Return value     : void                                                    **
**                                                                            **
*******************************************************************************/
void Adc_GetVersionInfo(Std_VersionInfoType * const versioninfo)
{
  /* [cover parentID={3F356509-3143-40ae-9ACA-883508FFF0E3}]
  DET is ON or SAFETY is ON [/cover] */
  #if((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))
  uint8 lErrVal;
  lErrVal = Adc_lCheckParamPointerDet(versioninfo, ADC_SID_GET_VERSION_INFO);
  /* [cover parentID={852F8896-A4B1-4713-B8C9-7D59D6608A21}]
  Param Pointer DET Error  [/cover] */
  if (ADC_E_NO_ERR == lErrVal)
  #endif
  {
    /* [cover parentID={920D10EE-6C58-4146-BE3F-0A9A115ACC04}]
    Update Version Information in the location referenced by versioninfo
    [/cover] */
    /* [cover parentID={9BD4444B-68F8-4ce1-9F0A-1B6090310D54}]
    Adc_GetVersionInfo [/cover] */
    versioninfo->moduleID = (uint16)ADC_MODULE_ID;
    versioninfo->vendorID = (uint16)ADC_VENDOR_ID;
    versioninfo->sw_major_version = (uint8)ADC_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = (uint8)ADC_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = (uint8)ADC_SW_PATCH_VERSION;
  }
}
#endif

#if(ADC_LOW_POWER_STATE_SUPPORT == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={2D15A3EE-022B-4aa9-BEA3-C3C837ACC3FB},
                                 {BA6EFE0D-B9E6-4630-BF56-93FFA7D4CB7F}]      **
**                                                                            **
** Syntax           : Std_ReturnType Adc_PreparePowerState                    **
**                    (                                                       **
**                      const Adc_PowerStateType PowerState                   **
**                      Adc_PowerStateRequestResultType * const Result        **
**                    )                                                       **
**                                                                            **
** Description      : API starts the needed process to allow the ADC hardware **
**                    module to enter the target power state if current power **
**                    state of all the hardware units is not same as the      **
**                    target power state. The API must be invoked from all the**
**                    cores using the ADC driver, as each call prepares the   **
**                    power state only for the ADC hardware groups used by the**
**                    calling core.                                           **
**                    Note: This API is available only when                   **
**                    AdcLowPowerStatesSupport is configured as true.         **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x13                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different CPU cores                       **
**                                                                            **
** Parameters(in)   : PowerState - Target power state intended to be attained **
**                                                                            **
** Parameters (out) : Result - Result of Power state change preparation       **
**                                                                            **
** Return value     : E_OK: Preparation process started                       **
**                    E_NOT_OK: Service is rejected                           **
*******************************************************************************/
Std_ReturnType Adc_PreparePowerState(const Adc_PowerStateType PowerState,
                                Adc_PowerStateRequestResultType * const Result)
{
  Std_ReturnType lRetVal;
  uint32 lCoreId, lBitPosn, lTempPowerState;
  uint8 lPwrState;

  /* Get the core Id from which it is called */
  lCoreId = Mcal_GetCpuIndex();
  /* [cover parentID={FCB6A86A-0B22-4cda-8528-907A942AFD66}]
  DET is ON or SAFETY is ON [/cover] */
  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))
  uint8 lDetVal;
  /* Check DET's for the API */
  lDetVal = Adc_lPreparePowerStateDetCheck(PowerState, Result, lCoreId);
  /* [cover parentID={1C90A9AD-AEB8-4751-831E-2FB1A4F93946}]
  Prepare power state DET error occured [/cover] */
  if(lDetVal != ADC_E_NO_ERR)
  {
    /* [cover parentID={823E5C83-8EF0-48ee-B79A-C375ED2DC9F4}]
    Update return value with E_NOT_OK [/cover] */
    lRetVal = E_NOT_OK;
  }
  else
  #endif
  {
    /* [cover parentID={9B9BB9B4-C945-4d3b-892F-C8F1EE82A618}]
    Get the current power state of the ADC hardware units [/cover] */
    lPwrState = Adc_lGetCurrentPwrState(ADC_SID_PREPARE_POWER_STATE, lCoreId);

    /* [cover parentID={2F48DE02-37BB-43f1-BB2A-550DE7255B7F}]
    Current power state is a valid power state [/cover] */
    if(lPwrState != ADC_INVALID_POWER_STATE)
    {
      /* [cover parentID={C6835FA8-79AE-4330-8E5F-BED0BBAF6135}]
      Current power state is same as the configured power state [/cover] */
      if(lPwrState == PowerState)
      {
        /* [cover parentID={2D7C80D5-E49A-4436-9DE9-5BA03FCEB210}]
        Update result as ADC_SEQUENCE_ERROR [/cover] */
        *Result = ADC_SEQUENCE_ERROR;
      }
      else
      {
        /* [cover parentID={B4059497-57BA-40c5-B256-F0815B0F641F}]
        Update result as ADC_SERVICE_ACCEPTED [/cover] */
        *Result = ADC_SERVICE_ACCEPTED;

        /* Set the Power state transition request bit */
        lTempPowerState = ((uint32)PowerState << ADC_ONE_U) | ADC_ONE_U;

        /* Calculate bit position based on Core Id */
        lBitPosn = (lCoreId * (uint32)ADC_BITS_PER_POWER_STATE);

        /* [cover parentID={FA52DCC3-F7C9-4a1a-A5F5-E557879E1B3F}]
        Update the requested power state & request bit of the core [/cover] */
        Mcal_SetBitAtomic(&Adc_PowerStateTransitionRequestBit, (uint8)lBitPosn,\
                          ADC_BITS_PER_POWER_STATE, lTempPowerState);
      }
      /* [cover parentID={E98020AE-49D3-4270-B910-FE93C2F91F40}]
      Update return value as E_OK [/cover] */
      lRetVal = E_OK;
    }
    else
    {
      /* [cover parentID={21730EBD-88BA-49e9-880B-A6B6E44D343D}]
      Update result as ADC_HW_FAILURE [/cover] */
      *Result = ADC_HW_FAILURE;

      /* [cover parentID={5A748E76-0CE3-4fd9-AC6E-81CA14228ABD}]
      Update return value with E_NOT_OK [/cover] */
      lRetVal = E_NOT_OK;
    }
  }
  /* MISRA2012_RULE_2_2_JUSTIFICATION: Tricore Atomic instructions are used
  to update global variables in this function call, which is not detected
  by MISRA. Hence, the assignment is not a dead code*/
  return(lRetVal);
}
#endif

#if(ADC_LOW_POWER_STATE_SUPPORT == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={E7F3E2D7-36B5-4165-BEC5-C847DAEE25C3},
                                 {BA6EFE0D-B9E6-4630-BF56-93FFA7D4CB7F}]      **
**                                                                            **
** Syntax           : Std_ReturnType Adc_SetPowerState                        **
**                    (                                                       **
**                      Adc_PowerStateRequestResultType * const Result        **
**                    )                                                       **
**                                                                            **
** Description      : API configures the ADC module so that it enters the     **
**                    already prepared power state,chosen between a predefined**
**                    set of configured ones.The API must be invoked from all **
**                    the cores using the ADC driver, as each call sets the   **
**                    power state only for the ADC hardware groups used by    **
**                    the calling core                                        **
**             Note: 1.When the converter is set to 'full power mode', then   **
**                     the conversion is started immediately by the hardware  **
**                     after a request (no additional time delay). This is the**
**                     default mode after modules initialization.             **
**                   2.When the converter is set to 'Fast standby mode' or    **
**                     'Slow standby mode' and no conversion is requested,then**
**                     it saves power. When a conversion is triggered then the**
**                     converter wakes up automatically, but it needs certain **
**                     wake-up time before conversions can be performed. There**
**                     is no power saving while the conversions are being     **
**                     performed during this mode.During this phase the driver**
**                     reports the current power state as 'Fast standby mode' **
**                     or 'Slow standby mode'. In this mode, when the         **
**                     conversion is no longer active,then the converter saves**
**                     power and a new conversion request will trigger the    **
**                     wake-up cycle again (time delay for wake-up).          **
**                   3.When the converter is set to 'off mode',it enters power**
**                     saving mode and no further conversions are possible    **
**                     until a power mode transition is made explicitly to    **
**                     come out of 'off mode'.                                **
**                   4.This API is available only when                        **
**                     AdcLowPowerStatesSupport is configured as true.        **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x10                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different CPU cores                       **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : Result - Result of Power state change                   **
**                                                                            **
** Return value     : E_OK: Power Mode changed                                **
**                    E_NOT_OK: Service is rejected                           **
*******************************************************************************/
Std_ReturnType Adc_SetPowerState(Adc_PowerStateRequestResultType * const Result)
{
  Std_ReturnType lRetVal = E_NOT_OK;
  uint32 lKernelCount, lCoreId, lBitPosn, lTargetPwrState;
  #if((ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
      (ADC_DEV_ERROR_DETECT == STD_ON))
  uint8 lErrVal;
  #endif

  /* Get the core Id from which it is called */
  lCoreId = Mcal_GetCpuIndex();

  /* Calculate the bit position of power state based on CoreId */
  lBitPosn = lCoreId * (uint32)ADC_BITS_PER_POWER_STATE;

  /* [cover parentID={1FFD16DD-64DF-4d0e-8A2E-FC8D10631D1C}]
  Critical Section [/cover] */
  /* [cover parentID={2D5D4B6F-6378-480e-9611-1E19B88E4907}]
  Start of Critical Section [/cover] */
  SchM_Enter_Adc_KernelData();

  /* [cover parentID={C7DBA3B2-CB3E-412a-B6EB-75097C81808E}]
  Read the targeted power state [/cover] */
  lTargetPwrState = (uint32)(Mcal_GetBitAtomic(\
        Adc_PowerStateTransitionRequestBit,(uint8)lBitPosn, \
        (uint32)ADC_BITS_PER_POWER_STATE));
  /* [cover parentID={3810DB26-73B0-4975-9AA2-8557438C29CA}]
  DET is ON or SAFETY is ON [/cover] */
  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))

  /* Check DET's for the API */
  lErrVal = Adc_lSetPowerStateDetCheck(Result, lCoreId, lTargetPwrState);
  /* [cover parentID={90CAB158-699F-4404-AA23-2D31D7DF578B}]
  Is Set power state DET error occured ? [/cover] */
  if(ADC_E_NO_ERR != lErrVal)
  {
    /* [cover parentID={90D540FE-B05E-4456-BFE2-65C941BB9BB7}]
    Update return value with E_NOT_OK [/cover] */
    lRetVal = E_NOT_OK;
  }
  else
  #endif
  {
    /* [cover parentID={D888A158-062B-4597-9114-02F855E1F3D3}]
    DET is ON for AUTOSAR version 4.2.2 or SAFETY is ON or Runtime Error
    Detection is ON [/cover] */
    #if((ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
       ((MCAL_AR_VERSION == MCAL_AR_422) && (ADC_DEV_ERROR_DETECT == STD_ON)))
    /* [cover parentID={319328BE-2CA3-4904-80BC-B1A5C6E40FE7}]
    Check Hardware Unit DisEngaged Development or Runtime Error [/cover] */
    lErrVal = Adc_lCheckHwUnitDisEngagedDet(ADC_SID_SET_POWER_STATE,lCoreId);
    /* [cover parentID={2AED0954-03DA-4dcd-B44F-E7912DA7E2EE}]
    Hardware Unit DisEngaged Development or Runtime Error occurred [/cover] */
    if(ADC_E_NO_ERR != lErrVal)
    {
      /* [cover parentID={6B36A0C6-84A5-4762-AEC0-27032B8245EF}]
      Update result pointer with ADC_TRANS_NOT_POSSIBLE [/cover] */
      *Result = ADC_TRANS_NOT_POSSIBLE;
      
      /* Update return value with E_NOT_OK */
      lRetVal = E_NOT_OK;
    }
    else
    #endif
    {
      /* Right shift once to get the already prepared power mode */
      lTargetPwrState = \
                ADC_TARGET_POWER_STATE_MASK & (~(lTargetPwrState >> ADC_ONE_U));

      /* [cover parentID={F1B52FF7-E9F9-4b3a-ADD4-98DFDD6A9298}]
      Till the last available kernel [/cover] */
      for(lKernelCount = (uint32)0U; lKernelCount < ADC_MAX_KERNEL_ID; \
        lKernelCount++)
      {
          /* [cover parentID={E2C8755B-E78B-4393-AEEA-63FAF182BDA0}]
          Check if Kernel is Configured for current core */
        if(Adc_ConfigPtr->CoreCfgPtr[lCoreId]->HwUnitCfgPtr[lKernelCount] != \
                                                                       NULL_PTR)
        {
          /*Change ANONC only for MASTER and STANDALONE kernels*/
          /* [cover parentID={E2C8755B-E78B-4393-AEEA-63FAF182BDA0}]
          Set the already prepared power state for Master & Stand-alone Kernels
          [/cover] */
          if(Adc_ConfigPtr->CoreCfgPtr[lCoreId]->HwUnitCfgPtr[lKernelCount]->\
            SyncConvMode != ADC_SYNC_CONV_MODE_SLAVE)
          {
            /* MISRA2012_RULE_10_3_JUSTIFICATION: The bitfied of SFR are
            programed with an unsigned long value. Since, bitfields are of
            different type than unsigned long MISRA populates this warning.
            However the write is performed only to the intended bits by
            applying proper masks*/
            /* [cover parentID={E2C8755B-E78B-4393-AEEA-63FAF182BDA0}]
            Set the already prepared power state for Master & Stand-alone 
            Kernels [/cover] */
            MODULE_EVADC.G[lKernelCount].ARBCFG.B.ANONC = lTargetPwrState;
          }
        }
      }
      /* [cover parentID={78589036-BF32-4561-BBAE-D8A309E2C498}]
      Clear the power state & power state transition request [/cover] */
      Mcal_SetBitAtomic(&Adc_PowerStateTransitionRequestBit, (uint8)lBitPosn, \
                      ADC_BITS_PER_POWER_STATE, 0U);
      /* [cover parentID={4072E7F1-71CF-4fe0-989F-4A78890B2EE6}]
      Update return value with E_OK [/cover] */
      lRetVal = E_OK;

      /* [cover parentID={6F1E2592-2435-4f37-8E93-7C7920CA1853}]
      Update result with ADC_SERVICE_ACCEPTED [/cover] */
      *Result = ADC_SERVICE_ACCEPTED;
    }
  }
  /* [cover parentID={5C32FA12-8A4F-40c6-87BC-5F5466F8A544}]
  End of Critical Section [/cover] */
  SchM_Exit_Adc_KernelData();
  return(lRetVal);
}
#endif

#if(ADC_LOW_POWER_STATE_SUPPORT == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={A250E667-B430-4753-A4C4-EAA8C64D58BB}],
                                 {BA6EFE0D-B9E6-4630-BF56-93FFA7D4CB7F}]      **
**                                                                            **
** Syntax           : Std_ReturnType Adc_GetTargetPowerState                  **
**                    (                                                       **
**                      Adc_PowerStateType * const TargetPowerState           **
**                      Adc_PowerStateRequestResultType * const Result        **
**                    )                                                       **
**                                                                            **
** Description      : API reports the power state passed and successfully     **
**                    prepared during the Adc_PreparePowerState() If the power**
**                    state was not prepared, then the current power state of **
**                    hardware units of the invoking core is returned         **
**                    Note: This API is available only when                   **
**                          AdcLowPowerStatesSupport is configured as true.   **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x12                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters(out)   :Result - Result of Target Power mode                    **
**                    TargetPowerState - Target Power mode of ADC HW Units    **
**                                                                            **
** Return value     : E_OK: Mode could be read                                **
**                    E_NOT_OK: Service is rejected                           **
*******************************************************************************/
Std_ReturnType Adc_GetTargetPowerState(\
               Adc_PowerStateType * const TargetPowerState,
               Adc_PowerStateRequestResultType * const Result)
{
  Std_ReturnType lRetVal;
  uint32 lCoreId, lBitPosn;
  uint8 lPwrState;

  /* Get the core Id from which it is called */
  lCoreId = Mcal_GetCpuIndex();

  /* [cover parentID={2C8F62AF-2746-49a6-9163-EA2AE68F56DD}]
  DET is ON or SAFETY is ON [/cover] */
  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))
  uint8 lDetVal;
  /* Check DET's for the API */
  lDetVal = Adc_lGetPowerStateDetCheck(TargetPowerState, Result, \
                                       ADC_SID_GET_TARGET_POWER_STATE, lCoreId);
  /* [cover parentID={902064BC-E248-4ab2-8618-A064AC9A5EBC}]
  Is Get power state DET error occured? [/cover] */
  if(lDetVal != ADC_E_NO_ERR)
  {
    /* [cover parentID={F6F519F0-1D3B-4b64-B54A-C8B76BAA66BB}]
    Update return value with E_NOT_OK [/cover] */
    lRetVal = E_NOT_OK;
  }
  else
  #endif
  {
    /* Calculate the bit position of power state based on CoreId */
    lBitPosn = lCoreId * (uint32)ADC_BITS_PER_POWER_STATE;

    /* [cover parentID={FA4BDCEC-173D-42e2-97D3-9818A8374284}]
    Read the prepared power state and transition request bit [/cover] */
    lPwrState = (uint8)(Mcal_GetBitAtomic(Adc_PowerStateTransitionRequestBit, \
                           (uint8)lBitPosn, (uint32)ADC_BITS_PER_POWER_STATE));
    /* [cover parentID={1FD055F1-996A-488f-8F85-111ADB66112C}]
    Is target power state prepared? [/cover] */
    if(lPwrState != (uint8)0U)
    {
      /* [cover parentID={2D5613CD-5010-44ba-8E1B-9640AEF3A9F9}]
      Get the prepared power state [/cover] */
      lPwrState = (lPwrState >> ADC_ONE_U);
    }
    else
    {
      /* [cover parentID={B90FBAB2-B411-4b1c-9FB9-986E96BB1247}]
      Get the current power state of the ADC hardware units [/cover] */
      lPwrState = Adc_lGetCurrentPwrState(ADC_SID_GET_TARGET_POWER_STATE, \
                                          lCoreId);
    }
    /* [cover parentID={5DF629A0-66CF-4434-9CE2-E5CCCDC33A53}]
    Current power state is not a valid power state [/cover] */
    if(lPwrState == ADC_INVALID_POWER_STATE)
    {
      /* [cover parentID={F8C3D084-77E4-4ead-8510-D2BAE9127B1C}]
      Update result as ADC_HW_FAILURE [/cover] */
      *Result = ADC_HW_FAILURE;

      /* [cover parentID={38D30316-E7E2-4006-80D2-729925953299}]
      Update return value with E_NOT_OK [/cover] */
      lRetVal = E_NOT_OK;
    }
    else
    {
      /* [cover parentID={03AADFEF-A1E3-4f0a-99E7-4890D5E87349}]
      Update return value with E_OK [/cover] */
      lRetVal = E_OK;
      /* Update power state pointer with current or target power state */
      *TargetPowerState = (Adc_PowerStateType)lPwrState;
      /* [cover parentID={EB8040BB-F379-4e13-979D-9BB49FA88FD9}]
      Update result as ADC_SERVICE_ACCEPTED [/cover] */
      *Result = ADC_SERVICE_ACCEPTED;
    }
  }
  return(lRetVal);
}
#endif

#if(ADC_LOW_POWER_STATE_SUPPORT == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={D8F34FC8-2D68-4fed-BD87-3EEA89743F99},
                                 {BA6EFE0D-B9E6-4630-BF56-93FFA7D4CB7F}]      **
**                                                                            **
** Syntax           : Std_ReturnType Adc_GetCurrentPowerState                 **
**                    (                                                       **
**                      Adc_PowerStateType * const CurrentPowerState          **
**                      Adc_PowerStateRequestResultType * const Result        **
**                    )                                                       **
**                                                                            **
** Description      : API returns the current power state of the ADC hardware **
**                    groups used by the calling core.                        **
**                    Note: This API is available only when                   **
**                          AdcLowPowerStatesSupport is configured as true.   **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x11                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters(out)   :CurrentPowerState - Current Power mode of ADC HW Units  **
**                    Result - Result of Current Power mode                   **
**                                                                            **
** Return value     : E_OK: Mode could be read                                **
**                    E_NOT_OK: Service is rejected                           **
*******************************************************************************/
Std_ReturnType Adc_GetCurrentPowerState(\
               Adc_PowerStateType * const CurrentPowerState,
               Adc_PowerStateRequestResultType * const Result)
{
  Std_ReturnType lRetVal;
  uint32 lCoreId;
  uint8 lCurrentPwrState;

  /* Get the Core Id from which it is called */
  lCoreId = Mcal_GetCpuIndex();
  /* [cover parentID={D02E5A1F-8629-41fc-A1B8-8688BBADFBFF}]
  DET is ON or SAFETY is ON [/cover] */
  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))
  uint8 lDetVal;
  /* Check DET's for the API */
  lDetVal = Adc_lGetPowerStateDetCheck(CurrentPowerState, Result, \
                                       ADC_SID_GET_CURRENT_POWER_STATE,lCoreId);
  /* [cover parentID={2B5E67D3-0B0F-4718-9024-3F3812734AE6}]
  Is Get power state DET error occured? [/cover] */
  if(lDetVal != ADC_E_NO_ERR)
  {
    /* [cover parentID={E26D933F-CCA9-47e0-BA70-7CA4FB7D84CA}]
    Update return value with E_NOT_OK [/cover] */
    lRetVal = E_NOT_OK;
  }
  else
  #endif
  {
    /* [cover parentID={D7CBEF91-4351-4d61-84A9-B53ABDFD18E7}]
    Get current power state of the ADC hardware units [/cover] */
    lCurrentPwrState = Adc_lGetCurrentPwrState(ADC_SID_GET_CURRENT_POWER_STATE,\
                                                                       lCoreId);
    /* [cover parentID={4179E182-DE9E-4f43-BDFA-35A116A3042C}]
    Is current power state valid ? [/cover] */
    if(lCurrentPwrState != ADC_INVALID_POWER_STATE)
    {
      /* Update pointer with current power state */
      *CurrentPowerState = (Adc_PowerStateType)lCurrentPwrState;

      /* [cover parentID={4154C92F-AB97-4a9f-9323-157EB5D57FD9}]
      Update result as ADC_SERVICE_ACCEPTED [/cover] */
      *Result = ADC_SERVICE_ACCEPTED;

      /* [cover parentID={361AA08A-C515-4765-8422-4DEE4A410EFD}]
      Update return value with E_OK [/cover] */
      lRetVal = E_OK;
    }
    else
    {
      /* [cover parentID={55169F07-0D2B-4ee0-A2FE-F3FC4AD3B6A0}]
      Update result as ADC_HW_FAILURE [/cover] */
      *Result = ADC_HW_FAILURE;

      /* [cover parentID={12BC5C13-5C5F-4742-9757-8355D2E34A3D}]
      Update return value with E_NOT_OK [/cover] */
      lRetVal = E_NOT_OK;
    }
  }
  return(lRetVal);
}
#endif

#if (ADC_STARTUP_CALIB_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={31CBFA99-822B-49c9-9E0F-090F042D833F},
                                 {BA6EFE0D-B9E6-4630-BF56-93FFA7D4CB7F}]      **
**                                                                            **
** Syntax           : Std_ReturnType Adc_TriggerStartupCal                    **
**                    (                                                       **
**                       void                                                 **
**                    )                                                       **
**                                                                            **
** Description      : This API triggers the start-up calibration. The API can **
**                    be invoked from any core, it should be ensured that     **
**                    initialization sequence of all the cores is over before **
**                    invoking the API.                                       **
**                    Note: This API is available only when AdcCalibStatusApi **
**                    is configured as true.                                  **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x31                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK: Startup calibration has been started              **
**                    E_NOT_OK: Development error occured                     **
**                                                                            **
*******************************************************************************/
Std_ReturnType Adc_TriggerStartupCal(void)
{
  Std_ReturnType lRetVal;
  /* [cover parentID={424396B4-E000-4022-AD68-AB6686110565}]
  DET is ON or SAFETY is ON [/cover] */
  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))
  uint8 lDetVal;

  /* Check DET's for the API */
  lDetVal = Adc_lTrigStartupCalDetCheck();

  /* [cover parentID={B63F12A1-94F6-44e1-AC04-2172DD1DBBC4}]
  DET Error Occured  [/cover] */
  if(lDetVal != ADC_E_NO_ERR)
  {
    /* [cover parentID={B1CB619C-B7A0-436f-B630-7870C19D99DE}]
    Update return value as E_NOT_OK [/cover] */
    lRetVal = E_NOT_OK;
  }
  else
  #endif
  {
    /* [cover parentID={2E1C4712-61E4-47f1-BB96-E51A87479E80}]
    Trigger One Conv Enable is ON [/cover] */
    #if (ADC_TRIGGER_ONE_CONV_ENABLE == STD_ON)
    lRetVal = Adc_lTriggerOneConversion();
    /* [cover parentID={EDAA81D4-2548-401f-A25A-BC845AB095C1}]
    Return value is not equal to E_NOT_OK [/cover] */
    if(E_NOT_OK != lRetVal)
    #endif
    {
      /* [cover parentID={784965B1-AFD9-4b98-9F0D-3DA119DA33B8}]
      Trigger the Start-Up Calibration [/cover] */
      Mcal_SetBitAtomic(&MODULE_EVADC.GLOBCFG.U, \
                        (uint8)IFX_EVADC_GLOBCFG_SUCAL_OFF, 1, 1U);
      /* [cover parentID={A6248276-98AE-40b9-876C-B15FC2F0411B}]
      Set the Status of start-up calibration [/cover] */
      Adc_lSetStartupCalStatusAtomic();
      /* [cover parentID={FFE0B71C-9B07-4504-BF0B-FADCE05C5A32}]
      Update return value as E_OK [/cover] */
      lRetVal = E_OK;
    }
  }
  return lRetVal;
}
#endif

#if (ADC_STARTUP_CALIB_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={DC2DD497-4276-40a6-8233-AC6B451543CF},
                                 {BA6EFE0D-B9E6-4630-BF56-93FFA7D4CB7F}]      **
**                                                                            **
** Syntax           : Adc_StartupCalibStatusType Adc_GetStartupCalStatus      **
**                    (                                                       **
**                       void                                                 **
**                    )                                                       **
**                                                                            **
** Description      : This API returns the status of the start-up calibration **
**                    for all the Adc HW groups used by the calling core.     **
**                    Note: This API is available only when AdcCalibStatusApi **
**                    is configured as true.                                  **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x30                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : ADC_STARTUP_CALIB_NOT_TRIGGERED: Startup calibration has**
**                                                     not been triggered     **
**                    ADC_STARTUP_CALIB_ONGOING: Startup calibration is       **
**                                               ongoing                      **
**                    ADC_STARTUP_CALIB_OVER: Startup calibration has         **
**                                            completed                       **
**                                                                            **
*******************************************************************************/
Adc_StartupCalibStatusType Adc_GetStartupCalStatus(void)
{
  uint32 lKernelCount;
  uint32 lCoreId;
  /* [cover parentID={347BB669-DEB3-4e3a-836F-E2B96ACB5085}]
  Update return value as Startup calibration has completed [/cover] */
  Adc_StartupCalibStatusType lRetVal = ADC_STARTUP_CALIB_OVER;
  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))
  uint8 lDetVal;
  #endif

  /* Get the core Id from which it is called */
  lCoreId = Mcal_GetCpuIndex();

  /* [cover parentID={30CC1146-AFDE-4d0e-AF6F-7315D6EB8D71}]
  DET is ON or SAFETY is ON [/cover] */
  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))
  /* Check DET's for the API */
  lDetVal = Adc_lCheckUnInitDet(ADC_SID_GET_STARTUP_CAL_STATUS, lCoreId);
  /* [cover parentID={E862FE3C-A0CB-41ff-AECE-78E7F68C64EA}]
  Un-Init DET Error [/cover] */
  if(lDetVal != ADC_E_NO_ERR)
  {
    lRetVal = ADC_STARTUP_CALIB_NOT_TRIGGERED;
  }
  else
  #endif
  {
    /* [cover parentID={E1CD3C63-3202-48f6-A31F-B35DAC8679D2}]
    Read the Start-up Calibration Status [/cover] */
    /* [cover parentID={43F9DBCA-D6CB-40c1-ABA2-AFCD37EC8AE1}]
    Is Start-up Calibarion Triggered [/cover] */
    if ((uint32)ADC_STARTUP_CAL_STARTED != Adc_lGetStartupCalStatusAtomic())
    {
      /* [cover parentID={D2820549-6B4B-416a-A7FA-792391A49366}]
      Update return value as Startup calibration has not been triggered
      [/cover] */
      lRetVal = ADC_STARTUP_CALIB_NOT_TRIGGERED;
    }
    else
    {
      /* [cover parentID={A2CB8D3E-F11F-45b2-8A57-3A67B280EA9B}]
      Till the last available Kernel [/cover] */
      for(lKernelCount = (uint32)0U; lKernelCount < ADC_MAX_KERNEL_ID; \
          lKernelCount++)
      {
        /* [cover parentID={EAF848B3-108B-4507-AAFE-A6C796BBF7EE}]
        Check if Kernel is Configured [/cover] */
        if(Adc_ConfigPtr->CoreCfgPtr[lCoreId]->HwUnitCfgPtr[lKernelCount] != \
            NULL_PTR)
        {
          /* [cover parentID={ABA92A2E-BE6A-424b-96D9-7CD1AA8C217F}]
          Read Calibration status and Update return value as Startup calibration
          is ongoing if Calibration is active [/cover] */
          if(MODULE_EVADC.G[lKernelCount].ARBCFG.B.CAL == (uint32)ADC_ONE_U)
          {
            /* [cover parentID={ABA92A2E-BE6A-424b-96D9-7CD1AA8C217F}]
            Read Calibration status and Update return value as Startup
            calibration is ongoing if Calibration is active [/cover] */
            lRetVal = ADC_STARTUP_CALIB_ONGOING;
            break;
          }
        }
      }
    }
  }
  return(lRetVal);
}
#endif

/*******************************************************************************
** Traceability: [cover parentID={D88A917E-FBB5-4df1-9569-0A75DE716C14},      **
**                               {BA6EFE0D-B9E6-4630-BF56-93FFA7D4CB7F}]      **
**                                                                            **
** Syntax           : void Adc_RS0EventInterruptHandler                       **
**                    (                                                       **
**                       const uint32 KernelId                                **
**                    )                                                       **
**                                                                            **
** Description      : This API Handles the interrupts from Request source 0   **
**                    for passed ADC KernelId.                                **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x33                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different ADC hardware groups             **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID for which the Interrupt handler    **
**                    is invoked                                              **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : void                                                    **
**                                                                            **
*******************************************************************************/
void Adc_RS0EventInterruptHandler(const uint32 KernelId)
{
  uint32 lCoreId;

  /* Get the core Id from which it is called */
  lCoreId = Mcal_GetCpuIndex();

  /*Since there is no DET check in interrupts, hence validation of
    configuration pointers is done here*/
  /* [cover parentID={51D2D15F-70F4-4bdc-B156-837C032EED36}]
  Is Configuration pointer not equal to NULL Pointer [/cover] */
  if(Adc_ConfigPtr != NULL_PTR)
  {
    /* [cover parentID={69B4FA70-C978-4f87-9366-653DA6B78872}]
    Core configuration pointer is not equal to NULL pointer [/cover] */
    if(Adc_ConfigPtr->CoreCfgPtr[lCoreId] != NULL_PTR)
    {
      /* [cover parentID={1FBD81F3-2767-4eee-89F7-5E8AC0B91879}]
      Is Kernel ID is within the Max Kernel ID? [/cover] */
      if(KernelId < ADC_MAX_KERNEL_ID)
      {
        /* [cover parentID={25E77D6A-2C59-452b-B5BD-A8D7D9DD1E50}]
        Is HW Unit Configuration pointer of Kernel ID for which Interrupt
        Handler is invoked is not equal to NULL pointer? [/cover] */
        if(Adc_ConfigPtr->CoreCfgPtr[lCoreId]->HwUnitCfgPtr[KernelId] != \
           NULL_PTR)
        {
          /* [cover parentID={FDDC420B-E586-423d-9CAC-542566C54F98}]
          Check validity of interrupt via the HW flag [/cover] */
          if(MODULE_EVADC.G[KernelId].SEFLAG.B.SEV0 == (uint32)ADC_ONE_U)
          {
            /* [cover parentID={1F7D71D9-3BAD-490d-AFEB-98537B4CBC58}]
            Clear Request Source event flag [/cover] */
            MODULE_EVADC.G[KernelId].SEFCLR.U = \
                               ((uint32)ADC_ONE_U<<IFX_EVADC_G_SEFCLR_SEV0_OFF);
            /* [cover parentID={8E483D08-83EC-429b-8993-A1B9CC1E8DD0}]
            Call Request Source Event Handler [/cover] */
            Adc_lRSEventHandler(KernelId, ADC_RS0_ID, lCoreId);
          }
          /* [cover parentID={1D00982B-2FC2-4e17-B37D-2DC015B52225}]
          Safety is on [/cover] */
          #if (ADC_SAFETY_ENABLE == STD_ON)
          else
          {
            /* [cover parentID={6E0B3E3B-D47B-4be4-99F6-D9D3AB08584A}]
            Report Interrupt Plausibility Safety Error [/cover] */
            Mcal_ReportSafetyError(ADC_MODULE_ID, ADC_MODULE_INSTANCE,\
                           ADC_SID_RS0_INTRPT_HANDLER, ADC_SE_INT_PLAUSIBILITY);
          }
          #endif
        }
        /* [cover parentID={8DF683D4-1648-4ee4-BA4F-CBB42C4EC050}]
        Safety is ON [/cover] */
        #if (ADC_SAFETY_ENABLE == STD_ON)
        else
        {
          /* [cover parentID={C291E97C-95AE-401e-A06E-3D582CABEEA5}]
          Report Safety Error if Kernel ID is not configured to the core
          [/cover] */
          Mcal_ReportSafetyError(ADC_MODULE_ID, ADC_MODULE_INSTANCE, \
                               ADC_SID_RS0_INTRPT_HANDLER, ADC_SE_PARAM_KERNEL);
        }
        #endif
      }
      /* [cover parentID={8DF683D4-1648-4ee4-BA4F-CBB42C4EC050}]
      Safety is ON [/cover] */
      #if (ADC_SAFETY_ENABLE == STD_ON)
      else
      {
        /* [cover parentID={C291E97C-95AE-401e-A06E-3D582CABEEA5}]
        Report Safety Error for Kernel ID greater than Max available kernels
        [/cover] */
        Mcal_ReportSafetyError(ADC_MODULE_ID, ADC_MODULE_INSTANCE, \
                               ADC_SID_RS0_INTRPT_HANDLER, ADC_SE_PARAM_KERNEL);
      }
      #endif
    }
  }
}

#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
/*******************************************************************************
** Traceability: [cover parentID={0DB01903-CE3D-4400-BA83-2EA818C5767A},      **
**                               {BA6EFE0D-B9E6-4630-BF56-93FFA7D4CB7F}]      **
**                                                                            **
** Syntax           : void Adc_RS1EventInterruptHandler                       **
**                    (                                                       **
**                       const uint32 KernelId                                **
**                    )                                                       **
**                                                                            **
** Description      : This API Handles the interrupts from Request source 1   **
**                    for passed ADC KernelId.                                **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x34                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different ADC hardware groups             **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID for which the Interrupt handler    **
**                    is invoked                                              **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : void                                                    **
**                                                                            **
*******************************************************************************/
void Adc_RS1EventInterruptHandler(const uint32 KernelId)
{
  uint32 lCoreId;

  /* Get the core Id from which it is called */
  lCoreId = Mcal_GetCpuIndex();

  /*Since there is no DET check in interrupts, hence validation of
    configuration pointers is done here*/
  /* [cover parentID={B54E0B00-A339-469a-890E-968AD83659E2}]
  Is Kernel Configuration pointer not equal to NULL Pointer [/cover] */
  if(Adc_ConfigPtr != NULL_PTR)
  {
    /* [cover parentID={E5F2878E-3204-4785-A2C6-D9FD14C24C1E}]
    Core configuration pointer is not equal to NULL pointer [/cover] */
    if(Adc_ConfigPtr->CoreCfgPtr[lCoreId] != NULL_PTR)
    {
      /* [cover parentID={ED8400A7-40ED-49f4-9BF9-1E77417BFEB9}]
      Is Kernel ID is within the Max Kernel ID? [/cover] */
      if(KernelId < ADC_MAX_KERNEL_ID)
      {
        /* [cover parentID={A4544E72-E003-4315-9473-3402177740D8}]
        Is HW Unit Configuration pointer of Kernel ID for which Interrupt
        Handler is invoked is not equal to NULL pointer [/cover] */
        if(Adc_ConfigPtr->CoreCfgPtr[lCoreId]->HwUnitCfgPtr[KernelId] != \
            NULL_PTR)
        {
          /* [cover parentID={C9E36780-7525-48f7-9948-B64947984AF9}]
          Check validity of interrupt via the HW flag  [/cover] */
          if(MODULE_EVADC.G[KernelId].SEFLAG.B.SEV1 == (uint32)ADC_ONE_U)
          {
            /* [cover parentID={9E53C956-0384-440c-9092-7F755EEBF98E}]
            Clear Request Source event flag [/cover] */
            MODULE_EVADC.G[KernelId].SEFCLR.U = \
                               ((uint32)ADC_ONE_U<<IFX_EVADC_G_SEFCLR_SEV1_OFF);
            /* [cover parentID={FFA725C7-478D-49fe-A65E-3820927B47DC}]
            Call Request Source Event Handler [/cover] */
            Adc_lRSEventHandler(KernelId, ADC_RS1_ID, lCoreId);
          }
          /* [cover parentID={1B52D5C4-FB00-483c-9A93-0B030115D7D9}]
          Safety is on [/cover] */
          #if (ADC_SAFETY_ENABLE == STD_ON)
          else
          {
            /* [cover parentID={F6C67629-9920-4273-B33A-1CD4584A8762}]
            Report Interrupt Plausibility Safety Error [/cover] */
            Mcal_ReportSafetyError(ADC_MODULE_ID, ADC_MODULE_INSTANCE,\
                           ADC_SID_RS1_INTRPT_HANDLER, ADC_SE_INT_PLAUSIBILITY);
          }
          #endif
        }
        /* [cover parentID={FE183915-703E-41c5-9032-08F792F7C62A}]
        Safety is ON [/cover] */
        #if (ADC_SAFETY_ENABLE == STD_ON)
        else
        {
          /* [cover parentID={C09390B4-B24C-4e96-ABF6-DBEE05EB3137}]
          Report Safety Error if Kernel ID is not configured to the core
          [/cover] */
          Mcal_ReportSafetyError(ADC_MODULE_ID, ADC_MODULE_INSTANCE, \
                               ADC_SID_RS1_INTRPT_HANDLER, ADC_SE_PARAM_KERNEL);
        }
        #endif
      }
      /* [cover parentID={FE183915-703E-41c5-9032-08F792F7C62A}]
      Safety is ON [/cover] */
      #if (ADC_SAFETY_ENABLE == STD_ON)
      else
      {
        /* [cover parentID={C09390B4-B24C-4e96-ABF6-DBEE05EB3137}]
        Report Safety Error for Kernel ID greater than Max available kernels
        [/cover] */
        Mcal_ReportSafetyError(ADC_MODULE_ID, ADC_MODULE_INSTANCE, \
                               ADC_SID_RS1_INTRPT_HANDLER, ADC_SE_PARAM_KERNEL);
      }
      #endif
    }
  }
}
#endif

#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
/*******************************************************************************
** Traceability: [cover parentID={477E8E2B-2614-4bd1-BAB1-DED74ADFD98E},      **
**                               {BA6EFE0D-B9E6-4630-BF56-93FFA7D4CB7F}]      **
**                                                                            **
** Syntax           : void Adc_RS2EventInterruptHandler                       **
**                    (                                                       **
**                       const uint32 KernelId                                **
**                    )                                                       **
**                                                                            **
** Description      : This API Handles the interrupts from Request source 2   **
**                    for passed ADC KernelId.                                **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x35                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different ADC hardware groups             **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID for which the Interrupt handler    **
**                    is invoked                                              **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : void                                                    **
**                                                                            **
*******************************************************************************/
void Adc_RS2EventInterruptHandler(const uint32 KernelId)
{
  uint32 lCoreId;

  /* Get the core Id from which it is called */
  lCoreId = Mcal_GetCpuIndex();

  /*Since there is no DET check in interrupts, hence validation of
    configuration pointers is done here*/
  /* [cover parentID={46210C60-0838-47e3-B24D-1F9CBD57D654}]
  Is Kernel Configuration pointer not equal to NULL Pointer [/cover] */
  if(Adc_ConfigPtr != NULL_PTR)
  {
    /* [cover parentID={5D3EEA39-4F8F-40be-ADBA-46E20BAC23A5}]
    Core configuration pointer is not equal to NULL pointer [/cover] */
    if(Adc_ConfigPtr->CoreCfgPtr[lCoreId] != NULL_PTR)
    {
      /* [cover parentID={54A82090-AC7F-41b0-9916-7E4F44F49535}]
      Is Kernel ID is within the Max Kernel ID? [/cover] */
      if(KernelId < ADC_MAX_KERNEL_ID)
      {
        /* [cover parentID={BFE2E7BA-EC0C-4c49-84A5-22CA02671F53}]
        Is HW Unit Configuration pointer of Kernel ID for which Interrupt
        Handler is invoked is not equal to NULL pointer [/cover] */
        if(Adc_ConfigPtr->CoreCfgPtr[lCoreId]->HwUnitCfgPtr[KernelId] != \
            NULL_PTR)
        {
          /* [cover parentID={B8402FDD-5EAC-4081-8BE3-67F815DC2245}]
          Check validity of interrupt via the HW flag [/cover] */
          if(MODULE_EVADC.G[KernelId].SEFLAG.B.SEV2 == (uint32)ADC_ONE_U)
          {
            /* [cover parentID={9883A3E2-0595-4b09-A771-14BC7DBF7322}]
            Clear Request Source event flag [/cover] */
            MODULE_EVADC.G[KernelId].SEFCLR.U = \
                               ((uint32)ADC_ONE_U<<IFX_EVADC_G_SEFCLR_SEV2_OFF);
            /* [cover parentID={98919F01-161E-4455-9AB0-5BBD8B443AF6}]
            Call Request Source Event Handler   [/cover] */
            Adc_lRSEventHandler(KernelId, ADC_RS2_ID, lCoreId);
          }
          /* [cover parentID={9BCEE3F1-F168-4872-B215-F89001B9A7BB}]
          Safety is on [/cover] */
          #if (ADC_SAFETY_ENABLE == STD_ON)
          else
          {
            /* [cover parentID={AB869CF4-456B-4e40-A9AD-BE503F7EADA9}]
            Report Interrupt Plausibility Safety Error [/cover] */
            Mcal_ReportSafetyError(ADC_MODULE_ID, ADC_MODULE_INSTANCE,\
                           ADC_SID_RS2_INTRPT_HANDLER, ADC_SE_INT_PLAUSIBILITY);
          }
          #endif
        }
        /* [cover parentID={200114C4-A585-47bf-89AE-50731C4AD29F}]
        Safety is ON [/cover] */
        #if (ADC_SAFETY_ENABLE == STD_ON)
        else
        {
          /* [cover parentID={D7125C94-DE8D-4a47-ABEB-63FA12D68414}]
          Report Safety Error if Kernel ID is not configured to the core
          [/cover] */
          Mcal_ReportSafetyError(ADC_MODULE_ID, ADC_MODULE_INSTANCE, \
                               ADC_SID_RS2_INTRPT_HANDLER, ADC_SE_PARAM_KERNEL);
        }
        #endif
      }
      /* [cover parentID={200114C4-A585-47bf-89AE-50731C4AD29F}]
      Safety is ON [/cover] */
      #if (ADC_SAFETY_ENABLE == STD_ON)
      else
      {
        /* [cover parentID={D7125C94-DE8D-4a47-ABEB-63FA12D68414}]
        Report Safety Error for Kernel ID greater than Max available kernels
        [/cover] */
        Mcal_ReportSafetyError(ADC_MODULE_ID, ADC_MODULE_INSTANCE, \
                               ADC_SID_RS2_INTRPT_HANDLER, ADC_SE_PARAM_KERNEL);
      }
      #endif
    }
  }
}
#endif

#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={590EE9F2-54AC-48b4-B5A7-723C9BE2421B},      **
**                               {BA6EFE0D-B9E6-4630-BF56-93FFA7D4CB7F}]      **
**                                                                            **
** Syntax           : void Adc_ChEventInterruptHandler                        **
**                    (                                                       **
**                       const uint32 KernelId                                **
**                    )                                                       **
**                                                                            **
** Description      : This API Handles the interrupts from ADC Channel Event  **
**                    for passed ADC KernelId.                                **
**                    Note: This API is available only when AdcLimitCheckApi  **
**                    is configured as true.                                  **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x36                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different ADC hardware groups             **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID for which the Interrupt handler    **
**                    is invoked                                              **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : void                                                    **
**                                                                            **
*******************************************************************************/
void Adc_ChEventInterruptHandler(const uint32 KernelId)
{
  const Adc_GlobalDataType *lKernelDataPtr;
  uint32 lChannelMask, lRsCount, lCoreId;
  Adc_ChannelType lLimitChkCh;
  #if (ADC_SAFETY_ENABLE == STD_ON)
  uint8 lChannelRqstRaised = 0U;
  #endif

  /* Get the core Id from which it is called */
  lCoreId = Mcal_GetCpuIndex();

  /*Since there is no DET check in interrupts, hence validation of
    configuration pointers is done here*/
  /* [cover parentID={7A286400-ADB6-4d2e-A7FA-7402E53E9570}]
  Is Kernel Configuration pointer not equal to NULL Pointer [/cover] */
  if(Adc_ConfigPtr != NULL_PTR)
  {
    /* [cover parentID={641A4AB0-81A9-4754-8020-0302A7C5F9E1}]
    Core configuration pointer is not equal to NULL pointer [/cover] */
    if(Adc_ConfigPtr->CoreCfgPtr[lCoreId] != NULL_PTR)
    {
      /* [cover parentID={96D361A9-C101-4274-8668-881CA0906F26}]
      Is Kernel ID is within the Max Kernel ID? [/cover] */
      if(KernelId < ADC_MAX_KERNEL_ID)
      {
        /* [cover parentID={B93EF855-FCF0-4df3-9194-BEDB179E2C67}]
        Is HW Unit Configuration pointer of Kernel ID for which Interrupt
        Handler is invoked is not equal to NULL pointer [/cover] */
        if(Adc_ConfigPtr->CoreCfgPtr[lCoreId]->HwUnitCfgPtr[KernelId] != \
            NULL_PTR)
        {
          lKernelDataPtr = Adc_lGetKernelDataAddress(KernelId, lCoreId);
          /* [cover parentID={0B913515-14E1-4d83-B2B1-B2839921FAFB}]
          Till the last Request Source [/cover] */
          for(lRsCount=(uint32)0U; lRsCount<ADC_REQSRC_USED_COUNT; lRsCount++)
          {
            lLimitChkCh = lKernelDataPtr->RSData[lRsCount].ActiveLimitChkCh;
            /* [cover parentID={4EF4EB4F-5C71-4c14-A66F-CF5D094DD90A}]
            If Limit check channel is less than Max available channel & If
            channel event occured  [/cover] */
            if(lLimitChkCh < (Adc_ChannelType)ADC_SECONDARY_CONV_CHANNEL_COUNT)
            {
              lChannelMask = ((uint32)ADC_ONE_U << lLimitChkCh);
              if((MODULE_EVADC.G[KernelId].CEFLAG.U & lChannelMask) == \
                                                                   lChannelMask)
              {
                /* [cover parentID={9A3F4291-98DB-4c4c-9C1A-052B593BA6C5}]
                Clear the Channel event flag [/cover] */
                MODULE_EVADC.G[KernelId].CEFCLR.U = lChannelMask;
                /* [cover parentID={9CC9BF30-8F11-4a09-B515-7F5288561454}]
                Safety is ON [/cover] */
                #if (ADC_SAFETY_ENABLE == STD_ON)
                /* [cover parentID={08B5AB9F-A99D-45c2-9D75-9280C735A262}]
                Set a flag if request raised from any of the request surce
                [/cover] */
                lChannelRqstRaised = ADC_ONE_U;
                #endif
                /* [cover parentID={56A75003-AC6C-400b-81EF-DB5CF551A863}]
                Call Limit Check Event Handler  [/cover] */
                Adc_lLimitChkEventHandler(KernelId,\
                      lKernelDataPtr->RSData[lRsCount].ActiveGroupId,\
                      lCoreId,(uint8)lRsCount);
              }
            }
          }
          /* [cover parentID={B2D89A79-AE9D-4ae8-AA3B-EFA25060225F}]
          Safety is ON [/cover] */
          #if (ADC_SAFETY_ENABLE == STD_ON)
          /* [cover parentID={68682F0F-D4B7-449d-B86E-BDFB452D3EDE}]
          Channel Event is not raised from any analog channels [/cover] */
          if(lChannelRqstRaised != ADC_ONE_U)
          {
            /* [cover parentID={6382F20A-B24D-473d-AC02-17A871C1F2C4}]
            Report Interrupt Plausibility Safety Error [/cover] */
            Mcal_ReportSafetyError(ADC_MODULE_ID, ADC_MODULE_INSTANCE,\
                            ADC_SID_CH_INTRPT_HANDLER, ADC_SE_INT_PLAUSIBILITY);
          }
          #endif
        }
        /* [cover parentID={E4C4B8D8-816E-43da-934E-7B363034887C}]
        Safety is ON [/cover] */
        #if (ADC_SAFETY_ENABLE == STD_ON)
        else
        {
          /* [cover parentID={FF14982D-B34A-4826-BD3D-520EA3758DF7}]
          Report Safety Error if Kernel ID is not configured to the core
          [/cover] */
          Mcal_ReportSafetyError(ADC_MODULE_ID, ADC_MODULE_INSTANCE, \
                               ADC_SID_CH_INTRPT_HANDLER, ADC_SE_PARAM_KERNEL);
        }
        #endif
      }
      /* [cover parentID={E4C4B8D8-816E-43da-934E-7B363034887C}]
      Safety is ON [/cover] */
      #if (ADC_SAFETY_ENABLE == STD_ON)
      else
      {
        /* [cover parentID={FF14982D-B34A-4826-BD3D-520EA3758DF7}]
        Report Safety Error for Kernel ID greater than Max available kernels
        [/cover] */
        Mcal_ReportSafetyError(ADC_MODULE_ID, ADC_MODULE_INSTANCE,\
                                ADC_SID_CH_INTRPT_HANDLER, ADC_SE_PARAM_KERNEL);
      }
      #endif
    }
  }
}
#endif

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/
/*******************************************************************************
** Traceability: [cover parentID={D9FAB69D-A392-4ab6-A81E-0D2F49CAB118}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint32 Adc_lGetAdcKernel                   **
**                    (                                                       **
**                       const Adc_GroupType GroupId                          **
**                    )                                                       **
**                                                                            **
** Description      : This function derives the Adc kernel number from the    **
**                    Adc channel group number.                               **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : GroupId - Adc Channel Group number                      **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Kernel Number                                           **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Adc_lGetAdcKernel(const Adc_GroupType GroupId)
{
  /* [cover parentID={DB254306-E32E-4a81-984A-BCBB7F214982}]
  Get Kernel number from channel group [/cover] */
  return((uint32)(Mcal_GetBitAtomic((uint32)GroupId, \
                                    ADC_KERNEL_ID_START_POS, \
                                    ADC_KERNEL_ID_NO_OF_BITS)));
}
/*******************************************************************************
** Traceability: [cover parentID={8E262E05-22C4-45d8-8ECD-8DFE45DE5DF9}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE Adc_GroupType Adc_lGetKernelGroupId        **
**                    (                                                       **
**                      const  Adc_GroupType GroupId                          **
**                    )                                                       **
**                                                                            **
** Description      : This function derives the Group Number from the         **
**                    Adc channel group ID.                                   **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : GroupId - Adc Channel Group number                      **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Group Number                                            **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Adc_GroupType Adc_lGetKernelGroupId(const Adc_GroupType GroupId)
{
  /* [cover parentID={89207E57-13A5-4afd-BD2C-1AC59C4F8F79}] Extract Kernel
  specific GroupID from Group [/cover] */
  return((Adc_GroupType)(GroupId & (Adc_GroupType)ADC_GROUP_ID_MASK));
}
/*******************************************************************************
** Traceability: [cover parentID={9B043C7C-9260-4568-8AD8-97A4BCB9331C}]      **
**                                                                            **
** Syntax           :LOCAL_INLINE Adc_GlobalDataType*Adc_lGetKernelDataAddress**
**                    (                                                       **
**                      const uint32 KernelId,                                **
**                      const uint32 CoreId                                   **
**                    )                                                       **
**                                                                            **
** Description      : This function returns the address of the element of the **
**                    array - Adc_KernelData, where kernel specific run-time  **
**                    data stored.                                            **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : address of the element of the Adc_KernelData            **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Adc_GlobalDataType* Adc_lGetKernelDataAddress(\
                                    const uint32 KernelId, const uint32 CoreId)
{
  return(&Adc_kKernelData[CoreId][Adc_kKernelDataIndex[CoreId][KernelId]]);
}

#if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
/*******************************************************************************
** Traceability: [cover parentID={06008D66-95B3-4772-844B-48F1257545DE}]      **
**                                                                            **
** Syntax           :LOCAL_INLINE uint8 Adc_lGetGrpReqSrc                     **
**                    (                                                       **
**                      const uint32 KernelId,                                **
**                      const Adc_GroupType GroupId,                          **
**                      const uint32 CoreId                                   **
**                    )                                                       **
**                                                                            **
** Description      : This function returns the request source on which a     **
**                    group is currently installed.                           **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different ADC hardware groups             **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    GroupId - Group ID                                      **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Request source of the group or ADC_INVALID_RS_ID if the **
**                    group is currently not installed on any RS              **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lGetGrpReqSrc(const uint32 KernelId,
                              const Adc_GroupType GroupId, const uint32 CoreId)
{
  uint8 lReqSrc;
  uint8 lRetVal = ADC_INVALID_RS_ID;
  const Adc_GlobalDataType *lKernelDataPtr;

  /* Get kernel data pointer */
  lKernelDataPtr = Adc_lGetKernelDataAddress(KernelId, CoreId);

  /* Check if requested group is installed on any request source */
  /* [cover parentID={C2F97E86-7C54-4ff2-A731-F12623E0E60A}]
  Till the last available RS or Group ID found [/cover] */
  for (lReqSrc = (uint8)0U; lReqSrc < (uint8)ADC_REQSRC_USED_COUNT; lReqSrc++)
  {
    /* [cover parentID={7BEECD1B-624B-405d-B904-E362A66AEC7F}]
    Group ID is equal to Active Group ID [/cover] */
    if (lKernelDataPtr->RSData[lReqSrc].ActiveGroupId == GroupId)
    {
      /* [cover parentID={C305183E-764C-49c8-9C07-E7EDFC2CFAC7}]
      Return the RS on which the group is running [/cover] */
      lRetVal = lReqSrc;
      break;
    }
  }

  return lRetVal;
}
#endif

/*******************************************************************************
** Traceability: [cover parentID={3A7A0185-43C6-4b05-8284-77AA6BB3829F}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE void Adc_lSetGroupStatusBusyAtomic         **
**                    (                                                       **
**                       Adc_GlobalDataType * const KernelDataPtr             **
**                       const Adc_GroupType GroupId                          **
**                    )                                                       **
** [/cover]                                                                   **
**                                                                            **
** Description      : This function sets the Group Status to ADC_BUSY         **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelDataPtr - Pointer to Adc_KernelData array element **
**                    GroupId - Adc Channel Group number                      **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Adc_lSetGroupStatusBusyAtomic(\
    Adc_GlobalDataType * const KernelDataPtr, const Adc_GroupType GroupId)
{
  /* [cover parentID={5A8C33A6-A2F7-43a3-BD1A-B789B92F1A0D}]
  Set the group status busy flag [/cover] */
  Mcal_SetBitAtomic(&(KernelDataPtr->GrpStatus), (uint8)GroupId, \
                    1, 1U);
  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
     instruction, hence they are not unused.*/
  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
     instruction, hence they are not unused.*/
  /* MISRA2012_RULE_8_13_JUSTIFICATION: Parameter are updated via assembly
     instruction, hence cannot be passed as const.*/
}

/*******************************************************************************
** Traceability: [cover parentID={2582C034-CBD6-47dd-A4A5-BA035DE4ADC2}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE void Adc_lSetGroupResultAtomic             **
**                    (                                                       **
**                       Adc_GlobalDataType * const KernelDataPtr             **
**                       const Adc_GroupType GroupId                          **
**                    )                                                       **
**                                                                            **
** Description      : This function changes the group conversion result status**
**                    to 'results-available'.                                 **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelDataPtr - Pointer to Adc_KernelData array element **
**                    GroupId - Adc Channel Group number                      **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Adc_lSetGroupResultAtomic(\
    Adc_GlobalDataType * const KernelDataPtr, const Adc_GroupType GroupId)
{
  /* [cover parentID={19AEEDE0-29FB-42a0-BABA-B35A5720EC52}]
  Set the group conversion result status flag [/cover] */
  Mcal_SetBitAtomic(&(KernelDataPtr->GrpResultStatus), (uint8)GroupId, \
                    1, 1U);
  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
     instruction, hence they are not unused.*/
  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
     instruction, hence they are not unused.*/
  /* MISRA2012_RULE_8_13_JUSTIFICATION:Parameter are updated via assembly
     instruction, hence cannot be passed as const.*/
}
/*******************************************************************************
** Traceability: [cover parentID={820D4D00-4326-4b14-8DB1-1F17469CE383}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE void Adc_lSetResBuffEndStatusAtomic        **
**                    (                                                       **
**                       Adc_GlobalDataType *const KernelDataPtr              **
**                       const Adc_GroupType GroupId                          **
**                    )                                                       **
**                                                                            **
** Description      : This function changes the group conversion result       **
**                    status to 'buffer full' (stream completed)              **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelDataPtr - Pointer to Adc_KernelData array element **
**                    GroupId - Adc Channel Group number                      **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Adc_lSetResBuffEndStatusAtomic(\
    Adc_GlobalDataType * const KernelDataPtr, const Adc_GroupType GroupId)
{
  /* [cover parentID={7FD4E3FE-2F0C-4531-A92B-180910EC9525}]
  Set the result buffer end status flag [/cover] */
  Mcal_SetBitAtomic(&(KernelDataPtr->GrpBufferEndResultStatus), (uint8)GroupId,\
                    1, 1U);
  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
     instruction, hence they are not unused.*/
  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
   instruction, hence they are not unused.*/
  /* MISRA2012_RULE_8_13_JUSTIFICATION:Parameter are updated via assembly
   instruction, hence cannot be passed as const.*/
}
#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={0820E1A6-1F7A-4253-87FA-090F0AC28936}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE void Adc_lSetGrpNotifAtomic                **
**                    (                                                       **
**                       Adc_GlobalDataType * const KernelDataPtr             **
**                       const Adc_GroupType GroupId                          **
**                    )                                                       **
**                                                                            **
** Description      : This function enables the group notification for        **
**                    the passed group                                        **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelDataPtr - Pointer to Adc_KernelData array element **
**                    GroupId - Adc Channel Group number                      **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Adc_lSetGrpNotifAtomic(\
    Adc_GlobalDataType * const KernelDataPtr, const Adc_GroupType GroupId)
{
  /* [cover parentID={8911CC38-9CA9-4daf-ADF1-AC97C465A4C5}]
  Set group notification flag [/cover] */
  Mcal_SetBitAtomic(&(KernelDataPtr->GrpNotifStatus), (uint8)GroupId, \
                    1, 1U);
  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
   instruction, hence they are not unused.*/
  /* MISRA2012_RULE_8_13_JUSTIFICATION:Parameter are updated via assembly
   instruction, hence cannot be passed as const.*/
}
#endif
#if (ADC_STARTUP_CALIB_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={433512DF-05F4-47a0-843D-CE66924A3A2C}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE void Adc_lSetStartupCalStatusAtomic        **
**                    (                                                       **
**                       void                                                 **
**                    )                                                       **
**                                                                            **
** Description      : This function sets the startup calibration status to    **
**                    STARTED value                                           **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Adc_lSetStartupCalStatusAtomic(void)
{
  /* [cover parentID={EB9D8D9D-C4B3-4261-8FC2-12ACC3AFBB9D}]
  Set the start-up calibration status flag [/cover] */
  Mcal_SetBitAtomic(&Adc_StartupCalStatus, (uint8)0U, 1, \
                    ADC_STARTUP_CAL_STARTED);
}
#endif
/*******************************************************************************
** Traceability: [cover parentID={E3C90EE4-A853-4728-A4D9-805DAE334076}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE void Adc_lClrGroupStatusBusyAtomic         **
**                    (                                                       **
**                       Adc_GlobalDataType * const KernelDataPtr             **
**                       const Adc_GroupType GroupId                          **
**                    )                                                       **
**                                                                            **
** Description      : This function clears the Group Status flag to indicate  **
**                    ADC_IDLE state.                                         **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelDataPtr - Pointer to Adc_KernelData array element **
**                    GroupId - Adc Channel Group number                      **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Adc_lClrGroupStatusBusyAtomic(\
    Adc_GlobalDataType * const KernelDataPtr, const Adc_GroupType GroupId)
{
  /* [cover parentID={5636327F-9D28-481b-B9A0-657A7A98871D}]
  Clears the group status busy flag [/cover] */
  Mcal_SetBitAtomic(&(KernelDataPtr->GrpStatus), (uint8)GroupId, \
                    1, 0U);
  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
   instruction, hence they are not unused.*/
  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
   instruction, hence they are not unused.*/
  /* MISRA2012_RULE_8_13_JUSTIFICATION: Parameter are updated via assembly
   instruction, hence cannot be passed as const.*/
}
/*******************************************************************************
** Traceability: [cover parentID={3FA8282D-21D3-4320-A7BC-2B99C0B0EEA7}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE void Adc_lClrGroupResultAtomic             **
**                    (                                                       **
**                       Adc_GlobalDataType * const KernelDataPtr             **
**                       const Adc_GroupType GroupId                          **
**                    )                                                       **
**                                                                            **
** Description      : This function changes the group conversion result status**
**                    to un-available                                         **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelDataPtr - Pointer to Adc_KernelData array element **
**                    GroupId - Adc Channel Group number                      **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Adc_lClrGroupResultAtomic(\
    Adc_GlobalDataType * const KernelDataPtr, const Adc_GroupType GroupId)
{
  /* [cover parentID={09A8B538-E429-43b6-AF83-CA85ACA8A3CC}]
  Clears group result status flag [/cover] */
  Mcal_SetBitAtomic(&(KernelDataPtr->GrpResultStatus), (uint8)GroupId, \
                    1, 0U);
  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
   instruction, hence they are not unused. */
  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
   instruction, hence they are not unused.*/
  /* MISRA2012_RULE_8_13_JUSTIFICATION:Parameter are updated via assembly
   instruction, hence cannot be passed as const. */
}

/*******************************************************************************
** Traceability: [cover parentID={8D04B305-3A20-4fb7-BDDD-0B0A973B142D}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE void Adc_lClrResBuffEndStatusAtomic        **
**                    (                                                       **
**                       Adc_GlobalDataType * const KernelDataPtr             **
**                       const Adc_GroupType GroupId                          **
**                    )                                                       **
**                                                                            **
** Description      : This function changes the group conversion result buffer**
**                    status to buffer not full.                              **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelDataPtr - Pointer to Adc_KernelData array element **
**                    GroupId - Adc Channel Group number                      **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Adc_lClrResBuffEndStatusAtomic(\
    Adc_GlobalDataType * const KernelDataPtr, const Adc_GroupType GroupId)
{
  /* [cover parentID={E504C68C-C881-4431-B278-D9CC430745E3}]
  Clears result buffer end status flag [/cover] */
  Mcal_SetBitAtomic(&(KernelDataPtr->GrpBufferEndResultStatus), (uint8)GroupId,\
                    1, 0U);
  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
     instruction, hence they are not unused.*/
  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
     instruction, hence they are not unused.*/
  /* MISRA2012_RULE_8_13_JUSTIFICATION:Parameter are updated via assembly
     instruction, hence cannot be passed as const.*/
}

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={F22B1E31-A2AF-456f-A730-66C19C41DE4A}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE void Adc_lClrGrpNotifAtomic                **
**                    (                                                       **
**                       Adc_GlobalDataType * const KernelDataPtr             **
**                       const Adc_GroupType GroupId                          **
**                    )                                                       **
**                                                                            **
** Description      : This function disables the group notification for the   **
**                    passed group.                                           **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelDataPtr - Pointer to Adc_KernelData array element **
**                    GroupId - Adc Channel Group number                      **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Adc_lClrGrpNotifAtomic(\
    Adc_GlobalDataType * const KernelDataPtr, const Adc_GroupType GroupId)
{
  /* [cover parentID={506E8C9D-26BC-4698-B982-B7FFCD4075A5}]
  Clears the group notification flag [/cover] */
  Mcal_SetBitAtomic(&(KernelDataPtr->GrpNotifStatus), (uint8)GroupId, \
                    1, 0U);
  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
   instruction, hence they are not unused.*/
  /* MISRA2012_RULE_2_7_JUSTIFICATION:Parameter are updated via assembly
   instruction, hence they are not unused.*/
  /* MISRA2012_RULE_8_13_JUSTIFICATION: Parameter are updated via assembly
   instruction, hence cannot be passed as const.*/
}
#endif

#if (ADC_STARTUP_CALIB_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={2F40225D-FC09-48b1-B44F-D32ECE1748F5}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE void Adc_lClrStartupCalStatusAtomic        **
**                    (                                                       **
**                       void                                                 **
**                    )                                                       **
**                                                                            **
** Description      : This function clears the startup calibration status to  **
**                    NOT STARTED value                                       **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Adc_lClrStartupCalStatusAtomic(void)
{
  /* [cover parentID={F40FDADA-3C86-432c-88AB-064CC8B50CE9}]
  Clears the startup calibration status flag [/cover] */
  Mcal_SetBitAtomic(&Adc_StartupCalStatus, (uint8)0U, 1, 0U);
}
#endif

/*******************************************************************************
** Traceability: [cover parentID={2D130EB1-AADC-408e-9F4A-DD03EAD1818D}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint32  Adc_lGetGroupStatus                **
**                    (                                                       **
**                       const Adc_GlobalDataType * const KernelDataPtr       **
**                       const Adc_GroupType GroupId                          **
**                    )                                                       **
**                                                                            **
** Description      : This function returns the Adc group status              **
**                    ADC_IDLE/ADC_BUSY.                                      **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelDataPtr - Pointer to Adc_KernelData array element **
**                    GroupId - Adc Channel Group number                      **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : 0U:ADC_IDLE                                             **
**                    1U:ADC_BUSY                                             **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Adc_lGetGroupStatus(\
  const Adc_GlobalDataType * const KernelDataPtr,  const Adc_GroupType GroupId)
{
  /* [cover parentID={2BA52126-B36A-459f-BCF9-1178C2FF9B5B},
  {7CDAEA32-F9C9-424e-968E-07D8700D211F}]  Read Group status flag [/cover] */
  return((uint32)(Mcal_GetBitAtomic((uint32)KernelDataPtr->GrpStatus, \
                                    GroupId, 1U)));
}

/*******************************************************************************
** Traceability: [cover parentID={870294C3-CB35-4754-A309-02A169041B1E}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint32  Adc_lGetGroupResultStatus          **
**                    (                                                       **
**                       const Adc_GlobalDataType * const KernelDataPtr       **
**                       Adc_GroupType GroupId                                **
**                    )                                                       **
**                                                                            **
** Description      : This function returns whether results are available for **
**                     the Group ID                                           **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelDataPtr - Pointer to Adc_KernelData array element **
**                    GroupId - Adc Channel Group number                      **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : 0U:Adc results are not available                        **
**                    1U:Atleast one streaming sample is completed            **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Adc_lGetGroupResultStatus(\
   const Adc_GlobalDataType * const KernelDataPtr,const Adc_GroupType GroupId)
{
  /* [cover parentID={C49CDEDF-92B1-4a4e-BB62-FE775F8D59DC}]
  Read Group result status flag [/cover] */
  return((uint32)(Mcal_GetBitAtomic((uint32)KernelDataPtr->GrpResultStatus, \
                                    GroupId, 1U)));
}
/*******************************************************************************
** Traceability: [cover parentID={4D4DD2DD-2B2C-4f8a-8EBC-D80BDD7E80EC}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint32  Adc_lGetResBuffEndStatus           **
**                    (                                                       **
**                       const Adc_GlobalDataType * const KernelDataPtr       **
**                       const Adc_GroupType GroupId                          **
**                    )                                                       **
**                                                                            **
** Description      : This function returns the Result buffer end status      **
**                   (ADC_STREAM_COMPLETED)                                   **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelDataPtr - Pointer to Adc_KernelData array element **
**                    GroupId - Adc Channel Group number                      **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : 0U:Adc result buffer is not full                        **
**                    1U:Adc result buffer is full                            **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Adc_lGetResBuffEndStatus(\
     const Adc_GlobalDataType *const KernelDataPtr,const Adc_GroupType GroupId)
{
  /* [cover parentID={E484A794-16F7-43de-9B60-0751057209EB}]
  Read the Result buffer end status flag [/cover] */
  return((uint32)(Mcal_GetBitAtomic(\
                    (uint32)KernelDataPtr->GrpBufferEndResultStatus,\
                    GroupId,1U)));
}

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={4BE0E071-1D42-46e1-ADEA-E6743A1D5DDF}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint32  Adc_lGetGroupNotifStatus           **
**                    (                                                       **
**                       const Adc_GlobalDataType * const KernelDataPtr       **
**                       const Adc_GroupType GroupId                          **
**                    )                                                       **
**                                                                            **
** Description      : This function returns the notification enabled status   **
**                   for the Group ID                                         **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelDataPtr - Pointer to Adc_KernelData array element **
**                    GroupId - Adc Channel Group number                      **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : 0U:Adc Groups notification is disabled                  **
**                    1U:Adc Groups notification is enabled                   **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Adc_lGetGroupNotifStatus(\
   const Adc_GlobalDataType * const KernelDataPtr, const Adc_GroupType GroupId)
{
  /* [cover parentID={10BF53A8-D027-4c09-B615-F49D3CAE4241}]
  Read group notification enabled status flag [/cover] */
  return((uint32)(Mcal_GetBitAtomic((uint32)KernelDataPtr->GrpNotifStatus, \
                                    GroupId, 1U)));
}
#endif

#if (ADC_STARTUP_CALIB_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={B75A6131-C11E-4b18-97F9-2A4ED48734B0}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint32 Adc_lGetStartupCalStatusAtomic      **
**                    (                                                       **
**                       void                                                 **
**                    )                                                       **
**                                                                            **
** Description      : This function returns the startup calibration status    **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : 0U:Startup calibration not started                      **
**                    1U:Startup calibration started                          **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Adc_lGetStartupCalStatusAtomic(void)
{
  /* [cover parentID={706AF351-DE5D-42ca-8163-DA5F84BD887D}]
  Read the Start-up calibration status flag [/cover] */
  return ((uint32)Mcal_GetBitAtomic((uint32)Adc_StartupCalStatus, (uint8)0U, \
                                    1U));
}
#endif

#if( (ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
     ((MCAL_AR_VERSION == MCAL_AR_422) && (ADC_DEV_ERROR_DETECT == STD_ON)) )
/*******************************************************************************
** Traceability: [cover parentID={4E86096B-BE3F-46eb-8676-44DED325F428}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint32  Adc_lGetAllGroupStatus             **
**                    (                                                       **
**                      const uint32 CoreId                                   **
**                    )                                                       **
**                                                                            **
** Description      : This function checks the BUSY / IDLE status of all the  **
**                    groups across all the kernels                           **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : 0U:All groups are in ADC_IDLE state                     **
**                    1U:Atleast one group is in ADC_BUSY state               **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Adc_lGetAllGroupStatus(const uint32 CoreId)
{
  const Adc_GlobalDataType *lKernelDataPtr;
  uint32 lKernelCount, lRetVal;
  lRetVal = (uint32)0U;
  /* [cover parentID={FD4BB6AC-BCB2-4b81-A146-7E9E26DE37E4}]
  Till the last available Kernel [/cover] */
  for(lKernelCount=(uint32)0U; lKernelCount<ADC_MAX_KERNEL_ID; lKernelCount++)
  {
    /* [cover parentID={E050FE45-29B3-4d4e-B619-811B519A7CA8}]
    Is Kernel Config pointer not equal to NULL pointer [/cover] */
    if(Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[lKernelCount] != \
        NULL_PTR)
    {
      lKernelDataPtr = Adc_lGetKernelDataAddress(lKernelCount, CoreId);
      /* [cover parentID={246E93EF-FBC9-4bf3-9F30-575CB5F8A35F}]
      Check if any group is busy, then return a busy state  [/cover] */
      if( (lKernelDataPtr->GrpStatus) != (uint32)0U )
      {
        lRetVal = (uint32)ADC_ONE_U;
        break;
      }
    }
  }
  return(lRetVal);
}
#endif

#if ((ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) ||\
     (ADC_SYNC_CONV_ENABLE == STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={BA588035-CF4B-4356-BB68-49EB32920F22}]      **
**                                                                            **
** Syntax           : static void  Adc_lSetRunningChAndResReg                 **
**                    (                                                       **
**                      const uint32 KernelId,                                **
**                      const Adc_GroupCfgType * const GrpCfgPtr,             **
**                      const uint32 CoreId                                   **
**                    )                                                       **
**                                                                            **
** Description      : This function sets the running channels and result      **
**                    registers for a kernel and, if the kernel is            **
**                    synchronization master, also for all slave kernels of   **
**                    the synchronization group                               **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    GrpCfgPtr - Pointer to the group configuration          **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Adc_lSetRunningChAndResReg(const uint32 KernelId,\
                                      const Adc_GroupCfgType * const GrpCfgPtr,\
                                      const uint32 CoreId)
{
  Adc_GlobalDataType *lKernelDataPtr;

  lKernelDataPtr = Adc_lGetKernelDataAddress(KernelId, CoreId);

  /* [cover parentID={25C2A78C-30D8-4593-851F-6290D421D8C0}]
  Set flags for used channels and result registers for Master kernel [/cover] */
  lKernelDataPtr->AllRunningChannels |= GrpCfgPtr->ChannelMask;
  lKernelDataPtr->AllRunningResReg |= GrpCfgPtr->ResultRegMask;

  /* [cover parentID={A2C09F43-4C56-4eb0-90F6-F649D5DFC351}]
  Sync Conversion is ON [/cover] */
  #if (ADC_SYNC_CONV_ENABLE == STD_ON)
  /* [cover parentID={84F10512-2928-4b1d-800E-EA01DDEDBCD8}]
  Channel of group configured for Sync conversion [/cover] */
  if (GrpCfgPtr->SyncChannelMask != (uint16)0U)
  {
    const Adc_HwUnitCfgType * lHwUnitCfgPtr;
    uint8 lKernelCount, lSlaveKernel;

    /* Get the base address of the kernel configuration */
    lHwUnitCfgPtr = Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[KernelId];

    /* [cover parentID={F7AAA234-49AB-44d4-BBDD-192F441B9E13}]
    Till the last available Kernel [/cover] */
    for (lKernelCount = (uint8)0U;
         lKernelCount < (uint8)(ADC_KERNELS_PER_SYNGRP - 1U); lKernelCount++)
    {
      lSlaveKernel = lHwUnitCfgPtr->SlaveKernels[lKernelCount];
      /* [cover parentID={2A2585C8-A0E1-4f8c-9A3B-1BE267AAB3E8}]
      Valid Slave Kernel [/cover] */
      if (lSlaveKernel != ADC_INVALID_KERNEL_ID)
      {
        lKernelDataPtr = Adc_lGetKernelDataAddress(lSlaveKernel, CoreId);
        /* [cover parentID={ADD974F8-0C2C-46bb-B975-4ABCBB1CCC2C}]
        Set all running Channels & running Result register for slave kernels
        [/cover] */
        lKernelDataPtr->AllRunningChannels |= GrpCfgPtr->SyncChannelMask;
        lKernelDataPtr->AllRunningResReg |= GrpCfgPtr->SyncResRegMask;
      }
    }
  }
  #endif
}
#endif

#if ((ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) ||\
     (ADC_SYNC_CONV_ENABLE == STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={4AD66CCC-980F-452b-951E-B873705DF1A4}]      **
**                                                                            **
** Syntax           : static void  Adc_lClrRunningChAndResReg                 **
**                    (                                                       **
**                      const uint32 KernelId,                                **
**                      const Adc_GroupCfgType * const GrpCfgPtr,             **
**                      const uint32 CoreId                                   **
**                    )                                                       **
**                                                                            **
** Description      : This function clears the running channels and result    **
**                    registers for a kernel and, if the kernel is            **
**                    synchronization master, also for all slave kernels of   **
**                    the synchronization group                               **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    GrpCfgPtr - Pointer to the group configuration          **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Adc_lClrRunningChAndResReg(const uint32 KernelId,\
                                    const Adc_GroupCfgType * const GrpCfgPtr,\
                                    const uint32 CoreId)
{
  Adc_GlobalDataType *lKernelDataPtr;

  lKernelDataPtr = Adc_lGetKernelDataAddress(KernelId, CoreId);

  /* [cover parentID={46DDFDAA-2EA8-4b97-AF0A-7F3723691B61}]
  Clear flags for used channels and result registers for Master Kernel[/cover]*/
  lKernelDataPtr->AllRunningChannels &= \
    (uint16)((~(GrpCfgPtr->ChannelMask))& ADC_CHANNEL_RESULT_CLR_MASK);
  lKernelDataPtr->AllRunningResReg &= \
    (uint16)((~(GrpCfgPtr->ResultRegMask)) & ADC_CHANNEL_RESULT_CLR_MASK);

  /* [cover parentID={D00F1051-9EA9-438b-AA46-BC6656041381}]
  Sync Conversion is ON [/cover] */
  #if (ADC_SYNC_CONV_ENABLE == STD_ON)
  /* [cover parentID={8A0532F1-B8E2-4859-AD95-2419F4709850}]
  Any channel configured for Sync conversion [/cover] */
  if (GrpCfgPtr->SyncChannelMask != (uint16)0U)
  {
    const Adc_HwUnitCfgType * lHwUnitCfgPtr;
    uint8 lKernelCount, lSlaveKernel;

    /* Get the base address of the kernel configuration */
    lHwUnitCfgPtr = Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[KernelId];

    /* [cover parentID={DE3FB344-AC36-4f7f-B75E-F725406EBB12}]
    Till the last available Kernel [/cover] */
    for (lKernelCount = (uint8)0U;
         lKernelCount < (uint8)(ADC_KERNELS_PER_SYNGRP - 1U); lKernelCount++)
    {
      lSlaveKernel = lHwUnitCfgPtr->SlaveKernels[lKernelCount];
      /* [cover parentID={490049C6-4CA9-4e9a-8E03-89A8C4C6B948}]
      Valid Slave Kernel [/cover] */
      if (lSlaveKernel != ADC_INVALID_KERNEL_ID)
      {
        lKernelDataPtr = Adc_lGetKernelDataAddress(lSlaveKernel, CoreId);

        /* [cover parentID={5AC3CD7F-128D-4c5c-A1EB-30321ACA2C57}]
        Clear all running Channels & running Result register for slave kernels
        [/cover] */
        lKernelDataPtr->AllRunningChannels &= \
          (uint16)((~GrpCfgPtr->SyncChannelMask) & ADC_CHANNEL_RESULT_CLR_MASK);
        lKernelDataPtr->AllRunningResReg &= \
          (uint16)((~GrpCfgPtr->SyncResRegMask) & ADC_CHANNEL_RESULT_CLR_MASK);
      }
    }
  }
  #endif
}
#endif

/*******************************************************************************
** Traceability: [cover parentID={529A8B95-316F-4ee4-935D-F60454F83ADE}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE void Adc_lInit                             **
**                    (                                                       **
**                       const uint32 CoreId                                  **
**                    )                                                       **
**                                                                            **
** Description      : This function resets the global and kernel specific SFRs**
**                    to reset values and then initializes them as per        **
**                    configuration.                                          **
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
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Adc_lInit(const uint32 CoreId)
{
  uint32 lKernelCount;
  /***** Start of DEINIT Process *****/
  /* [cover parentID={CCD3A440-B4AA-4712-9CE3-10E6462412B0}]
  Till the last available Kernel [/cover] */
  for(lKernelCount=(uint32)0U; lKernelCount<ADC_MAX_KERNEL_ID; lKernelCount++)
  {
    /* [cover parentID={8E126E2C-6B38-43d7-8799-D18A508584E4}]
    Check if Kernel is Configured [/cover] */
    if(Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[lKernelCount] != \
        NULL_PTR)
    {
      /* [cover parentID={E1A553C1-FDC5-46dc-8926-A5416CEC4047}]
      De-Initialize the Kernels [/cover] */
      Adc_lKernelDeInit(Adc_ConfigPtr->CoreCfgPtr[CoreId]-> \
                        HwUnitCfgPtr[lKernelCount], lKernelCount);
    }
  }
  /* [cover parentID={E848EEC7-1586-453a-9096-04780F02DD20}]
  Is CoreId is equal to Master CoreId
  [/cover] */
  if (MCAL_MASTER_COREID == CoreId)
  {
    Adc_lResetGlobalSfr();
    /***** End of DEINIT Process *****/
    /***** Start of INIT Process *****/
    /* [cover parentID={F6D426A3-719A-42f0-BA69-4CE486AF02C9}]
    Configure the Global Register [/cover] */
    MODULE_EVADC.GLOBCFG.U = ( (Adc_ConfigPtr->GlobalCfgPtr->GlobalCfg)|\
                               (uint32)ADC_GLOBCFG_WRITE_PROTECT_MSK);
    MODULE_EVADC.GLOB.ICLASS[0U].U = \
                             Adc_ConfigPtr->GlobalCfgPtr->GlobInputClass0Cfg;
    MODULE_EVADC.GLOB.ICLASS[1U].U = \
                             Adc_ConfigPtr->GlobalCfgPtr->GlobInputClass1Cfg;

    /* Configure Global EMUX Interface Register */
    MODULE_EVADC.EMUXSEL.U = \
                     Adc_ConfigPtr->GlobalCfgPtr->GlobEmuxGrpInterfaceCfg;

    /* [cover parentID={2260EB2A-A128-4ac0-8526-889FDE51E2F5}]
    Adc Calibration Status API is ON [/cover] */
    #if (ADC_STARTUP_CALIB_API == STD_ON)
    /* MISRA2012_RULE_2_2_JUSTIFICATION: Tricore Atomic instructions are used
    to update global variables in this function call, which is not detected
    by MISRA. Hence, this function call is not a dead code*/
    /* [cover parentID={39DC007C-582A-4c82-A709-EB21C7C46301}]
    Clear Start-up Calibration status [/cover] */
    Adc_lClrStartupCalStatusAtomic();
    #endif
  }

  /* [cover parentID={24F66B64-3DC4-4acc-9235-185575EB8AFB}]
  Till the last available kernel [/cover] */
  for(lKernelCount=(uint32)0U; lKernelCount<ADC_MAX_KERNEL_ID; lKernelCount++)
  {
    /* [cover parentID={E5D7F0EF-55DA-4e97-B66C-E86A63DD97DC}]
    Check if Kernel is Configured for current core [/cover] */
    if(Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[lKernelCount] != \
        NULL_PTR)
    {
      /* [cover parentID={FD1A7B89-ED6C-4197-86D6-AA25A6EDEB53}]
      Initialize the Kernels [/cover] */
      Adc_lKernelInit(Adc_ConfigPtr->CoreCfgPtr[CoreId]-> \
                      HwUnitCfgPtr[lKernelCount], lKernelCount);
    }
  }

  /* [cover parentID={25CC5098-87D2-4d58-91D4-DDEE31BE68E3}]
  Loop till the last kernel ID,missing or un-configured kernels will be
  NULL PTR in the config set [/cover] */
  for(lKernelCount=(uint32)0U; lKernelCount<ADC_MAX_KERNEL_ID; lKernelCount++)
  {
    /* [cover parentID={5F22ED4F-3113-4487-8848-FCFA8C7735F8}]
    Check if Kernel is Configured for current core [/cover] */
    if(Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[lKernelCount] != \
        NULL_PTR)
    {
      /* Converter is put to always ON mode via the ANONC bit,
         after all registers are configured */
      /* Converters need to be switched ON here,
         because startup calibration requires all converters to be ON */
      /* MISRA2012_RULE_10_3_JUSTIFICATION: The bitfied of SFR are programed
      with an unsigned long value. Since, bitfields are of different type
      than unsigned long MISRA populates this warning. However the write is
      performed only to the intended bits by applying proper masks*/
      /* [cover parentID={A1377B25-6229-4fe3-A294-675D0B4F3235}]
      Switch on kernels to full power as generated in configuration structure
      [/cover] */
      MODULE_EVADC.G[lKernelCount].ARBCFG.B.ANONC = (Adc_ConfigPtr->\
                   CoreCfgPtr[CoreId]->HwUnitCfgPtr[lKernelCount]->\
                   HwCfgPtr->GrpArbitCfg & (uint32)ADC_TARGET_POWER_STATE_MASK);
      /* Ensure register is written and converter is switched ON */
      DSYNC();
    }
  }
  Adc_lResetCoreGlobalVars(CoreId);
  /***** End of INIT Process *****/
}

#if (ADC_INIT_CHECK_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={4E5181CA-A240-4e90-8290-A1652275DEE7}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE Std_ReturnType Adc_lInitCheck              **
**                    (                                                       **
**                       const uint32 CoreId                                  **
**                    )                                                       **
**                                                                            **
** Description      : This function checks the value of initialized global    **
**                    and kernel specific SFRs with configured value          **
**                                                                            **
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
** Return value     : E_OK: Initialization verification passed                **
**                    E_NOT_OK: Initialization verification failed            **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Adc_lInitCheck(const uint32 CoreId)
{
  Std_ReturnType lErrVal = E_OK;
  uint32 lKernelCount;
  uint32 lCompareFlag = 0xFFFFFFFFU;

  /* [cover parentID={DE7D23C9-0CAF-450b-A903-58D13BCBD325}]
  Core Id is equal to Master Core Id [/cover] */
  if (MCAL_MASTER_COREID == CoreId)
  {
    /* [cover parentID={266762F7-8867-4bc6-8F9A-2A22B96824C3}]
    Global SFR Check [/cover] */
    lCompareFlag = Adc_lCheckGlobalSfr(lCompareFlag);

    /* [cover parentID={8EFDD2E5-647A-4719-8FDC-A9D21AB1B9DC}]
    Startup Calibration API is ON [/cover] */
    #if (ADC_STARTUP_CALIB_API == STD_ON)
    uint32 lSfrVal, lCfgVal;
    /* [cover parentID={D96B87E4-CEA3-446a-8889-D95BD03DE49E}]
    Compare Startup calibration status with reset value & Update flag as
    per result [/cover] */
    lSfrVal = (uint32)(Adc_StartupCalStatus);
    lCfgVal = (uint32)0U;
    lCompareFlag &= ~(lSfrVal ^ lCfgVal);
    #endif
  }

  /* [cover parentID={0DCB5978-7E12-4fd2-9266-7A606FE95BFA}]
  Loop till the last kernel ID, missing or un-configured kernels will be
  NULL PTR in the config set [/cover] */
  for(lKernelCount=(uint32)0U; lKernelCount < ADC_MAX_KERNEL_ID; lKernelCount++)
  {
    /* [cover parentID={A7DE9942-63F5-4408-9710-D35A75C40E8D}]
    Check if Kernel is Configured for current core [/cover] */
    if(Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[lKernelCount]!=NULL_PTR)
    {
      /* [cover parentID={55F2AD10-1699-4573-A3AE-1A08EFEA21C4}]
      Kernel Sfr check [/cover] */
      lCompareFlag = Adc_lCheckKernelSfr(Adc_ConfigPtr->CoreCfgPtr[CoreId]-> \
                        HwUnitCfgPtr[lKernelCount], lKernelCount, lCompareFlag);

      /* [cover parentID={72ECE23F-AEF3-4693-A9E7-59272501116D}]
      HW Trigger API is ON [/cover] */
      #if (ADC_HW_TRIGGER_API == STD_ON)
      /* [cover parentID={6E53EEF0-8C59-453b-B851-D8B4DF50D720}]
      GTM is available [/cover] */
      #if (ADC_GTM_AVAILABLE == STD_ON)
      /* [cover parentID={ED7A26D7-CB35-4558-8054-172DCA588D97}]
      GTM Sfrcheck [/cover] */
      lCompareFlag = Adc_lCheckGtmSfr(Adc_ConfigPtr->CoreCfgPtr[CoreId]-> \
                                      HwUnitCfgPtr[lKernelCount], lCompareFlag);
      #endif
      /* [cover parentID={EFB9B393-7A33-4ed5-983A-9A9DADF7B10A}]
      ERU Sfr Check  [/cover] */
      lCompareFlag = Adc_lCheckEruSfr(Adc_ConfigPtr->CoreCfgPtr[CoreId]-> \
                                      HwUnitCfgPtr[lKernelCount], lCompareFlag);
      #endif

    }
  }
  /* [cover parentID={0EBD4963-F18F-4420-8002-5613E64B112F}]
  Verify reset values of global variables [/cover] */
  lCompareFlag = Adc_lCheckGlobalCoreVars(CoreId, lCompareFlag);

  /* [cover parentID={F0DEB2CE-09D4-4800-9B7A-62074DF9B3D7}] 
  Check if any bit is not as per configured value [/cover] */
  if (lCompareFlag != 0xFFFFFFFFU)
  {
    /* Update error value as E_NOT_OK */
    lErrVal = E_NOT_OK;
  }
  return(lErrVal);
}
#endif

#if (ADC_INIT_CHECK_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={3972B576-1F0F-4f92-858E-D1825A3530B5}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint32 Adc_lCheckGlobalSfr                 **
**                    (                                                       **
**                       const uint32 CompareFlag                            **
**                    )                                                       **
**                                                                            **
** Description      : This function checks the reset value of global SFRs     **
**                    with configured value                                   **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : CompareFlag - Flag to compare with configured SFRs or   **
**                    Variables                                               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Compare flag value - all bits as 1 indicates a pass case**
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Adc_lCheckGlobalSfr(const uint32 CompareFlag)
{
  uint32 lSfrVal, lCfgVal;
  uint32 lCompareFlag = CompareFlag;
  const Ifx_EVADC_GLOB *lEvadcGlobalSfr;
  lEvadcGlobalSfr = &(MODULE_EVADC.GLOB);

  /* Compare global config register with configuration value & Update flag
     as per result */
  lSfrVal = MODULE_EVADC.GLOBCFG.U;
  lCfgVal = (Adc_ConfigPtr->GlobalCfgPtr->GlobalCfg);
  lCompareFlag &= ~(lSfrVal ^ lCfgVal);

  /* Compare External Multiplexer Interface Select Register with config values
     & Update flag based on result*/
  lSfrVal = (MODULE_EVADC.EMUXSEL.U);
  lCfgVal = (Adc_ConfigPtr->GlobalCfgPtr->GlobEmuxGrpInterfaceCfg);
  lCompareFlag &= ~(lSfrVal ^ lCfgVal);

  /* Compare global input class0 register with configuration value &
  Update flag as per result */
  lSfrVal = MODULE_EVADC.GLOB.ICLASS[0U].U;
  lCfgVal = (Adc_ConfigPtr->GlobalCfgPtr->GlobInputClass0Cfg);
  lCompareFlag &= ~(lSfrVal ^ lCfgVal);

  /* Compare global input class1 register with configuration value &
     Update flag as per result */
  lSfrVal = MODULE_EVADC.GLOB.ICLASS[1U].U;
  lCfgVal = (Adc_ConfigPtr->GlobalCfgPtr->GlobInputClass1Cfg);
  lCompareFlag &= ~(lSfrVal ^ lCfgVal);

  /* Compare boundary select register with config value & Update flag
     based on result*/
  lSfrVal = (lEvadcGlobalSfr->BOUND.U);
  lCfgVal = (uint32)0U;
  lCompareFlag &= ~(lSfrVal ^ lCfgVal);

  /* Compare event flag register with config values & Update flag
     based on result*/
  lSfrVal = (lEvadcGlobalSfr->EFLAG.U);
  lCfgVal = (uint32)0U;
  lCompareFlag &= ~(lSfrVal ^ lCfgVal);

  /* Compare event node pointer register with config values & Update flag
     based on result*/
  lSfrVal = (lEvadcGlobalSfr->EVNP.U);
  lCfgVal = (uint32)0U;
  lCompareFlag &= ~(lSfrVal ^ lCfgVal);

  /* Compare Test function register with config values & Update flag
     based on result*/
  lSfrVal = (lEvadcGlobalSfr->TF.U);
  lCfgVal = (uint32)0U;
  lCompareFlag &= ~(lSfrVal ^ lCfgVal);

  /* Compare Test Enable register with config values & Update flag
     based on result*/
  lSfrVal = (lEvadcGlobalSfr->TE.U);
  lCfgVal = (uint32)0U;
  lCompareFlag &= ~(lSfrVal ^ lCfgVal);

  /* Compare Result control register with config values & Update flag
     based on result*/
  lSfrVal = (lEvadcGlobalSfr->RCR.U);
  lCfgVal = (uint32)0U;
  lCompareFlag &= ~(lSfrVal ^ lCfgVal);

  /* Compare group result register with config values & Update flag
     based on result*/
  lSfrVal = (lEvadcGlobalSfr->RES.U);
  lSfrVal = lSfrVal &\
            ((uint32)IFX_EVADC_GLOB_RES_VF_MSK << IFX_EVADC_GLOB_RES_VF_OFF);
  lCfgVal = (uint32)0U;
  lCompareFlag &= ~(lSfrVal ^ lCfgVal);

  return(lCompareFlag);
}
#endif

/*******************************************************************************
** Traceability: [cover parentID={522687F7-22BF-4886-BA40-D2D3B6D56537}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE void Adc_lResetGlobalSfr                   **
**                    (                                                       **
**                       void                                                 **
**                    )                                                       **
**                                                                            **
** Description      : This function resets the global SFRs of EVADC           **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different CPU core                        **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Adc_lResetGlobalSfr(void)
{
  Ifx_EVADC_GLOB *lEvadcGlobalSfr;
  lEvadcGlobalSfr = &(MODULE_EVADC.GLOB);
  /* Reset Global SFRs to default values */
  lEvadcGlobalSfr->ICLASS[0U].U = (uint32)0U;
  lEvadcGlobalSfr->ICLASS[1U].U = (uint32)0U;
  lEvadcGlobalSfr->BOUND.U      = (uint32)0U;
  lEvadcGlobalSfr->RCR.U        = (uint32)0U;
  lEvadcGlobalSfr->RES.U        = ((uint32)ADC_ONE_U << \
                                   IFX_EVADC_GLOB_RESD_VF_OFF);
  lEvadcGlobalSfr->EFLAG.U      = ((uint32)ADC_ONE_U << \
                                   IFX_EVADC_GLOB_EFLAG_REVGLBCLR_OFF);
  lEvadcGlobalSfr->EVNP.U       = (uint32)0U;
  lEvadcGlobalSfr->TE.U         = (uint32)0U;
  lEvadcGlobalSfr->TF.U         = ADC_GLOBTF_WRITE_PROTECT_MSK;
  MODULE_EVADC.EMUXSEL.U        = (uint32)0U;
  MODULE_EVADC.GLOBCFG.U        = (uint32)ADC_GLOBCFG_WRITE_PROTECT_MSK;
}

/*******************************************************************************
** Traceability: [cover parentID={3E867D04-186C-4c82-B2C0-8E41432B521C}]      **
**                                                                            **
** Syntax           : static void Adc_lResetCoreGlobalVars                    **
**                    (                                                       **
**                       const uint32 CoreId                                  **
**                    )                                                       **
**                                                                            **
** Description      : This function resets the global variables of ADC driver **
**                    for the currently executing CPU core                    **
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
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Adc_lResetCoreGlobalVars(const uint32 CoreId)
{
  Adc_GlobalDataType *lKernelDataPtr;
  uint8 lLoopCount, lRsCount;
  /* Loop for all the indices of the array Adc_KernelData */

  /* [cover parentID={1B11016D-9F49-4984-BB13-7467B1512E8E}]
  Till the last available Kernel [/cover] */
  for(lLoopCount = (uint8)0U; lLoopCount < Adc_kKernelUsedCount[CoreId]; \
      lLoopCount++)
  {
    lKernelDataPtr = &Adc_kKernelData[CoreId][lLoopCount];

    /* [cover parentID={EDE394E7-65BE-48d7-A462-FE1BACEE49CF}]
    DMA Mode Result Handling is OFF [/cover] */
    #if(ADC_RESULT_HANDLING_IMPLEMENTATION != ADC_DMA_MODE_RESULT_HANDLING)
    /* When ADC_RESULT_HANDLING_IMPLEMENTATION is ADC_DMA_MODE_RESULT_HANDLING,
       then ADC_ENABLE_QUEUING will always be STD_OFF.
       Hence, this loop is not required when ADC_RESULT_HANDLING_IMPLEMENTATION
       is ADC_DMA_MODE_RESULT_HANDLING  */
    uint8 lGroupCount;
    for(lGroupCount = (uint8)0U; lGroupCount < ADC_MAX_GROUPS; lGroupCount++)
    {
      /* [cover parentID={F594617E-EB48-40c6-A8D0-5CE67A9A8D89}]
      Reset the Group variables to Default values [/cover] */
      lKernelDataPtr->GrpResBuffer[lGroupCount] = (Adc_ValueGroupType *)0U;
      lKernelDataPtr->NumofValidConRes[lGroupCount] = \
          (Adc_StreamNumSampleType)0U;

      /* [cover parentID={CC1B181E-8C5F-4770-99E5-1A6298AA0335}]
      Hw Priority is ON or Queue Mode is ON [/cover] */
      #if((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW) ||\
          (ADC_ENABLE_QUEUING == STD_ON))
      /* Intialize queue elements with invalid group ID */
      for(lRsCount = (uint8)0U; lRsCount < ADC_REQSRC_USED_COUNT; lRsCount++)
      {
        /* [cover parentID={AAD55E9E-ECC2-430f-8E92-9F52DA531645}]
        Intialize the Queue elements with Invalid group ID [/cover] */
        lKernelDataPtr->RSData[lRsCount].QueueOfSwGroup[lGroupCount].\
        PreviousGroup = ADC_INVALID_GROUP_ID;
        lKernelDataPtr->RSData[lRsCount].QueueOfSwGroup[lGroupCount].NextGroup=\
                                                        ADC_INVALID_GROUP_ID;
      }
      /* [cover parentID={BA01C756-FB09-4097-817F-69B6ADF7C5B6}]
      HW-SW Priority is ON [/cover] */
      #elif(ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
      /* [cover parentID={0A8C1914-2D9B-47b8-8CBC-ED7A07685DC1}]
      Reset Queue Of Sw Group with Invalid Group ID [/cover] */
      lKernelDataPtr->QueueOfSwGroup[lGroupCount].PreviousGroup =\
                                              ADC_INVALID_GROUP_ID;
      lKernelDataPtr->QueueOfSwGroup[lGroupCount].NextGroup =\
                                              ADC_INVALID_GROUP_ID;
      #endif
    }
    #endif

    /* [cover parentID={43DFC2F5-BF43-4333-A8C9-9D2D03E5FBE7}]
    Till the last available Request Source [/cover] */
    for(lRsCount = (uint8)0U; lRsCount < ADC_REQSRC_USED_COUNT; lRsCount++)
    {
      lKernelDataPtr->RSData[lRsCount].ActiveGroupId = ADC_INVALID_GROUP_ID;
      lKernelDataPtr->RSData[lRsCount].ActiveLimitChkCh = \
                                                      ADC_INVALID_CHANNEL_ID;
      lKernelDataPtr->RSData[lRsCount].IsrNoServiceFlag = (uint8)ADC_ONE_U;
      /* [cover parentID={CFE2BDA7-765A-4ae9-9C0B-E311DB674FB0}]
      Hw Priority is ON or Queue Mode is ON [/cover] */
      #if((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW) ||\
          (ADC_ENABLE_QUEUING == STD_ON))
      /* [cover parentID={27AD6803-BC77-4ab4-B4A2-8085DD397184}]
      Intialize queue elements with Invalid group ID [/cover] */
      lKernelDataPtr->RSData[lRsCount].PopGroupId = ADC_INVALID_GROUP_ID;
      lKernelDataPtr->RSData[lRsCount].PushGroupId = ADC_INVALID_GROUP_ID;
      #endif
    }

    lKernelDataPtr->GrpStatus = (uint32)0U;
    lKernelDataPtr->GrpResultStatus = (uint32)0U;
    lKernelDataPtr->GrpBufferEndResultStatus = (uint32)0U;
    lKernelDataPtr->GrpNotifStatus = (uint32)0U;
    lKernelDataPtr->AllRunningChannels = (uint16)0U;
    lKernelDataPtr->AllRunningResReg = (uint16)0U;
    #if(ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
    lKernelDataPtr->PopGroupId = ADC_INVALID_GROUP_ID;
    lKernelDataPtr->PushGroupId = ADC_INVALID_GROUP_ID;
    #endif

    /* [cover parentID={20A21461-40FA-41d8-B002-60EB18D18AC5}]
    Priority mode is ON [/cover] */
    #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
    /* [cover parentID={DF905651-5CAA-42e5-B6EA-C189D0DAB625}]
    Limit check is ON [/cover] */
    #if (ADC_ENABLE_LIMIT_CHECK==STD_ON)
    /* [cover parentID={FD9F85E4-BFAF-4af2-B721-715FEFD4683D}]
    Reset limit check active status flag [/cover] */
    lKernelDataPtr->LimitChkActiveFlag = (uint8)0U;
    #endif
    /* [cover parentID={6A40180B-D061-4b5b-B55C-DF6BE619E43D}]
    Reset alias active status flag [/cover] */
    lKernelDataPtr->AliasActiveFlag = (uint8)0U;
    #endif

    /* [cover parentID={08D32820-40AE-4f1c-8C9D-BBEEDB188F54}]
    Low Power State Support is on [/cover] */
    #if(ADC_LOW_POWER_STATE_SUPPORT == STD_ON)
    /* [cover parentID={696F4B82-DE3C-4428-B8E0-AB995E5D5BCD}]
    Reset Low power state support variable [/cover] */
    Mcal_SetBitAtomic(&Adc_PowerStateTransitionRequestBit, \
                      (uint8)(CoreId * ADC_BITS_PER_POWER_STATE),
                      ADC_BITS_PER_POWER_STATE, 0U);
    #endif

    #if(ADC_EMUX_ENABLE == STD_ON)
    /* Reset Emux Conversion Active Flag */
    lKernelDataPtr->EmuxConversionActiveFlag = ADC_EMUX_IDLE;
    #endif
  }
}

#if (ADC_INIT_CHECK_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={0842D2A4-27DD-469a-A676-FDED00356089}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint32 Adc_lCheckGlobalCoreVars            **
**                    (                                                       **
**                       const uint32 CoreId,                                 **
**                       const uint32 CompareFlag                             **
**                    )                                                       **
**                                                                            **
** Description      : This function checks the reset value of global variable **
**                    with config value for the currently executing CPU core  **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : CoreId - Logical CPU core ID                            **
**                  : CompareFlag - Flag to compare with configured SFRs or   **
**                    Variables                                               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Compare flag value - all bits as 1 indicates a pass case**
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Adc_lCheckGlobalCoreVars(const uint32 CoreId, \
                                                       const uint32 CompareFlag)
{
  const Adc_GlobalDataType *lKernelDataPtr;
  uint8 lLoopCount, lRsCount;
  uint32 lSfrVal, lCfgVal, lCompareFlag = CompareFlag;

  /* [cover parentID={61E62711-4C4D-4f0e-BFBF-9F94CC7552BC}]
  Loop for all the indices of the array Adc_KernelData [/cover] */
  for(lLoopCount = (uint8)0U; (lLoopCount < Adc_kKernelUsedCount[CoreId]); \
      lLoopCount++)
  {
    lKernelDataPtr = &Adc_kKernelData[CoreId][lLoopCount];

    /* [cover parentID={D59453D5-93E8-4dcc-94CC-379EECB0BE5B}]
    DMA Mode result handling is OFF [/cover] */
    #if(ADC_RESULT_HANDLING_IMPLEMENTATION != ADC_DMA_MODE_RESULT_HANDLING)
    /* When ADC_RESULT_HANDLING_IMPLEMENTATION is ADC_DMA_MODE_RESULT_HANDLING,
       then ADC_ENABLE_QUEUING will always be STD_OFF.
       Hence, this loop is not required when ADC_RESULT_HANDLING_IMPLEMENTATION
       is ADC_DMA_MODE_RESULT_HANDLING  */
    uint8 lGroupCount;
    /* [cover parentID={034D1913-4170-42c8-8D4F-6E845E8602C4}]
    Till the last available Group [/cover] */
    for(lGroupCount = (uint8)0U; (lGroupCount < ADC_MAX_GROUPS); lGroupCount++)
    {
      /* [cover parentID={B46C9522-A309-4386-B18D-A86AC2FFCCE9}]
      Verify all elements of group specific structure are reset to default value
      [/cover] */

      /* MISRA2012_RULE_11_4_JUSTIFICATION:The address of the buffer pointer is
      stores in a local variable to be comapred against 0-NULL.
      There are no other operation performed, hence this convesion
      does not cause any issue */
      /* MISRA2012_RULE_11_6_JUSTIFICATION:The address of the buffer pointer is
      stores in a local variable to be comapred against 0-NULL.
      There are no other operation performed, hence this convesion
      does not cause any issue */
      /* Compare result buffer values with config value & Update flag
      based on result */
      lSfrVal = (uint32)(lKernelDataPtr->GrpResBuffer[lGroupCount]);
      lCfgVal = (uint32)0U;
      lCompareFlag &= ~(lSfrVal ^ lCfgVal);

      /* Compare number of valid conversion values with config value & Update
      flag based on result */
      lSfrVal = (uint32)(lKernelDataPtr->NumofValidConRes[lGroupCount]);
      lCfgVal = (uint32)0U;
      lCompareFlag &= ~(lSfrVal ^ lCfgVal);

      #if((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW) ||\
          (ADC_ENABLE_QUEUING == STD_ON))
      /* [cover parentID={0C99DD4D-C3C1-4aff-A933-E1C866F8F480}]
      Till the last available Request Source [/cover] */
      for(lRsCount = (uint8)0U; (lRsCount < ADC_REQSRC_USED_COUNT); lRsCount++)
      {
        /* [cover parentID={23BE5A57-E8E1-46e2-A082-CBE907F46C55}]
        Verify all elements of RS specific structure are reset to default value
        [/cover] */
        /* Compare software group Queue values for previous group with config
           value & Update flag based on result */
        lSfrVal = (uint32)(lKernelDataPtr->RSData[lRsCount].\
                           QueueOfSwGroup[lGroupCount].PreviousGroup);
        lCfgVal = (uint32)ADC_INVALID_GROUP_ID;
        lCompareFlag &= ~(lSfrVal ^ lCfgVal);

        /* Compare software group Queue values for next group with config
           value & Update flag based on result */
        lSfrVal = (uint32)(lKernelDataPtr->RSData[lRsCount].\
                           QueueOfSwGroup[lGroupCount].NextGroup);
        lCfgVal = (uint32)ADC_INVALID_GROUP_ID;
        lCompareFlag &= ~(lSfrVal ^ lCfgVal);
      }
      #elif(ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
      /* Compare software group Queue values for Previous group with config
           value & Update flag based on result */
      lSfrVal = (uint32)lKernelDataPtr->QueueOfSwGroup[lGroupCount].\
                                                                  PreviousGroup;
      lCfgVal = (uint32)ADC_INVALID_GROUP_ID;
      lCompareFlag &= ~(lSfrVal ^ lCfgVal);

      /* Compare software group Queue values for next group with config value &
      Update flag based on result */
      lSfrVal = (uint32)lKernelDataPtr->QueueOfSwGroup[lGroupCount].NextGroup;
      lCfgVal = (uint32)ADC_INVALID_GROUP_ID;
      lCompareFlag &= ~(lSfrVal ^ lCfgVal);
      #endif
    }
    #endif
    /* [cover parentID={0C99DD4D-C3C1-4aff-A933-E1C866F8F480}]
    Till the last available Request Source [/cover] */
    for(lRsCount = (uint8)0U; (lRsCount < ADC_REQSRC_USED_COUNT); lRsCount++)
    {
      /* [cover parentID={23BE5A57-E8E1-46e2-A082-CBE907F46C55}]
      Verify all elements of RS specific structure are reset to default value
      [/cover] */
      /* Compare Active Group ID values with config value & Update flag based
         on result */
      lSfrVal = (uint32)(lKernelDataPtr->RSData[lRsCount].ActiveGroupId);
      lCfgVal = (uint32)ADC_INVALID_GROUP_ID;
      lCompareFlag &= ~(lSfrVal ^ lCfgVal);

      /* Compare Active limit check channel values with config value & Update
         flag based on result */
      lSfrVal = (uint32)(lKernelDataPtr->RSData[lRsCount].ActiveLimitChkCh);
      lCfgVal = (uint32)ADC_INVALID_CHANNEL_ID;
      lCompareFlag &= ~(lSfrVal ^ lCfgVal);

      /* Compare ISR No service flag values with config value & Update
         flag based on result */
      lSfrVal = (uint32)(lKernelDataPtr->RSData[lRsCount].IsrNoServiceFlag);
      lCfgVal = (uint32)ADC_ONE_U;
      lCompareFlag &= ~(lSfrVal ^ lCfgVal);

      #if((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW) ||\
          (ADC_ENABLE_QUEUING == STD_ON))
      /* Compare group ID value with config value for pop & Update flag based
         on result */
      lSfrVal = (uint32)(lKernelDataPtr->RSData[lRsCount].PopGroupId);
      lCfgVal = (uint32)ADC_INVALID_GROUP_ID;
      lCompareFlag &= ~(lSfrVal ^ lCfgVal);

      /* Compare group ID value with config value for push & Update flag based
         on result */
      lSfrVal = (uint32)(lKernelDataPtr->RSData[lRsCount].PushGroupId);
      lCfgVal = (uint32)ADC_INVALID_GROUP_ID;
      lCompareFlag &= ~(lSfrVal ^ lCfgVal);
      #endif
    }

    /* [cover parentID={E49F5D28-6707-4a8c-BD43-4E100E174ACE}]
    Verify all elements of structure are reset to default value [/cover] */
    /* Compare group status value with config value & Update flag based
       on result */
    lSfrVal = (uint32)(lKernelDataPtr->GrpStatus);
    lCfgVal = (uint32)0U;
    lCompareFlag &= ~(lSfrVal ^ lCfgVal);

    /* Compare group result status value with config value & Update flag based
       on result */
    lSfrVal = (uint32)(lKernelDataPtr->GrpResultStatus);
    lCfgVal = (uint32)0U;
    lCompareFlag &= ~(lSfrVal ^ lCfgVal);

    /* Compare group buffer end result status value with config value & Update
       flag based on result */
    lSfrVal = (uint32)(lKernelDataPtr->GrpBufferEndResultStatus);
    lCfgVal = (uint32)0U;
    lCompareFlag &= ~(lSfrVal ^ lCfgVal);

    /* Compare group notify status value with config value & Update flag based
       on result */
    lSfrVal = (uint32)(lKernelDataPtr->GrpNotifStatus);
    lCfgVal = (uint32)0U;
    lCompareFlag &= ~(lSfrVal ^ lCfgVal);

    /* Compare all running channels value with config value & Update flag based
       on result */
    lSfrVal = (uint32)(lKernelDataPtr->AllRunningChannels);
    lCfgVal = (uint32)0U;
    lCompareFlag &= ~(lSfrVal ^ lCfgVal);

    /* Compare all running result Reg value with config value & Update flag
       based on result */
    lSfrVal = (uint32)(lKernelDataPtr->AllRunningResReg);
    lCfgVal = (uint32)0U;
    lCompareFlag &= ~(lSfrVal ^ lCfgVal);

    #if(ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
    /* Compare Pop Group ID with config value & Update flag
    based on result */
    lSfrVal = (uint32)(lKernelDataPtr->PopGroupId);
    lCfgVal = (uint32)ADC_INVALID_GROUP_ID;
    lCompareFlag &= ~(lSfrVal ^ lCfgVal);

    /* Compare Push Group ID with config value & Update flag
    based on result */
    lSfrVal = (uint32)(lKernelDataPtr->PushGroupId);
    lCfgVal = (uint32)ADC_INVALID_GROUP_ID;
    lCompareFlag &= ~(lSfrVal ^ lCfgVal);
    #endif

    #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
    #if (ADC_ENABLE_LIMIT_CHECK==STD_ON)
    lSfrVal = (uint8)lKernelDataPtr->LimitChkActiveFlag;
    lCfgVal = (uint32)0U;
    lCompareFlag &= ~(lSfrVal ^ lCfgVal);
    #endif
    lSfrVal = (uint32)lKernelDataPtr->AliasActiveFlag;
    lCfgVal = (uint32)0U;
    lCompareFlag &= ~(lSfrVal ^ lCfgVal);
    #endif

    /* [cover parentID={236A5F78-F48E-48b6-848A-46217175B81B}]
    Low power state support is ON [/cover] */
    #if(ADC_LOW_POWER_STATE_SUPPORT == STD_ON)
    /* [cover parentID={57A95ABF-9929-4c8f-818F-72F24B064DCD}]
    Verify the power state transition request bit for core is reset to ZERO
    [/cover] */
    uint32 lBitPosn;
    lBitPosn = CoreId * (uint32)ADC_BITS_PER_POWER_STATE;
    /* Compare configured power state with reset value */
    lSfrVal = (uint32)((Mcal_GetBitAtomic(\
         Adc_PowerStateTransitionRequestBit, (uint8)lBitPosn, \
                                            (uint32)ADC_BITS_PER_POWER_STATE)));
    lCfgVal = (uint32)0U;
    lCompareFlag &= ~(lSfrVal ^ lCfgVal);
    #endif

    /* [cover parentID={E3A9B08A-8B84-4868-A2ED-D9F1A7BEFC9F}]
    EMUX mode is ON [/cover] */
    #if(ADC_EMUX_ENABLE == STD_ON)
    /* [cover parentID={ABECC2CD-45FB-45cc-BC46-19525521A4E1}]
    Compare Emux Conversion Active Flag with reset value [/cover] */
    lSfrVal = (uint8)lKernelDataPtr->EmuxConversionActiveFlag;
    lCfgVal = (uint32)0U;
    lCompareFlag &= ~(lSfrVal ^ lCfgVal);
    #endif
  }
  return(lCompareFlag);
}
#endif

/*******************************************************************************
** Traceability: [cover parentID={4D100DF8-F519-43d7-B284-5EBE0BCF4B4A}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE void Adc_lKernelInit                       **
**                    (                                                       **
**                       const Adc_HwUnitCfgType * const KernelCfgPtr         **
                         const uint32 KernelId                                **
**                    )                                                       **
**                                                                            **
** Description      : This function programs the kernels Analog Function,     **
**                    Input Class and Arbiter specific SFRs.                  **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different CPU core                        **
**                                                                            **
** Parameters(in)   : KernelCfgPtr - Pointer to the Kernel Config Data        **
**                    KernelId  - Kernel ID                                   **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Adc_lKernelInit(const Adc_HwUnitCfgType *const KernelCfgPtr,\
                                  const uint32 KernelId)
{
  Ifx_EVADC_G *lEvadcGroupPtr;
  const Adc_HwCfgType *lHwCfgPtr;

  /* Get the HW configuration address*/
  lHwCfgPtr = KernelCfgPtr->HwCfgPtr;
  /* Get the SFR base address for the kernel */
  lEvadcGroupPtr = &MODULE_EVADC.G[KernelId];

  /*Initialize kernel SFRs from the configuration */
  lEvadcGroupPtr->ANCFG.U      = lHwCfgPtr->GrpAnalogFuncCfg;
  lEvadcGroupPtr->ARBPR.U      = lHwCfgPtr->GrpArbitPrioCfg;
  lEvadcGroupPtr->ICLASS[0U].U = lHwCfgPtr->KernelInputClass0Cfg;
  lEvadcGroupPtr->ICLASS[1U].U = lHwCfgPtr->KernelInputClass1Cfg;
  lEvadcGroupPtr->SYNCTR.U     = lHwCfgPtr->GrpSyncCtrlCfg;

  /* Initialize the Service nodes for Request Source events */
  /* RSx event is mapped to SRx, x = 0..2*/
  lEvadcGroupPtr->SEVNP.U      = ADC_SEVNP_INIT_CFG_VALUE;

  /* Set channel event node pointer to SR3 for all channels
  Channel event will be triggered only when CHCTR.CHEVMODE is enabled
  for Limit checking groups */
  /* Initialize the service request node for channel events */
  lEvadcGroupPtr->CEVNP0.U = ADC_CEVNP_INIT_CFG_VALUE;
  /* Secondary kernel is available */
  #if (ADC_SECONDARY_KERNEL_AVAILABLE == STD_ON)
  if(KernelId > ADC_LAST_PRIMARY_KERNELID)
  {
    lEvadcGroupPtr->CEVNP1.U = ADC_CEVNP_INIT_CFG_VALUE;
  }
  #endif
  /* Initialize the service node for result event */
  lEvadcGroupPtr->REVNP0.U      = ADC_REVNP_INIT_CFG_VALUE;
  lEvadcGroupPtr->REVNP1.U      = ADC_REVNP_INIT_CFG_VALUE;

  /* Converter is NOT SWITCHED ON here */
  lEvadcGroupPtr->ARBCFG.U     = lHwCfgPtr->GrpArbitCfg;
}

#if (ADC_INIT_CHECK_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={25920956-D591-4a1d-8D37-C7E5E8F7D758}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint32 Adc_lCheckKernelSfr                 **
**                    (                                                       **
**                       const Adc_HwUnitCfgType * const KernelCfgPtr         **
**                       const uint32 KernelId,                               **
**                       const uint32 CompareFlag                             **
**                    )                                                       **
**                                                                            **
** Description      : This function checks the SFR values of Initialized      **
**                    kernels with configured values                          **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different ADC hardware groups             **
**                                                                            **
** Parameters(in)   : KernelCfgPtr - Pointer to the Kernel Config Data        **
**                    KernelId  - Kernel ID                                   **
**                  : CompareFlag - Flag to compare with configured SFRs or   **
**                    Variables                                               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Compare flag value - all bits as 1 indicates a pass case**
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Adc_lCheckKernelSfr(\
           const Adc_HwUnitCfgType *const KernelCfgPtr,\
           const uint32 KernelId, const uint32 CompareFlag)
{
  const Ifx_EVADC_G *lEvadcGroupPtr;
  uint32 lSfrVal, lCfgVal;
  uint32 lCompareFlag = CompareFlag;
  uint8 lLoopCount, lChannelCount;
  const Adc_HwCfgType *lHwCfgPtr;

  /* Get the HW configuration address*/
  lHwCfgPtr = KernelCfgPtr->HwCfgPtr;
  /* Get the SFR base address for the kernel */
  lEvadcGroupPtr = &MODULE_EVADC.G[KernelId];

  /* Compare Trigger control Register with configuration value &
  Update flag as per result */
  lSfrVal = lEvadcGroupPtr->TRCTR.U;
  lSfrVal = lSfrVal & ((uint32)~((uint32)IFX_EVADC_G_TRCTR_TSC_MSK));
  lCfgVal = (uint32)0U;
  lCompareFlag &= ~(lSfrVal ^ lCfgVal);

  /* Compare ANONS and ANONC values */
  lSfrVal = (((uint32)MODULE_EVADC.G[KernelId].ARBCFG.U) &\
       (((uint32)IFX_EVADC_G_ARBCFG_ANONC_MSK<<IFX_EVADC_G_ARBCFG_ANONC_OFF)|\
        ((uint32)IFX_EVADC_G_ARBCFG_ANONS_MSK<<IFX_EVADC_G_ARBCFG_ANONS_OFF)) );
  lCfgVal = (lHwCfgPtr->GrpArbitCfg & \
          ((uint32)IFX_EVADC_G_ARBCFG_ANONC_MSK<<IFX_EVADC_G_ARBCFG_ANONC_OFF));
  lCfgVal |= (uint32)(((~(uint32)ADC_FULL_POWER) & \
                       ADC_TARGET_POWER_STATE_MASK) << \
                      IFX_EVADC_G_ARBCFG_ANONS_OFF);

  lCompareFlag &= ~(lSfrVal ^ lCfgVal);

  /* Compare Arbitration Priority register value with config value &
     Update flag based on result */
  lSfrVal = (lEvadcGroupPtr->ARBPR.U);
  lCfgVal = (lHwCfgPtr->GrpArbitPrioCfg);
  lCompareFlag &= ~(lSfrVal ^ lCfgVal);

  /* Compare Analog function control register value with config value &
     Update flag based on result */
  lSfrVal = (lEvadcGroupPtr->ANCFG.U);
  lCfgVal = (lHwCfgPtr->GrpAnalogFuncCfg);
  lCompareFlag &= ~(lSfrVal ^ lCfgVal);

  /* Compare Input Class0 register value with config value & Update flag
     based on result */
  lSfrVal = (lEvadcGroupPtr->ICLASS[0U].U);
  lCfgVal = (lHwCfgPtr->KernelInputClass0Cfg);
  lCompareFlag &= ~(lSfrVal ^ lCfgVal);

  /* Compare Input Class1 register value with config value & Update flag
     based on result */
  lSfrVal = (lEvadcGroupPtr->ICLASS[1U].U);
  lCfgVal = (lHwCfgPtr->KernelInputClass1Cfg);
  lCompareFlag &= ~(lSfrVal ^ lCfgVal);

  /* Compare Alias Register with configuration value &
  Update flag as per result */
  lSfrVal = lEvadcGroupPtr->ALIAS.U;
  lCfgVal = ADC_ALIAS_DEFAULT_VALUE;
  lCompareFlag &= ~(lSfrVal ^ lCfgVal);

  /* Compare Bound Register with configuration value &
  Update flag as per result */
  lSfrVal = lEvadcGroupPtr->BOUND.U;
  lCfgVal = (uint32)0U;
  lCompareFlag &= ~(lSfrVal ^ lCfgVal);

  /* Compare Sync Control register value with config value & Update flag
  based on result for Slave Kernel */
  lSfrVal = (lEvadcGroupPtr->SYNCTR.U);
  lCfgVal = (lHwCfgPtr->GrpSyncCtrlCfg);
  lCompareFlag &= ~(lSfrVal ^ lCfgVal);

  for(lLoopCount = (uint8)0U; (lLoopCount < ADC_REQSRC_COUNT); lLoopCount++)
  {
    /* Compare Queue Source control Register with configuration value &
    Update flag as per result */
    lSfrVal = ( ((uint32)lEvadcGroupPtr->Q[lLoopCount].QCTRL.U) & ((uint32)\
    (~(((uint32)IFX_EVADC_G_Q_QCTRL_XTLVL_MSK<<IFX_EVADC_G_Q_QCTRL_XTLVL_OFF)|
    ((uint32)IFX_EVADC_G_Q_QCTRL_GTLVL_MSK<<IFX_EVADC_G_Q_QCTRL_GTLVL_OFF)))) );
    lCfgVal = (uint32)0U;
    lCompareFlag &= ~(lSfrVal ^ lCfgVal);

    /* Compare Queue Mode Register with configuration value &
    Update flag as per result */
    lSfrVal = lEvadcGroupPtr->Q[lLoopCount].QMR.U;
    lCfgVal = (uint32)0U;
    lCompareFlag &= ~(lSfrVal ^ lCfgVal);

    /* Compare Queue status Register with configuration value &
    Update flag as per result */
    lSfrVal = (((uint32)lEvadcGroupPtr->Q[lLoopCount].QSR.U) & \
               ((uint32)~((uint32)IFX_EVADC_G_Q_QSR_REQGT_MSK << \
                          IFX_EVADC_G_Q_QSR_REQGT_OFF)));
    lCfgVal = ((uint32)ADC_ONE_U << IFX_EVADC_G_Q_QSR_EMPTY_OFF);
    lCompareFlag &= ~(lSfrVal ^ lCfgVal);

    /* Compare Queue Request Timer Mode Register with configuration value &
    Update flag as per result */
    lSfrVal = lEvadcGroupPtr->Q[lLoopCount].REQTM.U;
    lCfgVal = ADC_REQTM_RESET_VALUE;
    lCompareFlag &= ~(lSfrVal ^ lCfgVal);

  }

  /* Compare Channel event flag registers with configuration value
  & Update flag as per result */
  lSfrVal = lEvadcGroupPtr->CEFLAG.U;
  lCfgVal = (uint32)0U;
  lCompareFlag &= ~(lSfrVal ^ lCfgVal);

  /* Compare Result event flag registers with configuration value
  & Update flag as per result */
  lSfrVal = lEvadcGroupPtr->REFLAG.U;
  lCfgVal = (uint32)0U;
  lCompareFlag &= ~(lSfrVal ^ lCfgVal);

  /* Compare Source event flag registers with configuration value
  & Update flag as per result */
  lSfrVal = lEvadcGroupPtr->SEFLAG.U;
  lCfgVal = (uint32)0U;
  lCompareFlag &= ~(lSfrVal ^ lCfgVal);

  /* Compare Channel Event Node pointer0 register value with config value &
     Update flag based on result */
  lSfrVal = (lEvadcGroupPtr->CEVNP0.U);
  lCfgVal = (ADC_CEVNP_INIT_CFG_VALUE);
  lCompareFlag &= ~(lSfrVal ^ lCfgVal);

  #if (ADC_SECONDARY_KERNEL_AVAILABLE == STD_ON)
  if(KernelId > ADC_LAST_PRIMARY_KERNELID)
  {
    /* Compare Channel Event Node pointer1 register value with config value &
       Update flag based on result */
    lSfrVal = (lEvadcGroupPtr->CEVNP1.U);
    lCfgVal = (ADC_CEVNP_INIT_CFG_VALUE);
    lCompareFlag &= ~(lSfrVal ^ lCfgVal);
  }
  #endif

  /* Compare Result Event Node pointer0 register value with config value &
     Update flag based on result */
  lSfrVal = (lEvadcGroupPtr->REVNP0.U);
  lCfgVal = (ADC_REVNP_INIT_CFG_VALUE);
  lCompareFlag &= ~(lSfrVal ^ lCfgVal);

  /* Compare Result Event Node pointer1 register value with config value &
     Update flag based on result */
  lSfrVal = (lEvadcGroupPtr->REVNP1.U);
  lCfgVal = (ADC_REVNP_INIT_CFG_VALUE);
  lCompareFlag &= ~(lSfrVal ^ lCfgVal);

  /* Compare Source Event Node pointer register value with config value &
     Update flag based on result */
  lSfrVal = (lEvadcGroupPtr->SEVNP.U);
  lCfgVal = (ADC_SEVNP_INIT_CFG_VALUE);
  lCompareFlag &= ~(lSfrVal ^ lCfgVal);

  /* Compare External Multiplexer Control register with configuration value &
  Update flag as per result */
  lSfrVal = lEvadcGroupPtr->EMUXCTR.U;
  lCfgVal = (uint32)0U;
  lCompareFlag &= ~(lSfrVal ^ lCfgVal);

  /* Compare Ext. Multiplexer Channel Select Register with configuration value
     & Update flag as per result */
  lSfrVal = lEvadcGroupPtr->EMUXCS.U;
  lCfgVal = (uint32)0U;
  lCompareFlag &= ~(lSfrVal ^ lCfgVal);

  /* Compare Valid flag registers with configuration value
  & Update flag as per result */
  lSfrVal = lEvadcGroupPtr->VFR.U;
  lCfgVal = (uint32)0U;
  lCompareFlag &= ~(lSfrVal ^ lCfgVal);

  if(KernelId > ADC_LAST_PRIMARY_KERNELID)
  {
    /* Update channel count value for secondary Kernel */
    lChannelCount = (uint8)ADC_SECONDARY_CONV_CHANNEL_COUNT;
  }
  else
  {
    /* Update channel count value for primary Kernel */
    lChannelCount = (uint8)ADC_PRIMARY_CONV_CHANNEL_COUNT;
  }

  for(lLoopCount = (uint8)0U; (lLoopCount < lChannelCount); lLoopCount++)
  {
    /* Compare Channel control registers with configuration value
    & Update flag as per result */
    lSfrVal = lEvadcGroupPtr->CHCTR[lLoopCount].U;
    lCfgVal = (uint32)0U;
    lCompareFlag &= ~(lSfrVal ^ lCfgVal);
  }

  for(lLoopCount = (uint8)0U; (lLoopCount < (uint8)ADC_MAX_RESULT_REGISTERS); \
      lLoopCount++)
  {
    /* Compare Result control registers with configuration value
    & Update flag as per result */
    lSfrVal = lEvadcGroupPtr->RCR[lLoopCount].U;
    lCfgVal = (uint32)0U;
    lCompareFlag &= ~(lSfrVal ^ lCfgVal);

    /* Compare Result control registers with configuration value
    & Update flag as per result */
    lSfrVal = lEvadcGroupPtr->RES[lLoopCount].U;
    lSfrVal = lSfrVal &\
              ((uint32)IFX_EVADC_G_RES_VF_MSK << IFX_EVADC_G_RES_VF_OFF);
    lCfgVal = (uint32)0U;
    lCompareFlag &= ~(lSfrVal ^ lCfgVal);
  }
  return(lCompareFlag);
}
#endif

/*******************************************************************************
** Traceability: [cover parentID={C6FB6B18-9430-4db9-A6BF-4F2E01256FAC}]      **
**                                                                            **
** Syntax           : static void Adc_lKernelDeInit                           **
**                    (                                                       **
**                       const Adc_HwUnitCfgType * const KernelCfgPtr         **
**                       const uint32 KernelId                                **
**                    )                                                       **
**                                                                            **
** Description      : This function resets the global SFRs of EVADC           **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different CPU core                        **
**                                                                            **
** Parameters(in)   : KernelCfgPtr - Pointer to the Kernel Config Data        **
**                    KernelId  - Kernel ID                                   **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Adc_lKernelDeInit(const Adc_HwUnitCfgType *const KernelCfgPtr,\
                              const uint32 KernelId)
{
  Ifx_EVADC_G *lEvadcGroupPtr;
  uint8 lLoopCount, lChannelCount;

  lEvadcGroupPtr = &MODULE_EVADC.G[KernelId];
  /* [cover parentID={A3BBAD45-CECD-41fa-912F-D198D357B4F2}]
  HW Trigger API is Enabled [/cover] */
  #if (ADC_HW_TRIGGER_API == STD_ON)
  const Adc_GroupCfgType *lGrpCfgPtr;
  uint8 lGroupCount;

  lGrpCfgPtr = KernelCfgPtr->GrpCfgPtr;
  lGroupCount = KernelCfgPtr->NoOfGroups;

  /* Loop for all the HW triggered groups, and reset the HW trigger peripheral*/
  for(lLoopCount = (uint8)0U; lLoopCount < lGroupCount; lLoopCount++)
  {
    /* [cover parentID={19FA0141-8A36-4a96-A8C4-E5FD9905A40D}]
    Is HW Trigger Group and Request Timer not configured [/cover] */
    if((lGrpCfgPtr[lLoopCount].TriggerSource) == ADC_TRIGG_SRC_HW)
    {
      /* [cover parentID={19FA0141-8A36-4a96-A8C4-E5FD9905A40D}]
      Is HW Trigger Group and Request Timer not configured [/cover] */
      if (lGrpCfgPtr[lLoopCount].GrpReqTmCfg == (uint32)0U)
      {
        /* [cover parentID={319CE3CD-62D7-4ff1-818C-1706124AACCC}]
        Reset HW Trigger  [/cover] */
        Adc_lResetHwTrigger(&lGrpCfgPtr[lLoopCount], (uint8)ADC_INIT_DEINIT);
      }
    }
  }
  #endif
  UNUSED_PARAMETER(KernelCfgPtr);

  for(lLoopCount = (uint8)0U; lLoopCount < ADC_REQSRC_COUNT; lLoopCount++)
  {
    /* Flush the Queue */
    lEvadcGroupPtr->Q[lLoopCount].QMR.U =(\
                              ((uint32)ADC_ONE_U<<IFX_EVADC_G_Q_QMR_FLUSH_OFF)|\
                              ((uint32)ADC_ONE_U<<IFX_EVADC_G_Q_QMR_CEV_OFF)|\
                              ((uint32)ADC_ONE_U<<IFX_EVADC_G_Q_QMR_CLRV_OFF));
    lEvadcGroupPtr->Q[lLoopCount].QCTRL.U = ADC_Q_CTRL_WRITE_PROTECT_MSK;
    lEvadcGroupPtr->Q[lLoopCount].REQTM.U = ADC_REQTM_RESET_VALUE;
  }

  /* Clear Kernel registers and Switch off the converter also */
  lEvadcGroupPtr->ARBCFG.U = (uint32)0U;
  /* Ensure register is written and converter is switched OFF */
  DSYNC();

  lEvadcGroupPtr->TRCTR.U = ((uint32)ADC_ONE_U << \
                             IFX_EVADC_G_TRCTR_COV_OFF);

  lEvadcGroupPtr->ARBPR.U        = (uint32)0U;
  lEvadcGroupPtr->ANCFG.U        = ADC_ANCFG_DEFAULT_VALUE;
  lEvadcGroupPtr->ICLASS[0U].U   = (uint32)0U;
  lEvadcGroupPtr->ICLASS[1U].U   = (uint32)0U;
  lEvadcGroupPtr->ALIAS.U        = ADC_ALIAS_DEFAULT_VALUE;
  lEvadcGroupPtr->BOUND.U        = (uint32)0U;
  lEvadcGroupPtr->SYNCTR.U       = (uint32)0U;
  lEvadcGroupPtr->EMUXCTR.U      = (uint32)ADC_ONE_U << \
                                   IFX_EVADC_G_EMUXCTR_EMXWC_OFF;
  lEvadcGroupPtr->EMUXCS.U       = (uint32)0U;

  if(KernelId > ADC_LAST_PRIMARY_KERNELID)
  {
    lChannelCount = (uint8)ADC_SECONDARY_CONV_CHANNEL_COUNT;
  }
  else
  {
    lChannelCount = (uint8)ADC_PRIMARY_CONV_CHANNEL_COUNT;
  }
  for(lLoopCount = (uint8)0U; lLoopCount < lChannelCount; lLoopCount++)
  {
    /*Clear Channel control registers,
      - 8 channels for primary converter
      - 16 channels for primary converter */
    lEvadcGroupPtr->CHCTR[lLoopCount].U = (uint32)0U;
  }
  for(lLoopCount = (uint8)0U; \
      lLoopCount < (uint8)ADC_MAX_RESULT_REGISTERS; lLoopCount++)
  {
    /* Clear all 16 result control registers */
    lEvadcGroupPtr->RCR[lLoopCount].U = (uint32)0U;
  }

  /* Clear Source events, result event ,channel event flags and
     service node pointers*/
  lEvadcGroupPtr->VFR.U      = ADC_CLR_VALID_FLAG_REG;
  lEvadcGroupPtr->SEFCLR.U   = ADC_CLR_SOURCE_EVENT;
  lEvadcGroupPtr->REFCLR.U   = ADC_CLR_RESULT_EVENT;
  lEvadcGroupPtr->SEVNP.U    = (uint32)0U;
  lEvadcGroupPtr->REVNP0.U   = (uint32)0U;
  lEvadcGroupPtr->REVNP1.U   = (uint32)0U;
  lEvadcGroupPtr->CEVNP0.U   = (uint32)0U;

  #if (ADC_SECONDARY_KERNEL_AVAILABLE == STD_ON)
  if(KernelId > ADC_LAST_PRIMARY_KERNELID)
  {
    /* Since channel count for secondary converters is 16,
       hence Channel event register and CEVNP1 are cleared here*/
    lEvadcGroupPtr->CEFCLR.U = ADC_CLR_SECONDARY_CH_EVENT;
    lEvadcGroupPtr->CEVNP1.U = (uint32)0U;
  }
  else
  #endif
  {
    /* Channel count for primary converters is 8 */
    lEvadcGroupPtr->CEFCLR.U = ADC_CLR_PRIMARY_CH_EVENT;
  }
}

#if (ADC_TRIGGER_ONE_CONV_ENABLE == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={8478D451-B801-4f2c-9DAC-57E3DD256555}]      **
**                                                                            **
** Syntax           : static Std_ReturnType Adc_lTriggerOneConversion         **
**                    (                                                       **
**                       void                                                 **
**                    )                                                       **
**                                                                            **
** Description      : This function triggers dummy conversion for each        **
**                    configured ADC HW group (Refer Errata ADC_TC.083)       **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK: Dummy conversion successfully completed           **
**                    E_NOT_OK: Dummy conversion not completed                **
*******************************************************************************/
static Std_ReturnType Adc_lTriggerOneConversion(void)
{
  Ifx_EVADC_G *lEvadcGroupPtr;
  Ifx_EVADC_G_Q *lEvadcQPtr;
  uint32 lVfrReg, lCoreId, lKernelCount;
  uint32 lTriggeredKernels = 0U;
  uint32 lWaitCount = 0U;
  Std_ReturnType lRetVal = E_OK;

  for(lCoreId = 0U; lCoreId < MCAL_NO_OF_CORES; lCoreId++ )
  {
    /* [cover parentID={A77C0846-D561-4cf8-9374-49D4C9F388AB}]
    Is Core Configured [/cover] */
    if(Adc_ConfigPtr->CoreCfgPtr[lCoreId] != NULL_PTR)
    {
      /* [cover parentID={72900E14-77AB-418f-AD42-B4279B4FA8A2}]
      Till the last available Kernel [/cover] */
      for(lKernelCount = (uint32)0U; lKernelCount < ADC_MAX_KERNEL_ID; \
          lKernelCount++)
      {
        /* [cover parentID={35998E4A-B1C0-4eaa-BC02-A44455AE5540}]
        Is Kernel Configured [/cover] */
        if(Adc_ConfigPtr->CoreCfgPtr[lCoreId]->HwUnitCfgPtr[lKernelCount] != \
            NULL_PTR)
        {
          /* [cover parentID={21442C93-8EE3-426f-93A9-022363625A56}]
          Trigger one dummy Conversion [/cover] */
          lEvadcGroupPtr = &MODULE_EVADC.G[lKernelCount];
          lEvadcQPtr = &MODULE_EVADC.G[lKernelCount].Q[0U];
          lEvadcGroupPtr->CHCTR[0U].U = (uint32)0U;
          lEvadcGroupPtr->RCR[0U].U = (uint32)0U;
          lEvadcGroupPtr->VFR.U = (uint32)ADC_ONE_U;
          lEvadcQPtr->QCTRL.U = (uint32)ADC_Q_CTRL_WRITE_PROTECT_MSK;
          lEvadcQPtr->QINR.U = (uint32)0U;
          lEvadcQPtr->QMR.U = ADC_START_SW_TRIG_CONV;
          lTriggeredKernels |= (uint32)ADC_ONE_U << lKernelCount;
        }
      }
    }
  }
  /* [cover parentID={E6B1D8FB-C7CD-45c4-92C4-473D8FE24778}]
  Till the last available Kernel [/cover] */
  for(lKernelCount = (uint32)0U; lKernelCount < ADC_MAX_KERNEL_ID; \
      lKernelCount++)
  {
    /* [cover parentID={33EC6A57-9643-44ce-888F-216BBA9C892A}]
    Is Kernel Triggered [/cover] */
    if( (lTriggeredKernels & ((uint32)ADC_ONE_U << lKernelCount)) != (uint32)0U)
    {
      lEvadcGroupPtr = &MODULE_EVADC.G[lKernelCount];
      /* [cover parentID={A349F2FD-16A8-44c7-9A67-E863F54F5544}]
      Till the defined Max WaitCount & Valid Result flag is equal to ZERO
      [/cover] */
      lWaitCount = 0U;
      do
      {
        /* [cover parentID={B34CD187-C755-4ade-B6CF-606541FF0FE2}]
        Read the Valid flag of Result register & Increment the WaitCount
        [/cover] */
        lVfrReg = lEvadcGroupPtr->VFR.U;
        lWaitCount++;
      }while((lVfrReg == 0U) && (lWaitCount < (uint32)ADC_WAIT_FOR_DUMMY_CONV));
      /* Flush the RS queue */
      lEvadcGroupPtr->Q[0U].QMR.U =\
                      (((uint32)ADC_ONE_U<<IFX_EVADC_G_Q_QMR_FLUSH_OFF)|\
                      ((uint32)ADC_ONE_U<<IFX_EVADC_G_Q_QMR_CEV_OFF)|\
                      ((uint32)ADC_ONE_U<<IFX_EVADC_G_Q_QMR_CLRV_OFF));
      /* Clear valid flags and event flags*/
      lEvadcGroupPtr->SEFCLR.U = (uint32)ADC_ONE_U;
      lEvadcGroupPtr->CEFCLR.U = (uint32)ADC_ONE_U;
      lEvadcGroupPtr->REFCLR.U = (uint32)ADC_ONE_U;
      lEvadcGroupPtr->VFR.U = (uint32)ADC_ONE_U;
      /* [cover parentID={C857F799-8EE1-4bd5-B29E-F16A0BB767EB}]
      WaitCount is greater than or equal to defined Max WaitCount [/cover] */
      if(lWaitCount >= ADC_WAIT_FOR_DUMMY_CONV)
      {
        /* [cover parentID={CDF0DF8F-FFBA-47de-98F1-33A6F579C871}]
        Update return value with E_NOT_OK [/cover] */
        lRetVal = E_NOT_OK;
      }
    }
  }
  return lRetVal;
}
#endif

/*******************************************************************************
** Traceability: [cover parentID={EB9DD6B6-5AD9-4391-B824-5E454CD75B1A}]      **
**                                                                            **
** Syntax           : static void Adc_lPrepareGrpForStart                     **
**                    (                                                       **
**                      const uint32 KernelId,                                **
**                      const Adc_GroupType  GroupId                          **
**                      const uint32 CoreId                                   **
**                    )                                                       **
**                                                                            **
** Description      : This function prepares (configures) all the analog      **
**                   channels and result registers of the group for conversion**
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different ADC hardware groups             **
**                                                                            **
** Parameters(in)   : KernelId  - ADC Kernel to which the group belongs       **
**                    GroupId   - ADC Group ID of the Kernel                  **
**                    CoreId    - Logical CPU core ID                         **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Adc_lPrepareGrpForStart(const uint32 KernelId,\
                                const Adc_GroupType GroupId,const uint32 CoreId)
{
  Ifx_EVADC_G *lEvadcGroupPtr;
  const Adc_GroupCfgType *lGrpCfgPtr;
  const Adc_ChannelCfgType *lChCfgPtr;
  const Adc_GroupDefType *lGrpDefCfgPtr;
  uint32 lChctrCfgVal;
  Adc_ChannelType lAsChannelId, lAnChannelId;
  Adc_ResultRegType lResReg;
  uint8 lNoOfChannels, lChloopCount;
  #if(ADC_EMUX_ENABLE == STD_ON)
  uint8 lEmuxGrp;
  #endif

  /*Get the SFR base address for the kernel */
  lEvadcGroupPtr = &MODULE_EVADC.G[KernelId];
  /*Get the base address of the group configuration */
  lGrpCfgPtr = &(Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[KernelId]->\
                 GrpCfgPtr[GroupId]);
  /*Get the base address of the channel configuration */
  lChCfgPtr = Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[KernelId]->\
              ChCfgPtr;
  /* Get the base address of the group definition */
  lGrpDefCfgPtr = lGrpCfgPtr->GroupDefinition;

  lNoOfChannels = lGrpCfgPtr->NoOfChannels;

  /* [cover parentID={59AD44B6-B3F2-4bc4-8389-4C21E2C16122}]
  Is the group configured for alias? [/cover] */
  if (ADC_ALIAS_DEFAULT_VALUE != lGrpCfgPtr->AliasChCfg)
  {
    /* [cover parentID={667FC348-2E6D-419a-BAE8-89EF407C8128}]
    Program alias registers as per configuration [/cover] */
    lEvadcGroupPtr->ALIAS.U = lGrpCfgPtr->AliasChCfg;
  }
  /* [cover parentID={1BF04B0E-26CF-4098-A100-DEDCC7CD515C}]
  EMUX is enabled [/cover] */
  #if(ADC_EMUX_ENABLE == STD_ON)
  uint8 lEmuxStartSelVal;
  lEmuxGrp = (ADC_ONE_U & (lGrpCfgPtr->GrpEmuxCfg));
  /* [cover parentID={9C09F698-EA1A-4b40-9F67-E851F583BEED}]
  Group is configured with the EMUX [/cover] */
  if(lEmuxGrp == ADC_ONE_U)
  {
    /* [cover parentID={F24F1A44-F7C7-42c0-B581-DBC890C42A40}]
    Program the EMUX control register with the start selection value of
    emux when EMUX mode is 000U [/cover] */
    lEmuxStartSelVal = ((lGrpCfgPtr->GrpEmuxCfg) >> ADC_ONE_U);
    lEvadcGroupPtr->EMUXCTR.U = ((uint32)lEmuxStartSelVal | \
                                                   ADC_EMUX_DUMMY_MODE_PROGRAM);
    /* Program the EMUX control register with actual EMUX mode */
    lEvadcGroupPtr->EMUXCTR.U = ((uint32)lEmuxStartSelVal | \
                                                ADC_EMUX_SEQUENCE_MODE_PROGRAM);
  }
  #endif
  lChloopCount = (uint8)0U;
  /* [cover parentID={63F185D6-5E0A-44df-8A09-BD85073FCF3E}]
  Till the last available channel [/cover] */
  do
  {
    /*Get the AS channel ID, this is used to get the CHCTR config value*/
    lAsChannelId = lGrpDefCfgPtr[lChloopCount].ASChannelId;
    /* Get the analog channel number */
    lAnChannelId = lGrpDefCfgPtr[lChloopCount].AnalogChannelNo;
    /* [cover parentID={26FB08AE-85F3-486e-88FD-839406F29E06}]
    EMUX is enabled [/cover] */
    #if(ADC_EMUX_ENABLE == STD_ON)
    /* [cover parentID={2A42C3F1-1C17-4a42-8E8A-7898457A72E5}]
    Group is configured with the EMUX [/cover] */
    if(lEmuxGrp == ADC_ONE_U)
    {
      /* [cover parentID={2A42C3F1-1C17-4a42-8E8A-7898457A72E5}]
      Program the  EMUX channel select register [/cover] */
      lEvadcGroupPtr->EMUXCS.U = lAnChannelId;
    }
    #endif

    lResReg = lGrpDefCfgPtr[lChloopCount].ResultReg;

    /* Program Channel configuration with result register */
    lChctrCfgVal = (lChCfgPtr[lAsChannelId].ChannelChctrCfg | ((uint32)lResReg\
                    << IFX_EVADC_G_CHCTR_RESREG_OFF));

    /* [cover parentID={D65037C1-2D39-4383-8D10-DAE25E99E065}]
    Configure channel conrtol register   [/cover] */
    /* Write the CHCTR value back to SFR */
    lEvadcGroupPtr->CHCTR[lAnChannelId].U = lChctrCfgVal;
    lEvadcGroupPtr->RCR[lResReg].U = (uint32)0U;

    /* [cover parentID={1A23377F-796A-4d54-B8CE-A23AE6C43948}]
    Sync Conversion is on [/cover] */
    #if (ADC_SYNC_CONV_ENABLE == STD_ON)
    /* [cover parentID={8A00E242-7200-4378-8225-2FDE200FA4BB}]
    Is channel configured for Sync conversion [/cover] */
    if(((uint16)(lGrpCfgPtr->SyncChannelMask &\
        (uint16)((uint16)1U <<lAnChannelId)))!= (uint16)0U)
    {
      /* [cover parentID={78AF8FF5-48C6-412a-BF96-133912894715}]
      Enable Sync channels [/cover] */
      Adc_lEnableSyncCh(KernelId, lAnChannelId, lChctrCfgVal, lResReg, CoreId);
    }
    #endif

    lChloopCount++;
  } while(lChloopCount < lNoOfChannels);

  /* [cover parentID={DEB59273-1EA8-41dd-89F4-68DA2BC790D7}]
  DMA mode is ON [/cover] */
  #if(ADC_RESULT_HANDLING_IMPLEMENTATION == ADC_DMA_MODE_RESULT_HANDLING)
  /* [cover parentID={E619480D-F939-4414-B1D2-914474252B3E}]
  Enable Result event for last conversion [/cover] */
  lEvadcGroupPtr->RCR[lResReg].U = (uint32)ADC_ONE_U<<IFX_EVADC_G_RCR_SRGEN_OFF;
  #endif

  /* [cover parentID={CB488856-3944-44db-8D26-5AEE993A1F12}]
  Limit Checking is ON [/cover] */
  #if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
  /* [cover parentID={1657BA4C-4D88-4a52-BECE-B4F2CD72016F}]
  Is Adc Limit Check for Group is enabled  [/cover] */
  if((uint8)ADC_ONE_U == lGrpCfgPtr->LimitCheckGroup)
  {
    /* [cover parentID={FEC6169D-C3CE-4b5c-ADE7-2236B7E28669}]
    Program Boundary values   [/cover] */
    /* Set limit check boundary values and channel event node pointer */
    lEvadcGroupPtr->BOUND.U = lChCfgPtr[lAsChannelId].BoundaryValues;
  }
  #endif
}

#if (ADC_SYNC_CONV_ENABLE == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={A1E6D446-8FB6-46b2-9B67-47970273DEA4}]      **
**                                                                            **
** Syntax           : static void Adc_lEnableSyncCh                           **
**                    (                                                       **
**                      const uint32 KernelId,                                **
**                      const Adc_ChannelType AnChannelNum,                   **
**                      const uint32 ChctrValue,                              **
**                      const Adc_ResultRegType ResReg,                       **
**                      const uint32 CoreId                                   **
**                    )                                                       **
**                                                                            **
** Description      : This configures the slave channels of a synchronization **
**                    group                                                   **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different ADC hardware groups             **
**                                                                            **
** Parameters(in)   : KernelId     - ADC Kernel                               **
**                    AnChannelNum - Analog channel number                    **
**                    ChctrValue   - CHCTR register value to configure        **
**                    ResReg       - Result register of the channel           **
**                    CoreId       - Logical CPU core ID                      **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Adc_lEnableSyncCh(const uint32 KernelId,\
                              const Adc_ChannelType AnChannelNum,\
                              const uint32 ChctrValue,\
                              const Adc_ResultRegType ResReg,\
                              const uint32 CoreId)
{
  Ifx_EVADC_G *lEvadcGroupPtr;
  const Adc_HwUnitCfgType * lHwUnitCfgPtr;
  uint8 lKernelCount, lSlaveKernel;

  /* Get the base address of the kernel configuration */
  lHwUnitCfgPtr = Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[KernelId];

  /* [cover parentID={2DDAC232-4D74-49c4-BA19-B295AD7EC847}]
  Till the last available Kernel [/cover] */
  for (lKernelCount = (uint8)0U;
       lKernelCount < (uint8)(ADC_KERNELS_PER_SYNGRP - 1U); lKernelCount++)
  {
    lSlaveKernel = lHwUnitCfgPtr->SlaveKernels[lKernelCount];
    /* [cover parentID={E7C200C0-E802-4e51-B8B6-E6084E89866D}]
    Valid Slave Kernel [/cover] */
    if (lSlaveKernel != ADC_INVALID_KERNEL_ID)
    {
      /* Get the SFR base address for the current slave kernel */
      lEvadcGroupPtr = &MODULE_EVADC.G[lSlaveKernel];

      /* [cover parentID={FB93277D-92A9-4a19-8B66-63BA2637701C}]
      Configure channel control register & reset Result control register
      [/cover] */
      lEvadcGroupPtr->CHCTR[AnChannelNum].U = ChctrValue;
      lEvadcGroupPtr->RCR[ResReg].U = (uint32)0U;
    }
  }
}
#endif

#if (ADC_SYNC_CONV_ENABLE == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={93B5E617-74F5-46af-BB26-84293C290F35}]      **
**                                                                            **
** Syntax           : static void Adc_lClearSyncCh                            **
**                    (                                                       **
**                      const uint32 KernelId,                                **
**                      const Adc_ChannelType AnChannelNum,                   **
**                      const Adc_ResultRegType ResReg,                       **
**                    )                                                       **
**                                                                            **
** Description      : This clears the slave channels for synchronization      **
**                    group                                                   **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different ADC hardware groups             **
**                                                                            **
** Parameters(in)   : KernelId     - ADC Kernel                               **
**                    AnChannelNum - Analog channel number                    **
**                    ResReg       - Result register of the channel           **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Adc_lClearSyncCh(const uint32 KernelId, \
                             const Adc_ChannelType AnChannelNum, \
                             const Adc_ResultRegType ResReg)
{
  Ifx_EVADC_G *lEvadcGroupPtr;
  uint32 lCoreId;
  const Adc_HwUnitCfgType * lHwUnitCfgPtr;
  uint8 lKernelCount, lSlaveKernel;

  /* Get the core Id from which it is called */
  lCoreId = Mcal_GetCpuIndex();

  /* Get the base address of the kernel configuration */
  lHwUnitCfgPtr = Adc_ConfigPtr->CoreCfgPtr[lCoreId]->HwUnitCfgPtr[KernelId];

  /* [cover parentID={5ECB66CC-367E-4a4e-A729-F748544C7AFE}]
  Till the last available Slave Kernel [/cover] */
  for (lKernelCount = (uint8)0U;
       lKernelCount < (uint8)(ADC_KERNELS_PER_SYNGRP - 1U); lKernelCount++)
  {
    lSlaveKernel = lHwUnitCfgPtr->SlaveKernels[lKernelCount];
    /* [cover parentID={8C3BB865-3966-4c58-A020-10AB875FEEDD}]
    Clear slave channel register and result control register [/cover] */
    if (lSlaveKernel != ADC_INVALID_KERNEL_ID)
    {
      /* Get the SFR base address for the current slave kernel */
      lEvadcGroupPtr = &MODULE_EVADC.G[lSlaveKernel];

      /* [cover parentID={8C3BB865-3966-4c58-A020-10AB875FEEDD}]
      Clear slave channel register and result control register [/cover] */
      lEvadcGroupPtr->CHCTR[AnChannelNum].U = (uint32)0U;
      lEvadcGroupPtr->RCR[ResReg].U = (uint32)0U;
    }
  }
}
#endif

#if(ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={C7F76F85-5D91-4c47-98A6-ACE7616B57A7}]      **
**                                                                            **
** Syntax           : static void Adc_lStartSwConversion                      **
**                    (                                                       **
**                      const Adc_GroupCfgType * const GrpPtr,                **
**                      const uint32 KernelId                                 **
**                      const uint8 ReqSrc                                    **
**                    )                                                       **
**                                                                            **
** Description      : This function programs the Request Source Queue and     **
**                    triggers the start of conversion.                       **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different ADC hardware groups             **
**                                                                            **
** Parameters(in)   : GrpPtr  - Pointer to the Group configuration data       **
**                    KernelId  - ADC Group ID of the Kernel                  **
**                    RegSrc - Request source on which to start the group     **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Adc_lStartSwConversion(const Adc_GroupCfgType * const GrpPtr, \
                                   const uint32 KernelId, \
                                   const uint8 ReqSrc)
{
  Ifx_EVADC_G *lEvadcGroupPtr;
  Ifx_EVADC_G_Q *lEvadcQPtr;
  const Adc_GroupDefType *lGrpDefCfgPtr;
  uint32 lConvMode, lRsIntpt;
  uint8 lNoOfChannels, lChloopCount;

  /* Get base address of the kernel SFR */
  lEvadcGroupPtr = &MODULE_EVADC.G[KernelId];
  /* Get base address of the RS SFR */

  lEvadcQPtr = &MODULE_EVADC.G[KernelId].Q[ReqSrc];

  /* Get the group definition configuration */
  lGrpDefCfgPtr = GrpPtr->GroupDefinition;

  /* Flush the RS queue, clear valid flags, before channels are queued up
     for conversion */
  lEvadcQPtr->QMR.U = (((uint32)ADC_ONE_U << IFX_EVADC_G_Q_QMR_FLUSH_OFF) | \
                       ((uint32)ADC_ONE_U << IFX_EVADC_G_Q_QMR_CEV_OFF) | \
                       ((uint32)ADC_ONE_U << IFX_EVADC_G_Q_QMR_CLRV_OFF));

  /* Clear RS event, Channel event and result event flags */
  lEvadcGroupPtr->SEFCLR.U = ((uint32)ADC_ONE_U << ReqSrc);
  lEvadcGroupPtr->CEFCLR.U = (uint32)GrpPtr->ChannelMask;
  lEvadcGroupPtr->REFCLR.U = (uint32)GrpPtr->ResultRegMask;
  /* Clear valid flag for all result registers */
  lEvadcGroupPtr->VFR.U = (uint32)GrpPtr->ResultRegMask;

  /* [cover parentID={3B15D2BA-4BEC-4dc8-875C-E893D21A77C0}]
   [/cover] */
  #if(ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW)
  /* [cover parentID={46197595-FA8C-479d-96E0-65DF05374A6D}]
  Is Group configured with Diagnostic channels [/cover] */
  if(GrpPtr->DiagnosticChGrp == (uint8)ADC_ONE_U)
  {
    /* [cover parentID={2AB0D1A9-757B-467b-8A68-971CA47D7596}]
    Enable Test function for corresponding Kernel of the Group [/cover] */
    Mcal_SetBitAtomic(&(MODULE_EVADC.GLOB.TE.U), (uint8)KernelId, 1, ADC_ONE_U);
  }
  #endif

  /* [cover parentID={3DB53821-0700-41f3-A263-9E02ABB8A6DC}]
  EMUX mode is ON [/cover] */
  #if(ADC_EMUX_ENABLE == STD_ON)
  Adc_ResultRegType lResReg;
  uint8 lEmuxGrp;
  lEmuxGrp = (ADC_ONE_U & (GrpPtr->GrpEmuxCfg));
  /* [cover parentID={444FD4F7-6FA4-43ac-856A-D521B09BE0A5}]
  Group is configured with the EMUX [/cover] */
  if(lEmuxGrp == ADC_ONE_U)
  {
    /* [cover parentID={243E4A2C-DD97-49ad-97DB-06B2286AC1E6}]
    Configure the Wait-For-Read mode when emux feature is enabled [/cover] */
    lResReg = lGrpDefCfgPtr[0U].ResultReg;
    lEvadcGroupPtr->RCR[lResReg].U |= \
                                  ((uint32)ADC_ONE_U<<IFX_EVADC_G_RCR_WFR_OFF);
  }
  #endif

  /* [cover parentID={0BD66C2D-739D-4c99-BE48-4D1809055DE2}]
  Sync conversion is on [/cover] */
  #if (ADC_SYNC_CONV_ENABLE == STD_ON)
  /* [cover parentID={25294F9A-DB76-4c13-9126-26292CD2E973}]
  Sync conversion is configured [/cover] */
  if(GrpPtr->SyncChannelMask != (uint16)0U)
  {
    /* [cover parentID={48E79809-F4CD-4054-A767-195E7F062A3B}]
    Clear Slave events [/cover] */
    Adc_lClearSlaveEvents(GrpPtr, KernelId);
  }
  #endif

  /* [cover parentID={E4005B76-7EC4-45d4-BF4A-AD7090D2D596}]
  Is Group is in continuous conversion mode [/cover] */
  if(GrpPtr->ConvMode == ADC_CONV_MODE_CONTINUOUS)
  {
    /* [cover parentID={5677A0A7-C2CB-4db6-A628-77EA33781828},
    {B9568FC8-DC93-4299-A713-C3BA9A6E7A0D}]Enable REFILL mode of Queue[/cover]*/
    /* If group is in continuous mode, enable REFILL mode of Queue*/
    lConvMode = (uint32)ADC_ONE_U << IFX_EVADC_G_Q_QINR_RF_OFF;
  }
  else
  {
    /* [cover parentID={CA739E58-269B-40d1-8D95-0A913FF6D921}]
    Disable REFILL mode of Queue [/cover] */
    lConvMode = (uint32)0U;
  }

  /* [cover parentID={98B3AC90-C3F8-4cc4-BDB0-AEE919020BDF}]
  Limit Checking is ON [/cover] */
  #if (ADC_ENABLE_LIMIT_CHECK==STD_ON)
  /* [cover parentID={D1D32C5E-4297-4a8e-8E4D-BE8B1A969D35}]
  Is Group a Limit Check  [/cover] */
  if(GrpPtr->LimitCheckGroup == (uint8)ADC_ONE_U)
  {
    /* [cover parentID={5C424B85-B035-4480-A0F2-08530704E7C4}]
    Disable the Request Source interrupt  [/cover] */
    lRsIntpt = (uint32)0U;
  }
  else
  #endif
  {
    /* [cover parentID={AA1887E5-6A08-4de3-BA9C-E36D6AF5B721}]
    Enable the Request Source interrupt [/cover] */
    lRsIntpt = (uint32)ADC_ONE_U << IFX_EVADC_G_Q_QINR_ENSI_OFF;
  }

  lNoOfChannels = GrpPtr->NoOfChannels;
  lChloopCount = (uint8)0U;

  /* Update QCTRL from the configuration directly */
  lEvadcQPtr->QCTRL.U =(uint32)\
              (GrpPtr->GroupQCtrlCfg | ADC_Q_CTRL_WRITE_PROTECT_MSK);

  /* [cover parentID={99B94939-2713-4d7b-BD7A-4773F6730F1F}]
  Till the all channels except last one [/cover] */
  while(lChloopCount < (lNoOfChannels - (uint8)1U))
  {
    /* [cover parentID={F7C9363B-DBEC-4700-BF2E-386088ED434A}]
    Analog channels are pushed to RS queue with refill mode and configured
    Diagnostics feature information [/cover] */
    lEvadcQPtr->QINR.U = (lConvMode |\
                      (uint32)(lGrpDefCfgPtr[lChloopCount].AnalogChannelNo) |\
                      (uint32)(lGrpDefCfgPtr[lChloopCount].AnChDiagnosticsCfg));
    lChloopCount++;
  }

  /* [cover parentID={E748A9F6-6849-4575-BAC3-E434857D37CB}]
  Last Analog channel is  pushed to RS queue with refill mode and configured
  Diagnostics feature information and RS interrupt enabled [/cover] */
  lEvadcQPtr->QINR.U =(lConvMode | lRsIntpt |\
             (uint32)(lGrpDefCfgPtr[lChloopCount].AnalogChannelNo) |\
             (uint32)(lGrpDefCfgPtr[lChloopCount].AnChDiagnosticsCfg));

  /* [cover parentID={0467DF16-33EA-4a46-8E2A-297C450121A4}]
  Priority Implementation is HW-SW Priority [/cover] */
  #if(ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
  /* [cover parentID={D0A1209A-04BA-4c39-8961-830C899875CE}]
  Adjust the Request Source priorities [/cover] */
  Adc_lAdjustRsPriorities(KernelId);
  #endif

  /* [cover parentID={6A8167EC-3955-4f9a-B527-D9B32B057444}]
  Ignore Gating signal and Trigger Start of conversion via SW trigger bit
  [/cover] */
  lEvadcQPtr->QMR.U = ADC_START_SW_TRIG_CONV;
}
#endif

#if (ADC_SYNC_CONV_ENABLE == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={D9FBCCA8-B0F5-4e72-BD96-3465CF3CAE39}]      **
**                                                                            **
** Syntax           : static void Adc_lClearSlaveEvents                       **
**                    (                                                       **
**                      const Adc_GroupCfgType * const GrpPtr,                **
**                      const uint32 KernelId                                 **
**                    )                                                       **
**                                                                            **
** Description      : This function clears the channel and result events for  **
**                    slave kernels of a synchronization group.               **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different ADC hardware groups             **
**                                                                            **
** Parameters(in)   : GrpPtr  - Pointer to the Group configuration data       **
**                    KernelId  - ADC Group ID of the Kernel                  **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Adc_lClearSlaveEvents(const Adc_GroupCfgType * const GrpPtr,\
                                        const uint32 KernelId)
{
  Ifx_EVADC_G *lEvadcGroupPtr;
  const Adc_HwUnitCfgType * lHwUnitCfgPtr;
  uint32 lCoreId;
  uint8 lKernelCount, lSlaveKernel;

  /* Get the core Id from which it is called */
  lCoreId = Mcal_GetCpuIndex();

  /* Get the base address of the kernel configuration */
  lHwUnitCfgPtr = Adc_ConfigPtr->CoreCfgPtr[lCoreId]->HwUnitCfgPtr[KernelId];

  /* [cover parentID={F660BCB1-DC46-432b-8693-C9F1DE7FAC08}]
  Till the last available Kernel [/cover] */
  for (lKernelCount = (uint8)0U;
       lKernelCount < (uint8)(ADC_KERNELS_PER_SYNGRP - 1U); lKernelCount++)
  {
    lSlaveKernel = lHwUnitCfgPtr->SlaveKernels[lKernelCount];
    /* [cover parentID={3E39680D-6101-4e75-9CEA-8EF12B90D350}]
    Valid Slave Kernel [/cover] */
    if (lSlaveKernel != ADC_INVALID_KERNEL_ID)
    {
      /* Get the SFR base address for the current slave kernel */
      lEvadcGroupPtr = &MODULE_EVADC.G[lSlaveKernel];

      /* [cover parentID={BB6AF7A0-E9F1-4ff4-8436-CE386DB28958}]
      Clear Channel event, Result event & Valid flag registers [/cover] */
      lEvadcGroupPtr->CEFCLR.U = (uint32)GrpPtr->SyncChannelMask;
      lEvadcGroupPtr->REFCLR.U = (uint32)GrpPtr->SyncResRegMask;
      /* Clear valid flag for all result registers */
      lEvadcGroupPtr->VFR.U = (uint32)GrpPtr->SyncResRegMask;
    }
  }
}
#endif

#if(ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
/*******************************************************************************
** Traceability: [cover parentID={69524FE9-9C52-40bd-B8D1-DD18CC4E8859}]      **
**                                                                            **
** Syntax           : static void Adc_lAdjustRsPriorities                     **
**                    (                                                       **
**                      const uint32 KernelId                                 **
**                    )                                                       **
**                                                                            **
** Description      : This function checks and (if required) programs the     **
**                    Request Source priorities as per priorities of the      **
**                    groups installed on them.                               **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different ADC hardware groups             **
**                                                                            **
** Parameters(in)   : KernelId  - ADC Group ID of the Kernel                  **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Adc_lAdjustRsPriorities(const uint32 KernelId)
{
  const Adc_GlobalDataType *lKernelDataPtr;
  const Adc_GroupCfgType *lGrpCfgPtr;
  Ifx_EVADC_G *lEvadcGroupPtr;
  uint8 lRsPrios[ADC_REQSRC_COUNT];
  uint8 lGroupPrios[ADC_REQSRC_COUNT];
  uint8 lRsCount;
  uint32 lFinalPrio, lCoreId, lArbPrVal;

  /* Get the core Id from which it is called */
  lCoreId = Mcal_GetCpuIndex();

  /* Get global state data location for the Kernel */
  lKernelDataPtr = Adc_lGetKernelDataAddress(KernelId, lCoreId);

  /* Get the SFR base address for the kernel and the queue */
  lEvadcGroupPtr = &MODULE_EVADC.G[KernelId];

  /* Get priorities (0..255) of installed groups and initialize required RS
   * priorities with 0 */
  /* [cover parentID={8EADC793-2868-420f-BC6C-2C0081F5F7A1}]
  Till the last available RS [/cover] */
  for (lRsCount = (uint8)0U; lRsCount < (uint8)ADC_REQSRC_USED_COUNT; \
       lRsCount++)
  {
    if (lKernelDataPtr->RSData[lRsCount].ActiveGroupId != ADC_INVALID_GROUP_ID)
    {
      /* [cover parentID={997CA6FF-021B-4a5a-ACDD-C7F590FB3F3F}]
      Read the priorities of the groups installed on all RS and Initialize
      required RS priority with 0 [/cover] */
      lGrpCfgPtr = &(Adc_ConfigPtr->CoreCfgPtr[lCoreId]->\
                     HwUnitCfgPtr[KernelId]->GrpCfgPtr\
                     [lKernelDataPtr->RSData[lRsCount].ActiveGroupId]);
      lGroupPrios[lRsCount] = lGrpCfgPtr->GrpPriority;
    }
    else
    {
      lGroupPrios[lRsCount] = (uint8)0U;
    }
    lRsPrios[lRsCount] = (uint8)0U;
  }

  /* Get required RS priorities */
  if (lGroupPrios[0] > lGroupPrios[1])
  {
    lRsPrios[0]++;
  }
  else if (lGroupPrios[1] > lGroupPrios[0])
  {
    lRsPrios[1]++;
  }
  else
  {
    /* Priorities equal - nothing to do */
  }

  if (lGroupPrios[0] > lGroupPrios[2])
  {
    lRsPrios[0]++;
  }
  else if (lGroupPrios[2] > lGroupPrios[0])
  {
    lRsPrios[2]++;
  }
  else
  {
    /* Priorities equal - nothing to do */
  }

  if (lGroupPrios[1] > lGroupPrios[2])
  {
    lRsPrios[1]++;
  }
  else if (lGroupPrios[2] > lGroupPrios[1])
  {
    lRsPrios[2]++;
  }
  else
  {
    /* Priorities equal - nothing to do */
  }

  /* Update RS priorities as per group priorities */
  lFinalPrio = (uint32)
      ((uint32)((uint32)lRsPrios[0] << IFX_EVADC_G_ARBPR_PRIO0_OFF) |
       (uint32)((uint32)lRsPrios[1] << IFX_EVADC_G_ARBPR_PRIO1_OFF) |
       (uint32)((uint32)lRsPrios[2] << IFX_EVADC_G_ARBPR_PRIO2_OFF));
  /* [cover parentID={122DBA7F-0EA6-4410-A515-A7FB88E46364}]
  Priorities needs to change [/cover] */
  if ((lEvadcGroupPtr->ARBPR.U & ADC_ARBPR_PRIO_MSK) != lFinalPrio)
  {
    /* [cover parentID={3E2DA8FB-A8F1-4824-9B74-9263F43D0ADD}]
    Disable aribration of all Request Source [/cover] */
    lArbPrVal = lEvadcGroupPtr->ARBPR.U;
    lArbPrVal &= ~(ADC_ARBPR_ASEN_MSK);
    /* Repeated write to catch corner case where RS is stopped just when a
       conversion requested by it starts */
    lEvadcGroupPtr->ARBPR.U = lArbPrVal;
    lEvadcGroupPtr->ARBPR.U = lArbPrVal;

    /* [cover parentID={880B9B9E-F187-4ce1-8AA5-3947080A6F07}]
    Reset request source priorities [/cover] */
    lArbPrVal &= ~(ADC_ARBPR_PRIO_MSK);
    lEvadcGroupPtr->ARBPR.U = lArbPrVal;

    /* [cover parentID={B88CAD87-07D4-4e41-A78F-5F69D1FEB4C6}]
    Update RS priorities & Re-enable arbitration sources [/cover] */
    lEvadcGroupPtr->ARBPR.U |= lFinalPrio;

    /* [cover parentID={B88CAD87-07D4-4e41-A78F-5F69D1FEB4C6}]
    Update RS priorities & Re-enable arbitration sources [/cover] */
    lEvadcGroupPtr->ARBPR.U |= ADC_ARBPR_ASEN_MSK;
  }
}
#endif

#if(((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW) ||\
 (ADC_ENABLE_QUEUING == STD_ON)) && (ADC_ENABLE_START_STOP_GROUP_API == STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={C98FBF8B-1A59-4301-9718-93EE42597C02}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE void  Adc_lPushToQueue                     **
**                    (                                                       **
**                       const uint32 KernelId                                **
**                       const Adc_GroupType GroupId                          **
**                       const uint32 CoreId                                  **
**                    )                                                       **
**                                                                            **
** Description      :The function places the new requested group in Queue and **
**                   updates the Queue data. If Queue is empty, the requested **
**                   Group conversion is started.                             **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different ADC hardware groups             **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    GroupId - Group ID for the Kernel                       **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Adc_lPushToQueue(const uint32 KernelId,\
                                   const Adc_GroupType GroupId,\
                                   const uint32 CoreId)
{
  Adc_GlobalDataType *lKernelDataPtr;
  const Adc_GroupCfgType *lGrpCfgPtr;
  Adc_GroupType lPushGrpId;

  /*Get the base address of the group configuration */
  lGrpCfgPtr = &(Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[KernelId]->\
                 GrpCfgPtr[GroupId]);
  /* Get global state data location for the Kernel */
  lKernelDataPtr = Adc_lGetKernelDataAddress(KernelId, CoreId);

  /* [cover parentID={36253C22-79F4-4234-9D63-C3FA6D11FADA}]
  Set group status to BUSY, as it is in the queue now [/cover] */
  Adc_lSetGroupStatusBusyAtomic(lKernelDataPtr, GroupId);
  /* [cover parentID={72D10A6C-4917-4e45-8AE0-DB4189F56ADC}]
  Clear Group Result [/cover] */
  Adc_lClrGroupResultAtomic(lKernelDataPtr, GroupId);
  /* [cover parentID={152E7BFD-4263-4b9b-8A40-FF59FE3B2714}]
  Clear result buffer end status [/cover] */
  Adc_lClrResBuffEndStatusAtomic(lKernelDataPtr, GroupId);
  lKernelDataPtr->NumofValidConRes[GroupId] = (Adc_StreamNumSampleType)0U;

  /* [cover parentID={AFD306E3-0C8E-41cb-A9AC-9405C753BA75}]
  Priority Implementation is ON or Sync Conversion is ON [/cover] */
  #if ((ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) ||\
       (ADC_SYNC_CONV_ENABLE == STD_ON))
  /* [cover parentID={056C496C-0258-4850-9441-093F144F6CE9}]
  Sets the running channels and result registers for all slave kernels[/cover]*/
  Adc_lSetRunningChAndResReg(KernelId, lGrpCfgPtr, CoreId);
  #endif

  /* [cover parentID={130F4874-6D82-4952-84E4-A863DD9BAC0C}]
  Priority Mode is ON [/cover] */
  #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
  /* [cover parentID={AB97672D-E6F0-443b-9177-9E3BFFBD9360}]
  Limit Check is ON [/cover] */
  #if (ADC_ENABLE_LIMIT_CHECK==STD_ON)
  /* [cover parentID={A8CED414-54D7-4c80-90E4-58A9CBD2905C}]
  Is Group enabled with limit check [/cover] */
  if ((uint8)ADC_ONE_U == lGrpCfgPtr->LimitCheckGroup)
  {
    /* [cover parentID={213A2567-83A9-4d3d-9F7A-5F02FB4BB902}]
    Set limit check active status flag before installing group into request
    source [/cover] */
    lKernelDataPtr->LimitChkActiveFlag = (uint8)ADC_ONE_U;
  }
  #endif

  /* [cover parentID={877AC307-2D2E-4b1f-99C6-0E7B468624B7}]
  Is the group configured for alias? [/cover] */
  if (ADC_ALIAS_DEFAULT_VALUE != lGrpCfgPtr->AliasChCfg)
  {
    /* [cover parentID={61F649F9-C9D9-41d4-AE12-609B841FE5EB}]
    Set alias active status flag before installing group into request source
    [/cover] */
    lKernelDataPtr->AliasActiveFlag = (uint8)ADC_ONE_U;
  }
  #endif

  /* [cover parentID={79C90658-5176-452a-ACBE-FA604F7A3563}]
  Is Queue Empty [/cover] */
  if(lKernelDataPtr->RSData[lGrpCfgPtr->GrpPriority].PushGroupId == \
        ADC_INVALID_GROUP_ID)
  {
    /* [cover parentID={562269D4-E07B-4e16-8A1D-15AAAC92D817}]
    Push the Current group to queue head  [/cover] */
    lKernelDataPtr->RSData[lGrpCfgPtr->GrpPriority].PushGroupId = GroupId;
    lKernelDataPtr->RSData[lGrpCfgPtr->GrpPriority].PopGroupId = GroupId;
    /* [cover parentID={0C238C74-B8C3-4c5e-BE69-983EC8C07A3A}]
    Schedule from the queue [/cover] */
    Adc_lScheduleFromQueue(KernelId, CoreId, lGrpCfgPtr->GrpPriority);
  }
  else
  {
    /* [cover parentID={CECC13EA-BE16-4ab6-B553-4E1688B591D6}]
    Add group to the end of the queue   [/cover] */
    lPushGrpId = lKernelDataPtr->RSData[lGrpCfgPtr->GrpPriority].PushGroupId;
    lKernelDataPtr->RSData[lGrpCfgPtr->GrpPriority].QueueOfSwGroup[lPushGrpId].\
                                                          NextGroup = GroupId;
    lKernelDataPtr->RSData[lGrpCfgPtr->GrpPriority].QueueOfSwGroup[GroupId].\
                                                   PreviousGroup = lPushGrpId;
    lKernelDataPtr->RSData[lGrpCfgPtr->GrpPriority].PushGroupId = GroupId;
  }
}
#endif

#if(((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW) ||\
 (ADC_ENABLE_QUEUING == STD_ON)) && (ADC_ENABLE_START_STOP_GROUP_API == STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={E6780B17-BD23-4f84-94D0-FE8FA2F3DACC}]      **
**                                                                            **
** Syntax           : static void Adc_lScheduleFromQueue                      **
**                    (                                                       **
**                      const uint32 KernelId                                 **
**                      const uint32 CoreId                                   **
**                      const uint8 ReqSrc                                    **
**                    )                                                       **
**                                                                            **
** Description      :This function Schedules the Group for conversion which   **
**                   is pointed by Pop index.                                 **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different ADC hardware groups             **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    CoreId - Logical CPU core ID                            **
**                    ReqSrc - Request source for which to schedule           **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Adc_lScheduleFromQueue(const uint32 KernelId,\
                                   const uint32 CoreId,\
                                   const uint8 ReqSrc)
{
  Adc_GlobalDataType *lKernelDataPtr;
  const Adc_GroupCfgType *lGrpCfgPtr;
  Adc_GroupType lPopGrpId;

  /* Get global state data location for the Kernel */
  lKernelDataPtr = Adc_lGetKernelDataAddress(KernelId, CoreId);

  /* [cover parentID={AE2D36E5-02EE-4035-AEDF-F39EE63400C9}]
  Get Group to be started at the queue head [/cover] */
  lPopGrpId = lKernelDataPtr->RSData[ReqSrc].PopGroupId;

  /* Get group configuration address */
  lGrpCfgPtr =  &(Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[KernelId]->\
                  GrpCfgPtr[lPopGrpId]);

  /* [cover parentID={F75BEED7-FE7E-4383-AF16-FCF47B05E02E}]
  Update Active Group ID to the Kernel Data [/cover] */
  lKernelDataPtr->RSData[ReqSrc].ActiveGroupId = lPopGrpId;

  /* [cover parentID={4F8F7079-6BB9-4d69-B595-B4E80DD24909}]
  Limit Checking is ON [/cover] */
  #if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
  if((uint8)ADC_ONE_U == lGrpCfgPtr->LimitCheckGroup)
  {
    /* [cover parentID={C0B216C4-D0CF-4e3d-AE90-AE02DFA3ABEB}]
    Update Limit checkgroup ID to the Kernel Data [/cover] */
    lKernelDataPtr->RSData[ReqSrc].ActiveLimitChkCh = \
        lGrpCfgPtr->GroupDefinition[0U].AnalogChannelNo;
  }
  #endif

  /* [cover parentID={EAC48EBC-0DD2-47a7-ADF7-C054B583874A}]
  Prepare Group to Start conversion [/cover] */
  Adc_lPrepareGrpForStart(KernelId, lPopGrpId, CoreId);
  /* Enable ISR servicing for the request source */
  lKernelDataPtr->RSData[ReqSrc].IsrNoServiceFlag = (uint8)0U;
  /* [cover parentID={6056B00A-7C97-4f32-A2DD-E93D4328A6F5}]
  Start Sw Conversion [/cover] */
  Adc_lStartSwConversion(lGrpCfgPtr, KernelId, ReqSrc);
}
#endif

#if((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW) ||\
    (ADC_ENABLE_QUEUING == STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={B759583E-6011-4128-B9D2-A62DA378FC55}]      **
**                                                                            **
** Syntax           : static void Adc_lPopFromQueue                           **
**                    (                                                       **
**                      const uint32 KernelId                                 **
**                      const Adc_GroupType GroupId                           **
**                      const uint32 CoreId                                   **
**                    )                                                       **
**                                                                            **
** Description      :The function removes the requested group from Queue and  **
**                   updates the Queue data. If requested Group is currently  **
**                   converting, the Group is stopped and the next Group in   **
**                   Queue is started for conversion (if any).                **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different ADC hardware groups             **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    GroupId - Group ID for the Kernel                       **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Adc_lPopFromQueue(const uint32 KernelId,\
                              const Adc_GroupType GroupId,\
                              const uint32 CoreId)
{
  Adc_GlobalDataType *lKernelDataPtr;
  Adc_QueueDataType *lQueuePtr;
  const Adc_GroupCfgType *lGrpCfgPtr;
  Adc_GroupType lPopGrpId, lTempPrevGrpId, lTempNextGrpId;

  /* Get global state data location for the Kernel */
  lKernelDataPtr = Adc_lGetKernelDataAddress(KernelId, CoreId);
  /* Get group configuration address */
  lGrpCfgPtr = &(Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[KernelId]->\
                 GrpCfgPtr[GroupId]);
  /* Get Base address of the Queue */
  lQueuePtr =  &(lKernelDataPtr->RSData[lGrpCfgPtr->GrpPriority].
                 QueueOfSwGroup[0U]);

  /* [cover parentID={8EA4C72C-B10F-4f07-AD03-24D2900155BE}]
  Priority Mode is ON [/cover] */
  #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
  /* [cover parentID={74E32476-92C3-4506-8427-80FEBC24FFDE}]
  Limit Check is ON [/cover] */
  #if (ADC_ENABLE_LIMIT_CHECK==STD_ON)
  /* [cover parentID={669F9DD1-B516-423b-A3BD-981566A3B460}]
  Is Group enabled with limit check [/cover] */
  if ((uint8)ADC_ONE_U == lGrpCfgPtr->LimitCheckGroup)
  {
    /* [cover parentID={A9D37CB6-165F-47df-A572-7B872D0FB27B}]
    Reset limit check active status flag [/cover] */
    lKernelDataPtr->LimitChkActiveFlag = (uint8)0U;
  }
  #endif

  /* [cover parentID={98342C15-A61C-42b2-8CE4-FAD15FA35D53}]
  Is the group configured for alias? [/cover] */
  if (ADC_ALIAS_DEFAULT_VALUE != lGrpCfgPtr->AliasChCfg)
  {
    /* [cover parentID={91EF1D06-580E-460e-9814-D5E1B05D0BD0}]
    Reset alias active status flag [/cover] */
    lKernelDataPtr->AliasActiveFlag = (uint8)0U;
  }
  #endif

  /* [cover parentID={411F7C4E-19D8-4286-9E1A-9DBDA0CB8F7F}]
  Is POP element currently in conversion [/cover] */
  if(lKernelDataPtr->RSData[lGrpCfgPtr->GrpPriority].PopGroupId == GroupId)
  {
    /* Disable ISR servicing for the request source */
    lKernelDataPtr->RSData[lGrpCfgPtr->GrpPriority].IsrNoServiceFlag = \
        (uint8)ADC_ONE_U;

    /* [cover parentID={FD692131-80AE-407c-B289-EAE1A6305081}]
    Remove the requested group from queue pop head and place the new group
    at the pop head [/cover] */
    lKernelDataPtr->RSData[lGrpCfgPtr->GrpPriority].PopGroupId = \
        lQueuePtr[GroupId].NextGroup;
    lPopGrpId = lKernelDataPtr->RSData[lGrpCfgPtr->GrpPriority].PopGroupId;
    /* Are there further groups in the queue */
    if(lPopGrpId != ADC_INVALID_GROUP_ID)
    {
      lQueuePtr[GroupId].NextGroup = ADC_INVALID_GROUP_ID;
      lQueuePtr[lPopGrpId].PreviousGroup = ADC_INVALID_GROUP_ID;
    }
    else
    {
      /*Since, there are no further groups in the queue, Queue is marked empty*/
      lKernelDataPtr->RSData[lGrpCfgPtr->GrpPriority].PushGroupId = \
          ADC_INVALID_GROUP_ID;
    }

    /* Stop the ongoing conversion */
    Adc_lStopConvRequest(lGrpCfgPtr, KernelId, lGrpCfgPtr->GrpPriority);

    /* Clear Kernel Data variable */
    Adc_lRemoveActiveGroup(lKernelDataPtr, lGrpCfgPtr, lGrpCfgPtr->GrpPriority);
    /* [cover parentID={988E965B-513A-4fa9-A07A-F635017D865D}]
    Sync Conversion is on or HW Priority Mode [/cover] */
    #if ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW) ||\
         (ADC_SYNC_CONV_ENABLE == STD_ON))
    /* [cover parentID={D8425544-4121-481c-BFBC-4D6683CCAE7B}]
    Clear slaves running channels [/cover] */
    Adc_lClrRunningChAndResReg(KernelId, lGrpCfgPtr, CoreId);
    #endif

    /* [cover parentID={921BB0F9-0EE4-473a-893B-973DDFB393EA}]
    Clear Group status [/cover] */
    Adc_lClrGroupStatusBusyAtomic(lKernelDataPtr, GroupId);
    /* [cover parentID={85F56BC9-E558-4c20-91AE-8C6B96E37DCD}]
    Clear Group Result [/cover] */
    Adc_lClrGroupResultAtomic(lKernelDataPtr, GroupId);
    /* [cover parentID={A77B4E91-A3BC-4cf9-8EF6-01EABC55C886}]
    Clear Result buffer end status [/cover] */
    Adc_lClrResBuffEndStatusAtomic(lKernelDataPtr, GroupId);
    lKernelDataPtr->NumofValidConRes[GroupId] = (Adc_StreamNumSampleType)0U;
    /* [cover parentID={001C0399-2483-453d-9358-FE81ACA4E7AB}]
    Group Notify Capability is ON [/cover] */
    #if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    /* [cover parentID={01E3DC3F-5F76-4f90-8542-FA0E5C085415}]
    Disable group notification [/cover] */
    Adc_lClrGrpNotifAtomic(lKernelDataPtr, GroupId);
    #endif
    /* [cover parentID={F415DAB4-9C61-43bb-B8C4-E44550C2B208}]
    Enable Start Stop Group API is on [/cover] */
    #if(ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
    /* [cover parentID={D2E51118-A381-4e65-A837-9AD5B7EA44F7}]
    Is Queue has more Groups [/cover] */
    if(lKernelDataPtr->RSData[lGrpCfgPtr->GrpPriority].PopGroupId !=\
                                                ADC_INVALID_GROUP_ID)
    {
      /* [cover parentID={887B15F3-3868-4175-BC2B-0BA68B0EE8EB}]
      Schedule next Group from the Queue [/cover] */
      Adc_lScheduleFromQueue(KernelId, CoreId, lGrpCfgPtr->GrpPriority);
    }
    #endif
  }
  else
  { /*Group is in between or at the end of the queue, only Link is removed.
      No need to stop any conversion or clear SFR */
    lTempPrevGrpId = lQueuePtr[GroupId].PreviousGroup;
    lTempNextGrpId = lQueuePtr[GroupId].NextGroup;
    if(lTempPrevGrpId != ADC_INVALID_GROUP_ID)
    {
      lQueuePtr[lTempPrevGrpId].NextGroup = lTempNextGrpId;
    }
    if(lTempNextGrpId != ADC_INVALID_GROUP_ID)
    {
      lQueuePtr[lTempNextGrpId].PreviousGroup = lTempPrevGrpId;
    }
    /* [cover parentID={BADA0420-19B2-4db2-8EEE-D1A802C830A1}]
    Remove the group from in between the queue [/cover] */
    lQueuePtr[GroupId].PreviousGroup = ADC_INVALID_GROUP_ID;
    lQueuePtr[GroupId].NextGroup = ADC_INVALID_GROUP_ID;

    if(lKernelDataPtr->RSData[lGrpCfgPtr->GrpPriority].PushGroupId == GroupId)
    {
      /*If the removed group is last in the queue, update the push group ID*/
      lKernelDataPtr->RSData[lGrpCfgPtr->GrpPriority].PushGroupId =\
                                                    lTempPrevGrpId;
    }

    /* [cover parentID={856702F0-D785-4b87-93E0-A6FFBD6A8D4A}]
    Clear Group status [/cover] */
    Adc_lClrGroupStatusBusyAtomic(lKernelDataPtr, GroupId);
    /* [cover parentID={984643BF-987A-49df-98AB-422945D31F79}]
    Clear Group Result [/cover] */
    Adc_lClrGroupResultAtomic(lKernelDataPtr, GroupId);
    /* [cover parentID={A75C6689-FB1A-4061-9362-6B2AB1BF5250}]
    Clear Result buffer end status [/cover] */
    Adc_lClrResBuffEndStatusAtomic(lKernelDataPtr, GroupId);
    lKernelDataPtr->NumofValidConRes[GroupId] = (Adc_StreamNumSampleType)0U;

    /* [cover parentID={F4388723-F162-434d-9585-5DFC707FBA8A}]
    Sync Conversion is on or Priority Mode not equal to None [/cover] */
    #if ((ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) ||\
         (ADC_SYNC_CONV_ENABLE == STD_ON))
    /* [cover parentID={1F6413A7-51A2-4c25-9AAB-6A1980D48489}]
    Clear slaves running channels [/cover] */
    Adc_lClrRunningChAndResReg(KernelId, lGrpCfgPtr, CoreId);
    #endif

    /* [cover parentID={12D547E5-0AF6-4181-B0E6-3C9B21F669CB}]
    Group Notify Capability is ON [/cover] */
    #if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    /* [cover parentID={E79BD343-2F8B-44fb-B8C4-434FC979C5F8}]
    Disable group notification [/cover] */
    Adc_lClrGrpNotifAtomic(lKernelDataPtr, GroupId);
    #endif
  }
}
#endif

#if((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW) ||\
    (ADC_ENABLE_QUEUING == STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={DE8C896F-5F42-4dd0-96F3-1BDC11F3890C}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE void Adc_lRemoveFromQueue                  **
**                    (                                                       **
**                       const uint32 KernelId                                **
**                       Adc_GlobalDataType * const KernelDataPtr             **
**                       const Adc_GroupType GroupId                          **
**                       const uint32 CoreId                                  **
**                    )                                                       **
**                                                                            **
** Description      :This function Removes the Group from Queue which has     **
**                   just completed the conversion (implicitly stopped)       **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different ADC hardware groups             **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    KernelDataPtr - Pointer to the kernels global data      **
**                                    structure                               **
**                    GroupId - Group ID for the Kernel                       **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Adc_lRemoveFromQueue(const uint32 KernelId,\
    Adc_GlobalDataType * const KernelDataPtr, const Adc_GroupType GroupId,\
    const uint32 CoreId)
{
  Adc_QueueDataType *lQueuePtr;
  const Adc_GroupCfgType *lGrpCfgPtr;
  Adc_GroupType lPopGrpId;

  /* Get group configuration address */
  lGrpCfgPtr = &(Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[KernelId]->\
                 GrpCfgPtr[GroupId]);
  /* Get Base address of the Queue */
  lQueuePtr = &(KernelDataPtr->RSData[lGrpCfgPtr->GrpPriority].\
                QueueOfSwGroup[0U]);

  /*Update the next group in queue as the POP group*/
  KernelDataPtr->RSData[lGrpCfgPtr->GrpPriority].PopGroupId = \
      lQueuePtr[GroupId].NextGroup;
  lPopGrpId = KernelDataPtr->RSData[lGrpCfgPtr->GrpPriority].PopGroupId;
  /* [cover parentID={3131A5DD-0057-4b64-A83D-B87E34E666B9}]
  Any Group is in Queue [/cover] */
  if(lPopGrpId != ADC_INVALID_GROUP_ID)
  {
    /* [cover parentID={8F40F301-FC45-415d-BCE3-64AF6DBFCF32}]
    Remove the group from the queue [/cover] */
    lQueuePtr[GroupId].NextGroup = ADC_INVALID_GROUP_ID;
    lQueuePtr[lPopGrpId].PreviousGroup = ADC_INVALID_GROUP_ID;
  }
  else
  {
    /* [cover parentID={C1DDE6D1-45F8-45e1-8AC6-A0B2BE610D50}]
    Mark queue as empty, since no group in the queue [/cover] */
    KernelDataPtr->RSData[lGrpCfgPtr->GrpPriority].PushGroupId = \
        ADC_INVALID_GROUP_ID;
  }
}
#endif

#if(ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
/*******************************************************************************
** Traceability: [cover parentID={8C84BADE-FAE8-4bdc-881B-18207E7DA9D9}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lGetReqSrcForGrp                 **
**                    (                                                       **
**                       const uint32 KernelId                                **
**                       const Adc_GroupType GroupId                          **
**                       const uint32 CoreId                                  **
**                    )                                                       **
**                                                                            **
** Description      :This function is to find a request source on which a     **
**                   given group could be installed immediately.              **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different ADC hardware groups             **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    GroupId - Group ID for the Kernel                       **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Request source index on which to install the requested  **
**                    group or ADC_INVALID_RS_ID if group cannot be started   **
**                    immediately.                                            **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lGetReqSrcForGrp(const uint32 KernelId,\
                               const Adc_GroupType GroupId, const uint32 CoreId)
{
  const Adc_GlobalDataType *lKernelDataPtr;
  const Adc_GroupCfgType *lGrpCfgPtr;
  Adc_GroupType lGroupId;
  Adc_GroupPriorityType lGroupPriority;
  uint8 lRetVal = ADC_INVALID_RS_ID;
  uint8 lRsCount;

  /* Get priority of group to be started */
  lGroupPriority = Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[KernelId]->\
                                  GrpCfgPtr[GroupId].GrpPriority;

  /* Get global state data location for the Kernel */
  lKernelDataPtr = Adc_lGetKernelDataAddress(KernelId, CoreId);

  /* [cover parentID={448E17D0-336C-4c0e-B240-8BCE50014B94}]
  Till the last available RS [/cover] */
  for (lRsCount = (uint8)0U; lRsCount < (uint8)ADC_REQSRC_USED_COUNT; \
       lRsCount++)
  {
    /* Get current group ID for each RS: */
    lGroupId = lKernelDataPtr->RSData[lRsCount].ActiveGroupId;
    /* [cover parentID={31DEBEE5-619F-458e-9516-2ED521BAE9A6}]
    Is current RS free [/cover] */
    if (ADC_INVALID_GROUP_ID == lGroupId)
    {
      /* [cover parentID={C427020B-9666-4c44-B84B-8D0F074AC9F0}]
      RS is free, group can be started [/cover] */
      lRetVal = lRsCount;
      break;
    }
  }

  /* No RS is free, check if lower priority SW group could be stopped */
  /* [cover parentID={9D37B110-C512-4597-87CC-CB2C8C6FFDD6}]
  No RS is free [/cover] */
  if (lRetVal == ADC_INVALID_RS_ID)
  {
    /* [cover parentID={D5BD428A-5553-435e-8019-56CD2782A024}]
    Till the last available RS [/cover] */
    for (lRsCount = (uint8)0U; lRsCount < (uint8)ADC_REQSRC_USED_COUNT; \
         lRsCount++)
    {
      /* Get current group ID for each RS: */
      lGroupId = lKernelDataPtr->RSData[lRsCount].ActiveGroupId;
      /* Get group configuration address */
      lGrpCfgPtr = &(Adc_ConfigPtr->CoreCfgPtr[CoreId]->\
                     HwUnitCfgPtr[KernelId]->GrpCfgPtr[lGroupId]);

      /* [cover parentID={14AE6EC8-C00A-4b76-9D82-E9AD39CF64A3}]
      Is lower priority SW group is converting [/cover] */
      if ((lGrpCfgPtr->TriggerSource == ADC_TRIGG_SRC_SW) &&
          (lGrpCfgPtr->GrpPriority < lGroupPriority))
      {
        /* SW group with lower priority could be stopped to start the new
           group; continue searching for another SW group with even lower
           priority */
        /* [cover parentID={4F9EA754-DD3D-47ba-8FBE-700BF23884B8}]
        Get index of RS on which to install the requested group [/cover] */
        lRetVal = lRsCount;
        lGroupPriority = lGrpCfgPtr->GrpPriority;
      }
    }
  }

  return(lRetVal);
}
#endif

#if(ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
/*******************************************************************************
** Traceability: [cover parentID={D5FF68A6-EC43-4828-BA2C-DFDDC6F315CC}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE void Adc_lPushToScheduler                  **
**                    (                                                       **
**                       const uint32 KernelId                                **
**                       const Adc_GroupType GroupId                          **
**                       const uint32 CoreId                                  **
**                       const uint8 PriorityBoost                            **
**                    )                                                       **
**                                                                            **
** Description      : This function pushs a group to the ordered SW queue of  **
**                    the scheduler                                           **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different ADC hardware groups             **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    GroupId - Group ID for the Kernel                       **
**                    CoreId - Logical CPU core ID                            **
**                    PriorityBoost - 0: Group is inserted after all the      **
**                                       groups of the same priority (last    **
**                                       amongst same priority)               **
**                                    1: Group is inserted before all the     **
**                                       groups of the same priority (first   **
**                                       amongst same priority)               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Adc_lPushToScheduler(const uint32 KernelId,\
                                       const Adc_GroupType GroupId,\
                                       const uint32 CoreId,\
                                       const uint8 PriorityBoost)
{
  Adc_GroupType lGroupId;
  Adc_GroupType lGroupInsertBefore;
  Adc_GroupType lNextGroup;
  Adc_GlobalDataType *lKernelDataPtr;
  const Adc_GroupCfgType *lGrpCfgPtr;
  const Adc_GroupCfgType *lGrpCfgPtrTmp;

  /* Get global state data location for the Kernel */
  lKernelDataPtr = Adc_lGetKernelDataAddress(KernelId, CoreId);

  /* [cover parentID={C5600984-5F9E-469c-A2F0-764FA785DE11}]
  Queue is Empty [/cover] */
  if (ADC_INVALID_GROUP_ID == lKernelDataPtr->PushGroupId)
  {
    /* [cover parentID={DAD89ED9-0A1B-487b-9783-A9A6F310FEB6}]
    Add group to the head of the queue (first) [/cover] */
    lKernelDataPtr->QueueOfSwGroup[GroupId].NextGroup = ADC_INVALID_GROUP_ID;
    lKernelDataPtr->QueueOfSwGroup[GroupId].PreviousGroup =\
                                                           ADC_INVALID_GROUP_ID;
    lKernelDataPtr->PopGroupId = GroupId;
    lKernelDataPtr->PushGroupId = GroupId;
  }
  else
  {
    /* [cover parentID={45D09BA0-9A64-4235-A9B0-304FC8E3BE70}]
    Read base address for group configuration [/cover] */
    lGrpCfgPtr = &(Adc_ConfigPtr->CoreCfgPtr[CoreId]->\
                   HwUnitCfgPtr[KernelId]->GrpCfgPtr[GroupId]);

    lGroupInsertBefore = ADC_INVALID_GROUP_ID;
    lGroupId = lKernelDataPtr->PushGroupId;

    /* [cover parentID={0861CB1B-B93E-4ff6-8AFB-4362584BD61D}]
    Group is inserted after all the groups of the same priority when
    PriorityBoost is 0 [/cover] */
    if (PriorityBoost == (uint8)0U)
    {
      /* [cover parentID={83E1463B-51FA-49e1-99C2-61A347D306BD}]
      Find location inside the SW queue to insert the new group at (based
      on priority) [/cover] */
      do
      {
        /* Get temporary group configuration address */
        lGrpCfgPtrTmp = &(Adc_ConfigPtr->CoreCfgPtr[CoreId]->\
                          HwUnitCfgPtr[KernelId]->GrpCfgPtr[lGroupId]);
        /* No priority boost: New group is inserted before pending groups
        with the same priority */
        if (lGrpCfgPtrTmp->GrpPriority >= lGrpCfgPtr->GrpPriority)
        {
          lGroupInsertBefore = lGroupId;
        }
        else
        {
          lGroupId = lKernelDataPtr->QueueOfSwGroup[lGroupId].PreviousGroup;
        }
      } while ((lGroupId != ADC_INVALID_GROUP_ID) && \
               (lGroupInsertBefore == ADC_INVALID_GROUP_ID));
    }
    /* [cover parentID={DFCFE545-1EC1-4518-9F37-D6D65550360D}]
    Group is inserted at the head of the queue when PriorityBoost is 1, since it
    was just removed from being active, it has to be next executed when Request
    source is free or Is the requested group is having highest priority among
    all the groups when PriorityBoost is 0 [/cover] */
    if (ADC_INVALID_GROUP_ID == lGroupInsertBefore)
    {
      /* [cover parentID={3AC4F86E-9AAC-4f22-AEAC-8BBB523B1366}]
      Insert group at the head of the queue [/cover] */
      lKernelDataPtr->QueueOfSwGroup[lKernelDataPtr->PopGroupId].PreviousGroup=\
                                                                        GroupId;
      lKernelDataPtr->QueueOfSwGroup[GroupId].NextGroup =\
                                                     lKernelDataPtr->PopGroupId;
      lKernelDataPtr->QueueOfSwGroup[GroupId].PreviousGroup =\
                                                           ADC_INVALID_GROUP_ID;
      lKernelDataPtr->PopGroupId = GroupId;
    }
    else
    {
      /* [cover parentID={4EC83D48-814C-4d10-9EE6-9BEF79C7A53F}]
      Insert group before the Group Inserted earlier [/cover] */
      lNextGroup = lKernelDataPtr->QueueOfSwGroup[lGroupInsertBefore].\
                                                                      NextGroup;
      lKernelDataPtr->QueueOfSwGroup[lGroupInsertBefore].NextGroup = GroupId;
      lKernelDataPtr->QueueOfSwGroup[GroupId].NextGroup = lNextGroup;
      lKernelDataPtr->QueueOfSwGroup[GroupId].PreviousGroup =lGroupInsertBefore;
      if (lNextGroup == ADC_INVALID_GROUP_ID)
      {
        lKernelDataPtr->PushGroupId = GroupId;
      }
      else
      {
        lKernelDataPtr->QueueOfSwGroup[lNextGroup].PreviousGroup = GroupId;
      }
    }
  }
}
#endif

#if((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)&&\
    (ADC_ENABLE_START_STOP_GROUP_API == STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={3CAB6D0C-BC19-4f76-80B9-9D77E7BF7EBE}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE Adc_GroupType Adc_lPopFromScheduler        **
**                    (                                                       **
**                       const uint32 KernelId                                **
**                       const uint32 CoreId                                  **
**                    )                                                       **
**                                                                            **
** Description      : This function pops the highest priority group from the  **
**                    ordered SW queue of the scheduler                       **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different ADC hardware groups             **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : GroupId of popped group or ADC_INVALID_GROUP_ID if SW   **
**                    queue is empty                                          **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Adc_GroupType Adc_lPopFromScheduler(const uint32 KernelId,\
                                                 const uint32 CoreId)
{
  Adc_GroupType lGroupId;
  Adc_GroupType lNextGroup;
  Adc_GlobalDataType *lKernelDataPtr;

  /* Get global state data location for the Kernel */
  lKernelDataPtr = Adc_lGetKernelDataAddress(KernelId, CoreId);
  lGroupId = lKernelDataPtr->PopGroupId;
  /* [cover parentID={173869DF-6DD9-4594-85C5-0D5EF3F1AF8E}]
  Are there any groups in SW queue [/cover] */
  if (lGroupId != ADC_INVALID_GROUP_ID)
  {
    /* [cover parentID={831919A5-5D32-4a01-8D6C-471B6321DCB4}]
    Group present in the queue is the last one [/cover] */
    if (lKernelDataPtr->PushGroupId == lGroupId)
    {
      /* [cover parentID={96C0C517-9F75-4590-A144-7026EA40C0B8}]
      Clear the group and return the last group ID in queue [/cover] */
      lKernelDataPtr->PopGroupId = ADC_INVALID_GROUP_ID;
      lKernelDataPtr->PushGroupId = ADC_INVALID_GROUP_ID;
    }
    else
    {
      /* [cover parentID={029D8F0F-9E0C-4680-8F39-AA26AA5F47CB}]
      Remove the 1st group ID from the queue. Next element is now at the head
      of the queue [/cover] */
      lNextGroup = lKernelDataPtr->QueueOfSwGroup[lGroupId].NextGroup;
      lKernelDataPtr->PopGroupId = lNextGroup;
      lKernelDataPtr->QueueOfSwGroup[lNextGroup].PreviousGroup =\
                                                           ADC_INVALID_GROUP_ID;
      lKernelDataPtr->QueueOfSwGroup[lGroupId].NextGroup =\
                                                           ADC_INVALID_GROUP_ID;
    }
  }

  return(lGroupId);
}
#endif

#if(ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
/*******************************************************************************
** Traceability: [cover parentID={6C9435D4-FE05-43fc-BBDE-A73FA61C0313}]      **
**                                                                            **
** Syntax           : static void  Adc_lSchedulerOnStart                      **
**                    (                                                       **
**                       const uint32 KernelId                                **
**                       const Adc_GroupType GroupId                          **
**                       const uint32 CoreId                                  **
**                    )                                                       **
**                                                                            **
** Description      :The function marks the new requested group busy. If the  **
**                   group is SW triggered, it is either immediately          **
**                   installed on a request source or just marked busy for    **
**                   later conversion. HW triggered groups are always started **
**                   immediately.                                             **
**                   If no request source is currently free, but a SW         **
**                   triggered group with lower priority than the new group   **
**                   is executing, the lower priority group is temporarily    **
**                   stopped.                                                 **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different ADC hardware groups             **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    GroupId - Group ID for the Kernel                       **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Adc_lSchedulerOnStart(const uint32 KernelId,\
                                  const Adc_GroupType GroupId,\
                                  const uint32 CoreId)
{
  Adc_GlobalDataType *lKernelDataPtr;
  const Adc_GroupCfgType *lGrpCfgPtr;
  uint8 lReqSrc;

  /*Get the base address of the group configuration */
  lGrpCfgPtr = &(Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[KernelId]->\
                 GrpCfgPtr[GroupId]);
  /* Get global state data location for the Kernel */
  lKernelDataPtr = Adc_lGetKernelDataAddress(KernelId, CoreId);

  /* [cover parentID={49108012-1036-41c5-AD6F-E4E210F90AEC}]
  Set group status to BUSY, as it is either started immediately or pushed
  to the queue now [/cover] */
  Adc_lSetGroupStatusBusyAtomic(lKernelDataPtr, GroupId);
  /* [cover parentID={909B7A49-E798-4923-9C08-445F6DED7CFA}]
  Clear group result [/cover] */
  Adc_lClrGroupResultAtomic(lKernelDataPtr, GroupId);
  /* [cover parentID={52EB4A47-ED77-45bb-A014-DA0B36127E17}]
  Clear result buffer end status [/cover] */
  Adc_lClrResBuffEndStatusAtomic(lKernelDataPtr, GroupId);
  lKernelDataPtr->NumofValidConRes[GroupId] = (Adc_StreamNumSampleType)0U;

  /* Set flags for used channels and result registers */
  Adc_lSetRunningChAndResReg(KernelId, lGrpCfgPtr, CoreId);

  /* [cover parentID={80EDB030-3486-4e9a-BDCE-19AD9363B1B4}]
  Limit Check is ON [/cover] */
  #if (ADC_ENABLE_LIMIT_CHECK==STD_ON)
  /* [cover parentID={DE3D8E08-F822-4b1c-85D5-06C8C83C6772}]
  Is Group enabled with limit check [/cover] */
  if ((uint8)ADC_ONE_U == lGrpCfgPtr->LimitCheckGroup)
  {
    /* [cover parentID={F3C1B4F1-7EF4-43c2-A906-683D0AE90420}]
    Set limit check active status flag before installing group into request
    source [/cover] */
    lKernelDataPtr->LimitChkActiveFlag = (uint8)ADC_ONE_U;
  }
  #endif

  /* [cover parentID={4A404036-18BA-47d7-9730-ED8CC172CEA5}]
  Is the group configured for alias? [/cover] */
  if (ADC_ALIAS_DEFAULT_VALUE != lGrpCfgPtr->AliasChCfg)
  {
    /* [cover parentID={4CCC4FE2-3A59-49c9-A2A7-1914AB734CA3}]
    Set alias active status flag before installing group into request source
    [/cover] */
    lKernelDataPtr->AliasActiveFlag = (uint8)ADC_ONE_U;
  }

  /* [cover parentID={3CEA4C12-B992-4f52-B681-244E373BEFCB}]
  Read request source to start the group immediately [/cover] */
  lReqSrc = Adc_lGetReqSrcForGrp(KernelId, GroupId, CoreId);

  /* [cover parentID={29454C6B-6AF0-448d-855F-C63FAE8CBA6F}]
  Is any RS free [/cover] */
  if(lReqSrc != ADC_INVALID_RS_ID)
  {
    /* [cover parentID={228250F7-043B-40a8-89DD-88A3EBB16032}]
    Is any group currently running on the RS [/cover] */
    if(lKernelDataPtr->RSData[lReqSrc].ActiveGroupId != ADC_INVALID_GROUP_ID)
    {
      Adc_GroupType lStopGrpId;
      const Adc_GroupCfgType *lStopGrpCfgPtr;

      /* Get configuration base address of group to be stopped */
      lStopGrpId = lKernelDataPtr->RSData[lReqSrc].ActiveGroupId;
      lStopGrpCfgPtr = &(Adc_ConfigPtr->CoreCfgPtr[CoreId]->\
                         HwUnitCfgPtr[KernelId]->GrpCfgPtr[lStopGrpId]);

      /* Disable ISR servicing for the request source */
      lKernelDataPtr->RSData[lReqSrc].IsrNoServiceFlag = (uint8)ADC_ONE_U;

      /* [cover parentID={488E4648-19CB-46e1-9CC4-60AF89DBB88B}]
      Stop the ongoing conversion [/cover] */
      Adc_lStopConvRequest(lStopGrpCfgPtr, KernelId, lReqSrc);

      /*Assign Invalid Group ID to active group variable*/
      lKernelDataPtr->RSData[lReqSrc].ActiveGroupId = ADC_INVALID_GROUP_ID;

      /* [cover parentID={26F83428-60C1-4be9-B9F4-D177DB333D30}]
      Limit Check is on [/cover] */
      #if (ADC_ENABLE_LIMIT_CHECK==STD_ON)
      if((uint8)ADC_ONE_U == lStopGrpCfgPtr->LimitCheckGroup)
      {
        /* [cover parentID={5DBD00CC-51E6-4e43-9FCE-857A51018F89}]
        Set active limit check channel ID to INVALID [/cover] */
        lKernelDataPtr->RSData[lReqSrc].ActiveLimitChkCh = \
            ADC_INVALID_CHANNEL_ID;
      }
      #endif

      /* [cover parentID={1126D70D-73CE-4c9e-AF8A-8286AFE20083}]
      Push group to scheduler queue [/cover] */
      Adc_lPushToScheduler(KernelId, lStopGrpId, CoreId, (uint8)1U);
    }

    /* Start the group conversion */

    /* Set the active group variable*/
    lKernelDataPtr->RSData[lReqSrc].ActiveGroupId = GroupId;

    /* [cover parentID={539B39F2-9E04-4bcb-87AD-016A96DBF80E}]
    Limit Check is on [/cover] */
    #if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
    if((uint8)ADC_ONE_U == lGrpCfgPtr->LimitCheckGroup)
    {
      /* [cover parentID={8C8A0F88-3349-4f9a-B34E-C2BF0DFF1666}]
      Set active limit check channel ID [/cover] */
      lKernelDataPtr->RSData[lReqSrc].ActiveLimitChkCh = \
          lGrpCfgPtr->GroupDefinition[0U].AnalogChannelNo;
    }
    #endif

    /* Prepare channels and result registers */
    Adc_lPrepareGrpForStart(KernelId, GroupId, CoreId);
    /* Enable ISR servicing for the request source */
    lKernelDataPtr->RSData[lReqSrc].IsrNoServiceFlag = (uint8)0U;

    /* [cover parentID={90C86616-0857-4fb6-B463-007CBCCA4CC0}]
    Trigger Source is SW [/cover] */
    if (lGrpCfgPtr->TriggerSource == ADC_TRIGG_SRC_SW)
    {
      /* [cover parentID={F934A372-288E-41a0-86A7-C6458FA02003}]
      Enable Start Stop Group API is on [/cover] */
      #if(ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
      /* [cover parentID={63AA1399-4853-4f4f-8E26-DE9AAB2E0FA6}]
      Start conversion of the group [/cover] */
      Adc_lStartSwConversion(lGrpCfgPtr, KernelId, lReqSrc);
      #endif
    }
    else
    {
      /* [cover parentID={42D76FFC-5704-4aec-B80F-9E4968054173}]
      HW Trigger API is on [/cover] */
      #if (ADC_HW_TRIGGER_API == STD_ON)
      /* [cover parentID={FA7E8BE8-2102-4548-A707-985FBB3CDFC0}]
      Start conversion of the group [/cover] */
      Adc_lStartHwConversion(lGrpCfgPtr, KernelId, lReqSrc);
      #endif
    }
  }
  else
  {
    /* Note: DET check prevents this path being executed for HW triggered
             groups. */

    /* Group cannot be started immediately, keep it busy for later conversion,
    and push group to scheduler queue */
    /* [cover parentID={FDD789A4-1A0D-429e-BB9F-A64BACD8030F}]
    Push group to scheduler queue [/cover] */
    Adc_lPushToScheduler(KernelId, GroupId, CoreId, 0U);
  }
}
#endif

#if((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)&&\
    (ADC_ENABLE_START_STOP_GROUP_API == STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={3E8DCCFC-991B-40cd-B9E3-C7952A3BD815}]      **
**                                                                            **
** Syntax           : static void Adc_lScheduleNext                           **
**                    (                                                       **
**                      const uint32 KernelId                                 **
**                      const uint32 CoreId                                   **
**                      const uint8 ReqSrc                                    **
**                    )                                                       **
**                                                                            **
** Description      :This function Schedules the pending Group for conversion **
**                   which has highest priority.                              **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different ADC hardware groups             **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    CoreId - Logical CPU core ID                            **
**                    ReqSrc - Request source for which to schedule           **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Adc_lScheduleNext(const uint32 KernelId,\
                              const uint32 CoreId,\
                              const uint8 ReqSrc)
{
  Adc_GlobalDataType *lKernelDataPtr;
  const Adc_GroupCfgType *lGrpCfgPtr;
  Adc_GroupType lGroupId;

  /* Get global state data location for the Kernel */
  lKernelDataPtr = Adc_lGetKernelDataAddress(KernelId, CoreId);

  /* [cover parentID={23FB90EF-8CAD-4bcc-8865-4C64E4118244}]
  Read next group to be converted [/cover] */
  lGroupId = Adc_lPopFromScheduler(KernelId, CoreId);

  /* [cover parentID={4AD4B8F6-B2B9-4560-ACA7-F8893E53BD56}]
  Valid Group ID [/cover] */
  if (lGroupId != ADC_INVALID_GROUP_ID)
  {
    /* Get group configuration address */
    lGrpCfgPtr =  &(Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[KernelId]->\
                    GrpCfgPtr[lGroupId]);

    /* Set the active group variable*/
    lKernelDataPtr->RSData[ReqSrc].ActiveGroupId = lGroupId;

    /* [cover parentID={549CCED3-7A27-43b0-B2D1-F85AF8AC8A8D}]
    Limit Check is on [/cover] */
    #if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
    if((uint8)ADC_ONE_U == lGrpCfgPtr->LimitCheckGroup)
    {
      /* [cover parentID={D955DA08-6803-4f66-A1B3-EBBBB4DBBC2A}]
      Set limit check Group [/cover] */
      lKernelDataPtr->RSData[ReqSrc].ActiveLimitChkCh = \
          lGrpCfgPtr->GroupDefinition[0U].AnalogChannelNo;
    }
    #endif

    /* [cover parentID={754D8F47-2294-42ea-A3DE-ED343119A35A}]
    Prepare channels and result registers [/cover] */
    Adc_lPrepareGrpForStart(KernelId, lGroupId, CoreId);
    /* Enable ISR servicing for the request source */
    lKernelDataPtr->RSData[ReqSrc].IsrNoServiceFlag = (uint8)0U;
    /* [cover parentID={AE2D36E5-02EE-4035-AEDF-F39EE63400C9}]
    Start conversion for group at the queue head  [/cover] */
    /* Prepare HW RS queue and trigger the SW conversion */
    Adc_lStartSwConversion(lGrpCfgPtr, KernelId, ReqSrc);
  }
}
#endif

#if(ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
/*******************************************************************************
** Traceability: [cover parentID={1D74134A-C83C-4883-82C4-58649FBB060D}]      **
**                                                                            **
** Syntax           : static void Adc_lSchedulerOnStop                        **
**                    (                                                       **
**                      const uint32 KernelId                                 **
**                      const Adc_GroupType GroupId                           **
**                      const uint32 CoreId                                   **
**                    )                                                       **
**                                                                            **
** Description      : Group passed to this function is stopped if it is       **
**                    currently converting then the next group in the queue   **
**                    is started (if any). If the group is not converting,it  **
**                    is removed from the queue of pending groups.            **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different ADC hardware groups             **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    GroupId - Group ID for the Kernel                       **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Adc_lSchedulerOnStop(const uint32 KernelId,\
                                 const Adc_GroupType GroupId,\
                                 const uint32 CoreId)
{
  Adc_GlobalDataType *lKernelDataPtr;
  Adc_QueueDataType *lQueuePtr;
  const Adc_GroupCfgType *lGrpCfgPtr;
  Adc_GroupType lTempPrevGrpId, lTempNextGrpId;

  uint8 lGrpReqSrc;

  /* Get global state data location for the Kernel */
  lKernelDataPtr = Adc_lGetKernelDataAddress(KernelId, CoreId);
  /* Get group configuration address */
  lGrpCfgPtr = &(Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[KernelId]->\
                 GrpCfgPtr[GroupId]);

  /* [cover parentID={4A551680-4ABF-472a-9697-5E632DA1FE32}]
  Read request source on which group is installed [/cover] */
  lGrpReqSrc = Adc_lGetGrpReqSrc(KernelId, GroupId, CoreId);

  /* [cover parentID={3061E726-4F93-40a3-B118-3DEB71D4CF5B}]
  Limit Check is ON [/cover] */
  #if (ADC_ENABLE_LIMIT_CHECK==STD_ON)
  /* [cover parentID={FE0E95AB-407C-489d-B5DD-F6506509E05E}]
  Is Group enabled with limit check [/cover] */
  if ((uint8)ADC_ONE_U == lGrpCfgPtr->LimitCheckGroup)
  {
    /* [cover parentID={6982EB8A-00EC-43f1-8225-8B424557E6D3}]
    Reset limit check active status flag [/cover] */
    lKernelDataPtr->LimitChkActiveFlag = (uint8)0U;
  }
  #endif

  /* [cover parentID={2BB04F98-7582-4f97-AB78-83222ED4C39D}]
  Is the group configured for alias? [/cover] */
  if (ADC_ALIAS_DEFAULT_VALUE != lGrpCfgPtr->AliasChCfg)
  {
    /* [cover parentID={F13285F8-C7EE-4a2a-88F0-7FFF69DB08D7}]
    Reset alias active status flag [/cover] */
    lKernelDataPtr->AliasActiveFlag = (uint8)0U;
  }

  /* [cover parentID={071663DB-3625-4ae7-8121-45DE5D7F82F3}]
  Group is currently converting [/cover] */
  if (lGrpReqSrc != ADC_INVALID_RS_ID)
  {
    /* Disable ISR servicing for the request source */
    lKernelDataPtr->RSData[lGrpReqSrc].IsrNoServiceFlag = (uint8)ADC_ONE_U;

    /* [cover parentID={E0B4DA57-90CD-4138-A3ED-8C320FD81A52}]
    Stop on going conversions [/cover] */
    Adc_lStopConvRequest(lGrpCfgPtr, KernelId, lGrpReqSrc);

    /* Clear Kernel Data variable */
    Adc_lRemoveActiveGroup(lKernelDataPtr, lGrpCfgPtr, lGrpReqSrc);
    Adc_lClrRunningChAndResReg(KernelId, lGrpCfgPtr, CoreId);

    /* [cover parentID={B47AFF5B-6E71-466e-8E82-D09999AC9D15}]
    Clear Group busy status [/cover] */
    Adc_lClrGroupStatusBusyAtomic(lKernelDataPtr, GroupId);
    /* [cover parentID={D46A70A2-C3D6-435f-9EEE-E5C0F90F736F}]
    Clear Group result [/cover] */
    Adc_lClrGroupResultAtomic(lKernelDataPtr, GroupId);
    /* [cover parentID={88D3C886-4625-4493-8A95-62A0FC84C2AD}]
    Clear result buffer end status [/cover] */
    Adc_lClrResBuffEndStatusAtomic(lKernelDataPtr, GroupId);
    lKernelDataPtr->NumofValidConRes[GroupId] = (Adc_StreamNumSampleType)0U;
    /* [cover parentID={DF9C77A9-660F-4b00-9C3E-723D28076B47}]
    Notification is on [/cover] */
    #if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    /* [cover parentID={E49E8588-C832-4a63-85AE-D659A296298F}]
    Disable group notification [/cover] */
    Adc_lClrGrpNotifAtomic(lKernelDataPtr, GroupId);
    #endif

    /* [cover parentID={8195DE57-8D88-4d30-B818-71016E77A60F}]
    Enable Start Stop Group API is on [/cover] */
    #if(ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
    /* [cover parentID={4413FCBE-D3D7-4819-A97C-13DDFD407D23}]
    If more groups are present in the queue,Start the next group in the queue
    [/cover] */
    Adc_lScheduleNext(KernelId, CoreId, lGrpReqSrc);
    #endif
  }
  else
  { /*Group is in the queue of pending groups. Only Link is removed.
      No need to stop any conversion or clear SFR */

    /* Get Base address of the Queue */
    lQueuePtr =  &(lKernelDataPtr->QueueOfSwGroup[0U]);
    lTempPrevGrpId = lQueuePtr[GroupId].PreviousGroup;
    lTempNextGrpId = lQueuePtr[GroupId].NextGroup;
    if(lTempPrevGrpId != ADC_INVALID_GROUP_ID)
    {
      lQueuePtr[lTempPrevGrpId].NextGroup = lTempNextGrpId;
    }
    if(lTempNextGrpId != ADC_INVALID_GROUP_ID)
    {
      lQueuePtr[lTempNextGrpId].PreviousGroup = lTempPrevGrpId;
    }
    /* [cover parentID={9149D6A9-9CCF-4271-AEC0-CADBC96DADD2}]
    Remove the group from the queue of pending groups [/cover] */
    lQueuePtr[GroupId].PreviousGroup = ADC_INVALID_GROUP_ID;
    lQueuePtr[GroupId].NextGroup = ADC_INVALID_GROUP_ID;

    if(lKernelDataPtr->PushGroupId == GroupId)
    {
      /*If the removed group is last in the queue, update the push group ID*/
      lKernelDataPtr->PushGroupId = lTempPrevGrpId;
    }
    if(lKernelDataPtr->PopGroupId == GroupId)
    {
      /*If the removed group is first in the queue, update the pop group ID*/
      lKernelDataPtr->PopGroupId = lTempNextGrpId;
    }

    /* [cover parentID={39FBB5FE-1AD4-4551-AEA6-28DBC6FA6707}]
    Clear Group busy status [/cover] */
    Adc_lClrGroupStatusBusyAtomic(lKernelDataPtr, GroupId);
    /* [cover parentID={44103670-97DC-430b-AEC2-B7D55F5080B0}]
    Clear Group result [/cover] */
    Adc_lClrGroupResultAtomic(lKernelDataPtr, GroupId);
    /* [cover parentID={94FEF9BC-B68B-4805-9024-B14F3A9F2600}]
    Clear result buffer end status [/cover] */
    Adc_lClrResBuffEndStatusAtomic(lKernelDataPtr, GroupId);
    lKernelDataPtr->NumofValidConRes[GroupId] = (Adc_StreamNumSampleType)0U;

    /* [cover parentID={A8A0A0BD-CF19-4404-A0A2-4EA2D46D5095}]
    Clear flags for used channels and result registers [/cover] */
    Adc_lClrRunningChAndResReg(KernelId, lGrpCfgPtr, CoreId);

    /* [cover parentID={7EF850E6-C912-49fb-8980-FA05C83DA660}]
    Notification is on [/cover] */
    #if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    /* [cover parentID={AF952EF1-AF84-4cd1-AC0D-4EC58B6A848A}]
    Disable group notification [/cover] */
    Adc_lClrGrpNotifAtomic(lKernelDataPtr, GroupId);
    #endif
  }
}
#endif

/*******************************************************************************
** Traceability: [cover parentID={7EA698D7-6BF5-4745-BB0E-73B717FC4E38}]      **
**                                                                            **
** Syntax           : static void Adc_lStopConvRequest                        **
**                    (                                                       **
**                      const Adc_GroupCfgType * const GrpPtr                 **
**                      const uint32 KernelId                                 **
**                      const uint8 ReqSrc                                    **
**                    )                                                       **
**                                                                            **
** Description      : This function  stops the on-going Adc group conversion  **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different ADC hardware groups             **
**                                                                            **
** Parameters(in)   : GrpPtr  - Pointer to the Group configuration data       **
**                    KernelId  - ADC Group ID of the Kernel                  **
**                    ReqSrc - Request Source of the Group                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Adc_lStopConvRequest(const Adc_GroupCfgType *const GrpPtr,\
                                 const uint32 KernelId,\
                                 const uint8 ReqSrc)
{
  Ifx_EVADC_G_Q *lEvadcQPtr;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
  this MISRA rule. Union usage is required to access SFR data type and implement
  efficiently for clearing of pending service requrest in Interrupt control
  register */
  volatile Ifx_SRC_SRCR *lVadcGrpSrcPtr;

  /* Read the base address of group specific Queue register */
  lEvadcQPtr = &MODULE_EVADC.G[KernelId].Q[ReqSrc];

  /* Disable the GATE signal of the Queue */
  lEvadcQPtr->QMR.B.ENGT = 0U;

  /* Flush the RS queue and clear the valid flags  */
  lEvadcQPtr->QMR.U = (((uint32)ADC_ONE_U << IFX_EVADC_G_Q_QMR_FLUSH_OFF) | \
                       ((uint32)ADC_ONE_U << IFX_EVADC_G_Q_QMR_CEV_OFF) | \
                       ((uint32)ADC_ONE_U << IFX_EVADC_G_Q_QMR_CLRV_OFF));

  /* [cover parentID={36E5198D-8F7F-4329-91C6-A7D68C1D35F6}]
  HW Trigger API Enabled [/cover] */
  #if (ADC_HW_TRIGGER_API == STD_ON)
  /* [cover parentID={EA6E802B-9C42-4f6d-AA13-FDE7ED627331}]
  Is the Group HW Trigger [/cover] */
  if(ADC_TRIGG_SRC_HW == GrpPtr->TriggerSource)
  {
    /* [cover parentID={BD628C24-6691-415e-8D30-7C4933CE1488}]
    Request timer configured [/cover] */
    if (GrpPtr->GrpReqTmCfg != (uint32)0U)
    {
      /* [cover parentID={A9B6D9AB-58F5-47bf-8766-933B464CADF4}]
      Reset request timer [/cover] */
      lEvadcQPtr->REQTM.U = ADC_REQTM_RESET_VALUE;
    }
    else
    {
      /* [cover parentID={1FF9998C-EB39-4462-89F2-A8CF797B3029}]
      Reset GTM/ERU Channel [/cover] */
      Adc_lResetHwTrigger(GrpPtr, (uint8)ADC_RUNTIME);
    }
  }
  #endif
  /* Wait for stop conversion required */
  /* [cover parentID={B850A7FC-9500-4084-AF7D-222F9B0A975B}]
  ADC Maximum Channel Conversion Time is greater than ZERO [/cover] */
  #if (ADC_MAX_CH_CONV_TIME > 0U)
  /* Wait for the ongoing conversion to stop */
  uint32 lWaitCount, lCurrentRS, lBusyFlag;
  const Ifx_EVADC_G *lEvadcGroupPtr;

  /* Get the base address of the Kernel SFR */
  lEvadcGroupPtr = &MODULE_EVADC.G[KernelId];

  lWaitCount = (uint32)ADC_MAX_CH_CONV_TIME;

  /* Get the currently converting RS */
  lCurrentRS = (uint32)lEvadcGroupPtr->ARBCFG.B.CSRC;
  /* Get the Converter Busy flag */
  lBusyFlag = (uint32)lEvadcGroupPtr->ARBCFG.B.BUSY;

  /*If BUSY flag is 1, CSRC bit indicates the current converting RS ,
  If Busy flag is 0, CSRC bit indicates the last converted RS,
  If BUSY flag is 1, while CSRC points to RS of the stopped AdcGroup,
  then the stopped conversion has not yet completed */
  /* [cover parentID={00471AC0-397D-4c8f-B8F4-18674792787E}]
  Till WaitCount Expired or Busy flag is Cleared [/cover] */
  while((lBusyFlag == (uint32)ADC_ONE_U) && (lCurrentRS == ReqSrc) && \
        (lWaitCount > (uint32)0U))
  {
    /* [cover parentID={CC1EB2BF-538D-443e-B2B3-A77864362F64}]
    Decrement the WaitCount & Get the Converter busy flag [/cover] */
    lWaitCount--;
    /* Get the currently converting RS */
    lCurrentRS = (uint32)lEvadcGroupPtr->ARBCFG.B.CSRC;
    /* Get the Converter Busy flag */
    lBusyFlag = (uint32)lEvadcGroupPtr->ARBCFG.B.BUSY;
  }
  /* [cover parentID={1AE6114A-0A1A-4185-8A6C-84E3D842313C}]
  Production error Reporting is ON [/cover] */
  #if (ADC_CONV_STOP_TIME_DEM_NOTIF == ADC_ENABLE_DEM_REPORT)
  /* [cover parentID={974BC09F-E4AC-40f5-95A7-2182F1C3D65B}]
  Is WaitCount Expired [/cover] */
  if(lWaitCount != (uint32)0U)
  {
    /* [cover parentID={FE02B674-750A-49fc-B09D-02EDD47704F8}]
    Report Production error PASS [/cover] */
    Adc_lReportDemError(ADC_E_CONV_STOP_TIME_FAILURE,DEM_EVENT_STATUS_PASSED);
  }
  else
  {
    /* [cover parentID={93E3CC99-A3E4-4de9-99E2-21EF7864AC87}]
    Report Production error FAIL [/cover] */
    /* Failure of Production error raised, when stop count reaches 0 */
    Adc_lReportDemError(ADC_E_CONV_STOP_TIME_FAILURE,DEM_EVENT_STATUS_FAILED);
  }
  #endif
  #endif

  /* Read the base address of group specific Service request control register */
  lVadcGrpSrcPtr = &(MODULE_SRC.VADC.G[KernelId].SR0);

  /* [cover parentID={97B237ED-8845-4f09-8879-DAB6F41A5FB5}]
  Limit check is ON [/cover] */
  #if (ADC_ENABLE_LIMIT_CHECK==STD_ON)
  /* [cover parentID={648374CC-53C3-4812-93D0-F8EE3C7571B8}]
  Is group enabled with limit check [/cover] */
  if(GrpPtr->LimitCheckGroup == (uint8)ADC_ONE_U)
  {
    /* Address of Service request control register for Limit check group */
    /* MISRA2012_RULE_18_1_JUSTIFICATION: Array based indexing is performed to
    access the Interrupt control registers efficiently.
    The access is checked to be within the bounds of the SFRs available in
    the HW*/
    /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic is performed to
    access the Interrupt control registers efficiently.
    The access is checked to be within the valid memory access of the SFRs
    available in the HW*/
    /* MISRA2012_RULE_1_3_JUSTIFICATION: Pointer arithmetic and Array based 
    indexing is performed to access the Interrupt control registers efficiently.
    The access is checked to be within the valid memory access and within the 
    bounds of the SFRs available in the HW, hence no occurrence of undefined
    behaviour*/
    /* [cover parentID={68622B54-6894-476e-9812-2426A15CD3FF}]
    Calculate address of Service request control register for Limit check group
    [/cover] */
    lVadcGrpSrcPtr = (lVadcGrpSrcPtr + ADC_LIMIT_CHECK_SRN);
  }
  else
  #endif
  {
    /* Address of Service request control register based on request source */
    /* MISRA2012_RULE_18_1_JUSTIFICATION: Array based indexing is performed to
    access the Interrupt control registers efficiently.
    The access is checked to be within the bounds of the SFRs available in
    the HW*/
    /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic is performed to
    access the Interrupt control registers efficiently.
    The access is checked to be within the valid memory access of the SFRs
    available in the HW*/
    /* [cover parentID={FEFFC6DA-E285-413e-8CB2-1B9F9C454BB1}]
    Calculate address of Service request control register based on request
    source [/cover] */
    lVadcGrpSrcPtr = (lVadcGrpSrcPtr + ReqSrc);
  }
  /* [cover parentID={1D628E43-43B4-455c-8820-C43DED8CE39F}]
  Supervisor mode is ON [/cover] */
  #if (ADC_RUN_TIME_API_MODE == ADC_MCAL_SUPERVISOR)
  /* [cover parentID={FFC35476-3FE8-41ab-AF67-873B93F71ECC}]
  Critical Section [/cover] */
  /* [cover parentID={1E0E66D3-797E-48f2-A8A2-ED7C8BF99CBF}]
  Start of critical section [/cover] */
  SchM_Enter_Adc_SrcRegAccess();
  #endif

  /* Clear Service Request bit to avoid unintended interrupt occurrence */
  /* MISRA2012_RULE_18_1_JUSTIFICATION: Array based indexing is performed to
  access the Interrupt control registers efficiently.
  The access is checked to be within the bounds of the SFRs available in
  the HW*/
  /* [cover parentID={F651A39F-FD34-44c1-BDAB-9F35B52B8B72}] Clear pending
  service request [/cover] */
  ADC_RUNTIME_OS_MODIFY32(ADC_MODULE_ID, lVadcGrpSrcPtr, \
                  ADC_CLR_SRC_MASK, ((uint32)ADC_ONE_U<<IFX_SRC_SRCR_CLRR_OFF));

  /* [cover parentID={2937CFFA-C568-486f-B839-8F07126C5F5E}]
  Supervisor mode is ON [/cover] */
  #if (ADC_RUN_TIME_API_MODE == ADC_MCAL_SUPERVISOR)
  /* [cover parentID={D097C7C3-833D-42eb-9D31-0F11B338AD78}]
  End of critical section [/cover] */
  SchM_Exit_Adc_SrcRegAccess();
  #endif

  /* Clear CHCTR, RCR and valid flags for the stopped group */
  Adc_lClearGroupSfr(GrpPtr, KernelId, ReqSrc);
}

/*******************************************************************************
** Traceability: [cover parentID={F2553855-F097-41bc-ADA0-9A9EE8487CA9}]      **
**                                                                            **
** Syntax           : static void Adc_lClearGroupSfr                          **
**                    (                                                       **
**                      const Adc_GroupCfgType * const GrpPtr                 **
**                      const uint32 KernelId                                 **
**                      const uint8 ReqSrc                                    **
**                    )                                                       **
**                                                                            **
** Description      : This function clears all the Channel Control Registers, **
**                    Result Control Registers and Queue Control Register for **
** [/cover]           the group ID.                                           **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different ADC hardware groups             **
**                                                                            **
** Parameters(in)   : GrpPtr  - Pointer to the Group configuration data       **
**                    KernelId  - ADC Group ID of the Kernel                  **
**                    ReqSrc - Request Source of the Group                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Adc_lClearGroupSfr(const Adc_GroupCfgType * const GrpPtr,\
                               const uint32 KernelId,\
                               const uint8 ReqSrc)
{
  Ifx_EVADC_G *lEvadcGroupPtr;
  Ifx_EVADC_G_Q *lEvadcQPtr;
  const Adc_GroupDefType *lGrpDefCfgPtr;
  Adc_ChannelType lAnChannelId;
  Adc_ResultRegType lResReg;
  uint8 lNoOfChannels, lChloopCount;

  /* Get the base address of the Kernel SFR */
  lEvadcGroupPtr = &MODULE_EVADC.G[KernelId];

  /* Get the base address of the RS Queue SFR */
  lEvadcQPtr = &MODULE_EVADC.G[KernelId].Q[ReqSrc];

  /* Get the base address of the groups definition */
  lGrpDefCfgPtr = GrpPtr->GroupDefinition;

  /* [cover parentID={2EA1C230-3012-4758-A38B-EB583758AB54}]
   [/cover] */
  #if(ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW)
  /* [cover parentID={AD537D9E-A091-4a50-89C1-2C8A9A7DB388}]
  Is Group configured with Diagnostic channels [/cover] */
  if(GrpPtr->DiagnosticChGrp == (uint8)ADC_ONE_U)
  {
    /* [cover parentID={DBF090E6-E6D5-438c-A9BD-B49F71832256}]
    Disable Test function for corresponding Kernel of the Group [/cover] */
    Mcal_SetBitAtomic(&(MODULE_EVADC.GLOB.TE.U), (uint8)KernelId, 1, 0U);
  }
  #endif

  /* Clear Queue mode register */
  lEvadcQPtr->QMR.U = (((uint32)ADC_ONE_U << IFX_EVADC_G_Q_QMR_FLUSH_OFF) | \
                       ((uint32)ADC_ONE_U << IFX_EVADC_G_Q_QMR_CEV_OFF) | \
                       ((uint32)ADC_ONE_U << IFX_EVADC_G_Q_QMR_CLRV_OFF));

  /*Clear Queue control register*/
  lEvadcQPtr->QCTRL.U = ADC_Q_CTRL_WRITE_PROTECT_MSK;

  /* Reset Alias configuration; Alias is set / reset only for groups with
    non-default Alias configuration */
  if (ADC_ALIAS_DEFAULT_VALUE != GrpPtr->AliasChCfg)
  {
    lEvadcGroupPtr->ALIAS.U = ADC_ALIAS_DEFAULT_VALUE;
  }
  /* [cover parentID={0C1EC9F7-2C78-4034-BB16-FA35C18EC181}]
  Sync Conversion is ON [/cover] */
  #if (ADC_SYNC_CONV_ENABLE == STD_ON)
  /* [cover parentID={00E667C5-4692-40dc-851A-090A66063724}]
  Is Sync channel configured [/cover] */
  if(GrpPtr->SyncChannelMask != (uint16)0U)
  {
    /* [cover parentID={B72D04C9-B642-4889-AA86-6DC9C4495C3C}]
    Clears the channel and result events for slave kernels of a synchronization
    group [/cover] */
    Adc_lClearSlaveEvents(GrpPtr, KernelId);
  }
  #endif

  lChloopCount = (uint8)0U;
  lNoOfChannels = GrpPtr->NoOfChannels;
  /* [cover parentID={E4F3995F-E3A7-42a3-A472-F9E0C4B4A8A5}]
  Till the Last channel of the Group [/cover] */
  do
  {
    /* Clear all channel control and result control register */
    lAnChannelId = lGrpDefCfgPtr[lChloopCount].AnalogChannelNo;
    lResReg = lGrpDefCfgPtr[lChloopCount].ResultReg;
    lEvadcGroupPtr->CHCTR[lAnChannelId].U = (uint32)0U;
    lEvadcGroupPtr->RCR[lResReg].U = (uint32)0U;
    /* [cover parentID={8231F767-9CCB-4a9e-9D64-E983DB3D4D38}]
    Sync Conversion is ON [/cover] */
    #if (ADC_SYNC_CONV_ENABLE == STD_ON)
    if(((uint16)(GrpPtr->SyncChannelMask &\
                 (uint16)((uint16)ADC_ONE_U << lAnChannelId))) != (uint16)0U)
    {
      /* [cover parentID={2BEBC113-5176-43f9-97B7-27BD91C367D6}]
      Clears the slave channels of synchronization group [/cover] */
      Adc_lClearSyncCh(KernelId, lAnChannelId, lResReg);
    }
    #endif
    lChloopCount++;
  } while(lChloopCount < lNoOfChannels);

  /* [cover parentID={4D0B5820-91D3-44b1-AFA2-AA54960BD8C3}]
  Enable Limit Check is ON [/cover] */
  #if (ADC_ENABLE_LIMIT_CHECK==STD_ON)
  /* [cover parentID={0832B66F-012D-43c6-9DDE-AC923B306F08}]
  Is Group enabled with Limit Check [/cover] */
  if(GrpPtr->LimitCheckGroup == (uint8)ADC_ONE_U)
  {
    /* [cover parentID={E31A02A8-90B0-44f2-8236-9A99EE29AFAD}]
    Clear Group bound register [/cover] */
    lEvadcGroupPtr->BOUND.U = (uint32)0U;
  }
  #endif

  /* [cover parentID={0E003331-2934-49e2-A173-CD09E1C87903}]
   [/cover] */
  #if(ADC_EMUX_ENABLE == STD_ON)
  uint8 lEmuxGrp;
  lEmuxGrp = (ADC_ONE_U & (GrpPtr->GrpEmuxCfg));
  /* [cover parentID={776746F7-11DF-4499-8390-D466EF651936}]
  Group is configured with the EMUX [/cover] */
  if(lEmuxGrp == ADC_ONE_U)
  {
    /* [cover parentID={776746F7-11DF-4499-8390-D466EF651936}]
    Clear the EMUX control and channel selection register [/cover] */
    lEvadcGroupPtr->EMUXCTR.U      = (uint32)ADC_ONE_U << \
                                                  IFX_EVADC_G_EMUXCTR_EMXWC_OFF;
    lEvadcGroupPtr->EMUXCS.U       = (uint32)0U;
  }
  #endif

  /* Clear RS event, Channel event and result event flags */
  lEvadcGroupPtr->SEFCLR.U = ((uint32)ADC_ONE_U << ReqSrc);
  lEvadcGroupPtr->CEFCLR.U = (uint32)GrpPtr->ChannelMask;
  lEvadcGroupPtr->REFCLR.U = (uint32)GrpPtr->ResultRegMask;
  /* Clear valid flags for all result registers */
  lEvadcGroupPtr->VFR.U = (uint32)GrpPtr->ResultRegMask;
}

/*******************************************************************************
** Traceability: [cover parentID={4DE88169-095F-42bd-92DB-13BFCFF000E8}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE void Adc_lRemoveActiveGroup                **
**                    (                                                       **
**                      Adc_GlobalDataType * const KernelDataPtr              **
**                      const Adc_GroupCfgType * const GrpPtr                 **
**                      const uint8 ReqSrc                                    **
**                    )                                                       **
**                                                                            **
** Description      : This Function removes the active group from the Kernel  **
**                    Data                                                    **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different ADC hardware groups             **
**                                                                            **
** Parameters(in)   : KernelDataPtr  - Pointer to the Kernel specific data    **
**                  : GrpPtr  - Pointer to the Group configuration data       **
**                  : RegSrc - Request source of the group                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Adc_lRemoveActiveGroup(\
                                     Adc_GlobalDataType *const KernelDataPtr,\
                                     const Adc_GroupCfgType * const GrpPtr,\
                                     const uint8 ReqSrc)
{
  /*Assign Invalid Group ID to active group variable*/
  KernelDataPtr->RSData[ReqSrc].ActiveGroupId = ADC_INVALID_GROUP_ID;

  /* [cover parentID={6A252B82-0EB4-4dfa-A027-A7C371A3F835}]
  Limit Checking is ON [/cover] */
  #if (ADC_ENABLE_LIMIT_CHECK==STD_ON)
  /* [cover parentID={689A1CA5-9184-4c9e-AA7D-A93E43914944}]
  Is Limit Checking enabled for the Group [/cover] */
  if((uint8)ADC_ONE_U == GrpPtr->LimitCheckGroup)
  {
    /* [cover parentID={E3B9FCA5-57FF-4eaa-8AA6-4B221CE23EA0}]
    Assign Invalid channel ID to an Active limit check channel [/cover] */
    KernelDataPtr->RSData[ReqSrc].ActiveLimitChkCh = ADC_INVALID_CHANNEL_ID;
  }
  #endif
  UNUSED_PARAMETER(GrpPtr);
}

#if (ADC_HW_TRIGGER_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={F7828BB7-D6BD-48cf-92E1-8752745C7E60}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE void Adc_lResetHwTrigger                   **
**                    (                                                       **
**                      const Adc_GroupCfgType * const GrpPtr,                **
**                      const uint8 Mode                                      **
**                    )                                                       **
**                                                                            **
** Description      : This Function disables the GTM/ERU channel used by the  **
**                    group.                                                  **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different HW channels                     **
**                                                                            **
** Parameters(in)   : GrpPtr  - Pointer to the Group configuration data       **
**                    Mode  - Indicates the phase in which the fucntion is    **
**                            invoked (Runtime or Init - De Init)             **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Adc_lResetHwTrigger(const Adc_GroupCfgType *const GrpPtr,
                                      const uint8 Mode)
{
  /* [cover parentID={D13D0351-49D5-4ed8-A2D1-D05BF7496A7A}]
  Is ERU Trig Confg not equal to NULL [/cover] */
  if(GrpPtr->EruTrigCfg != NULL_PTR)
  {
    /* [cover parentID={7598C062-B938-435f-B028-06108E550500}]
    De-initialize ERU channel [/cover] */
    Adc_lEruChannelDeInit(GrpPtr->EruTrigCfg, Mode);
  }
  /* [cover parentID={C731D272-4590-4cbd-89FF-9DA5FA064F06}]
  GTM is available [/cover] */
  #if (ADC_GTM_AVAILABLE == STD_ON)
  /* [cover parentID={9A9BB01D-8A8F-406d-A8D7-5C159A0D4CA5}]
  Is GTM Trig Confg not equal to NULL [/cover] */
  else if(GrpPtr->GtmTrigCfg != NULL_PTR)
  {
    /* [cover parentID={D1BC755E-57B0-448c-BC70-8A2704222C61}]
    De-initialize GTM channel [/cover] */
    Adc_lGtmChannelDeInit(GrpPtr->GtmTrigCfg);
  }
  #endif
  else
  {
    /*Do Nothing*/
  }
  /* [cover parentID={38414ADA-18D7-4b95-8B2E-22F83B0244A6}]
  Is ERU Gate Signal Confg not equal to NULL [/cover] */
  if(GrpPtr->EruGateCfg != NULL_PTR)
  {
    /* [cover parentID={3837322A-A3C8-4ce0-9840-EC5F1C031701}]
    De-initialize ERU Gate Signal [/cover] */
    Adc_lEruChannelDeInit(GrpPtr->EruGateCfg, Mode);
  }
  /* [cover parentID={6AE57FA1-5115-4d78-B26E-8D67B721A175}]
  GTM is available [/cover] */
  #if (ADC_GTM_AVAILABLE == STD_ON)
  /* [cover parentID={0ED1CB91-5ACA-4887-986D-2CC49CA04F86}]
  Is GTM Gate Signal Confg not equal to NULL [/cover] */
  else if(GrpPtr->GtmGateCfg != NULL_PTR)
  {
    /* [cover parentID={8C1997F0-4282-4057-BB46-E6CC9551F3E2}]
    De-initialize GTM Gate Signal [/cover] */
    Adc_lGtmChannelDeInit(GrpPtr->GtmGateCfg);
  }
  #endif
  else
  {
    /*Do Nothing*/
  }
}
#endif

#if ((ADC_HW_TRIGGER_API == STD_ON) && (ADC_INIT_CHECK_API == STD_ON) && \
     (ADC_GTM_AVAILABLE == STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={CA17F9AE-BE8B-450e-8005-E4709C8597F8}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint32 Adc_lCheckGtmSfr                    **
**                    (                                                       **
**                      const Adc_HwUnitCfgType *const KernelCfgPtr,          **
**                      const uint32 CompareFlag                              **
**                    )                                                       **
**                                                                            **
** Description      : This Function verify the disabled state of GTM Channel  **
**                    used by the group.                                      **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelCfgPtr - Pointer to the Kernel Config Data        **
**                  : CompareFlag - Flag to compare with configured SFRs or   **
**                    Variables                                               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Compare flag value - all bits as 1 indicates a pass case**
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Adc_lCheckGtmSfr (\
             const Adc_HwUnitCfgType *const KernelCfgPtr, \
             const uint32 CompareFlag)
{
  /* Initialize error value with E_OK */
  uint8 lLoopCount, lGroupCount, lErrVal = E_OK;
  const Adc_GroupCfgType *lGrpCfgPtr;
  uint32 lCompareFlag = CompareFlag;
  Mcu_17_Gtm_TomAtomChConfigType lGtmTomAtomChConfig;

  lGrpCfgPtr = KernelCfgPtr->GrpCfgPtr;
  lGroupCount = KernelCfgPtr->NoOfGroups;

  /* [cover parentID={9ADE8ADF-8752-44a6-9035-CF838B1125C1}]
  Till the last available Group [/cover] */
  for(lLoopCount = (uint8)0U; (lLoopCount < lGroupCount); lLoopCount++)
  {
    /* [cover parentID={37B5D45E-B5BA-437f-A3A9-5070649E7364}]
    Group configured with HW Trigger source and Request Timer not configured
    [/cover] */
    if((lGrpCfgPtr[lLoopCount].TriggerSource) == ADC_TRIGG_SRC_HW)
    {
      /* [cover parentID={37B5D45E-B5BA-437f-A3A9-5070649E7364}]
      Group configured with HW Trigger source and Request Timer not configured
      [/cover] */
      if (lGrpCfgPtr[lLoopCount].GrpReqTmCfg == (uint32)0U)
      {
        /* [cover parentID={738A2752-B2A9-425f-8AF1-DFDA10E9C331}]
        GTM Trigger Configured [/cover] */
        if(lGrpCfgPtr[lLoopCount].GtmTrigCfg != NULL_PTR)
        {
          /* Initialize the structure elements to reset state to verify the
          reseting of Tom/Atom related SFRs for InitCheck */
          /* [cover parentID={40C4EEF1-6228-4003-A961-65430611B749}]
          Initialize the structure elements of GTM Trigger to reset state
          [/cover] */
          lGtmTomAtomChConfig.TimerType = \
                                  lGrpCfgPtr[lLoopCount].GtmTrigCfg->TimerType;
          lGtmTomAtomChConfig.TimerId = \
                                    lGrpCfgPtr[lLoopCount].GtmTrigCfg->TimerId;
          lGtmTomAtomChConfig.TimerChCtrlReg = \
                                             ADC_TOM_ATOM_CH_CNTRL_REG_RST_VAL;
          lGtmTomAtomChConfig.TimerChCN0Reg = (uint32)0U;
          lGtmTomAtomChConfig.TimerChCM0Reg = (uint32)0U;
          lGtmTomAtomChConfig.TimerChCM1Reg = (uint32)0U;
          lGtmTomAtomChConfig.TimerChSR0Reg = (uint32)0U;
          lGtmTomAtomChConfig.TimerChSR1Reg = (uint32)0U;
          lGtmTomAtomChConfig.TimerChIntEnMode = (uint8)0U;

          /* [cover parentID={AB95E04A-ACF3-4e3b-ADD0-E248791FC883}]
          GTM timer type is TOM [/cover] */
          if(lGtmTomAtomChConfig.TimerType == MCU_GTM_TIMER_TOM)
          {
            /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable
            lGtmTomAtomChConfig is used inside Mcu_17_Gtm_TomChInitCheck() to
            read the values. The address is not used beyond the context of the
            API, hence it is not an issue*/
            /* [cover parentID={16115E88-585F-4db8-9D6D-DD8A497E7819}]
            Perform Tom Initcheck [/cover] */
            lErrVal = Mcu_17_Gtm_TomChInitCheck(&lGtmTomAtomChConfig);
          }
          else
          {
            /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable
            lGtmTomAtomChConfig is used inside Mcu_17_Gtm_AtomChInitCheck() to
            read the values. The address is not used beyond the context of the
            API, hence it is not an issue*/
            /* [cover parentID={30F4218A-1958-413e-89B9-B2F56AFBFE1A}]
            Perform ATOM InitCheck [/cover] */
            lErrVal = Mcu_17_Gtm_AtomChInitCheck(&lGtmTomAtomChConfig);
          }
        }
        /* [cover parentID={29FBD62B-932E-4f2b-85FC-5D49CD1AC4C1}]
        GTM Gate Configured and No error [/cover] */
        if((lGrpCfgPtr[lLoopCount].GtmGateCfg != NULL_PTR) && (lErrVal == E_OK))
        {
          /* Initialize the structure elements to reset state to verify the
          reseting of Tom/Atom related SFRs for InitCheck */
          /* [cover parentID={5B55CEF4-8648-4f9d-A2AA-5BA4FA10AD02}]
          Initialize the structure elements of GTM Gate to reset state[/cover]*/
          lGtmTomAtomChConfig.TimerType = \
                                  lGrpCfgPtr[lLoopCount].GtmGateCfg->TimerType;
          lGtmTomAtomChConfig.TimerId = \
                                    lGrpCfgPtr[lLoopCount].GtmGateCfg->TimerId;
          lGtmTomAtomChConfig.TimerChCtrlReg = \
                                     ADC_TOM_ATOM_CH_CNTRL_REG_RST_VAL;
          lGtmTomAtomChConfig.TimerChCN0Reg = (uint32)0U;
          lGtmTomAtomChConfig.TimerChCM0Reg = (uint32)0U;
          lGtmTomAtomChConfig.TimerChCM1Reg = (uint32)0U;
          lGtmTomAtomChConfig.TimerChSR0Reg = (uint32)0U;
          lGtmTomAtomChConfig.TimerChSR1Reg = (uint32)0U;
          lGtmTomAtomChConfig.TimerChIntEnMode = (uint8)0U;

          /* [cover parentID={C56E64D0-9745-4a8e-86A1-454D35033BF4}]
          GTM timer type is TOM [/cover] */
          if(lGtmTomAtomChConfig.TimerType == MCU_GTM_TIMER_TOM)
          {
            /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable
            lGtmTomAtomChConfig is used inside Mcu_17_Gtm_TomChInitCheck() to
            read the values. The address is not used beyond the context of the
            API, hence it is not an issue*/
            /* [cover parentID={1B1A26BC-F66D-47ab-8DB2-59D63246CAA6}]
            Perform Tom Initcheck [/cover] */
            lErrVal = Mcu_17_Gtm_TomChInitCheck(&lGtmTomAtomChConfig);
          }
          else
          {
            /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable
            lGtmTomAtomChConfig is used inside Mcu_17_Gtm_AtomChInitCheck() to
            read the values. The address is not used beyond the context of the
            API, hence it is not an issue*/
            /* [cover parentID={D0C6959C-2456-46f7-A0F7-259318BA7EF3}]
            Perform GTM Atom InitCheck [/cover] */
            lErrVal = Mcu_17_Gtm_AtomChInitCheck(&lGtmTomAtomChConfig);
          }
        }
        /* [cover parentID={4444ADA0-3986-49c4-84F7-84C90E59C5DD}]
        Error in GTM Tom or Atom InitCheck [/cover] */
        if(lErrVal != E_OK)
        {
          /* [cover parentID={0A1215B0-AC73-4c43-85C1-CADA48D3E6C4}]
          Corrupt the Compare Flag [/cover] */
          lCompareFlag = 0U;
          break;
        }
      }
    }
  }
  return(lCompareFlag);
}
#endif

#if ((ADC_HW_TRIGGER_API == STD_ON) && (ADC_INIT_CHECK_API == STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={7C3B0680-4429-4a4b-8042-0232736EE3F0}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint32 Adc_lCheckEruSfr                    **
**                    (                                                       **
**                      const Adc_HwUnitCfgType *const KernelCfgPtr,          **
**                      const uint32 CompareFlag                              **
**                    )                                                       **
**                                                                            **
** Description      : This Function verify the disabled state of ERU          **
**                    channel used by the group.                              **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelCfgPtr - Pointer to the Kernel Config Data        **
**                  : CompareFlag - Flag to compare with configured SFRs or   **
**                    Variables                                               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Compare flag value - all bits as 1 indicates a pass case**
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Adc_lCheckEruSfr(\
             const Adc_HwUnitCfgType *const KernelCfgPtr, \
             const uint32 CompareFlag)
{
  /* Initialize error value with E_OK */
  uint8 lLoopCount, lGroupCount;
  uint32 lCompareFlag = CompareFlag;
  const Adc_GroupCfgType *lGrpCfgPtr;

  lGrpCfgPtr = KernelCfgPtr->GrpCfgPtr;
  lGroupCount = KernelCfgPtr->NoOfGroups;

  /* Loop for all the HW triggered groups and Verify the reset state */
  /* [cover parentID={5F22F90A-11DF-4a1b-82F2-125DED02F52A}]
  Till the last available Group [/cover] */
  for(lLoopCount = (uint8)0U; (lLoopCount < lGroupCount); lLoopCount++)
  {
    /* [cover parentID={3CBD251A-F066-40f2-A335-B0B50E5F9742}]
    Group configured with HW Trigger source & Request Timer not configured
    [/cover] */
    if((lGrpCfgPtr[lLoopCount].TriggerSource) == ADC_TRIGG_SRC_HW)
    {
      /* [cover parentID={3CBD251A-F066-40f2-A335-B0B50E5F9742}]
      Group configured with HW Trigger source & Request Timer not configured
      [/cover] */
      if (lGrpCfgPtr[lLoopCount].GrpReqTmCfg == (uint32)0U)
      {
        /* [cover parentID={162676E2-570B-4008-835E-20D10930547B}]
        ERU Trigger Configured [/cover] */
        if(lGrpCfgPtr[lLoopCount].EruTrigCfg != NULL_PTR)
        {
          /* [cover parentID={F36A433B-ADFA-47e1-BF23-650E49CBDA75}]
          Perform ERU Trigger Channel De-Init Check [/cover] */
          lCompareFlag = Adc_lCheckEruChannelDeInit(\
                         lGrpCfgPtr[lLoopCount].EruTrigCfg, lCompareFlag);
        }
        /* [cover parentID={66BCF051-25D2-4486-9EC0-F0052F48DD15}]
        ERU Gate Configured [/cover] */
        if(lGrpCfgPtr[lLoopCount].EruGateCfg != NULL_PTR)
        {
          /* [cover parentID={FB264DBF-2A57-4731-8B2E-FE71C69F0B4E}]
          Perform ERU Gate Channel De-Init Check [/cover] */
          lCompareFlag = Adc_lCheckEruChannelDeInit(\
                         lGrpCfgPtr[lLoopCount].EruGateCfg, lCompareFlag);
        }
      }
    }
  }
  return(lCompareFlag);
}
#endif

#if (ADC_HW_TRIGGER_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={9D620829-64CB-450d-83DD-A941394ECFC9}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE void Adc_lSetHwTrigger                     **
**                    (                                                       **
**                      const Adc_GroupCfgType * const GrpPtr                 **
**                    )                                                       **
**                                                                            **
** Description      : This Function Enables the GTM/ERU channel used by the   **
** [/cover]                                                                   **
**                    group.                                                  **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different HW channels                     **
**                                                                            **
** Parameters(in)   : GrpPtr  - Pointer to the Group configuration data       **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Adc_lSetHwTrigger(const Adc_GroupCfgType * const GrpPtr)
{
  /* [cover parentID={39BD5D8B-00A5-4d15-BBBA-549FF88DA568}]
  Is ERU trigger signal configured [/cover] */
  if(GrpPtr->EruTrigCfg != NULL_PTR)
  {
    /* [cover parentID={DD6AC386-58E9-4311-8E05-266A0928E607}]
    Configures and Triggers the start of the ERUchannel [/cover] */
    Adc_lEruChannelInit(GrpPtr->EruTrigCfg);
  }
  /* [cover parentID={8D44C7D0-4D80-4cfe-9345-C66B12D77305}]
  GTM is available [/cover] */
  #if (ADC_GTM_AVAILABLE == STD_ON)
  /* [cover parentID={5C67B1AD-FC0A-415a-BBE7-E2AA13395A76}]
  Is GTM trigger signal configured [/cover] */
  else if(GrpPtr->GtmTrigCfg != NULL_PTR)
  {
    /* [cover parentID={D63EDF02-95D1-4f1f-AA17-94EDEF1D828F}]
    Configures and Triggers the start of the GTM channel [/cover] */
    Adc_lGtmChannelInit(GrpPtr->GtmTrigCfg);
  }
  #endif
  else
  {
    /*Do Nothing*/
  }

  /* [cover parentID={692487F4-2D65-4402-BAA5-D89C77818673}]
  Is ERU gate signal configured [/cover] */
  if(GrpPtr->EruGateCfg != NULL_PTR)
  {
    /* [cover parentID={0515D6FE-1A69-47ef-BF67-D19231E6AE62}]
    Configures and Triggers the start of the ERU Gate Signal [/cover] */
    Adc_lEruChannelInit(GrpPtr->EruGateCfg);
  }
  /* [cover parentID={5437467C-9AF0-48fe-B69A-64A37382D5A6}]
  GTM is available [/cover] */
  #if (ADC_GTM_AVAILABLE == STD_ON)
  /* [cover parentID={0F7242D8-D71D-4155-856D-E0FCAF25CE09}]
  Is GTM gate signal configured [/cover] */
  else if(GrpPtr->GtmGateCfg != NULL_PTR)
  {
    /* [cover parentID={78C3C2A3-2ABE-47d2-89BF-106F657D8447}]
    Configures and Triggers the start of the GTM Gate Signal [/cover] */
    Adc_lGtmChannelInit(GrpPtr->GtmGateCfg);
  }
  #endif
  else
  {
    /*Do Nothing*/
  }
}
#endif
#if (ADC_HW_TRIGGER_API == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={14785AA7-E1CB-48f1-8099-159E842D4D31}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE void Adc_lStartHwConversion                **
**                    (                                                       **
**                      const Adc_GroupCfgType * const GrpPtr                 **
**                      const uint32 KernelId                                 **
**                      const uint8 ReqSrc                                    **
**                    )                                                       **
**                                                                            **
** Description      : This function programs the Request Source Queue and     **
**                    triggers the start of conversion.                       **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different ADC hardware groups             **
**                                                                            **
** Parameters(in)   : GrpPtr  - Pointer to the Group configuration data       **
**                    KernelId  - ADC Group ID of the Kernel                  **
**                    ReqSrc  - Request source on which to start the group    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Adc_lStartHwConversion(const Adc_GroupCfgType * const GrpPtr,\
                                         const uint32 KernelId,\
                                         const uint8 ReqSrc)
{
  Ifx_EVADC_G *lEvadcGroupPtr;
  Ifx_EVADC_G_Q *lEvadcQPtr;
  const Adc_GroupDefType *lGrpDefCfgPtr;
  uint32 lConvMode, lRsIntpt, lWaitForTrigger;
  uint8 lNoOfChannels, lChloopCount;

  /* Get base address of the kernel SFR */
  lEvadcGroupPtr = &MODULE_EVADC.G[KernelId];
  /* Get base address of the RS SFR */

  lEvadcQPtr = &MODULE_EVADC.G[KernelId].Q[ReqSrc];
  
  /* Get the group definition configuration */
  lGrpDefCfgPtr = GrpPtr->GroupDefinition;
  
  /* Flush the RS queue, before channels are queued up for conversion */
  lEvadcQPtr->QMR.U = (((uint32)ADC_ONE_U << IFX_EVADC_G_Q_QMR_FLUSH_OFF) | \
                       ((uint32)ADC_ONE_U << IFX_EVADC_G_Q_QMR_CEV_OFF) | \
                       ((uint32)ADC_ONE_U << IFX_EVADC_G_Q_QMR_CLRV_OFF));

  /* Clear RS event, Channel event and result event flags */
  lEvadcGroupPtr->SEFCLR.U = ((uint32)ADC_ONE_U << ReqSrc);
  lEvadcGroupPtr->CEFCLR.U = (uint32)GrpPtr->ChannelMask;
  lEvadcGroupPtr->REFCLR.U = (uint32)GrpPtr->ResultRegMask;
  /* Clear valid flag for all result registers */
  lEvadcGroupPtr->VFR.U = (uint32)GrpPtr->ResultRegMask;

  /* [cover parentID={1EAA0F64-8A95-46a6-8794-057B79E3F6CF}]
  Priority Implementation is HW Priority [/cover] */
  #if(ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW)
  /* [cover parentID={C825CB39-5402-452e-B9DD-496BDA364FD4}]
  Is Group Configured with Diagnostic channels [/cover] */
  if(GrpPtr->DiagnosticChGrp == (uint8)ADC_ONE_U)
  {
    /* [cover parentID={3E3F0FA1-B8EB-47c9-B3C3-52E7D1147AE6}]
    Enable Test function for corresponding Kernel of the Group [/cover] */
    Mcal_SetBitAtomic(&(MODULE_EVADC.GLOB.TE.U), (uint8)KernelId, 1, ADC_ONE_U);
  }
  #endif

  /* [cover parentID={711BD69A-85AF-4860-B0F3-2347AA32BB0C}]
   [/cover] */
  #if(ADC_EMUX_ENABLE == STD_ON)
  Adc_ResultRegType lResReg;
  uint8 lEmuxGrp;

  /* [cover parentID={2324D378-57CD-4d09-B5D1-1A69024B69C7}]
  Group is configured with the EMUX [/cover] */
  lEmuxGrp = (ADC_ONE_U & (GrpPtr->GrpEmuxCfg));
  if(lEmuxGrp == ADC_ONE_U)
  {
    /* [cover parentID={2324D378-57CD-4d09-B5D1-1A69024B69C7}]
    Configure the Wait-For-Read mode when emux feature is enabled [/cover] */
    lResReg = lGrpDefCfgPtr[0U].ResultReg;
    lEvadcGroupPtr->RCR[lResReg].U |= \
                                  ((uint32)ADC_ONE_U<<IFX_EVADC_G_RCR_WFR_OFF);
  }
  #endif

  /* [cover parentID={33F297B1-9A54-49c7-A912-9DF8C2F037C5}]
  Sync conversion mode is on [/cover] */
  #if (ADC_SYNC_CONV_ENABLE == STD_ON)
  /* [cover parentID={3992B075-8725-46b7-BBED-86C84D8CA273}]
  Sync Channel [/cover] */
  if(GrpPtr->SyncChannelMask != (uint16)0U)
  {
    /* [cover parentID={2B42041A-AB54-4d15-827A-CE082385093A}]
    Clear slave events [/cover] */
    Adc_lClearSlaveEvents(GrpPtr, KernelId);
  }
  #endif

  /* [cover parentID={7D79E7C1-080A-4e88-9275-B50613068874}]
  Enable Refill mode for Hardware conversions [/cover] */
  lConvMode = (uint32)ADC_ONE_U << IFX_EVADC_G_Q_QINR_RF_OFF;

  /* [cover parentID={BEF0F4E5-067C-47de-BAF6-5579E90401A3}]
  Limit Checking is ON [/cover] */
  #if (ADC_ENABLE_LIMIT_CHECK==STD_ON)
  /* [cover parentID={56629BE2-8A40-49a3-A833-5AE8E5905175}]
  Is Group enabled with limit check [/cover] */
  if(GrpPtr->LimitCheckGroup == (uint8)ADC_ONE_U)
  {
    /* [cover parentID={D9CFE81F-6BCF-464d-B68C-97920BBB6B10}]
    Disable the Request Source interrupt [/cover] */
    lRsIntpt = (uint32)0U;
  }
  else
  #endif
  {
    /* [cover parentID={4FF84DCD-75EB-45eb-AE85-2317365185F5}]
    Enable the Request Source interrupt  [/cover] */
    /* If group is not LIMIT CHECKING, enable the RS interrupt */
    lRsIntpt = (uint32)ADC_ONE_U << IFX_EVADC_G_Q_QINR_ENSI_OFF;
  }

  lNoOfChannels = GrpPtr->NoOfChannels;
  lChloopCount = (uint8)0U;

  /* Update QCTRL from configuration directly */
  lEvadcQPtr->QCTRL.U = (uint32)\
              (GrpPtr->GroupQCtrlCfg | ADC_Q_CTRL_WRITE_PROTECT_MSK);

  /* Enable wait for external trigger for the 1st entry in the queue */
  /* [cover parentID={D5A2F0A5-9C4D-4745-8BBA-883DB126A386}]
  1st Entry in the queue shall wait for a Hardware trigger event [/cover] */
  lWaitForTrigger = (uint32)ADC_ONE_U << IFX_EVADC_G_Q_QINR_EXTR_OFF;

  /* [cover parentID={F3600562-8F7C-4c4c-9E70-7ED4FBAF3FBA}]
  Till the all channels except last one [/cover] */
  while(lChloopCount < (lNoOfChannels - (uint8)1U))
  {
    /* [cover parentID={C160A45C-1F09-4360-A20F-3BC2EA505C46},
    {B9568FC8-DC93-4299-A713-C3BA9A6E7A0D}] Analog channels are pushed to RS 
    queue with refill mode and Diagnostics feature information [/cover] */
    /* 1st channel is programmed to wait for a HW trigger event*/
    lEvadcQPtr->QINR.U =\
        (lConvMode | lWaitForTrigger |\
        (uint32)(lGrpDefCfgPtr[lChloopCount].AnalogChannelNo) |\
        (uint32)(lGrpDefCfgPtr[lChloopCount].AnChDiagnosticsCfg));
    /* Reset wait for trigger, for subsequent queue entries */
    lWaitForTrigger = (uint32)0U;
    lChloopCount++;
  }

  /* If there is only one channel in the group
     Wait for HW trigger event is enabled here */
  /* [cover parentID={D86B5A7D-C4EE-465b-B91B-9E925BDD6A0C}]
  Last Analog channel is pushed to RS queue with refill mode and and Diagnostics
  feature information and RS interrupt enabled [/cover] */
  lEvadcQPtr->QINR.U =(lConvMode | lWaitForTrigger | lRsIntpt  |\
                      (uint32)(lGrpDefCfgPtr[lChloopCount].AnalogChannelNo) |\
                      (uint32)(lGrpDefCfgPtr[lChloopCount].AnChDiagnosticsCfg));

  /* [cover parentID={79777411-BFBB-4be4-8A29-CABBBDB2E50C}]
  Set Up the HW trigger peripheral [/cover] */

  /* [cover parentID={F71436E6-392E-4db3-A3E1-815EFC754285}]
  Request timer configured [/cover] */
  if (GrpPtr->GrpReqTmCfg != (uint32)0U)
  {
    /* [cover parentID={DA63712F-FF60-4385-BA0C-A6154E0878AE}]
    Update request timer register with configured value [/cover] */
    lEvadcQPtr->REQTM.U = GrpPtr->GrpReqTmCfg;
  }
  else
  {
    /* [cover parentID={79777411-BFBB-4be4-8A29-CABBBDB2E50C}]
    Set Up the HW trigger peripheral [/cover] */
    Adc_lSetHwTrigger(GrpPtr);
  }

  /* [cover parentID={1673201D-EA4B-460d-871E-0CFA65D860A9}]
  Priority Implementation is HW-SW Priority [/cover] */
  #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
  /* [cover parentID={0B0DFCBC-32FA-43d6-A824-D5CEC9DF88A5}]
  Adjust RS priority [/cover] */
  Adc_lAdjustRsPriorities(KernelId);
  #endif

  /* [cover parentID={57676D1F-48FF-43c5-BA14-FD7AF1F1FE2E}]
  Program the QMR register from configuration, Wait for trigger event now to
  start conversions [/cover] */
  lEvadcQPtr->QMR.U = GrpPtr->GroupQModeCfg;
  /* [cover parentID={F1F45E7F-733B-4be1-AA9B-72FA1C19EB17}]
  Request timer configured [/cover] */
  if (GrpPtr->GrpReqTmCfg != (uint32)0U)
  {
    /* [cover parentID={B454F93C-9837-4884-83DA-39BB8509FB3B}]
    Start the request timer [/cover] */
    lEvadcQPtr->REQTM.B.REQTS = 1U;
  }
}
#endif

#if ((ADC_HW_TRIGGER_API == STD_ON) && (ADC_GTM_AVAILABLE == STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={EE0AC5ED-FEAC-4559-9D9A-0548399BC41A}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE void Adc_lGtmChannelInit                   **
**                    (                                                       **
**                      const Mcu_17_Gtm_TomAtomChConfigType *                **
**                      const GtmChannelCfgPtr                                **
**                    )                                                       **
**                                                                            **
** Description      : This function configures and triggers the start of the  **
**                    GTM channel.                                            **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different GTM channel                     **
**                                                                            **
** Parameters(in)   : GtmChannelCfgPtr  - Pointer to the GTM channel          **
**                    configuration structure.                                **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Adc_lGtmChannelInit(\
                const Mcu_17_Gtm_TomAtomChConfigType * const GtmChannelCfgPtr)
{
  uint8 lGtmModuleNo, lGtmChNo;

  /* Retrieve the TOM module  number */
  lGtmModuleNo = (uint8)((GtmChannelCfgPtr->TimerId & GTM_MODULE_NO_MASK) >> \
                         GTM_MODULE_NO_OFF);

  /* Retrieve the TOM module channel number */
  lGtmChNo = (uint8)((GtmChannelCfgPtr->TimerId & GTM_CHANNEL_NO_MASK) >> \
                     GTM_CHANNEL_NO_OFF);

  /* [cover parentID={98127654-3C59-4ee1-8CE8-492B69C690DB}]
  Is GTM channel configured Timer type is TOM [/cover] */
  if(GtmChannelCfgPtr->TimerType == MCU_GTM_TIMER_TOM)
  {
    /* [cover parentID={A9A6D91C-9CCB-4c06-8C86-B0D208723CA7}]
    Initialize the TOM channel [/cover] */
    Mcu_17_Gtm_TomChannelInit(GtmChannelCfgPtr);
    /* [cover parentID={E2D95263-218A-4a71-8388-7912D7D99B17}]
    Shadow Transfer trigger for TOM channel [/cover] */
    Mcu_17_Gtm_TomChannelShadowTransfer(lGtmModuleNo, lGtmChNo);
    /* [cover parentID={895AB5D8-CB72-436c-943B-59ED7A87FFDD}]
    Enable the channel & Output [/cover] */
    Mcu_17_Gtm_TomChannelEnable(lGtmModuleNo, lGtmChNo, \
                                MCU_GTM_TIMER_OUT_ENABLE);
  }
  else
  {
    /* [cover parentID={3770463C-5092-46cf-A504-FE160EF85082}]
    Initialize the ATOM channel [/cover] */
    Mcu_17_Gtm_AtomChannelInit(GtmChannelCfgPtr);
    /* [cover parentID={8BAE04F7-5A98-422a-BF50-4D3033176FBF}]
    Shadow Transfer trigger for ATOM channel [/cover] */
    Mcu_17_Gtm_AtomChannelShadowTransfer(lGtmModuleNo, lGtmChNo);
    /* [cover parentID={C9437F1E-4F08-4dde-B50C-B0B29A170830}]
    Enable the channel & Output [/cover] */
    Mcu_17_Gtm_AtomChannelEnable(lGtmModuleNo, lGtmChNo, \
                                 MCU_GTM_TIMER_OUT_ENABLE);
  }
}
#endif

#if ((ADC_HW_TRIGGER_API == STD_ON) && (ADC_GTM_AVAILABLE == STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={659720C3-53B5-4738-9DDA-BBB3CF0BC4D8}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE void Adc_lGtmChannelDeInit                 **
**                    (                                                       **
**                       const Mcu_17_Gtm_TomAtomChConfigType *               **
**                       const GtmChannelCfgPtr **                            **
**                    )                                                       **
**                                                                            **
** Description      : This function stops and de-initializes a GTM channel.   **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different GTM channel                     **
**                                                                            **
** Parameters(in)   : GtmChannelCfgPtr  - Pointer to the GTM channel          **
**                    configuration structure.                                **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Adc_lGtmChannelDeInit(\
                const Mcu_17_Gtm_TomAtomChConfigType * const GtmChannelCfgPtr)
{
  uint8 lGtmModuleNo, lGtmChNo;

  /* Retrieve the TOM module  number */
  lGtmModuleNo = (uint8)((GtmChannelCfgPtr->TimerId & GTM_MODULE_NO_MASK) >> \
                         GTM_MODULE_NO_OFF);

  /* Retrieve the TOM module channel number */
  lGtmChNo = (uint8)((GtmChannelCfgPtr->TimerId & GTM_CHANNEL_NO_MASK) >> \
                     GTM_CHANNEL_NO_OFF);

  /* [cover parentID={89F8EBA8-F96B-4f2d-9142-4A1072EB6167}]
  Is GTM channel configured Timer type is TOM [/cover] */
  if(GtmChannelCfgPtr->TimerType == MCU_GTM_TIMER_TOM)
  {
    /* [cover parentID={45B48AC5-D065-4073-9CCB-EE19BE7DAD90}]
    Disable the channel & Output [/cover] */
    Mcu_17_Gtm_TomChannelDisable(lGtmModuleNo, lGtmChNo);
    /* [cover parentID={E7BE7BCC-BB79-4401-9B1C-370E96E7AADF}]
    De-initialize the TOM channel [/cover] */
    Mcu_17_Gtm_TomChannelDeInit(lGtmModuleNo, lGtmChNo);
    /* [cover parentID={F1755792-0BA3-40cd-AD61-3D741A2C503E}]
    Shadow Transfer trigger for TOM Channel [/cover] */
    Mcu_17_Gtm_TomChannelShadowTransfer(lGtmModuleNo, lGtmChNo);
  }
  else
  {
    /* [cover parentID={4836A67E-8C29-4453-9FBA-FD8C3FA821F1}]
    Disable the channel & Output [/cover] */
    Mcu_17_Gtm_AtomChannelDisable(lGtmModuleNo, lGtmChNo);
    /* [cover parentID={A6D0AC59-4450-46f4-9E8C-04041424E867}]
    De-initialize the ATOM channel [/cover] */
    Mcu_17_Gtm_AtomChannelDeInit(lGtmModuleNo, lGtmChNo);
    /* [cover parentID={6F64F8A5-C34B-419d-8A6B-3B9E3CFEE0E7}]
    Shadow Transfer trigger for ATOM Channel [/cover] */
    Mcu_17_Gtm_AtomChannelShadowTransfer(lGtmModuleNo, lGtmChNo);
  }
}
#endif

#if (ADC_HW_TRIGGER_API == STD_ON)
/******************************************************************************
** Traceability: [cover parentID={8914AF2D-3897-4806-A8BB-6DF1760BD4F8}]     **
**                                                                           **
** Syntax           : LOCAL_INLINE void Adc_lEruChannelInit                  **
**                    (                                                      **
**                      const Adc_EruChannelCfgType * const EruChannelCfgPtr **
**                    )                                                      **
**                                                                           **
** Description      : This function configures and triggers the start of the **
**                    ERU channel.                                           **
** [/cover]                                                                  **
** Service ID       : NA                                                     **
**                                                                           **
** Sync/Async       : Synchronous                                            **
**                                                                           **
** Reentrancy       : Reentrant for different ERU Channels                   **
**                                                                           **
** Parameters(in)   : EruChannelCfgPtr  - Pointer to the ERU channel         **
**                    configuration structure.                               **
**                                                                           **
** Parameters (out) : None                                                   **
**                                                                           **
** Return value     : None                                                   **
**                                                                           **
******************************************************************************/
LOCAL_INLINE void Adc_lEruChannelInit(\
              const Adc_EruChannelCfgType * const EruChannelCfgPtr)
{
  uint32 lEicrIndex, lIgcrIndex;
  uint8 lEicrPos, lIgcrPos;

  /* Each EICR register consists of 2 channels, hence index is div 2 */
  lEicrIndex = (((uint32)(EruChannelCfgPtr->ErsChannel) >> (uint32)ADC_ONE_U) &\
                (uint32)ADC_ERU_EICR_REG_SEL_MASK);
  /* Odd Channels are at bit position is 16,
    and for even channels bit position is 0*/
  lEicrPos = (uint8)(\
  ((uint32)(EruChannelCfgPtr->ErsChannel) & (uint32)ADC_ONE_U)<<\
                                         (uint32)ADC_ERU_CH_CFG_BIT_POS_SHIFT);

  /* Each IGCR register consists of 2 channels, hence index is div 2 */
  lIgcrIndex = (((uint32)(EruChannelCfgPtr->OguChannel)>>(uint32)ADC_ONE_U) &\
                                          (uint32)ADC_ERU_IGCR_REG_SEL_MASK);
  /* Odd Channels are at bit position is 16,
    and for even channels bit position is 0*/
  lIgcrPos = (uint8)(\
  ((uint32)(EruChannelCfgPtr->OguChannel) & (uint32)ADC_ONE_U)<<\
                                         (uint32)ADC_ERU_CH_CFG_BIT_POS_SHIFT);

  /* [cover parentID={838833ED-99DB-433b-AF6F-03F1B9621465}]
  Program External input channel register  [/cover] */
  ADC_RUNTIME_WRITE_SAFETY_ENDINIT_PROTREGMASK(\
                           (&MODULE_SCU.EICR[lEicrIndex]),\
                           ((uint32)EruChannelCfgPtr->EruEicrCfg<<lEicrPos),\
                           (ADC_ERU_WR_MASK<<lEicrPos));

  /* [cover parentID={4BDE1B61-40C6-452d-B747-A8848308252C}]
  Program Interrupt gating control register [/cover] */
  ADC_RUNTIME_WRITE_SAFETY_ENDINIT_PROTREGMASK(\
                           (&MODULE_SCU.IGCR[lIgcrIndex]),\
                           ((uint32)EruChannelCfgPtr->EruIgcrCfg<<lIgcrPos),\
                           (ADC_ERU_WR_MASK<<lIgcrPos));
}
#endif

#if (ADC_HW_TRIGGER_API == STD_ON)
/******************************************************************************
** Traceability: [cover parentID={EDB26D17-38BB-4bd5-B8E3-45D73A68E4AB}]     **
**                                                                           **
** Syntax           : LOCAL_INLINE void Adc_lEruChannelDeInit                **
**                    (                                                      **
**                      const Adc_EruChannelCfgType * const EruChannelCfgPtr,**
**                      const uint8 Mode                                     **
**                    )                                                      **
**                                                                           **
** Description      : This function de-initializes ERS and OGU pointed by    **
**                    EruChannelCfgPtr                                       **
** [/cover]                                                                  **
** Service ID       : NA                                                     **
**                                                                           **
** Sync/Async       : Synchronous                                            **
**                                                                           **
** Reentrancy       : Reentrant for different ERU Channels                   **
**                                                                           **
** Parameters(in)   : EruChannelCfgPtr  - Pointer to the ERU channel         **
**                    configuration structure.                               **
**                    Mode  - Indicates the phase in which the fucntion is   **
**                            invoked (Runtime or Init - De Init)            **
**                                                                           **
** Parameters (out) : None                                                   **
**                                                                           **
** Return value     : None                                                   **
**                                                                           **
******************************************************************************/
LOCAL_INLINE void Adc_lEruChannelDeInit(\
               const Adc_EruChannelCfgType * const EruChannelCfgPtr,\
               const uint8 Mode)
{
  uint32 lEicrIndex, lIgcrIndex;
  uint8 lEicrPos, lIgcrPos;

  /* Each EICR register consists of 2 channels, hence index is div 2 */
  lEicrIndex = (((uint32)(EruChannelCfgPtr->ErsChannel) >> (uint32)ADC_ONE_U) \
                & (uint32)ADC_ERU_EICR_REG_SEL_MASK);
  /* Odd Channels are at bit position is 16,
    and for even channels bit position is 0*/
  lEicrPos = (uint8)(\
  ((uint32)(EruChannelCfgPtr->ErsChannel) & (uint32)ADC_ONE_U)<<\
                                         (uint32)ADC_ERU_CH_CFG_BIT_POS_SHIFT);

  /* Each IGCR register consists of 2 channels, hence index is div 2 */
  lIgcrIndex = (((uint32)(EruChannelCfgPtr->OguChannel)>>(uint32)ADC_ONE_U) &\
                                          (uint32)ADC_ERU_IGCR_REG_SEL_MASK);
  /* Odd Channels are at bit position is 16,
    and for even channels bit position is 0*/
  lIgcrPos = (uint8)(\
  ((uint32)(EruChannelCfgPtr->OguChannel) & (uint32)ADC_ONE_U)<<\
                                         (uint32)ADC_ERU_CH_CFG_BIT_POS_SHIFT);
  /* [cover parentID={CC4F6ED5-B3A2-4c02-B1E0-78E42C32B47C}]
  Mode is equal to ADC_INIT_DEINIT [/cover] */
  if(Mode == (uint8)ADC_INIT_DEINIT)
  {
    /* [cover parentID={4CBB4289-C56A-42a8-ABB1-18056B848C2C}]
    InitDeInit API Mode:Reset External input channel register [/cover] */
    ADC_INIT_DEINIT_WRITE_SAFETY_ENDINIT_PROTREGMASK(\
                            (&MODULE_SCU.EICR[lEicrIndex]),\
                            ((uint32)0U),\
                            (ADC_ERU_WR_MASK<<lEicrPos));

    /* [cover parentID={A79D760A-C7E3-424f-A0C9-5567988890DA}]
    InitDeInit API Mode:Reset Interrupt gating control register [/cover] */
    ADC_INIT_DEINIT_WRITE_SAFETY_ENDINIT_PROTREGMASK(\
                             (&MODULE_SCU.IGCR[lIgcrIndex]),\
                             ((uint32)0U),\
                             (ADC_ERU_WR_MASK<<lIgcrPos));
  }
  else
  {
    /* [cover parentID={821DE7A9-2A7D-4e8b-AB81-A122F277D7F4}]
    RunTime API Mode:Reset External input channel register [/cover] */
    ADC_RUNTIME_WRITE_SAFETY_ENDINIT_PROTREGMASK(\
                             (&MODULE_SCU.EICR[lEicrIndex]),\
                             ((uint32)0U),\
                             (ADC_ERU_WR_MASK<<lEicrPos));

    /* [cover parentID={3B832A9D-807F-4929-95CA-292BB667EDD0}]
    RunTime API Mode: Reset Interrupt gating control register [/cover] */
    ADC_RUNTIME_WRITE_SAFETY_ENDINIT_PROTREGMASK(\
                             (&MODULE_SCU.IGCR[lIgcrIndex]),\
                             ((uint32)0U),\
                             (ADC_ERU_WR_MASK<<lIgcrPos));
  }
}
#endif

#if ((ADC_HW_TRIGGER_API == STD_ON) && (ADC_INIT_CHECK_API == STD_ON))
/******************************************************************************
** Traceability: [cover parentID={B603D794-9973-4c88-9760-83B1AA9BE83D}]     **
**                                                                           **
** Syntax           : LOCAL_INLINE uint32 Adc_lCheckEruChannelDeInit         **
**                    (                                                      **
**                      const Adc_EruChannelCfgType * const EruChannelCfgPtr,**
**                      const uint32 CompareFlag                             **
**                    )                                                      **
**                                                                           **
** Description      : This function verifies the de-initialization state of  **
**                    ERS and OGU pointed by EruChannelCfgPtr                **
** [/cover]                                                                  **
** Service ID       : NA                                                     **
**                                                                           **
** Sync/Async       : Synchronous                                            **
**                                                                           **
** Reentrancy       : Reentrant                                              **
**                                                                           **
** Parameters(in)   : EruChannelCfgPtr  - Pointer to the ERU channel         **
**                    configuration structure.                               **
**                    CompareFlag - Flag to compare with configured SFRs or  **
**                    Variables                                              **
**                                                                           **
** Parameters (out) : None                                                   **
**                                                                           **
** Return value     : Compare flag value - all bits as 1 indicates a pass    **
**                    case                                                   **
******************************************************************************/
LOCAL_INLINE uint32 Adc_lCheckEruChannelDeInit(\
 const Adc_EruChannelCfgType * const EruChannelCfgPtr, const uint32 CompareFlag)
{
  uint32 lEicrIndex, lIgcrIndex, lSfrVal, lCfgVal;
  uint32 lCompareFlag = CompareFlag;
  uint8 lEicrPos, lIgcrPos;

  /* Each EICR register consists of 2 channels, hence index is div 2 */
  lEicrIndex = (((uint32)(EruChannelCfgPtr->ErsChannel)>>(uint32)ADC_ONE_U) &\
                                           (uint32)ADC_ERU_EICR_REG_SEL_MASK);

  /* Odd Channels are at bit position is 16,
  and for even channels bit position is 0*/
  lEicrPos = (uint8)(\
  ((uint32)(EruChannelCfgPtr->ErsChannel) & (uint32)ADC_ONE_U)<<\
                                         (uint32)ADC_ERU_CH_CFG_BIT_POS_SHIFT);

  /* Each IGCR register consists of 2 channels, hence index is div 2 */
  lIgcrIndex = (((uint32)(EruChannelCfgPtr->OguChannel)>>(uint32)ADC_ONE_U) &\
                                          (uint32)ADC_ERU_IGCR_REG_SEL_MASK);

  /* Odd Channels are at bit position is 16,
  and for even channels bit position is 0*/
  lIgcrPos = (uint8)(\
  ((uint32)(EruChannelCfgPtr->OguChannel) & (uint32)ADC_ONE_U)<<\
                                         (uint32)ADC_ERU_CH_CFG_BIT_POS_SHIFT);

  /* [cover parentID={97615EFD-BFA7-434a-A793-0B27EAD88183}]
  Compare values of EICR register with configured value and update the return
  value [/cover] */
  lSfrVal = ((MODULE_SCU.EICR[lEicrIndex].U) & (ADC_ERU_WR_MASK << lEicrPos));
  lCfgVal = ((uint32)0U);
  lCompareFlag &= ~(lSfrVal ^ lCfgVal);

  /* [cover parentID={05759C18-3D7B-4fab-9C7B-200DF8CCF675}]
  Compare values of IGCR register with configured value and update the return
  value [/cover] */
  lSfrVal = ((MODULE_SCU.IGCR[lIgcrIndex].U) & (ADC_ERU_WR_MASK << lIgcrPos));
  lCfgVal = ((uint32)0U);
  lCompareFlag &= ~(lSfrVal ^ lCfgVal);

  return(lCompareFlag);
}
#endif

/*CYCLOMATIC_Adc_lRSEventHandler_JUSTIFICATION: This function updates the
necessary result buffers and schedules the next group for different result
handling modes of ADC (Interrupt, DMA) for EMUX as well as normal ADC channel
groups based on the enable of pre-compile macros and provides notification, if
enabled. The different if conditions in different modes cause the complexity to
increase, but actually during run-time out of all the if conditions many will
be pre-compile time removed*/
/*******************************************************************************
** Traceability: [cover parentID={EC21FA6B-C11C-461d-BB9E-93D22A72DA99}]      **
**                                                                            **
** Syntax           : static void Adc_lRSEventHandler                         **
**                    (                                                       **
**                      const uint32 KernelId                                 **
**                      const uint8 RequestSrc                                **
**                      const uint32 CoreId                                   **
**                    )                                                       **
**                                                                            **
** Description      : This function updates the necessary result buffers and  **
**                    schedules the next group (if required) for conversion.  **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different ADC hardware groups             **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID for which the Interrupt handler    **
**                    is invoked                                              **
**                    RequestSrc - Request Source for which interrupt occured **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Adc_lRSEventHandler(const uint32 KernelId, const uint8 RequestSrc,\
                                const uint32 CoreId)
{
  Adc_GlobalDataType *lKernelDataPtr;
  Adc_GroupType lGroupId;
  #if ((ADC_EMUX_ENABLE == STD_ON) || (ADC_GRP_NOTIF_CAPABILITY == STD_ON))
  const Adc_GroupCfgType *lGrpCfgPtr;
  #endif

  /* Get global state data location for the Kernel */
  lKernelDataPtr = Adc_lGetKernelDataAddress(KernelId, CoreId);
  /* [cover parentID={D4BA0186-8773-4200-961B-BC4954C15EAD}]
  Is Interrupt Service Routine flag is equal to ZERO [/cover] */
  if(lKernelDataPtr->RSData[RequestSrc].IsrNoServiceFlag == (uint8)0U)
  {
    /* [cover parentID={8C9252D4-A726-472c-BD4A-7D250E6FCEEA}]
    Get running group ID for the Request Source [/cover] */
    lGroupId = lKernelDataPtr->RSData[RequestSrc].ActiveGroupId;

    /* [cover parentID={9ECC0121-5F55-42c3-8C09-046164D92E95}]
    EMUX mode is ON or Group Notify Capability is ON [/cover]*/
    #if ((ADC_EMUX_ENABLE == STD_ON) || (ADC_GRP_NOTIF_CAPABILITY == STD_ON))
    /* [cover parentID={FA988CC7-8A3A-43ef-AED4-6473BA23066D}]
    Get the base address of the group configuration [/cover]*/
    lGrpCfgPtr = &(Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[KernelId]->\
               GrpCfgPtr[lGroupId]);
    /* [cover parentID={8D3B12E9-720E-4977-B7C0-81BD97B9F3C7}]
    EMUX mode is ON [/cover]*/
    #if (ADC_EMUX_ENABLE == STD_ON)
    uint8 lEmuxGrp;
    /* [cover parentID={DA5ED0E4-27A0-4a58-A90B-36594181B47B}]
    Get the Emux data of the Group [/cover]*/
    lEmuxGrp = (ADC_ONE_U & (lGrpCfgPtr->GrpEmuxCfg));
    #endif
    #endif
    /* [cover parentID={FFD97187-68E4-41b0-9A34-81CFE485C9B6}]
    Precompile Switch : Is DMA result handling ON [/cover] */
    /* [cover parentID={09F226FF-1C23-4464-A030-2520B867FB6A}]
    Interrupt Mode Result Handling is ON [/cover] */
    #if(ADC_RESULT_HANDLING_IMPLEMENTATION != ADC_DMA_MODE_RESULT_HANDLING)
    /* [cover parentID={877EE3C7-B6CF-4632-827A-D0318CD0646C}]
    EMUX mode is ON [/cover]*/
    #if(ADC_EMUX_ENABLE == STD_ON)
    /* [cover parentID={FAFEADAC-E6A2-46b6-9973-2184C234CC99}]
    Is Group configured with the EMUX channel [/cover]*/
    if(lEmuxGrp == ADC_ONE_U)
    {
      /* [cover parentID={18C55E2A-53D2-4514-AA64-5ADCFB2DC760}]
      Update results to application buffer for converted EMUX channel [/cover]*/
      Adc_lUpdateEmuxResBuffer(KernelId, lGroupId, CoreId);
      /* [cover parentID={B78ACFA9-6FC4-43b4-BDFF-C437738C3CCC}]
      Are all sets of Emux conversion results available [/cover]*/
      if(lKernelDataPtr->EmuxConversionActiveFlag == ADC_EMUX_STREAM_COMPLETED)
      {
        /* [cover parentID={0B76A6A9-7B96-45eb-B57E-4FD9C83855CA}]
        Check for scheduling next group [/cover] */
        Adc_lGrpSequenceHandler(KernelId, lGroupId, RequestSrc, CoreId);

        /* [cover parentID={ECC4367F-1DFF-4b91-93BA-E8DA9B5026ED}]
        Group Notify Capability is ON [/cover] */
        #if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
        /* [cover parentID={D2190EEC-483A-4c3b-874E-A6E4F7303120}]
        Is Notification enabled for the Group [/cover] */
        if(Adc_lGetGroupNotifStatus(lKernelDataPtr, lGroupId) == \
                                                            (uint32)ADC_ONE_U)
        {
          /* [cover parentID={BA3B285A-89B1-4a9a-9213-D0C747C73B94}]
          Is Notification pointer not equal to NULL pointer [/cover] */
          if(lGrpCfgPtr->NotifyPtr != NULL_PTR)
          {
            /* [cover parentID={77059F6D-DABB-43fd-882E-A9C80DDC4D85}]
            Set the Emux conversion active status flag to indicate that one
            set of Emux conversion results are available to be sent for
            Notification [/cover] */
            lKernelDataPtr->EmuxConversionActiveFlag = ADC_EMUX_COMPLETED;
          }
          else
          {
            /* [cover parentID={B2951AA7-487D-4c1c-8B62-73BB10906133}]
            Set the Emux conversion active status flag to indicate that EMUX
            is idle, as conversion is completed and there is no notification
            pointer to send [/cover] */
            lKernelDataPtr->EmuxConversionActiveFlag = ADC_EMUX_IDLE;
          }
        }
        else
        #endif
        {
          /* [cover parentID={779BAC84-7797-4ee4-8AE4-FD084D4B1FB5}]
          Set the Emux conversion active status flag to indicate that EMUX is
          idle, as conversion is completed and notification is not enabled for
          the group or Group notification capability is not enabled [/cover]*/
          lKernelDataPtr->EmuxConversionActiveFlag = ADC_EMUX_IDLE;
        }
      }
    }
    else
    #endif
    {
      /* [cover parentID={3ECF3AE6-CDEB-4286-87C5-A9C4FF512140}]
      Update results to application buffers  [/cover] */
      Adc_lUpdateResBuffer(KernelId, lGroupId, CoreId);
      /* [cover parentID={A9781AFB-60FE-476b-987F-7466D4C57EA8}]
      Check for scheduling next group [/cover] */
      Adc_lGrpSequenceHandler(KernelId, lGroupId, RequestSrc, CoreId); 
    }
    /* [cover parentID={CDF31F5C-6E8E-41f8-9B59-2C70F4BAFF9E}]
    DMA Mode Result Handling is ON [/cover] */
    #else
      /* [cover parentID={21E31E08-AEA5-4154-905F-B382050CA361}]
      EMUX mode is ON [/cover]*/
      #if(ADC_EMUX_ENABLE == STD_ON)
      /* [cover parentID={6D595AC7-F9D4-4664-94CA-8B0A299F11A2}]
      Is Group configured with the EMUX channel [/cover] */
      if(lEmuxGrp == ADC_ONE_U)
      {
        const volatile Ifx_EVADC_G *lEvadcGroupPtr;
        lEvadcGroupPtr = &MODULE_EVADC.G[KernelId];
        Adc_ResultRegType lResReg;
        uint8 lCurrentEmuxChannel;
        lResReg = lGrpCfgPtr->GroupDefinition[0U].ResultReg;
        /* Read converted EMUX channel number */
        lCurrentEmuxChannel = lEvadcGroupPtr->RES[lResReg].B.EMUX;
        /* [cover parentID={1B91CCF3-C05D-48a2-921F-86FD2305A34A}]
        Are all the connected EMUX channels converted[/cover] */
        if(lCurrentEmuxChannel == (uint8)0U)
        {
          /* [cover parentID={57658B7C-38A7-4764-B938-E392397AD92E}]
          Set flag for number of streaming samples completed  [/cover] */
          Adc_lSetResBuffEndStatusAtomic(lKernelDataPtr, lGroupId);
          /* [cover parentID={BAE86353-BCB5-4d95-9B04-206B01866BB6}]
          Set flag for atleast one result sample avaialble [/cover] */
          Adc_lSetGroupResultAtomic(lKernelDataPtr, lGroupId);
          /* [cover parentID={E2671DE9-C6E1-4a35-8BFA-BD59BA6BEC4F}]
          Group Notify Capability is ON [/cover] */
          #if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
          /* [cover parentID={E66993F6-3AA2-4220-A613-8239F73AC16D}]
          Is Notification enabled for the Group [/cover] */
          if(Adc_lGetGroupNotifStatus(lKernelDataPtr, lGroupId) == \
                                                            (uint32)ADC_ONE_U)
          {
            /* [cover parentID={696ADF90-B0A5-4382-A4E7-15AA50BAEE74}]
            Is Notification pointer not equal to NULL pointer [/cover] */
            if(lGrpCfgPtr->NotifyPtr != NULL_PTR)
            {
              /* [cover parentID={EB018335-136A-4301-94FB-8865CC821BA8}]
              Set the Emux conversion active status flag to indicate that one
              set of Emux conversion results are available to be sent for
              Notification [/cover] */
              lKernelDataPtr->EmuxConversionActiveFlag = ADC_EMUX_COMPLETED;
            }
            else
            {
              /* [cover parentID={BFF07BDC-7207-4df3-BEE4-C16A583C8DDA}]
              Set the Emux conversion active status flag to indicate that EMUX
              is idle, as conversion is completed and there is no notification
              pointer to send [/cover] */
              lKernelDataPtr->EmuxConversionActiveFlag = ADC_EMUX_IDLE;
            }
          }
          else
          #endif
          {
            /* [cover parentID={F9CE16C0-012C-49b6-A362-EF69BFDBF0DB}]
            Set the Emux conversion active status flag to indicate that EMUX is
            idle, as conversion is completed and notification is not enabled for
            the group or Group notification capability is not enabled [/cover]*/
            lKernelDataPtr->EmuxConversionActiveFlag = ADC_EMUX_IDLE;
          }
        }
      }
      else
      #endif
      {
        /* [cover parentID={AC378BA0-4D5E-4beb-B4B2-780972AC40C1}]
        Set flag for number of streaming samples completed  [/cover] */
        Adc_lSetResBuffEndStatusAtomic(lKernelDataPtr, lGroupId);
        /* [cover parentID={71D03F64-F14A-4710-B17F-E8DB5B0B1A51}]
        Set flag for atleast one result sample avaialble [/cover] */
        Adc_lSetGroupResultAtomic(lKernelDataPtr, lGroupId);
      }
    #endif
    /* [cover parentID={28A065E7-2107-4dd6-B759-10E34ABFC781}]
    Group Notify Capability is ON [/cover] */
    #if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    /* [cover parentID={DDC0F9B5-0344-4a34-AD92-D551E148997A},
                       {2DEDFA3E-48DC-4f2c-AFB4-DBB2150DDD35}]
    Is Notification enabled for the Group [/cover] */
    if(Adc_lGetGroupNotifStatus(lKernelDataPtr, lGroupId) == (uint32)ADC_ONE_U)
    {
      /* [cover parentID={57A10656-34A5-444c-BE30-90999018F161}]
      EMUX mode is ON [/cover]*/
      #if(ADC_EMUX_ENABLE == STD_ON)
      /* [cover parentID={59217C92-6E7F-404e-943C-BAC3A7DC7D43}]
      Is Group configured with the EMUX channel [/cover] */
      if(lEmuxGrp == ADC_ONE_U)
      {
        /* [cover parentID={92805C52-6FAD-4f9e-940D-A28ECD5C4553}]
        Is one set of EMUX conversion results available [/cover] */
        if(lKernelDataPtr->EmuxConversionActiveFlag == ADC_EMUX_COMPLETED)
        {
          /* [cover parentID={D8E5D663-5442-455b-B296-8519A5922EA1}]
          Interrupt Mode Result Handling is ON [/cover] */
          #if(ADC_RESULT_HANDLING_IMPLEMENTATION != ADC_DMA_MODE_RESULT_HANDLING)
          /* [cover parentID={E5AF0BFB-1A64-45da-80AF-E51F89AD27FC}]
          Is Notification pointer not equal to NULL pointer [/cover] */
          if(lGrpCfgPtr->NotifyPtr != NULL_PTR)
          #endif
          {
            /* [cover parentID={98771DC0-0F18-45dc-B71E-9BDA74A31F14}]
            Call Notification function  [/cover] */
            lGrpCfgPtr->NotifyPtr();

            /* Set the Emux conversion active status flag to indicate that
            one set of EMUX conversion results are notified */
            lKernelDataPtr->EmuxConversionActiveFlag =
                                                  ADC_EMUX_RESULT_NOTIF_STATUS;
          }
        }
      }
      else
      #endif
      {
        /* [cover parentID={18AC48EE-9E98-419b-B42F-6CDF6C22CC58}]
        Is Notification pointer not equal to NULL pointer [/cover] */
        if(lGrpCfgPtr->NotifyPtr != NULL_PTR)
        {
          /* [cover parentID={0BF62050-2E53-4c67-A2C3-D6A2B2059F58}]
          Call Notification function  [/cover] */
          lGrpCfgPtr->NotifyPtr();
        }
      }
    }
    #endif
  }
  /* MISRA2012_RULE_8_13_JUSTIFICATION:Declaring pointer as a constant causes
  warings with compiler, hence it cannot be made const and not an issue*/
}

#if (ADC_ENABLE_LIMIT_CHECK==STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={1D9D7910-6C74-42e8-A76B-E2F8AA36BBFD}]      **
**                                                                            **
** Syntax           : static void Adc_lLimitChkEventHandler                   **
**                    (                                                       **
**                      const uint32 KernelId                                 **
**                      const Adc_GroupType GroupId                           **
**                      const uint32 CoreId                                   **
**                      const uint8 ReqSrc                                    **
**                    )                                                       **
**                                                                            **
** Description      : This function handles the channel event for a limit     **
**                    check group                                             **
** [/cover]                                                                   **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different ADC hardware groups             **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID for which the Interrupt handler    **
**                    is invoked                                              **
**                    GroupId - ADC Group ID of the Kernel                    **
**                    CoreId - Logical CPU core ID                            **
**                    ReqSrc - Request Source                                 **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Adc_lLimitChkEventHandler(const uint32 KernelId,\
                                      const Adc_GroupType GroupId,\
                                      const uint32 CoreId,\
                                      const uint8 ReqSrc)
{
  const Adc_GlobalDataType *lKernelDataPtr;
  #if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
  const Adc_GroupCfgType *lGrpCfgPtr;
  #endif

  /* Get global state data location for the Kernel */
  lKernelDataPtr = Adc_lGetKernelDataAddress(KernelId, CoreId);

  /* [cover parentID={1449C466-8EEC-4b37-BFD0-EB7A9DF5D857}]
  Is Interrupt Service Routine flag is equal to ZERO [/cover] */
  if(lKernelDataPtr->RSData[ReqSrc].IsrNoServiceFlag == (uint8)0U)
  {
    /* [cover parentID={03536338-C488-4eba-8957-65234384D6F8}]
    Update results to application buffers  [/cover] */
    Adc_lUpdateResBuffer(KernelId, GroupId, CoreId);
    /* [cover parentID={EA27913E-9BF5-40f6-B8E2-FEE19549E8DD}]
    Check for scheduling next group [/cover] */
    Adc_lGrpSequenceHandler(KernelId, GroupId, ReqSrc, CoreId);

    /* [cover parentID={5DABFA75-0E86-410b-B20F-8A7F08594C2F}]
    Group Notify Capability is ON [/cover] */
    #if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    /* [cover parentID={A4CA4D43-16D9-4b56-866C-1EEF592F0C0C}]
    Is Notification enabled for the Group [/cover] */
    if(Adc_lGetGroupNotifStatus(lKernelDataPtr, GroupId) == (uint32)ADC_ONE_U)
    {
      /* [cover parentID={2E8EE1E3-4044-4c69-AE1B-C35F947B3782}]
      Read the Grp config pointer [/cover] */
      lGrpCfgPtr = &(Adc_ConfigPtr->CoreCfgPtr[CoreId]->\
                     HwUnitCfgPtr[KernelId]->GrpCfgPtr[GroupId]);

      /* [cover parentID={17ACF50A-C4E9-4bcc-9C33-6A8AFD53ECC4}]
      Is Notofication pointer not equal to NULL pointer [/cover] */
      if(lGrpCfgPtr->NotifyPtr != NULL_PTR)
      {
        /* [cover parentID={7C9959B9-1927-4ecd-BF60-5FF6C25397E0}]
        Call Notification function  [/cover] */
        lGrpCfgPtr->NotifyPtr();
      }
    }
    #endif
  }
}
#endif

#if(ADC_RESULT_HANDLING_IMPLEMENTATION != ADC_DMA_MODE_RESULT_HANDLING)
/*******************************************************************************
** Traceability: [cover parentID={196FEE90-357A-454e-A7B4-8C56521A8A32}]      **
**                                                                            **
** Syntax           : static void Adc_lUpdateResBuffer                        **
**                    (                                                       **
**                      const uint32 KernelId                                 **
**                      const Adc_GroupType  GroupId                          **
**                      const uint32 CoreId                                   **
**                    )                                                       **
**                                                                            **
** Description      : This function Updates the Group Result buffer on        **
**                    conversion completion                                   **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different ADC hardware groups             **
**                                                                            **
** Parameters(in)   : KernelId  - ADC Kernel to which the group belongs       **
**                    GroupId   - ADC Group ID of the Kernel                  **
**                    CoreId    - Logical CPU core ID                         **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Adc_lUpdateResBuffer(const uint32 KernelId,\
                                 const Adc_GroupType GroupId,\
                                 const uint32 CoreId)
{

  const volatile Ifx_EVADC_G *lEvadcGroupPtr;
  Adc_GlobalDataType *lKernelDataPtr;
  const Adc_GroupCfgType *lGrpCfgPtr;
  Adc_ValueGroupType *lCurrentBufferPtr;
  Adc_StreamNumSampleType lNumOfSamples, lCurrentBufLocation;
  Adc_ResultRegType lResReg;
  uint8 lNoOfChannels, lCount;

  lEvadcGroupPtr = &MODULE_EVADC.G[KernelId];
  lKernelDataPtr = Adc_lGetKernelDataAddress(KernelId, CoreId);

  /* Get group related confiuration data */
  lGrpCfgPtr = &(Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[KernelId]->\
                 GrpCfgPtr[GroupId]);
  lNumOfSamples = lGrpCfgPtr->NumOfSamples;
  lNoOfChannels = lGrpCfgPtr->NoOfChannels;
  lResReg = lGrpCfgPtr->GroupDefinition[0U].ResultReg;

  /* Get the buffer location where results are to be written */
  lCurrentBufLocation = lKernelDataPtr->NumofValidConRes[GroupId];
  /* [cover parentID={3AE43E27-1847-4ee4-A061-128A086D9543}]
  Is Current Buffer position is equal to Number of Samples [/cover] */
  if(lCurrentBufLocation == lNumOfSamples)
  {
    /* [cover parentID={DDF88911-C460-4f55-BDA8-E5ADE3655020}]
    Reset the Current Buffer position to start of Buffer [/cover] */
    lCurrentBufLocation = (Adc_StreamNumSampleType)0U;
  }
  /*
   Application Result Buffer organisation for
   a)
   - 5 Channels - CH9, CH1, CH2, CH3 and CH4
   - 3 streaming samples for each channel
   - No synchronous conversion kernels

    Buffer Start                                       Buffer End
    +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    |CH9|CH9|CH9|CH1|CH1|CH1|CH2|CH2|CH2|CH3|CH3|CH3|CH4|CH4|CH4|
    +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+

    b)
   - 3 Channels - CH9, CH1, and CH2
   - 2 streaming samples for each channel
   - Kernel K0 synchronization master, kernel K1 and K2 synchronization slaves
   - Channels CH9 and CH2 enabled for synchronous conversion

    Buffer Start
    +-----+-----+-----+-----+-----+-----+    +-----+-----+-----+-----+
    |K0CH9|K0CH9|K0CH1|K0CH1|K0CH2|K0CH2| => |K1CH9|K1CH9|K1CH2|K1CH2| =>
    +-----+-----+-----+-----+-----+-----+    +-----+-----+-----+-----+

                      Buffer End
       +-----+-----+-----+-----+
    => |K2CH9|K2CH9|K2CH1|K2CH1|
       +-----+-----+-----+-----+

    c)
   - 3 Channels - CH9, CH1, and CH2
   - 2 streaming samples for each channel
   - Kernel K1 synchronization master, kernel K0 and K3 synchronization slaves
   - Channels CH1 and CH2 enabled for synchronous conversion

    Buffer Start
    +-----+-----+-----+-----+-----+-----+    +-----+-----+-----+-----+
    |K1CH9|K1CH9|K1CH1|K1CH1|K1CH2|K1CH2| => |K0CH1|K0CH1|K0CH2|K0CH2| =>
    +-----+-----+-----+-----+-----+-----+    +-----+-----+-----+-----+

                      Buffer End
       +-----+-----+-----+-----+
    => |K3CH1|K3CH1|K3CH2|K3CH2|
       +-----+-----+-----+-----+
  */

  /* [cover parentID={FCCA9CFB-9EAF-4c00-942C-88F2A8E6A27B}]
  Calculate the Current Buffer address to copy the results [/cover] */
  lCurrentBufferPtr = lKernelDataPtr->GrpResBuffer[GroupId];
  lCurrentBufferPtr = &lCurrentBufferPtr[lCurrentBufLocation];

  /* [cover parentID={08CC8E75-B377-4b35-9395-3380AF95098B}]
  Until the last channel in the group [/cover] */
  for(lCount = 0U; lCount < lNoOfChannels; lCount++)
  {
    /* [cover parentID={491E801B-9AE5-4062-B199-707D8771A974}]
    Mask the conversion result and copy result from register to the Data Buffer
    [/cover] */
    lCurrentBufferPtr[(uint32)lCount*(uint32)lNumOfSamples] = \
              (Adc_ValueGroupType)((uint32)lEvadcGroupPtr->RES[lResReg].U &\
                                   (uint32)ADC_12BIT_RESULT_MASK);
    lResReg++;
  }

  /* [cover parentID={D6464051-DAF4-444b-A015-5798EA3228E7}]
  Sync Conversion is on [/cover] */
  #if (ADC_SYNC_CONV_ENABLE == STD_ON)
  /* [cover parentID={1ABA0FE7-36DA-45ab-A83D-B544A5210874}]
  Channel configured for sync conversion [/cover] */
  if (lGrpCfgPtr->SyncChannelMask != (uint16)0U)
  {
    lCurrentBufferPtr = &lCurrentBufferPtr[(uint32)lNoOfChannels *\
                                           (uint32)lNumOfSamples];
    /* [cover parentID={2FF2A99E-3750-4310-9F82-6C863D31081D}]
    Update slave result buffer [/cover] */
    Adc_lUpdateSlaveResult(KernelId, GroupId, lCurrentBufferPtr, CoreId);
  }
  #endif

  /*Increment the number of valid conversions available */
  lCurrentBufLocation++;

  /*Set the next buffer position of the Application result buffer,
    also incidcates the number of result samples available */
  lKernelDataPtr->NumofValidConRes[GroupId] = lCurrentBufLocation;

  /* [cover parentID={278B1A22-175B-475a-AC03-7C21852162C1}]
  Update Group result status  [/cover] */
  /* Set the flag for atleast one result sample avaialble */
  Adc_lSetGroupResultAtomic(lKernelDataPtr, GroupId);

  /* [cover parentID={11E94302-20A6-48c6-B354-920A9D50E4BC}]
  Are Configured Number of streaming samples available [/cover] */
  if(lCurrentBufLocation == lNumOfSamples)
  {
    /* [cover parentID={E84AFDE5-9DDA-48c3-95AF-5EFC5F4E5130}]
    Set End Result Buffer Status  [/cover] */
    /*Set the flag for number of streaming samples completed,
      if the streaming sample set is completed*/
    Adc_lSetResBuffEndStatusAtomic(lKernelDataPtr, GroupId);
  }
}
#endif

#if ((ADC_EMUX_ENABLE == STD_ON) &&\
(ADC_RESULT_HANDLING_IMPLEMENTATION != ADC_DMA_MODE_RESULT_HANDLING))
/*******************************************************************************
** Traceability: [cover parentID={BB9BC317-A3A2-457b-8876-C8B921184248}]      **
**                                                                            **
** Syntax           : static void Adc_lUpdateEmuxResBuffer                    **
**                    (                                                       **
**                      const uint32 KernelId                                 **
**                      const Adc_GroupType  GroupId                          **
**                      const uint32 CoreId                                   **
**                    )                                                       **
**                                                                            **
** Description      : This function Updates the Emux Group Result buffer on   **
**                    conversion completion                                   **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different ADC hardware groups             **
**                                                                            **
** Parameters(in)   : KernelId  - ADC Kernel to which the group belongs       **
**                    GroupId   - ADC Group ID of the Kernel                  **
**                    CoreId    - Logical CPU core ID                         **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Adc_lUpdateEmuxResBuffer(const uint32 KernelId,\
                                 const Adc_GroupType GroupId,\
                                 const uint32 CoreId)
{

  const volatile Ifx_EVADC_G *lEvadcGroupPtr;
  Adc_GlobalDataType *lKernelDataPtr;
  const Adc_GroupCfgType *lGrpCfgPtr;
  Adc_ValueGroupType *lCurrentBufferPtr;
  Adc_StreamNumSampleType lNumOfSamples, lCurrentBufLocation;
  Adc_ResultRegType lResReg;
  uint8 lCurrentEmuxChannel;

  lEvadcGroupPtr = &MODULE_EVADC.G[KernelId];
  lKernelDataPtr = Adc_lGetKernelDataAddress(KernelId, CoreId);

  /* Get group related confiuration data */
  lGrpCfgPtr = &(Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[KernelId]->\
                 GrpCfgPtr[GroupId]);

  lNumOfSamples = lGrpCfgPtr->NumOfSamples;
  lResReg = lGrpCfgPtr->GroupDefinition[0U].ResultReg;

  /* Get the buffer location where results are to be written */
  lCurrentBufLocation = lKernelDataPtr->NumofValidConRes[GroupId];

  /* [cover parentID={5C87F864-3D75-4220-A3F1-12171EBFEC8A}]
  Is Current Buffer position is equal to Number of Samples [/cover] */
  if(lCurrentBufLocation == lNumOfSamples)
  {
    /* [cover parentID={C5D23B49-824D-4f99-AAEB-A1A30582F872}]
    Reset the Current Buffer position to start of Buffer [/cover] */
    lCurrentBufLocation = (Adc_StreamNumSampleType)0U;
  }

  /* [cover parentID={9490F2E7-381D-4eaf-B955-096FEB0F11F5}]
  Calculate the Current Buffer address to copy the results [/cover] */
  lCurrentBufferPtr = lKernelDataPtr->GrpResBuffer[GroupId];
  lCurrentBufferPtr = &lCurrentBufferPtr[lCurrentBufLocation];

  /* [cover parentID={1237BA29-140B-48ac-B73C-B5E181BB248F}]
  Read results of each EMUX channels and update result buffer [/cover] */
  lCurrentEmuxChannel = lEvadcGroupPtr->RES[lResReg].B.EMUX;
  lCurrentBufferPtr[lCurrentEmuxChannel*(uint32)lNumOfSamples] = \
    (Adc_ValueGroupType)((uint32)lEvadcGroupPtr->RES[lResReg].U &\
                                   (uint32)ADC_12BIT_RESULT_MASK);

  /* [cover parentID={225D1CEA-4BCF-482f-A8EB-08286B1A7378}]
  Are all the connected EMUX channels converted [/cover]*/
  if(lCurrentEmuxChannel == 0U)
  {
    /* [cover parentID={2049BBAD-8EC2-49b9-BD11-AF56AE506768}]
    Increment the number of valid conversions available [/cover]*/
    lCurrentBufLocation++;

    /*Set the next buffer position of the Application result buffer,
    also incidcates the number of result samples available */
    lKernelDataPtr->NumofValidConRes[GroupId] = lCurrentBufLocation;

    /* [cover parentID={9E816A47-DF44-425b-8C4F-E48F0888661B}]
    Update Group result status  [/cover] */
    Adc_lSetGroupResultAtomic(lKernelDataPtr, GroupId);

    /* Set the Emux conversion active status flag to indicate that one set of
    Emux conversion results are available */
    lKernelDataPtr->EmuxConversionActiveFlag = ADC_EMUX_COMPLETED;

    /* [cover parentID={999514E6-0E87-45d1-B909-85F7AACDB2A4}]
    Are Configured Number of streaming samples available [/cover] */
    if(lCurrentBufLocation == lNumOfSamples)
    {
      /* [cover parentID={3B45F7AC-3D43-40e7-8F33-021244E0A6E9}]
      Set End Result Buffer Status  [/cover] */
      /*Set the flag for number of streaming samples completed,
      if the streaming sample set is completed*/
      Adc_lSetResBuffEndStatusAtomic(lKernelDataPtr, GroupId);
      
      /* Set the Emux conversion active status flag to indicate that all sets of
      Emux conversion results are available */
      lKernelDataPtr->EmuxConversionActiveFlag = ADC_EMUX_STREAM_COMPLETED;
    }
  }
}
#endif

#if (ADC_SYNC_CONV_ENABLE == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={1876477F-CB8B-43dc-9538-EC21842F79CA}]      **
**                                                                            **
** Syntax           : static void Adc_lUpdateSlaveResult                      **
**                    (                                                       **
**                      const uint32 KernelId                                 **
**                      const Adc_GroupType  GroupId                          **
**                      Adc_ValueGroupType* const CurrentResBufPtr            **
**                      const uint32 CoreId                                   **
**                    )                                                       **
**                                                                            **
** Description      : This function Updates the Group Result buffer of        **
**                    synchronous conversion slaves                           **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different ADC hardware groups             **
**                                                                            **
** Parameters(in)   : KernelId  - ADC Kernel to which the group belongs       **
**                    GroupId   - ADC Group ID of the Kernel                  **
**                    CoreId    - Logical CPU core ID                         **
**                                                                            **
** Parameters (out) : CurrentResBufPtr - Pointer to result buffer for first   **
**                                       slave channel                        **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Adc_lUpdateSlaveResult(const uint32 KernelId,\
                                   const Adc_GroupType GroupId,\
                                   Adc_ValueGroupType * const CurrentResBufPtr,\
                                   const uint32 CoreId)
{
  const Ifx_EVADC_G *lEvadcGroupPtr;
  const Adc_HwUnitCfgType * lHwUnitCfgPtr;
  const Adc_GroupCfgType *lGrpCfgPtr;
  const Adc_GroupDefType *lGrpDefCfgPtr;
  uint32 lCurrentBufLocation;
  uint8 lKernelCount, lSlaveKernel;
  Adc_StreamNumSampleType lNumOfSamples;
  Adc_ResultRegType lResReg;
  Adc_ChannelType lChannelId, lAnChannelId;

  /*Get the base address of the group configuration */
  lGrpCfgPtr = &(Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[KernelId]->\
                 GrpCfgPtr[GroupId]);
  lNumOfSamples = lGrpCfgPtr->NumOfSamples;
  lCurrentBufLocation = (uint32)0U;

  /* Get the base address of the group definition */
  lGrpDefCfgPtr = lGrpCfgPtr->GroupDefinition;

  /* Get the base address of the kernel configuration */
  lHwUnitCfgPtr = Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[KernelId];

  /* [cover parentID={0E764F77-9236-4bbc-A3AA-132904ED7151}]
  Till the last available Kernel [/cover] */
  for (lKernelCount = (uint8)0U;
       lKernelCount < (uint8)(ADC_KERNELS_PER_SYNGRP - 1U); lKernelCount++)
  {
    /* [cover parentID={F7ADFC49-06B3-459c-B245-EB558CA78924}]
    Read slave kernel from hardware unit config pointer [/cover] */
    lSlaveKernel = lHwUnitCfgPtr->SlaveKernels[lKernelCount];
    /* [cover parentID={C88CAC4C-086E-4761-951D-BC0B73DA1651}]
    Valid slave kernel [/cover] */
    if (lSlaveKernel != ADC_INVALID_KERNEL_ID)
    {
      /*Get the SFR base address for the kernel */
      lEvadcGroupPtr = &MODULE_EVADC.G[lSlaveKernel];

      lChannelId = (Adc_ChannelType)0U;

      /* [cover parentID={445AB149-299C-4ff7-AF14-03E31A801224}]
      Till the last available channel [/cover] */
      do
      {
        /* Get the analog channel number */
        lAnChannelId = lGrpDefCfgPtr[lChannelId].AnalogChannelNo;
        lResReg = lGrpDefCfgPtr[lChannelId].ResultReg;

        if ((lGrpCfgPtr->SyncChannelMask &
             (uint16)((uint32)ADC_ONE_U << lAnChannelId)) != (uint16)0U)
        {
          /* [cover parentID={0B4042CF-9FD4-4bd7-829B-01CD5324A639}]
          Update the result buffer [/cover] */
          CurrentResBufPtr[lCurrentBufLocation] = \
                (Adc_ValueGroupType)((uint32)lEvadcGroupPtr->RES[lResReg].U &\
                                     (uint32)ADC_12BIT_RESULT_MASK);
          lCurrentBufLocation += lNumOfSamples;
        }

        lChannelId++;
      } while (lChannelId < lGrpCfgPtr->NoOfChannels);
    }
  }
}
#endif

#if ((ADC_READ_GROUP_API == STD_ON) &&\
     (ADC_RESULT_HANDLING_IMPLEMENTATION != ADC_DMA_MODE_RESULT_HANDLING) &&\
     (ADC_SYNC_CONV_ENABLE == STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={E6DF4EAB-6510-42e8-8CCC-F7EE74A23211}]      **
**                                                                            **
** Syntax           : static void Adc_lReadlaveResult                         **
**                    (                                                       **
**                      const uint32 KernelId                                 **
**                      const Adc_GroupCfgType* const GrpCfgPtr               **
**                      const Adc_ValueGroupType* ResultBufPtr                **
**                      Adc_ValueGroupType* const DataBufPtr                  **
**                      const uint32 CoreId                                   **
**                    )                                                       **
**                                                                            **
** Description      : This function reads the slave kernel conversion results **
**                    of the last conversion round from the streaming buffer. **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different ADC hardware groups             **
**                                                                            **
** Parameters(in)   : KernelId     - ADC Kernel to which the group belongs    **
**                    GrpCfgPtr    - Pointer to group configuration           **
**                    ResultBufPtr - Pointer to start of slave results in     **
**                                   the groups result buffer                 **
**                    CoreId       - Logical CPU core ID                      **
**                                                                            **
** Parameters (out) : DataBufPtr   - Pointer to data buffer for first slave   **
**                                   slave                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Adc_lReadSlaveResult(const uint32 KernelId,\
                                 const Adc_GroupCfgType* const GrpCfgPtr,\
                                 const Adc_ValueGroupType* const ResultBufPtr,\
                                 Adc_ValueGroupType* const DataBufPtr,\
                                 const uint32 CoreId)
{
  const Adc_HwUnitCfgType * lHwUnitCfgPtr;
  const Adc_GroupDefType *lGrpDefCfgPtr;
  uint32 lCurResBufLocation;
  uint8 lKernelCount;
  Adc_StreamNumSampleType lNumOfSamples, lCurDataBufLocation;
  Adc_ChannelType lChannelId, lAnChannelId;

  lNumOfSamples = GrpCfgPtr->NumOfSamples;
  lCurDataBufLocation = (Adc_StreamNumSampleType)0U;
  lCurResBufLocation = (uint32)0U;

  /* Get the base address of the group definition */
  lGrpDefCfgPtr = GrpCfgPtr->GroupDefinition;

  /* Get the base address of the kernel configuration */
  lHwUnitCfgPtr = Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[KernelId];

  /* [cover parentID={46983F5F-D89E-4e48-B33E-4CAAD78E3797}]
  Till the last slave kernel [/cover] */
  for (lKernelCount = (uint8)0U;
       lKernelCount < (uint8)(ADC_KERNELS_PER_SYNGRP - 1U); lKernelCount++)
  {
    /* [cover parentID={ACEFA154-95B2-4ea3-9FE8-5CC412540F2C}]
    Is valid Slave kernel [/cover] */
    if (lHwUnitCfgPtr->SlaveKernels[lKernelCount] != ADC_INVALID_KERNEL_ID)
    {
      lChannelId = (Adc_ChannelType)0U;

      /* [cover parentID={9A79F664-EC81-4522-A205-B9CBB2DBB5CD}]
      Till the total number of channels available and valid Sync channel
      [/cover] */
      do
      {
        /* Get the analog channel number */
        lAnChannelId = lGrpDefCfgPtr[lChannelId].AnalogChannelNo;

        if ((GrpCfgPtr->SyncChannelMask &
             (uint16)((uint32)ADC_ONE_U << lAnChannelId)) != (uint16)0U)
        {
          /* [cover parentID={5E9101F2-0590-4769-86EA-5154F238A7F0}]
          Copy the results of channel to application buffer [/cover] */
          DataBufPtr[lCurDataBufLocation] = ResultBufPtr[lCurResBufLocation];
          lCurDataBufLocation++;
          lCurResBufLocation += lNumOfSamples;
        }

        lChannelId++;
      } while (lChannelId < GrpCfgPtr->NoOfChannels);
    }
  }
}
#endif

#if(ADC_RESULT_HANDLING_IMPLEMENTATION != ADC_DMA_MODE_RESULT_HANDLING)
/*******************************************************************************
** Traceability: [cover parentID={F70A3470-2E4C-4901-8D69-F6E7FBB7D9A4}]      **
**                                                                            **
** Syntax           : static void Adc_lGrpSequenceHandler                     **
**                    (                                                       **
**                     const uint32 KernelId                                  **
**                     const Adc_GroupType  GroupId                           **
**                     const uint8 ReqSrc                                     **
**                     const uint32 CoreId                                    **
**                    )                                                       **
**                                                                            **
** Description      : This function stops the conversion of Implicit stop     **
**                    groups and schedules the next group in the queue.       **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different ADC hardware groups             **
**                                                                            **
** Parameters(in)   : KernelId  - ADC Kernel to which the group belongs       **
**                    GroupId   - ADC Group ID of the Kernel                  **
**                    ReqSrc    - Request Source                              **
**                    CoreId    - Logical CPU core ID                         **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
static void Adc_lGrpSequenceHandler(const uint32 KernelId,\
          const Adc_GroupType GroupId, const uint8 ReqSrc, const uint32 CoreId)
{
  Adc_GlobalDataType *lKernelDataPtr;
  const Adc_GroupCfgType *lGrpCfgPtr;
  uint32 lStrmCompletedFlag;

  /* Get group configuration address */
  lGrpCfgPtr = &(Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[KernelId]->\
                 GrpCfgPtr[GroupId]);
  /* Get global state data location for the Kernel */
  lKernelDataPtr =  Adc_lGetKernelDataAddress(KernelId, CoreId);
  /* [cover parentID={56EAC32B-C3E8-4b7d-A422-3193AB2085F0}]
  Read result buffer end status [/cover] */
  lStrmCompletedFlag = Adc_lGetResBuffEndStatus(lKernelDataPtr, GroupId);

  /* [cover parentID={A8456180-759D-4fd5-ACB4-6BB52C08B90F}]
  Is SW Trigger & One shot conv mode or
  Linear buffer & Streaming samples completed [/cover] */
  /* [cover parentID={A8456180-759D-4fd5-ACB4-6BB52C08B90F}]
  Group to be checked for stopping in the RS ISR (Implicit Stop Groups)
  SW TRIGGGER ONE SHOT - HW or SW trigger with LINEAR buffer and Streaming
  Samples completed [/cover] */
  if( ((lGrpCfgPtr->TriggerSource == ADC_TRIGG_SRC_SW) && \
       (lGrpCfgPtr->ConvMode == ADC_CONV_MODE_ONESHOT)) || \
      ((lGrpCfgPtr->StreamMode == ADC_STREAM_BUFFER_LINEAR) && \
       (lStrmCompletedFlag == (uint32)ADC_ONE_U))\
    )
  {
    lKernelDataPtr->RSData[ReqSrc].IsrNoServiceFlag = (uint8)ADC_ONE_U;

    /* SW TRIG ONE SHOT groups are not queued in refill mode,
       hence no need to stop them explicity.*/
    /* [cover parentID={BB700151-0B60-4757-8788-9E0920F99273}]
    Is SW Trigger & One shot conv mode [/cover] */
    if((lGrpCfgPtr->TriggerSource == ADC_TRIGG_SRC_SW) && \
        (lGrpCfgPtr->ConvMode == ADC_CONV_MODE_ONESHOT))
    {
      /* [cover parentID={1D938EE7-2D67-4105-A588-CAF7521BED22}]
      Clear Channel and Result registers [/cover] */
      Adc_lClearGroupSfr(lGrpCfgPtr, KernelId, ReqSrc);
    }
    else
    {
      /* Stop the conversion, flush the queue, reset registers for groups
      queued in refill mode */
      /* [cover parentID={D48FF423-4B19-44c5-BFC8-4A9DC59FE843}]
      Stop Conversion Request [/cover] */
      Adc_lStopConvRequest(lGrpCfgPtr, KernelId, ReqSrc);
    }

    /* Clear Kernel Data variable */
    Adc_lRemoveActiveGroup(lKernelDataPtr, lGrpCfgPtr, ReqSrc);
    /* [cover parentID={1AD08973-67C9-41aa-B9C7-B4D1694AE1BF}]
    Sync Conversion is ON or Priority mode is OFF [/cover] */
    #if ((ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) ||\
         (ADC_SYNC_CONV_ENABLE == STD_ON))
    /* [cover parentID={1252DA55-FCC7-4ac6-BE57-16BBBFB3B91B}]
    Critical Section [/cover] */
    /* [cover parentID={725092E2-523D-4f37-B618-8FF65023E15A}]
    Start of Critical Section [/cover] */
    SchM_Enter_Adc_KernelData();
    /* [cover parentID={B83EF8EF-DAE1-41df-94BC-1DA1651BC633}]
    Clears the Slave running channels [/cover] */
    Adc_lClrRunningChAndResReg(KernelId, lGrpCfgPtr, CoreId);

    /* [cover parentID={75130436-373E-4d5c-8B4C-DF3371F8A894}]
    Priority Mode is ON [/cover] */
    #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
    /* [cover parentID={2B919AB5-918D-404d-91DD-746716338498}]
    Limit Check is ON [/cover] */
    #if (ADC_ENABLE_LIMIT_CHECK==STD_ON)
    /* [cover parentID={593D41A9-C6AC-4e84-AF5A-961FC39076AA}]
    Is Group enabled with limit check? [/cover] */
    if ((uint8)ADC_ONE_U == lGrpCfgPtr->LimitCheckGroup)
    {
      /* [cover parentID={DFDC6778-D4B7-4ddb-A187-BF9EB68B9439}]
      Reset limit check active status flag [/cover] */
      lKernelDataPtr->LimitChkActiveFlag = (uint8)0U;
    }
    #endif

    /* [cover parentID={F03197F5-06FC-4608-8D1D-7D7FD6CC9405}]
    Is the group configured for alias? [/cover] */
    if (ADC_ALIAS_DEFAULT_VALUE != lGrpCfgPtr->AliasChCfg)
    {
      /* [cover parentID={206525D5-4B31-4e9f-89F3-C5BAFB2B33A6}]
      Reset alias active status flag [/cover] */
      lKernelDataPtr->AliasActiveFlag = (uint8)0U;
    }
    #endif

    /* [cover parentID={DB4F2119-5355-42f0-AA4A-438B21257240}]
    End of Critical Section [/cover] */
    SchM_Exit_Adc_KernelData();
    #endif

    /* Change groups status to not converting, only busy flag is reset.
      Result flags and count are not cleared, since results will be read later
      by application using ReadGroup or GetStreamLastPointer */
    Adc_lClrGroupStatusBusyAtomic(lKernelDataPtr, GroupId);

    /* [cover parentID={D851119B-1116-40c5-A842-192262998B99}]
    Hw Priority is ON or Queue Mode is ON [/cover] */
    #if((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW) ||\
        (ADC_ENABLE_QUEUING == STD_ON))
    /* [cover parentID={6F28C8C0-E0DD-4e8a-9AC5-A4DEEC5B00A1}]
    Remove Group from the queue [/cover] */
    Adc_lRemoveFromQueue(KernelId, lKernelDataPtr, GroupId, CoreId);
    /* [cover parentID={D6B00E04-C6D4-4884-B104-DB89EBAD1591}]
    Enable Start Stop Group API is on [/cover] */
    #if(ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
    /* If SW queue has more groups, schedule it for conversion*/
    /* [cover parentID={6BFF04AF-B86E-45cd-97EE-0F4EC6AE2C21}]
    Is SW queue has more Groups [/cover] */
    if(lKernelDataPtr->RSData[ReqSrc].PopGroupId != ADC_INVALID_GROUP_ID)
    {
      /* [cover parentID={C16EA876-3F53-4639-9C7F-EB1F834BAE92}]
      Schedule Group for conversion [/cover] */
      Adc_lScheduleFromQueue(KernelId,CoreId,ReqSrc);
    }
    #endif
    /* [cover parentID={0D542A96-B625-4b79-AF40-075BD7964A92}]
    HW-SW Priority is on and Enable start stop group API is on [/cover] */
    #elif((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)&&\
          (ADC_ENABLE_START_STOP_GROUP_API == STD_ON))

    /* [cover parentID={806CEC92-F9FF-4f35-8FD9-89A7B3F1C3A2}]
    Critical Section [/cover] */
    /* [cover parentID={70762A9E-D123-4645-987D-559FB9D5679D}]
    Start of Critical Section [/cover] */
    SchM_Enter_Adc_KernelData();
    /* [cover parentID={B8D493E6-0AE8-441b-AF41-DC09DFFF26AD}]
    Schedule next highest priority group for conversion [/cover] */
    Adc_lScheduleNext(KernelId, CoreId, ReqSrc);

    /* [cover parentID={67BA9EE9-6933-4278-BCDB-79ACC1B138FA}]
    End of Critical Section [/cover] */
    SchM_Exit_Adc_KernelData();
    #endif
  }
}
#endif

#if(ADC_LOW_POWER_STATE_SUPPORT == STD_ON)
/*******************************************************************************
** Traceability: [cover parentID={B43307B4-18AF-40be-AF61-4A96D5C4DEA5}]      **
**                                                                            **
** Syntax           : static uint8 Adc_lGetCurrentPwrState                    **
**                    (                                                       **
**                      const uint8 ServiceId,                                **
**                      const uint32 CoreId                                   **
**                    )                                                       **
**                                                                            **
** Description      : This function returns the current power state of the ADC**
**                    hardware groups used by the calling core and reports    **
**                    safety error if current power state is not available in **
**                    the configured power modes.                             **
**                    Note: This API is available only when                   **
**                          AdcLowPowerStatesSupport is configured as true.   **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different CPU cores                       **
**                                                                            **
** Parameters(in)   : ServiceId - Service ID of the API                       **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters(out)   :None                                                    **
**                                                                            **
** Return value     : 0 to 3 - Current Power States of ADC hardware units     **
**                    ADC_INVALID_POWER_STATE - Power state not available in  **
**                                              the configured power modes    **
*******************************************************************************/
static uint8 Adc_lGetCurrentPwrState(const uint8 ServiceId, const uint32 CoreId)
{
  uint32 lKernelCount;
  uint32 lCurrentPwrState = (uint32)0U;

  /* [cover parentID={74587DEC-86DC-4ce8-BED7-2FD80E863C39}]
  Till the first Master or Stand-alone kernel configured to current core
  [/cover] */
  for(lKernelCount=(uint32)0U; lKernelCount<ADC_MAX_KERNEL_ID; lKernelCount++)
  {
    /* [cover parentID={74587DEC-86DC-4ce8-BED7-2FD80E863C39}]
    Till the first Master or Stand-alone kernel configured to current core
    [/cover] */
    if(Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[lKernelCount] != \
        NULL_PTR)
    {
      /* [cover parentID={74587DEC-86DC-4ce8-BED7-2FD80E863C39}]
      Till the first Master or Stand-alone kernel configured to current core
      [/cover] */
      if(Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[lKernelCount]->\
                                       SyncConvMode != ADC_SYNC_CONV_MODE_SLAVE)
      {
        /* [cover parentID={1AB5CD7F-77F8-4554-86CC-CAD7BBF94CF6}]
        Read the current power state [/cover] */
        lCurrentPwrState = MODULE_EVADC.G[lKernelCount].ARBCFG.B.ANONS;
        lCurrentPwrState = (ADC_TARGET_POWER_STATE_MASK & (~lCurrentPwrState));
        break;
      }
    }
  }

  /* [cover parentID={023A8D73-147A-4553-B521-635D48E1A2B1}]
  Is power state not available in the configured core ? [/cover] */
  if((((uint32)ADC_ONE_U<<lCurrentPwrState)&(uint32)ADC_POWER_MODES_AVAILABLE)\
                                                                  == (uint32)0U)
  {
    /* [cover parentID={AA9ECD8F-2E9E-4eea-A6DA-0A67808E05ED}]
    Safety is ON [/cover] */
    #if (ADC_SAFETY_ENABLE == STD_ON)
    /* [cover parentID={5F4AEDD9-5459-46a1-A930-E7B70D2F6E89}]
    Report Safety error if power state read corresponds to invalid range
    [/cover] */
    Mcal_ReportSafetyError(ADC_MODULE_ID, ADC_MODULE_INSTANCE, ServiceId, \
                           ADC_SE_POWER_STATE_INVALID);
    #endif
    UNUSED_PARAMETER(ServiceId);

    /* Updatecurrent power state with invalid power state */
    lCurrentPwrState = ADC_INVALID_POWER_STATE;
  }
  return((uint8)lCurrentPwrState);
}
#endif

#if ((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={620D4BCB-150C-4fe5-8EDC-267826AA61FD}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lInitDetCheck                    **
**                    (                                                       **
**                       const Adc_ConfigType * const ConfigPtr,              **
**                       const uint32 CoreId                                  **
**                    )                                                       **
**                                                                            **
** Description      :This function is to check all the DETs for Adc_Init API  **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : ConfigPtr - Pointer to the config root                  **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lInitDetCheck(const Adc_ConfigType *const ConfigPtr, \
                                     const uint32 CoreId)
{
  uint8 lErrVal = ADC_E_NO_ERR;
  /* [cover parentID={D1CB56D8-C20D-493e-92C7-29B6C03E7EFE}]
  Number of Cores available are greater than one and Current CoreId is not equal
  to the Master CoreId [/cover]*/
  #if (MCAL_NO_OF_CORES > ADC_ONE_U)
  if (MCAL_MASTER_COREID != CoreId)
  {
    /* [cover parentID={7E1F2432-4BCD-49d9-BD54-B03D992A4BD0}]
    MultiCore Error Detection is on or Safety is on [/cover] */
    #if ((ADC_MULTICORE_ERROR_DETECT == STD_ON)||(ADC_SAFETY_ENABLE == STD_ON))
    /* [cover parentID={4666CFFE-D35D-4599-85CE-F7BD11280347}]
    Is Master Core Initialized [/cover] */
    if (Adc_InitStatus[MCAL_MASTER_COREID] != ADC_INITIALIZED)
    {
      lErrVal = ADC_E_MASTER_CORE_UNINIT;
      /* [cover parentID={95E73AF5-75B1-4f98-AAF6-D3D901CB5211}]
      Report ADC_E_MASTER_CORE_UNINIT DET  [/cover] */
      Adc_lReportMulticoreError(ADC_SID_INIT, ADC_E_MASTER_CORE_UNINIT);
    }
    /* [cover parentID={6DBCF186-3D8B-4d9b-A09B-BC4EB5600320}]
    Error in Master Core initialization [/cover] */
    if(ADC_E_NO_ERR == lErrVal)
    #endif
    {
      /* [cover parentID={192357ED-39F1-4c84-B5CD-2DEBB0A75149}]
      Is Config pointer NULL or Kernel Config pointer not equal to Config
      pointer [/cover] */
      if ((ConfigPtr == NULL_PTR) || (Adc_ConfigPtr != ConfigPtr))
      {
        #if(MCAL_AR_VERSION == MCAL_AR_422)
        {
          lErrVal = ADC_E_PARAM_CONFIG;
        }
        #else
        {
          lErrVal = ADC_E_PARAM_POINTER;
        }
        #endif
        /* [cover parentID={2F7121B9-E1ED-4147-B4AD-EA8A7CD93125}]
        Report DET Error [/cover] */
        Adc_lReportError(ADC_SID_INIT, lErrVal);
      }
      /* [cover parentID={04765A52-452C-497f-8865-F471094001A7}]
      MultiCore Error Detection is on or Safety is on [/cover] */
      #if((ADC_MULTICORE_ERROR_DETECT == STD_ON)||(ADC_SAFETY_ENABLE == STD_ON))
      /* [cover parentID={8BB218D1-E180-40b7-A89A-966A2AE8F001}]
      Is Core Config pointer NULL [/cover] */
      else if (ConfigPtr->CoreCfgPtr[CoreId] == NULL_PTR)
      {
        /* Update return value as ADC_E_CORE_NOT_CONFIGURED */
        lErrVal = ADC_E_CORE_NOT_CONFIGURED;
        /* [cover parentID={420F8B56-E912-4e72-905B-89670459E37D}]
        Report ADC_E_CORE_NOT_CONFIGURED DET [/cover] */
        Adc_lReportMulticoreError(ADC_SID_INIT, ADC_E_CORE_NOT_CONFIGURED);
      }
      #endif
      /* [cover parentID={1302F4C4-938F-40cc-BEFF-E67670516A17}]
      Is Core Already Initialized [/cover] */
      else if (Adc_InitStatus[CoreId] == ADC_INITIALIZED)
      {
        /* Update return value as ADC_E_ALREADY_INITIALIZED */
        lErrVal = ADC_E_ALREADY_INITIALIZED;
        /* [cover parentID={F11C9BED-2FB4-4543-A2E9-C3988111DD4F}]
        Report ADC_E_ALREADY_INITIALIZED DET  [/cover] */
        Adc_lReportError(ADC_SID_INIT, ADC_E_ALREADY_INITIALIZED);
      }
      else
      {
        /*Do Nothing*/
      }
    }
  }
  else
  #endif
  {
    /* [cover parentID={9CC8561B-3A69-4bd6-B6C9-F143D3BC7C35}]
    Is Config pointer NULL  [/cover] */
    /*Master core*/
    if(ConfigPtr == NULL_PTR)
    {
      #if(MCAL_AR_VERSION == MCAL_AR_422)
      {
        lErrVal = ADC_E_PARAM_CONFIG;
      }
      #else
      {
        lErrVal = ADC_E_PARAM_POINTER;
      }
      #endif
      /* [cover parentID={EE3F86E9-0D5E-4132-BD47-50A7345CF1D5}]
      Report DET Error [/cover] */
      Adc_lReportError(ADC_SID_INIT, lErrVal);
    }
    /* [cover parentID={DE882BF7-AF32-46a6-9554-670277524684}]
    Is Driver in Initialized state [/cover] */
    else if(Adc_InitStatus[CoreId] == ADC_INITIALIZED)
    {
      lErrVal = ADC_E_ALREADY_INITIALIZED;
      /* [cover parentID={02E14E41-E9F4-461d-B449-B371BF9DF69A}]
      Report ADC_E_ALREADY_INITIALIZED DET  [/cover] */
      Adc_lReportError(ADC_SID_INIT, ADC_E_ALREADY_INITIALIZED);
    }
    else
    {
      /*Do Nothing*/
    }
  }

  return(lErrVal);
}
#endif

#if (((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON)) &&\
     (ADC_RESULT_HANDLING_IMPLEMENTATION != ADC_DMA_MODE_RESULT_HANDLING))
/*******************************************************************************
** Traceability: [cover parentID={78F0E0C9-3247-4035-B081-DA3486CD238C}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lSetupResBufDetCheck             **
**                    (                                                       **
**                       const uint32 KernelId                                **
**                       const Adc_GroupType GroupId                          **
**                       const Adc_ValueGroupType * const DataBufferPtr       **
**                       const uint32 CoreId                                  **
**                    )                                                       **
**                                                                            **
** Description      :This function is to check all the DETs for               **
**                   Adc_SetupResultBuffer  API                               **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    GroupId - Group ID for the Kernel                       **
**                    DataBufferPtr - Pointer to the Result Buffer            **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lSetupResBufDetCheck(const uint32 KernelId, \
    const Adc_GroupType GroupId,const Adc_ValueGroupType * const DataBufferPtr,\
    const uint32 CoreId)
{

  uint8 lErrVal;
  /* [cover parentID={AF0955FC-DFCA-48ed-AEFA-D19748726B9A}]
  Check Adc Un-Init DET [/cover] */
  lErrVal = Adc_lCheckUnInitDet(ADC_SID_SETUP_RESULT_BUFFER, CoreId);
  /* [cover parentID={B0954766-2A5F-4de6-BE74-95C9A188B61E}]
  Un-Init DET Error [/cover] */
  if(lErrVal == ADC_E_NO_ERR)
  {
    /* [cover parentID={A58C79BD-5188-4514-85E3-30746D3BD0AC}]
    Check Param Group DET [/cover] */
    lErrVal = Adc_lCheckParamGrpDet(KernelId, GroupId, \
                                    ADC_SID_SETUP_RESULT_BUFFER, CoreId);
    /* [cover parentID={38E0D305-473F-4e2e-948B-19ECA5522261}]
    Input Param DET Error [/cover] */
    if(lErrVal == ADC_E_NO_ERR)
    {
      /* [cover parentID={9547CE6E-0D2E-407e-80F8-42A758E70C78}]
      Check Param Pointer DET [/cover] */
      lErrVal = Adc_lCheckParamPointerDet(DataBufferPtr, \
                                          ADC_SID_SETUP_RESULT_BUFFER);
    }
  }
  return(lErrVal);
}
#endif

#if(((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))\
                                                    &&(ADC_DEINIT_API ==STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={74F1C5B8-C34B-424a-ACAD-37345031C1CE}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lDeInitDetCheck                  **
**                    (                                                       **
**                       const uint32 CoreId                                  **
**                    )                                                       **
**                                                                            **
** Description      :This function is to check all the DETs for Adc_DeInit API**
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
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lDeInitDetCheck(const uint32 CoreId)
{
  uint8 lErrVal;

  /* [cover parentID={FCA9CA17-5A5C-4587-82FD-AB0834FC6A13}]
  Check Adc Un-Init DET [/cover] */
  lErrVal = Adc_lCheckUnInitDet(ADC_SID_DEINIT, CoreId);
  /* [cover parentID={B4BEDD08-684A-44f5-97A1-3C3D640A514E}]
  Un-Init DET Error [/cover] */
  if(lErrVal == ADC_E_NO_ERR)
  {
    /* [cover parentID={44DAFED3-DB35-4852-A763-1A300BECDDDD}]
    Safety is ON and Number of Cores available are greater than one or 
    MultiCore Error Detection is ON [/cover] */
    #if( (ADC_MULTICORE_ERROR_DETECT == STD_ON) || \
         ((ADC_SAFETY_ENABLE == STD_ON) && (MCAL_NO_OF_CORES > ADC_ONE_U)) )
    uint32 lCore;
    /* [cover parentID={0FD8C9BB-59F9-4453-8715-7CCB1A8C6F21}]
    Is CoreId is equal to Master CoreId [/cover] */
    if (MCAL_MASTER_COREID == CoreId)
    {
      /* [cover parentID={00805B64-FC29-40a3-91FD-931E913732D3}]
      Till the last available Core [/cover] */
      for (lCore = 0U; lCore < MCAL_NO_OF_CORES; lCore++)
      {
        /* [cover parentID={BBE7C10F-3CE5-46f0-8EBB-7ECE0D409501}]
        Is Core not equal to Master Core & Core is not in Uninit completed
        state [/cover] */
        if ((MCAL_MASTER_COREID != lCore) && \
            (Adc_InitStatus[lCore] != ADC_UNINIT_COMPLETED))
        {
          lErrVal = ADC_E_SLAVE_CORE_INIT;
          /* [cover parentID={358C55F8-42CB-4795-8919-86940BCCA14D}]
          Report ADC_E_SLAVE_CORE_INIT DET  [/cover] */
          Adc_lReportMulticoreError(ADC_SID_DEINIT, ADC_E_SLAVE_CORE_INIT);
          break;
        }
      }
    }
    #endif
  }
  return(lErrVal);
}
#endif

#if(((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))\
                                            &&(ADC_STARTUP_CALIB_API == STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={D747A5D9-FE39-466f-8A87-6B38A7897089}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lTrigStartupCalDetCheck          **
**                    (                                                       **
**                       void                                                 **
**                    )                                                       **
**                                                                            **
** Description      :This function is to check all the DETs for               **
**                   Adc_TriggerStartupCal API                                **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lTrigStartupCalDetCheck(void)
{
  uint8 lErrVal = ADC_E_NO_ERR;
  uint32 lCoreId;

  /* [cover parentID={11BE4CF3-4982-4b99-BDC6-0C34E82E9670}]
  Is Adc config pointer is equal to NULL? [/cover] */
  if(Adc_ConfigPtr == NULL_PTR)
  {
    /* [cover parentID={D6278CFF-7ECA-4922-9AD9-6642B0D5A6B3}]
    Report ADC_E_UNINIT DET [/cover] */
    Adc_lReportError(ADC_SID_TRIGGER_STARTUP_CAL, ADC_E_UNINIT);
    lErrVal = ADC_E_UNINIT;
  }
  else
  {
    /* [cover parentID={DC59B913-A06C-4041-8444-61E27DA30F78}]
    Till the last available CoreId [/cover] */
    for (lCoreId = 0U; lCoreId < MCAL_NO_OF_CORES; lCoreId++)
    {
      /* [cover parentID={BA874CCB-AF13-4cdc-89E0-4B8DB87CC86D}]
      Config pointer not equal to NULL pointer & Module is not Initialized
      [/cover] */
      if((Adc_ConfigPtr->CoreCfgPtr[lCoreId] != NULL_PTR) && \
          (Adc_InitStatus[lCoreId] != ADC_INITIALIZED))
      {
        /* [cover parentID={9EB7AA4B-8EC5-4775-A4B4-80092EFF1409}]
        Report ADC_E_UNINIT DET  [/cover] */
        Adc_lReportError(ADC_SID_TRIGGER_STARTUP_CAL, ADC_E_UNINIT);
        lErrVal = ADC_E_UNINIT;
        break;
      }
    }
  }
  return(lErrVal);
}
#endif

#if(((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))\
                                    &&(ADC_ENABLE_START_STOP_GROUP_API==STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={CF280F7A-88BC-4c54-8ECD-E792AE9D665A}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lStartGrpConvDetCheck            **
**                    (                                                       **
**                       const uint32 KernelId                                **
**                       const Adc_GroupType GroupId                          **
**                       const uint32 CoreId                                  **
**                    )                                                       **
**                                                                            **
** Description      :This function is to check all the DETs for               **
**                   Adc_StartGroupConversion API                             **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    GroupId - Group ID for the Kernel                       **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lStartGrpConvDetCheck(const uint32 KernelId, \
    const Adc_GroupType GroupId, const uint32 CoreId)
{
  uint8 lErrVal;
  /* [cover parentID={784CE157-0138-4921-9854-F8C93B14D212}]
  Check Adc Un-Init DET [/cover] */
  lErrVal = Adc_lCheckUnInitDet(ADC_SID_START_GROUP_CONVERSION, CoreId);
  /* [cover parentID={A83859C1-0797-478f-B0ED-6756051780D8}]
  Un-Init DET Error [/cover] */
  if(lErrVal == ADC_E_NO_ERR)
  {
    /* [cover parentID={684357BF-8182-49ff-A079-3D9AFCA050BB}]
    Check Param Group DET [/cover] */
    lErrVal = Adc_lCheckParamGrpDet(KernelId, GroupId, \
                                    ADC_SID_START_GROUP_CONVERSION, CoreId);
    /* [cover parentID={2D343A2D-4FF9-40bb-8491-BF18C9C52721}]
    Input Param DET Error [/cover] */
    if(lErrVal == ADC_E_NO_ERR)
    {
      /* [cover parentID={EC09CCEA-5925-4f41-BCB5-A1156FD2D93C}]
      Check wrong trigger source DET [/cover] */
      lErrVal = Adc_lCheckWrongTrigSrcDet(KernelId,GroupId,\
                               ADC_SID_START_GROUP_CONVERSION,CoreId);
      /* [cover parentID={F7446A71-9225-4e0f-82CA-0AE941A7FDD6}]
      Result Handling is not a DMA Mode [/cover] */
      #if(ADC_RESULT_HANDLING_IMPLEMENTATION != ADC_DMA_MODE_RESULT_HANDLING)
      /* [cover parentID={0165AC74-A99A-41d2-8384-30BBBD67E16E}]
      Wrong trigger source DET error [/cover] */
      if(lErrVal == ADC_E_NO_ERR)
      {
        /* [cover parentID={2D3F4CDD-F441-4c09-82A9-270815DFB497}]
        Check Buffer Un-Init DET [/cover] */
        lErrVal = Adc_lCheckBufferUnInitDet(KernelId,GroupId,\
                               ADC_SID_START_GROUP_CONVERSION,CoreId);
      }
      #endif

      /* [cover parentID={FF6299BD-B444-4220-8345-8FAA3C5D6FE2}]
      Low power state support is ON [/cover] */
      #if(ADC_LOW_POWER_STATE_SUPPORT==STD_ON)
      /* [cover parentID={C5A38D19-2F38-4f03-AF04-66F14E0F716C}]
      Buffer UnInit DET error [/cover] */
      if(lErrVal == ADC_E_NO_ERR)
      {
        /* [cover parentID={9D73C6BA-5331-4afa-AD82-CA524E4D95F8}]
        Check converter Off DET [/cover] */
        lErrVal = Adc_lCheckConverterOffDet(KernelId,
                                            ADC_SID_START_GROUP_CONVERSION);
      }
      #endif
      /* [cover parentID={52C072E2-9A29-4cfb-9AC2-68F2A80190E5}]
      Safety is on and Start-up calib api is on [/cover] */
      #if((ADC_SAFETY_ENABLE == STD_ON) && (ADC_STARTUP_CALIB_API == STD_ON))
      /* [cover parentID={7A356915-8B11-4fa0-B00A-0B0F039E1AAB}]
      Converted off DET error [/cover] */
      if(lErrVal == ADC_E_NO_ERR)
      {
        /* [cover parentID={8215924D-5C3A-4526-A88E-E5E051C4050B}]
        Check calibration on-going DET [/cover] */
        lErrVal = Adc_lCheckStartupCalibOngoingDet(KernelId, \
                  ADC_SID_START_GROUP_CONVERSION);
      }
      #endif
    }
  }
  return(lErrVal);
}
#endif

#if(((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))\
                                    &&(ADC_ENABLE_START_STOP_GROUP_API==STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={EDDB2352-032D-4a16-8551-F9EC316322C5}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lStopGrpConvDetCheck             **
**                    (                                                       **
**                      const uint32 KernelId                                 **
**                      const Adc_GroupType GroupId                           **
**                      const uint32 CoreId                                   **
**                    )                                                       **
**                                                                            **
** Description      :This function is to check all the DETs for               **
**                   Adc_StopGroupConversion API                              **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    GroupId - Group ID for the Kernel                       **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lStopGrpConvDetCheck(const uint32 KernelId,\
                               const Adc_GroupType GroupId, const uint32 CoreId)
{
  uint8 lErrVal;
  /* [cover parentID={77B5CFE7-352F-43f3-A6C4-147D12D25780}]
  Check Adc Un-Init DET [/cover] */
  lErrVal = Adc_lCheckUnInitDet(ADC_SID_STOP_GROUP_CONVERSION, CoreId);
  /* [cover parentID={06560AC1-A5CD-4973-BBB5-1B2C380B0C94}]
  Un-Init DET Error [/cover] */
  if(lErrVal == ADC_E_NO_ERR)
  {
    /* [cover parentID={C315ED29-079C-4457-9D38-94D39B66E04C}]
    Check Param Group DET [/cover] */
    lErrVal = Adc_lCheckParamGrpDet(KernelId, GroupId, \
                                    ADC_SID_STOP_GROUP_CONVERSION, CoreId);
    /* [cover parentID={03396869-2F4D-4ab8-8EB1-8C529AB7DD9F}]
    Input Param DET Error [/cover] */
    if(lErrVal == ADC_E_NO_ERR)
    {
      /* [cover parentID={BE480CCB-FF5B-4629-A1B4-324CCD3407F7}]
      Check wrong trigger source DET [/cover] */
      lErrVal = Adc_lCheckWrongTrigSrcDet(KernelId, GroupId, \
                               ADC_SID_STOP_GROUP_CONVERSION,CoreId);
    }
  }
return(lErrVal);
}
#endif

#if(((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))\
                                                 &&(ADC_READ_GROUP_API==STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={60236046-E151-4358-A11A-08414069CC6C}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lReadGrpDetCheck                 **
**                    (                                                       **
**                     const Adc_ValueGroupType * const DataBufferPtr         **
**                     const uint32 KernelId                                  **
**                     const Adc_GroupType GroupId                            **
**                     const uint32 CoreId                                    **
**                    )                                                       **
**                                                                            **
** Description      :This function is to check all the DETs for               **
**                   Adc_ReadGroup API                                        **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    GroupId - Group ID for the Kernel                       **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lReadGrpDetCheck(\
    const Adc_ValueGroupType * const DataBufferPtr, const uint32 KernelId,\
    const Adc_GroupType GroupId, const uint32 CoreId)
{
  uint8 lErrVal;
  /* [cover parentID={B4D7F764-7E5E-4d06-9FBD-05806DF8D290}]
  Check Adc Un-Init DET [/cover] */
  lErrVal = Adc_lCheckUnInitDet(ADC_SID_READ_GROUP, CoreId);
  /* [cover parentID={81DDB2DE-E101-428a-8786-4A23350F0428}]
  Un-Init DET Error [/cover] */
  if(lErrVal == ADC_E_NO_ERR)
  {
    /* [cover parentID={1E22851E-3DFF-4f20-88B8-982BDEE03001}]
    Check Param Group DET [/cover] */
    lErrVal = Adc_lCheckParamGrpDet(KernelId, GroupId, ADC_SID_READ_GROUP, \
                                    CoreId);
    /* [cover parentID={A9432FE2-ABAB-40a0-9093-B43CB86B245E}]
    Param Group DET Error [/cover] */
    if(lErrVal == ADC_E_NO_ERR)
    {
      /* [cover parentID={2BB2081E-DE7E-486b-98E6-68750BDF20FD}]
      Check Param Pointer DET [/cover] */
      lErrVal = Adc_lCheckParamPointerDet(DataBufferPtr, ADC_SID_READ_GROUP);
    }
  }
  return(lErrVal);
}
#endif

#if((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={72F3452B-FAD3-45d4-9B42-52368A6EE554}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lGetGrpStatusDetCheck            **
**                    (                                                       **
**                      const uint32 KernelId                                 **
**                      const Adc_GroupType GroupId                           **
**                      const uint32 CoreId                                   **
**                    )                                                       **
**                                                                            **
** Description      :This function is to check all the DETs for               **
**                   Adc_GetGroupStatus API                                   **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    GroupId - Group ID for the Kernel                       **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lGetGrpStatusDetCheck(const uint32 KernelId,\
                              const Adc_GroupType GroupId,const uint32 CoreId)
{
  uint8 lErrVal;
  /* [cover parentID={9BFF9A09-6363-4d75-B36A-BD0320B35D21}]
  Check Adc Un-Init DET [/cover] */
  lErrVal = Adc_lCheckUnInitDet(ADC_SID_GET_GROUP_STATUS, CoreId);
  /* [cover parentID={C86B64F3-7E0B-4cce-9E05-4BE0A073CD96}]
  Un-Init DET Error [/cover] */
  if(lErrVal == ADC_E_NO_ERR)
  {
    /* [cover parentID={EA652870-7A77-47ab-B158-6A808930889A}]
    Check Param Group DET [/cover] */
    lErrVal = Adc_lCheckParamGrpDet(KernelId,GroupId,ADC_SID_GET_GROUP_STATUS,\
                                    CoreId);
  }
  return(lErrVal);
}
#endif

#if (((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON)) && \
           (ADC_RESULT_HANDLING_IMPLEMENTATION != ADC_DMA_MODE_RESULT_HANDLING))
/*******************************************************************************
** Traceability: [cover parentID={A3384188-5730-42df-9628-5F2B9AC2328D}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lGetStrmPtrDetCheck              **
**                    (                                                       **
**                     const uint32 KernelId                                  **
**                     const Adc_GroupType GroupId                            **
**                     Adc_ValueGroupType ** const PtrToSamplePtr,            **
**                     const uint32 CoreId                                    **
**                    )                                                       **
**                                                                            **
** Description      :This function is to check all the DETs for               **
**                   Adc_GetStreamLastPointer API                             **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    GroupId - Group ID for the Kernel                       **
**                    PtrToSamplePtr - Pointer to the Sample pointer          **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lGetStrmPtrDetCheck(const uint32 KernelId,\
  const Adc_GroupType GroupId, Adc_ValueGroupType ** const PtrToSamplePtr,\
  const uint32 CoreId)
{
  uint8 lErrVal;
  /* [cover parentID={6B0DCB89-8C55-4ad9-90F0-CD4D988627F1}]
  Check Adc Un-Init DET [/cover] */
  lErrVal = Adc_lCheckUnInitDet(ADC_SID_GET_STREAM_LAST_POINTER, CoreId);
  /* [cover parentID={40A35996-4516-413d-B75C-CEC4528AFE35}]
  Un-Init DET Error [/cover] */
  if(lErrVal == ADC_E_NO_ERR)
  {
    /* [cover parentID={03A6CEFE-C83E-424f-A71F-EC19654E5EAE}]
    Check Param Group DET [/cover] */
    lErrVal = Adc_lCheckParamGrpDet(KernelId, GroupId, \
                                    ADC_SID_GET_STREAM_LAST_POINTER, CoreId);
    /* [cover parentID={7D1CA2FB-101B-4fd8-B788-E3DD2C2B2A5A}]
    Param Group DET error [/cover] */
    if(lErrVal == ADC_E_NO_ERR)
    {
      /* [cover parentID={5DE04AD1-34E3-4cc0-8373-626B212AFCF9}]
      Check Param Pointer Det [/cover] */
      lErrVal = Adc_lCheckParamPointerDet(PtrToSamplePtr, \
                                          ADC_SID_GET_STREAM_LAST_POINTER);
    }
  }
  return(lErrVal);
  /* MISRA2012_RULE_8_13_JUSTIFICATION:Declaring pointer as a constant causes
  warings with compiler, hence it cannot be made const and not an issue*/
}
#endif

#if(((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON)) && \
    (ADC_GRP_NOTIF_CAPABILITY ==STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={CC3012F7-5709-4e73-B375-0469857C33FC}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lEnGrpNotifDetCheck              **
**                    (                                                       **
**                     const uint32 KernelId                                  **
**                     const Adc_GroupType GroupId                            **
**                     const uint32 CoreId                                    **
**                    )                                                       **
**                                                                            **
** Description      :This function is to check all the DETs for               **
**                   Adc_EnableGroupNotification API                          **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different channel groups                  **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    GroupId - Group ID for the Kernel                       **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lEnGrpNotifDetCheck(const uint32 KernelId,\
                               const Adc_GroupType GroupId, const uint32 CoreId)
{
  uint8 lErrVal;
  /* [cover parentID={6FFCC006-2EB8-4de5-8615-1E7003A57572}]
  Check Adc Un-Init DET [/cover] */
  lErrVal = Adc_lCheckUnInitDet(ADC_SID_ENABLE_GROUP_NOTIFICATION, CoreId);
  /* [cover parentID={BC464C5B-800F-4614-967D-531A0AF41943}]
  Un-Init DET Error [/cover] */
  if(lErrVal == ADC_E_NO_ERR)
  {
    /* [cover parentID={D003790C-143E-4c2b-95E9-E318BC9B1853}]
    Check Param Group DET [/cover] */
    lErrVal = Adc_lCheckParamGrpDet(KernelId, GroupId, \
                                    ADC_SID_ENABLE_GROUP_NOTIFICATION, CoreId);
    /* [cover parentID={8FB5E499-5F21-423b-B911-40C54752FC1A}]
    Input Param DET Error [/cover] */
    if(lErrVal == ADC_E_NO_ERR)
    {
      /* [cover parentID={B3F6E23A-DE29-43fc-ADC0-35E93C9CD75E}]
      Check Notify Capability DET [/cover] */
      lErrVal = Adc_lCheckNotifCapableDet(KernelId,GroupId,\
                                      ADC_SID_ENABLE_GROUP_NOTIFICATION,CoreId);
    }
  }
  return(lErrVal);
}
#endif

#if(((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON)) && \
    (ADC_GRP_NOTIF_CAPABILITY ==STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={30394DD8-5D17-476c-AE79-478B8AAA39D2}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lDisGrpNotifDetCheck             **
**                    (                                                       **
**                     const uint32 KernelId                                  **
**                     const Adc_GroupType GroupId                            **
**                     const uint32 CoreId                                    **
**                    )                                                       **
**                                                                            **
** Description      :This function is to check all the DETs for               **
**                   Adc_DisableGroupNotification API                         **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    GroupId - Group ID for the Kernel                       **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lDisGrpNotifDetCheck(const uint32 KernelId,\
                                const Adc_GroupType GroupId,const uint32 CoreId)
{
  uint8 lErrVal;
  /* [cover parentID={A0D90506-8D9C-4cf2-8DC1-2E091905B3D3}]
  Check Adc Un-Init DET [/cover] */
  lErrVal = Adc_lCheckUnInitDet(ADC_SID_DISABLE_GROUP_NOTIFICATION, CoreId);
  /* [cover parentID={BC9D785A-0242-44da-B535-0084176621C4}]
  Un-Init DET Error [/cover] */
  if(lErrVal == ADC_E_NO_ERR)
  {
    /* [cover parentID={7507F255-283A-491d-AD79-A965C66DEC04}]
    Check Param Group DET [/cover] */
    lErrVal = Adc_lCheckParamGrpDet(KernelId,GroupId,\
                                    ADC_SID_DISABLE_GROUP_NOTIFICATION,CoreId);
    /* [cover parentID={8CC33768-C4E6-43c4-8C4E-137C0276E2C2}]
    Input Param DET Error [/cover] */
    if(lErrVal == ADC_E_NO_ERR)
    {
      /* [cover parentID={CBA622FA-C5A0-420e-A008-A8D9B2668DE5}]
      Check Notify Capability DET [/cover] */
      lErrVal = Adc_lCheckNotifCapableDet(KernelId,GroupId,\
                                     ADC_SID_DISABLE_GROUP_NOTIFICATION,CoreId);
    }
  }
  return(lErrVal);
}
#endif

#if(((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON)) && \
    (ADC_HW_TRIGGER_API==STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={2DE4C648-08A7-4349-B942-4512943EA4B1}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lEnHwTriggerDetCheck             **
**                    (                                                       **
**                       const uint32 KernelId                                **
**                       const Adc_GroupType GroupId                          **
**                       const uint32 CoreId                                  **
**                    )                                                       **
**                                                                            **
** Description      :This function is to check all the DETs for               **
**                   Adc_EnableHardwareTrigger  API                           **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    GroupId - Group ID for the Kernel                       **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lEnHwTriggerDetCheck(const uint32 KernelId,\
                                const Adc_GroupType GroupId,const uint32 CoreId)
{
  uint8 lErrVal;
  /* [cover parentID={6235998E-EC2B-467c-BBAB-BFF2B5478859}]
  Check Adc Un-Init DET [/cover] */
  lErrVal = Adc_lCheckUnInitDet(ADC_SID_ENABLE_HARDWARE_TRIGGER, CoreId);
  /* [cover parentID={2F4D21E9-42C9-49d4-BF84-88912060F6DF}]
  Un-Init DET Error [/cover] */
  if(lErrVal == ADC_E_NO_ERR)
  {
    /* [cover parentID={C9330C0B-A291-4d7e-A88B-E5A620B907C2}]
    Check Param Group DET [/cover] */
    lErrVal = Adc_lCheckParamGrpDet(KernelId, GroupId, \
                                    ADC_SID_ENABLE_HARDWARE_TRIGGER, CoreId);
    /* [cover parentID={14BC91C4-4C5B-4f32-8A1D-B33CF8E93130}]
    Input Param DET Error [/cover] */
    if(lErrVal == ADC_E_NO_ERR)
    {
      /* [cover parentID={CB8D4E1A-9827-4a26-BE08-B8C97D0A2019}]
      Check wrong trigger source DET [/cover] */
      lErrVal = Adc_lCheckWrongTrigSrcDet(KernelId,GroupId,\
                               ADC_SID_ENABLE_HARDWARE_TRIGGER,CoreId);
      /* [cover parentID={9FEB8F07-75A4-43f9-B286-61CA3C270EBB}]
      Wrong trigger source DET Error [/cover] */
      if(lErrVal == ADC_E_NO_ERR)
      {

        /* [cover parentID={6AEF6A92-715D-4e45-972C-A066408B6077}]
        DMA Mode Result Handling is OFF [/cover] */
        #if(ADC_RESULT_HANDLING_IMPLEMENTATION != ADC_DMA_MODE_RESULT_HANDLING)
        /* [cover parentID={861D8C65-CE69-4b19-BDC8-E03203A9D0C7}]
        Check Buffer Un-Init DET [/cover] */
        lErrVal = Adc_lCheckBufferUnInitDet(KernelId,GroupId,\
                               ADC_SID_ENABLE_HARDWARE_TRIGGER,CoreId);
        /* [cover parentID={75E62C6E-D5DE-48bd-8B6D-2FE123960B0B}]
        Buffer Un-Init DET Error [/cover] */
        if(lErrVal == ADC_E_NO_ERR)
        #endif
        {
          /* [cover parentID={4F40D2A1-9559-4467-8A5A-0BD09E7B2159}]
          Check wrong conv mode DET [/cover] */
          lErrVal = Adc_lCheckWrongConvModeDet(KernelId,GroupId,\
                                 ADC_SID_ENABLE_HARDWARE_TRIGGER,CoreId);
          /* [cover parentID={7F05797D-26E1-47e2-94EB-4878B0074EB5}]
          Low power state support is ON [/cover] */
          #if(ADC_LOW_POWER_STATE_SUPPORT==STD_ON)
          /* [cover parentID={E7DFF75B-636D-43c2-BF96-B50BA0BF4FD6}]
          Wrong conv mode DET error [/cover] */
          if(lErrVal == ADC_E_NO_ERR)
          {
            /* [cover parentID={239EF96B-7210-481e-92B8-1078ED41DB41}]
            Check Converter Off Det [/cover] */
            lErrVal = Adc_lCheckConverterOffDet(KernelId,
                                               ADC_SID_ENABLE_HARDWARE_TRIGGER);
          }
          #endif
          /* [cover parentID={A9FC6D16-089E-4d62-AC48-3C002DB8E272}]
          Safety is on and Startup Calib API is on [/cover] */
          #if((ADC_SAFETY_ENABLE == STD_ON) && \
              (ADC_STARTUP_CALIB_API == STD_ON))
          /* [cover parentID={EFC1F7AF-3FBF-4fe7-BFBF-4651B3FDD39E}]
          Converter off DET error [/cover] */
          if(lErrVal == ADC_E_NO_ERR)
          {
            /* [cover parentID={58E9128E-8837-447b-87E9-FE92FBCBF731}]
            Check calibration on-going DET [/cover] */
            lErrVal = Adc_lCheckStartupCalibOngoingDet(KernelId,
                                              ADC_SID_ENABLE_HARDWARE_TRIGGER);
          }
          #endif
        }
      }
    }
  }
  return(lErrVal);
}
#endif

#if(((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON)) && \
    (ADC_HW_TRIGGER_API==STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={FCE72B8C-FD0B-4e61-B3C7-45D2D41171CA}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lDisHwTriggerDetCheck            **
**                    (                                                       **
**                     const uint32 KernelId                                  **
**                     const Adc_GroupType GroupId                            **
**                     const uint32 CoreId                                    **
**                    )                                                       **
**                                                                            **
** Description      :This function is to check all the DETs for               **
**                   Adc_DisableHardwareTrigger  API                          **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for channel groups executing on different ADC **
**                    hardware groups                                         **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    GroupId - Group ID for the Kernel                       **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lDisHwTriggerDetCheck(const uint32 KernelId,\
                               const Adc_GroupType GroupId, const uint32 CoreId)
{
  uint8 lErrVal;
  /* [cover parentID={ED591D00-008C-4d84-BBB9-8EB1BAD11891}]
  Check Adc Un-Init DET [/cover] */
  lErrVal = Adc_lCheckUnInitDet(ADC_SID_DISABLE_HARDWARE_TRIGGER, CoreId);
  /* [cover parentID={12A22699-0066-49e5-979D-386E0F1056A4}]
  Un-Init DET Error [/cover] */
  if(lErrVal == ADC_E_NO_ERR)
  {
    /* [cover parentID={41F66738-ABB7-44ff-8F5C-F9ADE17D7B6D}]
    Check Param Group DET [/cover] */
    lErrVal = Adc_lCheckParamGrpDet(KernelId,GroupId,\
                                ADC_SID_DISABLE_HARDWARE_TRIGGER,CoreId);
    /* [cover parentID={45A82A2B-9B98-4590-B070-8DC80E4DB2D0}]
    Input Param DET Error [/cover] */
    if(lErrVal == ADC_E_NO_ERR)
    {
      /* [cover parentID={E4EC76EC-28E3-4f7b-A410-FE70055B03BF}]
      Check wrong trigger source DET [/cover] */
      lErrVal = Adc_lCheckWrongTrigSrcDet(KernelId,GroupId,\
                               ADC_SID_DISABLE_HARDWARE_TRIGGER,CoreId);
      /* [cover parentID={580AE70C-61B2-40ed-889B-F0600D593300}]
      Wrong trigger source DET Error [/cover] */
      if(lErrVal == ADC_E_NO_ERR)
      {
        /* [cover parentID={F110D19D-FEA5-4139-A4D8-D37269808136}]
        Check wrong conv mode DET [/cover] */
        lErrVal = Adc_lCheckWrongConvModeDet(KernelId,GroupId,\
                              ADC_SID_DISABLE_HARDWARE_TRIGGER,CoreId);
      }
    }
  }
  return(lErrVal);
}
#endif

#if(((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON)) && \
    (ADC_LOW_POWER_STATE_SUPPORT==STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={99E8C5C8-DD8D-4b84-B8AD-EBF21844C34D}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lPreparePowerStateDetCheck       **
**                    (                                                       **
**                      const Adc_PowerStateType PowerState,                  **
**                      Adc_PowerStateRequestResultType * const Result,       **
**                      const uint32 CoreId                                   **
**                    )                                                       **
**                                                                            **
** Description      :This function is to check all the DETs for               **
**                   Adc_PreparePowerState API                                **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different CPU cores                       **
**                                                                            **
** Parameters(in)   : PowerState - Target power state intended to be          **
**                                        attained                            **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : Result - Result of Power state change preparation       **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lPreparePowerStateDetCheck(\
     const Adc_PowerStateType PowerState,\
     Adc_PowerStateRequestResultType * const Result,const uint32 CoreId)
{
  uint8 lErrVal = ADC_E_NO_ERR;
  /* [cover parentID={5486F14E-07DA-4d41-90E3-940541786BBE}]
  Check param pointer DET [/cover] */
  lErrVal = Adc_lCheckParamPointerDet(Result, \
                                      ADC_SID_PREPARE_POWER_STATE);
  /* [cover parentID={9B4B56AC-2A6F-40ad-B1D3-623DC57F7E4C}]
  Param pointer DET error occured [/cover] */
  if(lErrVal == ADC_E_NO_ERR)
  {
    /* [cover parentID={661D9B03-FFF4-491d-8C80-0A41E47551CE}]
    Check UnInit DET [/cover] */
    lErrVal = Adc_lCheckUnInitDet(ADC_SID_PREPARE_POWER_STATE, CoreId);
    /* [cover parentID={FF13F535-A289-46eb-B4A6-76C08E408C54}]
    UnInit DET error occured [/cover] */
    if(lErrVal == ADC_E_NO_ERR)
    {
      /* [cover parentID={6C45E90F-2CEA-4291-A5EB-1EA08F7E4CFE}]
      Check power state support DET [/cover] */
      lErrVal = Adc_lCheckPowerStateNotSuppDet( PowerState,\
                                                ADC_SID_PREPARE_POWER_STATE);
      /* [cover parentID={91D14F45-8BD1-4b60-A8EA-F00C931082C6}]
      Power State Support Det error occured [/cover] */
      if(lErrVal != ADC_E_NO_ERR)
      {
        /* [cover parentID={8D034187-6AF3-4dbc-AC02-3139CAF0FAB0}]
        Update result with ADC_POWER_STATE_NOT_SUPP [/cover] */
        *Result = ADC_POWER_STATE_NOT_SUPP;
      }
    }
    else
    {
      /* [cover parentID={25DC4D38-588F-436e-8052-06C70B47B4FE}]
      Update result with ADC_NOT_INIT [/cover] */
      *Result = ADC_NOT_INIT;
    }
  }
  return(lErrVal);
}
#endif

#if(((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON)) && \
    (ADC_LOW_POWER_STATE_SUPPORT==STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={9A2D9882-443F-47b8-8906-4B0A8B5B8101}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lSetPowerStateDetCheck           **
**                    (                                                       **
**                      Adc_PowerStateRequestResultType * const Result,       **
**                      const uint32 CoreId,                                  **
**                      const uint32 TargetPwrState                           **
**                    )                                                       **
**                                                                            **
** Description      :This function is to check all the DETs for               **
**                   Adc_SetPowerState API                                    **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different CPU cores                       **
**                                                                            **
** Parameters(in)   : CoreId - Logical CPU core ID                            **
**                    TargetPwrState-Target pwr state intended to be attained **
**                                                                            **
** Parameters (out) : Result - Result of Power state change preparation       **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lSetPowerStateDetCheck(\
            Adc_PowerStateRequestResultType * const Result,const uint32 CoreId,\
            const uint32 TargetPwrState)
{
  uint8 lErrVal = ADC_E_NO_ERR;

  /* [cover parentID={3386D9A5-CC36-4569-A4D2-7FD82A87D108}]
  Check param pointer DET [/cover] */
  lErrVal = Adc_lCheckParamPointerDet(Result, \
                                      ADC_SID_SET_POWER_STATE);
  /* [cover parentID={B7F49DF3-4C1F-4a74-8383-5EBB9E3232AD}]
  Param pointer DET error occured [/cover] */
  if(lErrVal == ADC_E_NO_ERR)
  {
    /* [cover parentID={444D5E7D-8508-4499-B99F-B6F2D3C8B4E3}]
    Check UnInit DET [/cover] */
    lErrVal = Adc_lCheckUnInitDet(ADC_SID_SET_POWER_STATE, CoreId);

    /* [cover parentID={CCCCFA51-609A-4302-B4E9-91B95FFC2581}]
    UnInit Det error occured [/cover] */
    if(lErrVal == ADC_E_NO_ERR)
    {
      /* [cover parentID={1C406E76-22F4-4efb-8494-FD00CB962E72}]
      Check peripheral prepared DET [/cover] */
      lErrVal = Adc_lCheckPeripheralPreparedDet(TargetPwrState, \
                ADC_SID_SET_POWER_STATE);
      /* [cover parentID={18DFD06E-ECC7-4dc5-8025-6938E4B5CBC3}]
      Is Peripheral prepared DET error occured ? [/cover] */
      if(lErrVal != ADC_E_NO_ERR)
      {
        /* [cover parentID={A678A211-A745-4bb9-BED5-5764EE088640}]
        Update result pointer with ADC_SEQUENCE_ERROR [/cover] */
        *Result = ADC_SEQUENCE_ERROR;
      }
    }
    else
    {
      /* [cover parentID={2B577AB3-4563-4f9d-B6CE-C7ABE8DFAAAA}]
      Update result with ADC_NOT_INIT [/cover] */
      *Result = ADC_NOT_INIT;
    }
  }
  return(lErrVal);
}
#endif

#if(((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON)) && \
    (ADC_LOW_POWER_STATE_SUPPORT==STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={235D6261-5954-47ab-B188-F763822C7551}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lGetPowerStateDetCheck           **
**                    (                                                       **
**                      const Adc_PowerStateType * const PowerState,          **
**                      Adc_PowerStateRequestResultType * const Result,       **
**                      const uint8 ServiceId,                                **
**                      const uint32 CoreId                                   **
**                    )                                                       **
**                                                                            **
** Description      :This function is to check all the DETs for               **
**                   Adc_GetCurrentPowerState & Adc_GetTargetPowerState APIs  **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different CPU cores                       **
**                                                                            **
** Parameters(in)   : ServiceId - Service ID of the API                       **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : PowerState -Power state of ADC hardware Units           **
**                    Result - Result of Target Power state read              **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lGetPowerStateDetCheck(\
    const Adc_PowerStateType * const PowerState, \
    Adc_PowerStateRequestResultType * const Result,
    const uint8 ServiceId,  const uint32 CoreId)
{
  uint8 lErrVal = ADC_E_NO_ERR;
  /* [cover parentID={F6180600-C339-49a4-9F81-3246262C8165}]
  Check power state param pointer DET [/cover] */
  lErrVal = Adc_lCheckParamPointerDet(PowerState, ServiceId);
  /* [cover parentID={C3BB727C-3344-46f3-B25A-64B3BF177F90}]
  Param Pointer Det error occured [/cover] */
  if(lErrVal == ADC_E_NO_ERR)
  {
    /* [cover parentID={2461E0E2-15C1-40dd-955F-EB8C819FFC69}]
    Check result param pointer DET [/cover] */
    lErrVal = Adc_lCheckParamPointerDet(Result, ServiceId);
    /* [cover parentID={9B8D8D8D-D182-40cc-B00D-5478FDD68F16}]
    Param pointer DET error occured [/cover] */
    if(lErrVal == ADC_E_NO_ERR)
    {
      /* [cover parentID={F00D9D50-21CF-4bc1-8374-C34947531AA2}]
      Check UnInit Det [/cover] */
      lErrVal = Adc_lCheckUnInitDet(ServiceId, CoreId);
      /* [cover parentID={F7CA1566-EB6F-4338-B1F5-04B27CE59DFD}]
      UnInit DET error occured [/cover] */
      if(lErrVal != ADC_E_NO_ERR)
      {
        /* [cover parentID={F0575DF4-4C7B-46fc-A010-F0D022706DDF}]
        Update result with ADC_NOT_INIT [/cover] */
        *Result = ADC_NOT_INIT;
      }
    }
  }
  return(lErrVal);
}
#endif

#if((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={AEDE1654-91E5-4062-8E06-5624C46967EB}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lCheckUnInitDet                  **
**                    (                                                       **
**                      const uint8 ServiceId                                 **
**                      const uint32 CoreId                                   **
**                    )                                                       **
**                                                                            **
** Description      :This function is to check ADC_E_UNINIT DET for the       **
**                   ServiceId(API).                                          **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : ServiceId - Serive ID of the API                        **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lCheckUnInitDet(const uint8 ServiceId,\
                                       const uint32 CoreId)
{
  uint8 lErrVal = ADC_E_NO_ERR;

  /* [cover parentID={7CC5C3C3-7080-453a-B0C4-A9070E509D35}]
  Is Deinit API [/cover] */
  if(ADC_SID_DEINIT == ServiceId)
  {
    /* [cover parentID={D5BF4C4C-B58B-46b3-91EE-6DFF9FEB2500}]
    Is driver in Uninit completed state for called core  [/cover] */
    if(Adc_InitStatus[CoreId] == ADC_UNINIT_COMPLETED)
    {
      /* [cover parentID={E4D9F99F-8E1A-4c6f-93FE-CB0209FAD0AB}]
      Report ADC_E_UNINIT Det [/cover] */
      Adc_lReportError(ServiceId, ADC_E_UNINIT);
      lErrVal = ADC_E_UNINIT;
    }
  }
  else
  {
    /* [cover parentID={B177D123-ACAF-4bb8-AD62-5B7D6549EAD5}]
    Adc is not in Initialized state or
    Adc config pointer is equal to NULL pointer [/cover] */
    if((Adc_InitStatus[CoreId] != ADC_INITIALIZED) ||
        (Adc_ConfigPtr == NULL_PTR))
    {
      /* [cover parentID={4F5339EB-F621-434d-8543-467335385075}]
      Report ADC_E_UNINIT Det [/cover] */
      Adc_lReportError(ServiceId, ADC_E_UNINIT);
      lErrVal = ADC_E_UNINIT;
    }
  }
  return(lErrVal);
}
#endif

#if((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))
/*CYCLOMATIC_Adc_lCheckParamGrpDet_JUSTIFICATION: This function checks
ADC_E_PARAM_GROUP Development or Safety Error and also the MultiCore
related DET based on the enable of pre-compile macros. The different if
conditions for DET, Safety and MultiCore error check causes the complexity
to increase, but actually during run-time out of all if conditions many
will be pre-compile time removed */
/*******************************************************************************
** Traceability: [cover parentID={5F637317-7993-40b7-9EB3-0BDFD7BC052F}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lCheckParamGrpDet                **
**                    (                                                       **
**                      const uint32 KernelId                                 **
**                      const Adc_GroupType GroupId                           **
**                      const uint8 ServiceId                                 **
**                      const uint32 CoreId                                   **
**                    )                                                       **
**                                                                            **
** Description      :This function is to check ADC_E_PARAM_GROUP DET for the  **
**                   ServiceId(API).                                          **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    GroupId - Group ID for the Kernel                       **
**                    ServiceId - Serive ID of the API                        **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lCheckParamGrpDet(const uint32 KernelId,\
        const Adc_GroupType GroupId, const uint8 ServiceId, const uint32 CoreId)
{
  uint8 lErrVal;
  #if( (ADC_MULTICORE_ERROR_DETECT == STD_ON) || \
       ((ADC_SAFETY_ENABLE == STD_ON) && (MCAL_NO_OF_CORES > ADC_ONE_U)) )
  uint32 lCore, lMultiCoreErr = 0U;
  #endif

  /* [cover parentID={6B5CBDDE-D249-45a4-99ED-03327E00D195}]
  Is KernelId greater than Maximum KernelId [/cover] */
  if(KernelId >= ADC_MAX_KERNEL_ID)
  {
    /* Update return value as ADC_E_PARAM_GROUP */
    lErrVal = ADC_E_PARAM_GROUP;
  }
  /* [cover parentID={6745F7DA-2A71-498b-89B8-6090E893BD86}]
  Kernel not configured during Initialization [/cover] */
  else if(Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[KernelId] == \
          NULL_PTR)
  {
    /*If kernel is not configured at all, error value is ADC_E_PARAM_GROUP;
    If kernel is configured for a different CPU core, error value is
    ADC_E_CORE_GROUP_MISMATCH, instead */
    lErrVal = ADC_E_PARAM_GROUP;
    /* [cover parentID={EE166B67-0CD8-49de-9AF6-C9994AEE725D}]
    Safety is ON and Number of Cores available are greater than one or 
    MultiCore Error Detection is ON [/cover] */
    #if( (ADC_MULTICORE_ERROR_DETECT == STD_ON) || \
         ((ADC_SAFETY_ENABLE == STD_ON) && (MCAL_NO_OF_CORES > ADC_ONE_U)) )
    /* [cover parentID={03C55DE4-EF76-422e-AD07-8390F206BC69}]
    Till the last available Core [/cover] */
    for (lCore = (uint32)0U; lCore < MCAL_NO_OF_CORES; lCore++)
    {
      /* [cover parentID={11B650B0-7A04-4f77-AB33-1A138A167E78}]
      Is Core configured and Core Index is not equal to calling CoreId[/cover]*/
      if ((lCore != CoreId) && (Adc_ConfigPtr->CoreCfgPtr[lCore] != NULL_PTR))
      {
        /* [cover parentID={266053D1-BB3C-4dc3-A0F1-FD5A8EB92CD2}]
        Is kernel configured [/cover] */
        if (Adc_ConfigPtr->CoreCfgPtr[lCore]->HwUnitCfgPtr[KernelId] != \
            NULL_PTR)
        {
          lErrVal = ADC_E_CORE_GROUP_MISMATCH;
          lMultiCoreErr = ADC_ONE_U;
          /* [cover parentID={2BAC99F8-C9A7-4221-A595-426F9B05F7BE}]
          Report the Mutli-Core DET [/cover] */
          Adc_lReportMulticoreError(ServiceId, ADC_E_CORE_GROUP_MISMATCH);
          break;
        }
      }
    }
    #endif
  }
  /* [cover parentID={C3336738-258B-4c65-9C83-52B663926BBC}]
  Is GroupID greater than Max groups configured for this kernel  [/cover] */
  else if(GroupId >= (Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[KernelId]\
                      ->NoOfGroups))
  {
    /* [cover parentID={1C27753E-CADE-425c-9816-840298C81F3B}]
    Update return value as ADC_E_PARAM_GROUP  [/cover] */
    lErrVal = ADC_E_PARAM_GROUP;
  }
  else
  {
    lErrVal = ADC_E_NO_ERR;
  }
  /* [cover parentID={3EE9F965-F3C5-4821-BC6F-30C2EAC3B8C9}]
  Safety is ON and Number of Cores available are greater than one or 
  MultiCore Error Detection is ON [/cover] */
  #if( (ADC_MULTICORE_ERROR_DETECT == STD_ON) || \
       ((ADC_SAFETY_ENABLE == STD_ON) && (MCAL_NO_OF_CORES > ADC_ONE_U)) )
  /* [cover parentID={213330E2-5803-486b-844A-4FB97E19F159}]
  Multicore Error [/cover] */
  if(0U == lMultiCoreErr)
  #endif
  {
    /* [cover parentID={81C6DA90-1154-416c-BEBC-4FB0038578E2}]
    Return value not equal to ADC_E_NO_ERR [/cover] */
    if(lErrVal != ADC_E_NO_ERR)
    {
      /* [cover parentID={3A8C262C-4D19-461d-AD28-A84F2E2227C4}]
      Report DET based on type of Error  [/cover] */
      Adc_lReportError(ServiceId, lErrVal);
    }
  }
  return(lErrVal);
}
#endif

#if((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={A595109F-558B-4513-98EB-4BF44C5CCC39}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lCheckWrongTrigSrcDet            **
**                    (                                                       **
**                      const uint32 KernelId                                 **
**                      const Adc_GroupType GroupId                           **
**                      const uint8 ServiceId                                 **
**                      const uint32 CoreId                                   **
**                    )                                                       **
**                                                                            **
** Description      :This function is to check ADC_E_WRONG_TRIGG_SRC DET for  **
**                   the ServiceId(API).                                      **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    GroupId - Group ID for the Kernel                       **
**                    ServiceId - Serive ID of the API                        **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lCheckWrongTrigSrcDet(const uint32 KernelId,\
        const Adc_GroupType GroupId, const uint8 ServiceId, const uint32 CoreId)
{
  Adc_TriggerSourceType lTrigSrc;
  uint8 lErrVal;
  lErrVal = ADC_E_NO_ERR;
  lTrigSrc = Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[KernelId]->\
                                      GrpCfgPtr[GroupId].TriggerSource;

  /* [cover parentID={079E160B-4AD8-4467-948C-F0A291892604}]
  Check if Service ID is equal to START or STOP Group Software conversion
  [/cover] */
  if((ServiceId == ADC_SID_START_GROUP_CONVERSION) || \
      (ServiceId == ADC_SID_STOP_GROUP_CONVERSION))
  {
    /* [cover parentID={97B93495-0094-4c3f-9861-F1B732DA6B5F}]
    Is trigger source not equal to software trigger  [/cover] */
    if(lTrigSrc != ADC_TRIGG_SRC_SW)
    {
      /* [cover parentID={5369283B-2D78-4daf-9125-63F4D9DB95E1}]
      Report ADC_E_WRONG_TRIGG_SRC DET  [/cover] */
      Adc_lReportError(ServiceId, ADC_E_WRONG_TRIGG_SRC);
      lErrVal = ADC_E_WRONG_TRIGG_SRC;
    }
  }
  /* [cover parentID={6480428D-DF39-4ad9-BB88-695B46DDD86E}]
  Check if Service ID is equal to Enable or Disable Hardware Trigger Source
  for conversion [/cover] */
  else if((ServiceId == ADC_SID_ENABLE_HARDWARE_TRIGGER) || \
          (ServiceId == ADC_SID_DISABLE_HARDWARE_TRIGGER))
  {
    /* [cover parentID={9035EFC9-EE3B-4490-AC71-75E8E17392A4}]
    Is trigger source not equal to hardware trigger [/cover] */
    if(lTrigSrc != ADC_TRIGG_SRC_HW)
    {
      /* [cover parentID={649FA476-6A6A-4e8f-9BFD-FC04B0F0730A}]
      Report ADC_E_WRONG_TRIGG_SRC DET  [/cover] */
      Adc_lReportError(ServiceId, ADC_E_WRONG_TRIGG_SRC);
      lErrVal = ADC_E_WRONG_TRIGG_SRC;
    }
  }
  else
  {
    lErrVal = ADC_E_WRONG_TRIGG_SRC;
  }
  return(lErrVal);
}
#endif

#if(((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON)) && \
    (ADC_RESULT_HANDLING_IMPLEMENTATION != ADC_DMA_MODE_RESULT_HANDLING))
/*******************************************************************************
** Traceability: [cover parentID={F4CF83FE-B853-4eec-B7B6-C9E173A57F89}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lCheckBufferUnInitDet            **
**                    (                                                       **
**                      const uint32 KernelId                                 **
**                      const Adc_GroupType GroupId                           **
**                      const uint8 ServiceId                                 **
**                      const uint32 CoreId                                   **
**                    )                                                       **
**                                                                            **
** Description      :This function is to check ADC_E_BUFFER_UNINIT DET for the**
**                   ServiceId(API).                                          **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    GroupId - Group ID for the Kernel                       **
**                    ServiceId - Serive ID of the API                        **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lCheckBufferUnInitDet(const uint32 KernelId, \
    const Adc_GroupType GroupId, const uint8 ServiceId, const uint32 CoreId)
{
  const Adc_GlobalDataType *lKernelDataPtr;
  uint8 lErrVal = ADC_E_NO_ERR;

  /* Get global state data location for the Kernel */
  lKernelDataPtr = Adc_lGetKernelDataAddress(KernelId, CoreId);

  /* [cover parentID={815AB7A7-5582-4af4-AC2C-8D8C69FBB386}]
  Is buffer location for storing the conversion results is NULL  [/cover] */
  if(lKernelDataPtr->GrpResBuffer[GroupId] == NULL_PTR)
  {
    /* [cover parentID={453C4AB8-2D44-4828-ACC2-F75463201C34}]
    Report ADC_E_BUFFER_UNINIT Det Error  [/cover] */
    Adc_lReportError(ServiceId, ADC_E_BUFFER_UNINIT);
    lErrVal = ADC_E_BUFFER_UNINIT;
  }
  return(lErrVal);
}
#endif

#if( (ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
     ((MCAL_AR_VERSION == MCAL_AR_422) && (ADC_DEV_ERROR_DETECT == STD_ON)) )
/*******************************************************************************
** Traceability: [cover parentID={45ACC233-B15E-470c-84BD-25DB8070CC86}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lCheckGrpIdleDet                 **
**                    (                                                       **
**                      const uint32 KernelId                                 **
**                      const Adc_GroupType GroupId                           **
**                      const uint8 ServiceId                                 **
**                      const uint32 CoreId                                   **
**                    )                                                       **
**                                                                            **
** Description      :This function is to check ADC_E_IDLE Development or      **
**                   Runtime Error for the ServiceId(API).                    **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    GroupId - Group ID for the Kernel                       **
**                    ServiceId - Serive ID of the API                        **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lCheckGrpIdleDet(const uint32 KernelId,\
        const Adc_GroupType GroupId, const uint8 ServiceId, const uint32 CoreId)
{
  const Adc_GlobalDataType *lKernelDataPtr;
  uint32 lBusyFlag, lResultFlag;
  uint8 lErrVal = ADC_E_NO_ERR;

  /* Get global state data location for the Kernel */
  lKernelDataPtr = Adc_lGetKernelDataAddress(KernelId, CoreId);

  lBusyFlag = Adc_lGetGroupStatus(lKernelDataPtr, GroupId);
  lResultFlag = Adc_lGetGroupResultStatus(lKernelDataPtr, GroupId);

  /* [cover parentID={DEA5840C-CA62-4a4e-88E3-AEA6A5329121}]
  Is Group never started conversion OR Group has implicity stopped and
  results are read [/cover] */
  if( (lBusyFlag == (uint32)0U) && (lResultFlag == (uint32)0U) )
  {
    /* [cover parentID={93CAC01F-C2F3-429b-941B-CBE21537D620}]
    Report ADC_E_IDLE Error [/cover] */
    Adc_lReportRuntimeDetError(ServiceId, ADC_E_IDLE);
    /* Update return value as ADC_E_IDLE */
    lErrVal = ADC_E_IDLE;
  }

  return(lErrVal);
}
#endif

#if( (ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
     ((MCAL_AR_VERSION == MCAL_AR_422) && (ADC_DEV_ERROR_DETECT == STD_ON)) )
/*******************************************************************************
** Traceability: [cover parentID={20C41841-782D-4e59-8AC2-A416BCB6F8E1}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lCheckGrpBusyDet                 **
**                    (                                                       **
**                      const uint32 KernelId                                 **
**                      const Adc_GroupType GroupId                           **
**                      const uint8 ServiceId                                 **
**                      const uint32 CoreId                                   **
**                    )                                                       **
**                                                                            **
** Description      :This function is to check ADC_E_BUSY Development or      **
**                   Runtime Error for the ServiceId(API).                    **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    GroupId - Group ID for the Kernel                       **
**                    ServiceId - Serive ID of the API                        **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lCheckGrpBusyDet(const uint32 KernelId,\
        const Adc_GroupType GroupId, const uint8 ServiceId, const uint32 CoreId)
{
  const Adc_GlobalDataType *lKernelDataPtr;
  uint8 lErrVal = ADC_E_NO_ERR;

  /* Get global state data location for the Kernel */
  lKernelDataPtr = Adc_lGetKernelDataAddress(KernelId, CoreId);

  switch (ServiceId)
  {
    /* [cover parentID={F3B8BB46-B898-4a16-9121-888BF9C3A930}]
    Service Id is ADC_SID_DEINIT [/cover] */
    case ADC_SID_DEINIT:
    {
      /* [cover parentID={F91F2513-EF19-4290-8E40-036E4ACB2342}]
      Check if any group is busy in conversion [/cover] */
      if(Adc_lGetAllGroupStatus(CoreId) != (uint32)0U)
      {
        /* [cover parentID={3FFA44ED-380A-4808-951E-F3620023B03F}]
        Report ADC_E_BUSY Error [/cover] */
        Adc_lReportRuntimeDetError(ADC_SID_DEINIT, ADC_E_BUSY);
        /* Update the return value */
        lErrVal = ADC_E_BUSY; 
      }
    }
    break;
    /* [cover parentID={3D4D8F05-E025-40f3-B1E6-3B043EAB5BD8}]
    DMA Mode Result Handling is OFF [/cover] */
    #if(ADC_RESULT_HANDLING_IMPLEMENTATION != ADC_DMA_MODE_RESULT_HANDLING)
    /* [cover parentID={A4EDB7D3-1C09-4e9b-8205-E8AC78A5A69A}]
    Service Id is ADC_SID_SETUP_RESULT_BUFFER [/cover] */
    case ADC_SID_SETUP_RESULT_BUFFER:
    {
      uint32 lResultFlag, lBusyFlag;
      lResultFlag = Adc_lGetGroupResultStatus(lKernelDataPtr, GroupId);
      lBusyFlag = Adc_lGetGroupStatus(lKernelDataPtr, GroupId);
      /*Check if group is BUSY, currently converting
      OR group has implictly stopped with valid results available in buffer.
      Since results are available in buffer, the new buffer address should not
      be updated, because a ReadGroup call after this would read results from
      unknown location*/
      /* [cover parentID={04844BC0-4C0F-4514-ACAC-B08C879803F4}]
      Check if any group is busy or has valid results [/cover] */
      if((lBusyFlag == (uint32)ADC_ONE_U ) || \
          (lResultFlag == (uint32)ADC_ONE_U))
      {
        /* [cover parentID={416EB563-EFCA-4412-B1B0-F2B26AD397CF}]
        Report ADC_E_BUSY Error [/cover] */
        Adc_lReportRuntimeDetError(ADC_SID_SETUP_RESULT_BUFFER, ADC_E_BUSY);
        /* Update the return value */
        lErrVal = ADC_E_BUSY;
      }
    }
    break;
    #endif
    /* [cover parentID={C9969EF8-D24F-4633-AD3A-EC4A0AF4A6B9}]
    Service Id is ADC_SID_START_GROUP_CONVERSION [/cover] */
    case ADC_SID_START_GROUP_CONVERSION:
    {
      /* [cover parentID={3CDE6E14-F0E8-48c9-8C0E-9F1A6B9B423C}]
      Check Start Group Conversion Busy Development or Runtime Error [/cover]*/
      lErrVal = Adc_lChkStartGrpConvGrpBusyDet(KernelId,GroupId,\
                                               lKernelDataPtr,CoreId);
    }
    break;
    /* [cover parentID={2097C6CD-C18E-4929-9DEB-E6C04885D387}]
    Service Id is ADC_SID_ENABLE_HARDWARE_TRIGGER [/cover] */
    case ADC_SID_ENABLE_HARDWARE_TRIGGER:
    {
      /* [cover parentID={35FADFDF-7B94-4ca8-B4F9-3C72326E2833}]
      Check hardware trigger group busy Development or Runtime Error [/cover]*/
      lErrVal = Adc_lChkEnHwTrigGrpBusyDet(KernelId,GroupId,\
                                           lKernelDataPtr,CoreId);
    }
    break;
    default:
    /*Do nothing*/
    break;
  }
  return(lErrVal);
}
#endif

#if( (ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
     ((MCAL_AR_VERSION == MCAL_AR_422) && (ADC_DEV_ERROR_DETECT == STD_ON)) )
/*CYCLOMATIC_Adc_lChkStartGrpConvGrpBusyDet_JUSTIFICATION: This function checks 
ADC_E_BUSY Development or Runtime Error for different mode of ADC operation(No 
priority,Queuing,HW priority & HW-SW priority) & Also ADC_E_BUSY DET for groups 
enabled with Limit checking & Alias configurations.The different if conditions  
in different operating mode causes the complexity to increase, but actually 
during run-time out of all if conditions many will be pre-compile time removed*/
/*******************************************************************************
** Traceability: [cover parentID={AA8B5DEA-97C9-4766-AA2A-3EC907504AE2}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lChkStartGrpConvGrpBusyDet       **
**                    (                                                       **
**                      const uint32 KernelId                                 **
**                      const Adc_GroupType GroupId                           **
**                      const Adc_GlobalDataType * const KernelDataPtr        **
**                      const uint32 CoreId                                   **
**                    )                                                       **
**                                                                            **
** Description      :This function is to check the ADC_E_BUSY Development or  **
**                   Runtime Error for the ADC_SID_START_GROUP_CONVERSION     **
**                   service ID                                               **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    GroupId - Group ID for the Kernel                       **
**                    KernelDataPtr - Pointer to kernel data                  **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lChkStartGrpConvGrpBusyDet(const uint32 KernelId,\
  const Adc_GroupType GroupId, const Adc_GlobalDataType * const KernelDataPtr,\
  const uint32 CoreId)
{
  uint8 lErrVal = ADC_E_NO_ERR;
  /* [cover parentID={D817BC36-E441-44d3-A0DA-6F8C0D5DFED4}]
  Mode of Operation - Precompile Switch [/cover] */
  #if ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW) ||\
       (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW))
  /* FOR HW_PRIORITY MODE */
  uint16 lChannelMask, lResRegMask;

  lChannelMask = Adc_ConfigPtr->CoreCfgPtr[CoreId]->\
                 HwUnitCfgPtr[KernelId]->GrpCfgPtr[GroupId].ChannelMask;
  lResRegMask = Adc_ConfigPtr->CoreCfgPtr[CoreId]->\
                HwUnitCfgPtr[KernelId]->GrpCfgPtr[GroupId].ResultRegMask;
  /*Raise Busy Error, if group is already in the queue or any channel/result
    register of the group is already running on another request source */
  /* [cover parentID={F6BE3BE6-F832-46ce-B0AF-EA03E5FE0364}]
  Any channel or result register of the group is already running on another
  request source [/cover] */
  if(((KernelDataPtr->AllRunningChannels & lChannelMask) != (uint16)0U)||\
     ((KernelDataPtr->AllRunningResReg & lResRegMask)    != (uint16)0U) )
  #elif(ADC_ENABLE_QUEUING == STD_ON)
  /* FOR QUEUING MODE */
  /* [cover parentID={B0F89D8C-B146-47f0-977F-0C6D2FF393F6}]
  Group for the kernel is currently not in  idle state [/cover] */
  if(Adc_lGetGroupStatus(KernelDataPtr,GroupId) == (uint32)ADC_ONE_U )
  #else
  /* FOR NO PRIORITY MODE */
  /* [cover parentID={87672A78-2076-4c33-80CD-C10E166EEFF8}]
  Group for the kernel is currently not in  idle state [/cover] */
  if((KernelDataPtr->GrpStatus) != (uint32)0U)
  #endif
  {
    /* [cover parentID={B75D1D9E-1456-45cf-93B8-6D9462B73D74}]
    Report ADC_E_BUSY Error [/cover] */
    Adc_lReportRuntimeDetError(ADC_SID_START_GROUP_CONVERSION,ADC_E_BUSY);
    /* Update the return value */
    lErrVal = ADC_E_BUSY;
  }
  /* [cover parentID={F4B90FB3-4A14-46d4-B023-604210E34EAE}]
    Check ADC_E_BUSY Development or Runtime error if Priority is set to 
    ADC_PRIORITY_HW_SW[/cover] */
  #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
  else
  {
    /* [cover parentID={FE47DAFD-F0B6-423a-B001-C4EA36DF0464}]
    Report ADC_E_BUSY Development or Runtime error if no free RS and no lower 
    priority SW group is executing [/cover] */
    lErrVal = Adc_lCheckGrpPrioSwDet(KernelId, GroupId, CoreId);
  }
  #endif
  /* Raise Busy DET if group is limit check group and another limit check
  group is already started */
  /* [cover parentID={9FA073A1-1E7E-41c4-943F-03D63FD6FE93}]
  Priority mode is ON & Limit check is ON [/cover] */
  #if ((ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) &&\
       (ADC_ENABLE_LIMIT_CHECK==STD_ON))
  /* [cover parentID={817574CA-DF87-4017-A52D-437797CADAF9}]
  Are there any error occured? [/cover] */
  if (lErrVal == ADC_E_NO_ERR)
  {
    /* [cover parentID={FEDE0DF3-1B6E-43fa-B3F9-CB90E3E88D8A}]
    Is Group is limit check configured group? [/cover] */
    if ((uint8)ADC_ONE_U == Adc_ConfigPtr->CoreCfgPtr[CoreId]->\
        HwUnitCfgPtr[KernelId]->GrpCfgPtr[GroupId].LimitCheckGroup)
    {
      /* [cover parentID={EFB92AF7-257D-43bb-BCB6-3773793EAC91}]
      Is another limit check group is already started? [/cover] */
      if ((uint8)ADC_ONE_U == KernelDataPtr->LimitChkActiveFlag)
      {
        /* [cover parentID={FF702711-D3AA-4d53-A701-35E965E49E38}]
        Report ADC_E_BUSY Error [/cover] */
        Adc_lReportRuntimeDetError(ADC_SID_START_GROUP_CONVERSION, ADC_E_BUSY);
        /* Update the return value */
        lErrVal = ADC_E_BUSY;
      }
    }
  }
  #endif
  /* Raise busy DET if group has non-default ALIAS configuration and another
  group with non-default ALIAS configuration is already started */
  /* [cover parentID={B6177EDA-3219-40ec-A43D-7588CDE26F76}]
  Priority mode is ON [/cover] */
  #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
  /* [cover parentID={01A39559-0908-43a1-B9BA-A6D07200CE1E}]
  Are there any error occured? [/cover] */
  if (lErrVal == ADC_E_NO_ERR)
  {
    /* [cover parentID={65A04510-4FA0-49c0-AE40-3C4D122AADB0}]
    Is channel of the group is configured with alias configuration? [/cover] */
    if (ADC_ALIAS_DEFAULT_VALUE != Adc_ConfigPtr->CoreCfgPtr[CoreId]->\
        HwUnitCfgPtr[KernelId]->GrpCfgPtr[GroupId].AliasChCfg)
    {
      /* [cover parentID={997C0B5C-B035-49de-A042-5FA9C722FCF8}]
      Is another alias configuration group is already started? [/cover] */
      if ((uint8)ADC_ONE_U == KernelDataPtr->AliasActiveFlag)
      {
        /* [cover parentID={8BA365ED-B70D-4013-B896-0CBF21539FDB}]
        Report ADC_E_BUSY DET [/cover] */
        Adc_lReportRuntimeDetError(ADC_SID_START_GROUP_CONVERSION, ADC_E_BUSY);
        /* Update the return value */
        lErrVal = ADC_E_BUSY;
      }
    }
  }
  #endif
  /* [cover parentID={2023D57D-83D0-4c11-9905-887CEAE5D0C1}]
  SYNC mode is ON [/cover] */
  #if (ADC_SYNC_CONV_ENABLE == STD_ON)
  /* [cover parentID={26004456-4305-4964-A886-075182FC8D7C}]
  Any error occured [/cover] */
  if (lErrVal == ADC_E_NO_ERR)
  {
    const Adc_GroupCfgType *lGrpCfgPtr;
    /* Get group configuration address */
    lGrpCfgPtr = &(Adc_ConfigPtr->CoreCfgPtr[CoreId]->\
                   HwUnitCfgPtr[KernelId]->GrpCfgPtr[GroupId]);

    /* [cover parentID={552C4F19-05B0-4d37-8147-212F9C06E2C9}]
    Any Sync channels configured [/cover] */
    if (lGrpCfgPtr->SyncChannelMask != (uint16)0U)
    {
      /* [cover parentID={CF5048E0-8D83-485b-B50B-513E993B93EA}]
      Check if synchronous slave channels or result registers are currently
      in use [/cover] */
      lErrVal = Adc_lCheckSlaveGrpBusyDet(KernelId, GroupId, CoreId, \
                                          ADC_SID_START_GROUP_CONVERSION);

    }
    /* [cover parentID={7B7DED26-82FE-4c16-90CB-4631138D48C4}]
    No Priority Mode is ON [/cover] */
    #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_NONE)
    else if (Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[KernelId]->\
             SyncConvMode == ADC_SYNC_CONV_MODE_SLAVE)
    {
      /* [cover parentID={9C97120B-CB54-4c7f-8767-5402A8085E12}]
      Kernel is synchronization slave, check if any channels or result registers
      of group to be started are currently converting as slaves [/cover] */
      if(((KernelDataPtr->AllRunningChannels & lGrpCfgPtr->ChannelMask) != \
          (uint16)0U) || \
          ((KernelDataPtr->AllRunningResReg & lGrpCfgPtr->ResultRegMask) != \
           (uint16)0U))
      {
        /* [cover parentID={E73BBA8A-4327-436c-89AD-A5DF4C920318}]
        Report ADC_E_BUSY Error [/cover] */
        Adc_lReportRuntimeDetError(ADC_SID_START_GROUP_CONVERSION, ADC_E_BUSY);
        /* Update the return value */
        lErrVal = ADC_E_BUSY;
      }
    }
    else
    {
      /* Standalone group, nothing to do */
    }
    #endif
  }
  #endif
  UNUSED_PARAMETER(CoreId);
  UNUSED_PARAMETER(KernelId);
  UNUSED_PARAMETER(GroupId);

  return(lErrVal);
}
#endif

#if( (ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
     ((MCAL_AR_VERSION == MCAL_AR_422) && (ADC_DEV_ERROR_DETECT == STD_ON)) )
/*******************************************************************************
** Traceability: [cover parentID={FC3928E9-9C45-470d-8496-EBA963055228}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lChkEnHwTrigGrpBusyDet           **
**                    (                                                       **
**                      const uint32 KernelId                                 **
**                      const Adc_GroupType GroupId                           **
**                      const Adc_GlobalDataType * const KernelDataPtr        **
**                      const uint32 CoreId                                   **
**                    )                                                       **
**                                                                            **
** Description      :This function is to check ADC_E_BUSY Development or      **
**                   Runtime Error for the ADC_SID_ENABLE_HARDWARE_TRIGGER    **
**                   service ID.                                              **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    GroupId - Group ID for the Kernel                       **
**                    KernelDataPtr - Pointer to kernel data                  **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lChkEnHwTrigGrpBusyDet(const uint32 KernelId,\
  const Adc_GroupType GroupId, const Adc_GlobalDataType * const KernelDataPtr,\
  const uint32 CoreId)
{
  uint8 lErrVal = ADC_E_NO_ERR;

  /* [cover parentID={7E259757-8853-434e-B37F-182D312E7976}]
  Mode of Operation - Precompile Switch [/cover] */
  /* [cover parentID={CA83AA10-0FDA-47ef-BC31-29413166FB31}]
  FOR HW_PRIORITY MODE [/cover] */
  #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW)
  uint8 lReqSrc;
  uint16 lChannelMask, lResRegMask;
  lReqSrc = Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[KernelId]->\
            GrpCfgPtr[GroupId].GrpPriority;
  lChannelMask = Adc_ConfigPtr->CoreCfgPtr[CoreId]->\
                 HwUnitCfgPtr[KernelId]->GrpCfgPtr[GroupId].ChannelMask;
  lResRegMask = Adc_ConfigPtr->CoreCfgPtr[CoreId]->\
                HwUnitCfgPtr[KernelId]->GrpCfgPtr[GroupId].ResultRegMask;
  /* [cover parentID={9A4FF6C3-3BAF-4ad8-8B3E-7548C9E3D4B2}]
  Queue is not empty or RS is already running or Any channel or result register
  of the group is already running on another request source [/cover] */
  if((KernelDataPtr->RSData[lReqSrc].PopGroupId != ADC_INVALID_GROUP_ID)||\
     ((KernelDataPtr->AllRunningChannels & lChannelMask) !=(uint16)0U)||\
     ((KernelDataPtr->AllRunningResReg & lResRegMask) != (uint16)0U) )
  /* [cover parentID={AF947154-F987-48ee-9AC1-DE774DB706B2}]
  FOR HW_SW_PRIORITY MODE [/cover] */
  #elif (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
  uint16 lChannelMask, lResRegMask;
  lChannelMask = Adc_ConfigPtr->CoreCfgPtr[CoreId]->\
                 HwUnitCfgPtr[KernelId]->GrpCfgPtr[GroupId].ChannelMask;
  lResRegMask = Adc_ConfigPtr->CoreCfgPtr[CoreId]->\
                HwUnitCfgPtr[KernelId]->GrpCfgPtr[GroupId].ResultRegMask;
  /* [cover parentID={0F65BA11-8637-4b67-8CC7-6B7AF6393A69}]
  Any channel or result register of the group is already running on another
  request source [/cover] */
  if(((KernelDataPtr->AllRunningChannels & lChannelMask) !=(uint16)0U)||\
     ((KernelDataPtr->AllRunningResReg & lResRegMask) != (uint16)0U) )
  /* [cover parentID={94D1E98F-68DF-4540-A864-4F2464F1B99A}]
  FOR NO_PRIORITY AND QUEUING MODE [/cover] */
  #else
  /*- Check if all groups for the kernel are currently not converting
    - All SW triggered groups are in ADC_IDLE state
    */
  const Adc_HwUnitCfgType * lHwUnitCfgPtr;
  lHwUnitCfgPtr = Adc_ConfigPtr->CoreCfgPtr[CoreId]->\
                  HwUnitCfgPtr[KernelId];
  /* [cover parentID={D888D46F-98D3-46d8-B47B-ED1D9482A284}]
  Group for the kernel is currently not in  idle state [/cover] */
  if( ((KernelDataPtr->GrpStatus) != (uint32)0U) || \
      ( (KernelDataPtr->GrpBufferEndResultStatus & \
         lHwUnitCfgPtr->SwTrigGrpMask) != 0U) )
  #endif
  {
    /* [cover parentID={0B5B2EDB-C4E1-4290-9BC2-FB4846D99911}]
    Report ADC_E_BUSY Error [/cover] */
    Adc_lReportRuntimeDetError(ADC_SID_ENABLE_HARDWARE_TRIGGER, ADC_E_BUSY);
    /* Update the return value */
    lErrVal = ADC_E_BUSY;
  }
  #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
  else
  {
    /* [cover parentID={03EC011E-25E2-4ace-BFDE-B296B576DE85}]
    Report ADC_E_BUSY Development or Runtime error if no free RS and no lower  
    priority SW group is executing [/cover] */
    lErrVal = Adc_lCheckGrpPrioHwDet(KernelId, GroupId, CoreId);
  }
  #endif
  /* Raise Busy DET if group is limit check group and another limit check
  group is already started */
  /* [cover parentID={F0BB7CC4-597C-4c91-A10D-964BB520CCC0}]
  Priority mode is ON & Limit check is ON [/cover] */
  #if ((ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) &&\
       (ADC_ENABLE_LIMIT_CHECK==STD_ON))
  /* [cover parentID={EC1682F5-E6AE-4287-B840-0C91D554ADB7}]
  Are there any error occured? [/cover] */
  if (lErrVal == ADC_E_NO_ERR)
  {
    /* [cover parentID={5DA92F67-F9AB-468b-A212-CA89E6E073D9}]
    Is Group is limit check configured group? [/cover] */
    if ((uint8)ADC_ONE_U == Adc_ConfigPtr->CoreCfgPtr[CoreId]->\
        HwUnitCfgPtr[KernelId]->GrpCfgPtr[GroupId].LimitCheckGroup)
    {
      /* [cover parentID={08D12123-60F5-4e23-B995-4C8752FA0B64}]
      Is another limit check group is already started? [/cover] */
      if ((uint8)ADC_ONE_U == KernelDataPtr->LimitChkActiveFlag)
      {
        /* [cover parentID={C0E4ACF7-5EDB-4883-B3CF-89B885FA77E4}]
        Report ADC_E_BUSY Error [/cover] */
        Adc_lReportRuntimeDetError(ADC_SID_ENABLE_HARDWARE_TRIGGER, ADC_E_BUSY);
        /* Update the return value */
        lErrVal = ADC_E_BUSY;
      }
    }
  }
  #endif
  /* Raise busy DET if group has non-default ALIAS configuration and another
  group with non-default ALIAS configuration is already started */
  /* [cover parentID={66D04460-8157-4a94-BC58-9712AF869455}]
  Priority mode is ON [/cover] */
  #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
  /* [cover parentID={6BEC3B7A-213E-450b-8A9B-2DEA13B6EC52}]
  Are there any error occured? [/cover] */
  if (lErrVal == ADC_E_NO_ERR)
  {
    /* [cover parentID={1E7EF579-B31C-479e-938C-BA2DC812BC89}]
    Is channel of the group is configured with alias configuration? [/cover] */
    if (ADC_ALIAS_DEFAULT_VALUE != Adc_ConfigPtr->CoreCfgPtr[CoreId]->\
        HwUnitCfgPtr[KernelId]->GrpCfgPtr[GroupId].AliasChCfg)
    {
      /* [cover parentID={077C8DFC-DCBA-49f2-991C-E749D294766B}]
      Is another alias configuration group is already started? [/cover] */
      if ((uint8)ADC_ONE_U == KernelDataPtr->AliasActiveFlag)
      {
        /* [cover parentID={5ECAD507-2F12-4617-BACF-1CE5F8545837}]
        Report ADC_E_BUSY Error [/cover] */
        Adc_lReportRuntimeDetError(ADC_SID_ENABLE_HARDWARE_TRIGGER, ADC_E_BUSY);
        /* Update the return value */
        lErrVal = ADC_E_BUSY;
      }
    }
  }
  #endif
  /* [cover parentID={63505BE4-5A3A-4e94-A270-6A4161F1CF97}]
  SYNC mode is ON [/cover] */
  #if (ADC_SYNC_CONV_ENABLE == STD_ON)
  /* [cover parentID={667142B5-6AA8-403a-94CF-77CC4CCB28EB}]
  Any error occured [/cover] */
  if (lErrVal == ADC_E_NO_ERR)
  {
    const Adc_GroupCfgType *lGrpCfgPtr;
    /* Get group configuration address */
    lGrpCfgPtr = &(Adc_ConfigPtr->CoreCfgPtr[CoreId]->\
                   HwUnitCfgPtr[KernelId]->GrpCfgPtr[GroupId]);

    /* [cover parentID={FB6D6ECF-EE23-45ab-8D14-962828B3B8CE}]
    Any Sync channels configured [/cover] */
    if (lGrpCfgPtr->SyncChannelMask != (uint16)0U)
    {
      /* [cover parentID={C6EF425F-9D73-44f5-98B0-B685D795D5DA}]
      Check if synchronous slave channels or result registers are currently
      in use [/cover] */
      lErrVal = Adc_lCheckSlaveGrpBusyDet(KernelId, GroupId, CoreId, \
                                          ADC_SID_ENABLE_HARDWARE_TRIGGER);

    }
    /* For HW or HW-SW priority mode, the below check has already been done
       before, no need to repeat it */
    /* [cover parentID={4BD4736E-D572-4e31-BEB0-0893FCA6B9EC}]
    No Priority Mode is ON [/cover] */
    #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_NONE)
    else if (Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[KernelId]->\
             SyncConvMode == ADC_SYNC_CONV_MODE_SLAVE)
    {
      /* [cover parentID={9C878537-6709-4a6f-8FE2-47A6E1A40892}]
      Kernel is synchronization slave, check if any channels or result registers
      of group to be started are currently converting as slaves [/cover] */
      if(((KernelDataPtr->AllRunningChannels & lGrpCfgPtr->ChannelMask) !=\
          (uint16)0U) ||\
         ((KernelDataPtr->AllRunningResReg & lGrpCfgPtr->ResultRegMask) !=\
          (uint16)0U))
      {
        /* [cover parentID={C1C45D1E-DEF4-4547-B5B4-758CE51048B2}]
        Report ADC_E_BUSY Error [/cover] */
        Adc_lReportRuntimeDetError(ADC_SID_ENABLE_HARDWARE_TRIGGER, ADC_E_BUSY);
        /* Update the return value */
        lErrVal = ADC_E_BUSY;
      }
    }
    else
    {
      /* Standalone group, nothing to do */
    }
    #endif
  }
  #endif
  UNUSED_PARAMETER(GroupId);
  return(lErrVal);
}
#endif

#if ( ((ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
      ((MCAL_AR_VERSION == MCAL_AR_422) && (ADC_DEV_ERROR_DETECT == STD_ON))) \
      && (ADC_SYNC_CONV_ENABLE == STD_ON) )
/*******************************************************************************
** Traceability: [cover parentID={2D0495BA-9443-4bda-9411-C44216134490}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lCheckSlaveGrpBusyDet            **
**                    (                                                       **
**                       const uint32 KernelId                                **
**                       const Adc_GroupType GroupId                          **
**                       const uint32 CoreId                                  **
**                       const uint8 ApiId                                    **
**                    )                                                       **
**                                                                            **
** Description      :This function is to check the ADC_E_BUSY Development or  **
**                   Runtime Error for the slave kernels of the               **
**                   synchronization master                                   **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    GroupId - Group ID for the Kernel                       **
**                    CoreId - Logical CPU core ID                            **
**                    ApiId - API for which the check is done                 **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lCheckSlaveGrpBusyDet(const uint32 KernelId,\
                                             const Adc_GroupType GroupId,\
                                             const uint32 CoreId,\
                                             const uint8 ApiId)
{
  const Adc_HwUnitCfgType * lHwUnitCfgPtr;
  const Adc_GlobalDataType *lKernelDataPtr;
  uint16 lSyncChannelMask, lSyncResRegMask;
  uint8 lKernelCount, lSlaveKernel, lErrVal = ADC_E_NO_ERR;

  /* Get channels and result registers used by synchronization slaves */
  lSyncChannelMask = Adc_ConfigPtr->CoreCfgPtr[CoreId]->\
            HwUnitCfgPtr[KernelId]->GrpCfgPtr[GroupId].SyncChannelMask;
  lSyncResRegMask = Adc_ConfigPtr->CoreCfgPtr[CoreId]->\
            HwUnitCfgPtr[KernelId]->GrpCfgPtr[GroupId].SyncResRegMask;

  /* Check if required channel or result register of any slave is currently
     busy */
  /* Get the base address of the kernel configuration */
  lHwUnitCfgPtr = Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[KernelId];

  /* [cover parentID={38B70DE1-FB7F-4160-A99D-736E39C6519D}]
  Till the last available Kernel [/cover] */
  for (lKernelCount = (uint8)0U;
       lKernelCount < (uint8)(ADC_KERNELS_PER_SYNGRP - 1U); lKernelCount++)
  {
    lSlaveKernel = lHwUnitCfgPtr->SlaveKernels[lKernelCount];
    /* [cover parentID={7C025ACA-5875-46d2-8BA3-B5214B79369D}]
    Slave kernel is valid for Sync Master [/cover] */
    if (lSlaveKernel != ADC_INVALID_KERNEL_ID)
    {
      lKernelDataPtr = Adc_lGetKernelDataAddress(lSlaveKernel, CoreId);

      /* [cover parentID={DBBA7EC7-8A64-4ee8-97E0-EA21A5719C13}]
      Sync channels or Sync result registers are busy [/cover] */
      if (((lKernelDataPtr->AllRunningChannels & lSyncChannelMask) != \
           (uint16)0U) || \
          ((lKernelDataPtr->AllRunningResReg & lSyncResRegMask) != \
           (uint16)0U))
      {
        /* [cover parentID={0E32021C-6B49-4ede-9C81-65A15EE0CB0F}]
        Report ADC_E_BUSY Error [/cover] */
        Adc_lReportRuntimeDetError(ApiId, ADC_E_BUSY);
        /* Update the return value */
        lErrVal = ADC_E_BUSY;
        break;
      }
    }
  }
  return(lErrVal);
}
#endif

#if ( ((ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
      ((MCAL_AR_VERSION == MCAL_AR_422) && (ADC_DEV_ERROR_DETECT == STD_ON))) \
      && (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) )
/*******************************************************************************
** Traceability: [cover parentID={2FDB5EFA-DDAA-4d55-B459-702E2FD4ECEC}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lCheckGrpPrioSwDet               **
**                    (                                                       **
**                       const uint32 KernelId                                **
**                       const Adc_GroupType GroupId                          **
**                       const uint32 CoreId                                  **
**                    )                                                       **
**                                                                            **
** Description      :This function is to check the ADC_E_BUSY Development or  **
**                   Runtime error for Adc_StartGroupConversion API when      **
**                   priority mode is HW-SW priority                          **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    GroupId - Group ID for the Kernel                       **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lCheckGrpPrioSwDet(const uint32 KernelId,\
                               const Adc_GroupType GroupId, const uint32 CoreId)
{
  const Adc_GlobalDataType *lKernelDataPtr;
  const Adc_GroupCfgType *lGrpCfgPtr;
  Adc_GroupType lGroupId;
  Adc_GroupPriorityType lGroupPriority;
  Adc_GroupPriorityType lMinGroupPriority = ADC_MAX_PRIORITY_LVL;
  uint32 lRsCount;
  uint8 lErrVal = ADC_E_BUSY;

  /* Get priority of group to be started */
  lGroupPriority = Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[KernelId]->\
                   GrpCfgPtr[GroupId].GrpPriority;

  /* Get global state data location for the Kernel */
  lKernelDataPtr = Adc_lGetKernelDataAddress(KernelId, CoreId);

  /* [cover parentID={C25D2BC8-F696-4cbf-9D6B-3317B6E0AE08}]
  Till the available Request Source [/cover] */
  for (lRsCount = (uint32)0U; lRsCount < ADC_REQSRC_USED_COUNT; lRsCount++)
  {
    /* Get current group ID for each RS: */
    lGroupId = lKernelDataPtr->RSData[lRsCount].ActiveGroupId;
    /* [cover parentID={6B0EBC52-BA72-4d29-874E-AB1973FCBBAE}]
    RS is Free [/cover] */
    if (ADC_INVALID_GROUP_ID == lGroupId)
    {
      /* [cover parentID={7DB0E8AA-CA5D-4559-8E97-3C8A062D7C41}]
      Group can be started & Update error value as ADC_NO_ERR [/cover] */
      lErrVal = ADC_E_NO_ERR;
    }
    else
    {
      /* Get group configuration address */
      lGrpCfgPtr = &(Adc_ConfigPtr->CoreCfgPtr[CoreId]->\
                     HwUnitCfgPtr[KernelId]->GrpCfgPtr[lGroupId]);

      /* [cover parentID={C7C4CCD8-3B81-4838-8FA4-BCF4CD8FC565}]
      Lower priority SW group is currently executing [/cover] */
      if ((lGrpCfgPtr->TriggerSource == ADC_TRIGG_SRC_SW) &&
          (lGrpCfgPtr->GrpPriority < lGroupPriority))
      {
        /* [cover parentID={33E9A2E5-5B05-4874-91CA-094FAAE54650}]
        SW group with lower priority could be stopped to start the new group
        & Update error value as ADC_NO_ERR [/cover] */
        lErrVal = ADC_E_NO_ERR;
      }

      /* [cover parentID={7B4D5E0B-80F8-431a-A877-68A15E91A614}]
      Grp priority is less than min Grp priority [/cover] */
      if (lGrpCfgPtr->GrpPriority < lMinGroupPriority)
      {
        /* [cover parentID={2345FD43-F5AA-4e16-B893-50203462A5D9}]
        Store lowest priority of all currently executing group [/cover] */
        lMinGroupPriority = lGrpCfgPtr->GrpPriority;
      }
    }

    if (lErrVal == ADC_E_NO_ERR)
    {
      break;
    }
  }

  if (lErrVal != ADC_E_NO_ERR)
  {
    /* [cover parentID={27C79EB5-ACB7-4fe1-A9BE-DE9A24B01C5E}]
    No RS  Free & No lower priority SW Grp executing [/cover] */
    if (lGroupPriority <= lMinGroupPriority)
    {
      lErrVal = ADC_E_NO_ERR;
    }
    else
    {
      /* [cover parentID={8F768C0E-54D5-48f3-BC4B-A99919967E38}]
      Report ADC_E_BUSY Error [/cover] */
      Adc_lReportRuntimeDetError(ADC_SID_START_GROUP_CONVERSION, ADC_E_BUSY);
    }
  }
  return(lErrVal);
}
#endif

#if( ((ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
     ((MCAL_AR_VERSION == MCAL_AR_422) && (ADC_DEV_ERROR_DETECT == STD_ON))) \
     && (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) )
/*******************************************************************************
** Traceability: [cover parentID={4E8156EE-C74E-4de7-8194-FE073B92563F}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lCheckGrpPrioHwDet               **
**                    (                                                       **
**                       const uint32 KernelId                                **
**                       const Adc_GroupType GroupId                          **
**                       const uint32 CoreId                                  **
**                    )                                                       **
**                                                                            **
** Description      :This function is to check the ADC_E_BUSY Development or  **
**                   Runtime Error for Adc_EnableHwTrigger API when priority  **
**                   mode is HW-SW priority                                   **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    GroupId - Group ID for the Kernel                       **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lCheckGrpPrioHwDet(const uint32 KernelId,\
                               const Adc_GroupType GroupId, const uint32 CoreId)
{
  const Adc_GlobalDataType *lKernelDataPtr;
  const Adc_GroupCfgType *lGrpCfgPtr;
  Adc_GroupType lGroupId;
  Adc_GroupPriorityType lGroupPriority;
  uint32 lRsCount;
  uint8 lErrVal = ADC_E_BUSY;

  /* Get priority of group to be started */
  lGroupPriority = Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[KernelId]->\
                   GrpCfgPtr[GroupId].GrpPriority;

  /* Get global state data location for the Kernel */
  lKernelDataPtr = Adc_lGetKernelDataAddress(KernelId, CoreId);

  /* [cover parentID={A24E106D-D32A-4264-BC28-17FD97E3001F}]
  Till the available RS or free RS found [/cover] */
  for (lRsCount = (uint32)0U; lRsCount < ADC_REQSRC_USED_COUNT; lRsCount++)
  {
    /* Get current group ID for each RS: */
    lGroupId = lKernelDataPtr->RSData[lRsCount].ActiveGroupId;
    /* [cover parentID={A9333A04-F3C3-47cd-AA9C-1EEBC91083A2}]
    RS is Free [/cover] */
    if (ADC_INVALID_GROUP_ID == lGroupId)
    {
      /* [cover parentID={7C56FAFF-81FD-435a-BBCD-4D6F26BDF3E7}]
      Group can be started & Update error value as ADC_E_NO_ERR [/cover] */
      lErrVal = ADC_E_NO_ERR;
    }
    else
    {
      /* Get group configuration address */
      lGrpCfgPtr = &(Adc_ConfigPtr->CoreCfgPtr[CoreId]->\
                     HwUnitCfgPtr[KernelId]->GrpCfgPtr[lGroupId]);

      /* [cover parentID={DF457F7E-BE69-46a8-9D68-AC8CBC1E9BAA}]
      Lower priority SW group is currently executing [/cover] */
      if ((lGrpCfgPtr->TriggerSource == ADC_TRIGG_SRC_SW) &&
          (lGrpCfgPtr->GrpPriority < lGroupPriority))
      {
        /* [cover parentID={9BB9D1ED-203C-44a4-B385-53CD0BD17D95}]
        SW group with lower priority could be stopped to start the new group &
        Update error value as ADC_E_NO_ERR [/cover] */
        lErrVal = ADC_E_NO_ERR;
      }
    }
    if(lErrVal == ADC_E_NO_ERR)
    {
      break;
    }
  }
  /* [cover parentID={2F2460EB-9336-4e37-9658-312ECED200C3}]
  Is a RS found on which requested group can be started [/cover] */
  if (lErrVal != ADC_E_NO_ERR)
  {
    /* [cover parentID={47948E71-2A49-49bd-B15B-279F0B98D147}]
    Report ADC_E_BUSY Error [/cover] */
    Adc_lReportRuntimeDetError(ADC_SID_ENABLE_HARDWARE_TRIGGER, ADC_E_BUSY);
  }
  return(lErrVal);
}
#endif

#if(((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON)) && \
                                            (ADC_GRP_NOTIF_CAPABILITY ==STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={F44A611A-124E-4078-BB86-1757C5C2253C}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lCheckNotifCapableDet            **
**                    (                                                       **
**                      const uint32 KernelId                                 **
**                      const Adc_GroupType GroupId                           **
**                      const uint8 ServiceId                                 **
**                      const uint32 CoreId                                   **
**                    )                                                       **
**                                                                            **
** Description      :This function is to check ADC_E_NOTIF_CAPABILITY DET for **
**                   the ServiceId(API).                                      **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    GroupId - Group ID for the Kernel                       **
**                    ServiceId - Serive ID of the API                        **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lCheckNotifCapableDet(const uint32 KernelId,\
        const Adc_GroupType GroupId, const uint8 ServiceId, const uint32 CoreId)
{
  uint8 lErrVal = ADC_E_NO_ERR;
  Adc_NotifyFnPtrType lNotificationFn;

  lNotificationFn = Adc_ConfigPtr->CoreCfgPtr[CoreId]->\
                    HwUnitCfgPtr[KernelId]->GrpCfgPtr[GroupId].NotifyPtr;
  /* [cover parentID={C10525C5-9C9D-48ec-AB5F-CE7DCC1F842E}]
  Is Notification function pointer is NULL [/cover] */
  if((Adc_NotifyFnPtrType)0U == lNotificationFn)
  {
    /* [cover parentID={B8656CD5-B54E-48ec-B009-CFFA3CF95212}]
    Report ADC_E_NOTIF_CAPABILITY Det  [/cover] */
    Adc_lReportError(ServiceId, ADC_E_NOTIF_CAPABILITY);
    lErrVal = ADC_E_NOTIF_CAPABILITY;
  }
  return(lErrVal);
}
#endif

#if(((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON)) && \
    (ADC_HW_TRIGGER_API==STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={0377C5DD-7E9E-4549-8470-3D3BF8A9A898}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lCheckWrongConvModeDet           **
**                    (                                                       **
**                      const uint32 KernelId                                 **
**                      const Adc_GroupType GroupId                           **
**                      const uint8 ServiceId                                 **
**                      const uint32 CoreId                                   **
**                    )                                                       **
**                                                                            **
** Description      :This function is to check ADC_E_WRONG_CONV_MODE DET for  **
**                   the ServiceId(API).                                      **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    GroupId - Group ID for the Kernel                       **
**                    ServiceId - Serive ID of the API                        **
**                    CoreId - Logical CPU core ID                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lCheckWrongConvModeDet(const uint32 KernelId,\
        const Adc_GroupType GroupId, const uint8 ServiceId, const uint32 CoreId)
{
  uint8 lErrVal = ADC_E_NO_ERR;
  Adc_GroupConvModeType lConversionMode;

  lConversionMode = Adc_ConfigPtr->CoreCfgPtr[CoreId]->\
                    HwUnitCfgPtr[KernelId]->GrpCfgPtr[GroupId].ConvMode;
  /* [cover parentID={B415A15B-05CB-4070-9ECC-2560FDEE1D6D}]
  Is conversion mode is equal to continuous conversion mode [/cover] */
  if(lConversionMode == ADC_CONV_MODE_CONTINUOUS)
  {
    /* [cover parentID={D1C01A50-1442-4a1b-87B4-F5176C8784A5}]
    Report ADC_E_WRONG_CONV_MODE Det [/cover] */
    Adc_lReportError(ServiceId, ADC_E_WRONG_CONV_MODE);
    lErrVal = ADC_E_WRONG_CONV_MODE;
  }
  return(lErrVal);
}
#endif

#if((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={DD445580-5FE9-42fb-8E60-86901ABCF684}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lCheckParamPointerDet            **
**                    (                                                       **
**                      const void *const Ptr                                 **
**                      const uint8 ServiceId                                 **
**                    )                                                       **
**                                                                            **
** Description      :This function is to check ADC_E_PARAM_POINTER DET for    **
**                   the ServiceId(API).                                      **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : Ptr - Pointer                                           **
**                    ServiceId - Serive ID of the API                        **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lCheckParamPointerDet( const void * const Ptr,\
                                              const uint8 ServiceId )
{
  uint8 lErrVal = ADC_E_NO_ERR;

  /* [cover parentID={8614AB62-FB84-46d5-8A90-BD1A88C9FCF6}]
  Received pointer is equal to NULL Pointer [/cover] */
  if(NULL_PTR == Ptr)
  {
    /* [cover parentID={DB7CD1D4-FE0F-46da-B053-A949DCABCF27}]
    Update return value as ADC_E_PARAM_POINTER  & Report DET. [/cover] */
    Adc_lReportError(ServiceId, ADC_E_PARAM_POINTER);
    lErrVal = ADC_E_PARAM_POINTER;
  }
  return(lErrVal);
}
#endif

#if(((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON)) && \
    (ADC_LOW_POWER_STATE_SUPPORT==STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={22A4A913-449F-42e8-9966-1BB8830C4C68}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lCheckPowerStateNotSuppDet       **
**                    (                                                       **
**                      const uint8 ServiceId,                                **
**                      const Adc_PowerStateType PowerState                   **
**                    )                                                       **
**                                                                            **
** Description      :This function is to check the Power State Support DETs   **
**                   for Adc_PreparePowerState API                            **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different CPU cores                       **
**                                                                            **
** Parameters(in)   : PowerState - Target power state intended to be attained **
**                    ServiceId - Service ID of the API                       **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lCheckPowerStateNotSuppDet(\
                 const Adc_PowerStateType PowerState,const uint8 ServiceId )
{
  uint8 lErrVal;

  /* [cover parentID={E4592451-4948-4b9a-9E5C-618DD48FC5AC}]
  Is power state beyond the available power modes in the hardware [/cover] */
  if(PowerState > ADC_OFF)
  {
    /* Update the error status */
    lErrVal = ADC_E_POWER_STATE_NOT_SUPPORTED;
    /* [cover parentID={9029EE16-FD14-4690-B2E8-F52939AF337E}]
    Report ADC_E_POWER_STATE_NOT_SUPPORTED DET [/cover] */
    Adc_lReportError(ServiceId, ADC_E_POWER_STATE_NOT_SUPPORTED);
  }
  /* [cover parentID={F1C9F94F-102D-416d-A2B3-C8E614852863}]
  Is power state beyond the supported power modes from the configuration
  [/cover] */
  else if((((uint32)ADC_ONE_U << PowerState) & \
          (uint32)ADC_POWER_MODES_AVAILABLE) == (uint32)0U)
  {
    /* Update the error status */
    lErrVal = ADC_E_POWER_STATE_NOT_SUPPORTED;
    /* [cover parentID={9029EE16-FD14-4690-B2E8-F52939AF337E}]
    Report ADC_E_POWER_STATE_NOT_SUPPORTED DET [/cover] */
    Adc_lReportError(ServiceId, ADC_E_POWER_STATE_NOT_SUPPORTED);
  }
  else
  {
    /* return no error*/
    lErrVal = ADC_E_NO_ERR;
  }
  return(lErrVal);
}
#endif

#if(((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON)) && \
   (ADC_LOW_POWER_STATE_SUPPORT==STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={AB81997D-19F1-46d1-9A90-D85F43DE246D}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lCheckPeripheralPreparedDet      **
**                    (                                                       **
**                      const uint32 TargetPwrState                           **
**                      const uint8 ServiceId                                 **
**                    )                                                       **
**                                                                            **
** Description      :This function is to check the Peripheral Prepared DETs   **
**                   for Adc_SetPowerState API                                **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different CPU cores                       **
**                                                                            **
** Parameters(in)   : PowerState - Target power state intended to be attained **
**                    ServiceId - Service ID of the API                       **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lCheckPeripheralPreparedDet(const uint32 TargetPwrState,\
                                                   const uint8 ServiceId)
{
  uint8 lErrVal = ADC_E_NO_ERR;

  /* [cover parentID={FA1EDC17-3A24-4437-933C-6A98B6D370BF}]
  Requested power state is not prepared [/cover] */
  if( (TargetPwrState & (uint32)ADC_ONE_U) != (uint32)ADC_ONE_U )
  {
    /* Update error status */
    lErrVal = ADC_E_PERIPHERAL_NOT_PREPARED;
    /* [cover parentID={8183F4C5-8CE7-48d8-BD40-CD997FCA9803}]
    Report ADC_E_PERIPHERAL_NOT_PREPARED DET [/cover] */
    Adc_lReportError(ServiceId, ADC_E_PERIPHERAL_NOT_PREPARED);
  }
  return(lErrVal);
}
#endif

#if( ((ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
     ((MCAL_AR_VERSION == MCAL_AR_422) && (ADC_DEV_ERROR_DETECT == STD_ON))) \
     && (ADC_LOW_POWER_STATE_SUPPORT==STD_ON) )
/*******************************************************************************
** Traceability: [cover parentID={E53D87FA-E5C8-4d6d-A3DE-18C08518ADE0}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lCheckHwUnitDisEngagedDet        **
**                    (                                                       **
**                      const uint8 ServiceId,                                **
**                      const uint32 CoreId                                   **
**                    )                                                       **
**                                                                            **
** Description      :This function checks if any hardware group is not in     **
**                   state IDLE and reports hardware unit disengaged          **
**                   Development or Runtime Error for Adc_SetPowerState API   **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different CPU cores                       **
**                                                                            **
** Parameters(in)   : ServiceId - Service ID if the API                       **
**                    CoreId - Logical CPU core ID                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lCheckHwUnitDisEngagedDet(const uint8 ServiceId,\
                                                 const uint32 CoreId)
{
  const Adc_GlobalDataType *lKernelDataPtr;
  uint32 lKernelCount;
  uint8 lErrVal = ADC_E_NO_ERR;

  /* [cover parentID={569D5622-BB57-444c-BB07-6318D260388F}]
  Loop till the last kernel ID,missing or un-configured kernels will be
  NULL PTR in the config set [/cover] */
  for(lKernelCount=(uint32)0U; lKernelCount<ADC_MAX_KERNEL_ID; lKernelCount++)
  {
    /* [cover parentID={F6650E81-DC4B-430e-A59C-1853861C2686}]
    Is Kernel Configured to current Core [/cover] */
    if(Adc_ConfigPtr->CoreCfgPtr[CoreId]->HwUnitCfgPtr[lKernelCount] != \
        NULL_PTR)
    {
      /* Read base address of Kernal data pointer for core 8 */
      lKernelDataPtr = Adc_lGetKernelDataAddress(lKernelCount, CoreId);
      /* [cover parentID={862E386F-BC29-4415-851D-AD52AD05D16B}]
      Any group not in IDLE state or Notiifcaiton is enabled for any group
      [/cover] */
      if( (lKernelDataPtr->GrpStatus != (uint32)0U) || \
          (lKernelDataPtr->GrpNotifStatus != (uint32)0U) )
      {
        /* Update the error value */
        lErrVal = ADC_E_NOT_DISENGAGED;
        /* [cover parentID={9A99E6A3-9F2B-4879-90DA-F8D597DF9290}]
        Report ADC_E_NOT_DISENGAGED Error [/cover] */
        Adc_lReportRuntimeDetError(ServiceId, ADC_E_NOT_DISENGAGED);
        break;
      }
    }
  }

  return(lErrVal);
}
#endif

#if(((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON)) && \
    (ADC_LOW_POWER_STATE_SUPPORT==STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={C47DFD71-A20A-4bdd-BE9F-065F5B596282}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lCheckConverterOffDet            **
**                    (                                                       **
**                      const uint32 KernelId,                                **
**                      const uint8 ServiceId,                                **
**                    )                                                       **
**                                                                            **
** Description      :This function is to check ADC_E_CONVERTER_OFF DET for    **
**                   the ServiceId(API).                                      **
** [/cover]                                                                   **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different ADC hardware groups             **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    ServiceId - Service ID if the API                       **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lCheckConverterOffDet(const uint32 KernelId,\
                                             const uint8 ServiceId)
{
  uint8 lErrVal = ADC_E_NO_ERR;
  uint32 lPowerState;

  /* Read power state of the kernel */
  lPowerState = (uint32)(MODULE_EVADC.G[KernelId].ARBCFG.B.ANONS);
  lPowerState = (uint32)(ADC_TARGET_POWER_STATE_MASK & (~lPowerState));

  /* [cover parentID={89076792-A56A-4afe-BF8F-6B31A1891772}]
  Converter is in OFF state [/cover] */
  if(lPowerState == ADC_OFF)
  {
    /* [cover parentID={920C5BFE-F6F7-444f-9129-CD9CB15F1E65}]
    Report ADC_E_CONVERTER_OFF DET [/cover] */
    Adc_lReportError(ServiceId, ADC_E_CONVERTER_OFF);
    /* Update return value as ADC_E_CONVERTER_OFF */
    lErrVal = ADC_E_CONVERTER_OFF;
  }
  return(lErrVal);
}
#endif

#if((ADC_SAFETY_ENABLE == STD_ON) && (ADC_STARTUP_CALIB_API == STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={65F085DB-9358-43b1-8E29-6F65E6AC1F83}]      **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Adc_lCheckStartupCalibOngoingDet     **
**                    (                                                       **
**                       const uint32 KernelId,                               **
**                       const uint8 ServiceId                                **
**                    )                                                       **
**                                                                            **
** Description      : This API returns the status of the start-up calibration **
**                    for Adc_StartGroupConversion & Adc_EnableHardwareTrigger**
**                    Note: This API is available only when AdcCalibStatusApi **
**                    is true & Safety Enable is ON                           **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different CPU cores                       **
**                                                                            **
** Parameters(in)   : KernelId - Kernel ID                                    **
**                    ServiceId - Service ID if the API                       **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Error ID                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Adc_lCheckStartupCalibOngoingDet(const uint32 KernelId,\
                                                    const uint8 ServiceId)
{
  /* Initialize the error value */
  uint8 lErrVal = ADC_E_NO_ERR;

  /* [cover parentID={8F216966-F913-43ae-B240-67A6F3DF56A1}]
  Calibration is active [/cover] */
  if(MODULE_EVADC.G[KernelId].ARBCFG.B.CAL == (uint32)ADC_ONE_U)
  {
    /* Update error value with Calibration On-going */
    lErrVal = ADC_SE_CALIB_ONGOING;

    /* [cover parentID={98468243-DCED-475e-B902-061E3AEF31FB}]
    Report ADC_SE_CALIB_ONGOING Safety Error [/cover] */
    Mcal_ReportSafetyError(ADC_MODULE_ID, ADC_MODULE_INSTANCE, ServiceId, \
                           ADC_SE_CALIB_ONGOING);
  }
  return(lErrVal);
}
#endif

#if ((ADC_DEV_ERROR_DETECT == STD_ON) || (ADC_SAFETY_ENABLE == STD_ON))
/*******************************************************************************
** Traceability: [cover parentID={ABB0AC30-2202-479c-83F2-B05A2D892AD1}]      **
**                                                                            **
** Syntax           : static void Adc_lReportError                            **
**                    (                                                       **
**                       const uint8 ApiId,                                   **
**                       const uint8 ErrorId                                  **
**                    )                                                       **
**                                                                            **
** Description      : This function reports the DET or Safety Error           **
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
static void Adc_lReportError(const uint8 ApiId, const uint8 ErrorId)
{
  /* [cover parentID={355F0589-F6EA-4f2b-915B-88B31C4E687B}]
  DET is ON [/cover] */
  #if (ADC_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={AA871F77-EEAA-4a2d-96D9-419862CBC97C}]
  Report DET Error [/cover] */
  (void)Det_ReportError(ADC_MODULE_ID, ADC_MODULE_INSTANCE, ApiId, ErrorId);
  #endif

  /* [cover parentID={58EA4641-23B7-4d93-A3DE-371F59927735}]
  SAFETY is ON [/cover] */
  #if (ADC_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={CB3ACF8A-7DB5-4283-AC87-E968BA995230},
  {481FE4E7-02D4-4767-BB4E-74A4C880E110}] Report Safety Error [/cover] */
  Mcal_ReportSafetyError(ADC_MODULE_ID, ADC_MODULE_INSTANCE, ApiId, ErrorId);
  #endif
}
#endif

#if( (ADC_SAFETY_ENABLE == STD_ON) || (ADC_RUNTIME_ERROR_DETECT == STD_ON)||\
     ((MCAL_AR_VERSION == MCAL_AR_422) && (ADC_DEV_ERROR_DETECT == STD_ON)) )
/*******************************************************************************
** Traceability     :[cover parentID={BD05F7CF-95FD-4a35-8B7B-78747D9746E6}]  **
**                                                                            **
** Syntax           : static void Adc_lReportRuntimeDetError                  **
**                    (                                                       **
**                       const uint8 ApiId,                                   **
**                       const uint8 ErrorId                                  **
**                    )                                                       **
**                                                                            **
** Description      : This function reports the Runtime Error or DET Error and**
**                    Safety Error depending on the Autosar version.          **
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
static void Adc_lReportRuntimeDetError(const uint8 ApiId, const uint8 ErrorId)
{
  /* [cover parentID={B5164CDF-747F-45b6-910B-E8E48B7DF660}]
  Runtime Error Detection is only available in Autosar version AR440 [/cover] */
  #if(ADC_RUNTIME_ERROR_DETECT == STD_ON)
  /* [cover parentID={D267A3D8-236C-4bd6-B899-56EE54F5A08A}]
  Report the Runtime Error [/cover] */
  (void)Mcal_Wrapper_Det_ReportRuntimeError(ADC_MODULE_ID, ADC_MODULE_INSTANCE,
                               ApiId, ErrorId);
  #elif(MCAL_AR_VERSION == MCAL_AR_422)
    /* [cover parentID={3B6A4BB9-ED56-4222-9960-E4BB5DC18AD7}]
    DET is ON [/cover] */
    #if (ADC_DEV_ERROR_DETECT == STD_ON)
    /* [cover parentID={01F3BE59-CA0B-46e1-B9A0-7D3F8101B560}]
    Report the DET Error [/cover] */
    (void)Det_ReportError(ADC_MODULE_ID, ADC_MODULE_INSTANCE, ApiId, ErrorId);
    #endif

    /* [cover parentID={1867C543-A64C-49c0-BF52-21C4A4839412}]
    SAFETY is ON [/cover] */
    #if (ADC_SAFETY_ENABLE == STD_ON)
    /* [cover parentID={D41E5F04-6D6A-4ee0-87AD-CB844EB17B2D}]
    Report the Safety Error [/cover] */
    Mcal_ReportSafetyError(ADC_MODULE_ID, ADC_MODULE_INSTANCE, ApiId, ErrorId);
    #endif
  #endif
}
#endif

#if( (ADC_MULTICORE_ERROR_DETECT == STD_ON) || \
     ((ADC_SAFETY_ENABLE == STD_ON) && (MCAL_NO_OF_CORES > ADC_ONE_U)) )
/*******************************************************************************
** Traceability: [cover parentID={5A4190DE-6F5C-4ccc-8251-683D94DF6B46}]      **
**                                                                            **
** Syntax          : static void Adc_lReportMulticoreError                    **
**                   (                                                        **
**                      const uint8 ApiId,                                    **
**                      const uint8 ErrorId                                   **
**                   )                                                        **
**                                                                            **
** Description     : Function to report Safety Error and Multi-Core DET       **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : ApiId - Service ID of the API reporting an error         **
**                   ErrorId - ID of the error reported                       **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
*                                                                             **
*******************************************************************************/
static void Adc_lReportMulticoreError(const uint8 ApiId, const uint8 ErrorId)
{
  /* [cover parentID={A8608F1F-FFA0-4e35-9137-796F4D678EDA}]
  Multi-Core DET is ON [/cover] */
  #if (ADC_MULTICORE_ERROR_DETECT == STD_ON)
  /* [cover parentID={475931FE-D646-48b1-8299-BC61D25DD080}]
  Report Multi-Core DET Error [/cover] */
  (void)Det_ReportError(ADC_MODULE_ID, ADC_MODULE_INSTANCE, ApiId, ErrorId);
  #endif

  /* [cover parentID={CC6F5F83-81D0-42f2-84D9-5A7FD8956462}]
  SAFETY is ON [/cover] */
  #if (ADC_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={32BBFF20-665D-4142-B7EC-80C3BC24C87A},
  {481FE4E7-02D4-4767-BB4E-74A4C880E110}] Report Safety Error [/cover] */
  Mcal_ReportSafetyError(ADC_MODULE_ID, ADC_MODULE_INSTANCE, ApiId, ErrorId);
  #endif
}
#endif

#if ((ADC_CLC_FAILURE_DEM_NOTIF == ADC_ENABLE_DEM_REPORT)||\
     (ADC_CONV_STOP_TIME_DEM_NOTIF == ADC_ENABLE_DEM_REPORT))
/*******************************************************************************
** Traceability     : [cover parentID={EFD5B7DD-3CF9-40dc-A98E-92F2CD641A75}] **
**                                                                            **
** Syntax           : static void Adc_lReportDemError                         **
**                    (                                                       **
**                       const Dem_EventIdType EventId,                       **
**                       const Dem_EventStatusType EventStatus                **
**                    )                                                       **
**                                                                            **
** Description      : This function reports the Production error status       **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant for different Event IDs                       **
**                                                                            **
** Parameters (in)  : EventId - ID of the event reported                      **
**                    EventStatus - Status of the event reported              **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*                                                                             **
*******************************************************************************/
static void Adc_lReportDemError(const Dem_EventIdType EventId,
const Dem_EventStatusType EventStatus)
{
  /* [cover parentID={359CD9B0-BD82-45ea-802D-E668B175FC51}]
  Autosar version is AR422 [/cover] */
  #if (MCAL_AR_VERSION == MCAL_AR_422)
  /* [cover parentID={378278C7-FAE6-4885-81B0-9C4BD6A9F44C}]
  Report the Production error status [/cover] */
  Mcal_Wrapper_Dem_ReportErrorStatus(EventId, EventStatus);

  /* [cover parentID={8663E032-3451-4ca4-A5F0-2A1BA1656C83}]
  Autosar version is AR440 [/cover] */
  #else
  /* [cover parentID={FF90BA54-7482-481b-AE56-04C3B4D88762}]
  Report the Production error status [/cover] */
  (void)Mcal_Wrapper_Dem_SetEventStatus(EventId, EventStatus);

  #endif
}
#endif

/*[cover parentID={BA6EFE0D-B9E6-4630-BF56-93FFA7D4CB7F}]
Code Memory section executable by all cores
[/cover]*/
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
Code Memory section naming as per AS
[/cover]*/

/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
Callout Memory section not used in ADC driver
[/cover]*/
#define ADC_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Adc_MemMap.h"

