/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2020)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME    : I2c.c                                                       **
**                                                                            **
**  VERSION     : 1.40.0_17.0.0                                               **
**                                                                            **
**  DATE        : 2020-05-14                                                  **
**                                                                            **
**  VARIANT     : Variant PB                                                  **
**                                                                            **
**  PLATFORM    : Infineon AURIX2G                                            **
**                                                                            **
**  AUTHOR      : DL-AUTOSAR-Engineering                                      **
**                                                                            **
**  VENDOR      : Infineon Technologies                                       **
**                                                                            **
**  DESCRIPTION : This file contains functionality of I2C driver.             **
**                                                                            **
**  MAY BE CHANGED BY USER [yes/no]: No                                       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

#include "IfxI2c_reg.h"

/* Module header file. This also includes configuration file */
#include "I2c.h"

#if(I2C_INIT_DEINIT_API_MODE != I2C_MCAL_SUPERVISOR)
#include "McalLib_OsStub.h"
#endif

/* Conditional Inclusion of Developement Error Tracer File */
#if (I2C_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif /* (DIO_DEV_ERROR_DETECT == STD_ON) */

/*******************************************************************************
**                      Imported Compiler Switch Checks                       **
*******************************************************************************/
#ifndef I2C_SW_MAJOR_VERSION
#error "I2C_SW_MAJOR_VERSION is not defined. "
#endif

#ifndef I2C_SW_MINOR_VERSION
#error "I2C_SW_MINOR_VERSION is not defined. "
#endif

#ifndef I2C_SW_PATCH_VERSION
#error "I2C_SW_PATCH_VERSION is not defined. "
#endif

#if (I2C_SW_MAJOR_VERSION != 10U)
#error "I2C_SW_MINOR_VERSION does not match. "
#endif

#if (I2C_SW_MINOR_VERSION != 40U)
#error "I2C_SW_MINOR_VERSION does not match. "
#endif

#if (I2C_SW_PATCH_VERSION != 1U)
#error "I2C_SW_PATCH_VERSION does not match. "
#endif

#if (I2C_DEV_ERROR_DETECT == STD_ON)
#ifndef DET_AR_RELEASE_MAJOR_VERSION
  #error "DET_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

#if ( DET_AR_RELEASE_MAJOR_VERSION != 4U )
  #error "DET_AR_RELEASE_MAJOR_VERSION does not match. "
#endif
#endif

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/


#define I2C_DISABLE_INTERFACE                (0U)
#define I2C_ENABLE_INTERFACE                 (1U)
#define I2C_PACKET_SIZE_7BIT_ADDR   ((uint8)1U)
#define I2C_CLK_DISABLE             ((uint8)1U)
#define I2C_PACKET_SIZE_10BIT_ADDR ((uint8)2U)
#define I2C_PROTOCOL_INTERRUPT_MASK          ((uint32)0x0000007FU)
#define I2C_ERROR_INTERRUPT_MASK             ((uint32)0x0000000FU)
#define I2C_CLEAR_INTERRUPT                  ((uint32)0x0000000FU)
#define I2C_BURST_REQ_CHK                    ((uint32)0x000000C0U)
#define I2C_RAW_INTERRUPT_MASK               ((uint32)0x0000000FU)
#define I2C_ENABLE_INTERRUPT_MASK            ((uint32)0x0000003FU)

#define I2C_KERNEL_RESET_WAIT_COUNTS        (0x100U)
#define I2C_FIFO_BYTES_FULL                 ((uint16)0x1FU)
#define I2C_FIFO_BYTES_HALF_FULL            ((uint16)0x10U)
#define I2C_FIFO_STAGES_FULL                ((uint8)0x08U)
#define I2C_FIFO_STAGES_HALF_FULL           ((uint8)0x04U)
#define I2C_FIFO_SINGLE_STAGE_FULL          ((uint8)0x01U)
#define I2C_FIFO_MAX_DATA_IN_EACH_STAGE     ((uint8)0x04U)
#define I2C_SHIFT_EIGHT_BIT                 ((uint8)0x08U)
#define I2C_SHIFT_ONE_BIT                   ((uint8)0x01U)
#define I2C_EIGHT_BIT_MASK                  ((uint8)0xFFU)
#define I2C_10_BIT_ADDRESS_PREAMBLE         ((uint8)0xF0U)
#define I2C_MASTER_CODE                     (0x09U)
#define I2C_FLAG_SET                        (uint8)(0x01U)

#define I2C_WRITE_OPERATION                 (0x00U)
#define I2C_READ_OPERATION                  (0x01U)

#if (I2C_DEV_ERROR_DETECT == STD_ON)
#define I2C_UNINITIALIZED   (0U)
#define I2C_INITIALIZED     (1U)
#define I2C_7_BIT_MAX_SLAVE_ADD  (0x7FU)
#define I2C_10_BIT_MAX_SLAVE_ADD (0x3FFU)
#define I2C_MAX_SUPPORTED_SIZE   (0x3FFFU)
#endif

/*******************************************************************************
**                         User Mode Macros                                   **
*******************************************************************************/
#if(I2C_INIT_DEINIT_API_MODE == I2C_MCAL_SUPERVISOR)
/* Library APIs  */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 *'I2C_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG'
 *defined for User mode support in code.
 *No side effects foreseen by violating this MISRA rule. */
#define I2C_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(RegAdd,Data)   \
    Mcal_WritePeripEndInitProtReg(RegAdd,Data)
/* Supervisory mode registers */
  /* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
   * I2C_SFR_INIT_DEINIT_WRITE32
   * defined for User mode support in code.
   * No side effects foreseen by violating this MISRA rule. */
  #define I2C_SFR_INIT_DEINIT_WRITE32(reg, value) (*(reg) = (uint32)(value))
/* Supervisory mode registers */
  /* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
   * I2C_SFR_INIT_DEINIT_READ32
   * defined for User mode support in code.
   * No side effects foreseen by violating this MISRA rule. */
  #define I2C_SFR_INIT_DEINIT_READ32(reg) (*reg)
#else
/* Library APIs  */
#define I2C_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(RegAdd,Data)   \
    MCAL_LIB_WRITEPERIPENDINITPROTREG(RegAdd,Data)
/* Supervisory mode registers */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
* I2C_SFR_INIT_DEINIT_WRITE32
* defined for User mode support in code.
* No side effects foreseen by violating this MISRA rule. */
#define I2C_SFR_INIT_DEINIT_WRITE32(reg, value)    \
            MCAL_SFR_OS_WRITE32(I2C_MODULE_ID, reg, value)
/* Supervisory mode registers */
  /* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
   * I2C_SFR_INIT_DEINIT_READ32
   * defined for User mode support in code.
   * No side effects foreseen by violating this MISRA rule. */
#define I2C_SFR_INIT_DEINIT_READ32(reg)    \
            MCAL_SFR_OS_READ32(I2C_MODULE_ID, reg)
#endif

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

typedef enum
{
  I2C_RX_NOT_STARTED = 0u,
  I2C_RX_INITIATED,
  I2C_RX_COMMAND_SENT,
  I2C_RX_IN_PROGRESS,
  I2C_RX_COMPLETED
}I2c_RxTransferStateType;

typedef enum
{
  I2C_TX_IN_PROGRESS = 0u,
  I2C_TX_COMPLETED
}I2c_TxTransferStateType;

typedef enum
{
  I2C_NO_OPERATION = 0u,
  I2C_WRITE,
  I2C_READ
}I2c_OperationType;

typedef struct
{
  /* Data buffer pointer */
  I2c_DataType * DataPtr;
  /* Channel Transmit state */
  I2c_ChannelStatusType HwState;
  /* Number of bytes pending to transmit */
  I2c_SizeType DataLeft;
  /* Number of bytes transmited */
  I2c_SizeType TotalDataTxd;
  /* I2c Operation */
  I2c_OperationType I2c_Operation;
  /* I2c Slave Address */
  I2c_SlaveAddrType SlaveAddr;
  /* Read State */
  I2c_RxTransferStateType RxTransferState;
} I2c_ChannelInfoType;
/*******************************************************************************
**                     Private Function Declarations:                         **
*******************************************************************************/
/*Memory Map of the I2C Code*/
#define I2C_START_SEC_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "I2c_MemMap.h"
static I2c_ErrorType I2c_lSyncTransmit(Ifx_I2C* const HwModulePtr,
                           I2c_ChannelInfoType * const ChannelInfo,
                           const I2c_ChannelType ChannelId);
static I2c_ErrorType I2c_lSyncReceive(Ifx_I2C* const HwModulePtr,
                      I2c_ChannelInfoType * const ChannelInfo,
                      const I2c_ChannelType ChannelId);
static void I2c_lHwEnableInterrupt(Ifx_I2C* const HwModulePtr);

#if (I2C_DEV_ERROR_DETECT == STD_ON)
static I2c_ErrorType I2c_ReadWriteDetCheck(const I2c_ChannelType ChannelId,
                const I2c_DataType *const DataPtr, const I2c_SizeType Size,
                const I2c_SlaveAddrType SlaveAddress, const uint8 ServiceId);
#endif

static void I2c_lSendMasterCode(Ifx_I2C* const HwModulePtr);
static void I2c_lHwClearAllInterrupts(Ifx_I2C* const HwModulePtr);
static uint8 I2c_lHwInit(const uint8 HwUnit,const I2c_ConfigType* ConfigPtr);
static void I2c_lHwUpdateModuleReg(const uint8 HwUnit,
                              const I2c_ChannelConfigType *const ChannelConfigPtr);
