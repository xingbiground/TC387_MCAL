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
**  FILENAME     : Wdg_17_Scu.c                                               **
**                                                                            **
**  VERSION      : 31.0.0                                                     **
**                                                                            **
**  DATE         : 2023-05-19                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Wdg Driver source file                                     **
**                                                                            **
**  SPECIFICATION(S) : Specification of Watchdog Driver, AUTOSAR Release      **
**                     4.2.2 and 4.4.0                                        **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/* [cover parentID={52B9B0C8-144A-4b01-B59D-98C06AAF42BE}][/cover] */
/* [cover parentID={0802BF45-E6D8-4f10-8A5F-BB56A28BE484}][/cover] */
/* [cover parentID={0B883906-75E4-442d-B282-0DE58B686EAF}][/cover] */

/* [cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]
WDG does not support any callout function
[/cover] */

/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
WDG does not use the memmap section for CONST
[/cover] */
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* [cover parentID={0589C41B-C3FF-449b-ADE8-D063FCD12B58}][/cover] */
/* [cover parentID={ED1C159D-3890-4f04-83AA-F492BE37F64C}][/cover] */
/* [cover parentID={00BA4D93-B04F-4cfe-9AA1-D6EBE774D5D3}][/cover] */

/* [cover parentID={AD915654-E6D7-4e95-B3B3-BE23457F0610}][/cover] */
/* [cover parentID={7969F1AB-D1B4-4206-9D16-F7111A1D6FBB}][/cover] */
/* [cover parentID={D28023D6-E62A-47ec-9372-30DCB730B7EF}][/cover] */
/* [cover parentID={A8939D50-D585-45cc-A6FC-B85172B2E387}][/cover] */
/* [cover parentID={A4A136D7-A6A0-471d-8083-BE5E83AB8B4A}][/cover] */
/* [cover parentID={2B744778-E5A2-4e09-8251-15BE21CF45AD}][/cover] */
/* [cover parentID={F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}][/cover] */

/* Inclusion of Wdg module header file */
#include "Wdg_17_Scu.h"
/* Register definition file for Aurix2G target */
#include "IfxScu_reg.h"
#include "IfxScu_bf.h"

/* MCAL header file containing global macros, type definitions and functions
  needed by all MCAL drivers. */
#include "McalLib.h"

#if(WDG_17_SCU_TRIG_SELECT == WDG_17_SCU_STM_TIMER)
#include "IfxStm_reg.h"
#include "IfxStm_bf.h"
#endif

#include "SchM_Wdg_17_Scu.h"
/* Include Wdg_Cbk File*/
#include "Wdg_17_Scu_Cbk.h"
/*User Mode and Supervisor Mode Macros*/
#if( (WDG_17_SCU_INIT_API_MODE != WDG_17_SCU_MCAL_SUPERVISOR)||\
(WDG_17_SCU_RUNTIME_API_MODE != WDG_17_SCU_MCAL_SUPERVISOR) )
#include "McalLib_OsStub.h"
#endif

#if ((WDG_17_SCU_DISABLE_REJECT_DEM_REPORT == WDG_17_SCU_ENABLE_DEM_REPORT)||\
(WDG_17_SCU_MODE_FAIL_DEM_REPORT == WDG_17_SCU_ENABLE_DEM_REPORT))
/* Mcal_Wrapper header file */
#include "Mcal_Wrapper.h"
#endif
#if(WDG_17_SCU_DEV_ERROR_DETECT==STD_ON)
/* Import of DET functionality */
#include "Det.h"
#endif
#if((WDG_17_SCU_SAFETY_ENABLE==STD_ON))
/* Include Safety Error header definition */
#include "Mcal_SafetyError.h"
#endif


/*******************************************************************************
**                      Imported Compiler Switch Checks                       **
*******************************************************************************/
/* [cover parentID={D55B8CB8-A4EE-4c3e-96B6-93CF70C2A74A}][/cover] */
#ifndef WDG_17_SCU_AR_RELEASE_MAJOR_VERSION
#error "WDG_17_SCU_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

#ifndef WDG_17_SCU_AR_RELEASE_MINOR_VERSION
#error "WDG_17_SCU_AR_RELEASE_MINOR_VERSION is not defined. "
#endif

#ifndef WDG_17_SCU_AR_RELEASE_REVISION_VERSION
#error "WDG_17_SCU_AR_RELEASE_REVISION_VERSION is not defined. "
#endif

#ifndef WDG_17_SCU_SW_MAJOR_VERSION
#error "WDG_17_SCU_SW_MAJOR_VERSION is not defined. "
#endif

#ifndef WDG_17_SCU_SW_MINOR_VERSION
#error "WDG_17_SCU_SW_MINOR_VERSION is not defined. "
#endif

#ifndef WDG_17_SCU_SW_PATCH_VERSION
#error "WDG_17_SCU_SW_PATCH_VERSION is not defined. "
#endif

/* Check for Correct inclusion of headers */
#if ( WDG_17_SCU_SW_MAJOR_VERSION != 20U )
#error "WDG_17_SCU_SW_MAJOR_VERSION does not match. "
#endif

#if ( WDG_17_SCU_SW_MINOR_VERSION != 25U )
#error "WDG_17_SCU_SW_MINOR_VERSION does not match. "
#endif

#if ( WDG_17_SCU_SW_PATCH_VERSION != 0U )
#error "WDG_17_SCU_SW_PATCH_VERSION does not match. "
#endif

#if ( WDG_17_SCU_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION )
#error "WDG_17_SCU_AR_RELEASE_MAJOR_VERSION does not match. "
#endif

#if ( WDG_17_SCU_AR_RELEASE_MINOR_VERSION != MCAL_AR_RELEASE_MINOR_VERSION )
#error "WDG_17_SCU_AR_RELEASE_MINOR_VERSION does not match. "
#endif

#if ( WDG_17_SCU_AR_RELEASE_REVISION_VERSION != MCAL_AR_RELEASE_REVISION_VERSION )
#error "WDG_17_SCU_AR_RELEASE_REVISION_VERSION does not match. "
#endif

#if WDG_17_SCU_INIT_API_MODE  == WDG_17_SCU_MCAL_SUPERVISOR
/* Library APIs  */

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'WDG_LIB_INIT_WRITESAFETYENDINITPROTREG'
 * defined for User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define WDG_LIB_INIT_WRITECPUENDINITPROTREG(RegAdd,Data)    \
                                        Mcal_WriteCpuEndInitProtReg(RegAdd,Data)
/* [cover parentID={1A65EADD-AFD0-4845-B2D2-8257E086DD67}][/cover] */
#else/*WDG_MCAL_USER1 Mode*/

/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'WDG_LIB_INIT_WRITECPUENDINITPROTREG'
 * defined for User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define WDG_LIB_INIT_WRITECPUENDINITPROTREG(RegAdd,Data)      \
                                   MCAL_LIB_WRITECPUENDINITPROTREG(RegAdd,Data)

#endif
/* [cover parentID={1A65EADD-AFD0-4845-B2D2-8257E086DD67}][/cover] */
#if WDG_17_SCU_RUNTIME_API_MODE  == WDG_17_SCU_MCAL_SUPERVISOR
/* Library APIs  */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
* 'WDG_LIB_RUNTIME_WRITECPUENDINITPROTREG'
* defined for User mode support in code.
* No side effects foreseen by violating this MISRA rule. */
#define WDG_LIB_RUNTIME_WRITECPUENDINITPROTREG(RegAdd,Data)       \
                                        Mcal_WriteCpuEndInitProtReg(RegAdd,Data)
/* [cover parentID={1A65EADD-AFD0-4845-B2D2-8257E086DD67}][/cover] */
#else /*WDG_MCAL_USER1 Mode*/
/* Library APIs  */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'WDG_LIB_RUNTIME_WRITECPUENDINITPROTREG'
 * defined for User mode support in code.
 * No side effects foreseen by violating this MISRA rule. */
#define WDG_LIB_RUNTIME_WRITECPUENDINITPROTREG(RegAdd,Data)       \
                                    MCAL_LIB_WRITECPUENDINITPROTREG(RegAdd,Data)

#endif

/*------------------------------------------------------------------------------
                            DET File inclusion
------------------------------------------------------------------------------*/
/* [cover parentID={679E815C-B76C-415e-848B-C4BE1DB973E6}][/cover] */
#if (WDG_17_SCU_DEV_ERROR_DETECT == STD_ON)

#ifndef DET_AR_RELEASE_MAJOR_VERSION
#error "DET_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

#if ( DET_AR_RELEASE_MAJOR_VERSION != 4U )
#error "DET_AR_RELEASE_MAJOR_VERSION does not match. "
#endif

#endif /*End for WDG_17_SCU_DEV_ERROR_DETECT */
/*----------------------------------------------------------------------------*/

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
/* Software counter reset value */
#define WDG_COUNTER_RESET_VALUE         (uint16)(0x00U)

/*Software Reload reset value*/
#define WDG_RELOAD_RESET_VALUE          (uint16)(0x00U)

/* Disable the Watchdog value */
#define WDG_DISABLE_WDT                 (uint8)(0x01U)

/* Masks the 16bit WDT reload value */
#define WDG_MASK_WDTREL                (0xFFFF0000U)

/* Sets the WDTIR bit and enables the watchdog by resetting WDTDR
   bit in WDTCON1 */
#define WDG_SET_WDTIR_RESET_WDTDR      (0x00000004U)

/* Resets the WDTIR bit and enables the watchdog by resetting WDTDR
   bit in WDTCON1 */
#define WDG_RESET_WDTIR_RESET_WDTDR    (0x00000000U)

/* Mask for Watchdog status in WDTSR*/
#define WDG_STATUS_MASK                 (0x0000003CU)

/* This is the reload value which will trigger an almost instant reset */
#define WDG_INSTANT_RESET_RELOAD_VALUE (0xFFFFU) /* 1 tick near reset */

/* Shift value of REL in WDTCPU0CON0 SFR*/
#define WDG_REL_SHIFT_VALUE             (16U)

/* To mask password */
#define WDT_PASS_MASK                  (0x0000FFFCU)

/* Password mask BIT[15:8] */
#define WDT_PASS_UPPER_MASK            (0x0000FF00U)

/* Password mask BIT[7:2] */
#define WDT_PASS_LOWER_MASK            (0x000000FCU)

/* Set LCK and ENDINIT bit in WDTCPUxCON0*/
#define WDT_SETLCK_ENDINIT             (0x00000003U)

/* Timer 1 available */
#define WDG_AVAILABLE_TIMER_CORE_ONE                    (1U)

/* Timer 2 available */
#define WDG_AVAILABLE_TIMER_CORE_TWO                    (2U)

/* Timer 3 available */
#define WDG_AVAILABLE_TIMER_CORE_THREE                  (3U)

/* Timer 4 available */
#define WDG_AVAILABLE_TIMER_CORE_FOUR                   (4U)

/* Timer 5 available */
#define WDG_AVAILABLE_TIMER_CORE_FIVE                   (5U)

#if(WDG_17_SCU_TRIG_SELECT == WDG_17_SCU_STM_TIMER)
#define WDT_TIMEOUT_FACTOR              (1000000U)
#else
/* SLOW mode index */
#define WDG_GTM_INDEX_SLOW_MODE                         (0U)
/* FAST mode index */
#define WDG_GTM_INDEX_FAST_MODE                         (1U)
#endif

/* Register Mapping for WDG */
#define WDG_REGMAP       ((Ifx_SCU_WDTCPU*)(&SCU_WDTCPU0_CON0))

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/
/* [cover parentID={602A1690-219B-4a59-AF74-3B37C6F65C94}] */
/* WDG module core specific status, Global Varibales
 required that are private to Wdg_17_Scu.c */
typedef struct
{
  uint16 Wdg_TimeoutCounter;

  uint16 Wdg_CurrentReloadValue;

  /* Driver Internal State, Assigned Default state: WDG_UNINIT */
  Wdg_17_Scu_StatusType Wdg_17_Scu_DriverState;

  /* Driver current mode from WdgIf_Types.h */
  WdgIf_ModeType Wdg_17_Scu_DriverMode;

} Wdg_17_Scu_CoreStatusType;

/*[/cover] */

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
#define WDG_17_SCU_START_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Wdg_17_Scu_MemMap.h"

/* Function to Access password before accessing ENDINIT registers */
LOCAL_INLINE uint32 Wdg_lAccessPassword(uint32 WdtCon0);

/* Function to Check if  Password Sequencing Or Time Checking is enabled */
LOCAL_INLINE Std_ReturnType Wdg_lCheckPassSeqOrTimeCheck(uint32 CoreId);

/* Function to Modify the ENDINIT registers */
LOCAL_INLINE uint32 Wdg_lReloadModifyAccess(uint16 ReloadValue);

/* Calculate password to be put in the CON0 SFR */
LOCAL_INLINE uint32 Wdg_lModifyAccessPassword(uint32 PasswordAccess);

/*This routine Store the Reload value of the Current Core */ 
LOCAL_INLINE void Wdg_lUpdateWdtRelVal(const uint16 ReloadValue,const uint32 CoreId);

#if (WDG_17_SCU_DISABLE_REJECT_DEM_REPORT == WDG_17_SCU_ENABLE_DEM_REPORT)
static void Wdg_lReportDemError(const Dem_EventIdType EventId, const Dem_EventStatusType EventStatus); 
#endif

#if (WDG_17_SCU_DEV_ERROR_DETECT == STD_ON)||(WDG_17_SCU_SAFETY_ENABLE == STD_ON)
static void Wdg_lReportError(const uint8 ApiId, const uint8 ErrorId);
#endif

/* WDGx initialization */
static void Wdg_lInit(const uint32 CoreId);

/* Function to change mode of WDG. Available modes are WDGIF_OFF_MODE,
 WDGIF_SLOW_MODE and WDGIF_FAST_MODE*/
static Std_ReturnType Wdg_lChangeMode( const WdgIf_ModeType Mode, const uint8 ApiId,
                            const uint32 CoreId); 

/*Function to operate the Service timer in respective WDG mode */
static void Wdg_lStartOrStopTimeEngine(const WdgIf_ModeType Mode,
                             const uint32 CoreId);

#if(WDG_17_SCU_TRIG_SELECT == WDG_17_SCU_STM_TIMER)
/*This function Updates the CMP Register of STM */
static void Wdg_lStmUpdateCmp(const WdgIf_ModeType Mode,
                           const uint32 CoreId);
#endif

/* Function to calculate Timeout counter */
static void Wdg_lTimeoutHandler
(const WdgIf_ModeType Mode, const uint16 timeout, const uint32 CoreId);

/* Function to trigger the Watchdog Hardware cyclically */
static void Wdg_lTrigger(void);

#if ((WDG_17_SCU_DEV_ERROR_DETECT == STD_ON)||(WDG_17_SCU_SAFETY_ENABLE == STD_ON))
/* Funtion to check for DET during Mode Change for WDG */
static Std_ReturnType Wdg_lSetModeDetCheck
(const WdgIf_ModeType Mode, const uint32 CoreId);
#endif

#if ((WDG_17_SCU_DEV_ERROR_DETECT == STD_ON)||(WDG_17_SCU_SAFETY_ENABLE == STD_ON))
/* Funtion to check for DET during WDG Init */
static Std_ReturnType Wdg_lInitDetCheck
(const Wdg_17_Scu_ConfigType* const ConfigPtr,
 const uint32 CoreId);
#endif
/*Function to check if Status Error Flag is enabled*/
static Std_ReturnType Wdg_lCheckOverflowErrorStatusFlag
(const uint32 CoreId);

/*Function to check if Status Error Flag is enabled*/
static Std_ReturnType Wdg_lCheckAccessErrorStatusFlag
(const uint32 CoreId);

#if (WDG_17_SCU_INIT_CHECK_API == STD_ON)
/*Function to check SFR values after initialization*/
static Std_ReturnType Wdg_lSfrInitCheck
(const Wdg_17_Scu_ConfigType* const ConfigPtr,
 const uint32 CoreId,
 const WdgIf_ModeType Mode);

/*Function to check Global variables after initialization*/
static Std_ReturnType Wdg_lVarInitCheck
(const Wdg_17_Scu_ConfigType* const ConfigPtr,
 const uint32 CoreId,
 const WdgIf_ModeType Mode);

#endif

#define WDG_17_SCU_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Wdg_17_Scu_MemMap.h"

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

/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}][/cover] */
#define WDG_17_SCU_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Wdg_17_Scu_MemMap.h"

/* To store the Wdg Driver configuration pointer */
static const Wdg_17_Scu_ConfigType *Wdg_ConfigPtr[WDG_17_SCU_MAX_TIMERS];
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}][/cover] */
#define WDG_17_SCU_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Wdg_17_Scu_MemMap.h"

/*CORE 0 Specific Status Information*/
#if (WDG_17_SCU_CONFIGURED_CORE0 == STD_ON)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
#define WDG_17_SCU_START_SEC_VAR_CLEARED_ASIL_B_CORE0_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Wdg_17_Scu_MemMap.h"

/*Global Status Variable to maintain
core specific information for the CPU Wdg.*/
static Wdg_17_Scu_CoreStatusType Wdg_17_Scu_Core0;
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
#define WDG_17_SCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Wdg_17_Scu_MemMap.h"
#endif
#if (WDG_17_SCU_MAX_TIMERS > WDG_AVAILABLE_TIMER_CORE_ONE)
/*CORE 1 Specific Status Information*/
#if (WDG_17_SCU_CONFIGURED_CORE1 == STD_ON)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
#define WDG_17_SCU_START_SEC_VAR_CLEARED_ASIL_B_CORE1_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Wdg_17_Scu_MemMap.h"

/*Global Status Variable to maintain
core specific information for the CPU Wdg.*/
static Wdg_17_Scu_CoreStatusType Wdg_17_Scu_Core1;
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
#define WDG_17_SCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Wdg_17_Scu_MemMap.h"
#endif
#endif
#if (WDG_17_SCU_MAX_TIMERS > WDG_AVAILABLE_TIMER_CORE_TWO)
/*CORE 2 Specific Status Information*/
#if (WDG_17_SCU_CONFIGURED_CORE2 == STD_ON)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
#define WDG_17_SCU_START_SEC_VAR_CLEARED_ASIL_B_CORE2_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Wdg_17_Scu_MemMap.h"

/*Global Status Variable to maintain
core specific information for the CPU Wdg.*/
static Wdg_17_Scu_CoreStatusType Wdg_17_Scu_Core2;
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
#define WDG_17_SCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Wdg_17_Scu_MemMap.h"

#endif
#endif
#if (WDG_17_SCU_MAX_TIMERS > WDG_AVAILABLE_TIMER_CORE_THREE)
/*CORE 3 Specific Status Information*/
#if (WDG_17_SCU_CONFIGURED_CORE3 == STD_ON)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
#define WDG_17_SCU_START_SEC_VAR_CLEARED_ASIL_B_CORE3_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Wdg_17_Scu_MemMap.h"

/*Global Status Variable to maintain
core specific information for the CPU Wdg.*/
static Wdg_17_Scu_CoreStatusType Wdg_17_Scu_Core3;
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
#define WDG_17_SCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Wdg_17_Scu_MemMap.h"

#endif
#endif
#if (WDG_17_SCU_MAX_TIMERS > WDG_AVAILABLE_TIMER_CORE_FOUR)
/*CORE 4 Specific Status Information*/
#if (WDG_17_SCU_CONFIGURED_CORE4 == STD_ON)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
#define WDG_17_SCU_START_SEC_VAR_CLEARED_ASIL_B_CORE4_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Wdg_17_Scu_MemMap.h"

