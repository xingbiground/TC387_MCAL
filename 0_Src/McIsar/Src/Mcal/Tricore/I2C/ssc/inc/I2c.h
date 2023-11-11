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
**  FILENAME     : I2c.h                                                      **
**                                                                            **
**  VERSION      : 1.40.0_7.0.0                                               **
**                                                                            **
**  DATE         : 2020-04-17                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : I2c Driver header definition file                          **
**                                                                            **
**  SPECIFICATION(S) : Specification of I2c Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                                                                            **
**  TRACEABILITY : [cover parentID=] [/cover]                                 **
**                                                                            **
*******************************************************************************/

#ifndef I2C_H
#define I2C_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/* Inclusion of Platform_Types.h and Compiler.h  */
#include "Std_Types.h"
#include "McalLib.h"
#include "IfxI2c_bf.h"

/* Pre-compile/static configuration parameters for I2C  */
#include "I2c_Cfg.h"

/* Conditional Inclusion of Developement Error Tracer File */
#if (I2C_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif /* (I2C_DEV_ERROR_DETECT == STD_ON) */

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
#define I2C_INSTANCE_ID            (0U)

#define I2C_VENDOR_ID              (17U)
#define I2C_MODULE_ID              (255U)

#define I2C_MCAL_SUPERVISOR        (0)
#define I2C_MCAL_USER1             (1)

#if (I2C_DEV_ERROR_DETECT == STD_ON)
/* Development errors */

/*API Service called with NULL parameter.*/
#define I2C_E_PARAM_POINTER          ((uint8)0x00)
/*API Service used without initialization */
#define I2C_E_UNINIT                 ((uint8)0x01)
/*Synchronous transmission service called at invalid channel.*/
#define I2C_E_INVALID_CHANNEL        ((uint8)0x02)
/* I2C driver is already initialized */
#define I2C_E_ALREADY_INITIALIZED    ((uint8)0x03)
/* I2C peirpheral is busy */
#define I2C_E_HW_UNIT_BUSY           ((uint8)0x04)
/* I2C invalid slave address */
#define I2C_E_INVALID_SLAVE_ADDRESS  ((uint8)0x05)
/* I2C invalid size */
#define I2C_E_INVALID_SIZE           ((uint8)0x06)
/* I2C NULL Config Pointer Check */
#define I2C_E_INIT_FAILED            ((uint8)0x07)
/* End of Development errors */

/* API Service ID's */

/* API Service ID for I2c_Init */
#define I2C_SID_INIT                      ((uint8)0x4F)
/* API Service ID for I2c_DeInit */
#define I2C_SID_DEINIT                    ((uint8)0x50)
/* API Service ID for I2c_SyncWrite */
#define I2C_SID_SYNCWRITE                 ((uint8)0x51)
/* API Service ID for I2c_SyncRead */
#define I2C_SID_SYNCREAD                  ((uint8)0x52)
/* API Service ID for I2c_AsyncWrite */
#define I2C_SID_ASYNCWRITE                ((uint8)0x53)
/* API Service ID for I2c_AsyncRead */
#define I2C_SID_ASYNCREAD                 ((uint8)0x54)
/* API Service ID for I2c_GetStatus */
#define I2C_SID_GETSTATUS                 ((uint8)0x55)
/* API Service ID for I2c_CancelOperation */
#define I2C_SID_CANCELOPERATION           ((uint8)0x56)
/* API Service ID for I2c_GetVersionInfo */
#define I2C_SID_GETVERSIONINFO            ((uint8)0x57)

/* End of API Service ID's */

#endif /* (I2C_DEV_ERROR_DETECT == STD_ON) */

/* Macros to define the SFR mask values */
#define I2C_KRST1_SFR_MSK         (0x00000001U)
#define I2C_KRSTCLR_SFR_MSK       (0x00000001U)
#define I2C_IMSC_SFR_MSK          (0x0000001FU)
#define I2C_PIRQSM_SFR_MSK        (0x0000005FU)
#define I2C_SRC_SRCR_MSK          (0x7F3F18FFU)
#define I2C_CLC_SFR_MSK           (0x00000002U)


/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
typedef uint8 I2c_ChannelType;

typedef uint16 I2c_SizeType;

typedef uint8 I2c_DataType;

typedef uint16 I2c_SlaveAddrType;

/*
Type : I2c_ChannelStatusType
This type defines a range of specific status for I2C Driver.
It informs about the I2C Driver status and can be obtained
calling the API service I2c_GetStatus.
*/
typedef enum
{
  /* The I2C Driver is not initialized. */
  I2C_UNINIT = 0,
  /* The I2C Driver is idle. */
  I2C_IDLE,
  /* The I2C Driver is performing busy. */
  I2C_BUSY
}I2c_ChannelStatusType;

typedef enum
{
  I2C_NO_ERR = 0,
  I2C_TX_UNDERFLOW,
  I2C_TX_OVERFLOW,
  I2C_RX_UNDERFLOW,
  I2C_RX_OVERFLOW,
  I2C_NO_ACK,
  I2C_ARBITRATION_LOST,
  I2C_INVALID_CHANNEL,
  I2C_INVALID_SIZE,
  I2C_INVALID_ADDRESS,
  I2C_NULL_PTR,
  I2C_IS_UNINIT,
  I2C_IS_BUSY,
  I2C_ERR_OTHER
}I2c_ErrorType;

typedef enum
{
I2C_7_BIT_ADDRESSING,
I2C_10_BIT_ADDRESSING
}I2c_AddressingModeType;