static void I2c_lResetKernels(Ifx_I2C* const HwModulePtr);
static void  I2c_lWrite(Ifx_I2C* const HwModulePtr,
                           I2c_ChannelInfoType* const ChannelInfo);
static void I2c_lRead(Ifx_I2C* const HwModulePtr,
                            I2c_ChannelInfoType* const ChannelInfo);

#define I2C_STOP_SEC_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "I2c_MemMap.h"

/*******************************************************************************
**                      Hw  Apis                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/
#define I2C_START_SEC_CONST_QM_LOCAL_32
/*
 * To be used for global constants (32 bits)
 * Inclusion of I2c_MemMap.h
*/
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "I2c_MemMap.h"

static Ifx_I2C * const I2c_HwModuleAddr[I2C_MAX_HW_UNIT] = {I2C_REG_ADDR};

#define I2C_STOP_SEC_CONST_QM_LOCAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "I2c_MemMap.h"


/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define I2C_START_SEC_VAR_CLEARED_QM_LOCAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "I2c_MemMap.h"

/* This variable is used to store the I2c driver configuration pointer */
static const I2c_ConfigType * I2c_ConfigPtr;
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define I2C_STOP_SEC_VAR_CLEARED_QM_LOCAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "I2c_MemMap.h"

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define I2C_START_SEC_VAR_CLEARED_QM_LOCAL_8
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "I2c_MemMap.h"
static uint8 I2c_ChannelMap[I2C_MAX_HW_UNIT];

#if (I2C_DEV_ERROR_DETECT == STD_ON)
/* This variable is used to check the initialisation status*/
static uint8 I2c_InitStatus;
#endif/*(I2C_DEV_ERROR_DETECT == STD_ON)*/

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define I2C_STOP_SEC_VAR_CLEARED_QM_LOCAL_8
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "I2c_MemMap.h"

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define I2C_START_SEC_VAR_CLEARED_QM_LOCAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "I2c_MemMap.h"

static I2c_ChannelInfoType I2c_ChannelInfo[I2C_MAX_CHANNELS];

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define I2C_STOP_SEC_VAR_CLEARED_QM_LOCAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "I2c_MemMap.h"


/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
/*Memory Map of the I2C Code*/
#define I2C_START_SEC_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "I2c_MemMap.h"
/*******************************************************************************
**                                                                            **
** Syntax          : void I2c_Init(const I2c_ConfigType* ConfigPtr)           **
**                                                                            **
** Service ID      : 0x4F                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : ConfigPtr - Pointer to I2c Driver configuration set      **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : Driver Module Initialization                             **
**                    1.This function will initialize all relevant registers  **
**                      of I2C perpheral with the values of structure         **
**                      ConfigPtr                                             **
**                                                                            **
*******************************************************************************/
void I2c_Init
(
  const I2c_ConfigType* const ConfigPtr
)
{
  const I2c_ChannelConfigType* ChannelConfigPtr;
  Ifx_I2C* HwModulePtr;
  uint8 ClkDisableChk;
  uint8 Channel;
  uint8 HwUnit;

  ClkDisableChk = 0U;
  /***********************DET Check starts*************************************/
  #if (I2C_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType Returnvalue;
  Returnvalue = E_OK;

  if (ConfigPtr == NULL_PTR)
  {
    /* Report to  DET */
    Det_ReportError(I2C_MODULE_ID, I2C_INSTANCE_ID, I2C_SID_INIT, \
                    I2C_E_INIT_FAILED );
    Returnvalue = E_NOT_OK;
  }
  else if (I2c_InitStatus == I2C_INITIALIZED)
  {
    /* Report to  DET */
    Det_ReportError(I2C_MODULE_ID, I2C_INSTANCE_ID, I2C_SID_INIT, \
                    I2C_E_ALREADY_INITIALIZED);
    Returnvalue = E_NOT_OK;
  }
  else
  {
    /* No action required */
  }

  if (Returnvalue == E_OK)
  #endif
    /***********************DET Check ends*************************************/

    /***********Clock and General Configurations assignment starts*************/
  {
    for(Channel = 0U; Channel < ConfigPtr->I2c_MaxChannels; Channel++)
    {
      ChannelConfigPtr = &(ConfigPtr->I2c_ChannelConfigPtr[Channel]);
      HwUnit = ChannelConfigPtr->HwUnit;
      I2c_ChannelMap[HwUnit] = Channel;
      ClkDisableChk = I2c_lHwInit(HwUnit, ConfigPtr);
      if(0U == ClkDisableChk)
      {
      /* HW Clock initilisation */
        HwModulePtr = I2c_HwModuleAddr[ChannelConfigPtr->HwUnit];
        /* Store ConfigPtr for use by APIs*/
        I2c_lHwUpdateModuleReg(HwUnit,ChannelConfigPtr);
        I2c_lHwClearAllInterrupts(HwModulePtr);
      }
    }
    if(0U == ClkDisableChk)
    {
      for(Channel = 0U; Channel < ConfigPtr->I2c_MaxChannels; Channel++)
      {
        I2c_ChannelInfo[Channel].HwState = I2C_IDLE;
      }
      I2c_ConfigPtr = ConfigPtr;
      #if (I2C_DEV_ERROR_DETECT == STD_ON)
      I2c_InitStatus = I2C_INITIALIZED;
      #endif
    }
    else
    {
      #if (I2C_DEV_ERROR_DETECT == STD_ON)
      I2c_InitStatus = I2C_UNINITIALIZED;
      #else
      /* Do nothing */
      #endif
    }
  }
}

/*******************************************************************************
**                                                                            **
** Syntax          : void I2c_DeInit(void)                                    **
**                                                                            **
** Service ID      : 0x50                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: de-initialisation command has been accepted.       **
**                   E_NOT_OK: de-initialisation command has not been accepted**
**                                                                            **
** Description     : Driver DeInitialization                                  **
**                    1.This function will deinitialize the I2C module        **
**                                                                            **
*******************************************************************************/
Std_ReturnType I2c_DeInit
(
  void
)
{
  I2c_ChannelInfoType * ChannelInfo;
  Ifx_I2C* HwModulePtr;
  Std_ReturnType Returnvalue;
  uint8 Channel;
  uint8 HwUnit;


  Returnvalue = E_OK;

  #if (I2C_DEV_ERROR_DETECT == STD_ON)
  if (I2c_InitStatus == I2C_UNINITIALIZED)
  {
    /* Report to DET */
    Det_ReportError(I2C_MODULE_ID, I2C_INSTANCE_ID, I2C_SID_DEINIT, \
                    I2C_E_UNINIT);
    Returnvalue = E_NOT_OK;
  }
  if (Returnvalue == E_OK)
  #endif
  {
    #if (I2C_DEV_ERROR_DETECT == STD_ON)
    I2c_InitStatus = I2C_UNINITIALIZED;
    #endif /*(I2C_DEV_ERROR_DETECT == STD_ON)*/
    for(Channel = 0U; Channel < I2C_MAX_CHANNELS; Channel++)
    {
      /*Reset the channel info*/
      ChannelInfo = &I2c_ChannelInfo[Channel];
      ChannelInfo->DataPtr = NULL_PTR;
      ChannelInfo->HwState = I2C_UNINIT;
      ChannelInfo->DataLeft = 0U;
      ChannelInfo->TotalDataTxd = 0U;
      ChannelInfo->I2c_Operation = I2C_NO_OPERATION;
      ChannelInfo->SlaveAddr = 0U;
      ChannelInfo->RxTransferState = I2C_RX_NOT_STARTED;

      HwUnit = I2c_ConfigPtr->I2c_ChannelConfigPtr[Channel].HwUnit;
      HwModulePtr = I2c_HwModuleAddr[HwUnit];

      I2c_lHwClearAllInterrupts(HwModulePtr);
      /* Disable the I2C module clock */
      I2C_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(&HwModulePtr->CLC.U,
                                                       I2C_CLK_DISABLE);
    }
    I2c_ConfigPtr = NULL_PTR;
  }

  return Returnvalue;
}

