
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
**  FILENAME  : Smu_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 10.0.0                                                         **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:31              !!!IGNORE-LINE!!!           **
**                                                                            **
**  GENERATOR : Build b191017-0938                !!!IGNORE-LINE!!!           **
**                                                                            **
**                                                                            **
**  BSW MODULE DECRIPTION : NA                                                **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Smu configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef SMU_CFG_H
#define SMU_CFG_H
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

#define SMU_AR_RELEASE_MAJOR_VERSION     (4U)
#define SMU_AR_RELEASE_MINOR_VERSION     (2U)
#define SMU_AR_RELEASE_REVISION_VERSION  (2U)
#define SMU_SW_MAJOR_VERSION             (20U)
#define SMU_SW_MINOR_VERSION             (25U)
#define SMU_SW_PATCH_VERSION             (0U)

/*
Configuration Options for Production Error
Options for the enabling/disabling of Production Error in SMU Driver
*/
#define SMU_DISABLE_DEM_REPORT           (0U)
#define SMU_ENABLE_DEM_REPORT            (1U)

#define SmuConfigSet_0  ((uint8)0)

/* Configuration: SMU_VERSION_INFO_API
Version Information API configuration
- if STD_ON, Smu_GetVersionInfo API is available
- if STD_OFF, Smu_GetVersionInfo API is not available
*/
#define SMU_VERSION_INFO_API             (STD_OFF)

#define SMU_INIT_CHECK_API               (STD_ON)

/*
Configuration: SMU_DEV_ERROR_DETECT
Preprocessor switch for enabling the development error detection and 
reporting. 
- if STD_ON, DET is Enabled 
- if STD_OFF,DET is Disabled 
*/

#define SMU_DEV_ERROR_DETECT             (STD_ON)

/*Safety enable switch*/
#define SMU_SAFETY_ENABLE                (STD_ON)

/*Smu_stdby enable switch*/
#define SMU_STANDBY_SWITCH               (STD_OFF)

/*User and Supervisor mode moacros*/
#define SMU_MCAL_SUPERVISOR              0U

#define SMU_MCAL_USER1                   1U

/*Smu_core FSP[0] HW Port Direction*/

#define SMU_CORE_FSP0_HWDIR              (0x1U)

/*Smu_core FSP[1] HW Port Direction*/

#define SMU_CORE_FSP1_HWDIR              (0x0U)

/*Smu_core FSP[0] HW Port Enable*/

#define SMU_CORE_FSP0_PORT_ENABLE        (0x1U)

/*Smu_core FSP[1] HW Port Direction*/
#define SMU_CORE_FSP1_PORT_ENABLE        (0x0U)

/*Smu_core glitch filter through SCU enabled*/
#define SMU_GLITCHFILTER_SCU             (0x0U)

/*Smu_core glitch filter through SMU_STS enabled*/
#define SMU_GLITCHFILTER_SMU_STS         (0x0U)

/*Runtime API mode*/
#define SMU_RUNTIME_API_MODE             (SMU_MCAL_SUPERVISOR)

/*Init Deinit API mode*/
#define SMU_INIT_DEINIT_API_MODE         (SMU_MCAL_SUPERVISOR)

/*Total number of alarm groups for Smu_core*/
#define SMU_CORE_TOTAL_ALARM_GROUPS      ((uint32)(12U))

/*Total number of alarm groups for Smu_stdby*/
#define SMU_STDBY_TOTAL_ALARM_GROUPS     ((uint32)(2U))

/*Total number of alarm configuration registers for Smu_core*/
#define SMU_CORE_TOTAL_ALARM_CONFIG_REG  ((uint32)(36U))

/*Start group number for Smu_stdby*/
#define SMU_STDBY_START_ALARM_GROUP      ((uint32)(20U))

/*End group number for Smu_stdby*/
#define SMU_STDBY_END_ALARM_GROUP        ((uint32)(21U))

/*Smu_stdby FSP[0] as output*/
#define SMU_STDBY_FSP0_OUTPUT            (0x0U)

/*Smu_stdby FSP[1] as output*/
#define SMU_STDBY_FSP1_OUTPUT            (0x0U)

/*Macros to define the valid alarm positions wrt the alarm groups*/
#define SMU_MAX_ALARM_POS                (31U)
#define SMU_GROUP0_POS                   (0x1c07ff7U)
#define SMU_GROUP1_POS                   (0x1c07ff7U)
#define SMU_GROUP2_POS                   (0x1c07ff7U)
#define SMU_GROUP3_POS                   (0x1c07ff7U)
#define SMU_GROUP4_POS                   (0x0U)
#define SMU_GROUP5_POS                   (0x0U)
#define SMU_GROUP6_POS                   (0x3bffdf7U)
#define SMU_GROUP7_POS                   (0xffd3f007U)
#define SMU_GROUP8_POS                   (0xfeff3fffU)
#define SMU_GROUP9_POS                   (0x3802bU)
#define SMU_GROUP10_POS                  (0x77ffffU)
#define SMU_GROUP11_POS                  (0x373fU)
#define SMU_GROUP20_POS                  (0xfff0U)
#define SMU_GROUP21_POS                  (0x1ffbfU)

