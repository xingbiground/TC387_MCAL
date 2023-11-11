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
**  FILENAME  : Dsadc_Cfg.h                                                   **
**                                                                            **
**  VERSION   : 11.0.0                                                        **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:35        !!!IGNORE-LINE!!!                 **
**                                                                            **
**  GENERATOR : Build b191017-0938          !!!IGNORE-LINE!!!                 **
**                                                                            **
**  BSW MODULE DECRIPTION : Dsadc.bmd                                         **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Dsadc configuration generated out of ECUC file             **
**                                                                            **
**  SPECIFICATION(S) : Specification of DSADC Driver                          **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

#ifndef DSADC_CFG_H
#define DSADC_CFG_H
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
#define DSADC_AR_RELEASE_MAJOR_VERSION      (4U)
#define DSADC_AR_RELEASE_MINOR_VERSION      (2U)
#define DSADC_AR_RELEASE_REVISION_VERSION   (2U)

#define DSADC_SW_MAJOR_VERSION  (20U)
#define DSADC_SW_MINOR_VERSION  (25U)
#define DSADC_SW_PATCH_VERSION  (0U)

#define DSADC_NUM_OF_CHANNELS              (0xaU)

/* Configuration Options for DEM Options for the enabling/disabling of
   DEM in DSADC Driver */
#define DSADC_DISABLE_DEM_REPORT    (0x0U)
#define DSADC_ENABLE_DEM_REPORT     (0x1U)

/*Configuration option for DSADC Channel Access Mode*/
#define DSADC_SINGLE_READ           (0x0U)
#define DSADC_CIRCULAR_BUFFER       (0x1U)
#define DSADC_STREAM_LINEAR_BUFFER  (0x2U)
#define DSADC_DMA_ACCESS            (0x3U)

/*Configuration option for DSADc Channel Timestamp function availability*/
#define DSADC_TIMESTAMP_DISABLED    (0x0U)
#define DSADC_TIMESTAMP_ENABLED     (0x1U)

/*Configuration option for DSADC Channel Timestamp Trigger function availability*/
#define DSADC_NO_TIMESTAMP_TRIGGER  (0x0U)
#define DSADC_TIMESTAMP_WINDOWOPEN  (0x1U)
#define DSADC_TIMESTAMP_WINDOWCLOSE (0x2U)

/*Configuration option for DSADC Channel Trigger Mode*/
#define DSADC_TRIGGER_MODE_NORMAL   (0x0U)
#define DSADC_TRIGGER_MODE_WINDOW   (0x1U)

/*Configuration option for DSADC Channel Gate signla Active level*/
#define DSADC_GATE_HIGH_LEVEL       (0x0U)
#define DSADC_GATE_LOW_LEVEL        (0x1U)

/*Configuration option for Carrier Signal Type */
#define DSADC_CARR_SIG_STOPPED      (0x0U)
#define DSADC_CARR_SIG_SQUAREWAVE   (0x1U)
#define DSADC_CARR_SIG_TRIANGLE     (0x2U)
#define DSADC_CARR_SIG_SINEWAVE     (0x3U)

/* Type of Trigger Source when the Trigger mode is Window  */
#define DSADC_TRIGGER_NONE          (0x0U)
#define DSADC_TRIGGER_GTM           (0x1U)
#define DSADC_TRIGGER_ERU           (0x2U)

/* Configuration Options for the setting the privilege mode in DSADC Driver */
#define DSADC_SUPERVISOR_MODE  (0U)
#define DSADC_USER1_MODE  (1U)

/* Derived Configuration for DsadcDevErrorDetect */
#define DSADC_DEV_ERROR_DETECT              (STD_ON)

/* Derived Configuration for DsadcDeInitApi */
#define DSADC_DEINIT_API                    (STD_OFF)

/* Derived Configuration for DsadcSafetyEnable */
#define DSADC_SAFETY_ENABLE                 (STD_ON)

/* Derived Configuration for DsadcInitCheckApi */
#define DSADC_INITCHECK_API                 (STD_ON)


/* Derived Configuration for DsadcVersionInfoApi */
#define DSADC_VERSION_INFO_API              (STD_OFF)


/* Derived Configuration for DsadcRestartIntegratorApi */
#define DSADC_RESTART_INTEGRATOR_API                    (STD_OFF)

/* Configuration: DSADC_INIT_DEINIT_API_MODE
Determines the privilege mode in which the Initialization and De-initialization APIs would operate*/
#define DSADC_INIT_DEINIT_API_MODE          (DSADC_SUPERVISOR_MODE)

/* Configuration: DSADC_RUN_TIME_API_MODE
Determines the privilege mode in which the runtime APIs would operate*/
#define DSADC_RUN_TIME_API_MODE             (DSADC_SUPERVISOR_MODE)


/* Configuration: DSADC_GTMTRIGGER_USED
Pre Compile switch to determine any channel is using GTM or not.*/
#define DSADC_GTMTRIGGER_USED               (STD_OFF)

/* Configuration: DSADC_ERUTRIGGER_USED
Pre Compile switch to determine any channel is using ERU or not.*/
#define DSADC_ERUTRIGGER_USED               (STD_OFF)

/* Configuration: DSADC_ALL_CH_RESULT_HANDLING_DMA
Pre Compile switch to determine whether all channels are using the DMA or not.*/
#define DSADC_ALL_CH_RESULT_HANDLING_DMA    (STD_OFF)
/* Configured DSADC Channels Symbolic Names */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code to be in sync with  Autosar Naming constraints.
No side effects foreseen by violating this MISRA rule.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code to be in sync with  Autosar Naming constraints.
No side effects foreseen by violating this MISRA rule.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code to be in sync with  Autosar Naming constraints.
No side effects foreseen by violating this MISRA rule.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code to be in sync with  Autosar Naming constraints.
No side effects foreseen by violating this MISRA rule.*/
#ifndef DsadcChannel_DsadcChannelConfiguration_0
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code to be in sync with  Autosar Naming constraints.
No side effects foreseen by violating this MISRA rule.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code to be in sync with  Autosar Naming constraints.
No side effects foreseen by violating this MISRA rule.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code to be in sync with  Autosar Naming constraints.
No side effects foreseen by violating this MISRA rule.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code to be in sync with  Autosar Naming constraints.
No side effects foreseen by violating this MISRA rule.*/

#define DsadcChannel_DsadcChannelConfiguration_0     ((Dsadc_ChannelType)0x0U)
#endif

/* Number of DSADC channels configured */
#define DSADC_MAX_CHANNELS_CONFIGURED                ((Dsadc_ChannelType)1U)

/* Number of ERS channels configured for DSADC driver for pattern detection*/
#define DSADC_MAX_ERS_CHANNELS_CONFIGURED            (0U)

/* Configuration: DSADC_CLC_FAILURE_DEM_NOTIF Determines whether Production Error for CLC failure is enabled or disabled */
#define DSADC_CLC_FAILURE_DEM_NOTIF   (DSADC_ENABLE_DEM_REPORT)
#define DSADC_E_CLC_FAILURE           (DemConf_DemEventParameter_DSADC_E_CLC_FAILURE)
#define DSADC_FIFO_FAILURE_DEM_NOTIF  (DSADC_ENABLE_DEM_REPORT)
#define DSADC_E_FIFO_FAILURE          (DemConf_DemEventParameter_DSADC_E_FIFO_FAILURE)


#endif  /* DSADC_CFG_H */

