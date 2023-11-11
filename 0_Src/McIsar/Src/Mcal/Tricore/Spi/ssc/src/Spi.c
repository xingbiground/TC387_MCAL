/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2023)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : Spi.c                                                      **
**                                                                            **
**  VERSION      : 55.0.0                                                     **
**                                                                            **
**  DATE         : 2023-05-23                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Spi Driver source file                                     **
**                                                                            **
**  SPECIFICATION(S) : Specification of Spi Driver, AUTOSAR Release 4.2.2     **
**                     Specification of Spi Driver, AUTOSAR Release 4.4.0     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
  TRACEABILITY : [cover parentID={36369FEE-198F-4830-8AC3-FC974DFDA4C9}][/cover]
*******************************************************************************/
/* [cover parentID={7C35F255-0050-45c9-9E36-A1955AB1863B}][/cover] */
/* [cover parentID={F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}][/cover] */
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/* [cover parentID={2436DE99-75DC-4335-A759-DD23D7091616}] No SRC
register accessed [/cover] */
/* Include own header file */
#include "Spi.h"

#include "Std_Types.h"

/* Include QSPI SFR Header file */
#include "IfxQspi_reg.h"
#include "IfxQspi_bf.h"

#if(SPI_LEVEL_DELIVERED != 0U)
#include "IfxDma_bf.h"
#include "IfxDma_reg.h"
#endif

/* Include Port SFR file to access OMR register for CS_VIA_GPIO */
#include "IfxPort_reg.h"

/* Inclusion of Mcal_Wrapper.h */
#if((SPI_HW_ERROR_DEM_REPORT == SPI_DEM_REPORT_ENABLED) || (SPI_RUNTIME_ERROR_DETECT == STD_ON))
#include "Mcal_Wrapper.h"
#endif

/* [cover parentID={50933CF9-6589-450c-9A31-477BEEFC80EB}][/cover] */
#if((SPI_DEV_ERROR_DETECT == STD_ON) || (MCAL_AR_VERSION == MCAL_AR_440))
#include "Det.h"
#endif

/* Critical section protection header file */
#include "SchM_Spi.h"

/*User Mode and Supervisor Mode Macros*/
#if( (SPI_INIT_DEINIT_API_MODE != SPI_MCAL_SUPERVISOR)||\
     (SPI_RUN_TIME_API_MODE != SPI_MCAL_SUPERVISOR) )
#include "McalLib_OsStub.h"
#endif

#if (SPI_SAFETY_ENABLE == STD_ON)
#include "Mcal_SafetyError.h"
#endif
#include "IfxCpu_reg.h"
/*******************************************************************************
**                      Imported Compiler Switch Checks                       **
*******************************************************************************/
#ifndef SPI_SW_MAJOR_VERSION
#error "SPI_SW_MAJOR_VERSION is not defined."
#endif

#ifndef SPI_SW_MINOR_VERSION
#error "SPI_SW_MINOR_VERSION is not defined."
#endif

#ifndef SPI_SW_PATCH_VERSION
#error "SPI_SW_PATCH_VERSION is not defined."
#endif

#if(SPI_SW_MAJOR_VERSION != 20U)
#error "SPI_SW_MAJOR_VERSION does not match."
#endif

#if(SPI_SW_MINOR_VERSION != 25U)
#error "SPI_SW_MINOR_VERSION does not match."
#endif

#if(SPI_SW_PATCH_VERSION != 0U)
#error "SPI_SW_PATCH_VERSION does not match."
#endif

/* AUTOSAR Secification File Version Check */
#ifndef SPI_AR_RELEASE_MAJOR_VERSION
#error "SPI_AR_RELEASE_MAJOR_VERSION is not defined."
#endif

/* [cover parentID={795888B7-6661-4e89-9B1C-495A156B555F}]
AUTOSAR Major and Minor release version check [/cover] */
#if(SPI_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION)
#error "SPI_AR_RELEASE_MAJOR_VERSION does not match."
#endif

/* AUTOSAR Secification File Version Check */
#ifndef SPI_AR_RELEASE_MINOR_VERSION
#error "SPI_AR_RELEASE_MINOR_VERSION is not defined."
#endif


#if(SPI_AR_RELEASE_MINOR_VERSION != MCAL_AR_RELEASE_MINOR_VERSION)
#error "SPI_AR_RELEASE_MINOR_VERSION does not match."
#endif

/* AUTOSAR Secification File Version Check */
#ifndef SPI_AR_RELEASE_REVISION_VERSION
#error "SPI_AR_RELEASE_REVISION_VERSION is not defined."
#endif


#if(SPI_AR_RELEASE_REVISION_VERSION != MCAL_AR_RELEASE_REVISION_VERSION)
#error "SPI_AR_RELEASE_REVISION_VERSION does not match."
#endif

/* Inter Module Check for the correct version usage in the used modules */

/* [cover parentID={7DAC82BA-49FC-4584-B98C-7A9927665691}]
Version Check [/cover] */
/* Version check for DET module inclusion */
#if(SPI_DEV_ERROR_DETECT == STD_ON)

#ifndef DET_AR_RELEASE_MAJOR_VERSION
#error "DET_AR_RELEASE_MAJOR_VERSION is not defined."
#endif

#if (DET_AR_RELEASE_MAJOR_VERSION != SPI_AR_RELEASE_MAJOR_VERSION)
#error "DET_AR_RELEASE_MAJOR_VERSION does not match."
#endif

#endif /* SPI_DEV_ERROR_DETECT == STD_ON */

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
#define SPI_FIFO_ENTRY                  (0x00U)


/* MISRA2012_RULE_2_5_JUSTIFICATION: Used in multiple configuration
combination */
#define SPI_DMA_ADICR_DEST_NULL         (0x03C1080U)

/* All kernel types */
#define SPI_TOTAL_KERNEL_TYPE_BITS      (0x03U)
#if(SPI_LEVEL_DELIVERED != 1U)
#define SPI_SYNC_KERNEL                 (0x01U)
/* Comms type supported */
#define SPI_SYNC_COMMS_TYPE             (0U)
#endif
#define SPI_KERNEL_TYPE_MASK            (0x03U)

/* Enable / Disable DET reporting */
/* MISRA2012_RULE_2_5_JUSTIFICATION: Used in multiple configuration
combination */
#define SPI_REPORT_DET                  (1U)
#define SPI_DET_DISABLE                 (0U)

/* MISRA2012_RULE_2_5_JUSTIFICATION: Used in multiple configuration
combination */
#define SPI_IGNORE_COMMS_TYPE_CHECK     (4U)

/* Core Definition */
#define CORE0                           (0U)
#define CORE1                           (1U)
#define CORE2                           (2U)
#define CORE3                           (3U)
#define CORE4                           (4U)
#ifdef SPI_CORE5_ENABLE
#define CORE5                           (5U)
#endif

#if(SPI_LEVEL_DELIVERED != 0U)
#define SPI_MOVE_COUNTER_LIMIT          (8190U)
#define SPI_ASYNC_KERNEL                (0x02U)
#define SPI_WAIT_STATE                  (0x05U)
#define SPI_TRIGGER_ENABLE              (0x01U)
#define SPI_RETAIN_ICH_BIT_STATUS       (0x01U)
#define SPI_ASYNC_COMMS_TYPE            (1U)
#define SPI_SKIP_JOB_VAL             ((uint16)0x8000U)
/* Fixed value of ADICR based on Source and destination pointers */
#define SPI_DMA_ADICR_SRC_NULL          (0x03C0000U)
#endif
/* MISRA2012_RULE_2_5_JUSTIFICATION: Used only in TC39x */
#define SPI_KERNEL5                     (5U)
/* Kernel Definition for SPI */
#define SPI_KERNEL0                     (0U)
#define SPI_KERNEL1                     (1U)
#define SPI_KERNEL2                     (2U)
#define SPI_KERNEL3                     (3U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Used only in TC37x, TC38x and TC39x */
#define SPI_KERNEL4                     (4U)
/* Base Address for the QSPI Hw module instances (usually, 0xF0001C00) */
#define SPI_HW_MODULE    ((volatile Ifx_QSPI*)(volatile void*)&(MODULE_QSPI0))

/* Base address of the port pin P00 */
#define SPI_PORT_BASE_ADDR    ((volatile Ifx_P*)(volatile void*)&(MODULE_P00))

/* Number ECON SFR per QSPI HW */
#define SPI_MAX_ECON_CHANNEL         (8U)

/* value to disable the Clock */
#define SPI_QSPI_CLC_DISR_DISABLE    (0x00000001U)

/* Reset value for the SFR, PISEL */
#define SPI_PISEL_RST_VAL            (0x00000000U)

/* Resest value for the SFR, SSOC */
#define SPI_SSOC_RST_VAL             (0x00000000U)

/* Reset value for the SFR, GLOBALCON */
#define SPI_GLOBALCON_RST_VAL        (0x000F30FFU)

/* Reset value for the SFR, GLOBALCON1 */
#define SPI_GLOBALCON1_RST_VAL       (0x00050000U)

/* Reset value for the SFR, ECON */
#define SPI_ECON_RST_VAL             (0x00001450U)

/* Reset value for the SFR, FLAGSCLEAR */
#define SPI_FLAGSCLEAR_RST_VAL       (0x00009FFFU)

/* 32-Bit mask for bit fields [3:0] */
#define SPI_BIT_MASK_3_TO_0          (0x0000000FU)

/* 32-Bit mask for bit fields [6:0] */
#define SPI_BIT_MASK_6_TO_0          (0x0000007FU)

/* GLOBALCON default value */
/* Set MS = 0, EN = 1, EXPECT = 0xF , SRF = 1 */
#define SPI_GLOBALCON_VAL            (0x21203C00U)

#if(SPI_LEVEL_DELIVERED != 0U)
#define SPI_GLOBALCON1_INT_MASK      (0x000017FFU)
#endif
/* GLOBALCON1 */
/* PT2 set */
/* Set, TxFM = RxFM = 1(Single Move mode)
        Disable peripheral interrupts    */
#define SPI_GLOBALCON1_VAL           (0x17000000U)
/* DEL0 GLOBALCON */
#define SPI_GLOBALCON_DEL0_SET       (0x00008000U)
/* STROBE bit shift */
#define SPI_STROBE_SHIFT (0x10U)

/* Defines for FLAGSCLEAR register */
#define SPI_QSPI_FLAGSCLEAR_VALUE    (0x00000FFFU)

#if(SPI_LEVEL_DELIVERED != 1U)
#define SPI_TXF_RXFIFO_MASK          (0x00380200U)
/* TXF is Set and 1 FIFO level is received */
#define SPI_TXF_RXFIFO_1_SET         (0x00080200U)
#define SPI_HW_ERROR_MASK            (0x0000007FU)
#endif

/* HW channels vary from 0 - 15
   but the ECON maps 8 - 15 to 0 to 7.   */
#define SPI_QSPI_ECON_CH_MASK        (0x7U)

#if(SPI_LEVEL_DELIVERED != 0U)

#if(SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON)
/* 12-bit shift value */
#define SPI_SEQ_INTERRUPTABLE_BIT_OFFSET             (12U)
#define SPI_SEQ_PROP_COMP (1U)
#endif
#define SPI_BIT_MASK_9_TO_8          (0x00000300U)
#define SPI_JOBS_OF_DIFF_SEQ   (1U)
#define SPI_JOBS_OF_SAME_SEQ   (0U)
#define SPI_SEQ_ID_COMP (0U)
#define SPI_BOTH_SEQ_INTERRUPTABLE (1U)
#define SPI_ONE_SEQ_NON_INTERRUPTABLE (0U)
#define SPI_JOB_NOT_TO_INSERT (0U)
#define SPI_JOB_TO_INSERT (1U)

/* 8-bit shift value */
#define SPI_JOB_PRIORITY_BIT_OFFSET              (8U)

#define SPI_DMA_ENABLE_INTR          ((uint8)0x02U)
/* DMA RX Channel Address Control Reg Value :
   Dest Address  Increment : 1*CHDW
   Src  Address  Increment : 0
   CBLD = 0xF; INCD =1; SMF = DMF = 0 i.e 1*CHDW (i.e.CHCRxz.CHDW)
*/
#define SPI_DMA_RX_ADICR_VAL         (0x003CF080U)

/* DMA TX Channel Address Control Reg Value :
   Src  Address  Increment : 1*CHDW
   Dest  Address  Increment : 0
   CBLS = 0xF; INCS =1; SMF = DMF = 1*CHDW
*/
#define SPI_DMA_TX_ADICR_VAL         (0x003C0F08U)

#define SPI_DMA_TX_CHANNEL           (1U)

#define SPI_DMA_RX_CHANNEL           (0U)

/* Enable error interrupts */
#define SPI_GLOBALCON1_ERROREN       (0x0000007FU)

/* GLOBALCON1 */
/* Set, TxFM = RxFM = 1(Single Move mode)
   Enable peripheral interrupts TXEN = RXEN = PT2EN = 1 */
#define SPI_GLOBALCON1_ASYNC_VAL     (0x0000067FU)

#define SPI_BIT_MASK_7_TO_0          (0x000000FFU)
#endif

#if(SPI_LEVEL_DELIVERED == 2U)
#define SPI_DMA_DISABLE_INTR         ((uint8)0U)
#endif

/* To determine if data width > 16 */
#define SPI_16BIT_DATAWIDTH          ((uint8)16U)

/* To determine if data width > 8 */
#define SPI_8BIT_DATAWIDTH           ((uint8)8U)

/* Shift by 7 bits */
#define SPI_DATA_SHIFT_DIRECTION_BIT_OFFSET   (7U)

/* QSPI Hw unit mask bit[3:0] */
#define SPI_HWUNIT_MASK              ((uint8)0x0FU)

#define SPI_LOWER_HALF_WORD_MASK     (0x0000FFFFU)

/* 16-bit shift value */
#define SPI_GLOBALCON_LOWER_WORD_OFFSET      (16U)

#if(SPI_CHANNEL_BUFFERS_ALLOWED != 1U)
/* Channel data width offset */
#define SPI_DATAWIDTH_BITS_OFFSET             (4U)
#endif

/* Port number offset */
#define SPI_PORT_NUM_OFFSET                  (4U)

/* HW SLSO channel offset */
#define SPI_SLSO_CHANNEL_NUM_OFFSET          (4U)

/*******************************************************************************
**                         User Mode Macros                                   **
*******************************************************************************/
/* [cover parentID={A21FB581-44C4-473a-8B92-2FE1091D3207}][/cover] */
/* [cover parentID={1A65EADD-AFD0-4845-B2D2-8257E086DD67}] User mode[/cover] */
#if defined (SPI_MCAL_SUPERVISOR) || defined (SPI_MCAL_USER1)
#if(SPI_INIT_DEINIT_API_MODE == SPI_MCAL_SUPERVISOR)
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for
   User mode support in code. No side effects foreseen by violating this MISRA
   rule. */
#define SPI_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(RegAdd,Data)   \
    Mcal_WritePeripEndInitProtReg(RegAdd,Data)

/* Supervisory mode registers */
  /* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
   * SPI_SFR_INIT_DEINIT_WRITE32
   * defined for User mode support in code.
   * No side effects foreseen by violating this MISRA rule. */
  #define SPI_SFR_INIT_DEINIT_WRITE32(reg, value) (*(reg) = (uint32)(value))
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro is defined for
   User mode support in code. No side effects foreseen by violating this MISRA
   rule. */
#define SPI_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(RegAdd,Data)   \
    MCAL_LIB_WRITEPERIPENDINITPROTREG(RegAdd,Data)

/* Supervisory mode registers */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
* SPI_SFR_INIT_DEINIT_WRITE32
* defined for User mode support in code.
* No side effects foreseen by violating this MISRA rule. */
#define SPI_SFR_INIT_DEINIT_WRITE32(reg, value)    \
            MCAL_SFR_OS_WRITE32(SPI_MODULE_ID, reg, value)
#endif
#endif

#if defined (SPI_MCAL_SUPERVISOR) || defined (SPI_MCAL_USER1)
#if(SPI_RUN_TIME_API_MODE == SPI_MCAL_SUPERVISOR)
/* Supervisory mode registers */
  /* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
   * SPI_SFR_RUN_TIME_WRITE32
   * defined for User mode support in code.
   * No side effects foreseen by violating this MISRA rule. */
  #define SPI_SFR_RUN_TIME_WRITE32(reg, value) (*(reg) = (uint32)(value))
#else
/* Supervisory mode registers */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
* SPI_SFR_RUN_TIME_WRITE32
* defined for User mode support in code.
* No side effects foreseen by violating this MISRA rule. */
#define SPI_SFR_RUN_TIME_WRITE32(reg, value)    \
            MCAL_SFR_OS_WRITE32(SPI_MODULE_ID, reg, value)
#endif
#endif
/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/
/* [cover parentID={9FB4DBC2-B742-48B6-9A1C-1162B81BA31A}] */
/* Type : SpiCommsTypes
   This type defines a range of communication supported in QSPI module */
typedef enum
{
  SPI_SYNC_COMMS = 1,
  SPI_ASYNC_COMMS,
  SPI_BOTH
} SpiCommsTypes;

#if(SPI_LEVEL_DELIVERED != 0U)
/* Type: Spi_JobAndSeqQueueType
   Holds the JobId(s) for QSPIx HW.
   Holds the job properties like priority, Sequenceid for the corresponding
   JobId.
   It is a pointer to an array of size [SPI_JOB_QUEUE_LENGTH_QSPIx]      */
/* [cover parentID={939E5A2B-9D5F-4810-A235-9CB877D64FCD}] */
typedef struct
{
  /* Holds the JobId(s) into the queue which are on a particular QSPIx HW */
  Spi_JobType QueueJobId;

  /* Holds the Sequenceid for the corresponding JobId ([7:0] lower 8 bits),
     priority of the job ([9:8] 2-bits) and
     sequence interruptible flag (12th bit position).
     Bit [15],
     If the Sequence needs to be skipped
     Bit [12],
     Non_Interruptible = 0,
     Interruptible = 1
     Bit [9:8],
     JobPriotrity: 00B, 01B, 10B, 11B
     Eg, If Sequence S1(ID = 16) has Job J1(ID = 8) with priority 2
     QueueJobId  = 0x0008H (uint16)
     JobProperty = 0x0210H (Non_Interruptible)
     JobProperty = 0x1210H (Interruptible)                              */
  uint16 JobProperty;

} Spi_JobAndSeqQueueType;

/* [cover parentID={041DEDE2-2401-44e3-927E-984946A802CF}] */
/* Type: Spi_DmaTCSType
   DMA-TCS - Note that this must be aligned to 32-byte boundary. */
typedef struct
{
  Ifx_DMA_CH_RDCRCR DmaRDCRC; /* RD CRC */
  Ifx_DMA_CH_SDCRCR DmaSDCRC; /* SD CRC */
  Ifx_DMA_CH_SADR DmaSADR;    /* Source Address */
  Ifx_DMA_CH_DADR DmaDADR;    /* Destination Address */
  Ifx_DMA_CH_ADICR DmaADICR;  /* Control register */
  Ifx_DMA_CH_CHCFGR DmaCHCFGR;/* Channel Configuration register */
  Ifx_DMA_CH_SHADR DmaSHADR;  /* Shadow register */
  Ifx_DMA_CH_CHCSR DmaCHCSR;  /* Channel status register */
} Spi_DmaTCSType;

/* Type: Spi_QueueType
   Structure which processes the Job trnasmission requests */
/* [cover parentID={487ABEF5-4879-4716-BEC6-46B7A2FE3E4F}] */
typedef struct
{
  /* Holds the JobId(s) into the queue which are on a particular QSPIx HW.
     Holds the Sequenceid for the corresponding JobId.
     It is a pointer to an array of size [SPI_JOB_QUEUE_LENGTH_QSPIx]     */
  Spi_JobAndSeqQueueType *JobAndSeqQueuePtr;

  /* Temporary array variable holding jobs and
     sequence information while re-scheduling.
     It is a pointer to an array of size [SPI_JOB_QUEUE_LENGTH_QSPIx]     */
  Spi_JobAndSeqQueueType *JobAndSeqQueueRearrangePtr;

  /* This array acts as the transaction control set
     for the Tx Dma channel associated with QSPIz.
     It is a pointer to an array of size [SPI_DMA_MAX_TCS_NUM_QSPIz]      */
  Spi_DmaTCSType *DmaTxTCSPtr;

  /* This array acts as the transaction control set
     for the Rx Dma channel associated with QSPIz.
     It is a pointer to an array of size [SPI_DMA_MAX_TCS_NUM_QSPIz]      */
  Spi_DmaTCSType *DmaRxTCSPtr;

  /* Points to the current Job Id to be transmitted */
  Spi_JobType QueueStartIndex;

  /* Points to the last Job Id to be transmitted which is still in the Queue */
  Spi_JobType QueueEndIndex;

  /* Variable to point the current job index of a sequence being transmitted
     in the queue. Available if all the Sequences are non-interruptible    */
  Spi_JobType CurrentJobIndex;

  /* Variable to point the current channel index in a job */
  Spi_ChannelType CurrentChannelIndex;

} Spi_QueueType;
#endif /* SPI_LEVEL_DELIVERED != 0U */

/* [cover parentID={37D6305E-A8F3-4419-8452-729B45C311D5}] */
typedef struct
{
#if(SPI_LEVEL_DELIVERED != 0U)
  /* Job Queue Ptr */
  Spi_QueueType *JobQueuePtr;

  /* Async Communication status of kernel */
  Spi_StatusType AsyncComStatus;

  /* Dummy variable used to read data from QSPI when RX buffer is NULL */
  uint32 DummyRead;

  Ifx_QSPI_BACON *BaconChannelArray;
#endif
  /* Variable to hold the kernel status */
  Spi_StatusType KernelStatus;

} Spi_RuntimeKernelType;

/* [cover parentID={21BD6BE8-BB4F-4e98-B43A-62CEFD39C1C0}] */
typedef struct
{
  /* Lock to indicate if independent bus us busy transmitting for
  Sync transfer */
  uint32 KernelLock;

  #if (SPI_LEVEL_DELIVERED == 2U)
  /* This variable specifies the asynchronous mode
     for the transmission of a sequence in Level 2 */
  Spi_AsyncModeType AsyncMode;
  #endif

  /* Sequence result array */
  Spi_SeqResultType *SeqStatus;

  /* Job result array */
  Spi_JobResultType *JobStatus;

  /* Pointer to TX array */
  const Spi_DataBufferType *TxBuffer;

  /* Pointer to RX array */
  const Spi_DataBufferType *RxBuffer;

  /* Buffer pointer table */
  Spi_BufferType *ChannelBufPointers;
} Spi_RunTimeCoreConfigType;
/*  [/cover] */

/*******************************************************************************
**                     Private Function Declaration                           **
*******************************************************************************/
/* [cover parentID={9434323F-821F-4f9f-8643-2734E74E5311}] Header file structure
[/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}] Memory section
Definition
[/cover] */
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}] Memory map for
constants
[/cover] */
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}] Memmap section
for code [/cover] */
/* [cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}] Callout
memmap [/cover] */
#define SPI_START_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Spi_MemMap.h"
static void Spi_lAsyncInitPtrRuntimeVar(const uint8 Hwkernel);
#if(SPI_HW_ERROR_DEM_REPORT == SPI_DEM_REPORT_ENABLED)
static void Spi_lReportDemError(Dem_EventIdType EventId,
                                 Dem_EventStatusType EventStatus);
#endif
static uint8 Spi_lGetChannelDataWidth(
        const Spi_ChannelConfigType* const ChnlConfigPtr);
static void Spi_lClearMem(uint8 *const BufferPtr, const uint32 BufferSize);
#if (((MCAL_AR_VERSION == MCAL_AR_422) && ((SPI_DEV_ERROR_DETECT == STD_ON) || \
(SPI_SAFETY_ENABLE == STD_ON))) ||((MCAL_AR_VERSION == MCAL_AR_440) && \
(SPI_RUNTIME_ERROR_DETECT == STD_ON)))
static void Spi_lReportRuntimeDetError(const uint8 ApiId, const uint8 ErrorId);
#endif
#if(SPI_DEV_ERROR_DETECT == STD_ON) || (SPI_SAFETY_ENABLE == STD_ON)
static void Spi_lReportError(const uint8 ApiId, const uint8 ErrorId);
static Std_ReturnType Spi_lCheckChannelParam(const uint8 Api,
                                             uint8 * const Channel,
             const uint8 ApplicationChannelNumber, const uint8 BufEbIb);
static Std_ReturnType Spi_lCheckSeqParam(const uint8 Api,
    Spi_SequenceType *const Sequence, const Spi_SequenceType AppSequenceId,
    const uint8 SyncAsyncIgnore);
static Std_ReturnType Spi_lCheckSpiInitParam(
                   const Spi_ConfigType* const ConfigPtr);
#endif

#if (SPI_MULTICORE_ERROR_DETECT == STD_ON)|| (SPI_SAFETY_ENABLE == STD_ON)
static void Spi_lReportMulticoreError(const uint8 ApiId,
                                      const uint8 ErrorId);
#endif

#if(SPI_CHANNEL_BUFFERS_ALLOWED != 1U)
static void Spi_lIBCopyData(const uint8* const SrcAddrPtr,
                            uint8* const DestAddrPtr, const uint32 Length,
                            const uint8 DataWidthAndIncrementSource);
#endif

#if (SPI_INIT_CHECK_API == STD_ON)
static Std_ReturnType Spi_lCheckBusStatus(void);
#if(SPI_LEVEL_DELIVERED != 0U)
static Std_ReturnType Spi_lCheckKernelVar(const uint32 KernelId);
#endif
static Std_ReturnType Spi_lCheckRegisters(const uint32 KernelId);
static Std_ReturnType Spi_lCheckCoreVar(const uint32 CoreId);
#endif

static void Spi_lCoreInit(const uint32 CoreId);
static void Spi_lInitIBBuffer(void);
static uint8 Spi_lGetTotalIBChannelsInCore(const uint32 CoreId);
#if (MCAL_AR_VERSION == MCAL_AR_440)
#if(SPI_LEVEL_DELIVERED == 2U)
static Std_ReturnType Spi_lValidateDMAConfiguration(const Spi_SequenceType Sequence);
#endif
#endif
#if(SPI_LEVEL_DELIVERED != 0U)
static Std_ReturnType Spi_lValidateMoveCounterLimit(const Spi_SequenceType Sequence);
static uint32 Spi_lGetTotalBytesOfJob(const Spi_JobConfigType *const  JobPtr);
/* Add seq Jobs to Queue */
static Spi_JobType Spi_lAddSeqJobInQueue(const uint8 HwModule,
    const Spi_SequenceType Sequence, const Spi_JobType EndIndex,
    const Spi_JobType JobIndex);

/* Resets the global Queue variables */
static void Spi_lResetAsyncQueueVar(const uint8 ModIndex);

/* This function checks if the QSPI module
   is configure and is used as asynchronous */
static Std_ReturnType Spi_lIsQSPIHwConfiguredAsync(const uint8 HwModule);

/* This function initializes the global variables related to
   asynchronous QSPI.
   It partially(rest is updated at runtime) initializes the
   transaction control set needed for the
   DMA linked list implementation per QSPI module */
static void Spi_lQSPIHwDMAInit(const uint8 ModIndex);

/* This function checks if the slots are available
   in the Queue to be scheduled for transmission */
static Std_ReturnType Spi_lIsSlotsAvailableInQueue
(
  const uint16 NoOfJobs,
  const uint8 Module
);

/* Checks if the Job is not shared with other
    sequences which are already in SPI_SEQ_PENDING state */
static Std_ReturnType Spi_lCheckJobIsNotShared(const Spi_SequenceType Sequence);

/* This function inserts jobs assigned to the sequence
   in the Queue based on the Job priority */
static void Spi_lInsertSeqInQueue(const Spi_SequenceType Sequence);

/* Increments the Index and if the value is equal to the
   queue length then the index is rounded to initial
   value of zero(in order to implement circular Job queue) */
static Spi_JobType Spi_lIncrementRoundIndex
(
  const Spi_JobType Index,  const uint8 HwModule
);


/* This function copies the Job from Main Q to Local Q */
static void Spi_lPushToLocalQ
(
  const Spi_JobType LocalStartIndex, const Spi_JobType LocalEndIndex,
  const uint8 HwModule
);

/* This function pops the elements present in the Local Q
   to the Main Q after the jobs are inserted as per their priority */
static uint16 Spi_lPopFromLocalQ
(
  const Spi_JobType LocalStartIndex, const Spi_JobType LocalEndIndex,
  const Spi_JobType CopyIndex, const uint8 HwModule
);

/* This function checks whether job to be inserted in the curretn location by
comparing the priorities */
static uint8 Spi_lCheckForJobInsert(const uint8 JobPriority,
                                    const uint8 PrioOfJobInQ,
                                    const uint8 PrioOfNextJobInQ);

/* This function comapares the seqeuence ID and Sequence properties
based on the type of comparison */
static uint8 Spi_lGetCompareResult(const uint8 FirstParam,
                                const uint8 SecondParam, const uint8 CompOper);

/* This function gives the priority for the Job.
   Wrt Interruptible sequences, the priority of the job is as
   configured. However, for Non_Interruptible sequences the
   priority of all the jobs in that sequence is elevated
   to the highest priority configured for any job in that sequence */
static uint8 Spi_lModPrioforNonIntrSeq
(
  const Spi_SequenceType SeqId,
  const Spi_JobType JobId
);

/* This function sets up the job for asynchronous
   transmission. Available for Level 1 or 2. */
static void Spi_lAsyncStartJob(const Spi_JobType Job);

/* Configures the Transaction Control Sets per each channel for the Job */
static void Spi_lSetDmaTcs(const Spi_JobType JobId, const uint8 DmaChannelType);

/* This function sets up the transmission for next job if
   present else will terminate the transmission by setting
   up the statuses for Sequence and jobs, also it invokes
   notification function if configured. */
static void Spi_lBusHandler
(
  const uint8 Module,
  const Spi_SeqResultType SeqRes,
  const Spi_JobResultType JobRes
);

/* This function handles the Hw error event raised by QSPI
  when the driver is busy */
static void Spi_lErrorHandler(const uint8 Module);

/* Disable QSPI error interrupts */
static void Spi_lDisQspiErrIntr(const uint8 Module);

#endif /* SPI_LEVEL_DELIVERED !=0U */

#if(SPI_LEVEL_DELIVERED == 2U)
/* Performs Polling operation to propogate the state
   machine for Job transmission per QSPI module */
static void Spi_lModMainFunction(const uint8 Module);

#endif /* SPI_LEVEL_DELIVERED == 2U */

/* This local function checks whether the SPI driver is initialized */
static Std_ReturnType Spi_lCheckInitStatus(const uint8 ApiId,
    const uint8 DetRaise);

/* This function checks if the driver is BUSY or not */
static Std_ReturnType Spi_lIsStatusBusy(const SpiCommsTypes CheckCommsType);

#if(SPI_LEVEL_DELIVERED != 1U)
/* This function checks if the QSPI module
   is configure and is used as synchronous */
static Std_ReturnType Spi_lIsQSPIHwConfiguredSync(const uint8 HwModule);
#endif

/* This function checks if the QSPI module */
static Std_ReturnType Spi_lIsQSPIHwConfigured(const uint8 HwModule);

/* This function initialize the SFR related to QSPI
   indexed by the ModIndex. Initializes CLC, PISEL, GLOBALCON
   and SSOC SFRs for QSPI[ModIndex] with the RESET values of SFR */
static void Spi_lQSPIHwResetInit(const uint8 ModIndex);

/* This function initialize the SFR related to QSPI indexed by the ModIndex.
   Initializes CLC, PISEL, GLOBALCON and SSOC SFRs for QSPI[ModIndex] */
static void Spi_lQSPIHwInit(const uint8 ModIndex);

#if(SPI_LEVEL_DELIVERED != 0U)
/* Function sets the asynchronous driver status
   to the desired value requested in the argument */
static void Spi_lIsrDmaQspiRx(const uint8 Module);
static void Spi_lQspiTriggerNextJob(const uint8 Module, const uint8 ApiId,
                                         const uint8 Pt2Status);

#endif

#if(SPI_LEVEL_DELIVERED != 1U)

static Std_ReturnType Spi_lSyncTransmitData32Bit
(
  const Spi_ChannelType ChannelId,
  const Spi_JobConfigType* const JobConfigPtr,
  const uint8 IsFirstChnl,
  const uint8 IsLastChnl
);
static Std_ReturnType Spi_lSyncTransmitData16Bit
(
  const Spi_ChannelType ChannelId,
  const Spi_JobConfigType* const JobConfigPtr,
  const uint8 IsFirstChnl,
  const uint8 IsLastChnl
);
static Std_ReturnType Spi_lSyncTransmitData8Bit
(
  const Spi_ChannelType ChannelId,
  const Spi_JobConfigType* const JobConfigPtr,
  const uint8 IsFirstChnl,
  const uint8 IsLastChnl
);

/* Available only for SpiLevelDelivered 0 or 2.
   This function initiates transmission at the sequence level */
static Std_ReturnType Spi_lSyncTransmit(const Spi_SequenceType Sequence);

/* This function initiates the transmission at the Job level */
static Std_ReturnType Spi_lSyncStartJob(const Spi_JobType JobId);

/* Polls for the Tx data to be shifted-out and  Rx data to be
   shifted-in till the LOOP timeout counter expires.
   Also Checks for any transmission errors */
static Std_ReturnType Spi_lSynTransErrCheck(const Ifx_QSPI* ModulePtr);

#endif /* SPI_LEVEL_DELIVERED != 1U */


/* This function configures the SFR wrt the Channel properties,
   such as datawidth, LSB/MSB, default data etc. */
static Ifx_QSPI_BACON Spi_lHwSetChannelConfig
(
  const Spi_ChannelType SpiChId,
  const Spi_JobConfigType* const JobConfigPtr,
  const uint8 ToggleCs
);

/* This function configures the SFR wrt the Job properties assigned to
   the hardware, such as baudrate, parity, CS polarity, CLK phase etc. */
static void Spi_lHwSetJobConfig
(
  const Spi_JobConfigType* const JobConfigPtr,
  const uint8 IsAsynchronous
);

/* Sets the port pin to the desired level */
static void Spi_lSetCsViaGpio(const uint8 Port, const uint8 Pin,
                              const uint8 Level);

/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}][/cover] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
 * guideline. */
#include "Spi_MemMap.h"

/*******************************************************************************
**                      Global variables Definition                           **
*******************************************************************************/
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}][/cover] */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which the
 * variable has to be placed. */
#include "Spi_MemMap.h"

static Spi_RunTimeCoreConfigType   *Spi_RuntimeCoreVar[MCAL_NO_OF_CORES];

static Spi_RuntimeKernelType       *Spi_RuntimeKernelVar[SPI_MAX_HW_UNIT];

/* This is a pointer to the configuration of type const Spi_ConfigType */
static const Spi_ConfigType *Spi_kGlobalConfigPtr;

/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}][/cover] */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
 * guideline. */
#include "Spi_MemMap.h"

#if(SPI_CORE0_ENABLE == STD_ON)
/************************* Start - Core - 0 ******************************/
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}][/cover] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE0_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which the
 * variable has to be placed. */
#include "Spi_MemMap.h"

/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_RunTimeCoreConfigType Spi_RuntimeCore0Var;
/* [cover parentID={6725C750-0A11-4A84-BAAE-542C981E9D45}][/cover] */
#if ((SPI_NUM_IB_CHANNELS_CORE0 + SPI_NUM_EB_CHANNELS_CORE0) > 0U)
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_BufferType Spi_BufferCore0[SPI_NUM_IB_CHANNELS_CORE0 +             \
                                                                SPI_NUM_EB_CHANNELS_CORE0];
#endif

#if(SPI_IB_BUFFER_SIZE_CORE0 > 0U)
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_DataBufferType  Spi_TxIBBufferCore0[SPI_IB_BUFFER_SIZE_CORE0];
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_DataBufferType  Spi_RxIBBufferCore0[SPI_IB_BUFFER_SIZE_CORE0];
#endif /* SPI_ASYNC_IB_BUFFER_SIZE_QSPI0 > 0U */
/* [cover parentID={389F75A6-EC4A-4e22-8466-71C685E2ADC1}][/cover] */
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_SeqResultType Spi_SequenceStatusCore0[SPI_SEQUENCE_COUNT_CORE0];
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_JobResultType Spi_JobStatusCore0[SPI_JOB_COUNT_CORE0];

/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}][/cover] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
 * guideline. */
#include "Spi_MemMap.h"
/* end - Core - 0 */
#endif
#ifdef SPI_CORE1_ENABLE
#if (SPI_CORE1_ENABLE == STD_ON)
/************************* Start - Core - 1 ******************************/
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}][/cover] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE1_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which the
 * variable has to be placed. */
#include "Spi_MemMap.h"
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_RunTimeCoreConfigType Spi_RuntimeCore1Var;
/* [cover parentID={6725C750-0A11-4A84-BAAE-542C981E9D45}][/cover] */
#if ((SPI_NUM_IB_CHANNELS_CORE1 + SPI_NUM_EB_CHANNELS_CORE1) > 0U)
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_BufferType Spi_BufferCore1[SPI_NUM_IB_CHANNELS_CORE1 +             \
                                                                SPI_NUM_EB_CHANNELS_CORE1];
#endif

#if(SPI_IB_BUFFER_SIZE_CORE1 > 0U)
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_DataBufferType  Spi_TxIBBufferCore1[SPI_IB_BUFFER_SIZE_CORE1];
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_DataBufferType  Spi_RxIBBufferCore1[SPI_IB_BUFFER_SIZE_CORE1];
#endif /* SPI_ASYNC_IB_BUFFER_SIZE_Core1 > 0U */
/* [cover parentID={389F75A6-EC4A-4e22-8466-71C685E2ADC1}][/cover] */
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_SeqResultType Spi_SequenceStatusCore1[SPI_SEQUENCE_COUNT_CORE1];
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_JobResultType Spi_JobStatusCore1[SPI_JOB_COUNT_CORE1];

/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}][/cover] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
 * guideline. */
#include "Spi_MemMap.h"
/* end - Core 1 */
#endif
#endif
#ifdef SPI_CORE2_ENABLE
#if (SPI_CORE2_ENABLE == STD_ON)
/************************* Start - Core - 2 ******************************/
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}][/cover] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE2_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which the
 * variable has to be placed. */
#include "Spi_MemMap.h"
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_RunTimeCoreConfigType Spi_RuntimeCore2Var;
/* [cover parentID={6725C750-0A11-4A84-BAAE-542C981E9D45}][/cover] */
#if ((SPI_NUM_IB_CHANNELS_CORE2 + SPI_NUM_EB_CHANNELS_CORE2) > 0U)
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_BufferType Spi_BufferCore2[SPI_NUM_IB_CHANNELS_CORE2 + \
                                                                SPI_NUM_EB_CHANNELS_CORE2];
#endif

#if(SPI_IB_BUFFER_SIZE_CORE2 > 0U)
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_DataBufferType Spi_TxIBBufferCore2[SPI_IB_BUFFER_SIZE_CORE2];
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_DataBufferType Spi_RxIBBufferCore2[SPI_IB_BUFFER_SIZE_CORE2];
#endif /* SPI_ASYNC_IB_BUFFER_SIZE_CORE2 > 0U */
/* [cover parentID={389F75A6-EC4A-4e22-8466-71C685E2ADC1}][/cover] */
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_SeqResultType Spi_SequenceStatusCore2[SPI_SEQUENCE_COUNT_CORE2];
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_JobResultType Spi_JobStatusCore2[SPI_JOB_COUNT_CORE2];

/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}][/cover] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_32

/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
 * guideline. */
#include "Spi_MemMap.h"
/* End - Core - 2 */
#endif
#endif
#ifdef SPI_CORE3_ENABLE
#if (SPI_CORE3_ENABLE == STD_ON)
/************************* Start - Core - 3 ******************************/

/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
Const Section[/cover] */
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]
Var cleared section[/cover] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE3_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which the
 * variable has to be placed. */
#include "Spi_MemMap.h"
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_RunTimeCoreConfigType Spi_RuntimeCore3Var;
/* [cover parentID={6725C750-0A11-4A84-BAAE-542C981E9D45}][/cover] */
#if ((SPI_NUM_IB_CHANNELS_CORE3 + SPI_NUM_EB_CHANNELS_CORE3) > 0U)
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_BufferType Spi_BufferCore3[SPI_NUM_IB_CHANNELS_CORE3 + \
                                                                SPI_NUM_EB_CHANNELS_CORE3];
#endif

#if(SPI_IB_BUFFER_SIZE_CORE3 > 0U)
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_DataBufferType Spi_TxIBBufferCore3[SPI_IB_BUFFER_SIZE_CORE3];
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_DataBufferType Spi_RxIBBufferCore3[SPI_IB_BUFFER_SIZE_CORE3];
#endif /* SPI_ASYNC_IB_BUFFER_SIZE_CORE3 > 0U */
/* [cover parentID={389F75A6-EC4A-4e22-8466-71C685E2ADC1}][/cover] */
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_SeqResultType Spi_SequenceStatusCore3[SPI_SEQUENCE_COUNT_CORE3];
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_JobResultType Spi_JobStatusCore3[SPI_JOB_COUNT_CORE3];

/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}][/cover] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_32

/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
 * guideline. */
#include "Spi_MemMap.h"
/* End - Core - 3 */
#endif
#endif

#ifdef SPI_CORE4_ENABLE
#if (SPI_CORE4_ENABLE == STD_ON)
/************************* Start - Core - 4 ******************************/
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}][/cover] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE4_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which the
 * variable has to be placed. */
#include "Spi_MemMap.h"
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_RunTimeCoreConfigType Spi_RuntimeCore4Var;
/* [cover parentID={6725C750-0A11-4A84-BAAE-542C981E9D45}][/cover] */
#if ((SPI_NUM_IB_CHANNELS_CORE4 + SPI_NUM_EB_CHANNELS_CORE4) > 0U)
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_BufferType Spi_BufferCore4[SPI_NUM_IB_CHANNELS_CORE4 + \
                                                                SPI_NUM_EB_CHANNELS_CORE4];
#endif

#if(SPI_IB_BUFFER_SIZE_CORE4 > 0U)
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_DataBufferType Spi_TxIBBufferCore4[SPI_IB_BUFFER_SIZE_CORE4];
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_DataBufferType Spi_RxIBBufferCore4[SPI_IB_BUFFER_SIZE_CORE4];
#endif /* SPI_ASYNC_IB_BUFFER_SIZE_CORE4 > 0U */
/* [cover parentID={389F75A6-EC4A-4e22-8466-71C685E2ADC1}][/cover] */
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_SeqResultType Spi_SequenceStatusCore4[SPI_SEQUENCE_COUNT_CORE4];
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_JobResultType Spi_JobStatusCore4[SPI_JOB_COUNT_CORE4];

/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}][/cover] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_32

/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
 * guideline. */
#include "Spi_MemMap.h"
/* End - Core - 4 */
#endif
#endif

#ifdef SPI_CORE5_ENABLE
#if (SPI_CORE5_ENABLE == STD_ON)
/************************* Start - Core - 5 ******************************/
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}][/cover] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE5_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which the
 * variable has to be placed. */
#include "Spi_MemMap.h"
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_RunTimeCoreConfigType Spi_RuntimeCore5Var;
/* [cover parentID={6725C750-0A11-4A84-BAAE-542C981E9D45}][/cover] */
#if ((SPI_NUM_IB_CHANNELS_CORE5 + SPI_NUM_EB_CHANNELS_CORE5) > 0U)
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_BufferType Spi_BufferCore5[SPI_NUM_IB_CHANNELS_CORE5 + \
                                                                SPI_NUM_EB_CHANNELS_CORE5];
#endif

#if(SPI_IB_BUFFER_SIZE_CORE5 > 0U)
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
  multiple functions. Hence it is made as a global variable. */
static Spi_DataBufferType Spi_TxIBBufferCore5[SPI_IB_BUFFER_SIZE_CORE5];
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_DataBufferType Spi_RxIBBufferCore5[SPI_IB_BUFFER_SIZE_CORE5];
#endif /* SPI_ASYNC_IB_BUFFER_SIZE_CORE5 > 0U */
/* [cover parentID={389F75A6-EC4A-4e22-8466-71C685E2ADC1}][/cover] */
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_SeqResultType Spi_SequenceStatusCore5[SPI_SEQUENCE_COUNT_CORE5];
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_JobResultType Spi_JobStatusCore5[SPI_JOB_COUNT_CORE5];

/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}][/cover] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_32

/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
 * guideline. */
#include "Spi_MemMap.h"
/* End - Core - 5 */
#endif
#endif
/**************************** END CORE CONFIGURATION *************************/

/***************************** Start - QSPI0 *********************************/
/* variable specific to QSPI0 */
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}][/cover] */
#if(SPI_HW_QSPI0_USED == STD_ON)
#if (SPI_QSPI0_CORE == 0)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE0_32
#elif (SPI_QSPI0_CORE == 1)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE1_32
#elif (SPI_QSPI0_CORE == 2)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE2_32
#elif (SPI_QSPI0_CORE == 3)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE3_32
#elif (SPI_QSPI0_CORE == 4)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE4_32
#elif (SPI_QSPI0_CORE == 5)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE5_32
#endif
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which the
 * variable has to be placed. */
#include "Spi_MemMap.h"

/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_RuntimeKernelType Spi_RuntimeKernelQSPI0;
#if(SPI_LEVEL_DELIVERED != 0U)
#if(SPI_QSPI0_HWTYPE == SPI_ASYNC_BUS)
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_QueueType Spi_JobQueueQSPI0;
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_JobAndSeqQueueType Spi_JobAndSeqQueueQSPI0[                        \
    SPI_JOB_QUEUE_LENGTH_QSPI0];
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side effects seen*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side effects seen*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side effects seen*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side effects seen*/
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_JobAndSeqQueueType Spi_JobAndSeqQueueRearrangeQSPI0[               \
    SPI_JOB_QUEUE_LENGTH_QSPI0];
/* BACON Array for holding BACONS of all channels in a job */
/* MISRA2012_RULE_19_2_JUSTIFICATION: register type Definition */
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Ifx_QSPI_BACON Spi_Qspi0Bacon[SPI_DMA_MAX_TCS_NUM_QSPI0];
#endif
#endif

/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}][/cover] */
#if (SPI_QSPI0_CORE == 0)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_32
#elif (SPI_QSPI0_CORE == 1)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_32
#elif (SPI_QSPI0_CORE == 2)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_32
#elif (SPI_QSPI0_CORE == 3)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_32
#elif (SPI_QSPI0_CORE == 4)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_32
#elif (SPI_QSPI0_CORE == 5)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_32
#endif
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
 * guideline. */
#include "Spi_MemMap.h"

/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}][/cover] */
#if(SPI_LEVEL_DELIVERED != 0U)
#if(SPI_QSPI0_HWTYPE == SPI_ASYNC_BUS)
#if (SPI_QSPI0_CORE == 0)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE0_256
#elif (SPI_QSPI0_CORE == 1)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE1_256
#elif (SPI_QSPI0_CORE == 2)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE2_256
#elif (SPI_QSPI0_CORE == 3)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE3_256
#elif (SPI_QSPI0_CORE == 4)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE4_256
#elif (SPI_QSPI0_CORE == 5)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE5_256
#endif
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which the
 * variable has to be placed. */
#include "Spi_MemMap.h"
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_DmaTCSType Spi_DmaTxControlSetArrayQSPI0[SPI_DMA_MAX_TCS_NUM_QSPI0];
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_DmaTCSType Spi_DmaRxControlSetArrayQSPI0[SPI_DMA_MAX_TCS_NUM_QSPI0];
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}][/cover] */
#if (SPI_QSPI0_CORE == 0)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_256
#elif (SPI_QSPI0_CORE == 1)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_256
#elif (SPI_QSPI0_CORE == 2)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_256
#elif (SPI_QSPI0_CORE == 3)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_256
#elif (SPI_QSPI0_CORE == 4)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_256
#elif (SPI_QSPI0_CORE == 5)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_256
#endif
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
 * guideline. */
#include "Spi_MemMap.h"
#endif /* (SPI_QSPI0_HWTYPE == SPI_ASYNC_BUS) */
#endif

#endif /* (SPI_HW_QSPI0_USED == STD_ON) */

/***************************** Start - QSPI1 *********************************/
/* variable specific to QSPI1 */
#if(SPI_HW_QSPI1_USED == STD_ON)
#if defined (SPI_QSPI1_CORE) && (SPI_QSPI1_CORE == 0)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE0_32
#elif (SPI_QSPI1_CORE == 1)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE1_32
#elif (SPI_QSPI1_CORE == 2)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE2_32
#elif (SPI_QSPI1_CORE == 3)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE3_32
#elif (SPI_QSPI1_CORE == 4)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE4_32
#elif (SPI_QSPI1_CORE == 5)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE5_32
#endif

/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which the
 * variable has to be placed. */
#include "Spi_MemMap.h"

/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_RuntimeKernelType Spi_RuntimeKernelQSPI1;
#if(SPI_LEVEL_DELIVERED != 0U)
#if(SPI_QSPI1_HWTYPE == SPI_ASYNC_BUS)
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_QueueType Spi_JobQueueQSPI1;
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_JobAndSeqQueueType Spi_JobAndSeqQueueQSPI1[                        \
    SPI_JOB_QUEUE_LENGTH_QSPI1];
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side effects seen*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side effects seen*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side effects seen*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side effects seen*/
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_JobAndSeqQueueType Spi_JobAndSeqQueueRearrangeQSPI1[               \
    SPI_JOB_QUEUE_LENGTH_QSPI1];
/* BACON Array for holding BACONS of all channels in a job */
/* MISRA2012_RULE_19_2_JUSTIFICATION: register type Definition */
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Ifx_QSPI_BACON Spi_Qspi1Bacon[SPI_DMA_MAX_TCS_NUM_QSPI1];
#endif
#endif

#if (SPI_QSPI1_CORE == 0)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_32
#elif (SPI_QSPI1_CORE == 1)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_32
#elif (SPI_QSPI1_CORE == 2)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_32
#elif (SPI_QSPI1_CORE == 3)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_32
#elif (SPI_QSPI1_CORE == 4)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_32
#elif (SPI_QSPI1_CORE == 5)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_32
#endif

/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
 * guideline. */
#include "Spi_MemMap.h"
#if(SPI_LEVEL_DELIVERED != 0U)
#if(SPI_QSPI1_HWTYPE == SPI_ASYNC_BUS)
#if (SPI_QSPI1_CORE == 0)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE0_256
#elif (SPI_QSPI1_CORE == 1)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE1_256
#elif (SPI_QSPI1_CORE == 2)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE2_256
#elif (SPI_QSPI1_CORE == 3)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE3_256
#elif (SPI_QSPI1_CORE == 4)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE4_256
#elif (SPI_QSPI1_CORE == 5)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE5_256
#endif

/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which the
 * variable has to be placed.. */
#include "Spi_MemMap.h"
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_DmaTCSType Spi_DmaTxControlSetArrayQSPI1[SPI_DMA_MAX_TCS_NUM_QSPI1];
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_DmaTCSType Spi_DmaRxControlSetArrayQSPI1[SPI_DMA_MAX_TCS_NUM_QSPI1];
#if (SPI_QSPI1_CORE == 0)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_256
#elif (SPI_QSPI1_CORE == 1)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_256
#elif (SPI_QSPI1_CORE == 2)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_256
#elif (SPI_QSPI1_CORE == 3)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_256
#elif (SPI_QSPI1_CORE == 4)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_256
#elif (SPI_QSPI1_CORE == 5)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_256
#endif

/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
 * guideline. */
#include "Spi_MemMap.h"
#endif /* (SPI_QSPI1_HWTYPE == SPI_ASYNC_BUS) */
#endif
#endif /* (SPI_HW_QSPI1_USED == STD_ON) */

/***************************** Start - QSPI2 *********************************/
/* variable specific to QSPI2 */
#if(SPI_HW_QSPI2_USED == STD_ON)
#if (SPI_QSPI2_CORE == 0)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE0_32
#elif (SPI_QSPI2_CORE == 1)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE1_32
#elif (SPI_QSPI2_CORE == 2)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE2_32
#elif (SPI_QSPI2_CORE == 3)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE3_32
#elif (SPI_QSPI2_CORE == 4)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE4_32
#elif (SPI_QSPI2_CORE == 5)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE5_32
#endif

/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which the
 * variable has to be placed. */
#include "Spi_MemMap.h"

/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_RuntimeKernelType Spi_RuntimeKernelQSPI2;
#if(SPI_LEVEL_DELIVERED != 0U)
#if(SPI_QSPI2_HWTYPE == SPI_ASYNC_BUS)
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_QueueType Spi_JobQueueQSPI2;
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_JobAndSeqQueueType Spi_JobAndSeqQueueQSPI2[                        \
    SPI_JOB_QUEUE_LENGTH_QSPI2];
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side effects seen*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side effects seen*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side effects seen*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side effects seen*/
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_JobAndSeqQueueType Spi_JobAndSeqQueueRearrangeQSPI2[               \
    SPI_JOB_QUEUE_LENGTH_QSPI2];
/* BACON Array for holding BACONS of all channels in a job */
/* MISRA2012_RULE_19_2_JUSTIFICATION: register type Definition */
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Ifx_QSPI_BACON Spi_Qspi2Bacon[SPI_DMA_MAX_TCS_NUM_QSPI2];
#endif
#endif
#if (SPI_QSPI2_CORE == 0)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_32
#elif (SPI_QSPI2_CORE == 1)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_32
#elif (SPI_QSPI2_CORE == 2)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_32
#elif (SPI_QSPI2_CORE == 3)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_32
#elif (SPI_QSPI2_CORE == 4)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_32
#elif (SPI_QSPI2_CORE == 5)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_32
#endif
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
 * guideline. */
#include "Spi_MemMap.h"

#if(SPI_LEVEL_DELIVERED != 0U)
#if(SPI_QSPI2_HWTYPE == SPI_ASYNC_BUS)
#if (SPI_QSPI2_CORE == 0)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE0_256
#elif (SPI_QSPI2_CORE == 1)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE1_256
#elif (SPI_QSPI2_CORE == 2)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE2_256
#elif (SPI_QSPI2_CORE == 3)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE3_256
#elif (SPI_QSPI2_CORE == 4)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE4_256
#elif (SPI_QSPI2_CORE == 5)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE5_256
#endif
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which the
 * variable has to be placed. */
#include "Spi_MemMap.h"
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_DmaTCSType Spi_DmaTxControlSetArrayQSPI2[SPI_DMA_MAX_TCS_NUM_QSPI2];
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_DmaTCSType Spi_DmaRxControlSetArrayQSPI2[SPI_DMA_MAX_TCS_NUM_QSPI2];
#if (SPI_QSPI2_CORE == 0)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_256
#elif (SPI_QSPI2_CORE == 1)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_256
#elif (SPI_QSPI2_CORE == 2)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_256
#elif (SPI_QSPI2_CORE == 3)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_256
#elif (SPI_QSPI2_CORE == 4)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_256
#elif (SPI_QSPI2_CORE == 5)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_256
#endif
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
 * guideline. */
#include "Spi_MemMap.h"

#endif /* (SPI_QSPI2_HWTYPE == SPI_ASYNC_BUS) */
#endif
#endif /* (SPI_HW_QSPI2_USED == STD_ON) */

/***************************** Start - QSPI3 *********************************/
/* variable specific to QSPI3 */
#if(SPI_HW_QSPI3_USED == STD_ON)
#if (SPI_QSPI3_CORE == 0)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE0_32
#elif (SPI_QSPI3_CORE == 1)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE1_32
#elif (SPI_QSPI3_CORE == 2)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE2_32
#elif (SPI_QSPI3_CORE == 3)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE3_32
#elif (SPI_QSPI3_CORE == 4)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE4_32
#elif (SPI_QSPI3_CORE == 5)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE5_32
#endif
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which the
 * variable has to be placed. */
#include "Spi_MemMap.h"

/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_RuntimeKernelType Spi_RuntimeKernelQSPI3;
#if(SPI_LEVEL_DELIVERED != 0U)
#if(SPI_QSPI3_HWTYPE == SPI_ASYNC_BUS)
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_QueueType Spi_JobQueueQSPI3;
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_JobAndSeqQueueType Spi_JobAndSeqQueueQSPI3[                        \
    SPI_JOB_QUEUE_LENGTH_QSPI3];
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side effects seen*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side effects seen*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side effects seen*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side effects seen*/
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_JobAndSeqQueueType Spi_JobAndSeqQueueRearrangeQSPI3[               \
    SPI_JOB_QUEUE_LENGTH_QSPI3];
/* BACON Array for holding BACONS of all channels in a job */
/* MISRA2012_RULE_19_2_JUSTIFICATION: register type Definition */
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Ifx_QSPI_BACON Spi_Qspi3Bacon[SPI_DMA_MAX_TCS_NUM_QSPI3];
#endif
#endif

#if (SPI_QSPI3_CORE == 0)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_32
#elif (SPI_QSPI3_CORE == 1)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_32
#elif (SPI_QSPI3_CORE == 2)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_32
#elif (SPI_QSPI3_CORE == 3)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_32
#elif (SPI_QSPI3_CORE == 4)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_32
#elif (SPI_QSPI3_CORE == 5)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_32
#endif
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
 * guideline. */
#include "Spi_MemMap.h"

#if(SPI_LEVEL_DELIVERED != 0U)
#if(SPI_QSPI3_HWTYPE == SPI_ASYNC_BUS)
#if (SPI_QSPI3_CORE == 0)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE0_256
#elif (SPI_QSPI3_CORE == 1)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE1_256
#elif (SPI_QSPI3_CORE == 2)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE2_256
#elif (SPI_QSPI3_CORE == 3)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE3_256
#elif (SPI_QSPI3_CORE == 4)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE4_256
#elif (SPI_QSPI3_CORE == 5)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE5_256
#endif
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which the
 * variable has to be placed. */
#include "Spi_MemMap.h"
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_DmaTCSType Spi_DmaTxControlSetArrayQSPI3[SPI_DMA_MAX_TCS_NUM_QSPI3];
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_DmaTCSType Spi_DmaRxControlSetArrayQSPI3[SPI_DMA_MAX_TCS_NUM_QSPI3];

#if (SPI_QSPI3_CORE == 0)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_256
#elif (SPI_QSPI3_CORE == 1)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_256
#elif (SPI_QSPI3_CORE == 2)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_256
#elif (SPI_QSPI3_CORE == 3)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_256
#elif (SPI_QSPI3_CORE == 4)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_256
#elif (SPI_QSPI3_CORE == 5)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_256
#endif
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
 * guideline. */
#include "Spi_MemMap.h"
#endif /* (SPI_QSPI3_HWTYPE == SPI_ASYNC_BUS) */
#endif
#endif /* (SPI_HW_QSPI3_USED == STD_ON) */

/***************************** Start - QSPI4 *********************************/
/* variable specific to QSPI4 */
#ifdef SPI_HW_QSPI4_USED
#if(SPI_HW_QSPI4_USED == STD_ON)
#if (SPI_QSPI4_CORE == 0)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE0_32
#elif (SPI_QSPI4_CORE == 1)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE1_32
#elif (SPI_QSPI4_CORE == 2)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE2_32
#elif (SPI_QSPI4_CORE == 3)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE3_32
#elif (SPI_QSPI4_CORE == 4)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE4_32
#elif (SPI_QSPI4_CORE == 5)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE5_32
#endif
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which the
 * variable has to be placed. */
#include "Spi_MemMap.h"

/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_RuntimeKernelType Spi_RuntimeKernelQSPI4;
#if(SPI_LEVEL_DELIVERED != 0U)
#if(SPI_QSPI4_HWTYPE == SPI_ASYNC_BUS)
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_QueueType Spi_JobQueueQSPI4;
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_JobAndSeqQueueType Spi_JobAndSeqQueueQSPI4[                        \
    SPI_JOB_QUEUE_LENGTH_QSPI4];
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side effects seen*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side effects seen*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side effects seen*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
  in source code due to Autosar Naming constraints. Since compiler support
   more than 32 characters, no side effects seen*/
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_JobAndSeqQueueType Spi_JobAndSeqQueueRearrangeQSPI4[               \
    SPI_JOB_QUEUE_LENGTH_QSPI4];
/* BACON Array for holding BACONS of all channels in a job */
/* MISRA2012_RULE_19_2_JUSTIFICATION: register type Definition */
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Ifx_QSPI_BACON Spi_Qspi4Bacon[SPI_DMA_MAX_TCS_NUM_QSPI4];
#endif
#endif

#if (SPI_QSPI4_CORE == 0)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_32
#elif (SPI_QSPI4_CORE == 1)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_32
#elif (SPI_QSPI4_CORE == 2)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_32
#elif (SPI_QSPI4_CORE == 3)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_32
#elif (SPI_QSPI4_CORE == 4)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_32
#elif (SPI_QSPI4_CORE == 5)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_32
#endif
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
 * guideline. */
#include "Spi_MemMap.h"

#if(SPI_LEVEL_DELIVERED != 0U)
#if(SPI_QSPI4_HWTYPE == SPI_ASYNC_BUS)
#if (SPI_QSPI4_CORE == 0)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE0_256
#elif (SPI_QSPI4_CORE == 1)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE1_256
#elif (SPI_QSPI4_CORE == 2)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE2_256
#elif (SPI_QSPI4_CORE == 3)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE3_256
#elif (SPI_QSPI4_CORE == 4)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE4_256
#elif (SPI_QSPI4_CORE == 5)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE5_256
#endif
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which the
 * variable has to be placed. */
#include "Spi_MemMap.h"
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_DmaTCSType Spi_DmaTxControlSetArrayQSPI4[SPI_DMA_MAX_TCS_NUM_QSPI4];
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_DmaTCSType Spi_DmaRxControlSetArrayQSPI4[SPI_DMA_MAX_TCS_NUM_QSPI4];

#if (SPI_QSPI4_CORE == 0)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_256
#elif (SPI_QSPI4_CORE == 1)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_256
#elif (SPI_QSPI4_CORE == 2)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_256
#elif (SPI_QSPI4_CORE == 3)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_256
#elif (SPI_QSPI4_CORE == 4)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_256
#elif (SPI_QSPI4_CORE == 5)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_256
#endif
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
 * guideline. */
#include "Spi_MemMap.h"

#endif /* (SPI_QSPI4_HWTYPE == SPI_ASYNC_BUS) */
#endif
#endif /* (SPI_HW_QSPI4_USED == STD_ON) */
#endif

/***************************** Start - QSPI5 *********************************/
/* variable specific to QSPI5 */
#ifdef SPI_HW_QSPI5_USED
#if(SPI_HW_QSPI5_USED == STD_ON)
#if (SPI_QSPI5_CORE == 0)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE0_32
#elif (SPI_QSPI5_CORE == 1)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE1_32
#elif (SPI_QSPI5_CORE == 2)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE2_32
#elif (SPI_QSPI5_CORE == 3)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE3_32
#elif (SPI_QSPI5_CORE == 4)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE4_32
#elif (SPI_QSPI5_CORE == 5)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE5_32
#endif
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which the
 * variable has to be placed. */
#include "Spi_MemMap.h"

/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_RuntimeKernelType Spi_RuntimeKernelQSPI5;
#if(SPI_LEVEL_DELIVERED != 0U)
#if(SPI_QSPI5_HWTYPE == SPI_ASYNC_BUS)
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_QueueType Spi_JobQueueQSPI5;
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_JobAndSeqQueueType Spi_JobAndSeqQueueQSPI5[                        \
    SPI_JOB_QUEUE_LENGTH_QSPI5];
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Variable for each kernel */
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_JobAndSeqQueueType Spi_JobAndSeqQueueRearrangeQSPI5[               \
    SPI_JOB_QUEUE_LENGTH_QSPI5];
/* BACON Array for holding BACONS of all channels in a job */
/* MISRA2012_RULE_19_2_JUSTIFICATION: register type Definition */
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Ifx_QSPI_BACON Spi_Qspi5Bacon[SPI_DMA_MAX_TCS_NUM_QSPI5];
#endif
#endif
#if (SPI_QSPI5_CORE == 0)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_32
#elif (SPI_QSPI5_CORE == 1)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_32
#elif (SPI_QSPI5_CORE == 2)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_32
#elif (SPI_QSPI5_CORE == 3)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_32
#elif (SPI_QSPI5_CORE == 4)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_32
#elif (SPI_QSPI5_CORE == 5)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_32
#endif
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
 * guideline. */
#include "Spi_MemMap.h"

#if(SPI_LEVEL_DELIVERED != 0U)
#if(SPI_QSPI5_HWTYPE == SPI_ASYNC_BUS)
#if (SPI_QSPI5_CORE == 0)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE0_256
#elif (SPI_QSPI5_CORE == 1)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE1_256
#elif (SPI_QSPI5_CORE == 2)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE2_256
#elif (SPI_QSPI5_CORE == 3)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE3_256
#elif (SPI_QSPI5_CORE == 4)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE4_256
#elif (SPI_QSPI5_CORE == 5)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_START_SEC_VAR_CLEARED_ASIL_B_CORE5_256
#endif
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which the
 * variable has to be placed. */
#include "Spi_MemMap.h"
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_DmaTCSType Spi_DmaTxControlSetArrayQSPI5[SPI_DMA_MAX_TCS_NUM_QSPI5];
/* MISRA2012_RULE_8_9_JUSTIFICATION: This variable is accessed as pointer in
   multiple functions. Hence it is made as a global variable. */
static Spi_DmaTCSType Spi_DmaRxControlSetArrayQSPI5[SPI_DMA_MAX_TCS_NUM_QSPI5];
#if (SPI_QSPI5_CORE == 0)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE0_256
#elif (SPI_QSPI5_CORE == 1)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE1_256
#elif (SPI_QSPI5_CORE == 2)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE2_256
#elif (SPI_QSPI5_CORE == 3)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE3_256
#elif (SPI_QSPI5_CORE == 4)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE4_256
#elif (SPI_QSPI5_CORE == 5)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Macro identifiers shall be distinct
 * because of AS naming convention */
/* MISRA2012_RULE_5_5_JUSTIFICATION: Identifiers shall be distinct from macro
 * names because of AS naming convention */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_B_CORE5_256
#endif
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
 * guideline. */
#include "Spi_MemMap.h"
#endif
#endif
#endif
#endif

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/

/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}][/cover] */
#define SPI_START_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
 * guideline. */
#include "Spi_MemMap.h"
#if(SPI_HW_ERROR_DEM_REPORT == SPI_DEM_REPORT_ENABLED)
/*******************************************************************************
** Traceability     : [cover parentID={459CD033-C266-46a5-BE76-550CFD4DE896}] **
**                                                                            **
** Syntax          :  Spi_lReportDemError(Dem_EventIdType EventId,            **
**                               Dem_EventStatusType EventStatus)             **
**                                                                            **
** Service ID      :  NA                                                      **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Reentrant                                               **
**                                                                            **
** Parameters (in) :  EventId  - Indicates the Event ID                       **
**                    EventStatus - Indicates the event status                **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description     : Function reports Production Error
*******************************************************************************/
static void Spi_lReportDemError(Dem_EventIdType EventId,
                                      Dem_EventStatusType EventStatus)
{
  /*[cover parentID={6C6AC0A0-7E83-41e1-A62D-08B24A1D3A04}][/cover]*/
  #if(MCAL_AR_VERSION == MCAL_AR_422)
  /*[cover parentID={1475BFFE-2912-4b74-B4D8-22884A9F7610}][/cover]*/
  Mcal_Wrapper_Dem_ReportErrorStatus(EventId, EventStatus);
  #else
  /*[cover parentID={E5D3C103-695C-4037-B26B-EC2CA859D1D9}][/cover]*/
  /*[cover parentID={429B3FF7-703B-42fc-AEFD-FF9B4E8CA080}][/cover]*/
  (void)Mcal_Wrapper_Dem_SetEventStatus(EventId, EventStatus);
  #endif
}
#endif
/*******************************************************************************
** Traceability     : [cover parentID={BE28B796-3871-48C9-B2C3-6DA7FC1FBECE}] **
**                                                                            **
** Syntax          :  Spi_lReportMulticoreError(const uint8 ApiId,            **
                      const uint8 ErrorId)                                    **
**                                                                            **
** Service ID      :  NA                                                      **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Reentrant                                               **
**                                                                            **
** Parameters (in) :  ApiId  - API                                            **
**                    ErrorId - Error passed from API                         **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description     : Function reports multicore DET, enabled                  **
**                      when Safety is enabled or multicore DET is enabled.   **
*******************************************************************************/
#if (SPI_MULTICORE_ERROR_DETECT == STD_ON)|| (SPI_SAFETY_ENABLE == STD_ON)
/*[cover parentID={775C916C-9F17-44e7-B213-7D8F8472F530}][/cover]*/
static void Spi_lReportMulticoreError(const uint8 ApiId,
                                      const uint8 ErrorId)
{
  #if (SPI_MULTICORE_ERROR_DETECT == STD_ON)
  (void)Det_ReportError(
    SPI_MODULE_ID,
    SPI_INSTANCE_ID,
    ApiId,
    ErrorId);/* End of report to DET */
  #endif

  #if (SPI_SAFETY_ENABLE == STD_ON)
  Mcal_ReportSafetyError(
    SPI_MODULE_ID,
    SPI_INSTANCE_ID,
    ApiId,
    ErrorId);/* End of report to Safety */
  #endif
}
#endif

#if ((SPI_DEV_ERROR_DETECT == STD_ON) || (SPI_SAFETY_ENABLE == STD_ON))
/*******************************************************************************
** Traceability     : [cover parentID={BE28B796-3871-48C9-B2C3-6DA7FC1FBECE}] **
**                                                                            **
** Syntax          :  Spi_lReportError(const uint8 ApiId, const uint8 ErrorId)**
**                                                                            **
** Service ID      :  NA                                                      **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Reentrant                                               **
**                                                                            **
** Parameters (in) :  ApiId  - API                                            **
**                    ErrorId - Error passed from API                         **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description     :  This API is called by all the API functions to          **
**                    report either Safety error or DET. Based on the         **
**                    whether DET or Safety is enabled, errors are reported.  **
*******************************************************************************/
static void Spi_lReportError(const uint8 ApiId, const uint8 ErrorId)
{
  /*  [cover parentID={2DA275A7-193F-49fb-9F1C-5BFD76363ADB}]
      Report DET through Det_ReportError API
      [/cover] */
  #if (SPI_DEV_ERROR_DETECT == STD_ON)
  (void)Det_ReportError(
    SPI_MODULE_ID,
    SPI_INSTANCE_ID,
    ApiId,
    ErrorId);/* End of report to DET */
  #endif

  #if (SPI_SAFETY_ENABLE == STD_ON)
  Mcal_ReportSafetyError(
    SPI_MODULE_ID,
    SPI_INSTANCE_ID,
    ApiId,
    ErrorId);/* End of report to Safety */
  #endif
}

#endif
#if (((MCAL_AR_VERSION == MCAL_AR_422) && ((SPI_DEV_ERROR_DETECT == STD_ON) || \
(SPI_SAFETY_ENABLE == STD_ON))) ||((MCAL_AR_VERSION == MCAL_AR_440) && \
(SPI_RUNTIME_ERROR_DETECT == STD_ON)))
/*******************************************************************************
** Traceability     : [cover parentID={9939FF3D-7731-4fc1-AD0F-8B1B24700E75}] **
**                                                                            **
** Syntax          :  Spi_lReportRuntimeDetError(const uint8 ApiId,           **
**                                                 const uint8 ErrorId)       **
**                                                                            **
** Service ID      :  NA                                                      **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Reentrant                                               **
**                                                                            **
** Parameters (in) :  ApiId  - API                                            **
**                    ErrorId - Error passed from API                         **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description     :  This API is called by all the API functions to          **
**                    report Safety error or Runtime Error or DET.            **
**                    Based on the whether DET or Runtime Error or Safety     **
**                    Error is enabled, errors are reported.                  **
*******************************************************************************/
static void Spi_lReportRuntimeDetError(const uint8 ApiId, const uint8 ErrorId)
{
  /*[cover parentID={90618A22-B613-4225-ADA6-C4C755D1199F}]
    Report Runtime Error through Mcal_Wrapper_Det_ReportRuntimeError API
  [/cover] */
  #if(MCAL_AR_VERSION == MCAL_AR_440)
    #if (SPI_RUNTIME_ERROR_DETECT == STD_ON)
    /* [cover parentID={C7854565-52E1-4e6b-94CD-2167ABAFAB29}][/cover] */
    (void)Mcal_Wrapper_Det_ReportRuntimeError(SPI_MODULE_ID, SPI_INSTANCE_ID, ApiId, ErrorId);
  #endif
  #else
    #if (SPI_DEV_ERROR_DETECT == STD_ON)
      /* [cover parentID={45C36E86-9FB6-43C4-BD27-159CDB065C17}][/cover] */
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, ApiId, ErrorId);
    #endif

    #if (SPI_SAFETY_ENABLE == STD_ON)
      /* [cover parentID={64395834-BFDD-47dd-A290-3BBEAEC2B51C}][/cover] */
    Mcal_ReportSafetyError(SPI_MODULE_ID, SPI_INSTANCE_ID, ApiId, ErrorId);
    #endif
  #endif
}
#endif
/*******************************************************************************
** Traceability     : [cover parentID={50921691-EB6D-49da-BCCC-5ADBFE87AD6A}] **
**                                                                            **
** Syntax          : Std_ReturnType Spi_lCheckSpiInitParam                    **
**                                   (const Spi_ConfigType* const ConfigPtr)  **
**                                                                            **
** Service ID      :  NA                                                      **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non Reentrant                                           **
**                                                                            **
** Parameters (in) :  ConfigPtr - Pointer to configuration set                **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Returns E_OK if the param passed is proper,             **
**                    else returns E_NOT_OK                                   **
**                                                                            **
** Description     : Checks for the initialization of driver                  **
*******************************************************************************/
#if ((SPI_DEV_ERROR_DETECT == STD_ON) || (SPI_SAFETY_ENABLE == STD_ON))
static Std_ReturnType Spi_lCheckSpiInitParam(
  const Spi_ConfigType* const ConfigPtr)
{
  Std_ReturnType ErrStatus = E_NOT_OK;

  /* [cover parentID={4804DF01-13FA-4c7c-B461-AD6E94139744}]
  Check Config pointer
  [/cover] */
  /* [cover parentID={39DDE0B3-A336-4b57-BE9E-6D0700EBE8B8}]
  Configuration pointer is not valid
  [/cover] */
  if(ConfigPtr == NULL_PTR)
  {
    Spi_lReportError(SPI_SID_INIT,
                     SPI_E_PARAM_POINTER);
  }
  else
  {
    /* Check if Driver is already initialized */
    /* [cover parentID={22931E9D-EC22-4844-B695-748FE37681DE}]
    Check if same input config pointer is not passed in different cores
    if error status is E_OK
    [/cover] */
    /* [cover parentID={E78A2D27-479B-41b3-8CF8-D9ADAB7833B4}]
    Driver is already initialized
    [/cover] */
    ErrStatus = Spi_lCheckInitStatus(SPI_SID_INIT, (uint8)SPI_DET_DISABLE);
    if(ErrStatus != (uint8)E_OK)
    {
      /* [cover parentID={978CA36E-0172-486e-9DD2-26DF526931E5}]
       Report error SPI_E_ALREADY_INITIALIZED
      [/cover] */
      Spi_lReportError(SPI_SID_INIT,
                       SPI_E_ALREADY_INITIALIZED);
    }
    /* [cover parentID={1ACBA0A1-3211-49a1-A108-33F0FC397751}]
         Check if config pointer is proper one
        [/cover] */
    else if(Spi_kGlobalConfigPtr != NULL_PTR)
    {
      if(Spi_kGlobalConfigPtr != ConfigPtr)
      {
        /* [cover parentID={69DEF670-ED12-47d8-BFEF-4C9A3BE610E5}][/cover] */
        Spi_lReportError(SPI_SID_INIT,
                         SPI_E_INIT_FAILED);
        ErrStatus = E_NOT_OK;
      }
    }
    else
    {
      /* Dummy */
    }
  }

  return ErrStatus;
}
#endif /* SPI_DEV_ERROR_DETECT == STD_ON */


/*******************************************************************************
** Traceability     : [cover parentID={8BF4C15E-F036-422a-B2CB-8639229AF82E}] **
**                                                                            **
** Syntax         : Std_ReturnType Spi_InitCheck(const Spi_ConfigType* const  **
**                                                     ConfigPtr)             **
**                                                                            **
** Service ID      :  0x20                                                    **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Reentrant for the different core                        **
**                                                                            **
** Parameters (in) :  ConfigPtr - Pointer to configuration set                **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  E_OK on successfully checking the mentioned             **
**                             global variables / SFRs.                       **
**                    E_NOT_OK if any of the global variables or SFR          **
**                    is not set as expected.                                 **
**                                                                            **
** Description     : Check for all the globals and registers to be            **
                      initialized as per the configuration.                   **
*******************************************************************************/
#if (SPI_INIT_CHECK_API == STD_ON)
Std_ReturnType Spi_InitCheck(const Spi_ConfigType* const  ConfigPtr)
{
  uint32 CoreId = 0;
  Std_ReturnType ErrStatus = E_NOT_OK;
  uint8 Breakloop = 0;
  uint8 HwMap = 0;

  CoreId = Mcal_GetCpuIndex();
  ErrStatus = Spi_lCheckInitStatus(SPI_SID_INITCHECK, (uint8)SPI_DET_DISABLE);

  /* [cover parentID={FEBF2ED1-49C7-40e1-A64D-926EC3588AF4}]
   Check if Init is proper
  [/cover] */
  if(ErrStatus == (uint8)E_OK)
  {
    /* Check if a valid configuration pointer is obtained */
    if((Spi_kGlobalConfigPtr == ConfigPtr) && (ConfigPtr != NULL_PTR))
    {
      /*[cover parentID={A99AECA4-8D98-4250-92A5-6EE7B1D75CE4}] All critical
      variables configured as expected
      [/cover]*/
      /* Check for all the core variables if initialized as expected */
      ErrStatus = Spi_lCheckCoreVar(CoreId);
      if(ErrStatus == E_OK)
      {
        /*[cover parentID={CB60FA36-6061-4ce2-A3BF-79FE8B49E993}] Check
        critical variables for all assigned kernels
        [/cover]*/
        for(HwMap = 0; HwMap < SPI_MAX_HW_UNIT; HwMap++)
        {
          /* Is QSPI kernel configured */
          /*[cover parentID= {9BB7E2B4-63DA-4DCB-AAE8-2F0EBBEFFFAC}]
                Check if kernel is configured [/cover]*/
          if(Spi_lIsQSPIHwConfigured(HwMap) == (uint8)E_OK)
          {
            /* Check if all registers are initialized as expected */
            ErrStatus = Spi_lCheckRegisters(HwMap);
            if(ErrStatus != E_OK)
            {
              Breakloop = 1U;
            }
            #if(SPI_LEVEL_DELIVERED != 0U)
            if(ErrStatus == E_OK)
            {
                /*[cover parentID= {C9E09139-EE6C-4a9f-BAB0-6AD060B592E3}]
                Async Type [/cover]*/
              if(Spi_lIsQSPIHwConfiguredAsync(HwMap) == (uint8)E_OK)
              {
                /*[cover parentID=
                {A120FA62-3DF6-4448-97C3-74284FE54638}]
                All critical kernel
                variables configured as expected
                [/cover]*/
                /* Check if all kernel variables are initialized */
                ErrStatus = Spi_lCheckKernelVar(HwMap);
                if(ErrStatus != E_OK)
                {
                  Breakloop = 1U;
                }
              }
            }
            #endif
          }
          /*[cover parentID= {5A34F2E3-037B-4236-BD02-9DCB9FE999A6}]
                Any error observed[/cover]*/
          /* Break loop if any error occurred */
          if(Breakloop == 1U)
          {
            break;
          }
        }
      }
    }
    else
    {
      /*[cover parentID={CBC36DB3-BF9A-4f62-B792-1BA0300D1537}] No valid config
      pointer passed
      [/cover]*/
      ErrStatus = E_NOT_OK;
    }
  }

  return ErrStatus;
}

/*******************************************************************************
** Traceability     : [cover parentID={1516BE38-4D60-4484-8EA3-17EA6472A33F}] **
**                                                                            **
** Syntax       : static Std_ReturnType Spi_lCheckBusStatus(void)             **
**                                                                            **
** Service ID      :  NA                                                      **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non reentrant                                           **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  E_OK : Bus is IDLE                                      **
**                    E_NOT_OK : Bus is Busy                                  **
** Description     : Check all bus status variables.                          **
*******************************************************************************/
static Std_ReturnType Spi_lCheckBusStatus(void)
{
  Std_ReturnType ReturnVal = E_OK;

  uint8 HwMap = 0;

  uint32 CoreId = Mcal_GetCpuIndex();
  /*[cover parentID={D72507E3-103B-448b-B943-1A6C6F503175}][/cover]*/
  if(Spi_RuntimeCoreVar[CoreId]->KernelLock != 0U)
  {
    ReturnVal = E_NOT_OK;
  }

  /* Check for Async bus status - Must be in IDLE state */
  for(HwMap = 0; HwMap < SPI_MAX_HW_UNIT; HwMap++)
  {
    #if(SPI_LEVEL_DELIVERED != 0U)
    /* Is QSPI kernel configured */
    /*[cover parentID={2D0C845C-9524-4f63-B9A6-95D3CB1EBEC5}][/cover]*/
    if(Spi_lIsQSPIHwConfiguredAsync(HwMap) == (uint8)E_OK)
    {
       /*[cover parentID={EDA8FFF0-785F-4519-9E81-F97C7CFD2ADF}][/cover]*/
      if(Spi_RuntimeKernelVar[HwMap]->AsyncComStatus != SPI_IDLE)
      {
        ReturnVal = E_NOT_OK;
      }
    }
    #endif
    /*[cover parentID={8931D66B-81E2-4442-8518-35D3DAD7CD5E}][/cover]*/
    if(Spi_lIsQSPIHwConfigured(HwMap) == (uint8)E_OK)
    {
      /*[cover parentID={C0F37100-07B5-4425-9B06-015246A0A739}][/cover]*/
      if(Spi_RuntimeKernelVar[HwMap]->KernelStatus != SPI_IDLE)
      {
        ReturnVal = E_NOT_OK;
      }
    }
    if (ReturnVal == E_NOT_OK)
    {
      break;
    }
  }

  return ReturnVal;
}
/*******************************************************************************
** Traceability     : [cover parentID={B9CDB231-6453-4eab-8768-FC3C9C7FBD45}] **
**                                                                            **
** Syntax       : static Std_ReturnType Spi_lCheckCoreVar(const uint32 CoreId)**
**                                                                            **
** Service ID      :  NA                                                      **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non reentrant                                           **
**                                                                            **
** Parameters (in) :  CoreId - Core id for which all the core variables are   **
** to be verified.                                                            **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  E_OK: When core variables are initialized else returns  **
**                             E_NOT_OK.                                      **
** Description     : Check for all the globals and registers to be            **
**                    initialized as per the configuration.                   **
*******************************************************************************/
static Std_ReturnType Spi_lCheckCoreVar(const uint32 CoreId)
{
  Std_ReturnType ReturnVal = E_OK;

  /*[cover parentID={2E13F810-D5D3-44e5-BC54-92E79C3B2789}] Check for
  IB buffer pointers
  [/cover]*/
  /* Check if IB buffer is initialized */
  /*[cover parentID={8B8E261A-2203-41cf-A153-FC76A90D1890}][/cover]*/
  #if (SPI_CHANNEL_BUFFERS_ALLOWED != 1U)
  if(Spi_lGetTotalIBChannelsInCore(CoreId) != 0U)
  {
    if((Spi_RuntimeCoreVar[CoreId]->TxBuffer == NULL_PTR) \
        || (Spi_RuntimeCoreVar[CoreId]->RxBuffer == NULL_PTR))
    {
      ReturnVal = E_NOT_OK;
    }
  }
  if(ReturnVal == E_OK)
  #endif

  /* Check if mode is properly initialized */
  #if (SPI_LEVEL_DELIVERED == 2U)
  /*[cover parentID={43A2EBAA-F522-447c-BF12-73A1EBE9FEE2}][/cover]*/
  {
    if(Spi_RuntimeCoreVar[CoreId]->AsyncMode != SPI_POLLING_MODE)
    {
      ReturnVal = E_NOT_OK;
    }
  }
  if(ReturnVal == E_OK)
  #endif
  /*[cover parentID={7207F3D8-1C05-4825-9473-ED769BC38F2D}][/cover]*/
  /* Check for IDLe bus status */
  {
    ReturnVal = Spi_lCheckBusStatus();
  }

  #if ((SPI_CHANNEL_BUFFERS_ALLOWED == 1U) || (SPI_LEVEL_DELIVERED != 2U))
  UNUSED_PARAMETER(CoreId);
  #endif

  return ReturnVal;
}

/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax   : static Std_ReturnType Spi_lCheckRegisters(const uint32 KernelId)**
**                                                                            **
** Service ID      :  NA                                                      **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non reentrant                                           **
**                                                                            **
** Parameters (in) :  KernelId - KernelId for which all the variables are to  **
**                      be verified.                                          **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  E_OK: if all registers are intialized as                **
**                             per the configuration                          **
**                    E_NOT_OK : Otherwise.                                   **
**                                                                            **
** Description     : Check for all QSPI registers to be initialized as per the**
**                     configuration.                                         **
*******************************************************************************/
static Std_ReturnType Spi_lCheckRegisters(const uint32 KernelId)
{
  Std_ReturnType ReturnVal = E_OK;
  uint8 RegCheckCount = 0;
  uint8 LoopIndex;
  const Spi_CoreConfigType *CoreConfigPtr =
    Spi_kGlobalConfigPtr->CoreConfigPtr[Mcal_GetCpuIndex()];


  /*[cover parentID={446562ED-FF54-455c-B4BC-30DF9336DE91}] Check if all
  registers are updated as expected
  [/cover]*/
  /* Check all registers */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
     effects foreseen by violating this MISRA rule, as the pointer to
     the object type that it is getting cast into, is a known type. */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
   * effects foreseen by violating this MISRA rule, as the pointer to
   * the object type that it is getting cast into, is a known type. */
  if(SPI_HW_MODULE[KernelId].PISEL.U != (uint32) (IFX_QSPI_PISEL_MRIS_MSK & \
      (uint32)(CoreConfigPtr->QSPIHwConfigPtr[KernelId]->MasterReceivePortPin)))
  {
    RegCheckCount++;
  }
  /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
     effects foreseen by violating this MISRA rule, as the pointer to the
     object type that it is getting cast into, is a known type. */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
   * effects foreseen by violating this MISRA rule, as the pointer to
   * the object type that it is getting cast into, is a known type. */
  if(SPI_HW_MODULE[KernelId].SSOC.U != \
     (uint32) (CoreConfigPtr->QSPIHwConfigPtr[KernelId]->ActiveChipSelectLevel))
  {
    RegCheckCount++;
  }
  /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
     effects foreseen by violating this MISRA rule, as the pointer to the
     object type that it is getting cast into, is a known type. */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
   * effects foreseen by violating this MISRA rule, as the pointer to
   * the object type that it is getting cast into, is a known type. */
  if(SPI_HW_MODULE[KernelId].GLOBALCON.U != \
      (uint32) SPI_GLOBALCON_RST_VAL)
  {
    RegCheckCount++;
  }
  /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
    effects foreseen by violating this MISRA rule, as the pointer
    to the object type that it is getting cast into, is a known type. */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
   * effects foreseen by violating this MISRA rule, as the pointer to
   * the object type that it is getting cast into, is a known type. */
  if(SPI_HW_MODULE[KernelId].GLOBALCON1.U != \
      (uint32) SPI_GLOBALCON1_RST_VAL)
  {
    RegCheckCount++;
  }

  if(RegCheckCount != 0U)
  {
    ReturnVal = E_NOT_OK;
  }

  if(ReturnVal == E_OK)
  {
    for(LoopIndex = 0U; LoopIndex < SPI_MAX_ECON_CHANNEL; LoopIndex++)
    {

      /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access.
      No side effects foreseen by violating this MISRA rule, as the pointer
      to the object type that it is getting cast into, is a known type. */
      /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
       * effects foreseen by violating this MISRA rule, as the pointer to
       * the object type that it is getting cast into, is a known type. */
      if(SPI_HW_MODULE[KernelId].ECON[LoopIndex].U != \
          ((uint32) SPI_ECON_RST_VAL))
      {
        ReturnVal = E_NOT_OK;
        break;
      }
    }
  }

  return ReturnVal;
}

/*******************************************************************************
** Traceability     : [cover parentID={8548AE32-985A-4554-8C5F-5675EC155EF0}] **
**                                                                            **
** Syntax   : static Std_ReturnType Spi_lCheckKernelVar(const uint32 KernelId)**
**                                                                            **
** Service ID      :  NA                                                      **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non reentrant                                           **
**                                                                            **
** Parameters (in) :  KernelId - KernelId for which all the kernel variables  **
are to be verified.                                                           **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  E_OK: All kernel variables are initialized              **
**                    E_NOT_OK : Otherwise.                                   **
**                                                                            **
** Description     : Check for all QSPI kernel variables to be initialized    **
**                   as per the configuration.                                **
*******************************************************************************/
#if(SPI_LEVEL_DELIVERED != 0U)
static Std_ReturnType Spi_lCheckKernelVar(const uint32 KernelId)
{
  Std_ReturnType ReturnVal = E_NOT_OK;
  uint8 LoopIndex = 0U;
  const Spi_DmaTCSType *DmaTxTcsPtr;
  const Spi_DmaTCSType *DmaRxTcsPtr;
  const Spi_QueueType *JobQueuePtr;
  const Spi_CoreConfigType *CoreConfigPtr =
    Spi_kGlobalConfigPtr->CoreConfigPtr[Mcal_GetCpuIndex()];
  JobQueuePtr = Spi_RuntimeKernelVar[KernelId]->JobQueuePtr;

  /* Check if kernel variables are initialized */
  if(Spi_RuntimeKernelVar[KernelId]->JobQueuePtr != NULL_PTR)
  {
    DmaTxTcsPtr = JobQueuePtr->DmaTxTCSPtr;
    DmaRxTcsPtr = JobQueuePtr->DmaRxTCSPtr;

    if((Spi_RuntimeKernelVar[KernelId]->JobQueuePtr->\
        QueueStartIndex == 0U) && \
        (Spi_RuntimeKernelVar[KernelId]->JobQueuePtr->\
         QueueEndIndex == 0U) && \
        (Spi_RuntimeKernelVar[KernelId]->JobQueuePtr->\
         CurrentChannelIndex == 0U) && \
        (Spi_RuntimeKernelVar[KernelId]->JobQueuePtr->\
         CurrentJobIndex == 0U))
    {
      /*[cover parentID={DB18B8DF-4FED-4ca3-975B-9E9F3A06B44E}] Check if all
      TCS RAM variables Destinationa nd receive addressed is updated
      [/cover]*/
      /* Traverse through all the DMA TCS */
      for(LoopIndex = 0U; \
          LoopIndex < CoreConfigPtr->\
          QSPIHwConfigPtr[KernelId]->DMATCSCount;  \
          LoopIndex++)
      {
        /* Check for TX TCS destination address to be "QSPI TX register"
        and RX TCS source to be QSPI RX exit register */
        /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
         * effects foreseen by violating this MISRA rule, as the pointer to
         * the object type that it is getting cast into, is a known type. */
        /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access.
          No side effects foreseen by violating this MISRA rule, as the
          pointer to the object type that it is getting cast into,
          is a known type. */
        if((DmaTxTcsPtr[LoopIndex].DmaDADR.U == (uint32)&\
            (SPI_HW_MODULE[KernelId].DATAENTRY[SPI_FIFO_ENTRY].U)) && \
            (DmaRxTcsPtr[LoopIndex].DmaSADR.U == (uint32)\
             (&(SPI_HW_MODULE[KernelId].RXEXIT.U))))
        {
          ReturnVal = E_OK;
        }
        else
        {
          break;
        }
      }
    }
  }
  return ReturnVal;
}
#endif
#endif

/*******************************************************************************
** Traceability     : [cover parentID={2B2F0EC5-DD29-4445-B534-23C9114D1A3A}] **
**                                                                            **
** Syntax          : void Spi_Init(const Spi_ConfigType* const ConfigPtr)     **
**                                                                            **
** Service ID      :  0x0                                                     **
**                                                                            **
** Sync/Async      :  Synchronous                                             **
**                                                                            **
** Reentrancy      :  Non reentrant                                           **
**                                                                            **
** Parameters (in) :  ConfigPtr - Pointer to configuration set                **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description     : Driver Module Initialization function                    **
** Service for SPI initialization. The Initialization function shall          **
** initialize all SPI relevant registers with the values of the structure     **
** referenced by the parameter ConfigPtr.                                     **
** For Level2 this Function shall set the Handler/Driver Asynchronous         **
** Mechanism Mode in POLLING MODE and all the interrupts may be disabled      **
*******************************************************************************/
/*[cover parentID={890CF5BB-2DE2-41ef-B421-286B6DC41BD1}]*/
void Spi_Init(const Spi_ConfigType* const  ConfigPtr)
{
  uint32 CoreId = 0;
  const Spi_CoreConfigType *CoreConfigPtr = NULL_PTR;
  uint8 HwMap = 0;

  /*[cover parentID={A0996E5F-2DB7-417d-B982-2FCD377CA63B}]
  No action if already initialized [/cover]*/
  /* [cover parentID={FB02D20F-FE9A-4b2a-B8C9-29B1272B8EAD}]
  SPI_DEV_ERROR_DETECT is ON
  [/cover] */
  #if ((SPI_DEV_ERROR_DETECT == STD_ON) || (SPI_SAFETY_ENABLE == STD_ON))
  Std_ReturnType ErrStatus = E_NOT_OK;
  ErrStatus = Spi_lCheckSpiInitParam(ConfigPtr);
  if(ErrStatus == (uint8)E_OK)
  #endif /* SPI_DEV_ERROR_DETECT == STD_ON */
  {
    /* [cover parentID={471146E2-4B4B-4080-AA87-0D9C6B0A1DB3}]
     Get Core config pointer
    [/cover] */
    CoreId = Mcal_GetCpuIndex();

    Spi_kGlobalConfigPtr = ConfigPtr;

    CoreConfigPtr = Spi_kGlobalConfigPtr->CoreConfigPtr[CoreId];

    /* [cover parentID={74EE7998-B2EE-411b-BC98-9F908440A6F0}]
     Initialize all the core run-time variables
    [/cover] */
    Spi_lCoreInit(CoreId);
    /* [cover parentID={D5F1A367-860D-4cee-94A0-234005FE3B84}][/cover] */
    for(HwMap = 0; HwMap < SPI_MAX_HW_UNIT; HwMap++)
    {
      /* [cover parentID={D33F1E17-967B-45bf-BF80-78DEB19DCA67}]
      QSPIx kernel is configured [/cover] */
      /* Is QSPI kernel configured */
      if(Spi_lIsQSPIHwConfigured(HwMap) == (uint8)E_OK)
      {
        #if defined (SPI_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG)
        /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access.
           No side effects foreseen by violating this MISRA rule,
           as the pointer to the object type that it is getting cast into,
           is a known type. */
        /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
         * effects foreseen by violating this MISRA rule, as the pointer to
         * the object type that it is getting cast into, is a known type. */
        SPI_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(                  \
            &SPI_HW_MODULE[HwMap].CLC,                   \
            (uint32)CoreConfigPtr->QSPIHwConfigPtr[HwMap]->ClockSetting);
        #endif

        /* Initialize the QSPI registers to reset values */
        Spi_lQSPIHwResetInit(HwMap);

        /* Set-up Chip select */
        /* [cover parentID={CE0BC812-3EDC-45d6-8473-EBEDF42F52F3}]
         Set-up Chip select
        [/cover] */
        Spi_lQSPIHwInit(HwMap);

        Spi_lAsyncInitPtrRuntimeVar(HwMap);

        /* Update the QSPI Kernel Status to SPI_IDLE */
        Spi_RuntimeKernelVar[HwMap]->KernelStatus = SPI_IDLE;

        /* Set-up async run-time variables */
        #if(SPI_LEVEL_DELIVERED != 0U)
        /* [cover parentID={09266F79-B50C-410d-8ACE-4A11C95CD7E5}]
         QSPIx is asynchronous
        [/cover] */
        if(Spi_lIsQSPIHwConfiguredAsync(HwMap) == (uint8)E_OK)
        {
          Spi_lResetAsyncQueueVar(HwMap);

          Spi_lQSPIHwDMAInit(HwMap);
        }
        #endif
      }
    }

    /* Check for IB buffer assigned to core,
     * Set-up IB buffer for all the IB channels in Core */
     /* [cover parentID={E63059F6-22B6-4c7b-9ABD-80834E8F58C9}][/cover] */
    if(Spi_lGetTotalIBChannelsInCore(CoreId) != 0U)
    {
      Spi_lInitIBBuffer();
    }

    /* Always set default as polling - Applicable for L2 only */
    /* [cover parentID={8DD90C92-EC86-40d1-B523-26828F06D7FC}]
     Level delivered is 2
    [/cover] */
    #if(SPI_LEVEL_DELIVERED == 2U)
    /* [cover parentID={98C4A07F-DE8E-4a5e-B485-E1F644789A0A}]
     Set default asynchronous mode as polling
    [/cover] */
    Spi_RuntimeCoreVar[CoreId]->AsyncMode = SPI_POLLING_MODE;
    #endif

    #if(SPI_LEVEL_DELIVERED != 0U)
    for(HwMap = 0; HwMap < SPI_MAX_HW_UNIT; HwMap++)
    {
      /* Is QSPI kernel configured */
      /* [cover parentID={724E4B82-C06B-4370-8CD1-B6A10C0B24AF}][/cover] */
      if(Spi_lIsQSPIHwConfiguredAsync(HwMap) == (uint8)E_OK)
      {
        Spi_RuntimeKernelVar[HwMap]->AsyncComStatus = SPI_IDLE;
      }
    }
    #endif

  } /* ConfigPtr == NULL */
} /* End of function Spi_Init */
/*[/cover]*/
/*******************************************************************************
** Traceability     : [cover parentID={C6A14379-14AA-4f08-A7FF-D9F7F845090C}] **
**                                                                            **
** Syntax          : Std_ReturnType Spi_DeInit(void)                          **
**                                                                            **
** Service ID      : 0x01                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: de-initialization command has been accepted.       **
**                   E_NOT_OK: de-initialization command has not been accepted**
**                                                                            **
** Description     : This API de-initializes the hardware and                 **
**                   global variables related to SPI driver                   **
*******************************************************************************/
Std_ReturnType Spi_DeInit(void)
{
  Std_ReturnType RetVal = E_OK;
  #if(SPI_LEVEL_DELIVERED != 0U)
  uint8 HwMap = 0;
  #endif
  uint8 LoopIndex = 0U;
  /* [cover parentID={DC697E06-8903-4f2c-A99D-6C173F374843}]
   Get Core Information
  [/cover] */
  /* Get Core Information */
  uint32 CoreId = Mcal_GetCpuIndex();
  SpiCommsTypes temp;

  uint8  ClearGlobalPtr = 1;
  /* [cover parentID={AC451ECF-B933-4ec6-9574-7ABF1A7A7AEE}]
   Check the driver is initialized
  [/cover] */
  /* Check if Driver is initialized */
  /* [cover parentID={DCA5B64D-CFC4-490f-99F1-DE0A3D6AFF49}]
   SPI_DEV_ERROR_DETECT is ON
  [/cover] */
  #if ((SPI_DEV_ERROR_DETECT == STD_ON) || (SPI_SAFETY_ENABLE == STD_ON))
  RetVal = Spi_lCheckInitStatus(SPI_SID_DEINIT, (uint8)SPI_REPORT_DET);
  /* [cover parentID={421B212B-FE7B-4c57-A5F3-A61F477A74A9}]
   Driver is initialized
  [/cover] */
  if(RetVal == (uint8)E_OK)
  #endif
  {
    /* [cover parentID={BF2A8C33-312A-419c-B90E-6A7D86056FD9}]
     Check the driver status is SPI_IDLE for processing deinit
    [/cover] */
    /* Check if the driver is IDLE for processing deinit */
    temp = SPI_BOTH;
    /* [cover parentID={5DEBA144-2E9F-4ce2-A084-3074BD3F8B1E}][/cover] */
    /* [cover parentID={F625432D-FF17-4ce4-89EC-599ACD773B75}][/cover] */
    RetVal = Spi_lIsStatusBusy(temp);
    if(RetVal == (uint8)E_NOT_OK)
    {

      #if(SPI_LEVEL_DELIVERED != 0U)
      for(HwMap = 0; HwMap < SPI_MAX_HW_UNIT; HwMap++)
      {
        /* Is QSPI kernel configured */
        if(Spi_lIsQSPIHwConfiguredAsync(HwMap) == (uint8)E_OK)
        {
          Spi_RuntimeKernelVar[HwMap]->AsyncComStatus = SPI_UNINIT;
        }
      }
      #endif

      /* [cover parentID={BA66C133-A3D3-4100-8F72-324F1C83850A}]
         Loop through all Kernels of core to check if configured
        [/cover] */
      /* Loop through all the QSPI configured for core */
      for(LoopIndex = 0U; LoopIndex < (uint8)SPI_MAX_HW_UNIT; LoopIndex++)
      {
        /* [cover parentID={04CBA3FD-E74D-4ace-95AD-184FCA3B9679}]
         Check QSPIx is configured
        [/cover] */
        if(Spi_lIsQSPIHwConfigured(LoopIndex) == (uint8)E_OK)
        {
        /* [cover parentID={25923553-38CB-48f4-9A76-4A6CF4DDE8A4}]
         QSPIx is configured
        [/cover] */
          /* [cover parentID={1E8C16F8-8D0C-4818-A9F1-EB89976213DF}]
           De-initialize QSPIx kernel configuration
          [/cover] */
          /* [cover parentID={D2475564-32F3-4c8f-B367-0726C8892013}]
           De-Initialize variables and SFRs related to QSPI Hw
          [/cover] */
          /* De-Initialize variables and SFRs related to QSPI Hw */
          Spi_lQSPIHwResetInit(LoopIndex);
          /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access.
            No side effects foreseen by violating this MISRA rule,
            as the pointer to the object type that it is
            getting cast into, is a known type. */
          /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
           * effects foreseen by violating this MISRA rule, as the pointer to
           * the object type that it is getting cast into, is a known type. */
          SPI_INIT_DEINIT_WRITE_PERIP_ENDINIT_PROTREG(                        \
              &SPI_HW_MODULE[LoopIndex].CLC,                     \
              (uint32)SPI_QSPI_CLC_DISR_DISABLE);

      /* set the KernelStatus to SPI_UNINIT */
          Spi_RuntimeKernelVar[LoopIndex]->KernelStatus = SPI_UNINIT;
          Spi_RuntimeKernelVar[LoopIndex] = NULL_PTR;
        }
      }

      /* Reset all kernel / core pointers */
      Spi_RuntimeCoreVar[CoreId] = NULL_PTR;

      for(LoopIndex = 0U; LoopIndex < (uint8)MCAL_NO_OF_CORES; LoopIndex++)
      {
        /* Check if all run-time variables of all Cores are NULL */
        if(Spi_RuntimeCoreVar[LoopIndex] != NULL_PTR)
        {
          ClearGlobalPtr = 0U;
        }
      }

      /* Clear global configuration */
      /* [cover parentID={358DDA74-9A5D-445a-B887-BCDBC51E310F}][/cover] */
      if(ClearGlobalPtr == 1U)
      {
        Spi_kGlobalConfigPtr = NULL_PTR;
      }

      /* [cover parentID={13453510-8CF2-4cbb-9FDE-455EE6DD11B4}]
       Set return value as E_OK
      [/cover] */
      /* Return E_OK */
      RetVal = E_OK;
    }
    else
    {
      /* [cover parentID={F9A2D1F8-5C57-4791-BC61-029B45ED96E4}]
       Set return value as E_NOT_OK
      [/cover] */
      RetVal = E_NOT_OK;
    }
  }
  return RetVal;
} /* End of function Spi_DeInit */

#if(SPI_DEV_ERROR_DETECT == STD_ON) || (SPI_SAFETY_ENABLE == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={65CE97FF-E7D9-48d8-B4E0-2B099EA1EA08}] **
** Syntax          : Std_ReturnType Spi_lCheckChannelParam(                   **
**                                   const uint8 Api,                         **
**                                   uint8 *const Channel,                    **
**                                   const uint8 ApplicationChannelNumber,    **
**                                   const uint8 BufEbIb)                     **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : Api: Service ID of API                                   **
**                                                                            **
**                   ApplicationChannelNumber : channel-id from application   **
**                   DataWidth: Check if channel is EB or IB                  **
**                                                                            **
** Parameters (out):  Channel : Physical Channel ID if sequence is            **
**                                        valid                               **
**                                                                            **
** Return value    : E_OK for valid channel else E_NOT_OK                     **
**                                                                            **
** Description     : This function checks if the application passed           **
**                   channel-id is valid before operating on the parameter,   **
**                   this function returns the physical-id as well for the    **
**                   application channel-id.                                  **
*******************************************************************************/
static Std_ReturnType Spi_lCheckChannelParam(const uint8 Api,
                                       uint8 * const Channel,
                                      const uint8 ApplicationChannelNumber,
                                      const uint8 BufEbIb)
{
  /* Get core information */
  Std_ReturnType RetVal = E_NOT_OK;
  uint32 CoreId = Mcal_GetCpuIndex();
  const Spi_CoreConfigType *CoreConfigPtr;
  uint8 ChannelId;

  /*  Check if driver is not initialized */
  /* [cover parentID={690F9C55-49C7-4c76-B0DD-4F91B9977A35}][/cover] */
  RetVal = Spi_lCheckInitStatus(Api, (uint8)SPI_REPORT_DET);
  if(RetVal == (uint8)E_OK)
  {
    /* Check if channel is with-in range and assigned to Core */
    /* [cover parentID={BA0F6CB9-DFE8-460c-B8A0-38E9C95DBE6F}]
     Implement parameter checking
    [/cover] */
    /* [cover parentID={61912013-07D4-4421-9FE2-A34ACD3CD77D}]
     Channel is not with-in range
    [/cover] */
    if(ApplicationChannelNumber < Spi_kGlobalConfigPtr->NoOfChannels)
    {
      ChannelId = \
                  Spi_kGlobalConfigPtr->ChannelLookup[ApplicationChannelNumber];
      /* Check for channel within Core configuration range and check if
          valid channel configuration (EB / IB) */
      /* [cover parentID={F7AD0A4A-B09A-41a3-BA72-9C3F50F8308C}]
      Check if channel is assigned to core [/cover] */
      CoreConfigPtr = Spi_kGlobalConfigPtr->CoreConfigPtr[CoreId];
      if((ChannelId < CoreConfigPtr->NoOfChannels) &&
          (CoreConfigPtr->ChannelConfigPtr[ChannelId].ChannelType ==
           BufEbIb) &&
          (CoreConfigPtr->ChannelConfigPtr[ChannelId].ChannelId ==
           ApplicationChannelNumber))
      {
        *Channel = ChannelId;
        RetVal = E_OK;
      }
      else
      {
      /* [cover parentID={E4BA4182-981B-4b73-A0F0-327CE57C575C}]
       return not ok [/cover] */
        RetVal = E_NOT_OK;
        #if (SPI_MULTICORE_ERROR_DETECT == STD_ON)
        /* Report DET for invalid channel */
        /* [cover parentID={7A1EE8D3-41B0-49d3-8A2A-ED3ED507E070}][/cover] */
        Spi_lReportMulticoreError(Api, SPI_E_NOT_CONFIGURED);
        #else
        /* [cover parentID={2A266F8F-B99B-461b-B694-955184727C91}]
            Report error invalid channel SPI_E_PARAM_CHANNEL
           [/cover] */
        /* [cover parentID={689D7163-D48A-44cf-A233-6BF4236CDFD6}]
         Report error invalid channel SPI_E_PARAM_CHANNEL
        [/cover] */

        Spi_lReportError(Api, SPI_E_PARAM_CHANNEL );
        #endif
      }
    }
    else
    {
      /* [cover parentID={E4BA4182-981B-4b73-A0F0-327CE57C575C}]
       return not ok [/cover] */
      RetVal = E_NOT_OK;
      /* Report DET as not configured to this core */
      /* [cover parentID={2A266F8F-B99B-461b-B694-955184727C91}]
       Report error invalid channel SPI_E_PARAM_CHANNEL
      [/cover] */
      Spi_lReportError(Api, SPI_E_PARAM_CHANNEL );
    }
  }
  return RetVal;
}

/*******************************************************************************
** Traceability     : [cover parentID={2D629E1A-1FC2-43ec-B76D-9D9B591B5F18}] **
** Syntax          : Std_ReturnType Spi_lCheckSeqParam(const uint8 Api,       **
**                    Spi_SequenceType *const Sequence,                       **
**                    const Spi_SequenceType AppSequenceId,                   **
**                                        const uint8 SyncAsyncIgnore)        **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : Api    : Service ID of API                               **
**                   AppSequenceId: Sequence id passed from application       **
**                   SyncAsyncIgnore  : Sync(0) Or Async(1) Comms Or Ignore   **
**                   Ignore(4) - When no operation on Buffer                  **
**                                                                            **
** Parameters (out): Sequence     : Physical sequence ID if sequence is valid **
**                                                                            **
** Return value    : returns E_OK on valid sequence else E_NOT_OK             **
**                                                                            **
** Description     : Checks if the application passed sequence Id is a valid  **
**                   sequence to be transmitted and returns the "physical id" **
                     in the core configuration.                               **
*******************************************************************************/
static Std_ReturnType Spi_lCheckSeqParam
(
  const uint8 Api, Spi_SequenceType *const Sequence,
  const Spi_SequenceType AppSequenceId, const uint8 SyncAsyncIgnore
)
{
  /*Initialize return value as E_NOT_OK and check if Driver is
  not initialized   */
  Std_ReturnType RetVal = E_NOT_OK;
  uint32 CoreId = Mcal_GetCpuIndex();
  const Spi_CoreConfigType *CoreConfigPtr;
  #if (MCAL_AR_VERSION == MCAL_AR_422)
  uint8 SyncAsyncComms = 0;
  #endif
  uint8 SequenceId = 0;

  /* [cover parentID={72038943-B89A-4d8f-B465-566EA5511E86}]
     Check if driver is initialized
     [/cover] */
  /* Check if Driver is initialized */
  RetVal = Spi_lCheckInitStatus(Api, (uint8)SPI_REPORT_DET);
  if(RetVal == (uint8)E_OK)
  {
    /* [cover parentID={9CDA3989-F3DC-4a56-8691-1C2183A8D00E}]
     Sequence is not with-in range
    [/cover] */
    /* [cover parentID={71727B87-A217-4f65-AEC3-1060E700662F}]
     Sequence for valid sequence
     [/cover] */
    /* Check if sequence is with-in range and assigned to core */
    if(AppSequenceId < Spi_kGlobalConfigPtr->NoOfSequences)
    {
      SequenceId = Spi_kGlobalConfigPtr->SequenceLookup[AppSequenceId];
      CoreConfigPtr = Spi_kGlobalConfigPtr->CoreConfigPtr[CoreId];
      #if (MCAL_AR_VERSION == MCAL_AR_422)
      if((SyncAsyncIgnore == (uint8)SPI_IGNORE_COMMS_TYPE_CHECK) || \
          (SyncAsyncIgnore == \
           CoreConfigPtr->SequenceConfigPtr[SequenceId].u8Comm))
      {
        SyncAsyncComms = 1;
      }
      #endif
      /* [cover parentID={3CB7F28D-06CD-4b52-B1E1-B744D9642291}]
      Check if sequence belongs to this core
      [/cover] */
      /* Check if the Sequence is of type Sync / Async and logical
        sequence ID passed by application maps to physical sequence ID */
      #if (MCAL_AR_VERSION == MCAL_AR_422)
      if((SequenceId < CoreConfigPtr->NoOfSequences) && \
          (SyncAsyncComms == 1U) && \
          (CoreConfigPtr->SequenceConfigPtr[SequenceId].SequenceId == \
           AppSequenceId))
      #else
      if((SequenceId < CoreConfigPtr->NoOfSequences) && \
          (CoreConfigPtr->SequenceConfigPtr[SequenceId].SequenceId == \
           AppSequenceId))
      #endif
      {
        *Sequence = SequenceId;
        RetVal = E_OK;
      }
      else
      {
        RetVal = E_NOT_OK;
        #if ((SPI_MULTICORE_ERROR_DETECT == STD_ON) || (SPI_SAFETY_ENABLE == STD_ON))
          /* [cover parentID={61EB7FDA-35AC-4bbd-B4D5-3D92B394092D}][/cover] */
          /* Report DET as not configured to this core */
          Spi_lReportMulticoreError(Api, SPI_E_NOT_CONFIGURED);
        #else
          /* [cover parentID={0259108B-0177-438f-98AE-3799412B5252}][/cover] */
          Spi_lReportError(Api, SPI_E_PARAM_SEQ);
        #endif
      }
    }
    else
    {
      RetVal = E_NOT_OK;
      /* [cover parentID={0A8DCEDF-FFD1-466c-BD79-AE02EE8D7B4B}]
         Report error SPI_E_PARAM_SEQ
         [/cover] */

      Spi_lReportError(Api, SPI_E_PARAM_SEQ);
    }
  }
  #if (MCAL_AR_VERSION == MCAL_AR_440)
   UNUSED_PARAMETER(SyncAsyncIgnore);
  #endif
  return RetVal;
}
#endif


#if(SPI_LEVEL_DELIVERED != 1U)
/*******************************************************************************
** Traceability     : [cover parentID={C188D8C7-1D99-46b0-A4A3-1D6954BA29AB}] **
**                                                                            **
** Syntax          : Std_ReturnType Spi_SyncTransmit                          **
**                       (const Spi_SequenceType Sequence)                    **
**                                                                            **
** Service ID      : 0x0A                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : Sequence - Sequence Id                                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK     : Synchronous transmission request is accepted  **
**                   E_NOT_OK : Synchronous transmission request is rejected  **
**                                                                            **
** Description     : This API transmits the sequence synchronously over the   **
**                   QSPI buses defined by the jobs associated with the       **
**                   sequence. This API is synchronous, which means the       **
**                   application invoking the API is blocked till the         **
**                   sequence is transmitted completely.                      **
*******************************************************************************/
/* [cover parentID={9F00E433-7E5B-4b9f-81C7-51910D4AE4AC}][/cover] */
/* [cover parentID={02B1AFF8-7D20-4762-8ECD-FE9C2EAB6182}][/cover] */
Std_ReturnType Spi_SyncTransmit(const Spi_SequenceType Sequence)
{
  /* [cover parentID={5E3F6E79-BF62-4338-9CF8-10C2C0EC32D9}]
   Get core information and initialize the return value as E_NOT_OK
  [/cover] */
  Std_ReturnType RetVal = E_NOT_OK;
  uint32 CoreId = Mcal_GetCpuIndex();
  const Spi_CoreConfigType *CoreConfigPtr;
  uint8 PhysicalSeqId = 0U;
  uint8 temp;
  #if (MCAL_AR_VERSION == MCAL_AR_440)
  #if (SPI_LEVEL_DELIVERED == 2U)
  Spi_JobType StartId = 0U;
  Spi_JobType EndId = 0U;
  Spi_JobType JobId;
  #endif
  #endif
  /* [cover parentID={CAD07645-AE60-407a-876A-4B98D5D1F249}]
  SPI_DEV_ERROR_DETECT or SPI_SAFETY_ENABLE is ON
  [/cover] */
  #if ((SPI_DEV_ERROR_DETECT == STD_ON) || (SPI_SAFETY_ENABLE == STD_ON))
  /* [cover parentID={F9320784-0056-4a5e-9DDF-CD66493E6AB1}]
   Check the sequence ID passed is valid
  [/cover] */
  /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of variable PhysicalSeqId
    is used inside Spi_lCheckSeqParam() only to read values.
    The address is not stored for later usage in Spi_lCheckSeqParam().
    Hence it is safe to pass the address of the local variable. */
  RetVal = Spi_lCheckSeqParam(SPI_SID_SYNCTRANSMIT, &PhysicalSeqId,
                              Sequence, (uint8)SPI_SYNC_COMMS_TYPE);
  if(RetVal == (uint8)E_OK)
  #else
  /* [cover parentID={CB55B553-93ED-4562-9CCB-6ED3B6EE9023}][/cover] */
  /* If DET / SAFETY is OFF - Get sequence ID from look-up directly */
  PhysicalSeqId = Spi_kGlobalConfigPtr->SequenceLookup[Sequence];
  #endif
    /* [cover parentID={E8817E95-6C6C-4f5e-8D45-B1B1E7847D28}]
     Sequence ID is valid
    [/cover] */
  {
    CoreConfigPtr = Spi_kGlobalConfigPtr->CoreConfigPtr[CoreId];
    temp = CoreConfigPtr->SequenceConfigPtr[PhysicalSeqId].HwModuleUsed;

    /* [cover parentID={18D86A38-926A-4dd7-9812-392EDBB48AB3}]
      Lock and Update kernel / driver status to SPI_BUSY before transmission
     [/cover] */
    /* [cover parentID={2E4EB335-F754-4b65-90BA-D6D51A4A9B96}][/cover] */
    SchM_Enter_Spi_SyncLock();

    /* [cover parentID={6FFDE37E-7CDE-4c9d-BDCB-4AF43A9F5AC2}]
     SPI_SUPPORT_CONCURRENT_SYNC_TRANSMIT
    [/cover] */
    #if(SPI_SUPPORT_CONCURRENT_SYNC_TRANSMIT == STD_ON)
    /* Check if QSPI IP is transmitting a sequence */
    if(Spi_RuntimeKernelVar[temp]->KernelStatus == SPI_IDLE)
      /* [cover parentID={C42E3840-F02B-4a99-85C7-85304B1D5C4B}]
       Support for concurrent synchronous transmission is OFF
      [/cover] */
    #else
    /* Check if the QSPI driver status is BUSY - One of the QSPI assigned to
        core is transmitting a sequence */
    if((Spi_RuntimeKernelVar[temp]->KernelStatus == SPI_IDLE)
        && (Spi_RuntimeCoreVar[CoreId]->KernelLock == 0U))
    #endif
      /* [cover parentID={E9FA4584-684A-48db-9659-FDD68C5E573D}]
       QSPI not busy
      [/cover] */
    {
      /* [cover parentID={63A3DC8E-0A07-4304-A4DB-FB565C98014D}]
       Lock kernel
      [/cover] */
      Spi_RuntimeCoreVar[CoreId]->KernelLock |= (uint32)(1UL<<temp);

      /* [cover parentID={223FB761-0A30-4AD8-B380-A348933A8C25}][/cover] */
      /* Update the Kernel status to SPI_BUSY */
      Spi_RuntimeKernelVar[temp]->KernelStatus = SPI_BUSY;

      /* [cover parentID={186501B5-12E1-4987-8CC3-52F52EC321F9}]
      Reentrant function [/cover] */
      /* Release lock */
      SchM_Exit_Spi_SyncLock();

      /* [cover parentID={D8357FF1-588C-4f23-B22F-4C2C6F770C45}]
       Transmit
      [/cover] */
      /* [cover parentID={1F968DD8-4408-4054-B71F-F9AEDFD46ECD}]
       Get the return value
      [/cover] */
      RetVal = Spi_lSyncTransmit(PhysicalSeqId);

      /* [cover parentID={A0622DC3-D4F6-4987-BDB5-2D0195D96BF0}]
      Reentrant function[/cover] */
      /* Lock and Update kernel / driver status to IDLE after transmission */
      SchM_Enter_Spi_SyncLock();
      Spi_RuntimeCoreVar[CoreId]->KernelLock &= (uint32)(~(1UL<<temp));

      /* Update the Kernel status to SPI_IDLE */
      /* [cover parentID={2816B8E0-25CB-4b1f-97D3-05F32324CCD9}][/cover] */
      #if (MCAL_AR_VERSION == MCAL_AR_440)
      #if (SPI_LEVEL_DELIVERED == 2U)
      /* [cover parentID={99628208-D609-4f4d-AA03-E0F0C63435B5}]
      Check if JobQueuePtr is Initialized and StartId equals EndId[/cover] */
      if(Spi_RuntimeKernelVar[temp]->JobQueuePtr != NULL_PTR)
      {
        StartId = Spi_RuntimeKernelVar[temp]->JobQueuePtr->QueueStartIndex;
        EndId = Spi_RuntimeKernelVar[temp]->JobQueuePtr->QueueEndIndex;
      }

      if(StartId == EndId)
      #endif
      #endif
      {
       Spi_RuntimeKernelVar[temp]->KernelStatus = SPI_IDLE;
      }
      /* Release lock */
      SchM_Exit_Spi_SyncLock();
      /* [cover parentID={5FE4AFFA-9879-4edf-8326-128018961F40}][/cover] */
      #if(MCAL_AR_VERSION == MCAL_AR_440)
      #if (SPI_LEVEL_DELIVERED == 2U)
      /* Enter SchM */
      SchM_Enter_Spi_Queue_Update();
      /* [cover parentID={411B9922-1814-401d-833C-5FE6ED940045}][/cover] */

      if(StartId != EndId)
      {
        Spi_RuntimeKernelVar[temp]->AsyncComStatus = SPI_BUSY;
        JobId = Spi_RuntimeKernelVar[temp]->JobQueuePtr->
                   JobAndSeqQueuePtr[StartId].QueueJobId;
        Spi_RuntimeKernelVar[temp]->JobQueuePtr->CurrentJobIndex = 0U;

        /* Start Next Job in the Queue */
        Spi_lAsyncStartJob(JobId);
      }

      /* Enter SchM */
      SchM_Exit_Spi_Queue_Update();
      #endif
      #endif
    }
    else  /* Report DET as Sequence in progress */
    {
      /* [cover parentID={186501B5-12E1-4987-8CC3-52F52EC321F9}]
      Reentrant function [/cover] */
      /* Release lock */
      SchM_Exit_Spi_SyncLock();
      #if ((SPI_DEV_ERROR_DETECT == STD_ON) || (SPI_SAFETY_ENABLE == STD_ON))
      RetVal = E_NOT_OK;
      #endif
      #if (((MCAL_AR_VERSION == MCAL_AR_422) && \
      ((SPI_DEV_ERROR_DETECT == STD_ON) || (SPI_SAFETY_ENABLE == STD_ON))) || \
      ((MCAL_AR_VERSION == MCAL_AR_440) && (SPI_RUNTIME_ERROR_DETECT == STD_ON)))
      /* [cover parentID={983EDCE2-A819-4ece-A83E-C0C6845002DB}]
      Report runtime error [/cover] */
      Spi_lReportRuntimeDetError(SPI_SID_SYNCTRANSMIT, SPI_E_SEQ_IN_PROCESS);
      #endif
    }

  }
  /* [cover parentID={DFD2402A-EB24-495f-9993-C1890F8E39C2}]
   Return status
  [/cover] */
  return RetVal;
}
#endif /* SPI_LEVEL_DELIVERED != 1U */

#if (MCAL_AR_VERSION == MCAL_AR_440)
#if(SPI_LEVEL_DELIVERED == 2U)
/*******************************************************************************
** Traceability     : [cover parentID={6062F736-AF8B-4256-B77B-436832840479}] **
**                                                                            **
** Syntax          : Std_ReturnType Spi_lValidateDMAConfiguration             **
**                   (const Spi_SequenceType Sequence)                        **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : Sequence - Sequence ID                                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: DMA Channels are configured                        **
**                   E_NOT_OK: DMA channels are not configured                **
**                                                                            **
** Description     : Checks for the DMA channel configuration                 **
*******************************************************************************/
static Std_ReturnType Spi_lValidateDMAConfiguration(const Spi_SequenceType Sequence)
{
  Spi_JobType JobIndex;
  uint8 HwModule;
  Std_ReturnType RetVal = E_OK;

  /* Get the core information */
  uint32 CoreId = Mcal_GetCpuIndex();
  const Spi_CoreConfigType *CoreConfigPtr =
    Spi_kGlobalConfigPtr->CoreConfigPtr[CoreId];

  JobIndex =
      CoreConfigPtr->SequenceConfigPtr[Sequence].JobLinkPtrPhysical[0U];
  HwModule = CoreConfigPtr->JobConfigPtr[JobIndex].HwUnit &           \
               SPI_HWUNIT_MASK;

  /* Check if DMA channels are configured for the QSPI HW, If not reject
   * the request */
  /* [cover parentID={24710AB8-025E-41f3-87D0-B594A9BF2191}]
    Check for DMA configuration[/cover] */
  if ((CoreConfigPtr->QSPIHwConfigPtr[HwModule]->DMARxChannel == \
                               SPI_DMA_CHNL_INVALID) \
        || (CoreConfigPtr->QSPIHwConfigPtr[HwModule]->DMATxChannel ==  \
                               SPI_DMA_CHNL_INVALID))
  {
    /* [cover parentID={2FACFC68-7BB5-462a-ACDD-48364D56F70D}]
    Report DET SPI_E_DMA_CHANNEL_NOT_CONFIGURED[/cover] */
    #if ((SPI_DEV_ERROR_DETECT == STD_ON) || (SPI_SAFETY_ENABLE == STD_ON))
    Spi_lReportError(SPI_SID_ASYNCTRANSMIT,
                 SPI_E_DMA_CHANNEL_NOT_CONFIGURED);
    #endif
    RetVal = E_NOT_OK;
  }

  return RetVal;
}
#endif
#endif

#if(SPI_LEVEL_DELIVERED != 0U)
/*******************************************************************************
** Traceability     : [cover parentID={A9F5FE85-F0D8-45E1-B33E-6DDA2D01E937}] **
**                                                                            **
** Syntax          : Std_ReturnType Spi_lValidateMoveCounterLimit             **
**                   (const Spi_SequenceType Sequence)                        **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : Sequence - Sequence ID                                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: Move Counter limit is not exceeded                 **
**                   E_NOT_OK: Move Counter limit is exceeded                 **
**                                                                            **
** Description     : Checks for the Move counter                              **
**                   8190 elements limitation                                 **
*******************************************************************************/
static Std_ReturnType Spi_lValidateMoveCounterLimit(const Spi_SequenceType Sequence)
{
  const Spi_SequenceConfigType* SeqConfigPtr;
  const Spi_JobConfigType* JobConfigPtr;
  uint32 NoOfElements;
  Spi_JobType JobId, JobIndex;
  Std_ReturnType RetVal = E_OK;

  /* Get the core information */
  uint32 CoreId = Mcal_GetCpuIndex();
  const Spi_CoreConfigType *CoreConfigPtr =
    Spi_kGlobalConfigPtr->CoreConfigPtr[CoreId];

  /* Get the sequence configuration from core configuration */
  SeqConfigPtr = &CoreConfigPtr->SequenceConfigPtr[Sequence];

  /* Initialize Job Index to the first job and fetch first job */
  JobIndex = 0U;
  JobId = SeqConfigPtr->JobLinkPtrPhysical[JobIndex];
  do
  {
    JobConfigPtr = &CoreConfigPtr->JobConfigPtr[JobId];
    NoOfElements = Spi_lGetTotalBytesOfJob(JobConfigPtr);
    /* [cover parentID={AF8EAB64-B206-46aa-A6EC-63E0FB9F6D00}]
    Check for 8190 elements[/cover] */
    if (NoOfElements > SPI_MOVE_COUNTER_LIMIT)
    {
      RetVal = E_NOT_OK;
      break;
    }
    /* Traverse through next job for transmisaion */
    JobIndex++;
    JobId = SeqConfigPtr->JobLinkPtrPhysical[JobIndex];
  /* Check if all jobs are transmitted */
  } while(JobId != SPI_JOB_DELIMITER);

  /* Report Move counter DET */
  if (RetVal == E_NOT_OK)
  {
    /* [cover parentID={AF60586F-91B4-4376-8277-B591EEF3A069}]
    Report SPI_E_MOVECOUNTER_LIMIT_EXCEEDED [/cover] */
    #if ((SPI_DEV_ERROR_DETECT == STD_ON) || (SPI_SAFETY_ENABLE == STD_ON))
    Spi_lReportError(SPI_SID_ASYNCTRANSMIT,
               SPI_E_MOVECOUNTER_LIMIT_EXCEEDED);
    #endif
  }

  return RetVal;
}
/*******************************************************************************
** Traceability     : [cover parentID={04B0F0FC-AF2D-4fa7-9FC9-5C7C7230E393}] **
**                                                                            **
** Syntax          : Std_ReturnType Spi_AsyncTransmit                         **
**                   (const Spi_SequenceType Sequence)                        **
**                                                                            **
** Service ID      : 0x03                                                     **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : Sequence - Sequence ID                                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: Transmit request accepted                          **
**                   E_NOT_OK: Transmit request rejected                      **
**                                                                            **
** Description     : This API transmits the sequence asynchronously over the  **
**                   QSPI buses defined by the jobs associated with the       **
**                   sequence. This API is asynchronous, which means the      **
**                   application invoking the API is not blocked till the     **
**                   sequence is transmitted completely and completion of     **
**                   transmission would be notified (if configured).          **
*******************************************************************************/
/* [cover parentID={9F00E433-7E5B-4b9f-81C7-51910D4AE4AC}][/cover] */
Std_ReturnType Spi_AsyncTransmit(const Spi_SequenceType Sequence)
{
  const Spi_JobType* SeqJobLinkPtr;
  Spi_JobType JobIndex;
  Std_ReturnType RetVal = E_NOT_OK;
  uint8 HwModule;
  uint32 CoreId;
  const Spi_CoreConfigType *CoreConfigPtr;
  uint8 SeqIndex = 0;

  /* [cover parentID={22753B04-4DC8-4052-950D-795AC66F3C8D}]
   Get core information
  [/cover] */
  /* Get Core information */
  CoreId = Mcal_GetCpuIndex();
  /* [cover parentID={3B9C8D0A-6932-468c-ABA8-82309F1A10E1}]
  SPI_DEV_ERROR_DETECT or SPI_SAFETY_ENABLE is ON
  [/cover] */
  #if ((SPI_DEV_ERROR_DETECT == STD_ON) || (SPI_SAFETY_ENABLE == STD_ON))
  /* [cover parentID={81B220A3-BCA0-4819-AA20-B6D9667DA441}]
   Check if the sequence ID passed is valid
  [/cover] */
  /* Check if the sequence ID passed is valid */
  /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of variable SeqIndex
    is used inside Spi_lCheckSeqParam() only to read values.
    The address is not stored for later usage in Spi_lCheckSeqParam().
    Hence it is safe to pass the address of the local variable. */
  RetVal = Spi_lCheckSeqParam(SPI_SID_ASYNCTRANSMIT, &SeqIndex,
                              Sequence, (uint8)SPI_ASYNC_COMMS_TYPE);
  /* [cover parentID={7E4D63A8-E89D-44ce-B0DA-7BE84E849917}]
   Sequence ID is valid
  [/cover] */
  if(RetVal == (uint8)E_OK)
  #else
  /* [cover parentID={16FF7ECD-A916-4f5d-8244-BB0DACE8F803}][/cover] */
  /* If DET / SAFETY is OFF - Get the sequence ID from
      look-up table directly */
  SeqIndex = Spi_kGlobalConfigPtr->SequenceLookup[Sequence];
  #endif
  {
    CoreConfigPtr = Spi_kGlobalConfigPtr->CoreConfigPtr[CoreId];
    /* Get the first job ID of sequence */
    JobIndex =
      CoreConfigPtr->SequenceConfigPtr[SeqIndex].JobLinkPtrPhysical[0U];
    HwModule = CoreConfigPtr->JobConfigPtr[JobIndex].HwUnit &           \
               SPI_HWUNIT_MASK;
    RetVal =  Spi_lValidateMoveCounterLimit(SeqIndex);
    /* [cover parentID={ED8F1966-A634-45ee-BF62-074CE47A3257}][/cover] */
    if (RetVal == E_OK)
    {
      /* [cover parentID={F1C29AF0-F44A-4672-9DF8-26E3AB7F8198}][/cover] */
      /* Check if Async transmit request can be accepted or not */
      #if (MCAL_AR_VERSION == MCAL_AR_440)
      #if (SPI_LEVEL_DELIVERED == 2U)
      RetVal = Spi_lValidateDMAConfiguration(SeqIndex);
      /* [cover parentID={441C82F0-700B-48bc-A4D6-39150C950A2C}][/cover] */
      if (RetVal == E_OK)
      #endif
      #endif
      {
        /* [cover parentID={9E7704FD-A609-4af2-965A-2EF6DF91F70A}]
         Enter SchM
        [/cover] */
        /* Enter SchM - Lock till Queue information is updated */
        SchM_Enter_Spi_Queue_Update();
        /* [cover parentID={357A8EAF-6785-4f18-803F-1CAB43E4F933}] Return E_NOT_OK
        if space is not available[/cover] */
        /* Check if Space is available in the Job Queue */
        RetVal = Spi_lIsSlotsAvailableInQueue(                                  \
             CoreConfigPtr->SequenceConfigPtr[SeqIndex].NoOfJobInSeq,
             HwModule);
        if(RetVal == (uint8)E_OK)
        {
          /* [cover parentID={9EBFF007-E03E-4f64-848F-4F1402C3A89C}]
           Check the status of the sequence to be transmitted is SPI_SEQ_PENDING
          [/cover] */
          /* Check if the sequence to be transmitted is PENDING */
          if(Spi_RuntimeCoreVar[CoreId]->SeqStatus[SeqIndex] ==
            SPI_SEQ_PENDING)
          {
            /* [cover parentID={D7E8E444-37FA-4441-B346-12E6873DD61F}]
            Return E_NOT_OK
            [/cover] */
            /* [cover parentID={F3A5BC7D-385D-4dba-A34C-5A4AAEC97A66}]
            Return E_NOT_OK
            /cover] */
            RetVal = E_NOT_OK;
          }
          else
          {
            /* [cover parentID={5683E7B6-3211-4e4c-ACD8-BB4399309C5E}][/cover] */
            /* Check if any of the jobs in sequence is in
              Queue to be transmitted */
            RetVal = Spi_lCheckJobIsNotShared(SeqIndex);
          }
          /* [cover parentID={C249F613-B493-4eb4-9747-0CEB23306D93}][/cover] */
          if(RetVal == (uint8)E_OK)
          {
            /* [cover parentID={23F5859D-149F-4590-8A80-0795E4F1D0AB}]
            Accepted to be transmitted, set the sequence status to be
            SPI_SEQ_PENDING
            [/cover] */
            /* [cover parentID={7791E038-1371-46c5-B165-FAB25123602B}]
             The status of the sequence to be transmitted is SPI_SEQ_PENDING
            [/cover] */
            /* Accepted to be transmitted, set Sequence status to pending */
            Spi_RuntimeCoreVar[CoreId]->SeqStatus[SeqIndex] = SPI_SEQ_PENDING;
              SeqJobLinkPtr =
               CoreConfigPtr->SequenceConfigPtr[SeqIndex].JobLinkPtrPhysical;
            /* Set the status of all the jobs belonging to the sequence to
            SPI_JOB_QUEUED */
            JobIndex = 0U;
            do
            {
              /* [cover parentID={F60B2913-0652-483d-B07A-95B754848BC8}]
               Set the status to SPI_JOB_QUEUED
              [/cover] */
              Spi_RuntimeCoreVar[CoreId]->JobStatus[SeqJobLinkPtr[JobIndex]] =
                SPI_JOB_QUEUED;
              JobIndex++;
            } while(SeqJobLinkPtr[JobIndex] != SPI_JOB_DELIMITER);
            /* [cover parentID={997FEA9D-A565-4a91-A115-5D60B44A4F49}]
             Insert Jobs into the sequence as per priority
            [/cover] */
            /* [cover parentID={992BDC09-D63C-4c19-8FE7-9D5444D28D11}]
             Next job with high priority
            [/cover] */
            /* insert Jobs into the sequence as per priority */
            Spi_lInsertSeqInQueue(SeqIndex);

            /* [cover parentID={0A618E6A-BA5B-44a8-92DE-A93EE67B52DE}]
             Update kernel bus state to SPI_BUSY and call operation
             Spi_lAsyncStartJob to start job transmission
            [/cover] */
            /* Update kernel bus status to BUSY, indicating transmission
              in progress */
            if(Spi_RuntimeKernelVar[HwModule]->KernelStatus == SPI_IDLE)
            {
              Spi_RuntimeKernelVar[HwModule]->AsyncComStatus = SPI_BUSY;
              /* Update the HW unit status to SPI_BUSY */
              Spi_RuntimeKernelVar[HwModule]->KernelStatus = SPI_BUSY;
              Spi_RuntimeKernelVar[HwModule]->JobQueuePtr->
              CurrentJobIndex = 0U;

              /* Get the first job ID and start transmission from Queue */
              JobIndex = CoreConfigPtr->
                         SequenceConfigPtr[SeqIndex].JobLinkPtrPhysical[0U];
              Spi_lAsyncStartJob(JobIndex);
            }
            /* Exit SchM - Unlock and exit, return E_OK */
            SchM_Exit_Spi_Queue_Update();
          }
          else
          {
            /* [cover parentID={0FAF292F-800D-4414-ABA7-1D502B1E6494}][/cover] */
            /* [cover parentID={B1E5D2FE-218E-4918-B479-36DD14664906}]
            Report error as SPI_E_SEQ_PENDING
           [/cover] */
           #if (((MCAL_AR_VERSION == MCAL_AR_422) && \
           ((SPI_DEV_ERROR_DETECT == STD_ON) || (SPI_SAFETY_ENABLE == STD_ON))) \
           ||((MCAL_AR_VERSION == MCAL_AR_440) && \
            (SPI_RUNTIME_ERROR_DETECT == STD_ON)))
           Spi_lReportRuntimeDetError(SPI_SID_ASYNCTRANSMIT, SPI_E_SEQ_PENDING);
           #endif
           /* Exit SchM - Unlock and exit, return E_OK */
           SchM_Exit_Spi_Queue_Update();
          }
        }
        else
        {
          #if ((SPI_DEV_ERROR_DETECT == STD_ON) || (SPI_SAFETY_ENABLE == STD_ON))
          /* [cover parentID={24A363E0-A2F6-4091-87B9-6BB52B9BA692}]
          SPI_E_QUEUE_FULL DET [/cover] */
          Spi_lReportError(SPI_SID_ASYNCTRANSMIT,
                   SPI_E_QUEUE_FULL);
          #endif
          /* Exit SchM - Unlock and exit */
          SchM_Exit_Spi_Queue_Update();
        }
      }
    }
  }
  /* [cover parentID={C83B8CE7-2FAC-4cf8-B425-EE507919086B}]
   Return status
  [/cover] */
  return RetVal;
} /* End of function Spi_AsyncTransmit */
#endif /* SPI_LEVEL_DELIVERED != 0U */

/*******************************************************************************
**                                                                            **
** Traceability     : [cover parentID={7715CA85-2C2C-47af-9CD1-8E3E5DA801DB}] **
** Syntax          : static uint8 Spi_lGetChannelDataWidth(                   **
**                    const Spi_ChannelConfigType* const ChnlConfigPtr)       **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : ChnlConfigPtr - Channel configuration                    **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Size of data configured in channel configuration         **
**                                                                            **
** Description     : Function returns the data width in bytes for which the   **
**                   HW has to be configured for, returns 1, 2 or 4 bytes.    **
*******************************************************************************/
static uint8 Spi_lGetChannelDataWidth(
    const Spi_ChannelConfigType* const ChnlConfigPtr)
{
  uint8 SizeofElement = 0;

  /* [cover parentID={63884B77-5C71-411e-A320-9F8053C47F13}]
   Data width to be transmitted on SPI bus
  [/cover] */
  /* [cover parentID={F6679606-E01B-42a3-A2A2-E8C2DCD31224}]
    Check if 32-bit data to be transmitted [/cover] */
  if(((ChnlConfigPtr->DataConfig) & (uint8)SPI_BIT_MASK_6_TO_0)        \
      > SPI_16BIT_DATAWIDTH)
  { /* Size is 4 Bytes */
    SizeofElement = 4U;
  }
   /* [cover parentID={2520FC44-193A-4b3f-9F72-4183D4F29EF9}]
    Check if 16-bit data to be transmitted [/cover] */
  else if(((ChnlConfigPtr->DataConfig) & (uint8)SPI_BIT_MASK_6_TO_0)   \
          > SPI_8BIT_DATAWIDTH)
  { /* Size is 2 Bytes */
    SizeofElement = 2U;
  }
  else
  /* [cover parentID={C06F312A-8D81-4118-B3FE-C4E4A3D81ECA}]
    Check if 8-bit data to be transmitted [/cover] */
  {
    /* Size is 1 Byte */
    SizeofElement = 1U;
  }

  /* Return Size */
  return SizeofElement;
}

#if(SPI_CHANNEL_BUFFERS_ALLOWED != 1U)
/*******************************************************************************
** Traceability     : [cover parentID={A7D8ABB9-C699-4875-8F58-3C9A3AFBB8F8}] **
**                                                                            **
** Syntax          : Std_ReturnType Spi_WriteIB                               **
**                   (                                                        **
**                     const Spi_ChannelType Channel,                         **
**                     const Spi_DataBufferType* const DataBufferPtr          **
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
Std_ReturnType Spi_WriteIB
(
  const Spi_ChannelType Channel,
  const Spi_DataBufferType* const DataBufferPtr
)
{
  const Spi_DataBufferType* SrcBuffPtr = NULL_PTR;
  const Spi_DataBufferType* DestBuffPtr = NULL_PTR;
  const Spi_ChannelConfigType* ChnlConfigPtr;
  Std_ReturnType RetVal = E_NOT_OK;
  uint8 incrementSource = 0;
  uint8 ChannelDataWidth;

  /* Get Core Information */
  const Spi_CoreConfigType *CoreConfigPtr;
  uint32 CoreId = Mcal_GetCpuIndex();
  uint8 ChannelId = 0;

  /* DET / SAFETY ON - Check if the Channel ID passed is valid */
  /* [cover parentID={629A4B34-53A9-4cc4-BFD7-136928153944}]
   SPI_DEV_ERROR_DETECT or SPI_SAFETY_ENABLE is ON
  [/cover] */
  #if ((SPI_DEV_ERROR_DETECT == STD_ON) ||                                  \
  (SPI_SAFETY_ENABLE == STD_ON))
  /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of variable ChannelId
    is used inside Spi_lCheckChannelParam() only to read values.
    The address is not stored for later usage in Spi_lCheckChannelParam().
    Hence it is safe to pass the address of the local variable. */
  /* [cover parentID={63B348DB-4B7A-40d4-A31B-51B8D662E7A3}]
   Check the Channel ID passed is valid
  [/cover] */
  RetVal = Spi_lCheckChannelParam(SPI_SID_WRITEIB, &ChannelId,
                                  Channel, SPI_IB_CHANNEL);
  /* [cover parentID={3C661BFF-1768-4488-989A-9F4F845DF7FA}]
   Channel is valid
  [/cover] */
  if(RetVal == E_OK)
  #else
  /* If DET / SAFETY is OFF - Get the Channel ID from look-up
      table directly */
  /* [cover parentID={602B71AE-23BF-4912-965D-99DDD1BB69D0}][/cover] */
  ChannelId = Spi_kGlobalConfigPtr->ChannelLookup[Channel];
  #endif
  {
    CoreConfigPtr = Spi_kGlobalConfigPtr->CoreConfigPtr[CoreId];
    DestBuffPtr = Spi_RuntimeCoreVar[CoreId]-> \
                  ChannelBufPointers[ChannelId].SrcPtr;

    ChnlConfigPtr = &CoreConfigPtr->ChannelConfigPtr[ChannelId];

    /* [cover parentID={7D41DECC-2F8D-4621-9D03-482B75F0DBD6}] Check for
    valid buffer from application[/cover] */
    /* Check for valid buffer from application */
    if(DataBufferPtr != NULL_PTR)
    {
      /* Valid buffer - Use buffer as is, increment source buffer after
          each data element copy */
      incrementSource = 1;

      /* [cover parentID={8F8DB71F-5A26-4be3-9823-A2E01CB4BEBB}]
      Use buffer passed if not NULL
      [/cover] */
      SrcBuffPtr = DataBufferPtr;
    }
    /* [cover parentID={089CA124-DE1E-4c3b-B7FD-AC99B3DDB216}]
     Pointer to buffer is null
    [/cover] */
    else
    {
      /*  Use default data (max 32-bit), do not increment while
      copying data */
      incrementSource = 0;
      /* MISRA2012_RULE_11_8_JUSTIFICATION: The SrcBuffPtr is updated
         only when the user wants to transmit default data.
         Thus the const qualifier is not valid in this particular scenario. */
      SrcBuffPtr = (Spi_DataBufferType*)&ChnlConfigPtr->Defaultdata;
    }

    /* Get the channel Datawidth configured */
    ChannelDataWidth = Spi_lGetChannelDataWidth(ChnlConfigPtr);

    /* MISRA2012_RULE_11_8_JUSTIFICATION: The SrcBuffPtr and DestBuffPtr
       is of type 'const Spi_DataBufferType*' which is
       nothing but 'const uint8*'  */
    Spi_lIBCopyData((const uint8*)SrcBuffPtr, (uint8*)DestBuffPtr,
          ((uint32)ChnlConfigPtr->NoOfDataElements * (uint32)ChannelDataWidth),
    ((uint8)(ChannelDataWidth << SPI_DATAWIDTH_BITS_OFFSET) | incrementSource));

    /* [cover parentID={9703E25D-948C-4eba-BC64-F608C294EA51}]
     Set return value as E_OK
    [/cover] */
    RetVal = E_OK;
  }
  /* [cover parentID={B2C8080F-FB5E-4d11-AE57-019C2EB85A7D}]
   Return status
  [/cover] */
  return RetVal;
} /* End of function Spi_WriteIB */
#endif /* SPI_CHANNEL_BUFFERS_ALLOWED != 1U */

#if(SPI_CHANNEL_BUFFERS_ALLOWED != 1U)
/*******************************************************************************
** Traceability     : [cover parentID={890CF5BB-2DE2-41ef-B421-286B6DC41BD1}] **
**                                                                            **
** Syntax          : Std_ReturnType Spi_ReadIB                                **
**                   (                                                        **
**                     const Spi_ChannelType Channel,                         **
**                     Spi_DataBufferType* const DataBufferPointer            **
**                   )                                                        **
**                                                                            **
** Service ID      : 0x04                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : Channel - Specifies the channel ID                       **
**                                                                            **
** Parameters (out): DataBufferPointer - This is pointer to the destination   **
**                   buffer to where the received data is copied.             **
**                   If this pointer is NULL then Dets is raised              **
**                                                                            **
** Return value    : E_OK: Data from Internal buffer to the destination       **
**                         buffer is copied successfully                      **
**                   E_NOT_OK: Data was not copied from internal buffer       **
**                             to the destination buffer                      **
**                                                                            **
** Description     : This API copies the received channel data from           **
**                   Internal buffer to the destination buffer. DET is raised **
**                   if NULL address is given as destination address.         **
*******************************************************************************/
Std_ReturnType Spi_ReadIB
(
  const Spi_ChannelType Channel,
  Spi_DataBufferType* const DataBufferPointer
)
{
  const Spi_DataBufferType* SrcInternalBuffPtr;
  const Spi_ChannelConfigType* ChnlConfigPtr;
  const Spi_CoreConfigType *CoreConfigPtr;
  uint8 ChannelId = 0;
  uint8 ChannelDataWidth;
  /* [cover parentID={C82FC100-05D4-4cc3-86D4-79E4601B2618}][/cover] */
  Std_ReturnType RetVal = E_OK;

  /* Get Core Information */
  uint32 CoreId = Mcal_GetCpuIndex();

  /* [cover parentID={73038AB6-3BE8-44df-9503-D568FF8E1C8E}]
   SPI_DEV_ERROR_DETECT or SPI_SAFETY_ENABLE is ON
  [/cover] */
  #if ((SPI_DEV_ERROR_DETECT == STD_ON) || (SPI_SAFETY_ENABLE == STD_ON))
  /* DET / SAFETY ON - Check if the Channel ID passed is valid */
  /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of variable ChannelId
    is used inside Spi_lCheckChannelParam() only to read values.
    The address is not stored for later usage in Spi_lCheckChannelParam().
    Hence it is safe to pass the address of the local variable. */
  /* [cover parentID={64EA5437-051F-4a67-8FC3-0019A96DF890}]
   Check the Channel ID passed is valid
  [/cover] */
  RetVal = Spi_lCheckChannelParam(SPI_SID_READIB, &ChannelId,
                                  Channel, SPI_IB_CHANNEL);

  /* [cover parentID={6574970D-C101-474e-A8E7-30202CC5D723}]
    Check for Valid buffer to copy data [/cover] */
  if((RetVal == (uint8)E_OK) && (DataBufferPointer == NULL_PTR))
  {
    /* [cover parentID={AEFA5DDE-CCE0-4235-BE90-1C3A9C717F6F}]
    DET reporting[/cover] */
    /* [cover parentID={813EE116-87D6-4926-9511-B38343238844}]
    DET SPI_E_PARAM_POINTER[/cover] */
    Spi_lReportError(SPI_SID_READIB,
                     SPI_E_PARAM_POINTER);
    RetVal = E_NOT_OK;
  }
  /* [cover parentID={C6519D90-62BE-4204-A237-7A402C4DABDD}]
   Channel is valid
  [/cover] */
  if(RetVal == (uint8)E_OK)
  #else
  /* [cover parentID={8EA8FC11-B317-49b2-8C39-10376FA26583}][/cover] */
  /* If DET / SAFETY is OFF - Get the Channel ID from look-up table directly */
  ChannelId = Spi_kGlobalConfigPtr->ChannelLookup[Channel];
  #endif
  {
    CoreConfigPtr = Spi_kGlobalConfigPtr->CoreConfigPtr[CoreId];
    ChnlConfigPtr = &CoreConfigPtr->ChannelConfigPtr[ChannelId];

    /* [cover parentID={474223B5-EBBB-42ba-A27C-58F27C1890E5}]
     Copy received data from IB buffer to buffer passed by application
    [/cover] */
    SrcInternalBuffPtr = Spi_RuntimeCoreVar[CoreId]->
                           ChannelBufPointers[ChannelId].DestPtr;

    /*Get the channel data width */
    ChannelDataWidth = Spi_lGetChannelDataWidth(ChnlConfigPtr);

    Spi_lIBCopyData((const uint8*)SrcInternalBuffPtr,    \
                      (uint8*)DataBufferPointer, \
       ((uint32)ChnlConfigPtr->NoOfDataElements * (uint32)ChannelDataWidth), \
                 ((uint8)(ChannelDataWidth << SPI_DATAWIDTH_BITS_OFFSET) | 1U));
  }
  /* [cover parentID={B37768B1-0A34-4458-BEAB-4F78C3ACD81B}]
   Return error status
  [/cover] */
  return RetVal;
} /* End of function Spi_ReadIB */
#endif /* SPI_CHANNEL_BUFFERS_ALLOWED != 1U */

#if(SPI_CHANNEL_BUFFERS_ALLOWED != 0U)
/*******************************************************************************
** Traceability     : [cover parentID={545AF68B-5CD0-4e4b-A87F-29D8A6D8FE73}] **
**                                                                            **
** Syntax          : Std_ReturnType Spi_SetupEB                               **
**                  (                                                         **
**                      const Spi_ChannelType Channel,                        **
**                      const Spi_DataBufferType* const SrcDataBufferPtr,     **
**                      const Spi_DataBufferType* const DesDataBufferPtr,     **
**                      const Spi_NumberOfDataType Length                     **
**                  )                                                         **
**                                                                            **
** Service ID      : 0x05                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant for different channels                         **
**                                                                            **
** Parameters (in) : Channel - Channel ID of the respective EB channel        **
**                   SrcDataBufferPtr - This is the pointer to source buffer  **
**                                               for the EB channel           **
**                   DesDataBufferPtr - This is the pointer to destination    **
**                               buffer to where the received data is copied  **
**                   Length - Number of data elements to be transmitted.      **
**                            i.e.,                                           **
**                            for 8-bit channel, if length is 2, then         **
**                            2 * 8-bit = 16 bits will be transferred,        **
**                            for 16-bit channel, if length is 2, then        **
**                            2 * 16-bit = 32 bits will be transferred and    **
**                            for 32-bit channel, if length is 2, then        **
**                            2 * 32-bit = 64 bits will be transferred        **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK - Buffers has been setup for the EB channel         **
**                   E_NOT_OK - Buffer setup for the channel has not          **
**                                                     been accepted          **
**                                                                            **
** Description     : This API initializes the buffers and transfer length     **
**                   for the EB channels. No DET is raised for NULL address   **
**                      if given to either source or destination buffers.     **
**        i.e., If Source address is NULL, then transfer default configured   **
**              If Destination address is NULL, then ignore the received data **
*******************************************************************************/
Std_ReturnType Spi_SetupEB
(
    const Spi_ChannelType Channel,
    const Spi_DataBufferType* const SrcDataBufferPtr,
    const Spi_DataBufferType* const DesDataBufferPtr,
    const Spi_NumberOfDataType Length
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  /* Get Core Information */
  uint32 CoreId = Mcal_GetCpuIndex();
  uint8 ChannelId = 0;
  /* [cover parentID={5D5DBCDB-C27F-4b1c-9072-A4B4FD34E413}]
  SPI_DEV_ERROR_DETECT or SPI_SAFETY_ENABLE is ON
  [/cover] */
  #if ((SPI_DEV_ERROR_DETECT == STD_ON) || (SPI_SAFETY_ENABLE == STD_ON))
  const Spi_CoreConfigType *CoreConfigPtr;
  /* DET / SAFETY ON - Check if valid channel and length is received */
  Spi_NumberOfDataType MaxLength = 0U;
  /* [cover parentID={118A1C97-69C8-41ef-A696-D3C667909660}]
   Check if valid channel
  [/cover] */
  /* [cover parentID={23DA3682-D8C2-481d-89A3-2644B9DC983B}][/cover] */
  /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of variable ChannelId
    is used inside Spi_lCheckChannelParam() only to read values.
    The address is not stored for later usage in Spi_lCheckChannelParam().
    Hence it is safe to pass the address of the local variable. */
  RetVal = Spi_lCheckChannelParam(SPI_SID_SETUPEB, &ChannelId,
                                  Channel, SPI_EB_CHANNEL);

  if(RetVal == (uint8)E_OK)
  {
    CoreConfigPtr = Spi_kGlobalConfigPtr->CoreConfigPtr[CoreId];

    MaxLength =
      CoreConfigPtr->ChannelConfigPtr[ChannelId].NoOfDataElements;
    /* [cover parentID={AE9787B0-81A7-4d2c-A231-B29ACAF0B97D}]
     Check if valid length is received
    [/cover] */
    /* [cover parentID={D3E8BD17-8089-4779-ADAC-8DD1917003E2}]
     Length is greater than maximum length
    [/cover] */
    if(((Length > MaxLength) ||
        (Length == (Spi_NumberOfDataType)0U)))
    {
      /* [cover parentID={8D34308F-9101-4fac-9413-2A71F8AF2841}]
       Report error as SPI_E_PARAM_LENGTH
      [/cover] */
      Spi_lReportError(SPI_SID_SETUPEB,
                       SPI_E_PARAM_LENGTH);
      /* [cover parentID={8F415694-7F84-42bd-A61D-EA19437EC4BA}]
       Set return value E_NOT_OK
      [/cover] */
      RetVal = E_NOT_OK;
    }
  }

  if(RetVal == E_OK)
  #else
    /* [cover parentID={8614C92E-BC7F-4f1a-9BFD-DB183C05FB5F}][/cover] */
  /* If DET / SAFETY is OFF - Get the channel ID from look-up table */
  ChannelId = Spi_kGlobalConfigPtr->ChannelLookup[Channel];
  #endif
  {
    /* Copy Source, Destination and Length for EB channel */
    Spi_RuntimeCoreVar[CoreId]->
    ChannelBufPointers[ChannelId].SrcPtr  = SrcDataBufferPtr;
    Spi_RuntimeCoreVar[CoreId]->
    ChannelBufPointers[ChannelId].DestPtr = DesDataBufferPtr;
    Spi_RuntimeCoreVar[CoreId]->
    ChannelBufPointers[ChannelId].TransferLength = Length;

    /* [cover parentID={949FF942-C8FF-4a34-90F1-2F87D19D196E}]
     Return value is E_OK
    [/cover] */
    RetVal = E_OK;
  }
  /* [cover parentID={38BF8DA5-74EE-431c-9B4E-546E757DF5FD}]
   Return status
  [/cover] */
  return RetVal;
}
/* End of function Spi_SetupEB */
#endif /* SPI_CHANNEL_BUFFERS_ALLOWED != 0U */

/*******************************************************************************
** Traceability     : [cover parentID={76BC5DED-5216-453f-A482-F8B3D30EF4DB}] **
**                                                                            **
** Syntax          : Spi_JobResultType Spi_GetJobResult(const                 **
**                       Spi_JobType Job)                                     **
**                                                                            **
** Service ID      : 0x07                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : Job - Job ID                                             **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Spi_JobResultType - status of the job                    **
**                   returns SPI_JOB_FAILED for any errors                    **
**                                                                            **
** Description     : This service returns the last transmission result of the **
**                   specified Job. API returns the status of the job         **
**                   depending on whether job is queued, failed, pending or   **
**                   successful.                                              **
**                   In multicore context, API can only return the status of  **
**                   the jobs that are assigned to core in which API is called**
*******************************************************************************/
Spi_JobResultType Spi_GetJobResult(const Spi_JobType Job)
{
  Spi_JobResultType JobResult = SPI_JOB_FAILED;

  /* Get Core configuration */
  uint32 CoreId = Mcal_GetCpuIndex();

  /* [cover parentID={72CA83A9-749B-4fd0-B17C-2C356234C6A2}]
   SPI_DEV_ERROR_DETECT or SPI_SAFETY_ENABLE is ON
  [/cover] */
  #if ((SPI_DEV_ERROR_DETECT == STD_ON) || (SPI_SAFETY_ENABLE == STD_ON))

  #if (SPI_MULTICORE_ERROR_DETECT == STD_ON)|| (SPI_SAFETY_ENABLE == STD_ON)
  uint16 lJobId;
  const Spi_CoreConfigType *CoreConfigPtr;
  #endif
  Std_ReturnType ErrStatus = E_NOT_OK;

  /* [cover parentID={3115E937-7C8B-4e46-BBDB-A3CD09F87CA1}]
   Check if driver is initialized
  [/cover] */
  ErrStatus = Spi_lCheckInitStatus(SPI_SID_GETJOBRESULT, (uint8)SPI_REPORT_DET);
  if(ErrStatus == (uint8)E_OK)
  {
    /* [cover parentID={4F90B49E-D433-43db-959B-4DFF5A823AF6}][/cover] */
    /* [cover parentID={E0FF30D9-5C1D-4ca3-B14F-1A4AD8250D8F}]
     Job ID is valid
    [/cover] */
    if(Job < Spi_kGlobalConfigPtr->NoOfJobs)
    {
      #if (SPI_MULTICORE_ERROR_DETECT == STD_ON)|| (SPI_SAFETY_ENABLE == STD_ON)
      /* Fetch the physical job ID from look-up table */
      lJobId = Spi_kGlobalConfigPtr->JobLookup[Job];
      CoreConfigPtr = Spi_kGlobalConfigPtr->CoreConfigPtr[CoreId];

      /* Check if the physical job-id is in core specific job
          configuration */
      if((lJobId >= CoreConfigPtr->NoOfJobs) ||
          (CoreConfigPtr->JobConfigPtr[lJobId].JobId != Job))
      {
        /* Report DET as job not configured to this core */
        /* [cover parentID={48E19A23-6C33-4c39-8EEE-686A8B9A164E}][/cover] */
        Spi_lReportMulticoreError(SPI_SID_GETJOBRESULT,
                                  SPI_E_NOT_CONFIGURED);
        ErrStatus = E_NOT_OK;
      }
      #endif
    }
    else
    {
      /* Raise DET as Invalid Job ID */
      /* [cover parentID={16BA6955-E163-4c23-8F50-31593AD00BB4}]
       Report error as invalid Job ID SPI_E_PARAM_JOB
      [/cover] */
      Spi_lReportError(SPI_SID_GETJOBRESULT, SPI_E_PARAM_JOB);

      ErrStatus = E_NOT_OK;
    }
  }
  if(ErrStatus == (uint8)E_OK)
  #endif /* SPI_DEV_ERROR_DETECT == STD_ON */
  {
    JobResult =
      Spi_RuntimeCoreVar[CoreId]->JobStatus\
      [Spi_kGlobalConfigPtr->JobLookup[Job]];
  }
  /* [cover parentID={359D181D-9D16-43b1-9847-E003A1212D8E}]
   Return job result
  [/cover] */
  /* [cover parentID={B5126528-A292-444c-9FDA-7E3C5CACB453}]
   Return job result - SPI_JOB_FAILED if driver is not initialized
  [/cover] */
  return JobResult;
} /* End of function Spi_GetJobResult */

/*******************************************************************************
** Traceability     : [cover parentID={B100A302-6050-43b1-BAB6-53F194D30679}] **
**                                                                            **
** Syntax          : Spi_SeqResultType Spi_GetSequenceResult                  **
**                   (const Spi_SequenceType Sequence)                        **
**                                                                            **
** Service ID      : 0x08                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : Sequence - Sequence Id for which the status              **
**                   to be returned                                           **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Spi_SeqResultType - status of the Sequence               **
**                   returns SPI_SEQ_FAILED for any errors                    **
**                                                                            **
** Description     : This API returns the status of the Seq depending on      **
**                   whether Seq is cancelled, failed, pending or successful  **
*******************************************************************************/
Spi_SeqResultType Spi_GetSequenceResult(const Spi_SequenceType Sequence)
{
  Spi_SeqResultType SeqResult = SPI_SEQ_FAILED;
  /* [cover parentID={4DBB80B7-9C44-48a6-B26A-B33DD7D7F811}]
   Get core information
  [/cover] */
  uint32 CoreId = Mcal_GetCpuIndex();
  uint8 SeqIndex = 0;

  /* [cover parentID={0C2A1D20-D659-4b19-9AB9-113E55F79BF7}]
   SPI_DEV_ERROR_DETECT or SPI_SAFETY_ENABLE is ON
  [/cover] */
  #if ((SPI_DEV_ERROR_DETECT == STD_ON) || (SPI_SAFETY_ENABLE == STD_ON))
  /* DET / SAFETY ON - Check if valid Sequence ID is received */
  /* [cover parentID={3C0ABB21-8E00-45ea-8185-F2DA61A18447}]
   Check if valid Sequence ID is received
  [/cover] */
  /* [cover parentID={C385059A-BF65-4f5f-98CC-BBA15BF60A54}]
   Check API parameter - DET ON
  [/cover] */
  Std_ReturnType RetVal = E_NOT_OK;
  /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of variable SeqIndex
    is used inside Spi_lCheckSeqParam() only to read values.
    The address is not stored for later usage in Spi_lCheckSeqParam().
    Hence it is safe to pass the address of the local variable. */
  RetVal = Spi_lCheckSeqParam(SPI_SID_GETSEQUENCERESULT, &SeqIndex,
                              Sequence, (uint8)SPI_IGNORE_COMMS_TYPE_CHECK);
  /* [cover parentID={77312CC0-FC2C-498b-BA9C-7D650414459D}]
    Report error as received sequence is not valid SPI_E_PARAM_SEQ
  [/cover] */
  if(RetVal == E_OK)
  #else
    /* [cover parentID={A32278F2-8D74-46eb-B6AC-2BE181690A42}][/cover] */
  /* DET / SAFETY ON - Get the physical seq-id from look-up table */
  SeqIndex = Spi_kGlobalConfigPtr->SequenceLookup[Sequence];
  #endif
  {
    /* [cover parentID={159FA59F-37D7-4ebc-B435-08E003897A82}]
     Fetch the status of sequence and return
    [/cover] */
    SeqResult = Spi_RuntimeCoreVar[CoreId]->SeqStatus[SeqIndex];
  }
  return SeqResult;
} /* End of function Spi_GetSequenceResult */

/*******************************************************************************
** Traceability     : [cover parentID={B5495E1C-9496-4abd-B5FE-3887D6B0A6BE}] **
**                                                                            **
** Syntax          : Spi_StatusType Spi_GetStatus(void)                       **
**                                                                            **
** Service ID      : 0x06                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
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
** Description     : This API returns the status of the driver as whole       **
**                   including synchronous and asynchronous transmissions     **
**                   (if configured). After reset and before Spi_Init() API   **
**                   is invoked, the status of the driver will be SPI_UNINIT  **
*******************************************************************************/
Spi_StatusType Spi_GetStatus(void)
{
  Spi_StatusType RetVal = SPI_UNINIT;
  SpiCommsTypes temp = SPI_BOTH;

  /* [cover parentID={61C0CFB7-08AA-49c3-8DB8-7E191A17D5ED}]
  DET error [/cover] */
  #if ((SPI_DEV_ERROR_DETECT == STD_ON) || (SPI_SAFETY_ENABLE == STD_ON))
  /* Check if Driver is initialized */
  /* [cover parentID={A4D35E82-0F76-4e0a-B86E-465256E8C9E8}][/cover] */
  /* [cover parentID={E6286888-D516-43fb-A5DF-EF10DFAC7FDC}][/cover]
  un-initialized DET */
  if(Spi_lCheckInitStatus(SPI_SID_GETSTATUS, (uint8)SPI_REPORT_DET) == \
      (uint8)E_OK)
  #else
  if(Spi_lCheckInitStatus(SPI_SID_GETSTATUS, (uint8)SPI_DET_DISABLE) == \
      (uint8)E_OK)
  #endif
  {
    /* [cover parentID={D309F277-71BA-4d7c-BA96-FDFA6F187221}]
     Check if driver is busy or idle
    [/cover] */
    if(Spi_lIsStatusBusy(temp) == E_OK)
    {
      /* [cover parentID={157CF446-7014-406e-AA77-167EDB3BCE8B}]
       Transmitting data - Return SPI_BUSY
      [/cover] */
      /* [cover parentID={4F473541-9FA8-4713-93D7-A8081BE43BF2}]
       Set status as busy
      [/cover] */
      RetVal = SPI_BUSY;
    }
    else
    {
      /* [cover parentID={D80410E5-794E-4ed2-9286-F3685168E0D1}]
       Return SPI_IDLE if not transmitting
      [/cover] */
      /* [cover parentID={DD294243-2D48-40b1-A0CE-F30FF09791BC}]
       Set status as idle
      [/cover] */
      RetVal = SPI_IDLE;
    }
  }
  /* [cover parentID={31AEF37F-D562-447a-9083-7352A6A879A5}]
   Return status
  [/cover] */
  return RetVal;
} /* End of function Spi_GetStatus */

/*******************************************************************************
** Traceability     : [cover parentID={D7707344-4356-4546-8CCE-189ECF713C0F}] **
**                                                                            **
** Syntax          : Spi_StatusType Spi_GetHWUnitStatus                       **
**                   (const Spi_HWUnitType HWUnit)                            **
**                                                                            **
** Service ID      : 0x0B                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : HWUnit - QSPI Hw Unit                                    **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : SPI_UNINIT - The QSPI Hardware is not initialized        **
**                   or not usable                                            **
**                   SPI_IDLE - The QSPI Hardware is not currently            **
**                   transmitting any Job                                     **
**                   SPI_BUSY - The QSPI Hardware is performing a SPI         **
**                   Job(transmit)                                            **
**                                                                            **
** Description     : This API returns the status of the QSPI Hw which is      **
**                   either synchronous or asynchronous transmissions         **
**                   (if configured). After reset and before Spi_Init() API   **
**                   is invoked, the status of the QSPI Hw will be SPI_UNINIT **
*******************************************************************************/
#if (SPI_HW_STATUS_API == STD_ON)
Spi_StatusType Spi_GetHWUnitStatus(const Spi_HWUnitType HWUnit)
{
  Spi_StatusType RetVal = SPI_UNINIT;
  /* [cover parentID={38E88102-0BC3-4c66-A4B5-CDBC764FA3DB}] [/cover] */
  #if ((SPI_DEV_ERROR_DETECT == STD_ON) || (SPI_SAFETY_ENABLE == STD_ON))
  /* [cover parentID={6B0C8A4A-0A17-4ee7-A0B6-D84E9D35B60A}]
   Check if Driver is initialized
  [/cover] */
  if(Spi_lCheckInitStatus(SPI_SID_GETHWUNITSTATUS, (uint8)SPI_REPORT_DET) == \
      (uint8)E_OK)
  #endif
  {
    /* [cover parentID={9E8D1C68-A57B-40f8-9A86-CEDB64C9096B}]
     Check if the QSPI IP instance is in range and if assigned for a core
    [/cover] */
    /* [cover parentID={23BE0A7A-7CFF-4177-9551-C836B1093FCF}] [/cover] */
    if(HWUnit < (uint8)SPI_MAX_HW_UNIT)
    {
      if(Spi_lIsQSPIHwConfigured(HWUnit) == (uint8)E_OK)
      {
        /* Check if device is Idle, PHASE = 0 is wait state */
        /* [cover parentID={A021E0BB-9022-44e8-8D99-3FB8886CB761}]
         Check if device is Idle
        [/cover] */
        if(Spi_RuntimeKernelVar[HWUnit]->KernelStatus == SPI_IDLE)
        {
          RetVal = SPI_IDLE;
        }
        else
        {
          RetVal = SPI_BUSY;
        }
      }
      else
      {
        /* DET - Invalid parameter */
        /* [cover parentID={78BC8DD4-D078-4680-B356-88D42D9C4CCF}]
        SPI_DEV_ERROR_DETECT or SPI_SAFETY_ENABLE is ON
        [/cover] */
        #if ((SPI_DEV_ERROR_DETECT == STD_ON) || (SPI_SAFETY_ENABLE == STD_ON))
        /* [cover parentID={2DE57FA2-3317-484c-B371-B6A52F218426}]
         Report error as invalid parameter SPI_E_PARAM_UNIT
        [/cover] */
        Spi_lReportError(SPI_SID_GETHWUNITSTATUS,
                         SPI_E_PARAM_UNIT);
        #endif

      }
    }
    else
    {
      /* DET - Invalid parameter */
      #if ((SPI_DEV_ERROR_DETECT == STD_ON) || (SPI_SAFETY_ENABLE == STD_ON))
      Spi_lReportError(SPI_SID_GETHWUNITSTATUS,
                       SPI_E_PARAM_UNIT);
      #endif
      /* MISRA2012_RULE_15_7_JUSTIFICATION: The DET or safety error is
         reported only when the precompile options are enabled. */
    }
  }
  /* [cover parentID={FE8A6019-8B2F-4f50-940D-D19721ED06B9}]
   Return status
  [/cover] */
  return RetVal;
} /* End of function Spi_GetHWUnitStatus */
#endif

#if(SPI_LEVEL_DELIVERED == 2U)
/*******************************************************************************
** Traceability     : [cover parentID={C59E28B2-0CAA-4096-B7BE-56C323E58C1B}] **
**                                                                            **
** Syntax          : Std_ReturnType Spi_SetAsyncMode                          **
**                   (                                                        **
**                     const Spi_AsyncModeType Mode                           **
**                   )                                                        **
**                                                                            **
** Service ID      : 0x0D                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in) : Mode - Asynchronous mode (Interrupt/Polling)             **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK - Asynchronous mode was updated successfully        **
**                   E_NOT_OK - Asynchronous mode was not changed             **
**                                                                            **
** Description     : This API sets the asynchronous mode of handling          **
**                   transmission of sequences to either Polling mode or      **
**                   Interrupt mode. Available only in Level 2 Mode cannot    **
**                   be changed when the driver is busy in transmission of    **
**                   the asynchronous sequence; however mode can be changed   **
**                   if driver is busy with only synchronous transmission.    **
**                                                                            **
*******************************************************************************/
Std_ReturnType Spi_SetAsyncMode(const Spi_AsyncModeType Mode)
{
  Std_ReturnType RetVal = E_OK;
  uint32 CoreId = Mcal_GetCpuIndex();

  /* [cover parentID={B8B638EA-F404-493f-8BAE-5B9B828D0A14}]
   SPI_DEV_ERROR_DETECT or SPI_SAFETY_ENABLE is ON
  [/cover] */
  /* [cover parentID={32C2F6B2-6734-4ab4-B0D3-A9F86CC4A809}]
  DET / SAFETY Enabled
  [/cover] */
  #if ((SPI_DEV_ERROR_DETECT == STD_ON) || (SPI_SAFETY_ENABLE == STD_ON))
  /* [cover parentID={DACBB041-7BAF-4e05-81D1-D9F5744437D2}]
   Check if Driver is initialzed
  [/cover] */
  RetVal = Spi_lCheckInitStatus(SPI_SID_SETASYNCMODE, (uint8)SPI_REPORT_DET);
  /* [cover parentID={8ED292E2-ADC3-4ab2-858D-A7EB97372607}]
   Driver is initialized
  [/cover] */

  if(RetVal == (uint8)E_OK)
  {
  #endif
  #if (SPI_SAFETY_ENABLE == STD_ON)
    /* [cover parentID={E0A20CF5-B76D-4728-ADE1-71A31FD0869C}]
     Check if parameter is valid
    [/cover] */
    /* [cover parentID={FFBC5162-0A45-47e4-8194-C8278CB28AA8}]
     Check if parameter is valid
    [/cover] */
    if((Mode != SPI_POLLING_MODE) && (Mode != SPI_INTERRUPT_MODE))
    {
      /* Raise Safety error as invalid parameter */
      Mcal_ReportSafetyError(
                    SPI_MODULE_ID,
                    SPI_INSTANCE_ID,
                    SPI_SID_SETASYNCMODE,
                    SPI_E_SAFETY_INVALID_PARAM);/* End of report to Safety */

      RetVal = E_NOT_OK;
    }
 #endif
 #if ((SPI_DEV_ERROR_DETECT == STD_ON) || (SPI_SAFETY_ENABLE == STD_ON))
  }
  if(RetVal == (uint8)E_OK)
  #endif
  {

    /* [cover parentID={C9F22F24-2450-4638-BFA5-F90B24D94AE2}]
     Check if all the QSPI IP is IDLE
    [/cover] */
    /* [cover parentID={65E6B367-8CD7-4044-B0B2-4827E903A8EF}]
     All QSPI is idle
    [/cover] */
    if(Spi_lIsStatusBusy(SPI_ASYNC_COMMS) == (uint8)E_NOT_OK)
    {
      /* [cover parentID={02FBA700-BD38-4171-8499-E5BA00D735F7}]
      Will update mode per core
      [/cover] */
      /* Set Aync comms mode to polling or interrupt */
      Spi_RuntimeCoreVar[CoreId]->AsyncMode = Mode;

      /* Update status to E_OK */
      /* [cover parentID={AE49F715-DABE-4277-88E0-AEB35798A159}]
       Return E_OK
      [/cover] */
      RetVal = E_OK;
    }
    else
    {
      /* Update status to E_NOT_OK */
      /* [cover parentID={E7FC929B-D6CC-447d-89F0-05477BEE4F9F}]
        Return E_NOT_OK
      [/cover] */
      RetVal = E_NOT_OK;
    }
  }
  return RetVal;
} /* End of function Spi_SetAsyncMode */
#endif /* SPI_LEVEL_DELIVERED == 2U */
#if (SPI_CONTROL_LOOPBACK_API == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={80E05435-4977-4761-97C1-337856427A89}] **
**                                                                            **
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
Std_ReturnType Spi_ControlLoopBack(const Spi_HWUnitType HWUnit,
                                         const Spi_LoopBackType EnableOrDisable)
{
  Std_ReturnType RetVal = E_NOT_OK;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: register type Definition */
  Ifx_QSPI_GLOBALCON GlobalConReg;
  /* [cover parentID={A239F96D-D2C7-4c6d-BBD0-673AC644BB77}][/cover] */
  #if ((SPI_DEV_ERROR_DETECT == STD_ON) || (SPI_SAFETY_ENABLE == STD_ON))
  /* [cover parentID={29388982-E250-44d4-8F5D-3743291D6077}][/cover] */
  if(Spi_lCheckInitStatus(SPI_SID_CONTROLLOOPBACK, (uint8)SPI_REPORT_DET) == \
              (uint8)E_OK)
  #endif
  {
    /*[cover parentID={7D505ACA-632F-42d6-B05F-5998BF84FB24}]
    is parameter EnableOrDisable is valid
    [/cover] */
    if ((EnableOrDisable == SPI_LOOPBACK_ENABLE) || \
                            (EnableOrDisable == SPI_LOOPBACK_DISABLE))
    {
      /* [cover parentID={913199B3-F1F7-490a-A9CE-7330E8EF758D}]
      Is QSPI Hw number is valid [/cover] */
      if(HWUnit < (uint8)SPI_MAX_HW_UNIT)
      {
        /* [cover parentID={E3D966CF-07D7-44da-ADA4-2EDB45CC67E4}]
        is QSPI HW configured
        [/cover] */
        if(Spi_lIsQSPIHwConfigured(HWUnit) == (uint8)E_OK)
        {
          /* [cover parentID={D840BBAC-8F1E-425e-9E0F-22A9990B9251}]
          Is QSPI Hw is IDLE
          [/cover] */
          if(Spi_RuntimeKernelVar[HWUnit]->KernelStatus == SPI_IDLE)
          {
            /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access.
             No side effects foreseen by violating this MISRA rule,
             as the pointer to the object type that it is getting
             cast into, is a known type. */
            /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
             * effects foreseen by violating this MISRA rule. */
            GlobalConReg.U = SPI_HW_MODULE[HWUnit].GLOBALCON.U;
            if (EnableOrDisable == SPI_LOOPBACK_ENABLE)
            {
              GlobalConReg.U = (GlobalConReg.U | \
                          (1UL << (uint32)IFX_QSPI_GLOBALCON_LB_OFF));
            }
            else
            {
              GlobalConReg.U = (GlobalConReg.U & \
                          ~(1UL << (uint32)IFX_QSPI_GLOBALCON_LB_OFF));
            }
            /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access.
            No side effects foreseen by violating this MISRA rule, as the
            pointer to the object type that it is getting cast into,
            is a known type. */
            /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access.
            No side effects foreseen by violating this MISRA rule. */
            SPI_SFR_RUN_TIME_WRITE32(&SPI_HW_MODULE[HWUnit]. \
                            GLOBALCON.U, GlobalConReg.U);
            RetVal = E_OK;
          }
        }
      }
      else
      {
        /* [cover parentID={E7A7E9DA-A12E-4717-8374-FE9EB81208BD}] [/cover] */
        #if ((SPI_DEV_ERROR_DETECT == STD_ON) || (SPI_SAFETY_ENABLE == STD_ON))
        /* [cover parentID={136AAD78-175D-4258-B0D9-C881526230F9}]
        Report SPI_E_PARAM_UNIT
        [/cover] */
        Spi_lReportError(SPI_SID_CONTROLLOOPBACK,
                         SPI_E_PARAM_UNIT);
        #endif

      }
    }
    else
    {
      /* [cover parentID={F372A552-59AF-4f05-A5D1-B407B017041B}][/cover] */
      #if (SPI_SAFETY_ENABLE == STD_ON)
      /* [cover parentID={E5F93421-962F-432f-8CA5-87BCD7B3EB71}]
        Report SPI_E_SAFETY_INVALID_PARAM
        [/cover] */
      Mcal_ReportSafetyError(
                    SPI_MODULE_ID,
                    SPI_INSTANCE_ID,
                    SPI_SID_CONTROLLOOPBACK,
                    SPI_E_SAFETY_INVALID_PARAM);/* End of report to Safety */
      #endif

    }
  }
  return RetVal;
}
#endif
#if(SPI_CANCEL_API == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={7D3C2244-E84A-4e5b-87B2-8471EE5FA4CA}] **
**                                                                            **
** Syntax          : void Spi_Cancel(const Spi_SequenceType Sequence)         **
**                                                                            **
** Service ID      : 0x0C                                                     **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : Sequence - Sequence ID to be cancelled                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : This API cancels the on-going sequence transmission.     **
**                   Sets the sequence status to SPI_SEQ_CANCELLED            **
**                   and job status to SPI_JOB_OK.                            **
**                   Sequence should be in SPI_SEQ_PENDING.                   **
**                   i.e., for Sync Seq, the Sequence should be               **
**                   under execution and for Async Seq the sequence should    **
**                   be in Queue                                              **
*******************************************************************************/
void Spi_Cancel(const Spi_SequenceType Sequence)
{
  #if(SPI_LEVEL_DELIVERED != 0U)
  Spi_JobType StartId, EndId, JobId;
  Spi_SequenceType SeqId;
  uint8 HwId;
  #endif

  uint8 PhysicalSeqId = 0;

  /* Get the core information */
  uint32 CoreId = Mcal_GetCpuIndex();

  #if(SPI_LEVEL_DELIVERED != 0U)
  const Spi_CoreConfigType *CoreConfigPtr;
  #endif

  /* DET / SAFETY ON - Check if valid Sequence ID is received */
  /* [cover parentID={D3B6AD3A-E4CB-4bfb-B9EA-28F402877DC8}][/cover] */
  /* [cover parentID={038A9FE1-B373-4329-AE41-ED1C7750BE25}][/cover] */
  #if ((SPI_DEV_ERROR_DETECT == STD_ON) || (SPI_SAFETY_ENABLE == STD_ON))
  Std_ReturnType RetVal = E_NOT_OK;
  /* [cover parentID={6CA23B89-7C30-4bd7-BBA5-F0366F8E747C}]
  Check the Sequence ID passed is valid and sequence status is SPI_SEQ_PENDING
  [/cover] */
  RetVal = Spi_lCheckInitStatus(SPI_SID_CANCEL, (uint8)SPI_REPORT_DET);
  if(RetVal == (uint8)E_OK)
  {
    /* MISRA2012_RULE_1_3_JUSTIFICATION:  Address of variable PhysicalSeqId
    is used inside Spi_lCheckSeqParam() only to read values.
    The address is not stored for later usage in Spi_lCheckSeqParam().
    Hence it is safe to pass the address of the local variable. */
    RetVal = Spi_lCheckSeqParam(SPI_SID_CANCEL, &PhysicalSeqId, Sequence, \
                                (uint8)SPI_IGNORE_COMMS_TYPE_CHECK);
  }
  /* [cover parentID={5933D2E9-8F56-4eae-BECE-F34FD5E73119}]
   Channel ID is valid and sequence status is SPI_SEQ_PENDING
  [/cover]  */
  if(RetVal == E_OK)
  #else
  /* Read the physical index from the look-up table */
  PhysicalSeqId = Spi_kGlobalConfigPtr->SequenceLookup[Sequence];
  #endif
  {
    /* Check if sequence transmission is ongoing or not */
    if (Spi_RuntimeCoreVar[CoreId]->SeqStatus[PhysicalSeqId] == SPI_SEQ_PENDING)
    {
      /* Enter SchM - Cancel API */
      /* [cover parentID={812826F3-2E4D-46e8-BEBF-8D57CEF20372}]
      Cancel API
      [/cover] */
      SchM_Enter_Spi_Queue_Update();

      #if(SPI_LEVEL_DELIVERED != 0U)
      CoreConfigPtr = Spi_kGlobalConfigPtr->CoreConfigPtr[CoreId];
      JobId =
        CoreConfigPtr->SequenceConfigPtr[PhysicalSeqId].JobLinkPtrPhysical[0U];
      HwId = CoreConfigPtr->JobConfigPtr[JobId].HwUnit & SPI_HWUNIT_MASK;


      /*[cover parentID={F900B899-F708-4b4b-ABF3-8C7ADB65A82A}]QSPI is configured,
       Queue for particular QSPI to be checked for cancelling[/cover] */
      /* Check if the kernel sequence is configured as Async */
      if(Spi_lIsQSPIHwConfiguredAsync(HwId) == (uint8)E_OK)
      {
        /* Traverse through the Job Queue, Get sequence Id from properties */
        StartId = Spi_RuntimeKernelVar[HwId]->JobQueuePtr->QueueStartIndex;
        EndId = Spi_RuntimeKernelVar[HwId]->JobQueuePtr->QueueEndIndex;
      while(StartId != EndId)
      {
        SeqId =                                                              \
            (uint8)(Spi_RuntimeKernelVar[HwId]->
                    JobQueuePtr->JobAndSeqQueuePtr[StartId].JobProperty \
                    & (uint16)SPI_BIT_MASK_7_TO_0);

          /* [cover parentID={B16DD5EC-879A-476d-8897-DAFC37A6535F}]Check if
          job belongs to sequence being cancelled[/cover] */
          if(SeqId == PhysicalSeqId)
          {
            /* Set the job property variable to skip transmission */
            Spi_RuntimeKernelVar[HwId]->JobQueuePtr->
            JobAndSeqQueuePtr[StartId].JobProperty |= SPI_SKIP_JOB_VAL;
            /* Set the Job status as JOB_OK */
            Spi_RuntimeCoreVar[CoreId]->JobStatus[
            Spi_RuntimeKernelVar[HwId]->JobQueuePtr->
            JobAndSeqQueuePtr[StartId].QueueJobId] = SPI_JOB_OK;
        }
        StartId = Spi_lIncrementRoundIndex(StartId, HwId);
      }
    }
    #endif
    /* [cover parentID={A347C3B7-8DB3-48b3-A848-2A93704D9408}]
     Set sequence status as SPI_SEQ_CANCELED
    [/cover] */
    /* Set the sequence status to CANCELLED */
    Spi_RuntimeCoreVar[CoreId]->SeqStatus[PhysicalSeqId] = SPI_SEQ_CANCELED;

    /* Exit SchM - Cancel API */
    SchM_Exit_Spi_Queue_Update();
    }
  }
} /* End of function Spi_Cancel */
#endif /* SPI_CANCEL_API == STD_ON */

/*******************************************************************************
**              Global functions called in the interrupt context              **
*******************************************************************************/

#if(SPI_LEVEL_DELIVERED != 0U)
/*******************************************************************************
** Traceability     : [cover parentID={9FAF7F55-FF2A-4bbb-AC8A-E20267C39FB0}] **
**                                                                            **
** Syntax          : void Spi_QspiDmaCallout                                  **
**                   (const uint8 Channel, const uint32 Event)                **
**                                                                            **
** Service ID      : 0x21                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant for different QSPI HW                          **
** [/cover]                                                                   **
** Parameters (in) : Channel - DMA channel number                             **
**                   Event - DMA channel event                                **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : Invokes QSPI module specific ISRs                        **
*******************************************************************************/
/* [cover parentID={95F53E23-569B-460f-896B-4C4C67D5E32C}][/cover] */
void Spi_QspiDmaCallout(const uint8 Channel, const uint32 Event)
{
  uint8 ModIndex;
  #if(SPI_SAFETY_ENABLE == STD_ON)
  uint8 InvalidChannel = 0xFF;
  #endif
  /* Get core configuration */
  const Spi_CoreConfigType *CoreConfigPtr;
  uint32 CoreId = Mcal_GetCpuIndex();
  CoreConfigPtr = Spi_kGlobalConfigPtr->CoreConfigPtr[CoreId];


  /* [cover parentID={C0C2527E-02B6-4e0e-AFE3-A8E0E8FBB1DF}]
  Loop through all kernels to process DMA RX event
  [/cover] */
  /* Check if DMA has done the complete transfer */
  if((Event & (uint32)DMA_EVENT_CH_TRANSFER_COMPLETE) ==
                    (uint32)DMA_EVENT_CH_TRANSFER_COMPLETE)
  {
    #if(SPI_SAFETY_ENABLE == STD_ON)
    InvalidChannel = 1;
    #endif
    /* Loop through all kernels, check if the DMA is assigned to QSPI */
    for(ModIndex = 0U; ModIndex < SPI_MAX_HW_UNIT; ModIndex++)
    {
      if(CoreConfigPtr->QSPIHwConfigPtr[ModIndex] != NULL_PTR)
      {
        /* [cover parentID={C535FDD8-4FBC-406e-A010-A911E9E60FBE}]
        Check if RX channel of DMA is same as received channel
        [/cover] */
        if(Channel ==
            CoreConfigPtr->QSPIHwConfigPtr[ModIndex]->DMARxChannel)
        {
        #if(SPI_SAFETY_ENABLE == STD_ON)
          /* Channel Found */
          InvalidChannel = 0;
        #endif
          /* Call Rx handler */
          Spi_lIsrDmaQspiRx(ModIndex);

          /* Break and return */
          break;
        }
      }
    }
  }
  /* [cover parentID={DA0D3325-104E-4013-A5DA-59F4C8624D42}][/cover] */
  #if(SPI_SAFETY_ENABLE == STD_ON)
   /* [cover parentID={95AC8E2E-D040-4a86-BC30-F96046E3DB71}][/cover] */
  /* Check for invalid DMA event and Invalid channel */
  if ((Event == (uint32)DMA_EVENT_NONE) || (InvalidChannel == 1U))
  {
    /* [cover parentID={8D42C7B2-F0A3-4df9-A2C7-6E75BDD23C2A}][/cover] */
    Mcal_ReportSafetyError(
                    SPI_MODULE_ID,
                    SPI_INSTANCE_ID,
                    SPI_SID_RX_INTERRUPT,
                    SPI_E_SAFETY_INVALID_PARAM);/* End of report to Safety */
  }
  #endif
}
#endif /* SPI_LEVEL_DELIVERED != 0U */

#if(SPI_LEVEL_DELIVERED != 0U)
/*******************************************************************************
** Traceability     : [cover parentID={1C6853BC-B738-4552-BDB1-29635CF6B975}] **
** Syntax          : static void Spi_lIsrDmaQspiRx(const uint8 Module)        **
**                                                                            **
** Service ID      : NA                                                       **
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
** Description     : Function is called by DMA module on completion of        **
**                   transmission of a channel. Successive channel            **
**                   transmission is triggered by QSPI in this callback.      **
*******************************************************************************/
static void Spi_lIsrDmaQspiRx(const uint8 Module)
{
  Spi_JobType JobId;
  Spi_ChannelType ChnlId, ChnlIndex;
  uint8 ToggleCs;
  Ifx_QSPI* ModulePtr;

  /* Get core configuration */
  const Spi_CoreConfigType *CoreConfigPtr;
  uint32 CoreId = Mcal_GetCpuIndex();
  CoreConfigPtr = Spi_kGlobalConfigPtr->CoreConfigPtr[CoreId];

  /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
   * effects foreseen by violating this MISRA rule. */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access.
  No side effects foreseen by violating this MISRA rule, as the pointer
  to the object type that it is getting cast into, is a known type. */
  ModulePtr = &(SPI_HW_MODULE[Module]);

  /* [cover parentID={46BB41A0-7BC0-49da-91D7-A3099E3118B4}] Start
  transmission[/cover] */
  /* Check if the QSPI kernel is busy transmitting */
  if(Spi_RuntimeKernelVar[Module]->AsyncComStatus == SPI_BUSY)
  {
    JobId =
      Spi_RuntimeKernelVar[Module]->JobQueuePtr->JobAndSeqQueuePtr[  \
          Spi_RuntimeKernelVar[Module]->JobQueuePtr->QueueStartIndex].   \
      QueueJobId;
    ChnlIndex =
      Spi_RuntimeKernelVar[Module]->JobQueuePtr->CurrentChannelIndex;
    ChnlIndex++;
    ChnlId =
      CoreConfigPtr->JobConfigPtr[JobId].ChnlLinkPtrPhysical[ChnlIndex];
    ToggleCs = CoreConfigPtr->JobConfigPtr[JobId].FramebasedCs;

    /* [cover parentID={7EB92B50-CD09-4b55-AF79-EEB194FEA255}] Start
    transmission of next channel[/cover] */
    /* Check if the current channel is last channel to be transmitted,
     * else PT2 interrupt will trigger indicating "end of frame" */
    if(ChnlId != SPI_CHANNEL_DELIMITER)
    {
      Spi_RuntimeKernelVar[Module]->JobQueuePtr->CurrentChannelIndex++;

      /* [cover parentID={2316D2BB-0C35-4e5b-87D0-887B1C3ABE21}][/cover] */
      /* Enable RX DMA */
      Dma_ChEnableHardwareTrigger(                                         \
          (uint8)(CoreConfigPtr->QSPIHwConfigPtr[Module]->DMARxChannel));
      /* [cover parentID={2A46A3C9-D9CA-4861-B99E-28FDEBCB63D5}][/cover]*/
      /* Trigger the DMA TX for next channel */
      Dma_ChEnableHardwareTrigger(                                         \
          (uint8)(CoreConfigPtr->QSPIHwConfigPtr[Module]->DMATxChannel));
      /* [cover parentID={2AD70796-65D8-4c5d-8034-9B6F3D67D6B6}][/cover] */
      /* Set channel configuration since the data-width can be different */
      ModulePtr->BACONENTRY.U = \
                 Spi_RuntimeKernelVar[Module]->BaconChannelArray[ChnlIndex].U;
    }
    else
    {
      /* [cover parentID={EA634B3D-A1AC-4f99-AEFF-879B2475B407}] Check if
      frame based CS is enabled, call for next job[/cover]*/
      if(ToggleCs == SPI_TRIGGER_ENABLE)
      {
        Spi_lQspiTriggerNextJob(Module, SPI_SID_RX_INTERRUPT, 0U);
      }
    }
  }

} /* End of function Spi_lIsrDmaQspiRx */
#endif /* SPI_LEVEL_DELIVERED != 0U */

#if(SPI_LEVEL_DELIVERED != 0U)
/*******************************************************************************
** Traceability     : [cover parentID={9D6F01FD-3633-458a-8DCA-1A033E01EF84}] **
**                                                                            **
** Syntax          : static void Spi_lQspiTriggerNextJob(const uint8 Module,  **
**                                       const uint8 ApiId,                   **
**                                       const uint8 Pt2Status)               **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant for different QSPI HW                          **
**                                                                            **
** Parameters (in) : Module - QSPI module index [0 to SPI_MAX_HW_UNIT]        **
**                   ApiId - Service ID of called function                    **
**                   Pt2Status - Represents PT2 enable status                 **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : Triggers the next job transmission after checking for    **
**                     PT2(End of frame) status of previous Job transmission  **
*******************************************************************************/
static void Spi_lQspiTriggerNextJob(const uint8 Module, const uint8 ApiId,
                                           const uint8 Pt2Status)
{
  Spi_SequenceType SeqId;
  Spi_SeqResultType SeqResult;
  uint8 ToggleCs;
  Spi_JobType JobId;

  /* Get Core and kernel information */
  Ifx_QSPI* ModulePtr;

  /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
   * effects foreseen by violating this MISRA rule. */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
  effects foreseen by violating this MISRA rule, as the pointer
  to the object type that it is getting cast into, is a known type. */
  ModulePtr = &(SPI_HW_MODULE[Module]);

  /* Get core configuration */
  const Spi_CoreConfigType *CoreConfigPtr;
  uint32 CoreId = Mcal_GetCpuIndex();
  CoreConfigPtr = Spi_kGlobalConfigPtr->CoreConfigPtr[CoreId];

  /* Fetch the Job ID transmitted */
  JobId = Spi_RuntimeKernelVar[Module]->JobQueuePtr->JobAndSeqQueuePtr[\
          Spi_RuntimeKernelVar[Module]->JobQueuePtr->QueueStartIndex].   \
          QueueJobId;

  ToggleCs = CoreConfigPtr->JobConfigPtr[JobId].FramebasedCs;
  /* [cover parentID={36E6F05B-C76B-4c6f-80E4-83FE89A4046D}]
  Check for source of interrupt - PT2
  [/cover] */
  /* Check for Source of interrupt, either Job based CS / PT2 interrupt */
  if((ToggleCs == SPI_TRIGGER_ENABLE) || \
      (Pt2Status == SPI_TRIGGER_ENABLE))
  {
    /* Fetch the sequence ID in transmisison */
    SeqId = (Spi_SequenceType)\
            (Spi_RuntimeKernelVar[Module]->JobQueuePtr->JobAndSeqQueuePtr[ \
                Spi_RuntimeKernelVar[Module]->JobQueuePtr->QueueStartIndex]. \
             JobProperty & (uint16)SPI_BIT_MASK_7_TO_0);

    /* Disable Move counter - Since frame is complete */
    ModulePtr->MCCON.B.MCEN = 0;

    /* [cover parentID={FF3A678C-A7C4-411a-A970-16DCE204DDF2}]
    Check for sequence status
    [/cover] */
    /* Get sequence status */
    if(Spi_RuntimeCoreVar[CoreId]->SeqStatus[SeqId] == SPI_SEQ_CANCELED)
    {
      SeqResult = SPI_SEQ_CANCELED;
    }
    else
    {
      SeqResult = SPI_SEQ_OK;
    }

    /* [cover parentID={19FDA54E-8B52-49fa-A0EE-EBB4DB94D551}]
    Call lBusHandler to handle successive job transmission
    [/cover] */
    Spi_lBusHandler(Module, SeqResult, SPI_JOB_OK);

    /* Raise Production Error */
    /* [cover parentID={74823431-BBBF-42e4-80D9-26163D84DBA8}][/cover] */
    #if(SPI_HW_ERROR_DEM_REPORT == SPI_DEM_REPORT_ENABLED)
    /* [cover parentID={768F4DBD-274F-4FC3-B069-345E642E5297}][/cover] */
    Spi_lReportDemError(SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_PASSED);
    #endif
  }
  #if(SPI_SAFETY_ENABLE == STD_ON)
  else
  {
    /* [cover parentID={35AF0CD6-D3E9-4cde-B778-D941186948BC}]
    Spurious interrupt - DET
    [/cover] */
    /* ISR invalid ISR DET */
    Mcal_ReportSafetyError(
                SPI_MODULE_ID,
                SPI_INSTANCE_ID,
                ApiId,
                SPI_E_SAFETY_SPURIOUS_INTERRUPT);/* End of report to Safety */
  }
  #endif
  #if(SPI_SAFETY_ENABLE == STD_OFF)
  UNUSED_PARAMETER(ApiId);
  #endif
}

/*******************************************************************************
** Traceability     : [cover parentID={D84AC1CE-5680-4e06-9123-2648FCE6AA9C}] **
**                                                                            **
** Syntax          : void Spi_IsrQspiPT2(const uint8 Module)                  **
**                                                                            **
** Service ID      : 0x22                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant for different QSPI HW                          **
**                                                                            **
** Parameters (in) : Module - QSPI module index [0 to 5]                      **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : This Interrupt Service routine marks the end of the      **
**                   frame transmission and is triggered only at the end of   **
**                   the job transmission. Total number of elements to be     **
**                   transmitted in a next job is updated in the MCCOUNT      **
**during this interrupt and respective DMA channels are re-triggered.         **
*******************************************************************************/
void Spi_IsrQspiPT2(const uint8 Module)
{
  uint8 Pt2Status = 0;
  uint8 Pt2ENStatus = 0;

  /* [cover parentID={64D417FE-2506-4d54-B9FB-98A97E86CD42}] Check
  parameter [/cover] */
  if(Module < SPI_MAX_HW_UNIT)
  {
    /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
     * effects foreseen by violating this MISRA rule, as the pointer to
     * the object type that it is getting cast into, is a known type. */
    /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
    effects foreseen by violating this MISRA rule, as the pointer
    to the object type that it is getting cast into, is a known type. */
    Pt2Status = (uint8) (SPI_HW_MODULE[Module].STATUS.B.PT2F);

    /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
     * effects foreseen by violating this MISRA rule, as the pointer to
     * the object type that it is getting cast into, is a known type. */
    /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access.
    No side effects foreseen by violating this MISRA rule, as the pointer
    to the object type that it is getting cast into, is a known type. */
    SPI_HW_MODULE[Module].FLAGSCLEAR.B.PT2C = 1U;

    /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
     * effects foreseen by violating this MISRA rule, as the pointer to
     * the object type that it is getting cast into, is a known type. */
    /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
    effects foreseen by violating this MISRA rule, as the pointer
    to the object type that it is getting cast into, is a known type. */
    Pt2ENStatus = (uint8) (SPI_HW_MODULE[Module].GLOBALCON1.B.PT2EN);
    Pt2Status  = (Pt2Status & Pt2ENStatus);
    Spi_lQspiTriggerNextJob(Module, SPI_SID_PT2_INTERRUPT, Pt2Status);

  }
  /* [cover parentID={068801CE-7D51-4218-B161-A52D0AC82FFA}][/cover] */
  #if(SPI_SAFETY_ENABLE == STD_ON)
  else
  {
    /* [cover parentID={83F51FC5-FBD2-43b4-AAD5-E9476261B6D7}][/cover] */
    /* ISR invalid ISR DET */
    Mcal_ReportSafetyError(
                    SPI_MODULE_ID,
                    SPI_INSTANCE_ID,
                    SPI_SID_PT2_INTERRUPT,
                    SPI_E_SAFETY_INVALID_PARAM);/* End of report to Safety */
  }
  #endif
}
#endif

#if(SPI_LEVEL_DELIVERED != 0U)
/*******************************************************************************
** Traceability    : [cover parentID={C5A29B57-E29D-4d36-82DB-44460A414EF2}]  **
**                                                                            **
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
void Spi_IsrQspiError(const uint8 Module)
{
  /* [cover parentID={2647200E-4B51-4110-8A4A-626A07F04C85}] Check for
  valid parameter in ISR [/cover] */
  if(Module < SPI_MAX_HW_UNIT)
  {
    /* Check if any QSPI error flags are SET */
    /* [cover parentID={E5786683-BC42-4f22-BD79-C04DEC8DCFE2}][/cover] */
    /* [cover parentID={C5DC981B-5373-4d12-BD17-1E57DCDC2D83}]
    Check if any QSPI error flags are SET
    [/cover] */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
     * effects foreseen by violating this MISRA rule. */
    /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
    effects foreseen by violating this MISRA rule, as the pointer
    to the object type that it is getting cast into, is a known type. */
    if((SPI_HW_MODULE[Module].STATUS.B.ERRORFLAGS &                          \
        SPI_GLOBALCON1_ERROREN) != 0U)
    {
      /* Clear the error status */
      /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
       * effects foreseen by violating this MISRA rule.*/
      /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
      effects foreseen by violating this MISRA rule, as the pointe
      r to the object type that it is getting cast into, is a known type. */
      SPI_HW_MODULE[Module].FLAGSCLEAR.U = (SPI_QSPI_FLAGSCLEAR_VALUE);
      /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
       * effects foreseen by violating this MISRA rule. */
      /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
      effects foreseen by violating this MISRA rule, as the pointer
      to the object type that it is getting cast into, is a known type. */
      SPI_HW_MODULE[Module].FLAGSCLEAR.B.PT2C = 1U;
      /* [cover parentID={2160B614-23FF-4377-B5B4-89695321A82C}][/cover] */
      if(Spi_RuntimeKernelVar[Module]->AsyncComStatus == SPI_BUSY)
      {
        /* [cover parentID={F9C7D373-8B51-4873-916E-7C0855E22D6E}]
         Call Error handler to stop the current sequence
        [/cover] */
        Spi_lErrorHandler(Module);
      }
    }
    /* [cover parentID={EC31834E-BEFB-484b-A2AE-8644CFA7369A}][/cover] */
    #if(SPI_SAFETY_ENABLE == STD_ON)
    else
    {
      /* [cover parentID={6E2BD464-AB22-47b9-B114-B3037A36E05C}]
      Spurious interrupt - DET
      [/cover] */
      /* ISR invalid ISR DET */
      Mcal_ReportSafetyError(
                SPI_MODULE_ID,
                SPI_INSTANCE_ID,
                SPI_SID_QSPI_ERROR_INTERRUPT,
                SPI_E_SAFETY_SPURIOUS_INTERRUPT);/* End of report to Safety */
    }
  #endif
  }
  /* [cover parentID={2E28B1B5-0F7A-4b71-8FC0-6A70B476BD70}][/cover] */
  #if(SPI_SAFETY_ENABLE == STD_ON)
  else
  {
    /* [cover parentID={7176F4EA-1BC3-4a78-998C-606464C5E10A}][/cover] */
    /* Invalid ISR  DET */
    Mcal_ReportSafetyError(
                    SPI_MODULE_ID,
                    SPI_INSTANCE_ID,
                    SPI_SID_QSPI_ERROR_INTERRUPT,
                    SPI_E_SAFETY_INVALID_PARAM);/* End of report to Safety */
  }
  #endif
} /* End of function Spi_IsrQspiError */
#endif /* SPI_LEVEL_DELIVERED != 0U */

#if(SPI_LEVEL_DELIVERED != 0U)
/*******************************************************************************
** Traceability    : [cover parentID={2A951311-BDBE-44f9-965F-9AEFF4349B46}]  **
**                                                                            **
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
** Description     : Invokes QSPI specific DMA error handler                  **
*******************************************************************************/
void Spi_QspiDmaErrCallout(const uint8 Channel, const uint32 Event)
{
  uint8 ModIndex;
  #if (SPI_SAFETY_ENABLE == STD_ON)
  uint8 InvalidChannel = 1;
  #endif
  /* Get the core information */
  const Spi_CoreConfigType *CoreConfigPtr;
  uint32 CoreId = Mcal_GetCpuIndex();
  CoreConfigPtr = Spi_kGlobalConfigPtr->CoreConfigPtr[CoreId];

  /* Loop through all kernels, check if the DMA is assigned to QSPI */
  /* [cover parentID={A3215F04-3A09-4918-B5FA-36756B492231}]
  Is QSPI kernel configured for core
  [/cover] */
  for(ModIndex = 0U; ModIndex < SPI_MAX_HW_UNIT; ModIndex++)
  {
    if(CoreConfigPtr->QSPIHwConfigPtr[ModIndex] != NULL_PTR)
    {
      /* [cover parentID={98786E53-8337-469e-ACC6-3BF7D0FAF6AA}]
      Check if RX channel matches to process error
      [/cover] */
      if((Channel ==
          CoreConfigPtr->QSPIHwConfigPtr[ModIndex]->DMARxChannel) || \
          (Channel ==
           CoreConfigPtr->QSPIHwConfigPtr[ModIndex]->DMATxChannel))
      {
        #if (SPI_SAFETY_ENABLE == STD_ON)
        InvalidChannel = 0;
        #endif
        /* Call error handler */
        Spi_lErrorHandler(ModIndex);
      }
    }
  }
  UNUSED_PARAMETER(Event);
  /* [cover parentID={89B01D0D-DB2F-4005-BACF-90724A9B11C7}][/cover] */
  #if (SPI_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={7DFAB88B-F316-4ab7-8496-4B232626B214}][/cover] */
  if (InvalidChannel == 1U)
  {
    /* [cover parentID={6569ED88-2C1B-46ee-8F3F-2D133B292604}][/cover] */
    Mcal_ReportSafetyError(
                    SPI_MODULE_ID,
                    SPI_INSTANCE_ID,
                    SPI_SID_DMA_ERROR_INTERRUPT,
                    SPI_E_SAFETY_INVALID_PARAM);/* End of report to Safety */
  }
  #endif
}
#endif

/*******************************************************************************
**                     Scheduled function                                     **
*******************************************************************************/

#if(SPI_LEVEL_DELIVERED == 2U)
/*******************************************************************************
**                                                                            **
** Traceability     : [cover parentID={DB5B91F0-5941-4be1-9DBB-ABC8FB3C3B17}] **
**                                                                            **
** Syntax          : void Spi_MainFunction_Handling(void)                     **
**                                                                            **
** Service ID      : 0x10                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non-Reentrant                                            **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : This function polls the SPI interrupts linked to         **
**                   QSPI HW units allocated to the transmission of SPI       **
**                   sequences to enable the evolution of transmission        **
**                   state machine.                                           **
*******************************************************************************/
void Spi_MainFunction_Handling(void)
{
  /* [cover parentID={F5642A9A-B4FB-4e46-8262-383CAFECF805}]
     Spi_MainFunction_Handling
  [/cover] */
  uint8 QspiModIndex;
  #if ((SPI_DEV_ERROR_DETECT == STD_ON) || (SPI_SAFETY_ENABLE == STD_ON))
  Std_ReturnType RetVal;
  #endif
  uint32 CoreId = Mcal_GetCpuIndex();
  /* Check if Driver is initialzed */
  /* [cover parentID={59FF2F41-5BD3-4260-990A-4C925780DB35}]
   SPI_DEV_ERROR_DETECT or SPI_SAFETY_ENABLE is ON
  [/cover] */
  #if ((SPI_DEV_ERROR_DETECT == STD_ON) || (SPI_SAFETY_ENABLE == STD_ON))
  /* [cover parentID={A711865D-B4A5-4b77-B0CF-821BFCB942D1}]
   Check if Driver is initialzed
  [/cover] */
  RetVal = Spi_lCheckInitStatus(SPI_SID_MAINFUNCTION_HANDLING, \
                                (uint8)SPI_DET_DISABLE);
  /* [cover parentID={B2225693-0DB1-4465-8D0F-846B5EEC0656}]
   Driver is initialized
  [/cover] */
  if(RetVal == (uint8)E_OK)
  #endif
  {
    /* Applicable only if in "Polling mode" */
    /* [cover parentID={EA71C3F7-777F-4478-B1F2-A6FCA446D128}]
     Check polling mode is ON
    [/cover] */
    if(Spi_RuntimeCoreVar[CoreId]->AsyncMode == SPI_POLLING_MODE)
    {
      /* [cover parentID={B32E6868-8E27-44d8-816B-050E24258CF0}]
       Check for all kernels
      [/cover] */
      /* Loop through all kernels */
      for(QspiModIndex = 0U; QspiModIndex < SPI_MAX_HW_UNIT; QspiModIndex++)
      {
        /* Check if kernel is assigned for async communication */
        /* [cover parentID={C76DFC2C-1B5D-4f76-B269-C50A27003B69}]
        Check if kernel is async-type
        [/cover] */
        if(Spi_lIsQSPIHwConfiguredAsync(QspiModIndex) == (uint8)E_OK)
        {
          if (Spi_RuntimeKernelVar[QspiModIndex]->AsyncComStatus == SPI_BUSY)
          {
            Spi_lModMainFunction(QspiModIndex);
          }
        }
      }
    }
  }
} /* End of function Spi_MainFunction_Handling */
#endif /* SPI_LEVEL_DELIVERED == 2U */

/*******************************************************************************
**                     Private Function Definitions                           **
*******************************************************************************/

#if(SPI_LEVEL_DELIVERED != 0U)
/*******************************************************************************
**                                                                            **
** Traceability     : [cover parentID={0C8E1ECF-3DEE-47bd-AF40-38025E434A30}] **
** Syntax          : static void Spi_lBusHandler                              **
**                   (                                                        **
**                     const uint8 Module,                                    **
**                     const Spi_SeqResultType SeqRes,                        **
**                     const Spi_JobResultType JobRes                         **
**                   )                                                        **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant for different QSPI HW                          **
**                                                                            **
** Parameters (in) : Module - Qspi module index                               **
**                   SeqRes - Seq Result to be updated                        **
**                   JobRes - Job Result to be updated                        **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : This function sets up the transmission for next job      **
**                   if present else will terminate the transmission by       **
**                   setting up the statuses for Sequence and jobs, also it   **
**                   invokes notification function if configured.             **
*******************************************************************************/
static void Spi_lBusHandler
(
  const uint8 Module,
  const Spi_SeqResultType SeqRes,
  const Spi_JobResultType JobRes
)
{
  const Spi_JobConfigType* JobConfigPtr;
  Spi_JobType StartId, EndId;
  uint16 SeqStatus;
  Spi_SequenceType SeqId;
  uint8 CsPolarity;
  uint16 LastJobinSeq = 0;
  uint16 JobId = 0;

  /* Get the core config information */
  const Spi_CoreConfigType *CoreConfigPtr;
  uint32 CoreId = Mcal_GetCpuIndex();
  CoreConfigPtr = Spi_kGlobalConfigPtr->CoreConfigPtr[CoreId];

  /* Disable Qspi Error interrupt */
  Spi_lDisQspiErrIntr(Module);

  /* Get the sequence, job id and job Queue location to be processed */
  StartId = Spi_RuntimeKernelVar[Module]->JobQueuePtr->QueueStartIndex;
  JobId = Spi_RuntimeKernelVar[Module]->JobQueuePtr->
          JobAndSeqQueuePtr[StartId].QueueJobId;
  SeqId = (Spi_SequenceType)(Spi_RuntimeKernelVar[Module]->JobQueuePtr->\
          JobAndSeqQueuePtr[StartId].JobProperty & (uint16)SPI_BIT_MASK_7_TO_0);

  /* Get job configuration pointer and channel Id to be processed*/
  JobConfigPtr = &CoreConfigPtr->JobConfigPtr[JobId];
  Spi_RuntimeKernelVar[Module]->JobQueuePtr->CurrentJobIndex++;

  /* [cover parentID={0EBB2AAB-9001-495c-A9AB-E5A25C849D51}]
   Handling Chip select after transmisison of job
  [/cover] */
  /* If CS handled via port pin, enable CS based on polarity configured */
  if(JobConfigPtr->CSPortPin != SPI_CS_VIA_HW_OR_NONE)
  {
    if(CoreConfigPtr->JobConfigPtr[JobId].CsPolarity == (uint8)STD_LOW)
    {
      CsPolarity = (uint8)STD_LOW;
    }
    else
    {
      CsPolarity = (uint8)STD_HIGH;
    }

    Spi_lSetCsViaGpio(
      (uint8)((JobConfigPtr->CSPortPin) >> (uint16)SPI_PORT_NUM_OFFSET),     \
      (uint8)((JobConfigPtr->CSPortPin) & SPI_BIT_MASK_3_TO_0),       \
      CsPolarity);
  }

  /* [cover parentID={1A914736-E4F5-491f-96FF-E0273FBA73DF}]
   Update job status
  [/cover] */
  Spi_RuntimeCoreVar[CoreId]->JobStatus[JobId] = JobRes;
  /* [cover parentID={8CC9B03C-4A5F-40e7-8880-4999A24B1E38}][/cover] */
  /* Check and call callback Notification function if configured */
  if(JobConfigPtr->JobNotification != NULL_PTR)
  {
    JobConfigPtr->JobNotification();
  }

  LastJobinSeq = (CoreConfigPtr->SequenceConfigPtr[SeqId].\
                  NoOfJobInSeq - 1U);

  /* [cover parentID={774B2859-543A-46b6-AC06-62A2895FA88E}][/cover] */
  /* [cover parentID={C9DD3816-4AEA-4023-BC55-F8DB43564E67}]
       Reentrancy
  [/cover] */
  /* Enter SchM - Since Queue / status variables are updated */
  SchM_Enter_Spi_Queue_Update();

  /* [cover parentID={ADE4726E-01E1-4888-956B-A8FB30150401}] Check for
     last job in sequence or check if error occured [/cover] */
  /* Check if completed Job was the last job for sequence OR if
      sequence is failed OR Cancelled */
  if((CoreConfigPtr->SequenceConfigPtr[SeqId].\
      JobLinkPtrPhysical[LastJobinSeq] == JobId) ||
      (SeqRes == SPI_SEQ_FAILED) || (SeqRes == SPI_SEQ_CANCELED))
  {
    Spi_RuntimeKernelVar[Module]->JobQueuePtr->CurrentJobIndex = 0U;

    /* [cover parentID={85D502FC-8737-46a9-A86E-9292CCD933AE}]
     Update sequence result
    [/cover] */
    /* Set sequence status to SPI_SEQ_OK after the job is completed */
    Spi_RuntimeCoreVar[CoreId]->SeqStatus[SeqId] = SeqRes;

    /* Check and call seq notification if configured */
    /* [cover parentID={2C2344AF-972C-44f0-8B0E-7DC6C4D2083A}]
     Call sequence notification function
    [/cover] */
    /* [cover parentID={3F7237E5-DA82-4018-9080-AFD6C96CA021}]
     Sequence notification is configured
    [/cover] */
    /* [cover parentID={988246C2-69F9-4937-8376-5100E83EA1AA}][/cover] */
    if(CoreConfigPtr->SequenceConfigPtr[SeqId].SeqNotification != NULL_PTR)
    {
      CoreConfigPtr->SequenceConfigPtr[SeqId].SeqNotification();
    }
  }

  /* Clear the Queue variables */
  Spi_RuntimeKernelVar[Module]->JobQueuePtr->
  JobAndSeqQueuePtr[StartId].QueueJobId = 0;
  Spi_RuntimeKernelVar[Module]->JobQueuePtr->
  JobAndSeqQueuePtr[StartId].JobProperty = SPI_SEQUENCE_DELIMITER;

  /* Loop through rest of the jobs and skip cancelled sequences */
  StartId = Spi_RuntimeKernelVar[Module]->JobQueuePtr->QueueStartIndex;
  EndId = Spi_RuntimeKernelVar[Module]->JobQueuePtr->QueueEndIndex;

  /* [cover parentID={54BDE6E9-1A5B-4fe8-976F-AF02FEDCDFB5}]
    Asynctransmit - Transmit next job from Queue, ignore cancelled jobs
    [/cover] */
  while(StartId != EndId)
  {
    StartId = Spi_lIncrementRoundIndex(StartId, Module);

    SeqStatus =      \
                     (Spi_RuntimeKernelVar[Module]->JobQueuePtr->
                      JobAndSeqQueuePtr[StartId].JobProperty);

    SeqStatus = (SeqStatus & SPI_SKIP_JOB_VAL);

    if(SeqStatus == 0U)
    {
      /* Break if job is available for transmission */
      break;
    }
  }

  /* [cover parentID={2342D461-0252-4e68-B495-D5C36CFEC793}] Check if more
  jobs to be transmitted [/cover] */
  /* Check if there are any more jobs on the queue to be transmitted */
  Spi_RuntimeKernelVar[Module]->JobQueuePtr->QueueStartIndex = StartId;
  if(StartId != EndId)
  {
    JobId = Spi_RuntimeKernelVar[Module]->JobQueuePtr->
            JobAndSeqQueuePtr[StartId].QueueJobId;

    /* Start Next Job in the Queue */
    Spi_lAsyncStartJob(JobId);
  }
  else
  {
    /* Last job in Queue transmitted, clear all Queue variables */
    Spi_RuntimeKernelVar[Module]->JobQueuePtr->QueueStartIndex = 0U;
    Spi_RuntimeKernelVar[Module]->JobQueuePtr->QueueEndIndex = 0U;

    /* Set bus status to IDLE since all jobs are transmitted */
    Spi_RuntimeKernelVar[Module]->AsyncComStatus = SPI_IDLE;
  /* Set bus KernelStatus to IDLE since all jobs are transmitted */
    Spi_RuntimeKernelVar[Module]->KernelStatus = SPI_IDLE;
  }
  /* [cover parentID={9A0C63A6-81A6-4855-983C-8AA861AAA491}]
     Reentrancy
  [/cover] */
  /* Exit SchM */
  SchM_Exit_Spi_Queue_Update();
} /* End of function Spi_lBusHandler */
#endif /* SPI_LEVEL_DELIVERED != 0U */

#if(SPI_LEVEL_DELIVERED != 0U)
/*******************************************************************************
** Traceability     : [cover parentID={4490D689-E691-46df-AFB6-A7E8203FAE25}] **
** Syntax          : static void Spi_lErrorHandler(const uint8 Module)        **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant for different QSPI HW                          **
**                                                                            **
** Parameters (in) : Module - Qspi module index                               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : This function handles the Hw error event raised by QSPI  **
**                   when the driver is busy.                                 **
*******************************************************************************/
static void Spi_lErrorHandler(const uint8 Module)
{
  Spi_JobType StartId, EndId;
  Spi_SequenceType SeqId, Sequence;

  const Spi_CoreConfigType *CoreConfigPtr;
  uint32 CoreId = Mcal_GetCpuIndex();
  /* MISRA2012_RULE_19_2_JUSTIFICATION: register type Definition */
  Ifx_QSPI_GLOBALCON GlobalConReg;
  CoreConfigPtr = Spi_kGlobalConfigPtr->CoreConfigPtr[CoreId];

  StartId = Spi_RuntimeKernelVar[Module]->JobQueuePtr->QueueStartIndex;
  EndId = Spi_RuntimeKernelVar[Module]->JobQueuePtr->QueueEndIndex;

  /* Disable the Move counter */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
  effects foreseen by violating this MISRA rule, as the pointer
  to the object type that it is getting cast into, is a known type. */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
   * effects foreseen by violating this MISRA rule. */
  SPI_HW_MODULE[Module].MCCON.B.MCEN = 0;

  /* Reset the Counter to 0 */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
  effects foreseen by violating this MISRA rule, as the pointer
  to the object type that it is getting cast into, is a known type. */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
   * effects foreseen by violating this MISRA rule. */
  SPI_HW_MODULE[Module].MC.B.MCOUNT = 0;

  /* Reset QSPI HW state machine */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
  effects foreseen by violating this MISRA rule, as the pointer
  to the object type that it is getting cast into, is a known type. */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
   * effects foreseen by violating this MISRA rule. */
  GlobalConReg.U = SPI_HW_MODULE[Module].GLOBALCON.U;
  GlobalConReg.B.RESETS = 1;

  /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
  effects foreseen by violating this MISRA rule, as the pointer
  to the object type that it is getting cast into, is a known type. */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
   * effects foreseen by violating this MISRA rule. */
  SPI_SFR_RUN_TIME_WRITE32(&SPI_HW_MODULE[Module]. \
                                        GLOBALCON.U, GlobalConReg.U);

  /* [cover parentID={261B4760-B189-43b7-A383-708480135ECA}][/cover] */
  /* Disable DMA Tx Channel */
  Dma_ChStopTransfer(CoreConfigPtr->QSPIHwConfigPtr[Module]->DMATxChannel);

  /* Get the sequence being transmitted */
  Sequence =                                                                  \
      (Spi_SequenceType)(Spi_RuntimeKernelVar[Module]->JobQueuePtr->  \
                         JobAndSeqQueuePtr[StartId].JobProperty          \
                         & (uint16)SPI_BIT_MASK_7_TO_0);

  /* [cover parentID={39492211-3861-4f52-A38F-511579039259}]
   Check all jobs in Async Queue assigned to sequence
  [/cover] */
  /* Loop through all the jobs in Queue */
  while(StartId != EndId)
  {
    /* Get sequence Id from the job pointer */
    SeqId =
      (Spi_SequenceType)(Spi_RuntimeKernelVar[Module]->JobQueuePtr-> \
          JobAndSeqQueuePtr[StartId].JobProperty & (uint16)SPI_BIT_MASK_7_TO_0);

    /* [cover parentID={CE698A26-12E2-411a-9F98-0D8C5EFF4BD5}]
    Ignore all jobs with sequence errors
    [/cover] */
    /* Set the Job property to be "skipped" and set the
    job status to "SPI_JOB_FAILED" */
    if(SeqId == Sequence)
    {
      /* Set the 15th bit in the Job Property varaible */
      Spi_RuntimeKernelVar[Module]->JobQueuePtr->
      JobAndSeqQueuePtr[StartId].JobProperty |= SPI_SKIP_JOB_VAL;
      Spi_RuntimeCoreVar[CoreId]->JobStatus[Spi_RuntimeKernelVar[Module]->
           JobQueuePtr->JobAndSeqQueuePtr[StartId].QueueJobId] = SPI_JOB_FAILED;
    }
    StartId = Spi_lIncrementRoundIndex(StartId, Module);
  }

  /* [cover parentID={943852F7-EA6C-41ac-94CB-8AD98AE6B320}]
   Report Job, sequence failure
  [/cover] */
  Spi_lBusHandler(Module, SPI_SEQ_FAILED, SPI_JOB_FAILED);

  /* Raise Production Error */
  /* [cover parentID={B7C31BAC-50EE-4708-B3FF-38DB00C8A7F5}][/cover] */
  #if(SPI_HW_ERROR_DEM_REPORT == SPI_DEM_REPORT_ENABLED)
  /* [cover parentID={78406A85-B1F0-46df-AA57-D1E05ED110A9}][/cover] */
  Spi_lReportDemError(SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
  #endif

} /* End of function Spi_lErrorHandler */
#endif /* SPI_LEVEL_DELIVERED != 0U */

/*******************************************************************************
** Traceability     : [cover parentID={C1F17EBD-75A2-40b6-9B42-6B504F666F1B}] **
** Syntax          : static Std_ReturnType Spi_lCheckInitStatus               **
**                   (                                                        **
**                      const uint8 ApiId                                     **
**                      const uint8 DetRaise                                  **
**                   )                                                        **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : ApiId - Service id of the API which is invoking          **
**                   DetRaise - Is Det requiret to be raised,                 **
**              i.e., 0U - Det should not be raised                           **
**                    1U - Det should be raised                               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: driver is initialized                              **
**                   E_NOT_OK: driver is not initialized                      **
**                                                                            **
** Description     : This local function checks whether the                   **
**                                 SPI driver is initialized                  **
*******************************************************************************/
static Std_ReturnType Spi_lCheckInitStatus(const uint8 ApiId,
    const uint8 DetRaise)
{
  Std_ReturnType RetVal = E_OK;
  uint8 LoopIndex = 0U;

  /* Get core information */
  uint32 CoreId = Mcal_GetCpuIndex();

  /* [cover parentID={DCBF474B-832E-4f35-88FF-A9FFC2CED2EB}]Check if INIT
  API or another API [/cover] */
  if((ApiId == SPI_SID_INIT))
  {
    /* [cover parentID={87F9F6DA-66E5-4dde-A37B-4AD5DB8CE893}]Check
    if core pointers are updated[/cover] */
    if((Spi_RuntimeCoreVar[CoreId] != NULL_PTR))
    {
      RetVal = E_NOT_OK;
    }
  }
  else
  {
    /* [cover parentID={C4DCCDE2-4EC6-4fb3-B4D0-568B40ED46E3}]Check if
      core pointers are initialized [/cover] */
    if((Spi_RuntimeCoreVar[CoreId] != NULL_PTR))
    {
      /* If Level-1 OR Level-2, check the async kernel status if
       * not initialized */
      for(LoopIndex = 0U; LoopIndex < SPI_MAX_HW_UNIT; LoopIndex++)
      {
        #if((SPI_LEVEL_DELIVERED == 1U) || (SPI_LEVEL_DELIVERED == 2U))
        if(Spi_lIsQSPIHwConfiguredAsync(LoopIndex) == (uint8)E_OK)
        {
          if(Spi_RuntimeKernelVar[LoopIndex]->AsyncComStatus == SPI_UNINIT)
          {
            /* Return E_NOT_OK and break */
            RetVal = E_NOT_OK;
          }
        }
        #endif
        /* [cover parentID={6218CC3A-0CC5-4588-9A23-67098181A7F0}]
          Check if kernel status is UNINIT
          [/cover] */
        if(Spi_lIsQSPIHwConfigured(LoopIndex) == (uint8)E_OK)
        {
          if(Spi_RuntimeKernelVar[LoopIndex]->KernelStatus == SPI_UNINIT)
          {
            /* Return E_NOT_OK and break */
            RetVal = E_NOT_OK;
          }
        }
        if (RetVal == E_NOT_OK)
        {
          break;
        }
      }

    }
    else
    {
      RetVal = E_NOT_OK;
    }
    /* [cover parentID={FD9707EC-08BA-4a96-91BB-98D3C35D9186}][/cover] */
    #if ((SPI_DEV_ERROR_DETECT == STD_ON) || \
    (SPI_SAFETY_ENABLE == STD_ON))
    /* [cover parentID={DBA2A857-8885-483f-947C-BFF6449BC0BC}][/cover] */
    if(RetVal == (uint8)E_NOT_OK)
    {
      if(DetRaise == SPI_REPORT_DET)
      {
        /* [cover parentID={12B45F62-BEE4-4835-A0F7-FE741A386E36}]
         Report SPI_E_UNINIT error
        [/cover] */
        Spi_lReportError(ApiId, SPI_E_UNINIT);
      }
    }
    #else
    UNUSED_PARAMETER(ApiId);
    UNUSED_PARAMETER(DetRaise);
    #endif
  }
  return RetVal;
}

/*******************************************************************************
** Traceability     : [cover parentID={D5F9304E-E7D3-4846-8025-5D813ADF3E78}] **
** Syntax          : static void Spi_lCoreInit(const uint32 CoreId)           **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non reentrant                                            **
**                                                                            **
** Parameters (in) : Coreid : ID of the corresponding core                    **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : This function initializes the pointers of RAM variable   **
**  such as Job Queue and Internal buffer based on specific QSPI configured   **
*******************************************************************************/
static void Spi_lCoreInit(const uint32 CoreId)
{
  /* [cover parentID={558830A7-6750-4b4c-8530-61706BC1C3A3}][/cover] */
  /* Initialize the core-x run-time variables */
  /* Reset all core variables to "0" */
  /* Set the core status to IDLE */
  switch(CoreId)
  {
    case CORE0:
      #if defined (SPI_CORE0_ENABLE)
      #if (SPI_CORE0_ENABLE == STD_ON)
      Spi_RuntimeCoreVar[CoreId] = &Spi_RuntimeCore0Var;
      Spi_RuntimeCoreVar[CoreId]->KernelLock = 0;
      Spi_RuntimeCoreVar[CoreId]->ChannelBufPointers = Spi_BufferCore0;
      Spi_lClearMem((uint8*)Spi_BufferCore0, sizeof(Spi_BufferCore0));
      #if ((SPI_NUM_IB_CHANNELS_CORE0) > 0U)
      Spi_RuntimeCoreVar[CoreId]->TxBuffer = Spi_TxIBBufferCore0;
      Spi_RuntimeCoreVar[CoreId]->RxBuffer = Spi_RxIBBufferCore0;
      Spi_lClearMem((uint8*)Spi_TxIBBufferCore0, sizeof(Spi_TxIBBufferCore0));
      Spi_lClearMem((uint8*)Spi_RxIBBufferCore0, sizeof(Spi_RxIBBufferCore0));
      #else
      Spi_RuntimeCoreVar[CoreId]->TxBuffer = NULL_PTR;
      Spi_RuntimeCoreVar[CoreId]->RxBuffer = NULL_PTR;
      #endif
      Spi_RuntimeCoreVar[CoreId]->SeqStatus = Spi_SequenceStatusCore0;
      Spi_RuntimeCoreVar[CoreId]->JobStatus = Spi_JobStatusCore0;
      Spi_lClearMem((uint8*)Spi_SequenceStatusCore0,
                                 sizeof(Spi_SequenceStatusCore0));
      Spi_lClearMem((uint8*)Spi_JobStatusCore0, sizeof(Spi_JobStatusCore0));
      #endif
      #endif
      break;

    case CORE1:
      #if defined (SPI_CORE1_ENABLE)
      #if (SPI_CORE1_ENABLE == STD_ON)
      Spi_RuntimeCoreVar[CoreId] = &Spi_RuntimeCore1Var;
      Spi_RuntimeCoreVar[CoreId]->KernelLock = 0;
      Spi_RuntimeCoreVar[CoreId]->ChannelBufPointers = Spi_BufferCore1;
      Spi_lClearMem((uint8*)Spi_BufferCore1, sizeof(Spi_BufferCore1));
      #if ((SPI_NUM_IB_CHANNELS_CORE1) > 0U)
      Spi_RuntimeCoreVar[CoreId]->TxBuffer = Spi_TxIBBufferCore1;
      Spi_RuntimeCoreVar[CoreId]->RxBuffer = Spi_RxIBBufferCore1;
      Spi_lClearMem((uint8*)Spi_TxIBBufferCore1, sizeof(Spi_TxIBBufferCore1));
      Spi_lClearMem((uint8*)Spi_RxIBBufferCore1, sizeof(Spi_RxIBBufferCore1));
      #else
      Spi_RuntimeCoreVar[CoreId]->TxBuffer = NULL_PTR;
      Spi_RuntimeCoreVar[CoreId]->RxBuffer = NULL_PTR;
      #endif
      Spi_RuntimeCoreVar[CoreId]->SeqStatus = Spi_SequenceStatusCore1;
      Spi_RuntimeCoreVar[CoreId]->JobStatus = Spi_JobStatusCore1;
      Spi_lClearMem((uint8*)Spi_SequenceStatusCore1,
                             sizeof(Spi_SequenceStatusCore1));
      Spi_lClearMem((uint8*)Spi_JobStatusCore1, sizeof(Spi_JobStatusCore1));
      #endif
      #endif
      break;

    case CORE2:
      #if defined (SPI_CORE2_ENABLE)
      #if (SPI_CORE2_ENABLE == STD_ON)
      Spi_RuntimeCoreVar[CoreId] = &Spi_RuntimeCore2Var;
      Spi_RuntimeCoreVar[CoreId]->KernelLock = 0;
      Spi_RuntimeCoreVar[CoreId]->ChannelBufPointers = Spi_BufferCore2;
      Spi_lClearMem((uint8*)Spi_BufferCore2, sizeof(Spi_BufferCore2));
      #if ((SPI_NUM_IB_CHANNELS_CORE2) > 0U)
      Spi_RuntimeCoreVar[CoreId]->TxBuffer = Spi_TxIBBufferCore2;
      Spi_RuntimeCoreVar[CoreId]->RxBuffer = Spi_RxIBBufferCore2;
      Spi_lClearMem((uint8*)Spi_TxIBBufferCore2, sizeof(Spi_TxIBBufferCore2));
      Spi_lClearMem((uint8*)Spi_RxIBBufferCore2, sizeof(Spi_RxIBBufferCore2));
      #else
      Spi_RuntimeCoreVar[CoreId]->TxBuffer = NULL_PTR;
      Spi_RuntimeCoreVar[CoreId]->RxBuffer = NULL_PTR;
      #endif
      Spi_RuntimeCoreVar[CoreId]->SeqStatus = Spi_SequenceStatusCore2;
      Spi_RuntimeCoreVar[CoreId]->JobStatus = Spi_JobStatusCore2;
      Spi_lClearMem((uint8*)Spi_SequenceStatusCore2,
                              sizeof(Spi_SequenceStatusCore2));
      Spi_lClearMem((uint8*)Spi_JobStatusCore2, sizeof(Spi_JobStatusCore2));
      #endif
      #endif
      break;

    case CORE3:
      #if defined (SPI_CORE3_ENABLE)
      #if (SPI_CORE3_ENABLE == STD_ON)
      Spi_RuntimeCoreVar[CoreId] = &Spi_RuntimeCore3Var;
      Spi_RuntimeCoreVar[CoreId]->KernelLock = 0;
      Spi_RuntimeCoreVar[CoreId]->ChannelBufPointers = Spi_BufferCore3;
      Spi_lClearMem((uint8*)Spi_BufferCore3, sizeof(Spi_BufferCore3));
      #if ((SPI_NUM_IB_CHANNELS_CORE3) > 0U)
      Spi_RuntimeCoreVar[CoreId]->TxBuffer = Spi_TxIBBufferCore3;
      Spi_RuntimeCoreVar[CoreId]->RxBuffer = Spi_RxIBBufferCore3;
      Spi_lClearMem((uint8*)Spi_TxIBBufferCore3, sizeof(Spi_TxIBBufferCore3));
      Spi_lClearMem((uint8*)Spi_RxIBBufferCore3, sizeof(Spi_RxIBBufferCore3));
      #else
      Spi_RuntimeCoreVar[CoreId]->TxBuffer = NULL_PTR;
      Spi_RuntimeCoreVar[CoreId]->RxBuffer = NULL_PTR;
      #endif
      Spi_RuntimeCoreVar[CoreId]->SeqStatus = Spi_SequenceStatusCore3;
      Spi_RuntimeCoreVar[CoreId]->JobStatus = Spi_JobStatusCore3;
      Spi_lClearMem((uint8*)Spi_SequenceStatusCore3,
                               sizeof(Spi_SequenceStatusCore3));
      Spi_lClearMem((uint8*)Spi_JobStatusCore3, sizeof(Spi_JobStatusCore3));
      #endif
      #endif
      break;

    case CORE4:
      #if defined (SPI_CORE4_ENABLE)
      #if (SPI_CORE4_ENABLE == STD_ON)
      Spi_RuntimeCoreVar[CoreId] = &Spi_RuntimeCore4Var;
      Spi_RuntimeCoreVar[CoreId]->KernelLock = 0;
      Spi_RuntimeCoreVar[CoreId]->ChannelBufPointers = Spi_BufferCore4;
      Spi_lClearMem((uint8*)Spi_BufferCore4, sizeof(Spi_BufferCore4));
      #if ((SPI_NUM_IB_CHANNELS_CORE4) > 0U)
      Spi_RuntimeCoreVar[CoreId]->TxBuffer = Spi_TxIBBufferCore4;
      Spi_RuntimeCoreVar[CoreId]->RxBuffer = Spi_RxIBBufferCore4;
      Spi_lClearMem((uint8*)Spi_TxIBBufferCore4, sizeof(Spi_TxIBBufferCore4));
      Spi_lClearMem((uint8*)Spi_RxIBBufferCore4, sizeof(Spi_RxIBBufferCore4));
      #else
      Spi_RuntimeCoreVar[CoreId]->TxBuffer = NULL_PTR;
      Spi_RuntimeCoreVar[CoreId]->RxBuffer = NULL_PTR;
      #endif
      Spi_RuntimeCoreVar[CoreId]->SeqStatus = Spi_SequenceStatusCore4;
      Spi_RuntimeCoreVar[CoreId]->JobStatus = Spi_JobStatusCore4;
      Spi_lClearMem((uint8*)Spi_SequenceStatusCore4,
                              sizeof(Spi_SequenceStatusCore4));
      Spi_lClearMem((uint8*)Spi_JobStatusCore4, sizeof(Spi_JobStatusCore4));
      #endif
      #endif
      break;

      #ifdef SPI_CORE5_ENABLE
      #if defined (SPI_CORE5_ENABLE)
    case CORE5:
      #if (SPI_CORE5_ENABLE == STD_ON)
      Spi_RuntimeCoreVar[CoreId] = &Spi_RuntimeCore5Var;
      Spi_RuntimeCoreVar[CoreId]->KernelLock = 0;
      Spi_RuntimeCoreVar[CoreId]->ChannelBufPointers = Spi_BufferCore5;
      Spi_lClearMem((uint8*)Spi_BufferCore5, sizeof(Spi_BufferCore5));
      #if ((SPI_NUM_IB_CHANNELS_CORE5) > 0U)
      Spi_RuntimeCoreVar[CoreId]->TxBuffer = Spi_TxIBBufferCore5;
      Spi_RuntimeCoreVar[CoreId]->RxBuffer = Spi_RxIBBufferCore5;
      Spi_lClearMem((uint8*)Spi_TxIBBufferCore5, sizeof(Spi_TxIBBufferCore5));
      Spi_lClearMem((uint8*)Spi_RxIBBufferCore5, sizeof(Spi_RxIBBufferCore5));
      #else
      Spi_RuntimeCoreVar[CoreId]->TxBuffer = NULL_PTR;
      Spi_RuntimeCoreVar[CoreId]->RxBuffer = NULL_PTR;
      #endif
      Spi_RuntimeCoreVar[CoreId]->SeqStatus = Spi_SequenceStatusCore5;
      Spi_RuntimeCoreVar[CoreId]->JobStatus = Spi_JobStatusCore5;
      Spi_lClearMem((uint8*)Spi_SequenceStatusCore5,
                               sizeof(Spi_SequenceStatusCore5));
      Spi_lClearMem((uint8*)Spi_JobStatusCore5, sizeof(Spi_JobStatusCore5));
      #endif
      break;
      #endif
      #endif

    default: /* default case */
      break;
  }
}

/*******************************************************************************
** Traceability     : [cover parentID={414C89D1-F8B0-432f-A268-C2BDA20E7DA0}] **
** Syntax          : static uint8 Spi_lGetTotalIBChannelsInCore               **
**                   (const uint32 CoreId)                                    **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non reentrant                                            **
**                                                                            **
** Parameters (in) : CoreId - Core id.                                        **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : returns the total number of IB per core                  **
**                                                                            **
** Description     : Returns the total IB channels assigned in core.          **
*******************************************************************************/
static uint8 Spi_lGetTotalIBChannelsInCore(const uint32 CoreId)
{
  uint8 TotalIbChannels = 0;

  switch(CoreId)
  {
      #if (SPI_CORE0_ENABLE == STD_ON)
    case CORE0:
      TotalIbChannels = SPI_NUM_IB_CHANNELS_CORE0;
      break;
      #endif
      #ifdef SPI_CORE1_ENABLE
      #if (SPI_CORE1_ENABLE == STD_ON)
    case CORE1:
      TotalIbChannels = SPI_NUM_IB_CHANNELS_CORE1;
      break;
      #endif
      #endif
      #ifdef SPI_CORE2_ENABLE
      #if (SPI_CORE2_ENABLE == STD_ON)
    case CORE2:
      TotalIbChannels = SPI_NUM_IB_CHANNELS_CORE2;
      break;
      #endif
      #endif
      #ifdef SPI_CORE3_ENABLE
      #if (SPI_CORE3_ENABLE == STD_ON)
    case CORE3:
      TotalIbChannels = SPI_NUM_IB_CHANNELS_CORE3;
      break;
      #endif
       #endif

      #ifdef SPI_CORE4_ENABLE
      #if (SPI_CORE4_ENABLE == STD_ON)
    case CORE4:
      TotalIbChannels = SPI_NUM_IB_CHANNELS_CORE4;
      break;
      #endif
      #endif

      #ifdef SPI_CORE5_ENABLE
      #if (SPI_CORE5_ENABLE == STD_ON)
    case CORE5:
      TotalIbChannels = SPI_NUM_IB_CHANNELS_CORE5;
      break;
      #endif
      #endif

    default:
      /* Default case */
      break;
  }
  return TotalIbChannels;
}

/*******************************************************************************
** Traceability     : [cover parentID={6D792DCC-A1A8-48e1-9A3C-257C74FFBBF1}] **
** Syntax          : static void Spi_lAsyncInitPtrRuntimeVar                  **
**                   (const uint8 Hwkernel)                                   **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non reentrant                                            **
**                                                                            **
** Parameters (in) : Hwkernel - QSPI HW kernel to be updated with.            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : Initialize the run-time variables for asynchronous       **
**                   kernels. Resets all the kernel variables like JobQueue,  **
**                   TCS to and sets the kernel status to "IDLE"              **
*******************************************************************************/
static void Spi_lAsyncInitPtrRuntimeVar(const uint8 Hwkernel)
{
  /* Initialize the kernel-x run-time variables for Aync kernels */
  /* Reset all kernel variables to "0" */
  /* Set the kernel status to IDLE */
  switch(Hwkernel)
  {
    case SPI_KERNEL0:
      #if(SPI_HW_QSPI0_USED == STD_ON)
      Spi_RuntimeKernelVar[Hwkernel] = &Spi_RuntimeKernelQSPI0;
    #if(SPI_QSPI0_HWTYPE == SPI_ASYNC_BUS)
      Spi_RuntimeKernelVar[Hwkernel]->JobQueuePtr = &Spi_JobQueueQSPI0;
      Spi_RuntimeKernelVar[Hwkernel]->JobQueuePtr->JobAndSeqQueuePtr =
        Spi_JobAndSeqQueueQSPI0;
      Spi_RuntimeKernelVar[Hwkernel]->JobQueuePtr->
      JobAndSeqQueueRearrangePtr = Spi_JobAndSeqQueueRearrangeQSPI0;
      Spi_RuntimeKernelVar[Hwkernel]->JobQueuePtr->DmaTxTCSPtr =
        Spi_DmaTxControlSetArrayQSPI0;
      Spi_RuntimeKernelVar[Hwkernel]->JobQueuePtr->DmaRxTCSPtr =
        Spi_DmaRxControlSetArrayQSPI0;

      Spi_RuntimeKernelVar[Hwkernel]->BaconChannelArray = Spi_Qspi0Bacon;

      for(uint32 index = 0; index < SPI_JOB_QUEUE_LENGTH_QSPI0; index++)
      {
        Spi_JobAndSeqQueueQSPI0[index].QueueJobId = 0;
        Spi_JobAndSeqQueueQSPI0[index].JobProperty = SPI_SEQUENCE_DELIMITER;
      }

      Spi_lClearMem((uint8*)Spi_JobAndSeqQueueRearrangeQSPI0,
                   sizeof(Spi_JobAndSeqQueueRearrangeQSPI0));
      Spi_lClearMem((uint8*)Spi_DmaTxControlSetArrayQSPI0,
                   sizeof(Spi_DmaTxControlSetArrayQSPI0));
      Spi_lClearMem((uint8*)Spi_DmaRxControlSetArrayQSPI0,
                   sizeof(Spi_DmaRxControlSetArrayQSPI0));
      #endif
      #endif
      break;
    case SPI_KERNEL1:
      #if(SPI_HW_QSPI1_USED == STD_ON)
    Spi_RuntimeKernelVar[Hwkernel] = &Spi_RuntimeKernelQSPI1;
      #if(SPI_QSPI1_HWTYPE == SPI_ASYNC_BUS)
      Spi_RuntimeKernelVar[Hwkernel]->JobQueuePtr = &Spi_JobQueueQSPI1;
      Spi_RuntimeKernelVar[Hwkernel]->JobQueuePtr->JobAndSeqQueuePtr =
        Spi_JobAndSeqQueueQSPI1;
      Spi_RuntimeKernelVar[Hwkernel]->JobQueuePtr->
      JobAndSeqQueueRearrangePtr = Spi_JobAndSeqQueueRearrangeQSPI1;
      Spi_RuntimeKernelVar[Hwkernel]->JobQueuePtr->DmaTxTCSPtr =
        Spi_DmaTxControlSetArrayQSPI1;
      Spi_RuntimeKernelVar[Hwkernel]->JobQueuePtr->DmaRxTCSPtr =
        Spi_DmaRxControlSetArrayQSPI1;

      Spi_RuntimeKernelVar[Hwkernel]->BaconChannelArray = Spi_Qspi1Bacon;

      for(uint32 index = 0; index < SPI_JOB_QUEUE_LENGTH_QSPI1; index++)
      {
        Spi_JobAndSeqQueueQSPI1[index].QueueJobId = 0;
        Spi_JobAndSeqQueueQSPI1[index].JobProperty = SPI_SEQUENCE_DELIMITER;
      }

      Spi_lClearMem((uint8*)Spi_JobAndSeqQueueRearrangeQSPI1,
                   sizeof(Spi_JobAndSeqQueueRearrangeQSPI1));
      Spi_lClearMem((uint8*)Spi_DmaTxControlSetArrayQSPI1,
                   sizeof(Spi_DmaTxControlSetArrayQSPI1));
      Spi_lClearMem((uint8*)Spi_DmaRxControlSetArrayQSPI1,
                   sizeof(Spi_DmaRxControlSetArrayQSPI1));
      #endif
      #endif
      break;
    case SPI_KERNEL2:
      #if(SPI_HW_QSPI2_USED == STD_ON)
     Spi_RuntimeKernelVar[Hwkernel] = &Spi_RuntimeKernelQSPI2;
      #if (SPI_QSPI2_HWTYPE == SPI_ASYNC_BUS)
      Spi_RuntimeKernelVar[Hwkernel]->JobQueuePtr =
        &Spi_JobQueueQSPI2;
      Spi_RuntimeKernelVar[Hwkernel]->JobQueuePtr->JobAndSeqQueuePtr =
        Spi_JobAndSeqQueueQSPI2;
      Spi_RuntimeKernelVar[Hwkernel]->JobQueuePtr->
      JobAndSeqQueueRearrangePtr = Spi_JobAndSeqQueueRearrangeQSPI2;
      Spi_RuntimeKernelVar[Hwkernel]->JobQueuePtr->DmaTxTCSPtr =
        Spi_DmaTxControlSetArrayQSPI2;
      Spi_RuntimeKernelVar[Hwkernel]->JobQueuePtr->DmaRxTCSPtr =
        Spi_DmaRxControlSetArrayQSPI2;

      Spi_RuntimeKernelVar[Hwkernel]->BaconChannelArray = Spi_Qspi2Bacon;

      for(uint32 index = 0; index < SPI_JOB_QUEUE_LENGTH_QSPI2; index++)
      {
        Spi_JobAndSeqQueueQSPI2[index].QueueJobId = 0;
        Spi_JobAndSeqQueueQSPI2[index].JobProperty = SPI_SEQUENCE_DELIMITER;
      }

      Spi_lClearMem((uint8*)Spi_JobAndSeqQueueRearrangeQSPI2,
                   sizeof(Spi_JobAndSeqQueueRearrangeQSPI2));
      Spi_lClearMem((uint8*)Spi_DmaTxControlSetArrayQSPI2,
                   sizeof(Spi_DmaTxControlSetArrayQSPI2));
      Spi_lClearMem((uint8*)Spi_DmaRxControlSetArrayQSPI2,
                   sizeof(Spi_DmaRxControlSetArrayQSPI2));
      #endif
      #endif
      break;
    case SPI_KERNEL3:
      #if(SPI_HW_QSPI3_USED == STD_ON)
    Spi_RuntimeKernelVar[Hwkernel] = &Spi_RuntimeKernelQSPI3;
      #if (SPI_QSPI3_HWTYPE == SPI_ASYNC_BUS)
      Spi_RuntimeKernelVar[Hwkernel]->JobQueuePtr = &Spi_JobQueueQSPI3;
      Spi_RuntimeKernelVar[Hwkernel]->JobQueuePtr->JobAndSeqQueuePtr =
        Spi_JobAndSeqQueueQSPI3;
      Spi_RuntimeKernelVar[Hwkernel]->JobQueuePtr->
      JobAndSeqQueueRearrangePtr = Spi_JobAndSeqQueueRearrangeQSPI3;
      Spi_RuntimeKernelVar[Hwkernel]->JobQueuePtr->DmaTxTCSPtr =
        Spi_DmaTxControlSetArrayQSPI3;
      Spi_RuntimeKernelVar[Hwkernel]->JobQueuePtr->DmaRxTCSPtr =
        Spi_DmaRxControlSetArrayQSPI3;

      Spi_RuntimeKernelVar[Hwkernel]->BaconChannelArray = Spi_Qspi3Bacon;

      for(uint32 index = 0; index < SPI_JOB_QUEUE_LENGTH_QSPI3; index++)
      {
        Spi_JobAndSeqQueueQSPI3[index].QueueJobId = 0;
        Spi_JobAndSeqQueueQSPI3[index].JobProperty = SPI_SEQUENCE_DELIMITER;
      }
      Spi_lClearMem((uint8*)Spi_JobAndSeqQueueRearrangeQSPI3,
                   sizeof(Spi_JobAndSeqQueueRearrangeQSPI3));
      Spi_lClearMem((uint8*)Spi_DmaTxControlSetArrayQSPI3,
                   sizeof(Spi_DmaTxControlSetArrayQSPI3));
      Spi_lClearMem((uint8*)Spi_DmaRxControlSetArrayQSPI3,
                   sizeof(Spi_DmaRxControlSetArrayQSPI3));
      #endif
      #endif
      break;
      #ifdef SPI_HW_QSPI4_USED
      #if(SPI_HW_QSPI4_USED == STD_ON)
    case SPI_KERNEL4:
      Spi_RuntimeKernelVar[Hwkernel] = &Spi_RuntimeKernelQSPI4;
      #if (SPI_QSPI4_HWTYPE == SPI_ASYNC_BUS)
      Spi_RuntimeKernelVar[Hwkernel]->JobQueuePtr = &Spi_JobQueueQSPI4;
      Spi_RuntimeKernelVar[Hwkernel]->JobQueuePtr->JobAndSeqQueuePtr = \
          Spi_JobAndSeqQueueQSPI4;
      Spi_RuntimeKernelVar[Hwkernel]->JobQueuePtr->                   \
      JobAndSeqQueueRearrangePtr = Spi_JobAndSeqQueueRearrangeQSPI4;
      Spi_RuntimeKernelVar[Hwkernel]->JobQueuePtr->DmaTxTCSPtr =      \
          Spi_DmaTxControlSetArrayQSPI4;
      Spi_RuntimeKernelVar[Hwkernel]->JobQueuePtr->DmaRxTCSPtr =      \
          Spi_DmaRxControlSetArrayQSPI4;

      Spi_RuntimeKernelVar[Hwkernel]->BaconChannelArray = Spi_Qspi4Bacon;

      for(uint32 index = 0; index < SPI_JOB_QUEUE_LENGTH_QSPI4; index++)
      {
        Spi_JobAndSeqQueueQSPI4[index].QueueJobId = 0;
        Spi_JobAndSeqQueueQSPI4[index].JobProperty = SPI_SEQUENCE_DELIMITER;
      }
      Spi_lClearMem((uint8*)Spi_JobAndSeqQueueRearrangeQSPI4,                \
                   sizeof(Spi_JobAndSeqQueueRearrangeQSPI4));
      Spi_lClearMem((uint8*)Spi_DmaTxControlSetArrayQSPI4,                   \
                   sizeof(Spi_DmaTxControlSetArrayQSPI4));
      Spi_lClearMem((uint8*)Spi_DmaRxControlSetArrayQSPI4,                   \
                   sizeof(Spi_DmaRxControlSetArrayQSPI4));
      #endif
      break;
      #endif
      #endif

      #ifdef SPI_HW_QSPI5_USED
      #if(SPI_HW_QSPI5_USED == STD_ON)
    case SPI_KERNEL5:
      Spi_RuntimeKernelVar[Hwkernel] = &Spi_RuntimeKernelQSPI5;
      #if (SPI_QSPI5_HWTYPE == SPI_ASYNC_BUS)
      Spi_RuntimeKernelVar[Hwkernel]->JobQueuePtr = &Spi_JobQueueQSPI5;
      Spi_RuntimeKernelVar[Hwkernel]->JobQueuePtr->JobAndSeqQueuePtr = \
          Spi_JobAndSeqQueueQSPI5;
      Spi_RuntimeKernelVar[Hwkernel]->JobQueuePtr->                   \
      JobAndSeqQueueRearrangePtr = Spi_JobAndSeqQueueRearrangeQSPI5;
      Spi_RuntimeKernelVar[Hwkernel]->JobQueuePtr->DmaTxTCSPtr =      \
          Spi_DmaTxControlSetArrayQSPI5;
      Spi_RuntimeKernelVar[Hwkernel]->JobQueuePtr->DmaRxTCSPtr =      \
          Spi_DmaRxControlSetArrayQSPI5;

      Spi_RuntimeKernelVar[Hwkernel]->BaconChannelArray = Spi_Qspi5Bacon;

      for(uint32 index = 0; index < SPI_JOB_QUEUE_LENGTH_QSPI5; index++)
      {
        Spi_JobAndSeqQueueQSPI5[index].QueueJobId = 0;
        Spi_JobAndSeqQueueQSPI5[index].JobProperty = SPI_SEQUENCE_DELIMITER;
      }
      Spi_lClearMem((uint8*)Spi_JobAndSeqQueueRearrangeQSPI5,                \
                   sizeof(Spi_JobAndSeqQueueRearrangeQSPI5));
      Spi_lClearMem((uint8*)Spi_DmaTxControlSetArrayQSPI5,                   \
                   sizeof(Spi_DmaTxControlSetArrayQSPI5));
      Spi_lClearMem((uint8*)Spi_DmaRxControlSetArrayQSPI5,                   \
                   sizeof(Spi_DmaRxControlSetArrayQSPI5));
      #endif
      break;
      #endif
      #endif

    default: /* default case */
      break;
  }
}


#if(SPI_LEVEL_DELIVERED != 0U)
/*******************************************************************************
** Traceability     : [cover parentID={1CBE3585-4483-4fe6-A63C-83BB735C9B35}] **
** Syntax          : static Std_ReturnType Spi_lIsQSPIHwConfiguredAsync       **
**                                               (const uint8 HwModule)       **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : HwModule - QSPI Index                                    **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK - QSPI Hw is present and is Async                  **
**                    E_NOT_OK - Qspi Hw is either not defined or is Sync     **
**                                                                            **
** Description     : This function checks if the QSPI module is configure     **
**                              and is used as asynchronous                   **
*******************************************************************************/
static Std_ReturnType Spi_lIsQSPIHwConfiguredAsync(const uint8 HwModule)
{
  /* Get core information */
  Std_ReturnType RetVal = E_NOT_OK;
  const Spi_CoreConfigType *CoreConfigPtr =
    Spi_kGlobalConfigPtr->CoreConfigPtr[Mcal_GetCpuIndex()];
  Spi_QSPIHwMapConfigType HWType = (CoreConfigPtr->QSPIHwMap);
  HWType = HWType >> ((Spi_QSPIHwMapConfigType)HwModule *                      \
                  (Spi_QSPIHwMapConfigType)SPI_TOTAL_KERNEL_TYPE_BITS);
  HWType = HWType & (Spi_QSPIHwMapConfigType)SPI_KERNEL_TYPE_MASK;

  /* [cover parentID={E27EC4C8-09AD-4238-8269-1D5EB31E8A13}] Check
  if sync / async kernel[/cover] */
  /* Check if kernel is assigned for Sync sequence transmission if so
      update status as E_NOT_OK */
  if((Spi_QSPIHwMapConfigType)SPI_ASYNC_KERNEL == HWType)
  {
    RetVal = E_OK;
  }
  /* Return status */
  return RetVal;
} /* End of function Spi_lIsQSPIHwConfiguredAsync */
#endif /* SPI_LEVEL_DELIVERED != 0U */

#if(SPI_LEVEL_DELIVERED != 1U)
/*******************************************************************************
** Traceability     : [cover parentID={3296AF0D-C731-4694-A449-C07E9251A312}] **
** Syntax          : static Std_ReturnType Spi_lIsQSPIHwConfiguredSync        **
**                                               (const uint8 HwModule)       **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : HwModule - QSPI Index                                    **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK - QSPI Hw is present and is Sync                   **
**                    E_NOT_OK - Qspi Hw is either not defined or is Async    **
**                                                                            **
** Description     : This function checks if the QSPI module is configure     **
**                              and is used as synchronous                    **
*******************************************************************************/
static Std_ReturnType Spi_lIsQSPIHwConfiguredSync(const uint8 HwModule)
{
  /* Get core information */
  Std_ReturnType RetVal = E_NOT_OK;
  Spi_QSPIHwMapConfigType HWType = 0;
  const Spi_CoreConfigType *CoreConfigPtr =
    Spi_kGlobalConfigPtr->CoreConfigPtr[Mcal_GetCpuIndex()];
  HWType = (CoreConfigPtr->QSPIHwMap);
  HWType = HWType >> ((Spi_QSPIHwMapConfigType)HwModule *                      \
                  (Spi_QSPIHwMapConfigType)SPI_TOTAL_KERNEL_TYPE_BITS);

  /* [cover parentID={DC641145-BD34-4ccf-85D7-5EFD1D38D7B5}] Check
  if sync / async kernel[/cover] */
  HWType = HWType & (Spi_QSPIHwMapConfigType)SPI_KERNEL_TYPE_MASK;
  /* Check if kernel is assigned for Async sequence transmission if so
      update status as E_NOT_OK */
  if((Spi_QSPIHwMapConfigType)SPI_SYNC_KERNEL == HWType)
  {
    RetVal = E_OK;
  }

  return RetVal;
} /* End of function Spi_lIsQSPIHwConfiguredSync */
#endif /* SPI_LEVEL_DELIVERED != 1U */


/*******************************************************************************
** Traceability     : [cover parentID={1FB24C9B-F815-4a35-81BC-CEF15D52C3E3}] **
** Syntax          : static Std_ReturnType Spi_lIsQSPIHwConfigured            **
**                                               (const uint8 HwModule)       **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : HwModule - QSPI Index                                    **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK - QSPI Hw is present                               **
**                    E_NOT_OK - Qspi Hw is  not defined                      **
**                                                                            **
** Description     : This function checks if the QSPI module is configure     **
*******************************************************************************/
static Std_ReturnType Spi_lIsQSPIHwConfigured(const uint8 HwModule)
{
  Std_ReturnType RetVal = E_NOT_OK;

  /* [cover parentID={1AB9562C-46FB-4fe1-B2D4-ECDA44FB7889}] Level 0 checks
  [/cover] */
  #if(SPI_LEVEL_DELIVERED == 0U)
  if(Spi_lIsQSPIHwConfiguredSync(HwModule) == (uint8)E_OK)

    /* [cover parentID={1668D229-D960-4db9-BB6C-B1375F8B6C85}] Level 1 checks
     [/cover] */
#elif(SPI_LEVEL_DELIVERED == 1U)
    if(Spi_lIsQSPIHwConfiguredAsync(HwModule) == (uint8)E_OK)
  #else

  /* [cover parentID={0CB468D5-5805-4268-B392-D09293497564}] Level 2 checks
  [/cover] */
  Std_ReturnType RetVal1 = Spi_lIsQSPIHwConfiguredSync(HwModule);
  if((Spi_lIsQSPIHwConfiguredAsync(HwModule) == (uint8)E_OK) ||               \
      (RetVal1 == (uint8)E_OK))
  #endif
    {
      RetVal = E_OK;
    }
  return RetVal;
} /* End of function Spi_lIsQSPIHwConfigured */

/*******************************************************************************
** Traceability     : [cover parentID={BBC4509F-E4E2-437f-9DD4-A0A803994F8F}] **
** Syntax          : static void Spi_ClearMem(uint8 *const BufferPtr,         **
**                                  const uint32 BufferSize)                  **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : BufferPtr   -  Pointer to buffer to clear                **
**                   BufferSize  -  Size of buffer to be cleared              **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : Clears the memory by writing "Zero"                      **
*******************************************************************************/
static void Spi_lClearMem(uint8 *const BufferPtr, const uint32 BufferSize)
{
  /* Loop through all elements passed */
  /* Clear the value in pointer */
  uint32 LoopCount;
  for(LoopCount = 0; LoopCount < BufferSize; LoopCount++)
  {
    BufferPtr[LoopCount] = 0x00U;
  }
}

#if(SPI_LEVEL_DELIVERED != 0U)
/*******************************************************************************
** Traceability     : [cover parentID={C364D89F-AFA8-4aaa-8FC2-EC48AAEF6FF1}] **
** Syntax          : static void Spi_lResetAsyncQueueVar(const uint8 ModIndex)**
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : ModIndex :  QSPI HW index                                **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : Resets the global Queue variables                        **
*******************************************************************************/
static void Spi_lResetAsyncQueueVar(const uint8 ModIndex)
{
  /* Clear kernel specific Queue variables */
  if(Spi_RuntimeKernelVar[ModIndex]->JobQueuePtr != NULL_PTR)
  {
    Spi_RuntimeKernelVar[ModIndex]->JobQueuePtr->QueueStartIndex = 0U;
    Spi_RuntimeKernelVar[ModIndex]->JobQueuePtr->QueueEndIndex = 0U;
    Spi_RuntimeKernelVar[ModIndex]->JobQueuePtr->
    CurrentChannelIndex = 0U;
    Spi_RuntimeKernelVar[ModIndex]->JobQueuePtr->CurrentJobIndex = 0U;
  }
} /* End of function Spi_lResetAsyncQueueVar */
#endif /* SPI_LEVEL_DELIVERED != 0U */

/*******************************************************************************
** Traceability     : [cover parentID={A35AF310-7D14-4349-BD8E-D21138B3736B}] **
** Syntax          : static void Spi_lQSPIHwResetInit(const uint8 ModIndex)   **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : ModIndex - QSPI Hw index                                 **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : This function initialize the SFR related to              **
**       QSPI indexed by the ModIndex. Initializes CLC, PISEL, GLOBALCON and  **
**                 SSOC SFRs for QSPI[ModIndex] with the RESET values of SFR  **
*******************************************************************************/
static void Spi_lQSPIHwResetInit(const uint8 ModIndex)
{
  uint8 LoopIndex;
  /* [cover parentID={D4952204-41F1-4bdb-8F70-B58FE0B6DB5B}][/cover] */
  /* Clear all these registers of QSPI kernel to POR values -
   * PISEL, GLOBALCON, GLOBALCON1, ECON and FLAGSCLEAR */

   /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
   effects foreseen by violating this MISRA rule, as the pointer
   to the object type that it is getting cast into, is a known type. */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
   * effects foreseen by violating this MISRA rule. */
  SPI_SFR_INIT_DEINIT_WRITE32(&SPI_HW_MODULE[ModIndex].PISEL.U, \
                   SPI_PISEL_RST_VAL);

   /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access.
   No side effects foreseen by violating this MISRA rule, as the pointer
   to the object type that it is getting cast into, is a known type. */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
   * effects foreseen by violating this MISRA rule. */
  SPI_SFR_INIT_DEINIT_WRITE32(&SPI_HW_MODULE[ModIndex].GLOBALCON.U, \
                   SPI_GLOBALCON_RST_VAL);

   /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
   effects foreseen by violating this MISRA rule, as the pointer
   to the object type that it is getting cast into, is a known type. */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
   * effects foreseen by violating this MISRA rule. */
  SPI_SFR_INIT_DEINIT_WRITE32(&SPI_HW_MODULE[ModIndex].GLOBALCON1.U, \
              SPI_GLOBALCON1_RST_VAL);

  for(LoopIndex = 0U; LoopIndex < SPI_MAX_ECON_CHANNEL; LoopIndex++)
  {
     /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
     effects foreseen by violating this MISRA rule, as the pointer
     to the object type that it is getting cast into, is a known type. */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
   * effects foreseen by violating this MISRA rule. */
    SPI_SFR_INIT_DEINIT_WRITE32(&SPI_HW_MODULE[ModIndex].ECON[LoopIndex].U, \
                         SPI_ECON_RST_VAL);
  }

  /* reset the SSOC SFR */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
  effects foreseen by violating this MISRA rule, as the pointer
  to the object type that it is getting cast into, is a known type. */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
   * effects foreseen by violating this MISRA rule. */
  SPI_SFR_INIT_DEINIT_WRITE32(&SPI_HW_MODULE[ModIndex]. \
                                        SSOC.U, SPI_SSOC_RST_VAL);

  /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
  effects foreseen by violating this MISRA rule, as the pointer
  to the object type that it is getting cast into, is a known type. */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
   * effects foreseen by violating this MISRA rule. */
  SPI_HW_MODULE[ModIndex].FLAGSCLEAR.U = SPI_FLAGSCLEAR_RST_VAL;

} /* End of function Spi_lQSPIHwResetInit */

/*******************************************************************************
** Traceability     : [cover parentID={13EDCBEA-5E33-4057-A9AA-D5B810DBC936}] **
** Syntax          : static void Spi_lQSPIHwInit(const uint8 ModIndex)        **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : ModIndex - QSPI Hw index                                 **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : This function initialize the SFR related to              **
**       QSPI indexed by the ModIndex. Initializes CLC, PISEL, GLOBALCON and  **
**                 SSOC SFRs for QSPI[ModIndex]                               **
*******************************************************************************/
static void Spi_lQSPIHwInit(const uint8 ModIndex)
{
  const Spi_CoreConfigType *CoreConfigPtr =
    Spi_kGlobalConfigPtr->CoreConfigPtr[Mcal_GetCpuIndex()];

  /* Configure kernel specific HW registers */
  /* Set the MRST Pin */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
   * effects foreseen by violating this MISRA rule. */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
  effects foreseen by violating this MISRA rule, as the pointer
  to the object type that it is getting cast into, is a known type. */
  SPI_SFR_INIT_DEINIT_WRITE32(&SPI_HW_MODULE[ModIndex].\
      PISEL.U, (IFX_QSPI_PISEL_MRIS_MSK & (uint32)(CoreConfigPtr->         \
                QSPIHwConfigPtr[ModIndex]->MasterReceivePortPin)));

  /* [cover parentID={CC0D2C66-1AE7-44c7-A9CB-39EEDF879BE7}][/cover] */
  /* Set the Chip Select level */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
   * effects foreseen by violating this MISRA rule. */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
  effects foreseen by violating this MISRA rule, as the pointer
  to the object type that it is getting cast into, is a known type. */
  SPI_SFR_INIT_DEINIT_WRITE32(&SPI_HW_MODULE[ModIndex].SSOC.U, \
  (CoreConfigPtr->QSPIHwConfigPtr[ModIndex]->ActiveChipSelectLevel));

} /* End of function Spi_lQSPIHwInit */

#if(SPI_LEVEL_DELIVERED != 0U)
/*******************************************************************************
** Traceability     : [cover parentID={0506C9B7-4850-4435-BA33-FC0C1A648B36}] **
** Syntax          : static void Spi_lQSPIHwDMAInit(const uint8 ModIndex)     **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : ModIndex - QSPI Hw index                                 **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : This function initializes the global variables related   **
**     to asynchronous QSPI. It partially (rest is updated at runtime)        **
**     initializes the transaction control set needed for the                 **
**     DMA linked list implementation per QSPI module                         **
*******************************************************************************/
static void Spi_lQSPIHwDMAInit(const uint8 ModIndex)
{
  /* Get the core configuration */
  const Spi_CoreConfigType *CoreConfigPtr =
    Spi_kGlobalConfigPtr->CoreConfigPtr[Mcal_GetCpuIndex()];
  uint8 LoopIndex = 0U;
  Spi_DmaTCSType *DmaTxTcsPtr;
  Spi_DmaTCSType *DmaRxTcsPtr;
  const Spi_QueueType *JobQueuePtr;

  JobQueuePtr = Spi_RuntimeKernelVar[ModIndex]->JobQueuePtr;
  DmaTxTcsPtr = JobQueuePtr->DmaTxTCSPtr;
  DmaRxTcsPtr = JobQueuePtr->DmaRxTCSPtr;

  /* [cover parentID={2AE846EC-7AB4-483a-84A8-5A324A067E66}] For Kernels working
  in Async mode, configure the TCS destination and source address[/cover] */
  /* Traverse through all the DMA TCS */
  for(LoopIndex = 0U;                                                         \
      LoopIndex < CoreConfigPtr->QSPIHwConfigPtr[ModIndex]->DMATCSCount;  \
      LoopIndex++)
  {
    /* Update TX TCS destination address to be "QSPI TX register" */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
     * effects foreseen by violating this MISRA rule, as the pointer to
     * the object type that it is getting cast into, is a known type. */
    /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
    effects foreseen by violating this MISRA rule, as the pointer
    to the object type that it is getting cast into, is a known type. */
    DmaTxTcsPtr[LoopIndex].DmaDADR.U =                                        \
        (uint32) & (SPI_HW_MODULE[ModIndex].DATAENTRY[SPI_FIFO_ENTRY].U);

    /* Update RX TCS soruce address to be "QSPI RX register" */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
     * effects foreseen by violating this MISRA rule, as the pointer to
     * the object type that it is getting cast into, is a known type. */
    /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access.
    No side effects foreseen by violating this MISRA rule, as the pointer
    to the object type that it is getting cast into, is a known type. */
    DmaRxTcsPtr[LoopIndex].DmaSADR.U =                                        \
        (uint32)(&(SPI_HW_MODULE[ModIndex].RXEXIT.U));
  } /*for loop*/
} /* End of function Spi_lQSPIHwDMAInit */

#endif /* SPI_LEVEL_DELIVERED != 0U */

/*******************************************************************************
** Traceability     : [cover parentID={A2024C12-E5A2-4702-90B8-65A5A9E8DAF9}] **
** Syntax          : static void Spi_lInitIBBuffer(void)                      **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : This function initializes Internal bufferoffset          **
**                   for IB channels assigned to asynchronous Hw              **
*******************************************************************************/
static void Spi_lInitIBBuffer(void)
{
  /* Get the core congif */
  const Spi_ChannelConfigType *ChnlConfigPtr;
  uint8 ChannelIndex;
  uint32 CoreId = Mcal_GetCpuIndex();
  const Spi_CoreConfigType *CoreConfigPtr =
    Spi_kGlobalConfigPtr->CoreConfigPtr[CoreId];
  const Spi_DataBufferType *TxPtr =
    Spi_RuntimeCoreVar[CoreId]->TxBuffer;
  const Spi_DataBufferType *RxPtr =
    Spi_RuntimeCoreVar[CoreId]->RxBuffer;
  uint16 ChOffset = 0;

  /* [cover parentID={010C2C3D-77B8-41a5-90D6-EFBD56467CC6}][/cover] */
  /* Loop through all the channels assigned for Core */
  for(ChannelIndex = 0U; ChannelIndex < CoreConfigPtr->NoOfChannels;
      ChannelIndex++)
  {
    /* Get the channel configuration */
    ChnlConfigPtr = &(CoreConfigPtr->ChannelConfigPtr[ChannelIndex]);

    ChOffset = CoreConfigPtr->ChannelOffsetInfo[ChannelIndex].ChannelOffset;

    /* [cover parentID={4011B4E6-AA38-4de7-9476-6179FE45F2F6}][/cover] */
    /* Check if channel is IB */
    if(ChnlConfigPtr->ChannelType == SPI_IB_CHANNEL)
    {
      /* Get the source and destination locations for IB buffer */
      Spi_RuntimeCoreVar[CoreId]->
      ChannelBufPointers[ChannelIndex].SrcPtr  =
        &TxPtr[ChOffset];

      Spi_RuntimeCoreVar[CoreId]->
      ChannelBufPointers[ChannelIndex].DestPtr =
        &RxPtr[ChOffset];

      /* Update the number of elements to be transmitted in this channel */
      Spi_RuntimeCoreVar[CoreId]->
      ChannelBufPointers[ChannelIndex].TransferLength =
        ChnlConfigPtr->NoOfDataElements;
    }
  }
}

/*******************************************************************************
** Traceability     : [cover parentID={49725F3A-35AF-4718-999F-3E07B3AEACF9}] **
** Syntax          : static Std_ReturnType Spi_lIsStatusBusy                  **
**                            (const SpiCommsTypes CheckCommsType)            **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : CheckCommsType - Specifies communication type            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: Driver is BUSY,                                    **
**                   E_NOT_OK: Driver is not not BUSY                         **
**                            (either SPI_IDLE/SPI_UNINIT)                    **
**                                                                            **
** Description     : This function checks if the driver is BUSY or not        **
*******************************************************************************/
static Std_ReturnType Spi_lIsStatusBusy(const SpiCommsTypes CheckCommsType)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint8 LoopIndex = 0U;

  /* [cover parentID={AEAE5CDF-C289-48d1-A8D5-328EC69C1925}] Loop through all
  kernels to find sync and async kernels[/cover] */
  /* Loop through all the kernels */
  for(LoopIndex = 0U; LoopIndex < SPI_MAX_HW_UNIT; LoopIndex++)
  {
    /* Check if kernel is configured for comms */
    if(Spi_lIsQSPIHwConfigured(LoopIndex) == E_OK)
    {
      /* [cover parentID={6C903EC9-24EF-41ce-91D8-FF1516E8E9BB}]
           Check what type of kernel to verify [/cover] */
      /* Check if status is to be obtained for Synchronous
          kernels only */
      /* [cover parentID={6467C961-9220-4490-8246-8C54B03AD1D2}]
      Communication is for Sync or Both sync and async[/cover] */
      if(CheckCommsType == SPI_BOTH)
      {
        /* Check if the kernel is configured for Synchronous
            communication */
        /* [cover parentID={91A26392-28D2-459c-8AF6-E5E4CC5A9B83}]
        Check ststus if sync kernels[/cover] */
          /* Check if the QSPI kernel is busy transmitting */
          if(Spi_RuntimeKernelVar[LoopIndex]->KernelStatus ==
              SPI_BUSY)
          {
            /* Break if one of the kernel is busy transmitting */
            RetVal = E_OK;
          }
      }
      #if (SPI_LEVEL_DELIVERED == 2U)
      else
      {
        /* [cover parentID={509C1E7A-C933-4fed-9104-7689E05A1A2F}]
        Check status if for Async kernels[/cover] */
        /* Check if the kernel is configured for Asynchronous
        communication */
        if(Spi_lIsQSPIHwConfiguredAsync(LoopIndex) == E_OK)
        {
          /* Check if the QSPI kernel is busy transmitting */
          if(Spi_RuntimeKernelVar[LoopIndex]->AsyncComStatus ==
            SPI_BUSY)
          {
            /* Break if one of the kernel is busy transmitting */
            RetVal = E_OK;
          }
        }
      }
      #endif
      if(RetVal == E_OK)
      {
        break;
      }
    }
  }/* End of FOR loop */

  /* Retrun status */
  return RetVal;

} /* End of function Spi_lIsStatusBusy */

#if(SPI_CHANNEL_BUFFERS_ALLOWED != 1U)
/*******************************************************************************
** Traceability     : [cover parentID={57B30A42-FE26-41c3-BFF0-2665F068309C}] **
** Syntax          : static void Spi_lIBCopyData                              **
**                   (                                                        **
**                     const uint8* const SrcAddrPtr,                         **
**                     uint8* const DestAddrPtr,                              **
**                     const uint32 Length,                                   **
**                     const uint8 DataWidthAndIncrementSource                **
**                   )                                                        **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : SrcAddrPtr - Source data to be copied to                 **
**                             destination buffer                             **
**                   Length - this is the number of elements to be copied     **
**                   DataWidthAndIncrementSource-                             **
**                      (Lower nibble:                                        **
**                        1U : represents source buffer is incremented.       **
**                      0U : represents source buffer is not incremented.)    **
**                      (Upper nibble:                                        **
**                      1U : Channel datawidth configured as 8Bit.            **
**                      2U : Channel datawidth configured as 16Bit.           **
**                      4U : Channel datawidth configured as 32Bit.           **
** Parameters (out): DestAddrPtr - Points to the address to which data has    **
**                                       to be copied from source address     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : This function copies the data provided by the user to    **
**                   the internal buffer which is defined by the SPI driver   **
*******************************************************************************/
static void Spi_lIBCopyData
(
  const uint8* const SrcAddrPtr,
  uint8* const DestAddrPtr,
  const uint32 Length,
  const uint8 DataWidthAndIncrementSource
)
{
  uint32 IBEndIndex = Length;
  uint8 ChannelDataWidth = \
                  (DataWidthAndIncrementSource >> SPI_DATAWIDTH_BITS_OFFSET);
  uint8 IncrementSource = (DataWidthAndIncrementSource & (uint8)0x0F);
  uint32 counterDes = 0;
  uint32 counterSrc = 0;

  /* Loop through number of elements passed */
  do
  {
    /* Copy source to destination */
    /* Point to next location of destination */
    DestAddrPtr[counterDes] = SrcAddrPtr[counterSrc];
    counterDes++;
    /* [cover parentID={5A2E1DED-9AD3-4635-8013-C8BC84B8687B}] Check
    if source buffer to be incremented[/cover] */
    /* Check if Source has to be incremented, if so increment */
    if(IncrementSource > (uint8)0)
    {
      counterSrc++;
    }
    else
    {
      /* [cover parentID={C472B469-5181-4e0b-87FE-065F4156F319}] Default values
      copied if source is NULL[/cover] */
      /* check for 16/32bit channel data width configured */
      if ((ChannelDataWidth % 2U) == 0U)
      {
        counterSrc++;
        if (counterSrc == ChannelDataWidth)
        {
          /* Reset the counter */
          counterSrc = 0U;
        }
      }
    }
    /* Decrement the elements */
    IBEndIndex--;
    /* [cover parentID={055BB5A7-3C06-4602-878C-C213C925EE91}] ReadIB -
    Copy till last element[/cover] */
  } while (IBEndIndex > 0U); /* Exit if all elements are copied */
} /* End of function Spi_lIBCopyData */
#endif /* SPI_CHANNEL_BUFFERS_ALLOWED != 1U */

#if(SPI_LEVEL_DELIVERED != 1U)
/*******************************************************************************
** Traceability     : [cover parentID={4CDA9A1E-BE4A-4be5-BCF1-F25BFE072C0E}] **
** Syntax          : static Std_ReturnType Spi_lSyncTransmit                  **
**                     (const Spi_SeqeunceType Sequence)                      **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : Sequence - Sequence ID                                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK : When all jobs are successfully transmitted        **
**                   E_NOT_OK: When HW error occurs                           **
**                                                                            **
** Description     : This function initiates transmission at the sequence     **
**                   level. Available only for SpiLevelDelivered 0 or 2       **
*******************************************************************************/
static Std_ReturnType Spi_lSyncTransmit(const Spi_SequenceType Sequence)
{
  const Spi_SequenceConfigType* SeqConfigPtr;
  Spi_JobType JobId, JobIndex;
  Std_ReturnType RetVal = E_NOT_OK;

  /* Get the core information */
  uint32 CoreId = Mcal_GetCpuIndex();
  const Spi_CoreConfigType *CoreConfigPtr =
    Spi_kGlobalConfigPtr->CoreConfigPtr[CoreId];

  /* [cover parentID={CCBB9F04-0FE7-44ac-AC8E-74D8F59DE1B9}]
   Set the sequence status to pending while in transmissison
  [/cover] */
  Spi_RuntimeCoreVar[CoreId]->SeqStatus[Sequence] = SPI_SEQ_PENDING;

  /* Get the sequence configuration from core configuration */
  SeqConfigPtr = &CoreConfigPtr->SequenceConfigPtr[Sequence];

  /* Initialize Job Index to the first job and fetch first job */
  JobIndex = 0U;
  JobId = SeqConfigPtr->JobLinkPtrPhysical[JobIndex];

  /* [cover parentID={6D9E26DA-363B-43cf-8F20-AFA244F69400}]
  Sync transmit API - Blocking call, transmit synchronously
  [/cover] */
  /* Loop through all the jobs of sequence */
  do
  {
    /* [cover parentID={7C7B16B2-72D8-4753-AAAB-BCA22A85C11E}]
     Start transmission
    [/cover] */
    /* [cover parentID={0543A937-1622-429f-8A09-91FF4C2976FC}]
     Start job transmission
    [/cover] */
    RetVal = Spi_lSyncStartJob(JobId);

    /* [cover parentID={98521834-4FF3-4b42-9354-E6B92913733A}] Check
    if job failed - update sequence result[/cover] */
    /* Check if the Job transmission has failed due to hardware error */
    if(Spi_RuntimeCoreVar[CoreId]->JobStatus[JobId] == SPI_JOB_FAILED)
    {
      /* [cover parentID={B175779A-7F70-4db4-AA0A-06E8E9CFB63E}] Assign
      the status of sequence - SPI_SEQ_FAILED [/cover] */
      /* Assign sequence status to be failed */
      Spi_RuntimeCoreVar[CoreId]->SeqStatus[Sequence] = SPI_SEQ_FAILED;

      /* [cover parentID={4E3BAA9A-2762-4c74-A86F-D8E3BECA83DC}] Set all
      jobs to SPI_JOB_FAILED [/cover] */
      /* Loop through all jobs of sequence */
      while(JobId != SPI_JOB_DELIMITER)
      {
        /* Set the job status of sequence to be failed */
        Spi_RuntimeCoreVar[CoreId]->JobStatus[JobId] = SPI_JOB_FAILED;
        JobIndex++;
        JobId = SeqConfigPtr->JobLinkPtrPhysical[JobIndex];
      }
    }
    else
    {
      /* Traverse through next job for transmisaion */
      JobIndex++;
      JobId = SeqConfigPtr->JobLinkPtrPhysical[JobIndex];
    }

    /* [cover parentID={10F66A24-1CB6-4860-BC18-27E4E2FF6D4A}]
    SpiCancel is enabled [/cover] */
    /* Check if sequence is cancelled in between transmission */
    #if(SPI_CANCEL_API == STD_ON)
    /* [cover parentID={65DD0169-5278-4b18-8EC2-B4477D6C32F0}]
    Check if sequence is cancelled,
    update job status accordingly [/cover] */
    if(Spi_RuntimeCoreVar[CoreId]->SeqStatus[Sequence] ==
        SPI_SEQ_CANCELED)
    {
      /* [cover parentID={101A93D0-1678-491f-9C27-08FD72636EFF}]
      Loop through all jobs of sequence and set the status
      to SPI_JOB_OK[/cover] */
      /* Loop through all the jobs */
      while(JobId != SPI_JOB_DELIMITER)
      {
        /* Set the status of jobs to be OK */
        Spi_RuntimeCoreVar[CoreId]->JobStatus[JobId] = SPI_JOB_OK;
        JobIndex++;
        JobId = SeqConfigPtr->JobLinkPtrPhysical[JobIndex];
      }
    }
    #endif /* SPI_CANCEL_API == STD_ON */
    /* Check if all jobs are transmitted */
  } while(JobId != SPI_JOB_DELIMITER);

  /* [cover parentID={C8A9A2BF-20B8-461d-B1C3-BAB3A2AA075A}]
  Set sequence result to SPI_SEQ_OK on successful transmission
  [/cover] */
  /* Check if sequence is pending, update status to "OK" indicating
      successful transmission */
  if(Spi_RuntimeCoreVar[CoreId]->SeqStatus[Sequence] == SPI_SEQ_PENDING)
  {
    Spi_RuntimeCoreVar[CoreId]->SeqStatus[Sequence] = SPI_SEQ_OK;
  }
  return RetVal;
} /* End of function Spi_lSyncTransmit */
#endif /* SPI_LEVEL_DELIVERED != 1U */

#if(SPI_LEVEL_DELIVERED != 1U)
/*
 CYCLOMATIC_Spi_lSyncStartJob_JUSTIFICATION: Function is used to initiate the
 transmission of Jobs and the each channel in job is looped. Multiple
 conditions are required to check each channel datawidth and to check
 channel is last channel and time out is required to exit from the SFR
 check loop. This function cannot be split further.
*/
/*******************************************************************************
** Traceability     : [cover parentID={0A91EC86-52F0-4c7b-B65B-15C6A284CDC6}] **
** Syntax          : static Std_ReturnType Spi_lSyncStartJob                  **
**                               (const Spi_JobType JobId)                    **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : JobId - job Id to be transmitted                         **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: When there is NO HW error during transmission      **
**                   E_NOT_OK: Whene there is an error                        **
**                                                                            **
** Description     : This function initiates the transmission                 **
**                   at the Job level                                         **
*******************************************************************************/
static Std_ReturnType Spi_lSyncStartJob(const Spi_JobType JobId)
{
  const Spi_JobConfigType* JobConfigPtr;
  Spi_ChannelType ChannelId;
  Std_ReturnType ChnlTxErr = E_OK;
  uint8 ChannelIndex = 0U;
  uint8 IsFirstChnl = 1U;
  uint8 IsLastChnl = 0U;
  uint8 DataWidth = 0;
  uint8 HwId;
  uint8 CsPolarity;

  /* Get core information */
  uint32 CoreId = Mcal_GetCpuIndex();
  const Spi_CoreConfigType *CoreConfigPtr =
    Spi_kGlobalConfigPtr->CoreConfigPtr[CoreId];
  const Spi_ChannelConfigType* ChannelConfigPtr;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: register type Definition */
  Ifx_QSPI_GLOBALCON GlobalConReg;
  const Ifx_QSPI* ModulePtr;
  uint8 port;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: register type Definition */
  Ifx_QSPI_BACON lBacon;
  uint32 LoopCounter = Spi_kGlobalConfigPtr->SyncTimeout;
  /* [cover parentID={F0948AAD-B775-4060-A25F-13F0763106F8}]
   Fetch the Job configuration and set jobs status to pending
  [/cover] */
  /* Fetch the Job configuration */
  JobConfigPtr = &CoreConfigPtr->JobConfigPtr[JobId];
  uint8 ToggleCs = JobConfigPtr->FramebasedCs;

  /* Set jobs status to pending */
  Spi_RuntimeCoreVar[CoreId]->JobStatus[JobId] = SPI_JOB_PENDING;

  /* Set Job parameters - Configure QSPI mode, Baud and Move counter */
  Spi_lHwSetJobConfig(JobConfigPtr, SPI_SYNC_COMMS_TYPE);

  /* Fetch first channel to be transmitted */
  ChannelId = JobConfigPtr->ChnlLinkPtrPhysical[ChannelIndex];

  HwId = JobConfigPtr->HwUnit & SPI_HWUNIT_MASK;

  /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
  effects foreseen by violating this MISRA rule, as the pointer
  to the object type that it is getting cast into, is a known type. */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
   * effects foreseen by violating this MISRA rule. */
  ModulePtr = &(SPI_HW_MODULE[HwId]);

  /* [cover parentID={26A31D3A-5D80-4a21-B20F-ED32F329D22C}]
   Loop till all channels are transmitted
  [/cover] */
  /* Loop till last channel is transmitted */
  do
  {
    /* Check if next channel is Last channel */
    if(JobConfigPtr->ChnlLinkPtrPhysical[ChannelIndex + 1U] ==
        SPI_CHANNEL_DELIMITER)
    {
      IsLastChnl = 1U;
    }

    /* Set channel configuration - update BACON */
    lBacon = Spi_lHwSetChannelConfig(ChannelId, JobConfigPtr, ToggleCs);

    /* [cover parentID={26A31D3A-5D80-4a21-B20F-ED32F329D22C}]
    Update BACON for Sync transmit
    [/cover] */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access.
       No side effects foreseen by violating this MISRA rule. */
    /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
    effects foreseen by violating this MISRA rule, as the pointer
    to the object type that it is getting cast into, is a known type. */
    SPI_HW_MODULE[HwId].BACONENTRY.U = lBacon.U;

    ChannelConfigPtr =
      &CoreConfigPtr->ChannelConfigPtr[ChannelId];

    DataWidth = Spi_lGetChannelDataWidth(ChannelConfigPtr);

    /* [cover parentID={913B4B0F-5E19-44d7-8851-8D2A984FDA7F}]
    Check Datawidth to be transmitted
    [/cover] */
    /* Start transmission */
    /* [cover parentID={5CC0752C-03B8-48dc-A952-035E7CB5372D}]
    When Datawidth is 8Bit
    [/cover] */
    if(DataWidth == 1U)
    {
      ChnlTxErr = Spi_lSyncTransmitData8Bit( ChannelId, JobConfigPtr,
                                             IsFirstChnl, IsLastChnl);
    }
    /* [cover parentID={BA48477B-1593-424e-B440-EE19D52EC2A3}]
    When Datawidth is 16Bit
    [/cover] */
    else if(DataWidth == 2U)
    {
      ChnlTxErr = Spi_lSyncTransmitData16Bit( ChannelId, JobConfigPtr,
                                              IsFirstChnl, IsLastChnl);

    }
    else /*DataWidth == 4U */
    {
      ChnlTxErr = Spi_lSyncTransmitData32Bit( ChannelId, JobConfigPtr,
                                              IsFirstChnl, IsLastChnl);
    }

    IsFirstChnl = 0U;

    /* [cover parentID={BCDDD87D-919B-4ea2-AA4B-36B5B096E148}]
    Last channel of job - to operate CS [/cover] */
    /* If CS is operated by port pin and is last channel */
    if((IsLastChnl == 1U) || (ChnlTxErr == E_NOT_OK))
    {
        /* [cover parentID={FF3AB9FA-FD0B-49b6-A71D-99BEC70B53B9}]
        Wait till HW enters wait state and check for timeout occured [/cover] */
        /* Wait till TRAIL phase completes */
        while((ModulePtr->STATUS.B.PHASE != 0U) && (LoopCounter != 0U))
        {
          /* [cover parentID={C2E10AB2-01A7-4a7f-A017-1A6C30A94CDD}]
          Check for any QSPI Hw error occur  [/cover] */
          /* if error occurs break out of wait cycle */
          uint32 u32Sts = (ModulePtr->STATUS.U & SPI_HW_ERROR_MASK);
          if(u32Sts != 0U)
          {
            break;
          }
          LoopCounter--;
        }
        /* [cover parentID={E44AD894-81BB-4f01-A3E6-8F2919A3ED86}]
        Check if any QSPI Hw errors OR timeout occured [/cover] */
        if(((ModulePtr->STATUS.U & SPI_HW_ERROR_MASK) != 0U) || (LoopCounter == 0U))
        {
          ChnlTxErr = E_NOT_OK;
        }
      /* [cover parentID={CBFFF67B-0909-454e-92DC-C46307BDEEE9}]
          Check if CS is GPIO [/cover] */
      if(JobConfigPtr->CSPortPin != SPI_CS_VIA_HW_OR_NONE)
      {
        /* [cover parentID={3EE890D1-F3B7-4657-B4A4-4917929E7CCA}]
        De-assert CS - GPIO configured as CS[/cover] */
        /* De-assert CS */
        if(JobConfigPtr->CsPolarity == (uint8)STD_LOW)
        {
          CsPolarity = (uint8)STD_LOW ;
        }
        else
        {
          CsPolarity = (uint8)STD_HIGH;
        }

        port = (uint8)((JobConfigPtr->CSPortPin) >> \
                       (uint16)SPI_PORT_NUM_OFFSET);
        Spi_lSetCsViaGpio(port,
                    (uint8)((JobConfigPtr->CSPortPin) & SPI_BIT_MASK_3_TO_0), \
                     CsPolarity);
      }
    }

    /* [cover parentID={1843D50C-496A-48c5-8D52-438029E26A5A}] Stop
    sequence on HW error[/cover] */
    /* Check for any HW transmission error */
    if(ChnlTxErr == (uint8)E_OK)
    {
      /* Raise Production Error to indicate successful transmission */
      /* [cover parentID={1AF2287A-54B7-4071-9998-2650B57AA525}][/cover] */
      #if(SPI_HW_ERROR_DEM_REPORT == SPI_DEM_REPORT_ENABLED)
      /* [cover parentID={5C3BEDA6-5A4A-45E9-85DC-2FFACBF5FF54}][/cover] */
      Spi_lReportDemError(SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_PASSED);
      #endif
      ChannelIndex++;
      ChannelId = JobConfigPtr->ChnlLinkPtrPhysical[ChannelIndex];
    }
    else
    {
      /* On transmission error - Raise Production Error indicating failure */
      /* [cover parentID={402D0D29-550A-41d3-A28D-E2FFC38B5DF2}][/cover] */
      #if(SPI_HW_ERROR_DEM_REPORT == SPI_DEM_REPORT_ENABLED)
      /* [cover parentID={76887FE1-8D1C-4bec-B881-951484F2DF3B}][/cover] */
      Spi_lReportDemError(SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
      #endif

      /* Set the job status to failure and point to last channel */
      /* [cover parentID={8C2C0B0D-4A60-4c17-BB7E-33C49C84E715}][/cover] */
      Spi_RuntimeCoreVar[CoreId]->JobStatus[JobId] = SPI_JOB_FAILED;

      /* Reset QSPI HW state machine */
      /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access.
      No side effects foreseen by violating this MISRA rule, as the pointer
      to the object type that it is getting cast into, is a known type. */
      /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access.
         No side effects foreseen by violating this MISRA rule. */
      GlobalConReg.U = SPI_HW_MODULE[HwId].GLOBALCON.U;
      GlobalConReg.B.RESETS = 1;
      /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access.
      No side effects foreseen by violating this MISRA rule, as the pointer
      to the object type that it is getting cast into, is a known type. */
      /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
     * effects foreseen by violating this MISRA rule. */
      SPI_SFR_RUN_TIME_WRITE32(&SPI_HW_MODULE[HwId]. \
                                            GLOBALCON.U, GlobalConReg.U);
      /* Exit tx loop */
      ChannelId = SPI_CHANNEL_DELIMITER;
    }
  } while(ChannelId != SPI_CHANNEL_DELIMITER);

  /* [cover parentID={3626F54D-0F26-4f0c-BABA-7F7540A6761D}] Set job status
  to OK once successfully transmitted[/cover] */
  /* Check if the job status is "pending" */
  if(Spi_RuntimeCoreVar[CoreId]->JobStatus[JobId] == SPI_JOB_PENDING)
  {
    /* Set the job status to "OK" - job successfully transmitted */
    Spi_RuntimeCoreVar[CoreId]->JobStatus[JobId] = SPI_JOB_OK;
  }
  return ChnlTxErr;
} /* End of function Spi_lSyncStartJob */
#endif /* SPI_LEVEL_DELIVERED != 1U */

#if(SPI_LEVEL_DELIVERED != 0U)
/*******************************************************************************
** Traceability     : [cover parentID={3C45E11A-C060-4320-A818-AA6E644FAA23}] **
** Syntax          : static uint32 Spi_lGetTotalBytesOfJob                    **
**                   (const Spi_JobConfigType *const JobPtr)                  **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : JobPtr - Job configuration pointer                       **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns total bytes of a Job                             **
**                                                                            **
** Description     : Function calculates the total number of elements to be   **
**                   transmitted for whole of the job. i.e. if 3 channels are **
**                   assigned to a job, sum of all elements of all the 3      **
**                   channels is returned.                                    **
*******************************************************************************/
static uint32 Spi_lGetTotalBytesOfJob(const Spi_JobConfigType *const JobPtr)
{
  uint32 TotaljobBytes = 0;
  uint16 ChnlIndex = 0U;
  uint16 ChnlId = 0;

  /* Get the core information */
  uint32 CoreId = Mcal_GetCpuIndex();

  /* [cover parentID={6C0E82BA-F691-49a8-8A21-712AB8BFADBC}] Get total bytes
  to be transffered for job to load to Move counter [/cover] */
  /* Loop through all channels */
  while(JobPtr->ChnlLinkPtrPhysical[ChnlIndex] != SPI_CHANNEL_DELIMITER)
  {
    /* Get the total elements to be transmitted in a job */
    ChnlId = JobPtr->ChnlLinkPtrPhysical[ChnlIndex];
    TotaljobBytes += Spi_RuntimeCoreVar[CoreId]->
                     ChannelBufPointers[ChnlId].TransferLength;
    ChnlIndex++;
  }

  /* return total elements */
  return TotaljobBytes;
}
#endif

/*******************************************************************************
** Syntax          : static void Spi_lHwSetJobConfig                          **
**                   (                                                        **
**                     const Spi_JobConfigType *const JobConfigPtr,           **
**                     const uint8 IsAsynchronous                             **
**                   )                                                        **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : JobConfigPtr - Job configuration pointer                 **
**                   IsAsynchronous - Is the Job asynhronous                  **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : This function configures the SFR wrt the Job properties  **
**                   assigned to the hardware, such as baudrate, parity,      **
**                   CS polarity, CLK phase etc.                              **
*******************************************************************************/
static void Spi_lHwSetJobConfig
(
  const Spi_JobConfigType *const JobConfigPtr,
  const uint8 IsAsynchronous
)
{
  Ifx_QSPI* ModulePtr;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: register type Definition */
  Ifx_QSPI_GLOBALCON GlobalConReg;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: register type Definition */
  Ifx_QSPI_GLOBALCON1 GlobalCon1Reg;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: register type Definition */
  Ifx_QSPI_ECON EconReg;
  uint8 HwChannelno;
  uint8 HwUnitNum;
  uint32 Strobe;
  uint32 LBbitstatus;
  const Spi_CoreConfigType *CoreConfigPtr = NULL_PTR;

  #if(SPI_LEVEL_DELIVERED != 0U)
  uint8 ToggleCs = JobConfigPtr->FramebasedCs;
  #endif

  uint32 CoreId = Mcal_GetCpuIndex();

  CoreConfigPtr = Spi_kGlobalConfigPtr->CoreConfigPtr[CoreId];

  /* Get the kernel configuration */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
  effects foreseen by violating this MISRA rule, as the pointer
  to the object type that it is getting cast into, is a known type. */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
   * effects foreseen by violating this MISRA rule. */
  ModulePtr = &(SPI_HW_MODULE[JobConfigPtr->HwUnit & SPI_HWUNIT_MASK]);
  HwUnitNum = (JobConfigPtr->HwUnit & SPI_HWUNIT_MASK);
  HwChannelno = JobConfigPtr->HwUnit >> SPI_SLSO_CHANNEL_NUM_OFFSET;

  GlobalConReg.U = ((JobConfigPtr->BaudRateAndClockParam >> \
                   SPI_GLOBALCON_LOWER_WORD_OFFSET) & SPI_LOWER_HALF_WORD_MASK);

  /* Read the GLOBALCON register to get the status of Loopback mode */
  /* [cover parentID={8E837A82-BC83-4697-91E6-D5EED23D50B1}]
     Retain the Loopback status[/cover] */
  LBbitstatus = (ModulePtr->GLOBALCON.U & \
                        (1UL << (uint32)IFX_QSPI_GLOBALCON_LB_OFF));
  GlobalConReg.U |= SPI_GLOBALCON_VAL;
  GlobalConReg.U |= LBbitstatus;

  /* Check is External Demultiplexer mode is ON */
  /* [cover parentID={6D7A6AC3-647A-44bb-B08E-D4642503CAA7}]
     Is external demultiplexer is enabled[/cover] */
  if ((CoreConfigPtr->QSPIHwConfigPtr[HwUnitNum]->ExternalDemuxEnabled) == 1U)
  {
      Strobe = CoreConfigPtr->QSPIHwConfigPtr[HwUnitNum]->StrobeDelay;
      /* Set DEL0 bit */
      GlobalConReg.U |= SPI_GLOBALCON_DEL0_SET;
      /* Update the Strobe Value */
      GlobalConReg.U |= (Strobe << (uint32)SPI_STROBE_SHIFT);
  }
  GlobalCon1Reg.U = SPI_GLOBALCON1_VAL;

  #if(SPI_LEVEL_DELIVERED == 2U)
  if(IsAsynchronous == 1U)
  #else
  UNUSED_PARAMETER(IsAsynchronous);
  #endif

  #if(SPI_LEVEL_DELIVERED != 0U)
  {
    GlobalCon1Reg.U |= SPI_GLOBALCON1_ASYNC_VAL;
  }
  #endif

  /* [cover parentID={3DDDF10D-99D5-4fd3-917B-669BA0BD02CD}]
      In polling mode, error flags will be polled [/cover] */
  /* Disable error interrupt in polling mode */
  #if(SPI_LEVEL_DELIVERED == 2U)
  if(Spi_RuntimeCoreVar[CoreId]->AsyncMode == SPI_POLLING_MODE)
  {
    GlobalCon1Reg.B.ERRORENS = 0U;
  }
  #endif

  #if(SPI_LEVEL_DELIVERED != 0U)
  /* [cover parentID={C05EB50B-B642-4246-8956-648392AB17E5}]
     Check if frame based CS is enabled[/cover] */
  /* Check if the "Frame based CS" feature is enabled, do not use MC
  mode for transmission */
  if((ToggleCs == 0U) && (IsAsynchronous == 1U))
  {
    /* Enable frame completion interrupt and interrupt when "wait"
        state is reached */
    GlobalCon1Reg.B.PT2 = SPI_WAIT_STATE;

    /* [cover parentID={CF56E0B6-C529-4709-838B-D0F81D351D25}]
    PT2 not configured if in POLLING mode[/cover] */
    #if(SPI_LEVEL_DELIVERED == 2U)
    if(Spi_RuntimeCoreVar[CoreId]->AsyncMode == SPI_INTERRUPT_MODE)
    #endif
    {
      GlobalCon1Reg.B.PT2EN = SPI_TRIGGER_ENABLE;
    }

    /* [cover parentID={1082AA91-88F0-4c5d-B662-A7E251DDE9BE}]
    Enable HW driven Chip select mechanism to drive CS (SLSO)[/cover] */
    /* Enable move counter for totals elements in a job */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: Assignment to a register
       bit-field that is of narrower type. However the write is performed
       within allowed range of values. As the total number of elements
       that can be transmitted per job range from 1 to 8190. */
    ModulePtr->MC.B.MCOUNT = Spi_lGetTotalBytesOfJob(JobConfigPtr);
    ModulePtr->MCCON.B.MCEN = 1;
  }
  #endif

  /* Update Delays - ECON, Mode - GLOBALOCON1, GlobalCON and FLAGSCLEAR -
  clear interrupt flags */
  EconReg.U = (JobConfigPtr->BaudRateAndClockParam & SPI_LOWER_HALF_WORD_MASK);

  /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
  effects foreseen by violating this MISRA rule, as the pointer
  to the object type that it is getting cast into, is a known type. */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
   * effects foreseen by violating this MISRA rule. */
  SPI_SFR_RUN_TIME_WRITE32(&ModulePtr->GLOBALCON.U, GlobalConReg.U);

  /* [cover parentID={711CF276-9BDF-4D51-BAC2-2FAFE3D606D1}]
   Enable TXF, RXF and PT2 [/cover] */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
  effects foreseen by violating this MISRA rule, as the pointer
  to the object type that it is getting cast into, is a known type. */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
   * effects foreseen by violating this MISRA rule. */
  SPI_SFR_RUN_TIME_WRITE32(&ModulePtr->GLOBALCON1.U,    \
                                        GlobalCon1Reg.U);
  /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
  effects foreseen by violating this MISRA rule, as the pointer
  to the object type that it is getting cast into, is a known type. */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
   * effects foreseen by violating this MISRA rule. */
  SPI_SFR_RUN_TIME_WRITE32(&ModulePtr->ECON[HwChannelno \
                                         & SPI_QSPI_ECON_CH_MASK].U, EconReg.U);

  ModulePtr->FLAGSCLEAR.U = (SPI_QSPI_FLAGSCLEAR_VALUE);
} /* End of function Spi_lHwSetJobConfig */

/*******************************************************************************
** Traceability     : [cover parentID={64D50C48-3F47-4fa3-8C90-16628172EBA4}] **
** Syntax          : static Ifx_QSPI_BACON Spi_lHwSetChannelConfig            **
**                   (                                                        **
**                       const Spi_ChannelType SpiChId,                       **
**                       const Spi_JobConfigType* const JobConfigPtr,         **
**                       const uint8 ToggleCs                                 **
**                   )                                                        **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : SpiChId - Channel Id                                     **
**                   JobConfigPtr - Job config pointer                        **
**                   ToggleCs - 1U: represents Frame based Cs is enabled.     **
**                              0U: repesents Frame based Cs is disabled.     **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : returns the value to be written to BACON register        **
**                                                                            **
** Description     : This function configures the SFR wrt the Channel         **
**                   properties, such as datawidth, LSB/MSB, default data     **
*******************************************************************************/
static Ifx_QSPI_BACON Spi_lHwSetChannelConfig
(
  const Spi_ChannelType SpiChId,
  const Spi_JobConfigType* const JobConfigPtr,
  const uint8 ToggleCs
)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: register type Definition */
  Ifx_QSPI_BACON BaconReg;
  Ifx_QSPI* ModulePtr;

  /* Get the Core and channel configuration */
  uint32 CoreId = Mcal_GetCpuIndex();
  const Spi_CoreConfigType *CoreConfigPtr =
    Spi_kGlobalConfigPtr->CoreConfigPtr[CoreId];
  const Spi_ChannelConfigType* ChannelConfigPtr =
    &CoreConfigPtr->ChannelConfigPtr[SpiChId];

  /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
  effects foreseen by violating this MISRA rule, as the pointer
  to the object type that it is getting cast into, is a known type. */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
   * effects foreseen by violating this MISRA rule. */
  ModulePtr = &(SPI_HW_MODULE[JobConfigPtr->HwUnit & SPI_HWUNIT_MASK]);

  /* Clear all interrupt flags */
  ModulePtr->FLAGSCLEAR.U = SPI_QSPI_FLAGSCLEAR_VALUE;

  /* [cover parentID={633FDCBE-0D39-4d60-B971-8194F3932BC9}][/cover] */
  /* Update Idle/Lead/Trail configuration and also the Parity type */
  BaconReg.U = JobConfigPtr->IdleLeadTrailDelay;
  BaconReg.B.PARTYP = JobConfigPtr->ParitySupport;

  /* [cover parentID={42A68107-8DCA-429e-A9DB-33ECC8C6E18D}][/cover] */
  /* Update SLSO to be operated */
  BaconReg.B.CS = JobConfigPtr->HwUnit >> SPI_SLSO_CHANNEL_NUM_OFFSET;

  /* set data direction */
  BaconReg.B.MSB = (ChannelConfigPtr->DataConfig) >> \
                               SPI_DATA_SHIFT_DIRECTION_BIT_OFFSET;

  /* Set the data length to be transmitted */
  /* for 2 bits, value should be 1
              5 bits, value should be 4 */
  BaconReg.B.DL = ((ChannelConfigPtr->DataConfig) &                           \
                   (uint8)SPI_BIT_MASK_6_TO_0) - 1U;

  /* [cover parentID={6E791FDC-70C1-41a5-837F-9D5B43F9B87D}][/cover]  */
  /* Set Last - 0 indicates not last channel, 1 - indicates to de-assert SLSO */
  BaconReg.B.LAST = ToggleCs;

  BaconReg.B.BYTE = 0U;
  BaconReg.B.UINT = 1U;

  return BaconReg;
} /* End of function Spi_lHwSetChannelConfig */

#if(SPI_LEVEL_DELIVERED != 1U)
/*******************************************************************************
** Traceability     : [cover parentID={8DE87DEF-26BA-4030-87DC-FD18EEB7B672}] **
** Syntax          : static Std_ReturnType Spi_lSyncTransmitData8bit          **
**                   (                                                        **
**                     const Spi_ChannelType ChannelId,                       **
**                     const Spi_JobConfigType* const JobConfigPtr,           **
**                     const uint8 IsFirstChnl,                               **
**                     const uint8 IsLastChnl                                 **
**                   )                                                        **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant for different QSPI HW                          **
**                                                                            **
** Parameters (in) : ChannelId : Channel id for which data has to             **
**                                be transmitted                              **
**                   JobConfigPtr : Job Configuration pointer                 **
**                   IsFirstChnl : Value of 1 indicates first channel else    **
**                                   the value is 0.                          **
**                   IsLastChnl : Value of 1 indicates last channel else      **
**                                   the value is 0.                          **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK : Upon successful transmision.                      **
**                   E_NOT_OK: if any error occurs during transmission        **
**                                                                            **
** Description     : This function initiates the transmission at the          **
**                   channel level with 8-bit data width                      **
*******************************************************************************/
static Std_ReturnType Spi_lSyncTransmitData8Bit
(
  const Spi_ChannelType ChannelId,
  const Spi_JobConfigType* const JobConfigPtr,
  const uint8 IsFirstChnl,
  const uint8 IsLastChnl
)
{
  Ifx_QSPI* ModulePtr;
  const uint8* Src8BitPtr = NULL_PTR;
  uint8* Dest8BitPtr = NULL_PTR;
  uint8 CsPolarity = 0;
  Spi_NumberOfDataType TransferCount;
  Std_ReturnType RetVal = E_OK;
  uint8 HwId;
  uint8 SrcBufferNull = 0U;
  uint8 DestBufferNull = 0U;
  uint8 port;
  uint8 SyncDummyRead;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: register type Definition */
  Ifx_QSPI_BACON lBacon;

  /* Get core, channel configuration */
  uint32 CoreId = Mcal_GetCpuIndex();
  const Spi_CoreConfigType *CoreConfigPtr =
    Spi_kGlobalConfigPtr->CoreConfigPtr[CoreId];
  const Spi_ChannelConfigType* ChannelConfigPtr =
    &CoreConfigPtr->ChannelConfigPtr[ChannelId];
  HwId = JobConfigPtr->HwUnit & SPI_HWUNIT_MASK;

  /* Assign Source / destination pointers based on data width */
  Src8BitPtr = Spi_RuntimeCoreVar[CoreId]->                                  \
               ChannelBufPointers[ChannelId].SrcPtr;

  /* MISRA2012_RULE_11_8_JUSTIFICATION: The Dest8BitPtr is updated only when
   the destination buffer is NULL and a dummy variable is assigned to read data.
   Thus the const qualifier is not valid in this particular scenario.  */
  Dest8BitPtr = (uint8*)Spi_RuntimeCoreVar[CoreId]->                         \
                ChannelBufPointers[ChannelId].DestPtr;

  /* [cover parentID={48FF3DCA-5E16-43a3-9A68-6A900B781E55}]
  Check if destination is NULL, assign dummy variable to read data [/cover] */
  /* Check if destination / source buffer is NULL */
  if(Dest8BitPtr == NULL_PTR)
  {
    /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of variable SyncDummyRead
      is used only to read values.
    The address is not stored for later usage in the function.
    Hence it is safe to assign the address of the local variable. */
    Dest8BitPtr = &SyncDummyRead;
    DestBufferNull = 1U;
  }

  /* [cover parentID={48FF3DCA-5E16-43a3-9A68-6A900B781E55}]
  Check if source is NULL, assign default data to be transmitted [/cover] */
  if(Src8BitPtr == NULL_PTR)
  {
    Src8BitPtr = (const uint8*)&ChannelConfigPtr->Defaultdata;
    SrcBufferNull = 1U;
  }


  /* Get the total elements to be transmitted */
  TransferCount = Spi_RuntimeCoreVar[CoreId]->
                  ChannelBufPointers[ChannelId].TransferLength;

  /* Get the kernel pointer */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
  effects foreseen by violating this MISRA rule, as the pointer
  to the object type that it is getting cast into, is a known type. */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
   * effects foreseen by violating this MISRA rule. */
  ModulePtr = &(SPI_HW_MODULE[HwId]);

  /* [cover parentID={2B837025-A3D0-4b3e-BD57-3DCE9749218D}]
  Assert CS - GPIO configured as CS[/cover] */
  /* Check if CS is operated as port-pin and is the first channel,
      Asset CS pin */
  if((JobConfigPtr->CSPortPin != SPI_CS_VIA_HW_OR_NONE) && (IsFirstChnl == 1U))
  {
    if(JobConfigPtr->CsPolarity == (uint8)STD_LOW)
    {
      CsPolarity = (uint8)STD_HIGH ;
    }
    else
    {
      CsPolarity = (uint8)STD_LOW;
    }
    port = (uint8)(((JobConfigPtr->CSPortPin) >> (uint16)SPI_PORT_NUM_OFFSET));
    Spi_lSetCsViaGpio(port, (uint8)((JobConfigPtr->CSPortPin) &       \
                                    SPI_BIT_MASK_3_TO_0), (CsPolarity));
  }

  /* loop through number of elements to be transmitted */
  do
  {
    /* Update BACON.LAST if it is last channel and last
        * element to be transmitted */
    /* [cover parentID={7141019A-339E-4979-9060-FA7C1780EB8A}]
      last element
    [/cover] */
    if(TransferCount == 1U)
    {
      if(IsLastChnl == 1U)
      {
        lBacon = Spi_lHwSetChannelConfig(ChannelId, JobConfigPtr, 1U);
        ModulePtr->BACONENTRY.U = lBacon.U;
      }
    }

    ModulePtr->FLAGSCLEAR.U = (((uint32)1U << IFX_QSPI_FLAGSCLEAR_RXC_OFF) |  \
                               ((uint32)1U << IFX_QSPI_FLAGSCLEAR_TXC_OFF));

    /* Copy data to TX FIFO */
    ModulePtr->DATAENTRY[SPI_FIFO_ENTRY].U = (uint32) * Src8BitPtr;

    /* [cover parentID={F6DEC17D-70EF-413f-BA43-7464C502A98D}]
      If Source is NULL, do not increment
      Source pointer - Always copy from default data [/cover] */
    /* If Source is NULL, Do not increment source buffer
    * transmit Default data*/
    if(SrcBufferNull == 0U)
    {
      Src8BitPtr++;
    }

    /* [cover parentID={00A323DB-96DE-45e7-859E-17FFA2432A11}]
      HW error occured
    [/cover] */
    /* Check if any HW error occured during transmission,
        if error occured stop transmisison */
    RetVal = Spi_lSynTransErrCheck(ModulePtr);
    if(RetVal  == (uint8)E_OK)
    {
      /* Read the receive data from the QSPI RX FIFO */
      *Dest8BitPtr = (uint8)ModulePtr->RXEXIT.U;

      /* [cover parentID={818D0A39-8146-40e6-BE6E-6C53FC3EAFB0}]
      If destination is NULL, do not increment
      destination pointer - Always copy to dummy [/cover] */
      /* If Destination is NULL, Do not increment Destination
       * buffer - Ignore received data*/
      if(DestBufferNull == 0U)
      {
        Dest8BitPtr++;
      }

      TransferCount--;
    }
    else
    {
      /* Break loop */
      break;
    }

    /* Loop through till last element */
  } while(TransferCount > 0U);

  /* Return status */
  return RetVal;
} /* End of function Spi_lSyncTransmitData */

/*******************************************************************************
** Traceability     : [cover parentID={0140913B-A56E-4a21-A2E5-299B45064D48}] **
** Syntax          : static Std_ReturnType Spi_lSyncTransmitData16bit         **
**                   (                                                        **
**                     const Spi_ChannelType ChannelId,                       **
**                     const Spi_JobConfigType* const JobConfigPtr,           **
**                     const uint8 IsFirstChnl,                               **
**                     const uint8 IsLastChnl                                 **
**                   )                                                        **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant for different QSPI HW                          **
**                                                                            **
** Parameters (in) : ChannelId : Channel id for which data has to             **
**                                be transmitted                              **
**                   JobConfigPtr : Job Configuration pointer                 **
**                   IsFirstChnl : Value of 1 indicates first channel else    **
**                                   the value is 0.                          **
**                   IsLastChnl : Value of 1 indicates last channel else      **
**                                   the value is 0.                          **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK : Upon successful transmision.                      **
**                   E_NOT_OK: if any error occurs during transmission        **
**                                                                            **
** Description     : This function initiates the transmission at the          **
**                   channel level with 16-bit data width                     **
*******************************************************************************/
static Std_ReturnType Spi_lSyncTransmitData16Bit
(
  const Spi_ChannelType ChannelId,
  const Spi_JobConfigType* const JobConfigPtr,
  const uint8 IsFirstChnl,
  const uint8 IsLastChnl
)
{
  Ifx_QSPI* ModulePtr;
  const uint16* Src16BitPtr = NULL_PTR;
  uint16* Dest16BitPtr = NULL_PTR;
  uint8 CsPolarity = 0;
  Spi_NumberOfDataType TransferCount;
  Std_ReturnType RetVal = E_OK;
  uint8 HwId;
  uint8 SrcBufferNull = 0U;
  uint8 DestBufferNull = 0U;
  uint8 port;
  uint16 SyncDummyRead;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: register type Definition */
  Ifx_QSPI_BACON lBacon;

  /* Get core, channel configuration */
  uint32 CoreId = Mcal_GetCpuIndex();
  const Spi_CoreConfigType *CoreConfigPtr =
    Spi_kGlobalConfigPtr->CoreConfigPtr[CoreId];
  const Spi_ChannelConfigType* ChannelConfigPtr =
    &CoreConfigPtr->ChannelConfigPtr[ChannelId];
  HwId = JobConfigPtr->HwUnit & SPI_HWUNIT_MASK;


  /* MISRA2012_RULE_11_3_JUSTIFICATION: The casting is needed to perform 16 bit
     access as per data size and buffer is memory aligned.   */
  Src16BitPtr = (const uint16*)Spi_RuntimeCoreVar[CoreId]->                  \
                ChannelBufPointers[ChannelId].SrcPtr;

  /* MISRA2012_RULE_11_3_JUSTIFICATION: The casting is needed to perform 16 bit
     access as per data size and buffer is memory aligned.  */
  /* MISRA2012_RULE_11_8_JUSTIFICATION: The Dest16BitPtr is updated only when
     the destination buffer is NULL and a dummy variable is assigned to read data.
     Thus the const qualifier is not valid in this particular scenario.  */
  Dest16BitPtr = (uint16*)Spi_RuntimeCoreVar[CoreId]->                       \
                 ChannelBufPointers[ChannelId].DestPtr;
  /* [cover parentID={D0044A8B-303B-4117-9FA0-8908CC4CDE57}]
    Check if destination is NULL, assign dummy variable to read data
  [/cover] */
  /* Check if destination / source buffer is NULL */
  if(Dest16BitPtr == NULL_PTR)
  {
    /* MISRA2012_RULE_11_3_JUSTIFICATION: Address of SyncDummyRead
       variable that is of uint16 as per the data transfer width,
       is assigned to the Dest16BitPtr and buffer is memory aligned.
       No side effects foreseen by violating this MISRA rule. */
    /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of variable SyncDummyRead
      is used only to read values.
      The address is not stored for later usage in the function.
      Hence it is safe to assign the address of the local variable. */
    Dest16BitPtr = &SyncDummyRead;
    DestBufferNull = 1U;
  }

  /* [cover parentID={D0044A8B-303B-4117-9FA0-8908CC4CDE57}]
    Check if source is NULL, assign default data to be transmitted
   [/cover] */
  if(Src16BitPtr == NULL_PTR)
  {
    /* MISRA2012_RULE_11_3_JUSTIFICATION: The casting is needed to perform
       16 bit access as per data size and buffer is memory aligned. */
    /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of variable Defaultdata
      is used only to read values.
      The address is not stored for later usage in the function.
      Hence it is safe to assign the address of the local variable.  */
    Src16BitPtr = (const uint16*)&ChannelConfigPtr->Defaultdata;
    SrcBufferNull = 1U;
  }


  /* Get the total elements to be transmitted */
  TransferCount = Spi_RuntimeCoreVar[CoreId]->
                  ChannelBufPointers[ChannelId].TransferLength;

  /* Get the kernel pointer */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
  effects foreseen by violating this MISRA rule, as the pointer
  to the object type that it is getting cast into, is a known type. */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
   * effects foreseen by violating this MISRA rule. */
  ModulePtr = &(SPI_HW_MODULE[HwId]);
  /* [cover parentID={D3EE13E3-D765-4e58-BB43-8EB7A80A1A2A}]
    Assert CS - GPIO configured as CS
  [/cover] */
  /* Check if CS is operated as port-pin and is the first channel,
      Asset CS pin */
  if((JobConfigPtr->CSPortPin != SPI_CS_VIA_HW_OR_NONE) && (IsFirstChnl == 1U))
  {
    if(JobConfigPtr->CsPolarity == (uint8)STD_LOW)
    {
      CsPolarity = (uint8)STD_HIGH ;
    }
    else
    {
      CsPolarity = (uint8)STD_LOW;
    }

    port = (uint8)(((JobConfigPtr->CSPortPin) >> (uint16)SPI_PORT_NUM_OFFSET));
    Spi_lSetCsViaGpio(port, (uint8)((JobConfigPtr->CSPortPin) &       \
                                    SPI_BIT_MASK_3_TO_0), (CsPolarity));
  }

  /* loop through number of elements to be transmitted */
  do
  {

    /* Update BACON.LAST if it is last channel and last
        * element to be transmitted */
    /* [cover parentID={9A3EF6D5-2DA9-4029-9DBE-7530FB19B14A}]
      last element
    [/cover] */
    if(TransferCount == 1U)
    {
      if(IsLastChnl == 1U)
      {
        lBacon = Spi_lHwSetChannelConfig(ChannelId, JobConfigPtr, 1U);
        ModulePtr->BACONENTRY.U = lBacon.U;
      }
    }

    ModulePtr->FLAGSCLEAR.U = (((uint32)1U << IFX_QSPI_FLAGSCLEAR_RXC_OFF) |  \
                               ((uint32)1U << IFX_QSPI_FLAGSCLEAR_TXC_OFF));


    ModulePtr->DATAENTRY[SPI_FIFO_ENTRY].U = (uint32) * Src16BitPtr;
    /* [cover parentID={ABBB5C4C-0192-4299-B58F-937664C4245E}]
      If Source is NULL, do not increment
      Source pointer - Always copy from default data
    [/cover] */
    /* If Source is NULL, Do not increment source buffer
    * transmit Default data*/
    if(SrcBufferNull == 0U)
    {
      Src16BitPtr++;
    }

    /* [cover parentID={8CCA61B0-83A8-4fa6-BE11-59105E686FD8}]
     HW error occured
    [/cover] */
    /* Check if any HW error occured during transmission,
        if error occured stop transmisison */
    RetVal = Spi_lSynTransErrCheck(ModulePtr);
    if(RetVal  == (uint8)E_OK)
    {
      *Dest16BitPtr = (uint16)ModulePtr->RXEXIT.U;
      /* [cover parentID={CC605B6D-CFDD-4b47-A2F4-0B70A976883D}]
        If destination is NULL, do not increment
        destination pointer - Always copy to dummy
      [/cover] */
      /* If Destination is NULL, Do not increment Destination buffer
       * Ignore received data*/
      if(DestBufferNull == 0U)
      {
        Dest16BitPtr++;
      }

      TransferCount--;
    }
    else
    {
      /* Break loop */
      break;
    }

    /* Loop through till last element */
  } while(TransferCount > 0U);

  /* Return status */
  return RetVal;
} /* End of function Spi_lSyncTransmitData */

/*******************************************************************************
** Traceability     : [cover parentID={3F1ADFE2-F8E8-46e1-8120-3D66E20C99CD}] **
** Syntax          : static Std_ReturnType Spi_lSyncTransmitData32bit         **
**                   (                                                        **
**                     const Spi_ChannelType ChannelId,                       **
**                     const Spi_JobConfigType* const JobConfigPtr,           **
**                     const uint8 IsFirstChnl,                               **
**                     const uint8 IsLastChnl                                 **
**                   )                                                        **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant for different QSPI HW                          **
**                                                                            **
** Parameters (in) : ChannelId : Channel id for which data has to             **
**                                be transmitted                              **
**                   JobConfigPtr : Job Configuration pointer                 **
**                   IsFirstChnl : Value of 1 indicates first channel else    **
**                                   the value is 0.                          **
**                   IsLastChnl : Value of 1 indicates last channel else      **
**                                   the value is 0.                          **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK : Upon successful transmision.                      **
**                   E_NOT_OK: if any error occurs during transmission        **
**                                                                            **
** Description     : This function initiates the transmission at the          **
**                   channel level with 32-bit data width                     **
*******************************************************************************/
static Std_ReturnType Spi_lSyncTransmitData32Bit
(
  const Spi_ChannelType ChannelId,
  const Spi_JobConfigType* const JobConfigPtr,
  const uint8 IsFirstChnl,
  const uint8 IsLastChnl
)
{
  Ifx_QSPI* ModulePtr;
  const uint32* Src32BitPtr = NULL_PTR;
  uint32* Dest32BitPtr = NULL_PTR;
  uint8 CsPolarity = 0;

  Spi_NumberOfDataType TransferCount;
  Std_ReturnType RetVal = E_OK;
  uint8 HwId;
  uint8 SrcBufferNull = 0U;
  uint8 DestBufferNull = 0U;
  uint8 port;
  uint32 SyncDummyRead;
  /* MISRA2012_RULE_19_2_JUSTIFICATION: register type Definition */
  Ifx_QSPI_BACON lBacon;

  /* Get core, channel configuration */
  uint32 CoreId = Mcal_GetCpuIndex();
  const Spi_CoreConfigType *CoreConfigPtr =
    Spi_kGlobalConfigPtr->CoreConfigPtr[CoreId];
  const Spi_ChannelConfigType* ChannelConfigPtr =
    &CoreConfigPtr->ChannelConfigPtr[ChannelId];
  HwId = JobConfigPtr->HwUnit & SPI_HWUNIT_MASK;

  /* MISRA2012_RULE_11_3_JUSTIFICATION: The casting is needed to perform
     32 bit access as per data size and buffer is memory aligned. */
  Src32BitPtr = (const uint32*)Spi_RuntimeCoreVar[CoreId]->                  \
                ChannelBufPointers[ChannelId].SrcPtr;

  /* MISRA2012_RULE_11_3_JUSTIFICATION: The casting is needed to perform
     32 bit access as per data size and buffer is memory aligned. */
  /* MISRA2012_RULE_11_8_JUSTIFICATION: The Dest8BitPtr is updated only when
     the destination buffer is NULL and a dummy variable is assigned to
     read data. Thus the const qualifier
     is not valid in this particular scenario. */
  Dest32BitPtr = (uint32*)Spi_RuntimeCoreVar[CoreId]->                       \
                 ChannelBufPointers[ChannelId].DestPtr;

  /* [cover parentID={BC30C7C6-A0A2-4923-8396-14C5DA812C7D}]
    Check if destination is NULL, assign dummy variable to read data
  [/cover] */
  /* Check if destination / source buffer is NULL */
  if(Dest32BitPtr == NULL_PTR)
  {
    /* MISRA2012_RULE_1_3_JUSTIFICATION: Address of variable SyncDummyRead
      is used only to read values.
      The address is not stored for later usage in the function.
      Hence it is safe to assign the address of the local variable. */
    Dest32BitPtr = &SyncDummyRead;
    DestBufferNull = 1U;
  }

  /* [cover parentID={BC30C7C6-A0A2-4923-8396-14C5DA812C7D}]
    Check if source is NULL, assign default data to be transmitted
  [/cover] */
  if(Src32BitPtr == NULL_PTR)
  {
    Src32BitPtr = (const uint32*)&ChannelConfigPtr->Defaultdata;
    SrcBufferNull = 1U;
  }

  /* Get the total elements to be transmitted */
  TransferCount = Spi_RuntimeCoreVar[CoreId]->
                  ChannelBufPointers[ChannelId].TransferLength;

  /* Get the kernel pointer */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
  effects foreseen by violating this MISRA rule, as the pointer
  to the object type that it is getting cast into, is a known type. */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
   * effects foreseen by violating this MISRA rule. */
  ModulePtr = &(SPI_HW_MODULE[HwId]);
  /* [cover parentID={602A71FF-3909-4b55-B1F0-DEB6DFC03A96}]
   Assert CS - GPIO configured as CS
  [/cover] */
  /* Check if CS is operated as port-pin and is the first channel,
      Asset CS pin */
  if((JobConfigPtr->CSPortPin != SPI_CS_VIA_HW_OR_NONE) && (IsFirstChnl == 1U))
  {
    if(JobConfigPtr->CsPolarity == (uint8)STD_LOW)
    {
      CsPolarity = (uint8)STD_HIGH ;
    }
    else
    {
      CsPolarity = (uint8)STD_LOW;
    }
    port = (uint8)(((JobConfigPtr->CSPortPin) >> (uint16)SPI_PORT_NUM_OFFSET));
    Spi_lSetCsViaGpio(port, (uint8)((JobConfigPtr->CSPortPin) &       \
                                    SPI_BIT_MASK_3_TO_0), (CsPolarity));
  }

  /* loop through number of elements to be transmitted */
  do
  {
    /* Update BACON.LAST if it is last channel and last
        * element to be transmitted */
    /* [cover parentID={448E467A-6ED3-49e6-8E12-0D4E71B2E653}]
      last element
    [/cover] */
    if(TransferCount == 1U)
    {
      if(IsLastChnl == 1U)
      {
        lBacon = Spi_lHwSetChannelConfig(ChannelId, JobConfigPtr, 1U);
        ModulePtr->BACONENTRY.U = lBacon.U;
      }
    }

    ModulePtr->FLAGSCLEAR.U = (((uint32)1U << IFX_QSPI_FLAGSCLEAR_RXC_OFF) |  \
                               ((uint32)1U << IFX_QSPI_FLAGSCLEAR_TXC_OFF));

    ModulePtr->DATAENTRY[SPI_FIFO_ENTRY].U = (uint32) * Src32BitPtr;
    /* [cover parentID={703D5ABB-D6B5-43b1-BFEE-C88671AD1CFF}]
      If Source is NULL, do not increment
      Source pointer - Always copy from default data
    [/cover] */
    /* If Source is NULL, Do not increment source buffer
    * transmit Default data*/
    if(SrcBufferNull == 0U)
    {
      Src32BitPtr++;
    }

    /* [cover parentID={756E4439-0073-4b95-A06E-AA20D66C5FDF}]
       HW error occured
    [/cover] */
    /* Check if any HW error occured during transmission,
        if error occured stop transmisison */
    RetVal = Spi_lSynTransErrCheck(ModulePtr);
    if(RetVal  == (uint8)E_OK)
    {
      *Dest32BitPtr = (uint32)ModulePtr->RXEXIT.U;
      /* [cover parentID={D563C396-2E19-4af5-A146-1A6ACA7AD937}]
        If destination is NULL, do not increment
        destination pointer - Always copy to dummy
      [/cover] */
      /* If Destination is NULL, Do not increment Destination buffer
       * buffer - Ignore received data*/
      if(DestBufferNull == 0U)
      {
        Dest32BitPtr++;
      }

      TransferCount--;
    }
    else
    {
      /* Break loop */
      break;
    }

    /* Loop through till last element */
  } while(TransferCount > 0U);

  /* Return status */
  return RetVal;
} /* End of function Spi_lSyncTransmitData */
#endif /* SPI_LEVEL_DELIVERED != 1U */

#if(SPI_LEVEL_DELIVERED != 1U)
/*******************************************************************************
** Traceability     : [cover parentID={7934371C-AD34-4f1a-9114-3DB56DF7CEE5}] **
** Syntax          : static Std_ReturnType Spi_lSynTransErrCheck              **
**                                    (const Ifx_QSPI* const ModulePtr)       **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : ModulePtr - QSPI module pointer                          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK - Tx Data is Shifted-out and Rx is Shifted-in       **
**                   E_NOT_OK - Timeout or Hw error occurred                  **
**                                                                            **
** Description     : Polls for the Tx data to be shifted-out and              **
**                   Rx data to be shifted-in till the LOOP timeout counter   **
**                   expires. Also Checks for any transmission errors         **
*******************************************************************************/
static Std_ReturnType Spi_lSynTransErrCheck(const Ifx_QSPI* const ModulePtr)
{
  uint32 LoopCounter = Spi_kGlobalConfigPtr->SyncTimeout;
  Std_ReturnType RetVal = E_OK;

  /* [cover parentID={E567C930-4083-43ee-9C64-C6EDC9B552D3}]Check for
  timeout[/cover] */
  /* Check for data received on RX FIFO and check if timeout occured */
  while(((ModulePtr->STATUS.U & SPI_TXF_RXFIFO_MASK) != SPI_TXF_RXFIFO_1_SET) \
        && (LoopCounter != 0U))
  {
    /* [cover parentID={D4DCC5DE-071D-4d82-8ED4-AD9395EF4F95}]Check for
       errors[/cover] */
    /* Check if any QSPI Hw error occur */
    if((ModulePtr->STATUS.U & SPI_HW_ERROR_MASK) != 0U)
    {
      /* Update status as E_NOT_Ok */
      RetVal = E_NOT_OK;
      break;
    }
    LoopCounter--;
  }

  /* [cover parentID={CF9A82CB-0602-4b40-85EE-14A56EE62CF6}]Check for
  timeout or error occuring in synctransmit[/cover] */
  /* Check if any QSPI Hw error OR timeout occured */
  if(((ModulePtr->STATUS.U & SPI_HW_ERROR_MASK) != 0U) || (LoopCounter == 0U))
  {
    /* update status E_NOT_OK */
    RetVal = E_NOT_OK;
  }

  /* Return status */
  return RetVal;
} /* End of function Spi_lSynTransErrCheck */
#endif /* SPI_LEVEL_DELIVERED != 1U */

/*******************************************************************************
** Traceability     : [cover parentID={6DFE8631-7E75-42c3-82C5-CFCE204982EA}] **
**                                                                            **
** Syntax          : static void Spi_lSetCsViaGpio                            **
**                   (const uint8 Port, const uint8 Pin, const uint8 Level)   **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : Port - Port Number                                       **
**                   Pin - PortPin Number                                     **
**                   Level - Port level to be set                             **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : Sets the port pin to the desired level                   **
*******************************************************************************/
static void Spi_lSetCsViaGpio(const uint8 Port,
                              const uint8 Pin, const uint8 Level)
{
  uint32 PortOmrVal;

  /* wrt OMR, 'n' is the portpin and 'm' is the port.
     if Pm(n) = 0 and Pm(n+16)  = 1, then Pm(n) = Clears
     if Pm(n) = 0 and Pm(n+16)  = 1, then Pm(n) = Sets  */
  PortOmrVal = (uint32)(SPI_16BIT_DATAWIDTH) * Level;
  PortOmrVal += Pin;
  PortOmrVal = (uint32)1U << PortOmrVal;

  /* Update port pin state as per the Level parameter */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: PORT base address access.
     No side effects foreseen by violating this MISRA rule. */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
  effects foreseen by violating this MISRA rule, as the pointer
  to the object type that it is getting cast into, is a known type. */
  SPI_PORT_BASE_ADDR[Port].OMR.U = PortOmrVal;
} /* End of function Spi_lSetCsViaGpio */

#if(SPI_LEVEL_DELIVERED != 0U)
/*******************************************************************************
** Traceability     : [cover parentID={C156D2B5-1110-4b97-8541-93424952DCE7}] **
** Syntax          : Std_ReturnType Spi_lIsSlotsAvailableInQueue              **
**                   (                                                        **
**                     const uint16 NoOfJobs,                                 **
**                     const uint8 Module                                     **
**                   )                                                        **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : NoOfJobs - number Jobs assigned to the sequence          **
**                   Module - QSPI module index                               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK - Slots available in the Jobqueue                   **
**                   E_NOT_OK - Queue is full                                 **
**                                                                            **
** Description     : This function checks if the slots are available in the   **
**                   Queue to be scheduled for transmission                   **
*******************************************************************************/
static Std_ReturnType Spi_lIsSlotsAvailableInQueue(const uint16 NoOfJobs,
    const uint8 Module)
{
  Spi_JobType StartIndex, EndIndex, Length, Slots;
  Std_ReturnType RetVal = E_OK;

  /* Get core information */
  const Spi_CoreConfigType *CoreConfigPtr =
    Spi_kGlobalConfigPtr->CoreConfigPtr[Mcal_GetCpuIndex()];

  /* Get the First, Last element in Queue and length of Queue */
  StartIndex = Spi_RuntimeKernelVar[Module]->JobQueuePtr->QueueStartIndex;
  EndIndex = Spi_RuntimeKernelVar[Module]->JobQueuePtr->QueueEndIndex;
  Length = CoreConfigPtr->QSPIHwConfigPtr[Module]->JobQueueLength;

  /* [cover parentID={3B4F00D1-CE6C-4a55-A8F2-92F5E8B7EEF1}]Check no elements
  in Queue[/cover] */
  /* Check if Queue is empty */
  if(StartIndex == EndIndex)
  {
    Slots = Length;
  }
  /* [cover parentID={51243DB9-A55D-4d58-AD80-DC60816A7A99}]Check
  for slots in Queue[/cover] */
  /* Check remaining slots in Queue */
  else if(StartIndex < EndIndex)
  {
    Slots = ((Length - 1U) - EndIndex) + StartIndex;
  }
  else
  {
    Slots = StartIndex - (EndIndex - 1U);
  }

  /* [cover parentID={391653D0-7F99-412d-86AD-3979A3ACFB57}]Check
  if Queue can fit all jobs of sequence[/cover] */
  /* Check if the number jobs to be inserted are less than
      number of slots available */
  if(NoOfJobs > Slots)
  {
    /* If slots are less, update status as E_NOT_OK */
    RetVal = E_NOT_OK;
  }

  /* return status*/
  return RetVal;
} /* End of function Spi_lIsSlotsAvailableInQueue */
#endif /* SPI_LEVEL_DELIVERED != 0U */

#if(SPI_LEVEL_DELIVERED != 0U)
/*******************************************************************************
** Traceability     : [cover parentID={18759EE3-DA2B-4150-AE3B-2FA254136029}] **
** Syntax          : static Std_ReturnType Spi_lCheckJobIsNotShared           **
**                   (const Spi_SequenceType Sequence)                        **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : Sequence - Sequence ID                                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK - Job is not shared with other sequence which       **
**                          are in pending state                              **
**                   E_NOT_OK - Job is shared                                 **
**                                                                            **
** Description     : Checks if the Job is not shared with other sequences     **
**                   which are already in SPI_SEQ_PENDING state               **
*******************************************************************************/
static Std_ReturnType Spi_lCheckJobIsNotShared(const Spi_SequenceType Sequence)
{
  const uint8 * SeqSharePtr;
  Std_ReturnType RetVal = E_OK;
  uint8 Index = 0U;
  uint8 SeqIndex = 0U;

  /* Get core information */
  uint32 CoreId = Mcal_GetCpuIndex();
  const Spi_CoreConfigType *CoreConfigPtr =
    Spi_kGlobalConfigPtr->CoreConfigPtr[CoreId];

  /* Get the shared sequence list */
  SeqSharePtr = CoreConfigPtr->SequenceConfigPtr[Sequence].SeqSharePtr;

  /* [cover parentID={5E3CE047-14BE-447a-98BF-61561C69BD93}]Check if sequences
  are with shared jobs[/cover] */
  /* Loop through all shared sequence list */
  while(SeqSharePtr[Index] != SPI_SEQUENCE_DELIMITER)
  {
    /* Convert the Logical Sequence Number to Physical */
    SeqIndex = Spi_kGlobalConfigPtr->SequenceLookup[SeqSharePtr[Index]];

    /* [cover parentID={72ABC1BC-6022-431e-B1F3-7E4B56D69446}] check if
    sequence is in pending state[/cover] */
    /* Check if sequence is in pending state */
    if(Spi_RuntimeCoreVar[CoreId]->SeqStatus[SeqIndex] ==
        SPI_SEQ_PENDING)
    {
      /* Update status as E_NOT_OK and break */
      RetVal = E_NOT_OK;
      break;
    }
    Index++;
  }

  /* Return status */
  return RetVal;
} /* End of function Spi_lCheckJobIsNotShared */
#endif /* SPI_LEVEL_DELIVERED != 0U */

#if(SPI_LEVEL_DELIVERED != 0U)
/*******************************************************************************
** Traceability     : [cover parentID={B3516D81-2020-4c6d-BBFC-DE39A3EB2710}] **
** Syntax          : static void Spi_lAddSeqJobInQueue                        **
**                    (const uint8 HwModule, const Spi_SequenceType Sequence, **
**                    const Spi_JobType EndIndex, const Spi_JobType JobIndex) **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : HwModule : QSPI Hw                                       **
**                   Sequence : Sequence ID for which jobs are to be added    **
**                   EndIndex : Index in JobQueue to which jobs are to be     **
**                   added                                                    **
**                   JobIndex : Index from which jobs are to be fetched from  **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Returns the Index in which last job was inserted         **
**                                                                            **
** Description     : This function inserts jobs assigned to the sequence      **
**                   in the Queue based on the Job priority.                  **
*******************************************************************************/
static Spi_JobType Spi_lAddSeqJobInQueue(const uint8 HwModule,
    const Spi_SequenceType Sequence, const Spi_JobType EndIndex,
    const Spi_JobType JobIndex)
{
  uint16 JobProperty;
  Spi_JobType JobId;
  uint8 ModJobPrio;
  uint16 Job = JobIndex;
  Spi_JobType lEndIndex = EndIndex;

  /* Get core information */
  const Spi_CoreConfigType *CoreConfigPtr =
    Spi_kGlobalConfigPtr->CoreConfigPtr[Mcal_GetCpuIndex()];

  /* [cover parentID={7C161B81-7D29-4538-915A-873F752D2002}] Async jobs
  to be added to Queue for respective kernels [/cover] */
  /* Loop through all the jobs for a sequence */
  while(CoreConfigPtr->
        SequenceConfigPtr[Sequence].JobLinkPtrPhysical[Job] !=              \
        SPI_JOB_DELIMITER)
  {
    JobId = CoreConfigPtr->
            SequenceConfigPtr[Sequence].JobLinkPtrPhysical[Job];

    /* Update job property field to contain seq-id and modified priority */
    JobProperty = (uint16)Sequence;
    ModJobPrio = Spi_lModPrioforNonIntrSeq(Sequence, CoreConfigPtr->    \
                           SequenceConfigPtr[Sequence].JobLinkPtrPhysical[Job]);
    JobProperty |= ((uint16)ModJobPrio << SPI_JOB_PRIORITY_BIT_OFFSET);

    /* Update interruptible field in property */
    #if(SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON)
    JobProperty = JobProperty | ((uint16)CoreConfigPtr->               \
                            SequenceConfigPtr[Sequence].SeqInterruptible << \
                            SPI_SEQ_INTERRUPTABLE_BIT_OFFSET);
    #endif

    /* Update Job-Id and Job-Property in job Queue */
    Spi_RuntimeKernelVar[HwModule]->JobQueuePtr->                       \
    JobAndSeqQueuePtr[lEndIndex].QueueJobId = JobId;
    Spi_RuntimeKernelVar[HwModule]->JobQueuePtr->                       \
    JobAndSeqQueuePtr[lEndIndex].JobProperty = JobProperty;

    /* Point to next element in Queue */
    lEndIndex = Spi_lIncrementRoundIndex(lEndIndex, HwModule);
    Job++;
  }

  /* Return the last location updated */
  return lEndIndex;
}
#endif /* SPI_LEVEL_DELIVERED != 0U */

#if(SPI_LEVEL_DELIVERED != 0U)
/*******************************************************************************
** Traceability     :                                                         **
**                                                                            **
** Syntax          : static uint8 Spi_lGetCompareResult                       **
**                   (const uint8 FirstParam, const uint8 SecondParam,        **
**                                               const uint8 CompOper)        **
**                                                                            **
** Service ID      : NA                                                       **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : FirstParam : First number to be compared                 **
**                   SecondParam : Second number to be compared               **
**                   CompOper : SPI_SEQ_ID_COMP - Specifies Sequence ID       **
**                                comparison                                  **
**                              SPI_SEQ_PROP_COMP - Specifies Sequence        **
**                                property(interruptable/non-interruptable)   **
**                                comparison.                                 **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : SPI_JOBS_OF_DIFF_SEQ: Upon Sequence ID matches.          **
**                   SPI_JOBS_OF_SAME_SEQ: Upon Sequence ID mismatch.         **
**                   SPI_BOTH_SEQ_INTERRUPTABLE: when both sequences are      **
**                                         interruptable.                     **
**                   SPI_ONE_SEQ_NON_INTERRUPTABLE: when atleast one sequence **
**                              is non-interrutable.                          **
**                                                                            **
** Description     : Compares the passed parameters based on the              **
**                   operation specified                                      **
*******************************************************************************/
static uint8 Spi_lGetCompareResult(const uint8 FirstParam,
                                  const uint8 SecondParam, const uint8 CompOper)
{
  /* [cover parentID={66A73D49-ED59-4087-9390-C90214252F1E}] Async
  transmit    [/cover] */
  uint8 Status = SPI_ONE_SEQ_NON_INTERRUPTABLE;
  /* When comparing Sequence Id */
  if (CompOper == SPI_SEQ_ID_COMP)
  {
    if(FirstParam == SecondParam)
    {
      Status = SPI_JOBS_OF_SAME_SEQ;
    }
    else
    {
      Status = SPI_JOBS_OF_DIFF_SEQ;
    }
  } /* For comparing Sequences */
  else
  {
    if(FirstParam == SecondParam)
    {
      /* when both sequences are interruptable */
      if (FirstParam == SPI_BOTH_SEQ_INTERRUPTABLE)
      {
        Status = SPI_BOTH_SEQ_INTERRUPTABLE;
      }
    }
    else
    {
      Status = SPI_ONE_SEQ_NON_INTERRUPTABLE;
    }
  }
  return Status;
}

/*******************************************************************************
** Traceability     : [cover parentID={25165797-127F-475c-8D4F-1EE28B1B8ABC}] **
**                                                                            **
** Syntax          : static uint8 Spi_lCheckForJobInsert(                     **
**                                                   const uint8 JobPriority, **
**                                           const uint8 PrioOfJobInQNew,     **
**                                           const uint8 PrioOfNextJobInQ)    **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : JobPriority : Priority of the Job to be inserted.        **
**                   PrioOfJobInQ : Priority of the Job in Queue.             **
**                   PrioOfNextJobInQ : Priority of the next job in Queue.    **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : SPI_JOB_TO_INSERT : represents the Job to be inserted    **
**                   otherwise SPI_JOB_NOT_TO_INSERT.                         **
**                                                                            **
** Description     : This function compares the priority of incoming job      **
**                    with the priorities of the jobs in queue.               **
*******************************************************************************/
static uint8 Spi_lCheckForJobInsert(const uint8 JobPriority,
                                    const uint8 PrioOfJobInQ,
                                    const uint8 PrioOfNextJobInQ)
{
  uint8 status = SPI_JOB_NOT_TO_INSERT;
  uint8 result = FALSE;
  uint8 result1 = FALSE;

  /* Compare the priority of New Job with the Current job in Q and with the
  * next job in Q */
  if((JobPriority <= PrioOfJobInQ) && (JobPriority > PrioOfNextJobInQ))
  {
    result = TRUE;
  }

  /* Compare the priority of New Job with the Current job in Q and with the
  * next job in Q */
  if((JobPriority > PrioOfJobInQ) && (JobPriority > PrioOfNextJobInQ))
  {
    result1 = TRUE;
  }

  /* update the status variable */
  if ((result == TRUE) || (result1 == TRUE))
  {
    status = SPI_JOB_TO_INSERT;
  }

  return status;
}

/*
 CYCLOMATIC_Spi_lInsertSeqInQueue_JUSTIFICATION: Function is used to sort the
 priority of jobs in Queue for incoming sequence and insert the jobs in Queue
 in priority order, since multiple conditions play a role in sorting the Queue
 this function cannot be split further.
*/
/*******************************************************************************
** Traceability     : [cover parentID={2C113CD5-4BFA-4fa1-AA1D-63E08A508FAE}] **
** Syntax          : static void Spi_lInsertSeqInQueue                        **
**                   (const Spi_SequenceType Sequence)                        **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : Sequence - Sequence id                                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : This function inserts jobs assigned to the sequence      **
**                   in the Queue based on the Job priority.                  **
*******************************************************************************/
static void Spi_lInsertSeqInQueue(const Spi_SequenceType Sequence)
{
  Spi_JobType EndIndex, JobIndex, JobId;
  uint8 HwModule;
  #if(SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON)
  uint8 PrioOfJobInQNew;
  uint8 CompareResult = 0;
  Spi_JobType StartIndexBackup;
  uint8 SeqInQueueInterruptible;
  uint8 ModJobPrio;
  Spi_JobAndSeqQueueType *QueueElementPtr;
  uint8 NewSeqInterruptable;
  #endif
  Spi_JobType StartIndex;
  uint8 PrioOfJobInQ, PrioOfNextJobInQ;
  Spi_JobType LocalStartIndex, LocalEndIndex;
  const Spi_JobType* SeqJobLinkPtr;
  uint8 Result = 0;
  uint8 Result1 = 0;
  uint8 JobPriority, CheckForInsert;

  uint16 PreviousJobInserted, AllJobsInQueue;
  uint8 JobsWithDifferentSequence = 0;

  /* Get the core information */
  const Spi_CoreConfigType *CoreConfigPtr =                             \
      Spi_kGlobalConfigPtr->CoreConfigPtr[Mcal_GetCpuIndex()];

  /* When SPI_INTERRUPTIBLE_SEQ_ALLOWED=OFF, entire sequence is placed in
  * queue as per the priority of first job in sequence */

  /* When SPI_INTERRUPTIBLE_SEQ_ALLOWED=ON, the jobs are arranged in queue
   * based on the sequence property and job priority */

  /* Get the Queue parameters like Start, end
      total elements in Queue and Hw kernel */
  JobId =
    CoreConfigPtr->SequenceConfigPtr[Sequence].JobLinkPtrPhysical[0U];

  HwModule = CoreConfigPtr->JobConfigPtr[JobId].HwUnit & SPI_HWUNIT_MASK;

  StartIndex = (Spi_RuntimeKernelVar[HwModule]->\
                JobQueuePtr->QueueStartIndex);
  AllJobsInQueue = Spi_RuntimeKernelVar[HwModule]->                      \
                   JobQueuePtr->QueueEndIndex;

  EndIndex = Spi_RuntimeKernelVar[HwModule]->JobQueuePtr->QueueEndIndex;
  JobIndex = 0U;

  /* Check if Queue is empty or jobs have least priority - insert in last */

  /* [cover parentID={DF11BEF6-ED7F-4fb1-935A-A3B382B46BF4}]
   Queue is empty or jobs have least priority - insert in last
  [/cover] */
  if((StartIndex == EndIndex) || (CoreConfigPtr->JobConfigPtr[JobId].   \
                                  JobPriority == 0U))
  {
    EndIndex = Spi_lAddSeqJobInQueue(HwModule, Sequence, EndIndex,        \
                                     JobIndex);
  }
  /* [cover parentID={4BDBE87F-70C6-4002-9022-D4E080E4FD09}][/cover] */
  else    /* Re-arranging of jobs may be required */
  {
    StartIndex = (Spi_RuntimeKernelVar[HwModule]->                         \
                  JobQueuePtr->QueueStartIndex + 1U);
    EndIndex = Spi_RuntimeKernelVar[HwModule]->                           \
               JobQueuePtr->QueueEndIndex;

    SeqJobLinkPtr     = CoreConfigPtr->\
                        SequenceConfigPtr[Sequence].JobLinkPtrPhysical;

    PreviousJobInserted = 0;

    /* [cover parentID={4A187DC8-9EEE-46d1-B70D-814AFE52F73A}][/cover] */
    /* Loop through all the jobs in Queue to check priority */
    /* [cover parentID={15106C5C-575C-41f6-91C3-E6C62C16E165}]Priority
    rearrange[/cover] */
    while(AllJobsInQueue != 0U)
    {
      AllJobsInQueue--;
      #if(SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON)
      /* Check if job of particular index can be interrupted */
      SeqInQueueInterruptible = (uint8) (Spi_RuntimeKernelVar[HwModule]->\
                     JobQueuePtr->JobAndSeqQueuePtr[StartIndex].JobProperty >> \
                      SPI_SEQ_INTERRUPTABLE_BIT_OFFSET);

      /* Check if new sequence to be inserted in interruptible */
      /* [cover parentID={96A7EF4C-52AA-4e1a-8273-015C8F1FBCAF}]Set
      flag info to interruptible or non-interruptible[/cover] */
      NewSeqInterruptable = (uint8)                                   \
                            (CoreConfigPtr->SequenceConfigPtr[Sequence].       \
                             SeqInterruptible);
      #endif
      /* Check if the job in Queue and next job in Queue
          are related to same sequence */
      /* [cover parentID={4D058FC3-6F14-4ac7-A22D-4851E3127E63}][/cover] */
      Result = (uint8)(Spi_RuntimeKernelVar[HwModule]->           \
                       JobQueuePtr->JobAndSeqQueuePtr[StartIndex].JobProperty\
                       & 0xFFU);
      Result1 = (uint8)(Spi_RuntimeKernelVar[HwModule]->          \
                        JobQueuePtr->JobAndSeqQueuePtr[StartIndex + 1U].       \
                        JobProperty & 0xFFU);

      JobsWithDifferentSequence = Spi_lGetCompareResult(Result, Result1,
                                  SPI_SEQ_ID_COMP);

      LocalStartIndex = StartIndex;
      LocalEndIndex = EndIndex;
      #if(SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON)
      JobIndex = 0;
      #endif

      /* Get the priority of Queue element evaluated */
      PrioOfJobInQ = (uint8)((SPI_BIT_MASK_9_TO_8 &                     \
                              Spi_RuntimeKernelVar[HwModule]->JobQueuePtr->    \
     JobAndSeqQueuePtr[StartIndex].JobProperty) >> SPI_JOB_PRIORITY_BIT_OFFSET);

      #if(SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON)
      /* Check if both the sequences are interruptible */
      CompareResult = Spi_lGetCompareResult(SeqInQueueInterruptible,
                                            NewSeqInterruptable,
                                            SPI_SEQ_PROP_COMP);

      /* Sequence already in Queue is interruptible and new sequence
      is also interruptible */
      /* [cover parentID={6C528F63-25D3-4c1b-B634-066CAC76031A}]Interruptable
      sequence handling[/cover] */
      if(CompareResult == SPI_BOTH_SEQ_INTERRUPTABLE)
      {
        JobIndex = PreviousJobInserted;

        /* Loop through all the jobs of sequence */
        while(SeqJobLinkPtr[JobIndex] != SPI_JOB_DELIMITER)
        {
          LocalStartIndex = StartIndex;
          LocalEndIndex     = EndIndex;

          /* Get the priority of Queue element evaluated */
          PrioOfJobInQNew = (uint8)((SPI_BIT_MASK_9_TO_8 &             \
                            Spi_RuntimeKernelVar[HwModule]->JobQueuePtr->    \
                            JobAndSeqQueuePtr[StartIndex].JobProperty) >> \
                            SPI_JOB_PRIORITY_BIT_OFFSET);

          /* Get the priority of the next job in Q */
          PrioOfNextJobInQ = (uint8)((SPI_BIT_MASK_9_TO_8 &         \
                             Spi_RuntimeKernelVar[HwModule]->JobQueuePtr->     \
                            JobAndSeqQueuePtr[StartIndex + 1U].JobProperty) >> \
                            SPI_JOB_PRIORITY_BIT_OFFSET);

          /* Get the Job priority of the new Job to be inserted */
          JobPriority = CoreConfigPtr->JobConfigPtr \
                        [SeqJobLinkPtr[JobIndex]].JobPriority;

          /* Check the new job priority w.r.to Current Job in Q and
           * next job in Q for proper placement of job
           */
          /* [cover parentID={A89E4C12-9F74-4755-AAED-851A2BE5694B}]
          priority comparsion[/cover] */
          CheckForInsert = Spi_lCheckForJobInsert(JobPriority,
                                                  PrioOfJobInQNew,
                                                  PrioOfNextJobInQ);
          /* If job has to be inserted */
          if(CheckForInsert == SPI_JOB_TO_INSERT)
          {
            /* Place the Job right after the current job */
            if (((JobPriority <= PrioOfJobInQNew) && \
                 (JobPriority > PrioOfNextJobInQ)))
            {
              /* Increment the Index to next location */
              StartIndex = StartIndex + 1U;
              LocalStartIndex = LocalStartIndex + 1U;
            }

            /* get the Job's Queue Location */
            QueueElementPtr =                                     \
                &Spi_RuntimeKernelVar[HwModule]->JobQueuePtr->\
                JobAndSeqQueuePtr[StartIndex];

            /* Elevate the priority of non-interruptible sequence
               to highest priority */
            ModJobPrio = Spi_lModPrioforNonIntrSeq(Sequence,       \
                            CoreConfigPtr->SequenceConfigPtr[Sequence].\
                                             JobLinkPtrPhysical[JobIndex]);

            /* Copy Queue elements to temporary Queue */
            Spi_lPushToLocalQ(LocalStartIndex, LocalEndIndex, \
                              HwModule);

            /* Copy job-Id and job-properties */
            QueueElementPtr->QueueJobId = SeqJobLinkPtr[JobIndex];
            QueueElementPtr->JobProperty  =  (uint16) Sequence;
            QueueElementPtr->JobProperty |=  ((uint16)\
                                     ModJobPrio << SPI_JOB_PRIORITY_BIT_OFFSET);
            QueueElementPtr->JobProperty |=  ((uint16)\
                       NewSeqInterruptable << SPI_SEQ_INTERRUPTABLE_BIT_OFFSET);

            JobIndex++;
            PreviousJobInserted = JobIndex;

            /* Store the Current placed Job location,
            * because next job comparison starts from here */
            StartIndexBackup = StartIndex;

            /* This increment is needed to restore the
            * jobs from Re-arrange buffer
            */
            StartIndex =  Spi_lIncrementRoundIndex(StartIndex, \
                                                   HwModule);

            /* Copy Queue elements from temporary Queue
                to main Queue */
            EndIndex = Spi_lPopFromLocalQ(LocalStartIndex,        \
                                          LocalEndIndex, StartIndex, HwModule);

            /* next job comparison should start from this Job*/
            StartIndex = StartIndexBackup;
          }
          else
          {
            /* Point to next element in Queue */
            StartIndex =  Spi_lIncrementRoundIndex(StartIndex,      \
                                                   HwModule);
            break;
          }
        }
      }
      /* Only sequence in Queue is interruptible */
      /* [cover parentID={95003603-C2CF-4946-90C6-D61D39C27D2D}]Priority
      rearrange[/cover] */
      else if(SeqInQueueInterruptible == 1U)
      {
        /* [cover parentID={B148395C-AC28-4e57-BF6A-3B7C12A2E78F}]
        check for the priority[/cover] */

        /* Check the priority of job */
        if(CoreConfigPtr->JobConfigPtr[SeqJobLinkPtr[JobIndex]].  \
            JobPriority > PrioOfJobInQ)
        {
          /* Copy successive elements in Queue to temporary Queue */
          Spi_lPushToLocalQ(LocalStartIndex, LocalEndIndex, \
                            HwModule);

          /* Insert all new jobs in Main Queue */
          EndIndex = Spi_lAddSeqJobInQueue(HwModule, \
                                           Sequence, StartIndex, JobIndex);
          StartIndex =  EndIndex;

          /* Copy Queue elements from temporary Queue */
          EndIndex = Spi_lPopFromLocalQ(LocalStartIndex, \
                                        LocalEndIndex, StartIndex, HwModule);

          JobIndex += CoreConfigPtr->SequenceConfigPtr[Sequence].\
                      NoOfJobInSeq;
          break;
        }
        else
        {
          /* Point to next element in Queue */
          StartIndex =  \
                        Spi_lIncrementRoundIndex(StartIndex, HwModule);
        }
      }
      /* Only New sequence is interruptable OR Both are
          non-interruptable */
      else
      {
      #endif
        JobIndex = PreviousJobInserted;
        /* Either all the jobs are inserted OR parsed through
            complete Queue */
        /* [cover parentID={A5046CA0-D182-4cf0-A5A5-78FCC479A4E3}]check
        for non interruptable jobs remaining[/cover] */

        if((SeqJobLinkPtr[JobIndex] == SPI_JOB_DELIMITER) || \
            (StartIndex == EndIndex))
        {
          /* MISRA2012_RULE_15_4_JUSTIFICATION: The loop is terminated
             because there are no jobs remaining to be inserted
             into the queue from the new sequence, or if the end
             of the queue is reached. */
          break;
        }
        /* [cover parentID={E6185C31-7E57-4023-872D-ADCAA0F2D065}]
        check for jobs belonging to sequences[/cover] */
        /* Are the jobs belonging to Different sequences */
        else if(JobsWithDifferentSequence == SPI_JOBS_OF_DIFF_SEQ)
        {
          /* Get the priority of next job in Q */
          PrioOfNextJobInQ = (uint8)((SPI_BIT_MASK_9_TO_8 &         \
                            Spi_RuntimeKernelVar[HwModule]->JobQueuePtr->     \
                       JobAndSeqQueuePtr[StartIndex + 1U].JobProperty) >> \
                           SPI_JOB_PRIORITY_BIT_OFFSET);

          /* Get the Job priority of the new Job to be inserted */
          JobPriority = CoreConfigPtr->JobConfigPtr \
                        [SeqJobLinkPtr[JobIndex]].JobPriority;

          /* Check the New Job priority W.r.to the priorities
          * of current job and Next job in Q
          */
          CheckForInsert = Spi_lCheckForJobInsert(JobPriority,
                                                  PrioOfJobInQ,
                                                  PrioOfNextJobInQ);
          /* [cover parentID={E647D4FE-A8B4-44c6-B415-A6462AAB961D}]
          check for job insertion[/cover] */

          /* If job has to be inserted */
          if(CheckForInsert == SPI_JOB_TO_INSERT)
          {
            /* If new sequence to be inserted is
               non-interruptible */
            /* [cover parentID={45404AB5-C918-4560-A0BB-9A8B0590152F}]
            check for sequence interrutable[/cover] */
            #if(SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON)
            if(NewSeqInterruptable == 0U)
            {
            #endif
              /* Copy all queue elements to temporary Queue
              * Index is incremented to maintain sync between
              * Job restore location.
              */
              Spi_lPushToLocalQ(LocalStartIndex + 1U, \
                                LocalEndIndex, HwModule);

              /* Copy the new job right after the current Job
              * location.
              */
              EndIndex = Spi_lAddSeqJobInQueue(HwModule, \
                                         Sequence, StartIndex + 1U, JobIndex);

              StartIndex =  EndIndex;
              /* Restore the Jobs from Local Q to Main Q
              * in the same order that placed.
              */
              EndIndex = Spi_lPopFromLocalQ(LocalStartIndex + 1U, \
                                            LocalEndIndex, \
                                            StartIndex, HwModule);

              JobIndex += CoreConfigPtr->SequenceConfigPtr\
                          [Sequence].NoOfJobInSeq;

              /* MISRA2012_RULE_15_4_JUSTIFICATION: The loop is terminated
                 after the non-interruptible sequence is
                 inserted to main queue.  */
              break;
              #if(SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON)
            }
            else /* New sequence is interruptible */
            {
              /* Get the Next Job's location to insert the
              * new job as the current Job priority is Greater
              */
              QueueElementPtr = \
                                &Spi_RuntimeKernelVar[HwModule]->JobQueuePtr->\
                                JobAndSeqQueuePtr[StartIndex + 1U];

              /* Get the highest priority of sequence */
              ModJobPrio = Spi_lModPrioforNonIntrSeq\
                           (Sequence, \
                            CoreConfigPtr->SequenceConfigPtr[Sequence].\
                            JobLinkPtrPhysical[JobIndex]);

              /* Push Queue elements to temporary Queue
              * Index incremented to maintain Sync during restore
              */
              Spi_lPushToLocalQ\
              (LocalStartIndex + 1U, LocalEndIndex, HwModule);

              /* Copy Queue-id and properties */
              QueueElementPtr->QueueJobId = \
                                            SeqJobLinkPtr[JobIndex];
              QueueElementPtr->JobProperty  =  \
                                               (uint16) Sequence;
              QueueElementPtr->JobProperty |=  \
                           ((uint16)ModJobPrio << SPI_JOB_PRIORITY_BIT_OFFSET);
              QueueElementPtr->JobProperty |=  \
              ((uint16)NewSeqInterruptable << SPI_SEQ_INTERRUPTABLE_BIT_OFFSET);

              JobIndex++;
              PreviousJobInserted = JobIndex;

              /* Store the location of inserted Job as it is
              * required to start the comparison right from here */
              StartIndexBackup = StartIndex + 1U;

              /* Point to next location in Q to restore */
              StartIndex =  Spi_lIncrementRoundIndex    \
                            (StartIndex + 1U, HwModule);

              /* Copy Queue elements from temporary Queue */
              EndIndex = Spi_lPopFromLocalQ(LocalStartIndex + 1U, \
                                          LocalEndIndex, StartIndex, HwModule);

              /* Next Job should be compared with currently
              * inserted Job */
              StartIndex = StartIndexBackup;
            }
              #endif
          }
          else
          {
            /* Point to next job in Queue */
            StartIndex =  Spi_lIncrementRoundIndex \
                          (StartIndex, HwModule);
          }
        }
        else
        {
          /* Point to next element in Queue */
          StartIndex =  \
                        Spi_lIncrementRoundIndex(StartIndex, HwModule);
        }
        #if(SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON)
      }
        #endif
    }

    if(SeqJobLinkPtr[JobIndex] != SPI_JOB_DELIMITER)
    {
      /* Reached End of Queue - Add remaining elements in Queue */
      EndIndex = Spi_lAddSeqJobInQueue(HwModule, Sequence, EndIndex, \
                                       PreviousJobInserted);
    }
  }

  /* Update End of Queue - index */
  Spi_RuntimeKernelVar[HwModule]->JobQueuePtr->QueueEndIndex = EndIndex;
} /* End of function Spi_lInsertSeqInQueue */
#endif /* SPI_LEVEL_DELIVERED != 0U */

#if(SPI_LEVEL_DELIVERED != 0U)
/*******************************************************************************
** Traceability     : [cover parentID={5BA06B1E-214D-4144-8A6C-8758C1DDD397}] **
** Syntax          : static Spi_JobType Spi_lIncrementRoundIndex              **
**                   (const Spi_JobType Index, const uint8 HwModule)          **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : Index - StartIndex of EndIndex for the Queue to be       **
**                           incremented                                      **
**                   HwModule - QSPI Hw index to fetch the Queue length       **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Spi_JobType - Incremented value for the Index            **
**                                                                            **
** Description     : Increments the Index and if the value is equal to the    **
**                   queue length then the index is rounded to initial value  **
**                   of zero(in order to implement circular Job queue)        **
*******************************************************************************/
static Spi_JobType Spi_lIncrementRoundIndex(const Spi_JobType Index,
    const uint8 HwModule)
{
  Spi_JobType LocalIndex = Index;

  /* Get the core information */
  const Spi_CoreConfigType *CoreConfigPtr =                               \
      Spi_kGlobalConfigPtr->CoreConfigPtr[Mcal_GetCpuIndex()];

  /* Increment Queue index */
  LocalIndex++;

  /* [cover parentID={C3CC22AD-D448-494b-8A5F-3832AC86A2F2}]
  Check if last element is reached in Queue
  [/cover] */
  /* Set the index to "0" is end of Queue is reached */
  if (LocalIndex ==                                                           \
      (CoreConfigPtr->QSPIHwConfigPtr[HwModule]->JobQueueLength))
  {
    LocalIndex = 0U;
  }

  /* return index */
  return LocalIndex;
} /* End of function Spi_lIncrementRoundIndex */
#endif /* SPI_LEVEL_DELIVERED != 0U */


#if(SPI_LEVEL_DELIVERED != 0U)
/*******************************************************************************
** Traceability     : [cover parentID={8AA2EB53-23DA-47ce-B111-27F53149014C}] **
** Syntax          : static void Spi_lPushToLocalQ                            **
**                   (                                                        **
**                     const Spi_JobType LocalStartIndex,                     **
**                     const Spi_JobType LocalEndIndex,                       **
**                     const uint8 HwModule                                   **
**                   )                                                        **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : LocalStartIndex - StartIndex for the Local Q             **
**                   LocalEndIndex - EndIndex for the Local Q                 **
**                   HwModule - QSPI Hw index to fetch the QUeue length       **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : This function copies the Job from Main Q to Local Q      **
*******************************************************************************/
static void Spi_lPushToLocalQ
(
  const Spi_JobType LocalStartIndex,
  const Spi_JobType LocalEndIndex,
  const uint8 HwModule
)
{
  Spi_JobType LocalStartId = LocalStartIndex;

  /* [cover parentID={700A9B83-E673-4143-B39E-D775FAE18A19}]
  Push eleemnts into Queue to rearrange jobs as per priority
  [/cover] */
  /* Loop through elements in Queue from start to end index */
  while(LocalStartId != LocalEndIndex)
  {
    /* Copy job-id and job-property to temporary Queue */
    Spi_RuntimeKernelVar[HwModule]->JobQueuePtr->                       \
    JobAndSeqQueueRearrangePtr[LocalStartId] =                            \
        Spi_RuntimeKernelVar[HwModule]->JobQueuePtr->                   \
        JobAndSeqQueuePtr[LocalStartId];
    LocalStartId = Spi_lIncrementRoundIndex(LocalStartId, HwModule);
  }
} /* End of function Spi_lPushToLocalQ */
#endif /* SPI_LEVEL_DELIVERED != 0U */
#if(SPI_LEVEL_DELIVERED != 0U)
/*******************************************************************************
** Traceability     : [cover parentID={04518EC7-75F0-4e4f-9ADF-4B30AD7EB21F}] **
** Syntax          : static void Spi_lPopFromLocalQ                           **
**                   (                                                        **
**                     const Spi_JobType LocalStartIndex,                     **
**                     const Spi_JobType LocalEndIndex,                       **
**                     const Spi_JobType CopyIndex,                           **
**                     const uint8 HwModule,                                  **
**                   )                                                        **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : LocalStartIndex - StartIndex for the local Q             **
**                   LocalEndIndex - EndUndex for the local Q                 **
**                   CopyIndex - Copy index of the Main Queue                 **
**                   HwModule - QSPI module ID                                **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : return the last index to which job info is copied        **
**                                                                            **
** Description     : This function pops the elements present in the Local Q   **
**                   to the Main Q after the jobs are inserted as per         **
**                   their priority                                           **
*******************************************************************************/
static uint16 Spi_lPopFromLocalQ
(
  const Spi_JobType LocalStartIndex,
  const Spi_JobType LocalEndIndex,
  const Spi_JobType CopyIndex,
  const uint8 HwModule
)
{
  Spi_JobType EndId, LocalStartId;
  EndId = CopyIndex;
  LocalStartId = LocalStartIndex;

  /* [cover parentID={52FB8079-8A52-438f-A48C-2C947C29BBCF}]
    Loop through all elements pushed into Queue to rearrange as per priority
    [/cover] */
  /* Loop through elements in temporary Queue from start to end index */
  while(LocalStartId != LocalEndIndex)
  {
    /* Copy elements from temporary Queue to Main Queue */
    Spi_RuntimeKernelVar[HwModule]->                                         \
    JobQueuePtr->JobAndSeqQueuePtr[EndId] =
      Spi_RuntimeKernelVar[HwModule]->JobQueuePtr->                \
      JobAndSeqQueueRearrangePtr[LocalStartId];
    LocalStartId = Spi_lIncrementRoundIndex(LocalStartId, HwModule);
    EndId = Spi_lIncrementRoundIndex(EndId, HwModule);
  }

  /* return the last index to which job info is copied */
  return EndId;
} /* End of function Spi_lPopFromLocalQ */
#endif /* SPI_LEVEL_DELIVERED != 0U */
#if(SPI_LEVEL_DELIVERED != 0U)
/*******************************************************************************
** Traceability     : [cover parentID={FF5362A4-4757-4c2e-8D5E-93B29A7586D2}] **
**                                                                            **
** Syntax          : static uint8 Spi_lModPrioforNonIntrSeq                   **
**                   (                                                        **
**                     const Spi_SequenceType SeqId,                          **
**                     const Spi_JobType JobId                                **
**                   )                                                        **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : SeqId - Sequence Id                                      **
**                   JobId - JobId                                            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : Priority - Priority for the Job                          **
**                                                                            **
** Description     : This function gives the priority for the Job.            **
**                   Wrt Interruptible sequences, the priority of the job     **
**                   is as configured. However, for Non_Interruptible         **
**                   sequences the priority of all the jobs in that seqience  **
**                   is elevated to the highest priority configured for any   **
**                   job in that sequence                                     **
*******************************************************************************/
static uint8 Spi_lModPrioforNonIntrSeq
(
  const Spi_SequenceType SeqId,
  const Spi_JobType JobId
)
{
  Spi_JobType JobCounter, JobIndex;
  uint8 JobPriority = 0U;

  /* Get the core configuration */
  const Spi_CoreConfigType *CoreConfigPtr =                               \
      Spi_kGlobalConfigPtr->CoreConfigPtr[Mcal_GetCpuIndex()];

  /* return the priority of job as is if sequence is interruptible */
  #if(SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON)
  /* [cover parentID={42CD85A3-6B39-48c9-A2C7-37020049037C}]
  Return the priority of job
  [/cover] */
  if(CoreConfigPtr->SequenceConfigPtr[SeqId].SeqInterruptible ==          \
      SPI_SEQ_INT_TRUE)
  {
    JobPriority = CoreConfigPtr->JobConfigPtr[JobId].JobPriority;
  }
  else
  #else
  UNUSED_PARAMETER(JobId);
  #endif /* SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON */
  {
    /* [cover parentID={44AE22C9-F8F6-4b9c-9D5B-D926ABCA66DB}]
    Traverse through job list and return high priority job
    [/cover] */
    /* Traverse through all the jobs in the list */
    JobCounter = 0U;
    while(CoreConfigPtr->SequenceConfigPtr[SeqId].JobLinkPtrPhysical[      \
          JobCounter] != SPI_JOB_DELIMITER)
    {
      JobIndex = CoreConfigPtr->SequenceConfigPtr[SeqId].               \
                 JobLinkPtrPhysical[JobCounter];

      /* Check for the highest priority*/
      if(JobPriority < CoreConfigPtr->JobConfigPtr[JobIndex].JobPriority)
      {
        JobPriority = CoreConfigPtr->JobConfigPtr[JobIndex].JobPriority;
      }
      JobCounter++;
    }
  }

  /* return highest priority */
  return JobPriority;
} /* End of function Spi_lModPrioforNonIntrSeq */
#endif /* SPI_LEVEL_DELIVERED != 0U */

#if(SPI_LEVEL_DELIVERED != 0U)
/*******************************************************************************
** Traceability     : [cover parentID={51FDF870-1073-4077-BC89-E37B4E6ADC23}] **
** Syntax          : static void Spi_lAsyncStartJob(const Spi_JobType Job)    **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Asynchronous                                             **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : None                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : This function sets up the job for asynchronous           **
**                   transmission. Available for Level 1 or 2.                **
*******************************************************************************/
static void Spi_lAsyncStartJob(const Spi_JobType Job)
{
  const Spi_JobConfigType* JobConfigPtr;
  uint8 HwUnit;
  uint8 CsPolarity = 0;
  /* Get core configuration */
  uint32 CoreId = Mcal_GetCpuIndex();
  const Spi_CoreConfigType *CoreConfigPtr =
      Spi_kGlobalConfigPtr->CoreConfigPtr[CoreId];

  /* [cover parentID={E03B4A28-49C5-4dc6-8694-966A63581AE5}]
   Fetch the job configuration and set Job Status to pending
  [/cover] */
  JobConfigPtr = &CoreConfigPtr->JobConfigPtr[Job];

  /* Set Job Status to SPI_JOB_PENDING */
  Spi_RuntimeCoreVar[CoreId]->JobStatus[Job] = SPI_JOB_PENDING;

  /* Set Job parameters */
  Spi_lHwSetJobConfig(JobConfigPtr, SPI_ASYNC_COMMS_TYPE);

  /* [cover parentID={3ED49245-8513-46fe-A696-3973162D5832}]
   Set DMA Rx Channel
  [/cover] */
  Spi_lSetDmaTcs(Job, SPI_DMA_RX_CHANNEL);

  HwUnit = JobConfigPtr->HwUnit & SPI_HWUNIT_MASK;
  Spi_RuntimeKernelVar[HwUnit]->JobQueuePtr->CurrentChannelIndex =  0U;

  /* [cover parentID={C052C458-BCFC-4aee-91E4-A4B17508D776}]
   Set DMA Tx Channel
  [/cover] */
  Spi_lSetDmaTcs(Job, SPI_DMA_TX_CHANNEL);

  /* [cover parentID={13DF78F4-3176-4f5f-8AF2-01FB8A57BF5F}][/cover] */
  /* Assert CS if CS is a GPIO */
  if(JobConfigPtr->CSPortPin != SPI_CS_VIA_HW_OR_NONE)
  {
    if(JobConfigPtr->CsPolarity == (uint8)STD_LOW)
    {
      CsPolarity = (uint8)STD_HIGH ;
    }
    else
    {
      CsPolarity = (uint8)STD_LOW;
    }
    Spi_lSetCsViaGpio(
      (uint8)((JobConfigPtr->CSPortPin) >> (uint16)SPI_PORT_NUM_OFFSET),     \
      (uint8)((JobConfigPtr->CSPortPin) & SPI_BIT_MASK_3_TO_0),    \
      (CsPolarity));
  }

  /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access.
     No side effects foreseen by violating this MISRA rule. */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access.
     No side effects foreseen by violating this MISRA rule, as the pointer
     to the object type that it is getting cast into, is a known type. */
  SPI_HW_MODULE[HwUnit].BACONENTRY.U =
                   Spi_RuntimeKernelVar[HwUnit]->BaconChannelArray[0].U;

} /* End of function Spi_lAsyncStartJob */
#endif /* SPI_LEVEL_DELIVERED != 0U */

#if(SPI_LEVEL_DELIVERED != 0U)

/*******************************************************************************
** Traceability     : [cover parentID={A80AB1A9-E50C-4f56-93B1-01A34D89D16E}] **
** Syntax          : static void Spi_lSetDmaTcs                               **
**                   (                                                        **
**                     const Spi_JobType JobId,                               **
**                     const uint8 DmaChannelType                             **
**                   )                                                        **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant                                                **
**                                                                            **
** Parameters (in) : JobId - Job Id                                           **
**                   DmaChannelType - DMA CH type, Rx or Tx                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : Configures the Transaction Control Sets per each         **
**                   channel for the Job                                      **
*******************************************************************************/
static void Spi_lSetDmaTcs(const Spi_JobType JobId, const uint8 DmaChannelType)
{
  const Spi_JobConfigType* JobConfigPtr;
  const Spi_ChannelConfigType* ChConfigPtr = NULL_PTR;
  Dma_ConfigUpdateType DmaTCSVar = {0U};
  Spi_DmaTCSType* SpiDmaTCSPtr;
  uint8 ChnlId = 0U;
  uint8 ChnlIndex, DmaChannelNum;
  uint8 HwId;
  uint8 ToggleCs;
  /* Set Channel configuration. configure Bacon */
  /* MISRA2012_RULE_19_2_JUSTIFICATION: register type Definition */
  Ifx_QSPI_BACON lBacon;

  /* Get core information */
  uint32 CoreId = Mcal_GetCpuIndex();
  const Spi_CoreConfigType *CoreConfigPtr =
    Spi_kGlobalConfigPtr->CoreConfigPtr[CoreId];
  JobConfigPtr = &CoreConfigPtr->JobConfigPtr[JobId];
  ToggleCs = CoreConfigPtr->JobConfigPtr[JobId].FramebasedCs;

  /* get the HW kernel */
  HwId = JobConfigPtr->HwUnit & SPI_HWUNIT_MASK;


  /* [cover parentID={5970DD8B-3880-4ca8-A822-C62CF841EC6E}]
     Check if RX or TX DMA TCS are to be operated on
     [/cover] */
  /* DMA TCS configuration for TX or for RX */
  if(DmaChannelType == SPI_DMA_TX_CHANNEL)
  {
    SpiDmaTCSPtr = Spi_RuntimeKernelVar[HwId]->JobQueuePtr->DmaTxTCSPtr;
    DmaChannelNum = CoreConfigPtr->QSPIHwConfigPtr[HwId]->DMATxChannel;
  }
  else
  {
    SpiDmaTCSPtr = Spi_RuntimeKernelVar[HwId]->JobQueuePtr->DmaRxTCSPtr;
    DmaChannelNum = CoreConfigPtr->QSPIHwConfigPtr[HwId]->DMARxChannel;
  }

  /* [cover parentID={4AE06E53-0D11-4671-B934-5AA1569A3F5F}]
   Loop through all channels of job
   [/cover] */
  /* Loop through all the channels of a job */
  ChnlIndex = 0U;
  while(JobConfigPtr->ChnlLinkPtrPhysical[ChnlIndex] != SPI_CHANNEL_DELIMITER)
  {
    ChnlId = JobConfigPtr->ChnlLinkPtrPhysical[ChnlIndex];
    ChConfigPtr = &CoreConfigPtr->ChannelConfigPtr[ChnlId];

    /* Set Transfer count */
    SpiDmaTCSPtr[ChnlIndex].DmaCHCFGR.B.TREL =                                \
        Spi_RuntimeCoreVar[CoreId]->ChannelBufPointers[ChnlId].          \
        TransferLength;

    /* Set the data-width to be transmitted */
    /* 0, 1 or 2 represents 8-bit, 16-bit or 32-bit
          Spi_lGetChannelDataWidth returns the size of elements so check and
          subtract again for 4-byte elements */
    /* [cover parentID={95C23639-E2FE-44fe-9AD5-FBE7F79DB470}][/cover] */
    SpiDmaTCSPtr[ChnlIndex].DmaCHCFGR.B.CHDW =                                \
        (Spi_lGetChannelDataWidth(ChConfigPtr) - (uint8)1);
    if(SpiDmaTCSPtr[ChnlIndex].DmaCHCFGR.B.CHDW == 3U)
    {
      SpiDmaTCSPtr[ChnlIndex].DmaCHCFGR.B.CHDW = (SpiDmaTCSPtr[ChnlIndex].  \
          DmaCHCFGR.B.CHDW - 1U);
    }
    /* Link the next TCS to form the linked list */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: The SFR needs to be programmed
       with the address of the buffer used for the DMA Tx channel
       transaction control set. Hence the address is typecasted to uint32 */
    /* MISRA2012_RULE_11_6_JUSTIFICATION: The SFR needs to be programmed
       with the address of the buffer used for the DMA Tx channel
       transaction control set. Hence the address is typecasted to uint32 */
    SpiDmaTCSPtr[ChnlIndex].DmaSHADR.U = (uint32)&SpiDmaTCSPtr[ChnlIndex + 1U];

    /* [cover parentID={77F72D36-0391-4ff3-AC4D-49582367C15C}]
       Check if RX DMA TCS is
       configured - Level1, Level2 Async transmission mechaism
       [/cover] */
    /* Check if RX TCS is configured */
    if(DmaChannelType == SPI_DMA_RX_CHANNEL)
    {
      if(ChnlIndex > 0U)
      {
          /* ICH bit is cleared from hardware on reloading of TCS,
          so to retain the status this bit is to be SET by the SPI driver
          which is copied from DMA ME engine */
        SpiDmaTCSPtr[ChnlIndex].DmaCHCSR.B.ICH = SPI_RETAIN_ICH_BIT_STATUS;
      }
      SpiDmaTCSPtr[ChnlIndex].DmaADICR.U = SPI_DMA_RX_ADICR_VAL;

      /* Check if received data can be ignored */
      #if((SPI_LEVEL_DELIVERED != 0U) && (SPI_CHANNEL_BUFFERS_ALLOWED != 0U))
      /* [cover parentID={251A3C26-7C4E-4bff-B1D8-134272075106}]
       Destination pointer is null
      [/cover] */
      /* [cover parentID={DF300986-E132-4652-BB75-51F09F6294E5}][/cover] */
      if(Spi_RuntimeCoreVar[CoreId]->ChannelBufPointers[ChnlId].       \
          DestPtr == NULL_PTR)
      {
        /* [cover parentID={FC571789-02A4-45d1-B0E4-58BE25E706CC}]
         Point to dummy variable to hold the received data and
         enable circular buffer
        [/cover] */
        /* MISRA2012_RULE_11_6_JUSTIFICATION: The SFR needs to be programmed
           with the address of the DummyRead variable. Hence the address
           is typecasted to uint32. */
        /* MISRA2012_RULE_11_4_JUSTIFICATION: The SFR needs to be programmed
           with the address of the DummyRead variable. Hence the address
           is typecasted to uint32. */
        SpiDmaTCSPtr[ChnlIndex].DmaDADR.U =                               \
            (uint32)&Spi_RuntimeKernelVar[HwId]->DummyRead;

        /* Enable circular buffer */
        SpiDmaTCSPtr[ChnlIndex].DmaADICR.U = SPI_DMA_ADICR_DEST_NULL;
      }
      else
      #endif /* SPI_LEVEL_DELIVERED != 0U &&
        SPI_CHANNEL_BUFFERS_ALLOWED != 0U */
        {
          /* Point to destination buffer of channel */
          /* MISRA2012_RULE_11_4_JUSTIFICATION: The SFR needs to be programmed
             with the address of Destination buffer. Hence the address
             is typecasted to uint32. */
          /* MISRA2012_RULE_11_6_JUSTIFICATION: The SFR needs to be programmed
             with the address of Destination buffer. Hence the address
             is typecasted to uint32. */
          SpiDmaTCSPtr[ChnlIndex].DmaDADR.U = \
         (uint32)Spi_RuntimeCoreVar[CoreId]->ChannelBufPointers[ChnlId].DestPtr;

          /* Disable Circular buffer for Destination */

          SpiDmaTCSPtr[ChnlIndex].DmaADICR.B.DCBE = (uint8)0U;
        }


        /* [cover parentID={C4EBA7CA-BB56-42ff-9E8C-57542DDFDE07}]
           Setup DMA interrupt based on polling / interrupt mode
           [/cover] */
        /* Enable DMA RX complete event of DMA -
            callback after every channel RX */
      #if(SPI_LEVEL_DELIVERED == 2U)
        if(Spi_RuntimeCoreVar[CoreId]->AsyncMode == SPI_POLLING_MODE)
        {
          SpiDmaTCSPtr[ChnlIndex].DmaADICR.B.INTCT = SPI_DMA_DISABLE_INTR;
        }
        else
      #endif
        {
          SpiDmaTCSPtr[ChnlIndex].DmaADICR.B.INTCT = SPI_DMA_ENABLE_INTR;
        }
    }
    else
    {      /* SPI_DMA_TX_CHANNEL */
      /* compute BACON for the channels in a JOB */
      lBacon = Spi_lHwSetChannelConfig(ChnlId, JobConfigPtr, ToggleCs);
      Spi_RuntimeKernelVar[HwId]->BaconChannelArray[ChnlIndex].U = lBacon.U;

      /* Configure the DMA TCS for Tx registers */
      SpiDmaTCSPtr[ChnlIndex].DmaADICR.U = SPI_DMA_TX_ADICR_VAL;

      /* Check if the default data to be transmitted */
      /* [cover parentID={733BDC3A-A148-4658-B0AB-70059CA5A896}]
       Source pointer is null
      [/cover] */
      if(Spi_RuntimeCoreVar[CoreId]->                                      \
          ChannelBufPointers[ChnlId].SrcPtr == NULL_PTR)
      {
        /* [cover parentID={99D1F2CE-B119-4748-8645-92A7016871B2}]
         Enable circular buffer point to default data location
        [/cover] */
        /* MISRA2012_RULE_11_4_JUSTIFICATION: The SFR needs to be programmed
           with the address of the Defaultdata variable. Hence the address
           is typecasted to uint32. */
        /* MISRA2012_RULE_11_6_JUSTIFICATION: The SFR needs to be programmed
           with the address of the Defaultdata variable. Hence the address
           is typecasted to uint32. */
        SpiDmaTCSPtr[ChnlIndex].DmaSADR.U = (uint32) &ChConfigPtr->Defaultdata;
        SpiDmaTCSPtr[ChnlIndex].DmaADICR.U = SPI_DMA_ADICR_SRC_NULL;
      }
      /* [cover parentID={98383495-689C-47cd-B91F-7BD18398DFA6}]
       Source pointer is not null
      [/cover] */
      else
      {
        /* Point to source address */
        /* MISRA2012_RULE_11_4_JUSTIFICATION: The SFR needs to be programmed
           with the address of the Sorce buffer. Hence the address
           is typecasted to uint32. */
        /* MISRA2012_RULE_11_6_JUSTIFICATION: The SFR needs to be programmed
           with the address of the Sorce buffer. Hence the address
           is typecasted to uint32. */
        SpiDmaTCSPtr[ChnlIndex].DmaSADR.U = \
        (uint32)Spi_RuntimeCoreVar[CoreId]->ChannelBufPointers[ChnlId].SrcPtr;

        /* Disable Circular buffer for Source */
        SpiDmaTCSPtr[ChnlIndex].DmaADICR.B.SCBE = (uint8)0U;
      }
    }

    ChnlIndex++;
  }

  /* Last node of the Linked list - should point to NULL */
  SpiDmaTCSPtr[ChnlIndex - 1U].DmaSHADR.U = (uint32)NULL_PTR;

  /* Last node should not have the DMA linked list enabled */
  SpiDmaTCSPtr[ChnlIndex - 1U].DmaADICR.B.SHCT = (uint8)0U;

  /* Update DMA TCS variables as per DMA data structure */
  DmaTCSVar.SourceAddress = SpiDmaTCSPtr[0U].DmaSADR.U;
  DmaTCSVar.DestAddress = SpiDmaTCSPtr[0U].DmaDADR.U;
  DmaTCSVar.ControlAdicr = SpiDmaTCSPtr[0U].DmaADICR.U;
  DmaTCSVar.ControlChcsr = SpiDmaTCSPtr[0U].DmaCHCSR.U;
  DmaTCSVar.Config = SpiDmaTCSPtr[0U].DmaCHCFGR.U;
  DmaTCSVar.ShadowConfig = SpiDmaTCSPtr[0U].DmaSHADR.U;

  DmaTCSVar.UpdateSourceAddress = 1U;
  DmaTCSVar.UpdateDestAddress = 1U;
  DmaTCSVar.UpdateControlChcsr = 1U;
  DmaTCSVar.UpdateControlAdicr = 1U;
  DmaTCSVar.UpdateConfig = 1U;
  DmaTCSVar.UpdateShadowConfig = 1U;

  /*
   * last channel / one channel - do not update shadow channel else trap will
   * occur in DMA while updating shadow register
   * */
  /* Only 1 channel to be transmitted, so do not update shadow */
  if((ChnlIndex - 1U) == 0U)
  {
    DmaTCSVar.UpdateShadowConfig = 0U;
  }

  /* Update DMA registers for transfer */
  /* MISRA2012_RULE_1_3_JUSTIFICATION: Configuration information passed to DMA
   * module, variable is declared local to function.  */
  Dma_ChUpdate(DmaChannelNum, &DmaTCSVar, NULL_PTR);

  /* Enable Hardware trigger */
  Dma_ChEnableHardwareTrigger(DmaChannelNum);

} /* End of function Spi_lSetDmaTcs */
#endif /* SPI_LEVEL_DELIVERED != 0U */

#if(SPI_LEVEL_DELIVERED == 2U)
/*******************************************************************************
** Traceability     : [cover parentID={22677AA6-478D-489d-9703-8E1EF11060D0}] **
** Syntax          : static void Spi_lModMainFunction                         **
**                   (                                                        **
**                     const uint8 Module                                     **
**                   )                                                        **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Non Reentrant                                            **
**                                                                            **
** Parameters (in) : Module - QSPI Hw module index                            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : Performs Polling operation to propagate the state        **
**                   machine for Job transmission per QSPI module             **
*******************************************************************************/
static void Spi_lModMainFunction(const uint8 Module)
{
  uint8 DmaRxCh;
  uint8 DmaRxChStatus= E_NOT_OK;
  uint32 ChannelEvent;
  uint8 Pt2Status = 0;
  /* Get core configuration */
  const Spi_CoreConfigType *CoreConfigPtr =                               \
      Spi_kGlobalConfigPtr->CoreConfigPtr[Mcal_GetCpuIndex()];

  /* [cover parentID={48044264-4061-4067-A455-DDA223B6ED1C}]
      Check if any error occured during transmission
      [/cover] */
  /* Check if any QSPi error occured */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access.
     No side effects foreseen by violating this MISRA rule, as
     the pointer to the object type that it is getting cast into,
     is a known type. */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access.
     No side effects foreseen by violating this MISRA rule. */
  if((SPI_HW_MODULE[Module].STATUS.B.ERRORFLAGS & SPI_GLOBALCON1_ERROREN)    \
      == 0U)
  {
    /* Check if DMA RX channel is asserted */
    DmaRxCh = CoreConfigPtr->QSPIHwConfigPtr[Module]->DMARxChannel;
    ChannelEvent = Dma_GetEvents(DmaRxCh);
    if (((uint32)ChannelEvent & (uint32)DMA_EVENT_CH_TRANSFER_COMPLETE) ==
                  (uint32)DMA_EVENT_CH_TRANSFER_COMPLETE)
    {
      DmaRxChStatus = E_OK;
    }
    /* [cover parentID={1F0BC9DF-90B9-43ba-9692-12BE94F85FF9}]
    Check if DMA transfer is complete for a channel
    [/cover] */
    /* Clear status and call DMA Rx handler */
    if(DmaRxChStatus == E_OK)
    {
      Dma_ChStatusClear(DmaRxCh, DMA_EVENT_CH_TRANSFER_COMPLETE);
      Spi_lIsrDmaQspiRx(Module);
    }
    /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
     * effects foreseen by violating this MISRA rule, as the pointer to
     * the object type that it is getting cast into, is a known type.  */
    /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
    effects foreseen by violating this MISRA rule, as the pointe
    r to the object type that it is getting cast into, is a known type. */
    Pt2Status = (uint8) (SPI_HW_MODULE[Module].STATUS.B.PT2F);
    if(Pt2Status == SPI_TRIGGER_ENABLE)
    {
      Spi_lQspiTriggerNextJob(Module, SPI_SID_MAINFUNCTION_HANDLING,
                                                 Pt2Status);
      /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
       * effects foreseen by violating this MISRA rule.  */
      /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
      effects foreseen by violating this MISRA rule, as the pointer
      to the object type that it is getting cast into, is a known type. */
      SPI_HW_MODULE[Module].FLAGSCLEAR.B.PT2C = 1U;
    }
  }
  else
  {
    /* Stops the current job */
    Spi_lErrorHandler(Module);
    /* Clear Error Flags */
    /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
    effects foreseen by violating this MISRA rule, as the pointer
    to the object type that it is getting cast into, is a known type. */
    /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
     * effects foreseen by violating this MISRA rule.  */
    SPI_HW_MODULE[Module].FLAGSCLEAR.U = (SPI_QSPI_FLAGSCLEAR_VALUE);
  }
} /* End of function Spi_lModMainFunction */
#endif /* SPI_LEVEL_DELIVERED == 2U */


#if(SPI_LEVEL_DELIVERED != 0U)
/*******************************************************************************
** Traceability     : [cover parentID={3530681A-C404-4b49-BFAB-D685D44AD01A}] **
** Syntax          : static void Spi_lDisQspiErrIntr(const uint8 Module)      **
**                                                                            **
** Service ID      : None                                                     **
**                                                                            **
** Sync/Async      : Synchronous                                              **
**                                                                            **
** Reentrancy      : Reentrant for different QSPI HW                          **
**                                                                            **
** Parameters (in) : Module - QSPI Hw module index                            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description     : Disable QSPI error interrupts                            **
*******************************************************************************/
static void Spi_lDisQspiErrIntr(const uint8 Module)
{
  /* MISRA2012_RULE_19_2_JUSTIFICATION: register type Definition */
  Ifx_QSPI_GLOBALCON1 GlobalCon1Reg;

  /* Disable QSPI Hw errors */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
  effects foreseen by violating this MISRA rule, as the pointer
  to the object type that it is getting cast into, is a known type. */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
   * effects foreseen by violating this MISRA rule.  */
  GlobalCon1Reg.U = SPI_HW_MODULE[Module].GLOBALCON1.U;

  /* Clear TXEN, RXEN, PT2EN and ERRORENS */
  GlobalCon1Reg.U &= ~(SPI_GLOBALCON1_INT_MASK);

  /* MISRA2012_RULE_11_5_JUSTIFICATION: QSPI base address access. No side
  effects foreseen by violating this MISRA rule, as the pointer
  to the object type that it is getting cast into, is a known type. */
  /* MISRA2012_RULE_11_3_JUSTIFICATION: QSPI base address access. No side
   * effects foreseen by violating this MISRA rule.  */
  SPI_SFR_RUN_TIME_WRITE32(&SPI_HW_MODULE[Module]. \
                                        GLOBALCON1.U, GlobalCon1Reg.U);
} /* End of function Spi_lDisQspiErrIntr */
#endif /* SPI_LEVEL_DELIVERED != 0U */

#if(SPI_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={915D92BA-7839-484c-B61F-DC93CE6F874B}] **
**                                                                            **
** Syntax           : void  Spi_GetVersionInfo                                **
**                    (                                                       **
**                      Std_VersionInfoType *const versioninfo                **
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
******************************************************************************/
void Spi_GetVersionInfo(Std_VersionInfoType *const versioninfo)
{
  /* [cover parentID={DF5746C4-53DB-4efd-A796-9F2AEFA1375C}]
    Spi_GetVersionInfo
  [/cover] */
  /* [cover parentID={B6458B54-CDE1-4457-95AA-BAF96859DDFC}]
   Check if input pointer is not valid
  [/cover] */
  /* [cover parentID={37F066FC-B3FC-4166-A06E-3976CF7B67FD}]
   Input pointer is not valid
  [/cover] */
  /* [cover parentID={DCD19E67-07CD-45e9-8518-773C548AA7ED}][/cover] */
  #if ((SPI_DEV_ERROR_DETECT == STD_ON) || (SPI_SAFETY_ENABLE == STD_ON))
  if((versioninfo) == (NULL_PTR))
  {
    /* [cover parentID={438EC4B6-DA36-4531-8547-39EB204C9A0D}]
     Report error as SPI_E_PARAM_POINTER
    [/cover] */
    Spi_lReportError( SPI_SID_GETVERSIONINFO,
                      SPI_E_PARAM_POINTER);
  }
  else
  #endif
  {
    /* [cover parentID={3BDED06B-B0A6-4d89-B24A-9FB1DF3CBD51}][/cover] */
    /* SPI Module ID */
    ((Std_VersionInfoType*)(versioninfo))->moduleID = SPI_MODULE_ID;
    /* SPI vendor ID */
    ((Std_VersionInfoType*)(versioninfo))->vendorID = SPI_VENDOR_ID;
    /* Major version of SPI */
    ((Std_VersionInfoType*)(versioninfo))->sw_major_version =
      (uint8)SPI_SW_MAJOR_VERSION;
    /* Minor version of SPI */
    ((Std_VersionInfoType*)(versioninfo))->sw_minor_version =
      (uint8)SPI_SW_MINOR_VERSION;
    /* Patch version of SPI */
    ((Std_VersionInfoType*)(versioninfo))->sw_patch_version =
      (uint8)SPI_SW_PATCH_VERSION;
  }
}

#endif

/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}][/cover] */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
 * because of AS naming convention*/
#define SPI_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Spi_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
 * guideline. */
#include "Spi_MemMap.h"

/* End Of File */
