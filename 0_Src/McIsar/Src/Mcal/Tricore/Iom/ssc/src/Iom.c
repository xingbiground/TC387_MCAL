/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2019)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME    : Iom.c                                                       **
**                                                                            **
**  VERSION     : 1.40.0_11.0.0                                               **
**                                                                            **
**  DATE        : 2019-11-07                                                  **
**                                                                            **
**  VARIANT     : Variant PB                                                  **
**                                                                            **
**  PLATFORM    : Infineon AURIX2G                                            **
**                                                                            **
**  AUTHOR      : DL-AUTOSAR-Engineering                                      **
**                                                                            **
**  VENDOR      : Infineon Technologies                                       **
**                                                                            **
**  DESCRIPTION : This file contains                                          **
**                functionality of IOM driver.                                **
**                                                                            **
**  SPECIFICATION(S) : Specification of Iom Driver                            **
**                                                                            **
**  MAY BE CHANGED BY USER [yes/no]: No                                       **
**                                                                            **
*******************************************************************************/


/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/* Inclusion of Iom Register structure header file */
#include "IfxIom_reg.h"

/* Global functions like Set/Reset END INIT protection bit,
  Enable/Disable interrupts, Atomic write function */
#include "McalLib.h"

/* Own header file, this includes precompile/static configuration file also */
#include "Iom.h"

/* Conditional Inclusion of DEM */
#if (IOM_E_CLC_ENABLE_ERR_DEM_REPORT == IOM_ENABLE_DEM_REPORT)
#include "Dem.h"
#endif

/* Conditional Inclusion of Developement Error Tracer File */
#if (IOM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

#if (IOM_INIT_DEINIT_API_MODE == IOM_MCAL_USER1) || \
(IOM_RUN_TIME_API_MODE == IOM_MCAL_USER1)
/* Mode specific library wrappers.*/
#include "McalLib_OsStub.h"
#endif

/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/

#ifndef IOM_SW_MAJOR_VERSION
#error "IOM_SW_MAJOR_VERSION is not defined. "
#endif

#ifndef IOM_SW_MINOR_VERSION
#error "IOM_SW_MINOR_VERSION is not defined. "
#endif

#ifndef IOM_SW_PATCH_VERSION
#error "IOM_SW_PATCH_VERSION is not defined. "
#endif

/* Check for Correct inclusion of headers */
#if ( IOM_SW_MAJOR_VERSION != 10U )
#error "IOM_SW_MAJOR_VERSION does not match. "
#endif
#if ( IOM_SW_MINOR_VERSION != 40U )
#error "IOM_SW_MINOR_VERSION does not match. "
#endif
#if ( IOM_SW_PATCH_VERSION != 0U )
#error "IOM_SW_PATCH_VERSION does not match. "
#endif


#if (IOM_DEV_ERROR_DETECT == STD_ON)

#ifndef DET_AR_RELEASE_MAJOR_VERSION
#error "DET_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

#if ( DET_AR_RELEASE_MAJOR_VERSION != 4U )
#error "DET_AR_RELEASE_MAJOR_VERSION does not match. "
#endif

#endif /*#if (IOM_DEV_ERROR_DETECT == STD_ON)*/

#if (IOM_E_CLC_ENABLE_ERR_DEM_REPORT == IOM_ENABLE_DEM_REPORT)
#ifndef DEM_AR_RELEASE_MAJOR_VERSION
#error "DEM_AR_RELEASE_MAJOR_VERSION is not defined."
#endif

#if ( DEM_AR_RELEASE_MAJOR_VERSION != 4U )
#error "DEM_AR_RELEASE_MAJOR_VERSION does not match."
#endif

#endif /*#if (IOM_E_CLC_ENABLE_ERR_DEM_REPORT == IOM_ENABLE_DEM_REPORT)*/

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

#define IOM_KRST_TIMEOUT_VALUE  (0x00000100U)
#define IOM_REG_SETMASK_VALUE   (0x00000001U)
#define IOM_REG_CLRMASK_VALUE   (0xFFFFFFFFU)


/*******************************************************************************
**                          User Mode Supoort Macros                          **
*******************************************************************************/
#if (IOM_INIT_DEINIT_API_MODE == IOM_MCAL_SUPERVISOR)
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for
   User mode support in code. No side effects foreseen by violating this MISRA
   rule. */
#define IOM_LIB_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(RegAdd,Data)   \
                Mcal_WritePeripEndInitProtReg(RegAdd,Data)

#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for
   User mode support in code. No side effects foreseen by violating this MISRA
   rule. */
#define IOM_LIB_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(RegAdd,Data)   \
                MCAL_LIB_WRITEPERIPENDINITPROTREG(RegAdd,Data)

#endif

#if (IOM_RUN_TIME_API_MODE == IOM_MCAL_SUPERVISOR)


/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for
   User mode support in code. No side effects foreseen by violating this MISRA
   rule. */
#define IOM_LIB_RUNTIME_WRITEPERIPENDINITPROTREG(RegAdd,Data)   \
                    Mcal_WritePeripEndInitProtReg(RegAdd,Data)

#else


/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for
   User mode support in code. No side effects foreseen by violating this MISRA
   rule. */
#define IOM_LIB_RUNTIME_WRITEPERIPENDINITPROTREG(RegAdd,Data)    \
                    MCAL_LIB_WRITEPERIPENDINITPROTREG(RegAdd,Data)

#endif



/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/

#define IOM_START_SEC_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Iom_MemMap.h"
/* Function to reset Kernels */
static void Iom_lResetKernels(uint8 ServiceId);
#define IOM_STOP_SEC_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
  guideline. */
#include "Iom_MemMap.h"


/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/

/*
* To be used for global or static variables (32 bits) that are initialized
* after every reset (the normal case)
Inclusion of MemMap.h
*/

#define IOM_START_SEC_VAR_CLEARED_QM_LOCAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
  guideline. */
#include "Iom_MemMap.h"
/* Variable Holds the Configuration Pointer given in Iom_Init */
/* MISRA2012_RULE_8_9_JUSTIFICATION: No side effects foreseen
 * by violating this MISRA rule, as the config pointer is accessed in
 * more than one block depending on the precompile switch */
static const Iom_ConfigType *Iom_ConfigPtr;

#define IOM_STOP_SEC_VAR_CLEARED_QM_LOCAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Iom_MemMap.h"
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define IOM_START_SEC_VAR_CLEARED_QM_LOCAL_8
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Iom_MemMap.h"

