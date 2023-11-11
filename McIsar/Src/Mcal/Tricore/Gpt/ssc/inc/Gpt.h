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
**  FILENAME     : Gpt.h                                                      **
**                                                                            **
**  VERSION      : 20.0.0                                                     **
**                                                                            **
**  DATE         : 2021-03-01                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY : [cover parentID={C4AD9DFD-EC57-4cbe-941B-8F88942AEE94} ]   **
**                                                                            **
**  DESCRIPTION  : GPT Driver header definition file                          **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of GPT Driver, AUTOSAR Release 4.2.2     **
**                                                              and 4.4.0     **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

#ifndef  GPT_H
#define  GPT_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* [cover parentID={F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}][/cover] */
/* Inclusion of Platform_Types.h and Compiler.h */
#include "Std_Types.h"
/*GPT Pre-compile/static configuration file */
#include "Gpt_Cfg.h"

/* [cover parentID=  {9083125E-8A84-4f79-A181-9F883842A012}] */
#include "Mcu_17_TimerIp.h"
/* Inclusion of Module configuration file */
#include "McalLib.h"
/* Type definition of EcuM_WakeupSourceType */
/* The inclusion of EcuM_Cbk.h is required, if wakeup functionality is
   configured. */
   
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) 
#include "EcuM.h"
#if (MCAL_AR_VERSION == MCAL_AR_422)
#include "EcuM_Cbk.h"
#else
#include "EcuM_Externals.h"
#endif
#endif
/* [/cover] */
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/* Published parameters (Vendor ID, Module ID and Instance ID) */
/* [cover parentID={89786E64-497A-4d9d-9ED7-7876A1FF155C}] */
#define GPT_VENDOR_ID                (17U)
#define GPT_MODULE_ID                (100U)
/*  [/cover] */
#define GPT_INSTANCE_ID              (0U)

#if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON) || (GPT_RUNTIME_ERROR_DETECT == STD_ON))
/* [cover parentID={38A80282-5F9D-4d08-BEA0-9268CC1030EF}] */
#define GPT_E_BUSY                   ((uint8)0x0BU)
/* [/cover] */

/* [cover parentID={83401F37-61C8-40a4-BC97-C336F3D21389}] */
#define GPT_E_MODE                   ((uint8)0x0CU)
/* [/cover] */
#endif

#if ((GPT_SAFETY_ENABLE == STD_ON) || (GPT_DEV_ERROR_DETECT == STD_ON))
/*  Default Error Tracer (DET) error values */
/* [cover parentID={C4623325-8C56-424c-9CE6-FCF368695A2A}] */
#define GPT_E_UNINIT                 ((uint8)0x0AU)
/* [/cover] */

/* [cover parentID={C42DADD9-B574-4ac3-AC59-543BB70D9924}] */
#define GPT_E_ALREADY_INITIALIZED    ((uint8)0x0DU)
/* [/cover] */

/* [cover parentID={23A850DB-2226-4386-BFA3-1120C1CFDF78}] */
#define GPT_E_INIT_FAILED            ((uint8)0x0EU)
/* [/cover] */

/* [cover parentID={8C38FA5B-98CE-4721-BF30-E625097E9D07}] */
#define GPT_E_PARAM_CHANNEL          ((uint8)0x14U)
/* [/cover] */

/* [cover parentID={B6597606-0A31-4105-96D0-BA38192113CB}] */
#define GPT_E_PARAM_VALUE            ((uint8)0x15U)
/* [/cover] */

/* [cover parentID={8D7B4FF4-A919-499e-9F03-B9485A57DDF5}] */
#define GPT_E_PARAM_POINTER          ((uint8)0x16U)
/* [/cover] */

/* [cover parentID={46634E3E-E43C-40c2-BDE8-EE2A9A2EE016}] */
#define GPT_E_PARAM_PREDEF_TIMER     ((uint8)0x17U)
/* [/cover] */

