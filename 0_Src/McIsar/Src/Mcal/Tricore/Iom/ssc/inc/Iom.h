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
**  FILENAME    : Iom.h                                                      **
**                                                                           **
**  VERSION     : 1.30.0_4.0.0                                               **
**                                                                           **
**  DATE        : 2019-09-18                                                 **
**                                                                           **
**  VARIANT     : Variant PB                                                 **
**                                                                           **
**  PLATFORM    : Infineon AURIX2G                                           **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION : This header file exports functionalities of IOM driver     **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: No                                      **
**                                                                           **
******************************************************************************/

#ifndef  IOM_H
#define  IOM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/* Inclusion of Platform_Types.h and Compiler.h */
#include "Std_Types.h"

/* Iom Pre-compile/static configuration file */
#include "Iom_Cfg.h"


/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/*
  Macros used in protected mode support.
*/
#define IOM_CLC_DISS                0x00000002U
#define IOM_CLC_DISR                0xFFFFFFFEU
#define IOM_KRST0_RSTSTAT           0x00000002U
#define IOM_FPCCTR_CMP              0xFFFF0000U
#define IOM_FPCCTR_CMP_SETMASK      0x0000FFFFU
#define IOM_CLC_INIT                0x00000100U
#define IOM_ECMETH_CLR_VALUE    0x00000000U
#define IOM_RSTSTAT_BIT_POS     (uint8)0x2

/* Maximum FPC channel   */
#define IOM_FPC_CHNL        0x0FU
/*Possible edge : Rising edge, Falling edge, Both edges*/
#define IOM_POS_EDGE        0x03U
/* Rising edge */
#define IOM_RISING_EDGE       0U
/* Falling edge */
#define IOM_FALLING_EDGE      1U
/* Both edges */
#define IOM_BOTH_EDGE       2U
/* Maximum ECM  Threshold Count value */
#define IOM_MAXECM_THRES_COUNTVALUE 0x0fU
/* Count Threshold value for shifting */
#define IOM_COUNT_THRES_VAL     (uint32)0x0000000fU
/* MAXIMUM EVENT CHANNEL SELECT */
#define IOM_EVE_CHNL_SELMSK     0x0fU
/* Maximum Event Window Count Threshold value */
#define IOM_MAX_LAM_THRES     0x00ffffffU
/* Event Window Count Value of Lam block */
#define IOM_LAMEWCM_SETMASK     0x00ffffffU
/* Maximum LAM units */
#define IOM_MAX_LAM_UNIT      0x0fU
/* Event Combiner Module Counter */
#define IOM_ECM_COUNTER       0x03U
/* LAM configuartion mask */
#define IOM_LAMCFG_MASK       (uint32)0x00ff1f3f
#define IOM_MAX_EVETRIG_HISTORY   3U
#define IOM_RISING_EDGE_GLITCH    16U
#define IOM_EVEHISTRY_SHIFT     16U
#define IOM_EVEHISTRY_MSK     0xffffU
#define IOM_FALLING_EDGE_SHIFT    15U
#define IOM_EVENT_COUNTER_SHIFT   8U
#define IOM_EVENTCNT_THR_SHIFT    4U
#define IOM_ECMSELR_SETMASK     0x000fffffU
#define IOM_CLC_DISS_BITPOS         1U
#define IOM_KRST0_RSTSTAT_BITPOS    1U
#define IOM_INIT_ACCESS             1U
#define IOM_DEINIT_ACCESS           2U
#define IOM_RUNTIME_ACCESS          3U

/* IOM Vendor ID */
#define IOM_VENDOR_ID                       (17U)
/* IOM Module ID */
#define IOM_MODULE_ID                       (255U)

#define IOM_MODULE_GLOB           (MODULE_IOM)

#define IOM_KRSTCLR_SETMASK_VALUE       (0x00000001U)
#define IOM_KRSTCLR_CLRMASK_VALUE       (0xFFFFFFFFU)

