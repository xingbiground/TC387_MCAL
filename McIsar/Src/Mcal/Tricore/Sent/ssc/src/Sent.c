/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2020)                                 **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : Sent.c                                                     **
**                                                                            **
**  VERSION      : 1.40.0_16.0.0                                              **
**                                                                            **
**  DATE         : 2020-03-05                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : SENT Driver source file                                    **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                               Includes                                     **
*******************************************************************************/
/* Inclusion of SENT Register description file */
#include "IfxSent_reg.h"
/* Inclusion of Mcal Specific Global Header File */
#include "Mcal_Compiler.h"
/* Pre-compile/static configuration parameters for SENT  */
/* Includes Own header file Sent.h */
#include "Sent.h"
#if( (SENT_INIT_DEINIT_API_MODE != SENT_MCAL_SUPERVISOR) )
#include "McalLib_OsStub.h"
#endif
/* Conditional Inclusion of Developement Error Tracer File */
#if (SENT_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif /* (SENT_DEV_ERROR_DETECT == STD_ON) */
/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/
#ifndef SENT_SW_MAJOR_VERSION
#error "SENT_SW_MAJOR_VERSION is not defined. "
#endif
#ifndef SENT_SW_MINOR_VERSION
#error "SENT_SW_MINOR_VERSION is not defined. "
#endif
#ifndef SENT_SW_PATCH_VERSION
#error "SENT_SW_PATCH_VERSION is not defined. "
#endif
/* Check for Correct inclusion of headers */
#if ( SENT_SW_MAJOR_VERSION != 10U )
#error "SENT_SW_MAJOR_VERSION does not match. "
#endif
#if ( SENT_SW_MINOR_VERSION != 40U )
#error "SENT_SW_MINOR_VERSION does not match. "
#endif
#if ( SENT_SW_PATCH_VERSION != 1U )
#error "SENT_SW_PATCH_VERSION does not match. "
#endif
#if (SENT_DEV_ERROR_DETECT == STD_ON)

#ifndef DET_AR_RELEASE_MAJOR_VERSION
#error "DET_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif


#if ( DET_AR_RELEASE_MAJOR_VERSION != 4U )
#error "DET_AR_RELEASE_MAJOR_VERSION does not match. "
#endif

