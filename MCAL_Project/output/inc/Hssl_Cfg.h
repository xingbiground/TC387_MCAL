/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2017)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Hssl_Cfg.h                                                    **
**                                                                            **
**  VERSION   : 4.0.0                                                         **
**                                                                            **
**  DATE, TIME: 2023-11-11, 18:16:26      !!!IGNORE-LINE!!!                   **
**                                                                            **
**  GENERATOR : Build b200227-0222         !!!IGNORE-LINE!!!                  **
**                                                                            **
**  BSW MODULE DECRIPTION : NA                                                **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Hssl configuration generated out of ECUC file              **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef HSSL_CFG_H
#define HSSL_CFG_H
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/* Vendor specific implementation version information */
#define HSSL_SW_MAJOR_VERSION   (10U)
#define HSSL_SW_MINOR_VERSION   (40U)
#define HSSL_SW_PATCH_VERSION   (2U)

#define HSSL_MASTER               (0U)
#define HSSL_SLAVE                (1U)
#define HSSL_NO_ACCESS            (0U)
#define HSSL_READ_ACCESS          (1U)
#define HSSL_WRITE_ACCESS         (2U)
#define HSSL_READ_WRITE_ACCESS    (3U)
#define HSSL_REFCLK_10MHZ (0U)
#define HSSL_REFCLK_20MHZ (1U)
#define HSSL_REFCLK_40MHZ (2U)
#define HSSL_SYSCLK_DIV_1 (0U)
#define HSSL_SYSCLK_DIV_2 (1U)
#define HSSL_SYSCLK_DIV_4 (2U)
#define HSSL_TX_LOW_SPEED (0U)
#define HSSL_TX_HIGH_SPEED (2U)
#define HSSL_RX_LOW_SPEED (0U)
#define HSSL_RX_MEDIUM_SPEED (1U)
#define HSSL_RX_HIGH_SPEED (2U)
#define HSSL_POLLING_MODE (0U)
#define HSSL_INTERUPT_MODE (1U)

/*
Configuration: HSSL_DEV_ERROR_DETECT
- if STD_ON, DET is Enabled
- if STD_OFF,DET is Disabled
If the switch HSSL_DEV_ERROR_DETECT is enabled API parameter checking
is also enabled.
*/
#define HSSL_DEV_ERROR_DETECT  (STD_OFF)

#define HSSL_INTERFACE_MODE   (HSSL_MASTER)
#define HSSL_SYSTEM_CLOCK   (STD_ON)

#define HSSL_OPERATING_MODE   (HSSL_POLLING_MODE)

/* clok pre divider value for HSSL */
#define HSSL_CLOCK_PREDIVIDER  (0xffU)

/* Configurred HSSL Instances */
#define HSSL_NUM_INSTANCES_CONFIGURRED  (1U)
#define HSSL0_CONFIGURRED STD_ON
#define HSSL1_CONFIGURRED STD_OFF
#define HSSL_CH2_STREAMING       (1U)
#define HSSL_CH2_COMMAND         (0U)

/* Configurring the Channel-2 as Stream Mode/Command Mode */
#define HSSL0_STREAMING_CH_MODE  (HSSL_CH2_COMMAND)

/* Configurring the Channel-2 Transmitter as Single/Continuous Block mode */
#define  HSSL_STREAMING_MODE_CONTINOUS     (0U)
#define  HSSL_STREAMING_MODE_SINGLE        (1U)
#define HSSL0_STREAMING_MODE_TX  (HSSL_STREAMING_MODE_CONTINOUS)

#define HSSL0_EXI_HANDLE_CALLBACK          NULL_PTR

#define HSSL0_CH0_WRITE_HANDLE_CALLBACK          NULL_PTR

#define HSSL0_CH1_WRITE_HANDLE_CALLBACK          NULL_PTR

#define HSSL0_CH2_WRITE_HANDLE_CALLBACK          NULL_PTR

#define HSSL0_CH3_WRITE_HANDLE_CALLBACK          NULL_PTR

#define HSSL0_CH0_READ_HANDLE_CALLBACK          NULL_PTR

#define HSSL0_CH1_READ_HANDLE_CALLBACK          NULL_PTR

#define HSSL0_CH2_READ_HANDLE_CALLBACK          NULL_PTR

#define HSSL0_CH3_READ_HANDLE_CALLBACK          NULL_PTR

#define HSSL0_CH0_TRIGGER_HANDLE_CALLBACK          NULL_PTR

