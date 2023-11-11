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
**  FILENAME     : Hssl.h                                                     **
**                                                                            **
**  VERSION      : 1.40.0_7.0.0                                               **
**                                                                            **
**  DATE         : 2020-04-16                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Hssl Driver header definition file                         **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

#ifndef HSSL_H
#define HSSL_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Inclusion of Platform_Types.h and Compiler.h */
#include "Std_Types.h"

#include "Dma.h"

/* Pre-compile configuration parameters for HSSL */
#include "Hssl_Cfg.h"

#if ( HSSL_DEV_ERROR_DETECT == STD_ON)
/* Import of DET functionality */
#include "Det.h"
#endif  /* End Of HSSL_DEV_ERROR_DETECT */

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
#define HSSL_MODULE_INSTANCE ((uint8)0U)
/*
  Module Identification, Vendor Identification
*/
/* HSSL Module ID */
#define HSSL_MODULE_ID            ((uint16)255U)
/* HSSL Vendor ID */
#define HSSL_VENDOR_ID            (17U)

/* Return value when Development Error found*/
#define HSSL_ERR_FOUND          (1U)
/* Return value when Development error is not found*/
#define HSSL_ERR_NOT_FOUND      (0U)

/* Development Error values */
#if (HSSL_DEV_ERROR_DETECT == STD_ON)
/*
  Development error codes
*/
/* Service is called before Init */
#define HSSL_E_NOT_INITIALIZED                  ((uint8)1U)
/* Service is called with NULL pointer */
#define HSSL_E_INV_POINTER                      ((uint8)2U)
/* Service is called with invalid parameter */
#define HSSL_E_INV_PARAM                        ((uint8)3U)
/* Service is called in an Invalid driver Mode */
#define HSSL_E_INV_MODE                         ((uint8)4U)
/* Service is called with Unconfigured Hssl Instance */
#define HSSL_E_INSTANCE_NOT_CONFIGURED          ((uint8)5U)

/*
  HSSL API Service ID's
*/

/* Service ID for Hssl_SetMode */
#define HSSL_SID_MODE             ((uint8)58)
/* Service ID for Hssl_Reset */
#define HSSL_SID_RESET            ((uint8)59)
/* Service ID for Hssl_Init */
#define HSSL_SID_INIT             ((uint8)60)
/* Service ID for Hssl_InitChannel */
#define HSSL_SID_INIT_CH          ((uint8)61)
/* Service ID for Hssl_Write */
#define HSSL_SID_WRITE            ((uint8)62)
/* Service ID for Hssl_WriteAck */
#define HSSL_SID_WRITE_ACK        ((uint8)63)
/* Service ID for Hssl_Read */
#define HSSL_SID_READ             ((uint8)64)
/* Service ID for Hssl_ReadReply */
#define HSSL_SID_READ_REPLY       ((uint8)65)
/* Service ID for Hssl_Id */
#define HSSL_SID_READ_ID          ((uint8)66)
/* Service ID for Hssl_StartStream */
#define HSSL_SID_STREAM           ((uint8)67)
/* Service ID for Hssl_StopStream */
#define HSSL_SID_STREAM_STOP      ((uint8)68)
/* Service ID for Hssl_MultiWrite */
#define HSSL_SID_WRITE_MULTIPLE   ((uint8)69)
/* Service ID for Hssl_MultiRead */
#define HSSL_SID_READ_MULTIPLE    ((uint8)70)
/* Service ID for Hssl_GetGlobalError */
#define HSSL_SID_GET_GLOBALERROR  ((uint8)71)
/* Service ID for Hssl_GetVersionInfo */
#define HSSL_SID_GET_VERSIONINFO  ((uint8)72)
/* Service ID for Hssl_ActivateSlave */
#define HSSL_SID_ACTIVATE_SLAVE   ((uint8)73)
/* Service ID for Hssl_DeactivateSlave */
#define HSSL_DEACTIVATE_SLAVE     ((uint8)74)
/* Service ID for Hssl_SelectSlave */
#define HSSL_SID_SELECT_SLAVE     ((uint8)75)
/* Service ID for Hssl_GetChannelError */
#define HSSL_SID_GET_CHANNELERROR ((uint8)76)
/* Service ID for Hssl_Trigger */
#define HSSL_SID_TRIGGER ((uint8)77)

