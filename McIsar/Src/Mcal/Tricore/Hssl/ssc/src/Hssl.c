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
**  FILENAME     : Hssl.c                                                     **
**                                                                            **
**  VERSION      : 1.40.0_17.0.0                                              **
**                                                                            **
**  DATE         : 2020-05-14                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Hssl Driver source file                                    **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "IfxSrc_reg.h"
#include "Hssl.h"
#include "IfxHssl_reg.h"
#include "SchM_Hssl.h"

/*User Mode and Supervisor Mode Macros*/
#if ((HSSL_INIT_API_MODE != HSSL_SUPERVISOR_MODE)||\
     (HSSL_RUN_TIME_API_MODE != HSSL_SUPERVISOR_MODE) )
#include "McalLib_OsStub.h"
#endif

#ifdef DISABLE
/* MISRA2012_RULE_20_5_JUSTIFICATION: DISABLE is undefined here to resolve 
 * the conflict between macro 'DISABLE'
 * (ObjectAccessType) used in OS module and 'DISABLE' SFR definitions.
 * This is to be done before including "IfxHsct_reg.h"
 */
#undef DISABLE
#endif
#include "IfxHsct_reg.h"
/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/
/*    VERSION CHECK FOR HSSL MODULE INCLUSION */
#ifndef HSSL_SW_MAJOR_VERSION
#error "HSSL_SW_MAJOR_VERSION is not defined. "
#endif

#ifndef HSSL_SW_MINOR_VERSION
#error "HSSL_SW_MINOR_VERSION is not defined. "
#endif

#ifndef HSSL_SW_PATCH_VERSION
#error "HSSL_SW_PATCH_VERSION is not defined. "
#endif

#if ( HSSL_SW_MAJOR_VERSION != 10U )
#error "HSSL_SW_MAJOR_VERSION does not match. "
#endif

#if ( HSSL_SW_MINOR_VERSION != 40U )
#error "HSSL_SW_MINOR_VERSION does not match. "
#endif

#if ( HSSL_SW_PATCH_VERSION != 2U)
#error "HSSL_SW_PATCH_VERSION does not match."
#endif

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
#define HSSL_WRITE_PENDING                   (1U)
#define HSSL_READ_PENDING                    (2U)
#define HSSL_MAX_NUMBER_OF_INSTANCES         (2U)
#define HSSL_MAX_NUMBER_OF_CHANNELS          (4U)
#define HSSL_TRIGGER_PENDING                 (3U)
#define HSSL_SET_FLAG                        (0xffffffffU)
#define HSSL_TIMEOUT                         (0xFFU)
#define HSSL_WAIT_COUNT                      (2000U)
#define HSSL_CHANNEL_CFG                     (2U)
#define HSSL_NUM_4                           (4U)
#define HSSL_NUM_8                           (8U)
#define HSSL_NUM_12                          (12U)
#define HSSL_NUM_16                          (16U)
#define HSSL_NUM_22                          (22U)
#define HSSL_FLAG_CFG                        (0xfU)
#define HSSL0_DATA_ADDR                      (0xF00800B0U)
#define HSSL1_DATA_ADDR                      (0xF00A00B0U)
#define HSSL0_FC_ADDR                        (0xF00800BCU)
#define HSSL1_FC_ADDR                        (0xF00A00BCU)
#define HSSL0_MFLAGSSET_ADDR                 (0xF008001CU)
#define HSSL1_MFLAGSSET_ADDR                 (0xF00A001CU)
#define HSSL_KERNEL_RESET_WAIT_COUNT         (0x00000100U)
#define HSSL_DMA_CHCFGR_REGVALUE_WRITE       (0x00510000U)
#define HSSL_DMA_CHCFGR_REGVALUE_READ        (0x00400000U)
#define HSSL_DMA_CHCFGR_TREL_MASK            (0xFFFF3FFFU)
#define HSSL_PERIPHERAL_ON                   (1U)
#define HSSL_DMA_OPERATION_COMPLETED         (0U)
#define HSSL_DMA_OPERATION_IN_PROGRESS       (1U)
#define HSSL_CRC_EN_SHIFT                    (16U)
#define HSSL_INIT_API                        (0U)
#define HSSL_RUNTIME_API                     (1U)

#if (HSSL_INTERFACE_MODE == HSSL_MASTER)
#if(HSSL_MULTI_SLAVE_MODE == STD_ON)
#define HSSL_MSCR_UPPER_HALF_WORD_OFF        (0x2U)
#define HSSL_ACTIVATON_IN_PROGRESS           (1U)
#define HSSL_ACTIVATION_COMPLETED            (0U)
#define HSSL_DEACTIVATON_IN_PROGRESS         (2U)
#define HSSL_DEACTIVATON_COMPLETED           (3U)
#define HSSL_SLAVE_TRANSMISSION_ON           (0U)
#define HSSL_SLAVE_TRANSMISSION_OFF           (1U)
#define HSSL_SLAVE_LVDS_DISABLE              (0x32U)
#endif
#endif
/*******************************************************************************
**                         User Mode Macros                                   **
*******************************************************************************/
#if(HSSL_INIT_API_MODE == HSSL_SUPERVISOR_MODE)
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for
   User mode support in code. No side effects foreseen by violating this MISRA
   rule. */
#define HSSL_INIT_DEINIT_WRITEENDINITPROTREG(RegAdd,Data)   \
    Mcal_WritePeripEndInitProtReg(RegAdd,Data)
/* Supervisory mode registers */
  /* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
   * HSSL_SFR_INIT_DEINIT_WRITE32
   * defined for User mode support in code.
   * No side effects foreseen by violating this MISRA rule. */
#define HSSL_SFR_INIT_DEINIT_WRITE32(reg, value) (*(reg) = (uint32)(value))
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for
User mode support in code. No side effects foreseen by violating this MISRA
rule. */
#define HSSL_INIT_DEINIT_WRITEENDINITPROTREG(RegAdd,Data)   \
    MCAL_LIB_WRITEPERIPENDINITPROTREG(RegAdd,Data)
/* Supervisory mode registers */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
* SPI_SFR_INIT_DEINIT_WRITE32
* defined for User mode support in code.
* No side effects foreseen by violating this MISRA rule. */
#define HSSL_SFR_INIT_DEINIT_WRITE32(reg, value)    \
            MCAL_SFR_OS_WRITE32(HSSL_MODULE_ID, reg, value)
#endif

#if (HSSL_RUN_TIME_API_MODE == HSSL_SUPERVISOR_MODE)
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for
 User mode support in code. No side effects foreseen by violating this MISRA
 rule. */
#define HSSL_RUNTIME_WRITEENDINITPROTREG(RegAdd,Data)    \
    Mcal_WritePeripEndInitProtReg(RegAdd,Data)
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for
   User mode support in code. No side effects foreseen by violating this MISRA
   rule. */
#define HSSL_RUNTIME_WRITEENDINITPROTREG(RegAdd,Data)    \
    MCAL_LIB_WRITEPERIPENDINITPROTREG(RegAdd,Data)

#endif

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/
/* HSSL channel state. */
typedef enum
{
    HSSL_COMMAND_COMPLETED,
    HSSL_COMMAND_IN_PROGRESS
} Hssl_ChStateType;

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
#define HSSL_START_SEC_CODE_QM_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Hssl_MemMap.h"
static Std_ReturnType Hssl_lSetTargetAddress(const Hssl_InstanceID id,
                                             const uint32 *StartAddress,
                                             const uint32 DataSize);
static Std_ReturnType Hssl_lWriteAck(const Hssl_InstanceID id,
                                     const Hssl_ChannelType *const Channel);
static Std_ReturnType Hssl_lSingleFrameWrite(const Hssl_InstanceID id,\
        const Hssl_DataTemplateType *WriteData,\
        const uint16 DataSize,\
        const Hssl_ChannelType *const Channel,\
        const uint16 InjectedError,\
        uint32 *const NotificationDisable);
static void Hssl_lResetKernels(const uint32 id, const uint8 ApiType);
static Std_ReturnType Hsct_lInit(const uint32 id);
static void Hssl_lIsrError(const Hssl_InstanceID id, const uint8 Channel);
#if (HSSL_INTERFACE_MODE == HSSL_MASTER)
#if(HSSL_MULTI_SLAVE_MODE == STD_ON)
#if (HSSL_DEV_ERROR_DETECT == STD_ON)
static uint8 Hssl_lcheckSlaveParam(const Hssl_SlaveStatusType
                                     *Hssl_SlaveStatus);
#endif
static Std_ReturnType Hssl_lReadRply(const Hssl_InstanceID id,
                                     const Hssl_ChannelType *const Channel);
static Std_ReturnType Hssl_lTriggerRply(const Hssl_InstanceID id,
                                       const Hssl_ChannelType *const Channel);
static Std_ReturnType Hssl_lPollForSlaveExpectFlags(const Hssl_InstanceID id);
static void Hssl_lPollForMasterExpectFlags(const Hssl_InstanceID id);
#endif
#endif
#if (HSSL_DEV_ERROR_DETECT == STD_ON)
LOCAL_INLINE uint8 Hssl_lInitCallVerify(const Hssl_InstanceID id,\
                                        const uint8 ServiceId);
LOCAL_INLINE uint8 Hssl_lInstanceIDVerify(const Hssl_InstanceID id,\
        const uint8 ServiceId);
LOCAL_INLINE uint8 Hssl_lChannelVerify(const Hssl_InstanceID id, \
                                       const uint8 ChannelNumber,\
                                       const uint8 ServiceId);
LOCAL_INLINE uint8 Hssl_ldataSizeVerify(const Hssl_InstanceID id,\
                                        const uint16 DataSize,\
                                        const uint8 ServiceId);
LOCAL_INLINE uint8 Hssl_lRunModeVerify(const Hssl_InstanceID id,\
                                       const uint8 ServiceId);
static uint8 Hssl_lCheckParam(const uint8 ApiID,
                              const Hssl_DataTemplateType *WriteBuffer,
                              const Hssl_ReadDataTemplateType *ReadBuffer,
                              const uint32 *Buffer, const uint16 cmd);
#endif
static uint8 Hssl_lcheckDMAReadchannelUsage(const Hssl_InstanceID id);
static uint8 Hssl_lcheckDMAWritechannelUsage(const Hssl_InstanceID id);
#define HSSL_STOP_SEC_CODE_QM_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Hssl_MemMap.h"
/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
#define HSSL_START_SEC_VAR_CLEARED_QM_LOCAL_8
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Hssl_MemMap.h"
#if (HSSL_INTERFACE_MODE == HSSL_MASTER)
#if(HSSL_MULTI_SLAVE_MODE == STD_ON)
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable holds the state of slave
mode in multislave mode, hence it cannot be defined at block scope.*/
static uint8 HsslActivateSlaveState[HSSL_MAX_NUMBER_OF_INSTANCES];
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable holds the state of slave
mode in multislave mode, hence it cannot be defined at block scope.*/
static uint8 HsslDeactivateSlaveState[HSSL_MAX_NUMBER_OF_INSTANCES];
#endif
#endif
#if ( HSSL_DEV_ERROR_DETECT == STD_ON )
static uint8 Hssl_InterfaceMode[HSSL_NUM_INSTANCES_CONFIGURRED];
static uint8 Hssl_DriverState[HSSL_NUM_INSTANCES_CONFIGURRED];
#endif

#define HSSL_STOP_SEC_VAR_CLEARED_QM_LOCAL_8
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Hssl_MemMap.h"

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define HSSL_START_SEC_VAR_CLEARED_QM_LOCAL_32
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Hssl_MemMap.h"
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable holds the state of slave
mode in multislave mode, hence it cannot be defined at block scope.*/
static uint32 HsslActivateSlaveAPI[HSSL_MAX_NUMBER_OF_INSTANCES];
static uint32 HsslDeactivateSlaveAPI[HSSL_MAX_NUMBER_OF_INSTANCES];
static uint32 HsslStartStreamAPI[HSSL_MAX_NUMBER_OF_INSTANCES];
static uint32 Hssl_DMAWriteOperationState[HSSL_MAX_NUMBER_OF_INSTANCES];
static uint32 Hssl_DMAReadOperationState[HSSL_MAX_NUMBER_OF_INSTANCES];
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define HSSL_STOP_SEC_VAR_CLEARED_QM_LOCAL_32
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Hssl_MemMap.h"
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable holds the state of slave
mode in multislave mode, hence it cannot be defined at block scope.*/

/* HSSL base address Kernel wise */
#if (HSSL_NUM_INSTANCES_CONFIGURRED == 1U)
#if (HSSL0_CONFIGURRED == STD_ON)

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define HSSL_START_SEC_VAR_CLEARED_QM_LOCAL_32
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Hssl_MemMap.h"
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable holds the state of slave
mode in multislave mode, hence it cannot be defined at block scope.*/
static uint32 *Hssl0ReadDataBuffer[HSSL_MAX_NUMBER_OF_CHANNELS];
static Hssl_ChStateType Hssl0ChState[HSSL_MAX_NUMBER_OF_CHANNELS];
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define HSSL_STOP_SEC_VAR_CLEARED_QM_LOCAL_32
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Hssl_MemMap.h"

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define HSSL_START_SEC_CONST_QM_LOCAL_32
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Hssl_MemMap.h"
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable holds the state of slave
mode in multislave mode, hence it cannot be defined at block scope.*/
static Ifx_HSCT* const HSCT_Reg[] = {&MODULE_HSCT0};
static Ifx_HSSL* const HSSL_Reg[] = {&MODULE_HSSL0};
/* MISRA2012_RULE_8_9_JUSTIFICATION: The array contains the configuration data
for Init function. In order to limit stack usage, all such data is defined
 globally. Hence it can't be defined at block scope.*/
static const uint32 HSSL_WindowStartAddr[] = {HSSL0_ACCESS_WINDOW_START_ADDR0,\
                                              HSSL0_ACCESS_WINDOW_START_ADDR1,\
                                              HSSL0_ACCESS_WINDOW_START_ADDR2,\
                                              HSSL0_ACCESS_WINDOW_START_ADDR3};
/* MISRA2012_RULE_8_9_JUSTIFICATION: The array contains the configuration data
for Init function. In order to limit stack usage, all such data is defined
 globally. Hence it can't be defined at block scope.*/
static const uint32 HSSL_WindowEndAddr[] = {HSSL0_ACCESS_WINDOW_END_ADDR0,\
                                            HSSL0_ACCESS_WINDOW_END_ADDR1,\
                                            HSSL0_ACCESS_WINDOW_END_ADDR2,\
                                            HSSL0_ACCESS_WINDOW_END_ADDR3};
/* MISRA2012_RULE_8_9_JUSTIFICATION: The array contains the configuration data
for Init function. In order to limit stack usage, all such data is defined
 globally. Hence it can't be defined at block scope.*/
static const uint32 HSSL_AccessMode[] = {HSSL0_ACCESS_MODE_0,\
                                         HSSL0_ACCESS_MODE_1,\
                                         HSSL0_ACCESS_MODE_2,\
                                         HSSL0_ACCESS_MODE_3};
/* MISRA2012_RULE_8_9_JUSTIFICATION: The array contains the configuration data
for Init function. In order to limit stack usage, all such data is defined
 globally. Hence it can't be defined at block scope.*/
static const uint32 HSSL_Ch2TxMode[] = {HSSL0_STREAMING_MODE_TX};
/* MISRA2012_RULE_8_9_JUSTIFICATION: The array contains the configuration data
for Init function. In order to limit stack usage, all such data is defined
 globally. Hence it can't be defined at block scope.*/
static const uint32 HSSL_Ch2RxMode[] = {HSSL0_STREAMING_MODE_RX};
/* MISRA2012_RULE_8_9_JUSTIFICATION: The array contains the configuration data
for Init function. In order to limit stack usage, all such data is defined
 globally. Hence it can't be defined at block scope.*/
static const uint32 HSSL_Ch2Mode[] = {HSSL0_STREAMING_CH_MODE};
/* MISRA2012_RULE_8_9_JUSTIFICATION: The array contains the configuration data
for Init function. In order to limit stack usage, all such data is defined
 globally. Hence it can't be defined at block scope.*/
static const uint32 HSSL_TrgtAddr[] = {HSSL0_TIDADD_ADDR};
/* MISRA2012_RULE_8_9_JUSTIFICATION: The array contains the configuration data
for Init function. In order to limit stack usage, all such data is defined
 globally. Hence it can't be defined at block scope.*/
static const uint32 HSSL_RefrenceClock[] = {HSSL0_REFRENCE_CLK};
/* MISRA2012_RULE_8_9_JUSTIFICATION: The array contains the configuration data
for Init function. In order to limit stack usage, all such data is defined
 globally. Hence it can't be defined at block scope.*/
static const uint32 HSSL_SysClkDiv[] = {HSSL0_SYSCLK_DIV};
/* MISRA2012_RULE_8_9_JUSTIFICATION: The array contains the configuration data
for Init function. In order to limit stack usage, all such data is defined
 globally. Hence it can't be defined at block scope.*/
static const uint32 HSSL_MTXSpeed[] = {HSSL0_MASTER_TX_SPEED};
/* MISRA2012_RULE_8_9_JUSTIFICATION: The array contains the configuration data
for Init function. In order to limit stack usage, all such data is defined
 globally. Hence it can't be defined at block scope.*/
static const uint32 HSSL_MRXSpeed[] = {HSSL0_MASTER_RX_SPEED};
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define HSSL_STOP_SEC_CONST_QM_LOCAL_32
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Hssl_MemMap.h"
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define HSSL_START_SEC_VAR_INIT_QM_LOCAL_32
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Hssl_MemMap.h"
/* MISRA2012_RULE_8_9_JUSTIFICATION: This array holds the status of COK
interrupt notification , hence it cannot be defined at block scope.*/
static Hssl_UserNotify Hssl0_WriteNotificationFunc[] =
{HSSL0_CH0_WRITE_HANDLE_CALLBACK,
HSSL0_CH1_WRITE_HANDLE_CALLBACK,
HSSL0_CH2_WRITE_HANDLE_CALLBACK,
HSSL0_CH3_WRITE_HANDLE_CALLBACK};
/* MISRA2012_RULE_8_9_JUSTIFICATION: This array holds the state of write
notification, hence it cannot be defined at block scope.*/
static Hssl_DMAUserNotify Hssl0_DMAWriteNotificationFunc[] =
{HSSL0_DMA_MULTIWRITE_CALLBACK};
/* MISRA2012_RULE_8_9_JUSTIFICATION: This array holds the state of read
notification, hence it cannot be defined at block scope.*/
static Hssl_DMAUserNotify Hssl0_DMAReadNotificationFunc[] =
{HSSL0_DMA_MULTIREAD_CALLBACK};
/* MISRA2012_RULE_8_9_JUSTIFICATION: This array holds the status of RDI
interrupt notification , hence it cannot be defined at block scope.*/
static Hssl_UserNotify Hssl0_ReadNotificationFunc[] =
{HSSL0_CH0_READ_HANDLE_CALLBACK,
HSSL0_CH1_READ_HANDLE_CALLBACK,
HSSL0_CH2_READ_HANDLE_CALLBACK,
HSSL0_CH3_READ_HANDLE_CALLBACK};
/* MISRA2012_RULE_8_9_JUSTIFICATION: This array holds the status of Trigger
interrupt notification , hence it cannot be defined at block scope.*/
static Hssl_UserNotify Hssl0_TriggerNotificationFunc[] =
{HSSL0_CH0_TRIGGER_HANDLE_CALLBACK,
HSSL0_CH1_TRIGGER_HANDLE_CALLBACK,
HSSL0_CH2_TRIGGER_HANDLE_CALLBACK,
HSSL0_CH3_TRIGGER_HANDLE_CALLBACK};
/* MISRA2012_RULE_8_9_JUSTIFICATION: This array holds the status of Error
interrupt notification , hence it cannot be defined at block scope.*/
static Hssl_UserNotify Hssl0_ErrorNotificationFunc[] =
{HSSL0_CH0_ERROR_HANDLE_CALLBACK,
HSSL0_CH1_ERROR_HANDLE_CALLBACK,
HSSL0_CH2_ERROR_HANDLE_CALLBACK,
HSSL0_CH3_ERROR_HANDLE_CALLBACK};
/* MISRA2012_RULE_8_9_JUSTIFICATION: This array holds the status of Global
interrupt notification , hence it cannot be defined at block scope.*/
static Hssl_UserNotify Hssl0_EXINotificationFunc[] =
{HSSL0_EXI_HANDLE_CALLBACK};
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define HSSL_STOP_SEC_VAR_INIT_QM_LOCAL_32
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Hssl_MemMap.h"
#else
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define HSSL_START_SEC_VAR_CLEARED_QM_LOCAL_32
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Hssl_MemMap.h"
static Hssl_ChStateType Hssl1ChState[HSSL_MAX_NUMBER_OF_CHANNELS];
static uint32 *Hssl1ReadDataBuffer[HSSL_MAX_NUMBER_OF_CHANNELS];
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define HSSL_STOP_SEC_VAR_CLEARED_QM_LOCAL_32
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Hssl_MemMap.h"
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define HSSL_START_SEC_CONST_QM_LOCAL_32
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Hssl_MemMap.h"
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable holds the state of slave
mode in multislave mode, hence it cannot be defined at block scope.*/
static Ifx_HSCT* const HSCT_Reg[] = {&MODULE_HSCT1};
static Ifx_HSSL* const HSSL_Reg[] = {&MODULE_HSSL1};
/* MISRA2012_RULE_8_9_JUSTIFICATION: The array contains the configuration data
for Init function. In order to limit stack usage, all such data is defined
 globally. Hence it can't be defined at block scope.*/
static const uint32 HSSL_WindowStartAddr[] = {HSSL1_ACCESS_WINDOW_START_ADDR0,\
                                              HSSL1_ACCESS_WINDOW_START_ADDR1,\
                                              HSSL1_ACCESS_WINDOW_START_ADDR2,\
                                              HSSL1_ACCESS_WINDOW_START_ADDR3};
/* MISRA2012_RULE_8_9_JUSTIFICATION: The array contains the configuration data
for Init function. In order to limit stack usage, all such data is defined
 globally. Hence it can't be defined at block scope.*/
static const uint32 HSSL_WindowEndAddr[] = {HSSL1_ACCESS_WINDOW_END_ADDR0,\
                                            HSSL1_ACCESS_WINDOW_END_ADDR1,\
                                            HSSL1_ACCESS_WINDOW_END_ADDR2,\
                                            HSSL1_ACCESS_WINDOW_END_ADDR3};
/* MISRA2012_RULE_8_9_JUSTIFICATION: The array contains the configuration data
for Init function. In order to limit stack usage, all such data is defined
 globally. Hence it can't be defined at block scope.*/
static const uint32 HSSL_AccessMode[] = {HSSL1_ACCESS_MODE_0,\
                                         HSSL1_ACCESS_MODE_1,\
                                         HSSL1_ACCESS_MODE_2,\
                                         HSSL1_ACCESS_MODE_3};
/* MISRA2012_RULE_8_9_JUSTIFICATION: The array contains the configuration data
for Init function. In order to limit stack usage, all such data is defined
 globally. Hence it can't be defined at block scope.*/
static const uint32 HSSL_Ch2TxMode[] = {HSSL1_STREAMING_MODE_TX};
/* MISRA2012_RULE_8_9_JUSTIFICATION: The array contains the configuration data
for Init function. In order to limit stack usage, all such data is defined
 globally. Hence it can't be defined at block scope.*/
static const uint32 HSSL_Ch2RxMode[] = {HSSL1_STREAMING_MODE_RX};
/* MISRA2012_RULE_8_9_JUSTIFICATION: The array contains the configuration data
for Init function. In order to limit stack usage, all such data is defined
 globally. Hence it can't be defined at block scope.*/
static const uint32 HSSL_Ch2Mode[] = {HSSL1_STREAMING_CH_MODE};
/* MISRA2012_RULE_8_9_JUSTIFICATION: The array contains the configuration data
for Init function. In order to limit stack usage, all such data is defined
 globally. Hence it can't be defined at block scope.*/
