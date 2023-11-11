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
**  FILENAME     : Uart.h                                                     **
**                                                                            **
**  VERSION      : 17.0.0                                                     **
**                                                                            **
**  DATE         : 2021-11-02                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY : [cover parentID={F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}]    **
**                                                                            **
**  DESCRIPTION  : Uart Driver header definition file.                        **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Uart Driver, AUTOSAR Release 4.2.2 and**
**                                                  AUTOSAR Release 4.4.0     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/* [cover parentID={78296DD4-3F34-4cc4-83DC-98155A2DBD26}] */
/*  [/cover] */
#ifndef UART_H
#define UART_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/* Inclusion of Platform_Types.h and Compiler.h */
#include "Std_Types.h"

/* Pre-compile configuration parameters for UART */
#include "Uart_Cfg.h"

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/* [cover parentID={40FE0CDC-A039-4c2c-8168-A1EDE8BD52C2}] */
/*  [/cover] */
/* Vendor ID */
#define UART_VENDOR_ID                      (17U)

/* UART module identifier 255 */
#define UART_MODULE_ID                      (255U)

/* UART instance identifier */
#define UART_INSTANCE_ID                    (UART_INDEX)

/* Alternate receive pin selection */
#define UART_SELECT_A                       0U
#define UART_SELECT_B                       1U
#define UART_SELECT_C                       2U
#define UART_SELECT_D                       3U
#define UART_SELECT_E                       4U
#define UART_SELECT_F                       5U
#define UART_SELECT_G                       6U
#define UART_SELECT_H                       7U
/* Alternate CTS pin section */
#define UART_SELECT_CTS_NONE                0u
#define UART_SELECT_CTS_A                   0U
#define UART_SELECT_CTS_B                   1U
#define UART_SELECT_CTS_C                   2U
#define UART_SELECT_CTS_D                   3U



#if ((UART_DEV_ERROR_DETECT == STD_ON) || \
(UART_SAFETY_ENABLE == STD_ON) || \
(UART_RUNTIME_ERROR_DETECT == STD_ON))
/*
  Development and Safety error code values
*/

/* API service used without module initialization */
#define UART_E_UNINIT                       ((uint8)0x00)

/* API service used with an invalid channel identifier */
#define UART_E_INVALID_CHANNEL              ((uint8)0x01)

/* API service used with an invalid/NULL pointer */
#define UART_E_PARAM_POINTER                ((uint8)0x02)

/* API service called when channel is in busy state. */
#define UART_E_STATE_BUSY                   ((uint8)0x03)

/* Module initialization failed */
#define UART_E_INIT_FAILED                  ((uint8)0x04)

/* API service called with invalid data length parameter */
#define UART_E_INVALID_SIZE                 ((uint8)0x05)

/* API service(init) called when driver is already init */
#define UART_E_ALREADY_INITIALIZED          ((uint8)0x06)

#if (UART_SAFETY_ENABLE == STD_ON)
/* Spurious receive isr */
#define UART_E_SPURIOUS_INTERRUPT           ((uint8)0x07)

/* IRQ handler called with invalid hardware unit identifier */
#define UART_E_INVALID_HW_UNIT              ((uint8)0x08)

/* Fill level not matched with number of bytes filled in TXFIFO.*/
#define UART_E_TXFIFO_FILL_ERR              ((uint8)0x09)
#endif

/*
  API Service ID's
*/

/* [cover parentID={A9833DCE-2F78-4a57-8F14-1ECD1C0F6F9D}]
[/cover] */
/* API Service identifier init function */
#define UART_SID_INIT                       ((uint8)215)

#if (UART_INIT_CHECK_API == STD_ON)
/* API Service ID for Uart_InitCheck() */
#define UART_SID_INITCHECK                  ((uint8)216)
#endif
/* API Service ID for Uart_Read() */
#define UART_SID_READ                       ((uint8)217)

/* API Service ID for Uart_Write() */
#define UART_SID_WRITE                      ((uint8)218)

#if (UART_ABORT_WRITE_API == STD_ON)
/* API Service ID for Uart_AbortWrite() */
#define UART_SID_ABORT_WRITE                ((uint8)219)
#endif

