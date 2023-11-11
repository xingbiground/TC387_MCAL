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
**  FILENAME     : Spi.h                                                      **
**                                                                            **
**  VERSION      : 20.0.0                                                     **
**                                                                            **
**  DATE         : 2021-03-04                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Spi Driver header definition file                          **
**                                                                            **
**  SPECIFICATION(S) : Specification of Spi Driver, AUTOSAR Release 4.2.2     **
**                     Specification of Spi Driver, AUTOSAR Release 4.4.0     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
** TRACEABILITY :[cover parentID={A84FDB40-B3BA-42c3-B240-4BC6403CC34B}][/cover]
** [cover parentID={F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}][/cover]
*******************************************************************************/

#ifndef SPI_H
#define SPI_H

/* [cover parentID={39A545E5-2339-43d6-A8D6-99B9B60C2018}]
[/cover] */

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Std_Types.h"
#include "Spi_Cfg.h"

/* Inclusion of MCAL library file */
#include "McalLib.h"

#if(SPI_LEVEL_DELIVERED != 0U)
#include "Dma.h"
#endif

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/* Since the upper multiplicity of the module is 1 */
/* [cover parentID={3C4FF0DC-87D9-4a01-AF66-9F14296E9FB5}]
[/cover] */
#define SPI_INSTANCE_ID                ((uint8)0U)
#define SPI_VENDOR_ID                  (17U)
#define SPI_MODULE_ID                  ((uint16)83U)

/* ERROR IDs */
/* API service invoked with wrong Channel  */
#define SPI_E_PARAM_CHANNEL            ((uint8)0x0AU)
/* API service invoked with wrong Job      */
#define SPI_E_PARAM_JOB                ((uint8)0x0BU)
/* API service invoked with wrong Sequence */
#define SPI_E_PARAM_SEQ                ((uint8)0x0CU)
/* API service invoked with wrong Length   */
#define SPI_E_PARAM_LENGTH             ((uint8)0x0DU)
/* API service invoked with wrong Hw unit  */
#define SPI_E_PARAM_UNIT               ((uint8)0x0EU)
/* API service invoked with NULL pointer   */
#define SPI_E_PARAM_POINTER            ((uint8)0x10U)
/* For API service(except Init) invoked before initialization */
#define SPI_E_UNINIT                   ((uint8)0x1AU)
/* Requested Sequence for async transmit,
   is already in state SPI_SEQ_PENDING   */
#define SPI_E_SEQ_PENDING              ((uint8)0x2AU)
/* Spi_SyncTransmit is invoked while a sequence is on transmission */
#define SPI_E_SEQ_IN_PROCESS           ((uint8)0x3AU)
/* SPI_Init service invoked,
   while the SPI driver has already been initialized */
#define SPI_E_ALREADY_INITIALIZED      ((uint8)0x4AU)
/* Sequence / channel / job not configured to core */
#define SPI_E_NOT_CONFIGURED           ((uint8)0x4BU)
/* Queue full DET */
#define SPI_E_QUEUE_FULL               ((uint8)0x4CU)

/* Init check failure */
#define SPI_E_INIT_FAILED          ((uint8)0x64U)
/* SPI Safety - Invalid parameter */
#define SPI_E_SAFETY_INVALID_PARAM      ((uint8)0x65U)
/* SPI Invalid interrupt */
#define SPI_E_SAFETY_SPURIOUS_INTERRUPT ((uint8)0x66U)

/* DMA channels are not configured */
#define SPI_E_DMA_CHANNEL_NOT_CONFIGURED ((uint8)0x67U)
/* Move counter limit */
#define SPI_E_MOVECOUNTER_LIMIT_EXCEEDED ((uint8)0x68U)

/* Service ID */
/* Spi_Init */
#define SPI_SID_INIT                   ((uint8)0x00U)
/* Spi_DeInit */
#define SPI_SID_DEINIT                 ((uint8)0x01U)
/* Spi_WriteIB */
#define SPI_SID_WRITEIB                ((uint8)0x02U)
/* Spi_AsyncTransmit */
#define SPI_SID_ASYNCTRANSMIT          ((uint8)0x03U)
/* Spi_ReadIB *//*  */
#define SPI_SID_READIB                 ((uint8)0x04U)
/* Spi_SetupEB */
#define SPI_SID_SETUPEB                ((uint8)0x05U)
/* Spi_GetStatus */
#define SPI_SID_GETSTATUS              ((uint8)0x06U)
/* Spi_GetJobResult */
#define SPI_SID_GETJOBRESULT           ((uint8)0x07U)
/* Spi_GetSequenceResult */
#define SPI_SID_GETSEQUENCERESULT      ((uint8)0x08U)
/* Spi_GetVersionInfo */
#define SPI_SID_GETVERSIONINFO         ((uint8)0x09U)
/* Spi_SyncTransmit */
#define SPI_SID_SYNCTRANSMIT           ((uint8)0x0AU)
/* Spi_GetHWUnitStatus */
#define SPI_SID_GETHWUNITSTATUS        ((uint8)0x0BU)
/* Spi_Cancel */
#define SPI_SID_CANCEL                 ((uint8)0x0CU)
/* Spi_SetAsyncMode */
#define SPI_SID_SETASYNCMODE           ((uint8)0x0DU)
/* Spi_MainFunction_Handling */
#define SPI_SID_MAINFUNCTION_HANDLING  ((uint8)0x10U)
/* Spi_InitCheck */
#define SPI_SID_INITCHECK              ((uint8)0x20U)
/* SPI_DMA RX complete callback */
#define SPI_SID_RX_INTERRUPT           ((uint8)0x21U)
/* SPI PT2 interrupt handler */
#define SPI_SID_PT2_INTERRUPT          ((uint8)0x22U)
/* SPI Error interrupt*/
#define SPI_SID_QSPI_ERROR_INTERRUPT   ((uint8)0x23U)
/* SPI DMA Error interrupt */
#define SPI_SID_DMA_ERROR_INTERRUPT    ((uint8)0x24U)
/* SPI LOOP BACK */
#define SPI_SID_CONTROLLOOPBACK        ((uint8)0x25U)

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/

