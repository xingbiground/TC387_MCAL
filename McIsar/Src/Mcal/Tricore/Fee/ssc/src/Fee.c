/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2023)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME     : Fee.c                                                     **
**                                                                           **
**  VERSION      : 41.0.0                                                    **
**                                                                           **
**  DATE         : 2023-05-16                                                **
**                                                                           **
**  VARIANT      : Variant PB                                                **
**                                                                           **
**  PLATFORM     : Infineon AURIX2G                                          **
**                                                                           **
**  AUTHOR       : DL-AUTOSAR-Engineering                                    **
**                                                                           **
**  VENDOR       : Infineon Technologies                                     **
**                                                                           **
**  DESCRIPTION  : Fee Driver source file                                    **
**                                                                           **
**  SPECIFICATION(S) : Specification of Fee Driver,                          **
**                     AUTOSAR Release 4.2.2 and 4.4.0                       **
**                                                                           **
**  MAY BE CHANGED BY USER : no                                              **
**                                                                           **
******************************************************************************/
/* [cover parentID={540C6CF8-E5A3-47b2-9A71-B1EFD849D042}] Fee.c
[/cover] */
/* [cover parentID={21DDC179-B28F-4c4d-9045-F9A7AAB29407}]
Platform independent module
[/cover] */
/* [cover parentID={056FA7C0-7DE5-427e-8FD1-01B6F7EFEAB2}]*/
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]*/
/******************************************************************************
**                      Includes                                             **
******************************************************************************/

/* Inclusion of Flash header file */
#include "Fee.h"

/* Inclusion of FEE Callback functionality */
#include "Fee_Cbk.h"

/* [cover parentID={203A0946-A5FE-4078-9B0D-8D1489678415}][/cover] */
/* Scheduled function header file */
#include "SchM_Fee.h"

#if ((FEE_DEM_ENABLED == STD_ON) || (FEE_RUNTIME_ERROR_DETECT == STD_ON))
/* Inclusion of McalWrapper.h  */
#include "Mcal_Wrapper.h"
#endif

/* Conditional Inclusion of Developement Error Tracer File */
#if  (FEE_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

#if (FEE_SAFETY_ENABLE == STD_ON)
#include "Mcal_SafetyError.h"
#endif

/*AUTOSAR File*/

/******************************************************************************
**                      Imported Compiler Switch Check                       **
******************************************************************************/

/*
    AUTOSAR VERSION CHECK FOR FEE MODULE INCLUSION
*/
/* [cover parentID={CB9A9AFC-6470-4658-8BC1-8F515E9C8B88}]*/

#ifndef FEE_AR_RELEASE_MAJOR_VERSION
#error "FEE_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

#ifndef FEE_AR_RELEASE_MINOR_VERSION
  #error "FEE_AR_RELEASE_MINOR_VERSION is not defined."
#endif

#ifndef FEE_AR_RELEASE_REVISION_VERSION
  #error "FEE_AR_RELEASE_REVISION_VERSION is not defined."
#endif

#if ( FEE_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION)
#error "FEE_AR_RELEASE_MAJOR_VERSION does not match. "
#endif

#if ( FEE_AR_RELEASE_MINOR_VERSION != MCAL_AR_RELEASE_MINOR_VERSION)
  #error "FEE_AR_RELEASE_MINOR_VERSION does not match."
#endif

#if ( FEE_AR_RELEASE_REVISION_VERSION != MCAL_AR_RELEASE_REVISION_VERSION)
  #error "FEE_AR_RELEASE_REVISION_VERSION does not match."
#endif
/*
    DRIVER VERSION CHECK FOR FEE MODULE
*/

#ifndef FEE_SW_MAJOR_VERSION
#error "FEE_SW_MAJOR_VERSION is not defined. "
#endif

#ifndef FEE_SW_MINOR_VERSION
#error "FEE_SW_MINOR_VERSION is not defined. "
#endif

#ifndef FEE_SW_PATCH_VERSION
#error "FEE_SW_PATCH_VERSION is not defined."
#endif

/* [cover parentID={F53B2EEE-3552-4f44-A9BE-2BA5A962432D}]*/

#if ( FEE_SW_MAJOR_VERSION != 20U )
#error "FEE_SW_MAJOR_VERSION does not match. "
#endif

#if ( FEE_SW_MINOR_VERSION != 25U )
#error "FEE_SW_MINOR_VERSION does not match. "
#endif

#if ( FEE_SW_PATCH_VERSION != 0U )
#error "FEE_SW_PATCH_VERSION does not match."
#endif

/*
    VERSION CHECK FOR DET MODULE INCLUSION
*/

#if (FEE_DEV_ERROR_DETECT == STD_ON)

#ifndef DET_AR_RELEASE_MAJOR_VERSION
#error "DET_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

#if ( DET_AR_RELEASE_MAJOR_VERSION != 4U )
#error "DET_AR_RELEASE_MAJOR_VERSION does not match. "
#endif

#endif /* (FEE_DEV_ERROR_DETECT == STD_ON) */


/*
    VERSION CHECK FOR FLS MODULE INCLUSION
*/

#ifndef FLS_17_DMU_AR_RELEASE_MAJOR_VERSION
#error "FLS_17_DMU_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

#if ( FLS_17_DMU_AR_RELEASE_MAJOR_VERSION != 4U )
#error "FLS_17_DMU_AR_RELEASE_MAJOR_VERSION does not match. "
#endif

/******************************************************************************
**                      Private Macro Definitions                            **
******************************************************************************/

/*---------- Garbage Collection related constant------------------------*/

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

/* 1. User operation allowed states */
#define FEE_GC_REQUESTED                            (0x5U)
/*Read states of GC */
#define FEE_GC_UNCFG_START_COPY                     (0x10U)
#define FEE_GC_START_COPY                           (0x1U)

/* Erase states of GC */
#define FEE_GC_ERASE_PREV_SECTOR                    (0x3U)
#define FEE_GC_INIT_ERASE_PREV_SECTOR               (0x4U)

/* 2. User operation NOT allowed states */
/*Read states of GC */
#define FEE_GC_UNCFG_COPY_READ_NXTPAGE              (0x0U)
#define FEE_GC_COPY_READ_NXTPAGE                    (0x2U)

/* Write states of GC */
/* SECTOR0 -> Current/Prev Sector; SECTOR1 -> Next Sector */
/* V -> Valid; E -> Erased */
/* SP -> State Page; M -> Marker */

#define FEE_GC_UNCFG_COPY_WRITE          (0x6U)
#define FEE_GC_COPY_WRITE                (0x7U)
#define FEE_GC_MARK_SECTOR1_V_SP         (0x8U)
#define FEE_GC_MARK_SECTOR1_V_M          (0x9U)
#define FEE_GC_MARK_SECTOR0_E_SP         (0xAU)
#define FEE_GC_MARK_SECTOR0_E_M          (0xBU)
#define FEE_GC_INIT_MARK_SECTOR0_E_SP    (0xCU)
#define FEE_GC_INIT_MARK_SECTOR0_E_M     (0xDU)

#if (FEE_CANCELL_ALL_API == STD_ON) && \
(FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)
/* Cancel GC related */
#define FEE_GC_NOT_CANCLD                   (0U)
#define FEE_GC_CANCLD                     (1U)
#define FEE_GC_CANCLD_CACHEUPDATE            (2U)

#endif

#endif

/* 3. Non operational states of GC */
#define FEE_GC_IDLE                                 (0xEU)

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

#define FEE_GC_FAIL                                 (0xFU)

#endif

/* Fee_Init States - Used for detecting the Garbage Collection Interruption */
#define FEE_INITGC_IDLE                      (0U)

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

#define FEE_INITGC_HANDLE_INVALID            (1U)
#define FEE_INITGC_HANDLE_DIRTY              (2U)
#define FEE_INITGC_NORMAL                    (3U)
#define FEE_INITGC_PREPARE_DFLASH            (4U)
#define FEE_INITGC_COMPLETE                  (5U)
#define FEE_INITGC_FAIL                      (6U)
#define FEE_INITGC_HANDLE_VIRGIN             (7U)
/* States to monitor Garbage Collection completion, if it was interrupted */
/* earlier due to reset */
#define FEE_INITGC_NORMAL_S1                (0x1DU)
#define FEE_INITGC_NORMAL_S0                (0xD1U)
#define FEE_INITGC_DATA_COPY_S1_S0          (0x5DU)
#define FEE_INITGC_DATA_COPY_S0_S1          (0xD5U)
#define FEE_INITGC_ERASE_S1                 (0xDFU)
#define FEE_INITGC_ERASE_S0                 (0xFDU)

#endif

/*---------- Garbage Collection related constant End -------------------*/


/*---------- Erase suspend related constant ----------------------------*/


#if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
/* Erase-Suspend Status */
#define FEE_ERASE_NOT_SUSPENDED                     ((uint8)0)
#define FEE_ERASE_SUSPENDED                         ((uint8)1)
/* FeeEraseSuspendStatus > 1  : Resume-Erase failed */
/* FEE_RESUME_ERASE_LIMIT - 1 : No. of times Resume-Erase will be attempted */

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

#define FEE_RESUME_ERASE_LIMIT                      ((uint8)4)

#endif

#endif

/*---------- Erase suspend related constant End -------------------------*/

/*---------- Common constant start -------------------------*/
#define FEE_ZERO      (0U)

#define FEE_RESET     (0U)
#define FEE_SET       (1U)

#if(FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

#if (FEE_GET_CYCLE_COUNT_API == STD_ON)

#define FEE_STATE_PAGE_NUMBER (0U)

#endif

#define FEE_BLOCK_HDR_PAGE        (0U)
#define FEE_INVALID_BLOCK_LEN     (1U)
#define FEE_INVALID_BLOCK         (0U)
#define FEE_NEW_WL_BEGIN          (0U)
#define FEE_DATA_NEXT_PAGE_ID_POS (0U)
#define FEE_INVALID_BLOCK_PAGES   (2U)
#define FEE_BLOCK_NUM_MSB_POS     (2U)
#define FEE_BLOCK_NUM_LSB_POS     (1U)
#define FEE_BLOCK_MANGMNT_PAGES   (2U)
#define FEE_BLOCK_CYL_CNT_POS     (2U)
#define FEE_PAGE_TO_BYTE          (3U)
#define FEE_BYTE_TO_PAGE          (3U)
#define FEE_BLOCK_NUM_POS         (6U)
#endif

#define FEE_ONE       (1U)
#define FEE_TWO       (2U)
#define FEE_THREE     (3U)
#define FEE_FOUR      (4U)
#define FEE_FIVE      (5U)
#define FEE_SIX       (6U)
#define FEE_SEVEN     (7U)
#define FEE_EIGHT     (8U)
#define FEE_SIXTEEN   (16U)

#if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
#define FEE_DET_SAFETY_ERROR (0U)
#endif

#if (FEE_SAFETY_ENABLE == STD_ON)
#define FEE_SAFETY_ERROR (1U)
#endif

#if (FEE_RUNTIME_ERROR_DETECT== STD_ON)
#define FEE_RUNTIME_ERROR (2U)
#endif


/*---------- Common constant constant End -------------------------*/




/*---------- State page related constant End ---------------------------*/

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

#define FEE_STATE_FIRSTFIVE_COPY_OFFSET (40U)
#define FEE_STATE_ALLONES_OFFSET        (80U)
#define FEE_STATE_CRC_OFFSET            (116U)
#define FEE_STATE_WLCOUNT_MASK          (0xFFFFFF00U)
#define FEE_STATEPAGE_DATA_SIZE         (120U)
#define FEE_STATEPAGE_MARKER_SIZE       (8U)
#define FEE_STATEPAGE_SIZE              (128U)
#define FEE_STATEPAGE_PROGRAM_SIZE      (120U)
#define FEE_PROGRAM_STATEPAGE           (1U)
#define FEE_PROGRAM_MARKER              (2U)
/* State page Status */
#define FEE_SP_CLEAN                    (0U)
#define FEE_SP_DIRTY                    (1U)
#define FEE_SP_INVALID                  (2U)
#define FEE_VALID                       (0xD1U)
#define FEE_ERASED                      (0x1EU)
/* Page Identifier */
#define FEE_STATE_FIRST_PAGE_ID         (0x59U)
#define FEE_STATE_NEXT_PAGE_ID          (0xC6U)
#define FEE_STATE_PAGE_ID_POS           (0U)
#define FEE_STATE_PAGE_STATE_POS        (1U)
#define FEE_STATE_PAGE_UERWL_POS        (3U)
#define FEE_STATE_PAGE_STATE_CNT_POS    (4U)
#define FEE_STATE_PAGE_HDR_PAGES        (10U)

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)

#define FEE_STATE_PAGE_QS_OFFSET_LSB    (2U)
#define FEE_STATE_PAGE_QS_OFFSET_MSB    (3U)

/* Mask to extract the QS Data offset which is stored in State Page */
#define FEE_QS_DATA_OFFSET_MASK         (0x0FFF0000U)
/* Bit position indicating the start of the the QS Data offset which is stored
  in State Page */
#define FEE_QS_DATA_OFFSET_START        (16U)

#endif

#define FEE_STATE_PAGE_UERWL1_ADDRS_POS (12U)
#define FEE_STATE_PAGE_UERWL2_ADDRS_POS (20U)

/* State Page field for verification */
#define FEE_SP_MARKERFIELD_START        (120U)
#define FEE_SP_MARKER_WORD_1            (0xAFAFF53AU)
#define FEE_SP_MARKER_WORD_2            (0xAFAFF5F5U)
#define FEE_CRC_START_VAL              (0U)

#endif

/* State page Repair stages */
#define FEE_REPAIR_IDLE                (0U)


/*---------- State page related constant End ---------------------------*/

/*---------- Data block related constant -------------------------------*/

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/* Sector page offsets */
#define FEE_PAGE1_DATA_OFFSET            (8U)
#define FEE_VALID_BIT                    (0x80U)
#define FEE_PAGE_COUNT_MASK              (0x7FFFU)
#define FEE_VALID_MASK                   (0x80U)
/* Page Identifier */
#define FEE_DATA_FIRST_PAGE_ID           (0xA3U)
#define FEE_DATA_NEXT_PAGE_ID            (0x9CU)
#define FEE_DATA_MARKER_PAGE_ID          (0x65U)
#define FEE_DP_MARKER_WORD               (0xF5F5AF65U)
#define FEE_DP_MARKER_BYTE_2             (0xAFU)
#define FEE_DP_MARKER_BYTE_3             (0xF5U)
#define FEE_DP_MARKER_BYTE_4             (0xF5U)
#define FEE_LWB_DIRTY                    (1U)
#define FEE_LWB_CHECK_FOR_DIRTY          (2U)

#endif

/* Last Written Block Dirty Status */
#define FEE_LWB_NOT_DIRTY        (0U)

/*---------- Data block related constant end ----------------------------*/



#define FEE_16_BIT_ALL_ONES           (0xFFFFU)
#define FEE_32_BIT_ALL_ONES           (0xFFFFFFFFU)

#define FEE_DFLASH_WORDLINE_SIZE_1    (FEE_DFLASH_WORDLINE_SIZE - 1U)

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

#define FEE_WRITE_LEN_MAX             (FEE_MAX_BYTES_PER_CYCLE)
#define FEE_COMPARE_LEN_MAX           (FEE_MAX_BYTES_PER_CYCLE)


/*---------- Word line related constant --------------------------------*/

/* Data bytes in a word-line = ((WordLine Size / 8) * 7) */
#define FEE_DATA_BYTES_IN_WORDLINE    (448U)

/* Word-Line Affected Type */
/* 2. Block sharing the last written WL boundary is (also) affected */
#define FEE_LWB_ACROSS_WL_AFFECTED                ((uint8)0x01U)
/* 3. Only the block(s) present in the last written WL is affected */
#define FEE_LWB_WITHIN_WL_AFFECTED                ((uint8)0x02U)
/* 4. Continue copying block pages in last written WL */
#define FEE_LWB_WITHIN_WL_AFFECTED_CONT           ((uint8)0x03U)
/* 5. Copy marker page in last written WL */
#define FEE_LWB_MARKER_COPY_PENDING               ((uint8)0x04U)

#endif

/* 1. WL not affected */
#define FEE_LWB_NOT_AFFECTED                      ((uint8)0x00U)

/*---------- Word line related constant End ----------------------------*/

/*---------- Data flash related constant -------------------------------*/

#define FEE_DFLASH_WORD_SIZE              (4U)
/* Fee Prepare DFlash States */
#define FEE_PREPDF_ERASE_S0               (0U)


#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/* Sector states */
#define FEE_STATELESS                     (0U)

#define FEE_PREPDF_ERASE_S1               (1U)
#define FEE_PREPDF_MARK_S0_ERASED_SP      (2U)
#define FEE_PREPDF_MARK_S0_ERASED_M       (3U)
#define FEE_PREPDF_MARK_S0_VALID_SP       (4U)
#define FEE_PREPDF_MARK_S0_VALID_M        (5U)
#define FEE_PREPDF_MARK_S1_ERASED_SP      (6U)
#define FEE_PREPDF_MARK_S1_ERASED_M       (7U)
/*Two sector enabled, represents the NVM sector size*/
#define FLS_SECTOR0_SIZE                  (FLS_17_DMU_NVMSECTOR_SIZE)
/* Sector page values, used to store current status of the DFLASH */
#define FEE_DFLASH_SECTOR_SIZE            (FLS_SECTOR0_SIZE)
#define FEE_DFLASH_BANK1_BASE             (FEE_DFLASH_SECTOR_SIZE)
#define FEE_SECTOR0                       (0U)
#define FEE_SECTOR1                       (1U)
#define FEE_DFLASH_BANK0_BASE             (0x0000U)
/*Name to be changed*/
#define FLS_ERASE_SECTORS                 (FLS_17_DMU_NVMSECTOR_SIZE/4096)
/* Sector status */
#define FEE_SP_INIT                       (0U)
#define FEE_SP_DONE                       (1U)
/* DFlash status at Initialization */
#define FEE_S0_S1_EMPTY                   (0x0U)
#define FEE_S0_VALID                      (0x1U)
#define FEE_S1_VALID                      (0x2U)
#define FEE_S0_S1_VALID                   (0x3U)
#define FEE_S0_S1_INVALID                 (0x4U)


#endif

/*---------- Data flash related constant End ---------------------------*/

/*---------- Cache table related constant  -----------------------------*/

/* Cache Update states */
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

#define FEE_CACHE_FIND_NEXT_BLK            (1U)
#define FEE_CACHE_UPDATE_COMPLETE          (3U)

/* This macro is used as dummy parameter. This will be used while calling
 Fee_lGcErrorHandler when GC write/erase/GC on GC error occurred */
#define FEE_UNUSED_PARAM                   ((uint16)0xFFFFU)
#else

#define FEE_CACHE_IDLE_QS                  (4U)

#endif

#define FEE_CACHE_IDLE                     (0U)
#define FEE_LOG_BLOCK_NOT_FOUND            ((uint16)0xFFFFU)



/*---------- Cache table related constant End --------------------------*/

/*---------- Fee Job related constant  ---------------------------------*/

/* Pending request types */
#define FEE_PEND_PREV_NO_REQ                (1U)
#define FEE_PEND_PREV_READ_REQ              (3U)
#define FEE_PEND_PREV_READ_NOTIF            (5U)
#define FEE_REQ_READ                        (6U)
#define FEE_REQ_NORM_WRITE                  (8U)
#define FEE_REQ_IMM_WRITE                   (9U)
#define FEE_PEND_PREV_COMPARE               (10U)
#define FEE_PEND_INTR_COMPARE               (12U)

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

#define FEE_PEND_INTR_READ                  (13U)
#define FEE_PEND_INTR_WRITE                 (14U)
#define FEE_PEND_PREV_WRITE_REQ             (2U)

#endif

#define FEE_WRITE_FAIL                      (15U)

/* Job states */
#define FEE_JOB_IDLE                        (0U)
#define FEE_JOB_REQSTD                      (1U)
#define FEE_JOB_DONE                        (2U)
/* Job results */
#define FEE_JOB_PASS                        (0U)
#define FEE_JOB_FAIL                        (1U)
/* FEE JOBS */
#define FEE_WRITE_JOB                       (FLS_17_DMU_WRITE_JOB)
#define FEE_READ_JOB                        (FLS_17_DMU_READ_JOB)
#define FEE_ERASE_JOB                       (FLS_17_DMU_ERASE_JOB)
#define FEE_NO_JOB                          (FLS_17_DMU_NO_JOB)
#define FEE_CANCEL_JOB                      (FLS_17_DMU_CANCEL_JOB)

/*---------- Fee Job related constant End ------------------------------*/

/*---------- Fee Main state machine related constant -------------------*/

/* Fee Main Function States */
#define FEE_MAIN_UNINIT         (0U)
#define FEE_MAIN_INITGC         (1U)
#define FEE_MAIN_CACHEUPDATE    (2U)
#define FEE_MAIN_READ           (3U)
#define FEE_MAIN_WRITE          (4U)
#define FEE_MAIN_GC             (5U)

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)

#define FEE_MAIN_INITQS         (6U)
#define FEE_MAIN_QS             (7U)

#endif

#define FEE_MAIN_NONE           (10U)

/*---------- Fee Main state machine related constant End ----------------*/

/*---------- Fee Error related constant ---------------------------------*/

/* Error events during User/Internal operations */
#define FEE_CANCEL              ((uint8)0x0)

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
#define FEE_NOT_CANCEL          ((uint8)0xFF)
#endif

#define FEE_WRITE               ((uint8)0x1)
#define FEE_READ                ((uint8)0x2)
#define FEE_INVALIDATE          ((uint8)0x6)

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

#define FEE_GC_E_OK             ((uint8)0x0)
#define FEE_GC_WRITE            ((uint8)0x3)
#define FEE_GC_READ             ((uint8)0x4)
#define FEE_GC_ERASE            ((uint8)0x5)
#define FEE_GC_TRIG             ((uint8)0x7)


/* Un-configured block related constants */
#define FEE_UNCONFIG_BLK_LIMIT_CROSSED    ((uint8)0xFF)

#endif

/*---------- Fee Error related constant End ----------------------------*/

/*---------- QS data related constant End ----------  ------------------*/

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)

/* Macros for QS STATE values in DFLASH0 */
#define FEE_QS_STATE_DFERASE_STATE       (0x00000000U)
#define FEE_QS_STATE_WRITE_COMPLETE_LSW  (0x33334444U)
#define FEE_QS_STATE_WRITE_COMPLETE_MSW  (0x55556666U)
#define FEE_QS_STATE_WRITE_STARTED_LSW   (0x11112222U)
#define FEE_QS_STATE_WRITE_STARTED_MSW   (0x77778888U)
#define FEE_QS_STATE_ERASE_COMPLETE_LSW  FEE_QS_STATE_WRITE_COMPLETE_LSW
#define FEE_QS_STATE_ERASE_COMPLETE_MSW  FEE_QS_STATE_WRITE_COMPLETE_MSW
#define FEE_QS_STATE_ERASE_STARTED_LSW   FEE_QS_STATE_WRITE_STARTED_LSW
#define FEE_QS_STATE_ERASE_STARTED_MSW   FEE_QS_STATE_WRITE_STARTED_MSW
#define FEE_QS_STATE_DESTROY             (0xFFFFFFFFU)
/* quasi static block intermediate states */
#define FEE_REQ_QUASI_READ                        (16U)
#define FEE_REQ_QUASI_WRITE                       (17U)
#define FEE_REQ_QUASI_ERASE                       (18U)
#define FEE_INITQS_COMPLETE                       (7U)
#define FEE_MAX_BCC_QS                            (65535U)
#define FEE_QS_STATE_ERASE_STARTED_OFFSET         (24U)
#define FEE_QS_STATE_WRITE_COMPLETED_OFFSET       (16U)
#define FEE_QS_STATE_WRITE_STARTED_OFFSET         (8U)
#define FEE_QS_STATE_CYCLE_COUNT_OFFSET           (32U)

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)


#define FEE_PAGES_IN_WL                       ((uint8)64)
#define FEE_DFLASH_QS_SIZE               (FLS_17_DMU_QSDATA_SIZE)

/* quasi static region hardening Frequency */
/* The check and hardening is performed on a scalable part of QS area,
Here desired checking rate  is chosen as 2% of the QS area as per the concept*/
#define FEE_HARDENING_RATE \
        ((((FEE_DFLASH_QS_SIZE * 2U)/(100U * FEE_DFLASH_WORDLINE_SIZE)) + 1U))

#define FEE_GC_HARDEN_QS_SECTOR          (0x11U)
#define FEE_QS_SECTOR_BASE               (FLS_17_DMU_QSDATA_STARTADDRESS)
#define FEE_HARDEN_CHK_PAGE              ((uint8)0x55)
#define FEE_HARDEN_CHK_WL                ((uint8)0xAA)
#define FEE_HARDEN_NOT_REQRD             ((uint8)0U)
#define FEE_HARDEN_REQRD                 ((uint8)1U)
#define FEE_HARDEN_REQ_ERROR             ((uint8)2U)
#define FEE_NO_HARDEN_RET_ADDRESS        (0xFFFFFFFFU)

#endif

#define FEE_QS_IDLE                      ((uint8)0)
#define FEE_REPAIR_JOB                   ((uint8)20)
#define FEE_QS_DATA_OFFSET               36
#define FEE_QS_STATUS_PAGES              5U
#define FEE_QS_HARDING_IDLE              (0U)
#define FEE_QS_DATA_OFFSET_SECOND_PAGE   (40U)

#endif

/*---------- QS data related constant End ------------------------------*/

/*-------------ECCERRORINFO data related constant ----------------------*/
#if (FEE_GET_ECC_ERROR_INFO_API == STD_ON)
#define FEE_DEFAULT_BLK_NUMBER          (0xFFFFU)
#define FEE_DEFAULT_PAGE_ADDRESS          (0xFFFFFFFFU)
#define FEE_BASE_ADDRESS                FLS_17_DMU_BASE_ADDRESS
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
#define FEE_PAGE_SIZE                  (8U)
#endif
#endif

/******************************************************************************
**                      Private Type Definitions                             **
******************************************************************************/

/******************************************************************************
**                      Private Function Declarations                        **
******************************************************************************/

#define FEE_START_SEC_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safe gaurd. It complies to Autosar guidelines. */
#include "Fee_MemMap.h"

static void Fee_lDecideMainJob(void);

#if (FEE_GET_ECC_ERROR_INFO_API == STD_ON)
static uint16 Fee_lGetEccErrorBlockNumber(uint32 const PageAddress);
#endif

#if (FEE_DEM_ENABLED == STD_ON)
static void  Fee_lReportDemError( const Dem_EventIdType EventId,
    const Dem_EventStatusType EventStatus);
#endif


#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
static boolean Fee_lIsUnerasableAddr(const uint32 Addr);
#endif

static void Fee_lHandleWriteFail(void);

static void Fee_lHandleUsrJobFailure(const uint8 Error);

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

static void Fee_lUpdateBlockInfo(const Fee_CacheStatusType * const Status,
                                 const uint16 Index, const uint16 pageCount);

static void Fee_lUpdateUnconfigBlockInfo(const uint16 BlockNumber, \
    const uint16 PageCount);

#endif

static void Fee_lRegisterWriteRequest(const uint8 * const DataWriteBufferPtr,
                                      const Fee_BlockType * const BlockPtr);

static Std_ReturnType Fee_lRegisterNvmRead(const uint16 BlockNumber,
    const uint16 BlockOffset, uint8 * const DataBufferPtr, const uint16 Length,
    const uint8 GetPrevCopy );

#if ((((FEE_DEV_ERROR_DETECT == STD_ON) || (FEE_SAFETY_ENABLE == STD_ON)) \
&& (MCAL_AR_VERSION == MCAL_AR_422)) || (FEE_RUNTIME_ERROR_DETECT == STD_ON))
LOCAL_INLINE void Fee_lRegNvmReadDetCheck(uint8 DetCall, const uint8
GetPrevCopy);
#endif

LOCAL_INLINE Std_ReturnType Fee_lRegisterNvmReadUpdate(uint8 DetCall,
                                 Std_ReturnType RetVal, const uint8 GetPrevCopy);

static Std_ReturnType Fee_lRegisterNvmWrite( \
    const uint8 * const DataWriteBufferPtr, \
    const Fee_BlockType * const BlockPtr);

static uint16  Fee_lGetUsrBlockIndex(const uint16 BlockNumber);

static Fls_17_Dmu_Job_Type Fee_lGetUserJob(const uint8 PendReqType);

static MemIf_StatusType Fee_lGetStatus(void);

LOCAL_INLINE void Fee_lMainNoneTransHdlr(void);

LOCAL_INLINE void Fee_lMainReadTransHdlr(void);

LOCAL_INLINE void Fee_lMainWriteTransHdlr(void);

LOCAL_INLINE void Fee_lMainCacheUpdtTransHdlr(void);

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

LOCAL_INLINE void Fee_lCheckPrevPage(const uint32 EndAddr);

LOCAL_INLINE void Fee_lPrepareInvldReqBuff(const uint32 BlockCycleCount,
                                           uint8 * const ReadWriteBuffPtr);
                                           

LOCAL_INLINE void Fee_lHandleBlkHeaderFound(const uint8  PotentialMarkerPage,
                                            const uint32 DataNextPageCount);

LOCAL_INLINE void Fee_lHandleBlkMarkerFound(const uint32 LWBHeaderAddress,
                                            const uint32 LWBMarkerAddress,
                                            const uint16 PageCount);
LOCAL_INLINE void Fee_lComputeNextWLAddr( Fee_SectorInfoType * \
                                          const SectorInfoPtr);

LOCAL_INLINE uint8 Fee_lEvaluateStatePage(void);

LOCAL_INLINE uint8 Fee_lEvaluateStatePageFormat(void);

LOCAL_INLINE uint8 Fee_lEvaluateStatePageMarker(void);

LOCAL_INLINE uint32 Fee_lEvaluateStatePageCrc(const uint32 * const DataPtr,
                                              const uint32 Length);

LOCAL_INLINE uint32 Fee_lIsWLBeginning(const uint32 address);
#endif

LOCAL_INLINE uint32 Fee_lGetNextWLAddr(const uint32 address);

LOCAL_INLINE uint32 Fee_lGetWLBeginning(const uint32 address);

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

LOCAL_INLINE boolean Fee_lIsBlockAffected(const uint16 BlockNumber,
                                          const uint32 BlockAddr);

LOCAL_INLINE Std_ReturnType Fee_lEvaluateBlkHeader(const uint16 BlockNumber,
                                                   const uint16 BlockPageCount);

LOCAL_INLINE Std_ReturnType Fee_lPerformReadCheck(const uint16 UserBlockIndex);

LOCAL_INLINE Std_ReturnType Fee_lCheckBlkCycleCnt(
  const Fee_BlockType *const BlockPtr,
  const uint32 BlockCycleCount);

LOCAL_INLINE boolean Fee_lIsSectorEmpty(const uint8 state, const uint8 used);

#endif

LOCAL_INLINE boolean Fee_lIsUserReadReqstd(const Fee_StateDataType * \
                                           const s_ptr);

LOCAL_INLINE boolean Fee_lIsUserWriteInvldReqstd
(const Fee_StateDataType * const s_ptr);

#if (FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)
static void Fee_lGcHardenQsSector(void);

static boolean Fee_lIsQsWriteReadAllowedbyGC(void);
static Fls_17_Dmu_AddressType Fee_lGcHardenReqChk(void);

#endif
LOCAL_INLINE Std_ReturnType Fee_lInitSafetyCheck(const uint8 ApiId);

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
LOCAL_INLINE Std_ReturnType Fee_lEraseQsDataSafetycheck(void);
#endif

#if (FEE_SAFETY_ENABLE == STD_ON) || (MCAL_AR_VERSION == MCAL_AR_440)
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY) \
    && (FEE_GET_CYCLE_COUNT_API == STD_ON)
LOCAL_INLINE Std_ReturnType Fee_lGetCycleSafetyCheck\
          (const uint32 * const CountPtr);
#endif
#endif

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
LOCAL_INLINE Std_ReturnType Fee_lQsBlkInfoSafetyCheck \
      (const Fee_QuasiStaticBlockInfoType * const BlockInfoPtr);
#endif

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

static uint32 Fee_lGetBlkCycleCount(const uint16 Index);

static void Fee_lClearFeeReadWriteBuffer(void);

static void Fee_lPrepareMarkerBuffer(void);

static void Fee_lClearMarkerBuffer(void);

static void Fee_lHandleIntrWrite(void);

static void Fee_lLastPgHandler(void);

static void Fee_lUpdateCache(void);

static void Fee_lPrepareStatePageBuffer(const uint8 Bank, \
                                        const uint8 SectorState);

static void Fee_lHandleUserWrite(const uint16 UserBlockIndex);

static void Fee_lHandleWritePrepDFLASH(const uint8 *const SrcPtr);

static void Fee_lInitGC(void);

static void Fee_lLocalRead(void);

static uint16 Fee_lCheckReadLength(const Fls_17_Dmu_AddressType ActualAddr,
                                   const uint16 Length);

static void Fee_lLocalWrite(void);

static void Fee_lGcErrorHandler(const uint8 Error, const uint16 Index);

static void Fee_lGcRead(const Fls_17_Dmu_AddressType Position,
                        const uint16 Offset);

static void Fee_lGcPrologue(void);

static void Fee_lGcStartCopy(void);

static void Fee_lGcDiscardUnconfigBlk(const uint16 Index);
static void Fee_lGcDiscardConfigBlk(const uint16 Index);

static void Fee_lClearFeeGcReadWriteBuffer(void);

static void Fee_lHandleInitGcFail(void);

static void Fee_lGcCopyReadNxtPage(void);

static void Fee_lGarbageCollection(void);

static void Fee_lUpdateNonZeroWLInfo(Fee_SectorInfoType *const SectorInfoPtr, \
                                     const uint32 SrcAddr);

static boolean Fee_lIsReadAllowedbyGC(void);

static boolean Fee_lIsWriteInvldAllowedbyGC(void);

static boolean Fee_lIsLastWrittenWLAffected(const uint16 StartOffset);

static boolean Fee_lIsBlockAcrossWLLatest(void);

static boolean Fee_lGcCheckBlkCopy(void);

static uint8 Fee_lGcStartCopyWrite(void);

static uint8 Fee_lGcWrite(const Fls_17_Dmu_AddressType Position,
                          const uint16 Offset);

static uint8 Fee_lGcErasePrevSector(const uint8 GcState);

static uint8 Fee_lGcProgramStatePage(const uint8 GcState);

static Fee_PageType Fee_lGetDFLASHPages(const uint16 Size);

static uint32 Fee_lGetFreeDFLASHPages(const uint8 BankNumber,
                                      const uint32 StartAddr);

LOCAL_INLINE void Fee_lHandleIntrRead(void);

LOCAL_INLINE void Fee_lComputeNextFreePageAddr(const uint32 BankNumber);

LOCAL_INLINE void Fee_lUpdateCacheTable(const uint32 BankNumber, \
                                        const uint32 EndAddr);

LOCAL_INLINE Std_ReturnType Fee_lPerformWriteCheck( \
    const Fee_BlockType * const BlockPtr);

LOCAL_INLINE Std_ReturnType Fee_lPerformCurrBlkCheck(
  const Fee_BlockType * const BlockPtr);

LOCAL_INLINE uint32 Fee_lGetBlockHeaderAddress(const uint32 LWBMarkerAddress,
                                               const uint16 PageCount);

LOCAL_INLINE boolean Fee_lIsGcTriggeredOnce
(const Fee_StateDataType *const StateDataPtr);

LOCAL_INLINE boolean Fee_lIsSectorThresholdCrossed(const uint32 FreePages,
    const uint32 PageCount);

LOCAL_INLINE boolean Fee_lIsSectorEndCrossed(const uint32 FreePages,
                                             const uint32 PageCount);

LOCAL_INLINE boolean Fee_lGcCheckUnconfigBlkCopy(void);

LOCAL_INLINE uint16 Fee_lLocalReadStart(const Std_ReturnType ReturnValue,
                                        const uint16 UserBlockIndex);

LOCAL_INLINE void Fee_lMainGCTransHdlr(void);

LOCAL_INLINE void Fee_lHandleErasePrepDFLASH(void);

LOCAL_INLINE void Fee_lIDSM(void);

LOCAL_INLINE void Fee_lINSM(void);

LOCAL_INLINE void Fee_lIPrepDFlashSM(void);

LOCAL_INLINE void Fee_lInitGCDSMTransHandler(void);

LOCAL_INLINE void Fee_lInitGCPrepDFlsTransHandler(void);

LOCAL_INLINE uint8 Fee_lPrepDFlashStateEraseS0(void);

LOCAL_INLINE uint8 Fee_lPrepDFlashStateEraseS1(void);

LOCAL_INLINE uint8 Fee_lPrepDFlashStatepageProgram(const uint8 PrepDFlashStatePrm);

LOCAL_INLINE void Fee_lInitGCTransHandler(void);

LOCAL_INLINE void Fee_lHandleGcFail(void);

LOCAL_INLINE void Fee_lGcRequested(void);

LOCAL_INLINE void Fee_lGcBlkCompare(void);

LOCAL_INLINE void Fee_lHandleUnConfigGcCopyError(void);

LOCAL_INLINE void Fee_lHandleConfigGcCopyError(void);

LOCAL_INLINE void Fee_lGcEraseCompare(const uint8 GcState);

LOCAL_INLINE void Fee_lGcStatePageCompare(const uint8 GcState);

LOCAL_INLINE uint8 Fee_lGcStatePageComparePass(const uint8 GcState);

LOCAL_INLINE uint8 Fee_lGcStatePageComparePassSetnewState(const uint8 GcState);

LOCAL_INLINE uint8 Fee_lCheckPrevWordline(Fee_SectorInfoType * const \
    SectorInfoPtr, const uint32 EndAddr);

LOCAL_INLINE void Fee_lGetSectorFreeWL(Fee_SectorInfoType *const SectorInfoPtr);

LOCAL_INLINE void Fee_lSetInitGc(const uint8 DFlashStatus);

LOCAL_INLINE uint8 Fee_lBuildDFlashStatus(void);

LOCAL_INLINE uint8 Fee_lGetSectorInfo(const uint32 BankNumber, \
                                      const uint32 EndAddr);

LOCAL_INLINE void Fee_lPerformPrevBlkCheck(void);

LOCAL_INLINE void Fee_lUpdateGcCurrBlockInfo(void);

LOCAL_INLINE void Fee_lPerformStuffCheck(const uint16 UserBlockIndex);


LOCAL_INLINE void Fee_lPrepareWriteReqBuff(const uint32 BlockCycleCount,
    uint8 * const ReadWriteBuffPtr,const uint16 BlockSize);

LOCAL_INLINE void Fee_lHandleUserWriteReq(const uint16 UserBlockIndex);
LOCAL_INLINE void Fee_lHandleUserWriteCompare(const uint16 UserBlockIndex);
LOCAL_INLINE void Fee_lHandleIntrWriteCompare(const uint16 UserBlockIndex);
LOCAL_INLINE void Fee_lMainGCHdlr(void);
LOCAL_INLINE uint8 Fee_lHandleGcCopy(void);
#endif

#if (((FEE_CANCELL_ALL_API == STD_ON) && \
    (FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA))||\
    ((FEE_ONGOING_WRITE_CANCEL_SUPPORT == STD_ON)&& \
    (FEE_DATA_BLOCK_SUPPORTED !=  FEE_QUASI_STATIC_DATA_ONLY)))
static void Fee_lCancelWrite(void);
#endif

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)

static void Fee_lQsInit(void);

static void Fee_lQsErase(void);

static void Fee_lQsRead(void);

#if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
static void Fee_lQsResumeErase(void);
#endif

static void Fee_lQsWrite(void);

static void Fee_lMainQsTransHdlr(void);

static void Fee_lEvalQsBlockState(Fee_CacheType *const Cacheptr);

static void Fee_lHandleQsJobSuccess(void);

static void Fee_lHandleQsJobFailure(const uint8 Error);

static void Fee_lQsBlockErase(void);

static void Fee_lQsBccWrite(void);

static void Fee_lQsBlockWrite(void);

static void Fee_lQsProgState(void);

static void Fee_lQsIDSM(void);

static void Fee_lMainQs(void);

#if (FEE_CANCELL_ALL_API == STD_ON)
static void Fee_lCancelAll (void);

LOCAL_INLINE void Fee_lCancelallUsrJob (void);

LOCAL_INLINE void Fee_lCancelallUsrJobQs (void);

#if (FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)

static void Fee_lCancelAllGCrestart(void);
#endif

#endif
static Std_ReturnType Fee_lRegisterQsRead( const uint16 BlockNumber,
    const uint16 BlockOffset,  uint8 * const DataBufferPtr,
    const uint16 Length);

static Std_ReturnType Fee_lRegisterQsWrite( \
    const uint8 * const DataWriteBufferPtr, \
    const Fee_BlockType * const BlockPtr);

static Fee_QsBlock_StateType Fee_lEvalQsBlockWriteStatus(void);

static Fee_QsBlock_StateType Fee_lEvalQsBlockEraseStatus(void);

static uint16 Fee_lQsGetBcc(const uint16 Blkindex);
static Std_ReturnType Fee_lEvalQsBlockVirginStatus(void);
static void Fee_lHandleQsVirginBlocks(void);


#endif

#if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON) \
  || (FEE_RUNTIME_ERROR_DETECT == STD_ON)
static void Fee_lReportError(uint8 ApiId, uint8 ErrorId, uint8 ErrorType);
#endif

#if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
LOCAL_INLINE Std_ReturnType Fee_lReadDetSafetyCheck(const uint16 BlockNumber,
    const uint16 BlockOffset,
    const uint8 *const DataBufferPtr,
    const uint16 Length,
    uint8 ApiId);
#endif

#if((FEE_RUNTIME_ERROR_DETECT == STD_ON) || \
  (((FEE_SAFETY_ENABLE == STD_ON) || (FEE_DEV_ERROR_DETECT == STD_ON)) && \
  (MCAL_AR_VERSION == MCAL_AR_422)))
LOCAL_INLINE Std_ReturnType Fee_lCancelDetSafetyCheck(void);
#endif

LOCAL_INLINE void Fee_lHandleCancelNotification(void);
LOCAL_INLINE void Fee_lHandleUsrJobErrorNotification(Fls_17_Dmu_Job_Type Job);
LOCAL_INLINE void Fee_lHandleReadJobEndNotification(void);
#if (FEE_INITCHECK_API == STD_ON)
LOCAL_INLINE uint32 Fee_lCalDataStructCrc(void);
#endif

#define FEE_STOP_SEC_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safe gaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"

/******************************************************************************
**                      Global Constant Definitions                          **
******************************************************************************/

/******************************************************************************
**                      Global Variable Definitions                          **
******************************************************************************/
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FEE_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
/*MISRA2012_RULE_19_01_JUSTIFICATION:File inclusion after pre-processor
directives is
 allowed only for MemMap.h*/
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safe gaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"
/* [cover parentID={5C702DD9-D7F5-4c61-9ED1-45F6D8353DFB}][/cover] */
static const Fee_ConfigType * Fee_CfgPtr ;

#if (FEE_INITCHECK_API == STD_ON)

static uint32 Fee_DataStrcutInitCrc;

#endif

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FEE_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_32
/*MISRA2012_RULE_19_01_JUSTIFICATION:File inclusion after
pre-processor directives is
 allowed only for MemMap.h*/
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safe gaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"



/******************************************************************************
**                      Private Constant Definitions                          *
******************************************************************************/
/* FEE state page Non Zero Data structure */
#define FEE_START_SEC_CONST_ASIL_B_LOCAL_32
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

static const uint32 Fee_StateHalf[] = { 0xFFFFFFC6U, 0xFFFFFFFFU,
                                        0xFFFFFFC6U, 0xFFFFFFFFU,
                                        0xFFFFFFC6U, 0xFFFFFFFFU,
                                        0xFFFFFFC6U, 0xFFFFFFFFU,
                                        0xFAFA5FC6U
                                      };

#endif

#define FEE_STOP_SEC_CONST_ASIL_B_LOCAL_32
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"
/******************************************************************************
**                      Private Variable Definitions                         **
******************************************************************************/

/******************************************************************************
**                      Global Function Definitions                          **
******************************************************************************/
#define FEE_START_SEC_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safe gaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"

/******************************************************************************
** TRACEABILITY: [cover parentID={35CCD881-754A-4bd0-94B3-858BE25F259C}]     **
**                                                                           **
** Syntax : void Fee_Init (const Fee_ConfigType* const ConfigPtr)            **
**                                                                           **
** [/cover]                                                                  **
**                                                                           **
** Service ID:  0x00                                                         **
**                                                                           **
** Sync/Async:  Asynchronous                                                 **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in) : ConfigPtr - Pointer to the selected configuration set.  **
**                                                                           **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    :  void                                                   **
**                                                                           **
** Description : Driver Module Initialization function                       **
**               This service shall initialize the Flash EEPROM Emulation    **
**               module using the values provided in the configuration set.  **
**                                                                           **
******************************************************************************/
/* [cover parentID={8C26701C-9198-4408-8462-33D3FEF6D160}]
Fee_Init
[/cover] */
/* [cover parentID={5ADF6F97-3CF5-4ef0-9522-0E11F965AAFB}]
Resistance against Resets and Power Failures
[/cover] */

void Fee_Init (const Fee_ConfigType* const ConfigPtr)
{

  Fee_StateDataType  *StateDataPtr;
  Fee_GcBlkInfoType  *GcBlkInfoPtr;
  Fee_CacheType      *BlockPtr;
  Fee_SectorInfoType *SectorInfoPtr;
  Fee_LastWrittenBlkInfoType  *LastBlkInfoPtr;

  uint32 Index;
  #if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
  uint32 EndAddr;
  uint8  DFlashStatus;
  uint8  ReturnVal;
  #endif

  /* [cover parentID={C8F64E4E-6C3A-4ac0-92C0-385C6AEEE49F}]
     Is Configuration pointer is NULL?
     [/cover] */
  /* [cover parentID={63531847-F84D-4dc2-B0E1-A33E2FBE6E94}]
     Imported SW interfaces
     [/cover] */
  if (ConfigPtr == NULL_PTR)
  {
    /* [cover parentID={C16B81AE-C6F3-4d6e-9CA2-AD009DDE7613}]
        DET or Safety is Enbaled
        [/cover] */
    #if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)

    Fee_lReportError(FEE_SID_INIT, FEE_E_PARAM_POINTER, FEE_DET_SAFETY_ERROR);
    #endif
  }   /*Check for state variable and block config pointer*/
  /* [cover parentID={64D645EE-018D-4faa-B2BF-0EF986A3A034}][/cover] */
  else if((ConfigPtr->FeeStatePtr != NULL_PTR) &&
          (ConfigPtr->FeeBlockConfigPtr != NULL_PTR))
  {
    Fee_CfgPtr = ConfigPtr;
    StateDataPtr = Fee_CfgPtr->FeeStatePtr;
    SectorInfoPtr = StateDataPtr->FeeSectorInfo;


    /* Initialize the state variables of various state machines */

    /* Initialize the cache related variables */
    /* [cover parentID={3511BD2D-D381-43b0-A336-4625BC78F4C6}][/cover] */
    Index = FEE_RESET;
    do
    {
      BlockPtr = &(StateDataPtr->FeeBlockInfo[Index]);
      BlockPtr->Address = FEE_RESET;
      BlockPtr->BlockSize = FEE_RESET;
      BlockPtr->BlockNumber = FEE_RESET;
      BlockPtr->Status.Valid = FEE_RESET;
      BlockPtr->Status.Consistent = FEE_RESET;
      BlockPtr->Status.Copied = FEE_RESET;
      BlockPtr->Status.PrevCopyValid = FEE_RESET;
      BlockPtr->Status.PrevCopyConsistent = FEE_RESET;
      BlockPtr->Status.PrevCopyCopied = FEE_RESET;
      BlockPtr->PrevCopyAddress = FEE_RESET;
      BlockPtr->PrevBlkSize = FEE_RESET;

      Index++;
    } while(Index < (uint32)(FEE_TOTAL_BLOCK_COUNT));
    StateDataPtr->FeeCacheState = FEE_CACHE_IDLE;

    StateDataPtr->FeeGCUnconfigBlkCopyIndex = FEE_RESET;
    StateDataPtr->FeeUncfgBlksExceeded = FEE_RESET;
    StateDataPtr->FeeUnConfigBlockCount = FEE_RESET;

    GcBlkInfoPtr = &(StateDataPtr->FeeGcCurrBlkInfo);
    GcBlkInfoPtr->BlockNumber = FEE_RESET;
    GcBlkInfoPtr->PageCount = FEE_RESET;
    GcBlkInfoPtr->Addr = FEE_RESET;
    GcBlkInfoPtr->Consistent = FEE_RESET;

    for(Index = FEE_RESET; Index < FEE_MAX_NUM_OF_BLKS_IN_WL; Index++)
    {
      StateDataPtr->FeeGcLWBGcSrcAddr[Index] = FEE_RESET;
    }
    StateDataPtr->FeeGcBlkIndexInWL = FEE_RESET;

    StateDataPtr->FeeGcState = FEE_GC_IDLE;
    StateDataPtr->FeeGCCopyIndex = FEE_RESET;
    StateDataPtr->FeeGcSrcAddr = FEE_RESET;
    StateDataPtr->FeeGcDestAddr = FEE_RESET;
    StateDataPtr->FeeDisableGCStart = (boolean)FALSE;
    StateDataPtr->FeeGCImmBlkWrite = (boolean)FALSE;

    #if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
    StateDataPtr->FeeEraseSuspendStatus = FEE_ERASE_NOT_SUSPENDED;
    StateDataPtr->FeeEraseResumeDemReported = FEE_RESET;
    #endif

    /* Initialize the InitGC related variables */
    StateDataPtr->FeeInitGCState = FEE_INITGC_IDLE;
    StateDataPtr->FeePrepDFLASHState = FEE_PREPDF_ERASE_S0;
    StateDataPtr->FeeRepairStep = FEE_REPAIR_IDLE;
    StateDataPtr->FeeGcResumeState = FEE_RESET;

    /* Initialize the Read and Write related variables */
    StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_NO_REQ;
    StateDataPtr->FeeLastWrittenBlockDirty = FEE_LWB_NOT_DIRTY;

    LastBlkInfoPtr = &(StateDataPtr->FeeLastWrittenBlkInfo);
    LastBlkInfoPtr->Addr = FEE_RESET;
    LastBlkInfoPtr->BlockNumber = FEE_RESET;
    LastBlkInfoPtr->PageCount = FEE_RESET;
    LastBlkInfoPtr->Status.Valid = FEE_RESET;
    LastBlkInfoPtr->Status.Consistent = FEE_RESET;
    LastBlkInfoPtr->Status.Copied = FEE_RESET;
    LastBlkInfoPtr->Status.PrevCopyValid = FEE_RESET;
    LastBlkInfoPtr->Status.PrevCopyConsistent = FEE_RESET;
    LastBlkInfoPtr->Status.PrevCopyCopied = FEE_RESET;

    StateDataPtr->FeeNextFreePageAddr = FEE_RESET;
    StateDataPtr->FeeBlockStartAddr = FEE_RESET;

    StateDataPtr->FeeUserReadDestPtr = (uint8*)NULL_PTR;
    #if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
    /* Initialize common variables */
    Fee_lClearFeeReadWriteBuffer();
    Fee_lClearFeeGcReadWriteBuffer();
    #endif

    StateDataPtr->FeeBlkPageCount = (Fee_PageType)FEE_RESET;
    StateDataPtr->FeeCurrReqBlockNum = FEE_RESET;
    StateDataPtr->FeeUserWriteBytesCount = FEE_RESET;
    StateDataPtr->FeeUserJobFailCount = FEE_RESET;

    StateDataPtr->FeeStatusFlags.FeeBlkInvalidStatus = FEE_RESET;
    StateDataPtr->FeeStatusFlags.FeeBlkModified = FEE_RESET;
    StateDataPtr->FeeStatusFlags.FeeWriteInvldQSeraseAPICalled = FEE_RESET;
    StateDataPtr->FeeStatusFlags.FeeStartInitGC = FEE_RESET;
    StateDataPtr->FeeStatusFlags.FeeCurrSector = FEE_RESET;

    StateDataPtr->FeeMainJob = FEE_MAIN_UNINIT;
    StateDataPtr->FeeJobResult = MEMIF_JOB_OK;
    StateDataPtr->FeeIntrJob = FEE_NO_JOB;
    StateDataPtr->FeeIntrJobStatus = FEE_JOB_IDLE;
    StateDataPtr->FeeIntrJobResult = FEE_JOB_PASS;
    StateDataPtr->FeeUserJobStatus = FEE_JOB_IDLE;
    StateDataPtr->FeeUserJobResult = FEE_JOB_PASS;
    StateDataPtr->FeeIntrJobFailCount = FEE_RESET;

    StateDataPtr->FeeWLAffectedType = FEE_LWB_NOT_AFFECTED;
    StateDataPtr->FeeWriteAffectedAddr = FEE_RESET;

    /* Initialize Sector State information */
    /* [cover parentID={E877ED96-C8FA-4a00-A1DE-878B705D6B4A}][/cover] */
    for(Index = FEE_RESET; Index < FEE_SECTORS; Index++)
    {
      SectorInfoPtr[Index].State = FEE_RESET;
      SectorInfoPtr[Index].StateCount = FEE_RESET;
      SectorInfoPtr[Index].UnerasableWLCount = FEE_RESET;
      SectorInfoPtr[Index].UnerasableWLAddr[0] = FEE_RESET;
      SectorInfoPtr[Index].UnerasableWLAddr[1] = FEE_RESET;
      SectorInfoPtr[Index].Status.Dirty = FEE_RESET;
      SectorInfoPtr[Index].Status.Used = FEE_RESET;
      SectorInfoPtr[Index].StatePageAddr = FEE_RESET;
      SectorInfoPtr[Index].NextFreeWLAddr = FEE_RESET;
      SectorInfoPtr[Index].NonZeroWLCount = FEE_RESET;
      SectorInfoPtr[Index].NonZeroWLAddr[0] = FEE_RESET;
      SectorInfoPtr[Index].NonZeroWLAddr[1] = FEE_RESET;
    }
    StateDataPtr->FeeStateCount = FEE_RESET;
    StateDataPtr->FeeSectorCount = FEE_RESET;
    StateDataPtr->FeeComparedLen = FEE_RESET;
    StateDataPtr->FeeReadLen = FEE_RESET;
    StateDataPtr->FeeUnErasableWLAddrTemp[0] = FEE_RESET;
    StateDataPtr->FeeUnErasableWLAddrTemp[1] = FEE_RESET;
    StateDataPtr->FeeUnErasableWLCountTemp = FEE_RESET;

    #if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
    /* Read sector information */
    for(Index = FEE_RESET; Index < FEE_SECTORS; Index++)
    {
      if(Index == FEE_RESET)
      {
        EndAddr = FEE_DFLASH_BANK0_BASE;
      }
      else
      {
        EndAddr = FEE_DFLASH_BANK1_BASE;
      }
      StateDataPtr->FeeCurrSectSrcAddr = EndAddr +
                                         (FEE_DFLASH_SECTOR_SIZE -
                                          FEE_DFLASH_WORDLINE_SIZE);
      do
      {
        ReturnVal = Fee_lGetSectorInfo(Index, EndAddr);
      } while(ReturnVal == FEE_SP_INIT);
    }

    DFlashStatus = Fee_lBuildDFlashStatus();

    /* Initialize for quasi static blocks if configured */
    #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)

    StateDataPtr->FeeQsBlockVirginCount = FEE_RESET;
    Fee_lQsInit();

    #endif

    #if (FEE_CANCELL_ALL_API == STD_ON) && \
        (FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)

    StateDataPtr->FeeCancelallGCstate = FEE_GC_NOT_CANCLD;

    #endif

    StateDataPtr->FeeEraseVerErr = FEE_RESET;
    StateDataPtr->FeeProgVerErr  = FEE_RESET;
    Fee_lSetInitGc(DFlashStatus);

    if( Fee_CfgPtr->FeeGCConfigSetting.FeeGcRestartPoint ==
        (uint32)FEE_GC_RESTART_INIT )
    {
      /* [cover parentID={14D5A81B-1A65-400a-B2D0-A89AAE9BED19}]
      Assign FeeStartInitGC = 1
      [/cover] */
      /* Start Init GC:
      Check the current state of the sectors and bring them to normal state*/
      StateDataPtr->FeeStatusFlags.FeeStartInitGC = FEE_SET ;
    }

    #else
    StateDataPtr->FeeQsBlockVirginCount = FEE_RESET;
    Fee_lQsInit();
    /* [cover parentID={EFCEB24D-1879-4c0d-97A3-39C9A8BE68F1}]
        Set FeeInitAPICalled , indicating Fee Init API is called
    [/cover] */
    StateDataPtr->FeeStatusFlags.FeeStartInitGC = FEE_SET ;

    #endif

    #if (FEE_INITCHECK_API == STD_ON)

    Fee_DataStrcutInitCrc = Fee_lCalDataStructCrc();

    #endif

  }
  else
  {

    #if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)

    Fee_lReportError(FEE_SID_INIT, FEE_E_PARAM_POINTER, FEE_DET_SAFETY_ERROR);
    #endif
    /* Report DET-Safety error if DET-Safety is Enabled */
  }
  /* [cover parentID={5F24109C-8447-4116-B653-3A53C9716F11}]
      Return
     [/cover] */

} /*End of Fee_Init*/

#if ((FEE_SET_MODE_SUPPORTED == STD_ON) && \
    (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)) && \
    (MCAL_AR_VERSION == MCAL_AR_422)
/*******************************************************************************
** TRACEABILITY: []                                                           **
**                                                                            **
** Syntax : void Fee_SetMode( const MemIf_ModeType Mode )                     **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x01                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  MemIf_ModeType - Desired mode for the underlying flash  **
**                                      driver.                               **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  void                                                    **
**                                                                            **
** Description : This API sets the mode of the underlying flash driver        **
**                                                                            **
*******************************************************************************/
/* [cover parentID={272C7054-BCB3-4896-8A50-62B33C986E77}]Fee_SetMode[/cover] */
/* [cover parentID={1905C7A8-06F4-4ae3-9AD0-A438DBF66138}]
Fee_SetMode
[/cover] */
void Fee_SetMode(const MemIf_ModeType Mode)
{
  /* [cover parentID={2632D8CE-7764-4eef-84D2-AF09AC67A8EA}]
      DET enabled
     [/cover] */
  uint8              Error;
  MemIf_StatusType   FeeStatus;
  #if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)

  /* [cover parentID={2E09D74B-AC0E-4f9f-8ACD-59AF9D9BA2D0}]
      Is the configuration pointer NULL?
      [/cover] */
  /*Check for configuration pointer(Fee_CfgPtr)for null as part safety check */
  if(Fee_CfgPtr != NULL_PTR)
  #endif
  {
    /* [cover parentID={2632D8CE-7764-4eef-84D2-AF09AC67A8EA}]
        DET or safety enabled
       [/cover] */
    Error = FEE_RESET;
    /* [cover parentID={CCE44DC3-B99E-4da5-8892-DC625DA7592C}]
        Get Fee status
        [/cover] */
    /* Get the FEE status */
    FeeStatus = Fee_lGetStatus();
    /* [cover parentID={B391E83E-F746-4e00-B284-5FCE637876FA}]
    Is any user or internal job ongoing?
    [/cover] */
    if(FeeStatus != MEMIF_IDLE)
    {
      /* [cover parentID={0C2893D1-2C1F-41c5-8447-8BC0CD5183E7}]
      Is driver state is internal busy
      [/cover] */
      /* If busy, report error */
    #if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
      if(FeeStatus == MEMIF_BUSY)
      {
         /* [cover parentID={57D00748-5476-41f7-A9B3-07A4186C0828}]
         Report FEE_E_BUSY DET
         [/cover] */
        Fee_lReportError(FEE_SID_SETMODE, FEE_E_BUSY, FEE_DET_SAFETY_ERROR);
      }
    #endif
      Error = FEE_SET;
    }
    if(Error == FEE_RESET)
    {
      /* set mode of FLS */
      Fls_17_Dmu_SetMode(Mode);
    }
  }
  #if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
  else
  {
    /* [cover parentID={73D8CF32-6D88-4c5d-919D-8A233A83931D}]
        Report FEE_E_UNINIT DET
       [/cover] */
    Fee_lReportError(FEE_SID_SETMODE, FEE_E_UNINIT, FEE_DET_SAFETY_ERROR);
  }
  #endif
  /* [cover parentID={BA05C25B-11F6-4fe4-86EA-96E6EFF55374}]
      Return
     [/cover] */
}/* End of Fee_SetMode */

#endif /* #if (FEE_SET_MODE_SUPPORTED == STD_ON) */

#if ((FEE_SET_MODE_SUPPORTED == STD_ON) && \
    (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)) && \
    (MCAL_AR_VERSION == MCAL_AR_440)
/*******************************************************************************
** TRACEABILITY: [cover parentID={22E4911E-7754-4392-8BBA-6810E8AD3CA7}]      **
**                                                                            **
** Syntax : void Fee_SetMode( const MemIf_ModeType Mode )                     **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x01                                                          **
**                                                                            **
** Sync/Async: Asynchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  MemIf_ModeType - Desired mode for the underlying flash  **
**                                      driver.                               **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  void                                                    **
**                                                                            **
** Description : This API sets the mode of the underlying flash driver        **
**                                                                            **
*******************************************************************************/
void Fee_SetMode(const MemIf_ModeType Mode)
{
  MemIf_StatusType   FeeStatus;
  Fee_StateDataType  *StateDataPtr;

  /* [cover parentID={2E09D74B-AC0E-4f9f-8ACD-59AF9D9BA2D0}]
      Is the configuration pointer NULL?
      [/cover] */
  /*Check for configuration pointer(Fee_CfgPtr)for null as part safety check */
  if(Fee_CfgPtr != NULL_PTR)
  {
    /* [cover parentID={C24E9C5A-73A7-4122-8ADD-83AE39092A99}]]
     Get Fee status
    [/cover] */
    FeeStatus = Fee_lGetStatus();
    /* [cover parentID={21B5ACC3-E4EE-409b-AB43-B8EDD29DFFDF}]
    Is the driver is initialized
    [/cover] */
    if(FeeStatus != MEMIF_UNINIT)
    {
        StateDataPtr = Fee_CfgPtr->FeeStatePtr;

      /* Get the FEE status */
      /* [cover parentID={2CBD812F-71A9-42d2-ADD9-251001AE7A5A}]
      Is driver is busy with internal job
      [/cover] */
      if(FeeStatus == MEMIF_BUSY_INTERNAL)
      {
        /* [cover parentID={244DF83E-637C-424c-900B-D59C6C41569A}]
        Register the pending set mode request
        [/cover] */
        StateDataPtr->FeeSetModeReqPend = FEE_SET;
        StateDataPtr->FeeChangeReqMode = Mode;
      }
      else if(FeeStatus == MEMIF_IDLE)
      {
        /* [cover parentID={A29D45E2-1189-4e9b-8901-BF07A4FE4058}]
        Set mode of FLS
        [/cover] */
        /* set mode of FLS */
        Fls_17_Dmu_SetMode(Mode);
      }
      /* [cover parentID={0189B8AE-401E-481a-A67D-00DC6859FC94}]
      Is driver is busy with user job
      [/cover] */
      else
      {
      #if (FEE_RUNTIME_ERROR_DETECT== STD_ON)
        /* [cover parentID={83454225-3E38-48b0-AAB2-6B87F00FBF74}]
        Report FEE_E_BUSY DET
        [/cover] */
        /* If busy, report error */
        Fee_lReportError(FEE_SID_SETMODE, FEE_E_BUSY, FEE_RUNTIME_ERROR);
      #endif
      }
    }
    /* [cover parentID={2632D8CE-7764-4eef-84D2-AF09AC67A8EA}]
     DET or safety enabled
    [/cover] */
    #if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
    else
    {
      /* [cover parentID={5B668FF2-32E7-4247-AA94-FD75CAF92CD6}]
      Report FEE_E_UNINIT DET
      [/cover] */
      Fee_lReportError(FEE_SID_SETMODE, FEE_E_UNINIT, FEE_DET_SAFETY_ERROR);
    }
    #endif
  }
  #if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
  else
  {
    /* [cover parentID={5B668FF2-32E7-4247-AA94-FD75CAF92CD6}]
    Report FEE_E_UNINIT DET
    [/cover] */
    Fee_lReportError(FEE_SID_SETMODE, FEE_E_UNINIT, FEE_DET_SAFETY_ERROR);
  }
  #endif
  /* [cover parentID={BA05C25B-11F6-4fe4-86EA-96E6EFF55374}]
      Return
     [/cover] */
}/* End of Fee_SetMode */


#endif


/*******************************************************************************
** TRACEABILITY: [cover parentID={01E4E203-8396-4c5a-8D69-7498B9450CF6}]      **
**                                                                            **
** Syntax : Std_ReturnType Fee_Read(const uint16 BlockNumber,                 **
**           const uint16 BlockOffset,uint8 * const DataBufferPtr,            **
**           uint16 Length )                                                  **
**                                                                            **
** [/cover]                                                                   **
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
**                    E_OK : Request accepted                                 **
**                    E_NOT_OK : Request is not accepted. FEE module          **
**                    is busy in servicing other request.                     **
** Description : This function shall take the block start address and         **
** offset and calculate the corresponding memory read address. The address    **
** offset and length parameter can take any value within the given block      **
** this allows reading of an arbitrary number of bytes from an arbitrary start**
** address inside a logical block.                                            **
**                                                                            **
*******************************************************************************/
/* [cover parentID={98AD05C0-8E14-4115-8F67-B9A8041F57A7}]
Fee_Read
[/cover] */
Std_ReturnType Fee_Read(const uint16 BlockNumber,
                        const uint16 BlockOffset,
                        uint8 *const DataBufferPtr,
                        const uint16 Length)
{


  Std_ReturnType       ReturnValue;
  #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
  uint16               BlkIdx;
  Fee_StateDataType    *StateDataPtr;
  #endif
  /* [cover parentID={1CC0BEAF-AEC4-405c-B302-764B43B5A677}][/cover] */
  if (Fee_CfgPtr != NULL_PTR)
  {
    /* [cover parentID={DA1C5A03-C9D9-41cc-9994-F09270D9341C}]
       DET or safety enabled
       [/cover] */
    #if(MCAL_AR_VERSION == MCAL_AR_440)
    if(Fee_lGetStatus() != MEMIF_UNINIT)
    #endif
    {
    #if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
      /* [cover parentID={EA3ECE0D-3FA4-478c-94E9-4178292BE386}][/cover]*/
      /* [cover parentID={E43F3552-DD01-4714-89B2-CD53085F7B35}][/cover]*/
      /* [cover parentID={44D0A38B-BEAB-4e9c-96BB-AA4D71CD56DC}][/cover]*/
      ReturnValue = Fee_lReadDetSafetyCheck(BlockNumber, BlockOffset,
                                          DataBufferPtr, Length, FEE_SID_READ );
      /* [cover parentID={FFCC3DB6-6879-4e2b-AED0-A9DC2C5A8A84}][/cover]*/
      if(ReturnValue != E_NOT_OK)
      #endif
      {
        /* [cover parentID={27ABBB41-5DB3-41dd-9393-3C3C997010FB}]
           QS data block supported
           [/cover] */
      #if(FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)

        StateDataPtr = Fee_CfgPtr->FeeStatePtr;
        BlkIdx = Fee_lGetUsrBlockIndex(BlockNumber);

        StateDataPtr->FeePendReqInfo.CacheIndex = BlkIdx;
        /* [cover parentID={13FCC1DB-57DE-45d3-AADD-472C333D926B}]
            Is it for QS user?
            [/cover] */
        /* [cover parentID={4FFD7EF7-6FB8-4845-A2E3-2760C7BE6563}]
            Get block index
           [/cover] */
        /* [cover parentID={331E8782-EC9A-442d-AD29-C2D2E5206977}]
            Test for request type
           [/cover] */
        if(Fee_CfgPtr->FeeBlockConfigPtr[BlkIdx].FeeUser ==
            (uint8)FEE_QUASI_STATIC_USER)
        {
          /* [cover parentID={09217FC4-21E4-4728-AD66-7C8F9476839B}]
             Register QS read request and update Flag status
             [/cover] */
          /* register quasi static block request */
          ReturnValue = Fee_lRegisterQsRead(BlockNumber, BlockOffset,
                                          DataBufferPtr, Length);
        }
        else
        #endif
        {
          /* [cover parentID={88ECB633-69AC-4911-8F23-AD56B2B19A9B}]
          Register NVM read request and update Flag status
          [/cover] */
          /* register nvm request */
          ReturnValue = Fee_lRegisterNvmRead(BlockNumber, BlockOffset,
                                           DataBufferPtr, Length, FEE_RESET);
        }
      }
    }
    #if(MCAL_AR_VERSION == MCAL_AR_440)
    else
    {
      ReturnValue = E_NOT_OK;
    #if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
      /* [cover parentID={4059E72C-2B05-43a1-91BB-26A7FE63D453}][/cover] */
      Fee_lReportError(FEE_SID_READ, FEE_E_UNINIT, FEE_DET_SAFETY_ERROR);
    #endif
    }
    #endif
  }
  else
  {
    /* [cover parentID={08827D4A-F03C-4c07-8B21-1A66B88D2E9B}]
    Set Flag as E_NOT_OK
    [/cover] */
    ReturnValue = E_NOT_OK;
    #if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
    /* [cover parentID={4059E72C-2B05-43a1-91BB-26A7FE63D453}][/cover] */
    Fee_lReportError(FEE_SID_READ, FEE_E_UNINIT, FEE_DET_SAFETY_ERROR);
    #endif
  }

  /* [cover parentID={CEBB81F8-0C10-40d8-A895-2DBA80493D87}]
  Return Flag status
  [/cover] */
  return(ReturnValue);
  /* [cover parentID={9ED72611-8C9A-46d5-93B5-457408211296}]
  Return
  [/cover] */

} /* End of Fee_Read */

/*******************************************************************************
** TRACEABILITY: [cover parentID={D93EC71E-D34B-46ed-99C1-8FCF19C0E7DB}]      **
**                                                                            **
** Syntax : Std_ReturnType Fee_Write(const uint16 BlockNumber,                **
**                    const uint8 *const DataBufferPtr)                       **
**                                                                            **
** [/cover]                                                                   **
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
**                    E_OK : Request accepted                                 **
**                    E_NOT_OK : Request is not accepted. FEE module          **
**                    is busy in servicing other request.                     **
**                                                                            **
** Description : This function shall take the logical block number and        **
** determine the corresponding memory write address. This routine will        **
** perform the block write operation on DFLASH (DF_EEPROM).                   **
**                                                                            **
*******************************************************************************/
/* [cover parentID={9BF2094B-1F02-4294-978A-3CC5BEE6F977}]
Fee_write
[/cover] */

Std_ReturnType Fee_Write(const uint16 BlockNumber,
                         const uint8 *const DataBufferPtr)
{
  #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
  Fee_StateDataType     *StateDataPtr;
  #endif

  const Fee_BlockType*   BlockPtr;
  uint16                 UserBlockIndex;
  Std_ReturnType         ReturnValue;

  /*Check for configuration pointer(Fee_CfgPtr)for null as part safety check */
  /* [cover parentID={C330EC19-1B27-483d-9F93-50A8BBEF137B}]
  Is configuration pointer NULL?
  [/cover] */
  if(Fee_CfgPtr != NULL_PTR)
  {
    #if(MCAL_AR_VERSION == MCAL_AR_440)
    if(Fee_lGetStatus() != MEMIF_UNINIT)
    #endif
    {
      UserBlockIndex = Fee_lGetUsrBlockIndex(BlockNumber);
      BlockPtr = &(Fee_CfgPtr->FeeBlockConfigPtr[UserBlockIndex]);

      /* [cover parentID={5D986A7A-A25D-46e0-B1A2-C507BD67870D}]
      DET and SAFETY enabled
      [/cover] */
      #if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
      ReturnValue = E_OK;

      /* [cover parentID={54C7D2CF-C17A-4808-A87B-E6E44C955019}]
         [/cover] */

      /* [cover parentID={CD11A821-E091-4690-8B0E-E0C7C168377F}]
      Is block number invalid?
      [/cover] */
      /* Check if the block number is correct */
      if(UserBlockIndex == FEE_LOG_BLOCK_NOT_FOUND)
      {
        /* [cover parentID={035716BA-D7A0-4e6d-BA03-266CDC60C242}]
        Report FEE_E_INVALID_BLOCK_NO DET
        [/cover] */
        Fee_lReportError(FEE_SID_WRITE, FEE_E_INVALID_BLOCK_NO, FEE_DET_SAFETY_ERROR);

        /* [cover parentID={54C7D2CF-C17A-4808-A87B-E6E44C955019}]
        Set Flag status as E_NOT_OK
        [/cover] */
        ReturnValue = E_NOT_OK;
      }
      /* [cover parentID={90D30799-F868-486d-BCF9-6A9E81AFC230}]
      Is buffer pointer NULL?
      [/cover] */
      /* Check if the buffer pointer is NULL */
      else if(DataBufferPtr == (uint8*)NULL_PTR)
      {
        /* [cover parentID={A51384D5-E04A-49de-A1FE-A37570AD26A9}]
        Report FEE_E_PARAM_POINTER DET
        [/cover] */
        Fee_lReportError(FEE_SID_WRITE, FEE_E_PARAM_POINTER, FEE_DET_SAFETY_ERROR);
        /* [cover parentID={54C7D2CF-C17A-4808-A87B-E6E44C955019}]
        Set Flag status as E_NOT_OK
        [/cover] */
        ReturnValue = E_NOT_OK;
      }
      else
      {
        /* dummy else */
      }

      if (ReturnValue != E_NOT_OK)
      #endif /* End of FEE_DEV_ERROR_DETECT == STD_ON */
      {

        /* [cover parentID={9408C6E1-78CA-44d9-A113-984559B0BC0C}]
        Check for Fee user
        [/cover] */
        #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
        StateDataPtr = Fee_CfgPtr->FeeStatePtr;
        StateDataPtr->FeePendReqInfo.CacheIndex = UserBlockIndex;

        /* [cover parentID={F5E19301-3D1B-464f-B8DF-D5AB7426A10D}]
        Is it for Quasi static user?
        [/cover] */
        if(Fee_CfgPtr->FeeBlockConfigPtr[UserBlockIndex].FeeUser ==
          (uint8)FEE_QUASI_STATIC_USER)
        {
          /* [cover parentID={5E7361C7-B818-4fdc-8798-94B5D8FDB1BA}]
          Register QS write request and update Flag status
          [/cover] */
          /* register quasi static block request */
          ReturnValue = Fee_lRegisterQsWrite(DataBufferPtr, BlockPtr);
        }
        else
        #endif
        {
          /* [cover parentID={9CF0435A-C83A-4862-A4D6-F6B24EBF01FF}]
          Register NVM write request and update Flag status
          [/cover] */
          /* register nvm request */
          ReturnValue = Fee_lRegisterNvmWrite(DataBufferPtr, BlockPtr);
        }

      }
    }
    #if(MCAL_AR_VERSION == MCAL_AR_440)
    else
    {
      ReturnValue = E_NOT_OK;
      #if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
      /* [cover parentID={85CF0E69-4B89-4693-B69C-D559725B6FDF}]
      Report FEE_E_UNINIT DET
      [/cover] */
      Fee_lReportError(FEE_SID_WRITE, FEE_E_UNINIT, FEE_DET_SAFETY_ERROR);
      #endif
    }
    #endif
  }
  else
  {

    ReturnValue = E_NOT_OK;
    #if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
    /* [cover parentID={85CF0E69-4B89-4693-B69C-D559725B6FDF}]
    Report FEE_E_UNINIT DET
    [/cover] */
    Fee_lReportError(FEE_SID_WRITE, FEE_E_UNINIT, FEE_DET_SAFETY_ERROR);
    #endif

  }


  /* [cover parentID={B5FAF6DF-269B-495a-A2FB-882234AA9528}]
  Return Flag status
  [/cover] */
  return(ReturnValue);
  /* [cover parentID={AE18F765-4BBD-4d68-AF6A-3FD069990AE6}]
  Return
  [/cover] */
}
/* End of Fee_Write */

/*CYCLOMATIC_Fee_Cancel_JUSTIFICATION: Fee_Cancel has
to determine all the states of ongoing operation and then cancel.
It is broken properly into various stages using switch case which cannot be broken
further. If it is broken into more functions to fix RSM, the code readability
will get affected.
*/
/******************************************************************************
** TRACEABILITY: [cover parentID={1AC3C3C4-3B3C-468d-A5B2-684E3D5D03F1}]     **
**                                                                           **
** Syntax : void Fee_Cancel(void)                                            **
**                                                                           **
** [/cover]                                                                  **
**                                                                           **
** Service ID: 0x04                                                          **
**                                                                           **
** Sync/Async:  Synchronous                                                  **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in) :  None                                                   **
**                                                                           **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    :  void                                                   **
**                                                                           **
** Description : Service to call the cancel function of the underlying flash **
** driver.This function shall cancels a pending request.                     **
** Note: An ongoing write request is not cancelled. However, a queued        **
** write request is cancelled. Any read request either queued or under       **
** execution is cancelled.                                                   **
**                                                                           **
******************************************************************************/
/* [cover parentID={43CB653F-D9FC-41ef-B842-8DD9AF9F04F2},
{7B564D5D-0FF2-4354-930B-A2008C7B3245}]
Fee_Cancel
[/cover] */
void Fee_Cancel(void)
{

  const Fee_StateDataType  *StateDataPtr;
  uint8 NotifyCancel;
   /* [cover parentID={A8F80E20-A667-4bcf-BED4-73D9BC7BBE34}]
  DET or safety enabled
  [/cover] */
  #if((FEE_RUNTIME_ERROR_DETECT == STD_ON) || \
  (((FEE_SAFETY_ENABLE == STD_ON) || (FEE_DEV_ERROR_DETECT == STD_ON)) && \
  (MCAL_AR_VERSION == MCAL_AR_422)))
  Std_ReturnType  Error;
  #endif
  /* [cover parentID={431752DA-0ABE-4d79-AB16-D26A3C494824}][/cover] */

  NotifyCancel  = FEE_RESET;
  /* [cover parentID={46B369AC-83B5-45d7-99D8-16DCFBCC033D}][/cover] */
  if(Fee_lInitSafetyCheck(FEE_SID_CANCEL) == E_OK)
  {
    #if(FEE_RUNTIME_ERROR_DETECT == STD_ON) || \
    (((FEE_SAFETY_ENABLE == STD_ON) || (FEE_DEV_ERROR_DETECT == STD_ON))  && \
    (MCAL_AR_VERSION == MCAL_AR_422))

    /* [cover parentID={431752DA-0ABE-4d79-AB16-D26A3C494824}]
    Get the error status through calling the function
    [/cover] */
    Error = Fee_lCancelDetSafetyCheck();
    if(Error == E_OK)
    #endif
    {
      StateDataPtr = Fee_CfgPtr->FeeStatePtr;
      switch(StateDataPtr->FeePendReqStatus)
      {
        /* [cover parentID={BCB57445-F21F-495e-A682-43F524055698}][/cover] */
        /* All these cases mean that the job is requested but not started */
        case FEE_REQ_READ:
        case FEE_REQ_NORM_WRITE:
        case FEE_REQ_IMM_WRITE:
        {

          /* Job is in pending state and their is no job requested to fls.
          Set flag  NotifyCancel for triggering notification to user */
          NotifyCancel  = FEE_SET;
          break;
        }

        /* The following cases mean that the read job is on-going */
        case FEE_PEND_PREV_READ_REQ:
        case FEE_PEND_PREV_READ_NOTIF:
        {
          /* [cover parentID={A7271201-033A-463e-B2E6-9B2A8ADEA899}][/cover] */
          if(StateDataPtr->FeeUserJobStatus == FEE_JOB_REQSTD)
          {
            /* [cover parentID={65DDD0F0-B824-4acf-8670-5B83B01098A7}]
            Set flag  NotifyCancel for triggering notification to user
            (Notify cancel only if UserJobStatus is Job Requested)
            Cancel the read job
            [/cover] */
            /* Cancels the read job , notification to user will be triggered
            job fee_error notification function. This function is called by
            fls driver when cancel is requested */
            Fls_17_Dmu_CancelNonEraseJobs();
          }
          else
          {
            /* Their is no request sent to fls , so
            Set flag  NotifyCancel for triggering notification to user */
            NotifyCancel  = FEE_SET;
          }
          break;
        }
        /* [cover parentID={7982EEAA-B105-4d9d-AA43-DD4CC8599100}][/cover] */   
        #if(FEE_ONGOING_WRITE_CANCEL_SUPPORT == STD_ON)             
        case FEE_PEND_PREV_WRITE_REQ:           
        case FEE_PEND_INTR_WRITE:
        case FEE_PEND_INTR_READ:
        {
            /* Their is no request sent to fls , so
            Set flag  NotifyCancel for triggering notification to user */
            NotifyCancel  = FEE_SET;            
            break;          
        }
        
            
        case FEE_PEND_PREV_COMPARE: 
        case FEE_PEND_INTR_COMPARE:     
        {   
            /* cancel ongoing write*/
            Fee_lCancelWrite();
            break;
                
        }       
        #endif
        /* All other pend request states
        Example: FEE_PEND_PREV_NO_REQ:
        */
        default:
        {
          break;
        }
      }
      /* [cover parentID={2E4DCC84-5788-4f1e-9B45-DF4D6B11F6C3}]
      Is cancel notification call required?
      [/cover] */
      /* Check if cancel notification call is required */
      if(NotifyCancel  == FEE_SET)
      {
        /* [cover parentID={76226842-41D1-47d1-A7DD-5630D1F55A1C}]
        Trigger the error notification implying the job is cancelled
        [/cover] */
        /*call handle user job with error = FEE_CANCELto trigger only error
        notification */
        Fee_lHandleUsrJobFailure(FEE_CANCEL);
      }
    }
  }

  /* [cover parentID={2C015858-96DC-4466-AB3B-0913BD68009C}]
  Return
  [/cover] */
}
/*******************************************************************************
** TRACEABILITY: [cover parentID={226C491E-1CDC-467b-B1C7-34265C1D5390}]      **
**                                                                            **
** Syntax : MemIf_StatusType Fee_GetStatus(void)                              **
**                                                                            **
** [/cover]                                                                   **
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
** Description : Service to return the status of the driver.                  **
**                                                                            **
*******************************************************************************/
/* [cover parentID={257B750D-C0C9-47d1-B1E1-641B3FB9964D}]
Fee_GetStatus
[/cover] */
MemIf_StatusType Fee_GetStatus(void)
{

  MemIf_StatusType   ReturnStatus;

  /* Check if the Fee_Init API is called */
  /*[cover parentID={C6677223-02B7-4569-B3FC-7CB8E56B5623}] [/cover] */
  if(Fee_CfgPtr != NULL_PTR)
  {

    /* [cover parentID={63DFD354-F0AB-41f7-A591-A9D6689DAAB5}]
    Update Fee status accordingly
    [/cover] */
    ReturnStatus = Fee_lGetStatus();

  }
  else
  {
    /* [cover parentID={D174448D-7278-4e80-86C9-23521CD2EDBF}]
    Set return status as Fee uinitialised (MEMIF_UNINIT)
    [/cover] */
    ReturnStatus = MEMIF_UNINIT;
  }
  /* [cover parentID={BD705C64-BA6E-40b4-95A4-AEB95915D59F}]
  Return the status value
  [/cover] */
  return(ReturnStatus);

}/*End of Fee_GetStatus */

/*******************************************************************************
** TRACEABILITY: [cover parentID={851BA7DF-094F-4a18-99EB-5961F8038283}]      **
**                                                                            **
** Syntax : MemIf_JobResultType Fee_GetJobResult(void)                        **
**                                                                            **
** [/cover]                                                                   **
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
** Description : Service to query the result of the last accepted job issued  **
** by NVM.                                                                    **
**                                                                            **
*******************************************************************************/
/* [cover parentID={D12859D4-DC09-4009-AE0B-66AA09D02D76}]
Fee_GetJobResult
[/cover] */
MemIf_JobResultType Fee_GetJobResult(void)
{
  const Fee_StateDataType  *StateDataPtr;
  MemIf_JobResultType ReturnValue = MEMIF_JOB_FAILED;

  /*Check for configuration pointer(Fee_CfgPtr)for null as part safety check */
  /* Check if the Fee_Init API is called */

  #if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
  /*[cover parentID={85712388-9829-492f-8731-18B24E0B3A45}] [/cover] */
  if(Fee_CfgPtr != NULL_PTR)
  #endif
  {
  #if(MCAL_AR_VERSION == MCAL_AR_440)
    if(Fee_lGetStatus() != MEMIF_UNINIT)
  #endif
    {
      StateDataPtr = Fee_CfgPtr->FeeStatePtr;
      ReturnValue = StateDataPtr->FeeJobResult;
    }
  #if (((FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)) \
  && (MCAL_AR_VERSION == MCAL_AR_440))
    else
    {
      Fee_lReportError(FEE_SID_GETJOBRESULT, FEE_E_UNINIT, FEE_DET_SAFETY_ERROR);
      ReturnValue = MEMIF_JOB_FAILED;
    }
  #endif
  }
  /* [cover parentID={FD197E65-EE8B-493a-ADC6-6C2BFA4F2601}]
  DET or safety enabled
  [/cover] */
  #if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
  else
  {

    /* [cover parentID={2939037D-26A7-4b0a-A227-653F5D286757}]
    Report DET error as FEE_E_UNINIT
    [/cover] */

    /* [cover parentID={3782FDE0-A93B-4780-8567-D0FDE7BC4D93}]
    Return MEMIF_JOB_FAILED
    [/cover] */

    Fee_lReportError(FEE_SID_GETJOBRESULT, FEE_E_UNINIT, FEE_DET_SAFETY_ERROR);
    ReturnValue = MEMIF_JOB_FAILED;
  }

  #endif
  /* [cover parentID={09E392A4-0F42-4cd7-8A98-F2E95A884302}]
  Return Fee job result
  [/cover] */
  return (ReturnValue);
  /* [cover parentID={1D49459A-C72F-416f-89D4-8F5D33736EF8}]
  Return the job result type
  [/cover] */
}/*End of Fee_GetJobResult */

/*******************************************************************************
** TRACEABILITY: [cover parentID={1D45F947-1794-4611-A1D4-C4FCB2C5F847}]      **
**                                                                            **
** Syntax : Std_ReturnType Fee_InvalidateBlock(const uint16 BlockNumber)      **
**                                                                            **
** [/cover]                                                                   **
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
** Description : This function invalidates the given logical block            **
**                                                                            **
*******************************************************************************/
/* [cover parentID={53FDE5DD-D4B5-4fe3-889B-3ED80C47E6B7}]
Fee_InvalidateBlock
[/cover] */
Std_ReturnType Fee_InvalidateBlock(const uint16 BlockNumber)
{

  Fee_StateDataType   *StateDataPtr;
  const Fee_BlockType *BlockPtr;
  uint16               UserBlockIndex;
  MemIf_StatusType    ReturnStatus;

  Std_ReturnType       ReturnValue;
  /* [cover parentID={08905859-5E52-4608-A637-C88C8F2D83C8}]
  Return E_OK
  [/cover] */
  ReturnValue = Fee_lInitSafetyCheck(FEE_SID_INVALIDATEBLOCK);
  /*Check Fee_CfgPtr is null if yes return E_not_ok . This done to avoid trap
  if fee_init is not called */


  /* Check if the Fee_Init API is called */
  /* [cover parentID={EC251CE2-4ABC-4b2c-8B0B-64631235D3FA}]
  Is the configuration pointer NULL?
  [/cover] */
  if(ReturnValue == E_OK)
  {
    StateDataPtr = Fee_CfgPtr->FeeStatePtr;
    /* [cover parentID={032A4BEF-3F1A-43ed-BFE2-E359C539C84F}]
    Get user block index
    [/cover] */
    UserBlockIndex = Fee_lGetUsrBlockIndex(BlockNumber);
    /* [cover parentID={512DF666-A64F-44c0-8088-1BAFF548E94C}]
    DET or safety enabled
    [/cover] */
    /* [cover parentID={E7FBF8C4-C598-4c4f-9A02-E6F2E9073DC3}]*/
    #if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)

    /* [cover parentID={5C5DF49B-F830-4660-A219-6FFAE66F0A89}]
    Is user block index valid?
    [/cover] */
    if( UserBlockIndex == FEE_LOG_BLOCK_NOT_FOUND)
    {
      /* [cover parentID={48F1F75A-0C5E-436a-A2F0-636ECC141E4F}]
      Report FEE_E_INVALID_BLOCK_NO DET
      [/cover] */
      /* Block is not configured */
      Fee_lReportError(FEE_SID_INVALIDATEBLOCK, FEE_E_INVALID_BLOCK_NO, \
          FEE_DET_SAFETY_ERROR);
      /* [cover parentID={0AAA8D6D-89EF-4d2a-82F7-92D6AB2B2E36}]
      Return E_NOT_OK
      [/cover] */
      ReturnValue = E_NOT_OK;
    }

    else
    {
      /* [cover parentID={FDED4E44-602B-415e-8236-1CD52721E19D}]
      Check for Fee status
      [/cover] */
      /* [cover parentID={11F3085D-A819-43f2-8115-66E7876D5797}]
      Is Fee busy in internal operations?
      [/cover] */
    #if (MCAL_AR_VERSION == MCAL_AR_422)
      ReturnStatus = Fee_lGetStatus();
      if(ReturnStatus == MEMIF_BUSY_INTERNAL)
      {
        /* [cover parentID={150C65F1-92E0-4029-8384-79B0B828E3A2}]
               Reject the invalidation request
              [/cover] */
        /* [cover parentID={0AAA8D6D-89EF-4d2a-82F7-92D6AB2B2E36}]
                 Return E_NOT_OK
              [/cover] */
        ReturnValue = E_NOT_OK;
      }
    #endif
    }
    /* [cover parentID={E7FBF8C4-C598-4c4f-9A02-E6F2E9073DC3}]
    If no errors were detected and Fee is not internally busy
    [/cover] */
    if (ReturnValue != E_NOT_OK)
    #endif /*End of FEE_DEV_ERROR_DETECT == STD_ON */
    {
      /* [cover parentID={8A852F26-A7B3-47c2-B4E8-AEA266A0F7FF}]
      Any pending request?
      [/cover] */

      /* [cover parentID={8A852F26-A7B3-47c2-B4E8-AEA266A0F7FF}]
      No pending request and Return Status is Idle?
      [/cover] */
      /* Execute only if there is no pending request */
     ReturnStatus = Fee_lGetStatus();
      /* [cover parentID={1CEFF261-6E46-4bb3-B102-1C6E657B7BF5}]
      AUTOSAR version is 422
      [/cover] */
    #if (MCAL_AR_VERSION == MCAL_AR_422)
      if(( StateDataPtr->FeePendReqStatus == FEE_PEND_PREV_NO_REQ ) &&
          (ReturnStatus == MEMIF_IDLE))
    #else
      if (ReturnStatus != MEMIF_BUSY)
    #endif
      {
        #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
        /* [cover parentID={5C5DF49B-F830-4660-A219-6FFAE66F0A89}]
           Is user block index valid?
        [/cover] */
        if(Fee_CfgPtr->FeeBlockConfigPtr[UserBlockIndex].FeeUser ==
            (uint8)FEE_QUASI_STATIC_USER)
        {
          ReturnValue = E_NOT_OK;
          /* [cover parentID={589953FB-C89B-4c27-9639-A54471518253}]
          DET or safety enabled
          [/cover] */
          #if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
          /* [cover parentID={48F1F75A-0C5E-436a-A2F0-636ECC141E4F}]
          Report FEE_E_INVALID_BLOCK_NO DET
          [/cover] */
          Fee_lReportError(FEE_SID_INVALIDATEBLOCK, FEE_E_INVALID_BLOCK_NO,
              FEE_DET_SAFETY_ERROR);

          #endif

        }
        else
        #endif
        {
          BlockPtr = &(Fee_CfgPtr->FeeBlockConfigPtr[UserBlockIndex]);
          /* register invalidate request */
          StateDataPtr->FeeStatusFlags.FeeBlkInvalidStatus = FEE_SET ;
          Fee_lRegisterWriteRequest(StateDataPtr->FeeReadWriteBuffer, BlockPtr);
        }
      }
      else
      {
        /* [cover parentID={589953FB-C89B-4c27-9639-A54471518253}]
        DET enabled
        [/cover] */
      #if (((FEE_DEV_ERROR_DETECT == STD_ON) || (FEE_SAFETY_ENABLE == STD_ON)) &&\
       (MCAL_AR_VERSION == MCAL_AR_422)) || (FEE_RUNTIME_ERROR_DETECT == STD_ON)
        /* FEE is busy with another request; raise BUSY DET */
        /* [cover parentID={D660C0F2-B899-4359-90D7-18B2DB4975FB}][/cover] */

          /*[cover parentID={092E5527-B561-4969-81B6-DDC3C30AA64B}] [/cover] */
        #if (FEE_RUNTIME_ERROR_DETECT == STD_ON)
        Fee_lReportError(FEE_SID_INVALIDATEBLOCK, FEE_E_BUSY, FEE_RUNTIME_ERROR);
        #else
        Fee_lReportError(FEE_SID_INVALIDATEBLOCK, FEE_E_BUSY, FEE_DET_SAFETY_ERROR);
        #endif
        #endif
        /* [cover parentID={0AAA8D6D-89EF-4d2a-82F7-92D6AB2B2E36}]
        Return E_NOT_OK
        [/cover] */
        ReturnValue = E_NOT_OK;
      }
    }
    /* [cover parentID={11A5BFD3-42A1-41d9-A529-62D808D10C35}]
    Return
    [/cover] */
  }

  return(ReturnValue);

}/*End of Fee_InvalidateBlock */

/*******************************************************************************
** TRACEABILITY:                                                              **
**                                                                            **
** Syntax : Std_ReturnType Fee_EraseImmediateBlock( const uint16 BlockNumber )**
**                                                                            **
** [/cover]                                                                   **
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
/* [cover parentID={B5C7D98C-B3CA-4ccb-8205-08765E4FEC01}][/cover]*/
Std_ReturnType Fee_EraseImmediateBlock(const uint16 BlockNumber)
{
  UNUSED_PARAMETER (BlockNumber);
  /* [cover parentID={32D1C713-6EBC-40ab-9BE1-E3A9FE9A7DF1}]
  Set Return flag as E_NOT_OK
  [/cover] */
  return(E_NOT_OK);
  /* [cover parentID={CBDA1633-EB6D-4568-B28B-4EFB2FF1388D}]
  Return
  [/cover] */
}


#if (FEE_INITCHECK_API == STD_ON)

/******************************************************************************
** TRACEABILITY:                                                             **
**                                                                           **
**                                                                           **
** Syntax : Std_ReturnType Fee_17_InitCheck(const Fee_ConfigType             **
**                                           * const ConfigPtr)              **
**                                                                           **
** [/cover]                                                                  **
**                                                                           **
** Service ID: 0x30                                                          **
**                                                                           **
** Sync/Async:  Synchronous                                                  **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in) : ConfigPtr - Pointer to the selected configuration set   **
**                                                                           **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    :  Std_ReturnType                                         **
**                    E_OK :  Module is initialized properly.                **
**                    E_NOT_OK : Module is not initialized properly due to   **
**                               1) Fee_CfgPtr is NULL                       **
**                               2) Fee_CfgPtr is not matching with given    **
**                                  ConfigPtr.                               **
**                               3) Fee is not yet completely  initialized   **
** Description : Service to check module Initialization status. If module is **
**               not initialized properly  it will return E_NOT_OK           **
******************************************************************************/

/* [cover parentID={49FACB51-3230-4929-A415-2FB4E3231C33}]
Fee_17_InitCheck
[/cover] */
/*[cover parentID={F75EA151-84A9-44e8-A44B-ACE43C4B809C}] [/cover] */
Std_ReturnType Fee_17_InitCheck(const Fee_ConfigType * const ConfigPtr )
{
  Std_ReturnType      RetVal;

  RetVal = E_NOT_OK;

  /* Check if given ConfigPtr pointer is null */
  if(ConfigPtr != NULL_PTR)
  {
    /*Check if module is initialize properly*/
    /*[cover parentID={66E7D345-9ACC-49c1-86C7-9514D7BD883F}] [/cover] */
    if((Fee_CfgPtr != NULL_PTR) && (Fee_CfgPtr == ConfigPtr))
    {
      /* [cover parentID={EC6BC55F-7761-475d-86DD-6E188D93BF71}]
      Calculate the CRC of state structure variable
      [/cover] */
      /* [cover parentID={EDD76789-ED56-4235-A235-F8D5372C5912}]
      Check if  state variable CRC is same as the CRC at initialization?
      [/cover] */
      /*Check if FeeStatePtr and FeeBlockConfigPtr is not null */
      if(Fee_DataStrcutInitCrc == Fee_lCalDataStructCrc())
      {
        RetVal = E_OK;
      }
    }

  }

  return(RetVal);
  /* [cover parentID={74824B0A-B019-46df-82A0-0DE29ABAD076}]
  Return
  [/cover] */
} /*End of Fee_17_InitCheck */

/******************************************************************************
** TRACEABILITY:                                                             **
**                                                                           **
**                                                                           **
** Syntax : LOCAL_INLINE uint32 Fee_lCalDataStructCrc(void)                  **
**                                                                           **
** [/cover]                                                                  **
**                                                                           **
** Service ID:                                                               **
**                                                                           **
** Sync/Async:  Synchronous                                                  **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in) : ConfigPtr - Pointer to the selected configuration set   **
**                                                                           **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    :  uint32                                                 **
**                    CRC of Fee state variable data structure               **
** Description : Service to calculate CRC for fee state variable data        **
**               structure                                                   **
******************************************************************************/
/*[cover parentID={FF96A077-065F-419a-8271-9A7EBABD3682}][/cover]*/
LOCAL_INLINE  uint32 Fee_lCalDataStructCrc(void)
{
  uint32              FeeDataStructSize;
  uint32              Index;
  uint32              Crc32;
  const uint8        *FeeDataStructPtr;

  /*Get the szie of Fee state variable data structure */
  FeeDataStructSize  = sizeof(Fee_StateDataType);
  /*Set the initial CRC value as 0*/
  Crc32 = FEE_RESET;

  FeeDataStructPtr = (uint8*)Fee_CfgPtr->FeeStatePtr;

  /*CRC32 calculation byte-wise*/
  for(Index = FEE_RESET; Index < FeeDataStructSize; Index++)
  {
    Crc32 = CRC32B(Crc32, FeeDataStructPtr[Index]);
  }

  return(Crc32);

}

#endif

/* Memory Map of the FEE Code */
#define FEE_STOP_SEC_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"


#define FEE_START_SEC_JOBENDNOTIF_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"
/*******************************************************************************
** TRACEABILITY: [cover parentID={E921028D-82B0-4ac6-9AAB-2553676A53FC}]      **
**                                                                            **
** Syntax : void Fee_JobEndNotification(void)                                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID: 0x10                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  void                                                    **
**                                                                            **
** Description : Service to report to FEE module the successful end of an     **
** asynchronous operation performed by the underlying flash driver.           **
*******************************************************************************/
void Fee_JobEndNotification(void)
{
  Fee_StateDataType  *StateDataPtr;
  Fls_17_Dmu_Job_Type Job;

  #if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
  /* Check if the Fee_Init API is called */
  /* [cover parentID={956E6175-FAB8-44de-8141-49FB057148F6}][/cover] */
  if(Fee_CfgPtr != NULL_PTR)
  #endif
  {
    StateDataPtr = Fee_CfgPtr->FeeStatePtr;
    /* [cover parentID={B3E5D775-72A1-4bcd-BDAE-4A78BFBC18BC},
    {59E623D3-CB36-4c9c-A9A9-D28CA4495A23}]
    Get the FLS job that raised the notification
    [/cover] */
    Job = Fls_17_Dmu_GetNotifCaller();
    /* [cover parentID={041587D2-B988-4bc3-9B98-0B11B23D483C}]
    Is it internal job?
    [/cover] */
    if(Job == StateDataPtr->FeeIntrJob)
    {
      /* If job is internal job */
      /*
      Reset the pending request status and set Fee job result to MEMIF_JOB_OK
      FeePendReqInfo.GetPrevCopy = FEE_ZERO
      */
      /* [cover parentID={041587D2-B988-4bc3-9B98-0B11B23D483C}]*/
      StateDataPtr->FeeIntrJobStatus = FEE_JOB_DONE;
      StateDataPtr->FeeIntrJobResult = FEE_JOB_PASS;
      StateDataPtr->FeeIntrJob = FEE_NO_JOB;
    }
    /* [cover parentID={27BCAA74-DD8C-4b18-BEAE-993FF9E1F6B4}]
    Is it NVM Job?
    [/cover] */
    else if( Fee_lGetUserJob(StateDataPtr->FeePendReqStatus) == Job)
    {
      /* if job is user job */
      /* [cover parentID={7CD59A02-564E-423a-B7A5-6A9E0317D4CA}]*/
      StateDataPtr->FeeUserJobStatus = FEE_JOB_IDLE;
      StateDataPtr->FeeUserJobResult = FEE_JOB_PASS;
      /* [cover parentID={A96EAB68-61B5-4230-B9DC-E56735E5BDBC}]
      Is it read job?
      [/cover] */

      if(Job == FEE_READ_JOB)
      {
        Fee_lHandleReadJobEndNotification();
      }
      /* FLS_WRITE_JOB: Handling last page write is done as part of
       Write State Machine itself */
    }/* End of User Job Handling */

    /* [cover parentID={27BCAA74-DD8C-4b18-BEAE-993FF9E1F6B4}]*/
    #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
    /* [cover parentID={1B1980BA-F8C8-4bae-8DA7-3E0F81B12F2E}]
    [/cover] */
    else if(StateDataPtr->FeeQsIntrJob != FEE_NO_JOB)
    {
        StateDataPtr->FeeQsIntrJobStatus = FEE_JOB_IDLE;
        StateDataPtr->FeeQsIntrJobResult = MEMIF_JOB_OK;
    }
    /* [cover parentID={D9A935CB-8E11-4693-8466-8FC0D198370A}]
    Is it QS job?
    [/cover] */
    else if(StateDataPtr->FeeQsJob != FEE_NO_JOB)
    {
      /* reset job status */
      StateDataPtr->FeeQsJobStatus = FEE_JOB_IDLE;
      if(StateDataPtr->FeeQsJob == FEE_READ_JOB)
      {
        /* do handling only for read job */
        Fee_lHandleQsJobSuccess();
      }
    }
    #endif
    else
    {
      /* do nothing */
    }
  }
  /* [cover parentID={744096FC-A4E6-4e1d-A798-89BEE1EA24D5}][/cover] */
  #if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
  else
  {
    /* [cover parentID={7A89D95B-7673-431d-AE48-F6A057D59C2B}][/cover] */
    Fee_lReportError(FEE_SID_JOBENDNOTIF, FEE_E_UNINIT, FEE_DET_SAFETY_ERROR);
  }
  #endif
  /* [cover parentID={260D257B-9490-4d7f-B1B7-7FA08BFFD26D}]
  Return
  [/cover] */

}/*End of Fee_JobEndNotification */
#define FEE_STOP_SEC_JOBENDNOTIF_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safe gaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"
#define FEE_START_SEC_JOBERRNOTIF_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safe gaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"

/*******************************************************************************
** TRACEABILITY: [cover parentID={AA095DA4-6739-4654-BDB4-BEEA3B44ECA7}]      **
**                                                                            **
** Syntax : void Fee_JobErrorNotification(void)                               **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID: 0x11                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : Service to report to FEE module the failure of an            **
** asynchronous operation performed by the underlying flash driver.           **
*******************************************************************************/
/* [cover parentID={9870766D-AAE4-46f4-8DC3-CF8DB4AD87EB}]
Fee_JobErrorNotification
[/cover] */
void Fee_JobErrorNotification(void)
{
  Fee_StateDataType  *StateDataPtr;
  Fls_17_Dmu_Job_Type Job;

  #if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
  /* Check if the Fee_Init API is called */
  /* [cover parentID={D6D4C142-EDD9-4cc6-86A2-250717F5F423}][/cover] */
  if(Fee_CfgPtr != NULL_PTR)
  #endif
  {
    /* [cover parentID={A5487785-AF69-4e3b-9F91-54359044A202}]
    Get the FLS job that raised the notification
    [/cover] */
    /* [cover parentID={9870766D-AAE4-46f4-8DC3-CF8DB4AD87EB}][/cover] */
    StateDataPtr = Fee_CfgPtr->FeeStatePtr;
    Job = Fls_17_Dmu_GetNotifCaller();
    /* [cover parentID={E5E61E37-7F38-4769-B2EE-D07A39F483C1}][/cover] */
    if(Job == FEE_CANCEL_JOB)
    {
      Fee_lHandleCancelNotification();
    }
    /* [cover parentID={80D7E034-68FA-494e-8549-406F408E4BE2}][/cover] */
    else if(Job == StateDataPtr->FeeIntrJob)
    {
      /* if job is internal job */
      StateDataPtr->FeeIntrJobStatus = FEE_JOB_DONE;
      StateDataPtr->FeeIntrJobResult = FEE_JOB_FAIL;
      StateDataPtr->FeeIntrJob = FEE_NO_JOB;
    }
    /* [cover parentID={E44D68D3-BFA4-4688-B3BF-17F0AB0AF21B}][/cover] */
    else if( Job == Fee_lGetUserJob(StateDataPtr->FeePendReqStatus))
    {
      /* Internal Write activity has failed */
      /* [cover parentID={787D848A-A3FE-489a-AB17-DB4019402DE4}][/cover] */
      if( StateDataPtr->FeePendReqStatus == FEE_PEND_INTR_COMPARE)
      {
        Fee_lHandleWriteFail();
      }
      /* User Write / Read activity has failed */
      else
      {
        Fee_lHandleUsrJobErrorNotification(Job);
      }
    } /* End of User Job */
    #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
    /* [cover parentID={BFEA3281-9744-40a2-8E56-348FB464EAAC}][/cover] */
    else if(StateDataPtr->FeeQsIntrJob != FEE_NO_JOB)
    {
        StateDataPtr->FeeQsIntrJobStatus = FEE_JOB_IDLE;
        StateDataPtr->FeeQsIntrJobResult = MEMIF_JOB_FAILED;
    }
    /* [cover parentID={BAE438D8-BC86-4ab8-8C3C-0234C0D28908}][/cover] */
    else if(StateDataPtr->FeeQsJob != FEE_NO_JOB)
    {
      /* Call the Fee_lHandleQsJobFailure with  (FEE_NOT_CANCEL) to notify
      user about failed of job*/
      Fee_lHandleQsJobFailure((FEE_NOT_CANCEL));
    }
    #endif
    else
    {
      /* do nothing, in case if FLS is used as stand alone and this
       notification function being used */
    }
  }
  /* [cover parentID={1DD0346F-7BB3-45d9-AC1D-9DB28C979CA8}]
  DET or safety is enabled
  [/cover] */
  #if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
  else
  {
    /* [cover parentID={872B3E91-55B6-4eac-963B-F400E12DF732}]
    Report DET error as FEE_E_UNINIT
    [/cover] */
    Fee_lReportError(FEE_SID_JOBERRORNOTIF, FEE_E_UNINIT, FEE_DET_SAFETY_ERROR);

  }
  #endif
}/*End of Fee_JobErrorNotification */
#define FEE_STOP_SEC_JOBERRNOTIF_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"
#define FEE_START_SEC_ILLEGALNOTIF_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"

/*******************************************************************************
** Syntax : void Fee_17_IllegalStateNotification(void)                        **
**                                                                            **
** Traceability   : [cover parentID={32EEA8A2-7EB6-459a-9B3B-761D4C673810}]   **
**                                                                            **
** Service ID: 0x24                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  void                                                    **
**                                                                            **
** Description : This routine shall be called by the underlying flash         **
**                  driver when it reaches the illegal state                  **
*******************************************************************************/
/* [cover parentID={5B7ED9EA-E19F-4c18-813F-6EAACC6E85F6}]
Fee_17_IllegalStateNotification
[/cover] */
void Fee_17_IllegalStateNotification(void)
{
  /* [cover parentID={5B7ED9EA-E19F-4c18-813F-6EAACC6E85F6}]*/
  #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
  const Fee_StateDataType   *StateDataPtr;
  #endif

  /* [cover parentID={58B938B8-38DF-4a9d-ADBD-D089D462AAE6}]
  FEE_SAFETY_ENABLE is enabled
  [/cover] */
  #if (FEE_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={2915F7D7-68F1-432a-BBE1-270F959A6E65}][/cover] */
  if(Fee_CfgPtr != NULL_PTR)
  #endif
  {
    #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
    StateDataPtr = Fee_CfgPtr->FeeStatePtr;

    /* [cover parentID={67F239D5-E873-43bf-A00F-48D66AEEAFD8}][/cover] */
    if((StateDataPtr->FeeQsJob == FEE_NO_JOB) && (StateDataPtr->FeeQsIntrJob == FEE_NO_JOB))
    {
      if(Fee_CfgPtr->FeeNvmIllegalStateNotification != NULL_PTR)
      {
        Fee_CfgPtr->FeeNvmIllegalStateNotification();
      }
    }
    else
    {
      /* QS illegal notification will be called */
    /* [cover parentID={FDD52D62-AB1E-44ac-B0D8-9B410CBC3F3F}][/cover] */
      if(Fee_CfgPtr->FeeQsIllegalStateNotification != NULL_PTR)
      {
    /* [cover parentID={00EA22D3-5D16-4c9e-B87B-BC1C3CB354A9}][/cover] */
        Fee_CfgPtr->FeeQsIllegalStateNotification();
      }
    }

    #else
    /* [cover parentID={75A19B6B-4521-4049-97F8-C4B578266DAA}][/cover] */
    if(Fee_CfgPtr->FeeNvmIllegalStateNotification != NULL_PTR)
    {

      /* Call the Notification function */
    /* [cover parentID={972AD19B-6F21-4f06-A209-4C234557C084}][/cover] */
      Fee_CfgPtr->FeeNvmIllegalStateNotification();
    }
    #endif
  }
  #if (FEE_SAFETY_ENABLE == STD_ON)
  else
  {
    /* [cover parentID={34FD9AE4-8FE3-433d-8EA0-BBBC79DB10B5}]
    Report error FEE_E_UNINIT
    [/cover] */
      Fee_lReportError(FEE_SID_ILLEGALSTATENOTIFICATION, FEE_SE_UNINIT,
                        FEE_SAFETY_ERROR);
  }
  #endif
}/*End of Fee_17_IllegalStateNotification */
#define FEE_STOP_SEC_ILLEGALNOTIF_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safe gaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"
/* Memory Map of the FEE Code */
#define FEE_START_SEC_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safe gaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"



#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

#if (FEE_GET_CYCLE_COUNT_API == STD_ON)
/*******************************************************************************
** Syntax : Std_ReturnType Fee_17_GetCycleCount(const uint16 BlockNumber,     **
**                                              uint32 * const CountPtr)      **
**                                                                            **
** Traceability   : [cover parentID={CA460132-35A7-4725-933B-DBF822A5B00F}]   **
**                                                                            **
** Service ID:    0x20                                                        **
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
**                    E_OK: Block cycle count read successfully               **
**                    E_NOT_OK: Block cycle count can not be read due to      **
**                              1) Cache is not yet updated or                **
**                              2) Flash driver is busy with other request or **
**                              3) Garbage collection is ongoing              **
**                                                                            **
** Description : When called with BlockNumber = 0, this routine delivers the  **
** FEE sector erase cycle count. When called with a configured BlockNumber,   **
** the write cycle count of the given block is returned.                      **
**                                                                            **
*******************************************************************************/
Std_ReturnType Fee_17_GetCycleCount(const uint16 BlockNumber,
                                    uint32 * const CountPtr)
{
  uint32               RawCnt;
  const Fee_StateDataType   *StateDataPtr;
  uint16               BlockIndex;
  Std_ReturnType       ReturnValue;
  MemIf_StatusType     Status;

  /* [cover parentID={8F5D3017-260D-43f6-9DAD-699DE19349E9}]
  Set return value as E_NOT_OK
  [/cover] */
  ReturnValue = E_NOT_OK;
  #if (FEE_SAFETY_ENABLE == STD_ON) || (MCAL_AR_VERSION == MCAL_AR_440)
  /*Check for configuration pointer(Fee_CfgPtr)for null as part safety check */
  /* [cover parentID={273AF53D-B191-4301-953A-113198DF1108}]/cover] */
  if(Fee_lGetCycleSafetyCheck(CountPtr) == E_OK)
  #endif
  {
      /* [cover parentID={066C5C76-67C7-4ead-A465-1629BD66AD41},
      {EA4A7BB3-1CF8-4396-B891-C03D8ED2CDDB}]
      [/cover] */
      /* if the cache is not updated, or if GC is on going, return.
       else, proceed with Get block cycle count */
      /* [cover parentID={00DE57D6-FE1C-47aa-94F1-5A98A2F933A9}]
      Check for cache and GC status
      [/cover] */
      /* [cover parentID={3E4D0D11-A15E-4fc5-9EF9-2F3D39340B9F}]
      Check for valid block index
      [/cover] */
      /* [cover parentID={1BD5B167-F038-4142-BA3D-9C4C1ACE7849}]
      Is block index valid?
      [/cover] */
      /* [cover parentID={E0D91688-3A24-4c0e-838F-93CC2A6C3034}]
      Read block cycle count
      [/cover] */
      /* [cover parentID={C471858B-5677-4eec-8C8D-B609771A9937}]
      Check if block cycle count was read
      [/cover] */

      StateDataPtr = Fee_CfgPtr->FeeStatePtr;
      Status = Fee_lGetStatus();
      /* [cover parentID={00DE57D6-FE1C-47aa-94F1-5A98A2F933A9}]
      Check for cache and GC status
      [/cover] */
      /* [cover parentID={066C5C76-67C7-4ead-A465-1629BD66AD41}]
      Is the module state idle?
      [/cover] */
      if (Status == MEMIF_IDLE)
      {

        /* [cover parentID={4E4CD66B-4FF7-474d-827A-6DB051FA9740}][/cover] */
        if((StateDataPtr->FeeCacheState == FEE_CACHE_UPDATE_COMPLETE) &&
            (StateDataPtr->FeeGcState == FEE_GC_IDLE))
        {
          /* [cover parentID={222C72BC-61FF-4369-A797-DFD73214ADDE}]
          Is block number zero?
          [/cover] */
          if (BlockNumber == FEE_STATE_PAGE_NUMBER)
          {
            /* Erase Cycle count is derived from the latest state count
             State Count is incremented at every state page write.
            At the start / After preparation of DFLASH, the state count is 3.
            Since then the state count is incremented twice during GC
            (once for VALID SP programming and again for ERASED SP programming).
            Hence the Erase Cycle Count shall be (StateCount - 3)/2 */
            /* [cover parentID={75DEB242-F51C-46cd-9FA5-D93BF5CA2A8E}]
            Calculate erase cycle count
            [/cover] */
            RawCnt = ((StateDataPtr->FeeStateCount - FEE_THREE) >> FEE_ONE);
            *CountPtr = RawCnt;
            /* [cover parentID={EF577DD8-E8A2-4b24-B74C-1F3BD936E082}]
            Return E_OK
            [/cover] */
            ReturnValue = E_OK;
          }
          /* [cover parentID={222C72BC-61FF-4369-A797-DFD73214ADDE}]
          Is block number zero?
          [/cover] */
          /* [cover parentID={75DEB242-F51C-46cd-9FA5-D93BF5CA2A8E}]
          [/cover] */
          /* [cover parentID={7397E5C1-5866-4ebb-B366-7652FB3B9A87}]
          [/cover] */
          else
          {
            /* [cover parentID={7397E5C1-5866-4ebb-B366-7652FB3B9A87}]
            Get index of the block info stored in cache
            [/cover] */
            /* Get index of the block info stored in cache */
            BlockIndex = Fee_lGetUsrBlockIndex(BlockNumber);
            /* [cover parentID={3E4D0D11-A15E-4fc5-9EF9-2F3D39340B9F}]
            Check for valid block index
            [/cover] */
            /* [cover parentID={1BD5B167-F038-4142-BA3D-9C4C1ACE7849}]
            Is block index valid?
            [/cover] */

            if(BlockIndex != FEE_LOG_BLOCK_NOT_FOUND)
            {
              #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
              if(Fee_CfgPtr->FeeBlockConfigPtr[BlockIndex].FeeUser ==
                  (uint8)FEE_QUASI_STATIC_USER)
              {
                ReturnValue = E_NOT_OK;

                #if (FEE_SAFETY_ENABLE == STD_ON)
                /* [cover parentID={DF9E2968-4B59-4d87-A408-B2B81AF8DDB3}]
                Report safety error as FEE_E_INVALID_BLOCK_NO
                [/cover] */
                Fee_lReportError(FEE_SID_GETCYCLECOUNT,
                                  FEE_SE_INVALID_BLOCK_NO, FEE_SAFETY_ERROR);
                #endif
              }
              else
              #endif
              {
                /* [cover parentID={E0D91688-3A24-4c0e-838F-93CC2A6C3034}]
                Read block cycle count
                [/cover] */
                /* Read block cycle count */
                RawCnt = Fee_lGetBlkCycleCount(BlockIndex);
                /* [cover parentID={C471858B-5677-4eec-8C8D-B609771A9937}]
                Check if block cycle count was read
                [/cover] */
                /* [cover parentID={F7CB7631-7C7D-4c7a-A556-B66C41A663C6}]
                Is read performed and was successful ?
                [/cover] */
                /* Check if the read was performed */
                if(RawCnt != FEE_32_BIT_ALL_ONES)
                {
                  /* [cover parentID={2F9059CE-8C6C-4c64-99FE-5B9567CC56D6}]
                  Return the block cycle counter via countptr
                  Return E_OK
                  [/cover] */
                  *CountPtr = RawCnt;
                  ReturnValue = E_OK;
                  /* [cover parentID={EF577DD8-E8A2-4b24-B74C-1F3BD936E082}]
                  Return E_OK
                  [/cover] */

                }
              }
            }
            /* [cover parentID={E494297C-E13F-43fc-BDD4-FA7C6BAC86C2}]
            Safety error is enabled
            [/cover] */

            #if (FEE_SAFETY_ENABLE == STD_ON)
            else
            {
              /* [cover parentID={DF9E2968-4B59-4d87-A408-B2B81AF8DDB3}]
              Report safety error as FEE_E_INVALID_BLOCK_NO
              [/cover] */
              Fee_lReportError(FEE_SID_GETCYCLECOUNT,
                               FEE_SE_INVALID_BLOCK_NO, FEE_SAFETY_ERROR);
            }
            #endif
          } /* end of if ( BlockNumber == FEE_ZERO ) */
        }/* end of if FEE_CACHE_UPDATE_COMPLETE*/
      } /* end of if the module was idle*/

      #if ((FEE_SAFETY_ENABLE == STD_ON) && (MCAL_AR_VERSION == MCAL_AR_422)) \
      || (FEE_RUNTIME_ERROR_DETECT == STD_ON)
      else
      {
        /* [cover parentID={8E5B7794-EF3C-4363-B750-B49A8C8669AE}]
        Is the module is busy
        [/cover] */
        if(Status == MEMIF_BUSY )
        {
          /* [cover parentID={435AF9EA-B66D-4fef-A54F-A1F53DD0B9F0}]
          Report error to FEE_SID_GETCYCLECOUNT and FEE_E_BUSY
          [/cover] */
          #if(FEE_SAFETY_ENABLE == STD_ON) && (MCAL_AR_VERSION == MCAL_AR_422)
          Fee_lReportError(FEE_SID_GETCYCLECOUNT,
                              FEE_SE_BUSY, FEE_SAFETY_ERROR);
          #elif (FEE_RUNTIME_ERROR_DETECT == STD_ON)
          Fee_lReportError(FEE_SID_GETCYCLECOUNT,
                              FEE_E_BUSY, FEE_RUNTIME_ERROR);
          #endif
        }
      }
      #endif
  }
  /* [cover parentID={F0094B24-7E3F-416a-81DB-690C29CF0DF5}]
  Return
  [/cover] */
  return(ReturnValue);

}/*End of Fee_GetCycleCount */
#endif
/* End of FEE_GET_CYCLE_COUNT_API == STD_ON */

/******************************************************************************
** Syntax : void Fee_17_EnableGcStart( void )                                **
**                                                                           **
** Traceability   : [cover parentID={2CE2C6D5-740D-450d-9A6C-CD3FFCEE43B1}]  **
**                                                                           **
** Service ID:     0x21                                                      **
**                                                                           **
** Sync/Async:  Synchronous                                                  **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in) :  None                                                   **
**                                                                           **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    :  void                                                   **
**                                                                           **
** Description : This service allows enabling the trigger of GC, if GC was   **
** disabled earlier by calling the API Fee_17_DisableGcStart. After this API **
** is called,if the sector is filled up to the threshold level and additional**
** write / invalidate request is issued, then GC will be initiated.          **
**                                                                           **
******************************************************************************/
/* [cover parentID={0459E2CC-247D-4693-B08D-A503D87E4DCA}]
Fee_17_EnableGcStart
[/cover] */
void Fee_17_EnableGcStart(void)
{

  Fee_StateDataType  *StateDataPtr;
  /* [cover parentID={ADE93B08-FF37-464a-BFB7-1260BE7E629A}]
  Safety error is enabled
  [/cover] */
  #if (FEE_SAFETY_ENABLE == STD_ON)
  /*Check for configuration pointer(Fee_CfgPtr)for null as part safety check */
  /* [cover parentID={3595E30F-067D-458c-B731-E407B13DA9A3}]
  Is configuration pointer NULL?
  [/cover] */
  if(Fee_CfgPtr != NULL_PTR)
  #endif
  {
    #if(MCAL_AR_VERSION == MCAL_AR_440)
    /* [cover parentID={FBFEE4D9-D9F0-4bf5-9682-3EEA13EB281D}]
    Is driver initialization is complete
    [/cover] */
    if(Fee_lGetStatus() != MEMIF_UNINIT)
    #endif
    {
    StateDataPtr = Fee_CfgPtr->FeeStatePtr;
    /* [cover parentID={B9BEB9C6-ACD9-474a-A0F1-781C9EC20873}]
      Enable the GC start functionality
    [/cover] */
    StateDataPtr->FeeDisableGCStart = (boolean)FALSE;
  }
    #if(FEE_SAFETY_ENABLE == STD_ON) && (MCAL_AR_VERSION == MCAL_AR_440)
    else
    {
      Fee_lReportError(FEE_SID_ENABLEGCSTART,
                            FEE_SE_UNINIT, FEE_SAFETY_ERROR);
    }
    #endif
  }
  #if(FEE_SAFETY_ENABLE == STD_ON)
  else
  {
    /* [cover parentID={0C13789A-C15D-4b72-B987-040CA7CCB813}]
    Report error as FEE_E_UNINIT
    [/cover] */
    Fee_lReportError(FEE_SID_ENABLEGCSTART,
                          FEE_SE_UNINIT, FEE_SAFETY_ERROR);
  }
  #endif
}

/*******************************************************************************
** Syntax : void Fee_17_DisableGcStart( void )                                **
**                                                                            **
** Traceability   : [cover parentID={36D8B89D-6D66-4d21-B473-9731A9FDB6A1}]   **
**                                                                            **
** Service ID:      0x22                                                      **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  void                                                    **
**                                                                            **
** Description : This API prevents the GC from being started in case the      **
** threshold is crossed in the active FEE sector. This API does not stop an   **
** ongoing GC but only prevents the GC from being triggered by the            **
** Write/Invalidate request issued by the user.                               **
** Note: This API will disable the GC from starting only if,                  **
** 1. GC is not ongoing                                                       **
** 2. Initialization activities are complete (i.e. the state pages are read   **
** and the GC state is determined)                                            **
**                                                                            **
*******************************************************************************/
/* [cover parentID={AB6DB1F5-CD73-4523-81DE-7D95DF009FCB}]
Fee_17_DisableGcStart
[/cover] */
void Fee_17_DisableGcStart(void)
{

  Fee_StateDataType  *StateDataPtr;
  /* [cover parentID={5A355946-411E-44bc-A97B-E7B5FED152BE}]
  Safety error is enabled
  [/cover] */
  #if (FEE_SAFETY_ENABLE == STD_ON)
  /*Check for configuration pointer(Fee_CfgPtr)for null as part safety check */
  /* [cover parentID={E32EEFF5-B171-4895-99EB-EF860F84D8F5}][/cover] */
  if(Fee_CfgPtr != NULL_PTR)
  #endif
  {
    #if(MCAL_AR_VERSION == MCAL_AR_440)
    /* [cover parentID={01491577-C682-406c-8A7A-770E8BDD2A38}]
    Is driver initialization is complete
    [/cover] */
    if(Fee_lGetStatus() != MEMIF_UNINIT)
    #endif
    {
      StateDataPtr = Fee_CfgPtr->FeeStatePtr;
      /* Check if InitGC is COMPLETE */
      /* [cover parentID={67C5A6D4-7610-4679-A8BC-49105171E8EC}]
      Check for GC init state
      [/cover] */
      if(StateDataPtr->FeeInitGCState == FEE_INITGC_COMPLETE)
      {
        /* [cover parentID={78FC3E5F-7999-43b5-AFBC-D14FA2225FCE}]
        Check if GC is idle
        [/cover] */
        /* Check if the GC is not started (= IDLE) */
        /* [cover parentID={9F8B0BCF-713E-4691-B403-F7BA77E711C6}]
        Check for GC state
        [/cover] */

        if(StateDataPtr->FeeGcState == FEE_GC_IDLE)
        {
          /* [cover parentID={4C4E1F37-5052-4840-8EDF-0F19DB915E39}]
          Disable GC start functionality
          [/cover] */
          /* Disable the GC start functionality */
          StateDataPtr->FeeDisableGCStart = (boolean)TRUE;
        }
      }
    }
    #if(FEE_SAFETY_ENABLE == STD_ON) && (MCAL_AR_VERSION == MCAL_AR_440)
    else
    {
      Fee_lReportError(FEE_SID_DISABLEGCSTART,
                            FEE_SE_UNINIT, FEE_SAFETY_ERROR);
    }
  #endif
  }

  #if (FEE_SAFETY_ENABLE == STD_ON)
  else
  {
    /* [cover parentID={342CE27A-26A2-442f-B305-17905172F157}]
    Report safety error as FEE_E_UNINIT
    [/cover] */
    Fee_lReportError(FEE_SID_DISABLEGCSTART,
                          FEE_SE_UNINIT, FEE_SAFETY_ERROR);
  }
  #endif
  /* [cover parentID={9C48E59F-EAF7-4827-A2CA-565730D5B4FC}]
  Return
  [/cover] */
}/*End of Fee_17_DisableGcStart*/
#endif

/*******************************************************************************
** TRACEABILITY: [cover parentID={6DA9A0A4-6B27-454f-B64A-FC27DD7DFCF2}]      **
**                                                                            **
** Syntax : void Fee_MainFunction(void)                                       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID: 0x12                                                           **
**                                                                            **
** Sync/Async:  NA                                                            **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  void                                                    **
**                                                                            **
** Description : The scheduled function helps to drive asynchronous jobs-     **
** read, write, erase and internal management jobs like garbage collection.   **
**                                                                            **
*******************************************************************************/
/* [cover parentID={9DE37884-A9F6-4342-AF5C-CDD9507959A7},
{AAB72093-60CA-413e-9DFC-4037C25368F8}]
Fee_MainFunction
[/cover] */
void Fee_MainFunction(void)
{
  #if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
  const Fee_StateDataType  *StateDataPtr;
  #else
  Fee_StateDataType  *StateDataPtr;
  #endif
  /* [cover parentID={09B3C16C-44DF-49c3-A26D-C308340D5BB0}]
  Is ConfigPtr non-null?
  [/cover] */
  if(Fee_CfgPtr != NULL_PTR)
  {
    StateDataPtr = Fee_CfgPtr->FeeStatePtr;

    /* 1. Determine & switch Main Job,if required, based on input conditions */
    Fee_lDecideMainJob();

    /* 2. Execute the Main Job */
    switch(StateDataPtr->FeeMainJob)
    {
      #if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
      /* [cover parentID={783CCC3A-A8D3-4150-B35F-13DC245D0E28}][/cover] */
      case FEE_MAIN_INITGC:
      {
        /* [cover parentID={63DD725B-370A-412b-8BF9-E59FED6EC450}][/cover] */
        if(StateDataPtr->FeeIntrJobStatus != FEE_JOB_REQSTD)
        {
          /* [cover parentID={DAB4A9E6-228A-4d41-B7EE-54263AF02A14}][/cover] */
          Fee_lInitGC();
        }
        break;
      }
      #endif
      #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
      /* [cover parentID={A16681CC-EBBA-46eb-9DEB-ED9CFBBB204F}][/cover] */
      case FEE_MAIN_INITQS:
      {
        /* [cover parentID={B3DA472D-6F15-44ab-8BFF-D9D833E16666}][/cover] */
        if(StateDataPtr->FeeQsIntrJobStatus != FEE_JOB_REQSTD)
        {
          /* [cover parentID={CD1AEA92-B5D2-465e-A963-E750915E85C5}][/cover] */
          if(StateDataPtr->FeeQsBlockVirginCount == FEE_NUM_QUASI_BLOCKS)
          {
            /* [cover parentID={0E844C87-D069-414d-B161-4D7E43E9169B}][/cover] */
            Fee_lHandleQsVirginBlocks();
          }
          else
          {
            /* [cover parentID={9F371310-354B-4386-9505-0D952E07DC33}][/cover] */
            Fee_lQsIDSM();
          }

        }
        break;
      }
      #endif
      /* [cover parentID={DFC9496E-9EAE-439d-B40D-C8A2C81FE5E3}][/cover] */
      case FEE_MAIN_CACHEUPDATE:
      {
        #if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
        /* [cover parentID={1F7FE376-709B-47b9-9CD5-AED9DE3AB0D1}][/cover] */
        Fee_lUpdateCache();
        #else
        StateDataPtr->FeeCacheState = FEE_CACHE_IDLE_QS;
        #endif
        break;
      }

      #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
      /* [cover parentID={2D99AAB6-5551-4991-99BB-60D0C9215CCB}][/cover] */
      case FEE_MAIN_QS:
      {
        /* [cover parentID={03AB2197-4124-40f8-BBE4-70557AAB876F}][/cover] */
        if(StateDataPtr->FeeQsJobStatus != FEE_JOB_REQSTD)
        {
          /* [cover parentID={777B96FB-A391-4af0-8535-2DCB343B2FBA}][/cover] */
          Fee_lMainQs();
        }
        break;
      }
      #endif
      #if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
      /* [cover parentID={6A49C689-C017-4504-8CFF-7BBA9991DD2C}][/cover] */
      case FEE_MAIN_WRITE:
      {
        /* [cover parentID={E73F243C-8BAD-43b8-B439-93F35CCE4F26}][/cover] */
        if(StateDataPtr->FeeUserJobStatus != FEE_JOB_REQSTD)
        {
          /* [cover parentID={D06EBBC4-EA5C-49f8-A832-466D27A5C0C8}][/cover] */
          Fee_lLocalWrite();
        }
        break;
      }
      /* [cover parentID={8E1DDE83-D8F4-41d8-BE8C-30EA31BB3F61}][/cover] */
      case FEE_MAIN_READ:
      {
        /* [cover parentID={C95FAA41-EDB2-46cb-9CC9-19DBB8874F2D}][/cover] */
        if(StateDataPtr->FeeUserJobStatus != FEE_JOB_REQSTD)
        {
          /* [cover parentID={BF603D11-73F7-45d2-A05D-E780561CCBC9}]
          Call local read
          [/cover] */
          Fee_lLocalRead();
        }
        break;
      }
      /* [cover parentID={1FD5FF62-48F9-494f-8E96-84B6839BC58B}][/cover] */
      case FEE_MAIN_GC:
      {
        /* [cover parentID={68D4CE9A-4D3A-4574-9CA3-9F719D737DDA}][/cover] */
        Fee_lMainGCHdlr();
        break;
      }
      #endif
      /*case FEE_MAIN_NONE, FEE_MAIN_UNINIT belong here */
      default:
      {
        break;
      }
    }
  }
  /*
  Return
  */

}/*  End of Fee_MainFunction */


#if (FEE_GET_PREV_DATA_API == STD_ON)
/*******************************************************************************
** Syntax : Std_ReturnType Fee_17_GetPrevData(const uint16 BlockNumber,       **
**                                            const uint16 BlockOffset,       **
**                                            uint8 *const DataBufferPtr,     **
**                                            const uint16 Length)            **
**                                                                            **
** Traceability   : [cover parentID={FD1EBB5B-3408-414d-8872-281BC6442041}]   **
**                                                                            **
** Service ID: 0x23                                                           **
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
**                    E_OK : Request accepted                                 **
**                    E_NOT_OK : Request is not accepted accepted due to      **
**                    1) FEE module is busy in servicing other request. or    **
**                    2) Requested block number is not a NVM data block       **
**Description : The user can call this API to read one occurrence old data of **
**the given block. This API accepts the request and updates the FEE internal  **
**variables. However the actual reading of the data is done by the            **
**Fee_MainFunction after the cache is built.                                  **
**                                                                            **
*******************************************************************************/
/* [cover parentID={099DBE0A-0F91-49a8-9D6D-081A0C24CEB3}]
Fee_17_GetPrevData
[/cover] */
Std_ReturnType Fee_17_GetPrevData(const uint16 BlockNumber,
                                  const uint16 BlockOffset,
                                  uint8 *const DataBufferPtr,
                                  const uint16 Length)
{
  /* [cover parentID={207E879F-CE45-4b94-8DB8-74F9A3AAF126}]
  Return E_NOT_OK
  [/cover] */
  Std_ReturnType        RetVal = E_NOT_OK;

  #if((FEE_SAFETY_ENABLE == STD_ON) || \
      (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY))
  uint16               BlkIdx;

  #endif

  #if(FEE_SAFETY_ENABLE == STD_ON)
  uint32               BlkSize = FEE_RESET;
  /*Check for configuration pointer(Fee_CfgPtr)for null as part safety check */
  /* [cover parentID={DD2F6074-E2F4-47fa-AB2B-93328CF9F5A4}][/cover]*/
  if((Fee_CfgPtr != NULL_PTR) && (DataBufferPtr != NULL_PTR))
  #endif
  {
    #if(MCAL_AR_VERSION == MCAL_AR_440)
    /* [cover parentID={5861DA08-37AA-498b-8015-792F39DCC7FF}]
    Is driver initialization is complete
    [/cover] */
    if(Fee_lGetStatus() != MEMIF_UNINIT)
    #endif
    {
    /* [cover parentID={14D8388C-3115-4aa5-9C66-A64D6B220D96}]
    [/cover] */
    #if((FEE_SAFETY_ENABLE == STD_ON) || \
        (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY))
    /*Check if block is configured and given block number is not qs block*/
    BlkIdx = Fee_lGetUsrBlockIndex(BlockNumber);
    #endif
    #if (FEE_SAFETY_ENABLE == STD_ON)
    if(BlkIdx != FEE_LOG_BLOCK_NOT_FOUND)
    {
      BlkSize = Fee_CfgPtr->FeeBlockConfigPtr[BlkIdx].Size;
    }
    if(BlkIdx == FEE_LOG_BLOCK_NOT_FOUND)
    {
      RetVal = E_NOT_OK;
      /* [cover parentID={3F17237B-D727-4aa6-9BC8-B7777862BBA9}]
      Report error as FEE_SE_INVALID_BLOCK_NO
      [/cover] */
      Fee_lReportError(FEE_SID_GETPREVDATA,
                          FEE_SE_INVALID_BLOCK_NO, FEE_SAFETY_ERROR);
    }
    else if(BlockOffset >= BlkSize)
    {
      RetVal = E_NOT_OK;
      Fee_lReportError(FEE_SID_GETPREVDATA,
                          FEE_SE_INVALID_BLOCK_OFS, FEE_SAFETY_ERROR);
    }
    /* Check if the Length (from the given offset) is valid */
    else if ( ((uint32)BlockOffset + Length) > BlkSize )
    {
      RetVal = E_NOT_OK;
      Fee_lReportError(FEE_SID_GETPREVDATA,
                          FEE_SE_INVALID_BLOCK_LEN, FEE_SAFETY_ERROR);
    }
    else
    #endif
    {
      #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)

      /* [cover parentID={702FD5FB-86DD-43e8-8EEE-E87D3BBF9219}] [/cover] */
      if(Fee_CfgPtr->FeeBlockConfigPtr[BlkIdx].FeeUser ==
          (uint8)FEE_NVM_USER)
      #endif
      {
        /* [cover parentID={CCDD13FA-6F39-4e3f-B48B-9AF7DE1FC299}]

        [/cover] */
        RetVal = Fee_lRegisterNvmRead(BlockNumber, BlockOffset,
                                      DataBufferPtr, Length, FEE_SET);

      }
      #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
      else
      {
        /* [cover parentID={14D8388C-3115-4aa5-9C66-A64D6B220D96}]
        Return E_NOT_OK
        [/cover] */
        RetVal = E_NOT_OK;
        /* [cover parentID={85958C19-89C5-4634-90CC-30FF5A1303F7}]
        Fee Safety is enabled
        [/cover] */
        #if (FEE_SAFETY_ENABLE == STD_ON)
        Fee_lReportError(FEE_SID_GETPREVDATA,
                          FEE_SE_INVALID_BLOCK_NO, FEE_SAFETY_ERROR);
        #endif

        }
        #endif
      }
    }
    #if(MCAL_AR_VERSION == MCAL_AR_440)
    else
    {
      RetVal = E_NOT_OK;
  #if(FEE_SAFETY_ENABLE == STD_ON)
      Fee_lReportError(FEE_SID_GETPREVDATA,
                          FEE_SE_UNINIT, FEE_SAFETY_ERROR);
      #endif
    }
    #endif
  }
  #if (FEE_SAFETY_ENABLE == STD_ON)
  else
  {
    /* [cover parentID={34543921-4CD3-4521-802C-C3B2355A5C40}]
    Is configuration pointer is NULL?
    [/cover] */
    if(Fee_CfgPtr == NULL_PTR)
    {
      Fee_lReportError(FEE_SID_GETPREVDATA,
                          FEE_SE_UNINIT, FEE_SAFETY_ERROR);
    }
    else
    {
      Fee_lReportError(FEE_SID_GETPREVDATA,
                          FEE_SE_PARAM_POINTER, FEE_SAFETY_ERROR);
    }
    RetVal = E_NOT_OK;
  }
  #endif
  /* [cover parentID={1566E231-D1FA-4dd6-A8BA-E662C3FD3A84}]
  Merge
  [/cover] */
  /* [cover parentID={CA1FE649-9DFC-45d4-98C2-268C7D65D4E4}]
  Return
  [/cover] */
  return(RetVal);

}
#endif /* #if (FEE_GET_PREV_DATA_API == STD_ON) */

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
/* [cover parentID={18B78232-0B7E-4d65-AF36-AAA3AF6EAB24}][/cover] */
Std_ReturnType Fee_17_GetEccErrorInfo( uint16 * const BlockNumberPtr,
                             uint32 * const PageAddressPtr )
{
  MemIf_StatusType DriverStatus;
  /* [cover parentID={E07F38CA-3CC3-417f-ADE8-DD4EE012EDC1}]
  Return E_NOT_OK
  [/cover] */
  Std_ReturnType RetVal = E_NOT_OK;
  uint16 BlkNumber;

  #if(FEE_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={556E02D3-2F65-4e5b-B7BD-FD134D4AED81}]
  Configuration pointer is not null
  [/cover] */
  if((Fee_CfgPtr != NULL_PTR))
  #endif
  {
    DriverStatus = Fee_lGetStatus();
    #if(MCAL_AR_VERSION == MCAL_AR_440)
    /* [cover parentID={44268033-CAD4-49d4-B110-F3240C2CEAE9}]
    Driver initialization is complete
    [/cover] */
    if(DriverStatus != MEMIF_UNINIT)
    #endif
    {
      /* [cover parentID={980D390D-D43B-4797-8978-6C95B34B7387}]
        Driver is initialized
      [/cover] */
      if(DriverStatus == MEMIF_IDLE)
      {
        /* [cover parentID={28F6EA1C-B66D-41d6-9A2D-4B9E5E12A81D}]
          Input parameter pointer BlockNumber or PageAddress is NULL
        [/cover] */
        if((BlockNumberPtr != NULL_PTR) && (PageAddressPtr != NULL_PTR))
        {
          /* [cover parentID={78DD5A93-2281-4686-91C2-63E1EE10DF9F}]
          Update the block number and page address to pass parameter
          [/cover] */
          RetVal = Fls_17_Dmu_GetEccErrorPageAddress(PageAddressPtr);
          /* [cover parentID={30128A61-16F4-4ab8-847D-39EAF67A6CAA}]
          Fls return without error
          [/cover] */
          if(RetVal == E_OK)
          {
            /* [cover parentID={8AC526CB-3FDB-4a8f-94E9-A15BC4A14FFB}]
              Page address is by default (no ECC error detected)
            [/cover] */
            if(*(PageAddressPtr) != FEE_DEFAULT_PAGE_ADDRESS)
            {
              /* [cover parentID={68DC7F0A-19D3-49ec-8251-177B6171D100}]
                Get block number for the page address
              [/cover] */
              BlkNumber = \
              Fee_lGetEccErrorBlockNumber(*(PageAddressPtr));
              *(BlockNumberPtr) = BlkNumber;
            }
            else
            {
              *(BlockNumberPtr) = FEE_DEFAULT_BLK_NUMBER;
            }
            /* [cover parentID={153B8203-78E3-4507-A4AD-C5A4CC168A2E}]
              Return E_OK
            [/cover] */
          }
        }
        #if(FEE_SAFETY_ENABLE == STD_ON)
        else
        {
          /* [cover parentID={E94F4D3E-689A-4a12-9AB7-74F79C77CCB7}]
          Report error FEE_SE_PARAM_POINTER
          [/cover] */
          Fee_lReportError(FEE_SID_GETECCERRORINFO, FEE_SE_PARAM_POINTER, FEE_SAFETY_ERROR);
        }
        #endif
      }
      else
      {
        /* [cover parentID={C1AF3C70-0B6B-46fd-861A-7CC5615E71DB}]
        Driver is busy
        [/cover] */
        #if (MCAL_AR_VERSION == MCAL_AR_440) && \
          (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
        if(DriverStatus == MEMIF_BUSY)
        #endif
        {
        #if (FEE_RUNTIME_ERROR_DETECT == STD_ON)
          /* [cover parentID={7F56CEB6-177E-484e-A085-8AA2C8ED0DE4}]
          Report runtime error FEE_E_BUSY
          [/cover] */
          Fee_lReportError(FEE_SID_GETECCERRORINFO, FEE_E_BUSY, FEE_RUNTIME_ERROR);
        #elif (FEE_SAFETY_ENABLE == STD_ON) && (MCAL_AR_VERSION == MCAL_AR_422)
          Fee_lReportError(FEE_SID_GETECCERRORINFO, FEE_SE_BUSY, FEE_SAFETY_ERROR);
        #endif
        }
      }
    }
    #if(FEE_SAFETY_ENABLE == STD_ON) && (MCAL_AR_VERSION == MCAL_AR_440)
    else
    {
      Fee_lReportError(FEE_SID_GETECCERRORINFO, FEE_SE_UNINIT, FEE_SAFETY_ERROR);
    }
    #endif
  }
  #if(FEE_SAFETY_ENABLE == STD_ON)
  else
  {
    /* [cover parentID={402415BD-F0B2-4153-883F-06A46190AB52}]
    Report error FEE_SE_UNINT
    [/cover] */
    Fee_lReportError(FEE_SID_GETECCERRORINFO, FEE_SE_UNINIT, FEE_SAFETY_ERROR);
  }
  #endif
  return RetVal;
}
#endif


#if (FEE_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** TRACEABILITY: [cover parentID={C8E8D26B-C335-4eaf-8F42-C2646611E65E}]      **
**                                                                            **
** Syntax :void Fee_GetVersionInfo(Std_VersionInfoType * const VersionInfoPtr)**
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:      0x08                                                      **
**                                                                            **
** Sync/Async:      Synchronous                                               **
**                                                                            **
** Reentrancy:      Reentrant                                                 **
**                                                                            **
** Parameters (out): VersionInfoPtr - Pointer to standard version information **
**           structure                                                        **
**                                                                            **
** Parameters (in): none                                                      **
**                                                                            **
** Return value:    void                                                      **
**                                                                            **
** Description :    This service returns the version information of           **
**                  this module.                                              **
**                  The version information includes:                         **
**                  Module Id, Vendor Id, Vendor specific version numbers     **
**                                                                            **
*******************************************************************************/
/* [cover parentID={A60B63DC-1A6F-4048-B92A-213AB0E88AC8}]
Fee_GetVersionInfo
[/cover] */
void Fee_GetVersionInfo(Std_VersionInfoType * const VersionInfoPtr)
{
  /* [cover parentID={7D1F1883-FDF9-4fef-8DD2-99D904DC4678}]
  DET enabled
  [/cover] */
  #if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={602A3EF9-A774-4da2-B06F-44CF452D6C49}]
  Is VersionInfoPtr NULL?
  [/cover] */
  if ((VersionInfoPtr) == NULL_PTR)
  {
    /* [cover parentID={9C33444C-8F98-4c37-AD80-F438CD0DFA76}]
    Report DET error as FEE_E_PARAM_POINTER
    [/cover] */
    Fee_lReportError(FEE_SID_GETVERSIONINFO, FEE_E_PARAM_POINTER, FEE_DET_SAFETY_ERROR);
  }
  else
  #endif
  {
    /* [cover parentID={3161645F-3505-46a0-8EA4-A6356B1D3D11}]
    Update Version Information in the location referenced by VersionInfoPtr
    [/cover] */
    /* FEE Module ID */
    ((Std_VersionInfoType*)(VersionInfoPtr))->moduleID = FEE_MODULE_ID;
    /* FEE Vendor ID */
    ((Std_VersionInfoType*)(VersionInfoPtr))->vendorID = FEE_VENDOR_ID;
    /* major version of FEE */
    ((Std_VersionInfoType*)(VersionInfoPtr))->sw_major_version =
      (uint8)FEE_SW_MAJOR_VERSION;
    /* minor version of FEE */
    ((Std_VersionInfoType*)(VersionInfoPtr))->sw_minor_version =
      (uint8)FEE_SW_MINOR_VERSION;
    /* patch version of FEE */
    ((Std_VersionInfoType*)(VersionInfoPtr))->sw_patch_version =
      (uint8)FEE_SW_PATCH_VERSION;
  }
  /* [cover parentID={5ABE883B-1B58-444c-A871-81DC7F9533FA}]
  Return
  [/cover] */
}
#endif


/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/
#if (FEE_GET_ECC_ERROR_INFO_API == STD_ON)
/*******************************************************************************
** Syntax: LOCAL_INLINE boolean Fee_lGetEccErrorBlockNumber(                  **
**                                                  uint32 const PageAddress) **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : PageAddress - Page address for which block number to be  **
**                   searched.                                                **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : uint16 - (1 - 65534)                                     **
**                                                                            **
** Description : This function return block number which have input           **
**               page address                                                 **
*******************************************************************************/
/* [cover parentID={1C32CCC9-EAB5-44b0-818A-C88C5CF6B24A}][/cover] */
LOCAL_INLINE uint16 Fee_lGetEccErrorBlockNumber(uint32 const PageAddress)
{
  uint16                    BlockIndex = FEE_RESET;
  #if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
  const Fee_StateDataType   *StateDataPtr;
  const Fee_CacheType             *CachePtr;
  #endif
  const Fee_BlockType       *BlockCfgPtr;
  uint32                    BlockEndAddress;
  uint32                    BlockStartAddress;
  uint16 RetVal = FEE_DEFAULT_BLK_NUMBER;
  #if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
  uint32 NumberOfPages;
  #endif

  /* [cover parentID={DDD1C540-52EC-4f60-86C5-4840458333C8}]
  For all the blocks in cache table
  [/cover] */
  while(BlockIndex < Fee_CfgPtr->FeeBlkCnt)
  {
    BlockCfgPtr = &(Fee_CfgPtr->FeeBlockConfigPtr[BlockIndex]);
    #if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
    StateDataPtr = Fee_CfgPtr->FeeStatePtr;
    CachePtr = &(StateDataPtr->FeeBlockInfo[BlockIndex]);
    #if (FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_DATA_ONLY)
    NumberOfPages = Fee_lGetDFLASHPages(BlockCfgPtr->Size);
    if(CachePtr->Address != FEE_RESET)
    {
      BlockStartAddress = CachePtr->Address + FEE_BASE_ADDRESS;
      BlockEndAddress = (BlockStartAddress + (NumberOfPages * FEE_PAGE_SIZE));
    }
    else
    {
      BlockStartAddress = FEE_DEFAULT_PAGE_ADDRESS;
      BlockEndAddress = FEE_DEFAULT_PAGE_ADDRESS;
    }
  #else
    if(BlockIndex >= FEE_QSBLOCK_BEGIN_INDEX)
    {
      BlockStartAddress = BlockCfgPtr->Address + FEE_BASE_ADDRESS;
      BlockEndAddress = (BlockStartAddress + BlockCfgPtr->Size);
    }
    else
    {
      NumberOfPages = Fee_lGetDFLASHPages(BlockCfgPtr->Size);
      if(CachePtr->Address != FEE_RESET)
      {
        BlockStartAddress = CachePtr->Address + FEE_BASE_ADDRESS;
        BlockEndAddress = (BlockStartAddress + (NumberOfPages * FEE_PAGE_SIZE));
      }
      else
      {
        BlockStartAddress = FEE_DEFAULT_PAGE_ADDRESS;
        BlockEndAddress = FEE_DEFAULT_PAGE_ADDRESS;
      }
    }
  #endif
  #else
    BlockStartAddress = BlockCfgPtr->Address + FEE_BASE_ADDRESS;
    BlockEndAddress = (BlockStartAddress + BlockCfgPtr->Size);
  #endif
    /* [cover parentID={EA792F62-4814-4bb6-922D-F567A0348C7F}]
    Input page address is in between the start and end address of the currnet block
    [/cover] */
        if((PageAddress >= BlockStartAddress) && (PageAddress < BlockEndAddress))
    {
      RetVal = BlockCfgPtr->BlockNumber;
      BlockIndex = Fee_CfgPtr->FeeBlkCnt;
    }
    BlockIndex += FEE_ONE;
  }
  /* [cover parentID={50921FC0-E605-4662-985D-F756FA434332}]
  Return block number
  [/cover] */
  return RetVal;
}
#endif

/*******************************************************************************
** Syntax: LOCAL_INLINE boolean Fee_lIsUserReadReqstd(                        **
**                                     const Fee_StateDataType * const s_ptr) **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : s_ptr - Pointer to state data                            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : boolean                                                  **
**                   TRUE : Read operation requested                          **
**                   FALSE :Read operation not requested                      **
**                                                                            **
** Description : This routine checks if user read is requested                **
*******************************************************************************/
/* [cover parentID={B5AACBC9-6239-4358-A796-8AD0A7CFE8D5}][/cover] */
LOCAL_INLINE boolean Fee_lIsUserReadReqstd(const Fee_StateDataType * \
    const s_ptr)
{
  boolean RetVal;

  /* [cover parentID={67D14067-7D90-41eb-BDFD-C33661717F4C}][/cover] */
  if (s_ptr->FeePendReqStatus == FEE_REQ_READ)
  {
    RetVal = (boolean)TRUE;
  }
  else
  {
    RetVal = (boolean)FALSE;
  }
  return(RetVal);
}

/*******************************************************************************
** Syntax: LOCAL_INLINE boolean Fee_lIsUserWriteInvldReqstd                   **
**                                (const Fee_StateDataType * const s_ptr)     **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : s_ptr - Pointer to state data                            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : boolean                                                  **
**                   TRUE : write/invalidate operation requested              **
**                   FALSE :write/invalidate operation not requested          **
**                                                                            **
** Description : This routine checks if user write/invalidate is requested    **
*******************************************************************************/
/* [cover parentID={3C4D35C8-16D9-426e-80C9-8616C8AC0C73}][/cover] */
LOCAL_INLINE boolean Fee_lIsUserWriteInvldReqstd
(const Fee_StateDataType * const s_ptr)
{
  boolean RetVal;

  /* [cover parentID={CC382DB4-7CBA-4074-9E37-06F476849EA4}][/cover] */
  if(((s_ptr)->FeePendReqStatus == FEE_REQ_NORM_WRITE) ||
      ((s_ptr)->FeePendReqStatus == FEE_REQ_IMM_WRITE))
  {
    RetVal = (boolean)TRUE;
  }
  else
  {
    RetVal = (boolean)FALSE;
  }
  return(RetVal);
}

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/*******************************************************************************
** Syntax: LOCAL_INLINE boolean Fee_lIsSectorEmpty(const uint8 state,         **
**                                                 const uint8 used)          **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Reentrant                                                 **
**                                                                            **
** Parameters (in) : state - Sector state                                     **
**                   used - Sector used status                                **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : boolean                                                  **
**                 TRUE: Sector is empty , no data or state page is available **
**                 FALSE:Sector is  not empty , data or state page is         **
**                       available                                            **
** Description : This routine checks if sector is empty                       **
*******************************************************************************/
/* [cover parentID={ECEF61D1-8F31-4d29-B2BB-9FD0A24C0AF3}]
Fee_lIsSectorEmpty
[/cover] */
/* [cover parentID={6E6F4F9B-D703-4fcc-9081-8690C09C9614}][/cover] */
LOCAL_INLINE boolean Fee_lIsSectorEmpty(const uint8 state, const uint8 used)
{
  boolean RetVal;
  /* [cover parentID={6E3FDC07-BF62-4bc9-A809-0FB7683FFB69}][/cover] */
  if((state == FEE_STATELESS) && (used == FEE_RESET))
  {
    RetVal = (boolean)TRUE;
  }
  else
  {
    RetVal = (boolean)FALSE;
  }
  return(RetVal);
}


/*******************************************************************************
** Syntax: LOCAL_INLINE uint32 Fee_lIsWLBeginning(const uint32 address)       **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Reentrant                                                     **
**                                                                            **
** Parameters (in) : address - address to be checked                          **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : uint32                                                   **
**                                                                            **
** Description : This routine returns 0 if the given address is the beginning **
**               of a WL, non-zero otherwise.                                 **
*******************************************************************************/
/* [cover parentID={8F8F02D5-8532-4a9f-8706-E0FBDB005C24}]
Fee_lIsWLBeginning
[/cover] */
/* [cover parentID={9F2B0703-4047-44ff-AFB6-C84ABA203DDC}][/cover] */
LOCAL_INLINE uint32 Fee_lIsWLBeginning(const uint32 address)
{
  return(address & ((uint32)FEE_DFLASH_WORDLINE_SIZE_1));
}
#endif

/*******************************************************************************
** Syntax: LOCAL_INLINE uint32 Fee_lGetWLBeginning(const uint32 address)      **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : (uint32)address - address to be processed                **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : uint32                                                   **
**                                                                            **
** Description : This routine returns the start address of the WL             **
*******************************************************************************/
/* [cover parentID={02DF64E1-B52E-4a5d-B157-D5959AA84FD8}]
Fee_lGetWLBeginning
[/cover] */

/* [cover parentID={699ABA6A-A4E3-42de-9722-C50E06E1E0CF}][/cover] */
LOCAL_INLINE uint32 Fee_lGetWLBeginning(const uint32 address)
{
  return(address & ((uint32)(~((uint32)FEE_DFLASH_WORDLINE_SIZE_1))));
}

/*******************************************************************************
** Syntax: LOCAL_INLINE uint32 Fee_lGetNextWLAddr(const uint32 address)       **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : (uint32)address - address to be processed                **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : uint32                                                   **
**                                                                            **
** Description : This routine returns the start address of the next WL        **
*******************************************************************************/
/* [cover parentID={65F173FD-1411-4517-A860-BB69BA76F9E5}]
Fee_lGetNextWLAddr
[/cover] */
/* [cover parentID={237D5697-4E92-45f4-B0CD-41D2B0E16E50}][/cover] */
LOCAL_INLINE uint32 Fee_lGetNextWLAddr(const uint32 address)
{
  /*Beginning of WL from current address + WL -> next free WL*/
  return((Fee_lGetWLBeginning(address)) + FEE_DFLASH_WORDLINE_SIZE);
}
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/*******************************************************************************
** Syntax: LOCAL_INLINE boolean Fee_lIsGcTriggeredOnce(const Fee_StateDataType**
**                                                      *const StateDataPtr)  **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : StateDataPtr - Pointer to state data                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : boolean                                                  **
**                 TRUE: GC is was never triggered after initialization       **
**                 FALSE: GC is was  triggered after initialization           **
** Description : This routine checks whether GC was never triggered after     **
** initialization. This is done by checking whether Fee_Write was never       **
** called in the FEE_GC_RESTART_WRITE configuration                           **
*******************************************************************************/
/* [cover parentID={BA9DCE16-6576-4411-B7AF-D3331416BD3E}]
Fee_lIsGcTriggeredOnce
[/cover] */
/* [cover parentID={9BF281BD-6832-42df-B109-9733A317148B}][/cover] */
LOCAL_INLINE boolean Fee_lIsGcTriggeredOnce(const Fee_StateDataType
    * const StateDataPtr)
{
  boolean RetVal;

  /* [cover parentID={F40985E9-E5FA-4a55-8F4E-CBA43C7F75B4}][/cover] */
  if ((Fee_CfgPtr->FeeGCConfigSetting.FeeGcRestartPoint ==
       (uint32)FEE_GC_RESTART_WRITE)
      && (StateDataPtr->FeeStatusFlags.FeeWriteInvldQSeraseAPICalled ==
          (uint32)FEE_RESET))
  {
    RetVal = (boolean)TRUE;
  }
  else
  {
    RetVal = (boolean)FALSE;
  }
  return(RetVal);
}

/*******************************************************************************
** Syntax: LOCAL_INLINE boolean Fee_lIsSectorThresholdCrossed(                **
**                                                    const uint32 FreePages, **
**                                                    const uint32 PageCount) **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : FreePages - Number of free pages                         **
**                   PageCount - Page count                                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : boolean                                                  **
**                   TRUE : Sector Threshold is crossed.                      **
**                   FALSE: Sector Threshold is not crossed.                  **
**                                                                            **
** Description : This routine checks whether sector threshold will be crossed **
*******************************************************************************/
/* [cover parentID={414557E8-31F9-496c-AD2A-B0555A816D4D}]
Fee_lIsSectorThresholdCrossed
[/cover] */
/* [cover parentID={E52D591F-752A-408e-AFAD-3C5745DDD1C8}][/cover] */
LOCAL_INLINE boolean Fee_lIsSectorThresholdCrossed(const uint32 FreePages,
    const uint32 PageCount)
{
  boolean RetVal;
  /* [cover parentID={021235CB-2818-4488-B9E6-FB3E31002A02}][/cover] */
  /* Applying sign conversion in following condition will not cause a problem
  because the value of the parameters are limited by size of the flash which
  is typically order of a few MBs applying BV with MSB set will be due to a
  implausible value. */
  if ((sint32)(((sint32)FreePages - (sint32)PageCount)
               * (sint32)FEE_DFLASH_PAGE_SIZE)
      < (sint32)(Fee_CfgPtr->FeeThresholdLimit))
  {
    RetVal = (boolean)TRUE;
  }
  else
  {
    RetVal = (boolean)FALSE;
  }
  return(RetVal);
}

/*******************************************************************************
** Syntax: LOCAL_INLINE boolean Fee_lIsSectorEndCrossed(                      **
**                                                const uint32 FreePages,     **
**                                                const uint32 PageCount)     **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : FreePages - Number of free pages                         **
**                   PageCount - Page count                                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : boolean                                                  **
**                   TRUE : Sector end will be crossed.                       **
**                   FALSE: Sector end will not be crossed.                   **
**                                                                            **
** Description : This routine checks whether sector end will be crossed       **
*******************************************************************************/
/* [cover parentID={08E7BF93-2A90-4024-9FA2-E0BDF8973430}]
Fee_lIsSectorEndCrossed
[/cover] */
/* [cover parentID={12E3423D-CA85-4d40-B015-6D54F9438D32}][/cover] */
LOCAL_INLINE boolean Fee_lIsSectorEndCrossed(const uint32 FreePages,
    const uint32 PageCount)
{
  boolean RetVal;

  /* [cover parentID={44BB0E1F-C2A8-4579-A0DE-68DA603AE223}][/cover] */
  if (FreePages < PageCount)
  {
    RetVal = (boolean)TRUE;
  }
  else
  {
    RetVal = (boolean)FALSE;
  }
  return(RetVal);
}
#endif
/*******************************************************************************
** TRACEABILITY: []                                                           **
**                                                                            **
** Syntax : static void Fee_lHandleUsrJobFailure(const uint8 Error)           **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : Error : Type of user job failure                         **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function handles the user job failure occuring due to   **
**               FLS operation failure                                        **
*******************************************************************************/
/* [cover parentID={F93CF5D6-8C82-4a59-A5FB-9A4A154CF19E},
{3D4E0F4A-DBE1-47ae-8344-313B4E73FAC9}]
Fee_lHandleUsrJobFailure
[/cover] */
static void Fee_lHandleUsrJobFailure(const uint8 Error)
{
  Fee_StateDataType     *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  /* Set StateDataPtr->FeeJobResult as Failed */

  /* [cover parentID={1C77FA7F-E001-42aa-8CCD-1B2A545FCE28}][/cover]*/
  if(Error != FEE_CANCEL )
  {
    StateDataPtr->FeeJobResult = MEMIF_JOB_FAILED;
    /* During runtime, FeeBlkPageCount is used to store the number of pages of
    the block written during the user write request and as well as during
    garbage collection. When pending user request is cancelled, FeeBlkPageCount
    may contain the count of the number of pages written to DFlash during
    garbage collection which should be retained. Hence, FeeBlkPageCount is reset
    only when user job is failed and not while cancelling a pending request */
    StateDataPtr->FeeBlkPageCount = FEE_RESET;
  }
  else
  {
    StateDataPtr->FeeJobResult = MEMIF_JOB_CANCELED;
  }
  #if((FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA ) &&\
      (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON))
  /*Check if QS erase was suspended. If yes then set FeePendReqStatus to
  FEE_REQ_QUASI_ERASE to set module status to busy.*/
  /* [cover parentID={2103E23E-129A-4893-90E7-3E60B8C98F6B}][/cover]*/
  if(StateDataPtr->FeeQsEraseSuspend == FEE_ERASE_SUSPENDED)
  {
    /* [cover parentID={984E37D8-474A-4100-90B6-0933DE7D75BD}][/cover]*/
    StateDataPtr->FeePendReqStatus = FEE_REQ_QUASI_ERASE;
    StateDataPtr->FeeQsJob = FEE_ERASE_JOB;
  }
  else
  #endif
  {
    /* [cover parentID={2FB3BA7A-0FD7-43c4-B1E8-AFAAB9028DEC}][/cover]*/
    StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_NO_REQ;
  }

  /* Reset the Invalid Status flag */
  /* [cover parentID={219B2EBC-502E-4f49-8DCA-1965DB877794}][/cover]*/
  StateDataPtr->FeeStatusFlags.FeeBlkInvalidStatus = FEE_RESET;
  StateDataPtr->FeeUserJobStatus = FEE_JOB_IDLE;
  StateDataPtr->FeeUserJobResult = FEE_JOB_FAIL;
  StateDataPtr->FeeUserJobFailCount = FEE_RESET;

  /* Raise Job Failed production error */
  #if (FEE_WRITE_DEM_REPORT == FEE_ENABLE_DEM_REPORT)
  /* [cover parentID={57969A5A-E34A-4dcc-BF82-7F6C19DB0BAB}][/cover]*/
  if (Error == FEE_WRITE)
  {
    /* [cover parentID={85B21C01-71F7-4c33-AE93-125C456302CE}]
    Report write production error to Mcal_Wrapper FEE_E_WRITE
    [/cover] */
    Fee_lReportDemError(FEE_E_WRITE, DEM_EVENT_STATUS_FAILED);
  }
  #endif

  #if (FEE_INVALIDATE_DEM_REPORT == FEE_ENABLE_DEM_REPORT)
  /* [cover parentID={0C99BE02-B1FD-49b0-8F4E-C4ED3B2B92C6}][/cover]*/
  if (Error == FEE_INVALIDATE)
  {
    /* [cover parentID={F0B26CA2-58F4-4983-AF2C-69D7A8B445BE}]
    Report invalidate error to Mcal_Wrapper FEE_E_INVALIDATE
    [/cover] */
    Fee_lReportDemError(FEE_E_INVALIDATE, DEM_EVENT_STATUS_FAILED);
  }
  #endif

  #if (FEE_READ_DEM_REPORT == FEE_ENABLE_DEM_REPORT)
  /* [cover parentID={8144374E-C639-41e8-99BD-B0AD47AA0D19}][/cover]*/
  if (Error == FEE_READ)
  {
    /* [cover parentID={296972F3-33FE-4420-B8E2-32CC87327906}]
    Report read error to Mcal_Wrapper FEE_E_READ
    [/cover] */
    Fee_lReportDemError(FEE_E_READ, DEM_EVENT_STATUS_FAILED);
  }
  #endif

  #if (FEE_WRITE_DEM_REPORT != FEE_ENABLE_DEM_REPORT)
    #if (FEE_INVALIDATE_DEM_REPORT != FEE_ENABLE_DEM_REPORT)
      #if (FEE_READ_DEM_REPORT != FEE_ENABLE_DEM_REPORT)
      /* To avoid compiler warning */
      UNUSED_PARAMETER (Error);
      #endif
    #endif
  #endif
  #if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
  /* Report job Error notification */
  /* [cover parentID={486B22CE-BBA9-417e-989E-B8766E4BACEB}][/cover]*/
  if(Fee_CfgPtr->FeeNvmJobErrorNotification != NULL_PTR )
  {
    /* [cover parentID={FC5E8027-B173-41e5-9BFC-5DBB1466ED54}]
    Call the NVM job error notification function
    [/cover] */
    (Fee_CfgPtr->FeeNvmJobErrorNotification)();
  }
  #endif
}

/*******************************************************************************
** Syntax : static MemIf_StatusType Fee_lGetStatus(void)                      **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :None                                                  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  MemIf_StatusType                                        **
**                                                                            **
** Description : This function returns the status of the FEE driver           **
*******************************************************************************/
/*[cover parentID={17ECE2B2-88D5-4cb8-A467-57835E79CD09}][/cover]*/
static MemIf_StatusType Fee_lGetStatus(void)
{
  const Fee_StateDataType  *StateDataPtr;
  MemIf_StatusType   ReturnStatus;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  ReturnStatus = MEMIF_IDLE;
  /* [cover parentID={11105008-76C8-431b-91C3-49D5F0DE2B07}]
  Return status as MEMIF_IDLE
  [/cover] */
  /*[cover parentID={63FC1E50-BFF4-491d-93E4-D47CD2DFCC0C}][/cover]*/
  if(StateDataPtr->FeePendReqStatus == FEE_WRITE_FAIL)
  {
    /* ReturnStatus is MEMIF_IDLE */
  }
  /* If there is a request pending */
  /*[cover parentID={9D420F94-1ADB-4285-99B9-FC0D303BAB73}][/cover]*/
  else if(StateDataPtr->FeePendReqStatus != FEE_PEND_PREV_NO_REQ)
  {
    /* [cover parentID={1E38F4F8-84B8-4278-9D72-057D620E3EA7}]
    Return status as MEMIF_BUSY
    [/cover] */
    ReturnStatus = MEMIF_BUSY;
  }
  /* [cover parentID={4BE544DA-5C4E-4ff8-99F7-4CA2BD9118E6}]
  Return status as MEMIF_IDLE
  [/cover] */
  /* Init activities NOT triggered */
  /*[cover parentID={04C546D1-2E75-4922-8A2B-1D3F5447C555}][/cover]*/
  else if(StateDataPtr->FeeStatusFlags.FeeStartInitGC == (uint32)FEE_RESET)
  {
    /* ReturnStatus is MEMIF_IDLE */
  }
  /* [cover parentID={A5B248A0-FCDA-4d8b-9EB1-41ACA8BCC8C9}]
  Return status as MEMIF_IDLE
  [/cover] */
  #if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
  /* If the GC/InitGC has failed */
  /*[cover parentID={50F4AB07-F5D2-4bc2-90CA-AB180B66A739}][/cover]*/
  else if((StateDataPtr->FeeGcState == FEE_GC_FAIL) ||
          (StateDataPtr->FeeInitGCState == FEE_INITGC_FAIL))
  {
    /* ReturnStatus is MEMIF_IDLE */
  }

  /* if Cache update activities ongoing */
  /*[cover parentID={B196B7FD-C996-4847-A650-FA07049EE1F5}][/cover]*/
  else if(StateDataPtr->FeeCacheState != FEE_CACHE_UPDATE_COMPLETE)
  {
    /* [cover parentID={DB4C4736-67E3-478c-945D-263CA89FE9FB}]
    Return status as MEMIF_BUSY_INTERNAL
    [/cover] */
  #if (MCAL_AR_VERSION == MCAL_AR_422)
  ReturnStatus = MEMIF_BUSY_INTERNAL;
  #else
  /* [cover parentID={EE79AC0B-4E24-4a65-9183-7DF24AB0005E}]
  Return status as MEMIF_UNINIT
  [/cover] */
  ReturnStatus = MEMIF_UNINIT;
  #endif
  }
  #else
  /*[cover parentID={E00B5D53-532C-4487-8A9C-696C833C81ED}][/cover]*/
  else if(StateDataPtr->FeeCacheState != FEE_CACHE_IDLE_QS)

  {
    /* [cover parentID={E252153D-5632-4a82-B5A2-BC4D7D254DBD}]
    Return status as MEMIF_BUSY_INTERNAL
    [/cover] */
  #if (MCAL_AR_VERSION == MCAL_AR_422)
  ReturnStatus = MEMIF_BUSY_INTERNAL;
  #else
  ReturnStatus = MEMIF_UNINIT;
  #endif
  }
  #endif

  #if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
  /*[cover parentID={E1275385-88DF-4f9a-A6B9-84870A57EAA7}][/cover]*/
  else if(StateDataPtr->FeeGcState != FEE_GC_IDLE)
  {
    /* Scenario: First Fee write is not called but Fee_Read  */
    /* is already called                                     */
    /* [cover parentID={47C71766-E860-48a1-B791-ED113036B9FC}]
    Return status as MEMIF_IDLE
    [/cover] */
    if((boolean)FALSE != Fee_lIsGcTriggeredOnce(StateDataPtr))
    {
      /* ReturnStatus is MEMIF_IDLE */
    }
    else
    {
      /* [cover parentID={E252153D-5632-4a82-B5A2-BC4D7D254DBD}]
      Return status as MEMIF_BUSY_INTERNAL
      [/cover] */
      ReturnStatus = MEMIF_BUSY_INTERNAL;
    }
  }
  #endif
  else
  {
    /* ReturnStatus is MEMIF_IDLE */
  }

  return(ReturnStatus);

}/*End of Fee_GetStatus */
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/*******************************************************************************
** Syntax : LOCAL_INLINE boolean Fee_lGcCheckUnconfigBlkCopy(void)            **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :None                                                  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  TRUE : At least one un-configured block is to be copied **
**                    FALSE: All un-configured blocks are copied              **
**                                                                            **
** Description : This function checks whether any un-configured block needs   **
**               to be copied                                                 **
*******************************************************************************/
/* [cover parentID={8B763DD8-7779-4ef2-9186-791AFD8AD157}]
Fee_lGcCheckUnconfigBlkCopy
[/cover] */
/* [cover parentID={4CAA1D7C-18AE-4279-9BDC-4B575883F89F}][/cover]*/
LOCAL_INLINE boolean Fee_lGcCheckUnconfigBlkCopy(void)
{
  const Fee_StateDataType     *StateDataPtr;
  boolean               RetVal;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* if any un-configured block is yet to be copied then, return TRUE */
  /* [cover parentID={F6193DC3-A6A6-4344-A2C7-39BBA039DDDC}][/cover]*/
  if(StateDataPtr->FeeGCUnconfigBlkCopyIndex <
      StateDataPtr->FeeUnConfigBlockCount)
  {
    RetVal = (boolean)TRUE;
  }
  else
  {
    RetVal = (boolean)FALSE;
  }

  return(RetVal);
}
#endif
/*******************************************************************************
** Syntax: static Fls_17_Dmu_Job_Type Fee_lGetUserJob(const uint8 PendReqType)**
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :(uint8)PendReqType : Type of pending request              **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Fls_17_Dmu_Job_Type                                     **
**                                                                            **
** Description : This function returns the ongoing user job                   **
*******************************************************************************/
/*[cover parentID={B13D305A-1DCD-4fd2-941E-37FD1B4248B9}][/cover]*/
static Fls_17_Dmu_Job_Type Fee_lGetUserJob(const uint8 PendReqType)
{
  Fls_17_Dmu_Job_Type RetVal = FEE_NO_JOB;

  switch(PendReqType)
  {
    /* These states mean that the write job is going on */
    /*[cover parentID={BE31F97F-39C4-4017-9EB8-9C6A095CAC55}][/cover]*/
    case FEE_PEND_PREV_COMPARE:
    case FEE_PEND_INTR_COMPARE:
    {
      RetVal = FEE_WRITE_JOB;
      break;
    }

    /* The following are the states for read job */
    /*[cover parentID={35AA9CF5-179C-4474-8DC3-2AA8C2E156CA}][/cover]*/
    case FEE_PEND_PREV_READ_REQ:
    case FEE_PEND_PREV_READ_NOTIF:
    {
      RetVal = FEE_READ_JOB;
      break;
    }

    default:
    {
      break;
    }
  }

  return(RetVal);

}/*End of Fee_lGetUserJob */
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/*******************************************************************************
** TRACEABILITY: []                                                           **
**                                                                            **
** Syntax : static boolean Fee_lIsReadAllowedbyGC(void )                      **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :None                                                  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Bool                                                    **
**                   TRUE: Read Request execution is allowed during GC        **
**                   FALSE: Read Request execution not is allowed during GC   **
**                                                                            **
** Description : This function checks if the user read is allowed by GC       **
**                                                                            **
*******************************************************************************/
/* [cover parentID={1C4E2854-85A3-4a9d-A2EC-F0B8BB42000F}]
Fee_lIsReadAllowedbyGC
[/cover] */
/* [cover parentID={3D16AD0C-8960-490b-A95F-E4CA1693A8FF}]*/
static boolean Fee_lIsReadAllowedbyGC(void)
{

  #if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
  Fee_StateDataType *StateDataPtr;
  Std_ReturnType     FlsRetVal;
  #else
  const Fee_StateDataType *StateDataPtr;
  #endif
  boolean            RetVal;
  /* [cover parentID={1C4E2854-85A3-4a9d-A2EC-F0B8BB42000F}]*/
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  RetVal = (boolean)FALSE;
  /* [cover parentID={9DF016FA-2FB7-4a8f-AEF7-B9A77418CBDA}]
  Is GC requested and not yet started?
  [/cover] */
  /* GC is requested and not yet started */
  if(StateDataPtr->FeeGcState == FEE_GC_REQUESTED)
  {
    RetVal = (boolean)TRUE;
  }
  /* [cover parentID={8A62EE37-5298-4088-8DC6-DCC4F0F1C2C6}]
  Is copying of unconfigured blocks done and copy of next unconfigured block has not yet started?
  [/cover] */
  /* GC is in Un-configured block copy state and copy of current block is done
  and  next block copy is not yet started */
  else if((StateDataPtr->FeeGcState == FEE_GC_UNCFG_START_COPY) &&
          (StateDataPtr->FeeIntrJobStatus == FEE_JOB_IDLE))
  {
    RetVal = (boolean)TRUE;
  }
  /* [cover parentID={7E7F6DEA-EB6C-4caa-8CA8-7B8B4270BBCE}]
  Is copying of configured blocks done and copy of next configured block has not yet started?
  [/cover] */
  /* GC is in configured block copy state and copy of current block is done
  and  next block copy is not yet started */
  else if((StateDataPtr->FeeGcState == FEE_GC_START_COPY) &&
          (StateDataPtr->FeeIntrJobStatus == FEE_JOB_IDLE))
  {
    RetVal = (boolean)TRUE;
  }

  /*Check if GC in erase state as part of normal GC opertaion.Pending request
   can not be executed when GC in erase state as part init GC beacuse of cache
   table is not yet build and initializtion activity is not finished */
  /* [cover parentID={6D74086F-E7FA-4b20-9046-91C74051B1DD}][/cover] */
  else if((StateDataPtr->FeeGcState == FEE_GC_ERASE_PREV_SECTOR) ||
           (StateDataPtr->FeeGcState == FEE_GC_INIT_ERASE_PREV_SECTOR))
  {
    /*check if erased operation is requested to fls*/
    /* [cover parentID={2C1D3B99-D137-4c61-97EF-7B7A562AD28B}][/cover] */
    if(StateDataPtr->FeeIntrJobStatus == FEE_JOB_REQSTD)
    {
      /* call fls erase suspend function if supported by hardware */
    /* [cover parentID={E1E2A5AC-64CC-4b33-8D5A-E6DFA62C036D}]
     Check for erase suspend function
    [/cover] */
    #if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
      /* [cover parentID={8F7ACB83-7676-4010-BAAE-ABEF6FF3DEB5}][/cover] */
      if(FEE_ERASE_NOT_SUSPENDED == StateDataPtr->FeeEraseSuspendStatus)
      {
        FlsRetVal = Fls_17_Dmu_SuspendErase();
        /* [cover parentID={458957E2-5836-4961-A9B8-8FD89B996361}][/cover] */
        if(E_OK == FlsRetVal)
        {
          RetVal = (boolean)TRUE;
          StateDataPtr->FeeEraseSuspendStatus = FEE_ERASE_SUSPENDED;
        }
      }
      else
      {
        RetVal = (boolean)TRUE;
        /* In the case of a suspend request, when previous attempt of resume
        had failed at least once, then the count shall be
        reset back to 1, as it is a new request for suspend. */
        StateDataPtr->FeeEraseSuspendStatus = FEE_ERASE_SUSPENDED;
      }
      #endif
    }
    else
    {
      /* Erase operation is not started or completed */
      RetVal = (boolean)TRUE;
    }
  }
  else
  {
    /* dummy else */
  }

  return(RetVal);

}/* End of Fee_lIsReadAllowedbyGC */

/*******************************************************************************
** TRACEABILITY: []                                                           **
**                                                                            **
** Syntax : static boolean Fee_lIsWriteInvldAllowedbyGC(void)                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :None                                                  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Bool                                                    **
**                   FALSE: Write/Invalidate Request execution not allowed    **
**                   TRUE: Write/Invalidate  Request execution allowed        **
**                                                                            **
** Description : Checks if the Write/Invalidate request execution is allowed  **
**               by GC depending on the erase suspend feature configuration.  **
*******************************************************************************/
/* [cover parentID={6DB78D22-11ED-43f9-838E-5B61C20B9627}]
Fee_lIsWriteInvldAllowedbyGC
[/cover] */
/* [cover parentID={1D191D0E-C8C1-4284-89E3-AEFD9EB6974A}] */
static boolean Fee_lIsWriteInvldAllowedbyGC(void)
{
  #if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
  Fee_StateDataType *StateDataPtr;
  Std_ReturnType     FlsRetVal;
  #else
  const Fee_StateDataType *StateDataPtr;
  #endif
  boolean            RetVal;
  uint16             PendReqBlkNum;
  uint16             PendReqBlkIndex;
  Std_ReturnType     PendBlkWritable;
  const Fee_BlockType  *PendReqBlkPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  RetVal = (boolean)FALSE;

  /* Immediate write has been requested */
  /* [cover parentID={F63000BC-0CC6-484d-A803-6DB929092BB2}][/cover]*/
  if((StateDataPtr->FeePendReqStatus == (uint8)FEE_REQ_IMM_WRITE) &&
      (StateDataPtr->FeeStatusFlags.FeeBlkInvalidStatus == (uint32)FEE_RESET) &&
      ((StateDataPtr->FeeGcState == FEE_GC_UNCFG_START_COPY)
       || (StateDataPtr->FeeGcState == FEE_GC_START_COPY)))
  { /* [cover parentID={51BA216E-4E3B-4bde-8BAE-2A8640681293}]
    Is the GC read/write job requested to FLS ?
    [/cover] */
    /* Copying of an un-configure /configured block is done.Copy of next
    un-configured / configured block has not yet started */
    /* [cover parentID={51BA216E-4E3B-4bde-8BAE-2A8640681293}][/cover]*/
    if (StateDataPtr->FeeIntrJobStatus == FEE_JOB_IDLE)
    {
      RetVal = (boolean)TRUE;
    }

  }
  /* [cover parentID={72698D78-F7F1-491a-BBB4-BB737B4385EE}][/cover]*/
  else /* Immediate/Normal write has been requested during GC erase state */
  {
    /*Check if GC in erase state as part of normal GC opertaion.Pending request
    can not be executed when GC in erase state as part init GC beacuse of cache
    table is not yet build and initializtion activity is not finished */
    /* [cover parentID={72698D78-F7F1-491a-BBB4-BB737B4385EE}][/cover] */
    if(StateDataPtr->FeeGcState == FEE_GC_ERASE_PREV_SECTOR)
    {
      PendReqBlkNum = StateDataPtr->FeePendReqInfo.BlockNumber;
      PendReqBlkIndex = Fee_lGetUsrBlockIndex(PendReqBlkNum);
      /* MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic is used for
      for faster access of Block traversal.It is ensured that PendReqBlkIndex
      is within the desired boundary*/
      PendReqBlkPtr = Fee_CfgPtr->FeeBlockConfigPtr + PendReqBlkIndex;
      PendBlkWritable = Fee_lPerformCurrBlkCheck(PendReqBlkPtr);
      /* [cover parentID={9EBE5BF0-1959-4d9d-91E5-AFCF3C6181AF}][/cover] */
      if(StateDataPtr->FeeIntrJobStatus == FEE_JOB_REQSTD)
      {
        /* call fls erase suspend function if supported by hardware and can be
        suspended*/
        #if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
        if(PendBlkWritable == E_OK)
        {
          if(FEE_ERASE_NOT_SUSPENDED == StateDataPtr->FeeEraseSuspendStatus)
          { /* [cover parentID={F62D61CA-CF0C-4fd0-9A74-8EE630EF26B1}]
            Call fls erase suspend function (Only if the erase is not suspended already )
            [/cover] */
            FlsRetVal = Fls_17_Dmu_SuspendErase();
            /* [cover parentID={88FFC93A-1871-45ff-8D28-7E32C6F49E6A}][/cover] */
            if(E_OK == FlsRetVal)
            {
              RetVal = (boolean)TRUE;
              StateDataPtr->FeeEraseSuspendStatus = FEE_ERASE_SUSPENDED;
            }
          }
          else
          {
            RetVal = (boolean)TRUE;
            /* In the case of a suspend request, when previous attempt of
            resume had failed at least once, then the count shall be
            reset back to 1, as it is a new request for suspend. */
            StateDataPtr->FeeEraseSuspendStatus = FEE_ERASE_SUSPENDED;
          }
        }
        #endif
      }
      else
      {
        /* Erase operation is not started or completed*/
        /* [cover parentID={BE745360-1F63-4f35-A107-A743640119D7}][/cover] */
        if(PendBlkWritable == E_OK)
        {
          RetVal = (boolean)TRUE;
        }

      }
    }
  }

  return(RetVal);

}/* End of Fee_lIsWriteInvldAllowedbyGC */


/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lMainGCTransHdlr(void)                      **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function determines and performs the state transition   **
** for the main function when in FEE_MAIN_GC state                            **
*******************************************************************************/
/* [cover parentID={EF8D353C-AB6A-4a20-B50F-4DA55B84B024}][/cover] */
LOCAL_INLINE void Fee_lMainGCTransHdlr(void)
{
  Fee_StateDataType *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* Check if GC is completed */
  /* [cover parentID={D50EDFA6-5C50-4a37-AAF2-5B879722AB8E}][/cover] */
  if((FEE_MAIN_GC == StateDataPtr->FeeMainJob) &&
      (FEE_GC_IDLE == StateDataPtr->FeeGcState))
  {
    StateDataPtr->FeeMainJob = FEE_MAIN_NONE;
  }

  /* Check if the Read request is pending & can be executed */
  else if((boolean)TRUE == Fee_lIsUserReadReqstd(StateDataPtr))
  {
    /* [cover parentID={29D314F4-7094-4cfa-BB66-1687C72B5DC8}][/cover] */
    if(Fee_lIsReadAllowedbyGC() == (boolean)TRUE)
    {
      StateDataPtr->FeeMainJob = FEE_MAIN_READ;
    }
  }
  /* Check if the Write request is pending & can be executed */
  else if(((boolean)TRUE == Fee_lIsUserWriteInvldReqstd(StateDataPtr)) &&
          (FEE_MAIN_GC == StateDataPtr->FeeMainJob))
  {
    /* [cover parentID={D64343A8-A157-4e8d-B8AD-3914A7613FCB}][/cover] */
    if(Fee_lIsWriteInvldAllowedbyGC() == (boolean)TRUE)
    {
      StateDataPtr->FeeMainJob = FEE_MAIN_WRITE;
    }
  }
  #if(FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)
  /* [cover parentID={16D829C0-38AC-4da2-ADC6-C60DFDDD8F23}][/cover] */
  else if(Fee_lIsQsWriteReadAllowedbyGC() == TRUE)
  {
    StateDataPtr->FeeMainJob = FEE_MAIN_QS;
  }
  #endif
  else
  {
    /* dummy for MISRA */
  }


}
#endif
/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lMainNoneTransHdlr(void)                    **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :None                                                  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function determines and performs the state transition   **
** for the main function when in FEE_MAIN_NONE state                          **
*******************************************************************************/
/* [cover parentID={DBF4F12D-A366-43fd-B066-4BB004066247}][/cover] */
LOCAL_INLINE void Fee_lMainNoneTransHdlr(void)
{
  Fee_StateDataType *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* Check if User Read request is registered */
  /* [cover parentID={98AC46DE-C46D-4755-A8CB-70ACB41CC337}][/cover] */
  if( (boolean)TRUE == Fee_lIsUserReadReqstd(StateDataPtr) )
  {

    #if (FEE_CANCELL_ALL_API == STD_ON) && \
        (FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)
    /* Check if there is GC cancelled by cancel all */
    /* [cover parentID={18FBDBAB-7034-4add-8F5F-C61659B6C488}][/cover] */
    if(StateDataPtr->FeeCancelallGCstate == FEE_GC_CANCLD)
    {
      /* Call the Fee_lCancelAllGCrestart to restart the GC*/
      Fee_lCancelAllGCrestart();

      /* Set the FeeCancelallGCstate to FEE_GC_CANCLD_CACHEUPDATE and set main
      state to FEE_MAIN_INITGC */
      StateDataPtr->FeeCancelallGCstate = FEE_GC_CANCLD_CACHEUPDATE;
      StateDataPtr->FeeMainJob = FEE_MAIN_INITGC;

    }
    else
    #endif
    {
      StateDataPtr->FeeMainJob = FEE_MAIN_READ;
    }



  }
  /* Check if User Write, Invalidate request is registered */
  /* [cover parentID={C66BB228-446A-4123-B933-9509B3549DF8}][/cover] */
  else if( (boolean)TRUE == Fee_lIsUserWriteInvldReqstd(StateDataPtr) )
  {
    #if (FEE_CANCELL_ALL_API == STD_ON) && \
    (FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)
    /* Check if there is GC cancelled by cancel all */
    /* [cover parentID={6328E9E6-D61F-4a98-A89E-BD018049F01F}][/cover] */
    if(StateDataPtr->FeeCancelallGCstate == FEE_GC_CANCLD)
    {
      /* Call the Fee_lCancelAllGCrestart to restart the GC*/
      Fee_lCancelAllGCrestart();

      /* Set the FeeCancelallGCstate to FEE_GC_CANCLD_CACHEUPDATE and set main
      state to FEE_MAIN_INITGC */
      StateDataPtr->FeeCancelallGCstate = FEE_GC_CANCLD_CACHEUPDATE;
      StateDataPtr->FeeMainJob = FEE_MAIN_INITGC;

    }
    else
    #endif
    {
      StateDataPtr->FeeMainJob = FEE_MAIN_WRITE;
    }
  }
  #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
  /* [cover parentID={3321F78D-AC96-43d2-8D9D-61F787AEE239}][/cover] */
  else if( StateDataPtr->FeeQsJob != FEE_NO_JOB)
  {
    StateDataPtr->FeeMainJob = FEE_MAIN_QS;
  }
  #if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
  /* [cover parentID={CA771F99-FF6E-4278-99B7-B62042FB1988}][/cover] */
  else if( StateDataPtr->FeeQsEraseSuspend == FEE_SET )
  {
    StateDataPtr->FeeMainJob = FEE_MAIN_QS;
  }
  #endif
  #endif
  else
  {
    /* Fee_MainStateVar will be FEE_MAIN_NONE */
  }
}

/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lMainCacheUpdtTransHdlr(void)               **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :None                                                  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function determines and performs the state transition   **
** for the main function when in FEE_MAIN_CACHEUPDATE state                   **
*******************************************************************************/
/* [cover parentID={3829EAB5-02D8-4257-9893-60F48BF58519}]
Fee_lMainCacheUpdtTransHdlr
[/cover] */
/*[cover parentID={52D9E911-AAEC-41c6-AC79-0FF7CA1D7B99}][/cover]*/
LOCAL_INLINE void Fee_lMainCacheUpdtTransHdlr(void)
{
  Fee_StateDataType *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* Check if User Read request is registered */
  /* [cover parentID={B8099704-4745-47ad-9066-D56847B575AE}]
  Cache state update is complete or idle QS
  [/cover] */
  #if (FEE_DATA_BLOCK_SUPPORTED == FEE_QUASI_STATIC_DATA_ONLY)
  if(StateDataPtr->FeeCacheState == FEE_CACHE_IDLE_QS)
  #else
  if(StateDataPtr->FeeCacheState == FEE_CACHE_UPDATE_COMPLETE)
  #endif
  {
    #if (FEE_DATA_BLOCK_SUPPORTED == FEE_QUASI_STATIC_DATA_ONLY)
    /*[cover parentID={F1A171BB-D8BC-4864-9288-C4CB7139DD13}][/cover]*/
    if( StateDataPtr->FeeQsJob != FEE_NO_JOB)
    {
      StateDataPtr->FeeMainJob = FEE_MAIN_QS;
    }
    else
    {
    StateDataPtr->FeeMainJob = FEE_MAIN_NONE;
    }
    #else
    /*[cover parentID={018F0044-357E-46df-AAAF-D42339FD25A2}][/cover]*/
    if((boolean)TRUE == Fee_lIsUserReadReqstd(StateDataPtr))
    {
      StateDataPtr->FeeMainJob = FEE_MAIN_READ;
    }
    /*[cover parentID={1947C3EB-D512-4d6e-8BCE-6D2F8F3009DB}][/cover]*/
    else if((boolean)TRUE == Fee_lIsUserWriteInvldReqstd(StateDataPtr))
    {
      StateDataPtr->FeeMainJob = FEE_MAIN_WRITE;
    }
    #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
    /*[cover parentID={BA65760E-E551-44e6-A90D-AC7BDA729054}][/cover]*/
    else if( StateDataPtr->FeeQsJob != FEE_NO_JOB)
    {
      StateDataPtr->FeeMainJob = FEE_MAIN_QS;
    }
    #endif
    /*[cover parentID={C77217DA-B54F-4890-8DF9-8D45F23D25A9}][/cover]*/
    else if(StateDataPtr->FeeGcState != FEE_GC_IDLE)
    {
      StateDataPtr->FeeMainJob = FEE_MAIN_GC;
    }
    else
    {
      StateDataPtr->FeeMainJob = FEE_MAIN_NONE;
    }
   #endif
  }
}

/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lMainReadTransHdlr(void)                    **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :None                                                  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function determines and performs the state transition   **
** for the main function when in FEE_MAIN_READ state                          **
*******************************************************************************/
/*[cover parentID={740F470B-F525-4f68-AC5B-6941D5B977E5}][/cover]*/
LOCAL_INLINE void Fee_lMainReadTransHdlr(void)
{
  Fee_StateDataType *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* Check if the Write/Read/Invalidate job is finished */
  /*[cover parentID={F1EB88CB-4D23-4786-B6E8-5AD009152B96}][/cover]*/
  if(StateDataPtr->FeePendReqStatus == FEE_PEND_PREV_NO_REQ)
  {
    #if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
    /* Check if GC job is ongoing/requested */
    /*[cover parentID={91FADC2E-15F1-40e2-BEF8-E1B69F89FE58}][/cover]*/
    if(((boolean)FALSE == Fee_lIsGcTriggeredOnce(StateDataPtr)) &&
        (StateDataPtr->FeeGcState != FEE_GC_IDLE))
    {
      StateDataPtr->FeeMainJob = FEE_MAIN_GC;
    }
    else
    #endif
    {
      StateDataPtr->FeeMainJob = FEE_MAIN_NONE;
    }
  }
  /* Check if user write/invalidate is requested */
  /*[cover parentID={F8CFDB4A-24FA-46ad-B17D-E4DCCC781B93}][/cover]*/
  else if((boolean)TRUE == Fee_lIsUserWriteInvldReqstd(StateDataPtr))
  {
    StateDataPtr->FeeMainJob = FEE_MAIN_WRITE;
  }

  #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
  /* Check if Qs Erase job is requested */
  /*[cover parentID={A481178B-1635-4269-8334-2CB933CFC8D1}][/cover]*/
  else if(StateDataPtr->FeeQsJob == FEE_ERASE_JOB)
  {
    StateDataPtr->FeeMainJob = FEE_MAIN_QS;
  }

  /*Check if QS read is requested*/
  /*[cover parentID={D74B24AC-B13B-42c5-B06E-3BCA2A0A77D5}][/cover]*/
  else if(StateDataPtr->FeePendReqStatus == FEE_REQ_QUASI_READ)
  {
    StateDataPtr->FeeMainJob = FEE_MAIN_QS;
  }

  /*Check if QS write is requested*/
  /*[cover parentID={25E196E0-EA6A-4a32-B3FA-DD479B40E8D6}][/cover]*/
  else if(StateDataPtr->FeePendReqStatus == FEE_REQ_QUASI_WRITE)
  {
    StateDataPtr->FeeMainJob = FEE_MAIN_QS;
  }

  #endif
  else
  {
    /* dummy else */
  }
}

/*CYCLOMATIC_Fee_lMainWriteTransHdlr_JUSTIFICATION:
Fee_lMainWriteTransHdlr has to pass through many states for interrupted read
during write,if it is broken into more functions, the readability will get
affected.
*/
/*******************************************************************************
** Syntax: LOCAL_INLINE void Fee_lMainWriteTransHdlr(void)                    **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :None                                                  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function determines and performs the state transition   **
** for the main function when in FEE_MAIN_WRITE state                         **
*******************************************************************************/
/*[cover parentID={120678FC-72A9-4f06-89EE-47AE12CBC60C}][/cover]*/
LOCAL_INLINE void Fee_lMainWriteTransHdlr(void)
{
  Fee_StateDataType *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;


  /* Check if the Write/Read/Invalidate job is finished */
  /*[cover parentID={87778CAA-8019-46a2-BEEC-14EF9C00EF3F}][/cover]*/
  if(StateDataPtr->FeePendReqStatus == FEE_PEND_PREV_NO_REQ)
  {
    /* Check for !Fee_lIsGcTriggeredOnce() is not required as it is True
    when the main job is WRITE */
    /*[cover parentID={9A30072D-BEC4-43fc-B9D1-5062A448FC9E}][/cover]*/
    if (StateDataPtr->FeeGcState != FEE_GC_IDLE)
    {
      StateDataPtr->FeeMainJob = FEE_MAIN_GC;
    }
    else
    {
      StateDataPtr->FeeMainJob = FEE_MAIN_NONE;
    }
  }
  /*[cover parentID={A00F19AB-0D4D-48db-BF45-3E873F7B7CC0}][/cover]*/
  else if( (StateDataPtr->FeePendReqStatus == FEE_REQ_NORM_WRITE) ||
           (StateDataPtr->FeePendReqStatus == FEE_REQ_IMM_WRITE)
         )
  {

    /* Check for !Fee_lIsGcTriggeredOnce() is not required as it is always
    true when FeePendReqStatus = FEE_REQ_NORM_WRITE / FEE_REQ_IMM_WRITE */
    /*[cover parentID={48AFBC08-E0D5-4f61-9888-9EE1B20F4E6F}][/cover]*/
    if ((StateDataPtr->FeeGcState != FEE_GC_IDLE) &&
        (StateDataPtr->FeeReadLen == 0U))
    {
      StateDataPtr->FeeMainJob = FEE_MAIN_GC;
    }

  }

  #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
  /*Check for QS Write*/
  /*[cover parentID={7CAA6AB5-E9BE-4143-AF38-0FB448586B2A}][/cover]*/
  else if(StateDataPtr->FeePendReqStatus == FEE_REQ_QUASI_WRITE)
  {
    StateDataPtr->FeeMainJob = FEE_MAIN_QS;
  }

  #endif

  /* Check if user read is requested */
  /*[cover parentID={6EFF9E29-0BB8-4748-96BB-7015717C7150}][/cover]*/
  else if((boolean)TRUE == Fee_lIsUserReadReqstd(StateDataPtr))
  {
    StateDataPtr->FeeMainJob = FEE_MAIN_READ;
  }

  #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
  /*Check for QS read*/
  /*[cover parentID={56DFA09C-03B8-454e-9F13-D9FDEFFD35A6}][/cover]*/
  else if(StateDataPtr->FeePendReqStatus == FEE_REQ_QUASI_READ)
  {
    StateDataPtr->FeeMainJob = FEE_MAIN_QS;
  }
  /*[cover parentID={6AB91513-068C-4f06-AF29-D9BD20774664}][/cover]*/
  else if(StateDataPtr->FeePendReqStatus == FEE_REQ_QUASI_ERASE)
  {
    StateDataPtr->FeeMainJob = FEE_MAIN_QS;
  }

  #endif
  else
  {
    /* Remain in FEE_MAIN_WRITE */
    /* i.e.
    FEE_PEND_PREV_WRITE_REQ : Current block write is not yet completed
    */
  }
}

/*******************************************************************************
** Syntax : static void Fee_lDecideMainJob(void)                              **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :None                                                  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function determines and performs the state transition   **
** for the main function                                                      **
*******************************************************************************/
/*[cover parentID={1C5B8136-C85D-45c1-A9F9-612767538334}][/cover]*/
static void Fee_lDecideMainJob(void)
{
  Fee_StateDataType     *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;


  switch(StateDataPtr->FeeMainJob)
  {
    /*[cover parentID={F8DD5DCD-CB04-409d-A95D-B19F9EFACBFF}][/cover]*/
    case FEE_MAIN_INITGC:
    {
      #if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
      /* Check if InitGC activity is ongoing */
      /*[cover parentID={FB39CE14-7038-478a-98A2-79C18112A461}][/cover]*/
      if(StateDataPtr->FeeInitGCState == FEE_INITGC_COMPLETE)
      {
        #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)

        #if ((FEE_CANCELL_ALL_API == STD_ON) && \
        (FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA))
        if(StateDataPtr->FeeCancelallGCstate == FEE_GC_CANCLD_CACHEUPDATE)
        {
          StateDataPtr->FeeMainJob = FEE_MAIN_CACHEUPDATE;
          StateDataPtr->FeeCancelallGCstate = FEE_GC_NOT_CANCLD;
        }
        else
        {
          StateDataPtr->FeeMainJob = FEE_MAIN_INITQS;
        }
        #else
        StateDataPtr->FeeMainJob = FEE_MAIN_INITQS;
        #endif

        #else
        StateDataPtr->FeeMainJob = FEE_MAIN_CACHEUPDATE;
        #endif
      }
      #else
      /* Checking GC activity is not required for QS */
      StateDataPtr->FeeMainJob = FEE_MAIN_INITQS;
      #endif
      break;
    }
    #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
    /*[cover parentID={A03FCFA7-80ED-48b4-8A8E-A274E24C1365}][/cover]*/
    case FEE_MAIN_INITQS:
    {
      /*[cover parentID={4ABAE073-CAB6-49b8-A1FF-D33BC6D7E1E5}][/cover]*/
      if(StateDataPtr->FeeInitQSState == FEE_INITQS_COMPLETE)
      {
        StateDataPtr->FeeMainJob = FEE_MAIN_CACHEUPDATE;
      }
      break;
    }
    #endif
    /*[cover parentID={3DF01A3D-02B4-4dd9-90E2-AD484B10ACA9}][/cover]*/
    case FEE_MAIN_NONE:
    {
      Fee_lMainNoneTransHdlr();
      break;
    }
    /*[cover parentID={576DA2D4-5775-4d6d-890E-2AC0125BD2B5}][/cover]*/
    case FEE_MAIN_CACHEUPDATE:
    {
      /*[cover parentID={34A084E6-3C40-441b-995F-D195B5D7439D}][/cover]*/
      Fee_lMainCacheUpdtTransHdlr();
      break;
    }
    /*[cover parentID={FDDCED83-B51A-4f2f-A10C-ACCC457B676D}][/cover]*/
    case FEE_MAIN_READ:
    {
      Fee_lMainReadTransHdlr();
      break;
    }
    /*[cover parentID={C249F2FD-9CA3-4eb2-B67A-EA32D933291F}][/cover]*/
    case FEE_MAIN_WRITE:
    {
      Fee_lMainWriteTransHdlr();
      break;

    }
    #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
    /*[cover parentID={CA12403F-A5E2-4679-97F2-DE02758FB1BC}][/cover]*/
    case FEE_MAIN_QS:
    {
      Fee_lMainQsTransHdlr();
      break;
    }
    #endif
    #if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
    /*[cover parentID={B13CA5CE-E7F0-4e58-99A9-7A23D570E141}][/cover]*/
    case FEE_MAIN_GC:
    {
      Fee_lMainGCTransHdlr();
      break;
    }
    #endif
    case FEE_MAIN_UNINIT:
    {
      /* Check if InitGC activity is requested */
      /*[cover parentID={B6705956-93AF-47b9-969B-C268EC9F968A}][/cover]*/
      if(StateDataPtr->FeeStatusFlags.FeeStartInitGC == (uint32)FEE_SET )
      {
        StateDataPtr->FeeMainJob = FEE_MAIN_INITGC;
      }
      break;
    }
    default:
    {
      break;
    }
  }
}/*End of Fee_lDecideMainJob */
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lHandleErasePrepDFLASH(void)                **
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
** Description : This function handles the erase operations for DFLASH        **
**               preparation                                                  **
*******************************************************************************/
/* [cover parentID={17A84697-3D49-41a4-9B9E-AB77738D3081}]
Fee_lHandleErasePrepDFLASH
[/cover] */
/* [cover parentID={2DAC004C-9723-481c-9FDE-F1ECC80E6C3A}] */
LOCAL_INLINE void Fee_lHandleErasePrepDFLASH(void)
{
  Fee_StateDataType   *StateDataPtr;
  Fls_17_Dmu_AddressType      DestAddr;
  Std_ReturnType       ReturnValueFls;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  DestAddr = StateDataPtr->FeeCurrSectSrcAddr;
  StateDataPtr->FeeIntrJobStatus = FEE_JOB_REQSTD;
  StateDataPtr->FeeIntrJob = FEE_ERASE_JOB;

  /* erase current sector */
  /*[cover parentID={37BE2996-F3BB-4378-BAE6-15228ADF4CC7}][/cover]*/
  ReturnValueFls = Fls_17_Dmu_Erase(DestAddr,
                                    (Fls_17_Dmu_LengthType)FEE_DFLASH_SECTOR_SIZE);
  /*[cover parentID={2DB9C837-C68E-490c-BB0D-ED6DDE491188}][/cover]*/
  if(ReturnValueFls == E_NOT_OK)
  {
    StateDataPtr->FeeIntrJobStatus = FEE_JOB_IDLE;
    StateDataPtr->FeeIntrJob = FEE_NO_JOB;
    Fee_lHandleInitGcFail();
  }
}

/*******************************************************************************
** Syntax : static void Fee_lHandleWritePrepDFLASH(const uint8 *const SrcPtr) **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  SrcPtr:  Pointer to the buffer with state page data     **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    : None                                                     **
**                                                                            **
** Description : This function handles the write operations for DFLASH        **
**               preparation                                                  **
*******************************************************************************/
/* [cover parentID={F9397328-6B85-4b1d-9735-4462DBD22FE2}]
Fee_lHandleWritePrepDFLASH
[/cover] */
/*[cover parentID={C45F89CD-26B1-4871-B29D-EE9623174069}][/cover]*/
static void Fee_lHandleWritePrepDFLASH(const uint8 *const SrcPtr)
{
  Fee_StateDataType   *StateDataPtr;
  Fls_17_Dmu_AddressType      DestAddr;
  Std_ReturnType       ReturnValueFls = E_NOT_OK;
  uint8                PrepDFlashState;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  DestAddr = StateDataPtr->FeeCurrSectSrcAddr;
  /*[cover parentID={B1B3BA8D-905D-41ad-99D4-28CE38FEF914}][/cover]*/
  while(Fee_lIsUnerasableAddr(DestAddr) == TRUE)
  {

    DestAddr += (FEE_DFLASH_WORDLINE_SIZE);
  }
  StateDataPtr->FeeCurrSectSrcAddr = DestAddr;
  StateDataPtr->FeeIntrJobStatus = FEE_JOB_REQSTD;
  StateDataPtr->FeeIntrJob = FEE_WRITE_JOB;

  PrepDFlashState = StateDataPtr->FeePrepDFLASHState;

  switch (PrepDFlashState)
  {
    /*[cover parentID={6ADFC44A-0253-42d6-95CE-2BF63BBB42AB}][/cover]*/
    case FEE_PREPDF_MARK_S0_ERASED_SP:
    case FEE_PREPDF_MARK_S0_VALID_SP:
    case FEE_PREPDF_MARK_S1_ERASED_SP:
    {
      ReturnValueFls = Fls_17_Dmu_Write(DestAddr, SrcPtr,
                             (Fls_17_Dmu_LengthType)FEE_STATEPAGE_PROGRAM_SIZE);
    }
    break;

    case FEE_PREPDF_MARK_S0_ERASED_M:
    case FEE_PREPDF_MARK_S0_VALID_M:
    case FEE_PREPDF_MARK_S1_ERASED_M:
    {
      DestAddr += FEE_STATEPAGE_DATA_SIZE;
      ReturnValueFls = Fls_17_Dmu_Write(DestAddr, SrcPtr,
                              (Fls_17_Dmu_LengthType)FEE_STATEPAGE_MARKER_SIZE);
    }
    break;
    default:
  {
    break;
  }
  }
  /*[cover parentID={85E5C24D-DE71-4325-B5C8-3A9273F4FB6A}][/cover]*/
  if(ReturnValueFls == E_NOT_OK)
  {
    StateDataPtr->FeeIntrJobStatus = FEE_JOB_IDLE;
    StateDataPtr->FeeIntrJob = FEE_NO_JOB;
    /*[cover parentID={BFDB3D73-E27C-466b-92CE-A3A8F7E8E817}][/cover]*/
    Fee_lHandleInitGcFail();
  }
}/*End of Fee_lHandleWritePrepDFLASH */

/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lIDSM(void)                                 **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function implements the Init Dirty State Machine which  **
** repairs the identified state pages before handing over to the INSM         **
*******************************************************************************/
/* [cover parentID={0BDE2A71-D5BF-447c-8DCF-7A8C8B87E5F8}]
Fee_lIDSM
[/cover] */
/* [cover parentID={D80BE616-6B4A-4e87-B634-2E7E1A7885B6}][/cover] */
LOCAL_INLINE void Fee_lIDSM(void)
{
  Fee_StateDataType     *StateDataPtr;
  Fee_SectorInfoType    *SectorInfoPtr;
  uint8           *ReadWriteBuffPtr = NULL_PTR;
  Fls_17_Dmu_AddressType        DestWriteAddress = (Fls_17_Dmu_AddressType)FEE_RESET;
  uint32                 BankNumber;
  uint32                 WriteLength = FEE_RESET;
  Std_ReturnType         ReturnValueFls = E_OK;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  BankNumber =  StateDataPtr->FeeStatusFlags.FeeCurrSector;
  SectorInfoPtr = &StateDataPtr->FeeSectorInfo[BankNumber];
  /* [cover parentID={74EAB833-CF33-450f-A60F-F7967E60CD6F}][/cover] */
  if(SectorInfoPtr->Status.Dirty == (uint32)FEE_RESET)
  {
    BankNumber = BankNumber ^ FEE_SECTOR1;
    SectorInfoPtr = &StateDataPtr->FeeSectorInfo[BankNumber];
  }

  switch(StateDataPtr->FeeRepairStep)
  {
    /* [cover parentID={346F5328-F00F-41db-877A-8779B86AC327}][/cover] */
    case FEE_PROGRAM_MARKER:
    {
      StateDataPtr->FeeCurrSectSrcAddr = SectorInfoPtr->StatePageAddr;
      /* [cover parentID={4AE9C17A-12E8-45ed-B0EB-301933AA6D94}][/cover] */
      if (StateDataPtr->FeeIntrJobFailCount == FEE_RESET)
      {
        Fee_lClearFeeGcReadWriteBuffer();
        ReadWriteBuffPtr = StateDataPtr->FeeGcReadWriteBuffer;
        (void)Fls_17_Dmu_ReadWordsSync(
        (Fls_17_Dmu_AddressType)StateDataPtr->FeeCurrSectSrcAddr,
        /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for interfacing with
        FLS.FEE is passing parameters to FLS APIs, casting is needed to match with
        the Fls API prototype. ReadWriteBuffPtr is poiniting to FeeGcReadWriteBuffer
        which is part of Fee_StateDataType. FeeGcReadWriteBuffer is so placed to have
        4 byte alignment */
        (uint32 *)ReadWriteBuffPtr,
        (Fls_17_Dmu_LengthType)(FEE_STATEPAGE_DATA_SIZE / FEE_DFLASH_WORD_SIZE));

      }
      Fee_lPrepareMarkerBuffer();

      ReadWriteBuffPtr = &(StateDataPtr->FeeGcReadWriteBuffer
                         [FEE_STATEPAGE_DATA_SIZE]);
      WriteLength = FEE_DFLASH_PAGE_SIZE;
      DestWriteAddress = StateDataPtr->FeeCurrSectSrcAddr +
                         FEE_STATEPAGE_DATA_SIZE;
      break;
    }
    case FEE_PROGRAM_STATEPAGE:
    {
      StateDataPtr->FeeCurrSectSrcAddr = SectorInfoPtr->NextFreeWLAddr;
      ReadWriteBuffPtr = StateDataPtr->FeeGcReadWriteBuffer;
      /* Update the new state page address and the next free WL address */
      SectorInfoPtr->StatePageAddr = StateDataPtr->FeeCurrSectSrcAddr;
      SectorInfoPtr->NextFreeWLAddr =
        Fee_lGetNextWLAddr(StateDataPtr->FeeCurrSectSrcAddr);
      WriteLength = FEE_STATEPAGE_PROGRAM_SIZE;
      DestWriteAddress = StateDataPtr->FeeCurrSectSrcAddr;
      break;
    }
    default:
    {
      break;
    }
  }/* END OF SWITCH */
  StateDataPtr->FeeIntrJob = FEE_WRITE_JOB;
  StateDataPtr->FeeIntrJobStatus = FEE_JOB_REQSTD;
  ReturnValueFls = Fls_17_Dmu_Write(DestWriteAddress,
                                    ReadWriteBuffPtr,
                                    (Fls_17_Dmu_LengthType)WriteLength);
  /* [cover parentID={070CCA49-9EE0-477c-9FF1-3C5770701762}][/cover] */
  if(ReturnValueFls == E_NOT_OK)
  {
    StateDataPtr->FeeIntrJobStatus = FEE_JOB_IDLE;
    StateDataPtr->FeeIntrJob = FEE_NO_JOB;
    /* [cover parentID={553A6C31-9CEA-4368-A12A-4AA2AB474EED}][/cover] */
    Fee_lHandleInitGcFail();
  }
}


/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lINSM(void)                                 **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function implements the Init Normal State Machine which **
** detects the resumption point of the previously interrupted GC              **
*******************************************************************************/
/* [cover parentID={DD28E5F3-C60D-4fe1-AA91-FEDA8F328CBE}]
Fee_lINSM
[/cover] */
/* [cover parentID={26D9835C-70E4-4386-BEC0-83090A325B6D}][/cover] */
LOCAL_INLINE void Fee_lINSM(void)
{
  Fee_StateDataType  *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  switch (StateDataPtr->FeeGcResumeState)
  {
    /* Copy of Sector1 to Sector0 was ongoing */
    /* [cover parentID={9AA085C1-B3D9-418b-A6D1-8E943957F7AB}][/cover] */
    case FEE_INITGC_DATA_COPY_S1_S0:
    {
      StateDataPtr->FeeCurrSectSrcAddr = FEE_DFLASH_BANK1_BASE;
      StateDataPtr->FeeGcSrcAddr = FEE_DFLASH_BANK1_BASE;
      StateDataPtr->FeeGcDestAddr = FEE_DFLASH_BANK0_BASE;
      StateDataPtr->FeeGcState = FEE_GC_INIT_ERASE_PREV_SECTOR;

      break;
    }

    /* Copy of Sector0 to Sector1 was ongoing */
    /* [cover parentID={D0DC4217-A353-4f54-8ABA-4CD993CDBA68}][/cover] */
    case FEE_INITGC_DATA_COPY_S0_S1:
    {
      StateDataPtr->FeeCurrSectSrcAddr = FEE_DFLASH_BANK0_BASE;
      StateDataPtr->FeeGcSrcAddr = FEE_DFLASH_BANK0_BASE;
      StateDataPtr->FeeGcDestAddr = FEE_DFLASH_BANK1_BASE;
      StateDataPtr->FeeGcState = FEE_GC_INIT_ERASE_PREV_SECTOR;

      break;
    }

    /* Erase of Sector0 was ongoing */
    /* [cover parentID={9F64F421-7663-4645-B587-4FE061514367}][/cover] */
    case FEE_INITGC_ERASE_S0:
    {
      StateDataPtr->FeeCurrSectSrcAddr = FEE_DFLASH_BANK1_BASE;
      StateDataPtr->FeeGcSrcAddr = FEE_DFLASH_BANK1_BASE;
      StateDataPtr->FeeGcDestAddr = FEE_DFLASH_BANK0_BASE;
      StateDataPtr->FeeGcState = FEE_GC_ERASE_PREV_SECTOR;

      break;
    }

    /* Erase of Sector1 was ongoing */
    /* [cover parentID={A7D80398-2FA8-407b-B347-8AD0C0A87ACE}][/cover] */
    case FEE_INITGC_ERASE_S1:
    {
      StateDataPtr->FeeCurrSectSrcAddr = FEE_DFLASH_BANK0_BASE;
      StateDataPtr->FeeGcSrcAddr = FEE_DFLASH_BANK0_BASE;
      StateDataPtr->FeeGcDestAddr = FEE_DFLASH_BANK1_BASE;
      StateDataPtr->FeeGcState = FEE_GC_ERASE_PREV_SECTOR;

      break;
    }
    case FEE_INITGC_NORMAL_S1:
    case FEE_INITGC_NORMAL_S0:
    {
      /* Set Garbage Collection state to Idle */
      StateDataPtr->FeeGcState = FEE_GC_IDLE;

      /* Update the FeeCurrSectSrcAddr */
      if(StateDataPtr->FeeStatusFlags.FeeCurrSector == (uint32)FEE_SECTOR0)
      {
        StateDataPtr->FeeCurrSectSrcAddr = FEE_DFLASH_BANK0_BASE;
      }
      else
      {
        StateDataPtr->FeeCurrSectSrcAddr = FEE_DFLASH_BANK1_BASE;
      }

      break;
    }
    default:
    {
      break;
    }
  }/* End Switch */

  /* Mark end of initialization */
  StateDataPtr->FeeInitGCState = FEE_INITGC_COMPLETE;
}


/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lIPrepDFlashSM(void)                        **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function implements the DFlash preparation State        **
** Machine which prepares an empty DFlash                                     **
*******************************************************************************/
/* [cover parentID={1004EDAC-5B40-4685-BB70-EB8A98D46DCA}]
Fee_lIPrepDFlashSM
[/cover] */
/* [cover parentID={73D870B5-E703-4483-BA19-3D8B223518B9}][/cover] */
LOCAL_INLINE void Fee_lIPrepDFlashSM(void)
{
  const Fee_StateDataType  *StateDataPtr;
  const uint8              *BufferPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  switch(StateDataPtr->FeePrepDFLASHState)
  {
    /* [cover parentID={D3C422C1-59EC-4ca5-9EC5-9336314A8733}][/cover] */
    case FEE_PREPDF_ERASE_S0:
    case FEE_PREPDF_ERASE_S1:
    {
      Fee_lHandleErasePrepDFLASH();
      break;
    }
    /* [cover parentID={19CDB8DB-4A7C-49b1-BFCC-95BB7488FB24}][/cover] */
    case FEE_PREPDF_MARK_S0_ERASED_SP:
    {
      /* Step1: Program first 120bytes of state page */
      /* [cover parentID={50DE33D2-938D-4084-8994-BE45DB85D2AC}][/cover] */
      if (StateDataPtr->FeeIntrJobFailCount == FEE_RESET)
      {
        Fee_lPrepareStatePageBuffer(FEE_SECTOR0, FEE_ERASED);
      }
      else
      {
        /* The state page is being re-attempted after one compare failure
           Clear the last 8bytes of GcReadWriteBuffer for comparison of SP */
        Fee_lClearMarkerBuffer();
      }
      /* State page data is prepared in the first 128 pages of RWBuffer */
      BufferPtr = StateDataPtr->FeeGcReadWriteBuffer;
      Fee_lHandleWritePrepDFLASH(BufferPtr);
      break;
    }
    /* [cover parentID={20669E34-0AD9-436b-AE1F-B012AFD21B03}][/cover] */
    case FEE_PREPDF_MARK_S0_VALID_SP:
    {
      /* Step1: Program first 120bytes of state page */
      /* [cover parentID={E8886612-C00D-4f5a-9CA7-96C33A26B1B3}][/cover] */
      if (StateDataPtr->FeeIntrJobFailCount == FEE_RESET)
      {
        Fee_lPrepareStatePageBuffer(FEE_SECTOR0, FEE_VALID);
      }
      else
      {
        /* The state page is being re-attempted after one compare failure
           Clear the last 8bytes of GcReadWriteBuffer for comparison of SP */
        Fee_lClearMarkerBuffer();
      }
      /* State page data is prepared in the first 128 pages of RWBuffer */
      BufferPtr = StateDataPtr->FeeGcReadWriteBuffer;
      Fee_lHandleWritePrepDFLASH(BufferPtr);
      break;
    }
    /* [cover parentID={A20B1E3C-C72C-4304-9BA3-75C9B830E643}][/cover] */
    case FEE_PREPDF_MARK_S1_ERASED_SP:
    {
      /* Step1: Program first 120bytes of state page */
      /* [cover parentID={2B96281B-F722-41e1-929B-7D0CA57E7EED}][/cover] */
      if (StateDataPtr->FeeIntrJobFailCount == FEE_RESET)
      {
        Fee_lPrepareStatePageBuffer(FEE_SECTOR1, FEE_ERASED);
      }
      else
      {
        /* The state page is being re-attempted after one compare failure
           Clear the last 8bytes of GcReadWriteBuffer for comparison of SP */
        Fee_lClearMarkerBuffer();
      }
      /* State page data is prepared in the first 128 pages of RWBuffer */
      BufferPtr = StateDataPtr->FeeGcReadWriteBuffer;
      Fee_lHandleWritePrepDFLASH(BufferPtr);
      break;
    }

    case FEE_PREPDF_MARK_S0_ERASED_M:
    case FEE_PREPDF_MARK_S0_VALID_M:
    case FEE_PREPDF_MARK_S1_ERASED_M:
    {
      /* Step1: Program marker of state page */
      Fee_lPrepareMarkerBuffer();

      BufferPtr = &(StateDataPtr->FeeGcReadWriteBuffer[FEE_STATEPAGE_DATA_SIZE]);

      Fee_lHandleWritePrepDFLASH(BufferPtr);
      break;
    }
    default:
  {
    break;
  }
  }/* END OF SWITCH */
}

/*CYCLOMATIC_Fee_lInitGCDSMTransHandler_JUSTIFICATION:
Fee_lInitGCDSMTransHandler has to pass through many for finding the compare
failures and take the action accordingly.if it is broken into more functions,
the readability will get affected.
*/

/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lInitGCDSMTransHandler(void)                **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function shall handle the transitions required by the   **
** Init Dirty State Machine                                                   **
*******************************************************************************/
/* [cover parentID={3C7A1D9A-651A-4620-A87F-9970082C0112}]
Fee_lInitGCDSMTransHandler
[/cover] */
/* [cover parentID={60575D1D-3C38-45a5-8DD2-EB2D70901CC3}][/cover] */
LOCAL_INLINE void Fee_lInitGCDSMTransHandler(void)
{
  Fee_StateDataType  *StateDataPtr;
  Fee_SectorInfoType *SectorInfoPtr;
  const uint8        *ReadWriteBuffPtr;
  uint32              BankNumber;
  uint32              EndAddr;
  Fls_17_Dmu_AddressType     DestAddr;
  Std_ReturnType      ReturnVal1;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  ReturnVal1   = E_OK;

  DestAddr = (Fls_17_Dmu_AddressType)StateDataPtr->FeeCurrSectSrcAddr;
  /* Get the active sector number */
  BankNumber =  StateDataPtr->FeeStatusFlags.FeeCurrSector;
  SectorInfoPtr = &StateDataPtr->FeeSectorInfo[BankNumber];
  /* Is active sector state page dirty and being repaired?
     If yes - BankNumber = active sector,
     else - Bank Number = other sector */
  /* [cover parentID={B0C5AF5C-EF1C-40a4-B662-A7EA1AF92C4A}][/cover] */
  if(SectorInfoPtr->Status.Dirty == (uint32)FEE_RESET)
  {
    BankNumber = BankNumber ^ FEE_SECTOR1;
    SectorInfoPtr = &StateDataPtr->FeeSectorInfo[BankNumber];
  }
  /* [cover parentID={07313A5B-1D5A-4447-A559-B607A2EDA173}][/cover] */
  switch(StateDataPtr->FeeRepairStep)
  {
    case FEE_PROGRAM_MARKER:
    {
      /*Do compare only if PVER is not set*/
      /* [cover parentID={B9009F0D-519E-4bd6-A108-679C4DA08290}][/cover] */
      if(StateDataPtr->FeeProgVerErr == FEE_RESET)
      {
        ReadWriteBuffPtr = StateDataPtr->FeeGcReadWriteBuffer;
        ReturnVal1 = Fls_17_Dmu_CompareWordsSync(
                       (Fls_17_Dmu_AddressType)DestAddr,
                       /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for
                       interfacing with FLS.FEE is passing parameters to FLS
                       APIs, casting is needed to match with the Fls API
                       prototype. ReadWriteBuffPtr is poiniting to FeeGcReadWriteBuffer
                       which is part of Fee_StateDataType. FeeGcReadWriteBuffer is so placed to have
                       4 byte alignment*/
                       (const uint32 *)ReadWriteBuffPtr,
                       (Fls_17_Dmu_LengthType)
                       (FEE_STATEPAGE_SIZE / FEE_DFLASH_WORD_SIZE));
      }
      /* Compare failed or PVR bit set. Retry the Write operation */
      /* [cover parentID={CDC06D9A-62E8-41eb-973F-D1A4F7E41BB0}][/cover] */
      if((ReturnVal1 == E_NOT_OK) ||
          (StateDataPtr->FeeProgVerErr == FEE_SET))
      {
        /*Reset the FeeProgVerErr flag*/
        StateDataPtr->FeeProgVerErr = FEE_RESET;
        /* Compare failed for the first time */
        /* [cover parentID={3D91AA44-6105-40a9-B676-C05229918446}][/cover] */
        if(StateDataPtr->FeeIntrJobFailCount == FEE_RESET)
        {
          /* Check if there is space in the sector for state page */
          /* [cover parentID={1F503F05-FEA2-4f5f-A277-354AEC0D55A1}][/cover] */
          if(BankNumber == FEE_SECTOR0)
          {
            EndAddr = FEE_DFLASH_BANK0_BASE;
          }
          else
          {
            EndAddr = FEE_DFLASH_BANK1_BASE;
          }
          EndAddr = EndAddr +
                    (FEE_DFLASH_SECTOR_SIZE - FEE_DFLASH_WORDLINE_SIZE);
          if (SectorInfoPtr->NextFreeWLAddr > EndAddr)
          {
            /* No space - skip writing State Page and proceed */
            /* [cover parentID={06FF5DFF-47E9-4902-84A9-772DB245CF89}][/cover] */
            SectorInfoPtr->Status.Dirty = FEE_RESET;
            if ((StateDataPtr->FeeSectorInfo[0].Status.Dirty ==
                 (uint32)FEE_RESET) &&
                (StateDataPtr->FeeSectorInfo[1].Status.Dirty ==
                 (uint32)FEE_RESET))
            {
              /* Go to Init Normal State Machine */
              StateDataPtr->FeeInitGCState = FEE_INITGC_NORMAL;
            }
            else
            {
              /* Other sector state page needs repair -
                 remain in the same state */
            }
          }
          else
          {
            StateDataPtr->FeeIntrJobFailCount++;
            StateDataPtr->FeeRepairStep = FEE_PROGRAM_STATEPAGE;
          }
        }
        /* Compare/write failed twice - enter Fail state*/
        else
        {
          /* [cover parentID={06AD3CC2-7933-4565-A240-290E287C034D}][/cover] */
          Fee_lHandleInitGcFail();
        }
      }
      /* Repair successful */
      else
      {
        StateDataPtr->FeeIntrJobFailCount = FEE_RESET;
        SectorInfoPtr->Status.Dirty = FEE_RESET;
        /* [cover parentID={13137FE8-AAA6-487a-9077-93F999137A47}][/cover] */
        if((StateDataPtr->FeeSectorInfo[0].Status.Dirty
            == (uint32)FEE_RESET) &&
            (StateDataPtr->FeeSectorInfo[1].Status.Dirty
             == (uint32)FEE_RESET))
        {
          /* Go to Init Normal State Machine */
          StateDataPtr->FeeInitGCState = FEE_INITGC_NORMAL;
        }
        else
        {
          /* Other sector state page needs repair -
             remain in the same state */
        }
      }
      break;
    }

    case FEE_PROGRAM_STATEPAGE:
    {

      /*Do compare only if PVER is not set*/
      /* [cover parentID={F309CB83-9C8B-4357-BFAF-D66BD74E6277}][/cover] */
      if(StateDataPtr->FeeProgVerErr == FEE_RESET)
      {
        ReadWriteBuffPtr = StateDataPtr->FeeGcReadWriteBuffer;
        ReturnVal1 = Fls_17_Dmu_CompareWordsSync(
                       (Fls_17_Dmu_AddressType)DestAddr,
                       /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for
                       interfacing with FLS.FEE is passing parameters to FLS
                       APIs, casting is needed to match with the Fls API
                       prototype. ReadWriteBuffPtr is poiniting to FeeGcReadWriteBuffer
                       which is part of Fee_StateDataType. FeeGcReadWriteBuffer is so placed to have
                       4 byte alignment*/
                       (const uint32 *)ReadWriteBuffPtr,
                       (Fls_17_Dmu_LengthType)
                       (FEE_STATEPAGE_DATA_SIZE / FEE_DFLASH_WORD_SIZE));
      }
      /* Check if compare failed twice or write retry failed due to PVER. If
      yes then go to fail state */
      /* [cover parentID={587F79B9-7767-4f6d-9350-8198F440F073}][/cover] */
      if((ReturnVal1 == E_NOT_OK) ||
          ((StateDataPtr->FeeProgVerErr == FEE_SET)))
      {
        /*Reset the FeeProgVerErr flag*/
        StateDataPtr->FeeProgVerErr = FEE_RESET;
        Fee_lHandleInitGcFail();
      }
      else
      {
        StateDataPtr->FeeRepairStep = FEE_PROGRAM_MARKER;
      }
      break;
    }
    default:
    {
      break;
    }
  }/* END OF SWITCH */
}

/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lInitGCPrepDFlsTransHandler(void)           **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function shall handle the transitions required by the   **
** InitGC state machine during preparation of DFlash                          **
*******************************************************************************/
/* [cover parentID={B01B0434-2BE4-4779-97C8-B266F6F21AE5}]
Fee_lInitGCPrepDFlsTransHandler
[/cover] */
/* [cover parentID={AC4200CB-0519-4c0c-B62A-FFC144EF249B}][/cover] */
LOCAL_INLINE void Fee_lInitGCPrepDFlsTransHandler(void)
{
  Fee_StateDataType  *StateDataPtr;
  Fee_SectorInfoType *SectorInfoPtr0;
  Fee_SectorInfoType *SectorInfoPtr1;
  const uint8              *SrcAddr;
  uint32              DestAddr;
  uint8               PrepDFlashState;
  Std_ReturnType      ReturnVal1;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  StateDataPtr->FeeUnErasableWLCountTemp = FEE_RESET;
  StateDataPtr->FeeUnErasableWLAddrTemp[0] = FEE_RESET;
  StateDataPtr->FeeUnErasableWLAddrTemp[1] = FEE_RESET;
  SectorInfoPtr0 = &(StateDataPtr->FeeSectorInfo[0]);
  SectorInfoPtr1 = &(StateDataPtr->FeeSectorInfo[1]);

  PrepDFlashState = StateDataPtr->FeePrepDFLASHState;
  DestAddr = (Fls_17_Dmu_AddressType)(StateDataPtr->FeeCurrSectSrcAddr);
  ReturnVal1 = E_OK;

  /****** CASE FEE_PREPDF_ERASE_S0 ******************/
  /* [cover parentID={F612AD88-4E02-4da4-BD31-F21C61637D62}][/cover] */
  if (PrepDFlashState == FEE_PREPDF_ERASE_S0)
  {
     PrepDFlashState = Fee_lPrepDFlashStateEraseS0();
  }

  /****** CASE FEE_PREPDF_ERASE_S1 ******************/
  /* [cover parentID={F99309D0-A7FC-43b7-B798-CCB278320C75}][/cover] */
  else if (PrepDFlashState == FEE_PREPDF_ERASE_S1)
  {
     PrepDFlashState = Fee_lPrepDFlashStateEraseS1();
  }

  /****** All other state page program cases******************/
  else
  {
    /* [cover parentID={74DB593C-8BAE-4f95-B295-EFB2478CB5AE}][/cover] */
    if(StateDataPtr->FeeProgVerErr == FEE_RESET)
    {
      SrcAddr = StateDataPtr->FeeGcReadWriteBuffer;
      ReturnVal1 = Fls_17_Dmu_CompareWordsSync(
                   (Fls_17_Dmu_AddressType)DestAddr,
                   /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for
                   interfacing with FLS.FEE is passing parameters to FLS APIs,
                   casting is needed to match with the Fls API prototype.
                   SrcAddr is poiniting to FeeGcReadWriteBuffer which is part
                   of Fee_StateDataType. FeeGcReadWriteBuffer is so placed to
                   have 4 byte alignment*/
                   (const uint32 *)SrcAddr,
                   (Fls_17_Dmu_LengthType)
                   (FEE_STATEPAGE_SIZE / FEE_DFLASH_WORD_SIZE));
    }
    /* Compare failed or PVER error is set.*/
    /* [cover parentID={85A5B6BE-FAA2-4066-9B79-CD13AD33FBC0}][/cover] */
    if((ReturnVal1 == E_NOT_OK) || (StateDataPtr->FeeProgVerErr == FEE_SET))
    {
      StateDataPtr->FeeProgVerErr = FEE_RESET;
      /* Compare failed the first time */
      /* [cover parentID={46AA5E96-7BA6-4c39-88BD-DCC314C938BE}][/cover] */
      if(StateDataPtr->FeeIntrJobFailCount == FEE_RESET)
      {
        StateDataPtr->FeeIntrJobFailCount++;
        DestAddr = Fee_lGetNextWLAddr(DestAddr);
        DestAddr = Fee_lGetNextWLAddr(DestAddr);
        StateDataPtr->FeeCurrSectSrcAddr = DestAddr;

        PrepDFlashState = Fee_lPrepDFlashStatepageProgram(PrepDFlashState);
      }
      /* Compare failed/PVER error set twice */
      else
      {
        /* [cover parentID={7D2D003F-2D40-4f6f-9691-A9C26CCEE919}][/cover] */
        Fee_lHandleInitGcFail();
      } /* End of if if(StateDataPtr->FeeIntrJobFailCount == FEE_RESET) */
    }
    /* Compare successful */
    else
    {
      switch (PrepDFlashState)
      {
        /* [cover parentID={41B14E7A-7DC8-4a11-A38A-409E311A7547}][/cover] */
        case FEE_PREPDF_MARK_S0_ERASED_SP:
        {
          PrepDFlashState = FEE_PREPDF_MARK_S0_ERASED_M;
          break;
        }
        /* [cover parentID={16C45286-A527-41b6-AF2B-17F9B402B8A0}][/cover] */
        case FEE_PREPDF_MARK_S0_ERASED_M:
        {
          StateDataPtr->FeeIntrJobFailCount = FEE_RESET;
          DestAddr = Fee_lGetNextWLAddr(DestAddr);
          StateDataPtr->FeeCurrSectSrcAddr = DestAddr;
          PrepDFlashState = FEE_PREPDF_MARK_S0_VALID_SP;
          break;
        }
        /* [cover parentID={26ABAB12-9295-416c-98D9-0D45851E7351}][/cover] */
        case FEE_PREPDF_MARK_S0_VALID_SP:
        {
          PrepDFlashState = FEE_PREPDF_MARK_S0_VALID_M;
          break;
        }
        /* [cover parentID={B9628201-EFF0-437c-BFEC-DE4B7FF809BB}][/cover] */
        case FEE_PREPDF_MARK_S0_VALID_M:
        {
          StateDataPtr->FeeIntrJobFailCount = FEE_RESET;
          SectorInfoPtr0->StatePageAddr = DestAddr;
          DestAddr = Fee_lGetNextWLAddr(DestAddr);
          StateDataPtr->FeeNextFreePageAddr = DestAddr;
          SectorInfoPtr0->NextFreeWLAddr = DestAddr;
          StateDataPtr->FeeCurrSectSrcAddr = FEE_DFLASH_BANK1_BASE;
          PrepDFlashState = FEE_PREPDF_MARK_S1_ERASED_SP;
          break;
        }
        /* [cover parentID={7CCB3F5B-D1D8-4f5b-A362-BAC416358EF3}][/cover] */
        case FEE_PREPDF_MARK_S1_ERASED_SP:
        {
          PrepDFlashState = FEE_PREPDF_MARK_S1_ERASED_M;
          break;
        }


        case FEE_PREPDF_MARK_S1_ERASED_M:
        {
          StateDataPtr->FeeIntrJobFailCount = FEE_RESET;
          SectorInfoPtr1->StatePageAddr = DestAddr;
          DestAddr = Fee_lGetNextWLAddr(DestAddr);
          SectorInfoPtr1->NextFreeWLAddr = DestAddr;
          /* Set Garbage Collection state to Idle */
          StateDataPtr->FeeGcState = FEE_GC_IDLE;
          /* Mark end of initialization */
          StateDataPtr->FeeInitGCState = FEE_INITGC_COMPLETE;
          break;
        }
    default:
      {
        break;
      }
      }/* End of SWITCH */
    }/* End of if ( (ReturnVal1 == E_NOT_OK) || (ReturnVal1 == E_NOT_OK) )*/
  }

  StateDataPtr->FeePrepDFLASHState = PrepDFlashState;
}

/* [cover parentID={9EBA0993-888F-4fda-B392-414EE14D495D}][/cover] */
/*******************************************************************************
** Syntax : static uint8 Fee_lPrepDFlashStatepageProgram(const                **
**            uint8 PrepDFlashStatePrm)                                       **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  PrepDFlashStatePrm   : Flash state paramter             **
**                                                                            **
** Parameters (out):  PrepDFlashState :  Flash state to be prepared           **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function shall handle the transitions required by the   **
** InitGC state machine during preparation of DFlash                          **
*******************************************************************************/
LOCAL_INLINE uint8 Fee_lPrepDFlashStatepageProgram(const uint8 PrepDFlashStatePrm)
{
    uint8 PrepDFlashState;

    PrepDFlashState = PrepDFlashStatePrm;

    switch (PrepDFlashStatePrm)
    {
        /* [cover parentID={2EBC8FAC-F593-4df4-A317-5DAFDA87A300}][/cover] */
        case FEE_PREPDF_MARK_S0_ERASED_SP:
        case FEE_PREPDF_MARK_S0_ERASED_M:
        {
          PrepDFlashState = FEE_PREPDF_MARK_S0_ERASED_SP;
          break;
        }
        /* [cover parentID={0BEA353D-4C72-40bb-B32C-D7BFFD635D22}][/cover] */
        case FEE_PREPDF_MARK_S0_VALID_SP:
        case FEE_PREPDF_MARK_S0_VALID_M:
        {
          PrepDFlashState = FEE_PREPDF_MARK_S0_VALID_SP;
          break;
        }

        /* [cover parentID={6ABF3EFB-ED7E-4ab6-ADF0-4613397ED2A4}][/cover] */
        case FEE_PREPDF_MARK_S1_ERASED_SP:
        case FEE_PREPDF_MARK_S1_ERASED_M:
        {
          PrepDFlashState = FEE_PREPDF_MARK_S1_ERASED_SP;
          break;
        }
        default:
        {
          break;
        }
    }

    return PrepDFlashState;
}

/* [cover parentID={B1E230B1-900E-460f-9C63-610F5841EDC9}][/cover] */
/*******************************************************************************
** Syntax : LOCAL_INLINE uint8 Fee_lPrepDFlashStateEraseS1(void)              **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function shall handle the transitions required by the   **
** InitGC state machine during preparation of DFlash                          **
*******************************************************************************/
LOCAL_INLINE uint8 Fee_lPrepDFlashStateEraseS1(void)
{
    uint8 PrepDFlashState;
    Fee_StateDataType  *StateDataPtr;
    Fee_SectorInfoType *SectorInfoPtr1;
    Std_ReturnType      ReturnVal1;

    StateDataPtr = Fee_CfgPtr->FeeStatePtr;
    PrepDFlashState = FEE_PREPDF_ERASE_S1;
    SectorInfoPtr1 = &(StateDataPtr->FeeSectorInfo[1]);
      /* [cover parentID={38538B0B-5327-480f-BA53-67B74AB3E20F}][/cover] */
    if(StateDataPtr->FeeEraseVerErr == FEE_SET)
    {
      /*Check if the erase is failed 1st time, if yes then incerement the fail
      count to retry the erase operation.*/
    /* [cover parentID={2F127D16-B8D2-485e-B853-B458C48BCE10}][/cover] */
      if(StateDataPtr->FeeIntrJobFailCount != FEE_RESET)
      {
        /*Erase operation is failed 2nd time. Scan the sector for number of
        failed WL. If the number is greater than 2 then raise the illegal
        notification.*/
        ReturnVal1 = Fls_17_Dmu_VerifyErase(
                            (Fls_17_Dmu_AddressType)FEE_DFLASH_BANK1_BASE,
                             &(StateDataPtr->FeeUnErasableWLAddrTemp[0]),
                             &(StateDataPtr->FeeUnErasableWLCountTemp));

        /* [cover parentID={A75968C9-7AC7-4fa9-8C1B-47C2D28BB34E}][/cover] */
        if(ReturnVal1 == E_NOT_OK)
        {
          StateDataPtr->FeeIntrJobFailCount = FEE_RESET;
          Fee_lHandleInitGcFail();
        }
        else
        {
          SectorInfoPtr1->UnerasableWLCount =
          StateDataPtr->FeeUnErasableWLCountTemp;
          SectorInfoPtr1->UnerasableWLAddr[0] =
          StateDataPtr->FeeUnErasableWLAddrTemp[0];
          SectorInfoPtr1->UnerasableWLAddr[1] =
          StateDataPtr->FeeUnErasableWLAddrTemp[1];
          StateDataPtr->FeeCurrSectSrcAddr = FEE_DFLASH_BANK0_BASE;
          PrepDFlashState = FEE_PREPDF_MARK_S0_ERASED_SP;
          StateDataPtr->FeeIntrJobFailCount = FEE_RESET;

        }
      }
      else
      {
        StateDataPtr->FeeIntrJobFailCount++;
      }
      StateDataPtr->FeeEraseVerErr = FEE_RESET;
    }
    else
    {
      SectorInfoPtr1->UnerasableWLCount =StateDataPtr->FeeUnErasableWLCountTemp;
      SectorInfoPtr1->UnerasableWLAddr[0] =
      StateDataPtr->FeeUnErasableWLAddrTemp[0];
      SectorInfoPtr1->UnerasableWLAddr[1] =
      StateDataPtr->FeeUnErasableWLAddrTemp[1];
      StateDataPtr->FeeCurrSectSrcAddr = FEE_DFLASH_BANK0_BASE;
      PrepDFlashState = FEE_PREPDF_MARK_S0_ERASED_SP;
      StateDataPtr->FeeIntrJobFailCount = FEE_RESET;
    }

    return PrepDFlashState;
}

/* [cover parentID={1F5EB6BA-2608-4a65-A622-BD06BC1BB907}][/cover] */
/*******************************************************************************
** Syntax : LOCAL_INLINE uint8 Fee_lPrepDFlashStateEraseS0(void)                    **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function shall handle the transitions required by the   **
** InitGC state machine during preparation of DFlash                          **
*******************************************************************************/
LOCAL_INLINE uint8 Fee_lPrepDFlashStateEraseS0(void)
{
    uint8 PrepDFlashState;
    Fee_StateDataType  *StateDataPtr;
    Fee_SectorInfoType *SectorInfoPtr0;
    Std_ReturnType      ReturnVal1;

    StateDataPtr = Fee_CfgPtr->FeeStatePtr;
    PrepDFlashState = FEE_PREPDF_ERASE_S0;
    SectorInfoPtr0 = &(StateDataPtr->FeeSectorInfo[0]);
  /* [cover parentID={9738B748-7899-4cf0-8813-B57C0B366D04}][/cover] */
    if(StateDataPtr->FeeEraseVerErr == FEE_SET)
    {
      /*Check if the erase is failed 1st time, if yes then incerement the fail
      count to retry the erase operation.*/
    /* [cover parentID={FC6ABF13-68EC-4ac9-97AA-D32B6E35FC5A}][/cover] */
      if(StateDataPtr->FeeIntrJobFailCount != FEE_RESET)
      {
        /*Erase operation is failed 2nd time. Scan the sector for number of
        failed WL. If the number is greater than 2 then raise the illegal
        notification.*/

        ReturnVal1 = Fls_17_Dmu_VerifyErase(
                            (Fls_17_Dmu_AddressType)FEE_DFLASH_BANK0_BASE,
                            &(StateDataPtr->FeeUnErasableWLAddrTemp[0]),
                            &(StateDataPtr->FeeUnErasableWLCountTemp));


        /* [cover parentID={40B43B75-F630-4299-906A-09B1B1CE3F64}][/cover] */
        if(ReturnVal1 == E_NOT_OK)
        {
          StateDataPtr->FeeIntrJobFailCount = FEE_RESET;
          Fee_lHandleInitGcFail();
        }
        else
        {
          SectorInfoPtr0->UnerasableWLCount =
          StateDataPtr->FeeUnErasableWLCountTemp;
          SectorInfoPtr0->UnerasableWLAddr[0] =
          StateDataPtr->FeeUnErasableWLAddrTemp[0];
          SectorInfoPtr0->UnerasableWLAddr[1] =
          StateDataPtr->FeeUnErasableWLAddrTemp[1];
          StateDataPtr->FeeCurrSectSrcAddr = FEE_DFLASH_BANK1_BASE;
          PrepDFlashState = FEE_PREPDF_ERASE_S1;
          StateDataPtr->FeeIntrJobFailCount = FEE_RESET;
        }
      }
      else
      {
        StateDataPtr->FeeIntrJobFailCount++;
      }

      StateDataPtr->FeeEraseVerErr = FEE_RESET;
    }
    else
    {
      SectorInfoPtr0->UnerasableWLCount =
      StateDataPtr->FeeUnErasableWLCountTemp;
      SectorInfoPtr0->UnerasableWLAddr[0] =
      StateDataPtr->FeeUnErasableWLAddrTemp[0];
      SectorInfoPtr0->UnerasableWLAddr[1] =
      StateDataPtr->FeeUnErasableWLAddrTemp[1];
      StateDataPtr->FeeCurrSectSrcAddr = FEE_DFLASH_BANK1_BASE;
      PrepDFlashState = FEE_PREPDF_ERASE_S1;
      StateDataPtr->FeeIntrJobFailCount = FEE_RESET;
    }

    return PrepDFlashState;
}

/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lInitGCTransHandler(void)                   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function shall handle the transitions required by the   **
** InitGC state machine                                                       **
*******************************************************************************/
/* [cover parentID={59E06514-D891-4ce0-9084-6645DC6BF67B}]
Fee_lInitGCTransHandler
[/cover] */
/* [cover parentID={A839D226-A3F5-44d9-A65B-A582CBEAB7DE}][/cover] */
LOCAL_INLINE void Fee_lInitGCTransHandler(void)
{
  Fee_StateDataType  *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /**********************************************************************/
  /*                1.AYSNC STATE MACHINE TRANSITIONS                   */
  /**********************************************************************/

  /* Is the Job finished i.e. Should the State machine Transition be made */
  /* [cover parentID={D03A18C4-30C7-4b67-B404-8C055F62A7DD}][/cover] */
  if(StateDataPtr->FeeIntrJobStatus == FEE_JOB_DONE)
  {
    /* If the Job has failed because of other than PVER/EVER error then go to
    init GC fail state*/
    /* [cover parentID={0A00CF8D-0C81-4a52-9DC6-855D642370C6}][/cover] */
    if((StateDataPtr->FeeIntrJobResult == FEE_JOB_FAIL) &&
        (StateDataPtr->FeeProgVerErr  == FEE_RESET) &&
        (StateDataPtr->FeeEraseVerErr == FEE_RESET))
    {
      Fee_lHandleInitGcFail();
    }
    /* Job has passed */
    else
    {
      /***************** CASE 2: INITGC DIRTY STATE MACHINE ****************/
      /* [cover parentID={DEC2D77F-CFD9-4850-8FCA-41A0B18A5A13}][/cover] */
      if( StateDataPtr->FeeInitGCState == FEE_INITGC_HANDLE_DIRTY)
      {
        Fee_lInitGCDSMTransHandler();
      }/* End of FEE_INITGC_HANDLE_DIRTY */


      /***************** CASE 4: DFLASH PREPARATION STATE MACHINE *********/
      /* [cover parentID={0C9D1A24-DC9D-49d7-BB5B-11B629A7E432}][/cover] */
      if(StateDataPtr->FeeInitGCState == FEE_INITGC_PREPARE_DFLASH)
      {
        Fee_lInitGCPrepDFlsTransHandler();
      } /* END OF IF (PREPARE_DFLASH) */
    }/* END OF JOB PASS check */
    StateDataPtr->FeeIntrJobStatus = FEE_JOB_IDLE;
  }
  else
  {
    /* State Transition not required as no job was requested */
    /* Nothing to do */
  }
}

/*******************************************************************************
** TRACEABILITY: []                                                           **
********************************************************************************
** Syntax : static void Fee_lInitGC(void)                                     **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function shall detect if there was any interruption in  **
** the ongoing Garbage Collection procedure. If yes, then this routine shall  **
** get the DFLASH contents in the normal state.                               **
*******************************************************************************/
/* [cover parentID={3CA9D03E-7534-42a6-AC68-42F7510841A9},
{FB8B1E13-5374-4a91-90FE-0A9A984F338E}]
Fee_lInitGC
[/cover] */
static void Fee_lInitGC(void)
{
  Fee_StateDataType  *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /**********************************************************************/
  /*                1.AYSNC STATE MACHINE TRANSITIONS                   */
  /**********************************************************************/

  Fee_lInitGCTransHandler();

  /**********************************************************************/
  /*                       2.STATE MACHINE EXECUTION                    */
  /**********************************************************************/

  /***************** CASE 1: INITGC INVALID STATE MACHINE ********************/
  /* [cover parentID={674702C3-F543-4ada-B85E-BD04698BA3E9}]
  INITGC INVALID STATE MACHINE
  [/cover] */
  if(StateDataPtr->FeeInitGCState == FEE_INITGC_HANDLE_INVALID)
  {
    /* Check if DFLASH erase is enabled. if enabled go for DFLAS preparation
    with erase of DFLASH. Else go to illegal state  */
    /* [cover parentID={919C00BA-61F4-4864-89AA-1AF91DDA5E3B}][/cover] */
    if(Fee_CfgPtr->FeeEraseAllEnable == (boolean)TRUE)
    {
      StateDataPtr->FeeInitGCState = FEE_INITGC_PREPARE_DFLASH;
      StateDataPtr->FeePrepDFLASHState = FEE_PREPDF_ERASE_S0;
      StateDataPtr->FeeCurrSectSrcAddr = FEE_DFLASH_BANK0_BASE;
      StateDataPtr->FeeStateCount = FEE_RESET;
    }
    else
    { /* [cover parentID={F103A7E1-60A8-41c5-9C2C-B21BC4734F0F}]
      Call the function to raise the init GC production error and illegal notification and set the FeeInitGCState to fail
      [/cover] */
      /*Raise the init GC production error and illegal notification and set the
      FeeInitGCState to fail */
      Fee_lHandleInitGcFail();
    }
  }

  /***************** CASE 2: INITGC VIRGIN STATE MACHINE ********************/
  /* [cover parentID={BC4C2A4C-AD3D-4ef5-8ACD-E63D03087D82}][/cover] */
  if(StateDataPtr->FeeInitGCState == FEE_INITGC_HANDLE_VIRGIN)
  {
      #if (FEE_VIRGIN_FLASH_ILLEGAL_STATE == STD_OFF)
      /*set init gc state to prepare DFlash(NVM area) state. This will bring the
       DFLASH(NVM area) to intial state. */
      StateDataPtr->FeeInitGCState = FEE_INITGC_PREPARE_DFLASH;
      #else
      /*Raise the init GC production error and illegal notification and set the
      FeeInitGCState to fail */
    /* [cover parentID={51EC7038-DC62-4efe-8EF5-052B5EC7D6EF}][/cover] */
      Fee_lHandleInitGcFail();
      #endif
  }

  /***************** CASE 3: INITGC DIRTY STATE MACHINE ********************/
  /* [cover parentID={CCF20CBE-34B4-4a34-B6BE-EAC674ACD651}][/cover] */
  if(StateDataPtr->FeeInitGCState == FEE_INITGC_HANDLE_DIRTY)
  {
    Fee_lIDSM();
  }

  /***************** CASE 4: INITGC NORMAL STATE MACHINE *******************/
  /* [cover parentID={F746FC3D-ADF9-45a8-838B-543346FC2274}][/cover] */
  if(StateDataPtr->FeeInitGCState == FEE_INITGC_NORMAL)
  {
    Fee_lINSM();
  }

  /*********** CASE 5: DFLASH PREPARATION STATE MACHINE ********************/
  /* [cover parentID={854536E0-8BBE-43b1-881A-D2241F4F6F6C}][/cover] */
  if( StateDataPtr->FeeInitGCState == FEE_INITGC_PREPARE_DFLASH)
  {
    Fee_lIPrepDFlashSM();
  }

}/*End of Fee_lInitGC */


/*******************************************************************************
** Syntax : static void Fee_lLastPgHandler(void)                              **
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
** Description : This routine will perform end of job handling activities     **
**    for Write, Invalidate requests                                          **
*******************************************************************************/
/* [cover parentID={FDA14D4D-6413-48bd-814D-A9C01B187D2F}][/cover] */
static void Fee_lLastPgHandler(void)
{
  Fee_StateDataType           *StateDataPtr;
  Fee_LastWrittenBlkInfoType  *LastBlkInfoPtr;
  Fee_CacheType               *BlkPtr;
  const Fee_BlockType         *BlockCfgPtr;
  uint32                       LWBMarkerAddress;
  uint32                       NextFreePageWLAddr;
  uint16                       BlockIndex;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  BlockIndex = Fee_lGetUsrBlockIndex(StateDataPtr->FeeCurrReqBlockNum);
  BlockCfgPtr = &(Fee_CfgPtr->FeeBlockConfigPtr[BlockIndex]);
  BlkPtr = &(StateDataPtr->FeeBlockInfo[BlockIndex]);
  /*****************   UPDATE THE CACHE TABLE *********************/

  /* Push latest copy details of the block into Previous copy */
  /* Update previous copy information */
  BlkPtr->Status.PrevCopyValid = BlkPtr->Status.Valid;
  BlkPtr->Status.PrevCopyConsistent = BlkPtr->Status.Consistent;
  BlkPtr->Status.PrevCopyCopied = BlkPtr->Status.Copied;
  BlkPtr->PrevCopyAddress = BlkPtr->Address;
  BlkPtr->PrevBlkSize = BlkPtr->BlockSize;

  /* Update latest copy information in the cache table */
  BlkPtr->Address = StateDataPtr->FeeBlockStartAddr;
  BlkPtr->Status.Consistent = FEE_SET;

  /* If Invalidate request was ongoing then reset the flag */
  /* [cover parentID={D7989658-7F64-4399-BA5A-B3DC92B392F6}][/cover] */
  if(StateDataPtr->FeeStatusFlags.FeeBlkInvalidStatus == (uint32)FEE_SET )
  {
    BlkPtr->Status.Valid = FEE_RESET;
  }
  else
  {
    BlkPtr->Status.Valid = FEE_SET ;
    BlkPtr->BlockSize = BlockCfgPtr->Size;
  }

  /* if Garbage Collection is pending */
  /* [cover parentID={2DC7321F-AB80-499a-8003-6D1BE706D305}][/cover] */
  if(StateDataPtr->FeeGcState != FEE_GC_IDLE)
  {
    /*Check if the block was copied as part of GC already . If yes then
    copy the status .*/
    /* [cover parentID={240E7FB0-C9DE-441c-AFEC-A34C2EFAE9A5}][/cover] */
    if((StateDataPtr->FeeGcState != FEE_GC_ERASE_PREV_SECTOR) &&
        (StateDataPtr->FeeGcState != FEE_GC_INIT_ERASE_PREV_SECTOR))
    {
      /* [cover parentID={E11D6E09-25D7-4791-B2C2-F50EF1D7093E}][/cover] */
      if(BlkPtr->Status.Copied != FEE_RESET)
      {
        BlkPtr->Status.PrevCopyCopied = FEE_SET ;
      }
      else
      {
        BlkPtr->Status.PrevCopyCopied = FEE_RESET;
      }
      BlkPtr->Status.Copied = FEE_RESET;
      StateDataPtr->FeeStatusFlags.FeeBlkModified = FEE_SET ;
    }
  }

  /* Update Last written block information */
  LWBMarkerAddress = StateDataPtr->FeeNextFreePageAddr - FEE_DFLASH_PAGE_SIZE;
  /* [cover parentID={82F98FC0-DF0B-4ddf-98F6-C3CD7CCF244F}][/cover] */
  NextFreePageWLAddr = Fee_lGetWLBeginning(StateDataPtr->FeeNextFreePageAddr);
  if(((StateDataPtr->FeeBlockStartAddr) < NextFreePageWLAddr) &&
      (LWBMarkerAddress >= NextFreePageWLAddr))
  {
    LastBlkInfoPtr = &(StateDataPtr->FeeLastWrittenBlkInfo);
    LastBlkInfoPtr->BlockNumber = StateDataPtr->FeeCurrReqBlockNum;
    LastBlkInfoPtr->PageCount = StateDataPtr->FeeBlkPageCount;
    LastBlkInfoPtr->Addr = StateDataPtr->FeeBlockStartAddr;
    LastBlkInfoPtr->Status.Consistent = FEE_SET ; /*Consistent = 1 */
  }

  /************** RESET/UPDATE GLOBAL VARIABLES USED *******************/
  StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_NO_REQ;
  StateDataPtr->FeeStatusFlags.FeeBlkInvalidStatus = FEE_RESET;
  StateDataPtr->FeeJobResult = MEMIF_JOB_OK;
  StateDataPtr->FeeUserJobFailCount = FEE_RESET;
  StateDataPtr->FeeBlkPageCount = FEE_RESET;

  /* [cover parentID={2FF25002-3BC0-4b03-9ADE-D9F5FA9DEBFC}][/cover] */
  if(StateDataPtr->FeeGcState != FEE_GC_REQUESTED)
  {
    /* Call user configured job End notification */
    /* [cover parentID={29222515-284A-4876-AFE6-165408589006}][/cover] */
    if ( Fee_CfgPtr->FeeNvmJobEndNotification != NULL_PTR )
    {
      /* [cover parentID={008484B1-69EE-4726-93C3-2E367C5D61FB}]
      Call the notification function
      [/cover] */
      (Fee_CfgPtr->FeeNvmJobEndNotification)();
    }
  }
  else
  {
    /* Call user configured job End notification */
    /* [cover parentID={0D017210-7BF0-4e7d-9552-D778AE29D882}][/cover] */
    if ( Fee_CfgPtr->FeeNvmJobEndNotification != NULL_PTR )
    {
      /* [cover parentID={4D8817D5-A123-46ff-A686-B0FA4DB492AB}]
      Call the notification function
      [/cover] */
      (Fee_CfgPtr->FeeNvmJobEndNotification)();
    }
    StateDataPtr->FeeGCImmBlkWrite = FALSE;
    StateDataPtr->FeeMainJob = FEE_MAIN_GC;
  }

}/* End of Fee_lLastPgHandler */
#endif

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lPrepareInvldReqBuff(                       **
**                                          const uint32 BlockCycleCount,     **
**                                          uint8 * const ReadWriteBuffPtr    **
**                                                    )                       **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  BlockCycleCount : Block cycle count of block to be      **
**                                      written                               **
**                    ReadWriteBuffPtr : Buffer pointer used for invalidate   **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This routine will fill the read/write buffer with data       **
** for invalidation.                                                          **
*******************************************************************************/
/* [cover parentID={100AB608-E42C-4be6-B6E3-97187A4EC311}][/cover] */
LOCAL_INLINE void Fee_lPrepareInvldReqBuff(const uint32 BlockCycleCount,
    uint8 * const ReadWriteBuffPtr)
{
  Fee_StateDataType     *StateDataPtr;
  uint16                 BlockNumber;
  uint32                 NewBlockCycleCount;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  BlockNumber = StateDataPtr->FeePendReqInfo.BlockNumber;
  StateDataPtr->FeeCurrReqBlockNum = BlockNumber;
  NewBlockCycleCount = BlockCycleCount + FEE_ONE;

  /* Compose the write buffer with page ID and other details */
  /* [cover parentID={B8375F4E-0ACD-491b-9949-3A32A5696C26}][/cover] */
  if(StateDataPtr->FeeBlkPageCount == FEE_BLOCK_HDR_PAGE)
  {
    /* First Page write */
    *(ReadWriteBuffPtr)  = FEE_DATA_FIRST_PAGE_ID;
    ReadWriteBuffPtr[1U] = (uint8)(BlockNumber);
    ReadWriteBuffPtr[2U] = (uint8)(BlockNumber >> FEE_EIGHT);
    ReadWriteBuffPtr[3U] = (uint8)(NewBlockCycleCount);
    ReadWriteBuffPtr[4U] = (uint8)(NewBlockCycleCount >> FEE_EIGHT);
    ReadWriteBuffPtr[5U] = (uint8)(NewBlockCycleCount >> FEE_SIXTEEN);
    ReadWriteBuffPtr[6U] = FEE_INVALID_BLOCK_LEN; /* Page length = 1 */
    /* Page length = 1, Valid bit zero */
    ReadWriteBuffPtr[7U] = FEE_INVALID_BLOCK;

    StateDataPtr->FeeBlkPageCount = FEE_SET ;
  }
  else
  {
    *(ReadWriteBuffPtr)  = FEE_DATA_MARKER_PAGE_ID;
    ReadWriteBuffPtr[1U] = FEE_DP_MARKER_BYTE_2;
    ReadWriteBuffPtr[2U] = FEE_DP_MARKER_BYTE_3;
    ReadWriteBuffPtr[3U] = FEE_DP_MARKER_BYTE_4;
    ReadWriteBuffPtr[4U] = (uint8)(BlockNumber);
    ReadWriteBuffPtr[5U] = (uint8)(BlockNumber >> FEE_EIGHT);
    /* Page length = 1, Valid bit zero */
    ReadWriteBuffPtr[6U] = FEE_INVALID_BLOCK_LEN;
    ReadWriteBuffPtr[7U] = FEE_INVALID_BLOCK;

    StateDataPtr->FeeBlkPageCount = FEE_INVALID_BLOCK_PAGES;
  }
  StateDataPtr->FeeReadLen = FEE_DFLASH_PAGE_SIZE;
  StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_COMPARE;
}

/*******************************************************************************
** TRACEABILITY: []                                                           **
**                                                                            **
** Syntax : LOCAL_INLINE void Fee_lPrepareWriteReqBuff                        **
**                                        (                                   **
**                                           const uint32 BlockCycleCount,    **
**                                           uint8 * const ReadWriteBuffPtr   **                                           
**                                           const uint16 BlockSize           **
**                                        )                                   **
** [/cover]                                                                   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  BlockCycleCount : Blk count of block to be written      **
**                    ReadWriteBuffPtr : Buffer Pointer to be filled for write**
**                    BlockSize : Size of the block to be written             **
**                                                                            **
** Parameters (in-out) :None                                                  **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This routine will fill the read write buffer with data       **
*******************************************************************************/
/* [cover parentID={1B0BEFCC-11AD-4518-BD83-ED8489F3E535},
{4CB52C85-7505-48aa-A652-ED1E1CB18AF9}]
Fee_lPrepareWriteReqBuff
[/cover] */
/* [cover parentID={241ED9EB-A2AE-4e9c-A3D8-34A2F24EA38C}][/cover] */
LOCAL_INLINE void Fee_lPrepareWriteReqBuff(const uint32 BlockCycleCount,
    uint8 * const ReadWriteBuffPtr,
    const uint16 BlockSize)
{
  Fee_StateDataType     *StateDataPtr;
  const uint8           *DataBufferPtr;
  Fee_PageType           BlockPages_1;
  uint16                 DataByteCnt;
  uint16                 BlockNumber;
  uint8                  EndOfWLReached;
  uint32                 NewBlockCycleCount;

  EndOfWLReached = FEE_RESET;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  BlockNumber = StateDataPtr->FeePendReqInfo.BlockNumber;
  DataBufferPtr =
    ( const uint8*)StateDataPtr->FeePendReqInfo.DataWriteBufferPtr;

  NewBlockCycleCount = BlockCycleCount + FEE_ONE;
  BlockPages_1 = Fee_lGetDFLASHPages(BlockSize) - FEE_ONE;
  /* Update the block number */
  StateDataPtr->FeeCurrReqBlockNum = BlockNumber;

  /* Compose the write buffer with page ID and other details */
  if(StateDataPtr->FeeBlkPageCount == BlockPages_1)
  {

    *(ReadWriteBuffPtr)  = FEE_DATA_MARKER_PAGE_ID;
    ReadWriteBuffPtr[1U] = FEE_DP_MARKER_BYTE_2;
    ReadWriteBuffPtr[2U] = FEE_DP_MARKER_BYTE_3;
    ReadWriteBuffPtr[3U] = FEE_DP_MARKER_BYTE_4;
    ReadWriteBuffPtr[4U] = (uint8)(BlockNumber);
    ReadWriteBuffPtr[5U] = (uint8)(BlockNumber >> FEE_EIGHT);
    ReadWriteBuffPtr[6U] = (uint8)(BlockPages_1);
    ReadWriteBuffPtr[7U] = (uint8)((BlockPages_1 >> FEE_EIGHT)|(FEE_VALID_BIT));

    StateDataPtr->FeeBlkPageCount++;

    StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_COMPARE;
    StateDataPtr->FeeReadLen = FEE_PAGE1_DATA_OFFSET;
  }
  /* [cover parentID={9459F9E8-6304-41c4-87E7-0C5758577660}][/cover] */
  else
  {
    /* [cover parentID={C1C93D01-5429-4ef5-81B8-A417FB69449B}][/cover] */
    if(StateDataPtr->FeeBlkPageCount == FEE_BLOCK_HDR_PAGE)
    {
      /* First Page write */
      *(ReadWriteBuffPtr)  = FEE_DATA_FIRST_PAGE_ID;
      ReadWriteBuffPtr[1U] = (uint8)(BlockNumber);
      ReadWriteBuffPtr[2U] = (uint8)(BlockNumber >> FEE_EIGHT);
      ReadWriteBuffPtr[3U] = (uint8)(NewBlockCycleCount);
      ReadWriteBuffPtr[4U] = (uint8)(NewBlockCycleCount >> FEE_EIGHT);
      ReadWriteBuffPtr[5U] = (uint8)(NewBlockCycleCount >> FEE_SIXTEEN);
      ReadWriteBuffPtr[6U] = (uint8)(BlockPages_1);
      ReadWriteBuffPtr[7U] = (uint8)((BlockPages_1 >> FEE_EIGHT) |
                                     (FEE_VALID_BIT));

      StateDataPtr->FeeReadLen = FEE_PAGE1_DATA_OFFSET;
     

      StateDataPtr->FeeBlkPageCount++;

      /* [cover parentID={8EDBB843-4460-4734-8BBE-3826D25B4341}][/cover] */
      if(Fee_lIsWLBeginning(StateDataPtr->FeeNextFreePageAddr +
                            StateDataPtr->FeeReadLen) ==
          FEE_NEW_WL_BEGIN)
      {
        EndOfWLReached = FEE_SET ;
        StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_COMPARE;

      }
    }
    /* [cover parentID={A550120B-D0E4-461f-9980-D00046D4B264}][/cover] */
    if (EndOfWLReached == FEE_RESET)
    {
      /* Add data to the write buffer from the user specified pointer */
      DataByteCnt = StateDataPtr->FeeReadLen;
      /* [cover parentID={0BE32163-AEE0-4224-8051-0CE2DDAE6C7B}][/cover] */
      do
      {
        if((StateDataPtr->FeeReadLen & FEE_SEVEN) == FEE_DATA_NEXT_PAGE_ID_POS)
        {
          ReadWriteBuffPtr[StateDataPtr->FeeReadLen] = FEE_DATA_NEXT_PAGE_ID;

          StateDataPtr->FeeBlkPageCount++;
          StateDataPtr->FeeReadLen++;
        }
        else
        {

          ReadWriteBuffPtr[StateDataPtr->FeeReadLen] = *(DataBufferPtr);
          StateDataPtr->FeeReadLen++;

          DataBufferPtr++;
          StateDataPtr->FeeUserWriteBytesCount++;
        }
      }
      while((Fee_lIsWLBeginning(StateDataPtr->FeeNextFreePageAddr +
                               StateDataPtr->FeeReadLen) != FEE_NEW_WL_BEGIN) &&
            (StateDataPtr->FeeUserWriteBytesCount != BlockSize) &&
            ((StateDataPtr->FeeReadLen - DataByteCnt) <
             (uint16)(FEE_WRITE_LEN_MAX)));


      /* If this is the last page being written for the write request */
      /* [cover parentID={B10E65D8-F7EB-4e65-A731-36FA2C239091}][/cover] */
      if(StateDataPtr->FeeUserWriteBytesCount == BlockSize)
      {
        /* If there is a scope for stuff bits(all-one) */
        while((StateDataPtr->FeeReadLen & FEE_SEVEN) != FEE_RESET)
        {
          ReadWriteBuffPtr[StateDataPtr->FeeReadLen] = FEE_RESET;
          StateDataPtr->FeeReadLen++;
        }
        StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_COMPARE;

      }
      /* [cover parentID={FACC9599-C1F2-46b9-B787-AE18A003E515}][/cover] */
      /* If this is beginning of next word line */
      else if(Fee_lIsWLBeginning(StateDataPtr->FeeNextFreePageAddr +
                                 StateDataPtr->FeeReadLen) == FEE_NEW_WL_BEGIN)
      {
        StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_COMPARE;
      }
      else
      {
        /* dummy else to avoid MISRA */
      }

      /* Store the request parameters in last request buffer */
      StateDataPtr->FeePendReqInfo.DataWriteBufferPtr = DataBufferPtr;
    }
  }

} /* End of User Write req handling */

/*******************************************************************************
** Syntax : LOCAL_INLINE Std_ReturnType Fee_lCheckBlkCycleCnt(                **
**                                      const Fee_BlockType *const BlockPtr   **
**                                            const uint32 BlockCycleCount)   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  BlockPtr                                                **
**                    BlockCycleCount                                         **
**                                                                            **
** Parameters (out):  Std_ReturnType                                          **
**                    E_NOT_OK: Block cycle count is reached to maximum limit **
**                    E_OK    : Block cycle count is within limit.            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This routine checks if the block cycle count of the          **
** requested user block has reached the configured maximum                    **
*******************************************************************************/
/* [cover parentID={DAFD79A1-E9B4-4d56-9946-D50BD4A3F8DB}][/cover] */
LOCAL_INLINE Std_ReturnType Fee_lCheckBlkCycleCnt(
  const Fee_BlockType *const BlockPtr,
  const uint32 BlockCycleCount)
{
  Fee_StateDataType     *StateDataPtr;
  uint32                 CycleCountCfg;
  Std_ReturnType         RetVal;

  RetVal = E_OK;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  CycleCountCfg = BlockPtr->CycleCountLimit;

  /* If the cycle count limit is reached then
     report FEE_E_WRITE_CYCLES_EXHAUSTED to Mcal_Wrapper  */
  /* [cover parentID={FC4D2713-95A5-4f66-B103-31690AFDD27E}][/cover] */
  if( (CycleCountCfg != FEE_RESET) && (BlockCycleCount == CycleCountCfg ))
  {
    /* [cover parentID={C316CEB1-87D8-4ba9-8419-77E9B94918D2}]
    production error enabled
    [/cover] */
    #if (FEE_WRITE_CYCLES_DEM_REPORT == FEE_ENABLE_DEM_REPORT)

    /* [cover parentID={80CD3675-1B2C-4a5f-A60A-86B40CA8B370}]
    Report production error to Mcal_Wrapper FEE_E_WRITE_CYCLES_EXHAUSTED
    [/cover] */
    Fee_lReportDemError(FEE_E_WRITE_CYCLES_EXHAUSTED,
                          DEM_EVENT_STATUS_FAILED);
    #endif

    StateDataPtr->FeeJobResult = MEMIF_JOB_FAILED;
    StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_NO_REQ;

    /* Clear the DFLASH access for FEE */
    /* [cover parentID={D0D244C8-F795-490b-A532-D2D5165BC7D8}][/cover] */
    if ( Fee_CfgPtr->FeeNvmJobErrorNotification != NULL_PTR )
    {
      /* [cover parentID={4A35611F-D07E-4e52-9B13-943732082C3C}]
      Call the NVM job error notification function
      [/cover] */
      (Fee_CfgPtr->FeeNvmJobErrorNotification)();
    }
    RetVal = E_NOT_OK;
  }

  return(RetVal);

}

#endif

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lHandleUserWriteReq(                        **
**                                               const uint16 UserBlockIndex) **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  UserBlockIndex: Index of the requested block            **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This routine handles the functionality of FEE_REQ_NORM_WRITE **
** / FEE_REQ_IMM_WRITE state of Write state machine                           **
*******************************************************************************/
/* [cover parentID={3EF461A0-15EA-49ab-BA51-261710510A5F}][/cover] */
LOCAL_INLINE void Fee_lHandleUserWriteReq(const uint16 UserBlockIndex)
{
  Fee_StateDataType           *StateDataPtr;
  const Fee_BlockType         *BlockPtr;
  uint8                       *PendReqStatePtr;
  Fee_LastWrittenBlkInfoType  *LastWrittenBlkPtr;
  uint32                       BlockCycleCount;
  uint32                       DestAddr;
  uint32                       TempAddr;
  uint32                       Index;
  uint16                       Offset;
  Fls_17_Dmu_LengthType               Length;
  Std_ReturnType               ReturnValue;

  BlockCycleCount = FEE_RESET;
  ReturnValue = E_OK;
  Length = FEE_RESET;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  BlockPtr = &(Fee_CfgPtr->FeeBlockConfigPtr[UserBlockIndex]);
  PendReqStatePtr = &(StateDataPtr->FeePendReqStatus);
  LastWrittenBlkPtr = &(StateDataPtr->FeeLastWrittenBlkInfo);
  /* [cover parentID={09EE167F-32F7-4911-BB47-A610CD12C57A}][/cover] */
  if(StateDataPtr->FeeReadLen == (uint16)FEE_RESET)
  {
    /* Read block cycle count */
    /* [cover parentID={48037144-96F6-48c4-82E6-6E37BEA20C5B}][/cover] */
    if (StateDataPtr->FeeBlockInfo[UserBlockIndex].Address != FEE_RESET)
    {
      /* [cover parentID={EA1567CC-22C3-436a-BEE2-5A97E1D3EBC8}]
      Get block cycle count
      [/cover] */
      BlockCycleCount = Fee_lGetBlkCycleCount(UserBlockIndex);
    }
    /* [cover parentID={FFA81AE1-FFA8-4d8a-9867-773A52F73EAF}]
    Check if block cycle count has reached the maximum and update flag status
    [/cover] */
    /* Check if Block Cycle Count has reached the maximum */
    if (StateDataPtr->FeeUserJobFailCount == FEE_RESET)
    {
      ReturnValue = Fee_lCheckBlkCycleCnt(BlockPtr, BlockCycleCount);
    }

    if (ReturnValue != E_NOT_OK) /* If block cycle count not exceeded */
    {
      /* Check if request can be performed */
      /* [cover parentID={56FABAEF-5181-47ea-98F9-29770EE74C82}][/cover] */
      ReturnValue = Fee_lPerformWriteCheck(BlockPtr);
    }
  }
  /* If write is to be started */
  /* [cover parentID={2EFA81C3-4F2B-4750-BA12-669587CAE019}][/cover] */
  if( ReturnValue == E_OK )
  {
    DestAddr = StateDataPtr->FeeNextFreePageAddr;

    /* If it is not a new word line and if previous data is consistent */
    /* [cover parentID={EF544599-84AE-4df9-B72D-4449BECD2B32}][/cover] */
    /* [cover parentID={D539E12A-63F2-4c1f-B256-3A0BEBD12C12}][/cover] */
    if(Fee_lIsWLBeginning(DestAddr) != FEE_NEW_WL_BEGIN)
    {
      /* Read the previous page content to LastWrittenBlkBuff.
      This is used for comparison after the 1st page of current block is
      written */
      TempAddr = Fee_lGetWLBeginning(DestAddr);
      Length = (Fls_17_Dmu_LengthType)(DestAddr & FEE_DFLASH_WORDLINE_SIZE_1);
      Length -= StateDataPtr->FeeReadLen;
      /* [cover parentID={1402DC46-326C-4a34-AE60-D35D526846F4}][/cover] */
      if(Length > FEE_WRITE_LEN_MAX)
      {
        Length = FEE_WRITE_LEN_MAX;
      }
      /* [cover parentID={AA28DC12-FB68-4ece-BCB0-8EDF2704CC23}][/cover] */
      if(Length != (Fls_17_Dmu_LengthType)FEE_ZERO)
      {
        TempAddr += StateDataPtr->FeeReadLen;

        /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for interfacing with
        FLS.FEE is passing parameters to FLS APIs, casting is needed to match
        with the Fls API prototype. FeeLastWrittenBlkBuffer is member of
        Fee_StateDataType structure. FeeLastWrittenBlkBuffer is 4 byte aligned*/
        ReturnValue = Fls_17_Dmu_ReadWordsSync( \
                            (Fls_17_Dmu_AddressType)TempAddr, \
                            (uint32 *)(&(StateDataPtr->FeeLastWrittenBlkBuffer[\
                                StateDataPtr->FeeReadLen])), \
                            Length / FEE_DFLASH_WORD_SIZE);

        /* [cover parentID={4CF0031D-6848-439b-8E8C-89B1D125606A}][/cover] */
        if(ReturnValue == E_NOT_OK)
        {
          StateDataPtr->FeeReadLen = FEE_RESET;
          Length = FEE_RESET;
          /* Since reading of already written data in WL has failed,
          Update the information related to last written block(s)
          and update DestAddr to next WL */
          LastWrittenBlkPtr->Status.Consistent = FEE_RESET;
          LastWrittenBlkPtr->BlockNumber = FEE_RESET;
          StateDataPtr->FeeWLAffectedType = FEE_LWB_NOT_AFFECTED;
          DestAddr = Fee_lGetNextWLAddr(DestAddr);
          while (Fee_lIsUnerasableAddr(DestAddr) == TRUE)
          {

            DestAddr += (FEE_DFLASH_WORDLINE_SIZE);
          }
        }
        else
        {

          Offset = (uint16)(Length);
          Offset += StateDataPtr->FeeReadLen;
          /* Copy FeeLastWrittenBlkBuffer to ReadWriteBuffer
             for WL compare after first page write */
          for(Index = StateDataPtr->FeeReadLen; Index < Offset; Index++)
          {
            StateDataPtr->FeeReadWriteBuffer[Index] =
              StateDataPtr->FeeLastWrittenBlkBuffer[Index];
          } /* End of for(Index =0... */
          StateDataPtr->FeeReadLen += (uint16)(Length);
        } /* end of if(ReturnValue == E_NOT_OK) */
      }
      else
      {
        /*Check if any last written block is spanning across the WL*/
        /* [cover parentID={0C896D5C-0651-4d9b-9022-46C2CA636B24}][/cover] */
        if(LastWrittenBlkPtr->Status.Consistent == FEE_SET)
        {
          StateDataPtr->FeeWLAffectedType = FEE_LWB_ACROSS_WL_AFFECTED;
        }
        else
        {
          StateDataPtr->FeeWLAffectedType = FEE_LWB_WITHIN_WL_AFFECTED;
        }
      }
    } /* end of if ( (Fee_lIsWLBeginning(DestAddr) != FEE_ZERO).. */
    else
    {
      /* This is the beginning of WL and in case WL failure happens, re-write
      the user requested block as there are no blocks written in this WL */
      StateDataPtr->FeeWLAffectedType = FEE_LWB_NOT_AFFECTED;
    }


    /* initialize variables */
    /* [cover parentID={7601EC1D-16D9-45ba-8F67-0BA8C0AC9A96}][/cover] */
    if(Length == (Fls_17_Dmu_LengthType)FEE_ZERO)
    {
      StateDataPtr->FeeReadLen = FEE_RESET;
      StateDataPtr->FeeBlkPageCount = FEE_RESET;
      StateDataPtr->FeeUserWriteBytesCount = FEE_RESET;
      StateDataPtr->FeeBlockStartAddr = DestAddr;
      StateDataPtr->FeeNextFreePageAddr = DestAddr;
      *PendReqStatePtr = FEE_PEND_PREV_WRITE_REQ;
    }
  }
}

/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lHandleUserWriteCompare                     **
**                                             (const uint16 UserBlockIndex)  **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  UserBlockIndex: Index of the requested block            **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This routine handles the functionality of                    **
** FEE_PEND_PREV_COMPARE state of Write state machine                         **
*******************************************************************************/
/* [cover parentID={60E2D8CA-6998-4e0c-8EC0-B8D4D8CDE0FB}][/cover] */
LOCAL_INLINE void Fee_lHandleUserWriteCompare(const uint16 UserBlockIndex)
{
  Fee_StateDataType           *StateDataPtr;
  uint8                       *PendReqStatePtr;
  const Fee_BlockType         *BlockPtr;
  const Fee_LastWrittenBlkInfoType  *LastWrittenBlkPtr;
  uint32                       DestAddr;
  uint32                       TempAddr;
  Fls_17_Dmu_LengthType               CompareLength;
  Fls_17_Dmu_LengthType               TmpCompareLength;
  Std_ReturnType               ReturnValueFls;
  uint8                        Error;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  ReturnValueFls = E_OK;

  BlockPtr = &(Fee_CfgPtr->FeeBlockConfigPtr[UserBlockIndex]);
  LastWrittenBlkPtr = &(StateDataPtr->FeeLastWrittenBlkInfo);
  PendReqStatePtr = &(StateDataPtr->FeePendReqStatus);

  DestAddr = StateDataPtr->FeeNextFreePageAddr;
  /* Compare entire WL content */
  TempAddr = Fee_lGetWLBeginning(DestAddr);
  CompareLength = DestAddr - TempAddr;
  CompareLength += StateDataPtr->FeeLastWriteSize;
  TmpCompareLength = CompareLength;
  CompareLength -=  StateDataPtr->FeeComparedLen;
  /* [cover parentID={0B2024C2-FFF1-448e-9124-3FF903A192CF}][/cover] */
  if(CompareLength > FEE_COMPARE_LEN_MAX)
  {
    /* [cover parentID={1FF97F07-FEAA-44f8-9B78-29163F0AB006}]
    [/cover] */
    CompareLength = FEE_COMPARE_LEN_MAX;
  }

  /* [cover parentID={94D06135-13B2-4475-83AD-1E42EB898E3A}][/cover] */
  if(StateDataPtr->FeeProgVerErr == FEE_RESET)
  {
    /* [cover parentID={AF63CF49-94DA-4341-BB21-D6CA84E6950F}]
    Check if the state page marker reprogrammed correctly by comparing marker
    written in a Flash with the intended marker value
    [/cover] */
    /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for interfacing with
    FLS.FEE is passing parameters to FLS APIs, casting is needed to match with
    the Fls API prototype. FeeReadWriteBuffer is member of
        Fee_StateDataType structure. FeeReadWriteBuffer is 4 byte aligned*/
    ReturnValueFls = Fls_17_Dmu_CompareWordsSync(\
                     (Fls_17_Dmu_AddressType)(TempAddr + \
                         StateDataPtr->FeeComparedLen), \
                     (uint32 *)(&(StateDataPtr->FeeReadWriteBuffer\
                                  [StateDataPtr->FeeComparedLen])), \
                     (Fls_17_Dmu_LengthType)\
                     (CompareLength / FEE_DFLASH_WORD_SIZE));

    StateDataPtr->FeeComparedLen += (uint16)CompareLength;
  }
  /* Compare failed or PVER error set */
  /* [cover parentID={1F44BF10-7E64-4a0c-99BD-F10D029A579A}][/cover] */
  if((ReturnValueFls == E_NOT_OK) ||
      (StateDataPtr->FeeProgVerErr == FEE_SET))
  {
    StateDataPtr->FeeComparedLen = FEE_RESET;
    /*Reset the FeeProgVerErr flag*/
    StateDataPtr->FeeProgVerErr = FEE_RESET;
    /* Compare failed /PVER error set  first time */
    /* [cover parentID={FFFD9497-B22F-4607-93D3-F2DCBBEA5DA2}][/cover] */
    if(StateDataPtr->FeeUserJobFailCount == FEE_RESET)
    {
      StateDataPtr->FeeUserJobFailCount++;
      StateDataPtr->FeeWriteAffectedAddr = StateDataPtr->FeeBlockStartAddr;
      /*Switch to next to next free WL*/
      TempAddr  = Fee_lGetNextWLAddr(DestAddr);
      TempAddr += FEE_DFLASH_WORDLINE_SIZE;
      StateDataPtr->FeeNextFreePageAddr = TempAddr;
      /* Point to the start of the user data buffer to re-write user block */
      /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
            array indexing used for FEE application buffers.
            Pointers are accessing the correct memory range locations.
            The access range is within the boundaries of the buffer. */
      StateDataPtr->FeePendReqInfo.DataWriteBufferPtr -=
        StateDataPtr->FeeUserWriteBytesCount;
      /* Last Written Block affected? */
      /* [cover parentID={C6CD376B-B9A9-4602-AA46-B82AB052C42D}][/cover] */
      if((Fee_lIsBlockAcrossWLLatest() == TRUE) &&
         (StateDataPtr->FeeWLAffectedType == FEE_LWB_ACROSS_WL_AFFECTED))
      {
        /* One of the affected block spanning across the WL is the latest copy
        of that block, Hence update the block info with the
        last written block info*/
        StateDataPtr->FeeCurrSectSrcAddr = LastWrittenBlkPtr->Addr;
        StateDataPtr->FeeCurrReqBlockNum = LastWrittenBlkPtr->BlockNumber;
        /* Initialize variables for next write operation */
        StateDataPtr->FeeBlkPageCount = FEE_RESET;
        StateDataPtr->FeeBlockStartAddr = TempAddr;
        /* Move to Internal read */
        *PendReqStatePtr = FEE_PEND_INTR_READ;
      }
      /* [cover parentID={3A817C7F-7285-4849-8652-0DC1A7A3426E}][/cover] */
      else if((Fee_lIsLastWrittenWLAffected(FEE_ZERO) == (boolean)TRUE)&&
             (StateDataPtr->FeeWLAffectedType == FEE_LWB_WITHIN_WL_AFFECTED))
      {
        /* None of the affected block is spanning across the WL */
        StateDataPtr->FeeBlkPageCount = FEE_RESET;
        StateDataPtr->FeeBlockStartAddr = TempAddr;
        /* Move to Internal read */
        *PendReqStatePtr = FEE_PEND_INTR_READ;
      }
      else
      {
        /* No blocks are are affected,re-write the current requested
        block */
        Fee_lRegisterWriteRequest(
          StateDataPtr->FeePendReqInfo.DataWriteBufferPtr,
          BlockPtr);
      }
    }
    /* Compare failed / PVER error set twice */
    else
    {
      /* Update Next Free Page Address to next to next free WL*/
      StateDataPtr->FeeNextFreePageAddr  = Fee_lGetNextWLAddr(DestAddr);
      StateDataPtr->FeeNextFreePageAddr += FEE_DFLASH_WORDLINE_SIZE;

      /* Handle job failure: Raise production and Job error notification */
      /* [cover parentID={1DFD1B0A-3A7C-4f88-9DD2-5F9D468E6500}][/cover] */
      if(StateDataPtr->FeeStatusFlags.FeeBlkInvalidStatus
          == (uint32)FEE_SET )
      {
        StateDataPtr->FeeStatusFlags.FeeBlkInvalidStatus = FEE_RESET;
        Error = FEE_INVALIDATE;
      }
      else
      {
        Error = FEE_WRITE;
      }
      Fee_lHandleUsrJobFailure(Error); /* production & Job Error Notification */
    }
  }
  /* Compare Successful */
  else
  {
    /* [cover parentID={98068028-7246-443d-ABEF-98342E2E3F2E}][/cover] */
    if(StateDataPtr->FeeComparedLen == TmpCompareLength)
    {
      StateDataPtr->FeeComparedLen = FEE_RESET;
      StateDataPtr->FeeNextFreePageAddr += StateDataPtr->FeeLastWriteSize;
      /* Is it Invalidate request? */
      /* [cover parentID={B3FAAE67-8063-464a-AD95-D09B1D4CA590}][/cover] */
      if((StateDataPtr->FeeStatusFlags.FeeBlkInvalidStatus
          == (uint32)FEE_SET ) &&
          (StateDataPtr->FeeBlkPageCount == FEE_INVALID_BLOCK_PAGES))
      {
        Fee_lLastPgHandler();
      }
      /* Write request - All pages written? */
      /* [cover parentID={E185BD07-9EEE-4ac8-8B25-143F6AF9E627}][/cover] */
      else if(StateDataPtr->FeeBlkPageCount ==
              Fee_lGetDFLASHPages((uint16)(BlockPtr->Size)))
      {
        Fee_lLastPgHandler();
      }
      else
      {
        *PendReqStatePtr = FEE_PEND_PREV_WRITE_REQ;
      }
    }
  }
}

/*******************************************************************************
** Syntax : static boolean Fee_lIsLastWrittenWLAffected(                      **
**                                                const uint16 StartOffset)   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  StartOffset - Offset                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  boolean                                                 **
**                                                                            **
** Description : This function checks if the last written word-line is        **
**               affected                                                     **
*******************************************************************************/
/* [cover parentID={9AC1A68D-AA73-4b65-B7DE-72EBC2DCB4DC}][/cover] */
static boolean Fee_lIsLastWrittenWLAffected(const uint16 StartOffset)
{
  const Fee_StateDataType  *StateDataPtr;
  const uint8              *LWBBufferPtr;
  uint32              WLAddr;
  uint16              EndOffset;
  uint16              BlockNumber;
  boolean             RetVal;
  uint16              NewStartOffset;

  RetVal = (boolean)FALSE;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  LWBBufferPtr = &(StateDataPtr->FeeLastWrittenBlkBuffer[0]);
  EndOffset = (uint16)((StateDataPtr->FeeWriteAffectedAddr) &
                       FEE_DFLASH_WORDLINE_SIZE_1);
  NewStartOffset = (uint16)StartOffset;

  /* Check if any block header is present in the last written word-line */
  /* [cover parentID={FBBB244F-D261-47a4-A492-AD4A20557DA9}][/cover] */
  if(EndOffset > (uint16)FEE_DFLASH_PAGE_SIZE)
  {
    WLAddr = Fee_lGetWLBeginning(StateDataPtr->FeeWriteAffectedAddr);
    EndOffset -= FEE_DFLASH_PAGE_SIZE;
    do
    {
      /* if any block header is found */
      /* [cover parentID={DCFD33BF-980B-4e2a-BEF8-B4A111204339}][/cover] */
      if(LWBBufferPtr[NewStartOffset] == (uint8)FEE_DATA_FIRST_PAGE_ID)
      {

        BlockNumber = ((uint16)
        (((uint16)LWBBufferPtr[NewStartOffset + FEE_BLOCK_NUM_MSB_POS]) <<
            FEE_EIGHT) |
            ((uint16)LWBBufferPtr[NewStartOffset + FEE_BLOCK_NUM_LSB_POS]));
        /* check if the block and its address is in cache table */
        /* [cover parentID={104D397B-058A-49d1-9EF6-D0BF5277A1C0}][/cover] */
        RetVal = Fee_lIsBlockAffected(BlockNumber, (WLAddr + NewStartOffset));
      }
      NewStartOffset += FEE_DFLASH_PAGE_SIZE;
    } while((NewStartOffset < EndOffset) && (RetVal == (boolean)FALSE));
    /* [cover parentID={4E8AF4C6-5EB7-4835-A292-7692F1CC0D1C}][/cover] */
  }

  return(RetVal);
}

/*******************************************************************************
** Syntax : LOCAL_INLINE boolean Fee_lIsBlockAffected(                        **
**                                                  const uint16 BlockNumber, **
**                                                  const uint32 BlockAddr)   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  BlockNumber - Block Number                              **
**                    BlockAddr   - Block Address                             **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  boolean                                                 **
**                  TRUE : Block is affected due to write operation fail.     **
**                  Block entry is available in cache                         **
**                  FALSE: Block is not affected due to write operation fail. **
**                  Block entry is not available in cache                     **
** Description : This function checks if the block is affected                **
**                                                                            **
*******************************************************************************/
/* [cover parentID={D97DA96B-C386-49c8-91E4-679F4F951946}][/cover] */
LOCAL_INLINE boolean Fee_lIsBlockAffected(const uint16 BlockNumber,
    const uint32 BlockAddr)
{
  Fee_StateDataType     *StateDataPtr;
  const Fee_CacheType         *CachePtr;
  const Fee_CacheType         *UnconfigBlockPtr;
  uint16 TempIndex;
  uint16 BlockIndex;
  boolean RetVal;

  RetVal = (boolean)FALSE;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  /* [cover parentID={E1AA4FAA-1E3A-4b95-B8E4-B2A920B2FA7C}][/cover] */
  BlockIndex = Fee_lGetUsrBlockIndex(BlockNumber);
  /* [cover parentID={A7C56250-157B-4954-91FA-89BDF1E346DA}][/cover] */
  if(BlockIndex == FEE_LOG_BLOCK_NOT_FOUND)
  {
    /* un-configured block */
    TempIndex = FEE_RESET;

    UnconfigBlockPtr = &(StateDataPtr->FeeBlockInfo[Fee_CfgPtr->FeeBlkCnt]);
    /* [cover parentID={26CC45A1-CADA-4d0b-9894-1C75716D6179}][/cover] */
    while((TempIndex < (StateDataPtr->FeeUnConfigBlockCount)) &&
          (RetVal == (boolean)FALSE))
    {

      /* check if the block and its address is in cache table */
      /* [cover parentID={696835D2-E215-4ac4-B741-4CD8BAE896D1}][/cover] */
      if((UnconfigBlockPtr->BlockNumber == BlockNumber) &&
          (UnconfigBlockPtr->Address == BlockAddr))
      {
        RetVal = (boolean)TRUE;
      }
      else
      {
        TempIndex++;
      }

      UnconfigBlockPtr++;
    }
  }
  else
  {
    CachePtr = &(StateDataPtr->FeeBlockInfo[BlockIndex]);
    /* check if the block and its address is in cache table */
    /* [cover parentID={007BA1B0-DA96-4d3c-842E-CC9411AAD1EA}][/cover] */
    if(CachePtr->Address == BlockAddr)
    {
      RetVal = (boolean)TRUE;
    }
  }
  /* [cover parentID={85FB9E05-1C30-466d-A479-0C9458A4F427}][/cover] */
  if(RetVal == (boolean)TRUE)
  {
    /* if the block and its address exists in cache table then, update the
       current request */
    StateDataPtr->FeeCurrReqBlockNum = BlockNumber;
    StateDataPtr->FeeCurrSectSrcAddr = BlockAddr;
  }

  return(RetVal);
}

/*******************************************************************************
** Syntax : static boolean Fee_lIsBlockAcrossWLLatest(void)                   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  boolean                                                 **
**                                                                            **
** Description :This function checks if the block across the WL is the latest **
**              TRUE: Block is latest                                         **
**              FALSE: Block is not latest                                    **
*******************************************************************************/
/* [cover parentID={19AF252B-ECEE-427e-AF8D-675C127FF157}][/cover] */
static boolean Fee_lIsBlockAcrossWLLatest(void)
{
  Fee_StateDataType  *StateDataPtr;
  boolean             RetVal;
  uint16              BlockIndex;
  Fee_LastWrittenBlkInfoType  *LastWrittenBlkPtr;
  const Fee_CacheType         *ConfigBlockPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  LastWrittenBlkPtr = &(StateDataPtr->FeeLastWrittenBlkInfo);

  BlockIndex = Fee_lGetUsrBlockIndex(LastWrittenBlkPtr->BlockNumber);
  /* [cover parentID={5BAB2683-6F6B-44f8-BE25-45C138E1FE96}][/cover] */
  if(BlockIndex == FEE_LOG_BLOCK_NOT_FOUND)
  {
    RetVal = (boolean)TRUE;
  }
  else
  {
    ConfigBlockPtr= &(StateDataPtr->FeeBlockInfo[BlockIndex]);
    /* [cover parentID={FFA5A430-90AD-4b30-9C28-421CB5606E7A}][/cover] */
    if((ConfigBlockPtr->Address)==(LastWrittenBlkPtr->Addr))
    {
      RetVal = (boolean)TRUE;
    }
    else
    {
      LastWrittenBlkPtr->Status.Consistent = FEE_RESET;
      LastWrittenBlkPtr->BlockNumber = FEE_RESET;
      StateDataPtr->FeeWLAffectedType = FEE_LWB_WITHIN_WL_AFFECTED;
      RetVal = (boolean)FALSE;
    }

  }
  return(RetVal);
}

#endif

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/*******************************************************************************
** TRACEABILITY: []                                                           **
**                                                                            **
** Syntax : static void Fee_lHandleUserWrite(const uint16 UserBlockIndex)     **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  UserBlockIndex: Index of the requested block            **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This routine handles the functionality of                    **
** FEE_PEND_PREV_WRITE_REQ state of Write state machine                       **
*******************************************************************************/
/* [cover parentID={77B16520-BE1D-4f0a-B22A-954EE6B5E82F}]
Fee_lHandleUserWrite
[/cover] */
/* [cover parentID={7064F609-BBC5-40b9-A486-D666C66CEDC4}][/cover] */
static void Fee_lHandleUserWrite(const uint16 UserBlockIndex)
{
  Fee_StateDataType     *StateDataPtr;
  const Fee_BlockType   *BlockPtr;
  uint8                 *ReadWriteBuffPtr;
  uint32                 DestAddr;
  uint32                 BlockCycleCount;
  uint16                 BlockSize;
  uint16                 Offset;
  Std_ReturnType         RetVal;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* [cover parentID={77B16520-BE1D-4f0a-B22A-954EE6B5E82F}][/cover] */
  BlockPtr = &(Fee_CfgPtr->FeeBlockConfigPtr[UserBlockIndex]);
  BlockSize = (uint16)BlockPtr->Size;
  BlockCycleCount = FEE_RESET;

  /* Read block cycle count */
  /* [cover parentID={CD119A8A-568E-4c37-9D51-1FE08AE06DFD}][/cover] */
  if (StateDataPtr->FeeBlockInfo[UserBlockIndex].Address != FEE_RESET)
  {
    BlockCycleCount = Fee_lGetBlkCycleCount(UserBlockIndex);
  }

  DestAddr = StateDataPtr->FeeNextFreePageAddr;
  Offset = (uint16) (DestAddr & (uint32)FEE_DFLASH_WORDLINE_SIZE_1);
  /* [cover parentID={288F1D24-BD97-4818-8B98-8A1463EC6A07}][/cover] */
  if (Offset == FEE_ZERO)
  {

    /* Check against unersable WL*/
    /* [cover parentID={D6A81D1C-580D-4e8b-8927-6BB04A1AED35}][/cover] */
    while (Fee_lIsUnerasableAddr(DestAddr) == TRUE)
    { /* [cover parentID={F6EC2232-5C32-4d13-9D94-D839BCCCF265}]
         Add WL size to next free page address and assign it to destination address
        [/cover] */
      /* [cover parentID={F6EC2232-5C32-4d13-9D94-D839BCCCF265}][/cover] */
      DestAddr = Fee_lGetNextWLAddr(DestAddr);
    }
    StateDataPtr->FeeNextFreePageAddr = DestAddr;
    StateDataPtr->FeeLastWrittenBlkInfo.BlockNumber = FEE_RESET;
    StateDataPtr->FeeLastWrittenBlkInfo.Status.Consistent = FEE_RESET;
    StateDataPtr->FeeWLAffectedType = FEE_LWB_NOT_AFFECTED;
  }

  ReadWriteBuffPtr = &(StateDataPtr->FeeReadWriteBuffer[Offset]);

  /* if block invalidation is ongoing */
  /* [cover parentID={CFB6232C-7A08-4c47-BFA2-B11370825D49}][/cover] */
  if(StateDataPtr->FeeStatusFlags.FeeBlkInvalidStatus == (uint32)FEE_SET )
  {
    Fee_lPrepareInvldReqBuff(BlockCycleCount, ReadWriteBuffPtr);
  }
  else
  {
    Fee_lPrepareWriteReqBuff(BlockCycleCount, ReadWriteBuffPtr,BlockSize);
  }
  /* [cover parentID={0C445E85-939A-49ff-A4FB-4F2767D3B428}][/cover] */
  if(StateDataPtr->FeePendReqStatus == FEE_PEND_PREV_COMPARE)
  {

    StateDataPtr->FeeLastWriteSize = ((Fls_17_Dmu_LengthType)
                                      StateDataPtr->FeeReadLen);

    StateDataPtr->FeeUserJobStatus = FEE_JOB_REQSTD;

    /* Call Fls_17_Dmu_Write to write data in the DFLASH */
    RetVal = Fls_17_Dmu_Write((Fls_17_Dmu_AddressType)DestAddr,
                              (ReadWriteBuffPtr),
                              (Fls_17_Dmu_LengthType)(
                                StateDataPtr->FeeLastWriteSize));
    StateDataPtr->FeeReadLen = FEE_RESET;
    /* DET from FLS is not expected here */
    /* Hence, only check for Flash Sequence Error, Protection Error */
    /* In case of error, Fee_JobErrorNotification will be called */
    /* which would un-necessarily update FeeNextFreePageAddr */
    /* Hence the below code reverts FeeNextFreePageAddr back to its */
    /* original value */
    /* [cover parentID={E413F536-527C-4578-9C0E-3F31DCE04569}][/cover] */
    if(RetVal == E_NOT_OK)
    {
      if(StateDataPtr->FeeStatusFlags.FeeBlkInvalidStatus == (uint32)FEE_SET )
      {
        Fee_lHandleUsrJobFailure(FEE_INVALIDATE);
      }
      else
      {
        Fee_lHandleUsrJobFailure(FEE_WRITE);
      }
    }
  }
}

/*CYCLOMATIC_Fee_lHandleIntrRead_JUSTIFICATION:
Fee_lHandleIntrRead has to pass through many states for interrupted read during
write,if it is broken into more functions, the readability will get affected.
*/
/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lHandleIntrRead(void)                       **
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
** Description : This routine handles the functionality of                    **
** FEE_PEND_INTR_READ state of Write state machine                            **
*******************************************************************************/
/* [cover parentID={50715C99-90C8-455f-B489-28C878A12B84}]
Fee_lHandleIntrRead
[/cover] */
/* [cover parentID={D470C7A9-E5BC-4cd5-BAFE-96B6CC76808D}][/cover]*/
LOCAL_INLINE void Fee_lHandleIntrRead(void)
{
  /* [cover parentID={50715C99-90C8-455f-B489-28C878A12B84}]*/
  Fee_StateDataType  *StateDataPtr;
  uint8              *ReadWriteBuffPtr;
  const uint8              *LWBBufferPtr;
  uint32              SrcAddr;
  uint32              AffectedWLAddr;
  uint32              SrcAddrNextWLAddr;
  uint16              Offset;
  uint16              ReadLength;
  uint16              ReadLengthInWL;
  uint16              TempIndex;
  uint16              RemainingPageCount;
  uint16              LWBPageCount;
  uint16              ReadLengthMax;
  Std_ReturnType      ReturnValueFls;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  AffectedWLAddr = Fee_lGetWLBeginning(StateDataPtr->FeeWriteAffectedAddr);
  SrcAddr = StateDataPtr->FeeCurrSectSrcAddr;
  Offset = (uint16)((StateDataPtr->FeeNextFreePageAddr) &
                    (uint32)FEE_DFLASH_WORDLINE_SIZE_1);
  /* [cover parentID={D3BA665A-A577-40ce-B011-A18985F7BCF4}][/cover]*/
  if (Offset == FEE_ZERO)
  {
    Fee_lClearFeeReadWriteBuffer();
  }

  ReadWriteBuffPtr = &(StateDataPtr->FeeReadWriteBuffer[Offset]);
  ReadLengthMax = (uint16)FEE_DFLASH_WORDLINE_SIZE - Offset;

  /* if block(s) across the last written word line is affected */
  /* [cover parentID={D11C14B4-2265-49d6-837A-D2B97AEAAD52}][/cover]*/
  if(StateDataPtr->FeeWLAffectedType == FEE_LWB_ACROSS_WL_AFFECTED)
  {
    /* if current address is within the last written word line */
    /* [cover parentID={7C43E42E-08B7-447c-B421-860966553A99}][/cover]*/
    if(SrcAddr >= AffectedWLAddr)
    {
      Offset = (uint16)(SrcAddr & (uint32)FEE_DFLASH_WORDLINE_SIZE_1);
      LWBBufferPtr = &(StateDataPtr->FeeLastWrittenBlkBuffer[0]);
      LWBPageCount = (uint16)(StateDataPtr->FeeLastWrittenBlkInfo.PageCount);
      RemainingPageCount = LWBPageCount - (uint16)StateDataPtr->FeeBlkPageCount;
    /* [cover parentID={7E6733E4-D5A0-4255-BA60-86DF60377549}][/cover]*/
      if(RemainingPageCount == FEE_ONE)
      {
        /* After marker write, change affected type to within word line */
        ReadLength = FEE_DFLASH_PAGE_SIZE;
        StateDataPtr->FeeWLAffectedType = FEE_LWB_WITHIN_WL_AFFECTED;
      }
      else
      {
        ReadLength = ((RemainingPageCount - FEE_ONE) << FEE_PAGE_TO_BYTE);
        /* [cover parentID={9BAAA7EA-33D1-465c-AA46-A735B9713C70}][/cover]*/
        if(ReadLengthMax < ReadLength)
        {
          ReadLength = ReadLengthMax;
        }
      }
      for(TempIndex = FEE_RESET; TempIndex < ReadLength; TempIndex++)
      {
        /* copy from last written block buffer to read-write buffer */

        ReadWriteBuffPtr[TempIndex] = LWBBufferPtr[TempIndex + Offset];
      }
      StateDataPtr->FeeCurrSectSrcAddr += ReadLength;
      StateDataPtr->FeePendReqStatus = FEE_PEND_INTR_WRITE;
    }
    else
    {
      /* if current address is before the last written word line */
      ReadLength = (uint16)FEE_DFLASH_WORDLINE_SIZE - Offset;
      SrcAddrNextWLAddr = Fee_lGetNextWLAddr(SrcAddr);
      ReadLengthInWL = (uint16)(SrcAddrNextWLAddr - SrcAddr);
      /* [cover parentID={AD9A1E6C-949E-4557-BE21-2AD1B11BD92D}][/cover]*/
      if(ReadLength > ReadLengthInWL)
      {

        /* [cover parentID={165A8250-EBD5-40e2-B8F9-D230ED9DFCC3}][/cover]*/
        if (((boolean)FALSE != Fee_lIsUnerasableAddr(SrcAddrNextWLAddr)) ||
            (SrcAddrNextWLAddr >= AffectedWLAddr))
        {
          ReadLength = ReadLengthInWL;
        }
      }

      /* copy from flash to read-write buffer */

      /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for interfacing with
      FLS.FEE is passing parameters to FLS APIs, casting is needed to match with
      the Fls API prototype. ReadWriteBuff is 4 byte aligned which is part
      of Fee_StateDataType.*/
      ReturnValueFls = Fls_17_Dmu_ReadWordsSync(\
                       (Fls_17_Dmu_AddressType)SrcAddr, \
                       (uint32 *)ReadWriteBuffPtr, \
                       (Fls_17_Dmu_LengthType)\
                       ReadLength / FEE_DFLASH_WORD_SIZE);

      SrcAddr += ReadLength;
      /* [cover parentID={FF802D45-B175-429f-8B0F-9F759D1943D1}][/cover]*/
      while (Fee_lIsUnerasableAddr(SrcAddr) == TRUE)
      {
        SrcAddr = Fee_lGetNextWLAddr(SrcAddr);
      }
      StateDataPtr->FeeCurrSectSrcAddr = SrcAddr;

      if(ReturnValueFls == E_OK)
      {
        /* proceed to internal write */
        StateDataPtr->FeePendReqStatus = FEE_PEND_INTR_WRITE;
      }
      else
      {
        /* handle error */
        Fee_lHandleWriteFail();
      }
    }
  }
  /* [cover parentID={294D0159-5E5F-49d6-9A04-7D09F3793236}][/cover]*/
  else
  {
    /* if block(s) within the last written word line is affected */

    Offset = (uint16)(SrcAddr & (uint32)FEE_DFLASH_WORDLINE_SIZE_1);
    LWBBufferPtr = &(StateDataPtr->FeeLastWrittenBlkBuffer[0]);

    /* If last written block's marker copy pending */
    if(StateDataPtr->FeeWLAffectedType == FEE_LWB_MARKER_COPY_PENDING)
    {
      ReadLength = FEE_DFLASH_PAGE_SIZE;
      StateDataPtr->FeeWLAffectedType = FEE_LWB_WITHIN_WL_AFFECTED;
    }
    /* [cover parentID={59866088-A0F6-4538-88D2-A96C7AAC998B}][/cover]*/
    else if(StateDataPtr->FeeWLAffectedType == FEE_LWB_WITHIN_WL_AFFECTED)
    {
      StateDataPtr->FeeIntrCurrReqPageCount = (uint16)
                    ((uint16)(LWBBufferPtr[Offset + FEE_SEVEN]) << FEE_EIGHT) |
                    (LWBBufferPtr[Offset + FEE_SIX]);
      (StateDataPtr->FeeIntrCurrReqPageCount) &= ((uint16)FEE_PAGE_COUNT_MASK);
      ReadLength = (StateDataPtr->FeeIntrCurrReqPageCount) << FEE_PAGE_TO_BYTE;
      /* [cover parentID={C2A65BFC-5A78-498c-B20F-2206102AD86C}][/cover]*/
      if(ReadLength > ReadLengthMax)
      {
        ReadLength = ReadLengthMax;
        StateDataPtr->FeeWLAffectedType = FEE_LWB_WITHIN_WL_AFFECTED_CONT;
      }
      else
      {
        StateDataPtr->FeeWLAffectedType = FEE_LWB_MARKER_COPY_PENDING;
      }
    }
    else /* FeeWLAffectedType == FEE_LWB_WITHIN_WL_AFFECTED_CONT */
    {
      ReadLength = (uint16)((StateDataPtr->FeeIntrCurrReqPageCount) -
                            (StateDataPtr->FeeBlkPageCount));
      ReadLength = (ReadLength << FEE_PAGE_TO_BYTE);

      StateDataPtr->FeeWLAffectedType = FEE_LWB_MARKER_COPY_PENDING;
    }

    /* copy from last written block buffer to read-write buffer */
    for(TempIndex = FEE_RESET; TempIndex < ReadLength; TempIndex++)
    {

      ReadWriteBuffPtr[TempIndex] = LWBBufferPtr[TempIndex + Offset];
    }
    StateDataPtr->FeeCurrSectSrcAddr = SrcAddr + ReadLength;
    StateDataPtr->FeePendReqStatus = FEE_PEND_INTR_WRITE;
  }

  StateDataPtr->FeeLastReadSize = ReadLength;
}

/*******************************************************************************
** Syntax : static void Fee_lHandleIntrWrite(void)                            **
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
** Description : This routine handles the functionality of                    **
** FEE_PEND_INTR_WRITE state of Write state machine                           **
*******************************************************************************/
/* [cover parentID={7646FA6A-066B-4036-BFC5-5832EEAA6FCC}]
Fee_lHandleIntrWrite
[/cover] */
/* [cover parentID={C9CBE3C8-3DF6-46d7-AD8E-36F5A3F24128}] [/cover] */
static void Fee_lHandleIntrWrite(void)
{

  Fee_StateDataType     *StateDataPtr;
  const uint8           *ReadWriteBuffPtr;
  uint32                 DestAddr;
  uint16                 Offset;
  Std_ReturnType         RetVal;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  StateDataPtr->FeeLastWriteSize = StateDataPtr->FeeLastReadSize;
  DestAddr = StateDataPtr->FeeNextFreePageAddr;
  Offset = (uint16) (DestAddr & (uint32)FEE_DFLASH_WORDLINE_SIZE_1);

  /* Skip un-erasable word line, if any */
  /* [cover parentID={454C8484-CAB1-4905-8CC5-625BDB614EA1}]*/
  if (Offset == FEE_ZERO)
  {
    /* [cover parentID={BE69F40F-C3D7-4c6e-9204-912814A94DA5}]*/
    while (Fee_lIsUnerasableAddr(DestAddr) == TRUE)
    {

      DestAddr = Fee_lGetNextWLAddr(DestAddr);
    }
    /* [cover parentID={62815483-801C-4c5a-A703-7AC69C8FB74F}]
    Assign the destination address to next free page address
    [/cover] */
    StateDataPtr->FeeNextFreePageAddr = DestAddr;
    StateDataPtr->FeeLastWrittenBlkInfo.BlockNumber = FEE_RESET;
    StateDataPtr->FeeLastWrittenBlkInfo.Status.Consistent = FEE_RESET;
  }
  /* [cover parentID={ECB9A01F-DD15-4c82-A7D7-EFBFDFB8DCBF}]*/
  if(StateDataPtr->FeeBlkPageCount == FEE_ZERO)
  {
    /* [cover parentID={9989D3F6-A7A0-420d-AFF9-F4C842AA7D9C}]
    Assign the block start address as destination address
    [/cover] */
    StateDataPtr->FeeBlockStartAddr = DestAddr;
  }

  ReadWriteBuffPtr = &(StateDataPtr->FeeReadWriteBuffer[Offset]);
  StateDataPtr->FeeBlkPageCount +=
    (Fee_PageType)((StateDataPtr->FeeLastWriteSize) >> FEE_BYTE_TO_PAGE);
  StateDataPtr->FeeUserJobStatus = FEE_JOB_REQSTD;
  StateDataPtr->FeePendReqStatus = FEE_PEND_INTR_COMPARE;

  /* initiate FLS write */
  RetVal = Fls_17_Dmu_Write((Fls_17_Dmu_AddressType)DestAddr,
                          ReadWriteBuffPtr,
                          (Fls_17_Dmu_LengthType)
                          (StateDataPtr->FeeLastWriteSize));
  /* [cover parentID={32BE104C-10BF-4198-8A79-C84CF31715BD}]
  Write operation request accepted
  [/cover] */
  if(RetVal == E_NOT_OK)
  {
    /* [cover parentID={BD81B204-474E-431f-B374-EFCAC35A049E}]
    Handle internal job error
    [/cover] */
    Fee_lHandleWriteFail();
  }
}
/*CYCLOMATIC_Fee_lHandleIntrWriteCompare_JUSTIFICATION:
Fee_lHandleIntrWriteCompare has to pass through many checks to confirm
successful block write, if it is broken into more functions, the readability
will get affected.
*/
/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lHandleIntrWriteCompare                     **
**                                             (const uint16 UserBlockIndex)  **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  UserBlockIndex: Index of the requested block            **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This routine handles the functionality of                    **
** FEE_PEND_INTR_COMPARE state of Write state machine                         **
*******************************************************************************/
/* [cover parentID={D902E00D-373D-4fe0-8187-30A6B19CBFE9}]
Fee_lHandleIntrWriteCompare
[/cover] */
  /* [cover parentID={0ECC187B-A54C-4efe-8C82-E00D17C55BF6}]*/
LOCAL_INLINE void Fee_lHandleIntrWriteCompare(const uint16 UserBlockIndex)
{
  /* [cover parentID={D902E00D-373D-4fe0-8187-30A6B19CBFE9}]*/
  Fee_StateDataType     *StateDataPtr;
  uint8                 *PendReqStatePtr;
  const Fee_BlockType   *BlockPtr;
  Fee_CacheType         *UnconfigBlockPtr;
  uint32                DestAddr;
  uint32                TempAddr;
  uint16                BlockNumber;
  uint16                CompareLength;
  uint16                TmpCompareLength;
  uint32                StartOffset;
  uint16                UnconfigBlockIndex;
  Std_ReturnType        ReturnValueFls;
  boolean               RetVal;
  uint16                NewUserBlockIndex;
  RetVal = (boolean)FALSE;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  uint32                LWBMarkerAddress;
  uint32                NextFreePageWLAddr;
  Fee_LastWrittenBlkInfoType  *LastBlkInfoPtr;

  BlockPtr = &(Fee_CfgPtr->FeeBlockConfigPtr[UserBlockIndex]);
  UnconfigBlockPtr = &(StateDataPtr->FeeBlockInfo[Fee_CfgPtr->FeeBlkCnt]);
  PendReqStatePtr = &(StateDataPtr->FeePendReqStatus);
  ReturnValueFls = E_OK;

  DestAddr = StateDataPtr->FeeNextFreePageAddr;
  TempAddr = Fee_lGetWLBeginning(DestAddr);
  /* [cover parentID={4B7F1597-A85F-4b1c-AAF8-9661B6F9A753}]
  Limit the length to be compared to maximum configured value
  [/cover] */
  CompareLength = (uint16)((DestAddr + (StateDataPtr->FeeLastWriteSize)) -
                           TempAddr);
  TmpCompareLength = CompareLength;
  CompareLength -=  StateDataPtr->FeeComparedLen;
  if(CompareLength > FEE_COMPARE_LEN_MAX)
  {
    /* [cover parentID={4B7F1597-A85F-4b1c-AAF8-9661B6F9A753}]
    [/cover] */
    CompareLength = FEE_COMPARE_LEN_MAX;
  }
  /*Check PVR error is occurred in last write if yes then no need of compare */
  /* [cover parentID={F9A25856-F27F-4786-AA4F-4BC0497B2B9C}][/cover] */
  if(StateDataPtr->FeeProgVerErr == FEE_RESET)
  {
    /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for interfacing with
    FLS.FEE is passing parameters to FLS APIs, casting is needed to match with
    the Fls API prototype. ReadWriteBuff is 4 byte aligned which is part
    of Fee_StateDataType.*/
    /* [cover parentID={EB0699CA-8445-4964-9B68-DACF3A1396E8}][/cover] */
    ReturnValueFls = Fls_17_Dmu_CompareWordsSync( \
                     (Fls_17_Dmu_AddressType)\
                     (TempAddr + StateDataPtr->FeeComparedLen), \
                     (uint32 *)(&(StateDataPtr->FeeReadWriteBuffer\
                                  [StateDataPtr->FeeComparedLen])), \
                     ((Fls_17_Dmu_LengthType)
                      CompareLength / FEE_DFLASH_WORD_SIZE));

    StateDataPtr->FeeComparedLen += CompareLength;
  }
  /* Compare failed or PVR is set raise the illegal notification with write 
  production error */
  /* [cover parentID={C4276351-E6BA-4b09-81E3-32E19D0B0347}][/cover] */
  if((ReturnValueFls == E_NOT_OK) ||
      (StateDataPtr->FeeProgVerErr == FEE_SET))
  {
    StateDataPtr->FeeComparedLen = FEE_RESET;
    /* [cover parentID={1FC1262D-1AAF-42a7-8432-22A528B4CD75}][/cover] */
    Fee_lHandleWriteFail();
  }
  else if(StateDataPtr->FeeComparedLen != TmpCompareLength)
  {
    /*dummy else if to skip else for in between loops */
  }
  /* Compare successful */
  /* [cover parentID={C2A7EA14-1887-454c-AE77-46D3D035491D}][/cover] */
  else
  {
    StateDataPtr->FeeComparedLen = FEE_RESET;
    /* Update cache table for previous block - both configured and unconfigured
       blocks needs only address update, the status remains the same */
    StartOffset = DestAddr & FEE_DFLASH_WORDLINE_SIZE_1;
    /* [cover parentID={093B8388-B88A-4cef-84AF-4E2F12D4FA72}][/cover] */
    if((StateDataPtr->FeeLastWriteSize == FEE_EIGHT) &&
        ((StateDataPtr->FeeReadWriteBuffer[StartOffset]) ==
         FEE_DATA_MARKER_PAGE_ID))
    {
       BlockNumber = StateDataPtr->FeeCurrReqBlockNum;
       LWBMarkerAddress = StateDataPtr->FeeNextFreePageAddr;
       NextFreePageWLAddr =
       Fee_lGetWLBeginning(StateDataPtr->FeeNextFreePageAddr);
       LastBlkInfoPtr = &(StateDataPtr->FeeLastWrittenBlkInfo);
       /* [cover parentID={D9482901-428B-4092-B104-09E5BBE5F8DD}][/cover] */
       if(((StateDataPtr->FeeBlockStartAddr) < NextFreePageWLAddr) &&
          (LWBMarkerAddress >= NextFreePageWLAddr))
       {
          /*Last written block is spanning across the WL, update the block info
          to last written block info*/
          LastBlkInfoPtr->BlockNumber = StateDataPtr->FeeCurrReqBlockNum;
          LastBlkInfoPtr->PageCount = StateDataPtr->FeeBlkPageCount;
          LastBlkInfoPtr->Addr = StateDataPtr->FeeBlockStartAddr;
          LastBlkInfoPtr->Status.Consistent = FEE_SET;
       }

       NewUserBlockIndex = Fee_lGetUsrBlockIndex(BlockNumber);
       if(NewUserBlockIndex != FEE_LOG_BLOCK_NOT_FOUND)
       {
          StateDataPtr->FeeBlockInfo[NewUserBlockIndex].Address =
          StateDataPtr->FeeBlockStartAddr;
       }
       else
       {
          UnconfigBlockIndex = FEE_RESET;
          while((UnconfigBlockIndex < (StateDataPtr->FeeUnConfigBlockCount)) &&
              (RetVal == (boolean)FALSE))
          {
            if((UnconfigBlockPtr[UnconfigBlockIndex].BlockNumber) ==
                BlockNumber)
            {
              UnconfigBlockPtr[UnconfigBlockIndex].Address =
              StateDataPtr->FeeBlockStartAddr;
              RetVal = (boolean)TRUE;
            }
            else
            {
              UnconfigBlockIndex++;
            }
          }
       }
    }

    StateDataPtr->FeeNextFreePageAddr += (StateDataPtr->FeeLastWriteSize);
    *PendReqStatePtr = FEE_PEND_INTR_READ;

    /* if affected type is within the last written word line */
    /* [cover parentID={03AABAED-04C0-48db-8239-7ADEC055B1E3}][/cover] */
    if(StateDataPtr->FeeWLAffectedType == FEE_LWB_WITHIN_WL_AFFECTED)
    {
      StateDataPtr->FeeBlkPageCount = FEE_RESET;
      StartOffset = StateDataPtr->FeeCurrSectSrcAddr &
                    FEE_DFLASH_WORDLINE_SIZE_1;
      /* [cover parentID={E50CA68D-3674-4f52-A5AD-405CEAC83FBA}][/cover] */
      if(Fee_lIsLastWrittenWLAffected((uint16)(StartOffset)) == (boolean)FALSE)
      {
        /* Previous block is written, now write the current user requested block
          register write request */
        Fee_lRegisterWriteRequest(
          StateDataPtr->FeePendReqInfo.DataWriteBufferPtr,
          BlockPtr);
        StateDataPtr->FeeBlockStartAddr = StateDataPtr->FeeNextFreePageAddr;
      }
    }
  }
}

/*******************************************************************************
** Syntax : static void Fee_lLocalWrite(void)                                 **
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
** Description : This routine will perform the write operation on DFLASH. It  **
** is called by Fee_MainFunction                                              **
*******************************************************************************/
/*[cover parentID={5F758A15-CC83-4226-B568-5939E096E4B2}][/cover]*/
static void Fee_lLocalWrite(void)
{
  const Fee_StateDataType     *StateDataPtr;
  const uint8                 *PendReqStatePtr;
  uint16                 BlockNumber;
  uint16                 UserBlockIndex;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  BlockNumber = StateDataPtr->FeePendReqInfo.BlockNumber;
  /*[cover parentID={D5C821F1-C3EB-4276-B515-5EFD5F088BC6}][/cover]*/
  UserBlockIndex = Fee_lGetUsrBlockIndex(BlockNumber);

  PendReqStatePtr = &(StateDataPtr->FeePendReqStatus);

  /**********************************************************************/
  /*                       2.STATE MACHINE EXECUTION                    */
  /**********************************************************************/

  /*********** CASE 1: USER WRITE REQSTD STATE *******************/

  /*[cover parentID={FEE9B199-2578-4afd-8BD4-A7B908370F14}][/cover]*/
  if ((boolean)TRUE == Fee_lIsUserWriteInvldReqstd(StateDataPtr))
  {
    /*[cover parentID={42DB85BF-86B9-4350-BF7D-BDC6D31D5E54}][/cover]*/
    Fee_lHandleUserWriteReq(UserBlockIndex);
  }


  /*********** CASE: USER WRITE COMPARE STATE *******************/
  /*[cover parentID={A72D4963-1B3E-437c-9CCF-80BFDC6F3C09}][/cover]*/
  if(*PendReqStatePtr == FEE_PEND_PREV_COMPARE)
  {
    /*[cover parentID={38FB0220-1DFC-4a9c-B419-9D4A01B757D6}][/cover]*/
    Fee_lHandleUserWriteCompare(UserBlockIndex);
  }

  /*********** CASE: USER WRITE ONGOING STATE *******************/
  /*[cover parentID={67AC0843-8E98-4f3f-A0D7-AE9D4EE83CA7}][/cover]*/
  if(*PendReqStatePtr == FEE_PEND_PREV_WRITE_REQ)
  {
    /*[cover parentID={4C21089C-FF82-4c54-92B3-94225CB9E8F2}][/cover]*/
    Fee_lHandleUserWrite(UserBlockIndex);
  }


  /*********** CASE: INTERNAL WRITE COMPARE STATE *******************/
  /*[cover parentID={460BF695-F308-4bbc-B4C6-5DCA32A4BAE7}][/cover]*/
  if (*PendReqStatePtr == FEE_PEND_INTR_COMPARE)
  {
    /*[cover parentID={42B82BC3-AFEC-4c95-AC21-AE3F016F07B8}][/cover]*/
    Fee_lHandleIntrWriteCompare(UserBlockIndex);
  }

  /*********** CASE: INTERNAL WRITE BLOCK READ STATE *******************/
  /*[cover parentID={910D995A-207C-48e8-B54B-005701AB00FB}][/cover]*/
  if (*PendReqStatePtr == FEE_PEND_INTR_READ)
  {
    /*[cover parentID={6A1F0071-B0B1-45fa-8D64-F9C2578D8B5E}][/cover]*/
    Fee_lHandleIntrRead();
  }


  /*********** CASE: INTERNAL WRITE ONGOING STATE *******************/
  /*[cover parentID={D5E7EE4B-47FA-4157-BE16-A8AAAE89590B}][/cover]*/
  if (*PendReqStatePtr == FEE_PEND_INTR_WRITE)
  {
    /*[cover parentID={CC14EA77-4929-4cbe-A9CE-23293D566505}][/cover]*/
    Fee_lHandleIntrWrite();
  }
}/* End of Fee_lLocalWrite */

#endif
/*******************************************************************************
** Syntax : static void Fee_lRegisterWriteRequest(                            **
**                                   const uint8 * const DataWriteBufferPtr,  **
**                                   const Fee_BlockType * const BlockPtr)    **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in):  DataWriteBufferPtr -  Pointer to Data buffer             **
**                    BlockPtr - Pointer to block data structure              **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This routine will register the write request in the pending  **
** request buffer.                                                            **
*******************************************************************************/
/*[cover parentID={B498F3F5-2BF7-47e2-94BB-9E97DE112B78}] [/cover]*/
static void Fee_lRegisterWriteRequest(const uint8 * const DataWriteBufferPtr,
                                      const Fee_BlockType * const BlockPtr)
{
  Fee_StateDataType     *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  StateDataPtr->FeeStatusFlags.FeeWriteInvldQSeraseAPICalled = FEE_SET ;
  StateDataPtr->FeeStatusFlags.FeeStartInitGC = FEE_SET ; /*TRUE*/

  /* if the logical block is of immediate in nature */
  /*[cover parentID={D02B7DC4-BC83-4f7a-A57F-D7406B55075F}] [/cover]*/
  if ( ( BlockPtr->FeeImmediateData == (uint32)FEE_IMMEDIATE_DATA ) &&
       /* This request is not for invalidation    */
       ( StateDataPtr->FeeStatusFlags.FeeBlkInvalidStatus
         == (uint32)FEE_RESET )
     )
  {

    StateDataPtr->FeePendReqStatus = FEE_REQ_IMM_WRITE;
  }
  else
  {
    StateDataPtr->FeePendReqStatus = FEE_REQ_NORM_WRITE;
  }

  /* [cover parentID={46A7C871-0E1F-4a3a-803D-E0BA815B03F5}]
  Update the job result to MEMIF_JOB_PENDING
  [/cover] */
  StateDataPtr->FeeJobResult = MEMIF_JOB_PENDING;
  /* [cover parentID={A31CEE06-AEE1-4063-812D-7BE780C3A9C4}]
  Store the pending request parameters in the pending request buffer
  [/cover] */
  /* Store the pending request parameters in the pending request buffer*/
  StateDataPtr->FeePendReqInfo.BlockNumber  = BlockPtr->BlockNumber;
  StateDataPtr->FeePendReqInfo.DataWriteBufferPtr = DataWriteBufferPtr;

  /* Update the current requested logical block number */
  StateDataPtr->FeeCurrReqBlockNum = BlockPtr->BlockNumber;
  /*Reset FeeReadLen to 0 for every new write request. This is also needed
  in case if previous write request is cancelled.*/
  StateDataPtr->FeeReadLen = FEE_RESET;
}/* End of Fee_lRegisterWriteRequest */
/* [cover parentID={3F9907AD-6E65-4d53-882A-1F19726962C7}]
NVM data block supported
[/cover] */
/* [cover parentID={16B182B9-FE60-4d9d-AFFA-B333EFE37022}]
[/cover] */
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/*******************************************************************************
** TRACEABILITY: []                                                           **
**                                                                            **
** Syntax : static void Fee_lLocalRead(void)                                  **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This routine will perform the read operation on DFLASH. It   **
** is called by Fee_MainFunction                                              **
*******************************************************************************/
/* [cover parentID={2D9604F9-0837-4b8c-9F7B-22B3C0BE5ED8},
{83815BF6-33EE-45ff-AC9A-6D522CD1D384}]
Fee_lLocalRead
[/cover] */
static void Fee_lLocalRead(void)
{
  Fee_PendReqBufType   *PendReqPtr;
  Fee_StateDataType    *StateDataPtr;
  uint8                *DataBufferPtr;
  uint32                ActualAddr;

  uint16                ReadLength;
  uint16                BlockNumber;
  uint16                BlockOffset;
  uint16                Length;
  uint16                UserBlockIndex;
  uint16                DataByteCount;
  Std_ReturnType        ReturnValue;
  uint8                 LoopIndex;


  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  PendReqPtr = &StateDataPtr->FeePendReqInfo;
  BlockNumber = PendReqPtr->BlockNumber;
  BlockOffset = PendReqPtr->BlockOffset;
  DataBufferPtr = PendReqPtr->DataBufferPtr;
  DataByteCount = FEE_ONE;

  ReturnValue = E_OK;
  UserBlockIndex = Fee_lGetUsrBlockIndex(BlockNumber);

  /* [cover parentID={2D9604F9-0837-4b8c-9F7B-22B3C0BE5ED8}][/cover]]*/
  /**********************************************************************/
  /*                1.AYSNC STATE MACHINE TRANSITIONS                   */
  /**********************************************************************/
  /*These transitions are handled in Fee_JobEndNotification and
    Fee_JobErrorNotification as specified by AUTOSAR*/


  /**********************************************************************/
  /*                       2.STATE MACHINE EXECUTION                    */
  /**********************************************************************/

  /*********** CASE 1: READ REQSTD STATE *******************/
  /* [cover parentID={6FEF8D8B-D8CC-4a3e-B824-AFF8A4461AC9}][/cover]*/
  if((boolean)TRUE == Fee_lIsUserReadReqstd(StateDataPtr))
  {
    /*********************** PERFORM CHECKS START **********************/
    /* [cover parentID={D9445F4C-D14A-48d2-A91C-A6463D3D5F8B}]
    Perform read check
    [/cover] */
    ReturnValue = Fee_lPerformReadCheck(UserBlockIndex);

    /* [cover parentID={49CC71B9-087A-41cb-A546-0967F5467841}][/cover] */
    if(ReturnValue == E_OK)
    {
      /* [cover parentID={1FCDC8C5-DBAE-451c-A93D-D8237738A3C7}]
      Call
      [/cover] */
      Fee_lPerformStuffCheck(UserBlockIndex);
    }

    /* [cover parentID={18E22B35-ECF5-4a71-B0F7-8DEDB4362C85}]
    Perform initial operations for local read
    [/cover] */
    BlockOffset = Fee_lLocalReadStart(ReturnValue, UserBlockIndex);

    /*Check if the job is finished*/
    if(StateDataPtr->FeeJobResult != MEMIF_JOB_PENDING)
    {
      /* set ReturnValue to E_NOT_OK. This will avoid further processing */
      ReturnValue = E_NOT_OK;
    }
  }

  /*********** CASE 2: READ REQSTD STATE *******************/

  StateDataPtr->FeeUserReadDestPtr = DataBufferPtr;

  /* PERFORM READ START */
  /* [cover parentID={7ABD7BDF-9F5B-41e6-AB7A-8AB658E7029A}][/cover]]*/
  if (StateDataPtr->FeePendReqStatus == FEE_PEND_PREV_READ_REQ)
  {
    if(BlockOffset > FEE_ZERO)
    {
      while(BlockOffset < FEE_SEVEN)
      {

        StateDataPtr->FeeUserReadDestPtr[0] =
          StateDataPtr->FeeReadWriteBuffer[DataByteCount + BlockOffset];
        BlockOffset++;

        StateDataPtr->FeeUserReadDestPtr++;
      }
      BlockOffset = FEE_RESET;
      DataByteCount += FEE_EIGHT;
    }
    while(DataByteCount < StateDataPtr->FeeLastReadSize)
    {
      for(LoopIndex = FEE_RESET; LoopIndex < FEE_SEVEN; LoopIndex++)
      {

        StateDataPtr->FeeUserReadDestPtr[LoopIndex] =
          StateDataPtr->FeeReadWriteBuffer[DataByteCount + LoopIndex];
      }
      /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
            array indexing used for FEE application buffers.
            Pointers are accessing the correct memory range locations.
            The access range is within the boundaries of the buffer. */
      StateDataPtr->FeeUserReadDestPtr += FEE_SEVEN;
      DataByteCount += FEE_EIGHT;
    }
  }

  /* [cover parentID={F03A84F2-2309-4e10-9A32-53010A45CA72}][/cover]*/
  if (((ReturnValue == E_OK) &&
       (StateDataPtr->FeePendReqStatus != FEE_PEND_PREV_NO_REQ)) ||
      (StateDataPtr->FeePendReqStatus == FEE_PEND_PREV_READ_REQ)
     )
  {
    /* [cover parentID={C2FAE471-2275-4229-8D16-88623013D999}][/cover]
    Calculate actual address where data is needed to be read
    (current sector source address)
    [/cover] */
    /* calculate actual address where data is needed to be read */
    ActualAddr = StateDataPtr->FeeCurrSectSrcAddr;


    /*Store the block offset in pending buffer structure*/

    PendReqPtr->BlockOffset = BlockOffset;
    Length = PendReqPtr->Length;

    ReadLength = Fee_lCheckReadLength(ActualAddr, Length);

    Fee_lClearFeeReadWriteBuffer();

    StateDataPtr->FeeLastReadSize = (Fls_17_Dmu_LengthType)ReadLength;

    /* [cover parentID={D1B00BF2-5B12-4cf1-B2F7-5860DE19F72C}][/cover]*/
    ReturnValue = Fls_17_Dmu_Read((Fls_17_Dmu_AddressType)ActualAddr,
                           StateDataPtr->FeeReadWriteBuffer,
                           (Fls_17_Dmu_LengthType)ReadLength);
    /* [cover parentID={76AF25B5-E0ED-4c94-B3C8-94737A9A769D}]
    Read operation accepted
    [/cover] */
    if(ReturnValue == E_NOT_OK)
    {
      /* [cover parentID={9532BB3C-C9EB-429b-A848-D832DDE76A7B}]
      Read operation accepted
      [/cover] */
      Fee_lHandleUsrJobFailure(FEE_READ);
    }
    else
    {
      StateDataPtr->FeeCurrReqBlockNum = BlockNumber;

      /* If the current request is set to previous pending */
      /* [cover parentID={28DC10D4-9FB2-48cb-8999-14E4FDC2507B}][/cover]*/
      if(StateDataPtr->FeePendReqStatus == FEE_PEND_PREV_READ_REQ)
      {
        /* Increment FeeCurrSectSrcAddr to point to next page */

        ActualAddr += ReadLength;
        /* [cover parentID={717A019A-113F-4602-B06E-3C9E8AC51E28}][/cover]*/
        /* [cover parentID={D6D786E9-2A6C-4ee3-9F36-49D6743BBB34}][/cover]*/
        while (Fee_lIsUnerasableAddr(ActualAddr) == TRUE)
        {
          /* [cover parentID={7257A209-1DEF-4935-A045-467F3676C86B}][/cover]*/
          ActualAddr = Fee_lGetNextWLAddr(ActualAddr);
        }
        StateDataPtr->FeeCurrSectSrcAddr = ActualAddr;
      }

      /* Store the read request parameters in the Pending buffer structure */
      PendReqPtr->BlockOffset = BlockOffset;
      /* PendReqPtr->Length = Length;*/
      PendReqPtr->DataBufferPtr = StateDataPtr->FeeUserReadDestPtr;
      /* PERFORM READ ENDS */
    }
  }
}/* End of Fee_lLocalRead */


/*******************************************************************************
** TRACEABILITY: []                                                           **
**                                                                            **
** Syntax : static uint16 Fee_lCheckReadLength(const Fls_17_Dmu_AddressType   **
**                                               ActualAddr,                  **
**                                               const uint16 Length)         **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  ActualAddr - Address of read location                   **
**                    Length     -  Length to be read                         **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Actual Read length for reading data from flash.         **
**                                                                            **
** Description : This routine will perform the check of the read length       **
**                                                                            **
*******************************************************************************/
/* [cover parentID={2DAEED1A-ABAA-4798-A423-85A47074F04A}][/cover] */
static uint16 Fee_lCheckReadLength(const Fls_17_Dmu_AddressType ActualAddr,
                                   const uint16 Length)
{
  Fee_StateDataType    *StateDataPtr;
  Fee_PendReqBufType   *PendReqPtr;
  uint8                 ReadLengthPages;
  uint16                ReadLimit;
  uint16                ReadLength;
  uint16                BlockOffset;
  uint16                SizeInCurrentWL;
  uint32                TempAddress;
  uint16                NewLength;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  PendReqPtr = &StateDataPtr->FeePendReqInfo;
  BlockOffset = PendReqPtr->BlockOffset;
  NewLength = (uint16)Length;

  /* [cover parentID={2F225DFC-9226-4a7d-B0B7-CA802CA94014}][/cover] */
  if(Fee_lIsWLBeginning(ActualAddr) == FEE_NEW_WL_BEGIN)
  {
    ReadLimit = FEE_DATA_BYTES_IN_WORDLINE;
  }
  else
  {
    SizeInCurrentWL = (uint16)FEE_DFLASH_WORDLINE_SIZE -
                      (uint16)(ActualAddr & FEE_DFLASH_WORDLINE_SIZE_1);
    ReadLimit = (SizeInCurrentWL >> FEE_BYTE_TO_PAGE) * FEE_SEVEN;
  }
  /* [cover parentID={CE5D8656-0752-43ee-9F47-86EF17E79FCE}][/cover] */
  if (Length > (ReadLimit - BlockOffset))
  {
    /* [cover parentID={E69A67AD-59C3-45da-897A-EC57DA490C94}][/cover] */
    if(Fee_lIsWLBeginning(ActualAddr) != FEE_NEW_WL_BEGIN)
    {
      TempAddress = Fee_lGetNextWLAddr(ActualAddr);
      /* [cover parentID={D21B0A3A-0AF1-4200-B1CE-06FD72918D6C}][/cover] */
      if((boolean)FALSE == Fee_lIsUnerasableAddr(TempAddress))
      {
        ReadLimit = FEE_DATA_BYTES_IN_WORDLINE;
      }
    }
  }

  ReadLimit = ReadLimit - BlockOffset;
  /* [cover parentID={3B5E055E-D0B3-466e-9862-5FAD2AEE7A85}][/cover] */
  if (Length > ReadLimit)
  {
    ReadLength = ReadLimit;
    NewLength = Length - ReadLimit;
    StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_READ_REQ;
  }
  else
  {
    ReadLength = Length;
    StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_READ_NOTIF;
  }

  /* Call Fls_Read to read the data from DFLASH */
  StateDataPtr->FeeUserJobStatus = FEE_JOB_REQSTD;
  /* [cover parentID={FAB96444-AA81-4117-8E04-BC21852E167D}][/cover] */
  if((ReadLength + BlockOffset) > FEE_SEVEN)
  {
    ReadLength = ReadLength - (FEE_SEVEN - BlockOffset);
    ReadLengthPages = (uint8)Fee_lGetDFLASHPages(ReadLength) - FEE_ONE;

  }
  else
  {
    ReadLengthPages = (uint8)Fee_lGetDFLASHPages(ReadLength) - FEE_TWO;
  }

  ReadLength = (uint16)ReadLengthPages << FEE_PAGE_TO_BYTE;
  PendReqPtr->Length = NewLength;

  return (ReadLength);
}/*End of Fee_lCheckReadLength*/


/*******************************************************************************
** Syntax : LOCAL_INLINE uint16 Fee_lLocalReadStart                           **
**                                        (const Std_ReturnType ReturnValue,  **
**                                              const uint16 UserBlockIndex)  **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  ReturnValue - Return value of Fee_lPerformReadCheck     **
**                    UserBlockIndex - User block index                       **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  uint16 - Block Offset                                   **
**                                                                            **
** Description : This routine will perform the initial operations of          **
**               Fee_lLocalRead()                                             **
*******************************************************************************/
/* [cover parentID={37E1ECDE-74B6-409c-8422-3868E57E3A99}][/cover] */
LOCAL_INLINE uint16 Fee_lLocalReadStart(const Std_ReturnType ReturnValue,
                                        const uint16 UserBlockIndex)
{
  const Fee_PendReqBufType   *PendReqPtr;
  Fee_StateDataType    *StateDataPtr;
  uint32                StartAddr;
  uint16                BlockOffset;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  PendReqPtr = &StateDataPtr->FeePendReqInfo;
  BlockOffset = PendReqPtr->BlockOffset;

  /* [cover parentID={10B0AA13-A21D-47eb-AC09-59B6530BDABB}][/cover] */
  if(ReturnValue == E_NOT_OK )
  {
    /*Check if QS erase was suspended. If yes then set FeePendReqStatus to
     FEE_REQ_QUASI_ERASE to set module status to busy.*/
    #if((FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA ) && \
    (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON))
    /* [cover parentID={31FA2DC6-7CC2-4a7e-902A-C7FC43C1D89D}][/cover] */
    if(StateDataPtr->FeeQsEraseSuspend == FEE_ERASE_SUSPENDED)
    {
      StateDataPtr->FeePendReqStatus = FEE_REQ_QUASI_ERASE;
      StateDataPtr->FeeQsJob = FEE_ERASE_JOB;
    }
    else
    #endif
    {
      StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_NO_REQ;
    }

    /* [cover parentID={0B064C63-B18F-480e-ADB2-C0ECB2DFF313}][/cover] */
    if ( Fee_CfgPtr->FeeNvmJobErrorNotification != NULL_PTR )
    {
      /* [cover parentID={7E0A6A25-41BA-4a6e-9758-B1AB3941C27D}]
      Call the notification function
      [/cover] */
      (Fee_CfgPtr->FeeNvmJobErrorNotification)();
    }
  }
  /* ReturnValue is E_OK here */
  /* [cover parentID={67D186A8-D62B-4a72-AAD1-3B91B7539DFC}][/cover] */
  else
  {
    /* Load the start address of the block */
    #if (FEE_GET_PREV_DATA_API == STD_ON)
    if(PendReqPtr->GetPrevCopy == FEE_SET )
    {
      StartAddr = (StateDataPtr->FeeBlockInfo[UserBlockIndex].PrevCopyAddress)
                  + FEE_DFLASH_PAGE_SIZE;
    }
    else
    #endif
    {
      StartAddr = (StateDataPtr->FeeBlockInfo[UserBlockIndex].Address)
                  + FEE_DFLASH_PAGE_SIZE;
    }

    /*Calculate the address of data page using block offset.Read will be
    start from this page. */
    /* [cover parentID={E1B699DA-4B65-458d-9021-D2FD241F9495}][/cover] */
    do
    {
      /* [cover parentID={F4F75BF8-EB2C-4100-B7DF-EA8424DF882E}][/cover] */
      if(Fee_lIsWLBeginning(StartAddr) == FEE_NEW_WL_BEGIN)
      {
        while (Fee_lIsUnerasableAddr(StartAddr) == TRUE)
        {
          /* [cover parentID={A06C64FE-6A28-4f4b-BFB1-E45B9BDD8B3E}][/cover] */
          StartAddr = Fee_lGetNextWLAddr(StartAddr);
        }
      }
      if (BlockOffset >= FEE_SEVEN)
      {
        StartAddr += FEE_DFLASH_PAGE_SIZE;
        BlockOffset -= FEE_SEVEN;
      }
    } while(BlockOffset >= FEE_SEVEN);
    /* [cover parentID={34261008-11D1-4e1b-8AFF-FA65C88FDF8E}][/cover] */

    StateDataPtr->FeeCurrSectSrcAddr = StartAddr;
  }

  return(BlockOffset);
}

/******************************************************************************
** Syntax : static void Fee_lGcErrorHandler(const uint8 Error                **
**                                            const uint16 Index)            **
**                                                                           **
** Service ID:                                                               **
**                                                                           **
** Sync/Async:  Synchronous                                                  **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in) :  uint8  Error                                           **
**                    uint16 Block index in cache table                      **
**                                                                           **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    :  None                                                   **
**                                                                           **
** Description : This routine is responsible for handling GC transitions     **
**               in case of errors.                                          **
******************************************************************************/
/* [cover parentID={3F9907AD-6E65-4d53-882A-1F19726962C7}]
NVM data block supported
[/cover] */
/* [cover parentID={6CF9EF13-588A-468c-8629-0C1B68B18DA6}][/cover] */
static void Fee_lGcErrorHandler(const uint8 Error, const uint16 Index)
{
  Fee_StateDataType  *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  switch(Error)
  {
    /* Write Failure */
    /* [cover parentID={E0F2169B-FBAF-431d-AA7B-2DCD7D28C6C0}][/cover] */
    case FEE_GC_WRITE:
    {
      /* [cover parentID={977693FB-9D15-4328-9118-281929FCDA91}]
      production error enabled
      [/cover] */
      /* Report production error */
      #if (FEE_GC_WRITE_DEM_REPORT == FEE_ENABLE_DEM_REPORT)

      /* [cover parentID={625A4011-7623-4fb7-998D-4E6038401297}]
      Report write production error to Mcal_Wrapper FEE_E_GC_WRITE
      [/cover] */
      Fee_lReportDemError(FEE_E_GC_WRITE, DEM_EVENT_STATUS_FAILED);
      #endif
      /* [cover parentID={15A4389B-F048-4133-8BC1-61C7DCD564DF}][/cover] */
      Fee_lHandleGcFail();
      break;
    }

    /* Read Failure */
    /* [cover parentID={7320B26B-F351-4a00-A1F1-7E244BD7D7B7}][/cover] */
    case FEE_GC_READ:
    {
      /* [cover parentID={82304E5E-B10F-41b2-99CB-9168EE0163DF}]
      production error enabled
      [/cover] */
      /* Report production error */
      #if (FEE_GC_READ_DEM_REPORT == FEE_ENABLE_DEM_REPORT)

      /* [cover parentID={37FED89C-E60B-4289-99CC-D1480A538B50}]
      Report read production error to Mcal_Wrapper FEE_E_GC_READ
      [/cover] */
      Fee_lReportDemError(FEE_E_GC_READ, DEM_EVENT_STATUS_FAILED);
      #endif
     /* [cover parentID={6E677D74-B0F1-4539-966D-34B09EC2D8D9}][/cover] */
      if((StateDataPtr->FeeGcState == FEE_GC_UNCFG_START_COPY) ||
          (StateDataPtr->FeeGcState == FEE_GC_UNCFG_COPY_READ_NXTPAGE))
      {
        /* GC in unconfigured block copy state ,discard the current
        unconfigured block and continue GC*/
        Fee_lGcDiscardUnconfigBlk(Index);
        StateDataPtr->FeeGcState = FEE_GC_UNCFG_START_COPY;
      }
      else
      {
        /* GC in configure block copy state ,discard the current configured
         block and continue GC*/
        /* [cover parentID={C2010611-5A23-4dc1-A07E-83C9A9B0752A}][/cover] */
        Fee_lGcDiscardConfigBlk(Index);
        StateDataPtr->FeeGcState = FEE_GC_START_COPY;
      }
      break;
    }

    /* Erase Failure */
    /* [cover parentID={5D413302-47CF-4db9-B87F-008616CBAECB}][/cover] */
    case FEE_GC_ERASE:
    {
      /* Report production error */
      #if (FEE_GC_ERASE_DEM_REPORT == FEE_ENABLE_DEM_REPORT)

      /* [cover parentID={8DD26F81-EE1C-448f-93C1-5C8BC9E3C417}]
      Report erase production error to Mcal_Wrapper FEE_E_GC_ERASE
      [/cover] */
      Fee_lReportDemError(FEE_E_GC_ERASE, DEM_EVENT_STATUS_FAILED);
      #endif
      /* [cover parentID={15A4389B-F048-4133-8BC1-61C7DCD564DF}][/cover] */
      Fee_lHandleGcFail();
      break;
    }

    /* GC  failure - a case where the GC triggers another GC */
    case FEE_GC_TRIG:
    {
      /* [cover parentID={82304E5E-B10F-41b2-99CB-9168EE0163DF}]
      production error enabled
      [/cover] */
      /* Report production error */
      #if (FEE_GC_TRIG_DEM_REPORT == FEE_ENABLE_DEM_REPORT)

      /* [cover parentID={65B83B6F-AB0F-4a30-B718-3183A9FA7E2C}]
      Report to Mcal_Wrapper on account of GC trigger failure FEE_E_GC_TRIG
      [/cover] */
      Fee_lReportDemError(FEE_E_GC_TRIG, DEM_EVENT_STATUS_FAILED);
      #endif
      /* [cover parentID={15A4389B-F048-4133-8BC1-61C7DCD564DF}][/cover] */
      Fee_lHandleGcFail();
      break;
    }
    default:
    {
      break;
    }

  }


}/*End of Fee_lGcErrorHandler */

/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lHandleGcFail(void)                     **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function shall handle the severe error case or          **
** internal job fail case during Garbage collection                           **
*******************************************************************************/
/* [cover parentID={6E022F9A-F40D-47ef-8942-B91CFEC9BD34}][/cover] */
LOCAL_INLINE void Fee_lHandleGcFail(void)
{
  Fee_StateDataType     *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* Enter GC Fail state */
  StateDataPtr->FeeGcState = FEE_GC_FAIL;
  /* [cover parentID={5B785984-4A46-4d77-A92C-F7F5C38E8602}]
  Is illegal state notification configured?
  [/cover] */
  /* Raise Illegal state notification if configured */
  if(Fee_CfgPtr->FeeNvmIllegalStateNotification != NULL_PTR)
  {
    /* [cover parentID={7D8E6AA9-44D9-4f7f-8BE8-D7B5F5DABABC}]
    Call the notification function
    [/cover] */
    /* Call the Notification function */
    Fee_CfgPtr->FeeNvmIllegalStateNotification();
  }
}

/******************************************************************************
** Syntax : static void Fee_lGcRead(const Fls_17_Dmu_AddressType Position,   **
**                                  const uint16 Offset)                     **
**                                                                           **
** Service ID:                                                               **
**                                                                           **
** Sync/Async:  Asynchronous                                                 **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in) :(uint32)  Position: Dflash Address to read from          **
**                  (uint16) Offset: Offset of read write buffer             **
**                                                                           **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    :  None                                                   **
**                                                                           **
** Description : Gives a read request during GC                              **
******************************************************************************/
/* [cover parentID={FB953EC9-8278-497e-A1B9-8A52D4DDDEB4}][/cover] */
static void Fee_lGcRead(const Fls_17_Dmu_AddressType Position,
                        const uint16 Offset)
{
  Fee_StateDataType    *StateDataPtr;
  uint8                *GcReadWriteBufferPtr;
  Fee_PageType          PendingPageCount;
  Fls_17_Dmu_LengthType        ReadLength;
  uint32                PendingBlockSize;
  uint16                GcSrcAddrOffset;
  uint8               Error;
  uint16              BlockIndex;


  ReadLength = FEE_DFLASH_PAGE_SIZE;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  PendingPageCount = StateDataPtr->FeeGcCurrBlkInfo.PageCount -
                     StateDataPtr->FeeBlkPageCount;
  PendingBlockSize = ((uint32)PendingPageCount << FEE_PAGE_TO_BYTE);
  /* [cover parentID={B688E3ED-1D22-4b2d-8CB6-4B2774087182}][/cover] */
  if(PendingPageCount > FEE_ZERO)
  {
    /* [cover parentID={517A3C32-7DD6-4e94-8719-EC5D3AFA1E55}][/cover] */
    if(PendingBlockSize > (FEE_DFLASH_WORDLINE_SIZE - ((uint32)Offset)))
    {
      ReadLength = (Fls_17_Dmu_LengthType)FEE_DFLASH_WORDLINE_SIZE - Offset;
    }
    else
    {
      ReadLength = (Fls_17_Dmu_LengthType)PendingBlockSize;
    }
    GcSrcAddrOffset = (uint16)(Position & FEE_DFLASH_WORDLINE_SIZE_1);
    if(ReadLength >
      ((Fls_17_Dmu_LengthType)FEE_DFLASH_WORDLINE_SIZE - GcSrcAddrOffset))
    {
      if(Fee_lIsUnerasableAddr(Position + FEE_DFLASH_WORDLINE_SIZE) == TRUE)
      {
        ReadLength =
          (Fls_17_Dmu_LengthType)FEE_DFLASH_WORDLINE_SIZE - GcSrcAddrOffset;
      }
    }
  }

  /* [cover parentID={3E97A7D6-D344-49ae-9E23-70E8FA850B90}]
  Assign GcReadWriteBufferPtr as destination address by adding offset to FeeGcReadWriteBuffer
  [/cover] */

  GcReadWriteBufferPtr = &(StateDataPtr->FeeGcReadWriteBuffer[Offset]);

  /* initiate FLS read */
  Error = Fls_17_Dmu_Read(Position, GcReadWriteBufferPtr, ReadLength);
  /* [cover parentID={237CA2B3-0CA0-466b-8FD3-D5F4B8D74AB2}][/cover] */
  if(Error == E_OK)
  {
    StateDataPtr->FeeLastReadSize = ReadLength;
    StateDataPtr->FeeIntrJobStatus = FEE_JOB_REQSTD;
    StateDataPtr->FeeIntrJob = FEE_READ_JOB;
  }
  else
  {
    BlockIndex = Fee_lGetUsrBlockIndex(
                   StateDataPtr->FeeGcCurrBlkInfo.BlockNumber);
    /* [cover parentID={E42C759A-946D-4896-B9A5-28A3FE05189D}]
    Call error handler with GC read error. Pass the block index for which read
    error is occurred. This block will be marked as inconsistent and discarded
    from the GC.
    [/cover] */
    Fee_lGcErrorHandler(FEE_GC_READ, BlockIndex);
  }
}

/*******************************************************************************
** Syntax : static uint8 Fee_lGcWrite(const Fls_17_Dmu_AddressType Position,  **
**                                    const uint16 Offset)                    **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  Position: Dflash Address to write                       **
**                    Offset: Offset of read write buffer (page0 / page1)     **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  uint8                                                   **
**                 FEE_GC_E_OK: Write request is accepted by underlying flash **
**                  driver                                                    **
**                 FEE_GC_WRITE : Write request is accepted by underlying     **
**                 flash driver                                               **
** Description : Gives a write request and sets the error flag                **
**               in case of an error.                                         **
*******************************************************************************/
/* [cover parentID={E8C77A0A-929A-4ef6-A01E-23CCE785236A}]
Fee_lGcWrite
[/cover] */
/* [cover parentID={CA65836F-F856-4887-AF12-D1A503ACDB17}][/cover] */
static uint8 Fee_lGcWrite(const Fls_17_Dmu_AddressType Position,
                          const uint16 Offset)
{
  Std_ReturnType      ReturnValueFls;
  Fee_StateDataType  *StateDataPtr;
  const uint8              *GcReadWriteBufferPtr;
  uint8               Error;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  Error = FEE_GC_E_OK;

  GcReadWriteBufferPtr = &(StateDataPtr->FeeGcReadWriteBuffer[Offset]);
  StateDataPtr->FeeIntrJobStatus = FEE_JOB_REQSTD;
  StateDataPtr->FeeIntrJob = FEE_WRITE_JOB;
  StateDataPtr->FeeLastWriteSize = StateDataPtr->FeeLastReadSize;
  /* [cover parentID={DE930912-BB92-4303-B56F-424CAA503224}][/cover] */
  ReturnValueFls = Fls_17_Dmu_Write(Position,
                                    GcReadWriteBufferPtr,
                                    StateDataPtr->FeeLastWriteSize);
  /* if the Fls routine did not accept the request         */
  /* then report production error and Set GC state to FEE_GC_IDLE */
  /* [cover parentID={5888CF87-26FF-41f9-8C05-06ADBB67926A}][/cover] */
  if(ReturnValueFls == E_NOT_OK)
  {
    /* Any failure from FLS (both DET,production error) will trigger Illegal notification
       and FEE production error. Note Fee_JobErrorNotification will NOT raise any
       illegal notification / production error in case of internal job failures */
    Error = FEE_GC_WRITE;
  }

  return(Error);
}

/******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lGcRequested(void)                         **
**                                                                           **
** Service ID:  NA                                                           **
**                                                                           **
** Sync/Async:  Synchronous                                                 **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in) :  None                                                   **
**                                                                           **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    :  None                                                   **
**                                                                           **
** Description : This routine is responsible for handling Garbage Collection **
**                GC REQUESTED state                                         **
******************************************************************************/
/* [cover parentID={E59E08F7-AD94-4fb4-B247-A6F1C3D085F8}][/cover] */
LOCAL_INLINE void Fee_lGcRequested(void)
{
  Fee_CacheType         *CachePtr;
  Fee_StateDataType     *StateDataPtr;
  Fee_CacheType         *UnconfigBlockPtr;
  uint16                 BlockCount;
  uint8                  GcState;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  /* Initialize the copied status for all the logical blocks */
  CachePtr = StateDataPtr->FeeBlockInfo;
  BlockCount = FEE_RESET;

  do
  {
    CachePtr->Status.Copied = FEE_RESET;
    CachePtr->Status.PrevCopyCopied = FEE_RESET;
    BlockCount++;

    CachePtr++;
  } while(BlockCount != Fee_CfgPtr->FeeBlkCnt);

  /* Update the source and destination pointers based on the current sector */
  if(StateDataPtr->FeeStatusFlags.FeeCurrSector == (uint32)FEE_SECTOR0)
  {
    StateDataPtr->FeeGcDestAddr = StateDataPtr->FeeSectorInfo[1].NextFreeWLAddr;
    StateDataPtr->FeeGcSrcAddr = FEE_DFLASH_BANK0_BASE;
  }
  else
  {
    StateDataPtr->FeeGcDestAddr = StateDataPtr->FeeSectorInfo[0].NextFreeWLAddr;
    StateDataPtr->FeeGcSrcAddr = FEE_DFLASH_BANK1_BASE;
  }
  StateDataPtr->FeeBlkPageCount = FEE_RESET;
  StateDataPtr->FeeStatusFlags.FeeBlkModified = FEE_RESET;
  StateDataPtr->FeeGCCopyIndex = FEE_RESET;
  /* Functionality to take care of unconfigured blocks starts ******/

  GcState = FEE_GC_START_COPY;

  StateDataPtr->FeeGcBlkIndexInWL = FEE_RESET;

  /* Clear the copied status of un-configured blocks */
  /* [cover parentID={1D42BAE6-EE9D-4cb7-9420-35D5764EE134}]
  Check for unconfigured blocks
  [/cover] */
  if ((Fee_CfgPtr->FeeGCConfigSetting.FeeUnconfigBlock ==
       FEE_UNCONFIG_BLOCK_KEEP)
      && (StateDataPtr->FeeUnConfigBlockCount != FEE_RESET))
  {
    BlockCount = FEE_RESET;

    while(BlockCount < StateDataPtr->FeeUnConfigBlockCount)
    {

      UnconfigBlockPtr = &(StateDataPtr->FeeBlockInfo[(Fee_CfgPtr->FeeBlkCnt
                           + BlockCount)]);
      UnconfigBlockPtr->Status.Copied = FEE_RESET;
      BlockCount++;
    }

    StateDataPtr->FeeGCUnconfigBlkCopyIndex = FEE_RESET;
    GcState = FEE_GC_UNCFG_START_COPY;
  }

  StateDataPtr->FeeGcState = GcState;
}

/******************************************************************************
** Syntax : static void Fee_lGcPrologue(void)                                **
**                                                                           **
** Service ID:                                                               **
**                                                                           **
** Sync/Async:  Asynchronous                                                 **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in) :  None                                                   **
**                                                                           **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    :  None                                                   **
**                                                                           **
** Description : This routine is responsible for handling transitions from   **
** FEE_GC_UNCONFIG_BLOCK_READ_NXTPAGE and  FEE_GC_COPY_READ_NXTPAGE states.  **
** The transitions from the above states are handled as Prologue and not as  **
** part of the state itself. This is to avoid one main cycle delay           **
** in executing the next pass state (FEE_GC_UNCONFIG_BLOCK_WRITE or          **
** FEE_GC_START_COPY_WRITE)                                                  **
******************************************************************************/
/* [cover parentID={4070EA65-5A60-4635-8CC7-DC52B26CC648}][/cover] */
static void Fee_lGcPrologue(void)
{
  Fee_StateDataType     *StateDataPtr;
  uint16                 BlockIndex;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  /* [cover parentID={10B1867E-75B8-4456-A209-2A454D1EFF06}][/cover] */
  if (StateDataPtr->FeeIntrJobStatus == FEE_JOB_DONE)
  {
    /* [cover parentID={C0DAA55F-B277-4d13-B18F-4AD45A09418D}][/cover] */
    if (StateDataPtr->FeeGcState == FEE_GC_UNCFG_COPY_READ_NXTPAGE)
    {
      /* Reset the job status */
      StateDataPtr->FeeIntrJobStatus = FEE_JOB_IDLE;
      /* [cover parentID={C1D9507B-B82A-496a-A8CB-41551D958965}][/cover] */
      if(StateDataPtr->FeeIntrJobResult == FEE_JOB_FAIL)
      {
        /* [cover parentID={5EF6959E-A0F5-435a-B8B9-0DD93282D768}][/cover] */
        BlockIndex = Fee_lGetUsrBlockIndex(
                       StateDataPtr->FeeGcCurrBlkInfo.BlockNumber);
        /* [cover parentID={F607CD30-2BFD-4c58-8DCE-2BB53AB3FD5A}][/cover] */
        Fee_lGcErrorHandler(FEE_GC_READ, BlockIndex);
      }
      else
      {
        StateDataPtr->FeeGcState = FEE_GC_UNCFG_COPY_WRITE;
      }
    }
    /* [cover parentID={819EF908-7583-4ba5-B392-1E11AC4ED3C7}][/cover] */
    else if (StateDataPtr->FeeGcState == FEE_GC_COPY_READ_NXTPAGE)
    {
      StateDataPtr->FeeIntrJobStatus = FEE_JOB_IDLE;
      /* [cover parentID={7BD3222C-EDD7-4871-8188-9387C222901E}][/cover] */
      if(StateDataPtr->FeeIntrJobResult == FEE_JOB_FAIL)
      {
        BlockIndex = Fee_lGetUsrBlockIndex(
                       StateDataPtr->FeeGcCurrBlkInfo.BlockNumber);
        Fee_lGcErrorHandler(FEE_GC_READ, BlockIndex);
      }
      else
      {
        StateDataPtr->FeeGcState = FEE_GC_COPY_WRITE;
      }
    }
    else
    {
      /* dummy else */
    }
  }
}

/*******************************************************************************
** Syntax : static void Fee_lGcDiscardUnconfigBlk(void)                       **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async: Synchronous                                                    **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : uint16 Block index in cache table                        **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  void                                                    **
**                                                                            **
** Description : This function discards the un-configured block               **
**                                                                            **
*******************************************************************************/
/* [cover parentID={B1EFBE21-A5EE-42b3-8409-37091234EE38}]
Fee_lGcDiscardUnconfigBlk
[/cover] */
/* [cover parentID={8CAAE484-4DC8-4a7f-B7CD-A9715EF088CC}][/cover] */
static void Fee_lGcDiscardUnconfigBlk(const uint16 Index)
{
  Fee_StateDataType     *StateDataPtr;
  Fee_CacheType         *UnconfigBlockPtr;
  uint16                 BlockIndex;
  uint16                 Count;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  /* Check if the block index is in range. if not find the block index using
  the FeeGcCurrBlkInfo. FeeGcCurrBlkInfo is updated only we are able read the
  header of the block properly. In case we are not able read header of block
  given index will have valid value. */
  if(FEE_LOG_BLOCK_NOT_FOUND != Index)
  {
    BlockIndex = Index;
    UnconfigBlockPtr = &(StateDataPtr->FeeBlockInfo[Index]);
  }
  else
  {
    /*Find the block index for unconfigured block*/
    BlockIndex = FEE_RESET;
    UnconfigBlockPtr = &(StateDataPtr->FeeBlockInfo[Fee_CfgPtr->FeeBlkCnt]);
    while((BlockIndex < (StateDataPtr->FeeUnConfigBlockCount)) &&
          (StateDataPtr->FeeGcCurrBlkInfo.BlockNumber !=
           UnconfigBlockPtr->BlockNumber))
    {
      BlockIndex++;
      UnconfigBlockPtr++;
    }
  }

  /* Discard the block from cache table and reduce the number of un-configured
  by 1 and update the cache table for un-configured block */
  (StateDataPtr->FeeUnConfigBlockCount)--;
  Count = FEE_RESET;
  /* [cover parentID={A9439147-E612-4046-9A97-DE873B2DA3DB}][/cover] */
  while(BlockIndex < (StateDataPtr->FeeUnConfigBlockCount))
  {

    UnconfigBlockPtr[Count].BlockNumber =
      UnconfigBlockPtr[Count + FEE_ONE].BlockNumber;

    UnconfigBlockPtr[Count].Address =
      UnconfigBlockPtr[Count + FEE_ONE].Address;

    BlockIndex++;
    Count ++;

  }
}

/*******************************************************************************
** Syntax : static void Fee_lGcDiscardConfigBlk(const uint16 Index)           **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async: Synchronous                                                    **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  uint16 Block index in cache table.                      **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  void                                                    **
**                                                                            **
** Description : This function discards the configured block which has the ECC**
**               error while reading the block during GC.Also mark this block **
**               as inconsistent in cache table.                              **
**                                                                            **
*******************************************************************************/
/* [cover parentID={1370397F-B0B8-4f50-80A8-04D9EA12F60E}]
Fee_lGcDiscardConfigBlk
[/cover] */
/* [cover parentID={AECD8CC8-8CD5-4f72-A4A6-EA8B60DD9D50}][/cover] */
static void Fee_lGcDiscardConfigBlk(const uint16 Index)
{
  Fee_StateDataType     *StateDataPtr;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /*Mark the block as inconsistent*/
  StateDataPtr->FeeBlockInfo[Index].Status.Consistent = FEE_RESET;
  StateDataPtr->FeeBlockInfo[Index].Address = FEE_RESET;
}

/*******************************************************************************
** Syntax : static boolean Fee_lGcCheckBlkCopy(void)                          **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  boolean RetVal:                                         **
**                    TRUE: There is a block to be copied                     **
**                    FALSE:No block is to be copied                          **
**                                                                            **
** Description : This routine checks the cache table starting from the        **
**  FeeGCCopyIndex and finds if any block needs to be copied                  **
*******************************************************************************/
/* [cover parentID={382A336E-F484-4366-A128-016FB29EAAE6}][/cover] */
static boolean Fee_lGcCheckBlkCopy(void)
{
  Fee_StateDataType    *StateDataPtr;
  const Fee_CacheType        *CachePtr;
  uint16                BlockCount;
  boolean                 RetVal;

  RetVal = FALSE;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  BlockCount = StateDataPtr->FeeGCCopyIndex;

  CachePtr = &(StateDataPtr->FeeBlockInfo[BlockCount]);
  /* [cover parentID={C20B58DB-BA71-4e85-B000-11D95B2A9CAD}][/cover] */
  while ((RetVal == FALSE) && (BlockCount != Fee_CfgPtr->FeeBlkCnt))
  {
    /* If block is consistent and not copied */
    /* [cover parentID={DF5B1B7F-7A7D-406c-9B0D-6B048833674B}][/cover] */
    if ((CachePtr->Status.Consistent == (uint32)FEE_SET ) &&
        (CachePtr->Status.Copied == (uint32)FEE_RESET))
    {
      RetVal = TRUE ;
    }
    else
    {
      BlockCount++;

      CachePtr++;
    }
  }
  StateDataPtr->FeeGCCopyIndex = BlockCount;

  return(RetVal);
}

/*******************************************************************************
** Syntax : static void Fee_lGcStartCopy(void)                                **
**                                                                            **
** Service ID:  NA                                                            **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This routine is responsible for handling Garbage Collection  **
**                GC START COPY state                                         **
*******************************************************************************/
/* [cover parentID={CF14D4EB-C9EE-45f2-A48B-B7EB2D144604}][/cover] */
static void Fee_lGcStartCopy(void)
{
  Fee_CacheType         *CachePtr;
  const Fee_CacheType         *UnconfigBlockPtr;
  Fee_StateDataType     *StateDataPtr;
  uint32                 DestAddr;
  uint16                 Offset;
  uint16                 Index;
  boolean                StateFlag;
  Std_ReturnType         Error;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* [cover parentID={282D6316-73B6-4560-87AA-6A7C70648F97}][/cover] */
  if (StateDataPtr->FeeIntrJobStatus == FEE_JOB_DONE)
  {
    StateDataPtr->FeeIntrJobStatus = FEE_JOB_IDLE;
    /* [cover parentID={10B10B9F-CEA0-44c5-9E14-879CC8744A9E}][/cover] */
    if(StateDataPtr->FeeIntrJobResult == FEE_JOB_FAIL)
    {
      Index = Fee_lGetUsrBlockIndex(StateDataPtr->FeeGcCurrBlkInfo.BlockNumber);
      Fee_lGcErrorHandler(FEE_GC_READ, Index);
    }
    else
    {
      /* [cover parentID={A79A03B0-F737-4b78-8D0A-49FFADFDB102}][/cover] */
      if(StateDataPtr->FeeGcState == FEE_GC_START_COPY)
      {
        StateDataPtr->FeeGcState = FEE_GC_COPY_WRITE;
      }
      else
      {
        StateDataPtr->FeeGcState = FEE_GC_UNCFG_COPY_WRITE;
      }
    }
  }
  /* [cover parentID={727CE9C0-9FB9-4749-8015-188C8770D8B2}][/cover] */
  else
  {
    /* i.e. StateDataPtr->FeeGcState == FEE_GC_START_COPY */
    DestAddr = (uint32)StateDataPtr->FeeGcDestAddr;

    /* No more blocks to be copied in the current pass -
       check if any block is modified during GC */

    if(StateDataPtr->FeeGcState == FEE_GC_UNCFG_START_COPY)
    {
      /* [cover parentID={16F6A5B6-A50A-4305-83EE-012DF6EEEE1A}] [/cover] */
      StateFlag = Fee_lGcCheckUnconfigBlkCopy();
    }
    else /* if(StateDataPtr->FeeGcState == FEE_GC_START_COPY) */
    {
      /* Check if there are any more blocks to be copied */
      /* [cover parentID={0F4E7119-308D-462f-897A-8FF41BA2AFCB}] [/cover] */
      StateFlag = Fee_lGcCheckBlkCopy();
      /* [cover parentID={C9AE3945-0139-4dc2-AB7A-76ADF8E5006A}][/cover] */
      if (StateFlag == (boolean)FALSE)
      {
        /* if any of the logical blocks were modified */
        /* [cover parentID={76CBC2E7-1D59-4c40-A6D5-77FFFC8D8E53}][/cover] */
        if(StateDataPtr->FeeStatusFlags.FeeBlkModified == (uint32)FEE_SET )
        {
          StateDataPtr->FeeStatusFlags.FeeBlkModified = FEE_RESET;
          StateDataPtr->FeeGCCopyIndex = FEE_RESET;
          /* [cover parentID={6F04A339-1529-49c2-85DD-F9999B057308}][/cover] */
          StateFlag = Fee_lGcCheckBlkCopy();
        }
      }
    }

    /* Block copying not yet completed */
    /* [cover parentID={C37C25E8-0F6E-4122-B453-0FA545BA3E9E}][/cover] */
    if(StateFlag == (boolean)TRUE)
    {
      /* [cover parentID={29F68CA1-B0B1-4d12-A104-0AA31D3263C4}][/cover] */
      if(StateDataPtr->FeeGcState == FEE_GC_UNCFG_START_COPY)
      {

        UnconfigBlockPtr = &(StateDataPtr->FeeBlockInfo[(Fee_CfgPtr->FeeBlkCnt)
                             + (StateDataPtr->FeeGCUnconfigBlkCopyIndex)]);

        StateDataPtr->FeeGcSrcAddr = UnconfigBlockPtr->Address;

        /*Store cache index of block for passing in Fee_lGcErrorHandler in case
        of read error while reading header page  */
        Index = StateDataPtr->FeeGCUnconfigBlkCopyIndex;

      }

      else /* FeeGcState == FEE_GC_START_COPY */
      {
        CachePtr = &(StateDataPtr->FeeBlockInfo[StateDataPtr->FeeGCCopyIndex]);
        StateDataPtr->FeeGcSrcAddr = CachePtr->Address;

        /*Store cache index of block for passing in Fee_lGcErrorHandler in case
        of read error while reading header page  */
        Index = StateDataPtr->FeeGCCopyIndex;
      }
      StateDataPtr->FeeBlkPageCount = FEE_RESET;
      Offset = (uint16) (DestAddr & (uint32)FEE_DFLASH_WORDLINE_SIZE_1);
      /* [cover parentID={96E0CB38-D82C-4718-B8F0-EF0D09BE9A29}][/cover] */
      if (Offset == FEE_ZERO)
      {
        Fee_lClearFeeGcReadWriteBuffer();
      }
      /* Fill Current Block information */
      /* Read the header (first 8bytes) of the block to update the
        GC Current Block information */

      /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for interfacing with
      FLS.FEE is passing parameters to FLS APIs, casting is needed to match with
      the Fls API prototype. FeeGcReadWriteBuffer is member of Fee_StateDataType
      structure. FeeGcReadWriteBuffer is 4 byte aligned.*/
      /* [cover parentID={AFC4BD68-1B6A-4ad2-9BA4-499169C180C5}][/cover] */
      Error = Fls_17_Dmu_ReadWordsSync(\
                   (Fls_17_Dmu_AddressType)StateDataPtr->FeeGcSrcAddr, \
                   (uint32 *)(&(StateDataPtr->FeeGcReadWriteBuffer[Offset])), \
                   (Fls_17_Dmu_LengthType)\
                   (FEE_DFLASH_PAGE_SIZE / FEE_DFLASH_WORD_SIZE));
      /* [cover parentID={42A579A4-363A-403a-A555-168792D77DF4}][/cover] */
      if(Error == E_OK)
      {
        /* [cover parentID={C3E77B1B-B10B-47f8-BA17-68AB83EB0B38}][/cover] */
        Fee_lUpdateGcCurrBlockInfo();
        /* [cover parentID={97257093-6C41-45ea-B83B-5D58B0FFDB10}][/cover] */
        Fee_lGcRead((Fls_17_Dmu_AddressType)
                    (StateDataPtr->FeeGcSrcAddr), Offset);
      }
      else
      {
        /*Not able read the block , trigger the GC_READ_DEM and discard the
        block*/
        /* [cover parentID={6E143EFD-4DFF-40fb-8539-03217671E641}][/cover] */
        Fee_lGcErrorHandler(FEE_GC_READ, Index);

      }

    }
    /* Finished copying all the configured OR unconfigured blocks */
    else
    {
      /* [cover parentID={F2E9DFD4-FDCE-4b4d-B2DB-80A41DC340D9}][/cover] */
      if (Fee_lIsWLBeginning(DestAddr) != FEE_NEW_WL_BEGIN)
      {
        DestAddr = Fee_lGetNextWLAddr(DestAddr);
      }
      Fee_lClearFeeGcReadWriteBuffer();
      StateDataPtr->FeeGcDestAddr = DestAddr;

      /* Clear the compare fail count*/
      StateDataPtr->FeeIntrJobFailCount = FEE_RESET;
      /* [cover parentID={CEC47DC8-6924-40a5-9855-C2DF63A4AC9D}][/cover] */
      if(StateDataPtr->FeeGcState == FEE_GC_START_COPY)
      {
        /* Finished copying all the configured blocks */
        /* Mark the previous copy of blocks as inconsistent for the blocks which
        are not updated during GC - this means that only the latest data is
        copied during GC and there is no previous copy in the new sector */
        Index = FEE_RESET;
        do
        {
          CachePtr = &(StateDataPtr->FeeBlockInfo[Index]);
          if (CachePtr->Status.PrevCopyCopied == (uint32)FEE_RESET)
          {

            CachePtr->PrevCopyAddress = FEE_RESET;
            CachePtr->Status.PrevCopyValid = FEE_RESET;
            CachePtr->Status.PrevCopyConsistent = FEE_RESET;
            CachePtr->Status.PrevCopyCopied = FEE_RESET;
          }
          Index++;
        } while(Index < Fee_CfgPtr->FeeBlkCnt);

        /* Move to next state */
        StateDataPtr->FeeGcState = FEE_GC_MARK_SECTOR1_V_SP;
      }
      else
      {
        /* Finished copying all the unconfigured blocks */
        /* Now copy all the configured blocks */
        StateDataPtr->FeeGcState = FEE_GC_START_COPY;
      }
    }
  }
}

/*******************************************************************************
** Syntax : static uint8 Fee_lGcStartCopyWrite(void)                          **
**                                                                            **
** Service ID:  NA                                                            **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  uint8                                                   **
**                    FEE_GC_E_OK : No error operation is successful          **
**                    FEE_GC_WRITE: GC write operation is failed              **
**                    FEE_GC_TRIG : GC operation triggers the another GC      **
**                                  Operation                                 **
** Description : This routine is responsible for handling Garbage Collection  **
**                GC START COPY WRITE state                                   **
*******************************************************************************/
/* [cover parentID={8D5A86A2-A570-443a-B11E-1FA7E7FF2B31}][/cover] */
static uint8 Fee_lGcStartCopyWrite(void)
{
  Fee_StateDataType    *StateDataPtr;
  const Fee_GcBlkInfoType    *GcCurrBlkPtr;
  uint32                DestAddr;
  uint32                PageCount;
  uint32                FreePages;
  uint16                Offset;
  uint8                 BankNumber;
  uint8                 Error;

  Error = FEE_GC_E_OK;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  GcCurrBlkPtr = &(StateDataPtr->FeeGcCurrBlkInfo);
  /* [cover parentID={BB5587D9-1C7A-4e1f-9A97-54071C97D7CF}][/cover] */
  if (StateDataPtr->FeeIntrJobStatus == FEE_JOB_DONE)
  {
    StateDataPtr->FeeIntrJobStatus = FEE_JOB_IDLE;

    /*Check if write operation is failed due other than PVER. If yes then
    report the FEE_GC_WRITE error otherwise retry write operation. */
    /* [cover parentID={7065BEF1-7A5F-4e56-BA67-2BB6E12A557E}][/cover] */
    if((StateDataPtr->FeeIntrJobResult == FEE_JOB_FAIL) &&
        (StateDataPtr->FeeProgVerErr == FEE_RESET))
    {
      /* [cover parentID={D4B42884-BB10-49c3-9104-92022282D487}][/cover] */
      Error = FEE_GC_WRITE;
    }
    else
    {
      /* [cover parentID={27086814-0DC0-4abe-9D7C-B044D20C0513}][/cover] */
      Fee_lGcBlkCompare();
    }
  }
  /* [cover parentID={25A35889-F366-46ec-AFF7-1988A925067C}][/cover] */
  else if(StateDataPtr->FeeComparedLen != (uint16)FEE_ZERO)
  {
    /* [cover parentID={C8D3C9A8-819C-4df2-AA1A-7F2435D8D857}][/cover] */
    Fee_lGcBlkCompare();
  }
  else
  {
    /* i.e. StateDataPtr->FeeGcState == FEE_GC_COPY_WRITE */
    DestAddr = (uint32)StateDataPtr->FeeGcDestAddr;
    /* [cover parentID={C4066C1A-186B-4d26-9F99-670DA791FA4B}][/cover] */
    while(Fee_lIsUnerasableAddr(DestAddr) == TRUE)
    {
      DestAddr = Fee_lGetNextWLAddr(DestAddr);
    }
    StateDataPtr->FeeGcDestAddr = DestAddr;

    /*************** CHECK for the case of GC TRIGGERING GC *****************/
    /* [cover parentID={6B36C224-EB1F-47cb-A635-7C521CC64DBC}][/cover] */
    if (StateDataPtr->FeeBlkPageCount == FEE_ZERO)
    {
      /* Get the Destination sector - It is the sector other than curr sector*/
      BankNumber =(uint8)StateDataPtr->FeeStatusFlags.FeeCurrSector^FEE_SECTOR1;
      /* Find the free pages in the destination sector */
      FreePages = Fee_lGetFreeDFLASHPages(BankNumber, DestAddr);
      /* Get the block page count */
      PageCount = (uint32)StateDataPtr->FeeGcCurrBlkInfo.PageCount;
      /* Check if the block is crossing the threshold */
      /* [cover parentID={8B491B9B-DE7C-46fa-B333-BE009A192429}][/cover] */
      if ((boolean)TRUE == Fee_lIsSectorThresholdCrossed(FreePages, PageCount))
      {
        Error = FEE_GC_TRIG;
      }
    }
    /* [cover parentID={5013CBAE-2EDA-4edd-A716-B9A0E721B4EC}][/cover] */
    if (Error == FEE_RESET)
    {
      Offset = (uint16) (DestAddr & FEE_DFLASH_WORDLINE_SIZE_1);
      /* [cover parentID={7E1EF1A8-C413-4dc7-9244-F92675E95841}][/cover] */
      if(Offset == FEE_ZERO)
      {
        StateDataPtr->FeeGcFirstBlkNumInWL = GcCurrBlkPtr->BlockNumber;
        StateDataPtr->FeeGcBlkIndexInWL = FEE_RESET;
      }
      /* [cover parentID={88EF6E27-0D37-4e33-BE74-9113ABB802A5}][/cover] */
      if(StateDataPtr->FeeBlkPageCount == FEE_RESET)
      {
        StateDataPtr->FeeBlockStartAddr = DestAddr;
      }
      /* [cover parentID={E38394F3-429A-49db-A187-94D04DE16511}][/cover] */
      Error = Fee_lGcWrite((Fls_17_Dmu_AddressType)DestAddr, Offset);
    }
  }

  return(Error);
}

/*******************************************************************************
** Syntax : static void Fee_lGcCopyReadNxtPage(void)                          **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This routine is responsible for handling Garbage Collection  **
**                FEE_GC_COPY_READ_NXTPAGE state                              **
*******************************************************************************/
/* [cover parentID={5A35275E-BE0A-4017-9492-A74355CB54BD}]
Fee_lGcCopyReadNxtPage
[/cover] */
/* [cover parentID={E6CE4869-0645-446a-890A-E4E940C84869}][/cover] */
static void Fee_lGcCopyReadNxtPage(void)
{
  uint32                 SrcAddr;
  Fee_StateDataType     *StateDataPtr;
  uint16                 Offset;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* The transitions from this state are handled as part of Fee_lGcPrologue
     Hence only state actions are done here */

  Offset = (uint16) ((StateDataPtr->FeeGcDestAddr) &
                     (uint32)FEE_DFLASH_WORDLINE_SIZE_1);
  SrcAddr = StateDataPtr->FeeGcSrcAddr;
  /* [cover parentID={8EE90F45-4DC9-4a93-8B49-468FFB179969}][/cover] */
  while(Fee_lIsUnerasableAddr(SrcAddr) == TRUE)
  {
    SrcAddr = Fee_lGetNextWLAddr(SrcAddr);
  }
  StateDataPtr->FeeGcSrcAddr = SrcAddr;
  /* [cover parentID={570C2831-A89A-4920-B83B-D14596185FA3}][/cover] */
  Fee_lGcRead((Fls_17_Dmu_AddressType)(StateDataPtr->FeeGcSrcAddr), Offset);
}

/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lGcBlkCompare(void)                         **
**                                                                            **
** Service ID: NA                                                             **
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
** Description : Performs compare actions on FEE_GC_START_COPY_WRITE          **
**               during Garbage collection                                    **
*******************************************************************************/
/* [cover parentID={16B182B9-FE60-4d9d-AFFA-B333EFE37022}]
Fee_lGcBlkCompare
[/cover] */
/* [cover parentID={ABFF19ED-B7D1-4465-AD16-8FADF69A33D9}][/cover] */
LOCAL_INLINE void Fee_lGcBlkCompare(void)
{
  Fee_StateDataType     *StateDataPtr;
  const Fee_GcBlkInfoType     *GcCurrBlkPtr;
  Fee_CacheType         *CachePtr;
  Fee_CacheType         *UnconfigBlockPtr;
  uint32                 DestAddr;
  Fls_17_Dmu_AddressType        CompAddr;
  Fls_17_Dmu_LengthType         CompLength;
  Fls_17_Dmu_LengthType         TmpCompareLength;
  uint16                 BlockNumber;
  uint16                 Index;
  Std_ReturnType         ReturnVal;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  CachePtr = StateDataPtr->FeeBlockInfo;
  ReturnVal = E_OK;
  UnconfigBlockPtr = &(StateDataPtr->FeeBlockInfo[Fee_CfgPtr->FeeBlkCnt]);

  GcCurrBlkPtr = &(StateDataPtr->FeeGcCurrBlkInfo);

  DestAddr = StateDataPtr->FeeGcDestAddr;
  /* Compare entire WL */
  CompAddr = (Fls_17_Dmu_AddressType)Fee_lGetWLBeginning(DestAddr);

  CompLength = (StateDataPtr->FeeGcDestAddr) &
               (Fls_17_Dmu_LengthType)FEE_DFLASH_WORDLINE_SIZE_1;
  CompLength += (StateDataPtr->FeeLastWriteSize);
  TmpCompareLength = CompLength;

  CompLength -=  StateDataPtr->FeeComparedLen;
  /* [cover parentID={5F17C0EE-25ED-4649-8348-2C13F8AE82DD}][/cover] */
  if(CompLength > FEE_COMPARE_LEN_MAX)
  {
    CompLength = FEE_COMPARE_LEN_MAX;
  }

  /* [cover parentID={7ED03950-A3D6-4943-A82A-B6CD11926EA8}][/cover] */
  if(StateDataPtr->FeeProgVerErr == FEE_RESET)
  {
    /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for interfacing with
    FLS.FEE is passing parameters to FLS APIs, casting is needed to match with
    the Fls API prototype. FeeGcReadWriteBuffer is 4 byte aligned which is part
    of Fee_StateDataType.*/
    /* [cover parentID={FD88B256-3E35-4ecd-B50A-BC0E0CF92C5C}][/cover] */
    ReturnVal = Fls_17_Dmu_CompareWordsSync( \
                (CompAddr + StateDataPtr->FeeComparedLen), \
                (uint32 *)(&(StateDataPtr->FeeGcReadWriteBuffer\
                             [StateDataPtr->FeeComparedLen])), \
                (CompLength / FEE_DFLASH_WORD_SIZE));

    StateDataPtr->FeeComparedLen += (uint16)CompLength;
  }

  /* Compare failed or PVER error is set.*/
  /* [cover parentID={25A9CD53-11A4-4a71-AC5A-3E3DA94409B3}][/cover] */
  if((ReturnVal == E_NOT_OK) ||
      (StateDataPtr->FeeProgVerErr == FEE_SET))
  {
    StateDataPtr->FeeComparedLen = FEE_RESET;
    /*Reset the FeeProgVerErr flag*/
    StateDataPtr->FeeProgVerErr = FEE_RESET;
    /* [cover parentID={72657EFF-D435-4a8b-AAD1-44DDD86D5F5D}][/cover] */
    if(StateDataPtr->FeeIntrJobFailCount == FEE_RESET)
    {
      StateDataPtr->FeeIntrJobFailCount++;
      /* [cover parentID={7D6A8405-D9F4-416f-AF73-AED1E5A32112}][/cover] */
      if(StateDataPtr->FeeGcState == FEE_GC_UNCFG_COPY_WRITE)
      {
        /* [cover parentID={004D374A-B888-4250-8A68-B8D43FC0FB6D}][/cover] */
        if(StateDataPtr->FeeGcBlkIndexInWL != FEE_RESET)
        {
          /* [cover parentID={FB8D8524-A03F-4f0c-B756-CC9FCF3D2877}][/cover] */
          Fee_lHandleUnConfigGcCopyError();
        }
        StateDataPtr->FeeGcState = FEE_GC_UNCFG_START_COPY;
      }
      /* [cover parentID={C3D10F3F-2264-404c-8639-13C8EFCA19EB}][/cover] */
      else /* FeeGcState == FEE_GC_COPY_WRITE */
      {
        if(StateDataPtr->FeeGcBlkIndexInWL != FEE_RESET)
        {
          Fee_lHandleConfigGcCopyError();
        }
        StateDataPtr->FeeGcState = FEE_GC_START_COPY;
      }
      /* Switch the destination address to next to next free WL*/
      DestAddr = Fee_lGetNextWLAddr(DestAddr);
      DestAddr = Fee_lGetNextWLAddr(DestAddr);
      StateDataPtr->FeeGcDestAddr = DestAddr;
    }
    else
    {
      /* Write Fail two time raise the illegal notification.block index
      parameters is not used for write error , so passed as parameter not used.
      Block index is used only for read error to drop the block from GC process.
      */
      /* [cover parentID={3372162C-77BA-4a23-B405-D95A3FA0BC0D}][/cover] */
      Fee_lGcErrorHandler(FEE_GC_WRITE, FEE_UNUSED_PARAM);
    }
  }
  else if(StateDataPtr->FeeComparedLen != (uint16)TmpCompareLength)
  {
    /* dummy else if to skip else for in-between loops */
  }
  /* Compare successful */
  /* [cover parentID={9C0F4F7A-18C0-426c-A76B-34AB370FFC69}][/cover] */
  else
  {
    StateDataPtr->FeeComparedLen = FEE_RESET;
    StateDataPtr->FeeGcSrcAddr += StateDataPtr->FeeLastWriteSize;
    StateDataPtr->FeeGcDestAddr += StateDataPtr->FeeLastWriteSize;

    StateDataPtr->FeeBlkPageCount +=
      (Fee_PageType)(StateDataPtr->FeeLastWriteSize >> FEE_BYTE_TO_PAGE);
    /* [cover parentID={CC13B929-BBE2-4ebe-994F-872EE677245D}][/cover] */
    if (StateDataPtr->FeeBlkPageCount == (GcCurrBlkPtr->PageCount + FEE_ONE))
    {
      /* Clear the compare fail count if the block write is complete */
      /* Count shall not be cleared upon completion of previous block write */
      /* [cover parentID={104EC542-3AAC-4df4-A787-25823B8CCF52}][/cover] */
      if (GcCurrBlkPtr->BlockNumber != StateDataPtr->FeeGcPrevBlockNumber)
      {
        StateDataPtr->FeeIntrJobFailCount = FEE_RESET;
      }
      /* Update the cache table for current block */
      BlockNumber = GcCurrBlkPtr->BlockNumber;

      /* [cover parentID={6AACE9AF-A524-4ded-8EEF-2B058ECAB649}][/cover] */
      if(StateDataPtr->FeeGcState == FEE_GC_UNCFG_COPY_WRITE)
      {

        UnconfigBlockPtr = (&UnconfigBlockPtr
                            [StateDataPtr->FeeGCUnconfigBlkCopyIndex]);
        UnconfigBlockPtr->Status.Copied = FEE_SET ;
        StateDataPtr->FeeGcLWBGcSrcAddr[StateDataPtr->FeeGcBlkIndexInWL] =
          UnconfigBlockPtr->Address;
        UnconfigBlockPtr->Address = StateDataPtr->FeeBlockStartAddr;
        StateDataPtr->FeeGCUnconfigBlkCopyIndex++;

        /* Move to next state */
        StateDataPtr->FeeGcState = FEE_GC_UNCFG_START_COPY;
      }
      else /* FEE_GC_COPY_WRITE */
      {
        Index = Fee_lGetUsrBlockIndex(BlockNumber);

        CachePtr = &(CachePtr[Index]);
        CachePtr->Status.Copied = FEE_SET ;
        StateDataPtr->FeeGcLWBGcSrcAddr[StateDataPtr->FeeGcBlkIndexInWL] =
          CachePtr->Address;
        CachePtr->Address = StateDataPtr->FeeBlockStartAddr;
        StateDataPtr->FeeGCCopyIndex++;

        /* Move to next state */
        StateDataPtr->FeeGcState = FEE_GC_START_COPY;
      }

      /* Update LastBlock with Current block info */
      StateDataPtr->FeeGcPrevBlockNumber = GcCurrBlkPtr->BlockNumber;

      (StateDataPtr->FeeGcBlkIndexInWL)++;
    }
    else
    {
      /* [cover parentID={3BA076CC-FA0D-46b7-85EA-B2827E75E4A1}][/cover] */
      if(StateDataPtr->FeeGcState == FEE_GC_UNCFG_COPY_WRITE)
      {
        StateDataPtr->FeeGcState = FEE_GC_UNCFG_COPY_READ_NXTPAGE;
      }
      else /* FEE_GC_COPY_WRITE */
      {
        StateDataPtr->FeeGcState = FEE_GC_COPY_READ_NXTPAGE;
      }
    }
  }
}

/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lHandleUnConfigGcCopyError(void)            **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  void                                                    **
**                                                                            **
** Description : This function handles un-configured block's copy error       **
**                                                                            **
*******************************************************************************/
/* [cover parentID={B02A666C-094D-47c0-9DB6-AC87FEB69334}]
Fee_lHandleUnConfigGcCopyError
[/cover] */
/* [cover parentID={CD7D7018-0024-403e-B8AF-5E8FADC4AE95}][/cover] */
LOCAL_INLINE void Fee_lHandleUnConfigGcCopyError(void)
{
  Fee_StateDataType     *StateDataPtr;
  Fee_CacheType         *UnconfigBlockPtr;
  uint16                 BlockIndex;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  UnconfigBlockPtr = &(StateDataPtr->FeeBlockInfo[Fee_CfgPtr->FeeBlkCnt]);
  BlockIndex = FEE_RESET;

  /* Find the index of the first affected un-configured block */
  /* [cover parentID={02EABA1E-6DB2-4303-8005-1CD87E8531FE}][/cover] */
  while((BlockIndex < (StateDataPtr->FeeUnConfigBlockCount)) &&
        ((UnconfigBlockPtr->BlockNumber) != StateDataPtr->FeeGcFirstBlkNumInWL))
  {
    BlockIndex++;

    UnconfigBlockPtr++;
  }
  StateDataPtr->FeeGCUnconfigBlkCopyIndex = BlockIndex;

  /* Clear the Copied status of all the affected un-configured blocks */
  /* [cover parentID={6814F2C0-D04B-406b-9D17-D05DED0A8D8E}][/cover] */
  for(BlockIndex = FEE_RESET;
      BlockIndex < StateDataPtr->FeeGcBlkIndexInWL;
      BlockIndex++)
  {
    UnconfigBlockPtr->Status.Copied = FEE_RESET;
    UnconfigBlockPtr->Address = StateDataPtr->FeeGcLWBGcSrcAddr[BlockIndex];

    UnconfigBlockPtr++;
  }
  StateDataPtr->FeeGcBlkIndexInWL = FEE_RESET;
}

/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lHandleConfigGcCopyError(void)              **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  void                                                    **
**                                                                            **
** Description : This function handles configured block's copy error. Undoes  **
** the markings for the configured blocks (in the WL) affected during the GC  **
** copy operation.                                                            **
**                                                                            **
*******************************************************************************/
/* [cover parentID={BEA2009F-01BC-4277-A216-C597C15BAB19}]
Fee_lHandleConfigGcCopyError
[/cover] */
/* [cover parentID= {0D2CAF2F-71A1-4693-A275-6DF81B063430}][/cover] */
LOCAL_INLINE void Fee_lHandleConfigGcCopyError(void)
{
  Fee_StateDataType     *StateDataPtr;
  Fee_CacheType         *CachePtr;
  uint16                 BlockIndex;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  BlockIndex = Fee_lGetUsrBlockIndex(StateDataPtr->FeeGcFirstBlkNumInWL);
  CachePtr = &(StateDataPtr->FeeBlockInfo[BlockIndex]);

  StateDataPtr->FeeGCCopyIndex = BlockIndex;
  /* [cover parentID={7F203811-F285-4e5f-B71C-609EF062B2E5}][/cover] */
  for(BlockIndex = FEE_RESET;
      BlockIndex < StateDataPtr->FeeGcBlkIndexInWL;
      BlockIndex++)
  {
    /* [cover parentID={9327FB93-4E60-4616-9E79-1A483AA10E84}][/cover] */
    if(CachePtr->Status.Copied == (uint32)FEE_SET )
    {
      /* Latest copy not available. Move GcLogBlkCount to previous block Index
       and switch to Start Copy state */
      CachePtr->Status.Copied = FEE_RESET;
      CachePtr->Address = StateDataPtr->FeeGcLWBGcSrcAddr[BlockIndex];
    }
    else
    {
      /* Latest copy of the block is available: no need to copy the affected
      previous block.Just make the PrevCopyStatus as zero. This is needed to
      mark the affected previous copy as inconsistent */
      CachePtr->Status.PrevCopyCopied = FEE_RESET;
    }

    CachePtr++;
  }
  StateDataPtr->FeeGcBlkIndexInWL = FEE_RESET;
}

/*******************************************************************************
** Syntax : static uint8 Fee_lGcErasePrevSector(const uint8 GcState)          **
**                                                                            **
** Service ID:  NA                                                            **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  GcState: Current Gc State                               **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  uint8                                                   **
**                    FEE_GC_E_OK : No error erase operation is successful    **
**                    FEE_GC_ERASE: GC Erase request is not accepted by flash **
**                    driver or erase operation failed                        **
** Description : This routine is responsible for handling Garbage Collection  **
**    FEE_GC_ERASE_PREV_SECTOR / FEE_GC_INIT_ERASE_PREV_SECTOR state          **
*******************************************************************************/
/* [cover parentID={2EF44D40-9EF0-4773-ACE9-8DB14FDA91F4}]
Fee_lGcErasePrevSector
[/cover] */
/* [cover parentID={A094A9DA-0768-46ab-A1C1-750A8678818A}][/cover] */
static uint8 Fee_lGcErasePrevSector(const uint8 GcState)
{
  Fee_StateDataType   *StateDataPtr;
  Std_ReturnType       ReturnValueFls;
  uint8                Error;
  uint32                BankNumber;

  Error = FEE_GC_E_OK;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  /* [cover parentID={676FCD6E-C364-4e19-BE01-1ACF19024A84}][/cover] */
  if (StateDataPtr->FeeIntrJobStatus == FEE_JOB_DONE)
  {
    StateDataPtr->FeeIntrJobStatus = FEE_JOB_IDLE;
    /* Check if Erase operation is failed because of EVR bit set.If yes then
    do set GC error. This is done to find out unerasble WL address. */
    /* [cover parentID={2E001B9E-9063-41b6-B1E6-A20E1F3CCB66}][/cover] */
    /* [cover parentID={3DE3BF16-2592-41c1-8F8F-6089376533F9}][/cover] */
    if((StateDataPtr->FeeIntrJobResult == FEE_JOB_FAIL) &&
        (StateDataPtr->FeeEraseVerErr == FEE_RESET ))
    {
      Error = FEE_GC_ERASE;
      StateDataPtr->FeeIntrJobFailCount = FEE_RESET;
    }
    else if(StateDataPtr->FeeIntrJobResult == FEE_JOB_PASS)
    {
      if(GcState == FEE_GC_ERASE_PREV_SECTOR)
      {
        StateDataPtr->FeeGcState = FEE_GC_MARK_SECTOR0_E_SP;
      }
      /*  Case FEE_GC_INIT_ERASE_PREV_SECTOR */
      else
      {
        /* Erase of previous sector is happening as part of INIT GC.
           The FeeStateCount shall be incremented by 2 to mark one sector
           erase. Increment FeeStateCount by 1 here. FeeStateCount is
           incremented again while preparing the state page buffer in
           FEE_GC_INIT_MARK_SECTOR0_E_SP */
        StateDataPtr->FeeStateCount += FEE_ONE;
        StateDataPtr->FeeGcState = FEE_GC_INIT_MARK_SECTOR0_E_SP;
      }

      /*Erase is successful , reset the un-erasable WL address information
      for this sector. */
      if(StateDataPtr->FeeGcDestAddr == FEE_DFLASH_BANK1_BASE)
      {
        BankNumber = FEE_SECTOR1;
      }
      else
      {
        BankNumber = FEE_SECTOR0;
      }
      StateDataPtr->FeeSectorInfo[BankNumber].UnerasableWLCount = FEE_RESET;
      StateDataPtr->FeeSectorInfo[BankNumber].UnerasableWLAddr[0] = FEE_RESET;
      StateDataPtr->FeeSectorInfo[BankNumber].UnerasableWLAddr[1] = FEE_RESET;

      StateDataPtr->FeeIntrJobFailCount = FEE_RESET;

    }
    else
    {
      /* No need to check FeeEraseVerErr,because code flow will reach here
      when FeeEraseVerErr and erase operation is failed. Also when erase
      operation is successful in this FeeEraseVerErr will be 0 */
      /* [cover parentID={965B80E7-1CC2-4054-AAD9-4A94D566E6B1}][/cover] */
      StateDataPtr->FeeEraseVerErr = FEE_RESET;

      /*Check if the erase is failed 1st time, if yes then incerement the fail
      count to retry the erase operation.*/
    /* [cover parentID={C1B7D908-7550-4306-A745-AD9DA024E336}][/cover] */
      if(StateDataPtr->FeeIntrJobFailCount != FEE_RESET)
      {
        /*Erase operation is failed 2nd time. Scan the sector for number of
        failed WL. If the number is greater than 2 then raise the illegal
        notification.*/
        Fee_lGcEraseCompare(GcState);
      }
      else
      {
        StateDataPtr->FeeIntrJobFailCount++;
      }

    }
  }
  else if(StateDataPtr->FeeSectorCount > (uint8)FEE_ZERO)
  {
    /* [cover parentID={556CCD93-EE5A-46fd-89A8-0802E595F565}][/cover] */
    Fee_lGcEraseCompare(GcState);
  }
  else
  {
    /* i.e. StateDataPtr->FeeGcState == FEE_GC_ERASE_PREV_SECTOR or
                                      FEE_GC_INIT_ERASE_PREV_SECTOR  */
    StateDataPtr->FeeIntrJobStatus = FEE_JOB_REQSTD;
    StateDataPtr->FeeIntrJob = FEE_ERASE_JOB;
    /* [cover parentID={FD945D9E-9FDC-49ae-B4E7-B80DA01EFAF8}][/cover] */
    ReturnValueFls = Fls_17_Dmu_Erase(
                       (Fls_17_Dmu_AddressType)StateDataPtr->FeeGcDestAddr,
                       (Fls_17_Dmu_LengthType)FEE_DFLASH_SECTOR_SIZE);

    /* if the Fls routine did not accept the request */
    /* [cover parentID={8E360F1F-6835-4c54-BB4D-D329B649C190}][/cover] */
    if(ReturnValueFls == E_NOT_OK)
    {
      /* Any failure from FLS (both DET,production error) will trigger Illegal 
      notification and FEE production error */
      Error = FEE_GC_ERASE;
    }
  }

  return(Error);
}/*End of Fee_lGcErasePrevSector*/


/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lGcEraseCompare(const uint8 GcState)        **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  GcState: Current GC State                               **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : Performs state transitions from FEE_GC_ERASE_PREV_SECT or    **
**  FEE_GC_INIT_ERASE_PREV_SECTOR during Garbage collection                   **
*******************************************************************************/
/* [cover parentID={6D565FB7-C76C-43d3-8CEB-73748C03F1E4}][/cover] */
LOCAL_INLINE void Fee_lGcEraseCompare(const uint8 GcState)
{
  Fee_StateDataType    *StateDataPtr;
  uint32                BankNumber;
  Std_ReturnType        ReturnVal;
  uint8                 NewGcState;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  /* [cover parentID={5D107372-3476-4f69-A312-D69EAA6FD26E}][/cover] */
  if(StateDataPtr->FeeSectorCount == 0U)
  {
    StateDataPtr->FeeUnErasableWLAddrTemp[0] = FEE_RESET;
    StateDataPtr->FeeUnErasableWLAddrTemp[1] = FEE_RESET;
    StateDataPtr->FeeUnErasableWLCountTemp = FEE_RESET;
  }

  if(StateDataPtr->FeeGcDestAddr == FEE_DFLASH_BANK1_BASE)
  {
    BankNumber = FEE_SECTOR1;
  }
  else
  {
    BankNumber = FEE_SECTOR0;
  }
  /* [cover parentID={7CF3728A-3577-4582-9375-96CB793399A0}]
  Verify erase of the flash sector
  [/cover] */
  ReturnVal = Fls_17_Dmu_VerifySectorErase(StateDataPtr->FeeGcDestAddr,
              &(StateDataPtr->FeeUnErasableWLAddrTemp[0]),
              &(StateDataPtr->FeeUnErasableWLCountTemp),
              StateDataPtr->FeeSectorCount);
  /* [cover parentID={3309023F-BD55-41ac-8B15-3B249B51F096}][/cover] */
  if(ReturnVal == E_NOT_OK)
  {
    /* [cover parentID={B7FCE4D1-0B08-471e-A477-F8504E2424B3}]
    Call the error handler, pass the block address as block not found
    [/cover] */
    /* block index is not used for erase error , so passed as parameter unused.
    Block index is used only for read error to drop the block from GC process.
    */
    StateDataPtr->FeeIntrJobFailCount = FEE_RESET;
    Fee_lGcErrorHandler(FEE_GC_ERASE, FEE_UNUSED_PARAM);
  }
  else
  {
    StateDataPtr->FeeSectorCount++;

    /*MISRA2012_RULE_10_4_JUSTIFICATION:Typecasting is done. Types are same */
    /* [cover parentID={8F64C060-9DC8-4dfc-8B33-11698DA70942}][/cover] */
    if(StateDataPtr->FeeSectorCount == (uint8)FLS_ERASE_SECTORS)
    {
      StateDataPtr->FeeSectorInfo[BankNumber].UnerasableWLCount =
        StateDataPtr->FeeUnErasableWLCountTemp;
      StateDataPtr->FeeSectorInfo[BankNumber].UnerasableWLAddr[0] =
        StateDataPtr->FeeUnErasableWLAddrTemp[0];
      StateDataPtr->FeeSectorInfo[BankNumber].UnerasableWLAddr[1] =
        StateDataPtr->FeeUnErasableWLAddrTemp[1];
      /* [cover parentID={02816ECB-41C3-4003-95EB-ED1F93005D8B}][/cover] */
      if(GcState == FEE_GC_ERASE_PREV_SECTOR)
      {
        NewGcState = FEE_GC_MARK_SECTOR0_E_SP;
      }
      /*  Case FEE_GC_INIT_ERASE_PREV_SECTOR */
      else
      {
        /* Erase of previous sector is happening as part of INIT GC.
           The FeeStateCount shall be incremented by 2 to mark one sector
           erase. Increment FeeStateCount by 1 here. FeeStateCount is
           incremented again while preparing the state page buffer in
           FEE_GC_INIT_MARK_SECTOR0_E_SP */
        StateDataPtr->FeeStateCount += FEE_ONE;
        NewGcState = FEE_GC_INIT_MARK_SECTOR0_E_SP;
      }
      /* Move to next state */
      StateDataPtr->FeeGcState = NewGcState;
      StateDataPtr->FeeSectorCount = FEE_RESET;
    /* [cover parentID={48BAB7E3-68A9-4005-B8D5-2FB33EBB427F}][/cover] */
      StateDataPtr->FeeIntrJobFailCount = FEE_RESET;
    }
  }
}

/******************************************************************************
** Syntax : static uint8 Fee_lGcProgramStatePage(const uint8 GcState)        **
**                                                                           **
** Service ID:                                                               **
**                                                                           **
** Sync/Async:  Asynchronous                                                 **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in) : uint8  GcState: Current GC State                        **
**                                                                           **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    :  uint8                                                  **
**                   FEE_GC_E_OK: Operation is successful                    **
**                   FEE_GC_WRITE: GC write operation is failed              **
**                   FEE_GC_TRIG: GC operation triggers the another GC       **
**                                Operation                                  **
** Description : This routine is responsible for marking state page during   **
**               Garbage Collection                                          **
******************************************************************************/
/* [cover parentID={54190B01-DE09-4565-8C2B-3F8B97E1354C}]
Fee_lGcProgramStatePage
[/cover] */
/* [cover parentID={1029D83D-72D2-46ab-80F4-38CBA237F8BC}][/cover] */
static uint8 Fee_lGcProgramStatePage(const uint8 GcState)
{
  uint32                 DestAddr;
  uint32                 FreePages;
  uint32                 PageCount;
  Fee_StateDataType     *StateDataPtr;
  uint8                  BankNumber;
  uint8                  Error;

  Error = FEE_GC_E_OK;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  /* [cover parentID={8FE6B553-82A8-47db-BC36-4F78178538B7}][/cover] */
  if (StateDataPtr->FeeIntrJobStatus == FEE_JOB_DONE)
  {
    StateDataPtr->FeeIntrJobStatus = FEE_JOB_IDLE;
    /* [cover parentID={9D8E2C4C-3DA3-4cc0-9A38-D0E7DDE65EF9}][/cover] */
    if((StateDataPtr->FeeIntrJobResult == FEE_JOB_FAIL) &&
        (StateDataPtr->FeeProgVerErr == FEE_RESET))
    {
      Error = FEE_GC_WRITE;
    }
    else
    {
      Fee_lGcStatePageCompare(GcState);
    }
  }
  else
  {
    DestAddr = StateDataPtr->FeeGcDestAddr;
    if(DestAddr >= FEE_DFLASH_BANK1_BASE)
    {
      BankNumber = FEE_SECTOR1;
    }
    else
    {
      BankNumber = FEE_SECTOR0;
    }

    switch (GcState)
    {
      /* [cover parentID={89E4FD11-49DB-4f97-B1B0-0BBE06D85844}][/cover] */
      case FEE_GC_MARK_SECTOR1_V_SP:
      case FEE_GC_MARK_SECTOR0_E_SP:
      case FEE_GC_INIT_MARK_SECTOR0_E_SP:
      {
        /* [cover parentID={995FCB17-0B4D-461c-80CE-9FBA3B8815AE}][/cover] */
        if (StateDataPtr->FeeIntrJobFailCount == FEE_RESET)
        {
           /* [cover parentID={CB98BD48-5137-4566-B176-1418EC9CCEB9}][/cover] */
          if (GcState == FEE_GC_MARK_SECTOR1_V_SP)
          {
            /* [cover parentID={66E3A160-C5EF-46d7-81F2-C00AA8664F25}][/cover] */
            Fee_lPrepareStatePageBuffer(BankNumber, FEE_VALID);
          }
          else
          {
            /* [cover parentID={CBF413E6-26BC-4952-A586-80E53554DDF7}][/cover] */
            Fee_lPrepareStatePageBuffer(BankNumber, FEE_ERASED);
          }
        }
        else
        {
          /* The state page is being re-attempted after one compare failure
          Clear the last 8bytes of GcReadWriteBuffer for comparison of SP */
          /* [cover parentID={42EAB644-4E53-4209-A95A-5EFCD1BAE5F1}][/cover] */
          Fee_lClearMarkerBuffer();
        }
        while(Fee_lIsUnerasableAddr(DestAddr) == TRUE)
        {
          DestAddr = Fee_lGetNextWLAddr(DestAddr);
        }
        StateDataPtr->FeeGcDestAddr = DestAddr;

        /************* CHECK for the case of GC TRIGGERING GC *************/
        /* Get the Destination sector - the sector other than current sector
        */
        BankNumber = (uint8)StateDataPtr->FeeStatusFlags.FeeCurrSector ^ FEE_SECTOR1;
        /* Find the free pages in the destination sector */
        FreePages = Fee_lGetFreeDFLASHPages(BankNumber, DestAddr);
        /* Get the state page count */
        PageCount = FEE_DFLASH_WORDLINE_SIZE / FEE_DFLASH_PAGE_SIZE;
        /* Check if there is space in the new sector for state page */
        /* [cover parentID={2D23BAEF-B62E-4256-BE18-3F39AEE9FB73}][/cover] */
        if ((boolean)TRUE == Fee_lIsSectorEndCrossed(FreePages, PageCount))
        {
          Error = FEE_GC_TRIG;
        }
        else
        {
          StateDataPtr->FeeLastReadSize = FEE_STATEPAGE_PROGRAM_SIZE;
          /* [cover parentID={44BB2F39-9E4A-4e9a-8738-8275731B2E91}][/cover] */
          Error = Fee_lGcWrite((Fls_17_Dmu_AddressType)DestAddr, FEE_ZERO);
        }
        break;
      }


       case FEE_GC_MARK_SECTOR1_V_M:
       case FEE_GC_MARK_SECTOR0_E_M:
       case FEE_GC_INIT_MARK_SECTOR0_E_M:
      {
        /* [cover parentID={03B281B8-CAB1-4d9b-9909-EE814AB68D3E}][/cover] */
        Fee_lPrepareMarkerBuffer();
        StateDataPtr->FeeLastReadSize = FEE_STATEPAGE_MARKER_SIZE;
        Error = Fee_lGcWrite((Fls_17_Dmu_AddressType)
                             (DestAddr + FEE_STATEPAGE_DATA_SIZE),
                             FEE_STATEPAGE_DATA_SIZE);
        break;
      }
    default:
    {
      break;
    }
    }
  }

  return(Error);
}

/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lGcStatePageCompare(const uint8 GcState)    **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  GcState: Current GC State                               **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : Performs compare actions on state page programming           **
**               during Garbage collection                                    **
*******************************************************************************/
/* [cover parentID={A0DC241F-C69E-400b-AFF3-42C1376A57E8}]
Fee_lGcStatePageCompare
[/cover] */
/* [cover parentID={38B618F4-FC7F-49a8-8249-59C8C1A284D8}][/cover] */
LOCAL_INLINE void Fee_lGcStatePageCompare(const uint8 GcState)
{
  Fee_StateDataType    *StateDataPtr;
  const uint8          *SrcAddr;
  uint32                DestAddr;
  Std_ReturnType        ReturnVal1;
  uint8                 NewGcState = FEE_GC_IDLE;


  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  DestAddr = StateDataPtr->FeeGcDestAddr;
  SrcAddr = StateDataPtr->FeeGcReadWriteBuffer;
  ReturnVal1 = E_OK;

  /* [cover parentID={5546E055-5F4B-475e-A6EB-13E703D0F28C}][/cover] */
  if(StateDataPtr->FeeProgVerErr == FEE_RESET)
  {
    /* [cover parentID={7A521C74-670B-48e3-B5F7-6EA67238D8D3}]
    Compare the state page which was just written
    [/cover] */
    ReturnVal1 = Fls_17_Dmu_CompareWordsSync(
                   (Fls_17_Dmu_AddressType)DestAddr,
                   /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for
                   interfacing with FLS.FEE is passing parameters to FLS APIs,
                   casting is needed to match with the Fls API prototype.
                   SrcAddr is poiniting to FeeGcReadWriteBuffer which is part
                   of Fee_StateDataType. FeeGcReadWriteBuffer is so placed to
                   have 4 byte alignment*/
                   (const uint32 *)SrcAddr,
                   (Fls_17_Dmu_LengthType)
                   FEE_STATEPAGE_SIZE / FEE_DFLASH_WORD_SIZE);
  }

  /* Compare failed or PVER error is set.*/
  /* [cover parentID={E1DA1B5D-6ACA-4009-A4EA-32D962B06F91}][/cover] */
  if((ReturnVal1 == E_NOT_OK) || (StateDataPtr->FeeProgVerErr == FEE_SET))
  {
    /* [cover parentID={A9772711-A990-4b1b-A9DE-69C64A7D6644}][/cover] */
    if(StateDataPtr->FeeIntrJobFailCount == FEE_RESET)
    {
      /*Reset the FeeProgVerErr flag*/
      StateDataPtr->FeeProgVerErr = FEE_RESET;
      StateDataPtr->FeeIntrJobFailCount++;
      DestAddr = Fee_lGetNextWLAddr(DestAddr);
      StateDataPtr->FeeGcDestAddr = (DestAddr + FEE_DFLASH_WORDLINE_SIZE);

      switch (GcState)
      {
        /* [cover parentID={32C975D5-4465-4039-AF6D-43C7A9FE085B}][/cover] */
        case FEE_GC_MARK_SECTOR1_V_SP:
        case FEE_GC_MARK_SECTOR1_V_M:
        {
          NewGcState = FEE_GC_MARK_SECTOR1_V_SP;
          break;
        }
        /* [cover parentID={D9E21795-D6EF-4b67-9C29-8878FF0A85AA}][/cover] */
        case FEE_GC_MARK_SECTOR0_E_SP:
        case FEE_GC_MARK_SECTOR0_E_M:
        {
          NewGcState = FEE_GC_MARK_SECTOR0_E_SP;
          break;
        }


        case FEE_GC_INIT_MARK_SECTOR0_E_SP:
        case FEE_GC_INIT_MARK_SECTOR0_E_M:
        {
          NewGcState = FEE_GC_INIT_MARK_SECTOR0_E_SP;
          break;
        }
      default:
      {
        break;
      }
      }
      StateDataPtr->FeeGcState = NewGcState;
    }
    else
    {
      /* Write Fail two time raise the illegal notification. Pass the block
      index as unused parameter , because block index is not used when write
      error occurred. Block index is used only for read error to drop the block
      from GC process. */
      /* [cover parentID={6FBD5A3A-04D2-40e1-9C0C-6F44AC1429C9}][/cover] */
      Fee_lGcErrorHandler(FEE_GC_WRITE, FEE_UNUSED_PARAM);
    }
  }
  else
  {
    NewGcState = Fee_lGcStatePageComparePass(GcState);

    StateDataPtr->FeeGcState = NewGcState;
  }
}

/*[cover parentID={A4A2305F-E525-4192-AD7B-B6C56BB5EE60}][/cover]*/
/*******************************************************************************
** Syntax : LOCAL_INLINE uint8 Fee_lGcStatePageComparePass(                   **
                              const uint8 GcState)                            **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  GcState: Current GC State                               **
**                                                                            **
** Parameters (out):                                                          **
**                                                                            **
** Return value    :  NewGcState : GC state state set after comparing         **
**                                  different state page programming          **
**                                                                            **
** Description : Performs compare actions on state page programming           **
**               during Garbage collection                                    **
*******************************************************************************/
/*[cover parentID={8DF6DC79-071C-4b15-B88D-DC5DC54DD12C}][/cover]*/
LOCAL_INLINE uint8 Fee_lGcStatePageComparePass(const uint8 GcState)
{
    Fee_StateDataType    *StateDataPtr;
    Fee_SectorInfoType   *SectorInfoPtr;
    uint8                 BankNumber;
    uint8                 NewGcState = FEE_GC_IDLE;
    uint32                DestAddr;
    uint32                FreePages;
    uint32                PageCount;
    const uint8          *PendReqStatePtr;
    uint16             PendReqBlkNum;
    uint16             PendReqBlkIndex;
    const Fee_BlockType  *PendReqBlkPtr;

    StateDataPtr = Fee_CfgPtr->FeeStatePtr;
    DestAddr = StateDataPtr->FeeGcDestAddr;
    PendReqStatePtr = &(StateDataPtr->FeePendReqStatus);

    switch (GcState)
    {
      /* [cover parentID={44F5FF3D-87DF-4a28-940E-04C116993848}][/cover] */
      case FEE_GC_MARK_SECTOR1_V_SP:
      {
        NewGcState = FEE_GC_MARK_SECTOR1_V_M;
        break;
      }
      /* [cover parentID={C4C383CB-ACB3-4836-BD27-2836ACE32231}][/cover] */
      /* [cover parentID={A4A2305F-E525-4192-AD7B-B6C56BB5EE60}][/cover] */
      case FEE_GC_MARK_SECTOR1_V_M:
      {
        StateDataPtr->FeeIntrJobFailCount = FEE_RESET;
        /* Update the current sector to next sector */
        StateDataPtr->FeeStatusFlags.FeeCurrSector ^= FEE_SECTOR1;

        /* Update FreeWLAddr and StatePage Address and NextFreePageAddr */
        BankNumber = StateDataPtr->FeeStatusFlags.FeeCurrSector;
        SectorInfoPtr = &StateDataPtr->FeeSectorInfo[BankNumber];
        SectorInfoPtr->StatePageAddr = DestAddr;
        SectorInfoPtr->NextFreeWLAddr = Fee_lGetNextWLAddr(DestAddr);
        /* Update NextFreePageAddr */
        StateDataPtr->FeeNextFreePageAddr = SectorInfoPtr->NextFreeWLAddr;

        StateDataPtr->FeeLastWrittenBlkInfo.BlockNumber = FEE_RESET;
        StateDataPtr->FeeLastWrittenBlkInfo.Status.Consistent = FEE_RESET;
        /*Check for the GC on GC*/
        FreePages = (uint32)Fee_lGetFreeDFLASHPages(
                      BankNumber, SectorInfoPtr->NextFreeWLAddr);
        /* Get the state page count */
        PageCount = FEE_DFLASH_WORDLINE_SIZE / FEE_DFLASH_PAGE_SIZE;
        /* Check if there is space in the new sector for state page */
        /* [cover parentID={222A43B5-CEAD-464e-BE5B-B4C3C514AB2B}][/cover] */
        /* [cover parentID={29097A20-8551-4542-8A63-5270A1BAF554}][/cover] */
        if ((boolean)TRUE ==
            Fee_lIsSectorThresholdCrossed(FreePages, PageCount))
        {

          /* Pass the block index as unused parameter,because block index is
           not used when GC on GC error occurred. Block index is used only
           for read error to drop the block from GC process. */
          /* [cover parentID={BA70F568-8250-451f-90F4-34DE9074EFA6}][/cover] */
          Fee_lGcErrorHandler(FEE_GC_TRIG, FEE_UNUSED_PARAM );
          /*set the flag to previous state,so that driver remains in busy
           state.*/
          StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_COMPARE;
          StateDataPtr->FeeIntrJobStatus = FEE_JOB_IDLE;
          StateDataPtr->FeeIntrJobResult = FEE_JOB_FAIL;
          NewGcState = FEE_GC_FAIL;
          #if (FEE_GET_PREV_DATA_API == STD_ON)
          StateDataPtr->FeePendReqInfo.GetPrevCopy = FEE_RESET;
          #endif
          break;
        }

        if(BankNumber == FEE_SECTOR0)
        {
          StateDataPtr->FeeGcDestAddr = FEE_DFLASH_BANK1_BASE;
        }
        else
        {
          StateDataPtr->FeeGcDestAddr = FEE_DFLASH_BANK0_BASE;
        }

        /*Checking for Pending write during GC*/
        /* [cover parentID={F8CEA0F6-DE07-4d4b-A89E-4B3D732A4DCC}][/cover] */
        if((*PendReqStatePtr == FEE_REQ_NORM_WRITE) ||
            (*PendReqStatePtr == FEE_REQ_IMM_WRITE))
        {
          /* Check if there is space in the new sector for writing pending
          block.if no space available then raise the GC on GC production error
          and illegal state notification */
          PendReqBlkNum = StateDataPtr->FeePendReqInfo.BlockNumber;
          PendReqBlkIndex = Fee_lGetUsrBlockIndex(PendReqBlkNum);
          PendReqBlkPtr = &(Fee_CfgPtr->FeeBlockConfigPtr[PendReqBlkIndex]);
          if (E_NOT_OK == Fee_lPerformCurrBlkCheck(PendReqBlkPtr))
          {
            /* Pass the block index as unused parameter,because block index is
            not used when GC on GC error occurred. Block index is used only
            for read error to drop the block from GC process. */
            Fee_lGcErrorHandler(FEE_GC_TRIG, FEE_UNUSED_PARAM);

            StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_NO_REQ;
            StateDataPtr->FeeIntrJobStatus = FEE_JOB_IDLE;
            StateDataPtr->FeeIntrJobResult = FEE_JOB_FAIL;
            NewGcState = FEE_GC_FAIL;
            #if (FEE_GET_PREV_DATA_API == STD_ON)
            StateDataPtr->FeePendReqInfo.GetPrevCopy = FEE_RESET;
            #endif
            break;
          }

        }
        #if (FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)
        /* Move to next state */
        NewGcState = FEE_GC_HARDEN_QS_SECTOR;

        #else
        /* Move to next state */
        NewGcState = FEE_GC_ERASE_PREV_SECTOR;
        #endif
        break;
      }
      /* [cover parentID={832CB1AC-B547-4a03-A294-31DC1AD9DB22}][/cover] */
      case FEE_GC_MARK_SECTOR0_E_SP:
      {

        NewGcState = FEE_GC_MARK_SECTOR0_E_M;
        break;
      }
      /* [cover parentID={4C5FBF80-1616-4a70-943C-CC131D701794}][/cover] */
      case FEE_GC_INIT_MARK_SECTOR0_E_SP:
      {
        NewGcState = FEE_GC_INIT_MARK_SECTOR0_E_M;
        break;
      }
      /* [cover parentID={A64B2200-D927-45e5-B17F-B23997B6ACEA}][/cover] */
      case FEE_GC_MARK_SECTOR0_E_M:
      case FEE_GC_INIT_MARK_SECTOR0_E_M:
      {
        StateDataPtr->FeeIntrJobFailCount = FEE_RESET;
        /* Get the current active sector number */
        BankNumber = StateDataPtr->FeeStatusFlags.FeeCurrSector;
        /* calculate the previous sector number */
        BankNumber = BankNumber ^ FEE_SECTOR1;
        /* Update FreeWLAddr and StatePage Address */
        SectorInfoPtr = &StateDataPtr->FeeSectorInfo[BankNumber];
        SectorInfoPtr->StatePageAddr = DestAddr;
        SectorInfoPtr->NextFreeWLAddr = Fee_lGetNextWLAddr(DestAddr);
        NewGcState = Fee_lGcStatePageComparePassSetnewState(GcState);
        break;
      }
      default:
      {
        break;
      }
    }
    return NewGcState;
}

/*[cover parentID={43AE46F2-5AFF-43b1-AC56-27855ADD0B61}][/cover]*/
/*******************************************************************************
** Syntax : LOCAL_INLINE uint8 Fee_lGcStatePageComparePassSetnewState(        **
**                                                  const uint8 GcState)      **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  GcState: Current GC State                               **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  NewGcState : GC state state set after comparing         **
**                                  different state page programming          **
**                                                                            **
** Description : Performs compare actions on state page programming           **
**               during Garbage collection                                    **
*******************************************************************************/
LOCAL_INLINE uint8 Fee_lGcStatePageComparePassSetnewState(const uint8 GcState)
{
    uint8                 NewGcState;
    #if (FEE_SET_MODE_SUPPORTED == STD_ON) && \
    (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY) && \
    (MCAL_AR_VERSION == MCAL_AR_440)
    Fee_StateDataType    *StateDataPtr;

    StateDataPtr = Fee_CfgPtr->FeeStatePtr;
    #endif
    if (GcState == FEE_GC_MARK_SECTOR0_E_M)
    {
    NewGcState = FEE_GC_IDLE;
    #if (FEE_SET_MODE_SUPPORTED == STD_ON) && \
    (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY) && \
    (MCAL_AR_VERSION == MCAL_AR_440)
    /* [cover parentID={E9B2C7CC-831B-4fc7-99FA-4F5F36765EC6}]
    pending set mode request is registered
    [/cover] */
    if(StateDataPtr->FeeSetModeReqPend == FEE_SET)
    {
      /* [cover parentID={A38C3ADC-E259-4372-B18C-72F2B9CECE8F}]
      Call Fls for mode change
      [/cover] */
      Fls_17_Dmu_SetMode(StateDataPtr->FeeChangeReqMode);
      StateDataPtr->FeeSetModeReqPend = FEE_RESET;
    }
    #endif
    }
    else
    {
      NewGcState = FEE_GC_REQUESTED;
    }
    return NewGcState;
}
/*CYCLOMATIC_Fee_lGarbageCollection_JUSTIFICATION: Fee_lGarbageCollection has
to determine all the states of configure/unconfigure block and then generate
production error.It should also handle the hardening feature during GC, 
if it is broken into more functions to fix RSM, the code readability will 
get affected.
*/
/*******************************************************************************
** Syntax : static void Fee_lGarbageCollection(void)                          **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This routine is responsible for handling Garbage Collection  **
** which is done once the Sector reaches the threshold limit.                 **
*******************************************************************************/
/* [cover parentID={CC1B5E64-4160-484c-AFEE-1159BDF777D4}][/cover]*/
static void Fee_lGarbageCollection(void)
{
  Fee_StateDataType     *StateDataPtr;
  uint8                  Error;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;


  /* Asynchronous Transitions based ONLY on IntrJobStatus are done here */
  Fee_lGcPrologue();

  /**********************************************************************/
  /*         STATE MACHINE EXECUTION and STATE TRANSITIONS              */
  /**********************************************************************/

  /*********** GC REQSTD STATE *******************/
  /*  Initialization of variables is done here */
  /* [cover parentID={F5562E76-F04C-4c91-891C-9AC97B366D20}][/cover]*/
  if(StateDataPtr->FeeGcState == FEE_GC_REQUESTED)
  {
    #if (FEE_UNCFG_BLK_OVERFLOW_HANDLE == FEE_STOP_AT_GC)
    /* [cover parentID={DEA63189-022C-453a-B41E-A462A7E7AE38}][/cover]*/
    if(StateDataPtr->FeeUncfgBlksExceeded != FEE_UNCONFIG_BLK_LIMIT_CROSSED)
    #endif
    {
      /* [cover parentID={8221DF34-56CC-4a33-8551-D05734AB631F}][/cover]*/
      Fee_lGcRequested();
    }
  }

  /* [cover parentID={4FE54373-0E5D-485a-BBB3-0D7BAACE5722}][/cover]*/
  Error = Fee_lHandleGcCopy();

  /* [cover parentID={62914F2A-4FF6-4807-85A5-EB3132527AFF}][/cover]*/
  /***** FEE_GC_INIT_ERASE_PREV_SECTOR / FEE_GC_ERASE_PREV_SECTOR *********/
  /*  Erasing the previous sector is done here */
  if (StateDataPtr->FeeGcState == FEE_GC_ERASE_PREV_SECTOR)
  {
    /* [cover parentID={8DEC39E8-BFA9-497b-9F6F-99E5928ED60F}][/cover]*/
    Error = Fee_lGcErasePrevSector(FEE_GC_ERASE_PREV_SECTOR);
  }
  if (StateDataPtr->FeeGcState == FEE_GC_INIT_ERASE_PREV_SECTOR)
  {
    /* [cover parentID={818132A3-4B0D-45df-8653-A7039D9A71E8}][/cover]*/
    Error = Fee_lGcErasePrevSector(FEE_GC_INIT_ERASE_PREV_SECTOR);
  }


  /***** FEE_GC_INIT_MARK_SECTOR0_E_SP /
        FEE_GC_MARK_SECTOR0_E_SP *********/
  /*  Writing the erased state page content is done here */
  /* [cover parentID={0C474800-2702-4d59-A2B9-B8D098B1D8DE}][/cover]*/
  if (StateDataPtr->FeeGcState == FEE_GC_MARK_SECTOR0_E_SP)
  {
    /* [cover parentID={77345B65-B3C6-4963-A06C-88CCEE41D68C}][/cover]*/
    Error = Fee_lGcProgramStatePage(FEE_GC_MARK_SECTOR0_E_SP);
  }
  /* [cover parentID={5C1A3F42-0E18-47aa-AEFC-3D10D9145224}][/cover]*/
  if (StateDataPtr->FeeGcState == FEE_GC_INIT_MARK_SECTOR0_E_SP)
  {
    /* [cover parentID={32CA850E-D0A1-4a4a-AD45-7632E96339CE}][/cover]*/
    Error = Fee_lGcProgramStatePage(FEE_GC_INIT_MARK_SECTOR0_E_SP);
  }

  /***** FEE_GC_INIT_MARK_SECTOR0_E_M /
        FEE_GC_MARK_SECTOR0_E_M *********/
  /*  Writing the erased state page marker is done here */
  /* [cover parentID={DE462D71-A9EC-408a-8FB0-8D4727648C8A}][/cover]*/
  if (StateDataPtr->FeeGcState == FEE_GC_MARK_SECTOR0_E_M)
  {
    /* [cover parentID={CC5B158F-3E9D-4af2-84C2-83731DDF71CE}][/cover]*/
    Error = Fee_lGcProgramStatePage(FEE_GC_MARK_SECTOR0_E_M);
  }
  /* [cover parentID={800151A5-3974-41b3-A22C-13784EE7FE9F}][/cover]*/
  if (StateDataPtr->FeeGcState == FEE_GC_INIT_MARK_SECTOR0_E_M)
  {
    /* [cover parentID={BF3F400B-8848-4402-9168-2DFD19F0CB59}][/cover]*/
    Error = Fee_lGcProgramStatePage(FEE_GC_INIT_MARK_SECTOR0_E_M);
  }
  #if (FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)
  /* [cover parentID={A53CCA55-0E57-4a1d-A649-CE140A625038}][/cover]*/
  if(StateDataPtr->FeeGcState == FEE_GC_HARDEN_QS_SECTOR)
  {
    /* [cover parentID={376FED81-A75C-4842-AF38-9ABA7B0CF04A}]
    Check if hardening is required
    [/cover] */
    Fee_lGcHardenQsSector();
  }
  #endif
  /* Report production error, if Error occurred */
  /* [cover parentID={1DD7ADD6-3F4C-475b-9C7A-53730C41256E}][/cover]*/
  if (Error != FEE_GC_E_OK)
  {
    /* Clear all variables */
    StateDataPtr->FeeIntrJobStatus = FEE_JOB_IDLE;
    StateDataPtr->FeeIntrJobResult = FEE_JOB_FAIL;
    StateDataPtr->FeeIntrJob = FEE_NO_JOB;

    /* Write/erased failed raise the illegal notification.block index
    parameter is not used for write/erase error,so passed as parameter not
    used.Block index is used only for read error to drop the block from GC
    process. */
    /*[cover parentID={BD7B8CB0-5C2A-43d5-90CC-E24B1CF5B8DC}][/cover]*/
    Fee_lGcErrorHandler(Error, FEE_UNUSED_PARAM );
  }
}/*End of Fee_lGarbageCollection */

/*******************************************************************************
** Syntax : static Fee_PageType Fee_lGetDFLASHPages(const uint16 Size)        **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  (uint16)size                                            **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Fee_PageType                                            **
**                                                                            **
** Description : This routine will calculate and return the number of DFLASH  **
** pages required for a logical block size.                                   **
*******************************************************************************/
/*[cover parentID={BF381339-6DCB-4605-843C-65354E544BE8}][/cover]*/
static Fee_PageType Fee_lGetDFLASHPages(const uint16 Size)
{
  Fee_PageType  PhysicalPages;
  uint16        NewSize;

  PhysicalPages = FEE_BLOCK_MANGMNT_PAGES;
  NewSize       = Size;

  /*[cover parentID={35DDC7C6-BD47-42ce-A6C2-A9FF0CDAC6BF}][/cover]*/
  while (NewSize >= FEE_SEVEN)
  {
    PhysicalPages++;
    NewSize -= FEE_SEVEN;
  }

  /*[cover parentID={2650961E-C2BE-4114-BCB9-738BBE76F035}][/cover]*/
  if (NewSize > FEE_ZERO)
  {
    PhysicalPages++;
  }

  return(PhysicalPages);

}/*End of Fee_lGetDFLASHPages */


/*******************************************************************************
** Syntax : static uint32 Fee_lGetFreeDFLASHPages(const uint8 BankNumber      **
**                                               const uint32 StartAddr)      **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :(uint8)BankNumber : Bank Number                           **
**                  (uint32)StartAddr  : Current address                      **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  uint32                                                  **
**                                                                            **
** Description : This routine will calculate the number of empty DFLASH  pages**
** remaining in the sector.                                                   **
*******************************************************************************/
/*[cover parentID={D666BBCE-2350-4205-8F51-5462F627D921}][/cover]*/
/*[cover parentID={6142D35A-4BA1-4e3f-896A-A09B5C3D07D8}][/cover]*/
static uint32 Fee_lGetFreeDFLASHPages(const uint8 BankNumber,
                                      const uint32 StartAddr)
{
  const Fee_StateDataType *StateDataPtr;
  uint32             FreePages;
  uint32             EndAddr;
  uint32             WLAddr;
  sint32             RemainingPages;
  uint8              Count;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* Get the sector end address */
  if (BankNumber == FEE_SECTOR0)
  {
    EndAddr = FEE_DFLASH_BANK0_BASE + FEE_DFLASH_SECTOR_SIZE;
  }
  else
  {
    EndAddr = FEE_DFLASH_BANK1_BASE + FEE_DFLASH_SECTOR_SIZE;
  }

  RemainingPages = ( ((sint32)EndAddr - (sint32)StartAddr) /
                     (sint32)FEE_DFLASH_PAGE_SIZE );

  /* Subtract the pages of un-erasable word line, if any */
  Count = FEE_RESET;
  while(Count < StateDataPtr->FeeSectorInfo[BankNumber].UnerasableWLCount)
  {
    WLAddr = StateDataPtr->FeeSectorInfo[BankNumber].UnerasableWLAddr[Count];
    if ( (StartAddr <= WLAddr) && (WLAddr <= EndAddr) )
    {
      RemainingPages = RemainingPages -
                      (sint32)(FEE_DFLASH_WORDLINE_SIZE / FEE_DFLASH_PAGE_SIZE);
    }
    Count++;
  }

  /*[cover parentID={A6091D49-C400-49b6-91B0-1B8C525B8AD8}][/cover]*/
  if (RemainingPages > (sint32)FEE_ZERO)
  {
    FreePages = (uint32)RemainingPages;
  }
  else
  {
    FreePages = FEE_RESET;
  }

  return(FreePages);

}/*End of Fee_lGetFreeDFLASHPages */

#endif
/*******************************************************************************
** Syntax : static uint16 Fee_lGetUsrBlockIndex(const uint16 BlockNumber)     **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : (uint16) BlockNumber - Number of logical block           **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  uint16                                                  **
**                                                                            **
** Description : This utility function will return the Index (location)of the **
** block in the user configuration.                                           **
*******************************************************************************/
/*[cover parentID={AFA436A3-0ED3-4e88-B7DD-8E552415D1EB}][/cover]*/
static uint16 Fee_lGetUsrBlockIndex(const uint16 BlockNumber)
{
  const Fee_BlockType  *BlockPtr;
  sint32                BlockMiddle;
  sint32                BlockFirst;
  sint32                BlockLast;
  uint16                RetVal;

  BlockFirst  = 0x0;
  BlockMiddle = 0x0;
  RetVal = FEE_LOG_BLOCK_NOT_FOUND;
/* [cover parentID={2CE4CD18-0458-46a7-AD3E-5B5984EF2A20}]
Only QS data is configured
[/cover] */
#if (FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)
  /*MISRA2012_RULE_10_3_JUSTIFICATION: No unintended results with
    implicit conversions. Because max value is 65535 which within
    range sint32.*/
  BlockLast = FEE_QSBLOCK_BEGIN_INDEX - FEE_ONE;
#else
  /*MISRA2012_RULE_10_3_JUSTIFICATION: No unintended results with
    implicit conversions. Because max value is 65535 which within
    range sint32.*/
  BlockLast = ((uint32)(Fee_CfgPtr->FeeBlkCnt) - (uint32)FEE_ONE);
#endif

  BlockPtr = &(Fee_CfgPtr->FeeBlockConfigPtr[BlockFirst]);

  /*[cover parentID={330805AC-5468-4fc2-B625-FB5A52ED1601}][/cover]*/
  /* [cover parentID={8D24F650-F636-4918-8A81-E64842FEC722}]
  Block number found
  [/cover] */
  while(BlockFirst <= BlockLast)
  {
    BlockMiddle = BlockFirst +((BlockLast - BlockFirst ) / 2);

    if(BlockPtr[BlockMiddle].BlockNumber == BlockNumber)
    {
        RetVal = (uint16)BlockMiddle;
        break;
    }

    /*[cover parentID={2CE4CD18-0458-46a7-AD3E-5B5984EF2A20}][/cover]*/
    else if(BlockPtr[BlockMiddle].BlockNumber < BlockNumber)
    {
      BlockFirst = BlockMiddle + 1;

    }
    else
    {
      BlockLast = BlockMiddle - 1;
    }

  }

  /* if block is not configured, return invalid block index */
  if(BlockPtr[BlockMiddle].BlockNumber!= BlockNumber)
  {
#if (FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)
    /*MISRA2012_RULE_10_3_JUSTIFICATION: No unintended results with
      implicit conversions. Because max value is 65535 which within
      range sint32.*/
    BlockFirst = FEE_QSBLOCK_BEGIN_INDEX;
    /*MISRA2012_RULE_10_3_JUSTIFICATION: No unintended results with
      implicit conversions. Because max value is 65535 which within
      range sint32.*/
    BlockLast = ((uint32)(Fee_CfgPtr->FeeBlkCnt) - (uint32)(FEE_ONE));

    while(BlockFirst <= BlockLast)
    {
      BlockMiddle = BlockFirst +((BlockLast - BlockFirst ) / 2);

      if(BlockPtr[BlockMiddle].BlockNumber == BlockNumber)
      {
         RetVal = (uint16)BlockMiddle;
         break;
      }
      else if(BlockPtr[BlockMiddle].BlockNumber < BlockNumber)
      {
        BlockFirst = BlockMiddle + 1;
      }
      else
      {
        BlockLast = BlockMiddle - 1;
      }

    }
    /*[cover parentID={94C2F925-ABDA-4ebf-8BE1-570E221451CD}][/cover]*/
    if(BlockPtr[BlockMiddle].BlockNumber!= BlockNumber)
    {
      RetVal = FEE_LOG_BLOCK_NOT_FOUND;
    }

#else
    RetVal = FEE_LOG_BLOCK_NOT_FOUND;
#endif
  }

  return(RetVal);

}/* End of Fee_lGetUsrBlockIndex */

/*CYCLOMATIC_Fee_lComputeNextFreePageAddr_JUSTIFICATION:
The complexity of this is marginally over 15(complexity is 16).
Fee_lComputeNextFreePageAddr has to determine the next free page address,
for which it checks for the un-erasable WL, the checks are simple and few.
so, these cannot be avoided as the readability will get affected, if it is
broken into multiple functions.
*/
/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lComputeNextFreePageAddr                    **
**                                            (const uint32 BankNumber)       **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :BankNumber                                            **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This utility function computes the first free page address   **
** of the sector based on NextFreeWLAddr                                      **
*******************************************************************************/
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/* [cover parentID={6C36A6FC-E37D-489b-A42E-CC3C75D504D3}]
Fee_lComputeNextFreePageAddr
[/cover] */
/*[cover parentID={79F7A50C-9E02-487a-A1F4-D47723FBFCBF}][/cover]*/
LOCAL_INLINE void Fee_lComputeNextFreePageAddr(const uint32 BankNumber)
{
  Fee_StateDataType  *StateDataPtr;
  const Fee_SectorInfoType *SectorInfoPtr;
  const uint32             *TempDataPtr;
  uint32              TempAddr;
  uint32              TempAddrPrevWL;
  Std_ReturnType      RetVal;
  uint8               LoopEnd;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  SectorInfoPtr = &StateDataPtr->FeeSectorInfo[BankNumber];
  LoopEnd = FEE_RESET;

  /* Get the WL before the Next Free WL of the sector */
  StateDataPtr->FeeNextFreePageAddr = SectorInfoPtr->NextFreeWLAddr;

  /* Check if the WL before the free WL is state page */
  TempAddrPrevWL = SectorInfoPtr->NextFreeWLAddr - FEE_DFLASH_WORDLINE_SIZE;

  /* If previous word line contains a state page OR
     if it is an un-erasable word line, then next free page address is same
     as next free word line address; otherwise proceed to identify the
     next free page address */
  /*[cover parentID={E0BB1E49-3D1A-49c5-A8B9-DC2554F58F9E}][/cover]*/
  if((TempAddrPrevWL != SectorInfoPtr->StatePageAddr) &&
      (!((SectorInfoPtr->UnerasableWLCount != FEE_RESET) &&
         ((SectorInfoPtr->UnerasableWLAddr[0]  == TempAddrPrevWL) ||
          (SectorInfoPtr->UnerasableWLAddr[1]  == TempAddrPrevWL)))))
  {
    TempAddr = SectorInfoPtr->NextFreeWLAddr ;

    TempAddrPrevWL += FEE_DFLASH_PAGE_SIZE;

    do
    {
      TempAddr -= FEE_DFLASH_PAGE_SIZE;
      /* Read the header (2 Words) */

      /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for interfacing with
      FLS.FEE is passing parameters to FLS APIs, casting is needed to match with
      the Fls API prototype. FeeReadWriteBuffer is 4 byte aligned which is part
      of Fee_StateDataType.*/
      RetVal = Fls_17_Dmu_ReadWordsSync((Fls_17_Dmu_AddressType)TempAddr, \
                                (uint32 *)StateDataPtr->FeeReadWriteBuffer, \
                                (Fls_17_Dmu_LengthType)
                                (FEE_DFLASH_PAGE_SIZE / FEE_DFLASH_WORD_SIZE));

      /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform
      32 bit access and array is memory aligned.*/
      TempDataPtr = (uint32 *)StateDataPtr->FeeReadWriteBuffer;

      if((RetVal == E_OK) && (*(TempDataPtr) == (uint32)FEE_RESET) &&
          (TempDataPtr[1] == (uint32)FEE_RESET))
      {
        StateDataPtr->FeeNextFreePageAddr = TempAddr;
      }
      else
      {
        LoopEnd = FEE_SET ;
        if ((RetVal == E_OK) &&
            ((StateDataPtr->FeeReadWriteBuffer[0] == FEE_DATA_NEXT_PAGE_ID) ||
             (StateDataPtr->FeeReadWriteBuffer[0] == FEE_DATA_FIRST_PAGE_ID)))
        {
          StateDataPtr->FeeLastWrittenBlockDirty = FEE_LWB_CHECK_FOR_DIRTY;
        }
        else if (RetVal != E_OK)
        {
          StateDataPtr->FeeNextFreePageAddr = SectorInfoPtr->NextFreeWLAddr;
        }
        else
        {
          /* dummy else */
        }
      }
    } while ((TempAddr > TempAddrPrevWL) && (LoopEnd == FEE_RESET));
  }
}

/*******************************************************************************
** Syntax : static void Fee_lUpdateCache(void)                                **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :None                                                  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This utility function  will update the cache which contains  **
** the latest information about the DFLASH contents.                          **
*******************************************************************************/
/* [cover parentID={7EF281BE-B4A1-44d3-B03F-F5841091218F}][/cover] */
static void Fee_lUpdateCache(void)
{
  Fee_StateDataType      *StateDataPtr;
  Fee_SectorInfoType     *SectorInfoPtr;
  uint32                  EndAddr;
  uint32                  BankNumber;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;


  if(StateDataPtr->FeeStatusFlags.FeeCurrSector == (uint32)FEE_SECTOR0)
  {
    EndAddr = FEE_DFLASH_BANK0_BASE;
    BankNumber = FEE_SECTOR0;
  }
  else
  {
    EndAddr = FEE_DFLASH_BANK1_BASE;
    BankNumber = FEE_SECTOR1;
  }

  SectorInfoPtr = &StateDataPtr->FeeSectorInfo[BankNumber];
  /* [cover parentID={37ABA514-F548-42b6-B794-5C3C7E57392A}]
  Is cache state is FEE_CACHE_IDLE
  [/cover] */
  if(StateDataPtr->FeeCacheState == FEE_CACHE_IDLE)
  {

  /* Identifies next free page */
  Fee_lComputeNextFreePageAddr(BankNumber);

  /* Point to last written page of the valid sector */
  StateDataPtr->FeeCurrSectSrcAddr = StateDataPtr->FeeNextFreePageAddr -
                                     FEE_DFLASH_PAGE_SIZE;

    /* Set the number of pages to be scanned in one Fee_MainFunction() cycle */
    StateDataPtr->FeeBlkPageCount = FEE_PAGES_PER_FEEMAIN;

  /* Start the Cache Update state machine */
  StateDataPtr->FeeCacheState = FEE_CACHE_FIND_NEXT_BLK;

  Fee_lUpdateCacheTable(BankNumber, EndAddr);
  }
  /* [cover parentID={0DDF83A1-D28D-43cf-B946-5AF4E3478015}]
  Cache state is FEE_CACHE_FIND_NEXT_BLK
  [/cover] */
  else if(StateDataPtr->FeeCacheState == FEE_CACHE_FIND_NEXT_BLK)
  {
    /* Set the number of pages to be scanned in one Fee_MainFunction() cycle */
    StateDataPtr->FeeBlkPageCount = FEE_PAGES_PER_FEEMAIN;
    Fee_lUpdateCacheTable(BankNumber, EndAddr);
  }
  else
  {
    /* Empty for misra */
  }
  /* [cover parentID={33B21CF8-3820-4440-AB66-433BD546E627}][/cover] */
  if(StateDataPtr->FeeCacheState == FEE_CACHE_UPDATE_COMPLETE)
  {
    /* Reset the number of pages in the block */
    StateDataPtr->FeeBlkPageCount = FEE_RESET;
  }

  /* check if marker is missing for the last written block */
  /* [cover parentID={2915B333-C14F-450e-BD6F-848F4C00FA43}][/cover] */
  if((StateDataPtr->FeeLastWrittenBlockDirty == FEE_LWB_DIRTY) &&
      (StateDataPtr->FeeCacheState == FEE_CACHE_UPDATE_COMPLETE))
  {
    /* move next free page address to next page */
    /* to avoid any further write attempts on the missing marker location */
    StateDataPtr->FeeNextFreePageAddr += FEE_DFLASH_PAGE_SIZE;
    /* If next free page is the beginning of a word line */
    /* [cover parentID={F298FED5-5E77-43f5-A28D-02AB86A5E8F5}][/cover] */
    if(Fee_lIsWLBeginning(StateDataPtr->FeeNextFreePageAddr) ==
        FEE_NEW_WL_BEGIN)
    {
      /* clear last written block info */
      StateDataPtr->FeeLastWrittenBlkInfo.BlockNumber = FEE_RESET;
      StateDataPtr->FeeLastWrittenBlkInfo.Status.Consistent = FEE_RESET;
    }
    /* if next free page address is beyond next free word line address */
    /* [cover parentID={140F437D-DB78-45ab-904E-F211109BA967}][/cover] */
    if(StateDataPtr->FeeNextFreePageAddr > SectorInfoPtr->NextFreeWLAddr)
    {
      /* move next free word line to its next word line */
      SectorInfoPtr->NextFreeWLAddr += (FEE_DFLASH_WORDLINE_SIZE);
    }
  }

}/* End of Fee_lUpdateCache */
#endif

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lComputeNextWLAddr                          **
**                               (Fee_SectorInfoType * const SectorInfoPtr)   **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : SectorInfoPtr - Pointer to Sector Info               **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This utility function will confirm the next free WL address  **
*******************************************************************************/
/* [cover parentID={70343C38-995B-41b2-B7E7-7CB215F859C6}]
Fee_lComputeNextWLAddr
[/cover] */
/* [cover parentID={ECDAF14E-7BA9-4823-AC36-817AB9BB1AC4}][/cover] */
LOCAL_INLINE void Fee_lComputeNextWLAddr(Fee_SectorInfoType * const \
    SectorInfoPtr)
{
  uint32 index;
  const uint32 *SrcPtr;
  Fee_StateDataType  *StateDataPtr;
  Std_ReturnType      ReturnValueFls;
  uint32 Length;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  SrcPtr =
    /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 32 bit
    access and array is memory aligned.*/
    (const uint32 *)(StateDataPtr->FeeReadWriteBuffer);
  Length = FEE_DFLASH_WORDLINE_SIZE / FEE_DFLASH_WORD_SIZE;

  /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for interfacing with
  FLS.FEE is passing parameters to FLS APIs, casting is needed to match with
  the Fls API prototype.*/

  ReturnValueFls = Fls_17_Dmu_ReadWordsSync(\
                   (Fls_17_Dmu_AddressType)SectorInfoPtr->NextFreeWLAddr, \
                   (uint32 *)(StateDataPtr->FeeReadWriteBuffer), \
                   (Fls_17_Dmu_LengthType)(Length));

  /* If read error -> word line is not empty */
  /* [cover parentID={130FA20A-7039-44b2-855E-67492640912D}][/cover] */
  if(ReturnValueFls == E_NOT_OK)
  {
    SectorInfoPtr->NextFreeWLAddr =
      Fee_lGetNextWLAddr(SectorInfoPtr->NextFreeWLAddr);
  }
  /* [cover parentID={67091890-018D-4afb-9614-CB80A3AB5022}][/cover] */
  else
  {
    /* check if word line is empty */
    index = FEE_RESET;
    while((index < Length) && (*SrcPtr == (uint32)FEE_RESET))
    {

      SrcPtr++;
      index++;
    }
    /* if word line is not empty, move to next word line */
    if(index < Length)
    {
      SectorInfoPtr->NextFreeWLAddr =
        Fee_lGetNextWLAddr(SectorInfoPtr->NextFreeWLAddr);
    }
  }
} /* End of Fee_lComputeNextWLAddr */

/*CYCLOMATIC_Fee_lUpdateCacheTable_JUSTIFICATION: Fee_lUpdateCacheTable is the
 function will search for data block and update cache table from free page of
 the sector.If broken into more functions, the maintenance/readability will get
  affected.
*/
/*******************************************************************************
** TRACEABILITY: []                                                           **
**                                                                            **
** Syntax : LOCAL_INLINE void Fee_lUpdateCacheTable(                          **
**                                      const uint32 BankNumber,              **
**                                      const uint32 EndAddr                  **
**                                    )                                       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :BankNumber                                            **
**                      EndAddr                                               **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This utility function  will search through the DFLASH from   **
**  the free page of the sector until the start page of a data block is found **
*******************************************************************************/
/* [cover parentID={14665659-4D81-49c2-A37A-1559D2FA5E57}][/cover] */
LOCAL_INLINE void Fee_lUpdateCacheTable(const uint32 BankNumber, \
                                        const uint32 EndAddr)
{
  Fee_StateDataType       *StateDataPtr;
  uint8             *ReadWriteBufferPtr;
  uint32                   WordValue[2];
  uint32                   LWBHeaderAddress;
  uint32                   LWBMarkerAddress;
  uint32                   DataNextPageCount;
  uint16                   PageCount;
  uint16                   PageCount1;
  uint16                   BlockNumber;
  uint8                    PageId;
  uint8                    PotentialMarkerPage;
  Std_ReturnType           RetVal;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  ReadWriteBufferPtr = StateDataPtr->FeeReadWriteBuffer;
  PotentialMarkerPage = FEE_RESET;
  DataNextPageCount = FEE_RESET;
  do
  {
    /* Check for unerasable WL */
    /* [cover parentID={32D9C173-A175-4c32-8F44-9F9527D3DD01}][/cover] */
    while((Fee_lIsUnerasableAddr(StateDataPtr->FeeCurrSectSrcAddr) == TRUE) &&
          (StateDataPtr->FeeCacheState != FEE_CACHE_UPDATE_COMPLETE) &&
          (StateDataPtr->FeeBlkPageCount!= FEE_ZERO))
    {
      /* [cover parentID={5B61E537-5EA6-4008-80C5-8E41269E7FD7}][/cover] */
      Fee_lCheckPrevPage(EndAddr);
    }
    /* [cover parentID={B33D439F-1733-4162-BBB4-459F46046EC0}][/cover] */
    if ((StateDataPtr->FeeCacheState != FEE_CACHE_UPDATE_COMPLETE) &&
        (StateDataPtr->FeeBlkPageCount!= FEE_ZERO))
    {
      /* Read the header (2 Words) */
      /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for interfacing with
      FLS.FEE is passing parameters to FLS APIs, casting is needed to match with
      the Fls API prototype. ReadWriteBuffPtr is poiniting to FeeReadWriteBuffer
        which is part of Fee_StateDataType. FeeReadWriteBuffer is so placed to have
        4 byte alignment*/

      RetVal = Fls_17_Dmu_ReadWordsSync(\
                    (Fls_17_Dmu_AddressType)StateDataPtr->FeeCurrSectSrcAddr, \
                    (uint32 *)ReadWriteBufferPtr, \
                    (Fls_17_Dmu_LengthType)\
                    (FEE_DFLASH_PAGE_SIZE / FEE_DFLASH_WORD_SIZE));
      /* [cover parentID={1F72A1C8-821F-4865-A59D-FA9164481D28}][/cover] */
      if(StateDataPtr->FeeLastWrittenBlockDirty == FEE_LWB_CHECK_FOR_DIRTY)
      {
        /* [cover parentID={350227EF-15F5-48f8-AA3D-38AEAAFE46FF}][/cover] */
        if((RetVal == E_NOT_OK) ||
            ((ReadWriteBufferPtr[0] != FEE_DATA_FIRST_PAGE_ID) &&
             (ReadWriteBufferPtr[0] != FEE_DATA_NEXT_PAGE_ID)))
        {
          StateDataPtr->FeeLastWrittenBlockDirty = FEE_LWB_NOT_DIRTY;
        }
      }
      /* [cover parentID={C6CF4BF8-BDB7-48de-B7AA-CC213682271F}][/cover] */
      if(RetVal == E_NOT_OK)
      {
        /*Reading of page is failed due to error (ECC error or HW busy)
        and if this marker page then clear PotentialMarkerPage. This will
        avoid storing block data in cache with corrupted marker page and
        illegal notification while GC */
        PotentialMarkerPage = FEE_RESET;
        DataNextPageCount = FEE_RESET;
      }
      /* [cover parentID={191B2B49-2CDC-43c6-8E8F-97333B4110E5}][/cover] */
      else
      {
        /* Evaluate the header read */
        PageId = *ReadWriteBufferPtr;
        /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 32
        bit access and array is memory aligned.*/
        WordValue[0] = *((const uint32 *)ReadWriteBufferPtr);
        /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 32
         bit access and array is memory aligned.*/
        WordValue[1] = \
        *(const uint32 *)&(ReadWriteBufferPtr[FEE_DFLASH_WORD_SIZE]);

        /* Check for data continuation page */
        if (WordValue[0] == FEE_DP_MARKER_WORD)
        {

          DataNextPageCount = FEE_RESET;


          PageCount1 = ((uint16)((uint16)(ReadWriteBufferPtr[7]) << FEE_EIGHT) |
                        ReadWriteBufferPtr[6]);
          PageCount = (PageCount1 & (uint16)FEE_PAGE_COUNT_MASK);

          BlockNumber = ((uint16)((uint16)(ReadWriteBufferPtr[5]) << FEE_EIGHT) |
                         ReadWriteBufferPtr[4]);
          LWBMarkerAddress = StateDataPtr->FeeCurrSectSrcAddr;
          if(StateDataPtr->FeeSectorInfo[BankNumber].UnerasableWLCount ==
              FEE_RESET)
          {
            LWBHeaderAddress = LWBMarkerAddress - (
                                 (uint32)PageCount << FEE_PAGE_TO_BYTE);
          }
          else
          {
            LWBHeaderAddress = Fee_lGetBlockHeaderAddress(LWBMarkerAddress,
                               PageCount);
          }
          /* [cover parentID={5145C1E7-DA38-437d-9CA7-D42D7EF005B5}][/cover] */
          if((LWBHeaderAddress > EndAddr) && (PageCount1 != FEE_RESET) &&
              (LWBHeaderAddress < (FEE_DFLASH_SECTOR_SIZE * FEE_TWO )))
          {

            /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for interfacing
            with FLS.FEE is passing parameters to FLS APIs, casting is needed
            to match with the Fls API prototype. ReadWriteBuffPtr is poiniting to
            FeeReadWriteBuffer which is part of Fee_StateDataType. FeeReadWriteBuffer
            is so placed to have 4 byte alignment*/
            RetVal = Fls_17_Dmu_ReadWordsSync(\
                                (Fls_17_Dmu_AddressType)LWBHeaderAddress, \
                                (uint32 *)ReadWriteBufferPtr, \
                                (Fls_17_Dmu_LengthType)\
                                (FEE_DFLASH_PAGE_SIZE / FEE_DFLASH_WORD_SIZE));
            /* [cover parentID={92D1ECF3-5B39-4c30-9C74-19C59A06E0A6}][/cover] */
            if(RetVal == E_OK)
            {

              RetVal = Fee_lEvaluateBlkHeader(BlockNumber, PageCount1);
              /* [cover parentID={5A3667BB-AA2C-4dd1-A2F9-265774A7B94F}][/cover] */
              if(RetVal == E_OK)
              {
                /* [cover parentID={86674B7E-DE84-413b-8C8D-971B468BB1B6}][/cover] */
                Fee_lHandleBlkMarkerFound(LWBHeaderAddress, LWBMarkerAddress,
                                          PageCount);
                PotentialMarkerPage = FEE_RESET;
                /* Block Header page is valid and no need to scan the data pages
                 for ECC error because ECC error will be detected during the
                 read and GC.Block with ECC error in data pages will be treated
                 as inconsistent during GC and will be not be copied to another
                 sector. This will reduce the  the time for cache table build.
                 skipping of data pages is done by setting the
                StateDataPtr->FeeCurrSectSrcAddr address to LWBHeaderAddress */
                StateDataPtr->FeeCurrSectSrcAddr = LWBHeaderAddress;
              }
              else
              {

                /* Block Header page is not valid and no need to scan the data
                pages.Skiping of data pages is done by setting the
                StateDataPtr->FeeCurrSectSrcAddr address to LWBHeaderAddress */
                PotentialMarkerPage = FEE_RESET;
                StateDataPtr->FeeCurrSectSrcAddr = LWBHeaderAddress;
              }
            }
            else
            {
              PotentialMarkerPage = FEE_RESET;
              /* Block Header page is not valid and no need to scan the data
              pages.Skiping of data pages is done by setting the
              StateDataPtr->FeeCurrSectSrcAddr address to LWBHeaderAddress */
              StateDataPtr->FeeCurrSectSrcAddr = LWBHeaderAddress;
            }
            /* Decerement the number of pages to be scanned in one main
            cycle by 1 , because header page of block is analyzed*/
            StateDataPtr->FeeBlkPageCount -= FEE_ONE;
          }
          else
          {
            PotentialMarkerPage = FEE_SET ;
            DataNextPageCount = FEE_RESET;
          }
        }
        /* [cover parentID={F383C32D-56D9-438c-9840-B2FBE8269CE0}][/cover] */
        else if (PageId == FEE_DATA_NEXT_PAGE_ID)
        {
          DataNextPageCount++;
        }
        /* Check for data first page */
        /* [cover parentID={9B8C107A-0D58-4eaa-9905-C96EC2B5B72D}][/cover] */
        else if (PageId == FEE_DATA_FIRST_PAGE_ID)
        {
          Fee_lHandleBlkHeaderFound(PotentialMarkerPage, DataNextPageCount);
          DataNextPageCount = FEE_RESET;
          PotentialMarkerPage = FEE_RESET;
        }
        else
        {
          DataNextPageCount = FEE_RESET;
          /* [cover parentID={C5562534-FCC7-48e3-8246-72228C877055}][/cover] */
          if(((WordValue[0] == (uint32)FEE_RESET) &&
              (WordValue[1] == (uint32)FEE_RESET)) ||
              (ReadWriteBufferPtr[0] == FEE_STATE_FIRST_PAGE_ID))
          {
            PotentialMarkerPage = FEE_RESET;
          }
          else
          {
            /* Current page data is corrupted and if this marker page then
               clear PotentialMarkerPage. This will avoid storing block data
               in cache with corrupted marker page and illegal notification
               while GC  */
            PotentialMarkerPage = FEE_RESET;
          }
        }
      }
      Fee_lCheckPrevPage(EndAddr);
    }
  } while((StateDataPtr->FeeCacheState == FEE_CACHE_FIND_NEXT_BLK) &&
          (StateDataPtr->FeeBlkPageCount!= FEE_ZERO));
  /* [cover parentID={CAB4469D-0FBF-4a76-996A-FC1792C24FE5}][/cover] */
}
#endif

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/*******************************************************************************
** Syntax : LOCAL_INLINE Std_ReturnType Fee_lEvaluateBlkHeader                **
**                                         (const uint16 BlockNumber,         **
**                                          const uint16 BlockPageCount)      **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  BlockNumber - Logical block number                      **
**                    BlockPageCount - Page Count of the corresponding block  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                   E_OK:Block Header page is matching with marker page.     **
**                   E_NOT_OK:Block Header page is not matching with marker   **
**                   page.                                                    **
**                                                                            **
** Description : This function evaluates block header page with respect to    **
**               block marker page                                            **
**                                                                            **
*******************************************************************************/
/* [cover parentID={FEB7A878-CB8C-478a-B38D-7CB3691EA331}][/cover] */
LOCAL_INLINE Std_ReturnType Fee_lEvaluateBlkHeader(const uint16 BlockNumber,
    const uint16 BlockPageCount)
{
  const Fee_StateDataType          *StateDataPtr;
  const uint8                *ReadWriteBufferPtr;
  uint16                      BlockNumber1;
  uint16                      PageCount1;
  Std_ReturnType              RetVal;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  ReadWriteBufferPtr = StateDataPtr->FeeReadWriteBuffer;

  BlockNumber1 = (uint16)((uint16)ReadWriteBufferPtr[2] << FEE_EIGHT) |
                 ReadWriteBufferPtr[1];

  PageCount1   = (uint16)((uint16)ReadWriteBufferPtr[7] << FEE_EIGHT) |
                 ReadWriteBufferPtr[6];

  /* [cover parentID={71495D05-7A44-4c6e-967A-D8F3BC5B5317}][/cover] */
  if((BlockNumber == BlockNumber1) &&
      (BlockPageCount == PageCount1) &&
      (ReadWriteBufferPtr[0] == FEE_DATA_FIRST_PAGE_ID))
  {
    RetVal = E_OK;
  }
  else
  {
    RetVal = E_NOT_OK;
  }

  return(RetVal);
}

/*******************************************************************************
** Syntax : LOCAL_INLINE uint32 Fee_lGetBlockHeaderAddress                    **
**                                           (const uint32 LWBMarkerAddress,  **
**                                            const uint16 PageCount)         **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  (uint32)LWBMarkerAddress - Last Written Block's Marker  **
                                                 Address                      **
**                    (uint16)PageCount - Page Count of the corresponding     **
**                                          block                             **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  uint32 - Block header address                           **
**                                                                            **
** Description : This function returns the address of the block's header      **
**                                                                            **
*******************************************************************************/
/* [cover parentID={501EF677-CADF-4b03-AEF1-212338E60E6F}]
Fee_lGetBlockHeaderAddress
[/cover] */
/* [cover parentID={D3E72FDC-BF75-4272-A0D0-6A327BE99D23}][/cover] */
LOCAL_INLINE uint32 Fee_lGetBlockHeaderAddress(const uint32 LWBMarkerAddress,
    const uint16 PageCount)
{
  uint32 BlockSize;
  uint32 NewLWBMarkerAddress;

  BlockSize = (uint32)PageCount << FEE_PAGE_TO_BYTE;
  NewLWBMarkerAddress = (uint32)LWBMarkerAddress;
  /* [cover parentID={546D9630-0A3E-4f89-8839-2BFB93D74A9D}][/cover] */
  do
  {
    NewLWBMarkerAddress -= FEE_DFLASH_PAGE_SIZE;
    /* [cover parentID={C032B0D0-204B-44df-833E-7D599A9221A9}][/cover] */
    if(Fee_lIsUnerasableAddr(NewLWBMarkerAddress) == (boolean)FALSE)
    {
      BlockSize -= FEE_DFLASH_PAGE_SIZE;
    }
  } while(BlockSize > FEE_ZERO);

  return(NewLWBMarkerAddress);
}

/******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lHandleBlkMarkerFound                      **
**                                        (const uint32 LWBHeaderAddress,    **
**                                         const uint32 LWBMarkerAddress,    **
**                                         const uint16 PageCount)           **
**                                                                           **
** Service ID:                                                               **
**                                                                           **
** Sync/Async:  Synchronous                                                  **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in) : (uint32) LWBHeaderAddress - Last Written Block's Header **
                                                 Address                     **
**                   (uint32) LWBMarkerAddress - Last Written Block's Marker **
                                                  Address                    **
**                   (uint16) PageCount - Page Count of the corresponding    **
                                           block                             **
**                                                                           **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    :  void                                                   **
**                                                                           **
** Description:This function does the cache table update and other necessary **
**             handling when the block's marker is found during cache build  **
******************************************************************************/
/* [cover parentID={37A9C2EB-D1A4-442b-BBF2-9540B6A49AF5}]
Fee_lHandleBlkMarkerFound
[/cover] */
/* [cover parentID={FE455823-FB15-46ca-A78E-E17728918E39}][/cover] */
LOCAL_INLINE void Fee_lHandleBlkMarkerFound(const uint32 LWBHeaderAddress,
    const uint32 LWBMarkerAddress,
    const uint16 PageCount)
{
  Fee_StateDataType          *StateDataPtr;
  Fee_LastWrittenBlkInfoType *LastWrittenBlkPtr;
  const uint8                      *ReadWriteBufferPtr;
  Fee_CacheStatusType         Status;
  uint32                      NextFreePageWLAddr;
  uint16                      BlockNumber;
  uint16                      Index;

  Status.Consistent = FEE_SET;
  Status.Copied = FEE_RESET;
  Status.PrevCopyValid = FEE_RESET;
  Status.PrevCopyConsistent = FEE_RESET;
  Status.PrevCopyCopied = FEE_RESET;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  ReadWriteBufferPtr = StateDataPtr->FeeReadWriteBuffer;
  LastWrittenBlkPtr = &(StateDataPtr->FeeLastWrittenBlkInfo);
  StateDataPtr->FeeCurrSectSrcAddr = LWBHeaderAddress;

  BlockNumber = (uint16)((uint16)ReadWriteBufferPtr[2] << FEE_EIGHT) |
                ReadWriteBufferPtr[1];
  Index = Fee_lGetUsrBlockIndex(BlockNumber);

  /* [cover parentID={F0533167-5F51-49dc-AC32-DE0371783E70}][/cover] */
  if((ReadWriteBufferPtr[7] & FEE_VALID_MASK) != FEE_RESET)
  {
    Status.Valid = FEE_SET ;
  }
  else
  {
    Status.Valid = FEE_RESET;
  }

  /* Updated cache table */
  /* [cover parentID={5A7A0F35-2512-4fad-AFAF-EB1061497AC7}][/cover] */
  if ((Index != FEE_LOG_BLOCK_NOT_FOUND))
  {
    /* [cover parentID={1692F876-9F39-408b-9B72-B51C9D4526F5}][/cover] */

    /*MISRA2012_RULE_1_3_JUSTIFICATION: As per JIRA: 0000053912-10179 passing
    the Fee_CacheStatusType as reference.
    This is safe because in function Fee_lUpdateBlockInfo no pointer arthmetic
    is performed only read operation and within the scope of called function.
    So, no undefined behaviour */
    Fee_lUpdateBlockInfo(&(Status), Index, PageCount);

  }
  else
  {
    /* [cover parentID={31AADA5E-26FF-4378-A54D-363F56FEE982}][/cover] */
    Fee_lUpdateUnconfigBlockInfo(BlockNumber, PageCount);
  }

  /* Updated last written block info, if not done */
  /* [cover parentID={295E2765-3905-4973-90EC-4A70C6367400}][/cover] */
  if(LastWrittenBlkPtr->BlockNumber == FEE_RESET)
  {
    NextFreePageWLAddr = Fee_lGetWLBeginning(StateDataPtr->FeeNextFreePageAddr);
    /* [cover parentID={1CFD55A2-1069-40fe-B20C-EC0632BBAE44}][/cover] */
    if((LWBHeaderAddress < NextFreePageWLAddr) &&
        (LWBMarkerAddress >= NextFreePageWLAddr))
    {
      LastWrittenBlkPtr->PageCount = PageCount + FEE_ONE;
      LastWrittenBlkPtr->Addr = LWBHeaderAddress;
      LastWrittenBlkPtr->BlockNumber = BlockNumber;
      LastWrittenBlkPtr->Status.Consistent = FEE_SET ;
    }
    /* [cover parentID={CDD62F42-E101-4c07-AD57-E18AF06C9AF4}][/cover] */
    else if (LWBMarkerAddress < NextFreePageWLAddr)
    {
      LastWrittenBlkPtr->BlockNumber = FEE_16_BIT_ALL_ONES;
    }
    else
    {
      /* dummy else */
    }
  }
}

/******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lHandleBlkHeaderFound                      **
**                                        (const uint8 PotentialMarkerPage,  **
**                                         const uint32 DataNextPageCount)   **
**                                                                           **
** Service ID:                                                               **
**                                                                           **
** Sync/Async:  Synchronous                                                  **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in): (uint8) PotentialMarkerPage - Potential Marker Page was  **
**                                                found or not.              **
**                  (uint32) DataNextPageCount - Count of Data block's       **
**                                               continuation page           **
**                                                                           **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    :  void                                                   **
**                                                                           **
** Description:This function does the cache table update and other necessary **
**              handling when the block's header is found during cache build **
******************************************************************************/
/* [cover parentID={738E380E-9EE6-4fe8-A1A6-34BB60F4CBDB}][/cover] */
LOCAL_INLINE void Fee_lHandleBlkHeaderFound(const uint8 PotentialMarkerPage,
    const uint32 DataNextPageCount)
{
  Fee_StateDataType          *StateDataPtr;
  const uint8                      *ReadWriteBufferPtr;
  uint16                      PageCount;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  ReadWriteBufferPtr = StateDataPtr->FeeReadWriteBuffer;

  UNUSED_PARAMETER (PotentialMarkerPage);
  /* extract page count */
  PageCount = (uint16)((uint16)ReadWriteBufferPtr[7] << FEE_EIGHT) |
              ReadWriteBufferPtr[6];
  PageCount = (PageCount & (uint16)FEE_PAGE_COUNT_MASK) - FEE_ONE;
  /* [cover parentID={303F6A87-6A91-43e4-8CCF-E59870F0D29D}][/cover] */
  if(StateDataPtr->FeeLastWrittenBlockDirty == FEE_LWB_CHECK_FOR_DIRTY)
  {
    /* [cover parentID={09A8FD7D-4F95-4b5c-968C-A599C49BD408}][/cover] */
    if(PageCount == DataNextPageCount)
    {
      StateDataPtr->FeeLastWrittenBlockDirty = FEE_LWB_DIRTY;
    }
    else
    {
      StateDataPtr->FeeLastWrittenBlockDirty = FEE_LWB_NOT_DIRTY;
    }
  }
  /* AI00194692 - Do not update cache table as block is inconsistent */
  /*            - Continue the search for consistent copy of the block */

}

#endif

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lCheckPrevPage(const uint32 EndAddr)        **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :EndAddr - BaseAddr of the sector                      **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  void                                                    **
**                                                                            **
** Description : This utility function will check if the CurrSectSrcAddr      **
**  has reached the base address. If not, it decrements the CurrSectSrcAddr   **
**  by page size                                                              **
*******************************************************************************/
/* [cover parentID={0C4F21DC-2ECA-437b-AAB5-3D5340FC7FA2}]
Fee_lCheckPrevPage
[/cover] */
 /* [cover parentID={E452785D-3A38-4c72-8495-961C1EDE8347}][/cover] */
LOCAL_INLINE void Fee_lCheckPrevPage(const uint32 EndAddr)
{
  Fee_StateDataType       *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* Check if all pages have been read */
  /* [cover parentID={6B99A24F-A42E-4aa7-A6E4-EE7A24A14437}][/cover] */
  if( StateDataPtr->FeeCurrSectSrcAddr != EndAddr )
  {
    /* Move to the next page */
    StateDataPtr->FeeCurrSectSrcAddr -= FEE_DFLASH_PAGE_SIZE;
    /* [cover parentID={B4429EDE-559D-4304-9479-4C28E39E4FF9}]
    Block page count is not 0
    [/cover] */
    if(StateDataPtr->FeeBlkPageCount != FEE_ZERO)
    {
      StateDataPtr->FeeBlkPageCount -= FEE_ONE;
    }
  }
  else
  {
    /* Goto the next state */
    StateDataPtr->FeeCacheState = FEE_CACHE_UPDATE_COMPLETE;
  }
}

/*******************************************************************************
** Syntax : static uint32 Fee_lGetBlkCycleCount(const uint16 Index)           **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  Index      Cache Index for targeted logical block       **
**                                                                            **
** Parameters (in-out) :None                                                  **
**                                                                            **
** Return value    :  uint32     Fetches the cycle count for the logical block**
**                                                                            **
** Description : This utility function fetches the cycle count for a          **
**               logical block from DFLASH.                                   **
*******************************************************************************/
/*[cover parentID={DD7D4A15-7749-4849-8E49-A96FE968B15D}][/cover]*/
static uint32 Fee_lGetBlkCycleCount(const uint16 Index)
{
  Fee_StateDataType  *StateDataPtr;
  const uint8        *TempArrayPtr;
  uint32              Address;
  uint32              BlockCycleCount;
  uint32              TempVal;
  Std_ReturnType      RetVal;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  BlockCycleCount = FEE_32_BIT_ALL_ONES;

  /* Initialize the temp array */
  StateDataPtr->FeeTempArray[0U] = (uint32)FEE_RESET;
  StateDataPtr->FeeTempArray[1U] = (uint32)FEE_RESET;

  /* Read block cycle count */
  Address = (StateDataPtr->FeeBlockInfo[Index]).Address;
  /*[cover parentID={DDAB992A-A350-4368-8133-EE91E9CE6745}][/cover]*/
  if( Address != FEE_RESET )
  {
    /* Read the header (2 Words) */
    /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for interfacing
    with FLS.FEE is passing parameters to FLS APIs, casting is needed
    to match with the Fls API prototype.*/

    /*[cover parentID={DBA142A2-FD87-46eb-9032-FED3E7B81D3C}][/cover]*/
    RetVal = Fls_17_Dmu_ReadWordsSync((Fls_17_Dmu_AddressType)Address, \
                                      (uint32 *)(StateDataPtr->FeeTempArray), \
                                      (Fls_17_Dmu_LengthType)\
                                      (FEE_DFLASH_PAGE_SIZE /
                                       FEE_DFLASH_WORD_SIZE));
    /*[cover parentID={24478595-F8C0-4da5-A4CA-A899AB6AA739}][/cover]*/
    if( RetVal != E_OK )
    {

      /*Check if the previous copy of block is available.if yes then read the
      BCC from this block*/
      /*[cover parentID={E2048E9A-895D-40de-9E64-9B6AD3003948}][/cover]*/
      Address = (StateDataPtr->FeeBlockInfo[Index]).PrevCopyAddress;
      if( Address != FEE_RESET )
      {
        /* Read the header (2 Words) */
        /*[cover parentID={0AB1883F-CDF8-4719-92BD-36664A4B99D5}][/cover]*/
        RetVal = Fls_17_Dmu_ReadWordsSync(Address, (StateDataPtr->FeeTempArray),
                                (FEE_DFLASH_PAGE_SIZE / FEE_DFLASH_WORD_SIZE));

        /*[cover parentID={56F8293F-A427-450f-99B0-A3A457D7D302}][/cover]*/
        if(RetVal == E_OK)
        {
          /* Block Cycle count is 24 bits starting from 3rd byte of FeeTempArray
          Read the word from second byte and extract the upper 24bits */
          TempArrayPtr = (uint8 *)(StateDataPtr->FeeTempArray);
          /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
          array indexing used for FEE application buffers.
          Pointers are accessing the correct memory range locations.
          The access range is within the boundaries of the buffer. */
          TempArrayPtr += FEE_BLOCK_CYL_CNT_POS;
          /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform
          32 bit access and array is memory aligned. TempArrayPtr is poiniting to
          FeeTempArray which is part of Fee_StateDataType. FeeTempArray is so placed
          to have 4 byte alignment*/
          TempVal = *((const uint32 *)TempArrayPtr);
          BlockCycleCount = (TempVal >> FEE_EIGHT);
          /*Add the 1 to BCC of previous copy of block. This will give the
          BCC of current copy of block*/
          BlockCycleCount = BlockCycleCount + FEE_ONE;
        }
        else
        {
          BlockCycleCount = FEE_32_BIT_ALL_ONES;
        }
      }
      else
      {
        BlockCycleCount = FEE_32_BIT_ALL_ONES;
      }
    }
    else
    {
      /* Block Cycle count is 24 bits starting from 3rd byte of FeeTempArray.
         Read the word from second byte and extract the upper 24bits */
      TempArrayPtr = (uint8 *)(StateDataPtr->FeeTempArray);
      /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
      array indexing used for FEE application buffers.
      Pointers are accessing the correct memory range locations.
      The access range is within the boundaries of the buffer. */
      TempArrayPtr += FEE_BLOCK_CYL_CNT_POS;
      /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform
      32 bit access and array is memory aligned. TempArrayPtr is poiniting to
      FeeTempArray which is part of Fee_StateDataType. FeeTempArray is so placed
      to have 4 byte alignment*/
      TempVal = *((const uint32 *)TempArrayPtr);
      BlockCycleCount = (TempVal >> FEE_EIGHT);
    }
  }
  /* [cover parentID={34F26C48-1097-4c68-A607-71E65034E132}]
  Return
  [/cover] */
  return(BlockCycleCount);

}/*End of Fee_lGetBlkCycleCount */

/*******************************************************************************
** Syntax : LOCAL_INLINE uint8 Fee_lCheckPrevWordline(                        **
**                                 Fee_SectorInfoType *const SectorInfoPtr,   **
**                                 const uint32 EndAddr                       **
**                                      )                                     **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :SectorInfoPtr: Pointer to Sector Info                 **
**                     :EndAddr: Sector base addr                             **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  uint8                                                   **
**                  FEE_SP_INIT: Sector end is not reached                    **
**                  FEE_SP_DONE: Sector end reached                           **
** Description : This utility function will check if the CurrSectSrcAddr      **
**  has reached the end address. If not, it decrements the CurrSectSrcAddr    **
**  by word-line size. If the end address is reached, this function computes  **
**  the first free WL address and the sector used status.                     **
*******************************************************************************/
/* [cover parentID={C29C319E-7350-4cc0-9D7A-DD9D9E708951}]
Fee_lCheckPrevWordline
[/cover] */
/* [cover parentID={A29D3C4F-7101-458b-AE6C-8331A8F41D6F}][/cover] */
LOCAL_INLINE uint8 Fee_lCheckPrevWordline(Fee_SectorInfoType *const
    SectorInfoPtr, const uint32 EndAddr)
{
  Fee_StateDataType   *StateDataPtr;
  uint8                RetVal;
  uint32               NonZeroWlCount;
  uint8                SectorState;
  uint8                UnerasableWlCount;

  RetVal = FEE_SP_INIT;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  NonZeroWlCount = SectorInfoPtr->NonZeroWLCount;
  SectorState = SectorInfoPtr->State;
  UnerasableWlCount = SectorInfoPtr->UnerasableWLCount;

  /* Check if all pages have been read */
  /* [cover parentID={F912EE72-F924-4c6b-857C-8C1E3D08E732}][/cover] */
  if ( StateDataPtr->FeeCurrSectSrcAddr == EndAddr )
  {
    /* EndAddr reached - State page search complete */
    RetVal = FEE_SP_DONE;

    /************ Compile NextFreeWL Address and Sector used state **********/
    /* [cover parentID={DA8A2871-21E8-4ecf-A5CB-481A42979CA2}][/cover] */
    if (NonZeroWlCount == FEE_RESET)
    {
      /* The sector is empty -
         NextFreeWlAddr = BaseAddr, Sector status = Unused (default value) */
      SectorInfoPtr->NextFreeWLAddr = EndAddr;
    }
    else
    {
      Fee_lGetSectorFreeWL(SectorInfoPtr);
      /* Refer UTP AI00238899 - Don't verify if sector end is reached */
      if((SectorInfoPtr->NextFreeWLAddr) < (EndAddr + FEE_DFLASH_SECTOR_SIZE))
      {
        /* Refer UTP AI00194703 - Identify/confirm next empty word line */
        Fee_lComputeNextWLAddr(SectorInfoPtr);
      }

      /* Determine Sector Used state */
      /* [cover parentID={08A0868F-FB34-4e14-B1F5-6F729FC369CC}][/cover] */
      if (SectorState == FEE_ERASED)
      {
        if(((UnerasableWlCount == FEE_RESET) && (NonZeroWlCount == FEE_ONE)) ||
            ((UnerasableWlCount == FEE_ONE) && (NonZeroWlCount == FEE_TWO)) ||
            ((UnerasableWlCount == FEE_TWO) && (NonZeroWlCount == FEE_THREE)))
        {
          /* Sector is unused (Default value) */
          SectorInfoPtr->Status.Used = FEE_RESET ;
        }
        else
        {
          SectorInfoPtr->Status.Used = FEE_SET ;
        }
      }
      else
      {
        SectorInfoPtr->Status.Used = FEE_SET ;
      }
    } /* if (NonZeroWlCount == FEE_RESET) */
  }
  else
  {
    /* Move to the previous word line */
    StateDataPtr->FeeCurrSectSrcAddr -= FEE_DFLASH_WORDLINE_SIZE;
  }

  return(RetVal);

}

/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lGetSectorFreeWL(Fee_SectorInfoType *const  **
**                                                  SectorInfoPtr)            **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : SectorInfoPtr: Pointer to current sector info structure  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This utility function will determine the free WL of sector   **
** .This information will be updated in given sector info structure.          **
*******************************************************************************/
/* [cover parentID={3E16486F-D1F2-44fc-BE69-C3E08CBEFB77}][/cover] */
LOCAL_INLINE void Fee_lGetSectorFreeWL(Fee_SectorInfoType *const SectorInfoPtr)
{

  uint32               UnerasableWlAddr1;
  uint32               UnerasableWlAddr2;
  uint32               NonZeroWlAddr[3];
  uint32               StatePageAddr;
  uint8                UnerasableWlCount;
  uint8                SectorState;


  UnerasableWlAddr1 = SectorInfoPtr->UnerasableWLAddr[0];
  UnerasableWlAddr2 = SectorInfoPtr->UnerasableWLAddr[1];
  UnerasableWlCount = SectorInfoPtr->UnerasableWLCount;
  NonZeroWlAddr[0] = SectorInfoPtr->NonZeroWLAddr[0];
  NonZeroWlAddr[1] = SectorInfoPtr->NonZeroWLAddr[1];
  NonZeroWlAddr[2] = SectorInfoPtr->NonZeroWLAddr[2];
  StatePageAddr = SectorInfoPtr->StatePageAddr;
  SectorState = SectorInfoPtr->State;

  /* Updating NextFreeWLAddr of the sector */
  /* [cover parentID={DE367CD0-46E9-419e-BCAC-151C0058CA50}][/cover] */
  if(((NonZeroWlAddr[0] == UnerasableWlAddr1) &&
      (UnerasableWlCount != FEE_RESET)) ||
      ((NonZeroWlAddr[0] == UnerasableWlAddr2) &&
       (UnerasableWlCount != FEE_RESET)))
  {
    /* [cover parentID={7F898C8D-83DA-4882-87C6-14FD39BE6F11}][/cover] */
    if(SectorState == FEE_ERASED)
    {
      SectorInfoPtr->NextFreeWLAddr = Fee_lGetNextWLAddr(StatePageAddr);
      while (Fee_lIsUnerasableAddr(SectorInfoPtr->NextFreeWLAddr) == TRUE)
      {
        SectorInfoPtr->NextFreeWLAddr = Fee_lGetNextWLAddr(
                                          SectorInfoPtr->NextFreeWLAddr);
      }
    }
    else
    {
      /* [cover parentID={855564D7-C521-4f2f-BDC9-EB6FD9AA53E0}][/cover] */
      /*Check if there is only one unerasable WL. If yes then free WL will be
      next to 2nd non-zero WL. */
      if(NonZeroWlAddr[0] == UnerasableWlAddr1)
      {
        SectorInfoPtr->NextFreeWLAddr = Fee_lGetNextWLAddr(NonZeroWlAddr[1]);
        if(SectorInfoPtr->NextFreeWLAddr == UnerasableWlAddr1)
        {
          SectorInfoPtr->NextFreeWLAddr =
          Fee_lGetNextWLAddr(SectorInfoPtr->NextFreeWLAddr);
        }
      }
      /* [cover parentID={0BE90966-851F-466d-97B0-BEFBA1F090A5}][/cover] */
      /*Check if there is 2 unerasable WL. If yes then free WL will be
      next to either 2nd or 3rd non-zero WL. */
      else
      {
         /* [cover parentID={F8F1A562-A64B-40f4-B878-26C40E133CD3}][/cover] */
        if(NonZeroWlAddr[1] == UnerasableWlAddr1)
        {
          SectorInfoPtr->NextFreeWLAddr =
          Fee_lGetNextWLAddr(NonZeroWlAddr[2]);
          while(Fee_lIsUnerasableAddr(SectorInfoPtr->NextFreeWLAddr) == TRUE)
          {
            SectorInfoPtr->NextFreeWLAddr = Fee_lGetNextWLAddr(
                                            SectorInfoPtr->NextFreeWLAddr);
          }
        }
        else
        {
          SectorInfoPtr->NextFreeWLAddr =
          Fee_lGetNextWLAddr(NonZeroWlAddr[1]);
          while(Fee_lIsUnerasableAddr(SectorInfoPtr->NextFreeWLAddr) == TRUE)
          {
            SectorInfoPtr->NextFreeWLAddr = Fee_lGetNextWLAddr(
                                            SectorInfoPtr->NextFreeWLAddr);
          }
        }
      }
    }

  }
  else
  {
    SectorInfoPtr->NextFreeWLAddr = Fee_lGetNextWLAddr(NonZeroWlAddr[0]);
  }

}

#endif

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/*******************************************************************************
** Syntax : LOCAL_INLINE uint8 Fee_lEvaluateStatePageMarker(void)             **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :None                                                  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  FEE_SP_CLEAN: if the State Page Marker is Valid         **
**                    FEE_SP_DIRTY: if the State Page Marker is Non Zero      **
**                    FEE_SP_INVALID: if the State Page Marker is Zero        **
**                                                                            **
** Description : This utility function will evaluate the state page Marker    **
**  content and returns the status                                            **
*******************************************************************************/
/* [cover parentID={8D5082EC-AD0E-4514-B0A3-32C5E2C693EF}][/cover]*/
LOCAL_INLINE uint8 Fee_lEvaluateStatePageMarker(void)
{
  Fee_StateDataType *StateDataPtr;
  uint8             *BufferPtr;
  uint32             Marker[2];
  Std_ReturnType     FlsRetVal;
  uint8              ReturnVal;

  ReturnVal = FEE_SP_CLEAN;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* Read the marker (last 8 bytes) of the current page */
  /* Offset will be 120 */

  BufferPtr = &(StateDataPtr->FeeReadWriteBuffer[FEE_SP_MARKERFIELD_START]);

  /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for interfacing with
  FLS.FEE is passing parameters to FLS APIs, casting is needed to match with
  the Fls API prototype. FeeReadWriteBuffer access is 4 byte align,
  (FEE_SP_MARKERFIELD_START is 120) */

  FlsRetVal = Fls_17_Dmu_ReadWordsSync(\
                   (Fls_17_Dmu_AddressType)(StateDataPtr->FeeCurrSectSrcAddr + \
                    FEE_SP_MARKERFIELD_START), \
                   (uint32 *)(BufferPtr), \
                   (Fls_17_Dmu_LengthType)(FEE_STATEPAGE_MARKER_SIZE /
                    FEE_DFLASH_WORD_SIZE));

  /* [cover parentID={1B4D4D37-067E-4e56-B204-8DAB26F9DBA6}][/cover]*/
  if(FlsRetVal == E_NOT_OK)
  {
    ReturnVal = FEE_SP_DIRTY;
  }
  else
  {
    /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 32 bit
     access and array is memory aligned. .*/
    Marker[0] = *((const uint32*)(BufferPtr));
    /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 32 bit
    access and array is memory aligned. FeeReadWriteBuffer access is 4 byte align,
    (FEE_DFLASH_WORD_SIZE is 4)*/
    Marker[1] = *((const uint32*) & (BufferPtr[FEE_DFLASH_WORD_SIZE]));
    /* [cover parentID={1254D55E-FDC0-468d-AA25-96FFD2FF337E}][/cover]*/
    if((Marker[0] == FEE_RESET) && (Marker[1] == FEE_RESET))
    {
      ReturnVal = FEE_SP_INVALID;
    }
    else
    {
      /* if ReturnVal is FEE_SP_CLEAN */
      /* [cover parentID={820E6768-51EE-491a-AA17-463C10102EC0}][/cover]*/
      if ((Marker[0] != FEE_SP_MARKER_WORD_1) ||
          (Marker[1] != FEE_SP_MARKER_WORD_2))
      {
        ReturnVal = FEE_SP_DIRTY;
      }
    }
  }
  return(ReturnVal);
}

/******************************************************************************
** Syntax : LOCAL_INLINE uint8 Fee_lEvaluateStatePageFormat(void)            **
**                                                                           **
** Service ID: NA                                                            **
**                                                                           **
** Sync/Async:  Synchronous                                                  **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in-out) :None                                                 **
**                                                                           **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    : uint8                                                   **
**                    FEE_SP_CLEAN: if the state page is of New Format       **
**                    FEE_SP_INVALID: if the state page is invalid           **
**                                                                           **
** Description : This utility function will evaluate the state page content  **
**  with respect to New Format and returns the status                        **
******************************************************************************/
/* [cover parentID={E436188A-774A-4564-8439-63B5B52FE2DA}][/cover]*/
LOCAL_INLINE uint8 Fee_lEvaluateStatePageFormat(void)
{
  const Fee_StateDataType *StateDataPtr;
  const uint32             *BufferPtr;
  const uint32             *BufferPtr2;
  uint32             Data;
  uint32             Index;
  uint32             Length;
  uint8              ReturnVal;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  ReturnVal = FEE_SP_CLEAN;
  /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 32 bit
  access and array is memory aligned.*/
  BufferPtr = (const uint32*)(StateDataPtr->FeeReadWriteBuffer);
  /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 32 bit
  access and array is memory aligned. 4 byte aligned
  FEE_STATE_FIRSTFIVE_COPY_OFFSET is 40*/
  BufferPtr2 = (const uint32*)(&(StateDataPtr->FeeReadWriteBuffer[ \
                                 FEE_STATE_FIRSTFIVE_COPY_OFFSET]));

  /* check that the first word content is redundant below except page id */
  /* [cover parentID={CA0428FF-F909-4755-9472-C75D505055B6}][/cover]*/
  if((*BufferPtr & FEE_STATE_WLCOUNT_MASK) != \
      (*BufferPtr2 & FEE_STATE_WLCOUNT_MASK))
  {
    ReturnVal = FEE_SP_INVALID;
  }
  else
  {
    /* Check the state page header pages(starting from Byte-4) with its
     * duplicate copy.when Both copy matches then header pages are
     *  considered as valid */
    /* [cover parentID={B38BA74A-109D-4c16-8C91-3053B5B68965}][/cover]*/
    for(Index = FEE_RESET; Index < (FEE_STATE_PAGE_HDR_PAGES -FEE_ONE); Index++)
    {

      BufferPtr++;
      BufferPtr2++;

      if(*BufferPtr != *BufferPtr2)
      {
        ReturnVal = FEE_SP_INVALID;
        break; /* break */
      }

    }
    /* Check for second half of state page */
    /* [cover parentID={05F11B02-31B7-4b04-8061-452791CC2FEB}][/cover]*/
    if(ReturnVal != FEE_SP_INVALID)
    {

      /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 32 bit
      access and array is memory aligned. 4 byte aligned
      FEE_STATE_ALLONES_OFFSET is 80 */
      BufferPtr = (const uint32*)(&(StateDataPtr->FeeReadWriteBuffer[ \
                                    FEE_STATE_ALLONES_OFFSET]));
      /* get the length excluding CRC */


      Length = sizeof(Fee_StateHalf) / sizeof(Fee_StateHalf[0]);

      for(Index = FEE_RESET; Index < Length; Index++)
      {
        if(*BufferPtr != Fee_StateHalf[Index])
        {
          ReturnVal = FEE_SP_INVALID;
          break; /* break */
        }

        BufferPtr++;
      }
    }
    /* verify the CRC */
    if(ReturnVal != FEE_SP_INVALID)
    {
      /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 32 bit
      access and array is memory aligned.*/
      BufferPtr = (const uint32*)(&(StateDataPtr->FeeReadWriteBuffer[ \
                                    FEE_STATE_CRC_OFFSET]));
      /* Length will give the number of pages to Generate CRC */
      Length = FEE_STATE_CRC_OFFSET / FEE_DFLASH_WORD_SIZE;

      /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 32 bit
      access and array is memory aligned. */
      /* [cover parentID={86B2AAE4-F07F-48e5-BCD7-4B073271A3A9}][/cover]*/
      Data = Fee_lEvaluateStatePageCrc(\
                           (const uint32*)(StateDataPtr->FeeReadWriteBuffer), \
                           Length);
      /* [cover parentID={5C959E46-51CE-49ad-BE4C-D69295648AFF}][/cover]*/
      if( Data != *BufferPtr)
      {
        ReturnVal = FEE_SP_INVALID;
      }

    }
  }
  return(ReturnVal);
}

/*******************************************************************************
** Syntax : LOCAL_INLINE uint32 Fee_lEvaluateStatePageCrc                     **
**            (const uint32 * const DataPtr, const uint32 Length)             **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  DataPtr : Pointer to Data                               **
**                    Length : Data Length in Word                            **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  32 bit CRC value                                        **
**                                                                            **
** Description : This utility function will evaluate 32 bit CRC value over    **
**               data pointed by DataPtr for the requested Length             **
**                                                                            **
*******************************************************************************/
/* [cover parentID={566D2475-E078-4542-93B3-9AB5E1D64383}][/cover]*/
LOCAL_INLINE uint32 Fee_lEvaluateStatePageCrc(const uint32 * const DataPtr,
    const uint32 Length)
{
  uint32             Index;
  uint32             Crc32;

  Crc32 = FEE_CRC_START_VAL;
  /* [cover parentID= {3AA2CEEF-2062-4c30-95E5-2BB0CB221831}][/cover]*/
  for(Index = FEE_RESET; Index < Length; Index++)
  {
    Crc32 = CRC32(Crc32, DataPtr[Index]);

  }
  return(Crc32);
}

/******************************************************************************
** Syntax : LOCAL_INLINE uint8 Fee_lEvaluateStatePage(void)                  **
**                                                                           **
** Service ID: NA                                                            **
**                                                                           **
** Sync/Async:  Synchronous                                                  **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in-out) :None                                                 **
**                                                                           **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    : uint8                                                   **
**                    FEE_SP_CLEAN: if the state page is valid               **
**                    FEE_SP_DIRTY: if the state page is dirty               **
**                    FEE_SP_INVALID: if the state page is invalid           **
**                                                                           **
** Description : This utility function will evaluate the state page content  **
**  and returns the state page status                                        **
******************************************************************************/
/* [cover parentID={9D6ADF48-7C6D-4e58-9411-8FE8C93A9C55}][/cover]*/
LOCAL_INLINE uint8 Fee_lEvaluateStatePage(void)
{
  Fee_StateDataType *StateDataPtr;
  const uint8             *BufferPtr;
  Std_ReturnType     FlsRetVal;
  uint8              State;
  uint8              ReturnVal;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* Read the state page content (first 120 bytes) of the current page */
  FlsRetVal = Fls_17_Dmu_ReadWordsSync(
                (Fls_17_Dmu_AddressType)StateDataPtr->FeeCurrSectSrcAddr,
                /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for interfacing
                with FLS.FEE is passing parameters to FLS APIs, casting is
                needed to match with the Fls API prototype.*/
                (uint32 *)StateDataPtr->FeeReadWriteBuffer,
                (Fls_17_Dmu_LengthType)
                (FEE_STATEPAGE_DATA_SIZE / FEE_DFLASH_WORD_SIZE));
  BufferPtr = StateDataPtr->FeeReadWriteBuffer;
  State = BufferPtr[FEE_ONE];

  /* [cover parentID= {2880AD46-396E-4450-9C1F-37E6D9A187D7}][/cover]*/
  if( (FlsRetVal == E_NOT_OK) ||
      (!((State == FEE_VALID) || (State == FEE_ERASED))) )
  {
    ReturnVal = FEE_SP_INVALID;
  }
  else
  {
    ReturnVal = Fee_lEvaluateStatePageFormat();

  }

  /* [cover parentID= {324341E6-86B4-4273-B048-C4668AF7147E}][/cover]*/
  if(FEE_SP_INVALID != ReturnVal)
  {
    /* Check the marker field */
    ReturnVal = Fee_lEvaluateStatePageMarker();
  }

  return(ReturnVal);
}

/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lSetInitGc(const uint8 DFlashStatus)        **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :DFlashStatus: State of DFlash sectors                     **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This utility function sets the InitGc state based on         **
**  the DFlashStatus                                                          **
*******************************************************************************/
/* [cover parentID= {73069EFB-0578-40c2-8DCF-BAD3CAFF16D5}][/cover]*/
LOCAL_INLINE void Fee_lSetInitGc(const uint8 DFlashStatus)
{

  Fee_StateDataType  *StateDataPtr;
  Fee_SectorInfoType *SectorInfoPtr0;
  Fee_SectorInfoType *SectorInfoPtr1;
  uint32              S0StateCnt;
  uint32              S1StateCnt;
  #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
  uint16              S0HardeningCnt;
  uint16              S1HardeningCnt;
  #endif
  uint8               S0Used;
  uint8               S1Used;
  uint8               S0Dirty;
  uint8               S1Dirty;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  SectorInfoPtr0 = &StateDataPtr->FeeSectorInfo[0];
  SectorInfoPtr1 = &StateDataPtr->FeeSectorInfo[1];

  StateDataPtr->FeeInitGCState = FEE_INITGC_NORMAL;

  S0StateCnt = SectorInfoPtr0->StateCount;
  S1StateCnt = SectorInfoPtr1->StateCount;
  #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
  S0HardeningCnt = SectorInfoPtr0->QsHardeningOffset;
  S1HardeningCnt = SectorInfoPtr1->QsHardeningOffset;
  #endif
  S0Used = SectorInfoPtr0->Status.Used;
  S1Used = SectorInfoPtr1->Status.Used;
  S0Dirty = SectorInfoPtr0->Status.Dirty;
  S1Dirty = SectorInfoPtr1->Status.Dirty;

  /* Update the state count */
  /* [cover parentID= {C8DC623E-722C-4c22-82C6-A1FB9CBD59EB}][/cover]*/
  if (S0StateCnt > S1StateCnt)
  {
    /* [cover parentID= {507D65F7-806E-444f-BD0D-48E7AB6E4489}][/cover]*/
    StateDataPtr->FeeStateCount = S0StateCnt;
    #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
    StateDataPtr->FeeQsHardeningOffset = S0HardeningCnt;
    #endif
  }
  else
  {
    /* [cover parentID= {ED97A300-DEC0-48aa-990E-F241C81D0914}][/cover]*/
    StateDataPtr->FeeStateCount = S1StateCnt;
    #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
    StateDataPtr->FeeQsHardeningOffset = S1HardeningCnt;
    #endif
  }

  switch (DFlashStatus)
  {
    /* Both the sectors empty */
    /* [cover parentID= {437127BC-D0E7-484a-A909-06C634870167}][/cover]*/
    case FEE_S0_S1_EMPTY:
    {
      /* [cover parentID= {0BB90C71-4B01-4a8b-ACE0-CC2013B3FB1C}][/cover]*/
      StateDataPtr->FeeInitGCState = FEE_INITGC_HANDLE_VIRGIN;
      StateDataPtr->FeePrepDFLASHState = FEE_PREPDF_MARK_S0_ERASED_SP;
      StateDataPtr->FeeCurrSectSrcAddr =
        StateDataPtr->FeeSectorInfo[0].NextFreeWLAddr;
      S0Dirty = FEE_RESET;
      S1Dirty = FEE_RESET;

      break;
    }
    /* S0 is valid */
    /* [cover parentID= {A087EB8C-1529-4626-8066-5D38026B89AF}][/cover]*/
    case FEE_S0_VALID:
    {
      /* Check if copy was interrupted */
      /* [cover parentID= {2CF34704-3B99-48fd-810A-D228E9B68B29}][/cover]*/
      if(S1Used == FEE_SET )
      {
        StateDataPtr->FeeGcResumeState = FEE_INITGC_DATA_COPY_S0_S1;
        S1Dirty = FEE_RESET;
      }
      else
      {
        /* [cover parentID= {84F10F75-7524-4a5e-8E22-DBEE37FEA96E}][/cover]*/
        StateDataPtr->FeeGcResumeState = FEE_INITGC_NORMAL_S0;
      }
      break;
    }
    /* S1 is valid */
    /* [cover parentID= {9051E9E9-7B05-4a49-A25F-F8E352C71569}][/cover]*/
    case FEE_S1_VALID:
    {
      /* Change the current sector to SECTOR1 */
      StateDataPtr->FeeStatusFlags.FeeCurrSector = FEE_SECTOR1;
      /* Check if copy was interrupted */
      /* [cover parentID= {552B623C-9B5F-47b1-8174-6BFF007CB993}][/cover]*/
      if(S0Used == FEE_SET )
      {
        /* [cover parentID= {990D0812-83F0-40a9-82D7-84F459F021DB}][/cover]*/
        StateDataPtr->FeeGcResumeState = FEE_INITGC_DATA_COPY_S1_S0;
        S0Dirty = FEE_RESET;
      }
      else
      {
        /* [cover parentID= {86CDF4FB-1643-45a1-9613-CE3979F3087D}][/cover]*/
        StateDataPtr->FeeGcResumeState = FEE_INITGC_NORMAL_S1;
      }
      break;
    }
    /* Erase interrupted */
    /* [cover parentID= {860B3C41-9588-40c2-8EC9-1E0EF061FF1B}][/cover]*/
    case FEE_S0_S1_VALID:
    {
      /* [cover parentID= {F06DF482-D34D-46aa-8D79-6427A673BBFA}][/cover]*/
      if (S0StateCnt > S1StateCnt)
      {
        /* [cover parentID= {90F64D06-60C7-4f78-A999-3E4016793697}][/cover]*/
        StateDataPtr->FeeGcResumeState = FEE_INITGC_ERASE_S1;
        S1Dirty = FEE_RESET;
      }
      else
      {
        /* Change the current sector to SECTOR1 */
        /* [cover parentID= {FE397E2D-87EB-442a-B32D-C8895EEA339A}][/cover]*/
        StateDataPtr->FeeStatusFlags.FeeCurrSector = FEE_SECTOR1;
        StateDataPtr->FeeGcResumeState = FEE_INITGC_ERASE_S0;
        S0Dirty = FEE_RESET;
      }
      break;
    }
    case FEE_S0_S1_INVALID:
    {
      S0Dirty = FEE_RESET;
      S1Dirty = FEE_RESET;
      StateDataPtr->FeeInitGCState = FEE_INITGC_HANDLE_INVALID;

      break;
    }
    default:
    {
      break;
    }
  }

  /* [cover parentID= {F8958411-EB50-4857-832D-54316BC52BEA}][/cover]*/
  if ( (S0Dirty != FEE_RESET) || (S1Dirty != FEE_RESET) )
  {
    /* [cover parentID= {BDF753A9-8E26-49f9-BAD6-D035AEEE3D4E}][/cover]*/
    StateDataPtr->FeeInitGCState = FEE_INITGC_HANDLE_DIRTY;
    StateDataPtr->FeeRepairStep = FEE_PROGRAM_MARKER;
  }

  SectorInfoPtr0->Status.Dirty = S0Dirty;
  SectorInfoPtr1->Status.Dirty = S1Dirty;

}

/*******************************************************************************
** Syntax : LOCAL_INLINE uint8 Fee_lBuildDFlashStatus(void)                   **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :None                                                  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  DFlash status                                           **
**                                                                            **
** Description : This utility function compiles the DFLASH status based on    **
**  sector0 and sector1 state contents                                        **
*******************************************************************************/
/*[cover parentID={361664FB-92BB-45d0-96FD-3DB7EB1BAAC5}][/cover]*/
LOCAL_INLINE uint8 Fee_lBuildDFlashStatus(void)
{
  const Fee_StateDataType *StateDataPtr;
  uint8              S0State;
  uint8              S1State;
  uint8              S0Used;
  uint8              S1Used;
  uint8              RetVal;
  boolean            S0Empty;
  boolean            S1Empty;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  S0State = StateDataPtr->FeeSectorInfo[0].State;
  S1State = StateDataPtr->FeeSectorInfo[1].State;
  S0Used = StateDataPtr->FeeSectorInfo[0].Status.Used;
  S1Used = StateDataPtr->FeeSectorInfo[1].Status.Used;

  S0Empty = Fee_lIsSectorEmpty(S0State, S0Used);
  S1Empty = Fee_lIsSectorEmpty(S1State, S1Used);

  /*[cover parentID={5DC15EEE-FEAB-4d37-8B60-33103321EE84}][/cover]*/
  if ( (S0State == FEE_VALID) && (S1State == FEE_ERASED) )
  {
    RetVal = FEE_S0_VALID;
  }
  /*[cover parentID={0EEDBA10-E6EF-406a-ABE5-10FBCCAA2F02}][/cover]*/
  else if ( (S0State == FEE_ERASED) && (S1State == FEE_VALID) )
  {
    RetVal = FEE_S1_VALID;
  }
  /*[cover parentID={65D0B61B-6D8B-404f-BE5A-9A0D37531796}][/cover]*/
  else if ( (S0State == FEE_VALID) && (S1State == FEE_VALID) )
  {
    /* This happens when Erase of S0 / S1 is interrupted just before the start
       of Erase */
    RetVal = FEE_S0_S1_VALID;
  }
  /*[cover parentID={F3075C9E-4880-4fba-B70B-386873BC3F2E}][/cover]*/
  else if ( (S0State == FEE_VALID) && (S1State == FEE_STATELESS) )
  {
    /* This happens when Erase of S1 is interrupted. Handle it the same way as
       S0_S1_VALID so that S1 can be erased as part of INIT GC */
    RetVal = FEE_S0_S1_VALID;
  }
  /*[cover parentID={E87BE6A8-0753-4a79-B7CB-13929B5F1394}][/cover]*/
  else if ( (S0State == FEE_STATELESS) && (S1State == FEE_VALID) )
  {
    /* This happens when Erase of S0 is interrupted. Handle it the same way as
       S0_S1_VALID so that S0 can be erased as part of INIT GC */
    RetVal = FEE_S0_S1_VALID;
  }
  /*[cover parentID={EA7E82BC-6899-45ea-919F-A5630C203DBC}][/cover]*/
  else if ((S0Empty == (boolean)TRUE) && (S1Empty == (boolean)TRUE))
  {
    RetVal = FEE_S0_S1_EMPTY;
  }
  /* Any other combination leads to invalid state */
  else
  {
    RetVal = FEE_S0_S1_INVALID;
  }

  return(RetVal);

}

/*******************************************************************************
** Syntax : static void Fee_lUpdateNonZeroWLInfo(                             **
**                                   Fee_SectorInfoType *const SectorInfoPtr, **
**                                   const uint32        SrcAddr              **
**                                  )                                         **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :SectInfoPtr: Pointer to Sector Info                   **
**                     :SrcAddr: Current non zero page address.               **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This utility function will update the NonZeroWLAddr and      **
**  NonZeroWLCount                                                            **
*******************************************************************************/
/* [cover parentID={9B13D952-71FE-493d-8574-10F804C7F0E9} ] [/cover] */
static void Fee_lUpdateNonZeroWLInfo(Fee_SectorInfoType *const SectorInfoPtr, \
                                     const uint32 SrcAddr)
{
  uint32 NonZeroWlCount;
  NonZeroWlCount = SectorInfoPtr->NonZeroWLCount;
  /* [cover parentID={23D31021-77A8-40d0-9BD2-D6F00E8008AC}]
      Fee_lUpdateNonZeroWLInfo
     [/cover] */
  /* Update the non-zero WL location if not updated */
  if (NonZeroWlCount <= FEE_TWO)
  {
    SectorInfoPtr->NonZeroWLAddr[NonZeroWlCount] = SrcAddr;
  }

  /* Increment non-zero WL count */
  SectorInfoPtr->NonZeroWLCount++;
}

/*******************************************************************************
** Syntax : LOCAL_INLINE uint8 Fee_lGetSectorInfo (                           **
**                                     const uint32 BankNumber,               **
**                                     const uint32 EndAddr                   **
**                                   )                                        **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :(uint32)BankNumber: Sector number                     **
**                      (uint32)EndAddr: Base of Sector                       **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  uint8                                                   **
**                  FEE_SP_INIT: Sector scanning for state page is on going.  **
**                  FEE_SP_DONE: Sector scanning is completed                 **
** Description : This utility function will search through the DFLASH from    **
**  the bottom till base of the sector and get sector state information       **
*******************************************************************************/
/* [cover parentID={804DB87B-2AE9-421f-97F0-0D69563B9824},
{FC609CF8-1846-43bc-8922-86A42976F7A3}, {130CBADC-2E4F-4603-8D5C-F91DA268D7C3}]
Fee_lGetSectorInfo
[/cover] */
LOCAL_INLINE uint8 Fee_lGetSectorInfo(const uint32 BankNumber,
                                      const uint32 EndAddr)
{
  Fee_StateDataType   *StateDataPtr;
  Fee_SectorInfoType  *SectorInfoPtr;
  const uint32              *BuffPtr;
  uint32               SrcAddr;
  uint32               StateCount1;
  uint32               StateCount2;
  Std_ReturnType       RetVal;
  uint8                ReturnVal;
  #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
  uint32               QsOffset;
  #endif


  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  SectorInfoPtr = &StateDataPtr->FeeSectorInfo[BankNumber];

  SrcAddr = StateDataPtr->FeeCurrSectSrcAddr;

  /* Read the header of status page */
  /* [cover parentID={804DB87B-2AE9-421f-97F0-0D69563B9824}][/cover] */
  RetVal = Fls_17_Dmu_ReadWordsSync((Fls_17_Dmu_AddressType)SrcAddr,
                                    /* MISRA2012_RULE_11_3_JUSTIFICATION:This is
                                    done for interfacing with FLS.FEE is passing
                                    parameters to FLS APIs, casting is needed to
                                    match with the Fls API prototype.*/
                                    (uint32 *)StateDataPtr->FeeReadWriteBuffer,
                                    (Fls_17_Dmu_LengthType)
                                    ((FEE_DFLASH_PAGE_SIZE * FEE_TWO)
                                     / FEE_DFLASH_WORD_SIZE));

  /* Check if DBER is found in the header */
  /* DBER is NOT found */
  /* [cover parentID={132A0549-6A7E-4e03-A4F4-2334153178ED}][/cover] */
  if(RetVal == E_OK)
  {
    /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 32 bit
     access and array is memory aligned.*/
    BuffPtr = (uint32 *)StateDataPtr->FeeReadWriteBuffer;
    /* Check if the header is zero */

    if ((*BuffPtr == FEE_RESET) && ((BuffPtr[FEE_ONE]) == FEE_RESET) &&
        ((BuffPtr[FEE_TWO]) == FEE_RESET) && ((BuffPtr[FEE_THREE]) == FEE_RESET))
    {
      /* Zero page */
      /* Move to previous word line */
    }
    /* Non-zero page */
    /* [cover parentID={46088235-CF34-4932-991B-A3F1410D4A1B}][/cover] */
    else
    {
      Fee_lUpdateNonZeroWLInfo(SectorInfoPtr, SrcAddr);
      /* Check if it is state page */
      /* [cover parentID={830D2BF2-2C18-4cee-89A3-D75C87DD6368}][/cover] */
      if ( StateDataPtr->FeeReadWriteBuffer[FEE_STATE_PAGE_ID_POS] ==
           FEE_STATE_FIRST_PAGE_ID )
      {
        /* [cover parentID={49E3092F-8499-4357-B57F-98E62AA601E6}][/cover] */
        RetVal = Fee_lEvaluateStatePage();
        /* [cover parentID={E0915EAC-178B-4af9-921E-64887A137EE2}][/cover] */
        if ( (RetVal == FEE_SP_CLEAN) || (RetVal == FEE_SP_DIRTY))
        {
          /* State Count is at byte 4 of the buffer - move pointer by one word */

          StateCount2 = BuffPtr[FEE_ONE];
          StateCount1 = SectorInfoPtr->StateCount;
          /* [cover parentID={DFABC109-C94A-43cb-831F-F23291A9D2B2}][/cover] */
          if (StateCount2 > StateCount1)
          {
            SectorInfoPtr->Status.Dirty = RetVal;
            SectorInfoPtr->State =
              StateDataPtr->FeeReadWriteBuffer[FEE_STATE_PAGE_STATE_POS];
            SectorInfoPtr->UnerasableWLCount =
              (StateDataPtr->FeeReadWriteBuffer[FEE_STATE_PAGE_UERWL_POS] >>
               FEE_FOUR) & 0x0FU;
            SectorInfoPtr->StateCount = StateCount2;
            /* Unerasable WL Address is at byte 12 of the buffer -
               move pointer by three words */

            SectorInfoPtr->UnerasableWLAddr[FEE_ZERO] = BuffPtr[FEE_THREE];
            SectorInfoPtr->UnerasableWLAddr[FEE_ONE]  = BuffPtr[FEE_FIVE];
            SectorInfoPtr->StatePageAddr = SrcAddr;
            #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
            /* QS Data offset stored in state page is extracted and stored, so that  */
            QsOffset = BuffPtr[0];
            QsOffset = (QsOffset & FEE_QS_DATA_OFFSET_MASK);
            QsOffset = QsOffset >> FEE_QS_DATA_OFFSET_START;
            SectorInfoPtr->QsHardeningOffset = (uint16) QsOffset;
            #endif
          }/* if(StateCount2 > StateCount1) */
        }/* if ((RetVal == FEE_SP_CLEAN) || (RetVal == FEE_SP_DIRTY)) */
      }/* if(StateDataPtr->FeeReadWriteBuffer[0] == FEE_STATE_FIRST_PAGE_ID)*/
    }/* if( (*BuffPtr == FEE_ZERO) && (*(BuffPtr + 1U) == FEE_ZERO) ) */
  }
  else
  {
    Fee_lUpdateNonZeroWLInfo(SectorInfoPtr, SrcAddr);
  }

  /* [cover parentID={88E32981-A6F4-45e0-BE7D-7593C539A43D}][/cover] */
  ReturnVal = Fee_lCheckPrevWordline(SectorInfoPtr, EndAddr);

  return(ReturnVal);

}
#endif

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

/*******************************************************************************
** Syntax : static boolean Fee_lIsUnerasableAddr(const uint32 Addr)           **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :Address                                                   **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  TRUE: if Address is part of unerasable WL               **
**                    FALSE:if Address is not part of unerasable WL           **
**                                                                            **
** Description : This utility function checks if the Address is part of       **
** unerasable Word line                                                       **
*******************************************************************************/
/* [cover parentID={38625665-C299-405c-8245-9981344A0772}]
Fee_lIsUnerasableAddr
[/cover] */
/* [cover parentID={6EAF7AF1-A9CD-4af0-99A8-8802C7B55EBF}]cover] */
static boolean Fee_lIsUnerasableAddr(const uint32 Addr)
{
  const Fee_StateDataType *StateDataPtr;
  boolean            RetVal;
  uint8              UnErCount;
  uint32             NewAddr;
  uint8              BankNumber;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* Get the FEE sector index */
  if(Addr >= FEE_DFLASH_BANK1_BASE)
  {
    BankNumber = FEE_SECTOR1;
  }
  else
  {
    BankNumber = FEE_SECTOR0;
  }

  UnErCount = FEE_RESET;

  RetVal = (boolean)FALSE;

  /* Get word line beginning address of the address to be checked */

  NewAddr = (uint32)(Fee_lGetWLBeginning(Addr));

  /* Loop through to check whether Address is uneraseble */
  /* [cover parentID={DB1AFB35-9D90-4cff-B99F-4F883D7CC961}]cover] */
  while((UnErCount != StateDataPtr->FeeSectorInfo[BankNumber].UnerasableWLCount)
        && (RetVal == FALSE))
  {
    /* [cover parentID={E784AF92-085C-491e-89CA-4DFBCF82E405}]cover] */
    if(NewAddr ==
        StateDataPtr->FeeSectorInfo[BankNumber].UnerasableWLAddr[UnErCount])
    {
      RetVal = (boolean)TRUE;
    }
    else
    {
      UnErCount++;
    }
  }
  return(RetVal);
}
#endif

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/*******************************************************************************
** Syntax : static void Fee_lPrepareStatePageBuffer(const uint8 Bank,         **
**                                                  const uint8 SectorState)  **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  Bank: Sector Number                                     **
**                    SectorState: Erased / Valid                             **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This routine will update the write buffer for state page     **
** programming of a sector                                                    **
*******************************************************************************/
/* [cover parentID={9E1839E0-2F3B-4038-B42B-DEF7C312D59B}]
Fee_lPrepareStatePageBuffer
[/cover] */
/* [cover parentID={A73F92D8-FC32-4351-8FCC-DBEDDD3663DD}] [/cover] */
static void Fee_lPrepareStatePageBuffer(const uint8 Bank,
                                        const uint8 SectorState)
{
  uint32              StateCnt;
  uint32              WordlineAddr;
  uint32              WordlineAddr2;
  uint32              Index;
  uint32              Length;
  Fee_StateDataType  *StateDataPtr;
  uint8              *ArrPtr;
  uint8               WordlineCnt;
  #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
  uint8              QsHardenOffsetLSB;
  uint8              QsHardenOffsetMSB;
  uint16             QsHardenOffset;
  #endif

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  Fee_lClearFeeGcReadWriteBuffer();
  ArrPtr = StateDataPtr->FeeGcReadWriteBuffer;

  /* Get the State count */
  StateCnt = StateDataPtr->FeeStateCount;
  StateCnt = StateCnt + FEE_ONE;

  /* Get the UnerasableWL count */
  WordlineCnt = StateDataPtr->FeeSectorInfo[Bank].UnerasableWLCount;
  #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
  QsHardenOffset = (uint16)(StateDataPtr->FeeQsHardeningOffset);
  QsHardenOffsetLSB = (uint8)QsHardenOffset;
  QsHardenOffsetMSB = (uint8)(QsHardenOffset >> 8);
  #endif
  /* Get the UnerasableWL Address */
  WordlineAddr = StateDataPtr->FeeSectorInfo[Bank].UnerasableWLAddr[0];
  WordlineAddr2 = StateDataPtr->FeeSectorInfo[Bank].UnerasableWLAddr[1];

  /* Update the page id of the 1st page of state page */

  *ArrPtr = FEE_STATE_FIRST_PAGE_ID;
  ArrPtr[FEE_STATE_PAGE_STATE_POS] = SectorState;
  ArrPtr[FEE_STATE_PAGE_STATE_POS + FEE_STATE_FIRSTFIVE_COPY_OFFSET] =
    SectorState;
  #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)

  ArrPtr[FEE_STATE_PAGE_QS_OFFSET_LSB] = QsHardenOffsetLSB;
  ArrPtr[FEE_STATE_PAGE_QS_OFFSET_MSB] =
    (((WordlineCnt << 4) & 0xF0U) + ((QsHardenOffsetMSB) & 0x0FU));
  ArrPtr[FEE_STATE_PAGE_QS_OFFSET_LSB + FEE_STATE_FIRSTFIVE_COPY_OFFSET] =
    QsHardenOffsetLSB;
  ArrPtr[FEE_STATE_PAGE_QS_OFFSET_MSB + FEE_STATE_FIRSTFIVE_COPY_OFFSET] =
    (((WordlineCnt << 4) & 0xF0U) + ((QsHardenOffsetMSB) & 0x0FU));
  #else

  ArrPtr[FEE_STATE_PAGE_UERWL_POS] = ((WordlineCnt << 4) & 0xF0U );

  ArrPtr[FEE_STATE_PAGE_UERWL_POS + FEE_STATE_FIRSTFIVE_COPY_OFFSET] =
    ((WordlineCnt << 4) & 0xF0U);
  #endif
  /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 32 bit
  access and array is memory aligned.*/
  /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than array
  indexing used for FEE application buffers.Pointers are accessing the correct
   memory range locations.The access range is within the boundaries of the
   buffer. */
  *((uint32 *)(ArrPtr + FEE_STATE_PAGE_STATE_CNT_POS)) = StateCnt;
  /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 32 bit
  access and array is memory aligned.*/
  /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than array
  indexing used for FEE application buffers.Pointers are accessing the correct
  memory range locations.The access range is within the boundaries of the
  buffer. */
  *((uint32 *)\
  (ArrPtr + FEE_STATE_PAGE_STATE_CNT_POS + FEE_STATE_FIRSTFIVE_COPY_OFFSET)) \
    = StateCnt;


  if(WordlineCnt > FEE_ZERO)
  {

    /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 32 bit
     access and array is memory aligned.*/
    /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
          array indexing used for FEE application buffers.
          Pointers are accessing the correct memory range locations.
          The access range is within the boundaries of the buffer. 4 byte
          aligned FEE_STATE_PAGE_UERWL1_ADDRS_POS is 12*/
    *((uint32 *)(ArrPtr + FEE_STATE_PAGE_UERWL1_ADDRS_POS)) = WordlineAddr;
    /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 32 bit
     access and array is memory aligned. 4 byte aligned **/
    /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
          array indexing used for FEE application buffers.
          Pointers are accessing the correct memory range locations.
          The access range is within the boundaries of the buffer. */
    *((uint32 *)(ArrPtr + FEE_STATE_PAGE_UERWL2_ADDRS_POS)) = WordlineAddr2;
    /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 32 bit
     access and array is memory aligned.*/
    /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
          array indexing used for FEE application buffers.
          Pointers are accessing the correct memory range locations.
          The access range is within the boundaries of the buffer. */
    *((uint32 *)(ArrPtr + FEE_STATE_PAGE_UERWL1_ADDRS_POS + \
                 /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
                 array indexing used for FEE application buffers.
                 Pointers are accessing the correct memory range locations.
                  The access range is within the boundaries of the buffer. */
                 FEE_STATE_FIRSTFIVE_COPY_OFFSET)) = WordlineAddr;
    /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 32 bit
     access and array is memory aligned.*/
    /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
          array indexing used for FEE application buffers.
          Pointers are accessing the correct memory range locations.
          The access range is within the boundaries of the buffer. 4 byte aligned
          FEE_STATE_PAGE_UERWL2_ADDRS_POS is 20*/
    *((uint32 *)(ArrPtr + FEE_STATE_PAGE_UERWL2_ADDRS_POS + \
                 /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
                       array indexing used for FEE application buffers.
                       Pointers are accessing the correct memory range locations.
                       The access range is within the boundaries of the buffer. */
                 FEE_STATE_FIRSTFIVE_COPY_OFFSET)) = WordlineAddr2;
  }
  /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
        array indexing used for FEE application buffers.
        Pointers are accessing the correct memory range locations.
        The access range is within the boundaries of the buffer. */
  ArrPtr = StateDataPtr->FeeGcReadWriteBuffer + FEE_DFLASH_PAGE_SIZE;

  for(Index = FEE_ONE; Index < (FEE_STATE_PAGE_HDR_PAGES); Index++)
  {
    *ArrPtr = FEE_STATE_NEXT_PAGE_ID;
    /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
          array indexing used for FEE application buffers.
          Pointers are accessing the correct memory range locations.
          The access range is within the boundaries of the buffer. */
    ArrPtr += FEE_DFLASH_PAGE_SIZE;
  }

  ArrPtr = &(StateDataPtr->FeeGcReadWriteBuffer[FEE_STATE_ALLONES_OFFSET]);
  /* get the length excluding crc from All 1's field */

  Length = sizeof(Fee_StateHalf) / sizeof(Fee_StateHalf[0]);

  /* Write second half state page */
  for(Index = FEE_RESET; Index < Length; Index++)
  {
    /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 32 bit
     access and array is memory aligned.*/
    *(uint32 *)(ArrPtr) = Fee_StateHalf[Index];
    /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
    array indexing used for FEE application buffers.
     Pointers are accessing the correct memory range locations.
     The access range is within the boundaries of the buffer. */
    ArrPtr += FEE_DFLASH_WORD_SIZE;
  }

  /* prepare the CRC field */

  ArrPtr = &(StateDataPtr->FeeGcReadWriteBuffer[FEE_STATE_CRC_OFFSET]);
  /* Length will give the number of pages to Generate CRC */
  Length = FEE_STATE_CRC_OFFSET / FEE_DFLASH_WORD_SIZE;
  /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 32 bit
  access and array is memory aligned.*/
  *(uint32 *)(ArrPtr) =
    Fee_lEvaluateStatePageCrc(
  /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 32 bit
  access and array is memory aligned.*/
      (uint32 *)StateDataPtr->FeeGcReadWriteBuffer, Length);

  StateDataPtr->FeeStateCount = StateCnt;

}/* End of Fee_lPrepareStatePageBuffer */
/*******************************************************************************
** Syntax : static void Fee_lPrepareMarkerBuffer(void)                        **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This utility function prepares the Write buffer array for    **
**  marker programming of the state page                                      **
*******************************************************************************/
/* [cover parentID={46730273-C0EE-4a50-8C56-4F2718C6952A}]
Fee_lPrepareMarkerBuffer
[/cover] */
/* [cover parentID={1EEEFFDC-C315-47db-B4EB-6A3AD37BD4E5}] [/cover] */
static void Fee_lPrepareMarkerBuffer(void)
{
  Fee_StateDataType  *StateDataPtr;
  uint8              *BufferPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  BufferPtr = &(StateDataPtr->FeeGcReadWriteBuffer[FEE_STATEPAGE_DATA_SIZE]);
  /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 32 bit
  access and array is memory aligned.*/
  *((uint32*)(BufferPtr)) = FEE_SP_MARKER_WORD_1;
  /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 32 bit
  access and array is memory aligned.*/
  *((uint32*)(&(BufferPtr[4U]))) = FEE_SP_MARKER_WORD_2;
}/* End of Fee_lPrepareMarkerBuffer */

/*******************************************************************************
** Syntax : static void Fee_lClearMarkerBuffer(void)                          **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This utility function clears the marker field of             **
**  write buffer for comparison                                               **
*******************************************************************************/
/* [cover parentID={4D4C0096-3E6A-47da-842A-374FA1C36587}][/cover] */
static void Fee_lClearMarkerBuffer(void)
{
  Fee_StateDataType  *StateDataPtr;
  uint8              *BufferPtr;
  /* [cover parentID={F7D4168B-693E-463b-8CFD-F6527CD417FA}][/cover] */
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  BufferPtr = &(StateDataPtr->FeeGcReadWriteBuffer[FEE_STATEPAGE_DATA_SIZE]);
  /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 32 bit
  access and array is memory aligned.*/
  *((uint32*)(BufferPtr)) = (uint32)FEE_RESET;
  /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 32 bit
  access and array is memory aligned.*/
  *((uint32*)(&(BufferPtr[4U]))) = (uint32)FEE_RESET;
}/* End of Fee_lClearMarkerBuffer */

/*******************************************************************************
** Syntax : static void Fee_lClearFeeReadWriteBuffer(void)                    **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :None                                                  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This utility function clears the user read write buffer      **
*******************************************************************************/
/*[cover parentID={77BD326B-E54A-46ff-BF3B-E0185DD7372B}][/cover]*/
static void Fee_lClearFeeReadWriteBuffer(void)
{
  Fee_StateDataType  *StateDataPtr;
  uint32*             ReadWriteBuffPtr;
  uint16              DataByteCnt;
  uint32              Length;

  DataByteCnt = FEE_RESET;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 32 bit
  access and array is memory aligned.*/
  ReadWriteBuffPtr = (uint32 *)StateDataPtr->FeeReadWriteBuffer;
  Length = FEE_DFLASH_WORDLINE_SIZE / FEE_DFLASH_WORD_SIZE;
  /* Clear the fee read write buffer */
  do
  {
    ReadWriteBuffPtr[DataByteCnt] = FEE_RESET;
    DataByteCnt++;
  } while (DataByteCnt != Length);
  /*[cover parentID={F2A48557-F8BC-42d5-946D-A378E13D201F}][/cover]*/
}

/*******************************************************************************
** Syntax : static void Fee_lClearFeeGcReadWriteBuffer(void)                  **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) :None                                                  **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This utility function clears the Gc read write buffer        **
*******************************************************************************/
/*[cover parentID={0581E5CF-D0C5-407c-8996-FAB05B434301}][/cover]*/
static void Fee_lClearFeeGcReadWriteBuffer(void)
{
  Fee_StateDataType  *StateDataPtr;
  uint32*             GcReadWriteBuffPtr;
  uint16              DataByteCnt;
  uint32              Length;

  DataByteCnt = FEE_RESET;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 32 bit
  access and array is memory aligned.*/
  GcReadWriteBuffPtr = (uint32 *)StateDataPtr->FeeGcReadWriteBuffer;
  Length = FEE_DFLASH_WORDLINE_SIZE / FEE_DFLASH_WORD_SIZE;

  /* Clear the fee GC read write buffer */
  do
  {
    GcReadWriteBuffPtr[DataByteCnt] = FEE_RESET;
    DataByteCnt++;
  } while (DataByteCnt != Length);
}

/*******************************************************************************
** Syntax : static void Fee_lHandleInitGcFail(void)                           **
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
** Description : This function shall handle the fail cases during             **
** InitGC state machine                                                       **
*******************************************************************************/
/*[cover parentID={8BD0F667-20D8-4a47-A193-29493F27D57F}][/cover]*/
static void Fee_lHandleInitGcFail(void)
{
  Fee_StateDataType     *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* Enter InitGc fail state */
  StateDataPtr->FeeInitGCState = FEE_INITGC_FAIL;

  /* [cover parentID={483DFBF2-4B28-4570-9B30-58F0ED547A35}]
  production error enabled
  [/cover] */
  /* Raise production error */
  #if (FEE_GC_INIT_DEM_REPORT == FEE_ENABLE_DEM_REPORT)
  /* [cover parentID={3F7C17A3-C6D0-4dbc-82EC-0B296B787768}]
  Report production error to Mcal_Wrapper FEE_E_GC_INIT
  [/cover] */
  Fee_lReportDemError(FEE_E_GC_INIT, DEM_EVENT_STATUS_FAILED);
  #endif
  /* [cover parentID={38EF0E49-29B4-479a-B002-217D55DC4F46}]
  Is illegal state notification function configured?
  [/cover] */
  /* Raise Illegal state notification if configured */
  if(Fee_CfgPtr->FeeNvmIllegalStateNotification != NULL_PTR)
  {
    /* [cover parentID={129A9B2F-A577-408f-9B20-F25A26D2F51A}]
    Call the notification function
    [/cover] */
    /* Call the Notification function */
    Fee_CfgPtr->FeeNvmIllegalStateNotification();
  }
}

/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lPerformPrevBlkCheck (void)                 **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description :  Checks if there is enough space to accommodate the          **
** Last Written Block in case there is a word line issue                      **
*******************************************************************************/
/*[cover parentID={6D8844C8-3A85-40c2-993F-01A457DD82BD}][/cover]*/
LOCAL_INLINE void Fee_lPerformPrevBlkCheck(void)
{
  Fee_StateDataType *StateDataPtr;
  uint32             DestAddr;
  uint32             Offset;
  uint32             WLAddr;
  uint8              LWBType;
  Fee_PageType       LWBPageCount;
  uint32             RemainingPages;
  uint16             LWBNum;
  uint16             LWBIndex;
  uint8              BankNumber;
  boolean            ThresholdCrossed;


  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  BankNumber = StateDataPtr->FeeStatusFlags.FeeCurrSector;
  DestAddr = StateDataPtr->FeeNextFreePageAddr;

  LWBNum = StateDataPtr->FeeLastWrittenBlkInfo.BlockNumber;
  LWBPageCount = StateDataPtr->FeeLastWrittenBlkInfo.PageCount;
  LWBIndex = Fee_lGetUsrBlockIndex(LWBNum);

  /* Get the next but one free WL address. Then calculate number free pages,
     because in case of write failure we will retry from next but one free WL */

  WLAddr = Fee_lGetNextWLAddr(DestAddr);
  WLAddr = WLAddr + FEE_DFLASH_WORDLINE_SIZE;

  RemainingPages = Fee_lGetFreeDFLASHPages(BankNumber,
                   WLAddr);
  Offset = DestAddr & FEE_DFLASH_WORDLINE_SIZE_1;

  /* Unconfig blocks are treated as Normal blocks */
  /*[cover parentID={8B0BFFCB-0C0E-43b7-861A-CB3A95CCB18B}][/cover]*/
  if(LWBIndex == FEE_LOG_BLOCK_NOT_FOUND)
  {
    LWBType = (uint8)FEE_NORMAL_DATA;
  }
  else
  {
    LWBType = (uint8)(Fee_CfgPtr->FeeBlockConfigPtr[LWBIndex].FeeImmediateData);
  }

  /* Affected page count (in the worst-case) = Page Count of the block which
     crossed the current word-line boundary + filled pages in the current WL */
  LWBPageCount = LWBPageCount + (Fee_PageType)(Offset >> FEE_BYTE_TO_PAGE);

  /*Get the remaining frees pages from next but on free WL. This is because
  in case of write failure will start writing from next but one free WL*/
  ThresholdCrossed = Fee_lIsSectorThresholdCrossed((uint32)RemainingPages,
                                                   (uint32)LWBPageCount);
  /*[cover parentID={4A35BD41-2D3A-4df4-A5B4-EF11B825DB46}][/cover]*/
  if((LWBType == (uint8)FEE_NORMAL_DATA) && (ThresholdCrossed == (boolean)TRUE))
  {
    /* In case of a compare failure, the affected previously written blocks
       cannot be accommodated before the threshold boundary of the current
       sector. Hence, start the current request at next free WL */
    DestAddr = Fee_lGetNextWLAddr(DestAddr);
  }
  /*[cover parentID={3E420B85-FB5A-4e83-89B4-405473EA16B7}][/cover]*/
  else if ((LWBType == (uint8)FEE_IMMEDIATE_DATA) &&
           (RemainingPages < (uint32)LWBPageCount))
  {
    /* Previous Block cannot be accommodated if there is a compare failure
       Start the current request at new WL */
    DestAddr = Fee_lGetNextWLAddr(DestAddr);
  }
  else
  {
    /* Previous Block can be accommodated if there is a compare failure */
  }
  /*[cover parentID={58EF8E1F-6476-428b-A783-069163300A7F}][/cover]*/
  while (Fee_lIsUnerasableAddr(DestAddr) == TRUE)
  {
    DestAddr = Fee_lGetNextWLAddr(DestAddr);
  }
  StateDataPtr->FeeNextFreePageAddr = DestAddr;
}

/*******************************************************************************
** Syntax : LOCAL_INLINE Std_ReturnType Fee_lPerformCurrBlkCheck              **
**                                   (const Fee_BlockType * const BlockPt     **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  BlockPtr                                                **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                   E_OK : Block can be accommodate in current sector        **
**                   E_NOT_OK : Block can not be accommodate in current sector**
**                                                                            **
** Description :  Checks if there is enough space to accommodate the          **
** Current requested Block                                                    **
*******************************************************************************/
/*[cover parentID={50006C27-24B4-42a7-A7D6-C12CC0DC28C3}][/cover]*/
LOCAL_INLINE Std_ReturnType Fee_lPerformCurrBlkCheck(
  const Fee_BlockType * const BlockPtr)
{
  Fee_StateDataType *StateDataPtr;
  uint32             DestAddr;
  uint32             WLAddr;
  uint32             Offset;
  Fee_PageType       BlkPages;
  uint32             RemainingPages;
  uint8              BankNumber;
  Std_ReturnType     ReturnValue;

  ReturnValue = E_NOT_OK;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  BankNumber = StateDataPtr->FeeStatusFlags.FeeCurrSector;
  DestAddr = StateDataPtr->FeeNextFreePageAddr;


  if (StateDataPtr->FeeStatusFlags.FeeBlkInvalidStatus == (uint32)FEE_SET )
  {
    BlkPages = FEE_INVALID_BLOCK_PAGES;
  }
  else
  {
    BlkPages = Fee_lGetDFLASHPages((uint16)(BlockPtr->Size));
  }

  /*Check if next free page is beginning of WL. if yes then means no need to
    write old data in case of write failure.*/
  if(Fee_lIsWLBeginning(DestAddr) == FEE_NEW_WL_BEGIN)
  {
    RemainingPages = Fee_lGetFreeDFLASHPages(BankNumber, DestAddr);
  }
  else
  {
    /*This is not a WL beginning and there is some block data available in WL ,
      so in case of write failure we need write this data also. We will retry
      write from next to next free WL. So calculate the free pages from next
      to next free WL.This is done to avoid crossing sector boundary while
      write retry.
    */
    WLAddr = (Fee_lGetNextWLAddr(DestAddr) + FEE_DFLASH_WORDLINE_SIZE);

    RemainingPages = Fee_lGetFreeDFLASHPages(BankNumber, WLAddr);

    /*Total BlkPages = BlkPages + Number of filled pages in current WL*/

    Offset = (DestAddr & FEE_DFLASH_WORDLINE_SIZE_1);
    /* Convert the number of byte into pages */
    Offset = (Offset >> 3);

    Offset += BlkPages;

    /* Check if threshold will crossed in case of write retry . If yes mean we
     can not accommodate old data in current WL + requested block data.
     Switch next free page address to next free WL this will avoid corruption
     of old data in current WL in case write fail.
    */
    if ((boolean)TRUE == Fee_lIsSectorThresholdCrossed((uint32)RemainingPages,
        (uint32)Offset))
    {
      StateDataPtr->FeeNextFreePageAddr = Fee_lGetNextWLAddr(DestAddr);
      DestAddr = StateDataPtr->FeeNextFreePageAddr;
    }

    /*Now check if threshold crossed for current write request  */
    RemainingPages = Fee_lGetFreeDFLASHPages(BankNumber, DestAddr);

  }
  /*[cover parentID={8327131F-826B-4a2a-BDA9-675AD10B38AD}][/cover]*/
  if ((boolean)TRUE == Fee_lIsSectorThresholdCrossed((uint32)RemainingPages,
      (uint32)BlkPages))
  {
    /*GC start is disabled by user keep the request in pending state*/
    /****** Check if it is a NORMAL REQUEST *******/
    /*[cover parentID={77F4AA83-2CD2-4700-800B-3C27ACB2353F}][/cover]*/
    if( (BlockPtr->FeeImmediateData == (uint32)FEE_NORMAL_DATA) ||
        (StateDataPtr->FeeStatusFlags.FeeBlkInvalidStatus
         == (uint32)FEE_SET )
      )
    {
      /* Do nothing */
    }
    /****** Check if it is a IMMEDIATE REQUEST *******/
    else
    {
      /* if this block cannot be accommodated in the DFLASH */
      /*[cover parentID={1D38A69F-A7D5-4b50-B8D3-FCB974DE69F6}][/cover]*/
      if(RemainingPages < BlkPages)
      {
        /* Do nothing */
      }
      /**** Block can be accommodated within the current DFLASH Sector */
      else
      {
        StateDataPtr->FeeGCImmBlkWrite = (boolean)TRUE;
        ReturnValue = E_OK;
      }
    }/* End of immediate write check */

    /*[cover parentID={035E000D-671A-455a-BE10-41BB00B378DD}][/cover]*/
    /*[cover parentID={D22BCA54-B974-4042-A97A-D5C968DDEAD1}][/cover]*/
    if (StateDataPtr->FeeGcState == FEE_GC_IDLE)
    {
      /* GC should be triggered only if DisableGCStart is FALSE */
      /*[cover parentID={BDE15D5E-B4E6-46f3-BCC8-CAD3AECB9017}][/cover]*/
      if(StateDataPtr->FeeDisableGCStart == (boolean)FALSE)
      {
        /* Request for Garbage Collection and continue */
        StateDataPtr->FeeGcState = FEE_GC_REQUESTED;
      }
    }
  }
  /* Threshold NOT Crossed*/
  else
  {
    ReturnValue = E_OK;
  }

  return(ReturnValue);
}

/*******************************************************************************
** Syntax : LOCAL_INLINE Std_ReturnType Fee_lPerformWriteCheck                **
**                               ( const Fee_BlockType * const BlockPtr)      **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  BlockPtr                                                **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Return value    :  E_NOT_OK / E_OK                                         **
**                                                                            **
** Description :  Checks if there is enough space to accommodate the request  **
*******************************************************************************/
/*[cover parentID={64492263-4B67-4d72-A9EF-55F91083DAEA}][/cover]*/
LOCAL_INLINE Std_ReturnType Fee_lPerformWriteCheck(
  const Fee_BlockType * const BlockPtr)
{
  uint32             DestAddr;
  Fee_StateDataType *StateDataPtr;
  Std_ReturnType     ReturnValue;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  DestAddr = StateDataPtr->FeeNextFreePageAddr;
  /*[cover parentID={1EE9BDC2-674D-4ce7-8CE2-EF5B0DCA5C7C}][/cover]*/
  while(Fee_lIsUnerasableAddr(DestAddr) == TRUE)
  {
    DestAddr = Fee_lGetNextWLAddr(DestAddr);
  }
  StateDataPtr->FeeNextFreePageAddr = DestAddr;

  /* Check if Previous Block can be accommodated if there is a compare failure
   */
  /*[cover parentID={AFEEC63E-DE04-48ca-8898-8575E3B472A1}][/cover]*/
  if( (Fee_lIsWLBeginning(DestAddr) != FEE_NEW_WL_BEGIN) &&
      (StateDataPtr->FeeLastWrittenBlkInfo.Status.Consistent ==
       (uint32)FEE_SET ))
  {
    /*[cover parentID={724C552C-124B-48da-8D52-663E91C9ABB0}][/cover]*/
    Fee_lPerformPrevBlkCheck();
  }

  /* Check if Current Block can be accommodated */
  ReturnValue = Fee_lPerformCurrBlkCheck(BlockPtr);

  return(ReturnValue);
}
#endif
/*******************************************************************************
** Syntax : static void Fee_lHandleWriteFail(void)                            **
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
** Description : This function shall handle the severe error                  **
** (compare failed twice or internal write fail) case during                  **
** write state machine                                                        **
*******************************************************************************/
/*[cover parentID={786A84CA-3DC9-4f2e-AC4D-4F37A18654E2}][/cover]*/
static void Fee_lHandleWriteFail(void)
{
  Fee_StateDataType  *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* Enter Write Fail State */
  StateDataPtr->FeePendReqStatus = FEE_WRITE_FAIL;

  /* [cover parentID={FA984E1B-1BF3-4870-AC78-8D5F47D8F68F}]
  production error enabled
  [/cover] */
  /* Raise Job Failed production error */
  #if (FEE_WRITE_DEM_REPORT == FEE_ENABLE_DEM_REPORT)
  /* [cover parentID={45A51475-D8A1-4f4f-A794-971AE5C1303F}]
  Report production error to Mcal_Wrapper FEE_E_WRITE
  [/cover] */
  Fee_lReportDemError(FEE_E_WRITE, DEM_EVENT_STATUS_FAILED);
  #endif

  /* [cover parentID={F2A40B82-4348-489d-A08A-E96C4D4B9A9E}]
  Is illegal state notification configured?
  [/cover] */
  /* Raise Illegal state notification if configured */
  if(Fee_CfgPtr->FeeNvmIllegalStateNotification != NULL_PTR)
  {
    /* [cover parentID={8205126C-3839-46e9-9217-41FBA246ABD5}]
    Call the notification function
    [/cover] */
    /* Call the Notification function */
    Fee_CfgPtr->FeeNvmIllegalStateNotification();
  }
}

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

/*******************************************************************************
** TRACEABILITY: []                                                           **
**                                                                            **
** Syntax : LOCAL_INLINE Std_ReturnType Fee_lPerformReadCheck                 **
**                                              (const uint16 UserBlockIndex) **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  UserBlockIndex       block index                        **
**                                                                            **
** Parameters (in-out) :None                                                  **
**                                                                            **
** Return value    :                                                          **
**                  E_NOT_OK : Block is not valid or inconsistent             **
**                  E_OK : Block is  valid and consistent                     **
**                                                                            **
** Description :  This utility function checks if the requested copy of the   **
** logical data block is consistent and valid                                 **
*******************************************************************************/
/* [cover parentID={021E426E-3285-4e2a-8065-2D8F4BDF6D52}][/cover] */
LOCAL_INLINE Std_ReturnType Fee_lPerformReadCheck(const uint16 UserBlockIndex)
{
  Fee_StateDataType     *StateDataPtr;
  const Fee_CacheType         *BlockPtr;
  Std_ReturnType         RetVal;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  BlockPtr = &StateDataPtr->FeeBlockInfo[UserBlockIndex];

  #if (FEE_GET_PREV_DATA_API == STD_ON)
  /* [cover parentID={F1E0CF63-9125-4a0c-8924-E5FCEDB9E32A}][/cover] */
  if (StateDataPtr->FeePendReqInfo.GetPrevCopy == FEE_SET )
  {
    /* [cover parentID={AD46AE06-503D-4882-AA6C-7D8A55EA85B5}]
    Is the logical block inconsistent?
    [/cover] */
    if (BlockPtr->Status.PrevCopyConsistent == (uint32)FEE_RESET)
    {
      /* [cover parentID={94D9D304-CF44-48f6-BB78-CF09C9B05E89}]
      Update Fee job result as block MEMIF_BLOCK_INCONSISTENT
      [/cover] */
      StateDataPtr->FeeJobResult = MEMIF_BLOCK_INCONSISTENT;
      RetVal = E_NOT_OK;
    }
    /* [cover parentID={6EE8825D-927C-4fcc-A417-C16110628F48}]
    Is the logical block invalid?
    [/cover] */
    /* If the logical block is invalid */
    else if (BlockPtr->Status.PrevCopyValid == (uint32)FEE_RESET)
    {
      /* [cover parentID={77F3C9CE-CA24-40aa-B913-D26A9F163082}]
      Update Fee job result as MEMIF_BLOCK_INVALID
      [/cover] */
      StateDataPtr->FeeJobResult = MEMIF_BLOCK_INVALID;
      RetVal = E_NOT_OK;
    }
    else
    {
      RetVal = E_OK;
    }
  }
  else
  #endif
  {
    /* [cover parentID={0D4A8E30-6FC8-4406-A285-B15DAC21978D}]
    Is the current block inconsistent?
    [/cover] */
    /* If the logical block is inconsistent */
    if (BlockPtr->Status.Consistent == (uint32)FEE_RESET)
    {
      StateDataPtr->FeeJobResult = MEMIF_BLOCK_INCONSISTENT;
      RetVal = E_NOT_OK;
    }
    /* [cover parentID={77388B83-623E-41a1-A3D0-BAB58D4D8800}]
    Is the current logical block invalid?
    [/cover] */
    /* If the logical block is invalid */
    else if (BlockPtr->Status.Valid == (uint32)FEE_RESET)
    {
      StateDataPtr->FeeJobResult = MEMIF_BLOCK_INVALID;
      RetVal = E_NOT_OK;
    }
    else
    {
      RetVal = E_OK;
    }
  }

  return(RetVal);
}

/*******************************************************************************
** Syntax : static void Fee_lUpdateBlockInfo(const Fee_CacheStatusType        **
**                               * const Status,                              **
**                               const uint16 Index, const uint16 pageCount)  **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :Status: State of data block                               **
**                   Index: Block Index in cache table                        **
**                   pageCount: Page count                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  void                                                    **
**                                                                            **
** Description : This utility function updates the cache table with the       **
** block info                                                                 **
*******************************************************************************/
/* [cover parentID= {42009E6C-8C53-48c3-9E8C-AA24E2F7724A}][/cover] */
static void Fee_lUpdateBlockInfo(const Fee_CacheStatusType * const Status,
                                 const uint16 Index, const uint16 pageCount)
{
  Fee_CacheType           *CachePtr;
  Fee_StateDataType       *StateDataPtr;
  uint32                   NewPageCount;
  uint32                   BlockCycleCount;
  uint32                   PrvBlockCycleCount;
  const uint8              *TempArrayPtr;

  /* [cover parentID={30EAC34E-D3B0-4a50-A537-95F31B835280}]
    Point the Cache pointer to the block using block index
     [/cover] */
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  CachePtr = &(StateDataPtr->FeeBlockInfo[Index]);



  NewPageCount = pageCount;
  NewPageCount = (NewPageCount - FEE_ONE);
  /* [cover parentID={037D3D77-B1DD-4e8f-98E5-06FE5FC7B626}]
      Was cache update done for the block?
      [/cover] */
  if(CachePtr->Address == FEE_RESET)
  {
    /* [cover parentID={0A64E26F-7A17-411d-A3E1-C7F100221AFF}]
    Update the cache with block address
    Update valid, consistent and copied fields
    [/cover] */
    /* Update the cache with block Address */
    CachePtr->Address = StateDataPtr->FeeCurrSectSrcAddr;
    CachePtr->Status.Valid = Status->Valid;
    CachePtr->Status.Consistent = Status->Consistent;
    CachePtr->Status.Copied = Status->Copied;
    CachePtr->BlockSize = (NewPageCount * FEE_SEVEN);
  }
  /* [cover parentID={5ED60E83-4A2D-41b3-BEBC-CCF626AF975F}]
     Is the previous copy address reset?
     [/cover] */
  else if(CachePtr->PrevCopyAddress == FEE_RESET)
  {

    /*Get the cycle count of the current copy of block*/
    BlockCycleCount = Fee_lGetBlkCycleCount(Index);

    /*Get the cycle count of block from FeeReadWriteBuffer*/
    /*Here the intention is to read Bytes 3,4,5 from the data block
      which together indicates BCC. First bytes 2 to 5 are read and BCC bytes
      are extracted */
    TempArrayPtr = &(StateDataPtr->FeeReadWriteBuffer[FEE_BLOCK_CYL_CNT_POS]);
    /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 32 bit
     access and array is memory aligned.*/
    PrvBlockCycleCount = *((const uint32*)TempArrayPtr);
    /*Remove the MSB of number of data pages */
    PrvBlockCycleCount = (PrvBlockCycleCount >> FEE_EIGHT);
    /* [cover parentID={BE4264CB-8FAB-4f96-87A2-4ABED6C04875}]
       Update the cache with block address of previous copy
      Mark the previous copy as consistent
      [/cover] */
    /*Check if the cycle count of previous copy of block is 1 less than of cycle
    count of current copy of block if yes then only update cache table.*/
    /* [cover parentID= {A46C6485-94A9-44ca-82F4-91CC3A4432B1}][/cover] */
    if(PrvBlockCycleCount == (BlockCycleCount - FEE_ONE))
    {
      /* Update the cache with block Address of previous copy */
      CachePtr->PrevCopyAddress = StateDataPtr->FeeCurrSectSrcAddr;
      CachePtr->PrevBlkSize = (NewPageCount * FEE_SEVEN);
      CachePtr->Status.PrevCopyValid = Status->Valid;
      CachePtr->Status.PrevCopyConsistent = Status->Consistent;
      CachePtr->Status.PrevCopyCopied = Status->Copied;
    }
  }
  /* [cover parentID={0A64E26F-7A17-411d-A3E1-C7F100221AFF}]
        Update the cache with block address
       Update valid, consistent and copied fields
      [/cover] */
  else
  {
    /*Dummy Else to avoid MISRA*/
  }
}

/*******************************************************************************
** Syntax : static void Fee_lUpdateUnconfigBlockInfo(const uint16 BlockNumber,**
**                                                   const uint16 PageCount)  **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  BlockNumber - Block Number                              **
**                    PageCount   - page count                                **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  void                                                    **
**                                                                            **
** Description : This function does the cache table update of the             **
**               un-configured block                                          **
*******************************************************************************/
/* [cover parentID= {0CC32433-7485-4dc8-BF65-26705DCCDAB0}][/cover] */
static void Fee_lUpdateUnconfigBlockInfo(const uint16 BlockNumber, \
    const uint16 PageCount)
{
  Fee_StateDataType       *StateDataPtr;
  Fee_CacheType           *UnconfigBlockPtr;
  uint16                   UnconfigBlockIndex;
  uint16                   TempUnConfigBlockCount;


  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  TempUnConfigBlockCount = StateDataPtr->FeeUnConfigBlockCount;

  UnconfigBlockIndex = FEE_RESET;

  UnconfigBlockPtr = &(StateDataPtr->FeeBlockInfo[Fee_CfgPtr->FeeBlkCnt]);


  /* [cover parentID={EA7E70CD-76EF-4fe2-AF4F-F2D2317D1F8D}][/cover] */
  while((UnconfigBlockIndex < TempUnConfigBlockCount) &&
        (UnconfigBlockPtr->BlockNumber != BlockNumber))
  {
    UnconfigBlockIndex++;

    UnconfigBlockPtr++;
  }
  /* [cover parentID={65793023-B106-4d89-B3E9-DAB49C5AB6C1}][/cover] */
  if(UnconfigBlockIndex == TempUnConfigBlockCount)
  {
    /* check if the cache table has space */
    if(((Fee_CfgPtr->FeeBlkCnt) + TempUnConfigBlockCount) <
        (uint16)(FEE_TOTAL_BLOCK_COUNT))
    {
      /* [cover parentID={C63246F2-315E-401f-9747-82A5A030B401}]
      production error enabled
      [/cover] */
      #if (FEE_UNCFG_BLK_DEM_REPORT == FEE_ENABLE_DEM_REPORT)
      /* [cover parentID={D157E100-304E-49f5-895B-F70860E32832}][/cover] */
      if(((Fee_CfgPtr->FeeBlkCnt) + TempUnConfigBlockCount) ==
          FEE_MAX_BLOCK_COUNT)
      {
        /* [cover parentID={45BBF021-539B-42c1-96BB-232F0BA519E2}]
           Report production error to Mcal_Wrapper FEE_E_UNCONFIG_BLK_EXCEEDED
           [/cover] */
        Fee_lReportDemError(FEE_E_UNCONFIG_BLK_EXCEEDED,
                              DEM_EVENT_STATUS_FAILED);
      }
      #endif
      UnconfigBlockPtr->Address = StateDataPtr->FeeCurrSectSrcAddr;
      UnconfigBlockPtr->BlockNumber = BlockNumber;
      UnconfigBlockPtr->BlockSize = (uint32)((uint32)PageCount * FEE_SEVEN);
      TempUnConfigBlockCount++;
    }
    else
    {
      /* Un-configured blocks cache table is already full */
      StateDataPtr->FeeUncfgBlksExceeded = FEE_UNCONFIG_BLK_LIMIT_CROSSED;
    }
  }
  StateDataPtr->FeeUnConfigBlockCount = TempUnConfigBlockCount;
}

/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lUpdateGcCurrBlockInfo(void)                **
**                                                                            **
** Service ID: NA                                                             **
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
** Description : Updates the block information of the block being written     **
**               during Garbage collection                                    **
*******************************************************************************/
/* [cover parentID={1952A9DA-A5CF-41d8-9890-F950351C9E1B}][/cover] */
LOCAL_INLINE void Fee_lUpdateGcCurrBlockInfo(void)
{
  Fee_StateDataType    *StateDataPtr;
  Fee_GcBlkInfoType    *GcBlkPtr;
  const uint8                *ReadWriteBufferPtr;
  Fee_PageType          PageCount;
  uint32                WordValue;
  uint16                BlockNumber;
  uint16                Offset;
  /* [cover parentID={414D95EA-8C04-4a5c-8591-8DC77E0EBE19}]
  Fee_lUpdateGcCurrBlockInfo
  [/cover] */
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  GcBlkPtr = &(StateDataPtr->FeeGcCurrBlkInfo);
  Offset = (uint16)((StateDataPtr->FeeGcDestAddr) & FEE_DFLASH_WORDLINE_SIZE_1);
  ReadWriteBufferPtr = &(StateDataPtr->FeeGcReadWriteBuffer[Offset]);

  /* Extract block number and page count */
  /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 32 bit
  access and array is memory aligned.*/
  WordValue = *(const uint32 *)ReadWriteBufferPtr;
  BlockNumber = (uint16)(WordValue >> FEE_EIGHT);

  /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 16 bit
  access and array is memory aligned.*/
  PageCount = *((const uint16*)(&ReadWriteBufferPtr[FEE_BLOCK_NUM_POS]));
  PageCount = (PageCount & (uint16)FEE_PAGE_COUNT_MASK);

  /* Update FeeGcCurrBlkInfo */
  GcBlkPtr->Addr = StateDataPtr->FeeGcSrcAddr;
  GcBlkPtr->BlockNumber = BlockNumber;
  GcBlkPtr->PageCount = PageCount;
  GcBlkPtr->Consistent = FEE_SET ;
}
#endif

/*******************************************************************************
** Syntax : static Std_ReturnType Fee_lRegisterNvmRead(                       **
**                            const uint16 BlockNumber,                       **
**                            const uint16 BlockOffset,                       **
**                            uint8 * const DataBufferPtr,                    **
**                            const uint16 Length                             **
**                            const uint8 GetPrevCopy)                        **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  BlockNumber : Logical block number                      **
**                    BlockOffset : Read address offset within the block      **
**                    Length      : Number of bytes to be read                **
**                    DataBufferPtr : pointer to data buffer                  **
**                    GetPrevCopy : Set: Request is for reading pervious copy **
**                                  of data block                             **
**                                  Reset: Request is for reading current     **
**                                  copy of data block                        **
**                                                                            **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                    E_OK : Request is registered.                           **
**                    E_NOT_OK : Request is not registered. FEE module is busy**
**                     in servicing other request.                            **
** Description : This function will register the NVM read request in the      **
** pending request buffer if FEE is Idle or If erase suspend enabled and QS   **
** Erase is ongoing                                                           **
*******************************************************************************/
/* [cover parentID={24E7F068-5567-4b01-9D6C-6A80C21B9E4A}][/cover] */
static Std_ReturnType Fee_lRegisterNvmRead( const uint16 BlockNumber,
    const uint16 BlockOffset, uint8 * const DataBufferPtr, const uint16 Length,
    const uint8 GetPrevCopy)
{
  Fee_StateDataType  *StateDataPtr;
  Std_ReturnType RetVal;
  Std_ReturnType RetValue;
  Fee_PendReqBufType   *PendReqPtr;
  uint8 DetCall;

  DetCall = FEE_SET;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  PendReqPtr = &(StateDataPtr->FeePendReqInfo);

  /* [cover parentID={6A1D98CD-158F-4702-8165-6C5C726CD8BB}]
  Set Flag as E_NOT_OK
  [/cover] */
  RetVal = E_NOT_OK;

  /* [cover parentID={77B1992F-C0C7-447e-9CEE-7FC6CB46C199}][/cover] */
  if(StateDataPtr->FeePendReqStatus == FEE_PEND_PREV_NO_REQ)
  {
    /* [cover parentID={E8DF5530-B41E-4d87-A006-C3611C761B94}]
    Set Flag as E_OK
    [/cover] */
    RetVal = E_OK;
  }
  #if(FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY) && \
     (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
  else
  {
    /* [cover parentID={399A2610-BEB7-48e8-94B0-57E9486B0762}]
    Check for QS job status
    [/cover] */
    if((StateDataPtr->FeeQsState == (uint8)FEE_QS_PROG_STATE_ERASE_COMPLETE) &&
        (StateDataPtr->FeeQsJobStatus == FEE_JOB_REQSTD))
    {
      /* [cover parentID={2552C496-99D4-4919-9770-FE1BDC7BBE49}][/cover] */
      RetVal = Fls_17_Dmu_SuspendErase();
      if(RetVal == E_OK)
      {
        /* [cover parentID={291D18F2-CD8D-49d7-8345-B65FAAEFA4F0}][/cover] */
        StateDataPtr->FeeQsEraseSuspend = FEE_ERASE_SUSPENDED;
        StateDataPtr->FeeQsJobStatus = FEE_JOB_IDLE;
        StateDataPtr->FeeQsJob = FEE_NO_JOB;
      }
      #if (((FEE_DEV_ERROR_DETECT == STD_ON) || (FEE_SAFETY_ENABLE == STD_ON)) \
      && (MCAL_AR_VERSION == MCAL_AR_422)) || (FEE_RUNTIME_ERROR_DETECT == STD_ON)
      else
      {
        /* For suspend failure DET is not raised */
        DetCall = FEE_RESET;
      }
      #endif
    }
    /* [cover parentID={DF2AC9DC-7080-49ee-9C39-9A3181FFAC44}][/cover] */
    else if(StateDataPtr->FeeQsEraseSuspend == FEE_ERASE_SUSPENDED)
    {
      /* [cover parentID={4EEA0817-2B72-4e80-AA59-7D99A929A62D}][/cover] */
      RetVal =  E_OK;
      StateDataPtr->FeeQsJobStatus = FEE_JOB_IDLE;
      StateDataPtr->FeeQsJob = FEE_NO_JOB;
    }
    else
    {
      /*Dummy else for MISRA */
    }
  }
  #endif

  RetValue = Fee_lRegisterNvmReadUpdate(DetCall, RetVal, GetPrevCopy);

  /*[cover parentID={80B7B1C8-2BE1-4062-8F23-08A665011A22}][/cover] */
  if(RetValue == E_OK)
  {
    /* [cover parentID={2552C496-99D4-4919-9770-FE1BDC7BBE49}]
    Store the read request parameters in the pending buffer structure
    Update pending request status as 'read requested' and job result as 'MEMIF_JOB_PENDING'
    [/cover] */
    /* Store the read request parameters in the Pending buffer structure */
    PendReqPtr->BlockNumber = BlockNumber;
    PendReqPtr->BlockOffset = BlockOffset;
    PendReqPtr->DataBufferPtr = DataBufferPtr;
    PendReqPtr->Length = Length;
  }
  /* [cover parentID={138DF8B8-2FED-407d-AF0C-3015C8E3F599}]
  Return Flag status
  [/cover] */
  return(RetValue);
  /* [cover parentID={D6919DDB-986F-49ac-BBC4-FE6D936C3127}]
  Return
  [/cover] */
}

#if ((((FEE_DEV_ERROR_DETECT == STD_ON) || (FEE_SAFETY_ENABLE == STD_ON)) \
&& (MCAL_AR_VERSION == MCAL_AR_422)) || (FEE_RUNTIME_ERROR_DETECT == STD_ON))
/* [cover parentID={64223989-13EB-4996-94CE-5EBD4CBA23DB}][/cover] */
/*******************************************************************************
** Syntax : static Std_ReturnType Fee_lRegNvmReadDetCheck(                    **
**                            uint8 DetCall                                   **
**                            const uint8 GetPrevCopy)                        **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  DetCall : DET call status variable                      **
**                    GetPrevCopy : Set: Request is for reading pervious copy **
**                                  of data block                             **
**                                  Reset: Request is for reading current     **
**                                  copy of data block                        **
**                                                                            **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
** Description : This function will check the NVM read Det                    **
*******************************************************************************/
LOCAL_INLINE void Fee_lRegNvmReadDetCheck(uint8 DetCall, const uint8 GetPrevCopy)
{
    /* [cover parentID={F649153E-80B1-4dbf-9EF1-E647F532C64B}]
    DET or safety is enabled
    [/cover] */
    /* FEE is busy with another request; raise BUSY DET */
    /* [cover parentID={8C968070-3390-4bc2-8D73-62CDEF71B014}]
    Report error to DET/SAFETY
    [/cover] */
    #if (FEE_GET_PREV_DATA_API == STD_ON)
    /* [cover parentID={ABE7C3DA-BCDA-4cd1-AE0A-E059FCDC80A8}][/cover] */
    if(GetPrevCopy == FEE_SET)
    {
      /* [cover parentID={FD8870D2-8052-48c1-B972-7EC34F13A35E}][/cover] */
      #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY) \
        && (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
      if(DetCall == FEE_SET)
      #else
      UNUSED_PARAMETER(DetCall);
      #endif

      {
      /* If get previous copy is set then only report safety error. Because
      request came from non autosar API */
      #if (MCAL_AR_VERSION == MCAL_AR_422) && (FEE_SAFETY_ENABLE == STD_ON)
        /* [cover parentID={24DA148C-A961-4d92-BECC-20FA7400C850}]
        Report error to API GetPrevData

        [/cover] */
          Fee_lReportError(FEE_SID_GETPREVDATA, FEE_SE_BUSY, FEE_SAFETY_ERROR);
      #elif(FEE_RUNTIME_ERROR_DETECT == STD_ON)
          Fee_lReportError(FEE_SID_GETPREVDATA, FEE_E_BUSY, FEE_RUNTIME_ERROR);
      #endif

      }
    }
    else
    #endif
    {
      /* [cover parentID={61360DE2-AC41-44e2-B05C-1CE79EB058A5}][/cover] */
      #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY) \
             && (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
      if(DetCall == FEE_SET)
      #else
      UNUSED_PARAMETER(DetCall);
      #endif
      {
      #if(FEE_RUNTIME_ERROR_DETECT == STD_ON)
        /* [cover parentID={96EB3791-5CB5-4449-BBDC-DCE4A42B3CEF}]
        Report runtime error FEE_E_BUSY
        [/cover] */
        Fee_lReportError(FEE_SID_READ, FEE_E_BUSY, FEE_RUNTIME_ERROR);
      #else
        /* [cover parentID={8C968070-3390-4bc2-8D73-62CDEF71B014}]
        Report error to DET FEE_SID_READ
        [/cover] */
        Fee_lReportError(FEE_SID_READ, FEE_E_BUSY, FEE_DET_SAFETY_ERROR);
      #endif

      }
    }
    UNUSED_PARAMETER(GetPrevCopy);
}
#endif

/* [cover parentID={3FC8CF0E-D55A-4431-8401-288F5AEE6283}][/cover] */
/*******************************************************************************
** LOCAL_INLINE Std_ReturnType Fee_lRegisterNvmReadUpdate(                    **
**                  uint8 DetCall, Std_ReturnType RetVal,                     **
**                  const uint8 GetPrevCopy)                                  **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  DetCall : DET call status variable                      **
**                    RetVal : Return value E_OK/E_NOT_OK                     **
**                    GetPrevCopy : Set: Request is for reading pervious copy **
**                                  of data block                             **
**                                  Reset: Request is for reading current     **
**                                  copy of data block                        **
**                                                                            **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
** Description : This function will update pending request status             **
*******************************************************************************/
LOCAL_INLINE Std_ReturnType Fee_lRegisterNvmReadUpdate(uint8 DetCall,
                                 Std_ReturnType RetVal, const uint8 GetPrevCopy)
{
  Fee_StateDataType  *StateDataPtr;
  Std_ReturnType RetValue = E_OK;
  #if (FEE_GET_PREV_DATA_API == STD_ON)
  Fee_PendReqBufType   *PendReqPtr;
  #endif
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* [cover parentID={1692C8C3-9037-4e18-B0A3-DB9A45EDF676}][/cover] */
  if(RetVal == E_OK)
  {
    #if (FEE_GET_PREV_DATA_API == STD_ON)
    PendReqPtr = &(StateDataPtr->FeePendReqInfo);
    /* [cover parentID={4672374B-0E25-483e-8D02-AEC5C6EE2E28}][/cover] */
    if(GetPrevCopy == FEE_SET)
    {
      PendReqPtr->GetPrevCopy = FEE_SET;
    }
    else
    {
      PendReqPtr->GetPrevCopy = FEE_RESET;
    }
    #else
    UNUSED_PARAMETER (GetPrevCopy);
    #endif
    StateDataPtr->FeeStatusFlags.FeeStartInitGC = FEE_SET ;
    /* Store the read request parameters in the pending buffer structure
    Update pending request status as 'read requested' and job result as
    'MEMIF_JOB_PENDING' */
    StateDataPtr->FeePendReqStatus = FEE_REQ_READ;
    StateDataPtr->FeeJobResult = MEMIF_JOB_PENDING;
  }
  else
  {
     #if (((FEE_DEV_ERROR_DETECT == STD_ON) || (FEE_SAFETY_ENABLE == STD_ON)) \
     && (MCAL_AR_VERSION == MCAL_AR_422)) || (FEE_RUNTIME_ERROR_DETECT == STD_ON)
     Fee_lRegNvmReadDetCheck(DetCall, GetPrevCopy);
     #else
     UNUSED_PARAMETER(DetCall);
     #endif

     RetValue = E_NOT_OK;
  }

  return RetValue;
}

/*******************************************************************************
** Syntax : static Std_ReturnType                                             **
**   Fee_lRegisterNvmWrite(const uint8 * const DataWriteBufferPtr,            **
**                                      const Fee_BlockType * const BlockPtr) **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  DataWriteBufferPtr : Data buffer pointer                **
**                    BlockPtr      : Block cache pointer                     **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                    E_OK : Request is registered.                           **
**                    E_NOT_OK : Request is not registered. FEE module is busy**
**                     in servicing other request.                            **
** Description : This function will register the NVM write request in the     **
** pending request buffer if FEE is Idle or If erase suspend enabled and QS   **
** Erase is ongoing                                                           **
*******************************************************************************/
/* [cover parentID={71B119F7-AF7C-487b-8BD3-C20F63E92269},
{754520DC-4BD9-4c7d-AB85-FB6AB5BC9EAF}]
Fee_lRegisterNvmWrite
[/cover] */
static Std_ReturnType Fee_lRegisterNvmWrite( \
    const uint8 * const DataWriteBufferPtr, \
    const Fee_BlockType * const BlockPtr)
{
  /* [cover parentID={71B119F7-AF7C-487b-8BD3-C20F63E92269}]*/
  Fee_StateDataType  *StateDataPtr;
  Std_ReturnType RetVal;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  /* [cover parentID={DC2B5783-BBEB-4635-A759-BCF0F430CF2A}]*/
  if(StateDataPtr->FeePendReqStatus == FEE_PEND_PREV_NO_REQ)
  {
    /* [cover parentID={3940BCA6-5C15-4d8a-A009-DFB34F58D94A}]
    Register write request
    [/cover] */
    /* Register the write request */
    StateDataPtr->FeeStatusFlags.FeeBlkInvalidStatus = FEE_RESET;
    Fee_lRegisterWriteRequest(DataWriteBufferPtr, BlockPtr);
    /* [cover parentID={197B7188-11D0-4aaa-8350-F7B78E20EAFD}]
    Return E_OK
    [/cover] */
    RetVal = E_OK;
  }
  else
  {
    /* FEE is busy with other request; raise BUSY DET */
    /* [cover parentID={89275CDB-C274-4144-A84F-EB6BFDACBFC9}]*/
    /* [cover parentID={2010672E-36A5-49cd-A0DB-29F149E19143}]*/
  #if(FEE_RUNTIME_ERROR_DETECT == STD_ON)
    /* [cover parentID={16A1402F-1832-4ef5-9068-D500F78E1B16}]
    Runtime error report FEE_E_BUSY error
    [/cover] */
    Fee_lReportError(FEE_SID_WRITE, FEE_E_BUSY, FEE_RUNTIME_ERROR);
  #elif(((FEE_DEV_ERROR_DETECT == STD_ON) || (FEE_SAFETY_ENABLE == STD_ON)) \
  && (MCAL_AR_VERSION == MCAL_AR_422))
    /* [cover parentID={2010672E-36A5-49cd-A0DB-29F149E19143}]
    Report FEE_E_BUSY error
    [/cover] */
    Fee_lReportError(FEE_SID_WRITE, FEE_E_BUSY, FEE_DET_SAFETY_ERROR);
  #endif
    /* [cover parentID={89275CDB-C274-4144-A84F-EB6BFDACBFC9}]
    Report E_NOT_OK
    [/cover] */
    RetVal = E_NOT_OK;

  }
  return(RetVal);
}
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/*******************************************************************************
** Syntax : void Fee_lPerformStuffCheck(const uint16 UserBlockIndex)          **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  UserBlockIndex : Block Index                            **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This utility function checks if the requested block size is  **
**               different in DFlash & configured value and performs          **
**               stuffing the extra user bytes with zero if necessary         **
*******************************************************************************/
/*[cover parentID={C2BA48DD-4ADB-4664-88FA-A0B68DDD7B2C}][/cover]*/
LOCAL_INLINE void Fee_lPerformStuffCheck(const uint16 UserBlockIndex)
{
  Fee_StateDataType  *StateDataPtr;
  uint8*             DataBufPtr;
  uint16             Count;
  uint16             DflashBlkSize;
  uint16             BlkOffset;
  uint16             BlkLength;
  uint16             TmpCount;
  uint16             StuffLen;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  #if (FEE_GET_PREV_DATA_API == STD_ON)
  /*[cover parentID={3E59010C-5713-49b6-B920-79C787DF9CCF}][/cover]*/
  if(StateDataPtr->FeePendReqInfo.GetPrevCopy == FEE_SET )
  {
    DflashBlkSize = (uint16)StateDataPtr->FeeBlockInfo[UserBlockIndex].PrevBlkSize;
  }
  else
  #endif
  {
    DflashBlkSize = (uint16)StateDataPtr->FeeBlockInfo[UserBlockIndex].BlockSize;
  }
  BlkOffset = StateDataPtr->FeePendReqInfo.BlockOffset;
  BlkLength = StateDataPtr->FeePendReqInfo.Length;

  DataBufPtr = StateDataPtr->FeePendReqInfo.DataBufferPtr;
  /*[cover parentID={B83EE2E2-4A33-4adc-9175-5924BD8AFD85}][/cover]*/
  if(BlkLength > (uint16)0)
  {
    /* [cover parentID={733A15E7-7C0F-46d0-B83E-B42D2FC0930E}]
    Is block offset greater than configured block size?
    [/cover] */
    /* check whether block offset is greater than configured block size */
    if(BlkOffset > DflashBlkSize)
    {
      for(Count = FEE_RESET; Count < BlkLength; Count++)
      {
        DataBufPtr[Count] = FEE_RESET;
      }
      #if((FEE_DATA_BLOCK_SUPPORTED==FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)&&\
      (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON))
      /*Check if QS erase was suspended. If yes then set FeePendReqStatus to
      FEE_REQ_QUASI_ERASE to set module status to busy.*/
      /*[cover parentID={F9328DFA-7117-4af6-B85A-847C246814FC}][/cover]*/
      if(StateDataPtr->FeeQsEraseSuspend == FEE_ERASE_SUSPENDED)
      {
        /*[cover parentID={A0AE945D-6D16-4696-AFA6-0D346CC170AB}][/cover]*/
        StateDataPtr->FeePendReqStatus = FEE_REQ_QUASI_ERASE;
        StateDataPtr->FeeQsJob = FEE_ERASE_JOB;
      }
      else
      #endif
      {
        /* reset the pending request status */
        StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_NO_REQ;
      }
      /* Set the job result */
      StateDataPtr->FeeJobResult = MEMIF_JOB_OK;
      /* Call user configured job End notification */
      /*[cover parentID={849628AD-9936-4358-A2BB-A6991A416AC2}][/cover]*/
      if ( Fee_CfgPtr->FeeNvmJobEndNotification != NULL_PTR )
      {

        /*[cover parentID={D210FFF8-E123-4e8f-BCE6-1DE16E1826FC}][/cover]*/
        (Fee_CfgPtr->FeeNvmJobEndNotification)();
      }


    }
    /*[cover parentID={84F2E340-D25B-4226-8641-9D835C52AC2B}][/cover]*/
    else if( (BlkOffset + BlkLength) > DflashBlkSize)
    {
      TmpCount = DflashBlkSize - BlkOffset;
      StuffLen = BlkLength - TmpCount;
      StateDataPtr->FeePendReqInfo.Length = TmpCount;
      DataBufPtr = &(StateDataPtr->FeePendReqInfo.DataBufferPtr[TmpCount]);

      /* [cover parentID={FFDEF83C-CEA1-4473-BB90-168255B48FD5}]
      Stuff the buffer with zero data upto stuff length
      [/cover] */
      for(Count = FEE_RESET; Count < StuffLen; Count++)
      {
        DataBufPtr[Count] = FEE_RESET;
      }
    }
    else
    {
      /* Do Nothing */
    }
  }
  /* If length is zero, then reset the status*/
  else
  {
    #if((FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)&&\
        (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON))
    /*Check if QS erase was suspended. If yes then set FeePendReqStatus to
    FEE_REQ_QUASI_ERASE to set module status to busy.*/
    if(StateDataPtr->FeeQsEraseSuspend == FEE_ERASE_SUSPENDED)
    {
      StateDataPtr->FeePendReqStatus = FEE_REQ_QUASI_ERASE;
      StateDataPtr->FeeQsJob = FEE_ERASE_JOB;
    }
    else
    #endif
    {
      StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_NO_REQ;
    }
    /*************   RESET JOB VARIABLES ******************/
    StateDataPtr->FeeJobResult = MEMIF_JOB_OK;
    #if (FEE_GET_PREV_DATA_API == STD_ON)
    StateDataPtr->FeePendReqInfo.GetPrevCopy = FEE_RESET;
    #endif
    /*****************************************************/

    /* Call user configured job End notification */
    /*[cover parentID={3D9E121D-0B6F-47b9-94DB-13C31C6FD8CF}][/cover]*/
    if ( Fee_CfgPtr->FeeNvmJobEndNotification != NULL_PTR )
    {
      /* [cover parentID={3A7A259F-C7F7-4a71-B8B2-52A71CE93270}]
      Call the notification function
      [/cover] */
      (Fee_CfgPtr->FeeNvmJobEndNotification)();
    }
  }

}
#endif

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
/*******************************************************************************
** Syntax : static void Fee_lQsInit(void)                                     **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function will initialize the QS Block Management        **
** Environment variables and also update status of each QS block in cache     **
*******************************************************************************/
/*[cover parentID={0A218B3E-DFB2-4f73-BECF-72D47C85062D}][/cover]*/
static void Fee_lQsInit(void)
{
  Fee_CacheType       *CachePtr;
  const Fee_BlockType *BlockPtr;
  uint32               Index;
  Fee_StateDataType   *StateDataPtr;
  const uint8         *TgtAddr;
  uint32               SrcAddr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  StateDataPtr->FeeQuasiBlkInstanceTemp = FEE_RESET;
  #if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
  StateDataPtr->FeeQsEraseSuspend = FEE_ERASE_NOT_SUSPENDED;
  #endif
  StateDataPtr->FeeQsState = FEE_QS_IDLE;
  StateDataPtr->FeeQsJob = FEE_NO_JOB;
  StateDataPtr->FeeQsIntrJob = FEE_NO_JOB;
  StateDataPtr->FeeQsJobStatus = FEE_JOB_IDLE;
  StateDataPtr->FeeQsIntrJobStatus = FEE_JOB_IDLE;
  StateDataPtr->FeeQsRepairIndex = FEE_RESET;
  StateDataPtr->FeeInitQSState = FEE_RESET;
  StateDataPtr->FeeQsJobResult = MEMIF_JOB_OK;
  StateDataPtr->FeeQsIntrJobResult = MEMIF_JOB_OK;
  StateDataPtr->FeeHardeningWLCount = FEE_RESET;
  StateDataPtr->FeeHardeningPageCount = FEE_RESET;
  StateDataPtr->FeeQsHardeningOffset = FEE_RESET;
  StateDataPtr->FeeQsCancelAll = FEE_RESET;
  StateDataPtr->FeeHardenFlag = FEE_QS_HARDING_IDLE;

  CachePtr = &(StateDataPtr->FeeBlockInfo[FEE_QSBLOCK_BEGIN_INDEX]);
  BlockPtr = &(Fee_CfgPtr->FeeBlockConfigPtr[FEE_QSBLOCK_BEGIN_INDEX]);
  Index = FEE_RESET;
  TgtAddr = StateDataPtr->FeeReadWriteBuffer;

  /*[cover parentID={60B6A811-1097-4e77-AE7C-FC417B36AE00}][/cover]*/
  while(Index < FEE_NUM_QUASI_BLOCKS)
  {
    SrcAddr = BlockPtr->Address;
    CachePtr->Address = SrcAddr;
    CachePtr->Status.QsDirtyErase = 0;
    CachePtr->Status.QsDirtyWrite = 0;
    CachePtr->Status.State = FEE_QS_INVALID;

     /*
      Return value check for Fls_17_Dmu_ReadWordsSync is not required,
      because QS block status will be derived from the marker pages which is read
      in Fee_lEvalQsBlockState.
    */
    (void)Fls_17_Dmu_ReadWordsSync(
      (Fls_17_Dmu_AddressType)SrcAddr,
      /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for interfacing with
      FLS.FEE is passing parameters to FLS APIs, casting is needed to match with
      the Fls API prototype.*/
      /*MISRA2012_RULE_11_8_JUSTIFICATION:This function does not update the
      contents of the pointer. However, the called function will update the
      contents. Hence const qualifier is discarded while passing the argument.*/
      (uint32*)(TgtAddr),
      (Fls_17_Dmu_LengthType)(
        (FEE_QS_STATUS_PAGES * FEE_DFLASH_PAGE_SIZE) / FEE_DFLASH_WORD_SIZE));

    /*[cover parentID={0AC3278B-A799-4d79-9C53-AC79B6666B6F}][/cover]*/
    Fee_lEvalQsBlockState(CachePtr);

    Index++;
    CachePtr++;
    BlockPtr++;
  }

  StateDataPtr->FeeQsIntrJob = FEE_REPAIR_JOB;
}

/******************************************************************************
** Syntax : Std_ReturnType Fee_17_EraseQuasiStaticData(                      **
**          const uint16 BlockNumber, const uint16 Instances)                **
**                                                                           **
** Traceability   : [cover parentID={49B35985-54F0-4ae0-B288-8C77E3121785}]  **
**                                                                           **
** Service ID:        0x25                                                   **
**                                                                           **
** Sync/Async:  Asynchronous                                                 **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in) :  BlockNumber : Logical block number                     **
**                    Instances   : Number of block instances                **
**                                                                           **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    :  Std_ReturnType                                         **
**            E_OK : Erase Request is accepted                               **
**                    E_NOT_OK : Erase Request is not accepted               **
**                                                                           **
** Description : Service to initialize an erase job for one or               **
** multiple consecutive instances of a quasi-static data block               **
******************************************************************************/
/* [cover parentID={FA53B348-A966-4d6d-A389-EFC4E28BEA98}]
Fee_17_EraseQuasiStaticData
[/cover] */
Std_ReturnType Fee_17_EraseQuasiStaticData(const uint16 BlockNumber,
    const uint16 Instances)
{

  Fee_StateDataType  *StateDataPtr;
  uint16               BlockIndex;
  Std_ReturnType       RetVal;
  RetVal = E_NOT_OK;
  /* [cover parentID={67BE3317-4E3B-4f84-9DB3-E1B574C5EC60}]
  Is Check return with E_OK
  [/cover] */
  if(Fee_lEraseQsDataSafetycheck() == E_OK)
  {
    /* [cover parentID={6A2F02C4-16B3-4795-B6C4-7BD1D53D3324}]
    Get the block index of the requested QS block
    [/cover] */
    /* Get index of the block info stored in cache */
    BlockIndex = Fee_lGetUsrBlockIndex(BlockNumber);

    /*Accept the request only for QS block*/
    /* [cover parentID={880F3A68-FA22-4a51-93BC-92E3504CF99E}][/cover] */
    if((BlockIndex != FEE_LOG_BLOCK_NOT_FOUND) &&
        (Fee_CfgPtr->FeeBlockConfigPtr[BlockIndex].FeeUser ==
         (uint8)FEE_QUASI_STATIC_USER))
    {
      if(Instances == FEE_ZERO)
      {
        /*Invalid block instances value, raise safety error
         if configured */
        RetVal = E_NOT_OK;
        /* [cover parentID={706A3FE2-81A4-4f2e-9F94-F2114A858C94}]
        Safety error is enabled
        [/cover] */
        #if(FEE_SAFETY_ENABLE == STD_ON)
        /* [cover parentID={27F3883E-18DB-49f2-81A9-8AF55E32DD9A}]
        Report error FEE_E_INVALID_BLOCK_INTS
        [/cover] */
        Fee_lReportError(FEE_SID_ERASEQUASISTATICDATA,
                        FEE_SE_INVALID_BLOCK_INSTANCES, FEE_SAFETY_ERROR);
        #endif
      }
      /* [cover parentID={F11117B3-1478-48a4-B55F-6FED8871BFE0}]
      (Input instances is less than the configured block instances) or (is configured block instances equals zero and given instances is 1) ?
      [/cover] */
      else if((Instances <=
          Fee_CfgPtr->FeeBlockConfigPtr[BlockIndex].Instances) ||
          ((Fee_CfgPtr->FeeBlockConfigPtr[BlockIndex].Instances == FEE_ZERO)
          && (Instances == FEE_ONE)))
      {
        StateDataPtr = Fee_CfgPtr->FeeStatePtr;
        StateDataPtr->FeePendEraseInfo.CacheIndex = BlockIndex;
        StateDataPtr->FeePendEraseInfo.BlockInstances = Instances;
        StateDataPtr->FeePendEraseInfo.BlockNumber = BlockNumber;
        StateDataPtr->FeeQuasiBlkInstanceTemp = FEE_RESET;
        StateDataPtr->FeePendReqStatus = FEE_REQ_QUASI_ERASE;
        StateDataPtr->FeeQsJobResult = MEMIF_JOB_PENDING;
        StateDataPtr->FeeQsJob = FEE_ERASE_JOB;
        StateDataPtr->FeeQsState = (uint8)FEE_QS_PROG_STATE_ERASE_STARTED;
        StateDataPtr->FeeCurrReqBlockNum = BlockNumber;
        RetVal = E_OK;

        /* Set this flag to start GC and cache update process before
        serving Erase request.This will insure proper Erase operation in
        case GC is disabled during FEE initialization */
        StateDataPtr->FeeStatusFlags.FeeStartInitGC = FEE_SET;
        StateDataPtr->FeeStatusFlags.FeeWriteInvldQSeraseAPICalled=FEE_SET;
      }
      else
      {
        /*Invalid block instances value, raise safety error
          if configured */
        RetVal = E_NOT_OK;

        #if(FEE_SAFETY_ENABLE == STD_ON)
        Fee_lReportError(FEE_SID_ERASEQUASISTATICDATA,
                        FEE_SE_INVALID_BLOCK_INSTANCES, FEE_SAFETY_ERROR);
        #endif
      }


    }
    /* [cover parentID={6AF8CD71-96CC-45b2-8317-6F6F2D9DEDF5}]
    Safety error enabled
    [/cover] */
    #if(FEE_SAFETY_ENABLE == STD_ON)
    else
    {
      /* [cover parentID={F2CAB662-7CEC-49a4-8680-D9D98BCCBD0C}]
      Report Error as FEE_E_INVALID_BLOCK_NO
      [/cover] */
      Fee_lReportError(FEE_SID_ERASEQUASISTATICDATA,
                      FEE_SE_INVALID_BLOCK_NO, FEE_SAFETY_ERROR);
    }
    #endif
  }
  /* [cover parentID={40565740-7EE4-4c46-97D3-2B98D709C215}]
  Return
  [/cover] */
  return(RetVal);
}

/*******************************************************************************
** TRACEABILITY: [cover parentID={003CA79B-BA5C-442a-B315-3DAED23EC898}]      **
**                                                                            **
** Syntax : MemIf_JobResultType Fee_17_GetQuasiStaticJobResult(void)          **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x27                                                          **
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
** Description : Service to query the result of the last accepted job issued  **
** by QS Manager                                                              **
**                                                                            **
*******************************************************************************/
/* [cover parentID={AAD5F634-CB70-4b60-996F-D6DD5CFC274C}]
Fee_17_GetQuasiStaticJobResult
[/cover] */
MemIf_JobResultType Fee_17_GetQuasiStaticJobResult(void)
{

  const Fee_StateDataType  *StateDataPtr;
  MemIf_JobResultType ReturnValue;
  /* [cover parentID={0BA4CE80-3F48-4ea2-9D52-80DF2A5A07C1}]
  Safety is enabled
  [/cover] */
  #if (FEE_SAFETY_ENABLE == STD_ON)
  /*Check Fee_CfgPtr is null if yes return E_not_ok . This done to avoid trap
  if fee_init is not called */
  /* [cover parentID={1D69D905-A488-498f-A651-09E75E464828}][/cover] */
  if(Fee_CfgPtr != NULL_PTR)
  #endif
  {
    #if(MCAL_AR_VERSION == MCAL_AR_440)
    /* [cover parentID={F83109EE-32B8-40c2-9F78-6A4720A2505A}]
    Is driver initialization is complete
    [/cover] */
    if(Fee_lGetStatus() != MEMIF_UNINIT)
    #endif
    {
      StateDataPtr = Fee_CfgPtr->FeeStatePtr;
      ReturnValue = StateDataPtr->FeeQsJobResult;
    }
    #if(MCAL_AR_VERSION == MCAL_AR_440)
    else
    {
    #if (FEE_SAFETY_ENABLE == STD_ON)
      Fee_lReportError(FEE_SID_GETQUASISTATICJOBRESULT,
                            FEE_SE_UNINIT, FEE_SAFETY_ERROR);
    #endif
      ReturnValue = MEMIF_JOB_FAILED;
    }
    #endif
  }
  #if (FEE_SAFETY_ENABLE == STD_ON)
  else
  {
    /* [cover parentID={C6EE60F6-34E1-42f7-BEF6-61683C73D0E4}]
    Report safety error as FEE_E_UNINIT
    [/cover] */
    Fee_lReportError(FEE_SID_GETQUASISTATICJOBRESULT,
                            FEE_SE_UNINIT, FEE_SAFETY_ERROR);
    ReturnValue = MEMIF_JOB_FAILED;
  }

  #endif
  /* [cover parentID={9A9BED7E-067C-4da1-9F5A-3DB8151AA8A7}]
  Return the quasi static job result
  [/cover] */
  return(ReturnValue);
  /* [cover parentID={D2BEC781-8CBC-4464-BD83-25999ADC4808}]
  Return
  [/cover] */

}/*End of Fee_17_GetQuasiStaticJobResult */

/*******************************************************************************
** TRACEABILITY: [cover parentID={9CE9B6A6-08CB-48c3-91C3-1E6C24970EAC}]      **
**                                                                            **
** Syntax : MemIf_JobResultType Fee_17_GetQuasiStaticBlockInfo(               **
**          const uint16 BlockNumber,                                         **
**          Fee_QuasiStaticBlockInfoType * const BlockInfoPtr)                **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x26                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  BlockNumber : Logical block number                      **
**                                                                            **
** Parameters (out):  BlockInfoPtr : constant pointer to BlockInfo structure  **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                    E_OK : QS block info was read successfully              **
**                    E_NOT_OK : QS block info not available                  **
**                                                                            **
** Description : Service to read the Block State and the Block Cycle Counter  **
** of the given quasi-static data block instance.                             **
**                                                                            **
*******************************************************************************/
/* [cover parentID={C92C92E6-B01A-47ef-BD7D-BA7E974C2FD9}]
Fee_17_GetQuasiStaticBlockInfo
[/cover] */
Std_ReturnType Fee_17_GetQuasiStaticBlockInfo(const uint16 BlockNumber,
                            Fee_QuasiStaticBlockInfoType * const BlockInfoPtr)
{
  /* [cover parentID={C92C92E6-B01A-47ef-BD7D-BA7E974C2FD9}]*/
  const Fee_StateDataType  *StateDataPtr;
  uint32              BlkAddress;
  Std_ReturnType      ReadStat;
  uint32              BccBuffer[2];
  uint16              Bcc;
  uint16              BlockIndex;
  uint16              BccComp;
  Std_ReturnType      RetVal;


  RetVal = E_NOT_OK;
  ReadStat = E_OK;
  Bcc = FEE_RESET;

  /*Check Fee_CfgPtr is null if yes return E_not_ok . This done to avoid trap
  if fee_init is not called */
  /* [cover parentID={8CFB6FFB-C9AF-4713-8D57-A65990A00829}]
  Is check return with E_OK
  [/cover] */
  if(Fee_lQsBlkInfoSafetyCheck(BlockInfoPtr) == E_OK)
  {
    StateDataPtr = Fee_CfgPtr->FeeStatePtr;
    /* [cover parentID={91B0DB6B-5BAB-45c7-A448-AA7998BF85F2}]
    Get the block index of the requested quasi block
    [/cover] */
    /* Get index of the block info stored in cache */
    BlockIndex = Fee_lGetUsrBlockIndex(BlockNumber);
    /* [cover parentID={C1FB5201-9E3C-4ee8-B4AD-F0A15C742A41}]
    If the block is found and it is a QS block?
    [/cover] */
    /*Accept the request only for QS block*/
    if((BlockIndex != FEE_LOG_BLOCK_NOT_FOUND) &&
        (Fee_CfgPtr->FeeBlockConfigPtr[BlockIndex].FeeUser ==
         (uint8)FEE_QUASI_STATIC_USER))
    {
      /* [cover parentID={03607BAC-F3D3-44a2-A037-4F1E06365A07}]
      Make a local copy of block address
      Update Cache Status state
      [/cover] */
      BlkAddress = StateDataPtr->FeeBlockInfo[BlockIndex].Address;
      BlockInfoPtr->State =
        StateDataPtr->FeeBlockInfo[BlockIndex].Status.State;

      /*Check if the block state is FEE_QS_WRITE_COMPLETE if yes then read the
      BCC value from block , otherwise return BCC as 0 */
      /* [cover parentID={2ACF6C55-BA2D-417f-A398-2FAFF9A250EE}][/cover] */
      if(BlockInfoPtr->State == FEE_QS_WRITE_COMPLETE)
      {
        BlkAddress += FEE_QS_STATE_CYCLE_COUNT_OFFSET;
        ReadStat = Fls_17_Dmu_ReadWordsSync(
                     (Fls_17_Dmu_AddressType)BlkAddress,
                     /*MISRA2012_RULE_1_3_JUSTIFICATION:undefined behavior is
                     not expected because the called function limits the array
                     access to the length passed.*/
                     BccBuffer,
                     (FEE_DFLASH_PAGE_SIZE / FEE_DFLASH_WORD_SIZE));
        /* [cover parentID={470B4610-1CD1-4687-9FA2-78D3026B63AF}][/cover] */
        if(ReadStat == E_OK)
        {
          Bcc = (uint16)(BccBuffer[0] & FEE_16_BIT_ALL_ONES);
          BccComp = (uint16)((BccBuffer[0] >> 16) & FEE_16_BIT_ALL_ONES);
          /* [cover parentID={50FF8EC8-776E-4f1d-87E0-3C8B253ABED5}][/cover] */
          if(BccComp != ((~Bcc) & (uint16)FEE_16_BIT_ALL_ONES))
          {
            Bcc = FEE_RESET;
          }
        }

      }
      /* [cover parentID={EEBCD590-E211-40d0-8470-7BBF5C94D55A}]
      Set flag as E_OK
      [/cover] */
      RetVal = E_OK;
      BlockInfoPtr->Bcc = Bcc;
      /* [cover parentID={84022884-66C0-4364-947A-9AA24DDED927}]
      Check for ECC error
      [/cover] */
      /*Check if FLS returns E_NOT_OK due to ECC error*/
      if(ReadStat == E_NOT_OK)
      {
        /* [cover parentID={7D8259E7-347D-437b-A75F-6F09AD98B67F}]
        Set flag as E_NOT_OK
        [/cover] */
        RetVal = E_NOT_OK;
      }
    }
    /* [cover parentID={F9339422-88E3-4ff0-A521-1B07D811FC03}]
    Safety is enabled
    [/cover] */
    #if (FEE_SAFETY_ENABLE == STD_ON)
    else
    {
      /* [cover parentID={466FD2BA-81EE-4f43-8BAF-D8E78D7B642E}]
      Report safety error as FEE_E_INVALID_BLOCK_NO
      [/cover] */
      Fee_lReportError(FEE_SID_GETQUASISTATICBLOCKINFO,
                      FEE_SE_INVALID_BLOCK_NO, FEE_SAFETY_ERROR);
    }
    #endif
  }
  /* [cover parentID={5C0A2BB8-3CA9-45a1-8A1F-6FC37B34FEB9}]
  Return
  [/cover] */
  return(RetVal);

}/*End of Fee_17_GetQuasiStaticBlockInfo */

/*******************************************************************************
** Syntax : static void Fee_lQsErase(void)                                    **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function Performs various state transition handling     **
** during QS Block erase operation                                            **
*******************************************************************************/
/* [cover parentID={DBDCD90B-D850-47cd-9774-802FFDF31256}]
Fee_lQsErase
[/cover] */
/* [cover parentID={DB0128CB-3C66-4925-861F-D95EDC4F045B}][/cover] */
static void Fee_lQsErase(void)
{
  uint16                UserBlockIndex;
  uint16        BlockInstances;
  Fee_StateDataType  *StateDataPtr;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  UserBlockIndex = StateDataPtr->FeePendEraseInfo.CacheIndex;

  /* [cover parentID={089BD1C3-CB3E-4fe3-A592-9C5B14AC8786}]
  Has QS erase started?
  [/cover] */
  if(StateDataPtr->FeeQsState == (uint8)FEE_QS_START_ERASE)
  {
    Fee_lQsBlockErase();

    StateDataPtr->FeeQuasiBlkInstanceTemp = FEE_RESET;
    /* set the cache state to erase started */
  }
  /* [cover parentID={E98FA218-509E-4272-8C45-5574A60DE694}][/cover] */
  else if(StateDataPtr->FeeQsState == (uint8)FEE_QS_ERASE_COMPLETE)
  {
    StateDataPtr->FeeQuasiBlkInstanceTemp = FEE_RESET;
    BlockInstances = StateDataPtr->FeePendEraseInfo.BlockInstances;
    /* set the cache state to erase completed */
    /*MISRA2012_RULE_10_4_JUSTIFICATION:Types are same. It is unsigned int*/
    /* [cover parentID={D24D87E7-CCA6-4cab-B92C-69CF71C6AD7E}][/cover] */
    while(BlockInstances != 0)
    {
      StateDataPtr->FeeBlockInfo[UserBlockIndex].Status.State =
        FEE_QS_ERASE_COMPLETE;
      BlockInstances--;
      UserBlockIndex++;
    }
    StateDataPtr->FeePendEraseInfo.BlockInstances = FEE_RESET;
    Fee_lHandleQsJobSuccess();
  }
  else
  {
    /* [cover parentID={6273CF87-5A99-47e4-9039-C5CBF79A8783}][/cover] */
    Fee_lQsProgState();
  }
}/*End of Fee_lQsErase */

#if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
/*******************************************************************************
** Syntax : static void Fee_lQsResumeErase(void)                              **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function resumes the previous erase operation which was **
** suspended due to another Read/Write User job                               **
*******************************************************************************/
 /* [cover parentID={AF20F0AC-9EC9-4de3-8D10-8980E23D42CE}][/cover] */
static void Fee_lQsResumeErase(void)
{
  Fee_StateDataType  *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* [cover parentID={AA3A4028-DA6F-43ba-8FF5-B0E79DA49A94}][/cover] */
  /* [cover parentID={5DB255C6-A64A-49ff-819C-7FBD0DF72083}][/cover] */
  if(E_OK == Fls_17_Dmu_ResumeErase())
  {
    StateDataPtr->FeeQsEraseSuspend = FEE_ERASE_NOT_SUSPENDED;
    StateDataPtr->FeeQsState = (uint8)FEE_QS_PROG_STATE_ERASE_COMPLETE;
    StateDataPtr->FeeQsJobStatus = FEE_JOB_REQSTD;
    StateDataPtr->FeeQsJob = FEE_ERASE_JOB;
    StateDataPtr->FeeQsJobResult = MEMIF_JOB_PENDING;
    StateDataPtr->FeePendReqStatus = FEE_REQ_QUASI_ERASE;

  }
  else
  {
    /* Raise the job error and illegal notification*/

    Fee_lHandleQsJobFailure((FEE_NOT_CANCEL));
    if(Fee_CfgPtr->FeeQsIllegalStateNotification != NULL_PTR)
    {
    /* [cover parentID={7BE5FCF6-9F96-43b6-87AC-E7AB8B51A9C6}][/cover] */
      Fee_CfgPtr->FeeQsIllegalStateNotification();
    }

  }
}/*End of Fee_lQsResumeErase */
#endif
/*******************************************************************************
** Syntax : static void Fee_lRegisterQsRead(const uint16 BlockNumber,         **
** const uint16 BlockOffset, uint8 *const DataBufferPtr, const uint16 Length) **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  BlockNumber : Logical block numberNone                  **
**                    BlockOffset : Read address offset within the block      **
**                    Length      : Number of bytes to be read                **
**                    DataBufferPtr : pointer to data buffer where the qs     **
**                                    block data in Dflash will be updated    **
** Parameters (out):  DataBufferPtr : None                                    **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                    E_OK : Request is registered.                           **
**                    E_NOT_OK : Request is not registered. FEE module is busy**
**                     in servicing other request.                            **
** Description : This function will register the QS read request in the       **
** pending request buffer if FEE is Idle or QS Erase is ongoing and erase     **
** suspend enabled                                                            **
*******************************************************************************/
/* [cover parentID={1E4145B5-4D70-49de-B122-D8AB268DAD76},
{A8409AA6-4B75-47f3-82BA-1756DBF2FB5B}]
Fee_lRegisterQsRead
[/cover] */
static Std_ReturnType Fee_lRegisterQsRead( const uint16 BlockNumber,
    const uint16 BlockOffset, uint8 * const DataBufferPtr, const uint16 Length)
{
  Fee_StateDataType  *StateDataPtr;
  Std_ReturnType RetVal;
  MemIf_StatusType   ReturnStatus;
  Fee_PendReqBufType   *PendReqPtr;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  PendReqPtr = &(StateDataPtr->FeePendReqInfo);

  #if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)

  /* check whether quasi erase job is ongoing */
  /* [cover parentID={D4567254-3099-4a29-99DC-EC655619A6CE}][/cover] */
  if((StateDataPtr->FeeQsState == (uint8)FEE_QS_PROG_STATE_ERASE_COMPLETE) &&
      (StateDataPtr->FeeQsJobStatus == FEE_JOB_REQSTD))
  {
    /* [cover parentID={AFAF3581-1296-4dfa-A9C2-109D92694AE7}]
    Initiate suspend erase and update flag status
    [/cover] */
    /* erase is ongoing and can be suspended */
    RetVal = Fls_17_Dmu_SuspendErase();
    /* [cover parentID={36EAE65E-A4AA-41b5-A59F-8D02713A64FD}][/cover] */
    if(RetVal == E_OK)
    {
      StateDataPtr->FeeQsEraseSuspend = FEE_ERASE_SUSPENDED;
      StateDataPtr->FeeQsJobStatus = FEE_JOB_IDLE;
    }
  }
  else if(StateDataPtr->FeeQsEraseSuspend == FEE_ERASE_SUSPENDED)
  {
    RetVal =  E_OK;
    StateDataPtr->FeeQsJobStatus = FEE_JOB_IDLE;
  }
  else
  #endif
  {
    /* [cover parentID={B16224CA-4556-4831-9F2C-0C75397128F7}]
    Check FEE driver status
    [/cover] */
    /* check the Fee Driver status */
    ReturnStatus = Fee_lGetStatus();
    /* [cover parentID={A280A970-50B9-4fa9-B2D2-BB5AE5A9C9B4}]
    Is the driver busy?
    [/cover] */
    /* As per new request read should be accepted for MEMIF_BUSY_INTERNAL */
    if(ReturnStatus == MEMIF_BUSY)
    {
      /* [cover parentID={9D93D99A-D25E-4f2b-BD80-09B18D88B192}]
      Set Flag as NOT OK
      [/cover] */
      RetVal = E_NOT_OK;
  #if(FEE_RUNTIME_ERROR_DETECT == STD_ON) || (((FEE_DEV_ERROR_DETECT == STD_ON)\
    || (FEE_SAFETY_ENABLE == STD_ON)) && (MCAL_AR_VERSION == MCAL_AR_422))
    #if(MCAL_AR_VERSION == MCAL_AR_440)
    Fee_lReportError(FEE_SID_READ, FEE_E_BUSY, FEE_RUNTIME_ERROR);
  #else
    Fee_lReportError(FEE_SID_READ, FEE_E_BUSY, FEE_DET_SAFETY_ERROR);
  #endif
  #endif
    }
    else
    {
      /* [cover parentID={763A9DFF-B6D9-4c82-9D76-AE6D7E6E8045}]
      Set Flag as OK
      [/cover] */
      RetVal = E_OK;
    }
  }
  /* [cover parentID={99954DAF-8A75-4d09-A05E-6C9140E939F4}][/cover] */
  if(RetVal == E_OK)
  {
    /* [cover parentID={04623D01-D44E-43c8-B774-DF745FF3D1E7}]
    Store the read request parameters in the Pending buffer structure
    Update QS job as read job and job result as MEMIF_JOB_PENDING
    [/cover] */
    /* Store the read request parameters in the Pending buffer structure */
    PendReqPtr->BlockNumber = BlockNumber;
    PendReqPtr->BlockOffset = BlockOffset;
    PendReqPtr->DataBufferPtr = DataBufferPtr;
    PendReqPtr->Length = Length;

    StateDataPtr->FeePendReqStatus = FEE_REQ_QUASI_READ;
    StateDataPtr->FeeQsJobResult = MEMIF_JOB_PENDING;
    StateDataPtr->FeeQsJob = FEE_READ_JOB;
    StateDataPtr->FeeCurrReqBlockNum = BlockNumber;

    /* Set this flag to start GC and cache update process before serving write
       request.This will insure proper write operation in case GC is disabled
       during FEE initialization */
    StateDataPtr->FeeStatusFlags.FeeStartInitGC = FEE_SET ;
  }
  /* [cover parentID={A2ACCDE5-7C17-4956-9768-481F8D5BA8B4}]
  Return Flag status
  [/cover] */
  return(RetVal);
  /* [cover parentID={66C90A49-B70B-45e0-A449-F0345D62201C}]
  Return
  [/cover] */
}/*End of Fee_lRegisterQsRead */

/*******************************************************************************
** Syntax : static void Fee_lQsRead(void)                                     **
**                                                                            **
** Service ID:                                                                **
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
** Description : This function Triggers QS Block Data read on D-Flash as per  **
** Block details in pending Request buffer                                    **
*******************************************************************************/
/* [cover parentID={F130D237-0765-4aad-A128-2C2018AA1647}]
Fee_lQsRead
[/cover] */
 /* [cover parentID={7482B9C5-32DE-4f2d-9522-1349792154BC}][/cover] */
static void Fee_lQsRead(void)
{
  Fee_StateDataType    *StateDataPtr;
  const Fee_BlockType  *PendReqBlkPtr;
  uint32                SrcAddress;
  uint16                PendReqBlkNum;
  uint16                PendReqBlkIndex;
  uint16        Length;
  Std_ReturnType        RetVal;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  Length = StateDataPtr->FeePendReqInfo.Length;
  PendReqBlkNum = StateDataPtr->FeePendReqInfo.BlockNumber;

  /* [cover parentID={92A05FD6-C687-4127-8AF7-A2C80D1A3274}][/cover] */
  if(Length > ((uint16)0))
  {
    /* [cover parentID={FAF0FCFC-BBBD-4d45-BBB2-7F16531D99AE}][/cover] */
    PendReqBlkIndex = Fee_lGetUsrBlockIndex(PendReqBlkNum);
    PendReqBlkPtr = &(Fee_CfgPtr->FeeBlockConfigPtr[PendReqBlkIndex]);
    SrcAddress = PendReqBlkPtr->Address;
    /* [cover parentID={8B308AEE-F808-4f1c-B189-863340AC1B16}]
    Update the source address by accessing the address of the block required and adding QS data offset to it(36 bytes)
    [/cover] */
    /* point it to right offset location */
    /*MISRA2012_RULE_10_4_JUSTIFICATION:Types are same. It is unsigned int*/
    SrcAddress += StateDataPtr->FeePendReqInfo.BlockOffset + FEE_QS_DATA_OFFSET;
    /* [cover parentID={65B9927E-22E2-4af0-B17A-AC7007AF1EA1}][/cover] */
    RetVal = Fls_17_Dmu_Read((Fls_17_Dmu_AddressType)SrcAddress,
                   StateDataPtr->FeePendReqInfo.DataBufferPtr,
                   (Fls_17_Dmu_LengthType)StateDataPtr->FeePendReqInfo.Length);
    /* [cover parentID={604268C2-1878-44b0-8A50-C6C51299A9D2}][/cover] */
    if(RetVal == E_OK)
    {
      StateDataPtr->FeeQsState = FEE_REQ_QUASI_READ;
      StateDataPtr->FeeQsJobStatus = FEE_JOB_REQSTD;
    }
    else
    {
      /* Call the Fee_lHandleQsJobFailure with  (FEE_NOT_CANCEL) to notify
        user about failed of job*/
      Fee_lHandleQsJobFailure((FEE_NOT_CANCEL));
    }
  }
  /*Reset the status if length is zero*/
  else
  {

    Fee_lHandleQsJobSuccess();

  }
}/*End of Fee_lQsRead */

/*******************************************************************************
** Syntax : static void Fee_lRegisterQsWrite(                                 **
**                               const uint8 * const DataWriteBufferPtr,      **
**                               const Fee_BlockType * const BlockPtr)        **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  BlockPtr    : Pointer to block configuration            **
**                 :  DataWriteBufferPtr : pointer to data buffer             **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                    E_OK : Request is registered.                           **
**                    E_NOT_OK : Request is not registered. FEE module is busy**
**                     in servicing other request.                            **
** Description : This function will register the QS write request in the      **
** pending request buffer if FEE is Idle or QS Erase is ongoing and erase     **
** suspend is enabled                                                         **
*******************************************************************************/
/* [cover parentID={EA51FD4F-7011-4d3c-BDE6-69A23D11E8D0},
                     {64B68921-2DA4-4e1e-A7DC-5947FA87E4C7}]
Fee_lRegisterQsWrite
[/cover] */
static Std_ReturnType Fee_lRegisterQsWrite( \
    const uint8 * const DataWriteBufferPtr, \
    const Fee_BlockType * const BlockPtr)
{
  Fee_StateDataType  *StateDataPtr;
  Std_ReturnType      RetVal;
  MemIf_StatusType    ReturnStatus;
  Fee_PendReqBufType  *PendReqPtr;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  PendReqPtr = &(StateDataPtr->FeePendReqInfo);

  #if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
  /* [cover parentID={47B512BE-4EE1-42a4-BBD5-E7D00262BD79}][/cover] */
  if((StateDataPtr->FeeQsState == (uint8)FEE_QS_PROG_STATE_ERASE_COMPLETE) &&
      (StateDataPtr->FeeQsJobStatus == FEE_JOB_REQSTD))
  {
    /* [cover parentID={F8D319B0-90A3-4f96-968B-EA48DF7EC5CE}]
    Initiate suspend erase and update flag status
    [/cover] */
    RetVal = Fls_17_Dmu_SuspendErase();
    /* [cover parentID={D80642F4-C1DB-47e9-92A1-25CACC077210}][/cover] */
    if(RetVal == E_OK)
    {
      /* [cover parentID={8DF90125-6B71-4aa1-821D-E7920B09DB30}][/cover] */
      StateDataPtr->FeeQsEraseSuspend = FEE_ERASE_SUSPENDED;
      StateDataPtr->FeeQsJobStatus = FEE_JOB_IDLE;
    }
  }

  else if(StateDataPtr->FeeQsEraseSuspend == FEE_ERASE_SUSPENDED)
  {
    /* [cover parentID={31CDD652-A210-4101-B4C1-1166FDC5700B}][/cover] */
    RetVal =  E_OK;
    StateDataPtr->FeeQsJobStatus = FEE_JOB_IDLE;
  }
  else
  #endif
  {
    /* [cover parentID={47EC0F19-3082-46ca-AF45-9400AEDE4752}]
    Get Fee job status
    [/cover] */
    ReturnStatus = Fee_lGetStatus();

    /*Check if module is busy with NVM request. if not accept job else reject
    job */
    /* [cover parentID={94A830E6-9C89-4e85-A428-530FE9526896}][/cover] */
    if(ReturnStatus == MEMIF_BUSY)
    {
      /* [cover parentID={3869D8A5-6BEF-45b8-9C1E-FFC51AE85BE0}]
      Update Flag status as E_NOT_OK
      [/cover] */
  #if(FEE_RUNTIME_ERROR_DETECT == STD_ON)
      /* [cover parentID={E624BB6C-86BB-43a1-BCD1-17F919706233}]
      Report runtime error FEE_E_BUSY error
      [/cover] */
      Fee_lReportError(FEE_SID_WRITE, FEE_E_BUSY, FEE_RUNTIME_ERROR);
  #elif(((FEE_DEV_ERROR_DETECT == STD_ON) || (FEE_SAFETY_ENABLE == STD_ON)) \
  && (MCAL_AR_VERSION == MCAL_AR_422))
      Fee_lReportError(FEE_SID_WRITE, FEE_E_BUSY, FEE_DET_SAFETY_ERROR);
  #endif
      /* [cover parentID={3869D8A5-6BEF-45b8-9C1E-FFC51AE85BE0}]
      Update Flag status as E_NOT_OK
      [/cover] */
      RetVal = E_NOT_OK;
    }
    else
    {
      /* [cover parentID={A2A1E98F-3B35-43d1-BA0A-0AA02CFB2CBA}]
      Update Flag status as E_OK
      [/cover] */
      RetVal = E_OK;
    }
  }
  if(RetVal == E_OK)
  {
    /* [cover parentID={288C8F43-5267-4d50-A935-106DD5EFE509}]
    Store the read request parameters in the pending buffer structure
    Set QsJobResult to MEMIF_JOB_PENDING
    Set Pending request status as FEE_REQ_QUASI_WRITE
    Set QsJob as FEE_WRITE_JOB
    Set QsState as FEE_QS_PROG_STATE_WRITE_STARTED
    [/cover] */
    /* Store the read request parameters in the Pending buffer structure */
    PendReqPtr->BlockNumber = BlockPtr->BlockNumber;
    PendReqPtr->DataWriteBufferPtr = DataWriteBufferPtr;
    PendReqPtr->Length = BlockPtr->Size;
    StateDataPtr->FeePendReqStatus = FEE_REQ_QUASI_WRITE;
    StateDataPtr->FeeQsJobResult = MEMIF_JOB_PENDING;
    StateDataPtr->FeeQsJob = FEE_WRITE_JOB;
    StateDataPtr->FeeQsState = (uint8)FEE_QS_PROG_STATE_WRITE_STARTED;
    StateDataPtr->FeeCurrReqBlockNum = BlockPtr->BlockNumber;

    /* Set this flag to start GC and cache update process before serving write
       request.This will insure proper write operation in case GC is disabled
       during FEE initialization */
    StateDataPtr->FeeStatusFlags.FeeStartInitGC = FEE_SET ;
    StateDataPtr->FeeStatusFlags.FeeWriteInvldQSeraseAPICalled = FEE_SET ;

  }
  /* [cover parentID={565EC67C-EC86-415f-8FCA-BEA8EDD945A6}]
  Return Flag status
  [/cover] */
  return(RetVal);
  /* [cover parentID={7FAEC9EB-835A-4aae-83AC-B22032F0BD02}]
  Return
  [/cover] */
}/*End of Fee_lRegisterQsWrite */

/*******************************************************************************
** Syntax : static void Fee_lQsWrite(void)                                    **
**                                                                            **
** Service ID:                                                                **
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
** Description : This function Performs various state transition handling     **
** during QS Block write operation                                            **
*******************************************************************************/
/* [cover parentID={243E4334-3CBC-489d-BA93-F61DE6961841}]
Fee_lQsWrite
[/cover] */
/* [cover parentID={0E72030F-3B05-4217-957B-AFE3F2A1037D}] */
static void Fee_lQsWrite(void)
{
  Fee_StateDataType  *StateDataPtr;
  uint16                UserBlockIndex;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  UserBlockIndex = StateDataPtr->FeePendReqInfo.CacheIndex;
  switch(StateDataPtr->FeeQsState)
  {
    /* [cover parentID={47A2416C-2A6F-4466-B820-9D8E62450660}][/cover] */
    case (uint8)FEE_QS_START_BCC_WRITE:
    {
      /* set the cache state to write started */
      /* [cover parentID={4F4CC0E1-4BB8-4bb9-B2AF-4ED121D63FD8}][/cover] */
      StateDataPtr->FeeBlockInfo[UserBlockIndex].Status.State =
        FEE_QS_WRITE_STARTED;
      Fee_lQsBccWrite();
      break;
    }
    /* [cover parentID={82A3F878-9411-4e6b-8B06-E5FBE3EEE3A6}][/cover] */
    case (uint8)FEE_QS_START_BLOCK_WRITE:
    {
      /* [cover parentID={973A9D02-6A91-4911-8997-44D4974EF737}][/cover] */
      Fee_lQsBlockWrite();
      break;
    }
    /* [cover parentID={CD60B558-AB84-4e35-9286-975656847130}][/cover] */
    case (uint8)FEE_QS_WRITE_COMPLETE:
    {
      /* set the cache state to write complete */
      StateDataPtr->FeeBlockInfo[UserBlockIndex].Status.State =
        FEE_QS_WRITE_COMPLETE;
      /* [cover parentID={A389B822-D146-4734-902F-69E4C27FDD12}][/cover] */
      Fee_lHandleQsJobSuccess();
      break;
    }
    case (uint8)FEE_QS_PROG_STATE_WRITE_COMPLETE:
    case (uint8)FEE_QS_PROG_STATE_WRITE_STARTED:
    {
      /* [cover parentID={958BB304-6240-44ed-87CE-43E3F302AFD9}][/cover] */
      Fee_lQsProgState();
      break;
    }
  default:
  {
    break;
  }
  }
}/*End of Fee_lQsWrite */

/*******************************************************************************
** Syntax : static void Fee_lQsBccWrite(void)                                 **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function Performs QS Block BCC write operation          **
*******************************************************************************/
/* [cover parentID={869C59BD-0283-4a6b-8383-6BF55AA34E50}][/cover] */
static void Fee_lQsBccWrite(void)
{
  uint32                DestAddr;
  const uint32*         SrcPtr;
  Fee_StateDataType    *StateDataPtr;
  const Fee_BlockType  *PendReqBlkPtr;
  Std_ReturnType        RetVal;
  uint32                Bcc;
  uint32                BccComp;
  uint16                PendReqBlkNum;
  uint16                PendReqBlkIndex;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  PendReqBlkNum = StateDataPtr->FeePendReqInfo.BlockNumber;
  PendReqBlkIndex = Fee_lGetUsrBlockIndex(PendReqBlkNum);
  PendReqBlkPtr = &(Fee_CfgPtr->FeeBlockConfigPtr[PendReqBlkIndex]);
  Bcc = (uint32)Fee_lQsGetBcc(PendReqBlkIndex);
  /* Bcc += FEE_ONE; */
  BccComp = ~Bcc;
  BccComp &= BccComp;

  StateDataPtr->FeeTempArray[0] = (BccComp << FEE_SIXTEEN);
  StateDataPtr->FeeTempArray[0] |= (Bcc);

  StateDataPtr->FeeTempArray[1] =
    /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 32 bit
    access and array is memory aligned.*/

    *(const uint32*)(StateDataPtr->FeePendReqInfo.DataWriteBufferPtr);
  /* [cover parentID={EEC90E79-187D-446e-8FE9-1A46DD94F90F}]
  Set Write address to BCC page of block
  [/cover] */
  DestAddr = PendReqBlkPtr->Address + (FEE_QS_STATE_CYCLE_COUNT_OFFSET);
  SrcPtr = StateDataPtr->FeeTempArray;
  /* [cover parentID={3E07EA18-F991-4f55-969F-5F6A77C38AA6}]
  Initiate FLS write
  [/cover] */
  RetVal = Fls_17_Dmu_Write(DestAddr, (const uint8*)SrcPtr,
                            (Fls_17_Dmu_LengthType)FEE_DFLASH_PAGE_SIZE);

  /* [cover parentID={89715503-1E84-415d-A1F8-E971DB881ECE}][/cover] */
  if( RetVal == E_OK)
  {
    StateDataPtr->FeeQsState = (uint8)FEE_QS_START_BLOCK_WRITE;
    StateDataPtr->FeeQsJobStatus = (uint8)FEE_JOB_REQSTD;
  }
  else
  {
    /* Call the Fee_lHandleQsJobFailure with  (FEE_NOT_CANCEL) to notify
    user about failed of job*/
    /* [cover parentID={7A423D5D-41C1-4bf4-AAF8-2B7D036FA8D6}][/cover] */
    Fee_lHandleQsJobFailure((FEE_NOT_CANCEL));
  }
}/*End of Fee_lQsBccWrite */

/*******************************************************************************
** Syntax : static Uint16 Fee_lQsGetBcc(const uint16 Blkindex)                **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  Blkindex    : Block index in configuration table        **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  BCC value which is highest among all the instances      **
** of the QS Block                                                            **
**                                                                            **
** Description : This function will Calculates the highest Bcc value among    **
** the written QS Block instances and returns the value to the caller         **
*******************************************************************************/
/* [cover parentID={91987F5F-298F-4670-A378-51F55A1D71A9}]
Fee_lQsGetBcc
[/cover] */
/* [cover parentID={12B8A107-1CA5-4e91-8A88-C75C44118A34}][/cover] */
static uint16 Fee_lQsGetBcc(const uint16 Blkindex)
{
  Fee_StateDataType    *StateDataPtr;
  Fee_CacheType  *CachePtr;
  Fee_CacheType  *TempCachePtr;
  const Fee_BlockType  *BlkPtr;
  const Fee_BlockType  *TempBlkptr;
  uint16                Instances;
  uint16                Bcc;


  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  /*MISRA2012_RULE_18_1_JUSTIFICATION: Pointer arithmetic other than
        array indexing used for FEE application buffers.
        Pointers are accessing the correct memory range locations.
        The access range is within the boundaries of the buffer. */
  CachePtr = &(StateDataPtr->FeeBlockInfo[Blkindex]);
  TempCachePtr = CachePtr;
  TempBlkptr = &(Fee_CfgPtr->FeeBlockConfigPtr[FEE_QSBLOCK_BEGIN_INDEX]);
  BlkPtr = &(TempBlkptr[(Blkindex - FEE_QSBLOCK_BEGIN_INDEX)]);
  Instances = BlkPtr->Instances;
  /* [cover parentID={E23245F9-8B93-485b-B4F9-F43F7570DAC0}][/cover] */
  while((Instances == FEE_RESET) && (BlkPtr != TempBlkptr))
  {
    BlkPtr--;
    CachePtr--;
    Instances = BlkPtr->Instances;
  }

  Bcc = FEE_RESET;

  /* Block with 1 instance */

  /*MISRA2012_RULE_18_1_JUSTIFICATION: Pointer arithmetic other than array
  indexing used for FEE application buffers.Pointers are accessing the correct
  memory range locations.The access range is within the boundaries of the
  buffer. */
  /* [cover parentID={475BE9FD-FE73-42d1-9A24-AF611E684202}][/cover] */
  if((Instances == FEE_ONE) && \
      (CachePtr->Status.State == FEE_QS_WRITE_STARTED))
  {
    /*MISRA2012_RULE_18_1_JUSTIFICATION: Pointer arithmetic other than
          array indexing used for FEE application buffers.
          Pointers are accessing the correct memory range locations.
          The access range is within the boundaries of the buffer. */
    /* [cover parentID={93877B33-93AB-470c-B46B-6E6D536E5ACE}][/cover] */
    if(CachePtr->Blkcylcnt < FEE_MAX_BCC_QS )
    {
      /*MISRA2012_RULE_18_1_JUSTIFICATION: Pointer arithmetic other than
          array indexing used for FEE application buffers.
          Pointers are accessing the correct memory range locations.
          The access range is within the boundaries of the buffer. */
      CachePtr->Blkcylcnt++;
    }

    /*MISRA2012_RULE_18_1_JUSTIFICATION: Pointer arithmetic other than
          array indexing used for FEE application buffers.
          Pointers are accessing the correct memory range locations.
          The access range is within the boundaries of the buffer. */
    Bcc = CachePtr->Blkcylcnt;
  }
  /* [cover parentID={680965C4-21AE-4125-A577-663B75585824}][/cover] */
  else
  {
    /* Block with more than 1 instance */
    /* [cover parentID={680965C4-21AE-4125-A577-663B75585824}][/cover] */
    while(Instances != FEE_RESET)
    {
      /*MISRA2012_RULE_18_1_JUSTIFICATION: Pointer arithmetic other than
            array indexing used for FEE application buffers.
            Pointers are accessing the correct memory range locations.
            The access range is within the boundaries of the buffer. */
      /* [cover parentID={8F086B08-86B8-4b28-9C1F-6437249269D0}][/cover] */
      if(CachePtr->Status.State == FEE_QS_WRITE_STARTED)
      {
        TempCachePtr = CachePtr;
      }
      /*MISRA2012_RULE_18_1_JUSTIFICATION: Pointer arithmetic other than
            array indexing used for FEE application buffers.
            Pointers are accessing the correct memory range locations.
            The access range is within the boundaries of the buffer. */
      /* [cover parentID={393351FC-C93D-4ce8-9E33-AD8B37B202C9}][/cover] */
      if(CachePtr->Blkcylcnt > Bcc)
      {
        /*MISRA2012_RULE_18_1_JUSTIFICATION: Pointer arithmetic other than
              array indexing used for FEE application buffers.
              Pointers are accessing the correct memory range locations.
              The access range is within the boundaries of the buffer. */
        Bcc = CachePtr->Blkcylcnt;
      }

      /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
            array indexing used for FEE application buffers.
            Pointers are accessing the correct memory range locations.
            The access range is within the boundaries of the buffer. */
      /*MISRA2012_RULE_18_1_JUSTIFICATION: Pointer arithmetic other than
            array indexing used for FEE application buffers.
            Pointers are accessing the correct memory range locations.
            The access range is within the boundaries of the buffer. */
      CachePtr += FEE_ONE;
      Instances--;
    };

    /*Limit the BCC to max*/
    /* [cover parentID={094340D8-FC6D-4d46-AE51-27FBE0555D1F}][/cover] */
    if(Bcc < FEE_MAX_BCC_QS)
    {
      Bcc++;
    }

    /*MISRA2012_RULE_18_1_JUSTIFICATION: Pointer arithmetic other than
          array indexing used for FEE application buffers.
          Pointers are accessing the correct memory range locations.
          The access range is within the boundaries of the buffer. */
    TempCachePtr->Blkcylcnt = Bcc;
  }

  return(Bcc);
}/*End of Fee_lQsGetBcc */

/*******************************************************************************
** Syntax : static void Fee_lQsProgState(void)                                **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Asynchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function Triggers programming of QS Block state         **
** information on D-Flash as per FeeQsState Global Variable                   **
*******************************************************************************/
/* [cover parentID={97D8B4FE-A233-48ab-956D-F8505B433CBB}]
Fee_lQsProgState
[/cover] */
/* [cover parentID={BD786207-9880-4a16-AEBE-31F04A3CD5E2}][/cover] */
static void Fee_lQsProgState(void)
{
  Fee_StateDataType    *StateDataPtr;
  const Fee_BlockType  *TempBlkptr;
  uint32                DestAddr;
  uint32               *SrcAddr;
  uint16                BlkIndex;
  uint32                BlkSize;
  Fls_17_Dmu_LengthType        DataLength;
  Std_ReturnType        RetVal;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  if(StateDataPtr->FeePendReqStatus == FEE_REQ_QUASI_ERASE)
  {
    BlkIndex = StateDataPtr->FeePendEraseInfo.CacheIndex;
  }
  else
  {
    BlkIndex = StateDataPtr->FeePendReqInfo.CacheIndex;
  }

  TempBlkptr = &(Fee_CfgPtr->FeeBlockConfigPtr[BlkIndex]);
  BlkSize = TempBlkptr->Size;
  DestAddr = TempBlkptr->Address +

             (StateDataPtr->FeeQuasiBlkInstanceTemp * BlkSize);
  /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 32 bit
    access and array is memory aligned.*/
  SrcAddr = (uint32 *)(StateDataPtr->FeeReadWriteBuffer);
  DataLength = FEE_DFLASH_PAGE_SIZE;

  switch(StateDataPtr->FeeQsState)
  {
    /* [cover parentID={E577F060-D706-4ed0-85E0-0DADE5DA77DE}][/cover] */
    case (uint8)FEE_QS_PROG_STATE_ERASE_STARTED:
    {
      /* [cover parentID={6583BDB6-3CFB-4e8e-8706-E7EFB657CAE7}][/cover] */
      DestAddr += FEE_QS_STATE_ERASE_STARTED_OFFSET;
      *SrcAddr = FEE_QS_STATE_ERASE_STARTED_LSW;
      SrcAddr[1] = FEE_QS_STATE_ERASE_STARTED_MSW;
      /* [cover parentID={CD256792-4FE8-4c52-85E5-B9FC506D2290}][/cover] */
      StateDataPtr->FeeQsState = (uint8)FEE_QS_PROG_STATE_DESTROY;
      /* [cover parentID={DA9C3CD7-2B96-48e3-B4FC-D449ECAD102F}][/cover] */
      StateDataPtr->FeeBlockInfo[BlkIndex].Status.State =
        FEE_QS_ERASE_STARTED;
      break;
    }
    /* [cover parentID={41DAF54D-52B9-4c9d-BC7C-5F4BA0FEFA9A}][/cover] */
    case (uint8)FEE_QS_PROG_STATE_DESTROY:
    {
      /* [cover parentID={952DCE45-BA21-4b28-BAC4-5C6DEB67E017}][/cover] */
      DataLength = FEE_DFLASH_PAGE_SIZE * FEE_THREE;
      StateDataPtr->FeeQuasiBlkInstanceTemp += FEE_ONE;
      *SrcAddr = FEE_QS_STATE_DESTROY;

      SrcAddr[1] = FEE_QS_STATE_DESTROY;

      SrcAddr[2] = FEE_QS_STATE_DESTROY;

      SrcAddr[3] = FEE_QS_STATE_DESTROY;

      SrcAddr[4] = FEE_QS_STATE_DESTROY;

      SrcAddr[5] = FEE_QS_STATE_DESTROY;
      /* [cover parentID={BE09DD6B-636A-4fad-8258-BF6F47B51E21}][/cover] */
      if(StateDataPtr->FeeQuasiBlkInstanceTemp ==
          StateDataPtr->FeePendEraseInfo.BlockInstances)
      {
        /* [cover parentID={EF5FC75F-BE81-483e-BC2D-1C2715F0745B}][/cover] */
        StateDataPtr->FeeQsState = (uint8)FEE_QS_START_ERASE;
      }
      else
      {
        /* [cover parentID={FD6702CD-198B-4f46-9981-9EBFC466D0C4}][/cover] */
        StateDataPtr->FeeQsState = (uint8)FEE_QS_PROG_STATE_ERASE_STARTED;
      }
      break;
    }
    /* [cover parentID={7E7FAE14-9241-4f97-8D33-3892D559ED02}][/cover] */
    case (uint8)FEE_QS_PROG_STATE_ERASE_COMPLETE:
    {
      /* [cover parentID={D73F1E88-DB98-4638-BF0E-4CC50B84D5CE}][/cover] */
      *SrcAddr = FEE_QS_STATE_ERASE_COMPLETE_LSW;
      SrcAddr[FEE_ONE] = FEE_QS_STATE_ERASE_COMPLETE_MSW;
      StateDataPtr->FeeQuasiBlkInstanceTemp += FEE_ONE;
      if(StateDataPtr->FeeQuasiBlkInstanceTemp ==
          StateDataPtr->FeePendEraseInfo.BlockInstances)
      {
        /* [cover parentID={B61AC29F-AABA-432d-B273-63A251DCED5B}][/cover] */
        StateDataPtr->FeeQsState = (uint8)FEE_QS_ERASE_COMPLETE;
      }
      break;
    }
    /* [cover parentID={A98B26F1-4307-4840-8B6D-E597106209BD}][/cover] */
    case (uint8)FEE_QS_PROG_STATE_WRITE_COMPLETE:
    {
      /* [cover parentID={B630744B-323D-46dd-B666-7CCC9B34923C}][/cover] */
      DestAddr += FEE_QS_STATE_WRITE_COMPLETED_OFFSET;
      *SrcAddr = FEE_QS_STATE_WRITE_COMPLETE_LSW;
      SrcAddr[FEE_ONE] = FEE_QS_STATE_WRITE_COMPLETE_MSW;
      /* [cover parentID={522C8CF1-8FCB-4da0-8EB5-3EB3DB4915DB}][/cover] */
      StateDataPtr->FeeQsState = (uint8)FEE_QS_WRITE_COMPLETE;
      break;
    }
    /* [cover parentID={88DB5DC7-0402-490c-8440-F27DE34C713B}][/cover] */
    case (uint8)FEE_QS_PROG_STATE_WRITE_STARTED:
    {
      /* [cover parentID={18EACC9E-293F-44a4-97A8-2127096E8A46}][/cover] */
      DestAddr += FEE_QS_STATE_WRITE_STARTED_OFFSET;
      *SrcAddr = FEE_QS_STATE_WRITE_STARTED_LSW;
      SrcAddr[FEE_ONE] = FEE_QS_STATE_WRITE_STARTED_MSW;
      /* [cover parentID={302D45A6-6E23-414e-B5D2-529FE38C1229}][/cover] */
      StateDataPtr->FeeQsState = (uint8)FEE_QS_START_BCC_WRITE;
      break;
    }
    default:
    {
      break;
    }
  }

  RetVal = Fls_17_Dmu_Write((Fls_17_Dmu_AddressType)DestAddr, (uint8 *)SrcAddr,
                            DataLength);
  /* [cover parentID={498A7AA1-E622-4277-932C-A806E4FF518F}][/cover] */
  if( RetVal == E_OK)
  {
    StateDataPtr->FeeQsJobStatus = FEE_JOB_REQSTD;
  }
  else
  {
    /* Call the Fee_lHandleQsJobFailure with  (FEE_NOT_CANCEL) to notify
    user about failed of job*/
    Fee_lHandleQsJobFailure((FEE_NOT_CANCEL));
  }
}/*End of Fee_lQsProgState */

/*******************************************************************************
** Syntax : static void Fee_lQsBlockErase(void)                               **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function Triggers Erase of QS Block on D-Flash as per   **
** Block details in pending Request buffer                                    **
*******************************************************************************/
/* [cover parentID={4E00F903-9413-4788-B3B8-2F8B449891C9}]
Fee_lQsBlockErase
[/cover] */
/* [cover parentID={D23FDB2A-69C1-42d3-9C8A-BA047BADB3F8}][/cover] */
static void Fee_lQsBlockErase(void)
{
  Fee_StateDataType     *StateDataPtr;
  const Fee_BlockType   *TempBlkptr;
  uint32                 DestAddr;
  uint16                 BlkIndex;
  uint32                 BlkSize;
  Std_ReturnType         RetVal;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  BlkIndex = StateDataPtr->FeePendEraseInfo.CacheIndex;
  TempBlkptr = &(Fee_CfgPtr->FeeBlockConfigPtr[BlkIndex]);
  BlkSize = TempBlkptr->Size;
  BlkSize = BlkSize * (StateDataPtr->FeePendEraseInfo.BlockInstances);
  DestAddr = TempBlkptr->Address;

  /* erase logical sector */
  RetVal = Fls_17_Dmu_Erase(DestAddr, (Fls_17_Dmu_LengthType)BlkSize);

  /* [cover parentID={67BE7120-986C-43e1-ABA1-1840E6CA0C67}][/cover] */
  if( RetVal == E_OK)
  {
    StateDataPtr->FeeQsJobStatus = FEE_JOB_REQSTD;
    StateDataPtr->FeeQsState = (uint8)FEE_QS_PROG_STATE_ERASE_COMPLETE;
  }
  else
  {
    /* Call the Fee_lHandleQsJobFailure with  (FEE_NOT_CANCEL) to notify
    user about failed of job*/
    /* [cover parentID={8937D7B9-1C69-481e-8755-D0EEF4CD95F3}][/cover] */
    Fee_lHandleQsJobFailure((FEE_NOT_CANCEL));
  }
}/*End of Fee_lQsBlockErase */

/*******************************************************************************
** Syntax : static void Fee_lQsBlockWrite(void)                               **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function Triggers write of QS Block on D-Flash as per   **
** Block details in pending Request buffer                                    **
*******************************************************************************/
/* [cover parentID={A468F0A9-3CD5-4d96-BF03-7AA3FF7A9BF0}][/cover] */
static void Fee_lQsBlockWrite(void)
{
  Fee_StateDataType     *StateDataPtr;
  const Fee_BlockType   *TempBlkptr;
  uint32                 DestAddr;
  const uint32          *SrcAddr;
  uint16                 BlkIndex;
  uint16                 BlkSize;
  Std_ReturnType         RetVal;
  uint16                 PendReqBlkNum;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  PendReqBlkNum = StateDataPtr->FeePendReqInfo.BlockNumber;
  /* [cover parentID={7EC16D76-8BA7-422e-AD22-F325F7E097FD}][/cover] */
  BlkIndex = Fee_lGetUsrBlockIndex(PendReqBlkNum);


  TempBlkptr = &(Fee_CfgPtr->FeeBlockConfigPtr[BlkIndex]);
  BlkSize = (uint16)TempBlkptr->Size;
  BlkSize = BlkSize - (uint16)(FEE_QS_DATA_OFFSET_SECOND_PAGE);
  DestAddr = TempBlkptr->Address + (FEE_QS_DATA_OFFSET_SECOND_PAGE);
  /* [cover parentID={3E900673-9AA8-4412-9E35-9059BC781487}]
  Set writing address to starting data page of block
  [/cover] */
  /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 32 bit
    access and array is memory aligned.*/
  SrcAddr = (const uint32 *)StateDataPtr->FeePendReqInfo.DataWriteBufferPtr;
  /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than array
  indexing used for FEE application buffers.
  Pointers are accessing the correct memory range locations.
  The access range is within the boundaries of the buffer.*/
  SrcAddr += 1;

  /* [cover parentID={E9626BC0-439E-4e6a-AA5C-CD3361CDDD81}]
  Initiate FLS write
  [/cover] */
  /* program logical sector */
  RetVal = Fls_17_Dmu_Write((Fls_17_Dmu_AddressType)DestAddr,
                            (const uint8 *)SrcAddr, BlkSize);

  /* [cover parentID={25A1E92F-37EF-48f3-A7AF-BE0737D8811B}][/cover] */
  if( RetVal == E_OK)
  {
    StateDataPtr->FeeQsJobStatus = FEE_JOB_REQSTD;
    /* [cover parentID={A76A6EDD-A552-4bf0-806D-E17F7B7BE6BE}][/cover] */
    StateDataPtr->FeeQsState = (uint8)FEE_QS_PROG_STATE_WRITE_COMPLETE;
  }
  else
  {
    /* Call the Fee_lHandleQsJobFailure with  (FEE_NOT_CANCEL) to notify
    user about failed of job*/
    /* [cover parentID={35EC12B8-DBCF-4d79-B332-6E87548B7062}][/cover] */
    Fee_lHandleQsJobFailure((FEE_NOT_CANCEL));
  }
}/*End of Fee_lQsBlockWrite */

/*******************************************************************************
** Syntax : static void Fee_lMainQs(void)                                     **
**                                                                            **
** Service ID:                                                                **
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
** Description : This routine is responsible for handling QS Block state      **
**               machine                                                      **
*******************************************************************************/
/*[cover parentID={79707214-F807-47e8-B575-7208309EC646}][/cover]*/
static void Fee_lMainQs(void)
{
  const Fee_StateDataType     *StateDataPtr;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  #if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)

  /* If qs erase job is suspended and there is qs write request then first
  complete write request (FeePendReqStatus = FEE_REQ_QUASI_WRITE) and then
  resume suspended erase job.*/
  /* [cover parentID={41688BD3-7090-4fb1-9668-34A2B637E19B}][/cover] */
  if((StateDataPtr->FeeQsEraseSuspend == FEE_ERASE_SUSPENDED) &&
      (StateDataPtr->FeePendReqStatus == FEE_REQ_QUASI_ERASE))
  {
    Fee_lQsResumeErase();
  }
  else
  #endif
  {
    switch(StateDataPtr->FeeQsJob)
    {
      /* [cover parentID={7B54EC55-2430-4f75-9AA4-73B4CD6B30D6}][/cover] */
      case FEE_READ_JOB:
      {
        Fee_lQsRead();
        break;
      }
      /* [cover parentID={D7DE52AA-7EB0-4f6a-94C3-A91D6A87011B}][/cover] */
      case FEE_WRITE_JOB:
      {
        Fee_lQsWrite();
        break;
      }
      /* [cover parentID={C5D14D29-C4D9-4a9c-8E16-925792B76D37}][/cover] */
      case FEE_ERASE_JOB:
      {
        Fee_lQsErase();
        break;
      }
      default:
      {
        break;
      }
    }
  }
}/*End of Fee_lMainQs */

/*******************************************************************************
** Syntax : static void Fee_lHandleQsJobFailure(void)                         **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function handles the QS job failure occurring due to    **
**               FLS operation failure                                        **
*******************************************************************************/
/*[cover parentID={AE8F8DFA-2242-48d5-9150-45C3A7469B0C}][/cover]*/
static void Fee_lHandleQsJobFailure(const uint8 Error)
{
  Fee_StateDataType     *StateDataPtr;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  #if(FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
  /*Check if QS erase was suspended. If yes then set FeePendReqStatus to
  FEE_REQ_QUASI_ERASE to set module status to busy. If the FeePendReqStatus
  is FEE_REQ_QUASI_ERASE this mean resume failed so set FeePendReqStatus to
  FEE_PEND_PREV_NO_REQ */
  /*[cover parentID={0D695180-FB71-40f9-8DED-1110060B97B5}][/cover]*/
  if((StateDataPtr->FeeQsEraseSuspend == FEE_ERASE_SUSPENDED) &&
      (StateDataPtr->FeePendReqStatus != FEE_REQ_QUASI_ERASE))
  {
    StateDataPtr->FeePendReqStatus = FEE_REQ_QUASI_ERASE;
    StateDataPtr->FeeQsJob = FEE_ERASE_JOB;
  }
  else
  #endif
  {
    StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_NO_REQ;
    StateDataPtr->FeeQsJob = FEE_NO_JOB;
  }
  StateDataPtr->FeeQsState = FEE_QS_IDLE;
  StateDataPtr->FeeQsJobStatus = FEE_JOB_IDLE;
  /*[cover parentID={C1AD6FC2-FE07-42aa-9F80-B6FEA617044F}][/cover]*/
  if( FEE_CANCEL != Error)
  {
      /*[cover parentID={6BB95B02-8281-4751-A8F0-E87884F3CAA0}][/cover]*/
      StateDataPtr->FeeQsJobResult = MEMIF_JOB_FAILED;
  }
  else
  {
    StateDataPtr->FeeQsJobResult = MEMIF_JOB_CANCELED;
  }
  /* Call user configured job Error notification */
  /*[cover parentID={6D5E65F4-FE32-448b-8984-496FEE1BAA06}][/cover]*/
  if( Fee_CfgPtr->FeeQsJobErrorNotification != NULL_PTR )
  {
    /* [cover parentID={F41FCFA0-2BD2-4b1d-9686-AA9314115E08}]
    Call the notification function
    [/cover] */
    (Fee_CfgPtr->FeeQsJobErrorNotification)();
  }
}/*End of Fee_lHandleQsJobFailure */

/*******************************************************************************
** Syntax : static void Fee_lHandleQsJobSuccess(void)                         **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function performs QS global var status update after     **
**               successful completion of QS job operation                    **
*******************************************************************************/
/*[cover parentID={67E2E638-3877-4d78-83AE-E443573796F2}][/cover]*/
static void Fee_lHandleQsJobSuccess(void)
{
  Fee_StateDataType     *StateDataPtr;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  #if(FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
  /*Check if QS erase was suspended. If yes then set FeePendReqStatus to
  FEE_REQ_QUASI_ERASE to set module status to busy.*/
  /*[cover parentID={1ACC7EF7-AA20-4eef-9564-A1B1F48143E9}][/cover]*/
  if(StateDataPtr->FeeQsEraseSuspend == FEE_ERASE_SUSPENDED)
  {
    StateDataPtr->FeePendReqStatus = FEE_REQ_QUASI_ERASE;
    StateDataPtr->FeeQsJob = FEE_ERASE_JOB;
  }
  else
  #endif
  {
    StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_NO_REQ;
    StateDataPtr->FeeQsJob = FEE_NO_JOB;
  }
  StateDataPtr->FeeQsState = FEE_QS_IDLE;
  StateDataPtr->FeeQsJobStatus = FEE_JOB_IDLE;
  StateDataPtr->FeeQsJobResult = MEMIF_JOB_OK;
  /* Call user configured job End notification */
  /*[cover parentID={122CFC2A-B000-40b2-90D3-25115EE72D31}][/cover]*/
  if( Fee_CfgPtr->FeeQsJobEndNotification != NULL_PTR )
  {
    /* [cover parentID={33AE7770-BDD2-44d4-9A6F-3BF930911C40}]
    Call the notification function
    [/cover] */
    (Fee_CfgPtr->FeeQsJobEndNotification)();
  }
}/*End of Fee_lHandleQsJobSuccess */

/*******************************************************************************
** Syntax : static Void Fee_lEvalQsBlockState(Fee_CacheType *const Cacheptr)  **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  Cacheptr    : Pointer to Cache Index                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function will evaluate the Block status and updates     **
**               the Cache accordingly                                        **
*******************************************************************************/
/* [cover parentID={C27E4B8D-6CAB-4633-BABB-828035F78E2A}][/cover]*/
static void Fee_lEvalQsBlockState(Fee_CacheType *const Cacheptr)
{
  Fee_QsBlock_StateType QsBlkWriteStat;
  Fee_QsBlock_StateType QsBlkEraseStat;
  Fee_StateDataType     *StateDataPtr;
  const uint32*          TmpPtr;
  uint32                 Bcc;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* [cover parentID={3DD47090-004E-438f-9A72-1E50B98BB70B}][/cover]*/
  if(Fee_lEvalQsBlockVirginStatus() == E_OK)
  {
    StateDataPtr->FeeQsBlockVirginCount += FEE_ONE;
  }
  else
  {
    /* [cover parentID={979B2982-B1F1-4306-83B1-8B7C5899FEBD}][/cover]*/
    QsBlkWriteStat = Fee_lEvalQsBlockWriteStatus();

    /* [cover parentID={514D8932-9669-4e4c-AED6-4148420D3BA2}][/cover]*/
    QsBlkEraseStat = Fee_lEvalQsBlockEraseStatus();

    Cacheptr->Status.State = FEE_QS_INVALID;

    /* [cover parentID={E66852F5-941E-471f-A1CE-B670695B5351}][/cover]*/
    if(QsBlkEraseStat != FEE_QS_INVALID)
    {
      /* [cover parentID={D9ACD96F-8799-4c07-86F1-EF5FBEEFB806}][/cover]*/
      if(QsBlkEraseStat == FEE_QS_DIRTY_ERASE)
      {
        Cacheptr->Status.QsDirtyErase = FEE_SET ;
      }
      Cacheptr->Status.State = FEE_QS_ERASE_COMPLETE;
    }
    /* [cover parentID={768B9D11-0533-4046-892B-35D9FEFCC124}][/cover]*/
    if(QsBlkWriteStat != FEE_QS_INVALID)
    {
      /* [cover parentID={5CB7C7A7-0308-40f4-BF5B-3C5C0E21DBD3}][/cover]*/
      if(QsBlkWriteStat == FEE_QS_DIRTY_WRITE)
      {
        Cacheptr->Status.QsDirtyWrite = FEE_SET ;
        Cacheptr->Status.State = FEE_QS_WRITE_COMPLETE;
      }
      else
      {
        Cacheptr->Status.State = QsBlkWriteStat;
      }

      /* Read the block cycle count from read write buffer and update it
      into cache.*/

      /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform
      32 bit access and array is memory aligned.*/
      TmpPtr = (uint32 *)(StateDataPtr->FeeReadWriteBuffer);
      Bcc = ((TmpPtr[FEE_EIGHT]) & FEE_16_BIT_ALL_ONES);
      Cacheptr->Blkcylcnt = (uint16) Bcc;
    }
  }

}/*End of Fee_lEvalQsBlockState */


/*******************************************************************************
** Syntax : static Std_ReturnType Fee_lEvalQsBlockVirginStatus(void)          **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                    E_OK: Block is virgin                                   **
**                    E_NOT_OK : Block is not virgin                          **
** Description : This function will evaluate the Block  virgin status.        **
** all the state page and block cycle count is check for all 0 bits           **
*******************************************************************************/
/* [cover parentID={24F506EE-F27A-4813-B18B-86DD5823289B}]
Fee_lEvalQsBlockVirginStatus
[/cover] */
/* [cover parentID={C72851B7-B43E-4410-876A-22A34ACA17E8}][/cover]*/
static Std_ReturnType Fee_lEvalQsBlockVirginStatus(void)
{

  const Fee_StateDataType     *StateDataPtr;
  Std_ReturnType        RetVal;
  const uint32*         TmpPtr;
  uint8                 Index;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 32 bit
    access and array is memory aligned.*/
  TmpPtr = (const uint32 *)(StateDataPtr->FeeReadWriteBuffer);

  RetVal = E_OK;
  /*Check the all status pages for zero.In single iteration half page is checked
   */
  /* [cover parentID={CDA7A812-F359-4a6a-A907-BA6714EE4A4E}][/cover]*/
  for(Index = FEE_RESET ; Index < (FEE_QS_STATUS_PAGES + FEE_QS_STATUS_PAGES) ;
      Index++ )
  {
    if(TmpPtr[Index] != FEE_RESET )
    {
      RetVal = E_NOT_OK;
      break;
    }
  }

  return(RetVal);
}/*End of Fee_lEvalQsBlockVirginStatus */

/*******************************************************************************
** Syntax : Fee_lHandleQsVirginBlocks(void)                                   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                    E_OK: Block is virgin                                   **
**                    E_NOT_OK : Block is not virgin                          **
** Description : This function will write Erase complete state marker as part **
** Qs virgin blocks handling only if enabled otherwise triggers the qs        **
** illegal notification.                                                      **
*******************************************************************************/
/* [cover parentID={FAF5624C-FAC7-4d71-B111-2B5DE2F2EAB8},
{1D9DB568-A982-4a59-86B1-DC1395215AED}]
Fee_lHandleQsVirginBlocks
[/cover] */
static void Fee_lHandleQsVirginBlocks(void)
{

  Fee_StateDataType   *StateDataPtr;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  #if (FEE_VIRGIN_FLASH_ILLEGAL_STATE == STD_OFF)
  Fee_CacheType       *CachePtr;
  uint32*              SrcPtr;
  uint32               DestAddr;
  Std_ReturnType        RetVal;

  CachePtr = &(StateDataPtr->FeeBlockInfo[StateDataPtr->FeeQsRepairIndex +
                                                     FEE_QSBLOCK_BEGIN_INDEX]);
  /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 32 bit
    access and array is memory aligned.*/

  SrcPtr = (uint32 *)(StateDataPtr->FeeReadWriteBuffer);

  SrcPtr[0] = FEE_QS_STATE_ERASE_COMPLETE_LSW;
  SrcPtr[1] = FEE_QS_STATE_ERASE_COMPLETE_MSW;

  /* [cover parentID={6DD1AD7A-3CB1-490b-B2C6-4FFC50876CE1}][/cover]*/
  if((StateDataPtr->FeeQsIntrJobStatus == FEE_JOB_IDLE) &&
      (StateDataPtr->FeeQsIntrJobResult == MEMIF_JOB_OK))
  {
    /* Check if all the qs blocks are marked as erase complete */
    /* [cover parentID={010ACA16-0316-4048-AF96-CBB667AEC50E}][/cover]*/
    if(StateDataPtr->FeeQsRepairIndex < FEE_NUM_QUASI_BLOCKS)
    {
      DestAddr = CachePtr->Address;
      RetVal = Fls_17_Dmu_Write((Fls_17_Dmu_AddressType)DestAddr,
                                (uint8 *)SrcPtr, FEE_DFLASH_PAGE_SIZE);
      /* [cover parentID={8D3E8BC7-B124-4355-ADA6-DBA3407720A0}][/cover]*/
      if( RetVal == E_OK)
      {
        CachePtr->Status.QsDirtyErase = 0;
        CachePtr->Status.QsDirtyWrite = 0;
        CachePtr->Status.State = FEE_QS_ERASE_COMPLETE;
        StateDataPtr->FeeQsRepairIndex ++ ;
        StateDataPtr->FeeQsIntrJobStatus = FEE_JOB_REQSTD;
      }
      else
      {
        if(Fee_CfgPtr->FeeQsIllegalStateNotification != NULL_PTR)
        {
          Fee_CfgPtr->FeeQsIllegalStateNotification();
        }
        StateDataPtr->FeeQsIntrJob = FEE_NO_JOB;
        StateDataPtr->FeeInitQSState = FEE_INITQS_COMPLETE;
      }
    }
    else
    {
      StateDataPtr->FeeQsIntrJob = FEE_NO_JOB;
      StateDataPtr->FeeInitQSState = FEE_INITQS_COMPLETE;
    }
  }
  else
  #endif
  {
    /* [cover parentID={1FE91F7B-76AD-408e-A85E-49CA3EC844EB}][/cover]*/
    if(Fee_CfgPtr->FeeQsIllegalStateNotification != NULL_PTR)
    {
      /* [cover parentID={2DDC7E87-0F90-4da4-902C-32E470176197}][/cover]*/
      Fee_CfgPtr->FeeQsIllegalStateNotification();
    }
    StateDataPtr->FeeQsIntrJob = FEE_NO_JOB;
    StateDataPtr->FeeInitQSState = FEE_INITQS_COMPLETE;
  }
}


/*******************************************************************************
** Syntax : static Fee_QsBlock_StateType Fee_lEvalQsBlockEraseStatus(void)    **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  QS Block erase state in DFlash                          **
**                 FEE_QS_INVALID : Block erase state is not valid            **
**                 FEE_QS_ERASE_COMPLETE : Block erase state is erase         **
**                 completed                                                  **
**                 FEE_QS_DIRTY_ERASE : Block erase state is erase            **
**                 dirty, block erase is not completed                        **
** Description : This function will evaluate the Block erase completion status**
*******************************************************************************/
/* [cover parentID={D24EF183-AB87-403a-9257-39F9C40DAF23}][/cover] */
static Fee_QsBlock_StateType Fee_lEvalQsBlockEraseStatus(void)
{
  const Fee_StateDataType     *StateDataPtr;
  Fee_QsBlock_StateType RetVal;
  uint32                TempData;
  uint32                Bcc;
  const uint32*         TmpPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 32 bit
    access and array is memory aligned.*/
  TmpPtr = (const uint32 *)(StateDataPtr->FeeReadWriteBuffer);

  Bcc = TmpPtr[(FEE_QS_STATE_CYCLE_COUNT_OFFSET / FEE_DFLASH_WORD_SIZE)] &
        FEE_32_BIT_ALL_ONES;
  RetVal = FEE_QS_INVALID;
  TempData = (TmpPtr[FEE_TWO])  | (TmpPtr[FEE_THREE]) | (TmpPtr[FEE_FOUR]) |
             (TmpPtr[FEE_FIVE]) | (TmpPtr[FEE_SIX])   | (TmpPtr[FEE_SEVEN]);

  /* [cover parentID={58CA199F-25DB-4c73-AEC1-DEB4307A9F84}][/cover] */
  /* [cover parentID={EF5EBF79-2B4C-4ce2-8744-2CE129BB263D}][/cover] */
  if(TempData == FEE_RESET)
  {
    /* [cover parentID={7339DDB0-032B-499d-BB81-88FE0628FF7B}][/cover] */
    if(Bcc == FEE_RESET)
    {
      /* [cover parentID={3ED30284-D369-45ea-AF5C-B73AD1B6389F}][/cover] */
      if((*(TmpPtr) == FEE_QS_STATE_ERASE_COMPLETE_LSW) &&
          (TmpPtr[FEE_ONE] == FEE_QS_STATE_ERASE_COMPLETE_MSW))
      {
        RetVal = FEE_QS_ERASE_COMPLETE;
      }
      /* [cover parentID={F2615C5F-6938-4226-8171-3720FDC439D3}][/cover] */
      else if( (*(TmpPtr) | (TmpPtr[FEE_ONE])) != FEE_RESET)
      {
        RetVal = FEE_QS_DIRTY_ERASE;
      }
      else
      {
        /* To avoid misra warning */
      }
    }
  }

  return(RetVal);
}/*End of Fee_lEvalQsBlockEraseStatus */

/*******************************************************************************
** Syntax : static Fee_QsBlock_StateType Fee_lEvalQsBlockWriteStatus(void)    **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  QS Block write state in DFlash                          **
**                                                                            **
** Description : This function will evaluate the Block write completion status**
*******************************************************************************/
/* [cover parentID={C5B2318A-8DC2-4021-ACB4-18BC916B177B}][/cover] */
static Fee_QsBlock_StateType Fee_lEvalQsBlockWriteStatus(void)
{
  const Fee_StateDataType     *StateDataPtr;
  Fee_QsBlock_StateType  RetVal;
  uint32                 Bcc;
  uint32                 Bcc_Comp;
  const uint32*          TmpPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  /*MISRA2012_RULE_11_3_JUSTIFICATION:The casting is needed to perform 32 bit
    access and array is memory aligned.*/
  TmpPtr = (const uint32 *)(StateDataPtr->FeeReadWriteBuffer);

  Bcc = ((TmpPtr[FEE_EIGHT]) & FEE_16_BIT_ALL_ONES);
  Bcc_Comp = (((TmpPtr[FEE_EIGHT]) >> FEE_SIXTEEN) &
              FEE_16_BIT_ALL_ONES);

  RetVal = FEE_QS_INVALID;

  /* FEE_QS_STATE_DFERASE_STATE is also checked to handle power failure
   * during virgin flash preparation. */
  /* [cover parentID={3458CCEC-7B5E-48c5-A18A-6CEDA2B6BFB6}][/cover] */
  if(((*TmpPtr == FEE_QS_STATE_ERASE_COMPLETE_LSW) &&

      ((TmpPtr[FEE_ONE]) == FEE_QS_STATE_ERASE_COMPLETE_MSW))
      || (*TmpPtr == FEE_QS_STATE_DFERASE_STATE))
  {
    /* [cover parentID={2CE7DEFA-F665-4099-9E88-6C21BE818455}][/cover] */
    if(((TmpPtr[FEE_TWO]) == FEE_QS_STATE_WRITE_STARTED_LSW) &&

        ((TmpPtr[FEE_THREE]) == FEE_QS_STATE_WRITE_STARTED_MSW))
    {
      /* [cover parentID={AB38C3B5-738F-462f-ACD6-6702F70EA2EB}][/cover] */
      if(((TmpPtr[FEE_SIX]) | (TmpPtr[FEE_SEVEN])) == FEE_RESET)
      {
        /* [cover parentID={33501AC0-53DA-4393-BAE9-767A7D36AEFA}][/cover] */
        if(Bcc == (~Bcc_Comp & FEE_16_BIT_ALL_ONES))
        {
          /* [cover parentID={61AFB626-5566-4967-B146-68CDF63763BB}][/cover] */
          if(((TmpPtr[FEE_FOUR]) == FEE_QS_STATE_WRITE_COMPLETE_LSW) &&
              ((TmpPtr[FEE_FIVE]) == FEE_QS_STATE_WRITE_COMPLETE_MSW))
          {
            RetVal = FEE_QS_WRITE_COMPLETE;
          }
          /* [cover parentID={48E266F7-C641-4e05-A7A1-9AAEE4789DC5}][/cover] */
          else if(((TmpPtr[FEE_FOUR]) | (TmpPtr[FEE_FIVE])) == FEE_RESET)
          {
            RetVal = FEE_QS_WRITE_STARTED;

          }
          else
          {
            RetVal = FEE_QS_DIRTY_WRITE;
          }
        }
      }
    }
  }
  return(RetVal);
}/*End of Fee_lEvalQsBlockWriteStatus */

/*******************************************************************************
** Syntax : static Void Fee_lQsIDSM(void)                                     **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function will repair QS Blocks which are identified     **
**               in Init as Dirty                                             **
*******************************************************************************/
/* [cover parentID={81DD7816-C7F3-4c48-BE2B-9C7601A2A086},
{34019D92-D6C9-4d4e-ABEE-808DA8F12A11}]
Check for QS job status
[/cover] */
static void Fee_lQsIDSM(void)
{
  Fee_StateDataType    *StateDataPtr;
  uint32                BlkAddr;
  Fee_CacheType  *CachePtr;
  Std_ReturnType        RetVal;
  Std_ReturnType        TempRetVal;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  CachePtr = &(StateDataPtr->FeeBlockInfo[StateDataPtr->FeeQsRepairIndex +
                                                      FEE_QSBLOCK_BEGIN_INDEX]);
  StateDataPtr->FeeTempArray[0] = FEE_QS_STATE_WRITE_COMPLETE_LSW;
  StateDataPtr->FeeTempArray[1] = FEE_QS_STATE_WRITE_COMPLETE_MSW;
  TempRetVal = E_OK;
  BlkAddr = CachePtr->Address;

  /* [cover parentID={81DD7816-C7F3-4c48-BE2B-9C7601A2A086}][/cover] */
  if((StateDataPtr->FeeQsIntrJobStatus == FEE_JOB_IDLE) &&
      (StateDataPtr->FeeQsIntrJobResult == MEMIF_JOB_FAILED))
  {
    /*Repair of the block is failed mark the block status as invalid and reset
    block cylce count in cache.*/
    CachePtr->Status.State = FEE_QS_INVALID;
    CachePtr->Blkcylcnt = FEE_RESET;
  }

  /* [cover parentID={D8CA4C26-1560-410d-9F31-B9E67FC17E46}][/cover] */
  while((StateDataPtr->FeeQsRepairIndex < FEE_NUM_QUASI_BLOCKS) &&
        (TempRetVal == E_OK))
  {
    /* [cover parentID={EB3CB513-6A56-4fde-86A2-E9178936C6FB}][/cover] */
    if(CachePtr->Status.QsDirtyErase == (uint32)FEE_SET)
    {
      BlkAddr = CachePtr->Address;
      /* reset the Dirty Status */
      CachePtr->Status.QsDirtyErase = FEE_RESET;
      TempRetVal = E_NOT_OK;
    }
    /* [cover parentID={24C01888-4FA2-4839-A29F-5B7B6DAB0E6A}][/cover] */
    else if(CachePtr->Status.QsDirtyWrite == (uint32)FEE_SET)
    {
      BlkAddr = CachePtr->Address + FEE_QS_STATE_WRITE_COMPLETED_OFFSET;
      /* reset the Dirty Status */
      CachePtr->Status.QsDirtyWrite = FEE_RESET;
      TempRetVal = E_NOT_OK;
    }
    else
    {
      StateDataPtr->FeeQsRepairIndex++;
      CachePtr++;
    }
    /* [cover parentID={9E24E043-305F-44cc-A1B8-19ED987CDB75}][/cover] */
    if(TempRetVal == E_NOT_OK)
    {
      /* program logical sector */
      RetVal = Fls_17_Dmu_Write((Fls_17_Dmu_AddressType)BlkAddr,
                                (uint8 *)(StateDataPtr->FeeTempArray),
                                FEE_DFLASH_PAGE_SIZE);
      /* [cover parentID={47A31ADB-5A52-4129-98D7-83C4FB3C7D6D}][/cover] */
      if(RetVal == E_OK)
      {
        StateDataPtr->FeeQsIntrJobStatus = FEE_JOB_REQSTD;
      }
      else
      {
        /*Repair of the block is failed mark the block as invalid.Continue the
        repair of other blocks*/
        CachePtr->Status.State = FEE_QS_INVALID;
        TempRetVal = E_OK;
      }
    }
  }
  /* [cover parentID={7D17CE2F-E195-4327-830D-FDDFFFC85354}][/cover] */
  if(StateDataPtr->FeeQsRepairIndex == FEE_NUM_QUASI_BLOCKS)
  {
    StateDataPtr->FeeQsIntrJob = FEE_NO_JOB;
    StateDataPtr->FeeInitQSState = FEE_INITQS_COMPLETE;
  }
}/*End of Fee_lQsIDSM */

/*******************************************************************************
** Syntax : static Void Fee_lMainQsTransHdlr(void)                            **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function Performs the state transition for the main     **
**               function when in FEE_MAIN_QS state                           **
*******************************************************************************/
/* [cover parentID={8A30F525-7D54-4ae2-AB57-874F22227E25}][/cover] */
static void Fee_lMainQsTransHdlr(void)
{
  Fee_StateDataType    *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* [cover parentID={AF2AAA97-24A1-4cad-BDBB-46313E6E8615}][/cover] */
  if(StateDataPtr->FeePendReqStatus == FEE_PEND_PREV_NO_REQ)
  {

    #if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
    /* [cover parentID={99EDFFF5-44BC-48d4-910E-8C9A5883FA52}][/cover] */
    if(((boolean)FALSE == Fee_lIsGcTriggeredOnce(StateDataPtr)) &&
        (StateDataPtr->FeeGcState != FEE_GC_IDLE))
    {
      StateDataPtr->FeeMainJob = FEE_MAIN_GC;
    }
    else
    #endif
    {
      StateDataPtr->FeeMainJob = FEE_MAIN_NONE;
    }
  }

  #if (FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)
  /*Check for NVM write after QS write*/
  /* [cover parentID={43E95990-7658-4d61-AAF2-FC7F24F08C5A}][/cover] */
  else if( (boolean)TRUE == Fee_lIsUserWriteInvldReqstd(StateDataPtr) )
  {
    #if (FEE_CANCELL_ALL_API == STD_ON)
    /* Switch to main none to Check if there is GC cancelled by cancel all */
    StateDataPtr->FeeMainJob = FEE_MAIN_NONE;

    #else
    StateDataPtr->FeeMainJob = FEE_MAIN_WRITE;
    #endif

  }

  #endif


  #if (FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)
  /*Check for NVM read after QS write*/
  /* [cover parentID={A6C476F9-5144-471b-94C1-4D1A792F1E49}][/cover] */
  else if( (boolean)TRUE == Fee_lIsUserReadReqstd(StateDataPtr) )
  {
    #if (FEE_CANCELL_ALL_API == STD_ON)

    /* Switch to main none to Check if there is GC cancelled by cancel all */

    StateDataPtr->FeeMainJob = FEE_MAIN_NONE;

    #else
    StateDataPtr->FeeMainJob = FEE_MAIN_READ;
    #endif
  }
  else
  {
    /* To aviod misra warning */
  }

  #endif
}/*End of Fee_lMainQsTransHdlr */

#if (FEE_CANCELL_ALL_API == STD_ON) && \
    (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
/*******************************************************************************
** Traceability   : [cover parentID={910989B6-08AC-4a55-9E86-1BE2C74C6FAC}]   **
**                                                                            **
** Syntax : void Fee_17_CancelAll (void)                                      **
**                                                                            **
** Service ID: 0x28                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  void                                                    **
**                                                                            **
** Description : Service to cancel any ongoing Internal/User read or write    **
** job. However, ongoing erase cannot be cancelled.                           **
*******************************************************************************/
/* [cover parentID={7C10DE66-A21A-47db-8A13-D456A64C30B2}]
Fee_17_CancelAll
[/cover] */
void Fee_17_CancelAll(void)
{

  MemIf_StatusType   FeeStatus;

  /* [cover parentID={BC39E052-0028-4c12-851B-8B5724774BA5}]
  Safety error is enabled
  [/cover] */
  #if(FEE_SAFETY_ENABLE == STD_ON)

  /*Check for configuration pointer(Fee_CfgPtr)for null as part safety check */
  /* Check if the Fee_Init API is called */

  /* [cover parentID={9215E9C4-C1AF-42b7-B5B1-D70924A5D6F5}]
  Is the configuration pointer NULL?
  [/cover] */
  if(Fee_CfgPtr != NULL_PTR)

  #endif
  {
    #if(MCAL_AR_VERSION == MCAL_AR_440)
    /* [cover parentID={9F0B85C6-6F76-4c06-A29A-5D9321027C33}]
    Is driver initialization is complete
    [/cover] */
    if(Fee_lGetStatus() != MEMIF_UNINIT)
    #endif
    {
      /* [cover parentID={FE83D752-5E24-4d57-8348-62C72A9EFC7B}]
      Get Fee status
      [/cover] */
      FeeStatus = Fee_lGetStatus();
      /*any internal or User job ongoing*/
      /* [cover parentID={14E0C734-498B-4a77-B86F-404F91446F1C}]
      Is Fee busy?
      [/cover] */
      #if((MCAL_AR_VERSION == MCAL_AR_440) && \
      (FEE_DATA_BLOCK_SUPPORTED == FEE_QUASI_STATIC_DATA_ONLY))
      if(FeeStatus == MEMIF_BUSY)
      #else
      if((FeeStatus == MEMIF_BUSY_INTERNAL) || (FeeStatus == MEMIF_BUSY))
      #endif
      {
        /* [cover parentID={BCE9C3B0-AFD8-4536-8FAC-A19693551C59}]
        Cancel the ongoing job
        [/cover] */

        Fee_lCancelAll();
      }
      /* [cover parentID={F77E1C4F-6258-4a9c-B0E8-8D73015FA394}]
      Safety is enabled
      [/cover] */
      #if((FEE_SAFETY_ENABLE == STD_ON) && (MCAL_AR_VERSION == MCAL_AR_422)) \
      || (FEE_RUNTIME_ERROR_DETECT == STD_ON)
      else
      { /* [cover parentID={4E0263ED-0EDF-4276-8B16-636C7999B44E}]
        Report error as FEE_E_INVALID_CANCEL
        [/cover] */
        #if(MCAL_AR_VERSION == MCAL_AR_422) && (FEE_SAFETY_ENABLE == STD_ON)
        Fee_lReportError(FEE_SID_CANCELALL,
                        FEE_SE_INVALID_CANCEL, FEE_SAFETY_ERROR);
        #elif(FEE_RUNTIME_ERROR_DETECT == STD_ON)
        Fee_lReportError(FEE_SID_CANCELALL,
                      FEE_E_INVALID_CANCEL, FEE_RUNTIME_ERROR);
        #endif
      }
      #endif
    }
    #if(FEE_SAFETY_ENABLE == STD_ON) && (MCAL_AR_VERSION == MCAL_AR_440)
    else
    {
    Fee_lReportError(FEE_SID_CANCELALL,
                        FEE_SE_UNINIT, FEE_SAFETY_ERROR);
    }
    #endif
  }
  #if(FEE_SAFETY_ENABLE == STD_ON)
  else
  {
    /* [cover parentID={7CF34432-255A-4503-BE86-4D3FC9CA3328}]
    Report error as FEE_E_UNINIT
    [/cover] */
    Fee_lReportError(FEE_SID_CANCELALL,
                        FEE_SE_UNINIT, FEE_SAFETY_ERROR);
  }
  #endif

}
#endif

/*CYCLOMATIC_Fee_lCancelAll_JUSTIFICATION: Fee_lCancelAll has
to determine all the states of ongoing operation and then cancel.
It broken properly into various stages using switch case which cannot be broken
further. If it is broken into more functions to fix RSM, the code readability
will get affected.
*/
/*******************************************************************************
** Syntax : void Fee_lCancelAll(void)                                         **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function Performs the cancellation of ongoing           **
**               Fee Job operation including GC.                              **
*******************************************************************************/
#if (FEE_CANCELL_ALL_API == STD_ON) && \
    (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
/* [cover parentID={41BC93C6-486B-45f8-A095-EF6CFF2E1828},
{07F854EA-9B94-4496-8129-90F411D55A37}]
Fee_lCancelAll
[/cover] */
static void Fee_lCancelAll (void)
{

  #if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
  Fee_StateDataType     *StateDataPtr;
  uint8                  CancelGC = FEE_RESET;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  #endif

  Fee_lCancelallUsrJob();

  #if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)

  /* remember : before exit, there cannot be any pending jobs.
     We should be in some kind of an idle state so that new jobs
   can be accepted. This is a good test case */

  switch(StateDataPtr->FeeGcState)
  {
    /* [cover parentID={B3EC74A6-3DC9-4908-992A-42CC930AA265}][/cover] */
    case FEE_GC_IDLE:
    {
      CancelGC = FEE_RESET;
      break;
    }
    /* [cover parentID={5238C7C3-0B93-47e4-BD6F-E082849FF9A0}][/cover] */
    case FEE_GC_ERASE_PREV_SECTOR:
    case FEE_GC_INIT_ERASE_PREV_SECTOR:
    {
      if(StateDataPtr->FeeIntrJobStatus == FEE_JOB_IDLE)
      {
        CancelGC = FEE_SET;
      }
      else
      {
        CancelGC = FEE_RESET;
      }
      break;
    }
    /* [cover parentID={5270F94A-78B2-4073-B908-027D4422D7F2}][/cover] */
    case FEE_GC_REQUESTED:
    case FEE_GC_UNCFG_START_COPY:
    case FEE_GC_START_COPY:
    case FEE_GC_UNCFG_COPY_READ_NXTPAGE:
    case FEE_GC_COPY_READ_NXTPAGE:
    case FEE_GC_UNCFG_COPY_WRITE:
    case FEE_GC_COPY_WRITE:
    case FEE_GC_MARK_SECTOR1_V_SP:
    case FEE_GC_MARK_SECTOR1_V_M:
    case FEE_GC_MARK_SECTOR0_E_SP:
    case FEE_GC_MARK_SECTOR0_E_M:
    case FEE_GC_INIT_MARK_SECTOR0_E_SP:
    case FEE_GC_INIT_MARK_SECTOR0_E_M:
    {
      CancelGC = FEE_SET;
      break;
    }
    default:
    {
      break;
    }
  }
  if(CancelGC == FEE_SET)
  {
    Fee_lCancelWrite();
    StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_NO_REQ;
    StateDataPtr->FeeIntrJobStatus = FEE_JOB_IDLE;
    StateDataPtr->FeeIntrJobResult = (uint8)MEMIF_JOB_CANCELED;
    StateDataPtr->FeeIntrJob = FEE_NO_JOB;
    StateDataPtr->FeeGcState = FEE_GC_IDLE;
    /*Set  FeeCancelallGCstate to FEE_GC_CANCLD notify GC is cancelled by
    cancel all */
    StateDataPtr->FeeCancelallGCstate = FEE_GC_CANCLD;

  }

  #endif


}/*End of Fee_lCancelAll */

/* [cover parentID={78B27194-6B4F-4f02-A743-DF15FB3A0ABC}][/cover] */
/*******************************************************************************
** Syntax : void Fee_lCancelallUsrJob(void)                                   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function Performs the cancellation of ongoing           **
**               Fee Read/Write/Erase/QS Job operations                       **
*******************************************************************************/
LOCAL_INLINE void Fee_lCancelallUsrJob (void)
{
  const Fee_StateDataType     *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  switch(StateDataPtr->FeePendReqStatus)
  {


    #if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
    /* there was a write/read request registered only */
    /* [cover parentID={EBC1B4FE-0565-493a-8AC9-35B3B16F8F31}][/cover] */
    case FEE_REQ_IMM_WRITE:
    case FEE_REQ_NORM_WRITE:
    case FEE_REQ_READ:
    case FEE_PEND_PREV_READ_REQ:
    case FEE_PEND_PREV_READ_NOTIF:
    {
      /* Is any job requested to Fls, if yes then cancel the job.
      notification will be triggered to user by fee_job_error notification.*/
      /* [cover parentID={C00C587E-2B81-42b5-9544-4239E5E0B5CE}][/cover] */
      if(StateDataPtr->FeeUserJobStatus == FEE_JOB_REQSTD)
      {

        Fls_17_Dmu_Cancel();
      }
      else
      {
        /* Call the Fee_lHandleUsrJobFailure with  FEE_CANCEL to notify
        user about cancelled of job*/
        Fee_lHandleUsrJobFailure(FEE_CANCEL);
      }
      break;
    }
    /* write ongoing when this was called */
    case FEE_PEND_PREV_COMPARE:
    case FEE_PEND_INTR_COMPARE:
    {
      /* cancel ongoing write*/
      Fee_lCancelWrite();

      break;
    }
    #endif
    /* [cover parentID={AA0A51E4-135A-4287-8BA5-205DE27BC54A}][/cover] */
    case FEE_REQ_QUASI_WRITE:
    case FEE_REQ_QUASI_READ:
    case FEE_REQ_QUASI_ERASE:
    {

      Fee_lCancelallUsrJobQs();
      break;
    }
    default:
    {
      /*Do nothing*/

      /*The QS erase job can not be canceled */
      break;
    }
  }
}

/*[cover parentID={DCE7DD89-3680-4d19-88AB-61665F9A352A}][/cover]*/
/*******************************************************************************
** Syntax : void Fee_lCancelallUsrJobQs(void)                                   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function Performs the cancellation of ongoing           **
**               Fee QS Job operations                                        **
*******************************************************************************/
LOCAL_INLINE void Fee_lCancelallUsrJobQs (void)
{
  const Fee_StateDataType     *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  if(StateDataPtr->FeeQsJobStatus == FEE_JOB_REQSTD)
  {
    /* [cover parentID={C3A4EA11-C6AA-4536-917F-B3D316EF67D5}][/cover] */
    if(StateDataPtr->FeePendReqStatus == FEE_REQ_QUASI_ERASE)
    {
      /* Only cancel the fls write request in qs erase job. fls Erase
      request can not be canceled */
      /* [cover parentID={2396205A-CA03-4ce6-8D4B-11026CE473CA}][/cover] */
      if((StateDataPtr->FeeQuasiBlkInstanceTemp != FEE_ZERO) &&
          (StateDataPtr->FeeQsState != (uint8)FEE_QS_PROG_STATE_ERASE_COMPLETE))
      {
        Fls_17_Dmu_Cancel();
      }

    }
    /* [cover parentID={EBE1BD17-FD8C-4648-A7D6-DCC3924108A2}][/cover] */
    else
    {
      Fls_17_Dmu_Cancel();
    }

  }
  else
  {
    /* Call the Fee_lHandleQsJobFailure with  FEE_CANCEL to notify
    user about cancelled of job*/
    Fee_lHandleQsJobFailure(FEE_CANCEL);
  }
}
#endif

/* [cover parentID={DDA2DC38-6BEC-43ec-9880-430191057143}]
FEE_CANCELL_ALL_API enabled and QS data block supported
[/cover] */
#if (FEE_CANCELL_ALL_API == STD_ON) && \
    (FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)

/*******************************************************************************
** Syntax : void Fee_lCancelAllGCrestart(void)                                **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function Performs reset of sector info and will build   **
**               DFLASH and Set fee main to INITGC state.                     **
*******************************************************************************/
/* [cover parentID={527D5B4B-3905-4e54-8C05-6BE15D26C6C0}][/cover]*/
/* [cover parentID={5C98842C-4860-420e-A769-AEF76C955E93}][/cover]*/
static void Fee_lCancelAllGCrestart(void)
{


  Fee_StateDataType     *StateDataPtr;
  Fee_SectorInfoType    *SectorInfoPtr;
  uint32 Index;
  uint32 EndAddr;
  uint8  DFlashStatus;
  uint8  ReturnVal;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  SectorInfoPtr = StateDataPtr->FeeSectorInfo;
  /* Initialize Sector State information */
  /* [cover parentID={681C42AF-3C8D-474d-AFAF-0B7263548A1D}][/cover]*/
  for(Index = FEE_RESET; Index < FEE_SECTORS; Index++)
  {
    SectorInfoPtr[Index].State = FEE_RESET;
    SectorInfoPtr[Index].StateCount = FEE_RESET;
    SectorInfoPtr[Index].UnerasableWLCount = FEE_RESET;
    SectorInfoPtr[Index].UnerasableWLAddr[0] = FEE_RESET;
    SectorInfoPtr[Index].UnerasableWLAddr[1] = FEE_RESET;
    SectorInfoPtr[Index].Status.Dirty = FEE_RESET;
    SectorInfoPtr[Index].Status.Used = FEE_RESET;
    SectorInfoPtr[Index].StatePageAddr = FEE_RESET;
    SectorInfoPtr[Index].NextFreeWLAddr = FEE_RESET;
    SectorInfoPtr[Index].NonZeroWLCount = FEE_RESET;
    SectorInfoPtr[Index].NonZeroWLAddr[0] = FEE_RESET;
    SectorInfoPtr[Index].NonZeroWLAddr[1] = FEE_RESET;
  }

  StateDataPtr->FeeStateCount = FEE_RESET;
  StateDataPtr->FeeSectorCount = FEE_RESET;
  StateDataPtr->FeeComparedLen = FEE_RESET;
  StateDataPtr->FeeReadLen = FEE_RESET;
  StateDataPtr->FeeUnErasableWLAddrTemp[0] = FEE_RESET;
  StateDataPtr->FeeUnErasableWLAddrTemp[1] = FEE_RESET;
  StateDataPtr->FeeUnErasableWLCountTemp = FEE_RESET;

  /* Read sector information */
  /* [cover parentID={AB1BF9B5-6288-4be9-9D10-5F4B2DDA1C38}][/cover]*/
  /*Clear the fee read/write buffer*/
  Fee_lClearFeeReadWriteBuffer();
  for(Index = FEE_RESET; Index < FEE_SECTORS; Index++)
  {
    if(Index == FEE_RESET)
    {
      EndAddr = FEE_DFLASH_BANK0_BASE;
    }
    else
    {
      EndAddr = FEE_DFLASH_BANK1_BASE;
    }
    StateDataPtr->FeeCurrSectSrcAddr = EndAddr +
                                       (FEE_DFLASH_SECTOR_SIZE -
                                        FEE_DFLASH_WORDLINE_SIZE);
    do
    {
      ReturnVal = Fee_lGetSectorInfo(Index, EndAddr);
    } while(ReturnVal == FEE_SP_INIT);
  }

  DFlashStatus = Fee_lBuildDFlashStatus();

  /* Set the init GC state*/
  Fee_lSetInitGc(DFlashStatus);

}

#endif

#if (FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)
/*******************************************************************************
** Syntax : static void Fee_lGcHardenQsSector(void)                           **
**                                                                            **
** Service ID:                                                                **
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
** Description : This function Checks and performs Hardening operation on     **
** part of QS region                                                          **
*******************************************************************************/
/* [cover parentID={3D1C82A1-9719-4283-9359-A662A4B1A3C0}][/cover] */
/* [cover parentID={50DEDDB6-4A9A-4f26-B9C5-5EDBAAE36268}][/cover] */
static void Fee_lGcHardenQsSector(void)
{

  Fee_StateDataType   *StateDataPtr;
  Std_ReturnType       ReturnValue;
  uint8          *ReadWriteBuffPtr;
  Fls_17_Dmu_AddressType      Addr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  /* [cover parentID={37DF76E2-AA08-4cf3-B25D-57DAF4D129B1}][/cover] */
  if (StateDataPtr->FeeIntrJobStatus == FEE_JOB_DONE)
  {
    StateDataPtr->FeeIntrJobStatus = FEE_JOB_IDLE;
    StateDataPtr->FeeProgVerErr = FEE_RESET;
    /* [cover parentID={D3192FBC-AC5C-4d1f-87AC-9C948DD7A560}][/cover]*/
    if(StateDataPtr->FeeIntrJobResult == FEE_JOB_FAIL)
    {
      /* [cover parentID={9729EC09-099B-463e-A28F-24169C9B39A8}][/cover]*/
      /* Error is encountered while write operation as part of hardening
      switch GC state to erase previous sector state. */
      if(Fee_CfgPtr->FeeQsHardenErrorNotification != NULL_PTR)
      {
        /* [cover parentID={9729EC09-099B-463e-A28F-24169C9B39A8}]
        Call QS harden error notification (provided the notification function is configured)
        [/cover] */
        Fee_CfgPtr->FeeQsHardenErrorNotification();
      }
    }
  }

  /*This function checks if hardening is required or not with the help
  of Fls functionality and returns the page address where hardening is to
  be done. If hardening is not required, 0xFFFFFFFF will be obtained   */
  /* [cover parentID={7CDEEE63-E167-46f0-BC43-22C57A4D553F}][/cover]*/
  Addr = Fee_lGcHardenReqChk();

  /* [cover parentID={D25EF027-791F-4988-9EB2-EE25186122D2}][/cover]*/
  if(FEE_NO_HARDEN_RET_ADDRESS  != Addr)
  {
    /* [cover parentID={39DB863C-C2E8-4ccc-8967-FAF339519FED}]*/
    ReadWriteBuffPtr = StateDataPtr->FeeGcReadWriteBuffer;
    /* [cover parentID={39DB863C-C2E8-4ccc-8967-FAF339519FED}]
    Read word data from flash bank synchronously
    [/cover] */
    /*MISRA2012_RULE_11_3_JUSTIFICATION:This is done for interfacing with
      FLS.FEE is passing parameters to FLS APIs, casting is needed to match with
      the Fls API prototype.*/
    ReturnValue = Fls_17_Dmu_ReadWordsSync(Addr, (uint32 *)ReadWriteBuffPtr,
                                 (FEE_DFLASH_PAGE_SIZE / FEE_DFLASH_WORD_SIZE));
    /* [cover parentID={C8B57ABB-441A-42a9-9D3A-C6F05EBE473A}][/cover]*/
    if(E_NOT_OK == ReturnValue)
    {
      /* [cover parentID={C53A6B1C-22A9-4bfc-8EDA-E5F4C877AA24}][/cover]*/
      if(Fee_CfgPtr->FeeQsHardenErrorNotification != NULL_PTR)
      {
        /* [cover parentID={C53A6B1C-22A9-4bfc-8EDA-E5F4C877AA24}]
        Call QS harden error notification (provided the notification function is configured)
        [/cover] */
        /* Error is encountered while performing reading as
        part of hardening operation. */
        Fee_CfgPtr->FeeQsHardenErrorNotification();
      }
    }
    else
    {
      /* [cover parentID={48325974-6780-4ff4-AE8F-C79D90CAFFBA}][/cover]*/
      ReturnValue = Fls_17_Dmu_Write(Addr, ReadWriteBuffPtr,
                                     FEE_DFLASH_PAGE_SIZE);
      /* [cover parentID={708E7A39-6303-458c-BC8A-57728DBDA3D6}][/cover]*/
      if(E_NOT_OK == ReturnValue)
      {
        if(Fee_CfgPtr->FeeQsHardenErrorNotification != NULL_PTR)
        {
          /* Error is encountered while requesting write
          operation as part of hardening. */
          Fee_CfgPtr->FeeQsHardenErrorNotification();
        }
      }
      else
      {
        StateDataPtr->FeeIntrJobStatus = FEE_JOB_REQSTD;
        StateDataPtr->FeeIntrJob = FEE_WRITE_JOB;
      }
    }
  }

  return;

}/*End of Fee_lGcHardenQsSector */

/*CYCLOMATIC_Fee_lGcHardenReqChk_JUSTIFICATION:
  In this function, address of the wordline or address of the corresponding
  page is calculated.Further splitting (though it might not be a logical
  decomposition) would mean, these address calculations
  have to be repeated again in the split function or introduce new global static
  variables to handle the scenario.
*/
/*******************************************************************************
** Syntax : static Fls_17_Dmu_AddressType Fee_lGcHardenReqChk(void)           **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function checks whether hardening is required or not    **
** with the help of Fls functionality                                         **
*******************************************************************************/
/* [cover parentID={B0AA15C8-97E3-4ea0-A4B5-52E2E59A3F50}][/cover] */
/* [cover parentID={EE9701FA-E837-4066-AB85-E206AD830E5C}][/cover] */
static Fls_17_Dmu_AddressType Fee_lGcHardenReqChk(void)
{
  Fee_StateDataType   *StateDataPtr;
  uint8 RetPageChk = FEE_HARDEN_NOT_REQRD;
  uint8 RetWLChk = FEE_HARDEN_NOT_REQRD;
  uint8 HardeningRateReached = 0U;
  Fls_17_Dmu_AddressType      PageAddr;
  Fls_17_Dmu_AddressType      WLAddr;
  Fls_17_Dmu_AddressType      RetAddrToBeHardened;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  RetAddrToBeHardened = FEE_NO_HARDEN_RET_ADDRESS;
  do
  {
    /*Check if the hardening check and hardening is completed for the required
    portion of QS area */
    /* [cover parentID={7CE49723-D12B-4930-9F35-2189B9C9E365}][/cover] */
    if(FEE_HARDENING_RATE == StateDataPtr->FeeHardeningWLCount)
    {
      if(StateDataPtr->FeeQsHardeningOffset <
         ((FEE_DFLASH_QS_SIZE / FEE_DFLASH_WORDLINE_SIZE) - FEE_HARDENING_RATE))
      {
        /* This offset is stored in the state page so that Hardening check can
        be started from this address of the QS area in the next GC */
        StateDataPtr->FeeQsHardeningOffset += FEE_HARDENING_RATE;
      }
      else
      {
        StateDataPtr->FeeQsHardeningOffset = FEE_RESET;
      }
      StateDataPtr->FeeHardeningWLCount = FEE_RESET;
      HardeningRateReached = 1U ;
      /* Since Hardening is completed for the required portion, GC state is
       switched to erase previous sector state. */
      StateDataPtr->FeeGcState = FEE_GC_ERASE_PREV_SECTOR;
    }
    else
    {
      /* Word line Address is calculated for which Hardening check is to be done.
        Offset address is passed here as Fls driver adds this offset to the
        DFlash base address*/
      WLAddr = ((((StateDataPtr->FeeQsHardeningOffset  +
                StateDataPtr->FeeHardeningWLCount) * (FEE_DFLASH_WORDLINE_SIZE))
               + FEE_QS_SECTOR_BASE) - FLS_17_DMU_BASE_ADDRESS);
      /*if Hardening page count is 0, it means hardening check
        is to be done at fresh/new word line */
      if (0U == StateDataPtr->FeeHardeningPageCount)
      {
        /* [cover parentID={608FEC0D-CC01-40c8-9646-B3CFB7D12A73}]
        Call FLS function to find out whether hardening is required for fresh
        word line or not
        [/cover] */
        /*Check for Hardening required or not at Wordline level granularity */
        RetWLChk = Fls_17_Dmu_IsHardeningRequired(WLAddr, FEE_HARDEN_CHK_WL);
      }
      /*if Hardening page count is not 0, it means hardening check
      is to be done at page level. Also this is done to find which page is to be
      checked for Hardening for the wordline which requires Hardening */
      /* [cover parentID={DDC4947C-119C-49aa-B56A-B766A6158625}][/cover] */
      if ((FEE_HARDEN_REQRD == RetWLChk) ||
          (0U != StateDataPtr->FeeHardeningPageCount))
      {
        do
        {
          /*Page address is calculated for which Hardening check is
           to be done.*/
          PageAddr = WLAddr + (StateDataPtr->FeeHardeningPageCount * FEE_DFLASH_PAGE_SIZE);
          /*Check for Hardening required or not at Page level granularity */
          /* [cover parentID={DF166E2A-8968-4e0f-83ED-5695A39D5D8F}][/cover] */
          RetPageChk = Fls_17_Dmu_IsHardeningRequired(PageAddr,FEE_HARDEN_CHK_PAGE);
          /* [cover parentID={E0A3EAF7-2662-44f7-AC9F-ED1D8857C6E4}][/cover] */
          if (FEE_HARDEN_REQ_ERROR == RetPageChk)
          {
            if(Fee_CfgPtr->FeeQsHardenErrorNotification != NULL_PTR)
            {
              Fee_CfgPtr->FeeQsHardenErrorNotification();
            }
          }
          /* [cover parentID={910F0835-14B5-435a-BAB6-36D48F695624}][/cover] */
          if (FEE_HARDEN_REQRD == RetPageChk)
          {
            /* Page address for which hardening is to be done is returned  */
            RetAddrToBeHardened = PageAddr;
          }
          /*If Hardening check is not required for this page or if the
          Hardening check API from Fls encounters any error, then the check
          is continued for the remaining pages*/
          StateDataPtr->FeeHardeningPageCount += 1U;
        }
    /* [cover parentID={FAF1DAF5-9928-4217-8160-0585DE0BA446}][/cover] */
        while((FEE_HARDEN_REQRD != RetPageChk) &&
              (StateDataPtr->FeeHardeningPageCount < FEE_PAGES_IN_WL));
        if (FEE_PAGES_IN_WL == StateDataPtr->FeeHardeningPageCount)
        {
          /* Hardening page count is reset to 0 if it reaches maximum count.
          This reset is needed to arrive at the correct calculation of the
          corresponding page address of the Wordline if hardening had to be done
          for one or more pages in that word line  */
          StateDataPtr->FeeHardeningPageCount = 0U;
          /* 64 pages in the word line are checked for Hardening, hence move to
          next wordline */
          StateDataPtr->FeeHardeningWLCount += 1U;
        }
      }
      /* [cover parentID={E43329EF-3037-445e-9002-4A57AA8D9F9B}][/cover] */
      else if (FEE_HARDEN_REQ_ERROR == RetWLChk)
      {
        if(Fee_CfgPtr->FeeQsHardenErrorNotification != NULL_PTR)
        {
          Fee_CfgPtr->FeeQsHardenErrorNotification();
        }
        /*If Hardening check API from Fls encounters any error, then the check
            is continued for the remaining Word lines after raising the
            HardenErrorNotification */
        StateDataPtr->FeeHardeningWLCount += 1U;
      }
      else
      {
        /*If Hardening check is not required for this Word line then the check
            is continued for the remaining word lines*/
        StateDataPtr->FeeHardeningWLCount += 1U;
      }
    }
  } while((FEE_HARDEN_REQRD  != RetPageChk) && (FEE_HARDEN_REQRD  != RetWLChk)
        && (FEE_RESET == HardeningRateReached));

  return (RetAddrToBeHardened);
}

#endif
#endif

#if (((FEE_CANCELL_ALL_API == STD_ON) && \
    (FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA))|| \
    ((FEE_ONGOING_WRITE_CANCEL_SUPPORT == STD_ON)&& \
    (FEE_DATA_BLOCK_SUPPORTED !=  FEE_QUASI_STATIC_DATA_ONLY)))
/*******************************************************************************
** Syntax : static void Fee_lCancelWrite (void)                               **
**                                                                            **
** Service ID: NA                                                             **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : Performs canceling of ongoing write operation and resets     **
**               job status variables                                         **
*******************************************************************************/
/* [cover parentID={4C58F967-ACB1-4990-8787-235646670441}]
Fee_lCancelWrite
[/cover] */
/* [cover parentID={443D4D30-33BD-41a5-86A5-2C4254B7CCBE}][/cover]*/
/* [cover parentID={7E52A5B0-3BEB-4661-9C62-FCF287129FE1}][/cover]*/
static void Fee_lCancelWrite(void)
{
  /* [cover parentID={4C58F967-ACB1-4990-8787-235646670441}][/cover]*/
  /* [cover parentID={DDA2DC38-6BEC-43ec-9880-430191057143}][/cover]*/
  #if (FEE_CANCELL_ALL_API == STD_ON) && \
    (FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)
  Fls_17_Dmu_Job_Type RetVal;
  #endif
  Fee_StateDataType  *StateDataPtr;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  
  /*Checking Switches for avoiding compilation warning*/ 
  #if (FEE_CANCELL_ALL_API == STD_ON) && \
    (FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)  
  /* [cover parentID={7C3FB0C4-1039-4148-872C-5DD84F746ECE}][/cover]*/
  RetVal = Fee_lGetUserJob(StateDataPtr->FeePendReqStatus);
  if(RetVal == FEE_NO_JOB)
  {
    /* GC is cancelled check if there is any request to FLS. If yes then cancel
     the request. GC will be restarted by next NVM read/write request.*/
    /* [cover parentID={EB387ED5-E11A-4e26-8E26-BB95B4EABDDD}][/cover]*/
    if( StateDataPtr->FeeIntrJobStatus == FEE_JOB_REQSTD)
    {
      /* Cancel ongoing FLS request */
      Fls_17_Dmu_Cancel();
    }

  }
  /*User write job is cancelled check if there is any request to FLS.
  If yes then cancel the request. */
  /* [cover parentID={79352954-3AB5-4f2a-9306-7842D408EBE4}][/cover]*/
  else if(StateDataPtr->FeeUserJobStatus == FEE_JOB_REQSTD)
  {
  #else
  if(StateDataPtr->FeeUserJobStatus == FEE_JOB_REQSTD)
  { 
  #endif    
    /* NVM job error notification will be triggered by fee_error notification
    called by FLS when job is cancel*/
    Fls_17_Dmu_Cancel();
  }
  else
  {
    /* write job is cancelled then increase free page address to next
    but one WL. This will avoid write on same page for next write job.
    Also trigger NVM job error notification */

    Fee_lHandleUsrJobFailure(FEE_CANCEL);
    StateDataPtr->FeeNextFreePageAddr += StateDataPtr->FeeLastWriteSize;
    StateDataPtr->FeeNextFreePageAddr = Fee_lGetNextWLAddr(
                                          StateDataPtr->FeeNextFreePageAddr);
    StateDataPtr->FeeNextFreePageAddr += FEE_DFLASH_WORDLINE_SIZE;
  }
}
#endif

#if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON) \
  || (FEE_RUNTIME_ERROR_DETECT == STD_ON)
/*******************************************************************************
** Syntax :  static void Fee_lReportError(uint8 ApiId,uint8 ErrorId)          **
**                                                                            **
**                                                                            **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Ssynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : (uint8) ApiId   - Service id of the caller API           **
**                   (uint8) ErrorId - ID of the error to be reported         **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
** Description : Function to report Safety Error and DET                      **
*******************************************************************************/
/* [cover parentID={25435F35-A888-4723-B287-226507149FDF}][/cover] */
static void Fee_lReportError(uint8 ApiId, uint8 ErrorId, uint8 ErrorType)
{
  /* [cover parentID={83E19753-FDEB-4992-814C-2E0E46A7B40B}]
  DET enabled
  [/cover] */
  #if (FEE_DEV_ERROR_DETECT == STD_ON) || (FEE_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={55DF4E78-B193-4f4e-BAE1-53C7F0488E20}]
  Error type is DET safety
  [/cover] */
  if(ErrorType == FEE_DET_SAFETY_ERROR)
  {
  #if (FEE_DEV_ERROR_DETECT == STD_ON)
    /* [cover parentID={619A9DAB-D6AA-4ab0-9BD8-5B4D6045C873}]
    Call DET reporting with FEE_MODULE_ID, FEE_INSTANCE_ID, ApiId, ErrorId
    [/cover] */
    (void)Det_ReportError(FEE_MODULE_ID, FEE_INSTANCE_ID, ApiId, ErrorId);
  #endif
  #if (FEE_SAFETY_ENABLE == STD_ON)
      Mcal_ReportSafetyError(FEE_MODULE_ID, FEE_INSTANCE_ID, ApiId,
                         ErrorId);
  #endif
  }
  #endif
  /* [cover parentID={12098A7C-2D7F-47dd-98E6-31801ADEEECF}]
  Safety enabled
  [/cover] */
  #if (FEE_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={6B9905AC-07E5-4c3f-9D36-A631CDB2011C}]
  Error type is safety
  [/cover] */
  if(ErrorType == FEE_SAFETY_ERROR)
  {
    /* [cover parentID={B17C4A42-EAA9-4623-B004-81338746ACB4}]
    Reporting Safety Error, calling with FEE_MODULE_ID, FEE_INSTANCE_ID, ApiId, ErrorId
    [/cover] */
    Mcal_ReportSafetyError(FEE_MODULE_ID, FEE_INSTANCE_ID, ApiId,
                         ErrorId);
  }
  #endif

  #if (FEE_RUNTIME_ERROR_DETECT == STD_ON)
  /* [cover parentID={B5DF54A6-714A-47fd-93E1-B2455C1FF0FB}]
  Error type is runtime
  [/cover] */
  if(ErrorType == FEE_RUNTIME_ERROR)
  {
    /* [cover parentID={2F27C3DA-07F9-494a-ABEA-D3BFBF9D4A21}]
    Error report runtime error
    [/cover] */
    (void)Mcal_Wrapper_Det_ReportRuntimeError(FEE_MODULE_ID, FEE_INSTANCE_ID, ApiId, ErrorId);
  }
  #endif

} /*End of Fee_lReportError*/
#endif
#if (FEE_DEV_ERROR_DETECT == STD_ON)|| (FEE_SAFETY_ENABLE == STD_ON)
/******************************************************************************
** Syntax : LOCAL_INLINE Std_ReturnType Fee_lReadDetSafetyCheck(const uint16 **
**            BlockNumber,                                                   **
**            const uint16 BlockOffset,                                      **
**            const uint8 *const DataBufferPtr,                              **
**            const uint16 Length,                                           **
**            uint8 ApiId)                                                   **
**                                                                           **
**                                                                           **
**                                                                           **
** Service ID:                                                               **
**                                                                           **
** Sync/Async:  Synchronous                                                  **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in) :  BlockNumber - Logical Block Number                     **
**                    BlockOffset - Read address offset inside the block     **
**                    DataBufferPtr - Pointer to data buffer                 **
**                    Length - Number of bytes to read                       **
**                    ApiId   - Service id of the caller API                 **
**                                                                           **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    :  Std_ReturnType                                         **
**                    E_OK: Check Pass                                       **
**                    E_NOT_OK: Check Fail                                   **
** Description : Function will check the input parameters of read api.       **
** if parameters are not in valid range it will trigger DET/Safety Error     **
** and return E_NOT_OK                                                       **
******************************************************************************/
/* [cover parentID={23ABBD8D-A68F-4aaf-AE18-F48AB2807A4D}][/cover] */
LOCAL_INLINE Std_ReturnType Fee_lReadDetSafetyCheck(const uint16 BlockNumber,
    const uint16 BlockOffset,
    const uint8 *const DataBufferPtr,
    const uint16 Length,
    uint8 ApiId)
{

  uint16               BlkIdx;
  Std_ReturnType       ReturnValue;
  uint32               BlkSize;

  ReturnValue = E_OK;

  BlkIdx = Fee_lGetUsrBlockIndex(BlockNumber);

  /* If BlockNumber exists in the user configuration and is within range */
  /* [cover parentID={A5AA4B8D-E468-40c9-84F7-C2D8B158E3F7}][/cover] */
  if (BlkIdx == FEE_LOG_BLOCK_NOT_FOUND)
  {
    /* [cover parentID={ECA67BD8-EE6E-4430-ACA3-48B5E6C73DF7}]
    Call FEE_E_INVALID_BLOCK_NO DET
    [/cover] */
    Fee_lReportError( ApiId, FEE_E_INVALID_BLOCK_NO, FEE_DET_SAFETY_ERROR);

    /* [cover parentID={08827D4A-F03C-4c07-8B21-1A66B88D2E9B}]
    Set Flag as E_NOT_OK
    [/cover] */
    ReturnValue = E_NOT_OK;
  }
  else
  {

    BlkSize = Fee_CfgPtr->FeeBlockConfigPtr[BlkIdx].Size;

    #if(FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)

    if(Fee_CfgPtr->FeeBlockConfigPtr[BlkIdx].FeeUser ==
        (uint8)FEE_QUASI_STATIC_USER)
    {
      BlkSize = (BlkSize - (uint32)FEE_QS_DATA_OFFSET);
    }

    #endif

    /* Check if the offset is valid i.e. within the block size */
    /* [cover parentID={BE1BD7E2-7232-44b7-8398-827D58F459AC}][/cover] */
    if ((uint32)BlockOffset >= BlkSize)
    {
      /* [cover parentID={AD7C84D9-5CEB-4117-BE53-311BACA9A2BA}][/cover] */
      Fee_lReportError(ApiId, FEE_E_INVALID_BLOCK_OFS, FEE_DET_SAFETY_ERROR);
      ReturnValue = E_NOT_OK;
    }
    /* Check if the buffer pointer is non-NULL */
    /* [cover parentID={FB8055D1-97F4-4119-B92B-1ED00A492EEB}][/cover] */
    else if (DataBufferPtr == (uint8*) NULL_PTR)
    {
      /* [cover parentID={8F216F9D-8347-4daf-85DB-47B00524726E}]
      Call FEE_E_PARAM_POINTER DET
      [/cover] */
      Fee_lReportError(ApiId, FEE_E_PARAM_POINTER, FEE_DET_SAFETY_ERROR);

      ReturnValue = E_NOT_OK;
    }

    /* Check if the Length (from the given offset) is valid */
    /* [cover parentID={264D8497-F461-4c65-A096-9C2B89F19780}][/cover] */
    else if ( ((uint32)BlockOffset + Length) > BlkSize )
    {
      /* [cover parentID={E2D729FE-30D6-44a7-A6B7-FD2B03DBBB7F}]
      Call FEE_E_INVALID_BLOCK_LEN DET
      [/cover] */
      Fee_lReportError(ApiId, FEE_E_INVALID_BLOCK_LEN, FEE_DET_SAFETY_ERROR);
      /* [cover parentID={322440D0-572D-4143-B13B-D5EEC76BB78D}][/cover] */
      ReturnValue = E_NOT_OK;
    }
    else
    {
      /* dummy else */
    }
  }
  return(ReturnValue);

} /*End of Fee_lReadDetSafetyCheck*/
#endif
#if((FEE_RUNTIME_ERROR_DETECT == STD_ON) || \
  (((FEE_SAFETY_ENABLE == STD_ON) || (FEE_DEV_ERROR_DETECT == STD_ON)) && \
  (MCAL_AR_VERSION == MCAL_AR_422)))
/******************************************************************************
** Syntax : LOCAL_INLINE Std_ReturnType Fee_lCancelDetSafetyCheck(void)      **
**                                                                           **
**                                                                           **
**                                                                           **
** Service ID:                                                               **
**                                                                           **
** Sync/Async:  Synchronous                                                 **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in) :  None                                                   **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    :  Std_ReturnType                                         **
**                    E_OK: Check Pass                                       **
**                    E_NOT_OK: Check Fail                                   **
** Description : Function will check configuration pointer against the null  **
** and module status. if check fails it will trigger DET/Safety Error and    **
** return E_NOT_OK                                                           **
******************************************************************************/
/*[cover parentID={DEE5A0C3-3D9A-4d4a-8649-C7FFA0F0C5BD}][/cover]*/
LOCAL_INLINE Std_ReturnType Fee_lCancelDetSafetyCheck(void)
{
  MemIf_StatusType   FeeStatus;
  Std_ReturnType     ReturnValue;

  ReturnValue = E_OK;
  FeeStatus = Fee_lGetStatus();
  /*[cover parentID={4356B03D-1BA3-4189-BC05-4949CC3AC244}][/cover]*/
  if(FeeStatus != MEMIF_BUSY)
  {
    /*[cover parentID={372A760A-5C83-4ca1-82E4-293444E9D91B}][/cover]*/
    #if(MCAL_AR_VERSION == MCAL_AR_440)
    /* [cover parentID={7AEE303F-4415-4486-9022-D1393EDAD51B}]
    Report runtime error FEE_E_INVALID_CANCEL
    [/cover] */
    Fee_lReportError(FEE_SID_CANCEL, FEE_E_INVALID_CANCEL, FEE_RUNTIME_ERROR);
    #else
    Fee_lReportError(FEE_SID_CANCEL, FEE_E_INVALID_CANCEL, FEE_DET_SAFETY_ERROR);
    #endif
    ReturnValue = E_NOT_OK;
  }
  return(ReturnValue);
} /*End of Fee_lCancelDetSafetyCheck*/

#endif

/******************************************************************************
** Syntax : LOCAL_INLINE Std_ReturnType Fee_lInitSafetyCheck(void)           **
**                                                                           **
**                                                                           **
**                                                                           **
** Service ID:                                                               **
**                                                                           **
** Sync/Async:  Synchronous                                                 **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in) :  API: Service id of the caller API                      **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    :  Std_ReturnType                                         **
**                    E_OK: Check Pass                                       **
**                    E_NOT_OK: Check Fail                                   **
** Description : Check for the initialization of the driver and report error **
**               enabled.                                                    **
******************************************************************************/
/* [cover parentID={7EF79FAD-36AE-4efb-8E68-EF4B20DDA6C9}][/cover] */
LOCAL_INLINE Std_ReturnType Fee_lInitSafetyCheck(const uint8 ApiId)
{
  /* [cover parentID={9B9284EF-B93F-4723-B585-B9E49F305EF4}]
  Set return value as E_NOT_OK
  [/cover] */
  Std_ReturnType RetVal = E_NOT_OK;

  #if(FEE_DEV_ERROR_DETECT != STD_ON) && (FEE_SAFETY_ENABLE != STD_ON)
  UNUSED_PARAMETER (ApiId);
  #endif

  /* [cover parentID={5E0BA685-3A9F-46f8-8244-1DC917CC7FE5}]
  Is configuration pointer is null?
  [/cover] */
  if(Fee_CfgPtr != NULL_PTR)
  {
    #if(MCAL_AR_VERSION == MCAL_AR_440)
    /* [cover parentID={0B31F784-2D1C-4fc0-B42D-E5D011FD9B83}]
    Is Driver initialization is complete?
    [/cover] */
    if(Fee_lGetStatus() != MEMIF_UNINIT)
    #endif
    {
      RetVal = E_OK;
    }
    #if((FEE_DEV_ERROR_DETECT == STD_ON) || (FEE_SAFETY_ENABLE == STD_ON))\
    && (MCAL_AR_VERSION == MCAL_AR_440)
    else
    {
      Fee_lReportError(ApiId, FEE_E_UNINIT, FEE_DET_SAFETY_ERROR);
    }
    #endif
  }
  #if(FEE_DEV_ERROR_DETECT == STD_ON) || (FEE_SAFETY_ENABLE == STD_ON)
  else
  {
    /* [cover parentID={B24EE8C3-E059-4468-9BB4-D69FE0406250}]
    Report Det safety error FEE_E_UNINIT
    [/cover] */
    Fee_lReportError(ApiId, FEE_E_UNINIT, FEE_DET_SAFETY_ERROR);
  }
  #endif
  return RetVal;
}

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
/******************************************************************************
** Syntax : LOCAL_INLINE Std_ReturnType Fee_lEraseQsDataSafetycheck(void)    **
**                                                                           **
**                                                                           **
**                                                                           **
** Service ID:                                                               **
**                                                                           **
** Sync/Async:  Synchronous                                                 **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in) :  None                      **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    :  Std_ReturnType                                         **
**                    E_OK: Check Pass                                       **
**                    E_NOT_OK: Check Fail                                   **
** Description : Check for the initialization and busy status of the driver  **
**               and report error if enabled                                 **
**               enabled.                                                    **
******************************************************************************/
/* [cover parentID={96CBCDEB-1881-4162-8C39-DB234820A1B8}][/cover] */
LOCAL_INLINE Std_ReturnType Fee_lEraseQsDataSafetycheck()
{
  Std_ReturnType RetVal = E_NOT_OK;
  const Fee_StateDataType  *StateDataPtr;

  #if (FEE_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={2A3B66A6-384F-461e-BE03-E25290A7DCF6}]
  Is configuration pointer is not NULL?
  [/cover] */
  if(Fee_CfgPtr != NULL_PTR)
  #endif
  {
    #if(MCAL_AR_VERSION == MCAL_AR_440)
    /* [cover parentID={693C2374-18EC-4e7d-9181-571EBEEAAB4D}]
    Is driver initialization is complete
    [/cover] */
    if(Fee_lGetStatus() != MEMIF_UNINIT)
    #endif
    {
      StateDataPtr = Fee_CfgPtr->FeeStatePtr;
        #if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
        /* [cover parentID={0F32ADB1-8044-438e-AC1F-C9012E4481EC}]
        If GC is not idle or pending request exsists?
        [/cover] */
        if(( StateDataPtr->FeePendReqStatus == FEE_PEND_PREV_NO_REQ ) &&
            ( StateDataPtr->FeeGcState == FEE_GC_IDLE))
        #else
        /* [cover parentID={AA1C0DFA-1AC2-4e16-BC19-428DAE3BE8CF}]
        Is perivious request pending?
        [/cover] */
        if(StateDataPtr->FeePendReqStatus == FEE_PEND_PREV_NO_REQ )
        #endif
        {
          RetVal = E_OK;
        }
        #if ((FEE_SAFETY_ENABLE == STD_ON)) \
         || (FEE_RUNTIME_ERROR_DETECT == STD_ON)
        else
        {
        #if (FEE_DATA_BLOCK_SUPPORTED == FEE_QUASI_STATIC_DATA_ONLY)
          #if (MCAL_AR_VERSION == MCAL_AR_422)
          Fee_lReportError(FEE_SID_ERASEQUASISTATICDATA,
                              FEE_SE_BUSY, FEE_SAFETY_ERROR);
          #else
          Fee_lReportError(FEE_SID_ERASEQUASISTATICDATA,
                              FEE_E_BUSY, FEE_RUNTIME_ERROR);
          #endif
          #else
          if(StateDataPtr->FeePendReqStatus != FEE_PEND_PREV_NO_REQ )
          {
            #if (MCAL_AR_VERSION == MCAL_AR_422)
            Fee_lReportError(FEE_SID_ERASEQUASISTATICDATA,
                                FEE_SE_BUSY, FEE_SAFETY_ERROR);
            #else
            Fee_lReportError(FEE_SID_ERASEQUASISTATICDATA,
                              FEE_E_BUSY, FEE_RUNTIME_ERROR);
            #endif
          }
          #endif
        }
        #endif
    }
    #if(FEE_SAFETY_ENABLE == STD_ON) && (MCAL_AR_VERSION == MCAL_AR_440)
    else
    {
      Fee_lReportError(FEE_SID_ERASEQUASISTATICDATA,
                            FEE_SE_UNINIT, FEE_SAFETY_ERROR);
    }
    #endif
  }
  #if (FEE_SAFETY_ENABLE == STD_ON)
  else
  {
    Fee_lReportError(FEE_SID_ERASEQUASISTATICDATA,
                          FEE_SE_UNINIT, FEE_SAFETY_ERROR);
  }
  #endif
  return RetVal;
}
#endif

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
/******************************************************************************
** Syntax : LOCAL_INLINE Std_ReturnType Fee_lQsBlkInfoSafetyCheck            **
**             (const Fee_QuasiStaticBlockInfoType * const BlockInfoPtr)     **
**                                                                           **
**                                                                           **
** Service ID:                                                               **
**                                                                           **
** Sync/Async:  Synchronous                                                 **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in) :  BlockInfoPtr: Block information pointer                **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    :  Std_ReturnType                                         **
**                    E_OK: Check Pass                                       **
**                    E_NOT_OK: Check Fail                                   **
** Description : The function check for the initialization and the null      **
**               pointer check, report error if enabled.                     **
******************************************************************************/
/* [cover parentID={FB12060E-7F0F-46d2-91D5-751DDC199AB0}][/cover] */
LOCAL_INLINE Std_ReturnType Fee_lQsBlkInfoSafetyCheck
      (const Fee_QuasiStaticBlockInfoType * const BlockInfoPtr)
{
  Std_ReturnType RetVal = E_NOT_OK;
  const Fee_StateDataType  *StateDataPtr;

  #if (FEE_SAFETY_ENABLE != STD_ON)
  UNUSED_PARAMETER (BlockInfoPtr);
  #endif

  #if (FEE_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={72458822-6450-460f-9D78-7466AB1EB6A8}]
  CfgPtr is NULL or block information pointer is NULL?
  [/cover] */
  if((Fee_CfgPtr != NULL_PTR) && (BlockInfoPtr != NULL_PTR))
  #endif
  {
    StateDataPtr = Fee_CfgPtr->FeeStatePtr;
    #if(MCAL_AR_VERSION == MCAL_AR_440)
    /* [cover parentID={5F458C76-38B1-4c44-B4F7-EF79BBD7D3C6}]
    Is driver initialization is complete
    [/cover] */
    if(Fee_lGetStatus() != MEMIF_UNINIT)
    #endif
    {
      /* [cover parentID={210F32A1-192F-452a-8873-F4A1E65C4444}]
        Is driver busy
      [/cover] */
      #if(MCAL_AR_VERSION == MCAL_AR_422)
      if((StateDataPtr->FeeInitQSState == FEE_INITQS_COMPLETE)  && \
          ( StateDataPtr->FeePendReqStatus == FEE_PEND_PREV_NO_REQ ))
      #else
      if(StateDataPtr->FeePendReqStatus == FEE_PEND_PREV_NO_REQ)
      #endif
      {
        RetVal = E_OK;
      }
      #if ((FEE_SAFETY_ENABLE == STD_ON) && (MCAL_AR_VERSION == MCAL_AR_422))\
      || (FEE_RUNTIME_ERROR_DETECT == STD_ON)
      else
      {
      #if(MCAL_AR_VERSION == MCAL_AR_422)
        if(StateDataPtr->FeePendReqStatus != FEE_PEND_PREV_NO_REQ)
      #endif
        {
        #if(FEE_SAFETY_ENABLE == STD_ON) && (MCAL_AR_VERSION == MCAL_AR_422)
          Fee_lReportError(FEE_SID_GETQUASISTATICBLOCKINFO,
                              FEE_SE_BUSY, FEE_SAFETY_ERROR);
        #else
          Fee_lReportError(FEE_SID_GETQUASISTATICBLOCKINFO,
                              FEE_E_BUSY, FEE_RUNTIME_ERROR);
        #endif
        }
      }
      #endif
    }
    #if(MCAL_AR_VERSION == MCAL_AR_440) && (FEE_SAFETY_ENABLE == STD_ON)
    else
    {
      Fee_lReportError(FEE_SID_GETQUASISTATICBLOCKINFO,
                            FEE_SE_UNINIT, FEE_SAFETY_ERROR);
    }
    #endif
  }
  #if (FEE_SAFETY_ENABLE == STD_ON)
  else
  {
    /* [cover parentID={C0834B77-1E77-4321-B89C-508F58191567}]
    Is configuration pointer is NULL?
    [/cover] */
    if(Fee_CfgPtr != NULL_PTR)
    {
      Fee_lReportError(FEE_SID_GETQUASISTATICBLOCKINFO,
                          FEE_SE_PARAM_POINTER, FEE_SAFETY_ERROR);
    }
    else
    {
      Fee_lReportError(FEE_SID_GETQUASISTATICBLOCKINFO,
                        FEE_SE_UNINIT, FEE_SAFETY_ERROR);
    }
  }
  #endif
  return RetVal;
}
#endif

#if (FEE_SAFETY_ENABLE == STD_ON) || (MCAL_AR_VERSION == MCAL_AR_440)
#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY) \
    && (FEE_GET_CYCLE_COUNT_API == STD_ON)
/******************************************************************************
** Syntax : LOCAL_INLINE Std_ReturnType Fee_lGetCycleSafetyCheck             **
**                                      (const uint32 * const CountPtr)  **
**                                                                           **
**                                                                           **
** Service ID:                                                               **
**                                                                           **
** Sync/Async:  Synchronous                                                 **
**                                                                           **
** Reentrancy:  Non reentrant                                                **
**                                                                           **
** Parameters (in) :  CountPtr     : Count pointer passed.                   **
** Parameters (out):  None                                                   **
**                                                                           **
** Return value    :  Std_ReturnType                                         **
**                    E_OK: Check Pass                                       **
**                    E_NOT_OK: Check Fail                                   **
** Description : The function check for the initialization and the null      **
**               pointer check, report error if enabled.                     **
******************************************************************************/
/* [cover parentID={45AB1DF7-9855-4799-B3A8-5869709004B6}][/cover] */
LOCAL_INLINE Std_ReturnType Fee_lGetCycleSafetyCheck
          (const uint32 * const CountPtr)
{
  Std_ReturnType RetVal = E_NOT_OK;

  #if(MCAL_AR_VERSION == MCAL_AR_440) && (FEE_SAFETY_ENABLE != STD_ON)
  UNUSED_PARAMETER (CountPtr);
  #endif

  #if (FEE_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={D1ED6278-AF69-44cf-83F2-64D4E5DE7064}]
  Driver is not initialized or count pointer is NULL?
  [/cover] */
  if((Fee_CfgPtr != NULL_PTR) && (CountPtr != NULL_PTR))
  #endif
  {
    #if(MCAL_AR_VERSION == MCAL_AR_440)
    /* [cover parentID={8D1746AA-35F9-47c0-88AE-3C45EDE5DCB7}]
    Is driver initialization is complete
    [/cover] */
    if(Fee_lGetStatus() != MEMIF_UNINIT)
    #endif
    {
      RetVal = E_OK;
    }
    #if(MCAL_AR_VERSION == MCAL_AR_440) && (FEE_SAFETY_ENABLE == STD_ON)
    else
    {
      Fee_lReportError(FEE_SID_GETCYCLECOUNT,
                            FEE_SE_UNINIT, FEE_SAFETY_ERROR);
    }
    #endif
  }
  #if (FEE_SAFETY_ENABLE == STD_ON)
  else
  {
    /* [cover parentID={66E25A95-E286-4966-BBF1-490E4DE39B62}]
    Is configuration pointer is NULL?
    [/cover] */
    if(Fee_CfgPtr != NULL_PTR)
    {
      Fee_lReportError(FEE_SID_GETCYCLECOUNT,
                          FEE_SE_PARAM_POINTER, FEE_SAFETY_ERROR);
    }
    else
    {
      Fee_lReportError(FEE_SID_GETCYCLECOUNT,
                        FEE_SE_UNINIT, FEE_SAFETY_ERROR);
    }
  }
  #endif

  return RetVal;
}
#endif
#endif

/*******************************************************************************
** TRACEABILITY: TBD                                                          **
**                                                                            **
** Syntax : LOCAL_INLINE void Fee_lHandleCancelNotification(void)             **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **k
**
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : Service to handle the cancel job notification. This function **
** is called from  Fee_JobErrorNotification                                   **
*******************************************************************************/
/*[cover parentID={ECCF5152-94AC-4ae0-8779-8E757F46D24F}][/cover]*/
LOCAL_INLINE void Fee_lHandleCancelNotification(void)
{
  Fee_StateDataType  *StateDataPtr;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)

  /* check if it is QS read/write/erase job */
  /*[cover parentID={9B9D2BC8-470B-4e51-B351-A45EE52220F9}][/cover]*/
  if(StateDataPtr->FeeQsJob != FEE_NO_JOB)
  {
    /* Call the Fee_lHandleQsJobFailure with  FEE_CANCEL to notify
    user about cancelled of job*/
    /*[cover parentID={72C96430-9B50-48ba-80EC-65053978087B}][/cover]*/
    Fee_lHandleQsJobFailure(FEE_CANCEL);
  }
  else
  #endif
  {
    /*Call the nvm error notification using Fee_lHandleUsrJobFailure
    to notify cancelled job*/

    /*If write job is cancelled then increase free page address to next
    but one WL. This will avoid write on same page for next write job*/
    /*[cover parentID={8D56D966-D3B4-4917-B6F7-F15C4E3A9F37}][/cover]*/
    if(Fee_lGetUserJob(StateDataPtr->FeePendReqStatus) == FEE_WRITE_JOB)
    {
      StateDataPtr->FeeNextFreePageAddr += StateDataPtr->FeeLastWriteSize;
      #if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
      if(Fee_lIsWLBeginning(StateDataPtr->FeeNextFreePageAddr) != FEE_NEW_WL_BEGIN)
      #endif
      {
        StateDataPtr->FeeNextFreePageAddr = Fee_lGetNextWLAddr(
                                            StateDataPtr->FeeNextFreePageAddr);
      }
      StateDataPtr->FeeNextFreePageAddr += FEE_DFLASH_WORDLINE_SIZE;
      /*[cover parentID={6745F3AC-F1F9-461c-918F-E4EC103766D5}][/cover]*/
      Fee_lHandleUsrJobFailure(FEE_CANCEL);
      StateDataPtr->FeeUserJobStatus = FEE_JOB_IDLE;
      StateDataPtr->FeeUserJobResult = FEE_JOB_FAIL;
    }
    /*[cover parentID={45E51B08-CAAE-4a31-9B82-27E2948E535A}][/cover]*/
    else if(Fee_lGetUserJob(StateDataPtr->FeePendReqStatus)
            == FEE_READ_JOB)
    {
      Fee_lHandleUsrJobFailure(FEE_CANCEL);
      StateDataPtr->FeeUserJobStatus = FEE_JOB_IDLE;
      StateDataPtr->FeeUserJobResult = FEE_JOB_FAIL;
    }
    else
    {
      /* Internal job(GC related)is cancelled only reset internal
      variables NVM error notification is not needed for internal job*/
      StateDataPtr->FeeIntrJobStatus = FEE_JOB_DONE;
      StateDataPtr->FeeIntrJobResult = FEE_JOB_FAIL;
      StateDataPtr->FeeIntrJob = FEE_NO_JOB;
    }

  }
}  /* End of Fee_lHandleCancelNotification() */


/*******************************************************************************
** TRACEABILITY: TBD                                                          **
**                                                                            **
** Syntax : LOCAL_INLINE void Fee_lHandleUsrJobErrorNotification(             **
**                                           Fls_17_Dmu_Job_Type Job)         **
** [/cover]                                                                   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  Fls_17_Dmu_Job_Type Job: give the job type Write/Read   **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : Service to handle the failed job notification. This function **
** is called from Fee_JobErrorNotification                                    **
*******************************************************************************/
/* [cover parentID={783AEE17-3F9A-4e7d-9F8B-287916DEA8FD},
{3A8E66AE-97FF-474d-9C6B-03FB9E8F4473}]
Fee_lHandleUsrJobErrorNotification
[/cover] */
LOCAL_INLINE void Fee_lHandleUsrJobErrorNotification(Fls_17_Dmu_Job_Type Job)
{
  /* [cover parentID={783AEE17-3F9A-4e7d-9F8B-287916DEA8FD}]*/
  Fee_StateDataType  *StateDataPtr;
  uint8               Error;
  uint16              BlockIndex;
  Fee_CacheType      *BlkPtr;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  #if (FEE_GET_PREV_DATA_API == STD_ON)
  Fee_PendReqBufType *PendReqPtr;
  PendReqPtr = &(StateDataPtr->FeePendReqInfo);
  #endif
  /* [cover parentID={58446A1A-A9F2-4b68-83EE-5BEA000D737A}][/cover]*/
  if(Job == FEE_WRITE_JOB)
  {
    /* if job is write job */
    if(StateDataPtr->FeeStatusFlags.FeeBlkInvalidStatus ==
        (uint32)FEE_SET )
    {
      StateDataPtr->FeeStatusFlags.FeeBlkInvalidStatus = FEE_RESET;
      Error = FEE_INVALIDATE;
    }
    else
    {
      Error = FEE_WRITE;
    }

    /* Update Next Free Page Address to next but one WL  */
    StateDataPtr->FeeNextFreePageAddr += StateDataPtr->FeeLastWriteSize;

    StateDataPtr->FeeNextFreePageAddr = Fee_lGetNextWLAddr(
                                          StateDataPtr->FeeNextFreePageAddr);
    StateDataPtr->FeeNextFreePageAddr += FEE_DFLASH_WORDLINE_SIZE;


  }
  /* [cover parentID={AAA3FCEA-E231-402c-B71A-C4D107C4CC54}][/cover]*/
  else /*if(job == FLS_READ_JOB)*/
  {
    /* job is read job */
    /* Update block state as Inconsistent in Cache */
    BlockIndex =
      Fee_lGetUsrBlockIndex(StateDataPtr->FeeCurrReqBlockNum);
    if(BlockIndex != FEE_LOG_BLOCK_NOT_FOUND )
    {
    BlkPtr = &(StateDataPtr->FeeBlockInfo[BlockIndex]);
    #if (FEE_GET_PREV_DATA_API == STD_ON)
    if(PendReqPtr->GetPrevCopy == FEE_SET )
    {
      PendReqPtr->GetPrevCopy = FEE_RESET;
      BlkPtr->Status.PrevCopyConsistent = FEE_RESET;
    }
    else
    #endif
    {
      BlkPtr->Status.Consistent = FEE_RESET;
      if(StateDataPtr->FeeCurrReqBlockNum ==
          StateDataPtr->FeeLastWrittenBlkInfo.BlockNumber)
      {
        StateDataPtr->FeeLastWrittenBlkInfo.Status.Consistent =
          FEE_RESET;
        }
      }
    }
    Error = FEE_READ;
  }

  Fee_lHandleUsrJobFailure(Error);

} /* End of Fee_lHandleUsrJobErrorNotification() */

/*******************************************************************************
** TRACEABILITY: TBD                                                          **
**                                                                            **
** Syntax : LOCAL_INLINE void Fee_lHandleReadJobEndNotification(Void)         **
** [/cover]                                                                   **
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
** Return value    : void                                                     **
**                                                                            **
** Description : Service to handle the Read job completed notification. This  **
** function is called from Fee_JobEndNotification                             **
*******************************************************************************/
/*[cover parentID={99174D42-6191-4f33-AD96-AC2AF1DB0CF9}][/cover]*/
LOCAL_INLINE void Fee_lHandleReadJobEndNotification(void)
{
  Fee_StateDataType  *StateDataPtr;
  uint16             DataByteCount;
  uint16             BlockOffset;
  uint16             Length;
  uint16             LoopIndex;

  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  /* Is this last data set of block if yes then copy data into user buffer and
  trigger job completed notification if configured */
  /*[cover parentID={FD9D397A-6B20-4bc2-AC85-FFA64B0C28C4}][/cover]*/
  if(StateDataPtr->FeePendReqStatus == FEE_PEND_PREV_READ_NOTIF)
  {
    Length = StateDataPtr->FeePendReqInfo.Length;
    BlockOffset = StateDataPtr->FeePendReqInfo.BlockOffset;
    DataByteCount = FEE_ONE;

    /* Copy read data to user buffer */
    if(BlockOffset > FEE_ZERO)
    {
      while((BlockOffset < FEE_SEVEN) && (Length > FEE_ZERO))
      {

        StateDataPtr->FeePendReqInfo.DataBufferPtr[0] =
          StateDataPtr->FeeReadWriteBuffer[DataByteCount + BlockOffset];
        BlockOffset++;

        StateDataPtr->FeePendReqInfo.DataBufferPtr++;
        Length--;
      }
      DataByteCount += FEE_EIGHT;
    }
    while(DataByteCount < StateDataPtr->FeeLastReadSize)
    {
      for(LoopIndex = FEE_RESET;
          (LoopIndex < FEE_SEVEN) && (Length > FEE_ZERO);
          LoopIndex++)
      {

        StateDataPtr->FeePendReqInfo.DataBufferPtr[LoopIndex] =
          StateDataPtr->FeeReadWriteBuffer[DataByteCount + LoopIndex];
        Length--;
      }
      /*MISRA2012_RULE_18_4_JUSTIFICATION: Pointer arithmetic other than
            array indexing used for FEE application buffers.
            Pointers are accessing the correct memory range locations.
            The access range is within the boundaries of the buffer. */
      StateDataPtr->FeePendReqInfo.DataBufferPtr += FEE_SEVEN;
      DataByteCount += FEE_EIGHT;
    }
    /*Reset the pending request status and set the Fee job result
    to MEMIF_JOB_OK ] */
    /*************   RESET JOB VARIABLES ******************/

    #if((FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)&&\
        (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON))
    /*Check if QS erase was suspended. If yes then set FeePendReqStatus to
    FEE_REQ_QUASI_ERASE to set module status to busy.*/
    /*[cover parentID={21662114-6372-47ba-B775-B95AC8386253}][/cover]*/
    if(StateDataPtr->FeeQsEraseSuspend == FEE_ERASE_SUSPENDED)
    {
      /*[cover parentID={14AEAC11-2D47-4d90-8D41-08DA41A69402}][/cover]*/
      StateDataPtr->FeePendReqStatus = FEE_REQ_QUASI_ERASE;
      StateDataPtr->FeeQsJob = FEE_ERASE_JOB;
    }
    else
    #endif
    {
      StateDataPtr->FeePendReqStatus = FEE_PEND_PREV_NO_REQ;
    }
    /* [cover parentID={AC80BD0C-E228-4020-AF90-282FD8EFC9A9}]
    Set the Fee job result to MEMIF_JOB_OK
    FeePendReqInfo.GetPrevCopy = FEE_ZERO
    [/cover] */
    StateDataPtr->FeeJobResult = MEMIF_JOB_OK;
    #if (FEE_GET_PREV_DATA_API == STD_ON)
    StateDataPtr->FeePendReqInfo.GetPrevCopy = FEE_RESET;
    #endif
    /*****************************************************/
    /* [cover parentID={EA288A88-8827-4749-B1DB-2D9D779BB9DA}]
    NVM data block supported
    [/cover] */
    #if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
    /* [cover parentID={1F1E8365-8DFB-4a44-BAF9-12C4871659B7}]
        Call NVM Job end notification function
        [/cover] */
    /* [cover parentID={9515D550-3494-4e38-9569-591E0716E944}]
       Check for notification function
       [/cover] */
    /* Call user configured job End notification */
    if ( Fee_CfgPtr->FeeNvmJobEndNotification != NULL_PTR )
    {
      (Fee_CfgPtr->FeeNvmJobEndNotification)();
    }
    #endif
  }

} /* Emd of Fee_lHandleReadJobEndNotification() */

#if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lMainGCHdlr(void)                           **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This function determines and performs the action required for**
** GC .This function is called from main function  in FEE_MAIN_GC state. This **
*******************************************************************************/
/*[cover parentID={97BA7538-907D-47b5-96EC-5905C1F50E27}][/cover]*/
LOCAL_INLINE void Fee_lMainGCHdlr(void)
{

  #if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
  Fee_StateDataType  *StateDataPtr;
  #else
  const Fee_StateDataType  *StateDataPtr;
  #endif
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  #if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
  /*[cover parentID={EBA6E428-4FDD-492a-AEA9-B671EAD6FF97}][/cover]*/
  if(FEE_ERASE_NOT_SUSPENDED == StateDataPtr->FeeEraseSuspendStatus)
  {
  #endif
    /*[cover parentID={EE38351C-5876-45e5-B328-35D9281FDDB3}][/cover]*/
    if(StateDataPtr->FeeIntrJobStatus != FEE_JOB_REQSTD)
    {
      /*[cover parentID={133AAAAD-9E80-4caf-8ED0-EC281D9F1DAC}][/cover]*/
      Fee_lGarbageCollection();
    }
  #if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
  }
  else
  {
    /*[cover parentID={5921193C-62AF-4957-AFCB-31CD52ECD989}][/cover]*/
    if(StateDataPtr->FeeEraseSuspendStatus < FEE_RESUME_ERASE_LIMIT)
    {
      /* [cover parentID={80C27FFF-BC04-4758-B6E5-3696C361C36F}]
      Resume erase operation
      [/cover] */
      /*[cover parentID={3C1A8023-910E-45f6-A5FF-928F35205A16}][/cover]*/
      if(E_OK == Fls_17_Dmu_ResumeErase())
      {
        /*[cover parentID={BBDCAA49-9A4C-4b31-835B-498C848D9A09}][/cover]*/
        StateDataPtr->FeeEraseSuspendStatus = FEE_ERASE_NOT_SUSPENDED;
      }
      else
      {
        StateDataPtr->FeeEraseSuspendStatus++;
        /*[cover parentID={81909B46-2A7E-4582-A431-7757B992477D}][/cover]*/
        /* [cover parentID={9E85D234-B457-4074-B933-C9C6DA3043BA}]
          Check for erase suspend status
        [/cover] */
        if(FEE_RESUME_ERASE_LIMIT ==
            StateDataPtr->FeeEraseSuspendStatus)
        {
          /* Erased failed raise the illegal notification.block index
          parameter is not used for erase error,so passed as parameter not
          used.Block index is used only for read error to drop the block
          from GC process. */
          /*[cover parentID={ED591944-DD3B-4ea1-A50C-E0BCCDE5D0CC}][/cover]*/
          Fee_lGcErrorHandler(FEE_GC_ERASE, FEE_UNUSED_PARAM);
        }
      }
    }
  }
  #endif
}

/*******************************************************************************
** Syntax : LOCAL_INLINE void Fee_lHandleGcCopy(void)                         **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Uint8 : GC error code                                   **
**                    FEE_GC_WRITE : GC write operation failed.               **
**                    FEE_GC_READ : GC Read operation failed.                 **
** Description : This function handle the GC read , write operation as per GC **
** state . This function is called from Fee_lGarbageCollection function.      **
*******************************************************************************/
/*[cover parentID={63F8D762-7E5A-4d8e-89B0-A2FEE60D0CCB}][/cover]*/
LOCAL_INLINE  uint8 Fee_lHandleGcCopy(void)
{
  const Fee_StateDataType  *StateDataPtr;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;
  uint8                  Error;
  Error = FEE_GC_E_OK;

  /********* FEE_GC_UNCFG_START_COPY *******/
  /*  Reading the first page of an Unconfig block is done here */
  /* [cover parentID={9125A3B6-EBF3-4c87-BB26-7DBDCC8511FA}]
  Check if GC has to start copying unconfig blocks
  [/cover] */
  if(StateDataPtr->FeeGcState == FEE_GC_UNCFG_START_COPY)
  {
    /*[cover parentID={EC542E78-FD4E-4094-827C-E727E45922C7}][/cover]*/
    Fee_lGcStartCopy();

  }

  /*********** FEE_GC_UNCFG_COPY_WRITE *******************/
  /* [cover parentID={78F787F6-47A6-4077-9E99-7681FB79AD9A}]
  Check if GC has to start to write unconfig block
  [/cover] */
  /*  Writing a page of an unconfigure block is done here */
  if(StateDataPtr->FeeGcState == FEE_GC_UNCFG_COPY_WRITE)
  {
    /*[cover parentID={563929C9-2AFB-4834-9C67-D62A473BEEBF}][/cover]*/
    Error = Fee_lGcStartCopyWrite();
  }

  /*********** FEE_GC_UNCFG_COPY_READ_NXTPAGE *******************/
  /*  Reading the subsequent pages of an Unconfigure block is done here */
  /*[cover parentID={6760C467-873C-40d6-8A66-F5A73B18D641}][/cover]*/
  if(StateDataPtr->FeeGcState == FEE_GC_UNCFG_COPY_READ_NXTPAGE)
  {
    Fee_lGcCopyReadNxtPage();

  }


  /*********** FEE_GC_START_COPY *******************/
  /* [cover parentID={9C849D4D-AB46-45a8-87B0-F4DA96ACE8B9}][/cover] */
  /*  Reading the first page of a Configure block is done here */
  if(StateDataPtr->FeeGcState == FEE_GC_START_COPY)
  {
    /*[cover parentID={560892F1-209A-4f70-A718-4BE7C6DAD395}][/cover]*/
    Fee_lGcStartCopy();

  }


  /*********** FEE_GC_COPY_WRITE *******************/
  /*  Writing a page of a Configure block is done here */
  /*[cover parentID={96E8EE84-B8A1-4bc4-B33E-9BBE8AAC5A2B}][/cover]*/
  if(StateDataPtr->FeeGcState == FEE_GC_COPY_WRITE)
  {
    /*[cover parentID={3168C533-96A8-440a-9372-52A243E91183}][/cover]*/
    Error = Fee_lGcStartCopyWrite();
  }


  /*********** FEE_GC_COPY_READ_NXTPAGE *******************/
  /*  Reading the subsequent pages of a Configure block is done here */
  /*[cover parentID={94A978B9-20DF-4560-B067-5A736A5D6062}][/cover]*/
  if(StateDataPtr->FeeGcState == FEE_GC_COPY_READ_NXTPAGE)
  {
    /*[cover parentID={8D1A56A8-5412-4906-A310-4877D32C2C31}][/cover]*/
    Fee_lGcCopyReadNxtPage();

  }

  /*********** FEE_GC_MARK_SECTOR1_V_SP *******************/
  /*  Writing the valid state page content is done here */
  /*[cover parentID={F772B3BA-89DC-431b-BE4D-C47367057ECC}][/cover]*/
  if(StateDataPtr->FeeGcState == FEE_GC_MARK_SECTOR1_V_SP)
  {
    /*[cover parentID={7BC28FAC-3A6F-484e-8AB8-342BF55D1966}][/cover]*/
    Error = Fee_lGcProgramStatePage(FEE_GC_MARK_SECTOR1_V_SP);
  }


  /*********** FEE_GC_MARK_SECTOR1_V_M *******************/
  /*  Writing the valid state page marker is done here */
  /*[cover parentID={45E0D28C-B56F-448d-A3C7-B4B906ADBB29}][/cover]*/
  if(StateDataPtr->FeeGcState == FEE_GC_MARK_SECTOR1_V_M)
  {
    /*[cover parentID={D8BFCCF6-B3B4-4ce8-9BBA-2E9E637B0E22}][/cover]*/
    Error = Fee_lGcProgramStatePage(FEE_GC_MARK_SECTOR1_V_M);
  }

  return(Error);
}

#if (FEE_DATA_BLOCK_SUPPORTED == FEE_DOUBLE_SECTOR_AND_QUASI_STATIC_DATA)

/*******************************************************************************
** Syntax : Std_ReturnType  Fee_lIsQsWriteReadAllowed(void)                   **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in-out) : None                                                 **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  boolean : GC error code                                 **
**                    TRUE : QS Read/Write is allowed                         **
**                    FALSE :QS Read/Write is not allowed .                   **
** Description : This function will check if there Qs write or read is        **
** pending and can be executed                                                **
*******************************************************************************/
/* [cover parentID={45200610-4BB9-47b9-8FA8-69777362FF35}]
Fee_lIsQsWriteReadAllowedbyGC
[/cover] */
/* [cover parentID={FA629D11-03AC-476f-A96D-DBE4102A85BA}][/cover] */
static boolean Fee_lIsQsWriteReadAllowedbyGC(void)
{
  #if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
  Fee_StateDataType *StateDataPtr;
  Std_ReturnType     FlsRetVal;

  #else
  const Fee_StateDataType *StateDataPtr;
  #endif
  boolean            RetVal;

  RetVal = (boolean)FALSE;
  StateDataPtr = Fee_CfgPtr->FeeStatePtr;

  /* [cover parentID={D77485C3-84EE-43f5-ADB8-DAC33879E083}][/cover] */
  if((StateDataPtr->FeePendReqStatus == FEE_REQ_QUASI_WRITE) ||
      (StateDataPtr->FeePendReqStatus == FEE_REQ_QUASI_READ))
  {
    /*Check if GC in erase state as part of normal GC opertaion.Pending request
    can not be executed when GC in erase state as part init GC because of cache
    table is not yet build and initialization activity is not finished */
    /* [cover parentID={662B3AB5-68FC-4ace-87A3-04D29F233B7C}][/cover] */
    if((StateDataPtr->FeeGcState == FEE_GC_ERASE_PREV_SECTOR) ||
        (StateDataPtr->FeeGcState == FEE_GC_INIT_ERASE_PREV_SECTOR))
    {
      /* [cover parentID={635491B4-D99B-4786-B393-2063B328A1DB}][/cover] */
      if(StateDataPtr->FeeIntrJobStatus == FEE_JOB_REQSTD)
      {
        /*Check if erase operation can be suspended*/
        #if (FEE_FLS_SUPPORTS_ERASE_SUSPEND == STD_ON)
        if(FEE_ERASE_NOT_SUSPENDED == StateDataPtr->FeeEraseSuspendStatus)
        {
          /* [cover parentID={891C2ACF-0493-4ae4-B472-14359F1C6843}][/cover] */
          FlsRetVal = Fls_17_Dmu_SuspendErase();
          /* [cover parentID={7D299142-85D9-4dd0-A61F-70C1632538FF}][/cover] */
          if(E_OK == FlsRetVal)
          {
            RetVal = (boolean)TRUE;
            /* [cover parentID={C2498C15-66C1-490b-9DE1-1C4C6F6A3E16}][/cover] */
            StateDataPtr->FeeEraseSuspendStatus = FEE_ERASE_SUSPENDED;
          }
        }
        else
        {
          RetVal = (boolean)TRUE;
          StateDataPtr->FeeEraseSuspendStatus = FEE_ERASE_SUSPENDED;
        }
        #endif
      }
      else
      {
        /*Erase is not started or finshed. QS request can be executed*/
        RetVal = (boolean)TRUE;
      }
    }
  }

  return(RetVal);

}

#endif

#endif

#if (FEE_DEM_ENABLED == STD_ON)
/*******************************************************************************
** Syntax : static void  Fee_lReportDemError(void)                            **
**                                                                            **
** Service ID:                                                                **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Description      : This function reports the production error status       **
**                                                                            **
** Parameters (in)  : EventId - ID of the event reported                      **
**                    EventStatus - Status of the event reported              **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*                                                                             **
*******************************************************************************/
/* [cover parentID={B184A912-3160-492c-A464-8FB1E1AC1E4D}][/cover] */
static void  Fee_lReportDemError( const Dem_EventIdType EventId,
    const Dem_EventStatusType EventStatus)
{
  #if (MCAL_AR_VERSION == MCAL_AR_422)
  /* [cover parentID={BC2DA35E-9826-43ab-A4C2-E7CE9297552E}][/cover] */
  Mcal_Wrapper_Dem_ReportErrorStatus(EventId, EventStatus);
  #else
  /* [cover parentID={2E64DEC3-C18D-4b9a-92DE-741E7E20CD0D}][/cover] */
  (void)Mcal_Wrapper_Dem_SetEventStatus(EventId, EventStatus);
  #endif
}
#endif

/* Memory Map of the FEE Code */
#define FEE_STOP_SEC_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"

#define FEE_START_SEC_ERASEERRORNOTI_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"


/*******************************************************************************
** TRACEABILITY: TBD                                                          **
**                                                                            **
** Syntax : void Fee_17_JobEraseErrorNotification(void)                       **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x29                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : Service to report to FEE module the failure of an  Erase     **
** operation and EVR(Erase Verify ) Error occurred.                           **
*******************************************************************************/
/* [cover parentID={F0283E12-60D5-4eef-B6EE-538CD842131D}]
Fee_17_JobEraseErrorNotification
[/cover] */
void Fee_17_JobEraseErrorNotification(void)
{
  /* [cover parentID={436E0729-5394-4d12-97E0-CF59109131FF}]*/
  #if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
  Fls_17_Dmu_Job_Type Job;
  Fee_StateDataType  *StateDataPtr;
  #else
  const Fee_StateDataType  *StateDataPtr;
  #endif

  /* [cover parentID={039EA806-07C1-488a-886B-B0799058E979}]
  SAFETY ENABLE
  [/cover] */
  #if (FEE_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={D9161B1B-F3D9-4a6d-9EAD-0E52B4DFFF80}][/cover] */
  if(Fee_CfgPtr != NULL_PTR)
  #endif
  {
    StateDataPtr = Fee_CfgPtr->FeeStatePtr;

    #if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
    Job = Fls_17_Dmu_GetNotifCaller();
    /* [cover parentID={BECDA997-B9CC-412c-B19D-DC4750413F24}][/cover]*/
    if(Job == StateDataPtr->FeeIntrJob)
    {
      /* GC Erase is operation is failed.(Internal Operation) */
      /* [cover parentID={3D2907CE-F5CA-4d50-9727-B91782927B11}][/cover]*/
      StateDataPtr->FeeIntrJobStatus = FEE_JOB_DONE;
      StateDataPtr->FeeIntrJobResult = FEE_JOB_FAIL;
      StateDataPtr->FeeIntrJob = FEE_NO_JOB;
      StateDataPtr->FeeEraseVerErr = FEE_SET ;
    }
    #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
    /* [cover parentID={0DFAD396-D004-4885-A6D7-7AFB53EBD95B}]
    Check if QS job is requested
    [/cover] */
    else
    {

      /* [cover parentID={9A0F298B-959C-4053-9AAB-B5374E877F97}][/cover]*/
      Fee_lHandleQsJobFailure((FEE_NOT_CANCEL));
    }
    #endif

    #else
    /* [cover parentID={717A9A00-F636-4d4f-AB8A-8F055AC20A57}][/cover]*/
    if(StateDataPtr->FeeQsJob != FEE_NO_JOB)
    {
      /* [cover parentID={016F9895-5CA7-4be1-8B55-2FDED57FFD99}][/cover]*/
      Fee_lHandleQsJobFailure((FEE_NOT_CANCEL));
    }
    #endif
  }
  #if(FEE_SAFETY_ENABLE == STD_ON)
  else
  {
    /* [cover parentID={0123A4A1-A624-4c22-A827-E1334FE6BFEF}]
    Report error FEE_E_UNINIT
    [/cover] */
    Fee_lReportError(FEE_SID_JOBERASEERRORNOTIF,
                        FEE_SE_UNINIT, FEE_SAFETY_ERROR);
  }
  #endif
}

#define FEE_STOP_SEC_ERASEERRORNOTI_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"



#define FEE_START_SEC_PROGERRORNOTI_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"


/*******************************************************************************
** TRACEABILITY: TBD                                                          **
**                                                                            **
** Syntax : void Fee_17_JobProgErrorNotification(void)                        **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID:  0x31                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : Service to report to FEE module if Program Verify Error      **
**  occurred while programming/writing.                                       **
*******************************************************************************/
/* [cover parentID={ABEBA1F6-6119-4326-9549-FB898E5A4E86},
{2B346D07-6920-4f9c-90AC-DA91AD86E39E}]
Fee_17_JobProgErrorNotification
[/cover] */
/* [cover parentID={828AE813-7199-4dd4-A7F7-A89D3FB90B98}]
Program verify error notfication
[/cover] */
void Fee_17_JobProgErrorNotification(void)
{

  #if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
  Fls_17_Dmu_Job_Type Job;
  #endif
  Fee_StateDataType  *StateDataPtr;
  /* [cover parentID={8647E160-A868-4483-AD03-7DABDE73F7C7}]
  Safety is enabled
  [/cover] */
  #if (FEE_SAFETY_ENABLE == STD_ON)
  /* [cover parentID={99A3E686-2F5F-4829-8708-F7AD61FDE3FE}][/cover] */
  if(Fee_CfgPtr != NULL_PTR)
  #endif
  {
    StateDataPtr = Fee_CfgPtr->FeeStatePtr;

    #if (FEE_DATA_BLOCK_SUPPORTED != FEE_QUASI_STATIC_DATA_ONLY)
    Job = Fls_17_Dmu_GetNotifCaller();
    /* [cover parentID={1D58564F-1E3C-422c-A275-732F390B7DED}][/cover] */
    if(Job == StateDataPtr->FeeIntrJob)
    {
      /* [cover parentID={9999D7DD-046C-4ef8-85A9-658BDE0A59F0}][/cover] */
      /* GC Write operation is failed.(Internal Operation) */
      StateDataPtr->FeeIntrJobStatus = FEE_JOB_DONE;
      StateDataPtr->FeeIntrJobResult = FEE_JOB_FAIL;
      StateDataPtr->FeeIntrJob = FEE_NO_JOB;
      StateDataPtr->FeeProgVerErr = FEE_SET ;
    }
    /* [cover parentID={933D6827-C388-49ee-858C-1E193FA665DD}][/cover] */
    else if( Job == Fee_lGetUserJob(StateDataPtr->FeePendReqStatus))
    {
      /* [cover parentID={250338CD-3F8A-41a3-9A3F-B5062C7948E1}][/cover] */
      /* User write Job is failed  */
      StateDataPtr->FeeUserJobStatus = FEE_JOB_DONE;
      StateDataPtr->FeeUserJobResult = FEE_JOB_FAIL;
      StateDataPtr->FeeProgVerErr = FEE_SET ;
    }
    else
    {
      /* [cover parentID={09C4915A-FFAD-42cd-B6DF-AD557D634759}][/cover] */
      #if (FEE_DATA_BLOCK_SUPPORTED != FEE_DOUBLE_SECTOR_DATA_ONLY)
      /* [cover parentID={F9382416-FFC2-4d4d-9ECB-5CF34B43F31B}][/cover] */
      if(StateDataPtr->FeeQsIntrJob != FEE_NO_JOB)
      {
        StateDataPtr->FeeQsIntrJobStatus = FEE_JOB_IDLE;
        StateDataPtr->FeeQsIntrJobResult = MEMIF_JOB_FAILED;
      }
      /*Check if the Qs job is on going.*/
      /* [cover parentID={E98460C4-D3BE-4779-B1C7-3D5574D1C162}][/cover] */
      else if(StateDataPtr->FeeQsJob != FEE_NO_JOB)
      {
        /*Check if erase started marker or destroying of all marker write failed
        in this case ignore the error and continue. All other case raise the
        job error notification.*/
        /* [cover parentID={9BBF778D-19B3-4c0e-8DA6-706A97925D40}][/cover] */
        if((StateDataPtr->FeeQsJob == FEE_ERASE_JOB ) &&
          ((StateDataPtr->FeeQsState == (uint8)FEE_QS_PROG_STATE_ERASE_STARTED) ||
           (StateDataPtr->FeeQsState == (uint8)FEE_QS_PROG_STATE_DESTROY)))
        {
          /*Reset the StateDataPtr->FeeQsJobStatus to idle.So Fee_lMainQs
          get served*/
          StateDataPtr->FeeQsJobStatus = FEE_JOB_IDLE;
        }
        else
        {
          Fee_lHandleQsJobFailure((FEE_NOT_CANCEL));
        }

      }
      else
      {
        /*dummy for misra*/
      }
      #endif
    }


    #else
    /* [cover parentID={FA8C6C3A-D6D7-4304-B51E-151E5CA2069F}][/cover] */
    if(StateDataPtr->FeeQsIntrJob != FEE_NO_JOB)
    {
      StateDataPtr->FeeQsIntrJobStatus = FEE_JOB_IDLE;
      StateDataPtr->FeeQsIntrJobResult = MEMIF_JOB_FAILED;
    }
	/* [cover parentID={5A5DAA06-2D7D-4170-9A98-DA674E3C7215}][/cover] */
    else if(StateDataPtr->FeeQsJob != FEE_NO_JOB)
    {
      /*Check if erase started marker or destroying of all marker write failed
      in this case ignore the error and continue. All other case raise the
      job error notification.*/
      /* [cover parentID={9BBF778D-19B3-4c0e-8DA6-706A97925D40}][/cover] */
      if((StateDataPtr->FeeQsJob == FEE_ERASE_JOB ) &&
          ((StateDataPtr->FeeQsState == (uint8)FEE_QS_PROG_STATE_ERASE_STARTED) ||
           (StateDataPtr->FeeQsState == (uint8)FEE_QS_PROG_STATE_DESTROY)))
      {
        /*Reset the StateDataPtr->FeeQsJobStatus to idle.So Fee_lMainQs
        get served*/
        StateDataPtr->FeeQsJobStatus = FEE_JOB_IDLE;
      }
      else
      {
        Fee_lHandleQsJobFailure((FEE_NOT_CANCEL));
      }
    }
    else
    {
      /*dummy for misra*/
    }
    #endif

  }
  #if(FEE_SAFETY_ENABLE == STD_ON)
  else
  {
    /* [cover parentID={83CC42E0-B3A9-41a3-B6FC-2ADDB075E8B8}]
    Report safety error with FEE_E_UNINIT
    [/cover] */
    Fee_lReportError(FEE_SID_JOBPROGERRORNOTIF,
                        FEE_SE_UNINIT, FEE_SAFETY_ERROR);
  }
  #endif

}

#define FEE_STOP_SEC_PROGERRORNOTI_CODE_ASIL_B_LOCAL
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"
