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
**  FILENAME     : Wdg_17_Scu.h                                               **
**                                                                            **
**  VERSION      : 11.0.0                                                     **
**                                                                            **
**  DATE         : 2021-09-28                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Wdg Driver header definition file                          **
**                                                                            **
**  SPECIFICATION(S) : Specification of Watchdog Driver, AUTOSAR Release      **
**                     4.2.2 and 4.4.0                                        **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/* [cover parentID={52B9B0C8-144A-4b01-B59D-98C06AAF42BE}][/cover] */
/* [cover parentID={1354422D-7B2C-476e-8D1F-8D5275478391}][/cover] */
#ifndef WDG_17_SCU_H
#define WDG_17_SCU_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Wdg Module Configuration header file */
#include "Wdg_17_Scu_Cfg.h"

/* MCAL header file containing global macros, type definitions and functions
  needed by all MCAL drivers. */
#include "McalLib.h"
#include "Mcu_17_TimerIp.h"

/* [cover parentID={F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}][/cover] */
/* [cover parentID={0589C41B-C3FF-449b-ADE8-D063FCD12B58}][/cover] */
#if (MCAL_AR_VERSION == MCAL_AR_422)
 #include "WdgIf_Types.h"
#endif
#if (MCAL_AR_VERSION == MCAL_AR_440)
 #include "WdgIf.h"  
#endif
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/* [cover parentID={9A86A376-093A-4194-A84F-6A9E348BEA3D}][/cover] */
/* Vendor ID */
#define WDG_17_SCU_VENDOR_ID                (17U)
/* Wdg Module ID */
#define WDG_17_SCU_MODULE_ID                ((uint16)102U)

/* Wdg Development error or Safety error detection enabled */
#if((WDG_17_SCU_DEV_ERROR_DETECT==STD_ON)||\
(WDG_17_SCU_SAFETY_ENABLE==STD_ON))

/* API service used in wrong context (e.g. driver not initialized) */
/* [cover parentID={79A7232F-21D2-454b-BDF5-3C5AA9EE2EA3}][/cover] */
#define WDG_17_SCU_E_DRIVER_STATE ((uint8)0x10)

/* [cover parentID={7F5BF130-61D6-4519-B0A7-9CD55C0B8169}][/cover] */
/* API service called with wrong/inconsistent parameter(s) */
#define WDG_17_SCU_E_PARAM_MODE   ((uint8)0x11)

/* [cover parentID={9E1AF53D-FD2C-48b9-8C3D-0680E023E917}][/cover] */
/* API Service called with wrong parameter.Config is a null pointer */
#define WDG_17_SCU_E_PARAM_CONFIG  ((uint8)0x12)

/* [cover parentID={CE80965E-E58C-401b-9756-9F7945E7B727}][/cover] */
/* The passed timeout value is higher than the maximum timeout value*/
#define WDG_17_SCU_E_PARAM_TIMEOUT ((uint8)0x13)

/* [cover parentID={43EDFB21-4A6A-4ee5-96E6-88B75B5F677D}][/cover] */
/* API is called with wrong pointer value*/
#define WDG_17_SCU_E_PARAM_POINTER ((uint8)0x14)

/* [cover parentID={12BA0D74-BC59-4e30-A4FA-992DF4F0F2B0}][/cover] */
/* Invalid configuration set selection */
#define WDG_17_SCU_E_INIT_FAILED   ((uint8)0x15)
/*
   API Service ID's.
*/

/* API Service ID for Wdg_17_Scu_SetTriggerCondition() */
#define WDG_17_SCU_SID_TRIGGER_CONDITION   ((uint8)0x03)

/* API Service ID for Wdg_17_Scu_GetVersionInfo() */
#define WDG_17_SCU_SID_GETVERSIONINFO   ((uint8)0x04)

/* API Service ID for Driver notification function */
#define WDG_17_SCU_SID_TIMERNOTIF       ((uint8)0x05)

#endif

/* API Service ID for Wdg_17_Scu_Init() */
#define WDG_17_SCU_SID_INIT             ((uint8)0x00)

/* API Service ID for Wdg_17_Scu_SetMode() */
#define WDG_17_SCU_SID_SETMODE          ((uint8)0x01)

/* Wdg Safety error detection enabled */
#if((WDG_17_SCU_SAFETY_ENABLE == STD_ON))
/*Safety Errors*/
/*If ISR is triggered when WDG is disabled.*/
/* [cover parentID={B0FE28A9-BA02-43b9-A23B-1E6F14554E98}][/cover] */
#define WDG_17_SCU_E_MODE_DISABLED ((uint8)0xC8)

