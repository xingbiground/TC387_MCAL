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
**  FILENAME     : Lin_17_AscLin.h                                            **
**                                                                            **
**  VERSION      : 15.0.0                                                     **
**                                                                            **
**  DATE         : 2020-11-20                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Lin Driver header definition file                          **
**                                                                            **
**  SPECIFICATION(S) : Specification of Lin Driver, AUTOSAR Release 4.2.2     **
**                                              and AUTOSAR Release 4.4.0     **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/*[cover parentID={A6441ED2-CF72-40f9-B26D-BD0C8B9BBA95}][/cover]*/

/*[cover parentID={17CFEE3F-5831-4e31-B5CE-56C0E0970FD8}]
    [/cover]*/
#ifndef LIN_17_ASCLIN_H
#define LIN_17_ASCLIN_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* [cover parentID={1D305FB3-8B31-4222-9103-2D15AEC9C5BD}][/cover] */
/* [cover parentID={09D73E3A-684D-4139-9708-15FACB2D2B42}][/cover] */
/* Inclusion of type definition for ComStack */
#include "ComStack_Types.h"

/* Pre-compile/static configuration parameters for Lin  */
#include "Lin_17_AscLin_Cfg.h"
/* Global functions like Set/Reset END INIT protection bit,
  Enable/Disable interrupts, Automic write function */
#include "McalLib.h"
/* [cover parentID={7F741E1D-E2C2-4048-AFB2-2E802DFCA966}][/cover] */
/* [cover parentID={9359C2C4-C243-4fca-AA80-D7AEC16B6D06}][/cover] */
/* [cover parentID={AF9AC8DD-9758-47cd-B39E-D2FAFAA3DD80}][/cover] */
/* [cover parentID={BB9348C3-B299-4e20-8945-8D42DB1345B0}][/cover] */
/* Lin Specific type definitions*/
/* [cover parentID={0B79EA73-D164-4cba-B364-60375E3524D1}][/cover] */
/* [cover parentID={20BE2395-0B0F-4003-9637-9323B5A4825B}][/cover] */
/* [cover parentID={CF82B7F1-B9F1-46dd-A4B1-0C3E3077A286}][/cover] */
/* [cover parentID={7395CD2E-0D58-4a85-A804-1530B9A00B10}][/cover] */
/* [cover parentID={C0CCA1D9-7245-4793-ACC5-86CB70077288}][/cover] */
/* [cover parentID={2DF79DA9-F4E7-4769-B027-A28F2779FEFE}][/cover] */
/* [cover parentID={7AD7F462-98E6-43b1-A7EB-8AB8392AE211}][/cover] */
#include "Lin_GeneralTypes.h"

/* [cover parentID={0ABD588C-4780-48b8-B2FF-7E7BD2B71D34}][/cover] */
/* Inclusion of EcuM files to notify ECU State Manager on wakeup validation*/
#include "EcuM.h"
#if (MCAL_AR_VERSION == MCAL_AR_422)
#include "EcuM_Cbk.h"
#else
#include "EcuM_Externals.h"
#endif

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/* [cover parentID={12A12F60-EDF2-40c8-9A91-1D19750C1A02}][/cover] */
/* Vendor ID */
#define LIN_17_ASCLIN_VENDOR_ID  (17U)

/* LIN Module ID 82 */
#define LIN_17_ASCLIN_MODULE_ID  (82U)

/* LIN Instance ID */
#define LIN_17_ASCLIN_INSTANCE_ID  (LIN_17_ASCLIN_INDEX)

#if (LIN_17_ASCLIN_DEV_ERROR_DETECT == STD_ON)
/*
  Development error values
*/
/* API service used without module initialization */
/* [cover parentID={138FC137-48EC-4738-9683-D1AEEE9DEFFA}][/cover] */
#define LIN_17_ASCLIN_E_UNINIT            ((uint8)0x00)

/* API service used with an invalid channel Identifier */
/* [cover parentID={25EE39C2-2746-499d-9A6B-6615A51F31A2}][/cover] */
#define LIN_17_ASCLIN_E_INVALID_CHANNEL    ((uint8)0x02)

/* API service used with an invalid pointer */
/* [cover parentID={3D2DAC6D-CF69-4dae-A65C-14880D9BA150}][/cover] */
#define LIN_17_ASCLIN_E_INVALID_POINTER   ((uint8)0x03)

/* API service used with an invalid state transition */
/* [cover parentID={9A531F46-D5DC-4fcc-8D9B-C43757FE66D4}][/cover] */
#define LIN_17_ASCLIN_E_STATE_TRANSITION  ((uint8)0x04)