/* Type : Spi_StatusType
   This type defines a range of specific status for SPI Handler/Driver.
   It informs about the SPI Handler/Driver status and can be obtained
   calling the API service Spi_GetStatus                                */
/* [cover parentID={12F1EB74-01EB-49fb-A382-C43DDF842A84}] */
typedef enum
{
  SPI_UNINIT,  /* The SPI Driver is not initialized or not usable       */
  SPI_IDLE,    /* The SPI Driver is not currently transmitting any Jobs */
  SPI_BUSY     /* The SPI Driver is performing a SPI Job (transmit)     */
} Spi_StatusType;
/*  [/cover] */

/* Type : Spi_JobResultType
   This type specifies the Jobs status for SPI Handler/Driver.
   It informs about a SPI Handler/Driver Job status and can be obtained
   calling the API service Spi_GetJobResult with the Job ID             */
/* [cover parentID={60557A19-F3E2-49ff-BB6C-161CC1176826}] */
typedef enum
{
  SPI_JOB_OK,       /* The last transmission of the Job is successful   */
  SPI_JOB_PENDING,  /* The SPI Driver is performing a SPI Job transfer  */
  SPI_JOB_FAILED,   /* The last transmission of the Job has failed      */
  SPI_JOB_QUEUED    /* Job is in Queue and is not started yet           */
} Spi_JobResultType;
/*  [/cover] */

/* Type : Spi_SeqResultType
   This type specifies Sequences status for SPI Handler/Driver.
   It informs about a SPI Handler/Driver Sequence status and can be
   obtained calling the API service Spi_GetSequenceResult           */
/* [cover parentID={CC6585E0-8681-4d9e-9CD3-F85FFDE83BDD}] */
typedef enum
{
  SPI_SEQ_OK,       /* The last transmission of the Sequence is successful   */
  SPI_SEQ_PENDING,  /* The SPI Driver is performing a SEQ transfer           */
  SPI_SEQ_FAILED,   /* The last transmission of the Sequence has failed      */
  SPI_SEQ_CANCELED  /* The last transmission of the Seq is cancelled by user */
} Spi_SeqResultType;
/*  [/cover] */

/* Type : Spi_LoopBackType
   This type specifies loopback control parameters */
/* [cover parentID={1449AC57-2995-4774-8DF6-23F1A84DC3F4}] */
typedef enum
{
  SPI_LOOPBACK_DISABLE = 0U,     /* Disables the Loopback mode   */
  SPI_LOOPBACK_ENABLE = 1U       /* Enables the Loopback mode   */
} Spi_LoopBackType;
/*  [/cover] */

/* Type : Spi_DataBufferType
   Type of application data buffer elements.
   In order to always get the same user interface, the SPI Handler/Driver
   shall handle these differences using the following proposed rules:
   A) Spi_DataType 8/16/32 bits, data width 8/16/32 bits.
      Straightforward send and receive.
   B) Spi_DataType superior to data width. Send the lower part,
      ignore the upper part. Receive the lower part, extend with zero.
   C) Spi_DataType inferior to data width.
      According to the memory alignement use prior both rules.
*/
/* [cover parentID={82F31EE0-69A7-4db2-8BD0-B3B51003B4ED}][/cover] */
typedef uint8 Spi_DataBufferType;


/* Type : Spi_NumberOfDataType
   Type for defining the number of data elements of the
   type Spi_DataType to send and / or receive by Channel  */
/* [cover parentID={DE0FD440-39F7-4900-AECC-7DFA5592437C}] */
typedef uint16 Spi_NumberOfDataType;
/*  [/cover] */

/* Type : Spi_ChannelType
   Specifies the identification (ID) for a Channel */
/* [cover parentID={0B6719DC-B379-4a86-81B4-C4139BD99D7D}] */
typedef uint8 Spi_ChannelType;
/*  [/cover] */

/* Type : Spi_JobType
   Specifies the identification (ID) for a Job */
/* [cover parentID={07CA437F-5E1E-4852-9924-9CFE1BABE7FD}] */
typedef uint16 Spi_JobType;
/*  [/cover] */

/* Type : Spi_SequenceType
   Specifies the identification (ID) for a Sequence */
/* [cover parentID={21BD0700-DAF4-48cb-B63C-010E6DF18DED}] */
typedef uint8 Spi_SequenceType;
/*  [/cover] */

/* Type: Spi_HWUnitType
   Configuration Structure for HwModule and Hw Channel no */
/* [cover parentID={55F8F5D5-4E31-4fe1-811B-B57BFFA27CEF}] */
typedef uint8 Spi_HWUnitType;
/*  [/cover] */


typedef uint32 Spi_QSPIHwMapConfigType ;


/* Type : Spi_AsyncModeType
   Specifies the Asynchronous mechanism mode for Spi Handler/Driver
   i.e Polling Mode and Interrupt Mode.
   This type is available or not accordind to the pre compile
   time parameter:SPI_LEVEL_DELIVERED. This is only relevant for LEVEL 2 */
#if (SPI_LEVEL_DELIVERED == 2U)
/* [cover parentID={0EC09726-3F42-4fa2-B45E-9E410ED58CCC}] */
typedef enum
{
  SPI_POLLING_MODE,
  SPI_INTERRUPT_MODE
} Spi_AsyncModeType;
/*  [/cover] */
#endif

