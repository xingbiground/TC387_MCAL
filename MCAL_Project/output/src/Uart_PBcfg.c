
/******************************************************************************
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
**  FILENAME  : Uart_PBcfg.c                                                  **
**                                                                            **
**  VERSION   : 14.0.0                                                        **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:30  !!!IGNORE-LINE!!!                   **
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
**                                                  AUTOSAR Release 4.4.0     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/* [cover parentID={708D1F23-55ED-4ea8-9FC9-11E6F663FDEF}]
[/cover] */
/******************************************************************************
**                      Includes                                             **
******************************************************************************/
/* Include UART Module File */
#include "Uart.h"

/******************************************************************************
**                      Private Macro Definitions                            **
******************************************************************************/
/******************************************************************************
**                      Imported Compiler Switch Check                       **
******************************************************************************/
/******************************************************************************
**                      Private Type Definitions                             **
******************************************************************************/
/******************************************************************************
**                      Private Function Declarations                        **
******************************************************************************/
/******************************************************************************
**                      Global Constant Definitions                          **
******************************************************************************/
/******************************************************************************
**                      Extern Declaration                                   **
******************************************************************************/
/* [cover parentID={DB6AEAF8-1942-4dab-BAA6-C3A0AA2FC308}]
[/cover] */
/* Streaming notification function of UartChannel_0 */
extern void Streaming_Notification00(Uart_ErrorIdType ErrorId,Uart_SizeType RxDataSize);
/*
Container: UartConfigSet
*/
#define UART_START_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
/* [cover parentID={84FCEDA9-01F7-4f48-AC8B-47FFAF8417E4}] */
/*  [/cover] */
/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
* Const Section
* [/cover]*/
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
* Const Section
* [/cover]*/
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
* this is due to inclusion of memmap.h to specify the location to which
* the variable has to be placed. */
#include "Uart_MemMap.h"

/* [cover parentID={A876E15E-2536-4fe5-8E1B-C8BDD6893BDA}]
[/cover] */
/* [cover parentID={C13F0984-A501-47cd-AE26-25AA4A4DE269}]
[/cover] */
static const Uart_ChannelConfigType  Uart_ChannelConfig[1] =
{
  /* UART Channel ID: 0 Configuration */
  { /* Notification function */
    {
      /* Call-back notification function for write operation */
      NULL_PTR,
      /* Call-back notification function for read operation */
      NULL_PTR,
      /* Call-back notification function for abort write operation */
      NULL_PTR,
      /* Call-back notification function for abort read operation */
      NULL_PTR,
      /* Call-back notification function for streaming operation */
      &Streaming_Notification00,
    },
    /* BaudRate : 115200 Hz  */
    /* Channel baud rate numerator */
    288U,
    /* Channel baud rate denominator */
    1000U,
    /* Channel baud rate prescalar */
    4U,
    /* Channel oversampling */
    9U,
    /* Hardware channel id */
    UART_ASCLIN2,
    /* Number of stop Bits */
    1U,
    /* Frame length */
    8U,
    /* Alternate receive pin */
    UART_SELECT_A,
    /* Identifies the parity is enabled */
    0U,
    /* Identifies the parity is even or odd */
    0U,
    /* Alternate CTS pin */
    UART_SELECT_CTS_B,
    
    /* CTS is enabled */
    0U,
    /* RTS/CTS polarity if CTS is enabled */
    0U,
    /* Receive operation mode polling/interrupt */
    UART_INTERRUPT_MODE,
    /* Transmit operation mode polling/interrupt  */
    UART_INTERRUPT_MODE
  }
};
/* [cover parentID={1614ABEB-C055-42f9-90C1-009D55C1699C}]
[/cover] */
static const uint8 Uart_ChannelIdLookup[UART_MAX_HW_UNIT] =
{
  0xFFU,
  0xFFU,
  0U,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU,
  0xFFU};
/* [cover parentID={59DF25D6-EA51-4428-A68D-B42F8D3ACE82}]
[/cover] */
/* Uart configuration set */
const Uart_ConfigType Uart_Config =
{
  &Uart_ChannelConfig[0],
  &Uart_ChannelIdLookup[0],
  1U
};
#define UART_STOP_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
/* [cover parentID={84FCEDA9-01F7-4f48-AC8B-47FFAF8417E4}] */
/*  [/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
* this is due to inclusion of memmap.h to specify the location to which
* the variable has to be placed. */
#include "Uart_MemMap.h"

/******************************************************************************
**                      Global Variable Definitions                           *
******************************************************************************/
/******************************************************************************
**                      Private Constant Definitions                         **
******************************************************************************/
/******************************************************************************
**                      Private Variable Definitions                         **
******************************************************************************/
/******************************************************************************
**                      Global Function Definitions                          **
******************************************************************************/
/******************************************************************************
**                      Private Function Definitions                         **
******************************************************************************/
