
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
**  FILENAME  : Sent_Cfg.h                                                    **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
**                                                                            **
**  DATE, TIME: 2023-11-11, 18:00:52   !!!IGNORE-LINE!!!                      **
**                                                                            **
**  GENERATOR : Build b200227-0222       !!!IGNORE-LINE!!!                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Sent.bmd                                          **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Sent configuration generated out of ECUC file              **
**                                                                            **
**  SPECIFICATION(S) : Specification of Sent Driver, AUTOSAR Release 4.2.2    **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

#ifndef SENT_CFG_H
#define SENT_CFG_H

#include "Sent_Types.h"

/* AUTOSAR specification version numbers */
#define Sent_AR_RELEASE_MAJOR_VERSION  (4U)
#define Sent_AR_RELEASE_MINOR_VERSION  (2U)
#define Sent_AR_RELEASE_PATCH_VERSION  (2U)
/* Vendor specific implementation version information */
#define SENT_SW_MAJOR_VERSION              (10U)
#define SENT_SW_MINOR_VERSION              (40U)
#define SENT_SW_PATCH_VERSION              (1U)
/* SENT_MCAL_SUPERVISOR  */
/* Sent Operation in Supervisory Mode  */
#define SENT_MCAL_SUPERVISOR             (0U)

/* SENT_MCAL_USER1  */
/* Sent Operation in User 1 Mode  */
#define SENT_MCAL_USER1                  (1U)
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/*
Container : SentGeneralConfiguration
*/
/*
The following macros will enable or disable a particular feature
in SENT module.
Set the macro to ON to enable the feature and OFF to disable the same.
*/
/*
Configuration: SENT_DEV_ERROR_DETECT
Preprocessor switch for enabling the development error detection and
reporting.
- if STD_ON, DET is Enabled
- if STD_OFF,DET is Disabled
*/
#define SENT_DEV_ERROR_DETECT  (STD_ON)

/* Configuration: SENT_DEINIT_API
Sent_DeInit API configuration
- if STD_ON, DeInit API is Enabled
- if STD_OFF, DeInit API is Disabled
*/
#define SENT_DEINIT_API        (STD_OFF)

/* Configuration: SENT_VERSION_INFO_API
Version Information API configuration
- if STD_ON, VersionInfo API is Enabled
- if STD_OFF, VersionInfo API is Disabled
*/
#define SENT_VERSION_INFO_API  (STD_OFF)

/* Configuration: SENT_SPC_USED
SENT SPC Feature configuration
- if STD_ON, SPC feature is Enabled
- if STD_OFF, SPC feature is Disabled
*/
#define SENT_SPC_USED         (STD_OFF)

/* Configuration: SENT_RESET_SFR_AT_INIT
SENT Enable/Disable Reset of SFR's during Init
- if STD_ON, Enables Reset of SFR's during Init
- if STD_OFF, Disables Reset of SFR's during Init
*/
#define SENT_RESET_SFR_AT_INIT (STD_OFF)

/* Multicore Enabled or not */
#define SENT_MULTICORE_ERROR_DETECT (STD_ON)

/* Configuration: SENT_HW_MAX_CHANNELS
Maximum number of SENT physical channels supported
*/
#define SENT_HW_MAX_CHANNELS   (25U)

/* Configuration: SENT MODULE INSTANCE ID */
#define SENT_INSTANCE_ID       ((uint8)0)

/* Total no. of config sets */
#define SENT_CONFIG_COUNT    (1U)
/*
Configuration: SENT_INIT_DEINIT_API_MODE:
-User Mode Macro for init deinit APIs
*/
#define SENT_INIT_DEINIT_API_MODE      (SENT_MCAL_SUPERVISOR)

/* Configured SENT Channels Symbolic Names */
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/*******************************************************************************
**                                Sent Driver Usage                           **
*******************************************************************************/

/* Configuration: ResourceM
The configuration contains allocation of Sent channels across cores.
- if STD_ON, atleast one sent channel is configured in the core.
- if STD_OFF, no sent channels are configured in the core. */
#define SENT_CONFIGURED_CORE0                              (STD_ON)
#define SENT_CONFIGURED_CORE1                              (STD_OFF)
#define SENT_CONFIGURED_CORE2                              (STD_OFF)
#define SENT_CONFIGURED_CORE3                              (STD_OFF)
#define SENT_CONFIGURED_CORE4                              (STD_OFF)
#define SENT_CONFIGURED_CORE5                              (STD_OFF)

/*
Configuration:Max channels configured for Sent, max channels are same across
variants.
*/

/* [cover parentID={995E2C8C-C822-4607-A21E-DFBF8C0BF9EC}]
Sent Max Channels macro
[/cover] */
#define SENT_MAX_CHANNELS_CONFIGURED         ((Sent_ChannelType)1)
/* Number of Cores confgiured for Sent */
#define MASTER_CORE_ID           0U

#define SENT_CHANNEL_COUNT_CORE1           0U

#define SENT_CHANNEL_COUNT_CORE0       1U
#define SENT_MAX_CHANNELS_MASTER_CORE     1U

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
extern const Sent_NotifFnPtrType SentNotifFnPtrArray[1];
/* ConfigSet 0 */

/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/
#endif  /* SENT_CFG_H */