/*******************************************************************************
**                                                                            **
** Syntax          : I2c_ReturnType I2c_SyncWrite                             **
**                   (                                                        **
**                     const I2c_ChannelType ChannelId,                       **
**                     I2c_DataType *const DataPtr,                           **
**                     I2c_SizeType Size,                                     **
**                     I2c_SlaveAddrType SlaveAddress                         **
**                   )                                                        **
**                                                                            **
** Service ID      : 0x51                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant(for same channel)                          **
**                                                                            **
** Parameters (in) : ChannelId- I2C Channel identifier                        **
**                   DataPtr- Pointer to data that needs to be transmitted    **
**                   Size- Size of data to be transmitted in Bytes            **
**                   SlaveAddress- Address of slave                           **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : I2C_OK: I2C operation Successful                         **
**                   I2C_NOT_OK: I2C operation not Successful.                **
**                   I2C_IS_BUSY: I2C module is busy.                         **
**                                                                            **
** Description     : The service I2c_Write() is called to perform Write       **
**                   operation.                                               **
**                                                                            **
*******************************************************************************/
I2c_ErrorType I2c_SyncWrite
(
  const I2c_ChannelType ChannelId,
  I2c_DataType *const DataPtr,
  const I2c_SizeType Size,
  const I2c_SlaveAddrType SlaveAddress
)
{
  Ifx_I2C* HwModulePtr;
  const I2c_ChannelConfigType *ChannelConfigPtr;
  I2c_ChannelInfoType * ChannelInfo;
  I2c_ErrorType Returnvalue;

  /***********************DET Check starts*************************************/
  #if (I2C_DEV_ERROR_DETECT == STD_ON)
  Returnvalue = I2c_ReadWriteDetCheck(ChannelId, DataPtr, Size, SlaveAddress,
                                                             I2C_SID_SYNCWRITE);
  /***********************DET Check ends***************************************/
  if(Returnvalue == I2C_NO_ERR)
  #endif
  {
    /* Set the channel specific information */
    ChannelInfo = &I2c_ChannelInfo[ChannelId];
    ChannelInfo->HwState = I2C_BUSY;
    ChannelInfo->DataPtr = DataPtr;
    ChannelInfo->DataLeft = Size;
    ChannelInfo->TotalDataTxd = 0u;
    ChannelInfo->I2c_Operation = I2C_WRITE;
    ChannelInfo->SlaveAddr = SlaveAddress;
    ChannelConfigPtr = &I2c_ConfigPtr->I2c_ChannelConfigPtr[ChannelId];
    HwModulePtr = I2c_HwModuleAddr[ChannelConfigPtr->HwUnit];

    /* Enter to RUN state */
    HwModulePtr->RUNCTRL.B.RUN = I2C_ENABLE_INTERFACE;

    /* Send master code if configured for high speed mode */
    if(ChannelConfigPtr->FracDividerHighCfgValue > 0U)
    {
      I2c_lSendMasterCode(HwModulePtr);
    }

    /* Set transmit packet size as per the addressing mode */
    if(ChannelConfigPtr->AddressingMode == I2C_7_BIT_ADDRESSING)
    {
      HwModulePtr->TPSCTRL.U = ((uint32)(ChannelInfo->DataLeft) + \
                                           (uint32)I2C_PACKET_SIZE_7BIT_ADDR);
    }
    else
    {
      HwModulePtr->TPSCTRL.U = ((uint32)(ChannelInfo->DataLeft) + \
                                     (uint32)I2C_PACKET_SIZE_10BIT_ADDR);
    }

    /* Call local function to perform write */
    Returnvalue = I2c_lSyncTransmit(HwModulePtr, ChannelInfo, ChannelId);
  }
    return Returnvalue;
}

/*******************************************************************************
**                                                                            **
** Syntax          : I2c_ReturnType I2c_SyncRead                              **
**                   (                                                        **
**                     const I2c_ChannelType ChannelId,                       **
**                     I2c_DataType *const DataPtr,                           **
**                     I2c_SizeType Size,                                     **
**                     I2c_SlaveAddrType SlaveAddress                         **
**                   )                                                        **
**                                                                            **
** Service ID      : 0x52                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant(for same channel)                          **
**                                                                            **
** Parameters (in) : ChannelId- I2C Channel identifier                        **
**                   Size- Size of data to be recieved in Bytes               **
**                   SlaveAddress- Address of slave                           **
**                                                                            **
** Parameters (out): DataPtr- Pointer to data that is read                    **
**                                                                            **
** Return value    : I2C_OK: I2C operation Successful                         **
**                   I2C_NOT_OK: I2C operation not Successful.                **
**                   I2C_IS_BUSY: I2C module is busy.                         **
**                                                                            **
** Description     : The service I2c_Read() is called to perform Read         **
**                   operation.                                               **
**                                                                            **
*******************************************************************************/

I2c_ErrorType I2c_SyncRead
(
  const I2c_ChannelType ChannelId,
  I2c_DataType *const DataPtr,
  const I2c_SizeType Size,
  const I2c_SlaveAddrType SlaveAddress
)
{
  Ifx_I2C* HwModulePtr;
  I2c_ChannelInfoType * ChannelInfo;
  const I2c_ChannelConfigType *ChannelConfigPtr;
  I2c_ErrorType Returnvalue;

  /***********************DET Check starts*************************************/
  #if (I2C_DEV_ERROR_DETECT == STD_ON)
  Returnvalue = I2c_ReadWriteDetCheck(ChannelId, DataPtr, Size, SlaveAddress,
                                                              I2C_SID_SYNCREAD);
  /***********************DET Check ends***************************************/
  if(Returnvalue == I2C_NO_ERR)
  #endif
  {
    /* Set the channel specific information */
    ChannelInfo = &I2c_ChannelInfo[ChannelId];
    ChannelInfo->HwState = I2C_BUSY;
    ChannelInfo->DataPtr = DataPtr;
    ChannelInfo->DataLeft = Size;
    ChannelInfo->TotalDataTxd = 0;
    ChannelInfo->I2c_Operation = I2C_READ;
    ChannelConfigPtr = &I2c_ConfigPtr->I2c_ChannelConfigPtr[ChannelId];
    ChannelInfo->SlaveAddr = SlaveAddress;
    ChannelInfo->RxTransferState = I2C_RX_INITIATED;
    HwModulePtr = I2c_HwModuleAddr[ChannelConfigPtr->HwUnit];

    /* Enter to RUN state */
    HwModulePtr->RUNCTRL.B.RUN = I2C_ENABLE_INTERFACE;

    /* Send master code if configured for high speed mode */
    if(ChannelConfigPtr->FracDividerHighCfgValue > 0U)
    {
      I2c_lSendMasterCode(HwModulePtr);
    }
    /* Set transmit packet size as per the addressing mode */
    if(ChannelConfigPtr->AddressingMode == I2C_7_BIT_ADDRESSING)
    {
      HwModulePtr->TPSCTRL.U = I2C_PACKET_SIZE_7BIT_ADDR;
    }
    else
    {
      HwModulePtr->TPSCTRL.U = I2C_PACKET_SIZE_10BIT_ADDR;
    }
    /* Call local function to perform read */
    Returnvalue = I2c_lSyncReceive(HwModulePtr, ChannelInfo, ChannelId);
  }
  return Returnvalue;
}

/*******************************************************************************
**                                                                            **
** Syntax          : I2c_ReturnType I2c_AsyncWrite                            **
**                   (                                                        **
**                     const I2c_ChannelType ChannelId,                       **
**                     I2c_DataType *const DataPtr,                           **
**                     I2c_SizeType Size,                                     **
**                     I2c_SlaveAddrType SlaveAddress                         **
**                   )                                                        **
**                                                                            **
** Service ID      : 0x53                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant(for same channel)                          **
**                                                                            **
** Parameters (in) : ChannelId- I2C Channel identifier                        **
**                   DataPtr- Pointer to data that needs to be transmitted    **
**                   Size- Size of data to be transmitted in Bytes            **
**                   SlaveAddress- Address of slave                           **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : I2C_OK: I2C operation Successful                         **
**                   I2C_NOT_OK: I2C operation not Successful.                **
**                   I2C_IS_BUSY: I2C module is busy.                         **
**                                                                            **
** Description     : The service I2c_Write() is called to perform Write       **
**                   operation.                                               **
**                                                                            **
*******************************************************************************/
I2c_ErrorType I2c_AsyncWrite
(
  const I2c_ChannelType ChannelId,
  I2c_DataType *const DataPtr,
  const I2c_SizeType Size,
  const I2c_SlaveAddrType SlaveAddress
)
{
  Ifx_I2C* HwModulePtr;
  const I2c_ChannelConfigType *ChannelConfigPtr;
  I2c_ChannelInfoType * ChannelInfo;
  I2c_ErrorType Returnvalue;

  #if (I2C_DEV_ERROR_DETECT == STD_OFF)
  Returnvalue = I2C_NO_ERR;
  /***********************DET Check starts*************************************/
  #else
  Returnvalue = I2c_ReadWriteDetCheck(ChannelId, DataPtr, Size, SlaveAddress,
                                                            I2C_SID_ASYNCWRITE);
  /***********************DET Check ends***************************************/
  if(Returnvalue == I2C_NO_ERR)
  #endif
  {
    /* Set the channel specific information */
    ChannelInfo = &I2c_ChannelInfo[ChannelId];
    ChannelInfo->HwState = I2C_BUSY;
    ChannelInfo->DataPtr = DataPtr;
    ChannelInfo->DataLeft = Size;
    ChannelInfo->TotalDataTxd = 0u;
    ChannelInfo->I2c_Operation = I2C_WRITE;
    ChannelInfo->SlaveAddr = SlaveAddress;
    ChannelConfigPtr = &I2c_ConfigPtr->I2c_ChannelConfigPtr[ChannelId];
    HwModulePtr = I2c_HwModuleAddr[ChannelConfigPtr->HwUnit];

    /* Enable module interrupts */
    I2c_lHwEnableInterrupt(HwModulePtr);

    /* Enter to RUN state */
    HwModulePtr->RUNCTRL.B.RUN = I2C_ENABLE_INTERFACE;

    /* Send master code if configured for high speed mode */
    if(ChannelConfigPtr->FracDividerHighCfgValue > 0U)
    {
      I2c_lSendMasterCode(HwModulePtr);
    }

    /* Set transmit packet size as per the addressing mode */
    if(ChannelConfigPtr->AddressingMode == I2C_7_BIT_ADDRESSING)
    {
      HwModulePtr->TPSCTRL.U = ((uint32)(ChannelInfo->DataLeft) + \
                                             (uint32)I2C_PACKET_SIZE_7BIT_ADDR);
    }
    else
    {
      HwModulePtr->TPSCTRL.U = ((uint32)(ChannelInfo->DataLeft) + \
                                      (uint32)I2C_PACKET_SIZE_10BIT_ADDR);
    }
  }
    return Returnvalue;
}

