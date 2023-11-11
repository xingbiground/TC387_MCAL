
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
**  FILENAME  : Uart_Cfg.h                                                    **
**                                                                            **
**  VERSION   : 9.0.0                                                         **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:31  !!!IGNORE-LINE!!!                   **
**                                                                            **
**  GENERATOR : Build b191017-0938      !!!IGNORE-LINE!!!                   **
**                                                                            **
**  BSW MODULE DECRIPTION : Uart.bmd                                          **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Uart configuration generated out of ECUC file              **
**                                                                            **
**  SPECIFICATION(S) :Specification of Uart Driver, AUTOSAR Release 4.2.2 and **
**                                                      AUTOSAR Release 4.4.0 **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/* [cover parentID={417E6D71-626B-439d-A213-18197AE5E50D}]
[/cover] */
#ifndef UART_CFG_H
#define UART_CFG_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/* UART  Interrupt mode definations */
#define UART_INTERRUPT_MODE  (0U)
#define UART_POLLING_MODE    (1U)
#define UART_MIXED_MODE      (2U)

/* UART  clock source selection in CSR Register */
#define UART_CSRREG_CLKSEL_FASTCLK          (2U)
#define UART_CSRREG_CLKSEL_SLOWCLK          (4U)

/*SW Version Information*/
/* [cover parentID={4CDB1F5E-2C2B-4d68-9010-0D6412FF9A56}]
[/cover] */
#define UART_SW_MAJOR_VERSION   (20U)
/* [cover parentID={61892AA6-8599-46f6-BBB4-871FE72AAD0B}]
[/cover] */
#define UART_SW_MINOR_VERSION   (25U)
/* [cover parentID={A1E33B51-84CE-4af3-83D2-6F00D9D7DE1D}]
[/cover] */
#define UART_SW_PATCH_VERSION   (0U)

/* [cover parentID={CD73F08D-C743-4d6e-B2DA-A92CB28F0A95}]
[/cover] */
/* Section to Generate Autosar Specific Version Information */
#define UART_AR_RELEASE_MAJOR_VERSION          (4U)
/* [cover parentID={94FF191D-0837-4dd2-8F8A-0BF79B9E5475}]
[/cover] */
#define UART_AR_RELEASE_MINOR_VERSION          (2U)
/* [cover parentID={F68A26DB-F5C8-4c06-9A6A-E6CC8FB9BAD5}]
[/cover] */
#define UART_AR_RELEASE_PATCH_VERSION       (2U)

/*
Configuration Options for the setting the privilege mode in Uart driver
*/
#define UART_SUPERVISOR_MODE  (0U)
#define UART_USER1_MODE       (1U)
/*
Container : UartGeneral Configuration
*/