#endif  /* End of (HSSL_DEV_ERROR_DETECT == STD_ON) */


/* Driver States */
#define HSSL_DRIVER_INITIALIZED   (1U)
#define HSSL_DRIVER_UNINITIALIZED (2U)

/* HSSL Modes */
#define HSSL_MODE_INIT           ((uint8)(1U))
#define HSSL_MODE_RUN            ((uint8)(2U))
#define HSSL_MODE_SLEEP          ((uint8)(3U))
/* HSSL Commands */
#define HSSL_READ_FRAME          ((uint8)(1U))
#define HSSL_WRITE_FRAME         ((uint8)(2U))
#define HSSL_TRIGGER_FRAME       ((uint8)(3U))
#define HSSL_READ_ID_FRAME       ((uint8)(4U))

/* Macros to identify the Channel numbers */
#define HSSL_CH0                (0U)
#define HSSL_CH1                (1U)
#define HSSL_CH2                (2U)
#define HSSL_CH3                (3U)
#define HSSL_CHANNEL_INVALID    (4U)

#define HSSL_ID_INVALID    (255U)

/* Possible data size values */
#define HSSL_DATA_SIZE_8BIT      (0U)
#define HSSL_DATA_SIZE_16BIT     (1U)
#define HSSL_DATA_SIZE_32BIT     (2U)
#define HSSL_MAX_DATA_SIZE       (3U)

/*HSSL_CLC.bit0 = 0 is Enable the module */
#define HSSL_MOD_ENABLE            (0U)
#define HSCT_MOD_ENABLE            (0U)

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
/* Hssl_DataTemplateType structure - contains the data and address pointers */
typedef struct
{
    uint32 *Data;
    uint32 *Address;
} Hssl_DataTemplateType;

/*Hssl_ReadDataTemplateType structre contains the address for each array*/
typedef struct
{
    uint32 *Address;
} Hssl_ReadDataTemplateType;


/* Typedefition for HSSL Instance ID */
typedef enum
{
    HSSL0 = 0U,
    HSSL1 = 1U
} Hssl_InstanceID;

/* Typedefition for HSSL SLAVE Status */
typedef enum
{
    HSSL_SLAVE_ACTIVATED = 0U,
    HSSL_SLAVE_DEACTIVATED = 1U,
    HSSL_SLAVE_NOT_RESPONDING = 2U,
    HSSL_SLAVE_NOT_SELECTED =3U
} Hssl_SlaveStatusType;

/* Typedefition for HSSL CHANNEL ERROR Status */
typedef enum
{
    HSSL_CHANNEL_NO_ERROR = 0U,
    HSSL_CHANNEL_NACK_ERROR = 1U,
    HSSL_CHANNEL_TRANSACTION_TAG_ERROR = 2U,
    HSSL_CHANNEL_TIMEOUT_ERROR = 4U,
    HSSL_CHANNEL_UNEXPECTED_ERROR = 8U
} Hssl_ChannelErrorType;

/* Hssl_ChannelType structure should be utilised as a 4 element array
 in the application (for HSSL Channels 1-4)*/
typedef struct
{
    uint8 Number;
    uint32 Timeout;
} Hssl_ChannelType;

