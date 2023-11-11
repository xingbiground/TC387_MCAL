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
**  FILENAME     : Smu.c                                                      **
**                                                                            **
**  VERSION      : 40.0.0                                                     **
**                                                                            **
**  DATE         : 2023-05-24                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  TRACEABILITY :  [cover parentID={815FDDAE-0BA0-48d5-9822-E887D8DF54B8},   **
**                                  {7B2B919A-48D4-42ec-9EAB-C8703FCC451B},   **
**                                  {F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}]   **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Smu Driver source file                                     **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/


/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/*[cover parentID={BFB18007-C83F-439b-A0C6-A894B5B71D9E}]
Header file inclusions for Imported SW Interfaces
[/cover]*/
/*[cover parentID={825C220C-45ED-44f2-9CDA-CE9D43F07B83}]
File Structure
[/cover]*/

#include "McalLib.h"
#include "Smu.h"
#include "SchM_Smu.h"

#include "IfxSmu_bf.h"
#include "IfxSmu_reg.h"
#include "IfxPms_bf.h"
#include "IfxPms_reg.h"

#if (SMU_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

#if(SMU_SAFETY_ENABLE == STD_ON)
#include "Mcal_SafetyError.h"
#endif

/*******************************************************************************
**                          User Mode Supoort Macros                          **
*******************************************************************************/
/*[cover parentID={2A02D62C-64C2-4af4-90F1-753403F5273A}]
User Mode Execution
[/cover]*/

#if( (SMU_INIT_DEINIT_API_MODE != SMU_MCAL_SUPERVISOR)||\
     (SMU_RUNTIME_API_MODE != SMU_MCAL_SUPERVISOR) )
#include "McalLib_OsStub.h"
#endif

#if SMU_INIT_DEINIT_API_MODE  == SMU_MCAL_SUPERVISOR
/* Library APIs  */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG'
 * defined for User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(RegAdd,Data)   \
Mcal_WriteSafetyEndInitProtReg(RegAdd,Data)
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREGMASK'
 * defined for User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
#define SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREGMASK(RegAdd,Data,Mask)    \
Mcal_WriteSafetyEndInitProtRegMask(RegAdd,Data,Mask)
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'SMU_SFR_INIT_DEINIT_WRITE32'
 * defined for User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define  SMU_SFR_INIT_DEINIT_WRITE32(reg, value)    ((*(reg)) = (uint32)(value))
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG'
 * defined for User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(RegAdd,Data)    \
MCAL_LIB_WRITESAFETYENDINITPROTREG(RegAdd,Data)
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREGMASK'
 * defined for User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
#define SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREGMASK(RegAdd,Data,Mask)    \
MCAL_LIB_WRITESAFETYENDINITPROTREGMASK(RegAdd,Data,Mask)
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'SMU_SFR_INIT_DEINIT_WRITE32'
 * defined for User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define  SMU_SFR_INIT_DEINIT_WRITE32(reg, value)   \
                               MCAL_SFR_OS_WRITE32(SMU_MODULE_ID, reg, value)
#endif

#if SMU_RUNTIME_API_MODE  == SMU_MCAL_SUPERVISOR
/* Library APIs  */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG'
 * defined for User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG(RegAdd,Data)    \
Mcal_WriteSafetyEndInitProtReg(RegAdd,Data)
/* Supervisory mode registers */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'SMU_SFR_RUNTIME_WRITE32'
 * defined for User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define  SMU_SFR_RUNTIME_WRITE32(reg, value)    ((*(reg)) = (uint32)(value))
#else
/* Library APIs  */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG'
 * defined for User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG(RegAdd,Data)    \
MCAL_LIB_WRITESAFETYENDINITPROTREG(RegAdd,Data)
/* Supervisory mode registers */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'SMU_SFR_RUNTIME_WRITE32'
 * defined for User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define  SMU_SFR_RUNTIME_WRITE32(reg, value)    \
MCAL_SFR_OS_WRITE32(SMU_MODULE_ID, reg, value)

#endif



/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/
#ifndef SMU_SW_MAJOR_VERSION
  #error "SMU_SW_MAJOR_VERSION is not defined."
#endif

#ifndef SMU_SW_MINOR_VERSION
  #error "SMU_SW_MINOR_VERSION is not defined."
#endif

#ifndef SMU_SW_PATCH_VERSION
  #error "SMU_SW_PATCH_VERSION is not defined."
#endif

#if ( SMU_SW_MAJOR_VERSION != 20U )
  #error "SMU_SW_MAJOR_VERSION does not match."
#endif

#if ( SMU_SW_MINOR_VERSION != 25U )
  #error "SMU_SW_MINOR_VERSION does not match."
#endif

#if ( SMU_SW_PATCH_VERSION != 0U )
  #error "SMU_SW_PATCH_VERSION does not match."
#endif
/*[cover parentID={6867086D-86C6-4eb6-962C-ABF2FC465496}] [/cover]*/
/*[cover parentID={E86BC0A7-8DEE-4818-AFCA-A9C02F2E61A6}] [/cover]*/
#if (SMU_DEV_ERROR_DETECT == STD_ON)

  #ifndef DET_AR_RELEASE_MAJOR_VERSION
    #error "DET_AR_RELEASE_MAJOR_VERSION is not defined."
  #endif

  #if ( DET_AR_RELEASE_MAJOR_VERSION != 4U )
    #error "DET_AR_RELEASE_MAJOR_VERSION does not match."
  #endif

#endif

#if ((SMU_ACTIVATE_RUN_STATE_FAILURE_DEM_NOTIF == SMU_ENABLE_DEM_REPORT)||\
     (SMU_CLEAR_ALARM_STATUS_DEM_NOTIF == SMU_ENABLE_DEM_REPORT)||\
     (SMU_RELEASE_FSP_DEM_NOTIF == SMU_ENABLE_DEM_REPORT)||\
     (SMU_CORE_ALIVE_FAILURE_DEM_NOTIF == SMU_ENABLE_DEM_REPORT)||\
     (SMU_RT_STOP_FAILURE_DEM_NOTIF == SMU_ENABLE_DEM_REPORT)||\
     (SMU_ACTIVATE_PES_FAILURE_DEM_NOTIF == SMU_ENABLE_DEM_REPORT)||\
     (SMU_ACTIVATE_FSP_FAILURE_DEM_NOTIF == SMU_ENABLE_DEM_REPORT)||\
     (SMU_SET_ALARM_STATUS_DEM_NOTIF == SMU_ENABLE_DEM_REPORT)||\
     (SMU_SFF_TEST_FAILURE_DEM_NOTIF == SMU_ENABLE_DEM_REPORT))
#include "Mcal_Wrapper.h"
#endif
/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
#if ((SMU_DEV_ERROR_DETECT == STD_ON) || \
(SMU_SAFETY_ENABLE == STD_ON) ||(SMU_INIT_CHECK_API == STD_ON))
/* Driver initialization flag */
#define SMU_INITIALIZED      (0x1U)
#define SMU_NOT_INITIALIZED  (0x0U)

/* Error Pin  initialization flag */
#define SMU_ERRPIN_SET       (0x1U)
#define SMU_ERRPIN_NOTSET    (0x0U)

/* SMU Driver status */
#define SMU_FAILED           (0x1U)
#define SMU_NOT_FAILED       (0x0U)

/* SMU Configuration registers lock flag */
#define SMU_LOCKED           (0x1U)
#define SMU_NOT_LOCKED       (0x0U)
#endif

/* SMU SW alarm to validate API input parameter */
#define SMU_SW_ALARM_GROUP   (10U)

/* SMU Command Argument bit position in the CMD register */
#define SMU_CMD_ARG_BIT_POS  (4U)

/* SMU configuration - permanent lock value on and cfg(temp) lock on*/
#define SMU_CFG_PERLCK_ON_CFGLCK_ON  (0x0000FF00U)

/* SMU configuration - permanent lock value off and cfg(temp) lock off*/
#define SMU_CFG_PERLCK_OFF_CFGLCK_OFF  (0x000000BCU)

/* SMU configuration unlock lock value */
#define SMU_CFG_KEY_UNLOCK  ((SMU_KEYS.U & (uint32)(0xFFFFFF00U)) | \
                              ((uint32)0xBCU))
#define SMU_CFG_KEY_TEMPLOCK (0x0U)

/* Status of SMU CMD execution sucess value in SMU_STS.B.RES bit*/
#define SMU_COMMAND_SUCCESS  (0x0U)
#define SMU_COMMAND_FAILURE  (0x1U)

/*Alarm status readback result*/
#define SMU_CLEAR_ALARM_STATUS_READBACK (0x0U)
#define SMU_SET_ALARM_STATUS_READBACK (0x1U)

/* The mask for the Alarm group configuration from 3 bit value for each
CFG registers*/
#define SMU_ALMGRP_CFG0_MASK (0x1U)
#define SMU_ALMGRP_CFG1_MASK (0x2U)
#define SMU_ALMGRP_CFG2_MASK (0x4U)

/*The masks for error pin set and release*/
#define SMU_PCTL_MASK (0x80U)
#define SMU_PCTL_HWEN_POS (2U)
#define SMU_PCTL_GF_SCU (4U)
#define SMU_PCTL_GF_STS (5U)
#define SMU_PCTL_RESET_VAL (0x00088000U)

/* SMU registers  Reset values */
#define SMU_FSP_RESET_VAL       (0x003FFF00U)
#define SMU_AGC_RESET_VAL       (0x0U)
#define SMU_RTC_RESET_VAL       (0x003FFF03U)
#define SMU_RTAC00_RESET_VAL     (0x00A80108U)
#define SMU_RTAC01_RESET_VAL     (0x00C800B8U)
#define SMU_RTAC10_RESET_VAL     (0x00E800D8U)
#define SMU_RTAC11_RESET_VAL     (0x00F800F8U)
#define SMU_ALARM_CFG_RESET_VAL (0x0U)
#define SMU_ALARM8_CFG_RESET_VAL (0x0001FC00U)
#define SMU_ALARM10_CFG_RESET_VAL (0x00030000U)
#define SMU_ALARM_FSP_RESET_VAL (0x0U)
#define SMU_AGFSPSTDBY0_RESET_VAL  (0x0U)
#define SMU_AGFSPSTDBY1_RESET_VAL   (0x0U)
#define SMU_CMD_STDBY_RESET_VAL   (0x0U)
#define SMU_RMSTS_RESETVAL (0x0U)
#define SMU_RMEF_RESETVAL (0x0U)
#define SMU_RMCTL_RESETVAL (0x0U)
#define SMU_AG_SET_ALL          (0xFFFFFFFFU)

/* Mask for extracting the FSP action from Register after shift */
#define SMU_ALARM_FSP_MASK      ((uint8)0x1U)

/*Mask to test whether SMU alarm can be configured*/
#define SMU_ALARM_VALID (0x1U)

/*Macro to offset a value by half word*/
#define SMU_HALF_WORD_OFFSET (0x10U)

/*Macros for register monitoring*/
#define SMU_TOTAL_RMCTL_BITS (0xBU)
#define SMU_SFF_TEST_ENABLE (0x1U)

/*JIRA Reference: 0000053912-10134
The time required for completion of Register Monitor test depends on the
frequency settings for the module under test. Maximum time is required for
Register monitor test of IOM, as it has module specific clock divider
IOM_CLC.RMC, which further divdes the SPB frequency.
Based on the results of hardware testing, the maximum number of while loop
iterations for completion of Register Monitor test is 310, when
Register monitor test of IOM is enabled, Fsource0=PLL0 Frequency = 100Mhz,
SPBDIV=4, IOM_CLC.RMC=255 and Compiler=Dcc.
Based on these results, SFF_RM_TIMEOUT is set to 0x168U(360), considering
15% tolerance on maximum value.*/
#define SFF_RM_TIMEOUT (0x168U)

/*JIRA Reference: 0000053912-7453
One SPB cycle can correspond to minimum one CPU cycle and
maximum six CPU cycles, depending on the configurations.
One readback while loop iteration correspond to minimum six CPU cycle,
depending on the compiler and compiler options.
Hence, atleast one SPB cycle delay is achieved by each iteration of the
readback while loop.

The time required for status update into SMU_STS register after a command is
written to SMU_CMD register is one SPB cycle.
Based on these calculations, SMU_CMDSTATUS_TIMEOUT is set to 2, considering
tolerance of one extra iteration.

Similarly, the time required for alarm status update into SMU_AGx register
can be upto four SPB cycle.
Based on these calculations, SMU_AGSTATUS_TIMEOUT is set to 5, considering
tolerance of one extra iteration.
*/
#define SMU_CMDSTATUS_TIMEOUT   (2U)
#define SMU_AGSTATUS_TIMEOUT (5U)

/*AGCF Masks for alarm positions*/
#define SMU_ALARM_POS1 (1U)
#define SMU_ALARM_POS2 (2U)
#define SMU_GROUP8_CFG_POS1 (24U)
#define SMU_GROUP8_CFG_POS2 (26U)
#define SMU_GROUP10_CFG_POS1 (31U)
#define SMU_GROUP10_CFG_POS2 (32U)

/*RT Missed event position*/
#define SMU_RT0_MISSED_EVENT (0x20000U)
#define SMU_RT1_MISSED_EVENT (0x80000U)

/*Alarm action masks*/
#define SMU_ALMACTION_MSK      (3U)
#define SMU_FSP_ACTION_MSK     (1U)

/*Macros if DET is enabled*/
#if (SMU_DEV_ERROR_DETECT == STD_ON)||(SMU_SAFETY_ENABLE == STD_ON)
/*SMU per lock value*/
#define SMU_CFG_PERLCK_VALUE (0xFFU)
/*SMU alarm valid/invalid mask*/
#define SMU_ALARM_INVALID (0x0U)
/*SMU permanent lock check mask*/
#define SMU_LOCK_MSK           (8U)
/*SMU alarm execution status check mask*/
#define SMU_ALMEXEC_MSK        (31U)

/* SMU maximum recovery timers */
#define SMU_MAX_RECOV_TIM    (0x2U)
/* Mask for SMU permanent lock */
#define SMU_KEY_PERLOCK_MASK    (0xFF00U)
#endif/*End of DET check masks*/

/*Macros available if Smu_stdby is enabled*/
#if SMU_STANDBY_SWITCH == STD_ON
#define SMU_STDBY_BIT_PROT (0x40000000U)
#define SMU_CMD_FSP_RESET (0x40000009U)
#define SMU_STDBY_F1_MSK (0x2U)
#define SMU_STDBY_F0_MSK (0x1U)
#define SMU_ALIVE_TEST_START    ((uint8)0x5U)
#define SMU_ALIVE_TEST_STOP    ((uint8)0xAU)
/*Enabling the disabling bit protection for Smu_stdby CMD register*/
#define SMU_STDBY_ASCE_COMMAND (0x8U)
#else
#define SMU_STDBY_BIT_PROT (0x0U)
#endif/*End of Smu_stdby enable check masks*/

/*Spinlock timeout value*/
#define SMU_SPINLOCK_TIMEOUT   (8192U)

/*Mask for all configuration fields of FSP register except FSP mode*/
#define SMU_FSP_MODE_MSK  (uint32)((uint32)IFX_SMU_FSP_MODE_MSK \
                                  << IFX_SMU_FSP_MODE_OFF)

/*Mask for all configuration fields of FSP register except FSP mode*/
#define SMU_FSP_CFG_MSK  (uint32)(~SMU_FSP_MODE_MSK)

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
/*[cover parentID={22DA4B9E-BACA-444d-AF9E-4B6B656A5A88}] [/cover]*/
/*[cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}] [/cover]*/
/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}] [/cover]*/
/*[cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}] [/cover]*/
/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}] [/cover]*/
/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}] [/cover]*/
/*[cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}] [/cover]*/

#define SMU_START_SEC_VAR_INIT_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Smu_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of global status variables
 * before include of memap.h - Accepted deviation in AUTOSAR */
#include "Smu_MemMap.h"

#if ((SMU_DEV_ERROR_DETECT == STD_ON) || (SMU_SAFETY_ENABLE == STD_ON) ||\
     (SMU_INIT_CHECK_API == STD_ON))
/*Global variable to store initialization status*/
/*[cover parentID={610F7DF6-E647-43fe-9E36-D3C5C0CE4C48}] [/cover]*/
static uint32 Smu_InitStatus = SMU_NOT_INITIALIZED;

/*Global variable to store error pin status*/
/*[cover parentID={AF223FA2-14DD-486d-9702-AD4FA5601FA2}] [/cover]*/
static uint32 Smu_ErrPinStatus = SMU_ERRPIN_SET;

/*Global variable to store permanent lock status status*/
/*[cover parentID={8D55AA29-1FEB-484f-99F7-6D287B517292}] [/cover]*/
static uint32 Smu_LockState = SMU_LOCKED;

/*Global variable to store driver status*/
/*[cover parentID={5067294E-BC26-4198-B883-73DC498420EE}] [/cover]*/
static uint32 Smu_DriverState = SMU_FAILED;
#endif

/*Global variable to store TTAS lock address for SMU driver*/
/*[cover parentID={2E4F4AFD-36D0-47ca-9184-D410327295FD}][/cover]*/
static uint32 Smu_LockAddress = 0U;

/*Global variable to store TTAS lock address for SMU command sequence*/
/*[cover parentID={712603E7-496B-432a-B8B5-C93A0F8204FD}][/cover]*/
static uint32 Smu_CmdLockAddress = 0U;

#define SMU_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Smu_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of Smu_LockAddress
 * before #include memap.h - Accepted deviation in AUTOSAR */
#include "Smu_MemMap.h"

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/* Type:SMU_CoreAlarmGroupRegMap - SMU Alarm group specific registers is listed
according to their order in hardware Memory.   */
typedef struct
{
  volatile Ifx_SMU_AGCF CfgReg[SMU_CORE_TOTAL_ALARM_CONFIG_REG];
  volatile Ifx_SMU_AGFSP FSPCfgReg[SMU_CORE_TOTAL_ALARM_GROUPS];
  volatile Ifx_SMU_AG AGStatusReg[SMU_CORE_TOTAL_ALARM_GROUPS];
  uint32 Reserved1[4];
  volatile Ifx_SMU_AD ADStatusReg[SMU_CORE_TOTAL_ALARM_GROUPS];
} SMU_CoreAlarmGroupRegMapType;

/* Mapping starting location of register set(SMU_CoreAlarmGroupRegMapType)
 * - Alarm group registers.
 */
#define SMU_CORE_ALARM_GROUP  \
((SMU_CoreAlarmGroupRegMapType *)(&SMU_AGCF0_0))

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
#if (SMU_DEV_ERROR_DETECT == STD_ON) || (SMU_SAFETY_ENABLE == STD_ON)
/* Local function - to check for init and driver state */
static Std_ReturnType Smu_lInitFailedCheck(const uint8 ServiceId);
/* Local function - to check for valid alarm group and position */
static Std_ReturnType Smu_lAlarmValidCheck(const Smu_AlarmGroupId AlarmGroup,
                                           const Smu_AlarmIdType AlarmPos,
                                           const uint8 ServiceId);
/*Local Function to report Safety Error and DET*/
static void Smu_lReportError(const uint8 ApiId,const uint8 ErrorId);
#endif

#if ((SMU_ACTIVATE_RUN_STATE_FAILURE_DEM_NOTIF == SMU_ENABLE_DEM_REPORT)||\
     (SMU_CLEAR_ALARM_STATUS_DEM_NOTIF == SMU_ENABLE_DEM_REPORT)||\
     (SMU_RELEASE_FSP_DEM_NOTIF == SMU_ENABLE_DEM_REPORT)||\
     (SMU_CORE_ALIVE_FAILURE_DEM_NOTIF == SMU_ENABLE_DEM_REPORT)||\
     (SMU_RT_STOP_FAILURE_DEM_NOTIF == SMU_ENABLE_DEM_REPORT)||\
     (SMU_ACTIVATE_PES_FAILURE_DEM_NOTIF == SMU_ENABLE_DEM_REPORT)||\
     (SMU_ACTIVATE_FSP_FAILURE_DEM_NOTIF == SMU_ENABLE_DEM_REPORT)||\
     (SMU_SET_ALARM_STATUS_DEM_NOTIF == SMU_ENABLE_DEM_REPORT)||\
     (SMU_SFF_TEST_FAILURE_DEM_NOTIF == SMU_ENABLE_DEM_REPORT))
/*Local Function to report Production Error event status*/
static void Smu_lReportDemError(const Dem_EventIdType EventId,
const Dem_EventStatusType EventStatus);
#endif

/* Local function - to clear all SMU alarms on initialization */
static void Smu_lClearAllAlarms(void);
/* Local function - to write into the SFR for clearing alarm status */
static void Smu_lClrAlarmStatus(const Smu_AlarmGroupId AlarmGroup,
                                          const Smu_AlarmIdType AlarmPos);
/* Local function - to write into the SFR for setting alarm status */
static void Smu_lSetAlarmStatus(const Smu_AlarmGroupId AlarmGroup,
                                 const Smu_AlarmIdType AlarmPos);
/* Local function - to get the alarm action */
static Std_ReturnType Smu_lSetAlmAction(const Smu_AlarmGroupId AlarmGroup,
                               const Smu_AlarmIdType AlarmPos,
                               const Smu_CoreAlarmActionType AlarmAction,
                               const Smu_FSPActionType FSPAction);
/* Local function - to get the alarm action */
static Std_ReturnType Smu_lGetAlmAction(const Smu_AlarmGroupId AlarmGroup,
                              const Smu_AlarmIdType AlarmPos,
                              Smu_CoreAlarmActionType * const IntAlarmAction,
                              Smu_FSPActionType * const FSPAction);


#define SMU_START_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Smu_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of Smu_InitStatus
 * before #include memap.h - Accepted deviation in AUTOSAR */
#include "Smu_MemMap.h"
/*******************************************************************************
**                       Private Function Definitions                         **
*******************************************************************************/

#if (SMU_DEV_ERROR_DETECT == STD_ON) || (SMU_SAFETY_ENABLE == STD_ON)

/*******************************************************************************
** Traceability     : [cover parentID={C0FF38A0-6DFF-4de3-AF10-FD846B363D58}] **
**                                                                            **
** Syntax           : static Std_ReturnType Smu_lInitFailedCheck              **
**                    (const uint8 ServiceId)                                 **
**                                                                            **
** Description      : This function checks the initialization status and      **
**                    driver state.                                           **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : ServiceId: ServiceId of the API for which check is made **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK - Operation successfully performed                 **
**                    E_NOT_OK - Operation failed                             **
*******************************************************************************/
static Std_ReturnType Smu_lInitFailedCheck(const uint8 ServiceId)
{
  /* [cover parentID={49FD4B3C-CB0A-48ab-874E-94866AA16CCF}]
  Error Detection OR Safety Checks Enabled
  [/cover] */
  Std_ReturnType RetVal = (Std_ReturnType)E_NOT_OK;

  /*Check if driver is initialized*/
  /* [cover parentID={2A8B3342-5CF4-4e37-87EC-1784E2DDBFA1}]
  Is driver  initialized?
  [/cover] */
  if(SMU_NOT_INITIALIZED == Smu_InitStatus)
  {
    /*Report error SMU_E_UNINIT*/
    /* [cover parentID={610E7593-7D93-47da-AD6A-30E745A0FC5D}]
    Report error SMU_E_UNINIT
    [/cover] */
    Smu_lReportError(ServiceId, SMU_E_UNINIT);
  }
  else
  {
    /*Check driver state is not FAILED state*/
    /* [cover parentID={DAD935D7-10B4-4a2a-B9CE-5D2FB22F3F90}]
    Is driver state FAILED?
    [/cover] */
    if(SMU_FAILED == Smu_DriverState)
    {
      /*Report error SMU_E_INVALID_DRIVER_STATE*/
      /* [cover parentID={D144A63C-4304-4c04-A0E8-FC5DA0687FD1}]
      Report error SMU_E_INVALID_DRIVER_STATE
      [/cover] */
      Smu_lReportError(ServiceId, SMU_E_INVALID_DRIVER_STATE);
    }
    else
    {
      /* [cover parentID={44F789B1-94E1-49c7-80CC-82346C7D65FF}]
      Result set as E_OK
      [/cover] */
      RetVal = (Std_ReturnType)E_OK;
    }
  }
  /* [cover parentID={5D8D9D56-D6FF-4c9e-8558-97E08DD2BA9D}]
  Return Result
  [/cover] */
  return RetVal;
}

/*******************************************************************************
** Traceability     : [cover parentID={853755DD-5F97-442b-ADF9-96B7B4FB7EB0}] **
**                                                                            **
** Syntax           : static Std_ReturnType Smu_lAlarmValidCheck              **
**                    (const Smu_AlarmGroupId AlarmGroup,                     **
**                     const Smu_AlarmIdType  AlarmPos,                       **
**                     const uint8 ServiceId)                                 **
**                                                                            **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** [/cover]                                                                   **
** Parameters(in)   : AlarmGroup:Alarm group to clear the status              **
**                    AlarmPos:Alarm position to clear the status             **
**                    ServiceId: Service id of the API for which check is made**
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK - Operation successfully performed                 **
**                    E_NOT_OK - Operation failed                             **
**                                                                            **
** Description      : The purpose of the function is to check for the         **
**                    validity of the Smu_core and Smu_stdby alarm group      **
**                    and positions. In case the group requested is in        **
**                    Smu_stdby, it checks whether Smu_stdby is enabled or    **
**                    disabled.                                               **
*******************************************************************************/
static Std_ReturnType Smu_lAlarmValidCheck(const Smu_AlarmGroupId AlarmGroup,
                                             const Smu_AlarmIdType AlarmPos,
                                             const uint8 ServiceId)
{
  /* [cover parentID={D648A504-FB7D-4dc0-A2FA-2B4D6E2863F4}]
  Error Detection OR Safety Checks Enabled
  [/cover] */
  Std_ReturnType RetVal = (Std_ReturnType)E_NOT_OK;
  uint32 AlarmRes;

  /*Array to check the alarm position validity for Smu_core*/
  uint32 CoreAlarmIdReservedType[SMU_CORE_TOTAL_ALARM_GROUPS] =
  {
    SMU_GROUP0_POS,
    SMU_GROUP1_POS,
    SMU_GROUP2_POS,
    SMU_GROUP3_POS,
    SMU_GROUP4_POS,
    SMU_GROUP5_POS,
    SMU_GROUP6_POS,
    SMU_GROUP7_POS,
    SMU_GROUP8_POS,
    SMU_GROUP9_POS,
    SMU_GROUP10_POS,
    SMU_GROUP11_POS,
  };

  /*Check if the alarm position is within range*/
  /* [cover parentID={5EF2D2F9-C286-4338-B96E-DA482D80C1AD}]
  Is the alarm position in valid range?
  [/cover] */
  if((uint32)AlarmPos <= SMU_MAX_ALARM_POS)
  {
    /*Check if the group is valid in core/stdby*/
    /* [cover parentID={2F315458-8DBA-45e9-A6C3-E8DE9201D71A}]
    Is the alarm group in core domain?
    [/cover] */
    if((uint32)AlarmGroup < SMU_CORE_TOTAL_ALARM_GROUPS)
    {
      /*Check for validity of alarm position*/
      /* [cover parentID={F21C9CCC-D2C2-41df-966A-828077A9C20E}]
      Check for validity of alarm position for the specified alarm group
      [/cover] */
      AlarmRes = (uint32)CoreAlarmIdReservedType[AlarmGroup] &
                 ((uint32)SMU_ALARM_VALID << (uint32)AlarmPos);

      AlarmRes = AlarmRes >> (uint32)AlarmPos;

      /*Check if alarm position is valid*/
      /* [cover parentID={113C32E0-2589-4eda-835F-91542B8C2E32}]
      Is the alarm position invalid?
      [/cover] */
      if(AlarmRes == SMU_ALARM_INVALID)
      {
        /* [cover parentID={2D68C2E7-ADAB-474e-9748-81B7E69888D7}]
        Report error SMU_E_PARAM_GROUP
        [/cover] */
        Smu_lReportError(ServiceId, SMU_E_PARAM_GROUP);
      }
      else
      {
        /* [cover parentID={7529AC86-C419-477e-8103-5EDB2FB90E0E}]
        Set the result as E_OK
        [/cover] */
        RetVal = E_OK;
      }
    }
    /* [cover parentID={618B9F0C-38E9-402f-A460-345E23573499}]
    Is the alarm group in standby domain?
    [/cover] */
    else if(((uint32)AlarmGroup <= SMU_STDBY_END_ALARM_GROUP) &&
            ((uint32)AlarmGroup >= SMU_STDBY_START_ALARM_GROUP))
    {
      /*Check if Smu_stdby is OFF*/
      /* [cover parentID={79D139E0-6860-4ed6-B20E-01BCB5E3085F}]
      Is Standby mode OFF?
      [/cover] */
      /* [cover parentID={3D262481-9F08-4b88-B7F2-90C28397B31D}]
      Standby Mode OFF
      [/cover] */
      #if(SMU_STANDBY_SWITCH == STD_OFF)
      /*Report error SMU_E_STDBY_DISABLED*/
      /* [cover parentID={21F14CFD-B086-41e0-B9EE-2753F40F7FAE}]
      Report error SMU_E_STDBY_DISABLED
      [/cover] */
      Smu_lReportError(ServiceId, SMU_E_STDBY_DISABLED);
      /* [cover parentID={0F1DDC1F-D613-4c7d-9DC9-F2E46CC50E0F}]
      Standby Mode ON
      [/cover] */
      #else
      /*Array to check the alarm position validity for Smu_core*/
      uint32 StdbyAlarmIdReservedType[SMU_STDBY_TOTAL_ALARM_GROUPS] =
      {
        SMU_GROUP20_POS,
        SMU_GROUP21_POS
      };

      /* [cover parentID={6EB4B5BB-5DC8-4b12-A8A9-C3F0F6E564FB}]
      Is the alarm group Alarm group 20?
      [/cover] */
      if(AlarmGroup == SMU_ALARM_GROUP20)
      {
        /* [cover parentID={03924AAD-19EF-4b9c-AA7A-12EFCE94FED2}]
        Check for validity of alarm position for alarm group 20
        [/cover] */
        AlarmRes = (uint32)StdbyAlarmIdReservedType[0] & \
                   ((uint32)SMU_ALARM_VALID << (uint32)AlarmPos);
      }
      else
      {
        /* [cover parentID={2FE40D31-108C-4c1f-98E6-CEA791E8255F}]
        Check for validity of alarm position for alarm group 21
        [/cover] */
        AlarmRes = (uint32)StdbyAlarmIdReservedType[1] & \
                   ((uint32)SMU_ALARM_VALID << (uint32)AlarmPos);

      }
      AlarmRes = AlarmRes >> (uint32)AlarmPos;
      /*Check if alarm position is valid*/
      /* [cover parentID={6A0D061E-9186-4834-A03C-D41177B54D45}]
      Is the alarm position valid?
      [/cover] */
      if(AlarmRes == SMU_ALARM_INVALID)
      {
        /*Report error SMU_E_PARAM_GROUP*/
        /* [cover parentID={3D5355A2-FC91-43d2-82F0-6CCB0C3D88A8}]
        Report error SMU_E_PARAM_GROUP
        [/cover] */
        Smu_lReportError(ServiceId, SMU_E_PARAM_GROUP);

      }
      else
      {
        /* [cover parentID={9020A3E9-D672-4865-889D-90E247C7C66C}]
        Set the result as E_OK
        [/cover] */
        RetVal = E_OK;
      }
      #endif
    }
    else
    {
      /*Report error SMU_E_PARAM_GROUP*/
      /* [cover parentID={0321E4AC-4B15-4a49-A767-BB10F5544EAE}]
      Report error SMU_E_PARAM_GROUP
      [/cover] */
      Smu_lReportError(ServiceId, SMU_E_PARAM_GROUP);
    }
  }
  else
  {
    /*Report error SMU_E_PARAM_GROUP*/
    /* [cover parentID={30479E7B-FC5A-41fb-B867-993AA96FF4BE}]
    Report error SMU_E_PARAM_GROUP
    [/cover] */
    Smu_lReportError(ServiceId, SMU_E_PARAM_GROUP);
  }
  /* [cover parentID={586D54F1-81D8-4b4a-BF25-958884DCEA77}]
  Return the result
  [/cover] */
  return RetVal;
}

