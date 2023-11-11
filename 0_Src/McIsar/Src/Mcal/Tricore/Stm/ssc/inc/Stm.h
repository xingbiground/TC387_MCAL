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
**  FILENAME     : Stm.h                                                      **
**                                                                            **
**  VERSION      : 8.0.0                                                      **
**                                                                            **
**  DATE         : 2019-06-12                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Stm Driver header definition file                          **
**                                                                            **
**  SPECIFICATION(S) : Specification of Stm Driver                            **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

#ifndef STM_H
#define STM_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Inclusion of Platform_Types.h and Compiler.h */
#include "Std_Types.h"
/*GPT Pre-compile/static configuration file */
#include "Stm_Cfg.h"

/*******************************************************************************
**                      Global Macro Definitions                              **
*****************************************1*************************************/
/* Module ID */
#define STM_MODULE_ID       (255)
/* STM Vendor ID */
#define STM_VENDOR_ID       (17)
/* STM Instance ID */
#define STM_INSTANCE_ID       ((uint8)0)


#define STM_BASE (&(MODULE_STM0))

#define STM0_SRC_BASE  ((Ifx_SRC_SRCR *) (void *) &(SRC_STM_STM0_SR0))
#if (STM_MAX_TIMERS > 0x0U)
#define STM1_SRC_BASE  ((Ifx_SRC_SRCR *)(void *) &(SRC_STM_STM1_SR0))
#endif
#if (STM_MAX_TIMERS > 0x1U)
#define STM2_SRC_BASE  ((Ifx_SRC_SRCR *)(void *) &(SRC_STM_STM2_SR0))
#endif
#if (STM_MAX_TIMERS > 0x2U)
#define STM3_SRC_BASE  ((Ifx_SRC_SRCR *)(void *) &(SRC_STM_STM3_SR0))
#endif
#if (STM_MAX_TIMERS > 0x3U)
#define STM4_SRC_BASE  ((Ifx_SRC_SRCR *)(void *) &(SRC_STM_STM4_SR0))
#endif
#if (STM_MAX_TIMERS > 0x4U)
#define STM5_SRC_BASE  ((Ifx_SRC_SRCR *)(void *) &(SRC_STM_STM5_SR0))
#endif


/* Development error codes */
#if (STM_DEV_ERROR_DETECT == STD_ON)

/* Service is called with invalid STM timer number allocated for the core */
#define STM_E_CORE_TIMER_MISMATCH    ((uint8)0x65U)

/* Service is called with invalid compare register number */
#define STM_E_CMPREG_FAILED           ((uint8)0x01U)

/* Service is called with invlaid timer mode */
#define STM_E_TIMER_MODE_FAILED       ((uint8)0x02U)

/*  Service is called with invlaid function pointer  */
#define STM_E_PARAM_POINTER           ((uint8)0x03U)

/* Service is called with invalid Mstart */
#define STM_E_MSTART_FAILED           ((uint8)0x04U)

/* Service is called with invalid sleep mode control */
#define STM_E_SLEEP_MODE_FAILED        ((uint8)0x05U)

/* Service is called with invalid Timer number is passed */
#define STM_E_INV_TIMER_NUMBER        ((uint8)0x06U)

/* Service is called with invalid MSize is passed */
#define STM_E_MSIZE_FAILED            ((uint8)0x07U)




/*
  Service ID number for all STM driver services
*/
/* Service ID for Stm_EnableModule */
#define STM_SID_ENABLEMODULE                   ((uint8)0xC7U)
/* Service ID for Stm_EnableAlarm */
#define STM_SID_ENABLEALARM                    ((uint8)0xC8U)
/* Service ID for Stm_DisableAlarm */
#define STM_SID_DISABLEALARM                   ((uint8)0xC9U)
/* Service ID for Stm_SetCompareMatchControl */
#define STM_SID_SETCOMPAREMATCH_CTRL           ((uint8)0xCAU)
/* Service ID for Stm_ReadTimerValue */
#define STM_SID_READTIMERVAL                   ((uint8)0xCBU)
/* Service ID for Stm_ReadTotalTimerValue */
#define STM_SID_READTOTALTIMERVAL              ((uint8)0xCCU)
/* Service ID for Stm_InterruptNodeSelection */
#define STM_SID_SLEEPMODHANDLE                 ((uint8)0xCDU)
/* Service ID for Stm_GetVersionInfo */
#define STM_SID_GETVERSIONINFO                 ((uint8)0xCEU)