/* Events reported by HSSL module */
typedef enum
{
    HSSL_NO_EVENT = 0U,
    HSSL_WRITE_COMMAND_COMPLETED = 0x2U,
    HSSL_READ_COMMAND_COMPLETED = 0x4U,
    HSSL_TRIGGER_COMMAND_COMPLETED = 0x8U,
    HSSL_ERROR_NACK = 0x10U,
    HSSL_ERROR_TRANSACTION_TAG = 0x20U,
    HSSL_ERROR_TIMEOUT = 0x40U,
    HSSL_ERROR_UNEXPECTED = 0x80U,
    HSSL_STREAM_BLOCK_TRANSMITTED = 0x100U,
    HSSL_STREAM_BLOCK_ERROR_OCCURED = 0x200U,
    HSSL_STREAM_BLOCK_RECEIVED = 0x400U,
    HSSL_SRI_BUS_ERROR = 0x800U,
    HSSL_PIE1_CHANNEL_NUMBER_CODE_ERROR = 0x1000U,
    HSSL_PIE2_DATA_LENGHT_ERROR = 0x2000U,
    HSSL_CRC_ERROR = 0x4000U
}Hssl_EventType;

typedef void(*Hssl_UserNotify)(uint32 Event);

typedef void(*Hssl_DMAUserNotify)(Dma_EventsType Event);

typedef void Hssl_ConfigType;

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
#define HSSL_START_SEC_CODE_QM_LOCAL
#include "Hssl_MemMap.h"

/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_Init(                                **
**                            const Hssl_ConfigType* const Address)           **
**                                                                            **
** Description     : Initializes Initiator / Target side of HSSL module.      **
**                                                                            **
** Service ID      : 0x3A                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : Address: Configuration address                           **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Hssl_Init(const Hssl_ConfigType* const Address);

/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_Reset(const Hssl_InstanceID id)      **
**                                                                            **
** Description     : Performs Kernel reset of module,clears all status and    **
**                   error registers, disables module clock and sets driver   **
**                   module.  Any transfers in progress when reset is called  **
**                   will immediately end.                                    **
**                                                                            **
** Service ID      : 0x3B                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id - Specifies HSSL instance (0: HSSL0, 1: HSSL1)        **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Hssl_Reset(const Hssl_InstanceID id) ;

/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_SetMode(const Hssl_InstanceID id,    **
**                                                      const uint8 Mode)     **
**                                                                            **
** Description     : Puts the HSSL module into the required mode.             **
**                   Must be used to place module into 'INIT' mode before     **
**                   calling the initialization functions.                    **
**                   function.                                                **
**                                                                            **
** Service ID      : 0x3C                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id - Specifies HSSL instance (0: HSSL0, 1: HSSL1)        **
**                   Mode                                                     **
**                   0 = Disabled, 1 = Enabled/Init, 2 = Enabled/Run          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Hssl_SetMode(const Hssl_InstanceID id, const uint8 Mode) ;

/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_InitChannel(                         **
**                                          const Hssl_InstanceID id,         **
**                                   const Hssl_ChannelType *const Channel,   **
**                                          const uint8 TimeoutErr,           **
**                                          const uint8 TransID,              **
**                                          const uint8 AckErr)               **
**                                                                            **
** Description     : Initializes HSSL Channel. Also sets up interrupts.       **
**                   events to handle received packets appropriately.         **
**                                                                            **
** Service ID      : 0x3D                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id - Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   Channel : HSSL Channel to use.                           **
**                   TimeoutErr: Enable/Disable Timeout Error interrupt.      **
**                   TransID: Enable/Disable Transaction ID Error interrupt.  **
**                   AckErr: Enable/Disable Acknowledge Error interrupt.      **
**                     (0 to disable, 1 to enable)                            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Hssl_InitChannel (const Hssl_InstanceID id,
                                       const Hssl_ChannelType *const Channel,
                                        const uint8 TimeoutErr, 
                                        const uint8 TransID,
                                        const uint8 AckErr);

