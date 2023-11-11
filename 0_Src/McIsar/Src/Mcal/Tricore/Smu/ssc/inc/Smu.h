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
**  FILENAME     : Smu.h                                                      **
**                                                                            **
**  VERSION      : 18.0.0                                                     **
**                                                                            **
**  DATE         : 2021-02-23                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  TRACEABILITY :  [cover parentID={E8CB7CE0-837D-40f3-B0DB-E2BB4DE403BC},   **
**                                  {F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}]   **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Smu Driver header definition file                          **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/


#ifndef _SMU_H
#define _SMU_H
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/*[cover parentID={825C220C-45ED-44f2-9CDA-CE9D43F07B83}]
File Structure
[/cover]*/
#include "Smu_Cfg.h"
#include "Std_Types.h"

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/*[cover parentID={70444DB5-00D6-4121-B642-285FB7D96C66}] [/cover]*/
#define SMU_VENDOR_ID                       ((uint16)17U)
#define SMU_MODULE_ID                       ((uint16)255U)
#define SMU_MODULE_INSTANCE                 ((uint8)0U)

#if ((SMU_DEV_ERROR_DETECT == STD_ON) || (SMU_SAFETY_ENABLE == STD_ON))
/* DET - Default Error Tracer ID's */
/*Default macro to indicate No Error*/
#define SMU_E_NO_ERR                        ((uint8)0x00U)
/*[cover parentID={748C22DD-D68D-4f37-BE50-455C697486A8}]  [/cover]*/
#define SMU_E_UNINIT                        ((uint8)0x01U)
/*[cover parentID={08C62394-5A89-4150-B236-CC6C9218558E}] [/cover]*/
#define SMU_E_ALREADY_INITIALIZED           ((uint8)0x02U)
/*[cover parentID={F658DA39-67C0-494c-AF57-22170723B077}][/cover]*/
#define SMU_E_INIT_FAILED                   ((uint8)0x03U)
/*[cover parentID={BFCEB174-BCD7-4c09-9872-27B229811CAE}][/cover]*/
#define SMU_E_PARAM_POINTER                 ((uint8)0x04U)
/*[cover parentID={5B4E62F8-C243-4edb-889C-D767AC1E9482}] [/cover]*/
#define SMU_E_PARAM_GROUP                   ((uint8)0x05U)
/*[cover parentID={CBD06857-7EE3-488c-859E-3AE9CAB54E96}] [/cover]*/
#define SMU_E_INVALID_DRIVER_STATE          ((uint8)0x06U)
/*[cover parentID={81243A47-386C-4cb5-B931-87079D187EE5}] [/cover]*/
#define SMU_E_INVALID_TIMER                 ((uint8)0x07U)
/*[cover parentID={5D196B54-D632-40aa-8E76-A41F795104AC}] [/cover]*/
#define SMU_E_STDBY_DISABLED                ((uint8)0x08U)
/*[cover parentID={FD864E23-EBF2-459a-9F4F-974942AA7E0B}] [/cover]*/
#define SMU_E_LOCKED                        ((uint8)0x09U)
/*[cover parentID={27A32948-9BED-4dbf-AC77-434413BEFA82}] [/cover]*/
#define SMU_E_INVALID_ALARM_ACTION          ((uint8)0x0AU)
/*[cover parentID={E30A6307-5431-48a1-A0AD-210A38AA6CE7}] [/cover]*/
#define SMU_E_INVALID_EXECUTION_STATUS      ((uint8)0x0BU)
/*[cover parentID={9FC890EF-C1E3-4fbd-898D-66E047807BF3}] [/cover]*/
#define SMU_E_CORE_MISMATCH                 ((uint8)0x68U)