/* Development error codes */
#if (IOM_DEV_ERROR_DETECT == STD_ON)
/* Indicates module is not uninitialized */
#define IOM_UNINITPENDING     ((uint8)0x02)
/* Indicates module is initialized */
#define IOM_INITIALISED       ((uint8)0x01)
/* Indicates module is uninitialized */
#define IOM_UNINITIALIZED     ((uint8)0x00)
/* Inidicates module initialized before calling Iom_Init() */
#define IOM_E_INIT            ((uint8)0x10)
/*  Indicates module uninitialized */
#define IOM_E_UNINIT          ((uint8)0x11)
/* Inidicates invalid configuration pointer */
#define IOM_E_PARAM_CONFIG    ((uint8)0x12)
/* Inidicates invalid parameter */
#define IOM_E_PARAM_INVALID   ((uint8)0x13)
/* Inidicates invalid FPC parameter */
#define IOM_E_PARAM_FPC       ((uint8)0x14)
/* Inidicates invalid LAM parameter */
#define IOM_E_PARAM_LAM       ((uint8)0x15)
/* Inidicates invalid edge parameter */
#define IOM_E_PARAM_EDGE      ((uint8)0x16)
/* Inidicates invalid threshold value */
#define IOM_E_PARAM_THRES     ((uint8)0x17)
/* Inidicates invalid global event selection */
#define IOM_E_PARAM_EVESEL    ((uint8)0x18)
/* Inidicates invalid counter */
#define IOM_E_PARAM_CNT       ((uint8)0x19)
/* Inidicates invalid channel select */
#define IOM_E_PARAM_CHNLSEL   ((uint8)0x20)
/* Inidicates invalid event history */
#define IOM_E_PARAM_EVEHSTRY  ((uint8)0x21)



/* Service ID for Iom_Init */
#define IOM_SID_INIT                          ((uint8)0x5FU)
#define IOM_SID_DEINIT                        ((uint8)0x60U)
#define IOM_SID_RESETKERNEL                   ((uint8)0x61U)
#define IOM_SID_GETRESETSTAT                  ((uint8)0x62U)
#define IOM_SID_CLRRESETSTAT                  ((uint8)0x63U)
#define IOM_SID_CLRFPCEDGESTAT                ((uint8)0x64U)
#define IOM_SID_GETFPCEDGESTAT                ((uint8)0x65U)
#define IOM_SID_SETFPCCMP                     ((uint8)0x66U)
#define IOM_SID_GETFPCCMP                     ((uint8)0x67U)
#define IOM_SID_SETLAMCONFIG                  ((uint8)0x68U)
#define IOM_SID_GETLAMCONFIG                  ((uint8)0x69U)
#define IOM_SID_SETLAMTHRES                   ((uint8)0x6AU)
#define IOM_SID_GETLAMTHRES                   ((uint8)0x6BU)
#define IOM_SID_GETLAMENTWINCOUNT             ((uint8)0x6CU)
#define IOM_SID_SETECMGLOBEVESEL              ((uint8)0x6DU)
#define IOM_SID_GETECMGLOBEVESEL              ((uint8)0x6EU)
#define IOM_SID_SETECMTHRES                   ((uint8)0x6FU)
#define IOM_SID_GETECMTHRES                   ((uint8)0x70U)
#define IOM_SID_GETECMEVETRIGHIS              ((uint8)0x71U)
#define IOM_SID_CLRECMSTATHIS                 ((uint8)0x72U)
#define IOM_SID_GETVERINFO                    ((uint8)0x73U)

#endif


/*lint +e961*/
/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
/*Type Definition for  Iom_RstStatusType */
typedef uint8 Iom_RstStatusType;

/*Type Definition for  Iom_RstStatusType */
typedef uint8 Iom_FpcStatusType;

/*Type Definition for  Iom_Ecm_ThresType */
typedef uint8 Iom_Ecm_ThresType;

/*Type Definition for  Iom_Fpc_CompareType */
typedef uint32 Iom_Fpc_CompareType;

/*Type Definition for  Iom_Ecm_EveHisType */
typedef uint32 Iom_Ecm_EveHisType;

/*Type Definition for  Iom_Lam_ConfigType */
typedef uint32 Iom_Lam_ConfigType;

/*Type Definition for  Iom_Lam_ThresType */
typedef uint32 Iom_Lam_ThresType;

/*Type Definition for  Iom_Lam_CountType */
typedef uint32 Iom_Lam_CountType;

