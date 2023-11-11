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
**  FILENAME     : Fee.h                                                      **
**                                                                            **
**  VERSION      : 21.0.0                                                     **
**                                                                            **
**  DATE         : 2023-05-16                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Fee Driver header definition file                          **
**                                                                            **
**  SPECIFICATION(S) : Specification of Fee Driver,                           **
**                     AUTOSAR Release 4.2.2 and 4.4.0                        **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/* [cover parentID={EDF07109-7688-4815-8863-184718D1F4F9}] Fee.h
[/cover] */
/* [cover parentID={B8A44088-DF56-41df-97E2-3A6928B72E09}]Header file structure
[/cover] */

#ifndef  FEE_H
#define  FEE_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/* Inclusion of Std_Types.h  */
#include "Std_Types.h"

#include "Mcal_Compiler.h"

/* Fee Module Configuration header file */
#include "Fee_Cfg.h"

/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/* [cover parentID={A68F697B-2F7E-418d-9A31-3070DF10D036}]Vendor and module IDs
[/cover] */
/* Published parameters */

/* FEE Vendor ID */
#define FEE_VENDOR_ID                  ((uint16)17)

/* FEE Module ID */
#define FEE_MODULE_ID                  ((uint16)21)

/* FEE instance ID */
#define FEE_INSTANCE_ID                ((uint8)0)

#if (FEE_DEV_ERROR_DETECT  == STD_ON) || (FEE_SAFETY_ENABLE == STD_ON)
/* Development error values - DET's */
/* API service called with wrong parameter */
#define FEE_E_UNINIT                 ((uint8)0x01)
#define FEE_E_INVALID_BLOCK_NO       ((uint8)0x02)
#define FEE_E_INVALID_BLOCK_OFS      ((uint8)0x03)
#define FEE_E_PARAM_POINTER          ((uint8)0x04)
#define FEE_E_INVALID_BLOCK_LEN      ((uint8)0x05)
#if(FEE_SAFETY_ENABLE == STD_ON)
#define FEE_SE_INVALID_BLOCK_INSTANCES ((uint8)0x20)
#define FEE_SE_UNINIT                 ((uint8)0x01)
#define FEE_SE_INVALID_BLOCK_NO       ((uint8)0x02)
#define FEE_SE_INVALID_BLOCK_OFS      ((uint8)0x03)
#define FEE_SE_PARAM_POINTER          ((uint8)0x04)
#define FEE_SE_INVALID_BLOCK_LEN      ((uint8)0x05)
#define FEE_SE_BUSY                   ((uint8)0x06)
#define FEE_SE_INVALID_CANCEL         ((uint8)0x08)
#endif
#endif

#define FEE_SID_CANCEL               ((uint8)4)
#define FEE_SID_INVALIDATEBLOCK      ((uint8)7)

#if (FEE_DEV_ERROR_DETECT  == STD_ON) || (FEE_SAFETY_ENABLE == STD_ON) \
  || (FEE_RUNTIME_ERROR_DETECT == STD_ON)
#define FEE_E_BUSY                   ((uint8)0x06)
#define FEE_E_INVALID_CANCEL         ((uint8)0x08)

/* API Service ID's */
#define FEE_SID_INIT                 ((uint8)0)
#define FEE_SID_SETMODE              ((uint8)1)
#define FEE_SID_READ                 ((uint8)2)
#define FEE_SID_WRITE                ((uint8)3)
#define FEE_SID_GETSTATUS            ((uint8)5)
#define FEE_SID_GETJOBRESULT         ((uint8)6)
#define FEE_SID_GETVERSIONINFO       ((uint8)8)
#define FEE_SID_JOBENDNOTIF          ((uint8)16)
#define FEE_SID_JOBERRORNOTIF        ((uint8)17)



/*For Non Autosar API*/
#define FEE_SID_CANCELALL                 ((uint8)0x28)
#define FEE_SID_DISABLEGCSTART            ((uint8)0x22)
#define FEE_SID_ENABLEGCSTART             ((uint8)0x21)
#define FEE_SID_ERASEQUASISTATICDATA      ((uint8)0x25)
#define FEE_SID_GETCYCLECOUNT             ((uint8)0x20)
#define FEE_SID_GETPREVDATA               ((uint8)0x23)
#define FEE_SID_GETQUASISTATICBLOCKINFO   ((uint8)0x26)
#define FEE_SID_GETQUASISTATICJOBRESULT   ((uint8)0x27)
#define FEE_SID_ILLEGALSTATENOTIFICATION  ((uint8)0x24)
#define FEE_SID_JOBERASEERRORNOTIF        ((uint8)0x29)
#define FEE_SID_INITCHECK                 ((uint8)0x30)
#define FEE_SID_JOBPROGERRORNOTIF         ((uint8)0x31)
#define FEE_SID_GETECCERRORINFO           ((uint8)0x32)
#endif
/* FEE_DEV_ERROR_DETECT */

#define FEE_UNCONFIG_BLOCK_IGNORE    (0U)
#define FEE_UNCONFIG_BLOCK_KEEP      (1U)

#define FEE_CACHE_EXTRA_BUFFER_COUNT (10U)
#define FEE_TOTAL_BLOCK_COUNT        ((FEE_MAX_BLOCK_COUNT) + \
                                      (FEE_CACHE_EXTRA_BUFFER_COUNT))

#define FEE_GC_RESTART_INIT          (0U)
#define FEE_GC_RESTART_WRITE         (1U)

#define FEE_ERASE_SUSPEND_ENABLED    (1U)
#define FEE_ERASE_SUSPEND_DISABLED   (0U)