/*******************************************************************************
**                                                                            **
** Syntax          : I2c_ReturnType I2c_AsyncRead                             **
**                   (                                                        **
**                     const I2c_ChannelType ChannelId,                       **
**                     I2c_DataType *const DataPtr,                           **
**                     I2c_SizeType Size,                                     **
**                     I2c_SlaveAddrType SlaveAddress                         **
**                   )                                                        **
**                                                                            **
** Service ID      : 0x54                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant(for same channel)                          **
**                                                                            **
** Parameters (in) : ChannelId- I2C Channel identifier                        **
**                   Size- Size of data to be recieved in Bytes               **
**                   SlaveAddress- Address of slave                           **
**                                                                            **
** Parameters (out): DataPtr- Pointer to data that is read                    **
**                                                                            **
** Return value    : I2C_OK: I2C operation Successful                         **
**                   I2C_NOT_OK: I2C operation not Successful.                **
**                   I2C_IS_BUSY: I2C module is busy.                         **
**                                                                            **
** Description     : The service I2c_Read() is called to perform Read         **
**                   operation.                                               **
**                                                                            **
*******************************************************************************/

I2c_ErrorType I2c_AsyncRead
(
  const I2c_ChannelType ChannelId,
  I2c_DataType *const DataPtr,
  const I2c_SizeType Size,
  const I2c_SlaveAddrType SlaveAddress
)
{
  Ifx_I2C* HwModulePtr;
  I2c_ChannelInfoType * ChannelInfo;
  const I2c_ChannelConfigType *ChannelConfigPtr;
  I2c_ErrorType Returnvalue;

  #if (I2C_DEV_ERROR_DETECT == STD_OFF)
  Returnvalue = I2C_NO_ERR;
  /***********************DET Check starts*************************************/
  #else
  Returnvalue = I2c_ReadWriteDetCheck(ChannelId, DataPtr, Size, SlaveAddress,
                                                             I2C_SID_ASYNCREAD);
  /***********************DET Check ends***************************************/
  if(Returnvalue == I2C_NO_ERR)
  #endif
  {
    /* Set the channel specific information */
    ChannelInfo = &I2c_ChannelInfo[ChannelId];
    ChannelInfo->HwState = I2C_BUSY;
    ChannelInfo->DataPtr = DataPtr;
    ChannelInfo->DataLeft = Size;
    ChannelInfo->TotalDataTxd = 0;
    ChannelInfo->I2c_Operation = I2C_READ;
    ChannelConfigPtr = &I2c_ConfigPtr->I2c_ChannelConfigPtr[ChannelId];
    ChannelInfo->SlaveAddr = SlaveAddress;
    ChannelInfo->RxTransferState = I2C_RX_INITIATED;
    HwModulePtr = I2c_HwModuleAddr[ChannelConfigPtr->HwUnit];

    /* Enable module interrupts */
    I2c_lHwEnableInterrupt(HwModulePtr);

    /* Enter to RUN state */
    HwModulePtr->RUNCTRL.B.RUN = I2C_ENABLE_INTERFACE;

    /* Send master code if configured for high speed mode */
    if(ChannelConfigPtr->FracDividerHighCfgValue > 0U)
    {
      I2c_lSendMasterCode(HwModulePtr);
    }

    /* Set transmit packet size as per the addressing mode */
    if(ChannelConfigPtr->AddressingMode == I2C_7_BIT_ADDRESSING)
    {
      HwModulePtr->TPSCTRL.U = I2C_PACKET_SIZE_7BIT_ADDR;
    }
    else
    {
      HwModulePtr->TPSCTRL.U = I2C_PACKET_SIZE_10BIT_ADDR;
    }

  }
  return Returnvalue;
}

/*******************************************************************************
**                                                                            **
** Syntax          : I2c_ChannelStatusType I2c_GetStatus                      **
**                   (                                                        **
**                    I2c_ChannelType ChannelId                               **
**                   )                                                        **
**                                                                            **
** Service ID      : 0x55                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : ChannelId- I2C Channel identifier                        **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : I2C_UNINIT: I2C module is uninitialized.                 **
**                   I2C_IDLE: I2C module is idle.                            **
**                   I2C_BUSY: I2C module is busy.                            **
**                                                                            **
** Description     : This service return the status of the specified I2C      **
**                   module. The service I2c_GetStatus() is called to         **
**                   know if the specified I2C module is IDLE, BUSY or        **
**                   UNINITIALIZED.                                           **
**                                                                            **
*******************************************************************************/
I2c_ChannelStatusType I2c_GetStatus
(
  const I2c_ChannelType ChannelId
)
{
  I2c_ChannelStatusType ReturnStatus;

  #if (I2C_DEV_ERROR_DETECT == STD_ON)

  if (ChannelId >= I2C_MAX_CHANNELS)
  {
    /* Report to DET */
    Det_ReportError(I2C_MODULE_ID, I2C_INSTANCE_ID, \
                    I2C_SID_GETSTATUS, I2C_E_INVALID_CHANNEL);
    ReturnStatus = I2C_UNINIT;
  }
  else
  #endif
  {
   /*MISRA2012_RULE_18_1_JUSTIFICATION: Pointer arithmetic other than
        array indexing used for I2c_ChannelInfo structure. When DET is
        off it is expected that the plausile value of ChannelId is
        provided from upper layer. So the array range will be with in the
        boundary value. */
  ReturnStatus = I2c_ChannelInfo[ChannelId].HwState;
  }

  return ReturnStatus;
}

/*******************************************************************************
**                                                                            **
** Syntax          : I2c_SizeType I2c_CancelOperation                         **
**                   (                                                        **
**                    I2c_ChannelType ChannelId,                              **
**                    I2c_SizeType *const TransmittedDataSize                 **
**                   )                                                        **
**                                                                            **
** Service ID      : 0x56                                                     **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in) : ChannelId- I2C Channel Id                                **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: Operation Successful.                              **
**                   E_NOT_OK: Operation not Successful.                      **
**                                                                            **
** Description     : This service return the total data transmitted thhrough  **
**                   I2c Channel before it is cancelled.                      **
**                                                                            **
*******************************************************************************/
Std_ReturnType I2c_CancelOperation
(
const I2c_ChannelType ChannelId,
I2c_SizeType *const TransmittedDataSize
)
{
  Ifx_I2C* HwModulePtr;
  const I2c_ChannelConfigType *ChannelConfigPtr;
  I2c_ChannelInfoType * ChannelInfo;
  I2c_SizeType RetDataTransmitted;
  Std_ReturnType ReturnValue;
  /***********************DET Check starts*************************************/
  #if (I2C_DEV_ERROR_DETECT == STD_ON)

  if (I2c_InitStatus == I2C_UNINITIALIZED)
  {
  ReturnValue = E_NOT_OK;
    /* Report to DET */
    Det_ReportError(I2C_MODULE_ID, I2C_INSTANCE_ID, \
        I2C_SID_CANCELOPERATION, I2C_E_UNINIT);
  }
  else if (ChannelId >= I2C_MAX_CHANNELS)
  {
  ReturnValue = E_NOT_OK;
    /* Report to DET */
    Det_ReportError(I2C_MODULE_ID, I2C_INSTANCE_ID, \
        I2C_SID_CANCELOPERATION, I2C_E_INVALID_CHANNEL);
  }
  else if (TransmittedDataSize == NULL_PTR)
  {
  ReturnValue = E_NOT_OK;
    /* Report to DET */
    Det_ReportError(I2C_MODULE_ID, I2C_INSTANCE_ID, \
        I2C_SID_CANCELOPERATION, I2C_E_PARAM_POINTER);
  }
  else
  #endif
  /***********************DET Check ends*************************************/
  {
    ChannelConfigPtr = &I2c_ConfigPtr->I2c_ChannelConfigPtr[ChannelId];
    HwModulePtr = I2c_HwModuleAddr[ChannelConfigPtr->HwUnit];
    ChannelInfo = &I2c_ChannelInfo[ChannelId];

    /* Disable the RUNCTRL for further transmission */
    HwModulePtr->RUNCTRL.B.RUN = I2C_DISABLE_INTERFACE;
    I2c_lHwClearAllInterrupts(HwModulePtr);

    /* Return total data txd/rxd before operation was aborted */
    RetDataTransmitted = ChannelInfo->TotalDataTxd;

    /* Reset channel info structure */
    ChannelInfo->HwState = I2C_IDLE;
    ChannelInfo->DataPtr = NULL_PTR;

    /* Reset data counter */
    ChannelInfo->DataLeft = 0U;
    ChannelInfo->TotalDataTxd = 0U;
    ReturnValue = E_OK;
    *TransmittedDataSize = RetDataTransmitted;
  }
  return ReturnValue;
}