#if(IOM_DEV_ERROR_DETECT == STD_ON)
/* To indicate whether IOM driver is initialised or not.
If equal to 1: Driver is initialised
if equal to 0: Driver is deinitiaised */
static uint8 Iom_InitStatus;
#endif

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define IOM_STOP_SEC_VAR_CLEARED_QM_LOCAL_8
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Iom_MemMap.h"

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/


/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
/*Memory Map of the  Code*/
#define IOM_START_SEC_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
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
**                      referenced by the parameter ConfigPtr.                **
**                                                                            **
*******************************************************************************/
void Iom_Init(const Iom_ConfigType *const ConfigPtr)
{
  uint8 FpcId;
  uint8 LamId;
  uint8 ChannelIndex;
  /* local pointers to FPC and LAM unit */
  const Iom_FpcConfigType *LocalFpcPtr;
  const Iom_LamConfigType *LocalLamPtr;

  #if(IOM_DEV_ERROR_DETECT == STD_ON)
  uint8 DetErr;
  DetErr = 0U;
  /*Check the config pointer for NULL_PTR*/
  if(ConfigPtr == NULL_PTR)
  {
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_INIT,
                    IOM_E_PARAM_CONFIG);
    /*Skip the API functionality and return from the API */
    DetErr = 1U;
  }
  /*Check if IOM is initialised*/
  else if(Iom_InitStatus == IOM_INITIALISED)
  {
    /* Report IOM_E_INIT DET */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_INIT,
                    IOM_E_INIT);
    /* Skip the API functionality and return from the API */
    DetErr = 1U;
  }
  else
  {
    /* No action - Added for MISRA*/
  }
  /* Proceed only if no error was found */
  if(DetErr == 0U)
  #endif

  {
    /*Initialize the global variable to hold the config pointer */
    Iom_ConfigPtr = ConfigPtr;
    /* Enable IOM module clock by configured value */
    IOM_LIB_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(&IOM_CLC.U, \
        Iom_ConfigPtr->ClkCntrl);
    /* Checking the clock is enabled using status of DISS bit in the 
    IOM_CLC Register */
    if((((IOM_CLC.U) & IOM_CLC_DISS) >> \
        IOM_CLC_DISS_BITPOS) == 0U)
    {
      #if(IOM_E_CLC_ENABLE_ERR_DEM_REPORT == IOM_ENABLE_DEM_REPORT)
      /*Report DEM for IOM enable passed*/
      Dem_ReportErrorStatus(IOM_E_CLC_ENABLE_ERR, \
                            DEM_EVENT_STATUS_PASSED);
      #endif
      /*kernel reset for all available kernels*/
      Iom_lResetKernels(IOM_INIT_ACCESS);

      /* Set ECM and GTM configuration registers */
      /*update IOM_ECMCCFG register with the user configured values*/
      IOM_ECMCCFG.U = Iom_ConfigPtr->EcmConfig->EcmCountConfig;
      /*update IOM_ECMSELR register with the user configured values*/
      IOM_ECMSELR.U = Iom_ConfigPtr->EcmConfig->EcmGlobEntSel;
      
      #if(IOM_GTM_AVAILABLE == STD_ON)
      /*update IOM_GTMEXR register with the user configured values*/
      IOM_GTMEXR.U = Iom_ConfigPtr->GtmConfig;
      #endif

      /* Set FPC congfiguration register based on maximum channel configured */
      for(ChannelIndex = 0U;
          ChannelIndex < Iom_ConfigPtr->MaxChannel;
          ChannelIndex++)
      {
        /*Update the local Fpc pointer for Fpc configuration */
        LocalFpcPtr = &Iom_ConfigPtr->FpcConfig[ChannelIndex];
        FpcId = (uint8)LocalFpcPtr->FpcUnitNo;
        /*update IOM_FPCCTR register with the user configured values*/
        IOM_MODULE_GLOB.FPCCTR[FpcId].U = LocalFpcPtr->FpcCfg;
      }
      /* Set LAM configuartion register based on maximum channel configured */
      for(ChannelIndex = 0U;
          ChannelIndex < Iom_ConfigPtr->MaxChannel;
          ChannelIndex++)
      {
        /*Update the local Lam pointer for Lam configuration */
        LocalLamPtr = &Iom_ConfigPtr->LamConfig[ChannelIndex];
        LamId = (uint8)LocalLamPtr->LamNo;
        /*update IOM_LAMEWS register with the user configured values*/
        IOM_MODULE_GLOB.LAMEWS[LamId].U = LocalLamPtr->LamEntWinCount;
        /*update IOM_LAMCFG register with the user configured values*/
        IOM_MODULE_GLOB.LAMCFG[LamId].U = LocalLamPtr->LamCfg;
      }

      #if(IOM_DEV_ERROR_DETECT == STD_ON)
      /* Set initialisation status to indicate initialization is done */
      Iom_InitStatus = IOM_INITIALISED;
      #endif  /*(IOM_DEV_ERROR_DETECT == STD_ON)*/
    } /*End of status of DISS bit check in the IOM_CLC Register */
    else
    {
      #if(IOM_DEV_ERROR_DETECT == STD_ON)
      /* Set initialisation status to indicate the module is
      uninitialized */
      Iom_InitStatus = IOM_UNINITIALIZED;
      #endif /* End of (IOM_DEV_ERROR_DETECT == STD_ON) */
      #if(IOM_E_CLC_ENABLE_ERR_DEM_REPORT == IOM_ENABLE_DEM_REPORT)
      /*Report DEM for IOM enable failed*/
      Dem_ReportErrorStatus(IOM_E_CLC_ENABLE_ERR, \
                            DEM_EVENT_STATUS_FAILED);
      #endif
    }
  } /* DetErr == 0U */
}/* End of Iom_Init */


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
void Iom_DeInit(void)
{
  volatile uint32 ReadBack;
  uint8 FpcId;
  uint8 LamId;
  uint8 ChannelIndex;
  uint32 DisableRequest;
  #if (IOM_DEV_ERROR_DETECT == STD_ON)
  uint8 DetErr;
  DetErr = 0U;
  /*Check if IOM is initialised*/
  if(Iom_InitStatus != IOM_INITIALISED )
  {
    /* Report DET IOM_E_UNINIT */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_DEINIT,
                    IOM_E_UNINIT);

    DetErr = 1U;
  }
  /* Proceed only if no error was found */
  if(DetErr == 0U)
  #endif  /* End of (IOM_DEV_ERROR_DETECT == STD_ON) */
  {
    #if(IOM_DEV_ERROR_DETECT == STD_ON)
    /* Set driver state to deinitialization pending */
    Iom_InitStatus = IOM_UNINITPENDING;
    #endif

    /* Set ECM ,GTM registers to reset value */
    /*update IOM_ECMCCFG register*/
    IOM_ECMCCFG.U = (uint32)0U;
    /*update IOM_ECMSELR register*/
    IOM_ECMSELR.U = (uint32)0U;
    
    #if(IOM_GTM_AVAILABLE == STD_ON)
    /*update IOM_GTMEXR register*/
    IOM_GTMEXR.U = (uint32)0U;
    #endif

    /* Reset FPC and LAM registers */
    for(ChannelIndex = 0U;
        ChannelIndex < Iom_ConfigPtr->MaxChannel;
        ChannelIndex++)
    {
      FpcId = (uint8)Iom_ConfigPtr->FpcConfig[ChannelIndex].FpcUnitNo;
      /*update IOM_FPCCTR register*/
      IOM_MODULE_GLOB.FPCCTR[FpcId].U = 0U;
    }

    for(ChannelIndex = 0U;
        ChannelIndex < Iom_ConfigPtr->MaxChannel;
        ChannelIndex++)
    {
      LamId = (uint8)Iom_ConfigPtr->LamConfig[ChannelIndex].LamNo;
      /*update IOM_LAMEWS register*/
      IOM_MODULE_GLOB.LAMEWS[LamId].U = 0U;
      /*update IOM_LAMCFG register*/
      IOM_MODULE_GLOB.LAMCFG[LamId].U = 0U;
    }
    /* kernel reset for all available kernels*/
    Iom_lResetKernels(IOM_DEINIT_ACCESS);
    
    /* Request to disable the module */
    DisableRequest  =  IOM_CLC.U;
    DisableRequest &= IOM_CLC_DISR;
    DisableRequest |= (uint32)1U;
    /* Disable the module clock */
    IOM_LIB_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(&IOM_CLC.U, \
        DisableRequest);

    /* Read back the CLC register to flush the pipeline effects */
    ReadBack = (IOM_CLC.U);
    UNUSED_PARAMETER(ReadBack);

    #if(IOM_DEV_ERROR_DETECT == STD_ON)
    /*Set driver state to deinitialization completed */
    Iom_InitStatus = IOM_UNINITIALIZED ;
    #endif  /*(IOM_DEV_ERROR_DETECT == STD_ON)*/
  }  /* DetErr = 0  */
} /* end of Deinit API */
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
void Iom_ResetKernel(void)
{
  #if (IOM_DEV_ERROR_DETECT == STD_ON)
  uint8 DetErr;
  DetErr = 0U;
  /*Check if IOM is initialised*/
  if(Iom_InitStatus != IOM_INITIALISED )
  {
    /* Report DET IOM_E_UNINIT */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_RESETKERNEL,
                    IOM_E_UNINIT);
    DetErr = 1U;
  }
  /* Proceed only if no error was found */
  if(DetErr == 0U)
  #endif
  {
    /* kernel reset requested*/
    Iom_lResetKernels(IOM_RUNTIME_ACCESS);
  }
}


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
Iom_RstStatusType Iom_GetResetStatus(void)
{
  uint8 RstStat;

  #if (IOM_DEV_ERROR_DETECT == STD_ON)
  uint8 DetErr;
  DetErr = 0U;
  /*Check if IOM is initialised*/
  if(Iom_InitStatus != IOM_INITIALISED )
  {
    /* Report DET IOM_E_UNINIT */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_GETRESETSTAT,
                    IOM_E_UNINIT);

    DetErr = 1U;
  }
  /* Proceed only if no error was found */
  if(DetErr == 0U)
  #endif
  {
    /* Read the KRST0 register for reset status */
    RstStat = (uint8)IOM_MODULE_GLOB.KRST0.U;
    /* Get the reset status bit from KRST0 register */
    RstStat = ((RstStat & IOM_RSTSTAT_BIT_POS) >> 1);
  }
  #if (IOM_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* Invalid value is returned indicating DET is reported */
    RstStat = 0xFF;
  }
  #endif
  /* Reset status is returned for kernel */
  return RstStat;
}


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
void Iom_ClrResetStatus(void)
{
  uint32 StatusClr;
  #if (IOM_DEV_ERROR_DETECT == STD_ON)
  uint8 DetErr;
  DetErr = 0U;
  /*Check if IOM is initialised*/
  if(Iom_InitStatus != IOM_INITIALISED )
  {
    /* Report DET IOM_E_UNINIT */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_CLRRESETSTAT,
                    IOM_E_UNINIT);
    DetErr = 1U;
  }
  /* Proceed only if no error was found */
  if(DetErr == 0U)
  #endif
  {
    /* Mask value is applied to set CLR bit in KRSTCLR register*/
    StatusClr = IOM_MODULE_GLOB.KRSTCLR.U;
    StatusClr &= IOM_KRSTCLR_CLRMASK_VALUE;
    StatusClr |= IOM_KRSTCLR_SETMASK_VALUE;
    /*update IOM_KRSTCLR register to clear kernel reset status*/
    IOM_LIB_RUNTIME_WRITEPERIPENDINITPROTREG(&IOM_MODULE_GLOB.KRSTCLR.U, \
        StatusClr);
  }/* DetErr = 0  */
}