/*Interface IDs*/
#define SMU_SID_INIT                        ((uint8)0xA8U)
#define SMU_SID_INIT_CHECK                  ((uint8)0xA9U)
#define SMU_SID_DEINIT                      ((uint8)0xAAU)
#define SMU_SID_GET_ALARM_ACTION            ((uint8)0xABU)
#define SMU_SID_SET_ALARM_ACTION            ((uint8)0xACU)
#define SMU_SID_CLEAR_ALARM_STATUS          ((uint8)0xADU)
#define SMU_SID_SET_ALARM_STATUS            ((uint8)0xAEU)
#define SMU_SID_GET_ALARM_STATUS            ((uint8)0xAFU)
#define SMU_SID_GET_ALARM_DEBUG_STATUS      ((uint8)0xB0U)
#define SMU_SID_LOCK_CFG_REGISTER           ((uint8)0xB1U)
#define SMU_SID_RELEASE_FSP                 ((uint8)0xB2U)
#define SMU_SID_ACTIVATE_FSP                ((uint8)0xB3U)
#define SMU_SID_SET_ERROR_PIN               ((uint8)0xB4U)
#define SMU_SID_RELEASE_ERROR_PIN           ((uint8)0xB5U)
#define SMU_SID_RTSTOP                      ((uint8)0xB6U)
#define SMU_SID_GET_RT_MISSEDEVENT          ((uint8)0xB7U)
#define SMU_SID_ACTIVATE_PES                ((uint8)0xB8U)
#define SMU_SID_REGISTER_MONITORING         ((uint8)0xB9U)
#define SMU_SID_GET_SMU_STATE               ((uint8)0xBAU)
#define SMU_SID_ACTIVATE_RUN_STATE          ((uint8)0xBBU)
#define SMU_SID_GET_VERSION_INFO            ((uint8)0xBCU)
#define SMU_SID_CORE_ALIVE_TEST             ((uint8)0xBDU)
#define SMU_SID_GET_ALARM_EXEC_STS          ((uint8)0xBEU)
#define SMU_SID_CLEAR_ALARM_EXEC_STS        ((uint8)0xBFU)
#endif /*End for SMU_DEV_ERROR_DETECT */

#if (SMU_SAFETY_ENABLE == STD_ON)
/*[cover parentID={B46C457E-86C9-4ba6-B7A4-B1F269C4DE0B}] [/cover]*/
#define SMU_E_SF_CFG_LOCKED_FAILURE         ((uint8)0xC8U)
#endif
/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/

/* SMU external action (FSP) configuration - one bit value (Enable / Disable)*/
/*[cover parentID={548E7D85-5A7A-46b1-93F2-9D8187735231}] [/cover]*/
typedef uint32 Smu_FSPActionType;

/* SMU Fault to Run state enable / disable macro */
/* [cover parentID={9C8CA72A-5F27-42b1-804E-BB92430E2A38}] [/cover]*/
typedef enum
{
  SMU_EFRST_DISABLE = 0U,
  SMU_EFRST_ENABLE  = 1U
} Smu_EnableRunStateType;


/* SMU Commands */
/* [cover parentID={1AFE8F1C-0530-4608-BB1D-C4651FE63806}] [/cover]*/
typedef uint8  Smu_CoreCommandType;
#define SMU_RUN_COMMAND    ((Smu_CoreCommandType)0U)
#define SMU_ACTIVATEFSP_COMMAND ((Smu_CoreCommandType)1U)
#define SMU_RELEASEFSP_COMMAND  ((Smu_CoreCommandType)2U)
#define SMU_ACTIVATEPES_COMMAND ((Smu_CoreCommandType)3U)
#define SMU_STOPREC_COMMAND    ((Smu_CoreCommandType)4U)
#define SMU_ASCE_COMMAND    ((Smu_CoreCommandType)5U)
#define SMU_ALARM_COMMAND    ((Smu_CoreCommandType)6U)
#define SMU_ALIVETEST_COMMAND  ((Smu_CoreCommandType)7U)

/* SMU state as read by hardware register - 2 bit value */
/* [cover parentID={13F1A6C4-FC7C-40d1-9AF2-C32513692948}] [/cover]*/
typedef uint8 Smu_CoreStateType;
#define SMU_START_STATE   ((Smu_CoreStateType)0U)
#define SMU_RUN_STATE  ((Smu_CoreStateType)1U)
#define SMU_FAULT_STATE    ((Smu_CoreStateType)2U)
#define SMU_UNDEFINED_STATE  ((Smu_CoreStateType)3U)

/* Valid alarm actions which can be set in alarm config registers */
/* Invalid alarm action which will not be set in alarm config register */
/* [cover parentID={23D093E0-7210-4ea2-AD4C-885F2C581ADE}] [/cover]*/
typedef uint8 Smu_CoreAlarmActionType;
#define  SMU_ALARM_ACTION_NONE  ((Smu_CoreAlarmActionType)0U)
#define SMU_ALARM_ACTION_RSVD   ((Smu_CoreAlarmActionType)1U)
#define SMU_ALARM_ACTION_IGCS0  ((Smu_CoreAlarmActionType)2U)
#define SMU_ALARM_ACTION_IGCS1   ((Smu_CoreAlarmActionType)3U)
#define SMU_ALARM_ACTION_IGCS2   ((Smu_CoreAlarmActionType)4U)
#define SMU_ALARM_ACTION_NMI      ((Smu_CoreAlarmActionType)5U)
#define SMU_ALARM_ACTION_RESET    ((Smu_CoreAlarmActionType)6U)
#define SMU_ALARM_ACTION_CPU_RESET ((Smu_CoreAlarmActionType)7U)