#define FEE_DATA_PAGE_COUNT          (FLS_NVM_SECTOR_SIZE/FLS_PAGE_SIZE)
#define FEE_DFLASH_PAGE_SIZE         (FLS_17_DMU_PAGE_SIZE)
#define FEE_MARKPAGE_ARR_COUNT       ((uint8)(FEE_DATA_PAGE_COUNT/32U))
#define FEE_SECTORS                  (2U)

/* Repair result values */
#define FEE_REPAIR_FAILED            (0U)
#define FEE_REPAIR_SUCCESSFUL        (1U)
#define FEE_REPAIR_ONGOING           (2U)

/* Minimum block size is 2 pages (16 bytes) for invalidated block */
#define FEE_MIN_BLK_SIZE             (16U)
/* Maximum number of blocks which can be accommodated in a wordline */
#define FEE_MAX_NUM_OF_BLKS_IN_WL    (FEE_DFLASH_WORDLINE_SIZE/FEE_MIN_BLK_SIZE)

#define FEE_DOUBLE_SECTOR_DATA_ONLY  (0U)
#define FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA (1U)
#define FEE_QUASI_STATIC_DATA_ONLY (2U)

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
/* [cover parentID={DFDA8AAB-758A-4537-B0FB-7C1320004FB4}] [/cover] */
typedef uint16  Fee_PageType;

/* [cover parentID={35E59B6D-DE64-426b-9EC6-4CB341C21306}] [/cover] */
typedef enum
{
  FEE_NORMAL_DATA = 0U,
  FEE_IMMEDIATE_DATA,
} Fee_DataType;

/* [cover parentID={94B95B8F-17E8-4e3c-8AB0-0BD04BB88151}] [/cover] */
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
typedef enum
{
  FEE_NVM_USER = 0U,
  FEE_QUASI_STATIC_USER
} Fee_UserType;
#endif

/* [cover parentID={48F05845-0CC3-4fdc-B7A7-1CD8EAB7B24D}] [/cover] */
typedef enum
{
  FEE_QS_PROG_STATE_ERASE_STARTED = 0,
  FEE_QS_PROG_STATE_DESTROY,
  FEE_QS_PROG_STATE_ERASE_COMPLETE,
  FEE_QS_PROG_STATE_WRITE_COMPLETE,
  FEE_QS_PROG_STATE_WRITE_STARTED,
  FEE_QS_START_ERASE,
  FEE_QS_START_BCC_WRITE,
  FEE_QS_START_BLOCK_WRITE,
  FEE_QS_ERASE_COMPLETE,
  FEE_QS_DIRTY_ERASE,
  FEE_QS_WRITE_COMPLETE,
  FEE_QS_DIRTY_WRITE,
  FEE_QS_ERASE_STARTED,
  FEE_QS_WRITE_STARTED,
  FEE_QS_DESTROY,
  FEE_QS_INVALID = 25,
} Fee_QsBlock_StateType;

/* Type:Fee_NotifFunctionPtrType                         */
/* Funtion pointer for JobEnd and JobError Notification  */
/* [cover parentID={6F376884-26C0-4922-BEB1-784789EC2E7F}] [/cover] */
typedef void (*Fee_NotifFunctionPtrType)(void);


/* [cover parentID={0A52D233-D3CE-4073-9A1A-57338F04D64F}] [/cover] */
typedef struct
{
  /* Block Cycle count */
  unsigned_int  CycleCountLimit:24;
  /* Data type : Immediate or Normal */
  unsigned_int  FeeImmediateData:8;
  /* Logical Block number */
  unsigned_int  BlockNumber:16;
  /* Size of the logical block */
  unsigned_int  Size:16;
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
  unsigned_int        Address:32;
  unsigned_int Instances:16;
  unsigned_int FeeUser:8;
#endif

} Fee_BlockType;

/********************   Fee_CacheType  ****************************************/
/*
  This is the type of FEE Cache data structure containing
  the overall information about a particular logical block
*/
/* [cover parentID={B4C909AD-5E94-4112-A0F8-392F4444A168}] [/cover] */
typedef struct
{
  /* Valid: Indicates if the DFLASH contains Valid information for block */
  unsigned_int  Valid              : 1;
  /* Consistent: Indicates if the DFLASH contents of the block is consistent*/
  unsigned_int  Consistent         : 1;
  /* Copied: Indicates if the block contents are copied during GC */
  unsigned_int  Copied             : 1;
  /* PrevCopyValid: 'Valid' info for Previous Copy */
  unsigned_int  PrevCopyValid      : 1;
  /* PrevCopyConsistent: 'Consistent' info for Previous Copy */
  unsigned_int  PrevCopyConsistent : 1;
  /* PrevCopyCopied: 'Copied' info for Previous Copy */
  unsigned_int  PrevCopyCopied     : 1;
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
  unsigned_int  QsDirtyWrite              : 1;
  unsigned_int  QsDirtyErase              : 1;
  Fee_QsBlock_StateType    State;
#endif

} Fee_CacheStatusType;

/* [cover parentID={157B1F81-C3EF-492b-ABD1-52F4C66E1817}] [/cover] */
typedef struct
{
  /* Physical Address of the latest copy of logical block */
  uint32  Address;
  uint32 BlockSize;

  /* Logical block number */
  uint16 BlockNumber;

  /* Status information of the latest copy of logical block */
  Fee_CacheStatusType Status;

  /* Physical Address of the previous copy of logical block */
  uint32  PrevCopyAddress;
  uint32  PrevBlkSize;

  uint16 Blkcylcnt;
} Fee_CacheType;