/*Global Status Variable to maintain
core specific information for the CPU Wdg.*/
static Wdg_17_Scu_CoreStatusType Wdg_17_Scu_Core4;
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
#define WDG_17_SCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Wdg_17_Scu_MemMap.h"

#endif
#endif
#if (WDG_17_SCU_MAX_TIMERS > WDG_AVAILABLE_TIMER_CORE_FIVE)
/*CORE 5 Specific Status Information*/
#if (WDG_17_SCU_CONFIGURED_CORE5 == STD_ON)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
#define WDG_17_SCU_START_SEC_VAR_CLEARED_ASIL_B_CORE5_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Wdg_17_Scu_MemMap.h"

/*Global Status Variable to maintain
core specific information for the CPU Wdg.*/
static Wdg_17_Scu_CoreStatusType Wdg_17_Scu_Core5;
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
#define WDG_17_SCU_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Wdg_17_Scu_MemMap.h"
#endif
#endif
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
#define WDG_17_SCU_START_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Wdg_17_Scu_MemMap.h"

#if(WDG_17_SCU_TRIG_SELECT == WDG_17_SCU_STM_TIMER)
/*Variable to hold STM timer TIM0 value assinged to each core specific WDG */
/* MISRA2012_RULE_19_2_JUSTIFICATION:Union used for register type definition.
 No side effects foreseen by violating this MISRA rule*/
/* MISRA2012_RULE_8_9_JUSTIFICATION: No side effects foreseen by violating 
 * this MISRA rule,as the variable is accessed via pointer by Wdg_lStmUpdateCmp. 
 * Since pointer is constant, it cannot be local and needs memmap */  
static volatile Ifx_STM_TIM0* const Wdg_17_Scu_StmTim0[WDG_17_SCU_MAX_TIMERS] =
{
  &MODULE_STM0.TIM0,
  #if ( WDG_17_SCU_MAX_TIMERS > WDG_AVAILABLE_TIMER_CORE_ONE )
  &MODULE_STM1.TIM0,
  #endif

  #if ( WDG_17_SCU_MAX_TIMERS > WDG_AVAILABLE_TIMER_CORE_TWO )
  &MODULE_STM2.TIM0,
  #endif

  #if ( WDG_17_SCU_MAX_TIMERS > WDG_AVAILABLE_TIMER_CORE_THREE )
  &MODULE_STM3.TIM0,
  #endif

  #if ( WDG_17_SCU_MAX_TIMERS > WDG_AVAILABLE_TIMER_CORE_FOUR )
  &MODULE_STM4.TIM0,
  #endif

  #if ( WDG_17_SCU_MAX_TIMERS > WDG_AVAILABLE_TIMER_CORE_FIVE )
  &MODULE_STM5.TIM0
  #endif
  /* MISRA2012_RULE_19_2_JUSTIFICATION: Array of STM_TIM0 registers, based on
   * CPU index getting the latest tick count. No side effects foreseen by
   * violating this MISRA rule. */
};
#endif
/*To hold core specific Wdg information*/
static Wdg_17_Scu_CoreStatusType* const Wdg_17_Scu_Status[WDG_17_SCU_MAX_TIMERS] =
{
  #if (WDG_17_SCU_CONFIGURED_CORE0 == STD_ON)
  (Wdg_17_Scu_CoreStatusType*)&Wdg_17_Scu_Core0,
  #else
  NULL_PTR,
  #endif
  #if (WDG_17_SCU_MAX_TIMERS > WDG_AVAILABLE_TIMER_CORE_ONE)
  #if (WDG_17_SCU_CONFIGURED_CORE1 == STD_ON)
  (Wdg_17_Scu_CoreStatusType*)&Wdg_17_Scu_Core1,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (WDG_17_SCU_MAX_TIMERS > WDG_AVAILABLE_TIMER_CORE_TWO)
  #if (WDG_17_SCU_CONFIGURED_CORE2 == STD_ON)
  (Wdg_17_Scu_CoreStatusType*)&Wdg_17_Scu_Core2,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (WDG_17_SCU_MAX_TIMERS > WDG_AVAILABLE_TIMER_CORE_THREE)
  #if (WDG_17_SCU_CONFIGURED_CORE3 == STD_ON)
  (Wdg_17_Scu_CoreStatusType*)&Wdg_17_Scu_Core3,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (WDG_17_SCU_MAX_TIMERS > WDG_AVAILABLE_TIMER_CORE_FOUR)
  #if (WDG_17_SCU_CONFIGURED_CORE4 == STD_ON)
  (Wdg_17_Scu_CoreStatusType*)&Wdg_17_Scu_Core4,
  #else
  NULL_PTR,
  #endif
  #endif
  #if (WDG_17_SCU_MAX_TIMERS > WDG_AVAILABLE_TIMER_CORE_FIVE)
  #if (WDG_17_SCU_CONFIGURED_CORE5 == STD_ON)
  (Wdg_17_Scu_CoreStatusType*)&Wdg_17_Scu_Core5,
  #else
  NULL_PTR,
  #endif
  #endif

};

#define WDG_17_SCU_STOP_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Wdg_17_Scu_MemMap.h"

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define WDG_17_SCU_START_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Wdg_17_Scu_MemMap.h"

/*******************************************************************************
** Traceability     :[cover parentID={63BCCED1-A483-4628-BEE7-79D1E75356CD}]  **
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
void Wdg_17_Scu_Init(const Wdg_17_Scu_ConfigType* const ConfigPtr)
{
  Std_ReturnType ErrorFlag = (Std_ReturnType)E_NOT_OK;
  uint32 CoreId;
  /* Retrieve the Current Core Id */
  CoreId = Mcal_GetCpuIndex();
  /* If DET or Safety error check is Enabled */
  /* [cover parentID={A669F2A9-9B6F-4242-A77A-6E07A79DC088}]
   If DET and SAFETY Error Check is Enabled
   [/cover] */
  #if ((WDG_17_SCU_DEV_ERROR_DETECT==STD_ON)||\
  (WDG_17_SCU_SAFETY_ENABLE==STD_ON))
  /*Check the config pointer for any error*/
  /* [cover parentID={FFCB6F39-5E04-490f-990B-0D2F27CEF192}][/cover] */
  ErrorFlag = Wdg_lInitDetCheck(ConfigPtr, CoreId);
  /* If Error flag is E_OK (if no error occurred) */
  /* [cover parentID={F9D4D5BD-6B7B-4d1a-9601-4CF378BC203B}]
   If Error flag is E_OK (if no error occurred)
   [/cover] */
  if(ErrorFlag == (Std_ReturnType)E_OK)
  #endif
  {
    /* Check if Password Sequencing or Time Check flag is enabled */
    /* [cover parentID={FE239EF3-D23D-46ce-813D-591F01D04E57}]
     Check if Password Sequencing or Time Check flag is enabled
     [/cover] */
    ErrorFlag = Wdg_lCheckPassSeqOrTimeCheck(CoreId);
    /*If Error flag is E_OK (if no error occurred)*/
    /* [cover parentID={95834F66-BFAE-4751-9713-9DE6014ADE85}]
      If Error flag is E_OK (If no error occurred)
      [/cover] */
    if(ErrorFlag == E_OK)
    {
      /* Retrieve the Current Core specific configuration and initialize to
         global variable to hold the config pointer */
      /* [cover parentID={650C58FB-0EB8-44ca-B99F-887AA196D353}]
         Retrieve the Current Core specific configuration and
         initialize to global variable to hold the config pointer
        [/cover] */
      Wdg_ConfigPtr[CoreId] = ConfigPtr;
      /* Initialize the CPU specific WDG */
      /* [cover parentID={3CB3D2E6-E9A2-4542-9490-8722F15DA0E1}]
        Initialize the CPU specific Wdg
        [/cover] */
      Wdg_lInit(CoreId);
    }
    /* No initialization done */
    /* [cover parentID={CE66B120-C666-4239-89E8-D0366DE5CF08}]
     Merge
     [/cover] */

  } /* End of (ErrorFlag == E_OK) */
  return;
}/* End of Wdg_17_Scu_Init */

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
** Return value     : E_OK : initialization was successful                    **
**                    E_NOT_OK: initialization was not successful             **
**                                                                            **
*******************************************************************************/
#if (WDG_17_SCU_INIT_CHECK_API == STD_ON)
Std_ReturnType Wdg_17_Scu_InitCheck
(const Wdg_17_Scu_ConfigType* const ConfigPtr)
{

  Std_ReturnType ReturnValue = (Std_ReturnType)E_NOT_OK;
  uint32 CoreId;
  WdgIf_ModeType Mode;
  /*Retrieve the Current Core Id*/
  CoreId = Mcal_GetCpuIndex();
  /*if config pointer is not NULL*/
  /* [cover parentID={A72D578D-DA57-4da5-93E3-06F1EE959895}]
   If ConfigPtr is not NULL
   [/cover] */
  if((ConfigPtr != NULL_PTR) && 
      /*If Core Id is same as the current core*/
      /* [cover parentID={097B9581-7AFC-4537-9249-75315D2F1727}]
        If Core Id is same as the current core
        [/cover] */
      (ConfigPtr->WdgCoreID == CoreId) && 
      /*if the driver is initialized (state of the driver is WDG_IDLE)*/
      /* [cover parentID={1DA3CC7A-53F3-4ac1-B598-753F2F61CFDA}]
        if the driver is initialized (state of the driver is WDG_IDLE)
        [/cover] */
      (Wdg_17_Scu_Status[CoreId]->Wdg_17_Scu_DriverState == WDG_17_SCU_IDLE))
  {
    Mode = ConfigPtr->DefaultMode;
    /*Check to validate the SFR values updated after initialization*/
    /* [cover parentID={A3310A24-C7EE-481a-A0ED-F13E69FBF3F3}]
      Check to validate the SFR values updated after initialization
      [/cover] */
    ReturnValue = Wdg_lSfrInitCheck(ConfigPtr, CoreId, Mode);
    /*If no errors occurred (Return value is E_OK)*/
    /* [cover parentID={FA59A43D-57DD-412b-BD89-08FD30C345CF}]
      If no errors occurred (Return value is E_OK)
      [/cover] */
    if(ReturnValue == (Std_ReturnType)E_OK)
    {
      /*Check if the Global variables are updated after initialization*/
      /* [cover parentID={923B03B4-F2A6-4bb9-9FF3-1508CFFFC395}]
       Check if the Global variables are updated after initialization
      [/cover] */
      ReturnValue = Wdg_lVarInitCheck(ConfigPtr, CoreId, Mode);
    }
    else
    { /*SFRs were not updated as expected after initialization
          (Return value is E_NOT_OK)*/
      /* [cover parentID={E63997EC-BB99-4d9c-98A6-424385371495}]
          SFRs were not updated as expected after initialization
      (Return value is E_NOT_OK)
      [/cover] */
      ReturnValue = (Std_ReturnType)E_NOT_OK;
    }
  }
  else
  { /* Config Pointer is NULL or Core Id is not a match or
       driver is not initialized
      (Return value is E_NOT_OK) */
    /* [cover parentID={A6DBF649-7E75-4c26-B176-612D5550D37F}]
       Config Pointer is NULL or Core Id is not a match or
       driver is not initialized
      (Return value is E_NOT_OK)
      [/cover] */
    ReturnValue = (Std_ReturnType)E_NOT_OK;
  }
  /* [cover parentID={75FDB781-4E68-45f0-B862-6F5EF94D8F45}]
   Return the return value
   [/cover] */
  return ReturnValue;
}/* End of Wdg_17_Scu_Init */
#endif