/*SMU alarm group id*/
/* [cover parentID={1A3452AB-1955-4e1d-8F92-5E376051943F}] [/cover]*/
typedef enum
{
  SMU_ALARM_GROUP0      = 0U,
  SMU_ALARM_GROUP1      = 1U,
  SMU_ALARM_GROUP2      = 2U,
  SMU_ALARM_GROUP3      = 3U,
  SMU_ALARM_GROUP4      = 4U,
  SMU_ALARM_GROUP5      = 5U,
  SMU_ALARM_GROUP6      = 6U,
  SMU_ALARM_GROUP7      = 7U,
  SMU_ALARM_GROUP8      = 8U,
  SMU_ALARM_GROUP9      = 9U,
  SMU_ALARM_GROUP10     = 10U,
  SMU_ALARM_GROUP11     = 11U,
  SMU_ALARM_GROUP20     = 20U,
  SMU_ALARM_GROUP21     = 21U
} Smu_AlarmGroupId;

/* SMU alarm Id in each group */
/* [cover parentID={2A07D4EB-51CF-4c25-A155-370FA99894AE}][/cover]*/
typedef enum
{
  SMU_ALARM_0    = 0U,
  SMU_ALARM_1    = 1U,
  SMU_ALARM_2    = 2U,
  SMU_ALARM_3    = 3U,
  SMU_ALARM_4    = 4U,
  SMU_ALARM_5    = 5U,
  SMU_ALARM_6    = 6U,
  SMU_ALARM_7    = 7U,
  SMU_ALARM_8    = 8U,
  SMU_ALARM_9    = 9U,
  SMU_ALARM_10   = 10U,
  SMU_ALARM_11   = 11U,
  SMU_ALARM_12   = 12U,
  SMU_ALARM_13   = 13U,
  SMU_ALARM_14   = 14U,
  SMU_ALARM_15   = 15U,
  SMU_ALARM_16   = 16U,
  SMU_ALARM_17   = 17U,
  SMU_ALARM_18   = 18U,
  SMU_ALARM_19   = 19U,
  SMU_ALARM_20   = 20U,
  SMU_ALARM_21   = 21U,
  SMU_ALARM_22   = 22U,
  SMU_ALARM_23   = 23U,
  SMU_ALARM_24   = 24U,
  SMU_ALARM_25   = 25U,
  SMU_ALARM_26   = 26U,
  SMU_ALARM_27   = 27U,
  SMU_ALARM_28   = 28U,
  SMU_ALARM_29   = 29U,
  SMU_ALARM_30   = 30U,
  SMU_ALARM_31   = 31U
} Smu_AlarmIdType;

/*SFF tset results*/
/* [cover parentID={9CDA5220-4233-408b-ACDA-E913DDA5E7C9}] [/cover]*/
typedef uint8 Smu_SffTestResType;

/* SMU module configuration type - post-build configuration */
/*[cover parentID={D1AE504F-A75F-4412-BC8E-0B3A062D9E31}][/cover]*/
/*[cover parentID={1A1CB070-D698-4a4b-9220-38FCC943019D}][/cover]*/
typedef struct
{
  uint32 FSPCfg;
  uint32 AGCCfg;
  uint32 RTCCfg;
  uint32 RTAC00Cfg;
  uint32 RTAC01Cfg;
  uint32 RTAC10Cfg;
  uint32 RTAC11Cfg;
  uint32 AlarmStdbyCfg;
  uint32 AlarmCoreConfig[SMU_CORE_TOTAL_ALARM_CONFIG_REG];
  uint32 AlarmCoreFspConfig[SMU_CORE_TOTAL_ALARM_GROUPS];
  uint32 AlarmStdbyFspConfig[SMU_STDBY_TOTAL_ALARM_GROUPS];
} Smu_ConfigType;


/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/
#define SMU_START_SEC_CODE_ASIL_B_GLOBAL
#include "Smu_MemMap.h"

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
/*******************************************************************************
** Traceability     : [cover parentID={B04BBEBC-4001-4d36-B4B5-2A1442DE3350}] **
**                                                                            **
** Syntax           : Std_ReturnType Smu_Init(Smu_ConfigType* ConfigPtr)      **
**                                                                            **
** Description      : The purpose of the API is to setup the SMU peripheral   **
**                    based on the configuration. The SMU driver initializes  **
**                    the resources of the AURIX SMU peripheral, for example  **
**                    the error reaction and the Fault Signalling Protocol    **
**                    (FSP). Initialization should be done only from the      **
**                    master core.                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0xA8                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : ConfigPtr - Pointer to the SMU configuration for        **
**                                  initialization                            **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK - Operation successfully performed                 **
**                    E_NOT_OK - Operation failed eg. Driver already          **
**                    initialized.                                            **
*******************************************************************************/

