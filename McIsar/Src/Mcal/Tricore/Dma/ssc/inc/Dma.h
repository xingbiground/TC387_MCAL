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
**  FILENAME     : Dma.h                                                      **
**                                                                            **
**  VERSION      : 15.0.0                                                     **
**                                                                            **
**  DATE         : 2021-09-30                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Dma Driver header definition file                          **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

#ifndef DMA_H
#define DMA_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/*[cover parentID={F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}][/cover]*/
/* Inclusion of McalLib.h and Std_Types.h */
#include "McalLib.h"
#include "Std_Types.h"

/* Inclusion of configuration file */
#include "Dma_Cfg.h"

/* [cover parentID= {302796C3-9B51-414f-889F-51DFED9FEAAA}]
DMA Header file
[/cover] */

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/* Vendor ID */
#define DMA_VENDOR_ID                                   ((uint16)17U)

/* DMA Module ID - 255 */
#define DMA_MODULE_ID                                   ((uint16)255U)

/* DMA Module Instance 0 */
#define DMA_MODULE_INSTANCE                             ((uint8)0U)

/****************************Service ID's****************************/
#define DMA_SID_INIT                                    ((uint8)0x01U)
#define DMA_SID_ISINITDONE                              ((uint8)0x02U)
#define DMA_SID_CHINIT                                  ((uint8)0x03U)
#define DMA_SID_CHUPDATE                                ((uint8)0x04U)
#define DMA_SID_CHDEINIT                                ((uint8)0x05U)
#define DMA_SID_CHTRANSFERFREEZE                        ((uint8)0x06U)
#define DMA_SID_CHTRANSFERRESUME                        ((uint8)0x07U)
#define DMA_SID_CHENABLEHARDWARETRIGGER                 ((uint8)0x08U)
#define DMA_SID_CHDISABLEHARDWARETRIGGER                ((uint8)0x09U)
#define DMA_SID_CHSTARTTRANSFER                         ((uint8)0x0AU)
#define DMA_SID_CHSTOPTRANSFER                          ((uint8)0x0BU)
#define DMA_SID_CHGETREMAININGDATA                      ((uint8)0x0CU)
#define DMA_SID_CHSWITCHBUFFER                          ((uint8)0x0DU)
#define DMA_SID_GETEVENTS                               ((uint8)0x0EU)
#define DMA_SID_CHSTATUSCLEAR                           ((uint8)0x0FU)
#define DMA_SID_CHINTERRUPTENABLE                       ((uint8)0x10U)
#define DMA_SID_CHINTERRUPTDISABLE                      ((uint8)0x11U)
#define DMA_SID_CHGETVERSIONINFO                        ((uint8)0x12U)
#define DMA_SID_MESTATUSCLEAR                           ((uint8)0x13U)
#define DMA_SID_INITCHECK                               ((uint8)0x14U)
#define DMA_SID_GETCRCVALUE                             ((uint8)0x15U)
#define DMA_SID_GETTIMESTAMP                            ((uint8)0x16U)
#define DMA_SID_ISCHINITDONE                            ((uint8)0x17U)
#define DMA_SID_DEINIT                                  ((uint8)0x18U)
#define DMA_SID_SETPATTERN                              ((uint8)0x19U)
#define DMA_SID_CHINTERRUPTHANDLER                      ((uint8)0xF3U)
#define DMA_SID_MEINTERRUPTDISPATCHER                   ((uint8)0xF4U)

/********************************************************************/

