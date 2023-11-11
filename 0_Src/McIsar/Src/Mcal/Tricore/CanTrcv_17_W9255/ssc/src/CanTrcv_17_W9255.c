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
**  FILENAME     : CanTrcv_17_W9255.c                                         **
**                                                                            **
**  VERSION      : 17.0.0                                                     **
**                                                                            **
**  DATE         : 2023-05-22                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY : [cover parentID={AD599919-06CE-49e3-A96A-1D36C6E9D3EE}]    **
**                                                                            **
**  DESCRIPTION  : CanTrcv W9255 Driver source file                           **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of CanTrcv Driver,AUTOSAR Release 4.2.2  **
**                     and 4.4.0                                              **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/*[cover parentID={E2878637-D6D2-412e-A4CA-141FDE5BCC00}] File Structure
[/cover]*/
/* [cover parentID={CFC8F379-8006-46cb-A618-C485ED5235C3}] [/cover] */
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/*[cover parentID={3BE34470-088E-49cd-933E-15FB7B40AC81}]
Imported Interfaces [/cover]*/
/* Header file structure */
#include "CanTrcv_17_W9255.h"
/* CanIf.h contains prototype of CAN Interface function and CanIf Callback functions */
#include "CanIf.h"
/* Check if Autosar version is AR440 */
 #if(MCAL_AR_VERSION == MCAL_AR_440)
    /* CanIf_CanTrcv.h contains prototype of CAN Interface callback function */
    #include "CanIf_CanTrcv.h"
     /* Enable / Disable DET or Runtime error checking */
    #if (CANTRCV_17_W9255_DEV_ERROR_DETECT == STD_ON)
        #include "Det.h"
    #endif
    #if (CANTRCV_17_W9255_RUNTIME_ERROR_DETECT == STD_ON)
        #include "Mcal_Wrapper.h"
    #endif
#else
    /* Enable / Disable DET checking */
    #if (CANTRCV_17_W9255_DEV_ERROR_DETECT == STD_ON)
        #include "Det.h"
    #endif
#endif

/* MCAL header file containing global macros, type definitions and functions
  needed by all MCAL drivers. */
#include "McalLib.h"

/* Critical section protection header file */
#include "SchM_CanTrcv_17_W9255.h"
/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/
/* Check for consistent AUTOSAR version between generated code and static code
using macro published by MCALLIB */
/* [cover parentID={F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}]
     [/cover] */
#ifndef CANTRCV_17_W9255_AR_RELEASE_MAJOR_VERSION
#error "CANTRCV_17_W9255_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

/*[cover parentID={74F4CEEA-E43E-4fd0-960E-3CC41353DE5C}] Modules version
consistency check [/cover]*/
#if (CANTRCV_17_W9255_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION)
#error "CANTRCV_17_W9255_AR_RELEASE_MAJOR_VERSION does not match. "
#endif

#ifndef CANTRCV_17_W9255_SW_MAJOR_VERSION
#error "CANTRCV_17_W9255_SW_MAJOR_VERSION is not defined. "
#endif

#ifndef CANTRCV_17_W9255_SW_MINOR_VERSION
#error "CANTRCV_17_W9255_SW_MINOR_VERSION is not defined. "
#endif

#ifndef CANTRCV_17_W9255_SW_PATCH_VERSION
#error "CANTRCV_17_W9255_SW_PATCH_VERSION is not defined. "
#endif

/*[cover parentID={74F4CEEA-E43E-4fd0-960E-3CC41353DE5C}] Modules version
consistency check [/cover]*/
#if (CANTRCV_17_W9255_SW_MAJOR_VERSION != 20U)
#error "CANTRCV_17_W9255_SW_MAJOR_VERSION does not match. "
#endif

#if (CANTRCV_17_W9255_SW_MINOR_VERSION != 25U)
#error "CANTRCV_17_W9255_SW_MINOR_VERSION does not match. "
#endif

#if (CANTRCV_17_W9255_SW_PATCH_VERSION != 0U)
#error "CANTRCV_17_W9255_SW_PATCH_VERSION does not match. "
#endif

/*
  Inter Module Checks to avoid integration of incompatible files
*/
/* [cover parentID={F33F59DE-1D95-4835-B373-BF99E331CDE7}] [/cover] */
#if (CANTRCV_17_W9255_DEV_ERROR_DETECT == STD_ON)

#ifndef DET_AR_RELEASE_MAJOR_VERSION
#error "DET_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

/* Check for consistent AUTOSAR version between generated code and static
  code using macro published by MCALLIB */
/* [cover parentID={F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}]
     [/cover] */
#if ( DET_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION )
#error "DET_AR_RELEASE_MAJOR_VERSION does not match. "
#endif

#endif
/* End Of CANTRCV_17_W9255_DEV_ERROR_DETECT */


/******************************************************************************
**                      Private Macro Definitions                            **
******************************************************************************/
 #if (CANTRCV_17_W9255_DEV_ERROR_DETECT == STD_ON)
/* CAN Transceiver Driver states */
/* CAN Transceiver Driver is NOT initialized. */
#define  CANTRCV_17_W9255_UNINIT                         ((uint8)0)
/* CAN Transceiver Driver is initialized. */
#define  CANTRCV_17_W9255_INITIALIZED                    ((uint8)1)
#endif

/* SPI error check */
#define CANTRCV_17_W9255_SPI_ERROR_CHECK                 ((uint16)(0X8000U))

/* Values to be written to the Mode control register */
/* Normal Mode */

#define  CANTRCV_17_W9255_NORMAL                         ((uint16)(0x0008U))
/* Stand By Mode */

#define  CANTRCV_17_W9255_STANDBY                        ((uint16)(0x0002U))
/* Sleep Mode */

/* Values for set and clear CANTRCV_17_W9255 registers */
#define CANTRCV_17_W9255_CLEAR_REG                       (0U)
#define CANTRCV_17_W9255_SET_REG                         (1U)

#define CANTRCV_17_W9255_PN_NOT_CONFIGURED               (0xFFU)
#if (CANTRCV_17_W9255_PN_CONFIGURED_CHANNELS > 0U)
#define CANTRCV_17_W9255_PN_COMMAND_COUNT                (10U)
#endif

/* Enable/Disable report DET */
#define CANTRCV_17_W9255_REPORT_DET                      (1U)
#define CANTRCV_17_W9255_DET_DISABLE                     (0U)

/* Bit shifting operations */
#define CANTRCV_17_W9255_SHIFT_BY_TWO                    ((uint16) (2U))
#define CANTRCV_17_W9255_SHIFT_EIGHT                     ((uint32) (8U))

/* SPI Data transfer length */
#define CANTRCV_17_W9255_DATA_LENGTH                     ((uint8)(1U))

#define CANTRCV_17_W9255_REGISTER_COUNT                  ((uint8)(4U))

/* Extract Data Field */
#define CANTRCV_17_W9255_EXTRACT_DATA_FIELD              ((uint16)(0X00FFU))
#define CANTRCV_17_W9255_EXTRACT_FOUR_BITS               ((uint16)(0x000FU))

/* Extract wake flag values */
#define CANTRCV_17_W9255_LWU_CHECK                       ((uint16)(0X0004U))
#define CANTRCV_17_W9255_WUP_CHECK                       ((uint16)(0X0002U))
#define CANTRCV_17_W9255_WUF_CHECK                       ((uint16)(0X0001U))
#define CANTRCV_17_W9255_CFGVAL_CHECK                    ((uint16)(0X0001U))
/* POR check */
#define CANTRCV_17_W9255_POR_CHECK                       ((uint16)(0X4000U))
/* SYSERR check */
#define CANTRCV_17_W9255_SYSERR_CHECK                    ((uint16)(0X0010U))

/* Transceiver registers */
#define CANTRCV_17_W9255_WRITE_REG_SWK_CTRL_1            ((uint16)(0x8501U))
#define CANTRCV_17_W9255_READ_REG_SWK_CTRL_1             ((uint16)(0x0500U))
#define CANTRCV_17_W9255_CLEAR_CFGVAL                    ((uint16)(0x8500U))
#define CANTRCV_17_W9255_DISBALE_PN                      ((uint16)(0x8604U))
#define CANTRCV_17_W9255_READ_SWK_ECNT_STAT              ((uint16)(0x1D00U))
#define CANTRCV_17_W9255_READ_SWK_STAT                   ((uint16)(0x1C00U))
#define CANTRCV_17_W9255_READ_WAKE_STAT                  ((uint16)(0x1B00U))
#define CANTRCV_17_W9255_INITIALIZE_HW_CTRL              ((uint16)(0x82E3U))
#define CANTRCV_17_W9255_READ_SWK_CTRL_2                 ((uint16)(0x0600U))
#define CANTRCV_17_W9255_WRITE_SWK_CTRL_2                ((uint16)(0x8600U))
#define CANTRCV_17_W9255_ENABLE_SWK_EN                   ((uint16)(0x0080U))
#define CANTRCV_17_W9255_DISABLE_SWK_EN                  ((uint16)(0x007FU))
#define CANTRCV_17_W9255_READ_TRANS_STAT                 ((uint16)(0x1800U))
#define CANTRCV_17_W9255_CLEAR_WAKE_STAT                 ((uint16)(0x9BF7U))
#define CANTRCV_17_W9255_CLEAR_POR                       ((uint16)(0x98FFU))
#define CANTRCV_17_W9255_READ_MODE_CTRL                  ((uint16)(0x0100U))
#define CANTRCV_17_W9255_CLEAR_CANTO_BIT                 ((uint16)(0x9C04U))
#define CANTRCV_17_W9255_CLEAR_WUF_BIT                   ((uint16)(0x9B01U))

/*****************************************************************************
**                      Private Type Definitions                            **
*****************************************************************************/

/*****************************************************************************
**                      Imported Global Constant Declaration                **
*****************************************************************************/

/*****************************************************************************
**                      Private Function Declarations                       **
*****************************************************************************/
#define CANTRCV_17_W9255_START_SEC_CODE_QM_LOCAL
/* [cover parentID={03C90BFA-850A-4b3e-9D6E-51E503B46FE9}]
    MemMap file  [/cover] */
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
    MemMap mapping for code  [/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
    MemMap mapping  [/cover] */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_W9255_MemMap.h"
static Std_ReturnType CanTrcv_17_W9255_lHardwareInit(const uint8 ChannelId,
    const Spi_SequenceType SpiSequenceUsed, const uint16 InitState);

#if (CANTRCV_17_W9255_PN_CONFIGURED_CHANNELS > 0U)
static Std_ReturnType CanTrcv_17_W9255_lHardwareInitPN
(const Spi_SequenceType SpiSequenceUsed,
 const uint8 ChannelId, const uint8 serviceid);
#endif
#if (CANTRCV_17_W9255_GENERAL_WAKE_UP_SUPPORT ==    \
CANTRCV_17_W9255_WAKE_UP_BY_INTERRUPT)
static Std_ReturnType CanTrcv_17_W9255_lCheckWakeup(const uint8 Transceiver);
#endif

LOCAL_INLINE uint16 CanTrcv_17_W9255_lGetPendWakeup(const uint8 ChannelId);

LOCAL_INLINE void CanTrcv_17_W9255_lSetPendWakeup(const uint8 ChannelId);

LOCAL_INLINE void CanTrcv_17_W9255_lClearPendWakeup(const uint8 ChannelId);

static void CanTrcv_17_W9255_ldelay(void);

static Std_ReturnType CanTrcv_17_W9255_lSetTrcvMode (const uint8 Transceiver,
    const Spi_SequenceType SpiSequenceUsed, const CanTrcv_TrcvModeType OpMode);

#if (CANTRCV_17_W9255_DEV_ERROR_DETECT == STD_ON)
static Std_ReturnType CanTrcv_17_W9255_lCheckUninitDet(const uint8 serviceId);

static Std_ReturnType CanTrcv_17_W9255_lCheckChannelId(const uint8 ChannelId,
    const uint8 serviceId);

static Std_ReturnType CanTrcv_17_W9255_lCheckModeDet
(const CanTrcv_TrcvModeType Mode, const uint8 serviceId,
 const CanTrcv_TrcvModeType OpMode);
#endif
static Std_ReturnType CanTrcv_17_W9255_lInitCheckPorSyserr
(const uint8 ChannelIndex, const uint8 serviceid);

static Std_ReturnType CanTrcv_17_W9255_lSpiRetries(
const Spi_SequenceType SpiSequenceId,
    const uint16* const Buffer, const uint8 serviceId,  const uint8 DetRaise);

static Std_ReturnType CanTrcv_17_W9255_lCheckInitWakeup
(const uint8 ChannelIndex, const uint8 Transceiver);

static Std_ReturnType CanTrcv_17_W9255_lPorSyserrCheck(const uint8 ChannelIndex,
       const uint8 serviceId, const CanTrcv_TrcvModeType OpMode);

static Std_ReturnType CanTrcv_17_W9255_lWuReasonChecks(
const uint8 ChannelIndex,
    const CanTrcv_TrcvModeType Mode, const uint8 serviceId,
    const CanTrcv_TrcvModeType OpMode);
#if (CANTRCV_17_W9255_GENERAL_WAKE_UP_SUPPORT ==    \
CANTRCV_17_W9255_WAKE_UP_BY_POLLING)
static Std_ReturnType CanTrcv_17_W9255_lPollWakeup (const uint8 Transceiver,
    const Spi_SequenceType SpiSequenceId);
#endif
static Std_ReturnType CanTrcv_17_W9255_lSpiBusyCheck(const uint8 ChannelId);
static Std_ReturnType CanTrcv_17_W9255_lReportRuntimeDetError(const uint8 DetRaise,
const uint16* const Buffer,const uint8 ApiId, const uint8 ErrorId);