/* [cover parentID={89900BEC-C873-4efe-BA88-C0872E5F6EC9}] */
#define GPT_E_PARAM_MODE             ((uint8)0x1FU)
/* [/cover] */

#define GPT_E_MASTER_UNINIT          ((uint8)0x66U)

/* [cover parentID={D48DED1E-2439-4498-B19C-EA93E89410AD}] */
#define GPT_E_NOT_CONFIGURED         ((uint8)0x64U)
/* [/cover] */


#define GPT_E_SLAVE_INIT             ((uint8)0x67U)

/* [cover parentID={77AAE2EB-CC57-4dda-A519-452EEF68C5BE}] */
#define GPT_E_CORE_CHANNEL_MISMATCH  ((uint8)0x65U)
/* [/cover] */

#endif
/* End of #if ((GPT_SAFETY_ENABLE == STD_ON) || \
                                            (GPT_DEV_ERROR_DETECT == STD_ON)) */
                                            
#if (GPT_SAFETY_ENABLE == STD_ON)
/* [cover parentID={3E7101E7-2F36-4a67-9ED3-F9011E5983A6}] */
#define GPT_E_INVALID_START          ((uint8)0xC8)
/* [/cover] */
#endif
/* End of #if ((GPT_SAFETY_ENABLE == STD_ON) */

/* API Service ID's */
#define GPT_SID_GETVERSIONINFO       ((uint8)0x00U)
#define GPT_SID_INIT                 ((uint8)0x01U)
#define GPT_SID_DEINIT               ((uint8)0x02U)
#define GPT_SID_GET_TIMEELAPSED      ((uint8)0x03U)
#define GPT_SID_GET_TIMEREMAINING    ((uint8)0x04U)
#define GPT_SID_STARTTIMER           ((uint8)0x05U)
#define GPT_SID_STOPTIMER            ((uint8)0x06U)
#define GPT_SID_ENABLE_NOTIFICATION  ((uint8)0x07U)
#define GPT_SID_DISABLE_NOTIFICATION ((uint8)0x08U)
#define GPT_SID_SET_MODE             ((uint8)0x09U)
#define GPT_SID_DISABLE_WAKEUP       ((uint8)0x0AU)
#define GPT_SID_ENABLE_WAKEUP        ((uint8)0x0BU)
#define GPT_SID_CHECK_WAKEUP         ((uint8)0x0CU)
#define GPT_SID_GET_PREDEFTIMERVALUE ((uint8)0x0DU)
#define GPT_SID_INITCHECK            ((uint8)0x0EU)
#define GPT_SID_ISR                  ((uint8)0x0FU)

/* Channel Status indicators*/
#define GPT_CHANNEL_UNINITIALIZED    ((uint8)0x00U)
#define GPT_CHANNEL_INITIALIZED      ((uint8)0x01U)
#define GPT_CHANNEL_RUNNING          ((uint8)0x02U)
#define GPT_CHANNEL_STOPPED          ((uint8)0x03U)
#define GPT_CHANNEL_EXPIRED          ((uint8)0x04U)


/* Channel status (Return type for the local function Gpt_lGtmStartTimer()) */
typedef enum
{
  GTM_GPT_CHANNEL_RUNNING = (uint32)0U,
  GTM_GPT_WRONG_PARAM     = (uint32)1U,
  GTM_GPT_CHANNEL_BUSY    = (uint32)2U
} Gtm_GptChannelStatusType;

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/

/****************** The Type definitions for Gpt_PBcfg.c **********************/
/* Timer Channel notification function pointer type in normal mode */
/* [cover parentID={064F471F-7362-4135-89D5-97F2DAE1BCAB}] */
typedef void(*const Gpt_NotificationPtrType)(void);
/*  [/cover] */

/* [cover parentID={990B5C44-865C-47c3-8055-E63093A5AE73}] */
/* Channel wakeup TRUE/FALSE */
typedef boolean Gpt_EnableWakeupType;
/*  [/cover] */