#if ( (DMA_DEV_ERROR_DETECT == STD_ON) || (DMA_SAFETY_ENABLE == STD_ON) )
/****************************DET Error ID***************************/
#define DMA_E_DRIVER_NOT_INITIALIZED                    ((uint8)0x01)
#define DMA_E_CHANNEL_NOT_INITIALIZED                   ((uint8)0x02)
#define DMA_E_CHANNEL_INVALID_ID                        ((uint8)0x03)
#define DMA_E_CHANNEL_INVALID_EVENT                     ((uint8)0x04)
#define DMA_E_NULL_POINTER                              ((uint8)0x05)
#define DMA_E_FREEZE_STATE                              ((uint8)0x06)
#define DMA_E_NO_TRANSFERS_PENDING                      ((uint8)0x07)
#define DMA_E_NOT_IN_FREEZE_STATE                       ((uint8)0x08)
#define DMA_E_DATA_TRANSFER_IN_PROGRESS                 ((uint8)0x09)
#define DMA_E_ALREADY_INITIALIZED                       ((uint8)0x0A)
#define DMA_E_CH_ALREADY_INITIALIZED                    ((uint8)0x0B)
#define DMA_E_TIMEOUT                                   ((uint8)0x0C)
#define DMA_E_CHANNEL_INVALID_SWITCH_REQ                ((uint8)0x0D)
#define DMA_E_INVALID_SHADOW_CONFIG_REQ                 ((uint8)0x0E)
#define DMA_E_INVALID_CRC_TYPE_REQ                      ((uint8)0x0F)
#define DMA_E_CRC_NOT_SUPPORTED                         ((uint8)0x10)
#define DMA_E_MOVE_ENGINE_INVALID_ID                    ((uint8)0x11)
#define DMA_E_CH_NO_NOTIFICATION_CONFIGURED             ((uint8)0x12)
#define DMA_E_CHANNEL_INVALID_START_REQ                 ((uint8)0x13)
#define DMA_E_CH_PATTERN_INVALID_REQ                    ((uint8)0x14)
#define DMA_E_ERR_INT_PLAUSIBILITY                      ((uint8)0x15)
#define DMA_E_CH_INT_PLAUSIBILITY                       ((uint8)0x16)


/* MultiCore errors */
#define DMA_E_CORE_NOT_CONFIGURED                       ((uint8)0x64)
#define DMA_E_CORE_CHANNEL_MISMATCH                     ((uint8)0x65)
#define DMA_E_MASTER_UNINIT                             ((uint8)0x66)
#define DMA_E_SLAVE_INIT                                ((uint8)0x67)

/* Safety errors */
/* *** None *** */

/********************************************************************/
#endif

#define DMA_MAX_TRLCHANNELS ((uint8)(((DMA_MAX_NUM_OF_CHANNELS - 1u)/32u) + 1u))


/*********************************************************************/
/* Type definition for Dma_EventsType*/
typedef enum
{
  DMA_EVENT_NONE                      = 0,
  DMA_EVENT_CH_RUNNING                = 1,
  DMA_EVENT_CH_TRANSFER_COMPLETE      = 2,
  DMA_EVENT_CH_BUFFER_WRAP_SOURCE     = 4,
  DMA_EVENT_CH_BUFFER_WRAP_DEST       = 8,
  DMA_EVENT_CH_UNKNOWN_EVENT          = 16,
  DMA_EVENT_CH_TRL_ERROR              = 32,
  DMA_EVENT_CH_PATTERN_DETECTION      = 64,
  DMA_EVENT_ME_SOURCE_ERROR           = 128,
  DMA_EVENT_ME_DESTINATION_ERROR      = 256,
  DMA_EVENT_ME_SPB_ERROR              = 512,
  DMA_EVENT_ME_SRI_ERROR              = 1024,
  DMA_EVENT_ME_RAM_ERROR              = 2048,
  DMA_EVENT_ME_SAFE_LINKEDLIST_ERROR  = 4096,
  DMA_EVENT_ME_DMA_LINKEDLIST_ERROR   = 8192
} Dma_EventsType;
/* [cover parentID={67331F88-E6FB-47df-A9D1-1D1E91FBE4E5}]
Events type
[/cover] */

/* Type definition for Dma_CrcType */
typedef enum
{
  DMA_NO_CRC_TYPE = 0,
  DMA_DATA_CRC_TYPE = 1,
  DMA_ADDRESS_CRC_TYPE = 2
} Dma_CrcType;
/* [cover parentID={F51D5CEA-B99E-4bc5-B780-20209C5F7265}]
CRC Type
[/cover] */


/* Type definition for Dma_CrcType */
typedef enum
{
  DMA_ME_NONE = 0,
  DMA_ME_0 = 1,
  DMA_ME_1 = 2,
  DMA_ME_ALL = 4
} Dma_MoveEngineListType;
/* [cover parentID={84806724-503C-49ce-9213-188AE20B464C}]
ME List type
[/cover] */


/* Type definition for Dma_MoveEngineErrorNotificationPtrType*/
typedef void (*Dma_MoveEngineErrorNotificationPtrType)(uint8 Channel,\
                                                       uint32 Event);