/*******************************************************************************
** Traceability     :[cover parentID={12ACA780-4EA8-48fc-B8BE-51498C0ECD2A}]  **
**                                                                            **
** Syntax           : LOCAL_INLINE void Smu_lReportError                      **
**                    ( const uint8 ApiId,const uint8 ErrorId)                **
**                                                                            **
** Description      : Function to report Safety Error and DET                 **
** [/cover]                                                                   **
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
*******************************************************************************/
static void Smu_lReportError(const uint8 ApiId,
                             const uint8 ErrorId)
{
  /* [cover parentID={DD7B24BD-EF10-4abf-A6E0-30C8D435839F}]
  DET is ON or safety is enabled
  [/cover] */
  /* [cover parentID={9BF22F7C-856A-4d43-9B7B-B425A8C1C197}]
  DET Checks ON
  [/cover] */
  #if (SMU_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={AB39144C-28F2-4113-B2DE-E5E1703ECC4D}]
  Report DET as per the ID specified by input parameter
  [/cover] */
  (void)Det_ReportError(SMU_MODULE_ID, SMU_MODULE_INSTANCE, \
                  ApiId, ErrorId); /* End of report to DET */
  #endif

  /* [cover parentID={44A663A1-D99C-4ef7-A532-826DC6EB2A17}]
  Is Safety Check enabled?
  [/cover] */
  #if (SMU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={ACA4ABEB-7783-4e65-B510-90C674F03739}]
  Report safety error as per the ID specified by input parameter
  [/cover] */
  Mcal_ReportSafetyError(SMU_MODULE_ID, SMU_MODULE_INSTANCE, \
                         ApiId, ErrorId); /* End of report to Safety */
  #endif
}

#endif/*End of DET specific functions*/

#if ((SMU_ACTIVATE_RUN_STATE_FAILURE_DEM_NOTIF == SMU_ENABLE_DEM_REPORT)||\
     (SMU_CLEAR_ALARM_STATUS_DEM_NOTIF == SMU_ENABLE_DEM_REPORT)||\
     (SMU_RELEASE_FSP_DEM_NOTIF == SMU_ENABLE_DEM_REPORT)||\
     (SMU_CORE_ALIVE_FAILURE_DEM_NOTIF == SMU_ENABLE_DEM_REPORT)||\
     (SMU_RT_STOP_FAILURE_DEM_NOTIF == SMU_ENABLE_DEM_REPORT)||\
     (SMU_ACTIVATE_PES_FAILURE_DEM_NOTIF == SMU_ENABLE_DEM_REPORT)||\
     (SMU_ACTIVATE_FSP_FAILURE_DEM_NOTIF == SMU_ENABLE_DEM_REPORT)||\
     (SMU_SET_ALARM_STATUS_DEM_NOTIF == SMU_ENABLE_DEM_REPORT)||\
     (SMU_SFF_TEST_FAILURE_DEM_NOTIF == SMU_ENABLE_DEM_REPORT))
/*******************************************************************************
** Traceability     : [cover parentID={25A6FC10-B10D-44e0-B5E5-8A02230BF657}] **
**                                                                            **
** Syntax           : static void Smu_lReportDemError                         **
**                    (                                                       **
**                       const Dem_EventIdType EventId,                       **
**                       const Dem_EventStatusType EventStatus                **
**                    )                                                       **
**                                                                            **
** Description      : Function to report the production error status           **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant for different Event IDs                       **
**                                                                            **
** Parameters (in)  : EventId - ID of the event reported                      **
**                    EventStatus - Status of the event reported              **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*                                                                             **
*******************************************************************************/
static void Smu_lReportDemError(const Dem_EventIdType EventId,
const Dem_EventStatusType EventStatus)
{
  /* [cover parentID={B3C232D7-6277-464f-86FB-3275E5860F71}]
  Autosar version is AR422 [/cover] */
  #if (MCAL_AR_VERSION == MCAL_AR_422)
  /* [cover parentID={FF8F9E12-8F45-434c-B70E-D4D7C7F97332}]
  Report the Production Error status [/cover] */
  Mcal_Wrapper_Dem_ReportErrorStatus(EventId, EventStatus);

  /* [cover parentID={58143BBD-FE93-495a-84EE-6F6B75820F99}]
  Autosar version is AR440 [/cover] */
  #else
  /* [cover parentID={D70BD90A-7A10-4312-9703-A6B4EE709A97}]
  Report the Production Error status [/cover] */
  (void)Mcal_Wrapper_Dem_SetEventStatus(EventId, EventStatus);

  #endif
}
#endif/*End of Production Error specific function*/

/*******************************************************************************
** Traceability     : [cover parentID={78878FBF-B398-4bfe-AE2E-0B20ACD97895}] **
**                                                                            **
** Syntax           : static void Smu_lClearAllAlarms(void)                   **
**                                                                            **
** Description      : The purpose of the function is to clear all the         **
**                    SMU Alarms                                              **
** [/cover]                                                                   **
** Service ID       : none                                                    **
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
static void Smu_lClearAllAlarms(void)
{
  uint8 AlarmGroupIndex;

  /*For Smu_core, clear the alarm status for all alarm groups*/
  AlarmGroupIndex = (uint8)SMU_ALARM_GROUP0;
  /* [cover parentID={BA442D50-E0FB-461c-A98F-0BBF0E00A636}]
  Write clear alarm status in the alarm configuration registers
  [/cover] */
  do
  {
    /* Write SMU_ASCE(0) in CMD register of Smu_core */
    /* [cover parentID={2F57FEED-BF74-4448-A234-0C5FC4EF6861}]
    Enable Alarm Status Clear by writing to Command register
    [/cover] */
    SMU_SFR_INIT_DEINIT_WRITE32(&SMU_CMD.U, (uint32)SMU_ASCE_COMMAND);

    /* Write clear alarm status in all the alarm configuration registers
    for Smu_core*/

    /* [cover parentID={A7443B2C-F20A-42c8-B2CF-EADFF615CD59}]
    Clear the alarm status for all alarm groups for Smu_core
    [/cover] */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between
    pointers of different object types due to SFR access. */
    SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG( \
        &SMU_CORE_ALARM_GROUP->AGStatusReg[AlarmGroupIndex], \
        (uint32)SMU_AG_SET_ALL);
    AlarmGroupIndex++;

  }
  /* [cover parentID={EBA0E8F9-F685-4560-8874-6D97E0B20C66}]
  Loop till last Alarm Group in SMU Core
  [/cover] */
  while(AlarmGroupIndex < SMU_CORE_TOTAL_ALARM_GROUPS);

  /*If Smu_stdby is enabled*/
  /* [cover parentID={0DD8A08E-D3BD-4e1e-9A0A-891ED84C3BA2}]
  Is SMU Standby Mode enabled ?
  [/cover] */
  #if(SMU_STANDBY_SWITCH == STD_ON)
  /* [cover parentID={E850ABCE-70C3-4aef-A291-5EE122BF9A84}]
  Enable the command to clear the alarm status for group 20
  [/cover] */
  SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&MODULE_PMS.CMD_STDBY, \
      (SMU_STDBY_BIT_PROT | SMU_STDBY_ASCE_COMMAND | PMS_CMD_STDBY.U));

  /* [cover parentID={AC40131F-89D5-407f-8BB7-268FEA05FACC}]
  Clear the alarm status for alarm group 20
  [/cover] */
  SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&MODULE_PMS.AG_STDBY0, \
      (uint32)SMU_AG_SET_ALL);

  /* [cover parentID={3DE26362-26E5-4688-9642-AB08ABBD8014}]
  Enable the command to clear alarm status for group 21
  [/cover] */
  SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&MODULE_PMS.CMD_STDBY, \
      (SMU_STDBY_BIT_PROT | SMU_STDBY_ASCE_COMMAND | PMS_CMD_STDBY.U));

  /* [cover parentID={8F4D7B8D-A242-4166-9FAD-72E2ED633575}]
  Clear the alarm status for alarm group 21
  [/cover] */
  SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG(&MODULE_PMS.AG_STDBY1, \
      (uint32)SMU_AG_SET_ALL);
  #endif

}

/*******************************************************************************
** Traceability     :[cover parentID={1E6E002B-FE95-4798-B0F3-B597C29CE5EC}]  **
**                                                                            **
** Syntax           : static Std_ReturnType Smu_lClrAlarmStatus(              **
**                      const Smu_AlarmGroupId AlarmGroup,                    **
**                      const Smu_AlarmIdType  AlarmPos)                      **
**                                                                            **
** Description      : This function clears the alarm status of the alarm group**
**                    and position requested.                                 **
** [/cover]                                                                   **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : AlarmGroup:Alarm group to clear the status              **
**                    AlarmPos:Alarm position to clear the status             **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK - Operation successfully performed                 **
**                    E_NOT_OK - Operation failed                             **
*******************************************************************************/
static void Smu_lClrAlarmStatus(const Smu_AlarmGroupId AlarmGroup,
                                const Smu_AlarmIdType AlarmPos)
{
  /*If alarm group lies in Smu_core*/
  /* [cover parentID={BAAB0956-DAC6-4600-B05D-69CA33A1FAC0}]
  Is the requested alarm  group in Core Domain?
  [/cover] */
  if((uint8)AlarmGroup < SMU_CORE_TOTAL_ALARM_GROUPS)
  {
    /* Write the command to clear alarm status in  CMD register */
    /* [cover parentID={64C79D3C-5C0C-440e-AF61-3DEA665D1A23}]
    Clear alarm status by writing to  Command register
    [/cover] */
    SMU_SFR_RUNTIME_WRITE32(&SMU_CMD.U, (uint32)SMU_ASCE_COMMAND );
    /* [cover parentID={650CBF32-FC30-439d-9548-EBE11B07B2E4}]
    Clear the alarm configuration register for the requested alarm group
    and position.
    [/cover] */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between
    pointers of different object types due to SFR access. */
    SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG( \
        &SMU_CORE_ALARM_GROUP->AGStatusReg[AlarmGroup], \
        (uint32)((uint32)SMU_ALARM_POS1 << AlarmPos));
  }

  /* [cover parentID={43057EC8-85E3-4489-8FD1-586527A8BCF1}]
  Is Smu_stdby enabled?
  [/cover] */
  #if(SMU_STANDBY_SWITCH == STD_ON)
  /*If the requested group is group 20*/
  /* [cover parentID={CF30CD2A-BDCD-49a5-AED1-B49D0AC8F04D}]
  Is the requested alarm  group is Alarm group 20?
  [/cover] */
  else if((uint8)AlarmGroup == (uint8)SMU_ALARM_GROUP20)
  {
    /*Enable alarm status clear for Smu_stdby*/
    /* [cover parentID={2C74811C-A09F-4daa-9944-99B450A1835E}]
    Enable alarm status clear for SMU standby mode
    [/cover] */
    SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG(&MODULE_PMS.CMD_STDBY, \
        (SMU_STDBY_BIT_PROT | SMU_STDBY_ASCE_COMMAND | PMS_CMD_STDBY.U));
    /* [cover parentID={E9783993-B319-444f-99BE-F8682A0C7849}]
    Clear the alarm configuration register for the requested alarm group
    20 position.
    [/cover] */
    /*Write Config key to configure the SMU registers. */
    SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG( \
        &MODULE_PMS.AG_STDBY0, (uint32)((uint32)SMU_ALARM_POS1 << AlarmPos));
  }
  /*If the requested group is group 21*/
  else
  {
    /* [cover parentID={A21DBEB9-7E2C-4111-9433-8FF217D2BF36}]
    Is DET and Safety disabled?
    [/cover] */
    #if (SMU_DEV_ERROR_DETECT == STD_OFF) && \
    (SMU_SAFETY_ENABLE == STD_OFF)
    /* [cover parentID={485F7D54-D0D9-41bb-BF5A-7C7E1D2B2A68}]
    Is the requested alarm  group is Alarm group 21?
    [/cover] */
    if((uint8)AlarmGroup == (uint8)SMU_ALARM_GROUP21)
    #endif
    {
      /*Enable alarm status clear for Smu_stdby*/
      /* [cover parentID={F02B96C1-F463-4c61-B913-A6BC44FBDE37}]
      Enable alarm status clear for SMU standby mode
      [/cover] */
      SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG(&MODULE_PMS.CMD_STDBY, \
          (SMU_STDBY_BIT_PROT | SMU_STDBY_ASCE_COMMAND | PMS_CMD_STDBY.U));
      /* [cover parentID={A3C19486-954B-447d-9434-A5D3B324E223}]
      Clear the alarm configuration register for the requested alarm
      group 21 position.
      [/cover] */
      SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG( \
          &MODULE_PMS.AG_STDBY1, (uint32)((uint32)SMU_ALARM_POS1 << AlarmPos));
    }
  }
  #endif
}

/*******************************************************************************
** Traceability     :[cover parentID={1E29E5BF-A25E-4ea4-AF0E-74A79844AA92}]  **
**                                                                            **
** Syntax           : static Std_ReturnType Smu_lSetAlarmStatus(              **
**                      const Smu_AlarmGroupId AlarmGroup,                    **
**                      const Smu_AlarmIdType  AlarmPos)                      **
**                                                                            **
** Description      : The purpose of the function is to set the status of     **
**                    requested alarm group and position.                     **
** [/cover]                                                                   **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : AlarmGroup:Alarm group to clear the status              **
**                    AlarmPos:Alarm position to clear the status             **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK - Operation successfully performed                 **
**                    E_NOT_OK - Operation failed                             **
*******************************************************************************/
static void Smu_lSetAlarmStatus(const Smu_AlarmGroupId AlarmGroup,
                                const Smu_AlarmIdType AlarmPos)
{
  Smu_CoreStateType SmuState;
  /* Read the SMU state from module DBG register */
  /* [cover parentID={C1F92F60-2A93-46d3-BFF4-CB12D2E5C2DA}]
  Read the SMU state from module DBG register
  [/cover] */
  SmuState = (uint8)(SMU_DBG.B.SSM);
  /* SMU is in START state */
  /* [cover parentID={A9F458AD-5786-4e50-B01E-6B1085CACBA4}]
  Is SMU in START state ?
  [/cover] */
  if(SMU_START_STATE == SmuState)
  {
    /* All SMU Groups are allowed to set alarm status */
    /* [cover parentID={DEF71E0A-5250-40e9-8A25-8EF3676FD79D}]
    Set alarm status
    [/cover] */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between
    pointers of different object types due to SFR access. */
    SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG((uint32*)  \
        &SMU_CORE_ALARM_GROUP->AGStatusReg[AlarmGroup], \
        ((uint32)SMU_ALARM_POS1 << AlarmPos));
  }
  /* Alarm is in RUN state or FAULT state */
  /* [cover parentID={FE8126A1-A1DE-480a-B089-ED0F2D509F5E}]
  Is Alarm in either RUN state or FAULT state ?
  [/cover] */
  else if ((SMU_RUN_STATE == SmuState) || (SMU_FAULT_STATE == SmuState))
  {
    /*Only SMU SW alarm group can chenge status in this state.*/
    /*Check if the requested group is SW alarm group.*/
    /* [cover parentID={4AC51A1A-E163-47a2-810E-854959950439}]
    Is the requested group SW alarm group ?
    [/cover] */
    if((uint8)AlarmGroup == SMU_SW_ALARM_GROUP)
    {
      /*Write SMU_Alarm command to trigger SW based alarm*/
      /* [cover parentID={8AC727F8-D116-44c7-AD9E-B8FE33FB2DC4}]
      Write SMU_Alarm command to trigger SW based alarm
      [/cover] */
      SMU_SFR_RUNTIME_WRITE32(&SMU_CMD.U, ((uint32)SMU_ALARM_COMMAND \
                             | ((uint32)AlarmPos << SMU_CMD_ARG_BIT_POS)));
    }
  }
  else
  {
    /*Invalid state*/
  }
}

/*******************************************************************************
** Traceability     :[cover parentID={0918C35B-BE7C-4fbf-A5CB-21803F1417F5}]  **
**                                                                            **
** Syntax           : static Std_ReturnType Smu_lSetAlmAction(                **
**                      const Smu_AlarmGroupId AlarmGroup,                    **
**                      const Smu_AlarmIdType  AlarmPos,                      **
**                      const Smu_CoreAlarmActionType AlarmAction,            **
**                      const Smu_FSPActionType FSPAction)                    **
**                                                                            **
** Description      : The purpose of the function is to set the desired alarm **
**                    action.                                                 **
** [/cover]                                                                   **
** Service ID       : none                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : AlarmGroup:Alarm group to clear the status              **
**                    AlarmPos:Alarm position to clear the status             **
**                    AlarmAction:Internal alarm action to be configured      **
**                    FSPAction:FSP alarm action to be configured             **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK - Operation successfully performed                 **
**                    E_NOT_OK - Operation failed                             **
*******************************************************************************/
static Std_ReturnType Smu_lSetAlmAction(const Smu_AlarmGroupId AlarmGroup,
                               const Smu_AlarmIdType AlarmPos,
                               const Smu_CoreAlarmActionType AlarmAction,
                               const Smu_FSPActionType FSPAction)
{
  uint8 AlarmGroupCFIndex;
  uint32 AlarmGroupCF2;
  uint32 AlarmGroupCF1;
  uint32 AlarmGroupCF0;
  uint32 AlarmGroupCFMask;
  Std_ReturnType RetVal = E_NOT_OK;

  /* Get the Register set index */
  AlarmGroupCFIndex = (uint8)((uint8)AlarmGroup * SMU_ALMACTION_MSK);

  /* Get the mask for configuration registers to set the perticular bits*/
  AlarmGroupCFMask = ~((uint32)SMU_ALARM_VALID << AlarmPos);

  /* [cover parentID={0D20AD6F-7260-4c0d-90C9-531A056367E4}][/cover] */
  /* [cover parentID={5F697F7E-0A4B-411b-9ADB-B60CA7D7C01C}]
  Enter critical section
  [/cover] */
  SchM_Enter_Smu_DriverAccess();
  /*Acquire spinlock*/
  /* [cover parentID={6471CFAE-4C46-4291-9E14-30DB3B098643}]
  Acquire spinlock
  [/cover] */
  Mcal_GetSpinlock(&Smu_LockAddress, SMU_SPINLOCK_TIMEOUT);

  /* [cover parentID={C9EFB3CD-B2F4-4301-986D-F3F5FD7F54F9}]
  Is the alarm group in SMU core ?
  [/cover] */
  if((uint8)AlarmGroup < SMU_CORE_TOTAL_ALARM_GROUPS)
  {
    /* Extract Alarm configuration for 3 CFG registers from
    input parameter*/
    /* [cover parentID={B6576F5B-2DB9-4a3c-958F-4631A45B0F52}]
    Extract Configuration Group 0 as per mask from input parameter
    for specified alarm group
    [/cover] */
    AlarmGroupCF0 = (uint32)(((uint32)AlarmAction & \
                    (uint32)SMU_ALMGRP_CFG0_MASK)<< (uint32)AlarmPos);
    /*Extract Configuration Group 1 as per mask from input parameter
    for specified alarm group*/
    AlarmGroupCF1 = (uint32)((uint32)(((uint32)AlarmAction & \
                    (uint32)SMU_ALMGRP_CFG1_MASK) >> (uint32)SMU_ALARM_POS1) \
                    << (uint32)AlarmPos);
    /*Extract Configuration Group 2 as per mask from input parameter
    for specified alarm group*/
    AlarmGroupCF2 = (uint32)((uint32)(((uint32)AlarmAction & \
                    (uint32)SMU_ALMGRP_CFG2_MASK) >> (uint32)SMU_ALARM_POS2) \
                    << (uint32)AlarmPos);

    /*Write Config key to configure the SMU registers. */
    /* [cover parentID={DB839A87-32AD-44f8-82A7-56B042B0D57D}]
    Write Config key to Unlock the SMU  configuration registers
    [/cover] */
    SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG(&MODULE_SMU.KEYS, \
        (uint32)SMU_CFG_KEY_UNLOCK);

    /* [cover parentID={DACC9979-02B5-4e00-8348-956B477DA98A}]
    Write Alarm configuration into SMU alarm CF0 registers
    [/cover] */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between
    pointers of different object types due to SFR access. */
    SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG( \
        &SMU_CORE_ALARM_GROUP->CfgReg[AlarmGroupCFIndex].U, \
        (((SMU_CORE_ALARM_GROUP->CfgReg[AlarmGroupCFIndex].U)& \
          (uint32)AlarmGroupCFMask) | (uint32)AlarmGroupCF0));

    /* [cover parentID={93351F5F-1B48-4492-AE4D-BF346674720A}]
    Write Alarm configuration into SMU alarm CF1 registers
    [/cover] */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between
    pointers of different object types due to SFR access. */
    SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG( \
        &SMU_CORE_ALARM_GROUP->CfgReg \
        [(AlarmGroupCFIndex + SMU_ALARM_POS1)].U, \
        (((SMU_CORE_ALARM_GROUP->CfgReg \
           [(AlarmGroupCFIndex + SMU_ALARM_POS1)].U)& \
          (uint32)AlarmGroupCFMask) | (uint32)AlarmGroupCF1) );

    /* [cover parentID={DE391D65-8AE5-4892-8551-ED9A511DF301}]
    Write Alarm configuration into SMU alarm CF2 registers
    [/cover] */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between
    pointers of different object types due to SFR access. */
    SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG( \
        &SMU_CORE_ALARM_GROUP->CfgReg \
        [(AlarmGroupCFIndex + SMU_ALARM_POS2)].U, \
        (((SMU_CORE_ALARM_GROUP->CfgReg \
           [(AlarmGroupCFIndex + SMU_ALARM_POS2)].U) & \
          (uint32)AlarmGroupCFMask) | (uint32)AlarmGroupCF2 ) );

    /* [cover parentID={7E6B847B-5530-4a57-ADC9-EF5ECDE5B0D3}]
    Write FSP action into FSP configuration register
    [/cover] */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between
    pointers of different object types due to SFR access. */
    SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG( \
        &SMU_CORE_ALARM_GROUP->FSPCfgReg[AlarmGroup].U, \
        (((SMU_CORE_ALARM_GROUP->FSPCfgReg[AlarmGroup].U)& \
          (uint32)AlarmGroupCFMask) | (FSPAction << AlarmPos)));

    /* After configuration set temporary lock of SMU configuration*/
    /* [cover parentID={9B04BE01-CFC4-4ba0-8A29-D287AFEA97E4}]
    Set temporary lock of SMU configuration
    [/cover] */
    SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG(&MODULE_SMU.KEYS, \
        (uint32)SMU_CFG_KEY_TEMPLOCK);

    RetVal = E_OK;
  }
  /* [cover parentID={F539D404-CF9A-411e-993A-C7936815F3E5}]
  Is Smu_stdby enabled?
  [/cover] */
  #if(SMU_STANDBY_SWITCH == STD_ON)
  /* [cover parentID={5633929C-DDBE-430c-B4ED-2BD7F4E660F6}]
  Is the alarm group Alarm group 20 ?
  [/cover] */
  else if(AlarmGroup == SMU_ALARM_GROUP20)
  {
    /*Configure the FSP configuration registers for Smu_stdby
      group 20*/
    /* [cover parentID={81153733-B64A-4865-BDA5-AB4907B228D8}]
    Write FSP action into FSP configuration registers for Smu_stdby group 20
    [/cover] */
    SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG( \
      &MODULE_PMS.AGFSP_STDBY0, \
      ((PMS_AGFSP_STDBY0.U & (uint32)AlarmGroupCFMask) | \
      SMU_STDBY_BIT_PROT | (FSPAction << AlarmPos)));

    RetVal = E_OK;
  }
  else
  {
    /* [cover parentID={AEE38933-84C6-46e9-B809-D879A2C54F9E}]
    Is DET and Safety disabled?
    [/cover] */
    #if (SMU_DEV_ERROR_DETECT == STD_OFF) && \
    (SMU_SAFETY_ENABLE == STD_OFF)
    /* [cover parentID={A7E56CC4-C987-479a-A2E7-58719704708F}]
    Is the alarm group Alarm group 21 ?
    [/cover] */
    if(AlarmGroup == SMU_ALARM_GROUP21)
    #endif
    {
      /*Configure the FSP configuration registers for Smu_stdby
      group 21*/
      /* [cover parentID={85757A0E-878D-4ffc-8CCE-C256AB4AA1B3}]
      Write FSP action into FSP configuration registers for
      Smu_stdby group 21
      [/cover] */
      SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG( \
        &MODULE_PMS.AGFSP_STDBY1, \
        ((PMS_AGFSP_STDBY1.U & (uint32)AlarmGroupCFMask) | \
        SMU_STDBY_BIT_PROT | (FSPAction << AlarmPos)));

      RetVal = E_OK;
    }
  }
  #endif
  /*Release the spinlock*/
  /* [cover parentID={59D8ACF6-2DC8-4cea-8A20-3DC26C486E3B}]
  Release the spinlock
  [/cover] */
  Mcal_ReleaseSpinlock(&Smu_LockAddress);
  /* [cover parentID={93C3EE94-390A-464f-914A-6659FA643752}]
  Exit critical section
  [/cover] */
  SchM_Exit_Smu_DriverAccess();
  /* [cover parentID={7989ED14-0EE8-4cff-9E6A-30BE2EAD3997}]
  Return the result of return value
  [/cover] */
  return RetVal;
}