static const uint32 HSSL_TrgtAddr[] = {HSSL1_TIDADD_ADDR};
/* MISRA2012_RULE_8_9_JUSTIFICATION: The array contains the configuration data
for Init function. In order to limit stack usage, all such data is defined
 globally. Hence it can't be defined at block scope.*/
static const uint32 HSSL_RefrenceClock[] = {HSSL1_REFRENCE_CLK};
/* MISRA2012_RULE_8_9_JUSTIFICATION: The array contains the configuration data
for Init function. In order to limit stack usage, all such data is defined
 globally. Hence it can't be defined at block scope.*/
static const uint32 HSSL_SysClkDiv[] = {HSSL1_SYSCLK_DIV};
/* MISRA2012_RULE_8_9_JUSTIFICATION: The array contains the configuration data
for Init function. In order to limit stack usage, all such data is defined
 globally. Hence it can't be defined at block scope.*/
static const uint32 HSSL_MTXSpeed[] = {HSSL1_MASTER_TX_SPEED};
/* MISRA2012_RULE_8_9_JUSTIFICATION: The array contains the configuration data
for Init function. In order to limit stack usage, all such data is defined
 globally. Hence it can't be defined at block scope.*/
static const uint32 HSSL_MRXSpeed[] = {HSSL1_MASTER_RX_SPEED};
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define HSSL_STOP_SEC_CONST_QM_LOCAL_32
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Hssl_MemMap.h"
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define HSSL_START_SEC_VAR_INIT_QM_LOCAL_32
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Hssl_MemMap.h"
/* MISRA2012_RULE_8_9_JUSTIFICATION: This array holds the status of COK
interrupt notification , hence it cannot be defined at block scope.*/
static Hssl_UserNotify Hssl1_WriteNotificationFunc[] =
{HSSL1_CH0_WRITE_HANDLE_CALLBACK,
HSSL1_CH1_WRITE_HANDLE_CALLBACK,
HSSL1_CH2_WRITE_HANDLE_CALLBACK,
HSSL1_CH3_WRITE_HANDLE_CALLBACK};
/* MISRA2012_RULE_8_9_JUSTIFICATION: This array holds the state of write
notification, hence it cannot be defined at block scope.*/
static Hssl_DMAUserNotify Hssl1_DMAWriteNotificationFunc[] =
{HSSL1_DMA_MULTIWRITE_CALLBACK};
/* MISRA2012_RULE_8_9_JUSTIFICATION: This array holds the state of read
notification, hence it cannot be defined at block scope.*/
static Hssl_DMAUserNotify Hssl1_DMAReadNotificationFunc[] =
{HSSL1_DMA_MULTIREAD_CALLBACK};
/* MISRA2012_RULE_8_9_JUSTIFICATION: This array holds the status of RDI
interrupt notification , hence it cannot be defined at block scope.*/
static Hssl_UserNotify Hssl1_ReadNotificationFunc[] =
{HSSL1_CH0_READ_HANDLE_CALLBACK,
HSSL1_CH1_READ_HANDLE_CALLBACK,
HSSL1_CH2_READ_HANDLE_CALLBACK,
HSSL1_CH3_READ_HANDLE_CALLBACK};
/* MISRA2012_RULE_8_9_JUSTIFICATION: This array holds the status of Trigger
interrupt notification , hence it cannot be defined at block scope.*/
static Hssl_UserNotify Hssl1_TriggerNotificationFunc[] =
{HSSL1_CH0_TRIGGER_HANDLE_CALLBACK,
HSSL1_CH1_TRIGGER_HANDLE_CALLBACK,
HSSL1_CH2_TRIGGER_HANDLE_CALLBACK,
HSSL1_CH3_TRIGGER_HANDLE_CALLBACK};
/* MISRA2012_RULE_8_9_JUSTIFICATION: This array holds the status of Error
interrupt notification , hence it cannot be defined at block scope.*/
static Hssl_UserNotify Hssl1_ErrorNotificationFunc[] =
{HSSL1_CH0_ERROR_HANDLE_CALLBACK,
HSSL1_CH1_ERROR_HANDLE_CALLBACK,
HSSL1_CH2_ERROR_HANDLE_CALLBACK,
HSSL1_CH3_ERROR_HANDLE_CALLBACK};
/* MISRA2012_RULE_8_9_JUSTIFICATION: This array holds the status of Global
interrupt notification , hence it cannot be defined at block scope.*/
static Hssl_UserNotify Hssl1_EXINotificationFunc[] =
{HSSL1_EXI_HANDLE_CALLBACK};
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define HSSL_STOP_SEC_VAR_INIT_QM_LOCAL_32
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Hssl_MemMap.h"
#endif
#endif

#if (HSSL_NUM_INSTANCES_CONFIGURRED == 2u)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define HSSL_START_SEC_VAR_CLEARED_QM_LOCAL_32
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Hssl_MemMap.h"
static Hssl_ChStateType Hssl0ChState[HSSL_MAX_NUMBER_OF_CHANNELS];
static Hssl_ChStateType Hssl1ChState[HSSL_MAX_NUMBER_OF_CHANNELS];
static uint32 *Hssl0ReadDataBuffer[HSSL_MAX_NUMBER_OF_CHANNELS];
static uint32 *Hssl1ReadDataBuffer[HSSL_MAX_NUMBER_OF_CHANNELS];
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define HSSL_STOP_SEC_VAR_CLEARED_QM_LOCAL_32
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Hssl_MemMap.h"

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define HSSL_START_SEC_CONST_QM_LOCAL_32
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Hssl_MemMap.h"
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable holds the state of slave
mode in multislave mode, hence it cannot be defined at block scope.*/
static Ifx_HSCT* const HSCT_Reg[] = {&MODULE_HSCT0,&MODULE_HSCT1};
static Ifx_HSSL* const HSSL_Reg[] = {&MODULE_HSSL0,&MODULE_HSSL1};
/* MISRA2012_RULE_8_9_JUSTIFICATION: The array contains the configuration data
for Init function. In order to limit stack usage, all such data is defined
 globally. Hence it can't be defined at block scope.*/
static const uint32 HSSL_WindowStartAddr[] = {HSSL0_ACCESS_WINDOW_START_ADDR0,\
                                              HSSL0_ACCESS_WINDOW_START_ADDR1,\
                                              HSSL0_ACCESS_WINDOW_START_ADDR2,\
                                              HSSL0_ACCESS_WINDOW_START_ADDR3,\
                                              HSSL1_ACCESS_WINDOW_START_ADDR0,\
                                              HSSL1_ACCESS_WINDOW_START_ADDR1,\
                                              HSSL1_ACCESS_WINDOW_START_ADDR2,\
                                              HSSL1_ACCESS_WINDOW_START_ADDR3};
/* MISRA2012_RULE_8_9_JUSTIFICATION: The array contains the configuration data
for Init function. In order to limit stack usage, all such data is defined
 globally. Hence it can't be defined at block scope.*/
static const uint32 HSSL_WindowEndAddr[] = {HSSL0_ACCESS_WINDOW_END_ADDR0,\
                                            HSSL0_ACCESS_WINDOW_END_ADDR1,\
                                            HSSL0_ACCESS_WINDOW_END_ADDR2,\
                                            HSSL0_ACCESS_WINDOW_END_ADDR3,\
                                            HSSL1_ACCESS_WINDOW_END_ADDR0,\
                                            HSSL1_ACCESS_WINDOW_END_ADDR1,\
                                            HSSL1_ACCESS_WINDOW_END_ADDR2,\
                                            HSSL1_ACCESS_WINDOW_END_ADDR3};
/* MISRA2012_RULE_8_9_JUSTIFICATION: The array contains the configuration data
for Init function. In order to limit stack usage, all such data is defined
 globally. Hence it can't be defined at block scope.*/
static const uint32 HSSL_AccessMode[] = {HSSL0_ACCESS_MODE_0,\
                                         HSSL0_ACCESS_MODE_1,\
                                         HSSL0_ACCESS_MODE_2,\
                                         HSSL0_ACCESS_MODE_3,\
                                         HSSL1_ACCESS_MODE_0,\
                                         HSSL1_ACCESS_MODE_1,\
                                         HSSL1_ACCESS_MODE_2,\
                                         HSSL1_ACCESS_MODE_3};
/* MISRA2012_RULE_8_9_JUSTIFICATION: The array contains the configuration data
for Init function. In order to limit stack usage, all such data is defined
 globally. Hence it can't be defined at block scope.*/
static const uint32 HSSL_Ch2TxMode[] = {HSSL0_STREAMING_MODE_TX,\
                                        HSSL1_STREAMING_MODE_TX};
/* MISRA2012_RULE_8_9_JUSTIFICATION: The array contains the configuration data
for Init function. In order to limit stack usage, all such data is defined
 globally. Hence it can't be defined at block scope.*/
static const uint32 HSSL_Ch2RxMode[] = {HSSL0_STREAMING_MODE_RX,\
                                        HSSL1_STREAMING_MODE_RX};
/* MISRA2012_RULE_8_9_JUSTIFICATION: The array contains the configuration data
for Init function. In order to limit stack usage, all such data is defined
 globally. Hence it can't be defined at block scope.*/
static const uint32 HSSL_Ch2Mode[] = {HSSL0_STREAMING_CH_MODE,\
                                      HSSL1_STREAMING_CH_MODE};
/* MISRA2012_RULE_8_9_JUSTIFICATION: The array contains the configuration data
for Init function. In order to limit stack usage, all such data is defined
 globally. Hence it can't be defined at block scope.*/
static const uint32 HSSL_TrgtAddr[] = {HSSL0_TIDADD_ADDR, HSSL1_TIDADD_ADDR};
/* MISRA2012_RULE_8_9_JUSTIFICATION: The array contains the configuration data
for Init function. In order to limit stack usage, all such data is defined
 globally. Hence it can't be defined at block scope.*/
static const uint32 HSSL_RefrenceClock[] = {HSSL0_REFRENCE_CLK,\
                                            HSSL1_REFRENCE_CLK};
/* MISRA2012_RULE_8_9_JUSTIFICATION: The array contains the configuration data
for Init function. In order to limit stack usage, all such data is defined
 globally. Hence it can't be defined at block scope.*/
static const uint32 HSSL_SysClkDiv[] = {HSSL0_SYSCLK_DIV,\
                                        HSSL1_SYSCLK_DIV};
/* MISRA2012_RULE_8_9_JUSTIFICATION: The array contains the configuration data
for Init function. In order to limit stack usage, all such data is defined
 globally. Hence it can't be defined at block scope.*/
static const uint32 HSSL_MTXSpeed[] = {HSSL0_MASTER_TX_SPEED,\
                                       HSSL1_MASTER_TX_SPEED};
/* MISRA2012_RULE_8_9_JUSTIFICATION: The array contains the configuration data
for Init function. In order to limit stack usage, all such data is defined
 globally. Hence it can't be defined at block scope.*/