/* [cover parentID={50A7B890-FF09-433a-9C75-97E65C89467C}]
Error notification Type
[/cover] */


/* Type definition for Dma_ChannelNotificationPtrType */
typedef void (*Dma_ChannelNotificationPtrType)(uint8 Channel,\
                                               uint32 Event);
/* [cover parentID={3687A5D2-547F-4ace-B6D8-DA563747CAA2}]
Channel notification pointer
[/cover] */


/* Forward declaration of Dma_TransactionCtrlSetType */
struct Dma_TransactionCtrlSetType;

/* Type definition for Dma_TransactionCtrlSetType */
/* if linked list is enabled then this will represent a full DMA TCS of 8
 * registers.
 */
/**! The following structure holds the transaction control set register values
 * of a particular DMA channel. */
typedef struct
{
  #if (DMA_LINKED_LIST_ENABLE == STD_ON)
  uint32  DmaReadDataCrc;             /* RDCRC register */
  uint32  DmaSourceDestAddressCrc;/* SDCRC register */
  #endif
  uint32 *DmaSourceAddress;           /* SADR register */
  uint32 *DmaDestinationAddress;      /* DADR register */
  uint32  DmaAddressInterruptControl; /* ADICR register */
  uint32  DmaChannelConfig;           /* CHCFGR register */
  #if ((DMA_LINKED_LIST_ENABLE    == STD_ON) || \
  (DMA_DOUBLE_BUFFER_ENABLE  == STD_ON))
  const struct Dma_TransactionCtrlSetType* DmaShadowAddress; /* SHADR reg */
  #endif
  #if (DMA_LINKED_LIST_ENABLE == STD_ON)
  uint32  DmaChControlStatus;         /* CHCSR register */
  #endif
} Dma_TransactionCtrlSetType;
/* [cover parentID={2AA1536A-9B92-42f4-ADE4-26CD08704E7A}]
Dma_TransactionCtrlSetType
[/cover] */

/* Type definition for Dma_ChConfigType */
/**! The following structure holds the configuration of a particular DMA
 * channel. */
typedef struct
{
  const Dma_TransactionCtrlSetType*   DmaChTCSPtr;   /* Pointer to TCS list */
  Dma_ChannelNotificationPtrType      DmaChNotifPtr; /* Channel Notification*/
  uint32 DmaTsrConfig;    /* TSR register configuration */
  uint8 DmaChNumber;  /* Dma Channel Id */
  uint8 DmaChHwPartitionConfig; /* Access partition configuration */
  Dma_MoveEngineErrorNotificationPtrType DmaMEErrorNotifPtr; /*ME Err Notif*/
} Dma_ChConfigType;
/* [cover parentID={90CEBB91-8682-4404-888C-AA56D178CAD7}]
Dma_ChConfigType
[/cover] */

/* Type definition for Dma_ResourcePartitionConfigType */
typedef struct
{
  /*Masters allowed to access partition*/
  uint32 DmaHwResourceBusMasterAccess[4];

  /* Access mode to access partition */
  uint8 DmaHwResourceMode[4];
} Dma_ResourcePartitionConfigType;
/* [cover parentID={78EA4572-D5F1-4810-8489-E34E043F6EBA}]
Dma_ResourcePartitionConfigType
[/cover] */

/* [cover parentID={5E742C47-CDE2-4e4a-833D-05D1396C5D4D}]
ConfigType
[/cover] */
typedef struct
{
  /* Pointer to channel config list */
  const Dma_ChConfigType* DmaChConfigPtr;

  /* Number of DMA channel configured */
  uint8  DmaNumberofChConfiguredPerCore;
} Dma_CoreSpecificChConfigType;


/* This structure holds the mapping data of the channel to the core
 * and the configuration index */
typedef struct
{
  /* Mapping of the channels and config index - Store the index of the
   * configuration where the channel information is kept. */
  uint8 Dma_ChannelConfIndexMap;

  /* Mapping of the core and channels - Store the core number of each channel
   * here. Searching becomes easy with this. */
  uint8 Dma_ChannelCoreMap;
} Dma_ChannelMapType;

/* [cover parentID={D6999E96-51E3-42bd-B592-D8EB72DB238D}]
Dma_ChannelMapType
[/cover] */