/*******************************************************************************
** Traceability     : [cover parentID={F49F8CE5-965F-4fce-9D0E-0B00189837C1}] **
**                                                                            **
** Syntax           : static Std_ReturnType Smu_lGetAlmAction(                **
**                      const Smu_AlarmGroupId AlarmGroup,                    **
**                      const Smu_AlarmIdType  AlarmPos)                      **
**                      Smu_CoreAlarmActionType * const AlarmGroup,           **
**                      Smu_FSPActionType * const FSPAction)                  **
**                                                                            **
** Description      : The purpose of the function is to get the desired alarm **
**                    action.                                                 **
** [/cover]                                                                   **
** Service ID       : none                                                    **
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
**                    E_NOT_OK - Operation failed                             **
*******************************************************************************/
static Std_ReturnType Smu_lGetAlmAction(const Smu_AlarmGroupId AlarmGroup,
                              const Smu_AlarmIdType AlarmPos,
                              Smu_CoreAlarmActionType * const IntAlarmAction,
                              Smu_FSPActionType * const FSPAction)
{
  Std_ReturnType RetVal = (Std_ReturnType)E_NOT_OK;
  uint32  AlarmGroupCF2;
  uint32  AlarmGroupCF1;
  uint32  AlarmGroupCF0;
  uint32 AlarmGroupCFIndex;
  Smu_CoreAlarmActionType  IntActionRes;
  Smu_FSPActionType FSPActionRes;

  /* [cover parentID={57F99E91-8AA6-4108-88A6-F6CD8A1B3B0B}]
  Is the required Alarm Group in SMU Core ?
  [/cover] */
  if((uint8)AlarmGroup < SMU_CORE_TOTAL_ALARM_GROUPS)
  {
    /* Get the Register set index */
    /* [cover parentID={F02B98BC-8A82-4b99-A0B3-4138B77BA86B}]
    Get the Register set index
    [/cover] */
    AlarmGroupCFIndex = (uint32)((uint32)AlarmGroup * SMU_ALMACTION_MSK);

    /* Read Alarm configuration from SMU alarm CFx (x=0-2) registers
    and align them to combine to get 3 bit value*/

    /* [cover parentID={0F3EBF11-7258-4448-A572-A035EA943164}]
    Read  as per mask from configuration group 0 for specified alarm position
    [/cover] */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between
    pointers of different object types due to SFR access. */
    AlarmGroupCF0 = (uint32)(((uint32) \
                    (SMU_CORE_ALARM_GROUP->CfgReg[AlarmGroupCFIndex].U)>> \
                    (uint32)AlarmPos) & (uint32)SMU_ALMGRP_CFG0_MASK);

    /* [cover parentID={CB032CB6-A1D5-4581-9B64-F927A4463E6C}]
    Read  as per mask from configuration group 1 for specified alarm position
    [/cover] */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between
    pointers of different object types due to SFR access. */
    AlarmGroupCF1 = ((uint32)((uint32)((uint32)(SMU_CORE_ALARM_GROUP->CfgReg
                    [(AlarmGroupCFIndex + (uint32)SMU_ALARM_POS1)].U) >> \
                    (uint32)AlarmPos) << (uint32)SMU_ALARM_POS1) & \
                    (uint32)SMU_ALMGRP_CFG1_MASK);

    /* [cover parentID={254C5CA1-5CDD-4866-8041-77A1866948BD}]
    Read  as per mask from configuration group 2 for specified alarm position
    [/cover] */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between
    pointers of different object types due to SFR access. */
    AlarmGroupCF2 = ((uint32)((uint32)((uint32)(SMU_CORE_ALARM_GROUP->CfgReg \
                    [(AlarmGroupCFIndex + (uint32)SMU_ALARM_POS2)].U) >> \
                    (uint32)AlarmPos) << (uint32)SMU_ALARM_POS2) & \
                    (uint32)SMU_ALMGRP_CFG2_MASK);

    /* [cover parentID={81D53095-EA8F-46fd-993D-8138631AC1E4}]
    Combine the alarm actions configured into 3 bit value and assign
    to out parameter
    [/cover] */
    *IntAlarmAction = (Smu_CoreAlarmActionType)(AlarmGroupCF0 |
                      AlarmGroupCF1 | AlarmGroupCF2);

    /* [cover parentID={306ACA73-D7A6-4da9-87B4-9D5DE5430A96}]
    Assign the FSP action configured to out parameter
    [/cover] */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between pointers of
        different object types due to SFR access. */
    *FSPAction = (Smu_FSPActionType) \
                 (((SMU_CORE_ALARM_GROUP->FSPCfgReg[(uint32)AlarmGroup].U) \
                   >> (uint32)AlarmPos)& SMU_ALARM_FSP_MASK);

  }
  /* [cover parentID={16B82FB9-FF42-4cbf-A599-7E4A35C0B2C6}]
  Is Smu_stdby enabled?
  [/cover] */
  #if(SMU_STANDBY_SWITCH == STD_ON)
  /* [cover parentID={3E7CB496-47E9-41f9-B61A-1407060EB635}]
  Is required alarm group Alarm Group 20 ?
  [/cover] */
  else if(AlarmGroup == SMU_ALARM_GROUP20)
  {
    /* [cover parentID={AA555433-703C-4c9d-84A0-A92ABACC824C}]
    Assign internal action to no reaction
    [/cover] */
    *IntAlarmAction = SMU_ALARM_ACTION_NONE;
    /* [cover parentID={15FB85CE-4FCE-454f-8268-BB345D184C05}]
    Assign the FSP action configured to out parameter
    [/cover] */
    *FSPAction = (Smu_FSPActionType)(((PMS_AGFSP_STDBY0.U) >> \
                                      (uint32)AlarmPos)& SMU_ALARM_FSP_MASK);
  }
  else
  {
    /* [cover parentID={62F372AD-4BB1-4921-A43C-E0AB6CE21F39}]
    Is required alarm group Alarm group 21?
    [/cover] */
    if(AlarmGroup == SMU_ALARM_GROUP21)
    {
      /* [cover parentID={39F24D91-2C2C-4660-803D-BB53709FE986}]
      Assign internal action to no reaction
      [/cover] */
      *IntAlarmAction = SMU_ALARM_ACTION_NONE;
      /* [cover parentID={4A54E508-E1ED-4498-8BE9-DDE19A15BB17}]
      Assign the FSP action configured to out parameter
      [/cover] */
      *FSPAction = (Smu_FSPActionType)(((PMS_AGFSP_STDBY1.U) >> \
                                        (uint32)AlarmPos)& SMU_ALARM_FSP_MASK);
    }
  }
  #endif
  /*Check validity of internal action*/
  IntActionRes = *IntAlarmAction;

  /*Check validity of FSP action*/
  FSPActionRes = *FSPAction;

  /* [cover parentID={C5B925C4-7642-4a75-ABF0-59B438BF20FF}]
  Is internal action as well as FSP action valid ?
  [/cover] */
  if(((IntActionRes == SMU_ALARM_ACTION_NONE) ||
      (IntActionRes == SMU_ALARM_ACTION_IGCS0) ||
      (IntActionRes == SMU_ALARM_ACTION_IGCS1) ||
      (IntActionRes == SMU_ALARM_ACTION_IGCS2) ||
      (IntActionRes == SMU_ALARM_ACTION_NMI) ||
      (IntActionRes == SMU_ALARM_ACTION_RESET) ||
      (IntActionRes == SMU_ALARM_ACTION_CPU_RESET)) &&
      (FSPActionRes <= SMU_FSP_ACTION_MSK))
  {
    /* [cover parentID={4BCDE4C2-DB3C-4837-AFBA-EAFEE4FA175B}]
    Return result as E_OK
    [/cover] */
    RetVal = (Std_ReturnType)E_OK;
  }
  else
  {
    /* [cover parentID={8D2CD8B3-1A75-45cf-B763-19344F240AF1}]
    Return result as E_NOT_OK
    [/cover] */
    RetVal = E_NOT_OK;
  }
  /* [cover parentID={5C95A235-BD5A-4099-B449-9084702C9598}]
  Return Result
  [/cover] */
  return RetVal;
}


/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/

/*******************************************************************************
** Traceability     : [cover parentID={B04BBEBC-4001-4d36-B4B5-2A1442DE3350}] **
**                    [cover parentID={20BE67A9-790F-4e0f-961F-F823089B98E1}] **
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
Std_ReturnType Smu_Init
(
  const Smu_ConfigType* const ConfigPtr
)
{
  Std_ReturnType RetVal = (Std_ReturnType)E_NOT_OK;
  uint32 Index;
  uint32 CurrentCoreID;

  /*Check if det is on or safety is enabled*/
  /* [cover parentID={0209F0E0-A75E-47c7-BE00-4C3CA36077DB}]
  DET or safety is enabled
  [/cover] */
  #if (SMU_DEV_ERROR_DETECT == STD_ON)||(SMU_SAFETY_ENABLE == STD_ON)
  /*Check if config pointer is a NULL pointer*/
  /* [cover parentID={577A59B1-E4F3-4616-B0FB-CE1C96BFFA29}]
  Check if config pointer is  a NULL pointer
  [/cover] */
  if( ConfigPtr == NULL_PTR)
  {
    /*Report error SMU_E_INIT_FAILED*/
    /* [cover parentID={B2961759-7D15-4d74-A984-93F8333BF8F3}]
    Report error SMU_E_INIT_FAILED
    [/cover] */
    Smu_lReportError(SMU_SID_INIT, SMU_E_INIT_FAILED);
  }
  else
  #endif
  {
    /*Get the current core id*/
    /* [cover parentID={4C65168E-B58B-4005-871E-B58E3D3D51D3}]
    Get the current core id
    [/cover] */
    CurrentCoreID = Mcal_GetCpuIndex();
    /*If the core is master core, proceed with initialization sequence*/
    /* [cover parentID={2882EA1A-2F3A-4c59-8FA8-FFA856726F9E}]
    Check if it is the core  master core ?
    [/cover] */
    if(MCAL_MASTER_COREID == CurrentCoreID)
    {
      /*Check if det is on or safety is enabled*/
      /* [cover parentID={31C5F837-EA53-45fb-8D38-CAD8A8398641}]
      DET is or safety is enabled
      [/cover] */
      #if (SMU_DEV_ERROR_DETECT == STD_ON) || \
      (SMU_SAFETY_ENABLE == STD_ON)

      /* Check if SMU driver is already initialized */
      /* [cover parentID={B9C4E348-42FF-4e61-B121-2DC45C97AB15}]
      Check if SMU driver is already initialized
      [/cover] */
      if(SMU_INITIALIZED == Smu_InitStatus)
      {
        /*Report error SMU_E_ALREADY_INITIALIZED*/
        /* [cover parentID={7CF4713A-D698-4e4d-AE8E-4C341E39D103}]
        Report error SMU_E_ALREADY_INITIALIZED
        [/cover] */
        Smu_lReportError(SMU_SID_INIT, SMU_E_ALREADY_INITIALIZED);
      }
      /*Check if driver is permanently locked*/
      /* [cover parentID={49CD2848-6097-4443-82E9-BD0DAE331F4C}]
      Check if configuration registers are permanently locked
      [/cover] */
      else if(((uint32)(SMU_KEYS.U & SMU_KEY_PERLOCK_MASK) >>
               SMU_LOCK_MSK) == (uint32)SMU_CFG_PERLCK_VALUE)
      {
        /* SMU config registers are permanently locked */
        /* [cover parentID={CBAF9024-3EC9-42b3-AC18-B005EA60FED5}]
        Set SMU Lock State to Locked
        [/cover] */
        Smu_LockState = SMU_LOCKED;
        /*Report error SMU_E_LOCKED*/
        /* [cover parentID={3DF437D5-189C-4119-91F6-D86737739007}]
        Report error SMU_E_LOCKED
        [/cover] */
        Smu_lReportError(SMU_SID_INIT, SMU_E_LOCKED);
        /* [cover parentID={FD570D1C-0740-4014-8AB5-9DC50E2887DA}]
        Return Result as E_NOT_OK
        [/cover] */
        RetVal = E_NOT_OK;
      }
      else
      {
        /* [cover parentID={F886D40A-FAB0-47a5-A5B0-F2C6E329EDB7}]
        Set Result to E_OK
        [/cover] */
        RetVal = E_OK;
      }
      /* Initialize SMU Driver if no DET or Safety errors */
      /* [cover parentID={49F3741A-5E9B-42aa-A1BB-70FD4954757B}]
      Are DET and safety checks  passed?
      [/cover] */
      if(RetVal == (Std_ReturnType)E_OK)
      #endif
      {

        /* [cover parentID={1CDB2637-5F2E-4a6e-8D7C-08CE79D866A3}]
        Clear all SMU Alarms
        [/cover] */
        Smu_lClearAllAlarms();

        /*Unlock the configuration to configure the SMU registers. */
        /* [cover parentID={BAFD1E3C-2C3D-460d-BB3B-1261FFF93DAA}]
        Unlock the configuration registers to configure the SMU registers
        [/cover] */
        SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG( \
            &MODULE_SMU.KEYS, SMU_CFG_KEY_UNLOCK);

        /* [cover parentID={7A08B7FA-598D-41f3-83B9-A4C9F8A24C26}]
        Configure FSP mode in FSP register of Smu_core as Bi-stable mode
        [/cover] */
        SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREGMASK(&MODULE_SMU.FSP, \
        (SMU_FSP_RESET_VAL & SMU_FSP_MODE_MSK), \
        SMU_FSP_MODE_MSK);

        /*JIRA Reference: 0000053912-9599
        A dummy read of FSP register is required to ensure that FSP mode is
        written into the register and not cached or stored in write buffer,
        before modifying the values of PRE1, PRE2 or TFSP_HIGH.
        Mcal_WriteSafetyEndInitProtRegMask API, which is used to write into
        the FSP register, has multiple dummy reads of WDT registers. Both WDT
        and SMU operate on the SPB bus. Thus, the dummy reads of WDT registers
        in the Mcal_WriteSafetyEndInitProtRegMask API also ensure that FSP mode
        is written into the FSP register.
        Hence, a separate dummy read is not done here .*/

        /* [cover parentID={7A08B7FA-598D-41f3-83B9-A4C9F8A24C26}]
        Configure FSP configuration register of Smu_core except for FSP mode
        as per the configuration*/
        SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREGMASK( \
        &MODULE_SMU.FSP, ((ConfigPtr->FSPCfg) & SMU_FSP_CFG_MSK), \
        SMU_FSP_CFG_MSK);

        /* [cover parentID={7A08B7FA-598D-41f3-83B9-A4C9F8A24C26}]
        Configure FSP mode in FSP register of Smu_core as per the
        configuration*/
        SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREGMASK( \
        &MODULE_SMU.FSP, ((ConfigPtr->FSPCfg) & SMU_FSP_MODE_MSK), \
        SMU_FSP_MODE_MSK);

        /*Configure alarm global configuration of Smu_core register
        as per the configuration */
        SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG\
        (&MODULE_SMU.AGC, ConfigPtr->AGCCfg);

        /*Configure the recovery timer register of Smu_core as per the
        configuration*/
        SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG( \
            &MODULE_SMU.RTC, ConfigPtr->RTCCfg);

        /*Configure the recovery timer 0 alarm configuration 0 register
        as per the configuration*/
        SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG \
        (&MODULE_SMU.RTAC00, ConfigPtr->RTAC00Cfg);

        /*Configure the recovery timer 0 alarm configuration 1 register
        as per the configuration*/
        SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG( \
            &MODULE_SMU.RTAC01, ConfigPtr->RTAC01Cfg);

        /*Configure the recovery timer 1 alarm configuration 0 register
        as per the configuration*/
        SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG \
        (&MODULE_SMU.RTAC10, ConfigPtr->RTAC10Cfg);

        /*Configure the recovery timer 1 alarm configuration 1 register
        as per the configuration*/
        SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG( \
            &MODULE_SMU.RTAC11, ConfigPtr->RTAC11Cfg);

        /*Configure the alarm group configuration registers
        for Smu_core*/
        /* [cover parentID={CBE27963-B9A3-460d-8893-39C4C5D0E449}]
        Configure Alarm  configuration registers as per the
        configuration for SMU Core
        [/cover] */
        for(Index = 0U; Index < SMU_CORE_TOTAL_ALARM_CONFIG_REG; Index++)
        {
          /* [cover parentID={F63E22AB-94B3-456e-A2F9-1466254A3A43}]
          Configure Alarm  configuration register as per the alarm
          group configuration for SMU Core
          [/cover] */
          /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between
          pointers of different object types due to SFR access. */
          SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG( \
              &SMU_CORE_ALARM_GROUP->CfgReg[Index], \
              ConfigPtr->AlarmCoreConfig[Index]);
        }

        /*Configure the FSP configuration registers for Smu_core*/
        /* [cover parentID={2161037F-6C28-4799-8AAE-025E4000670A}]
        Configure the FSP configuration registers for SMU Core
        [/cover] */
        for(Index = 0U; Index < SMU_CORE_TOTAL_ALARM_GROUPS; Index++)
        {
          /* [cover parentID={A42FFC7E-620A-43b5-92E4-C3AFA1C10B3C}]
          Configure the FSP configuration registers for SMU Core
          [/cover] */
          /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between
          pointers of different object types due to SFR access. */
          SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG( \
              &SMU_CORE_ALARM_GROUP->FSPCfgReg[Index], \
              ConfigPtr->AlarmCoreFspConfig[Index]);
        }

        /*Configure the Smu_stdby as disabled or enabled as per
        user configuration*/
        SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG( \
            &MODULE_PMS.CMD_STDBY, (SMU_STDBY_BIT_PROT | \
                                    ConfigPtr->AlarmStdbyCfg));

        /*Configure the FSP configuration registers for Smu_stdby
        group 20*/
        SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG( \
            &MODULE_PMS.AGFSP_STDBY0, (SMU_STDBY_BIT_PROT | \
                                       ConfigPtr->AlarmStdbyFspConfig[0]));

        /*Configure the FSP configuration registers for Smu_stdby
        group 21*/
        SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG( \
            &MODULE_PMS.AGFSP_STDBY1, (SMU_STDBY_BIT_PROT | \
                                       ConfigPtr->AlarmStdbyFspConfig[1]));

        /* After configuration set temporary lock of SMU configuration*/
        /* [cover parentID={01D28EAB-1F6F-4ebd-BE28-804B1FA9C83A}]
        Set temporary lock of SMU configuration
        [/cover] */
        SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG( \
            &MODULE_SMU.KEYS, SMU_CFG_KEY_TEMPLOCK);

        /* [cover parentID={C54BB564-F844-4a24-BE88-83A157DE12DE}]
        Is DET or Safety or Init Check enabled?
        [/cover] */
        #if ((SMU_DEV_ERROR_DETECT == STD_ON) || \
        (SMU_SAFETY_ENABLE == STD_ON) ||(SMU_INIT_CHECK_API == STD_ON))
        /* Set the error pin status to not set */
        /* [cover parentID={A36C7B8A-9C44-4a72-92EA-E8798E5FCC8B}]
        Set the error pin status to not set
        [/cover] */
        Smu_ErrPinStatus = SMU_ERRPIN_NOTSET;

        /* Set the error pin status to not set */
        /* [cover parentID={739BA3D4-5E81-42a2-88D6-4FAA4F2D3E41}]
        Set the Driver state to not failed
        [/cover] */
        Smu_DriverState = SMU_NOT_FAILED;

        /* Set the lock state  to not locked */
        /* [cover parentID={42818553-DB6E-48d8-9882-78E118D768C6}]
        Set the lock state  to not locked
        [/cover] */
        Smu_LockState = SMU_NOT_LOCKED;

        /* Set the initialisation staus as initialized */
        /* [cover parentID={3B1EFE55-E1FE-4ec4-AF2C-4BCA151AC4DB}]
        Set the initialisation status as initialized
        [/cover] */
        Smu_InitStatus = SMU_INITIALIZED;
        #endif
        /* [cover parentID={89F549DF-6A85-413d-B152-EFE7A1AB9CD8}]
        Set Result as E_OK
        [/cover] */
        RetVal = E_OK;
      }
    }
    /*If the core is a slave core abort the sequence*/
    else
    {
      /* [cover parentID={FD570D1C-0740-4014-8AB5-9DC50E2887DA}]
      Return Result as E_NOT_OK
      [/cover] */
      RetVal = E_NOT_OK;

      /*Check if DET is on or safety is enabled*/
      /* [cover parentID={4763A026-7422-42c9-AADD-9B18BDDD3884}]
      DET is ON or safety is enabled
      [/cover] */
      #if (SMU_DEV_ERROR_DETECT == STD_ON) || \
      (SMU_SAFETY_ENABLE == STD_ON)
      /*Report error SMU_E_CORE_MISMATCH*/
      /* [cover parentID={577F7A58-C22E-47ec-B34C-E4574E48C911}]
      Report error SMU_E_CORE_MISMATCH
      [/cover] */
      Smu_lReportError(SMU_SID_INIT, SMU_E_CORE_MISMATCH);
      #endif
    }
  }
  /* [cover parentID={D096F902-EFD2-4eef-B83D-73E6925DD209}]
  Return Result
  [/cover] */
  return RetVal;
}

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
/* CYCLOMATIC_Smu_DeInit_JUSTIFICATION: This Function has Cyclomatic Complexity
>15. This is due to higher number of DET checks inside the function which are
used to reset the global variables and do plausibility check. The different if
conditions in different operating mode causes the complexity to increase,but
actually during run-time out of all if conditions many will be pre-compile
time removed */
Std_ReturnType Smu_DeInit(void)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint32 Index;
  uint32 CurrentCoreID;

  /*Get the current core id*/
  /* [cover parentID={D3DC8446-2C4F-4c82-856B-3FD2058302D4}]
  Get the current core ID
  [/cover] */
  CurrentCoreID = Mcal_GetCpuIndex();
  /*If the current core is the master core proceed with
  deinitialization sequence*/
  /* [cover parentID={D58AC000-BE3E-4507-8A45-7EE56FED0CA9}]
  Check if the core is the core  master core ?
  [/cover] */
  if(MCAL_MASTER_COREID == CurrentCoreID)
  {
    /*Check if DET is on or Safety is enabled*/
    /* [cover parentID={C6F432EA-73F8-4a3c-B509-FD283F60D90E}]
    DET is ON or safety is enabled
    [/cover] */
    #if (SMU_DEV_ERROR_DETECT == STD_ON) || \
    (SMU_SAFETY_ENABLE == STD_ON)

    /* Check if SMU driver is already initialized */
    /* [cover parentID={5C134582-15EB-450f-A00B-963F8163D7BB}]
    Check if SMU driver is not initialized
    [/cover] */
    if(SMU_NOT_INITIALIZED == Smu_InitStatus)
    {
      /* [cover parentID={C8BCA559-19A4-4a33-B91D-978FBF61B715}]
      Report error SMU_E_UNINIT
      [/cover] */
      Smu_lReportError(SMU_SID_DEINIT, SMU_E_UNINIT);
    }
    /*Check if driver is permanently locked*/
    /* [cover parentID={A8631D44-E072-4839-8BEB-7EC15E498C1B}]
    Check if SMU cfg registers are permanently locked
    [/cover] */
    else if(Smu_LockState == SMU_LOCKED)
    {
      /*Report error SMU_E_LOCKED*/
      /* [cover parentID={8A120D9E-87FB-4b6f-A834-F99046C08063}]
      Report error SMU_E_LOCKED
      [/cover] */
      Smu_lReportError(SMU_SID_DEINIT, SMU_E_LOCKED);
    }
    /* [cover parentID={572D9FAA-D874-49ce-81A7-54D3171135F1}]
    For all other conditions when driver is both initialized and unlocked
    [/cover] */
    else
    {
      /* [cover parentID={9B65BA75-1136-47b5-8A51-A3E8318DD8E4}]
      Set result as E_OK
      [/cover] */
      RetVal = E_OK;
    }
    /*Check if all DET or Saftey checks have passed*/
    /* [cover parentID={7F7DC553-8B18-4927-AA9E-68E5E0A95376}]
    Have all checks passed ?
    [/cover] */
    if(RetVal == E_OK)
    #endif
    {
      /* [cover parentID={372A0DDE-01BB-4b49-9745-9C6A445EF95C}]
      Is DET or Safety or Init Check enabled?
      [/cover] */
      #if ((SMU_DEV_ERROR_DETECT == STD_ON) || \
      (SMU_SAFETY_ENABLE == STD_ON) ||(SMU_INIT_CHECK_API == STD_ON))
      /* Set SMU Driver init status to not initialized */
      /* [cover parentID={3F931DBC-A994-4ab7-AA2C-3609CA287296}]
      Set the initialization status to deinitialized
      [/cover] */
      Smu_InitStatus = SMU_NOT_INITIALIZED;
      #endif

      /*Unlock configuration register configure the SMU registers. */
      /* [cover parentID={05F5391C-DF31-4d1c-B856-09C99C43F897}]
      Unlock configuration register configure the SMU registers
      [/cover] */
      SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG( \
          &MODULE_SMU.KEYS, SMU_CFG_KEY_UNLOCK);

      /* Configure alarm group configuration registers of
      Smu_core to their reset value */
      /* [cover parentID={BD23A33E-1750-4106-9421-D2EBEC7C0517}]
      Configure alarm group configuration registers of SMU Core to
      their reset value
      [/cover] */

      for(Index = 0U; Index < SMU_CORE_TOTAL_ALARM_CONFIG_REG; Index++)
      {
        /* [cover parentID={8CE28A9D-EE50-4e3d-8873-78B7245F8A8C}]
        Select the reset value of alarm group configuration register
        depending on the alarm group
        [/cover] */
        /* [cover parentID={AAC508C1-8830-4213-8F74-4F161C1E9067}]
        Check if the configuration register is alarm group 8
        configuration register
        [/cover] */
        if((Index == SMU_GROUP8_CFG_POS1) || \
              (Index == SMU_GROUP8_CFG_POS2))
        {
          /* [cover parentID={676FA24F-2D1F-4b74-B77C-AF38EF4E8D00}]
          Configure alarm group 8 configuration registers of SMU Core
           to reset value of alarm group 8 configuration
          [/cover] */
          /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between
          pointers of different object types due to SFR access. */
          SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG( \
              &SMU_CORE_ALARM_GROUP->CfgReg[Index], \
              SMU_ALARM8_CFG_RESET_VAL);

        }
        /* [cover parentID={87582AAD-D472-4f9a-B55C-2497C48EC7B0}]
        Check if the configuration register is alarm group 10
        configuration register
        [/cover] */
        else if((Index == SMU_GROUP10_CFG_POS1) || \
                (Index == SMU_GROUP10_CFG_POS2))
        {
          /* [cover parentID={CAC02F34-1859-4053-8C2F-6CF83A44746E}]
          Configure alarm group 10 configuration registers of SMU
          Core to reset value of alarm group 10 configuration
          [/cover] */
          /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between
          pointers of different object types due to SFR access. */
          SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG( \
              &SMU_CORE_ALARM_GROUP->CfgReg[Index], \
              SMU_ALARM10_CFG_RESET_VAL);
        }
        /* [cover parentID={99825212-B921-49c7-9EAD-DDE310BA397F}]
        For all the configuration register except alarm group 8 and
        group10 configuration register
        [/cover] */
        else
        {
          /* [cover parentID={D848DCB8-E079-4d91-96FC-3F242990421B}]
          Configure alarm group configuration registers of SMU Core
          to their reset value
          [/cover] */
          /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between
          pointers of different object types due to SFR access. */
          SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG( \
              &SMU_CORE_ALARM_GROUP->CfgReg[Index] \
              , SMU_ALARM_CFG_RESET_VAL);
        }
      }
      /* Configure FSP configuration registers of Smu_core to their
      reset value */
      /* [cover parentID={A8B9B38C-E22F-4915-99DE-4A2048787581}]
      Configure FSP configuration registers of SMU Core to their reset
      value
      [/cover] */
      for(Index = 0U; Index < SMU_CORE_TOTAL_ALARM_GROUPS; Index++)
      {
        /* [cover parentID={34B22379-76A1-4176-BB99-3855C5ED89EE}]
        Check if the alarm group is alarm group 10
        [/cover] */
        if(Index == (uint32)SMU_ALARM_GROUP10)
        {
          /* [cover parentID={C8030C99-A06F-4aa0-B26E-D498805D0382}]
          Configure FSP configuration register of alarm group 10 of
          Smu_core to reset value of alarrm group 10 FSP configuration
          [/cover] */
          /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between
          pointers of different object types due to SFR access. */
          SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG( \
              &SMU_CORE_ALARM_GROUP->FSPCfgReg[Index], \
              SMU_ALARM10_CFG_RESET_VAL);

        }
        /* [cover parentID={2D69E9FB-56E9-42ff-91FA-1AF8D315E616}]
        For all the alarm groups except alarm group10
        [/cover] */
        else
        {
          /* [cover parentID={A8B9B38C-E22F-4915-99DE-4A2048787581}]
          Configure FSP configuration registers of SMU Core to
          their reset value
          [/cover] */
          /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between
          pointers of different object types due to SFR access. */
          SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG( \
              &SMU_CORE_ALARM_GROUP->FSPCfgReg[Index], \
              SMU_ALARM_FSP_RESET_VAL);
        }
      }

      /* Configure Smu_stdby alarm group 20 FSP configuration register
      to its reset value*/
      SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG( \
          &MODULE_PMS.AGFSP_STDBY0, (SMU_STDBY_BIT_PROT | \
                                     SMU_AGFSPSTDBY0_RESET_VAL));

      /* Configure Smu_stdby alarm group 21 FSP configuration register
          to its reset value*/
      SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG( \
          &MODULE_PMS.AGFSP_STDBY1, (SMU_STDBY_BIT_PROT | \
                                     SMU_AGFSPSTDBY1_RESET_VAL));

      /* [cover parentID={85D1E643-A48C-4c20-8001-E550C3457BF0},
                         {7A08B7FA-598D-41f3-83B9-A4C9F8A24C26}]
      Configure FSP mode in FSP register of Smu_core as Bi-stable mode
      which is also the reset value
      [/cover] */
      SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREGMASK( \
          &MODULE_SMU.FSP, (SMU_FSP_RESET_VAL & SMU_FSP_MODE_MSK), \
          SMU_FSP_MODE_MSK);

      /*JIRA Reference: 0000053912-9599
      A dummy read of FSP register is required to ensure that FSP mode is
      written into the register and not cached or stored in write buffer,
      before modifying the values of PRE1, PRE2 or TFSP_HIGH.
      Mcal_WriteSafetyEndInitProtRegMask API, which is used to write into
      the FSP register, has multiple dummy reads of WDT registers. Both WDT
      and SMU operate on the SPB bus. Thus, the dummy reads of WDT registers
      in the Mcal_WriteSafetyEndInitProtRegMask API also ensure that FSP mode
      is written into the FSP register.
      Hence, a separate dummy read is not done here .*/

      /* [cover parentID={C4889A78-324F-4e4e-981E-A25FF099A83D}]
      Configure FSP configuration register of Smu_core except for FSP mode to
      its reset value
      [/cover] */
      SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREGMASK( \
          &MODULE_SMU.FSP, (SMU_FSP_RESET_VAL & SMU_FSP_CFG_MSK), \
          SMU_FSP_CFG_MSK);

      /* Configure alarm global configuration register of Smu_core to
      its reset value */
      SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG( \
          &MODULE_SMU.AGC, SMU_AGC_RESET_VAL);

      /* Configure recovery timer configuration register of Smu_core to
      its reset value */
      SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG( \
          &MODULE_SMU.RTC, SMU_RTC_RESET_VAL);

      /* Configure recovery timer 0 alarm configuration 0 register of
      Smu_core to its reset value */
      SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG( \
          &MODULE_SMU.RTAC00, SMU_RTAC00_RESET_VAL);

      /* Configure recovery timer 0 alarm configuration 1 register of
      Smu_core to its reset value */
      SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG( \
          &MODULE_SMU.RTAC01, SMU_RTAC01_RESET_VAL);

      /* Configure recovery timer 1 alarm configuration 0 register of
      Smu_core to its reset value */
      SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG( \
          &MODULE_SMU.RTAC10, SMU_RTAC10_RESET_VAL);

      /* Configure recovery timer 1 alarm configuration 1 register of
      Smu_core to its reset value */
      SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG( \
          &MODULE_SMU.RTAC11, SMU_RTAC11_RESET_VAL);

      /* Configure Smu_stdby CMD register to its reset value */
      SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG( \
        &MODULE_PMS.CMD_STDBY, (SMU_STDBY_BIT_PROT | SMU_CMD_STDBY_RESET_VAL));


      /* After configuration set temporary lock of SMU configuration */
      /* [cover parentID={EB65210A-06DE-4dba-BA5E-46EB65A803D7}]
      Set temporary lock of SMU configuration
      [/cover] */
      SMU_LIB_INIT_DEINIT_WRITESAFETYENDINITPROTREG( \
          &MODULE_SMU.KEYS, SMU_CFG_KEY_TEMPLOCK);

      /* [cover parentID={2E81904E-2A04-4b44-975B-2480F77920A8}]
      Clear all SMU Alarms
      [/cover] */
      Smu_lClearAllAlarms();

      /* [cover parentID={CCFAB638-FC8F-4df7-9DF0-5384DAA4B59C}]
      Is DET or Safety or Init Check is enabled?
      [/cover] */
      #if ((SMU_DEV_ERROR_DETECT == STD_ON) || \
      (SMU_SAFETY_ENABLE == STD_ON) ||(SMU_INIT_CHECK_API == STD_ON))
      /* Set SMU error pin status to error pin not set */
      /* [cover parentID={6B1E8803-4629-49b2-AB54-230CB7684B35}]
      Set the error pin status to not set
      [/cover] */
      Smu_ErrPinStatus = SMU_ERRPIN_NOTSET;

      /* Set SMU Driver status to not failed */
      /* [cover parentID={58695AB0-C954-4404-ADCD-AAC50E20648D}]
      Set the Driver state to not failed
      [/cover] */
      Smu_DriverState = SMU_NOT_FAILED;

      /* Set SMU lock status to not locked */
      /* [cover parentID={D9CE2E5B-DBCC-412f-A3AC-DAB6D5ACA25B}]
      Set the lock state  to not locked
      [/cover] */
      Smu_LockState = SMU_NOT_LOCKED;
      #endif
      /* [cover parentID={6E6EB485-2ECC-4fa2-9299-DCAF42FA1AEA}]
      Set Result as E_OK
      [/cover] */
      RetVal = E_OK;
    }
  }
  else
  {
    /* [cover parentID={74823B27-26C9-4405-B7CC-0C9D9C450BEC}]
    Return Result as E_NOT_OK
    [/cover] */
    RetVal = E_NOT_OK;
    /*Check if det is on or safety is enabled*/
    /* [cover parentID={5704399B-511F-45ab-B936-B4CABA760879}]
    DET is ON or safety is enabled
    [/cover] */
    #if(SMU_DEV_ERROR_DETECT == STD_ON)||(SMU_SAFETY_ENABLE == STD_ON)
    /*Report error SMU_E_ALREADY_INITIALIZED*/
    /* [cover parentID={58EE5FB3-3151-45e7-A3D7-B7FE626E254F}]
    Report error SMU_E_CORE_MISMATCH
    [/cover] */
    Smu_lReportError(SMU_SID_DEINIT, SMU_E_CORE_MISMATCH);
    #endif

  }
  /* [cover parentID={DFE9BD05-8B4B-400e-873D-BAA2C2F124DB}]
  Return Result
  [/cover] */
  return RetVal;
}

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
Std_ReturnType Smu_ClearAlarmStatus
(
  const Smu_AlarmGroupId AlarmGroup,
  const Smu_AlarmIdType AlarmPos
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint32 AlarmStatusReadback = 0xFFFFFFFFU;
  uint32 Timeout = 0U;

  /*Check if DET or Safety errors are enabled*/
  /* [cover parentID={37F52E11-AB41-4520-8531-9465980FE670}]
  DET OR Safety Checks ON
  [/cover] */
  #if (SMU_DEV_ERROR_DETECT == STD_ON) || (SMU_SAFETY_ENABLE == STD_ON)
  /*Check if driver is initialized and driver state not failed*/
  /* [cover parentID={3659CFC4-69DA-450d-AAD9-4C3C3F9EEFE5}]
  Check if driver is initialized and is not in failed state
  [/cover] */
  RetVal = Smu_lInitFailedCheck(SMU_SID_CLEAR_ALARM_STATUS);

  /* [cover parentID={6AEF1797-A95A-4017-9159-67070EB2E934}]
  Have all initialization checks passed ?
  [/cover] */
  if(RetVal == E_OK)
  {
    /*Check the validity of alarm group and position.
    In case Smu_stdby group and position is requested check whether
    Smu_stdby is enabled*/
    /* [cover parentID={EBC0834E-211D-41c1-8B38-499E0371F7FE}]
    Check the validity of alarm group and position
    [/cover] */
    RetVal = Smu_lAlarmValidCheck(AlarmGroup, AlarmPos,
                                  SMU_SID_CLEAR_ALARM_STATUS);
  }
  /*Check if all checks have passed*/
  /* [cover parentID={25090A97-E5A9-4698-A8EB-9D6D6506B67E}]
  Have all checks passed ?
  [/cover] */
  if(RetVal == E_OK)
  #endif
  {
    /* [cover parentID={0D20AD6F-7260-4c0d-90C9-531A056367E4}][/cover] */
    /* [cover parentID={6DA99BD3-6A81-4b94-8D75-680F0374A2BB}]
    Enter critical section
    [/cover] */
    SchM_Enter_Smu_DriverAccess();
    /*Acquire Spinlock*/
    /* [cover parentID={C9F6FE80-E4CE-4aad-B21E-CE93B17C1A36}]
    Acquire spinlock
    [/cover] */
    Mcal_GetSpinlock(&Smu_LockAddress, SMU_SPINLOCK_TIMEOUT);

    /* [cover parentID={859D93D7-9434-4806-9C4B-78895B88FF65}]
    Clear Alarm Status
    [/cover] */
    Smu_lClrAlarmStatus(AlarmGroup, AlarmPos);

    /*Read back AG register to validate the Clear */
    /* [cover parentID={A3E2E97D-84CA-4218-9F99-890830A65BE3}]
    Read back AG register to validate the Clear
    [/cover] */
    do
    {
      /* [cover parentID={EAFC1A72-385B-4b33-AECF-D3C5021A65A8}]
      Check if the alarm group is in Smu_core. The check is done in case
      DET and Safety is OFF and Smu_Stdby is ON
      [/cover] */
      #if(SMU_STANDBY_SWITCH == STD_ON)||\
      ((SMU_DEV_ERROR_DETECT == STD_OFF) && \
       (SMU_SAFETY_ENABLE == STD_OFF))
      /* [cover parentID={EAFC1A72-385B-4b33-AECF-D3C5021A65A8}]
      Check if the alarm group is in Smu_core
      [/cover] */
      if((uint32)AlarmGroup < SMU_CORE_TOTAL_ALARM_GROUPS)
      #endif
      {
        /* Read Alarm status */
        /* [cover parentID={E4473F51-4E6F-4b10-A13E-1AB2E07F556E}]
        Read the alarm status of alarm group in core domain
        [/cover] */
        /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between
         pointers of different object types due to SFR access. */
        AlarmStatusReadback = (((uint32) \
              (SMU_CORE_ALARM_GROUP->AGStatusReg[AlarmGroup].U) >> AlarmPos) \
             & SMU_ALARM_POS1);

      }
      /*For Smu_stdby*/
      /* [cover parentID={A5CB8F8E-E6D1-47e4-B7DA-60E2BE0A91AB}]
      Standby mode is enabled
      [/cover] */
      #if(SMU_STANDBY_SWITCH == STD_ON)
      /* [cover parentID={961AEBCD-7A61-4218-AE28-8565808FB387}]
      Check if the alarm group is SMU Alarm Group 20
      [/cover] */
      else if(AlarmGroup == SMU_ALARM_GROUP20)
      {
        /* [cover parentID={ABB04BFD-54DD-4bc2-A19D-11822FAA3882}]
        Read the alarm status from Alarm group 20
        [/cover] */
        AlarmStatusReadback = (uint32)(PMS_AG_STDBY0.U >> AlarmPos) \
                              & SMU_ALARM_POS1;
      }
      else
      {
        /* [cover parentID={09323012-00FE-4936-8A00-F7E4A20E123A}]
        Check if DET and Safety is OFF and Smu_Stdby id ON. If yes,
        then check if the alarm group is SMU Alarm Group 21
        [/cover] */
        #if (SMU_DEV_ERROR_DETECT == STD_OFF) && \
        (SMU_SAFETY_ENABLE == STD_OFF)
        /* [cover parentID={09323012-00FE-4936-8A00-F7E4A20E123A}]
        Check if the alarm group is SMU Alarm Group 21
        [/cover] */
        if(AlarmGroup == SMU_ALARM_GROUP21)
        #endif
        {
          /* [cover parentID={E08B2692-DB05-4a81-98AC-739268BE5EBE}]
          Read the alarm status from Alarm group 21
          [/cover] */
          AlarmStatusReadback = (uint32)(PMS_AG_STDBY1.U >> AlarmPos) \
                                & SMU_ALARM_POS1;
        }
      }
      #endif
      Timeout++;
    }
    /* [cover parentID={7DCB738B-DBF9-4ba6-9B68-3F05C99231CD}]
    Loop till Alarm Status Clear is not Validated or till Timeout
    [/cover] */
    while((Timeout < SMU_AGSTATUS_TIMEOUT) &&
          (AlarmStatusReadback != SMU_CLEAR_ALARM_STATUS_READBACK));

    /*Release spinlock*/
    /* [cover parentID={E5729C2E-60FA-439d-B8B2-7C61D984913A}]
    Release Spinlock
    [/cover] */
    Mcal_ReleaseSpinlock(&Smu_LockAddress);
    /* [cover parentID={1A2077D6-9DF6-4c3b-A1F9-6755D70C0436}]
    Exit critical section
    [/cover] */
    SchM_Exit_Smu_DriverAccess();

    /*Check the readback value*/
    /* [cover parentID={92B1B4FC-5C21-4767-AA0C-D30B6CD5FA7D}]
    Is readback value equal to expected status ?
    [/cover] */
    if(AlarmStatusReadback != SMU_CLEAR_ALARM_STATUS_READBACK)
    {
      /* [cover parentID={C1EBF5F8-9E36-47fb-B0DC-96BC40575354}]
      Set Result as E_NOT_OK
      [/cover] */
      RetVal = E_NOT_OK;

      /* [cover parentID={0ACD2144-183F-42f9-AB78-0F37EBEFF276}]
      Production Error notification for clearing alarm status failure or success is
      enabled
      [/cover] */
      #if (SMU_CLEAR_ALARM_STATUS_DEM_NOTIF == \
      SMU_ENABLE_DEM_REPORT)
      /* Report failure as Production Error event status*/
      /* [cover parentID={433D1BD1-EBB3-44fa-A167-403123BD967D}]
      Report failure as Production Error event status
      [/cover] */
      Smu_lReportDemError(SMU_E_CLEAR_ALARM_STATUS_FAILURE,
                            DEM_EVENT_STATUS_FAILED);
      #endif
    }
    else
    {
      /* [cover parentID={8B75A328-5DE7-47c7-8F95-F497F1F885EF}]
      Set Result as E_OK
      [/cover] */
      RetVal = E_OK;
      /* [cover parentID={1E04B99D-E58D-4f48-A4B3-7C5C7D62E855}]
      Production Error notification for clearing alarm status failure or success is
      enabled
      [/cover] */
      #if (SMU_CLEAR_ALARM_STATUS_DEM_NOTIF == \
      SMU_ENABLE_DEM_REPORT)
      /* Report success as Production Error event status*/
      /* [cover parentID={A231A655-F5D0-49a1-86CA-EA152A0846B4}]
      Report success as Production Error event status
      [/cover] */
      Smu_lReportDemError(SMU_E_CLEAR_ALARM_STATUS_FAILURE,
                            DEM_EVENT_STATUS_PASSED);
      #endif
    }
  }
  /* [cover parentID={30EC0A0B-8ED5-4357-BD08-1ECCE9CE8AF5}]
  Return Result
  [/cover] */
  return RetVal;
}