/*******************************************************************************
** Traceability    :    NA                                                    **
**                                                                            **
** Syntax          :    void Iom_ClrFpcEdgeStatus(const uint8 FpcNo,          **
**                            const uint8 Edge)                               **
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
void Iom_ClrFpcEdgeStatus(const uint8 FpcNo, const uint8 Edge)
{
  uint32 EdgeRsClr;
  uint32 EdgeFaClr;
  uint32 EdgeClr;

  #if (IOM_DEV_ERROR_DETECT == STD_ON)
  uint8 DetErr;
  DetErr = 0U;
  /*Check if IOM is initialised*/
  if(Iom_InitStatus != IOM_INITIALISED )
  {
    /* Report DET IOM_E_UNINIT */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_CLRFPCEDGESTAT,
                    IOM_E_UNINIT);

    DetErr = 1U;
  }
  /*Check if Fpc channel is not more than maximum channels*/
  else if(FpcNo > IOM_FPC_CHNL)
  {
    /* Report DET IOM_E_PARAM_FPC for invalid argument */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_CLRFPCEDGESTAT,
                    IOM_E_PARAM_FPC);

    DetErr = 1U;
  }
  /*Check if Edge is not more than IOM_BOTH_EDGE */
  else if(Edge > IOM_BOTH_EDGE)
  {
    /* Report DET IOM_E_PARAM_EDGE for invalid argument */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_CLRFPCEDGESTAT,
                    IOM_E_PARAM_EDGE);

    DetErr = 1U;
  }
  else
  {
    /* do nothing - Added for MISRA */
  }
  /* Proceed only if no error was found */
  if(DetErr == 0U)
  #endif
  {
    /* Clear rising edge */
    if(Edge == IOM_RISING_EDGE) 
    {
      /* Read FPCESR register and clear rising edge for corresponding Fpc */
      EdgeRsClr = ~((uint32)1U << (FpcNo + IOM_RISING_EDGE_GLITCH));
      EdgeClr = (IOM_FPCESR.U) & EdgeRsClr;
      /*update IOM_FPCESR register to clear rising edge*/
      IOM_FPCESR.U = EdgeClr;
    }
    /* Clear falling edge */
    else if(Edge == IOM_FALLING_EDGE) 
    {
      /* Read FPCESR register and clear falling edge for corresponding Fpc */
      EdgeFaClr = ~((uint32)1U << FpcNo);
      EdgeClr = (IOM_FPCESR.U) & EdgeFaClr;
      /*update IOM_FPCESR register to clear falling edge*/
      IOM_FPCESR.U = EdgeClr;
    }
    /* Clear Both edges */
    else 
    {
      /* Read FPCESR register and clear both edge for corresponding Fpc */
      EdgeFaClr = ~((uint32)1U << FpcNo);
      EdgeRsClr = ~((uint32)1U << (FpcNo + IOM_RISING_EDGE_GLITCH));
      EdgeClr = EdgeFaClr & EdgeRsClr;
      EdgeClr &= (IOM_FPCESR.U);
      /*update IOM_FPCESR register*/
      IOM_FPCESR.U = EdgeClr;
    }
   
  }/* DetErr = 0  */
}


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
Iom_FpcStatusType Iom_GetFpcEdgeStatus(const uint8 FpcNo, const uint8 Edge)
{
  uint32 EdgeRs;
  uint32 EdgeFa;
  uint32 EdgeSt = 0;
  uint32 EdgeRSt;
  uint32 EdgeFSt;
  uint32 FpcEdgeStatus;

  #if (IOM_DEV_ERROR_DETECT == STD_ON)
  uint8 DetErr;
  DetErr = 0U;
  /*Check if IOM is initialised*/
  if(Iom_InitStatus != IOM_INITIALISED )
  {
    /* Report DET IOM_E_UNINIT */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_GETFPCEDGESTAT,
                    IOM_E_UNINIT);
    DetErr = 1U;
  }
  /*Check if Fpc channel is not more than maximum channels*/
  else if(FpcNo > IOM_FPC_CHNL)
  {
    /* Report DET IOM_E_PARAM_FPC for invalid argument */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_GETFPCEDGESTAT,
                    IOM_E_PARAM_FPC);

    DetErr = 1U;
  }
  /*Check if Edge is not more than IOM_BOTH_EDGE */
  else if(Edge > IOM_BOTH_EDGE)
  {
    /* Report DET IOM_E_PARAM_EDGE for invalid argument */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_GETFPCEDGESTAT,
                    IOM_E_PARAM_EDGE);

    DetErr = 1U;
  }
  else
  {
    /* do nothing - Added for MISRA*/
  }
  /* Proceed only if no error was found */
  if(DetErr == 0U)
  #endif
  {
    FpcEdgeStatus = IOM_MODULE_GLOB.FPCESR.U;
    /* To get rising edge */
    if(Edge == IOM_RISING_EDGE)  
    {
      /* Read FPCESR register and get rising edge for corresponding Fpc */
      EdgeRs = ((uint32)1U << (FpcNo + IOM_RISING_EDGE_GLITCH));
      EdgeSt = FpcEdgeStatus & EdgeRs;
      EdgeSt = (EdgeSt >> (FpcNo + IOM_RISING_EDGE_GLITCH));
    }
    /* To get falling edge */
    else if(Edge == IOM_FALLING_EDGE)   
    {
      /* Read FPCESR register and get falling edge for corresponding Fpc */
      EdgeFa = ((uint32)1U << (FpcNo));
      EdgeSt = FpcEdgeStatus & EdgeFa;
      EdgeSt = (EdgeSt >> (FpcNo));
    }
    /* To get both edges */
    else   
    {
      /* Read FPCESR register and get both edge for corresponding Fpc */
      EdgeFa = ((uint32)1U << (FpcNo));
      EdgeFSt = FpcEdgeStatus & EdgeFa;
      EdgeFSt = (EdgeFSt >> (FpcNo));
      EdgeRs = ((uint32)1U << (FpcNo + IOM_RISING_EDGE_GLITCH));
      EdgeRSt = FpcEdgeStatus & EdgeRs;
      EdgeRSt = (EdgeRSt >> (FpcNo + IOM_FALLING_EDGE_SHIFT));
      EdgeSt = EdgeFSt | EdgeRSt ;
    }
  
  }/* DetErr = 0  */
  #if (IOM_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* Invalid value is returned indicating DET is reported */
    EdgeSt = 0xFF;
  }
  #endif
  /* FPC edge status is returned */
  return((uint8)EdgeSt);
}


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
void Iom_SetFpcCompare(const uint8 FpcNo, const uint16 CompVal)
{
  #if (IOM_DEV_ERROR_DETECT == STD_ON)
  uint8 DetErr;
  DetErr = 0U;
  /*Check if IOM is initialised*/
  if(Iom_InitStatus != IOM_INITIALISED )
  {
    /* Report DET IOM_E_UNINIT */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_SETFPCCMP,
                    IOM_E_UNINIT);

    DetErr = 1U;
  }
  /*Check if Fpc channel is not more than maximum channels*/
  else if((FpcNo > IOM_FPC_CHNL))
  {
    /* Report DET IOM_E_PARAM_FPC for invalid argument */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_SETFPCCMP,
                    IOM_E_PARAM_FPC);

    DetErr = 1U;
  }
  else
  {
    /* do nothing - Added for MISRA*/
  }
  /* Proceed only if no error was found */
  if(DetErr == 0U)
  #endif
  {
    /*update IOM_FPCCTR register*/
    /* MISRA2012_RULE_18_1_JUSTIFICATION: Array based indexing is performed
    to access the FPC registers efficiently.The access is checked to be
    within the bounds of the SFRs */
    IOM_MODULE_GLOB.FPCCTR[FpcNo].U &=  IOM_FPCCTR_CMP;
    /* MISRA2012_RULE_18_1_JUSTIFICATION: Array based indexing is performed
    to access the FPC registers efficiently.The access is checked to be
    within the bounds of the SFRs */
    /* Update compare value in IOM_FPCCTR register */
    IOM_MODULE_GLOB.FPCCTR[FpcNo].U |= (uint32)CompVal;
  }
}


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
Iom_Fpc_CompareType Iom_GetFpcCompare(const uint8 FpcNo)
{
  uint32 FpcComp;
  #if (IOM_DEV_ERROR_DETECT == STD_ON)
  uint8 DetErr;
  DetErr = 0U;
  /*Check if IOM is initialised*/
  if(Iom_InitStatus != IOM_INITIALISED )
  {
    /* Report DET IOM_E_UNINIT */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_GETFPCCMP,
                    IOM_E_UNINIT);

    DetErr = 1U;
  }
  /*Check if Fpc channel is not more than maximum channels*/
  else if(FpcNo > IOM_FPC_CHNL)
  {
    /* Report DET IOM_E_PARAM_FPC for invalid argument */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_GETFPCCMP,
                    IOM_E_PARAM_FPC);

    DetErr = 1U;
  }
  else
  {
    /* do nothing - Added for MISRA*/
  }
  /* Proceed only if no error was found */
  if(DetErr == 0U)
  #endif
  {
    /* MISRA2012_RULE_18_1_JUSTIFICATION: Array based indexing is performed
    to access the FPC registers efficiently.The access is checked to be
    within the bounds of the SFRs */
    /* Read FPCCTR register and get compare value for corresponding Fpc */
    FpcComp = ((IOM_MODULE_GLOB.FPCCTR[FpcNo].U) & IOM_FPCCTR_CMP_SETMASK);
  }

  #if (IOM_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* Invalid value is returned indicating DET is reported */ 
    FpcComp = 0xFFFFFFFFU;
  }
  #endif
  /* FPC compare value is returned */
  return FpcComp;
}


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
void Iom_SetLamConfig(const uint8 LamNo, const uint32 ConfigVal)
{
  uint32 LamConfigVal;

  #if (IOM_DEV_ERROR_DETECT == STD_ON)
  uint8 DetErr;
  DetErr = 0U;
  /*Check if IOM is initialised*/
  if(Iom_InitStatus != IOM_INITIALISED )
  {
    /* Report DET IOM_E_UNINIT */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_SETLAMCONFIG,
                    IOM_E_UNINIT);

    DetErr = 1U;
  }
  /*Check if Lam unit is not more than maximum Lam unit*/
  else if(LamNo > IOM_MAX_LAM_UNIT)
  {
    /* Report DET IOM_E_PARAM_LAM for invalid argument */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_SETLAMCONFIG,
                    IOM_E_PARAM_LAM);

    DetErr = 1U;
  }
  else
  {
    /* do nothing - Added for MISRA*/
  }
  /* Proceed only if no error was found */
  if(DetErr == 0U)
  #endif
  {
    /* Mask for reserved bits */
    LamConfigVal = ConfigVal & IOM_LAMCFG_MASK;
    /*update configuration value in IOM_LAMCFG register */
    /* MISRA2012_RULE_18_1_JUSTIFICATION: Array based indexing is performed
    to access the LAM registers efficiently.The access is checked to be
    within the bounds of the SFRs */
    IOM_MODULE_GLOB.LAMCFG[LamNo].U = LamConfigVal;
  }
}


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
Iom_Lam_ConfigType Iom_GetLamConfig(const uint8 LamNo)
{
  uint32 LamConfigVal;
  
  #if (IOM_DEV_ERROR_DETECT == STD_ON)
  uint8 DetErr;
  DetErr = 0U;
  /*Check if IOM is initialised*/
  if(Iom_InitStatus != IOM_INITIALISED )
  {
    /* Report DET IOM_E_UNINIT */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_GETLAMCONFIG,
                    IOM_E_UNINIT);

    DetErr = 1U;
  }
  /*Check if Lam unit is not more than maximum Lam unit*/
  else if(LamNo > IOM_MAX_LAM_UNIT)
  {
    /* Report DET IOM_E_PARAM_LAM for invalid argument */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_GETLAMCONFIG,
                    IOM_E_PARAM_LAM);

    DetErr = 1U;
  }
  else
  {
    /* do nothing - Added for MISRA*/
  }
  /* Proceed only if no error was found */
  if(DetErr == 0U)
  #endif
  {
    /* MISRA2012_RULE_18_1_JUSTIFICATION: Array based indexing is performed
    to access the LAM registers efficiently.The access is checked to be
    within the bounds of the SFRs */
    /* Get configuration value from IOM_LAMCFG register */
    LamConfigVal = ((IOM_MODULE_GLOB.LAMCFG[LamNo].U) & IOM_LAMCFG_MASK);
  }
  #if (IOM_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* Invalid value is returned indicating DET is reported */
    LamConfigVal = 0xFF000000U;
  }
  #endif
  /* LAM configuration value is returned */
  return LamConfigVal;
}


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
void Iom_SetLamThreshold(const uint8 LamNo, const uint32 ThresVal)
{
  uint32 LamThres;

  #if (IOM_DEV_ERROR_DETECT == STD_ON)
  uint8 DetErr;
  DetErr = 0U;
  /*Check if IOM is initialised*/
  if(Iom_InitStatus != IOM_INITIALISED )
  {
    /* Report DET IOM_E_UNINIT */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_SETLAMTHRES,
                    IOM_E_UNINIT);

    DetErr = 1U;
  }
  /*Check if Lam unit is not more than maximum Lam unit*/
  else if(LamNo > IOM_MAX_LAM_UNIT)
  {
    /* Report DET IOM_E_PARAM_LAM for invalid argument */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_SETLAMTHRES,
                    IOM_E_PARAM_LAM);

    DetErr = 1U;
  }
  /*Check if threshold value is not more than maximum threshold value */
  else if(ThresVal > IOM_MAX_LAM_THRES)
  {
    /* Report DET IOM_E_PARAM_THRES for invalid argument */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_SETLAMTHRES,
                    IOM_E_PARAM_THRES);

    DetErr = 1U;
  }
  else
  {
    /* do nothing - Added for MISRA*/
  }
  /* Proceed only if no error was found */
  if(DetErr == 0U)
  #endif
  {
    LamThres = ThresVal & IOM_MAX_LAM_THRES;
    /*update threshold value in IOM_LAMEWS register*/
    /* MISRA2012_RULE_18_1_JUSTIFICATION: Array based indexing is performed
    to access the LAM registers efficiently.The access is checked to be
    within the bounds of the SFRs */
    IOM_MODULE_GLOB.LAMEWS[LamNo].U = LamThres;
  }

}