/*Type Definition for  Iom_Ecm_EveSelType */
typedef uint32 Iom_Ecm_EveSelType;

typedef enum
{
  IOM_EVETRIG_HISTORY_A = 0U,
  IOM_EVETRIG_HISTORY_B = 1U,
  IOM_EVETRIG_HISTORY_C = 2U,
  IOM_EVETRIG_HISTORY_D = 3U
} Iom_EventHistory;

/* Type definition for FPC module */
typedef struct
{
  uint32 FpcCfg;  /* FPC control value and compare value */
  uint16 FpcUnitNo;    /* FPC unit Id */
} Iom_FpcConfigType;

/* Type definition for LAM module */
typedef struct
{
  uint32 LamEntWinCount; /* LAM event window threshold */
  uint32 LamCfg;  /* LAM Configuration register value */
  uint16 LamNo;    /* LAM unit Id */
} Iom_LamConfigType;

/* Type definition for ECM module */
typedef struct
{
  uint32 EcmCountConfig;  /* ECM counter configuration register value*/
  uint32 EcmGlobEntSel;  /* ECM golbal event selection register value*/
} Iom_EcmConfigType;

/* Type definition for IOM channel */
typedef struct
{
  const Iom_FpcConfigType *FpcConfig;
  const Iom_LamConfigType *LamConfig;
  const Iom_EcmConfigType *EcmConfig;
  uint32 GtmConfig;
  uint32 ClkCntrl;

  /* Number of FPC and LAM uints */
  uint16 MaxChannel;
} Iom_ConfigType;


/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/


/*Memory Map of the  Code*/
#define IOM_START_SEC_CODE_QM_LOCAL

#include "Iom_MemMap.h"

/*******************************************************************************
** Traceability    :    NA                                                    **
**                                                                            **
** Syntax          :    void Iom_Init(const Iom_ConfigType *const ConfigPtr)  **
**                                                                            **
** Service ID      :    0x5F                                                  **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Non Reentrant                                         **
**                                                                            **
** Parameters (in) :    ConfigPtr - Pointer to configuration set              **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    :    None                                                  **
**                                                                            **
** Description     :    This routine initializes the IOM module.              **
**                      This function will initialize all relevant registers  **
**                      of Iom hardware with the values of structure          **
**                            referenced by the parameter ConfigPtr.          **
**                                                                            **
*******************************************************************************/
extern void Iom_Init(const Iom_ConfigType *const ConfigPtr);


#if (IOM_DEINIT_API == STD_ON)
/*******************************************************************************
** Traceability    :    NA                                                    **
**                                                                            **
** Syntax          :    void Iom_DeInit(void)                                 **
**                                                                            **
** Service ID      :    0x60                                                  **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Non Reentrant                                         **
**                                                                            **
** Parameters (in) :    None                                                  **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    :    None                                                  **
**                                                                            **
** Description     :    Driver Module Deinitialization function.Service for   **
**                      deinitializing all hardware registers to their        **
**                      power on reset state.                                 **
**                                                                            **
*******************************************************************************/
extern void Iom_DeInit(void);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
 *to function like macro where they are interchangeable*/
#define Iom_DeInit()  ERROR_Iom_DeInit_NOT_SELECTED

#endif


/*******************************************************************************
** Traceability    :    NA                                                    **
**                                                                            **
** Syntax          :    void Iom_ResetKernel(void)                            **
**                                                                            **
** Service ID      :    0x61                                                  **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Reentrant                                             **
**                                                                            **
** Parameters (in) :    None                                                  **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    :    None                                                  **
**                                                                            **
** Description     :    This service to reset IOM kernel                      **
**                                                                            **
*******************************************************************************/
extern void Iom_ResetKernel(void);


/*******************************************************************************
** Traceability    :    NA                                                    **
**                                                                            **
** Syntax          :    Iom_RstStatusType Iom_GetResetStatus(void)            **
**                                                                            **
** Service ID      :    0x62                                                  **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Reentrant                                             **
**                                                                            **
** Parameters (in) :    None                                                  **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    :    uint8: Kernel Reset status                            **
**                                                                            **
** Description     :    This service read the kernel reset status bit         **
**                                                                            **
*******************************************************************************/
extern Iom_RstStatusType Iom_GetResetStatus(void);