/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_Write(const Hssl_InstanceID id,      **
**                    const Hssl_DataTemplateType *WriteData,                 **
**                    const uint16 DataSize,                                  **
**                    const Hssl_ChannelType *const Channel,                  **
**                    const uint16 InjectedError)                             **
**                                                                            **
** Description     : Performs a direct write transfer.                        **
**                                                                            **
** Service ID      : 0x3E                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id - Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   WriteData :: Pointer to Hssl_DataTemplateType structure  **
**                   which includes write Address and Data to be written.     **
**                   DataSize:: Size of data to be written.                   **
**                   Channel:: HSSL Channel to used.                          **
**                   InjectedError: injected error (if required)              **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Hssl_Write (const Hssl_InstanceID id,
                                  const Hssl_DataTemplateType *WriteData,
                                  const uint16 DataSize,
                                  const Hssl_ChannelType *const Channel,
                                  const uint16 InjectedError
                                 ) ;

/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_WriteAck(                            **
**                                  const Hssl_InstanceID id,                 **
**                                  const Hssl_ChannelType *const Channel)    **
**                                                                            **
** Description     : Write acknowledge function, should be called when a      **
**                    write acknowledge is received by the module, or a       **
**                    timeout occurs during a write command.                  **
**                                                                            **
** Service ID      : 0x3F                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id - Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   Channel:: HSSL Channel to use within an instance         **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Hssl_WriteAck(
    const Hssl_InstanceID id,
    const Hssl_ChannelType *const Channel);

/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_Read(                                **
**                    const Hssl_InstanceID id,                               **
**                    const Hssl_DataTemplateType *DataAddress,               **
**                    const uint16 DataSize,                                  **
**                    const Hssl_ChannelType *const Channel,                  **
**                    const uint16 InjectedError)                             **
**                                                                            **
** Description     : Performs a direct Read transfer.                         **
**                                                                            **
** Service ID      : 0x40                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id - Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   DataAddress :Pointer to Hssl_DataTemplateType structure  **
**                       which includes read Address                          **
**                   DataSize:: Size of data to be read.                      **
**                   Channel:: HSSL Channel to use.                           **
**                   InjectedError: injected error (if required)              **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Hssl_Read(const Hssl_InstanceID id,
                                const Hssl_DataTemplateType *DataAddress,
                                const uint16 DataSize,
                                const Hssl_ChannelType *const Channel,
                                const uint16 InjectedError
                               ) ;
#if (HSSL_OPERATING_MODE == HSSL_POLLING_MODE)
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_ReadRply (                           **
**                          const Hssl_InstanceID id,                         **
**                          const Hssl_ChannelType *const Channel)            **
**                                                                            **
** Description     : Reply function which is called either when a successful  **
**                   read reply is received, or when a timeout is reached.    **
**                   If called due to a timeout then only the Channel and     **
**                   Error parameters will be written.                        **
**                                                                            **
** Service ID      : 0x41                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id - Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   Channel:: HSSL Channel to use.                           **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Hssl_ReadRply (const Hssl_InstanceID id,\
                                     const Hssl_ChannelType *const Channel);
#endif
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_Id(                                  **
**                                      const Hssl_InstanceID id,             **
**                                      uint32 *const StoreAddress,           **
**                                     const Hssl_ChannelType *const Channel) **
**                                                                            **
** Description     : Sends ID Request Frame to target. Stores received        **
**                   command in the address passed.                           **
**                                                                            **
** Service ID      : 0x42                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   StoreAddress : Pointer to the Address location/variable  **
**                    to store the ID received from target                    **
**                   Channel:: HSSL Channel to use.                           **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Hssl_Id(const Hssl_InstanceID id, 
                       uint32 *const StoreAddress,
                       const Hssl_ChannelType *const Channel);
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_Trigger(                             **
**                                      const Hssl_InstanceID id,             **
**                                     const Hssl_ChannelType *const Channel) **
**                                                                            **
** Description     : Sends ID Request Frame to target. Stores received        **
**                   command in the address passed.                           **
**                                                                            **
** Service ID      : 0x43                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   Channel:: HSSL Channel to use.                           **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Hssl_Trigger(const Hssl_InstanceID id,
                                   const Hssl_ChannelType *const Channel);