/*******************************************************************************
** Traceability    :    NA                                                    **
**                                                                            **
** Syntax          :    Iom_Lam_ThresType Iom_GetLamThreshold(                **
**                          const uint8 LamNo)                                **
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
Iom_Lam_ThresType Iom_GetLamThreshold(const uint8 LamNo)
{
  uint32 ThresVal;
  
  #if (IOM_DEV_ERROR_DETECT == STD_ON)
  uint8 DetErr;
  DetErr = 0U;
  /*Check if IOM is initialised*/
  if(Iom_InitStatus != IOM_INITIALISED )
  {
    /* Report DET IOM_E_UNINIT */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_GETLAMTHRES,
                    IOM_E_UNINIT);

    DetErr = 1U;
  }
  /*Check if Lam unit is not more than maximum Lam unit*/
  else if(LamNo > IOM_MAX_LAM_UNIT)
  {
    /* Report DET IOM_E_PARAM_LAM for invalid argument */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_GETLAMTHRES,
                    IOM_E_PARAM_LAM);

    DetErr = 1U;
  }
  else
  {
    /* do nothing - Added for MISRA */
  }
  /* Proceed only if no error was found */
  if(DetErr == 0U)
  #endif
  {
    /* MISRA2012_RULE_18_1_JUSTIFICATION: Array based indexing is performed
    to access the LAM registers efficiently.The access is checked to be
    within the bounds of the SFRs */
    /* Read LAMWES register and get threshold value for corresponding Lam */
    ThresVal = ((IOM_MODULE_GLOB.LAMEWS[LamNo].U) & IOM_MAX_LAM_THRES);
  }/* DetErr = 0  */
  #if (IOM_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* Invalid value is returned indicating DET is reported */
    ThresVal = 0xFFFFFFFFU;
  }
  #endif
  /* LAM threshold value is returned */
  return(ThresVal);
}

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
Iom_Lam_CountType Iom_GetLamEntWinCount(const uint8 LamNo)
{
  uint32 LamCnt;
  
  #if (IOM_DEV_ERROR_DETECT == STD_ON)
  uint8 DetErr;
  DetErr = 0U;
  /*Check if IOM is initialised*/
  if(Iom_InitStatus != IOM_INITIALISED )
  {
    /* Report DET IOM_E_UNINIT */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_GETLAMENTWINCOUNT,
                    IOM_E_UNINIT);

    DetErr = 1U;
  }
  /*Check if Lam unit is not more than maximum Lam unit*/
  else if(LamNo > IOM_MAX_LAM_UNIT)
  {
    /* Report DET IOM_E_PARAM_LAM for invalid argument */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_GETLAMENTWINCOUNT,
                    IOM_E_PARAM_LAM);

    DetErr = 1U;
  }
  else
  {
    /* do nothing - Added for MISRA*/
  }
  /* Proceed only if no error was found */
  if(DetErr == 0U)
  #endif
  {
    /* MISRA2012_RULE_18_1_JUSTIFICATION: Array based indexing is performed
    to access the LAM registers efficiently.The access is checked to be
    within the bounds of the SFRs */
    /* Read LAMEWC register and get event window count for corresponding Lam */
    LamCnt = ((IOM_MODULE_GLOB.LAMEWC[LamNo].U) & IOM_LAMEWCM_SETMASK);
  }
  #if (IOM_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* Invalid value is returned indicating DET is reported */
    LamCnt = 0xFFFFFFFFU;
  }
  #endif
  /* LAM count value is returned */
  return (LamCnt);
}


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
void Iom_SetEcmGlobalEveSel(const uint32 EventSel)
{
  #if (IOM_DEV_ERROR_DETECT == STD_ON)
  uint8 DetErr;
  DetErr = 0U;
  /*Check if IOM is initialised*/
  if(Iom_InitStatus != IOM_INITIALISED )
  {
    /* Report DET IOM_E_UNINIT */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_SETECMGLOBEVESEL,
                    IOM_E_UNINIT);

    DetErr = 1U;
  }
  /*Check if ECM global event selction is not more than maximum event combiner
    selection */
  else if(EventSel > IOM_ECMSELR_SETMASK)
  {
    /* Report DET IOM_E_PARAM_EVESEL for invalid argument */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_SETECMGLOBEVESEL,
                    IOM_E_PARAM_EVESEL);

    DetErr = 1U;
  }
  else
  {
    /* do nothing - Added for MISRA*/
  }
  /* Proceed only if no error was found */
  if(DetErr == 0U)
  #endif
  {
    /*update IOM_ECMSELR register with user passed value */
    IOM_ECMSELR.U = EventSel;
  }
}


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
Iom_Ecm_EveSelType Iom_GetEcmGlobalEveSel(void)
{
  uint32 EcmEveSel;
  
  #if (IOM_DEV_ERROR_DETECT == STD_ON)
  uint8 DetErr;
  DetErr = 0U;
  /*Check if IOM is initialised*/
  if(Iom_InitStatus != IOM_INITIALISED )
  {
    /* Report DET IOM_E_UNINIT */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_GETECMGLOBEVESEL,
                    IOM_E_UNINIT);

    DetErr = 1U;
  }
  /* Proceed only if no error was found */
  if(DetErr == 0U)
  #endif
  {
    /* Read IOM_ECMSELR for global event selection */
    EcmEveSel = (uint32)(IOM_ECMSELR.U);
  }
  #if (IOM_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* Invalid value is returned indicating DET is reported */
    EcmEveSel = 0xFFFFFFFFU;
  }
  #endif
  /* ECM global event selection register value is returned */
  return(EcmEveSel);
}


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
void Iom_SetEcmThresVal(const uint8 CounterNo, const uint8 CountVal, \
                        const uint8 SelInput)
{
  uint32 EcmThres;

  #if (IOM_DEV_ERROR_DETECT == STD_ON)
  uint8 DetErr;
  DetErr = 0U;
  /*Check if IOM is initialised*/
  if(Iom_InitStatus != IOM_INITIALISED )
  {
    /* Report DET IOM_E_UNINIT */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_SETECMTHRES,
                    IOM_E_UNINIT);

    DetErr = 1U;
  }
  /*Check if ECM counter is not more than maximum ECM counter */
  else if(CounterNo > IOM_ECM_COUNTER)
  {
    /* Report DET IOM_E_PARAM_CNT for invalid argument */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_SETECMTHRES,
                    IOM_E_PARAM_CNT);

    DetErr = 1U;
  }
  /*Check if ECM count value is not more than maximum threshold count value */
  else if(CountVal > IOM_MAXECM_THRES_COUNTVALUE)
  {
    /* Report DET IOM_E_PARAM_THRES for invalid argument */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_SETECMTHRES,
                    IOM_E_PARAM_THRES);

    DetErr = 1U;
  }
  /*Check if ECM select input is not more than maximum ECM event slect value */
  else if(SelInput > IOM_EVE_CHNL_SELMSK)
  {
    /* Report DET IOM_E_PARAM_CHNLSEL for invalid argument */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_SETECMTHRES,
                    IOM_E_PARAM_CHNLSEL);

    DetErr = 1U;
  }
  else
  {
    /* do nothing - Added for MISRA */
  }
  /* Proceed only if no error was found */
  if(DetErr == 0U)
  #endif
  {
    /* Set threshold value for selcted event channel and counter number */
    EcmThres = ((uint32)SelInput << (CounterNo * IOM_EVENT_COUNTER_SHIFT)) \
               | ((uint32)CountVal << (IOM_EVENTCNT_THR_SHIFT +  \
                                       (CounterNo * IOM_EVENT_COUNTER_SHIFT)));
    /*update threshold value of passed counter number in IOM_ECMCCFG register */
    IOM_ECMCCFG.U = EcmThres;
  }/* DetErr = 0  */
}


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
Iom_Ecm_ThresType Iom_GetEcmThresVal(const uint8 CounterNo)
{
  uint32 CountThres;
  uint32 ThresVal;

  #if (IOM_DEV_ERROR_DETECT == STD_ON)
  uint8 DetErr;
  DetErr = 0U;
  /*Check if IOM is initialised*/
  if(Iom_InitStatus != IOM_INITIALISED )
  {
    /* Report DET IOM_E_UNINIT */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_GETECMTHRES,
                    IOM_E_UNINIT);

    DetErr = 1U;
  }
  /*Check if ECM counter is not more than maximum ECM counter */
  else if(CounterNo > IOM_ECM_COUNTER)
  {
    /* Report DET IOM_E_PARAM_CNT for invalid argument */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_GETECMTHRES,
                    IOM_E_PARAM_CNT);

    DetErr = 1U;
  }
  else
  {
    /* do nothing - Added for MISRA */
  }
  /* Proceed only if no error was found */
  if(DetErr == 0U)
  #endif
  {
    /* Mask to get threshold value for selected counter number and event
    channel */
    CountThres = IOM_COUNT_THRES_VAL << (IOM_EVENTCNT_THR_SHIFT + \
                                         (CounterNo * IOM_EVENT_COUNTER_SHIFT));
    /* Threshold value is extracted for passed counter number */
    ThresVal = (CountThres & (IOM_ECMCCFG.U))\
               >> (IOM_EVENTCNT_THR_SHIFT + \
                   (CounterNo * IOM_EVENT_COUNTER_SHIFT));
  }
  #if (IOM_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* Invalid value is returned indicating DET is reported */
    ThresVal = 0xFF;
  }
  #endif
  /* ECM threshold value is returned */
  return((uint8)ThresVal);
}


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
**                      ETB,ETC and ETD                                       **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    :    uint16: ECM event trigger history                     **
**                                                                            **
** Description     :    This service returns ECM event trigger history        **
**                                                                            **
*******************************************************************************/
Iom_Ecm_EveHisType Iom_GetEcmEveTrigHis(const Iom_EventHistory EveHistory)
{
  uint32 EveTrigHis = 0;

  #if (IOM_DEV_ERROR_DETECT == STD_ON)
  uint8 DetErr;
  DetErr = 0U;
  /*Check if IOM is initialised*/
  if(Iom_InitStatus != IOM_INITIALISED )
  {
    /* Report DET IOM_E_UNINIT */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_GETECMEVETRIGHIS,
                    IOM_E_UNINIT);

    DetErr = 1U;
  }
  /* Check if Event History is not within valid range */
  else if(!((EveHistory == IOM_EVETRIG_HISTORY_A) || \
            (EveHistory == IOM_EVETRIG_HISTORY_B) || \
            (EveHistory == IOM_EVETRIG_HISTORY_C) || \
            (EveHistory == IOM_EVETRIG_HISTORY_D)))
  {
    /* Report DET IOM_E_PARAM_EVEHSTRY for invalid argument */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_GETECMEVETRIGHIS,
                    IOM_E_PARAM_EVEHSTRY);

    DetErr = 1U;
  }
  else
  {
    /* do nothing - Added for MISRA */
  }
  /* Proceed only if no error was found */
  if(DetErr == 0U)
  #endif
  {
    /* If event trigger history selected is ETA */
    if(EveHistory == IOM_EVETRIG_HISTORY_A)
    {
      /* Get event trigger history of ETA */
      EveTrigHis = (IOM_MODULE_GLOB.ECMETH0.U) & IOM_EVEHISTRY_MSK;
    }
    /* If event trigger history selected is ETB */
    else if(EveHistory == IOM_EVETRIG_HISTORY_B)
    {
      /* Get event trigger history of ETB */
      EveTrigHis = ((IOM_MODULE_GLOB.ECMETH0.U >> IOM_EVEHISTRY_SHIFT)
                    & IOM_EVEHISTRY_MSK);
    }
    /* If event trigger history selected is ETC */
    else if(EveHistory == IOM_EVETRIG_HISTORY_C)
    {
      /* Get event trigger history of ETC */
      EveTrigHis = (IOM_MODULE_GLOB.ECMETH1.U) & IOM_EVEHISTRY_MSK;
    }
    /* If event trigger history selected is ETD */
    else
    {
      /* Get event trigger history of ETD */
      EveTrigHis = ((IOM_MODULE_GLOB.ECMETH1.U >> IOM_EVEHISTRY_SHIFT)
                    & IOM_EVEHISTRY_MSK);
    }
  }
  #if (IOM_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* Invalid value is returned indicating DET is reported */
    EveTrigHis = 0xFFFFFFFFU;
  }
  #endif
  /* ECM Event trigger history is returned */
  return(EveTrigHis);
}


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
void Iom_ClrEcmStatusHistory(void)
{
  #if (IOM_DEV_ERROR_DETECT == STD_ON)
  uint8 DetErr;
  DetErr = 0U;
  /*Check if IOM is initialised*/
  if(Iom_InitStatus != IOM_INITIALISED )
  {
    /* Report DET IOM_E_UNINIT */
    Det_ReportError((uint16)IOM_MODULE_ID,
                    IOM_INSTANCE_ID,
                    IOM_SID_CLRECMSTATHIS,
                    IOM_E_UNINIT);

    DetErr = 1U;
  }
  /* Proceed only if no error was found */
  if(DetErr == 0U)
  #endif
  {
    /* Clear Event Trigger History register */
    IOM_ECMETH0.U = IOM_ECMETH_CLR_VALUE;
    IOM_ECMETH1.U = IOM_ECMETH_CLR_VALUE;
  }
}