/* Type: Spi_JobEndNotification
   To provide Job Notification the following type will be used */
/* [cover parentID={1B47B45A-107F-4262-948B-8E4D5A722791}] */
typedef void(*Spi_JobEndNotification)(void);
/*  [/cover] */

/* Type: Spi_SeqEndNotification
   To provide Sequence Notification the following type will be used */
/* [cover parentID={F31E6E5D-F9D5-4119-9E08-6D8FD73E8B98}][/cover] */
/* [cover parentID={29C4896C-3F8C-4d5c-AD78-2FB83A0610DD}] */
typedef void(*Spi_SeqEndNotification)(void);
/*  [/cover] */

/* Type: Spi_SequenceConfigType
   The contents of the SPI Sequence Configuration Parameters.
   A constant variable to this structure is
   defined in Spi_PBcfg.c based on user configuration          */
typedef struct
{
  Spi_SequenceType SequenceId;

  #if((SPI_LEVEL_DELIVERED == 1U) || (SPI_LEVEL_DELIVERED == 2U))
  /* Call back function which will be called once the sequence is completed */
  Spi_SeqEndNotification SeqNotification;
  #endif

  /* Job Linked list, containing the jobs assigned to the sequence */
  const Spi_JobType *JobLinkPtrPhysical;

  #if((SPI_LEVEL_DELIVERED == 1U) || (SPI_LEVEL_DELIVERED == 2U))
  /* List of Sequences with which the given sequence shares atleast one job */
  const uint8 *SeqSharePtr;
  #endif

  /* Number Jobs assigned to the Sequence */
  uint16 NoOfJobInSeq;

  #if(SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON)
  /* Boolean parameter to specify if sequences is interruptable or not */
  uint8 SeqInterruptible;
  #endif

  /* Specifies the QSPI Hw on which the sequnces is transmitted */
  /* For Synchronous sequences,
     the value might vary for more than one QSPI Hw */
  uint8 HwModuleUsed;

  #if (MCAL_AR_VERSION == MCAL_AR_422)
  uint8 u8Comm; /* 0 - Sync, 1 - Async */
  #endif

} Spi_SequenceConfigType;

/* Type: Spi_JobConfigType
   The contents of the SPI Job Configuration Parameters.
   A constant variable to this structure is defined in
   Spi_PBcfg.c based on user configuration                        */
/* [cover parentID={2D71C467-D7AF-4d8d-A48B-62CAD6212DAB}] */
typedef struct
{
  Spi_JobType JobId;

  #if((SPI_LEVEL_DELIVERED == 1U) || (SPI_LEVEL_DELIVERED == 2U))
  /* Call back function which will be called once the sequence is completed */
  Spi_JobEndNotification JobNotification;
  #endif

  /* Upper half-word Baudrate parameter TQ, LB LoopBack support to be
     programmed in GLOBALCON SFR. Lower half-word Baudrate
     parameters(Q,A,B,C) and Clock parameter(Parity, CLK polarity, phase)   */
  uint32 BaudRateAndClockParam;

  /* Values are representation of bit field definition for
     timing delays configuration to be put in BACON SFR,
     contains additionally SLSO and parity type value      */
  uint32 IdleLeadTrailDelay;

  /* Channel link pointer with delimiter at the end */
  const Spi_ChannelType *ChnlLinkPtrPhysical;

  /* Represents Chip Select PortPin,
     If CS_VIA_HW, then it is done during Spi_Init via
     ActiveChipSelectLevel present in Spi_QspiHwConfigType */
  uint16 CSPortPin;

  /* Job Priority ranging from 0 (Lowest) to
     3 (Highest) (available only for Level 1 or 2) */
  uint8 JobPriority;

  /* CS Polarity */
  uint8 CsPolarity;

  /* Contains the QSPI module[Bit,3:0] and Hw Channel[Bit,7:4] information */
  Spi_HWUnitType HwUnit;

  /* Parity to support Even=0/Odd=1/Disabled=2 */
  uint8 ParitySupport;

  uint8 FramebasedCs;
} Spi_JobConfigType;
/*  [/cover] */

/* Type: Spi_QspiHwConfigType
   The contents of the SPI QSPI Hw Configuration Parameters.
   A constant variable to this structure is defined in
   Spi_PBcfg.c based on user configuration                        */
/* [cover parentID={BA3A46D0-85A6-4d73-810C-D113114441A0}] */
typedef struct
{
  /* Chip select configuration data type for QSPI HW, could be used
     to directly program the QSPI.SSOC SFR. Contains values of
     AOL and OEN for a particular QSPI covering all the SLSOs       */
  uint32 ActiveChipSelectLevel;


  /* Specifies the length for the job queue for the corresponding QSPI HW */
  uint16 JobQueueLength;

  #if(SPI_LEVEL_DELIVERED != 0U)

  /* DMA Channel for reception associated with the QSPI HW */
  uint8 DMARxChannel;

  /* DMA Channel for transmission associated with the QSPI HW */
  uint8 DMATxChannel;

  /* Maximum number of channels assigned to a Job */
  uint8 DMATCSCount;
  #endif /* SPI_LEVEL_DELIVERED != 0U */

  /* SPI HW Clock Setting (CLC Register - Enable QSPI Module,
     Set Sleep Settings) CLC register DISR and EDIS bits are updated */
  uint8 ClockSetting;

  /* SPI HW MRST Pin Selection Setting (PISEL Register) */
  uint8 MasterReceivePortPin;

  Spi_SequenceType MaxSequence;

  /* External Demultiplexer mode */
  uint8 ExternalDemuxEnabled;

  /* Strobe delay for SLSO0 in External Demultiplexer mode */
  uint32 StrobeDelay;

} Spi_QspiHwConfigType;
/*  [/cover] */