/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_StartStream                          **
**                    ( const Hssl_InstanceID id,                             **
**                      const uint32 *const SourceAddressStart,               **
**                      const uint32 *const DestinationAddressStart,          **
**                      const uint16 DataSize,                                **
**                      const uint16 InjectedError)                           **
**                                                                            **
** Description     : Performs streaming write transfer.                       **
**                                                                            **
** Service ID      : 0x43                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   SourceAddressStart : Pointer to address containing start **
**                      of data to be streamed.                               **
**                   DestinationAddressStart : Pointer to address containing  **
**                      destination of data to be streamed.                   **
**                   DataSize:: Size of data to be written.                   **
**                   InjectedError: injected Error (if required)              **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Hssl_StartStream (const Hssl_InstanceID id,\
                                        const uint32 *const SourceAddressStart,\
                                   const uint32 *const DestinationAddressStart,\
                                        const uint16 DataSize,
                                        const uint16 InjectedError) ;

/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_StopStream(const Hssl_InstanceID id) **
**                                                                            **
** Description     : Stops the ongoing data streaming.                        **
**                                                                            **
** Service ID      : 0x45                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Hssl_StopStream(const Hssl_InstanceID id) ;

/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_MultiWrite                           **
**                    ( const Hssl_InstanceID id,                             **
**                      const Hssl_DataTemplateType *WriteArray,              **
**                      const uint16 DataSize, const uint16 NumCmd,           **
**                const Hssl_ChannelType *const Channel,                      **
**                 const uint16 InjectedError)                                **
**                                                                            **
** Description     : Performs multiple write transfers.                       **
**                                                                            **
** Service ID      : 0x46                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   WriteArray : Hssl_DataTemplateType structure which       **
**                     includes array containing write Address and Data to be **
**                     written for each array record.                         **
**                   DataSize: Size of data to be written.                    **
**                   NumCmd : Number of address command pairs                 **
**                   Channel: HSSL Channel to use.                            **
**                   InjectedError: injected Error (if required)              **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Hssl_MultiWrite (const Hssl_InstanceID id,
                                       const Hssl_DataTemplateType *WriteArray,
                                       const uint16 DataSize,
                                       const uint16 NumCmd,
                                       const Hssl_ChannelType *const Channel,
                                       const uint16 InjectedError
                                      ) ;

/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_MultiRead                            **
**                    ( const Hssl_InstanceID id,                             **
**                      const Hssl_DataTemplateType *ReadArray,               **
**                      const uint32 *Buffer,                                 **
**                      const uint16 DataSize, const uint16 NumCmd,           **
**                const Hssl_ChannelType *const Channel,                      **
**                      const uint16 InjectedError)                           **
**                                                                            **
** Description     : Performs multiple read transfers.                        **
**                                                                            **
** Service ID      : 0x47                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   ReadArray : Hssl_DataTemplateType structure which        **
**                    includes array containing write Address and Data to be  **
**                    read for each array record.                             **
**                   Buffer: Store buffer for received data                   **
**                   DataSize: Size of data to be written.                    **
**                   NumCmd : Number of address command pairs                 **
**                   Channel: HSSL Channel to use.                            **
**                   InjectedError: injected Error (if required)              **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Hssl_MultiRead (const Hssl_InstanceID id,
                                    const Hssl_ReadDataTemplateType *ReadArray,
                                      const uint32 *Buffer,
                                      const uint16 DataSize,
                                      const uint16 NumCmd,
                                      const Hssl_ChannelType *const Channel,
                                      const uint16 InjectedError
                                     ) ;
#if(HSSL_MULTI_SLAVE_MODE == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_SelectSlave(const Hssl_InstanceID id,**
**                         const uint8 Hssl_SlaveID)                          **
**                                                                            **
** Description     : Selecting the slave in multi slave mode.                 **
**                                                                            **
** Service ID      : 0x4A                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   Hssl_SlaveID : Indicates HSSL slave ID                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Hssl_SelectSlave(const Hssl_InstanceID id,\
                                       const uint8 Hssl_SlaveID);