/* Numeric ID of a GPT Channel */
/* [cover parentID={7B4A5403-F60F-493f-995F-DD21D760E074}] */
typedef uint8 Gpt_ChannelType;
/*  [/cover] */

/* The timeout value given in timer ticks. Used for reading the current timer
value/setting periodic timer values (in number of ticks) up to hours */
/* [cover parentID={138D24DA-4D3E-49b2-B269-1AF63B50DCFF}] */
typedef uint32 Gpt_ValueType;
/*  [/cover] */

/* [cover parentID={5FAED5CF-D256-4bee-BBEF-7E1C5B3ADC7C}] */
/* Allows selection of different driver modes  */
typedef enum
{
  GPT_MODE_NORMAL = (uint32)0U,
  GPT_MODE_SLEEP  = (uint32)1U,
} Gpt_ModeType;
/*  [/cover] */

/* Allows selection of different channel modes */
/* [cover parentID={0A59DE49-8640-4b32-8B8E-8E7318AB74C0}] */
typedef uint8 Gpt_ChannelModeType;
/*  [/cover] */

/* [cover parentID={F2A5EC29-B999-442d-8CB0-C01EF2CBD97B}] */
typedef uint8 Gpt_ClockType;
/*  [/cover] */

/* [cover parentID={B22B0F05-82FA-4ba5-B46F-E44A11ABD7FC}] */
/* Type for GPT Predef Timers */
typedef enum
{
  GPT_PREDEF_TIMER_1US_16BIT   = (uint32)0U,
  GPT_PREDEF_TIMER_1US_24BIT   = (uint32)1U,
  GPT_PREDEF_TIMER_1US_32BIT   = (uint32)2U,
  GPT_PREDEF_TIMER_100US_32BIT = (uint32)3U
} Gpt_PredefTimerType;
/*  [/cover] */

/* [cover parentID={DABB7801-CD40-474e-A880-85339F4F353F}] */
/* Channel specific configuration type of GPT driver */
typedef struct
{
  #if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
  Gpt_NotificationPtrType GptNotificationPtr;
  #endif

  #if ((GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) \
  && (GPT_REPORT_WAKEUP_SOURCE == STD_ON))
  /* Wakeup information to EcuM_SetWakeupEvent */
  EcuM_WakeupSourceType GptChannelWakeupInfo;
  #endif

  #if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
  /* Channel wakeup capability TRUE/FALSE */
  Gpt_EnableWakeupType GptEnableWakeupState;
  #endif
  /* Channel mode - GPT_MODE_CONTINUOUS/GPT_MODE_ONESHOT */
  Gpt_ChannelModeType GptChannelMode;
  /* The following holds the Tom/Atom channel specific parameters details
                                 required for TOM/ATOM channel initialization.*/
  #if ((GPT_ATOM_USED == STD_ON) || (GPT_TOM_USED == STD_ON))                              
  const Mcu_17_Gtm_TomAtomChConfigType* const GptGtmTimerInfo;
  #endif
  #if (GPT_GPT12_USED == STD_ON)
  const Mcu_17_Gpt12_TimerConfigType* const GptGpt12TimerInfo;
  #endif
} Gpt_ChannelConfigType;
/*  [/cover] */

#if ((GPT_PREDEF_TIMER_1US_16BIT_EN == STD_ON)   || \
     (GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON)   || \
     (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))