static const uint32 HSSL_MRXSpeed[] = {HSSL0_MASTER_RX_SPEED,\
                                       HSSL1_MASTER_RX_SPEED};
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define HSSL_STOP_SEC_CONST_QM_LOCAL_32
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Hssl_MemMap.h"
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define HSSL_START_SEC_VAR_INIT_QM_LOCAL_32
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Hssl_MemMap.h"
/* MISRA2012_RULE_8_9_JUSTIFICATION: This array holds the status of COK
interrupt notification , hence it cannot be defined at block scope.*/
static Hssl_UserNotify Hssl0_WriteNotificationFunc[] =
{HSSL0_CH0_WRITE_HANDLE_CALLBACK,
HSSL0_CH1_WRITE_HANDLE_CALLBACK,
HSSL0_CH2_WRITE_HANDLE_CALLBACK,
HSSL0_CH3_WRITE_HANDLE_CALLBACK};
/* MISRA2012_RULE_8_9_JUSTIFICATION: This array holds the status of RDI
interrupt notification , hence it cannot be defined at block scope.*/
static Hssl_UserNotify Hssl0_ReadNotificationFunc[] =
{HSSL0_CH0_READ_HANDLE_CALLBACK,
HSSL0_CH1_READ_HANDLE_CALLBACK,
HSSL0_CH2_READ_HANDLE_CALLBACK,
HSSL0_CH3_READ_HANDLE_CALLBACK};
/* MISRA2012_RULE_8_9_JUSTIFICATION: This array holds the state of write
notification, hence it cannot be defined at block scope.*/
static Hssl_DMAUserNotify Hssl1_DMAWriteNotificationFunc[] =
{HSSL1_DMA_MULTIWRITE_CALLBACK};
/* MISRA2012_RULE_8_9_JUSTIFICATION: This array holds the state of read
notification, hence it cannot be defined at block scope.*/
static Hssl_DMAUserNotify Hssl1_DMAReadNotificationFunc[] =
{HSSL1_DMA_MULTIREAD_CALLBACK};
/* MISRA2012_RULE_8_9_JUSTIFICATION: This array holds the status of Trigger
interrupt notification , hence it cannot be defined at block scope.*/
static Hssl_UserNotify Hssl0_TriggerNotificationFunc[] =
{HSSL0_CH0_TRIGGER_HANDLE_CALLBACK,
HSSL0_CH1_TRIGGER_HANDLE_CALLBACK,
HSSL0_CH2_TRIGGER_HANDLE_CALLBACK,
HSSL0_CH3_TRIGGER_HANDLE_CALLBACK};
/* MISRA2012_RULE_8_9_JUSTIFICATION: This array holds the status of Error
interrupt notification , hence it cannot be defined at block scope.*/
static Hssl_UserNotify Hssl0_ErrorNotificationFunc[] =
{HSSL0_CH0_ERROR_HANDLE_CALLBACK,
HSSL0_CH1_ERROR_HANDLE_CALLBACK,
HSSL0_CH2_ERROR_HANDLE_CALLBACK,
HSSL0_CH3_ERROR_HANDLE_CALLBACK};
/* MISRA2012_RULE_8_9_JUSTIFICATION: This array holds the status of Global
interrupt notification , hence it cannot be defined at block scope.*/
static Hssl_UserNotify Hssl0_EXINotificationFunc[] =
{HSSL0_EXI_HANDLE_CALLBACK};
/* MISRA2012_RULE_8_9_JUSTIFICATION: This array holds the state of write
notification, hence it cannot be defined at block scope.*/
static Hssl_DMAUserNotify Hssl0_DMAWriteNotificationFunc[] =
{HSSL0_DMA_MULTIWRITE_CALLBACK};
/* MISRA2012_RULE_8_9_JUSTIFICATION: This array holds the state of read
notification, hence it cannot be defined at block scope.*/
static Hssl_DMAUserNotify Hssl0_DMAReadNotificationFunc[] =
{HSSL0_DMA_MULTIREAD_CALLBACK};
/* MISRA2012_RULE_8_9_JUSTIFICATION: This array holds the status of COK
interrupt notification , hence it cannot be defined at block scope.*/
static Hssl_UserNotify Hssl1_WriteNotificationFunc[] =
{HSSL1_CH0_WRITE_HANDLE_CALLBACK,
HSSL1_CH1_WRITE_HANDLE_CALLBACK,
HSSL1_CH2_WRITE_HANDLE_CALLBACK,
HSSL1_CH3_WRITE_HANDLE_CALLBACK};
/* MISRA2012_RULE_8_9_JUSTIFICATION: This array holds the status of RDI
interrupt notification , hence it cannot be defined at block scope.*/
static Hssl_UserNotify Hssl1_ReadNotificationFunc[] =
{HSSL1_CH0_READ_HANDLE_CALLBACK,
HSSL1_CH1_READ_HANDLE_CALLBACK,
HSSL1_CH2_READ_HANDLE_CALLBACK,
HSSL1_CH3_READ_HANDLE_CALLBACK};
/* MISRA2012_RULE_8_9_JUSTIFICATION: This array holds the status of trigger
interrupt notification , hence it cannot be defined at block scope.*/
static Hssl_UserNotify Hssl1_TriggerNotificationFunc[] =
{HSSL1_CH0_TRIGGER_HANDLE_CALLBACK,
HSSL1_CH1_TRIGGER_HANDLE_CALLBACK,
HSSL1_CH2_TRIGGER_HANDLE_CALLBACK,
HSSL1_CH3_TRIGGER_HANDLE_CALLBACK};
/* MISRA2012_RULE_8_9_JUSTIFICATION: This array holds the status of Error
interrupt notification , hence it cannot be defined at block scope.*/
static Hssl_UserNotify Hssl1_ErrorNotificationFunc[] =
{HSSL1_CH0_ERROR_HANDLE_CALLBACK,
HSSL1_CH1_ERROR_HANDLE_CALLBACK,
HSSL1_CH2_ERROR_HANDLE_CALLBACK,
HSSL1_CH3_ERROR_HANDLE_CALLBACK};
/* MISRA2012_RULE_8_9_JUSTIFICATION: This array holds the status of Global
interrupt notification , hence it cannot be defined at block scope.*/
static Hssl_UserNotify Hssl1_EXINotificationFunc[] =
{HSSL1_EXI_HANDLE_CALLBACK};
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define HSSL_STOP_SEC_VAR_INIT_QM_LOCAL_32
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Hssl_MemMap.h"
#endif

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define HSSL_START_SEC_CODE_QM_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Hssl_MemMap.h"
/*
 CYCLOMATIC_Hssl_SetMode_JUSTIFICATION: This function sets the HSSL interface
 mode. For better readability, all conditions are kept in the same function*/
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_SetMode(const Hssl_InstanceID id,    **
**                                                      const uint8 Mode)     **
**                                                                            **
** Description     : Puts the HSSL module into the required mode.             **
**                   Must be used to place module into 'INIT' mode before     **
**                   calling the initialization functions.                    **
**                   function.                                                **
**                                                                            **
** Service ID      : 0x3A                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id - Specifies HSSL instance (0: HSSL0, 1: HSSL1)        **
**                   Mode                                                     **
**                   0 = Sleep, 1 = Enabled/Init, 2 = Enabled/Run             **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
Std_ReturnType Hssl_SetMode(const Hssl_InstanceID id, const uint8 Mode)
{
    Std_ReturnType RetVal;
    uint32 WaitCount;

    /* Parameter check for the API if DET is STD_ON*/
#if ( HSSL_DEV_ERROR_DETECT == STD_ON )
    uint8 ErrorFlag;
    RetVal = E_NOT_OK;

    /* Check for the proper HSSL instance */
    ErrorFlag = Hssl_lInstanceIDVerify(id, HSSL_SID_MODE);
    if (ErrorFlag == HSSL_ERR_NOT_FOUND)
    {
         /* Check for driver initialization */
         ErrorFlag = Hssl_lInitCallVerify(id, HSSL_SID_MODE);
        if (ErrorFlag == HSSL_ERR_NOT_FOUND)
        {
        /* Check If the Mode passed is a Valid one */
        if ((HSSL_MODE_RUN == Mode) || (HSSL_MODE_SLEEP == Mode) ||\
                (HSSL_MODE_INIT == Mode))
        {
            /* Check the mode transition */
            if (HSSL_MODE_SLEEP == Hssl_InterfaceMode[id])
            {
                if (HSSL_MODE_RUN == Mode)
                {
                    Det_ReportError(HSSL_MODULE_ID,HSSL_MODULE_INSTANCE,\
                                    HSSL_SID_MODE,HSSL_E_INV_MODE);
                    /*Error flag is set*/
                    ErrorFlag = HSSL_ERR_FOUND;
                }
            }
        }
        else /* Mode parameter is wrong */
        {
            Det_ReportError(HSSL_MODULE_ID,HSSL_MODULE_INSTANCE,\
                            HSSL_SID_MODE,HSSL_E_INV_PARAM);
            ErrorFlag = HSSL_ERR_FOUND;
        }
        }
    }
    /*If no error present*/
    if (HSSL_ERR_NOT_FOUND == ErrorFlag)
#endif
        /*End Of HSSL_DEV_ERROR_DETECT*/
    {
        RetVal = E_OK;
        /* check the mode and set the sfr accordingly */
        switch (Mode)
        {
        case HSSL_MODE_SLEEP:
        {
            /* Disable HSSL module */
           HSSL_RUNTIME_WRITEENDINITPROTREG(&HSSL_Reg[id]->CLC,0X08U);
           HSCT_Reg[id]->SLEEPCTRL.B.SLPEN  = 1U;

            /* Check the status bit DISS to be Set */
            if (HSSL_Reg[id]->CLC.B.EDIS == 1U)
            {
#if ( HSSL_DEV_ERROR_DETECT == STD_ON )
                Hssl_InterfaceMode[id] = HSSL_MODE_SLEEP;
#endif
            }
            else
            {
                RetVal = E_NOT_OK;
            }
        }
        break;

        case HSSL_MODE_INIT:
        {
#if ( HSSL_DEV_ERROR_DETECT == STD_ON )
            Hssl_InterfaceMode[id] = HSSL_MODE_INIT;
#endif
            /* Set the Module to INIT mode */
            HSSL_Reg[id]->MFLAGSSET.B.INIS = 1U;
        }
        break;

        case HSSL_MODE_RUN:
        {
            /* Set the Module to RUN mode */
            HSSL_Reg[id]->MFLAGSCL.B.INIC = 1U;

            WaitCount = (uint32)HSSL_WAIT_COUNT;
            while ((HSSL_Reg[id]->MFLAGS.B.INI == 1U) && (WaitCount > 0U))
            {
                WaitCount--;
            }

            if (WaitCount != 0U)
            {
#if ( HSSL_DEV_ERROR_DETECT == STD_ON )
                Hssl_InterfaceMode[id] = HSSL_MODE_RUN;
#endif
            }
            else
            {
                RetVal = E_NOT_OK;
            }
        }
        break;

        default:
        /* default case */
        break;
        }
    }/* if (HSSL_ERR_FOUND != ErrorFlag)   */
    return RetVal;
}
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_Reset(const Hssl_InstanceID id)      **
**                                                                            **
** Description     : Performs Kernel reset of module,clears all status and    **
**                   error registers, disables module clock and sets driver   **
**                   module.  Any transfers in progress when reset is called  **
**                   will immediately end.                                    **
**                                                                            **
** Service ID      : 0x3B                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id - Specifies HSSL instance (0: HSSL0, 1: HSSL1)        **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
Std_ReturnType Hssl_Reset(const Hssl_InstanceID id)
{
    Std_ReturnType RetVal = E_NOT_OK;

    /* Parameter check for the API if DET is STD_ON*/
#if ( HSSL_DEV_ERROR_DETECT == STD_ON )
    uint8 ErrorFlag = HSSL_ERR_NOT_FOUND;

    /* Check for the proper HSSL instance */
    ErrorFlag = Hssl_lInstanceIDVerify(id, HSSL_SID_RESET);
    if (HSSL_ERR_NOT_FOUND == ErrorFlag)
    {
        /* Check for driver initialization */
         ErrorFlag = Hssl_lInitCallVerify(id, HSSL_SID_RESET);
    }
    if (HSSL_ERR_NOT_FOUND == ErrorFlag)
#endif     /*End Of HSSL_DEV_ERROR_DETECT*/
    {
        HSSL_Reg[id]->MFLAGSCL.U = HSSL_SET_FLAG;
        RetVal = E_OK;
        /* Reset HSSL module */
        Hssl_lResetKernels((uint32)id, HSSL_RUNTIME_API);
#if ( HSSL_DEV_ERROR_DETECT == STD_ON )
        /* Reset Driver State */
        Hssl_DriverState[id] = HSSL_DRIVER_UNINITIALIZED;
        Hssl_InterfaceMode[id] = HSSL_MODE_INIT;
#endif
    }
    return (RetVal);
}
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_Init(                                **
**                        const Hssl_ConfigType* const Address)               **
**                                                                            **
** Description     : Initializes Initiator / Target side of HSSL module.      **
**                                                                            **
** Service ID      : 0x3C                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : Address: NULL pointer                                    **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
Std_ReturnType Hssl_Init(const Hssl_ConfigType* const Address)
{
    Std_ReturnType RetVal =E_OK;
    volatile uint32 ClkDisableChk;
    uint32 AccessRules;
    uint32 Index;
    UNUSED_PARAMETER(Address);
#if ( HSSL_DEV_ERROR_DETECT == STD_ON )
    if ( Address != NULL_PTR )
    {
        Det_ReportError(HSSL_MODULE_ID,HSSL_MODULE_INSTANCE,HSSL_SID_INIT,\
                        HSSL_E_INV_PARAM);
        RetVal = E_NOT_OK;
    }
    else
#endif
    {
        for (Index = 0U; ((Index < HSSL_NUM_INSTANCES_CONFIGURRED) &&
                          (RetVal == E_OK)); Index++)
        {
            /* Enable HSCT module */
            HSSL_INIT_DEINIT_WRITEENDINITPROTREG(&HSCT_Reg[Index]->CLC,\
                    HSCT_MOD_ENABLE);
            /* Enable HSSL module */
            HSSL_INIT_DEINIT_WRITEENDINITPROTREG(&HSSL_Reg[Index]->CLC,\
                    HSSL_MOD_ENABLE);

            ClkDisableChk = HSSL_Reg[Index]->CLC.B.DISS;
            /* Check the status bit DISS is Zero*/
            if (0U == ClkDisableChk)
            {

            Hssl_lResetKernels(Index, HSSL_INIT_API);
            RetVal = Hsct_lInit(Index);
            if (RetVal == E_OK)
            {

            /* Set the Global Pre-divider */
            HSSL_Reg[Index]->CFG.B.PREDIV  = HSSL_CLOCK_PREDIVIDER;

            /* Set the start and End address of access windows where HSSL access
            are allowed */
            HSSL_SFR_INIT_DEINIT_WRITE32(&HSSL_Reg[Index]->AW[0].AWSTART.U,
                         HSSL_WindowStartAddr[Index]);

            HSSL_SFR_INIT_DEINIT_WRITE32(&HSSL_Reg[Index]->AW[0].AWEND.U,
                                        HSSL_WindowEndAddr[Index]);
            HSSL_SFR_INIT_DEINIT_WRITE32(&HSSL_Reg[Index]->AW[1].AWSTART.U,
             HSSL_WindowStartAddr[Index + 1U]);
            HSSL_SFR_INIT_DEINIT_WRITE32(&HSSL_Reg[Index]->AW[1].AWEND.U,
                                      HSSL_WindowEndAddr[Index + 1U]);
            HSSL_SFR_INIT_DEINIT_WRITE32(&HSSL_Reg[Index]->AW[2].AWSTART.U,
                        HSSL_WindowStartAddr[Index + 2U]);
            HSSL_SFR_INIT_DEINIT_WRITE32(&HSSL_Reg[Index]->AW[2].AWEND.U,
            HSSL_WindowEndAddr[Index + 2U]);
            HSSL_SFR_INIT_DEINIT_WRITE32(&HSSL_Reg[Index]->AW[3].AWSTART.U,
                            HSSL_WindowStartAddr[Index + 3U]);
            HSSL_SFR_INIT_DEINIT_WRITE32(&HSSL_Reg[Index]->AW[3].AWEND.U,
                      HSSL_WindowEndAddr[Index + 3U]);

            /* Allow read/write access for all windows  */
            AccessRules = ((HSSL_AccessMode[Index]) |
                            (HSSL_AccessMode[Index + 1U] << 2U) |
                            (HSSL_AccessMode[Index + 2U] << 4U) |
                            (HSSL_AccessMode[Index + 3U] << 6U));

            HSSL_SFR_INIT_DEINIT_WRITE32(&HSSL_Reg[Index]->AR.U, AccessRules);

            /* Set Channel 2 Mode to Streaming / Command */
            HSSL_Reg[Index]->CFG.B.SCM  = (uint8)HSSL_Ch2Mode[Index];
            HSSL_Reg[Index]->CFG.B.SMT  = (uint8)HSSL_Ch2TxMode[Index];
            HSSL_Reg[Index]->CFG.B.SMR  = (uint8)HSSL_Ch2RxMode[Index];

            /* Enable CRC Error interrupt */
            HSSL_Reg[Index]->MFLAGSEN.B.CRCEEN = 1U;
            HSSL_SFR_INIT_DEINIT_WRITE32(&HSSL_Reg[Index]->TIDADD.U, HSSL_TrgtAddr[Index]);
#if (HSSL_MULTI_SLAVE_MODE == STD_ON)
            HSSL_Reg[Index]->MSCR.B.EN = 1U;
#endif
#if ( HSSL_DEV_ERROR_DETECT == STD_ON )
            /* Set Driver State to Initialised */
            Hssl_DriverState[Index] = HSSL_DRIVER_INITIALIZED;
#endif
            }
            }
            else
            {
                RetVal = E_NOT_OK;
#if ( HSSL_DEV_ERROR_DETECT == STD_ON )
                /* Reset Driver State */
                Hssl_DriverState[Index] = HSSL_DRIVER_UNINITIALIZED;
#endif
            }
        }
    }
    return (RetVal);
}
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_InitChannel(                         **
**                                          const Hssl_InstanceID id,         **
**                                    const Hssl_ChannelType *const Channel,  **
**                                          const uint8 TimeoutErr,           **
**                                          const uint8 TransID,              **
**                                          const uint8 AckErr)               **
**                                                                            **
** Description     : Initializes HSSL Channel. Also sets up interrupts.       **
**                   events to handle received packets appropriately.         **
**                                                                            **
** Service ID      : 0x3D                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id - Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   Channel : HSSL Channel to use.                           **
**                   TimeoutErr: Enable/Disable Timeout Error interrupt.      **
**                   TransID: Enable/Disable Transaction ID Error interrupt.  **
**                   AckErr: Enable/Disable Acknowledge Error interrupt.      **
**                     (0 to disable, 1 to enable)                            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
Std_ReturnType Hssl_InitChannel(const Hssl_InstanceID id,\
                      const Hssl_ChannelType *const Channel, 
                      const uint8 TimeoutErr,\
                      const uint8 TransID, const uint8 AckErr)
{
    Std_ReturnType RetVal;

    /* Parameter check for the API if DET is STD_ON*/
#if ( HSSL_DEV_ERROR_DETECT == STD_ON )
    uint8 ErrorFlag;

    RetVal = E_NOT_OK;
    ErrorFlag = Hssl_lInstanceIDVerify(id, HSSL_SID_INIT_CH);
    if (HSSL_ERR_FOUND != ErrorFlag)
    {
        ErrorFlag = Hssl_lInitCallVerify(id, HSSL_SID_INIT_CH);
        /*If Error Flag is not set*/
        if (HSSL_ERR_FOUND != ErrorFlag)
        {
            /* Verify Channel Number parameter */
            ErrorFlag = Hssl_lChannelVerify(id, Channel->Number, HSSL_SID_INIT_CH);
        }
    }

    /*If no error present*/
    if (HSSL_ERR_FOUND != ErrorFlag)
#endif   /*End Of HSSL_DEV_ERROR_DETECT*/
    {
        RetVal = E_OK;

        if (AckErr != 0U)
        {
            /* Enable Not Ack Error interrupt */
            HSSL_Reg[id]->MFLAGSEN.B.NACKEN = (1U << Channel->Number);
        }
        if (TransID != 0U)
        {
            /* Enable Transaction Tag Error interrupt */
            HSSL_Reg[id]->MFLAGSEN.B.TTEEN = (1U << Channel->Number);
        }
        if (TimeoutErr != 0U)
        {
            /* Enable Timeout Error interrupt */
            HSSL_Reg[id]->MFLAGSEN.B.TIMEOUTEN = (1U << Channel->Number);
        }
    }/* if (HSSL_ERR_FOUND != ErrorFlag) */
    return (RetVal);
}
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_Write(const Hssl_InstanceID id,      **
**                    const Hssl_DataTemplateType *WriteData,                 **
**                    const uint16 DataSize,                                  **
**                    const Hssl_ChannelType *const Channel,                  **
**                    const uint16 InjectedError)                                   **
**                                                                            **
** Description     : Performs a direct write transfer.                        **
**                                                                            **
** Service ID      : 0x3E                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id - Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   WriteData :: Pointer to Hssl_DataTemplateType structure  **
**                   which includes write Address and Data to be written.     **
**                   DataSize:: Size of data to be written.                   **
**                   Channel:: HSSL Channel to used.                          **
**                   InjectedError: injected error (if required)              **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
Std_ReturnType Hssl_Write(const Hssl_InstanceID id,\
                          const Hssl_DataTemplateType *WriteData,\
                          const uint16 DataSize, 
                          const Hssl_ChannelType *const Channel,\
                          const uint16 InjectedError)
{
    Std_ReturnType RetVal;

    /* Parameter check for the API if DET is STD_ON*/
#if ( HSSL_DEV_ERROR_DETECT == STD_ON )
    uint8 ErrorFlag;

    RetVal = E_NOT_OK;

    ErrorFlag = Hssl_lInstanceIDVerify(id, HSSL_SID_WRITE);
    if (HSSL_ERR_FOUND != ErrorFlag)
    {
        /* Verify Channel Number parameter */
        ErrorFlag = Hssl_lChannelVerify(id, Channel->Number, HSSL_SID_WRITE);

        if (HSSL_ERR_FOUND != ErrorFlag)
        {
            /* verify the data size */
            ErrorFlag = Hssl_ldataSizeVerify(id, DataSize, HSSL_SID_WRITE);

            if (HSSL_ERR_FOUND != ErrorFlag)
            {
                /* Verify the mode to be run */
                ErrorFlag = Hssl_lRunModeVerify(id, HSSL_SID_WRITE);

                if (HSSL_ERR_FOUND != ErrorFlag)
                {
                    /* verify the data pointer */
                    if((NULL_PTR == WriteData->Data) ||
                                           (NULL_PTR == WriteData->Address))
                    {
                        Det_ReportError(HSSL_MODULE_ID,HSSL_MODULE_INSTANCE,\
                                        HSSL_SID_WRITE,HSSL_E_INV_POINTER);
                        ErrorFlag = HSSL_ERR_FOUND ;
                    }
                }
            }
        }
    }
    /*If no error present*/
    if (HSSL_ERR_FOUND != ErrorFlag)
#endif
    {
        RetVal = Hssl_lSingleFrameWrite(id,WriteData,DataSize,\
                                        Channel,InjectedError,NULL_PTR);
    }
    return(RetVal);
}
#if (HSSL_OPERATING_MODE == HSSL_POLLING_MODE)
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_WriteAck(                            **
**                                  const Hssl_InstanceID id,                 **
**                                  const Hssl_ChannelType *const Channel)    **
**                                                                            **
** Description     : Write acknowledge function, should be called when a      **
**                    write acknowledge is received by the module, or a       **
**                    timeout occurs during a write command.                  **
**                                                                            **
** Service ID      : 0x3F                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id - Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   Channel:: HSSL Channel to use within an instance         **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
Std_ReturnType Hssl_WriteAck(const Hssl_InstanceID id,
                                      const Hssl_ChannelType *const Channel)
{
    Std_ReturnType RetVal;

    /* Parameter check for the API if DET is STD_ON*/
#if ( HSSL_DEV_ERROR_DETECT == STD_ON )
    uint8 ErrorFlag;
    RetVal = E_NOT_OK;
    ErrorFlag = Hssl_lInstanceIDVerify(id, HSSL_SID_WRITE_ACK);
    if (HSSL_ERR_FOUND != ErrorFlag)
    {
        /* Verify Channel Number parameter */
        ErrorFlag = Hssl_lChannelVerify(id, Channel->Number, HSSL_SID_WRITE_ACK);
        if (HSSL_ERR_FOUND != ErrorFlag)
        {
            /* Verify the mode to be run */
            ErrorFlag = Hssl_lRunModeVerify(id, HSSL_SID_WRITE_ACK);
        }
    }

    /*If no Error present*/
    if (HSSL_ERR_FOUND != ErrorFlag)
#endif /* #if ( HSSL_DEV_ERROR_DETECT == STD_ON ) */
    {
        RetVal = Hssl_lWriteAck(id, Channel) ;
    }  /* if (HSSL_ERR_FOUND != ErrorFlag) */
    return (RetVal);
}
#endif
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_Read(                                **
**                    const Hssl_InstanceID id,                               **
**                    const Hssl_DataTemplateType *DataAddress,               **
**                    const uint16 DataSize,                                  **
**                    const Hssl_ChannelType *const Channel,                  **
**                    const uint16 InjectedError)                             **
**                                                                            **
** Description     : Performs a direct Read transfer.                         **
**                                                                            **
** Service ID      : 0x40                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id - Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   DataAddress :Pointer to Hssl_DataTemplateType structure  **
**                       which includes read Address                          **
**                   DataSize:: Size of data to be read.                      **
**                   Channel:: HSSL Channel to use.                           **
**                   InjectedError: injected error (if required)              **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
Std_ReturnType Hssl_Read(const Hssl_InstanceID id,\
                         const Hssl_DataTemplateType *DataAddress,\
                         const uint16 DataSize, 
                         const Hssl_ChannelType *const Channel,\
                         const uint16 InjectedError)
{
    /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
    this MISRA rule. Union usage is required to access SFR data type and
    implement efficiently for clearing of pending service requrest in Interrupt
    control register */
    volatile Ifx_HSSL_I_ICON *CtrlRegPtr;
    /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
    this MISRA rule. Union usage is required to access SFR data type and
    implement efficiently for clearing of pending service requrest in Interrupt
    control register */
    volatile Ifx_HSSL_I_IRWA *AddRegPtr;
    uint32 *HsslReadDataBuffer = NULL_PTR;
    Std_ReturnType RetVal = E_NOT_OK;
    Hssl_ChStateType *ChStateTypePtr= NULL_PTR;

    /* Parameter check for the API if DET is STD_ON*/
#if ( HSSL_DEV_ERROR_DETECT == STD_ON )
    uint8 ErrorFlag;
    ErrorFlag = Hssl_lInstanceIDVerify(id, HSSL_SID_READ);
    if (HSSL_ERR_FOUND != ErrorFlag)
    {

        /* Verify Channel Number parameter */
        ErrorFlag = Hssl_lChannelVerify(id, Channel->Number, HSSL_SID_READ);

        /* verify the data size */
        if (HSSL_ERR_FOUND != ErrorFlag)
        {
            ErrorFlag = Hssl_ldataSizeVerify(id, DataSize, HSSL_SID_READ);

            /* Verify the mode to be run */
            if (HSSL_ERR_FOUND != ErrorFlag)
            {
                ErrorFlag = Hssl_lRunModeVerify(id, HSSL_SID_READ);
                /* verify the data pointer */
                if (HSSL_ERR_FOUND != ErrorFlag)
                {
                    if (NULL_PTR == DataAddress)
                    {
                        Det_ReportError(HSSL_MODULE_ID,HSSL_MODULE_INSTANCE,\
                                        HSSL_SID_READ,HSSL_E_INV_POINTER);
                        ErrorFlag = HSSL_ERR_FOUND;
                    }
                }
            }
        }
    }
    /*If no Error present*/
    if (HSSL_ERR_FOUND != ErrorFlag)
#endif
    {

#if (HSSL0_CONFIGURRED == STD_ON)
        if (id == HSSL0)
        {
            /* MISRA2012_RULE_1_3_JUSTIFICATION: Passing local to fetch
             * data - Hssl0ReadDataBuffer - agreed violation */
            /* MISRA2012_RULE_11_3_JUSTIFICATION: Hssl0ReadDataBuffer
             base address access */
            HsslReadDataBuffer = (uint32*)&Hssl0ReadDataBuffer[Channel->Number];
            ChStateTypePtr = Hssl0ChState;
        }
#endif
#if (HSSL1_CONFIGURRED == STD_ON)
        if (id == HSSL1)
        {
            /* MISRA2012_RULE_1_3_JUSTIFICATION: Passing local to fetch
             * data - Hssl1ReadDataBuffer - agreed violation */
            /* MISRA2012_RULE_11_3_JUSTIFICATION: Hssl1ReadDataBuffer
             base address access */
            HsslReadDataBuffer = (uint32*)&Hssl1ReadDataBuffer[Channel->Number];
            ChStateTypePtr = Hssl1ChState;
        }
#endif
        CtrlRegPtr = (&HSSL_Reg[id]->I[Channel->Number].ICON);
        AddRegPtr = (&HSSL_Reg[id]->I[Channel->Number].IRWA);

            /* Enter SchM section to prevent concurrent access */
            SchM_Enter_Hssl_ChannelStatusLock();
            if (ChStateTypePtr[Channel->Number] != HSSL_COMMAND_IN_PROGRESS)
            {
                /* set the channel state to "HSSL_COMMAND_IN_PROGRESS" */
                ChStateTypePtr[Channel->Number] = HSSL_COMMAND_IN_PROGRESS;
                RetVal = E_OK;
            }
            /* Enter SchM */
            SchM_Exit_Hssl_ChannelStatusLock();

            if (RetVal == E_OK)
            {
                /*Read ICONx.BSY bit to check if Channel is Busy or Available*/
                if(CtrlRegPtr->B.BSY == 0U)
                {
                    /* If Error Injection is needed, set it in CRC register */
                    if(InjectedError != 0U)
                    {
                     HSSL_RUNTIME_WRITEENDINITPROTREG(
                     &(HSSL_Reg[id]->CRC),
                     ((uint32)InjectedError | (1UL<<HSSL_CRC_EN_SHIFT)));
                    }

       /* MISRA2012_RULE_11_6_JUSTIFICATION:The address of the buffer pointer is
       stores in a local variable to be comapred against 0-NULL.
       There are no other operation performed, hence this convesion
       does not cause any issue */
       /* MISRA2012_RULE_11_4_JUSTIFICATION:The address of the buffer pointer is
       stores in a local variable to be comapred against 0-NULL.
       There are no other operation performed, hence this convesion
       does not cause any issue */
                        *HsslReadDataBuffer = (uint32)DataAddress->Data;
                        /* Write data size in ICONx */
                        CtrlRegPtr->B.DATLEN = (uint8)DataSize;
                        /* Write Time Out Value in ICONx */
                        CtrlRegPtr->B.TOREL  = (uint8)Channel->Timeout;
                        /* Write ICONx.RWT with 0x10 Write Frame */
                        CtrlRegPtr->B.RWT    = HSSL_READ_FRAME;
                        /* Write IRWAx register with Address */
                        AddRegPtr->U = *DataAddress->Address;

                }
                else
                {
                    RetVal = E_NOT_OK;
                }
                ChStateTypePtr[Channel->Number] = HSSL_COMMAND_COMPLETED;
            }/* Channel is Busy */
    } /* if (HSSL_ERR_FOUND != ErrorFlag)   */
    return(RetVal);
}
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_Id(                                  **
**                                      const Hssl_InstanceID id,             **
**                                      uint32 *const StoreAddress,           **
**                                const Hssl_ChannelType *const Channel)      **
**                                                                            **
** Description     : Sends ID Request Frame to target. Stores received        **
**                   command in the address passed.                           **
**                                                                            **
** Service ID      : 0x42                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   StoreAddress : Pointer to the Address location/variable  **
**                    to store the ID received from target                    **
**                   Channel: Hssl channel number                             **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
Std_ReturnType Hssl_Id(const Hssl_InstanceID id, uint32 *const StoreAddress,
                       const Hssl_ChannelType *const Channel)
{
    Std_ReturnType RetVal= E_NOT_OK;
    /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
    this MISRA rule. Union usage is required to access SFR data type and
    implement efficiently for clearing of pending service requrest in Interrupt
    control register */
    volatile Ifx_HSSL_I_ICON *CtrlRegPtr;
#if (HSSL_OPERATING_MODE == HSSL_POLLING_MODE)
    /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
    this MISRA rule. Union usage is required to access SFR data type and
    implement efficiently for clearing of pending service requrest in Interrupt
    control register */
    volatile const Ifx_HSSL_I_IRD *ReadDataRegPtr;
    volatile uint32 Qflags;
    uint32 ExpectMask;
#else
    uint32 *HsslReadDataBuffer = NULL_PTR;
#endif
    Hssl_ChStateType *ChStateTypePtr= NULL_PTR;

    /* Parameter check for the API if DET is STD_ON*/
#if ( HSSL_DEV_ERROR_DETECT == STD_ON )
    uint8 ErrorFlag;
    ErrorFlag = Hssl_lInstanceIDVerify(id, HSSL_SID_READ_ID);
    if (HSSL_ERR_FOUND != ErrorFlag)
    {
    /* check if Init is called or not */
    ErrorFlag = Hssl_lChannelVerify(id, Channel->Number, HSSL_SID_READ_ID);

    /* verify the driver Mode */
    if (HSSL_ERR_FOUND != ErrorFlag)
    {
        ErrorFlag = Hssl_lRunModeVerify(id, HSSL_SID_READ_ID);

        /* verify the data pointer */
        if (HSSL_ERR_FOUND != ErrorFlag)
        {
            if (NULL_PTR == StoreAddress)
            {
                Det_ReportError(HSSL_MODULE_ID,HSSL_MODULE_INSTANCE,\
                                HSSL_SID_READ_ID,HSSL_E_INV_POINTER);
                ErrorFlag = HSSL_ERR_FOUND ;
            }
        }
    }
    }
    /*If no Error present*/
    if (HSSL_ERR_FOUND != ErrorFlag)
#endif
    {
#if (HSSL0_CONFIGURRED == STD_ON)
        if (id == HSSL0)
        {
#if (HSSL_OPERATING_MODE != HSSL_POLLING_MODE)
            /* MISRA2012_RULE_1_3_JUSTIFICATION: Passing local to fetch
             * data - Hssl0ReadDataBuffer - agreed violation */
            /* MISRA2012_RULE_11_3_JUSTIFICATION: Hssl0ReadDataBuffer
             base address access */
            HsslReadDataBuffer =(uint32 *)&Hssl0ReadDataBuffer[Channel->Number];
#endif
            ChStateTypePtr = Hssl0ChState;
        }
#endif
#if (HSSL1_CONFIGURRED == STD_ON)
        if (id == HSSL1)
        {
#if (HSSL_OPERATING_MODE != HSSL_POLLING_MODE)
            /* MISRA2012_RULE_1_3_JUSTIFICATION: Passing local to fetch
             * data - Hssl1ReadDataBuffer - agreed violation */
            /* MISRA2012_RULE_11_3_JUSTIFICATION: Hssl1ReadDataBuffer
             base address access */
            HsslReadDataBuffer =(uint32 *)&Hssl1ReadDataBuffer[Channel->Number];
#endif
            ChStateTypePtr = Hssl1ChState;
        }
#endif
        /* Read ID is sent on Channel 0 always */
        CtrlRegPtr = (&HSSL_Reg[id]->I[Channel->Number].ICON);
#if (HSSL_OPERATING_MODE == HSSL_POLLING_MODE)
        ReadDataRegPtr = (&HSSL_Reg[id]->I[Channel->Number].IRD);
#endif
        /* Enter SchM section to prevent concurrent access */
            SchM_Enter_Hssl_ChannelStatusLock();
            if ( ChStateTypePtr[Channel->Number] != HSSL_COMMAND_IN_PROGRESS)
            {
                /* set the channel state to "HSSL_COMMAND_IN_PROGRESS" */
                ChStateTypePtr[Channel->Number]   = HSSL_COMMAND_IN_PROGRESS;
                RetVal = E_OK;
            }
            /* Enter SchM */
            SchM_Exit_Hssl_ChannelStatusLock();

            if (RetVal == E_OK)
            {
             /*  Read ICONx.BSY bit to check if Channel is Busy or Available */
                if (CtrlRegPtr->B.BSY == 0U)
                {
                    /* LOad Write Time Out Reload Value in ICONx */
                    CtrlRegPtr->B.TOREL = HSSL_TIMEOUT;

                    /* Request a Read ID Frame */
                    CtrlRegPtr->B.IDQ = 1U;
#if (HSSL_OPERATING_MODE == HSSL_POLLING_MODE)
                /* Check Ix and Ex signals to check if any request is pending */
                  do
                  {
                    Qflags = HSSL_Reg[id]->QFLAGS.U;
                  }while ((Qflags & (((uint32)HSSL_READ_PENDING << ((uint32)HSSL_NUM_16 + \
                           (Channel->Number*(uint32)HSSL_CHANNEL_CFG)))
                          |((uint32)1U << Channel->Number))) != 0U);

                    /* check RetVal and return */
                    /* NACK */
                    ExpectMask = ((uint32)1U << (uint32)Channel->Number);
                    /* TTE */
                    ExpectMask = ExpectMask |
                     ((uint32)1U << (Channel->Number + (uint32)HSSL_NUM_4));
                    /*TIMEOUT*/
                    ExpectMask = ExpectMask |
                     ((uint32)1U << (Channel->Number + (uint32)HSSL_NUM_8));
                    ExpectMask = ExpectMask |
                     ((uint32)1U << (Channel->Number + (uint32)HSSL_NUM_12));
                    /* SRIE,PIE1,PIE2,CRCE */
                    ExpectMask = ExpectMask | ((uint32)HSSL_FLAG_CFG << (uint32)HSSL_NUM_22);
                    if ((HSSL_Reg[id]->MFLAGS.U & ExpectMask) != 0U)
                    {
                        RetVal = E_NOT_OK;
                    }
                    else
                    {
                        RetVal = E_OK;
                        *StoreAddress = ReadDataRegPtr->U;
                    }
#else
                    if(HsslReadDataBuffer != NULL_PTR)
                    {
       /* MISRA2012_RULE_11_6_JUSTIFICATION:The address of the buffer pointer is
       stores in a local variable to be comapred against 0-NULL.
       There are no other operation performed, hence this convesion
       does not cause any issue */
       /* MISRA2012_RULE_11_4_JUSTIFICATION:The address of the buffer pointer is
       stores in a local variable to be comapred against 0-NULL.
       There are no other operation performed, hence this convesion
       does not cause any issue */
                        *HsslReadDataBuffer = (uint32)StoreAddress;
                    }
#endif
                }
                else
                {
                    RetVal= E_NOT_OK;
                }
                /* set the channel state to "HSSL_COMMAND_IN_PROGRESS" */
                ChStateTypePtr[Channel->Number] = HSSL_COMMAND_COMPLETED;
            }  /* Channel is Busy */
        /* if (HSSL_ERR_FOUND != ErrorFlag)    */
    }
    return(RetVal);
}
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_Trigger(const Hssl_InstanceID id,    **
**                                  const Hssl_ChannelType *const Channel)    **
**                                                                            **
** Description     : Sends ID Request Frame to target. Stores received        **
**                   command in the address passed.                           **
**                                                                            **
** Service ID      : 0x4D                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   Channel: Hssl Channel number                             **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
Std_ReturnType Hssl_Trigger(const Hssl_InstanceID id,
                                  const Hssl_ChannelType *const Channel)
{
    Std_ReturnType RetVal= E_NOT_OK;
    /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
    this MISRA rule. Union usage is required to access SFR data type and
    implement efficiently for clearing of pending service requrest in Interrupt
    control register */
    volatile Ifx_HSSL_I_ICON *CtrlRegPtr;
#if (HSSL_OPERATING_MODE == HSSL_POLLING_MODE)
    volatile uint32 Qflags;
    uint32 ExpectMask;
#endif
    Hssl_ChStateType *ChStateTypePtr= NULL_PTR;
    /* Parameter check for the API if DET is STD_ON*/
#if ( HSSL_DEV_ERROR_DETECT == STD_ON )
    uint8 ErrorFlag;
    ErrorFlag = Hssl_lInstanceIDVerify(id, HSSL_SID_TRIGGER);
    if (HSSL_ERR_FOUND != ErrorFlag)
    {
    /* check if Init is called or not */
    ErrorFlag = Hssl_lChannelVerify(id, Channel->Number, HSSL_SID_TRIGGER);

    /* verify the driver Mode */
    if (HSSL_ERR_FOUND != ErrorFlag)
    {
        ErrorFlag = Hssl_lRunModeVerify(id, HSSL_SID_TRIGGER);
    }
    }
    /*If no Error present*/
    if (HSSL_ERR_FOUND != ErrorFlag)
#endif
    {

#if (HSSL0_CONFIGURRED == STD_ON)
        if (id == HSSL0)
        {
            ChStateTypePtr = Hssl0ChState;
        }
#endif
#if (HSSL1_CONFIGURRED == STD_ON)
        if (id == HSSL1)
        {
            ChStateTypePtr = Hssl1ChState;
        }
#endif
        /* Read ID is sent on Channel 0 always */
        CtrlRegPtr = (&HSSL_Reg[id]->I[Channel->Number].ICON);
        /* Enter SchM section to prevent concurrent access */

            SchM_Enter_Hssl_ChannelStatusLock();
            if ( ChStateTypePtr[Channel->Number] != HSSL_COMMAND_IN_PROGRESS)
            {
                /* set the channel state to "HSSL_COMMAND_IN_PROGRESS" */
                ChStateTypePtr[Channel->Number]   = HSSL_COMMAND_IN_PROGRESS;
                RetVal = E_OK;
            }
            /* Enter SchM */
            SchM_Exit_Hssl_ChannelStatusLock();

            if (RetVal == E_OK)
            {
              /*  Read ICONx.BSY bit to check if Channel is Busy or Available */
                if (CtrlRegPtr->B.BSY == 0U)
                {
                    /* LOad Write Time Out Reload Value in ICONx */
                    CtrlRegPtr->B.TOREL = HSSL_TIMEOUT;

                    /* Request a Read ID Frame */
                    CtrlRegPtr->B.TQ = 1U;
#if (HSSL_OPERATING_MODE == HSSL_POLLING_MODE)
                /* Check Ix and Ex signals to check if any request is pending */
                  do
                  {
                    Qflags = HSSL_Reg[id]->QFLAGS.U;
                  }while ((Qflags & (((uint32)HSSL_TRIGGER_PENDING << ((uint32)HSSL_NUM_16 + \
                           (Channel->Number*(uint32)HSSL_CHANNEL_CFG)))
                          |((uint32)1U << Channel->Number))) != 0U);

                    /* check RetVal and return */
                    /* NACK */
                    ExpectMask = ((uint32)1U << (uint32)Channel->Number);
                    /* TTE */
                    ExpectMask = ExpectMask |
                     ((uint32)1U << (Channel->Number + (uint32)HSSL_NUM_4));
                    /*TIMEOUT*/
                    ExpectMask = ExpectMask |
                     ((uint32)1U << (Channel->Number + (uint32)HSSL_NUM_8));
                    ExpectMask = ExpectMask |
                     ((uint32)1U << (Channel->Number + (uint32)HSSL_NUM_12));
                    /* SRIE,PIE1,PIE2,CRCE */
                    ExpectMask = ExpectMask | ((uint32)HSSL_FLAG_CFG << (uint32)HSSL_NUM_22);
                    if ((HSSL_Reg[id]->MFLAGS.U & ExpectMask) != 0U)
                    {
                        RetVal = E_NOT_OK;
                    }
                    else
                    {
                        RetVal = E_OK;
                    }
#endif
                }
                else
                {
                    RetVal= E_NOT_OK;
                }
                /* set the channel state to "HSSL_COMMAND_IN_PROGRESS" */
                ChStateTypePtr[Channel->Number] = HSSL_COMMAND_COMPLETED;
            }  /* Channel is Busy */

    }
    return(RetVal);
}