/*******************************************************************************
** Traceability     : [cover parentID={474BDCAA-C380-4ce2-AEBB-FEF0F93F2CA9}] **
**                                                                            **
** Syntax           : Std_ReturnType Smu_SetAlarmStatus                       **
**                    (                                                       **
**                      const Smu_AlarmGroupId AlarmGroup,                    **
**                      const Smu_AlarmGroupId AlarmPos                       **
**                    )                                                       **
**                                                                            **
** Description      : The purpose of the API is to set the requested alarm    **
**                    status. This service can be used by the user software to**
**                    to trigger software SMU alarm. For SMU_core during the  **
**                    START state of the SMU, it shall be possible to set any **
**                    of the alarms. However, during the RUN state, only the  **
**                    software alarms shall be set. The API is applicable only**
**                    for SMU_core alarm groups and positions.                **
**                                                                            **
** [/cover]                                                                   **
** Service ID       : 0xAE                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : AlarmGroup : Alarm group register                       **
**                    AlarmPos : Alarm position within the requested group    **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK - Operation successfully performed                 **
**                    E_NOT_OK - Operation failed eg. Due to invalid          **
**                      parameters.                                           **
*******************************************************************************/
Std_ReturnType Smu_SetAlarmStatus
(
  const Smu_AlarmGroupId AlarmGroup,
  const Smu_AlarmIdType AlarmPos
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint32 Timeout = 0U;
  uint32 AlarmStatusReadback = 0xFFFFFFFFU;

  /*Check if the DET or Safety checks are enabled*/
  /* [cover parentID={FA987376-A7E7-4508-99B2-CFD2A0397112}]
  DET OR Safety Checks ON
  [/cover] */
  #if (SMU_DEV_ERROR_DETECT == STD_ON) || (SMU_SAFETY_ENABLE == STD_ON)

  uint32 AlarmRes = 0U;
  uint32 CoreAlarmIdReservedType[SMU_CORE_TOTAL_ALARM_GROUPS] =
  {
    SMU_GROUP0_POS,
    SMU_GROUP1_POS,
    SMU_GROUP2_POS,
    SMU_GROUP3_POS,
    SMU_GROUP4_POS,
    SMU_GROUP5_POS,
    SMU_GROUP6_POS,
    SMU_GROUP7_POS,
    SMU_GROUP8_POS,
    SMU_GROUP9_POS,
    SMU_GROUP10_POS,
    SMU_GROUP11_POS,
  };

  /*Check if driver is initialized and driver state not failed*/
  /* [cover parentID={167BD113-2215-4287-AE75-DF7400BA3350}]
  Check if driver is initialized and is not in failed state
  [/cover] */
  RetVal = Smu_lInitFailedCheck(SMU_SID_SET_ALARM_STATUS);

  /* [cover parentID={F49B8616-BC70-4141-9609-A3927B97339C}]
  Have all checks passed ?
  [/cover] */
  if(RetVal == E_OK)
  {
    /* [cover parentID={8BBC54BF-9988-4d0a-B170-8864FBAD662A}]
    Is the alarm position within the maximum range?
    [/cover] */
    if((uint32)AlarmPos <= SMU_MAX_ALARM_POS)
    {
      /* [cover parentID={6429446D-1FD5-4265-B94C-D30299685BF8}]
      Is the alarm group within Smu_core?
      [/cover] */
      if((uint32)AlarmGroup < SMU_CORE_TOTAL_ALARM_GROUPS)
      {
        AlarmRes = (CoreAlarmIdReservedType[AlarmGroup]) & \
                   ((uint32)SMU_ALARM_VALID << (uint32)AlarmPos);

        AlarmRes = AlarmRes >> (uint32)AlarmPos;
        /* [cover parentID={9AAD5213-E7A0-458d-9266-B98CA7B128E5}]
        Check the validity of alarm position
        [/cover] */
        if(AlarmRes == SMU_ALARM_INVALID)
        {
          /* [cover parentID={8744099B-118A-4bed-996C-22D48091A4E5}]
          Report error SMU_E_PARAM_GROUP
          [/cover] */
          Smu_lReportError(SMU_SID_SET_ALARM_STATUS, SMU_E_PARAM_GROUP);
          RetVal = E_NOT_OK;
        }
      }
      else
      {
        /* [cover parentID={99F488C7-B8FE-4b09-9B96-975E761CB4DA}]
        Report error SMU_E_PARAM_GROUP
        [/cover] */
        Smu_lReportError(SMU_SID_SET_ALARM_STATUS, SMU_E_PARAM_GROUP);
        RetVal = E_NOT_OK;
      }
    }
    else
    {
      /*Report error SMU_E_PARAM_GROUP*/
      /* [cover parentID={112687FE-AC96-4ba3-85EA-5A18B7C25A88}]
      Report error SMU_E_PARAM_GROUP
      [/cover] */
      Smu_lReportError(SMU_SID_SET_ALARM_STATUS, SMU_E_PARAM_GROUP);
      RetVal = E_NOT_OK;
    }
  }
  /*Check if all checks have passed*/
  /* [cover parentID={96096F14-0055-4f2d-A450-E56153C00EFB}]
  Have all checks passed ?
  [/cover] */
  if(RetVal == E_OK)
  #endif
  {
    /* [cover parentID={0D20AD6F-7260-4c0d-90C9-531A056367E4}][/cover] */
    /* [cover parentID={7AC360ED-9ED0-428c-9D58-CC49AB8D6093}]
    Enter critical section
    [/cover] */
    SchM_Enter_Smu_DriverAccess();
    /*Acquire Spinlock*/
    /* [cover parentID={F7BB6B09-719A-45df-9FAD-85B370EA67C8}]
    Get Spinlock
    [/cover] */
    Mcal_GetSpinlock(&Smu_LockAddress, SMU_SPINLOCK_TIMEOUT);

    /* [cover parentID={15B941A8-23E9-44e0-A588-4B57E873B66E}]
    Smu_lSetAlarmStatus
    [/cover] */
    Smu_lSetAlarmStatus(AlarmGroup, AlarmPos);

    /*Confirm the readback status*/
    /* [cover parentID={E75C7E2F-316F-45de-A498-FB47CE177AEB}]
    Current Value of Alarm Status Timer
    [/cover] */
    do
    {
      /*Read the alarm status*/
      /* [cover parentID={E8EE1ABE-E212-44e9-873F-F8E463FE0CE0}]
      Read the alarm status
      [/cover] */
      /*MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between pointers
         of different object types due to SFR access. */
      AlarmStatusReadback = (((uint32) \
                        (SMU_CORE_ALARM_GROUP->AGStatusReg[AlarmGroup].U) >> \
                        AlarmPos)& SMU_ALARM_POS1);
      Timeout++;

    }
    /* [cover parentID={853288A6-F376-4141-80DE-D74BDCE301BE}]
    Loop till Timeout or Change in Alarm Status
    [/cover] */
    while((Timeout < SMU_AGSTATUS_TIMEOUT) &&
          (AlarmStatusReadback != SMU_SET_ALARM_STATUS_READBACK));

    /*Release spinlock*/
    /* [cover parentID={7B24FFF4-445B-4a67-AC84-62B9047D5648}]
    Release spinlock
    [/cover] */
    Mcal_ReleaseSpinlock(&Smu_LockAddress);
    /* [cover parentID={A3891C9E-EEBC-4e69-8A7D-DDC8DF5C76CA}]
    Exit critical section
    [/cover] */
    SchM_Exit_Smu_DriverAccess();

    /* [cover parentID={342C1FC1-9201-4ea5-9F91-6D83DC82BB4B}]
    Is readback value equal to expected status ?
    [/cover] */
    /*Check if readback value is equal to expected status*/
    if(AlarmStatusReadback != SMU_SET_ALARM_STATUS_READBACK)
    {
      /* Error in reading */
      /* [cover parentID={423057EA-4D81-4c4b-B02B-B8F2F3D6A765}]
      Set Result as E_NOT_OK
      [/cover] */
      RetVal = E_NOT_OK;

      /* [cover parentID={27D372DF-BD68-455d-9768-38160A9333D7}]
      Production Error notification for setting alarm status failure is enabled
      [/cover] */
      #if (SMU_SET_ALARM_STATUS_DEM_NOTIF == \
      SMU_ENABLE_DEM_REPORT)
      /* Report failure as Production Error event status*/
      /* [cover parentID={8928DCFE-51C5-48bb-8CEB-99187B49072F}]
      Report failure as Production Error event status
      [/cover] */
      Smu_lReportDemError(SMU_E_SET_ALARM_STATUS_FAILURE,
                            DEM_EVENT_STATUS_FAILED);
      #endif
    }
    else
    {
      /* [cover parentID={4748C213-EE3D-4557-91AA-899060B37272}]
      Set Result as E_OK
      [/cover] */
      RetVal = E_OK;
      /* [cover parentID={D40A04C4-73FD-4a21-B56C-F8BD6343F771}]
      Production Error notification for setting alarm status failure or
      success is enabled
      [/cover] */
      #if (SMU_SET_ALARM_STATUS_DEM_NOTIF == \
      SMU_ENABLE_DEM_REPORT)
      /* Report success as Production Error event status*/
      /* [cover parentID={4C63B199-5645-4d55-9026-9CE7388AFA2E}]
      Report success as Production Error event status
      [/cover] */
      Smu_lReportDemError(SMU_E_SET_ALARM_STATUS_FAILURE,
                            DEM_EVENT_STATUS_PASSED);
      #endif
    }
  }
  /* [cover parentID={75C9C8CD-4EB9-484a-B495-57AA470AFD73}]
  Return Result
  [/cover] */
  return RetVal;
}

/*******************************************************************************
** Traceability      :[cover parentID={2555771A-6BE0-4ba4-9FDA-F301A662610B}] **
**                                                                            **
** Syntax           : Std_ReturnType Smu_GetAlarmStatus                       **
**                    (                                                       **
**                      const Smu_AlarmGroupId AlarmGroup,                    **
**                      uint32* const AlarmStatus                             **
**                    )                                                       **
**                                                                            **
** Description      : The purpose of the API is to provide the alarm status   **
**                      requested alarm group.                                **
** [/cover]                                                                   **
** Service ID       : 0xAF                                                    **
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
*******************************************************************************/
Std_ReturnType Smu_GetAlarmStatus
(
  const Smu_AlarmGroupId AlarmGroup,
  uint32* const AlarmStatus
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  /*Check if DET or Safety error is enabled*/
  /* [cover parentID={5F4AF45C-AEBC-4f15-8091-111BB5C70904}]
  DET OR Safety Checks ON
  [/cover] */
  #if (SMU_DEV_ERROR_DETECT == STD_ON) || (SMU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={2B3FADE9-3F7C-4f9a-92F2-AED5F0B7EF17}]
  Check if input parameter is NULL pointer
  [/cover] */
  if(AlarmStatus == NULL_PTR)
  {
    /* [cover parentID={64010FFE-28DF-4aa0-9688-4DD8868E8113}]
    Report error SMU_E_PARAM_POINTER
    [/cover] */
    Smu_lReportError(SMU_SID_GET_ALARM_STATUS, SMU_E_PARAM_POINTER);
  }
  /* [cover parentID={C1B94F65-79AE-4879-A395-3BBC5F4D1B13}]
  Is SMU driver initialized ?
  [/cover] */
  else if(SMU_INITIALIZED == Smu_InitStatus)
  {
    /* [cover parentID={922DC0BD-5888-49c4-B0C1-90D5DB401341}]
    Does the alarm group lie within the Smu_Standby domain?
    [/cover] */
    if(((uint32)AlarmGroup <= SMU_STDBY_END_ALARM_GROUP) &&
        ((uint32)AlarmGroup >= SMU_STDBY_START_ALARM_GROUP))
    {
      /* [cover parentID={065B6383-679D-4803-BB33-E3897B42D065}]
      Is Smu_Stdby disabled?
      [/cover] */
      #if(SMU_STANDBY_SWITCH == STD_OFF)
      /* [cover parentID={BF646E1F-746A-4b42-8E43-40CD820DEE11}]
      Report error SMU_E_STDBY_DISABLED
      [/cover] */
      Smu_lReportError(SMU_SID_GET_ALARM_STATUS, \
                       SMU_E_STDBY_DISABLED);
      /* [cover parentID={71CD9897-7826-4033-AF48-968D62D9510F}]
      Is Smu_Standby enabled?
      [/cover] */
      #else
      RetVal = E_OK;
      #endif
    }
    /* [cover parentID={2A63BDB4-C7CD-4fa2-9DA0-0AFD62B3F1C3}]
    Is the alarm group within Smu_core?
    [/cover] */
    else if((uint32)AlarmGroup < SMU_CORE_TOTAL_ALARM_GROUPS)
    {
      /* [cover parentID={B1B69236-C2A3-41c0-B112-1BC57F7A04C2}]
      Set Result as E_OK
      [/cover] */
      RetVal = E_OK;
    }
    else
    {
      /* [cover parentID={B4DBC5F1-9DB4-40bc-B343-B0EAD21DBDD7}]
      Report error SMU_E_PARAM_GROUP
      [/cover] */
      Smu_lReportError(SMU_SID_GET_ALARM_STATUS, SMU_E_PARAM_GROUP);
    }
  }
  else
  {
    /* [cover parentID={083A65A3-4417-4965-B3FF-70F36415C1F2}]
    Report error SMU_E_UNINIT
    [/cover] */
    Smu_lReportError(SMU_SID_GET_ALARM_STATUS, SMU_E_UNINIT);
  }
  /* [cover parentID={E439BFE5-CE15-45b3-BA83-29351974DD0E}]
  Have all checks passed ?
  [/cover] */
  if(RetVal == (Std_ReturnType)E_OK)
  #endif
  {
    /* [cover parentID={47EC3FF4-EB82-4a0b-8E49-C1444E2D31D5}]
    Standby mode is enabled
    [/cover] */
    #if(SMU_STANDBY_SWITCH == STD_ON)
    /* [cover parentID={3968BF57-B40B-4fe5-B661-AC653ABC913C}]
    Check if the alarm group is SMU Alarm Group 20
    [/cover] */
    if(AlarmGroup == SMU_ALARM_GROUP20)
    {
      /* [cover parentID={1B1819B7-BC1E-4243-B93F-F45C897AA50A}]
      Read the alarm status from Alarm group 20
      [/cover] */
      *AlarmStatus = (uint32)(PMS_AG_STDBY0.U  & SMU_GROUP20_POS);
      RetVal = E_OK;
    }
    /* [cover parentID={D0035E5A-6D90-46a5-AB1A-3A00D47B96BF}]
    Check if alarm group is SMU Alarm Group 21
    [/cover] */
    else if(AlarmGroup == SMU_ALARM_GROUP21)
    {
      /* [cover parentID={E540C914-02E2-4577-B72D-2C82C9A81A4E}]
      Read the alarm status from Alarm group 21
      [/cover] */
      *AlarmStatus = (uint32)(PMS_AG_STDBY1.U);
      RetVal = E_OK;
    }
    else
    #endif
    {
      /* [cover parentID={791310BD-E80F-4688-A22E-788D2BC3C178}]
      Is Safety and DET disabled?
      [/cover] */
      #if(SMU_DEV_ERROR_DETECT == STD_OFF) && \
      (SMU_SAFETY_ENABLE == STD_OFF)
      /* [cover parentID={3521AE75-49A7-4820-892B-22963D68A81F}]
      Check if the alarm group is in Smu_core
      [/cover] */
      if((uint32)AlarmGroup < SMU_CORE_TOTAL_ALARM_GROUPS)
      #endif
      {
        /* [cover parentID={DFF0CAFD-0023-47d3-B2CE-08A77DB52C60}]
        Read the alarm status of alarm group in core domain
        [/cover] */
        /*MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between
        pointers of different object types due to SFR access. */
        *AlarmStatus = \
                       (SMU_CORE_ALARM_GROUP->AGStatusReg[AlarmGroup].U);
        RetVal = E_OK;
      }
    }
  }
  /* [cover parentID={A9684859-4987-4c46-8692-6C6E635DD8B8}]
  Return Result
  [/cover] */
  return RetVal;
}