#endif /*(STM_DEV_ERROR_DETECT == STD_ON)*/




/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
typedef struct
{
  void (*Stm_ArrayFunctionPtr[2])(void);
  uint32 CompareRegValue[2];
  uint8 InterruptNodeMap;
  uint8 TimerMode;
} Stm_ModuleParameterType;

typedef struct
{
  uint32 LowerPart;
  uint32 UpperPart;
} Stm_TotalTimerCaptureType;


typedef struct
{
  uint8 StmModID;
  uint8 CmpRegId;
} Stm_ModuleType;


/* Type definition for STM Application notification function pointer */
typedef void (*Stm_CallbackFnPtrType) (void);
/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/


/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
#define STM_START_SEC_CODE_QM_GLOBAL

#include "Stm_MemMap.h"
/*******************************************************************************
**                                                                            **
** Syntax           : void Stm_EnableModule(ModuleNumber)                     **
**                                                                            **
** Service ID       : 0xC7                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non reentrant                                           **
**                                                                            **
** Parameters(in)   : ModuleNumber - Stm Peripheral number                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : This function enables the STM interrupts and interrupt  **
**                     node mapping                                           **
*******************************************************************************/
extern void Stm_EnableModule(const uint8 ModuleNumber);


/*******************************************************************************
**                                                                            **
** Syntax           : void Stm_EnableAlarm(uint8 ModuleNumber,                **
**                    uint8 CompareRegisterId, uint8 TimerMode,uint32 Ticks,  **
**                    void (*Stm_Applicationfunction)(void))                  **
**                                                                            **
** Service ID       : 0xC8                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different STM timer number                **
**                                                                            **
** Parameters(in)   : ModuleNumber - Stm Peripheral number                    **
**                    CompareRegisterId - Compare register number             **
**                    TimerMode - One shot(0) or continuous(1)                **
**                    Ticks - Timer ticks w.r.t selected timer                **
**                    void (*Stm_Applicationfunction)(void)) -                **
**                    Functon pointer used for Call-back function             **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : This function provides service to invoke a Call-back    **
                      function after the elapse of configured                 **
                      amount of time(scheduling a function)                   **
*******************************************************************************/
extern void Stm_EnableAlarm(const uint8 ModuleNumber,
              const uint8 CompareRegisterId, const uint8 TimerMode,  
              const uint32 Ticks,
              const Stm_CallbackFnPtrType Stm_Applicationfunction);

/*******************************************************************************
**                                                                            **
** Syntax           : void Stm_DisableAlarm(uint8 ModuleNumber,uint8          **
**                                          CompareRegisterId)                **
** Service ID       : 0xC9                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different STM timer number                **
**                                                                            **
** Parameters(in)   : ModuleNumber - Stm Peripheral number                    **
**                    CompareRegisterId - Compare register number             **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : This function stops the invoke of a Call-back function  **
**                                                                            **
*******************************************************************************/
extern void Stm_DisableAlarm(const uint8 ModuleNumber,
                             const uint8 CompareRegisterId);