/*
Derived Configuration for UartDevErrorDetect
- if STD_ON, DET is Enabled
- if STD_OFF,DET is Disabled
The detection of all development errors is configurable (On / Off)
at precompile time. The switch UART_DEV_ERROR_DETECT  shall
activate or deactivate the detection of all development errors.

If the switch UART_DEV_ERROR_DETECT is enabled API parameter checking
is also enabled.
*/
#define UART_DEV_ERROR_DETECT  (STD_ON)
/* [cover parentID={A63E3C3E-8967-4d8e-9C89-F576C5551815}]
[/cover] */
/*
Derived Configuration for UartVersionInfoApi
- if STD_ON, Function Uart_GetVersionInfo is available
- if STD_OFF,Function Uart_GetVersionInfo is not available
*/
#define UART_VERSION_INFO_API  (STD_ON)
/* [cover parentID={4429B9A4-4A10-4cd7-BAE2-7DDAC6E3237D}]
[/cover] */
/* [cover parentID={D1A79D4F-2569-410c-B3E8-AC33182F76B5}]
[/cover] */
/*
Derived Configuration for Uart_InitCheck
- if STD_ON, Function Uart_InitCheck is available
- if STD_OFF,Function Uart_InitCheck is not available
*/
#define UART_INIT_CHECK_API  (STD_OFF)
/* [cover parentID={F9326D24-DFB7-4f82-88CA-E516B1811703}]
[/cover] */
/*
Derived Configuration for UartDeinitApi
- if STD_ON, Function UartDeinitApi is available
- if STD_OFF,Function UartDeinitApi is not available
*/
#define UART_DEINIT_API  (STD_ON)
/* [cover parentID={F97996B1-009A-4bdf-9B37-7C159F941A79}]
[/cover] */
/*
Derived Configuration for UartStreaming APIs
- if STD_ON, Functions Uart_StartStreaming and Uart_StopStreaming are available
- if STD_OFF,Functions Uart_StartStreaming and Uart_StopStreaming are not available
*/
#define UART_RECEIVE_STREAMING_MODE_API  (STD_ON)
/* [cover parentID={96EF52DD-2606-4824-B769-A88314479A6F}]
[/cover] */
/*
Derived Configuration for UartAbortReadApi
- if STD_ON, Function UartAbortReadApi is available
- if STD_OFF,Function UartAbortReadApi is not available
*/
#define UART_ABORT_READ_API  (STD_ON)
/* [cover parentID={FFF59F58-EC6D-4755-BB4B-8FC53B4634BA}]
[/cover] */
/*
Derived Configuration for UartAbortWriteApi
- if STD_ON, Function UartAbortWriteApi is available
- if STD_OFF,Function UartAbortWriteApi is not available
*/
#define UART_ABORT_WRITE_API  (STD_ON)
/* [cover parentID={4C9A5139-5A7F-4be2-AD8C-5E1D27DD2828}]
[/cover] */
/* Configuration: UART_INIT_DEINIT_API_MODE
Determines the privilege mode in which the Initialization and
De-initialization APIs would operate
*/
#define UART_INIT_DEINIT_API_MODE  (UART_SUPERVISOR_MODE)

/* [cover parentID={59A52310-7D5F-428b-B542-578A53CC08D2}]
[/cover] */
/*
Derived Configuration for UartRxChannelMode
- if UART_INTERRUPT_MODE, Function Uart_IsrReceive,Uart_IsrError is available
- if UART_POLLING_MODE,Function Uart_MainFunction_Read is available
- if UART_MIXED_MODE,Function Uart_MainFunction_Read,Uart_IsrReceive and Uart_IsrError is available.
*/
#define UART_RX_MODE  (UART_INTERRUPT_MODE)

/* [cover parentID={DF7CB90D-64C9-451c-A273-AE7415D2745A}]
[/cover] */
/*
Derived Configuration for UartTxPollingEnable
- if UART_INTERRUPT_MODE, Function Uart_IsrTransmit,Uart_IsrError is available
- if UART_POLLING_MODE,Function Uart_MainFunction_Write is available
- if UART_MIXED_MODE,Function Uart_MainFunction_Write,Uart_IsrTransmit and Uart_IsrError is available.
*/
#define UART_TX_MODE  (UART_INTERRUPT_MODE)

/* [cover parentID={2596A0C0-0059-4db8-99CD-BE08911A6173}]
[/cover] */
/*
Derived Configuration for UartSafetyEnable
- if STD_ON, Safety feature is enable.
- if STD_OFF,Safety feature is disable.
*/
#define UART_SAFETY_ENABLE  (STD_ON)
/* Derived configuration for UartIndex */
#define UART_INDEX  (0U)

/* [cover parentID={B76F4DF7-5C1E-43af-A615-C8E14D9B2B05}]
[/cover] */
/* Specifies the maximum time in nanoseconds to wait for hardware timeout errors */
#define UART_MAXTIMEOUT_COUNT  (4294967295U)

/* [cover parentID={288809DE-6463-4723-A725-1817AA5E94FA}]
[/cover] */
/* Total number of ASCLIN hardware module available */
#define UART_MAX_HW_UNIT (24U)