/* Predef timer Channel specific configuration type of GPT driver */
/* [cover parentID={28C1AB72-0346-4222-A8D3-4B3949F64ED8}] */
typedef struct
{
  #if (GPT_PREDEF_EXTRA_CH_1US == STD_ON)
  /* The following holds the Tom channel specific parameters details
     which is used to tick the actual Predef timer channel.*/
  Mcu_17_Gtm_TomAtomChConfigType GptGtm1UsTimerInfo0; /*Used for Ticking*/
  #endif

  /* Actual timer channel configured for Predef functionality.*/
  Mcu_17_Gtm_TomAtomChConfigType GptGtm1UsTimerInfo1; /*Actual Channel*/

  #if ((GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON)    || \
       (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))
  /* The following holds the Tom channel specific parameters details required
     for the Predef channel initialization in case of 24/32 bit Predef timer.*/
  Mcu_17_Gtm_TomAtomChConfigType GptGtm1UsTimerInfo2; /*Cascading Channel*/
  #endif

  /* This variable sets when there is a requirement of an extra channel for
     frequency tuning to implement Predef timer functionality.*/
  boolean ExtraChRequirement1Us;

  /* Types of Predef timers enabled : */
  Gpt_PredefTimerType Gpt1UsPredefTimerUsed0;
  Gpt_PredefTimerType Gpt1UsPredefTimerUsed1;
  Gpt_PredefTimerType Gpt1UsPredefTimerUsed2;

} Gpt_1UsPredefTimerChannelConfigType;
/*  [/cover] */
#endif

#if (GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON)
/* Predef timer Channel specific configuration type of GPT driver  */
/* [cover parentID={33A009ED-73A8-49c1-A781-732D1381660B}] */
typedef struct
{
  #if (GPT_PREDEF_EXTRA_CH_100US == STD_ON)
  /* The following holds the Tom channel specific parameters details
     which is used to tick the actual Predef timer channel.*/
  Mcu_17_Gtm_TomAtomChConfigType GptGtm100UsTimerInfo0;
  #endif

  /* Actual timer channel configured for Predef functionality.*/
  Mcu_17_Gtm_TomAtomChConfigType GptGtm100UsTimerInfo1;

  /* The following holds the Tom channel specific parameters details
      which is used for cascading to make 32bit Predef timer.*/
  Mcu_17_Gtm_TomAtomChConfigType GptGtm100UsTimerInfo2;

  /* This variable sets when there is a requirement of an extra channel for
      frequency tuning to implement Predef timer functionality.*/
  boolean ExtraChRequirement100Us;

  /* Types of Predef timers enabled : */
  Gpt_PredefTimerType Gpt100UsPredefTimerUsed0;

} Gpt_100UsPredefTimerChannelConfigType;
/*  [/cover] */
#endif

/* Core specific module configuration type of GPT Driver  */
/* [cover parentID={5CF49EA1-56C5-4095-8618-496EA2B2F75B}] */
typedef struct
{
  #if (GPT_MAX_CORE_USED > 1U)
  /* Pointer to Channels allocated to Core */
  const uint8 * const Gpt_ChannelIndexPtr;
  #endif

  /* Pointer to core's channel configuration */
  const Gpt_ChannelConfigType * const ChannelConfigPtr;

  #if ((GPT_PREDEF_TIMER_1US_16BIT_EN == STD_ON)    || \
       (GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON)    || \
       (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))
  /* Pointer to 1us Predef channel specific configuration */
  const Gpt_1UsPredefTimerChannelConfigType * const Predef1UsChannelConfigPtr;
  #endif

  #if (GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON)
  /* Pointer to 100us Predef channel specific configuration */
  const Gpt_100UsPredefTimerChannelConfigType 
  *const Predef100UsChannelConfigPtr;
  #endif

  /* Maximum Normal Channels allocated to core */
  const uint8 Gpt_MaxNormalChannels;

} Gpt_CoreConfigType;
/*  [/cover] */

/* Module specific configuration type of GPT Driver  */
/* [cover parentID={73C4BA3A-4D9D-447f-B04E-AF7486CBE62D}] */
typedef struct
{
  /* Core specific configuration Sets */
  const Gpt_CoreConfigType* const Gpt_Config_CorePtr[MCAL_NO_OF_CORES];

  #if (GPT_READ_ACROSS_CORES == STD_ON)
  const uint32 *const Gpt_Config_ChannelCoreIndex;
  #endif

} Gpt_ConfigType;
/*  [/cover] */

