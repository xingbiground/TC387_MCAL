
/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2018)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Stm_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:30                 !!!IGNORE-LINE!!!     **
**                                                                            **
**  GENERATOR : Build b191017-0938                     !!!IGNORE-LINE!!!     **
**                                                                            **
**  BSW MODULE DECRIPTION : Stm.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Stm configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Requirements of Stm Driver                             **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef STM_CFG_H
#define STM_CFG_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                              **
** Traceabilty      :                                                         **
*******************************************************************************/
#define STM_AR_RELEASE_MAJOR_VERSION     (4U)
#define STM_AR_RELEASE_MINOR_VERSION     (2U)
#define STM_AR_RELEASE_REVISION_VERSION  (2U)

#define STM_SW_MAJOR_VERSION  (10U)
#define STM_SW_MINOR_VERSION  (40U)
#define STM_SW_PATCH_VERSION  (0U)

#define    STM_CMP0_CMP1_UNUSED        (0xFFU)
#define    STM_CMP0_USED               (0x0U)
#define    STM_CMP1_USED               (0x1U)
#define    STM_CMP0_CMP1_USED          (0x2U)

#define    STM_TIMER_UNUSED            (0xFFU)

/*
  Configuration Options for the setting the privilege mode in ADC Driver
*/
#define STM_MCAL_SUPERVISOR  (0U)
#define STM_MCAL_USER1       (1U)


#define  STM_0  (0x0U)
#define  STM_1  (0x1U)
#define  STM_2  (0x2U)
#define  STM_3  (0x3U)

  






        
/* Maximum number of timers configured in each core */
#define STM_CORE0_MAX_TIMERS       (0x1U)
#define STM_CORE1_MAX_TIMERS       (0x1U)
#define STM_CORE2_MAX_TIMERS       (0x0U)
#define STM_CORE3_MAX_TIMERS       (0x0U)
#define STM_CORE4_MAX_TIMERS       (0x0U)
#define STM_CORE5_MAX_TIMERS       (0x0U)

/*
                    Container:StmGeneral
*/
/*
  Configuration of Development Error Detection 
  API Parameter Checking is enabled if this compiler
  switch is STD_ON. 
  - if STD_ON, Development error detection is enabled
  - if STD_OFF, Development error detection is disabled
*/
#define STM_DEV_ERROR_DETECT                (  STD_ON)

/*
  Configuration: STM_VERSION_INFO_API :
  Configuration of version information  
  Adds/removes the Stm_GetVersionInfo() API from the code 
  - if STD_ON, Stm_GetVersionInfo() is available in the code
  - if STD_OFF, Stm_GetVersionInfo() is not available in the code
*/
#define STM_VERSION_INFO_API                (  STD_OFF)

/* Dem reporting enable/disabled macro */
#define STM_ENABLE_DEM_REPORT  (1U)
#define STM_DISABLE_DEM_REPORT (0U)


/* DEM enable/disable for STM module clock enable failure */
#define STM_E_CLC_ENABLE_ERR_DEM_REPORT    (STM_DISABLE_DEM_REPORT)

/*
Configuration: STM_RUNTIME_API_MODE 
  - if STM_MCAL_USER1 is selected   User1 Mode is enabled 
  - if STM_MCAL_SUPERVISOR is selected Runtime Mode is enabled 
*/
#define STM_RUN_TIME_API_MODE                (  STM_MCAL_SUPERVISOR)


/*
  Total number of STM timers availability
*/
#define STM_MAX_TIMERS      (0x4U)


/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/
#endif