#if (HSSL_OPERATING_MODE == HSSL_POLLING_MODE)
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_ReadRply (                           **
**                          const Hssl_InstanceID id,                         **
**                          const Hssl_ChannelType *const Channel)            **
**                                                                            **
** Description     : Reply function which is called either when a successful  **
**                   read reply is received, or when a timeout is reached.    **
**                   If called due to a timeout then only the Channel and     **
**                   Error parameters will be written.                        **
**                                                                            **
** Service ID      : 0x41                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id - Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   Channel:: HSSL Channel to use.                           **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
Std_ReturnType Hssl_ReadRply (const Hssl_InstanceID id,
                                       const Hssl_ChannelType *const Channel)
{
    Std_ReturnType RetVal;
    volatile uint32 Qflags;
    uint32 ExpectMask ;
    const uint32 *HsslReadDataBuffer= NULL_PTR ;
    uint32 *BufferAddress = NULL_PTR;
    /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
    this MISRA rule. Union usage is required to access SFR data type and
    implement efficiently for clearing of pending service requrest in Interrupt
    control register */
    volatile const Ifx_HSSL_I_IRD *ReadDataRegPtr;
#if ( HSSL_DEV_ERROR_DETECT == STD_ON )
    uint8 ErrorFlag;
    RetVal = E_NOT_OK;
    ErrorFlag = Hssl_lInstanceIDVerify(id, HSSL_SID_READ_REPLY);
    if (HSSL_ERR_FOUND != ErrorFlag)
    {

        /* Verify Channel Number parameter */
        ErrorFlag = Hssl_lChannelVerify(id,Channel->Number,HSSL_SID_READ_REPLY);

        /* verify the driver Mode */
        if (HSSL_ERR_FOUND != ErrorFlag)
        {
            ErrorFlag = Hssl_lRunModeVerify(id,HSSL_SID_READ_REPLY);
        }
    }
    /*If no Error present*/
    if (HSSL_ERR_FOUND != ErrorFlag)
#endif
    {
        RetVal = E_OK;

#if (HSSL0_CONFIGURRED == STD_ON)
        if (id == HSSL0)
        {
            /* MISRA2012_RULE_1_3_JUSTIFICATION: Passing local to fetch
             * data - Hssl0ReadDataBuffer - agreed violation */
            /* MISRA2012_RULE_11_3_JUSTIFICATION: Hssl0ReadDataBuffer
             base address access */
            HsslReadDataBuffer =(uint32*)&Hssl0ReadDataBuffer[Channel->Number];
        }
#endif
#if (HSSL1_CONFIGURRED == STD_ON)
        if (id == HSSL1)
        {
            /* MISRA2012_RULE_1_3_JUSTIFICATION: Passing local to fetch
             * data - Hssl1ReadDataBuffer - agreed violation */
            /* MISRA2012_RULE_11_3_JUSTIFICATION: Hssl1ReadDataBuffer
             base address access */
            HsslReadDataBuffer =(uint32*)&Hssl1ReadDataBuffer[Channel->Number];
        }
#endif
        ReadDataRegPtr = (&HSSL_Reg[id]->I[Channel->Number].IRD);
        Qflags = HSSL_Reg[id]->QFLAGS.U;
        /* Check Ix and Ex signals to check if any request is pending */
       do
       {
           Qflags = HSSL_Reg[id]->QFLAGS.U;
       }while ((Qflags & (((uint32)HSSL_READ_PENDING << ((uint32)HSSL_NUM_16 + \
                           (Channel->Number*(uint32)HSSL_CHANNEL_CFG)))
                          |((uint32)1U << Channel->Number))) != 0U);

        /* check RetVal and return */
        /* NACK */
        ExpectMask = ((uint32)1U << (uint32)Channel->Number);
        /* TTE */
        ExpectMask = ExpectMask |
                     ((uint32)1U << (Channel->Number + (uint32)HSSL_NUM_4));
        /*TIMEOUT*/
        ExpectMask = ExpectMask |
                     ((uint32)1U << (Channel->Number + (uint32)HSSL_NUM_8));
        ExpectMask = ExpectMask |
                     ((uint32)1U << (Channel->Number + (uint32)HSSL_NUM_12));
        /* SRIE,PIE1,PIE2,CRCE */
       ExpectMask = ExpectMask | ((uint32)HSSL_FLAG_CFG << (uint32)HSSL_NUM_22);
        if ((HSSL_Reg[id]->MFLAGS.U & ExpectMask) != 0U)
        {
            RetVal = E_NOT_OK;
        }
        else
        {
            if(HsslReadDataBuffer != NULL_PTR)
            {
       /* MISRA2012_RULE_11_6_JUSTIFICATION:The address of the buffer pointer is
       stores in a local variable to be comapred against 0-NULL.
       There are no other operation performed, hence this convesion
       does not cause any issue */
       /* MISRA2012_RULE_11_4_JUSTIFICATION:The address of the buffer pointer is
       stores in a local variable to be comapred against 0-NULL.
       There are no other operation performed, hence this convesion
       does not cause any issue */
                BufferAddress = (uint32*)*HsslReadDataBuffer;
                *BufferAddress = ReadDataRegPtr->U;
            }
        }
    }/* if (HSSL_ERR_FOUND != ErrorFlag) */
    return RetVal;
}
#endif
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_StartStream                          **
**                    ( const Hssl_InstanceID id,                             **
**                      const uint32 *const SourceAddressStart,               **
**                      uint32 *const DestinationAddressStart,                **
**                      const uint16 DataSize,                                **
**                      const uint16 InjectedError)                           **
**                                                                            **
** Description     : Performs streaming write transfer.                       **
**                                                                            **
** Service ID      : 0x43                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   SourceAddressStart : Pointer to address containing start **
**                      of data to be streamed.                               **
**                   DestinationAddressStart : Pointer to address containing  **
**                      destination of data to be streamed.                   **
**                   DataSize:: Size of data to be written.                   **
**                   InjectedError: injected Error (if required)              **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
Std_ReturnType Hssl_StartStream (const Hssl_InstanceID id,\
                                 const uint32 *const SourceAddressStart,\
                                 const uint32 *const DestinationAddressStart,\
                                 const uint16 DataSize,
                                 const uint16 InjectedError)
{
    Std_ReturnType RetVal = E_NOT_OK;
    Hssl_ChStateType *ChStateTypePtr= NULL_PTR;

    /* Parameter check for the API if DET is STD_ON*/
#if ( HSSL_DEV_ERROR_DETECT == STD_ON )
    uint8 ErrorFlag;

ErrorFlag = Hssl_lInstanceIDVerify(id, HSSL_SID_STREAM);
    if (HSSL_ERR_FOUND != ErrorFlag)
    {

        /* Verify the mode to be run */
        ErrorFlag = Hssl_lRunModeVerify(id, HSSL_SID_STREAM);
        /* verify the data pointer */
        if (HSSL_ERR_FOUND != ErrorFlag)
        {
            if ((NULL_PTR == SourceAddressStart) ||
            (NULL_PTR == DestinationAddressStart))
            {
                Det_ReportError(HSSL_MODULE_ID,HSSL_MODULE_INSTANCE,\
                                HSSL_SID_STREAM,HSSL_E_INV_POINTER);
                ErrorFlag = HSSL_ERR_FOUND ;
            }
            if (DataSize == 0U)
            {
                Det_ReportError(HSSL_MODULE_ID,HSSL_MODULE_INSTANCE,\
                                HSSL_SID_STREAM,HSSL_E_INV_PARAM);
                ErrorFlag = HSSL_ERR_FOUND ;
            }
        }
    }
    /*If no Error present*/
    if (HSSL_ERR_FOUND != ErrorFlag)
#endif
    {
#if (HSSL0_CONFIGURRED == STD_ON)
        if (id == HSSL0)
        {
            ChStateTypePtr = Hssl0ChState;
        }
#endif
#if (HSSL1_CONFIGURRED == STD_ON)
        if (id == HSSL1)
        {
            ChStateTypePtr = Hssl1ChState;
        }
#endif
        /* Enter SchM section to prevent concurrent access */

            SchM_Enter_Hssl_ChannelStatusLock();
            if ( ChStateTypePtr[2] != HSSL_COMMAND_IN_PROGRESS)
            {
                /* set the channel state to "HSSL_COMMAND_IN_PROGRESS" */
                ChStateTypePtr[2]   = HSSL_COMMAND_IN_PROGRESS;
                RetVal = E_OK;
            }
            else
            {
                RetVal = E_NOT_OK;
            }
            /* Exit SchM */
            SchM_Exit_Hssl_ChannelStatusLock();
            if (RetVal==E_OK)
            {
                RetVal = Hssl_lSetTargetAddress(id,DestinationAddressStart,
                               DataSize);
                if (RetVal == E_OK)
                {
                    /*  Read ICONx.BSY bit to check if Channel
                    is Busy or Available */
                    if (HSSL_Reg[id]->I[2U].ICON.B.BSY == 0U)
                    {
                        if (InjectedError != 0U)
                        {
                          HSSL_RUNTIME_WRITEENDINITPROTREG(
                          &(HSSL_Reg[id]->CRC),
                          ((uint32)InjectedError | (1UL<<HSSL_CRC_EN_SHIFT)));
                        }
                        /* Initiator Address */

      /* MISRA2012_RULE_11_6_JUSTIFICATION:The address of the buffer pointer is
         stores in a local variable to be comapred against 0-NULL.
              There are no other operation performed, hence this convesion
                        does not cause any issue */
      /* MISRA2012_RULE_11_4_JUSTIFICATION:The address of the buffer pointer is
        stores in a local variable to be comapred against 0-NULL.
        There are no other operation performed, hence this convesion
        does not cause any issue */
                        HSSL_Reg[id]->IS.SA[0].U = (uint32)SourceAddressStart;
       /* MISRA2012_RULE_11_6_JUSTIFICATION:The address of the buffer pointer is
             stores in a local variable to be comapred against 0-NULL.
             There are no other operation performed, hence this convesion
             does not cause any issue */
       /* MISRA2012_RULE_11_4_JUSTIFICATION:The address of the buffer pointer is
         stores in a local variable to be comapred against 0-NULL.
         There are no other operation performed, hence this convesion
         does not cause any issue */
                        HSSL_Reg[id]->IS.SA[1].U = (uint32)SourceAddressStart;

                        /* Initiator reload counter (burst numbers,
                        one burst is 8 words)*/
                        HSSL_Reg[id]->IS.FC.B.RELCOUNT  = DataSize;
                        HSSL_Reg[id]->I[2U].ICON.B.TOREL = (HSSL_TIMEOUT);

                        /* Start streaming */
                        HSSL_Reg[id]->MFLAGSSET.B.TSES = 1U;
                        HSSL_Reg[id]->MFLAGSSET.B.ISBS = 1U;
                        ChStateTypePtr[2]  = HSSL_COMMAND_COMPLETED ;
                    }
                    else
                    {
                        RetVal = E_NOT_OK;
                    }
                }
            }

    }
    return(RetVal);
}
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_StopStream(const Hssl_InstanceID id) **
**                                                                            **
** Description     : Stops the ongoing data streaming.                        **
**                                                                            **
** Service ID      : 0x44                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
Std_ReturnType Hssl_StopStream(const Hssl_InstanceID id)
{
    Std_ReturnType RetVal = E_NOT_OK;

#if ( HSSL_DEV_ERROR_DETECT == STD_ON )
    uint8 ErrorFlag = HSSL_ERR_NOT_FOUND;

    /* Check for the proper HSSL instance */
    ErrorFlag = Hssl_lInstanceIDVerify(id, HSSL_SID_STREAM_STOP);
    if (HSSL_ERR_NOT_FOUND == ErrorFlag)
    {
        /* check if Init is called or not */
       ErrorFlag = Hssl_lRunModeVerify(id, HSSL_SID_STREAM_STOP);
    }
    if (HSSL_ERR_NOT_FOUND == ErrorFlag)
#endif
    {
        RetVal = E_OK;
        HSSL_Reg[id]->MFLAGSCL.B.TSEC = 1U;
        HSSL_Reg[id]->MFLAGSCL.B.ISBC = 1U;
    }
    return (RetVal);
}
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : static uint8 Hssl_lcheckDMAReadchannelUsage              **
**                    ( const Hssl_InstanceID id)                             **
**                                                                            **
** Description     : Checks the DMA Read channel usage status                 **
**                                                                            **
** Service ID      :                                                          **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'HSSL_ERR_NOT_FOUND' if successful,              **
**                          'HSSL_ERR_FOUND' otherwise.                       **
**                                                                            **
*******************************************************************************/
static uint8 Hssl_lcheckDMAReadchannelUsage(const Hssl_InstanceID id)
{
    uint8 ErrorFlag;
    ErrorFlag = HSSL_ERR_FOUND;

    /* Enter SCHM */
    SchM_Enter_Hssl_DmaOperatedCmdQueue();
    /* Verify whether Init had been called */
    if (Hssl_DMAReadOperationState[id] ==  HSSL_DMA_OPERATION_COMPLETED)
    {
        Hssl_DMAReadOperationState[id] = HSSL_DMA_OPERATION_IN_PROGRESS;
        ErrorFlag = HSSL_ERR_NOT_FOUND;
    }
    /*Exit SCHM */
    SchM_Exit_Hssl_DmaOperatedCmdQueue();
    return (ErrorFlag);
}
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : static uint8 Hssl_lcheckDMAWritechannelUsage             **
**                    ( const Hssl_InstanceID id)                             **
**                                                                            **
** Description     : Checks the DMA channel usage status                      **
**                                                                            **
** Service ID      :                                                          **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'HSSL_ERR_NOT_FOUND' if successful,              **
**                          'HSSL_ERR_FOUND' otherwise.                       **
**                                                                            **
*******************************************************************************/
static uint8 Hssl_lcheckDMAWritechannelUsage(const Hssl_InstanceID id)
{
    uint8 ErrorFlag;
    ErrorFlag = HSSL_ERR_FOUND;

    /* Enter SCHM */
    SchM_Enter_Hssl_DmaOperatedCmdQueue();
    /* Verify whether Init had been called */
    if (Hssl_DMAWriteOperationState[id] ==  HSSL_DMA_OPERATION_COMPLETED)
    {
        Hssl_DMAWriteOperationState[id] = HSSL_DMA_OPERATION_IN_PROGRESS;
        ErrorFlag = HSSL_ERR_NOT_FOUND;
    }
    /*Exit SCHM */
    SchM_Exit_Hssl_DmaOperatedCmdQueue();
    return (ErrorFlag);
}
/*
 CYCLOMATIC_Hssl_MultiWrite_JUSTIFICATION: Function is used to perform multiple
 write transfer using DMA channels, multiple conditions are used to configure
 multi write operations hence this fuction cannot split further.
*/
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_MultiWrite                           **
**                    ( const Hssl_InstanceID id,                             **
**                      const Hssl_DataTemplateType *WriteArray,              **
**                      const uint16 DataSize, const uint16 NumCmd,           **
**                const Hssl_ChannelType *const Channel, uint16 InjectedError)**
**                                                                            **
** Description     : Performs multiple write transfers.                       **
**                                                                            **
** Service ID      : 0x45                                                     **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   WriteArray : Hssl_DataTemplateType structure which       **
**                     includes array containing write Address and Data to be **
**                     written for each array record.                         **
**                   DataSize: Size of data to be written.                    **
**                   NumCmd : Number of address command pairs                 **
**                   Channel: HSSL Channel to use.                            **
**                   InjectedError: injected Error (if required)              **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
Std_ReturnType Hssl_MultiWrite(const Hssl_InstanceID id,\
                               const Hssl_DataTemplateType *WriteArray,\
                               const uint16 DataSize,const uint16 NumCmd,\
                               const Hssl_ChannelType *const Channel,
                               const uint16 InjectedError)
{
    Std_ReturnType RetVal = E_NOT_OK;
    Dma_ConfigUpdateType Hssl_DmaTxConfig = {0};
    uint8 DmaChNum;
    /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
    this MISRA rule. Union usage is required to access SFR data type and
    implement efficiently for clearing of pending service requrest in Interrupt
    control register */
    volatile Ifx_HSSL_I_ICON *CtrlRegPtr;
    /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
    this MISRA rule. Union usage is required to access SFR data type and
    implement efficiently for clearing of pending service requrest in Interrupt
    control register */
    volatile Ifx_HSSL_I_IWD *WriteDataRegPtr;
    Hssl_ChStateType *ChStateTypePtr= NULL_PTR;
    uint8 ErrorFlag  = HSSL_ERR_NOT_FOUND;
    /* Parameter check for the API if DET is STD_ON*/
#if ( HSSL_DEV_ERROR_DETECT == STD_ON )
    ErrorFlag = Hssl_lInstanceIDVerify(id, HSSL_SID_WRITE_MULTIPLE);
    if (HSSL_ERR_FOUND != ErrorFlag)
    {

        /* Verify Channel Number parameter */
        ErrorFlag = Hssl_lChannelVerify(id, Channel->Number,\
                                        HSSL_SID_WRITE_MULTIPLE);

        /* verify the data size */
        if (HSSL_ERR_FOUND != ErrorFlag)
        {
          ErrorFlag = Hssl_ldataSizeVerify(id,DataSize,HSSL_SID_WRITE_MULTIPLE);

            /* Verify the mode to be run */
            if (HSSL_ERR_FOUND != ErrorFlag)
            {
                ErrorFlag = Hssl_lRunModeVerify(id, HSSL_SID_WRITE_MULTIPLE);
                /* verify the data pointer */
                if (HSSL_ERR_FOUND != ErrorFlag)
                {

                    ErrorFlag = Hssl_lCheckParam(HSSL_SID_WRITE_MULTIPLE,
                    WriteArray,NULL_PTR,NULL_PTR,NumCmd);

                }
            }
        }
    }
    /*If no Error present*/
    if (HSSL_ERR_FOUND != ErrorFlag)
#endif
    {
        /* Check if any other channel is already using DMA */
        ErrorFlag = Hssl_lcheckDMAWritechannelUsage(id);
        if (HSSL_ERR_FOUND != ErrorFlag)
        {
#if (HSSL0_CONFIGURRED == STD_ON)
        if (id == HSSL0)
        {
            ChStateTypePtr = Hssl0ChState;
        }
#endif
#if (HSSL1_CONFIGURRED == STD_ON)
        if (id == HSSL1)
        {
            ChStateTypePtr = Hssl1ChState;
        }
#endif
        CtrlRegPtr = (&HSSL_Reg[id]->I[Channel->Number].ICON);
        WriteDataRegPtr = (&HSSL_Reg[id]->I[Channel->Number].IWD);

        /* Enter SchM section to prevent concurrent access */
            SchM_Enter_Hssl_ChannelStatusLock();
            if ( ChStateTypePtr[Channel->Number] != HSSL_COMMAND_IN_PROGRESS)
            {
                /* set the channel state to "HSSL_COMMAND_IN_PROGRESS" */
                ChStateTypePtr[Channel->Number]  = HSSL_COMMAND_IN_PROGRESS;
                RetVal = E_OK;
            }
            /* Enter SchM */
            SchM_Exit_Hssl_ChannelStatusLock();

            if (RetVal == E_OK)
            {
             /*  Read ICONx.BSY bit to check if Channel is Busy or Available */
                if(CtrlRegPtr->B.BSY == 0U)
                {
                    /* If injected Error is needed set it in CRC register */
                    if(InjectedError != 0U)
                    {
                     HSSL_RUNTIME_WRITEENDINITPROTREG(
                     &(HSSL_Reg[id]->CRC),
                     ((uint32)InjectedError | (1UL<<HSSL_CRC_EN_SHIFT)));
                    }
                    /* Write data size in ICONx */
                    CtrlRegPtr->B.DATLEN = (uint8)DataSize;
                    /* Write Time Out Value in ICONx */
                    CtrlRegPtr->B.TOREL  = (uint8)Channel->Timeout;
                    /* Write ICONx.RWT with 0x10 Write Frame */
                    CtrlRegPtr->B.RWT    = HSSL_WRITE_FRAME;
                    /* Disable DMA Tx Channel */
#if (HSSL_NUM_INSTANCES_CONFIGURRED == 1U)
                    DmaChNum = HSSL_DMA_MULTI_WRITE_CHANNEL;
#else
                    if (id == HSSL0)
                    {
                        DmaChNum = HSSL0_DMA_MULTI_WRITE_CHANNEL_USED;
                    }
                    else
                    {
                        DmaChNum = HSSL1_DMA_MULTI_WRITE_CHANNEL_USED;
                    }
#endif

                    Dma_ChStopTransfer((uint8)DmaChNum);
       /* MISRA2012_RULE_11_6_JUSTIFICATION:The address of the buffer pointer is
       stores in a local variable to be comapred against 0-NULL.
       There are no other operation performed, hence this convesion
       does not cause any issue */
       /* MISRA2012_RULE_11_4_JUSTIFICATION:The address of the buffer pointer is
       stores in a local variable to be comapred against 0-NULL.
       There are no other operation performed, hence this convesion
       does not cause any issue */
                    Hssl_DmaTxConfig.SourceAddress = (uint32)(WriteArray->Data);
       /* MISRA2012_RULE_11_6_JUSTIFICATION:The address of the buffer pointer is
       stores in a local variable to be comapred against 0-NULL.
       There are no other operation performed, hence this convesion
       does not cause any issue */
       /* MISRA2012_RULE_11_4_JUSTIFICATION:The address of the buffer pointer is
       stores in a local variable to be comapred against 0-NULL.
       There are no other operation performed, hence this convesion
       does not cause any issue */
                    Hssl_DmaTxConfig.DestAddress = (uint32)WriteDataRegPtr;
                    Hssl_DmaTxConfig.Config = (
                    ((uint32)HSSL_DMA_CHCFGR_REGVALUE_WRITE) |
                    ((uint32)(NumCmd) & (uint32)HSSL_DMA_CHCFGR_TREL_MASK));

                    Hssl_DmaTxConfig.UpdateSourceAddress = 1U;
                    Hssl_DmaTxConfig.UpdateDestAddress = 1U;
                    Hssl_DmaTxConfig.UpdateConfig = 1U;
/* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable Hssl_DmaTxConfig
              is used inside Dma_ChUpdate() to
            read the values. The address is not used beyond the context of the
            API, hence it is not an issue*/
                    Dma_ChUpdate((uint8)DmaChNum, &Hssl_DmaTxConfig, NULL_PTR);
                    Dma_ChEnableHardwareTrigger(DmaChNum);
                    Dma_ChStartTransfer(DmaChNum);
                }
                else
                {
                    RetVal = E_NOT_OK;
                }
            }
            ChStateTypePtr[Channel->Number]  = HSSL_COMMAND_COMPLETED;
        }
    }
    if ( RetVal == E_NOT_OK )
    {
         Hssl_DMAWriteOperationState[id] = HSSL_DMA_OPERATION_COMPLETED;
    }
    return(RetVal);
}
#if ( HSSL_DEV_ERROR_DETECT == STD_ON )
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : static uint8 Hssl_lCheckParam                            **
**                    (const uint8 ApiID,                                     **
**                     const Hssl_DataTemplateType *WriteBuffer,              **
**                     const Hssl_ReadDataTemplateType *ReadBuffer,           **
**                     const uint32 *Buffer, const uint16 cmd)                **
**                                                                            **
** Description     :                                                          **
**                                                                            **
** Service ID      :                                                          **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : ApiID : Indicates the API ID                             **
**                   WriteBuffer : Write buffer address                       **
**                   ReadBuffer : Read buffer address                         **
**                   Buffer : Buffer for receiving the data                   **
**                   cmd : Indicates the command to execute                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns HSSL_ERR_NOT_FOUND or HSSL_ERR_FOUND based on    **
**                   validation.                                              **
*******************************************************************************/
static uint8 Hssl_lCheckParam(const uint8 ApiID,
                              const Hssl_DataTemplateType *WriteBuffer,
                              const Hssl_ReadDataTemplateType *ReadBuffer,
                              const uint32 *Buffer, const uint16 cmd)
{
    uint8 ErrorFlag = HSSL_ERR_NOT_FOUND;

    if (ApiID == HSSL_SID_WRITE_MULTIPLE)
    {
        if ((NULL_PTR == WriteBuffer))
        {
            Det_ReportError(HSSL_MODULE_ID,HSSL_MODULE_INSTANCE,
                        ApiID,HSSL_E_INV_POINTER);
            ErrorFlag = HSSL_ERR_FOUND ;
        }
    }
    if (ApiID == HSSL_SID_READ_MULTIPLE)
    {
        if ((NULL_PTR == Buffer) || (NULL_PTR == ReadBuffer))
        {
            Det_ReportError(HSSL_MODULE_ID,HSSL_MODULE_INSTANCE,
                        ApiID,HSSL_E_INV_POINTER);
            ErrorFlag = HSSL_ERR_FOUND ;
        }
    }
    if (cmd == 0U)
    {
        Det_ReportError(HSSL_MODULE_ID,HSSL_MODULE_INSTANCE,
                    ApiID,HSSL_E_INV_PARAM);
        ErrorFlag = HSSL_ERR_FOUND ;
    }
    return ErrorFlag;
}
#endif
/*
 CYCLOMATIC_Hssl_MultiRead_JUSTIFICATION: Function is used to perform multiple
 read operation using DMA channels, multiple conditions are used to configure
 multi read operations hence this fuction cannot split further.
*/
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_MultiRead                            **
**                    ( const Hssl_InstanceID id,                             **
**                      const Hssl_DataTemplateType *ReadArray,               **
**                      const uint32 *Buffer,                                 **
**                      const uint16 DataSize, const uint16 NumCmd,           **
**                const Hssl_ChannelType *const Channel,                      **
**                    const uint16 InjectedError)                             **
**                                                                            **
** Description     : Performs multiple read transfers.                        **
**                                                                            **
** Service ID      : 0x46                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   ReadArray : Hssl_DataTemplateType structure which        **
**                    includes array containing write Address and Data to be  **
**                    read for each array record.                             **
**                   Buffer: Store buffer for received data                   **
**                   DataSize: Size of data to be written.                    **
**                   NumCmd : Number of address command pairs                 **
**                   Channel: HSSL Channel to use.                            **
**                   InjectedError: injected Error (if required)              **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
Std_ReturnType Hssl_MultiRead (const Hssl_InstanceID id,\
                               const Hssl_ReadDataTemplateType *ReadArray,\
                               const uint32 *Buffer,
                               const uint16 DataSize,const uint16 NumCmd,\
                               const Hssl_ChannelType *const Channel,
                               const uint16 InjectedError)
{
    Std_ReturnType RetVal = E_NOT_OK;
    Dma_ConfigUpdateType Hssl_DmaTxConfig={0};
    Dma_ConfigUpdateType Hssl_DmaRxConfig = {0};
    uint8 DmaRxChNum;
    uint8 DmaTxChNum;
    Hssl_ChStateType *ChStateTypePtr= NULL_PTR;
    /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
    this MISRA rule. Union usage is required to access SFR data type and
    implement efficiently for clearing of pending service requrest in Interrupt
    control register */
    volatile  Ifx_HSSL_I_IRWA * ReadAddrssPtr;
    /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
    this MISRA rule. Union usage is required to access SFR data type and
    implement efficiently for clearing of pending service requrest in Interrupt
    control register */
    volatile Ifx_HSSL_I_IRD *ReadDataPtr;
    /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
    this MISRA rule. Union usage is required to access SFR data type and
    implement efficiently for clearing of pending service requrest in Interrupt
    control register */
    volatile Ifx_HSSL_I_ICON *CtrlRegPtr;
    uint8 ErrorFlag = HSSL_ERR_NOT_FOUND;
    /* Parameter check for the API if DET is STD_ON*/
#if ( HSSL_DEV_ERROR_DETECT == STD_ON )
    ErrorFlag = Hssl_lInstanceIDVerify(id, HSSL_SID_READ_MULTIPLE);
    if (HSSL_ERR_FOUND != ErrorFlag)
    {

        /* Verify Channel Number parameter */
        ErrorFlag = Hssl_lChannelVerify(id, Channel->Number,\
                                        HSSL_SID_READ_MULTIPLE);

        /* verify the data size */
        if (HSSL_ERR_FOUND != ErrorFlag)
        {
         ErrorFlag = Hssl_ldataSizeVerify(id, DataSize, HSSL_SID_READ_MULTIPLE);

            /* Verify the mode to be run */
            if (HSSL_ERR_FOUND != ErrorFlag)
            {
                ErrorFlag = Hssl_lRunModeVerify(id, HSSL_SID_READ_MULTIPLE);
                  /* verify the data pointer */
                  if (HSSL_ERR_FOUND != ErrorFlag)
                  {
                   ErrorFlag = Hssl_lCheckParam(HSSL_SID_READ_MULTIPLE,NULL_PTR,
                                                 ReadArray,Buffer,NumCmd);
                  }
            }
        }
    }
    /*If no Error present*/
    if (HSSL_ERR_FOUND != ErrorFlag)
#endif
    {
        /* Check if any other channel is already using DMA */
        ErrorFlag = Hssl_lcheckDMAReadchannelUsage(id);
        if (HSSL_ERR_FOUND != ErrorFlag)
        {
#if (HSSL0_CONFIGURRED == STD_ON)
        if (id == HSSL0)
        {
            ChStateTypePtr = Hssl0ChState;
        }
#endif
#if (HSSL1_CONFIGURRED == STD_ON)
        if (id == HSSL1)
        {
            ChStateTypePtr = Hssl1ChState;
        }
#endif
        ReadAddrssPtr = (&HSSL_Reg[id]->I[Channel->Number].IRWA);
        ReadDataPtr = (&HSSL_Reg[id]->I[Channel->Number].IRD);
        CtrlRegPtr = (&HSSL_Reg[id]->I[Channel->Number].ICON);

        /* Enter SchM section to prevent concurrent access */

            SchM_Enter_Hssl_ChannelStatusLock();
            if ( ChStateTypePtr[Channel->Number] != HSSL_COMMAND_IN_PROGRESS)
            {
                /* set the channel state to "HSSL_COMMAND_IN_PROGRESS" */
                ChStateTypePtr[Channel->Number]  = HSSL_COMMAND_IN_PROGRESS;
                RetVal = E_OK;
            }
            /* Enter SchM */
            SchM_Exit_Hssl_ChannelStatusLock();
            if (RetVal == E_OK)
            {
                RetVal = E_NOT_OK;
              /*  Read ICONx.BSY bit to check if Channel is Busy or Available */
                if(CtrlRegPtr->B.BSY == 0U)
                {
                    /* If injected Error is needed set it in CRC register */
                    if(InjectedError != 0U)
                    {
                     HSSL_RUNTIME_WRITEENDINITPROTREG(
                     &(HSSL_Reg[id]->CRC),
                     ((uint32)InjectedError | (1UL<<HSSL_CRC_EN_SHIFT)));
                    }

#if (HSSL_NUM_INSTANCES_CONFIGURRED == 1U)

                    DmaRxChNum = HSSL_DMA_MULTI_READ_RX_CHANNEL;
                    DmaTxChNum = HSSL_DMA_MULTI_READ_TX_CHANNEL;
#else
                    if (id == HSSL0)
                    {
                        DmaRxChNum = HSSL0_DMA_MULTI_READ_RX_CHANNEL_USED;
                        DmaTxChNum = HSSL0_DMA_MULTI_READ_TX_CHANNEL_USED;
                    }
                    else
                    {
                        DmaRxChNum = HSSL1_DMA_MULTI_READ_RX_CHANNEL_USED;
                        DmaTxChNum = HSSL1_DMA_MULTI_READ_TX_CHANNEL_USED;
                    }
#endif

                    Dma_ChStopTransfer((uint8)DmaRxChNum);
                    Dma_ChStopTransfer((uint8)DmaTxChNum);

                    /* Write data size in ICONx */
                    CtrlRegPtr->B.DATLEN = (uint8)DataSize;
                    /* Write Time Out Value in ICONx */
                    CtrlRegPtr->B.TOREL  = (uint8)Channel->Timeout;
                    /* Write ICONx.RWT with 0x10 Write Frame */
                    CtrlRegPtr->B.RWT    = HSSL_READ_FRAME;

                    /* Using DMA channel - 1 ,
                    send the address from RAM buffer to Register */
       /* MISRA2012_RULE_11_6_JUSTIFICATION:The address of the buffer pointer is
       stores in a local variable to be comapred against 0-NULL.
       There are no other operation performed, hence this convesion
       does not cause any issue */
       /* MISRA2012_RULE_11_4_JUSTIFICATION:The address of the buffer pointer is
         stores in a local variable to be comapred against 0-NULL.
         There are no other operation performed, hence this convesion
         does not cause any issue */
                    Hssl_DmaRxConfig.SourceAddress = (uint32)ReadDataPtr;
      /* MISRA2012_RULE_11_6_JUSTIFICATION:The address of the buffer pointer is
            stores in a local variable to be comapred against 0-NULL.
            There are no other operation performed, hence this convesion
            does not cause any issue */
      /* MISRA2012_RULE_11_4_JUSTIFICATION:The address of the buffer pointer is
      stores in a local variable to be comapred against 0-NULL.
      There are no other operation performed, hence this convesion
      does not cause any issue */
                    Hssl_DmaRxConfig.DestAddress = (uint32)(Buffer);
                    Hssl_DmaRxConfig.Config = (
                    ((uint32)HSSL_DMA_CHCFGR_REGVALUE_READ) |
                    ((uint32)(NumCmd) & (uint32)HSSL_DMA_CHCFGR_TREL_MASK));

                    Hssl_DmaRxConfig.UpdateSourceAddress = 1U;
                    Hssl_DmaRxConfig.UpdateDestAddress = 1U;
                    Hssl_DmaRxConfig.UpdateConfig = 1U;
/* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable Hssl_DmaRxConfig
              is used inside Dma_ChUpdate() to
            read the values. The address is not used beyond the context of the
            API, hence it is not an issue*/
                   Dma_ChUpdate((uint8)DmaRxChNum, &Hssl_DmaRxConfig, NULL_PTR);
                    Dma_ChEnableHardwareTrigger((uint8)DmaRxChNum);

                    /* Using DMA channel -1 ,
                    send the address from RAM buffer to Register */
       /* MISRA2012_RULE_11_6_JUSTIFICATION:The address of the buffer pointer is
       stores in a local variable to be comapred against 0-NULL.
       There are no other operation performed, hence this convesion
       does not cause any issue */
       /* MISRA2012_RULE_11_4_JUSTIFICATION:The address of the buffer pointer is
             stores in a local variable to be comapred against 0-NULL.
             There are no other operation performed, hence this convesion
             does not cause any issue */
                  Hssl_DmaTxConfig.SourceAddress = (uint32)(ReadArray->Address);

       /* MISRA2012_RULE_11_6_JUSTIFICATION:The address of the buffer pointer is
       stores in a local variable to be comapred against 0-NULL.
       There are no other operation performed, hence this convesion
       does not cause any issue */
       /* MISRA2012_RULE_11_4_JUSTIFICATION:The address of the buffer pointer is
         stores in a local variable to be comapred against 0-NULL.
         There are no other operation performed, hence this convesion
         does not cause any issue */
                    Hssl_DmaTxConfig.DestAddress = (uint32)ReadAddrssPtr;
                    Hssl_DmaTxConfig.Config = (
                    ((uint32)HSSL_DMA_CHCFGR_REGVALUE_READ) |
                    ((uint32)(NumCmd) & (uint32)HSSL_DMA_CHCFGR_TREL_MASK));

                    Hssl_DmaTxConfig.UpdateSourceAddress = 1U;
                    Hssl_DmaTxConfig.UpdateDestAddress = 1U;
                    Hssl_DmaTxConfig.UpdateConfig = 1U;
/* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable Hssl_DmaTxConfig
              is used inside Dma_ChUpdate() to
            read the values. The address is not used beyond the context of the
            API, hence it is not an issue*/
                   Dma_ChUpdate((uint8)DmaTxChNum, &Hssl_DmaTxConfig, NULL_PTR);
                    Dma_ChEnableHardwareTrigger((uint8)DmaTxChNum);
                    Dma_ChStartTransfer((uint8)DmaTxChNum);
                    RetVal = E_OK;
                }
                ChStateTypePtr[Channel->Number] = HSSL_COMMAND_IN_PROGRESS;

            }
        }
    }
        if ( RetVal == E_NOT_OK )
        {
            Hssl_DMAReadOperationState[id] = HSSL_DMA_OPERATION_COMPLETED;
        }
    return(RetVal);
}
#if (HSSL_MULTI_SLAVE_MODE == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_SelectSlave(const Hssl_InstanceID id,**
**                         const uint8 Hssl_SlaveID)                          **
**                                                                            **
** Description     : Selecting the slave in multi slave mode.                 **
**                                                                            **
** Service ID      : 0x4B                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   Hssl_SlaveID : Indicates HSSL slave ID                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
Std_ReturnType Hssl_SelectSlave(const Hssl_InstanceID id, 
                                     const uint8 Hssl_SlaveID)
{
    Std_ReturnType RetVal = E_NOT_OK;

#if ( HSSL_DEV_ERROR_DETECT == STD_ON )
    uint8 ErrorFlag = HSSL_ERR_NOT_FOUND;
    /* Check for the proper HSSL instance */
    ErrorFlag = Hssl_lInstanceIDVerify(id, HSSL_SID_SELECT_SLAVE);
    if (HSSL_ERR_NOT_FOUND == ErrorFlag)
    {
        ErrorFlag = Hssl_lRunModeVerify(id, HSSL_SID_SELECT_SLAVE);
    }
    if (HSSL_ERR_NOT_FOUND == ErrorFlag)
    {
        /* Check for the proper HSSL instance */
        if ((Hssl_SlaveID == 0U) || ( Hssl_SlaveID > 3U))
        {
            Det_ReportError(HSSL_MODULE_ID,HSSL_MODULE_INSTANCE,
                        HSSL_SID_SELECT_SLAVE,HSSL_E_INV_PARAM);

            ErrorFlag = HSSL_ERR_FOUND;
        }
    }
    if (HSSL_ERR_NOT_FOUND == ErrorFlag)
#endif
    {
        HSSL_Reg[id]->MSCR.B.SLAVETAG = Hssl_SlaveID;
        RetVal = E_OK;
    }
    return (RetVal);
}