#define CANTRCV_17_W9255_STOP_SEC_CODE_QM_LOCAL
/* [cover parentID={03C90BFA-850A-4b3e-9D6E-51E503B46FE9}]
    MemMap file  [/cover] */
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
    MemMap mapping for code  [/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
    MemMap mapping  [/cover] */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_W9255_MemMap.h"
/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
/*[cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
Variables Memory section as per AS
[/cover]*/
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define CANTRCV_17_W9255_START_SEC_VAR_CLEARED_QM_LOCAL_32
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_W9255_MemMap.h"

/* Enable/Disable/Clear the wakeup notification */
/*MISRA2012_RULE_8_9_JUSTIFICATION: This variable is updated across APIs using
 Tricore Atomic instructions, which is not detected by MISRA. Hence it cannot be
 declared at block scope */
static CanTrcv_TrcvWakeupModeType   \
CanTrcv_17_W9255_WakeupMode[CANTRCV_17_W9255_CHANNELS_CONFIGURED];

/* Store wakeup reason */
/*MISRA2012_RULE_8_9_JUSTIFICATION: This variable is updated across APIs using
 Tricore Atomic instructions, which is not detected by MISRA. Hence it cannot be
 declared at block scope */
static CanTrcv_TrcvWakeupReasonType   \
CanTrcv_17_W9255_WuReason[CANTRCV_17_W9255_CHANNELS_CONFIGURED];
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define CANTRCV_17_W9255_STOP_SEC_VAR_CLEARED_QM_LOCAL_32
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_W9255_MemMap.h"
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define CANTRCV_17_W9255_START_SEC_VAR_CLEARED_QM_LOCAL_16
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_W9255_MemMap.h"
/* Set/Clear the pending notification */
static uint16 CanTrcv_17_W9255_PendWakeup;

/* Source buffer to be transferred over SPI */
static uint16
CanTrcv_17_W9255_SourceBuffer[CANTRCV_17_W9255_CHANNELS_CONFIGURED];

/* Destination buffer received from SPI */
static uint16 CanTrcv_17_W9255_DestBuffer[CANTRCV_17_W9255_CHANNELS_CONFIGURED];
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define CANTRCV_17_W9255_STOP_SEC_VAR_CLEARED_QM_LOCAL_16
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_W9255_MemMap.h"
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define CANTRCV_17_W9255_START_SEC_VAR_CLEARED_QM_LOCAL_8
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_W9255_MemMap.h"
#if (CANTRCV_17_W9255_GENERAL_WAKE_UP_SUPPORT ==   \
CANTRCV_17_W9255_WAKE_UP_BY_POLLING)
/* Flag that indicates occurrence of a wakeup event */
static uint8
CanTrcv_17_W9255_WakeupFlagIndication[CANTRCV_17_W9255_CHANNELS_CONFIGURED];
#endif
#if (CANTRCV_17_W9255_DEV_ERROR_DETECT == STD_ON)
/* CAN trasnceiver hardware initialization updation */
static uint8 CanTrcv_17_W9255_InitState;
#endif
/* SPI busy status */
static uint8
CanTrcv_17_W9255_SpiBusyStatus[CANTRCV_17_W9255_CHANNELS_CONFIGURED];
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define CANTRCV_17_W9255_STOP_SEC_VAR_CLEARED_QM_LOCAL_8
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_W9255_MemMap.h"
/*[cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
Variables Memory section as per AS
[/cover]*/
/*****************************************************************************
**                      Global Function Definitions                         **
*****************************************************************************/
#define CANTRCV_17_W9255_START_SEC_CODE_QM_LOCAL
/* [cover parentID={03C90BFA-850A-4b3e-9D6E-51E503B46FE9}]
    MemMap file  [/cover] */
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
    MemMap mapping for code  [/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
    MemMap mapping  [/cover] */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_W9255_MemMap.h"
/* CanTrcv_17_W9255_Init API  */
/******************************************************************************
** Traceability    : [cover parentID={C2F5C298-D3AD-4dc9-B8D6-576D48AEA086}] **
**                                                                           **
** Syntax          : void  CanTrcv_17_W9255_Init(                            **
**                      const CanTrcv_ConfigType * const ConfigPtr)          **
**                                                                           **
** Description     : This API initializes the CAN Transceiver module. The    **
**                   registers of the TLE9255W hardware are initialized as   **
**                   per the configuration. The CAN Transceiver              **
**                   initialization status is set at the end of the          **
**                   initialization function execution.                      **
**                                                                           **
** [/cover]                                                                  **
**                                                                           **
** Service ID      : 0x00                                                    **
**                                                                           **
** Sync/Async      : Synchronous                                             **
**                                                                           **
** Reentrancy      : Non reentrant                                           **
**                                                                           **
** Parameters (in) : ConfigPtr : Pointer to driver configuration             **
**                                                                           **
** Parameters (out): None                                                    **
**                                                                           **
** Return value    : None                                                    **
**                                                                           **
******************************************************************************/
void CanTrcv_17_W9255_Init(const CanTrcv_17_W9255_ConfigType* const ConfigPtr)
{
  uint8 ChannelIndex;
  Std_ReturnType ReturnValue = E_OK;
  Spi_ChannelType SpiChannelUsed;
  Spi_SequenceType SpiSequenceUsed;
  uint8 ChannelId;
  uint8 PnIndex;
  uint8 CanTrcvWuByBus;
  uint16 InitState;

  #if (CANTRCV_17_W9255_DEV_ERROR_DETECT == STD_OFF)
  UNUSED_PARAMETER(ConfigPtr);
  #endif

  /* [cover parentID={4A1783F4-220A-4286-AD1A-761C4AB6978D}]
  DET enabled
  [/cover] */
  #if (CANTRCV_17_W9255_DEV_ERROR_DETECT == STD_ON)
  /* CAN transceiver hardware is not Initialized */
  CanTrcv_17_W9255_InitState = CANTRCV_17_W9255_UNINIT;
  /* [cover parentID={1BDCDB4C-09C9-4340-A8FF-B821DAB6B0D0}]
  Is ConfigPtr null?
  [/cover] */
  /* Check if NULL pointer is not passed */
  if (NULL_PTR != ConfigPtr)
  {
    /* [cover parentID={440A4BB5-2F52-4377-950C-FE8F29F3065B}]
    Report CANTRCV_17_W9255_E_INIT_FAILED to DET
    [/cover] */
    (void)Det_ReportError(
      CANTRCV_17_W9255_MODULE_ID,
      CANTRCV_17_W9255_INSTANCE_ID,
      CANTRCV_17_W9255_SID_INIT,
      CANTRCV_17_WV9255_E_INIT_FAILED
    );

  }
  else
  #endif
  {
    /* [cover parentID={B55BBFF7-8CE9-4b67-94C9-12C8754F47CF}]
    Are all used channels checked and return status E_OK?
    [/cover] */
    /* loop for all the configured transceivers */
    for(ChannelIndex = 0 ; ((ChannelIndex < CANTRCV_17_W9255_CHANNELS_USED) &&
                (ReturnValue == E_OK)); ChannelIndex++)
    {
      SpiChannelUsed =
             CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvSpiChannel;

      ChannelId =
             CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvChannelId;

      ReturnValue = CanTrcv_17_W9255_lSpiBusyCheck(ChannelId);

      /* [cover parentID={C768C71B-11D7-4efd-AC96-21D354130EE5}]
      Check if SPI channel status is idle
      [/cover] */
      if(ReturnValue == E_OK)
      {
        /* Initialization of source and destination buffers */
        ReturnValue = Spi_SetupEB(SpiChannelUsed, (Spi_DataBufferType*)
                                  &CanTrcv_17_W9255_SourceBuffer[ChannelId],
                 (Spi_DataBufferType*) &CanTrcv_17_W9255_DestBuffer[ChannelId],
                                  CANTRCV_17_W9255_DATA_LENGTH);

        SpiSequenceUsed =
          CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvSpiSequence;

        InitState =
               CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvInitState;

        /* Set the Wake up reason to Wake up by reset */
        CanTrcv_17_W9255_WuReason[ChannelId] = CANTRCV_WU_RESET;

        /* [cover parentID={688F042A-550D-4b8d-8636-B77616952F24}]
        Is return status E_OK?
        [/cover] */
        if(ReturnValue == E_OK)
        {
         CanTrcvWuByBus =
          CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvWakeupByBusEnable;

          /* [cover parentID={94A5C903-13B9-49c6-89E8-6F93E8FD8B40}]
          Check if wakeup by bus is enabled for the specified channel?
          [/cover] */
          if (CanTrcvWuByBus == STD_ON)
          {
            /* Check for wakeup during init */
            ReturnValue = CanTrcv_17_W9255_lCheckInitWakeup(ChannelIndex,
                                                            ChannelId);
          }
          /* [cover parentID={34AFBAFA-B58B-4b76-A53B-BF0FFEC45F91}]
          Is return status E_OK?
          [/cover] */
          if(ReturnValue == E_OK)
          {
            PnIndex = CanTrcv_17_W9255_PnConfigured[ChannelId];
            /* [cover parentID={9721C336-2A85-4b85-ABE8-911A89356C43}]
            Is PN enabled for the channel?
            [/cover] */
            if(PnIndex != CANTRCV_17_W9255_PN_NOT_CONFIGURED)
            {
              /* [cover parentID={A851133F-D91C-44b1-AF70-EC9E4341EFBE}]
              Check POR and SYSERR flags
              [/cover] */
              ReturnValue = CanTrcv_17_W9255_lInitCheckPorSyserr
                           (ChannelIndex, CANTRCV_17_W9255_SID_INIT);
              /* [cover parentID={F3A71B66-7563-42e5-AA6D-76311AACE568}]
              Is return status E_OK and POR or SYSERR not occurred?
              [/cover] */
              if((ReturnValue == E_OK) &&
              (CanTrcv_17_W9255_WuReason[ChannelId]!=CANTRCV_WU_BY_SYSERR) &&
              (CanTrcv_17_W9255_WuReason[ChannelId]!=CANTRCV_WU_POWER_ON))
              {
                #if (CANTRCV_17_W9255_PN_CONFIGURED_CHANNELS > 0U)
                /* [cover parentID={0D733171-491F-474d-8783-988D7FE3876F}]
                Configure registers for Partial networking and update
                return status
                [/cover] */
                /* Configure for Partial networking */
                ReturnValue = CanTrcv_17_W9255_lHardwareInitPN
                            (SpiSequenceUsed,
                             ChannelId, CANTRCV_17_W9255_SID_INIT);
                #endif
              }
            }
            else
            {
                CanTrcv_17_W9255_SourceBuffer[ChannelId] = CANTRCV_17_W9255_CLEAR_CFGVAL;
                ReturnValue = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                            &CanTrcv_17_W9255_DestBuffer[ChannelId], CANTRCV_17_W9255_SID_INIT,
                            (uint8)CANTRCV_17_W9255_REPORT_DET);
                /* [cover parentID={CCEB060E-774C-415e-878D-B9370C08B77B}]
                 Is return status E_OK?
                [/cover] */
                if(ReturnValue == E_OK)
                {
                  CanTrcv_17_W9255_SourceBuffer[ChannelId] = CANTRCV_17_W9255_DISBALE_PN;
                  ReturnValue = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                            &CanTrcv_17_W9255_DestBuffer[ChannelId], CANTRCV_17_W9255_SID_INIT,
                            (uint8)CANTRCV_17_W9255_REPORT_DET);
                }
            }
            /* [cover parentID={1854072D-C956-43bd-85E8-B649EC3DDA43}]
            Is return status E_OK?
            [/cover] */
            if(ReturnValue == E_OK)
            {
              /* [cover parentID={2A27FE7C-8698-4ba1-976D-D071492E3BE3}]
              Initialize hardware (Non - PN) registers
              [/cover] */
              /* Initialize hardware (Non - PN) registers */
              ReturnValue =
               CanTrcv_17_W9255_lHardwareInit(ChannelId, SpiSequenceUsed,
                                              InitState);
            }
          }
        }
        CanTrcv_17_W9255_SpiBusyStatus[ChannelId] = 0U;
      }
    }

    /* [cover parentID={ADA90FED-104A-41c6-9091-2AE3A4F739CE}]
    DET enabled
    [/cover] */
    #if (CANTRCV_17_W9255_DEV_ERROR_DETECT == STD_ON)

    /* [cover parentID={13F552E9-B068-4964-BFF2-18A5A5FEA4EF}]
    Is return status E_OK?
    [/cover] */
    if (ReturnValue == E_OK)
    {
      /* [cover parentID={C7D3BBF0-959D-4c62-BA7C-68E290E5DBBE}]
      Set driver state as initialized
      [/cover] */
      /* CAN transceiver hardware is Initialized */
      CanTrcv_17_W9255_InitState = CANTRCV_17_W9255_INITIALIZED;
    }
    #endif
  }
}/* end of CanTrcv_17_W9255_Init API */
/* CanTrcv_17_W9255_SetOpMode API  */
/******************************************************************************
** Traceability    : [cover parentID={217AFFFE-46AD-47e0-A60A-D3B9E18253DA}] **
**                                                                           **
** Syntax          : Std_ReturnType  CanTrcv_17_W9255_SetOpMode (            **
**                     const uint8 Transceiver,                              **
**                     const CanTrcv_TrcvModeType OpMode)                    **
**                                                                           **
** Description     : This API sets the mode of the requested Transceiver to  **
**                   the value OpMode. If PN is enabled, the API checks for  **
**                   POR and SYSERR flags. If POR flag is set, transceiver is**
**                   reinitialized and if SYSERR flag is set, transceiver is **
**                   reinitialized for PN functionality.                     **
**                                                                           **
**                                                                           **
** [/cover]                                                                  **
**                                                                           **
** Service ID      : 0x01                                                    **
**                                                                           **
** Sync/Async      : Asynchronous                                            **
**                                                                           **
** Reentrancy      : Reentrant for different transceivers                    **
**                                                                           **
** Parameters (in) : OpMode - This parameter contains the desired            **
**                           operating mode                                  **
**                   Transceiver - CAN transceiver to which API call         **
**                                has to be applied                          **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value    : E_OK : will be returned if the request for transceiver  **
**                          mode change has been accepted                    **
**                   E_NOT_OK : If there is SPI communication failure or a   **
**                              development error occurs                     **
**                                                                           **
******************************************************************************/
Std_ReturnType  CanTrcv_17_W9255_SetOpMode
(
  const uint8 Transceiver,
  const CanTrcv_TrcvModeType OpMode
)
{
  uint8 ChannelIndex;
  Std_ReturnType ReturnValue = E_NOT_OK;
  Spi_SequenceType SpiSequenceUsed;
  uint16 DataField;
  uint16 DestBuf;
  CanTrcv_TrcvModeType Mode = CANTRCV_TRCVMODE_STANDBY;

  /* [cover parentID={3F4073D4-8CD8-40d4-A0F1-E96BB79C9C75}]
  DET is ON
  [/cover] */
  #if (CANTRCV_17_W9255_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType DevError;

  /* [cover parentID={4CF6E8C3-96EF-487d-B8AB-702A9362BD36}]
  Check if the transceiver is initialized and update the return status
  [/cover] */
  /*  Check for driver initialization */
  DevError = CanTrcv_17_W9255_lCheckUninitDet
             (CANTRCV_17_W9255_SID_SETOPMODE);

  /* [cover parentID={D26801D8-4740-4787-81B4-35B14FBC7184}]
   Is return status E_OK?
  [/cover] */
  if (DevError == E_OK)
  {
    /* [cover parentID={92FE2F77-D036-4847-8D10-5734AEDDCDD0}]
    Check for invalid transceiver ID and update return status
    [/cover] */
    /* Check for valid channel Id */
    DevError = CanTrcv_17_W9255_lCheckChannelId(Transceiver,
               CANTRCV_17_W9255_SID_SETOPMODE);
  }

  /* [cover parentID={A58FE6E3-7CDE-461d-9608-EA88667C4EA4}]
  Is return status E_OK?
  [/cover] */
  if (DevError == E_OK)
  #endif
  {
    ChannelIndex = CanTrcv_17_W9255_ChannelUsed[Transceiver];

    SpiSequenceUsed =
       CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvSpiSequence;

    ReturnValue = CanTrcv_17_W9255_lSpiBusyCheck(Transceiver);

    /* [cover parentID={06E97FD2-6B0A-45d7-8305-3D26099A5B94}]
    Is SPI channel idle?
    [/cover] */
    if(ReturnValue == E_OK)
    {
      /* [cover parentID={375E9889-D649-4e69-B4BF-4F704E94CDAC}]
      Read the current mode from MODE_CTRL register
      [/cover] */
      /* Read the current mode */
      CanTrcv_17_W9255_SourceBuffer[Transceiver] =
          CANTRCV_17_W9255_READ_MODE_CTRL;

      /* [cover parentID={375E9889-D649-4e69-B4BF-4F704E94CDAC}]
      Read the current mode from MODE_CTRL register
      [/cover] */
      ReturnValue = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                    &CanTrcv_17_W9255_DestBuffer[Transceiver],
                    CANTRCV_17_W9255_SID_SETOPMODE,
                    (uint8)CANTRCV_17_W9255_REPORT_DET);

      DestBuf = CanTrcv_17_W9255_DestBuffer[Transceiver];

      /* [cover parentID={4BD89614-F99B-42c7-BFC0-31A55D485980}]
      Is return status E_OK?
      [/cover] */
      if (ReturnValue == E_OK)
      {
        DataField = DestBuf &
                    CANTRCV_17_W9255_EXTRACT_FOUR_BITS;
        /* [cover parentID={8EB7CC22-1B74-483d-8489-37524163D572}]
        Is the current mode NORMAL?
        [/cover] */
        if (DataField == CANTRCV_17_W9255_NORMAL)
        {
          Mode = CANTRCV_TRCVMODE_NORMAL;
        }
        /* [cover parentID={7ECF8791-5748-4faf-8241-6ECC8901812C}]
        Is the current mode STANDBY?
        [/cover] */
        else if (DataField == CANTRCV_17_W9255_STANDBY)
        {
          Mode = CANTRCV_TRCVMODE_STANDBY;
        }
        else
        {
          Mode = CANTRCV_TRCVMODE_SLEEP;
        }
        /* [cover parentID={E0F0DA79-0369-41b4-8BEA-849837DC9275}]
        DET is ON
        [/cover] */
        #if (CANTRCV_17_W9255_DEV_ERROR_DETECT == STD_ON)
        /* [cover parentID={C00D3532-BF3E-469f-BFCC-BE3EB2DC1E4E}]
        Check for valid mode transitions
        [/cover] */
        /* Check for valid mode transitions */
        DevError = CanTrcv_17_W9255_lCheckModeDet(Mode,
                   CANTRCV_17_W9255_SID_SETOPMODE, OpMode);

        /* [cover parentID={98F75AC6-1445-429d-B256-ECF59B8E46AF}]
        Has DET error occurred?
        [/cover] */
        if (DevError == E_NOT_OK)
        {
          /* [cover parentID={CF7F9A59-E1FD-4116-AD92-85E2F9416B31}]
          Update return status as E_NOT_OK
          [/cover] */
          ReturnValue = E_NOT_OK;
        }
        else
        #endif
        {
          /* [cover parentID={67AE407C-485D-4dca-B43F-1A4729578E27}]
          Check for wakeups and update return status
          [/cover] */
          ReturnValue = CanTrcv_17_W9255_lWuReasonChecks(ChannelIndex,
                        Mode, CANTRCV_17_W9255_SID_SETOPMODE, OpMode);

          /* [cover parentID={29DB087E-4A7F-4cf1-9AC6-C1D4C35CCCE4}]
          Is return status E_OK?
          [/cover] */
          if(ReturnValue == E_OK)
          {
            /* Check for the status of POR and SYSERR flags */
            ReturnValue = CanTrcv_17_W9255_lPorSyserrCheck(ChannelIndex,
                          CANTRCV_17_W9255_SID_SETOPMODE, OpMode);

            /* [cover parentID={2E982409-2B57-4c49-BA5B-964696D6690E}]
            Is return status E_OK?
            [/cover] */
            if (ReturnValue == E_OK)
            {
              /* [cover parentID={176EC923-60D6-4d87-A4FC-2BB85B28583D}]
              Check if the current mode is not equal to the mode requested
              [/cover] */
              /* Check if the current mode is not equal to the mode requested */
              if(Mode == OpMode)
              {
                /* [cover parentID={524B41BC-F488-49a3-9586-C0478367D5A5}]
                Inform CanIf about the mode switch
                [/cover] */
                /*Invoke call back function after each mode switch*/
                CanIf_TrcvModeIndication(Transceiver, OpMode);
              }
              else
              {

                /* [cover parentID={6275C663-8027-49f1-9D32-3D3EAFF18E22}]
                Put the transceiver to the mode requested and update
                the return status
                [/cover] */
                /* Put the transceiver to the mode requested */
                ReturnValue = CanTrcv_17_W9255_lSetTrcvMode
                              (Transceiver, SpiSequenceUsed, OpMode);

                /* [cover parentID={55AF2092-9AC0-441a-BB64-3070BD777263}]
                Is return status E_OK?
                [/cover] */
                if (ReturnValue == E_OK)
                {
                  /* [cover parentID={524B41BC-F488-49a3-9586-C0478367D5A5}]
                  Inform CanIf about the mode switch
                  [/cover] */
                  /*Invoke call back function after each mode switch*/
                  CanIf_TrcvModeIndication(Transceiver, OpMode);

                  CanTrcv_17_W9255_SpiBusyStatus[Transceiver] = 0U;
                }
              }
            }
          }
        }
      }
      CanTrcv_17_W9255_SpiBusyStatus[Transceiver] = 0U;
    }
  }

  /* [cover parentID={B8760D3E-56B4-4d29-A075-64F6A9331BCF}]
  Return status
  [/cover] */
  return ReturnValue;
}/* end of CanTrcv_17_W9255_SetOpMode API  */
/* CanTrcv_17_W9255_GetOpMode API  */
/******************************************************************************
** Traceability    : [cover parentID={0D31B38B-6350-4a74-ABB7-359D502A0733}] **
**                                                                           **
** Syntax          : Std_ReturnType  CanTrcv_17_W9255_GetOpMode(             **
**                       const uint8 Transceiver,                            **
**                       CanTrcv_TrcvModeType * const OpMode)                **
**                                                                           **
** Description     : Gets the mode of the Transceiver and returns it in      **
**                   parameter OpMode                                        **
**                                                                           **
** [/cover]                                                                  **
**                                                                           **
** Service ID      : 0x02                                                    **
**                                                                           **
** Sync/Async      : Synchronous                                             **
**                                                                           **
** Reentrancy      : Reentrant                                               **
**                                                                           **
** Parameters (in) : Transceiver - CAN transceiver to which API call has     **
**                                 to be applied                             **
**                                                                           **
**                                                                           **
** Parameters (out): OpMode - Pointer to operation mode of the transceiver   **
**                            the API is applied to                          **
**                                                                           **
** Return value    : E_OK : will be returned if the operation mode           **
**                          was detected                                     **
**                   E_NOT_OK : If SPI communication failure or a development**
**                              error occurs                                 **
**                                                                           **
******************************************************************************/
Std_ReturnType  CanTrcv_17_W9255_GetOpMode
(
  const uint8 Transceiver,
  CanTrcv_TrcvModeType * const OpMode
)
{
  Std_ReturnType ReturnValue = E_NOT_OK;
  uint16 DataField;
  uint8 ChannelIndex;
  Spi_SequenceType SpiSequenceUsed;

  /* [cover parentID={35673AF8-0B29-4bd2-B44F-45E35305D8D8}]
  DET is ON
  [/cover] */
  #if (CANTRCV_17_W9255_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType DevError ;

  /* [cover parentID={28747595-4B13-4f40-81D7-0D682E94833C}]
  Check for module initialization
  [/cover] */
  /* Check for driver initialization */
  DevError = CanTrcv_17_W9255_lCheckUninitDet
             (CANTRCV_17_W9255_SID_GETOPMODE);

  /* [cover parentID={3A6E5D60-0D65-4b24-9B91-D55AF60B3C76}]
  Is module initialized?
  [/cover] */
  if (DevError == E_OK)
  {
    /* [cover parentID={674DAB4C-8422-493d-B8CF-40F7C8C9694F}]
    Check for invalid CAN transceiver channel Id
    [/cover] */
    /* Check for valid channel Id */
    DevError = CanTrcv_17_W9255_lCheckChannelId(Transceiver,
               CANTRCV_17_W9255_SID_GETOPMODE);
  }

  /* [cover parentID={753F2BE9-9AE1-472d-915D-B66432C21CDE}]
  Is channel Id invalid?
  [/cover] */
  if (DevError == E_OK)
  {
    /* [cover parentID={D2AA9577-72ED-4a16-86F9-C3DFF0FAC39B}]
    Is NULL pointer passed as parameter?
    [/cover] */
    /* Null pointer check */
    if (OpMode == NULL_PTR)
    {
      /* [cover parentID={D4E24492-9773-4d80-ABA9-7ECA2742D1E8}]
      Report error CANTRCV_17_W9255_E_PARAM_POINTER to DET
      [/cover] */
      /* Parameter is null. Report error to DET. */
      (void)Det_ReportError(
        CANTRCV_17_W9255_MODULE_ID,
        CANTRCV_17_W9255_INSTANCE_ID,
        CANTRCV_17_W9255_SID_GETOPMODE,
        CANTRCV_17_W9255_E_PARAM_POINTER
      );
      DevError = E_NOT_OK ;
    }
  }

  /* [cover parentID={D2AA9577-72ED-4a16-86F9-C3DFF0FAC39B}]
  Any DET error occured?
  [/cover] */
  if (DevError == E_OK)
  #endif
  {
    ChannelIndex = CanTrcv_17_W9255_ChannelUsed[Transceiver];

    SpiSequenceUsed =
         CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvSpiSequence;

    ReturnValue = CanTrcv_17_W9255_lSpiBusyCheck(Transceiver);

    /* [cover parentID={7BFA37A8-AE1B-48a2-A1AE-9E9E2EB7D9CD}]
    Check if SPI channel status is idle
    [/cover] */
    if(ReturnValue == E_OK)
    {
      /* [cover parentID={CCD8C589-2D92-422a-8C52-DC371F303CE6}]
      Load the source buffer to read MODE_CTRL register
      [/cover] */
      /* Read the current mode */
      CanTrcv_17_W9255_SourceBuffer[Transceiver] =
          CANTRCV_17_W9255_READ_MODE_CTRL;

      /* [cover parentID={57AE9ACB-5F2D-40bf-8417-D75B2A32B0D8}]
       Transmit buffer over SPI and check for SPI error and update
       the return status
      [/cover] */
      ReturnValue = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                    &CanTrcv_17_W9255_DestBuffer[Transceiver],
                    CANTRCV_17_W9255_SID_GETOPMODE,
                    (uint8)CANTRCV_17_W9255_REPORT_DET);

      /* [cover parentID={412E492A-BAF8-44e4-BB34-241CA72DBDE9}]
      Is return status E_OK?
      [/cover] */
      if (ReturnValue == E_OK)
      {
        DataField = CanTrcv_17_W9255_DestBuffer[Transceiver] &
                    CANTRCV_17_W9255_EXTRACT_FOUR_BITS;
        /* [cover parentID={2DE95BFE-4A09-4642-908E-08788D85530D}]
        Read the current mode and update the OpMode value
        [/cover] */
        if (DataField == CANTRCV_17_W9255_NORMAL)
        {
          *OpMode = CANTRCV_TRCVMODE_NORMAL;
        }
        else if (DataField == CANTRCV_17_W9255_STANDBY)
        {
          *OpMode = CANTRCV_TRCVMODE_STANDBY;
        }
        else
        {
          *OpMode = CANTRCV_TRCVMODE_SLEEP;
        }
      }
      CanTrcv_17_W9255_SpiBusyStatus[Transceiver] = 0U;
    }
  }
  /* [cover parentID={787C6BAE-5C2B-4614-BFDA-3F364B4FE4A2}]
   Return status
  [/cover] */
  return ReturnValue;
}/* end of CanTrcv_17_W9255_GetOpMode API  */
/* CanTrcv_17_W9255_GetBusWuReason API  */
/******************************************************************************
** Traceability    : [cover parentID={A82CFC0F-743D-41c4-B9B2-0B4E5E3EA297}] **
**                                                                           **
** Syntax          : Std_ReturnType  CanTrcv_17_W9255_GetBusWuReason(        **
**                        const uint8 Transceiver,                           **
**                        CanTrcv_TrcvWakeupReasonType * const reason)       **
**                                                                           **
** Description     : Gets the wakeup reason for the Transceiver and returns  **
**                   it in parameter Reason                                  **
**                                                                           **
** [/cover]                                                                  **
**                                                                           **
** Service ID      : 0x03                                                    **
**                                                                           **
** Sync/Async      : Synchronous                                             **
**                                                                           **
** Reentrancy      : Reentrant                                               **
**                                                                           **
** Parameters (in) : Transceiver - CAN transceiver to which API call has to  **
**                                 be applied                                **
**                                                                           **
** Parameters (out): reason - Pointer to wake up reason of the bus the API   **
**                            is applied to                                  **
**                                                                           **
** Return value    : E_OK : will be returned if the transceiver wakeup       **
**                          reason was detected                              **
**                   E_NOT_OK : if the service request failed                **
**                              due to development errors                    **
**                                                                           **
******************************************************************************/
Std_ReturnType  CanTrcv_17_W9255_GetBusWuReason
(
  const uint8 Transceiver,
  CanTrcv_TrcvWakeupReasonType * const reason
)
{
  Std_ReturnType DevError ;

  /* [cover parentID={7BC834C3-69D0-4399-A874-41E38233B504}]
  DET is ON
  [/cover] */
  #if (CANTRCV_17_W9255_DEV_ERROR_DETECT == STD_ON)

  /* [cover parentID={86B347F5-9181-43f9-A951-D226E126AF8B}]
  Check for module initialization
  [/cover] */
  /* Check for driver initialization */
  DevError =
      CanTrcv_17_W9255_lCheckUninitDet(CANTRCV_17_W9255_SID_GETBUSWUREASON);

  /* [cover parentID={89935E46-A99A-48ca-A7AC-9C347B5E5F7A}]
  Is module initialized?
  [/cover] */
  if (DevError == E_OK)
  {
    /* [cover parentID={87003DBA-FDDF-4bca-AB63-0E536EC5D322}]
    Check for Invalid CAN transceiver channel Id
    [/cover] */
    /* If called with invalid network Id */
    DevError = CanTrcv_17_W9255_lCheckChannelId(Transceiver,
               CANTRCV_17_W9255_SID_GETBUSWUREASON);

  }
  /* [cover parentID={06642D3E-5758-40c0-AA72-BE722EA76962}]
  Is channel Id invalid?
  [/cover] */
  if (DevError == E_OK)
  {
    /* [cover parentID={2BD41F26-45C5-44af-9E45-948837D538B5}]
    Is pointer NULL?
    [/cover] */
    /* Null pointer check */
    if (reason == NULL_PTR)
    {
      /* [cover parentID={E088C727-7086-4448-B91D-B5F2524CB37B}]
      Report error CANTRCV_17_W9255_E_PARAM_POINTER to DET
      [/cover] */
      /* Parameter is null. Report error to DET. */
      (void)Det_ReportError(
        CANTRCV_17_W9255_MODULE_ID,
        CANTRCV_17_W9255_INSTANCE_ID,
        CANTRCV_17_W9255_SID_GETBUSWUREASON,
        CANTRCV_17_W9255_E_PARAM_POINTER
      );

      /* [cover parentID={499BC692-7C06-42a7-9BC4-4FCEE636BA8E}]
      Return E_NOT_OK
      [/cover] */
      DevError = E_NOT_OK;
    }
  }
  /* [cover parentID={2BD41F26-45C5-44af-9E45-948837D538B5}]
  Any DET error occured?
  [/cover] */
  if (DevError == E_OK)
  #endif
  {

    /* [cover parentID={6EFBE5B4-1490-4298-A517-49398C2492D5}]
     Read and return the Wake Up Reason
    [/cover] */
    /* returns the wake up reason */
    *reason = CanTrcv_17_W9255_WuReason[Transceiver];

    /* If No DET is raised, return E_OK else return E_NOT_OK */
    DevError = E_OK;

  }
  return DevError;
}/* end of CanTrcv_17_W9255_GetBusWuReason API  */
#if (CANTRCV_17_W9255_GET_VERSION_INFO == STD_ON)
/* CanTrcv_17_W9255_GetVersionInfo API  */
/*******************************************************************************
** Traceability    : [cover parentID={6064B839-C3D4-4d39-897B-743EE316AD6E}]  **
**                                                                            **
** Syntax          : void  CanTrcv_17_W9255_GetVersionInfo (                  **
**                        Std_VersionInfoType * const versioninfo )           **
**                                                                            **
** Description     : Gets the version of the module and returns it in         **
**                   versioninfo                                              **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      : 0x04                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): versioninfo - Pointer to where to store version          **
**                                 information of this module                 **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
/* [cover parentID={9791CB9C-CAEA-4d06-8F98-C038DFB0F012}]
CanTrcv_17_W9255_GetVersionInfo
[/cover] */
void CanTrcv_17_W9255_GetVersionInfo
(
  Std_VersionInfoType* const versioninfo
)
{
  /* [cover parentID={1B2FE92A-821F-4640-A609-DB4691BAD70E}]
   DET is ON
  [/cover] */
  #if (CANTRCV_17_W9255_DEV_ERROR_DETECT == STD_ON )

  /* [cover parentID={DEBE9134-6368-4c0c-89FA-83AB4F942265}]
  Is versioninfo NULL?
  [/cover] */
  /* Null pointer check */
  if ((versioninfo) == NULL_PTR)
  {

    /* [cover parentID={84779425-8556-46a8-A7CB-03700854AE9E}]
    Report CANTRCV_17_W9255_E_PARAM_POINTER error to DET
    [/cover] */
    /* API called with null pointer parameter. Report error to DET. */
    (void)Det_ReportError((uint16)CANTRCV_17_W9255_MODULE_ID,
                    CANTRCV_17_W9255_INSTANCE_ID,
                    CANTRCV_17_W9255_SID_GETVERSIONINFO,
                    CANTRCV_17_W9255_E_PARAM_POINTER);

  }
  else
  #endif /* #if (CANTRCV_17_W9255_DEV_ERROR_DETECT == STD_ON )  */
  {
    /* [cover parentID={FD5527F2-A3EE-4992-983F-1E40AC1A6E73}]
    Update Version Information in the location referenced by versioninfo pointer
    [/cover] */
    /* Update Version Information in the location referenced by versioninfo */
    versioninfo->moduleID = CANTRCV_17_W9255_MODULE_ID;
    versioninfo->vendorID = CANTRCV_17_W9255_VENDOR_ID;
    versioninfo->sw_major_version =
      (uint8)CANTRCV_17_W9255_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version =
      (uint8)CANTRCV_17_W9255_SW_MINOR_VERSION;
    versioninfo->sw_patch_version =
      (uint8)CANTRCV_17_W9255_SW_PATCH_VERSION;
  }
}/* end of CanTrcv_17_W9255_GetVersionInfo API  */
#endif
/* CanTrcv_17_W9255_SetWakeupMode API  */
/******************************************************************************
** Traceability    : [cover parentID={EDA202DD-D3E0-4479-AF91-850D479CDA1A}] **
**                                                                           **
** Syntax          : Std_ReturnType  CanTrcv_17_W9255_SetWakeupMode (        **
**                    const uint8 Transceiver,                               **
**                    const CanTrcv_TrcvWakeupModeType TrcvWakeupMode)       **
**                                                                           **
** Description     : This function enables, disables and clears the          **
**                   notification for wake up events of the Transceiver      **
**                   according to the parameter TrcvWakeupMode               **
**                                                                           **
** [/cover]                                                                  **
**                                                                           **
** Service ID      : 0x05                                                    **
**                                                                           **
** Sync/Async      : Synchronous                                             **
**                                                                           **
** Reentrancy      : Reentrant for different transceivers                    **
**                                                                           **
** Parameters (in) : TrcvWakeupMode - Requested Transceiver Wakeup Mode      **
**                   Transceiver - CAN transceiver to which API call has     **
**                                to be applied                              **
**                                                                           **
** Parameters (out): None                                                    **
**                                                                           **
** Return value    : E_OK : Wakeup state changed to the requested mode       **
**                   E_NOT_OK : If SPI communication fails, wake-up by bus is**
**                              disabled or a development error occurs. The  **
**                              previous state has not been changed.         **
**                                                                           **
******************************************************************************/
Std_ReturnType  CanTrcv_17_W9255_SetWakeupMode
(
  const uint8 Transceiver,
  const CanTrcv_TrcvWakeupModeType TrcvWakeupMode
)
{
  Std_ReturnType DevError ;
  uint8 ChannelIndex;
  EcuM_WakeupSourceType WakeupSourceRef;
  boolean CanTrcvWuByBus;
   /* [cover parentID={2A122E84-7E82-4f88-9A7B-A3DFE59A1542}]
   DET is OFF
   [/cover] */
  #if (CANTRCV_17_W9255_DEV_ERROR_DETECT == STD_OFF)
  DevError = E_OK;
  #endif

  /* [cover parentID={467C77CC-AEF0-44d0-BD8D-47F81B7F14BA}]
  DET enabled
  [/cover] */
  #if (CANTRCV_17_W9255_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={BEEF588D-19AE-4dc8-8012-1ECEFDBEEEB4}]
  Check for driver initialization and update the return status
  [/cover] */
  /* Check for driver initialization */
  DevError = CanTrcv_17_W9255_lCheckUninitDet
             (CANTRCV_17_W9255_SID_SETWAKEUPMODE);

  /* [cover parentID={0F98859D-4D19-49c7-9C84-75F60EDCF863}]
  Has DET error occured?
  [/cover] */
  if (DevError == E_OK)
  {
    /* [cover parentID={1A1FBDE9-8D21-4f49-A084-BD78ECD7FC06}]
    Check for invalid CAN transceiver channel Id and update the return status
    [/cover] */
    /* Check for valid channel Id */
    DevError = CanTrcv_17_W9255_lCheckChannelId(Transceiver,
               CANTRCV_17_W9255_SID_SETWAKEUPMODE);
  }

  /* [cover parentID={7735242A-868C-4df6-A85B-F3ECC333FE75}]
  Has DET error occured?
  [/cover] */
  if (DevError == E_OK)
  {
    /* [cover parentID={8CC6ED4E-5400-447f-B215-3EABA2708C19}]
    Is Wakeup mode invalid?
    [/cover] */
    /* Check for invalid wakeup mode */
    if ((TrcvWakeupMode != CANTRCV_WUMODE_ENABLE) &&
        (TrcvWakeupMode != CANTRCV_WUMODE_DISABLE) &&
        (TrcvWakeupMode != CANTRCV_WUMODE_CLEAR))
    {
      /* [cover parentID={3DE0199F-8BFF-41d2-8615-7BC15C07595C}]
      Report error CANTRCV_17_W9255_E_PARAM_TRCV_WAKEUP_MODE to DET and
      update the return status as E_NOT_OK
      [/cover] */
      /* Parameter is not valid. Report error to DET. */
      (void)Det_ReportError( CANTRCV_17_W9255_MODULE_ID,
                       CANTRCV_17_W9255_INSTANCE_ID,
                       CANTRCV_17_W9255_SID_SETWAKEUPMODE,
                       CANTRCV_17_W9255_E_PARAM_TRCV_WAKEUP_MODE
                     );
      DevError = E_NOT_OK;
    }
  }
  /* [cover parentID={3DE0199F-8BFF-41d2-8615-7BC15C07595C}]
  Has DET error occured?
  [/cover] */
  if (DevError == E_OK)
  #endif
  {
    ChannelIndex = CanTrcv_17_W9255_ChannelUsed[Transceiver];
    /* wake up by bus variable */
    CanTrcvWuByBus =
         CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvWakeupByBusEnable;
    /* [cover parentID={CFB4533B-4C63-47fe-8318-359A57C98898}]
    Is wake up by bus enabled?
    [/cover] */
    if(CanTrcvWuByBus == STD_ON)
    {
    /* [cover parentID={F0E4CED4-8F6A-4e99-999B-C59041AA8BA2}]
    Requested to Enable the Wake Up ?
    [/cover] */
    /* If the function CanTrcv_17_W9255_SetWakeupMode is called with
    TrcvWakupMode==CANTRCV_WUMODE_ENABLE and if the CanTrcv module has a
    stored wakeup event pending for the addressed channel, the CanTrcv module
    shall inform EcuM */
    if (TrcvWakeupMode == CANTRCV_WUMODE_ENABLE)
    {
      /* [cover parentID={6CE70665-E82A-4050-B7E6-CD0FF8139694}]
      Enable the Wake Up notification for the respective channel
      [/cover] */
      /* Enable the wake up for the related channel */
      CanTrcv_17_W9255_WakeupMode[Transceiver] = CANTRCV_WUMODE_ENABLE;

      /* [cover parentID={A1A44E88-4080-4956-A819-FABE0BA43524}]
      Is there any pending Wake up?
      [/cover] */
      /* Check for pending wakeup events */
      if (CANTRCV_17_W9255_PENWU_SET ==
          CanTrcv_17_W9255_lGetPendWakeup(Transceiver))
      {
        WakeupSourceRef =
         CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvWakeupSourceRef;

        /* [cover parentID={C2D7B2EE-D1FD-4cb0-BAA6-AA54197ABE24}]
        Indicate EcuM about the Pending Wake Up
        [/cover] */
        /* Inform about the pending wakeup event to EcuM */
        EcuM_SetWakeupEvent(((uint32)1U) << WakeupSourceRef);

        /* Clear the pending wakeup events */
        CanTrcv_17_W9255_lClearPendWakeup(Transceiver);
      }
    }
    /* [cover parentID={BB80ED09-D757-47e0-B739-78FAE620806F}]
    Requested to Disable the Wake Up ?
    [/cover] */
    /*  Disabled: If the function CanTrcv_17_W9255_SetWakeupMode is
    called with TrcvWakeupMode==CANTRCV_WUMODE_DISABLE, then the notifications
    for wakeup events are disabled on the addressed channel */
    else if (TrcvWakeupMode == CANTRCV_WUMODE_DISABLE)
    {
      /* [cover parentID={24BBF7BB-752F-4d6f-9859-B828259B2F44}]
      Disable the Wake Up notification on the addressed channel
      [/cover] */
      /* Disable the notification  */
      CanTrcv_17_W9255_WakeupMode[Transceiver] = CANTRCV_WUMODE_DISABLE;
    }
    /* [cover parentID={DC81EE09-92F5-47fe-92CF-60C5CA2A1C30}]
    Requested to Clear the Wake Up ?
    [/cover] */
    /* Clear: If the function CanTrcv_17_W9255_SetWakeupMode is called with
    TrcvWakeupMode==CANTRCV_WUMODE_CLEAR, then a stored wakeup event is
    cleared on the addressed channel */
    else
    {
      Spi_SequenceType SpiSequenceUsed =
           CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvSpiSequence;

      /* [cover parentID={4914D399-64E0-4079-9DD4-DD9A23693FE6}]
      Clear the pending wakeup events
      [/cover] */
      /* Clear the pending wakeup events */
      CanTrcv_17_W9255_lClearPendWakeup(Transceiver);

      DevError = CanTrcv_17_W9255_lSpiBusyCheck(Transceiver);

      /* [cover parentID={D0ED2CBD-F7F8-4273-B41F-6813666748A2}]
      Check if SPI channel status is idle
      [/cover] */
      if(DevError == E_OK)
      {
        /* [cover parentID={5BC61227-E834-4757-A146-A9992AD04845}]
        Clear the WAKE STAT register and update the return status
        [/cover] */
        /* Clear the wake flags */
        CanTrcv_17_W9255_SourceBuffer[Transceiver] =
            CANTRCV_17_W9255_CLEAR_WAKE_STAT;
        DevError = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                           &CanTrcv_17_W9255_DestBuffer[Transceiver],
                           CANTRCV_17_W9255_SID_SETWAKEUPMODE,
                           (uint8)CANTRCV_17_W9255_REPORT_DET);

        CanTrcv_17_W9255_SpiBusyStatus[Transceiver] = 0U;
      }

      /* [cover parentID={CCE0F5BF-F921-42ba-B968-F6976E151379}]
      Set the wake up mode as Clear for the related channel
      [/cover] */
      /* Clear the wake up for the related channel */
      CanTrcv_17_W9255_WakeupMode[Transceiver] = CANTRCV_WUMODE_CLEAR;
    }
    }
    else
    {
        DevError = E_NOT_OK;
    }
  }
  /* [cover parentID={F0257122-F95C-4e9f-BE13-FD6D866C45C4}]
  Return status
  [/cover] */
  return DevError;
}/* end of CanTrcv_17_W9255_SetWakeupMode API  */
/* CanTrcv_17_W9255_CheckWakeup API  */
/*******************************************************************************
** Traceability    : [cover parentID={03869DA7-EE33-453f-B0EE-7C2F6CEE0F09}]  **
**                                                                            **
** Syntax          : Std_ReturnType  CanTrcv_17_W9255_CheckWakeup (           **
**                    const uint8 Transceiver )                               **
**                                                                            **
** Description     : This service is called by the underlying CanIf, both in  **
**                   cases of polling and interrupt mode. This API validates  **
**                   wake-up event and if true, reports it to EcuM if the     **
**                   wakeup mode is enabled, clears the wake flags on the     **
**                   hardware and changes the mode of the respective channel  **
**                   to Normal.                                               **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      : 0x07                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : Transceiver - CAN transceiver to which API call has      **
**                                 to be applied                              **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value    : E_OK  : If a valid interrupt is detected                 **
**                   E_NOT_OK  : If SPI communication fails, development error**
**                               is detected, wake up by bus is disabled for  **
**                               the channel called, or a false interrupt is  **
**                               detected                                     **
**                                                                            **
*******************************************************************************/
Std_ReturnType  CanTrcv_17_W9255_CheckWakeup
(
  const uint8 Transceiver
)
{
  /* [cover parentID={B8521C14-DF23-4758-B124-D182CC90DC96}]
  Set return status as E_NOT_OK
  [/cover] */
  Std_ReturnType ReturnValue = E_NOT_OK ;
  uint8 ChannelIndex;
  uint16 DataField;
  CanTrcv_TrcvModeType Mode = CANTRCV_TRCVMODE_STANDBY;
  Spi_SequenceType SpiSequenceUsed;
  /* [cover parentID={85858996-D503-4f4b-A06A-B5F1F1C5A72C}]
  DET is ON
  [/cover] */
  #if (CANTRCV_17_W9255_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType DevError;
  /* [cover parentID={356E7F2E-9E45-435e-994B-FE988C78A148}]
  Check if the transceiver is initialized and update the return status
  [/cover] */
  /* Check for driver initialization */
  DevError = CanTrcv_17_W9255_lCheckUninitDet
             (CANTRCV_17_W9255_SID_CHECKWAKEUP);
  /* [cover parentID={79D60BA6-275C-4dc7-ADA1-1EF035128F45}]
  Is the transceiver initialized?
  [/cover] */
  if (DevError == E_OK)
  {
    /* [cover parentID={813F7B04-272A-478a-A482-0DEFA187FB3A}]
    Check for valid transceiver ID and update the return status
    [/cover] */
    /* Check for valid channel Id */
    DevError = CanTrcv_17_W9255_lCheckChannelId(Transceiver,
               CANTRCV_17_W9255_SID_CHECKWAKEUP);
  }

  /* [cover parentID={4C5941EC-159A-4ce6-8285-1032061B75DE}]
  Is return status E_OK?
  [/cover] */
  if (DevError == E_OK)
  #endif
  {
    ChannelIndex = CanTrcv_17_W9255_ChannelUsed[Transceiver];

    SpiSequenceUsed =
        CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvSpiSequence;

    ReturnValue = CanTrcv_17_W9255_lSpiBusyCheck(Transceiver);
    /* [cover parentID={BD12CF4C-9E4E-4cb2-8D05-7CC19CB09EC1}]
    Is SPI channel idle?
    [/cover] */
    if(ReturnValue == E_OK)
    {
      /* Read the current mode */
      CanTrcv_17_W9255_SourceBuffer[Transceiver] =
          CANTRCV_17_W9255_READ_MODE_CTRL;

      /* [cover parentID={DDB0CB48-5B54-44b6-B9B1-9FADF90E4C93}]
       Read the current mode from the MODE_CTRL register and
       update the return status
      [/cover] */
      ReturnValue = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                    &CanTrcv_17_W9255_DestBuffer[Transceiver],
                    CANTRCV_17_W9255_SID_CHECKWAKEUP,
                    (uint8)CANTRCV_17_W9255_DET_DISABLE);
      /* [cover parentID={F5FE3174-06DA-409a-8479-344F03563F37}]
      Is return status E_OK?
      [/cover] */
      if (ReturnValue == E_OK)
      {
        DataField = CanTrcv_17_W9255_DestBuffer[Transceiver] &
                    CANTRCV_17_W9255_EXTRACT_FOUR_BITS;

        /* [cover parentID={DDB0CB48-5B54-44b6-B9B1-9FADF90E4C93}]
        Read the current mode from the MODE_CTRL register
        [/cover] */
        if (DataField == CANTRCV_17_W9255_NORMAL)
        {
          Mode = CANTRCV_TRCVMODE_NORMAL;
        }
        else if (DataField == CANTRCV_17_W9255_STANDBY)
        {
          Mode = CANTRCV_TRCVMODE_STANDBY;
        }
        else
        {
          Mode = CANTRCV_TRCVMODE_SLEEP;
        }
        /* [cover parentID={C60C46D6-0657-4e19-8FD7-E6400660ABD4}]
            Wake up supported by Interrupt
            [/cover] */
        #if (CANTRCV_17_W9255_GENERAL_WAKE_UP_SUPPORT ==  \
        CANTRCV_17_W9255_WAKE_UP_BY_INTERRUPT)
        /* [cover parentID={77A0E13E-F281-47fa-9B52-E26E9C488B32}]
        Is current mode STANDBY?
        [/cover] */
        /* Check if the current mode is STANDBY */
        if (Mode ==  CANTRCV_TRCVMODE_STANDBY)
        {
          /* [cover parentID={CDC0BBDD-05FA-4d29-B1A5-FCA41ACC9462}]
          Check for valid wakeup and update return status
          [/cover] */
          /* Check for valid wake up */
          ReturnValue = CanTrcv_17_W9255_lCheckWakeup(Transceiver);
        }
        #else
        /* [cover parentID={B88C659F-AA17-4d0f-AC1A-78C967DF4B95}]
            Wake up supported by Polling
            [/cover] */
        /* [cover parentID={1448ABBC-AB0A-499f-A689-BC08DA439874}]
        Is current mode SLEEP/STANDBY?
        [/cover] */
        /* Check if the current mode is Standby/Sleep */
        if (Mode !=  CANTRCV_TRCVMODE_NORMAL)
        {
        boolean CanTrcvWuByBus =
          CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvWakeupByBusEnable;

          /* [cover parentID={D29F70A8-1F73-49b2-B56A-9DDD9AAC9BCE}]
          Is wake up flag status set and bus enabled?
          [/cover] */
          /* Check if wake flag is set and wake up by bus is enabled */
          if((CanTrcv_17_W9255_WakeupFlagIndication[Transceiver] == 1U) &&
              (CanTrcvWuByBus == STD_ON))
          {
            /* Reset the wake flag status */
            CanTrcv_17_W9255_WakeupFlagIndication[Transceiver] = 0U;

            /* [cover parentID={0025454D-DEE9-4da8-8B6E-27E95A735085}]
            Is wake mode enabled?
            [/cover] */
            /* Check if wake mode is enabled */
            if (CANTRCV_WUMODE_ENABLE ==
                CanTrcv_17_W9255_WakeupMode[Transceiver])
            {
            EcuM_WakeupSourceType WakeupSourceRef =
            CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvWakeupSourceRef;

              /* [cover parentID={CC2A6DB4-7E80-41e1-93C5-008C51FA4183}]
              Inform EcuM about the wake-up event
              [/cover] */
              /* Inform EcuM about the wake-up event */
              EcuM_SetWakeupEvent(((uint32)1U) << WakeupSourceRef);
            }
            else
            {
              /* [cover parentID={0EE5746D-7745-4ad9-8069-EE1F4404A954}]
              Update the pending wakeup event
              [/cover] */
              /* Update the pending wakeup event */
              CanTrcv_17_W9255_lSetPendWakeup(Transceiver);
            }
            /* Clear the wake flags */
            CanTrcv_17_W9255_SourceBuffer[Transceiver] =
                CANTRCV_17_W9255_CLEAR_WAKE_STAT;
            ReturnValue = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                          &CanTrcv_17_W9255_DestBuffer[Transceiver],
                          CANTRCV_17_W9255_SID_CHECKWAKEUP,
                          (uint8)CANTRCV_17_W9255_DET_DISABLE);

            /* [cover parentID={2B027EB1-CFFF-4700-B241-CD18E6C6C990}]
            Is return status E_OK?
            [/cover] */
            if (ReturnValue == E_OK)
            {
              /* Set the CAN transceiver hardware to Normal mode */
              CanTrcv_17_W9255_SourceBuffer[Transceiver] =
                  CANTRCV_17_W9255_NORMAL_VAL;
              /* [cover parentID={1DB83456-6808-4041-970D-0FE69F916CBD}]
              Set the CAN transceiver hardware to Normal mode and update the
              return status
              [/cover] */
              ReturnValue = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                            &CanTrcv_17_W9255_DestBuffer[Transceiver],
                            CANTRCV_17_W9255_SID_CHECKWAKEUP,
                            (uint8)CANTRCV_17_W9255_DET_DISABLE);

              CanTrcv_17_W9255_ldelay();
            }

          }
        }
        #endif
        else
        {
          ReturnValue = E_NOT_OK;
        }
      }
      CanTrcv_17_W9255_SpiBusyStatus[Transceiver] = 0U;
    }
  }
  /* [cover parentID={06CEDE4E-E400-4e6a-B9FC-557A0485BCB3}]
  Return status
  [/cover] */
  return ReturnValue;
}/* end of CanTrcv_17_W9255_CheckWakeup API  */
#if (CANTRCV_17_W9255_GENERAL_WAKE_UP_SUPPORT ==    \
CANTRCV_17_W9255_WAKE_UP_BY_POLLING)
/* CanTrcv_17_W9255_MainFunction API  */
/******************************************************************************
** Traceability    : [cover parentID={2988EDFC-E3D7-4d96-B293-DB1253E9A8DF}] **
**                                                                           **
** Syntax          : void CanTrcv_17_W9255_MainFunction ( void )             **
**                                                                           **
** Description     : This API scans all transceiver channels in Stand-by     **
**                   and Sleep modes for wake up events and sets a wake-up   **
**                   event flag to perform these events.                     **
**                                                                           **
** [/cover]                                                                  **
**                                                                           **
** Service ID      : 0x06                                                    **
**                                                                           **
** Sync/Async      : Synchronous                                             **
**                                                                           **
** Reentrancy      : Non-Reentrant                                           **
**                                                                           **
** Parameters (in) : None                                                    **
**                                                                           **
** Parameters (out): None                                                    **
**                                                                           **
** Return value    : None                                                    **
**                                                                           **
******************************************************************************/
void CanTrcv_17_W9255_MainFunction(void)
{
  uint8 ChannelIndex;
  Std_ReturnType DevError = E_OK;
  CanTrcv_TrcvModeType Mode = CANTRCV_TRCVMODE_STANDBY;
  Spi_SequenceType SpiSequenceUsed;
  uint8 Transceiver;
  uint16 DataField;
  uint16 DestBuf;
  boolean CanTrcvWuByBus;

/* Check for MCAL AUTOSAR Version is 422 and DET is ON */
  /* [cover parentID={3149615D-E28D-4da0-9BA1-CDA3CE293C86}]
  DET is ON
  [/cover] */
  #if ((MCAL_AR_VERSION == MCAL_AR_422) &&  \
        (CANTRCV_17_W9255_DEV_ERROR_DETECT == STD_ON))
  /* Check for driver initialization */
  /* [cover parentID={38D54421-DA0D-494f-9794-1985A282E17B}]
  Check for module initialization
  [/cover] */
  DevError = CanTrcv_17_W9255_lCheckUninitDet
             (CANTRCV_17_W9255_SID_MAINFUNCTION);
  /* [cover parentID={D2B0740F-176B-4771-B0E6-F214703C8D67}]
  Is the module initialized?
  [/cover] */
  if (DevError == E_OK)
  #endif
  {
    /*The CanTrcv_17_W9255_MainFunction scans all buses in STANDBY and
    SLEEP for wake up events and sets up a wake flag for
    performing these events. */

    /* [cover parentID={9F57965F-F561-4265-8060-E94D4D82E903}]
    Are all used channels checked and return status E_OK?
    [/cover] */
    /* loop for all the enabled transceiver channels */
    for(ChannelIndex = 0 ; ((ChannelIndex < CANTRCV_17_W9255_CHANNELS_USED) &&
                (DevError == E_OK)); ChannelIndex++)
    {
      SpiSequenceUsed =
              CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvSpiSequence;

      Transceiver =
                CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvChannelId;

      CanTrcvWuByBus =
        CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvWakeupByBusEnable;

      DevError = CanTrcv_17_W9255_lSpiBusyCheck(Transceiver);

      /* [cover parentID={A75B1D91-FC39-4982-9A59-C3F626F29719}]
      Is SPI channel idle?
      [/cover] */
      if(DevError == E_OK)
      {
        /* Read the current mode of the transceiver channel */
        CanTrcv_17_W9255_SourceBuffer[Transceiver] =
            CANTRCV_17_W9255_READ_MODE_CTRL;
        /* [cover parentID={ACE758F6-B41C-4cad-AD4D-9379E64BAB43}]
        Read current mode from MODE_CTRL register and update the return status
        [/cover] */
        DevError = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                      &CanTrcv_17_W9255_DestBuffer[Transceiver],
                      CANTRCV_17_W9255_SID_MAINFUNCTION,
                      (uint8)CANTRCV_17_W9255_DET_DISABLE);

        DestBuf = CanTrcv_17_W9255_DestBuffer[Transceiver];

        /* [cover parentID={ECFCD6AC-D51C-43fd-91D0-95FB15A020F2}]
        Is return status E_OK?
        [/cover] */
        if (DevError == E_OK)
        {
          DataField = DestBuf &
                      CANTRCV_17_W9255_EXTRACT_FOUR_BITS;
          /* [cover parentID={ACE758F6-B41C-4cad-AD4D-9379E64BAB43}]
          Read current mode from MODE_CTRL register
          [/cover] */
          if (DataField == CANTRCV_17_W9255_NORMAL)
          {
            Mode = CANTRCV_TRCVMODE_NORMAL;
          }
          else if (DataField == CANTRCV_17_W9255_STANDBY)
          {
            Mode = CANTRCV_TRCVMODE_STANDBY;
          }
          else
          {
            Mode = CANTRCV_TRCVMODE_SLEEP;
          }

          /* [cover parentID={65E10850-78AB-4aa9-8575-6E284701A2EE}]
          Is current mode STANDBY/SLEEP and bus enabled?
          [/cover] */
          /* Check if mode is Standby/Sleep and wakeup by bus is enabled */
          if ((Mode !=  CANTRCV_TRCVMODE_NORMAL) && (CanTrcvWuByBus == STD_ON))
          {
              DevError = CanTrcv_17_W9255_lPollWakeup (Transceiver,
                          SpiSequenceUsed);
          }
          else
          {
              DevError = E_OK;
          }

          CanTrcv_17_W9255_SpiBusyStatus[Transceiver] = 0U;
        }
      }
    }
  }
  return;
} /* End of CanTrcv_17_W9255_MainFunction function */
#endif
/* CanTrcv_17_W9255_ClearTrcvTimeoutFlag API  */
/******************************************************************************
** Traceability    : [cover parentID={32B45F33-7470-4943-9A4D-A8C4CBA6206C}] **
**                                                                           **
** Syntax          : Std_ReturnType  CanTrcv_17_W9255_ClearTrcvTimeoutFlag ( **
**                    const uint8 Transceiver)                               **
**                                                                           **
** Description     : This API clears the status of the timeout flag in the   **
**                   transceiver hardware. Since the configuration parameter **
**                   CanTrcvHwPnSupport is always TRUE, the availability of  **
**                   this API is not dependent on the configuration          **
**                   parameter. The timeout flag indicates whether or not    **
**                   the TLE9255W hardware has entered the Selective Sleep   **
**                   Sub-Mode at least once.                                 **
**                                                                           **
** [/cover]                                                                  **
**                                                                           **
** Service ID      : 0x0c                                                    **
**                                                                           **
** Sync/Async      : Synchronous                                             **
**                                                                           **
** Reentrancy      : Non Reentrant                                           **
**                                                                           **
** Parameters (in) : Transceiver - CAN transceiver to which API call has     **
**                                 to be applied                             **
**                                                                           **
** Parameters (out): None                                                    **
**                                                                           **
** Return value    : E_OK  : Will be returned, if the timeout flag is        **
**                           successfully cleared.                           **
**                   E_NOT_OK  : Will be returned, if the timeout flag could **
**                               not be cleared.                             **
**                                                                           **
******************************************************************************/
/* [cover parentID={3743404D-310C-4c85-9DDF-90CA1FBD8DA9}]
Dependency of the configuration parameter CanTrcvHwPnSupport on APIs
[/cover] */
Std_ReturnType  CanTrcv_17_W9255_ClearTrcvTimeoutFlag
(
  const uint8 Transceiver
)
{
  Spi_SequenceType SpiSequenceUsed;
  uint8 ChannelIndex;
  Std_ReturnType ReturnValue = E_NOT_OK;
  /* [cover parentID={D75E54E1-9A20-4d34-AAE4-3F0F04369E1C}]
  DET is ON
  [/cover] */
  #if (CANTRCV_17_W9255_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType DevError;
  /* [cover parentID={A2CBD802-70DB-4299-A282-2992FE89B0E7}]
  Check if the channel Id is valid
  [/cover] */
  /* If called with invalid network Id */
  DevError = CanTrcv_17_W9255_lCheckChannelId(Transceiver,
             CANTRCV_17_W9255_SID_CLEARTIMEOUTFLAG);
  /* [cover parentID={6B58BF0A-C450-4394-85FE-B12C4069B7A1}]
  Is network ID invalid?
  [/cover] */
  if (DevError == E_OK)
  #endif
  {
    ChannelIndex = CanTrcv_17_W9255_ChannelUsed[Transceiver];

    SpiSequenceUsed =
           CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvSpiSequence;

    ReturnValue = CanTrcv_17_W9255_lSpiBusyCheck(Transceiver);
    /* [cover parentID={5665E2D2-854E-4298-B5F2-95D609908A80}]
    Is SPI channel idle?
    [/cover] */
    if(ReturnValue == E_OK)
    {
      /* Clear the timeout flag */
      CanTrcv_17_W9255_SourceBuffer[Transceiver] =
          CANTRCV_17_W9255_CLEAR_CANTO_BIT;

      /* [cover parentID={B4843A69-05B9-446c-B3F6-F861F7C9EDC6}]
      Clear CANTO bit in the SWK_STAT register through SPI and
      update the return status
      [/cover] */
      ReturnValue = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                    &CanTrcv_17_W9255_DestBuffer[Transceiver],
                    CANTRCV_17_W9255_SID_CLEARTIMEOUTFLAG,
                    (uint8)CANTRCV_17_W9255_DET_DISABLE);

      CanTrcv_17_W9255_SpiBusyStatus[Transceiver] = 0U;
    }
  }
  /* [cover parentID={3B89D31B-777A-42a6-81BA-3CDEF5E26834}]
  Return status
  [/cover] */
  return ReturnValue;
}/* end of CanTrcv_17_W9255_ClearTrcvTimeoutFlag API  */