/*******************************************************************************
** Traceability    :    NA                                                    **
**                                                                            **
** Syntax          :    void Iom_ClrResetStatus(void)                         **
**                                                                            **
** Service ID      :    0x63                                                  **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Reentrant                                             **
**                                                                            **
** Parameters (in) :    None                                                  **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    :    None                                                  **
**                                                                            **
** Description     :    This service clear the kernel reset status bit        **
**                                                                            **
*******************************************************************************/
extern void Iom_ClrResetStatus(void);


/*******************************************************************************
** Traceability    :    NA                                                    **
**                                                                            **
** Syntax          :    void Iom_ClrFpcEdgeStatus(const uint8 FpcNo,          **
**                                                  const uint8 Edge)         **
**                                                                            **
** Service ID      :    0x64                                                  **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Reentrant                                             **
**                                                                            **
** Parameters (in) :    FpcNo: Numeric identifier of the Fpc channel          **
**                      Edge: Indicates Rising, Falling or both edge          **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    :    None                                                  **
**                                                                            **
** Description     :    Service to clear rising,falling or both edge          **
**                      glitches                                              **
**                                                                            **
*******************************************************************************/
extern void Iom_ClrFpcEdgeStatus(const uint8 FpcNo, const uint8 Edge);


/*******************************************************************************
** Traceability    :    NA                                                    **
**                                                                            **
** Syntax          :    Iom_FpcStatusType Iom_GetFpcEdgeStatus(const          **
**                                         uint8 FpcNo,const uint8 Edge)      **
** Service ID      :    0x65                                                  **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Reentrant                                             **
**                                                                            **
** Parameters (in) :    FpcNo: Numeric identifier of the FPC channel          **
**                      Edge: Indicates Rising, Falling or both edge          **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    :    uint8 : FPC edge status                               **
**                                                                            **
** Description     :    Service for reading the FPC Edge status of register   **
**                                                                            **
*******************************************************************************/
extern Iom_FpcStatusType Iom_GetFpcEdgeStatus(const uint8 FpcNo, \
        const uint8 Edge);


/*******************************************************************************
** Traceability    :    NA                                                    **
**                                                                            **
** Syntax          :    void Iom_SetFpcCompare(const uint8 FpcNO,             **
**                                                  const uint16  CompVal)    **
**                                                                            **
** Service ID      :    0x66                                                  **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Reentrant                                             **
**                                                                            **
** Parameters (in) :    FpcNo: Fpc number                                     **
**                      CompVal: Compare value for the FPC                    **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    :    None                                                  **
**                                                                            **
** Description     :    Service to set FPC compare value                      **
**                                                                            **
*******************************************************************************/
extern void Iom_SetFpcCompare(const uint8 FpcNo, const uint16 CompVal);


/*******************************************************************************
** Traceability    :    NA                                                    **
**                                                                            **
** Syntax          :    Iom_Fpc_CompareType Iom_GetFpcCompare(                **
**                            const uint8 FpcNO)                              **
**                                                                            **
** Service ID      :    0x67                                                  **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Reentrant                                             **
**                                                                            **
** Parameters (in) :    FpcNo: Fpc number                                     **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    :    uint16                                                **
**                                                                            **
** Description     :    Service is provided to get the FPC compare            **
**                      value                                                 **
**                                                                            **
*******************************************************************************/
extern Iom_Fpc_CompareType Iom_GetFpcCompare(const uint8 FpcNo);


/*******************************************************************************
** Traceability    :    NA                                                    **
**                                                                            **
** Syntax          :    void Iom_SetLamConfig(const uint8 LamNo,              **
**                          const uint32 ConfigVal)                           **
**                                                                            **
** Service ID      :    0x68                                                  **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Reentrant                                             **
**                                                                            **
** Parameters (in) :    LamNo: LAM unit number                                **
**                      ConfigVal:LAM configuration value                     **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    :    None                                                  **
**                                                                            **
** Description     :    This service is provided to change LAM configuration  **
**                                                                            **
*******************************************************************************/
extern void Iom_SetLamConfig(const uint8 LamNo, const uint32 ConfigVal);