/*CYCLOMATIC_Wdg_17_Scu_SetMode_JUSTIFICATION: This function checks
the combination of different watchdog features in different modes of its 
operation. The different conditions in different operating modes are 
causing the complexity to increase, but are kept together for readability. */ 
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
** Return value     : E_OK - Mode change was successful                       **
**                    E_NOT_OK - Mode change was unsuccessful                 **
*******************************************************************************/
Std_ReturnType Wdg_17_Scu_SetMode(const WdgIf_ModeType Mode)
{
  uint16 TimeoutValue;
  WdgIf_ModeType PreviousMode;
  #if(WDG_17_SCU_TRIG_SELECT == WDG_17_SCU_GTM_TIMER)
  const Mcu_17_Gtm_TomAtomChConfigType *GtmChConfig;
  uint8 GtmModuleNumber;
  uint8 GtmChannelNumber;
  Ifx_GTM_TOM_CH* TomChannelRegPtr;
  Ifx_GTM_ATOM_CH* AtomChannelRegPtr;
  #endif
  Std_ReturnType ReturnValue = E_OK;
  uint32 CoreId;

  /* Retrieve the current Core Id */
  CoreId = Mcal_GetCpuIndex();

  /* If DET and Safety Error Check is Enabled */
  /* [cover parentID={702948F6-DDFA-41f4-AA33-1DD61DD072EF}]
   If DET and Safety Error Check is Enabled
   [/cover] */
   /* [cover parentID={DEA24ACD-A675-4b6a-BC7A-A97DBA1D087D}]
   If DET and Safety Error Check is Enabled
   [/cover] */
  #if((WDG_17_SCU_DEV_ERROR_DETECT==STD_ON) || (WDG_17_SCU_SAFETY_ENABLE==STD_ON))

  /* Check and Report the development or Safety errors */
  /* [cover parentID={1E43AD2D-D773-4a59-99F2-6684D45F38B9}][/cover] */
  ReturnValue = Wdg_lSetModeDetCheck(Mode, CoreId);
  /*If any DET/Safety errors were not reported (if return value is E_OK) */
  /* [cover parentID={ABD59FEB-40E9-4378-9D1F-DE04DDAE68E4}]
   If any DET/Safety errors were not reported (if return value is E_OK)
   [/cover] */
  if(ReturnValue == E_OK)
  #endif
  {
    /*Hold the previous mode information */
    PreviousMode = Wdg_17_Scu_Status[CoreId]->Wdg_17_Scu_DriverMode;
    /* If requested Mode is not equal to previous mode */
    /* [cover parentID={B097310C-F2B3-4ef5-A237-42D453B16125}]
     If requested Mode is not equal to previous mode [/cover] */
    if(Mode != PreviousMode)
    {      
      /* If the requested mode is OFF_MODE and WDG disable is not allowed */
      /* [cover parentID={1F7427E4-6886-475f-B0AD-2D4ED917606F}]
      If driver is initialized and If the requested mode is OFF_MODE and
      WDG disable is not allowed
      [/cover] */
      if((Wdg_ConfigPtr[CoreId]->WdgDisableAllowed == FALSE) &&
          (Mode == WDGIF_OFF_MODE))
      {
        /* If Production error is enabled */
        #if (WDG_17_SCU_DISABLE_REJECT_DEM_REPORT == WDG_17_SCU_ENABLE_DEM_REPORT)
        /* Report Production error WDG_17_SCU_E_DISABLE_REJECTED as FAILED */
        /* [cover parentID={3D973B0B-9158-49de-9C1B-4233B3230FFB}]
        Report Production error WDG_17_SCU_E_DISABLE_REJECTED as FAILED
        [/cover] */
        Wdg_lReportDemError((Dem_EventIdType)WDG_17_SCU_E_DISABLE_REJECTED,
                               DEM_EVENT_STATUS_FAILED);
        #endif
        /* Set error Flag to E_NOT_OK since mode of WDG is OFF and
          Wdg disable is not allowed */
        /* [cover parentID={B3568278-A00C-43b9-94DA-17E7BA7F876B}]
        Set error Flag to E_NOT_OK since mode of WDG is OFF and
        Wdg disable is not allowed
        [/cover] */
        ReturnValue = E_NOT_OK;
      }
      else
      {
        /* Set error Flag to E_OK since mode of Wdg disable is allowed */
        /* [cover parentID={695F0167-A74C-467d-A3F3-157DF12BB550}]
        Report Production error WDG_17_SCU_E_DISABLE_REJECTED as PASSED
        [/cover] */
        #if (WDG_17_SCU_DISABLE_REJECT_DEM_REPORT == WDG_17_SCU_ENABLE_DEM_REPORT)
        Wdg_lReportDemError((Dem_EventIdType)WDG_17_SCU_E_DISABLE_REJECTED,
                              DEM_EVENT_STATUS_PASSED);
        #endif
        /* [cover parentID={6ABAFDB2-1795-4ee2-B83E-7EC159762B3E}]
        Is GTM used? [/cover] */
        /* [cover parentID={B91529FA-E787-4d00-A80C-F0C94FECAF00}]
        Is GTM used? [/cover] */
        /* [cover parentID={217D44AC-528F-4843-ADBD-E6D83D31AB47}]
        Is GTM used? [/cover] */
        #if(WDG_17_SCU_TRIG_SELECT == WDG_17_SCU_GTM_TIMER)
        /*default index for WdgGtmTimerInfo */
        uint32 GtmIndex = WDG_GTM_INDEX_FAST_MODE; 
        if (Mode == WDGIF_SLOW_MODE)
        {          
          GtmIndex = WDG_GTM_INDEX_SLOW_MODE;
        }
        /*  Retrieve GTM module and Channel number for the Core specific Wdg*/
        GtmChConfig = &(Wdg_ConfigPtr[CoreId]->WdgGtmTimerInfo[GtmIndex]);
        /*Get GTM module number  */
        GtmModuleNumber = (uint8)((GtmChConfig->TimerId &
                          GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);
        /* Get GTM module channel number*/
        GtmChannelNumber = (uint8)((GtmChConfig->TimerId &
                           GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF); 
        #endif 
        /* [cover parentID={8454C64E-4EF9-4fca-A962-4704828ECB47}]
           If mode is OFF[/cover] */
        if(Mode == WDGIF_OFF_MODE)
        {
          #if(WDG_17_SCU_TRIG_SELECT == WDG_17_SCU_GTM_TIMER)
          /* ATOM/TOM channel module is disabled*/
          /* TOM channel module is selected*/
          /* [cover parentID={3DADD306-8171-482d-B57B-D7EF44FFDCD6}]
             If TOM[/cover] */
          if(GtmChConfig->TimerType == MCU_GTM_TIMER_TOM)
          {
            /* De initialize TOM channel */
            /* [cover parentID={5C4B5B43-D87A-4911-B742-8D85B8F1FDD7}]
             Disable TOM channel[/cover] */
             Mcu_17_Gtm_TomChannelDisable(GtmModuleNumber, GtmChannelNumber);
          }
          else  /* ATOM channel module is selected*/
          {
            /* Disable ATOM channel */
            /* [cover parentID={27DF1D36-D5B3-4e1e-80E4-4CA2966A85D0}]
             De initialize ATOM channel [/cover] */
            Mcu_17_Gtm_AtomChannelDisable(GtmModuleNumber, GtmChannelNumber);
          }
          #else /*If STM Timer is selected*/
          /*[cover parentID={7416E03D-0791-469a-95BD-93F5B0520CF2}]
            STM timer selected [/cover] */
          /*Disable the STM interrupt as further service of WDG is
           not required after window expires */
          /* [cover parentID={F8D584E5-E667-455a-B8C3-60CDBFF46B49}]
           Disable the STM interrupt as further service of WDG is not required
           after window expires
           [/cover] */
          Mcu_17_Stm_ComparatorIntDisable(
           (uint8)Wdg_ConfigPtr[CoreId]->WdgStmConfig->StmTimerId, 
           (uint8)Wdg_ConfigPtr[CoreId]->WdgStmConfig->CMPRegId);
          #endif
        }           
        /* Enter the critical section for timer handling  */
        /* [cover parentID={C7D1B629-063D-499c-866E-C71AC3986707}]
        Critical section [/cover] */
        SchM_Enter_Wdg_17_Scu_TimerHandling();
        /* Set Driver State to BUSY */
        Wdg_17_Scu_Status[CoreId]->Wdg_17_Scu_DriverState = WDG_17_SCU_BUSY;             
        /* If requested and previous Mode is not OFF mode */
        /* [cover parentID={E20867E0-FEBD-4eff-A80F-B5F76C914DC4}]
        If requested and previous Mode is not OFF mode [/cover] */
        if((PreviousMode != WDGIF_OFF_MODE) && (Mode != WDGIF_OFF_MODE))
        {
          /* Trigger the Watchdog hardware */
          Wdg_lTrigger();
        }
        /* Set WDG to the requested Mode */
        /* [cover parentID={2915DAAA-C4CB-4b6e-B4C2-EB355F1EA7DC}]
        Set WDG to the requested Mode
        [/cover] */
        ReturnValue = Wdg_lChangeMode(Mode, WDG_17_SCU_SID_SETMODE, CoreId);

        /* Check if there was error during mode switching
        (If return value is E_OK */
        /* [cover parentID={F63A8369-7AD3-4679-B5EF-DC7BB6885B94}]
        Check if there was error during mode switching
        (If return value is not E_OK)
        [/cover] */
        if(ReturnValue != E_OK)
        {
          /*If Production error is enabled*/
          #if (WDG_17_SCU_MODE_FAIL_DEM_REPORT == WDG_17_SCU_ENABLE_DEM_REPORT)
          /*Report Production error WDG_17_SCU_E_MODE_FAILED as FAILED*/
          /* [cover parentID={C9D9A325-A5C5-4918-8170-D3A33506A4D8}]
          Report Production error WDG_17_SCU_E_MODE_FAILED as FAILED
          [/cover] */
          Wdg_lReportDemError((Dem_EventIdType)WDG_17_SCU_E_MODE_FAILED,
                            DEM_EVENT_STATUS_FAILED);
          #endif
          /*Update return value as E_NOT_OK*/
          /* [cover parentID={516272DC-33E4-427b-ADA0-D667518DDCBF}]
          Update return value as E_NOT_OK
          [/cover] */
          ReturnValue = E_NOT_OK;
        }
        /*Report Production error WDG_17_SCU_E_MODE_FAILED as PASSED*/
        /* [cover parentID={F7612F52-C022-4b21-84A9-C6924D00E085}]
        Report Production error WDG_17_SCU_E_MODE_FAILED as PASSED
        [/cover] */
        else
        {
          /*If Production error is enabled*/
          #if (WDG_17_SCU_MODE_FAIL_DEM_REPORT == WDG_17_SCU_ENABLE_DEM_REPORT)
          /*Report Production error WDG_17_SCU_E_MODE_FAILED as PASSED*/
          /* [cover parentID={F7612F52-C022-4b21-84A9-C6924D00E085}]
          Report Production error WDG_17_SCU_E_MODE_FAILED as PASSED
          [/cover] */
          Wdg_lReportDemError((Dem_EventIdType)WDG_17_SCU_E_MODE_FAILED,
                            DEM_EVENT_STATUS_PASSED);
          #endif
          /*Update return value as E_NOT_OK*/
          /* [cover parentID={78A4008C-F267-4113-B3CC-F70EC8A073C2}]
          Update return value as E_OK
          [/cover] */
          ReturnValue = E_OK;        
          /* Update the current mode of Wdg driver */
          Wdg_17_Scu_Status[CoreId]->Wdg_17_Scu_DriverMode = Mode; 
          /* [cover parentID={7A4DC51A-C403-4157-8BD2-6AE8A3624E2D}]
          If mode is not OFF [/cover] */
          if(Mode != WDGIF_OFF_MODE) 
          {
            /* If previous mode is OFF */
            /* [cover parentID={B73937A8-DEDA-4914-BB96-9C4E8CF0FC15}]
            If previous mode is OFF
            [/cover] */
            if(PreviousMode == WDGIF_OFF_MODE)
            {
              /* Wdg_TimeoutCounter will be set in the next
              Wdg_17_Scu_SetTriggerCondition call which should
              be done immediately,in case of transition from
              OFF mode to any other mode.*/
              /* Update the timeout value as initial refresh time */
              TimeoutValue = Wdg_ConfigPtr[CoreId]->InitialRefreshTime;
              /* enable the timer */
              Wdg_lStartOrStopTimeEngine(Mode,CoreId);
              /*Calculate Timeout counter for the new timeout parameter*/
              Wdg_lTimeoutHandler(Mode,TimeoutValue, CoreId);
            }
            else /*If previous mode is not OFF */
            {
              /* If previous Mode is slow */
              /* [cover parentID={766344CF-0D80-4d8c-9428-2762941B2D26}]
                 If previous mode is SLOW
              [/cover] */
              if(PreviousMode == WDGIF_SLOW_MODE)
              {
                /* Update the timeout value for SLOW Mode by multiplying the
                   current timeout counter value with slow refresh time */
                /* [cover parentID={9A3CB966-F808-4239-8157-99B8CF81A6C9}]
                   Update the timeout value for SLOW Mode by multiplying the current
                   timeout counter value with slow refresh time
                [/cover] */
                TimeoutValue = Wdg_17_Scu_Status[CoreId]->Wdg_TimeoutCounter *
                         Wdg_ConfigPtr[CoreId]->SlowModeRefreshTime;
              }
              else
              {
                /* Update the timeout value for FAST Mode by multiplying the
                   current timeout counter value with fast refresh time */
                /* [cover parentID={06CDC216-75B0-4bc2-8C36-E8627F96238D}]
                   Update the timeout value for FAST Mode by multiplying the current
                   timeout counter value with fast refresh time[/cover] */
                TimeoutValue = Wdg_17_Scu_Status[CoreId]->Wdg_TimeoutCounter *
                         Wdg_ConfigPtr[CoreId]->FastModeRefreshTime;
              }
               /* [cover parentID={F22EF696-CB1D-4c9f-8BB2-316B55702379}]
                  if timeout value is not equal to zero [/cover] */
              /* if timeout value is not equal to zero */
              if(TimeoutValue!=0U)              
              {
                /* Calculate Timeout counter for the remaining timeout value */
                Wdg_lTimeoutHandler(Mode, TimeoutValue, CoreId);
              }

              #if(WDG_17_SCU_TRIG_SELECT == WDG_17_SCU_GTM_TIMER)           
              /* TOM channel module is selected*/
              /* [cover parentID={5141108B-1B97-4419-BEFA-7D0D2A850B14}]
              TOM channel module is selected [/cover] */
              /* [cover parentID={6DCE59C8-F797-4eac-BD3A-8B9EC084E6AB}]
              If TOM channel is selected [/cover] */
              if(GtmChConfig->TimerType == MCU_GTM_TIMER_TOM)
              {
                /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects
                 * foreseen by violating this MISRA rule, as the pointer to the
                 * object type it is getting cast into is a known type . */
                /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects
                 * foreseen by violating this MISRA rule. */
                 TomChannelRegPtr = GTM_TOM_CH_POINTER(GtmModuleNumber, GtmChannelNumber);
                /* pulling down the CN0 of used TOM channel */
                 TomChannelRegPtr->CN0.U = 0U ;
                 TomChannelRegPtr->SR0.U = GtmChConfig->TimerChSR0Reg ;
                 TomChannelRegPtr->CM0.U = GtmChConfig->TimerChCM0Reg ; 
              }
              else  /* ATOM channel module is selected*/
              {
                /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects
                 * foreseen by violating this MISRA rule, as the pointer to the
                 * object type it is getting cast into is a known type . */
                /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects
                 * foreseen by violating this MISRA rule. */
                 AtomChannelRegPtr = GTM_ATOM_CH_POINTER(GtmModuleNumber, GtmChannelNumber);
                /* pulling down the CN0 of used ATOM channel */
                 AtomChannelRegPtr->CN0.U = 0U ;
                 AtomChannelRegPtr->SR0.U = GtmChConfig->TimerChSR0Reg ;
                 AtomChannelRegPtr->CM0.U = GtmChConfig->TimerChCM0Reg ;
              }
              #else /*If STM Timer is selected*/
              /* update the timer after setting the new window time */
              Wdg_lStmUpdateCmp (Mode, CoreId);
              #endif 
            }
          }
          /* Reset timeout counter to zero for OFF Mode */
          else
          {
            Wdg_17_Scu_Status[CoreId]->Wdg_TimeoutCounter = 0U;  
          }
        }
        /* Set Driver State to Idle */
        /* [cover parentID={6941446F-9E9B-4409-A838-8641B52C59F5}]
           Change the state of the driver to IDLE[/cover] */
        Wdg_17_Scu_Status[CoreId]->Wdg_17_Scu_DriverState = WDG_17_SCU_IDLE;
        /*Exit critical section for timer handling */
        /* [cover parentID={C7D1B629-063D-499c-866E-C71AC3986707}]
        Critical section [/cover] */
        SchM_Exit_Wdg_17_Scu_TimerHandling();
      }     
    }
  }
  /* Return the the updated retun value */
  return ReturnValue;

} /* End of Wdg_17_Scu_SetMode */

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
void Wdg_17_Scu_SetTriggerCondition(const uint16 timeout)
{
  uint32 CoreId;
  WdgIf_ModeType Mode;
  #if(WDG_17_SCU_TRIG_SELECT == WDG_17_SCU_GTM_TIMER)
  const Mcu_17_Gtm_TomAtomChConfigType *GtmChConfig;
  uint8 GtmModuleNumber;
  uint8 GtmChannelNumber;
  Ifx_GTM_TOM_CH* TomChannelRegPtr;
  Ifx_GTM_ATOM_CH* AtomChannelRegPtr;
  #endif
  /* If DET and Safety Error Check is Enabled */
  #if ((WDG_17_SCU_DEV_ERROR_DETECT == STD_ON) || (WDG_17_SCU_SAFETY_ENABLE == STD_ON))
  Std_ReturnType ReturnValue = E_NOT_OK;
  #endif
  /*Retrieve the current core Id*/
  CoreId = Mcal_GetCpuIndex();
  /* If DET and Safety Error Check is Enabled */
  /* [cover parentID={33AF4C6D-6E82-4063-9307-C93431CBDB8E}]
   If DET and Safety Error Check is Enabled
   [/cover] */
  #if ((WDG_17_SCU_DEV_ERROR_DETECT == STD_ON) || (WDG_17_SCU_SAFETY_ENABLE == STD_ON))
  /*If state of the Wdg driver for the core is not IDLE
  (Wdg driver is not initialized)*/
  /* [cover parentID={D222FEA9-80D8-42fb-8451-200DCF42C8A1}]
   If state of the Wdg driver for the core is not IDLE
   (Wdg driver is not initialized)
   [/cover] */
  if(Wdg_17_Scu_Status[CoreId]->Wdg_17_Scu_DriverState != WDG_17_SCU_IDLE)
  {
    /*Report DET or Safety Error WDG_17_SCU_E_DRIVER_STATE*/
    /* [cover parentID={22AA5179-8A7A-484c-A789-298ADFA08E85}]
      Report DET or Safety Error WDG_17_SCU_E_DRIVER_STATE
      [/cover] */
    Wdg_lReportError
    (WDG_17_SCU_SID_TRIGGER_CONDITION, WDG_17_SCU_E_DRIVER_STATE);   
  }
  /*If input timeout parameter passed is greater than
   the maximum timeout (WdgMaxTimeout)*/
  /* [cover parentID={5836958E-C4B6-4700-AE8F-FF7A4A9929CF}]
   If input timeout parameter passed is greater than
   the maximum timeout (WdgMaxTimeout)
   [/cover] */
  else if(timeout > (uint16)Wdg_ConfigPtr[CoreId]->MaxTimeOutTime)
  {
    /* Report DET or Safety Error WDG_17_SCU_E_PARAM_TIMEOUT */
    /* [cover parentID={39909DC5-C466-4d49-B7E4-8EE4BD8B564D}]
       Report DET or Safety Error WDG_17_SCU_E_PARAM_TIMEOUT
      [/cover] */
    Wdg_lReportError
    (WDG_17_SCU_SID_TRIGGER_CONDITION, WDG_17_SCU_E_PARAM_TIMEOUT);
  }
  else
  { 
    /*Update the return value to E_OK*/
    ReturnValue = E_OK;
  }
  /* If timeout is less than maximum timeout(If return value is E_OK) */
  /* [cover parentID={06240A73-4557-49a8-8DCA-51CFEC2DA04D}]
  If Return Value is E_OK
  [/cover] */
  if(ReturnValue == E_OK)
  #endif
  {
    /* Get the driver mode */
    Mode = Wdg_17_Scu_Status[CoreId]->Wdg_17_Scu_DriverMode;
    /* [cover parentID={B99D33AA-90F9-4428-ADF8-8ADE01686AA9}]
       If Mode is SLOW or FAST
    [/cover] */
    if(Mode != WDGIF_OFF_MODE)
    {       
      /*If GTM Timer is selected*/
      #if(WDG_17_SCU_TRIG_SELECT == WDG_17_SCU_GTM_TIMER)
      /*default index for WdgGtmTimerInfo */  
      uint32 GtmIndex = WDG_GTM_INDEX_FAST_MODE;     
      if (Mode == WDGIF_SLOW_MODE)
      {          
        GtmIndex = WDG_GTM_INDEX_SLOW_MODE;
      }
        
      /*  Retrieve GTM module and Channel number for the Core specific Wdg*/
      GtmChConfig = &(Wdg_ConfigPtr[CoreId]->WdgGtmTimerInfo[GtmIndex]);
      /*Get GTM module number  */
      GtmModuleNumber = (uint8)((GtmChConfig->TimerId &
                               GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);
      /* Get GTM module channel number*/
      GtmChannelNumber = (uint8)((GtmChConfig->TimerId &
                                GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);
      #endif
      /* Enter the critical section for timer handling  */
      /* [cover parentID={559EBB3E-3165-4c44-85E6-42791ACEDC76}]
      Schm timer handling [/cover] */
      
      SchM_Enter_Wdg_17_Scu_TimerHandling();
      /* Set the driver state to BUSY */
      /* [cover parentID={87FD7770-CFC3-46e2-BE38-C8BBA488895F}]
      Set the driver state to BUSY [/cover] */
      Wdg_17_Scu_Status[CoreId]->Wdg_17_Scu_DriverState = WDG_17_SCU_BUSY;
      
      /*If GTM Timer is selected*/
      /* [cover parentID={F950F914-F5D2-4594-A4E0-42FD1128FD16}]
      If GTM Timer is selected [/cover] */
      #if(WDG_17_SCU_TRIG_SELECT == WDG_17_SCU_GTM_TIMER)   
      /* TOM channel module is selected*/
      /* [cover parentID={5141108B-1B97-4419-BEFA-7D0D2A850B14}]
      TOM channel module is selected [/cover] */
      if(GtmChConfig->TimerType == MCU_GTM_TIMER_TOM)
      {
        /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects
         * foreseen by violating this MISRA rule, as the pointer to the
         * object type it is getting cast into is a known type . */
        /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects
         * foreseen by violating this MISRA rule. */
        TomChannelRegPtr = GTM_TOM_CH_POINTER(GtmModuleNumber, GtmChannelNumber);
        /* pulling down the CN0 of used TOM channel */
        TomChannelRegPtr->CN0.U = 0U ;
      }
      else  /* ATOM channel module is selected*/
      {
        /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects
         * foreseen by violating this MISRA rule, as the pointer to the
         * object type it is getting cast into is a known type . */
        /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects
         * foreseen by violating this MISRA rule. */
        AtomChannelRegPtr = GTM_ATOM_CH_POINTER(GtmModuleNumber, GtmChannelNumber);
        /* pulling down the CN0 of used ATOM channel */
        AtomChannelRegPtr->CN0.U = 0U ;
      }
      #else /*If STM Timer is selected*/
      /* update the timer after setting the new window time */
      Wdg_lStmUpdateCmp (Mode, CoreId);
      #endif 
      /* Calculate Timeout counter for the new timeout parameter */
      /* [cover parentID={83B985F3-1EBB-4fb8-BE00-DECFD53872AB}]
      Calculate Timeout counter for the new timeout parameter
      [/cover] */
      Wdg_lTimeoutHandler(Mode, timeout, CoreId);
      /* If the timeout counter is not zero (If zero, Do nothing)*/
      /* [cover parentID={E825DE38-EBDA-474e-810A-ADE34C8DA32A}]
      If the timeout counter is not zero (If zero, Do nothing)
      [/cover] */
      if(Wdg_17_Scu_Status[CoreId]->Wdg_TimeoutCounter != (uint16)0x0U)
      {
        /* If current mode is not OFF mode */
        /* [cover parentID={356D88E0-EC57-415a-838C-9BB6452F553F}]
           If current mode is not OFF mode
           [/cover] */

          /* Trigger the Watchdog hardware */
          /* [cover parentID={2BFC3E4A-0F98-426e-B0E4-1FB94C042315}]
              Trigger the Watchdog hardware
              [/cover] */
          Wdg_lTrigger();

      }
      /* Set the driver state to IDLE */
      /* [cover parentID={33DE6C47-F2FB-4d98-B03B-D25655373433}]
        Set the driver state to IDLE
        [/cover] */
      Wdg_17_Scu_Status[CoreId]->Wdg_17_Scu_DriverState = WDG_17_SCU_IDLE;
      /*Exit critical section for timer handling */
      SchM_Exit_Wdg_17_Scu_TimerHandling();
    }
  }
  return;
}
/* End of Wdg_17_Scu_SetTriggerCondition */

/*******************************************************************************
** Traceability     :[cover parentID={18FCC30C-D81C-44d6-8058-37C0D932A011}]  **
**                                                                            **
** Syntax           : void Wdg_17_Scu_GetVersionInfo                          **
**                    (                                                       **
**                      const Std_VersionInfoType* versioninfo                **
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
** Reentrancy       : Reentrant                                               **
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
/* [cover parentID={DE9BAC89-B634-4052-8F3A-7D16848FD88D}]
Wdg_17_Scu_GetversionInfo
[/cover] */
void Wdg_17_Scu_GetVersionInfo (Std_VersionInfoType* const versioninfo)
{
  /* If DET and Safety Error check is Enabled */
  /* [cover parentID={5F0C5BDC-3DED-4227-BB84-D9BCD0419407}]
     If DET and SAFETY Error Check is Enabled
   [/cover] */
  #if ((WDG_17_SCU_DEV_ERROR_DETECT == STD_ON) || (WDG_17_SCU_SAFETY_ENABLE == STD_ON))
  Std_ReturnType ReturnValue = E_NOT_OK;
  /* If the passed parameter is a NULL_PTR. */
  /* [cover parentID={8539E56D-C90F-45f6-9A6E-584038771D7B}]
    If the passed parameter is a NULL_PTR
   [/cover] */
  if((versioninfo) == NULL_PTR)
  {
    /* Report a DET or a Safety Error WDG_17_SCU_E_PARAM_POINTER */
    /* [cover parentID={8A924DA9-6A2E-4701-880D-DEF04B3016D3}]
      Report a DET or a Safety Error WDG_17_SCU_E_PARAM_POINTER
      [/cover] */
    Wdg_lReportError
    (WDG_17_SCU_SID_GETVERSIONINFO, WDG_17_SCU_E_PARAM_POINTER);
    /* Update the return value to E_NOT_OK */
    /* [cover parentID={E24E8FA5-CDBF-4126-85C7-648B11F64614}]
      Update the return value to E_NOT_OK
      [/cover] */
    ReturnValue = E_NOT_OK;
  }
  else
  {
    /* Update the return value to E_OK */
    /* [cover parentID={2258F8A0-ED02-4eab-A8EE-758650C9C8C9}]
       Update the return value to E_OK
      [/cover] */
    ReturnValue = E_OK;
  }
  /* If Return value is E_OK */
  /* [cover parentID={6D491A16-164D-4b10-8E7C-D6189E3BCB2D}]
   If Return Value is E_OK
   [/cover] */
  if(ReturnValue == (Std_ReturnType)E_OK)
  #endif
  {
    /* Retrieve the version information of Wdg  the module */
    /* [cover parentID={FDF46A91-8F4E-4f43-B133-AF5E2A52E0AA}]
      Retrieve the version information of WDG the module
      [/cover] */
    /* Get Vendor ID */
    ((Std_VersionInfoType*)(versioninfo))->vendorID = WDG_17_SCU_VENDOR_ID;
    /* Get WDG Module ID */
    ((Std_VersionInfoType*)(versioninfo))->moduleID = WDG_17_SCU_MODULE_ID;
    /* Get WDG module Software major version */
    ((Std_VersionInfoType*)(versioninfo))->sw_major_version =
      (uint8)WDG_17_SCU_SW_MAJOR_VERSION;
    /* Get WDG module Software minor version */
    ((Std_VersionInfoType*)(versioninfo))->sw_minor_version =
      (uint8)WDG_17_SCU_SW_MINOR_VERSION;
    /* Get WDG module Software patch version */
    ((Std_VersionInfoType*)(versioninfo))->sw_patch_version =
      (uint8)WDG_17_SCU_SW_PATCH_VERSION;
  }
  return;
}

#endif
/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/


/*******************************************************************************
** Traceability     : [cover parentID={DB288E09-8D55-4e01-B62C-B1F7796C47F7}] **
**                                                                            **
** Syntax           : void Wdg_lTrigger(void)                                 **
**                                                                            **
** Description      : This routine triggers the watchdog hardware. It has to  **
**                    be called cyclically in order to prevent the            **
**                    watchdog hardware from expiring.                        **
**                    counter                                                 **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
*******************************************************************************/
static void Wdg_lTrigger(void)
{
  uint32 PasswordAccess;
  uint32 ModifyAccess;
  /* Local variable to hold the value of Watchdog Timer Control Register */
  uint32 WdtCon0;
  uint32 CoreId;

  CoreId = Mcal_GetCpuIndex();

  /* Password Access:
   - (Bits[7:4])Set Hardware password to WDTHPW1 TO 1111.
   - (Bits[3:2])This field must be written with the value of the bits
                SCU_WDTCPU0_CON1.WDTDR and SCU_WDTCPU0_CON1.WDTIR.
   - (Bit[1])Set WDTLCK to '0' to unlock SCU_WDTCPU0_CON0.
   - (Bit[0])Write back the read ENDINIT bit.
  */
  /* Enter critical section */
  /* [cover parentID={9ECCE1C5-A6CD-4fd5-8A43-F021F1476A1D}]
    Enter critical section for CPU ENDINIT[/cover] */
  /*SchM_Enter_Wdg_17_Scu_Trigger();*/
  /* [cover parentID={A8B9B338-BFD3-4138-8EF4-E5B8A500E45D}][/cover] */
  SchM_Enter_Wdg_17_Scu_CpuEndInit();
  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  WdtCon0 = (uint32)WDG_REGMAP[CoreId].CON0.U;
  /* Password Access:
     - (Bits[15:8])Set Hardware password WDTHPW1 TO 0
     - (Bits[7:4])Set Hardware password TO 1111
     - (Bits[3:2]) This field must be written with 0's during a password
                   access to SCU_WDTCPU0_CON0.
     - (Bit[1]) Set WDTLCK to '0' to unlock SCU_WDTCPUx_CON0
     - (Bit[0]) Set ENDINIT bit while password access
   */
  /* [cover parentID={DE64BEEA-27D7-4fd2-94C9-16E842B5F1A5}]
   Access Password[/cover] */
  PasswordAccess = Wdg_lAccessPassword(WdtCon0);
  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* [cover parentID={5F8F3E87-E5A9-4854-B770-20523AD02C18}]
   Clear ENDINIT, LOCK bit with the Password[/cover] */
  WDG_REGMAP[CoreId].CON0.U = (uint32)PasswordAccess;  /* PASSWORD ACCESS */

  /* Modify Access:
     - (Bits[15:8]) Password as is.
     - (Bits[7:2]) Bits should be inverted
     - (Bit[1]) Set WDTLCK to '1' to unlock SCU_WDTCPUx_CON0
     - (Bit[0]) Set ENDINIT bit to '1' while modify access
  */
  ModifyAccess = (PasswordAccess) | WDT_SETLCK_ENDINIT;

  /* MODIFY ACCESS */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */

  WDG_REGMAP[CoreId].CON0.U = (uint32)ModifyAccess;
  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  WdtCon0 = (uint32)WDG_REGMAP[CoreId].CON0.U;
  PasswordAccess = Wdg_lAccessPassword(WdtCon0);
  /* PASSWORD ACCESS */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  WDG_REGMAP[CoreId].CON0.U = (uint32)PasswordAccess;
  /* Update with the existing Reload Value */
  /* [cover parentID={474DE07B-D913-4eab-9A20-37DA4F68CA3E}]
   Modify the Access[/cover] */
  ModifyAccess = Wdg_lModifyAccessPassword(PasswordAccess);
  /* [cover parentID={D95D0991-0524-4076-B676-DFB936CBCAA3}]
   Calculate Current Mode Reload Value[/cover] */
  ModifyAccess |= Wdg_lReloadModifyAccess
                  (Wdg_17_Scu_Status[CoreId]->Wdg_CurrentReloadValue);
  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* [cover parentID={421D50B7-5339-4e19-BA83-D68109CDFD1F}]
   Set the ENDINIT and LOCK bit and Reload value by
   using the Password[/cover] */
  WDG_REGMAP[CoreId].CON0.U = (uint32)ModifyAccess;

  /* Exit critical section */
  /* [cover parentID={8FC99E05-7A71-4d45-8FEA-711A77684F5F}]
   Exit critical section for CPU ENDINIT[/cover] */
  /*SchM_Exit_Wdg_17_Scu_Trigger();*/
  /* [cover parentID={A8B9B338-BFD3-4138-8EF4-E5B8A500E45D}][/cover] */
  SchM_Exit_Wdg_17_Scu_CpuEndInit();

  return;
} /* End of Wdg_lTrigger */

/*******************************************************************************
** Traceability     : [cover parentID={F346C9BB-854B-4209-9BDE-4479A870F5BC}] **
**                                                                            **
** Syntax           : void Wdg_lUpdateWdtRelVal                               **
**                            (const uint16 ReloadValue,const uint32 CoreId)  **
**                                                                            **
** Description      : This routine Store the Reload value of the Current Core **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : ReloadValue : WDT reload value                          **
**                    CoreId :Id of the core                                  **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE void Wdg_lUpdateWdtRelVal(const uint16 ReloadValue, 
                                       const uint32 CoreId)
{  
  uint32 WdtCon0;  
  /*Enter Critical Section for CpuEndInit*/
  /* [cover parentID={272E1B8A-1352-42e2-AC1F-D017D6AE2942}]
   Enter critical section for CpuEndinit
   [/cover] */
  /* [cover parentID={A8B9B338-BFD3-4138-8EF4-E5B8A500E45D}][/cover] */
  SchM_Enter_Wdg_17_Scu_CpuEndInit();
  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
    * by violating this MISRA rule, as the pointer to the object type
    * it is getting cast into is a known type . */
  /* Retrieve the contents of the OCN0 register into a local variable */
  WdtCon0 = (uint32)WDG_REGMAP[CoreId].CON0.U;
  /* Calculate Password, ENDINIT and LOCK bit to Clear */
  /* [cover parentID={632F376F-0091-4fb3-B96D-B7297854156A}]
   Calculate Password, ENDINIT and LOCK bit to Clear
   [/cover] */
  WdtCon0 = Wdg_lAccessPassword(WdtCon0);
  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* Clear ENDINIT, LOCK bit with the Password of the Current Core CON0
   Register */
  /* [cover parentID={E62589AB-1861-40cd-9DDA-29D999E2887F}]
   Clear ENDINIT, LOCK bit with the Password of the Current Core CON0 Register
   [/cover] */
  WDG_REGMAP[CoreId].CON0.U = (uint32)WdtCon0;
  /*Calculate Password, LOCK and ENDINIT bit to set*/
  /* [cover parentID={D5F0D9C1-4C5A-47ab-A9A6-0228A42BFF23}]
   Calculate Password, LOCK and ENDINIT bit to set
   [/cover] */
  WdtCon0 = Wdg_lModifyAccessPassword(WdtCon0);
  /* Calculate Reload Value */
  /* [cover parentID={00BE6476-911F-4abc-975F-03D4926ED653}]
    Calculate Reload Value
    [/cover] */
  WdtCon0 |= Wdg_lReloadModifyAccess(ReloadValue);
  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /*Set the ENDINIT and LOCK bit and Reload value by using the
     Password of the Current Core CON0 Register*/
  /* [cover parentID={74436391-DB24-4e4d-8E8F-2658458A0151}]
   Set the ENDINIT and LOCK bit and Reload value by using the Password of the
   Current Core CON0 Register[/cover] */
  WDG_REGMAP[CoreId].CON0.U = (uint32)WdtCon0;

  /* Exit Critical Section for CpuEndInit */
  /* [cover parentID={63882F63-06B6-46e0-804F-2AE6A275E18A}]
   Exit critical section for CpuEndinit[/cover] */
  /* [cover parentID={A8B9B338-BFD3-4138-8EF4-E5B8A500E45D}][/cover] */
  SchM_Exit_Wdg_17_Scu_CpuEndInit();
} /* End of Wdg_lUpdateWdtRelVal */

/*******************************************************************************
** Traceability     : [cover parentID={9998B88D-52D1-4150-8113-37FED79C1AB6}] **
**                                                                            **
** Syntax           : Std_ReturnType Wdg_lChangeMode                          **
**                                      (const WdgIf_ModeType Mode,           **
**                                       const uint8 ApiId,                   **
**                                      (const uint32 CoreId)                 **
**                                                                            **
** Description      : This routine changes the mode of WDG to the given mode. **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : Mode   -  Mode to which the WDG to be switched          **
**                    ApiId  -  Service Id of the API in which the            **
**                              local function is called                      **
**                    CoreId -  Id of the core                                **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK or E_NOT_OK                                        **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Wdg_lChangeMode
(const WdgIf_ModeType Mode, const uint8 ApiId, const uint32 CoreId)
{
  Std_ReturnType ChangeModeDone;
  /* MISRA2012_RULE_19_2_JUSTIFICATION:Union used for register type definition.
   No side effects foreseen by violating this MISRA rule*/
  Ifx_SCU_WDTCPU_CON1 WdtCon1;
  uint32 ClockDivider;
  uint16 ReloadValue;
  uint8 TimeoutModeFlag;
  uint8 DisableFlag;
  /* Set the default error status to E_NOT_OK */
  ChangeModeDone = E_NOT_OK;
  /* If OFF Mode is requested */
  /* [cover parentID={96E4E9D5-6D74-4029-B5EA-D0D45DEE11AF}]
   If Mode is OFF and Wdg Disable is Allowed
   [/cover] */
  if (Mode == WDGIF_OFF_MODE)
  {
    ReloadValue = WDG_RELOAD_RESET_VALUE;
    /* Update current reload value with Reload Reset value */
    Wdg_17_Scu_Status[CoreId]->Wdg_CurrentReloadValue = ReloadValue;
    /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
      * by violating this MISRA rule, as the pointer to the object type
      * it is getting cast into is a known type . */
    /* Read contents of the the CON1 register to a local variable */
    WdtCon1.U = WDG_REGMAP[CoreId].CON1.U;
    /* Update the CON1 register's DR bit to disable the watchdog */
    WdtCon1.B.DR = WDG_DISABLE_WDT;
    /* [cover parentID={AF1F26AF-41AC-4ec6-8687-8D3A4645E819}]
       Is this local function called from Wdg_17_Scu_SetMode()
       [/cover] */ 
    /* Is this local function called from Wdg_17_Scu_SetMode() */
    if (ApiId == WDG_17_SCU_SID_SETMODE)
    {
      /* Request to Disable the Watchdog */
      /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
       * by violating this MISRA rule, as the pointer to the object type
       * it is getting cast into is a known type . */
      /* Disable the Watchdog for the Current Core ID */
      WDG_LIB_RUNTIME_WRITECPUENDINITPROTREG(&WDG_REGMAP[CoreId].CON1, (uint32)WdtCon1.U);
    }
    else
    { 
      /* Request to Disable the Watchdog */
      /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
       * by violating this MISRA rule, as the pointer to the object type
       * it is getting cast into is a known type . */

      /* Disable the Watchdog for the Current Core ID */
      /* [cover parentID={34AF6F86-74A9-4aaf-BB00-643C91D1574A}]
         Disable the Watchdog for the Current Core ID
         [/cover] */
      WDG_LIB_INIT_WRITECPUENDINITPROTREG(&WDG_REGMAP[CoreId].CON1, (uint32)WdtCon1.U);
    }
    /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
      * by violating this MISRA rule, as the pointer to the object type
      * it is getting cast into is a known type . */
    /* Read the TO(timeout) flag  from the SR register */
    TimeoutModeFlag = (uint8)WDG_REGMAP[CoreId].SR.B.TO;
    /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
      * by violating this MISRA rule, as the pointer to the object type
      * it is getting cast into is a known type . */
    /* Read the DS(Disable) flag  from the SR register */
    DisableFlag = (uint8)WDG_REGMAP[CoreId].SR.B.DS;

    /*If the Disable flag is enabled and timeout mode is disabled*/
    /* [cover parentID={4D2B8439-789E-4b73-BA82-0C63832C7062}]
      If the Disable flag is enabled and timeout mode is disabled
      [/cover] */
    if ( (1U == DisableFlag) && (0U == TimeoutModeFlag) )
    {
      /* Change Mode to OFF was successful */
      /* [cover parentID={49AB97E4-8265-4470-8E71-13FCC8D7EA6B}]
        Mode change Successful. Update Return Value as E_OK
        [/cover] */
      ChangeModeDone = E_OK;
    }

  }
  else /* Mode is WDGIF_SLOW_MODE  or WDGIF_FAST_MODE */
  {
    /* Mode is WDGIF_SLOW_MODE*/
    /* [cover parentID={B26C289B-78E2-4632-9A79-2C4B3AE6E118}]
      If Mode is SLOW
      [/cover] */
    if (Mode == WDGIF_SLOW_MODE)
    {
      /* [cover parentID={A2ED8634-385C-4e7b-8F70-92456CD9B233}]
        Retrieve the Clock Divider Value and the Reload Value for
        SLOW Mode for the Current Core ID
        [/cover] */
      ClockDivider = WDG_RESET_WDTIR_RESET_WDTDR;
      /* Retrieve the Reload value for Slow mode */
      /* [cover parentID={98AC21BD-598F-4472-A271-0E1A66530458}]
        Update current reload value with Reload Reset value
        [/cover] */
      ReloadValue  = Wdg_ConfigPtr[CoreId]->SlowModeReloadValue;
    }
    /* [cover parentID={F7AE96D6-2F16-47de-9FE2-ECE0B536979B}]
      If Mode is FAST
      [/cover] */
    else /*  Mode is WDGIF_FAST_MODE */
    {
      /* [cover parentID={50B1F59F-8152-4baa-A011-6CA269EC101E}]
            Retrieve the Clock Divider Value and the Reload Value for
            FAST Mode for the Current Core ID[/cover] */
      /* Get the Clock divider for Fast mode */
      ClockDivider = WDG_SET_WDTIR_RESET_WDTDR;
      /* Get the Reload value for Fast mode */
      ReloadValue  = Wdg_ConfigPtr[CoreId]->FastModeReloadValue;
    }       
    /* Update the Reload value of the Current Core */
    Wdg_lUpdateWdtRelVal(ReloadValue, CoreId);
       
     /* Is this local function called from Wdg_17_Scu_SetMode() */
     /* [cover parentID={D26F9D9E-24BA-4916-8726-A06F256091F0}]
        Is this local function called from Wdg_17_Scu_SetMode() 
        [/cover]  */
    if (ApiId == WDG_17_SCU_SID_SETMODE)
    {
      /* To update WDTx_CON1 in Supervisor mode,Set the clock divider */
      /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
       * by violating this MISRA rule, as the pointer to the object type
       * it is getting cast into is a known type . */

      /*Update the CON1 register with the clock divider value*/
      WDG_LIB_RUNTIME_WRITECPUENDINITPROTREG(&WDG_REGMAP[CoreId].CON1,(uint32)ClockDivider);
    }
    else
    { 
      /* To update WDTx_CON1 in Supervisor mode,Set the clock divider */
      /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
       * by violating this MISRA rule, as the pointer to the object type
       * it is getting cast into is a known type . */

      /*Update the CON1 register with the clock divider value*/
      /* [cover parentID={37891E8F-D0B2-4ecd-BC06-A6AE31A57AF0}]
       Update the Clock Divider In CON1 Register of the Current Core
      [/cover] */
      WDG_LIB_INIT_WRITECPUENDINITPROTREG(&WDG_REGMAP[CoreId].CON1, (uint32)ClockDivider);
    }
    /* Check if clock divider is FAST*/
    if ( ClockDivider == WDG_SET_WDTIR_RESET_WDTDR)
    {
      /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
       * by violating this MISRA rule, as the pointer to the object type
       * it is getting cast into is a known type . */
      /* [cover parentID={3AFE9BE3-9780-4b73-A12A-099DC6776BB2}]
        If Mode in the SCU_WDTCPUxSR status register is FAST
        [/cover] */
      if (((WDG_REGMAP[CoreId].SR.U) & WDG_STATUS_MASK) == 
          WDG_SET_WDTIR_RESET_WDTDR)
      {
        /* [cover parentID={853C6555-3694-45f0-A980-8CA2FD7BC5CE}]
           Mode Change is Successful . Update Return Value as E_OK.
           [/cover] */
        ChangeModeDone = E_OK; /* Change Mode to FAST was successful */
      }
    }
    else /* ClockDivider is SLOW */
    {
      /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
       * by violating this MISRA rule, as the pointer to the object type
       * it is getting cast into is a known type . */
      /* [cover parentID={5A45F8EA-3710-4804-9BBD-E0D5C97423FD}]
        If Mode in the SCU_WDTCPUxSR status register is SLOW
        [/cover] */
      if (((WDG_REGMAP[CoreId].SR.U) & WDG_STATUS_MASK) == 
          WDG_RESET_WDTIR_RESET_WDTDR)
      {
        /* [cover parentID={82F4653C-69F6-4e6f-8266-B2EFB5C0D6EE}]
           Mode Change is Successful . Update Return Value as E_OK.
           [/cover] */
        ChangeModeDone = E_OK; /* Change Mode to SLOW was successful */

      }
    }/* End of 'if ( ClockDivider == WDG_SET_WDTIR_RESET_WDTDR)' */
    /* [cover parentID={A7C46AE8-1F36-45b8-BF4C-8D6F5BEC5E33}]
    Is the return status E_OK?
    [/cover] */
    if( ChangeModeDone != E_OK )
    { 
  
      /* Is this local function called from Wdg_17_Scu_SetMode() */
      /* [cover parentID={65D7C15A-5D20-4ab0-A1FB-071CAF2DF0B2}]
         Is this local function called from Wdg_17_Scu_SetMode() 
         [/cover]  */
      if (ApiId == WDG_17_SCU_SID_SETMODE)
      {
        /* Restore the Reload value because of ChangeMode failure */  
        Wdg_lUpdateWdtRelVal(Wdg_17_Scu_Status[CoreId]->Wdg_CurrentReloadValue, CoreId);  
      }
      else
      {  
        /* Restore the Reload value because of ChangeMode failure */  
        Wdg_lUpdateWdtRelVal((uint16)0xFFFCU, CoreId);
      }
    }
    else
    {
      /* [cover parentID={0A7FD043-F1B4-473f-88A2-AAB53BBA43D4}]
         ChangeMode successful, update the global data
      [/cover] */
      /* ChangeMode successful, update the global data */
      Wdg_17_Scu_Status[CoreId]->Wdg_CurrentReloadValue = ReloadValue;
    }

  } /* End of 'if (Mode == WDGIF_SLOW_MODE)' */
  /* return E_OK if change mode done successfully */

  return ChangeModeDone;

}/* End of Wdg_lChangeMode */

/*******************************************************************************
** Traceability     : [cover parentID={51FFCB91-1BBF-4b4d-96C7-44CEABEB5F49}] **
**                                                                            **
** Syntax           : void Wdg_lStartOrStopTimeEngine                         **
**                         (const WdgIf_ModeType Mode, const uint32 CoreId)   **
**                                                                            **
** Description      : This function starts SRV timer if watchdog SLOW-MODE    **
**                    or FAST-MODE is requested                               **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : Mode : Mode to which the WDG to be switched             **
**                    CoreId :Id of the core                                  **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
*******************************************************************************/
static void Wdg_lStartOrStopTimeEngine
(const WdgIf_ModeType Mode, const uint32 CoreId)
{
  #if(WDG_17_SCU_TRIG_SELECT == WDG_17_SCU_GTM_TIMER)
  const Mcu_17_Gtm_TomAtomChConfigType *GtmChConfig;
  uint8 GtmModuleNumber;
  uint8 GtmChannelNumber;
  /*default index for WdgGtmTimerInfo */
  uint32 GtmIndex = WDG_GTM_INDEX_FAST_MODE;   

  if (Mode == WDGIF_SLOW_MODE)
  {          
    GtmIndex = WDG_GTM_INDEX_SLOW_MODE;
  }  
  /* [cover parentID={F3BCF407-3B42-4b01-8714-75CD3945EE71}]
   Retrieve GTM module and Channel number for the Core specific Wdg[/cover] */
  GtmChConfig = &(Wdg_ConfigPtr[CoreId]->WdgGtmTimerInfo[GtmIndex]);

  /*Get GTM module number  */
  GtmModuleNumber = (uint8)((GtmChConfig->TimerId & 
                             GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);
  /* Get GTM module channel number*/
  GtmChannelNumber = (uint8)((GtmChConfig->TimerId & 
                              GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);
  /* ATOM/TOM channel module is disabled*/
  /* TOM channel module is selected*/
  /* [cover parentID={3DADD306-8171-482d-B57B-D7EF44FFDCD6}]
   If TOM[/cover] */
  if(GtmChConfig->TimerType == MCU_GTM_TIMER_TOM)
  {
    /* De initialize TOM channel */
    /* [cover parentID={5C4B5B43-D87A-4911-B742-8D85B8F1FDD7}]
      De initialize TOM channel[/cover] */
    Mcu_17_Gtm_TomChannelDisable(GtmModuleNumber, GtmChannelNumber);
  }
  else  /* ATOM channel module is selected*/
  {
    /* De initialize ATOM channel */
    /* [cover parentID={27DF1D36-D5B3-4e1e-80E4-4CA2966A85D0}]
      De initialize ATOM channel [/cover] */
    Mcu_17_Gtm_AtomChannelDisable(GtmModuleNumber, GtmChannelNumber);
  }
  #else /*If STM Timer is selected*/

  /*Disable the STM interrupt as further service of WDG is
   not required after window expires */
  /* [cover parentID={F8D584E5-E667-455a-B8C3-60CDBFF46B49}]
   Disable the STM interrupt as further service of WDG is not required
   after window expires
   [/cover] */
  Mcu_17_Stm_ComparatorIntDisable
  ((uint8)Wdg_ConfigPtr[CoreId]->WdgStmConfig->StmTimerId, 
   (uint8)Wdg_ConfigPtr[CoreId]->WdgStmConfig->CMPRegId);
  #endif
  /* [cover parentID={3A9F1764-4E6C-4a0b-AAB5-B1859AA5098D}]
     If mode is not OFF [/cover] */
  /* [cover parentID={420BCAAC-0E7E-4350-ADC5-02D5CD1EE4B4}]
     If mode is not OFF [/cover] */
  if(Mode != WDGIF_OFF_MODE)
  { 
    /* [cover parentID={87DFBC48-E2A9-4a66-B3C9-5AEC99E1F13A}]
       If GTM? [/cover] */
    #if(WDG_17_SCU_TRIG_SELECT == WDG_17_SCU_GTM_TIMER)
    /* ATOM/TOM channel module is enabled*/
    /* check if it is TOM Channel */
    /* [cover parentID={BFB4DBEB-F042-458b-BC43-23103CBAAA81}]
       check if it is TOM Channel [/cover] */
    if(GtmChConfig->TimerType == MCU_GTM_TIMER_TOM)
    {
      /* Initialize TOM channel */
      /* [cover parentID={5E1409FF-8136-4c25-AC55-C4E55AC0D365}]
         Initialize TOM channel [/cover] */
      Mcu_17_Gtm_TomChannelInit(GtmChConfig);
      /*Data in Shadow registers is transferred to main TOM/ATOM registers*/
      Mcu_17_Gtm_TomChannelShadowTransfer(GtmModuleNumber, GtmChannelNumber);
      /* Enabled TOM channel */
      Mcu_17_Gtm_TomChannelEnable(GtmModuleNumber, GtmChannelNumber, 0U);
    }
    else  /* ATOM channel module is selected*/
    {
      /* Initialize ATOM channel */
      /* [cover parentID={E0742041-3AB3-49c7-9B15-B33B8B30724C}]
         Initialize ATOM channel [/cover] */
      Mcu_17_Gtm_AtomChannelInit (GtmChConfig);
      /*Data in Shadow registers is transferred to main TOM/ATOM registers*/
      Mcu_17_Gtm_AtomChannelShadowTransfer(GtmModuleNumber, GtmChannelNumber);
      /* Enabled ATOM channel */
      Mcu_17_Gtm_AtomChannelEnable(GtmModuleNumber, GtmChannelNumber, 0U);
    }
    #else
    /* update the timer after setting the new window time */
    Wdg_lStmUpdateCmp (Mode, CoreId);
    #endif
  } /* end of If(Mode != OFF_MODE) */
  
  return;

} /* End of Wdg_lStartOrStopTimeEngine */

#if(WDG_17_SCU_TRIG_SELECT == WDG_17_SCU_STM_TIMER)
/*******************************************************************************
** Traceability     : [cover parentID={8F79F632-188D-4630-A0A3-93DFB2200A74}] **
**                                                                            **
** Syntax           : void Wdg_lStmUpdateCmp                                  **
**                         (const WdgIf_ModeType Mode, const uint32 CoreId)   **
**                                                                            **
** Description      : This function Updates the CMP Register of STM           **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : Mode : Mode to which the WDG to be switched             **
**                    CoreId :Id of the core                                  **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
*******************************************************************************/
static void Wdg_lStmUpdateCmp(const WdgIf_ModeType Mode, const uint32 CoreId)
{
  Mcu_17_Stm_TimerConfigType StmConfig;
  uint32 TimeOutCount;
  uint32 TimeOutResolution;
  uint32 StmTimerNumber;
  uint32 StmTimerValue;
  uint32 RefreshTime = 0U;

  /*Retrieve the Stm timer number and Stm timer Resolution */
  TimeOutResolution = Mcal_DelayTickResolution();
  StmTimerNumber = Wdg_ConfigPtr[CoreId]->WdgStmConfig->StmTimerId;

  /*If Mode is SLOW */
  /* [cover parentID={90A662DB-4783-4cd7-945D-5D577BAEB457}][/cover] */
  if(Mode == WDGIF_SLOW_MODE)
  {
    /*Reading the slow mode refresh time in local variable */
    RefreshTime = Wdg_ConfigPtr[CoreId]->SlowModeRefreshTime ;
  }
  else
  {
    /*Reading the fast mode refresh time in local variable */
    RefreshTime = Wdg_ConfigPtr[CoreId]->FastModeRefreshTime ;
  }
  /*Retrieve  all the STM timer information from the initialized
    Wdg config pointer */
  TimeOutCount = ((RefreshTime * WDT_TIMEOUT_FACTOR) / TimeOutResolution);
  StmConfig.StmTimerId =  Wdg_ConfigPtr[CoreId]->WdgStmConfig->StmTimerId;
  StmConfig.CMPRegId =  Wdg_ConfigPtr[CoreId]->WdgStmConfig->CMPRegId;
  StmConfig.CmconRegVal =  Wdg_ConfigPtr[CoreId]->WdgStmConfig->CmconRegVal;
  StmConfig.reserved = 0x0U;

  /* Update the CMP Register value by adding the current STMx_TIM0(x=CoreId)
     with the tmeoutcount((ModeRefreshtime*100000)/STM timer Resolution) */
  StmTimerValue = (uint32)(Wdg_17_Scu_StmTim0[StmTimerNumber]->U);
  StmConfig.CompareRegVal = StmTimerValue + TimeOutCount;

  /* Update the CMCON,ICR and CMP register*/
  /* MISRA2012_RULE_1_3_JUSTIFICATION: The auto variable StmConfig is  used only
     in read only mode in the local called function as const. Hence, it is not 
     an issue."  */
  Mcu_17_Stm_SetupComparator(&StmConfig);

  return;

} /* Wdg_lStmUpdateCmp */
#endif

/*******************************************************************************
** Traceability     : [cover parentID={EF722DB8-EEE5-4880-BDAD-FDEF0807B6AF}] **
**                                                                            **
** Syntax           : void Wdg_lTimeoutHandler(const WdgIf_ModeType Mode,     **
**                                          const uint16 timeout,             **
**                                          const uint32 CoreId)              **
**                                                                            **
** Description      : This function allow to set "0" as the time frame for    **
**                    triggering which will result in an (almost) immediate   **
**                    stop of the watchdog triggering and an (almost)         **
**                    instantaneous watchdog reset of the ECU.                **
**                    This function also calulates the value of Timeout       **
**                    counter if watchdog SLOW-MODE or FAST-MODE is requested **
**                    and resets if OFF-MODE is requested                     **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : Mode : Mode to which the WDG to be switched             **
** **                 timeout :Timeout period (in milliseconds)               **
**                               used to calculate Wdg_TimeoutCounter,        **
**                    CoreId :Id of the core                                  **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
*******************************************************************************/
static void Wdg_lTimeoutHandler
(const WdgIf_ModeType Mode, const uint16 timeout, const uint32 CoreId)
{
  /* Time elapsed in ms relative to the last notification */
  uint32 TimeInms;
  /* Local variable to hold the value of Watchdog Timer Control Register */
  uint32 WdtCon0;
  uint32 PasswordAccess;
  uint32 ModifyAccess;
  /* If an immediate stop of the watchdog triggering and an instantaneous
     watchdog reset of the ECU is requested - WDG140: */
  /* [cover parentID={389C4956-EB03-4c76-96C4-FBED19B970E4}]
   If timeout is 0[/cover] */
  if(timeout == 0U)
  {
    /* Enter critical section */  
    /*Enter Critical section for CPU ENDINIT*/
    /* [cover parentID={B6900D37-0904-4017-BCF8-BFB6A08E8EAE}][/cover] */
    /* [cover parentID={A8B9B338-BFD3-4138-8EF4-E5B8A500E45D}][/cover] */
    SchM_Enter_Wdg_17_Scu_CpuEndInit();
    /* Read the current value of Watchdog Timer Control Register */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
     * by violating this MISRA rule, as the pointer to the object type
     * it is getting cast into is a known type . */
    WdtCon0 = (uint32)WDG_REGMAP[CoreId].CON0.U;
    /* Servicing the Watchdog Timer is performed in two steps, a Valid Password
     Access followed by a Valid Modify Access */
    /* PASSWORD ACCESS */
    /* [cover parentID={B3DCC492-0C49-4b4f-9367-C9F1A7F54A2E}]
      Access Password[/cover] */
    PasswordAccess = Wdg_lAccessPassword(WdtCon0);
    /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
     * by violating this MISRA rule, as the pointer to the object type
     * it is getting cast into is a known type . */
    /* [cover parentID={75A82982-982A-451c-8E73-C672ABEDE132}]
      Clear ENDINIT, LOCK bit with the Password[/cover] */
    WDG_REGMAP[CoreId].CON0.U = (uint32)PasswordAccess;
    /* MODIFY ACCESS */
    /* [cover parentID={648B21C6-B925-4b9b-BFAE-FC9B69528D25}]
     Modify the Access[/cover] */
    ModifyAccess = Wdg_lModifyAccessPassword(PasswordAccess);
    /* [cover parentID={AEAC53E1-D95A-41bf-BF8E-60B367E36CFD}]
     Calculate Reload Value to do an immediate reset[/cover] */
    ModifyAccess |= Wdg_lReloadModifyAccess(WDG_INSTANT_RESET_RELOAD_VALUE);
    /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
     * by violating this MISRA rule, as the pointer to the object type
     * it is getting cast into is a known type . */
    /* [cover parentID={4C61207D-F072-4f46-AC6A-731ED77E2CEA}]
      Set the ENDINIT and LOCK bit and Reload value by using the Password
      [/cover] */
    WDG_REGMAP[CoreId].CON0.U = ModifyAccess;
    /* As user wants a reset, update the watchdog Timeout Counter,
     so that Watchdog hardware timer will not be reloaded
     in the next call of Wdg_17_Scu_Cbk_GtmNotificationSRV */

    /* [cover parentID={E8F98EFB-318C-4b70-B08C-88D489E7E4FF}]
     Update the Core Specific Wdg drive timeout counter value to
     the reset value[/cover] */
    Wdg_17_Scu_Status[CoreId]->Wdg_TimeoutCounter = WDG_COUNTER_RESET_VALUE;
    /* [cover parentID={CD5F9837-C2D4-40ef-9C7F-80BE870687AD}]
      Exit Critical section for CPU ENDINIT[/cover] */
    /* [cover parentID={A8B9B338-BFD3-4138-8EF4-E5B8A500E45D}][/cover] */
    SchM_Exit_Wdg_17_Scu_CpuEndInit();
  }
  else
  { 
    switch(Mode)
    {
      /* Reset Timeout counter if watchdog OFF_Mode is requested */
      /* [cover parentID={4834AEFA-A36F-4e24-83E7-252FF3F66FBB}]If Mode is OFF
      [/cover] */    
      case WDGIF_OFF_MODE:
      {
        /* As user wants OFF mode, update the watchdog Timeout Counter,
           so that Watchdog hardware timer will not be reloaded
           in the next call of the ISR */
        /* [cover parentID={2F17A4FE-426F-4897-BBE2-649171F5F40D}]
           Update the timeout counter to 0[/cover] */
        Wdg_17_Scu_Status[CoreId]->Wdg_TimeoutCounter = WDG_COUNTER_RESET_VALUE;
        break;
      }
      /* Calculate Timeout counter when Watchdog SLOW Mode is requested */
      /* [cover parentID={4CE029E1-B9A7-4b6a-9216-8B9AAB496D1D}]If Mode is SLOW
      [/cover] */
      case WDGIF_SLOW_MODE:
      {
        /* Convert the timeout into count of refresh time */
        /* [cover parentID={9386D7A5-BD14-4f08-82FF-067151708F24}]
          Convert the timeout into count of slow refresh time[/cover] */
        TimeInms = (Wdg_ConfigPtr[CoreId]->SlowModeRefreshTime);
        /* [cover parentID={E65E0EB0-83B7-4c0b-9E83-7A77C11ED67B}]
           Update the timeout counter for the core specific Wdg[/cover] */
        Wdg_17_Scu_Status[CoreId]->Wdg_TimeoutCounter = 
            (uint16)(timeout / TimeInms);
        break;
      }
      /* Calculate Timeout counter when Watchdog Fats Mode is requested */
      /* [cover parentID={C6FFE641-B45A-4dee-8E37-A387BDF6A966}]If mode is FAST
         [/cover] */
      default: /* WDGIF_FAST_MODE */     
      {
        /* Convert the timeout into count of refresh time */
        /* [cover parentID={5376D769-7466-4abb-AB3B-274EB1BE0783}]
           Convert the timeout into count of fast refresh time[/cover] */
        TimeInms = Wdg_ConfigPtr[CoreId]->FastModeRefreshTime;
        /* [cover parentID={62A0D1FF-B128-4f9c-800B-2391BF488715}]
           Update the timeout counter for the core specific Wdg[/cover] */
        Wdg_17_Scu_Status[CoreId]->Wdg_TimeoutCounter = 
            (uint16)(timeout / TimeInms);
        break;
      }
    }
  }
  return;

}/* End of Wdg_lTimeoutHandler */

/* [cover parentID={084EB343-4D2E-4cc2-9A68-90D5EC3A924A}]
If DET Check or Safety Error check is enabled[/cover] */
#if ((WDG_17_SCU_DEV_ERROR_DETECT == STD_ON)||\
     (WDG_17_SCU_SAFETY_ENABLE == STD_ON))
/*******************************************************************************
** Traceability     : [cover parentID={FD35D658-D468-4fe7-9146-37548336F824}] **
**                                                                            **
** Syntax           : Std_ReturnType Wdg_lSetModeDetCheck                     **
**                    (const WdgIf_ModeType Mode,const uint32 CoreId)         **
**                                                                            **
** Description      : This function checks  the DET's during Mode Change      **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : Mode : Mode to which the WDG to be switched             **
**                    CoreId :Id of the core                                  **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK or E_NOT_OK                                        **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Wdg_lSetModeDetCheck
(const WdgIf_ModeType Mode, const uint32 CoreId)
{ /*, const uint32 CoreId*/
  /* Flag to indicate any DET Error. */
  Std_ReturnType ErrorFlag = E_NOT_OK;
  /*Check if the Driver is initialized .If not so, report to DET */
  /* [cover parentID={BAC57EC1-1CA7-4907-8CDB-DF5368C1CFFB}]If driver state is
   not IDLE[/cover] */
  /* [cover parentID={BAC57EC1-1CA7-4907-8CDB-DF5368C1CFFB}]
   If driver state is not IDLE[/cover] */
  if ( Wdg_17_Scu_Status[CoreId]->Wdg_17_Scu_DriverState != WDG_17_SCU_IDLE)
  {
    /* Report to DET WDG_17_SCU_E_DRIVER_STATE */
    /* [cover parentID={9EEAAE6D-0081-4852-8798-2845D39B00FE}]
     Report to DET WDG_17_SCU_E_DRIVER_STATE[/cover] */
    Wdg_lReportError(WDG_17_SCU_SID_SETMODE, WDG_17_SCU_E_DRIVER_STATE);
    /* Update the Error Flag as E_NOT_OK */
    /* [cover parentID={A990441A-6EE0-4138-8BCB-02AC9321C7C6}]
      Update the Error Flag as E_NOT_OK[/cover] */
    ErrorFlag = E_NOT_OK;
  }
  /* If Mode is within allowed range */
  /* [cover parentID={E574C6FD-9639-4c23-AEBA-98C0D1490FC2}]
   If Mode is within allowed range[/cover] */
  else if ( !((Mode == WDGIF_SLOW_MODE) ||
              (Mode == WDGIF_FAST_MODE) ||
              (Mode == WDGIF_OFF_MODE)) )
  {
    /* Report to DET WDG_17_SCU_E_PARAM_MODE */
    /* [cover parentID={C3EF09DD-D158-4f69-87B9-F1F4360590FA}]
      Report DET WDG_17_SCU_E_PARAM_MODE[/cover] */
    /* [cover parentID={60736B45-B9EB-4d35-9B54-F4A4B23064E2}]
     Report to DET WDG_17_SCU_E_PARAM_MODE[/cover] */
    Wdg_lReportError(WDG_17_SCU_SID_SETMODE, WDG_17_SCU_E_PARAM_MODE);
    /* Update the Error Flag as E_NOT_OK */
    /* [cover parentID={A990441A-6EE0-4138-8BCB-02AC9321C7C6}]
     Update the Error Flag as E_NOT_OK[/cover] */
    ErrorFlag = E_NOT_OK;
  }
  /* If the Slow and Fast mode reload values are out of the boundary
    with respect to 16 bit REL value in CON1 */
  /* [cover parentID={EA75ED17-B358-4a19-9DD5-1D5B5316B2E0}]
   If the Slow and Fast mode reload values are out of the boundary
   with respect to 16 bit REL value in CON1[/cover] */
  else if((Wdg_ConfigPtr[CoreId]->SlowModeReloadValue > 0xFFFEU) || 
          (Wdg_ConfigPtr[CoreId]->FastModeReloadValue > 0xFFFEU))
  {
    /* Report DET WDG_17_SCU_E_PARAM_MODE */
    Wdg_lReportError(WDG_17_SCU_SID_SETMODE, WDG_17_SCU_E_PARAM_MODE);
    /* [cover parentID={A990441A-6EE0-4138-8BCB-02AC9321C7C6}]
      Update the Error Flag as E_NOT_OK[/cover] */
    ErrorFlag = E_NOT_OK;
  }
  else
  {
    /* Update the Error Flag */
    ErrorFlag = E_OK;
  }
  return ErrorFlag;
}/* End of Wdg_lSetModeDetCheck*/

#endif
/*******************************************************************************
** Traceability     : [cover parentID={55D1F4AD-5846-4571-9590-84D90936B5E9}] **
**                                                                            **
** Syntax           : void Wdg_lInit(const uint32 CoreId)                     **
**                                                                            **
** Description      : This function initializes WDGx                          **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : CoreId :Id of the core                                  **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
*******************************************************************************/
static void Wdg_lInit(const uint32 CoreId)
{
  /* Variables for WDG init */
  Std_ReturnType ReturnValue = E_NOT_OK;
  uint32 OldPassword;
  /* [cover parentID={5916817D-2A1B-4947-8D00-3ECAF8B18A7D}]
  If Safety error check is enabled
  [/cover] */
  /* If Safety error check is enabled */
  #if(WDG_17_SCU_SAFETY_ENABLE == STD_ON)
  /*If the driver state is  BUSY*/
  /* [cover parentID={16CB69BA-994D-4215-BC95-44F0CD78C265}]
   If State of the driver is BUSY
   [/cover] */
  if(Wdg_17_Scu_Status[CoreId]->Wdg_17_Scu_DriverState == WDG_17_SCU_BUSY)
  {
    /*Report Safety Error WDG_17_SCU_E_BUSY*/
    /* [cover parentID={4A8E9AD1-1B90-445d-A047-1903D3C75511}]
    Report Safety Error WDG_17_SCU_E_BUSY
    [/cover] */
    Wdg_lReportError(WDG_17_SCU_SID_INIT, WDG_17_SCU_E_BUSY);
  }
  else
  #endif
  {
    /* Update driver state to UNINIT for the Wdg of a specific core*/
    /* [cover parentID={E6719476-4728-421e-A349-9CEE70C675B0}]
       Update driver state to UNINIT for the Wdg of a specific core
       [/cover] */
    Wdg_17_Scu_Status[CoreId]->Wdg_17_Scu_DriverState = WDG_17_SCU_UNINIT;

    /* Update driver mode to OFF for the Wdg of a specific core */
    /* [cover parentID={42C84F37-6EC8-45e5-B83C-900C3D6E2742}]
      Update driver mode to OFF for the Wdg of a specific core
      [/cover] */
    Wdg_17_Scu_Status[CoreId]->Wdg_17_Scu_DriverMode = WDGIF_OFF_MODE;

    /* Update the Password in the CON0 Register to User Specified Password*/
    /* [cover parentID={A02D338B-9E10-4d4b-8BA3-2C7BBB0CE95B}]
      Update the Password to the user configured value of the current core
      [/cover] */
    OldPassword = Mcal_SetCpuWdgPassword(Wdg_ConfigPtr[CoreId]->WdgPassword);

    if(OldPassword != Wdg_ConfigPtr[CoreId]->WdgPassword)
    {
      /*Do Nothing.*/
    }
    /* Retrieve the Password set and check if it is same as
       configured by user*/
    /* [cover parentID={6DB2AA89-7459-48ad-A817-F1842625FA65}]
       Retrieve the Password set[/cover] */
    /* [cover parentID={61A4CB52-DAF3-4985-A8E8-1EAAE634A7F0}]
       If the password set is same as the user configured?[/cover] */
    if(Mcal_GetCpuWdgPassword() == Wdg_ConfigPtr[CoreId]->WdgPassword)
    {
      /*Update Return Value as E_OK*/
      /* [cover parentID={E7B31EC6-5216-4b36-BF20-D30273D42B45}]
         Update Return Value as E_OK[/cover] */
      ReturnValue = E_OK;
    }
    else
    {
      /*Update Return Value as E_NOT_OK*/
      /* [cover parentID={EA641382-016E-4733-96BA-26FF76A534AA}]
         Update Return Value as E_NOT_OK[/cover] */
      ReturnValue = E_NOT_OK;
    }
    /* [cover parentID={DE2F78F1-832C-448f-857A-E320F4F2D18B}]
       If Return Value is E_OK[/cover] */
    /*If Return Value is E_OK */
    if(ReturnValue == E_OK)
    {
      /* If the default mode is OFF and WDG Disable is not allowed */
      /* [cover parentID={312CEF5C-FD0C-4f47-BF55-724ECA22D414}]
          If the default mode is OFF and WDG Disable is not allowed
          [/cover] */
      if((Wdg_ConfigPtr[CoreId]->WdgDisableAllowed == FALSE) &&
          (Wdg_ConfigPtr[CoreId]->DefaultMode == WDGIF_OFF_MODE))
      {
        /*If Production error is Enabled */
        #if (WDG_17_SCU_DISABLE_REJECT_DEM_REPORT == WDG_17_SCU_ENABLE_DEM_REPORT)
        /* Raise a Production error WDG_17_SCU_E_DISABLE_REJECTED FAILED */
        /* [cover parentID={F3B5C155-3F68-4ca7-B847-949B7C0F3C5C}]
             Raise a Production error WDG_17_SCU_E_DISABLE_REJECTED FAILED[/cover] */
        Wdg_lReportDemError
        ((Dem_EventIdType)WDG_17_SCU_E_DISABLE_REJECTED,
        DEM_EVENT_STATUS_FAILED);
        #endif
        /* Update Return Value as E_NOT_OK */
        /* [cover parentID={C3D73E5B-E6D5-4922-AF6C-330B3A23FCC6}]
             Update Return Value as E_NOT_OK
             [/cover] */
        ReturnValue = E_NOT_OK;
      }
      /* If the default mode is OFF and WDG Disable is allowed */
      else
      {
        /* If Production error is Enabled */
        #if (WDG_17_SCU_DISABLE_REJECT_DEM_REPORT == \
        WDG_17_SCU_ENABLE_DEM_REPORT)
        /*Raise a Production error WDG_17_SCU_E_DISABLE_REJECTED PASSED */
        /* [cover parentID={B1BDF833-C90D-4b25-9D16-ADA8B4B619CA}]
            Raise a Production error WDG_17_SCU_E_DISABLE_REJECTED PASSED[/cover] */
        Wdg_lReportDemError
        ((Dem_EventIdType)WDG_17_SCU_E_DISABLE_REJECTED,
        DEM_EVENT_STATUS_PASSED);
        #endif
        ReturnValue = E_OK;
      }

    }
    /*If Return value is E_OK (Wdg disable and OFF mode switch is allowed*/
    /* [cover parentID={CEBE784B-B141-4598-B6C7-A6996DA3C71F}]
       If Return Value is E_OK[/cover] */
    if(ReturnValue == E_OK)
    {
      /* Set WDG to the given Mode. Available modes are OFF_MODE,
          SLOW_MODE and FAST_MODE */
      /* [cover parentID={F08A263E-6EAA-4f92-91EB-1BEF6162323A}]
          Set WDG to the given Mode. Available modes are OFF_MODE,
          SLOW_MODE and FAST_MODE
          [/cover] */
      ReturnValue = Wdg_lChangeMode
                    (Wdg_ConfigPtr[CoreId]->DefaultMode, WDG_17_SCU_SID_INIT, CoreId);
      /* If Return value is E_OK (Check if there was an error
          during mode switching) */
      /* [cover parentID={FD5E92D5-E845-485b-AE94-2FA5981CD50B}]
          If Return value is not E_OK
          (Check if there was an error during mode switching)
          [/cover] */
      if (ReturnValue != E_OK)
      {
        /* Reset the core specific Wdg_TimeoutCounter */
        Wdg_17_Scu_Status[CoreId]->Wdg_TimeoutCounter = WDG_COUNTER_RESET_VALUE;           
        /*If Production error is enabled */
        #if (WDG_17_SCU_MODE_FAIL_DEM_REPORT == WDG_17_SCU_ENABLE_DEM_REPORT)
        /* Raise Production error WDG_17_SCU_E_MODE_FAILED FAILED*/
        /* [cover parentID={4A95F89B-AB8A-4ee5-A60E-CEEC00575ACC}]
            Raise Production error WDG_17_SCU_E_MODE_FAILED FAILED[/cover] */
        Wdg_lReportDemError((Dem_EventIdType)WDG_17_SCU_E_MODE_FAILED,
                              DEM_EVENT_STATUS_FAILED);
        #endif
        /* if DET and SAFETY is enabled  */
        /* [cover parentID={8E20FD4E-C308-4e79-BA8C-1A9A0D5F3F45}]
            if DET and SAFETY is enabled
            [/cover] */
        #if ((WDG_17_SCU_DEV_ERROR_DETECT==STD_ON) || (WDG_17_SCU_SAFETY_ENABLE==STD_ON))
        /*Report DET or Safety Error  WDG_17_SCU_E_PARAM_CONFIG */
        /* [cover parentID={82C26881-7E6B-4198-AF1B-58103F59E9B5}]
            Report DET or Safety Error  WDG_17_SCU_E_PARAM_CONFIG[/cover] */
        Wdg_lReportError(WDG_17_SCU_SID_INIT, WDG_17_SCU_E_PARAM_CONFIG);
        #endif
      } /* End of '(ReturnValue != E_OK)'*/

      else /*Mode Change was successful*/
      {
        /* if Production error is Enabled */
        #if (WDG_17_SCU_MODE_FAIL_DEM_REPORT == WDG_17_SCU_ENABLE_DEM_REPORT)
        /* Raise Production error WDG_17_SCU_E_MODE_FAILED PASSED */
        /* [cover parentID={0A1AE50E-92B7-4443-BD2E-D07AC5E1F7D7}]
            Raise Production error WDG_17_SCU_E_MODE_FAILED PASSED[/cover] */
        Wdg_lReportDemError((Dem_EventIdType)WDG_17_SCU_E_MODE_FAILED,
                              DEM_EVENT_STATUS_PASSED);
        #endif
        /* Calculate the initial timeout counter of the core specific
             WdgCalculate the timeout counter */
        /* [cover parentID={A2B32AE6-B892-4968-A297-B38502F59717}]
            Calculate the initial timeout counter of the core specific Wdg
            [/cover] */
        Wdg_lTimeoutHandler(Wdg_ConfigPtr[CoreId]->DefaultMode,
                            Wdg_ConfigPtr[CoreId]->InitialRefreshTime, CoreId);

        /*Stop or Start the timer for the Core specific Wdg*/
        /* [cover parentID={CC4AFE75-116F-4c5b-B609-0C49914E6E8C}]
             Stop or Start the timer for the Core specific Wdg
             [/cover] */
        Wdg_lStartOrStopTimeEngine(Wdg_ConfigPtr[CoreId]->DefaultMode,CoreId);
                                   
        /* Set Driver State to IDLE */
        /* [cover parentID={8F701D85-7BA2-441a-A440-6B63E96C9FEA}]
            Set Driver State to IDLE [/cover] */
        Wdg_17_Scu_Status[CoreId]->Wdg_17_Scu_DriverState = WDG_17_SCU_IDLE;

        /* Update the current mode of Wdg driver */
        /* [cover parentID={BE8217B8-73D7-4df7-9796-141EEDE71DD7}]
            Update the current mode of Wdg driver
            [/cover] */
        Wdg_17_Scu_Status[CoreId]->Wdg_17_Scu_DriverMode = 
            Wdg_ConfigPtr[CoreId]->DefaultMode;
      }  /* End of '(ReturnValue == E_OK)' */
    }
  }
  return;
}/* End of Wdg_lInit */


#if ((WDG_17_SCU_DEV_ERROR_DETECT == STD_ON) || (WDG_17_SCU_SAFETY_ENABLE == STD_ON))
/*******************************************************************************
** Traceability     : [cover parentID={92C75E16-61C3-4c57-B556-1DA876D6468F}] **
**                                                                            **
** Syntax           : Std_ReturnType Wdg_lInitDetCheck                        **
**                            (const Wdg_17_Scu_ConfigType* const ConfigPtr,  **
**                             const uint32 CoreId)                           **
**                                                                            **
** Description      : This function checks  the DET's during Initialization   **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : ConfigPtr : Configuration pointer                       **
**                    CoreId :Id of the core                                  **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK or E_NOT_OK                                        **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Wdg_lInitDetCheck
(const Wdg_17_Scu_ConfigType* const ConfigPtr,
 const uint32 CoreId)
{
  /* Flag to indicate any DET/Production Error. */
  Std_ReturnType ErrorFlag = E_NOT_OK;

  /* Check if the configuration set passed as a input parameter is a NULL_PTR.
      If so, report DET */
  /* [cover parentID={1A56FC6E-FF9E-45ab-8886-E3BB7C38231A}]
   If CfgPtr is NULL[/cover] */
  if (ConfigPtr == NULL_PTR)
  {
    /* Raise a DET or Safety error WDG_17_SCU_E_INIT_FAILED */
    /* [cover parentID={F9EE1F5B-963E-4a45-AD1E-403283FC43C9}]
     Raise a DET or Safety error WDG_17_SCU_E_INIT_FAILED
     [/cover] */
    Wdg_lReportError(WDG_17_SCU_SID_INIT, WDG_17_SCU_E_INIT_FAILED);
    /* [cover parentID={AEA3F825-7B7A-4cda-AA59-BDB82AEA14DA}]
      Update Error Flag to E_NOT_OK[/cover] */
    ErrorFlag = E_NOT_OK;
  }
  /* Check if the configuration set passed for the current core.
     If not so, report to DET */
  /* [cover parentID={96C747A5-6C82-4e2d-A20E-53E8122C9445}]
   If Core Id is not same as the current Core Id[/cover] */
  else if(ConfigPtr->WdgCoreID != CoreId)
  {
    /* Raise a DET or Safety error WDG_17_SCU_E_PARAM_CONFIG */
    /* [cover parentID={0802BF45-E6D8-4f10-8A5F-BB56A28BE484}]
      Wdg Driver - Multi-core & Single-core Support[/cover] */
    /* [cover parentID={FC8D1659-4CF3-4b05-8FDE-CA8DC385F34A}]
     Raise a DET or Safety error WDG_17_SCU_E_PARAM_CONFIG[/cover] */
    Wdg_lReportError(WDG_17_SCU_SID_INIT, WDG_17_SCU_E_PARAM_CONFIG);
    /* [cover parentID={964CE218-FCA4-4490-A73D-0FEEC4B696C4}]
     Update Error Flag to E_NOT_OK[/cover] */
    ErrorFlag = E_NOT_OK;
  }
  else
  {
    /* Flag to no error */
    /* [cover parentID={51B233C5-653D-4f84-9740-0E5DF014EC83}]
      Update Error Flag to E_OK[/cover] */
    ErrorFlag = E_OK;
  }
  return ErrorFlag ;

}/* End of Wdg_lInitDetCheck */
#endif