/*******************************************************************************
**                            I2c Hw Apis                                     **
*******************************************************************************/
/*******************************************************************************
**                                                                            **
** Syntax          : I2c_lHwInit(const I2c_ConfigType* ConfigPtr)             **
**                                                                            **
** Service ID      : N.A                                                      **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in) : ConfigPtr - Pointer to I2c Driver configuration set      **
**                   HwUnit    - HwUnit to be initialized                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : uint8                                                    **
**                                                                            **
** Description     : This function will initialize the hardware peripheral    **
**                    - All the interrupts are cleared                        **
**                                                                            **
*******************************************************************************/
static uint8 I2c_lHwInit
(
  const uint8 HwUnit,
  const I2c_ConfigType* ConfigPtr
)
{
  Ifx_I2C * HwModulePtr;
  uint8 ClkDisableChk;

  I2c_lResetKernels(I2c_HwModuleAddr[HwUnit]);
  HwModulePtr = I2c_HwModuleAddr[HwUnit];

  I2C_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(&HwModulePtr->CLC.U, (uint32)0U);
  ClkDisableChk = HwModulePtr->CLC.B.DISS;
  if(ClkDisableChk == 0U)
  {
    HwModulePtr->CLC1.U = ConfigPtr->I2c_ChannelConfigPtr[HwUnit].HWClkSetting;
    ClkDisableChk = HwModulePtr->CLC1.B.DISS;
  }
  return ClkDisableChk;
}

/*******************************************************************************
**                                                                            **
** Syntax          : void I2c_lHwClearAllInterrupts(Ifx_I2C* const HwModulePtr)*
**                                                                            **
** Service ID      : N.A                                                      **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in) : HwModulePtr - Pointer to to Hw module                    **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : Fucntion to clear all the interrupts during init         **
**                                                                            **
*******************************************************************************/
static void I2c_lHwClearAllInterrupts
(
  Ifx_I2C* const HwModulePtr
)
{
  /*Disable module interrupt mask control*/
  HwModulePtr->IMSC.U = (uint32)0U;
  /*Disable protocol interrupt mask control*/
  HwModulePtr->PIRQSM.U = (uint32)0U;
  /*Clear protocol interrupt source*/
  HwModulePtr->PIRQSC.U = I2C_PROTOCOL_INTERRUPT_MASK;
  /*Disable error interrupt mask control*/
  HwModulePtr->ERRIRQSM.U = (uint32)0U;
  /*Clear error interrupt source*/
  HwModulePtr->ERRIRQSC.U = I2C_CLEAR_INTERRUPT;

}

/*******************************************************************************
**                                                                            **
** Syntax          : void I2c_lHwUpdateModuleReg                              **
**                        (                                                   **
**                        const uint8 HwUnit                                  **
**                        const I2c_ChannelConfigType *const ChannelConfigPtr **
**                        )                                                   **
**                                                                            **
** Service ID      : N.A                                                      **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : HwUnit- Hw module id                                     **
**                   ChannelConfigPtr- Pointer to Channel Configuration       **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : This function will update the peripheral registers       **
**                   to facilitate packer read/write operation                **
**                                                                            **
*******************************************************************************/
static void I2c_lHwUpdateModuleReg
(
  const uint8 HwUnit,
  const I2c_ChannelConfigType *const ChannelConfigPtr
)
{
  Ifx_I2C* HwModulePtr;

  HwModulePtr = I2c_HwModuleAddr[HwUnit];

  /* Disable I2C Bus interface */
  HwModulePtr->RUNCTRL.B.RUN = I2C_DISABLE_INTERFACE;
  /* Set Fractional Divider Value */
  HwModulePtr->FDIVCFG.U = ChannelConfigPtr->FracDividerCfgValue;
  /* Set Fractional Divider Value for High speed mode */
  HwModulePtr->FDIVHIGHCFG.U = ChannelConfigPtr->FracDividerHighCfgValue;
  /* Set Address Configuration Value */
  HwModulePtr->ADDRCFG.U = ChannelConfigPtr->AdddressCfgValue;
  /* Set Timing Configuration Value */
  HwModulePtr->TIMCFG.U = ChannelConfigPtr->TimingCfgvalue;
  /* Set FIFO Configuration Value */
  HwModulePtr->FIFOCFG.U = ChannelConfigPtr->FIFOCfgValue;
  /* Set PORT Pin Configuration Value */
  I2C_SFR_INIT_DEINIT_WRITE32(&HwModulePtr->GPCTL.U,
                                 ChannelConfigPtr->PortPinCfgvalue);
}

/*******************************************************************************
**                                                                            **
** Syntax          : void I2c_lHwEnableInterrupt(Ifx_I2C* const HwModulePtr)  **
**                                                                            **
** Service ID      : N.A                                                      **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : HwModulePtr - HW unit index(ID)                          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : Fucntion to clear all the interrupts during init         **
**                                                                            **
*******************************************************************************/
static void I2c_lHwEnableInterrupt
(
  Ifx_I2C* const HwModulePtr
)
{
  /* Enable module interrupt mask */
  HwModulePtr->IMSC.U = I2C_ENABLE_INTERRUPT_MASK;
  /* Enable protocol interrupt mask */
  HwModulePtr->PIRQSM.U = I2C_PROTOCOL_INTERRUPT_MASK;
}


/*******************************************************************************
**                                                                            **
** Syntax          : void I2c_lSendMasterCode(I2c_HWUnitType HwUnit)          **
**                                                                            **
** Service ID      : N.A                                                      **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : HwModulePtr - Pointer to to Hw module                    **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :                                                          **
**                                                                            **
** Description     : This function returns the HW peripheral status           **
**                                                                            **
*******************************************************************************/
static void I2c_lSendMasterCode
(
  Ifx_I2C* const HwModulePtr
)
{
  /* Set TPS for Master Code */
  HwModulePtr->TPSCTRL.U = I2C_PACKET_SIZE_7BIT_ADDR;
  /* Send the Master code */
  HwModulePtr->TXD.U = I2C_MASTER_CODE;
  /* Clear the Burst request */
  HwModulePtr->ICR.U = I2C_CLEAR_INTERRUPT;
  /* Clear NACK and TX_END */
  HwModulePtr->PIRQSC.U = I2C_PROTOCOL_INTERRUPT_MASK;
}
/*******************************************************************************
**                                                                            **
** Syntax          : static void I2c_lResetKernels(Ifx_I2C *const HwModulePtr)**
**                                                                            **
** Service ID      : N.A                                                      **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in) : HwModulePtr - Pointer to to Hw module                    **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description     : This function resets SFR to default values by resetting  **
**                   kernel registers                                         **
**                                                                            **
*******************************************************************************/
static void I2c_lResetKernels
(
  Ifx_I2C * const HwModulePtr
)
{
  uint32 RstStatus;
  uint32 WaitCount;

  I2C_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(&HwModulePtr->KRST0.U, 1U);
  I2C_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG\
                                     (&HwModulePtr->KRST1.U, I2C_KRST1_SFR_MSK);
  /* Wait for Timeout*/
  WaitCount = (uint32)I2C_KERNEL_RESET_WAIT_COUNTS;
  do
  {
    WaitCount--;
    /* MISRA2012_RULE_11_8_JUSTIFICATION: SFR access.No side effects foreseen
       by violating this MISRA rule */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: I2C base address access */
    RstStatus = (((uint32)(I2C_SFR_INIT_DEINIT_READ32(&HwModulePtr->KRST0.U))) & \
              ((uint32)IFX_I2C_KRST0_RSTSTAT_MSK << IFX_I2C_KRST0_RSTSTAT_OFF));
    RstStatus = ((uint32)RstStatus >> IFX_I2C_KRST0_RSTSTAT_OFF);
  } while((RstStatus == 0U) && (WaitCount > 0U));

  I2C_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG\
                                 (&HwModulePtr->KRSTCLR.U, I2C_KRSTCLR_SFR_MSK);

}