/*API Service called with NULL parameter.*/
/* [cover parentID={4CCC2965-CC9E-4da2-9163-A0D9F9F1D62B}][/cover] */
#define LIN_17_ASCLIN_E_PARAM_POINTER     ((uint8)0x05)

/*
  API Service ID's
*/
/* API Service ID for Lin_17_AscLin_Init() */
#define LIN_17_ASCLIN_SID_INIT                  ((uint8)0x0)

/* API Service ID for Lin_GetVersionInfo() */
#define LIN_17_ASCLIN_SID_VERSIONINFO           ((uint8)0x1)

/* API Service ID for Lin_SendFrame() */
#define LIN_17_ASCLIN_SID_SENDFRAME             ((uint8)0x4)

/* API Service ID for Lin_17_AscLin_GoToSleep() */
#define LIN_17_ASCLIN_SID_GOTOSLEEP            ((uint8)0x6)

/* API Service ID for Lin_WakeUp() */
#define LIN_17_ASCLIN_SID_WAKEUP               ((uint8)0x7)

/* API Service ID for Lin_17_AscLin_GetStatus() */
#define LIN_17_ASCLIN_SID_GETSTATUS            ((uint8)0x8)

/* API Service ID for Lin_17_AscLin_GoToSleepInternal() */
#define LIN_17_ASCLIN_SID_GOTOSLEEPINTERNAL    ((uint8)0x9)

/* API Service ID for Lin_17_AscLin_CheckWakeup() */
#define LIN_17_ASCLIN_SID_CHECKWAKEUP          ((uint8)0xA)

/* API Service ID for Lin_WakeUpInternal() */
#define LIN_17_ASCLIN_SID_WAKEUPINTERNAL       ((uint8)0xB)

#endif /* (LIN_17_ASCLIN_DEV_ERROR_DETECT == ON) */

/* Multi-core DETs*/
/* Report DET LIN module not configured for this Core*/
#define LIN_17_ASCLIN_E_CORE_NOT_CONFIGURED     ((uint8)0x64)
/* [cover parentID={FC349D62-D8A0-47d0-8809-4567B47D99F5}]
   LIN channel is not allocated to this core
[/cover] */
#define LIN_17_ASCLIN_E_CORE_CHANNEL_MISMATCH   ((uint8)0x65)

/* Macro's to check the wake is enabled by channel */
#define LIN_17_ASCLIN_CHANNEL_WAKEUP_ENABLED (1U)
#define LIN_17_ASCLIN_CHANNEL_WAKEUP_DISABLED (0U)
/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
/*
  This sturcture defines the channel timing parameters
*/
/* [cover parentID={0B0D4A70-0DC1-4b31-85B5-BEE8F6A11C04}]
    [/cover] */
typedef struct
{
  /* BRG.NUMERATOR value  */
  uint16 HwBrgNumerator;
  /* BRG.DENOMINATOR value  */
  uint16 HwBrgDenominator;
  /* BITCON.PRESCALAR value  */
  uint16 HwBitconPrescalar;
  /* Prescalar for Wakeup detection */
  uint16 HwWakeupBitconPrescalar;
  /* This is the delay inserted between transmission of bytes and also
  the delay between the header and the response.
  Delay is in terms of bit times  */
  uint8 InterByteResponseSpace;
  /* Iocr Depth for wakeup detection */
  uint8 HwWakeupIocrDepth;
} Lin_17_AscLin_ChannelTimingConfigType;

/*
Type: Lin_17_AscLin_ChannelType
This is the type of the external data structure containing the overall
initialization data for one LIN Channel.
*/
/* [cover parentID={FD7CEA73-DAAC-40de-8A2F-E1F14D5B212F}]
    [/cover] */
typedef struct
{
  /* Specifies the channel timing*/
  Lin_17_AscLin_ChannelTimingConfigType TimingConfig;
  /* Identifies the wake up source id */
  EcuM_WakeupSourceType WakeupSourceId;
  /* Identifies the the ASCLINx */
  uint8 HwModule;
  /* Identifies the Lin channel support wake up */
  uint8 Wakeup;
  /*Rx alternate pin selection*/
  uint8 RxAlternatePinSelect;
  /* Logical channel Id */
  uint8 LogicalId;
  /* Node type */
  uint8 Node;
} Lin_17_AscLin_ChannelType;

/*
Type: Lin_17_AscLin_CoreConfigType
*/
/* [cover parentID={AA483BBD-CE1D-41c6-AC00-33CED0A0A71F}]
    [/cover] */