#if (WDG_17_SCU_INIT_CHECK_API== STD_ON)
/*******************************************************************************
** Traceability     :[cover parentID={9AC9F000-73C6-4a9e-837B-C02A1A088145}]  **
**                                                                            **
** Syntax           : Std_ReturnType Wdg_lSfrInitCheck                        **
**                      (const Wdg_17_Scu_ConfigType* const ConfigPtr,        **
**                       const uint32 CoreId,                                 **
**                       const WdgIf_ModeType Mode)                           **
**                                                                            **
** Description      : This function checks if the SFRs are same as expected   **
**                    after initialization                                    **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : ConfigPtr : Configuration pointer                       **
**                    CoreId :Id of the core                                  **
**                    Mode : Mode of the Wdg                                  **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK or E_NOT_OK                                        **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Wdg_lSfrInitCheck
(const Wdg_17_Scu_ConfigType* const ConfigPtr,
 const uint32 CoreId,
 const WdgIf_ModeType Mode)
{
  Std_ReturnType ReturnValue = E_NOT_OK;
  uint32 WdgCon1;
  uint16 ReloadValue;
  #if(WDG_17_SCU_TRIG_SELECT == WDG_17_SCU_GTM_TIMER)
  const Mcu_17_Gtm_TomAtomChConfigType *GtmChConfig;
  #else
  const Mcu_17_Stm_TimerConfigType *StmConfig;
  StmConfig = ConfigPtr->WdgStmConfig;

  #endif
  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* Retrieve Clock divider value */
  WdgCon1 = WDG_REGMAP[CoreId].CON1.U;
  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* Retrieve Reload value */
  ReloadValue = WDG_REGMAP[CoreId].CON0.B.REL;
  /*If the password set is same as the password in config pointer*/
  /* [cover parentID={36AA6C7D-B72D-426e-95BF-678E58E3F4AD}]
   If the password set is same as the password in config pointer[/cover] */
  if(Mcal_GetCpuWdgPassword() == ConfigPtr->WdgPassword)
  {
    switch(Mode)
    { /*If mode is OFF */
      /* [cover parentID={823CB8C3-9738-4416-A6DE-4121CC2B1E59}]
          If Mode is OFF[/cover] */
      case WDGIF_OFF_MODE:
      {
        /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side
             effects foreseen by violating this MISRA rule, as the
             pointer to the object type
             * it is getting cast into is a known type . */
        /*If DS bit in the SR register is enabled */
        /* [cover parentID={85EDF754-7832-44c5-A80A-572660F9D966}]
             If DS bit in the SR register is Enabled[/cover] */
        if(1U == (uint8)WDG_REGMAP[CoreId].SR.B.DS)
        {
          /* Update the return value to E_OK */
          /* [cover parentID={8FCBE659-E062-476a-A032-A55A54451F15}]
                 Update the return value to E_OK[/cover] */
          ReturnValue = E_OK;
        }

        break;
      }
      /* If Mode is SLOW*/
      /* [cover parentID={FE6F55F3-CDDE-49af-97BA-D0A9FB2123D0}]
          If Mode is Slow[/cover] */
      case WDGIF_SLOW_MODE:
      {
        /* If Reload Value is same as config pointer in REL bits of
            CON0 register and If the Clock Divider Values are same as
            config pointer  in the SR register */
        /* [cover parentID={64C6F82A-6665-4c61-BEA8-A68F19C53752}]
            If Reload Value and clock divider is as expected[/cover] */
        if (((WdgCon1 & WDG_STATUS_MASK) == WDG_RESET_WDTIR_RESET_WDTDR) && 
            (ReloadValue >= ConfigPtr->SlowModeReloadValue))
        {
          /* If GTM Timer is selected */
          #if(WDG_17_SCU_TRIG_SELECT == WDG_17_SCU_GTM_TIMER)

          GtmChConfig = &(ConfigPtr->WdgGtmTimerInfo[0]);
          /* If  it is TOM Channel */
          /* [cover parentID={EFC375E6-6A12-4b64-B687-18B8BBC7FB09}]
                If TOM Channel
                [/cover] */
          if(GtmChConfig->TimerType == MCU_GTM_TIMER_TOM)
          { /* Update the Return value by calling the Tom init check */
            /* [cover parentID={598478D7-E7E3-4275-81F9-8A41855AE8EA}]
                   Update the Return value by calling the Tom init check
                   [/cover] */
            ReturnValue = Mcu_17_Gtm_TomChInitCheck(GtmChConfig);
          }

          else  /* ATOM channel module is selected*/
          { /* Update the Return value by calling the Atom init check */
            /* [cover parentID={1C6B854B-9979-496d-A955-CA3F202882AA}]
                   Update the Return value by calling the Atom init check
                   [/cover] */
            ReturnValue = Mcu_17_Gtm_AtomChInitCheck(GtmChConfig);
          }
          #else
          /* STM Timer slected. Update the Return value by calling the
                Stm init check */
          /* [cover parentID={73F26381-5D6B-449d-9F02-8521AA6368E0}]
                Update the Return value by calling the Stm init check
                [/cover] */
          ReturnValue =
            Mcu_17_Stm_CheckComparator(StmConfig);
          #endif
        }
        break;
      }
      /*If Mode is OFF*/
      /* [cover parentID={EC79731F-33A1-4f84-89D2-C7FBA98B74D9}]
          If Mode is FAST
          [/cover] */
      default: /* WDGIF_FAST_MODE */      
      {
        /* If Reload Value is same as config pointer in REL bits of
             CON0 register and If the Clock Divider Values are same as
             config pointer in the SR register */
        /* [cover parentID={03C640BC-ACA5-4338-858A-9316A34896EE}]
            If Reload Value and clock divider is as expected[/cover] */
        if (((WdgCon1 & WDG_STATUS_MASK) == WDG_SET_WDTIR_RESET_WDTDR) && 
            (ReloadValue >= ConfigPtr->FastModeReloadValue))
        {
          /*If GTM timer is chosen*/
          #if(WDG_17_SCU_TRIG_SELECT == WDG_17_SCU_GTM_TIMER)
          GtmChConfig = &(ConfigPtr->WdgGtmTimerInfo[1]);
          /* ATOM/TOM channel module is enabled*/
          /* check if it is TOM Channel */
          /* [cover parentID={13D8A9DC-EBCC-41cb-8AE7-77C9CD91D391}]
                If TOM Channel[/cover] */
          if(GtmChConfig->TimerType == MCU_GTM_TIMER_TOM)
          {
            /* [cover parentID={1DC61C2A-DC87-4707-B429-AE14794C168B}]
            Update the Return value by calling the Tom init check
            [/cover] */
            ReturnValue = Mcu_17_Gtm_TomChInitCheck(GtmChConfig);
          }
          else  /* ATOM channel module is selected*/
          {
            /* [cover parentID={3DF652F9-45E3-43c8-A3C6-651734D8F962}]
                  Update the Return value by calling the Atom init check
                  [/cover] */
            ReturnValue = Mcu_17_Gtm_AtomChInitCheck(GtmChConfig);
          }
          #else
          /* [cover parentID={FDB97E14-8336-4388-A778-D474316BCD62}]
                Update the Return value by calling the Stm init check
                [/cover] */
          ReturnValue =
            Mcu_17_Stm_CheckComparator(StmConfig);
          #endif
        }
        break;
      }     
    }
  }
  return ReturnValue;

}