/* Type definition for Dma_ConfigType */
/**! This is the master structure which is being passed to the init
 * function for the initial configurations. */
typedef struct
{
  /* Pointers to the core specific init configurations. The cores should
   * access only their respective structures */
  const Dma_CoreSpecificChConfigType* DmaCoreConfigPtr[MCAL_NO_OF_CORES];

  /* MoveEngine error configuration - Holds the different errors which can
   * be triggered from the Move Engines */
  uint32 DmaMovEngErr[2];
  
  #if (DMA_SETPATTERN_API == STD_ON)
  /* Dma pattern configuration - Holds different pattern for matching */
  uint32 DmaPattern[2];
  
  /* Dma pattern channel configuration - Holds different channel for pattern matching */
  uint32 DmaPatternCh[2];
  #endif
  
  /* DMA resource partition configuration - for access enable/disable and
   * user/supervisor bus access configuration */
  Dma_ResourcePartitionConfigType DmaHwResourcePartition;

  /* The channel mapping to the core and config index */
  Dma_ChannelMapType Dma_ChannelMaps[DMA_MAX_NUM_OF_CHANNELS];

  /* The list of channels with TRL enabled */
  uint32 DmaChTrlEnabled[DMA_MAX_TRLCHANNELS];

  /* Total number of DMA channel configured */
  uint8  DmaTotalChConfigured;
} Dma_ConfigType;


/* [cover parentID={F869B1A3-76D8-4c22-AF9C-74B07CD58E04}]
ConfigType
[/cover] */
/* [cover parentID={90682D65-35B5-489b-A2FB-AC64E3297894}]
ConfigType
[/cover] */

/**! Dma_ConfigUpdateType contains the elements which are needed in updating
 * the channel settings of an already configured channel.  */
/* [cover parentID={3DEF54E2-A783-422a-934F-6C3A87B0FE0C}]
Config update type
[/cover] */
typedef struct
{
  uint32  SourceAddress;          /* Source address, contents of SADR */
  uint32  DestAddress;            /* Destination address, contents of DADR */
  uint32  ControlAdicr;           /* Contents of ADICR */
  uint32  ControlChcsr;           /* Contents of CHCSR */
  uint32  Config;                 /* Contents of CHCFGR */
  uint32  ShadowConfig;           /* Contents of SHADR */
  uint32  AddressCrc;             /* Contents of SDCRC register */
  uint32  DataCrc;                /* Contents of RDCRC register */
  /* Should Source address be updated? */
  unsigned_int   UpdateSourceAddress: 1;
  /* Should Destination address be updated?*/
  unsigned_int   UpdateDestAddress: 1;
  /* Should ADICR be updated? */
  unsigned_int   UpdateControlAdicr: 1;
  /* Should CHCSR be updated? */
  unsigned_int   UpdateControlChcsr: 1;
  /* Should CHCFG be updated? */
  unsigned_int   UpdateConfig: 1;
  /* Should SHADR be updated? */
  unsigned_int   UpdateShadowConfig: 1;
  /* Should SDCRC be updated? (needed in case of safeLinkedList) */
  unsigned_int   UpdateAddressCrc: 1;
  /* Should RDCRC be updated? (needed in case of safeLinkedList) */
  unsigned_int   UpdateDataCrc: 1;
} Dma_ConfigUpdateType;


/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/
#define DMA_START_SEC_CODE_ASIL_B_GLOBAL

#include "Dma_MemMap.h"

/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax : extern void Dma_Init(const Dma_ConfigType *ConfigPtr)             **
**                                                                            **
** Description : Service for DMA initialization. This function initializes    **
**               all DMA move engine registers as well as registers of        **
**               configured channels, with the values of the structure        **
**               referenced by the parameter ConfigPtr.                       **
**               This function should be called before calling any other      **
**               Dma API                                                      **
**                                                                            **
** Service ID:  0x01                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  ConfigPtr - Pointer to DMA Driver configuration set     **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
extern void Dma_Init
(
  const Dma_ConfigType* const ConfigPtr
);