typedef struct
{
  /* Maximum no of the channels allocated to the core */
  uint8 MaxCoreChannels;
  /* Ptr to LIN Channel Config */
  const Lin_17_AscLin_ChannelType* ChannelConfigPtr;
} Lin_17_AscLin_CoreConfigType;

/*
Type: Lin_17_AscLin_ConfigType
*/
/* [cover parentID={4D975FA5-93BA-4933-BCDC-EB5C80C5998E}]
    [/cover] */
typedef struct
{
  /* Ptr to Core configuration */
  const Lin_17_AscLin_CoreConfigType* CoreConfigPtr[MCAL_NO_OF_CORES];
  /* Ptr to the channel allocation core mapping */
  const uint8* ChannelToCorePtr;
  /* Ptr to channel lookup */
  const uint8* Lin_17_AscLin_ChannelIdLookupPtr;
} Lin_17_AscLin_ConfigType;

/*Macro for the Node Type of a LIN channel */
#define LIN_17_ASCLIN_MASTER_NODE (0x1U) /* LIN Channel node is MASTER*/
#if (MCAL_AR_VERSION == MCAL_AR_440) /* Slave Supported */
#define LIN_17_ASCLIN_SLAVE_NODE (0x0U) /* LIN Channel node is Slave */
#endif

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/


/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
#define LIN_17_ASCLIN_START_SEC_CODE_QM_GLOBAL
/*mapping of code and data to specific memory sections via memory mapping file*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
    without safegaurd. It complies to Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"


/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax : void Lin_17_AscLin_Init( const Lin_17_AscLin_ConfigType* Config ) **
**                                                                            **
** Service ID:  0x00                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  Config - Pointer to LIN driver configuration set        **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : Driver Module Initialization function.                       **
** Service for LIN initialization. The Initialization function shall          **
** initialize all common relevant registers of Lin channels with the values   **
** of the structure referenced by the parameter ConfigPtr.                    **
*******************************************************************************/
extern void Lin_17_AscLin_Init
(
  const Lin_17_AscLin_ConfigType* const Config
);

/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax : Std_ReturnType Lin_17_AscLin_CheckWakeup(uint8 Channel)           **
**                                                                            **
** Service ID:  0x0A                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : Channel : LIN channel to be addressed                    **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: No error has occurred during execution of the API  **
**               E_NOT_OK: An error has occurred during execution of the API  **
**                                                                            **
** Description : This API checks if a wakeup has occurred on the              **
**               addressed LIN channel                                        **
*******************************************************************************/
extern Std_ReturnType Lin_17_AscLin_CheckWakeup
(
  const uint8 Channel
);
#if (LIN_17_ASCLIN_MASTER_CH_PRESENT == STD_ON)
/*******************************************************************************
** Syntax : Std_ReturnType Lin_17_AscLin_SendFrame                            **
**  (                                                                         **
**    uint8 Channel,                                                          **
**    const Lin_PduType* PduInfoPtr                                           **
**  )                                                                         **
**                                                                            **
** Service ID:  0x04                                                          **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in): Channel - LIN channel to be addressed .                   **
**                  PduInfoPtr - Pointer to PDU containing the PID, Checksum  **
**                  model, Response type, Dl and SDU data pointer             **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK - send command has been accepted.                   **
**                   E_NOT_OK - send command has not been accepted,
**                              development or production error occurred.     **
**                                                                            **
** Description : Service to send a Lin header and send/recv response.         **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Lin_17_AscLin_SendFrame
(
  const uint8 Channel,
  const Lin_PduType* const PduInfoPtr
);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Lin_17_AscLin_SendFrame(Channel, PduInfoPtr) \
                  (ERROR_Lin_17_AscLin_SendFrame_NO_MASTER_CHANNEL_CONFIGURED)
#endif /* End for Lin_17_AscLin_SendFrame API */