/*******************************************************************************
** Traceability      :[cover parentID={26FB7351-B093-434b-A30E-F9BE2DA12080}] **
**                                                                            **
** Syntax           : Std_ReturnType Smu_GetAlarmDebugStatus                  **
**                    (                                                       **
**                      const Smu_AlarmGroupId AlarmGroup,                    **
**                      uint32* const AlarmStatus                             **
**                    )                                                       **
**                                                                            **
** Description      : The purpose of the API is to provide the alarm status   **
**                      for the requested alarm group from the stored debug   **
**                      registers.It is applicable only for Smu_core.         **
** [/cover]                                                                   **
** Service ID       : 0xB0                                                    **
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
*******************************************************************************/
Std_ReturnType Smu_GetAlarmDebugStatus
(
  const Smu_AlarmGroupId AlarmGroup,
  uint32* const AlarmStatus
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  /*Check if DET or safety is enabled/disabled*/
  /* [cover parentID={32FC3AC5-A77F-4ee3-94C4-B3612F1C2ACF}]
  DET OR Safety Checks ON
  [/cover] */
  #if (SMU_DEV_ERROR_DETECT == STD_ON) || (SMU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={7276793C-5C3E-4274-AF95-154BD0B55B1E}]
  Check if input parameter is NULL pointer
  [/cover] */
  if(AlarmStatus == NULL_PTR)
  {
    /*Report error SMU_E_PARAM_POINTER*/
    /* [cover parentID={60BFF620-261E-4212-9AFF-92A54B88930B}]
    Report error SMU_E_PARAM_POINTER
    [/cover] */
    Smu_lReportError(SMU_SID_GET_ALARM_DEBUG_STATUS, SMU_E_PARAM_POINTER);
  }
  else
  {
    /* [cover parentID={DCB48520-5726-420b-9159-405996BA3254}]
    Is SMU driver initialized?
    [/cover] */
    if(SMU_INITIALIZED == Smu_InitStatus)
    {
      /* [cover parentID={FD90824D-0E45-48cb-A2BA-CF44FA3B5CFE}]
      Is the alarm group and position valid and  in SMU Core Domain ?
      [/cover] */
      if((uint32)AlarmGroup < SMU_CORE_TOTAL_ALARM_GROUPS)
      {
        /* [cover parentID={08C0DEA6-BA13-4ad4-9661-E837B4100F9D}]
        Set Result as E_OK
        [/cover] */
        RetVal = E_OK;
      }
      else
      {
        /* [cover parentID={0840E1C6-C91E-4878-A475-154E2BC817A6}]
        Report error SMU_E_PARAM_GROUP
        [/cover] */
        Smu_lReportError(SMU_SID_GET_ALARM_DEBUG_STATUS, \
                         SMU_E_PARAM_GROUP);
      }
    }
    else
    {
      /* [cover parentID={A2D5DF0E-F90A-46da-A68A-47D30C2F9764}]
      Report error SMU_E_UNINIT
      [/cover] */
      Smu_lReportError(SMU_SID_GET_ALARM_DEBUG_STATUS, \
                       SMU_E_UNINIT);
    }
  }

  /*Check if all checks have passed*/
  /* [cover parentID={7275BB85-A276-43d5-BAEE-4AEC9A02006A}]
  Have all checks passed ?
  [/cover] */
  if(RetVal == (Std_ReturnType)E_OK)
  #endif
  {
    /* [cover parentID={5A0535E5-3863-4352-A8A7-6C0FC4F8A729}]
    Read the alarm debug status from the debug register
    [/cover] */
    /*MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between pointers
    of different object types due to SFR access. */
    *AlarmStatus = (SMU_CORE_ALARM_GROUP->ADStatusReg[AlarmGroup].U);
    RetVal = E_OK;
  }

  /* [cover parentID={7EA7033E-7C78-46d2-AA61-D11684B4A8F2}]
  Return Result
  [/cover] */
  return RetVal;
}

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
** Description      : The purpose of the API is to provide the internal alarm,**
**                    FSP action currently configured for the requested alarm.**
**                                                                            **
** [/cover]                                                                   **
** Service ID       : 0xAB                                                    **
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
*******************************************************************************/
Std_ReturnType Smu_GetAlarmAction
(
  const Smu_AlarmGroupId AlarmGroup,
  const Smu_AlarmIdType AlarmPos,
  Smu_CoreAlarmActionType * const IntAlarmAction,
  Smu_FSPActionType * const FSPAction
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  /* [cover parentID={983EB5DF-90AB-4222-A4C5-86CDD5DD4F72}]
  DET OR Safety Checks ON
  [/cover] */
  #if (SMU_DEV_ERROR_DETECT == STD_ON) || (SMU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={26091F8C-EB32-47b9-9B62-4B30BED39B2F}]
  Check if output parameters are NULL pointers
  [/cover] */
  if((IntAlarmAction == NULL_PTR) || (FSPAction == NULL_PTR))
  {
    /* [cover parentID={3BDB6554-3513-4b70-A6AE-86615EFE9BEA}]
    Report error SMU_E_PARAM_POINTER
    [/cover] */
    Smu_lReportError(SMU_SID_GET_ALARM_ACTION, SMU_E_PARAM_POINTER);
  }
  else
  {
    /*Check if driver is initialized*/
    /* [cover parentID={43BA95D6-E2CA-474d-A350-877B12998FD7}]
    Is the initialization check passed ?
    [/cover] */
    if(SMU_INITIALIZED == Smu_InitStatus)
    {
      /* [cover parentID={B436CFD9-B889-40e5-ABA7-A501256BB06B}]
      Is the alarm group validity check passed ?
      [/cover] */
      if(E_OK == Smu_lAlarmValidCheck(AlarmGroup, AlarmPos,
                                      SMU_SID_GET_ALARM_ACTION))
      {
        /* [cover parentID={5520B822-F05F-486c-9D66-1680B28D1AD1}]
        Set result as E_OK
        [/cover] */
        RetVal = E_OK;
      }
    }
    /* [cover parentID={8D2CE7D2-F1AF-4fe8-8B8F-9C10C29527AA}]
    For all other conditions when ouput parameter is not NULL and registers
    are not locked
    [/cover] */
    else
    {
      /* [cover parentID={8E3ACE08-372A-4172-A6EE-2A8232EF549A}]
      Report error SMU_E_UNINIT
      [/cover] */
      Smu_lReportError(SMU_SID_GET_ALARM_ACTION, SMU_E_UNINIT);
    }
  }

  /* [cover parentID={A04D910F-2EA8-44f6-969A-6938573C304D}]
  Have all checks passed ?
  [/cover] */
  if(RetVal == E_OK)
  #endif
  {
    /* [cover parentID={4DCA642B-2109-4b22-875B-484AE23E744D}]
    Get Alarm Action
    [/cover] */
    RetVal = Smu_lGetAlmAction(AlarmGroup, AlarmPos, IntAlarmAction,
                               FSPAction);
  }
  /* [cover parentID={A7CB4C89-02C8-422b-9BAD-252644F3172C}]
  Return Result
  [/cover] */
  return RetVal;
}

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
** Description      : The purpose of the API is to set the desired alarm      **
**                    action for the group and position specified.            **
**                                                                            **
** [/cover]                                                                   **
** Service ID       : 0xAC                                                    **
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
*******************************************************************************/
Std_ReturnType Smu_SetAlarmAction
(
  const Smu_AlarmGroupId AlarmGroup,
  const Smu_AlarmIdType AlarmPos,
  const Smu_CoreAlarmActionType AlarmAction,
  const Smu_FSPActionType FSPAction
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  /*Check if DET or Safety enabled*/
  /* [cover parentID={A0BE1253-CADE-44de-8E51-9818895C9F1C}]
  DET OR Safety Checks ON
  [/cover] */
  #if (SMU_DEV_ERROR_DETECT == STD_ON) || (SMU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={B412347C-0941-4d84-9070-820DB92269E6}]
  Is the driver initialized and not in failed state?
  [/cover] */
  if(E_OK == Smu_lInitFailedCheck(SMU_SID_SET_ALARM_ACTION))
  {
    /* [cover parentID={F78717BB-983A-4baa-8EC3-62217D3DE5D3}]
    Have all alarm group validation checks passed ?
    [/cover] */
    if(E_OK == Smu_lAlarmValidCheck(AlarmGroup, AlarmPos,
                                    SMU_SID_SET_ALARM_ACTION))
    {
      /* [cover parentID={A1809107-AAF8-4162-B533-5EBE3AA49698}]
      Check if the alarm group is in SMU core and the alarm action is
      outside the range or reserved.
      [/cover] */
      if(((uint32)AlarmGroup < SMU_CORE_TOTAL_ALARM_GROUPS) &&
          ((AlarmAction > SMU_ALARM_ACTION_CPU_RESET) ||
           ((uint8)AlarmAction == (uint8)SMU_ALARM_ACTION_RSVD)))
      {
        /* Invalid AlarmAction */
        /*Report DET SMU_E_INVALID_ALARM_ACTION*/
        /* [cover parentID={F7466CA9-41BE-40ee-8854-234220F15156}]
        Report SMU_E_INVALID_ALARM_ACTION
        [/cover] */
        Smu_lReportError(SMU_SID_SET_ALARM_ACTION, \
                         SMU_E_INVALID_ALARM_ACTION);
      }
      /* [cover parentID={680AC9D3-8EA0-4359-8DCA-74A6922AF808}]
      Is Smu_Stdby enabled?
      [/cover] */
      #if(SMU_STANDBY_SWITCH == STD_ON)
      /* [cover parentID={C615EAC9-2FA2-4431-A55D-D127EEBB49DC}]
      Check if the alarm group is outside SMU core and the alarm action
      is not alarm action none.
      [/cover] */
      else if(((uint8)AlarmAction != (uint8)SMU_ALARM_ACTION_NONE)
              && ((uint32)AlarmGroup > SMU_CORE_TOTAL_ALARM_GROUPS)
             )
      {
        /* [cover parentID={1F665189-CC0E-467a-B0FF-846F2EF736E2}]
        Report Error SMU_E_INVALID_ALARM_ACTION
        [/cover] */
        Smu_lReportError(SMU_SID_SET_ALARM_ACTION, \
                         SMU_E_INVALID_ALARM_ACTION);
      }
      #endif
      /* [cover parentID={18B8AA72-2C12-40a7-BA48-EC4AB8E5E945}]
      Check if SMU configuration registers are permanently locked
      [/cover] */
      else if(Smu_LockState == SMU_LOCKED)
      {
        /* SMU config registers are permanently locked */
        /* [cover parentID={105B18B3-732A-44be-835F-03C730FC6A63}]
        Report Error SMU_E_LOCKED
        [/cover] */
        Smu_lReportError(SMU_SID_SET_ALARM_ACTION, SMU_E_LOCKED);

      }
      /* [cover parentID={DA878D39-2F6B-465e-8724-C07ACDB0B8B4}]
      Check if FSP action is invalid
      [/cover] */
      else if(FSPAction > SMU_FSP_ACTION_MSK)
      {
        /* [cover parentID={89339310-90AB-4f01-AD78-77F36E93A370}]
        Report Error SMU_E_INVALID_ALARM_ACTION
        [/cover] */
        Smu_lReportError(SMU_SID_SET_ALARM_ACTION,
                         SMU_E_INVALID_ALARM_ACTION);
      }
      /* [cover parentID={9EE25F8F-7D29-4b16-8FC8-B18B8DCA2650}]
      For all other conditions when SMU is not locked,alarm group is in
      SMU core,internal and external alarm action is valid or alarm group
      is outside SMU core and alarm action is none .
      [/cover] */
      else
      {
        /* [cover parentID={832AB722-63DD-4a52-9B5A-A8A291691636}]
        Set Result as E_OK
        [/cover] */
        RetVal = E_OK;
      }
    }
  }
  /* [cover parentID={F6F635A7-E448-4e67-AA73-5893A0A9984C}]
  Have all checks passed ?
  [/cover] */
  if(RetVal == E_OK)
  #endif
  {
    /* [cover parentID={299769C5-BFE2-479c-877C-7A0CE4C23B90}]
    Set Alarm Action
    [/cover] */
    RetVal = Smu_lSetAlmAction(AlarmGroup, AlarmPos, AlarmAction, FSPAction);
  }

  /* [cover parentID={8A42093A-3739-4b59-B746-F4C1FDAD7362}]
  Return Result
  [/cover] */
  return RetVal;
}

/*******************************************************************************
** Traceability      : [cover parentID={23EABD59-5B57-464d-A9C3-63C45653C383},**
**                                     {7D727F3C-08FD-42d8-92DC-792B515ACDC4}]**
** Syntax           : Std_ReturnType Smu_ReleaseFSP(void)                     **
**                                                                            **
** Service ID       : 0xB2                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
** [/cover]                                                                   **
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
Std_ReturnType Smu_ReleaseFSP(void)
{
  /* [cover parentID={CB792BB6-1652-44f0-B08D-DC4E3D02E653}]
  Initialize Result to E_NOT_OK
  [/cover] */
  Std_ReturnType RetVal = E_NOT_OK;
  Smu_CoreStateType SmuState;
  uint32 SmuEFRST;
  uint32 CommandStatus;
  uint32 Timeout = 0U;
  /*Check if Safety or DET is enabled*/
  /* [cover parentID={FA347CC1-DB7C-4092-A6F0-774712EA710F}]
  DET OR Safety Checks ON
  [/cover] */
  #if (SMU_DEV_ERROR_DETECT == STD_ON) || (SMU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={D677E59D-3629-4b9e-9B8F-736F7B0A328F}]
  Check if driver is initialized and is not in failed state
  [/cover] */
  RetVal = Smu_lInitFailedCheck(SMU_SID_RELEASE_FSP);
  /*Check if all checks have passed*/
  /* [cover parentID={ECA27BE2-4AED-479c-BCB5-5C016C5E2316}]
  Have all checks passed ?
  [/cover] */
  if(RetVal == E_OK)
  #endif
  {
    /*Read if Fault to RUN state is enabled*/
    /* [cover parentID={756C97F7-DD34-4fed-BD77-70DE4AFB94EF}]
    Read the value of Fault to RUN state Enabled
    [/cover] */
    SmuEFRST = (uint32)(SMU_AGC.B.EFRST);
    /* [cover parentID={74A7A315-5F22-4610-A8DF-111FC94AE59B}]
    Read the SMU state from DBG register
    [/cover] */
    SmuState = (Smu_CoreStateType)(SMU_DBG.B.SSM);
    /* SMU is in START state or (FAULT state with EFRST enabled) */
    /* [cover parentID={E5CF30E9-3B9F-4974-B711-96D4D86B5F81}]
    Is SMU either  in START state or FAULT state with EFRST enabled?
    [/cover] */
    if((SmuState == SMU_START_STATE) || ((SmuState == SMU_FAULT_STATE) &&
       (SmuEFRST == (uint32)SMU_EFRST_ENABLE)))
    {
      /* [cover parentID={65742C32-D390-4a2a-B344-13CD5A75D90A}]
      Enter critical section
      [/cover] */
      /* [cover parentID={FFAA68CC-DFB9-4a4d-8ECD-A9509C305330}][/cover] */
      SchM_Enter_Smu_CmdAccess();
      /*Acquire Spinlock*/
      /* [cover parentID={90C27175-4883-424b-95DB-7ACB95EC0B5E}]
      Acquire Spinlock
      [/cover] */
      Mcal_GetSpinlock(&Smu_CmdLockAddress, SMU_SPINLOCK_TIMEOUT);

      /* Write SMU_ReleaseFSP(0) in CMD register */
      /* [cover parentID={4E7185F1-3699-4bdd-868C-81ADB0E2B802}]
      Give command to release FSP by writing to Command Register
      [/cover] */
      SMU_SFR_RUNTIME_WRITE32(&SMU_CMD.U, (uint32)SMU_RELEASEFSP_COMMAND);


      /* Check if Release FSP command is accepted
      by reading the Status reg*/
      /* [cover parentID={40205E6F-3528-4feb-BD84-616C7E247FAE}]
      Loop till Command Status Change is reflected while reading
      back the status
      [/cover] */
      do
      {
        /* [cover parentID={70AA337B-20A7-4ec4-877B-A3FD91971E92}]
        Read from the Command Status Register
        [/cover] */
        CommandStatus = (uint32)SMU_STS.B.RES;
        Timeout++;
      }
      /* [cover parentID={A9A79892-32AE-4711-B4C4-EEC59AD7693A}]
      Loop till timeout is zero AND status of command is failed
      [/cover] */
      while((Timeout < SMU_CMDSTATUS_TIMEOUT) &&
            (CommandStatus != SMU_COMMAND_SUCCESS));

      /*Release spinlock*/
      /* [cover parentID={FAD61CFF-11D2-4184-9AA4-B3E0B816F1F9}]
      Release Spinlock
      [/cover] */
      Mcal_ReleaseSpinlock(&Smu_CmdLockAddress);

      /* [cover parentID={68A8EF5A-0EDA-496e-BD47-EFB3FFFD2BBE}]
      Exit critical section
      [/cover] */
      SchM_Exit_Smu_CmdAccess();

      /* [cover parentID={C9B4899A-DE24-4012-83BA-2086C0BDEBE0}]
      Is release FSP command accepted?
      [/cover] */
      if(CommandStatus != SMU_COMMAND_SUCCESS)
      {
        /* [cover parentID={378BA7E0-E550-4d52-9294-B0ECE54B0D15}]
        Set Result as E_NOT_OK
        [/cover] */
        RetVal = E_NOT_OK;

        /* [cover parentID={DCD9313F-BB06-4ade-AF10-B1F338BD6ED3}]
        Production Error notification for FSP release failure or success is enabled
        [/cover] */
        #if (SMU_RELEASE_FSP_DEM_NOTIF == \
        SMU_ENABLE_DEM_REPORT)
        /* Set status to passed, when set alarm status fails*/
        /* [cover parentID={30984FBF-7DEF-427b-9E6E-52709C203423}]
        Report failure as Production Error event status
        [/cover] */
        Smu_lReportDemError(SMU_E_RELEASE_FSP_FAILURE, \
                              DEM_EVENT_STATUS_FAILED);
        #endif
      }
      else
      {
        /* [cover parentID={1804B9CC-A6AD-4387-AEF2-F3AB7CEDED36}]
        Set Result as E_OK
        [/cover] */
        RetVal = E_OK;

        /* [cover parentID={BAB7D3D4-AA32-4ddf-B4A4-E3941FDA8E2A}]
        Production Error notification for FSP release failure or success is enabled
        [/cover] */
        #if (SMU_RELEASE_FSP_DEM_NOTIF == \
        SMU_ENABLE_DEM_REPORT)
        /* Set status to passed, when set alarm status is passed*/
        /* [cover parentID={E0E751E4-B2CD-4f16-97B3-F2E31877C8C8}]
        Report success as Production Error event status
        [/cover] */
        Smu_lReportDemError(SMU_E_RELEASE_FSP_FAILURE, \
                              DEM_EVENT_STATUS_PASSED);
        #endif
      }
    }
    else
    {
      /* [cover parentID={C58E3BFE-AC07-4cd0-B4FB-63A3255DA8B2}]
      Set Result as E_NOT_OK
      [/cover] */
      RetVal = E_NOT_OK;
    }
  }
  /* [cover parentID={D4AFD21B-2690-4727-8013-A3C57428BA45}]
  Return Result
  [/cover] */
  return RetVal;
}

/*******************************************************************************
** Traceability     : [cover parentID={CC28E023-9FD7-4f99-BCCC-55D4AFFAADF3}] **
**                                                                            **
** Syntax           : Std_ReturnType Smu_ActivateFSP (void)                   **
**                                                                            **
** Description      : This API activates the FSP to indicate a FAULT state on **
**                    the error pin to the safe state switching device. Also, **
**                    in the SMU START state, activation of FSP is only       **
**                    possible using this API as alarms are NOT processed.    **
**                    Additionally, this is required for the testing of the   **
**                    FSP timing                                              **
**                                                                            **
** [/cover]                                                                   **
** Service ID       : 0xB3                                                    **
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
*******************************************************************************/
Std_ReturnType Smu_ActivateFSP(void)
{

  Std_ReturnType RetVal = E_NOT_OK;
  uint32 Timeout = 0U;
  uint32 CommandStatus;
  /*Check if DET or Safety are enabled*/
  /* [cover parentID={6A9418DE-F72D-4d9a-9C00-B7CECA135400}]
  DET OR Safety Checks ON
  [/cover] */
  #if (SMU_DEV_ERROR_DETECT == STD_ON) || (SMU_SAFETY_ENABLE == STD_ON)
  /*Check if driver is initialized and is not in failed state*/
  /* [cover parentID={A60AE207-9EB8-4218-90E3-F246AC7D6B46}]
  Check if driver is initialized and is not in failed state
  [/cover] */
  RetVal = Smu_lInitFailedCheck(SMU_SID_ACTIVATE_FSP);

  /*Check if all checks have passed*/
  /* [cover parentID={0B91F7A6-1064-4603-ADFC-A30EF703227C}]
  Have all checks passed ?
  [/cover] */
  if(RetVal == E_OK)
  #endif
  {
    /* [cover parentID={309CCDE0-2A40-4046-8582-2B885DFB6718}]
    Enter critical section
    [/cover] */
    /* [cover parentID={FFAA68CC-DFB9-4a4d-8ECD-A9509C305330}][/cover] */
    SchM_Enter_Smu_CmdAccess();
    /*Acquire spinlock*/
    /* [cover parentID={3705F9B1-2A40-4a1b-B334-F24EE4DADFC8}]
    Acquire Spinlock
    [/cover] */
    Mcal_GetSpinlock(&Smu_CmdLockAddress, SMU_SPINLOCK_TIMEOUT);

    /* Activate FSP by Writing into CMD register*/
    /* [cover parentID={B396B44D-A5B0-4c80-8B69-3342AD5C7DB6}]
    Give command to activate FSP by writing to Command Register
    [/cover] */
    SMU_SFR_RUNTIME_WRITE32(&SMU_CMD.U, (uint32)SMU_ACTIVATEFSP_COMMAND );

    /* Check if Activate FSP command is successfully accepted */
    /* [cover parentID={38D25FF8-C7E8-47a8-803E-8FF8EFB7710E}]
    Loop till Command Status Change is reflected while reading back the
    status
    [/cover] */
    do
    {
      /* [cover parentID={1159B80A-4289-4783-B4BD-0CAAC9AA40F2}]
      Read from the Command Status Register
      [/cover] */
      CommandStatus = (uint32)SMU_STS.B.RES;
      Timeout++;
    }
    /* [cover parentID={D225CDB9-A033-4802-8F50-D6784B6F24ED}]
    Loop till timeout is zero AND status of command is failed
    [/cover] */
    while((Timeout < SMU_CMDSTATUS_TIMEOUT) &&
          (CommandStatus != SMU_COMMAND_SUCCESS));

    /*Release spinlock*/
    /* [cover parentID={39EFA903-F17A-4e63-977D-01E14BE495D6}]
    Release spinlock
    [/cover] */
    Mcal_ReleaseSpinlock(&Smu_CmdLockAddress);

    /* [cover parentID={90CB5D3B-9A79-48e9-BC66-C7702F5B763C}]
    Exit critical section
    [/cover] */
    SchM_Exit_Smu_CmdAccess();
    /* [cover parentID={8A7ECE32-264C-448d-A50C-9F3B2844F54A}]
    Is activate FSP command accepted?
    [/cover] */
    if(CommandStatus != SMU_COMMAND_SUCCESS)
    {
      /* [cover parentID={737F09CC-1175-4f8b-88F7-A59370302462}]
      Set Result as E_NOT_OK
      [/cover] */
      RetVal = E_NOT_OK;

      /* [cover parentID={1FC76E12-EEA8-4a2e-A27A-8DC8E1362497}]
      Production Error notification for FSP activation failure or success is enabled
      [/cover] */
      #if (SMU_ACTIVATE_FSP_FAILURE_DEM_NOTIF == SMU_ENABLE_DEM_REPORT)
      /* Raise failure Production Error, when activate FSP fails*/
      /* [cover parentID={ADE66FCE-FAFB-493b-BC41-21261F1C93ED}]
      Report failure as Production Error event status
      [/cover] */
      Smu_lReportDemError(SMU_E_ACTIVATE_FSP_FAILURE,
                            DEM_EVENT_STATUS_FAILED);
      #endif
    }
    else
    {
      /* [cover parentID={1C96DC5B-1B50-44a1-A2A3-263B7AA55184}]
      Set Result as E_OK
      [/cover] */
      RetVal = E_OK;
      /* [cover parentID={BD3CA5C3-951E-4a19-9A9A-BDE9AA8BC8A1}]
      Production Error notification for FSP activation failure or success is enabled
      [/cover] */
      #if (SMU_ACTIVATE_FSP_FAILURE_DEM_NOTIF == SMU_ENABLE_DEM_REPORT)
      /* Raise failure Production Error, when activate FSP fails*/
      /* [cover parentID={594C3C4D-DFC0-487f-90A1-FC58E6687B73}]
      Report success as Production Error event status
      [/cover] */
      Smu_lReportDemError(SMU_E_ACTIVATE_FSP_FAILURE,
                            DEM_EVENT_STATUS_PASSED);
      #endif
    }

  }
  /* [cover parentID={169A7A9E-2A8B-4a6e-88A2-6F1841A7FE41}]
  Return Result
  [/cover] */
  return RetVal;
}

/*******************************************************************************
** Traceability     : [cover parentID={A001457A-1DCC-48c1-9D56-C167B076C012}] **
**                                                                            **
** Syntax           : Std_ReturnType Smu_SetupErrorPin(void)                  **
**                                                                            **
** Description      : This service enables the SMU to control the error pin   **
**                    and hence activate the safe state via the FSP. This API **
**                    switches the error pin from GPIO mode to SMU mode.      **
**                    Only after switching to the SMU mode, SMU can control   **
**                    the error pin (i.e by Alarm, Activate, Release APIs)    **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0xB4                                                    **
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
*******************************************************************************/
Std_ReturnType Smu_SetupErrorPin(void)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint32 ReadPCTL;
  uint32 FSPHWDir;
  uint32 FSPPortEnable;

  /* [cover parentID={F6366B22-5138-44e3-9F7B-9C2AB11FECEC}]
  DET OR Safety Checks ON
  [/cover] */
  #if (SMU_DEV_ERROR_DETECT == STD_ON) || (SMU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={D45E96D1-7415-4bd7-8837-22F9CDC33931}]
  Check if driver is initialized and is not in failed state
  [/cover] */
  RetVal = Smu_lInitFailedCheck(SMU_SID_SET_ERROR_PIN);
  /* [cover parentID={F2C6FE58-5E4F-4453-B4AD-276782FBF220}]
  Is the initialization and driver state check passed?
  [/cover] */
  if(RetVal == E_OK)
  {
    /*Check if configuration registers are permanently locked*/
    /* [cover parentID={67F89F96-F123-4e3a-9884-03C71BE506E2}]
    Is SMU  already locked ?
    [/cover] */
    if(Smu_LockState == SMU_LOCKED)
    {
      /*Report error SMU_E_LOCKED*/
      /* [cover parentID={1F81A925-FDFE-4dd6-9BFE-6F759965EAEB}]
      Report error SMU_E_LOCKED
      [/cover] */
      Smu_lReportError(SMU_SID_SET_ERROR_PIN, SMU_E_LOCKED);
      RetVal = E_NOT_OK;
    }
    /* Check if Error Pin is already setup */
    /* [cover parentID={DF51F979-8A84-45b6-9E65-91BEB0F46F46}]
    Is Error Pin already setup?
    [/cover] */
    else if(Smu_ErrPinStatus == SMU_ERRPIN_SET)
    {
      /* [cover parentID={01286938-A7EB-42f9-B613-EFABFD4D1E45}]
      Set Result as E_NOT_OK
      [/cover] */
      RetVal = E_NOT_OK;
    }
    else
    {
      /* [cover parentID={1A109F76-21FD-49c8-AA39-2FABD45A244E}]
      Set Result as E_OK
      [/cover] */
      RetVal = E_OK;
    }
  }
  /*Check if all checks have passed*/
  /* [cover parentID={1CFE6DFC-F223-4425-8874-BC5F1A9C7114}]
  Have all checks  passed?
  [/cover] */
  if(RetVal == E_OK)
  #endif
  {

    /*Calculate the FSP HW Direction which chooses port direction*/
    /* [cover parentID={BC7F1497-4821-432e-8059-A5E1CA2DA1B2}]
    Calculate the FSP HW Direction which chooses port direction
    [/cover] */
    FSPHWDir = SMU_CORE_FSP0_HWDIR | (SMU_CORE_FSP1_HWDIR << SMU_ALARM_VALID);

    /*Calculate the FSP Port Enable*/
    FSPPortEnable = SMU_CORE_FSP0_PORT_ENABLE | \
                    (SMU_CORE_FSP1_PORT_ENABLE << SMU_ALARM_VALID);

    /*calculate final PCTL mask*/
    ReadPCTL = (FSPHWDir | (FSPPortEnable << SMU_PCTL_HWEN_POS) | \
              ((uint32)SMU_GLITCHFILTER_SCU << (uint32)SMU_PCTL_GF_SCU) | \
              ((uint32)SMU_GLITCHFILTER_SMU_STS << (uint32)SMU_PCTL_GF_STS) | \
              (uint32)SMU_PCTL_MASK);

    /* [cover parentID={206D7F00-F26B-4553-A155-51A957009A9B}]
    Enter critical section
    [/cover] */
    /* [cover parentID={0D20AD6F-7260-4c0d-90C9-531A056367E4}][/cover] */
    SchM_Enter_Smu_DriverAccess();
    /*Acquire spinlock*/
    /* [cover parentID={8CB4FC8A-687C-4ee6-82AE-8B4627DEA1C5}]
    Acquire Spinlock
    [/cover] */
    Mcal_GetSpinlock(&Smu_LockAddress, SMU_SPINLOCK_TIMEOUT);

    /*Unlock the SMU configuration registers*/
    /* [cover parentID={2610EDD8-33E1-42a1-BB71-5A6E13279A1F}]
    Unlock the SMU configuration registers
    [/cover] */
    SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG(&MODULE_SMU.KEYS,  \
        (uint32)SMU_CFG_KEY_UNLOCK);

    /* [cover parentID={7126F98F-6F1D-4ef0-935F-8B514DB3631D}]
    Write the FSP configuration values to setup error pin
    [/cover] */
    SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG( \
        &MODULE_SMU.PCTL, (uint32)ReadPCTL);

    /* After configuration set temporary lock of SMU configuration */
    /* [cover parentID={0A8016E8-EA75-41b3-AA84-369F0C02677E}]
    Set temporary lock on SMU configuration
    [/cover] */
    SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG( \
        &MODULE_SMU.KEYS, (uint32)SMU_CFG_KEY_TEMPLOCK);

    /*Check if Smu_stdby is enabled*/
    /* [cover parentID={784A2D1A-FBDE-49c6-85EA-4C7E14E2981B}]
    SMU standby mode ON
    [/cover] */
    #if(SMU_STANDBY_SWITCH == STD_ON)
    uint32 FSPStdbyPortEnable;
    /*Calculate the FSP[1:0] enable values for Smu_stdby*/
    /* [cover parentID={21B6680F-CC27-4104-B238-593D0C1A8A56}]
    Calculate FSP Port enable for SMU Stand by
    [/cover] */
    FSPStdbyPortEnable = (SMU_STDBY_FSP1_OUTPUT << SMU_STDBY_F1_MSK) \
           | (SMU_STDBY_FSP0_OUTPUT << SMU_STDBY_F0_MSK) | SMU_STDBY_BIT_PROT;

    FSPStdbyPortEnable = PMS_CMD_STDBY.U | FSPStdbyPortEnable;

    /*Write into the CMD SFR to enable PORT*/
    /* [cover parentID={68E792FD-9399-4ac8-954F-C5FD263663BA}]
    Setup the Error Pin in SMU Standby mode
    [/cover] */
    SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG( \
        &MODULE_PMS.CMD_STDBY, (uint32)FSPStdbyPortEnable);

    #endif
    /* [cover parentID={2CE026D0-BE73-409c-B103-9933D776C4A8}]
    Is DET or safety or Init Check API is enabled?
    [/cover] */
    #if ((SMU_DEV_ERROR_DETECT == STD_ON) || \
    (SMU_SAFETY_ENABLE == STD_ON) ||(SMU_INIT_CHECK_API == STD_ON))
    /* Set the Smu_ErrPinStatus global variable SMU_ERRPIN_SET*/
    /* [cover parentID={A90229BE-515A-4f65-A240-056C3C187D35}]
    Set Error Pin Status
    [/cover] */
    Smu_ErrPinStatus = SMU_ERRPIN_SET;
    #endif
    /*Release spinlock*/
    /* [cover parentID={6BB983CA-4C60-485c-BDD8-87EEABB83849}]
    Release spinlock
    [/cover] */
    Mcal_ReleaseSpinlock(&Smu_LockAddress);

    /* [cover parentID={158C78F1-AF94-4735-B773-DD50F410D57D}]
    Exit critical section
    [/cover] */
    SchM_Exit_Smu_DriverAccess();
    RetVal = E_OK;

  }
  /* [cover parentID={D0A0B97A-473A-4504-8D84-B4F57B98BE5D}]
  Return Result
  [/cover] */
  return RetVal;
}