/* Channel modes */
#define GPT_MODE_CONTINUOUS          ((Gpt_ChannelModeType)0x00U)
#define GPT_MODE_ONESHOT             ((Gpt_ChannelModeType)0x01U)

/* Configurable Clocks*/
#define GTM_CONFIGURABLE_CLOCK_0     ((Gpt_ClockType)0x00U)
#define GTM_CONFIGURABLE_CLOCK_1     ((Gpt_ClockType)0x01U)
#define GTM_CONFIGURABLE_CLOCK_2     ((Gpt_ClockType)0x02U)
#define GTM_CONFIGURABLE_CLOCK_3     ((Gpt_ClockType)0x03U)
#define GTM_CONFIGURABLE_CLOCK_4     ((Gpt_ClockType)0x04U)
#define GTM_CONFIGURABLE_CLOCK_5     ((Gpt_ClockType)0x05U)
#define GTM_CONFIGURABLE_CLOCK_6     ((Gpt_ClockType)0x06U)
#define GTM_CONFIGURABLE_CLOCK_7     ((Gpt_ClockType)0x07U)

/* Fixed Clock */
#define GTM_FIXED_CLOCK_0            ((Gpt_ClockType)0x08U)
#define GTM_FIXED_CLOCK_1            ((Gpt_ClockType)0x09U)
#define GTM_FIXED_CLOCK_2            ((Gpt_ClockType)0x0AU)
#define GTM_FIXED_CLOCK_3            ((Gpt_ClockType)0x0BU)
#define GTM_FIXED_CLOCK_4            ((Gpt_ClockType)0x0CU)

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/


/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/

/******************************************************************************/
#define GPT_START_SEC_CODE_ASIL_B_GLOBAL
#include "Gpt_MemMap.h"

#if (GPT_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Traceability   : [ ]                                                       **
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
**                                information of this module )                **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
extern void Gpt_GetVersionInfo(Std_VersionInfoType* const VersionInfoPtr);
/******************************************************************************/
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Gpt_GetVersionInfo(VersionInfoPtr)  (ERROR_Gpt_GetVersionInfo_API_IS_NOT_SELECTED)
#endif

/*******************************************************************************
** Traceability   : [ ]                                                       **
**                                                                            **
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
extern void Gpt_Init(const Gpt_ConfigType *const ConfigPtr);
/******************************************************************************/

#if (GPT_DEINIT_API == STD_ON)
/*******************************************************************************
** Traceability   : [ ]                                                       **
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
extern void Gpt_DeInit(void);
/******************************************************************************/
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Gpt_DeInit()  (ERROR_Gpt_DeInit_API_IS_NOT_SELECTED)
#endif
/* End of #if (GPT_DEINIT_API == STD_ON) */

#if (GPT_TIME_ELAPSED_API == STD_ON)
/*******************************************************************************
** Traceability   : [ ]                                                       **
**                                                                            **
** Syntax         : Gpt_ValueType Gpt_GetTimeElapsed(                         **
**                                          const Gpt_ChannelType Channel     **
**                                                  )                         **
**                                                                            **
** Description    : This API returns the time already elapsed.                **
**                  In one shot mode, this is the value relative to the       **
**                  point in time, the channel has been started with          **
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
extern Gpt_ValueType Gpt_GetTimeElapsed(const Gpt_ChannelType Channel);
/******************************************************************************/
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Gpt_GetTimeElapsed(Channel)  (ERROR_Gpt_GetTimeElapsed_API_IS_NOT_SELECTED)
#endif
/* End of #if (GPT_TIME_ELAPSED_API == STD_ON) */