#if (LIN_17_ASCLIN_MASTER_CH_PRESENT == STD_ON)
/*******************************************************************************
** Syntax : Std_ReturnType Lin_17_AscLin_GoToSleep(uint8 Channel)             **
**                                                                            **
** Service ID:  0x06                                                          **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non Reentrant                                                 **
**                                                                            **
** Parameters (in) : Channel - LIN channel to be addressed                    **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: Sleep command has been accepted                    **
**                   E_NOT_OK: Sleep command has not been accepted,           **
**                   development or production error occurred                 **
**                                                                            **
** Description : The service instructs the driver to transmit a
**               go-to-sleep-command on the addressed LIN channel             **
**                                                                            **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Lin_17_AscLin_GoToSleep
(
  const uint8 Channel
);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Lin_17_AscLin_GoToSleep(Channel) \
                  (ERROR_Lin_17_AscLin_GoToSleep_NO_MASTER_CHANNEL_CONFIGURED)
#endif /* End for Lin_17_AscLin_GoToSleep API */
/*******************************************************************************
** Syntax : Std_ReturnType Lin_17_AscLin_GoToSleepInternal(uint8 Channel)     **
**                                                                            **
** Service ID:  0x09                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Reentrant                                                 **
**                                                                            **
** Parameters (in) : Channel - LIN channel to be addressed .                  **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: Command has been accepted.                         **
**                   E_NOT_OK: Command has not been accepted, development     **
**                   or production error occurred                             **
**                                                                            **
** Description : Sets the channel state to LIN_CH_SLEEP                       **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Lin_17_AscLin_GoToSleepInternal
(
  const uint8 Channel
);

/*******************************************************************************
** Syntax           : Std_ReturnType Lin_17_AscLin_Wakeup(uint8 Channel)      **
**                                                                            **
** Service ID       : 0x07                                                    **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters (in)  : none                                                    **
**                                                                            **
** Parameters (out) : Channel - LIN channel to be addressed                   **
**                                                                            **
** Return value     : E_OK: Wake-up request has been accepted                 **
**                    E_NOT_OK: Wake-up request has not been accepted,        **
**                    development or production error occurred                **
**                                                                            **
** Description      : This service Generates a wake up pulse and sets the     **
**                    channel state to LIN_CH_OPERATIONAL.                    **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Lin_17_AscLin_Wakeup
(
  const uint8 Channel
);
#if (LIN_17_ASCLIN_MASTER_CH_PRESENT == STD_ON)
/*******************************************************************************
** Syntax : Lin_StatusType Lin_17_AscLin_GetStatus                            **
**                                        (uint8 Channel, uint8 **LinSduPtr)  **
**                                                                            **
** Service ID:      0x08                                                      **
**                                                                            **
** Sync/Async:      Synchronous                                               **
**                                                                            **
** Reentrancy:      non reentrant                                             **
**                                                                            **
** Parameters (in): Channel    : LIN channel to be addressed                  **
**                                                                            **
** Parameters (out):LinSduPtr : Reference to a shadow buffer or memory mapped **
**                               LIN Hardware receive buffer where the current**
**                               SDU is stored                                **
**                                                                            **
** Return value:    LIN_NOT_OK  : Development or Production error occurred    **
**                  LIN_TX_OK   : Successful transmission                     **
**                  LIN_TX_BUSY : Ongoing Transmission (Header or Response)   **
**                  LIN_TX_HEADER_ERROR :                                     **
**                      Erroneous header transmission such as:                **
**                         - Mismatch between sent and read back data         **
**                         - Identifier parity error or                       **
**                         - Physical bus error                               **
**                  LIN_TX_ERROR: Erroneous transmission                      **
**                         - Mismatch between sent and read back data         **
**                         - Physical bus error                               **
**                  LIN_RX_OK   : Reception of correct response               **
**                  LIN_RX_BUSY : Ongoing reception: at least one response    **
**                                byte has been received, but the checksum    **
**                                byte has not been received                  **
**                  LIN_RX_ERROR: Erroneous reception                         **
**                                - Framing error                             **
**                                - Data error                                **
**                                - Checksum error or Short response          **
**                  LIN_RX_NO_RESPONSE : No reception                         **
**                  LIN_OPERATIONAL : Normal operation; the related LIN       **
**                                    channel is ready to transmit next header**
**                                    No data from previous frame available   **
**                                   (e.g. after initialization)              **
**                  LIN_CH_SLEEP : Sleep mode operation; in this mode wake-up **
**                                 detection from slave nodes is enabled      **
**                  LIN_TX_HEADER_TIMEOUT_ERROR: Transmit header timeout error**
**                                              occurred                      **
**                  LIN_RX_RESPONSE_TIMEOUT_ERROR: Response timeout error     **
**                                                occurred                    **
**                                                                            **
** Description :    Indicates the current transmission, reception or          **
**                  operation status of the LIN driver                        **
**                                                                            **
**                  If a SDU has been successfully received, the SDU          **
**                  will be stored in a shadow buffer or memory mapped LIN    **
**                  Hardware receive buffer referenced by Lin_SduPtr.         **
**                  The buffer will only be valid and must be read until the  **
**                  next Lin_SendHeader function call.                        **
**                  The LIN driver shall provide a function to                **
**                  interrogate the status of the current frame transmission  **
**                  request ((Lin_17_AscLin_GetStatus)                        **
**                  The LIN driver shall provide a service for                **
**                  checking the current state of each LIN channel under its  **
**                  control (( Lin_17_AscLin_GetStatus)                       **
**                  LIN operation states for a LIN channel or frame,          **
**                  as returned by the API service Lin_17_AscLin_GetStatus()  **
**                                                                            **
*******************************************************************************/
extern Lin_StatusType Lin_17_AscLin_GetStatus
(
  const uint8 Channel,
  uint8 ** const LinSduPtr
);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Lin_17_AscLin_GetStatus(Channel, LinSduPtr) \
                  (ERROR_Lin_17_AscLin_GetStatus_NO_MASTER_CHANNEL_CONFIGURED)