/*******************************************************************************
** Traceability     : [cover parentID={E9D7EA34-BB9E-45f1-8EED-F89C5AA17DA5}] **
**                                                                            **
** Syntax           : Std_ReturnType Smu_ReleaseErrorPin(void)                **
**                                                                            **
** Descripition:      This API switches the error pin from SMU mode           **
**                    to GPIO mode.                                           **
** [/cover]                                                                   **
** Service ID       : 0xB5                                                    **
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
**                    E_NOT_OK - Operation failed eg. Configuration is locked **
*******************************************************************************/
Std_ReturnType Smu_ReleaseErrorPin(void)
{
  Std_ReturnType RetVal = E_NOT_OK;

  /*Check if DET or safety is enabled*/
  /* [cover parentID={24D09745-158B-4cdc-AD8D-EC9087B6685E}]
  DET OR Safety Checks ON
  [/cover] */
  #if (SMU_DEV_ERROR_DETECT == STD_ON) || (SMU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={58684C8D-826C-4745-B85C-EDF7B90DB636}]
  Check if driver is initialized and is not in failed state
  [/cover] */
  RetVal = Smu_lInitFailedCheck(SMU_SID_RELEASE_ERROR_PIN);
  /* Check if SMU is already locked */
  /* [cover parentID={95AA665A-DB8B-4040-B336-766CA6CC8B6C}]
  Has the initialization and driver failed check passed?
  [/cover] */
  if(RetVal == E_OK)
  {
    /* [cover parentID={D28802DC-4556-4788-8A75-7BA61BE84454}]
    Is SMU  already locked ?
    [/cover] */
    if(Smu_LockState == SMU_LOCKED)
    {
      /* [cover parentID={41231000-0D71-4d8c-9007-B21B07AAD18C}]
      Report error SMU_E_LOCKED
      [/cover] */
      Smu_lReportError(SMU_SID_RELEASE_ERROR_PIN, SMU_E_LOCKED);
      /* SMU config registers are permanently locked */
      RetVal = E_NOT_OK;
    }
    /* Check if Error Pin is already released */
    /* [cover parentID={B3554C4B-C7CC-42f9-9915-01166F0606F6}]
    Is Error Pin already released?
    [/cover] */
    else if(Smu_ErrPinStatus == SMU_ERRPIN_NOTSET)
    {
      /* [cover parentID={47F5900E-D93E-426d-820B-F7CEEE2F1333}]
      Set Result as E_NOT_OK
      [/cover] */
      RetVal = E_NOT_OK;
    }
    else
    {
      /* [cover parentID={E706F68B-CBC7-49db-890C-96D30735EA98}]
      Set Result as E_OK
      [/cover] */
      RetVal = E_OK;
    }
  }
  /*Check if all checks have passed*/
  /* [cover parentID={6C67E1AD-AF7D-487b-817B-9A83B6D5ECE3}]
  Have all checks  passed?
  [/cover] */
  if(RetVal == E_OK)
  #endif
  {
    /* [cover parentID={F7DEABC5-71D1-49ef-8F98-130ECAF794DD}]
    Enter critical section
    [/cover] */
    /* [cover parentID={0D20AD6F-7260-4c0d-90C9-531A056367E4}][/cover] */
    SchM_Enter_Smu_DriverAccess();
    /*Acquire spinlock*/
    /* [cover parentID={183A22C8-624C-464f-A880-A0458E3027BB}]
    Acquire Spinlock
    [/cover] */
    Mcal_GetSpinlock(&Smu_LockAddress, SMU_SPINLOCK_TIMEOUT);

    /*Unlock configuration registers*/
    /* [cover parentID={958F8D19-A0B1-4d28-A993-016A979CD695}]
    Unlock the SMU configuration registers
    [/cover] */
    SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG(&MODULE_SMU.KEYS,    \
        (uint32)SMU_CFG_KEY_UNLOCK);

    /* [cover parentID={4E910AFB-FE0F-480b-9E32-79D849BB6B79}]
    Relase Error Pin from SMU mode
    [/cover] */
    SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG(&MODULE_SMU.PCTL,  \
        (uint32)SMU_PCTL_RESET_VAL);

    /* After configuration set temporary lock of SMU configuration */
    /* [cover parentID={15BD79D8-8890-4252-8664-7C99E375D7E7}]
    Set temporary lock on SMU configuration
    [/cover] */
    SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG(&MODULE_SMU.KEYS,   \
        (uint32)SMU_CFG_KEY_TEMPLOCK);

    /*Check if Smu_stdby is enabled*/
    /* [cover parentID={23622706-6D97-4922-AD27-7ED87ED4BD56}]
    SMU standby mode ON
    [/cover] */
    #if(SMU_STANDBY_SWITCH == STD_ON)

    /* [cover parentID={DE86E215-7636-49eb-86DD-2C441153C4AF}]
    Calculate FSP Port enable for SMU Stand by
    [/cover] */
    uint32 FSPStdbyPortEnable = PMS_CMD_STDBY.U & SMU_CMD_FSP_RESET;

    /*Release error pin to GPIO mode*/
    /* [cover parentID={63EDFC55-DBA8-44d2-BB9D-17111AB0CA68}]
    Release the Error Pin in SMU Standby mode
    [/cover] */
    SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG( \
        &MODULE_PMS.CMD_STDBY, (uint32) \
        (FSPStdbyPortEnable | SMU_STDBY_BIT_PROT));

    #endif
    /* [cover parentID={B06B8E6C-53E4-43cd-996F-E6C3059026F4}]
    Is DET or Safety or Init Check API enabled?
    [/cover] */
    #if ((SMU_DEV_ERROR_DETECT == STD_ON) || \
    (SMU_SAFETY_ENABLE == STD_ON) ||(SMU_INIT_CHECK_API == STD_ON))
    /* Set the Smu_ErrPinStatus global variable to SMU_ERRPIN_NOTSET*/
    /* [cover parentID={288FB060-C7AB-42fc-88C5-26A434745EFF}]
    Reset Error Pin Status
    [/cover] */
    Smu_ErrPinStatus = SMU_ERRPIN_NOTSET;
    #endif

    /*Release spinlock*/
    /* [cover parentID={2A52C48F-6BB0-44ab-9C5C-6E4DCDCA8952}]
    Release spinlock
    [/cover] */
    Mcal_ReleaseSpinlock(&Smu_LockAddress);

    /* [cover parentID={666A0CEE-091A-4230-8791-349290D6C5AD}]
    Exit critical section
    [/cover] */
    SchM_Exit_Smu_DriverAccess();
    RetVal = E_OK;

  }

  /* [cover parentID={0AA5591D-968B-4468-8C42-EFAD72A14CF5}]
  Return Result
  [/cover] */
  return RetVal;
}
/*******************************************************************************
** Traceability      :[cover parentID={5DEE019E-6A73-49f3-97B4-93E28844ADE6}] **
**                                                                            **
** Syntax           : Std_ReturnType Smu_RTStop(const uint8 TimerNum )        **
**                                                                            **
** Service ID       : 0xB6                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
** [/cover]                                                                   **
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
Std_ReturnType Smu_RTStop(const uint8 TimerNum )
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint32 Timeout = 0U;
  uint32 CommandStatus = SMU_COMMAND_FAILURE;
  uint32 RTSArray[2];

  /* [cover parentID={0F2F6810-0765-42f6-97A0-EAE6D1EBDD61}]
  DET OR Safety Checks ON
  [/cover] */
  #if (SMU_DEV_ERROR_DETECT == STD_ON) || (SMU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={C9769357-8593-411d-8796-1DEAB6717E56}]
  Check if the input parameter timer index is within the valid range
  [/cover] */
  if(TimerNum >= (uint8)SMU_MAX_RECOV_TIM)
  {
    /* [cover parentID={D1EA75FC-1D12-46d0-89EA-E2A313C1CA2C}]
    Report error SMU_E_INVALID_TIMER
    [/cover] */
    Smu_lReportError(SMU_SID_RTSTOP, SMU_E_INVALID_TIMER);
  }
  else
  {
    /* [cover parentID={DD76A869-D0C7-497d-8653-DE1F62DF1686}]
    Check if driver is initialized and is not in failed state
    [/cover] */
    RetVal = Smu_lInitFailedCheck(SMU_SID_RTSTOP);
  }
  /*Check if all checks have passed*/
  /* [cover parentID={B59C3B01-EB84-480d-9919-222FBC22382A}]
  Have all checks passed ?
  [/cover] */
  if(RetVal == E_OK)
  #endif
  {
    /* [cover parentID={1D9C60D6-C9AC-4b62-979E-D3C695DB50DE}]
    Enter critical section
    [/cover] */
    /* [cover parentID={FFAA68CC-DFB9-4a4d-8ECD-A9509C305330}][/cover] */
    SchM_Enter_Smu_CmdAccess();
    /*Acquire spinlock*/
    /* [cover parentID={578A0BF2-A667-4d68-ABB4-BA1754AC9E86}]
    Acquire Spinlock
    [/cover] */
    Mcal_GetSpinlock(&Smu_CmdLockAddress, SMU_SPINLOCK_TIMEOUT);

    /* Read the Register status */
    RTSArray[0] = SMU_STS.B.RTS0;
    RTSArray[1] = SMU_STS.B.RTS1;

    /* [cover parentID={A1B0C76F-B92C-4ba2-80A0-BED65F092F16}]
    Is the recovery timer already stopped?
    [/cover] */
    if(RTSArray[TimerNum & SMU_ALARM_VALID] == SMU_ALARM_VALID)
    {
      /* Write CMD for Stop Recovery Timer */
      /* [cover parentID={C369DC35-221E-4466-914B-68FE515F0E2E}]
      Give command to Stop Recovery Timer by writing to Command Register
      [/cover] */
      SMU_SFR_RUNTIME_WRITE32(&SMU_CMD.U, ((uint32)SMU_STOPREC_COMMAND | \
                             ((uint32)TimerNum << SMU_CMD_ARG_BIT_POS))) ;
      /* [cover parentID={6B892884-F37B-411d-9167-026D519520A7}]
      Loop till Command Status Change is reflected while reading back
      the status
      [/cover] */
      do
      {
        /* [cover parentID={3939ABBF-FADC-47e0-8E76-B79B8B5A4C4F}]
        Read from the Command Status Register
        [/cover] */
        CommandStatus = (uint32)SMU_STS.B.RES;
        Timeout++;
      }
      /* [cover parentID={6CEB4F04-18ED-4dc9-ADDA-F0FC5F7586E3}]
      Loop till timeout is zero AND status of command is failed
      [/cover] */
      while((Timeout < SMU_CMDSTATUS_TIMEOUT) &&
            (CommandStatus != SMU_COMMAND_SUCCESS));
    }

    /*Release spinlock*/
    /* [cover parentID={665E7EA4-02BE-409a-9C28-D8D36688AF52}]
    Release Spinlock
    [/cover] */
    Mcal_ReleaseSpinlock(&Smu_CmdLockAddress);
    /* [cover parentID={A7AB34EC-5C84-4c45-A15C-1EBA1D8C5C98}]
    Exit SchM
    [/cover] */
    SchM_Exit_Smu_CmdAccess();

    /* [cover parentID={56CC505D-96AA-4cbc-865B-29EBB2632EFB}]
    Is command to stop Recovery timer accepted?
    [/cover] */
    if(CommandStatus != SMU_COMMAND_SUCCESS)
    {
      /* [cover parentID={7E0CBCE8-B2C8-46c6-A523-F15839F6CFF2}]
      Set Result as E_NOT_OK
      [/cover] */
      RetVal = E_NOT_OK;
      /* [cover parentID={3E308B57-1CFB-449a-AAEE-41C9FDCF4D44}]
      Production Error notification for stop recovery timer command failure or
      success is enabled
      [/cover] */
      /* [cover parentID={3D1FDAEF-C113-4ebd-9D5F-34D4D373547A}]
      Is Production Error notification for stop recovery timer command failure or
      success enabled?
      [/cover] */
      #if (SMU_RT_STOP_FAILURE_DEM_NOTIF == SMU_ENABLE_DEM_REPORT)
      /* Raise failure Production Error, when activate FSP fails*/
      /* [cover parentID={224E8842-8CFF-4ced-8745-0122FD78A720}]
      Report failure as Production Error event status
      [/cover] */
      Smu_lReportDemError(SMU_E_RT_STOP_FAILURE, \
                            DEM_EVENT_STATUS_FAILED);
      #endif
    }
    else
    {
      /* [cover parentID={C38567F4-AD33-4762-A2C6-A1D697541795}]
      Set Result as E_OK
      [/cover] */
      RetVal = E_OK;
      /* [cover parentID={D74196F1-570B-43da-BB09-D98ADB83B824}]
      Production Error notification for stop recovery timer command failure or
      success is enabled
      [/cover] */
      /* [cover parentID={C4488086-77F0-43d5-9CC1-BDD69B502C84}]
      Is Production Error notification for stop recovery timer command failure or
      success enabled?
      [/cover] */
      #if (SMU_RT_STOP_FAILURE_DEM_NOTIF == SMU_ENABLE_DEM_REPORT)
      /* Raise failure Production Error, when activate FSP fails*/
      /* [cover parentID={A1982512-8307-4d4d-BDE2-987B5FBE2055}]
      Report success as Production Error event status
      [/cover] */
      Smu_lReportDemError(SMU_E_RT_STOP_FAILURE, \
                            DEM_EVENT_STATUS_PASSED);
      #endif
    }
  }
  /* [cover parentID={CB00C76A-3A20-44a2-A2CE-C9B84A20EE22}]
  Return Result
  [/cover] */
  return RetVal;
}

/*******************************************************************************
** Traceability      :[cover parentID={F7F8E849-20E0-413d-B603-B55F711DF221}] **
**                                                                            **
** Syntax           : Std_ReturnType Smu_GetRTMissedEvent                     **
**                    (                                                       **
**                      const uint8 TimerNum,                                 **
**                      boolean* const EventMissed                            **
**                    )                                                       **
**                                                                            **
** Description      : The purpose of the API is to know if any alarms         **
**                    requiring the requested recovery timer was SET while    **
**                    the recovery timer was running.                         **
** [/cover]                                                                   **
** Service ID       : 0xB7                                                    **
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
*******************************************************************************/
Std_ReturnType Smu_GetRTMissedEvent
(
  const uint8 TimerNum,
  boolean* const EventMissed
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint32 kTimMissEventPos[2] = {(uint32)SMU_RT0_MISSED_EVENT,
                                (uint32)SMU_RT1_MISSED_EVENT};
  uint32 TimerMissEvent;

  /*Check if DET or Safety is enabled*/
  /* [cover parentID={57DC994B-9EC6-4e73-A4B3-45CB90931884}]
  DET OR Safety Checks ON
  [/cover] */
  #if (SMU_DEV_ERROR_DETECT == STD_ON) || (SMU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={751CDA57-9BE3-4d8d-B8D1-5D8EB15DD4D5}]
  Check if the input parameters are not with in the valid range
  [/cover] */
  if(TimerNum >= (uint8)SMU_MAX_RECOV_TIM)
  {
    /* [cover parentID={E7BB49B0-3668-41d8-8776-2A36BF6AA071}]
    Report error SMU_E_INVALID_TIMER
    [/cover] */
    Smu_lReportError(SMU_SID_GET_RT_MISSEDEVENT, SMU_E_INVALID_TIMER);
  }
  /* [cover parentID={DC08F38B-535A-40a5-BC78-4D5449884EA8}]
  Check if the pointer is NULL
  [/cover] */
  else if(EventMissed == NULL_PTR)
  {
    /* [cover parentID={7942D4CF-F598-4a24-9112-75885EAEAA01}]
    Report error SMU_E_PARAM_POINTER
    [/cover] */
    Smu_lReportError(SMU_SID_GET_RT_MISSEDEVENT, SMU_E_PARAM_POINTER);
  }
  /* [cover parentID={A22577DE-4FDF-4bc8-AC93-4F973626065F}]
  Check if the driver is initialized and not failed?
  [/cover] */
  else
  {
    /* [cover parentID={5E55A91A-C723-4ebc-A36F-238546D9928F}]
    Return the value of Smu_lInitFailedCheck
    [/cover] */
    RetVal = Smu_lInitFailedCheck(SMU_SID_GET_RT_MISSEDEVENT);
  }

  /*Check if all checks have passed*/
  /* [cover parentID={71BD5535-5449-4447-AD07-9DECE3C1D6F1}]
  Have all checks passed ?
  [/cover] */
  if(RetVal == E_OK)
  #endif
  {
    /*Read the timer event from status register */
    /* [cover parentID={17725203-995C-4fde-9C78-DD496E52E0E7}]
    Read the timer event from status register
    [/cover] */
    /* MISRA2012_RULE_18_1_JUSTIFICATION:Value of Timer is within range */
    TimerMissEvent = (uint32)(SMU_STS.U & kTimMissEventPos[TimerNum]);
    /* [cover parentID={EC9FADAA-884F-4fc3-A8C5-ADE75DB847D0}]
    Is event missed ?
    [/cover] */
    if(TimerMissEvent > 0U)
    {
      /* [cover parentID={83CF7012-FD74-44bc-909D-6D45287D1BB5}]
      Set out parameter as TRUE
      [/cover] */
      *EventMissed = (boolean)TRUE;
    }
    else
    {
      /* [cover parentID={BDD7C434-78B3-4ed5-B23C-D54BA73E5C95}]
      Set out parameter as FALSE
      [/cover] */
      *EventMissed = (boolean)FALSE;
    }
    RetVal = E_OK;
  }
  /* [cover parentID={AD3C5099-256E-43b2-B6BA-4F088CC221FF}]
  Return Result
  [/cover] */
  return RetVal;
}

/*******************************************************************************
** Traceability     : [cover parentID={288D8F0D-7CD5-44c2-9DD7-4B5F8A69DE7D}] **
**                                                                            **
** Syntax           : Std_ReturnType Smu_LockConfigRegs(void)                 **
**                                                                            **
** Description      : The purpose of the API is to lock the SMU configuration **
**                    registers to prevent any modification to configuration  **
**                    register content.                                       **
** [/cover]                                                                   **
** Service ID       : 0xB1                                                    **
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
*******************************************************************************/
Std_ReturnType Smu_LockConfigRegs(void)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint32 RtcValueOld;
  uint32 RtcValueNew;
  uint32 AgcValueOld;
  uint32 AgcValueNew;

  /* [cover parentID={56341190-CE4D-4feb-A019-C7235275287B}]
  Is DET or Safety or Init Check enabled?
  [/cover] */
  #if ((SMU_DEV_ERROR_DETECT == STD_ON) || \
  (SMU_SAFETY_ENABLE == STD_ON) ||(SMU_INIT_CHECK_API == STD_ON))
  /* Set Smu_LockState global variable status to SMU_LOCKED*/
  /* [cover parentID={44BC3D81-B43D-4e43-A141-F3918AA20F6B}]
  Set SMU Locked state as SMU Locked
  [/cover] */
  Smu_LockState = SMU_LOCKED;
  #endif

  /*Check if DET or Safety is enabled*/
  /* [cover parentID={2FC1CAF1-C2FB-4dc5-B9A8-24E3CAD5F4BF}]
  DET OR Safety Checks ON
  [/cover] */
  #if (SMU_DEV_ERROR_DETECT == STD_ON) || (SMU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={20A3537E-0793-4e96-9C53-C1BF176ED462}]
  Check if driver is initialized and is not in failed state
  [/cover] */
  RetVal = Smu_lInitFailedCheck(SMU_SID_LOCK_CFG_REGISTER);
  /* [cover parentID={8126A0C8-D31D-4b2c-B4B2-EC5BA6258D68}]
  Has the initialization check passed ?
  [/cover] */
  if(RetVal == E_OK)
{
  /* Check if SMU cfg registers is already locked */
  /* [cover parentID={E2D302FC-7B9C-4c80-97C5-BC3C05826C75}]
  Check if SMU cfg registers is already locked
  [/cover] */
  if(SMU_KEYS.B.PERLCK == SMU_CFG_PERLCK_VALUE)
    {
      /*Report error SMU_E_LOCKED*/
      /* [cover parentID={E861B2FF-3E09-4043-8755-D2CE6AB0CBE4}]
      Report error SMU_E_LOCKED
      [/cover] */
      Smu_lReportError(SMU_SID_LOCK_CFG_REGISTER, SMU_E_LOCKED);
      RetVal = E_NOT_OK;
    }
  }
  /*Check if all checks have passed*/
  /* [cover parentID={C70F4A31-3C61-4347-A543-9BCEDF98AA6F}]
  Have all checks passed ?
  [/cover] */
  if(RetVal == E_OK)
  #endif
{
  /* Enable permanent lock and enable cfg(temp) lock */
  /* [cover parentID={AA34154C-CA35-4927-BDBD-BDBFF52D7769}]
  Enable permanent lock
  [/cover] */
  SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG(&MODULE_SMU.KEYS,  \
      (uint32)SMU_CFG_PERLCK_ON_CFGLCK_ON);

    /* Try to disable permanent lock and disable cfg(temp) lock.
    Since permanent lock is already done, this instruction shall
    not have any effect on SMU_KEYS register */
    /* [cover parentID={C976F954-DE19-4912-BE06-AEE4FAE45C3B}]
    Disable the permanent lock by writing into lock register. This should
    have no effect
    [/cover] */
    SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG(&MODULE_SMU.KEYS,  \
        (uint32)SMU_CFG_PERLCK_OFF_CFGLCK_OFF);
    /*Check if permanent lock is enabled*/
    /* [cover parentID={67E9BDCE-4063-4e27-AD43-FF903A5D42DF}]
    Is permanent lock enabled ?
    [/cover] */
    if ((uint32)SMU_CFG_PERLCK_ON_CFGLCK_ON == SMU_KEYS.U)
    {
      /* To verify lock mechanism, try to ovewrite couple of SMU
      configuration registers that are controlled by SMU_KEYS
      register and ensure register contents remains unchanged.*/

      /*Store old value of RTC register*/
      /* [cover parentID={FF969715-97D0-4f94-A542-EC82AD4202CF}]
      Store old value of RTC register
      [/cover] */
      RtcValueOld = SMU_RTC.U;

      /*Store old value of AGC register*/
      AgcValueOld = SMU_AGC.U;

      /*Write new value to RTC register*/
      SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG( \
          &MODULE_SMU.RTC, (uint32)((uint32)RtcValueOld ^ \
                                    (uint32)IFX_SMU_RTC_RT0E_MSK));

      /*Write new value to AGC register*/
      SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG( \
          &MODULE_SMU.AGC, (uint32)((uint32)AgcValueOld ^ \
                                    (uint32)IFX_SMU_AGC_IGCS0_MSK));

      /*Compare the old and new values*/
      RtcValueNew = SMU_RTC.U;

      AgcValueNew = SMU_AGC.U;

      /*The values are not written into*/
      /* [cover parentID={54A1C9B2-6A07-48cd-BD60-49BFEFAA55D7}]
      Are the old and new values RTC and AGC register respectively same ?
      [/cover] */
      if ((RtcValueOld == RtcValueNew) && (AgcValueOld == AgcValueNew))
      {
        /* [cover parentID={E1E88324-001C-4b41-B515-C2B518BB0D3A}]
        Set Result As E_OK
        [/cover] */
        RetVal = E_OK;

      }
      else
      {
        /* [cover parentID={E2C5E442-B9E7-4dae-BBF2-5D2B422DE52B}]
        Is DET or Safety or Init Check enabled
        [/cover] */
        #if ((SMU_DEV_ERROR_DETECT == STD_ON) || \
        (SMU_SAFETY_ENABLE == STD_ON) ||(SMU_INIT_CHECK_API == STD_ON))
        /* Set Smu_LockState global variable status SMU_LOCKED*/
        /* [cover parentID={3ED60AB9-C62E-4310-B5A4-57EEE41C2936}]
        Reset SMU Locked state as SMU Unlocked
        [/cover] */
        Smu_LockState = SMU_NOT_LOCKED;
        #endif

        RetVal = E_NOT_OK;
        /* [cover parentID={91877E26-C853-46f4-81B8-8F724C157B8C}]
        Safety Checks ON
        [/cover] */
        #if(SMU_SAFETY_ENABLE == STD_ON)
        /* [cover parentID={BB576F03-F340-4efa-AC3D-22F870762BA7}]
        Report safety error SMU_E_SF_CFG_LOCKED_FAILURE
        [/cover] */
        Mcal_ReportSafetyError(SMU_MODULE_ID, SMU_MODULE_INSTANCE, \
                     SMU_SID_LOCK_CFG_REGISTER, SMU_E_SF_CFG_LOCKED_FAILURE);
        #endif
      }
    }
    else
    {
      /* [cover parentID={2D75511A-3535-4e53-90D8-2912A222A20D}]
      Is DET or Safety or Init Check is enabled?
      [/cover] */
      #if ((SMU_DEV_ERROR_DETECT == STD_ON) || \
      (SMU_SAFETY_ENABLE == STD_ON) ||(SMU_INIT_CHECK_API == STD_ON))
      /* Set Smu_LockState global variable status SMU_LOCKED*/
      /* [cover parentID={F0F44AAB-28CE-4266-8A14-BC83B8B22031}]
      Smu_LockState is set to NOT LOCKED
      [/cover] */
      Smu_LockState = SMU_NOT_LOCKED;
      #endif
      RetVal = E_NOT_OK;
      /* [cover parentID={8D2B17DE-D912-466c-903C-64611C331C33}]
      Is Safety check enabled?
      [/cover] */
      #if(SMU_SAFETY_ENABLE == STD_ON)
      /* [cover parentID={9FF0EEF2-8001-42d1-B2F6-2DB97F144738}]
      Report safety Error SMU_E_SF_CFG_LOCKED_FAILURE
      [/cover] */
      Mcal_ReportSafetyError(SMU_MODULE_ID, SMU_MODULE_INSTANCE, \
                   SMU_SID_LOCK_CFG_REGISTER, SMU_E_SF_CFG_LOCKED_FAILURE);
      #endif
    }
  }
  /* [cover parentID={5A3A4E6F-274D-42ba-B2B5-6CF9F3C0ED8C}]
  Return Result
  [/cover] */
  return RetVal;

}

/*******************************************************************************
** Traceability      :[cover parentID={8B53101F-9B99-48c0-92B7-6792A141297E}] **
**                                                                            **
** Syntax           : Smu_CoreStateType Smu_GetSmuState (void)                **
**                                                                            **
** Description      : The purpose of the API is to provide the current state  **
**                    of the Smu_core. This is referred to as the safety      **
**                    status of the system as all critical faults will cause  **
**                    the SMU to go to the FAIL state as configured by the    **
**                    user.                                                   **
**                                                                            **
** [/cover]                                                                   **
** Service ID       : 0xBA                                                    **
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
*******************************************************************************/
Smu_CoreStateType Smu_GetSmuState(void)
{
  /* [cover parentID={890FB504-8F63-4ba5-9807-48AF30D53148}]
  Set SMU state as undefined
  [/cover] */
  Smu_CoreStateType RetVal = SMU_UNDEFINED_STATE;
  /* [cover parentID={D329C532-79EE-49e1-A1BE-1C79D22FAB90}]
  DET OR Safety Checks ON
  [/cover] */
  #if (SMU_DEV_ERROR_DETECT == STD_ON) || (SMU_SAFETY_ENABLE == STD_ON)

  uint8 lErrorVal = SMU_E_NO_ERR;
  /* [cover parentID={E7F4669A-F3C8-4952-A462-63AB82E491BD}]
  Is driver initialized ?
  [/cover] */
  if(SMU_NOT_INITIALIZED == Smu_InitStatus)
  {
    /*Report error SMU_E_UNINIT*/
    /* [cover parentID={5AD7B51E-98A4-436e-BE8A-C8993619764D}]
    Report error SMU_E_UNINIT
    [/cover] */
    lErrorVal = SMU_E_UNINIT;
    Smu_lReportError(SMU_SID_GET_SMU_STATE, SMU_E_UNINIT);
  }
  /*Check if all checks have passed*/
  /* [cover parentID={9B8E2400-70D6-4950-8FDB-708782F1358D}]
  Have all checks passed ?
  [/cover] */
  if(lErrorVal == SMU_E_NO_ERR)
  #endif
  {
    /* Read SMU state read from DBG register */
    /* [cover parentID={18BE4FA0-2DDD-4cb2-BADE-AB7FED6FAC3D}]
    Read SMU state read from DBG register
    [/cover] */
    RetVal = (Smu_CoreStateType)SMU_DBG.B.SSM;
  }
  /* [cover parentID={DB0E2367-8163-4d19-B590-C803BE7B62ED}]
  Return result
  [/cover] */
  return RetVal;
}