#endif /*#if (SENT_DEV_ERROR_DETECT == STD_ON)*/
/*******************************************************************************
**                         User Mode Macros                                   **
*******************************************************************************/
#if (SENT_INIT_DEINIT_API_MODE == SENT_MCAL_SUPERVISOR)
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for
User mode support in code. No side effects foreseen by violating this MISRA
rule. */
#define SENT_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(RegAdd,Data)\
Mcal_WritePeripEndInitProtReg(RegAdd,Data)
#else
#define SENT_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(RegAdd,Data)\
MCAL_LIB_WRITEPERIPENDINITPROTREG(RegAdd,Data)
#endif
/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
#if (SENT_SPC_USED == STD_ON)
/* Bit value of the TRIG bit in the SCR SFR*/
#define SENT_SPCCONFIG_TRIGSRC_SHIFT        (6U)
/* Bit value of the DELAY bit in the SCR SFR*/
#define SENT_SPCCONFIG_DELAY_SHIFT          (8U)
/* Bit value of the TIMEBASE bit in the SCR SFR*/
#define SENT_SPCCONFIG_TIMEBASE_SHIFT       (14U)
#endif /* SENT_SPC_USED == STD_ON */
/* Counter value for the kernel reset*/
#define SENT_KERNEL_RESET_WAIT_COUNT        (0x00000100U)
#define SENT_ONE_U                          (0x1U)
#if (MCAL_NO_OF_CORES > SENT_ONE_U)
/* Channel register reset*/
#define SENT_CHANNEL_RESET_REG              (0x0U)
/*Macro to reset IOCR register
bit 10(CEC) clears bit 20 to 27(EC) of IOCR
bit 14(CREG) clears bit 12(REG) of IOCR
bit 15(CFEG) clears bit 13(FEG) of IOCR
bit 28(CTR) clears bit 29(TRM) of IOCR*/
#define SENT_IOCR_RESET_REG                 (0x1000C400U)
#endif
/* Mask bit to enable the module*/
#define SENT_CLC_DISR_DISABLE               (0xEU)
/* Module Disable Request Bit*/
#define SENT_ENABLE_LAST_BIT                (0x00000001)
/* Values used by the SENT module*/
#define SENT_ZERO_U                         (0x0U)
#define SENT_TWO_U                          (0x2U)
#define SENT_WDI_SHIFT                      (28U)
#define SENT_SDI_SHIFT                      (24U)
#define SENT_ERRI_SHIFT                     (20U)
#define SENT_TBI_SHIFT                      (16U)
#define SENT_TDI_SHIFT                      (12U)
#define SENT_RBI_SHIFT                      (8U)
#define SENT_RDI_SHIFT                      (4U)
/* Maximum frame length*/
#define SENT_MAX_FRAME_LENGTH               (8U)
/*******************************************************************************
**                   Function like macro definitions                          **
*******************************************************************************/
/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/
/* Data type used for core specific SENT driver global data storage */
/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
#if (SENT_DEV_ERROR_DETECT == STD_ON)
/* function to verify DET check */
static uint32 Sent_lDetCheck(uint8 ServiceID,
const Sent_ChannelIdxType ChannelId,
const void * Ptr);
/* Function for validate the requested configuration */
static Std_ReturnType Sent_lInitDetCheck( const Sent_ConfigType *CfgPtr,
const uint8 CoreId);
#endif
#if((SENT_RESET_SFR_AT_INIT == STD_ON) || (SENT_DEINIT_API == STD_ON))
/* Function to reset Kernels */
static Std_ReturnType Sent_lResetKernels(void);
#endif
/* Function to initialize the Core specific SENT Module */
static void Sent_lCoreInit(const uint8 CoreId,
const Sent_ConfigType *ConfigPtr);
/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define SENT_START_SEC_VAR_CLEARED_QM_GLOBAL_8
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Sent_MemMap.h"
/* Variable to hold the pointers to variables holding core specific
states */
#if (SENT_DEV_ERROR_DETECT == STD_ON)
static uint8 Sent_GblCoreState[MCAL_NO_OF_CORES];
#endif
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define SENT_STOP_SEC_VAR_CLEARED_QM_GLOBAL_8
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Sent_MemMap.h"
/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define SENT_START_SEC_VAR_CLEARED_QM_GLOBAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Sent_MemMap.h"
/* To store the Sent driver configuration pointer */
static const Sent_ConfigType *Sent_kConfigPtr;
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define SENT_STOP_SEC_VAR_CLEARED_QM_GLOBAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Sent_MemMap.h"
/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
/* Mapping the code */
#define SENT_START_SEC_CODE_QM_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Sent_MemMap.h"
/*******************************************************************************
** Traceability    :                                                          **
**                                                                            **
** Syntax          : void Sent_Init                                           **
**                    (                                                       **
**                      const Sent_ConfigType const *ConfigPtr                **
**                    )                                                       **
**                                                                            **
** Description     : This function:                                           **
**                      - Initializes the SENT Module, Baud Rate registers    **
**                      - Also configures the respective Channels registers   **
**                                                                            **
** Service ID:  0x98                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  ConfigPtr - Pointer to SENT configuration               **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
void Sent_Init(const Sent_ConfigType * const ConfigPtr)
{
  uint8 CoreId;
  uint32 TempVal;
  Std_ReturnType ErrStatus;
  /* Get core id which is executing currently */
  CoreId = (uint8)Mcal_GetCpuIndex();
  #if (SENT_DEV_ERROR_DETECT == STD_ON)
  /* Do the initialization DET checks */
  ErrStatus = Sent_lInitDetCheck(ConfigPtr, CoreId);
  /* Check all DET is passed */
  if(ErrStatus != E_NOT_OK)
  #endif /* SENT_DEV_ERROR_DETECT == STD_ON */
  {
    if(CoreId == MCAL_MASTER_COREID)
    {
      /* Kernel clock initialization Sequence */
      TempVal = (uint32)(ConfigPtr->ModuleClkDiv);
      TempVal |= (uint32) (SENT_CLC.U  & SENT_CLC_DISR_DISABLE);
      SENT_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(&SENT_CLC, TempVal);
      /* Read back the CLC register to flush the pipeline effects */
      if (SENT_CLC.B.DISS == SENT_ZERO_U)
      {
        #if (SENT_RESET_SFR_AT_INIT == STD_ON)
        ErrStatus = Sent_lResetKernels();
        if( ErrStatus == E_OK)
        #endif
        {
          /* Load the Fractional Divider register with normal mode operation*/
          TempVal = (uint32)((uint32)(ConfigPtr->ModuleFracDivStep) | 0x4000U);
          TempVal |= SENT_FDR.U;
          SENT_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(&SENT_FDR, TempVal);
          /* Configure the TimeStamp Pre-Divider register with the same
          frequency as fracdiv*/
          SENT_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(&SENT_TPD, SENT_ZERO_U);
          #if (SENT_MAX_CHANNELS_MASTER_CORE != SENT_ZERO_U)
          /*Initialize master core variables*/
          Sent_lCoreInit(CoreId,ConfigPtr);
          #endif
          #if (SENT_DEV_ERROR_DETECT == STD_ON)
          /* Set Status to indicate that initialization is done */
          Sent_GblCoreState[MCAL_MASTER_COREID]= SENT_MOD_INITIALIZED;
          #endif
          /* Take copy of passed global config pointer in master core */
          Sent_kConfigPtr = ConfigPtr;
        }
      }/*SENT_CLC.B.DISS == 0U*/
    }
    #if (MCAL_NO_OF_CORES > SENT_ONE_U)
    else
    {
      if (SENT_CLC.B.DISS == SENT_ZERO_U)
      {
        /*Initialize slave core channels */
        Sent_lCoreInit(CoreId,ConfigPtr);
        #if (SENT_DEV_ERROR_DETECT == STD_ON)
        /* Set Status to indicate that initialization is done */
        Sent_GblCoreState[CoreId]= SENT_MOD_INITIALIZED;
        #endif
      }
    }
    #endif
  }
}/* End of Function: Sent_Init */
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : void Sent_SetChannel                                    **
**                    (                                                       **
**                      const Sent_ChannelIdxType ChanId,                     **
**                      Sent_ChanOpType Operation                             **
**                    )                                                       **
**                                                                            **
** Description      : This function:                                          **
**                      - Enables/Disables the SENT Channel                   **
**                                                                            **
** Service ID       : 0x99                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters(in)   : Channel_Id - SENT logical channel number                **
**                    Operation - SENT_ENABLE/SENT_DISABLE                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                     **
**                                                                            **
*******************************************************************************/
void Sent_SetChannel(const Sent_ChannelIdxType ChanId,
Sent_ChanOpType Operation)
{
  #if (SENT_DEV_ERROR_DETECT == STD_ON)
  if (Sent_lDetCheck(SENT_SID_SETCHANNEL, ChanId, NULL_PTR) == E_OK)
  #endif
  {
    uint8 Channel;
    uint8 Flag;
    /*Extracting the physical channel ID*/
    Channel = Sent_kConfigPtr->Sent_PhysicalChanId[ChanId];
    if (Operation == SENT_ENABLE)
    {
      Flag = SENT_ONE_U;
    }
    else
    {
      Flag = SENT_ZERO_U;
    }
    SENT_CHANNEL[Channel].RCR.B.CEN = Flag;
  }
} /* End of Function: Sent_SetChannel */
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : uint32 Sent_ReadData                                    **
**                    (                                                       **
**                      const Sent_ChannelIdxType ChannelId                   **
**                    )                                                       **
**                                                                            **
** Description      : This function:                                          **
**                      - reads the nibbles received in the Data register     **
**                                                                            **
** Service ID       : 0x9A                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters(in)   : ChannelId - SENT Channel whose data has to be read      **
**                                                                            **
** Parameters (out) :   none                                                  **
**                                                                            **
** Return value     : Data read from the SENT Channel                         **
**                                                                            **
*******************************************************************************/
uint32 Sent_ReadData(const Sent_ChannelIdxType ChannelId)
{
  uint32 DataVal;
  Sent_ChannelIdxType Channel;

  #if (SENT_DEV_ERROR_DETECT == STD_ON)
  DataVal = SENT_ZERO_U;
  if (Sent_lDetCheck(SENT_SID_READDATA, ChannelId, NULL_PTR) == E_OK)
  #endif
  {
    /*Extracting the physical channel ID*/
    Channel = Sent_kConfigPtr->Sent_PhysicalChanId[ChannelId];
    DataVal = SENT_RDR[Channel].U;
  }
  return DataVal;
} /* End of Function: Sent_ReadData */
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : void Sent_ReadSerialData                                **
**                    (                                                       **
**                      const Sent_ChannelIdxType ChannelId,                  **
**                      Sent_RxSerialDataType *DataPtr                        **
**                    )                                                       **
**                                                                            **
** Description      : This function:                                          **
**                      - reads the Serial data recieved and collected over   **
**                        several SENT frames                                 **
**                                                                            **
** Service ID       : 0x9B                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters(in)   : ChannelId - SENT Channel's serial data has to be read   **
**                                                                            **
** Parameters (out) : DataPtr -Data pointer pointing to the serial data read  **
**                              from the SENT Channel                         **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
*******************************************************************************/
void Sent_ReadSerialData(const Sent_ChannelIdxType ChannelId,
Sent_RxSerialDataType * const DataPtr)
{
  uint8 Channel;
  #if (SENT_DEV_ERROR_DETECT == STD_ON)
  if (Sent_lDetCheck(SENT_SID_READSERIALDATA, ChannelId, DataPtr) == E_OK)
  #endif
  {
    /*Extracting the physical channel ID*/
    Channel = Sent_kConfigPtr->Sent_PhysicalChanId[ChannelId];
    DataPtr->Data = SENT_CHANNEL[Channel].SDS.B.SD;
    DataPtr->MsgId = (uint8) SENT_CHANNEL[Channel].SDS.B.MID;
    DataPtr->Configuration = SENT_CHANNEL[Channel].SDS.B.CON;
    DataPtr->Crc = SENT_CHANNEL[Channel].SDS.B.SCRC;
  }
} /* End of Function: Sent_ReadSerialData */
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : void Sent_ReadChannelStatus                             **
**                    (                                                       **
**                      const Sent_ChannelIdxType ChannelId,                  **
**                      Sent_ChanStatusType *StatPtr                          **
**                    )                                                       **
**                                                                            **
** Description      : This function:                                          **
**                      - reads the Channel status                            **
**                      - Also collects the Timestamp                         **
**                                                                            **
** Service ID       : 0x9C                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters(in)   : ChannelId - SENT Channel's status has to be read        **
**                                                                            **
** Parameters (out) : StatPtr - Pointer pointing to the status of the SENT    **
**                              Channel                                       **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
*******************************************************************************/
void Sent_ReadChannelStatus(const Sent_ChannelIdxType ChannelId,
Sent_ChanStatusType * const StatPtr)
{
  uint8 Channel;
  #if (SENT_DEV_ERROR_DETECT == STD_ON)
  if (Sent_lDetCheck(SENT_SID_READCHANSTATUS, ChannelId, StatPtr) == E_OK)
  #endif
  {
    /*Extracting the physical channel ID*/
    Channel = Sent_kConfigPtr->Sent_PhysicalChanId[ChannelId];
    StatPtr->RxTimeStamp = SENT_TIMESTAMP[Channel].U;
    /*MISRA2012_RULE_11_4_JUSTIFICATION: Conversion between pointer to
    object and integer type is permitted for special function registers*/
    /* MISRA2012_RULE_10_5_JUSTIFICATION: Unsigned to enum typecast is
    performed as API return type is an enum, whereas return value is from
    SFR defined as unsigned int. */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: Assignment to narrower type enum
    is performed however CST possible values (from SFR) are within
    allowed enum values. */
    StatPtr->ChanStat = (Sent_ChanStateType)SENT_CHANNEL[Channel].RSR.B.CST;
    StatPtr->StatCommNibble = SENT_CHANNEL[Channel].RSR.B.SCN;
    StatPtr->RxCrc = SENT_CHANNEL[Channel].RSR.B.CRC;
    StatPtr->IntStat = SENT_CHANNEL[Channel].INTSTAT.U;
  }
} /* End of Function: Sent_ReadChannelStatus */
#if (SENT_SPC_USED == STD_ON)
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : void Sent_SpcGenPulse                                   **
**                    (                                                       **
**                      const Sent_ChannelIdxType ChanId,                     **
**                      const Sent_SpcType *SpcCfgPtr                         **
**                    )                                                       **
**                                                                            **
** Description      : This function:                                          **
**                      - generates a Master pulse for SPC Sync transmission  **
**                      - can be used for Bi-Directional mode also            **
**                                                                            **
** Service ID       : 0x9D                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters(in)   : ChannelId - SENT Channel's status has to be read        **
**                    Sent_SpcType - Pointer to configure the SPC mode and    **
**                                   generate a master pulse                  **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
*******************************************************************************/
void Sent_SpcGenPulse (const Sent_ChannelIdxType ChanId,
const Sent_SpcType * const SpcCfgPtr)
{
  uint8 Error = E_OK;
  /* Get core id which is executing currently */
  uint32 TimeOut = SENT_TIMEOUT_VALUE;
  /* check if Transaction is in progress, before proceeding !!! */
  uint8 Channel;
  uint8 ChanIdx;
  const Sent_ChannelCfgType * ChanPtr;
  uint8 CoreId = (uint8)Mcal_GetCpuIndex();
  #if (SENT_DEV_ERROR_DETECT == STD_ON)
  if (Sent_lDetCheck(SENT_SID_SPCGENPULSE, ChanId, SpcCfgPtr) == E_OK)
  #endif
  {
    /*Extract the index of channel configuration and the channel configuration*/
    ChanIdx = Sent_kConfigPtr->Sent_ChannelLookUpTable[ChanId].
              Sent_ChannelIndex;
    ChanPtr = Sent_kConfigPtr->SentCorePtr[CoreId]->Sent_ChannelConfig;
    /*Extracting the physical channel ID*/
    Channel = Sent_kConfigPtr->Sent_PhysicalChanId[ChanId];
    while ((SENT_CHANNEL[Channel].SCR.B.TRQ == 1U) && (TimeOut > SENT_ZERO_U))
    {
      /* Wait for Transaction to be completed */
      TimeOut--;
    }
    if (TimeOut == SENT_ZERO_U)
    {
      ChanPtr[ChanIdx].CallbackFn(Channel, SENT_TRANS_INPROGRESS_EVENT);
      /* Skip the API functionality and return from the API */
      Error = E_NOT_OK;
    }
    if (Error == E_OK)
    {
      uint32 SCR_RegVal;
      SCR_RegVal = (SpcCfgPtr->PulseLength) |
      ((uint32)SpcCfgPtr->TriggerSource << SENT_SPCCONFIG_TRIGSRC_SHIFT) |
      ((uint32)SpcCfgPtr->Delay << SENT_SPCCONFIG_DELAY_SHIFT) |
      ((uint32)SpcCfgPtr->TimeBase << SENT_SPCCONFIG_TIMEBASE_SHIFT);
      SENT_CHANNEL[Channel].SCR.U = SCR_RegVal;
      if (SpcCfgPtr->Mode == BIDIRECTIONAL_MODE)
      {
        /* Enable Buffer Underflow interrupt also */
        SENT_CHANNEL[Channel].INTEN.B.TBI = SENT_ONE_U;
      }
    } /* Error == 0U for SENT_E_TRANS_INPROGRESS */
  } /* DetError */
} /* End of Function: Sent_SpcGenPulse */
#endif /* SENT_SPC_USED == STD_ON */
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : void Sent_SetWdgTimer                                   **
**                    (                                                       **
**                      const Sent_ChannelIdxType ChanId,                     **
**                      uint16 WdgTimerReloadVal                              **
**                    )                                                       **
**                                                                            **
** Description      : This function:                                          **
**                      - configures the Channel's watchdog timer             **
**                                                                            **
** Service ID       : 0x9E                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters(in)   : ChannelId - SENT Channel's status has to be read        **
**                    WdgTimerReloadVal - Watchdog Reload Timer value         **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
*******************************************************************************/
void Sent_SetWdgTimer(const Sent_ChannelIdxType ChanId,
const uint16 WdgTimerReloadVal)
{
  uint8 Channel;
  #if (SENT_DEV_ERROR_DETECT == STD_ON)
  if (Sent_lDetCheck(SENT_SID_CONFIGWDG, ChanId, NULL_PTR) == E_OK)
  #endif
  {
    /*Extracting the physical channel ID*/
    Channel = Sent_kConfigPtr->Sent_PhysicalChanId[ChanId];
    SENT_CHANNEL[Channel].INTEN.B.WDI = SENT_ONE_U;
    SENT_CHANNEL[Channel].WDT.B.WDL = WdgTimerReloadVal;
  }
} /* End of Function: Sent_SetWdgTimer */
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : Sent_GlitchStatusType Sent_ReadGlitchFilterStatus       **
**                    (                                                       **
**                      const Sent_ChannelIdxType ChannelId                   **
**                    )                                                       **
**                                                                            **
** Description      : This function:                                          **
**                      - reads the status of the glitch filter               **
**                                                                            **
** Service ID       : 0xA1                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters(in)   : ChannelId - SENT Channel's status has to be read        **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK: Glitch is detected during rising or falling edge  **
**                   E_NOT_OK  :     Glitch is not detected                   **
*******************************************************************************/
Std_ReturnType Sent_ReadGlitchFilterStatus (const Sent_ChannelIdxType ChannelId)
{
  Std_ReturnType RetValue = E_NOT_OK;
  uint8 Channel;
  static Sent_GlitchStatusType GlitchStat;
  #if (SENT_DEV_ERROR_DETECT == STD_ON)
  if (Sent_lDetCheck(SENT_SID_READGLITCHSTATUS, ChannelId, NULL_PTR) == E_OK)
  #endif
  {
    /*Extracting the physical channel ID*/
    Channel = Sent_kConfigPtr->Sent_PhysicalChanId[ChannelId];
    GlitchStat.RisingEdge = SENT_CHANNEL[Channel].IOCR.B.REG;
    GlitchStat.FallingEdge = SENT_CHANNEL[Channel].IOCR.B.FEG;
    if (GlitchStat.RisingEdge == 1U)
    {
      RetValue = E_OK;
    }
    else if (GlitchStat.FallingEdge == 1U)
    {
      RetValue = E_OK;
    }
    else
    {
      RetValue = E_NOT_OK;
    }
  }
  return RetValue;
} /* End of Function: Sent_ReadGlitchFilterStatus */
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : void Sent_ResetGlitchFilterStatus                       **
**                    (                                                       **
**                      const Sent_ChannelIdxType ChannelId                   **
**                    )                                                       **
**                                                                            **
** Description      : This function:                                          **
**                      - resets the status flag after glitch filtering and   **
**                        signal inversion                                    **
**                                                                            **
** Service ID       : 0xA2                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters(in)   : ChannelId - SENT Channel's status has to be read        **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
*******************************************************************************/
void Sent_ResetGlitchFilterStatus (const Sent_ChannelIdxType ChannelId)
{
  uint8 Channel;
  uint8 SignalEdge;
  #if (SENT_DEV_ERROR_DETECT == STD_ON)
  if (Sent_lDetCheck(SENT_SID_RESETGLITCHSTATUS, ChannelId, NULL_PTR) == E_OK)
  #endif
  {
    /*Extracting the physical channel ID*/
    Channel = Sent_kConfigPtr->Sent_PhysicalChanId[ChannelId];
    SignalEdge = SENT_CHANNEL[Channel].IOCR.B.RXM;
    if(SignalEdge != SENT_CHANNEL[Channel].IOCR.B.IIE)
    {
      SENT_CHANNEL[Channel].IOCR.B.CFEG = SENT_ONE_U;
      SENT_CHANNEL[Channel].IOCR.B.CREG = SENT_ONE_U;
    }
  }
} /* End of Function: Sent_ResetGlitchFilterStatus */
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : Std_ReturnType Sent_FDFLParameters                      **
**                    (                                                       **
**                      const Sent_ChannelIdxType ChanId                      **
**                    )                                                       **
**                                                                            **
** Description      : This function:                                          **
**                      - Does the frequency drift analysis in frames         **
**                        with pause pulse                                    **
**                                                                            **
** Service ID       : 0xA3                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters(in)   : ChannelId - SENT Channel's status has to be read        **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value    : E_OK - Accept the frame                                  **
**                   E_NOT_OK - Reject the frame                              **
**                                                                            **
*******************************************************************************/
Std_ReturnType Sent_FDFLParameters (const Sent_ChannelIdxType ChannelId)
{
  Std_ReturnType RetValue = E_NOT_OK;
  #if (SENT_DEV_ERROR_DETECT == STD_ON)
  if (Sent_lDetCheck(SENT_SID_FDFLPARAMETERS, ChannelId, NULL_PTR) == E_OK)
  #endif
  {
    sint32 Diff;
    uint16 Framelength = 0U;
    uint16 MeasuredDiv1 = 0U, MeasuredDiv2;
    uint32 Ratio1 =0;
    uint32  Ratio2=0;
    uint8 Channel;
    uint16 TimeOut;
    uint8 Error = E_OK;
    uint8 Frame;
    /*Extracting the physical channel ID*/
    Channel = Sent_kConfigPtr->Sent_PhysicalChanId[ChannelId];


    if(SENT_CHANNEL[Channel].RCR.B.FDFL != SENT_ZERO_U)
    {

      /* check if RSI has been issued, before proceeding !!! */
      /* Loop for two frames*/
      for(Frame = SENT_ZERO_U; Frame < SENT_TWO_U; Frame++)
      {
        TimeOut = SENT_TIMEOUT_VALUE;
        while ((SENT_CHANNEL[Channel].INTSTAT.B.RSI != 1U) &&
        (TimeOut > SENT_ZERO_U))
        {
          /* Wait for Transaction to be completed */
          TimeOut--;
        }
        if (TimeOut == SENT_ZERO_U)
        {
          Error = SENT_ONE_U;
        }
        if ((Error == SENT_ZERO_U) && (Frame == 0U))
        {
          Framelength = SENT_CHANNEL[Channel].RSR.B.FRLEN;
          MeasuredDiv1 = SENT_CHANNEL[Channel].CFDR.B.DIVM;
          /* MISRA2012_RULE_10_8_JUSTIFICATION: Impermissible cast of
          composite expression used for negative value*/
          Ratio1 = ((uint32)(Framelength * 10000U) / MeasuredDiv1);
        }
        else if((Error == SENT_ZERO_U) && (Frame == 1U))
        {
          MeasuredDiv2 = SENT_CHANNEL[Channel].CFDR.B.DIVM;
          /* MISRA2012_RULE_10_8_JUSTIFICATION: Impermissible cast of
          composite expression used for negative value*/
          Ratio2 = ((uint32)(Framelength * 10000U) /MeasuredDiv2);
        }
        else
        {
          break;
        }
      }
      /* MISRA2012_RULE_10_8_JUSTIFICATION: Impermissible cast of
      composite expression used for negative value*/
      Diff =(sint32) (Ratio1 - Ratio2);


      if ((Diff < 15625) && (Diff > -15625))
      {
        RetValue = E_OK;
      }
      else
      {
        RetValue = E_NOT_OK;
      }
    }
  }
  return RetValue;
} /* End of Function: Sent_FDFLParameters */
#if (SENT_DEINIT_API == STD_ON)
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : void Sent_DeInit                                        **
**                    (                                                       **
**                      void                                                  **
**                    )                                                       **
**                                                                            **
** Description      : This function:                                          **
**                      - De-Initializes the SENT Module and it's registers,  **
**                      - also with respective Channels registers             **
**                                                                            **
** Service ID       : 0xA0                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
*******************************************************************************/
/*CYCLOMATIC_Sent_DeInit_JUSTIFICATION: This Function has cyclomatic
Complexity >15. Multiple conditions needed to verify if channel notification
needs to be provided. Further breakdown cannot be
done in order to maintain readability.*/
void Sent_DeInit (void)
{
  uint32 TempVal = 0;
  Sent_ChannelIdxType ChanIndex;
  Sent_ChannelIdxType ChannelId;
  Sent_ChannelIdxType Channels;
  uint8 ErrStatus = E_NOT_OK;
  #if(SENT_DEV_ERROR_DETECT == STD_ON)
  #if((SENT_MULTICORE_ERROR_DETECT == STD_ON) && (MCAL_NO_OF_CORES > SENT_ONE_U))
  uint8 CoreIdx;
  #endif
  #endif
  const Sent_ChannelCfgType* lChannelConfigPtr;
  /* Get core Id which is currently executing */
  uint8 CoreId = (uint8) Mcal_GetCpuIndex();
  #if (SENT_DEV_ERROR_DETECT == STD_ON)
  uint8 DevError = E_OK;
  /* Check if the channel is in uninitialized state */
  if ((Sent_GblCoreState[CoreId]) != SENT_MOD_INITIALIZED)
  {
    /* Report to DET */
    Det_ReportError(
    (uint16)SENT_MODULE_ID,
    SENT_INSTANCE_ID,
    SENT_SID_DEINIT,
    SENT_E_UNINIT);
    DevError = E_NOT_OK;
  }
  #if((SENT_MULTICORE_ERROR_DETECT == STD_ON) && (MCAL_NO_OF_CORES > SENT_ONE_U))
  else if (MCAL_MASTER_COREID == CoreId)
  {
    for (CoreIdx = 0U; CoreIdx < (uint8)MCAL_NO_OF_CORES; CoreIdx++)
    {
      if ((MCAL_MASTER_COREID != CoreIdx) &&
      (Sent_GblCoreState[CoreIdx] != SENT_UNINITIALIZED))
      {
        Det_ReportError(
        (uint16)SENT_MODULE_ID,
        SENT_INSTANCE_ID,
        SENT_SID_DEINIT,
        SENT_E_SLAVE_CORE_INIT);
        DevError = E_NOT_OK;
        break;
      }
    }
  }
  else
  {
    /*Do Nothing*/
  }
  #endif /* SENT_MULTICORE_ERROR_DETECT == STD_ON */
  if (E_NOT_OK != DevError)
  #endif /* SENT_DEV_ERROR_DETECT == STD_ON */
  {
    /*Deinit for the master core*/
    if(MCAL_MASTER_COREID == CoreId)
    {
      /* Core specific configuration pointer */
      lChannelConfigPtr = Sent_kConfigPtr->SentCorePtr[CoreId]->
                          Sent_ChannelConfig;
      Channels = Sent_kConfigPtr->SentCorePtr[CoreId]->MaxChannels;
      for (ChanIndex = SENT_ZERO_U; ChanIndex < Channels;
      ChanIndex++)
      {
        /*Physical channel ID of the channel */
        ChannelId = lChannelConfigPtr[ChanIndex].ChanId;
        /* Reset the suspend enable bit */
        SENT_CHANNEL[ChannelId].RCR.B.SUSEN = SENT_ZERO_U;
      }
      /* Sent Kernel Reset to set registers to default value */
      ErrStatus = Sent_lResetKernels();
      if(ErrStatus != E_NOT_OK){
        Sent_kConfigPtr = NULL_PTR;
        /* Disable the SENT module clock */
        TempVal = ((uint32)SENT_CLC.U | (uint32)SENT_ENABLE_LAST_BIT);
        SENT_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(&SENT_CLC,
        ((uint32)TempVal));
        #if(SENT_DEV_ERROR_DETECT == STD_ON)
        Sent_GblCoreState[CoreId]= SENT_UNINITIALIZED;
        #endif /* SENT_DEV_ERROR_DETECT == STD_ON */
      }
    }
    #if (MCAL_NO_OF_CORES > SENT_ONE_U)
    /*Slave core deinitialization*/
    else
    {
      /* Core specific configuration pointer */
      lChannelConfigPtr = Sent_kConfigPtr->SentCorePtr[CoreId]->
                          Sent_ChannelConfig;
      Channels = Sent_kConfigPtr->SentCorePtr[CoreId]->MaxChannels;
      for (ChanIndex = SENT_ZERO_U; ChanIndex < Channels;
      ChanIndex++)
      {
        /*Physical channel ID of the channel */
        ChannelId = lChannelConfigPtr[ChanIndex].ChanId;
        /* ReSet the respective Channel registers */
        SENT_CHANNEL[ChannelId].INTEN.U = SENT_CHANNEL_RESET_REG;
        SENT_CHANNEL[ChannelId].INP.U   = SENT_CHANNEL_RESET_REG;
        SENT_CHANNEL[ChannelId].VIEW.U  = SENT_CHANNEL_RESET_REG;
        SENT_CHANNEL[ChannelId].IOCR.U  = SENT_IOCR_RESET_REG;
        SENT_CHANNEL[ChannelId].RCR.U   = SENT_CHANNEL_RESET_REG;
        SENT_CHANNEL[ChannelId].CFDR.U  = SENT_CHANNEL_RESET_REG;
        SENT_CHANNEL[ChannelId].CPDR.U  = SENT_CHANNEL_RESET_REG;
      }
      #if(SENT_DEV_ERROR_DETECT == STD_ON)
      Sent_GblCoreState[CoreId]= SENT_UNINITIALIZED;
      #endif /* SENT_DEV_ERROR_DETECT == STD_ON */
    }
    #endif
  }
}/* End of Function: Sent_DeInit */
#endif /* SENT_DEINIT_API == STD_ON */
#if (SENT_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : void Sent_GetVersionInfo                                **
**                    (                                                       **
**                      Std_VersionInfoType* const versioninfo                **
**                    )                                                       **
**                                                                            **
** Description      : - This function returns the version information of this **
**                      module.The version information include : Module ID,   **
**                      Vendor ID,Vendor specific version numbers             **
**                                                                            **
** Service ID       : 0x9F                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in) : none                                                    **
**                                                                            **
** Parameters (out) : versioninfo - Pointer to store the                      **
**                    version information of this module.                     **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
*******************************************************************************/
void Sent_GetVersionInfo(Std_VersionInfoType* const versioninfo)
{
  #if (SENT_DEV_ERROR_DETECT == STD_ON )
  if ((versioninfo) == NULL_PTR)
  {
    Det_ReportError((uint16)SENT_MODULE_ID,
    SENT_INSTANCE_ID,
    SENT_SID_GETVERINFO,
    SENT_E_PARAM_POINTER
    );
  }
  else
  #endif /* #if (SENT_DEV_ERROR_DETECT == STD_ON )  */
  {
    ((Std_VersionInfoType*)(versioninfo))->moduleID = SENT_MODULE_ID;
    ((Std_VersionInfoType*)(versioninfo))->vendorID = SENT_VENDOR_ID;
    ((Std_VersionInfoType*)(versioninfo))->sw_major_version =
    (uint8)SENT_SW_MAJOR_VERSION;
    ((Std_VersionInfoType*)(versioninfo))->sw_minor_version =
    (uint8)SENT_SW_MINOR_VERSION;
    ((Std_VersionInfoType*)(versioninfo))->sw_patch_version =
    (uint8)SENT_SW_PATCH_VERSION;
  }
}
#endif /* #if( (SENT_VERSION_INFO_API == STD_ON) */
#if((SENT_RESET_SFR_AT_INIT == STD_ON) || (SENT_DEINIT_API == STD_ON))
/*******************************************************************************
** Traceability    :                                                          **
**                                                                            **
** Syntax          : static Std_ReturnType Sent_lResetKernels(void)           **
**                                                                            **
** Description     : This function :                                          **
**                    - Execute kernel reset for all available kernels        **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : NA                                                       **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: No DET error occurred                              **
**                   E_NOT_OK: DET error occurred                             **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Sent_lResetKernels(void)
{
  uint32 lWaitCount;
  uint32 TempVal;
  Std_ReturnType lRetVal = E_OK;
  /*Clear the ENDINIT bit in the WDT_CONSR register in order
  to disable the write-protection for registers protected
  via the EndInit feature */
  /* Set request to reset the SENT Kernel */
  TempVal = ((uint32)SENT_KRST0.U | (uint32)SENT_ENABLE_LAST_BIT);
  SENT_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(&SENT_KRST0, TempVal);
  TempVal = ((uint32)SENT_KRST1.U | (uint32)SENT_ENABLE_LAST_BIT);
  SENT_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(&SENT_KRST1, TempVal);
  /* Set the ENDINIT bit in the WDT_CONSR register again
  to enable the write-protection and to prevent a time-out */
  lWaitCount = (uint32)SENT_KERNEL_RESET_WAIT_COUNT;
  do
  {
    lWaitCount--;
  }
  while((SENT_KRST0.B.RSTSTAT != SENT_ONE_U) && (lWaitCount > SENT_ZERO_U));
  /*Clear the ENDINIT bit in the WDT_CONSR register in order
  to disable the write-protection for registers protected
  via the EndInit feature */
  if(lWaitCount == SENT_ZERO_U){
    /*Reset of kernals is not successful*/
    lRetVal = E_NOT_OK;
  }
  else{
    /* Clear the SENT Kernel Reset Flag */
    TempVal = ((uint32)SENT_KRSTCLR.U | (uint32)SENT_ENABLE_LAST_BIT);
    SENT_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(&SENT_KRSTCLR, TempVal);
  }
  return lRetVal;
}
#endif
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : void Sent_Isr (uint8 IntrNode)                          **
**                                                                            **
** Description      : This function:                                          **
**                      - is the interrupt handler and collects the status    **
**                        of the relevant channels and inform the user        **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters(in)   : IntrNode - Interrupt Node number                        **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
*******************************************************************************/
void Sent_Isr(uint8 IntrNode)
{
  uint32 IntStat;
  Sent_ChannelIdxType ChanIdx;
  Sent_ChannelIdxType PhyChId;
  uint8   CoreId = (uint8)Mcal_GetCpuIndex();
  const Sent_CoreConfigType *CorePtr;
  CorePtr = Sent_kConfigPtr->SentCorePtr[CoreId];
  const Sent_ChannelCfgType * ChanPtr;
  uint8 ChanIntNode;
  for (ChanIdx = SENT_ZERO_U; ChanIdx < CorePtr->MaxChannels; ChanIdx++)
  {
    /* extract the channel configuration*/
    ChanPtr = CorePtr->Sent_ChannelConfig;
    /*get the interrupt node configured for the channel*/
    ChanIntNode= ChanPtr[ChanIdx].Sent_InterruptNode;
    if (IntrNode == ChanIntNode)
    {
      /* get the SENT Physical channel id */
      PhyChId = ChanPtr[ChanIdx].ChanId;
      IntStat = SENT_CHANNEL[PhyChId].INTSTAT.U;
      if ((IntStat & SENT_CHANNEL_CFG_INTEN) != SENT_ZERO_U)
      {
        /* Notify the Application */
        ChanPtr[ChanIdx].CallbackFn(ChanIdx, IntStat);
        /* Clear the respective Interrupt events */
        SENT_CHANNEL[PhyChId].INTCLR.U = IntStat;
      }
    }
  } /* end of for */
} /* End of Interrupt Handler : Sent_Isr */
/*******************************************************************************
**                      Local Function Definitions                            **
*******************************************************************************/
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax           : static uint32 Sent_lDetCheck                            **
**                    (                                                       **
**                      uint8 ServiceID                                       **
**                      const Sent_ChannelIdxType ChannelId                   **
**                    )                                                       **
**                                                                            **
** Description      : This function:                                          **
**                       - checks whether SENT module is initialized or not   **
**                       - also verifies if the SENT channel has been         **
**                         configured or not. Raising DET if error.           **
**                       - also verifies if the OutPtr is not NULL            **
**                                                                            **
** Service ID       :                                                         **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters(in)   : ServiceID - Informs Service ID of an API                **
**                    ChannelId - SENT logical channel number                 **
**                    OutPtr    - Output pointer                              **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK: No DET error occurred                             **
**                    E_NOT_OK: DET error occurred                            **
**                                                                            **
*******************************************************************************/
#if (SENT_DEV_ERROR_DETECT == STD_ON)
static uint32 Sent_lDetCheck (uint8 ServiceID,
Sent_ChannelIdxType ChannelId,
const void *Ptr)
{
  uint32 RetVal = E_OK;
  uint8 CoreId = (uint8) Mcal_GetCpuIndex();
  Sent_ChannelIdxType PhyChId;
  #if(SENT_MULTICORE_ERROR_DETECT == STD_ON)
  uint8 CoreCh;
  #endif
  if ((Sent_GblCoreState[CoreId]) == SENT_UNINITIALIZED)
  {
    /* Report to DET */
    Det_ReportError
    (
    (uint16)SENT_MODULE_ID,
    SENT_INSTANCE_ID,
    ServiceID,
    SENT_E_UNINIT
    );
    RetVal = E_NOT_OK;
  }
  else if(ChannelId >= SENT_HW_MAX_CHANNELS)
  {
    /* Report to DET */
    Det_ReportError
    (
    (uint16)SENT_MODULE_ID,
    SENT_INSTANCE_ID,
    ServiceID,
    SENT_E_INVALID_CHANNEL
    );
    RetVal = E_NOT_OK;
  }
  /*check if the channel is configuration is available*/
  else if(ChannelId >= SENT_MAX_CHANNELS_CONFIGURED)
  {
    /* Report to DET */
    Det_ReportError
    (
    (uint16)SENT_MODULE_ID,
    SENT_INSTANCE_ID,
    ServiceID,
    SENT_E_CHANNEL_NOT_CONFIGURED
    );
    RetVal = E_NOT_OK;
  }
  else if (
  ((ServiceID == SENT_SID_SPCGENPULSE) ||
  (ServiceID == SENT_SID_READCHANSTATUS) ||
  (ServiceID == SENT_SID_READSERIALDATA)) && (Ptr == NULL_PTR)){
    /* Report to DET */
    Det_ReportError
    (
    (uint16)SENT_MODULE_ID,
    SENT_INSTANCE_ID,
    ServiceID,
    SENT_E_PARAM_POINTER
    );
    RetVal = E_NOT_OK;
  }
  /*check for the channel status except for the set channel and
  read channel status APIs*/
  else if((ServiceID != SENT_SID_SETCHANNEL) &&
         (ServiceID != SENT_SID_READCHANSTATUS))
  {
    /*Extracting the physical channel ID*/
    PhyChId = Sent_kConfigPtr->Sent_PhysicalChanId[ChannelId];
    if((uint8)(SENT_CHANNEL[PhyChId].RCR.B.CEN) != (uint8)SENT_ENABLE){
      /* Report to DET */
      Det_ReportError
      (
      (uint16)SENT_MODULE_ID,
      SENT_INSTANCE_ID,
      ServiceID,
      SENT_E_CHANNEL_NOT_ENABLED
      );
      RetVal = E_NOT_OK;
    }
  }
  else{
    /*Do nothing*/
  }
  /* Extract the channel assigned as per core */
  #if(SENT_MULTICORE_ERROR_DETECT == STD_ON)
  /*Get the core ID assigend with the channel*/
  CoreCh = Sent_kConfigPtr-> Sent_ChannelLookUpTable[ChannelId].
                           Sent_ChannelCore;
  /* Report to DET */
  /* Check if channel is assigned to core */
  if ((RetVal == E_OK) && (CoreCh != CoreId))
  {
    Det_ReportError
    (
    (uint16)SENT_MODULE_ID,
    SENT_INSTANCE_ID,
    ServiceID,
    SENT_E_CORE_CHANNEL_MISMATCH
    );
    RetVal = E_NOT_OK;
  }
  #endif
  return RetVal;
} /* End of Function: Sent_lDetCheck */
#endif
/*******************************************************************************
**                                                                            **
** Traceability    :                                                          **
**                                                                            **
** Syntax          : static void Sent_lCoreInit(const uint8 CoreId)           **
**                                                                            **
** Service ID      : None(local API)                                          **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non reentrant                                            **
**                                                                            **
** Parameters (in) : CoreId                                                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : This function initialize all variables                   **
**                   used by the SENT driver module to an initial state.      **
**                   There are no such variables in the SENT module           **
*******************************************************************************/
static void Sent_lCoreInit(const uint8 CoreId, const Sent_ConfigType *
                           const ConfigPtr)
{
  uint32 TempVal;
  Sent_ChannelIdxType ChanIndex;
  Sent_ChannelIdxType PhyChannelId;
  const Sent_CoreConfigType* CorePtr;
  /* Core specific configuration pointer */
  CorePtr = ConfigPtr->SentCorePtr[CoreId];
  /* Initialize the core-x variables */
  /* Reset all core variables to "0" */
  /* Set the core status to IDLE */
  for (ChanIndex = SENT_ZERO_U; ChanIndex <
  CorePtr->MaxChannels; ChanIndex++)
  {
    /* Retrieve the SENT Physical channel id */
    PhyChannelId = CorePtr->Sent_ChannelConfig[ChanIndex].ChanId;
    /*Consolidate the same Interrupt node for all interrupts specific to a
    channel*/
    TempVal = CorePtr->Sent_ChannelConfig[ChanIndex].Sent_InterruptNode;
    TempVal = (TempVal << SENT_WDI_SHIFT)
    | (TempVal << SENT_SDI_SHIFT)
    | (TempVal << SENT_ERRI_SHIFT)
    | (TempVal << SENT_TBI_SHIFT)
    | (TempVal << SENT_TDI_SHIFT)
    | (TempVal << SENT_RBI_SHIFT)
    | (TempVal << SENT_RDI_SHIFT)
    | TempVal;
    /* Configure the respective Channel registers */
    SENT_CHANNEL[PhyChannelId].CPDR.U =
    CorePtr->Sent_ChannelConfig[ChanIndex].ChanPreDiv;
    SENT_CHANNEL[PhyChannelId].CFDR.U =
    CorePtr->Sent_ChannelConfig[ChanIndex].ChanFracDiv;
    SENT_CHANNEL[PhyChannelId].RCR.U =
    CorePtr->Sent_ChannelConfig[ChanIndex].ChanRxCtrl;
    SENT_CHANNEL[PhyChannelId].IOCR.U =
    CorePtr->Sent_ChannelConfig[ChanIndex].ChanIOCtrl;
    SENT_CHANNEL[PhyChannelId].VIEW.U =
    CorePtr->Sent_ChannelConfig[ChanIndex].ChanDataView;
    SENT_CHANNEL[PhyChannelId].INP.U = TempVal;
    SENT_CHANNEL[PhyChannelId].INTEN.U = SENT_CHANNEL_CFG_INTEN;
    if (CorePtr->Sent_ChannelConfig[ChanIndex].ChanFrameLen >
    SENT_MAX_FRAME_LENGTH)
    {
      /* Clear RSI and enable only RDI interrupt */
      SENT_CHANNEL[PhyChannelId].INTEN.B.RSI = SENT_ZERO_U;
      SENT_CHANNEL[PhyChannelId].INTEN.B.RDI = SENT_ONE_U;
    }
  }
}
#if (SENT_DEV_ERROR_DETECT == STD_ON)
/*******************************************************************************
** Syntax          : static uint8 Sent_lInitDetCheck                          **
**                          (const Sent_ConfigType *CfgPtr                    **
**                                          const uint8 CoreId)               **
**                                                                            **
** Service ID      : none                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : non reentrant                                            **
**                                                                            **
** Parameters (in) : CfgPtr - Pointer to configuration set                    **
**                   CoreId : Core Number                                     **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value    : ErrorFlag (uint32)                                       **
**                                                                            **
** Description     : Local function :Service for DET check in Sent_Init()     **
**                                   function                                 **
**                                                                            **
** Traceability    :                                                          **
*******************************************************************************/
static Std_ReturnType Sent_lInitDetCheck( const Sent_ConfigType * const CfgPtr,
const uint8 CoreId)
{
  Std_ReturnType ErrStatus;
  /* Initialize the return variable */
  ErrStatus = E_OK;
  /* Check validity of configPtr */
  /* Det Check for NULL pointer  */
  if (NULL_PTR == CfgPtr )
  {
    /*Report to DET upon error, Init has been called with wrong
    parameter NULL Config Pointer*/
    Det_ReportError(
    (uint16)SENT_MODULE_ID,
    SENT_INSTANCE_ID,
    SENT_SID_INIT,
    SENT_E_INIT_FAILED);
    /* Report Error */
    ErrStatus = E_NOT_OK;
  }
  #if ((SENT_MULTICORE_ERROR_DETECT == STD_ON) && (MCAL_NO_OF_CORES > SENT_ONE_U))
  /* Check if current core is slave core */
  else if(MCAL_MASTER_COREID != CoreId)
  {
    if((Sent_GblCoreState[MCAL_MASTER_COREID]) == SENT_UNINITIALIZED)
    {
      ErrStatus = E_NOT_OK;
      Det_ReportError(
      (uint16)SENT_MODULE_ID,
      SENT_INSTANCE_ID,
      SENT_SID_INIT,
      SENT_MASTER_CORE_UNINIT);
    }
    else if (Sent_kConfigPtr != CfgPtr)
    {
      ErrStatus = E_NOT_OK;
      Det_ReportError(
      (uint16)SENT_MODULE_ID,
      SENT_INSTANCE_ID,
      SENT_SID_INIT,
      SENT_E_INIT_FAILED);
    }
    else
    {
      /* Do Nothing */
    }
  }
  else
  {
    /* Do nothing */
  }
  #endif/* #if (SENT_MULTICORE_ERROR_DETECT == STD_ON) */
  if(E_NOT_OK != ErrStatus)
  {
    if((Sent_GblCoreState[CoreId]) != SENT_UNINITIALIZED)
    {
      ErrStatus = E_NOT_OK;
      Det_ReportError(
      (uint16)SENT_MODULE_ID,
      SENT_INSTANCE_ID,
      SENT_SID_INIT,
      SENT_E_ALREADY_INITIALIZED);
    }
    /* Check if core is configured */
    #if(SENT_MAX_CHANNELS_MASTER_CORE == SENT_ZERO_U)
    else if((NULL_PTR == CfgPtr->SentCorePtr[CoreId]) &&
    (MCAL_MASTER_COREID != CoreId))
    #else
    else if(NULL_PTR == CfgPtr->SentCorePtr[CoreId])
    #endif
    {
      /* Report Error */
      ErrStatus = E_NOT_OK;
      /* if core is configured */
      Det_ReportError
      ((uint16)SENT_MODULE_ID,
      SENT_INSTANCE_ID,
      SENT_SID_INIT,
      SENT_E_CORE_NOT_CONFIGURED);/* End of report to DET */
    }
    else
    {
      /* Do nothing */
    }
  }
  return ErrStatus;
} /* End of Sent_lInitDetCheck() function */
#endif
/* MISRA2012_RULE_2_5_JUSTIFICATION:This Macro is used for the memmap section.
Memory Map of the SENT Code*/
#define SENT_STOP_SEC_CODE_QM_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Sent_MemMap.h"