#if (UART_ABORT_READ_API == STD_ON)
/* API Service ID for Uart_AbortRead() */
#define UART_SID_ABORT_READ                 ((uint8)220)
#endif

/* API Service ID for Uart_GetStatus() */
#define UART_SID_GETSTATUS                  ((uint8)221)

#if (UART_DEINIT_API == STD_ON)
/* API Service ID for Uart_DeInit() */
#define UART_SID_DEINIT                     ((uint8)222)
#endif

#if(UART_VERSION_INFO_API == STD_ON)
/* API Service ID for Uart_GetVersionInfo() */
#define UART_SID_VERINFO                    ((uint8)223)
#endif

/* API Service ID for Uart_MainFunction_Read() */
#define UART_SID_MAIN_READ                  ((uint8)224)

/* API Service ID for Uart_MainFunction_Write() */
#define UART_SID_MAIN_WRITE                 ((uint8)225)

/* API Service ID for Uart_IsrError() */
#define UART_SID_ISR_ERROR                  ((uint8)226)

#if((UART_SAFETY_ENABLE == STD_ON) || (UART_RUNTIME_ERROR_DETECT == STD_ON))
/* API Service ID for Uart_IsrReceive() */
#define UART_SID_ISR_RECEIVE                ((uint8)227)
#endif

#if(UART_SAFETY_ENABLE == STD_ON)
/* API Service ID for Uart_IsrTransmit() */
#define UART_SID_ISR_TRANSMIT               ((uint8)228)
#endif

#if((UART_DEV_ERROR_DETECT == STD_ON) || (UART_SAFETY_ENABLE == STD_ON))
/* API Service ID for Uart_StartStreaming() */
#define UART_SID_START_STREAMING            ((uint8)229)

/* API Service ID for Uart_StopStreaming() */
#define UART_SID_STOP_STREAMING             ((uint8)230)
#endif

#endif
/*******************************************************************************
**                    Exported Type Definitions                               **
*******************************************************************************/
/* [cover parentID={D9B74459-5D93-4ce6-971C-048CD4DB9CAA}] */
/*  [/cover] */
/*
Type: Uart_MemType
Data type of the buffer used by the UART channels for data reception and
transmission.
*/
typedef uint8 Uart_MemType;

/* [cover parentID={E1B3608E-5D12-44ee-AC29-3D1B35A25659}] */
/*  [/cover] */
/*
Type: Uart_SizeType
The Uart_SizeType specifies the number of data bytes to be transmitted/received.
*/
typedef uint16 Uart_SizeType;

/* [cover parentID={1E98E053-4C94-48a5-9016-320FC0300EF7}] */
/*  [/cover] */
/*
Type: Uart_ChannelIdType
The Uart_ChannelIdType specifies the Datatype of the Logical Channel Ids
*/
typedef uint8 Uart_ChannelIdType;

/* [cover parentID={4B26D4B6-8E86-49c1-9596-BCD739CE774E}] */
/*  [/cover] */
/*
This type definition specifies the error if they have occured
during the data transmission and reception on a particular Uart channel.
*/
typedef enum
{
  /* No error */
  UART_E_NO_ERR = 0,
  /* Parity error */
  UART_E_PARITY_ERR,
  /* Frame error */
  UART_E_FRAME_ERR,
  /* RXFIFO overflow error */
  UART_E_RXFIFO_OVERFLOW,
  /* Insufficient buffer error */
  UART_E_INSUFFICIENT_BUFSIZE
} Uart_ErrorIdType;

/* [cover parentID={606E387E-7A78-44e0-8626-CEB0A3D8A452}] */
/*  [/cover] */
/*
Type: Uart_ReturnType
This type specifies whether a given API(read/write) was called without
any errors for a given channel or not or the channel was busy was with
some other(read/write) operation on the same channel
*/
typedef enum
{
  /* API execute without error */
  UART_E_OK = 0,
  /* API execute with error */
  UART_E_NOT_OK,
  /* UART channel is busy in same operation which is requested by API. */
  UART_E_BUSY
} Uart_ReturnType;

