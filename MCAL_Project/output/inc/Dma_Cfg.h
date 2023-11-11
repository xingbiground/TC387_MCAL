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
**  FILENAME  : Dma_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 9.0.0                                                         **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:31            !!!IGNORE-LINE!!!             **
**                                                                            **
**  GENERATOR : Build b191017-0938              !!!IGNORE-LINE!!!             **
**                                                                            **
**  BSW MODULE DECRIPTION : NA                                                **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Dma configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

#ifndef DMA_CFG_H
#define DMA_CFG_H

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/* AUTOSAR specification version numbers */
#define DMA_AR_RELEASE_MAJOR_VERSION        (4U)
#define DMA_AR_RELEASE_MINOR_VERSION        (2U)
#define DMA_AR_RELEASE_REVISION_VERSION     (2U)

/*SW Version Information*/
#define DMA_SW_MAJOR_VERSION                (20U)
#define DMA_SW_MINOR_VERSION                (10U)
#define DMA_SW_PATCH_VERSION                (0U)

/*Number of DMA channels present in the controller*/
#define DMA_MAX_NUM_OF_CHANNELS             (128U)


/* Derived Configuration for DmaDevErrorDetect */
/*
Configuration: DMA_DEV_ERROR_DETECT
Preprocessor switch for enabling the development error detection and
reporting.
- if STD_ON, DET is Enabled
- if STD_OFF,DET is Disabled
*/
#define DMA_DEV_ERROR_DETECT                (STD_ON)


/* Configuration: DMA_CHDEINIT_API
Deinit API configuration
- if STD_ON, Dma_ChDeInit API is available
- if STD_OFF, Dma_ChDeInit API is not available
*/
#define DMA_CHDEINIT_API                    (STD_OFF)

/* Configuration: DMA_SUSPEND_API
Suspend and freeze API configuration
- if STD_ON, Dma_ChTransferFreeze and Dma_ChTransferResume APIs are available
- if STD_OFF, Dma_ChTransferFreeze and Dma_ChTransferResume APIs are not
available
*/
#define DMA_SUSPEND_API                     (STD_OFF)

/* Configuration: DMA_TRIGGER_API
Channel hardware trigger API configuration
- if STD_ON, Dma_ChEnableHardwareTrigger and Dma_ChDisableHardwareTrigger APIs
are available
- if STD_OFF, Dma_ChEnableHardwareTrigger and Dma_ChDisableHardwareTrigger APIs
are not available
*/
#define DMA_TRIGGER_API                     (STD_ON)

/* Configuration: DMA_DATA_PENDING_API
Get remaining data API configuration
- if STD_ON, Dma_ChGetRemainingData API is available
- if STD_OFF, Dma_ChGetRemainingData API is not available
*/
#define DMA_DATA_PENDING_API                (STD_OFF)

/* Configuration: DMA_BUFFER_SWITCH_API
Buffer Switch API configuration
- if STD_ON, Dma_ChSwitchBuffer API is available
- if STD_OFF, Dma_ChSwitchBuffer API is not available
*/
#define DMA_BUFFER_SWITCH_API               (STD_OFF)

/* Configuration: DMA_GETVERSIONINFO_API
Version Information API configuration
- if STD_ON, Dma_GetVersionInfo API is available
- if STD_OFF, Dma_GetVersionInfo API is not available
*/
#define DMA_GETVERSIONINFO_API               (STD_OFF)


/* Maximum number of transaction set allowed on a DMA channel in case
of linked list
*/
#define DMA_MAX_TRANSACTION_SET_PER_CHANNEL (1U)


/* configuration for DMA_LINKED_LIST_ENABLE
- if STD_ON, Any channel has more than one TCS
- if STD_OFF, None of the DMA channel has more than one TCS
*/
#define DMA_LINKED_LIST_ENABLE              (STD_OFF)

/* configuration for DMA_DOUBLE_BUFFER_ENABLE
- if STD_ON, Any DMA channel has Double buffer configuration
- if STD_OFF, None of the DMA channel has Double buffer configuration
*/
#define DMA_DOUBLE_BUFFER_ENABLE            (STD_OFF)

/* No of DMA channels used in the configuration */
#define DMA_NUM_OF_CHANNELS                 (8U)


/* ******************** USER/SUPERVISOR MODE CONFIGURATIONS ***************** */

#define DMA_MCAL_SUPERVISORMODE (0U)
#define DMA_MCAL_USER1MODE      (1U)

/* Configuration: DMA_INIT_DEINIT_API_MODE
Mode selection for the Init and Deinit APIs
- if DMA_MCAL_SUPERVISORMODE, the init and deinit functions should be
running in the supervisor mode
- if DMA_MCAL_USER1MODE, the init and deinit functions should be running in the
user1 mode
*/
#define DMA_INIT_DEINIT_API_MODE       (DMA_MCAL_SUPERVISORMODE)

/* Configuration: DMA_RUNTIME_API_MODE
Mode selection for the Runtime APIs
- if DMA_MCAL_SUPERVISORMODE, the Runtime functions should be running in the
supervisor mode
- if DMA_MCAL_USER1MODE, the Runtime functions should be running in the
user1 mode
*/
#define DMA_RUNTIME_API_MODE    (DMA_MCAL_SUPERVISORMODE)
/* ************************************************************************** */


/* ************************ MULTICORE CONFIGURATIONS ************************ */

/* Derived Configuration for DmaMultiCoreErrorDetect */
/*
Configuration: DMA_MULTICORE_ERROR_DETECT
Preprocessor switch for enabling the multicore error checks and error reporting.
- if STD_ON, multicore error checks are Enabled
- if STD_OFF, multicore error checks are Disabled
*/

#define DMA_MULTICORE_ERROR_DETECT          (STD_OFF)


/* Total number of DMA channels in core 0 */
#define DMA_ALLOCATED_CHANNELS_CORE0 (8U)
/* Total number of DMA channels in core 1 */
#define DMA_ALLOCATED_CHANNELS_CORE1 (0U)
/* Total number of DMA channels in core 2 */
#define DMA_ALLOCATED_CHANNELS_CORE2 (0U)
/* Total number of DMA channels in core 3 */
#define DMA_ALLOCATED_CHANNELS_CORE3 (0U)


/* ************************************************************************** */


/* *************************** SAFETY CONFIGURATIONS ************************ */
/* Derived Configuration for DmaSafetyEnable */
/*
Configuration: DMA_SAFETY_ENABLE
Preprocessor switch for enabling the safety checks and error reporting.
- if STD_ON, Safety checks are Enabled
- if STD_OFF,Safety checks are Disabled
*/
#define DMA_SAFETY_ENABLE                   (STD_ON)

/* Configuration: DMA_INITCHECK_API
Init check API configuration
- if STD_ON,  Dma_InitCheck API is available
- if STD_OFF, Dma_InitCheck API is not available
*/
#define DMA_INITCHECK_API                   (STD_ON)

/* Configuration: DMA_DEINIT_API
Deinit API configuration
- if STD_ON,  DeInit API is available
- if STD_OFF, DeInit API is not available
*/
#define DMA_DEINIT_API                   (STD_OFF)

/* Configuration: DMA_SETPATTERN_API
Set_Pattern API configuration
- if STD_ON,  Set_Pattern API is available
- if STD_OFF, Set_Pattern API is not available
*/
#define DMA_SETPATTERN_API             (STD_OFF)

/* ************************************************************************** */

#endif  /* DMA_CFG_H */