/*******************************************************************************
** Traceability    :    NA                                                    **
**                                                                            **
** Syntax          :    Iom_Lam_ConfigType Iom_GetLamConfig(const uint8 LamNo)**
**                                                                            **
** Service ID      :    0x69                                                  **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Reentrant                                             **
**                                                                            **
** Parameters (in) :    LamNo: LAM unit number                                **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    :    uint32: LAM configuartion value                       **
**                                                                            **
** Description     :    This service returns Lam configuration value          **
**                                                                            **
*******************************************************************************/
extern Iom_Lam_ConfigType Iom_GetLamConfig(const uint8 LamNo);


/*******************************************************************************
** Traceability    :    NA                                                    **
**                                                                            **
** Syntax          :    void Iom_SetLamThreshold(const uint8 LamNo,           **
**                      const uint32 ThresVal)                                **
**                                                                            **
** Service ID      :    0x6A                                                  **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Reentrant                                             **
**                                                                            **
** Parameters (in) :    LamNo: LAM unit number                                **
**                      ThresVal: Threshold value                             **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    :    None                                                  **
**                                                                            **
** Description     :    Service for changing LAM threshold value              **
**                                                                            **
*******************************************************************************/
extern void Iom_SetLamThreshold(const uint8 LamNo, const uint32 ThresVal);


/*******************************************************************************
** Traceability    :    NA                                                    **
**                                                                            **
** Syntax          :    Iom_Lam_ThresType Iom_GetLamThreshold(                **
**                                                      const uint8 LamNo)    **
**                                                                            **
** Service ID      :    0x6B                                                  **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Reentrant                                             **
**                                                                            **
** Parameters (in) :    LamNo: LAM unit number                                **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    :    uint32: LAM unit threshold value                      **
**                                                                            **
** Description     :    This service returns Lam threshold value              **
**                                                                            **
*******************************************************************************/
extern Iom_Lam_ThresType Iom_GetLamThreshold(const uint8 LamNo);


/*******************************************************************************
** Traceability    :    NA                                                    **
**                                                                            **
** Syntax          :    Iom_Lam_CountType Iom_GetLamEntWinCount(              **
**                          const uint8 LamNo)                                **
**                                                                            **
** Service ID      :    0x6C                                                  **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Non Reentrant                                         **
**                                                                            **
** Parameters (in) :    LamNo: LAM unit number                                **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    :    uint32: LAM unit event window count value             **
**                                                                            **
** Description     :    Service for reading event window count value          **
**                                                                            **
*******************************************************************************/
extern Iom_Lam_CountType Iom_GetLamEntWinCount(const uint8 LamNo);


/*******************************************************************************
** Traceability    :    NA                                                    **
**                                                                            **
** Syntax          :    void Iom_SetEcmGlobalEveSel(const uint32 EventSel)    **
**                                                                            **
** Service ID      :    0x6D                                                  **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Reentrant                                             **
**                                                                            **
** Parameters (in) :    EventSel: inclusion of the respective channel and     **
**              counter output event in the generation of the global event    **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    :    None                                                  **
**                                                                            **
** Description     :    This service sets Global event selection              **
**                      register                                              **
**                                                                            **
*******************************************************************************/
extern void Iom_SetEcmGlobalEveSel(const uint32 EventSel);


/*******************************************************************************
** Traceability    :    NA                                                    **
**                                                                            **
** Syntax          :    Iom_Ecm_EveSelType Iom_GetEcmGlobalEveSel(void)       **
**                                                                            **
** Service ID      :    0x6E                                                  **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Reentrant                                             **
**                                                                            **
** Parameters (in) :    None                                                  **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    :    uint32: Global event selection register               **
**                                                                            **
** Description     :    This service returns Global event selection           **
**                      register                                              **
**                                                                            **
*******************************************************************************/
extern Iom_Ecm_EveSelType Iom_GetEcmGlobalEveSel(void);


