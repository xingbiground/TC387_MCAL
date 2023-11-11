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
**  FILENAME  : CanTrcv_17_W9255_Cfg.h                                        **
**                                                                            **
**  VERSION   : 4.0.0                                                         **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:31       !!!IGNORE-LINE!!!                  **
**                                                                            **
**  GENERATOR : Build b191017-0938           !!!IGNORE-LINE!!!                **
**                                                                            **
**  BSW MODULE DECRIPTION : CanTrcv_17_W9255.bmd                              **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : CanTrcv configuration generated out of ECUC file           **
**                                                                            **
**  SPECIFICATION(S) : Specification of CanTrcv Driver, AUTOSAR Release 4.2.2 **
**                       and AUTOSAR Release 4.4.0                            **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/******************************************************************************/
#ifndef CANTRCV_17_W9255_CFG_H
#define CANTRCV_17_W9255_CFG_H
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Include Icu header file */
#include "Icu_17_TimerIp.h"
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/* CAN transceiver module instance Id */
#define CANTRCV_17_W9255_INSTANCE_ID                     ((uint8)0)

/*Autosar Specific Version Information*/
#define CANTRCV_17_W9255_AR_RELEASE_MAJOR_VERSION        (4U)
#define CANTRCV_17_W9255_AR_RELEASE_MINOR_VERSION        (2U)
#define CANTRCV_17_W9255_AR_RELEASE_REVISION_VERSION     (2U)

/* Software Version Information */
#define CANTRCV_17_W9255_SW_MAJOR_VERSION                (20U)
#define CANTRCV_17_W9255_SW_MINOR_VERSION                (25U)
#define CANTRCV_17_W9255_SW_PATCH_VERSION                (0U)

/*
Configuration: CANTRCV_17_W9255_DEV_ERROR_DETECT
Preprocessor switch for enabling the development error detection and
reporting.
- if STD_ON, DET is Enabled
- if STD_OFF, DET is Disabled
*/
#define CANTRCV_17_W9255_DEV_ERROR_DETECT                (STD_ON)

/*
Configuration: CANTRCV_17_W9255_GENERAL_WAKE_UP_SUPPORT
Wake-up modes supported by the transceiver
- INTERRUPT: Wake-up by Interrupt mode
- POLLING: Wake-up by Polling mode
*/
#define CANTRCV_17_W9255_GENERAL_WAKE_UP_SUPPORT      (CANTRCV_17_W9255_WAKE_UP_BY_POLLING)

/*
Configuration: CANTRCV_17_W9255_GET_VERSION_INFO
Version Information API configuration
- if STD_ON, Function CanTrcv_17_W9255_GetVersionInfo is available
- if STD_OFF, Function CanTrcv_17_W9255_GetVersionInfo is not available
*/
#define CANTRCV_17_W9255_GET_VERSION_INFO                (STD_OFF)

/*
Configuration: CANTRCV_17_W9255_WAIT_TIME (Unit is nanoseconds)
Wait time for transceiver mode changes
*/
#define CANTRCV_17_W9255_WAIT_TIME                       (20000U)

/*
Configuration: CANTRCV_17_W9255_SPI_COMM_RETRIES
Indicates the maximum number of communication retries in case of
failed SPI communication
*/
#define CANTRCV_17_W9255_SPI_COMM_RETRIES                (0U)

/* Symbolic name of CanTrcv Channel_0 */
/*
MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars. in generated code due to Autosar naming constraints.
MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars. in generated code due to Autosar naming constraints.
MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars. in generated code due to Autosar naming constraints.
MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars. in generated code due to Autosar naming constraints.
*/
#ifndef CanTrcv_17_W9255_CanTrcvConf_CanTrcvChannel_CanTrcvChannel_0
/*
MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars. in generated code due to Autosar naming constraints.
MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars. in generated code due to Autosar naming constraints.
MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars. in generated code due to Autosar naming constraints.
MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars. in generated code due to Autosar naming constraints.
*/
#define CanTrcv_17_W9255_CanTrcvConf_CanTrcvChannel_CanTrcvChannel_0    (0U)
#endif

/* Max baud rate supported for CanTrcv Channel_0 */
#define CANTRCV_17_W9255_CH_0_MAX_BAUDRATE_SUPPORT       (5000U)

/* Symbolic name of CanTrcv Channel_1 */
/*
MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars. in generated code due to Autosar naming constraints.
MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars. in generated code due to Autosar naming constraints.
MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars. in generated code due to Autosar naming constraints.
MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars. in generated code due to Autosar naming constraints.
*/
#ifndef CanTrcv_17_W9255_CanTrcvConf_CanTrcvChannel_CanTrcvChannel_1
/*
MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars. in generated code due to Autosar naming constraints.
MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars. in generated code due to Autosar naming constraints.
MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars. in generated code due to Autosar naming constraints.
MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars. in generated code due to Autosar naming constraints.
*/
#define CanTrcv_17_W9255_CanTrcvConf_CanTrcvChannel_CanTrcvChannel_1    (1U)
#endif

/* Max baud rate supported for CanTrcv Channel_1 */
#define CANTRCV_17_W9255_CH_1_MAX_BAUDRATE_SUPPORT       (5000U)

/* Number of channels enabled */
#define CANTRCV_17_W9255_CHANNELS_USED                   (2U)

/* Number of channels Configured for PN */
#define CANTRCV_17_W9255_PN_CONFIGURED_CHANNELS          (1U)

/* Number of channels configured */
#define CANTRCV_17_W9255_CHANNELS_CONFIGURED             (2U)


#endif
/*END OF  CANTRCV_17_W9255_CFG_H */