/* CanTrcv_17_W9255_ReadTrcvTimeoutFlag API */
/******************************************************************************
** Traceability    : [cover parentID={7C7B2282-9363-4006-9A17-59EE7EFA72E5}] **
**                                                                           **
** Syntax          : Std_ReturnType  CanTrcv_17_W9255_ReadTrcvTimeoutFlag (  **
**                     const uint8 Transceiver,                              **
**                     CanTrcv_17_W9255_TrcvFlagStateType * const FlagState) **
**                                                                           **
** Description     : This API reads the status of the timeout flag from the  **
**                   transceiver hardware. Since the configuration parameter **
**                   CanTrcvHwPnSupport is always TRUE, the availability of  **
**                   this API is not dependent on the configuration          **
**                   parameter. The timeout flag indicates whether or not    **
**                   the TLE9255W hardware has entered the Selective Sleep   **
**                   Sub-Mode at least once.                                 **
**                                                                           **
** [/cover]                                                                  **
**                                                                           **
** Service ID      : 0x0b                                                    **
**                                                                           **
** Sync/Async      : Synchronous                                             **
**                                                                           **
** Reentrancy      : Non Reentrant                                           **
**                                                                           **
** Parameters (in) : Transceiver - CAN transceiver to which API call has     **
**                                 to be applied                             **
**                                                                           **
** Parameters (out): FlagState - State of the timeout flag                   **
**                                                                           **
** Return value    : E_OK  : Will be returned, if status of the timeout flag **
**                           is successfully read                            **
**                   E_NOT_OK  : Will be returned, if status of the          **
**                               timeout flag could not be read              **
**                                                                           **
******************************************************************************/
Std_ReturnType  CanTrcv_17_W9255_ReadTrcvTimeoutFlag
(
  const uint8 Transceiver,
  CanTrcv_17_W9255_TrcvFlagStateType * const FlagState
)
{
  Spi_SequenceType SpiSequenceUsed;
  uint8 ChannelIndex;
  uint16 TimeoutStatus;
  Std_ReturnType ReturnValue = E_NOT_OK;

  /* [cover parentID={164AE2D1-6824-49c5-AD69-E3BE1163F016}]
  DET is ON
  [/cover] */
  #if (CANTRCV_17_W9255_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType DevError;

  /* [cover parentID={0E3065B6-7D5C-4012-9785-1E6FA875C8AE}]
  Check if the network ID is valid and update the return status
  [/cover] */
  /* Check for invalid network id */
  DevError = CanTrcv_17_W9255_lCheckChannelId(Transceiver,
             CANTRCV_17_W9255_SID_READTIMEOUTFLAG);

  /* [cover parentID={287D5ADB-0BB5-4849-8992-DAD31D9471D5}]
  Is return status E_OK?
  [/cover] */
  if (DevError == E_OK)
  {
    /* [cover parentID={2D11EC1B-9E62-4513-BE17-7121291A4D88}]
    Check if NULL pointer is passed
    [/cover] */
    /* Null pointer check */
    if(FlagState == NULL_PTR)
    {
      /* [cover parentID={5C594298-5665-4fb0-A197-7BF3E67609B3}]
      Report DET error CANTRCV_17_W9255_E_PARAM_POINTER and update
      return status
      [/cover] */
      (void)Det_ReportError(CANTRCV_17_W9255_MODULE_ID,
                      CANTRCV_17_W9255_INSTANCE_ID,
                      CANTRCV_17_W9255_SID_READTIMEOUTFLAG,
                      CANTRCV_17_W9255_E_PARAM_POINTER
                     );
      DevError = E_NOT_OK;
    }
  }

  /* [cover parentID={C370B2CE-F3B8-4664-8324-2810A35D4213}]
  Is return status E_OK?
  [/cover] */
  if (DevError == E_OK)
  #endif
  {
    ChannelIndex = CanTrcv_17_W9255_ChannelUsed[Transceiver];

    SpiSequenceUsed =
              CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvSpiSequence;

    ReturnValue = CanTrcv_17_W9255_lSpiBusyCheck(Transceiver);

    /* [cover parentID={15F14EFA-FF71-4d37-8F75-A46B8683BBD2}]
    Is SPI channel idle?
    [/cover] */
    if(ReturnValue == E_OK)
    {
      /* Read SWK_STAT register */
      CanTrcv_17_W9255_SourceBuffer[Transceiver] =
          CANTRCV_17_W9255_READ_SWK_STAT;

      ReturnValue = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                    &CanTrcv_17_W9255_DestBuffer[Transceiver],
                    CANTRCV_17_W9255_SID_READTIMEOUTFLAG,
                    (uint8)CANTRCV_17_W9255_DET_DISABLE);

      /* [cover parentID={C42B0EA0-4960-44df-AA34-C5577ABFFBAD}]
      Update flag state
      [/cover] */
      if (ReturnValue == E_OK)
      {
        /* [cover parentID={7CCC3280-C548-4795-B5A4-1F62702D955B}]
        Fetch the value of CANTO bit from the register
        [/cover] */
        /* Store Timeout flag status */
        TimeoutStatus = (CanTrcv_17_W9255_DestBuffer[Transceiver] >>
              CANTRCV_17_W9255_SHIFT_BY_TWO) & (uint16)CANTRCV_17_W9255_SET_REG;

        /* [cover parentID={3497AF84-A9C6-4909-8915-D63F940EE278}]
        Is CANTO bit set?
        [/cover] */
        /* Check if the flag is set */
        if(TimeoutStatus == CANTRCV_17_W9255_SET_REG)
        {
          /* [cover parentID={3D07F8C8-1FE2-4346-8487-716F1C0C55FB}]
          Set Flag state to CANTRCV_17_W9255_FLAG_SET
          [/cover] */
          *FlagState = CANTRCV_17_W9255_FLAG_SET;
        }
        else
        {
          /* [cover parentID={9ED942FD-3A2C-48bb-9941-5EF6C8385B20}]
          Set flag state to CANTRCV_17_W9255_FLAG_CLEARED
          [/cover] */
          *FlagState = CANTRCV_17_W9255_FLAG_CLEARED;
        }
      }
      CanTrcv_17_W9255_SpiBusyStatus[Transceiver] = 0U;
    }
  }
  /* [cover parentID={36B9196D-328A-457e-BC92-16D3C55F8DA7}]
  Return status
  [/cover] */
  return ReturnValue;
}/* end of CanTrcv_17_W9255_ReadTrcvTimeoutFlag API */