#if (DMA_DEINIT_API == STD_ON)
/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax : void Dma_DeInit(void)                                             **
**                                                                            **
** Description : Service for DMA deinitialization. This function deinitializes**
**               all DMA move engine registers as well as registers of        **
**               configured channels, with their reset value.                 **
**                                                                            **
** Service ID:  0x18                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
extern void Dma_DeInit(void) ;
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'Dma_DeInit' defined. No side effects foreseen by
 * violating this MISRA rule. */
#define Dma_DeInit()       (ERROR_Dma_DeInit_API_IS_NOT_SELECTED)
#endif

#if(DMA_INITCHECK_API == STD_ON)
/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax           : Std_ReturnType Dma_InitCheck (const Dma_ConfigType*     **
**                    const ConfigPtr)                                        **
**                                                                            **
** Description      : This API can be used to check the whether the           **
**                    initialization happened correctly for the DMA driver.   **
**                    The basic idea is to check whether the variables        **
**                    and the SFRs which were initialized are holding the     **
**                    same values that they were initialized with.            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x16                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non Re-entrant                                          **
**                                                                            **
** Parameters(in)   : ConfigPtr - Pointer to the DMA configuration for        **
**                                  initialization                            **
**                                                                            **
** Parameters (out) : none                                                    **
**                                                                            **
** Return value     : E_OK - Operation successfully performed                 **
**                    E_NOT_OK - Operation failed                             **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Dma_InitCheck
(
  const Dma_ConfigType* const ConfigPtr
);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'Dma_InitCheck' defined. No side effects foreseen by
 * violating this MISRA rule. */
#define Dma_InitCheck(ConfigPtr)       (ERROR_Dma_InitCheck_API_IS_NOT_SELECTED)
#endif

/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax : extern Std_ReturnType Dma_IsInitDone(void)                        **
**                                                                            **
** Description : Service to check if the DMA is initial                       **
**                                                                            **
** Service ID:  0x02                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant                                                     **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :   DMA driver state.                                      **
**                     E_OK  - DMA is initialized                             **
**                     E_NOT_OK - DMA is not initialized                      **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Dma_IsInitDone
(
  void
);
/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax : extern void Dma_ChInit(uint8 Channel)                             **
**                                                                            **
** Description : Service for channel initialization with parameters defined   **
**               in DMAChannelTransactionSet container.                       **
**                                                                            **
** Service ID:  0x03                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant for different CPU core                              **
**                                                                            **
** Parameters (in) :  Channel - DMA channel ID(0-127)                         **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
extern void Dma_ChInit
(
  const uint8 Channel
);

/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax : extern void Dma_ChUpdate (uint8 Channel, Dma_ConfigUpdateType     **
**                                   *Config, uint32 * NodeAddress)           **
**                                                                            **
** Description : Service for channel initialization with parameters provided  **
**               by the user                                                  **
**                                                                            **
** Service ID:  0x04                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant for different CPU core                              **
**                                                                            **
** Parameters (in) : Channel - DMA channel ID(0-127)                          **
**                   Dma_ConfigUpdateType - Channel update structure with     **
**                   channel configuration updated                            **
**                   NodeAddress - Start of a memory block which must be      **
**                   formatted with information in "Config" object            **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
extern void Dma_ChUpdate
(
  const uint8 Channel,
  const Dma_ConfigUpdateType* const Config,
  const uint32* const NodeAddress
);

#if (DMA_CHDEINIT_API == STD_ON)
/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax : extern void Dma_ChDeInit(uint8 Channel)                           **
**                                                                            **
** Description : Driver channel deinitialization                              **
**               This function will deinitialize the DMA channel registers    **
**                                                                            **
** Service ID:  0x05                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant for different CPU core                              **
**                                                                            **
** Parameters (in) :  Channel - DMA channel ID(0-127)                         **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
extern void Dma_ChDeInit
(
  const uint8 Channel
);

#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'Dma_ChDeInit' defined. No side effects foreseen by
 * violating this MISRA rule. */
#define Dma_ChDeInit(Channel)       (ERROR_Dma_ChDeInit_API_IS_NOT_SELECTED)
#endif

#if (DMA_SUSPEND_API == STD_ON)
/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax : extern void Dma_ChTransferFreeze (uint8 Channel)                  **
**                                                                            **
** Description : Service to halt a channel. This function freezes the         **
**               ongoing channel transaction.                                 **
**                                                                            **
** Service ID:  0x06                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant for different CPU core                              **
**                                                                            **
** Parameters (in) :  Channel - DMA channel ID(0-127)                         **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
extern void Dma_ChTransferFreeze
(
  const uint8 Channel
);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'Dma_ChTransferFreeze' defined. No side effects foreseen by
 * violating this MISRA rule. */