#if (GPT_TIME_REMAINING_API == STD_ON)
/*******************************************************************************
** Traceability   : [ ]                                                       **
**                                                                            **
** Syntax         : Gpt_ValueType Gpt_GetTimeRemaining                        **
**                                    (const Gpt_ChannelType Channel)         **
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
extern Gpt_ValueType Gpt_GetTimeRemaining(const Gpt_ChannelType Channel);
/******************************************************************************/
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Gpt_GetTimeRemaining(Channel)  \
                                  (ERROR_Gpt_GetTimeRemaining_API_IS_NOT_SELECTED)
#endif
/* End of #if (GPT_TIME_REMAINING_API == STD_ON) */

/*******************************************************************************
** Traceability   : [ ]                                                       **
**                                                                            **
** Syntax         : void Gpt_StartTimer(                                      **
**                                const Gpt_ChannelType Channel,              **
**                                const Gpt_ValueType Value                   **
**                                     )                                      **
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
** Reentrancy     : Reentrant                                                 **
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
extern void Gpt_StartTimer(const Gpt_ChannelType Channel, const Gpt_ValueType Value);
/******************************************************************************/

/*******************************************************************************
** Traceability   : [ ]                                                       **
**                                                                            **
** Syntax         : void Gpt_StopTimer(const Gpt_ChannelType Channel)         **
**                                                                            **
** Description    :  This API stops the selected timer channel.               **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     :  0x06                                                     **
**                                                                            **
** Sync/Async     :  Synchronous                                              **
**                                                                            **
** Reentrancy     :  Reentrant                                                **
**                                                                            **
** Parameters(in) :  Channel: Numeric identifier of the GPT channel           **
**                                                                            **
** Parameters(out):  None                                                     **
**                                                                            **
** Return value   :  None                                                     **
**                                                                            **
*******************************************************************************/
extern void Gpt_StopTimer(const Gpt_ChannelType Channel);
/******************************************************************************/

#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
/*******************************************************************************
** Traceability   :  [ ]                                                      **
**                                                                            **
** Syntax         :  void Gpt_EnableNotification                              **
**                                        (const Gpt_ChannelType Channel)     **
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
** Reentrancy     :  Reentrant                                                **
**                                                                            **
** Parameters(in) :  Channel: Numeric identifier of the GPT channel           **
**                                                                            **
** Parameters(out):  None                                                     **
**                                                                            **
** Return value   :  None                                                     **
**                                                                            **
*******************************************************************************/
extern void Gpt_EnableNotification(const Gpt_ChannelType Channel);
/******************************************************************************/
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Gpt_EnableNotification(Channel) \
  (ERROR_Gpt_EnableNotification_API_IS_NOT_SELECTED)
#endif
/* End of #if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) */

#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
/*******************************************************************************
** Traceability   :  [ ]                                                      **
**                                                                            **
** Syntax         :  void Gpt_DisableNotification                             **
**                                          (const Gpt_ChannelType Channel)   **
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
** Reentrancy     :  Reentrant                                                **
**                                                                            **
** Parameters(in) :  Channel: Numeric identifier of the GPT channel           **
**                                                                            **
** Parameters(out):  None                                                     **
**                                                                            **
** Return value   :  None                                                     **
**                                                                            **
*******************************************************************************/
extern void Gpt_DisableNotification(const Gpt_ChannelType Channel);
/******************************************************************************/
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Gpt_DisableNotification(Channel) \
        (ERROR_Gpt_DisableNotification_API_IS_NOT_SELECTED)
#endif
/* End of #if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) */

#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/*******************************************************************************
** Traceability   : [ ]                                                       **
**                                                                            **
** Syntax         : void Gpt_SetMode(const Gpt_ModeType mode)                 **
**                                                                            **
** Description    : This API sets the operation mode to                       **
**                   the given mode parameter.                                **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : 0x09                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : mode (GPT_MODE_NORMAL/GPT_MODE_SLEEP)                     **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
extern void Gpt_SetMode(const Gpt_ModeType Mode);
/******************************************************************************/
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Gpt_SetMode(Mode) (ERROR_Gpt_SetMode_API_IS_NOT_SELECTED)
#endif
/* End of #if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) */