/* CanTrcv_17_W9255_ReadTrcvSilenceFlag API */
/******************************************************************************
** Traceability    : [cover parentID={41407590-1BC3-4a39-8ECC-8E754C0D8F12}] **
**                                                                           **
** Syntax          : Std_ReturnType  CanTrcv_17_W9255_ReadTrcvSilenceFlag (  **
**                     const uint8 Transceiver,                              **
**                     CanTrcv_17_W9255_TrcvFlagStateType * const FlagState) **
**                                                                           **
** Description     : This API reads the status of the silence flag from the  **
**                   transceiver hardware. Since the configuration parameter **
**                   CanTrcvHwPnSupport is always TRUE, the availability of  **
**                   this API is not dependent on the configuration          **
**                   parameter. The silence flag, if set, indicates that     **
**                   there is no communication on the CAN bus for a specified**
**                   period of time (0.6 - 1.2 seconds). It helps to identify**
**                   whether or not the TLE9255W hardware is in the          **
**                   Selective Sleep Sub-Mode.                               **
**                                                                           **
** [/cover]                                                                  **
**                                                                           **
** Service ID      : 0x0d                                                    **
**                                                                           **
** Sync/Async      : Synchronous                                             **
**                                                                           **
** Reentrancy      : Non Reentrant                                           **
**                                                                           **
** Parameters (in) : Transceiver - CAN transceiver to which API call has     **
**                                 to be applied                             **
**                                                                           **
** Parameters (out): FlagState - State of the silence flag                   **
**                                                                           **
** Return value    : E_OK  : Will be returned, if status of the silence flag **
**                           is successfully read                            **
**                   E_NOT_OK  : Will be returned, if status of the silence  **
**                               flag could not be read                      **
**                                                                           **
******************************************************************************/
Std_ReturnType  CanTrcv_17_W9255_ReadTrcvSilenceFlag
(
  const uint8 Transceiver,
  CanTrcv_17_W9255_TrcvFlagStateType * const FlagState
)
{
  Spi_SequenceType SpiSequenceUsed;
  uint8 ChannelIndex;
  uint16 SilenceFlag;
  Std_ReturnType ReturnValue = E_NOT_OK;

  /* [cover parentID={2533B0DF-BA88-4470-8662-4C9C38930A12}]
  DET is ON
  [/cover] */
  #if (CANTRCV_17_W9255_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType DevError;

  /* [cover parentID={DCF0F8EB-49F4-429c-963F-999BF3BD045A}]
  Check if the channel ID is valid and update the return status
  [/cover] */
  /* Check for invalid network id */
  DevError = CanTrcv_17_W9255_lCheckChannelId(Transceiver,
             CANTRCV_17_W9255_SID_READSILENCEFLAG);

  /* [cover parentID={9534743A-D698-44ca-8779-1E0536A5FD41}]
  Is return status E_OK?
  [/cover] */
  if (DevError == E_OK)
  {
    /* [cover parentID={085DABE1-9BB9-4def-AD0D-3A1E894CAA5C}]
    Check if NULL pointer is passed
    [/cover] */
    /* Null pointer check */
    if(FlagState == NULL_PTR)
    {
      /* [cover parentID={5E4361F7-DFE0-4258-897B-8BC4F5719F74}]
      Report DET error CANTRCV_17_W9255_E_PARAM_POINTER and
      update the return status
      [/cover] */
      (void)Det_ReportError(CANTRCV_17_W9255_MODULE_ID,
                      CANTRCV_17_W9255_INSTANCE_ID,
                      CANTRCV_17_W9255_SID_READSILENCEFLAG,
                      CANTRCV_17_W9255_E_PARAM_POINTER
                     );
      DevError = E_NOT_OK;
    }
  }

  /* [cover parentID={242AED07-650D-46f9-8AA4-6F522D11F97F}]
  Is return status E_OK?
  [/cover] */
  if (DevError == E_OK)
  #endif
  {
    ChannelIndex = CanTrcv_17_W9255_ChannelUsed[Transceiver];

    SpiSequenceUsed =
            CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvSpiSequence;

    ReturnValue = CanTrcv_17_W9255_lSpiBusyCheck(Transceiver);

    /* [cover parentID={20615880-347A-4278-87DB-56BAE4BEDEE8}]
    Is SPI channel idle?
    [/cover] */
    if(ReturnValue == E_OK)
    {
      /* Read SWK_STAT register */
      CanTrcv_17_W9255_SourceBuffer[Transceiver] =
          CANTRCV_17_W9255_READ_SWK_STAT;
      /* [cover parentID={81557054-F58D-40fa-840C-133C81F822D3}]
      Fetch the value of CANSIL bit from the register
      [/cover] */
      ReturnValue = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                    &CanTrcv_17_W9255_DestBuffer[Transceiver],
                    CANTRCV_17_W9255_SID_READSILENCEFLAG,
                    (uint8)CANTRCV_17_W9255_DET_DISABLE);

      /* [cover parentID={37AAC141-6186-44de-95A6-FB8267695219}]
      Update flag state
      [/cover] */
      if (ReturnValue == E_OK)
      {
        /* Store Silence flag status */
        SilenceFlag = (CanTrcv_17_W9255_DestBuffer[Transceiver] >>
                 CANTRCV_17_W9255_SET_REG) & (uint16) CANTRCV_17_W9255_SET_REG;

        /* [cover parentID={2995F79A-F70A-4def-99E1-6E2F7A3E27E7}]
        Is CANSIL bit set?
        [/cover] */
        /* Check if Silence flag is set */
        if(SilenceFlag == CANTRCV_17_W9255_SET_REG)
        {
          /* [cover parentID={37AAC141-6186-44de-95A6-FB8267695219}]
          Update flag state
          [/cover] */
          /* [cover parentID={527F49D0-B96E-4e29-9B7A-5107C8B64A26}]
          Set Flag state to CANTRCV_17_W9255_FLAG_SET
          [/cover] */
          *FlagState = CANTRCV_17_W9255_FLAG_SET;
        }
        else
        {
          /* [cover parentID={37AAC141-6186-44de-95A6-FB8267695219}]
          Update flag state
          [/cover] */
          /* [cover parentID={F64F42B3-7BEA-4e92-8B06-E003E8D68CA6}]
          Set flag state to CANTRCV_17_W9255_FLAG_CLEARED
          [/cover] */
          *FlagState = CANTRCV_17_W9255_FLAG_CLEARED;
        }
      }
      CanTrcv_17_W9255_SpiBusyStatus[Transceiver] = 0U;
    }
  }
  /* [cover parentID={13469C1B-C461-4028-9BCD-267CC45D7234}]
  Return status
  [/cover] */
  return ReturnValue;
}/* end of CanTrcv_17_W9255_ReadTrcvSilenceFlag API */
/* CanTrcv_17_W9255_ClearTrcvWufFlag API  */
/******************************************************************************
** Traceability    : [cover parentID={CCFE19EC-82B1-45cd-985C-6F7E753C7597}] **
**                                                                           **
** Syntax          : Std_ReturnType  CanTrcv_17_W9255_ClearTrcvWufFlag (     **
**                     const uint8 Transceiver)                              **
**                                                                           **
** Description     : This API clears the WUF flag in the transceiver         **
**                   hardware. Since the configuration parameter             **
**                   CanTrcvHwPnSupport is always TRUE, the availability of  **
**                   this API is not dependent on the configuration          **
**                   parameter.                                              **
**                                                                           **
** [/cover]                                                                  **
**                                                                           **
** Service ID      : 0x0a                                                    **
**                                                                           **
** Sync/Async      : Synchronous                                             **
**                                                                           **
** Reentrancy      : Reentrant for different transceivers                    **
**                                                                           **
** Parameters (in) : Transceiver - CAN transceiver to which API call has     **
**                                 to be applied                             **
**                                                                           **
** Parameters (out): None                                                    **
**                                                                           **
** Return value    : E_OK  : will be returned if the WUF flag has been       **
**                           cleared                                         **
**                   E_NOT_OK  : will be returned if the WUF flag has not    **
**                               been cleared or a development error occurred**
**                                                                           **
******************************************************************************/
Std_ReturnType  CanTrcv_17_W9255_ClearTrcvWufFlag
(
  const uint8 Transceiver
)
{
  Spi_SequenceType SpiSequenceUsed;
  uint8 ChannelIndex;
  Std_ReturnType ReturnValue = E_NOT_OK;
  /* [cover parentID={07B550EE-203F-4568-AF31-36DA1676C2E0}]
  DET is ON
  [/cover] */
  #if (CANTRCV_17_W9255_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType DevError;
  /* [cover parentID={D6DC9D39-1E3F-4cc0-840A-7C6C2AC2F71E}]
  Check if the transceiver is initialized and update the return status
  [/cover] */
  /* Check for module initialization */
  DevError = CanTrcv_17_W9255_lCheckUninitDet
             (CANTRCV_17_W9255_SID_CLEARWUFFLAG);
  /* [cover parentID={39AEBD8C-677E-4db5-BB39-EDE20DC18DA1}]
  Is the transceiver initialized?
  [/cover] */
  if (DevError == E_OK)
  {
    /* [cover parentID={ADF85660-8A95-48e3-B0DA-A4CA21EAF91D}]
    Check for valid transceiver ID and update the return status
    [/cover] */
    /* Check for valid channel Id */
    DevError = CanTrcv_17_W9255_lCheckChannelId(Transceiver,
               CANTRCV_17_W9255_SID_CLEARWUFFLAG);
  }

  /* [cover parentID={CBA74FA7-E434-4180-B5FF-AAA04BA72242}]
  Is return status E_OK?
  [/cover] */
  if (DevError == E_OK)
  #endif
  {
    ChannelIndex = CanTrcv_17_W9255_ChannelUsed[Transceiver];

    SpiSequenceUsed =
        CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvSpiSequence;

    ReturnValue = CanTrcv_17_W9255_lSpiBusyCheck(Transceiver);

    /* [cover parentID={BB8B942F-4908-49c3-A219-517FE44E51F5}]
    Is SPI channel idle?
    [/cover] */
    if(ReturnValue == E_OK)
    {
      /* Read WAKE_STAT register */
      CanTrcv_17_W9255_SourceBuffer[Transceiver] =
          CANTRCV_17_W9255_CLEAR_WUF_BIT;
      /* [cover parentID={862E8A85-CD9A-4568-9BB7-3F6E9BEAFEAC}]
      Clear WUF flag and update the return status
      [/cover] */
      ReturnValue = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                    &CanTrcv_17_W9255_DestBuffer[Transceiver],
                    CANTRCV_17_W9255_SID_CLEARWUFFLAG,
                    (uint8)CANTRCV_17_W9255_REPORT_DET);

      /* [cover parentID={3FC85D4C-0AE3-4b3b-844F-8A3A18AE08BC}]
      Is return status E_OK?
      [/cover] */
      if (ReturnValue == E_OK)
      {
          /* [cover parentID={B54EA0BA-F79D-4565-B0F8-26BF320ED73E}]
          Inform CanIf that the wakeup flag has been cleared for the
          requested transceiver ID
          [/cover] */
          /* Informing CanIf that the wakeup frame flag has been
            cleared for the requested transceiver */
        CanIf_ClearTrcvWufFlagIndication(Transceiver);
      }
      CanTrcv_17_W9255_SpiBusyStatus[Transceiver] = 0U;
    }
  }
  /* [cover parentID={A61D3364-8381-4278-BCD7-742719D4C64E}]
  Return status
  [/cover] */
  return ReturnValue;
}/* end of CanTrcv_17_W9255_ClearTrcvWufFlag API  */
/* CanTrcv_17_W9255_SetPNActivationState API */
/******************************************************************************
** Traceability    : [cover parentID={1B646EBE-623F-4934-920E-ABAC4375BCA0}] **
**                                                                           **
** Syntax          : Std_ReturnType  CanTrcv_17_W9255_SetPNActivationState(  **
**                   const CanTrcv_17_W9255_PNActivationType ActivationState)**
**                                                                           **
** Description     : This API enables/disables selective wake-up             **
**                   functionality of of all those channels which have       **
**                   enabled PN in their configuration.                      **
**                                                                           **
** [/cover]                                                                  **
**                                                                           **
** Service ID      : 0x0f                                                    **
**                                                                           **
** Sync/Async      : Synchronous                                             **
**                                                                           **
** Reentrancy      : Non Reentrant                                           **
**                                                                           **
** Parameters (in) : ActivationState - CANTRCV_17_W9255_PN_ENABLED: PN       **
**                                     wakeup functionality in CanTrcv shall **
**                                     be enabled                            **
**                                     CANTRCV_17_W9255_PN_DISABLED: PN      **
**                                     wakeup functionality in CanTrcv shall **
**                                     be disabled                           **
** Parameters (out): None                                                    **
**                                                                           **
** Return value    : E_OK  : Will be returned, if the PN has been changed    **
**                       to the requested configuration                      **
**                   E_NOT_OK  : Will be returned, if the PN configuration   **
**                          change has failed. The previous configuration    **
**                          has not been changed                             **
**                                                                           **
******************************************************************************/
Std_ReturnType  CanTrcv_17_W9255_SetPNActivationState
(
  const CanTrcv_17_W9255_PNActivationType ActivationState
)
{
  uint8 ChannelIndex;
  Std_ReturnType DevError;
  Spi_SequenceType SpiSequenceUsed;
  uint16 DataField;
  uint8 ChannelId;
  uint8 PnIndex;

  /* [cover parentID={CB3EBCE2-B393-4bc7-B2CA-ABBA7CCF0ABD}]
DET is OFF
[/cover] */
#if (CANTRCV_17_W9255_DEV_ERROR_DETECT == STD_OFF)
  DevError = E_OK;
#endif
  /* [cover parentID={A14D14BD-3FF6-4b6d-9D7D-FCC17532A731}]
  DET is ON
  [/cover] */
  #if (CANTRCV_17_W9255_DEV_ERROR_DETECT == STD_ON)

  /* [cover parentID={16599870-7448-44ef-8B53-8ADCDB60E945}]
  Check for init status and update the return status
  [/cover] */
  /* Check for driver initialization */
  DevError = CanTrcv_17_W9255_lCheckUninitDet(CANTRCV_17_W9255_SID_SETPNSTATE);

  /* [cover parentID={BA76F2C9-94FA-47f3-B753-F038C0E301DC}]
  Is return status E_OK?
  [/cover] */
  if (DevError == E_OK)
  #endif
  {
    /* [cover parentID={268C9EC3-19CD-4114-B2E5-91568F6847FF}]
    Are all used channels checked and return status E_OK?
    [/cover] */
    /* loop for all the enabled transceiver channels */
    for(ChannelIndex = 0 ; ((ChannelIndex < CANTRCV_17_W9255_CHANNELS_USED) &&
            (DevError == E_OK)); ChannelIndex++)
    {
      SpiSequenceUsed =
              CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvSpiSequence;

      ChannelId =
                  CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvChannelId;

      PnIndex = CanTrcv_17_W9255_PnConfigured[ChannelId];

      DevError = CanTrcv_17_W9255_lSpiBusyCheck(ChannelId);

      /* [cover parentID={56F05D57-7D89-421f-9356-73F12C127574}]
      Is SPI channel idle?
      [/cover] */
      if(DevError == E_OK)
      {
        /* [cover parentID={8AD6AFDE-FA2B-48b0-A628-3F20E5A6D505}]
        Set PN state as requested
        [/cover] */
        /* Check if PN is enabled for the respective channel */
        if(PnIndex != CANTRCV_17_W9255_PN_NOT_CONFIGURED)
        {
          /* Read current SWK state */
          CanTrcv_17_W9255_SourceBuffer[ChannelId] =
              CANTRCV_17_W9255_READ_SWK_CTRL_2;
          DevError = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                        &CanTrcv_17_W9255_DestBuffer[ChannelId],
                        CANTRCV_17_W9255_SID_SETPNSTATE,
                        (uint8)CANTRCV_17_W9255_DET_DISABLE);

          /* [cover parentID={7EA0554A-9284-4da7-BDB3-8F21F6612792}]
          Update PN state as requested
          [/cover] */
          if (DevError == E_OK)
          {
            /* [cover parentID={298450DA-1296-4be2-AFA5-9848502D5B43}]
            Is Activation state set to CANTRCV_17_W9255_PN_ENABLED ?
            [/cover] */
            /* If asked for PN enable */
            if (ActivationState == CANTRCV_17_W9255_PN_ENABLED)
            {
              /* Enable SWK_EN bit in SWK_CTRL_2 register */
              DataField = CanTrcv_17_W9255_DestBuffer[ChannelId] &
                          CANTRCV_17_W9255_EXTRACT_DATA_FIELD;

              /* [cover parentID={BC59453E-B0BE-4ba9-A446-077CAF7A737D}]
              Enable PN for the channel by enabling SWK_EN bit in SWK_CTRL_2
              register through SPI and update return status
              [/cover] */
              CanTrcv_17_W9255_SourceBuffer[ChannelId] |=
                  CANTRCV_17_W9255_WRITE_SWK_CTRL_2 | DataField |
                  CANTRCV_17_W9255_ENABLE_SWK_EN;

              DevError = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                          &CanTrcv_17_W9255_DestBuffer[ChannelId],
                          CANTRCV_17_W9255_SID_SETPNSTATE,
                          (uint8)CANTRCV_17_W9255_DET_DISABLE);
            }
            /* [cover parentID={FCC8DD00-82EE-4825-BB42-5440FAA30CE6}]
            Is Activation state set to CANTRCV_17_W9255_PN_DISABLED ?
            [/cover] */
            else if(ActivationState == CANTRCV_17_W9255_PN_DISABLED)
            {
              /* Disable SWK_EN bit in SWK_CTRL_2 register */
              DataField = CanTrcv_17_W9255_DestBuffer[ChannelId] &
                          CANTRCV_17_W9255_DISABLE_SWK_EN;
              /* [cover parentID={BABA4486-D0DF-4f4b-BD50-FC9C41AE0950}]
              Disable PN for the channel by disabling SWK_EN bit in
              SWK_CTRL_2 register through SPI and update return status
              [/cover] */
              CanTrcv_17_W9255_SourceBuffer[ChannelId] |=
                  CANTRCV_17_W9255_WRITE_SWK_CTRL_2 | DataField;

              DevError = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                          &CanTrcv_17_W9255_DestBuffer[ChannelId],
                          CANTRCV_17_W9255_SID_SETPNSTATE,
                          (uint8)CANTRCV_17_W9255_DET_DISABLE);
            }
            else
            {
              /* [cover parentID={DCE4FC9F-646C-4360-A145-BB0CB43EF447}]
              Update return status as E_NOT_OK
              [/cover] */
              DevError = E_NOT_OK;
            }
          }
        }
        CanTrcv_17_W9255_SpiBusyStatus[ChannelId] = 0U;
      }
    }
  }

  /* [cover parentID={1FA5991B-F867-49f0-BA4C-F1E798066D77}]
  Return status
  [/cover] */
  return DevError;
}/* end of CanTrcv_17_W9255_SetPNActivationState API */
/* CanTrcv_17_W9255_GetTrcvSystemData API */
/******************************************************************************
** Traceability    : [cover parentID={06115817-4AEE-4083-8610-BFA1E7754A3C}] **
**                                                                           **
** Syntax          : Std_ReturnType  CanTrcv_17_W9255_GetTrcvSystemData(     **
**                   const uint8 Transceiver,                                **
**                   uint32 * const TrcvSysData)                             **
**                                                                           **
** Description     : This API reads the transceiver status data and returns  **
**                   it through parameter TrcvSysData. Since the             **
**                   configuration parameter CanTrcvHwPnSupport is always    **
**                   TRUE, the availability of this API is not dependent on  **
**                   the configuration parameter.                            **
**                                                                           **
** [/cover]                                                                  **
**                                                                           **
** Service ID      : 0x09                                                    **
**                                                                           **
** Sync/Async      : Synchronous                                             **
**                                                                           **
** Reentrancy      : Non Reentrant                                           **
**                                                                           **
** Parameters (in) : Transceiver - CAN transceiver to which API call has     **
**                                 to be applied                             **
**                                                                           **
** Parameters(out) : TrcvSysData - This parameter holds the selective wake   **
**                                 status, error status, transceiver status  **
**                                 and wake-up event status information. The **
**                                 first 8 bits of LSB contain the data      **
**                                 stored in TRANS_STAT register, the next 8 **
**                                 bits contain the data in SWK_ECNT_STAT    **
**                                 register, the next 8 bits depict the data **
**                                 stored in WAKE_STAT register and the last **
**                                 8 bits contain the data stored in SWK_STAT**
**                                 register                                  **
**                                                                           **
** Return value    : E_OK  : will be returned if the transceiver status is   **
**                           successfully read                               **
**                   E_NOT_OK  : will be returned if the transceiver status  **
**                               data is not available or a development error**
**                               occurs                                      **
**                                                                           **
******************************************************************************/
Std_ReturnType  CanTrcv_17_W9255_GetTrcvSystemData
(
  const uint8 Transceiver,
  uint32 * const TrcvSysData
)
{
  Spi_SequenceType SpiSequenceUsed;

  /*Registers to be read */
  uint16 RegisterArray[CANTRCV_17_W9255_REGISTER_COUNT] =
  { CANTRCV_17_W9255_READ_TRANS_STAT, CANTRCV_17_W9255_READ_SWK_ECNT_STAT,
    CANTRCV_17_W9255_READ_WAKE_STAT, CANTRCV_17_W9255_READ_SWK_STAT
  };

  uint16 DataField;
  uint8 ChannelIndex;
  uint8 LoopIndex;
  Std_ReturnType DevError;
  uint32 Data = 0;
  uint32 Status = 0;

  /* [cover parentID={82DC47C7-168F-4205-9747-F74DCC81AA8A}]
  DET is ON
  [/cover] */
  #if (CANTRCV_17_W9255_DEV_ERROR_DETECT == STD_ON)

  /* [cover parentID={766EA6A8-C65A-4dc0-8FFC-5EC07F58468D}]
  Check for module initialization status and update return status
  [/cover] */
  /* Check for driver initialization */
  DevError = CanTrcv_17_W9255_lCheckUninitDet
             (CANTRCV_17_W9255_SID_GETSYSTEMDATA);
  /* [cover parentID={2BF34A4C-FE2C-42d9-851F-B0EFD726AA94}]
  Is return status E_OK?
  [/cover] */
  if (DevError == E_OK)
  {
    /* [cover parentID={85540D2B-7596-4d00-8D08-E4ABC178DF0E}]
    Check for valid transceiver ID and update the return status
    [/cover] */
    /* Check for valid channel Id */
    DevError = CanTrcv_17_W9255_lCheckChannelId(Transceiver,
               CANTRCV_17_W9255_SID_GETSYSTEMDATA);
  }
  /* [cover parentID={3B5CD699-677A-4dd4-A9EE-F25A2C688346}]
  Is return status E_OK?
  [/cover] */
  if (DevError == E_OK)
  {
    /* [cover parentID={3B303845-A8AB-4cf1-A968-5AC0AE163790}]
    Is NULL pointer passed as parameter?
    [/cover] */
    /* Null pointer check */
    if (TrcvSysData == NULL_PTR)
    {
      /* [cover parentID={FD85F79F-39E2-4ad4-A7FD-449060016F5E}]
      Report CANTRCV_17_W9255_E_PARAM_POINTER error to DET and update
      the return status
      [/cover] */
      /* API called with null pointer parameter. Report error to DET. */
      (void)Det_ReportError(
        CANTRCV_17_W9255_MODULE_ID,
        CANTRCV_17_W9255_INSTANCE_ID,
        CANTRCV_17_W9255_SID_GETSYSTEMDATA,
        CANTRCV_17_W9255_E_PARAM_POINTER
      );

      DevError = E_NOT_OK;
    }
  }

  /* [cover parentID={F0025C28-18EF-447d-BC7B-77498829CC92}]
  Is return status E_OK?
  [/cover] */
  if (DevError == E_OK)
  #endif
  {
      DevError = CanTrcv_17_W9255_lSpiBusyCheck(Transceiver);

    /* [cover parentID={1E1D4348-A90A-4cae-96DC-5F1515818764}]
    Is SPI channel idle?
    [/cover] */
    if(DevError == E_OK)
    {
      /* [cover parentID={047C6DEF-BFFC-4bfb-9EC4-6D5F1A176664}]
      Read register set
      [/cover] */
      for( LoopIndex = 0 ; (LoopIndex < CANTRCV_17_W9255_REGISTER_COUNT) &&
           (DevError == E_OK) ; LoopIndex++ )
      {
        ChannelIndex = CanTrcv_17_W9255_ChannelUsed[Transceiver];

        SpiSequenceUsed =
             CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvSpiSequence;


        CanTrcv_17_W9255_SourceBuffer[Transceiver] = RegisterArray[LoopIndex];

        DevError = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                      &CanTrcv_17_W9255_DestBuffer[Transceiver],
                      CANTRCV_17_W9255_SID_GETSYSTEMDATA,
                      (uint8)CANTRCV_17_W9255_REPORT_DET);

        /* [cover parentID={F41C904A-B02C-4cf4-80A4-995EAC709948}]
        Is return status E_OK?
        [/cover] */
        if (DevError == E_OK)
        {
          DataField = (CanTrcv_17_W9255_DestBuffer[Transceiver] &
                       CANTRCV_17_W9255_EXTRACT_DATA_FIELD);
          Data = (uint32) DataField;
          Status |= (Data <<
                     (CANTRCV_17_W9255_SHIFT_EIGHT * (uint32)LoopIndex));
        }
      }
      /* TrcvSysData holds the value of following status registers
       * ERR_STAT, WAKE_STAT, SWK_STAT and TRANS_STAT
       */
      /* [cover parentID={CEB7B805-3984-40c1-887F-753D02FAA0E1}]
      Update the pointer with the buffer value
      [/cover] */
      *TrcvSysData = Status;
      CanTrcv_17_W9255_SpiBusyStatus[Transceiver] = 0U;
    }
  }
  /* [cover parentID={53903198-DEB6-4187-BDEB-1CE2336042B7}]
  Return status
  [/cover] */
  return DevError;
}/* end of CanTrcv_17_W9255_GetTrcvSystemData API */
/* CanTrcv_17_W9255_CheckWakeFlag API  */
/*******************************************************************************
** Traceability    : [cover parentID={DF237DE8-DE02-4f87-82C4-D984C5833742}]  **
**                                                                            **
** Syntax          : Std_ReturnType  CanTrcv_17_W9255_CheckWakeFlag (         **
**                   const uint8 Transceiver )                                **
**                                                                            **
** Description     : This API checks the status of the wake-up flags from the **
**                   transceiver hardware and informs the CanIf with the      **
**                   callback notification CanIf_CheckTrcvWakeFlagIndication, **
**                   that the wake flags of the CAN transceiver with the      **
**                   corresponding Transceiver ID have been checked.          **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID      : 0x0e                                                     **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : Transceiver - CAN transceiver to which API call has      **
**                                 to be applied                              **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK  : Will be returned, if the request for checking the**
**                          wakeup flag has been accepted                     **
**                   E_NOT_OK  : Will be returned, if the request for checking**
**                          the wakeup flag has not been accepted,  wake up by**
**                          bus is disabled, development error occurred or if **
**                          SPI communication fails.                          **
**                                                                            **
*******************************************************************************/
Std_ReturnType  CanTrcv_17_W9255_CheckWakeFlag
(
  const uint8 Transceiver
)
{
  Std_ReturnType ReturnValue = E_NOT_OK;
  Spi_SequenceType SpiSequenceUsed;
  uint8 ChannelIndex ;
  boolean CanTrcvWuByBus;
  /* [cover parentID={68EEC133-79B8-4f66-93A5-DACE78098E2A}]
  DET is ON
  [/cover] */
  #if (CANTRCV_17_W9255_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType DevError;
  /* [cover parentID={C7DE93DB-D1F7-4ddf-8E50-CC45BCA3FC54}]
  Check if the channel ID is valid and update the return status
  [/cover] */
  /* Check for valid channel Id */
  DevError = CanTrcv_17_W9255_lCheckChannelId(Transceiver,
             CANTRCV_17_W9255_SID_CHECKWAKEFLAG);
  /* [cover parentID={BEAD1F20-2ABD-44e0-A2AF-4175EF4FB588}]
  Is return status E_OK?
  [/cover] */
  if (DevError == E_OK)
  #endif
  {
    ChannelIndex = CanTrcv_17_W9255_ChannelUsed[Transceiver];

    SpiSequenceUsed =
             CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvSpiSequence;

    CanTrcvWuByBus =
         CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvWakeupByBusEnable;
    /* [cover parentID={2A59BED6-1A62-48dc-AAF9-FEC78D9131D5}]
    Is wake up by bus enabled?
    [/cover] */
    if(CanTrcvWuByBus == STD_ON)
    {
      ReturnValue = CanTrcv_17_W9255_lSpiBusyCheck(Transceiver);
      /* [cover parentID={D020EB4D-3999-48e5-808E-825E3EEA8315}]
       Check if SPI channel status is idle
       [/cover] */
      if(ReturnValue == E_OK)
      {
        /* [cover parentID={A4F1A551-94A2-49e2-94CF-4ED022B394F1}]
        Check the status of wake flags from the WAKE_STAT register and update
        the return status
        [/cover] */
        /* Check the status of wake flags in the WAKE_STAT register */
        CanTrcv_17_W9255_SourceBuffer[Transceiver] =
            CANTRCV_17_W9255_READ_WAKE_STAT;
        ReturnValue = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                      &CanTrcv_17_W9255_DestBuffer[Transceiver],
                      CANTRCV_17_W9255_SID_CHECKWAKEFLAG,
                      (uint8)CANTRCV_17_W9255_DET_DISABLE);

        CanTrcv_17_W9255_SpiBusyStatus[Transceiver] = 0U;
        /* [cover parentID={22CFCD73-72E8-4f5c-92AF-DFE6656C4EE3}]
        Is return status E_OK?
        [/cover] */
        if(ReturnValue == E_OK)
        {
          /* [cover parentID={D3447120-8874-4a71-A103-11114C7053A1}]
          Inform CanIf that the wake flags of the CAN Transceiver with the
          corresponding Transceiver Id have been checked
          [/cover] */
          /* Inform CanIf that the wake flags of the CAN Transceiver with the
          corresponding Transceiver Id have been checked */
          CanIf_CheckTrcvWakeFlagIndication(Transceiver);
        }
      }
    }
  }
  /* [cover parentID={51AA21FF-E2C1-42ae-8045-BFD7A9276AB9}]
  Return status
  [/cover] */
  return ReturnValue;
}/* end of CanTrcv_17_W9255_CheckWakeFlag API  */
/******************************************************************************
**                      Private Function Definitions                         **
******************************************************************************/