/* Type: Spi_ChannelConfigType
   The contents of the SPI Channel Configuration Parameters.
   A constant variable to this structure is defined in
   Spi_PBcfg.c based on user configuration                   */
/* [cover parentID={025D434E-3868-4735-A2CA-1C9DE7C95724}] */
typedef struct
{
  /* Default data to be transmitted in case NULL_PTR
   is given while setting up the buffer             */
  uint32 Defaultdata;

  /* For IB - contains number of IB data elements,
     For EB - contains maximum data elements          */
  uint16 NoOfDataElements;

  /* Specify EB/IB type */
  uint8 ChannelType;

  /* Data characteristics:
     MSB/LSB - bit[7], Data width - bit[6:0] */
  uint8 DataConfig;

  Spi_ChannelType ChannelId;


} Spi_ChannelConfigType;
/*  [/cover] */

/* Type: Spi_BufferType
   Variable of this type stores the information wrt
   buffer elements and length of transfer for each channel   */
/* [cover parentID={500106EC-20F9-47CB-9B29-7FD89FC84DE3}] */
typedef struct
{
  /* Pointer to constant source buffer */
  const Spi_DataBufferType *SrcPtr;

  /* Pointer to destination buffer */
  const Spi_DataBufferType *DestPtr;

  /* Number of data elements to be transferred */
  Spi_NumberOfDataType TransferLength;

} Spi_BufferType;

/* Type: Spi_CoreChannelOffsetType
   Variable of this will store the offset in Tx and Rx
   buffer and transfer length */
/* [cover parentID={3E2597AE-1DA7-4E4B-BB3F-2B5400DDB445}] */
typedef struct
{
  uint16 ChannelOffset;
  uint16 DataTransferLength;
} Spi_CoreChannelOffsetType;

/* [cover parentID={E44885A0-1957-4737-B4A7-1EEB54FAC397}] */
typedef struct
{
  /* Pointer to the SPI Sequence configuration */
  const Spi_SequenceConfigType *SequenceConfigPtr;

  /* Pointer to the SPI Job configuration */
  const Spi_JobConfigType *JobConfigPtr;

  /* Pointer to the SPI Channel configuration */
  const Spi_ChannelConfigType *ChannelConfigPtr;

  /* Pointer to SPI channel offset */
  const Spi_CoreChannelOffsetType *ChannelOffsetInfo;

  /* Pointers to QSPIx HW Peripheral
   Configuration x is the Max QSPI Hw available  */
  const Spi_QspiHwConfigType *QSPIHwConfigPtr[SPI_MAX_HW_UNIT];

  /* Pointer to an array, holding the Map Index of whether the
   QSPI is configured or not (wrt Asynchronous and Synchronous) */
  const Spi_QSPIHwMapConfigType QSPIHwMap;

  /* Number of Sequences configured */
  Spi_SequenceType NoOfSequences;

  /* Number of Jobs configured */
  Spi_JobType NoOfJobs;

  /* Number of Channels configured */
  Spi_ChannelType NoOfChannels;

} Spi_CoreConfigType;
/* [/cover] */

/* [cover parentID={D30C85EA-90A5-4b76-A2AB-3271FD726DA2}] */
typedef struct
{
  const Spi_CoreConfigType *CoreConfigPtr[MCAL_NO_OF_CORES];

  /* Look-up table pointer for Sequence */
  const uint8 *SequenceLookup;

  /* Look-up table pointer for jobs */
  const uint16 *JobLookup;

  /* Look-up table pointer for channels */
  const uint8 *ChannelLookup;

  /* Number of Sequences configured */
  Spi_SequenceType NoOfSequences;

  /* Number of Jobs configured */
  Spi_JobType NoOfJobs;

  /* Number of Channels configured */
  Spi_ChannelType NoOfChannels;

  /* Timeout for Synchronous transfer */
  uint32 SyncTimeout;
} Spi_ConfigType;
/* [/cover] */

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/

#define SPI_START_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
#include "Spi_MemMap.h"

/*******************************************************************************
** Syntax         : void Spi_InitCheck(const Spi_ConfigType* const  ConfigPtr)**
**                                                                            **
** Service ID      :  0x00                                                    **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Reentrant for the different core                        **
**                                                                            **
** Parameters (in) :  ConfigPtr - Pointer to configuration set                **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description     : Check for all the globals and registers to be            **
initialized as per the configuration.                                         **
*******************************************************************************/
#if (SPI_INIT_CHECK_API == STD_ON)
extern Std_ReturnType Spi_InitCheck(const Spi_ConfigType* const  ConfigPtr);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
 * compilation error, when the function is called by application and not 
 * enabled in the configuration. */
#define Spi_InitCheck(ConfigPtr) (ERROR_Spi_InitCheck_API_IS_NOT_SELECTED)
#endif /* (SPI_INIT_CHECK_API == STD_ON) */

/*******************************************************************************
** Syntax          : void Spi_Init(const Spi_ConfigType* const ConfigPtr)     **
**                                                                            **
** Service ID      : 0x00                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non reentrant                                            **
**                                                                            **
** Parameters (in) : ConfigPtr - Pointer to configuration set                 **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description : Driver Module Initialization function                        **
** Service for SPI initialization. The Initialization function shall          **
** initialize all SPI relevant registers with the values of the structure     **
** referenced by the parameter ConfigPtr.                                     **
** For Level2 this Function shall set the Handler/Driver Asynchronous         **
** Mechanism Mode in POLLING MODE and all the interrupts may be disabled      **
*******************************************************************************/
extern void Spi_Init(const Spi_ConfigType* const ConfigPtr);