#endif
#if (HSSL_INTERFACE_MODE == HSSL_MASTER)
#if (HSSL_MULTI_SLAVE_MODE == STD_ON)
#if ( HSSL_DEV_ERROR_DETECT == STD_ON )
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : static uint8 Hssl_lcheckSlaveParam( const                **
**                           Hssl_SlaveStatusType *Hssl_SlaveStatus)          **
**                                                                            **
** Description     : Activates the slave in multi slave mode.                 **
**                                                                            **
** Service ID      : 0x0B                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): Hssl_SlaveStatus : returns the slave status              **
**                                                                            **
** Return value    : Returns HSSL_ERR_NOT_FOUND or HSSL_ERR_FOUND             **
**                                                                            **
*******************************************************************************/
static uint8 Hssl_lcheckSlaveParam(const Hssl_SlaveStatusType *Hssl_SlaveStatus)
{
    uint8 ErrorFlag = HSSL_ERR_NOT_FOUND;
    if (NULL_PTR == Hssl_SlaveStatus)
    {
        Det_ReportError(HSSL_MODULE_ID,HSSL_MODULE_INSTANCE,
                        HSSL_SID_ACTIVATE_SLAVE,HSSL_E_INV_POINTER);
        ErrorFlag = HSSL_ERR_FOUND ;
    }
    return ErrorFlag;
}
#endif
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_ActivateSlave(const Hssl_InstanceID  **
**                   id, const uint8 Hssl_SlaveID,                            **
**                   Hssl_SlaveStatusType *const Hssl_SlaveStatus)            **
**                                                                            **
** Description     : Activates the slave in multi slave mode.                 **
**                                                                            **
** Service ID      : 0x49                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   Hssl_SlaveID : Indicates HSSL Slave ID                   **
**                                                                            **
** Parameters (out): Hssl_SlaveStatus : returns the slave status              **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
Std_ReturnType Hssl_ActivateSlave(const Hssl_InstanceID id, 
                                   const uint8 Hssl_SlaveID,
                                  Hssl_SlaveStatusType *const Hssl_SlaveStatus)
{
    Std_ReturnType RetVal = E_NOT_OK;
    Hssl_DataTemplateType WriteData;
    uint32 DataBuffer;
    uint32 DataAddr;
    Hssl_ChannelType Channel;
    uint8 SlaveId;
    uint8 ControlCode;
    Hssl_ChStateType *ChStateTypePtr = NULL_PTR;

#if ( HSSL_DEV_ERROR_DETECT == STD_ON )
    uint8 ErrorFlag = HSSL_ERR_NOT_FOUND;

    /* Check for the proper HSSL instance */
    ErrorFlag = Hssl_lInstanceIDVerify(id, HSSL_SID_ACTIVATE_SLAVE);

    if(HSSL_ERR_NOT_FOUND == ErrorFlag)
    {
        ErrorFlag = Hssl_lRunModeVerify(id, HSSL_SID_ACTIVATE_SLAVE);
        if(HSSL_ERR_NOT_FOUND == ErrorFlag)
        {
            ErrorFlag = Hssl_lcheckSlaveParam(Hssl_SlaveStatus);

            if(HSSL_ERR_NOT_FOUND == ErrorFlag)
            {
#endif

#if (HSSL0_CONFIGURRED == STD_ON)
        if (id == HSSL0)
        {
            ChStateTypePtr = Hssl0ChState;
        }
#endif
#if (HSSL1_CONFIGURRED == STD_ON)
        if (id == HSSL1)
        {
            ChStateTypePtr = Hssl1ChState;
        }
#endif


            SchM_Enter_Hssl_ActivateSlave();
           if ( HsslActivateSlaveState[id] != (uint8)HSSL_ACTIVATON_IN_PROGRESS)
            {
                /* set the channel state to "HSSL_COMMAND_IN_PROGRESS" */
                HsslActivateSlaveState[id]  = (uint8)HSSL_ACTIVATON_IN_PROGRESS;
                RetVal = E_OK;
            }
            SchM_Exit_Hssl_ActivateSlave();
            if (RetVal == E_OK)
            {
                /* Enter SchM */
                /* Read the SLAVETAG to Get the SLAVE ID configured */
                SlaveId  = HSSL_Reg[id]->MSCR.B.SLAVETAG;
                *Hssl_SlaveStatus = HSSL_SLAVE_NOT_SELECTED;
                RetVal = E_NOT_OK;
                /* Load the appropriate interface control
                command based on slave ID */
                if (SlaveId == Hssl_SlaveID)
                {
                    ControlCode = (uint8)(0x50U + SlaveId);

                    /* Send the Interface control command to enable the
                    * slave transmitter */
                    HSCT_Reg[id]->IFCTRL.B.IFCVS = ControlCode;
                    HSCT_Reg[id]->IFCTRL.B.SIFCV = 1;

                    /* Activate the slave transmission by sending 16 Bit write
                    * frame using Hssl Channel-0 */
                    Channel.Number = 0U;
                    Channel.Timeout = HSSL_TIMEOUT;
                    DataBuffer = HSSL_SLAVE_TRANSMISSION_ON;
            /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable
            DataBuffer is used inside Hssl_lSingleFrameWrite() to
            read the values. The address is not used beyond the context of the
            API, hence it is not an issue*/
                    WriteData.Data = &DataBuffer ;
       /* MISRA2012_RULE_11_6_JUSTIFICATION:The address of the buffer pointer is
         stores in a local variable to be comapred against 0-NULL.
         There are no other operation performed, hence this convesion
         does not cause any issue */
       /* MISRA2012_RULE_11_4_JUSTIFICATION:The address of the buffer pointer is
         stores in a local variable to be comapred against 0-NULL.
         There are no other operation performed, hence this convesion
         does not cause any issue */
                    DataAddr = ((uint32)(&HSSL_Reg[id]->MSCR)) +
                                   HSSL_MSCR_UPPER_HALF_WORD_OFF ;
            /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable
            DataAddr is used inside Hssl_lSingleFrameWrite() to
            read the values. The address is not used beyond the context of the
            API, hence it is not an issue*/
                    WriteData.Address = &DataAddr;
                    /* Check for pending requests on Channel -0*/
                    /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable
                    Channel is used inside Hssl_lWriteAck() to
                    read the values. The address is not used beyond the context of the
                    API, hence it is not an issue*/
                    (void)Hssl_lWriteAck(id, &Channel);
                    /* trigger the Write frame to Set MSCR.ITXSTOP = 0 */
            /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable
            WriteData is used inside Hssl_lSingleFrameWrite() to
            read the values. The address is not used beyond the context of the
            API, hence it is not an issue*/
                    RetVal = Hssl_lSingleFrameWrite(id,&WriteData,
                    /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable
                    Channel is used inside Hssl_lSingleFrameWrite() to
                    read the values. The address is not used beyond the context of the
                    API, hence it is not an issue*/
                    HSSL_DATA_SIZE_16BIT,&Channel,0U,&HsslActivateSlaveAPI[id]);
                    *Hssl_SlaveStatus = HSSL_SLAVE_NOT_RESPONDING;
                    if (RetVal == E_OK)
                    {
                      /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable
                         Channel is used inside Hssl_lWriteAck() to
                         read the values. The address is not used beyond the context of the
                         API, hence it is not an issue*/
                        RetVal = Hssl_lWriteAck(id, &Channel);
                        if (RetVal == E_OK)
                        {
                            RetVal = E_NOT_OK;
                            /* Send the trigger command */
                            SchM_Enter_Hssl_ChannelStatusLock();
                            if ( ChStateTypePtr[Channel.Number] !=
                                  HSSL_COMMAND_IN_PROGRESS)
                            {
                      /* set the channel state to "HSSL_COMMAND_IN_PROGRESS" */
                                ChStateTypePtr[Channel.Number] =
                                HSSL_COMMAND_IN_PROGRESS;
                                RetVal = E_OK;
                            }
                            SchM_Exit_Hssl_ChannelStatusLock();
                            if (RetVal == E_OK)
                            {
                                HsslActivateSlaveAPI[id] = 1;
                                HSSL_Reg[id]->I[Channel.Number].ICON.B.TQ = 1U;
                                /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable
                                   Channel is used inside Hssl_lTriggerRply() to
                                   read the values. The address is not used beyond the context of the
                                   API, hence it is not an issue*/
                                RetVal = Hssl_lTriggerRply(id, &Channel);
                                if (RetVal == E_OK)
                                {
                                    *Hssl_SlaveStatus = HSSL_SLAVE_ACTIVATED;
                                    HsslActivateSlaveState[id] =
                                    (uint8)HSSL_ACTIVATION_COMPLETED;
                                }
                                ChStateTypePtr[Channel.Number] =
                                HSSL_COMMAND_COMPLETED;
                            }
                        }
                    }
                }
            }
#if ( HSSL_DEV_ERROR_DETECT == STD_ON )
        }
        }
    }
#endif
    return RetVal;
}
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_DeactivateSlave(const Hssl_InstanceID**
**                   id, const uint8 Hssl_SlaveID,                            **
**                   Hssl_SlaveStatusType *const Hssl_SlaveStatus)            **
**                                                                            **
** Description     : Deactivates the slave in multi slave mode.               **
**                                                                            **
** Service ID      : 0x4A                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   Hssl_SlaveID : Indicates HSSL Slave ID                   **
**                                                                            **
** Parameters (out): Hssl_SlaveStatus : returns the slave status              **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
Std_ReturnType Hssl_DeactivateSlave(const Hssl_InstanceID id,
                                    const uint8 Hssl_SlaveID,
                                    Hssl_SlaveStatusType *const Hssl_SlaveStatus)
{
    Std_ReturnType RetVal = E_NOT_OK;
    Hssl_DataTemplateType WriteData;
    uint32 DataBuffer;
    uint32 DataAddr;
    Hssl_ChannelType Channel;
    uint8 SlaveId;

#if ( HSSL_DEV_ERROR_DETECT == STD_ON )
    uint8 ErrorFlag = HSSL_ERR_NOT_FOUND;

    /* Check for the proper HSSL instance */
    ErrorFlag = Hssl_lInstanceIDVerify(id, HSSL_DEACTIVATE_SLAVE);

    if(HSSL_ERR_NOT_FOUND == ErrorFlag)
    {

        ErrorFlag = Hssl_lRunModeVerify(id, HSSL_DEACTIVATE_SLAVE);
        if(HSSL_ERR_NOT_FOUND == ErrorFlag)
        {
            if (NULL_PTR == Hssl_SlaveStatus)
            {
                Det_ReportError(HSSL_MODULE_ID,HSSL_MODULE_INSTANCE,
                HSSL_DEACTIVATE_SLAVE,HSSL_E_INV_POINTER);
                        ErrorFlag = HSSL_ERR_FOUND ;
            }
            if(HSSL_ERR_NOT_FOUND == ErrorFlag)
            {
#endif

                SchM_Enter_Hssl_DeactivateSlave();
                if (HsslDeactivateSlaveState[id] !=
                             (uint8)HSSL_DEACTIVATON_IN_PROGRESS)
                {
                    /* set the channel state to "HSSL_COMMAND_IN_PROGRESS" */
                    HsslDeactivateSlaveState[id] =
                              (uint8)HSSL_DEACTIVATON_IN_PROGRESS;
                    RetVal = E_OK;
                }
                SchM_Exit_Hssl_DeactivateSlave();

                if (RetVal == E_OK)
                {
                    Channel.Number = 0U;
                    Channel.Timeout = HSSL_TIMEOUT;
                    /* Read the SLAVETAG to Get the SLAVE ID configured */
                    SlaveId  = HSSL_Reg[id]->MSCR.B.SLAVETAG;

                 /* Load the appropriate interface control command
                 based on slave ID */
                    if (SlaveId == Hssl_SlaveID)
                    {
                      /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable
                      Channel is used inside Hssl_lReadRply() to
                     read the values. The address is not used beyond the context of the
                     API, hence it is not an issue*/
                        (void)Hssl_lReadRply(id, &Channel);
                        /* Set the ITXSTOP bit to disable the slave initiator
                        transmission */
                        DataBuffer = HSSL_SLAVE_TRANSMISSION_OFF;
                    /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto
                    variable DataBuffer is used inside Hssl_lSingleFrameWrite()
                    to read the values. The address is not used beyond the
                    context of the API, hence it is not an issue*/
                        WriteData.Data = &DataBuffer ;
               /* MISRA2012_RULE_11_6_JUSTIFICATION:The address of the buffer
               pointer is stores in a local variable to be comapred against
                0-NULL. There are no other operation performed, hence this
                convesion does not cause any issue */
               /* MISRA2012_RULE_11_4_JUSTIFICATION:The address of the buffer
               pointer is stores in a local variable to be comapred against
               0-NULL.There are no other operation performed, hence this convesion
                 does not cause any issue */
                    DataAddr = ((uint32)(&HSSL_Reg[id]->MSCR)) +
                                  HSSL_MSCR_UPPER_HALF_WORD_OFF ;
                    /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable
                    DataAddr is used inside Hssl_lSingleFrameWrite() to
                    read the values. The address is not used beyond the
                    context of the API, hence it is not an issue*/
                    WriteData.Address = &DataAddr;
                    /* Check for pending requests on Channel -0*/
                    /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable
                      Channel is used inside Hssl_lWriteAck() to
                     read the values. The address is not used beyond the context of the
                     API, hence it is not an issue*/
                    (void)Hssl_lWriteAck(id, &Channel);
                     /* trigger the Write frame to Set MSCR.ITXSTOP = 1 */
                    /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable
                    WriteData is used inside Hssl_lSingleFrameWrite() to
                    read the values. The address is not used beyond the context
                    of the API, hence it is not an issue*/
                    RetVal = Hssl_lSingleFrameWrite(id,&WriteData,
                    /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable
                    Channel is used inside Hssl_lSingleFrameWrite() to
                    read the values. The address is not used beyond the context
                    of the API, hence it is not an issue*/
                    HSSL_DATA_SIZE_16BIT,&Channel,0U,&HsslDeactivateSlaveAPI[id]);
                    *Hssl_SlaveStatus = HSSL_SLAVE_NOT_RESPONDING;
                    if (RetVal == E_OK)
                    {
                      /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable
                      Channel is used inside Hssl_lWriteAck() to
                     read the values. The address is not used beyond the context of the
                     API, hence it is not an issue*/
                        RetVal = Hssl_lWriteAck(id, &Channel);
                        if (RetVal == E_OK)
                        {
                            RetVal = Hssl_lPollForSlaveExpectFlags(id);
                            if (RetVal == E_OK)
                            {
                                Hssl_lPollForMasterExpectFlags(id);
                                /* Send interface control command to
                                disable the LVDS pads */
                                HSCT_Reg[id]->IFCTRL.B.IFCVS =
                                              HSSL_SLAVE_LVDS_DISABLE;
                                HSCT_Reg[id]->IFCTRL.B.SIFCV = 1;
                                *Hssl_SlaveStatus = HSSL_SLAVE_DEACTIVATED;
                                HsslDeactivateSlaveState[id] =
                                     (uint8)HSSL_DEACTIVATON_COMPLETED;
                            }
                        }
                    }
                }
                else
                {
                    RetVal = E_NOT_OK;
                    *Hssl_SlaveStatus = HSSL_SLAVE_NOT_SELECTED;
                }
            }

#if ( HSSL_DEV_ERROR_DETECT == STD_ON )
    }
        }
    }
#endif
    return RetVal;
}