#define Dma_ChTransferFreeze(Channel)   \
                                    (ERROR_Dma_ChTransferFreeze_API_IS_NOT_SELECTED)
#endif

#if (DMA_SUSPEND_API == STD_ON)
/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax : extern void Dma_ChTransferResume(uint8 Channel)                   **
**                                                                            **
** Description : Service to resume a halted channel.                          **
**                                                                            **
** Service ID:  0x07                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant for different CPU core                              **
**                                                                            **
** Parameters (in) :  Channel - DMA channel ID(0-127)                         **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
extern void Dma_ChTransferResume
(
  const uint8 Channel
);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'Dma_ChTransferResume' defined. No side effects foreseen by
 * violating this MISRA rule. */
#define Dma_ChTransferResume(Channel)   \
                                    (ERROR_Dma_ChTransferResume_API_IS_NOT_SELECTED)
#endif

#if (DMA_TRIGGER_API == STD_ON)
/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax : extern void Dma_ChEnableHardwareTrigger(uint8 Channel)            **
**                                                                            **
** Description : Service to enable hardware trigger for the channel           **
**                                                                            **
** Service ID:  0x08                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant for different CPU core                              **
**                                                                            **
** Parameters (in) :  Channel - DMA channel ID(0-127)                         **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
extern void Dma_ChEnableHardwareTrigger
(
  const uint8 Channel
);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'Dma_ChEnableHardwareTrigger' defined. No side effects foreseen by
 * violating this MISRA rule. */
#define Dma_ChEnableHardwareTrigger(Channel)   \
                            (ERROR_Dma_ChEnableHardwareTrigger_API_IS_NOT_SELECTED)
#endif

#if (DMA_TRIGGER_API == STD_ON)
/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax : extern void Dma_ChDisableHardwareTrigger (uint8 Channel)          **
**                                                                            **
** Description : Service to disable hardware trigger for the channel          **
**                                                                            **
** Service ID:  0x09                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant for different CPU core                              **
**                                                                            **
** Parameters (in) :  Channel - DMA channel ID(0-127)                         **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
extern void Dma_ChDisableHardwareTrigger
(
  const uint8 Channel
);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'Dma_ChDisableHardwareTrigger' defined. No side effects foreseen by
 * violating this MISRA rule. */
#define Dma_ChDisableHardwareTrigger(Channel)   \
                            (ERROR_Dma_ChDisableHardwareTrigger_API_IS_NOT_SELECTED)
#endif

/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax : extern void Dma_ChStartTransfer (uint8 Channel)                   **
**                                                                            **
** Description : Service to start the transaction for the channel.            **
**               This function applies software trigger for the DMA transfer  **
**                                                                            **
** Service ID:  0x0A                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant for different CPU core                              **
**                                                                            **
** Parameters (in) :  Channel - DMA channel ID(0-127)                         **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
*******************************************************************************/
extern void Dma_ChStartTransfer
(
  const uint8 Channel
);

/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax : extern void Dma_ChStopTransfer (uint8 Channel)                    **
**                                                                            **
** Description : Service to stop/abort the transaction for the channel.       **
**                                                                            **
** Service ID:  0x0B                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant for different CPU core                              **
**                                                                            **
** Parameters (in) :  Channel - DMA channel ID(0-127)                         **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
extern void Dma_ChStopTransfer
(
  const uint8 Channel
);

#if (DMA_DATA_PENDING_API == STD_ON)
/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax : extern void Dma_ChGetRemainingData (uint8 Channel)                **
**                                                                            **
** Description : Service to get Number of bytes remaining in the transaction  **
**                                                                            **
** Service ID:  0x0C                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant for different CPU core                              **
**                                                                            **
** Parameters (in) :  Channel - DMA channel ID(0-127)                         **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Pending transfer count                                  **
**                                                                            **
*******************************************************************************/
extern uint32 Dma_ChGetRemainingData
(
  const uint8 Channel
);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'Dma_ChGetRemainingData' defined. No side effects foreseen by violating
 * this MISRA rule. */