/*******************************************************************************
** Traceability     :[cover parentID={CC63077D-0C19-4fda-9838-1E4661FD5319}]  **
**                                                                            **
** Syntax           : Std_ReturnType Wdg_lVarInitCheck                        **
**                      (const Wdg_17_Scu_ConfigType* const ConfigPtr,        **
**                       const uint32 CoreId,                                 **
**                       const WdgIf_ModeType Mode)                           **
**                                                                            **
** Description      : This function checks if the globals are same as         **
**                    expected after initialization                           **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : ConfigPtr : Configuration pointer                       **
**                    CoreId :Id of the core                                  **
**                    Mode : Mode of the Wdg                                  **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK or E_NOT_OK                                        **
**                                                                            **
*******************************************************************************/
static Std_ReturnType  Wdg_lVarInitCheck
(const Wdg_17_Scu_ConfigType* const ConfigPtr,
 const uint32 CoreId,
 const WdgIf_ModeType Mode)
{
  Std_ReturnType ReturnValue = E_NOT_OK;
  /*If the address of ConfigPtr is same as the Wdg_ConfigPtr*/
  /* [cover parentID={C58CB898-948F-43e2-941E-EE9DA5A8CC8E}]
   If the address of the config pointer is same as the Wdg Config pointer
   [/cover] */
  if((ConfigPtr == Wdg_ConfigPtr[CoreId]) && 
     /*If mode of the driver is same as default mode in config pointer*/
    (Wdg_17_Scu_Status[CoreId]->Wdg_17_Scu_DriverMode == ConfigPtr->DefaultMode))
  {
    switch(Mode)
    {
      /*If Mode is OFF */
      /* [cover parentID={5E216164-22F8-4afd-8E58-31700F270F71}]
          If Mode is OFF
          [/cover] */
      case WDGIF_OFF_MODE:
      {
        /* [cover parentID={2B17D8D4-5F0B-4f26-83D4-13CFCE9B3974}]
             If timeout counter is equal to reset value and
             If reload value is equal to reset value and
             If mode of the driver is same as default mode in config pointer
             [/cover] */
        /*If timeout counter is equal to reset value*/
        if((Wdg_17_Scu_Status[CoreId]->Wdg_TimeoutCounter ==
            WDG_COUNTER_RESET_VALUE) && 
            /*If reload value is equal to reset value*/
           (Wdg_17_Scu_Status[CoreId]->Wdg_CurrentReloadValue ==
             WDG_RELOAD_RESET_VALUE))
        {
          /*Update return value as E_OK*/
          /* [cover parentID={F269D473-9165-4863-BA8A-2EEC998ECB7D}]
            Update return value as E_OK[/cover] */
          ReturnValue = E_OK;
        }
        break;
      }
      /*If Mode is SLOW */
      /* [cover parentID={C57DE141-636D-4f3f-9526-BB21E85B158C}]
          If Mode is SLOW[/cover] */
      case WDGIF_SLOW_MODE:
      { /* [cover parentID={22064D86-6703-4383-80BD-3476B201DB1A}]
           If current reload value is equal to slow mode reload value and
           If mode of the driver is same as default mode in config pointer
           [/cover] */
        /* If current reload value is equal to slow mode reload value */
        if((Wdg_17_Scu_Status[CoreId]->Wdg_CurrentReloadValue ==
            ConfigPtr->SlowModeReloadValue))
        {
          /*Update return value as E_OK*/
          /* [cover parentID={7D25FF85-B31A-46d1-84CE-49D4F4EFCFAD}]
                Update return value as E_OK
                [/cover] */
          ReturnValue = E_OK;
        }
        break;
      }
      /* cover parentID={C57DE141-636D-4f3f-9526-BB21E85B158C}]
          If Mode is FAST
          [/cover] */
      default: /* WDGIF_FAST_MODE */
      {
        /* [cover parentID={76D4006F-D7A3-40ff-B70C-E499C20D5747}]
             If current reload value is equal to fast mode reload value and
             If mode of the driver is same as default mode in config pointer
             [/cover] */
        /* If current reload value is equal to fast mode reload value */
        if((Wdg_17_Scu_Status[CoreId]->Wdg_CurrentReloadValue ==
            ConfigPtr->FastModeReloadValue))
        {
          /*Update return value as E_OK*/
          /* [cover parentID={25985009-8C94-4af0-9CB2-20E6F16C3C55}]
                Update return value as E_OK[/cover] */
          ReturnValue = E_OK;
        }
        break;
      }
    }
  }
  /* [cover parentID={857551A5-953B-4c4e-BF76-340CD4A9219D}]Merge[/cover] */
  return ReturnValue;
}
#endif

