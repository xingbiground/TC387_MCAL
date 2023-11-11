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
**  FILENAME     : Gpt.c                                                      **
**                                                                            **
**  VERSION      : 44.0.0                                                     **
**                                                                            **
**  DATE         : 2023-05-16                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY : [cover parentID={10553D6E-883D-4257-9EFC-7FDFD75F6C57} ]   **
**                                                                            **
**  DESCRIPTION  : GPT Driver source file                                     **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of GPT Driver, AUTOSAR Release 4.2.2     **
**                                                              and 4.4.0     **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* GPT Module header file, this includes GPT Static configuration file also */
/* [cover parentID={11FB42A1-19F9-418a-99FB-1B2F923F5FE3}] */

/* Implementation features */
/* [cover parentID= {EFBFFFCD-33C2-4977-A88A-976F258A1823}] */ 

/* Safety properties */
/* [cover parentID=  {9ECDE779-B732-48ce-8855-2C1AD7687FD7}] */

/* [cover parentID={F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}][/cover] */

#include "Gpt.h"

#include "Gpt_Cbk.h"
#include "SchM_Gpt.h"
/* [/cover] */
#if ((GPT_TOM_USED == STD_ON) || (GPT_ATOM_USED == STD_ON))
#include "IfxGtm_reg.h"
#endif

#if (GPT_GPT12_USED == STD_ON)
#include "IfxGpt12_reg.h"
#endif
/* [cover parentID={9083125E-8A84-4f79-A181-9F883842A012}] */
/* Import of DET functionality.*/
#if (GPT_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

#if (GPT_RUNTIME_ERROR_DETECT == STD_ON)
#include "Mcal_Wrapper.h"
#endif

/* Import of Safety functionality.*/
#if (GPT_SAFETY_ENABLE == STD_ON)
#include "Mcal_SafetyError.h"
#endif
/* [/cover] */
/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/
/* [cover parentID={7C464C41-ED25-4763-97AB-56FC549EF845}] */
/* Check for definition of the AS Version */
#ifndef GPT_AR_RELEASE_MAJOR_VERSION
#error "GPT_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

#if ( GPT_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION)
#error "GPT_AR_RELEASE_MAJOR_VERSION does not match. "
#endif

#ifndef GPT_AR_RELEASE_MINOR_VERSION
#error "GPT_AR_RELEASE_MINOR_VERSION is not defined."
#endif

#if (GPT_AR_RELEASE_MINOR_VERSION != MCAL_AR_RELEASE_MINOR_VERSION)
#error "GPT_AR_RELEASE_MINOR_VERSION does not match."
#endif

#ifndef GPT_AR_RELEASE_REVISION_VERSION
#error "GPT_AR_RELEASE_REVISION_VERSION is not defined."
#endif

#if (GPT_AR_RELEASE_REVISION_VERSION != MCAL_AR_RELEASE_REVISION_VERSION)
#error "GPT_AR_RELEASE_REVISION_VERSION does not match."
#endif

/* Check for definition of SW version Information */
#ifndef GPT_SW_MAJOR_VERSION
#error "GPT_SW_MAJOR_VERSION is not defined. "
#endif

#ifndef GPT_SW_MINOR_VERSION
#error "GPT_SW_MINOR_VERSION is not defined. "
#endif

#ifndef GPT_SW_PATCH_VERSION
#error "GPT_SW_PATCH_VERSION is not defined."
#endif

#if ( GPT_SW_MAJOR_VERSION != 20U )
#error "GPT_SW_MAJOR_VERSION does not match. "
#endif

#if ( GPT_SW_MINOR_VERSION != 25U )
#error "GPT_SW_MINOR_VERSION does not match. "
#endif

#if (GPT_SW_PATCH_VERSION != 0U)
#error "GPT_SW_PATCH_VERSION does not match."
#endif
/*  [/cover] */

/* DET version check */
/* [cover parentID={F90D9A34-44E9-4871-96D7-1134D7C426D6}] */
#if ( GPT_DEV_ERROR_DETECT == STD_ON)

#ifndef DET_AR_RELEASE_MAJOR_VERSION
#error "DET_AR_RELEASE_MAJOR_VERSION is not defined."
#endif

#if ( DET_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION )
#error "DET_AR_RELEASE_MAJOR_VERSION does not match."
#endif
#endif /* End for GPT_DEV_ERROR_DETECT */
/*  [/cover] */

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
/* Marcos used to avoid magic numbers in source code */ 
/* Marco used to clear the error flag */

/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is used across the code in
multiple conditions.
Hence this macro will be unused in some pre-compile conditions */
#define GPT_E_DET_NO_ERR                ((uint8)0U)

/* Marco used to set the error flag */
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is used across the code in
multiple conditions.
Hence this macro will be unused in some pre-compile conditions */
#define GPT_E_DET_ERR                   ((uint8)1U)

/* Status of the GPT Driver */
#define GPT_DRIVER_UNINITIALIZED        ((uint8)0U)
#if (GPT_DEINIT_API == STD_ON)
#define GPT_DRIVER_UNINITIALIZ_REQ      ((uint8)1U)
#endif
#define GPT_DRIVER_INITIALIZED          ((uint8)2U)
#define GPT_CORE_STATUS_LEN             (2)

#if (GPT_TOM_USED == STD_ON)
/* Macros used for Max value that a TOM channel can have */
#define GPT_GTM_TOM_TIMER_MAX           ((uint32)0xFFFFU)
#endif

#if (GPT_ATOM_USED == STD_ON)
/* Macros used for Max value that a ATOM channel can have */
#define GPT_GTM_ATOM_TIMER_MAX          ((uint32)0xFFFFFFU)
#endif

#if ((GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON) || \
     (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON) || \
     (GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON))
#define GPT_GTM_TOM_PREDEFTIMER_MAX     ((uint32)0x10000U)
#endif

#if (GPT_GPT12_USED  == STD_ON)
#define GPT_GPT12_TIMER_MAX             ((uint32)0xFFFFU)
#define GPT_GPT12_REL_DELAYOFFSET       ((uint32)0x1U)
#define GPT_GPT12_TIBPS_MASK            ((uint32)0x00001807U)
#define GPT_GPT12_TIBPS_VAL             ((uint32)0x00000800U)
#define GPT_GPT12_START_MASK            ((uint32)0x00000040U)
#define GPT_GPT12_STOP_MASK             ((uint32)0xFFFFFFBFU)

#if (GPT_ONESHOT_USED == STD_ON)
#define GPT_GPT12_TOTL_MASK             ((uint32)0xFFFFFBFFU)

#if ((GPT_TIME_REMAINING_API == STD_ON) || (GPT_TIME_ELAPSED_API == STD_ON))
#define GPT_GPT12_TOTL_BIT              (0x0AU)
#endif

#endif
#endif

/* Value to be written onto the notify register to clear the interrupts */
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is used across the code in
multiple conditions.
Hence this macro will be unused in some pre-compile conditions */
#define GPT_CLEAR_INTERRUPTS            ((uint32)0x00000003U)

/* Macro related to TOM Bit positions */
/* Value to be written onto the notify register to clear the interrupts */
/* MISRA2012_RULE_2_5_JUSTIFICATION: This macro is used across the code in
multiple conditions.
Hence this macro will be unused in some pre-compile conditions */
#define GPT_GTM_CTRL_OSM                ((uint8)26U)

#if (GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON)
/* Mask for 24 Bit Predef Timer with 1us tick */
#define GPT_24BIT_MASK                ((uint32)0xFFFFFFU)
#endif

/* Macro to fetch the core ID */
#if (GPT_MAX_CORE_USED > 1U)
#define GPT_INVALID_CHANNEL           ((uint8)0xFFU)
#endif

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro defined for easy
 * readability in code. No side effects foreseen by violating this MISRA rule.
 */
#define GPT_GET_COREID()              (Mcal_GetCpuIndex())

/* Macro to get the bit position of the core in Gpt_DriverStatus */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro defined for easy
 * readability in code. No side effects foreseen by violating this MISRA rule.
 */
#define GPT_CORE_BITPOS(COREID)       ((uint8)(COREID << 0x1U))

/* Macro to get the ConfigPtr to the core */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro defined for easy
 * readability in code. No side effects foreseen by violating this MISRA rule.
 */
#define GPT_GET_CORECONFIGPTR(COREID)\
                                  (Gpt_ConfigPtr->Gpt_Config_CorePtr[COREID])
#if (GPT_TOM_USED == STD_ON) || (GPT_ATOM_USED == STD_ON)
/* Macro to get the GTM Timer Info */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro defined for easy
 * readability in code. No side effects foreseen by violating this MISRA rule.
 */
#define GPT_GET_GTMTIMERINFO(COREID, CHANNEL)                                  \
                  ((&(GPT_GET_CORECONFIGPTR(COREID))->                         \
                                  ChannelConfigPtr[CHANNEL])->GptGtmTimerInfo[0])
#endif
#if (GPT_GPT12_USED == STD_ON)
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'GPT_GET_GPT12TIMERINFO'
 * defined for extratct GPT12 timer info.
 * No side effects foreseen by violating this MISRA rule. */
#define GPT_GET_GPT12TIMERINFO(COREID, CHANNEL, INDEX)                               \
                  ((&(GPT_GET_CORECONFIGPTR(COREID))->                         \
                              ChannelConfigPtr[CHANNEL])->GptGpt12TimerInfo[INDEX])

#endif
/*#if (GPT_GPT12_USED == STD_ON)*/
#if ((GPT_PREDEF_TIMER_1US_16BIT_EN == STD_ON)    || \
     (GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON)    || \
     (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))

/* Bit position of 100us Predef Timer in Driver Status */
#define GPT_1USPREDEFTIMER_BITPOS           ((uint8)MCAL_NO_OF_CORES * 2U)

/* Macro to set status */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro defined for easy
 * readability in code. No side effects foreseen by violating this MISRA rule.
 */
#define GPT_SET_1US_PREDEF_TIMER_STS(STS)                        \
      Mcal_SetBitAtomic(&Gpt_DriverStatus, GPT_1USPREDEFTIMER_BITPOS, 0x3, STS)

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro defined for easy
 * readability in code. No side effects foreseen by violating this MISRA rule.
 */
#define GPT_GET_1US_PREDEF_TIMER_STS()                           \
      Mcal_GetBitAtomic(Gpt_DriverStatus, GPT_1USPREDEFTIMER_BITPOS, 0x3)
#endif

#if (GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON)

/* BitPosition of 100us Predef Timer in Driver Status */
#define GPT_100USPREDEFTIMER_BITPOS   ((uint8)((MCAL_NO_OF_CORES * 2U) + 3U))

/* Macro to set status */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro defined for easy
 * readability in code. No side effects foreseen by violating this MISRA rule.
 */
#define GPT_SET_100US_PREDEF_TIMER_STS(STS)                       \
    Mcal_SetBitAtomic(&Gpt_DriverStatus, GPT_100USPREDEFTIMER_BITPOS, 0x3, STS)

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro defined for easy
 * readability in code. No side effects foreseen by violating this MISRA rule.
 */
#define GPT_GET_100US_PREDEF_TIMER_STS()                          \
    Mcal_GetBitAtomic(Gpt_DriverStatus, GPT_100USPREDEFTIMER_BITPOS, 0x3)
#endif

#if (GPT_INITCHECK_API == STD_ON)
#define GPT_INITCHECK_STS_VAL               (0xFFFFFFFFU)
#endif

#if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_MULTICORE_ERROR_DETECT == STD_ON))
#if (GPT_DEINIT_API == STD_ON)
#define SLAVE_CORE_STATUS_MASK              (uint32)((1UL << (uint8)\
                                            (MCAL_NO_OF_CORES * 2U)) - 1U)
#endif
#endif
#if ((GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) || (\
(GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) && (GPT_REPORT_WAKEUP_SOURCE == STD_ON)\
))
#if (GPT_TOM_USED == STD_ON) || (GPT_ATOM_USED == STD_ON)
#define GPT_ENABLE_IRQ                      (0x01)
#define GPT_DISABLE_IRQ                     (0x00)
#endif
#endif
#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
#define GPT_NOTIF_MSK                       ((uint32)0x01U)
#define GPT_ENABLE_NOTIF                    (0x01U)
#define GPT_BITLEN_NOTIF                    (0x01)
#define GPT_BITPOS_NOTIF                    (0x00U)
#define GPT_DISABLE_NOTIF                   (0x00U)
#endif
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
#if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
#define GPT_BITPOS_WAKEUP                   (0x01U)
#define GPT_BITLEN_WAKEUP                   (0x01)
#define GPT_WAKEUP_ENABLED                  (0x01)
#endif
#endif
#if ((GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) && ((GPT_TOM_USED == STD_ON)|| \
    (GPT_ATOM_USED == STD_ON) || (GPT_REPORT_WAKEUP_SOURCE == STD_ON))) 
/* Macro used to set/clear wakeup notification flag */
#define GPT_WAKEUP_MSK                      ((uint32)0x02U)
#define GPT_WAKEUP_DISABLED                 ((uint32)0x00)
#endif
/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/
/* [cover parentID={1032E60F-F757-4c9f-A8FC-99D06BD04BD8}] */
/* Global Variables required in the driver (private to GPT.c) */
typedef struct
{
  /* Variable to store the Driver mode (GPT_MODE_SLEEP/GPT_MODE_NORMAL) in
   * context to the core
   */
  Gpt_ModeType Gpt_DriverMode;

  #if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
  #if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
  /* Variable to store the channel wakeup info due to which GPT woke up */
  EcuM_WakeupSourceType Gpt_WakeupChannelInfo;
  #endif
  #endif
  /* End of #if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) */
  #if (GPT_GPT12_USED == STD_ON)
  uint32 *const Gpt_Targettime;
  #endif
  /* Pointer to a variable to store channel status.
   * i.e. Channel Initialized/Running/Stopped/Expired/Uninitialized
   */
  uint32 *const Gpt_ChannelStatusPtr;
 
  #if ((GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) || \
       (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
  /* Pointer to a variable to store Notification and WakeUp Flag for channels
   * mapped to a certain core.
   *
   * Bit7       Bit2          Bit1                Bit0
   *  --------------------------------------------
   * | reserved | WakeUp flag | Notification flag |
   *  --------------------------------------------
   */
  uint32 *const Gpt_FlagPtr;
  #endif

} Gpt_ThreadSafeDataType;
/*  [/cover] */
/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}] */
/* Memory mapping for code */
/* [/cover] */
#define GPT_START_SEC_CODE_ASIL_B_GLOBAL

/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
/*[cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}][/cover]*/
/*[cover parentID={CDC53A42-9F15-4a14-877A-1DF68CCE5ED1}][/cover]*/
#include "Gpt_MemMap.h"

#if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
/* Function to check DET errors in Gpt_Init API. */
static uint32 Gpt_lInitDetCheck(const Gpt_ConfigType *const ConfigPtr,
                                const uint32 CurrentCoreId);
#endif

#if (GPT_TOM_USED == STD_ON) || (GPT_ATOM_USED == STD_ON)
/* Function to initialize all channels except Predef timer channels. */
static void Gpt_lGtmChannelInit
(const Gpt_ChannelConfigType *const GptChannelPtr);

/* Function to stop a GPT timer from counting. */
static void Gpt_lGtmStopTimer(const Gpt_ChannelType Channel,
                              const uint32 CurrentCoreId);

/* Function to start the GPT timer to count until TimeOutVal */
static void Gpt_lGtmStartTimer
                              (
                                const Gpt_ChannelType Channel,
                                const uint32 TimeOutVal,
                                const uint32 CurrentCoreId
                              );
#endif
#if (GPT_GPT12_USED == STD_ON)
/*Function to perform GPT12 channel Init */                              
static void Gpt_lGpt12ChannelInit
                             (const Gpt_ChannelConfigType *const GptChannelPtr);
                             
/*Function to start GPT12 channel */  
static void Gpt_lGpt12StartTimer
                              (
                                const Gpt_ChannelType Channel,
                                const uint32 TimeOutVal,
                                const uint32 CurrentCoreId
                              );
/*Function to stop GPT12 channel */                              
static void Gpt_lGpt12StopTimer 
                              (
                                const Gpt_ChannelType Channel,
                                const uint32 CurrentCoreId
                              );
#endif

#if ((GPT_TIME_REMAINING_API == STD_ON) && (GPT_GPT12_USED == STD_ON))
/*Function to get GPT12 channel time remaining */  
static uint32 Gpt_lGpt12GetTimeRemaining
                           (const Gpt_ChannelConfigType *const GptChannelPtr, 
                            const Gpt_ChannelType LocalChannel, 
                            const uint32 CurrentCoreId);
#endif
#if ((GPT_TIME_ELAPSED_API == STD_ON) && (GPT_GPT12_USED == STD_ON))                           
/*Function to get GPT12 channel time elapsed */ 
static uint32 Gpt_lGpt12GetTimeElapsed
                            (
                              const Gpt_ChannelConfigType *const GptChannelPtr, 
                              const Gpt_ChannelType LocalChannel, 
                              const uint32 CurrentCoreId
                            );
#endif
#if ((GPT_ONESHOT_USED == STD_ON) && (GPT_GPT12_USED == STD_ON))
LOCAL_INLINE void Gpt_lGpt12HandleOsm
                            (const Gpt_ChannelConfigType *const GptChannelPtr);
#endif

#if ((GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON)  || \
     (GPT_PREDEF_TIMER_1US_16BIT_EN == STD_ON)    || \
     (GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON)    || \
     (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))
/* API to check DET errors in Gpt_lGetPredefErrCheck API */
static uint32 Gpt_lGetPredefErrCheck
                                    (
                                      const Gpt_PredefTimerType PredefTimer,
                                      const uint32 *const TimeValuePtr,
                                      const uint32 CurrentCoreId
                                    );
/* API to check PredefTimer passed by user is valid */
LOCAL_INLINE uint32 Gpt_lCheckPredefTimer
                                    (
                                      const Gpt_PredefTimerType PredefTimer, 
                                      const uint32 CurrentCoreId
                                    );
#endif

#if (GPT_DEINIT_API == STD_ON)
/* API to reset the channels configured for GPT back to their power on
reset state */
static void Gpt_lResetChannel(const Gpt_ChannelConfigType *GptChannelPtr);

#if((GPT_SAFETY_ENABLE == STD_ON) || (GPT_RUNTIME_ERROR_DETECT == STD_ON)||\
    (GPT_DEV_ERROR_DETECT == STD_ON)) 
/* API to check DET errors in Gpt_DeInit API */
static uint32 Gpt_lDeInitDetCheck(const uint32 CurrentCoreId);
#endif
/* End of #if ((GPT_SAFETY_ENABLE == STD_ON) || \
                                  (GPT_DEV_ERROR_DETECT == STD_ON)) */

#endif
/* End of #if (GPT_DEINIT_API == STD_ON) */

#if (GPT_ONESHOT_USED == STD_ON)
#if ((GPT_TOM_USED == STD_ON) || (GPT_ATOM_USED == STD_ON))
/* API to stop a TOM/ATOM channel in one shot mode. */
LOCAL_INLINE void Gpt_lGtmHandleOsm(const Gpt_ChannelConfigType *GptChannelPtr);
#endif
/* API to check if the channel is in one shot mode configuration */
LOCAL_INLINE void Gpt_lHandleOsmChannel
                                  (
                                    const Gpt_ChannelConfigType *GptChannelPtr,
                                    const Gpt_ChannelType Channel,
                                    const uint32 CurrentCoreId
                                  );
#endif
/* End of #if (GPT_ONESHOT_USED == STD_ON) */

#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/* Service to switch from sleep to normal mode   */
LOCAL_INLINE void Gpt_lSetNormalMode (
                                      const Gpt_CoreConfigType *LocalCoreConfigPtr, 
                                      const uint32 CurrentCoreId);

/* Service to switch from normal to sleep mode */
LOCAL_INLINE void Gpt_lSetSleepMode( 
                              const Gpt_CoreConfigType *LocalCoreConfigPtr, 
                              const uint32 CurrentCoreId 
                                   );

#if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
/* API to check if the WakeUp flag is set for the corresponding channel when the
GPT driver is in SLEEP mode. */
LOCAL_INLINE void Gpt_lHandleWakeupEvent
                                  (
                                    const Gpt_ChannelConfigType *GptChannelPtr,
                                    const Gpt_ChannelType Channel,
                                    const uint32 CurrentCoreId
                                  );
#endif
/* End of #if (GPT_REPORT_WAKEUP_SOURCE == STD_ON) */

#if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
/* API to check DET errors in Gpt_EnableWakeup & Gpt_DisableWakeup APIs */
static uint32 Gpt_lWakeupDetCheck (
                                    const Gpt_ChannelType Channel, 
                                    const uint8 Gpt_Sid,           
                                    const uint32 CurrentCoreId     
                                  );

static uint32 Gpt_lSetModeDetCheck(
                                    const Gpt_ModeType Mode,  
                                    const uint32 CurrentCoreId
                                  );
#endif

#endif
/* End of #if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON ) */

#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
#if (GPT_TOM_USED == STD_ON) || (GPT_ATOM_USED == STD_ON)
LOCAL_INLINE boolean Gpt_lModeCont(const Gpt_ChannelModeType ChannelMode);
#endif
#endif

#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)

#if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
/* API to check for DETs for the APIs Gpt_EnableNotification and
Gpt_DisableNotification */
static uint32 Gpt_lNotifDetCheck (
                                    const Gpt_ChannelType Channel,  
                                    const uint8 Gpt_Sid,            
                                    const uint32 CurrentCoreId      
                                  );
#endif
/* End of #if ((GPT_SAFETY_ENABLE == STD_ON) || \
                                            (GPT_DEV_ERROR_DETECT == STD_ON)) */

/* API to check if the notification flag is set for the corresponding channel
when the GPT driver is in NORMAL mode */
LOCAL_INLINE void Gpt_lHandleNotifCall
                                  (
                                    const Gpt_ChannelConfigType *GptChannelPtr,
                                    const Gpt_ChannelType Channel,
                                    const uint32 CurrentCoreId
                                  );
#endif
/* End of #if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) */
#if ((GPT_TOM_USED == STD_ON) || (GPT_ATOM_USED == STD_ON))
#if ((GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) || \
     (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
/* API to enable/disable the CCU0/CCU1 interrupt. */
static void Gpt_lGtmIrqModify (
                                const Gpt_ChannelConfigType *GptChannelPtr,
                                const uint8 InterruptFlag
                              );
#endif
/* End of #if ((GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) || \
                                  (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) ) */

#if (GPT_TIME_REMAINING_API == STD_ON)
/* API returns the time remaining for a GPT channel to complete timeout. */
static uint32 Gpt_lGtmGetTimeRemaining
                                  (const Gpt_ChannelConfigType *GptChannelPtr);
#endif
/* End of #if (GPT_TIME_REMAINING_API == STD_ON) */

#if (GPT_TIME_ELAPSED_API == STD_ON)
/* API returns the time elapsed for a GPT channel. */
static uint32 Gpt_lGtmGetTimeElapsed
                                  (const Gpt_ChannelConfigType *GptChannelPtr);
#endif
/* End of #if (GPT_TIME_ELAPSED_API == STD_ON) */
#endif
/* End of #if (GPT_TOM_USED == STD_ON) || (GPT_ATOM_USED == STD_ON) */

#if ((GPT_TIME_ELAPSED_API == STD_ON) || (GPT_TIME_REMAINING_API == STD_ON))
/* API is used to check the channel status */
LOCAL_INLINE boolean Gpt_lCheckChannelStatus
                   (const Gpt_ChannelType Channel, const uint32 CurrentCoreId);

#if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
/* API to check DET errors in Gpt_GetTimeElapsed and
Gpt_GetTimeRemaining API's */
static uint32 Gpt_lGetTimeDetCheck  (
                                      const Gpt_ChannelType Channel,
                                      const uint8 Gpt_Sid,
                                      const uint32 CoreId
                                    );
#endif
/* End of #if ((GPT_SAFETY_ENABLE == STD_ON) || \
                                          (GPT_DEV_ERROR_DETECT == STD_ON)) */
#endif
/* End of #if (GPT_TIME_REMAINING_API == STD_ON) || \
                                          (GPT_TIME_ELAPSED_API == STD_ON) */

#if ((GPT_PREDEF_TIMER_1US_16BIT_EN == STD_ON)    || \
     (GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON)    || \
     (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))
/* API to deliver the current value of the desired 1us Predef Timer. */
static uint32 Gpt_lGtmGet1UsPredefTimerValue
                                      (
                                        const Gpt_PredefTimerType PredefTimer,
                                        const uint32 CurrentCoreId
                                      );

/* API to initialize and start all 1us Predef timers, if configured. */
static void Gpt_lGtmStart1UsPredefTimer
                              (const Gpt_CoreConfigType *const CoreConfigPtr);

#if ((GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) || (GPT_DEINIT_API == STD_ON))
/* API to stop all 1us Predef timers configured from counting */
static void Gpt_lGtmStop1UsPredefTimer
                              (
                                const Gpt_CoreConfigType *const CoreConfigPtr,
                                const uint8 Gpt_Sid
                              );
#endif
/* End of #if ((GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) || \
                                                  (GPT_DEINIT_API == STD_ON)) */
#if (GPT_INITCHECK_API == STD_ON)
static Std_ReturnType Gpt_lGtmInitCheck1UsPredefTimer
                                (const Gpt_CoreConfigType *const CoreConfigPtr);
#endif
/* End of #if (GPT_INITCHECK_API == STD_ON) */
#endif
/* End of #if ((GPT_PREDEF_TIMER_1US_16BIT_EN == STD_ON) || \
              (GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON) || \
              (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON)) */

#if (GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON)
/* API delivers the current value of the 100us Predef Timer. */
static uint32 Gpt_lGtmGet100UsPredefTimerValue(const uint32 CurrentCoreId);

/* API to initialize and start the 100us Predef timer, if configured. */
static void Gpt_lGtmStart100UsPredefTimer
                              (const Gpt_CoreConfigType *const CoreConfigPtr);

#if ((GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) || (GPT_DEINIT_API == STD_ON))
/* API to stop 100us Predef timer configured from counting. */
static void Gpt_lGtmStop100UsPredefTimer
                              (
                                const Gpt_CoreConfigType *const CoreConfigPtr,
                                const uint8 Gpt_Sid
                              );
#endif
/* End of #if ((GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) || \
                                 (GPT_DEINIT_API == STD_ON)) */

#if (GPT_INITCHECK_API == STD_ON)
static Std_ReturnType Gpt_lGtmInitCheck100UsPredefTimer
                                (const Gpt_CoreConfigType *const CoreConfigPtr);
#endif
/* End of #if (GPT_INITCHECK_API == STD_ON) */
#endif
/* End of #if (GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON) */

#if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
/* Function to report Safety Error and DET. */
static void Gpt_lReportError(const uint8 Gpt_Sid, const uint8 ErrorId);
#endif

#if( (GPT_SAFETY_ENABLE == STD_ON) || (GPT_RUNTIME_ERROR_DETECT == STD_ON)||\
   ((MCAL_AR_VERSION == MCAL_AR_422) && (GPT_DEV_ERROR_DETECT == STD_ON)) )
/* This function reports the Runtime or DET Error  */
static void Gpt_lReportRuntimeDetError(const uint8 ApiId, const uint8 ErrorId);
#endif

#if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_MULTICORE_ERROR_DETECT == STD_ON))

#if (GPT_DEINIT_API == STD_ON)
LOCAL_INLINE uint32 Gpt_lMulCoreDeInitDetCheck
                                      (
                                        const uint32 CurrentCoreId,
                                        const uint32 CurrentCoreDriverState
                                      );
#endif
/* End of #if (GPT_DEINIT_API == STD_ON) */

static uint32 Gpt_lMulCoreInitDetCheck
                                      (
                                        const uint32 CurrentCoreId
                                      );

static uint32 Gpt_lMulCoreChannelDetCheck
                                      (
                                        const uint32 CurrentCoreId,
                                        const Gpt_ChannelType Channel,
                                        const uint8 Gpt_Sid
                                      );

/* API to check Multi core related DET errors in Gpt_Init API. */
LOCAL_INLINE void Gpt_lReportMulticoreError(const uint8 Gpt_Sid,
                                                      const uint8 ErrorId);
#endif
/* End of #if ((GPT_SAFETY_ENABLE == STD_ON) || \
                                      (GPT_MULTICORE_ERROR_DETECT == STD_ON)) */

#if (GPT_MAX_CORE_USED > 1U)
LOCAL_INLINE Gpt_ChannelType Gpt_lMulCoreGetChannelInfo
                    (const uint32 CurrentCoreId, const Gpt_ChannelType Channel);
#endif
/* End of #if (GPT_MAX_CORE_USED > 1U) */

LOCAL_INLINE void Gpt_lChannelsInit
    (const uint32 CurrentCoreId, const Gpt_CoreConfigType *const CoreConfigPtr);

/* API to check is the time out value passed within valid range */
LOCAL_INLINE boolean Gpt_lCheckTimeOutVaue
                                (const uint32 TimeOutVal, const uint32 MaxVal);

#if (GPT_INITCHECK_API == STD_ON)
LOCAL_INLINE Std_ReturnType Gpt_lChannelsInitCheck(const uint32 CurrentCoreId,
                                Gpt_CoreConfigType const *const CoreConfigPtr);
                                
#if (GPT_TOM_USED == STD_ON) || (GPT_ATOM_USED == STD_ON)
LOCAL_INLINE Std_ReturnType Gpt_lGtmChannelInitCheck
                            (const Gpt_ChannelConfigType *const GptChannelPtr);
#endif                            
#endif
/* End of #if (GPT_INITCHECK_API == STD_ON) */

#define GPT_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline.  */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}] */
/* Memory mapping for variables */
/* [/cover] */
#if (GPT_CONFIGURED_CORE0 == STD_ON)

#if (GPT_MAX_CHANNELS_CORE0 > 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define GPT_START_SEC_VAR_CLEARED_ASIL_B_CORE0_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"

#if (GPT_GPT12_USED == STD_ON)
/* Variable to store target time for started channels in current core */
static uint32 Gpt_ChannelTargettime_Core0[GPT_MAX_CHANNELS_CORE0];
#endif

/* Variable to store channel status for channels in current core*/
static uint32 Gpt_ChannelStatus_Core0[GPT_MAX_CHANNELS_CORE0];

#if ((GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) || \
     (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
/* Variable to store Notification and WakeUp Flag for channels per core */
static uint32 Gpt_Flag_Core0[GPT_MAX_CHANNELS_CORE0];
#endif

#define GPT_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"
#endif   /* End of #if (GPT_MAX_CHANNELS_CORE0 > 0U) */

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define GPT_START_SEC_VAR_INIT_ASIL_B_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"

/* Variable to store status private to each core */
static Gpt_ThreadSafeDataType Gpt_ThreadSafeData_Core0 =
{
  GPT_MODE_NORMAL,

  #if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
  #if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
  /* Variable to store the channel wakeup info due to which GPT woke up */
  0x0,
  #endif
  #endif  /* End of #if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) */
  #if (GPT_MAX_CHANNELS_CORE0 > 0U)
  #if (GPT_GPT12_USED == STD_ON)
  &Gpt_ChannelTargettime_Core0[0],
  #endif
  &Gpt_ChannelStatus_Core0[0],
  #if ((GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) || \
       (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
  &Gpt_Flag_Core0[0]
  #endif
  #else
  #if (GPT_GPT12_USED == STD_ON)
  NULL_PTR,
  #endif
  NULL_PTR,
  #if ((GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) || \
       (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
  NULL_PTR
  #endif
  #endif   /* End of #if (GPT_MAX_CHANNELS_CORE0 > 0U) */
};

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define GPT_STOP_SEC_VAR_INIT_ASIL_B_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"
#endif    /* End of #if (GPT_CONFIGURED_CORE0 == STD_ON) */

#if (GPT_CONFIGURED_CORE1 == STD_ON)

#if (GPT_MAX_CHANNELS_CORE1 > 0U)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define GPT_START_SEC_VAR_CLEARED_ASIL_B_CORE1_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"

#if (GPT_GPT12_USED == STD_ON)
/* Variable to store target time for started channels in current core */
static uint32 Gpt_ChannelTargettime_Core1[GPT_MAX_CHANNELS_CORE1];
#endif

/* Variable to store channel status for channels in current core*/
static uint32 Gpt_ChannelStatus_Core1[GPT_MAX_CHANNELS_CORE1];

#if ((GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) || \
     (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
/* Variable to store Notification and WakeUp Flag for channels per core */
static uint32 Gpt_Flag_Core1[GPT_MAX_CHANNELS_CORE1];
#endif

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define GPT_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"
#endif   /* End of #if (GPT_MAX_CHANNELS_CORE1 > 0U) */

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define GPT_START_SEC_VAR_INIT_ASIL_B_CORE1_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"
/* Variable to store status private to each core */
static Gpt_ThreadSafeDataType Gpt_ThreadSafeData_Core1 =
{
  GPT_MODE_NORMAL,

  #if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
  #if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
  /* Variable to store the channel wakeup info due to which GPT woke up */
  0x0,
  #endif
  #endif    /* End of #if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) */

  #if (GPT_MAX_CHANNELS_CORE1 > 0U)
  #if (GPT_GPT12_USED == STD_ON)
  &Gpt_ChannelTargettime_Core1[0],
  #endif
  &Gpt_ChannelStatus_Core1[0],
  #if ((GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) || \
       (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
  &Gpt_Flag_Core1[0]
  #endif
  #else
  #if (GPT_GPT12_USED == STD_ON)
  NULL_PTR,
  #endif
  NULL_PTR,
  #if ((GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) || \
       (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
  NULL_PTR
  #endif
  #endif    /* End of #if (GPT_MAX_CHANNELS_CORE1 > 0U) */
};

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define GPT_STOP_SEC_VAR_INIT_ASIL_B_CORE1_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"
#endif    /* End of #if (GPT_CONFIGURED_CORE1 == STD_ON) */

#if (GPT_CONFIGURED_CORE2 == STD_ON)

#if (GPT_MAX_CHANNELS_CORE2 > 0U)

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define GPT_START_SEC_VAR_CLEARED_ASIL_B_CORE2_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"

#if (GPT_GPT12_USED == STD_ON)
/* Variable to store target time for started channels in current core */
static uint32 Gpt_ChannelTargettime_Core2[GPT_MAX_CHANNELS_CORE2];
#endif

/* Variable to store channel status for channels in current core*/
static uint32 Gpt_ChannelStatus_Core2[GPT_MAX_CHANNELS_CORE2];

#if ((GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) || \
     (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
/* Variable to store Notification and WakeUp Flag for channels per core */
static uint32 Gpt_Flag_Core2[GPT_MAX_CHANNELS_CORE2];
#endif

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define GPT_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"
#endif    /* End of #if (GPT_MAX_CHANNELS_CORE2 > 0U)*/

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define GPT_START_SEC_VAR_INIT_ASIL_B_CORE2_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"
/* Variable to store status private to each core */
static Gpt_ThreadSafeDataType Gpt_ThreadSafeData_Core2 =
{
  GPT_MODE_NORMAL,

  #if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
  #if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
  /* Variable to store the channel wakeup info due to which GPT woke up */
  0x0,
  #endif
  #endif   /* End of #if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) */

  #if (GPT_MAX_CHANNELS_CORE2 > 0U)
  #if (GPT_GPT12_USED == STD_ON)
  &Gpt_ChannelTargettime_Core2[0],
  #endif
  &Gpt_ChannelStatus_Core2[0],
  #if ((GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) || \
       (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
  &Gpt_Flag_Core2[0]
  #endif
  #else
  #if (GPT_GPT12_USED == STD_ON)
  NULL_PTR,
  #endif
  NULL_PTR,
  #if ((GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) || \
       (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
  NULL_PTR
  #endif
  #endif   /* End of #if (GPT_MAX_CHANNELS_CORE2 > 0U) */
};

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define GPT_STOP_SEC_VAR_INIT_ASIL_B_CORE2_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"
#endif    /* End of #if (GPT_CONFIGURED_CORE2 == STD_ON) */

#if (GPT_CONFIGURED_CORE3 == STD_ON)

#if (GPT_MAX_CHANNELS_CORE3 > 0U)

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define GPT_START_SEC_VAR_CLEARED_ASIL_B_CORE3_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"

#if (GPT_GPT12_USED == STD_ON)
/* Variable to store target time for started channels in current core */
static uint32 Gpt_ChannelTargettime_Core3[GPT_MAX_CHANNELS_CORE3];
#endif

/* Variable to store channel status for channels in current core*/
static uint32 Gpt_ChannelStatus_Core3[GPT_MAX_CHANNELS_CORE3];

#if ((GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) || \
     (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
/* Variable to store Notification and WakeUp Flag for channels per core */
static uint32 Gpt_Flag_Core3[GPT_MAX_CHANNELS_CORE3];
#endif

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define GPT_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"
#endif   /* End of #if (GPT_MAX_CHANNELS_CORE3 > 0U) */

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define GPT_START_SEC_VAR_INIT_ASIL_B_CORE3_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"

/* Variable to store status private to each core */
static Gpt_ThreadSafeDataType Gpt_ThreadSafeData_Core3 =
{
  GPT_MODE_NORMAL,

  #if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
  #if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
  /* Variable to store the channel wakeup info due to which GPT woke up */
  0x0,
  #endif
  #endif   /* End of #if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) */

  #if (GPT_MAX_CHANNELS_CORE3 > 0U)
  #if (GPT_GPT12_USED == STD_ON)
  &Gpt_ChannelTargettime_Core3[0],
  #endif
  &Gpt_ChannelStatus_Core3[0],
  #if ((GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) || \
       (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
  &Gpt_Flag_Core3[0]
  #endif
  #else
  #if (GPT_GPT12_USED == STD_ON)
  NULL_PTR,
  #endif
  NULL_PTR,
  #if ((GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) || \
       (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
  NULL_PTR
  #endif
  #endif   /* End of #if (GPT_MAX_CHANNELS_CORE3 > 0U) */
};

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define GPT_STOP_SEC_VAR_INIT_ASIL_B_CORE3_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"
#endif   /* End of #if (GPT_CONFIGURED_CORE3 == STD_ON) */

#if (GPT_CONFIGURED_CORE4 == STD_ON)

#if (GPT_MAX_CHANNELS_CORE4 > 0U)

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define GPT_START_SEC_VAR_CLEARED_ASIL_B_CORE4_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"

#if (GPT_GPT12_USED == STD_ON)
/* Variable to store target time for started channels in current core */
static uint32 Gpt_ChannelTargettime_Core4[GPT_MAX_CHANNELS_CORE4];
#endif

/* Variable to store channel status for channels in current core*/
static uint32 Gpt_ChannelStatus_Core4[GPT_MAX_CHANNELS_CORE4];

#if ((GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) || \
     (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
/* Variable to store Notification and WakeUp Flag for channels per core */
static uint32 Gpt_Flag_Core4[GPT_MAX_CHANNELS_CORE4];
#endif

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define GPT_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"
#endif   /* End of #if (GPT_MAX_CHANNELS_CORE4 > 0U) */

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define GPT_START_SEC_VAR_INIT_ASIL_B_CORE4_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"
/* Variable to store status private to each core */
static Gpt_ThreadSafeDataType Gpt_ThreadSafeData_Core4 =
{
  GPT_MODE_NORMAL,

  #if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
  #if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
  /* Variable to store the channel wakeup info due to which GPT woke up */
  0x0,
  #endif
  #endif   /* End of #if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) */

  #if (GPT_MAX_CHANNELS_CORE4 > 0U)
  #if (GPT_GPT12_USED == STD_ON)
  &Gpt_ChannelTargettime_Core4[0],
  #endif
  &Gpt_ChannelStatus_Core4[0],
  #if ((GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) || \
       (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
  &Gpt_Flag_Core4[0]
  #endif
  #else
  #if (GPT_GPT12_USED == STD_ON)
  NULL_PTR,
  #endif
  NULL_PTR,
  #if ((GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) || \
       (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
  NULL_PTR
  #endif
  #endif   /* End of #if (GPT_MAX_CHANNELS_CORE4 > 0U) */
};

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define GPT_STOP_SEC_VAR_INIT_ASIL_B_CORE4_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"
#endif   /* End of #if (GPT_CONFIGURED_CORE4 == STD_ON) */

#if (GPT_CONFIGURED_CORE5 == STD_ON)

#if (GPT_MAX_CHANNELS_CORE5 > 0U)

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define GPT_START_SEC_VAR_CLEARED_ASIL_B_CORE5_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"

#if (GPT_GPT12_USED == STD_ON)
/* Variable to store target time for started channels in current core */
static uint32 Gpt_ChannelTargettime_Core5[GPT_MAX_CHANNELS_CORE5];
#endif

/* Variable to store channel status for channels in current core*/
static uint32 Gpt_ChannelStatus_Core5[GPT_MAX_CHANNELS_CORE5];

#if ((GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) || \
(GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
/* Variable to store Notification and WakeUp Flag for channels per core */
static uint32 Gpt_Flag_Core5[GPT_MAX_CHANNELS_CORE5];
#endif

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define GPT_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"
#endif   /* End of #if (GPT_MAX_CHANNELS_CORE5 > 0U) */

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define GPT_START_SEC_VAR_INIT_ASIL_B_CORE5_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"

/* Variable to store status private to each core */
static Gpt_ThreadSafeDataType Gpt_ThreadSafeData_Core5 =
{
  GPT_MODE_NORMAL,

  #if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
  #if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
  /* Variable to store the channel wakeup info due to which GPT woke up */
  0x0,
  #endif
  #endif   /* End of #if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) */

  #if (GPT_MAX_CHANNELS_CORE5 > 0U)
  #if (GPT_GPT12_USED == STD_ON)
  &Gpt_ChannelTargettime_Core5[0],
  #endif
  &Gpt_ChannelStatus_Core5[0],
  #if ((GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) || \
       (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
  &Gpt_Flag_Core5[0]
  #endif
  #else
  #if (GPT_GPT12_USED == STD_ON)
  NULL_PTR,
  #endif
  NULL_PTR,
  #if ((GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) || \
       (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
  NULL_PTR
  #endif
  #endif   /* End of #if (GPT_MAX_CHANNELS_CORE5 > 0U) */
};

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define GPT_STOP_SEC_VAR_INIT_ASIL_B_CORE5_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"
#endif   /* End of #if (GPT_CONFIGURED_CORE5 == STD_ON)*/

/* Start variable section (LMU) for unspecified */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define GPT_START_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"
/* Constant Data */
static Gpt_ThreadSafeDataType *const Gpt_ThreadSafeData[6] =
{
  #if (GPT_CONFIGURED_CORE0 == STD_ON)
  &Gpt_ThreadSafeData_Core0,
  #else
  NULL_PTR,
  #endif
  #if (GPT_CONFIGURED_CORE1 == STD_ON)
  &Gpt_ThreadSafeData_Core1,
  #else
  NULL_PTR,
  #endif
  #if (GPT_CONFIGURED_CORE2 == STD_ON)
  &Gpt_ThreadSafeData_Core2,
  #else
  NULL_PTR,
  #endif
  #if (GPT_CONFIGURED_CORE3 == STD_ON)
  &Gpt_ThreadSafeData_Core3,
  #else
  NULL_PTR,
  #endif
  #if (GPT_CONFIGURED_CORE4 == STD_ON)
  &Gpt_ThreadSafeData_Core4,
  #else
  NULL_PTR,
  #endif
  #if (GPT_CONFIGURED_CORE5 == STD_ON)
  &Gpt_ThreadSafeData_Core5,
  #else
  NULL_PTR,
  #endif
};

/* Stop variable section (LMU) for unspecified */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define GPT_STOP_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"

/* 16 bit variable LMU SECTION initialized with values after every reset */
/************************ Start 16 bit variable LMU SECTION *******************/
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define GPT_START_SEC_VAR_INIT_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"
/* This variable stores the status information of the GPT Driver that is shared
 * across all cores.
 *
 * Bit31      Bit17    Bit15    Bit12                              Bit2   Bit0
 *  ----------------------------------------------------------------------
 * | reserved | 100us  | 1us    | Core | Core | Core | Core | Core | Core |
 * |          | Predef | Predef |   5  |   4  |   3  |   2  |   1  |   0  |
 *  ----------------------------------------------------------------------
*/

/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is updated using atomic
instructions of tricore in multiple functions, hence it cannot be defined at
block scope.*/

static volatile uint32 Gpt_DriverStatus = GPT_DRIVER_UNINITIALIZED;

/* Stop 16 bit variable section */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define GPT_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"

/************************ Start 32 bit variable section ***********************/
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define GPT_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"

/* Store the GPT driver configuration pointer */
static const Gpt_ConfigType *Gpt_ConfigPtr;

/* Stop 32 bit variable section */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define GPT_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"
/******************************************************************************/

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
/*************************** Start GPT code section ***************************/
#define GPT_START_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"

#if (GPT_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={1ED7FC2B-8DF2-4232-974A-55AD0746EA96}]   **
**                                                                            **
** Syntax         : void Gpt_GetVersionInfo                                   **
**                              (Std_VersionInfoType * const VersionInfoPtr)  **
**                                                                            **
** Description    : This service returns the version information              **
**                  of this module.The version information includes :         **
**                  - Module Id                                               **
**                  - Vendor Id                                               **
**                  - Vendor specific version numbers                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : 0x00                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : None                                                      **
**                                                                            **
** Parameters(out): versioninfo (Pointer to where to store the version        **
**                               information of this module)                  **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
void Gpt_GetVersionInfo(Std_VersionInfoType* const VersionInfoPtr)
{
  /* Check if the passed parameter is a NULL_PTR */
  /* [cover parentID={D2FD2C51-C3A2-41c3-B0BC-BD316DFD62F5}]
  Safety enable or DET is On
  [/cover] */
  #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
  /* [cover parentID={061C3818-3BA9-4ed6-9C27-5196A082A606}]
  Is the passed pointer valid?
  [/cover] */
  if ((VersionInfoPtr) == NULL_PTR)
  {
    /* Report DET with GPT_E_PARAM_POINTER */
    Gpt_lReportError(GPT_SID_GETVERSIONINFO, GPT_E_PARAM_POINTER);
  }
  /* [/cover] */
  /* [/cover] */
  else
  #endif
  {
    /* Get GPT Vendor ID */
    ((Std_VersionInfoType*)(VersionInfoPtr))->vendorID = GPT_VENDOR_ID;

    /* Get GPT Module ID */
    ((Std_VersionInfoType*)(VersionInfoPtr))->moduleID = GPT_MODULE_ID;

    /* Get GPT module Software major version */
    ((Std_VersionInfoType*)(VersionInfoPtr))->sw_major_version =
                                       (uint8)GPT_SW_MAJOR_VERSION;

    /* Get GPT module Software minor version */
    ((Std_VersionInfoType*)(VersionInfoPtr))->sw_minor_version =
                                       (uint8)GPT_SW_MINOR_VERSION;

    /* Get GPT module Software patch version */
    ((Std_VersionInfoType*)(VersionInfoPtr))->sw_patch_version =
                                       (uint8)GPT_SW_PATCH_VERSION;
  }
} /* End of Gpt_GetVersionInfo() */

/******************************************************************************/
#endif
/* End of #if (GPT_VERSION_INFO_API == STD_ON) */

/*******************************************************************************
** Traceability   : [cover parentID={151D5BB1-0296-43e1-99B3-521C8F2B5F59}]   **
**                                                                            **
** Syntax         : void Gpt_Init (                                           **
**                             const Gpt_ConfigType *const ConfigPtr)         **
**                                )                                           **
**                                                                            **
** Description    : This API initializes the hardware timer module according  **
**                  to a configuration set referenced by ConfigPtr.           **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     :  0x01                                                     **
**                                                                            **
** Sync/Async     :  Synchronous                                              **
**                                                                            **
** Reentrancy     :  Non Reentrant                                            **
**                                                                            **
** Parameters(in) :  ConfigPtr - Pointer to the configuration structure       **
**                                                                            **
** Parameters(out):  None                                                     **
**                                                                            **
** Return value   :  None                                                     **
**                                                                            **
*******************************************************************************/
/* [cover parentID={070C15E2-9194-44ff-9DB8-0FE97BDF9333}] */
/*  [/cover] */
/* [cover parentID={4141A6C4-464E-4050-A147-DE34112CA916}] */
/*  [/cover] */
void Gpt_Init(const Gpt_ConfigType *const ConfigPtr)
{
  const Gpt_CoreConfigType  *LocalCoreConfigPtr;
  uint32                    CurrentCoreId;

  #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
  uint32 IDetVal;
  #endif
  /* End of #if ((GPT_SAFETY_ENABLE == STD_ON) || \
                                            (GPT_DEV_ERROR_DETECT == STD_ON)) */

  /* Get the current core ID */
  CurrentCoreId = GPT_GET_COREID();

  /* [cover parentID={799600DE-F5A4-4f6f-9F48-6974F984E562}]
  Safety enable or DET is On
  [/cover] */
  #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))

  /* [cover parentID={801C4DDB-E0A7-4c58-A605-42FC9A3F8400}]
  Check for DETs
  [/cover] */
  IDetVal = Gpt_lInitDetCheck(ConfigPtr, CurrentCoreId);

  /* [cover parentID={40C35107-9FA7-4fb9-9FC6-1F8A4A6C79B0}]
  Are there any errors?
  [/cover] */
  if (GPT_E_DET_ERR != IDetVal)
  #endif
  {

    /* [cover parentID={D2E8B1A5-0E15-46b8-BF1D-03FAB3E8E4C1}]
    Is current core the master core?
    [/cover] */
    if (CurrentCoreId == MCAL_MASTER_COREID)
    {
      /* [cover parentID={623B198B-D378-41cd-8E9D-357CC3220151}]
      Save the ConfigPtr locally only from Master Core
      [/cover] */
      Gpt_ConfigPtr = ConfigPtr;
    }

    /* Get the pointer to current core configuration */
    LocalCoreConfigPtr = GPT_GET_CORECONFIGPTR(CurrentCoreId);
    /* [cover parentID={60265C27-E2FA-435b-A9C2-6693867600C1}]
       Initialize only the channels allocated to the current core
       [/cover] */
    /* Initialize the channels allocated to the core */
    Gpt_lChannelsInit(CurrentCoreId, LocalCoreConfigPtr);

    /* Start Predef Timer(s) only from master core */
    /* [cover parentID={C109B43D-FBA0-4468-9512-660BE6B8A5BA}]
    Is current core the master core?
    [/cover] */
    if (CurrentCoreId == MCAL_MASTER_COREID)
    {
      /* [cover parentID={5EC5A566-6FC4-40a8-B1F7-46203B767A81}]
      GPT predefined timer 1us ON
      [/cover] */
      #if ((GPT_PREDEF_TIMER_1US_16BIT_EN == STD_ON)    || \
          (GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON)    || \
          (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))
      /* [cover parentID={C0BF6373-4D3E-40c8-867E-91F5BB8B771D}]
      Start the 1us predefined timer
      [/cover] */
      Gpt_lGtmStart1UsPredefTimer(LocalCoreConfigPtr);
      #endif
      /* [cover parentID={25342428-410B-45fa-98F2-69481E8E0FDC}]
         GPT predefined timer 100us ON
         [/cover] */

      #if (GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON)
      /* [cover parentID={BCDBEFE8-6546-4e38-B307-BF149C1B260F}]
      Start the 100us predefined timer
      [/cover] */
      Gpt_lGtmStart100UsPredefTimer(LocalCoreConfigPtr);
      #endif
    }

    /* [cover parentID={8F29730D-8A8A-465a-ABF3-81368C6E7861}]
    Set the driver status to "Initialized" for corresponding core
    [/cover] */


    Mcal_SetBitAtomic( 
                       &Gpt_DriverStatus, 
                       GPT_CORE_BITPOS(CurrentCoreId), 
                       GPT_CORE_STATUS_LEN, 
                       GPT_DRIVER_INITIALIZED 
                     );


    /* [cover parentID={C44A38F7-7508-4a9b-A325-3CEE584F326F}]
    Set the Mode to "Normal" for corresponding core
    [/cover] */
    Gpt_ThreadSafeData[CurrentCoreId]->Gpt_DriverMode = GPT_MODE_NORMAL;

  } /* End of if (GPT_E_DET_ERR != IDetVal )*/

  return;
}/* End of Gpt_Init */
/******************************************************************************/

#if (GPT_DEINIT_API == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={FB77C8F8-E4DE-4a3d-BDE6-CFF09F7869F1}]   **
**                                                                            **
** Syntax         : void Gpt_DeInit(void)                                     **
**                                                                            **
** Description    : This API de-initializes all the configured hardware       **
**                  timer channels to their power on reset state.             **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     :  0x02                                                     **
**                                                                            **
** Sync/Async     :  Synchronous                                              **
**                                                                            **
** Reentrancy     :  Non Reentrant                                            **
**                                                                            **
** Parameters(in) :  None                                                     **
**                                                                            **
** Parameters(out):  None                                                     **
**                                                                            **
** Return value   :  None                                                     **
**                                                                            **
*******************************************************************************/
/* [cover parentID={070C15E2-9194-44ff-9DB8-0FE97BDF9333}] */
/*  [/cover] */
/* [cover parentID={4141A6C4-464E-4050-A147-DE34112CA916}] */
/*  [/cover] */
void Gpt_DeInit(void)
{
  const Gpt_ChannelConfigType   *LocalChannelConfigPtr;
  const Gpt_CoreConfigType      *LocalCoreConfigPtr;
  uint32 CurrentCoreId;

  #if((GPT_SAFETY_ENABLE == STD_ON) || (GPT_RUNTIME_ERROR_DETECT == STD_ON)||\
     (GPT_DEV_ERROR_DETECT == STD_ON))
  uint32 IDetVal;
  #endif

  uint8  Counter;

  /* Get the current core ID */
  CurrentCoreId = GPT_GET_COREID();

  /* [cover parentID={65DDCC1C-C512-4dcd-99CC-5545FBF17F74}]
  Safety enabled or DET is On
  [/cover] */
  #if((GPT_SAFETY_ENABLE == STD_ON) || (GPT_RUNTIME_ERROR_DETECT == STD_ON)||\
     (GPT_DEV_ERROR_DETECT == STD_ON)) 
  IDetVal = Gpt_lDeInitDetCheck(CurrentCoreId);

  /* [cover parentID={B8A22910-48CF-4778-B590-38BE5376ED6E}]
  Are there any errors?
  [/cover] */
  if (GPT_E_DET_ERR != IDetVal)
  #endif
  /* End of #if ((GPT_SAFETY_ENABLE == STD_ON) || \
                                          (GPT_DEV_ERROR_DETECT == STD_ON)) */
  {
    /* [cover parentID={AC8772A6-2482-44f4-94FF-0C5B4721A12C}]
    Set the core specific driver status to denote "Uninitialize requested"
    [/cover] */

    Mcal_SetBitAtomic( 
                       &Gpt_DriverStatus, 
                       GPT_CORE_BITPOS(CurrentCoreId), 
                       GPT_CORE_STATUS_LEN, 
                       GPT_DRIVER_UNINITIALIZ_REQ 
                     );


    /* Get the pointer to current core configuration */
    LocalCoreConfigPtr = GPT_GET_CORECONFIGPTR(CurrentCoreId);

    /* Get the pointer to the channel configuration */
    LocalChannelConfigPtr = LocalCoreConfigPtr->ChannelConfigPtr;

    /* [cover parentID={A88EB11F-7D20-4efc-A5C2-4D9BD289CD08}]
    Reset channels mapped to the current core
    [/cover] */
    for( Counter = (uint8)0x0U ;
       (Counter < LocalCoreConfigPtr->Gpt_MaxNormalChannels) ; Counter++ )
    {
      /* [cover parentID={6B94C198-3C7F-40cd-96FD-C7D8494A87F9}]
      Reset Channel
      [/cover] */

      /* [cover parentID={05BC71F6-B139-471f-B25A-039DCEFDAB8A}]
        Wakeup enabled or Notification enabled
        [/cover] */
      #if ((GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) ||            \
      (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
      Gpt_ThreadSafeData[CurrentCoreId]->Gpt_FlagPtr[Counter] =          
                                                    (uint8)0x0U;
      #endif
      /* End of #if ((GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) ||  \
                      (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)) */

      /* [cover parentID={ADCF0B4D-18AD-41f1-9A1D-B482A153DC66}]
      Reset the Channel
      [/cover] */
      /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic used due to
      PBConfigStructure and is within allowed range.*/
      Gpt_lResetChannel(LocalChannelConfigPtr + Counter);

      /* [cover parentID={E69D3CF9-7592-4988-B646-AFD7F5174F77}]
       Set the corresponding channel status to "UnInitialized"
       [/cover] */
      /* De-initialize Channel Status Flags */
      Gpt_ThreadSafeData[CurrentCoreId]->Gpt_ChannelStatusPtr[Counter] = 
          GPT_CHANNEL_UNINITIALIZED;
    } /* End of for ( Counter = (uint8)0x0U;
                                    Counter < GPT_MAX_CHANNELS; Counter++ ) */

    /* Stop all enabled GPT Predef Timer(s) only from master core */
    /*
    Is GPT 100us predefined timer is already started
    (implies current core is master core)?
     */
    /* [cover parentID={148BB408-17B1-4afb-852D-AE59022EF9C0}]
    Is GPT 1us predefined timer is already started
    (implies current core is master core)?
    [/cover] */
    if (CurrentCoreId == MCAL_MASTER_COREID)
    {
      /* [cover parentID={5FBC5859-55EF-48e2-BABC-130AF90CACCF}]
      GPT predefined timer 100us ON
      [/cover] */
      /* [cover parentID={643EDAB2-B82F-4972-B32D-8A7AF3E0D8E1}]
      GPT predefined timer 1us ON
      [/cover] */
      #if ((GPT_PREDEF_TIMER_1US_16BIT_EN == STD_ON) || \
          (GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON)  || \
          (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))
      /* [cover parentID={6684586D-518D-46b3-A78B-9FC98157BA6B}]
      Stop all enabled GPT Predef 1us Timers
      [/cover] */
      Gpt_lGtmStop1UsPredefTimer(LocalCoreConfigPtr, GPT_SID_DEINIT);
      #endif

      /* [cover parentID={5FBC5859-55EF-48e2-BABC-130AF90CACCF}]
        GPT predefined timer 100us ON
        [/cover] */
      #if (GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON)
      /* [cover parentID={E8194989-D8B5-46e7-BA54-ADE71A19D714}]
      Stop all enabled GPT Predef 100us timers
      [/cover] */
      Gpt_lGtmStop100UsPredefTimer(LocalCoreConfigPtr, GPT_SID_DEINIT);
      #endif
    }

    /* [cover parentID={75F84485-9CA0-4b46-A0BC-99BBA6B600E6}]
    Clear core specific driver status to denote "Uninitialized"
    [/cover] */

    Mcal_SetBitAtomic( 
                       &Gpt_DriverStatus, 
                       GPT_CORE_BITPOS(CurrentCoreId), 
                       0x2, 
                       GPT_DRIVER_UNINITIALIZED 
                     );


  } /* End of if (GPT_E_DET_ERR != IDetVal )*/

  return;
}/* End of Gpt_DeInit */
/******************************************************************************/
#endif
/* End of #if (GPT_DEINIT_API == STD_ON) */

/*******************************************************************************
** Traceability   : [cover parentID={C234053A-CA3E-4d3c-949C-F803E1FDD135}]   **
**                                                                            **
** Syntax         : void Gpt_StartTimer (                                     **
**                            const Gpt_ChannelType Channel,                  **
**                            const Gpt_ValueType Value                       **
**                                      )                                     **
**                                                                            **
** Description    : This API starts the selected timer channel with a         **
**                  defined timeout period. After this timeout period, a      **
**                  notification can be invoked (if enabled).                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : 0x05                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant (but not for the same timer channel)            **
**                                                                            **
** Parameters(in) : Channel : Numeric identifier of the GPT channel           **
**                  Value   : Timeout period (in number of ticks) after a     **
**                            notification shall occur.                       **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
/* [cover parentID={070C15E2-9194-44ff-9DB8-0FE97BDF9333}] */
/*  [/cover] */
void Gpt_StartTimer(const Gpt_ChannelType Channel, const Gpt_ValueType Value )
{
  #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
  uint32 IDetVal = GPT_E_DET_NO_ERR;
  #endif
  uint32 CurrentCoreId;
  Gpt_ChannelType LocalChannel;

  /* Get the current core ID */
  CurrentCoreId = GPT_GET_COREID();

  /* [cover parentID={A8DC2F29-BA1D-4579-8B32-196C6B1A462D}]
  Safety enable or DET is On
  [/cover] */
  #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
    
  /* Check if driver was initialized from the current core */
  /* [cover parentID={BB85F367-69D4-4fda-A4B6-A2D6AA2A4759}]
  Is driver initialised from the current core?
  [/cover] */
  if (GPT_DRIVER_INITIALIZED != 
        Mcal_GetBitAtomic(Gpt_DriverStatus, GPT_CORE_BITPOS(CurrentCoreId), 
                                                         GPT_CORE_STATUS_LEN))
  {
    /* [cover parentID={6F4B3303-F585-4b4d-8F40-59459A097CBE}]
    Report DET, set error flag
    [/cover] */
    Gpt_lReportError(GPT_SID_STARTTIMER, GPT_E_UNINIT);

    IDetVal = GPT_E_DET_ERR; /* Set Error Flag */
  }

  /* [cover parentID={4B7C8A36-7AB1-4037-96DC-A51012BD6CE2}]
  Safety enabled
  [/cover] */
  #if (GPT_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={191E802B-867D-463b-88A2-A51BCB327A3C}]
  Is in wrong mode in current core?
  [/cover] */
  /* Check if the driver is in wrong mode in current core */
  else if (GPT_MODE_SLEEP == 
           Gpt_ThreadSafeData[CurrentCoreId]->Gpt_DriverMode )
  {
    /* [cover parentID={6A5AE8F1-0FEA-4fd9-89F4-36CD79834F69}]
    Report to Safety Error
    [/cover] */
    Mcal_ReportSafetyError(GPT_MODULE_ID, GPT_INSTANCE_ID, 
                           GPT_SID_STARTTIMER, GPT_E_INVALID_START);

    IDetVal = GPT_E_DET_ERR; /* Set Error Flag */
  }
  #endif
  /* [cover parentID={A53516E1-CD54-4b27-A90D-8FD3A50C47BB}]
  Is 'Channel' within valid range?
  [/cover] */
  /* Check is 'Channel' within valid range */
  else if (Channel >= GPT_MAX_CHANNELS)
  {
    /* [cover parentID={70639801-1858-4091-9290-A7B567178673}]
    Report Det, set error flag
    [/cover] */
    Gpt_lReportError(GPT_SID_STARTTIMER, GPT_E_PARAM_CHANNEL);

    IDetVal = GPT_E_DET_ERR; /* Set Error Flag */
  }
  else
  {
    
    #if ((GPT_SAFETY_ENABLE == STD_ON) || \
         (GPT_MULTICORE_ERROR_DETECT == STD_ON))
    /* [cover parentID={28F7E1EF-3937-4ab6-8D30-981FCD50B8E2}]
    SAFETY ENABLED (OR) Multi Core Error Detect is ON
    [/cover] */
    /* Check is channel present in current core */
    /* [cover parentID={13414F18-4361-4721-A38A-02E22DD12701}]
    Check the channel valid in context to the current core
    [/cover] */
    IDetVal = 
      Gpt_lMulCoreChannelDetCheck(CurrentCoreId, Channel, GPT_SID_STARTTIMER);
    #endif
  }
  /* [cover parentID={C33CDC34-C5A6-46da-A5AB-D89B4C4B07DB}]
  Are there any errors?
  [/cover] */
  if (IDetVal != GPT_E_DET_ERR)
  #endif
  /* End of #if ((GPT_SAFETY_ENABLE == STD_ON) || \
                                            (GPT_DEV_ERROR_DETECT == STD_ON)) */
  {
    /* [cover parentID={5D041BD6-2737-4828-8962-9893FB69A80A}]
    Is Gpt configured in more than one core?
    [/cover] */
    #if (GPT_MAX_CORE_USED > 1U)
    /* [cover parentID={193C867F-3632-47a7-BF76-4020D66BEA1C}]
    Get the relative index of the channel in context to the core
    [/cover] */
    LocalChannel = Gpt_lMulCoreGetChannelInfo(CurrentCoreId, Channel);
    #else
    LocalChannel = Channel;
    #endif

    /* [cover parentID={EECA098D-BED3-4f56-AFD0-C6A80389D664}]
    Safety enable or DET is On
    [/cover] */
    #if( (GPT_SAFETY_ENABLE == STD_ON) || (GPT_RUNTIME_ERROR_DETECT == STD_ON)||\
       ((MCAL_AR_VERSION == MCAL_AR_422) && (GPT_DEV_ERROR_DETECT == STD_ON)) )
    /* [cover parentID={D75EECCA-C368-4702-B793-B4BAF88BF292}]
    Is channel running?
    [/cover] */
    if (Gpt_ThreadSafeData[CurrentCoreId]->  
        Gpt_ChannelStatusPtr[LocalChannel] == GPT_CHANNEL_RUNNING)
    {
      /* [cover parentID={47F8D812-981D-405c-99B1-F6F0D63E3279}]
      Report DET
      [/cover] */
      Gpt_lReportRuntimeDetError(GPT_SID_STARTTIMER, GPT_E_BUSY);
    }
    else
    #endif
    {
      /* [cover parentID={7845F66A-117F-491f-869B-7D037CC59D58}]
      GPT12  used
      [/cover] */
      #if (GPT_GPT12_USED == STD_ON)
      /* [cover parentID={BC17FEDC-CE22-4cb1-B7A1-44956DED9F3A}]
      Is channel configured for GPT12
      [/cover] */
      if(GPT_GET_CORECONFIGPTR(CurrentCoreId)->ChannelConfigPtr[LocalChannel].
           GptGpt12TimerInfo != NULL_PTR)
      {
        /* [cover parentID={E6DD9872-703C-4b65-9E74-DA28BB0AE886}]
        Start the required timer channel
        [/cover] */
        Gpt_lGpt12StartTimer(LocalChannel, Value, CurrentCoreId);        
      }
      else
      #endif
      {
        
        #if (GPT_TOM_USED == STD_ON) || (GPT_ATOM_USED == STD_ON)
        /* [cover parentID={E3E79CC6-83C7-4659-9A40-220D83DC0D93}]
        GTM used
        [/cover] */
        /* [cover parentID={A2F21CDA-6248-424c-87D3-9D1C728BB54A}]
        Start the required timer channel
        [/cover] */
        Gpt_lGtmStartTimer(LocalChannel, Value, CurrentCoreId);
        #endif
      }
      
    }
  }  
  return;
}/* End of Gpt_StartTimer */
/******************************************************************************/

/*******************************************************************************
** Traceability   : [cover parentID={AEC07CA4-9B96-4a33-8719-DBAA3AC165C0}]   **
**                                                                            **
** Syntax         : void Gpt_StopTimer(const Gpt_ChannelType Channel)         **
**                                                                            **
** Description    : This API stops the selected timer channel.                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     :  0x06                                                     **
**                                                                            **
** Sync/Async     :  Synchronous                                              **
**                                                                            **
** Reentrancy     :  Reentrant (but not for the same timer channel)           **
**                                                                            **
** Parameters(in) :  Channel: Numeric identifier of the GPT channel           **
**                                                                            **
** Parameters(out):  None                                                     **
**                                                                            **
** Return value   :  None                                                     **
**                                                                            **
*******************************************************************************/
/* [cover parentID={070C15E2-9194-44ff-9DB8-0FE97BDF9333}] */
/*  [/cover] */
void Gpt_StopTimer (const Gpt_ChannelType Channel)
{
  #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
  uint32 IDetVal = GPT_E_DET_NO_ERR;
  #endif

  uint32          CurrentCoreId;
  Gpt_ChannelType LocalChannel;

  /* Get the current core ID */
  CurrentCoreId = GPT_GET_COREID();

  /* [cover parentID={7DEBCE97-5C0A-4264-8031-20EBD26943EC}]
  Safety enable or DET is On
  [/cover] */
  #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
  
  /* [cover parentID={BB2FA66F-A7D5-47eb-A858-3E2423ACD853}]
  Is driver initialised from the current core?
  [/cover] */
  if (GPT_DRIVER_INITIALIZED != 
          Mcal_GetBitAtomic(Gpt_DriverStatus, GPT_CORE_BITPOS(CurrentCoreId), 
                                                           GPT_CORE_STATUS_LEN))
  {
    /* [cover parentID={0E0B9E97-3FD6-4e1b-AC56-097C89C980F0}]
    Report DET and set error flag
    [/cover] */
    Gpt_lReportError(GPT_SID_STOPTIMER, GPT_E_UNINIT);

    IDetVal = GPT_E_DET_ERR; /* Set IDetVal */
  }
  /* [cover parentID={2D5BAB28-F6E5-4786-9C07-4DD90AEB4C44}]
  Is channel within valid range?
  [/cover] */
  else if ((uint32)Channel >= (GPT_MAX_CHANNELS))
  {
    /* [cover parentID={681E6C82-6A77-4589-A11A-5A073E87D1FE}]
    Report DET and set error flag
    [/cover] */
    Gpt_lReportError(GPT_SID_STOPTIMER, GPT_E_PARAM_CHANNEL);

    IDetVal = GPT_E_DET_ERR;  /* Set IDetVal */
  }
  else
  {
    
    #if ((GPT_SAFETY_ENABLE == STD_ON) || \
         (GPT_MULTICORE_ERROR_DETECT == STD_ON))
    /* [cover parentID={B693C599-A672-4ab2-9319-61D52AA22A48}]
    SAFETY ENABLED (OR)  MULTICORE ERROR DETECT is ON
    [/cover] */
    /* [cover parentID={5C9282C9-955A-4dc8-8B25-C5A5A10AC946}]
    Check is channel present in current core
    [/cover] */
    /* [cover parentID={42271654-B82E-4b89-B846-A7039FA548E5}]
    Check is channel present in current core and set error flag accordingly
    [/cover] */
    /* Check is channel present in current core */
    IDetVal = 
      Gpt_lMulCoreChannelDetCheck(CurrentCoreId, Channel, GPT_SID_STOPTIMER);
    #endif
  }

  /* [cover parentID={83BA9195-6456-4021-B81E-988270E6AA9B}]
  Are there any error?
  [/cover] */

  if (GPT_E_DET_ERR != IDetVal )
  #endif
  /* End of #if ((GPT_SAFETY_ENABLE == STD_ON) || \
                                            (GPT_DEV_ERROR_DETECT == STD_ON)) */
  {
    /* [cover parentID={26609AE6-F638-4b25-9C0A-CD3908059D18}]
    Multicore
    [/cover] */
    #if (GPT_MAX_CORE_USED > 1U)
    /* [cover parentID={7D65C1BE-2E1F-4b03-8767-EED08EC90C08}]
    Get the channel index relative to the core
    [/cover] */
    LocalChannel = Gpt_lMulCoreGetChannelInfo(CurrentCoreId, Channel);
    /* [cover parentID={E2843811-040C-41c2-8CDD-E097B102CF3D}]
    Single Core
    [/cover] */
    #else
    /* [cover parentID={782ED513-F4EC-4f92-96E5-6057665E8513}]
    Use the channel as is, no indexing requird
    [/cover] */
    LocalChannel = Channel;
    #endif

    /* [cover parentID={C70A25F2-EF5B-492a-B473-4893630E93BF}]
    Is the channel running?
    [/cover] */
    if (GPT_CHANNEL_RUNNING == Gpt_ThreadSafeData[CurrentCoreId]-> 
                                            Gpt_ChannelStatusPtr[LocalChannel])
    {
      /* [cover parentID={72F3B79D-A4BE-49aa-8386-6A2184C46A49}]
      GPT12 used
      [/cover] */
      #if (GPT_GPT12_USED == STD_ON)
       /* [cover parentID={57051E12-8BD2-4949-B043-8FF0C78ED28E}]
      Is GPT12 timer used?
      [/cover] */
      if(GPT_GET_CORECONFIGPTR(CurrentCoreId)->ChannelConfigPtr[LocalChannel].
      GptGpt12TimerInfo != NULL_PTR)
      {
        /* [cover parentID={C06FE1B7-45F1-4b94-B21B-D138BEDE0EB6}]
        Stop the GPT12 channel
        [/cover] */
        Gpt_lGpt12StopTimer(LocalChannel, CurrentCoreId);
      }
      else
      #endif
      {
        
        #if (GPT_TOM_USED == STD_ON) || (GPT_ATOM_USED == STD_ON)
        /* [cover parentID={CEE63C72-33D2-41d7-88C2-DD0CE796C8DE}]
        GTM used
        [/cover] */
        /* Stop the timer */
        /* [cover parentID={769CDE18-1806-468c-8FC2-BA3991D9A842}]
        Stop the GTM channel
        [/cover] */
        Gpt_lGtmStopTimer(LocalChannel, CurrentCoreId);
        #endif
      }
      /* [cover parentID={7F1F294C-F459-45d8-9453-E2E0FE362480}]
      Set status to channel Stopped
      [/cover] */
      Gpt_ThreadSafeData[CurrentCoreId]->Gpt_ChannelStatusPtr[LocalChannel] =
                                                            GPT_CHANNEL_STOPPED;
    }
    /* [cover parentID={B0D4D198-F992-425a-AE64-787BCB5C248E}]
    Otherwise no action required
    [/cover] */
  }

  return;
}/* End of Gpt_StopTimer */
/******************************************************************************/

#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={86C4BD95-A628-4597-B831-E6E7D4301B1D}]   **
**                                                                            **
** Syntax         :  void Gpt_EnableNotification                              **
**                                            (const Gpt_ChannelType Channel) **
**                                                                            **
** Description    :  This API enables the notification for a channel during   **
**                   runtime.                                                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     :  0x07                                                     **
**                                                                            **
** Sync/Async     :  Synchronous                                              **
**                                                                            **
** Reentrancy     :  Reentrant (but not for the same timer channel)           **
**                                                                            **
** Parameters(in) :  Channel: Numeric identifier of the GPT channel           **
**                                                                            **
** Parameters(out):  None                                                     **
**                                                                            **
** Return value   :  None                                                     **
**                                                                            **
*******************************************************************************/
/* [cover parentID={070C15E2-9194-44ff-9DB8-0FE97BDF9333}] */
/*  [/cover] */
void Gpt_EnableNotification(const Gpt_ChannelType Channel)
{
  
  
  uint32                    CurrentCoreId;
  Gpt_ChannelType LocalChannel;

  /* Get the current core ID */
  CurrentCoreId = GPT_GET_COREID();

  /* [cover parentID={C7C650CB-64AE-4009-A88B-C3CBE2102250}]
  Safety enable or DET is On
  [/cover] */
  #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
  uint32 IDetVal;

  /* [cover parentID={6962320A-E5A6-4a58-A650-3BB40774468E}]
  Check for DET errors
  [/cover] */
  IDetVal = Gpt_lNotifDetCheck(Channel, GPT_SID_ENABLE_NOTIFICATION, 
                               CurrentCoreId);
  /* [cover parentID={FE2B8CB9-F3FD-4a70-9990-8EB691D3D6C7}]
  Are there any errors?
  [/cover] */
  if (GPT_E_DET_ERR != IDetVal )
  #endif
    /* End of #if ((GPT_SAFETY_ENABLE == STD_ON) || \
                                            (GPT_DEV_ERROR_DETECT == STD_ON)) */
  {
    
    /* [cover parentID={DF50B473-0F09-4c6d-891D-675034D802D9}]
    Multicore
    [/cover] */
    #if (GPT_MAX_CORE_USED > 1U)
    /* [cover parentID={9BC96934-6F1C-4a35-AB8F-9DECC877714B}]
    Fetch the channel index relative to the core
    [/cover] */
    LocalChannel = GPT_GET_CORECONFIGPTR(CurrentCoreId)->Gpt_ChannelIndexPtr[Channel];
    /* [cover parentID={3AB6E043-0A04-4672-B944-896C80AEECBE}]
    Single Core
    [/cover] */
    #else
    /* [cover parentID={592F3B0F-5A9D-40c0-B506-08E408A39DF5}]
    Use the channel as is, no indexing required
    [/cover] */
    LocalChannel = Channel;
    #endif

    /* [cover parentID={C01FE63E-4DCE-4653-AFC8-2C7C58BFABEF}]
    Safety enable or DET is OFF
    [/cover] */
    #if ((GPT_SAFETY_ENABLE == STD_OFF) && (GPT_DEV_ERROR_DETECT == STD_OFF))
    /* [cover parentID={2578C641-3F1D-4e1d-A871-56111105921E}]
    Is notification function valid?
    [/cover] */
    if (NULL_PTR != 
        GPT_GET_CORECONFIGPTR(CurrentCoreId)->ChannelConfigPtr[LocalChannel].GptNotificationPtr)
    #endif
    {
      /* [cover parentID={7A3ED8BB-90A9-401e-BA03-35FF4967B150}]
      Skip the functionality in sleep mode
      [/cover] */
      if (Gpt_ThreadSafeData[CurrentCoreId]->
          Gpt_DriverMode == GPT_MODE_NORMAL)
      {
        /*
        [cover parentID={A1BCBCFB-539A-48a7-B262-F5585C124672}]
        Check is the notification flag disabled, only then set the flag
        [/cover] */
        if ((Gpt_ThreadSafeData[CurrentCoreId]->
             Gpt_FlagPtr[LocalChannel] & GPT_NOTIF_MSK) == GPT_DISABLE_NOTIF)
        {
          /* [cover parentID={767A184E-EB75-4465-9F91-562EE0AD76C3}]
          GTM used
          [/cover] */
          #if (GPT_TOM_USED == STD_ON) || (GPT_ATOM_USED == STD_ON)
           /* [cover parentID={FA608ED9-C82D-4858-99AD-462BE8737C8B}]
          If channel is GTM's
          [/cover] */
          if(GPT_GET_CORECONFIGPTR(CurrentCoreId)->ChannelConfigPtr[LocalChannel].
             GptGtmTimerInfo != NULL_PTR)
          {
            
            /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic used due to
            PBConfigStructure and is within allowed range.*/
            /* [cover parentID={3A93EDDA-3FCA-4b76-82CC-44DC3BB71745}]
            Enable Interrupt
            [/cover] */
            Gpt_lGtmIrqModify(((GPT_GET_CORECONFIGPTR(CurrentCoreId)->ChannelConfigPtr) \
                                            + LocalChannel), GPT_ENABLE_IRQ);
            
          }
          #endif
          /* #if (GPT_TOM_USED == STD_ON) || (GPT_ATOM_USED == STD_ON) */
          /* [cover parentID={385FFE02-09BD-4dfa-82C1-5E422B3C2B6C}]
          Set the notification flag
          [/cover] */
          Mcal_SetBitAtomic(
                            &Gpt_ThreadSafeData[CurrentCoreId]-> Gpt_FlagPtr[LocalChannel], 
                            GPT_BITPOS_NOTIF, 
                            GPT_BITLEN_NOTIF, 
                            GPT_ENABLE_NOTIF);
        }
      }
    }
  }
  
  return;
}/* End of Gpt_EnableNotification */
/******************************************************************************/

/*******************************************************************************
** Traceability   : [cover parentID={507E6B0D-1B0E-41b2-B4B0-4282D7A7EFBE}]   **
**                                                                            **
** Syntax         :  void Gpt_DisableNotification(                            **
**                                             const Gpt_ChannelType Channel  **
**                                               )                            **
**                                                                            **
** Description    :  This API disables the notification for a channel during  **
**                   runtime. Note, that stopping a timer automatically       **
**                   disables notification on this channel.                   **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     :  0x08                                                     **
**                                                                            **
** Sync/Async     :  Synchronous                                              **
**                                                                            **
** Reentrancy     :  Reentrant (but not for the same timer channel)           **
**                                                                            **
** Parameters(in) :  Channel: Numeric identifier of the GPT channel           **
**                                                                            **
** Parameters(out):  None                                                     **
**                                                                            **
** Return value   :  None                                                     **
**                                                                            **
*******************************************************************************/
/* [cover parentID={070C15E2-9194-44ff-9DB8-0FE97BDF9333}] */
/*  [/cover] */
void Gpt_DisableNotification(const Gpt_ChannelType Channel)
{
  #if (GPT_TOM_USED == STD_ON) || (GPT_ATOM_USED == STD_ON) || (GPT_MAX_CORE_USED > 1U)
  const Gpt_CoreConfigType     *LocalCoreConfigPtr;
  #endif
  #if (GPT_TOM_USED == STD_ON) || (GPT_ATOM_USED == STD_ON)
  const Gpt_ChannelConfigType  *LocalGptChannelPtr;
  Gpt_ChannelModeType ChannelMode;
  #endif
  #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
  uint32 IDetVal;
  #endif
  /* End of #if ((GPT_SAFETY_ENABLE == STD_ON) || \
                                            (GPT_DEV_ERROR_DETECT == STD_ON)) */
  uint32                       CurrentCoreId;                                         
  Gpt_ChannelType              LocalChannel;
  

  /* Get the current core ID */
  CurrentCoreId = GPT_GET_COREID();

  /* [cover parentID={A6E99B6E-51FF-465c-B4F4-CF9F3032FC7F}]
  Safety enable or DET is On
  [/cover] */
  #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
  /* [cover parentID={C6D0060A-2E6B-4e13-A4B3-6E6988BA7A68}]
  Check for DET errors
  [/cover] */
  IDetVal = Gpt_lNotifDetCheck(Channel, GPT_SID_DISABLE_NOTIFICATION, 
                               CurrentCoreId);
  /* [cover parentID={43B8188C-75C6-47fa-9755-8DDACDBAA150}]
  Are there any errors?
  [/cover] */
  if (GPT_E_DET_ERR != IDetVal)
  #endif
  /* End of #if ((GPT_SAFETY_ENABLE == STD_ON) || \
                                            (GPT_DEV_ERROR_DETECT == STD_ON)) */
  {
    #if (GPT_TOM_USED == STD_ON) || (GPT_ATOM_USED == STD_ON) || (GPT_MAX_CORE_USED > 1U)
    /* Get the pointer to current core configuration */
    LocalCoreConfigPtr = GPT_GET_CORECONFIGPTR(CurrentCoreId);
    #endif
    /* [cover parentID={639421E9-096E-4efe-86EF-0F01A9C244C1}]
    Multicore
    [/cover] */
    #if (GPT_MAX_CORE_USED > 1U)
    /* [cover parentID={C3D94CB1-4E1C-48ca-9C12-CD41D9B840FA}]
    Fetch the channel index relative to the core
    [/cover] */
    LocalChannel = (Gpt_ChannelType) 
                         LocalCoreConfigPtr->Gpt_ChannelIndexPtr[Channel];
    /* [cover parentID={01C1D29D-0780-400a-A6A8-97F1F09241B2}]
    Single Core
    [/cover] */
    #else
    /* [cover parentID={B3DD65E5-CA38-45c6-8979-AADFE7F8BFB8}]
    Use the channel as is, no indexing required
    [/cover] */
    LocalChannel = Channel;
    #endif
    /* [cover parentID={85C9178E-CAAE-4bac-91A9-487A28CD3A2A}]
    Skip the functionality in sleep mode
    [/cover] */
    if (Gpt_ThreadSafeData[CurrentCoreId]->
        Gpt_DriverMode == GPT_MODE_NORMAL)
    {
      /* [cover parentID={732319AE-D82E-4e8a-9ECD-6ED879F7D4B6}]
      Check is notification flag enabled, only then clear the flag
      [/cover] */
      if ((Gpt_ThreadSafeData[CurrentCoreId]-> Gpt_FlagPtr[LocalChannel] & 
           GPT_ENABLE_NOTIF) == GPT_ENABLE_NOTIF)
      {
        /* [cover parentID={A6564F65-566A-4215-ACEC-1A4979F61745}]
        GTM used
        [/cover] */
        /*
        [cover parentID={E52E77FA-CB70-4450-AD86-6761F11FDBA9}]
        Wakeup Enabled
        [/cover] */
        #if (GPT_TOM_USED == STD_ON) || (GPT_ATOM_USED == STD_ON)
        #if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
        /* [cover parentID={03E6FABC-462C-422a-B170-534E03498218}]
        Disable notification interrupt only if the wakeup flag is cleared and
        notification flag is set earlier
        [/cover] */
        
        if ((Gpt_ThreadSafeData[CurrentCoreId]-> Gpt_FlagPtr[LocalChannel] & 
             GPT_WAKEUP_MSK) == GPT_WAKEUP_DISABLED)
        #endif
        {
          /* Get pointer to channel config of current core */
          LocalGptChannelPtr = &LocalCoreConfigPtr->
                               ChannelConfigPtr[LocalChannel];
          
          /* [cover parentID={88B5E649-BF54-4a07-9B2C-78C7220B66FE}]
           Is channel used GTM's
           [/cover] */
          if(LocalGptChannelPtr -> GptGtmTimerInfo != NULL_PTR)
          {            
            /* [cover parentID={8EB989DF-9805-4895-8E7B-CC0794FEC8AD}]
            Get the mode of the channel
            [/cover] */
            ChannelMode = (LocalGptChannelPtr->GptChannelMode);
            /* [cover parentID={AB773852-1F49-40d3-9266-8B759A11B6B5}]
            Is the channel in CONTINUOS MODE?
            [/cover] */
            if (Gpt_lModeCont(ChannelMode) == (boolean)TRUE)
            {
              /* [cover parentID={A8264BB9-421C-4c4c-BFB1-7FD83A3C067D}]
              Disable the interrupt
              [/cover] */
              Gpt_lGtmIrqModify(LocalGptChannelPtr, GPT_DISABLE_IRQ);
            }
          }
        }
        #endif
        /* [cover parentID={6CDB95D7-E80F-491f-95DE-313D1B9D6574}]
        Clear the Notification flag
        [/cover] */
        Mcal_SetBitAtomic( 
          &Gpt_ThreadSafeData[CurrentCoreId]->Gpt_FlagPtr[LocalChannel],
          GPT_BITPOS_NOTIF, GPT_BITLEN_NOTIF, GPT_DISABLE_NOTIF);
      }
    }
  }
  return;
}/* End of the function Gpt_DisableNotification */
/******************************************************************************/
#endif
/* End of #if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) */

#if (GPT_TIME_ELAPSED_API == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={1E70CB43-B01D-4693-8EE6-88BA0AF94653}]   **
**                                                                            **
** Syntax         : Gpt_ValueType Gpt_GetTimeElapsed (                        **
**                                           const Gpt_ChannelType Channel    **
**                                                   )                        **
**                                                                            **
** Description    : This API returns the time already elapsed.                **
**                  In one shot mode, this is the value relative to the       **
**                  point in time, the channel has been running with          **
**                  Gpt_StartTimer.                                           **
**                  In continuous mode, the function returns the timer value  **
**                  relative to the last notification /the start              **
**                  of the channel.                                           **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : 0x03                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : Channel: Numeric identifier of the GPT channel            **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : Gpt_ValueType (Elapsed timer value in number of ticks )   **
**                                                                            **
*******************************************************************************/
/* [cover parentID={070C15E2-9194-44ff-9DB8-0FE97BDF9333}] */
/*  [/cover] */
Gpt_ValueType Gpt_GetTimeElapsed(const Gpt_ChannelType Channel )
{
  const Gpt_CoreConfigType  *LocalCoreConfigPtr;
  uint32                    CoreId;
  uint32                    TimeElapsed;

  #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
  uint32 IDetVal;
  #endif
  /* End of #if ((GPT_SAFETY_ENABLE == STD_ON) || \
                                            (GPT_DEV_ERROR_DETECT == STD_ON)) */
  Gpt_ChannelType LocalChannel;

  TimeElapsed = (uint8)0x0U;
  
  #if (GPT_READ_ACROSS_CORES == STD_OFF) 
  /* Get the current core ID */
  CoreId = GPT_GET_COREID();
  #else
  CoreId = Gpt_ConfigPtr->Gpt_Config_ChannelCoreIndex[Channel];
  #endif
  
  /* [cover parentID={95AA5608-224C-4e8f-9F34-692BB1EF562F}]
  Safety enabled or DET is On
  [/cover] */
  #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
  /* Check is channel valid */

  IDetVal = Gpt_lGetTimeDetCheck(Channel, GPT_SID_GET_TIMEELAPSED, CoreId);

  /* [cover parentID={B942E70E-3F48-496e-B94E-652A9491169E}]
  Check for DET errors
  [/cover] */
  /* [cover parentID={FEB1758C-8243-4530-85F4-28AEB7E0C69B}]
  Check for DET errors
  [/cover] */
  if (IDetVal != GPT_E_DET_ERR)
  #endif
    /* End of #if ((GPT_SAFETY_ENABLE == STD_ON) || \
                                              (GPT_DEV_ERROR_DETECT == STD_ON)) */
  {
    

    /* Get the pointer to current core configuration */
    LocalCoreConfigPtr = GPT_GET_CORECONFIGPTR(CoreId);

    /* Get the mapped offset for this channel from configuration */
    /* [cover parentID={F85EF705-68AC-4831-974F-308159E33B51}]
    Multicore
    [/cover] */
    #if (GPT_MAX_CORE_USED > 1U)
    /* [cover parentID={7A5CFCF4-4CC6-4687-8B20-C3600E99FF7A}]
    Fetch the channel index relative to the core
    [/cover] */
    LocalChannel = LocalCoreConfigPtr->Gpt_ChannelIndexPtr[Channel];
    /* [cover parentID={505E1F0A-6B9C-497d-BC35-CC8B445D20CC}]
    Single Core
    [/cover] */
    #else
    /* [cover parentID={6077FFEF-A3FD-4c1b-BADF-9209EAC268AF}]
    Use the channel as is, no indexing required
    [/cover] */
    LocalChannel = Channel;
    #endif

    /* [cover parentID={71F4669C-DF3F-43c3-AF0B-EDF67307050D}]
    Get the channel status
    [/cover] */
    /* [cover parentID={4AE579F3-6C9D-4d62-9204-B572C4172085}]
    Get TimeElapsed if timer Running/Stopped/Expired else return '0'
    [/cover] */
    if (Gpt_lCheckChannelStatus(LocalChannel, CoreId) == (boolean)TRUE)
    {
      /* [cover parentID={A9121973-2223-4dff-A8C4-C9B58D47CEB0}]
      GPT12 used
      [/cover] */
      #if (GPT_GPT12_USED == STD_ON)
      /* [cover parentID={60941C8A-E931-41fc-A4A0-B324FFC3FAC3}]
      Is channel used GPT12's
      [/cover] */
      if(LocalCoreConfigPtr->ChannelConfigPtr[LocalChannel].
                                              GptGpt12TimerInfo != NULL_PTR)
      {
        
        /* [cover parentID={B65CCD60-D30F-4884-B1C0-62EAE2B12850}]
        Read the time elapsed
        [/cover] */
        TimeElapsed = Gpt_lGpt12GetTimeElapsed
                        (&LocalCoreConfigPtr->ChannelConfigPtr[LocalChannel], 
                         LocalChannel, CoreId);
                         
      }
      else
      #endif
      {
        
        #if (GPT_TOM_USED == STD_ON) || (GPT_ATOM_USED == STD_ON)
        /* [cover parentID={8D7C82B7-0308-4fa3-87BB-26ABF6960EEF}]
        Read the time elapsed
        [/cover] */
        /* [cover parentID={F8F5F772-8CFA-43f7-B59F-2ABC137D8A3B}]
        GTM used
        [/cover] */
        TimeElapsed = Gpt_lGtmGetTimeElapsed
                    (&LocalCoreConfigPtr->ChannelConfigPtr[LocalChannel]);
        #endif
      }
    }
  }

  return (Gpt_ValueType)TimeElapsed; /* Return TimeElapsed value  */
}/* End of Gpt_GetTimeElapsed */
/******************************************************************************/
#endif
/* End of #if (GPT_TIME_ELAPSED_API == STD_ON) */

#if (GPT_TIME_REMAINING_API == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={B6D949EC-10CB-42f6-A017-4647429FC9CF}]   **
**                                                                            **
** Syntax         : Gpt_ValueType Gpt_GetTimeRemaining(                       **
**                                          const Gpt_ChannelType Channel     **
**                                                    )                       **
**                                                                            **
** Description    : This API returns the timer value remaining until the      **
**                  target time is reached (calculated by the normal          **
**                  operation function by subtracting the timeout minus the   **
**                  current timer value and returning the absolute value).    **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : 0x04                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : Channel: Numeric identifier of the GPT channel            **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : Gpt_ValueType (Remaining timer value in number of ticks ) **
**                                                                            **
*******************************************************************************/
/* [cover parentID={070C15E2-9194-44ff-9DB8-0FE97BDF9333}] */
/*  [/cover] */
Gpt_ValueType Gpt_GetTimeRemaining(const Gpt_ChannelType Channel)
{
  const Gpt_CoreConfigType  *LocalCoreConfigPtr;
  uint32                    CoreId;
  uint32                    ReadTimer;

  #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
  uint32 IDetVal;
  #endif

  Gpt_ChannelType LocalChannel;

  ReadTimer = (uint8)0x0U;
  #if (GPT_READ_ACROSS_CORES == STD_OFF) 
  /* Get the current core ID */
  CoreId = GPT_GET_COREID();
  #else
  CoreId = Gpt_ConfigPtr->Gpt_Config_ChannelCoreIndex[Channel];
  #endif
  /* [cover parentID={AB0A6538-5BBD-41c0-9D7B-2B6CCD3A2297}]
  Safety enabled or DET is On
  [/cover] */
  #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
  /* [cover parentID={CBDBBC3F-AE32-47e4-A33D-2E89A45640B6}]
  Check for DET errors
  [/cover] */
  IDetVal = Gpt_lGetTimeDetCheck(Channel, GPT_SID_GET_TIMEREMAINING, CoreId);
  /* [cover parentID={29DD7F52-478F-422f-A8C0-4623415F11C0}]
  Are there any errors?
  [/cover] */
  if (IDetVal != GPT_E_DET_ERR)
  #endif
    /* End of #if ((GPT_SAFETY_ENABLE == STD_ON) || \
                                              (GPT_DEV_ERROR_DETECT == STD_ON)) */
  {
    
    /* Get the pointer to current core configuration */
    LocalCoreConfigPtr = GPT_GET_CORECONFIGPTR(CoreId);

    /* Get the mapped offset for this channel from configuration */
    /* [cover parentID={33322BF7-77B9-4eac-931C-7EBAF9B84C6A}]
    Multicore
    [/cover] */
    #if (GPT_MAX_CORE_USED > 1U)
    /* [cover parentID={D68E83BC-0F8A-4932-853F-18274C5A8FD8}]
    Fetch the channel index relative to the core
    [/cover] */
    LocalChannel = LocalCoreConfigPtr->Gpt_ChannelIndexPtr[Channel];
    /* [cover parentID={1EFDB7AD-5919-4f41-92D8-4379019CE92A}]
    Single Core
    [/cover] */
    #else
    /* [cover parentID={36D1A835-CED5-4227-BDFE-B78EDD9181EA}]
    Use the channel as is, no indexing required
    [/cover] */
    LocalChannel = Channel;
    #endif

    /* [cover parentID={B61B9BDA-CCC3-4d3a-BB40-A4F73ABE9E44}]
    Get the channel status
    [/cover] */
    /* [cover parentID={7C969C02-09F6-4eb2-9A3E-40E133473365}]
    Get TimeRemaining if timer Running/Stopped/Elapsed else return '0'
    [/cover] */
    if (Gpt_lCheckChannelStatus(LocalChannel, CoreId) == (boolean)TRUE)
    {
      
      /* [cover parentID={BFEBD2EA-713E-4405-9761-D2B5F02CC63D}]
      GPT12 used
      [/cover] */
      #if (GPT_GPT12_USED == STD_ON)
      /* [cover parentID={E5F7B1D7-CC0F-40f3-9CB2-95F039A7FB25}]
      Is channel used GPT12's
      [/cover] */
      if(LocalCoreConfigPtr->ChannelConfigPtr[LocalChannel].
         GptGpt12TimerInfo != NULL_PTR)
      {
        
        /* [cover parentID={3A0B104E-67F0-4ffd-9FCD-CDE4B9EFF43E}]
        Get the time remaining
        [/cover] */
        ReadTimer = Gpt_lGpt12GetTimeRemaining
                    (&LocalCoreConfigPtr->ChannelConfigPtr[LocalChannel], 
                     LocalChannel, CoreId);
                      
      }
      else
      #endif
      {
        
        #if (GPT_TOM_USED == STD_ON) || (GPT_ATOM_USED == STD_ON)
        /* [cover parentID={F083F53B-0F8F-4e36-9CAB-1624F625FA33}]
        GTM used
        [/cover] */
        /* [cover parentID={B60FCA43-0A26-4760-9AE3-65F30910B142}]
        Get the time remaining
        [/cover] */
        ReadTimer = Gpt_lGtmGetTimeRemaining
                  (&LocalCoreConfigPtr->ChannelConfigPtr[LocalChannel]);
        #endif
      }
    }
  }

  return (Gpt_ValueType)ReadTimer; /* Remaining timer value in ticks */
}/* End of Gpt_GetTimeRemaining */
/******************************************************************************/
#endif
/* End of #if (GPT_TIME_REMAINING_API == STD_ON) */

#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={B9AAD8F8-517F-48b9-B11B-51D783C1C1D4}]   **
**                                                                            **
** Syntax         : void Gpt_SetMode(const Gpt_ModeType Mode)                 **
**                                                                            **
** Description    : This API sets the operation mode to the given mode        **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : 0x09                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : Mode (GPT_MODE_NORMAL/GPT_MODE_SLEEP)                     **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
/* [cover parentID={070C15E2-9194-44ff-9DB8-0FE97BDF9333}] */
/*  [/cover] */
/* [cover parentID={4141A6C4-464E-4050-A147-DE34112CA916}] */
/*  [/cover] */
void Gpt_SetMode(const Gpt_ModeType Mode)
{
  const Gpt_CoreConfigType *LocalCoreConfigPtr;
  uint32                   CurrentCoreId;

  /* Get the current core ID */
  CurrentCoreId = GPT_GET_COREID();

  /* [cover parentID={AAFFCF36-C9BC-4491-9BAA-158D6CA14357}]
  Safety enable or DET is On
  [/cover] */
  #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
  /* If no errors reported, set the mode of the driver as passed by parameter */

  /*
  [cover parentID={91232061-ED09-4dfb-A937-B698EFAD5EA5}]
  Call to Gpt_lSetModeDetCheck
  [/cover]
  [cover parentID={6FAF31A0-37FB-474d-98FB-72433D2C3B3D}]
  Are errors reported?
  [/cover] */
  if (GPT_E_DET_NO_ERR == Gpt_lSetModeDetCheck(Mode, CurrentCoreId))
  #endif
  /* End of #if ((GPT_SAFETY_ENABLE == STD_ON) || \
                                            (GPT_DEV_ERROR_DETECT == STD_ON)) */
  {
    /* Get the pointer to current core configuration */
    LocalCoreConfigPtr = GPT_GET_CORECONFIGPTR(CurrentCoreId);

    /* [cover parentID={7376D88D-2E8E-4e28-B6D7-77C5B886D28E}]
    Is Sleep requested?
    [/cover] */
    if (GPT_MODE_SLEEP == Mode)
    {
      /* [cover parentID={571F3886-19E6-4643-BC6B-D7907AA8144D}]
      Switch from NORMAL to  SLEEP mode
      [/cover] */
      Gpt_lSetSleepMode(LocalCoreConfigPtr, CurrentCoreId);
      
    }
    /*
    [cover parentID={FADAFD24-9AFA-4ff2-A035-721E2CC18765}]
    Switch from SLEEP to NORMAL mode
    [/cover] */
    if (GPT_MODE_NORMAL == Mode)
    {
      /* [cover parentID={DE064B10-B9D9-4d52-B585-272C9E457584}]
      Switch from SLEEP to NORMAL mode
      [/cover] */
      Gpt_lSetNormalMode(LocalCoreConfigPtr, CurrentCoreId);
      
    }


  }
  return;
}/* End of Gpt_SetMode */
/******************************************************************************/

/*******************************************************************************
** Traceability   : [cover parentID={F433DDCD-AB59-4d0b-8176-FDBDA13DC0AD}]   **
**                                                                            **
** Syntax         : void Gpt_EnableWakeup (const Gpt_ChannelType channel)     **
**                                                                            **
** Description    : This API Enables the wakeup notification of a             **
**                  single GPT channel.                                       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : 0x0B                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant (but not for the same timer channel)            **
**                                                                            **
** Parameters(in) : Channel: Numeric identifier of the GPT channel            **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
/* [cover parentID={070C15E2-9194-44ff-9DB8-0FE97BDF9333}] */
/*  [/cover] */
void Gpt_EnableWakeup(const Gpt_ChannelType Channel)
{
  #if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
  #if ((GPT_MAX_CORE_USED > 1U) || ((GPT_SAFETY_ENABLE == STD_OFF) && \
  (GPT_DEV_ERROR_DETECT == STD_OFF)))
  const Gpt_CoreConfigType  *LocalCoreConfigPtr;
  #endif
  #endif

  uint32                    CurrentCoreId;

  #if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
  Gpt_ChannelType LocalChannel;
  #endif

  #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
  uint32 IDetVal;
  #endif

  /* Get the current core ID */
  CurrentCoreId = GPT_GET_COREID();

  /* [cover parentID={7DCE5551-73A3-4bbd-8799-1F8F227E2A89}]
  Safety enable or DET is ON
  [/cover] */
  #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
  /* [cover parentID={9DCCE616-0DCA-4307-B6C6-85C88E0FF988}]
  Check for DET errors
  [/cover] */
  /* Check, is the channel valid and is wakeup capable */
  IDetVal = Gpt_lWakeupDetCheck(Channel, GPT_SID_ENABLE_WAKEUP, CurrentCoreId);

  /* [cover parentID={8556031B-82DF-4a7b-A5DA-D981C351860F}]
  Are there any errors?
  [/cover] */
  if (IDetVal != GPT_E_DET_ERR)
  #endif
  {
    /* [cover parentID={C887DADB-7023-4185-B9FE-9D2AF06E59B6}]
    Report Wakeup Source is ON
    [/cover] */
    #if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
    /* Get the pointer to current core configuration */
    #if ((GPT_MAX_CORE_USED > 1U) || ((GPT_SAFETY_ENABLE == STD_OFF) && \
                                    (GPT_DEV_ERROR_DETECT == STD_OFF)))
    LocalCoreConfigPtr = GPT_GET_CORECONFIGPTR(CurrentCoreId);
    #endif
    #if (GPT_MAX_CORE_USED > 1U)

    /* Get the mapped offset for this channel from configuration */
    /* [cover parentID={71B4C7A6-4055-4485-8C78-6A62A0E0AEA5}]
    Multicore
    [/cover] */
    /* [cover parentID={AFA05AEF-CB4A-41d5-9699-DA3B88D92B0C}]
    Fetch the channel index relative to the core
    [/cover] */
    LocalChannel = LocalCoreConfigPtr->Gpt_ChannelIndexPtr[Channel];

    /* [cover parentID={9E4DD025-F9D8-41f7-88F7-D4D0C413FB14}]
    Single Core
    [/cover] */
    #else
    /* [cover parentID={674ADCDB-049C-445b-99AE-E84AABDB2AEC}]
    Use the channel as is, no indexing required
    [/cover] */
    LocalChannel = Channel;
    #endif

    /*
    [cover parentID={6D88D1A8-28E3-4558-8440-6A98328ED408}]
    Set the wakeup flag state to wakeup requested only in wakeup disabled or
    wakeup disable requested cases
    [/cover] */
    if(GPT_MODE_NORMAL == Gpt_ThreadSafeData[CurrentCoreId]->Gpt_DriverMode)
    {
      /* [cover parentID={1B863426-30D4-40e5-8FBE-8C3C2FFA26A0}]
      Safety enable or DET is On
      [/cover] */
      #if ((GPT_SAFETY_ENABLE == STD_OFF) && (GPT_DEV_ERROR_DETECT == STD_OFF))
      /*
      [cover parentID={534057DC-C3D5-4c3a-86D5-5D81EA032663}]
      Check is Channel wakeup capable
      [/cover] */
      if ((&LocalCoreConfigPtr->ChannelConfigPtr[LocalChannel])-> 
                                      GptEnableWakeupState == (boolean)TRUE)
      #endif
      {
        /* [cover parentID={3A3E09DC-E69A-4743-B50F-98869DE08CD3}]
        Set the corresponding wakeup flag
        [/cover] */
        Mcal_SetBitAtomic( 
                           &Gpt_ThreadSafeData[CurrentCoreId]->Gpt_FlagPtr[LocalChannel], 
                           GPT_BITPOS_WAKEUP, 
                           GPT_BITLEN_WAKEUP, 
                           GPT_WAKEUP_ENABLED
                         );

      }
    }
    #endif
    /* End of #if (GPT_REPORT_WAKEUP_SOURCE == STD_ON) */
  }
  /*
  MISRA2012_RULE_2_2_JUSTIFICATION: Tricore Atomic instructions are used
  to update global variables in this function call, which is not detected
  by MISRA. Hence, the assignment is not a dead code
  */
  return;
}/* End of Gpt_EnableWakeup*/
/******************************************************************************/

/*******************************************************************************
** Traceability   : [cover parentID={3D23E526-D369-45af-A152-546177BEDDC0}]   **
**                                                                            **
** Syntax         : void Gpt_DisableWakeup(const Gpt_ChannelType channel)     **
**                                                                            **
** Description    : This API disables the wakeup notification of a            **
**                  single GPT channel.                                       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : 0x0A                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant (but not for the same timer channel)            **
**                                                                            **
** Parameters(in) : Channel: Numeric identifier of the GPT channel            **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
/* [cover parentID={070C15E2-9194-44ff-9DB8-0FE97BDF9333}] */
/*  [/cover] */
void Gpt_DisableWakeup(const Gpt_ChannelType Channel)
{
  #if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
    #if (GPT_MAX_CORE_USED > 1U)
    const Gpt_CoreConfigType  *LocalCoreConfigPtr;
    #endif
   /* Gpt_ChannelModeType ChannelMode; */
  Gpt_ChannelType LocalChannel;
  #endif

  uint32                    CurrentCoreId;
  #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
  uint32 IDetVal;
  #endif

  /* Get the current core ID */
  CurrentCoreId = GPT_GET_COREID();

  /* [cover parentID={692D5B84-6F51-4052-83EC-543C098161BF}]
  Safety enable or DET is On
  [/cover] */
  #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
  /* [cover parentID={0B7AE9C1-8D74-4a8b-B2FB-CAEDAEC2A290}]
  Check for DET errors
  [/cover] */
  /* Call DET check,If DET occurred then return without executing the routine */
  IDetVal = Gpt_lWakeupDetCheck(Channel,GPT_SID_DISABLE_WAKEUP, CurrentCoreId);
  /* [cover parentID={7250BFBF-8052-4c4b-9D53-B8B16250938E}]
  Are there any errors?
  [/cover] */
  if (IDetVal != GPT_E_DET_ERR)
  #endif
  /* End of #if ((GPT_SAFETY_ENABLE == STD_ON) || \
                                            (GPT_DEV_ERROR_DETECT == STD_ON)) */
  {
    /* [cover parentID={D6F0500C-8FDE-4140-B3FF-7576C87C55CA}]
    Report Wakeup Source is ON
    [/cover] */
    #if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
    #if (GPT_MAX_CORE_USED > 1U)
    LocalCoreConfigPtr = GPT_GET_CORECONFIGPTR(CurrentCoreId);
    /* Get the mapped offset for this channel from configuration */
    /* [cover parentID={1BAF9225-B490-48da-8E76-C1403A3EE7E1}]
    Multicore
    [/cover] */

    /* Get the pointer to current core configuration */
    /* [cover parentID={27313FDD-BCA5-4016-A218-B89B8507C8A8}]
    Fetch the channel index relative to the core
    [/cover] */
    LocalChannel = LocalCoreConfigPtr->Gpt_ChannelIndexPtr[Channel];
    /* [cover parentID={5F00035C-0ED8-4655-A2A3-67B69A6DDADF}]
    Single Core
    [/cover] */
    #else
    /* [cover parentID={014925E0-BE79-4d1d-89C2-194B0475DD9D}]
    Use the channel as is, no indexing required
    [/cover] */
    LocalChannel = Channel;
    #endif
    /* [cover parentID={39F18D0A-DC0A-4993-AB68-A3F22719A91F}]
    Is wakeup flag set?
    [/cover] */
    if ((Gpt_ThreadSafeData[CurrentCoreId]->
         Gpt_FlagPtr[LocalChannel] & GPT_WAKEUP_MSK) == GPT_WAKEUP_MSK)
    {
      /*
      Disable the flag if in sleep mode or wakeup is enabled, and not yet serviced
      [cover parentID={D9E89B54-E405-4281-8139-400D7A6CD1D4}]
      */

      if(GPT_MODE_SLEEP == Gpt_ThreadSafeData[CurrentCoreId]->Gpt_DriverMode)
      {
        /* [cover parentID={AEB4647E-B4D8-44b5-A45A-18C0CCC25E20}]
        Clear the Wakeup flag
        [/cover] */
        Mcal_SetBitAtomic( 
                           &Gpt_ThreadSafeData[CurrentCoreId]->Gpt_FlagPtr[LocalChannel], 
                           GPT_BITPOS_WAKEUP, 
                           GPT_BITLEN_WAKEUP, 
                           GPT_WAKEUP_DISABLED
                         );
      }
    }
    #endif
    /* End of #if (GPT_REPORT_WAKEUP_SOURCE == STD_ON) */
  }
  return;
}/* End of Gpt_DisableWakeup */
/******************************************************************************/

/*******************************************************************************
** Traceability   : [cover parentID={5D24A7B0-59FD-4b64-AFFA-8EFA5A9907D3}]   **
**                                                                            **
** Syntax         : void Gpt_CheckWakeup (                                    **
**                                  const EcuM_WakeupSourceType WakeupSource  **
**                                       )                                    **
**                                                                            **
** Description    : This API checks whether the wakeup capable GPT channel    **
**                  is the source for a wakeup event and calls the            **
**                  ECU state manager service EcuM_SetWakeupEvent             **
**                  in case of a valid GPT channel wakeup event.              **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : 0x0C                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : wakeupSource                                              **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
/* [cover parentID={070C15E2-9194-44ff-9DB8-0FE97BDF9333}] */
/*  [/cover] */
void Gpt_CheckWakeup(const EcuM_WakeupSourceType WakeupSource)
{
  uint32 CurrentCoreId;

  /* Get the current core ID */
  CurrentCoreId = GPT_GET_COREID();

  /* [cover parentID={67FD5ADE-5354-40a2-A989-D556D11EDC62}]
  Safety enabled or DET is ON
  [/cover] */
  #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
  /* [cover parentID={597329D6-EC30-4c52-8A80-E8486DE8D42B}]
  Is driver initialised from the current core?
  [/cover] */
  /* Check if driver was initialized from the current core */
  if (GPT_DRIVER_INITIALIZED != 
      Mcal_GetBitAtomic(Gpt_DriverStatus, GPT_CORE_BITPOS(CurrentCoreId), 
                        GPT_CORE_STATUS_LEN))
  {
    /* [cover parentID={7181083C-F780-4073-A893-77F9EA0E8451}]
    Report to DET
    [/cover] */
    Gpt_lReportError(GPT_SID_CHECK_WAKEUP, GPT_E_UNINIT);
  }
  else
  #endif
  /* End of #if ((GPT_SAFETY_ENABLE == STD_ON) || \
                                            (GPT_DEV_ERROR_DETECT == STD_ON)) */
  {
    /* [cover parentID={54BDCB66-1E29-489f-A6AB-219C54966A11}]
    Report Wakeup Source is ON
    [/cover] */
    #if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
    /* [cover parentID={C4E50798-285F-406c-A663-42967E09B607}]
    Is wakeup info stored matches with WakeupSource
    [/cover] */
    if (Gpt_ThreadSafeData[CurrentCoreId]->Gpt_WakeupChannelInfo == 
                                                        WakeupSource)
    {
      /* [cover parentID={7C306EA5-3E11-40b4-A4DE-4CD7E3DDC439}]
      Wakeup the core
      [/cover] */
      EcuM_SetWakeupEvent(WakeupSource);
    }
    #endif
    /* End of #if (GPT_REPORT_WAKEUP_SOURCE == STD_ON) */
  }
      
  UNUSED_PARAMETER(WakeupSource);
  return;
}/* End of Gpt_CheckWakeup*/
/******************************************************************************/
#endif
/* End of #if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) */

#if ((GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON) || \
(GPT_PREDEF_TIMER_1US_16BIT_EN == STD_ON)   || \
(GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON)   || \
(GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))
/*******************************************************************************
** Traceability   : [cover parentID={1045262E-CC8D-4174-BCC9-A8AE3459CF3D}]   **
**                                                                            **
** Syntax         : Std_ReturnType Gpt_GetPredefTimerValue(                   **
**                               const Gpt_PredefTimerType PredefTimer,       **
**                               uint32 *const TimeValuePtr                   **
**                                                        )                   **
**                                                                            **
** Description    : This API Delivers the current value of the                **
**                  desired GPT Predef Timer.                                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : 0x0D                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : PredefTimer  - GPT Predef Timer                           **
**                                                                            **
** Parameters(out): TimeValuePtr -                                            **
**                        Pointer to time value destination data in RAM       **
**                                                                            **
** Return value   : Std_ReturnType -                                          **
**                                E_OK      : No error has been detected      **
**                                E_NOT_OK  : Aborted due to errors           **
**                                                                            **
*******************************************************************************/
/* [cover parentID={070C15E2-9194-44ff-9DB8-0FE97BDF9333}] */
/*  [/cover] */
Std_ReturnType Gpt_GetPredefTimerValue
            (const Gpt_PredefTimerType PredefTimer, uint32 *const TimeValuePtr)
{
  uint32 CurrentCoreId;
  uint32 IErrVal;
  /* [cover parentID={F6028452-43D6-4a55-935B-8EC7F2849C7B}] 
  Predefined Timer in Multicore Environment
  [/cover] */
  /* [cover parentID={0C7E104B-98CD-45be-97D1-9FAF6A5ED080}]
  Set return value to E_NOT_OK
  [/cover] */
  Std_ReturnType RetVal = E_NOT_OK;

  /* Get the current core ID */
  CurrentCoreId = GPT_GET_COREID();
  /* [cover parentID={885AC416-B01F-46a6-80D4-3581F5E79333}]
  Check for errors
  [/cover] */
  IErrVal = Gpt_lGetPredefErrCheck(PredefTimer, TimeValuePtr, CurrentCoreId);

  /* [cover parentID={F7B34D1D-E91A-4376-B0CD-FBA71A433C83}]
  Are there any errors?
  [/cover] */
  if (IErrVal != GPT_E_DET_ERR)
  {
    /* [cover parentID={1890A587-413E-482c-8020-9F56652CBE64}]
    1us Predefined Timer  (16/24/32Bit) enabled
    [/cover] */
    #if ((GPT_PREDEF_TIMER_1US_16BIT_EN == STD_ON)    || \
         (GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON)    || \
         (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))
    /* [cover parentID={10286610-842E-40c5-9F3E-5CD9DD602116}]
    Is 1us PredefTimer (16/24/32Bit) ON?
    [/cover] */
    if ((PredefTimer == GPT_PREDEF_TIMER_1US_16BIT) || 
        (PredefTimer == GPT_PREDEF_TIMER_1US_24BIT) || 
        (PredefTimer == GPT_PREDEF_TIMER_1US_32BIT))
    {
      /* [cover parentID={931D6F5F-AE77-4943-963D-9B9EEDF49E0A}]
      Read the timer value and save it in the reference location
      [/cover] */
      *TimeValuePtr = 
                    Gpt_lGtmGet1UsPredefTimerValue(PredefTimer, CurrentCoreId);
    }
    #endif

  /* [cover parentID={42B4200E-1929-492c-8E1E-6A076479EC5C}]
    100us Predef Timer enabled
    [/cover] */
    #if (GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON)
    /* [cover parentID={CD62C173-1AAB-4450-8ED7-BF55AE67C079}]
    Check PredefTimer value is  32 bit 100us PredefTimer value
    [/cover] */
    if (PredefTimer == GPT_PREDEF_TIMER_100US_32BIT)
    {
      /* [cover parentID={21AFE5AB-D2BA-4754-9274-182097439534}]
      Read the timer value and save it in the reference location
      [/cover] */
      *TimeValuePtr = Gpt_lGtmGet100UsPredefTimerValue(CurrentCoreId);
    }
    #endif
    /* [cover parentID={59A57CD3-98DE-4ed0-9F22-5938FD4FC1A7}]
    Set return value to E_OK
    [/cover] */
    RetVal = E_OK;
  }

  return RetVal;
}/* End of Gpt_GetPredefTimerValue */
/******************************************************************************/
#endif
/* End of #if ((GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON) || \
              (GPT_PREDEF_TIMER_1US_16BIT_EN == STD_ON)    || \
              (GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON)    || \
              (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON)) */

#if (GPT_INITCHECK_API == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID=]                                         **
**                                                                            **
** Syntax         : Std_ReturnType Gpt_InitCheck                              **
**                                  (                                         **
**                                    const Gpt_ConfigType *const ConfigPtr   **
**                                  )                                         **
**                                                                            **
** Description    : This function verifies the initialization the GPT driver  **
**                  in context to the core from where the API is invoked.     **
**                                                                            **
**                  Note: Init check should be performed in the following     **
**                        sequence:                                           **
**                          1. Call Gpt_Init from a core (master/salve core). **
**                          2. Call Gpt_InitCheck from the same core.         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : 0x0E                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : None                                                      **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : E_OK - Initialization comparison is success               **
**                  E_NOT_OK - Initialization comparison failed               **
**                                                                            **
*******************************************************************************/
/* [cover parentID={86147709-85ED-4413-BB21-AC61123F0375}]
Gpt_InitCheck
[/cover]*/
/* [cover parentID={E7E4A641-B68C-4fec-909B-B9596A9F9438}]
Is the current core master core?
[/cover]*/
Std_ReturnType Gpt_InitCheck(const Gpt_ConfigType *const ConfigPtr)
{
  const  Gpt_CoreConfigType *LocalCoreConfigPtr;
  uint32 CurrentCoreId;
  uint32 CompareMatchFlag = GPT_INITCHECK_STS_VAL;
  Std_ReturnType RetVal   = E_OK;
  uint8  BitPos;

  /* Get the core Id from which it is called */
  CurrentCoreId = GPT_GET_COREID();

  /* [cover parentID={1E55E816-2E34-4081-BDC5-9B7DB3E0CE4B}]
  Is the current core master core?
  [/cover] */
  if (CurrentCoreId == MCAL_MASTER_COREID)
  {
    /* [cover parentID={3E13E9E0-3BA8-4aa3-9BEE-A051D36C883C}]
    Is passed configuration pointer vaild?
    [/cover] */
    if ((ConfigPtr == NULL_PTR) || (ConfigPtr != Gpt_ConfigPtr))
    {
      RetVal = E_NOT_OK;
    }
  }
  /* [cover parentID={F8B2A9F7-E73F-4348-A4F1-36F13A20C248}]
  Are there any errors?
  [/cover] */
  if (RetVal == E_OK)
  {
    BitPos = GPT_CORE_BITPOS(CurrentCoreId);
    /* [cover parentID={EFBB01A6-35B8-441e-85EF-BEFA99709676}]
    Driver Initialized from current core?
    [/cover] */
    if (GPT_DRIVER_INITIALIZED != 
        Mcal_GetBitAtomic(Gpt_DriverStatus, BitPos, GPT_CORE_STATUS_LEN))
    {
      RetVal = E_NOT_OK;
    }
    /* [cover parentID={408E072F-C37C-431a-AC93-9ACBD2BFD063}]
    Driver in wrong mode in current core?
    [/cover] */
    /* Check if the driver is in wrong mode in current core */
    else if (GPT_MODE_SLEEP == 
             Gpt_ThreadSafeData[CurrentCoreId]->Gpt_DriverMode)
    {
      RetVal = E_NOT_OK;
    }
    else
    {
      /* Get the pointer to current core configuration */
      LocalCoreConfigPtr = GPT_GET_CORECONFIGPTR(CurrentCoreId);
      /* [cover parentID={2EC3436E-7EFB-441a-BE52-DA295CDC4201}]
      Any normal channel present in current core?
      [/cover] */
      /* Check if any normal channel present in the current core */
      if (LocalCoreConfigPtr->ChannelConfigPtr != NULL_PTR)
      {
        /* Check all channels allocated to the core are initialized */
        CompareMatchFlag &= ~(E_OK ^ (uint32) 
                              Gpt_lChannelsInitCheck(CurrentCoreId, LocalCoreConfigPtr));
      }
      /* [cover parentID={38E5E15A-56F4-4692-9147-571586E88035}]
      Is Current core the master core?
      [/cover] */
      if (CurrentCoreId == MCAL_MASTER_COREID)
      {
        /* [cover parentID={31AF8BB4-622E-4081-BA52-B029390739F1}]
        1us Predefined Timer  (16/24/32Bit) enabled
        [/cover] */
        #if ((GPT_PREDEF_TIMER_1US_16BIT_EN == STD_ON) || \
             (GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON) || \
             (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))
        /* [cover parentID={088A889B-F56E-485c-93D6-B8593C1D532E}]
        Call Gpt_lGtmInitCheck1UsPredefTimer
        [/cover] */
        /* Check 1us predefined timer is configured correctly */
        CompareMatchFlag &= ~(E_OK ^ (uint32) 
                              Gpt_lGtmInitCheck1UsPredefTimer(LocalCoreConfigPtr));
        #endif

        /* [cover parentID={44477E90-750F-4681-A6AB-B9AA11FE3C7F}]
        100us Predef Timer enabled
        [/cover] */
        #if (GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON)
        /* Check 100us predefined timer is configured correctly */
        /* [cover parentID={64AE09E1-3A0C-4085-B9B8-5F3E5CDFEB7E}]
          Call Gpt_lGtmInitCheck100UsPredefTimer
          [/cover] */
        CompareMatchFlag &= ~(E_OK ^ (uint32) 
                              Gpt_lGtmInitCheck100UsPredefTimer(LocalCoreConfigPtr));
        #endif
      }

      /* [cover parentID={266BEA85-1A5C-4a5a-84A9-81E67F98823F}]
      Any check failed?
      [/cover] */
      /* Check the flag, if the current value is same as initial value */
      if (CompareMatchFlag != GPT_INITCHECK_STS_VAL)
      {
        /* InitCheck failed */
        RetVal = E_NOT_OK;
      }
    }
  }

  return RetVal;
}/* End of Gpt_InitCheck */
/******************************************************************************/
#endif
/* End of #if (GPT_INITCHECK_API == STD_ON) */

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/
#if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
/*******************************************************************************
** Traceability   :[cover parentID={E19E9B98-170C-4392-B6C0-5D5A6A1AA1F4}]    **
**                                                                            **
** Syntax         : static uint32 Gpt_lInitDetCheck                           **
**                                  (                                         **
**                                    const Gpt_ConfigType *const ConfigPtr,  **
**                                    const uint32 CurrentCoreId              **
**                                  )                                         **
**                                                                            **
** Description    : This function checks DET errors in Gpt_Init Function      **
**                                                                            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : ConfigPtr     - Pointer to the configuration structure    **
**                  CurrentCoreId - Current Core ID                           **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : IErrVal (uint32)                                          **
**                                                                            **
*******************************************************************************/
static uint32 Gpt_lInitDetCheck(const Gpt_ConfigType *const ConfigPtr,
                                const uint32 CurrentCoreId)
{
  /* [cover parentID={F5E0A30F-4B42-426f-BBF9-FF6ABB39DBD9}]
  Gpt_lInitDetCheck
  [/cover] */
  uint32 IErrVal = GPT_E_DET_NO_ERR;
  uint8 CoreBitPos = GPT_CORE_BITPOS(CurrentCoreId);
  /* [cover parentID={A1B12915-270C-4c4c-8F02-A95365209D6A}]
  Is ConfigPtr valid? [/cover] */
  if (ConfigPtr == NULL_PTR )
  {
    
    /* [cover parentID={CF20BD7B-67D8-4876-8BCD-DC5FEAB16911}]
    Report DET     
    [/cover] */
    Gpt_lReportError(GPT_SID_INIT, GPT_E_INIT_FAILED);
    IErrVal = GPT_E_DET_ERR;
    
  }
  else
    
  /* [cover parentID={A705B0FB-4FE2-4983-9255-804427A7F0EF}]
  Is Safety or Multicore Error reporting enabled?
  [/cover] */ 
  #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_MULTICORE_ERROR_DETECT == STD_ON))
  {
    
    /* [cover parentID={BF1DFE46-6272-42bf-90C2-E54D342D354A}]
    Check multicore related DETs
    [/cover] */
    IErrVal = Gpt_lMulCoreInitDetCheck(CurrentCoreId);
    
  }
  
  /* [cover parentID={FC553C49-B465-46a6-BAFA-CA5BEE32D931}]
  Any error reported?
  [/cover] */
  if (GPT_E_DET_ERR != IErrVal)

  #endif
  {
    
    /* [cover parentID={B1414F59-41A8-4c19-A639-14AB2CFB907B}]
    Is Gpt driver already initialized in current core?
    [/cover] */
    if (GPT_DRIVER_UNINITIALIZED != 
        Mcal_GetBitAtomic(Gpt_DriverStatus, CoreBitPos, GPT_CORE_STATUS_LEN))
    {
      /* [cover parentID={CF20BD7B-67D8-4876-8BCD-DC5FEAB16911}]
      Report DET
      [/cover] */
      /* Report to DET */
      Gpt_lReportError(GPT_SID_INIT, GPT_E_ALREADY_INITIALIZED);

      /* Set IErrVal */
      IErrVal = GPT_E_DET_ERR;
    }
  }

  return IErrVal;
}/* End of Gpt_lInitDetCheck */
/******************************************************************************/
#endif
/* End of #if ((GPT_SAFETY_ENABLE == STD_ON) || \
                                  (GPT_DEV_ERROR_DETECT == STD_ON)) */

/*******************************************************************************
** Traceability   : [cover parentID={040EE8F3-E054-41d1-997A-3732352E4710}]   **
**                                                                            **
** Syntax         : LOCAL_INLINE void Gpt_lChannelsInit                       **
**                            (                                               **
**                              const uint32 CurrentCoreId,                   **
**                              Gpt_CoreConfigType const *const CoreConfigPtr **
**                            )                                               **
** Description    : This function initializes all the channels configured in  **
**                  the core (except Predef timer) and also there             **
**                  corresponding status flags.                               **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : CurrentCoreId - Current Core ID                           **
**                  CoreConfigPtr - Pointer to current core configuration     **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : LocalChannel (Gpt_ChannelType)                            **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Gpt_lChannelsInit(const uint32 CurrentCoreId,
                                    Gpt_CoreConfigType const *const CoreConfigPtr)
{
  uint8           Counter;

  /* Initialize the channels allocated to the core */
  /* [cover parentID={010F07FA-C913-4c45-8841-60576367AA93}]
  Initialize the channels allocated to the core
  [/cover] */
  /* [cover parentID={E5437C80-E348-49b0-A806-B92605581B6B}]
  Initialize to Zero
  [/cover] */
  for ( Counter = (uint8)0x0U;
        /* [cover parentID={5F0C3989-D8F2-4844-9C5A-EC93A4F2EA73}]
        Till max channels in core
        [/cover] */
        (Counter < CoreConfigPtr->Gpt_MaxNormalChannels);  Counter++ )
  {

    /* [cover parentID={481A0A6F-1F4F-4f2c-9B48-4A08F2667388}]
    Wake enabled or Notification enabled
    [/cover] */
    #if ((GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) ||   \
         (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
    /* [cover parentID={643E2255-AB24-474c-97BE-909CD166557E}]
    Clear the wakeup and notification flag of the corresponding channel
    [/cover] */
    Gpt_ThreadSafeData[CurrentCoreId]->Gpt_FlagPtr[Counter] = 
                                              (uint8)0x0U;
    #endif
    /* End of ((GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) ||   \
                              (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)) */
    /* [cover parentID={A0E4AADA-779A-4e90-97A8-A9C87C03710D}]
    Initialize Channel and corresponding  status flag
    [/cover] */
    /* [cover parentID={65531120-AA08-429c-BCFD-7E9F7060B06A}]
    GPT12 used
    [/cover] */
    #if (GPT_GPT12_USED == STD_ON)
    /* [cover parentID={20C0550D-972B-411c-84AE-0C5441F682CC}]
    Is channel used GPT12's
    [/cover] */
    if(CoreConfigPtr -> ChannelConfigPtr[Counter].GptGpt12TimerInfo != NULL_PTR)
    {
      /* [cover parentID={89EB9C1F-C96A-4ae3-9894-6CDB95E3B88B}]
      Initialize GPT12 channel
      [/cover] */
      Gpt_lGpt12ChannelInit(&CoreConfigPtr->ChannelConfigPtr[Counter]);
    }
    else
    #endif
    {

      #if (GPT_TOM_USED == STD_ON) || (GPT_ATOM_USED == STD_ON)
      /* [cover parentID={41E6E628-2F78-4928-9C4E-1866C90AFC3A}]
      GTM used
      [/cover] */
      
      /* [cover parentID={ADC016CD-8952-4899-A750-2C99DBA38393}]
      Initialize TOM/ATOM channel
      [/cover] */
      Gpt_lGtmChannelInit(&CoreConfigPtr->ChannelConfigPtr[Counter]);
      #endif
    }
    
    /* Initialize Channel Status Flags */
    Gpt_ThreadSafeData[CurrentCoreId]->Gpt_ChannelStatusPtr[Counter] = 
                                                  GPT_CHANNEL_INITIALIZED;
  } /* End of for ( Counter = (uint8)0x0U;
                                    Counter < GPT_MAX_CHANNELS; Counter++ ) */
  return;
}
/******************************************************************************/

#if (GPT_TOM_USED == STD_ON) || (GPT_ATOM_USED == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={BE826E4C-B39D-4726-8EAE-43736A6BF648}]   **
**                                                                            **
** Syntax         : static void Gpt_lGtmChannelInit                           **
**                        (const Gpt_ChannelConfigType *const GptChannelPtr)  **
**                                                                            **
** Description    : This function initializes the GTM Timers configured.      **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : GptChannelPtr - Pointer to core specific channel config   **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
static void Gpt_lGtmChannelInit
                              (const Gpt_ChannelConfigType *const GptChannelPtr)
{
  const Mcu_17_Gtm_TomAtomChConfigType *LocalGptGtmTimerInfo;
  uint8                                ChannelNumber;
  uint8                                ModuleNumber;

  /* Fetch GptGtmTimerInfo that contains properties of TOM/ATOM channel used */
  LocalGptGtmTimerInfo = GptChannelPtr->GptGtmTimerInfo;

  /* Module Id of the TOM channel */
  ModuleNumber  = (uint8)((LocalGptGtmTimerInfo->TimerId & 
                           GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);

  /* Channel number of the TOM channel */
  ChannelNumber = (uint8)((LocalGptGtmTimerInfo->TimerId &
                           GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);

  /* [cover parentID={4B69C2BC-96FD-4dae-8387-6F59EEADB551}]
  TOM is used
  [/cover] */
  #if (GPT_TOM_USED == STD_ON)

  /* [cover parentID={831ADEDE-B033-4c45-B1AC-4E438FEB16BA}]
  Is the channel a TOM Channel?
  [/cover] */
  if (LocalGptGtmTimerInfo->TimerType == MCU_GTM_TIMER_TOM)
  {
    /* [cover parentID={D4EEEF0C-2224-46c6-A0DA-75C3A6E5489F}]
    Call GTM Library to Initialize TOM channel
    [/cover] */
    Mcu_17_Gtm_TomChannelInit(LocalGptGtmTimerInfo);
    /* [cover parentID={5B86BE44-8270-4051-BE28-3DC94AD56DC7}]
    Force update CM0, CM1 and CRK_SRC registers of the TOM channel
    [/cover] */
    /* Force update CM0, CM1 and CRK_SRC registers of the TOM channel */
    Mcu_17_Gtm_TomChannelShadowTransfer(ModuleNumber, ChannelNumber);
  }
  #endif
  /* End of #if (GPT_TOM_USED == STD_ON) */

  /* [cover parentID={C87F3506-E51F-4057-B423-BB7EBB92E54C}]
  ATOM is used
  [/cover] */
  #if (GPT_ATOM_USED == STD_ON)
  /* [cover parentID={47E32616-4C16-4417-875F-6875703B2A52}]
  Is the channel a ATOM Channel?
  [/cover] */
  if (LocalGptGtmTimerInfo->TimerType == MCU_GTM_TIMER_ATOM)
  {
    /* [cover parentID={F2068902-B95B-496a-8AF8-E61A34CAE6FC}]
    Call GTM Library to Initialize ATOM channel
    [/cover] */
    Mcu_17_Gtm_AtomChannelInit(LocalGptGtmTimerInfo);
    /* [cover parentID={FB84CDED-147C-420b-BD38-85E45D83AA5F}]
    Force update CM0, CM1 and CRK_SRC registers of the ATOM channel
    [/cover] */
    /* Force update CM0, CM1 and CRK_SRC registers of the ATOM channel */
    Mcu_17_Gtm_AtomChannelShadowTransfer(ModuleNumber, ChannelNumber);
  }
  #endif
  /* End of #if (GPT_ATOM_USED == STD_ON) */

  return;
}/* End of Gpt_lGtmChannelInit */
#endif

/******************************************************************************/

#if (GPT_GPT12_USED == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={14398227-9585-4d75-A7AB-492D7852718F}]   **
**                                                                            **
** Syntax         : static void Gpt_lGpt12ChannelInit                         **
**                        (const Gpt_ChannelConfigType *const GptChannelPtr)  **
**                                                                            **
** Description    : This function initializes the GPT12 Timers configured.    **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : GptChannelPtr - Pointer to core specific channel config   **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
static void Gpt_lGpt12ChannelInit
                              (const Gpt_ChannelConfigType *const GptChannelPtr)
{
  
  Mcu_17_Gpt12_TimerChIdentifierType LocalGpt12TimerId0 = GptChannelPtr->GptGpt12TimerInfo[0].TimerId;
  
  /* [cover parentID={05BF13B3-AB45-4499-9648-5A4C27291FE6}]
  Initialize the first timer
  [/cover] */
  Mcu_17_Gpt12_TimerInit(&GptChannelPtr->GptGpt12TimerInfo[0]);
  
  /* [cover parentID={C53AD488-39D8-4c9e-B859-F73FDDB23607}]
  If mode is continous and first timer is T3
  [/cover] */
  if((GptChannelPtr->GptChannelMode == GPT_MODE_CONTINUOUS) && 
    (LocalGpt12TimerId0 == MCU_GPT12_TIMER3))
  {
    /* [cover parentID={54B1F790-6174-4de6-9199-45F904AB48E5}]
    Initialize the second timer
    [/cover] */
    Mcu_17_Gpt12_TimerInit(&GptChannelPtr->GptGpt12TimerInfo[1]); 
    
  }
  
  return;
}/* End of Gpt_lGpt12ChannelInit */
#endif

/******************************************************************************/

#if ( (GPT_DEINIT_API == STD_ON) && \
    ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_RUNTIME_ERROR_DETECT == STD_ON)||\
    (GPT_DEV_ERROR_DETECT == STD_ON)) )
/* CYCLOMATIC_Gpt_lDeInitDetCheck_JUSTIFICATION: This API provides various
   error checks with different combinations which is always needed */
/*******************************************************************************
** Traceability   : [cover parentID={8B7B748F-4DA4-4e2b-8FCB-EE92B4EB29E0}]   **
**                                                                            **
** Syntax         : static uint32 Gpt_lDeInitDetCheck                         **
**                                              (const uint32 CurrentCoreId)  **
**                                                                            **
** Description    : This function checks DET errors in Gpt_DeInit Function in **
**                  context to the core                                       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : CurrentCoreId           - Current Core ID                 **
**                  CurrentCoreDriverState  - Status of the driver            **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : IErrVal (uint32)                                          **
**                                                                            **
*******************************************************************************/
static uint32 Gpt_lDeInitDetCheck(const uint32 CurrentCoreId)
{
  
  uint32                    IErrVal = GPT_E_DET_NO_ERR;
  /* [cover parentID={07125B2F-5B73-4fa0-8633-1B21D912E90A}]
  If safety or DET is ON
  [/cover] */
  #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
  uint32                    CurrentCoreDriverState;
  /* Read the state of the driver in current core */
  CurrentCoreDriverState = 
                           Mcal_GetBitAtomic(Gpt_DriverStatus, GPT_CORE_BITPOS(CurrentCoreId), 
                               GPT_CORE_STATUS_LEN);
  /* [cover parentID={62554CC6-1279-43b3-98FD-E894B4154BA4}]
  Is Multicore Error reporting enabled?
  [/cover] */

  #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_MULTICORE_ERROR_DETECT == STD_ON))
  /* [cover parentID={1481F3BE-9AD8-4aa5-8A84-33867B0D7D41}]
  Check multicore related DETs and update error flag
  [/cover] */
  IErrVal = Gpt_lMulCoreDeInitDetCheck(CurrentCoreId, CurrentCoreDriverState);
  /* [cover parentID={BBBD05C9-6BE5-4817-8B0A-B2B4763EAB61}]
  Any errors reported?
  [/cover] */
  if (GPT_E_DET_ERR != IErrVal)
  #endif
  /*End of #if (GPT_MULTICORE_ERROR_DETECT == STD_ON)*/
  
  {
    /* [cover parentID={34C8C3E8-53FC-4784-9AFE-721160530364}]
    Is driver initialised in the current core?
    [/cover] */
    if (GPT_DRIVER_INITIALIZED != CurrentCoreDriverState)
    {
      /* [cover parentID={5D9155A9-0212-42df-A115-89C9723032EF}]
      Report DET
      [/cover] */
      Gpt_lReportError(GPT_SID_DEINIT, GPT_E_UNINIT);

      /* Set IErrVal */
      IErrVal = GPT_E_DET_ERR;
    }
    else
  #endif
  /*End of #if ((GPT_SAFETY_ENABLE == STD_ON)||
                  (GPT_DEV_ERROR_DETECT == STD_ON))*/
    
    {
    /* [cover parentID={CA9802C9-1B71-4b8f-9012-3F79699EC2C8}]
    If safety or runtime error enabled, or det and AS422 version enabled 
    [/cover] */
    #if( (GPT_SAFETY_ENABLE == STD_ON) || (GPT_RUNTIME_ERROR_DETECT == STD_ON)||\
       ((MCAL_AR_VERSION == MCAL_AR_422) && (GPT_DEV_ERROR_DETECT == STD_ON)) )
       
      uint8                     Counter;
      
      /* Get the pointer to current core configuration */
      const Gpt_CoreConfigType *LocalCoreConfigPtr = GPT_GET_CORECONFIGPTR(CurrentCoreId);

      for ( Counter = (uint8)0x0U;
            /* [cover parentID={47A21DCB-53F1-4a75-959E-DEB95FA14B4F}]
            Till max normal channels in the core
            [/cover] */
            (Counter < LocalCoreConfigPtr->Gpt_MaxNormalChannels) && 
            (IErrVal != GPT_E_DET_ERR); Counter++ )
      {
        /* [cover parentID={DD5E5053-2684-433f-AEBB-CC4D8719E6DA}]
        Check any channel running in the core
        [/cover] */
        /* [cover parentID={F17F024B-EDA5-486d-9922-BEB1B962F224}]
        Is channel running?
        [/cover] */
        if (GPT_CHANNEL_RUNNING == 
            Gpt_ThreadSafeData[CurrentCoreId]->Gpt_ChannelStatusPtr[Counter])
        {
          IErrVal = GPT_E_DET_ERR;
        }
      }

      /* [cover parentID={A19AEE97-C406-4841-8F28-539B60CFD07F}]
      Is error flag set?
      [/cover] */
      /* Error Flag set */
      if (IErrVal == GPT_E_DET_ERR)
      {
        /* [cover parentID={A4B75DF9-45D3-4410-A059-FF4F8D9EB6F0}]
        Report DET
        [/cover] */        /* Report to  DET */
        Gpt_lReportRuntimeDetError(GPT_SID_DEINIT, GPT_E_BUSY);
      }
    #endif
    /* End of #if( (GPT_SAFETY_ENABLE == STD_ON) || 
    (GPT_RUNTIME_ERROR_DETECT == STD_ON)||\
    ((MCAL_AR_VERSION == MCAL_AR_422) && (GPT_DEV_ERROR_DETECT == STD_ON)) )*/
       
    }
  #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON)) 
  }
  #endif
  return IErrVal;
} /* End of Gpt_lDeInitDetCheck */
/******************************************************************************/
#endif
/* End of #if ((GPT_DEINIT_API == STD_ON) && \
                ((GPT_SAFETY_ENABLE == STD_ON) || \
                                           (GPT_DEV_ERROR_DETECT == STD_ON))) */

#if ((GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) && \
    ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON)))
/*******************************************************************************
** Traceability   : [cover parentID={A2B88C2A-3266-4e30-BD48-C02055BD6347}]   **
**                                                                            **
** Syntax         : static uint32 Gpt_lWakeupDetCheck                         **
**                                          (                                 **
**                                            const Gpt_ChannelType Channel,  **
**                                            const uint8 Gpt_Sid,            **
**                                            const uint32 CurrentCoreId      **
**                                          )                                 **
**                                                                            **
** Description    : This function checks DET errors in Gpt_EnableWakeup and   **
**                  Gpt_DisableWakeup API's                                   **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : Channel       - Channel ID                                **
**                  Gpt_Sid       - Service id of the caller API              **
**                  CurrentCoreId - Current Core ID                           **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : IErrVal (uint32)                                          **
**                                                                            **
*******************************************************************************/
static uint32 Gpt_lWakeupDetCheck (
                                    const Gpt_ChannelType Channel,
                                    const uint8 Gpt_Sid,
                                    const uint32 CurrentCoreId
                                  )
{
  const Gpt_CoreConfigType *LocalCoreConfigPtr;
  uint32                   IErrVal = GPT_E_DET_NO_ERR;
  Gpt_ChannelType          LocalChannel;
  /* [cover parentID={1E669736-3551-4cab-BFE6-D8FFAC50C1FB}]
  Check for DETs
  [/cover] */

  /* [cover parentID={A28E1326-31F0-430b-8985-DD9D7C6832DA}]
  Check if driver was initialised from the current core
  [/cover] */
  /* Check if driver was initialized from the current core */
  if (GPT_DRIVER_INITIALIZED != 
          Mcal_GetBitAtomic(Gpt_DriverStatus, GPT_CORE_BITPOS(CurrentCoreId), 
                                                           GPT_CORE_STATUS_LEN))
  {
    /* [cover parentID={AAC1A1D4-660D-4acc-B037-98A31D65144C}]
    Report DET
    [/cover] */
    /* Report to DET */
    Gpt_lReportError(Gpt_Sid, GPT_E_UNINIT);

    IErrVal = GPT_E_DET_ERR;
  }
  /* [cover parentID={1F9805F1-2B34-49fe-81C3-7251DB60E56D}]
  Check if 'Channel' within valid range
  [/cover] */
  else if ( Channel >= GPT_MAX_CHANNELS )
  {
    /* [cover parentID={888F6DE8-9C8B-4224-BD70-61DF352E1DD4}]
    Report DET
    [/cover] */
    /* Report DET */
    Gpt_lReportError(Gpt_Sid, GPT_E_PARAM_CHANNEL);

    IErrVal = GPT_E_DET_ERR;
  }
  /* [cover parentID={F8B00BDA-6B69-4ed4-AC31-28BA3C7F9946}]
  Otherwise
  [/cover] */
  else
  {
    
    #if ((GPT_SAFETY_ENABLE == STD_ON) || \
         (GPT_MULTICORE_ERROR_DETECT == STD_ON))
    /* [cover parentID={E618C9F4-87E3-4080-985A-9A948A369937}]
    Multi Core or Single Core
    [/cover] */
    /* [cover parentID={1308D127-759F-4500-86BA-294F485AE862}]
    Is Multi Core with multicore DET Reporting enabled
                      OR Safety Error Reporting enabled?
    [/cover] */
    /* Check is the channel present in current core */
    /* [cover parentID={15A9222F-422E-46a3-A962-15445CE99996}]
    Check for Multi Core related DETs and set error flag accordingly
    [/cover] */
    IErrVal = Gpt_lMulCoreChannelDetCheck(CurrentCoreId, Channel, Gpt_Sid);
    #endif
  }


  /* [cover parentID={B2DA8EC0-77B7-413c-8EB8-EAE6E6E119AD}]
  Are there any errors?
  [/cover] */
  if (IErrVal != GPT_E_DET_ERR)
  {
    /* Get the pointer to current core configuration */
    LocalCoreConfigPtr = GPT_GET_CORECONFIGPTR(CurrentCoreId);

    /* [cover parentID={337B3FD5-0B1A-4c90-B0EB-BC443E3A2D59}]
    MultiCore
    [/cover] */
    #if (GPT_MAX_CORE_USED > 1U)
    /* [cover parentID={D050AEA2-6984-4c0f-BB9D-8967F67F9A2B}]
    Fetch the channel index relative to the core
    [/cover] */
    LocalChannel = Gpt_lMulCoreGetChannelInfo(CurrentCoreId, Channel);
    /* [cover parentID={A6F24E35-5AC8-40dd-BB37-496FD14AFB91}]
    Single Core
    [/cover] */
    #else
    /* [cover parentID={FF8DC3C7-4959-4687-B1EF-64600240F8AB}]
    Use the channel as is, no indexing required
    [/cover] */
    LocalChannel = Channel;
    #endif

    /* [cover parentID={8A0F6CEF-69DE-4ea2-816E-1EF2CDF2757E}]
    Is channel is capable of wakeup?
    [/cover] */
    /* Check if Channel is not wakeup capable */
    if ((&LocalCoreConfigPtr->ChannelConfigPtr[LocalChannel])-> 
        GptEnableWakeupState == (boolean)FALSE)
    {
      /* [cover parentID={2B6BBE1E-05CC-40c7-A9DF-61EC927E6752}]
      Report to Det
      [/cover] */
      /* Report to DET */
      Gpt_lReportError(Gpt_Sid, GPT_E_PARAM_CHANNEL);

      IErrVal = GPT_E_DET_ERR;
    }
    else
    {
      /* No Action Required */
    }
  }

  return IErrVal;
}/* End of Gpt_lWakeupDetCheck */
/******************************************************************************/
#endif
/* End of #if ((GPT_WAKEUP_FUNCTIONALITY_API == STD_ON ) && \
                                    ((GPT_SAFETY_ENABLE == STD_ON) || \
                                            (GPT_DEV_ERROR_DETECT == STD_ON)) */

#if ((GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON) || \
     (GPT_PREDEF_TIMER_1US_16BIT_EN == STD_ON)   || \
     (GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON)   || \
     (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))
/*******************************************************************************
** Traceability   : [cover parentID={58C0E237-A7C4-45e9-82D9-A2F523A67E1E}]   **
**                                                                            **
** Syntax         : LOCAL_INLINE boolean Gpt_lCheckPredefTimer                **
**                                (                                           **
**                                  const Gpt_PredefTimerType PredefTimer,    **
**                                  const uint32 CurrentCoreId                **
**                                )                                           **
**                                                                            **
** Description    : This function checks is the PredefTimer passed is valid   **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : PredefTimer   - GPT Predef Timer                          **
**                  CurrentCoreId - Current Core ID                           **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : IErrVal (uint32)                                          **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Gpt_lCheckPredefTimer
(
  const Gpt_PredefTimerType PredefTimer, 
  const uint32 CurrentCoreId
)
{
  const Gpt_CoreConfigType                    *LocalCoreConfigPtr;

  #if ((GPT_PREDEF_TIMER_1US_16BIT_EN == STD_ON)    || \
       (GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON)    || \
       (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))
  const Gpt_1UsPredefTimerChannelConfigType   *LocalGptPredefChannel1usPtr;
  #endif

  #if (GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON)
  const Gpt_100UsPredefTimerChannelConfigType *LocalGptPredefChannel100usPtr;
  #endif

  uint32 IErrVal;

  /* Get pointer to current core configuration */
  LocalCoreConfigPtr = GPT_GET_CORECONFIGPTR(CurrentCoreId);
  /* [cover parentID={D85DA72F-E037-4fe2-BB50-8FD7195A59CC}]
  Predef Timer 1us ON
  [/cover] */
  #if ((GPT_PREDEF_TIMER_1US_16BIT_EN == STD_ON)    || \
       (GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON)    || \
       (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))
  LocalGptPredefChannel1usPtr = LocalCoreConfigPtr->Predef1UsChannelConfigPtr;
  /* [cover parentID={7E81C875-0B73-42bc-BA0E-688385E79DD7}]
  Is PredefTimer of type 1us Predef Timer?
  [/cover] */
  if ((PredefTimer == LocalGptPredefChannel1usPtr->Gpt1UsPredefTimerUsed0) ||
      (PredefTimer == LocalGptPredefChannel1usPtr->Gpt1UsPredefTimerUsed1) ||
      (PredefTimer == LocalGptPredefChannel1usPtr->Gpt1UsPredefTimerUsed2))
  {
    /* [cover parentID={86AE1FA5-1F81-4ccb-9BED-ACFE2E5B2AD5}]
  Clear error flag
  [/cover] */
  IErrVal = GPT_E_DET_NO_ERR;
  }
  else
  #endif
  {
    /* [cover parentID={7B89877B-829B-41e4-B7D9-68B1B67031BF}]
    Predef Timer 100us ON
    [/cover] */
    #if (GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON)
    LocalGptPredefChannel100usPtr = 
                                LocalCoreConfigPtr->Predef100UsChannelConfigPtr;

    /* [cover parentID={5E6FB0A7-54A5-4aad-A0CA-F3D89554289B}]
    Is PredefTimer of type 100us Predef Timer?
    [/cover] */
    if (PredefTimer == LocalGptPredefChannel100usPtr->Gpt100UsPredefTimerUsed0)
    {
      /* [cover parentID={2A71C16E-5805-4562-8A9E-35C200C66D2B}]
      Clear error flag
      [/cover] */
      IErrVal = GPT_E_DET_NO_ERR;
    }
    else
    #endif
    {
      /* [cover parentID={FFC78E5B-8681-4b88-8CC0-0AF6C7240D00}]
      DET or Safety in ON
      [/cover] */
      #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
      /* [cover parentID={1CCD9E00-D1AC-42c2-838D-726462C79169}]
      Report to DET
      [/cover] */
      Gpt_lReportError(GPT_SID_GET_PREDEFTIMERVALUE, GPT_E_PARAM_PREDEF_TIMER);
      #endif

      /* [cover parentID={BE1EC10C-E574-45bf-89DA-1596B418370B}]
      Set error flag
      [/cover] */
      IErrVal = GPT_E_DET_ERR; /* Set Error Flag */
    }
  }

  return IErrVal;
}
/******************************************************************************/

/* CYCLOMATIC_Gpt_lGetPredefErrCheck_JUSTIFICATION: This API provides various
   error checks with different combinations which is always needed */
/*******************************************************************************
** Traceability   : [cover parentID={5E2597AE-B95D-4e96-AF1C-2C0987C68E42}]   **
**                                                                            **
** Syntax         : static uint32 Gpt_lGetPredefErrCheck                      **
**                                  (                                         **
**                                    const Gpt_PredefTimerType PredefTimer,  **
**                                    const uint32 *const TimeValuePtr,       **
**                                    const uint32 CurrentCoreId              **
**                                  )                                         **
**                                                                            **
** Description    : This function checks possible errors for                  **
**                  Gpt_GetPredefTimerValue()                                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : PredefTimer     - GPT Predef Timer                        **
**                  TimeValuePtr    - Pointer to destination data in RAM      **
**                  CurrentCoreId   - Current Core ID                         **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : IErrVal (uint32)                                          **
**                                                                            **
*******************************************************************************/
static uint32 Gpt_lGetPredefErrCheck  (
                                        const Gpt_PredefTimerType PredefTimer,
                                        const uint32 *const TimeValuePtr,
                                        const uint32 CurrentCoreId
                                      )
{
  uint32 IErrVal = GPT_E_DET_NO_ERR;

  /* [cover parentID={F4CDBE52-164D-4b57-BB46-6EE67793EDCE}]
  Check for DET errors
  [/cover] */

  /* [cover parentID={01C09404-3242-4ab9-83C8-BA3448ED8FA4}]
  Driver is not initialised from the current core
  [/cover] */
  /* Check if driver was initialized from the current core */
  if (GPT_DRIVER_INITIALIZED != 
      Mcal_GetBitAtomic(Gpt_DriverStatus, GPT_CORE_BITPOS(CurrentCoreId), 
                        GPT_CORE_STATUS_LEN))
  {
    /* [cover parentID={F4CDBE52-164D-4b57-BB46-6EE67793EDCE}]
    Check for DET errors
    [/cover] */
    #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
    /* [cover parentID={805949D9-A814-48b0-8702-8C627EE2D931}]
    Report DET
    [/cover] */
    Gpt_lReportError(GPT_SID_GET_PREDEFTIMERVALUE, GPT_E_UNINIT);
    #endif

    IErrVal = GPT_E_DET_ERR; /* Set Error Flag */
  }
  /* [cover parentID={68A0E065-9A1C-4a40-8883-C40DBDC1568F}]
  Driver is in wrong mode in current core
  [/cover] */
  /* Check if the driver is in wrong mode in current core */
  else if (GPT_MODE_SLEEP == 
           Gpt_ThreadSafeData[CurrentCoreId]->Gpt_DriverMode )
  {
    
    #if( (GPT_SAFETY_ENABLE == STD_ON) || (GPT_RUNTIME_ERROR_DETECT == STD_ON)||\
       ((MCAL_AR_VERSION == MCAL_AR_422) && (GPT_DEV_ERROR_DETECT == STD_ON)) )
    /* [cover parentID={6BA3A72B-EEAE-43b8-9297-F249FBF8D122}]
    Report errors
    [/cover] */
    Gpt_lReportRuntimeDetError(GPT_SID_GET_PREDEFTIMERVALUE, GPT_E_MODE);
    #endif

    IErrVal = GPT_E_DET_ERR; /* Set Error Flag */
  }

  /* [cover parentID={876B2E6B-8B3D-4554-B9D7-07A719B7566C}]
  The parameter TimeValuePtr is a null pointer
  [/cover] */
  else if (TimeValuePtr == NULL_PTR)
  {
    #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
    /* [cover parentID={F3E8E761-6B50-4717-B719-2C9FD1D298E1}]
    Report to DET
    [/cover] */
    Gpt_lReportError(GPT_SID_GET_PREDEFTIMERVALUE, GPT_E_PARAM_POINTER);
    #endif

    IErrVal = GPT_E_DET_ERR; /* Set Error Flag */
  }
  /* [cover parentID={A6976FAE-ED62-427b-94FB-8E18D658D0A3}]
  Otherwise
  [/cover] */
  /* Check if the parameter PredefTimer is valid */
  else
  {
      /* [cover parentID={5A4901EB-CDCE-43ec-8BCA-DF82D2EB3719}]
      Is the parameter PredefTimer is valid
      [/cover] */
      IErrVal = Gpt_lCheckPredefTimer(PredefTimer, CurrentCoreId);
  }

  /* [cover parentID={9CC9F43B-2819-4e1b-BB45-8B637DE36690}]
  Predef Timer (16/24/32Bit) is enabled
  [/cover] */
  #if ((GPT_PREDEF_TIMER_1US_16BIT_EN == STD_ON)    || \
       (GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON)    || \
       (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))
  /* [cover parentID={2B9E845A-3832-48bd-B10C-267C564536C6}]
  Are there any errors?
  [/cover] */
  if (IErrVal != GPT_E_DET_ERR)
  {
    /* Check if the GPT Predef Timer passed by the parameter PredefTimer
    is not enabled */
  /* [cover parentID={90638A2E-BFA7-4538-AF5A-2BBEC5978E0B}]
  Is the Predef Timer passed enabled?
  [/cover] */
    if (GPT_CHANNEL_RUNNING != GPT_GET_1US_PREDEF_TIMER_STS())
    {
      #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
      /* Report to DET */
      /* [cover parentID={2F5BC676-C276-4e64-94E7-326BA2419B53}]
      Report to DET
      [/cover] */
      Gpt_lReportError(GPT_SID_GET_PREDEFTIMERVALUE, GPT_E_PARAM_PREDEF_TIMER);
      #endif
      IErrVal = GPT_E_DET_ERR; /* Set Error Flag */
    }
  }
  #endif
  /* End of #if ((GPT_PREDEF_TIMER_1US_16BIT_EN == STD_ON)  || \
                 (GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON)  || \
                 (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON)) */

  /* [cover parentID={2B43D96F-B738-4fc5-8CA2-F3178437A0B7}]
  100us Predef Timer is enabled
  [/cover] */
  #if (GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON)
  /* [cover parentID={D4385A77-1581-47f4-8E41-4639E405AFCD}]
  Are there any errors?
  [/cover] */
  if (IErrVal != GPT_E_DET_ERR)
  {
    /* Check if the GPT Predef Timer passed by the parameter PredefTimer
    is not enabled */
    /* [cover parentID={90F61C52-2BF7-4cc6-87BA-83B7823F16AD}]
    Is the Predef Timer passed enabled?
    [/cover] */
    if (GPT_CHANNEL_RUNNING != GPT_GET_100US_PREDEF_TIMER_STS())
    {
      #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
      /* [cover parentID={9B82EE2F-1D74-4e31-8155-907EBECA34CE}]
      Report to DET
      [/cover] */
      Gpt_lReportError(GPT_SID_GET_PREDEFTIMERVALUE, GPT_E_PARAM_PREDEF_TIMER);
      #endif
      IErrVal = GPT_E_DET_ERR; /* Set Error Flag */
    }
  }
  #endif
  /* End of #if (GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON) */

  return IErrVal;
} /* End of Gpt_lGetPredefErrCheck */
/******************************************************************************/
#endif
/* End of #if (((GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON) || \
               (GPT_PREDEF_TIMER_1US_16BIT_EN == STD_ON)    || \
               (GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON)    || \
               (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))   && \
               ((GPT_SAFETY_ENABLE == STD_ON)               || \
               (GPT_DEV_ERROR_DETECT == STD_ON)))           */

#if (GPT_TOM_USED == STD_ON) || (GPT_ATOM_USED == STD_ON)               
#if ((GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) ||    \
     (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON))
/*******************************************************************************
** Traceability   : [cover parentID={5F36A3EE-ABA9-49f4-8CE1-619527210A7B}]   **
**                                                                            **
** Syntax         : static void Gpt_lGtmIrqModify                             **
**                       (                                                    **
**                          const Gpt_ChannelConfigType *const GptChannelPtr, **
**                          const uint8 InterruptFlag                         **
**                       )                                                    **
**                                                                            **
** Description    : This function Enables/Disables CCU0/CCU1 Interrupt        **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : GptChannelPtr - Pointer to core specific channel config   **
**                  InterruptFlag - Interrupt bits to set/reset               **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
static void Gpt_lGtmIrqModify
                            (
                              const Gpt_ChannelConfigType *const GptChannelPtr,
                              const uint8 InterruptFlag
                            )
{
  const Mcu_17_Gtm_TomAtomChConfigType *LocalGptGtmTimerInfo;

  #if (GPT_TOM_USED == STD_ON)
  Ifx_GTM_TOM_CH *TomChannelRegPtr; /* Ptr to TOM Channel Register */
  #endif

  #if (GPT_ATOM_USED == STD_ON)
  Ifx_GTM_ATOM_CH *AtomChannelRegPtr; /* Ptr to ATOM Channel Register  */
  #endif

  uint8 ModuleNumber;                        /* Holds the module number  */
  uint8 ChannelNumber;                       /* Holds the channel number */

  /* The GptGtmTimerInfo contains properties of TOM/ATOM channel used */
  LocalGptGtmTimerInfo = GptChannelPtr->GptGtmTimerInfo;

  ModuleNumber = (uint8)((LocalGptGtmTimerInfo->TimerId & 
                          GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);

  ChannelNumber = (uint8)((LocalGptGtmTimerInfo->TimerId &
                           GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);

  /* [cover parentID={30538A06-D829-470f-986B-5FA6602AA124}]
  TOM is used
  [/cover] */
  #if (GPT_TOM_USED == STD_ON)
  /* [cover parentID={DC9DE34E-EF9E-4e2f-8059-9E673D26ACBB}]
  Is the channel a TOM channel?
  [/cover] */
  if (LocalGptGtmTimerInfo->TimerType == MCU_GTM_TIMER_TOM)
  {
    /* MISRA2012_RULE_11_3_JUSTIFICATION: Pointer type recasting done
       for ease of access to channels registers.*/
    /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and
       integer type. Permitted for special function registers.*/
    /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
       by violating this MISRA rule.*/
    /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic used due to
       PBConfigStructure and is within allowed range.*/
    TomChannelRegPtr = GTM_TOM_CH_POINTER(ModuleNumber, ChannelNumber);
    /* [cover parentID={54BF12D5-0823-4b98-82C9-FAA8F89A8930}]
    Set or clear  the CCU0 Trigger Condition
    [/cover] */
    /* Clear all Pending Interrupts */
    /* Interrupts are disabled before clearing the notify bits so that any
    interruption after clearing the notify doesn't set the notify bits again */
    TomChannelRegPtr->IRQ.EN.U = (uint32)0x0U;
    TomChannelRegPtr->IRQ.NOTIFY.U = GPT_CLEAR_INTERRUPTS;
    TomChannelRegPtr->IRQ.EN.U = InterruptFlag & (uint32)0x03;
  }
  #endif
  /* End of #if (GPT_TOM_USED == STD_ON)   */

  /* [cover parentID={0A501CF2-42E9-4460-AF56-0FF499CDE782}]
  ATOM is used
  [/cover] */
  #if (GPT_ATOM_USED == STD_ON)
  /* [cover parentID={CB80FE39-0C59-493d-8DC7-4F0E5CCB92E4}]
  Is the channel a ATOM channel?
  [/cover] */
  if (LocalGptGtmTimerInfo->TimerType == MCU_GTM_TIMER_ATOM)
  {
    /* MISRA2012_RULE_11_3_JUSTIFICATION: Pointer type recasting done
       for ease of access to channels registers.*/
    /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and
       integer type. Permitted for special function registers.*/
    /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
       by violating this MISRA rule.*/
    /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic used due to
       PBConfigStructure and is within allowed range.*/
    AtomChannelRegPtr = GTM_ATOM_CH_POINTER(ModuleNumber, ChannelNumber);
    /* [cover parentID={4B750E8D-D67B-4831-9292-CBA757B2C2BD}]
    Set or clear  the CCU0 Trigger Condition
    [/cover] */
    /* Clear all Pending Interrupts */
    /* Interrupts are disabled before clearing the notify bits so that any
    interruption after clearing the notify doesn't set the notify bits again*/
    AtomChannelRegPtr->IRQ.EN.U = (uint32)0x0U;
    AtomChannelRegPtr->IRQ.NOTIFY.U = GPT_CLEAR_INTERRUPTS;
    AtomChannelRegPtr->IRQ.EN.U = InterruptFlag & (uint32)0x03;
  }
  #endif
  /* End of #if (GPT_ATOM_USED == STD_ON)   */

  return;
}/* End of Gpt_lGtmIrqModify */
/******************************************************************************/
#endif
/* End of #if ((GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) ||    \
                            (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)) */
#endif

/*******************************************************************************
** Traceability   : [cover parentID={952FD2AB-4BF0-4171-AA50-EB95F25FDA68}]   **
**                                                                            **
** Syntax         : LOCAL_INLINE boolean Gpt_lCheckTimeOutVaue                **
                              (const uint32 TimeOutVal, const uint32 MaxVal)  **
**                                                                            **
** Description    : This function validates the timeout value is within the   **
**                  allowed range or not                                      **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : TimeOutVal    - Timeout value to which the GPT timer has  **
**                                  to count                                  **
**                  MaxVal        - Maximum value that is valid               **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : True/False                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE boolean Gpt_lCheckTimeOutVaue
                                (const uint32 TimeOutVal, const uint32 MaxVal)
{
  boolean result = FALSE;

  /* Check is time out value within the allowed range */
  if ((TimeOutVal <= MaxVal) && (TimeOutVal > 0x0U))
  {
    result = TRUE;
  }

  return result;
}
/******************************************************************************/

#if (GPT_TOM_USED == STD_ON) || (GPT_ATOM_USED == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={5AB7712E-E0B9-4687-AA53-048C0C8ED93D}]   **
**                                                                            **
** Syntax         : static void Gpt_lGtmStartTimer                            **
**                                           (                                **
**                                             const Gpt_ChannelType Channel, **
**                                             const uint32 TimeOutVal,       **
**                                             const uint32 CurrentCoreId     **
**                                           )                                **
**                                                                            **
** Description    : This function starts the GPT timer to count               **
**                  until TimeOutVal.                                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant for different timer channel                     **
**                                                                            **
** Parameters(in) : Channel       - Channel ID                                **
**                  TimeOutVal    - Timeout value to which the GPT timer has  **
**                                  to count                                  **
**                  CurrentCoreId - Current Core ID                           **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
static void Gpt_lGtmStartTimer  (
                                  const Gpt_ChannelType Channel,
                                  const uint32 TimeOutVal,
                                  const uint32 CurrentCoreId
                                )
{
  const Mcu_17_Gtm_TomAtomChConfigType *LocalGptGtmTimerInfo;

  #if (GPT_TOM_USED == STD_ON)
  Ifx_GTM_TOM_CH *TomChannelRegPtr;   /* Ptr to TOM Channel Register */
  #endif

  #if (GPT_ATOM_USED == STD_ON)
  Ifx_GTM_ATOM_CH *AtomChannelRegPtr; /* Ptr to ATOM Channel Register */
  #endif

  #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
  uint32 IDetVal;
  #endif

  uint8 ChannelNumber;                     /* Holds the channel number     */
  uint8 ModuleNumber;                      /* Holds the module number      */


  /* [cover parentID={E8D2C0E0-95B0-4eac-B295-4993DF066933}]
  Safety enable or DET is On
  [/cover] */
  #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
  IDetVal = (uint32)GTM_GPT_WRONG_PARAM;
  #endif

  /* Get pointer to channel configuration */
  LocalGptGtmTimerInfo = &GPT_GET_GTMTIMERINFO(CurrentCoreId, Channel);

  ModuleNumber  = (uint8)((LocalGptGtmTimerInfo->TimerId &
                           GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);

  ChannelNumber = (uint8)((LocalGptGtmTimerInfo->TimerId &
                           GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);

  /* [cover parentID={1E4911FF-C6C8-4043-A05B-8FAA01EF79F0}]
  TOM is used
  [/cover] */
  #if (GPT_TOM_USED == STD_ON)
  /* [cover parentID={E91FE033-1BE3-4ec1-A357-D3D7EF0CC0F2}]
  Configure and Start the TOM channel
  [/cover] */

  /* [cover parentID={77818AE7-13A8-4b26-94FB-DBFD15644B7C}]
   Is it a TOM channel?
   [/cover] */
  if (LocalGptGtmTimerInfo->TimerType == MCU_GTM_TIMER_TOM)
  {
    /* [cover parentID={B3DC983E-EA47-4318-9367-D0BE481AB2A9}]
    Is target value within range?
    [/cover] */
    if (Gpt_lCheckTimeOutVaue(TimeOutVal, GPT_GTM_TOM_TIMER_MAX) == TRUE)
    {
      /* MISRA2012_RULE_11_3_JUSTIFICATION: Pointer type recasting done
        for ease of access to channels registers.*/
      /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and
        integer type. Permitted for special function registers.*/
      /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
        by violating this MISRA rule.*/
      /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic used due to
        PBConfigStructure and is within allowed range.*/
      TomChannelRegPtr = GTM_TOM_CH_POINTER(ModuleNumber, ChannelNumber);
     
      /* [cover parentID={1FD3F172-E94B-4bab-86E5-4CB46AE749F1}]
      Clear CN0 Set CM0 and SR0 with the Timeout value
      [/cover] */
      TomChannelRegPtr->CN0.U = (uint8)0x0U; /* Clear CN0 register */

      /* Set CM0 with the Timeout value */
      TomChannelRegPtr->CM0.U = TimeOutVal;

      /* Set Shadow register also with same TimeOut Value, this is a safety
      measure to avoid unintended update from shadow registers */
      TomChannelRegPtr->SR0.U = TimeOutVal;
      
      /* Clear Notify */
      TomChannelRegPtr->IRQ.NOTIFY.U = GPT_CLEAR_INTERRUPTS;
        

      /* [cover parentID={2337A00F-397D-435e-9D80-B391AB519AFB}]
      Safety enable or DET is On
      [/cover] */
      #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
      /* [cover parentID={419BCD61-DED4-48b4-A816-0A9C6BC8F901}]
      Set status variable to "Running"
      [/cover] */
      IDetVal = (uint32)GTM_GPT_CHANNEL_RUNNING;
      #endif
      
      /* [cover parentID={1469F13B-AA9D-4fc2-B37C-10FA6137E330}]
      Start of critical section
      [/cover] */
      SchM_Enter_Gpt_GtmStartTimer();
      
      /* [cover parentID={8370261C-EF07-4aaa-A413-1E6B9CB12F48}]
      Start the timer channel with TimerOutputEn=0, as its not required to
      enable the output mode
      [/cover] */
      /* Call the library function to start the timer channel.
        with TimerOutputEn=0, as its not required to enable the output mode.*/
      Mcu_17_Gtm_TomChannelEnable(ModuleNumber, ChannelNumber, 0x0U);
      /* [cover parentID={834374EF-877B-4f3b-B8E2-CEDE9B10A9ED}]
      Clear CN0 and set channel status to 'Running'
      [/cover] */
      TomChannelRegPtr->CN0.U = (uint8)0x0U; /* Clear CN0 register */
      Gpt_ThreadSafeData[CurrentCoreId]->Gpt_ChannelStatusPtr[Channel] =
                                                        GPT_CHANNEL_RUNNING;
                                                        
      /* [cover parentID={6C7A76A4-04C6-43a1-984A-8A69F5225388}]
      End of critical section
      [/cover] */                                                  
      SchM_Exit_Gpt_GtmStartTimer(); 
    }
  }
  #endif
  /* End of #if (GPT_TOM_USED == STD_ON)   */

  /* [cover parentID={AB0F4ADF-6934-4a51-AE0B-2B7B581D2CCB}]
  ATOM is used
  [/cover] */
  #if (GPT_ATOM_USED == STD_ON)
  /* [cover parentID={2A8B908F-D84B-4d68-A1C9-4D825B646AF7}]
  Configure and Start the ATOM channel
  [/cover] */

  /* [cover parentID={C3CA5245-D397-43b7-8ECA-8485D3172DA2}]
  Is it an ATOM  channel?
  [/cover] */
  if (LocalGptGtmTimerInfo->TimerType == MCU_GTM_TIMER_ATOM)
  {
    /* [cover parentID={8B1AAE4C-1462-4249-8B87-3F6A3ADE87CE}]
    Is target value within range?
    [/cover] */
    if (Gpt_lCheckTimeOutVaue(TimeOutVal, GPT_GTM_ATOM_TIMER_MAX) == TRUE)
    {
      /* MISRA2012_RULE_11_3_JUSTIFICATION: Pointer type recasting done
         for ease of access to channels registers.*/
      /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and
         integer type. Permitted for special function registers.*/
      /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
         by violating this MISRA rule.*/
      /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic used due to
         PBConfigStructure and is within allowed range.*/
      AtomChannelRegPtr = GTM_ATOM_CH_POINTER(ModuleNumber, ChannelNumber);

     
      /* [cover parentID={B9B9C406-4BD3-40f7-83B9-AC05EADEF7CA}]
      Clear CN0 Set CM0 and SR0 with the Timeout value
      [/cover] */
      /* Clear the CN0 register  */
      AtomChannelRegPtr->CN0.U = (uint8)0x0U;

      /* Set CM0 with the Timeout value */
      AtomChannelRegPtr->CM0.U = TimeOutVal;

      /* Set Shadow register also with same TimeOut Value, this is a safety
      measure to avoid unintended update from shadow registers */
      AtomChannelRegPtr->SR0.U = TimeOutVal;

     
      /* Clear Notify */
      AtomChannelRegPtr->IRQ.NOTIFY.U = GPT_CLEAR_INTERRUPTS;


      /* [cover parentID={E8D2C0E0-95B0-4eac-B295-4993DF066933}]
      Safety enable or DET is On
      [/cover] */
      /* [cover parentID={F24D2EC2-9397-4bf6-B305-A20DD0953215}]
      Safety enable or DET is On
      [/cover] */
      #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
      IDetVal = (uint32)GTM_GPT_CHANNEL_RUNNING;
      #endif
      
      /* [cover parentID={ADF8C998-622F-4575-AFF5-AFA4D9086381}]
      Start of critical section
      [/cover] */
      SchM_Enter_Gpt_GtmStartTimer();
      
      /* Call the library function to start the timer channel.
      with TimerOutputEn=0, as its not required to enable the output mode.*/
      /* [cover parentID={59631276-BBE3-4ddc-AE5F-617A21DC19DD}]
      Start the timer channel with TimerOutputEn=0, as its not required 
      to enable the output 
      [/cover] */
      Mcu_17_Gtm_AtomChannelEnable(ModuleNumber, ChannelNumber, 0x0U);
      /* [cover parentID={98F07D17-B959-4254-AD0F-400193880886}]
      Clear CN0 and set channel status to 'Running'
      [/cover] */
      AtomChannelRegPtr->CN0.U = (uint8)0x0U;
      Gpt_ThreadSafeData[CurrentCoreId]->Gpt_ChannelStatusPtr[Channel] =
                                                        GPT_CHANNEL_RUNNING;
                                                        
      /* [cover parentID={E221E144-ECC8-4bd2-B7F3-777A30FDF7A6}]
      End of critical section
      [/cover] */                                                  
      SchM_Exit_Gpt_GtmStartTimer();    
    }
  }
  #endif
  /* End of #if (GPT_ATOM_USED == STD_ON)  */

  /* [cover parentID={FD7CAD66-4C54-4b50-8B99-2F0BF902FCEE}]
  Safety enable or DET is On
  [/cover] */
  #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))

  /* [cover parentID={5B3B1DB0-1894-408b-B75F-99209C46B658}]
  Is TimeOutVal valid?
  [/cover] */
  if (IDetVal == (uint32)GTM_GPT_WRONG_PARAM)
  {
    /* [cover parentID={F8BBB996-66B7-4a39-9187-07299F185CF1}]
    Report DET
    [/cover] */
    Gpt_lReportError(GPT_SID_STARTTIMER, GPT_E_PARAM_VALUE);
  }
  #endif

  return;
}/* End of Gpt_lGtmStartTimer */
/******************************************************************************/
#endif
 
#if (GPT_GPT12_USED == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={6D3C6162-FA76-47a5-B62B-BF3349877ACE}]   **
**                                                                            **
** Syntax         : static void Gpt_lGpt12StartTimer                          **
**                                           (                                **
**                                             const Gpt_ChannelType Channel, **
**                                             const uint32 TimeOutVal,       **
**                                             const uint32 CurrentCoreId     **
**                                           )                                **
**                                                                            **
** Description    : This function starts the GPT timer to count               **
**                  until TimeOutVal.                                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant for different timer channel                     **
**                                                                            **
** Parameters(in) : Channel       - Channel ID                                **
**                  TimeOutVal    - Timeout value to which the GPT timer has  **
**                                  to count                                  **
**                  CurrentCoreId - Current Core ID                           **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
static void Gpt_lGpt12StartTimer  (
                                  const Gpt_ChannelType Channel,
                                  const uint32 TimeOutVal,
                                  const uint32 CurrentCoreId
                                )
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * this MISRA rule, Gpt12TxRegPtr is used to access the SFR. 
   * Union is required */
  volatile Ifx_GPT12_T2 *Gpt12TxRegPtr = &GPT120_T2;

  
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * this MISRA rule, Gpt12TxConRegPtr is used to access the SFR. 
   * Union is required*/
  volatile Ifx_GPT12_T2CON *Gpt12TxConRegPtr = &GPT120_T2CON;

  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * this MISRA rule, Gpt12CaprelPtr is used to access the SFR. 
   * Union is required*/
  volatile Ifx_GPT12_CAPREL *Gpt12CaprelPtr = &GPT120_CAPREL;
  Mcu_17_Gpt12_TimerChIdentifierType Timernumber;    /* Holds the channel number     */
  Mcu_17_Gpt12_TimerChIdentifierType Timernumber2;   /* Holds the channel number     */
  uint32 Ctrlregval;

  /* [cover parentID={7C786AD9-2774-4606-BD64-7BD5E3357660}]
  If target time is valid
  [/cover] */
  /* [cover parentID={32FD0C5A-1DDD-462b-BA35-7296C5C58A9C}]
  Check whether the target time is valid
  [/cover] */
  if (Gpt_lCheckTimeOutVaue(TimeOutVal, GPT_GPT12_TIMER_MAX) == TRUE)
  {

    Timernumber = GPT_GET_GPT12TIMERINFO(CurrentCoreId, Channel, 0).TimerId;
    Ctrlregval = Gpt12TxConRegPtr[Timernumber].U | GPT_GPT12_START_MASK;

    Gpt12TxRegPtr[Timernumber].U = TimeOutVal;   
    /* [cover parentID={B4435EEE-65F1-49df-AB46-9F3777985297}]
    Is mode continous
    [/cover] */
    if(GPT_GET_CORECONFIGPTR(CurrentCoreId)->ChannelConfigPtr[Channel].
       GptChannelMode == GPT_MODE_CONTINUOUS)
    {    
    
      /* [cover parentID={3DD56A0A-77D5-4e5b-8A0D-50B749D35EAD}]
      Set the functionality for continuous mode
      [/cover] */
      /* [cover parentID={4A2803DD-2CE7-423c-A645-55DA8C235F4D}]
      Is GPT block 2 used ?
      [/cover] */
      if(MCU_GPT12_TIMER4 < Timernumber)
      {
        /* [cover parentID={75F5C251-35C5-4814-98AF-A1E54E364E9D}]
        Load the target time to the reload register
        [/cover] */
        Gpt12CaprelPtr->U = TimeOutVal;
      }
      else
      {
        Timernumber2 =GPT_GET_GPT12TIMERINFO(CurrentCoreId, Channel, 1).TimerId;
        /* [cover parentID={02C6A932-A743-43b3-B906-3AEBC30FF5A7}]
        Is T2 used with fastest configuration/highest resolution? [/cover] */
        if(Timernumber2 == MCU_GPT12_TIMER2)
        {
          uint32 TimeOut = TimeOutVal ;
          if ((Ctrlregval & GPT_GPT12_TIBPS_MASK) == GPT_GPT12_TIBPS_VAL)
          {
            /* [cover parentID={65229B4A-FA79-46b4-9457-D3993B8F9758}]
            Load the target time minus one to the T2 timer [/cover] */
            TimeOut -=  GPT_GPT12_REL_DELAYOFFSET; 
          }
          Gpt12TxRegPtr->U = TimeOut;
        }
        else
        {
          /* [cover parentID={11D4E549-1EA0-44dd-8B6D-070861F8A0ED}]
          Load the target time to T4 timer
          [/cover] */ 
          Gpt12TxRegPtr[Timernumber2].U = TimeOutVal;
        }
      }
    }
    #if (GPT_ONESHOT_USED == STD_ON)
    /* [cover parentID={ECDB1D0A-BAC4-4dec-97C3-8B90B1D69C29}]
    Is mode One-shot
    [/cover] */
    else
    {
      /* [cover parentID={56BDB17F-6425-4e3d-9DC7-EE31196034B8}]
      Is timer used T3 or T6?
      [/cover] */
      if((MCU_GPT12_TIMER3 == Timernumber) || (MCU_GPT12_TIMER6==Timernumber))
      { 
        /* [cover parentID={FAFD3D63-05EA-4113-9FAE-E9C267786529}]
        Clear the underflow flag of the timer
        [/cover] */
        Ctrlregval &= GPT_GPT12_TOTL_MASK;
        
      }
    }
    #endif
    
    /* [cover parentID={FFFE89D1-62EE-402c-B7A9-3080D959FF9C}]
    Start of critical section
    [/cover] */
    SchM_Enter_Gpt_Gpt12StartTimer();
    
    /* [cover parentID={F2833F19-5D88-45da-BBEA-7BF6DB284D6E}]
    Start the timer(write the value to control register)
    [/cover] */
    Gpt12TxConRegPtr[Timernumber].U = Ctrlregval;
    
    /* [cover parentID={925183CD-E9B9-41f8-B23C-9C1255840F41}]
    Set channel state to running and save the target time for the channel
    [/cover] */
    Gpt_ThreadSafeData[CurrentCoreId]->Gpt_ChannelStatusPtr[Channel] =
                                                         GPT_CHANNEL_RUNNING;
                                                            
    
    Gpt_ThreadSafeData[CurrentCoreId]->Gpt_Targettime[Channel] = TimeOutVal;
    
    /* [cover parentID={7D3BEE14-E1D2-4244-BD36-685C7053AF16}]
    End of critical section
    [/cover] */
    SchM_Exit_Gpt_Gpt12StartTimer();
  
  }
  #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON)) 
  else
  {
    /* [cover parentID={991C8BC4-4EFD-48b0-9570-D1EE7F9C5F65}]
    Report safety error
    [/cover] */
    Gpt_lReportError(GPT_SID_STARTTIMER, GPT_E_PARAM_VALUE);
  }
  #endif

  return;

}/* End of Gpt_lGpt12StartTimer */
#endif

#if (GPT_TOM_USED == STD_ON) || (GPT_ATOM_USED == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={8E8DFC79-5C49-4bcd-82B4-F8314BECE3D2}]   **
**                                                                            **
** Syntax         : static void Gpt_lGtmStopTimer                             **
**                                        (                                   **
**                                          const Gpt_ChannelType Channel,    **
**                                          const uint32 CurrentCoreId        **
**                                        )                                   **
**                                                                            **
** Description    : This function stops a GPT Timer from counting             **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant for different timer channel                     **
**                                                                            **
** Parameters(in) : Channel       - Channel ID                                **
**                  CurrentCoreId - Current Core ID                           **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
static void Gpt_lGtmStopTimer (
                                const Gpt_ChannelType Channel,
                                const uint32 CurrentCoreId
                              )
{
  const Mcu_17_Gtm_TomAtomChConfigType *LocalGptGtmTimerInfo;
  uint8 ModuleNumber;      /* Holds the module Number */
  uint8 ChannelNumber;     /* Holds the Channel Number*/

  /* Get pointer to channel configuration */
  LocalGptGtmTimerInfo = &GPT_GET_GTMTIMERINFO(CurrentCoreId, Channel);

  ModuleNumber  = (uint8)((LocalGptGtmTimerInfo->TimerId &
                           GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);

  ChannelNumber = (uint8)((LocalGptGtmTimerInfo->TimerId &
                           GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);

  /* [cover parentID={12579D95-CD51-4470-99BC-FEA1C1A761E2}]
  TOM is used
  [/cover] */
  #if (GPT_TOM_USED == STD_ON)
  /* Check the Module Type */
  /* [cover parentID={97D2E240-9D7D-4e6b-8E6A-83064CAD8F67}]
  Is the channel a TOM channel?
  [/cover] */
  if (LocalGptGtmTimerInfo->TimerType == MCU_GTM_TIMER_TOM)
  {
    /* [cover parentID={9EFB84DF-8BF0-4d91-B19E-521190F38E14}]
    Stop the TOM timer channel
    [/cover] */
    Mcu_17_Gtm_TomChannelDisable(ModuleNumber, ChannelNumber);
  }
  #endif
  /*   #if (GPT_TOM_USED == STD_ON)   */

  /* [cover parentID={71A60981-3DA2-4f6c-A860-E9196D078168}]
  ATOM is used
  [/cover] */
  #if (GPT_ATOM_USED == STD_ON)
  /* Check the Module Type */
  /* [cover parentID={D558363C-043F-4f93-B1FD-DCD257E4A0ED}]
  Is the channel a ATOM channel?
  [/cover] */
  if (LocalGptGtmTimerInfo->TimerType == MCU_GTM_TIMER_ATOM)
  {
    /* [cover parentID={33225D2B-6DD3-4ddc-BB15-07A25E6D9317}]
    Stop the ATOM timer channel
    [/cover] */
    Mcu_17_Gtm_AtomChannelDisable(ModuleNumber, ChannelNumber);
  }
  #endif
  /* #if (GPT_ATOM_USED == STD_ON)   */

  return;
}/* End of Gpt_lGtmStopTimer */
/******************************************************************************/
#endif

#if (GPT_GPT12_USED == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={A1A5729C-F062-4c5b-BBB5-9D8EBA0B6004}]   **
**                                                                            **
** Syntax         : static void Gpt_lGpt12StopTimer                           **
**                                        (                                   **
**                                          const Gpt_ChannelType Channel,    **
**                                          const uint32 CurrentCoreId        **
**                                        )                                   **
**                                                                            **
** Description    : This function stops a GPT Timer from counting             **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant for different timer channel                     **
**                                                                            **
** Parameters(in) : Channel       - Channel ID                                **
**                  CurrentCoreId - Current Core ID                           **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
static void Gpt_lGpt12StopTimer (
                                const Gpt_ChannelType Channel,
                                const uint32 CurrentCoreId
                              )
{
  Mcu_17_Gpt12_TimerChIdentifierType Timernumber;

  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * this MISRA rule, Gpt12TxConRegPtr is used to access the SFR. 
   * Union is required*/
  volatile Ifx_GPT12_T2CON *Gpt12TxConRegPtr = &GPT120_T2CON;
  
  Timernumber = GPT_GET_GPT12TIMERINFO(CurrentCoreId, Channel, 0).TimerId;
  /* [cover parentID={FFB59982-8FE8-4aad-80E9-E5DD5F714936}]
  Stop the timer
  [/cover] */              
  Gpt12TxConRegPtr[Timernumber].U &= GPT_GPT12_STOP_MASK;


  return;
}/* End of Gpt_lGtmStopTimer */
#endif
/******************************************************************************/
#if (GPT_TOM_USED == STD_ON) || (GPT_ATOM_USED == STD_ON)
#if (GPT_TIME_REMAINING_API == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={41B94A0F-542D-4d7a-B6C2-02986CF64E23}]   **
**                                                                            **
** Syntax         : static uint32 Gpt_lGtmGetTimeRemaining                    **
**                         (const Gpt_ChannelConfigType *const GptChannelPtr) **
**                                                                            **
** Description    : This function gets the Time Remaining for a GPT channel   **
**                  to complete counting                                      **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : GptChannelPtr - Pointer to core specific channel config   **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : RetVal - Time Remaining for Timeout                       **
**                                                                            **
*******************************************************************************/
static uint32 Gpt_lGtmGetTimeRemaining
                            (const Gpt_ChannelConfigType *const GptChannelPtr)
{
  const Mcu_17_Gtm_TomAtomChConfigType *LocalGptGtmTimerInfo;

  #if (GPT_TOM_USED == STD_ON)
  const Ifx_GTM_TOM_CH *TomChannelRegPtr;   /* Ptr to TOM Channel Register  */
  #endif

  #if (GPT_ATOM_USED == STD_ON)
  const Ifx_GTM_ATOM_CH *AtomChannelRegPtr; /* Ptr to ATOM Channel Register */
  #endif

  uint32 Cm0Val;                            /* Holds the CM0 value          */
  uint32 Cn0Val;                            /* Holds the CN0 value          */
  uint32 RetVal;                            /* Holds the Return value       */
  uint8 ModuleNumber;                       /* Holds the module number      */
  uint8 ChannelNumber;                      /* Holds the channel number     */

  #if (GPT_ONESHOT_USED == STD_ON)
  boolean OneShotModeStatus;                /* Holds OSM status             */
  #endif /* End of #if (GPT_ONESHOT_USED == STD_ON) */

  /* The GptGtmTimerInfo contains properties of TOM/ATOM channel used */
  LocalGptGtmTimerInfo = GptChannelPtr->GptGtmTimerInfo;

  ModuleNumber = (uint8)((LocalGptGtmTimerInfo->TimerId & 
                          GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);

  ChannelNumber = (uint8)((LocalGptGtmTimerInfo->TimerId &
                          GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);

  RetVal = (uint8)0x0U;

  /* [cover parentID={0E750DAC-E97A-4099-9D59-4AD5EBE55D94}]
  TOM is used
  [/cover] */
  #if (GPT_TOM_USED == STD_ON)
  /* [cover parentID={BB99DED9-92DD-4423-8FCD-17D246CD916E}]
  Read the timer count
  [/cover] */

  /* [cover parentID={93FE0807-9EAD-4f9e-A3CE-B12E7568FC2C}]
  Is it a TOM channel?
  [/cover] */
  if (LocalGptGtmTimerInfo->TimerType == MCU_GTM_TIMER_TOM)
  {
    /* MISRA2012_RULE_11_3_JUSTIFICATION: Pointer type recasting done
       for ease of access to channels registers.*/
    /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and
       integer type. Permitted for special function registers.*/
    /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
       by violating this MISRA rule.*/
    /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic used due to
       PBConfigStructure and is within allowed range.*/
    TomChannelRegPtr = GTM_TOM_CH_POINTER(ModuleNumber, ChannelNumber);
    /* [cover parentID={6C192651-A6BC-4942-9AD0-4E0A621F023E}]
    ONESHOT Mode
    [/cover] */
    #if (GPT_ONESHOT_USED == STD_ON)
    /* [cover parentID={CB61DCDA-D60C-494c-8E5A-C5838D24BE50}]
    Is oneshot mode enabled?
    [/cover] */
    if (((uint32)TomChannelRegPtr->CTRL.U & 
         ((uint32)0x1U << GPT_GTM_CTRL_OSM)) > (uint32)0x0U)
    {
      OneShotModeStatus = (boolean)TRUE;
    }
    else
    {
      OneShotModeStatus = (boolean)FALSE;
    }

    /* CN0 continues to count after reaching CM0. This is
       handled in the ISR. To avoid corner cases, due to ISR latency, the
       notify bit is also checked, and if it is set it would indicate the
       Timer count is complete */
    /* [cover parentID={8740DD80-1E31-49c7-ADF8-DD0BAEC4526C}]
    Read the Notify bit,  as it would indicate the timer count status.
    [/cover] */

    /* [cover parentID={C9FF3C2D-F218-4788-B6E8-027C91304AB0}]
      Is Oneshot mode enabled and Notiy bit set?
     [/cover] */
    if ((Mcal_GetBitAtomic(TomChannelRegPtr->IRQ.NOTIFY.U, 0x0U, 0x1U) 
         == 0x1U) && (OneShotModeStatus == (boolean)TRUE))
    {
      /* [cover parentID={60E17354-75FE-4b80-8D54-086B2D1FCE19}]
      Return zero
      [/cover] */
      RetVal = (uint8)0x0U;
    }
    else
    #endif /* End of #if (GPT_ONESHOT_USED == STD_ON)*/
    {
      Cm0Val = TomChannelRegPtr->CM0.U;
      Cn0Val = TomChannelRegPtr->CN0.U;

      /* [cover parentID={6A35B867-8AC7-454e-A337-BFB766CB9ABA}]
      Return the difference between CM0 and CN0 value
      [/cover] */
      /* Return the difference between CM0 and CN0 value */
      RetVal = Cm0Val - Cn0Val;
    }
  }
  #endif
  /* End of #if (GPT_TOM_USED == STD_ON)   */

  /* [cover parentID={D0CF58F0-CBAA-40bd-A4FC-767FB0839E65}]
  ATOM is used
  [/cover] */
  #if (GPT_ATOM_USED == STD_ON)
  /* [cover parentID={A6FF8627-6A16-490f-905C-F86EBEBD0100}]
  Read the timer count
  [/cover] */

  /* [cover parentID={0735FAEC-3038-451d-AC9F-8725AF74EAF4}]
  Is it an ATOM  channel?
  [/cover] */
  if (LocalGptGtmTimerInfo->TimerType == MCU_GTM_TIMER_ATOM)
  {
    /* MISRA2012_RULE_11_3_JUSTIFICATION: Pointer type recasting done
       for ease of access to channels registers.*/
    /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and
       integer type. Permitted for special function registers.*/
    /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
       by violating this MISRA rule.*/
    /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic used due to
       PBConfigStructure and is within allowed range.*/
    AtomChannelRegPtr = GTM_ATOM_CH_POINTER(ModuleNumber, ChannelNumber);

    /* [cover parentID={2063A931-010F-432e-9665-C88CEFF97029}]
    ONESHOT Mode
    [/cover] */
    #if (GPT_ONESHOT_USED == STD_ON)
    /* [cover parentID={7A800AB5-0732-42c3-A952-E006DFDCD412}]
    Is oneshot mode enabled?
    [/cover] */
    if (((uint32)AtomChannelRegPtr->CTRL.U & 
         ((uint32)0x1U << GPT_GTM_CTRL_OSM)) > (uint32)0x0U)
    {
      OneShotModeStatus = (boolean)TRUE;
    }
    else
    {
      OneShotModeStatus = (boolean)FALSE;
    }

    /* CN0 continues to count after reaching CM0. This is
       handled in the ISR. To avoid corner cases, due to ISR latency, the
       notify bit is also checked, and if it is set it would indicate the
       Timer count is complete */
    /* [cover parentID={B031FD7D-C2B1-492d-9C2B-CEAE997867B1}]
    Is Oneshot mode enabled and Notiy bit set?
    [/cover] */
    if ((Mcal_GetBitAtomic(AtomChannelRegPtr->IRQ.NOTIFY.U, 0x0U, 0x1U) 
         == 0x1U) && (OneShotModeStatus == (boolean)TRUE))
    {
      /* [cover parentID={A7D5BCE7-70A1-485f-A5DB-9B4AC50E08B3}]
      Return zero
      [/cover] */
      RetVal = (uint8)0x0U;
    }
    else
    #endif
    /* End of #if (GPT_ONESHOT_USED == STD_ON) */
    {
      Cm0Val = AtomChannelRegPtr->CM0.U;
      Cn0Val = AtomChannelRegPtr->CN0.U;

      /* Return the difference between CM0 and CN0 value */
      RetVal = Cm0Val - Cn0Val;
    }
  }
  #endif
  /* #if (GPT_ATOM_USED == STD_ON)   */

  return RetVal;
}/* End of Gpt_lGtmGetTimeRemaining */
/******************************************************************************/
#endif
/* End of #if (GPT_TIME_REMAINING_API == STD_ON) */
#endif

#if ((GPT_TIME_REMAINING_API == STD_ON) && (GPT_GPT12_USED == STD_ON))
/*******************************************************************************
** Traceability   : [cover parentID={FD03DA22-966F-4c6c-9D1E-F898C855C80A}]   **
**                                                                            **
** Syntax         : static uint32 Gpt_lGtmGetTimeRemaining                    **
**                         (const Gpt_ChannelConfigType *const GptChannelPtr) **
**                                                                            **
** Description    : This function gets the time remaining for a GPT channel   **
**                  to complete counting                                      **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : GptChannelPtr - Pointer to core specific channel config   **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : RetVal - Time Remaining for Timeout                       **
**                                                                            **
*******************************************************************************/
static uint32 Gpt_lGpt12GetTimeRemaining
                            (const Gpt_ChannelConfigType *const GptChannelPtr, 
                             const Gpt_ChannelType LocalChannel, 
                             const uint32 CurrentCoreId)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
  * this MISRA rule, Gpt12TxRegPtr is used to access the SFR. 
  * Union is required*/
  volatile Ifx_GPT12_T2 *Gpt12TxRegPtr = &GPT120_T2;
  uint32  Timeremaining;
  Mcu_17_Gpt12_TimerChIdentifierType Timernumber;
  uint32 Timeout;
  #if (GPT_ONESHOT_USED == STD_ON)
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
  * this MISRA rule, Gpt12TxConRegPtr is used to access the SFR. 
  * Union is required*/
  volatile Ifx_GPT12_T2CON *Gpt12TxConRegPtr = &GPT120_T2CON;
  uint32 ChannelData, Underflowflag;
  #endif
  Timernumber = GptChannelPtr -> GptGpt12TimerInfo[0].TimerId;

  Timeout = Gpt_ThreadSafeData[CurrentCoreId]-> Gpt_Targettime[LocalChannel];
  
  Timeremaining = Gpt12TxRegPtr[Timernumber].U;
  /* [cover parentID={46089237-46B5-4310-ABAE-686D0E738C1B}]
  Is the mode continuous?
  [/cover] */
  if(GptChannelPtr -> GptChannelMode == GPT_MODE_CONTINUOUS)
  {
    if(Timernumber == MCU_GPT12_TIMER3)
    {
      /* [cover parentID={9A66341D-99CA-461e-A268-8EB5976EE896}]
      If time remaining is greater than target time and timer is T3
      [/cover] */
      if( Timeremaining > Timeout)
      {
        /* [cover parentID={BB764C0F-7080-4ec9-82DB-38CB0FE23317}]
        Set time remaining as target time
        [/cover] */
        Timeremaining = Timeout;
      }
        
    }
  }
  
  /* [cover parentID={377E5774-1656-4395-8A01-9C3561EBF43A}]
  One-shot mode available?
  [/cover] */
  #if (GPT_ONESHOT_USED == STD_ON)
  else
  {
    
    /* [cover parentID={52BC05C8-474F-460d-98AD-7E6B980F57EE}]
    If the timer is core timer
    [/cover] */
    if((Timernumber == MCU_GPT12_TIMER3)||(Timernumber == MCU_GPT12_TIMER6))
    {
     
       Underflowflag = Mcal_GetBitAtomic(Gpt12TxConRegPtr[Timernumber].U, 
                                         GPT_GPT12_TOTL_BIT, 0x1U);
       /* [cover parentID={E8AD3486-7391-4a89-907C-D51463D16A8E}]
       Is underflow flag set
       [/cover] */
       if(Underflowflag == 0x1U)
       {
         /* [cover parentID={D404480E-6224-4cd7-9678-CF0E0D0420AB}]
        Set time remaining as zero
        [/cover] */
         Timeremaining = 0u; 
       }
    }
    else
    {
      ChannelData = 
                    Gpt_ThreadSafeData[CurrentCoreId]->
                    Gpt_ChannelStatusPtr[LocalChannel];
      /* [cover parentID={63628199-90A2-49ba-82BA-9FF1920A1850}]
      If channel expired or time remaining greater than target time
      [/cover] */
      if((ChannelData == GPT_CHANNEL_EXPIRED) || (Timeremaining> Timeout))
      {
        /* [cover parentID={AD0A84A9-C473-4510-AF70-C7B5B04EF794}]
        Set time remaining as zero
        [/cover] */
        Timeremaining = 0u; 
      }
    }
  }
  #endif
  return Timeremaining;
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
  * by violating this MISRA rule, as the pointer Gpt12TxRegPtr  
  * is used for SFR access  */
  /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
  * by violating this MISRA rule, as the pointer  
  * Gpt12TxConRegPtr is used for SFR access  */
}
#endif
/* End of #if (GPT_TIME_REMAINING_API == STD_ON && GPT_GPT12_USED == STD_ON) */


#if ((GPT_TOM_USED == STD_ON) || (GPT_ATOM_USED == STD_ON))
#if (GPT_TIME_ELAPSED_API == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={25DD9B1C-F605-4147-92DE-B76285427473}]   **
**                                                                            **
** Syntax         : static uint32 Gpt_lGtmGetTimeElapsed                      **
**                        (const Gpt_ChannelConfigType *const GptChannelPtr)  **
**                                                                            **
** Description    : This function gets the Time Elapsed for a GPT channel.    **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : GptChannelPtr - Pointer to core specific channel config   **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : RetVal - Time Elapsed so far                              **
**                                                                            **
*******************************************************************************/
static uint32 Gpt_lGtmGetTimeElapsed
(const Gpt_ChannelConfigType *const GptChannelPtr)
{
  const Mcu_17_Gtm_TomAtomChConfigType *LocalGptGtmTimerInfo;

  #if (GPT_TOM_USED == STD_ON)
  const Ifx_GTM_TOM_CH *TomChannelRegPtr;    /* Ptr to TOM Channel Register  */
  #endif

  #if (GPT_ATOM_USED == STD_ON)
  const Ifx_GTM_ATOM_CH *AtomChannelRegPtr;  /* Ptr to ATOM Channel Register */
  #endif

  uint32 RetVal;                             /* Holds the Return value       */
  uint8 ModuleNumber;                        /* Holds the module number      */
  uint8 ChannelNumber;                       /* Holds the channel number     */

  #if (GPT_ONESHOT_USED == STD_ON)
  boolean OneShotModeStatus;                 /* Holds OSM status         */
  #endif
  /* End of #if (GPT_ONESHOT_USED == STD_ON) */

  /* The GptGtmTimerInfo contains properties of TOM/ATOM channel used */
  LocalGptGtmTimerInfo = GptChannelPtr->GptGtmTimerInfo;

  ModuleNumber = (uint8)((LocalGptGtmTimerInfo->TimerId & 
                          GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);

  ChannelNumber = (uint8)((LocalGptGtmTimerInfo->TimerId &
                           GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);

  RetVal = (uint8)0x0U;
  /* [cover parentID={95480BDE-AF45-4d56-A66D-2FC8742F40D7}]
  TOM is used
  [/cover] */

  /* [cover parentID={D822511D-1D48-49c7-9E7E-4A24852F143F}]
  Is it a TOM channel?
  [/cover] */
  #if (GPT_TOM_USED == STD_ON)
  /* [cover parentID={7754DB69-50A7-4689-9ADE-F8D4184366D2}]
  Read the timer count
  [/cover] */

  if (LocalGptGtmTimerInfo->TimerType == MCU_GTM_TIMER_TOM)
  {
    /* Get reference to the module Channel Register */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: Pointer type recasting done
       for ease of access to channels registers.*/
    /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and
       integer type. Permitted for special function registers.*/
    /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
       by violating this MISRA rule.*/
    /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic used due to
       PBConfigStructure and is within allowed range.*/
    TomChannelRegPtr = GTM_TOM_CH_POINTER(ModuleNumber, ChannelNumber);
    /* [cover parentID={E77F39BF-3798-4bb7-8C17-2940732E32D5}]
    ONESHOT Mode
    [/cover] */
    #if (GPT_ONESHOT_USED == STD_ON)
    /* [cover parentID={450FD725-682B-4929-AA17-8B97E024C019}]
    Is oneshot mode enabled?
    [/cover] */
    if (((uint32)TomChannelRegPtr->CTRL.U & 
         ((uint32)0x1U << GPT_GTM_CTRL_OSM)) > (uint32)0x0U)
    {
      /* [cover parentID={C788B77B-9434-4ee0-B7A8-39E6F75274AE}]
      Set oneshot mode status flag to TRUE
      [/cover] */
      OneShotModeStatus = (boolean)TRUE;
    }
    else
    {
      /* [cover parentID={39B94BE3-0F0B-4966-86DE-ACA53FC55897}]
      Set oneshot mode status flag to FALSE
      [/cover] */
      OneShotModeStatus = (boolean)FALSE;
    }

    /* CN0 continues to count after reaching CM0. This is
       handled in the ISR. To avoid corner cases, due to ISR latency, the
       notify bit is also checked, and if it is set it would indicate the
       Timer count is complete */
    /* [cover parentID={5B3BD77A-2AB6-4fd4-BAC0-9529F42F551A}]
    Is Oneshot mode enabled and Notiy bit set?
    [/cover] */
    if ((Mcal_GetBitAtomic(TomChannelRegPtr->IRQ.NOTIFY.U, 0x0U, 0x1U) 
         == 0x1U) && (OneShotModeStatus == (boolean)TRUE))
    {
      RetVal = TomChannelRegPtr->CM0.U;
    }
    else
    #endif
    /* End of #if (GPT_ONESHOT_USED == STD_ON)*/
    {
      /* Return CN0 value */
      RetVal = TomChannelRegPtr->CN0.U;
    }
  }
  #endif
  /* End of #if (GPT_TOM_USED == STD_ON) */

  /* [cover parentID={1CDCC109-DAFE-48ca-BD17-65B50BB192E0}]
  ATOM is used
  [/cover] */
  #if (GPT_ATOM_USED == STD_ON)
  /* [cover parentID={5FC752FE-22B8-4190-BF12-1C35E72CC5C8}]
  Read the timer count
  [/cover] */

  /* [cover parentID={25FC61A5-488E-4854-8B2E-BADDF336DDCE}]
  Is it an ATOM channel?
  [/cover] */
  if (LocalGptGtmTimerInfo->TimerType == MCU_GTM_TIMER_ATOM)
  {
    /* Get reference to the module Channel Register */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: Pointer type recasting done
       for ease of access to channels registers.*/
    /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and
       integer type. Permitted for special function registers.*/
    /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
       by violating this MISRA rule.*/
    /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic used due to
       PBConfigStructure and is within allowed range.*/
    AtomChannelRegPtr = GTM_ATOM_CH_POINTER(ModuleNumber, ChannelNumber);

    /* [cover parentID={2D924E90-247C-41da-B9E9-CFEB73830508}]
      ONESHOT Mode
      [/cover] */
    #if (GPT_ONESHOT_USED == STD_ON)
    /* [cover parentID={0F2E2FDF-499C-426c-A0A4-07D617B6223E}]
    Is oneshot mode enabled?
    [/cover] */
    if (((uint32)AtomChannelRegPtr->CTRL.U & 
         ((uint32)0x1U << GPT_GTM_CTRL_OSM)) > (uint32)0x0U)
    {
      /* [cover parentID={DFED6D68-6C9D-43aa-A1E0-A6EA3F6309A6}]
      Set oneshot mode status flag to TRUE
      [/cover] */
      OneShotModeStatus = (boolean)TRUE;
    }
    else
    {
      /* [cover parentID={69DFE90E-B082-4bfe-8147-569C99244DAF}]
      Set oneshot mode status flag to FALSE
      [/cover] */
      OneShotModeStatus = (boolean)FALSE;
    }

    /* CN0 continues to count after reaching CM0. This is
       handled in the ISR. To avoid corner cases, due to ISR latency, the
       notify bit is also checked, and if it is set it would indicate the
       Timer count is complete */
    /* [cover parentID={C56514AE-1F1A-4ad3-B537-9F5A57A2D823}]
    Is Oneshot mode enabled and Notiy bit set?
    [/cover] */
    if ((Mcal_GetBitAtomic(AtomChannelRegPtr->IRQ.NOTIFY.U, 0x0U, 0x1U) 
         == 0x1U) && (OneShotModeStatus == (boolean)TRUE))
    {
      RetVal = AtomChannelRegPtr->CM0.U;
    }
    else
    #endif
    {
      /* Return CN0 value */
      RetVal = AtomChannelRegPtr->CN0.U;
    }
  }
  #endif
  /* End of #if (GPT_ATOM_USED == STD_ON) */

  return RetVal;
}/* End of Gpt_lGtmGetTimeElapsed */
/******************************************************************************/
#endif
/* #if (GPT_TIME_ELAPSED_API == STD_ON) */  
#endif
/* #if ((GPT_TOM_USED == STD_ON) || (GPT_ATOM_USED == STD_ON)) */


#if ((GPT_TIME_ELAPSED_API == STD_ON) && (GPT_GPT12_USED == STD_ON))
/*******************************************************************************
** Traceability   : [cover parentID={11B77451-C85F-4fdb-9D17-9BF9A8B17194}]   **
**                                                                            **
** Syntax         : static uint32 Gpt_lGpt12GetTimeElapsed                    **
**                        (const Gpt_ChannelConfigType *const GptChannelPtr)  **
**                                                                            **
** Description    : This function gets the Time Elapsed for a GPT channel.    **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : GptChannelPtr - Pointer to core specific channel config   **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : RetVal - Time Elapsed so far                              **
**                                                                            **
*******************************************************************************/
static uint32 Gpt_lGpt12GetTimeElapsed
                            (const Gpt_ChannelConfigType *const GptChannelPtr, 
                             const Gpt_ChannelType LocalChannel, 
                             const uint32 CurrentCoreId) 
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
   * this MISRA rule, Gpt12TxRegPtr is used to access the SFR. 
   * Union is required*/
  volatile Ifx_GPT12_T2 *Gpt12TxRegPtr = &GPT120_T2;
  uint32 Timeelapsed, Timeremaining;
  Mcu_17_Gpt12_TimerChIdentifierType Timernumber;
  uint32 Timeout;
  #if (GPT_ONESHOT_USED == STD_ON)
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
  * this MISRA rule, Gpt12TxConRegPtr is used to access the SFR. 
  * Union is required*/
  volatile Ifx_GPT12_T2CON *Gpt12TxConRegPtr = &GPT120_T2CON;
  uint32 ChannelData, Underflowflag;
  #endif
  Timernumber = GptChannelPtr -> GptGpt12TimerInfo[0].TimerId;


  Timeout = Gpt_ThreadSafeData[CurrentCoreId]-> Gpt_Targettime[LocalChannel];
  Timeremaining = Gpt12TxRegPtr[Timernumber].U;
  Timeelapsed = Timeout - Timeremaining;
  
  /* [cover parentID={895E4FB7-625E-4eed-A188-D41F72787F4E}]
  Is the mode continuous?
  [/cover] */
  if(GptChannelPtr -> GptChannelMode == GPT_MODE_CONTINUOUS)
  {
    if(Timernumber == MCU_GPT12_TIMER3)
    {
      /* [cover parentID={4AD161F5-A0FA-42bf-BCD7-18323F8EC1BC}]
      If time remaining is greater than target time and timer is T3
      [/cover] */
      if( Timeremaining > Timeout)
      {
        /* [cover parentID={DD9A5C8A-452B-40d6-90AB-532BA491DF41}]
        Set time elapsed as zero
        [/cover] */
        Timeelapsed = 0u;
      }

    }
  }
  
  /* [cover parentID={581D6CFD-5F39-48f5-9823-CBD9839A13A2}]
  One-shot mode available?
  [/cover] */
  #if (GPT_ONESHOT_USED == STD_ON)
  else
  {
    
    /* [cover parentID={067D1D66-3D27-4dc3-A547-2AB0E3FD5A46}]
    If the timer is core timer
    [/cover] */
    if((Timernumber == MCU_GPT12_TIMER3)||(Timernumber == MCU_GPT12_TIMER6))
    {
      
       Underflowflag = Mcal_GetBitAtomic(Gpt12TxConRegPtr[Timernumber].U, 
                                         GPT_GPT12_TOTL_BIT, 0x1U);
       /* [cover parentID={243A65BA-373C-4471-B4C1-6853C33480E8}]
       Is underflow flag set
       [/cover] */
       if(Underflowflag == 0x1U)
       {     
     
        /* [cover parentID={133FEFE1-F2E5-4347-8721-30535E2DF7C9}]
        Set time elapsed as target time
        [/cover] */
        Timeelapsed = Timeout;    
       }        
    }
    else
    {
      ChannelData = 
                    Gpt_ThreadSafeData[CurrentCoreId]->
                    Gpt_ChannelStatusPtr[LocalChannel];
      
      /* [cover parentID={C4C5B56A-0023-4949-80F4-F91BCE52188C}]
      If channel expired or time remaining greater than target time
      [/cover] */      
      if((ChannelData == GPT_CHANNEL_EXPIRED) || (Timeremaining> Timeout))
      {
        
        /* [cover parentID={48326E55-0169-478b-B81A-DBBA5F2FD832}]
        Set time elapsed as target time
        [/cover] */
        Timeelapsed = Timeout; 
      }
    }
  }
  #endif

  return Timeelapsed;
   /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer Gpt12TxRegPtr  
   * is used for SFR access  */
   /* MISRA2012_RULE_8_13_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule, as the pointer  
   * Gpt12TxConRegPtr is used for SFR access  */
}/* End of Gpt_lGtmGetTimeElapsed */
/******************************************************************************/
#endif
/* #if (GPT_TIME_ELAPSED_API == STD_ON) */


#if ((GPT_PREDEF_TIMER_1US_16BIT_EN == STD_ON)    || \
     (GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON)    || \
     (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))
/*******************************************************************************
** Traceability   : [cover parentID={D85F9C63-542F-41ab-8AF7-9003E7B721A5}]   **
**                                                                            **
** Syntax         : static void Gpt_lGtmStart1UsPredefTimer                   **
**                            (const Gpt_CoreConfigType *const CoreConfigPtr) **
**                                                                            **
** Description    : This function initializes and starts all the 1Us          **
**                  GPT Predef timers that are configured.                    **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : CoreConfigPtr - Pointer to current core configuration     **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
static void Gpt_lGtmStart1UsPredefTimer
                                (const Gpt_CoreConfigType *const CoreConfigPtr)
{
  const Gpt_1UsPredefTimerChannelConfigType   *LocalGptPredefChannelPtr;
  uint8 ModuleNumber;                         /* Holds the module number     */
  uint8 ChannelNumber;                        /* Holds the channel number    */

  #if ((GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON) || \
       (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))
  Gpt_PredefTimerType PredefTimerUsed;
  #endif

  /* Get pointer to 1us Predef Timer */
  LocalGptPredefChannelPtr = CoreConfigPtr->Predef1UsChannelConfigPtr;

  #if ((GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON) || \
      (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))
  PredefTimerUsed = LocalGptPredefChannelPtr->Gpt1UsPredefTimerUsed0;
  #endif

  /* Set the 1us Predef timer status to "Uninitialized" */
  /* [cover parentID={E4E5C9CD-156B-4dc9-BC87-6652924F3DB5}]
  Set the 1us predef timer status to "Uninitialized"
  [/cover] */
  GPT_SET_1US_PREDEF_TIMER_STS(GPT_CHANNEL_UNINITIALIZED);

  /* [cover parentID={18FF39EA-FD50-420b-B71D-3AC93FF678AC}]
  Extra channel required
  [/cover] */
  #if (GPT_PREDEF_EXTRA_CH_1US == STD_ON)
  /* [cover parentID={BED9FCA6-E3D2-4f4e-BC0B-6BA44E8C4418}]
  Is extra channel required for 1us predefined?
  [/cover] */
  if (LocalGptPredefChannelPtr->ExtraChRequirement1Us == 0x1U)
  {
    /************************************************************************
     * Configure the channel which is used to tick the Predef channel       *
     ************************************************************************/
    /* Module Id of the TOM channel */
    ModuleNumber = (uint8)  
      ((LocalGptPredefChannelPtr->GptGtm1UsTimerInfo0.TimerId &
                      GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);

    /* Channel number of the TOM channel */
    ChannelNumber = (uint8) 
                    ((LocalGptPredefChannelPtr->GptGtm1UsTimerInfo0.TimerId &
                      GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);

    /* Call GTM Library to Initialize TOM channel */
    Mcu_17_Gtm_TomChannelInit(
      &(LocalGptPredefChannelPtr->GptGtm1UsTimerInfo0));

    /* Force update CM0, CM1 and CRK_SRC registers of the TOM channel */
    Mcu_17_Gtm_TomChannelShadowTransfer(ModuleNumber, ChannelNumber);

    /* [cover parentID={FE8C7BC9-3F3D-4d3b-8B0A-0097270F324C}]
    Call the library function to start the timer channel.
    with TimerOutputEn=0, as its not required to enable the output mode.
    [/cover] */
    Mcu_17_Gtm_TomChannelEnable(ModuleNumber, ChannelNumber, 0x0U);
  }
  #endif

  /**************************************************************************
   * Configure the actual Predef Channel                                    *
   **************************************************************************/
  /* Module Id of the TOM channel */
  ModuleNumber = (uint8)  
                 ((LocalGptPredefChannelPtr->GptGtm1UsTimerInfo1.TimerId &
                   GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);

  /* Channel number of the TOM channel */
  ChannelNumber = (uint8) 
                  ((LocalGptPredefChannelPtr->GptGtm1UsTimerInfo1.TimerId &
                    GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);

  /* Call GTM Library to Initialize TOM channel */
  Mcu_17_Gtm_TomChannelInit(
    &(LocalGptPredefChannelPtr->GptGtm1UsTimerInfo1));

  /* Force update CM0, CM1 and CRK_SRC registers of the TOM channel */
  Mcu_17_Gtm_TomChannelShadowTransfer(ModuleNumber, ChannelNumber);

  /* [cover parentID={438F8287-A53B-465f-972A-DF181F9DD0B7}]
  Call the library function to start the timer channel with TimerOutputEn=0,
  as its not required to enable the output mode
  [/cover] */
  Mcu_17_Gtm_TomChannelEnable(ModuleNumber, ChannelNumber, 0x0U);

  /* [cover parentID={57E53CCE-B6AB-455d-B281-77AA00E13962}]
  Predef timer more than 16Bits
  [/cover] */
  #if ((GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON) || \
      (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))
  /* [cover parentID={378CD636-00AF-4ae9-950E-55354A92F135}]
  Is 1us Predef Timer more than 16bits?
  [/cover] */
  if (PredefTimerUsed != GPT_PREDEF_TIMER_1US_16BIT)
  {
    /************************************************************************
     * Configure the immediate next channel in case of 24 or 32 bit Predef  *
     * timer                                                                *
     ************************************************************************/
    /* Module Id of the TOM channel */
    ModuleNumber = (uint8)  
        ((LocalGptPredefChannelPtr->GptGtm1UsTimerInfo2.TimerId &
                          GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);

    /* Channel number of the TOM channel */
    ChannelNumber = (uint8) 
                    ((LocalGptPredefChannelPtr->GptGtm1UsTimerInfo2.TimerId &
                      GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);

    /* Call GTM Library to Initialize TOM channel */
    Mcu_17_Gtm_TomChannelInit(
      &(LocalGptPredefChannelPtr->GptGtm1UsTimerInfo2));

    /* Force update CM0, CM1 and CRK_SRC registers of the TOM channel */
    Mcu_17_Gtm_TomChannelShadowTransfer(ModuleNumber, ChannelNumber);

    /* [cover parentID={4645E957-6F24-49e5-B9C1-99CB56937755}]
    Call the library function to start the timer channel.
    with TimerOutputEn=0, as its not required to enable the output mode.
    [/cover] */
    Mcu_17_Gtm_TomChannelEnable(ModuleNumber, ChannelNumber, 0x0U);
  }
  #endif
  /* [cover parentID={D6EEA3B7-E988-40cd-8FEC-67E26050109E}]
  Set the 1us predef timer status to "Running"
  [/cover] */
  /* Set the 1us Predef timer status to "Running" */
  GPT_SET_1US_PREDEF_TIMER_STS(GPT_CHANNEL_RUNNING);

  return;
}/* End of Gpt_lGtmStart1UsPredefTimer */
/******************************************************************************/

/*******************************************************************************
** Traceability   : [cover parentID={5816ED9A-06CE-4bff-ABA0-1E00C4191686}]   **
**                                                                            **
** Syntax         : static uint32 Gpt_lGtmGet1UsPredefTimerValue              **
**                                   (                                        **
**                                     const Gpt_PredefTimerType PredefTimer, **
**                                     const uint32 CurrentCoreId             **
**                                   )                                        **
**                                                                            **
** Description    : This function delivers the current value of               **
**                  the desired 1Us Predef Timer.                             **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : PredefTimer   - Type of Predef timer                      **
**                  CurrentCoreId - Current Core ID                           **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : RetVal - Time Elapsed so far                              **
**                                                                            **
*******************************************************************************/
static uint32 Gpt_lGtmGet1UsPredefTimerValue
                                      (
                                        const Gpt_PredefTimerType PredefTimer,
                                        const uint32 CurrentCoreId
                                      )
{
  const Gpt_1UsPredefTimerChannelConfigType   *LocalGptPredefChannelPtr;
  const Gpt_CoreConfigType                    *LocalCoreConfigPtr;

  /* Ptr to TOM Channel Register */
  Ifx_GTM_TOM_CH *TomChannelRegPtr1;

  #if ((GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON) || \
       (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))
  /* Ptr to TOM Channel Register */
  const Ifx_GTM_TOM_CH *TomChannelRegPtr2; /* Ptr to TOM Channel Register */

  uint32 TomChannelCount1; /* Holds the CN0 value of TOM Channel Register 1  */
  uint32 TomChannelCount2; /* Holds the CN0 value of TOM Channel Register 2  */
  #endif
  /* End of #if ((GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON) || \
       (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))            */

  uint32 RetVal;                                  /* Holds the Return value  */
  uint8 ModuleNumber1;                            /* Holds the module Number */
  uint8 ChannelNumber1;                           /* Holds the Channel Number*/

  #if ((GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON) || \
       (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))
  uint8 ModuleNumber2;                            /* Holds the module Number */
  uint8 ChannelNumber2;                           /* Holds the Channel Number*/
  #endif
  /* End of #if ((GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON) || \
                (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON)) */

  /* Get pointer to current core configuration */
  LocalCoreConfigPtr = GPT_GET_CORECONFIGPTR(CurrentCoreId);

  /* Get pointer to Predef Timer */
  LocalGptPredefChannelPtr = LocalCoreConfigPtr->Predef1UsChannelConfigPtr;

  /* Module Id of the TOM channel */
  ModuleNumber1 = 
                  (uint8)((LocalGptPredefChannelPtr->GptGtm1UsTimerInfo1.TimerId &
                           GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);

  /* Channel number of the TOM channel */
  ChannelNumber1 = 
                   (uint8)((LocalGptPredefChannelPtr->GptGtm1UsTimerInfo1.TimerId &
                            GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);

  /* MISRA2012_RULE_11_3_JUSTIFICATION: Pointer type recasting done
     for ease of access to channels registers.*/
  /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and
     integer type. Permitted for special function registers.*/
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
     by violating this MISRA rule.*/
  /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic used due to
     PBConfigStructure and is within allowed range.*/
  TomChannelRegPtr1 = GTM_TOM_CH_POINTER(ModuleNumber1, ChannelNumber1);

  /* [cover parentID={01786E4C-82A8-478d-B374-5F76C720E997}]
  1us Predef Timer  24/32 Bit enabled
  [/cover] */
  #if ((GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON) || \
      (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))

  /* [cover parentID={046BC392-FB72-468f-9072-C5E4D438DC6E}]
  Read Timer
  [/cover] */

  /* [cover parentID={35DA04C2-1510-4ada-8394-5D310B6B7DCC}]
  Is 24/32 Bit predef timer?
  [/cover] */
  if (PredefTimer != GPT_PREDEF_TIMER_1US_16BIT)
  {
    /* Module Id of the TOM channel */
    ModuleNumber2 = 
        (uint8)((LocalGptPredefChannelPtr->GptGtm1UsTimerInfo2.TimerId &
                        GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);

    /* Channel number of the TOM channel */
    ChannelNumber2 = 
        (uint8)((LocalGptPredefChannelPtr->GptGtm1UsTimerInfo2.TimerId &
                      GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);

    /* Get reference to the module Channel Register */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: Pointer type recasting done
       for ease of access to channels registers.*/
    /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and
       integer type. Permitted for special function registers.*/
    /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
       by violating this MISRA rule.*/
    /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic used due to
       PBConfigStructure and is within allowed range.*/
    TomChannelRegPtr2 = GTM_TOM_CH_POINTER(ModuleNumber2, ChannelNumber2);

    /* [cover parentID={4DCAE7E0-CD70-47f1-8276-1FA273301087}]
    Enter critical section
    [/cover] */
    SchM_Enter_Gpt_Get1UsPredefTimerValue();

    /* [cover parentID={3A05CF17-BA82-453e-8410-C03E6F8D1D6F}]
    Start of Critical Section */

    
    /*Clear any pending interrupts of lower timer */
    TomChannelRegPtr1->IRQ.NOTIFY.U = GPT_CLEAR_INTERRUPTS;

    /* Read the count in upper timer */
    TomChannelCount2 = TomChannelRegPtr2->CN0.U;

    /* Read the count in lower timer */
    TomChannelCount1 = TomChannelRegPtr1->CN0.U;
    /* [/cover] */

    /* To avoid corner cases, check notify bit and if it is set it would
       indicate the lower timer rolled over and triggered the upper timer */
    /* [cover parentID={E3AC716B-645F-47bb-9114-402FAC67E13E}]
      Is the notify bit set?
      [/cover] */
    if(Mcal_GetBitAtomic(TomChannelRegPtr1->IRQ.NOTIFY.U, 0x0U, 0x1U) 
        == 0x1U)
    {
      /* Re-read the count in upper timer */
      TomChannelCount2 = TomChannelRegPtr2->CN0.U;

      /* Re-read the count in lower timer */
      TomChannelCount1 = TomChannelRegPtr1->CN0.U;
    }
    /* [/cover] */

    SchM_Exit_Gpt_Get1UsPredefTimerValue();
    /* [cover parentID={6E1FA24B-3AD8-4837-84E7-93E30EE2A33B}]
    End of Critical Section
    [/cover] */

    RetVal = (uint32)((TomChannelCount2 * GPT_GTM_TOM_PREDEFTIMER_MAX) + 
                      TomChannelCount1);
    /* [cover parentID={A4698E7B-3542-4cda-BA06-37FB5ADBDB19}]
    Is 24bit predef timer?
    [/cover] */
    if (PredefTimer == GPT_PREDEF_TIMER_1US_24BIT)
    {
      /* [cover parentID={66CF5C21-7E04-48e1-B746-4B4A15763641}]
      Mask the upper 8bits of Time Elapsed so far,
      as only 24Bit value is required.
      [/cover] */
      RetVal = ((uint32)(RetVal & GPT_24BIT_MASK));
    }
  }
  else
  #endif
    /* End of #if ((GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON)  || \
                  (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON)) */
  {
    RetVal = TomChannelRegPtr1->CN0.U;
  }
  UNUSED_PARAMETER(PredefTimer);
  return RetVal;
  /* MISRA2012_RULE_8_13_JUSTIFICATION: TomChannelRegPtr1 cannot be const 
  * because the pointer will be de-referenced and written when the 
  * predef compile switch is ON */
}/* End of Gpt_lGtmGet1UsPredefTimerValue */
/******************************************************************************/

#if ((GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) || (GPT_DEINIT_API == STD_ON))
/*******************************************************************************
** Traceability   : [cover parentID={DB92AC01-82B5-40da-A77F-512F9F0C4DFE}]   **
**                                                                            **
** Syntax         : static void Gpt_lGtmStop1UsPredefTimer                    **
**                           (                                                **
**                             const Gpt_CoreConfigType *const CoreConfigPtr, **
**                             const uint8 Gpt_Sid                            **
**                           )                                                **
**                                                                            **
** Description    : This function stops the 1us Predef Timer from counting    **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : CoreConfigPtr - Pointer to current core configuration     **
**                  Gpt_Sid       - Service id of the caller API              **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
static void Gpt_lGtmStop1UsPredefTimer
                              (
                                const Gpt_CoreConfigType *const CoreConfigPtr,
                                const uint8 Gpt_Sid
                              )
{
  const Gpt_1UsPredefTimerChannelConfigType   *LocalGptPredefChannelPtr;

  uint8 ModuleNumber;                        /* Holds the module number     */
  uint8 ChannelNumber;                       /* Holds the channel number    */

  #if ((GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON) || \
       (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))
  Gpt_PredefTimerType PredefTimerUsed;
  #endif

  LocalGptPredefChannelPtr = CoreConfigPtr->Predef1UsChannelConfigPtr;

  /* [cover parentID={7C8C50A4-590B-4f48-81A6-8D8FADF26C61}]
  Predef Timer is 24Bit or 32bit
  [/cover] */
  #if ((GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON) || \
      (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))
  /* [cover parentID={04A98578-B7A3-4b2d-A3D3-4A9B0EADB67E}]
  Fetch the PredefTimer used (16/24/32Bit)
  [/cover] */
  PredefTimerUsed = LocalGptPredefChannelPtr->Gpt1UsPredefTimerUsed0;
  #endif

  /* [cover parentID={057BF7AB-848B-4930-9081-1889317199DE}]
  Extra channel required
  [/cover] */
  #if (GPT_PREDEF_EXTRA_CH_1US == STD_ON)
  /* [cover parentID={D933E269-A5C1-4635-8B16-22D57DDEAF9C}]
  Is extra channel required for 1us predefined?
  [/cover] */
  if (LocalGptPredefChannelPtr->ExtraChRequirement1Us == 0x1U)
  {
    /************************************************************************
     * Stop the channel which is used to tick the Predef channel            *
     ************************************************************************/
    /* Module Id of the TOM channel */
    ModuleNumber = (uint8)  
        ((LocalGptPredefChannelPtr->GptGtm1UsTimerInfo0.TimerId &
                        GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);

    /* Channel number of the TOM channel */
    ChannelNumber = (uint8) 
                    ((LocalGptPredefChannelPtr->GptGtm1UsTimerInfo0.TimerId &
                      GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);

    /* [cover parentID={54E06E89-6E04-4395-9ABF-DC68C9B002B3}]
      Stop the TOM channel
      [/cover] */
    Mcu_17_Gtm_TomChannelDisable(ModuleNumber, ChannelNumber);

    /* [cover parentID={A4D543C2-9284-434c-803B-E80DA6A418A0}]
      Is DeInit requested?
      [/cover] */
    if (Gpt_Sid == GPT_SID_DEINIT)
    {
      /* [cover parentID={835B5C06-22E7-456d-B3DF-853D6AACC116}]
      Reset the TOM channel registers to its reset value
      [/cover] */
      Mcu_17_Gtm_TomChannelDeInit(ModuleNumber, ChannelNumber);
    }
  }
  #endif

  /*************************************************************************
   * Stop the actual Predef Channel                                        *
   *************************************************************************/
  /* Module Id of the TOM channel */
  ModuleNumber = (uint8)  
                 ((LocalGptPredefChannelPtr->GptGtm1UsTimerInfo1.TimerId &
                   GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);

  /* Channel number of the TOM channel */
  ChannelNumber = (uint8) 
                  ((LocalGptPredefChannelPtr->GptGtm1UsTimerInfo1.TimerId &
                    GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);

  /* [cover parentID={EAF8FA75-F054-4c7f-A823-2584B52D512C}]
  Stop the TOM channel
  [/cover] */
  Mcu_17_Gtm_TomChannelDisable(ModuleNumber, ChannelNumber);

  /* [cover parentID={C6A4AA12-943A-403b-8D98-65896EA672A3}]
  Is DeInit requested?
  [/cover] */
  if (Gpt_Sid == GPT_SID_DEINIT)
  {
    /* [cover parentID={790B01D9-F9E5-4327-825D-95E0906EDE45}]
    Reset the TOM channel registers to its reset value
    [/cover] */
    /* Reset the TOM channel registers to its reset value.*/
    Mcu_17_Gtm_TomChannelDeInit(ModuleNumber, ChannelNumber);
  }

  /* [cover parentID={A8AF60DE-31A3-4b0b-B87C-B524019203EF}]
  Predef timer more than 16Bits
  [/cover] */
  #if ((GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON) || \
  (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))

  /* [cover parentID={D324E4D6-0E27-4159-8A72-4311683C5B08}]
  Is 1us Predef Timer more than 16bits?
  [/cover] */
  if (PredefTimerUsed != GPT_PREDEF_TIMER_1US_16BIT)
  {
    /************************************************************************
     * Stop the immediate next channel in case of 24 or 32 bit Predef timer *
     ************************************************************************/
    /* Module Id of the TOM channel */
    ModuleNumber = (uint8)  
        ((LocalGptPredefChannelPtr->GptGtm1UsTimerInfo2.TimerId &
                        GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);

    /* Channel number of the TOM channel */
    ChannelNumber = (uint8) 
                    ((LocalGptPredefChannelPtr->GptGtm1UsTimerInfo2.TimerId &
                      GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);

    /* [cover parentID={FE3E16ED-568E-4867-B760-AF7A0C7C5130}]
    Call the library function to stop the timer channel
    [/cover] */
    Mcu_17_Gtm_TomChannelDisable(ModuleNumber, ChannelNumber);

    /* [cover parentID={35B29350-18ED-489f-B5C5-6C66A4807617}]
      Is DeInit requested?
      [/cover] */
    if (Gpt_Sid == GPT_SID_DEINIT)
    {
      /* [cover parentID={C41B6D09-3C7E-4dd9-88D8-4F03C4B23351}]
      Reset the TOM channel registers to its reset value
      [/cover] */
      /* Reset the TOM channel registers to its reset value.*/
      Mcu_17_Gtm_TomChannelDeInit(ModuleNumber, ChannelNumber);
    }
  }
  #endif

  /* Set the 1us Predef timer status to "Stopped" */
  GPT_SET_1US_PREDEF_TIMER_STS(GPT_CHANNEL_STOPPED);


  return;
}/* End of Gpt_lGtmStop1UsPredefTimer */
/******************************************************************************/
#endif
/* End of #if ((GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) || \
                              (GPT_DEINIT_API == STD_ON))    */
#endif
/* End of #if ((GPT_PREDEF_TIMER_1US_16BIT_EN == STD_ON)    || \
               (GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON)    || \
               (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))   */

#if (GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={7A0F8C7F-A651-45ac-AC9D-A3B72ABE7AA2}]   **
**                                                                            **
** Syntax         : static void Gpt_lGtmStart100UsPredefTimer                 **
**                           (const Gpt_CoreConfigType *const CoreConfigPtr)  **
**                                                                            **
** Description    : This function initializes and starts the 100us            **
**                  GPT Predef timer.                                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : CoreConfigPtr - Pointer to current core configuration     **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
static void Gpt_lGtmStart100UsPredefTimer
                                (const Gpt_CoreConfigType *const CoreConfigPtr)
{
  const Gpt_100UsPredefTimerChannelConfigType *LocalGptPredefChannelPtr;
  uint8 ModuleNumber;                         /* Holds the module number     */
  uint8 ChannelNumber;                        /* Holds the channel number    */

  /* Get pointer to 100us Predef Timer */
  LocalGptPredefChannelPtr = CoreConfigPtr->Predef100UsChannelConfigPtr;

  /* [cover parentID={292C6ABE-E069-4be6-B8A2-46BDB48D971E}]
  Set the 100us predef timer status to "Uninitialized"
  [/cover] */
  /* Set the 100us Predef timer status to "Uninitialized" */
  GPT_SET_100US_PREDEF_TIMER_STS(GPT_CHANNEL_UNINITIALIZED);

  /* [cover parentID={3A504827-ADB9-4f27-83DA-20B7DFFAB894}]
  Extra Channel Required
  [/cover] */
  #if (GPT_PREDEF_EXTRA_CH_100US == STD_ON)
  /* [cover parentID={9C63A5FB-2A63-4fb7-9B7C-BAC9CE2074C0}]
  Is extra channel  required for 100us predefined timer?
  [/cover] */
  if (LocalGptPredefChannelPtr->ExtraChRequirement100Us == 0x1U)
  {
    /************************************************************************
     * Configure the channel which is used to tick the Predef channel       *
     ************************************************************************/
    /* Module Id of the TOM channel */
    ModuleNumber = (uint8)  
                   ((LocalGptPredefChannelPtr->GptGtm100UsTimerInfo0.TimerId &
                     GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);

    /* Channel number of the TOM channel */
    ChannelNumber = (uint8) 
                    ((LocalGptPredefChannelPtr->GptGtm100UsTimerInfo0.TimerId &
                      GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);
    /* [cover parentID={50EED2E6-0181-4abe-91D9-BB7946EE89B7}]
    Initialize TOM channel
    [/cover] */
    Mcu_17_Gtm_TomChannelInit(
      &(LocalGptPredefChannelPtr->GptGtm100UsTimerInfo0)
    );
    /* Force update CM0, CM1 and CRK_SRC registers of the TOM channel */
    Mcu_17_Gtm_TomChannelShadowTransfer(ModuleNumber, ChannelNumber);

    /* [cover parentID={EEC5FF33-AA23-4596-A1E4-645A2E97A868}]
    Start the timer channel with TimerOutputEn=0
    [/cover] */
    Mcu_17_Gtm_TomChannelEnable(ModuleNumber, ChannelNumber, 0x0U);
  }
  #endif
  /* End of #if (GPT_PREDEF_EXTRA_CH_100US == STD_ON) */

  /*************************************************************************
   * Configure the actual Predef Channel                                   *
   *************************************************************************/
  /* Module Id of the TOM channel */
  ModuleNumber = (uint8) 
                 ((LocalGptPredefChannelPtr->GptGtm100UsTimerInfo1.TimerId &
                   GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);

  /* Channel number of the TOM channel */
  ChannelNumber = (uint8) 
                  ((LocalGptPredefChannelPtr->GptGtm100UsTimerInfo1.TimerId &
                    GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);

  /* [cover parentID={D8F9E60B-E8C9-4fca-9D48-D5B89687F344}]
    Initialize TOM channel
    [/cover] */

  Mcu_17_Gtm_TomChannelInit(
    &(LocalGptPredefChannelPtr->GptGtm100UsTimerInfo1));

  /* Force update CM0, CM1 and CRK_SRC registers of the TOM channel */
  Mcu_17_Gtm_TomChannelShadowTransfer(ModuleNumber, ChannelNumber);

  /* [cover parentID={D36A7494-A9D3-466a-A581-E58ED0925F68}]
  Start the timer channel with TimerOutputEn=0
  [/cover] */
  Mcu_17_Gtm_TomChannelEnable(ModuleNumber, ChannelNumber, 0x0U);

  /**************************************************************************
   * Configure the immediate next channel to make a 32 bit Predef timer     *
   **************************************************************************/
  /* Module Id of the TOM channel */
  ModuleNumber = (uint8)  
                 ((LocalGptPredefChannelPtr->GptGtm100UsTimerInfo2.TimerId &
                   GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);

  /* Channel number of the TOM channel */
  ChannelNumber = (uint8) 
                  ((LocalGptPredefChannelPtr->GptGtm100UsTimerInfo2.TimerId &
                    GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);

  /* [cover parentID={0581F2A4-F95E-4bb3-A377-482EF384706F}]
  Initialize TOM channel
  [/cover] */
  Mcu_17_Gtm_TomChannelInit(
    &(LocalGptPredefChannelPtr->GptGtm100UsTimerInfo2));

  /* Force update CM0, CM1 and CRK_SRC registers of the TOM channel */
  Mcu_17_Gtm_TomChannelShadowTransfer(ModuleNumber, ChannelNumber);


  /* [cover parentID={9D36FBA6-BAF1-40ff-A9B2-FDBA7E402260}]
  Start the timer channel with TimerOutputEn=0
  [/cover] */
  Mcu_17_Gtm_TomChannelEnable(ModuleNumber, ChannelNumber, 0x0U);

  /* [cover parentID={F2421467-5432-4c13-B95F-C85905C42D72}]
  Set 100us predef timer status to "Running"
  [/cover] */
  GPT_SET_100US_PREDEF_TIMER_STS(GPT_CHANNEL_RUNNING);

  return;
}/* End of Gpt_lGtmStart100UsPredefTimer */
/******************************************************************************/

/*******************************************************************************
** Traceability   : [cover parentID={B9C39719-F2D0-4ffd-9CD9-22091A90B544}]   **
**                                                                            **
** Syntax         : static uint32 Gpt_lGtmGet100UsPredefTimerValue            **
**                                              (const uint32 CurrentCoreId)  **
**                                                                            **
** Description    : This function delivers the current value of               **
**                  the desired GPT Predef Timer.                             **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : CurrentCoreId - Current Core ID                           **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : RetVal - Time Elapsed so far                              **
**                                                                            **
*******************************************************************************/
static uint32 Gpt_lGtmGet100UsPredefTimerValue(const uint32 CurrentCoreId)
{
  const Gpt_100UsPredefTimerChannelConfigType *LocalGptPredefChannelPtr;
  const Gpt_CoreConfigType                    *LocalCoreConfigPtr;

  /* Ptr to TOM Channel Register */
  Ifx_GTM_TOM_CH *TomChannelRegPtr1;

  /* Ptr to TOM Channel Register */
  const Ifx_GTM_TOM_CH *TomChannelRegPtr2;

  uint32 TomChannelCount1;           /* Holds CN0 of TOM Channel Register 1  */
  uint32 TomChannelCount2;           /* Holds CN0 of TOM Channel Register 2  */

  uint32 RetVal;                         /* Holds the Return value   */
  uint8 ModuleNumber1;                   /* Holds the module Number  */
  uint8 ChannelNumber1;                  /* Holds the Channel Number */
  uint8 ModuleNumber2;                   /* Holds the module Number  */
  uint8 ChannelNumber2;                  /* Holds the Channel Number */

  /* Get pointer to current core configuration */
  LocalCoreConfigPtr = GPT_GET_CORECONFIGPTR(CurrentCoreId);

  /* Get pointer to 100us Predef Timer configuration */
  LocalGptPredefChannelPtr = LocalCoreConfigPtr->Predef100UsChannelConfigPtr;

  /* Module Id of the TOM channel */
  ModuleNumber1 = 
                  (uint8)((LocalGptPredefChannelPtr->GptGtm100UsTimerInfo1.TimerId &
                           GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);

  /* Channel number of the TOM channel */
  ChannelNumber1 = 
                   (uint8)((LocalGptPredefChannelPtr->GptGtm100UsTimerInfo1.TimerId &
                            GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);

  /* Get reference to the module Channel Register */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: Pointer type recasting done
     for ease of access to channels registers.*/
  /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and
     integer type. Permitted for special function registers.*/
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
     by violating this MISRA rule.*/
  /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic used due to
     PBConfigStructure and is within allowed range.*/
  TomChannelRegPtr1 = GTM_TOM_CH_POINTER(ModuleNumber1, ChannelNumber1);

  /* Get the cascaded value of the counter registers to make 32 bit output */
  /* Module Id of the TOM channel */
  ModuleNumber2 = 
                  (uint8)((LocalGptPredefChannelPtr->GptGtm100UsTimerInfo2.TimerId &
                           GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);

  /* Channel number of the TOM channel */
  ChannelNumber2 = 
                   (uint8)((LocalGptPredefChannelPtr->GptGtm100UsTimerInfo2.TimerId &
                            GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);

  /* Get reference to the module Channel Register */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: Pointer type recasting done
     for ease of access to channels registers.*/
  /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and
     integer type. Permitted for special function registers.*/
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
     by violating this MISRA rule.*/
  /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic used due to
     PBConfigStructure and is within allowed range.*/
  TomChannelRegPtr2 = GTM_TOM_CH_POINTER(ModuleNumber2, ChannelNumber2);

  /* [cover parentID={242979FC-A7E4-4948-B839-2EC544448A85}]
  Enter critical section
  [/cover] */
  SchM_Enter_Gpt_Get100UsPredefTimerValue();

  /* [cover parentID={3548EB2E-97FF-4038-BEBF-F95AAF14C34E}]
  Start of Critical Section
  [/cover] */

  
  /* Clear any pending interrupts */

  TomChannelRegPtr1->IRQ.NOTIFY.U = GPT_CLEAR_INTERRUPTS;

  /* Read the count in upper timer */
  TomChannelCount2 = TomChannelRegPtr2->CN0.U;

  /* Read the count in lower timer */
  TomChannelCount1 = TomChannelRegPtr1->CN0.U;

  /* To avoid corner cases, check notify bit and if it is set it would indicate
     the lower timer rolled over and triggered the upper timer */
  /* [cover parentID={3E9B6983-A5AF-4637-B3A5-423B15928DC9}]
    Is the notify bit set?
    [/cover] */
  if(Mcal_GetBitAtomic(TomChannelRegPtr1->IRQ.NOTIFY.U, 0x0U, 0x1U) 
      == 0x1U)
  {
    /* Re-read the count in upper timer */
    TomChannelCount2 = TomChannelRegPtr2->CN0.U;

    /* Re-read the count in lower timer */
    TomChannelCount1 = TomChannelRegPtr1->CN0.U;
  }

  /* Exit critical section */
  SchM_Exit_Gpt_Get100UsPredefTimerValue();
  /* [cover parentID={2EE0F203-FA10-48f9-97DD-F8CBDD5B59DA}]
  End of Critical Section
  [/cover] */

  /* [cover parentID={B98E1702-93B3-4bb3-BAA6-B44329E007B9}]
  Time Elapsed so far is the sum of immediate next channel's CN0 count
  multiplied by maximum count of TOM (0xFFFF) and current channel's CN0 count.
  [/cover] */
  RetVal = (uint32)((TomChannelCount2 * GPT_GTM_TOM_PREDEFTIMER_MAX) + 
                                                TomChannelCount1);

  return RetVal;

}/* End of Gpt_lGtmGet100UsPredefTimerValue */
/******************************************************************************/

#if ((GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) || (GPT_DEINIT_API == STD_ON))
/*******************************************************************************
** Traceability   : [cover parentID={D582D4CF-1951-4b77-B51B-1FFA42FC892F}]   **
**                                                                            **
** Syntax         : static void Gpt_lGtmStop100UsPredefTimer                  **
**                           (                                                **
**                             const Gpt_CoreConfigType *const CoreConfigPtr, **
**                             const uint8 Gpt_Sid                            **
**                           )                                                **
**                                                                            **
** Description    : This function stops the 100us GPT Predef Timer from       **
**                  counting.                                                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : CoreConfigPtr - Pointer to current core configuration     **
**                  Gpt_Sid       - Service id of the caller API              **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
static void Gpt_lGtmStop100UsPredefTimer
                            (
                              const Gpt_CoreConfigType *const CoreConfigPtr,
                              const uint8 Gpt_Sid
                            )
{
  const Gpt_100UsPredefTimerChannelConfigType *LocalGptPredefChannelPtr;
  uint8 ModuleNumber;                        /* Holds the module number     */
  uint8 ChannelNumber;                       /* Holds the channel number    */

  LocalGptPredefChannelPtr = CoreConfigPtr->Predef100UsChannelConfigPtr;
  /* [cover parentID={ABE57CF1-655A-428f-8D67-696FCF180F18}]
  Extra Channel Required
  [/cover] */
  #if (GPT_PREDEF_EXTRA_CH_100US == STD_ON)
  /*************************************************************************
   * Stop the channel which is used to tick the Predef channel             *
   *************************************************************************/
  /* Stop the channel which is used to tick the Predef channel */
  /* [cover parentID={ED3962B0-8451-4a09-8EE8-35E3634CD1DD}]
     Is extra channel  required for 100us predefined timer?
     [/cover] */
  if (LocalGptPredefChannelPtr->ExtraChRequirement100Us == 0x1U)
  {
    /* Module Id of the TOM channel */
    ModuleNumber = (uint8)  
                   ((LocalGptPredefChannelPtr->GptGtm100UsTimerInfo0.TimerId &
                     GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);

    /* Channel number of the TOM channel */
    ChannelNumber = (uint8) 
                    ((LocalGptPredefChannelPtr->GptGtm100UsTimerInfo0.TimerId &
                      GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);

    /* [cover parentID={8CE5719E-9F3F-46c0-B3F5-1FFF641E83D5}]
     Stop the TOM Channel
     [/cover] */
    Mcu_17_Gtm_TomChannelDisable(ModuleNumber, ChannelNumber);
    /* [cover parentID={43AC4939-5C3B-441f-8938-838A3A9CB774}]
    Is DeInit requested?
    [/cover] */
    if (Gpt_Sid == GPT_SID_DEINIT)
    {
      /* [cover parentID={62DF46D0-7BDD-49fa-9E2D-0CB9CA61A0B1}]
      Reset the TOM channel registers to its reset value
      [/cover] */
      Mcu_17_Gtm_TomChannelDeInit(ModuleNumber, ChannelNumber);
    }
  }
  #endif

  /*************************************************************************
   * Stop the actual Predef channel                                        *
   *************************************************************************/
  /* Module Id of the TOM channel */
  ModuleNumber = (uint8)  
                 ((LocalGptPredefChannelPtr->GptGtm100UsTimerInfo1.TimerId &
                   GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);

  /* Channel number of the TOM channel */
  ChannelNumber = (uint8) 
                  ((LocalGptPredefChannelPtr->GptGtm100UsTimerInfo1.TimerId &
                    GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);

  /* [cover parentID={9E334645-BE5E-4a98-A7D0-278997D1E7CC}]
  Stop the TOM Channel
  [/cover] */
  Mcu_17_Gtm_TomChannelDisable(ModuleNumber, ChannelNumber);
  /* [cover parentID={92FB7BCA-F7A1-4bec-A8F7-41E5FC68DCB4}]
     Is DeInit requested?
     [/cover] */
  if (Gpt_Sid == GPT_SID_DEINIT)
  {
    /* Reset the TOM channel registers to its reset value.*/
    Mcu_17_Gtm_TomChannelDeInit(ModuleNumber, ChannelNumber);
  }

  /*************************************************************************
   * Stop the immediate next channel which is used for cascading           *
   *************************************************************************/
  /* Module Id of the TOM channel */
  ModuleNumber = (uint8)  
                 ((LocalGptPredefChannelPtr->GptGtm100UsTimerInfo2.TimerId &
                   GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);

  /* Channel number of the TOM channel */
  ChannelNumber = (uint8) 
                  ((LocalGptPredefChannelPtr->GptGtm100UsTimerInfo2.TimerId &
                    GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);

  /* [cover parentID={00EF7BDB-4327-45b5-85B8-69A272F64020}]
  Stop the TOM Channel
  [/cover] */
  Mcu_17_Gtm_TomChannelDisable(ModuleNumber, ChannelNumber);
  /* [cover parentID={26F575A7-AF0D-4a6e-83E0-3A9BAA04AC9C}]
  Is DeInit requested?
  [/cover] */
  if (Gpt_Sid == GPT_SID_DEINIT)
  {
    /* [cover parentID={A4529BCA-DD5D-421f-8213-85130CBC7ADC}]
    Reset the TOM channel registers to its reset value
    [/cover] */
    Mcu_17_Gtm_TomChannelDeInit(ModuleNumber, ChannelNumber);
  }

  /* Set 100us Predef timer status to "Stopped" */
  GPT_SET_100US_PREDEF_TIMER_STS(GPT_CHANNEL_STOPPED);

  return;
}/* End of Gpt_lGtmStop100UsPredefTimer */
/******************************************************************************/
#endif
/* End of #if ((GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) || \
                              (GPT_DEINIT_API == STD_ON)) */
#endif
/* End of #if (GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON) */

#if (GPT_DEINIT_API == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={9DBA304A-24B5-433a-8D73-7FA5AC541475}]   **
**                                                                            **
** Syntax         : static void Gpt_lResetChannel                             **
**                        (const Gpt_ChannelConfigType *const GptChannelPtr)  **
**                                                                            **
** Description    : This function resets the channel configured in GPT back   **
**                  to their Power On reset state                             **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : GptChannelPtr - Pointer to core specific channel config   **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
static void Gpt_lResetChannel(const Gpt_ChannelConfigType *const GptChannelPtr)
{ 
  #if (GPT_GPT12_USED == STD_ON)
  const Mcu_17_Gpt12_TimerConfigType *LocalGptGpt12TimerInfo;
  Mcu_17_Gpt12_TimerChIdentifierType             TimerNumber;
  #endif
  
  /* [cover parentID={9000627C-5BEF-4811-8049-E78F8D4C0F2B}]
  GTM used
  [/cover] */
  #if ((GPT_TOM_USED == STD_ON) || (GPT_ATOM_USED == STD_ON))
  const Mcu_17_Gtm_TomAtomChConfigType  *LocalGptGtmTimerInfo;
  uint8                                 ModuleNumber;
  uint8                                 ChannelNumber;

  /* The GptGtmTimerInfo contains properties of TOM/ATOM channel used */
  LocalGptGtmTimerInfo = GptChannelPtr->GptGtmTimerInfo;
  /* [cover parentID={4C374863-BCF8-4d22-A74D-A56BAB931256}]
  Is GTM used
  [/cover] */
  if(LocalGptGtmTimerInfo != NULL_PTR)
  {
    /* Module Id of the TOM channel */
    ModuleNumber  = (uint8)((LocalGptGtmTimerInfo->TimerId & 
                             GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);

    /* Channel number of the TOM channel */
    ChannelNumber = (uint8)((LocalGptGtmTimerInfo->TimerId &
                             GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);

    /* [cover parentID={20BB55B2-50D5-43f3-9C65-B79C86396568}]
    TOM is used
    [/cover] */
    #if (GPT_TOM_USED == STD_ON)
    /* [cover parentID={35596A30-9C2C-4818-B128-D05A3BD34A69}]
    Is it aTOM channel?
    [/cover] */
    if (LocalGptGtmTimerInfo->TimerType == MCU_GTM_TIMER_TOM)
    {
      /* [cover parentID={161EE188-4DA1-469e-BD4E-CC5F1D7409F7}]
      Call the library function to stop the timer channel
      [/cover] */
      Mcu_17_Gtm_TomChannelDisable(ModuleNumber, ChannelNumber);

      /* [cover parentID={A76F82E1-AE61-4436-AF28-B1C562759131}]
      Resets the TOM channel registers to its reset value
      [/cover] */
      Mcu_17_Gtm_TomChannelDeInit(ModuleNumber, ChannelNumber);
    }
    #endif
    /* End of #if (GPT_TOM_USED == STD_ON) */

    /* [cover parentID={0F18744D-923C-4a9a-B877-C0A7A3C90E56}]
    ATOM is used
    [/cover] */
    #if (GPT_ATOM_USED == STD_ON)
    /* [cover parentID={AE3F723F-133B-493c-8358-225467EE0CB2}]
    Is it ATOM Channel?
    [/cover] */
    if (LocalGptGtmTimerInfo->TimerType == MCU_GTM_TIMER_ATOM)
    {
      /* [cover parentID={161EE188-4DA1-469e-BD4E-CC5F1D7409F7}]
      Call the library function to stop the timer channel
      [/cover] */
      Mcu_17_Gtm_AtomChannelDisable(ModuleNumber, ChannelNumber);
      /* [cover parentID={84ABE952-051E-4d1d-824F-D8A15DD11BD7}]
      Resets the ATOM channel registers to its reset value
      [/cover] */
      /* To resets the TOM channel registers to its reset value.*/
      Mcu_17_Gtm_AtomChannelDeInit(ModuleNumber, ChannelNumber);
    }
    #endif
  }
  else
  #endif
  /* #if (GPT_ATOM_USED == STD_ON)   */
  {
    /* [cover parentID={A958D045-92DC-4832-A225-5D70BE7AA6DB}]
    GPT12 used
    [/cover] */
    #if (GPT_GPT12_USED == STD_ON)
    /* If used channel is from GPT12 */
    /* [cover parentID={46A16DBF-FA26-4133-968A-F8DDA0EC0E35}]
    Get the GPT12 timer and De-Init it
    [/cover] */
    LocalGptGpt12TimerInfo = GptChannelPtr->GptGpt12TimerInfo;
    
    TimerNumber = LocalGptGpt12TimerInfo->TimerId;
    
    Mcu_17_Gpt12_TimerDeInit(TimerNumber);
    
    #endif
  }
  return;
}/* End of Gpt_lResetChannel */
/******************************************************************************/
#endif
/* End of #if (GPT_DEINIT_API == STD_ON) */

#if ((GPT_TIME_REMAINING_API == STD_ON) || (GPT_TIME_ELAPSED_API == STD_ON))
/*******************************************************************************
** Traceability   : [cover parentID={DB439941-CD18-4d31-8ED8-344F07F2A92C}]   **
**                                                                            **
** Syntax         : LOCAL_INLINE boolean Gpt_lCheckChannelStatus              **
**                                      ( const Gpt_ChannelType Channel,      **
**                                        const uint32 CurrentCoreId          **
**                                      )                                     **
**                                                                            **
** Description    : This function checks the current status of the Channel    **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : Channel       - Channel ID                                **
**                  CurrentCoreId - Current Core ID                           **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : Flag (boolean)                                            **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE boolean Gpt_lCheckChannelStatus (const Gpt_ChannelType Channel,
                                                    const uint32 CurrentCoreId)
{
  uint32 ChannelStatus;
  boolean Flag = (boolean)FALSE;

  ChannelStatus = 
                  Gpt_ThreadSafeData[CurrentCoreId]->Gpt_ChannelStatusPtr[Channel];

  if ((ChannelStatus == GPT_CHANNEL_RUNNING) || 
      (ChannelStatus == GPT_CHANNEL_STOPPED) || 
      (ChannelStatus == GPT_CHANNEL_EXPIRED))
  {
    Flag = (boolean)TRUE;
  }

  return Flag;
}/* End of Gpt_lCheckChannelStatus */
/******************************************************************************/
#endif
/* End of #if (GPT_TIME_REMAINING_API == STD_ON) ||
              (GPT_TIME_ELAPSED_API == STD_ON) */

#if (((GPT_TIME_ELAPSED_API == STD_ON)  || (GPT_TIME_REMAINING_API == STD_ON)) \
      && ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON)))
/*******************************************************************************
** Traceability   : [cover parentID={7B82FC1B-88A0-4a01-9C95-5CAAE75C7C82}]   **
**                                                                            **
** Syntax         : static uint32 Gpt_lGetTimeDetCheck                        **
**                                          (                                 **
**                                            const Gpt_ChannelType Channel,  **
**                                            const uint8 Gpt_Sid,            **
**                                            const uint32 CoreId             **
**                                          )                                 **
**                                                                            **
** Description    : Service to check DET errors in                            **
**                  Gpt_GetTimeElapsed and Gpt_GetTimeRemaining API's         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : Channel       - Channel ID                                **
**                  Gpt_Sid       - Service id of the caller API              **
**                  CoreId        - Core ID                                   **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : IErrVal (uint32)                                          **
**                                                                            **
*******************************************************************************/
static uint32 Gpt_lGetTimeDetCheck  (
  const Gpt_ChannelType Channel,
  const uint8 Gpt_Sid,
  const uint32 CoreId
)
{
  uint32 IErrVal = GPT_E_DET_NO_ERR;
  /* [cover parentID={07B04CE2-E31F-4167-A17D-BF1EC2D8197A}]
  Check for DETs
  [/cover] */

  /* [cover parentID={EB019436-0E01-4e4f-B355-35FDB5D0CC6E}]
  Is the driver initialized from the current core
  [/cover] */
  if (GPT_DRIVER_INITIALIZED != 
      Mcal_GetBitAtomic(Gpt_DriverStatus, GPT_CORE_BITPOS(CoreId), 
                        GPT_CORE_STATUS_LEN))
  {
    /* [cover parentID={0CC0B770-0CC8-47d2-B484-8F83A6627818}]
    Report to Det
    [/cover] */
    Gpt_lReportError(Gpt_Sid, GPT_E_UNINIT);

    IErrVal = GPT_E_DET_ERR;
  }
  /* [cover parentID={98C39CB8-9279-4dfd-B178-05DC756A88A5}]
  Is 'Channel' within valid range
  [/cover] */
  else if ( Channel >= GPT_MAX_CHANNELS )
  {
    /* [cover parentID={590AD873-02C1-4090-8935-3416F81D72E2}]
    Report to Det
    [/cover] */
    Gpt_lReportError(Gpt_Sid, GPT_E_PARAM_CHANNEL);

    IErrVal = GPT_E_DET_ERR;
  }
  /* [cover parentID={37A0C848-6A92-467d-B830-90EA7754218A}]
  Otherwise
  [/cover] */
  else
  {

    #if (GPT_READ_ACROSS_CORES == STD_OFF)
    #if ((GPT_SAFETY_ENABLE == STD_ON) || \
    (GPT_MULTICORE_ERROR_DETECT == STD_ON))
    /* [cover parentID={829C46AB-FCCE-41c6-9840-4CFFB57AB1F7}]
    Multicore
    [/cover] */
    /* Check is the channel present in current core */
    /* [cover parentID={9263684E-8DDD-42d3-A607-52748E77FDB1}]
    Check for multicore related DETs
    [/cover] */
    IErrVal = Gpt_lMulCoreChannelDetCheck(CoreId, Channel, Gpt_Sid);
    #endif
    #endif
  }

  return IErrVal;
}/* End of Gpt_lGetTimeDetCheck */
/******************************************************************************/
#endif
/* End of #if (((GPT_TIME_ELAPSED_API == STD_ON)    || \
                (GPT_TIME_REMAINING_API == STD_ON)) && \
                ((GPT_SAFETY_ENABLE == STD_ON)      || \
                (GPT_DEV_ERROR_DETECT == STD_ON)))  */

#if ((GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) && \
    ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON)))
/*******************************************************************************
** Traceability   : [cover parentID={E506FB4F-BFA0-4c1f-9DDF-1C2DC726C4F1}]   **
**                                                                            **
** Syntax         : static uint32 Gpt_lNotifDetCheck                          **
**                                          (                                 **
**                                            const Gpt_ChannelType Channel,  **
**                                            const uint8 Gpt_Sid,            **
**                                            const uint32 CurrentCoreId      **
**                                          )                                 **
**                                                                            **
** Description    : Service to check DET errors in Gpt_EnableNotification     **
**                  and Gpt_DisableNotification API's                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : Channel       - Channel ID                                **
**                  Gpt_Sid       - Service id of the caller API              **
**                  CurrentCoreId - Current Core ID                           **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : IErrVal (uint32)                                          **
**                                                                            **
*******************************************************************************/
static uint32 Gpt_lNotifDetCheck (
                                    const Gpt_ChannelType Channel,  
                                    const uint8 Gpt_Sid,            
                                    const uint32 CurrentCoreId      
                                  )
{
  const Gpt_CoreConfigType *LocalCoreConfigPtr;
  uint32                   IErrVal  = GPT_E_DET_NO_ERR;
  Gpt_ChannelType          LocalChannel;
  /* [cover parentID={5DE385A8-9F8A-409d-9550-788C4FC0F607}]
  Check for DETs
  [/cover] */

  /* [cover parentID={698B214C-B986-4ab1-8E3C-C8ECA39A57CA}]
  Check if driver was initialised from the current core
  [/cover] */
  /* Check if driver was initialized from the current core */
  if (GPT_DRIVER_INITIALIZED != 
      Mcal_GetBitAtomic(Gpt_DriverStatus, GPT_CORE_BITPOS(CurrentCoreId), 
                        GPT_CORE_STATUS_LEN))
  {
    /* [cover parentID={036AC42A-A9EF-4dfd-AEF6-9ED8130654C4}]
    Report DET
    [/cover] */
    Gpt_lReportError( Gpt_Sid, GPT_E_UNINIT);

    IErrVal = GPT_E_DET_ERR;
  }
  /* [cover parentID={8C94A947-5D0C-45d3-9794-EB6AC1545A0E}]
  Check if 'Channel' within valid range
  [/cover] */
  else if ( Channel >= GPT_MAX_CHANNELS )
  {
    /* [cover parentID={ADC7ED13-A6A1-4a2e-B8F4-B835D57A611A}]
    Report DET
    [/cover] */
    Gpt_lReportError(Gpt_Sid, GPT_E_PARAM_CHANNEL);

    IErrVal = GPT_E_DET_ERR;
  }
  /* [cover parentID={0C674858-1CAA-4bcd-BBD3-DDBA3D8B4FF3}]
  Set error flag as No error
  [/cover] */
  /* [cover parentID={F34070A9-B067-4296-BB56-E4162FFA5236}]
  Otherwise
  [/cover] */
  else
  {
    
    
    #if ((GPT_SAFETY_ENABLE == STD_ON) || \
    (GPT_MULTICORE_ERROR_DETECT == STD_ON))
    /* [cover parentID={BB1E5590-2A8D-47be-9981-5FFF5F689B09}]
    Is Multi Core?
    [/cover] */
    /* [cover parentID={76EAB8E9-EB9D-4c1a-AA6D-9CC025EE6359}]
    MultiCore with SAFETY ENABLED or MultiCore DET Reporting ON
    [/cover] */
    /* [cover parentID={D2E2F6A9-E3FB-43d3-9C77-D582240FDD6A}]
    Check for Multi Core related DETs and set error flag accordingly
    [/cover] */
    /* Check is channel present in current core */
    IErrVal = Gpt_lMulCoreChannelDetCheck(CurrentCoreId, Channel, Gpt_Sid);
    #endif
  }

  /* [cover parentID={5D137EB3-79BF-48dd-88F9-8C461AEE6A17}]
  Are there any errors?
  [/cover] */
  if (IErrVal != GPT_E_DET_ERR)
  {
    /* Get the pointer to the current core configuration */
    LocalCoreConfigPtr = GPT_GET_CORECONFIGPTR(CurrentCoreId);
    /* [cover parentID={B71913EF-64EE-4731-8C32-D9F21F94A412}]
    Set error flag as No error
    [/cover] */
    /* [cover parentID={85A7A82F-1F0B-4d14-B41C-45C06CE94429}]
    Multi Core or Single Core
    [/cover] */
    #if (GPT_MAX_CORE_USED > 1U)
    LocalChannel = LocalCoreConfigPtr->Gpt_ChannelIndexPtr[Channel];
    /* [cover parentID={23B992AA-5803-4873-80CB-6AC3C19B12DB}]
    Single Core
    [/cover] */
    #else
    /* [cover parentID={14B0E0FA-9E85-45c4-A463-58154F525540}]
      Use the channel as is, no indexing required
      [/cover] */
    LocalChannel = Channel;
    #endif

    /* [cover parentID={B219B1DA-2A94-49af-91AA-3A7294C76E1F}]
    Is notification function valid?
    [/cover] */
    if (NULL_PTR == 
        LocalCoreConfigPtr->ChannelConfigPtr[LocalChannel].GptNotificationPtr)
    {
      /* [cover parentID={1D7C9CF1-78E0-457e-8558-2875F450DD9B}]
      Report to Det
      [/cover] */
      Gpt_lReportError(Gpt_Sid, GPT_E_PARAM_CHANNEL);

      IErrVal = GPT_E_DET_ERR; /* Set IErrVal */
    }
  }

  return IErrVal;
}/* End of Gpt_lNotifDetCheck */
/******************************************************************************/
#endif
/* End of #if ((GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) && \
                                      ((GPT_SAFETY_ENABLE == STD_ON) || \
                                           (GPT_DEV_ERROR_DETECT == STD_ON))) */

#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={2D1EB6BA-0597-486f-98C5-E7B96BCE0C44}]   **
**                                                                            **
** Syntax         : LOCAL_INLINE void Gpt_lSetNormalMode                      **
**                                          (                                 **
**                              const Gpt_CoreConfigType *LocalCoreConfigPtr, **
**                              uint32 CurrentCoreId                          **
**                                          )                                 **
**                                                                            **
** Description    : Service to switch from sleep to normal mode               **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : LocalCoreConfigPtr                                        **
**                    - Pointer to current core configuration                 **
**                  CurrentCoreId                                             **
**                    - Current Core ID                                       **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/

LOCAL_INLINE void Gpt_lSetNormalMode (
          const Gpt_CoreConfigType *LocalCoreConfigPtr, 
          const uint32 CurrentCoreId)
{
  
  /* [cover parentID={C9609AD6-1290-40fa-B8C3-7C26E1AD4F9A}]
  Is driver in Sleep Mode in current core?
  [/cover] */
  if (GPT_MODE_SLEEP == Gpt_ThreadSafeData[CurrentCoreId]->Gpt_DriverMode)
  {
    #if (GPT_TOM_USED == STD_ON) || (GPT_ATOM_USED == STD_ON)
    /* Report wakeup source is ON
    [cover parentID={A0D937A7-A0D0-4065-9F59-9D1463A9504F}][/cover]
    */
    #if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
    /* For all normal channels in the core
    [cover parentID={85D5F8D1-62BA-4356-AA95-BBF754CDB174}][/cover]
    */
    for (uint8 Counter = (uint8)0x0U;
         /* Till max channels in core */
         (Counter < LocalCoreConfigPtr->Gpt_MaxNormalChannels);
         Counter++ )
    {
      /*
      [cover parentID={3E82C127-506C-4c13-91E3-ECEEFA98D0F4}]
      Check is Channel wakeup capable
      [/cover] */
      if ((&LocalCoreConfigPtr->ChannelConfigPtr[Counter])-> 
          GptEnableWakeupState == (boolean)TRUE)
      {
        /*
        [cover parentID={564F9C15-C8CF-4c5b-BFFB-117A9E971727}]
        Disable the wake up interrupt only if
        disable wakeup is requested already
        [/cover]
        */
        if ((Gpt_ThreadSafeData[CurrentCoreId]-> Gpt_FlagPtr[Counter] & 
             GPT_WAKEUP_MSK) == GPT_WAKEUP_DISABLED)
        {
          /*
          Enabled/Disable Notification API is ON:
          [cover parentID={E427D81C-1E08-4944-B9DA-451B5710B8A8}]
          [/cover]
          */
          #if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
          /*
          [cover parentID={7EA3DFCD-430B-4d61-B8F5-25A4E084F1D8}]
          Disable the wake up interrupt:
          Disable the interrupt if notification is disabled
          [/cover]
          */
          if ((Gpt_ThreadSafeData[CurrentCoreId]-> Gpt_FlagPtr[Counter] & 
               GPT_NOTIF_MSK) == GPT_DISABLE_NOTIF)
          #endif
          {
            /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic used
            due to PBConfigStructure and is within allowed range.*/
            /* [cover parentID={F7A657DC-D61C-4331-B6C1-8C8ABD5781E0}]
            Disable Interrupt
            [/cover] */
            Gpt_lGtmIrqModify(((LocalCoreConfigPtr->ChannelConfigPtr) + \
                               Counter), GPT_DISABLE_IRQ);
          }
        }
      }
      /* [cover parentID={9AF29F9C-8680-403e-A043-F1F71FCD7E43}]
      Stopped channels while entering sleep mode
      are not restarted automatically
      [/cover] */
    }
    #endif
    #endif 
    /* [cover parentID={4D25D8EA-EE93-4030-97D7-27918C555097}]
    Start the Predef timer only if switch to Normal mode is requested
    from master core
    [/cover] */
    if (CurrentCoreId == MCAL_MASTER_COREID)
    {
      /* [cover parentID={DF19F25A-1E65-4689-9BD4-E93851AC5EF5}]
      1us Predef Timer ON
      [/cover] */
      #if ((GPT_PREDEF_TIMER_1US_16BIT_EN == STD_ON)   || \
          (GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON)    || \
          (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))
      /* [cover parentID={5E413B97-C1D6-45c9-BA08-CF6C0649D44D}]
      Start 1Us Predef Timers
      [/cover] */
      Gpt_lGtmStart1UsPredefTimer(LocalCoreConfigPtr);
      #endif

      /* [cover parentID={92CF6B03-98E9-4567-ADB3-2F239FE2E079}]
      100us Predef Timer ON
      [/cover] */
      #if (GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON)
      /* [cover parentID={6BBD4B1F-8D6C-49ea-B340-E9CA834C646B}]
      Start 100Us Predef Timer
      [/cover] */
      Gpt_lGtmStart100UsPredefTimer(LocalCoreConfigPtr);
      #endif
    }
  }
  UNUSED_PARAMETER(*LocalCoreConfigPtr);
  /* Update the driver state to GPT_MODE_NORMAL*/
  Gpt_ThreadSafeData[CurrentCoreId]->Gpt_DriverMode = GPT_MODE_NORMAL;
}/* End of Gpt_lSetNormalMode */

/*******************************************************************************
** Traceability   : [cover parentID={3DFD6E5E-958B-4be6-BB4F-1B46C889B427}]   **
**                                                                            **
** Syntax         : LOCAL_INLINE void Gpt_lSetSleepMode                       **
**                                          (                                 **
**                              const Gpt_CoreConfigType *LocalCoreConfigPtr, **
**                              uint32 CurrentCoreId                          **
**                                          )                                 **
**                                                                            **
** Description    : Service to switch from normal to sleep mode               **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : LocalCoreConfigPtr                                        **
**                    - Pointer to current core configuration                 **
**                  CurrentCoreId                                             **
**                    - Current Core ID                                       **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Gpt_lSetSleepMode( 
                                     const Gpt_CoreConfigType *LocalCoreConfigPtr, 
                                     const uint32 CurrentCoreId 
                                   )
{
  /* [cover parentID={3A996929-C75D-4017-B75D-9E3F3EA79227}]
  Till max channels in core
  [/cover] */
  for (uint8 Counter = (uint8)0x0U;
       (Counter < LocalCoreConfigPtr->Gpt_MaxNormalChannels);
       Counter++ )
  {
   
    /* [cover parentID={65B5FF9C-87C6-45e0-BEA6-625E3163DCF1}]
    Report Wakeup Source is ON
    [/cover] */
    #if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
    /* Is cahnnel wakeup capable
    [cover parentID={61D21C24-4E58-497a-8C17-A7304A6795D2}]
    [/cover]*/
    if(((Gpt_ThreadSafeData[CurrentCoreId]->Gpt_FlagPtr[Counter]) 
        & GPT_WAKEUP_MSK) == GPT_WAKEUP_MSK)
    {
     
    /* [cover parentID={C0E57BAF-CC0A-4574-9DE0-530902568CB5}]
      GTM used
      [/cover] */
      #if (GPT_TOM_USED == STD_ON) || (GPT_ATOM_USED == STD_ON)
      /* [cover parentID={73AC7EC7-0FC8-413b-96F4-EED1EB022110}]
      Enabled/Disable Notification API is ON
      [/cover] */
      #if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
      /* [cover parentID={76D0CC5E-8F8F-4b79-A2CC-0C605569C1B0}]
      Enable interrupt only if not already enabled by notification
      and enable wakeup flag is in wakeup requested state
      [/cover] */
      if ((Gpt_ThreadSafeData[CurrentCoreId]->
           Gpt_FlagPtr[Counter] & GPT_NOTIF_MSK) == GPT_DISABLE_NOTIF)
      #endif
      {
        /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic used
        due to PBConfigStructure and is within allowed range.*/
        /* [cover parentID={34CA10CA-562C-4fb2-B4BF-683CCEA231E4}]
        Enable Interrupt
        [/cover] */

        Gpt_lGtmIrqModify(((LocalCoreConfigPtr->ChannelConfigPtr) \
                           + Counter), GPT_ENABLE_IRQ);
      }
      #endif

    }
    /* Stop all non-wakeup capable channels */
    /* [cover parentID={059E61F8-8129-427a-B6DC-D6AB6CDFFAE1}]
    Stop all non-wakeup capable channels
    [/cover] */
    else
    #endif
   
    {
      /* [cover parentID={059E61F8-8129-427a-B6DC-D6AB6CDFFAE1}]
      Is channel running
      [/cover] */
      if ((GPT_CHANNEL_RUNNING == Gpt_ThreadSafeData[CurrentCoreId]->
           Gpt_ChannelStatusPtr[Counter]))
      {
        /* [cover parentID={230C7BFE-F09D-4313-B8E3-13203F3D0A69}]
        GPT12 used
        [/cover] */
        #if (GPT_GPT12_USED == STD_ON)
        /* [cover parentID={E17B212A-927F-41ab-BAD1-B77856FD91B5}]
        Is the channel using GPT12
        [/cover] */
        if(LocalCoreConfigPtr->ChannelConfigPtr[Counter].
                                              GptGpt12TimerInfo != NULL_PTR)
        {
          /* [cover parentID={A102A34A-7D28-4ad8-80F5-A0DF93BEFD6F}]
          Stop the channel
          [/cover] */
          Gpt_lGpt12StopTimer(Counter, CurrentCoreId);
        }
        else
        #endif
        {
          
          #if (GPT_TOM_USED == STD_ON) || (GPT_ATOM_USED == STD_ON)
           /* [cover parentID={FA403625-01F7-49ab-BF50-227CA806DFDF}]
          GTM used
          [/cover] */
          /* [cover parentID={0B7E6701-21F8-406a-A7FD-C1E7C1EA31C9}]
          Stop the required timer channel
          [/cover] */
          Gpt_lGtmStopTimer(Counter, CurrentCoreId);
          #endif
        }
          /* [cover parentID={77B829CC-AB53-41d7-AE60-BB299ABF5C03}]
          Set the channel status to 'STOPPED'
          [/cover] */
          Gpt_ThreadSafeData[CurrentCoreId]->Gpt_ChannelStatusPtr[Counter] 
            = GPT_CHANNEL_STOPPED;
        
      }
    }
  }
  /*
  Stop all enabled GPT Predef Timer(s) only if 'Sleep' is requested from
  the master core
   */
  /* [cover parentID={2C576068-873F-4366-9236-4CFF072894B2}]
  Is current core master core?
  [/cover] */
  if (CurrentCoreId == MCAL_MASTER_COREID)
  {
    /* [cover parentID={8586C560-0C80-44af-99A9-65AAAA06270C}]
    1us Predef Timer ON
    [/cover] */
    #if ((GPT_PREDEF_TIMER_1US_16BIT_EN == STD_ON) || \
    (GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON)  || \
    (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))
    /* [cover parentID={3201453A-F495-4d20-86D1-582F098ACE7C}]
    Stop 1Us Predef Timers
    [/cover] */
    Gpt_lGtmStop1UsPredefTimer(LocalCoreConfigPtr, GPT_SID_SET_MODE);
    #endif

    /* [cover parentID={3699DDAE-A492-4b39-8F22-E0DCCD481947}]
    100us Predef Timer ON
    [/cover] */
    #if (GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON)
    /* [cover parentID={38B9500C-8BD7-4ae8-B895-2FA1E3F29939}]
    Stop 100Us Predef Timer
    [/cover] */
    Gpt_lGtmStop100UsPredefTimer(LocalCoreConfigPtr, GPT_SID_SET_MODE);
    #endif
  }

  /* Update the driver state to GPT_MODE_SLEEP  */
  Gpt_ThreadSafeData[CurrentCoreId]->Gpt_DriverMode = GPT_MODE_SLEEP;
} /* End of Gpt_lSetSleepMode */

#if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
/*******************************************************************************
** Traceability   : [cover parentID={7914261E-0BF1-4cd0-AD60-E40369140303}]   **
**                                                                            **
** Syntax         : static uint32 Gpt_lSetModeDetCheck                        **
**                                          (                                 **
**                                            const Gpt_ModeType Mode,        **
**                                            const uint32 CurrentCoreId      **
**                                          )                                 **
**                                                                            **
** Description    : Service to check DET errors in Gpt_SetMode                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : Mode (GPT_MODE_NORMAL/GPT_MODE_SLEEP)                     **
**                  CurrentCoreId - Current Core ID                           **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : IErrVal (uint32)                                          **
**                                                                            **
*******************************************************************************/
static uint32 Gpt_lSetModeDetCheck (
                                     const Gpt_ModeType Mode,  
                                     const uint32 CurrentCoreId
                                   )
{
  /* [cover parentID={00585C61-3C17-4e5a-B02A-D973194D482F}]
  Check DETs
  [/cover] */
  uint32 IErrVal = GPT_E_DET_NO_ERR;
  /*
  Driver not initialized in the current core
  */
  /* Check if driver was initialized from the current core */
  /* Check if driver was initialized from the current core */
  if (GPT_DRIVER_INITIALIZED != 
      Mcal_GetBitAtomic(Gpt_DriverStatus, GPT_CORE_BITPOS(CurrentCoreId), 
                        GPT_CORE_STATUS_LEN))
  {
    /* [cover parentID={C3E1835C-2E62-40e8-BDCD-3DBFD5024B33}]
        Report to  DET
    [/cover] */
    Gpt_lReportError(GPT_SID_SET_MODE, GPT_E_UNINIT);
    IErrVal = GPT_E_DET_ERR;
  }
  /* Mode passed is invalid */
  /* Check for invalid mode passed as parameter */
  else if (!((Mode == GPT_MODE_NORMAL) || (Mode == GPT_MODE_SLEEP)))
  {
    /* [cover parentID={5B10791F-652C-44dd-AA14-526CFF198A47}]
        Report to  DET
       [/cover] */
    Gpt_lReportError(GPT_SID_SET_MODE, GPT_E_PARAM_MODE);
    IErrVal = GPT_E_DET_ERR;
  }
  else
  {
    /* No Action required */
  }

  return IErrVal;
}/* End of Gpt_lSetModeDetCheck */
/******************************************************************************/
#endif
/* #if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON)) */
#endif
/* #if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) */

#if ((GPT_ONESHOT_USED == STD_ON) && ((GPT_TOM_USED == STD_ON) || \
    (GPT_ATOM_USED == STD_ON)))
/*******************************************************************************
** Traceability   : [cover parentID={891300A2-50F1-40c8-B91F-50D5AFEB9D93}]   **
**                                                                            **
** Syntax         : LOCAL_INLINE void Gpt_lGtmHandleOsm                       **
**                         (const Gpt_ChannelConfigType *const GptChannelPtr) **
**                                                                            **
** Description    : This function stops a TOM/ATOM channel in One Shot mode   **
**                  and reset the CN0 register value.                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant for different timer channel                     **
**                                                                            **
** Parameters(in) : GptChannelPtr - Pointer to core specific channel config   **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Gpt_lGtmHandleOsm
                            (const Gpt_ChannelConfigType *const GptChannelPtr)
{
  const Mcu_17_Gtm_TomAtomChConfigType *LocalGptGtmTimerInfo;

  #if (GPT_TOM_USED == STD_ON)
  Ifx_GTM_TOM_CH *TomChannelRegPtr;     /* Ptr to TOM Channel Register   */
  #endif

  #if (GPT_ATOM_USED == STD_ON)
  Ifx_GTM_ATOM_CH *AtomChannelRegPtr;   /* Ptr to ATOM Channel Register  */
  #endif

  uint8 ModuleNumber;                        /* Holds the module number  */
  uint8 ChannelNumber;                       /* Holds the channel number */

  /* The GptGtmTimerInfo contains properties of TOM/ATOM channel used */
  LocalGptGtmTimerInfo = GptChannelPtr->GptGtmTimerInfo;

  ModuleNumber = (uint8)((LocalGptGtmTimerInfo->TimerId & 
                          GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);

  ChannelNumber = (uint8)((LocalGptGtmTimerInfo->TimerId &
                           GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);

  /* [cover parentID={CBF7E0C1-8842-4251-B6B7-52FBF03737A0}]
  TOM is used
  [/cover] */
  #if (GPT_TOM_USED == STD_ON)
  /* [cover parentID={7854B398-F712-49b9-8B08-A91C965562A3}]
  Is the channel a TOM channel?
  [/cover] */
  if (LocalGptGtmTimerInfo->TimerType == MCU_GTM_TIMER_TOM)
  {
    /* MISRA2012_RULE_11_3_JUSTIFICATION: Pointer type recasting done
       for ease of access to channels registers.*/
    /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and
       integer type. Permitted for special function registers.*/
    /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
       by violating this MISRA rule.*/
    /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic used due to
       PBConfigStructure and is within allowed range.*/
    TomChannelRegPtr = GTM_TOM_CH_POINTER(ModuleNumber, ChannelNumber);

    /* [cover parentID={80410C36-8DB5-4b44-8FDE-85CE3743844D}]
    Disable the TOM timer channel
    [/cover] */
    Mcu_17_Gtm_TomChannelDisable(ModuleNumber, ChannelNumber);

    /* [cover parentID={49F5684F-92A3-4fbe-BAA3-6A0D09538DD7}]
      Set CN0 equal to CM0
      [/cover] */
    TomChannelRegPtr->CN0.U = TomChannelRegPtr->CM0.U;
  }
  #endif
  /* End of #if (GPT_TOM_USED == STD_ON) */

  /* [cover parentID={9247180F-0525-43dc-945D-6735FD61A445}]
  ATOM is used
  [/cover] */
  #if (GPT_ATOM_USED == STD_ON)
  /* Check the Module Type */
  /* [cover parentID={F8A3303F-362B-4377-A157-CAF527194509}]
  Is the channel a ATOM channel?
  [/cover] */
  if (LocalGptGtmTimerInfo->TimerType == MCU_GTM_TIMER_ATOM)
  {
    /* MISRA2012_RULE_11_3_JUSTIFICATION: Pointer type recasting done
       for ease of access to channels registers.*/
    /* MISRA2012_RULE_11_4_JUSTIFICATION: conversion between pointer and
       integer type. Permitted for special function registers.*/
    /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
       by violating this MISRA rule.*/
    /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic used due to
       PBConfigStructure and is within allowed range.*/
    AtomChannelRegPtr = GTM_ATOM_CH_POINTER(ModuleNumber, ChannelNumber);

    /* [cover parentID={A9FBD368-489A-4cb9-99A2-BA7EF48E49AE}]
    Disable the ATOM timer channel
    [/cover] */
    Mcu_17_Gtm_AtomChannelDisable(ModuleNumber, ChannelNumber);

    /* [cover parentID={270A2501-9CB0-487f-8996-1DD1AB12C501}]
      Set CN0 equal to CM0
      [/cover] */
    AtomChannelRegPtr->CN0.U = AtomChannelRegPtr->CM0.U;
  }
  #endif
  /* End of #if (GPT_ATOM_USED == STD_ON) */

  return;
}/* End of Gpt_lGtmHandleOsm */
/******************************************************************************/
#endif
/* End of #if (GPT_ONESHOT_USED == STD_ON) */

#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={4583DCB9-4D41-4da0-A822-C3426A4D494A}]   **
**                                                                            **
** Syntax         : LOCAL_INLINE void Gpt_lHandleNotifCall                    **
**                             (                                              **
**                               const Gpt_ChannelConfigType *GptChannelPtr,  **
**                               const Gpt_ChannelType Channel,               **
**                               const uint32 CurrentCoreId                   **
**                             )                                              **
**                                                                            **
** Description    : This function checks if notification is enabled and       **
**                  driver mode is GPT_MODE_NORMAL and invokes the            **
**                  notification function accordingly                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : GptChannelPtr - Pointer to core specific channel config   **
**                  CurrentCoreId - Current Core ID                           **
**                  Channel       - Channel ID                                **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Gpt_lHandleNotifCall
                                  (
                                    const Gpt_ChannelConfigType *GptChannelPtr,
                                    const Gpt_ChannelType Channel,
                                    const uint32 CurrentCoreId
                                  )
{
  uint8 NotifFlag = (uint8)(Gpt_ThreadSafeData[CurrentCoreId]->
                            Gpt_FlagPtr[Channel] & (uint32)0x1U);

  /* Is callback possible? */
  if ((Gpt_ThreadSafeData[CurrentCoreId]->Gpt_DriverMode == GPT_MODE_NORMAL) 
      && (NotifFlag == 0x1U))
  {
    /* Call Notification if in normal mode and enabled */
    (GptChannelPtr->GptNotificationPtr)();
  }

  return;
}/* End of Gpt_lHandleNotifCall */
/******************************************************************************/
#endif
/* End of #if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)  */

#if (GPT_ONESHOT_USED == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={4BF3D047-3045-4fe8-9C0F-724780DA9C8D}]   **
**                                                                            **
** Syntax         : LOCAL_INLINE boolean Gpt_lHandleOsmChannel                **
**                             (                                              **
**                               const Gpt_ChannelConfigType *GptChannelPtr,  **
**                               const Gpt_ChannelType Channel,               **
**                               const uint32 CurrentCoreId                   **
**                             )                                              **
**                                                                            **
** Description    : This function checks if the GPT channel mode of operation **
**                  is ONE SHOT and accordingly stops, resets and updates the **
**                  status of the channel                                     **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant for different channel                           **
**                                                                            **
** Parameters(in) : GptChannelPtr - Pointer to core specific channel config   **
**                  CurrentCoreId - Current Core ID                           **
**                  Channel       - Channel ID                                **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Gpt_lHandleOsmChannel
                                  (
                                    const Gpt_ChannelConfigType *GptChannelPtr,
                                    const Gpt_ChannelType Channel,
                                    const uint32 CurrentCoreId
                                  )
{
  /*
  [cover parentID={C1981B39-7321-4680-A85C-069A7156636D}]
  Is channel in one shot mode?
  [/cover]
  */
  if (GPT_MODE_ONESHOT == GptChannelPtr->GptChannelMode)
  {
    
      /*
    [cover parentID={B9288E62-5249-4f42-8127-E97A76ED64F4}]
    GPT12 used
    [/cover]
    */
    #if (GPT_GPT12_USED == STD_ON)
    /*
    [cover parentID={351D4933-B57E-4699-894C-DF633E5F2046}]
    Is channel GPT12's
    [/cover]
    */
    if(GptChannelPtr -> GptGpt12TimerInfo != NULL_PTR)
    {
       /*
      [cover parentID={9985B5BF-9510-4570-A140-B9BE2305F5A2}]
      Handle one shot mode
      [/cover]
      */
      Gpt_lGpt12HandleOsm(GptChannelPtr);
    }
    else
    #endif
    {
      /*
      [cover parentID={B13B7978-9197-42d6-8CFD-497EACB839E0}]
      GTM used
      [/cover]
      */
      #if (GPT_TOM_USED == STD_ON) || (GPT_ATOM_USED == STD_ON)
      /* [cover parentID={9F7B20F4-9A6B-4ee4-8318-09E34E0C2607}]
      Handle one shot mode
      [/cover] */
      Gpt_lGtmHandleOsm(GptChannelPtr);
      
      #endif
    }
    /*
    [cover parentID={215BEF93-E40C-4c91-B24C-24A88DFC0AE4}]
    Set the status to expired
    [/cover]
    */
    Gpt_ThreadSafeData[CurrentCoreId]->
    Gpt_ChannelStatusPtr[Channel] = GPT_CHANNEL_EXPIRED;
  }

  return;
}/*End of Gpt_lHandleOsmChannel*/
/******************************************************************************/
#endif
/* End of #if (GPT_ONESHOT_USED == STD_ON)*/

#if ((GPT_ONESHOT_USED == STD_ON) && (GPT_GPT12_USED == STD_ON))
/* #if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) */

/*******************************************************************************
** Traceability   : [cover parentID={21582C81-FE7F-41cd-9543-9D9F61F18E01}]   **
**                                                                            **
** Syntax         : LOCAL_INLINE void Gpt_lGpt12HandleOsm                     **
**                         (const Gpt_ChannelConfigType *const GptChannelPtr) **
**                                                                            **
** Description    : This function stops a TOM/ATOM channel in One Shot mode   **
**                  and reset the CN0 register value.                         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant for different timer channel                     **
**                                                                            **
** Parameters(in) : GptChannelPtr - Pointer to core specific channel config   **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Gpt_lGpt12HandleOsm
                            (const Gpt_ChannelConfigType *const GptChannelPtr) 
{
  Mcu_17_Gpt12_TimerChIdentifierType Timernumber;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: No side effects foreseen by violating
  * this MISRA rule, Gpt12TxConRegPtr is used to access the SFR. 
  * Union is required*/
  volatile Ifx_GPT12_T2CON *Gpt12TxConRegPtr = &GPT120_T2CON;
  
  /* [cover parentID={697B2198-07E3-427b-9E17-5C733A7BB4A7}]
  Is channel in one shot mode?
  [/cover] */
  if (GPT_MODE_ONESHOT == GptChannelPtr->GptChannelMode)
  {
    Timernumber = GptChannelPtr->GptGpt12TimerInfo[0].TimerId;
     
    /* [cover parentID={53A205BA-863D-4497-8D4D-DDF72705393D}]
    Stop the timer
    [/cover] */
    Gpt12TxConRegPtr[Timernumber].U &= GPT_GPT12_STOP_MASK;
    
  }
  
  return;
}
#endif

#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
#if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={0924AAA5-E803-4ce7-A699-23FA2E1A3AA1}]   **
**                                                                            **
** Syntax         : LOCAL_INLINE boolean Gpt_lHandleWakeupEvent               **
**                             (                                              **
**                               const Gpt_ChannelConfigType *GptChannelPtr,  **
**                               const Gpt_ChannelType Channel,               **
**                               const uint32 CurrentCoreId                   **
**                             )                                              **
**                                                                            **
** Description    : This function checks if the WakeUp flag is set            **
**                  for the channel while the GPT Driver is in SLEEP mode.    **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : GptChannelPtr - Pointer to core specific channel config   **
**                  CurrentCoreId - Current Core ID                           **
**                  Channel       - Channel ID                                **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Gpt_lHandleWakeupEvent
                                  (
                                    const Gpt_ChannelConfigType *GptChannelPtr,
                                    const Gpt_ChannelType Channel,
                                    const uint32 CurrentCoreId
                                  )
{
  uint32 WakeupFlag = (Gpt_ThreadSafeData[CurrentCoreId]->
                       Gpt_FlagPtr[Channel] >> (uint32)0x1U) & (uint32)0x1U;

  /* Check is Driver in Sleep mode and wakeup flag for channel is set */
  if ((Gpt_ThreadSafeData[CurrentCoreId]->Gpt_DriverMode == GPT_MODE_SLEEP) 
      && (WakeupFlag == (uint32)0x1U))
  {
    Gpt_ThreadSafeData[CurrentCoreId]->Gpt_WakeupChannelInfo = 
        (uint32)0x1U << (GptChannelPtr->GptChannelWakeupInfo);

    EcuM_CheckWakeup((uint32)0x1U << (GptChannelPtr->GptChannelWakeupInfo));
  }

  return;

}/* End of Gpt_lHandleWakeupEvent */
/******************************************************************************/
#endif /* End of #if (GPT_REPORT_WAKEUP_SOURCE == STD_ON) */
#endif /* End of #if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) */

#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
#if (GPT_TOM_USED == STD_ON) || (GPT_ATOM_USED == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={C7F7138F-72C8-406d-82BF-9B9EB244D86C}]   **
**                                                                            **
** Syntax         : LOCAL_INLINE boolean Gpt_lModeCont                        **
**                                  (const Gpt_ChannelModeType ChannelMode)   **
**                                                                            **
** Description    : This function checks if the channel is in CONTINUOS MODE  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : ChannelMode - GPT channel mode                            **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : True/False                                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE boolean Gpt_lModeCont(const Gpt_ChannelModeType ChannelMode)
{
  boolean RetVal;

  if (ChannelMode == GPT_MODE_CONTINUOUS)
  {
    RetVal = TRUE;
  }
  else
  {
    RetVal = FALSE;
  }

  return RetVal;
}/* End of Gpt_lModeCont */
#endif
#endif
/******************************************************************************/



#if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_MULTICORE_ERROR_DETECT == STD_ON))
#if (GPT_DEINIT_API == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID={DCA9F695-CFD4-4201-88FD-8A14F31173CD}]  **
**                                                                            **
** Syntax         : LOCAL_INLINE uint32 Gpt_lMulCoreDeInitDetCheck            **
**                                     (                                      **
**                                       const uint32 CurrentCoreId,          **
**                                       const uint32 CurrentCoreDriverState  **
**                                     )                                      **
**                                                                            **
**                                                                            **
** Description    : This function performs the DET checks related to DeInit   **
**                  in Multicore environment                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : CurrentCoreId          - Current Core ID                  **
**                  CurrentCoreDriverState - Status of the driver             **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : IErrVal (uint32)                                          **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint32 Gpt_lMulCoreDeInitDetCheck
                                      (
                                        const uint32 CurrentCoreId,
                                        const uint32 CurrentCoreDriverState
                                      )
{
  uint32 IErrVal;

  IErrVal = GPT_E_DET_NO_ERR;
  /* [cover parentID={27663FCE-3F47-456b-AC59-E89550A9F2DE}]
  Is current core the master core?
  [/cover] */
  if (CurrentCoreId == MCAL_MASTER_COREID)
  {
    /* [cover parentID={E873D52E-9FEE-4958-A1DD-9EE48044647E}]
    Is Gpt driver deinitialized in all slave cores?
    [/cover] */
    if (0x0U != 
        ((Gpt_DriverStatus & SLAVE_CORE_STATUS_MASK) ^ 
         (CurrentCoreDriverState << GPT_CORE_BITPOS(MCAL_MASTER_COREID))))
    {
      /* [cover parentID={E1504163-E104-4573-A57F-1DE8C98373E1}]
      Report DET
      [/cover] */
      Gpt_lReportMulticoreError(GPT_SID_DEINIT, GPT_E_SLAVE_INIT);

      IErrVal = GPT_E_DET_ERR;
    }
  }

  return IErrVal;
}
/******************************************************************************/
#endif
/* End of #if (GPT_DEINIT_API == STD_ON) */

/*******************************************************************************
** Traceability    : [cover parentID={A9A5FA85-83D2-4355-B119-18DE16E9351C}]  **
**                                                                            **
** Syntax         : static uint32 Gpt_lMulCoreInitDetCheck                    **
**                                   (                                        **
**                                                                            **
**                                     const uint32 CurrentCoreId             **
**                                   )                                        **
**                                                                            **
** Description    : This function performs the DET checks related to Init in  **
**                  Multicore environment                                     **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : ConfigPtr     - Pointer to the configuration structure    **
**                  CurrentCoreId - Current Core ID                           **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : IErrVal (uint32)                                          **
**                                                                            **
*******************************************************************************/
static uint32 Gpt_lMulCoreInitDetCheck
                                      (
                                        const uint32 CurrentCoreId
                                      )
{
  uint32 IErrVal;
  uint8  BitPos = GPT_CORE_BITPOS(MCAL_MASTER_COREID);

  IErrVal = GPT_E_DET_NO_ERR;
  /* [cover parentID={0A0B50B1-41AE-46f5-91A4-749DA64E037A}]
  Is current core the master core?
  [/cover] */
  if (CurrentCoreId != MCAL_MASTER_COREID)
  {
    /* [cover parentID={DB438167-D886-433d-BE90-8A31B5847E41}]
    Is slave core initialization is attempted before master core?
    [/cover] */
    /* [cover parentID={E3F5419B-FC42-449d-8BD7-ACF13EBA46FB}]
    GPT Initialization and Deinitialization
    [/cover] */
    if (GPT_DRIVER_INITIALIZED != 
             Mcal_GetBitAtomic(Gpt_DriverStatus, BitPos, GPT_CORE_STATUS_LEN))
    {
      /* [cover parentID={C8018679-AB8E-4955-AEF6-5EC5D5D25B34}]
      Report DET
      [/cover] */
      Gpt_lReportMulticoreError(GPT_SID_INIT, GPT_E_MASTER_UNINIT);

      IErrVal = GPT_E_DET_ERR;
    }
        /* [cover parentID={71C05B3D-D421-4aeb-872E-2A5C92C93D98}]
    Is Gpt configured in the current core?
    [/cover] */
    else if(GPT_GET_CORECONFIGPTR(CurrentCoreId) == NULL_PTR)
    {
      /* [cover parentID={C8EAFBB5-0200-40e9-B565-15EDEAAB085F}]
      Report DET
      [/cover] */
      Gpt_lReportMulticoreError(GPT_SID_INIT, GPT_E_NOT_CONFIGURED);

      IErrVal = GPT_E_DET_ERR;
    }
    else
    {
      /* No Action Required */
    }
  }
  return IErrVal;
}
/******************************************************************************/

/*******************************************************************************
** Traceability    : [cover parentID={DAB6895E-F014-4c67-BC11-A7DF78A99E88}]  **
**                                                                            **
** Syntax         : static uint32 Gpt_lMulCoreChannelDetCheck                 **
**                                      (                                     **
**                                        const uint32 CurrentCoreId,         **
**                                        const Gpt_ChannelType Channel,      **
**                                        const uint8 Gpt_Sid                 **
**                                      )                                     **
**                                                                            **
** Description    : This function performs the DET checks related to channel  **
**                  in Multicore environment                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : CurrentCoreId - Current Core ID                           **
**                  Channel       - Channel ID                                **
**                  Gpt_Sid       - Service id of the caller API              **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : IErrVal (uint32)                                          **
**                                                                            **
*******************************************************************************/
static uint32 Gpt_lMulCoreChannelDetCheck (
                                            const uint32 CurrentCoreId,
                                            const Gpt_ChannelType Channel,
                                            const uint8 Gpt_Sid
                                          )
{
  const Gpt_CoreConfigType  *LocalCoreConfigPtr;
  uint32                    IErrVal;
  #if (GPT_MAX_CORE_USED > 1U)
  Gpt_ChannelType           LocalChannel;
  #endif

  IErrVal = GPT_E_DET_NO_ERR;

  /* Get the pointer to the current core configuration */
  LocalCoreConfigPtr = GPT_GET_CORECONFIGPTR(CurrentCoreId);

  /* [cover parentID={0B0530F6-4037-43ee-A7AA-AA1720135BF2}]
  Is any normal channel present in the current core?
  [/cover] */
  /* Check if any normal channel present in the current core */
  if (LocalCoreConfigPtr->ChannelConfigPtr == NULL_PTR)
  {
    /* [cover parentID={4CBB3A13-20F4-42da-A6E2-0D60F8DE0DC1}]
    Report DET
    [/cover] */
    /* Report to DET as no normal channels are mapped to the current core */
    Gpt_lReportMulticoreError(Gpt_Sid, GPT_E_CORE_CHANNEL_MISMATCH);

    IErrVal = GPT_E_DET_ERR; /* Set Error Flag */
  }

  /* [cover parentID={AD1D923D-AF5F-4a7a-B19F-ACB25909B8EF}]
  MULTICORE
  [/cover] */
  #if (GPT_MAX_CORE_USED > 1U)
  else
  {
    /* Get the offset for this channel from configuration */
    LocalChannel = LocalCoreConfigPtr->Gpt_ChannelIndexPtr[Channel];

    /* [cover parentID={37232C4D-454A-40cb-8C12-C68F8ADCCEDC}]
    Is channel mapped to current core?
    [/cover] */
    /* Check if channel is mapped to current core */
    if (LocalChannel == GPT_INVALID_CHANNEL)
    {
      /* [cover parentID={39A33243-3161-4f5f-9975-B8AE53FDCC53}]
      Report DET
      [/cover] */
      /* Report to DET */
      Gpt_lReportMulticoreError(Gpt_Sid, GPT_E_CORE_CHANNEL_MISMATCH);

      IErrVal = GPT_E_DET_ERR; /* Set Error Flag */
    }
  }
  #else
  UNUSED_PARAMETER(Channel);
  #endif


  return IErrVal;
}
/******************************************************************************/
#endif
/* End of #if ((GPT_SAFETY_ENABLE == STD_ON) || \
                                            (GPT_DEV_ERROR_DETECT == STD_ON)) */

#if (GPT_MAX_CORE_USED > 1U)
/*******************************************************************************
** Traceability   : [cover parentID={6CAACF42-5329-4720-83F3-68861DF11A96}]   **
**                                                                            **
** Syntax         : LOCAL_INLINE Gpt_ChannelType Gpt_lMulCoreGetChannelInfo   **
**                                    (                                       **
**                                      const uint32 CurrentCoreId,           **
**                                      const Gpt_ChannelType Channel         **
**                                    )                                       **
** Description    : This function returns the channel ID in context to the    **
**                  core                                                      **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : CurrentCoreId - Current Core ID                           **
**                  Channel       - Channel ID                                **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : LocalChannel (Gpt_ChannelType)                            **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Gpt_ChannelType Gpt_lMulCoreGetChannelInfo
                    (const uint32 CurrentCoreId, const Gpt_ChannelType Channel)
{
  const Gpt_CoreConfigType    *LocalCoreConfigPtr;
  Gpt_ChannelType             LocalChannel;

  /* Get the pointer to the current core configuration */
  LocalCoreConfigPtr = GPT_GET_CORECONFIGPTR(CurrentCoreId);

  /* Get the mapped offset for this channel from configuration */
  LocalChannel = LocalCoreConfigPtr->Gpt_ChannelIndexPtr[Channel];

  return LocalChannel;
}
/******************************************************************************/
#endif
/* End of #if (GPT_MAX_CORE_USED > 1U) */

#if (GPT_DEV_ERROR_DETECT == STD_ON)|| (GPT_SAFETY_ENABLE == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={492E4AD5-FBAB-487e-9E87-438A623B9E6E}]   **
**                                                                            **
** Syntax          : static void Gpt_lReportError                             **
**                                (const uint8 Gpt_Sid, const uint8 ErrorId)  **
**                                                                            **
** Description     : Function to report Safety Error and DET                  **
** [/cover]                                                                   **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : Gpt_Sid - Service id of the caller API                   **
**                   ErrorId - ID of the error to be reported                 **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
*                                                                             **
*******************************************************************************/
static void Gpt_lReportError(const uint8 Gpt_Sid, const uint8 ErrorId)
{
  /* [cover parentID={790AB6E1-617F-42b2-9A5F-40EFF5A9ED3B}]
  DET reporting is ON
  [/cover] */
  #if (GPT_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={D026E0DB-A011-482e-8E7E-2C9BB882A0B6}]
  Report DET
  [/cover] */
  (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, Gpt_Sid, ErrorId);
  #endif
  /* [cover parentID={5EAC0B3A-A581-459c-B2F6-6F27280F5619}]
  Safety error reporting is ON.
  [/cover] */
  #if (GPT_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={7D1E2773-0AFF-4a44-BC4F-E672F99A39B4}]
  Report Safety Error
  [/cover] */
  Mcal_ReportSafetyError(GPT_MODULE_ID, GPT_INSTANCE_ID, Gpt_Sid, ErrorId);
  #endif
}
#endif

#if (GPT_MULTICORE_ERROR_DETECT == STD_ON)|| (GPT_SAFETY_ENABLE == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={32575748-CB64-4581-A5EF-2C1EE03EF5E7}]   **
**                                                                            **
** Syntax          : LOCAL_INLINE void Gpt_lReportMulticoreError              **
**                                  (const uint8 ApiId, const uint8 ErrorId)  **
**                                                                            **
** Description     : This function reports Multicore DET and Safety Error     **
** [/cover]                                                                   **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : Gpt_Sid - Service id of the caller API                   **
**                   ErrorId - ID of the error to be reported                 **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
*                                                                             **
*******************************************************************************/
LOCAL_INLINE void Gpt_lReportMulticoreError
                                      (const uint8 Gpt_Sid, const uint8 ErrorId)
{
  /* [cover parentID={C93E9113-48C0-4e4e-872E-7C59E89C1DFD}]
  MULTICORE ERROR DETECT
  [/cover] */
  #if (GPT_MULTICORE_ERROR_DETECT == STD_ON)
  /* [cover parentID={222EB571-EB06-4ec3-8B88-F6DD3BAF4A4F}]
  Report DET
  [/cover] */
  (void)Det_ReportError( GPT_MODULE_ID, GPT_INSTANCE_ID, Gpt_Sid, ErrorId);
  #endif

  /* [cover parentID={8A74B46C-983F-4ec1-BD5D-82F74B17055D}]
  SAFETY ENABLED
  [/cover] */
  #if (GPT_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={A9957C74-45DF-494e-8538-ED399E697314}]
  Mcal_ReportSafetyError
  [/cover] */
  Mcal_ReportSafetyError( GPT_MODULE_ID, GPT_INSTANCE_ID, Gpt_Sid, ErrorId);
  #endif
}
#endif

#if( (GPT_SAFETY_ENABLE == STD_ON) || (GPT_RUNTIME_ERROR_DETECT == STD_ON)||\
   ((MCAL_AR_VERSION == MCAL_AR_422) && (GPT_DEV_ERROR_DETECT == STD_ON)) )
/*******************************************************************************
** Traceability: [cover parentID={C2A834FE-2B4B-4fe9-9B35-015445925AC6}]      **
**                                                                            **
** Syntax           : static void Gpt_lReportRuntimeDetError                  **
**                    (                                                       **
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
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*                                                                             **
*******************************************************************************/
static void Gpt_lReportRuntimeDetError(const uint8 ApiId, const uint8 ErrorId)
{
  /* Runtime Error Detection is only available in Autosar version AR440 */
  /* [cover parentID={9BA8C4A8-E4D4-41bd-A9E0-BE427C5E88FE}]
  If runtime error is ON
  [/cover] */
  #if(GPT_RUNTIME_ERROR_DETECT == STD_ON)
  /* [cover parentID={17B89C68-F8C7-433a-8EE7-5FB8E437D3B1}]
  Report runtime error
  [/cover] */
  /* Report the Runtime Error */
  (void)Mcal_Wrapper_Det_ReportRuntimeError(GPT_MODULE_ID, GPT_INSTANCE_ID, ApiId, ErrorId);
  #elif(MCAL_AR_VERSION == MCAL_AR_422)
    /* DET is ON */
    /* [cover parentID={E5D2D7A4-6193-4015-B6AA-B556D113C4AF}]
    DET reporting is ON
    [/cover] */
    #if (GPT_DEV_ERROR_DETECT == STD_ON)
    /* Report the DET Error */
    /* [cover parentID={80EE7427-BCD0-487d-806F-1E5F21FAE8C5}]
    Report DET
    [/cover] */
    (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, ApiId, ErrorId);
    #endif
    /* [cover parentID={C3B05770-5679-486a-85B3-7174710FE495}]
    Safety error reporting is ON.
    [/cover] */
    /* SAFETY is ON */
    #if (GPT_SAFETY_ENABLE == STD_ON)
      
    /* [cover parentID={FD112B8D-ED98-4cd3-A3BF-C472BD7ED1EA}]
    Report Safety error
    [/cover] */
    /* Report the Safety Error */
    Mcal_ReportSafetyError(GPT_MODULE_ID, GPT_INSTANCE_ID, ApiId, ErrorId);
    #endif
  #endif
}
#endif

/******************************************************************************/

#if (GPT_INITCHECK_API == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={1655299D-EBF5-4164-867A-441D71DCDBFC}]   **
**                                                                            **
** Syntax         : LOCAL_INLINE Std_ReturnType Gpt_lChannelsInitCheck        **
**                            (                                               **
**                              const uint32 CurrentCoreId,                   **
**                              Gpt_CoreConfigType const *const CoreConfigPtr **
**                            )                                               **
** Description    : This function verifies initialization of all the channels **
**                  configured in the core (except Predef timer) and the      **
**                  corresponding status flags                                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : CurrentCoreId - Current Core ID                           **
**                  CoreConfigPtr - Pointer to current core configuration     **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : E_OK     - Initialization comparison is success           **
**                  E_NOT_OK - Initialization comparison fails                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Gpt_lChannelsInitCheck(const uint32 CurrentCoreId,
                                  Gpt_CoreConfigType const *const CoreConfigPtr)
{
  uint32 CompareMatchFlag;
  uint8           Counter;
  Std_ReturnType  RetVal = E_OK;

  /* [cover parentID={6E0B8311-0908-4b9c-9935-3AD63D7C3EC2}]
  Set error condition for return variable
  [/cover] */
  CompareMatchFlag = GPT_INITCHECK_STS_VAL;

  /* Iterate for all the channels allocated to the core to check they are
     configured correctly */
  /* [cover parentID={BAF7A71F-0281-400c-A792-8CFECE79C633}]
  Loop exited with error condition
  [/cover] */
  /* [cover parentID={D911A58F-B939-401c-A011-B4D725125598}]
  Iterate for all the allocated channels
  [/cover] */
  for ( Counter = (uint8)0x0U;
        /* [cover parentID={AC383880-6D2D-4ca8-A529-2770B54511B5}]
        Loop upto Max chanels or Error condition
        [/cover] */
        ((Counter < CoreConfigPtr->Gpt_MaxNormalChannels) &&
         (CompareMatchFlag == GPT_INITCHECK_STS_VAL)); Counter++ )
  {
    /* [cover parentID={52974148-2761-44e2-91F5-49C13E8D0D4A}]
    Check for channel status is initialized
    [/cover] */
    CompareMatchFlag &= ~(GPT_CHANNEL_INITIALIZED ^
      (uint32)Gpt_ThreadSafeData[CurrentCoreId]->Gpt_ChannelStatusPtr[Counter]);
    #if (GPT_GPT12_USED == STD_ON)
    /* [cover parentID={D71ABEC9-1309-4d63-804D-1AA24702DA84}]
    Is channel using GPT12
    [/cover] */
    if(CoreConfigPtr->ChannelConfigPtr[Counter].GptGpt12TimerInfo != NULL_PTR)
    {
      /* [cover parentID={4F441756-6CA9-4f97-A2FA-D77E3BFADC46}]
       Check the corresponding GPT12 channel is properly initialized
       [/cover] */
      CompareMatchFlag &= ~(E_OK ^ (uint32)Mcu_17_Gpt12_TimerInitCheck
                (CoreConfigPtr->ChannelConfigPtr[Counter].GptGpt12TimerInfo));
    }
    else
    #endif
    { 
      /*Check for channel status is initialized */;
      #if (GPT_TOM_USED == STD_ON) || (GPT_ATOM_USED == STD_ON)
       /* [cover parentID={119AFCD0-0D8C-4c5e-B209-CA299DF0DBFF}]
       Check the corresponding TOM/ATOMs are properly initialized
       [/cover] */
      CompareMatchFlag &= ~(E_OK ^ (uint32)Gpt_lGtmChannelInitCheck
                          (&CoreConfigPtr->ChannelConfigPtr[Counter]));
      #endif
    }
    /* [cover parentID={56028478-F1F8-4a4f-A1E3-AB9C1132C282}]
    WakeupReporting is ON or Notification is Enabled
    [/cover] */
    /* Check if the channel corresponding flag is reset */
    #if ((GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) ||   \
         (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
    /* [cover parentID={37F3695E-5F81-4229-A217-B1515971BB82}]
    Check if the channel corresponding flag is reset
    [/cover] */
    CompareMatchFlag &= ~((uint8)0x0U ^ 
               (uint32)Gpt_ThreadSafeData[CurrentCoreId]->Gpt_FlagPtr[Counter]);
    #endif
  } /* End of for ( Counter = (uint8)0x0U;
          ((Counter < CoreConfigPtr->Gpt_MaxNormalChannels) &&
              CompareMatchFlag == GPT_INITCHECK_STS_VAL);Counter++ ) */

  if (CompareMatchFlag != GPT_INITCHECK_STS_VAL)
  {
    RetVal = E_NOT_OK;
  }

  return RetVal;
}/* End of Gpt_lChannelsInitCheck */
/******************************************************************************/
#if (GPT_TOM_USED == STD_ON) || (GPT_ATOM_USED == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={5A92843A-577F-418e-B1F9-D4CC8A29826C}]   **
**                                                                            **
** Syntax         : LOCAL_INLINE Std_ReturnType Gpt_lGtmChannelInitCheck      **
**                         (const Gpt_ChannelConfigType *const GptChannelPtr) **
**                                                                            **
** Description    : This function verifies the initialization of the          **
**                  configured GTM Timer Channel                              **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : GptChannelPtr - Pointer to core specific channel config   **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : E_OK     - Initialization comparison is success           **
**                  E_NOT_OK - Initialization comparison fails                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Gpt_lGtmChannelInitCheck
                              (const Gpt_ChannelConfigType *const GptChannelPtr)
{
  const Mcu_17_Gtm_TomAtomChConfigType *LocalGptGtmTimerInfo;
  Std_ReturnType RetVal = E_NOT_OK;

  /* Fetch GptGtmTimerInfo that contains properties of TOM/ATOM channel used */
  LocalGptGtmTimerInfo = GptChannelPtr->GptGtmTimerInfo;

  /* Call TOM/ATOM Init check API accordingly to check the initialization
  of the channel based on selection */
  /* [cover parentID={5CCCC314-3C2A-4b1d-B737-3E81690CF6B2}]
  TOM USED
  [/cover] */
  #if (GPT_TOM_USED == STD_ON)
  /* [cover parentID={3C74F6A6-0002-4d61-9FB2-32AD28F66C34}]
  Is current timer is TOM
  [/cover] */
  if (LocalGptGtmTimerInfo->TimerType == MCU_GTM_TIMER_TOM)
  {
    /* [cover parentID={CABA141C-6CD7-4051-9376-044B53293A9E}]
    Check TOM registers are initialized as intended
    [/cover] */
    RetVal = Mcu_17_Gtm_TomChInitCheck(LocalGptGtmTimerInfo);
  }
  #endif
  /* End of #if (GPT_TOM_USED == STD_ON) */

  /* [cover parentID={3A04D882-034E-46b4-8A63-5AA91A4B8A69}]
  ATOM USED
  [/cover] */
  #if (GPT_ATOM_USED == STD_ON)
  /* [cover parentID={0A77F096-499C-49fb-AEA7-274FAFF68193}]
  Is current timer is ATOM
  [/cover] */
  if (LocalGptGtmTimerInfo->TimerType == MCU_GTM_TIMER_ATOM)
  {
    /* [cover parentID={7680AC08-9242-4164-AC90-FA8C657D72CB}]
    Check ATOM registers are initialized as intended
    [/cover] */
    RetVal = Mcu_17_Gtm_AtomChInitCheck(LocalGptGtmTimerInfo);
  }
  #endif
  /* End of #if (GPT_ATOM_USED == STD_ON) */

  return RetVal;
}/* End of Gpt_lGtmChannelInitCheck */
#endif
/******************************************************************************/
#if ((GPT_PREDEF_TIMER_1US_16BIT_EN == STD_ON)    || \
     (GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON)    || \
     (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))

/*******************************************************************************
** Traceability   : [cover parentID={3198B7D0-A914-4c6c-B926-43B81B47B0D7}]   **
**                                                                            **
** Syntax         : static Std_ReturnType Gpt_lGtmInitCheck1UsPredefTimer     **
                              (const Gpt_CoreConfigType *const CoreConfigPtr) **
**                                                                            **
** Description    : This function verifies the initialization of configured   **
**                  1us Predef Timer                                          **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : CoreConfigPtr - Pointer to current core configuration     **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : E_OK     - Initialization comparison is success           **
**                  E_NOT_OK - Initialization comparison failed               **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Gpt_lGtmInitCheck1UsPredefTimer
                                 (const Gpt_CoreConfigType *const CoreConfigPtr)
{
  const Gpt_1UsPredefTimerChannelConfigType   *LocalGptPredefChannelPtr;
  uint32 CompareMatchFlag = GPT_INITCHECK_STS_VAL;
  Std_ReturnType RetVal = E_NOT_OK;
  uint8 ModuleNumber;                         /* Holds the module number     */
  uint8 ChannelNumber;                        /* Holds the channel number    */

  /* Get pointer to 1us Predef Timer */
  LocalGptPredefChannelPtr = CoreConfigPtr->Predef1UsChannelConfigPtr;

  /* [cover parentID={D38F782C-171D-411c-93CD-9C6C5120F3D0}]
  Check the software flags corresponding to 1us GPT Predef Timer  are enabled
  [/cover] */
  /* Check the software flags corresponding to 1us GPT Predef Timer
    are enabled */
  CompareMatchFlag &= ~(GPT_CHANNEL_RUNNING ^ GPT_GET_1US_PREDEF_TIMER_STS());
  /* [cover parentID={BC0AA633-C07E-45fb-8188-2001D8C8D51F}]
  Extra Channels required
  [/cover] */
  #if (GPT_PREDEF_EXTRA_CH_1US == STD_ON)
  /* [cover parentID={FC0A77CC-30BE-4b49-B4E4-9FEBEFADDEA9}]
  Extra chennel required?
  [/cover] */
  if (LocalGptPredefChannelPtr->ExtraChRequirement1Us == 0x1U)
  {
    /************************************************************************
     * Configure the channel which is used to tick the Predef channel       *
     ************************************************************************/
    /* Module Id of the TOM channel */
    ModuleNumber = (uint8)  
                   ((LocalGptPredefChannelPtr->GptGtm1UsTimerInfo0.TimerId &
                     GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);

    /* Channel number of the TOM channel */
    ChannelNumber = (uint8) 
                    ((LocalGptPredefChannelPtr->GptGtm1UsTimerInfo0.TimerId &
                      GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);

    /* [cover parentID={61143CF2-17F4-4f9c-817E-1E2865B861BE}]
    Call GTM Library to verify TOM channel initialization
    [/cover] */
    /* Call GTM Library to verify TOM channel initialization */
    CompareMatchFlag &= ~( E_OK ^ (uint32)Mcu_17_Gtm_TomChInitCheck(
                             &(LocalGptPredefChannelPtr->GptGtm1UsTimerInfo0)));

    /* [cover parentID={5F38622D-A4C6-4a2a-805B-FBD4BA8C162C}]
    Call the library function to verify that the timer channel is started
    [/cover] */
    CompareMatchFlag &= ~(MCU_GTM_TIMER_RUNNING ^
          (uint32)Mcu_17_Gtm_IsTomChannelEnabled(ModuleNumber, ChannelNumber));
  }
  #endif

  /**************************************************************************
   * Configure the actual Predef Channel                                    *
   **************************************************************************/
  /* Module Id of the TOM channel */
  ModuleNumber = (uint8)  
                 ((LocalGptPredefChannelPtr->GptGtm1UsTimerInfo1.TimerId &
                   GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);

  /* Channel number of the TOM channel */
  ChannelNumber = (uint8) 
                  ((LocalGptPredefChannelPtr->GptGtm1UsTimerInfo1.TimerId &
                    GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);

  /* [cover parentID={7B7667F5-5CC9-4286-A0E5-C30F3C0148C2}]
  Call GTM Library to verify TOM channel initialization
  [/cover] */
  CompareMatchFlag &= ~( E_OK ^ (uint32)Mcu_17_Gtm_TomChInitCheck(
                           &(LocalGptPredefChannelPtr->GptGtm1UsTimerInfo1)));

  /* [cover parentID={576E787B-4237-4f07-B167-EA66D921556C}]
  Call the library function to verify that the timer channel is started
  [/cover] */
  CompareMatchFlag &= ~(MCU_GTM_TIMER_RUNNING ^
          (uint32)Mcu_17_Gtm_IsTomChannelEnabled(ModuleNumber, ChannelNumber));

  /* [cover parentID={26008AF9-B1DD-4e86-B559-4487359638C2}]
  24/32Bit Timer
  [/cover] */
  #if ((GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON) || \
       (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))
  /* [cover parentID={25D4D6FC-685C-4200-B424-987E081C0DA6}]
  Is the timer more than 16bits in length
  [/cover] */
  if (LocalGptPredefChannelPtr->Gpt1UsPredefTimerUsed0 != 
                                                  GPT_PREDEF_TIMER_1US_16BIT)
  {
    /************************************************************************
     * Configure the immediate next channel in case of 24 or 32 bit Predef  *
     * timer                                                                *
     ************************************************************************/
    /* Module Id of the TOM channel */
    ModuleNumber = (uint8)  
        ((LocalGptPredefChannelPtr->GptGtm1UsTimerInfo2.TimerId &
                          GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);

    /* Channel number of the TOM channel */
    ChannelNumber = (uint8) 
                    ((LocalGptPredefChannelPtr->GptGtm1UsTimerInfo2.TimerId &
                      GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);

    /* [cover parentID={0CB2ED43-3E28-42b8-A069-0DA631D04F33}]
    Call GTM Library to verify TOM channel initialization
    [/cover] */
    CompareMatchFlag &= ~( E_OK ^ (uint32)Mcu_17_Gtm_TomChInitCheck(
                             &(LocalGptPredefChannelPtr->GptGtm1UsTimerInfo2)));

    /* [cover parentID={A3590B67-980A-4873-BF47-B902FECE2A8A}]
    Call the library function to verify that the timer channel is started
    [/cover] */
    CompareMatchFlag &= ~(MCU_GTM_TIMER_RUNNING ^
                          (uint32)Mcu_17_Gtm_IsTomChannelEnabled(ModuleNumber, ChannelNumber));
  }
  #endif
  /* [cover parentID={ACE9AC8C-BF24-4a3d-B190-2CD98CAC71AC}]
  Are there errors
  [/cover] */
  if(CompareMatchFlag == GPT_INITCHECK_STS_VAL)
  {
    /* [cover parentID={B36D3CED-6E95-44f4-A8BD-21793CE24590}]
    Set errors
    [/cover] */
    RetVal = E_OK;
  }

return RetVal;
}/* End of Gpt_lGtmInitCheck1UsPredefTimer */
#endif
/******************************************************************************/

#if (GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={F8ECD09A-9B18-4d58-AEDE-59E4EE694F74}]   **
**                                                                            **
** Syntax         : static Std_ReturnType Gpt_lGtmInitCheck100UsPredefTimer   **
                              (const Gpt_CoreConfigType *const CoreConfigPtr) **
**                                                                            **
** Description    : This function verifies the initialization of configured   **
**                  100us Predef Timer                                        **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : None                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : CoreConfigPtr - Pointer to current core configuration     **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : E_OK     - Initialization comparison is success           **
**                  E_NOT_OK - Initialization comparison failed               **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Gpt_lGtmInitCheck100UsPredefTimer
                                 (const Gpt_CoreConfigType *const CoreConfigPtr)
{
  const Gpt_100UsPredefTimerChannelConfigType *LocalGptPredefChannelPtr;
  uint32 CompareMatchFlag = GPT_INITCHECK_STS_VAL;
  Std_ReturnType RetVal = E_NOT_OK;
  uint8 ModuleNumber;                         /* Holds the module number     */
  uint8 ChannelNumber;                        /* Holds the channel number    */

  /* Get pointer to 100us Predef Timer */
  LocalGptPredefChannelPtr = CoreConfigPtr->Predef100UsChannelConfigPtr;

   /* [cover parentID={ED387A7D-F3DB-45f1-8100-982A7E0736C4}]
  Check the software flags corresponding to 100us GPT Predef Timer  are enabled
  [/cover] */
  CompareMatchFlag &= ~(GPT_CHANNEL_RUNNING ^ GPT_GET_100US_PREDEF_TIMER_STS());
  /* [cover parentID={54500ECD-A189-4fd9-A4C2-B84C86E0678F}]
  Extra Channels required
  [/cover] */
  #if (GPT_PREDEF_EXTRA_CH_100US == STD_ON)
  /* [cover parentID={9F1089F9-8AE5-4fcf-AEA8-6DA7F6131AB7}]
  Extra chennel required?
  [/cover] */
  if (LocalGptPredefChannelPtr->ExtraChRequirement100Us == 0x1U)
  {
    /************************************************************************
     * Verify the channel which is used to tick the Predef channel          *
     ************************************************************************/
    /* Module Id of the TOM channel */
    ModuleNumber = (uint8)  
                   ((LocalGptPredefChannelPtr->GptGtm100UsTimerInfo0.TimerId &
                     GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);

    /* Channel number of the TOM channel */
    ChannelNumber = (uint8) 
                    ((LocalGptPredefChannelPtr->GptGtm100UsTimerInfo0.TimerId &
                      GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);

    /* [cover parentID={F2A9C39C-3A3A-4368-9EDE-35146B5053B4}]
    Call GTM Library to verify TOM channel initialization
    [/cover] */
    CompareMatchFlag &= ~( E_OK ^ (uint32)Mcu_17_Gtm_TomChInitCheck(
                             &(LocalGptPredefChannelPtr->GptGtm100UsTimerInfo0)));

    /* [cover parentID={B37C4630-F1B6-49e7-B65F-ADC093892DF3}]
    Call the library function to verify that the timer channel is started
    [/cover] */
    /* [cover parentID={E9A90F2F-D396-48fe-A798-B5296CA50A19}]
    Call the library function to verify that the timer channel is started
    [/cover] */
    CompareMatchFlag &= ~(MCU_GTM_TIMER_RUNNING ^
           (uint32)Mcu_17_Gtm_IsTomChannelEnabled(ModuleNumber, ChannelNumber));
  }
  #endif
  /* End of #if (GPT_PREDEF_EXTRA_CH_100US == STD_ON) */

  /*************************************************************************
   * Verify the actual Predef Channel                                      *
   *************************************************************************/
  /* Module Id of the TOM channel */
  ModuleNumber = (uint8) 
                 ((LocalGptPredefChannelPtr->GptGtm100UsTimerInfo1.TimerId &
                   GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);

  /* Channel number of the TOM channel */
  ChannelNumber = (uint8) 
                  ((LocalGptPredefChannelPtr->GptGtm100UsTimerInfo1.TimerId &
                    GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);

  /* [cover parentID={CF955E48-D932-471e-B2CA-B2470DC0EEA4}]
  Call GTM Library to verify TOM channel initialization
  [/cover] */
  /* Call GTM Library to verify TOM channel initialization */
  CompareMatchFlag &= ~( E_OK ^ (uint32)Mcu_17_Gtm_TomChInitCheck(
                           &(LocalGptPredefChannelPtr->GptGtm100UsTimerInfo1)));

  /* [cover parentID={D4621173-D494-48a7-9765-4DEF44D6C90E}]
  Call the library function to verify that the timer channel is started
  [/cover] */
  CompareMatchFlag &= ~(MCU_GTM_TIMER_RUNNING ^
           (uint32)Mcu_17_Gtm_IsTomChannelEnabled(ModuleNumber, ChannelNumber));

  /**************************************************************************
   * Verify the immediate next channel to make a 32 bit Predef timer        *
   **************************************************************************/
  /* Module Id of the TOM channel */
  ModuleNumber = (uint8)  
                 ((LocalGptPredefChannelPtr->GptGtm100UsTimerInfo2.TimerId &
                   GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);

  /* Channel number of the TOM channel */
  ChannelNumber = (uint8) 
                  ((LocalGptPredefChannelPtr->GptGtm100UsTimerInfo2.TimerId &
                    GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);

  /* [cover parentID={3316D833-ACF9-4e8c-A1BE-90EF689FA5FF}]
  Call GTM Library to verify TOM channel initialization
  [/cover] */
  /* Call GTM Library to verify TOM channel initialization */
  CompareMatchFlag &= ~( E_OK ^ (uint32)Mcu_17_Gtm_TomChInitCheck(
                           &(LocalGptPredefChannelPtr->GptGtm100UsTimerInfo2)));

  /* Call the library function to verify that the timer channel is started */
  CompareMatchFlag &= ~(MCU_GTM_TIMER_RUNNING ^
           (uint32)Mcu_17_Gtm_IsTomChannelEnabled(ModuleNumber, ChannelNumber));

  /* [cover parentID={21FE5DB4-D200-435e-8D35-95979BFA73AB}]
  Are there errors
  [/cover] */
  if(CompareMatchFlag == GPT_INITCHECK_STS_VAL)
  {
    /* [cover parentID={0220EA52-E177-43e3-9671-00DD2AF6D61A}]
    Set errors
    [/cover] */
    RetVal = E_OK;
  }

  return RetVal;
}/* End of Gpt_lGtmInitCheck100UsPredefTimer */
#endif
/******************************************************************************/
#endif
/* End of #if (GPT_INITCHECK_API == STD_ON) */



/* Stop GPT code section */
#define GPT_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"

#define GPT_START_SEC_CODE_FAST_ASIL_B_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"

/*******************************************************************************
** Traceability    : [cover parentID={DDD9DFE5-469D-4846-BD1E-D963A00C66AC}]  **
**                                                                            **
** Syntax         : void Gpt_Isr(const uint32 LogicalChId)                    **
**                                                                            **
** Description    : Interrupt service routine called on any timer event.      **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : 0x0F                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : LogicalChId - GPT Channel Number                          **
**                  StatusFlags - Source of ISR is CM0 or CM1                 **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
/* [cover parentID={4141A6C4-464E-4050-A147-DE34112CA916}] */
/*  [/cover] */
void Gpt_Isr(const uint32 LogicalChId, const uint32 StatusFlags)
{
  #if ((GPT_ONESHOT_USED == STD_ON)                     || \
       (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)  || \
       ((GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)        && \
       (GPT_REPORT_WAKEUP_SOURCE == STD_ON)))
  const Gpt_ChannelConfigType *LocalGptChannelPtr;
  const Gpt_CoreConfigType    *LocalCoreConfigPtr;
  uint32                      CurrentCoreId;
  Gpt_ChannelType             LocalChannel;

    /* [cover parentID={DCF8E698-29AD-4ec4-A5E4-DA781934A55B}]
  Get the core Id
  [/cover] */
  /* Get the current core ID */
  CurrentCoreId = GPT_GET_COREID();

  /* Get the pointer to current core configuration */
  LocalCoreConfigPtr = GPT_GET_CORECONFIGPTR(CurrentCoreId);
  /* Check if any normal channel present in the current core */
  /* [cover parentID={1DD51CCE-05E4-4b72-A486-13C6C49F1F9E}]
  Is any normal channel present in the current core?
  [/cover] */
  if (LocalCoreConfigPtr->ChannelConfigPtr != NULL_PTR)
  {
    /* Get the mapped offset for this channel from configuration */
    /* [cover parentID={DEAA603B-8F5B-4517-8E76-55D5B5D8175B}]
      Is more than one core used?
      [/cover] */
    #if (GPT_MAX_CORE_USED > 1U)
    LocalChannel = (Gpt_ChannelType) 
                   LocalCoreConfigPtr->Gpt_ChannelIndexPtr[LogicalChId];
    /* [cover parentID={A3EEC252-49AC-4bd0-9B77-092C29C7765B}]
    Is channel is mapped to current core?
    [/cover] */
    /* Check if channel is mapped to current core */
    if (LocalChannel != GPT_INVALID_CHANNEL)
    #else
    LocalChannel = (Gpt_ChannelType)LogicalChId;
    #endif
    {
           /* Get pointer to channel config of current core */
      LocalGptChannelPtr = &LocalCoreConfigPtr->
                                           ChannelConfigPtr[LocalChannel];
      
      /* Perform the required service(s) */

      #if (GPT_ONESHOT_USED == STD_ON)
      /* [cover parentID={4A29E2BC-CE55-4ca9-81DA-2685FEA016F4}]
      Handle OSM Channel
      [/cover] */
      /* Check and handle channel configured in one-shot mode */
      Gpt_lHandleOsmChannel
                          (LocalGptChannelPtr, LocalChannel, CurrentCoreId);
      #endif
      /* End of #if (GPT_ONESHOT_USED == STD_ON) */

      #if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
      /* [cover parentID={36800203-772D-4ed7-82C9-952C19A2AE38}]
      Handle Notifcation Call
      [/cover] */
      Gpt_lHandleNotifCall(LocalGptChannelPtr, LocalChannel, CurrentCoreId);
      #endif
      /* End of #if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) */

      #if ((GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) && \
           (GPT_REPORT_WAKEUP_SOURCE == STD_ON))
      /* [cover parentID={AED9444D-92F1-4b83-97E6-486EE05BE848}]
      Handle WakeupEvent
      [/cover] */
      Gpt_lHandleWakeupEvent
                          (LocalGptChannelPtr, LocalChannel, CurrentCoreId);
      #endif
      /* End of #if ((GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) && \
                    (GPT_REPORT_WAKEUP_SOURCE == STD_ON))     */
      
    }
    #if (GPT_MAX_CORE_USED > 1U)
    #if (GPT_SAFETY_ENABLE == STD_ON)
    else
    {
      /* Report to Safety Error as channel is not mapped to current
      * core
      */
      /* [cover parentID={F9DBEB9E-769B-41d6-BC35-EE9C8D1FDD2B}]
      Mcal_ReportSafetyError
      [/cover] */
      Mcal_ReportSafetyError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_SID_ISR, 
                          GPT_E_NOT_CONFIGURED);
    }
    #endif
    #endif
  }
  #if (GPT_SAFETY_ENABLE == STD_ON)
  else
  {
    /* Report to Safety Error as core has no GPT channels mapped to
    * current core
    */
    /* [cover parentID={F9DBEB9E-769B-41d6-BC35-EE9C8D1FDD2B}]
    Mcal_ReportSafetyError
    [/cover] */
    Mcal_ReportSafetyError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_SID_ISR, 
                                                  GPT_E_NOT_CONFIGURED);
  }
  #endif
  /* End of #if (GPT_SAFETY_ENABLE == STD_ON) */
  #endif
  /* End of   #if ((GPT_ONESHOT_USED == STD_ON)         || \
     (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)  || \
     ((GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)        && \
     (GPT_REPORT_WAKEUP_SOURCE == STD_ON)))*/
           
  UNUSED_PARAMETER(LogicalChId);
  UNUSED_PARAMETER(StatusFlags);
  return;
}/* End of Gpt_Isr */


/******************************************************************************/
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
Callout Memory section not used in GPT driver
[/cover]*/
#define GPT_STOP_SEC_CODE_FAST_ASIL_B_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"

/*******************************************************************************
**                               End of File                                  **
*******************************************************************************/