/********************   FeePendReqInfo_Buf  ***********************************/
/*
  This structure will hold the details of the Fee pending request.
*/
/* [cover parentID={FF3B6566-4027-4d8c-89FC-C831B6A74446}] [/cover] */
typedef struct
{
  uint8  *DataBufferPtr;
  const uint8 *DataWriteBufferPtr;
  uint16 BlockNumber;
  uint16 BlockOffset;
  uint16 Length;
#if (FEE_GET_PREV_DATA_API == STD_ON)
  uint8 GetPrevCopy;
#endif
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
  uint16 CacheIndex;
  uint16 BlockInstances;
#endif
} Fee_PendReqBufType;

/********************   Fee_StatusFlagsType  **********************************/
/*
  This structure will have Fee status Flags which will have values with in the
  range of 0 and 1.
*/

/* [cover parentID={1F738E26-581B-4b06-A60A-41864223BE32}] [/cover] */
typedef  struct
{
  /* FeeBlkModified : This variable will indicate if the block contents were */
  /*                modified during Step GC operation                        */
  unsigned_int   FeeBlkModified                  : 1;
  /* FeeStartInitGC : This variable will indicate if the InitGC              */
  /*             can be invoked                                              */
  /* Value - 0   InitGC       cannot be invoked                              */
  /* Value - 1   InitGC       can be invoked                                 */
  unsigned_int   FeeStartInitGC                     : 1;
  /* FeeCurrSector: Stores the current sector on which blocks write          */
  /* operation will be done                                                  */
  /* Value - 0   Current sector is Sector 0                                  */
  /* Value - 1   Current sector is Sector 1                                  */
  unsigned_int   FeeCurrSector            : 1;
  
  /* FeeBlkInvalidStatus: Stores if the Invalidate request for a             */
  /* block is initiated                                                      */
  unsigned_int   FeeBlkInvalidStatus        : 1;
  /* FeeWriteInvldAPICalled: Stores the status if an Fee_Write is executed   */
  /* Value - 0   Fee_Write is not called                                     */
  /* Value - 1   Fee_Write is executed once already                          */
  unsigned_int   FeeWriteInvldQSeraseAPICalled        : 1;
  unsigned_int   unused                        : 2;
} Fee_StatusFlagsType;


/*
  This structure will have Fee status Flags which will have values with in the
  range of 0 and 1.
*/
/* [cover parentID={1EBE1A74-2878-42e6-B8FA-F7A95F9D18AB}] [/cover] */
typedef  struct
{
  /* Dirty : This variable will indicate if the state page is clean / dirty  */
  unsigned_int   Dirty                 : 1;
  /* Used : This variable will indicate if the sector is empty / used        */
  unsigned_int   Used                  : 1;
  unsigned_int   unused                : 6;
} Fee_SectorStatusType;

/*
  This structure will have the information regarding a DFLASH sector
*/
/* [cover parentID={22524E97-B0C3-48df-BE26-AF5C1596EEAB}] [/cover] */
typedef struct
{
  /* state count of the sector */
  uint32 StateCount;

  /* UnerasableWLAddr: Unerasable WL Addr in the sector */
  uint32 UnerasableWLAddr[2];

  /* NonZeroWLAddr: Non Zero WL Addr encountered during Init */
  uint32 NonZeroWLAddr[3];

  /* NonZeroWLCount: Non Zero WL count encountered during Init */
  uint32 NonZeroWLCount;

  /* StatePageAddr: State Page Addr in the sector */
  uint32 StatePageAddr;

  /* NextFreeWLAddr: Addr of the next free WL in the sector */
  uint32 NextFreeWLAddr;
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
  uint16 QsHardeningOffset;
#endif
  /* UnerasableWLCount: Unerasable WL count in the sector */
  uint8 UnerasableWLCount;

  /* State: Sector state: Valid / Erased / Stateless */
  uint8 State;

  /* Status information of the sector:
    Sector Empty / Used
    StatePage Clean/Dirty */
  Fee_SectorStatusType Status;
} Fee_SectorInfoType;

/* [cover parentID={5B76D385-E531-4ba2-809D-44E224D81D3A}] [/cover] */
typedef struct
{
  /* Logical Block address in DFlash */
  uint32  Addr;
  /* Logical Block size in pages */
  Fee_PageType  PageCount;
  /* Logical Block number */
  uint16  BlockNumber;
  /* Status information of the logical block */
  Fee_CacheStatusType Status;
} Fee_LastWrittenBlkInfoType;

/* [cover parentID={33D0234D-F60F-48a6-A1B2-7AF9DEFDBDFF}] [/cover] */
typedef struct
{
  /* Logical Block address in DFlash */
  uint32  Addr;
  /* Logical Block size in pages */
  Fee_PageType  PageCount;
  /* Logical Block number */
  uint16  BlockNumber;
  /* Logical Block Consistent or not */
  uint8   Consistent;
} Fee_GcBlkInfoType;

/* [cover parentID={51EABE40-59E9-4687-9AB9-F98F41F24774}] [/cover] */
/* [cover parentID={883561CF-F5DE-42dd-B54D-89C3ECE4BA1C}] [/cover] */
typedef struct
{
  /* block cycle count */
  uint16 Bcc;
  /* Block state */
  Fee_QsBlock_StateType State;
} Fee_QuasiStaticBlockInfoType;