#endif

#if (HSSL_INTERFACE_MODE == HSSL_MASTER)
#if(HSSL_MULTI_SLAVE_MODE == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_ActivateSlave(const Hssl_InstanceID  **
**                   id, const uint8 Hssl_SlaveID,                            **
**                   Hssl_SlaveStatusType *const Hssl_SlaveStatus)            **
**                                                                            **
** Description     : Activates the slave in multi slave mode.                 **
**                                                                            **
** Service ID      : 0x48                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   Hssl_SlaveID : Indicates HSSL Slave ID                   **
**                                                                            **
** Parameters (out): Hssl_SlaveStatus : returns the slave status              **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Hssl_ActivateSlave(const Hssl_InstanceID id,\
        const uint8 Hssl_SlaveID,
        Hssl_SlaveStatusType *const Hssl_SlaveStatus);
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_DeactivateSlave(const Hssl_InstanceID**
**                   id, const uint8 Hssl_SlaveID,                            **
**                   Hssl_SlaveStatusType *const Hssl_SlaveStatus)            **
**                                                                            **
** Description     : Deactivates the slave in multi slave mode.               **
**                                                                            **
** Service ID      : 0x49                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   Hssl_SlaveID : Indicates HSSL Slave ID                   **
**                                                                            **
** Parameters (out): Hssl_SlaveStatus : returns the slave status              **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Hssl_DeactivateSlave(const Hssl_InstanceID id,\
        const uint8 Hssl_SlaveID,\
        Hssl_SlaveStatusType *const Hssl_SlaveStatus);
#endif
#endif
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_GetGlobalError(                      **
**                                  const Hssl_InstanceID id,\                **
**                                  uint32 *const Hssl_GlobalErrFlg);         **
**                                                                            **
** Description     : Reads the global error flags for the HSSL                **
**                                                                            **
** Service ID      : 0x4B                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   Hssl_GlobalErrFlg: Pointer to store Hssl                 **
                                        Global error flags value              **
** Parameters (out): Hssl_GlobalErrFlg : Hssl Global error flags value        **
**                                                                            **
** Return value    : Returns 'E_OK' if successful, 'E_NOT_OK' otherwise.      **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Hssl_GetGlobalError(const Hssl_InstanceID id,\
        uint32 *const Hssl_GlobalErrFlg);
/*******************************************************************************
** Traceability    : [cover parentID=][/cover]                                **
**                                                                            **
** Syntax          : Std_ReturnType Hssl_GetChannelError                      **
**                 (const Hssl_InstanceID id,Hssl_ChannelType *const Channel, **
**                      Hssl_ChannelErrorType *ChannelError)                  **
**                                                                            **
** Description     : Reads the channel error flags for the HSSL channel       **
**                                                                            **
** Service ID      : 0x4C                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   Channel: HSSL Channel to use.                            **
**                   ChannelError : Holds the channel error occured           **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    : Returns E_OK, Successful execution. Otherwise E_NOT_OK.   **
*******************************************************************************/
extern Std_ReturnType Hssl_GetChannelError(const Hssl_InstanceID id,
                                    const Hssl_ChannelType *const Channel,
                                    Hssl_ChannelErrorType *const ChannelError);