/*WDG ISR is triggered if interrupt source is not CMP0 in case of GTM.*/
/* [cover parentID={4219AEFF-2CAB-4a36-B608-0435BFA91870}][/cover] */
#define WDG_17_SCU_E_INVALID_INTERRPT_SOURCE ((uint8)0xC9)

/*If ISR is triggered when WDG is disabled.*/
/* [cover parentID={E0298433-177A-467e-8CFD-81508F584CE0}][/cover] */
#define WDG_17_SCU_E_OVERFLOW ((uint8)0xCA)

/*WDG ISR is triggered if interrupt source is not CMP0 in case of GTM.*/
/* [cover parentID={E00F7529-6DE5-4a86-B876-E716A2DA0F83}][/cover] */
#define WDG_17_SCU_E_ACCESS ((uint8)0xCB)

/*If WDG initialization is called while the state is BUSY*/
/* [cover parentID={9C7CA781-2D36-4ff6-AB1B-4C548CC47B28}][/cover] */
#define WDG_17_SCU_E_BUSY ((uint8)0xCC)

#endif

#define WDG_17_SCU_INIT_ACCESS                (10U)
#define WDG_17_SCU_RUNTIME_ACCESS             (11U)

/*Contains STM Compare unit information*/
#define WDG_17_SCU_STM_CMP0             ((uint8)0U)
#define WDG_17_SCU_STM_CMP1             ((uint8)1U)

#define WDG_17_SCU_GTM_TIMER             (1U)
#define WDG_17_SCU_STM_TIMER             (2U)

#define WDG_17_SCU_MCAL_SUPERVISOR                 (0U)
#define WDG_17_SCU_MCAL_USER1                      (1U)


/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
/*  [/cover] */
/* [cover parentID={F5510766-918B-4e26-9EA9-D93176D648D3}] */
/* WDG module configuration information */

/* [cover parentID={83404304-3FB6-44d5-87B0-66574F398AAF}] */
typedef struct Wdg_17_Scu_ConfigType
{
  /*STM timer configuration information*/
  #if(WDG_17_SCU_TRIG_SELECT == WDG_17_SCU_STM_TIMER)
  const Mcu_17_Stm_TimerConfigType *WdgStmConfig;
  /*  [/cover] */
  #else
  /*GTM timer configuration information.*/
  const  Mcu_17_Gtm_TomAtomChConfigType *WdgGtmTimerInfo;
  #endif
  /*Fast mode reload value in ticks*/
  uint16  FastModeReloadValue;
  /*Slow mode reload value in ticks*/
  uint16  SlowModeReloadValue;
  /*Fast callback interval in terms of time in ms*/
  uint16  FastModeRefreshTime;
  /*Slow callback interval in terms of time in ms*/
  uint16  SlowModeRefreshTime;
  /*Initial refresh timeout in terms of time in ms*/
  uint16  InitialRefreshTime;
  /*Maximum timeout time in ms*/
  uint16  MaxTimeOutTime;
  /*WdgDefaultMode*/
  WdgIf_ModeType  DefaultMode;
  /*WdgDisableAllowed*/
  boolean  WdgDisableAllowed;
  /*core id*/
  uint32  WdgCoreID;
  /*Wdg password*/
  uint32 WdgPassword;

} Wdg_17_Scu_ConfigType;

/*  [/cover] */
/*  [/cover] */
/* [cover parentID={00A64856-199B-494a-9299-617BDB28333D}] */
/*Provides the status of WDG*/
typedef enum
{
  WDG_17_SCU_UNINIT = 0U,
  WDG_17_SCU_IDLE = 1U,
  WDG_17_SCU_BUSY = 2U
} Wdg_17_Scu_StatusType;

/*  [/cover] */


/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
#define WDG_17_SCU_START_SEC_CODE_ASIL_B_GLOBAL
/* [cover parentID={A604246C-F580-4feb-ABD3-B14E73230A8E}][/cover]*/
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}][/cover]*/
#include "Wdg_17_Scu_MemMap.h"

/*******************************************************************************
** Traceability     : [cover parentID={63BCCED1-A483-4628-BEE7-79D1E75356CD}] **
**                                                                            **
** Syntax           : void Wdg_17_Scu_Init                                    **
**                    (                                                       **
**                      const Wdg_17_Scu_ConfigType* const ConfigPtr          **
**                    )                                                       **
**                                                                            **
** Description      : Driver Module Initialization function.This routine      **
**                    initializes the watchdog driver and watchdog hardware   **
**                    i.e it sets the default watchdog mode and timeout       **
**                    period as provided in the configuration set. The        **
**                    configuration set for each core shall be chosen from    **
**                    the statically configured set of each core.             **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x00                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : ConfigPtr - Pointer to WDG configuration Set            **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
*******************************************************************************/
extern void Wdg_17_Scu_Init(const Wdg_17_Scu_ConfigType* const ConfigPtr);