/* [cover parentID={EC889242-1192-475a-9D35-C745AD69B0AA}] [/cover] */
/* [cover parentID={BE493436-93E9-44dc-9FEB-9A7BEC535893}] [/cover] */
typedef struct
{
  /* FeeSectorInfo : Sector information is stored */
  Fee_SectorInfoType      FeeSectorInfo[FEE_SECTORS];

  /* Fee cache : Block information is stored */
  Fee_CacheType           FeeBlockInfo[FEE_TOTAL_BLOCK_COUNT];

  /* Fee Fee_LastWrittenBlkInfo : Last Written Block information is stored */
  /* This is used to rewrite the affected previous block during Fee_Write
     because of BLWL issue */
  Fee_LastWrittenBlkInfoType      FeeLastWrittenBlkInfo;

  /* Fee FeeGcCurrBlkInfo : Current Block being written during GC,
     the addr is from prev sector */
  Fee_GcBlkInfoType       FeeGcCurrBlkInfo;

  /* FeePendReqInfo: Fee pending request details are stored */
  Fee_PendReqBufType      FeePendReqInfo;

  /* FeeGcLWBGcSrcAddr: Source address of the LWB during GC */
  uint32                  FeeGcLWBGcSrcAddr[FEE_MAX_NUM_OF_BLKS_IN_WL];

  /* FeeTempArray: Stores temporary data */
  uint32                  FeeTempArray[2U];

  /* FeeStateCount: Stores the state count from the latest state page
     in DFLASH */
  uint32                  FeeStateCount;

  /* FeeUserReadWriteBuffer: buffer to pass to the Flash driver        */
  /* NOTE: The array is intentionally placed here so that it is
   * word aligned due to the previous uint32 member
   */
  uint8                   FeeReadWriteBuffer[FEE_DFLASH_WORDLINE_SIZE];
  /* FeeGcReadWriteBuffer: buffer to pass to the Flash driver     */
  /* NOTE: The array is intentionally placed here so that it is
   * word aligned due to the previous uint32 member
   */
  uint8                   FeeGcReadWriteBuffer[FEE_DFLASH_WORDLINE_SIZE];

  /* FeeLastWrittenBlkBuffer: Stores the content of last page of
     previous data block. This is used while re-writing the affected
     previous data block because of BLWL */
  uint8                   FeeLastWrittenBlkBuffer[FEE_DFLASH_WORDLINE_SIZE];

  /* FeeGcDestAddr: Destination Addr for copying data during GC              */
  uint32                  FeeGcDestAddr;

  /* FeeGcSrcAddr: Source Addr from which data needs to be copied during GC  */
  uint32                  FeeGcSrcAddr;

  /* FeeNextFreePageAddr: Stores the next available DFLASH address for       */
  /* next block write                                                        */
  uint32                  FeeNextFreePageAddr;

  /* FeeWriteAffectedAddr: Write affected address */
  uint32                  FeeWriteAffectedAddr;

  /* FeeBlockStartAddr: Stores the start page address of the data block
     during user write / during copy in GC - This is used for cache update
     after successful completion of block write / copy                     */
  uint32                  FeeBlockStartAddr;

  /* FeeCurrSectSrcAddr: Used during InitGc, Cache update and GC to read the
     entire sector and for reading the previous block data during rewrite of
     previous block because of BLWL   */
  uint32                  FeeCurrSectSrcAddr;

  /* FeeUnErasableWLAddrTemp: Temporarily stores the unerasable WL address */
  uint32                  FeeUnErasableWLAddrTemp[2];

  /* FeeUserReadDestPtr: Stores the address of the buffer during read job  */
  uint8*                  FeeUserReadDestPtr;

  /* FeeJobResult: Stores the job result of the ongoing/finished job        */
  MemIf_JobResultType     FeeJobResult;

  /* FeeLastWriteSize: Last write size */
  Fls_17_Dmu_LengthType          FeeLastWriteSize;

  /* FeeLastReadSize: Last read size */
  Fls_17_Dmu_LengthType          FeeLastReadSize;

  /* FeeComparedLen: Last compared size */
  uint16                  FeeComparedLen;

  /* FeeReadLen: Last Read size */
  uint16                  FeeReadLen;

  /* FeeBlkPageCount: Tracks number of DFLASH pages read/written during   */
  /* Fee Write / GC process                                               */
  Fee_PageType            FeeBlkPageCount;

  /* FeeUserWriteBytesCount: Keeps track of the number of bytes written     */
  uint16                  FeeUserWriteBytesCount;

  /* FeeCurrReqBlockNum: Block number of the current request */
  uint16                  FeeCurrReqBlockNum;

  /* FeeIntrCurrReqPageCount: Page count of the current internal request */
  uint16                  FeeIntrCurrReqPageCount;

  /* FeeGCCopyIndex: Tracks the Index of logical blocks covered during      */
  /* GC process                                                             */
  uint16                  FeeGCCopyIndex;

  /* Index of the current un-configured block in cache table */
  uint16                  FeeGCUnconfigBlkCopyIndex;

  /* Number of un-configured blocks in cache table */
  uint16                  FeeUnConfigBlockCount;

  /* FeeGcPrevBlockNumber: Previous block number during GC */
  uint16                  FeeGcPrevBlockNumber;

  /* FeeGcFirstBlkNumInWL: Index of the first block number in the WL */
  uint16                  FeeGcFirstBlkNumInWL;

  /* FeeStatusFlags: This structure will have Fee status Flags which will   */
  /* have values with in the range of 0 and 1.                              */
  Fee_StatusFlagsType     FeeStatusFlags;

  /* FeeLastWrittenBlockDirty: Dirty status of the last block in the sector */
  uint8                   FeeLastWrittenBlockDirty;

  /* FeePendReqStatus: Stores the status of the pending request             */
  uint8                   FeePendReqStatus;

  /* FeeGcState: Garbage Collection State variable to keep track of the    */
  /* current state of of the garbage collection procedure                  */
  uint8                   FeeGcState;

  /* FeeGcResumeState: Indicates the state at which GC was interrupted,
     this helps in deciding the state from which GC shall be resumed       */
  uint8                   FeeGcResumeState;

  /* FeeGcBlkIndexInWL: Block index within WL during GC */
  uint8                   FeeGcBlkIndexInWL;

  /* FeeInitGCState: Stores the current state for Fee initialization process*/
  uint8                   FeeInitGCState;

  /* FeePrepDFLASHState: Stores current state of the preparation of DFLASH  */
  uint8                   FeePrepDFLASHState;

  /* FeeCacheState: Stores current state of the cache update process        */
  uint8                   FeeCacheState;

  /* FeeRepairStep: Stores State page repair status */
  uint8                   FeeRepairStep;

  /* FeeWLAffectedType: Type of corruption */
  uint8                   FeeWLAffectedType;

  /* FeeIntrJob: Stores the current Internal Job */
  uint8                   FeeIntrJob;

  /* FeeIntrJobStatus: Stores the Job status of internal job */
  uint8                   FeeIntrJobStatus;

  /* FeeUserJobStatus: Stores the Job status of user job */
  uint8                   FeeUserJobStatus;

  /* FeeIntrJobResult: Stores the Job result of internal job */
  uint8                   FeeIntrJobResult;

  /* FeeUserJobResult: Stores the Job result of user job */
  uint8                   FeeUserJobResult;

  /* FeeMainJob: Stores the current Main Job */
  uint8                   FeeMainJob;

  /* FeeUserJobFailCount: Stores the number of times the
     comparison during User write failed   */
  uint8                   FeeUserJobFailCount;

  /* FeeIntrJobFailCount: Stores the number of times the
     comparison during GC failed   */
  uint8                   FeeIntrJobFailCount;

  /* FeeUncfgBlksExceeded: Stores the status whether the number of
     un-configured blocks exceeded the configured limit */
  uint8                   FeeUncfgBlksExceeded;

  /* FeeUnErasableWLCountTemp: Temporarily stores unerasable WL count */
  uint8                   FeeUnErasableWLCountTemp;

  /* FeeSectorCount: Stores the present sector count value for which erase
     verification is ongoing/complete in DFLASH */
  uint8                  FeeSectorCount;

#if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
  /* FeeEraseSuspendStatus: Status of Erase suspend */
  uint8                   FeeEraseSuspendStatus;

  /* FeeEraseResumeDemReported: Status of Erase-Resume failure production error 
     report */
  uint8                   FeeEraseResumeDemReported;
#endif
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
  uint16                   FeeQuasiBlkInstanceTemp;
  uint8                   FeeQsEraseSuspend;
  uint8                   FeeQsState;
  uint8                   FeeQsJob;
  uint8                   FeeQsIntrJob;
  uint8                   FeeQsJobStatus;
  uint8                   FeeQsIntrJobStatus;
  uint16                  FeeQsRepairIndex;
  uint8                   FeeInitQSState;
  MemIf_JobResultType     FeeQsJobResult;
  MemIf_JobResultType     FeeQsIntrJobResult;
  Fee_PendReqBufType      FeePendEraseInfo;
  /* FeeTempPendQsInfo: Fee pending high prio request details are stored */
  Fee_PendReqBufType      FeeTempPendQsInfo;
  uint32                  FeeHardeningWLCount;
  uint32                  FeeHardeningPageCount;
  uint32                  FeeQsHardeningOffset;
  boolean                 FeeQsCancelAll;
  uint8                   FeeHardenFlag;
#endif

  /* FeeDisableGCStart: GC Enable/Disable */
  boolean                 FeeDisableGCStart;
  /* Indicate in Immdiate block was written beyond threshold TEST */
  boolean                 FeeGCImmBlkWrite;
   
#if (FEE_CANCELL_ALL_API == STD_ON) && \
    (FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)
  /* Flag to indicate the GC is cancelled by cancel all */ 
  
  uint8 FeeCancelallGCstate;

#endif

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
 /* Variable to count number of QS virgin blocks */
  uint16 FeeQsBlockVirginCount;

#endif

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
 /* Flag to indicate flash erase verify is failed. If this flag is set in GC
 will scan the erased sector to find out un-erasble WL address. for QS erase
 job we give job error notification  */
  uint8 FeeEraseVerErr;
  
   /* Flag to indicate flash program(wite) verify is failed. If this flag is 
   set then retry the program on next to next free WL. for QS program(write)
   job error notification will be raised */
  uint8 FeeProgVerErr;

#endif

#if (FEE_SET_MODE_SUPPORTED == STD_ON) && \
    (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY) && \
    (MCAL_AR_VERSION == MCAL_AR_440)
  boolean FeeSetModeReqPend; 
  MemIf_ModeType FeeChangeReqMode;
#endif



} Fee_StateDataType;

