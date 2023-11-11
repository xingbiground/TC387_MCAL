
/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2021)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Can_17_McmCan_Cfg.h                                           **
**                                                                            **
**  VERSION   : 12.0.0                                                        **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:32          !!!IGNORE-LINE!!!               **
**                                                                            **
**  GENERATOR : Build b191017-0938            !!!IGNORE-LINE!!!               **
**                                                                            **
**  BSW MODULE DECRIPTION : Can_17_McmCan.bmd                                 **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Can configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of Can Driver, AUTOSAR Release 4.2.2 and **
**                     4.4.0                                                  **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/


#ifndef CAN_17_MCMCAN_CFG_H
#define CAN_17_MCMCAN_CFG_H




/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/*******************************************************************************
**                      Common Published Information                          **
*******************************************************************************/
/* [cover parentID={BDE616FE-5D39-4b9d-9390-8351CC6C490C}]
[/cover] */
/* [cover parentID={7BE20AAE-30B8-46f5-ABBC-F2E65FBCEEE8}]
[/cover] */
#define CAN_17_MCMCAN_AR_RELEASE_MAJOR_VERSION          (4U)
/* [cover parentID={B0D7A378-F23B-4f83-86A7-50682CB089E5}]
[/cover] */
#define CAN_17_MCMCAN_AR_RELEASE_MINOR_VERSION          (2U)
/* [cover parentID={F34E3ADE-341D-4e08-9A3B-B454B00382E4}]
[/cover] */
#define CAN_17_MCMCAN_AR_RELEASE_REVISION_VERSION       (2U)

/* [cover parentID={98E1F5ED-AA8E-49af-8DBB-E84CD1B0960B}]
[/cover] */
#define CAN_17_MCMCAN_SW_MAJOR_VERSION                  (20U)
/* [cover parentID={EAB7012E-044A-4fb7-84E1-245B81493A73}]
[/cover] */
#define CAN_17_MCMCAN_SW_MINOR_VERSION                  (25U)
/* [cover parentID={4763C7E9-3BE5-4b3b-96DA-1E92B11A9191}]
[/cover] */
#define CAN_17_MCMCAN_SW_PATCH_VERSION                  (0U)


/*******************************************************************************
**          Global Macro Definitions                                          **
*******************************************************************************/

/* L-PDU receive callout support enabled or not */
#define CAN_17_MCMCAN_LPDU_RX_CALLOUT                    (STD_OFF)

/* Master core is allocated with CAN controllers */
#define CAN_17_MCMCAN_MASTER_CORE_ALLOCATION                       (STD_ON)

/* Multicore Enabled or not */
#define CAN_17_MCMCAN_MULTICORE_ERROR_DETECT                       (STD_OFF)

#define CAN_17_MCMCAN_RUNTIME_ERROR_DETECT               (STD_ON)

/* Maximum number of CAN Controllers configured in a ConfigSet */
#define CAN_17_MCMCAN_NOOF_CONTROLLER                       (uint8)(2U)

/* Maximum number of CAN Controllers configured in a ConfigSet for CORE0 */
#define CAN_17_MCMCAN_CORE0_NOOF_CONTROLLER      (uint8)(2U)

/* Trigger transmit Enabled or not */
#define CAN_17_MCMCAN_TRIG_TRANSMIT                                 (STD_ON)

/* Maximum number of main function RW periods configured in a ConfigSet */
#define CAN_17_MCMCAN_NOOF_RX_TX_PERIODS_CONFIG              (0U)

/* Multiple cycle period for Recieve is configured in a ConfigSet */
#define CAN_17_MCMCAN_RX_MULTI_PERIODS_SUPPORT               (STD_OFF)

/* Multiple cycle period for Transmit is configured in a ConfigSet */
#define CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT               (STD_OFF)

/* Maximum number of Icom configurations with in the ConfigSet */
#define CAN_17_MCMCAN_NOOF_ICOM_CONFIGURATIONS        (IcomConfigIdType) (1U)

/* Maximum number of Icom Message configurations with in the ConfigSet */
#define CAN_17_MCMCAN_NOOF_ICOM_MSGCONFIGURATIONS     (1U)

/* Maximum number of Icom Signal configurations with in the ConfigSet */
#define CAN_17_MCMCAN_NOOF_ICOM_SIGNALCONFIGURATIONS  (0U)

/* Initialization and De-Initilaization user mode configuration */
#define CAN_17_MCMCAN_INIT_DEINIT_API_MODE   (CAN_17_MCMCAN_MCAL_SUPERVISOR)