#if (IOM_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Traceability    :    NA                                                    **
**                                                                            **
** Syntax          :    void Iom_GetVersionInfo                               **
**                      (                                                     **
**                        Std_VersionInfoType * const versioninfo             **
**                      )                                                     **
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
void Iom_GetVersionInfo(Std_VersionInfoType * const versioninfo)
{
  #if (IOM_DEV_ERROR_DETECT == STD_ON)
  /* Check for DET: IOM_E_PARAM_POINTER */
  if ((versioninfo) == NULL_PTR)
  {
    /* Report IOM_E_PARAM_POINTER DET if service called with
         NULL_PTR
    */
    Det_ReportError(
      IOM_MODULE_ID,
      IOM_INSTANCE_ID,
      IOM_SID_GETVERINFO,
      IOM_E_PARAM_INVALID);
  }
  else
  #endif  /*IOM_DEV_ERROR_DETECT == STD_ON*/
  {
    /* Vendor ID information */
    (versioninfo)->vendorID = IOM_VENDOR_ID;
    /*IOM module ID information */
    (versioninfo)->moduleID = IOM_MODULE_ID;
    /*IOM Instance ID information */
    /* IOM module Software major version information */
    (versioninfo)->sw_major_version = (uint8)IOM_SW_MAJOR_VERSION;
    /* IOM module Software minor version information */
    (versioninfo)->sw_minor_version = (uint8)IOM_SW_MINOR_VERSION;
    /* IOM module Software patch version information */
    (versioninfo)->sw_patch_version = (uint8)IOM_SW_PATCH_VERSION;
  }
}
#endif