/*[cover parentID={D210EC95-734B-4e3e-8296-D28E5FEFAEBD}][/cover]*/
/*[cover parentID={5FF2B3B1-5484-4f8b-A944-62C7C6E97C03}][/cover]*/
typedef struct
{
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
  /* Flag to configure if configured blocks should be copied       */
  /* Value : FEE_UNCONFIG_BLOCK_IGNORE -> Do not copy              */
  /*         FEE_UNCONFIG_BLOCK_KEEP   -> Copy unconfigured        */
  /*                                      block to the next sector */
  unsigned_int FeeUnconfigBlock   : 1;
#endif
  /* Garbage Collection restarting point                           */
  /* Value : FEE_GC_RESTART_INIT   -> Restart GC at Initialization */
  /*         FEE_GC_RESTART_WRITE  -> Restart GC at First Write    */
  unsigned_int FeeGcRestartPoint : 1;

  /* Erase Suspend Feature ON/OFF */
  unsigned_int FeeUseEraseSuspend:1;
  unsigned_int unused : 5;
} Fee_GCConfigType;

/*
  This is the type of FEE external data structure containing
  the overall initialization data for the FEE Driver
*/
/* [cover parentID={A6C86937-A02A-4fe0-851F-E4217524209E}] [/cover] */

typedef struct
{
  /* Pointer to the state variable data structure */
  Fee_StateDataType       *FeeStatePtr;

  /* Pointer to logical block configurations */
  const Fee_BlockType     *FeeBlockConfigPtr;
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
  /* Job End Notification Call back routine */
  Fee_NotifFunctionPtrType  FeeNvmJobEndNotification;

  /* Job Error Notification Call back routine */
  Fee_NotifFunctionPtrType  FeeNvmJobErrorNotification;
#endif
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
  Fee_NotifFunctionPtrType  FeeQsJobEndNotification;

  Fee_NotifFunctionPtrType  FeeQsJobErrorNotification;
#endif
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
  /* Fee Threshold Limit */
  uint32                    FeeThresholdLimit;
#endif
  /* Derived Config parameter : No. of configured blocks */
  uint16                    FeeBlkCnt;

  /* Fee settings for unconfigured blocks and GC restart */
  Fee_GCConfigType     FeeGCConfigSetting;

  /* Notification pointer in case of Illegal State */
  Fee_NotifFunctionPtrType  FeeNvmIllegalStateNotification;

  /* Notification pointer in case of QS Illegal State */
  Fee_NotifFunctionPtrType  FeeQsIllegalStateNotification;

  /* Notification pointer in case of QS hardening error */
  Fee_NotifFunctionPtrType  FeeQsHardenErrorNotification;

  /* TRUE/FALSE Config parameter for Erase All behaviour */
  boolean FeeEraseAllEnable;

} Fee_ConfigType;

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/