extern Std_ReturnType Smu_Init
(
  const Smu_ConfigType* const ConfigPtr
);



/*******************************************************************************
** Traceability      : [cover parentID={AF259B1B-60B1-4c22-BB8F-6E2B3453AFDC}]**
**                                                                            **
** Syntax           : Std_ReturnType Smu_DeInit(void)                         **
**                                                                            **
** Description      :Deinitializes the SMU driver by reseting the module      **
**                   registers. Deinitialization shall be done only from      **
**                   master core.                                             **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0xAA                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK - Operation successfully performed                 **
**                    E_NOT_OK - Operation failed                             **
*******************************************************************************/

extern Std_ReturnType Smu_DeInit(void);


/*******************************************************************************
** Traceability      : [cover parentID={6764836C-E38B-4182-AAD7-7FF688427633}]**
**                                                                            **
** Syntax           : Std_ReturnType Smu_GetAlarmAction                       **
**                    (                                                       **
**                      const Smu_AlarmGroupId AlarmGroup,                    **
**                      const Smu_AlarmIdType AlarmPos,                       **
**                      Smu_CoreAlarmActionType* const IntAlarmAction,        **
**                      Smu_FSPActionType* const FSPAction                    **
**                    )                                                       **
**                                                                            **
** Service ID       : 0x3                                                     **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : AlarmGroup : Alarm group register                       **
**                    AlarmPos   : Alarm position within the requested group  **
**                                                                            **
** Parameters (out) : IntAlarmAction: Alarm action for the requested alarm    **
**                    FSPAction  : FSP action for the requested alarm         **
**                                                                            **
** Return value     : E_OK - Operation successfully performed                 **
**                    E_NOT_OK - Operation failed eg. Due to invalid          **
**                      parameters.                                           **
**                                                                            **
** Description      : The purpose of the API is to provide the internal alarm,**
**                    FSP action currently configured for the requested alarm.**
*******************************************************************************/
extern Std_ReturnType Smu_GetAlarmAction
(
  const Smu_AlarmGroupId AlarmGroup,
  const Smu_AlarmIdType AlarmPos,
  Smu_CoreAlarmActionType* const IntAlarmAction,
  Smu_FSPActionType* const FSPAction
);


/*******************************************************************************
** Traceability     :[cover parentID={969BDF14-FEEB-4224-A413-F16A79239E4C}]  **
**                                                                            **
** Syntax           : Std_ReturnType Smu_SetAlarmAction                       **
**                    (                                                       **
**                      const Smu_AlarmGroupId AlarmGroup,                    **
**                      const Smu_AlarmIdType AlarmPos,                       **
**                      const Smu_CoreAlarmActionType AlarmAction             **
**                      const Smu_FSPActionType FSPAction)                    **
**                                                                            **
** Service ID       : 0x4                                                     **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : AlarmGroup : Alarm group register                       **
**                    AlarmPos   : Alarm position within the requested group  **
**                    AlarmAction: Alarm action for the requested alarm       **
**                    FSPAction:FSP alarm action to be configured             **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK - Operation successfully performed                 **
**                    E_NOT_OK - Operation failed eg. Due to invalid          **
**                      parameters. SMU lock already activated                **
**                                                                            **
** Description      : The purpose of the API is to set the desired alarm      **
**                    action for the group and position specified.            **
*******************************************************************************/
extern Std_ReturnType Smu_SetAlarmAction
(
  const Smu_AlarmGroupId AlarmGroup,
  const Smu_AlarmIdType AlarmPos,
  const Smu_CoreAlarmActionType AlarmAction,
  const Smu_FSPActionType FSPAction
);

/*******************************************************************************
** Traceability     : [cover parentID={288D8F0D-7CD5-44c2-9DD7-4B5F8A69DE7D}] **
**                                                                            **
** Syntax           : Std_ReturnType Smu_LockConfigRegs(void)                 **
**                                                                            **
** Service ID       : 0x9                                                     **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK - Operation successfully performed                 **
**                    E_NOT_OK - Operation failed eg. Config registers already**
**                                 locked                                     **
**                                                                            **
**                                                                            **
** Description      : The purpose of the API is to lock the SMU configuration **
**                    registers to prevent any modification to configuration  **
**                    register content.                                       **
*******************************************************************************/
extern Std_ReturnType Smu_LockConfigRegs(void);