/*******************************************************************************
** Syntax          : void Hssl_IsrCOK(const Hssl_InstanceID id,               **
**                                         const uint8 Channel)               **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1)        **
**                   Channel: HSSL Channel to use                             **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value    : none                                                     **
**                                                                            **
** Description     : ISR get called error free frame response                 **
                    triggers a COK interrupt                                  **
*******************************************************************************/
extern void Hssl_IsrCOK(const Hssl_InstanceID id, const uint8 Channel);
/*******************************************************************************
** Syntax          : void Hssl_IsrRDI(const Hssl_InstanceID id,               **
**                                          const uint8 Channel)              **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1)        **
**                   Channel: HSSL Channel to use                             **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value    : none                                                     **
**                                                                            **
** Description     : ISR get called read frame response is received           **
*******************************************************************************/
extern void Hssl_IsrRDI(const Hssl_InstanceID id, const uint8 Channel);
/*******************************************************************************
** Syntax          :void Hssl_IsrError(const Hssl_InstanceID id,              **
**                                   const uint8 Channel)                     **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1)        **
**                   Channel: HSSL Channel to use                             **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value    : none                                                     **
**                                                                            **
** Description     : ISR get called error intrrupt is triggered               **
*******************************************************************************/
extern void Hssl_IsrError(const Hssl_InstanceID id, const uint8 Channel);
/*******************************************************************************
** Syntax          : void Hssl_IsrTrg(const Hssl_InstanceID id,               **
**                                  const uint8 Channel)                      **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1)        **
**                   Channel: HSSL Channel to use                             **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value    : none                                                     **
**                                                                            **
** Description     : ISR get called at target when trigger frame is aarived   **
*******************************************************************************/
extern void Hssl_IsrTrg(const Hssl_InstanceID id, const uint8 Channel);
/*******************************************************************************
** Syntax          : void Hssl_IsrEXI(const Hssl_InstanceID id)               **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1)        **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value    : none                                                     **
**                                                                            **
** Description     : ISR get called during global error                       **
*******************************************************************************/
extern void Hssl_IsrEXI(const Hssl_InstanceID id);

/*******************************************************************************
**                                                                            **
** Traceability     :                                                         **
**                                                                            **
** Syntax          : void Hssl_DmaCallout                                     **
**                   (const uint32 Channel, const Dma_EventsType Event)      **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      :                                                          **
**                                                                            **
** Reentrancy      :                                                          **
** [/cover]                                                                   **
** Parameters (in) : Channel - DMA channel number                             **
**                   Event - DMA channel event (enum)                         **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     :                                                          **
*******************************************************************************/
extern void Hssl_DmaErrCallout (const uint32 Channel,
                                 const Dma_EventsType Event);

/*******************************************************************************
**                                                                            **
** Traceability     :                                                         **
**                                                                            **
** Syntax          : void Hssl_DmaCallout                                     **
**                   (const uint32 Channel, const Dma_EventsType Event)      **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      :                                                          **
**                                                                            **
** Reentrancy      :                                                          **
** [/cover]                                                                   **
** Parameters (in) : Channel - DMA channel number                             **
**                   Event - DMA channel event (enum)                         **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     :                                                          **
*******************************************************************************/
extern void Hssl_DmaCallout(const uint32 Channel, const Dma_EventsType Event);

#if(HSSL_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Traceability    : [cover parentID=]                                        **
**                                                                            **
** Syntax          : void  Hssl_GetVersionInfo                                **
**                   ( const Hssl_InstanceID id,                              **
**                     Std_VersionInfoType *const versioninfo                 **
**                   )                                                        **
**                                                                            **
** Description     : This service returns the version information of module.  **
**                   The version information includes:                        **
**                   - Vendor Id                                              **
**                   - Module Id                                              **
**                   - SW Major Version                                       **
**                   - SW Minor Version                                       **
**                   - SW Patch Version                                       **
**                                                                            **
** Service ID      : 0x4c                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : id : Specifies HSSL instance (0: HSSL0, 1: HSSL1).       **
**                   versioninfo : (Pointer to store the version              **
**                   information of this module)                              **
**                                                                            **
** Parameters (out): versioninfo values are updated with version              **
**                   information                                              **
**                                                                            **
** Return value:   : None                                                     **
**                                                                            **
*******************************************************************************/
extern void Hssl_GetVersionInfo(Std_VersionInfoType *const versioninfo);
#endif

#define HSSL_STOP_SEC_CODE_QM_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Hssl_MemMap.h"

#endif  /* HSSL_H */