/*******************************************************************************
**                            I2c local functions                             **
*******************************************************************************/
#if (I2C_DEV_ERROR_DETECT == STD_ON)
/*******************************************************************************
**                                                                            **
** Syntax          : void  I2c_ReadWriteDetCheck                              **
**                  (                                                         **
**                   const I2c_ChannelType ChannelId,                         **
**                   const I2c_DataType *const DataPtr,                       **
**                   const I2c_SizeType Size,                                 **
**                   const I2c_SlaveAddrType SlaveAddress,                    **
**                   const uint8 ServiceId                                    **
**                  )                                                         **
**                                                                            **
** Service ID      : N.A                                                      **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : ChannelId- Channel Id                                    **
**                   DataPtr- Pointer to data to be transmitted/recieved      **
**                   Size- Size of the data                                   **
**                   SlaveAddress- Slave address                              **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : This function is check validity of input parameters      **
**                                                                            **
*******************************************************************************/
static I2c_ErrorType I2c_ReadWriteDetCheck
(
 const I2c_ChannelType ChannelId,
 const I2c_DataType *const DataPtr,
 const I2c_SizeType Size,
 const I2c_SlaveAddrType SlaveAddress,
 const uint8 ServiceId
)
{
  I2c_ErrorType Returnvalue;

  if (I2c_InitStatus == I2C_UNINITIALIZED)
    {

      /* Report to DET */
      Det_ReportError(I2C_MODULE_ID, I2C_INSTANCE_ID,
                                                 ServiceId, I2C_E_UNINIT);

      Returnvalue = I2C_IS_UNINIT;
    }
    else if (ChannelId >= I2C_MAX_CHANNELS)
    {
      /* Report to DET */
      Det_ReportError(I2C_MODULE_ID, I2C_INSTANCE_ID,
                                         ServiceId, I2C_E_INVALID_CHANNEL);

      Returnvalue = I2C_INVALID_CHANNEL;
    }
    else if(DataPtr == NULL_PTR)
    {
      /* Report to DET */
      Det_ReportError(I2C_MODULE_ID, I2C_INSTANCE_ID,
                                                 ServiceId, I2C_E_PARAM_POINTER);
      Returnvalue = I2C_NULL_PTR;
    }
    else if((Size == 0U) || (Size > I2C_MAX_SUPPORTED_SIZE))
    {
      /* Report to DET */
      Det_ReportError(I2C_MODULE_ID, I2C_INSTANCE_ID,
                                                  ServiceId, I2C_E_INVALID_SIZE);
      Returnvalue = I2C_INVALID_SIZE;
    }
    else if((I2c_ConfigPtr->I2c_ChannelConfigPtr[ChannelId].AddressingMode ==
               I2C_7_BIT_ADDRESSING) && (SlaveAddress > I2C_7_BIT_MAX_SLAVE_ADD))
    {
        /* Report to DET */
        Det_ReportError(I2C_MODULE_ID, I2C_INSTANCE_ID,
                                         ServiceId, I2C_E_INVALID_SLAVE_ADDRESS);
        Returnvalue = I2C_INVALID_ADDRESS;
    }
    else if((I2c_ConfigPtr->I2c_ChannelConfigPtr[ChannelId].AddressingMode ==
              I2C_10_BIT_ADDRESSING) && (SlaveAddress > I2C_10_BIT_MAX_SLAVE_ADD))
    {
        /* Report to DET */
        Det_ReportError(I2C_MODULE_ID, I2C_INSTANCE_ID,
                                           ServiceId, I2C_E_INVALID_SLAVE_ADDRESS);
        Returnvalue = I2C_INVALID_ADDRESS;
    }
    else if(I2c_ChannelInfo[ChannelId].HwState == I2C_BUSY)
    {
      Det_ReportError(I2C_MODULE_ID, I2C_INSTANCE_ID,
                                              ServiceId, I2C_E_HW_UNIT_BUSY);

      Returnvalue = I2C_IS_BUSY;

    }
    else
    {
        Returnvalue = I2C_NO_ERR;
    }
  return Returnvalue;
}
#endif

/*******************************************************************************
**                                                                            **
** Syntax          : void  I2c_lWrite                                         **
**                  (                                                         **
**                   Ifx_I2C* const HwModulePtr,                              **
**                   I2c_ChannelInfoType* const ChannelInfo                   **
**                  )                                                         **
**                                                                            **
** Service ID      : N.A                                                      **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : HwModulePtr- Pointer to Hw module Register               **
**                   ChannelInfo- Pointer to Channelinfo structure            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : This function is called to transmit the data on the bus  **
**                                                                            **
*******************************************************************************/
static void  I2c_lWrite
(
  Ifx_I2C* const HwModulePtr,
  I2c_ChannelInfoType* const ChannelInfo
)
{
  const I2c_DataType* DataPointer;
  uint32 TxData;
  uint32 TempTxData;
  uint16 DataLeft;
  uint16 TxdCnt;
  uint16 SlaveAddr;
  uint8 UpperSlaveAddr;
  uint8 Counter;
  uint8 FilledFIFOStage;
  uint8 FIFOCounter;

  DataLeft = ChannelInfo->DataLeft;
  TxdCnt = ChannelInfo->TotalDataTxd;
  /* calculate the file FIFO stage */
  /* the following calculation is for first transmission */
  if(TxdCnt == 0U)
  {
    /* if data left is more than FIFO size, set filled FIFO stage to 8 */
    if(DataLeft >= I2C_FIFO_BYTES_FULL)
    {
      FilledFIFOStage = I2C_FIFO_STAGES_FULL;
    }
    else
    {
      /* if data left is less than FIFO size, set FilledFIFOStage to next stage */
      FilledFIFOStage = (uint8)(DataLeft / I2C_FIFO_MAX_DATA_IN_EACH_STAGE);
      if((ChannelInfo->DataLeft & 3u) > 0U)
      {
         FilledFIFOStage++;
      }
    }
  }
  /* the following calcutaion is for consecutive transmissions */
  else
  {
    if((HwModulePtr->RIS.U & I2C_BURST_REQ_CHK) != 0U)
    {
      /* if data left is more than half FIFO size, set filled FIFO stage to 4 */
      if(DataLeft >= I2C_FIFO_BYTES_HALF_FULL)
      {
         FilledFIFOStage = I2C_FIFO_STAGES_HALF_FULL;
      }
      else
      {
         /* if data left is less than FIFO size, set the stage to next aligned stage */
         FilledFIFOStage =(uint8)(DataLeft / I2C_FIFO_MAX_DATA_IN_EACH_STAGE);

         if((ChannelInfo->DataLeft & 3u) != 0U)
         {
           FilledFIFOStage++;
         }
      }
    }
    else
    {
      FilledFIFOStage = I2C_FIFO_SINGLE_STAGE_FULL;
    }
  }

  /* Set FIFO counter and Data counter */
  FIFOCounter = 0U;
  DataPointer = ChannelInfo->DataPtr;
  /* Loop till FIFO is empty */
  while(FIFOCounter < FilledFIFOStage)
  {
    TxData = 0U;
    if((FIFOCounter == 0U) && (TxdCnt == 0U))
    {
       if(I2c_ConfigPtr->I2c_ChannelConfigPtr->AddressingMode ==
                                                            I2C_7_BIT_ADDRESSING)
       {
         SlaveAddr = (ChannelInfo->SlaveAddr << I2C_SHIFT_ONE_BIT) | \
                                           I2C_WRITE_OPERATION;
         TxData = (uint8)SlaveAddr;
         Counter = 1;
       }
       else
       {
         /* Calculate Upper address byte */
         SlaveAddr = ChannelInfo->SlaveAddr;
         UpperSlaveAddr = ((I2C_10_BIT_ADDRESS_PREAMBLE) |
              ((uint8)(SlaveAddr >> I2C_SHIFT_EIGHT_BIT) << I2C_SHIFT_ONE_BIT) |
                                                              I2C_WRITE_OPERATION);

         /* MISRA2012_RULE_10_8_JUSTIFICATION: Cast is being performed to assign
          *it to variable, which will eventually read it into HW register. So
          *interfacing with the HW is needed. Also, the final value being assigned
          *is found to be appropriately working. So, no side effects foreseen by
          *violating this MISRA rule. */
         /* Address frame containing 2 bytes */
         TxData = (((uint32)(SlaveAddr & I2C_EIGHT_BIT_MASK) <<
                                I2C_SHIFT_EIGHT_BIT) | (uint32)UpperSlaveAddr);
         Counter = 2;
       }
    }
    else
    {
      Counter = 0U;
    }

    while((Counter < I2C_FIFO_MAX_DATA_IN_EACH_STAGE) && (DataLeft > 0U))
    {
       TempTxData = DataPointer[TxdCnt];
       TxData |= ( TempTxData << (Counter * I2C_SHIFT_EIGHT_BIT));
       TxdCnt++;
       DataLeft--;
       Counter++;
    }

     FIFOCounter++;
     HwModulePtr->TXD.U =  TxData;
  }

  ChannelInfo->DataLeft = DataLeft;
  ChannelInfo->TotalDataTxd = TxdCnt;
}
/*******************************************************************************
**                                                                            **
** Syntax          : void  I2c_lSyncTransmit                                  **
**                  (                                                         **
**                   Ifx_I2C* const HwModulePtr,                              **
**                   I2c_ChannelInfoType* const ChannelInfo,                  **
**                   const I2c_ChannelConfigType *const ChannelConfigPtr      **
**                  )                                                         **
**                                                                            **
** Service ID      : N.A                                                      **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : HwModulePtr- Pointer to Hw module Register               **
**                   ChannelInfo- Pointer to Channelinfo structure            **
**                   ChannelConfigPtr- Pointer to ChannelConfig Structure     **
**                   ChannelId- Timeout counter value                         **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : This function is called to transmit synchronously        **
**                                                                            **
*******************************************************************************/
static I2c_ErrorType I2c_lSyncTransmit
(
  Ifx_I2C* const HwModulePtr,
  I2c_ChannelInfoType * const ChannelInfo,
  const I2c_ChannelType ChannelId
)
{
  I2c_ErrorType ErrorId;
  I2c_TxTransferStateType TransmitPending;
  uint32 ERRIRQSS_Val;
  uint32 PIRQSS_Val;
  uint32 TimeOutValue;

  TimeOutValue = I2c_ConfigPtr->I2c_ChannelConfigPtr[ChannelId].TxTimeOutCount;
  TransmitPending = I2C_TX_IN_PROGRESS;
  ErrorId = I2C_NO_ERR;

  while((TransmitPending == I2C_TX_IN_PROGRESS) && (TimeOutValue > 0U))
  {
    /* Check for any transmission error */
    ERRIRQSS_Val = HwModulePtr->ERRIRQSS.U & I2C_ERROR_INTERRUPT_MASK;
    PIRQSS_Val = HwModulePtr->PIRQSS.U & I2C_PROTOCOL_INTERRUPT_MASK;
    /* If any Burst inettrupt is pending continue transmission */
    if((HwModulePtr->RIS.U & I2C_RAW_INTERRUPT_MASK) != 0U)
    {
      I2c_lWrite(HwModulePtr,ChannelInfo);
      HwModulePtr->ICR.U = I2C_CLEAR_INTERRUPT;
    }
    /* Get the error id if any error has occured */
    else if((ERRIRQSS_Val != 0U) || (PIRQSS_Val != 0U))
    {
        ChannelInfo->HwState = I2C_IDLE;

        if(HwModulePtr->ERRIRQSS.B.TXF_UFL == I2C_FLAG_SET)
        {
          ErrorId = I2C_TX_UNDERFLOW;
        }
        else if(HwModulePtr->ERRIRQSS.B.TXF_OFL == I2C_FLAG_SET)
        {
          ErrorId = I2C_TX_OVERFLOW;
        }
        else if(HwModulePtr->PIRQSS.B.NACK == I2C_FLAG_SET)
        {
          ErrorId = I2C_NO_ACK;
        }
        else if(HwModulePtr->PIRQSS.B.AL == I2C_FLAG_SET)
        {
          ErrorId = I2C_ARBITRATION_LOST;
        }
        else if(HwModulePtr->PIRQSS.B.TX_END == I2C_FLAG_SET)
        {
          ErrorId = I2C_NO_ERR;
        }
        else
        {
          ErrorId = I2C_ERR_OTHER;
        }

        TransmitPending = I2C_TX_COMPLETED;
        I2c_lHwClearAllInterrupts(HwModulePtr);
    }
    else
    {
      /* Do nothing */
    }
  TimeOutValue--;
  }
  HwModulePtr->RUNCTRL.B.RUN = I2C_DISABLE_INTERFACE;
  return ErrorId;
}