/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/
/* Testing purpose */



/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/

#define FEE_START_SEC_CODE_ASIL_B_LOCAL
#include "Fee_MemMap.h"

#if (FEE_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Syntax : void Fee_GetVersionInfo( Std_VersionInfoType *const               **
**                                      VersionInfoPtr )                      **
**                                                                            **
**                                                                            **
** Service ID:      0x08                                                      **
**                                                                            **
** Sync/Async:      Synchronous                                               **
**                                                                            **
** Reentrancy:      non reentrant                                             **
**                                                                            **
** Parameters (out): versioninfo : Pointer to where to store the version      **
**                                information of this module.                 **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Return value:    none                                                      **
**                                                                            **
** Description :    This service returns the version information of           **
**                  this module.                                              **
**                  The version information includes:                         **
**                  Module Id, Vendor Id, Vendor specific version numbers     **
**                                                                            **
*******************************************************************************/
extern void Fee_GetVersionInfo(Std_VersionInfoType * const VersionInfoPtr);
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when this optional function is called by application and
  not enabled in the configuration*/
#define Fee_GetVersionInfo(VersionInfo) \
                                 (ERROR_Fee_GetVersionInfo_API_IS_NOT_SELECTED)
#endif


/*******************************************************************************
** Syntax : void Fee_Init (const Fee_ConfigType *const ConfigPtr)             **
**                                                                            **
** Service ID:  0x00                                                          **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  ConfigPtr : only NULL_PTR should be passed              **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : Driver Module Initialization function                        **
**         This service shall initialize the Flash EEPROM Emulation module    **
** using the values provided in the configuration set.                        **
*******************************************************************************/
extern void Fee_Init (const Fee_ConfigType *const ConfigPtr);

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
#if (FEE_SET_MODE_SUPPORTED == STD_ON)
/*******************************************************************************
** Syntax : void Fee_SetMode( const MemIf_ModeType Mode )                     **
**                                                                            **
** Service ID:  0x01                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  MemIf_ModeType    Desired mode for the underlying flash **
**                                      driver.                               **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This API sets the mode of the underelying flash driver       **
**                                                                            **
*******************************************************************************/
extern void Fee_SetMode(const MemIf_ModeType Mode );
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when this optional function is called by application and
  not enabled in the configuration*/
#define Fee_SetMode(Mode) \
(ERROR_Fee_SetMode_API_IS_NOT_SELECTED)
#endif

#if (FEE_GET_CYCLE_COUNT_API == STD_ON)
/*******************************************************************************
** Syntax : Std_ReturnType Fee_17_GetCycleCount(const uint16 BlockNumber,     **
**                                              uint32 * const CountPtr)      **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in):  BlockNumber - Logical Block Number                       **
**                                                                            **
** Parameters (out) :  CountPtr - Pointer to the variable to which the Erase  **
**                               cycle count is to be updated                 **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                                                                            **
** Description : When called with BlockNumber = 0, this routine delivers the  **
** FEE sector erase cycle count. When called with a configured BlockNumber,   **
** the write cycle count of the given block is returned.                      **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fee_17_GetCycleCount
(
  const uint16 BlockNumber,
  uint32 * const CountPtr
);

#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when this optional function is called by application and
  not enabled in the configuration*/
#define Fee_17_GetCycleCount(BlockNumber,CountPtr)    \
(ERROR_Fee_17_GetCycleCount_API_IS_NOT_SELECTED)

#endif /* Fee_17_GetCycleCount */
#endif /*End of FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY*/