/*******************************************************************************
** Traceability      : [cover parentID={5A7DB499-BDAF-40c7-8E30-DA6DBFFE4B76}]**
**                                                                            **
** Syntax           : Std_ReturnType Smu_ActivateRunState (const uint32 Cmd)  **
**                                                                            **
** Service ID       : 0x13                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : Cmd       : Command to switch the SMU to the RUN state  **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK - Operation successfully performed                 **
**                    E_NOT_OK - Operation failed eg. SMU not in START state, **
**                                 invalid command                            **
**                                                                            **
** Description      : This API allows to switch the SMU peripheral into the   **
**                    RUN fault-free state as requested by the caller.        **
**                    The SMU validates the request based                     **
**                    on its own integrity checks (i.e. check of the command  **
**                    value). In the negative case the SMU shall be           **
**                    permanently blocked in the fault state and no further   **
**                    action shall be possible. On reaching the RUN state,    **
**                    the processing of the alarms and triggering of the      **
**                    internal/external reactions is enabled and hence the    **
**                    SMU is now able to trigger the safe state/ inform       **
**                    application based on the configuration, in case of an   **
**                    alarm.                                                  **
*******************************************************************************/
extern Std_ReturnType Smu_ActivateRunState(const uint32 Cmd);
/*******************************************************************************
** Traceability      : [cover parentID={E9869FA4-F02D-4635-8028-136CCF94FCBF}]**
**                                                                            **
** Syntax           : Std_ReturnType Smu_ClearAlarmStatus                     **
**                    (                                                       **
**                      const Smu_AlarmGroupId AlarmGroup,                    **
**                      const Smu_AlarmIdType AlarmPos                        **
**                    )                                                       **
**                                                                            **
** Description      : This service clears SMU alarm status of the requested   **
**                    alarm.                                                  **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0xAD                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : AlarmGroup : Alarm group register                       **
**                    AlarmPos : Alarm position within the requested group    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK - Operation successfully performed                 **
**                    E_NOT_OK - Operation failed eg. Due to invalid          **
**                      parameters.                                           **
*******************************************************************************/
extern Std_ReturnType Smu_ClearAlarmStatus
(
  const Smu_AlarmGroupId AlarmGroup,
  const Smu_AlarmIdType AlarmPos
);


/*******************************************************************************
** Traceability     : [cover parentID={474BDCAA-C380-4ce2-AEBB-FEF0F93F2CA9}] **
**                                                                            **
** Syntax           : Std_ReturnType Smu_SetAlarmStatus                       **
**                    (                                                       **
**                      const Smu_AlarmGroupId AlarmGroup,                    **
**                      const Smu_AlarmGroupId AlarmPos                       **
**                    )                                                       **
**                                                                            **
** Service ID       : 0x6                                                     **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : AlarmGroup : Alarm group register                       **
**                    AlarmPos : Alarm position within the requested group    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK - Operation successfully performed                 **
**                    E_NOT_OK - Operation failed eg. Due to invalid          **
**                      parameters.                                           **
**                                                                            **
** Description      : The purpose of the API is to set the requested          **
**                    alarm status. This service can be used by the user      **
**                    software to trigger SW SMU alarm. For Smu_core during   **
**                    the START  state of the SMU, it shall be possible to    **
**                    set any of the alarms. However,during the RUN state,    **
**                    only the SW alarms shall be set.                        **
*******************************************************************************/
extern Std_ReturnType Smu_SetAlarmStatus
(
  const Smu_AlarmGroupId AlarmGroup,
  const Smu_AlarmIdType AlarmPos
);

/*******************************************************************************
** Traceability      :[cover parentID={2555771A-6BE0-4ba4-9FDA-F301A662610B}] **
**                                                                            **
** Syntax           : Std_ReturnType Smu_GetAlarmStatus                       **
**                    (                                                       **
**                      const Smu_AlarmGroupId AlarmGroup,                    **
**                      uint32* const AlarmStatus                             **
**                    )                                                       **
**                                                                            **
** Service ID       : 0x7                                                     **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : AlarmGroup : Alarm group register                       **
**                                                                            **
** Parameters (out) : AlarmStatus: Status of the Alarm register               **
**                                                                            **
** Return value     : E_OK - Operation successfully performed                 **
**                    E_NOT_OK - Operation failed eg. Due to invalid          **
**                      parameters.                                           **
**                                                                            **
** Description      : The purpose of the API is to provide the alarm status   **
**                      requested alarm group.                                **
*******************************************************************************/
extern Std_ReturnType Smu_GetAlarmStatus
(
  const Smu_AlarmGroupId AlarmGroup,
  uint32* const AlarmStatus
);