/*******************************************************************************
**                                                                            **
** Syntax          : void  I2c_lRead                                          **
**                  (                                                         **
**                   Ifx_I2C* const HwModulePtr,                              **
**                   I2c_ChannelInfoType* const ChannelInfo                   **
**                  )                                                         **
**                                                                            **
** Service ID      : N.A                                                      **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : HwModulePtr- Pointer to Hw module Register               **
**                   ChannelInfo- Pointer to Channelinfo structure            **
**                   ChannelConfigPtr- Pointer to ChannelConfig Structure     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : This function is called to Receive the data on the bus   **
**                                                                            **
*******************************************************************************/
static void I2c_lRead
(
  Ifx_I2C* const HwModulePtr,
  I2c_ChannelInfoType* const ChannelInfo
)
{
  I2c_DataType* DataPointer;
  uint32 RxData;
  uint32 TxData;
  uint16 SlaveAddr;
  uint16 DataLeft;
  uint16 RxdCnt;
  uint8 UpperSlaveAddr;
  uint8 LoopCount;
  uint8 Counter;
  uint8 FilledFIFOStage;


  DataLeft = ChannelInfo->DataLeft;
  RxdCnt = ChannelInfo->TotalDataTxd;

  if(ChannelInfo->RxTransferState == I2C_RX_INITIATED)
  {
    ChannelInfo->RxTransferState  = I2C_RX_COMMAND_SENT;
    /*  Send read command */
    SlaveAddr = ChannelInfo->SlaveAddr;
    if(I2c_ConfigPtr->I2c_ChannelConfigPtr->AddressingMode ==
                                                           I2C_7_BIT_ADDRESSING)
    {
      TxData = (((uint32)SlaveAddr << (uint32)I2C_SHIFT_ONE_BIT) | \
                         (uint32)I2C_READ_OPERATION);
      HwModulePtr->TXD.U = TxData;
    }
    else
    {
      /* Calculate the upper slave byte */
        UpperSlaveAddr = ((I2C_10_BIT_ADDRESS_PREAMBLE) |
            ((uint8)(SlaveAddr >> I2C_SHIFT_EIGHT_BIT) << I2C_SHIFT_ONE_BIT) |
                                                            I2C_WRITE_OPERATION);

         /* MISRA2012_RULE_10_8_JUSTIFICATION: Cast is being performed to assign
          *it to variable, which will eventually read it into HW register. So
          *interfacing with the HW is needed. Also, the final value being assigned
          *is found to be appropriately working. So, no side effects foreseen by
          *violating this MISRA rule. */
        /* Address frame containing 2 bytes of 10 bit address */
        TxData = (((uint32)(SlaveAddr & I2C_EIGHT_BIT_MASK) <<
                                I2C_SHIFT_EIGHT_BIT) | (uint32)UpperSlaveAddr);
        HwModulePtr->TXD.U = TxData;
        /* Set the repeated start condition */
        HwModulePtr->ENDDCTRL.B.SETRSC = 1U;
        /* Send the 10 bit preamble with Read command */
        HwModulePtr->TPSCTRL.U = 1U;
        HwModulePtr->TXD.U = ((uint32)UpperSlaveAddr | (uint32)I2C_READ_OPERATION);
    }
    HwModulePtr->MRPSCTRL.U = ChannelInfo->DataLeft;
  }
  else
  {
    ChannelInfo->RxTransferState = I2C_RX_IN_PROGRESS;
    FilledFIFOStage = HwModulePtr->FFSSTAT.B.FFS;
    DataPointer = ChannelInfo->DataPtr;

    /* Receive Data from FIFO */
    for (LoopCount = 0U; LoopCount < FilledFIFOStage; LoopCount++)
    {
      RxData = HwModulePtr->RXD.U;
      /* Fill application buffer */
      for(
          Counter = 0U;
          (Counter < I2C_FIFO_MAX_DATA_IN_EACH_STAGE) && (DataLeft > 0u);
          Counter++)
      {
        DataPointer[RxdCnt] =(uint8)(RxData >>(Counter * I2C_SHIFT_EIGHT_BIT));
        RxdCnt++;
        DataLeft--;
      }



      ChannelInfo->DataLeft = DataLeft;
      ChannelInfo->TotalDataTxd = RxdCnt;
    }
  }
}

/*******************************************************************************
**                                                                            **
** Syntax          : static void  I2c_lSyncReceive                            **
**                  (                                                         **
**                   Ifx_I2C* const HwModulePtr,                              **
**                   I2c_ChannelInfoType* const ChannelInfo,                  **
**                   const I2c_ChannelConfigType *const ChannelConfigPtr      **
**                  )                                                         **
**                                                                            **
** Service ID      : N.A                                                      **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : HwModulePtr- Pointer to Hw module Register               **
**                   ChannelInfo- Pointer to Channelinfo structure            **
**                   ChannelConfigPtr- Pointer to ChannelConfig Structure     **
**                   ChannelId- Timeout counter value                         **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : This function is called to Receive synchronously         **
**                                                                            **
*******************************************************************************/
static I2c_ErrorType I2c_lSyncReceive
(
  Ifx_I2C* const HwModulePtr,
  I2c_ChannelInfoType * const ChannelInfo,
  const I2c_ChannelType ChannelId
)
{
  I2c_ErrorType ErrorId;
  I2c_RxTransferStateType ReceivePending;
  uint32 ERRIRQSS_Val;
  uint32 PIRQSS_Val;
  uint32 TimeOutValue;

  TimeOutValue = I2c_ConfigPtr->I2c_ChannelConfigPtr[ChannelId].RxTimeOutCount;
  ReceivePending = I2C_RX_IN_PROGRESS;
  ErrorId = I2C_NO_ERR;

  while((ReceivePending == I2C_RX_IN_PROGRESS) && (TimeOutValue > 0U))
  {
    /* Get the error values if any */
    ERRIRQSS_Val = HwModulePtr->ERRIRQSS.U & I2C_ERROR_INTERRUPT_MASK;
    PIRQSS_Val = HwModulePtr->PIRQSS.U & I2C_PROTOCOL_INTERRUPT_MASK;
    if((ERRIRQSS_Val != 0U) || (PIRQSS_Val != 0U))
    {

      if(HwModulePtr->ERRIRQSS.B.RXF_UFL == I2C_FLAG_SET)
      {
         ErrorId = I2C_RX_UNDERFLOW;
      }
      else if(HwModulePtr->ERRIRQSS.B.RXF_OFL == I2C_FLAG_SET)
      {
        ErrorId = I2C_RX_OVERFLOW;
      }
      else if(HwModulePtr->PIRQSS.B.NACK == I2C_FLAG_SET)
      {
        ErrorId = I2C_NO_ACK;
      }
      else if(HwModulePtr->PIRQSS.B.AL == I2C_FLAG_SET)
      {
        ErrorId = I2C_ARBITRATION_LOST;
      }
      else if(HwModulePtr->PIRQSS.B.TX_END == I2C_FLAG_SET)
      {
        ErrorId = I2C_NO_ERR;
      }
      else
      {
      ErrorId = I2C_ERR_OTHER;
      }
      I2c_lHwClearAllInterrupts(HwModulePtr);
      if((ChannelInfo->RxTransferState == I2C_RX_COMMAND_SENT) && \
           (ErrorId != I2C_NO_ERR))
      {
         ChannelInfo->RxTransferState = I2C_RX_IN_PROGRESS;
      }
      else
      {
        ReceivePending = I2C_RX_COMPLETED;
        ChannelInfo->HwState = I2C_IDLE;
      }
    }
    /* If any burst interrupt is pending, continue recieving */
    else if((HwModulePtr->RIS.U & I2C_RAW_INTERRUPT_MASK) != 0U)
    {
      I2c_lRead(HwModulePtr,ChannelInfo);
      HwModulePtr->ICR.U = I2C_CLEAR_INTERRUPT;
    }
    else
    {
      /* Do nothing */
    }
    TimeOutValue--;
  }
  HwModulePtr->RUNCTRL.B.RUN = I2C_DISABLE_INTERFACE;
  return ErrorId;
}