/*******************************************************************************
** Syntax : Std_ReturnType Fee_Read(const uint16 BlockNumber,                 **
**                                  const uint16 BlockOffset,                 **
**                                  uint8 *const DataBufferPtr,               **
**                                  const uint16 Length )                     **
**                                                                            **
** Service ID: 0x02                                                           **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  BlockNumber - Logical Block Number                      **
**                    BlockOffset - Read address offset inside the block      **
**                    Length - Number of bytes to read                        **
**                                                                            **
** Parameters (out):  DataBufferPtr - Pointer to data buffer                  **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                                                                            **
** Description : This function shall take the block start address and         **
** offset and calculate the corresponding memory read address. The address    **
** offset and length parameter can take any value within the given block      **
** this allows reading of an arbitrary number of bytes from an arbitrary start**
** address inside a logical block                                             **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fee_Read(const uint16 BlockNumber,
                               const uint16 BlockOffset,
                               uint8 *const DataBufferPtr,
                               const uint16 Length);

/*******************************************************************************
** Syntax : Std_ReturnType Fee_Write(const uint16 BlockNumber,                **
**          const uint8 *const DataBufferPtr)                                 **
**                                                                            **
** Service ID: 0x03                                                           **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  BlockNumber - Logical Block Number                      **
**                    DataBufferPtr - Pointer to data buffer                  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                                                                            **
** Description : This function shall take the logical block number and        **
** determine the corresponding memory write address. This routine will        **
** perform the block write operation on DFLASH (DF_EEPROM).                   **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fee_Write(const uint16 BlockNumber,
                                const uint8 *const DataBufferPtr);


/*******************************************************************************
** Syntax : void Fee_Cancel(void)                                             **
**                                                                            **
** Service ID: 0x04                                                           **
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
** Description : This functions shall cancel a pending request.               **
** Note: An ongoing write request is not cancelled. However, a queued         **
** write request is cancelled. Any read request either queued or under        **
** execution is cancelled.                                                    **
**                                                                            **
*******************************************************************************/
extern void Fee_Cancel(void);
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
#if (FEE_CANCELL_ALL_API == STD_ON)
/*******************************************************************************
** Syntax : void Fee_17_CancelAll (void)                                      **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : Service to cancel an ongoing user job                        **
*******************************************************************************/
extern void Fee_17_CancelAll(void);

#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when this optional function is called by application and
  not enabled in the configuration*/
#define Fee_17_CancelAll(void) \
(ERROR_Fee_17_CancelAll_API_IS_NOT_SELECTED)
#endif
#endif

/*******************************************************************************
** Syntax : MemIf_StatusType Fee_GetStatus(void)                              **
**                                                                            **
** Service ID: 0x05                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  MemIf_StatusType                                        **
**                                                                            **
** Description : This function returns the status of the FEE driver           **
**                                                                            **
*******************************************************************************/
extern MemIf_StatusType Fee_GetStatus(void);


/*******************************************************************************
** Syntax : MemIf_JobResultType Fee_GetJobResult(void)                        **
**                                                                            **
** Service ID: 0x06                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  MemIf_JobResultType                                     **
**                                                                            **
** Description : This function shall return the result of the last job that   **
** that was executed.                                                         **
**                                                                            **
*******************************************************************************/
extern MemIf_JobResultType Fee_GetJobResult(void);


/*******************************************************************************
** Syntax : Std_ReturnType Fee_InvalidateBlock(const uint16 BlockNumber)      **
**                                                                            **
** Service ID: 0x07                                                           **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  BlockNumber : Logical Block Number                      **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                                                                            **
** Description : This function shall invalidate the given logical             **
** block                                                                      **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fee_InvalidateBlock(const uint16 BlockNumber);


/*******************************************************************************
** TRACEABILITY:                                                              **
**                                                                            **
** Syntax : Std_ReturnType Fee_EraseImmediateBlock( const uint16 BlockNumber )**
**                                                                            **
**                                                                            **
**                                                                            **
** Service ID: 0x09                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  BlockNumber - Logical Block Number                      **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                                                                            **
** Description : Service to erase an immediate logical block.                 **
** Since double-sector algorithm is used with threshold limit                 **
** for triggering GC, immediate block's write requests during GC can be       **
** accommodated within the pre-erased threshold area of the active FEE sector.**
** Hence, this API is implemented as a dummy function returning E_NOT_OK.     **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fee_EraseImmediateBlock(const uint16 BlockNumber);


#if (FEE_INITCHECK_API == STD_ON)
/*******************************************************************************
** TRACEABILITY: Yet to be updated                                            **
**                                                                            **
** Syntax : Std_ReturnType Fee_17_InitCheck(const Fee_ConfigType              **
**                                           * const ConfigPtr)               **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID: Yet to be updated                                              **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : ConfigPtr - Pointer to the selected configuration set    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                                                                            **
** Description : Service to check module Initialization status. if module is  **
**               not initialize it will return E_NOT_OK                       **
*******************************************************************************/
extern Std_ReturnType Fee_17_InitCheck(const Fee_ConfigType * const ConfigPtr );

#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when this optional function is called by application and
  not enabled in the configuration*/
#define Fee_17_InitCheck(ConfigPtr) \
(ERROR_Fee_17_InitCheck_API_IS_NOT_SELECTED)

#endif

/*******************************************************************************
** Syntax : void  Fee_17_EnableGcStart( void )                                **
**                                                                            **
** Service ID:                                                                **
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
** Description : This service allows enabling the trigger of GC, if GC was    **
** disabled earlier by calling the API Fee_17_DisableGcStart. This service    **
** allows the FEE to trigger the GC if the sector is filled up to the         **
** threshold level                                                            **
**                                                                            **
*******************************************************************************/
extern void Fee_17_EnableGcStart( void );

