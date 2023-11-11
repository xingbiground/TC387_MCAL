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
**  FILENAME  : Lin_17_AscLin_Cfg.h                                           **
**                                                                            **
**  VERSION   : 11.0.0                                                         **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:30      !!!IGNORE-LINE!!!               **
**                                                                            **
**  GENERATOR : Build b191017-0938          !!!IGNORE-LINE!!!               **
**                                                                            **
**  BSW MODULE DECRIPTION : Lin.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Lin configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of Lin Driver, AUTOSAR Release 4.2.2     **
**                                              and AUTOSAR Release 4.4.0     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

#ifndef LIN_17_ASCLIN_CFG_H
#define LIN_17_ASCLIN_CFG_H

/* AUTOSAR specification version numbers */
#define LIN_17_ASCLIN_AR_RELEASE_MAJOR_VERSION  (4U)
#define LIN_17_ASCLIN_AR_RELEASE_MINOR_VERSION  (2U)
#define LIN_17_ASCLIN_AR_RELEASE_REVISION_VERSION  (2U)

/* Vendor specific implementation version information */
#define LIN_17_ASCLIN_SW_MAJOR_VERSION  (20U)
#define LIN_17_ASCLIN_SW_MINOR_VERSION  (25U)
#define LIN_17_ASCLIN_SW_PATCH_VERSION  (0U)
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/


/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/*
    Container : GeneralConfiguration
*/

/*
    Configuration: LIN_17_ASCLIN_DEV_ERROR_DETECT
    - if STD_ON, DET is Enabled
    - if STD_OFF, DET is Disabled
*/
#define LIN_17_ASCLIN_DEV_ERROR_DETECT (STD_ON)
/*
    Configuration: LIN_17_ASCLIN_MULTICORE_ERROR_DETECT
    DET should be ON when LinMultiCoreErrorDetect is ON
*/
#define LIN_17_ASCLIN_MULTICORE_ERROR_DETECT           (STD_OFF)

/* LIN  clock source selection in CSR Register */
#define LIN_17_ASCLIN_CSRREG_CLKSEL_FASTCLK          (2U)
#define LIN_17_ASCLIN_CSRREG_CLKSEL_SLOWCLK          (4U)

/* Macro for Timeout duration */
#define LIN_17_ASCLIN_TIMEOUT_COUNT (300U)

/* Production Error reporting  macros */
#define LIN_17_ASCLIN_DEM_REPORT_DISABLED               (0U)
#define LIN_17_ASCLIN_DEM_REPORT_ENABLED                (1U)
/* Production Error Related Macros */
#define LIN_17_ASCLIN_HW_ERROR_DEM_REPORT            (LIN_17_ASCLIN_DEM_REPORT_DISABLED)

/*
    Configuration: LIN_17_ASCLIN_VERSION_INFO_API
    - if STD_ON, Lin_17_AscLin_GetVersionInfo() Api is Enabled
    - if STD_OFF, Lin_17_AscLin_GetVersionInfo() Api is Disabled
*/

#define LIN_17_ASCLIN_VERSION_INFO_API (STD_OFF)
/* Instance Id of Lin module instance */
#define LIN_17_ASCLIN_INDEX (0)

/* Maximum number of ASCLIN Hw modules available  */
#define LIN_17_ASCLIN_MAX_HW_UNIT (24U)

/* Maximum number of LIN Channels configured */
#define LIN_17_ASCLIN_MAXIMUM_CHANNEL_CONFIGURED (1)
/*
    Configuration: LIN_17_ASCLIN_CLC
    - if 0x0, ASCLIN module sleep upon request is Enabled
    - if 0x8, ASCLIN module sleep upon request is Disabled
*/
#define LIN_17_ASCLIN_CLC (0x8)
/* Identifies the the Rx alternate pin selection for a channel */
#define LIN_17_ASCLIN_SELECT_A (0x0)
#define LIN_17_ASCLIN_SELECT_B (0x1)
#define LIN_17_ASCLIN_SELECT_C (0x2)
#define LIN_17_ASCLIN_SELECT_D (0x3)
#define LIN_17_ASCLIN_SELECT_E (0x4)
#define LIN_17_ASCLIN_SELECT_F (0x5)
#define LIN_17_ASCLIN_SELECT_G (0x6)
#define LIN_17_ASCLIN_SELECT_H (0x7)