#if (CANTRCV_17_W9255_GENERAL_WAKE_UP_SUPPORT ==   \
CANTRCV_17_W9255_WAKE_UP_BY_INTERRUPT)
/******************************************************************************
** Traceability    : [cover parentID={CFCD600A-D519-443a-B82A-3D4DAD13BAF9}] **
**                                                                           **
** Syntax          : static Std_ReturnType CanTrcv_17_W9255_lCheckWakeup     **
**                                  (const uint8 Transceiver)                **
**                                                                           **
** Description     :  This function detects valid wakeup on the channel      **
**                                                                           **
** [/cover]                                                                  **
**                                                                           **
** Service ID      :  NA                                                     **
**                                                                           **
** Sync/Async      :  Synchronous                                            **
**                                                                           **
** Reentrancy      :  Non-Reentrant                                          **
**                                                                           **
** Parameters (in) :  Transceiver - CAN transceiver to which API call has    **
**                                to be applied.                             **
**                                                                           **
** Parameters (out):  none                                                   **
**                                                                           **
** Return value    :  E_OK: Channel has been checked for valid wakeup events **
**                          successfully                                     **
**                    E_NOT_OK: Failed to check the Channel for valid wakeup **
**                              events                                       **
**                                                                           **
******************************************************************************/
static Std_ReturnType CanTrcv_17_W9255_lCheckWakeup(const uint8 Transceiver)
{
  Std_ReturnType ReturnValue = E_NOT_OK;
  uint8 ChannelIndex = CanTrcv_17_W9255_ChannelUsed[Transceiver];
  boolean CanTrcvWuByBus =
         CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvWakeupByBusEnable;
  Spi_SequenceType SpiSequenceUsed =
              CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvSpiSequence;
  EcuM_WakeupSourceType WakeupSourceRef =
      CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvWakeupSourceRef;
  uint16 DestBuf;

  /* [cover parentID={7D572726-CFF3-419a-98E5-B827E273F298}]
  Is wake up by bus enabled?
  [/cover] */
  if (CanTrcvWuByBus == STD_ON)
  {
    /* Read WAKE_STAT register */
    CanTrcv_17_W9255_SourceBuffer[Transceiver] =
        CANTRCV_17_W9255_READ_WAKE_STAT;
    ReturnValue = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                  &CanTrcv_17_W9255_DestBuffer[Transceiver],
                  CANTRCV_17_W9255_SID_CHECKWAKEUP,
                  (uint8)CANTRCV_17_W9255_DET_DISABLE);

    DestBuf = CanTrcv_17_W9255_DestBuffer[Transceiver];

    /* [cover parentID={B46974A3-27FB-42d0-A004-FA7B556C9AE1}]
    Is return status E_OK?
    [/cover] */
    if (ReturnValue == E_OK)
    {
      /* Read the status of SYSERR flag */
      CanTrcv_17_W9255_SourceBuffer[Transceiver] =
          CANTRCV_17_W9255_READ_SWK_STAT;
      ReturnValue = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                    &CanTrcv_17_W9255_DestBuffer[Transceiver],
                    CANTRCV_17_W9255_SID_CHECKWAKEUP,
                    (uint8)CANTRCV_17_W9255_DET_DISABLE);
    }

    /* [cover parentID={2813F11A-6CF3-461f-B9B1-8A1A046164CC}]
    Is return status E_OK?
    [/cover] */
    if (ReturnValue == E_OK)
    {
      /* [cover parentID={ADE600E4-4D57-41e9-B53F-E098A1260EF9}]
      Is wake detected?
      [/cover] */
      /* Check if wake is detected */
      if(((DestBuf & CANTRCV_17_W9255_LWU_CHECK) ==
          CANTRCV_17_W9255_LWU_CHECK) ||
          ((DestBuf & CANTRCV_17_W9255_WUP_CHECK)
           == CANTRCV_17_W9255_WUP_CHECK) ||
          ((DestBuf & CANTRCV_17_W9255_WUF_CHECK)
           == CANTRCV_17_W9255_WUF_CHECK) ||
          ((CanTrcv_17_W9255_DestBuffer[Transceiver] &
            CANTRCV_17_W9255_SYSERR_CHECK) ==
           CANTRCV_17_W9255_SYSERR_CHECK))
      {
        /* [cover parentID={C2EB7A18-6A60-43fd-919F-0976C8D0CCD1}]
        Check if WUF or WUP bits are set
        [/cover] */
        /* Check if wakeup is due to pattern/frame */
        if(((DestBuf & CANTRCV_17_W9255_WUP_CHECK)
            == CANTRCV_17_W9255_WUP_CHECK) ||
            ((DestBuf & CANTRCV_17_W9255_WUF_CHECK)
             == CANTRCV_17_W9255_WUF_CHECK))
        {
          /* Set the Wake up reason to Wake up by bus */
          CanTrcv_17_W9255_WuReason[Transceiver] = CANTRCV_WU_BY_BUS;
        }
        else if(((DestBuf & CANTRCV_17_W9255_LWU_CHECK) ==
                 CANTRCV_17_W9255_LWU_CHECK))
        {
          /* Set the Wake up reason to Wake up by pin */
          CanTrcv_17_W9255_WuReason[Transceiver] = CANTRCV_WU_BY_PIN;
        }
        else
        {
          /* Set the Wake up reason to Wake up by SYSERR */
          CanTrcv_17_W9255_WuReason[Transceiver] = CANTRCV_WU_BY_SYSERR;
        }

        /* [cover parentID={C767813B-7343-4d3f-816C-C2C9DF4C1A30}]
        Is wake up mode enabled?
        [/cover] */
        if (CANTRCV_WUMODE_ENABLE == CanTrcv_17_W9255_WakeupMode[Transceiver])
        {
          /* [cover parentID={43CD856F-D2FE-4d05-A7ED-420D38CA932C}]
          Inform EcuM about the wake-up event
          [/cover] */
          /* Inform EcuM about the wake-up event */
          EcuM_SetWakeupEvent(((uint32)1U) << WakeupSourceRef);
        }
        /* [cover parentID={9A367324-2D5A-4229-AD11-8FAA5FF64A9B}]
        Is wake up mode disabled?
        [/cover] */
        else
        {
          /* [cover parentID={F5967671-C771-4012-BCB2-865F5E8988E4}]
          Update the pending wakeup event
          [/cover] */
          /* Update the pending wakeup event */
          CanTrcv_17_W9255_lSetPendWakeup(Transceiver);
        }

        /* Clear the wake flags */
        CanTrcv_17_W9255_SourceBuffer[Transceiver] =
            CANTRCV_17_W9255_CLEAR_WAKE_STAT;
        ReturnValue = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                      &CanTrcv_17_W9255_DestBuffer[Transceiver],
                      CANTRCV_17_W9255_SID_CHECKWAKEUP,
                      (uint8)CANTRCV_17_W9255_DET_DISABLE);

        /* [cover parentID={034E085C-20A1-4a3a-86AC-76F204B5CD13}]
        Is return status E_OK?
        [/cover] */
        if (ReturnValue == E_OK)
        {
          /* Set the CAN transceiver hardware to Normal mode */
          CanTrcv_17_W9255_SourceBuffer[Transceiver] =
              CANTRCV_17_W9255_NORMAL_VAL;
          /* [cover parentID={0BC24FCA-F031-41a3-BF7A-7A7618D47C21}]
          Set the CAN transceiver hardware to Normal mode and update
          return status
          [/cover] */
          ReturnValue = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                        &CanTrcv_17_W9255_DestBuffer[Transceiver],
                        CANTRCV_17_W9255_SID_CHECKWAKEUP,
                        (uint8)CANTRCV_17_W9255_DET_DISABLE);

          CanTrcv_17_W9255_ldelay();
        }
      }
    }
  }
  return ReturnValue;
}
#endif
#if (CANTRCV_17_W9255_DEV_ERROR_DETECT == STD_ON)
/******************************************************************************
** Traceability   : [cover parentID={D90F56E8-F519-4135-8ECF-967170B33FCC}]  **
**                                                                           **
** Syntax         : static Std_ReturnType CanTrcv_17_W9255_lCheckUninitDet   **
**                  (const uint8 serviceId)                                  **
**                                                                           **
** Description    : This function will check for driver initialization       **
**                                                                           **
** [/cover]                                                                  **
**                                                                           **
** Sync/Async     : Synchronous                                              **
**                                                                           **
** Reentrancy     : Non-Reentrant                                            **
**                                                                           **
** Parameters(in) : serviceId: Service Id of the API                         **
**                                                                           **
** Parameters(out): None                                                     **
**                                                                           **
** Return value   : E_OK : The driver is successfully initialized            **
**                  E_NOT_OK : Driver initialization failed                  **
**                                                                           **
******************************************************************************/
static Std_ReturnType CanTrcv_17_W9255_lCheckUninitDet(const uint8 serviceId)
{
  Std_ReturnType RetVal;

  /* [cover parentID={CD788B37-492B-4c09-813B-91D2E3785ECF}]
  Is the driver initialized?
  [/cover] */
  /* Check for driver initialization */
  if (CanTrcv_17_W9255_InitState == CANTRCV_17_W9255_UNINIT)
  {
    /* [cover parentID={9FC8FFC0-9A92-4082-843E-5E1A3B98BD09}]
    Report error as CANTRCV_17_W9255_E_UNINIT to DET
    [/cover] */
    /* Driver not initialized. Report error to DET. */
    (void)Det_ReportError(CANTRCV_17_W9255_MODULE_ID, CANTRCV_17_W9255_INSTANCE_ID,
                    serviceId, CANTRCV_17_W9255_E_UNINIT);
    RetVal = E_NOT_OK;

  }
  else
  {
    RetVal = E_OK;
  }

  return RetVal;
}
/******************************************************************************
** Traceability   : [cover parentID={55C485E1-124A-46fb-A087-0756D199B28B}]  **
**                                                                           **
** Syntax         : static Std_ReturnType CanTrcv_17_W9255_lCheckChannelId   **
**                  (const uint8 ChannelId, const uint8 serviceId)           **
**                                                                           **
** Description    : This function will check if the channel id is valid      **
**                                                                           **
** [/cover]                                                                  **
**                                                                           **
** Sync/Async     : Synchronous                                              **
**                                                                           **
** Reentrancy     : Reentrant                                                **
**                                                                           **
** Parameters(in) : ChannelId: Channel Number                                **
**                  serviceId: Service ID of the API                         **
**                                                                           **
** Parameters(out): None                                                     **
**                                                                           **
** Return value   : E_OK : The channel ID is valid                           **
**                  E_NOT_OK : The channel ID is not valid                   **
**                                                                           **
******************************************************************************/
static Std_ReturnType CanTrcv_17_W9255_lCheckChannelId(const uint8 ChannelId,
    const uint8 serviceId)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint8 ChannelIndex;

  /* [cover parentID={99922A18-CFB7-41ca-BC70-FBE467342D90}]
  Is the channel Id value less than or equal to the number of
  channels configured?
  [/cover] */
  /* Check if channel Id is Invalid */
  if (ChannelId >= CANTRCV_17_W9255_CHANNELS_CONFIGURED)
  {
    /* [cover parentID={84601991-D91C-4e4d-81A1-EA85D86F62CA}]
       Report error CANTRCV_17_W9255_E_INVALID_TRANSCEIVER to DET
      [/cover] */
    /* Report error to DET */
    (void)Det_ReportError(CANTRCV_17_W9255_MODULE_ID,
                          CANTRCV_17_W9255_INSTANCE_ID,
                          serviceId, CANTRCV_17_W9255_E_INVALID_TRANSCEIVER);
  }
  else
  {
    /* Get Channel Index */
    ChannelIndex = CanTrcv_17_W9255_ChannelUsed[ChannelId];

    /* [cover parentID={C2EF11BB-138B-4ad4-BC06-D98747B282F4}]
    Is channel index valid?
    [/cover] */
    /* Check if channel is disabled */
    if (ChannelIndex == 0xFFU)
    {
      /* [cover parentID={84601991-D91C-4e4d-81A1-EA85D86F62CA}]
      Report error CANTRCV_17_W9255_E_INVALID_TRANSCEIVER to DET
      [/cover] */
      /* Report to DET for Invalid Channel Id */
      (void)Det_ReportError(CANTRCV_17_W9255_MODULE_ID,
                            CANTRCV_17_W9255_INSTANCE_ID,
                            serviceId, CANTRCV_17_W9255_E_INVALID_TRANSCEIVER);
    }
    else
    {
      RetVal = E_OK;
    }
  }
  return RetVal;
}
#endif
/* #if (CANTRCV_17_W9255_DEV_ERROR_DETECT == STD_ON) */
/*******************************************************************************
** Traceability   : [cover parentID={E54F75EE-37D8-48da-9650-FBF60831EE35}]   **
**                                                                            **
** Syntax         : LOCAL_INLINE uint16 CanTrcv_17_W9255_lGetPendWakeup       **
**                  (const uint8 ChannelId)                                   **
**                                                                            **
** Description    : Function to get the pending wakeup on the Channel,if any  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : ChannelId - Channel Number                                **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : uint16 - Returns 1 if there is pending wakeup set and 0 if**
**                           there is no pending wakeup on the channel        **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint16 CanTrcv_17_W9255_lGetPendWakeup(const uint8 ChannelId)
{
  /* [cover parentID={977BB6FB-1FA7-40d9-A5FC-5AD2C52F1DE1}]
  Get the pending wakeup of the network, if any
  [/cover] */
  return (CanTrcv_17_W9255_PendWakeup >> ChannelId) & (uint16)1U ;
}
/*******************************************************************************
** Traceability   : [cover parentID={37D66664-736C-49f6-8AC0-1FCBC347EBD9}]   **
**                                                                            **
** Syntax         : LOCAL_INLINE void CanTrcv_17_W9255_lSetPendWakeup         **
**                  (const uint8 ChannelId)                                   **
**                                                                            **
** Description    : This function sets the pending wake-up on the channel     **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : ChannelId - Channel Number                                **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void CanTrcv_17_W9255_lSetPendWakeup(const uint8 ChannelId)
{
  /* [cover parentID={ABB66BE7-8FCF-46e8-9C0A-58CCB89FB536}]
  Set the pending wakeup of the network
  [/cover] */
  CanTrcv_17_W9255_PendWakeup |= (uint16)( (uint16)1U << ChannelId ) ;
}
/*******************************************************************************
** Traceability   : [cover parentID={7C2F25A8-AB9E-4e5b-A6BA-AF29AFF8F7EE}]   **
**                                                                            **
** Syntax         : LOCAL_INLINE void CanTrcv_17_W9255_lClearPendWakeup       **
**                  (const uint8 ChannelId)                                   **
**                                                                            **
** Description    : Function to clear the pending wakeup on the channel       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : ChannelId - Channel Number                                **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void CanTrcv_17_W9255_lClearPendWakeup(const uint8 ChannelId)
{
  /* [cover parentID={68CCD7BB-3227-4dc7-B519-6EF67169C9FB}]
  Clear the pending wakeup of the network
  [/cover] */
  CanTrcv_17_W9255_PendWakeup &= (~((uint16)1U << ChannelId ));
}
/*******************************************************************************
** Traceability    : [cover parentID={448BA9B2-B85B-4d64-AF42-30C7320C77DC}]  **
**                                                                            **
** Syntax         : static void CanTrcv_17_W9255_ldelay(void)                 **
**                                                                            **
** Description    : This function provides the delay required for mode        **
**                  transition.                                               **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : None                                                      **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
static void CanTrcv_17_W9255_ldelay(void)
{
  uint32 TickResolution = 0U;
  uint32 DelayCount = 0U;
  uint32 InitialCount = 0U;
  uint32 ElapsedTicks = 0U;

  TickResolution = Mcal_DelayTickResolution();
  DelayCount =  (uint32)CANTRCV_17_W9255_WAIT_TIME / TickResolution ;
  InitialCount = Mcal_DelayGetTick();
  /* [cover parentID={8F908F39-B7AD-43fc-AA4F-F0CECCD40B3B}]
  State Transition Delay
  [/cover] */
  do
  {

    ElapsedTicks = Mcal_DelayGetTick() - InitialCount;

  } while(DelayCount >= ElapsedTicks );
}
#if (CANTRCV_17_W9255_PN_CONFIGURED_CHANNELS > 0U)
/*******************************************************************************
** Traceability   : [cover parentID={B8A9048B-FCE3-4c9b-987A-17D364FC3AD2}]   **
**                                                                            **
** Syntax         : static Std_ReturnType  CanTrcv_17_W9255_lHardwareInitPN(  **
**                  const Spi_SequenceType                                    **
**                  SpiSequenceUsed,const uint8 ChannelId,                    **
**                  const uint8 serviceid)                                    **
**                                                                            **
** Description    : Function to initialize the partial networking registers   **
**                  of the channel                                            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : SpiSequenceUsed - SPI sequence used for the channel       **
**                  ChannelId - Id of the transceiver channel                 **
**                  serviceid - Service ID of the API                         **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : E_OK : All the PN registers are initialized successfully  **
**                  E_NOT_OK : Initialization of PN registers failed          **
**                                                                            **
*******************************************************************************/
static Std_ReturnType CanTrcv_17_W9255_lHardwareInitPN
(const Spi_SequenceType SpiSequenceUsed,
 const uint8 ChannelId, const uint8 serviceid)
{
  Std_ReturnType ReturnValue = E_OK;
  uint8 LoopCount;
  uint16 PnFrameDlc = 0;
  uint8 PnIndex = CanTrcv_17_W9255_PnConfigured[ChannelId];
  PnFrameDlc = CanTrcv_17_W9255_PNConfig[PnIndex].CanTrcvPnDlc;


  /* [cover parentID={554CD680-239B-438c-ADE3-CDC8CFCE86F6}]
  Configure Baudrate, CAN Id and CAN Id mask and enable PN for the channel
  [/cover] */
  /* Configure Baudrate, CAN Id and CAN Id mask and enable PN */
  for(LoopCount = 0; (LoopCount < CANTRCV_17_W9255_PN_COMMAND_COUNT) &&
      (ReturnValue == E_OK); LoopCount++)
  {
    CanTrcv_17_W9255_SourceBuffer[ChannelId] =
        CanTrcv_17_W9255_PNConfig[PnIndex].CanTrcvPnIdInfoPtr[LoopCount];

    /* [cover parentID={1ADD0BFC-F8B7-41d5-B9FD-890FE5830A75}]
    Fetch the command and transmit over SPI and update the return status
    [/cover] */
    ReturnValue = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                  &CanTrcv_17_W9255_DestBuffer[ChannelId],
                  serviceid, (uint8)CANTRCV_17_W9255_REPORT_DET);

  }

  /* [cover parentID={A233BD26-7524-4913-BB06-BD1984DEF939}]
  Is return status E_OK?
  [/cover] */
  if(ReturnValue == E_OK)
  {
    /* [cover parentID={C9D2033B-19F4-4cdc-A2FD-97CEAF6FF3E9}]
    Configure Data masks
    [/cover] */
    /* Configure Data masks of the PN frame */
    for(LoopCount = 0; (LoopCount < PnFrameDlc)  &&
        (ReturnValue == E_OK); LoopCount++)
    {
      CanTrcv_17_W9255_SourceBuffer[ChannelId] =
          CanTrcv_17_W9255_PNConfig[PnIndex].CanTrcvPnDataInfoPtr[LoopCount];

      /* [cover parentID={60EB6E57-5180-466a-A77A-83730187D269}]
      Fetch the command and transmit over SPI and update the return status
      [/cover] */
      ReturnValue = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                    &CanTrcv_17_W9255_DestBuffer[ChannelId],
                    serviceid, (uint8)CANTRCV_17_W9255_REPORT_DET);
    }
  }

  /* [cover parentID={8EB74102-137A-47c6-ADE1-9B4EE36DBA79}]
  Is return status E_OK?
  [/cover] */
  if(ReturnValue == E_OK)
  {
    /* [cover parentID={840AEFE3-ADD3-4c31-A220-B80B109DF12E}]
    Confirm PN configuration by enabling the CFG_VAL bit of SWK_CTRL_1 register
    [/cover] */
    /* Confirm PN configuration by enabling the
              CFG_VAL bit of SWK_CTRL_1 register */
    CanTrcv_17_W9255_SourceBuffer[ChannelId] =
        CANTRCV_17_W9255_WRITE_REG_SWK_CTRL_1;
    ReturnValue = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                  &CanTrcv_17_W9255_DestBuffer[ChannelId],
                  serviceid, (uint8)CANTRCV_17_W9255_REPORT_DET);
  }

  return ReturnValue;
}
#endif
/*******************************************************************************
** Traceability   : [cover parentID={678FCE18-F665-44a7-9E9D-1D61D69049C5}]   **
**                                                                            **
** Syntax         : Std_ReturnType CanTrcv_17_W9255_lSetTrcvMode(             **
**                  const uint8 Transceiver, const Spi_SequenceType           **
**                  SpiSequenceUsed, const CanTrcv_TrcvModeType OpMode)       **
**                                                                            **
** Description    : This function changes the mode of the transceiver to the  **
**                  mode requested.                                           **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Non-Reentrant                                             **
**                                                                            **
** Parameters (in): Transceiver - Channel ID                                  **
**                  SpiSequenceUsed - SPI sequence ID configured for the      **
**                                    channel                                 **
**                  OpMode - Mode to be set                                   **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : E_OK  : will be returned if the transceiver mode is       **
**                          changed successfully to the mode requested        **
**                  E_NOT_OK  : will be returned if the transceiver mode is   **
**                          not changed                                       **
**                                                                            **
*******************************************************************************/
static Std_ReturnType CanTrcv_17_W9255_lSetTrcvMode (const uint8 Transceiver,
    const Spi_SequenceType SpiSequenceUsed, const CanTrcv_TrcvModeType OpMode)
{

  Std_ReturnType ReturnValue;
  uint8 PnIndex;
  uint16 CFG_VAL_value;
  /* [cover parentID={A9C6A7BE-7AAC-4e4d-BA64-14CF8F24FE8F}]
  Is OpMode NORMAL?
  [/cover] */
  if (OpMode == CANTRCV_TRCVMODE_NORMAL)
  {
    /* [cover parentID={DD55A76B-7CF8-4c17-8233-8DE092065429}]
    Set up the source buffer to set the CAN transceiver hardware to NORMAL mode
    [/cover] */
    /* Set the CAN transceiver hardware to Normal mode. */
    CanTrcv_17_W9255_SourceBuffer[Transceiver] = CANTRCV_17_W9255_NORMAL_VAL;
  }

  /* [cover parentID={07C2530B-2500-478f-A7BD-29E6D85F6C83}]
  Is OpMode STANDBY?
  [/cover] */
  else if (OpMode == CANTRCV_TRCVMODE_STANDBY)
  {
    /* Clear LWU, WUF and WUP flags before entering into Standby */
    CanTrcv_17_W9255_SourceBuffer[Transceiver] =
        CANTRCV_17_W9255_CLEAR_WAKE_STAT;
    /* [cover parentID={5128D35F-C92C-498c-9E08-AC1FCF78A551}]
    Clear LWU, WUF and WUP flags of WAKE_STAT register before entering
    into STANDBY mode and update return status
    [/cover] */
    ReturnValue = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                  &CanTrcv_17_W9255_DestBuffer[Transceiver],
                  CANTRCV_17_W9255_SID_SETOPMODE,
                  (uint8)CANTRCV_17_W9255_REPORT_DET);

    /* [cover parentID={4882B0DE-23D9-4e7d-AC04-A85F9CE6D4B8}]
    Is return status E_OK?
    [/cover] */
    if (ReturnValue == E_OK)
    {
      /* [cover parentID={59B8060C-EEAB-452d-8CF6-DACED2C8C30C}]
      Set up the source buffer to set the CAN transceiver hardware to
      STANDBY mode
      [/cover] */
      /* Set the CAN transceiver hardware to Standby mode. */
      CanTrcv_17_W9255_SourceBuffer[Transceiver] =
          CANTRCV_17_W9255_STANDBY_VAL;
    }
  }

  else
  {
    PnIndex = CanTrcv_17_W9255_PnConfigured[Transceiver];

    /* [cover parentID={D89BF5D0-9B48-4b59-9493-95D00D6572C3}]
    Is PN enabled for the channel?
    [/cover] */
    if(PnIndex == CANTRCV_17_W9255_PN_NOT_CONFIGURED)
    {
      /* [cover parentID={C2C3AA2E-AFAE-4342-8A33-843EBEF99DE8}]
      Set up the source buffer to set the CAN transceiver hardware
      to SLEEP mode
      [/cover] */
      /* Set the CAN transceiver hardware to Sleep mode. */
      CanTrcv_17_W9255_SourceBuffer[Transceiver] = CANTRCV_17_W9255_SLEEP_VAL;

    }
    else
    {
             CanTrcv_17_W9255_SourceBuffer[Transceiver] =
              CANTRCV_17_W9255_READ_REG_SWK_CTRL_1;
      ReturnValue = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                    &CanTrcv_17_W9255_DestBuffer[Transceiver],
                    CANTRCV_17_W9255_SID_SETOPMODE,
                    (uint8)CANTRCV_17_W9255_REPORT_DET);
      CFG_VAL_value = CanTrcv_17_W9255_DestBuffer[Transceiver] &
                      CANTRCV_17_W9255_CFGVAL_CHECK;

      /* [cover parentID={CB811D86-8B84-48b7-9BD5-A338AB14E118}]
      Is CFG_VAL flag reset?
      [/cover] */
      if((CFG_VAL_value == 0U) && (ReturnValue == E_OK))
      {
        CanTrcv_17_W9255_SourceBuffer[Transceiver] =
               CANTRCV_17_W9255_WRITE_REG_SWK_CTRL_1;
        ReturnValue = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                      &CanTrcv_17_W9255_DestBuffer[Transceiver],
                      CANTRCV_17_W9255_SID_SETOPMODE,
                      (uint8)CANTRCV_17_W9255_REPORT_DET);
      }
      /* [cover parentID={3E9C876C-F00E-4079-A2FE-AFBB781FDF23}]
      Is return status E_OK?
      [/cover] */
      if(ReturnValue == E_OK)
      {
        /* Set the CAN transceiver hardware to Sleep mode. */
        CanTrcv_17_W9255_SourceBuffer[Transceiver] = CANTRCV_17_W9255_SLEEP_VAL;
      }
    }
  }

  /* [cover parentID={B7DC8803-5B1A-42cb-814C-809CD6C21F6E}]
  Transmit buffer over SPI and update return status
  [/cover] */
  ReturnValue = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                &CanTrcv_17_W9255_DestBuffer[Transceiver],
                CANTRCV_17_W9255_SID_SETOPMODE,
                (uint8)CANTRCV_17_W9255_REPORT_DET);

  /* [cover parentID={35A218A6-677C-4504-BBCB-AD59C093D476}]
  Is return status E_OK?
  [/cover] */
  if (ReturnValue == E_OK)
  {
    /* Delay for Mode Transition */
    CanTrcv_17_W9255_ldelay();
  }

  /* [cover parentID={08DC1739-57DB-4a4f-999D-0D07EA57DF77}]
  Return status
  [/cover] */
  return ReturnValue;
}
#if (CANTRCV_17_W9255_DEV_ERROR_DETECT == STD_ON)
/******************************************************************************
** Traceability   : [cover parentID={2FC24BFE-836B-4a8e-8AF9-C7D1380656A9}]  **
**                                                                           **
** Syntax         : Std_ReturnType  CanTrcv_17_W9255_lCheckModeDet(          **
**                  const CanTrcv_TrcvModeType Mode, const uint8 serviceId,  **
**                  const CanTrcv_TrcvModeType OpMode)                       **
**                                                                           **
** Description    : Checks DETs CANTRCV_17_W9255_E_PARAM_TRCV_OPMODE,        **
**                  CANTRCV_17_W9255_E_TRCV_NOT_NORMAL,                      **
**                  CANTRCV_17_W9255_E_TRCV_NOT_STANDBY and reports if any   **
**                                                                           **
** [/cover]                                                                  **
**                                                                           **
** Service ID     : NA                                                       **
**                                                                           **
** Sync/Async     : Synchronous                                              **
**                                                                           **
** Reentrancy     : Reentrant                                                **
**                                                                           **
** Parameters (in): Mode - Current mode of the channel                       **
**                  serviceId - Service Id of the SetOpMode API              **
**                  OpMode - Requested operating mode                        **
**                                                                           **
** Parameters(out): None                                                     **
**                                                                           **
** Return value   : E_OK  : will be returned if no DET error occurs          **
**                  E_NOT_OK  : will be returned if any DET error occcurs    **
**                                                                           **
******************************************************************************/
static Std_ReturnType CanTrcv_17_W9255_lCheckModeDet
(const CanTrcv_TrcvModeType Mode,
 const uint8 serviceId, const CanTrcv_TrcvModeType OpMode)
{
  Std_ReturnType DevError = E_OK;

  /* [cover parentID={05A750AA-49D1-419a-841F-02175972D46D}]
  Is OpMode invalid?
  [/cover] */
  /* Check if Opmode is passed with invalid value */
  if ((OpMode != CANTRCV_TRCVMODE_NORMAL) &&
      (OpMode != CANTRCV_TRCVMODE_STANDBY) &&
      (OpMode != CANTRCV_TRCVMODE_SLEEP))
  {
    /* [cover parentID={67371A6C-D038-4423-91E3-C192F859DAA6}]
    Report CANTRCV_17_W9255_E_PARAM_TRCV_OPMODE error to DET
    [/cover] */
    /* Parameter is not valid. Report error to DET. */
    (void)Det_ReportError(
      CANTRCV_17_W9255_MODULE_ID,
      CANTRCV_17_W9255_INSTANCE_ID,
      serviceId,
      CANTRCV_17_W9255_E_PARAM_TRCV_OPMODE
    );

    /* [cover parentID={91569E80-178B-471c-8B89-D6C48C11D5E1}]
    Return E_NOT_OK
    [/cover] */
    DevError = E_NOT_OK;
  }

  /* [cover parentID={B5F7B47E-04BB-486a-A5F0-56D2E79FE19F}]
  Is there mode transition from Sleep to Standby?
  [/cover] */
  /* Check if the mode transition is from Sleep -> Standby */
  else if((Mode == CANTRCV_TRCVMODE_SLEEP) &&
          (OpMode == CANTRCV_TRCVMODE_STANDBY))
  {
    /* [cover parentID={CB17A442-EBC4-4205-86BE-A25BF4ABCC70}]
    Report CANTRCV_17_W9255_E_TRCV_NOT_NORMAL error to DET
    [/cover] */
    /* Mode Transition invalid. Report error to DET. */
    (void)Det_ReportError(
      CANTRCV_17_W9255_MODULE_ID,
      CANTRCV_17_W9255_INSTANCE_ID,
      serviceId,
      CANTRCV_17_W9255_E_TRCV_NOT_NORMAL
    );

    /* [cover parentID={91569E80-178B-471c-8B89-D6C48C11D5E1}]
    Return E_NOT_OK
    [/cover] */
    DevError = E_NOT_OK;
  }

  /* [cover parentID={3981B6B7-9E11-4526-8F85-1B56DAA9DA63}]
  Is there mode transition from Normal to Sleep?
  [/cover] */
  /* Check if the mode transition is from Normal-> Sleep */
  else if((Mode == CANTRCV_TRCVMODE_NORMAL) &&
          (OpMode == CANTRCV_TRCVMODE_SLEEP))
  {
    /* [cover parentID={6539E865-2C3C-489b-91F7-F377B63EF5AA}]
    Report CANTRCV_17_W9255_E_TRCV_NOT_STANDBY error to DET
    [/cover] */
    /* Mode Transition invalid. Report error to DET. */
    (void)Det_ReportError(
      CANTRCV_17_W9255_MODULE_ID,
      CANTRCV_17_W9255_INSTANCE_ID,
      serviceId,
      CANTRCV_17_W9255_E_TRCV_NOT_STANDBY
    );
    /* [cover parentID={91569E80-178B-471c-8B89-D6C48C11D5E1}]
    Return E_NOT_OK
    [/cover] */
    DevError = E_NOT_OK;
  }
  else
  {
    /* Do nothing. Added for Misra check */
  }
  return DevError;
}
#endif
/*******************************************************************************
** Traceability   : [cover parentID={9E67B7C4-3899-4623-8348-0C93E22E597A}]   **
**                                                                            **
** Syntax         : Std_ReturnType CanTrcv_17_W9255_lHardwareInit(            **
**                  const uint8 ChannelId, const Spi_SequenceType             **
**                  SpiSequenceUsed, const uint16 InitState)                  **
**                                                                            **
** Description    : Initializes the Hardware control and Mode control         **
**                  (Non-PN) registers                                        **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Non Reentrant                                             **
**                                                                            **
** Parameters (in): ChannelId - Id of the transceiver channel                 **
**                  SpiSequenceUsed - SPI sequence Id configured for the      **
**                                    channel                                 **
**                  InitState - Mode of the transceiver after driver          **
**                              initialization                                **
**                                                                            **
** Return value   : E_OK  : will be returned if initialization is done with   **
**                          no DET error occurrence                           **
**                                                                            **
**                  E_NOT_OK  : will be returned if any DET error occurs      **
**                              during initialization                         **
**                                                                            **
*******************************************************************************/
static Std_ReturnType CanTrcv_17_W9255_lHardwareInit(const uint8 ChannelId,
    const Spi_SequenceType SpiSequenceUsed, const uint16 InitState)
{

  Std_ReturnType ReturnValue = E_NOT_OK;

  /* [cover parentID={995C8E43-5120-4571-B462-8AA2FB5717D2}]
  Configure MODE_CTRL register for putting transceiver to requested init mode
  and update return status
  [/cover] */
  /* Configure MODE_CTRL register for putting transceiver
     * to requested init mode */
  CanTrcv_17_W9255_SourceBuffer[ChannelId] = InitState;

  ReturnValue = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                &CanTrcv_17_W9255_DestBuffer[ChannelId],
                CANTRCV_17_W9255_SID_INIT,
                (uint8)CANTRCV_17_W9255_REPORT_DET);

  /* [cover parentID={F46852D7-D8FE-4df8-A009-9E02EC6BBBDA}]
  Is return status E_OK?
  [/cover] */
  if (ReturnValue == E_OK)
  {
    /* Delay for Mode Transition */
    CanTrcv_17_W9255_ldelay();

    /* [cover parentID={343518CA-859A-4502-96B4-6B3D3C37B234}]
    Configure HW_CTRL register for LWU and RxD pin behavior
    and update return status
    [/cover] */
    /* Configure HW_CTRL register for LWU and RxD behavior */
    /* Enable local wakeup to be performed on both the edges
     * and configure RxD pin to toggle between low and high
     *  if a wakeup event is detected */
    CanTrcv_17_W9255_SourceBuffer[ChannelId] =
        CANTRCV_17_W9255_INITIALIZE_HW_CTRL;

    ReturnValue = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                  &CanTrcv_17_W9255_DestBuffer[ChannelId],
                  CANTRCV_17_W9255_SID_INIT,
                  (uint8)CANTRCV_17_W9255_REPORT_DET);

  }
  return ReturnValue;
}
/******************************************************************************
** Traceability   : [cover parentID={074A1750-F434-49cd-BC26-AEE95D43AE5C}]  **
**                                                                           **
** Syntax         : static Std_ReturnType CanTrcv_17_W9255_lSpiRetries(      **
**                  const Spi_SequenceType SpiSequenceId, const uint16*      **
**                 const Buffer, const uint8 serviceId, const uint8 DetRaise)**
**                                                                           **
** Description    : Function to transmit data through SPI and check for      **
**                  successful communication                                 **
**                                                                           **
** [/cover]                                                                  **
**                                                                           **
** Sync/Async     : Synchronous                                              **
**                                                                           **
** Reentrancy     : Non-Reentrant                                            **
**                                                                           **
** Parameters(in) : SpiSequenceId - SPI sequence Id configured for the       **
**                                  channel                                  **
**                  Buffer - Pointer to destination buffer of the channel    **
**                  serviceId - Service Id of the API                        **
**                  DetRaise - Indicates if DET is to be raised or not       **
**                                                                           **
** Parameters(out): None                                                     **
**                                                                           **
** Return value   : E_OK  : will be returned if SPI communication succeeds   **
**                                                                           **
**                  E_NOT_OK  : will be returned if SPI communication fails  **
**                                                                           **
******************************************************************************/
static Std_ReturnType CanTrcv_17_W9255_lSpiRetries(
  const Spi_SequenceType SpiSequenceId,
  const uint16* const Buffer, const uint8 serviceId, const uint8 DetRaise)
{
  Std_ReturnType RetStatus = E_NOT_OK;
  uint16 Retries;

  /* [cover parentID={30DBD3AF-574F-470b-AACA-F5AA7DBDCAE8}]
  SPI communication retries
  [/cover] */
  /* Transmit data through SPI and repeat for the requested number
     of times, if failed */
  for(Retries = (uint16)(CANTRCV_17_W9255_SPI_COMM_RETRIES + 1U);
      ((Retries > 0U ) && (RetStatus == E_NOT_OK)); Retries--)
  {
    RetStatus = Spi_SyncTransmit(SpiSequenceId);
  }
   /* [cover parentID={F00915EF-DAC9-4973-A9D8-30601B59830F}]
  Check for SPI error
  [/cover] */
  if(RetStatus == E_OK)
  {
    /* [cover parentID={99AC1DE3-2A84-4b68-97EB-1ACC1F375E89}]
    Report error  CANTRCV_17_W9255_E_NO_TRCV_CONTROL to DET
    [/cover] */
    /* There is no/incorrect communication. Report DET or runtime error*/
    RetStatus = CanTrcv_17_W9255_lReportRuntimeDetError(DetRaise,
    Buffer, serviceId, CANTRCV_17_W9255_E_NO_TRCV_CONTROL);
  }

return RetStatus;
}