/*******************************************************************************
** Traceability     : [cover parentID={759A219D-CE80-40a4-A964-7F681452BDA6}] **
**                                                                            **
** Syntax           :LOCAL_INLINE uint32 Wdg_lAccessPassword                  **
**                     (const uint32 WdtCon0)                                 **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : WDTCON0 register                                        **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : uint32 (modified wdtCon0)                               **
**                                                                            **
** Description      : Function to Access password before accessing ENDINIT    **
**                      registers                                             **
**                      Password Access:                                      **
**       - (Bits[15:8])Set previous password bits                             **
**       - (Bits[7:2]) calculate the Inverted bits from previous password     **
**       - (Bit[1]) Set WDTLCK to '0' to unlock SCU_WDTCPUx_CON0              **
**       - (Bit[0]) Set ENDINIT bit while password access                     **
**[/cover]                                                                    **
*******************************************************************************/
LOCAL_INLINE uint32 Wdg_lAccessPassword(const uint32 WdtCon0)
{
  uint32 lPasswordAccess;

  /* Keep bits[15:8] as is */
  lPasswordAccess = (uint32)(WdtCon0 & WDT_PASS_UPPER_MASK);

  /* Invert the bits[7:2] */
  lPasswordAccess |= (uint32)((uint32)(~WdtCon0) & WDT_PASS_LOWER_MASK);

  /* Set ENDINIT bit, Clear LCK bit */
  lPasswordAccess |= (uint32)(0x01U);

  /* Update the Reload value */
  lPasswordAccess |= (uint32)(WdtCon0 & WDG_MASK_WDTREL);

  /* CON0 SFR value with new password */
  return lPasswordAccess;

}