/* Identifies the the ASCLINx for a channel */
#define LIN_17_ASCLIN0 (0U)
#define LIN_17_ASCLIN1 (1U)
#define LIN_17_ASCLIN2 (2U)
#define LIN_17_ASCLIN3 (3U)
#define LIN_17_ASCLIN4 (4U)
#define LIN_17_ASCLIN5 (5U)
#define LIN_17_ASCLIN6 (6U)
#define LIN_17_ASCLIN7 (7U)
#define LIN_17_ASCLIN8 (8U)
#define LIN_17_ASCLIN9 (9U)
#define LIN_17_ASCLIN10 (10U)
#define LIN_17_ASCLIN11 (11U)
#define LIN_17_ASCLIN12 (12U)
#define LIN_17_ASCLIN13 (13U)
#define LIN_17_ASCLIN14 (14U)
#define LIN_17_ASCLIN15 (15U)
#define LIN_17_ASCLIN16 (16U)
#define LIN_17_ASCLIN17 (17U)
#define LIN_17_ASCLIN18 (18U)
#define LIN_17_ASCLIN19 (19U)
#define LIN_17_ASCLIN20 (20U)
#define LIN_17_ASCLIN21 (21U)
#define LIN_17_ASCLIN22 (22U)
#define LIN_17_ASCLIN23 (23U)

/* Generating list of offset addresses defined in register file for all LIN
kernels */
#define LIN_17_ASCLIN_REGADDR   &MODULE_ASCLIN0,  \
    &MODULE_ASCLIN1,    &MODULE_ASCLIN2,    &MODULE_ASCLIN3,  \
    &MODULE_ASCLIN4,    &MODULE_ASCLIN5,    &MODULE_ASCLIN6,  \
    &MODULE_ASCLIN7,    &MODULE_ASCLIN8,    &MODULE_ASCLIN9,  \
    &MODULE_ASCLIN10,    &MODULE_ASCLIN11,    &MODULE_ASCLIN12,  \
    &MODULE_ASCLIN13,    &MODULE_ASCLIN14,    &MODULE_ASCLIN15,  \
    &MODULE_ASCLIN16,    &MODULE_ASCLIN17,    &MODULE_ASCLIN18,  \
    &MODULE_ASCLIN19,    &MODULE_ASCLIN20,    &MODULE_ASCLIN21,  \
    &MODULE_ASCLIN22,    &MODULE_ASCLIN23

/*
    Configuration: LIN_17_ASCLIN_CSRREG_CLKSEL_CLC
    - if LIN_17_ASCLIN_CSRREG_CLKSEL_FASTCLK, ASCLIN peripheral frequency for fast mode is selected.
    (Derived from PLL2 frequency upto 200 MHz)
    - if LIN_17_ASCLIN_CSRREG_CLKSEL_SLOWCLK, ASCLIN peripheral frequency for slow mode is selected.
    (Derived from PLL1 frequency upto 80 MHz)
*/
#define LIN_17_ASCLIN_CSRREG_CLKSEL (LIN_17_ASCLIN_CSRREG_CLKSEL_FASTCLK)
#define LIN_17_ASCLIN_INIT_API_MODE (LIN_17_ASCLIN_MCAL_SUPERVISOR_MODE)

#define LIN_17_ASCLIN_MCAL_SUPERVISOR_MODE (STD_ON)

#define LIN_17_ASCLIN_MCAL_USER1_MODE (STD_OFF)


/*
    Lin Channel : (LinChannel_0)
*/

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/

#ifndef Lin_17_AscLinConf_LinChannel_LinChannel_0

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/

/* <!-- [cover parentID={F7E0ED21-7774-45fb-9AEC-47490C5AE1F9}]
[/cover] --> */

#define Lin_17_AscLinConf_LinChannel_LinChannel_0          (0U)
#endif


/* Loop for all the cores */

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define LIN_17_ASCLIN_MAX_CHANNELS_CORE0               (1U)

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define LIN_17_ASCLIN_MAX_CHANNELS_CORE1               (0U)

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define LIN_17_ASCLIN_MAX_CHANNELS_CORE2               (0U)

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define LIN_17_ASCLIN_MAX_CHANNELS_CORE3               (0U)
/*
    Configuration: LIN_17_ASCLIN_GLOBAL_CHANNEL_WAKEUP_SUPPORT
    - if STD_ON, LinChannelWakeupSupport is enabled for atleast 1 channel
    - if STD_OFF, LinChannelWakeupSupport is not enabled for atleast 1 channel
*/
#define LIN_17_ASCLIN_GLOBAL_CHANNEL_WAKEUP_SUPPORT (STD_ON)

/* Identifies Node Type of LIN Channel */
#define LIN_17_ASCLIN_SLAVE_CH_PRESENT (STD_OFF)
/* <!-- [cover parentID={253D8B6A-D7FC-4780-BF78-AB3DE3BBB817}]
[/cover] --> */
#define LIN_17_ASCLIN_MASTER_CH_PRESENT (STD_ON)
#define LIN_17_ASCLIN_INTERRUPT_ENABLE (STD_ON)
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

/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/
#endif /* LIN_17_ASCLIN_CFG_H */