/*******************************************************************************
** Traceability: [cover parentID={2CD4A101-8393-42a9-9704-91737861AEA4}]      **                                     **
**                                                                            **
** Syntax           : static Std_ReturnType CanTrcv_17_W9255_lReportRuntimeDetError**
**                    (                                                       **
**                       const uint8 DetRaise                                 **
**                       const uint16* const Buffer                           **
**                       const uint8 ApiId,                                   **
**                       const uint8 ErrorId                                  **
**                    )                                                       **
**                                                                            **
** Description      : This function reports the Runtime or DET Error          **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : ApiId - Service ID of the API reporting an error        **
**                    ErrorId - ID of the error reported                      **
**                    Buffer - Pointer to destination buffer of the channel   **
**                    DetRaise - Indicates if DET is to be raised or not      **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
**   Return value   : E_OK  : will be returned if SPI communication succeeds  **
**                                                                            **
**                    E_NOT_OK  : will be returned if SPI communication fails **                                                    **
**                                                                            **
*******************************************************************************/
static Std_ReturnType CanTrcv_17_W9255_lReportRuntimeDetError(const uint8 DetRaise,
const uint16* const Buffer,const uint8 ApiId, const uint8 ErrorId)
{
uint16 ErrorFlag;
Std_ReturnType RetStatus = E_NOT_OK;

    /* Extract ERR_STAT from the status information field */
    ErrorFlag = *Buffer & CANTRCV_17_W9255_SPI_ERROR_CHECK;

    /* [cover parentID={71B3149B-5638-41b5-A2E9-32727A9211A3}]
    Is ERR_STAT bit set?
    [/cover] */
    /* Check if ERR_STAT bit of status information field is set */
    if (ErrorFlag == CANTRCV_17_W9255_SPI_ERROR_CHECK)
    {
      /* [cover parentID={ECC88720-B312-4805-B37A-B4343FC2FAB1}]
      Is DET to be reported?
      [/cover] */
      if(DetRaise == CANTRCV_17_W9255_REPORT_DET)
      {
        /* Runtime Error Detection is only available in Autosar version AR440 */
        #if(MCAL_AR_VERSION == MCAL_AR_440)
            /* [cover parentID={91FD656A-ADD1-466c-8136-A6FA06629CAC}]
            Is Runtime Error ON?
            [/cover] */
            /* Check Runtime error is ON */
            #if (CANTRCV_17_W9255_RUNTIME_ERROR_DETECT == STD_ON)
                  /* Report the Runtime Error */
                  (void)Mcal_Wrapper_Det_ReportRuntimeError(CANTRCV_17_W9255_MODULE_ID,
                                  CANTRCV_17_W9255_INSTANCE_ID, ApiId, ErrorId);
            #else
                UNUSED_PARAMETER(ApiId);
                UNUSED_PARAMETER(ErrorId);
            #endif
        #else
            /* [cover parentID={355D71D3-C54D-406f-A256-366B66C5F3F5}]
            Is DET ON?
            [/cover] */
            /* Check DET is Enabled*/
            #if (CANTRCV_17_W9255_DEV_ERROR_DETECT == STD_ON)
                  /* Report the DET Error */
                      (void)Det_ReportError(CANTRCV_17_W9255_MODULE_ID,
                                  CANTRCV_17_W9255_INSTANCE_ID, ApiId, ErrorId);

            #else
                UNUSED_PARAMETER(ApiId);
                UNUSED_PARAMETER(ErrorId);
            #endif
        #endif
      }
    }
    /* No ERR_STAT bit is set */
    else
    {
    RetStatus = E_OK;
    }
   /* [cover parentID={CD9F455D-88C1-4be4-9466-EB67D617A20F}]
  Return status
  [/cover] */
  return RetStatus;
}
/******************************************************************************
** Traceability   : [cover parentID={66EABFCE-1D15-413f-B9F1-264FFD011DEB}]  **
**                                                                           **
** Syntax         : static Std_ReturnType                                    **
**                  CanTrcv_17_W9255_lInitCheckPorSyserr                     **
**                  (const uint8 ChannelIndex, const uint8 serviceid)        **
**                                                                           **
** Description    : This function will check for POR and SYSERR flags for the**
**                  respective channel during driver initialization and if   **
**                  set, reports to EcuM.                                    **
**                                                                           **
** [/cover]                                                                  **
**                                                                           **
** Sync/Async     : Synchronous                                              **
**                                                                           **
** Reentrancy     : Non-Reentrant                                            **
**                                                                           **
** Parameters(in) : ChannelIndex - Channel Index                             **
**                  serviceid - Service Id of the API                        **
**                                                                           **
** Parameters(out): None                                                     **
**                                                                           **
** Return value   : E_OK  : Successfully checked for POR and SYSERR flags    **
**                  E_NOT_OK  : POR and SYSERR flag check failed             **
**                                                                           **
******************************************************************************/
static Std_ReturnType CanTrcv_17_W9255_lInitCheckPorSyserr
(const uint8 ChannelIndex, const uint8 serviceid)
{
  Std_ReturnType ReturnValue;
  uint8 ChannelId;
  Spi_SequenceType SpiSequenceUsed;
  uint16 DestBuf;
  uint16 InitState;
  EcuM_WakeupSourceType CanTrcvPorWakeupSource;
  EcuM_WakeupSourceType CanTrcvSyserrWakeupSource;
  CanTrcvPorWakeupSource =
       CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvPorWakeupSourceRef;
  CanTrcvSyserrWakeupSource =
    CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvSyserrWakeupSourceRef;
  SpiSequenceUsed =
              CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvSpiSequence;
  ChannelId =
              CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvChannelId;
  InitState =
              CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvInitState;

  /* [cover parentID={B9308B24-7EEC-437d-A21F-02BC05633F9E}]
  Fetch status of POR and SYSERR flags by reading the Selective
  Wake Status register and update the return status
  [/cover] */
  /* Read the status of SYSERR and POR flags */
  CanTrcv_17_W9255_SourceBuffer[ChannelId] =
      CANTRCV_17_W9255_READ_SWK_STAT;
  ReturnValue = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                &CanTrcv_17_W9255_DestBuffer[ChannelId], serviceid,
                (uint8)CANTRCV_17_W9255_REPORT_DET);
  DestBuf = CanTrcv_17_W9255_DestBuffer[ChannelId];

  /* [cover parentID={004896D9-2A2F-4ee6-8A52-BFE51F2962AB}]
  Is return status E_OK?
  [/cover] */
  if (ReturnValue == E_OK)
  {
    /* [cover parentID={F809BE6E-B001-49eb-8BAE-7EDEC598E403}]
    Is SYSERR flag set?
    [/cover] */
    /* Report wakeup if SYSERR flag is set and reconfigure
          for selective wakeup functionality */
    if ((DestBuf &
         CANTRCV_17_W9255_SYSERR_CHECK) == CANTRCV_17_W9255_SYSERR_CHECK)
    {
      /* [cover parentID={99B3EFE2-DF9E-41b4-9AF5-26A9239F8036}]
      Report wakeup to EcuM with the SYSERR wakeup source reference
      [/cover] */
      EcuM_SetWakeupEvent(((uint32)1U) << CanTrcvSyserrWakeupSource);
      CanTrcv_17_W9255_WuReason[ChannelId] = CANTRCV_WU_BY_SYSERR;
    }

    /* [cover parentID={7280D174-FFA6-48d6-994F-E6FD83F2DD6B}]
    Is POR flag set?
    [/cover] */
    /* Report wakeup if POR flag is set and reconfigure for
         selective wakeup functionality */
    if ((DestBuf &
         CANTRCV_17_W9255_POR_CHECK) == CANTRCV_17_W9255_POR_CHECK)
    {
      /* [cover parentID={4D49E537-1881-4a08-A3CC-8F734E1B4646}]
      Report wakeup to EcuM
      [/cover] */
      EcuM_SetWakeupEvent(((uint32)1U) << CanTrcvPorWakeupSource);
      CanTrcv_17_W9255_WuReason[ChannelId] = CANTRCV_WU_POWER_ON;
      ReturnValue =
        CanTrcv_17_W9255_lHardwareInit(ChannelId, SpiSequenceUsed, InitState);

      /* [cover parentID={BD322D82-222F-4796-AE79-E1773ECD62BE}]
      Is return status E_OK?
      [/cover] */
      if(ReturnValue == E_OK)
      {
        /* [cover parentID={D8092F29-A1DE-4252-9C23-0D7B47C3DF22}]
        Clear the POR flag in the transceiver hardware and update the
        return status
        [/cover] */
        CanTrcv_17_W9255_SourceBuffer[ChannelId] =
            CANTRCV_17_W9255_CLEAR_POR;
        ReturnValue = CanTrcv_17_W9255_lSpiRetries (SpiSequenceUsed,
                      &CanTrcv_17_W9255_DestBuffer[ChannelId], serviceid,
                      (uint8)CANTRCV_17_W9255_REPORT_DET);

      }
    }
    /* [cover parentID={C1B5B7D1-AF45-4e4b-B87B-74543AA084EC}]
    Is return status E_OK and POR/SYSERR flag set?
    [/cover] */
    if ((ReturnValue == E_OK) &&
        (((DestBuf &
         CANTRCV_17_W9255_SYSERR_CHECK) == CANTRCV_17_W9255_SYSERR_CHECK) ||
         ((DestBuf &
           CANTRCV_17_W9255_POR_CHECK) == CANTRCV_17_W9255_POR_CHECK)))
    {
      #if (CANTRCV_17_W9255_PN_CONFIGURED_CHANNELS > 0U)
      /* [cover parentID={E8F22450-2A0F-4bfe-A25C-40FA634E5A0C}]
      Re-configure for Partial networking and update return status
      [/cover] */
      /* Configure for Partial networking */
      ReturnValue = CanTrcv_17_W9255_lHardwareInitPN(SpiSequenceUsed,
                    ChannelId, serviceid);
      #endif
    }
  }
  /* [cover parentID={574B135D-6BEB-4ba1-AE09-D339B1577888}]
  Return status
  [/cover] */
  return ReturnValue;
}
/******************************************************************************
** Traceability    : [cover parentID={A799295E-97C0-4cf4-94B4-8EE68D56CED7}] **
**                                                                           **
** Syntax          : static Std_ReturnType CanTrcv_17_W9255_lCheckInitWakeup **
**                   (const uint8 ChannelIndex, const uint8 Transceiver)     **
**                                                                           **
** Description     : This function will check for valid wakeup events for the**
**                   respective channel during driver initialization and if  **
**                   detected, reports to EcuM.                              **
**                                                                           **
** [/cover]                                                                  **
**                                                                           **
** Service ID      : NA                                                      **
**                                                                           **
** Sync/Async      : Sychronous                                              **
**                                                                           **
** Reentrancy      : Non Reentrant                                           **
**                                                                           **
** Parameters (in) : ChannelIndex - Channel Index                            **
**                   Transceiver - Channel Id                                **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value    : E_OK: Channel was checked for wakeup events successfully**
**                   E_NOT_OK: Wakeup check failed for the channel           **
**                                                                           **
******************************************************************************/
static Std_ReturnType CanTrcv_17_W9255_lCheckInitWakeup
(const uint8 ChannelIndex, const uint8 Transceiver)
{
  Std_ReturnType ReturnValue;
  uint16 DestBuf;
  EcuM_WakeupSourceType WakeupSourceRef;
  Spi_SequenceType SpiSequenceUsed =
            CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvSpiSequence;

  /* Initially Enable the Wakeup for the channel */
  CanTrcv_17_W9255_WakeupMode[Transceiver] = CANTRCV_WUMODE_ENABLE;

  /* Initially Pending Wakeup is cleared for the channel */
  CanTrcv_17_W9255_lClearPendWakeup(Transceiver);

  /* check for valid wakeup events */
  CanTrcv_17_W9255_SourceBuffer[Transceiver] = CANTRCV_17_W9255_READ_WAKE_STAT;

  /* [cover parentID={FF5D46DA-4241-44a2-A27E-6DF2050A9215}]
  Read the WAKE_STAT register and update the return status
  [/cover] */
  ReturnValue = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                &CanTrcv_17_W9255_DestBuffer[Transceiver],
                CANTRCV_17_W9255_SID_INIT,
                (uint8)CANTRCV_17_W9255_REPORT_DET);
  DestBuf = CanTrcv_17_W9255_DestBuffer[Transceiver];

  /* [cover parentID={D90FBE28-CA12-4051-BBB5-9397C5A6F979}]
  Is return status E_OK?
  [/cover] */
  if (ReturnValue == E_OK)
  {
    /* [cover parentID={54710784-7EA5-48c4-B67E-A328626528A4}]
    Check if wakeup has occurred
    [/cover] */
    /* If Wake is detected, check for wake up mode type */
    if(((DestBuf & CANTRCV_17_W9255_LWU_CHECK) ==
        CANTRCV_17_W9255_LWU_CHECK) ||
        ((DestBuf & CANTRCV_17_W9255_WUP_CHECK)
         == CANTRCV_17_W9255_WUP_CHECK) ||
        ((DestBuf & CANTRCV_17_W9255_WUF_CHECK)
         == CANTRCV_17_W9255_WUF_CHECK))
    {
      WakeupSourceRef =
          CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvWakeupSourceRef;

      /* [cover parentID={49BD3579-ED52-4b40-AB5F-BE4C050A1BA1}]
      Inform EcuM about the wake-up event
      [/cover] */
      /* Inform EcuM about the wake-up event */
      EcuM_SetWakeupEvent(((uint32)1U) << WakeupSourceRef);

      /* [cover parentID={30DCB978-544D-4f83-99A0-2A5CA265CD33}]
      Check if local wakeup has occurred
      [/cover] */
      /* Check for local wakeup */
      if(((DestBuf & CANTRCV_17_W9255_LWU_CHECK) ==
          CANTRCV_17_W9255_LWU_CHECK))
      {
        /* Set the Wake up reason to Wake up by pin */
        CanTrcv_17_W9255_WuReason[Transceiver] = CANTRCV_WU_BY_PIN;
      }
      else
      {
        /* Set the Wake up reason to Wake up by bus */
        CanTrcv_17_W9255_WuReason[Transceiver] = CANTRCV_WU_BY_BUS;
      }

      /* Clear the wake flags */
      CanTrcv_17_W9255_SourceBuffer[Transceiver] =
          CANTRCV_17_W9255_CLEAR_WAKE_STAT;
      ReturnValue = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                    &CanTrcv_17_W9255_DestBuffer[Transceiver],
                    CANTRCV_17_W9255_SID_INIT,
                    (uint8)CANTRCV_17_W9255_REPORT_DET);
    }
  }
  return ReturnValue;
}