#endif
#endif
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_GetGlobalError(                      **
**                                  const Hssl_InstanceID id,\                **
**                                  uint32 *const Hssl_GlobalErrFlg);         **
**                                                                            **
** Description     : Reads the global error flags for the HSSL                **
**                                                                            **
** Service ID      : 0x47                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   Hssl_GlobalErrFlg: Pointer to store Hssl                 **
                                        Global error flags value              **
** Parameters (out): Hssl_GlobalErrFlg : Hssl Global error flags value        **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
Std_ReturnType Hssl_GetGlobalError(const Hssl_InstanceID id,\
                                   uint32 *const Hssl_GlobalErrFlg)
{
    Std_ReturnType RetVal = E_NOT_OK;

    /* Parameter check for the API if DET is STD_ON*/
#if ( HSSL_DEV_ERROR_DETECT == STD_ON )
    uint8 ErrorFlag = HSSL_ERR_NOT_FOUND;
    if(NULL_PTR == Hssl_GlobalErrFlg)
    {
        Det_ReportError(HSSL_MODULE_ID,HSSL_MODULE_INSTANCE,\
                        HSSL_SID_GET_GLOBALERROR, HSSL_E_INV_POINTER);
        ErrorFlag = HSSL_ERR_FOUND;
    }
    if(HSSL_ERR_NOT_FOUND == ErrorFlag )
    {
        /* Check for the proper HSSL instance */
        ErrorFlag = Hssl_lInstanceIDVerify(id, HSSL_SID_GET_GLOBALERROR);
        if(HSSL_ERR_NOT_FOUND == ErrorFlag)
        {
            ErrorFlag = Hssl_lRunModeVerify(id, HSSL_SID_GET_GLOBALERROR);
        }
        if(HSSL_ERR_NOT_FOUND == ErrorFlag)
#endif     /*End Of HSSL_DEV_ERROR_DETECT*/
        {
            RetVal = E_OK;
            /* Read the Global Error Flags*/
            *Hssl_GlobalErrFlg = (uint32)HSSL_Reg[id]->MFLAGS.U ;
        }
#if ( HSSL_DEV_ERROR_DETECT == STD_ON )
    }
#endif
    return(RetVal);
}
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_GetChannelError                      **
**                 (const Hssl_InstanceID id,Hssl_ChannelType *const Channel, **
**                      Hssl_ChannelErrorType *ChannelError)                  **
**                                                                            **
** Description     : Reads the channel error flags for the HSSL channel       **
**                                                                            **
** Service ID      : 0x4C                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   Channel: HSSL Channel to use.                            **
**                                                                            **
** Parameters (out):  ChannelError : Holds the channel error occured          **
**                                                                            **
** Return value    : Returns E_OK, Successful execution. Otherwise E_NOT_OK.  **
*******************************************************************************/
Std_ReturnType Hssl_GetChannelError(const Hssl_InstanceID id,
                                    const Hssl_ChannelType *const Channel,
                                    Hssl_ChannelErrorType *const ChannelError)
{
    Std_ReturnType RetVal = E_NOT_OK;

#if ( HSSL_DEV_ERROR_DETECT == STD_ON )
    uint8 ErrorFlag;

    /* verify the instance id */
    ErrorFlag = Hssl_lInstanceIDVerify(id, HSSL_SID_GET_CHANNELERROR);

    /*If Error Flag is not set*/
    if (HSSL_ERR_FOUND != ErrorFlag)
    {
        ErrorFlag = Hssl_lRunModeVerify(id,HSSL_SID_GET_CHANNELERROR);
        if (HSSL_ERR_FOUND != ErrorFlag)
        {
          /* Verify Channel Number parameter */
           ErrorFlag = Hssl_lChannelVerify(id, Channel->Number,\
                                            HSSL_SID_GET_CHANNELERROR);
        }
    }
    /*If no error present*/
    if (HSSL_ERR_FOUND != ErrorFlag)
#endif  /*End Of HSSL_DEV_ERROR_DETECT*/
{
        *ChannelError = HSSL_CHANNEL_NO_ERROR;
        /* NACK Error */
        if (((HSSL_Reg[id]->MFLAGS.B.NACK) & (1U << Channel->Number)) != 0U)
        {
            *ChannelError = HSSL_CHANNEL_NACK_ERROR;
        }
        /* Transcation Tag Error */
        else if(((HSSL_Reg[id]->MFLAGS.B.TTE) & (1U << Channel->Number)) != 0U)
        {
            *ChannelError = HSSL_CHANNEL_TRANSACTION_TAG_ERROR;
        }
        /*TIMEOUT Error*/
        else if(((HSSL_Reg[id]->MFLAGS.B.TIMEOUT) & (1U << Channel->Number)) != 0U)
        {
            *ChannelError = HSSL_CHANNEL_TIMEOUT_ERROR;
        }
        /*Unexpected Error*/
        else if(((HSSL_Reg[id]->MFLAGS.B.UNEXPECTED) & (1U << Channel->Number)) != 0U)
        {
            *ChannelError = HSSL_CHANNEL_UNEXPECTED_ERROR;
        }
        else
        {
            /* Do Nothing */
        }
        RetVal = E_OK;
}
return RetVal;
}
#if(HSSL_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID=]                                        **
**                                                                            **
** Syntax          : void  Hssl_GetVersionInfo                                **
**                   ( const Hssl_InstanceID id,                              **
**                     Std_VersionInfoType *const versioninfo                 **
**                   )                                                        **
**                                                                            **
** Description     : This service returns the version information of module.  **
**                   The version information includes:                        **
**                   - Vendor Id                                              **
**                   - Module Id                                              **
**                   - SW Major Version                                       **
**                   - SW Minor Version                                       **
**                   - SW Patch Version                                       **
**                                                                            **
** Service ID      : 0x48                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   versioninfo : (Pointer to store the version              **
**                   information of this module)                              **
**                                                                            **
** Parameters (out): versioninfo values are updated with version              **
**                   information                                              **
**                                                                            **
** Return value:   : None                                                     **
**                                                                            **
*******************************************************************************/
void Hssl_GetVersionInfo(Std_VersionInfoType *const versioninfo)
{
    /*
      Development Error Check: (only if Development Error Detection is ON)
      1. Check input VersionInfoPtr for invalid pointer (NULL_PTR) and
         report DET Error.
    */
#if (HSSL_DEV_ERROR_DETECT == STD_ON)
    uint8 ErrorFlag = HSSL_ERR_NOT_FOUND;

    if (NULL_PTR == versioninfo)
    {
        Det_ReportError(HSSL_MODULE_ID,HSSL_MODULE_INSTANCE,\
                        HSSL_SID_GET_VERSIONINFO, HSSL_E_INV_POINTER);
        ErrorFlag = HSSL_ERR_FOUND;
    }

    if (HSSL_ERR_FOUND != ErrorFlag)
#endif
    {
        /*
          Copy module version information:
          1. Module ID.
          2. Vendor ID.
          3. SW Major version.
          4. SW Minor version.
          5. SW Patch version.
        */

        versioninfo->moduleID         = (uint16)HSSL_MODULE_ID;
        versioninfo->vendorID         = (uint16)HSSL_VENDOR_ID;
        versioninfo->sw_major_version = (uint8)HSSL_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version = (uint8)HSSL_SW_MINOR_VERSION;
        versioninfo->sw_patch_version = (uint8)HSSL_SW_PATCH_VERSION;
    }
}
#endif
#if (HSSL_INTERFACE_MODE == HSSL_MASTER)
#if(HSSL_MULTI_SLAVE_MODE == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : static Std_ReturnType Hssl_lReadRply                     **
**              (const Hssl_InstanceID id,                                    **
**                            const Hssl_ChannelType *const Channel)          **
**                                                                            **
** Description     : Write acknowledge function, should be called when a      **
**                   write acknowledge is received by the module, or a timeout**
**                   occurs during a write command.                           **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non reentrant                                            **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   Channel: HSSL Channel to use.                            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Hssl_lReadRply(const Hssl_InstanceID id,
                                     const Hssl_ChannelType *const Channel)
{
    volatile uint32 Qflags;
    uint32 ExpectMask ;
    Std_ReturnType RetVal;

    /*Read the Request Flag register*/
    Qflags = HSSL_Reg[id]->QFLAGS.U;

    /* Check Ix and Ex signals to check if any request is pending */
    do
    {
        Qflags = HSSL_Reg[id]->QFLAGS.U;
    }while ((Qflags & (((uint32)HSSL_READ_PENDING
          << ((uint32)HSSL_NUM_16 +(Channel->Number * (uint32)HSSL_CHANNEL_CFG)))
          |((uint32)1U << Channel->Number))) != 0U);

    ExpectMask = ((uint32)1U << Channel->Number);        /* Not ACK Error */
    /* Transcation Tag Error */
    ExpectMask = ExpectMask |
                 ((uint32)1U << (Channel->Number + (uint32)HSSL_NUM_4));
    /*TIMEOUT Error*/
    ExpectMask = ExpectMask |
                 ((uint32)1U << (Channel->Number + (uint32)HSSL_NUM_8));
    ExpectMask = ExpectMask |
                 ((uint32)1U << (Channel->Number + (uint32)HSSL_NUM_12));
    /* SRIE,PIE1,PIE2,CRCE */
    ExpectMask = ExpectMask | ((uint32)HSSL_FLAG_CFG << (uint32)HSSL_NUM_22);
    if ((HSSL_Reg[id]->MFLAGS.U & ExpectMask) != 0U)
    {
        RetVal = E_NOT_OK ;
    }
    else
    {
        RetVal = E_OK;
    }

    return RetVal;
}

/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : static Std_ReturnType Hssl_lTriggerRply                  **
**              (const Hssl_InstanceID id,                                    **
**                  const Hssl_ChannelType *const Channel)                    **
**                                                                            **
** Description     : Write acknowledge function, should be called when a      **
**                   write acknowledge is received by the module, or a timeout**
**                   occurs during a write command.                           **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non reentrant                                            **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   Channel: HSSL Channel to use.                            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Hssl_lTriggerRply(const Hssl_InstanceID id,
                                        const Hssl_ChannelType *const Channel)
{
    volatile uint32 Qflags;
    uint32 ExpectMask ;
    Std_ReturnType RetVal;

    /*Read the Request Flag register*/
    Qflags = HSSL_Reg[id]->QFLAGS.U;

    /* Check Ix and Ex signals to check if any request is pending */
    do
    {
        Qflags = HSSL_Reg[id]->QFLAGS.U;
    }while ((Qflags & (((uint32)HSSL_TRIGGER_PENDING << ((uint32)HSSL_NUM_16
                       +(Channel->Number * (uint32)HSSL_CHANNEL_CFG)))
                      |((uint32)1U << Channel->Number))) != 0U);

    ExpectMask = ((uint32)1U << Channel->Number);        /* Not ACK Error */
    /* Transcation Tag Error */
    ExpectMask = ExpectMask |
                 ((uint32)1U << (Channel->Number + (uint32)HSSL_NUM_4));
    /*TIMEOUT Error*/
    ExpectMask = ExpectMask |
                 ((uint32)1U << (Channel->Number + (uint32)HSSL_NUM_8));
    ExpectMask = ExpectMask |
                 ((uint32)1U << (Channel->Number + (uint32)HSSL_NUM_12));
    /* SRIE,PIE1,PIE2,CRCE */
    ExpectMask = ExpectMask | ((uint32)HSSL_FLAG_CFG << (uint32)HSSL_NUM_22);
    if ((HSSL_Reg[id]->MFLAGS.U & ExpectMask) != 0U)
    {
        RetVal = E_NOT_OK ;
    }
    else
    {
        RetVal = E_OK;
    }

    return RetVal;
}