/*******************************************************************************
** Traceability     : [cover parentID={5985816A-E7DA-4f35-BEC6-29D074D5C888}] **
** Syntax           : Std_ReturnType Wdg_lCheckPassSeqOrTimeCheck             **
**                                                  (const uint32 CoreId)     **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : CoreId: Id of the core on which code executed           **
**                                                                            **
** Parameters (out) : RetVal                                                  **
**                                                                            **
** Return value     : E_OK/E_NOT_OK                                           **
**                                                                            **
** Description      : Function to Check if  Password Sequencing Or            **
**                    Time Checking is enabled                                **
**[/cover]                                                                    **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Wdg_lCheckPassSeqOrTimeCheck
(const uint32 CoreId)
{
  uint32 PassSeqOrTimeChck;
  Std_ReturnType RetVal = E_NOT_OK;
  /*Create Mask value for Password Auto-sequence Status Flag and
   Timer Check Status Flag bit fields of Status register */
  PassSeqOrTimeChck =
    (uint32)(((uint32)(0x01U) << IFX_SCU_WDTCPU_SR_PAS_OFF) |   
             ((uint32)(0x01U) << IFX_SCU_WDTCPU_SR_TCS_OFF));

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* [cover parentID={1CBBA117-9B45-48c4-9A41-EE0E28A78220}]
    Retrieve the Password Sequence and Time check bit from the
    Wdg Status Register
    [/cover] */
  PassSeqOrTimeChck &= WDG_REGMAP[CoreId].SR.U;
  /* [cover parentID={662DA34E-148E-4c69-B8EA-710C38AF6E74}]
    If Password Sequence and Time check is enabled[/cover] */
  if(PassSeqOrTimeChck != 0U)
  {
    /* Time checking or Password Sequencing enabled */
    /* If Production error Enabled */
    #if (WDG_17_SCU_MODE_FAIL_DEM_REPORT == WDG_17_SCU_ENABLE_DEM_REPORT)
    /* Report Production errors to Mcal_Wrapper - SWS_Wdg_00173 */
    Wdg_lReportDemError((Dem_EventIdType)WDG_17_SCU_E_MODE_FAILED,
                          DEM_EVENT_STATUS_FAILED);
    #endif
    /* [cover parentID={07A4BD92-9B73-4a7d-A43B-046B07FAA3F1}]
      Return Value E_NOT_OK
      [/cover] */
    RetVal = E_NOT_OK;
  }
  else
  {
    /* If Production error Enabled */
    #if (WDG_17_SCU_MODE_FAIL_DEM_REPORT == WDG_17_SCU_ENABLE_DEM_REPORT)
    /* Report Production errors to DEM - SWS_Wdg_00181 */
    Wdg_lReportDemError((Dem_EventIdType)WDG_17_SCU_E_MODE_FAILED,
                          DEM_EVENT_STATUS_PASSED);
    #endif
    /* [cover parentID={8ADBF25A-4CCC-4f8d-A4B3-9F522A5DA38D}]
      Return Value E_OK[/cover] */
    RetVal = E_OK;
  }
  return RetVal;
}

/*******************************************************************************
** Traceability     : [cover parentID={68A07D93-E1FA-4e89-A076-C21CAADD0DFD}] **
**                                                                            **
** Syntax           : Std_ReturnType Wdg_lCheckAccessErrorStatusFlag          **
                                                    (const uint32 CoreId)     **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : CoreId : Current Core Id                                **
**                                                                            **
** Parameters (out) : RetVal                                                  **
**                                                                            **
** Return value     : E_OK/E_NOT_OK                                           **
**                                                                            **
** Description      : Function to Check if  Access Error                      **
**                      flag is enabled                                       **
**[/cover]                                                                    **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Wdg_lCheckAccessErrorStatusFlag(const uint32 CoreId)
{
  uint32 AccessErrorStatusFlag;
  Std_ReturnType ReturnValue = E_NOT_OK;

  /*Create a mask for Access Error Status Flag*/
  AccessErrorStatusFlag =
    (uint32)((uint32)(0x01U) << IFX_SCU_WDTCPU_SR_AE_OFF);
  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /*Retrieve the AccessErrorFlag bit from the Wdg Status Register*/
  AccessErrorStatusFlag &= WDG_REGMAP[CoreId].SR.U;
  /* If Acess Error Status Flag is enabled */
  /* [cover parentID={3F2159F3-2B16-41b1-AFA2-C36F6D3C27CE}]
    If Access Error Status Flag is enabled[/cover] */
  if(AccessErrorStatusFlag != 0U)
  {
    /*If Safety Error is enabled*/
    /* [cover parentID={4467200E-3F14-4dbc-B2B9-DE8C1CB41954}]
      If Safety Error check is Enabled[/cover] */
    #if(WDG_17_SCU_SAFETY_ENABLE==STD_ON)
    /*Report a Safety error WDG_17_SCU_E_ACCESS*/
    /* [cover parentID={5A5FD6FB-601F-4462-8893-6446C195CBB8}]
      Report a Safety error WDG_17_SCU_E_ACCESS[/cover] */
    Wdg_lReportError(WDG_17_SCU_SID_TIMERNOTIF, WDG_17_SCU_E_ACCESS);
    #endif
    /* Update the return value to E_NOT_OK */
    /* [cover parentID={C579CA72-99C4-4ce0-AACC-7D1E8DA5D1A3}]
      Retun Value E_NOT_OK[/cover] */
    ReturnValue = E_NOT_OK;
  }
  else
  {
    /*Update the return value to E_OK*/
    /* [cover parentID={481C12FC-EAE0-4cd3-8DDF-758790A0EFD9}]
      Return Value E_OK[/cover] */
    ReturnValue = E_OK;
  }

  return ReturnValue;

}


/*******************************************************************************
** Traceability     : [cover parentID={02802B87-5643-4798-B5DE-0B0D1A93A06C}] **
**                                                                            **
** Syntax           : Std_ReturnType Wdg_lCheckOverflowErrorStatusFlag        **
                                                        (const uint32 CoreId) **
**                                                                            **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : CoreId : Current Core Id                                **
**                                                                            **
** Parameters (out) : RetVal                                                  **
**                                                                            **
** Return value     : E_OK/E_NOT_OK                                           **
**                                                                            **
** Description      : Function to Check if  Overflow error                    **
                      flag is enabled                                         **
**[/cover]                                                                    **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Wdg_lCheckOverflowErrorStatusFlag
(const uint32 CoreId)
{
  uint32 OverflowErrorFlag;
  Std_ReturnType ReturnValue = E_NOT_OK;
  uint32 PasswordValue;
  /*Create a mask for Overflow Error Status Flag*/
  OverflowErrorFlag = (uint32)((uint32)(0x01U) << IFX_SCU_WDTCPU_SR_OE_OFF);
  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* Retrieve the OverflowErrorFlag bit from the Wdg Status Register */
  OverflowErrorFlag &= WDG_REGMAP[CoreId].SR.U;

   /* [cover parentID={35F9AA05-AB6B-4d6b-B9CB-4DD398ED1070}]
     If overflow flag is enabled[/cover] */
  if(OverflowErrorFlag != 0U)
  {
    /* Retrieve the installed password and set the same back again*/
    PasswordValue = Mcal_SetCpuWdgPassword(Mcal_GetCpuWdgPassword());
    /* If the password value */
    /* [cover parentID={DEA68A93-C64C-4f1f-9981-97B2F1734602}]
     If the insalled password is same as the retrieved password[/cover] */
    if(PasswordValue == Mcal_GetCpuWdgPassword())
    {
      /* [cover parentID={7ABB43FF-AFE4-4edf-B1BA-4CB901D8205E}]
        Do Nothing. The above steps are performed to Clear the OE and AE
        by doing a Valid Modify Access by setting the same installed
        password for the next cycle[/cover] */
      /* Do Nothing. The above steps are performed to Clear the OE and AE
        by doing a Valid Modify Access bet setting the same installed password
        for the next cycle */
    }
    /* If Safety Error is enabled */
    /* [cover parentID={1DAF2396-1B7D-45df-A210-0DAEB2AE16E1}]
     If Safety Error Check is Enabled[/cover] */
    #if(WDG_17_SCU_SAFETY_ENABLE==STD_ON)
    /* Report safety error WDG_17_SCU_E_OVERFLOW */
    /* [cover parentID={5C79E1E2-2A65-4a4c-9729-CD30BE38E1CF}]
     Report safety error WDG_17_SCU_E_OVERFLOW[/cover] */
    Wdg_lReportError(WDG_17_SCU_SID_TIMERNOTIF, WDG_17_SCU_E_OVERFLOW);
    #endif
    /* [cover parentID={D7999B59-FCC9-439b-AA2D-B4DC13163CCF}]
     Retun Value E_NOT_OK[/cover] */
    ReturnValue = E_NOT_OK;
  }
  else
  {
    /* [cover parentID={0D1CCD24-A444-4edd-9D2E-A2A9F7CCC3AC}]
     Return Value E_OK[/cover] */
    ReturnValue = E_OK;
  }

  return ReturnValue;

}