/*******************************************************************************
**                                                                            **
** Syntax           : void Stm_SetCompareMatchControl(uint8 ModuleNumber      **
**                     uint8 CompareRegisterId,uint8 Mstart,uint8 MSize)      **
**                                                                            **
** Service ID       : 0xCA                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different STM timer number                **
**                                                                            **
** Parameters(in)   : ModuleNumber - Stm Peripheral number                    **
**                    CompareRegisterId - Compare register number             **
**                    Mstart - The lowest bit number of the 64-bit STM        **
**                    MSize - Number of bits in register CMPx                 **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : This function provides service to write into the        **
**                    CMPx register.                                          **
**                                                                            **
*******************************************************************************/
extern void Stm_SetCompareMatchControl(const uint8 ModuleNumber,
                                       const uint8 CompareRegisterId, 
                                       const uint8 Mstart, const uint8 MSize);


/*******************************************************************************
**                                                                            **
** Syntax           : uint32 Stm_ReadTimerValue(uint8 ModuleNumber,           **
**                                              uint8 TimerNumber)            **
** Service ID       : 0xCB                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different STM timer number                **
**                                                                            **
** Parameters(in)   : ModuleNumber - stm periheral number                     **
**                    TimerNumber - The TimerNumber values shall be           **
**                                  0,1,2,3,4,5 and 6                         **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : uint32 - Current running timer value in ticks           **
**                                                                            **
** Description      : This function returns individual TIM value of a         **
**                    particular STM module                                   **
**                                                                            **
*******************************************************************************/
extern uint32 Stm_ReadTimerValue(const uint8 ModuleNumber,
                                 const uint8 TimerNumber);



/*******************************************************************************
**                                                                            **
** Syntax           : Stm_TotalTimerCaptureType                               **
**                     Stm_ReadTotalTimerValue(uint8 ModuleNumber)            **
**                                                                            **
** Service ID       : 0xCC                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different STM timer number                **
**                                                                            **
** Parameters(in)   : ModuleNumber - Stm Peripheral number                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : Stm_TotalTimerCaptureType : Holds the lower and upper   **
**                    32-bit values of a 64-bit STM timer                     **
**                                                                            **
** Description      : This function returns complete 64 bit STM Timer value   **
**                    of a particular STM module                              **
**                                                                            **
*******************************************************************************/
extern Stm_TotalTimerCaptureType Stm_ReadTotalTimerValue(
         const uint8 ModuleNumber);

/*******************************************************************************
**                                                                            **
** Syntax           : void Stm_SleepModeHandle(uint8 ModuleNumber,            **
                                       uint8 SleemodeControl)                 **
**                                                                            **
** Service ID       : 0xCD                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non reentrant                                           **
**                                                                            **
** Parameters(in)   : ModuleNumber - Stm Peripheral number                    **
**                    SleemodeControl - 0 or 1                                **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : This function:                                          **
**                                                                            **
*******************************************************************************/
extern void Stm_SleepModeHandle
              (const uint8 ModuleNumber, const uint8 SleepmodeControl);


/* Enable / Disable the use of the function */
#if ( STM_VERSION_INFO_API == STD_ON )
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax :void Stm_GetVersionInfo                                            **
**                    (                                                       **
**                      Std_VersionInfoType *VersionInfo                      **
**                    )                                                       **
**                                                                            **
** Description :  This Api:                                                   **
**   - This function returns the version information of this module           **
**     The version information include : Module ID, Vendor ID,                **
**     Vendor specific version numbers                                        **
**   - This function is available if the STM_VERSION_INFO_API is              **
**     set ON                                                                 **
**                                                                            **
** Service ID:  0xCE                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant                                                     **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
**                                                                            **
** Parameters (out):  VersionInfoPtr - Pointer to store the                   **
**                    version information of this module.                     **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/

extern void Stm_GetVersionInfo
(
  Std_VersionInfoType *versioninfo
);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION:Function Like Macro used */
#define Stm_GetVersionInfo() (ERROR_Stm_GetVersionInfo_NOT_SELECTED)
#endif /* STM_VERSION_INFO_API == STD_ON */
#define STM_STOP_SEC_CODE_QM_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Stm_MemMap.h"

#endif /* STM_H */