/*******************************************************************************
** Syntax          : Std_ReturnType Spi_DeInit (void)                         **
**                                                                            **
** Service ID      :  0x01                                                    **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non reentrant                                           **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: de-initialization command has been accepted.       **
**                   E_NOT_OK: de-initialization command has not been accepted**
**                                                                            **
** Description : Service For SPI Deinitialization                             **
*******************************************************************************/
extern Std_ReturnType Spi_DeInit(void);

#if(SPI_CHANNEL_BUFFERS_ALLOWED != 1U)
/*******************************************************************************
** Syntax          : Std_ReturnType Spi_WriteIB                               **
**                   (                                                        **
**                     const Spi_ChannelType Channel,                         **
**                     const Spi_DataBufferType* DataBufferPtr                **
**                   )                                                        **
**                                                                            **
** Service ID      : 0x02                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant for different channels                         **
**                                                                            **
** Parameters (in) : Channel - Specifies the channel ID                       **
**                                                                            **
** Parameters (out): const DataBufferPtr* - Pointer to Source data buffer.    **
**                   If this pointer points to NULL, it is assumed that the   **
**                   data to be transmitted is not relevant and the default   **
**                   transmit value of this channel will be used instead      **
**                                                                            **
** Return value    : E_OK: specifies the data in the source buffer is copied  **
**                         into the local internal buffer                     **
**                   E_NOT_OK: requested functionality is not done            **
**                                                                            **
** Description     : This API copies the source data pointed by               **
**                   DataBufferPtr into the internal buffer of the            **
**                   SPI driver for the specified channel.                    **
*******************************************************************************/
extern Std_ReturnType Spi_WriteIB
(
  const Spi_ChannelType Channel,
  const Spi_DataBufferType * const DataBufferPtr
);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
 * compilation error, when the function is called by application and not 
 * enabled in the configuration. */
#define Spi_WriteIB(Channel, DataBufferPtr) (ERROR_Spi_WriteIB_API_IS_NOT_SELECTED)
#endif /* (SPI_CHANNEL_BUFFERS_ALLOWED != 1U) */

#if(SPI_LEVEL_DELIVERED != 0U)
/*******************************************************************************
** Syntax          : Std_ReturnType Spi_AsyncTransmit                         **
**                   (                                                        **
**                     const Spi_SequenceType Sequence                        **
**                   )                                                        **
**                                                                            **
** Service ID      : 0x03                                                     **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Re-entrant                                               **
**                                                                            **
** Parameters (in) : Sequence - Sequnece ID                                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK - Transmission command has been accepted.           **
**                   E_NOT_OK - Transmission command has been accepted.       **
**                                                                            **
** Description : Async service to transmit data on the SPI bus.               **
** This service shall take over the given parameter, initiate a transmission  **
** and set the SPI Handler/Driver status to SPI_BUSY, set the sequence result **
** to SPI_SEQ_PENDING, set the 1st job result to SPI_JOB_PENDING and return.  **
** This function is pre compile time selectable by the configuration          **
** parameter SPI_LEVEL_DELIVERED. This function is only relevant for          **
** LEVEL 1 and LEVEL 2.                                                       **
** The function allows transmitting more than one Sequence at the same time.  **
** That means during a Sequence on-going transmission, all requests           **
** to transmit another Sequence shall be evaluated, using the                 **
** lead Job, for an acceptance if different SPI buses or for set to           **
** pending state for transmission later.                                      **
** This method shall be called after a Spi_SetupEB method for EB Channels or  **
** Spi_WriteIB method for IB Channels but before the Spi_ReadIB method.       **
*******************************************************************************/
extern Std_ReturnType Spi_AsyncTransmit(const Spi_SequenceType Sequence);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
 * compilation error, when the function is called by application and not 
 * enabled in the configuration. */
#define Spi_AsyncTransmit(Sequence) (ERROR_Spi_AsyncTransmit_API_IS_NOT_SELECTED)
#endif /* (SPI_LEVEL_DELIVERED != 0U) */

#if(SPI_CHANNEL_BUFFERS_ALLOWED != 1U)
/*******************************************************************************
** Syntax          : Std_ReturnType Spi_ReadIB                                **
**                                 (                                          **
**                                  const Spi_ChannelType Channel,            **
**                                  Spi_DataBufferType* const DataBufferPtr   **
**                                 )                                          **
** Service ID      : 0x04                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Re-entrant                                               **
**                                                                            **
** Parameters (in) : Channel - Channel ID.                                    **
**                   DataBufferPtr - Pointer to destination data buffer in RAM**
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK - Read command has been accepted.                   **
**                   E_NOT_OK - Read command has not been accepted.           **
**                                                                            **
** Description : Service for reading synchronously one or more                **
** data from an IB SPI Handler/Driver Channel specified by parameter.         **
** In case of 16bit Channel Data Width the DataBufferPtr must be 16bit aligned**
** Different Jobs, consequently also Sequences, can have in common            **
** Channels. But, the use of those shared Channels is restricted. Read and    **
** Write functions can not guarantee the data integrity while Channel data is **
** being transmitted. User must ensure that Read and/or Write functions are   **
** not called during transmission.                                            **
** This method shall be called after one Transmit method call to have         **
** relevant data within IB Channel.                                           **
*******************************************************************************/
extern Std_ReturnType Spi_ReadIB
(
  const Spi_ChannelType Channel,
  Spi_DataBufferType* const DataBufferPointer
);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
 * compilation error, when the function is called by application and not 
 * enabled in the configuration. */