#define HSSL0_CH1_TRIGGER_HANDLE_CALLBACK          NULL_PTR

#define HSSL0_CH2_TRIGGER_HANDLE_CALLBACK          NULL_PTR

#define HSSL0_CH3_TRIGGER_HANDLE_CALLBACK          NULL_PTR

#define HSSL0_CH0_ERROR_HANDLE_CALLBACK          NULL_PTR

#define HSSL0_CH1_ERROR_HANDLE_CALLBACK          NULL_PTR

#define HSSL0_CH2_ERROR_HANDLE_CALLBACK          NULL_PTR

#define HSSL0_CH3_ERROR_HANDLE_CALLBACK          NULL_PTR

#define HSSL0_DMA_MULTIREAD_CALLBACK          NULL_PTR

#define HSSL0_DMA_MULTIWRITE_CALLBACK          NULL_PTR

/* Configurring the Channel-2 Receiver as Single/Continuous Block mode */
#define HSSL0_STREAMING_MODE_RX  (HSSL_STREAMING_MODE_CONTINOUS)

/* Configuration: HSSL_VERSION_INFO_API
HSSL Enable/Disable version information API
- if STD_ON, Enables Version Info API
- if STD_OFF, Disables Version Info API
*/
#define HSSL_VERSION_INFO_API  (STD_OFF)

/*
Configuration: HSSL_RUNNING_IN_USER_0_MODE_ENABLE
- if STD_ON, enable User0 mode
- if STD_OFF, enable User1 mode
*/
#define HSSL_SUPERVISOR_MODE                   (STD_ON)
#define HSSL_USER_MODE                         (STD_OFF)
#define HSSL_INIT_API_MODE              HSSL_SUPERVISOR_MODE
#define HSSL_RUN_TIME_API_MODE                 HSSL_SUPERVISOR_MODE
#define HSSL_MULTI_SLAVE_MODE  (STD_OFF)

/* Address pointer containing the address of the memory
location containing the unique ID data */
#define HSSL0_TIDADD_ADDR  (0x0U)

/* DMA Transmit Channel Used for Multi Write */
#define HSSL0_DMA_MULTI_WRITE_CHANNEL_USED          (3U)
#define HSSL_DMA_MULTI_WRITE_CHANNEL HSSL0_DMA_MULTI_WRITE_CHANNEL_USED

/* DMA Transmit Channel Used for Multi Write/multi read */
#define HSSL0_DMA_MULTI_READ_TX_CHANNEL_USED          (4U)
#define HSSL_DMA_MULTI_READ_TX_CHANNEL HSSL0_DMA_MULTI_READ_TX_CHANNEL_USED

/* DMA receive Channel Used for Multi Write/multi read */
#define HSSL0_DMA_MULTI_READ_RX_CHANNEL_USED          (5U)
#define HSSL_DMA_MULTI_READ_RX_CHANNEL HSSL0_DMA_MULTI_READ_RX_CHANNEL_USED

/* Memory Access Window and Protection Window definitions for HSSL */
#define HSSL0_ACCESS_WINDOW_START_ADDR0 (0x0U)
#define HSSL0_ACCESS_WINDOW_START_ADDR1 (0x0U)
#define HSSL0_ACCESS_WINDOW_START_ADDR2 (0x0U)
#define HSSL0_ACCESS_WINDOW_START_ADDR3 (0x0U)
#define HSSL0_ACCESS_WINDOW_END_ADDR0 (0x0U)
#define HSSL0_ACCESS_WINDOW_END_ADDR1 (0x0U)
#define HSSL0_ACCESS_WINDOW_END_ADDR2 (0x0U)
#define HSSL0_ACCESS_WINDOW_END_ADDR3 (0x0U)


#define HSSL0_ACCESS_MODE_0   (HSSL_NO_ACCESS)

#define HSSL0_ACCESS_MODE_1   (HSSL_NO_ACCESS)

#define HSSL0_ACCESS_MODE_2   (HSSL_NO_ACCESS)

#define HSSL0_ACCESS_MODE_3   (HSSL_NO_ACCESS)

#define HSSL0_REFRENCE_CLK   (HSSL_REFCLK_20MHZ)

#define HSSL0_SYSCLK_DIV   (HSSL_SYSCLK_DIV_1)

#define HSSL0_MASTER_TX_SPEED   (HSSL_TX_LOW_SPEED)

#define HSSL0_MASTER_RX_SPEED   (HSSL_RX_LOW_SPEED)
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
#endif /* end of HSSL_CFG_H */
