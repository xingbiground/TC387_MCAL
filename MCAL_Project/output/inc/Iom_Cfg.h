/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2019)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME   : Iom_Cfg.h                                                 **
**                                                                           **
**  VERSION    : 3.0.0                                                     **
**                                                                           **
**  DATE, TIME: 2023-11-11, 18:27:58            !!!IGNORE-LINE!!!        **
**                                                                           **
**  GENERATOR : Build b200227-0222                 !!!IGNORE-LINE!!!       **
**                                                                           **
**  BSW MODULE DECRIPTION : NA                                               **
**                                                                           **
**  VARIANT   : Variant PB                                                   **
**                                                                           **
**  PLATFORM  : Infineon AURIX2G                                             **
**                                                                           **
**  AUTHOR    : DL-AUTOSAR-Engineering                                       **
**                                                                           **
**  VENDOR    : Infineon Technologies                                        **
**                                                                           **
**  DESCRIPTION  : IOM configuration generated out of ECU configuration      **
**                 file (Iom.bmd/.xdm)                                       **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: No                                      **
**                                                                           **
******************************************************************************/


#ifndef IOM_CFG_H
#define IOM_CFG_H
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/




#define IOM_AR_RELEASE_MAJOR_VERSION      (4U)
#define IOM_AR_RELEASE_MINOR_VERSION      (2U)
#define IOM_AR_RELEASE_REVISION_VERSION   (2U)


#define IOM_SW_MAJOR_VERSION              (10U)
#define IOM_SW_MINOR_VERSION              (40U)
#define IOM_SW_PATCH_VERSION              (0U)  



/* Configuration: IOM_VERSION_INFO_API
Preprocessor switch for enabling version information Iom_GetVersionInfo() API  
- if STD_ON, VersionInfo API is Enabled 
- if STD_OFF, VersionInfo API is Disabled 
*/
#define IOM_VERSION_INFO_API  (STD_OFF)

/* Configuration: IOM_DEINIT_API
Preprocessor switch for enabling Iom_Deinit API 
- if STD_ON, Deinit API is Enabled 
- if STD_OFF, Deinit API is Disabled 
*/
#define IOM_DEINIT_API  (STD_ON)

/*
Configuration: IOM_DEV_ERROR_DETECT
Preprocessor switch for enabling the development error detection and 
reporting. 
- if STD_ON, DET is Enabled 
- if STD_OFF,DET is Disabled 
*/
#define IOM_DEV_ERROR_DETECT  (STD_ON)

/*
Configuration: IOM_GTM_AVAILABLE
Preprocessor switch for checcking wheteher GTM is available */
#define IOM_GTM_AVAILABLE (STD_ON)

/* Instance id for the IOM module */
#define IOM_INSTANCE_ID (0U)

/*
Configuration Options for DEM
Options for the enabling/disabling of DEM in IOM Driver
*/
#define IOM_DISABLE_DEM_REPORT  (0U)
#define IOM_ENABLE_DEM_REPORT   (1U)

/* DEM enable/disable for IOM module clock enable failure */
#define IOM_E_CLC_ENABLE_ERR_DEM_REPORT    (IOM_DISABLE_DEM_REPORT)

/*
Configuration Options for the setting the privilege mode in IOM Driver
*/
#define IOM_MCAL_SUPERVISOR  (0U)
#define IOM_MCAL_USER1       (1U)
/*
Configuration: IOM_INIT_DEINIT_API_MODE
- if STD_ON, Enable Protected Mode(user mode) in Init API 
- if STD_OFF, Enable Supervisor mode in Init API  
*/
#define IOM_INIT_DEINIT_API_MODE                     (IOM_MCAL_SUPERVISOR)

/*Configuration: IOM_RUN_TIME_API_MODE
- if STD_ON, Enable Protected mode in APIs other than Init/Deinit APIs
- if STD_OFF, Disable Protected mode in APIs other than Init/Deinit APIs
*/
#define IOM_RUN_TIME_API_MODE (IOM_MCAL_SUPERVISOR)

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/




/******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/


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
#endif  /* IOM_CFG_H */