/* [cover parentID={D9C23B7F-8AB7-4d46-A351-41E039BEE6D7}] */
/*  [/cover] */
/*
Type: Uart_StatusType
This type definition specifies the Status of the particular
channel at the time of request.
*/
typedef enum
{
  /* Channel in idle state */
  UART_IDLE = 0,
  /* Channel is busy in transmit operation */
  UART_BUSY_TRANSMIT,
    /* Channel is busy in receive operation */
  UART_BUSY_RECEIVE,
  /* Channel is busy in transmit and receive operation */
  UART_BUSY_TRANSMIT_RECEIVE,
} Uart_StatusType;

/* [cover parentID={173D225F-D734-4146-AA8C-8BCB9F6D9E88}] */
/*  [/cover] */
/* Type definition of notification function */
typedef void(*Uart_NotificationPtrType)(Uart_ErrorIdType ErrorId);
/* [cover parentID={9B1AB6C4-EDA1-4d91-9E9C-F4396CC39E66}] */
/*  [/cover] */
/* Type definition of Streaming notification function */
typedef void(*Uart_Streaming_NotificationPtrType)(Uart_ErrorIdType ErrorId,Uart_SizeType RxDataSize);
/* [cover parentID={FF2A2D9D-B285-4585-A66B-1F1E2022B572}] */
/*  [/cover] */
/*
Type: UartNotifType
This type definition contains the Call back function pointers
which would be called after completion of a particular Operation
*/
typedef struct
{
  Uart_NotificationPtrType UartTransmitNotifPtr;
  Uart_NotificationPtrType UartReceiveNotifPtr;
  Uart_NotificationPtrType UartAbortTransmitNotifPtr;
  Uart_NotificationPtrType UartAbortReceiveNotifPtr;
  Uart_Streaming_NotificationPtrType UartStreamingNotifPtr;
} Uart_NotifType;

/* [cover parentID={E2A1C613-9230-43fd-996D-AE03DBE87C96}] */
/*  [/cover] */
/*
Type: Uart_ConfigType
This type definition holds complete
configuration data needed for a channel
*/
typedef struct
{
  /* Structure containing call-back function pointers */
  Uart_NotifType UartNotif;
  /* Channel baud rate numerator */
  uint16 ChanBaudRateNumerator;
  /* Channel baud rate denominator */
  uint16 ChanBaudRateDenominator;
  /* Channel baud rate prescalar */
  uint16 ChanBaudRatePrescalar;
  /* Channel oversampling */
  uint8 ChanOversampling;
  /* Hardware channel id */
  uint8 HwModule;
  /* Number of stop Bits */
  uint8 StopBits;
  /* Frame length */
  uint8 DataLength;
  /* Alternate Receive pin */
  uint8 RxPin;
  /* Identifies the parity is enabled */
  uint8 ParityEnable;
  /* Identifies the parity is even or odd */
  uint8 Parity;
  /* Alternate CTS pin */
  uint8 CTSPin;
  /* Identifies the CTS is enabled*/
  uint8 CtsEnable;
  /* Identifies the RTS/CTS polarity if CTS is enabled*/
  uint8 CtsPolarity;
  /* Identifies the receive operation mode polling/interrupt */
  uint8 RxMode;
  /* Identifies the transmit operation mode polling/interrupt */
  uint8 TxMode;
} Uart_ChannelConfigType;

/* [cover parentID={8D5ED691-B86F-44bd-968F-F232A611B329}] */
/*  [/cover] */
/*
Type: Uart_ConfigType
This type definition holds the Uart driver configuration data
*/
typedef struct
{
  /* Pointer to channel communication */
  const Uart_ChannelConfigType *ChannelConfigPtr;
  /* Pointer to channel lookup */
  const uint8 *Uart_ChannelIdLookupPtr;
  /* Number of channels configured */
  uint8 NoOfChannels;
} Uart_ConfigType;

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/

