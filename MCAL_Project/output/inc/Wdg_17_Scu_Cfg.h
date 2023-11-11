
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
**  FILENAME  : Wdg_17_Scu_Cfg.h                                              **
**                                                                            **
**  VERSION   : 10.0.0                                                         **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:31               !!!IGNORE-LINE!!!       **
**                                                                            **
**  GENERATOR : Build b191017-0938                   !!!IGNORE-LINE!!!       **
**                                                                            **
**  BSW MODULE DECRIPTION : Wdg.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Wdg configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of Wdg Driver, AUTOSAR Release 4.2.2 and **
**                     4.4.0                                                  **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/


#ifndef WDG_17_SCU_CFG_H
#define WDG_17_SCU_CFG_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/* AUTOSAR specification version numbers */

#define WDG_17_SCU_AR_RELEASE_MAJOR_VERSION     (4U)
#define WDG_17_SCU_AR_RELEASE_MINOR_VERSION     (2U)
#define WDG_17_SCU_AR_RELEASE_REVISION_VERSION  (2U)


/* Vendor specific implementation version information */
#define WDG_17_SCU_SW_MAJOR_VERSION   (20U)
#define WDG_17_SCU_SW_MINOR_VERSION   (25U)
#define WDG_17_SCU_SW_PATCH_VERSION   (0U)

/*
Configuration: WDG_DEV_ERROR_DETECT  :
- if ON, DET is Enabled
- if OFF,DET is Disabled
ECUC_Wdg_00115: Compile switch to enable/disable development error detection
for this module.
- STD_ON if WdgDevErrorDetect is true
- STD_OFF if WdgDevErrorDetect is true
*/

#define WDG_17_SCU_DEV_ERROR_DETECT                                         (STD_ON)  


/*
Configuration: WDG_VERSION_INFO_API:
ECUC_Wdg_00119:Compile switch to enable/disable the version information API
- STD_ON if WdgVersionInfoApi is true
- STD_OFF if WdgVersionInfoApi is false
*/

#define WDG_17_SCU_VERSION_INFO_API                                         (STD_OFF)  


/*
Configuration: WDG_17_SCU_SAFETY_ENABLE:
ECUC_Wdg_00119:Compile switch to enable/disable the Safety Enable API
- ON if WdgSafetyEnable is true
- OFF if WdgSafetyEnable is false
*/

#define WDG_17_SCU_SAFETY_ENABLE                                            (STD_OFF)  


/*
Configuration: WDG_17_SCU_INIT_CHECK_API:
ECUC_Wdg_00119:Compile switch to enable/disable the Init Check API
- STD_ON if WdgInitCheckApi is true
- STD_OFF if WdgInitCheckApi is false
*/

#define WDG_17_SCU_INIT_CHECK_API                                           (STD_OFF)  


/*
Configuration: WDG_17_SCU_INIT_API_MODE:
-User Mode Macro for Init API
*/

#define WDG_17_SCU_INIT_API_MODE                           (WDG_17_SCU_MCAL_SUPERVISOR)

/*
Configuration: WDG_17_SCU_RUNTIME_API_MODE:
-User Mode Macro for Runtime APIs
*/

#define WDG_17_SCU_RUNTIME_API_MODE                        (WDG_17_SCU_MCAL_SUPERVISOR)

/*Wdg Core Configured*/
  

#define WDG_17_SCU_CONFIGURED_CORE0                                 (STD_ON)

#define WDG_17_SCU_CONFIGURED_CORE1                                 (STD_ON)
#define WDG_17_SCU_CONFIGURED_CORE2                                 (STD_OFF)
#define WDG_17_SCU_CONFIGURED_CORE3                                 (STD_OFF)

/* WDG_MAX_TIMERS: holds maximum number of WDG timers configured */

#define WDG_17_SCU_MAX_TIMERS (4U) 


/* WDG_TRIG_SELECT: Select the timer for service WDG during STC window period */
#define WDG_17_SCU_TRIG_SELECT (WDG_17_SCU_STM_TIMER)

/* Production error related pre-compile switches */
/* Production error reporting enable/disabled macro */
#define WDG_17_SCU_ENABLE_DEM_REPORT  (1U)
#define WDG_17_SCU_DISABLE_DEM_REPORT (0U)

#define WDG_17_SCU_DISABLE_REJECT_DEM_REPORT   (WDG_17_SCU_DISABLE_DEM_REPORT)

#define WDG_17_SCU_MODE_FAIL_DEM_REPORT        (WDG_17_SCU_DISABLE_DEM_REPORT)
/* Instance ID for WDG module */

#define WDG_17_SCU_INSTANCE_ID   ((uint8)0U)
#define Wdg_17_ScuConf_WdgGeneral_WdgIndex (WDG_17_SCU_INSTANCE_ID)


/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/


/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/


/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/


/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/
#endif  /* WDG_17_CFG_H */

