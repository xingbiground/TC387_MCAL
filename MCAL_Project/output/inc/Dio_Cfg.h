
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
**  FILENAME  : Dio_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 8.0.0                                                         **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:31         !!!IGNORE-LINE!!!                **
**                                                                            **
**  GENERATOR : Build b191017-0938             !!!IGNORE-LINE!!!              **
**                                                                            **
**  BSW MODULE DECRIPTION : Dio.bmd                                           **
**                                                                            **
**  VARIANT   : Variant LT                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Dio configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of Dio Driver, AUTOSAR Release 4.2.2     **
**                     and AUTOSAR Release 4.4.0                              **
**                                                                            **
** MAY BE CHANGED BY USER : no                                                **
**                                                                            **
*******************************************************************************/
#ifndef DIO_CFG_H
#define DIO_CFG_H
/*
Notes:
- The runtime configuration is handled by the Port Driver Module.
- The configuration and usage of the DIO Driver Module is adapted to
the microcontroller and ECU.

*/

/*Version check macros */
#define DIO_AR_RELEASE_MAJOR_VERSION     (4U)
#define DIO_AR_RELEASE_MINOR_VERSION     (2U)
#define DIO_AR_RELEASE_REVISION_VERSION  (2U)


#define DIO_SW_MAJOR_VERSION  (20U)
#define DIO_SW_MINOR_VERSION  (25U)
#define DIO_SW_PATCH_VERSION  (0U)

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/*                          Container: DioGeneral                            */
/*

Pre-processor switch to enable/disable detection of Development errors.
- if defined ON, Development error detection is enabled
- if defined OFF, Development error detection is disabled
*/
#define DIO_DEV_ERROR_DETECT                (STD_ON)

/*
Pre-Compiler switch to include the API Dio_GetVersionInfo()
- if defined ON, Dio_GetVersionInfo API available
- if defined OFF, Dio_GetVersionInfo API not available
*/
#define DIO_VERSION_INFO_API                (STD_OFF)

/*
Pre-Compiler switch to include the API Dio_FlipChannel()
- if defined ON, Dio_FlipChannel API available
- if defined OFF, Dio_FlipChannel API not available
*/
#define DIO_FLIP_CHANNEL_API                (STD_ON)

#define DIO_MASKED_WRITE_PORT_API           (STD_OFF)
/*
Pre-Compiler switch to include the Safety Check
*/

#define DIO_SAFETY_ENABLE                (STD_ON)

/* The following macros are available only if development error detection
is enabled */
/* Definition to specify the ports available on the microcontroller
Bit value = 0 implies the port is not available
Bit value = 1 implies the port is available
Bit 0 is for Port 0, Bit 1 is for Port 1, ... , Bit 31 is for Port 31 */
#define DIO_PORTS_AVAILABLE_00_31           (0xc7f0fc07U)

/* Definition to specify the ports available on the microcontroller
Bit value = 0 implies the port is not available
Bit value = 1 implies the port is available
Bit 0 is for Port 32, Bit 1 is for Port 33, ... , Bit 31 is for Port 63 */
#define DIO_PORTS_AVAILABLE_32_63           (0x00000307U)

/* Definition to specify the ports that are read only ports on the microcontroller
Bit value = 0 implies the port readable/writable
Bit value = 1 implies the port is read only port
Bit 0 is for Port 0, Bit 1 is for Port 1, ... , Bit 31 is for Port 31 */
#define DIO_PORTS_READONLY_00_31             (0x00000000U)

/* Definition to specify the ports that are read only ports on the microcontroller
Bit value = 0 implies the port readable/writable
Bit value = 1 implies the port is read only port
Bit 0 is for Port 32, Bit 1 is for Port 33, ... , Bit 31 is for Port 63 */
#define DIO_PORTS_READONLY_32_63             (0x00000300U)