/*******************************************************************************
** Traceability   : [cover parentID={C2FB8066-B540-499a-8BE5-7073DB830C05}]   **
**                                                                            **
** Syntax         : static Std_ReturnType CanTrcv_17_W9255_lPorSyserrCheck    **
**                  (const uint8 ChannelIndex,                                **
**                   const uint8 serviceId,                                   **
**                   const CanTrcv_TrcvModeType OpMode)                       **
**                                                                            **
** Description    : Function to check for POR and SYSERR flags and confirm    **
**                  selective wakeup for the channel                          **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Non-Reentrant                                             **
**                                                                            **
** Parameters(in) : ChannelIndex - Channel index                              **
**                  serviceId - Service Id of the API                         **
**                  OpMode - Mode to be set                                   **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : E_OK: POR and SYSERR flags are checked successfully       **
**                  E_NOT_OK: POR and SYSERR flags check failed               **
**                                                                            **
*******************************************************************************/
static Std_ReturnType CanTrcv_17_W9255_lPorSyserrCheck(const uint8 ChannelIndex,
    const uint8 serviceId, const CanTrcv_TrcvModeType OpMode)
{
  Std_ReturnType ReturnValue = E_OK;
  Spi_SequenceType SpiSequenceUsed =
              CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvSpiSequence;
  uint8 ChannelId =
                CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvChannelId;
  uint16 DestBuf;
  uint8 PnIndex = CanTrcv_17_W9255_PnConfigured[ChannelId];

  /* [cover parentID={2A7AA021-421B-48e5-8865-2C5D524C3B02}]
  Is PN enabled for the channel?
  [/cover] */
  if(PnIndex != CANTRCV_17_W9255_PN_NOT_CONFIGURED)
  {
    /* Read the status of SYSERR and POR flags */
    CanTrcv_17_W9255_SourceBuffer[ChannelId] =
        CANTRCV_17_W9255_READ_SWK_STAT;

    /* [cover parentID={3536E412-4EDB-4383-A150-FCCACF8379CC}]
    Read the status of POR and SYSERR flags and update the return status
    [/cover] */
    ReturnValue = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                  &CanTrcv_17_W9255_DestBuffer[ChannelId], serviceId,
                  (uint8)CANTRCV_17_W9255_REPORT_DET);
    DestBuf = CanTrcv_17_W9255_DestBuffer[ChannelId];

    /* [cover parentID={A1B5CEA7-29DA-4bd7-90F4-811544E9397D}]
    Is return status E_OK and if any of the flags are set?
    [/cover] */
    if((ReturnValue == E_OK) &&
        (((DestBuf & CANTRCV_17_W9255_POR_CHECK) ==
          CANTRCV_17_W9255_POR_CHECK) ||
         ((DestBuf & CANTRCV_17_W9255_SYSERR_CHECK) ==
          CANTRCV_17_W9255_SYSERR_CHECK)))
    {
      /* [cover parentID={982E9038-CE06-43b0-B424-BF6951AEF6E9}]
      Is POR flag set?
      [/cover] */
      if(((DestBuf & CANTRCV_17_W9255_POR_CHECK) ==
          CANTRCV_17_W9255_POR_CHECK))
      {
        /* Configure HW_CTRL register for LWU and RxD behavior */
        CanTrcv_17_W9255_SourceBuffer[ChannelId] =
            CANTRCV_17_W9255_INITIALIZE_HW_CTRL;

        /* [cover parentID={362A5493-51C8-4540-B282-B3C8AE479E66}]
        Reinitialize HW_CTRL register and update the return status
        [/cover] */
        ReturnValue = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                      &CanTrcv_17_W9255_DestBuffer[ChannelId],
                      serviceId,
                      (uint8)CANTRCV_17_W9255_REPORT_DET);
        /* [cover parentID={89DE9005-90BC-4855-9517-ADCE92796677}]
        Is return status E_OK?
        [/cover] */
        if(ReturnValue == E_OK)
        {
          CanTrcv_17_W9255_SourceBuffer[ChannelId] =
              CANTRCV_17_W9255_CLEAR_POR;
          ReturnValue = CanTrcv_17_W9255_lSpiRetries (SpiSequenceUsed,
                        &CanTrcv_17_W9255_DestBuffer[ChannelId], serviceId,
                        (uint8)CANTRCV_17_W9255_REPORT_DET);
        }
      }
      else
      {
        CanTrcv_17_W9255_WuReason[ChannelId] = CANTRCV_WU_BY_SYSERR;
      }
      #if (CANTRCV_17_W9255_PN_CONFIGURED_CHANNELS > 0U)
      /* [cover parentID={B15E91BE-0915-45d3-9C95-FD5B3DC99820}]
      Is return status E_OK?
      [/cover] */
      if(ReturnValue == E_OK)
      {
        /* [cover parentID={713CCC5C-EB42-431a-9AD0-9D4F36A211A4}]
        Reinitialize for selective wake functionality and update the
        return status
        [/cover] */
        ReturnValue = CanTrcv_17_W9255_lHardwareInitPN
                      (SpiSequenceUsed, ChannelId, serviceId);
      }
      #endif
    }
      /* [cover parentID={3FE081FA-EF8F-4c37-B658-0658AAC2BE04}]
      Is return status E_OK, SYSERR flag not set and requested mode NORMAL?
      [/cover] */
      if((ReturnValue == E_OK) &&
          ((DestBuf & CANTRCV_17_W9255_SYSERR_CHECK) ==
           CANTRCV_17_W9255_CLEAR_REG) && (OpMode == CANTRCV_TRCVMODE_NORMAL))
      {
        /* [cover parentID={B2BF431C-0E66-44e9-BDA3-71B2AD4CE501}]
        Inform CanIf about PN availablity
        [/cover] */
        CanIf_ConfirmPnAvailability(ChannelId);
      }
  }

  return ReturnValue;
}