/*Memory Map of the UART Code*/
#define UART_START_SEC_CODE_ASIL_B_LOCAL
/* [cover parentID={84FCEDA9-01F7-4f48-AC8B-47FFAF8417E4}] */
/*  [/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Uart_MemMap.h"

/*******************************************************************************
** Syntax : void Uart_Init(const Uart_ConfigType *const ConfigPtr )           **
**                                                                            **
** Service ID      : 215                                                      **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non reentrant                                            **
**                                                                            **
** Parameters (in) : ConfigPtr - Pointer to Uart driver configuration set     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : Uart driver Initialization function. Function initialize **
**                   all Uart configured channels.                            **
*******************************************************************************/
extern void Uart_Init(const Uart_ConfigType *const ConfigPtr);

/*******************************************************************************
** Syntax          : void Uart_DeInit(void)                                   **
** Service ID      : 222                                                      **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non reentrant                                            **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : Uart driver deInitialization function.                   **
*******************************************************************************/
#if (UART_DEINIT_API == STD_ON)
extern void Uart_DeInit(void);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Uart_DeInit(void)  (ERROR_Uart_DeInit_API_IS_NOT_SELECTED)
#endif

/*******************************************************************************
** Syntax : Uart_ReturnType Uart_Read                                         **
**  (                                                                         **
**    const Uart_ChannelIdType channel,Uart_MemType *const MemPtr,            **
**                                                   const Uart_SizeType Size **
**  )                                                                         **
**                                                                            **
** Service ID      : 217                                                      **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Reentrant(Not for same channel)                          **
**                                                                            **
** Parameters (in) : Channel - Uart channel to be addressed.                  **
**                   MemPtr - Memory location where data needs to be stored   **
**                   Size -Number of data bytes to be received. If channel    **
**                         frame length configured with greater than 8 bit    **
**                         then number of bytes should be multiple of 2.      **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : UART_E_OK - Read operation was initiated successfully    **
**                   UART_E_NOT_OK - Read operation couldn't be initiated     **
**                   due to development errors                                **
**                   UART_E_BUSY - Uart channel is busy with other            **
**                   read operation                                           **
**                                                                            **
** Description     : Api to configure the given UART Channel for reception    **
**                   of the specified number of data bytes and the memory     **
**                   location to be used to store the received data           **
*******************************************************************************/
extern Uart_ReturnType Uart_Read(const Uart_ChannelIdType Channel, \
                                 Uart_MemType *const MemPtr, \
                                 const Uart_SizeType Size);

/*******************************************************************************
** Syntax : Uart_ReturnType Uart_Write                                        **
**  (                                                                         **
**    const Uart_ChannelIdType channel,Uart_MemType *const MemPtr,            **
**    const Uart_SizeType Size                                                **
**  )                                                                         **
**                                                                            **
** Service ID      : 218                                                      **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Reentrant(Not for the same channel)                      **
**                                                                            **
** Parameters (in) : Channel -Uart channel to be addressed                    **
**                   MemPtr -Pointer to buffer from where data to be transmit **
**                   Size -Number of data bytes to be transmitted.If channel  **
**                         frame length configured with greater than 8 bit    **
**                         then number of bytes should be multiple of 2.      **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : UART_E_OK - Write operation initialized successfully     **
**                   UART_E_NOT_OK -Write operation couldn't performed due to **
**                                 development error.                         **
**                   UART_E_BUSY - Uart channel is busy in other transmit     **
**                                 operation                                  **
**                                                                            **
** Description     : Function to transmit data from user memory location      **
**                   (App Buffer)on to the given channel                      **
**                                                                            **
*******************************************************************************/
extern Uart_ReturnType Uart_Write(const Uart_ChannelIdType Channel, \
                                  Uart_MemType *const MemPtr, \
                                  const Uart_SizeType Size);
/*******************************************************************************
** Syntax : Uart_SizeType Uart_AbortRead(Uart_ChannelIdType Channel)          **
**                                                                            **
** Service ID      : 220                                                      **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant  (Not for the same channel)                    **
**                                                                            **
** Parameters (in) : Channel - Uart channel to be addressed                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : UartRetSize - Number of bytes successfully received and  **
**                                 stored to the application memory location  **
**                                 before the read operation was aborted.     **
** Description     : API to abort read operation on given channel.            **
**                                                                            **
*******************************************************************************/
#if (UART_ABORT_READ_API == STD_ON)
extern Uart_SizeType Uart_AbortRead(const Uart_ChannelIdType Channel);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Uart_AbortRead(Channel)  (ERROR_Uart_AbortRead_API_IS_NOT_SELECTED)
#endif