#define Spi_ReadIB(Channel, DataBufferPtr) (ERROR_Spi_ReadIB_API_IS_NOT_SELECTED)
#endif /* (SPI_CHANNEL_BUFFERS_ALLOWED != 1U) */

#if(SPI_CHANNEL_BUFFERS_ALLOWED != 0U)
/*******************************************************************************
** Syntax          : Std_ReturnType Spi_SetupEB                               **
**                   (                                                        **
**                     const Spi_ChannelType Channel,                         **
**                     const Spi_DataBufferType* const SrcDataBufferPtr,      **
**                     const Spi_DataBufferType* const DesDataBufferPtr,      **
**                     const Spi_NumberOfDataType Length                      **
**                   )                                                        **
** Service ID      : 0x05                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant for different channels                         **
**                                                                            **
** Parameters (in) : Channel - Channel ID.                                    **
**                   SrcDataBufferPtr - Pointer to Source data buffer         **
**                   DesDataBufferPtr - Pointer to Destination data buffer    **
**                   Length - Length of the data to be transmitted from       **
**                   SrcdataBufferPtr and/or received from DesDataBufferPtr   **
**                   Min.: 1                                                  **
**                   Max.: Max of data specified at configuration for         **
**                   this channel                                             **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK - Setup command has been accepted.                  **
**                   E_NOT_OK - Setup command has not been accepted.          **
**                                                                            **
** Description : Service to setup the buffers and the length of data          **
** for the EB SPI Handler/Driver Channel specified.                           **
** This service shall update the buffer pointers and length attributes        **
** of the specified Channel with the provided values. As these attributes are **
** persistent, they will be used for all succeeding calls to one Transmit     **
** method (for the specified Channel).                                        **
** To transmit a variable number of data, it is mandatory to call             **
** Spi_SetupEB function to store new parameters within SPI Handler/Driver     **
** before each of the Sync/Async transmit function calls.                     **
** To transmit a constant number of data, it is only mandatory to call        **
** Spi_SetupBuffers function to store parameters within SPI Handler/Driver    **
** before the first Spi_Transmit function call.                               **
** For EB Channels the application shall provide the buffering,               **
** and shall take care of the consistency of the data in the buffer during    **
** transmission. The size of the Channel buffer is either fixed or variable.  **
** A maximum size for the Channel buffer is fixed by configuration,           **
** but the size of the buffer provided by the User can change.                **
** In case of 16 bit Channel Data Width, The SrcDataBufferPtr and             **
** DesDataBufferPtr must be 16bit aligned. Different Jobs, consequently also  **
** Sequences, can have in common Channels.                                    **
** But, the use of those shared Channels is restricted. Read and              **
** Write functions can not guarantee the data integrity while Channel data is **
** being transmitted. User must ensure that Read and/or Write functions are   **
** not called during transmission.                                            **
** This method shall be called one time for all Channels with EB              **
** declared before to call a Transmit method for them.                        **
*******************************************************************************/
extern Std_ReturnType Spi_SetupEB
(
  const Spi_ChannelType Channel,
  const Spi_DataBufferType* const SrcDataBufferPtr,
  const Spi_DataBufferType* const DesDataBufferPtr,
  const Spi_NumberOfDataType Length
);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
 * compilation error, when the function is called by application and not 
 * enabled in the configuration. */
#define Spi_SetupEB(Channel, SrcDataBufferPtr, DesDataBufferPtr, Length)       \
                                        (ERROR_Spi_SetupEB_API_IS_NOT_SELECTED)
#endif /* (SPI_CHANNEL_BUFFERS_ALLOWED != 0U) */

/*******************************************************************************
** Syntax          : Spi_StatusType Spi_GetStatus(void)                       **
**                                                                            **
** Service ID      : 0x06                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Re-entrant                                               **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : SPI_UNINIT: The SPI Handler/Driver is not initialized.   **
**                   SPI_IDLE : The SPI Handler/Driver is not currently       **
**                   transmitting any Job.                                    **
**                   SPI_BUSY: The SPI Handler/Driver is performing a SPI     **
**                   Job (transmit).                                          **
**                                                                            **
** Description : This service shall return the                                **
** SPI Handler/Driver status.                                                 **
*******************************************************************************/
extern Spi_StatusType Spi_GetStatus(void);

/*******************************************************************************
** Syntax          : Spi_JobResultType Spi_GetJobResult(const Spi_JobType Job)**
**                                                                            **
** Service ID      : 0x07                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Re-entrant                                               **
**                                                                            **
** Parameters (in) : Job - Job ID. An invalid job ID will                     **
**                   return an undefined result.                              **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Spi_JobResultType - status of the job                    **
**                   returns SPI_JOB_FAILED for any errors                    **
**                                                                            **
** Description : This service shall return the last transmission result       **
** of the specified Job.                                                      **
** The user shall call Spi_GetJobResult() method to know if the Job           **
** transmission succeeded (SPI_JOB_OK) or failed (SPI_JOB_FAILED)             **
*******************************************************************************/
extern Spi_JobResultType Spi_GetJobResult(const Spi_JobType Job);

/*******************************************************************************
** Syntax          : Spi_SeqResultType Spi_GetSequenceResult                  **
**                         (const Spi_SequenceType Sequence)                  **
**                                                                            **
** Service ID      : 0x08                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Re-entrant                                               **
**                                                                            **
** Parameters (in) : Sequence - Sequence ID. An invalid sequence ID will      **
**                   return an undefined result.                              **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Spi_SeqResultType - status of the Sequence               **
**                   returns SPI_SEQ_FAILED for any errors                    **
**                                                                            **
** Description : This service shall return the last transmission result       **
** of the specified Sequence                                                  **
** The user shall call Spi_GetSequenceResult() method to know if the          **
** full Sequence transmission succeeded (SPI_SEQ_OK) or failed                **
*******************************************************************************/
extern Spi_SeqResultType Spi_GetSequenceResult(const Spi_SequenceType Sequence);