/*******************************************************************************
** Traceability   : [cover parentID={F9665BD0-39D0-410a-8FC9-F355DEF2636A}]   **
**                                                                            **
** Syntax         : static Std_ReturnType CanTrcv_17_W9255_lWuReasonChecks    **
**                  (const uint8 ChannelIndex,                                **
**                   const CanTrcv_TrcvModeType Mode,                         **
**                   const uint8 serviceId,                                   **
**                   const CanTrcv_TrcvModeType OpMode)                       **
**                                                                            **
** Description    : This function checks and updates wake up reason due to    **
**                  POR, SYSERR or an internal mode change request to NORMAL  **
**                  mode                                                      **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Non-Reentrant                                             **
**                                                                            **
** Parameters(in) : ChannelIndex - Channel index                              **
**                  Mode -  Current mode                                      **
**                  serviceId - Service Id of the API                         **
**                  OpMode - Mode to be set                                   **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : E_OK: Wake-up reasons were checked successfully           **
**                  E_NOT_OK: Wake-up reason  check failed                    **
**                                                                            **
*******************************************************************************/
static Std_ReturnType CanTrcv_17_W9255_lWuReasonChecks(const uint8 ChannelIndex,
    const CanTrcv_TrcvModeType Mode, const uint8 serviceId,
    const CanTrcv_TrcvModeType OpMode)
{
  Std_ReturnType ReturnValue = E_OK;
  uint8 ChannelId =
               CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvChannelId;
  uint8 PnIndex = CanTrcv_17_W9255_PnConfigured[ChannelId];
  Spi_SequenceType SpiSequenceUsed =
             CanTrcv_17_W9255_ChannelConfig[ChannelIndex].CanTrcvSpiSequence;
  uint16 DestBuf;
  /* [cover parentID={0874A991-BC66-47a8-BF55-B2C51B24100F}]
  Wake-up checks and wake-up reason updation in APIs
  [/cover] */
  /* [cover parentID={4525BD90-9118-4e28-9654-8D0B3FAEA5DC}]
  Is PN enabled?
  [/cover] */
  if(PnIndex != CANTRCV_17_W9255_PN_NOT_CONFIGURED)
  {
    /* Read the status of SYSERR and POR flags */
    CanTrcv_17_W9255_SourceBuffer[ChannelId] =
        CANTRCV_17_W9255_READ_SWK_STAT;
    ReturnValue = CanTrcv_17_W9255_lSpiRetries(SpiSequenceUsed,
                  &CanTrcv_17_W9255_DestBuffer[ChannelId], serviceId,
                  (uint8)CANTRCV_17_W9255_REPORT_DET);
    DestBuf = CanTrcv_17_W9255_DestBuffer[ChannelId];

    /* [cover parentID={FFA554AE-39DF-474f-9894-9DE58A7470D9}]
    Is return status E_OK and has POR/SYSERR occurred?
    [/cover] */
    if((ReturnValue == E_OK) &&
        (((DestBuf & CANTRCV_17_W9255_POR_CHECK) ==
          CANTRCV_17_W9255_POR_CHECK) ||
         ((DestBuf & CANTRCV_17_W9255_SYSERR_CHECK) ==
          CANTRCV_17_W9255_SYSERR_CHECK)))
    {

      /* [cover parentID={9D495350-568B-4fc1-B899-3D6311C47A42}]
      Has POR occurred?
      [/cover] */
      if(((DestBuf & CANTRCV_17_W9255_POR_CHECK) ==
          CANTRCV_17_W9255_POR_CHECK))
      {
        CanTrcv_17_W9255_WuReason[ChannelId] = CANTRCV_WU_POWER_ON;
      }
      else
      {
        /* [cover parentID={2FB72402-610C-4ac4-B6ED-B29A5E247A8B}]
        Is the transceiver transitting from STANDBY to NORMAL?
        [/cover] */
        if((Mode == CANTRCV_TRCVMODE_STANDBY) &&
            (OpMode == CANTRCV_TRCVMODE_NORMAL))
        {
          CanTrcv_17_W9255_WuReason[ChannelId] = CANTRCV_WU_INTERNALLY;
        }
      }
    }
    else
    {
      /* [cover parentID={3A331CAC-9DFC-43c1-BAC8-9193E75E1BF8}]
      Is the transceiver transitting from STANDBY to NORMAL?
      [/cover] */
      if((Mode == CANTRCV_TRCVMODE_STANDBY) &&
          (OpMode == CANTRCV_TRCVMODE_NORMAL))
      {
        CanTrcv_17_W9255_WuReason[ChannelId] = CANTRCV_WU_INTERNALLY;
      }
    }
  }
  else
  {
    /* [cover parentID={2FB72402-610C-4ac4-B6ED-B29A5E247A8B}]
    Is the transceiver transitting from STANDBY to NORMAL?
    [/cover] */
    if((Mode == CANTRCV_TRCVMODE_STANDBY) &&
        (OpMode == CANTRCV_TRCVMODE_NORMAL))
    {
      CanTrcv_17_W9255_WuReason[ChannelId] = CANTRCV_WU_INTERNALLY;
    }
  }

  /* [cover parentID={4C64E7AC-7E56-4789-8E19-E19550CE6689}]
  Is the transceiver transitting from SLEEP to NORMAL?
  [/cover] */
  if((Mode == CANTRCV_TRCVMODE_SLEEP) && (OpMode == CANTRCV_TRCVMODE_NORMAL))
  {
    CanTrcv_17_W9255_WuReason[ChannelId] = CANTRCV_WU_INTERNALLY;
  }
  return ReturnValue;
}
#if (CANTRCV_17_W9255_GENERAL_WAKE_UP_SUPPORT ==    \
CANTRCV_17_W9255_WAKE_UP_BY_POLLING)
/******************************************************************************
** Traceability    : [cover parentID={AE720230-2ADF-42f7-B2A7-B8B2DEA2CD66}] **
**                                                                           **
** Syntax          : static Std_ReturnType CanTrcv_17_W9255_lPollWakeup      **
**                    (const uint8 Transceiver,                              **
**                    const Spi_SequenceType SpiSequenceId)                  **
**                                                                           **
** Description     :  This function detects valid wakeup on the channel      **
**                                                                           **
** [/cover]                                                                  **
**                                                                           **
** Service ID      :  NA                                                     **
**                                                                           **
** Sync/Async      :  Synchronous                                            **
**                                                                           **
** Reentrancy      :  Non-Reentrant                                          **
**                                                                           **
** Parameters (in) :  Transceiver - CAN transceiver to which API call has    **
**                                to be applied.                             **
**                    SpiSequenceId - SPI sequence used for the channel      **
**                                                                           **
** Parameters (out):  none                                                   **
**                                                                           **
** Return value    :  E_OK: Channel has been checked for valid wakeup events **
**                          successfully                                     **
**                    E_NOT_OK: Failed to check the Channel for valid wakeup **
**                              events                                       **
**                                                                           **
******************************************************************************/
static Std_ReturnType CanTrcv_17_W9255_lPollWakeup (const uint8 Transceiver,
    const Spi_SequenceType SpiSequenceId)
{
  Std_ReturnType ReturnValue;
  uint16 DestBuf;
  /* Read WAKE_STAT register */
  CanTrcv_17_W9255_SourceBuffer[Transceiver] =
      CANTRCV_17_W9255_READ_WAKE_STAT;
  ReturnValue = CanTrcv_17_W9255_lSpiRetries(SpiSequenceId,
                &CanTrcv_17_W9255_DestBuffer[Transceiver],
                CANTRCV_17_W9255_SID_MAINFUNCTION,
                (uint8)CANTRCV_17_W9255_DET_DISABLE);

  DestBuf = CanTrcv_17_W9255_DestBuffer[Transceiver];

  /* [cover parentID={15CAAA57-8B11-4e7c-8C56-F35A190674BB}]
  Is return status E_OK?
  [/cover] */
  if (ReturnValue == E_OK)
  {
    /* Read the status of SYSERR flag */
    CanTrcv_17_W9255_SourceBuffer[Transceiver] =
        CANTRCV_17_W9255_READ_SWK_STAT;
    ReturnValue = CanTrcv_17_W9255_lSpiRetries(SpiSequenceId,
                  &CanTrcv_17_W9255_DestBuffer[Transceiver],
                  CANTRCV_17_W9255_SID_MAINFUNCTION,
                  (uint8)CANTRCV_17_W9255_DET_DISABLE);
  }

  /* [cover parentID={350D1B57-C2BD-464e-B411-FB2E4B0A3E94}]
  Is return status E_OK?
  [/cover] */
  if (ReturnValue == E_OK)
  {
    /* [cover parentID={4A3EE444-4113-4b25-8C53-27F2024F39A7}]
    Is wake detected?
    [/cover] */
    /* Check if wake is detected */
    if(((DestBuf & CANTRCV_17_W9255_LWU_CHECK) ==
        CANTRCV_17_W9255_LWU_CHECK) ||
        ((DestBuf & CANTRCV_17_W9255_WUP_CHECK)
         == CANTRCV_17_W9255_WUP_CHECK) ||
        ((DestBuf & CANTRCV_17_W9255_WUF_CHECK)
         == CANTRCV_17_W9255_WUF_CHECK) ||
        ((CanTrcv_17_W9255_DestBuffer[Transceiver] &
          CANTRCV_17_W9255_SYSERR_CHECK) ==
         CANTRCV_17_W9255_SYSERR_CHECK))
    {

      CanTrcv_17_W9255_WakeupFlagIndication[Transceiver] = 1U;

      /* [cover parentID={018F1470-FFCD-48c9-870A-99802937D603}]
      Check if WUF or WUP bits are set
      [/cover] */
      /* Check if the wakeup is due to pattern/frame */
      if(((DestBuf & CANTRCV_17_W9255_WUP_CHECK)
          == CANTRCV_17_W9255_WUP_CHECK) ||
          ((DestBuf & CANTRCV_17_W9255_WUF_CHECK)
           == CANTRCV_17_W9255_WUF_CHECK))
      {
        /* Set the Wake up reason to Wake up by bus */
        CanTrcv_17_W9255_WuReason[Transceiver] = CANTRCV_WU_BY_BUS;
      }
      /* [cover parentID={47484B9E-AD71-4074-928E-4A29A72D5FD9}]
      Check if LWU is set
      [/cover] */
      else if(((DestBuf & CANTRCV_17_W9255_LWU_CHECK) ==
               CANTRCV_17_W9255_LWU_CHECK))
      {
        /* Set the Wake up reason to Wake up by pin */
        CanTrcv_17_W9255_WuReason[Transceiver] = CANTRCV_WU_BY_PIN;
      }
      else
      {
        CanTrcv_17_W9255_WuReason[Transceiver] = CANTRCV_WU_BY_SYSERR;
      }
    }
  }
  return ReturnValue;
}
#endif
/******************************************************************************
** Traceability   : [cover parentID={ACCE863E-E990-417f-B0DC-B56987205E17}]  **
**                                                                           **
** Syntax         : static Std_ReturnType CanTrcv_17_W9255_lSpiBusyCheck     **
**                  (void)                                                   **
**                                                                           **
** Description    : This function will check if the SPI status is busy       **
**                                                                           **
** [/cover]                                                                  **
**                                                                           **
** Sync/Async     : Synchronous                                              **
**                                                                           **
** Reentrancy     : Non-Reentrant                                            **
**                                                                           **
** Parameters(in) : ChannelId : Id of the transceiver channel                **
**                                                                           **
** Parameters(out): None                                                     **
**                                                                           **
** Return value   : E_OK : Spi is free for communication                     **
**                  E_NOT_OK : Spi is busy                                   **
**                                                                           **
******************************************************************************/
static Std_ReturnType CanTrcv_17_W9255_lSpiBusyCheck(const uint8 ChannelId)
{
  Std_ReturnType ReturnValue;

  /* [cover parentID={4C18FD5E-224A-4ade-96AD-5255A25950F1}]
  Critical section
  [/cover] */
  /* [cover parentID={6AEA0DB4-DEA8-4a5a-963E-7662827D145D}]
  Start of Critical Section
  [/cover] */
  SchM_Enter_CanTrcv_17_W9255_SpiStatusUpdate();

  /* [cover parentID={F7F91D96-2EFB-45fd-B761-C23AD375E9E9}]
  Check if SPI channel for the respective transceiver channel is busy
  [/cover] */
  if(CanTrcv_17_W9255_SpiBusyStatus[ChannelId] == 1U)
  {
    ReturnValue = E_NOT_OK;
  }
  else
  {
    CanTrcv_17_W9255_SpiBusyStatus[ChannelId] = 1U;
    ReturnValue = E_OK;
  }

  /* [cover parentID={7638D215-65B7-42d4-85EF-380C3D1B6396}]
  End of Critical Section
  [/cover] */
  SchM_Exit_CanTrcv_17_W9255_SpiStatusUpdate();

  return ReturnValue;
}

#define CANTRCV_17_W9255_STOP_SEC_CODE_QM_LOCAL
/* [cover parentID={03C90BFA-850A-4b3e-9D6E-51E503B46FE9}]
    MemMap file  [/cover] */
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]
    MemMap mapping for code  [/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
    MemMap mapping  [/cover] */
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
Callout Memory section not used in CanTrcv_17_W9255 driver
[/cover]*/
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
Const Memory section not used in CanTrcv_17_W9255 driver
[/cover] */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_W9255_MemMap.h"