/*******************************************************************************
** Traceability      : [cover parentID={5A7DB499-BDAF-40c7-8E30-DA6DBFFE4B76},**
**                                     {7D727F3C-08FD-42d8-92DC-792B515ACDC4}]**
**                                                                            **
** Syntax           : Std_ReturnType Smu_ActivateRunState (const uint32 Cmd)  **
**                                                                            **
** Description      : This API allows to switch the SMU peripheral into the   **
**                    RUN fault-free state as requested by the caller.        **
**                    The SMU validates the request based                     **
**                    on its own integrity checks (i.e. check of the command  **
**                    value).                                                 **
**                                                                            **
** [/cover]                                                                   **
** Service ID       : 0xBB                                                    **
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
*******************************************************************************/
Std_ReturnType Smu_ActivateRunState(const uint32 Cmd)
{
  Std_ReturnType RetVal = E_NOT_OK;
  Smu_CoreStateType SmuState;
  uint32 CommandStatus;
  uint32 Timeout = 0U;

  /*Check if DET or Safety is enabled*/
  /* [cover parentID={12F363EB-91A5-41c4-9548-3EC8395A7A18}]
  DET OR Safety Checks ON
  [/cover] */
  #if (SMU_DEV_ERROR_DETECT == STD_ON) || (SMU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={F22F5492-E34F-46c7-97AB-28844CAF5DD2}]
  Check if driver is initialized and is not in failed state
  [/cover] */
  RetVal = Smu_lInitFailedCheck(SMU_SID_ACTIVATE_RUN_STATE);
  /*Check if all checks have passed*/
  /* [cover parentID={4BD350BE-B270-493a-9391-5C3CD5DD4272}]
  Have all checks passed ?
  [/cover] */
  if(RetVal == E_OK)
  #endif
  {
    /* Read the SMU state from DBG register */
    /* [cover parentID={BD4CD263-4486-4cca-ADBF-A8B1298F888F}]
    Read the SMU state from DBG register
    [/cover] */
    SmuState = (Smu_CoreStateType)(SMU_DBG.B.SSM);

    /* Check if SMU is in START state */
    /* [cover parentID={1396AC28-A9C2-4ab3-8A13-91142BCB70CB}]
    Is SMU in START state ?
    [/cover] */
    if (SmuState != SMU_START_STATE)
    {
      /* [cover parentID={94F5FEFB-2C19-4ef4-8D7A-D2D5EFE2B009}]
      Set Result as E_NOT_OK
      [/cover] */
      RetVal = E_NOT_OK;
    }
    /* Check if input Cmd is RUN Command */
    /* [cover parentID={3A1D86E6-5308-40b9-9565-C87A4DE72997}]
    Is input Command RUN Command ?
    [/cover] */
    else if (Cmd != (uint32)SMU_RUN_COMMAND)
    {

      /* [cover parentID={FFAA68CC-DFB9-4a4d-8ECD-A9509C305330}]
      [/cover] */
      /* [cover parentID={49930FD6-8BBF-42bf-8C1C-B1353C3E84EA}]
      Enter critical section
      [/cover] */
      SchM_Enter_Smu_CmdAccess();
      /*Acquire spinlock*/
      /* [cover parentID={95D720CA-36D2-4f3b-8075-AF224B8A81F9}]
      Acquire Spinlock
      [/cover] */
      Mcal_GetSpinlock(&Smu_CmdLockAddress, SMU_SPINLOCK_TIMEOUT);

      /* Set SMU in Fault state */
      /* [cover parentID={6B3D0554-0FC3-4cc8-9EC1-C16403919A9F}]
      Activate FSP by Writting SMU_ActivateFSP(0) in CMD register
      [/cover] */
      SMU_SFR_RUNTIME_WRITE32(&SMU_CMD.U, (uint32)SMU_ACTIVATEFSP_COMMAND);
      /* [cover parentID={EA0BC1A6-9E73-4c3a-BECD-412366CCDDC9}]
      Is DET or safety or Init Check is enabled?
      [/cover] */
      #if ((SMU_DEV_ERROR_DETECT == STD_ON) || \
      (SMU_SAFETY_ENABLE == STD_ON) ||(SMU_INIT_CHECK_API == STD_ON))
      /* Set SMU Driver as Failed */
      /* [cover parentID={8490A03A-293C-4c6d-9E2C-AC0A03792132}]
      Set SMU Driver as Failed
      [/cover] */
      Smu_DriverState = SMU_FAILED;
      #endif

      /*Release spinlock*/
      /* [cover parentID={19A82F21-D33B-4d70-BDDA-CD69D9C0B400}]
      Release spinlock
      [/cover] */
      Mcal_ReleaseSpinlock(&Smu_CmdLockAddress);
      /* [cover parentID={92AE513C-8392-4692-97A7-FA93EE547163}]
      Exit critical section
      [/cover] */
      SchM_Exit_Smu_CmdAccess();
      RetVal = E_NOT_OK;
    }
    else
    {

      /* [cover parentID={FFAA68CC-DFB9-4a4d-8ECD-A9509C305330}]
      [/cover] */
      /* [cover parentID={97BC47EC-9219-4541-A85F-B7A584A72CA8}]
      Enter critical section
      [/cover] */
      SchM_Enter_Smu_CmdAccess();
      /*Acquire spinlock*/
      /* [cover parentID={3DD44A7C-4CBE-4edc-9FD8-FD99A17210EE}]
      Acquire Spinlock
      [/cover] */
      Mcal_GetSpinlock(&Smu_CmdLockAddress, SMU_SPINLOCK_TIMEOUT);

      /* [cover parentID={D0B50B95-C6A0-454e-A4AF-23F812E09E56}]
      Write CMD for RUN
      [/cover] */
      SMU_SFR_RUNTIME_WRITE32(&SMU_CMD.U, Cmd );
      /* Check if RUN command is successfully accepted */
      /* [cover parentID={6D252100-645C-404c-90CD-448EDF76C6A0}]
      Loop till timeout is zero AND status of command is failed
      [/cover] */
      do
      {
        /* [cover parentID={2FAF43DC-EA43-4937-99AA-DB6EC9D3CAF3}]
        Read from the Command Status Register
        [/cover] */
        CommandStatus = (uint32)SMU_STS.B.RES;
        Timeout++;
      }

      /* [cover parentID={BF75201C-CECE-4ad7-8E9B-1FBD48A6CE33}]
      Loop till Command Status Change is reflected while reading back the status
      [/cover] */
      while((Timeout < SMU_CMDSTATUS_TIMEOUT) &&
            (CommandStatus != SMU_COMMAND_SUCCESS));

      /*Release spinlock*/
      /* [cover parentID={B635DCD9-F1ED-4f91-8056-3E31467ADE5D}]
      Release spinlock
      [/cover] */
      Mcal_ReleaseSpinlock(&Smu_CmdLockAddress);
      /* [cover parentID={8BD71C19-BBB8-4cd9-B11D-0ADE66F3566C}]
      Exit critical section
      [/cover] */
      SchM_Exit_Smu_CmdAccess();
      /* [cover parentID={D585785A-FA36-42a7-AFB4-93E3A46C9C27}]
      Is RUN command successfully accepted ?
      [/cover] */
      if(CommandStatus != SMU_COMMAND_SUCCESS)
      {
        /* [cover parentID={EF5E54B1-547D-45f3-8A55-224EFCE6D93E}]
        Set Result as E_NOT_OK
        [/cover] */
        RetVal = E_NOT_OK;
        /* [cover parentID={2C74451B-6685-4e18-954E-6FFC494A5FA0}]
        Production Error notification for activating run state failure is enabled
        [/cover] */
        #if (SMU_ACTIVATE_RUN_STATE_FAILURE_DEM_NOTIF == \
        SMU_ENABLE_DEM_REPORT)
        /* Raise failure Production Error, when activate FSP fails*/
        /* [cover parentID={E033B4A3-4191-4b6b-9BFA-6F695F595617}]
        Report failure as Production Error event status
        [/cover] */
        Smu_lReportDemError(SMU_E_ACTIVATE_RUN_STATE_FAILURE,
                              DEM_EVENT_STATUS_FAILED);
        #endif
      }
      else
      {
        /* [cover parentID={1C5C76B7-AB11-44a6-B059-B5D0A254F5D7}]
        Set Result as E_OK
        [/cover] */
        RetVal = E_OK;
        /* [cover parentID={24A73774-D5D6-443e-8B5C-C9E78F3D77D7}]
        Is DET or safety or Init Check is enabled?
        [/cover] */
        #if ((SMU_DEV_ERROR_DETECT == STD_ON) || \
        (SMU_SAFETY_ENABLE == STD_ON) ||(SMU_INIT_CHECK_API == STD_ON))
        /* Set SMU Driver as Failed */
        /* [cover parentID={9AD0DE95-2C40-48fd-9416-5741AD904270}]
        Set SMU Driver state as not failed
        [/cover] */
        Smu_DriverState = SMU_NOT_FAILED;
        #endif
        /* [cover parentID={2C8DADED-8A37-47a3-AE08-60AB6AAA2F95}]
        Production Error notification for activating run state failure or success
        is enabled
        [/cover] */
        #if (SMU_ACTIVATE_RUN_STATE_FAILURE_DEM_NOTIF == \
        SMU_ENABLE_DEM_REPORT)
        /* Raise failure Production Error, when activate FSP fails*/
        /* [cover parentID={C7FA568E-2514-4ae9-A165-AA1359B1FFDB}]
        Report success as Production Error event status
        [/cover] */
        Smu_lReportDemError(SMU_E_ACTIVATE_RUN_STATE_FAILURE,
                              DEM_EVENT_STATUS_PASSED);
        #endif
      }
    }
  }
  /* [cover parentID={AFE9A11E-6BEA-4f95-A78B-C43A014D86C9}]
  Return Result
  [/cover] */
  return RetVal;
}

/*******************************************************************************
** Traceability      : [cover parentID={BCBDE82F-3689-4ef3-BFE4-0691CA2F3262}]**
**                                                                            **
** Syntax           : Std_ReturnType Smu_ActivatePES (void)                   **
**                                                                            **
** Description      : Triggers the activation of the Port Emergency Stop(PES).**
**                   The PES is also directly controlled by the SMU_core when **
**                   entering the FAULT state.                                **
** [/cover]                                                                   **
** Service ID       : 0xB8                                                    **
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
*******************************************************************************/
Std_ReturnType Smu_ActivatePES(void)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint32 Timeout = 0U;
  uint32 CommandStatus;

  /*Check if DET or safety is enabled*/
  /* [cover parentID={B87882C9-049A-416e-91CA-A8456DBBE505}]
  DET OR Safety Checks ON
  [/cover] */
  #if (SMU_DEV_ERROR_DETECT == STD_ON) || (SMU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={E4834DC5-D11D-4240-943B-1B7796C23B0B}]
  Check if driver is initialized and is not in failed state
  [/cover] */
  RetVal = Smu_lInitFailedCheck(SMU_SID_ACTIVATE_PES);

  /*Check if all checks have passed*/
  /* [cover parentID={0938BC91-FA8E-4122-9803-7C1B3B4C71CD}]
  Have all checks passed ?
  [/cover] */
  if(RetVal == E_OK)
  #endif
  {
    /* [cover parentID={82A24743-622D-4719-8D55-E23DEF701DA0}]
    Enter critical section
    [/cover] */
    /* [cover parentID={FFAA68CC-DFB9-4a4d-8ECD-A9509C305330}][/cover] */
    SchM_Enter_Smu_CmdAccess();
    /*Acquire spinlock*/
    /* [cover parentID={296E6FF3-CAB2-4315-8A2C-020C2A6A32DB}]
    Acquire Spinlock
    [/cover] */
    Mcal_GetSpinlock(&Smu_CmdLockAddress, SMU_SPINLOCK_TIMEOUT);

    /* Activate PES by Writing SMU_ActivatePES command in CMD register */
    /* [cover parentID={E2286174-E2C2-4722-83FB-66776A2575C7}]
    Give command to activate PES by writing to Command Register
    [/cover] */
    SMU_SFR_RUNTIME_WRITE32(&SMU_CMD.U, (uint32)SMU_ACTIVATEPES_COMMAND );
    /* Check if Activate PES command is successfully accepted */
    /* [cover parentID={9286C2FB-FB77-4176-9558-8E066FEC9C7B}]
    Loop till Command Status Change is reflected while reading back
    the status
    [/cover] */
    do
    {
      /* [cover parentID={DE2C7680-47CA-41c0-9246-42B958912866}]
      Read from the Command Status Register
      [/cover] */
      CommandStatus = (uint32)SMU_STS.B.RES;
      Timeout++;
    }
    /* [cover parentID={BC5083F4-65E5-4562-B8C4-B26C4383B5CA}]
    Loop till timeout is zero AND status of command is failed
    [/cover] */
    while((Timeout < SMU_CMDSTATUS_TIMEOUT) &&
          (CommandStatus != SMU_COMMAND_SUCCESS));

    /*Release Spinlock*/
    /* [cover parentID={9F9B0CEE-1679-4d1f-94F0-F1AB2F0E432A}]
    Release spinlock
    [/cover] */
    Mcal_ReleaseSpinlock(&Smu_CmdLockAddress);
    /* [cover parentID={FDCD18DB-9B97-4cdf-9B80-7F24EE30AB7B}]
    Exit critical section
    [/cover] */
    SchM_Exit_Smu_CmdAccess();
    /* [cover parentID={B6579E49-5172-4380-9865-37E677F6A710}]
    Is activate PES command accepted?
    [/cover] */
    if(CommandStatus != SMU_COMMAND_SUCCESS)
    {
      /* [cover parentID={A7F69481-8E37-457c-B38E-2B2051D3B9AC}]
      Set Result as E_NOT_OK
      [/cover] */
      RetVal = E_NOT_OK;

      /* [cover parentID={957D91A2-7CEF-40af-80F2-B94A39B9C157}]
      Production Error notification for activating PES failure or success is enabled
      [/cover] */
      #if (SMU_ACTIVATE_PES_FAILURE_DEM_NOTIF == SMU_ENABLE_DEM_REPORT)
      /* Raise failure Production Error, when activate PES fails*/
      /* [cover parentID={57A96D3C-44BB-46ae-8BD6-201B345AB9BA}]
      Report failure as Production Error event status
      [/cover] */
      Smu_lReportDemError(SMU_E_ACTIVATE_PES_FAILURE, \
                            DEM_EVENT_STATUS_FAILED);
      #endif
    }
    else
    {
      /* [cover parentID={8299784B-2730-4e4a-88FA-C11B09FC4E71}]
      Set Result as E_OK
      [/cover] */
      RetVal = E_OK;

      /* [cover parentID={25A467F0-66D6-46d7-8FAE-0F54CA635FB7}]
      Production Error notification for activating PES failure or success is enabled
      [/cover] */
      #if (SMU_ACTIVATE_PES_FAILURE_DEM_NOTIF == SMU_ENABLE_DEM_REPORT)
      /* Raise failure Production Error, when activate PES is passed*/
      /* [cover parentID={C4CC54DE-DDF0-4c23-BF69-4FCC8BF38B92}]
      Report success as Production Error event status
      [/cover] */
      Smu_lReportDemError(SMU_E_ACTIVATE_PES_FAILURE, \
                            DEM_EVENT_STATUS_PASSED);
      #endif
    }

  }
  /* [cover parentID={3A752477-ECCB-4359-A7C6-CCB299079280}]
  Return Result
  [/cover] */
  return RetVal;
}

/*******************************************************************************
** Traceability      :[cover parentID={088D792F-9D76-4472-A6C9-741D9C26C61E}] **
**                                                                            **
** Syntax           : Std_ReturnType Smu_CoreAliveTest (void)                 **
**                                                                            **
** Description      : This API provides the means to execute the Smu_CoreAlive**
**                  command which checks the Smu_core_alive signal. the       **
**                  Smu_stdby has to remain enabled to execute this command.  **
** [/cover]                                                                   **
** Service ID       : 0xBD                                                    **
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
*******************************************************************************/
Std_ReturnType Smu_CoreAliveTest(void)
{
  /* [cover parentID={1D25BBAF-50C8-4453-836D-F95C510C7AFA}]
  Initialize Result to E_NOT_OK
  [/cover] */
  Std_ReturnType RetVal = E_NOT_OK;

  /*Check if Smu_stdby is enabled*/
  /* [cover parentID={B3F6C832-5FE7-4b81-92E4-F087EDB0FD70}]
  Is Smu_Standby is ON?
  [/cover] */
  #if(SMU_STANDBY_SWITCH == STD_ON)
  uint32 CommandStatus;
  uint32 Timeout = 0U;
  Smu_CoreStateType SmuState;

  /*Check if DET or Safety check is enabled*/
  /* [cover parentID={832D864E-16DD-4c91-A5D9-55D3B02350B1}]
  DET OR Safety Checks ON
  [/cover] */
  #if (SMU_DEV_ERROR_DETECT == STD_ON) || \
  (SMU_SAFETY_ENABLE == STD_ON)

  /*Check if driver is initialized and driver state not failed*/
  /* [cover parentID={47CE4A0A-30AC-4704-B630-4434A4E4C391}]
  Check if driver is initialized and is not in failed state
  [/cover] */
  RetVal = Smu_lInitFailedCheck(SMU_SID_CORE_ALIVE_TEST);

  /*Check if all checks have passed*/
  /* [cover parentID={123F652B-AC22-4126-83F8-61FAD0F72892}]
  Have all checks passed ?
  [/cover] */
  if(RetVal == E_OK)
  #endif
  {
    /* Read the SMU state from DBG register */
    /* [cover parentID={D473B8B1-DB1E-45a7-8223-F3224E4F04B6}]
    Read the SMU state from DBG register
    [/cover] */
    SmuState = (Smu_CoreStateType)(SMU_DBG.B.SSM);

    /* Check if SMU is in START state */
    /* [cover parentID={E976F1C5-9E79-4a87-BC75-A3EC1B486911}]
    Is SMU in START state ?
    [/cover] */
    if (SmuState == SMU_START_STATE)
    {
      /* [cover parentID={472F72D5-FD07-4300-9103-B179225D6F77}]
      Enter critical section
      [/cover] */
      /* [cover parentID={FFAA68CC-DFB9-4a4d-8ECD-A9509C305330}][/cover] */
      SchM_Enter_Smu_CmdAccess();
      /*Acquire spinlock*/
      /* [cover parentID={ECD3CDFE-4226-4210-811D-F9ABBD3DCABC}]
      Acquire Spinlock
      [/cover] */
      Mcal_GetSpinlock(&Smu_CmdLockAddress, SMU_SPINLOCK_TIMEOUT);

      /* Activate FSP by Writing SMU_AliveTest(0x5) in CMD register */
      /* [cover parentID={01E5C3CB-1684-46e7-B357-67708D410D42}]
      Give command to test if core is alive by writing to Command Register
      [/cover] */
      SMU_SFR_RUNTIME_WRITE32(&SMU_CMD.U, (uint32)(SMU_ALIVETEST_COMMAND \
                              | (SMU_ALIVE_TEST_START << SMU_CMD_ARG_BIT_POS)));

      /* Check if alive test command is successfully accepted */
      /* [cover parentID={DB014A62-0CDF-4a23-8547-B6F7FDF26C2C}]
      Loop till Command Status Change is reflected while reading back
      the status
      [/cover] */
      do
      {
        /* [cover parentID={EE58AFFD-ACD9-4a5f-8CDA-9A8D8C46356F}]
        Read from the Command Status Register
        [/cover] */
        CommandStatus = (uint32)SMU_STS.B.RES;
        Timeout++;
      }
      /* [cover parentID={B2C3C789-9269-4178-BD58-ECE4C27281D2}]
      Loop till timeout is zero AND status of command is failed
      [/cover] */
      while((Timeout < SMU_CMDSTATUS_TIMEOUT) &&
            (CommandStatus != SMU_COMMAND_SUCCESS));

      /* Stop alive test by Writing 0xA in CMD register */
      /* [cover parentID={75F5DECC-400C-4f8f-BE3D-AA09A305B4CC}]
      Stop alive test by writing 0xA in command register
      [/cover] */
      SMU_SFR_RUNTIME_WRITE32(&SMU_CMD.U, (uint32)(SMU_ALIVETEST_COMMAND \
                              | (SMU_ALIVE_TEST_STOP << SMU_CMD_ARG_BIT_POS)));

      /*Release spinlock*/
      /* [cover parentID={53F08F17-7D90-46e9-A105-A090F77A8585}]
      Release spinlock
      [/cover] */
      Mcal_ReleaseSpinlock(&Smu_CmdLockAddress);
      /* [cover parentID={718F058D-6FCF-41bd-A6B5-5BE25D7E87A8}]
      Exit critical section
      [/cover] */
      SchM_Exit_Smu_CmdAccess();
      /* [cover parentID={2B6C2B77-580C-48fd-BA88-14D75051AEF9}]
      Is Alive Test command accepted?
      [/cover] */
      if(CommandStatus != SMU_COMMAND_SUCCESS)
      {
        /* [cover parentID={E935183A-32B7-4bfb-99D2-6D3B0B426BB0}]
        Set Result as E_NOT_OK
        [/cover] */
        RetVal = E_NOT_OK;

        /* [cover parentID={937FA92C-058F-47a0-A89A-7609FAB5327B}]
        Production Error notification for core alive failure is enabled
        [/cover] */
        #if (SMU_CORE_ALIVE_FAILURE_DEM_NOTIF == \
        SMU_ENABLE_DEM_REPORT)
        /* Raise failure Production Error, when activate PES fails*/
        /* [cover parentID={B674A008-F671-49d1-B7A6-953EFBC98C19}]
        Report failure as Production Error event status
        [/cover] */
        Smu_lReportDemError(SMU_E_CORE_ALIVE_FAILURE, \
                              DEM_EVENT_STATUS_FAILED);
        #endif

      }
      else
      {
        /* [cover parentID={1FE06FAF-101E-4f68-8BFA-33F00DCAD33E}]
        Set Result as E_OK
        [/cover] */
        RetVal = E_OK;
        /* [cover parentID={DB7C0CD9-BEA3-41de-AF70-85DB41DFCC77}]
        Production Error notification for core alive failure or success is enabled
        [/cover] */
        #if (SMU_CORE_ALIVE_FAILURE_DEM_NOTIF == \
        SMU_ENABLE_DEM_REPORT)
        /* Raise failure Production Error, when activate PES fails*/
        /* [cover parentID={9B7BF114-143D-47c9-8EDC-31259D96C81B}]
        Report success as Production Error event status
        [/cover] */
        Smu_lReportDemError(SMU_E_CORE_ALIVE_FAILURE, \
                              DEM_EVENT_STATUS_PASSED);
        #endif
      }
    }
    else
    {
      /* [cover parentID={3B47B050-D2C4-4884-833B-0B1423AAE2E1}]
      Set Result as E_NOT_OK
      [/cover] */
      RetVal = E_NOT_OK;
    }
  }
  /*If Smu_stdby is not enabled the command will not execute*/
  /* [cover parentID={B5FEF9E0-F899-4597-937D-6670FA228235}]
  Standby Mode OFF
  [/cover] */
  #else
  /* [cover parentID={627EBBE0-8DED-48f0-AA49-E0CB7EDBF402}]
  DET OR Safety Checks ON
  [/cover] */
  #if(SMU_DEV_ERROR_DETECT == STD_ON)||(SMU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={52752ED3-2432-4c09-990E-C44B5A30EF31}]
  Report error SMU_E_STDBY_DISABLED
  [/cover] */
  Smu_lReportError(SMU_SID_CORE_ALIVE_TEST, SMU_E_STDBY_DISABLED);
  #endif
  #endif

  /* [cover parentID={79828D0E-CFDA-453e-AE34-37424E7F5DEE}]
  Return Result
  [/cover] */
  return RetVal;
}

/*******************************************************************************
** Traceability      :[cover parentID={4A9763EF-63A4-4888-88FD-5E75716ED268}] **
**                                                                            **
** Syntax           : Std_ReturnType Smu_GetAlarmExecutionStatus              **
**                                   (const uint32 AlarmExecStatusReq,        **
**                                    uint32* const AlarmExecStatus)          **
** Description      : The purpose of the API is to retrieve the requested     **
**                    alarm reaction execution status or the alarm event      **
**                    missed result.                                          **
**                                                                            **
** [/cover]                                                                   **
** Service ID       : 0xBE                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : AlarmExecStatusReq:  Requested alarm reaction execution **
**                    status bit or alarm event missed bit                    **
**                                                                            **
** Parameters (out) : AlarmExecStatus: Pointer that stores the alarm execution**
**                    status or the alarm event missed result                 **
**                                                                            **
** Return value     : E_OK: Operation successful that is retrieval of         **
**                    requested alarm reaction execution status or the alarm  **
**                    event missed result is successful.                      **
**                    E_NOT_OK: Operation not successful that is retrieval of **
**                    requested alarm reaction execution status or the alarm  **
**                    event missed result is not successful, for example due  **
**                    to invalid parameters.                                  **
*******************************************************************************/
Std_ReturnType Smu_GetAlarmExecutionStatus
(
  const uint32 AlarmExecStatusReq,
  uint32* const AlarmExecStatus
)
{
  /* [cover parentID={EEE98563-976C-4aa8-B599-959624CFAE3F}]
  Initialize Result to E_NOT_OK
  [/cover] */
  Std_ReturnType RetVal = E_NOT_OK;
  /*Check if DET or Safety check is enabled*/
  /* [cover parentID={389B4610-BF6A-4c60-8E4F-346C15D4F8BE}]
  DET OR Safety Checks ON
  [/cover] */
  #if (SMU_DEV_ERROR_DETECT == STD_ON) || (SMU_SAFETY_ENABLE == STD_ON)

  uint32 AlarmRes = 0U;
  /* [cover parentID={D5FCCD08-6B63-4cf8-B981-5307767C7A67}]
  Check if input parameter is a null pointer
  [/cover] */
  /* [cover parentID={30EE0789-80CC-47e0-B3DC-EF7680D2DA2E}]
  Is the parameter a NULL ponter?
  [/cover] */
  if(AlarmExecStatus != NULL_PTR)
  {
    /* [cover parentID={76562B65-712E-4cf4-A41E-2E725710D275}]
    Check if driver is initialized and is not in failed state
    [/cover] */
    RetVal = Smu_lInitFailedCheck(SMU_SID_GET_ALARM_EXEC_STS);
    /* [cover parentID={F12282A9-0D23-431a-830E-3B5CA0940466}]
    Has driver initialization and state check passed?
    [/cover] */
    if(RetVal == E_OK)
    {
      /* [cover parentID={CBF556F3-202E-4e45-9CC5-1BF8318180C3}]
      Is the alarm reaction execution status bit or alarm event missed bit
      request within a valid range?
      [/cover] */
      if(AlarmExecStatusReq > SMU_ALMEXEC_MSK)
      {
        /* [cover parentID={DD0EF293-538B-4fbf-910D-D3188E16C61B}]
        Report error SMU_E_INVALID_EXECUTION_STATUS
        [/cover] */
        Smu_lReportError(SMU_SID_GET_ALARM_EXEC_STS, \
                         SMU_E_INVALID_EXECUTION_STATUS);
        /* [cover parentID={DF54D2E7-BAEF-4320-B063-23CC8795BC22}]
        Return Result as E_NOT_OK
        [/cover] */
        RetVal = E_NOT_OK;
      }
      else
      {
        /* [cover parentID={2D7CFF7A-B626-45f1-A39C-9674C92F90D3}]
        Check if requested alarm reaction execution status bit or alarm event
        missed bit is reserved
        [/cover] */
        AlarmRes = (uint32)SMU_ALARMEXECSTATUS_VALID & \
                   ((uint32)SMU_ALARM_VALID << (uint32)AlarmExecStatusReq);
        AlarmRes = AlarmRes >> AlarmExecStatusReq;
        /* [cover parentID={60A0115C-884F-474e-8C13-28B96B9E3BA4}]
        Is the requested alarm reaction execution status bit or alarm event
        missed bit reserved?
        [/cover] */
        if(AlarmRes == SMU_ALARM_INVALID)
        {
          /* [cover parentID={7A3B4108-0D70-406f-8CE0-B915E6BE223E}]
          Report error SMU_E_INVALID_EXECUTION_STATUS
          [/cover] */
          Smu_lReportError(SMU_SID_GET_ALARM_EXEC_STS, \
                           SMU_E_INVALID_EXECUTION_STATUS);
          /* [cover parentID={F9783E2D-A2E7-40c7-B51E-9F8D50DD541B}]
          Set result as E_NOT_OK
          [/cover] */
          RetVal = E_NOT_OK;
        }
      }
    }
  }
  else
  {
    /* [cover parentID={18DF0D15-2E02-45bb-8DB4-DA2DA88AEA47}]
    Report error SMU_E_PARAM_POINTER
    [/cover] */
    Smu_lReportError(SMU_SID_GET_ALARM_EXEC_STS, SMU_E_PARAM_POINTER);
  }

  /*Check if all checks have passed*/
  /* [cover parentID={164C7DBC-7A86-465c-9687-DEA2888065D8}]
  Have all checks passed?
  [/cover] */
  if(RetVal == E_OK)
  #endif
  {
    /* [cover parentID={9F870C5A-5499-4c4b-B3FD-5AB72A93871E}]
    Extract alarm reaction execution status or alarm event missed bit
    [/cover] */
    *AlarmExecStatus = ((SMU_AEX.U & ((uint32)SMU_ALARM_VALID <<
                  (uint32)AlarmExecStatusReq)) >> (uint32)AlarmExecStatusReq);
    /* [cover parentID={7D56BEBE-9CF9-44a7-ADFC-306BF4269E43}]
    Set Result as E_OK
    [/cover] */
    RetVal = E_OK;
  }
  /* [cover parentID={5FF7B60E-5FB5-4c20-9D44-B965E931E154}]
  Return result
  [/cover] */
  return RetVal;
}