#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/*******************************************************************************
** Traceability   : [ ]                                                       **
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
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : Channel: Numeric identifier of the GPT channel            **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
extern void Gpt_DisableWakeup(const Gpt_ChannelType Channel);
/******************************************************************************/
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Gpt_DisableWakeup(Channel) (ERROR_Gpt_DisableWakeup_API_IS_NOT_SELECTED)
#endif
/* End of #if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) */

#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/*******************************************************************************
** Traceability   : [ ]                                                       **
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
** Reentrancy     : Reentrant                                                 **
**                                                                            **
** Parameters(in) : Channel: Numeric identifier of the GPT channel            **
**                                                                            **
** Parameters(out): None                                                      **
**                                                                            **
** Return value   : None                                                      **
**                                                                            **
*******************************************************************************/
extern void Gpt_EnableWakeup(const Gpt_ChannelType Channel);
/******************************************************************************/
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Gpt_EnableWakeup(Channel) (ERROR_Gpt_EnableWakeup_API_IS_NOT_SELECTED)
#endif
/* End of #if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) */

#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/*******************************************************************************
** Traceability   : [ ]                                                       **
**                                                                            **
** Syntax         : void Gpt_CheckWakeup                                      **
**                                (const EcuM_WakeupSourceType WakeupSource)  **
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
extern void Gpt_CheckWakeup(const EcuM_WakeupSourceType WakeupSource);
/******************************************************************************/
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Gpt_CheckWakeup(wakeupSource) (ERROR_Gpt_CheckWakeup_API_IS_NOT_SELECTED)
#endif
/* End of #if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) */

#if ((GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON) || \
    (GPT_PREDEF_TIMER_1US_16BIT_EN == STD_ON)    || \
    (GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON)    || \
    (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))
/*******************************************************************************
** Traceability   : [ ]                                                       **
**                                                                            **
** Syntax         : Std_ReturnType Gpt_GetPredefTimerValue(                   **
**                                    const Gpt_PredefTimerType PredefTimer,  **
**                                    uint32 *const TimeValuePtr              **
**                                                        )                   **
**                                                                            **
** Description    : This API Delivers the current value of the                **
**                   desired GPT Predef Timer.                                **
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
**                                E_OK: no error has been detected            **
**                                E_NOT_OK: aborted due to errors             **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Gpt_GetPredefTimerValue
(const Gpt_PredefTimerType PredefTimer, uint32 *const TimeValuePtr);
/******************************************************************************/
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Gpt_GetPredefTimerValue(PredefTimer, TimeValuePtr) \
        (ERROR_Gpt_GetPredefTimerValue_API_IS_NOT_SELECTED)
#endif
/* End of #if ((GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON) || \
              (GPT_PREDEF_TIMER_1US_16BIT_EN == STD_ON)    || \
              (GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON)    || \
              (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))   */

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
** Return value   : E_OK     - Initialization comparison is success           **
**                  E_NOT_OK - Initialization comparison failed               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Gpt_InitCheck(const Gpt_ConfigType *const ConfigPtr);
/******************************************************************************/
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Gpt_InitCheck(ConfigPtr) (ERROR_Gpt_InitCheck_API_IS_NOT_SELECTED)
#endif
/* End of #if (GPT_INITCHECK_API == STD_ON) */

#define GPT_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Gpt_MemMap.h"

/*******************************************************************************
The file is included to get extern declaration of all the configuration root
structure. The extern declaration of configuration root structure is needed by
application software
*******************************************************************************/
#include "Gpt_PBcfg.h"
/*******************************************************************************
**                      Global In-line Function Definitions                   **
*******************************************************************************/
#endif /* GPT_H */
