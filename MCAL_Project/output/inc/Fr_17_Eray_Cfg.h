
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
**  FILENAME  : Fr_17_Eray_Cfg.h                                              **
**                                                                            **
**  VERSION   : 13.0.0                                                        **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:31             !!!IGNORE-LINE!!!        **
**                                                                            **
**  GENERATOR : Build b191017-0938               !!!IGNORE-LINE!!!          **
**                                                                            **
**  BSW MODULE DECRIPTION : Fr_17_Eray.bmd                                    **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Fr configuration generated out of ECUC file                **
**                                                                            **
**  SPECIFICATION(S) : Specification of FlexRay Driver, AUTOSAR Release 4.2.2 **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/******************************************************************************/
#ifndef  FR_17_ERAY_CFG_H
#define  FR_17_ERAY_CFG_H


/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/* Fr Instance ID */
#define FR_17_ERAY_INSTANCE_ID                ((uint8)0)

/* Autosar specification version */
#define FR_17_ERAY_AR_RELEASE_MAJOR_VERSION           (4U)
#define FR_17_ERAY_AR_RELEASE_MINOR_VERSION           (2U)
#define FR_17_ERAY_AR_RELEASE_REVISION_VERSION        (2U)

/* Vendor specific implementation version information */
#define FR_17_ERAY_SW_MAJOR_VERSION           (20U)
#define FR_17_ERAY_SW_MINOR_VERSION           (25U)
#define FR_17_ERAY_SW_PATCH_VERSION           (0U)

/* FR module Operation in Supervisory Mode  */
#define FR_17_ERAY_MCAL_SUPERVISOR            (0U)

/* FR module Operation in User 1 Mode  */
#define FR_17_ERAY_MCAL_USER1                 (1U)

#define FR_17_ERAY_LPDU_RECONFIGURABLE        (STD_ON)
#define FR_17_ERAY_LPDU_NOT_RECONFIGURABLE    (STD_OFF)

/*
Container : FrDriverConfiguration - ECUC_Fr_00392:
General configuration (parameters) of the FlexRay Driver module.
*/

/*
Configuration: FR_17_ERAY_PREPARE_LPDU
Adds/removes the service Fr_17_Eray_PrepapreLPdu() from the code
- if STD_ON, Fr_17_Eray_PrepapreLPdu() can be used
- if STD_OFF, Fr_17_Eray_PrepapreLPdu() can not be used
*/
#define FR_17_ERAY_PREPARE_LPDU                    (STD_ON)

/*
Configuration: FR_17_ERAY_RECONFIG_LPDU
Adds/removes the service Fr_17_Eray_ReconfigLPdu() from the code
- if STD_ON, Fr_17_Eray_ReconfigLPdu() can be used
- if STD_OFF, Fr_17_Eray_ReconfigLPdu() can not be used
*/
#define FR_17_ERAY_RECONFIG_LPDU                   (STD_ON)

/*
Configuration: FR_17_ERAY_DISABLE_LPDU
Adds/removes the service Fr_17_Eray_DisableLPdu() from the code
- if STD_ON, Fr_17_Eray_DisableLPdu() can be used
- if STD_OFF, Fr_17_Eray_DisableLPdu() can not be used
*/
#define FR_17_ERAY_DISABLE_LPDU                    (STD_ON)

/*
Configuration: FR_17_ERAY_CTRL_TEST_COUNT
Specifies the maximum number of iterations the FlexRay controller hardware test
is performed during controller initialization.
*/
#define FR_17_ERAY_CTRL_TEST_COUNT                   (1U)

/*
Configuration: FR_17_ERAY_DEV_ERROR_DETECT
Preprocessor switch to enable/disable the development error detection and
reporting.
- if STD_ON, Enable development error detection
- if STD_OFF, Disable development error detection
*/
#define FR_17_ERAY_DEV_ERROR_DETECT                  (STD_ON)

/*Configuration: FR_17_ERAY_INDEX
Specifies the InstanceId of this module instance.*/
#define FR_17_ERAY_INDEX             (0U)

/*
Configuration: FR_17_ERAY_NUM_CTRL_SUPPORTED
Determines the maximum number of communication controllers that the driver
supports.
*/
#define FR_17_ERAY_NUM_CTRL_SUPPORTED               (1U)

/*
Configuration: FR_17_ERAY_RX_STRINGENT_CHECK
If stringent check is enabled (true), received frames are only accepted if no
slot status error occured.
*/
#define FR_17_ERAY_RX_STRINGENT_CHECK                (STD_ON)


/*
Configuration: FR_17_ERAY_RX_STRINGENT_LENGTH_CHECK
If stringent check is enabled (true), received frames are only accepted the
received payload length matches the configured payload length.
*/
#define FR_17_ERAY_RX_STRINGENT_LENGTH_CHECK         (STD_OFF)


/*
Configuration: FR_17_ERAY_VERSION_INFO_API
Adds/removes the service Fr_17_Eray_GetVersionInfo() from the code
- if STD_ON, Fr_17_Eray_GetVersionInfo() can be used
- if STD_OFF, Fr_17_Eray_GetVersionInfo() can not be used
*/
#define FR_17_ERAY_VERSION_INFO_API                  (STD_ON)