/*******************************************************************************
** Traceability    : NA                                                       **
**                                                                            **
** Syntax          : static void Iom_lResetKernels(uint8)                     **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : NA                                                       **
**                                                                            **
** Parameters (in) : ServiceId: Id to determine Reset Kernel call             **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : This service returns kernel reset for all                **
**                   available kernels                                        **
**                                                                            **
*******************************************************************************/
static void Iom_lResetKernels(uint8 ServiceId)
{
  volatile uint32 ReadBack;
  uint32 TimeOutVar;
  uint32 KernelRstReq;
  uint32 KernelRstClr;
  /* Read and set mask for kernel reset register KRST0 */
  KernelRstReq = IOM_KRST0.U;
  KernelRstReq &= (IOM_REG_CLRMASK_VALUE);
  KernelRstReq |= IOM_REG_SETMASK_VALUE;

  /* If kernel reset requested during init, deinit or runtime */
  if((ServiceId == IOM_INIT_ACCESS) || (ServiceId == IOM_DEINIT_ACCESS))
  {
    /*update IOM_KRST0 register*/
    IOM_LIB_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(&IOM_KRST0.U, \
        KernelRstReq);
    /* Read back the KRST0 register to flush the pipeline effects */
    ReadBack = (uint32)IOM_KRST0.U;
  }
  else
  {
    /*update IOM_KRST0 register*/
    IOM_LIB_RUNTIME_WRITEPERIPENDINITPROTREG(&IOM_KRST0.U, KernelRstReq);
    /* Read back the KRST0 register to flush the pipeline effects */
    ReadBack = (uint32)(IOM_KRST0.U);
  }
  /* Read and set mask for kernel reset register KRST1 */
  KernelRstReq = IOM_KRST1.U;
  KernelRstReq &= (IOM_REG_CLRMASK_VALUE);
  KernelRstReq |= IOM_REG_SETMASK_VALUE;
  /* If kernel reset requested during init, deinit or runtime */
  if((ServiceId == IOM_INIT_ACCESS) || (ServiceId == IOM_DEINIT_ACCESS))
  {
    /*update IOM_KRST1 register*/
    IOM_LIB_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(&IOM_KRST1.U, \
        KernelRstReq);
    /* Read back the KRST1 register to flush the pipeline effects */
    ReadBack = (uint32)IOM_KRST1.U;
  }
  else
  {
    /*update IOM_KRST1 register*/
    IOM_LIB_RUNTIME_WRITEPERIPENDINITPROTREG(&IOM_KRST1.U, KernelRstReq);
    /* Read back the KRST1 register to flush the pipeline effects */
    ReadBack = (uint32)(IOM_KRST1.U);
  }

  /* Wait time for Kernel Reset */
  TimeOutVar = IOM_KRST_TIMEOUT_VALUE;
  do
  {
    TimeOutVar--;
  } while(((((IOM_KRST0.U) &\
             IOM_KRST0_RSTSTAT) >> IOM_KRST0_RSTSTAT_BITPOS) != 1U) && \
          (TimeOutVar > 0U));

  /* Read and set mask for kernel reset status clear register KRSTCLR */
  KernelRstClr = IOM_KRSTCLR.U;
  KernelRstClr &= (IOM_REG_CLRMASK_VALUE);
  KernelRstClr |= IOM_REG_SETMASK_VALUE;
  /* If kernel reset status clear requested during init, deinit or runtime */
  if((ServiceId == IOM_INIT_ACCESS) || (ServiceId == IOM_DEINIT_ACCESS))
  {
    /*update IOM_KRSTCLR register */
    IOM_LIB_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(&IOM_KRSTCLR.U, \
        KernelRstClr);
    /* Read back the KRSTCLR register to flush the pipeline effects */    
    ReadBack = (uint32)(IOM_KRSTCLR.U);
  }

  UNUSED_PARAMETER(ReadBack);
}


#define IOM_STOP_SEC_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Iom_MemMap.h"