/*******************************************************************************
** Traceability      :[cover parentID={26FB7351-B093-434b-A30E-F9BE2DA12080}] **
**                                                                            **
** Syntax           : Std_ReturnType Smu_GetAlarmDebugStatus                  **
**                    (                                                       **
**                      const Smu_AlarmGroupId AlarmGroup,                    **
**                      uint32* const AlarmStatus                             **
**                    )                                                       **
**                                                                            **
** Service ID       : 0x8                                                     **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : AlarmGroup : Alarm group register                       **
**                                                                            **
** Parameters (out) : AlarmStatus: Status of the Alarm register               **
**                                                                            **
** Return value     : E_OK - Operation successfully performed                 **
**                    E_NOT_OK - Operation failed eg. Due to invalid          **
**                      parameters.                                           **
**                                                                            **
** Description      : The purpose of the API is to provide the alarm status   **
**                      for the requested alarm group from the stored debug   **
**                      registers.It is applicable only for Smu_core.         **
*******************************************************************************/
extern Std_ReturnType Smu_GetAlarmDebugStatus
(
  const Smu_AlarmGroupId AlarmGroup,
  uint32* const AlarmStatus
);

/*******************************************************************************
** Traceability     : [cover parentID={A001457A-1DCC-48c1-9D56-C167B076C012}] **
**                                                                            **
** Syntax           : Std_ReturnType Smu_SetupErrorPin(void)                  **
**                                                                            **
** Service ID       : 0xC                                                     **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK - Operation successfully performed                 **
**                    E_NOT_OK - Operation failed eg. already in SMU mode     **
**                                                                            **
**                                                                            **
** Description      : This service enables the SMU to control the error pin   **
**                    and hence activate the safe state via the FSP. This API **
**                    switches the error pin from GPIO mode to SMU mode.      **
**                    Only after switching to the SMU mode, SMU can control   **
**                    the error pin (i.e by Alarm, Activate, Release APIs)    **
*******************************************************************************/
extern Std_ReturnType Smu_SetupErrorPin(void);

/*******************************************************************************
** Traceability     : [cover parentID={E9D7EA34-BB9E-45f1-8EED-F89C5AA17DA5}] **
**                                                                            **
** Syntax           : Std_ReturnType Smu_ReleaseErrorPin(void)                **
**                                                                            **
** Service ID       : 0XD                                                     **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Re-entrant                                              **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK - Operation successfully performed                 **
**                    E_NOT_OK - Operation failed eg. Configuration is locked **
**                                                                            **
** Descripition:      This API switches the error pin from SMU mode           **
**                    to GPIO mode.                                           **
*******************************************************************************/
extern Std_ReturnType Smu_ReleaseErrorPin(void);

/*******************************************************************************
** Traceability      : [cover parentID={23EABD59-5B57-464d-A9C3-63C45653C383}]**
**                                                                            **
** Syntax           : Std_ReturnType Smu_ReleaseFSP(void)                     **
**                                                                            **
** Service ID       : 0xA                                                     **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK - Operation successfully performed                 **
**                    E_NOT_OK - Operation failed eg. Due to invalid          **
**                    conditions i.e.transition from FAULT to RUN is disabled.**
**                                                                            **
** Description      : The purpose of the API is to switch the SMU peripheral  **
**                    from the FAULT state to the RUN state. This also        **
**                    switches the error pin from the FAULT state to          **
**                    FAULT-FREE state. Additionally, this API can be used    **
**                    change the FSP state from the power-on state to the     **
**                    Fault-free state. This is essential to setup the error  **
**                    pin to drive the FSP.It is also required for testing of **
**                    FSP pin                                                 **
*******************************************************************************/
extern Std_ReturnType Smu_ReleaseFSP(void);


/*******************************************************************************
** Traceability     : [cover parentID={CC28E023-9FD7-4f99-BCCC-55D4AFFAADF3}] **
**                                                                            **
** Syntax           : Std_ReturnType Smu_ActivateFSP (void)                   **
**                                                                            **
** Service ID       : 0xB                                                     **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK - Operation successfully performed                 **
**                    E_NOT_OK - Operation failed eg. SMU not initialized     **
**                                                                            **
** Description      : This API activates the FSP to indicate a FAULT state on **
**                    the error pin to the safe state switching device. Also, **
**                    in the SMU START state, activation of FSP is only       **
**                    possible using this API as alarms are NOT processed.    **
**                    Additionally, this is required for the testing of the   **
**                    FSP timing                                              **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Smu_ActivateFSP(void);

/*******************************************************************************
** Traceability      :[cover parentID={5DEE019E-6A73-49f3-97B4-93E28844ADE6}] **
**                                                                            **
** Syntax           : Std_ReturnType Smu_RTStop(const uint8 TimerNum )        **
**                                                                            **
** Service ID       : 0xE                                                     **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : TimerNum : Identifies the Recovery Timer unit to be     **
**                      stopped                                               **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK - Operation successfully performed                 **
**                    E_NOT_OK - Operation failed eg. Due to invalid          **
**                                 parameters                                 **
**                                                                            **
**                                                                            **
** Description      : The purpose of the API is to stop the requested recovery**
**                    timer unit. Possible usecase: When an fault occurs,     **
**                    error handler might be triggered. However, this error   **
**                    handler should setup a recovery mechanism or error      **
**                    mitigation mechanism within a finite interval of time   **
**                    to prevent the system from failing.                     **
*******************************************************************************/
extern Std_ReturnType Smu_RTStop(const uint8 TimerNum );