/*******************************************************************************
** Traceability    :    NA                                                    **
**                                                                            **
** Syntax          :    void Iom_SetEcmThresVal(const uint8 CounterNo,        **
**                            const uint8 CountVal,const uint8 SelInput)      **
**                                                                            **
** Service ID      :    0x6F                                                  **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Reentrant                                             **
**                                                                            **
** Parameters (in) :    CounterNo: Channel event output to be routed to       **
**                      Counter.                                              **
**                      CountVal: Threshold value for the counter             **
**                      SelInput: Select channel event output to be counted   **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    :    None                                                  **
**                                                                            **
** Description     :    This service sets the ECMs counter threshold          **
**                      value                                                 **
**                                                                            **
*******************************************************************************/
extern void Iom_SetEcmThresVal(const uint8 CounterNo,
                               const uint8 CountVal,
                               const uint8 SelInput);

/*******************************************************************************
** Traceability    :    NA                                                    **
**                                                                            **
** Syntax          :    Iom_Ecm_ThresType Iom_GetEcmThresVal(                 **
**                          const uint8 CounterNo)                            **
**                                                                            **
** Service ID      :    0x70                                                  **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Reentrant                                             **
**                                                                            **
** Parameters (in) :    CounterNo : Counter number in ECM                     **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    :    uint8                                                 **
**                                                                            **
** Description     :    This service returns threshold value of the           **
**                      counter in ECM                                        **
**                                                                            **
*******************************************************************************/
extern Iom_Ecm_ThresType Iom_GetEcmThresVal(const uint8 CounterNo);


/*******************************************************************************
** Traceability    :    NA                                                    **
**                                                                            **
** Syntax          :    Iom_Ecm_EveHisType Iom_GetEcmEveTrigHis( const        **
**                                         Iom_EventHistory EveHistory)       **
**                                                                            **
** Service ID      :    0x71                                                  **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Reentrant                                             **
**                                                                            **
** Parameters (in) :    EveHistory: Event trigger history recorded in ETA,    **
**                                  ETB,ETC and ETD                           **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    :    uint32: ECM event trigger history                     **
**                                                                            **
** Description     :    This service returns ECM event trigger history        **
**                                                                            **
*******************************************************************************/
extern Iom_Ecm_EveHisType Iom_GetEcmEveTrigHis(Iom_EventHistory EveHistory);


/*******************************************************************************
** Traceability    :    NA                                                    **
**                                                                            **
** Syntax          :    void Iom_ClrEcmStatusHistory(void)                    **
**                                                                            **
** Service ID      :    0x72                                                  **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Reentrant                                             **
**                                                                            **
** Parameters (in) :    None                                                  **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    :    None                                                  **
**                                                                            **
** Description     :    This service resets the ECM event trigger             **
**                      status history                                        **
**                                                                            **
*******************************************************************************/
extern void Iom_ClrEcmStatusHistory(void);


#if(IOM_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Traceability    :    NA                                                    **
**                                                                            **
** Syntax          :    void Iom_GetVersionInfo                               **
**                     (                                                      **
**                       Std_VersionInfoType * const versioninfo              **
**                     )                                                      **
**                                                                            **
** Service ID      :    0x73                                                  **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Non Reentrant                                         **
**                                                                            **
** Parameters (in) :    None                                                  **
**                                                                            **
** Parameters (out):    versioninfo - Pointer to store the                    **
**                      version information of this module.                   **
**                                                                            **
** Return value    :    None                                                  **
**                                                                            **
** Description     :    This function:                                        **
**                    - returns the version information of this module        **
**                      The version information include:Module ID, Vendor ID, **
**                      Vendor specific version numbers                       **
**                    - This function is available if the IOM_VERSION_INFO_API**
**                      is set ON                                             **
**                                                                            **
*******************************************************************************/
extern void  Iom_GetVersionInfo(Std_VersionInfoType * const versioninfo);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:function like macro define used in preference
  to function like macro where they are interchangeable*/
#define Iom_GetVersionInfo() (ERROR_Iom_GetVersionInfo_NOT_SELECTED)
#endif  /* #if (IOM_VERSION_INFO_API == STD_ON) */


#define IOM_STOP_SEC_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Iom_MemMap.h"
/* The file is included to get extern declaration of all the configuration root
structure. The extern declaration of configuration root structure is needed by
application software */
#include "Iom_PBcfg.h"
#endif /* IOM_H */