/*******************************************************************************
**                      CAN General Information                               **
*******************************************************************************/
/* Configuration: CAN_17_MCMCAN_INSTANCE_ID
- Specifies the InstanceId of this module instance
*/
#define CAN_17_MCMCAN_INSTANCE_ID                     (0U)

/* Configuration: CAN_17_MCMCAN_DEV_ERROR_DETECT
- STD_ON  - DET is enabled
- STD_OFF - DET is disabled
*/
#define CAN_17_MCMCAN_DEV_ERROR_DETECT                            (STD_OFF)


/* Configuration: CAN_17_MCMCAN_VERSION_INFO_API
- STD_ON  - Can_17_McmCan_GetVersionInfo API is enabled
- STD_OFF - Can_17_McmCan_GetVersionInfo API is disabled
*/
#define CAN_17_MCMCAN_VERSION_INFO_API                            (STD_ON)

/* Configuration: CAN_17_MCMCAN_MULTIPLEXED_TRANSMISSION
- STD_ON  - Multiplexed transmission feature is enabled
- STD_OFF - Multiplexed transmission feature is disabled
*/
#define CAN_17_MCMCAN_MULTIPLEXED_TRANSMISSION                    (STD_OFF)

/* Configuration: CAN_17_MCMCAN_TIMEOUT_DURATION
- Specifies the maximum amount of time for a blocking function until
a time-out is raised in short term wait loops
*/
#define CAN_17_MCMCAN_TIMEOUT_DURATION                            (10000000U)

/* Configuration: CAN_17_MCMCAN_SET_BAUDRATE_API
- STD_ON  - Can_17_McmCan_SetBaudrate API is enabled
- STD_OFF - Can_17_McmCan_SetBaudrate API is Disabled
*/
#define CAN_17_MCMCAN_SET_BAUDRATE_API                            (STD_ON)

/* Configuration: CanControllerFdBaudrateConfig
- STD_ON  - FD Operation is Enabled
- STD_OFF - FD Operation is Disabled
*/
#define CAN_17_MCMCAN_FD_ENABLE                                   (STD_ON)
/* Configuration: CAN_17_MCMCAN_DEINIT_API
- STD_ON  - CAN De-initialization API is enabled
- STD_OFF - CAN De-initialization API is not enabled
*/
#define CAN_17_MCMCAN_DEINIT_API                                  (STD_ON)

/* Configuration: CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT
- STD_ON  - CAN Pretended networking is enabled
- STD_OFF - CAN Pretended networking is not enabled
*/
#define CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT                         (STD_ON)

/* Number of transmit hardware object buffers present */
#define CAN_17_MCMCAN_MAX_SWOBJECT_INDEX            ((uint8)(384U))

/* Number of nodes per kernel */
#define CAN_17_MCMCAN_NOOF_NODES_PER_KERNEL     ((uint32)(4U))



/******************************************************************************/
/* CAN Controller Configurations */
/******************************************************************************/
/* CAN Activation on CORE0
- STD_ON  - A CAN Kernel is activated on Core 0
- STD_OFF - No CAN Kernel is activated on Core 0
*/
#define CAN_17_MCMCAN_CORE0_ACTIVATION                     (STD_ON)
/* CAN Activation on CORE1
- STD_ON  - A CAN Kernel is activated on Core 1
- STD_OFF - No CAN Kernel is activated on Core 1
*/
#define CAN_17_MCMCAN_CORE1_ACTIVATION                     (STD_OFF)
/* CAN Activation on CORE2
- STD_ON  - A CAN Kernel is activated on Core 2
- STD_OFF - No CAN Kernel is activated on Core 2
*/
#define CAN_17_MCMCAN_CORE2_ACTIVATION                     (STD_OFF)
/* CAN Activation on CORE3
- STD_ON  - A CAN Kernel is activated on Core 3
- STD_OFF - No CAN Kernel is activated on Core 3
*/
#define CAN_17_MCMCAN_CORE3_ACTIVATION                     (STD_OFF)
/* CAN Activation on CORE4
- STD_ON  - A CAN Kernel is activated on Core 4
- STD_OFF - No CAN Kernel is activated on Core 4
*/
#define CAN_17_MCMCAN_CORE4_ACTIVATION                     (STD_OFF)
/* CAN Activation on CORE5
- STD_ON  - A CAN Kernel is activated on Core 5
- STD_OFF - No CAN Kernel is activated on Core 5
*/
#define CAN_17_MCMCAN_CORE5_ACTIVATION                     (STD_OFF)