/* Value of the most significant pin on the port
Note: In case of no pins on a port, the value is kept 0 */
#define DIO_PORT_0_MSPIN                     (15U)
#define DIO_PORT_1_MSPIN                     (15U)
#define DIO_PORT_2_MSPIN                     (15U)
#define DIO_PORT_3_MSPIN                     (0U)
#define DIO_PORT_4_MSPIN                     (0U)
#define DIO_PORT_5_MSPIN                     (0U)
#define DIO_PORT_6_MSPIN                     (0U)
#define DIO_PORT_7_MSPIN                     (0U)
#define DIO_PORT_8_MSPIN                     (0U)
#define DIO_PORT_9_MSPIN                     (0U)
#define DIO_PORT_10_MSPIN                     (15U)
#define DIO_PORT_11_MSPIN                     (15U)
#define DIO_PORT_12_MSPIN                     (1U)
#define DIO_PORT_13_MSPIN                     (15U)
#define DIO_PORT_14_MSPIN                     (15U)
#define DIO_PORT_15_MSPIN                     (15U)
#define DIO_PORT_16_MSPIN                     (0U)
#define DIO_PORT_17_MSPIN                     (0U)
#define DIO_PORT_18_MSPIN                     (0U)
#define DIO_PORT_19_MSPIN                     (0U)
#define DIO_PORT_20_MSPIN                     (14U)
#define DIO_PORT_21_MSPIN                     (7U)
#define DIO_PORT_22_MSPIN                     (11U)
#define DIO_PORT_23_MSPIN                     (7U)
#define DIO_PORT_24_MSPIN                     (15U)
#define DIO_PORT_25_MSPIN                     (15U)
#define DIO_PORT_26_MSPIN                     (0U)
#define DIO_PORT_27_MSPIN                     (0U)
#define DIO_PORT_28_MSPIN                     (0U)
#define DIO_PORT_29_MSPIN                     (0U)
#define DIO_PORT_30_MSPIN                     (15U)
#define DIO_PORT_31_MSPIN                     (15U)
#define DIO_PORT_32_MSPIN                     (7U)
#define DIO_PORT_33_MSPIN                     (15U)
#define DIO_PORT_34_MSPIN                     (5U)
#define DIO_PORT_35_MSPIN                     (0U)
#define DIO_PORT_36_MSPIN                     (0U)
#define DIO_PORT_37_MSPIN                     (0U)
#define DIO_PORT_38_MSPIN                     (0U)
#define DIO_PORT_39_MSPIN                     (0U)
#define DIO_PORT_40_MSPIN                     (15U)
#define DIO_PORT_41_MSPIN                     (8U)
/* Macro to define the maximum port available */
#define MAX_AVAILABLE_PORT                  (41U)

/* Values to mask the undefined port pins within a port */
#define DIO_MASK_ALL_PINS_PORT0             (0xffffU)
#define DIO_MASK_ALL_PINS_PORT1             (0xffffU)
#define DIO_MASK_ALL_PINS_PORT2             (0xffffU)
#define DIO_MASK_ALL_PINS_PORT3             (0x0000U)
#define DIO_MASK_ALL_PINS_PORT4             (0x0000U)
#define DIO_MASK_ALL_PINS_PORT5             (0x0000U)
#define DIO_MASK_ALL_PINS_PORT6             (0x0000U)
#define DIO_MASK_ALL_PINS_PORT7             (0x0000U)
#define DIO_MASK_ALL_PINS_PORT8             (0x0000U)
#define DIO_MASK_ALL_PINS_PORT9             (0x0000U)
#define DIO_MASK_ALL_PINS_PORT10             (0xefffU)
#define DIO_MASK_ALL_PINS_PORT11             (0xffffU)
#define DIO_MASK_ALL_PINS_PORT12             (0x0003U)
#define DIO_MASK_ALL_PINS_PORT13             (0xfeffU)
#define DIO_MASK_ALL_PINS_PORT14             (0xffffU)
#define DIO_MASK_ALL_PINS_PORT15             (0xfdffU)
#define DIO_MASK_ALL_PINS_PORT16             (0x0000U)
#define DIO_MASK_ALL_PINS_PORT17             (0x0000U)
#define DIO_MASK_ALL_PINS_PORT18             (0x0000U)
#define DIO_MASK_ALL_PINS_PORT19             (0x0000U)
#define DIO_MASK_ALL_PINS_PORT20             (0x7fcfU)
#define DIO_MASK_ALL_PINS_PORT21             (0x00ffU)
#define DIO_MASK_ALL_PINS_PORT22             (0x0fffU)
#define DIO_MASK_ALL_PINS_PORT23             (0x00ffU)
#define DIO_MASK_ALL_PINS_PORT24             (0xffffU)
#define DIO_MASK_ALL_PINS_PORT25             (0xffffU)
#define DIO_MASK_ALL_PINS_PORT26             (0x0001U)
#define DIO_MASK_ALL_PINS_PORT27             (0x0000U)
#define DIO_MASK_ALL_PINS_PORT28             (0x0000U)
#define DIO_MASK_ALL_PINS_PORT29             (0x0000U)
#define DIO_MASK_ALL_PINS_PORT30             (0xffffU)
#define DIO_MASK_ALL_PINS_PORT31             (0xffffU)
#define DIO_MASK_ALL_PINS_PORT32             (0x00ffU)
#define DIO_MASK_ALL_PINS_PORT33             (0xffffU)
#define DIO_MASK_ALL_PINS_PORT34             (0x003eU)
#define DIO_MASK_ALL_PINS_PORT35             (0x0000U)
#define DIO_MASK_ALL_PINS_PORT36             (0x0000U)
#define DIO_MASK_ALL_PINS_PORT37             (0x0000U)
#define DIO_MASK_ALL_PINS_PORT38             (0x0000U)
#define DIO_MASK_ALL_PINS_PORT39             (0x0000U)
#define DIO_MASK_ALL_PINS_PORT40             (0xffffU)
#define DIO_MASK_ALL_PINS_PORT41             (0x01ffU)

#define DIO_MAX_VALID_PORT_PIN_ID                  (0x298U)

/* Macro to define the No of channel groups configured */
#define DIO_CHANNELGROUPCOUNT               (1U)


/*******************************************************************************
**                           Global Symbols                                   **
*******************************************************************************/

/*
Symbolic names for DIO Channels, Port & Channel groups
*/