/*******************************************************************************
** Traceability     : [cover parentID={466D81F9-CE73-42a0-9B3B-33C9551996F1}] **
**                                                                            **
** Syntax           : Std_ReturnType Wdg_17_Scu_SetMode                       **
**                                       (const WdgIf_ModeType Mode )         **
**                                                                            **
** Description      : By choosing one of a limited number of statically       **
**                    configured settings (e.g. toggle or window watchdog,    **
**                    different timeout periods) the watchdog driver and      **
**                    hardware can be switched between the following three    **
**                    different watchdog Modes Off or Slow or Fast:           **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x01                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters (in)  : WdgIf_ModeType Mode                                     **
**                      One of the following statically configured modes:     **
**                      1. WDGIF_OFF_MODE                                     **
**                      2. WDGIF_SLOW_MODE                                    **
**                      3. WDGIF_FAST_MODE                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Std_ReturnType (E_OK or E_NOT_OK)                       **
*******************************************************************************/
extern Std_ReturnType Wdg_17_Scu_SetMode(const WdgIf_ModeType Mode);


/*******************************************************************************
** Traceability     : [cover parentID={F43AB8FF-39D2-4828-8E27-1580287B2E57}] **
**                                                                            **
** Syntax           : void Wdg_17_Scu_SetTriggerCondition                     **
**                    (                                                       **
**                      const uint16 timeout                                  **
**                    )                                                       **
**                                                                            **
** Description      : The function Wdg_17_Scu_SetTriggerCondition shall sets  **
**                    Timeout value (milliseconds) for setting the trigger    **
**                    counter                                                 **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x03                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : timeout - Timeout value for setting the trigger counter **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
*******************************************************************************/
extern void Wdg_17_Scu_SetTriggerCondition(const uint16 timeout);


/*******************************************************************************
** Traceability     : [cover parentID={18FCC30C-D81C-44d6-8058-37C0D932A011}] **
**                                                                            **
** Syntax           : void Wdg_17_Scu_GetVersionInfo                          **
**                    (                                                       **
**                      const Std_VersionInfoType* const versioninfo          **
**                    )                                                       **
**                                                                            **
** Description      : This API returns the version information of Wdg module  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x04                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : versioninfo - Pointer to where to store the version     **
**                    information of this module                              **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
*******************************************************************************/
#if (WDG_17_SCU_VERSION_INFO_API == STD_ON)

extern void Wdg_17_Scu_GetVersionInfo(Std_VersionInfoType* const versioninfo);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro 'Wdg_17_Scu_GetVersionInfo'
 * defined. No side effects foreseen by violating this MISRA rule. */
#define Wdg_17_Scu_GetVersionInfo(versioninfo) \
                                (ERROR_Wdg_17_Scu_GetVersionInfo_API_IS_NOT_SELECTED)

#endif

/*******************************************************************************
** Traceability     : [cover parentID={6429A86C-11FA-4b5d-AB4A-CE11F23387FB}] **
**                                                                            **
** Syntax           : Std_ReturnType Wdg_17_Scu_InitCheck                     **
**                    (                                                       **
**                      const Wdg_17_Scu_ConfigType* const ConfigPtr          **
**                    )                                                       **
**                                                                            **
** Description      : This API returns the status of the module               **
**                    initialization in context to the core from              **
**                    where the API is invoked.The API is available when      **
**                    safety is enabled or initialization check is            **
**                    explicitly enabled. This API does not check any         **
**                    running counter values of GTM, STM and global variables.**
**                                                                            **
**                    Note: Init check should be performed in the following   **
**                    sequence:                                               **
**                    1. Call Wdg_17_Scu_Init from a core.                    **
**                    2. Call Wdg_17_Scu_InitCheck from the same core.        **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x06                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : ConfigPtr - Pointer to WDG configuration Set            **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK : initialization was suscessful                    **
**                    E_NOT_OK: initialization was not suscessful             **
**                                                                            **
*******************************************************************************/

#if (WDG_17_SCU_INIT_CHECK_API == STD_ON)

Std_ReturnType Wdg_17_Scu_InitCheck(const Wdg_17_Scu_ConfigType*
                                    const ConfigPtr);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro 'Wdg_17_Scu_InitCheck'
 * defined. No side effects foreseen by violating this MISRA rule. */  
#define Wdg_17_Scu_InitCheck(ConfigPtr) \
                                (ERROR_Wdg_17_Scu_InitCheck_API_IS_NOT_SELECTED)
#endif

#define WDG_17_SCU_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
#include "Wdg_17_Scu_MemMap.h"

#include "Wdg_17_Scu_PBcfg.h"
/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/

#endif /* WDG_17_SCU_H */