#define Dma_ChGetRemainingData(Channel) \
                                (ERROR_Dma_ChGetRemainingData_API_IS_NOT_SELECTED)
#endif

#if (DMA_BUFFER_SWITCH_API == STD_ON)
/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax : extern void Dma_ChSwitchBuffer (uint8 Channel)                    **
**                                                                            **
** Description : Service to redirect incoming data stream to the empty buffer **
**               in a double buffering scheme.                                **
**                                                                            **
** Service ID:  0x0D                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant for different CPU core                              **
**                                                                            **
** Parameters (in) :  Channel - DMA channel ID(0-127)                         **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
extern void Dma_ChSwitchBuffer
(
  const uint8 Channel
);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro 'Dma_ChSwitchBuffer'
 * defined. No side effects foreseen by violating this MISRA rule. */
#define Dma_ChSwitchBuffer(Channel) \
                                (ERROR_Dma_ChSwitchBuffer_API_IS_NOT_SELECTED)
#endif

/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax : extern void Dma_ChStatusClear (uint8 Channel,                     **
**                                         Dma_ChEventType Event)             **
**                                                                            **
** Description : Service to clear channel Event                               **
**                                                                            **
** Service ID:  0x0F                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant for different CPU core                              **
**                                                                            **
** Parameters (in) :  Channel - DMA channel ID(0-127)                         **
**                    Event   - Event to be cleared for assertion             **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
extern void Dma_ChStatusClear
(
  const uint8 Channel,
  const Dma_EventsType Event
);

/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax : extern void Dma_ChInterruptEnable (uint8 Channel,                 **
**                                             Dma_ChEventType Event)         **
**                                                                            **
** Description : Service to enable channel interrupt                          **
**                                                                            **
** Service ID:  0x10                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant for different CPU core                              **
**                                                                            **
** Parameters (in) :  Channel - DMA channel ID(0-127)                         **
**                    Event   - channel interrupt to be enabled               **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
extern void Dma_ChInterruptEnable
(
  const uint8 Channel,
  const Dma_EventsType Event
);

#if (DMA_SETPATTERN_API == STD_ON)
/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax : Std_ReturnType  Dma_SetPattern (const uint8 Channel,              **
**                                       const uint32 Pattern )               **
**                                                                            **
** Description : This API allows the user to set or change the pattern which  **
**               should be used for the pattern detection/conditional linked  **
**               list feature.                                                **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x19                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  reentrant                                                     **
**                                                                            **
** Parameters (in) : Channel - Channel number for which the pattern is        **
**                             intended.                                      **
**                   Pattern   - The specific pattern which is to be set to   **
**                               the PRR register.                            **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  E_OK - Pattern was programmed into the register         **
**                           successfully                                     **
**                    E_NOT_OK - Pattern was not programmed into the register,** 
**                               if error detected in Dma_lDetCheck or        **
**                               Channel not configured for pattern or        **
**                               Channel is in progress                       **
**                                                                            **
*******************************************************************************/
Std_ReturnType  Dma_SetPattern (const uint8 Channel, const uint32 Pattern ) ;
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro 'Dma_SetPattern'
 * defined. No side effects foreseen by violating this MISRA rule. */
#define Dma_SetPattern (Channel, Pattern ) \
                                (ERROR_Dma_SetPattern_API_IS_NOT_SELECTED)
#endif

/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax : extern void Dma_ChInterruptDisable (uint8 Channel,                **
**                                              Dma_ChEventType Event)        **
**                                                                            **
** Description : Service to disable channel interrupt                         **
**                                                                            **
** Service ID:  0x11                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant for different CPU core                              **
**                                                                            **
** Parameters (in) :  Channel - DMA channel ID(0-127)                         **
**                    Event   - channel interrupt to be disabled              **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
extern void Dma_ChInterruptDisable
(
  const uint8 Channel,
  const Dma_EventsType Event
);

#if (DMA_GETVERSIONINFO_API == STD_ON)
/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax : extern void Dma_GetVersionInfo                                    **
**                                     (Std_VersionInfoType * VersionInfoPtr) **
**                                                                            **
** Description : Service to get DMA driver version                            **
**                                                                            **
** Service ID:  0x12                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant                                                     **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  VersionInfoPtr -  Pointer to store version ID by driver **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
extern void Dma_GetVersionInfo
(
  Std_VersionInfoType * const VersionInfoPtr
);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro 'Dma_GetVersionInfo'
 * defined. No side effects foreseen by violating this MISRA rule. */