/*******************************************************************************
** Syntax : void  Fee_17_DisableGcStart( void )                               **
**                                                                            **
** Service ID:                                                                **
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
** Description : This API prevents the GC from being started in case the      **
** threshold is crossed in the active FEE sector. This API does not stop an   **
** ongoing GC but only prevents the GC from being triggered by the            **
** Write/Invalidate request issued by the user.                               **
** Note: This API will disable the GC from starting only if,                  **
** 1. GC is not ongoing                                                       **
** 2. Initialisation activities are complete (i.e. the state pages are read   **
** and the GC state is determined)                                            **
**                                                                            **
*******************************************************************************/
extern void Fee_17_DisableGcStart( void );

#if (FEE_GET_PREV_DATA_API == STD_ON)
/*******************************************************************************
** Syntax : Std_ReturnType Fee_17_GetPrevData(const uint16 BlockNumber,       **
**                                            const uint16 BlockOffset,       **
**                                            uint8 *const DataBufferPtr,     **
**                                            const uint16 Length)            **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async: Asynchronous                                                   **
**                                                                            **
** Reentrancy: Non reentrant                                                  **
**                                                                            **
** Parameters (in) :  BlockNumber - Logical Block Number                      **
**                    BlockOffset - Read address offset inside the block      **
**                    Length - Number of bytes to read                        **
**                                                                            **
** Parameters (out):  DataBufferPtr - Pointer to data buffer                  **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                                                                            **
** Description : This API shall read one occurance previous version of the    **
** given logical block                                                        **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fee_17_GetPrevData(const uint16 BlockNumber,
    const uint16 BlockOffset,
    uint8 *const DataBufferPtr,
    const uint16 Length );
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when this optional function is called by application and
  not enabled in the configuration*/
#define Fee_17_GetPrevData(BlockNumber,CountPtr,DataBufferPtr,Length)    \
(ERROR_Fee_17_GetPrevData_API_IS_NOT_SELECTED)
#endif

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)

/*******************************************************************************
** Syntax : Std_ReturnType Fee_17_EraseQuasiStaticData(                       **
            const uint16 BlockNumber, const uint16 Instances)                 **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  BlockNumber : Logical block number                      **
**                    Instances   : Number of block instances                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  E_OK : Erase Request is accepted                        **
**                    E_NOT_OK : Erase Request is not accepted                **
**                                                                            **
** Description : This function will initialize an erase job for one or        **
** multiple consecutive instances of a quasi-static data block                **
*******************************************************************************/
extern Std_ReturnType Fee_17_EraseQuasiStaticData(const uint16 BlockNumber,
    const uint16 Instances);

/*******************************************************************************
**                                                                            **
** Syntax : MemIf_JobResultType Fee_17_GetQuasiStaticJobResult(               **
**          const uint16 BlockNumber,                                         **
**          const Fee_QuasiStaticBlockInfoType *BlockInfoPtr)                 **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  BlockNumber : Logical block number                      **
**                    BlockInfoPtr : constant pointer to BlockInfo structure  **
**                                                                            **
** Parameters (out):  BlockInfoPtr : Blockinfo structure updated with the     **
**                                   block state and block cycle count        **
**                                                                            **
** Return value    :  E_OK : QS block info was read successfully              **
**                    E_NOT_OK : QS block info not available                  **
**                                                                            **
** Description : This function provides the block state and the block cycle   **
**               counter of the requested quasi-static data block instance    **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fee_17_GetQuasiStaticBlockInfo(const uint16 BlockNumber,
    Fee_QuasiStaticBlockInfoType * const BlockInfoPtr);

/*******************************************************************************
**                                                                            **
** Syntax : MemIf_JobResultType Fee_17_GetQuasiStaticJobResult(void)          **
**                                                                            **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  MemIf_JobResultType                                     **
**                                                                            **
** Description : This function shall return the result of the last QS job     **
** that was executed.                                                         **
**                                                                            **
*******************************************************************************/
extern MemIf_JobResultType Fee_17_GetQuasiStaticJobResult(void);




#endif

#if (FEE_GET_ECC_ERROR_INFO_API == STD_ON)
/*******************************************************************************
** TRACEABILITY:                                                              **
**                                                                            **
** Syntax :void Fee_17_GetEccErrorInfo( uint16 * const BlockNumberPtr,        **
**                                   uint32 * const PageAddressPtr )          **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:      0x32                                                      **
**                                                                            **
** Sync/Async:      Synchronous                                               **
**                                                                            **
** Reentrancy:      Non Reentrant                                             **
**                                                                            **
** Parameters (out): BlockNumberPtr - Block number with ECC error             **
**                   PageAddressPtr - Address of page with ECC error          **
**                                                                            **
** Parameters (in): Std_ReturnType                                            **
**                                                                            **
** Return value:    E_OK - The requested job has been executed                **
**                  E_NOT_OK - The requested job has not been executed        **
**                                                                            **
** Description :   Service to get the last ECC error information (Block       **
** number and page address where last ECC error is detected) Default value    **
** - If there is no ECC error detected, then default valur for                **
**   BlockNumber = 0xFFFF, PageAddress = 0xFFFFFFFF                           **
** - If the block number is unknown, the default value                        **
**   BlockNumber = 0xFFFF is used                                             **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fee_17_GetEccErrorInfo( uint16 * const BlockNumberPtr,
                             uint32 * const PageAddressPtr );
#else
/*MISRA2012_RULE_4_9_JUSTIFICATION:Function like macro is used to generate
  compilation error, when this optional function is called by application and
  not enabled in the configuration*/
#define Fee_17_GetEccErrorInfo(BlockNumber, PageAddressPtr)    \
(ERROR_Fee_17_GetEccErrorInfo_API_IS_NOT_SELECTED)
#endif


/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/


#define FEE_STOP_SEC_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Fee_MemMap.h"

/* Fee Module Post Buid Configuration header file */
#include "Fee_PBcfg.h"

#endif /* FEE_H */