/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_lPollForSlaveExpectFlags(            **
**                   const Hssl_InstanceID id)                                **
**                                                                            **
** Description     : Activates the slave in multi slave mode.                 **
**                                                                            **
** Service ID      : 0x0B                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Hssl_lPollForSlaveExpectFlags(const Hssl_InstanceID id)
{
    /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
    this MISRA rule. Union usage is required to access SFR data type and
    implement efficiently for clearing of pending service requrest in Interrupt
    control register */
    volatile Ifx_HSSL_I_ICON *CtrlRegPtr;
    /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
    this MISRA rule. Union usage is required to access SFR data type and
    implement efficiently for clearing of pending service requrest in Interrupt
    control register */
    volatile Ifx_HSSL_I_IRWA *AddRegPtr;
    /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
    this MISRA rule. Union usage is required to access SFR data type and
    implement efficiently for clearing of pending service requrest in Interrupt
    control register */
    const volatile Ifx_HSSL_I_IRD *ReadDataRegPtr;
    volatile uint32 SlaveExpectFlags = 0xFFFFFFFFU;
    Std_ReturnType RetVal =E_NOT_OK;
    Hssl_ChannelType Channel;
    Channel.Number = 0U;
    Channel.Timeout = HSSL_TIMEOUT;
    Hssl_ChStateType *ChStateTypePtr= NULL_PTR;

#if (HSSL0_CONFIGURRED == STD_ON)
    if (id == HSSL0)
    {
        ChStateTypePtr = Hssl0ChState;
    }
#endif
#if (HSSL1_CONFIGURRED == STD_ON)
    if (id == HSSL1)
    {
        ChStateTypePtr = Hssl1ChState;
    }
#endif

    /* Enter SchM section to prevent concurrent access */

        SchM_Enter_Hssl_ChannelStatusLock();
        if ( ChStateTypePtr[Channel.Number] != HSSL_COMMAND_IN_PROGRESS)
        {
            /* set the channel state to "HSSL_COMMAND_IN_PROGRESS" */
            ChStateTypePtr[Channel.Number]  = HSSL_COMMAND_IN_PROGRESS;
            RetVal = E_OK;
        }
        else
        {
            RetVal = E_NOT_OK;
        }
        /* Enter SchM */
        if (RetVal == E_OK)
        {
            CtrlRegPtr = (&HSSL_Reg[id]->I[Channel.Number].ICON);
            AddRegPtr = (&HSSL_Reg[id]->I[Channel.Number].IRWA);
            ReadDataRegPtr = (&HSSL_Reg[id]->I[Channel.Number].IRD);
            /* Wait untill all the slave operations are done */
            while (SlaveExpectFlags != 0U)
            {
                if(CtrlRegPtr->B.BSY == 0U)
                {
                    HsslDeactivateSlaveAPI[id] = 1U;
                    /* Write data size in ICONx */
                    CtrlRegPtr->B.DATLEN = (uint8)HSSL_DATA_SIZE_32BIT;
                    /* Write Time Out Value in ICONx */
                    CtrlRegPtr->B.TOREL  = (uint8)Channel.Timeout;
                    /* Write ICONx.RWT with 0x10 Write Frame */
                    CtrlRegPtr->B.RWT    = HSSL_READ_FRAME;
                    /* Write IRWAx register with Address */
                    /* MISRA2012_RULE_11_6_JUSTIFICATION:The address of the
                    buffer pointer is stores in a local variable to be comapred
                    against 0-NULL.There are no other operation performed,hence
                    this convesion does not cause any issue */
                    /* MISRA2012_RULE_11_4_JUSTIFICATION:The address of the
                    buffer pointer is stores in a local variable to be comapred
                    against 0-NULL.There are no other operation performed,hence
                    this convesion does not cause any issue */
                    AddRegPtr->U = (uint32)&HSSL_Reg[id]->QFLAGS;
                    /* wait till the read command completes */
                    /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable
                      Channel is used inside Hssl_lReadRply() to
                     read the values. The address is not used beyond the context of the
                     API, hence it is not an issue*/
                    RetVal = Hssl_lReadRply(id, &Channel);
                    if(RetVal == E_OK)
                    {
                        SlaveExpectFlags = ((ReadDataRegPtr->U) & 0x80FF0000U);
                    }
                    else
                    {
                        break;
                    }
                }
            }
            ChStateTypePtr[Channel.Number]  = HSSL_COMMAND_COMPLETED;
        }
    return RetVal;
}
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : void Hssl_lPollForMasterExpectFlags(                     **
**                       const Hssl_InstanceID id)                            **
**                                                                            **
** Description     : Activates the slave in multi slave mode.                 **
**                                                                            **
** Service ID      : 0x0B                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
static void Hssl_lPollForMasterExpectFlags(const Hssl_InstanceID id)
{
    volatile uint32 Qflags;
    /*Read the Request Flag register*/
    Qflags = HSSL_Reg[id]->QFLAGS.U;

    /* Check Ix and Ex signals to check if any request is pending */
    do
    {
        Qflags = HSSL_Reg[id]->QFLAGS.U;
    }while ((Qflags & 0x80FF0000U) !=0U);
}
#endif
#endif
/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/
#if (HSSL_DEV_ERROR_DETECT == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : LOCAL_INLINE uint32 Hssl_lInitCallVerify(                **
                                        const Hssl_InstanceID id,             **
                                        const uint8 ServiceId)                **
**                                                                            **
** Description     : Local function :Service to verify whether Init has been  **
**                     called or report DET error                             **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   ServiceId : API Service Id number                        **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Error - Informs whether error is found or not            **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Hssl_lInitCallVerify(const Hssl_InstanceID id,\
                                        const uint8 ServiceId)
{
    uint8 ErrorFlag;
    ErrorFlag = HSSL_ERR_NOT_FOUND;

    /* Verify whether Init had been called */
    if (Hssl_DriverState[id] !=  HSSL_DRIVER_INITIALIZED)
    {
        Det_ReportError(
            HSSL_MODULE_ID,
            (uint8)id,
            ServiceId,
            HSSL_E_NOT_INITIALIZED
        );/* End of report to  DET */
        ErrorFlag = HSSL_ERR_FOUND;
    }
    return (ErrorFlag);
}/* End of Hssl_lInitCallVerify() function */
#endif  /*HSSL_DEV_ERROR_DETECT == STD_ON*/

#if (HSSL_DEV_ERROR_DETECT == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : LOCAL_INLINE uint32 Hssl_lChannelVerify                  **
**                    (const Hssl_InstanceID id,                              **
**                      const uint8 ChannelNumber, const uint8 ServiceId)     **
**                                                                            **
** Description     : Local function :Service to verify whether Channel is     **
**                     correct or report DET error                            **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   ServiceId : API Service Id number                        **
**                   ChannelNumber : Channel number                           **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Error - Informs whether error is found or not            **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Hssl_lChannelVerify(const Hssl_InstanceID id,\
                                       const uint8 ChannelNumber,\
                                       const uint8 ServiceId)
{
    uint8 ErrorFlag;
    ErrorFlag = HSSL_ERR_NOT_FOUND;

    /* Verify Channel Number */
    if (ChannelNumber >= HSSL_CHANNEL_INVALID)
    {
        Det_ReportError(HSSL_MODULE_ID,(uint8)id,
                        ServiceId,HSSL_E_INV_PARAM);

        ErrorFlag = HSSL_ERR_FOUND;
    }
    return (ErrorFlag);
}/* End of Hssl_lChannelVerify() function */
#endif

#if (HSSL_DEV_ERROR_DETECT == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : LOCAL_INLINE uint32 Hssl_ldataSizeVerify                 **
**                    (const Hssl_InstanceID id,                              **
                        const uint16 DataSize, const uint8 ServiceId)         **
**                                                                            **
** Description     : Local function :Service to verify whether data size is   **
**                     correct or report DET error                            **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   ServiceId - API Service Id number                        **
**                   DataSize - size of the data                              **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Error - Informs whether error is found or not            **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Hssl_ldataSizeVerify(const Hssl_InstanceID id,\
                                   const uint16 DataSize, const uint8 ServiceId)
{
    uint8 ErrorFlag;
    ErrorFlag = HSSL_ERR_NOT_FOUND;
    /* Verify whether Init had been called */

    /* Data size can be 8 , 16 or  32 bit only */
    if (DataSize >= HSSL_MAX_DATA_SIZE)
    {
        Det_ReportError(HSSL_MODULE_ID,(uint8)id,
                        ServiceId,HSSL_E_INV_PARAM);

        ErrorFlag = HSSL_ERR_FOUND;
    }
    return (ErrorFlag);
}/* End of Hssl_ldataSizeVerify() function */
#endif

#if (HSSL_DEV_ERROR_DETECT == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : LOCAL_INLINE uint32 Hssl_lRunModeVerify                  **
**                    (const Hssl_InstanceID id, const uint8 ServiceId)       **
**                                                                            **
** Description     : Local function :Service to verify whether the interface  **
**                     mode is correct or report DET error                    **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   ServiceId - API Service Id number                        **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Error - Informs whether error is found or not            **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Hssl_lRunModeVerify(const Hssl_InstanceID id,\
                                       const uint8 ServiceId)
{
    uint8 ErrorFlag;
    ErrorFlag = HSSL_ERR_NOT_FOUND;

    /* Verify if driver in RUN Mode*/
    if (Hssl_InterfaceMode[id] !=  HSSL_MODE_RUN)
    {
        Det_ReportError(
            HSSL_MODULE_ID,
            (uint8)id,
            ServiceId,
            HSSL_E_INV_MODE
        );
        ErrorFlag = HSSL_ERR_FOUND;
    }
    return (ErrorFlag);
}/* End of Hssl_lRunModeVerify() function */
#endif

#if (HSSL_DEV_ERROR_DETECT == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : LOCAL_INLINE uint32 Hssl_lInstanceIDVerify               **
**                    (const Hssl_InstanceID id, const uint8 ServiceId)       **
**                                                                            **
** Description     : Local function :Service to verify whether the interface  **
**                     mode is correct or report DET error                    **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   ServiceId - API Service Id number                        **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Error - Informs whether error is found or not            **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Hssl_lInstanceIDVerify(const Hssl_InstanceID id,\
        const uint8 ServiceId)
{
    uint8 ErrorFlag;
    ErrorFlag = HSSL_ERR_NOT_FOUND;

    /* Verify if ID is valid*/
#if (HSSL_NUM_INSTANCES_CONFIGURRED == 2u)
    /* MISRA2012_RULE_14_3_JUSTIFICATION:The maximum number for instance is two
     i.e, HSSL0 and HSSL1 hence this convesion does not cause any issue */
    if (id > HSSL1)
    {
        ErrorFlag = HSSL_ERR_FOUND;
        Det_ReportError(HSSL_MODULE_ID,(uint8)id,ServiceId,\
                        HSSL_E_INSTANCE_NOT_CONFIGURED);
    }
#else
#if (HSSL0_CONFIGURRED == STD_ON)
    if (HSSL0 != id)
    {
        ErrorFlag = HSSL_ERR_FOUND;
        Det_ReportError(HSSL_MODULE_ID,(uint8)id,ServiceId,\
                        HSSL_E_INSTANCE_NOT_CONFIGURED);
    }
#endif
#if (HSSL1_CONFIGURRED == STD_ON)
    if (HSSL1 != id)
    {
        ErrorFlag = HSSL_ERR_FOUND;
        Det_ReportError(HSSL_MODULE_ID,(uint8)id,ServiceId,\
                        HSSL_E_INSTANCE_NOT_CONFIGURED);
    }
#endif
#endif
    return (ErrorFlag);
}/* End of Hssl_lInstanceIDVerify() function */
#endif
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : static Std_ReturnType Hssl_lSetTargetAddress             **
**                     (const Hssl_InstanceID id, const uint32 *StartAddress, **
**                      const uint32 DataSize)                                **
**                                                                            **
** Description     : Local function to do direct write transfer.              **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non reentrant                                            **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   StartAddress : Specifies the address to be written to    **
**                                  stream registers                          **
**                   DataSize: Number of stream frames to transmit            **
**                               (Each frame length: 256 bit)                 **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Hssl_lSetTargetAddress(const Hssl_InstanceID id,\
        const uint32 *StartAddress, const uint32 DataSize)
{
    uint32 DataBuffer;
    uint32 DataAddr, MflagsSetAddr, FcAddr;
    Hssl_DataTemplateType WriteData;
    Std_ReturnType Error;
    Hssl_ChannelType Channel;

    Channel.Number = 0U;
    Channel.Timeout = HSSL_TIMEOUT;
    /* MISRA2012_RULE_11_6_JUSTIFICATION:The address of the buffer pointer is
    stores in a local variable to be comapred against 0-NULL.
    There are no other operation performed, hence this convesion
    does not cause any issue */
    /* MISRA2012_RULE_11_4_JUSTIFICATION:The address of the buffer pointer is
    stores in a local variable to be comapred against 0-NULL.
    There are no other operation performed, hence this convesion
    does not cause any issue */
    DataBuffer = (uint32)StartAddress;
    /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable DataBuffer
           is used inside Hssl_lSingleFrameWrite() to
         read the values. The address is not used beyond the context of the
         API, hence it is not an issue*/
    WriteData.Data = &DataBuffer ;
    if (HSSL0 == id)
    {
        DataAddr =  HSSL0_DATA_ADDR;
        MflagsSetAddr = HSSL0_MFLAGSSET_ADDR;
        FcAddr = HSSL0_FC_ADDR;
    }
    else
    {
        DataAddr =  HSSL1_DATA_ADDR;
        MflagsSetAddr = HSSL1_MFLAGSSET_ADDR;
        FcAddr = HSSL1_FC_ADDR;
    }
    /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable DataAddr
           is used inside Hssl_lSingleFrameWrite() to
         read the values. The address is not used beyond the context of the
         API, hence it is not an issue*/
    WriteData.Address = &DataAddr;
    /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable WriteData
           is used inside Hssl_lSingleFrameWrite() to
         read the values. The address is not used beyond the context of the
         API, hence it is not an issue*/
    Error = Hssl_lSingleFrameWrite(id,&WriteData,HSSL_DATA_SIZE_32BIT,\
                                   &Channel,0U, &HsslStartStreamAPI[id]);

    if (E_OK == Error)
    {
      /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable
      Channel is used inside Hssl_lWriteAck() to
      read the values. The address is not used beyond the context of the
      API, hence it is not an issue*/
        Error = Hssl_lWriteAck(id, &Channel);
        if (E_OK == Error)
        {
            DataAddr = (DataAddr + HSSL_NUM_4);
       /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable DataAddr
              is used inside Hssl_lSingleFrameWrite() to
            read the values. The address is not used beyond the context of the
            API, hence it is not an issue*/
            WriteData.Address = &DataAddr;
/* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable WriteData
              is used inside Hssl_lSingleFrameWrite() to
            read the values. The address is not used beyond the context of the
            API, hence it is not an issue*/
            Error = Hssl_lSingleFrameWrite(id,&WriteData,\
                       HSSL_DATA_SIZE_32BIT,&Channel,0U,&HsslStartStreamAPI[id]);
        }
    }
    if (E_OK == Error)
    {
      /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable
      Channel is used inside Hssl_lWriteAck() to
      read the values. The address is not used beyond the context of the
      API, hence it is not an issue*/
        Error = Hssl_lWriteAck(id, &Channel);
        if (E_OK == Error)
        {
            DataBuffer = (uint32)DataSize;
/* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable DataBuffer
              is used inside Hssl_lSingleFrameWrite() to
            read the values. The address is not used beyond the context of the
            API, hence it is not an issue*/
            WriteData.Data = &DataBuffer ;
/* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable DataAddr
              is used inside Hssl_lSingleFrameWrite() to
            read the values. The address is not used beyond the context of the
            API, hence it is not an issue*/
            WriteData.Address = &FcAddr;
/* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable WriteData
              is used inside Hssl_lSingleFrameWrite() to
            read the values. The address is not used beyond the context of the
            API, hence it is not an issue*/
            Error = Hssl_lSingleFrameWrite(id,&WriteData,\
                      HSSL_DATA_SIZE_32BIT,&Channel,0U, &HsslStartStreamAPI[id]);
        }
    }
    if (E_OK == Error)
    {
      /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable
      Channel is used inside Hssl_lWriteAck() to
      read the values. The address is not used beyond the context of the
      API, hence it is not an issue*/
        Error = Hssl_lWriteAck(id, &Channel);
        if (E_OK == Error)
        {
            DataBuffer = (uint32)0x10000000u;
/* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable DataBuffer
              is used inside Hssl_lSingleFrameWrite() to
            read the values. The address is not used beyond the context of the
            API, hence it is not an issue*/
            WriteData.Data = &DataBuffer;
/* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable DataAddr
              is used inside Hssl_lSingleFrameWrite() to
            read the values. The address is not used beyond the context of the
            API, hence it is not an issue*/
            WriteData.Address = &MflagsSetAddr;
/* MISRA2012_RULE_1_3_JUSTIFICATION: Address of auto variable WriteData
              is used inside Hssl_lSingleFrameWrite() to
            read the values. The address is not used beyond the context of the
            API, hence it is not an issue*/
            Error = Hssl_lSingleFrameWrite(id,&WriteData,\
                       HSSL_DATA_SIZE_32BIT,&Channel,0U,&HsslStartStreamAPI[id]);
        }
    }
    return(Error) ;
}
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : static Std_ReturnType Hssl_lSingleFrameWrite             **
**                     (const Hssl_InstanceID id,                             **
**                      const Hssl_DataTemplateType *WriteData,               **
**                     const uint16 DataSize,                                 ** 
**                     const Hssl_ChannelType *const Channel,                 **
**                     const uint16 InjectedError,                            **
**                     uint32 *const NotificationDisable)                     **
**                                                                            **
** Description     : Local function to do direct write transfer.              **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : reentrant                                                **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
                     WriteData : Pointer to Hssl_DataTemplateType structure   **