/*******************************************************************************
** Syntax : Uart_ReturnType Uart_StartStreaming                               **
**  (                                                                         **
**    const Uart_ChannelIdType channel,Uart_MemType *const MemPtr,            **
**                                                const Uart_SizeType BufSize **
**  )                                                                         **
**                                                                            **
** Service ID      : 229                                                      **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Reentrant(Not for same channel)                          **
**                                                                            **
** Parameters (in) : Channel - Uart channel to be addressed.                  **
**                   MemPtr - Memory location where data needs to be stored   **
**                   BufSize -Application buffer length in Bytes.If channel   **
**                         frame length configured with greater than 8 bit    **
**                         then buffer length should be multiple of 2.        **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : UART_E_OK - Read operation was initiated successfully    **
**                   UART_E_NOT_OK - Read operation couldn't be initiated     **
**                   due to development errors                                **
**                   UART_E_BUSY - Uart channel is busy with other            **
**                   read operation                                           **
**                                                                            **
** Description     : Api to configure the given UART Channel for reception    **
**                   of the specified number of data bytes and the memory     **
**                   location to be used to store the received data           **
*******************************************************************************/
#if (UART_RECEIVE_STREAMING_MODE_API == STD_ON)
extern Uart_ReturnType Uart_StartStreaming(const Uart_ChannelIdType Channel, \
                          Uart_MemType *const MemPtr, \
                          const Uart_SizeType BufSize);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Uart_StartStreaming(Channel,MemPtr,BufSize) (ERROR_Uart_StartStreaming_API_IS_NOT_SELECTED)
#endif

/*******************************************************************************
** Syntax:Uart_ReturnType Uart_StopStreaming(const Uart_ChannelIdType Channel)**
**                                                                            **
** Service ID      : 230                                                      **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant  (Not for the same channel)                    **
**                                                                            **
** Parameters (in) : Channel - Uart channel to be addressed                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : UART_E_OK - Stop streaming was initiated successfully    **
**                   UART_E_NOT_OK - Stop streaming couldn't be initiated     **
**                   due to development errors                                **
** Description     : API to stop streaming operation on given channel.        **
**                                                                            **
*******************************************************************************/
#if (UART_RECEIVE_STREAMING_MODE_API == STD_ON)
extern Uart_ReturnType Uart_StopStreaming(const Uart_ChannelIdType Channel);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Uart_StopStreaming(Channel) (ERROR_Uart_StopStreaming_API_IS_NOT_SELECTED)
#endif
/*******************************************************************************
** Syntax : Uart_SizeType Uart_AbortWrite( Uart_ChannelIdType Channel )       **
**                                                                            **
** Service ID      : 219                                                      **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant(Not for the same channel)                      **
**                                                                            **
** Parameters (in) : Channel - Uart channel to be addressed                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : UartRetSize - Number of bytes that have been             **
**                                 successfully transmitted before the write  **
**                                 operation was aborted.                     **
**                                                                            **
** Description     : API to abort data transmission on given channel.         **
                                                                              **
**                                                                            **
*******************************************************************************/
#if (UART_ABORT_WRITE_API == STD_ON)
extern Uart_SizeType Uart_AbortWrite(const Uart_ChannelIdType Channel);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Uart_AbortWrite(Channel)  (ERROR_Uart_AbortWrite_API_IS_NOT_SELECTED)
#endif

/*******************************************************************************
** Syntax: Uart_StatusType Uart_GetStatus(const Uart_ChannelIdType Channel)   **
**                                                                            **
** Service ID      : 221                                                      **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant(Not for the same channel)                      **
**                                                                            **
** Parameters (in) : Channel - Uart channel to be addressed                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :                                                          **
**                   UART_BUSY_TRANSMIT : UART channel busy in transmit       **
**                                                              operation.    **
**                   UART_BUSY_RECEIVE : UART channel busy in receive         **
**                                                                 operation. **
**                   UART_BUSY_TRANSMIT_RECEIVE : UART channel busy in        **
**                                           receive and transmit operation.  **
**                   UART_IDLE : Idle state (no transmits or receive          **
**                               operation in progress).                      **
**                                                                            **
** Description     : API to read an UART channels status.                     **
**                                                                            **
*******************************************************************************/
extern Uart_StatusType Uart_GetStatus(const Uart_ChannelIdType Channel);

