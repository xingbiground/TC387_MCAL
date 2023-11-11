/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2022)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : CanTrcv_17_V9251G_Cfg.h                                       **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:32       !!!IGNORE-LINE!!!              **
**                                                                            **
**  GENERATOR : Build b191017-0938           !!!IGNORE-LINE!!!              **
**                                                                            **
**  MODULE DECRIPTION : CanTrcv_17_V9251.bmd                                  **
**                                                                            **
**  VARIANT   : VariantPC                                                     **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : CanTrcv_17_V9251 configuration generated out of            **
**                 ECU configuration file                                     **
**                                                                            **
**  SPECIFICATION(S) : Specification of CanTransceiver Driver                 **
**                     Release AUTOSAR 4.2.2                                  **
**                                                                            **
**  MAY BE CHANGED BY USER [yes/no]: No                                       **
*******************************************************************************/
#ifndef CANTRCV_17_V9251_CFG_H
#define CANTRCV_17_V9251_CFG_H
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Include Icu header file */
#include "Icu_17_TimerIp.h"
/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/* CANTRCV MODULE INSTANCE ID */
#define CANTRCV_17_V9251_INSTANCE_ID                  ((uint8)0)

/* Autosar specific version information */
#define CANTRCV_17_V9251_AR_RELEASE_MAJOR_VERSION     (4U)
#define CANTRCV_17_V9251_AR_RELEASE_MINOR_VERSION     (2U)
#define CANTRCV_17_V9251_AR_RELEASE_REVISION_VERSION  (2U)

/* Vendor specific implementation version information */
#define CANTRCV_17_V9251_SW_MAJOR_VERSION             (20U)
#define CANTRCV_17_V9251_SW_MINOR_VERSION             (20U)
#define CANTRCV_17_V9251_SW_PATCH_VERSION             (0U)

/*
Configuration: CANTRCV_DEV_ERROR_DETECT
- if STD_ON, DET is Enabled
- if STD_OFF,DET is Disabled
*/
#define CANTRCV_17_V9251_DEV_ERROR_DETECT             (STD_ON)


/*
Configuration: CANTRCV_GENERAL_WAKE_UP_SUPPORT
- INTERRUPT: Only Interrupt mode is supported
*/
#define CANTRCV_17_V9251_GENERAL_WAKE_UP_SUPPORT  \
(CANTRCV_17_V9251_WAKE_UP_BY_INTERRUPT)


/*
Configuration: CANTRCV_VERSION_INFO_API
- if STD_ON, Function CanTrcv_17_V9251_GetVersionInfo is available
- if STD_OFF,Function CanTrcv_17_V9251_GetVersionInfo is not available
*/
#define CANTRCV_17_V9251_GET_VERSION_INFO             (STD_OFF)


/*
Configuration: CANTRCV_WAIT_COUNT expressed in nanoseconds.
- Range is 20us ... 255us
*/
#define CANTRCV_17_V9251_WAIT_COUNT                   (20000U)


/*
Configuration: Channel Identifier
*/
/* Symbolic name for CanTrcvChannel_1 */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#ifndef CanTrcv_17_V9251Conf_CanTrcvChannel_CanTrcvChannel_1

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CanTrcv_17_V9251Conf_CanTrcvChannel_CanTrcvChannel_1    ((uint8)1U)
#endif

/* Icu channel reference  not configured */
#define CANTRCV_17_V9251_CH_1_ICU_REF        (ICU_REFERENCE_NOT_CONFIGURED)

/* CanTrcv Channel_1 max baud rate supported */
/* [cover parentID={B10A013A-6F8D-4c8f-BCC8-D9F079EDB143}] [/cover] */
#define CANTRCV_17_V9251_CH_1_MAX_BAUDRATE_SUPPORT      (1000U)

/* Symbolic name for CanTrcvChannel_2 */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#ifndef CanTrcv_17_V9251Conf_CanTrcvChannel_CanTrcvChannel_2

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CanTrcv_17_V9251Conf_CanTrcvChannel_CanTrcvChannel_2    ((uint8)2U)
#endif

/* Icu channel reference  not configured */
#define CANTRCV_17_V9251_CH_2_ICU_REF        (ICU_REFERENCE_NOT_CONFIGURED)

/* CanTrcv Channel_2 max baud rate supported */
/* [cover parentID={B10A013A-6F8D-4c8f-BCC8-D9F079EDB143}] [/cover] */
#define CANTRCV_17_V9251_CH_2_MAX_BAUDRATE_SUPPORT      (1000U)

/* Symbolic name for CanTrcvChannel_3 */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#ifndef CanTrcv_17_V9251Conf_CanTrcvChannel_CanTrcvChannel_3

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CanTrcv_17_V9251Conf_CanTrcvChannel_CanTrcvChannel_3    ((uint8)3U)
#endif

/* Icu channel reference  not configured */
#define CANTRCV_17_V9251_CH_3_ICU_REF        (ICU_REFERENCE_NOT_CONFIGURED)

/* CanTrcv Channel_3 max baud rate supported */
/* [cover parentID={B10A013A-6F8D-4c8f-BCC8-D9F079EDB143}] [/cover] */
#define CANTRCV_17_V9251_CH_3_MAX_BAUDRATE_SUPPORT      (1000U)

/* Symbolic name for CanTrcvChannel_0 */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#ifndef CanTrcv_17_V9251Conf_CanTrcvChannel_CanTrcvChannel_0

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define CanTrcv_17_V9251Conf_CanTrcvChannel_CanTrcvChannel_0    ((uint8)0U)
#endif

/* Icu channel reference  not configured */
#define CANTRCV_17_V9251_CH_0_ICU_REF        (ICU_REFERENCE_NOT_CONFIGURED)

/* CanTrcv Channel_0 max baud rate supported */
/* [cover parentID={B10A013A-6F8D-4c8f-BCC8-D9F079EDB143}] [/cover] */
#define CANTRCV_17_V9251_CH_0_MAX_BAUDRATE_SUPPORT      (5000U)

/* Number of channels used */
#define CANTRCV_17_V9251_CHANNELS_USED              ((uint8)4U)

/* Number of channels configured in the CanTrcvChannel container */
#define CANTRCV_17_V9251_CHANNELS_CFG               ((uint8)4U)

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/

/*******************************************************************************
**                               End of File                                  **
*******************************************************************************/
#endif /*END OF  CANTRCV_17_V9251_CFG_H */