/*
Symbolic names for Channels
*/
#define DIO_CHANNEL_0_0                    ((Dio_ChannelType)0x000)
#define DIO_CHANNEL_0_1                    ((Dio_ChannelType)0x001)
#define DIO_CHANNEL_0_2                    ((Dio_ChannelType)0x002)
#define DIO_CHANNEL_0_3                    ((Dio_ChannelType)0x003)
#define DIO_CHANNEL_0_4                    ((Dio_ChannelType)0x004)
#define DIO_CHANNEL_0_5                    ((Dio_ChannelType)0x005)
#define DIO_CHANNEL_0_6                    ((Dio_ChannelType)0x006)
#define DIO_CHANNEL_0_7                    ((Dio_ChannelType)0x007)
#define DIO_CHANNEL_0_8                    ((Dio_ChannelType)0x008)
#define DIO_CHANNEL_0_9                    ((Dio_ChannelType)0x009)
#define DIO_CHANNEL_0_10                    ((Dio_ChannelType)0x00a)
#define DIO_CHANNEL_0_11                    ((Dio_ChannelType)0x00b)
#define DIO_CHANNEL_0_12                    ((Dio_ChannelType)0x00c)
#define DIO_CHANNEL_0_13                    ((Dio_ChannelType)0x00d)
#define DIO_CHANNEL_0_14                    ((Dio_ChannelType)0x00e)
#define DIO_CHANNEL_0_15                    ((Dio_ChannelType)0x00f)
#define DIO_CHANNEL_1_0                    ((Dio_ChannelType)0x010)
#define DIO_CHANNEL_1_1                    ((Dio_ChannelType)0x011)
#define DIO_CHANNEL_1_2                    ((Dio_ChannelType)0x012)
#define DIO_CHANNEL_1_3                    ((Dio_ChannelType)0x013)
#define DIO_CHANNEL_1_4                    ((Dio_ChannelType)0x014)
#define DIO_CHANNEL_1_5                    ((Dio_ChannelType)0x015)
#define DIO_CHANNEL_1_6                    ((Dio_ChannelType)0x016)
#define DIO_CHANNEL_1_7                    ((Dio_ChannelType)0x017)
#define DIO_CHANNEL_1_8                    ((Dio_ChannelType)0x018)
#define DIO_CHANNEL_1_9                    ((Dio_ChannelType)0x019)
#define DIO_CHANNEL_1_10                    ((Dio_ChannelType)0x01a)
#define DIO_CHANNEL_1_11                    ((Dio_ChannelType)0x01b)
#define DIO_CHANNEL_1_12                    ((Dio_ChannelType)0x01c)
#define DIO_CHANNEL_1_13                    ((Dio_ChannelType)0x01d)
#define DIO_CHANNEL_1_14                    ((Dio_ChannelType)0x01e)
#define DIO_CHANNEL_1_15                    ((Dio_ChannelType)0x01f)
#define DIO_CHANNEL_2_0                    ((Dio_ChannelType)0x020)
#define DIO_CHANNEL_2_1                    ((Dio_ChannelType)0x021)
#define DIO_CHANNEL_2_2                    ((Dio_ChannelType)0x022)
#define DIO_CHANNEL_2_3                    ((Dio_ChannelType)0x023)
#define DIO_CHANNEL_2_4                    ((Dio_ChannelType)0x024)
#define DIO_CHANNEL_2_5                    ((Dio_ChannelType)0x025)
#define DIO_CHANNEL_2_6                    ((Dio_ChannelType)0x026)
#define DIO_CHANNEL_2_7                    ((Dio_ChannelType)0x027)
#define DIO_CHANNEL_2_8                    ((Dio_ChannelType)0x028)
#define DIO_CHANNEL_2_9                    ((Dio_ChannelType)0x029)
#define DIO_CHANNEL_2_10                    ((Dio_ChannelType)0x02a)
#define DIO_CHANNEL_2_11                    ((Dio_ChannelType)0x02b)
#define DIO_CHANNEL_2_12                    ((Dio_ChannelType)0x02c)
#define DIO_CHANNEL_2_13                    ((Dio_ChannelType)0x02d)
#define DIO_CHANNEL_2_14                    ((Dio_ChannelType)0x02e)
#define DIO_CHANNEL_2_15                    ((Dio_ChannelType)0x02f)
#define DIO_CHANNEL_10_0                    ((Dio_ChannelType)0x0a0)
#define DIO_CHANNEL_10_1                    ((Dio_ChannelType)0x0a1)
#define DIO_CHANNEL_10_2                    ((Dio_ChannelType)0x0a2)
#define DIO_CHANNEL_10_3                    ((Dio_ChannelType)0x0a3)
#define DIO_CHANNEL_10_4                    ((Dio_ChannelType)0x0a4)
#define DIO_CHANNEL_10_5                    ((Dio_ChannelType)0x0a5)
#define DIO_CHANNEL_10_6                    ((Dio_ChannelType)0x0a6)
#define DIO_CHANNEL_10_7                    ((Dio_ChannelType)0x0a7)
#define DIO_CHANNEL_10_8                    ((Dio_ChannelType)0x0a8)
#define DIO_CHANNEL_10_9                    ((Dio_ChannelType)0x0a9)
#define DIO_CHANNEL_10_10                    ((Dio_ChannelType)0x0aa)
#define DIO_CHANNEL_10_11                    ((Dio_ChannelType)0x0ab)
#define DIO_CHANNEL_10_13                    ((Dio_ChannelType)0x0ad)
#define DIO_CHANNEL_10_14                    ((Dio_ChannelType)0x0ae)
#define DIO_CHANNEL_10_15                    ((Dio_ChannelType)0x0af)
#define DIO_CHANNEL_11_0                    ((Dio_ChannelType)0x0b0)
#define DIO_CHANNEL_11_1                    ((Dio_ChannelType)0x0b1)
#define DIO_CHANNEL_11_2                    ((Dio_ChannelType)0x0b2)
#define DIO_CHANNEL_11_3                    ((Dio_ChannelType)0x0b3)
#define DIO_CHANNEL_11_4                    ((Dio_ChannelType)0x0b4)
#define DIO_CHANNEL_11_5                    ((Dio_ChannelType)0x0b5)
#define DIO_CHANNEL_11_6                    ((Dio_ChannelType)0x0b6)
#define DIO_CHANNEL_11_7                    ((Dio_ChannelType)0x0b7)
#define DIO_CHANNEL_11_8                    ((Dio_ChannelType)0x0b8)
#define DIO_CHANNEL_11_9                    ((Dio_ChannelType)0x0b9)
#define DIO_CHANNEL_11_10                    ((Dio_ChannelType)0x0ba)
#define DIO_CHANNEL_11_11                    ((Dio_ChannelType)0x0bb)
#define DIO_CHANNEL_11_12                    ((Dio_ChannelType)0x0bc)
#define DIO_CHANNEL_11_13                    ((Dio_ChannelType)0x0bd)
#define DIO_CHANNEL_11_14                    ((Dio_ChannelType)0x0be)
#define DIO_CHANNEL_11_15                    ((Dio_ChannelType)0x0bf)
#define DIO_CHANNEL_12_0                    ((Dio_ChannelType)0x0c0)
#define DIO_CHANNEL_12_1                    ((Dio_ChannelType)0x0c1)
#define DIO_CHANNEL_13_0                    ((Dio_ChannelType)0x0d0)
#define DIO_CHANNEL_13_1                    ((Dio_ChannelType)0x0d1)
#define DIO_CHANNEL_13_2                    ((Dio_ChannelType)0x0d2)
#define DIO_CHANNEL_13_3                    ((Dio_ChannelType)0x0d3)
#define DIO_CHANNEL_13_4                    ((Dio_ChannelType)0x0d4)
#define DIO_CHANNEL_13_5                    ((Dio_ChannelType)0x0d5)
#define DIO_CHANNEL_13_6                    ((Dio_ChannelType)0x0d6)
#define DIO_CHANNEL_13_7                    ((Dio_ChannelType)0x0d7)
#define DIO_CHANNEL_13_9                    ((Dio_ChannelType)0x0d9)
#define DIO_CHANNEL_13_10                    ((Dio_ChannelType)0x0da)
#define DIO_CHANNEL_13_11                    ((Dio_ChannelType)0x0db)
#define DIO_CHANNEL_13_12                    ((Dio_ChannelType)0x0dc)
#define DIO_CHANNEL_13_13                    ((Dio_ChannelType)0x0dd)
#define DIO_CHANNEL_13_14                    ((Dio_ChannelType)0x0de)
#define DIO_CHANNEL_13_15                    ((Dio_ChannelType)0x0df)
#define DIO_CHANNEL_14_0                    ((Dio_ChannelType)0x0e0)
#define DIO_CHANNEL_14_1                    ((Dio_ChannelType)0x0e1)
#define DIO_CHANNEL_14_2                    ((Dio_ChannelType)0x0e2)
#define DIO_CHANNEL_14_3                    ((Dio_ChannelType)0x0e3)
#define DIO_CHANNEL_14_4                    ((Dio_ChannelType)0x0e4)
#define DIO_CHANNEL_14_5                    ((Dio_ChannelType)0x0e5)
#define DIO_CHANNEL_14_6                    ((Dio_ChannelType)0x0e6)
#define DIO_CHANNEL_14_7                    ((Dio_ChannelType)0x0e7)
#define DIO_CHANNEL_14_8                    ((Dio_ChannelType)0x0e8)
#define DIO_CHANNEL_14_9                    ((Dio_ChannelType)0x0e9)
#define DIO_CHANNEL_14_10                    ((Dio_ChannelType)0x0ea)
#define DIO_CHANNEL_14_11                    ((Dio_ChannelType)0x0eb)
#define DIO_CHANNEL_14_12                    ((Dio_ChannelType)0x0ec)
#define DIO_CHANNEL_14_13                    ((Dio_ChannelType)0x0ed)
#define DIO_CHANNEL_14_14                    ((Dio_ChannelType)0x0ee)
#define DIO_CHANNEL_14_15                    ((Dio_ChannelType)0x0ef)
#define DIO_CHANNEL_15_0                    ((Dio_ChannelType)0x0f0)
#define DIO_CHANNEL_15_1                    ((Dio_ChannelType)0x0f1)
#define DIO_CHANNEL_15_2                    ((Dio_ChannelType)0x0f2)
#define DIO_CHANNEL_15_3                    ((Dio_ChannelType)0x0f3)
#define DIO_CHANNEL_15_4                    ((Dio_ChannelType)0x0f4)
#define DIO_CHANNEL_15_5                    ((Dio_ChannelType)0x0f5)
#define DIO_CHANNEL_15_6                    ((Dio_ChannelType)0x0f6)
#define DIO_CHANNEL_15_7                    ((Dio_ChannelType)0x0f7)
#define DIO_CHANNEL_15_8                    ((Dio_ChannelType)0x0f8)
#define DIO_CHANNEL_15_10                    ((Dio_ChannelType)0x0fa)
#define DIO_CHANNEL_15_11                    ((Dio_ChannelType)0x0fb)
#define DIO_CHANNEL_15_12                    ((Dio_ChannelType)0x0fc)
#define DIO_CHANNEL_15_13                    ((Dio_ChannelType)0x0fd)
#define DIO_CHANNEL_15_14                    ((Dio_ChannelType)0x0fe)
#define DIO_CHANNEL_15_15                    ((Dio_ChannelType)0x0ff)
#define DIO_CHANNEL_20_0                    ((Dio_ChannelType)0x140)
#define DIO_CHANNEL_20_1                    ((Dio_ChannelType)0x141)
#define DIO_CHANNEL_20_2                    ((Dio_ChannelType)0x142)
#define DIO_CHANNEL_20_3                    ((Dio_ChannelType)0x143)
#define DIO_CHANNEL_20_6                    ((Dio_ChannelType)0x146)
#define DIO_CHANNEL_20_7                    ((Dio_ChannelType)0x147)
#define DIO_CHANNEL_20_8                    ((Dio_ChannelType)0x148)
#define DIO_CHANNEL_20_9                    ((Dio_ChannelType)0x149)
#define DIO_CHANNEL_20_10                    ((Dio_ChannelType)0x14a)
#define DIO_CHANNEL_20_11                    ((Dio_ChannelType)0x14b)
#define DIO_CHANNEL_20_12                    ((Dio_ChannelType)0x14c)
#define DIO_CHANNEL_20_13                    ((Dio_ChannelType)0x14d)
#define DIO_CHANNEL_20_14                    ((Dio_ChannelType)0x14e)
#define DIO_CHANNEL_21_0                    ((Dio_ChannelType)0x150)
#define DIO_CHANNEL_21_1                    ((Dio_ChannelType)0x151)
#define DIO_CHANNEL_21_2                    ((Dio_ChannelType)0x152)
#define DIO_CHANNEL_21_3                    ((Dio_ChannelType)0x153)
#define DIO_CHANNEL_21_4                    ((Dio_ChannelType)0x154)
#define DIO_CHANNEL_21_5                    ((Dio_ChannelType)0x155)
#define DIO_CHANNEL_21_6                    ((Dio_ChannelType)0x156)
#define DIO_CHANNEL_21_7                    ((Dio_ChannelType)0x157)
#define DIO_CHANNEL_22_0                    ((Dio_ChannelType)0x160)
#define DIO_CHANNEL_22_1                    ((Dio_ChannelType)0x161)
#define DIO_CHANNEL_22_2                    ((Dio_ChannelType)0x162)
#define DIO_CHANNEL_22_3                    ((Dio_ChannelType)0x163)
#define DIO_CHANNEL_22_4                    ((Dio_ChannelType)0x164)
#define DIO_CHANNEL_22_5                    ((Dio_ChannelType)0x165)
#define DIO_CHANNEL_22_6                    ((Dio_ChannelType)0x166)
#define DIO_CHANNEL_22_7                    ((Dio_ChannelType)0x167)
#define DIO_CHANNEL_22_8                    ((Dio_ChannelType)0x168)
#define DIO_CHANNEL_22_9                    ((Dio_ChannelType)0x169)
#define DIO_CHANNEL_22_10                    ((Dio_ChannelType)0x16a)
#define DIO_CHANNEL_22_11                    ((Dio_ChannelType)0x16b)
#define DIO_CHANNEL_23_0                    ((Dio_ChannelType)0x170)
#define DIO_CHANNEL_23_1                    ((Dio_ChannelType)0x171)
#define DIO_CHANNEL_23_2                    ((Dio_ChannelType)0x172)
#define DIO_CHANNEL_23_3                    ((Dio_ChannelType)0x173)
#define DIO_CHANNEL_23_4                    ((Dio_ChannelType)0x174)
#define DIO_CHANNEL_23_5                    ((Dio_ChannelType)0x175)
#define DIO_CHANNEL_23_6                    ((Dio_ChannelType)0x176)
#define DIO_CHANNEL_23_7                    ((Dio_ChannelType)0x177)
#define DIO_CHANNEL_24_0                    ((Dio_ChannelType)0x180)
#define DIO_CHANNEL_24_1                    ((Dio_ChannelType)0x181)
#define DIO_CHANNEL_24_2                    ((Dio_ChannelType)0x182)
#define DIO_CHANNEL_24_3                    ((Dio_ChannelType)0x183)
#define DIO_CHANNEL_24_4                    ((Dio_ChannelType)0x184)
#define DIO_CHANNEL_24_5                    ((Dio_ChannelType)0x185)
#define DIO_CHANNEL_24_6                    ((Dio_ChannelType)0x186)
#define DIO_CHANNEL_24_7                    ((Dio_ChannelType)0x187)
#define DIO_CHANNEL_24_8                    ((Dio_ChannelType)0x188)
#define DIO_CHANNEL_24_9                    ((Dio_ChannelType)0x189)
#define DIO_CHANNEL_24_10                    ((Dio_ChannelType)0x18a)
#define DIO_CHANNEL_24_11                    ((Dio_ChannelType)0x18b)
#define DIO_CHANNEL_24_12                    ((Dio_ChannelType)0x18c)
#define DIO_CHANNEL_24_13                    ((Dio_ChannelType)0x18d)
#define DIO_CHANNEL_24_14                    ((Dio_ChannelType)0x18e)
#define DIO_CHANNEL_24_15                    ((Dio_ChannelType)0x18f)
#define DIO_CHANNEL_25_0                    ((Dio_ChannelType)0x190)
#define DIO_CHANNEL_25_1                    ((Dio_ChannelType)0x191)
#define DIO_CHANNEL_25_2                    ((Dio_ChannelType)0x192)
#define DIO_CHANNEL_25_3                    ((Dio_ChannelType)0x193)
#define DIO_CHANNEL_25_4                    ((Dio_ChannelType)0x194)
#define DIO_CHANNEL_25_5                    ((Dio_ChannelType)0x195)
#define DIO_CHANNEL_25_6                    ((Dio_ChannelType)0x196)
#define DIO_CHANNEL_25_7                    ((Dio_ChannelType)0x197)
#define DIO_CHANNEL_25_8                    ((Dio_ChannelType)0x198)
#define DIO_CHANNEL_25_9                    ((Dio_ChannelType)0x199)
#define DIO_CHANNEL_25_10                    ((Dio_ChannelType)0x19a)
#define DIO_CHANNEL_25_11                    ((Dio_ChannelType)0x19b)
#define DIO_CHANNEL_25_12                    ((Dio_ChannelType)0x19c)
#define DIO_CHANNEL_25_13                    ((Dio_ChannelType)0x19d)
#define DIO_CHANNEL_25_14                    ((Dio_ChannelType)0x19e)
#define DIO_CHANNEL_25_15                    ((Dio_ChannelType)0x19f)
#define DIO_CHANNEL_26_0                    ((Dio_ChannelType)0x1a0)
#define DIO_CHANNEL_30_0                    ((Dio_ChannelType)0x1e0)
#define DIO_CHANNEL_30_1                    ((Dio_ChannelType)0x1e1)
#define DIO_CHANNEL_30_2                    ((Dio_ChannelType)0x1e2)
#define DIO_CHANNEL_30_3                    ((Dio_ChannelType)0x1e3)
#define DIO_CHANNEL_30_4                    ((Dio_ChannelType)0x1e4)
#define DIO_CHANNEL_30_5                    ((Dio_ChannelType)0x1e5)
#define DIO_CHANNEL_30_6                    ((Dio_ChannelType)0x1e6)
#define DIO_CHANNEL_30_7                    ((Dio_ChannelType)0x1e7)
#define DIO_CHANNEL_30_8                    ((Dio_ChannelType)0x1e8)
#define DIO_CHANNEL_30_9                    ((Dio_ChannelType)0x1e9)
#define DIO_CHANNEL_30_10                    ((Dio_ChannelType)0x1ea)
#define DIO_CHANNEL_30_11                    ((Dio_ChannelType)0x1eb)
#define DIO_CHANNEL_30_12                    ((Dio_ChannelType)0x1ec)
#define DIO_CHANNEL_30_13                    ((Dio_ChannelType)0x1ed)
#define DIO_CHANNEL_30_14                    ((Dio_ChannelType)0x1ee)
#define DIO_CHANNEL_30_15                    ((Dio_ChannelType)0x1ef)
#define DIO_CHANNEL_31_0                    ((Dio_ChannelType)0x1f0)
#define DIO_CHANNEL_31_1                    ((Dio_ChannelType)0x1f1)
#define DIO_CHANNEL_31_2                    ((Dio_ChannelType)0x1f2)
#define DIO_CHANNEL_31_3                    ((Dio_ChannelType)0x1f3)
#define DIO_CHANNEL_31_4                    ((Dio_ChannelType)0x1f4)
#define DIO_CHANNEL_31_5                    ((Dio_ChannelType)0x1f5)
#define DIO_CHANNEL_31_6                    ((Dio_ChannelType)0x1f6)
#define DIO_CHANNEL_31_7                    ((Dio_ChannelType)0x1f7)
#define DIO_CHANNEL_31_8                    ((Dio_ChannelType)0x1f8)
#define DIO_CHANNEL_31_9                    ((Dio_ChannelType)0x1f9)
#define DIO_CHANNEL_31_10                    ((Dio_ChannelType)0x1fa)
#define DIO_CHANNEL_31_11                    ((Dio_ChannelType)0x1fb)
#define DIO_CHANNEL_31_12                    ((Dio_ChannelType)0x1fc)
#define DIO_CHANNEL_31_13                    ((Dio_ChannelType)0x1fd)
#define DIO_CHANNEL_31_14                    ((Dio_ChannelType)0x1fe)
#define DIO_CHANNEL_31_15                    ((Dio_ChannelType)0x1ff)
#define DIO_CHANNEL_32_0                    ((Dio_ChannelType)0x200)
#define DIO_CHANNEL_32_1                    ((Dio_ChannelType)0x201)
#define DIO_CHANNEL_32_2                    ((Dio_ChannelType)0x202)
#define DIO_CHANNEL_32_3                    ((Dio_ChannelType)0x203)
#define DIO_CHANNEL_32_4                    ((Dio_ChannelType)0x204)
#define DIO_CHANNEL_32_5                    ((Dio_ChannelType)0x205)
#define DIO_CHANNEL_32_6                    ((Dio_ChannelType)0x206)
#define DIO_CHANNEL_32_7                    ((Dio_ChannelType)0x207)
#define DIO_CHANNEL_33_0                    ((Dio_ChannelType)0x210)
#define DIO_CHANNEL_33_1                    ((Dio_ChannelType)0x211)
#define DIO_CHANNEL_33_2                    ((Dio_ChannelType)0x212)
#define DIO_CHANNEL_33_3                    ((Dio_ChannelType)0x213)
#define DIO_CHANNEL_33_4                    ((Dio_ChannelType)0x214)
#define DIO_CHANNEL_33_5                    ((Dio_ChannelType)0x215)
#define DIO_CHANNEL_33_6                    ((Dio_ChannelType)0x216)
#define DIO_CHANNEL_33_7                    ((Dio_ChannelType)0x217)
#define DIO_CHANNEL_33_8                    ((Dio_ChannelType)0x218)
#define DIO_CHANNEL_33_9                    ((Dio_ChannelType)0x219)
#define DIO_CHANNEL_33_10                    ((Dio_ChannelType)0x21a)
#define DIO_CHANNEL_33_11                    ((Dio_ChannelType)0x21b)
#define DIO_CHANNEL_33_12                    ((Dio_ChannelType)0x21c)
#define DIO_CHANNEL_33_13                    ((Dio_ChannelType)0x21d)
#define DIO_CHANNEL_33_14                    ((Dio_ChannelType)0x21e)
#define DIO_CHANNEL_33_15                    ((Dio_ChannelType)0x21f)
#define DIO_CHANNEL_34_1                    ((Dio_ChannelType)0x221)
#define DIO_CHANNEL_34_2                    ((Dio_ChannelType)0x222)
#define DIO_CHANNEL_34_3                    ((Dio_ChannelType)0x223)
#define DIO_CHANNEL_34_4                    ((Dio_ChannelType)0x224)
#define DIO_CHANNEL_34_5                    ((Dio_ChannelType)0x225)
#define DIO_CHANNEL_40_0                    ((Dio_ChannelType)0x280)
#define DIO_CHANNEL_40_1                    ((Dio_ChannelType)0x281)
#define DIO_CHANNEL_40_2                    ((Dio_ChannelType)0x282)
#define DIO_CHANNEL_40_3                    ((Dio_ChannelType)0x283)
#define DIO_CHANNEL_40_4                    ((Dio_ChannelType)0x284)
#define DIO_CHANNEL_40_5                    ((Dio_ChannelType)0x285)
#define DIO_CHANNEL_40_6                    ((Dio_ChannelType)0x286)
#define DIO_CHANNEL_40_7                    ((Dio_ChannelType)0x287)
#define DIO_CHANNEL_40_8                    ((Dio_ChannelType)0x288)
#define DIO_CHANNEL_40_9                    ((Dio_ChannelType)0x289)
#define DIO_CHANNEL_40_10                    ((Dio_ChannelType)0x28a)
#define DIO_CHANNEL_40_11                    ((Dio_ChannelType)0x28b)
#define DIO_CHANNEL_40_12                    ((Dio_ChannelType)0x28c)
#define DIO_CHANNEL_40_13                    ((Dio_ChannelType)0x28d)
#define DIO_CHANNEL_40_14                    ((Dio_ChannelType)0x28e)
#define DIO_CHANNEL_40_15                    ((Dio_ChannelType)0x28f)
#define DIO_CHANNEL_41_0                    ((Dio_ChannelType)0x290)
#define DIO_CHANNEL_41_1                    ((Dio_ChannelType)0x291)
#define DIO_CHANNEL_41_2                    ((Dio_ChannelType)0x292)
#define DIO_CHANNEL_41_3                    ((Dio_ChannelType)0x293)
#define DIO_CHANNEL_41_4                    ((Dio_ChannelType)0x294)
#define DIO_CHANNEL_41_5                    ((Dio_ChannelType)0x295)
#define DIO_CHANNEL_41_6                    ((Dio_ChannelType)0x296)
#define DIO_CHANNEL_41_7                    ((Dio_ChannelType)0x297)
#define DIO_CHANNEL_41_8                    ((Dio_ChannelType)0x298)
/*
Symbolic names for DIO ports
*/
#define DIO_PORT_0                          ((Dio_PortType)0)
#define DIO_PORT_1                          ((Dio_PortType)1)
#define DIO_PORT_2                          ((Dio_PortType)2)
#define DIO_PORT_10                          ((Dio_PortType)10)
#define DIO_PORT_11                          ((Dio_PortType)11)
#define DIO_PORT_12                          ((Dio_PortType)12)
#define DIO_PORT_13                          ((Dio_PortType)13)
#define DIO_PORT_14                          ((Dio_PortType)14)
#define DIO_PORT_15                          ((Dio_PortType)15)
#define DIO_PORT_20                          ((Dio_PortType)20)
#define DIO_PORT_21                          ((Dio_PortType)21)
#define DIO_PORT_22                          ((Dio_PortType)22)
#define DIO_PORT_23                          ((Dio_PortType)23)
#define DIO_PORT_24                          ((Dio_PortType)24)
#define DIO_PORT_25                          ((Dio_PortType)25)
#define DIO_PORT_26                          ((Dio_PortType)26)
#define DIO_PORT_30                          ((Dio_PortType)30)
#define DIO_PORT_31                          ((Dio_PortType)31)
#define DIO_PORT_32                          ((Dio_PortType)32)
#define DIO_PORT_33                          ((Dio_PortType)33)
#define DIO_PORT_34                          ((Dio_PortType)34)
#define DIO_PORT_40                          ((Dio_PortType)40)
#define DIO_PORT_41                          ((Dio_PortType)41)