/*******************************************************************************
** Traceability     : [cover parentID={625BDBDC-549F-4429-9289-E48015B2B9B2}] **
**                                                                            **
** Syntax           : Std_ReturnType Smu_ClearAlarmExecutionStatus            **
**                                   (const uint32 AlarmExecStatusReq)        **
**                                                                            **
** Description      : The purpose of the API is to clear the requested alarm  **
**                    reaction execution status bit or the alarm event missed **
**                    bit.                                                    **
**                                                                            **
** [/cover]                                                                   **
** Service ID       : 0xBF                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : AlarmExecStatusReq: Alarm reaction execution status bit **
**                    or alarm event missed bit to be cleared                 **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK: Operation successful that is requested alarm      **
**                    reaction execution status bit or the alarm event missed **
**                    bit is cleared successfully                             **
**                    E_NOT_OK: Operation not successful that is requested    **
**                    alarm reaction execution status bit or the alarm event  **
**                    missed bit is not cleared successfully, for example due **
**                    to invalid parameters                                   **
*******************************************************************************/
Std_ReturnType Smu_ClearAlarmExecutionStatus
(
  const uint32 AlarmExecStatusReq
)
{
  /* [cover parentID={C20C2C47-DD08-43f1-A48D-F32CBC4F235D}]
  Initialize Result to E_NOT_OK
  [/cover] */
  Std_ReturnType RetVal = E_NOT_OK;
  uint32 StatusClearRes;

  /*Check if DET or Safety check is enabled*/
  /* [cover parentID={35BA1C86-2DBD-4e0f-A8A8-88800A489E83}]
  DET OR Safety Checks ON
  [/cover] */
  #if (SMU_DEV_ERROR_DETECT == STD_ON) || (SMU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={8145195A-F5F9-4214-A1AA-C6562D57AC7C}]
  Check if driver is initialized and is not in failed state
  [/cover] */
  uint32 AlarmRes = 0U;
  RetVal = Smu_lInitFailedCheck(SMU_SID_CLEAR_ALARM_EXEC_STS);
  /* [cover parentID={A4A41D0D-1F39-47ac-960E-3DE8171E2C46}]
  Has driver initialization and state check passed?
  [/cover] */
  if(RetVal == E_OK)
  {
    /* [cover parentID={4D89B29A-146A-42c2-9D92-9E165E6BABD5}]
    Is the alarm reaction execution status bit or alarm event missed bit
    request within a valid range?
    [/cover] */
    if(AlarmExecStatusReq > SMU_ALMEXEC_MSK)
    {
      /* [cover parentID={DFDA3884-9FE9-4472-8E20-730B75FDD01A}]
      Report error SMU_E_INVALID_EXECUTION_STATUS
      [/cover] */
      Smu_lReportError(SMU_SID_CLEAR_ALARM_EXEC_STS, \
                       SMU_E_INVALID_EXECUTION_STATUS);
      /* [cover parentID={B00434B1-107C-4a59-94A0-01CA528CF85D}]
      Set Result as E_NOT_OK
      [/cover] */
      RetVal = E_NOT_OK;
    }
    else
    {
      /* [cover parentID={FBD98AE7-5B57-48d4-B9D9-817A1BADDB9B}]
      Check if requested alarm reaction execution status bit or alarm event
      missed bit is reserved
      [/cover] */
      AlarmRes = (uint32)SMU_ALARMEXECSTATUS_VALID & \
                 ((uint32)SMU_ALARM_VALID << (uint32)AlarmExecStatusReq);
      AlarmRes = AlarmRes >> AlarmExecStatusReq;
      /* [cover parentID={DC296C8F-D593-4ac6-88D9-03655BADC4E6}]
      Is the requested alarm reaction execution status bit or alarm event
      missed bit reserved?
      [/cover] */
      if(AlarmRes == SMU_ALARM_INVALID)
      {
        /* [cover parentID={1C8F23EA-660A-4b20-8A67-F843DF208F20}]
        Report error SMU_E_INVALID_EXECUTION_STATUS
        [/cover] */
        Smu_lReportError(SMU_SID_CLEAR_ALARM_EXEC_STS, \
                         SMU_E_INVALID_EXECUTION_STATUS);
        /* [cover parentID={D2E58440-6E94-47af-AFBF-11E894225065}]
        Set result as E_NOT_OK
        [/cover] */
        RetVal = E_NOT_OK;
      }
    }
  }

  /*Check if all checks have passed*/
  /* [cover parentID={08011079-FB94-4a1b-B166-1C0DD5E03756}]
  Have all checks passed ?
  [/cover] */
  if(RetVal == E_OK)
  #endif
  {
    /* [cover parentID={C7DE04ED-9E3E-4505-BDF8-522B457BEBC3}]
    Read the result of the requested alarm reaction execution status bit or alarm
    event missed bit
    [/cover] */
    StatusClearRes = ((uint32)SMU_ALARM_VALID << AlarmExecStatusReq);

    /* [cover parentID={8133EF9E-D185-465f-8B3B-DECED5EBB598}]
    Update the result to also include corresponding missed event bit, in case,
    the requested bit corresponds to one of the STS bits
    [/cover] */
    /*If AEM bit is requested, then below code will result in ORing
    StatusClearRes with 0.
    This is done to avoid if condition.*/
    StatusClearRes = StatusClearRes | \
                     (((uint32)SMU_ALARM_VALID << SMU_HALF_WORD_OFFSET) \
                      << AlarmExecStatusReq);

    /* [cover parentID={34561FDD-78DB-4165-957E-75A0FE7B76A2}]
    Enter critical section
    [/cover] */
    /* [cover parentID={0D20AD6F-7260-4c0d-90C9-531A056367E4}][/cover] */
    SchM_Enter_Smu_DriverAccess();
    /*Acquire spinlock*/
    /* [cover parentID={D499399E-8050-432d-9BBC-468717D1231A}]
    Acquire Spinlock
    [/cover] */
    Mcal_GetSpinlock(&Smu_LockAddress, SMU_SPINLOCK_TIMEOUT);

    /*Write into the alarm execution staus clear register*/
    /* [cover parentID={DD7776D4-44B9-43c2-8297-0CAE75F1D22F}]
    Clear alarm event missed bit or alarm reaction execution status bit and
    corresponding alarm event missed bit
    [/cover] */
    SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG( \
        &MODULE_SMU.AEXCLR, (uint32)StatusClearRes);

    /*Release the spinlock*/
    /* [cover parentID={E577889A-0851-495f-9CF8-F79FB4C23B6E}]
    Release spinlock
    [/cover] */
    Mcal_ReleaseSpinlock(&Smu_LockAddress);
    /* [cover parentID={0C035A58-62B0-4f4c-8F3C-0650D20842C5}]
    Exit critical section
    [/cover] */
    SchM_Exit_Smu_DriverAccess();
    /* [cover parentID={87ECA555-748E-4179-A049-8AA510415204}]
    Set Result as E_OK
    [/cover] */
    RetVal = E_OK;
  }
  /* [cover parentID={B362009D-EEA3-4ac5-869B-DB946C1BF5ED}]
  Return result
  [/cover] */
  return RetVal;
}


/*******************************************************************************
** Traceability      :[cover parentID={CDC49D92-3240-4011-A48F-65600AECD8EB}] **
**                                                                            **
** Syntax           : Std_ReturnType Smu_RegisterMonitor                      **
**                    (                                                       **
**                      const uint16 * const RegMonPtr,                       **
**                      Smu_SffTestResType * const  RegMonResult              **
**                    )                                                       **
**                                                                            **
** Service ID       : 0xB9                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** [/cover]                                                                   **
** Parameters(in)   : RegMonPtr : Pointer to the SFF test request variable    **
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
Std_ReturnType Smu_RegisterMonitor
(
  const uint16 * const RegMonPtr, Smu_SffTestResType * const  RegMonResult
)
{
  uint8 Index = 0U;
  Std_ReturnType RetVal = (Std_ReturnType)E_NOT_OK;
  uint32 RMCTLVal = 0U;
  uint32 ResStatus;
  uint32 Timeout = 0U;
  uint32 RMSTSVal = 0U;
  /* [cover parentID={BF61C256-7A97-4d61-A528-924776FE4571}]
  DET OR Safety Checks ON
  [/cover] */
  #if (SMU_DEV_ERROR_DETECT == STD_ON) || (SMU_SAFETY_ENABLE == STD_ON)
  /*Check if driver is initialized and driver state not failed*/
  /* [cover parentID={E8898744-63BA-431e-9B7C-5237DEA98867}]
  Check if driver is initialized and is not in failed state
  [/cover] */
  RetVal = Smu_lInitFailedCheck(SMU_SID_REGISTER_MONITORING);
  /* [cover parentID={86560ABE-2634-4887-9CEF-85143DB55157}]
  Is the Result E_OK?
  [/cover] */
  if(RetVal == E_OK)
  {
    /* [cover parentID={E47C0CED-2FF4-46d7-9FDF-2CAE039A3562}]
    Is SMU locked ?
    [/cover] */
    if(SMU_LOCKED == Smu_LockState)
    {
      /*Report error SMU_E_LOCKED*/
      /* [cover parentID={F59AB20B-86EC-4361-B648-5DD47372CEAD}]
      Report error SMU_E_LOCKED
      [/cover] */
      Smu_lReportError(SMU_SID_REGISTER_MONITORING, SMU_E_LOCKED);
      RetVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
      /* [cover parentID={742A4FBB-EF2E-4e59-B42E-12C81551E600}]
      Is the SFF test request pointer or the result pointer NULL?
      [/cover] */
      if((RegMonPtr == NULL_PTR) || (RegMonResult == NULL_PTR))
      {
        /* [cover parentID={F0DD6FD5-229F-42c4-AEBE-03F20A5D1559}]
        Report error SMU_E_PARAM_POINTER
        [/cover] */
        /*Report error SMU_E_PARAM_POINTER*/
        Smu_lReportError(SMU_SID_REGISTER_MONITORING,
                         SMU_E_PARAM_POINTER);
        RetVal = (Std_ReturnType)E_NOT_OK;
      }
    }
  }

  /*Check if all checks have passed*/
  /* [cover parentID={1C5231A1-EA61-41aa-A7E8-CB70516C2F75}]
  Have all checks passed ?
  [/cover] */
  if(RetVal == (Std_ReturnType)E_OK)
  #endif
  {
    /*Set the RMCTL bits according to the tests chosen*/
    /* [cover parentID={B81B29F8-DC33-40ec-879E-887E8088E3FF},
                       {BB923ED4-973C-4afe-8270-CBDD00DA8116}]
      Start SFF tests
    [/cover] */
    /* [cover parentID={9AC2E3B2-0C67-4ae1-8497-024E22F58818}]
    Check if Register Monitor is enabled
    [/cover] */
    for(Index = 0U; (Index < SMU_TOTAL_RMCTL_BITS); Index++)
    {
      /* [cover parentID={6517FAC4-F17A-42e8-B63A-4C286E6A11CF}]
      Check if it is valid RMCTL Bit and Register Monitor is enabled
      [/cover] */
      if(RegMonPtr[Index] == SMU_SFF_TEST_ENABLE)
      {
        /* [cover parentID={C862C55A-1F4F-45a7-B7BF-D7FA2D4CD3FE}]
        Set the value of Register Monitor Control Bit
        [/cover] */
        RMCTLVal = RMCTLVal | ((uint32)SMU_ALARM_VALID << \
                               (uint32)Index);
      }

    }
    /* [cover parentID={43DBC0B0-B738-4d6f-9A40-77D4A4A861D8}]
    Enter critical section
    [/cover] */
    /* [cover parentID={0D20AD6F-7260-4c0d-90C9-531A056367E4}][/cover] */
    SchM_Enter_Smu_DriverAccess();
    /*Acquire spinlock*/
    /* [cover parentID={81DD6662-B00C-448e-97D3-8D2B2D96A8F0}]
    Acquire spinlock
    [/cover] */
    Mcal_GetSpinlock(&Smu_LockAddress, SMU_SPINLOCK_TIMEOUT);

    /*Write Config key to configure the SMU registers. */
    /* [cover parentID={AAFF1DEB-ACC8-4af4-9B3C-59A460A4FBB0}]
    Unlock SMU Registers
    [/cover] */
    SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG( \
        &MODULE_SMU.KEYS, SMU_CFG_KEY_UNLOCK);


    /* [cover parentID={D6D91B36-BC16-4610-B1D9-5B83ECA7D7C8}]
    Set the RMCTL bits according to the tests chosen
    [/cover] */
    SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG( \
        &MODULE_SMU.RMCTL, RMCTLVal);

    /* After configuration set temporary lock of SMU configuration */
    /* [cover parentID={0C311A13-811D-4fb1-A456-CFC0372ACC5E}]
    Temporarily lock SMU Registers
    [/cover] */
    SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG( \
        &MODULE_SMU.KEYS, SMU_CFG_KEY_TEMPLOCK);

    /*Wait until all the active status bits are set or timeout occurs*/
    /* [cover parentID={542C3CE3-A3C6-4f1f-955C-BC8C2E25DD65}]
    Wait until all the active status bits are set or timeout occurs
    [/cover] */
    do
    {
      /* [cover parentID={46A891CB-2FCD-4391-8565-C1B56F7D1D27}]
      Set the value of Register Monitor Control Bit
      [/cover] */
      RMSTSVal = SMU_RMSTS.U;
      Timeout++;
    }
    /* [cover parentID={3B286671-3E8B-4566-860D-057EB2941C6D}]
    Loop till all the active status bits are set or timeout occurs
    [/cover] */
    while ((RMCTLVal != (RMSTSVal & RMCTLVal)) \
           && (Timeout < SFF_RM_TIMEOUT));

    ResStatus = SMU_RMEF.U;

    /*set the RMSTS status bits to 0*/
    /* [cover parentID={135A7830-88CD-4c75-BFE8-E986DC608290}]
    Reset the Register Monitor status bits
    [/cover] */
    SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG( \
        &MODULE_SMU.RMSTS, SMU_RMSTS_RESETVAL);
    /*set the RMEF status bits to 0*/
    /* [cover parentID={63ABACFC-1644-40c2-A90E-A2171D497348}]
    Reset the Register Monitor error flags
    [/cover] */
    SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG( \
        &MODULE_SMU.RMEF, SMU_RMEF_RESETVAL);

    /* [cover parentID={B1EEA932-1E94-456a-A524-396FD5DA3B9B}]
    Unlock the SMU temporary configuration lock
    [/cover] */
    SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG( \
        &MODULE_SMU.KEYS, SMU_CFG_KEY_UNLOCK);

    /*set the RMCTL status bits to 0*/
    /* [cover parentID={9853166E-864B-4445-9E9F-E08CCEE8BC9B}]
    Reset the Register Monitor error flags
    [/cover] */
    SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG( \
        &MODULE_SMU.RMCTL, SMU_RMCTL_RESETVAL);

    /* After configuration set temporary lock of SMU configuration */
    /* [cover parentID={18E8827F-C172-4422-9082-3FFC2C24F4C5}]
    Lock the SMU temporary configuration lock
    [/cover] */
    SMU_LIB_RUNTIME_WRITESAFETYENDINITPROTREG( \
        &MODULE_SMU.KEYS, SMU_CFG_KEY_TEMPLOCK);

    /*Release the spinlock*/
    /* [cover parentID={605A62F7-0193-4276-B430-FB7FF08B0F47}]
    Release Spinlock
    [/cover] */
    Mcal_ReleaseSpinlock(&Smu_LockAddress);
    /* [cover parentID={C42A08F7-2487-49d2-BF2E-9768D23E9223}]
    Exit critical section
    [/cover] */
    SchM_Exit_Smu_DriverAccess();

    /*If timeout error occurs*/
    /* [cover parentID={05B31E40-BBBE-4a77-85B0-32EF858A87D0}]
    Has timeout error occurred ?
    [/cover] */
    if (Timeout >= SFF_RM_TIMEOUT)
    {
      /* Timeout error has occurred */
      /* [cover parentID={2174263F-7BDA-4235-8896-B0CD861927A3}]
      Set Result as E_NOT_OK
      [/cover] */
      RetVal = E_NOT_OK;
      /* [cover parentID={EE57D66A-A772-4f3e-B89A-0978386DF91D}]
      Production Error notification for SFF test failure is enabled
      [/cover] */
      #if(SMU_SFF_TEST_FAILURE_DEM_NOTIF == SMU_ENABLE_DEM_REPORT)
      /* Raise failure Production Error, when clear alarm status fails*/
      /* [cover parentID={0E00500E-341E-46a8-B2A8-66F2F0FD41FB}]
      Report failure as Production Error event status
      [/cover] */
      Smu_lReportDemError(SMU_E_SFF_TEST_FAILURE, \
                            DEM_EVENT_STATUS_FAILED);
      #endif
    }
    else
    {
      /*Write the result into the result array*/
      /* [cover parentID={DB320615-407F-4134-9F4D-A2E21219C98A}]
      Extract the result and write into the result array
      [/cover] */
      for(Index = 0; Index < SMU_TOTAL_RMCTL_BITS; Index++)
      {
        /* [cover parentID={D1B235FB-4744-469a-AFAE-132250D5DEE3}]
        Extract the Register Monitor error flags for particular
        control bit and write into the result array
        [/cover] */
        RegMonResult[Index] = (Smu_SffTestResType)((ResStatus & \
                ((uint32)SMU_ALARM_VALID << (uint32)Index)) >> (uint32)Index);

      }
      RetVal = E_OK;
      /* [cover parentID={75875BF7-730B-4dd6-8906-94726201BC81}]
      Production Error notification for SFF test failure or success is enabled
      [/cover] */
      #if (SMU_SFF_TEST_FAILURE_DEM_NOTIF == SMU_ENABLE_DEM_REPORT)
      /* Raise failure Production Error, when clear alarm status fails*/
      /* [cover parentID={292D5ACD-7DAF-4630-B5D4-2C6C14923AE9}]
      Report success as Production Error event status
      [/cover] */
      Smu_lReportDemError(SMU_E_SFF_TEST_FAILURE, \
                            DEM_EVENT_STATUS_PASSED);
      #endif
    }
  }
  /* [cover parentID={E65887AE-E02F-4e37-8CF2-ECFB032FD79C}]
  Return Result
  [/cover] */
  return RetVal;
}

/* Enable / Disable the use of the function as per Init Check API
enabled/disableds*/
/*[cover parentID={13D694F5-C200-415a-9315-24246544DA9E}] [/cover]*/
#if(SMU_INIT_CHECK_API==STD_ON)
/*******************************************************************************
** Traceability      :[cover parentID={E91BE0ED-EBBE-49de-80D7-1F05348A6D92}] **
**                                                                            **
** Syntax           :Std_ReturnType Smu_InitCheck (const Smu_ConfigType*      **
**                   const ConfigPtr)                                         **
**                                                                            **
** Description      : This API checks the initialization values after SMU is  **
**                    initialized. It should be called after Smu_Init to check**
**                    the initialization values.                              **
**                                                                            **
** [/cover]                                                                   **
** Service ID       : 0xA9                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different cores                           **
**                                                                            **
** Parameters(in)   : ConfigPtr - Pointer to the SMU configuration for        **
**                                  initialization                            **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK - Operation successfully performed                 **
**                    E_NOT_OK - Operation failed                             **
*******************************************************************************/
Std_ReturnType Smu_InitCheck (const Smu_ConfigType* const ConfigPtr)
{
  Std_ReturnType TempErrFlag = E_NOT_OK;
  uint32 Index = 0U;
  uint32 SfrVal;
  uint32 CfgVal;
  volatile uint32 CompareFlag = 0xFFFFFFFFU;

  Std_ReturnType RetVal = E_NOT_OK;
  /* [cover parentID={1BA15EAC-E9D5-45d9-9954-B60C2CCAE746}]
  Is input parameter a NULL pointer?
  [/cover] */
  if(ConfigPtr != NULL_PTR)
  {
    /*Check if driver is initialized*/
    /* [cover parentID={620CA9BE-116B-434d-A6BE-F9AF70588E38}]
    Is driver initialized?
    [/cover] */
    if(SMU_INITIALIZED == Smu_InitStatus)
    {
      /* [cover parentID={AC89776F-909E-4cd7-82F9-CC71AFC01491}]
      Set result as E_OK
      [/cover] */
      RetVal = E_OK;
    }
  }
  /*Check if all checks have passed*/
  /* [cover parentID={CCF354E8-BFE3-428a-ADED-730ED2D3D418}]
  Have all checks passed?
  [/cover] */
  if(RetVal == E_OK)
  {

    /*Compare FSP register value with configuration.
    Update flag as per result*/
    /* [cover parentID={BC0AA302-67FE-4eb2-83F1-70CB6EB9EB1A}]
    Compare the FSP configuration registers for SMU Core with the
    configurations and update the flag as per the result.
    [/cover] */
    SfrVal = (uint32)SMU_FSP.U ;
    CfgVal = (ConfigPtr->FSPCfg | SMU_FSP_RESET_VAL);
    CompareFlag &= ~(SfrVal ^ CfgVal);

    /*Compare RTC register value with configuration.
    Update flag as per result*/
    SfrVal = (uint32)SMU_RTC.U;
    CfgVal = ConfigPtr->RTCCfg;
    CompareFlag &= ~(SfrVal ^ CfgVal);

    /*Compare AGC register value with configuration.
    Update flag as per result*/
    SfrVal = (uint32)SMU_AGC.U;
    CfgVal = ConfigPtr->AGCCfg;
    CompareFlag &= ~(SfrVal ^ CfgVal);

    /*Compare RTAC00 register value with configuration.
    Update flag as per result*/
    SfrVal = (uint32)SMU_RTAC00.U;
    CfgVal = ConfigPtr->RTAC00Cfg;
    CompareFlag &= ~(SfrVal ^ CfgVal);

    /*Compare RTAC01 register value with configuration.
    Update flag as per result*/
    SfrVal = (uint32)SMU_RTAC01.U;
    CfgVal = ConfigPtr->RTAC01Cfg;
    CompareFlag &= ~(SfrVal ^ CfgVal);

    /*Compare RTAC10 register value with configuration.
    Update flag as per result*/
    SfrVal = (uint32)SMU_RTAC10.U;
    CfgVal = ConfigPtr->RTAC10Cfg;
    CompareFlag &= ~(SfrVal ^ CfgVal);

    /*Compare RTAC11 register value with configuration.
    Update flag as per result*/
    SfrVal = (uint32)SMU_RTAC11.U;
    CfgVal = ConfigPtr->RTAC11Cfg;
    CompareFlag &= ~(SfrVal ^ CfgVal);

    /*Compare Smu_stdby CMD register value with configuration.
    Update flag as per result*/
    SfrVal = (uint32)PMS_CMD_STDBY.U ;
    CfgVal = ConfigPtr->AlarmStdbyCfg ;
    CompareFlag &= ~(SfrVal ^ CfgVal);

    /*Compare Smu_stdby FSP group 20 register value with configuration.
    Update flag as per result*/
    SfrVal = (uint32)PMS_AGFSP_STDBY0.U;
    CfgVal = ConfigPtr->AlarmStdbyFspConfig[0];
    CompareFlag &= ~(SfrVal ^ CfgVal);

    /*Compare Smu_stdby FSP group 21 register value with configuration.
    Update flag as per result*/
    SfrVal = (uint32)PMS_AGFSP_STDBY1.U ;
    CfgVal = ConfigPtr->AlarmStdbyFspConfig[1];
    CompareFlag &= ~(SfrVal ^ CfgVal);

    /*Compare alarm cfg register value with configuration.
    Update flag as per result*/
    /* [cover parentID={28924FCC-2F91-4835-886B-8E47A7991C47}]
    Compare the Alarm Group configuration registers for SMU Core
    [/cover] */
    for(Index = 0U; Index < SMU_CORE_TOTAL_ALARM_CONFIG_REG; Index++)
    {
      /* [cover parentID={28924FCC-2F91-4835-886B-8E47A7991C47}]
      Compare the Alarm Group configuration registers for SMU Core
      [/cover] */
      /* [cover parentID={C2FCC7F5-29EB-495c-B427-A9F97C3898E2}]
      Compare the Alarm Group configuration registers for SMU Core
      with the configurations and update the flag as per the result.
      [/cover] */
      /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between a
      pointer of type to pointer of type uint32 is performed for
      continuous array based access of the register. SFR.U based
      access and Uint32* based access would be same because of
      same data width. Advantange is better code.*/
      SfrVal = (uint32)SMU_CORE_ALARM_GROUP->CfgReg[Index].U;
      CfgVal = ConfigPtr->AlarmCoreConfig[Index];
      CompareFlag &= ~(SfrVal ^ CfgVal);
    }

    /*Compare alarm FSP register value with configuration.
    Update flag as per result*/
    /* [cover parentID={AED6A617-DBA0-4295-8B89-26C4FC7BF1D1}]
    Compare FSP configuration register with the configurations and
    update the flag as per the result.
    [/cover] */
    for(Index = 0U; Index < SMU_CORE_TOTAL_ALARM_GROUPS; Index++)
    {
      /* [cover parentID={015FD3E3-7EFD-4ec1-8FE0-2168AB6E9568}]
      Compare the FSP configuration registers for SMU Core
      [/cover] */
      /* MISRA2012_RULE_11_3_JUSTIFICATION: Conversion between a
      pointer of type to pointer of type uint32 is performed for
      continuous array based access of the register. SFR.U based
      access and Uint32* based access would be same because of
      same data width. Advantange is better code.*/
      SfrVal = (uint32)SMU_CORE_ALARM_GROUP->FSPCfgReg[Index].U;
      CfgVal = ConfigPtr->AlarmCoreFspConfig[Index];
      CompareFlag &= ~(SfrVal ^ CfgVal);
    }

    /*Check the global variable status values and SFR values*/
    /* [cover parentID={6D0881CD-8162-4215-B25F-E781AE1B77F3}]
    Are the values of the global variables for error pin, driver status
    and lock status not set,not failed and not locked respectively?
    [/cover] */
    if((Smu_LockState == SMU_NOT_LOCKED) &&
        (Smu_DriverState == SMU_NOT_FAILED) &&
        (Smu_ErrPinStatus == SMU_ERRPIN_NOTSET))
    {
      /* [cover parentID={96EF5704-369F-43f0-A914-082CB48CA65D}]
      Is result of comparison for all global variables and SFRs with
      corresponding configurations positive ?
      [/cover] */
      if(CompareFlag == 0xFFFFFFFFU)
      {
        /* [cover parentID={EF046654-BDB4-4086-B6D0-A78DFDA07F16}]
        Set result of comparison flag as E_OK
        [/cover] */
        TempErrFlag = E_OK;
      }
    }
  }
  /* [cover parentID={7BEFF850-DF0C-4956-B47C-7E5114D0F669}]
  Return Result
  [/cover] */
  return TempErrFlag;
}
#endif

/* Enable / Disable the use of the function as per Version Info API
enabled/disableds*/
#if (SMU_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Traceability      :[cover parentID={0718DB96-C902-43cd-A42E-FC4059BD228D}] **
**                                                                            **
** Syntax           :void Smu_GetVersionInfo(Std_VersionInfoType              **
**                   * const VersionInfoPtr)                                  **
**                                                                            **
** Description      : This function returns the version information of this   **
**                    module. The version information include :               **
**                    Module ID, Vendor ID. Vendor specific version numbers   **
**                    This function is available if the SMU_VERSION_INFO_API  **
**                    is set ON                                               **
**                                                                            **
** [/cover]                                                                   **
** Service ID       : 0xBC                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** [/cover]                                                                   **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out):  VersionInfoPtr - Pointer to store the                   **
**                    version information of this module.                     **
**                                                                            **
** Return value     : None                                                    **
*******************************************************************************/
void Smu_GetVersionInfo(Std_VersionInfoType * const VersionInfoPtr)
{
  /*Check if DET is enabled*/
  /* [cover parentID={8181CA5D-94C5-4207-A800-9E368B1E4EEA}]
  DET Check ON
  [/cover] */
  #if (SMU_DEV_ERROR_DETECT == STD_ON) || (SMU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={3C8A18E2-7169-45d3-AB24-247579C15030}]
  DET Check
  [/cover] */
  /* [cover parentID={DF6CEAD8-4B1D-4abd-BDCA-ECC3632E904B}]
  Check if pointer to location where  the version information should be
  stored is a NULL pointer
  [/cover] */
  if ((VersionInfoPtr) == NULL_PTR)
  {
    /* Report SMU_E_PARAM_POINTER DET if service called with NULL_PTR*/
    /* [cover parentID={EF18141C-BB95-4764-B8C0-6D8CC8851397}]
    Report DET SMU_E_PARAM_POINTER
    [/cover] */
    Smu_lReportError(SMU_SID_GET_VERSION_INFO, SMU_E_PARAM_POINTER);
  }
  else
  #endif
  {
    /* Vendor ID information */
    /* [cover parentID={426C377A-6C94-4bff-AEFF-BE1211513BBA}]
    Extract Vendor ID
    [/cover] */
    ((Std_VersionInfoType*)(VersionInfoPtr))->vendorID = SMU_VENDOR_ID;
    /* Smu module ID information */
    ((Std_VersionInfoType*)(VersionInfoPtr))->moduleID = SMU_MODULE_ID;
    /* Smu module Software major version information */
    ((Std_VersionInfoType*)(VersionInfoPtr))->sw_major_version =
      (uint8)SMU_SW_MAJOR_VERSION;
    /* Smu module Software minor version information */
    ((Std_VersionInfoType*)(VersionInfoPtr))->sw_minor_version =
      (uint8)SMU_SW_MINOR_VERSION;
    /* Smu module Software patch version information */
    ((Std_VersionInfoType*)(VersionInfoPtr))->sw_patch_version =
      (uint8)SMU_SW_PATCH_VERSION;
  }
}
#endif

#define SMU_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Smu_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of Smu_InitStatus
 * before include of memap.h - Accepted deviation in AUTOSAR */
#include "Smu_MemMap.h"