/*******************************************************************************
** Traceability      :[cover parentID={F7F8E849-20E0-413d-B603-B55F711DF221}] **
**                                                                            **
** Syntax           : Std_ReturnType Smu_GetRTMissedEvent                     **
**                    (                                                       **
**                      const uint8 TimerNum,                                 **
**                      boolean* const EventMissed                            **
**                    )                                                       **
**                                                                            **
** Service ID       : 0xF                                                     **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : TimerNum : Identifies the Recovery Timer unit to be     **
**                    stopped                                                 **
**                                                                            **
** Parameters (out) : EventMissed                                             **
**                    TRUE: Event has been missed                             **
**                    FALSE: Event has NOT been missed                        **
**                                                                            **
** Return value     : E_OK - Operation successfully performed                 **
**                    E_NOT_OK - Operation failed eg. Due to invalid          **
**                                 parameters                                 **
**                                                                            **
**                                                                            **
** Description      : The purpose of the API is to know if any alarms         **
**                    requiring the requested recovery timer was SET while    **
**                    the recovery timer was running.                         **
*******************************************************************************/
extern Std_ReturnType Smu_GetRTMissedEvent
(
  const uint8 TimerNum,
  boolean* const EventMissed
);

/*******************************************************************************
** Traceability      :[cover parentID={8B53101F-9B99-48c0-92B7-6792A141297E}] **
**                                                                            **
** Syntax           : Smu_CoreStateType Smu_GetSmuState (void)                **
**                                                                            **
** Service ID       : 0x12                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : SMU_START - SMU is in the START state                   **
**                  : SMU_RUN   - SMU is in the RUN state                     **
**                  : SMU_FAULT    - SMU is in the FAULT state                **
**                                                                            **
** Description      : The purpose of the API is to provide the current state  **
**                    of the Smu_core. This is referred to as the safety      **
**                    status of the system as all critical faults will cause  **
**                    the SMU to go to the FAIL state as configured by the    **
**                    user.                                                   **
*******************************************************************************/
extern Smu_CoreStateType Smu_GetSmuState(void);

/*******************************************************************************
** Traceability      : [cover parentID=]        [/cover]                      **
**                                                                            **
** Syntax           : Std_ReturnType Smu_ActivatePES (void)                   **
**                                                                            **
** Service ID       : 0x10                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK - Operation successfully performed                 **
**                    E_NOT_OK - Operation failed eg. Due to invalid          **
**                                 parameters                                 **
**                                                                            **
** Description      : Triggers the activation of the Port Emergency Stop(PES).**
**                   The PES is also directly controlled by the SMU_core when **
**                   entering the FAULT state.                                **
*******************************************************************************/
extern Std_ReturnType Smu_ActivatePES (void);

/*******************************************************************************
** Traceability      :[cover parentID={088D792F-9D76-4472-A6C9-741D9C26C61E}] **
**                                                                            **
** Syntax           : Std_ReturnType Smu_CoreAliveTest (void)                 **
**                                                                            **
** Service ID       : 0x15                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK - Operation successfully performed                 **
**                    E_NOT_OK - Operation failed eg. Due to invalid          **
**                                 parameters                                 **
**                                                                            **
** Description      : This API provides the means to execute the Smu_CoreAlive**
**                  command which checks the Smu_core_alive signal. the       **
**                  Smu_stdby has to remain enabled to execute this command.  **
*******************************************************************************/
extern Std_ReturnType Smu_CoreAliveTest (void);

/*******************************************************************************
** Traceability      :[cover parentID={4A9763EF-63A4-4888-88FD-5E75716ED268}] **
**                                                                            **
** Syntax           : Std_ReturnType Smu_GetAlarmExecutionStatus              **
**                  (const uint32 AlarmExecStatusReq,                         **
**                      uint32* const AlarmExecStatus)                        **
** Service ID       : 0x17                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : AlarmExecStatusReq : Alarm exceution status request     **
**                                                                            **
** Parameters (out) : AlarmExecStatus: Status of the Alarm execution status   **
**                    register                                                **
**                                                                            **
** Return value     : E_OK - Operation successfully performed                 **
**                    E_NOT_OK - Operation failed eg. Due to invalid          **
**                      parameters.                                           **
**                                                                            **
** Description      : This API get the status of the alarm reactions          **
**                    executed.                                               **
*******************************************************************************/
extern Std_ReturnType Smu_GetAlarmExecutionStatus(
  const uint32 AlarmExecStatusReq,
  uint32* const AlarmExecStatus);