typedef void(*I2c_NotifFunctionPtrType)(I2c_ErrorType ErrorId);

typedef struct
{
  I2c_NotifFunctionPtrType I2c_NotifFunctionPtr;
}I2c_NotifType;

typedef struct
{
  const uint8 HwUnit;

  const uint32 AdddressCfgValue;

  const uint32 FracDividerCfgValue;

  const uint32 FracDividerHighCfgValue;

  const uint32 TimingCfgvalue;

  const uint32 FIFOCfgValue;

  const uint8  PortPinCfgvalue;

  const uint32 HWClkSetting;

  const I2c_AddressingModeType AddressingMode;

  I2c_NotifType I2c_Notif;

  const uint32 TxTimeOutCount;
  const uint32 RxTimeOutCount;

}I2c_ChannelConfigType;


typedef struct
{
  const I2c_ChannelConfigType* I2c_ChannelConfigPtr;
  const uint8 I2c_MaxChannels;

} I2c_ConfigType;

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
#define I2C_START_SEC_CODE_QM_LOCAL

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
extern void I2c_Init(const I2c_ConfigType* const ConfigPtr);
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
extern Std_ReturnType I2c_DeInit(void);

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
extern I2c_ErrorType I2c_SyncWrite(const I2c_ChannelType ChannelId,
           I2c_DataType *const DataPtr,const I2c_SizeType Size, \
           const I2c_SlaveAddrType SlaveAddress);
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
**                   DataPtr- Pointer to data that is read                    **
**                   Size- Size of data to be recieved in Bytes               **
**                   SlaveAddress- Address of slave                           **
**                                                                            **                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : I2C_OK: I2C operation Successful                         **
**                   I2C_NOT_OK: I2C operation not Successful.                **
**                   I2C_IS_BUSY: I2C module is busy.                         **
**                                                                            **
** Description     : The service I2c_Read() is called to perform Read         **
**                   operation.                                               **
**                                                                            **
*******************************************************************************/

extern I2c_ErrorType I2c_SyncRead(const I2c_ChannelType ChannelId,
           I2c_DataType *const DataPtr,const I2c_SizeType Size,
           const I2c_SlaveAddrType SlaveAddress);
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
** Sync/Async      : Asynchronous                                              **
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

extern I2c_ErrorType I2c_AsyncWrite(const I2c_ChannelType ChannelId,
           I2c_DataType *const DataPtr,const I2c_SizeType Size, \
           const I2c_SlaveAddrType SlaveAddress);
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
** Sync/Async      : Asynchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant(for same channel)                          **
**                                                                            **
** Parameters (in) : ChannelId- I2C Channel identifier                        **
**                   DataPtr- Pointer to data that is read                    **
**                   Size- Size of data to be recieved in Bytes               **
**                   SlaveAddress- Address of slave                           **
**                                                                            **                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : I2C_OK: I2C operation Successful                         **
**                   I2C_NOT_OK: I2C operation not Successful.                **
**                   I2C_IS_BUSY: I2C module is busy.                         **
**                                                                            **
** Description     : The service I2c_Read() is called to perform Read         **
**                   operation.                                               **
**                                                                            **
*******************************************************************************/

extern I2c_ErrorType I2c_AsyncRead(const I2c_ChannelType ChannelId,
           I2c_DataType *const DataPtr,const I2c_SizeType Size,
           const I2c_SlaveAddrType SlaveAddress);
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
**                   know if the specified I2C module is I2C_IDLE I2C_BUSY.   **
**                                                                            **
*******************************************************************************/
extern I2c_ChannelStatusType I2c_GetStatus(const I2c_ChannelType ChannelId);

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
extern Std_ReturnType I2c_CancelOperation(const I2c_ChannelType ChannelId, \
                                   I2c_SizeType *const TransmittedDataSize);
/*******************************************************************************
**                                                                            **
** Syntax          : void I2c_IsrI2cDtr(const uint8 HwUnit)                   **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Reentrant                                                **
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
extern void I2c_IsrI2cDtr(const uint8 HwUnit);
/*******************************************************************************
**                                                                            **
** Syntax          : void I2c_IsrI2cProtocol(const uint8 HwUnit)              **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Reentrant                                                **
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
extern void I2c_IsrI2cProtocol(const uint8 HwUnit);
/*******************************************************************************
**                                                                            **
** Syntax          : void I2c_IsrI2cError(const uint8 HwUnit)                 **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Reentrant                                                **
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
extern void I2c_IsrI2cError(const uint8 HwUnit);

#if(I2C_VERSION_INFO_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Syntax           : void I2c_GetVersionInfo                                 **
**                    (                                                       **
**                      Std_VersionInfoType * const VersionInfoPtr            **
**                    )                                                       **
**                                                                            **
** Description      : This API returns the version information of this module.**
**                    Note: This API is available only when AdcVersionInfoApi **
**                    is configured as true.                                  **
**                                                                            **
** Service ID       : 0x57                                                    **
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
extern void I2c_GetVersionInfo(Std_VersionInfoType * const VersionInfoPtr);
#else
#define I2c_GetVersionInfo(versioninfo) (ERROR_I2c_GetVersionInfo_NOT_SELECTED)
#endif /* End for I2C_VERSION_INFO_API */

#define I2C_STOP_SEC_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "I2c_MemMap.h"
/*******************************************************************************
**                      Global Function Declarations:                         **
**             Functions to be Called From Interrupt/Scheduler Context        **
*******************************************************************************/

/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "I2c_PBCfg.h"

#endif /* I2C_H */
