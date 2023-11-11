/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2021)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME   : Fls_17_Dmu_Cfg.h                                            **
**                                                                           **
**  VERSION :  12.0.0                                                        **
**                                                                           **
**  DATE, TIME: 2023-11-11, 17:37:32              !!!IGNORE-LINE!!!      **
**                                                                           **
**  GENERATOR : Build b191017-0938                !!!IGNORE-LINE!!!        **
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
**  DESCRIPTION  : FLS configuration generated out of ECU configuration      **
**                   file                                                    **
**                                                                           **
**  SPECIFICATION(S) : Specification of FLS Driver,                          **
**                           AUTOSAR Release 4.2.2 and 4.4.0                 **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: No                                      **
**                                                                           **
******************************************************************************/


#ifndef FLS_17_DMU_CFG_H
#define FLS_17_DMU_CFG_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/* MemIf Type Defnitions Imported from Memory Abstract Interface */
#include "MemIf_Types.h"

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/*
  Published parameters
*/


/* FLS Instance ID */
#define FLS_17_DMU_INSTANCE_ID                ((uint8)0)


#define Fls_17_DmuConf_FlsGeneral_FlsDriverIndex  (FLS_17_DMU_INSTANCE_ID)
/* Autosar specification version */
#define FLS_17_DMU_AR_RELEASE_MAJOR_VERSION           (4U)
#define FLS_17_DMU_AR_RELEASE_MINOR_VERSION           (2U)
#define FLS_17_DMU_AR_RELEASE_REVISION_VERSION        (2U)

/* Vendor specific implementation version information */
#define FLS_17_DMU_SW_MAJOR_VERSION           (20U)
#define FLS_17_DMU_SW_MINOR_VERSION           (25U)
#define FLS_17_DMU_SW_PATCH_VERSION           (0U)

/*
  The following macros will enable or disable a particular feature in FLS
  module.Set the macro to STD_ON to enable the feature and STD_OFF to
  disable the same.
*/
/* Enable/Disable Development error detection(DET)  */
#define FLS_17_DMU_DEV_ERROR_DETECT           (STD_OFF)


/* Enable/Disable RunTime error detection */
#define FLS_17_DMU_RUNTIME_ERROR_DETECT           (STD_OFF)


/* Enable/Disable Safety error detection */
#define FLS_17_DMU_SAFETY_ENABLE           (STD_OFF)


/*Enable/Disable FLS Init Check API*/
#define FLS_17_DMU_INITCHECK_API           (STD_OFF)



#define FLS_17_DMU_USE_INTERRUPTS          (STD_OFF)


/*Erase verification during write feature*/
#define FLS_17_DMU_ERASE_VERIFICATION           (STD_OFF)


/*Erase verification reporting feature*/
#define FLS_17_DMU_ERASE_VERIFY_REPORT          (STD_OFF)


/*Write verification feature*/
#define FLS_17_DMU_WRITE_VERIFICATION          (STD_OFF)


/*Timeout Supervision feature*/
#define FLS_17_DMU_TIMEOUT_SUPERVISION           (STD_OFF)

/*Fls_cancel api selection*/

#define FLS_17_DMU_CANCEL_API               (STD_ON)


/*Fls_17_Dmu_GetEccErrorPageAddress api selection*/
#define FLS_17_DMU_ECC_ERROR_INFO_API         (STD_OFF)


/*Fls_SetMode api selection*/
#define FLS_17_DMU_SET_MODE_API               (STD_ON)

/*Fls_compare api selection*/
#define FLS_17_DMU_COMPARE_API              (STD_ON)


/*Fls_BlankCheck api selection*/
#define FLS_17_DMU_BLANK_CHECK_API              (STD_OFF)

/*Fls_GetJobResult api selection*/
#define FLS_17_DMU_GET_JOB_RESULT_API       (STD_ON)


/*Fls_GetStatus api selection*/
#define FLS_17_DMU_GET_STATUS_API           (STD_ON)

/*Fls_GetVersionInfo api selection*/
#define FLS_17_DMU_VERSION_INFO_API     (STD_OFF)

/*Erase suspend/resume feature selection*/
#define FLS_17_DMU_USE_ERASESUSPEND     (STD_OFF)



/* IFX FEE is being used in configuration */
#define FLS_17_DMU_IFX_FEE_USED        (STD_ON)


/*DFLASH base/start address*/
#define FLS_17_DMU_BASE_ADDRESS           (0xaf000000U)

/*DFLASH total size*/

#define FLS_17_DMU_TOTAL_SIZE             (0x18000U)

/* Start address of the NVM Sector0 */
#define FLS_17_DMU_NVMSECTOR0_STARTADDRESS (0xaf000000U)

/* Start address of the NVM Sector1 */

#define FLS_17_DMU_NVMSECTOR1_STARTADDRESS (0xaf008000U)

/* Size of the 1 NVM sector of the the double sector in bytes*/

#define FLS_17_DMU_NVMSECTOR_SIZE        (0x8000U)
/* Start address of the Quasi Static Data */
#define FLS_17_DMU_QSDATA_STARTADDRESS   (0xaf010000U)

/* Size of the Quasi static data in bytes*/
#define FLS_17_DMU_QSDATA_SIZE           (0x8000U)

  
/* IFX FEE NVM is present in the configuration */
#define FLS_17_DMU_IFX_NVM_PRESENT        (STD_ON)


/*
Configuration: FLS_INIT_API_MODE
Specifies the operating modes for Fls initialization - SUPERVISOR/ USER1
*/
#define FLS_17_DMU_INIT_API_MODE             (FLS_17_DMU_MCAL_SUPERVISOR)

/*
Configuration: FLS_RUNTIME_API_MODE
Specifies the operating modes for Fls runtime - SUPERVISOR/ USER1
*/
#define FLS_17_DMU_RUNTIME_API_MODE           (FLS_17_DMU_MCAL_SUPERVISOR)


/* Page size of the Data flash is 8 bytes */
#define FLS_17_DMU_PAGE_SIZE            (8U)


/* erase and write times are published in us (micro seconds) */
#define FLS_17_DMU_ERASE_TIME            (1897500000U)


#define FLS_17_DMU_WRITE_TIME            (5154000U)


#define FLS_17_DMU_DEFAULT_ERASEVALUE            (0U)

/*Timeout for Erase suspend/resume feature*/

#if (FLS_17_DMU_USE_ERASESUSPEND == STD_ON)
#define FLS_17_DMU_ERASESUSPEND_TIMEOUT        (0x2ee0U)
#endif

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
#endif  /* FLS_17_DMU_CFG_H */