/*******************************************************************************
** Traceability     : [cover parentID={1EF255A9-E62B-4e17-8C9C-D1F1066F8D9C}] **
**                                                                            **
** Syntax     :  LOCAL_INLINE uint32 Wdg_lModifyAccessPassword                **
**                                       (const uint32 PasswordAccess)        **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : PasswordAccess - the password bit field.                **
**                                                                            **
** Parameters (out) : RetVal                                                  **
**                                                                            **
** Return value     : E_OK/E_NOT_OK                                           **
**                                                                            **
** Description      : Function to calculate the password to be                **
**                             put in CON0 SFR                                **
**[/cover]                                                                    **
*******************************************************************************/
LOCAL_INLINE uint32 Wdg_lModifyAccessPassword(const uint32 PasswordAccess)
{
  uint32 ModPasswordAccess;
  /* Calculate only password */
  ModPasswordAccess = (uint32)(PasswordAccess & WDT_PASS_MASK);

  /* Set LCK bit and ENDINIT Bit */
  ModPasswordAccess |= WDT_SETLCK_ENDINIT;

  return ModPasswordAccess;

} /* End of Wdg_lModifyAccessPassword */

/*******************************************************************************
** Traceability     : [cover parentID={2D8F6D5E-823F-42e3-94D5-5EDE681CE2E1}] **
** Syntax           :LOCAL_INLINE uint32 Wdg_lReloadModifyAccess              **
**                                                (const uint16 ReloadValue)  **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : ReloadValue (in ticks)                                  **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : uint32 (modified Value)                                 **
**                                                                            **
** Description      : Function to Modify the ENDINIT registers                **
**[/cover]                                                                    **
*******************************************************************************/
LOCAL_INLINE uint32 Wdg_lReloadModifyAccess(const uint16 ReloadValue)
{
  /* Create Value for the bit field REL(Bit: 31:16) */
  return (uint32)((((uint32)(ReloadValue)) << WDG_REL_SHIFT_VALUE)&
                  WDG_MASK_WDTREL);

} /* End of Wdg_lReloadModifyAccess */

 #if (WDG_17_SCU_DISABLE_REJECT_DEM_REPORT == WDG_17_SCU_ENABLE_DEM_REPORT)
/*******************************************************************************
** Traceability     : [cover parentID={6ECEB54A-EFBB-40a1-9029-F725C4E55FE1}] **
**                                                                            **
** Syntax           : static void Wdg_lReportDemError(const Dem_EventIdType   **
**                           EventId, const Dem_EventStatusType EventStatus)  **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant                                                **
**                                                                            **
** Parameters (in):  EventId - DEM Event id                                   **
**                   EventStatus - DEM Event status                           **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
** Description :    Function to report Production errors                      **
**                                                                            **
**[/cover]                                                                    **
*******************************************************************************/
static void Wdg_lReportDemError(const Dem_EventIdType EventId,
const Dem_EventStatusType EventStatus)
{
  #if (MCAL_AR_VERSION == MCAL_AR_422)
  /* Report Production error for AS422 by calling 
     Mcal_Wrapper_Dem_ReportErrorStatus */
  Mcal_Wrapper_Dem_ReportErrorStatus(EventId,EventStatus);
  #endif
  #if (MCAL_AR_VERSION == MCAL_AR_440)  
  /*Report Production error for AS440 by calling 
    Mcal_Wrapper_Dem_SetEventStatus */
  /* [cover parentID={A8AF1790-96B6-4ff5-9E5D-583AAFA007B1}]
     Report Production error for AS440 by calling 
     Mcal_Wrapper_Dem_SetEventStatus [/cover] */
  (void)Mcal_Wrapper_Dem_SetEventStatus(EventId,EventStatus); 
  #endif
}
#endif
/* End of Wdg_lReportDemError */

#if ((WDG_17_SCU_DEV_ERROR_DETECT == STD_ON)||\
(WDG_17_SCU_SAFETY_ENABLE == STD_ON))
/*******************************************************************************
** Traceability     : [cover parentID={AB0989B3-4A01-48c8-9991-B720D9C43FB0}] **
**                                                                            **
** Syntax           : static void Wdg_lReportError(const uint8 ApiId,         **
**                                          const uint8 ErrorId)              **
** Service ID:       None                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       Reentrant                                                **
**                                                                            **
** Parameters (in):  ApiId - Service ID of the API reporting an error         **
**                   ErrorId - ID of the error reported                       **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
** Description :    Function to report Safety Error and DET                   **
**                                                                            **
**[/cover]                                                                    **
*******************************************************************************/
static void Wdg_lReportError(const uint8 ApiId, const uint8 ErrorId)
{
  /* [cover parentID={7B555AD7-BCD9-4a41-B810-8469583827D9}]
     Is DET error detect enabled[/cover] */
  #if (WDG_17_SCU_DEV_ERROR_DETECT == STD_ON)
  /* [cover parentID={0FED20EE-618B-462f-B5D2-E225EA573A9B}]
     Report WDG development error[/cover] */
  (void)Det_ReportError(WDG_17_SCU_MODULE_ID, WDG_17_SCU_INSTANCE_ID, ApiId, ErrorId);
  /* End of report to DET */
  #endif
  /* [cover parentID={814D4B07-D60E-432e-A3BE-89A218C4C0A6}]
     If Safety Check is enabled[/cover] */
  #if (WDG_17_SCU_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={00C183AD-5282-489d-B55C-39C7802D39B2}]
     Report safety error[/cover] */
  Mcal_ReportSafetyError(WDG_17_SCU_MODULE_ID, WDG_17_SCU_INSTANCE_ID, ApiId, ErrorId);
  /* End of report to Safety */
  #endif
}
#endif

#define WDG_17_SCU_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Wdg_17_Scu_MemMap.h"

#define WDG_17_SCU_START_SEC_CODE_FAST_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Wdg_17_Scu_MemMap.h"

/*******************************************************************************
** Traceability     :[cover parentID={138600B4-44B8-48cb-8D86-9533DB237C27}]  **
**                                                                            **
** Syntax           : void Wdg_17_Scu_Isr                                     **
**                    (const uint32 LogicalChId, const uint32 IsrStatus)      **
**                                                                            **
** Description      : This timer(GTM/STM)interrupt function is called if SRV  **
**                    timer is expired and triggers the Watchdog hardware     **
**                    timer if Timeout counter value has not reached zero.    **
**                                                                            **
**[/cover]                                                                    **
**                                                                            **
** Service ID       : 0x05                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Reentrant                                           **
**                                                                            **
** Parameters(in)   : LogicalChId - (GTM/STM) timer Id                        **
**                    IsrStatus - indicates the interrupt source              **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void Wdg_17_Scu_Isr(const uint32 LogicalChId, const uint32 IsrStatus)
{
  uint32 CoreId;
  Std_ReturnType ErrorFlag = E_NOT_OK;

  /* Retrieve the current core Id */
  CoreId = Mcal_GetCpuIndex();

  /* If Safety error check is enabled */
  /* [cover parentID={3704EAAA-320A-4cfc-9618-4AD81D32C008}]
   If Safety Error check is Enabled
   [/cover] */
  #if(WDG_17_SCU_SAFETY_ENABLE==STD_ON)
  /* if GTM trimer is selected */
  /* [cover parentID={FA160694-84C8-435c-B05B-65D0958B91F2}]
   if GTM trimer is selected
   [/cover] */
  #if(WDG_17_SCU_TRIG_SELECT == WDG_17_SCU_GTM_TIMER)
  /* If the interrupt source is valid in case of GTM(from CMP0)*/
  /* [cover parentID={DDF925D1-F0B3-48ba-BB0F-EFBF388D68D5}]
   If the interrupt source is valid in case of GTM from CMP0 ( from CMP0 )
   [/cover] */
  if((uint32)IsrStatus != (uint32)0x01U)
  {
    /* Report Safety error WDG_17_SCU_E_INVALID_INTERRPT_SOURCE */
    /* [cover parentID={83F22A26-3956-40f7-891F-F6699C8B1B4C}]
       Report Safety error WDG_17_SCU_E_INVALID_INTERRPT_SOURCE
       [/cover] */
    Wdg_lReportError
    (WDG_17_SCU_SID_TIMERNOTIF, WDG_17_SCU_E_INVALID_INTERRPT_SOURCE);
    /* Update the error flag to E_NOT_OK */
    /* [cover parentID={6E5CCE19-DB0E-4a74-A081-7EBD5F9D32DD}]
      Update the error flag to E_NOT_OK[/cover] */
    ErrorFlag = E_NOT_OK;
  }
  else
  #endif
  {
    /* If the Mode is OFF */
    /* [cover parentID={CCAFD6E8-FF03-44f9-A2B4-52EFE207D543}]
     If mode is OFF[/cover] */
    if (Wdg_17_Scu_Status[CoreId]->Wdg_17_Scu_DriverMode == WDGIF_OFF_MODE)
    {
      /* Report Safety error WDG_17_SCU_E_MODE_DISABLED */
      /* [cover parentID={53E50731-F880-4296-B873-8C31F28A35BA}]
        Report Safety error WDG_17_SCU_E_MODE_DISABLED[/cover] */
      Wdg_lReportError(WDG_17_SCU_SID_TIMERNOTIF, WDG_17_SCU_E_MODE_DISABLED);
      /* Update the error flag to E_NOT_OK */
      /* [cover parentID={5155C67A-DC64-4b40-A17D-DD0A8D4F858E}][/cover] */
      ErrorFlag = E_NOT_OK;
    }
    else
    {
      /* Update the error flag to E_OK */
      /* [cover parentID={1737FD67-B538-4e86-834F-A7163F8E9DDF}]
        Update the error flag to E_OK[/cover] */
      ErrorFlag = E_OK;
    }
  }
  /* If error flag is E_OK (valid interrupt source and Wdg
   is not in OFF mode)*/
  /* [cover parentID={6CCE52BE-593B-4ecf-B4F2-3A0B7DD5F59E}]
   If error flag is E_OK (valid interrupt source and Wdg is not in OFF mode)
   [/cover] */
  if(ErrorFlag == (Std_ReturnType)E_OK)
  #endif
  {
    /*If state of driver is not IDLE (Driver is not initialized)*/
    /* [cover parentID={2F344ECD-69F4-46f9-8702-1B6BFBB2E4FE}]
     If state of driver is not IDLE (Driver is not initialized)[/cover] */
    if (Wdg_17_Scu_Status[CoreId]->Wdg_17_Scu_DriverState != WDG_17_SCU_IDLE)
    {
      /* If DET or Safety Error Check is Enabled */
      /* [cover parentID={042B9BCB-58EE-424b-A474-29A63795EEF9}]
        If DET and Safety Error Check is Enabled[/cover] */
      #if ((WDG_17_SCU_DEV_ERROR_DETECT == STD_ON) || (WDG_17_SCU_SAFETY_ENABLE == STD_ON))
      /* Report DET or Safety error WDG_17_SCU_E_DRIVER_STATE */
      /* [cover parentID={C7158C5A-CFAD-4e88-BF37-C7A71B61E8ED}]
        Report DET or Safety error WDG_17_SCU_E_DRIVER_STATE[/cover] */
      Wdg_lReportError(WDG_17_SCU_SID_TIMERNOTIF, WDG_17_SCU_E_DRIVER_STATE);
      #endif
      /* Update the error flag to E_NOT_OK */
      /* [cover parentID={73DD5152-DCA0-42b5-AEF8-E9766658F12A}]
        Update the error flag to E_NOT_OK[/cover] */
      ErrorFlag = E_NOT_OK;
    }
    else
    {
      /* Update the error flag to E_OK */
      /* [cover parentID={B42711F6-6760-4b90-84EC-6F220785B505}]
         Update the error flag to E_OK[/cover] */
      ErrorFlag = E_OK;
    }
    /* If error flag is E_OK (Driver is initialized) */
    /* [cover parentID={91E021AF-B4DE-4283-84AD-7F79ABBA0157}]
     If error flag is E_OK (Driver is initialized)[/cover] */
    if(ErrorFlag == E_OK)
    {
      /* Check if overflow error status flag is enabled */
      /* [cover parentID={F3D76DF6-827B-4820-9D2F-82414DA666C3}]
         Check if overflow error status flag is enabled[/cover] */
      ErrorFlag = Wdg_lCheckOverflowErrorStatusFlag(CoreId);
      /* If error flag is E_OK (No overflow error) */
      /* [cover parentID={BC5F3EB0-68BA-4c0f-B90A-9D9D536731DD}]
        If Return Value is E_OK(No Overflow Error)[/cover] */
      if(ErrorFlag == E_OK)
      {
        /* Check if access error status flag is enabled */
        /* [cover parentID={2887559B-2321-4c8e-93A4-15528089E3DF}]
          Check if access error status flag is enabled[/cover] */
        ErrorFlag = Wdg_lCheckAccessErrorStatusFlag(CoreId);
      }
      /* If error flag is E_OK (No access and overflow error)  */
      /* [cover parentID={4F2ECC59-7A53-4cac-A4F1-81DA34A8326C}]
      If error flag is E_OK (No access and overflow error)[/cover] */
      if(ErrorFlag == E_OK)
      {
        /* Set Driver State to BUSY */
        /* [cover parentID={88608A27-4A23-4a70-9E5B-F7E69F78C60B}]
           Update the State of the driver to BUSY[/cover] */
        Wdg_17_Scu_Status[CoreId]->Wdg_17_Scu_DriverState = WDG_17_SCU_BUSY;

        /*If the timeout counter is greater than zero*/
        /* [cover parentID={AB095AAA-93F5-4a72-BCFB-A2253EA99D1B}]
        If the timeout counter is greater than zero[/cover] */
        if(Wdg_17_Scu_Status[CoreId]->Wdg_TimeoutCounter > 0x00U)
        {
          /* Decrement the Timeout Counter by 1 */
          /* [cover parentID={A4345EFF-FC1D-4ad9-8F21-F5A1125FC18D}]
          Decrement timeout counter by 1[/cover] */
          Wdg_17_Scu_Status[CoreId]->Wdg_TimeoutCounter = 
              Wdg_17_Scu_Status[CoreId]->Wdg_TimeoutCounter - 0x01U;

          /* Service the Watchdog hardware */
          /* [cover parentID={E96E1459-5C4A-4b6c-88A5-511E976CBF35}]
           Service the Wdg Hardware[/cover] */
          Wdg_lTrigger();
          /* if STM timer is selected */
          #if(WDG_17_SCU_TRIG_SELECT == WDG_17_SCU_STM_TIMER)
          /*Updates the CMP Register of STM */
          Wdg_lStmUpdateCmp(Wdg_17_Scu_Status[CoreId]->Wdg_17_Scu_DriverMode, CoreId);
          #endif
        }
        else
        {
          /* If GTM timer is selected */
          #if(WDG_17_SCU_TRIG_SELECT == WDG_17_SCU_GTM_TIMER)
          const Mcu_17_Gtm_TomAtomChConfigType *GtmChConfig;
          uint8 GtmModuleNumber;
          uint8 GtmChannelNumber;
          /*default index for WdgGtmTimerInfo */
          uint32 GtmIndex = WDG_GTM_INDEX_FAST_MODE; 
        
          if (Wdg_17_Scu_Status[CoreId]->Wdg_17_Scu_DriverMode == WDGIF_SLOW_MODE)
          {          
            GtmIndex = WDG_GTM_INDEX_SLOW_MODE;
          }
          
          /*Retrieve the gtm timer information */
          /* [cover parentID={076807FF-C4DE-4016-B2D9-757E9209A343}]
          Retrieve the gtm timer information [/cover] */
          GtmChConfig = &(Wdg_ConfigPtr[CoreId]->WdgGtmTimerInfo[GtmIndex]);
          
          /* [cover parentID={66254E1A-32C4-46d8-A1E6-6C3148767483}]
              Read the GTM channel and the module number[/cover] */
          /*Read GTM module number  */
          GtmModuleNumber = (uint8)((GtmChConfig->TimerId & 
                                     GTM_MODULE_NO_MASK) >> GTM_MODULE_NO_OFF);
          /* Read GTM channel number  */
          GtmChannelNumber = (uint8)((GtmChConfig->TimerId & 
                                   GTM_CHANNEL_NO_MASK) >> GTM_CHANNEL_NO_OFF);

          /* If TOM channel is configured  */
          /* [cover parentID={863B6DEE-A500-42d1-ABFC-B94D77FD45F6}]
              If TOM channel is selected[/cover] */
          if(GtmChConfig->TimerType == MCU_GTM_TIMER_TOM)
          {
            /* De initialize TOM channel */
            /* [cover parentID={D48C32E7-9C3A-4b0b-9577-7DAC5749CCE5}]
                 De-initialize TOM channel[/cover] */
            Mcu_17_Gtm_TomChannelDisable(GtmModuleNumber, GtmChannelNumber);
          }

          else  /* ATOM channel is configured */
          {
            /* De initialize ATOM channel */
            /* [cover parentID={2D43A6FC-E338-4cb4-9DD9-BD502FCA6953}]
             De-initialize ATOM channel[/cover] */
            Mcu_17_Gtm_AtomChannelDisable(GtmModuleNumber, GtmChannelNumber);
          }
          #else
          /*Disable the STM interrupt as further service of WDG is
            not required after window expires */
          Mcu_17_Stm_ComparatorIntDisable
          ((uint8)Wdg_ConfigPtr[CoreId]->WdgStmConfig->StmTimerId, 
           (uint8)Wdg_ConfigPtr[CoreId]->WdgStmConfig->CMPRegId);
          #endif
        }
        /* Set Driver State to IDLE */
        /* [cover parentID={A69BBEA9-B0DF-4504-B310-F041EC1BC3DF}]
        Set Driver State to Idle[/cover] */
        Wdg_17_Scu_Status[CoreId]->Wdg_17_Scu_DriverState = WDG_17_SCU_IDLE;
      }
    }
  }
  /* Unused parameters for Wdg */
  UNUSED_PARAMETER(LogicalChId);
  UNUSED_PARAMETER(IsrStatus);
} /* End of Wdg_17_Scu_Isr */


#define WDG_17_SCU_STOP_SEC_CODE_FAST_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
#include "Wdg_17_Scu_MemMap.h"

