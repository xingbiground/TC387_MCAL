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
**  FILENAME     : Sent_Types.h                                               **
**                                                                            **
**  VERSION      : 4.0.0                                                      **
**                                                                            **
**  DATE         : 2019-06-21                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : SENT Driver Local header definition file typedefs required **
**                                          for SENT Module                   **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef SENT_TYPES_H
#define SENT_TYPES_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/* Inclusion of Platform_Types.h and Compiler.h */
#include "Std_Types.h"

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/* Value for ACCEN types */
#define SENT_ACCEN_DEFAULT        0U
#define SENT_ACCEN_INIT           1U
#define SENT_ACCEN_API            2U

/* SRN to SENT logical channel not mapped */
#define SENT_CHANNEL_NOT_MAPPED   255U
/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
/* Type definition for Channel Ids */
typedef uint8 Sent_ChannelIdxType;


/* Type definition for SENT Event/s to be notified */
typedef uint32 Sent_NotifType;

/* Type definition for Channel enable/disable operations */
typedef enum
{
  SENT_DISABLE        = 0x00U,
  SENT_ENABLE         = 0x01U,
} Sent_ChanOpType;

/* Type definition for SENT Application notification function pointer */
typedef void (*Sent_NotifFnPtrType) (Sent_ChannelIdxType ChannelId,
                                     Sent_NotifType Stat);

/*
  Structure definition for a SENT channel configuration
*/
typedef struct
{
  /* SENT_RCRx register value */
  uint32          ChanRxCtrl;
  /* SENT_IOCRx register value */
  uint32          ChanIOCtrl;
  /* SENT_VIEWx register value */
  uint32          ChanDataView;
  /* SENT_CPDRx register value */
  uint16          ChanPreDiv;
  /* SENT_CFDRx register value */
  uint16          ChanFracDiv;
  /* Frame length */
  uint8           ChanFrameLen;
  /* Physical Channel Id  */
  Sent_ChannelIdxType  ChanId;
  /* Callback function*/
  Sent_NotifFnPtrType CallbackFn;
  /*Interrupt node */
  uint8 Sent_InterruptNode;

} Sent_ChannelCfgType;

/* Structure defination for the core */
typedef struct
{
  /* No of channels */
  Sent_ChannelIdxType          MaxChannels;
  /* Sent Channel Configuration */
  const  Sent_ChannelCfgType *Sent_ChannelConfig;
} Sent_CoreConfigType;



/* Structure definition to receive serial data */
typedef struct
{
  /* 16-bit serial data */
  uint16    Data;
  /* 4/8-bit Message Id */
  uint8     MsgId;
  /* CRC of the serial data */
  uint8     Crc;
  /* Configuration bit */
  uint8     Configuration;
} Sent_RxSerialDataType;

/* Enumeration to depict Channel state */
typedef enum
{
  SENT_STOP = 0x00U,
  SENT_INITIALIZED = 0x1U,
  SENT_RUNNING = 0x2U,
  SENT_SYNCHRONIZED = 0x3U
}Sent_ChanStateType;

/* Structure definition for Channel Status */
typedef struct
{
  /* Channel state */
  Sent_ChanStateType  ChanStat;
  /* Timestamp of the last received SENT frame */
  uint32              RxTimeStamp;
  /* Interrupt Status bitmap */
  uint32              IntStat;
  /* CRC of the last received SENT frame */
  uint8               RxCrc;
  /* Status and Comm Nibble of the last received SENT frame */
  uint8               StatCommNibble;
} Sent_ChanStatusType;

/* Structure definition for the Glitch filter status */
typedef struct
{
  /* Rising Edge Glitch Flag Status */
  uint8         RisingEdge;
  /* Falling Edge Glitch Flag Status */
  uint8         FallingEdge;
} Sent_GlitchStatusType;

typedef struct
{
  /* Mapping of the core and channels - Store the core number of each channel
   * here. Searching becomes easy with this. */
  uint8 Sent_ChannelCore;
  /* Mapping of the channels and config index - Store the index of the
   * configuration where the channel information is kept. */
  Sent_ChannelIdxType Sent_ChannelIndex;
} Sent_ChannelMapType;

#endif /* SENT_TYPES_H */