/*******************************************************************************
** Traceability      : [cover parentID={625BDBDC-549F-4429-9289-E48015B2B9B2}]**
**                                                                            **
** Syntax           : Std_ReturnType Smu_ClearAlarmExecutionStatus            **
**                  (const uint32 AlarmExecStatusReq)                         **
** Service ID       : 0x18                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : AlarmExecStatusReq : Alarm exceution status request     **
**                                                                            **
** Parameters (out) : AlarmExecStatus: Status of the Alarm execution status   **
**                    register                                                **
**                                                                            **
** Return value     : E_OK - Operation successfully performed                 **
**                    E_NOT_OK - Operation failed eg. Due to invalid          **
**                      parameters.                                           **
**                                                                            **
** Description      : This API clear the status of the alarm reactions        **
**                    executed.                                               **
*******************************************************************************/
extern Std_ReturnType Smu_ClearAlarmExecutionStatus
(
  const uint32 AlarmExecStatusReq
);

/*******************************************************************************
** Traceability      :[cover parentID={CDC49D92-3240-4011-A48F-65600AECD8EB}] **
**                                                                            **
** Syntax           : Std_ReturnType Smu_RegisterMonitor                      **
**                    (                                                       **
**                      const uint16 * const RegMonPtr,                       **
**                      Smu_SffTestResType * const  RegMonResult              **
**                    )                                                       **
**                                                                            **
** Service ID       : 0x11                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : RegMonPtr : Alarm group register                        **
**                                                                            **
** Parameters (out) : RegMonResult: Status of the SFF test irrespective of    **
**                    the RMCTL bit enabled/disabled                          **
**                                                                            **
** Return value     : E_OK - Operation successfully performed                 **
**                    E_NOT_OK - Operation failed eg. Due to invalid          **
**                      parameters.                                           **
**                                                                            **
** Description      : This API provides the initialization, execution and     **
**                    termination of the SafetyFlipFlop Tests to be executed  **
**                    for different modules as per the configuration.         **
*******************************************************************************/
extern Std_ReturnType Smu_RegisterMonitor
(
  const uint16 * const RegMonPtr, Smu_SffTestResType * const  RegMonResult
);

#if(SMU_INIT_CHECK_API==STD_ON)
/*******************************************************************************
** Traceability      : [cover parentID=]        [/cover]                      **
**                                                                            **
** Syntax           :Std_ReturnType Smu_InitCheck (const Smu_ConfigType*      **
**                   const ConfigPtr)                                         **
**                                                                            **
** Service ID       : 0x16                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different cores                           **
**                                                                            **
** Parameters(in)   : RegMonPtr : Alarm group register                        **
**                                                                            **
** Parameters (out) : AlarmStatus: Status of the Alarm register               **
**                                                                            **
** Return value     : E_OK - Operation successfully performed                 **
**                    E_NOT_OK - Operation failed eg. Due to invalid          **
**                      parameters.                                           **
**                                                                            **
** Description      : This API checks the initialization values after SMU is  **
**                    initialized. It should be called after Smu_Init to check**
**                    the initialization values.                              **
*******************************************************************************/
extern Std_ReturnType Smu_InitCheck (const Smu_ConfigType* const ConfigPtr);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Smu_InitCheck(ConfigPtr)     \
                              (ERROR_Smu_InitCheck_API_IS_NOT_SELECTED)
#endif

#if (SMU_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Traceability      :[cover parentID={0718DB96-C902-43cd-A42E-FC4059BD228D}] **
**                                                                            **
** Syntax           :void Smu_GetVersionInfo(Std_VersionInfoType              **
**                   * const VersionInfoPtr)                                  **
**                                                                            **
** Service ID       : 0x14                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out):  VersionInfoPtr - Pointer to store the                   **
**                    version information of this module.                     **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : This function returns the version information of this   **
**                    module. The version information include :               **
**                    Module ID, Vendor ID. Vendor specific version numbers   **
**                    This function is available if the SMU_VERSION_INFO_API  **
**                    is set ON                                               **
*******************************************************************************/
extern void Smu_GetVersionInfo(Std_VersionInfoType * const VersionInfoPtr);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when an optional function is called by application
  and not enabled in the configuration*/
#define Smu_GetVersionInfo(VersionInfoPtr)     \
                              (ERROR_Smu_GetVersionInfo_API_IS_NOT_SELECTED)
#endif

#define SMU_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Smu_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
#include "Smu_MemMap.h"

#include "Smu_PBcfg.h"
#endif