#if(UART_RX_MODE != UART_POLLING_MODE)
/*******************************************************************************
** Syntax          : void Uart_IsrReceive( const uint8 HwUnit)                **
**                                                                            **
** Service ID      : 227                                                      **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Reentrant(Not for the same HW Unit)                      **
**                                                                            **
** Parameters (in) : HwUnit : ASCLIN channel number.                          **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value    : none                                                     **
**                                                                            **
** Description     : IRQ handler for RXFIFO level interrupts.                 **
*******************************************************************************/
extern void Uart_IsrReceive(const uint8 HwUnit);
#endif

#if(UART_TX_MODE != UART_POLLING_MODE)
/*******************************************************************************
** Syntax          : void Uart_IsrTransmit(const uint8 HwUnit)                **
**                                                                            **
** Service ID      : 228                                                      **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Reentrant(Not for the same HW Unit)                      **
**                                                                            **
** Parameters (in) : HwUnit : ASCLIN channel number.                          **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value    : none                                                     **
**                                                                            **
** Description     : IRQ handler for TXFIFO level interrupts.                 **
**                                                                            **
*******************************************************************************/
extern void Uart_IsrTransmit(const uint8 HwUnit);
#endif

#if((UART_TX_MODE != UART_POLLING_MODE)||(UART_RX_MODE != UART_POLLING_MODE))
/*******************************************************************************
** Syntax : void Uart_IsrError( const uint8  HwUnit)                          **
**                                                                            **
** Service ID      : 226                                                      **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Reentrant  (Not for the same HW Unit)                    **
**                                                                            **
** Parameters (in) : HwUnit : ASCLIN channel number.                          **
**                                                                            **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value    : none                                                     **
**                                                                            **
** Description     : IRQ handler for error occurred during reception and      **
**                   handle transmit complete interrupt.                      **
*******************************************************************************/
extern void Uart_IsrError(const uint8 HwUnit);
#endif



#if(UART_INIT_CHECK_API == STD_ON)
/*******************************************************************************
** Syntax : void Uart_InitCheck(const Uart_ConfigType *const ConfigPtr )      **
** Service ID      : 216                                                      **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non reentrant                                            **
**                                                                            **
** Parameters (in) : ConfigPtr - Pointer to Uart driver configuration set     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : Uart Module Initialization check function.Initialization **
**                   check function which verify variables and register's of  **
**                   Uart module and log error(in case missmatch).            **
*******************************************************************************/
extern Std_ReturnType Uart_InitCheck(const Uart_ConfigType *const ConfigPtr);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Uart_InitCheck(ConfigPtr)  (ERROR_Uart_InitCheck_API_IS_NOT_SELECTED)
#endif

#if(UART_VERSION_INFO_API == STD_ON)
/*******************************************************************************
**                                                                            **
** Syntax           : void Uart_GetVersionInfo                                **
**                    (                                                       **
**                      Std_VersionInfoType *const versioninfo                **
**                    )                                                       **
**                                                                            **
** Description      : This API returns the version information of this module **
**                    Note: API is available only when UartVersionInfoApi     **
**                    is configured as true.                                  **
**                                                                            **
** Service ID       : 223                                                     **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : none                                                    **
**                                                                            **
** Parameters (out) : versioninfo -  Pointer to where to store the version    **
**                    information of this module                              **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
*******************************************************************************/
extern void Uart_GetVersionInfo(Std_VersionInfoType *const VersionInfoPtr);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Uart_GetVersionInfo(VersionInfoPtr) \
                                      (ERROR_Uart_GetVersionInfo_API_IS_NOT_SELECTED)
#endif

#define UART_STOP_SEC_CODE_ASIL_B_LOCAL
/* [cover parentID={84FCEDA9-01F7-4f48-AC8B-47FFAF8417E4}] */
/*  [/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Uart_MemMap.h"

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Uart_PBcfg.h"
#endif