/*BusOff Processing Event used as Interrupt
- STD_ON - BusOff event is notified through Interrupt mechanism by the
configured controller
- STD_OFF - BusOff event is notified through Interrupt mechanism by the
configured controller
*/
#define CAN_17_MCMCAN_BO_INTERRUPT_PROCESSING                     (STD_ON)

/* Transmission Processing Event used as Interrupt
- STD_ON - Transmission event is notified through Interrupt mechanism by the
configured controller
- STD_OFF - Transmission event is notified through Interrupt mechanism by the
configured controller
*/
#define CAN_17_MCMCAN_TX_INTERRUPT_PROCESSING                     (STD_ON)

/* Reception Processing Event used as Interrupt
- STD_ON - Reception event is notified through Interrupt mechanism by the
configured controller
- STD_OFF - Reception event is not notified through Interrupt mechanism by the
configured controller
*/
#define CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING                     (STD_ON)

/*BusOff Processing Event used as POLLING
- STD_ON - BusOff event is notified through Polling mechanism by the
configured controller
- STD_OFF - BusOff event is notified through Polling mechanism by the
configured controller
*/
#define CAN_17_MCMCAN_BO_POLLING_PROCESSING                       (STD_OFF)

/* Transmission Processing Event used as POLLING
- STD_ON - Transmission event is notified through Polling mechanism by the
configured controller
- STD_OFF - Transmission event is notified through Polling mechanism by the
configured controller
*/
#define CAN_17_MCMCAN_TX_POLLING_PROCESSING                       (STD_OFF)

/* Reception Processing Event used as POLLING
- STD_ON - Reception event is notified through Polling mechanism by the
configured controller
- STD_OFF - Reception event is notified through Polling mechanism by the
configured controller
*/
#define CAN_17_MCMCAN_RX_POLLING_PROCESSING                       (STD_OFF)

/* WakeUp Processing Event used as POLLING
- STD_ON - WakeUp event is notified through Polling mechanism by the
configured controller
- STD_OFF - WakeUp event is notified through Polling mechanism by the
configured controller
*/
#define CAN_17_MCMCAN_WU_POLLING_PROCESSING                       (STD_OFF)

/* Reception Processing Event used as Mixed
- STD_ON - Reception event is notified through mixed mode by the
configured controller
- STD_OFF - Reception event is notified through mixed mode by the
configured controller
*/
#define CAN_17_MCMCAN_RX_MIXED_PROCESSING                     (STD_OFF)

/* Transmission Processing Event used as Mixed
- STD_ON - Transmission event is notified through mixed mode by the
configured controller
- STD_OFF - Transmission event is notified through mixed mode by the
configured controller
*/
#define CAN_17_MCMCAN_TX_MIXED_PROCESSING                     (STD_OFF)

/* Controller Handle Id */

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define Can_17_McmCanConf_CanController_CanController_0             0

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define Can_17_McmCanConf_CanController_CanController_1             1

/* Hardware object Handle Id */

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define Can_17_McmCanConf_CanHardwareObject_CanHardwareObject_0         0

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define Can_17_McmCanConf_CanHardwareObject_CanHardwareObject_1         1

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define Can_17_McmCanConf_CanHardwareObject_CanHardwareObject_2         2

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define Can_17_McmCanConf_CanHardwareObject_CanHardwareObject_3         3

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define Can_17_McmCanConf_CanHardwareObject_CanHardwareObject_4         4

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define Can_17_McmCanConf_CanHardwareObject_CanHardwareObject_5         5

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define Can_17_McmCanConf_CanHardwareObject_CanHardwareObject_6         6

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define Can_17_McmCanConf_CanHardwareObject_CanHardwareObject_7         7

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define Can_17_McmCanConf_CanHardwareObject_CanHardwareObject_8         8

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define Can_17_McmCanConf_CanHardwareObject_CanHardwareObject_9         9

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define Can_17_McmCanConf_CanHardwareObject_CanHardwareObject_10         10

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define Can_17_McmCanConf_CanHardwareObject_CanHardwareObject_11         11

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define Can_17_McmCanConf_CanHardwareObject_CanHardwareObject_12         12

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define Can_17_McmCanConf_CanHardwareObject_CanHardwareObject_13         13

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define Can_17_McmCanConf_CanHardwareObject_CanHardwareObject_14         14

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define Can_17_McmCanConf_CanHardwareObject_CanHardwareObject_15         15

/* ICOM Configuration Id */
#define Can_17_McmCanConf_CanIcomConfigIndex_Deactivate            0

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define Can_17_McmCanConf_CanIcomConfigIndex_CanIcomConfig_0         1
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


#endif  /* CAN_17_MCMCAN_CFG_H */