#if (SPI_CONTROL_LOOPBACK_API == STD_ON)
/*******************************************************************************
** Syntax          : Std_ReturnType Spi_ControlLoopBack                       **
**      (const Spi_HWUnitType HWUnit, const Spi_LoopBackType EnableOrDisable) **
**                                                                            **
** Service ID      : 0x25                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant for different QSPI HW                          **
**                                                                            **
** Parameters (in) :   HWUnit - QSPI Hw Unit                                  **
**                     EnableOrDisable : Enable or disable loopback mode      **
**                     SPI_LOOPBACK_ENABLE : Loopback Enable                  **
**                     SPI_LOOPBACK_DISABLE : Loopback Disable                **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK, If Loopback mode is enabled/disabled successful    **
**                   E_NOT_OK, otherwise.                                     **
**                                                                            **
** Description     : This API enables/disables the Loopback mode              **
*******************************************************************************/
extern Std_ReturnType Spi_ControlLoopBack(const Spi_HWUnitType HWUnit,
                                        const Spi_LoopBackType EnableOrDisable);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
 * compilation error, when the function is called by application and not 
 * enabled in the configuration. */
#define Spi_ControlLoopBack(HWUnit, EnableOrDisable) \
                                 (ERROR_Spi_ControlLoopBack_API_IS_NOT_SELECTED)
#endif /* (SPI_CONTROL_LOOPBACK_API == STD_ON) */

/*******************************************************************************
** Syntax          : Std_ReturnType Spi_SyncTransmit                          **
**                        (                                                   **
**                           const Spi_SequenceType Sequence                  **
**                        )                                                   **
** Service ID      :  0x0A                                                    **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Re-entrant                                              **
**                                                                            **
** Parameters (in) : Sequence - Sequnece ID                                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK - Transmission command has been accepted.           **
**                   E_NOT_OK - Transmission command has been accepted.       **
**                                                                            **
** Description : Sync Service to transmit data on the SPI bus .               **
** This service shall take over the given parameter, initiate a transmission, **
** and set the SPI Handler/Driver status to SPI_BUSY, set the sequence result **
** to SPI_SEQ_PENDING, set the first job result to SPI_JOB_PENDING and return.**
** The LEVEL 0 SPI Handler/Driver shall offer a synchronous transfer          **
** service for SPI busses. When there is no on-going Sequence transmission,   **
** the SPI Handler/Driver shall be in idle state (SPI_IDLE).                  **
** Hence, the LEVEL 0 SPI Handler/Driver shall not allow transmitting         **
** more than one Sequence at the same time. That means during a Sequence      **
** on-going transmission, all requests to transmit another Sequence shall be  **
** rejected.                                                                  **
** The LEVEL 2 SPI Handler/Driver shall offer a synchronous transfer          **
** service for a dedicated SPI bus and it shall also offer an asynchronous    **
** transfer service for others SPI busses. When there is no on-going Sequence **
** transmission, the SPI Handler/Driver shall be in idle state (SPI_IDLE).    **
*******************************************************************************/
#if(SPI_LEVEL_DELIVERED != 1U)
extern Std_ReturnType Spi_SyncTransmit(const Spi_SequenceType Sequence);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
 * compilation error, when the function is called by application and not 
 * enabled in the configuration. */
#define Spi_SyncTransmit(Sequence) (ERROR_Spi_SyncTransmit_API_IS_NOT_SELECTED)
#endif /* SPI_LEVEL_DELIVERED != 1) */

#if (SPI_HW_STATUS_API == STD_ON)
/*******************************************************************************
** Syntax          : Spi_StatusType Spi_GetHWUnitStatus                       **
**                   (                                                        **
**                      const Spi_HWUnitType  HWUnit                          **
**                   )                                                        **
** Service ID      : 0x0B                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : reentrant                                                **
**                                                                            **
** Parameters (in) : HWUnit- SPI Bus identifier                               **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value    : SPI_UNINIT - The QSPI Hardware is not initialized        **
**                   or not usable                                            **
**                   SPI_IDLE - The QSPI Hardware is not currently            **
**                   transmitting any Job                                     **
**                   SPI_BUSY - The QSPI Hardware is performing a SPI         **
**                   Job(transmit)                                            **
**                                                                            **
** Description : This service shall return the status of the specified        **
** SPI Hardware microcontroller peripheral. The user shall call               **
** Spi_GetHWUnitStatus()  method to know if the specified SPI Hardware        **
** microcontroller peripheral is SPI_IDLE or SPI_BUSY.                        **
** This function is pre compile time configurable                             **
** On / Off by the configuration parameter: SPI_HW_STATUS_API.                **
** Note that the HW Bus is busy only if a Job is running on it.If the HW Bus  **
** is Idle it can be assumed that no job is running on it currently but a job **
** could be pending and can be scheduled to run on the bus later              **
*******************************************************************************/
extern Spi_StatusType Spi_GetHWUnitStatus(const Spi_HWUnitType HWUnit);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
 * compilation error, when the function is called by application and not 
 * enabled in the configuration. */
#define Spi_GetHWUnitStatus(HWUnit) (ERROR_Spi_GetHWUnitStatus_API_IS_NOT_SELECTED)
#endif /* (SPI_HW_STATUS_API == STD_ON) */