/*Alarm Execution status validity check masks*/
#define SMU_ALARMEXECSTATUS_VALID        (0xa7f0a7fU)

/* Configuration: SMU_ACTIVATE_RUN_STATE_FAILURE_DEM_NOTIF and SMU_E_ACTIVATE_RUN_STATE_FAILURE 
Determines whether Production Error for Activate RUN state failure is enabled or disabled.
*/



#define SMU_ACTIVATE_RUN_STATE_FAILURE_DEM_NOTIF  (SMU_ENABLE_DEM_REPORT)
#define SMU_E_ACTIVATE_RUN_STATE_FAILURE          (DemConf_DemEventParameter_SMU_E_ACTIVATE_RUN_STATE_FAILURE)



/* Configuration: SMU_CLEAR_ALARM_STATUS_DEM_NOTIF   and SMU_E_CLEAR_ALARM_STATUS_FAILURE
Determines whether Production Error for clearing alarm status failure is enabled or disabled.
*/


#define SMU_CLEAR_ALARM_STATUS_DEM_NOTIF          (SMU_ENABLE_DEM_REPORT)
#define SMU_E_CLEAR_ALARM_STATUS_FAILURE          (DemConf_DemEventParameter_SMU_E_CLEAR_ALARM_STATUS_FAILURE)

/* Configuration: SMU_RELEASE_FSP_DEM_NOTIF and SMU_E_RELEASE_FSP_FAILURE
Determines whether Production Error for releasing FSP failure is enabled or disabled.
*/



#define SMU_RELEASE_FSP_DEM_NOTIF                 (SMU_ENABLE_DEM_REPORT)
#define SMU_E_RELEASE_FSP_FAILURE                 (DemConf_DemEventParameter_SMU_E_RELEASE_FSP_FAILURE)

/* Configuration: SMU_CORE_ALIVE_FAILURE_DEM_NOTIF and SMU_E_CORE_ALIVE_FAILURE
Determines whether Production Error for Smu_core_alive test failure is enabled or disabled.
*/


#define SMU_CORE_ALIVE_FAILURE_DEM_NOTIF          (SMU_ENABLE_DEM_REPORT)
#define SMU_E_CORE_ALIVE_FAILURE                  (DemConf_DemEventParameter_SMU_E_CORE_ALIVE_FAILURE)

/* Configuration: SMU_RT_STOP_FAILURE_DEM_NOTIF  and SMU_E_RT_STOP_FAILURE
Determines whether Production Error for RT stop failure is enabled or disabled.
*/



#define SMU_RT_STOP_FAILURE_DEM_NOTIF             (SMU_ENABLE_DEM_REPORT)
#define SMU_E_RT_STOP_FAILURE                     (DemConf_DemEventParameter_SMU_E_RT_STOP_FAILURE)

/* Configuration: SMU_ACTIVATE_PES_FAILURE_DEM_NOTIF   and SMU_E_ACTIVATE_PES_FAILURE
Determines whether Production Error for Activate PES failure is enabled or disabled.
*/

#define SMU_ACTIVATE_PES_FAILURE_DEM_NOTIF        (SMU_ENABLE_DEM_REPORT)
#define SMU_E_ACTIVATE_PES_FAILURE                (DemConf_DemEventParameter_SMU_E_ACTIVATE_PES_FAILURE)

/* Configuration: SMU_ACTIVATE_FSP_FAILURE_DEM_NOTIF  and SMU_E_ACTIVATE_FSP_FAILURE 
Determines whether Production Error for Activate FSP failure is enabled or disabled.
*/


#define SMU_ACTIVATE_FSP_FAILURE_DEM_NOTIF        (SMU_ENABLE_DEM_REPORT)
#define SMU_E_ACTIVATE_FSP_FAILURE                (DemConf_DemEventParameter_SMU_E_ACTIVATE_FSP_FAILURE)

/* Configuration: SMU_SET_ALARM_STATUS_DEM_NOTIF and SMU_E_SET_ALARM_STATUS_FAILURE
Determines whether Production Error for set alarm status failure is enabled or disabled.
*/


#define SMU_SET_ALARM_STATUS_DEM_NOTIF            (SMU_ENABLE_DEM_REPORT)
#define SMU_E_SET_ALARM_STATUS_FAILURE            (DemConf_DemEventParameter_SMU_E_SET_ALARM_STATUS_FAILURE)

/* Configuration: SMU_SFF_TEST_FAILURE_DEM_NOTIF   and SMU_E_SFF_TEST_FAILURE
Determines whether Production Error for SFF test failure is enabled or disabled.
*/


#define SMU_SFF_TEST_FAILURE_DEM_NOTIF            (SMU_ENABLE_DEM_REPORT)
#define SMU_E_SFF_TEST_FAILURE                    (DemConf_DemEventParameter_SMU_E_SFF_FAILURE)


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

#endif  /* SMU_CFG_H */