/*******************************************************************************
**                                 I2c ISRs                                   **
*******************************************************************************/

/*******************************************************************************
**                                                                            **
** Syntax          : void I2c_IsrI2cDtr(const uint8 HwUnit)                   **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Reentrant(for different channel)                         **
**                                                                            **
** Parameters (in) : HwUnit - HW unit index(ID)                               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : ISR fucntion to take care of Data interrupts             **
**                                                                            **
*******************************************************************************/
void I2c_IsrI2cDtr
(
  const uint8 HwUnit
)
{
  Ifx_I2C * HwModulePtr;
  I2c_ChannelInfoType* ChannelInfo;
  uint8 ChannelId;
  HwModulePtr = I2c_HwModuleAddr[HwUnit];
  ChannelId = I2c_ChannelMap[HwUnit];
  ChannelInfo = &I2c_ChannelInfo[ChannelId];

  if(ChannelInfo->I2c_Operation == I2C_WRITE)
  {
    if(ChannelInfo->DataLeft > 0U)
    {
       I2c_lWrite(HwModulePtr, ChannelInfo);
    }
    HwModulePtr->ICR.U = I2C_CLEAR_INTERRUPT;
  }
  else
  {
    I2c_lRead(HwModulePtr, ChannelInfo);
    HwModulePtr->ICR.U = I2C_CLEAR_INTERRUPT;
  }

}

/*******************************************************************************
**                                                                            **
** Syntax          : void I2c_IsrI2cProtocol(const uint8 HwUnit)              **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Reentrant(for different channel)                         **
**                                                                            **
** Parameters (in) : HwUnit - HW unit index(ID)                               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : ISR fucntion to take care of Protocol interrupts         **
**                                                                            **
*******************************************************************************/
void I2c_IsrI2cProtocol
(
  const uint8 HwUnit
)
{
  const I2c_ChannelConfigType* ChannelConfigPtr;
  I2c_ChannelInfoType* ChannelInfo;
  Ifx_I2C * HwModulePtr;
  I2c_ErrorType ErrorId;
  uint8 ChannelId;

  ChannelId = I2c_ChannelMap[HwUnit];
  HwModulePtr = I2c_HwModuleAddr[HwUnit];
  ChannelInfo = &I2c_ChannelInfo[ChannelId];
  ChannelConfigPtr = &I2c_ConfigPtr->I2c_ChannelConfigPtr[ChannelId];

  if((HwModulePtr->PIRQSS.U & I2C_PROTOCOL_INTERRUPT_MASK) != 0U)
  {
    if(ChannelInfo->RxTransferState != I2C_RX_COMMAND_SENT)
    {
      if(HwModulePtr->PIRQSS.B.NACK == I2C_FLAG_SET)
      {
        ErrorId = I2C_NO_ACK;
      }
      else if(HwModulePtr->PIRQSS.B.AL == I2C_FLAG_SET)
      {
        ErrorId = I2C_ARBITRATION_LOST;
      }
      else if(HwModulePtr->PIRQSS.B.TX_END == I2C_FLAG_SET)
      {
        ErrorId = I2C_NO_ERR;
      }
      else
      {
        ErrorId = I2C_ERR_OTHER;
      }
      /* Set channel state idle */
      ChannelInfo->HwState = I2C_IDLE;
      HwModulePtr->PIRQSC.U = I2C_PROTOCOL_INTERRUPT_MASK;
      HwModulePtr->ERRIRQSC.U = I2C_CLEAR_INTERRUPT;

      /* Set the RUN state to 0 */
      HwModulePtr->RUNCTRL.B.RUN = I2C_DISABLE_INTERFACE;

      /* Check notification configured */
      if(ChannelConfigPtr->I2c_Notif.I2c_NotifFunctionPtr != NULL_PTR)
      {
        /* Call configured notification function */
        ChannelConfigPtr->I2c_Notif.I2c_NotifFunctionPtr(ErrorId);
      }
    }
    else
    {
      HwModulePtr->PIRQSC.U = I2C_PROTOCOL_INTERRUPT_MASK;
    }
  }
}

/*******************************************************************************
**                                                                            **
** Syntax          : void I2c_IsrI2cError(const uint8 HwUnit)                 **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Reentrant(for different channel)                         **
**                                                                            **
** Parameters (in) : HwUnit - HW unit index(ID)                               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : ISR fucntion to take care of Error interrupts            **
**                                                                            **
*******************************************************************************/
void I2c_IsrI2cError
(
  const uint8 HwUnit
)
{
  const I2c_ChannelConfigType* ChannelConfigPtr;
  I2c_ChannelInfoType* ChannelInfo;
  Ifx_I2C * HwModulePtr;
  I2c_ErrorType ErrorId;
  uint8 ChannelId;

  ChannelId = I2c_ChannelMap[HwUnit];
  HwModulePtr = I2c_HwModuleAddr[HwUnit];
  ChannelInfo = &I2c_ChannelInfo[ChannelId];
  ChannelConfigPtr = &I2c_ConfigPtr->I2c_ChannelConfigPtr[ChannelId];

  if((HwModulePtr->ERRIRQSS.U & I2C_ERROR_INTERRUPT_MASK) != 0U)
  {
    ChannelInfo->HwState = I2C_IDLE;

    if(HwModulePtr->ERRIRQSS.B.TXF_UFL == I2C_FLAG_SET)
    {
       ErrorId = I2C_TX_UNDERFLOW;
    }
    else if(HwModulePtr->ERRIRQSS.B.TXF_OFL == I2C_FLAG_SET)
    {
      ErrorId = I2C_TX_OVERFLOW;
    }
    else if(HwModulePtr->ERRIRQSS.B.RXF_UFL == I2C_FLAG_SET)
    {
       ErrorId = I2C_RX_UNDERFLOW;
    }
    else if(HwModulePtr->ERRIRQSS.B.RXF_OFL == I2C_FLAG_SET)
    {
      ErrorId = I2C_RX_OVERFLOW;
    }
    else
    {
      ErrorId = I2C_ERR_OTHER;
    }

    HwModulePtr->PIRQSC.U = I2C_PROTOCOL_INTERRUPT_MASK;
    HwModulePtr->ERRIRQSC.U = I2C_CLEAR_INTERRUPT;

    /* Set the RUN state to 0 */
     HwModulePtr->RUNCTRL.B.RUN = I2C_DISABLE_INTERFACE;

    /* Check notification configured */
    if(ChannelConfigPtr->I2c_Notif.I2c_NotifFunctionPtr != NULL_PTR)
    {
      /* Call configured notification function */
      ChannelConfigPtr->I2c_Notif.I2c_NotifFunctionPtr(ErrorId);
    }
  }

}

#if (I2C_VERSION_INFO_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Syntax           : void I2c_GetVersionInfo                                 **
**                    (                                                       **
**                      Std_VersionInfoType * const VersionInfoPtr            **
**                    )                                                       **
**                                                                            **
** Description      : This API returns the version information of this module.**
**                    Note: This API is available only when I2cVersionInfoApi **
**                    is configured as true.                                  **
**                                                                            **
** Service ID       : 0x55                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : VersionInfoPtr -  Pointer to where to store the version **
**                    information of this module                              **
**                                                                            **
** Return value     : void                                                    **
**                                                                            **
*******************************************************************************/
void I2c_GetVersionInfo(Std_VersionInfoType * const VersionInfoPtr)
{
  #if(I2C_DEV_ERROR_DETECT == STD_ON)
  if ((VersionInfoPtr) == NULL_PTR)
  {
    /* Report to DET */
    Det_ReportError(
      I2C_MODULE_ID,
      I2C_INSTANCE_ID,
      I2C_SID_GETVERSIONINFO,
      I2C_E_PARAM_POINTER
    );
  }
  else
  #endif
  {
    /* Note that versioninfo pointer is not checked for NULL as the user
       is supposed to send the memory allocated pointer */
    /* I2C Module ID */
    ((Std_VersionInfoType*)(VersionInfoPtr))->moduleID = I2C_MODULE_ID;
    /* I2C vendor ID */
    ((Std_VersionInfoType*)(VersionInfoPtr))->vendorID = I2C_VENDOR_ID;
    /* major version of I2C */
    ((Std_VersionInfoType*)(VersionInfoPtr))->sw_major_version =
      (uint8)I2C_SW_MAJOR_VERSION;
    /* minor version of I2C */
    ((Std_VersionInfoType*)(VersionInfoPtr))->sw_minor_version =
      (uint8)I2C_SW_MINOR_VERSION;
    /* patch version of I2C */
    ((Std_VersionInfoType*)(VersionInfoPtr))->sw_patch_version =
      (uint8)I2C_SW_PATCH_VERSION;
  }
}
#endif

#define I2C_STOP_SEC_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "I2c_MemMap.h"

/*******************************************************************************
**                            General Notes                                   **
*******************************************************************************/