**                    which includes write Address and Data to be written.    **
**                    DataSize:: Size of data to be written.                  **
**                    Channel:: HSSL Channel to use.                          **
**                    InjectedError: injected error (if required)             **
**                                                                            **
** Parameters (out): NotificationDisable: Notification enable or disable      **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Hssl_lSingleFrameWrite (
    const Hssl_InstanceID id,
    const Hssl_DataTemplateType * WriteData,
    const uint16 DataSize, const Hssl_ChannelType *const Channel,
    const uint16 InjectedError, uint32 *const NotificationDisable)
{
    Std_ReturnType RetVal = E_NOT_OK;
    /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
    this MISRA rule. Union usage is required to access SFR data type and
    implement efficiently for clearing of pending service requrest in Interrupt
    control register */
    volatile Ifx_HSSL_I_ICON *CtrlRegPtr;
    /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
    this MISRA rule. Union usage is required to access SFR data type and
    implement efficiently for clearing of pending service requrest in Interrupt
    control register */
    volatile Ifx_HSSL_I_IWD *WriteDataRegPtr;
    /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
    this MISRA rule. Union usage is required to access SFR data type and
    implement efficiently for clearing of pending service requrest in Interrupt
    control register */
    volatile Ifx_HSSL_I_IRWA *AddRegPtr;
    Hssl_ChStateType *ChStateTypePtr= NULL_PTR;

    CtrlRegPtr = (&HSSL_Reg[id]->I[Channel->Number].ICON);
    WriteDataRegPtr = (&HSSL_Reg[id]->I[Channel->Number].IWD);
    AddRegPtr = (&HSSL_Reg[id]->I[Channel->Number].IRWA);

#if (HSSL0_CONFIGURRED == STD_ON)
    if (id == HSSL0)
    {
        ChStateTypePtr = Hssl0ChState;
    }
#endif
#if (HSSL1_CONFIGURRED == STD_ON)
    if (id == HSSL1)
    {
        ChStateTypePtr = Hssl1ChState;
    }
#endif
    /* Enter SchM section to prevent concurrent access */

        SchM_Enter_Hssl_ChannelStatusLock();
        if ( ChStateTypePtr[Channel->Number] != HSSL_COMMAND_IN_PROGRESS)
        {
            /* set the channel state to "HSSL_COMMAND_IN_PROGRESS" */
            ChStateTypePtr[Channel->Number]  = HSSL_COMMAND_IN_PROGRESS;
            RetVal = E_OK;
        }
        else
        {
            RetVal = E_NOT_OK;
        }
        /* Enter SchM */
        SchM_Exit_Hssl_ChannelStatusLock();
        if (RetVal == E_OK)
        {
            /*  Read ICONx.BSY bit to check if Channel is Busy or Available */
            if (CtrlRegPtr->B.BSY == 0U)
            {
                /* If injected error is needed set it in CRC register */
                if (InjectedError != 0U)
                {
                HSSL_RUNTIME_WRITEENDINITPROTREG(
                &(HSSL_Reg[id]->CRC),
                ((uint32)InjectedError | (1UL<<HSSL_CRC_EN_SHIFT)));
                }

                if (NotificationDisable != NULL_PTR)
                {
                    *NotificationDisable=1U;
                }
                /* Write data size in ICONx */
                CtrlRegPtr->B.DATLEN = (uint8)DataSize;
                /* Write Time Out Value in ICONx */
                CtrlRegPtr->B.TOREL  = HSSL_TIMEOUT;
                /* Write ICONx.RWT with 0x10 Write Frame */
                CtrlRegPtr->B.RWT    = HSSL_WRITE_FRAME;
                /* Write IWDx register with the data */
                WriteDataRegPtr->U =*WriteData->Data;
                /* Write IRWAx register with Address */
                AddRegPtr->U = *WriteData->Address;
            }
            else
            {
                RetVal=E_NOT_OK;
            }
            /* Set the channel status to HSSL_COMMAND_COMPLETED */
            ChStateTypePtr[Channel->Number]  = HSSL_COMMAND_COMPLETED;
        }

    return(RetVal) ;
}
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : static Std_ReturnType Hssl_lWriteAck                     **
**               (const Hssl_InstanceID id,                                   **
**                   const Hssl_ChannelType *const Channel)                   **
**                                                                            **
** Description     : Write acknowledge function, should be called when a      **
**                   write acknowledge is received by the module, or a timeout**
**                   occurs during a write command.                           **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non reentrant                                            **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   Channel: HSSL Channel to use.                            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Hssl_lWriteAck(const Hssl_InstanceID id,
                                     const Hssl_ChannelType *const Channel)
{
    volatile uint32 Qflags;
    uint32 ExpectMask ;
    Std_ReturnType RetVal;

    /*Read the Request Flag register*/
    Qflags = HSSL_Reg[id]->QFLAGS.U;

    /* Check Ix and Ex signals to check if any request is pending */
    do
    {
        Qflags = HSSL_Reg[id]->QFLAGS.U;
    }while ((Qflags & (((uint32)HSSL_WRITE_PENDING
          << ((uint32)HSSL_NUM_16 +(Channel->Number * (uint32)HSSL_CHANNEL_CFG)))
          |((uint32)1U << Channel->Number))) != 0U);

    ExpectMask = ((uint32)1U << Channel->Number);        /* Not ACK Error */
    /* Transcation Tag Error */
    ExpectMask = ExpectMask |
                 ((uint32)1U << (Channel->Number + (uint32)HSSL_NUM_4));
    /*TIMEOUT Error*/
    ExpectMask = ExpectMask |
                 ((uint32)1U << (Channel->Number + (uint32)HSSL_NUM_8));
    ExpectMask = ExpectMask |
                 ((uint32)1U << (Channel->Number + (uint32)HSSL_NUM_12));
    /* SRIE,PIE1,PIE2,CRCE */
    ExpectMask = ExpectMask | ((uint32)HSSL_FLAG_CFG << (uint32)HSSL_NUM_22);
    if ((HSSL_Reg[id]->MFLAGS.U & ExpectMask) != 0U)
    {
        RetVal = E_NOT_OK ;
    }
    else
    {
        RetVal = E_OK;
    }

    return RetVal;
}
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : static void HSCT_lInit(const uint32 id)                  **
**                                                                            **
** Description     : HSCT initialisation should be done before hssl           **
**                   initialisation                                           **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non reentrant                                            **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Hsct_lInit(const uint32 id)
{
    uint32 TimeOutCounter = 0xFFFFU;
    uint8 RetVal = E_OK;
    /* Initialize HSCT module for master/slave */
    HSCT_Reg[id]->INIT.B.IFM  = HSSL_INTERFACE_MODE;
    HSCT_Reg[id]->INIT.B.SYS_CLK_EN  = HSSL_SYSTEM_CLOCK;
    HSCT_Reg[id]->INIT.B.SRCF  = (uint8)HSSL_RefrenceClock[id];
    HSCT_Reg[id]->INIT.B.SSCF  =(uint8)HSSL_SysClkDiv[id];
    /* Peripheral power on */
    HSCT_Reg[id]->CONFIGPHY.B.PON  = (uint8)HSSL_PERIPHERAL_ON;
    /* Tx speed */
    HSCT_Reg[id]->IFCTRL.B.MTXSPEED = (uint8)HSSL_MTXSpeed[id];
    /* Rx speed */
    HSCT_Reg[id]->IFCTRL.B.MRXSPEED = (uint8)HSSL_MRXSpeed[id];
    HSCT_Reg[id]->DISABLE.U = 0U;

    /* wait until pll is locked */
    while ((HSCT_Reg[id]->STATPHY.B.PLOCK == 0U) && (TimeOutCounter != 0U))
    {
        TimeOutCounter--;
    }

    if ((HSCT_Reg[id]->STATPHY.B.PLOCK == 0U) && (TimeOutCounter == 0U))
    {
        RetVal = E_NOT_OK;
    }
    /* 5. Enable slave reception */
    /* write the command into the register */
    HSCT_Reg[id]->IFCTRL.B.IFCVS = 49;
    /* activate the command */
    HSCT_Reg[id]->IFCTRL.B.SIFCV = 1;

    return RetVal;
}
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : static void Hssl_lResetKernels(const uint32 id,          **
**                                     const uint8 ApiType)                   **
**                                                                            **
** Description     : local function to reset all available kernels            **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non reentrant                                            **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   ApiId : Specifies the called function type(INIT API or   **
**                           RUNTIME API)                                     **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
static void Hssl_lResetKernels(const uint32 id, const uint8 ApiType)
{
    volatile uint32 Readback;
    uint32 WaitCount;

    /* Set request to reset the HSCT Kernel */
    if (ApiType == HSSL_INIT_API)
    {
      HSSL_INIT_DEINIT_WRITEENDINITPROTREG(&(HSCT_Reg[id]->KRST0),1U);
      Readback = HSCT_Reg[id]->KRST0.U;

      HSSL_INIT_DEINIT_WRITEENDINITPROTREG(&(HSCT_Reg[id]->KRST1),1U);
      Readback = HSCT_Reg[id]->KRST1.U;

      WaitCount = (uint32)HSSL_KERNEL_RESET_WAIT_COUNT;
      do
      {
          WaitCount--;
      }
      while ((HSCT_Reg[id]->KRST0.B.RSTSTAT != 1U)&&(WaitCount > 0U));

      /* Clear the HSCT Kernel Reset Flag */
      HSSL_INIT_DEINIT_WRITEENDINITPROTREG(&(HSCT_Reg[id]->KRSTCLR),1U);
      Readback = HSCT_Reg[id]->KRSTCLR.U;

      /* Set request to reset the HSSL Kernel */
      HSSL_INIT_DEINIT_WRITEENDINITPROTREG(&(HSSL_Reg[id]->KRST0),1U);
      Readback = HSSL_Reg[id]->KRST0.U;

      HSSL_INIT_DEINIT_WRITEENDINITPROTREG(&(HSSL_Reg[id]->KRST1),1U);
      Readback = HSSL_Reg[id]->KRST1.U;

      WaitCount = (uint32)HSSL_KERNEL_RESET_WAIT_COUNT;
      do
      {
          WaitCount--;
      }
      while ((HSSL_Reg[id]->KRST0.B.RSTSTAT != 1U)&&(WaitCount > 0U));

      /* Clear the HSSL Kernel Reset Flag */
      HSSL_INIT_DEINIT_WRITEENDINITPROTREG(&(HSSL_Reg[id]->KRSTCLR),1U);
      Readback = HSSL_Reg[id]->KRSTCLR.U;
    }
    else
    {
      HSSL_RUNTIME_WRITEENDINITPROTREG(&(HSCT_Reg[id]->KRST0),1U);
      Readback = HSCT_Reg[id]->KRST0.U;

      HSSL_RUNTIME_WRITEENDINITPROTREG(&(HSCT_Reg[id]->KRST1),1U);
      Readback = HSCT_Reg[id]->KRST1.U;

      WaitCount = (uint32)HSSL_KERNEL_RESET_WAIT_COUNT;
      do
      {
          WaitCount--;
      }
      while ((HSCT_Reg[id]->KRST0.B.RSTSTAT != 1U)&&(WaitCount > 0U));

      /* Clear the HSCT Kernel Reset Flag */
      HSSL_RUNTIME_WRITEENDINITPROTREG(&(HSCT_Reg[id]->KRSTCLR),1U);
      Readback = HSCT_Reg[id]->KRSTCLR.U;

      /* Set request to reset the HSSL Kernel */
      HSSL_RUNTIME_WRITEENDINITPROTREG(&(HSSL_Reg[id]->KRST0),1U);
      Readback = HSSL_Reg[id]->KRST0.U;

      HSSL_RUNTIME_WRITEENDINITPROTREG(&(HSSL_Reg[id]->KRST1),1U);
      Readback = HSSL_Reg[id]->KRST1.U;

      WaitCount = (uint32)HSSL_KERNEL_RESET_WAIT_COUNT;
      do
      {
          WaitCount--;
      }
      while ((HSSL_Reg[id]->KRST0.B.RSTSTAT != 1U)&&(WaitCount > 0U));

      /* Clear the HSSL Kernel Reset Flag */
      HSSL_RUNTIME_WRITEENDINITPROTREG(&(HSSL_Reg[id]->KRSTCLR),1U);
      Readback = HSSL_Reg[id]->KRSTCLR.U;
    }
    UNUSED_PARAMETER(Readback);
}
/*
 CYCLOMATIC_Hssl_IsrCOK_JUSTIFICATION: This is an ISR function where it calls
 user notification function with different events based on some conditions.
 For readability purpose, all conditions are kept together in the same function.
*/
/*******************************************************************************
** Syntax          : void Hssl_IsrCOK(const Hssl_InstanceID id, uint8 Channel)**
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1)        **
**                   Channel: HSSL Channel to use                             **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value    : none                                                     **
**                                                                            **
** Description     : ISR get called error free frame response                 **
                    triggers a COK interrupt                                  **
*******************************************************************************/
void Hssl_IsrCOK(const Hssl_InstanceID id, uint8 Channel)
{
const Hssl_UserNotify *Notification = NULL_PTR;
#if (HSSL0_CONFIGURRED == STD_ON)
    if (id == HSSL0)
    {
      Notification = &Hssl0_WriteNotificationFunc[0];
    }
#endif
#if (HSSL1_CONFIGURRED == STD_ON)
    if (id == HSSL1)
    {
        Notification = &Hssl1_WriteNotificationFunc[0];
    }
#endif
    if(Channel == HSSL_CH0)
    {
        /* Skip the user notification, while activating slave */
        if ((HsslActivateSlaveAPI[id] != 1U) && (HsslStartStreamAPI[id] !=1U)
               && (HsslDeactivateSlaveAPI[id] != 1U))
        {
            if (Notification[Channel] != NULL_PTR)
            {
                (Notification[Channel])((uint32)HSSL_WRITE_COMMAND_COMPLETED);
            }
        }
        else
        {
            if (HsslActivateSlaveAPI[id] != 0U)
            {
                HsslActivateSlaveAPI[id] = 0U;
            }
            if (HsslStartStreamAPI[id] != 0U)
            {
                HsslStartStreamAPI[id] = 0U;
            }
        }
    }
    if( (Channel == HSSL_CH1) || (Channel == HSSL_CH3))
    {
        if (Notification[Channel] != NULL_PTR)
         {
                (Notification[Channel])((uint32)HSSL_WRITE_COMMAND_COMPLETED);
         }
    }
    if( Channel == HSSL_CH2)
    {
        if (Notification[Channel] != NULL_PTR)
        {
            if (HSSL_Ch2Mode[id] == HSSL_CH2_STREAMING)
            {
                (Notification[Channel])((uint32)HSSL_STREAM_BLOCK_TRANSMITTED);
            }
            else
            {
                (Notification[Channel])((uint32)HSSL_WRITE_COMMAND_COMPLETED);
            }
        }
    }
}
/*******************************************************************************
** Syntax          : void Hssl_IsrRDI(const Hssl_InstanceID id,uint8 Channel) **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1)        **
**                   Channel: HSSL Channel to use                             **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value    : none                                                     **
**                                                                            **
** Description     : ISR get called read frame response is received           **
*******************************************************************************/
void Hssl_IsrRDI(const Hssl_InstanceID id,uint8 Channel)
{
    /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
    this MISRA rule. Union usage is required to access SFR data type and
    implement efficiently for clearing of pending service requrest in Interrupt
    control register */
volatile const Ifx_HSSL_I_IRD *ReadDataRegPtr = (&HSSL_Reg[id]->I[Channel].IRD);
    const uint32 *HsslReadDataBuffer = NULL_PTR;
    uint32 *buffer;
const Hssl_UserNotify *Notification= NULL_PTR;

#if (HSSL0_CONFIGURRED == STD_ON)
    if (id == HSSL0)
    {
        Notification = &Hssl0_ReadNotificationFunc[0];
        /* MISRA2012_RULE_1_3_JUSTIFICATION: Passing local to fetch
        * data - Hssl0ReadDataBuffer - agreed violation */
        /* MISRA2012_RULE_11_3_JUSTIFICATION: Hssl0ReadDataBuffer
        base address access */
        HsslReadDataBuffer = (uint32 *)&Hssl0ReadDataBuffer[Channel];
    }
#endif
#if (HSSL1_CONFIGURRED == STD_ON)
    if (id == HSSL1)
    {
        Notification = &Hssl1_ReadNotificationFunc[0];
        /* MISRA2012_RULE_1_3_JUSTIFICATION: Passing local to fetch
        * data - Hssl1ReadDataBuffer - agreed violation */
        /* MISRA2012_RULE_11_3_JUSTIFICATION: Hssl1ReadDataBuffer
        base address access */
        HsslReadDataBuffer =(uint32 *)&Hssl1ReadDataBuffer[Channel];
    }
#endif

    if( Channel == HSSL_CH0)
    {
        if (HsslDeactivateSlaveAPI[id] != 1U)
        {
            if (HsslReadDataBuffer != NULL_PTR)
            {
              /* read the data from RDI register and update the buffer */
       /* MISRA2012_RULE_11_6_JUSTIFICATION:The address of the buffer pointer is
       stores in a local variable to be comapred against 0-NULL.
       There are no other operation performed, hence this convesion
       does not cause any issue */
       /* MISRA2012_RULE_11_4_JUSTIFICATION:The address of the buffer pointer is
       stores in a local variable to be comapred against 0-NULL.
       There are no other operation performed, hence this convesion
       does not cause any issue */
               buffer = (uint32*)*HsslReadDataBuffer;
               *buffer = ReadDataRegPtr->U;
            }
            if (Notification[Channel] != NULL_PTR)
            {
                (Notification[Channel])((uint32)HSSL_READ_COMMAND_COMPLETED);
            }
        }
        else
        {
            HsslDeactivateSlaveAPI[id] = 0U;
        }
    }
    if((Channel == HSSL_CH1) ||( Channel == HSSL_CH2) || (Channel == HSSL_CH3))
    {
        /* read the data from RDI register and update the buffer */
       if (HsslReadDataBuffer != NULL_PTR)
       {
         /* MISRA2012_RULE_11_6_JUSTIFICATION:The address of the buffer pointer is
       stores in a local variable to be comapred against 0-NULL.
       There are no other operation performed, hence this convesion
       does not cause any issue */
       /* MISRA2012_RULE_11_4_JUSTIFICATION:The address of the buffer pointer is
       stores in a local variable to be comapred against 0-NULL.
       There are no other operation performed, hence this convesion
       does not cause any issue */
        buffer = (uint32*)*HsslReadDataBuffer;
        *buffer = ReadDataRegPtr->U;
       }
        if (Notification[Channel] != NULL_PTR)
        {
            (Notification[Channel])((uint32)HSSL_READ_COMMAND_COMPLETED);
        }
    }
}
/*******************************************************************************
** Syntax          :void Hssl_IsrError(const Hssl_InstanceID id,uint8 Channel)**
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1)        **
**                   Channel: HSSL Channel to use                             **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value    : none                                                     **
**                                                                            **
** Description     : ISR get called error intrrupt is triggered               **
*******************************************************************************/
void Hssl_IsrError(const Hssl_InstanceID id,uint8 Channel)
{
    if( Channel == HSSL_CH0)
    {
     if ((HsslActivateSlaveAPI[id] != 1U) && (HsslDeactivateSlaveAPI[id] != 1U)
         && (HsslStartStreamAPI[id] != 1U))
        {
            Hssl_lIsrError(id,Channel);
        }
        else
        {
            if (HsslActivateSlaveAPI[id] != 0U)
            {
                HsslActivateSlaveAPI[id] = 0U;
            }
            if (HsslDeactivateSlaveAPI[id] != 0U)
            {
                HsslDeactivateSlaveAPI[id] = 0U;
            }
            if (HsslStartStreamAPI[id] != 0U)
            {
                HsslStartStreamAPI[id] = 0U;
            }
        }
    }
    if((Channel == HSSL_CH1) || (Channel == HSSL_CH2) || (Channel == HSSL_CH3))
    {
        Hssl_lIsrError(id,Channel);
    }
}
/*******************************************************************************
** Syntax          : void Hssl_IsrTrg(const Hssl_InstanceID id,uint8 Channel) **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1)        **
**                   Channel: HSSL Channel to use                             **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value    : none                                                     **
**                                                                            **
** Description     : ISR get called at target when trigger frame is aarived   **
*******************************************************************************/
void Hssl_IsrTrg(const Hssl_InstanceID id,uint8 Channel)
{
const Hssl_UserNotify *Notification = NULL_PTR;
#if (HSSL0_CONFIGURRED == STD_ON)
    if (id == HSSL0)
    {
      Notification = &Hssl0_TriggerNotificationFunc[0];
    }
#endif
#if (HSSL1_CONFIGURRED == STD_ON)
    if (id == HSSL1)
    {
        Notification = &Hssl1_TriggerNotificationFunc[0];
    }
#endif
    if(Channel == HSSL_CH0)
    {
        if (HsslActivateSlaveAPI[id] != 0U)
        {
            HsslActivateSlaveAPI[id]= 0U;
            if (Notification[Channel] != NULL_PTR)
            {
                (Notification[Channel])((uint32)HSSL_TRIGGER_COMMAND_COMPLETED);
            }
        }

    }
    if((Channel == HSSL_CH1) || (Channel == HSSL_CH3))
    {
        if (Notification[Channel] != NULL_PTR)
        {
            (Notification[Channel])((uint32)HSSL_TRIGGER_COMMAND_COMPLETED);
        }
    }
    if( Channel == HSSL_CH2)
    {
        if (Notification[Channel] != NULL_PTR)
        {
            if (HSSL_Ch2Mode[id] == HSSL_CH2_STREAMING)
            {
                (Notification[Channel])((uint32)HSSL_STREAM_BLOCK_RECEIVED);
            }
            else
            {
                (Notification[Channel])((uint32)HSSL_TRIGGER_COMMAND_COMPLETED);
            }
        }
    }
}
/*******************************************************************************
** Syntax          : void Hssl_IsrEXI(const Hssl_InstanceID id)               **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1)        **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value    : none                                                     **
**                                                                            **
** Description     : ISR get called during global error                       **
*******************************************************************************/
void Hssl_IsrEXI(const Hssl_InstanceID id)
{
    const Hssl_UserNotify *Notification = NULL_PTR;
    uint32 Event = (uint32)HSSL_NO_EVENT;
#if (HSSL0_CONFIGURRED == STD_ON)
    if (id == HSSL0)
    {
      Notification = &Hssl0_EXINotificationFunc[0];
    }
#endif
#if (HSSL1_CONFIGURRED == STD_ON)
    if (id == HSSL1)
    {
        Notification = &Hssl1_EXINotificationFunc[0];
    }
#endif
    if (*Notification != NULL_PTR)
    {
        if (HSSL_Reg[id]->MFLAGS.B.SRIE != 0U)
        {
            Event = (Event | (uint32)HSSL_SRI_BUS_ERROR);
        }
        else if(HSSL_Reg[id]->MFLAGS.B.PIE1 != 0U)
        {
            Event = (Event | (uint32)HSSL_PIE1_CHANNEL_NUMBER_CODE_ERROR);
        }
        else if(HSSL_Reg[id]->MFLAGS.B.PIE2 != 0U)
        {
            Event = (Event | (uint32)HSSL_PIE2_DATA_LENGHT_ERROR);
        }
        else if(HSSL_Reg[id]->MFLAGS.B.CRCE != 0U)
        {
            Event = (Event | (uint32)HSSL_CRC_ERROR);
        }
        else
        {
            /* Do nothing*/
        }
        (*Notification)(Event);
    }
}
/*******************************************************************************
** Syntax          : static void Hssl_lIsrError(const Hssl_InstanceID id,     **
                                                const uint8 Channel)          **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1)        **
**                   Channel : Specifies the channel                          **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value    : none                                                     **
**                                                                            **
** Description     : ISR get called at target when Error frame is aarived     **
*******************************************************************************/
static void Hssl_lIsrError(const Hssl_InstanceID id, const uint8 Channel)
{
const Hssl_UserNotify *Notification =NULL_PTR;
    uint32 Event = (uint32)HSSL_NO_EVENT ;
#if (HSSL0_CONFIGURRED == STD_ON)
    if (id == HSSL0)
    {
      Notification = &Hssl0_ErrorNotificationFunc[0];
    }
#endif
#if (HSSL1_CONFIGURRED == STD_ON)
    if (id == HSSL1)
    {
        Notification = &Hssl1_ErrorNotificationFunc[0];
    }
#endif

    if (Notification[Channel] != NULL_PTR)
    {
        if (((HSSL_Reg[id]->MFLAGS.B.NACK) & (1U << Channel)) != 0U)
        {
            Event = (Event | (uint32)HSSL_ERROR_NACK);
        }
        else if(((HSSL_Reg[id]->MFLAGS.B.TTE) & (1U << Channel)) != 0U)
        {
            Event = (Event | (uint32)HSSL_ERROR_TRANSACTION_TAG);
        }
        else if(((HSSL_Reg[id]->MFLAGS.B.TIMEOUT) & (1U << Channel)) != 0U)
        {
            Event = (Event | (uint32)HSSL_ERROR_TIMEOUT);
        }
        else if(((HSSL_Reg[id]->MFLAGS.B.UNEXPECTED) & (1U << Channel)) != 0U)
        {
            Event = (Event | (uint32)HSSL_ERROR_UNEXPECTED);

        }
        else
        {
            /* Do nothing*/
        }
        (Notification[Channel])(Event);
    }
}
/*******************************************************************************
**                                                                            **
** Traceability     :                                                         **
**                                                                            **
** Syntax          : void Hssl_DmaCallout                                     **
**                   (const uint32 Channel, const Dma_EventsType Event)      **
**                                                                            **
** Service ID      : None(local API)                                          **
**                                                                            **
** Sync/Async      :                                                          **
**                                                                            **
** Reentrancy      :                                                          **
** [/cover]                                                                   **
** Parameters (in) : Channel - DMA channel number                             **
**                   Event - DMA channel event (enum)                         **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     :                                                          **
*******************************************************************************/
void Hssl_DmaCallout(const uint32 Channel, const Dma_EventsType Event)
{
    const Hssl_DMAUserNotify *Notification = NULL_PTR;
  /* Check if DMA has done the complete transfer */
  if(((uint32)Event & (uint32)DMA_EVENT_CH_TRANSFER_COMPLETE) ==
                        (uint32)DMA_EVENT_CH_TRANSFER_COMPLETE)
  {

        #if (HSSL0_CONFIGURRED == STD_ON)
        if (Channel == (uint32)HSSL0_DMA_MULTI_WRITE_CHANNEL_USED)
        {
          Hssl_DMAWriteOperationState[0] = HSSL_DMA_OPERATION_COMPLETED;
          Notification = &Hssl0_DMAWriteNotificationFunc[0];
        }
        #endif
        #if (HSSL1_CONFIGURRED == STD_ON)
        if (Channel == (uint32)HSSL1_DMA_MULTI_WRITE_CHANNEL_USED)
        {
            Hssl_DMAWriteOperationState[1] = HSSL_DMA_OPERATION_COMPLETED;
            Notification = &Hssl1_DMAWriteNotificationFunc[0];
        }
        #endif

        #if (HSSL0_CONFIGURRED == STD_ON)
        if (Channel == (uint32)HSSL0_DMA_MULTI_READ_RX_CHANNEL_USED)
        {
          Hssl_DMAReadOperationState[0] = HSSL_DMA_OPERATION_COMPLETED;
          Notification = &Hssl0_DMAReadNotificationFunc[0];
        }
        #endif
        #if (HSSL1_CONFIGURRED == STD_ON)
        if (Channel == (uint32)HSSL1_DMA_MULTI_READ_RX_CHANNEL_USED)
        {
            Hssl_DMAReadOperationState[1] = HSSL_DMA_OPERATION_COMPLETED;
            Notification = &Hssl1_DMAReadNotificationFunc[0];
        }
        #endif
        if (*Notification != NULL_PTR)
        {
            (*Notification)(Event);
        }
  }
}
/*******************************************************************************
**                                                                            **
** Traceability     :                                                         **
**                                                                            **
** Syntax          : void Hssl_DmaErrCallout                                  **
**                   (const uint32 Channel, const Dma_EventsType Event)      **
**                                                                            **
** Service ID      : None(local API)                                          **
**                                                                            **
** Sync/Async      :                                                          **
**                                                                            **
** Reentrancy      :                                                          **
** [/cover]                                                                   **
** Parameters (in) : Channel - DMA channel number                             **
**                   Event - DMA channel event (enum)                         **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     :                                                          **
*******************************************************************************/
void Hssl_DmaErrCallout (const uint32 Channel, const Dma_EventsType Event)
{
    uint32 Hssl_id = HSSL_ID_INVALID;
       /* Check if DMA has done the complete transfer */

        #if (HSSL0_CONFIGURRED == STD_ON)
        if (Channel == (uint32)HSSL0_DMA_MULTI_WRITE_CHANNEL_USED)
        {
          Hssl_id = 0U;
          Hssl_DMAWriteOperationState[0] = HSSL_DMA_OPERATION_COMPLETED;
        }
        #endif
        #if (HSSL1_CONFIGURRED == STD_ON)
        if (Channel == (uint32)HSSL1_DMA_MULTI_WRITE_CHANNEL_USED)
        {
            Hssl_id = 1U;
            Hssl_DMAWriteOperationState[1] = HSSL_DMA_OPERATION_COMPLETED;
        }
        #endif

        #if (HSSL0_CONFIGURRED == STD_ON)
        if (Channel == (uint32)HSSL0_DMA_MULTI_READ_RX_CHANNEL_USED)
        {
          Hssl_id = 0U;
          Hssl_DMAReadOperationState[0] = HSSL_DMA_OPERATION_COMPLETED;
        }
        #endif
        #if (HSSL1_CONFIGURRED == STD_ON)
        if (Channel == (uint32)HSSL1_DMA_MULTI_READ_RX_CHANNEL_USED)
        {
            Hssl_id = 1U;
            Hssl_DMAReadOperationState[1] = HSSL_DMA_OPERATION_COMPLETED;
        }
        #endif

      /* Disable DMA Tx Channel */
      Dma_ChStopTransfer((uint8)Channel);
      UNUSED_PARAMETER(Event);
      /* Reset the kernel on error */
      Hssl_lResetKernels(Hssl_id, HSSL_RUNTIME_API);
}

#define HSSL_STOP_SEC_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Hssl_MemMap.h"