#endif /* End for Lin_17_AscLin_GetStatus API */

/*******************************************************************************
** Syntax           : Std_ReturnType Lin_17_AscLin_WakeupInternal             **
**                    (                                                       **
**                        uint8 Channel                                       **
**                    )                                                       **
**                                                                            **
** Service ID       : 0x0b                                                    **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : non - reentrant                                         **
**                                                                            **
** Parameters (in)  : none                                                    **
**                                                                            **
** Parameters (out) : Channel - LIN channel to be addressed                   **
**                                                                            **
** Return value     : E_OK: Wake-up request has been accepted                 **
**                    E_NOT_OK: Wake-up request has not been accepted,        **
**                    development or production error occurred                **
**                                                                            **
** Description      : This service Sets the channel state to                  **
**                    LIN_CH_OPERATIONAL without generating a wake up pulse.  **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Lin_17_AscLin_WakeupInternal
(
  const uint8 Channel
);

#if(LIN_17_ASCLIN_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Traceability :                                                             **
**                                                                            **
** Syntax           : void  Lin_17_AscLin_GetVersionInfo                      **
**                    (                                                       **
**                      Std_VersionInfoType *VersionInfo                      **
**                    )                                                       **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x01                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : none                                                    **
**                                                                            **
** Parameters (out) : versioninfo - Pointer to where to store the             **
**                    version information of this module.                     **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : This function:                                          **
**   - This function returns the version information of the module            **
*******************************************************************************/
extern void Lin_17_AscLin_GetVersionInfo
(
  Std_VersionInfoType *const versioninfo
);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Lin_17_AscLin_GetVersionInfo(versioninfo) \
                             (ERROR_Lin_17_AscLin_GetVersionInfo_API_IS_NOT_SELECTED)
#endif /* End for Lin_17_AscLin_GetVersionInfo API */

#if (LIN_17_ASCLIN_INTERRUPT_ENABLE == STD_ON)
/*******************************************************************************
**                      Global Function Declarations:                         **
**             Functions to be Called From Interrupt/Scheduler Context        **
*******************************************************************************/
/*******************************************************************************
** Syntax :          void Lin_17_AscLin_IsrReceive( uint8  HwUnit)            **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  HwUnit : Represents ASCLIN hw module number              **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
** Description :     This ISR will be called whenever the Slave response data **
**                   is completely received by the ASCLIN w/o any errors      **
*******************************************************************************/
extern void Lin_17_AscLin_IsrReceive(const uint8 HwUnit);
/*******************************************************************************
** Syntax :          void Lin_17_AscLin_IsrTransmit( uint8  HwUnit)           **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  HwUnit : Represents Hw Module number                     **
**                                                                            **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
** Description :     This ISR will be called whenever the response data       **
**                   is successfully transmitted by the ASCLIN w/o any errors **
**                                                                            **
*******************************************************************************/
extern void Lin_17_AscLin_IsrTransmit(const uint8 HwUnit);
/*******************************************************************************
** Syntax :          void Lin_17_AscLin_IsrError( uint8  HwUnit)              **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  HwUnit : Represents Hw Module number                     **
**                                                                            **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
** Description :     This ISR will be called whenever there is an data        **
**                   transmission or reception error in ASCLIN                **
*******************************************************************************/
extern void Lin_17_AscLin_IsrError(const uint8 HwUnit);
#endif
/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/
#define LIN_17_ASCLIN_STOP_SEC_CODE_QM_GLOBAL
/*mapping of code and data to specific memory sections via memory mapping file*/
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safegaurd.*/
#include "Lin_17_AscLin_MemMap.h"
/* The file is included to get extern declaration of all the configuration root
structure. The extern declaration of configuration root structure is needed by
application software */
#include "Lin_17_AscLin_PBcfg.h"
#endif   /*  LIN_17_ASCLIN_H  */