/* [cover parentID={6402633D-25D0-4580-9038-6A995A77B28C}]
[/cover] */
/* Identifies the the ASCLINx for a channel */
#define UART_ASCLIN0 (0U)
#define UART_ASCLIN1 (1U)
#define UART_ASCLIN2 (2U)
#define UART_ASCLIN3 (3U)
#define UART_ASCLIN4 (4U)
#define UART_ASCLIN5 (5U)
#define UART_ASCLIN6 (6U)
#define UART_ASCLIN7 (7U)
#define UART_ASCLIN8 (8U)
#define UART_ASCLIN9 (9U)
#define UART_ASCLIN10 (10U)
#define UART_ASCLIN11 (11U)
#define UART_ASCLIN12 (12U)
#define UART_ASCLIN13 (13U)
#define UART_ASCLIN14 (14U)
#define UART_ASCLIN15 (15U)
#define UART_ASCLIN16 (16U)
#define UART_ASCLIN17 (17U)
#define UART_ASCLIN18 (18U)
#define UART_ASCLIN19 (19U)
#define UART_ASCLIN20 (20U)
#define UART_ASCLIN21 (21U)
#define UART_ASCLIN22 (22U)
#define UART_ASCLIN23 (23U)

/* [cover parentID={8410EE05-E0E1-4f51-8BD6-C560FCB6B8E4}]
[/cover] */
/* Generating list of offset addresses defined in register file for all UART
kernels */
#define UART_ASCLIN_REG_ADDR   &MODULE_ASCLIN0,  \
    &MODULE_ASCLIN1,    &MODULE_ASCLIN2,    &MODULE_ASCLIN3,  \
    &MODULE_ASCLIN4,    &MODULE_ASCLIN5,    &MODULE_ASCLIN6,  \
    &MODULE_ASCLIN7,    &MODULE_ASCLIN8,    &MODULE_ASCLIN9,  \
    &MODULE_ASCLIN10,    &MODULE_ASCLIN11,    &MODULE_ASCLIN12,  \
    &MODULE_ASCLIN13,    &MODULE_ASCLIN14,    &MODULE_ASCLIN15,  \
    &MODULE_ASCLIN16,    &MODULE_ASCLIN17,    &MODULE_ASCLIN18,  \
    &MODULE_ASCLIN19,    &MODULE_ASCLIN20,    &MODULE_ASCLIN21,  \
    &MODULE_ASCLIN22,    &MODULE_ASCLIN23

/* [cover parentID={B51D0ED0-D2A0-4809-9434-425705C8147B}]
[/cover] */
/*
    Configuration: UART_CSRREG_CLKSEL_CLC
    - if UART_CSRREG_CLKSEL_FASTCLK, ASCLIN peripheral frequency for fast mode is selected.
    (Derived from PLL2 frequency upto 200 MHz)
    - if UART_CSRREG_CLKSEL_SLOWCLK, ASCLIN peripheral frequency for slow mode is selected.
    (Derived from PLL1 frequency upto 80 MHz)
*/
#define UART_CSRREG_CLKSEL_CLC (UART_CSRREG_CLKSEL_SLOWCLK)

/* Maximum of number of channels configured. */
/* [cover parentID={344C50A8-3C3B-451c-BDC1-91765B6418CA}]
[/cover] */
#define UART_NUM_OF_CHANNEL_CONFIGURED (1U)
/* Sleep mode is enable or disable */
#define UART_SLEEP_MODE_SUPPORT (0x08U)

/* [cover parentID={1C813F83-60F1-4df7-8D9F-3E1FEF4B2E54}]
[/cover] */
/* Enable/Disable RunTime error detection */
#define UART_RUNTIME_ERROR_DETECT         (STD_ON)

/******************************************************************************
**                      Global Type Definitions                              **
******************************************************************************/

/******************************************************************************
**                      Global Constant Declarations                         **
******************************************************************************/

/*****************************************************************************
**                      Global Variable Declarations                        **
******************************************************************************/

/******************************************************************************
**                      Global Inline Function Definitions                   **
******************************************************************************/
#endif  /* UART_CFG_H */