#define Dma_GetVersionInfo(VersionInfoPtr) \
                                (ERROR_Dma_GetVersionInfo_API_IS_NOT_SELECTED)
#endif


/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax : uint32 Dma_GetEvents( uint8 Channel )                             **
**                                                                            **
** Description : Service to get list of all events happened on a DMA channel, **
**               including the channel events and error events.               **
**                                                                            **
** Service ID:  0x0E                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Conditionally Reentrant - This API is re-entrant for          **
**              different DMA channels                                        **
**                                                                            **
** Parameters (in) :  Channel - Dma Channel ID                                **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Status word containing consolidated channel events      **
**                                                                            **
*******************************************************************************/
extern uint32 Dma_GetEvents
(
  const uint8 Channel
);

/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax : Std_ReturnType Dma_MEStatusClear(Dma_MoveEngineListType           **
**                                              const MoveEngineNumber)       **
**                                                                            **
** Description : Service to Clear all or selected MoveEngine events           **
**                                                                            **
** Service ID:  0x15                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Dma_MEStatusClear
(
  Dma_MoveEngineListType const MoveEngineNumber
);

/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax : extern void Dma_ChInterruptHandler (const uint8 Channel)          **
**                                                                            **
** Description : This is the interrupt service routine of a channel interrupt **
**               invoked by the interrupt frame (installed in the interrupt   **
**               vector table).                                               **
**               It identifies the cause of the interrupt, clears the status  **
**               and invokes registered notification routines                 **
**                                                                            **
** Service ID:  None                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  Channel - DMA channel ID(0-127)                         **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
extern void Dma_ChInterruptHandler
(
  const uint8 Channel
);

/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax : extern void Dma_MEInterruptDispatcher (void)                      **
**                                                                            **
** Description : This is the Level-2 interrupt dispatcher meant to be called  **
**                by the interrupt service routine (installed in the          **
**                interrupt vector table). The handler identifies the ME      **
**                responsible for the error interrupt and calls the interrupt **
**                handler                                                     **
**                                                                            **
** Service ID:  None                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
*******************************************************************************/
extern void Dma_MEInterruptDispatcher
(
  void
);

/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax : Std_ReturnType Dma_GetCrcValue(uint8 ChannelId,                   **
**                                         uint32 CrcType,                    **
**                                         uint32* CrcBuffer)                 **
**                                                                            **
** Description : Service to read the CRC value calculated by the DMA hardware **
**                                                                            **
** Service ID:  0x17                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant                                                     **
**                                                                            **
** Parameters (in) :  ChannelId - DMA channel ID                              **
**                    CrcType   - Address CRC or Data CRC selection           **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  CRC value calculated by the hardware                    **
**                                                                            **
*******************************************************************************/
extern uint32 Dma_GetCrcValue
(
  const uint8 ChannelId,
  const Dma_CrcType CrcType
);

/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax : Std_ReturnType Dma_GetCurrentTimeStamp(void)                      **
**                                                                            **
** Description : Service to read the current time stamp in DMA                **
**                                                                            **
** Service ID:  0x18                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant                                                     **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  Current time stamp                                      **
**                                                                            **
*******************************************************************************/
extern uint32 Dma_GetCurrentTimeStamp
(
  void
);

/*******************************************************************************
** Traceability:                                                              **
**                                                                            **
** Syntax : Std_ReturnType Dma_IsChannelInitDone(uint8 ChannelId)             **
**                                                                            **
** Description : Service to read the init status of a channel                 **
**                                                                            **
** Service ID:  0x19                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant                                                     **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): ChannelId - The channel id                               **
**                                                                            **
** Return value    :  E_OK      - Channel is initialized                      **
**                    E_NOT_OK  - Channel is not initialized                  **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Dma_IsChannelInitDone
(
  const uint8 ChannelId
);


#define DMA_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Dma_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
#include "Dma_MemMap.h"


/* Include the PbCfg header */
#include "Dma_PBcfg.h"

#endif