/*
User Defined Symbolic Names for the DIO Ports, Channels & Channel Groups
*/
/*
DIO PORT : (DioPort_0)
*/
#ifndef DioConf_DioPort_DioPort_0
#define DioConf_DioPort_DioPort_0 (DIO_PORT_33)
#endif
/* DIO Channel : (DioChannel_LED) */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
#ifndef DioConf_DioChannel_DioChannel_LED
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
#define DioConf_DioChannel_DioChannel_LED (DIO_CHANNEL_33_5)
#endif
/* DIO Channel : (DioChannel_1) */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
#ifndef DioConf_DioChannel_DioChannel_1
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
#define DioConf_DioChannel_DioChannel_1 (DIO_CHANNEL_33_6)
#endif
/* DIO Channel : (DioChannel_2) */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
#ifndef DioConf_DioChannel_DioChannel_2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
#define DioConf_DioChannel_DioChannel_2 (DIO_CHANNEL_33_7)
#endif
/* DIO Channel : (STB2) */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
#ifndef DioConf_DioChannel_STB2
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
#define DioConf_DioChannel_STB2 (DIO_CHANNEL_33_10)
#endif
/*DIO Channel Group : DioChGrpId_P33_0*/
/* To prevent double declaration */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
#ifndef DioConf_DioChannelGroup_DioChannelGroup_LED
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
#define DioConf_DioChannelGroup_DioChannelGroup_LED (&Dio_Config.Dio_ChannelGroupConfigPtr[0])
#endif
/*
DIO PORT : (DioPort_1)
*/
#ifndef DioConf_DioPort_DioPort_1
#define DioConf_DioPort_DioPort_1 (DIO_PORT_20)
#endif
/* DIO Channel : (TRB_LED) */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
#ifndef DioConf_DioChannel_TRB_LED
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
#define DioConf_DioChannel_TRB_LED (DIO_CHANNEL_20_11)
#endif
/*
DIO PORT : (DioPort_2)
*/
#ifndef DioConf_DioPort_DioPort_2
#define DioConf_DioPort_DioPort_2 (DIO_PORT_2)
#endif
/* DIO Channel : (OCU_CHANNEL_PIN) */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
#ifndef DioConf_DioChannel_OCU_CHANNEL_PIN
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
#define DioConf_DioChannel_OCU_CHANNEL_PIN (DIO_CHANNEL_2_5)
#endif
/*
DIO PORT : (DioPort_3)
*/
#ifndef DioConf_DioPort_DioPort_3
#define DioConf_DioPort_DioPort_3 (DIO_PORT_10)
#endif
/* DIO Channel : (STB) */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
#ifndef DioConf_DioChannel_STB
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers are defined
according to requirement ecuc_sws_2108*/
#define DioConf_DioChannel_STB (DIO_CHANNEL_10_6)
#endif



/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/
#define DIO_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
#include "Dio_MemMap.h"

extern const struct Dio_ConfigType Dio_Config; 
#define DIO_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines 
Dio_Memmap.h header is included without safegaurd.*/
#include "Dio_MemMap.h"
/*******************************************************************************
**                      Global Data Type                                      **
*******************************************************************************/
/* End of DIO_CFG_H */
#endif