/*
Configuration: FR_17_ERAY_NMVECTOR_ENABLE
Adds/removes the service Fr_17_Eray_GetNmVector() from the code
- if STD_ON, Fr_17_Eray_GetNmVector() can be used
- if STD_OFF, Fr_17_Eray_GetNmVector() can not be used
*/
#define FR_17_ERAY_NMVECTOR_ENABLE                   (STD_ON)

/*
Configuration: FR_17_ERAY_TIMEOUT_DURATION
Specifies the maximum time in nanoseconds for blocking function until
a timeout is raised in short term wait loops.
*/
#define FR_17_ERAY_TIMEOUT_DURATION                  (3000U)

/*
Configuration: FR_INIT_API_MODE
Specifies the operating modes for FlexRay initialization - SUPERVISOR/ USER1
*/
#define FR_17_ERAY_INIT_API_MODE                  (FR_17_ERAY_MCAL_SUPERVISOR)

/*
Configuration: FR_17_ERAY_TX_CONFLICT_DETECTION
If transmit conflict detection is enabled (true), the Fr_CheckTxLPduStatus API
detects the occurrence of a transmission conflict.
*/
#define FR_17_ERAY_TX_CONFLICT_DETECTION             (STD_ON)

/* Production Error reporting disabled macro */
#define FR_17_ERAY_DEM_REPORT_DISABLED            (0U)

/*****************************************************************************/
/* Symbolic name definitions */
/*****************************************************************************/
/*
Symbolic name definitions for FR controllers and timers.
The symbolic names identify the controller/timers (within an ECU).
*/
/* MISRA2012_RULE_5_1_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
#define Fr_17_ErayConf_FrController_FrController_0_0       (0U)

/* MISRA2012_RULE_5_1_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: Name of identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
#define Fr_17_ErayConf_FrAbsoluteTimer_FrController_0_0    (0U)



/*****************************************************************************/

/*******************************************************************************
**                      Derived Configuration Parameters                      **
*******************************************************************************/

/*
Configuration: FR_17_ERAY_CLEAR_RAMS_TIMEOUT
Specifies the timeout duration in nanoseconds until a timeout
is raised after initialization of the E-Ray internal RAM blocks.
The initialization of the E-Ray internal RAM blocks requires minimum
2048 fCLC_ERAY cycles. 5 percent margin(102 cycles) added to the value.
*/
#define FR_17_ERAY_CLEAR_RAMS_TIMEOUT                (21500U)

/*
Configuration: FR_17_ERAY_POC_BUSY_TIMEOUT
Specifies the timeout duration in nanoseconds for the POC to exit the
busy state during initialization until a timeout is raised.
It takes a maximum of 1024 fCLC_ERAY cycles for the POC to exit busy state.
5 percent margin(51 cycles) added to the value.
*/
#define FR_17_ERAY_POC_BUSY_TIMEOUT                  (10750U)

/*
Configuration: FR_17_ERAY_MBF_TO_OBF_TRNSF_TIMEOUT
Specifies the worst case timeout duration in nanoseconds for
the data transfer from Message Buffer RAM to Output Buffer.
It takes a maximum of 435 fCLC_ERAY cycles for this data transfer.
5 percent margin(22 cycles) is added to this value.
*/
#define FR_17_ERAY_MBF_TO_OBF_TRNSF_TIMEOUT          (4570U)

/* Flag for FIFO configuration */
#define FR_17_ERAY_FIFO_CONFIGURED          (STD_OFF)

/*
Estimated maximum number of message buffers used per controller.
Min (128, max(LPDU count in all PB configurations))
*/
#define FR_17_ERAY_MSG_BUFF_COUNT_MAX_0 (6U)
#define FR_17_ERAY_MSG_BUFF_COUNT_MAX_1 (0U)

/* Number of ERAY Controllers available in the device */
#define FR_17_ERAY_NUM_CONTROLLERS_IN_DEVICE  (2U)

#define FR_17_ERAY_CONTROLLER0_CONFIGURED   (STD_ON)

#define FR_17_ERAY_CONTROLLER1_CONFIGURED   (STD_OFF)

/*
Configuration: FR_17_ERAY_RUNTIME_ERROR_DETECT
Preprocessor switch for enabling the runtime error detection and
reporting.
- if STD_ON, Reporting runntime error is Enabled
- if STD_OFF,Reporting runntime error is Disabled
*/
#define FR_17_ERAY_RUNTIME_ERROR_DETECT  (STD_OFF)
/*
Configuration: FR_17_ERAY_EXTENDED_LPDU_REPORTING
Adds/removes the FR EXTENDED LPDU REPORTING feature
- if STD_ON, Enable LPDU reporting
- if STD_OFF, Disable LPDU reporting
*/
#define FR_17_ERAY_EXTENDED_LPDU_REPORTING  (STD_OFF)

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/


#endif /* FR_17_ERAY_CFG_H */