#if(SPI_CANCEL_API == STD_ON)
/*******************************************************************************
** Syntax:         : void Spi_Cancel                                          **
**                   (                                                        **
**                     const Spi_SequenceType Sequence                        **
**                   )                                                        **
** Service ID      : 0x0C                                                     **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : reentrant                                                **
**                                                                            **
** Parameters (in) : Sequence                                                 **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value    : none                                                     **
**                                                                            **
** Description : This service shall cancel the specified on-going             **
** sequence transmission without cancelling any Job transmission and the SPI  **
** Handler/Driver will set the sequence result to SPI_SEQ_CANCELED.           **
** The SPI Handler/Driver is not responsible on external devices damages or   **
** undefined state due to cancelling a sequence transmission. It is up to the **
** user to be aware of what user is doing!                                    **
*******************************************************************************/
extern void Spi_Cancel(const Spi_SequenceType Sequence);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
 * compilation error, when the function is called by application and not 
 * enabled in the configuration. */
#define Spi_Cancel(Sequence) (ERROR_Spi_Cancel_API_IS_NOT_SELECTED)
#endif /* (SPI_CANCEL_API = STD_ON) */

#if (SPI_LEVEL_DELIVERED == 2U)
/*******************************************************************************
** Syntax          : Std_ReturnType Spi_SetAsyncMode                          **
**                   (                                                        **
**                    const Spi_AsyncModeType Mode                            **
**                   )                                                        **
** Service ID      : 0x0D                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in) : Mode                                                     **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value    : E_OK -     command has been accepted.                    **
**                   E_NOT_OK - command has not been accepted.                **
**                                                                            **
** Description :This function is pre compile time selectable by the           **
** configuration parameter: SPI_LEVEL_DELIVERED. This function is only        **
** relevant for LEVEL 2.                                                      **
** This function is pre compile time selectable by the configuration          **
** parameter: SPI_LEVEL_DELIVERED. This function is only relevant for LEVEL 2 **
** The SPI Handler/Driver LEVEL 2 shall implemented one                       **
** polling mechanism mode and one interrupt mechanism mode for SPI busses     **
** handled asynchronously. Both mechanisms are selectable during              **
** execution time                                                             **
*******************************************************************************/
extern Std_ReturnType Spi_SetAsyncMode(const Spi_AsyncModeType Mode);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
 * compilation error, when the function is called by application and not 
 * enabled in the configuration. */
#define Spi_SetAsyncMode(Mode) (ERROR_Spi_SetAsyncMode_API_IS_NOT_SELECTED)
#endif /* (SPI_LEVEL_DELIVERED == 2U) */

#if(SPI_LEVEL_DELIVERED != 0U)
/*******************************************************************************
** Syntax          : void Spi_IsrQspiError(const uint8 Module)                **
**                                                                            **
** Service ID      : 0x23                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant for different QSPI HW                          **
**                                                                            **
** Parameters (in) : Module - QSPI module index                               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : This interrupt service routine handles the QSPI errors   **
**                   during asynchronous transmission. Sets the status of     **
**                   the Sequence to SPI_SEQ_FAILED and job status belonging  **
**                   to the sequence except which are completed to            **
**                   SPI_JOB_FAILED.                                          **
*******************************************************************************/
extern void Spi_IsrQspiError(const uint8 Module);

/*******************************************************************************
** Syntax          : void Spi_QspiDmaCallout(const uint8 Channel,             **
**                     const uint32 Event)                                    **
**                                                                            **
** Service ID      : 0x21                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant for different QSPI HW                          **
**                                                                            **
** Parameters (in) : Module - QSPI module index                               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : Called by DMA module on Rx / Tx interrupt
*******************************************************************************/
extern void Spi_QspiDmaCallout
(const uint8 Channel, const uint32 Event);
/*******************************************************************************
** Syntax          : void Spi_QspiDmaErrCallout(const uint8 Channel,          **
**                              const uint32 Event)                           **
**                                                                            **
** Service ID      : 0x24                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant for different QSPI HW                          **
**                                                                            **
** Parameters (in) : Channel - DMA channel number                             **
**                   Event - DMA Kernel  event                                **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : Invokes QSPI module specific ISRs                        **
*******************************************************************************/
extern void Spi_QspiDmaErrCallout
(const uint8 Channel, const uint32 Event);

/*******************************************************************************
** Syntax          : void Spi_IsrQspiPT2(const uint8 Module)                  **
**                                                                            **
** Service ID      : 0x22                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant for different QSPI HW                          **
**                                                                            **
** Parameters (in) : Module - QSPI module index                               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : Handles the QSPI Phase transition interrupt              **
*******************************************************************************/
extern void Spi_IsrQspiPT2(const uint8 Module);
#endif /* SPI_LEVEL_DELIVERED != 0U */

#if(SPI_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Syntax           : void  Spi_GetVersionInfo                                **
**                    (                                                       **
**                      Std_VersionInfoType * const versioninfo               **
**                    )                                                       **
**                                                                            **
** Service ID       : 0x09                                                    **
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
**   - This function returns the version information of this module           **
**     The version information include : Module ID, Vendor ID,                **
**     Vendor specific version numbers                                        **
**   - This function is available if the SPI_VERSION_INFO_API is set STD_ON   **
*******************************************************************************/
extern void Spi_GetVersionInfo(Std_VersionInfoType * const versioninfo);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
 * compilation error, when the function is called by application and not 
 * enabled in the configuration. */
#define Spi_GetVersionInfo(versioninfo) (ERROR_Spi_GetVersionInfo_API_IS_NOT_SELECTED)
#endif /* End for SPI_VERSION_INFO_API */

#define SPI_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
 * guideline. */
#include "Spi_MemMap.h"

#include "Spi_PBcfg.h"

#endif /* SPI_H */
/* End Of File */
