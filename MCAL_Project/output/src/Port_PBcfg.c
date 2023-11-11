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
**  FILENAME  : Port_PBCfg.c                                                  **
**                                                                            **
**  VERSION   : 14.0.0                                                        **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:32          !!!IGNORE-LINE!!!               **
**                                                                            **
**  GENERATOR : Build b191017-0938            !!!IGNORE-LINE!!!               **
**                                                                            **
**  BSW MODULE DECRIPTION : Port.bmd                                          **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Port configuration generated out of ECUC file              **
**                                                                            **
**  SPECIFICATION(S) : Specification of Port Driver, AUTOSAR Release 4.2.2    **
**                     and AUTOSAR Release 4.4.0                              **
**                                                                            **
** MAY BE CHANGED BY USER : no                                                **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Inclusion of Port Header file */
#include "Port.h"

    
  /*******************************************************************************
  **                      Private Macro Definitions                             **
  *******************************************************************************/
  /* Macro definition for PORT pad drive control register Pn_PDR0 */
  /* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macros are used
  to calculate 32bit value for the register PDR0. This function like
  macro directly updates the register and reduces the code complexity
  and improves readability.*/
  #define  Portx_lPdrConfig1(Pd0,Pd1,Pd2,Pd3,Pd4,Pd5,Pd6,Pd7)                    \
  ( ((uint32)(Pd7) << (uint32)28) | ((uint32)(Pd6) << (uint32)24) |              \
  ((uint32)(Pd5) << (uint32)20) | ((uint32)(Pd4) << (uint32)16) |                \
  ((uint32)(Pd3) << (uint32)12) |  ((uint32)(Pd2) << (uint32)8)  |               \
  ((uint32)(Pd1) << (uint32)4)  | (uint32)(Pd0)                                  \
  )

  /* Macro definition for PORT pad drive control register Pn_PDR1 */
  /* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macros are used
  to calculate 32bit value for the register PDR1. This function like
  macro directly updates the register and reduces the code complexity
  and improves readability.*/
  #define  Portx_lPdrConfig2(Pd8,Pd9,Pd10,Pd11,Pd12,Pd13,Pd14,Pd15)              \
  ( ((uint32)(Pd15) << (uint32)28) | ((uint32)(Pd14) << (uint32)24) |            \
  ((uint32)(Pd13) << (uint32)20) | ((uint32)(Pd12) << (uint32)16) |              \
  ((uint32)(Pd11) << (uint32)12)|  ((uint32)(Pd10) << (uint32)8)  |              \
  ((uint32)(Pd9) << (uint32)4) | (uint32)(Pd8)                                   \
  )
  /* Macro definition for PORT Pad Disable Control Register */
  /* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macros are used
  to calculate register values. This function like macro directly
  updates the register and reduces the code complexity and improves
  readability.*/
    #define Port_lDiscSet(b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,b15) \
    ((uint16)(                                                                   \
    (uint32)(b0) | ((uint32)(b1) << (uint32)1) |                                 \
    ((uint32)(b2) << (uint32)2) | ((uint32)(b3) << (uint32)3) |                  \
    ((uint32)(b4) << (uint32)4) | ((uint32)(b5) << (uint32)5) |                  \
    ((uint32)(b6) << (uint32)6) | ((uint32)(b7) << (uint32)7) |                  \
    ((uint32)(b8) << (uint32)8) | ((uint32)(b9) << (uint32)9) |                  \
    ((uint32)(b10) << (uint32)10) | ((uint32)(b11) << (uint32)11) |              \
    ((uint32)(b12) << (uint32)12) | ((uint32)(b13)<< (uint32)13) |               \
    ((uint32)(b14) << (uint32)14) | ((uint32)(b15) << (uint32)15)                \
    ))
  /* Macro definition for PORT Pad Disable Control Register */
  /* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macros are used
  to calculate register values. This function like macro directly
  updates the register and reduces the code complexity and improves
  readability.*/
  #define Port_lPcsr(b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,b15)      \
  ((uint32)(                                                                     \
  ((uint32)(b0)) | ((uint32)(b1) << (uint32)1) |                                 \
  ((uint32)(b2) << (uint32)2) | ((uint32)(b3) << (uint32)3) |                    \
  ((uint32)(b4) << (uint32)4) | ((uint32)(b5) << (uint32)5) |                    \
  ((uint32)(b6) << (uint32)6) | ((uint32)(b7) << (uint32)7) |                    \
  ((uint32)(b8) << (uint32)8) | ((uint32)(b9) << (uint32)9) |                    \
  ((uint32)(b10) << (uint32)10) | ((uint32)(b11) << (uint32)11) |                \
  ((uint32)(b12) << (uint32)12) | ((uint32)(b13) << (uint32)13) |                \
  ((uint32)(b14) << (uint32)14) | ((uint32)(b15) << (uint32)15)                  \
  ))
  /* Macro definition for PORT LPCR register for LVDS */
  /* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macros are used
  to calculate register values. This function like macro directly
  updates the register and reduces the code complexity and improves
  readability.*/
    #define Port_lLvds(REN_CTRL,RX_EN,TERM,LRTXERM,LVDSM,PS,TEN_CTRL,TX_EN,\
    VIDFFADJ,VOSDYN,VOSEXT,TX_PD,TX_PWDPD)                                       \
    ((uint32)(                                                                   \
    ((uint32)(REN_CTRL)) | ((uint32)(RX_EN) << (uint32)1) |                      \
    ((uint32)(TERM) << (uint32)2) | ((uint32)(LRTXERM) << (uint32)3) |           \
    ((uint32)(LVDSM) << (uint32)6) |((uint32)(PS) << (uint32)7) |                \
    ((uint32)(TEN_CTRL) << (uint32)8) |                                          \
    ((uint32)(TX_EN) << (uint32)9) |((uint32)(VIDFFADJ) << (uint32)10) |         \
    ((uint32)(VOSDYN) << (uint32)12) | ((uint32)(VOSEXT) << (uint32)13)|         \
    ((uint32)(TX_PD) << (uint32)14) | ((uint32)(TX_PWDPD) << (uint32)15)         \
    ))

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/

#define PORT_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Port_Memmap.h header is included without safegaurd.*/
#include "Port_MemMap.h"
/*******************************************************************************
**                      Configuration Options                                 **
*******************************************************************************/
/*
Container : PortPinConfiguration
*/
/* Macros to define pin Default Input Output control value */
#define  PORT_PIN_DEFAULT                   (0x10U)
/*
Configuration Options: Physical pin level
-LOW  (Low Volatage Level)
-HIGH (High Voltage Level)
*/
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_PIN_LEVEL_LOW    (0x00U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_PIN_LEVEL_HIGH   (0x01U)
/*
Configuration Options: Pin input pull resistor
-NO PULL
-PULL DOWN
-PULL UP
*/
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_PIN_IN_PULL_UP     (0x10U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_PIN_IN_PULL_DOWN   (0x08U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_PIN_IN_NO_PULL     (0x00U)
/*
Configuration Options: Pin driver strength
*/
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define RFAST_PORT_PIN_STRONG_DRIVER_SHARP_EDGE  (0x0U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define RFAST_PORT_PIN_STRONG_DRIVER_MEDIUM_EDGE (0x1U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define RFAST_PORT_PIN_MEDIUM_DRIVER             (0x2U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define RFAST_PORT_PIN_RGMII_DRIVER              (0x3U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define RFAST_PORT_PIN_DEFAULT_DRIVER            (0x0U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define FAST_PORT_PIN_STRONG_DRIVER_SHARP_EDGE  (0x0U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define FAST_PORT_PIN_STRONG_DRIVER_MEDIUM_EDGE (0x1U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define FAST_PORT_PIN_MEDIUM_DRIVER             (0x2U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define FAST_PORT_PIN_DEFAULT_DRIVER            (0x0U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define SLOW_PORT_PIN_MEDIUM_DRIVER_SHARP_EDGE  (0x0U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define SLOW_PORT_PIN_MEDIUM_DRIVER             (0x1U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define SLOW_PORT_PIN_DEFAULT_DRIVER            (0x0U)
/* Pin driver strength value for the non available pins*/
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define  PORT_PIN_PAD_STRENGTH_DEFAULT      (0x0U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define  PORT_PIN_PAD_LEVEL_DEFAULT         (0x0U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define  PORT_PIN_PAD_DEFAULT               (0x0U)
/*
Configuration Options: Pin output characteristics
-PUSHPULL
-OPENDRAIN
*/
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_PIN_OUT_PUSHPULL     (0x00U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_PIN_OUT_OPENDRAIN    (0x40U)
/*
Configuration Options: Pin Pad Level
*/
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE  (0x0U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_INPUT_LEVEL_TTL_3_3V       (0xCU)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_INPUT_LEVEL_TTL_5_0V       (0x8U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_RGMII_INPUT      (0x03U)
/* For the Px_DISC register value set */
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_PIN_ANALOG_INPUT_ENABLE  (0x1U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_PIN_ANALOG_INPUT_DISABLE (0x0U)
/* For PCSR register */
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_PCSR_ENABLE  (0x1U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_PCSR_DISABLE (0x0U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_PCSR_DEFAULT   (0x0U)
/* For Pn_LPCR registers wrt LVDSH pads */
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_LVDS_PORT_CONTROLLED           (0x0U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_LVDS_HSCT_CONTROLLED           (0x1U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_LVDS_ENABLE                    (0x1U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_LVDS_DISABLE                   (0x0U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_LVDS_INTERNAL_TERMINATION      (0x1U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_LVDS_EXTERNAL_TERMINATION      (0x0U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_LVDS_POLY_RESISTOR_TERM        (0x0U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_LVDS_LVDSM                     (0x1U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_LVDS_LVDSH                     (0x0U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PAD_SUPPLY_3_3V                     (0x0U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PAD_SUPPLY_5_0V                    (0x1U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_LVDS_LVDS_VDIFF_ADJ            (0x1U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_LVDS_VOSDYN                    (0x1U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_LVDS_VOSEXT                    (0x0U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_LVDS_POWER_DOWN                (0x1U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_LVDS_TX_PWDPD_ENABLE           (0x1U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_LVDS_TX_PWDPD_DISABLE          (0x0U)
/* MISRA2012_RULE_2_5_JUSTIFICATION: Local Macros used in the configuration
structures for generation values for structure members. The use of the macros
in code is dependent on user configuration and hence the macros cant be removed.*/
#define PORT_LVDS_DEFAULT                   (0x0U)
/******************************************************************************/
    
    
static const Port_n_ConfigType Port_kConfiguration[] =
{
  /*                              Port0                       */
  {
    {
    
    /* Port pins direction, characteristics and mode configuration */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 7*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT3),/*Pin 8*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 9*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 10*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 11*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 12*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 13*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 14*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO) /*Pin 15*/

    },
    {
    /* Port pins initial level configuration */
      PORT_PIN_LEVEL_LOW,/* Pin 0 */
      PORT_PIN_LEVEL_LOW,/* Pin 1 */
      PORT_PIN_LEVEL_LOW,/* Pin 2 */
      PORT_PIN_LEVEL_LOW,/* Pin 3 */
      PORT_PIN_LEVEL_LOW,/* Pin 4 */
      PORT_PIN_LEVEL_LOW,/* Pin 5 */
      PORT_PIN_LEVEL_LOW,/* Pin 6 */
      PORT_PIN_LEVEL_LOW,/* Pin 7 */
      PORT_PIN_LEVEL_LOW,/* Pin 8 */
      PORT_PIN_LEVEL_LOW,/* Pin 9 */
      PORT_PIN_LEVEL_LOW,/* Pin 10 */
      PORT_PIN_LEVEL_LOW,/* Pin 11 */
      PORT_PIN_LEVEL_LOW,/* Pin 12 */
      PORT_PIN_LEVEL_LOW,/* Pin 13 */
      PORT_PIN_LEVEL_LOW,/* Pin 14 */
      PORT_PIN_LEVEL_LOW,/* Pin 15 */
      0U /* Reserved */
    },
    /* Port pins drive strength1 configuration */
    Portx_lPdrConfig1(
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin0*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin1*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin2*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin3*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin4*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin5*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin6*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT)/*Pin7*/
                  ),
    /* Port pins drive strength2 configuration */
    Portx_lPdrConfig2(
      (PORT_PIN_PAD_LEVEL_DEFAULT|SLOW_PORT_PIN_DEFAULT_DRIVER),/*Pin8*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin9*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin10*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin11*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin12*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin13*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin14*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT)/*Pin15*/
                  ),
    {/* Port pin run time mode changeable or not configuration */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 0 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 1 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 2 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 3 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 4 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 5 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 6 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 7 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 8 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 9 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 10 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 11 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 12 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 13 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 14 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 15 */
    0U /* Reserved */

    },
    {/* Port pin run time direction changeable or not configuration */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 0 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 1 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 2 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 3 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 4 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 5 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 6 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 7 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 8 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 9 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 10 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 11 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 12 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 13 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 14 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 15 */
      0U /* Reserved */

    },
    {
    /* Port pins direction, characteristics and mode configuration if
    direction is changeable */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin7*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT3),/*Pin8*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin9*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin10*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin11*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin12*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin13*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin14*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO)/*Pin15*/
    },
    {/* Port pin run time mode changeable or not configuration */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 0 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 1 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 2 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 3 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 4 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 5 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 6 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 7 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 8 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 9 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 10 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 11 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 12 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 13 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 14 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 15 */
      0U /* Reserved */

    }
  },
  /*                              Port1                       */
  {
    {
    
    /* Port pins direction, characteristics and mode configuration */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 7*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 8*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 9*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 10*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 11*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 12*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 13*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 14*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO) /*Pin 15*/

    },
    {
    /* Port pins initial level configuration */
      PORT_PIN_LEVEL_LOW,/* Pin 0 */
      PORT_PIN_LEVEL_LOW,/* Pin 1 */
      PORT_PIN_LEVEL_LOW,/* Pin 2 */
      PORT_PIN_LEVEL_LOW,/* Pin 3 */
      PORT_PIN_LEVEL_LOW,/* Pin 4 */
      PORT_PIN_LEVEL_LOW,/* Pin 5 */
      PORT_PIN_LEVEL_LOW,/* Pin 6 */
      PORT_PIN_LEVEL_LOW,/* Pin 7 */
      PORT_PIN_LEVEL_LOW,/* Pin 8 */
      PORT_PIN_LEVEL_LOW,/* Pin 9 */
      PORT_PIN_LEVEL_LOW,/* Pin 10 */
      PORT_PIN_LEVEL_LOW,/* Pin 11 */
      PORT_PIN_LEVEL_LOW,/* Pin 12 */
      PORT_PIN_LEVEL_LOW,/* Pin 13 */
      PORT_PIN_LEVEL_LOW,/* Pin 14 */
      PORT_PIN_LEVEL_LOW,/* Pin 15 */
      0U /* Reserved */
    },
    /* Port pins drive strength1 configuration */
    Portx_lPdrConfig1(
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin0*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin1*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin2*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin3*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin4*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin5*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin6*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT)/*Pin7*/
                  ),
    /* Port pins drive strength2 configuration */
    Portx_lPdrConfig2(
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin8*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin9*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin10*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin11*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin12*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin13*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin14*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT)/*Pin15*/
                  ),
    {/* Port pin run time mode changeable or not configuration */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 0 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 1 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 2 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 3 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 4 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 5 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 6 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 7 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 8 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 9 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 10 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 11 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 12 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 13 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 14 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 15 */
    0U /* Reserved */

    },
    {/* Port pin run time direction changeable or not configuration */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 0 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 1 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 2 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 3 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 4 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 5 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 6 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 7 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 8 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 9 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 10 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 11 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 12 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 13 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 14 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 15 */
      0U /* Reserved */

    },
    {
    /* Port pins direction, characteristics and mode configuration if
    direction is changeable */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin7*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin8*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin9*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin10*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin11*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin12*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin13*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin14*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO)/*Pin15*/
    },
    {/* Port pin run time mode changeable or not configuration */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 0 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 1 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 2 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 3 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 4 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 5 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 6 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 7 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 8 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 9 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 10 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 11 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 12 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 13 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 14 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 15 */
      0U /* Reserved */

    }
  },
  /*                              Port2                       */
  {
    {
    
    /* Port pins direction, characteristics and mode configuration */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT1),/*Pin 5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 7*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 8*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT5),/*Pin 9*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 10*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 11*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 12*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 13*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 14*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO) /*Pin 15*/

    },
    {
    /* Port pins initial level configuration */
      PORT_PIN_LEVEL_LOW,/* Pin 0 */
      PORT_PIN_LEVEL_LOW,/* Pin 1 */
      PORT_PIN_LEVEL_LOW,/* Pin 2 */
      PORT_PIN_LEVEL_LOW,/* Pin 3 */
      PORT_PIN_LEVEL_LOW,/* Pin 4 */
      PORT_PIN_LEVEL_LOW,/* Pin 5 */
      PORT_PIN_LEVEL_LOW,/* Pin 6 */
      PORT_PIN_LEVEL_LOW,/* Pin 7 */
      PORT_PIN_LEVEL_LOW,/* Pin 8 */
      PORT_PIN_LEVEL_LOW,/* Pin 9 */
      PORT_PIN_LEVEL_LOW,/* Pin 10 */
      PORT_PIN_LEVEL_LOW,/* Pin 11 */
      PORT_PIN_LEVEL_LOW,/* Pin 12 */
      PORT_PIN_LEVEL_LOW,/* Pin 13 */
      PORT_PIN_LEVEL_LOW,/* Pin 14 */
      PORT_PIN_LEVEL_LOW,/* Pin 15 */
      0U /* Reserved */
    },
    /* Port pins drive strength1 configuration */
    Portx_lPdrConfig1(
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin0*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin1*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin2*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin3*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin4*/
      (PORT_PIN_PAD_LEVEL_DEFAULT|FAST_PORT_PIN_DEFAULT_DRIVER),/*Pin5*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin6*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT)/*Pin7*/
                  ),
    /* Port pins drive strength2 configuration */
    Portx_lPdrConfig2(
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin8*/
      (PORT_PIN_PAD_LEVEL_DEFAULT|SLOW_PORT_PIN_DEFAULT_DRIVER),/*Pin9*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin10*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin11*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin12*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin13*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin14*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT)/*Pin15*/
                  ),
    {/* Port pin run time mode changeable or not configuration */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 0 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 1 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 2 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 3 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 4 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 5 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 6 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 7 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 8 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 9 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 10 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 11 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 12 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 13 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 14 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 15 */
    0U /* Reserved */

    },
    {/* Port pin run time direction changeable or not configuration */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 0 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 1 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 2 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 3 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 4 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 5 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 6 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 7 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 8 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 9 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 10 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 11 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 12 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 13 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 14 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 15 */
      0U /* Reserved */

    },
    {
    /* Port pins direction, characteristics and mode configuration if
    direction is changeable */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT1),/*Pin5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin7*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin8*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT5),/*Pin9*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin10*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin11*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin12*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin13*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin14*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO)/*Pin15*/
    },
    {/* Port pin run time mode changeable or not configuration */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 0 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 1 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 2 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 3 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 4 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 5 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 6 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 7 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 8 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 9 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 10 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 11 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 12 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 13 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 14 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 15 */
      0U /* Reserved */

    }
  },
  /*                              Port10                       */
  {
    {
    
    /* Port pins direction, characteristics and mode configuration */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT2),/*Pin 5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_GPIO),/*Pin 6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 7*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 8*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 9*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 10*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 11*/
    (PORT_PIN_DEFAULT),/*Pin 12*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 13*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 14*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO) /*Pin 15*/

    },
    {
    /* Port pins initial level configuration */
      PORT_PIN_LEVEL_LOW,/* Pin 0 */
      PORT_PIN_LEVEL_LOW,/* Pin 1 */
      PORT_PIN_LEVEL_LOW,/* Pin 2 */
      PORT_PIN_LEVEL_LOW,/* Pin 3 */
      PORT_PIN_LEVEL_LOW,/* Pin 4 */
      PORT_PIN_LEVEL_LOW,/* Pin 5 */
      PORT_PIN_LEVEL_LOW,/* Pin 6 */
      PORT_PIN_LEVEL_LOW,/* Pin 7 */
      PORT_PIN_LEVEL_LOW,/* Pin 8 */
      PORT_PIN_LEVEL_LOW,/* Pin 9 */
      PORT_PIN_LEVEL_LOW,/* Pin 10 */
      PORT_PIN_LEVEL_LOW,/* Pin 11 */
      0U,/* Pin 12 */
      PORT_PIN_LEVEL_LOW,/* Pin 13 */
      PORT_PIN_LEVEL_LOW,/* Pin 14 */
      PORT_PIN_LEVEL_LOW,/* Pin 15 */
      0U /* Reserved */
    },
    /* Port pins drive strength1 configuration */
    Portx_lPdrConfig1(
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin0*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin1*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin2*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin3*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin4*/
      (PORT_PIN_PAD_LEVEL_DEFAULT|SLOW_PORT_PIN_DEFAULT_DRIVER),/*Pin5*/
      (PORT_PIN_PAD_LEVEL_DEFAULT|SLOW_PORT_PIN_DEFAULT_DRIVER),/*Pin6*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT)/*Pin7*/
                  ),
    /* Port pins drive strength2 configuration */
    Portx_lPdrConfig2(
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin8*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin9*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin10*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin11*/
      (PORT_PIN_PAD_DEFAULT),/*Pin12*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin13*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin14*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT)/*Pin15*/
                  ),
    {/* Port pin run time mode changeable or not configuration */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 0 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 1 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 2 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 3 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 4 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 5 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 6 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 7 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 8 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 9 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 10 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 11 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 12 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 13 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 14 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 15 */
    0U /* Reserved */

    },
    {/* Port pin run time direction changeable or not configuration */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 0 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 1 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 2 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 3 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 4 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 5 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 6 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 7 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 8 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 9 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 10 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 11 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 12 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 13 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 14 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 15 */
      0U /* Reserved */

    },
    {
    /* Port pins direction, characteristics and mode configuration if
    direction is changeable */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT2),/*Pin5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_GPIO),/*Pin6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin7*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin8*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin9*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin10*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin11*/
      (PORT_PIN_DEFAULT),/*Pin12*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin13*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin14*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO)/*Pin15*/
    },
    {/* Port pin run time mode changeable or not configuration */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 0 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 1 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 2 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 3 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 4 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 5 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 6 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 7 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 8 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 9 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 10 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 11 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 12 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 13 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 14 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 15 */
      0U /* Reserved */

    }
  },
  /*                              Port11                       */
  {
    {
    
    /* Port pins direction, characteristics and mode configuration */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT6),/*Pin 0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT6),/*Pin 1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT6),/*Pin 2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT6),/*Pin 3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT7),/*Pin 4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT6),/*Pin 6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 7*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 8*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 9*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 10*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 11*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 12*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 13*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 14*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO) /*Pin 15*/

    },
    {
    /* Port pins initial level configuration */
      PORT_PIN_LEVEL_LOW,/* Pin 0 */
      PORT_PIN_LEVEL_LOW,/* Pin 1 */
      PORT_PIN_LEVEL_LOW,/* Pin 2 */
      PORT_PIN_LEVEL_LOW,/* Pin 3 */
      PORT_PIN_LEVEL_LOW,/* Pin 4 */
      PORT_PIN_LEVEL_LOW,/* Pin 5 */
      PORT_PIN_LEVEL_LOW,/* Pin 6 */
      PORT_PIN_LEVEL_LOW,/* Pin 7 */
      PORT_PIN_LEVEL_LOW,/* Pin 8 */
      PORT_PIN_LEVEL_LOW,/* Pin 9 */
      PORT_PIN_LEVEL_LOW,/* Pin 10 */
      PORT_PIN_LEVEL_LOW,/* Pin 11 */
      PORT_PIN_LEVEL_LOW,/* Pin 12 */
      PORT_PIN_LEVEL_LOW,/* Pin 13 */
      PORT_PIN_LEVEL_LOW,/* Pin 14 */
      PORT_PIN_LEVEL_LOW,/* Pin 15 */
      0U /* Reserved */
    },
    /* Port pins drive strength1 configuration */
    Portx_lPdrConfig1(
      (PORT_PIN_PAD_LEVEL_DEFAULT|RFAST_PORT_PIN_RGMII_DRIVER),/*Pin0*/
      (PORT_PIN_PAD_LEVEL_DEFAULT|RFAST_PORT_PIN_RGMII_DRIVER),/*Pin1*/
      (PORT_PIN_PAD_LEVEL_DEFAULT|RFAST_PORT_PIN_RGMII_DRIVER),/*Pin2*/
      (PORT_PIN_PAD_LEVEL_DEFAULT|RFAST_PORT_PIN_RGMII_DRIVER),/*Pin3*/
      (PORT_PIN_PAD_LEVEL_DEFAULT|RFAST_PORT_PIN_RGMII_DRIVER),/*Pin4*/
      (PORT_RGMII_INPUT|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin5*/
      (PORT_PIN_PAD_LEVEL_DEFAULT|RFAST_PORT_PIN_RGMII_DRIVER),/*Pin6*/
      (PORT_RGMII_INPUT|PORT_PIN_PAD_STRENGTH_DEFAULT)/*Pin7*/
                  ),
    /* Port pins drive strength2 configuration */
    Portx_lPdrConfig2(
      (PORT_RGMII_INPUT|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin8*/
      (PORT_RGMII_INPUT|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin9*/
      (PORT_RGMII_INPUT|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin10*/
      (PORT_RGMII_INPUT|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin11*/
      (PORT_RGMII_INPUT|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin12*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin13*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin14*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT)/*Pin15*/
                  ),
    {/* Port pin run time mode changeable or not configuration */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 0 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 1 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 2 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 3 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 4 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 5 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 6 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 7 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 8 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 9 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 10 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 11 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 12 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 13 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 14 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 15 */
    0U /* Reserved */

    },
    {/* Port pin run time direction changeable or not configuration */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 0 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 1 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 2 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 3 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 4 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 5 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 6 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 7 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 8 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 9 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 10 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 11 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 12 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 13 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 14 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 15 */
      0U /* Reserved */

    },
    {
    /* Port pins direction, characteristics and mode configuration if
    direction is changeable */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT6),/*Pin0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT6),/*Pin1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT6),/*Pin2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT6),/*Pin3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT7),/*Pin4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT6),/*Pin6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin7*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin8*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin9*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin10*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin11*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin12*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin13*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin14*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO)/*Pin15*/
    },
    {/* Port pin run time mode changeable or not configuration */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 0 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 1 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 2 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 3 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 4 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 5 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 6 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 7 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 8 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 9 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 10 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 11 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 12 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 13 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 14 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 15 */
      0U /* Reserved */

    }
  },
  /*                              Port12                       */
  {
    {
    
    /* Port pins direction, characteristics and mode configuration */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT6),/*Pin 0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 1*/
    (PORT_PIN_DEFAULT),/*Pin 2*/
    (PORT_PIN_DEFAULT),/*Pin 3*/
    (PORT_PIN_DEFAULT),/*Pin 4*/
    (PORT_PIN_DEFAULT),/*Pin 5*/
    (PORT_PIN_DEFAULT),/*Pin 6*/
    (PORT_PIN_DEFAULT),/*Pin 7*/
    (PORT_PIN_DEFAULT),/*Pin 8*/
    (PORT_PIN_DEFAULT),/*Pin 9*/
    (PORT_PIN_DEFAULT),/*Pin 10*/
    (PORT_PIN_DEFAULT),/*Pin 11*/
    (PORT_PIN_DEFAULT),/*Pin 12*/
    (PORT_PIN_DEFAULT),/*Pin 13*/
    (PORT_PIN_DEFAULT),/*Pin 14*/
    (PORT_PIN_DEFAULT) /*Pin 15*/

    },
    {
    /* Port pins initial level configuration */
      PORT_PIN_LEVEL_LOW,/* Pin 0 */
      PORT_PIN_LEVEL_LOW,/* Pin 1 */
      0U,/* Pin 2 */
      0U,/* Pin 3 */
      0U,/* Pin 4 */
      0U,/* Pin 5 */
      0U,/* Pin 6 */
      0U,/* Pin 7 */
      0U,/* Pin 8 */
      0U,/* Pin 9 */
      0U,/* Pin 10 */
      0U,/* Pin 11 */
      0U,/* Pin 12 */
      0U,/* Pin 13 */
      0U,/* Pin 14 */
      0U,/* Pin 15 */
      0U /* Reserved */
    },
    /* Port pins drive strength1 configuration */
    Portx_lPdrConfig1(
      (PORT_PIN_PAD_LEVEL_DEFAULT|SLOW_PORT_PIN_DEFAULT_DRIVER),/*Pin0*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin1*/
      (PORT_PIN_PAD_DEFAULT),/*Pin2*/
      (PORT_PIN_PAD_DEFAULT),/*Pin3*/
      (PORT_PIN_PAD_DEFAULT),/*Pin4*/
      (PORT_PIN_PAD_DEFAULT),/*Pin5*/
      (PORT_PIN_PAD_DEFAULT),/*Pin6*/
      (PORT_PIN_PAD_DEFAULT)/*Pin7*/
                  ),
    /* Port pins drive strength2 configuration */
    Portx_lPdrConfig2(
      (PORT_PIN_PAD_DEFAULT),/*Pin8*/
      (PORT_PIN_PAD_DEFAULT),/*Pin9*/
      (PORT_PIN_PAD_DEFAULT),/*Pin10*/
      (PORT_PIN_PAD_DEFAULT),/*Pin11*/
      (PORT_PIN_PAD_DEFAULT),/*Pin12*/
      (PORT_PIN_PAD_DEFAULT),/*Pin13*/
      (PORT_PIN_PAD_DEFAULT),/*Pin14*/
      (PORT_PIN_PAD_DEFAULT)/*Pin15*/
                  ),
    {/* Port pin run time mode changeable or not configuration */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 0 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 1 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 2 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 3 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 4 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 5 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 6 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 7 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 8 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 9 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 10 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 11 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 12 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 13 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 14 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 15 */
    0U /* Reserved */

    },
    {/* Port pin run time direction changeable or not configuration */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 0 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 1 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 2 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 3 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 4 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 5 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 6 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 7 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 8 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 9 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 10 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 11 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 12 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 13 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 14 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 15 */
      0U /* Reserved */

    },
    {
    /* Port pins direction, characteristics and mode configuration if
    direction is changeable */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT6),/*Pin0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin1*/
      (PORT_PIN_DEFAULT),/*Pin2*/
      (PORT_PIN_DEFAULT),/*Pin3*/
      (PORT_PIN_DEFAULT),/*Pin4*/
      (PORT_PIN_DEFAULT),/*Pin5*/
      (PORT_PIN_DEFAULT),/*Pin6*/
      (PORT_PIN_DEFAULT),/*Pin7*/
      (PORT_PIN_DEFAULT),/*Pin8*/
      (PORT_PIN_DEFAULT),/*Pin9*/
      (PORT_PIN_DEFAULT),/*Pin10*/
      (PORT_PIN_DEFAULT),/*Pin11*/
      (PORT_PIN_DEFAULT),/*Pin12*/
      (PORT_PIN_DEFAULT),/*Pin13*/
      (PORT_PIN_DEFAULT),/*Pin14*/
      (PORT_PIN_DEFAULT)/*Pin15*/
    },
    {/* Port pin run time mode changeable or not configuration */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 0 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 1 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 2 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 3 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 4 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 5 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 6 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 7 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 8 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 9 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 10 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 11 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 12 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 13 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 14 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 15 */
      0U /* Reserved */

    }
  },
  /*                              Port13                       */
  {
    {
    
    /* Port pins direction, characteristics and mode configuration */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_GPIO),/*Pin 0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_GPIO),/*Pin 1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 7*/
    (PORT_PIN_DEFAULT),/*Pin 8*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 9*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 10*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 11*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 12*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 13*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 14*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO) /*Pin 15*/

    },
    {
    /* Port pins initial level configuration */
      PORT_PIN_LEVEL_LOW,/* Pin 0 */
      PORT_PIN_LEVEL_LOW,/* Pin 1 */
      PORT_PIN_LEVEL_LOW,/* Pin 2 */
      PORT_PIN_LEVEL_LOW,/* Pin 3 */
      PORT_PIN_LEVEL_LOW,/* Pin 4 */
      PORT_PIN_LEVEL_LOW,/* Pin 5 */
      PORT_PIN_LEVEL_LOW,/* Pin 6 */
      PORT_PIN_LEVEL_LOW,/* Pin 7 */
      0U,/* Pin 8 */
      PORT_PIN_LEVEL_LOW,/* Pin 9 */
      PORT_PIN_LEVEL_LOW,/* Pin 10 */
      PORT_PIN_LEVEL_LOW,/* Pin 11 */
      PORT_PIN_LEVEL_LOW,/* Pin 12 */
      PORT_PIN_LEVEL_LOW,/* Pin 13 */
      PORT_PIN_LEVEL_LOW,/* Pin 14 */
      PORT_PIN_LEVEL_LOW,/* Pin 15 */
      0U /* Reserved */
    },
    /* Port pins drive strength1 configuration */
    Portx_lPdrConfig1(
      (PORT_PIN_PAD_LEVEL_DEFAULT|FAST_PORT_PIN_DEFAULT_DRIVER),/*Pin0*/
      (PORT_PIN_PAD_LEVEL_DEFAULT|FAST_PORT_PIN_DEFAULT_DRIVER),/*Pin1*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin2*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin3*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin4*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin5*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin6*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT)/*Pin7*/
                  ),
    /* Port pins drive strength2 configuration */
    Portx_lPdrConfig2(
      (PORT_PIN_PAD_DEFAULT),/*Pin8*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin9*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin10*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin11*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin12*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin13*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin14*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT)/*Pin15*/
                  ),
    {/* Port pin run time mode changeable or not configuration */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 0 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 1 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 2 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 3 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 4 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 5 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 6 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 7 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 8 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 9 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 10 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 11 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 12 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 13 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 14 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 15 */
    0U /* Reserved */

    },
    {/* Port pin run time direction changeable or not configuration */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 0 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 1 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 2 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 3 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 4 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 5 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 6 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 7 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 8 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 9 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 10 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 11 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 12 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 13 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 14 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 15 */
      0U /* Reserved */

    },
    {
    /* Port pins direction, characteristics and mode configuration if
    direction is changeable */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_GPIO),/*Pin0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_GPIO),/*Pin1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin7*/
      (PORT_PIN_DEFAULT),/*Pin8*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin9*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin10*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin11*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin12*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin13*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin14*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO)/*Pin15*/
    },
    {/* Port pin run time mode changeable or not configuration */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 0 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 1 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 2 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 3 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 4 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 5 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 6 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 7 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 8 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 9 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 10 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 11 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 12 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 13 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 14 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 15 */
      0U /* Reserved */

    }
  },
  /*                              Port14                       */
  {
    {
    
    /* Port pins direction, characteristics and mode configuration */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT2),/*Pin 0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT6),/*Pin 5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT6),/*Pin 6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 7*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 8*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT6),/*Pin 9*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT6),/*Pin 10*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 11*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 12*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 13*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 14*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO) /*Pin 15*/

    },
    {
    /* Port pins initial level configuration */
      PORT_PIN_LEVEL_LOW,/* Pin 0 */
      PORT_PIN_LEVEL_LOW,/* Pin 1 */
      PORT_PIN_LEVEL_LOW,/* Pin 2 */
      PORT_PIN_LEVEL_LOW,/* Pin 3 */
      PORT_PIN_LEVEL_LOW,/* Pin 4 */
      PORT_PIN_LEVEL_LOW,/* Pin 5 */
      PORT_PIN_LEVEL_LOW,/* Pin 6 */
      PORT_PIN_LEVEL_LOW,/* Pin 7 */
      PORT_PIN_LEVEL_LOW,/* Pin 8 */
      PORT_PIN_LEVEL_LOW,/* Pin 9 */
      PORT_PIN_LEVEL_LOW,/* Pin 10 */
      PORT_PIN_LEVEL_LOW,/* Pin 11 */
      PORT_PIN_LEVEL_LOW,/* Pin 12 */
      PORT_PIN_LEVEL_LOW,/* Pin 13 */
      PORT_PIN_LEVEL_LOW,/* Pin 14 */
      PORT_PIN_LEVEL_LOW,/* Pin 15 */
      0U /* Reserved */
    },
    /* Port pins drive strength1 configuration */
    Portx_lPdrConfig1(
      (PORT_PIN_PAD_LEVEL_DEFAULT|FAST_PORT_PIN_DEFAULT_DRIVER),/*Pin0*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin1*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin2*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin3*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin4*/
      (PORT_PIN_PAD_LEVEL_DEFAULT|FAST_PORT_PIN_DEFAULT_DRIVER),/*Pin5*/
      (PORT_PIN_PAD_LEVEL_DEFAULT|FAST_PORT_PIN_DEFAULT_DRIVER),/*Pin6*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT)/*Pin7*/
                  ),
    /* Port pins drive strength2 configuration */
    Portx_lPdrConfig2(
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin8*/
      (PORT_PIN_PAD_LEVEL_DEFAULT|FAST_PORT_PIN_DEFAULT_DRIVER),/*Pin9*/
      (PORT_PIN_PAD_LEVEL_DEFAULT|FAST_PORT_PIN_DEFAULT_DRIVER),/*Pin10*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin11*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin12*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin13*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin14*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT)/*Pin15*/
                  ),
    {/* Port pin run time mode changeable or not configuration */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 0 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 1 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 2 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 3 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 4 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 5 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 6 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 7 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 8 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 9 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 10 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 11 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 12 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 13 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 14 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 15 */
    0U /* Reserved */

    },
    {/* Port pin run time direction changeable or not configuration */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 0 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 1 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 2 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 3 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 4 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 5 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 6 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 7 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 8 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 9 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 10 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 11 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 12 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 13 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 14 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 15 */
      0U /* Reserved */

    },
    {
    /* Port pins direction, characteristics and mode configuration if
    direction is changeable */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT2),/*Pin0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT6),/*Pin5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT6),/*Pin6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin7*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin8*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT6),/*Pin9*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT6),/*Pin10*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin11*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin12*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin13*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin14*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO)/*Pin15*/
    },
    {/* Port pin run time mode changeable or not configuration */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 0 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 1 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 2 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 3 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 4 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 5 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 6 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 7 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 8 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 9 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 10 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 11 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 12 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 13 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 14 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 15 */
      0U /* Reserved */

    }
  },
  /*                              Port15                       */
  {
    {
    
    /* Port pins direction, characteristics and mode configuration */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT2),/*Pin 0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_OPENDRAIN | PORT_PIN_MODE_ALT6),/*Pin 4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_OPENDRAIN | PORT_PIN_MODE_ALT6),/*Pin 5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 7*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT3),/*Pin 8*/
    (PORT_PIN_DEFAULT),/*Pin 9*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 10*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 11*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 12*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 13*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 14*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO) /*Pin 15*/

    },
    {
    /* Port pins initial level configuration */
      PORT_PIN_LEVEL_LOW,/* Pin 0 */
      PORT_PIN_LEVEL_LOW,/* Pin 1 */
      PORT_PIN_LEVEL_LOW,/* Pin 2 */
      PORT_PIN_LEVEL_LOW,/* Pin 3 */
      PORT_PIN_LEVEL_HIGH,/* Pin 4 */
      PORT_PIN_LEVEL_HIGH,/* Pin 5 */
      PORT_PIN_LEVEL_LOW,/* Pin 6 */
      PORT_PIN_LEVEL_LOW,/* Pin 7 */
      PORT_PIN_LEVEL_LOW,/* Pin 8 */
      0U,/* Pin 9 */
      PORT_PIN_LEVEL_LOW,/* Pin 10 */
      PORT_PIN_LEVEL_LOW,/* Pin 11 */
      PORT_PIN_LEVEL_LOW,/* Pin 12 */
      PORT_PIN_LEVEL_LOW,/* Pin 13 */
      PORT_PIN_LEVEL_LOW,/* Pin 14 */
      PORT_PIN_LEVEL_LOW,/* Pin 15 */
      0U /* Reserved */
    },
    /* Port pins drive strength1 configuration */
    Portx_lPdrConfig1(
      (PORT_PIN_PAD_LEVEL_DEFAULT|FAST_PORT_PIN_DEFAULT_DRIVER),/*Pin0*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin1*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin2*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin3*/
      (PORT_PIN_PAD_LEVEL_DEFAULT|FAST_PORT_PIN_DEFAULT_DRIVER),/*Pin4*/
      (PORT_PIN_PAD_LEVEL_DEFAULT|FAST_PORT_PIN_DEFAULT_DRIVER),/*Pin5*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin6*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT)/*Pin7*/
                  ),
    /* Port pins drive strength2 configuration */
    Portx_lPdrConfig2(
      (PORT_PIN_PAD_LEVEL_DEFAULT|FAST_PORT_PIN_DEFAULT_DRIVER),/*Pin8*/
      (PORT_PIN_PAD_DEFAULT),/*Pin9*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin10*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin11*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin12*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin13*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin14*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT)/*Pin15*/
                  ),
    {/* Port pin run time mode changeable or not configuration */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 0 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 1 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 2 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 3 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 4 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 5 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 6 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 7 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 8 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 9 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 10 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 11 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 12 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 13 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 14 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 15 */
    0U /* Reserved */

    },
    {/* Port pin run time direction changeable or not configuration */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 0 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 1 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 2 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 3 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 4 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 5 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 6 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 7 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 8 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 9 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 10 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 11 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 12 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 13 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 14 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 15 */
      0U /* Reserved */

    },
    {
    /* Port pins direction, characteristics and mode configuration if
    direction is changeable */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT2),/*Pin0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_OPENDRAIN | PORT_PIN_MODE_ALT6),/*Pin4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_OPENDRAIN | PORT_PIN_MODE_ALT6),/*Pin5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin7*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT3),/*Pin8*/
      (PORT_PIN_DEFAULT),/*Pin9*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin10*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin11*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin12*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin13*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin14*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO)/*Pin15*/
    },
    {/* Port pin run time mode changeable or not configuration */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 0 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 1 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 2 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 3 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 4 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 5 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 6 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 7 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 8 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 9 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 10 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 11 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 12 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 13 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 14 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 15 */
      0U /* Reserved */

    }
  },
  /*                              Port20                       */
  {
    {
    
    /* Port pins direction, characteristics and mode configuration */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT5),/*Pin 0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 3*/
    (PORT_PIN_DEFAULT),/*Pin 4*/
    (PORT_PIN_DEFAULT),/*Pin 5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 7*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT5),/*Pin 8*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT3),/*Pin 9*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT4),/*Pin 10*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_GPIO),/*Pin 11*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 12*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT5),/*Pin 13*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT3),/*Pin 14*/
    (PORT_PIN_DEFAULT) /*Pin 15*/

    },
    {
    /* Port pins initial level configuration */
      PORT_PIN_LEVEL_LOW,/* Pin 0 */
      PORT_PIN_LEVEL_LOW,/* Pin 1 */
      PORT_PIN_LEVEL_LOW,/* Pin 2 */
      PORT_PIN_LEVEL_LOW,/* Pin 3 */
      0U,/* Pin 4 */
      0U,/* Pin 5 */
      PORT_PIN_LEVEL_LOW,/* Pin 6 */
      PORT_PIN_LEVEL_LOW,/* Pin 7 */
      PORT_PIN_LEVEL_HIGH,/* Pin 8 */
      PORT_PIN_LEVEL_HIGH,/* Pin 9 */
      PORT_PIN_LEVEL_HIGH,/* Pin 10 */
      PORT_PIN_LEVEL_LOW,/* Pin 11 */
      PORT_PIN_LEVEL_LOW,/* Pin 12 */
      PORT_PIN_LEVEL_LOW,/* Pin 13 */
      PORT_PIN_LEVEL_LOW,/* Pin 14 */
      0U,/* Pin 15 */
      0U /* Reserved */
    },
    /* Port pins drive strength1 configuration */
    Portx_lPdrConfig1(
      (PORT_PIN_PAD_LEVEL_DEFAULT|FAST_PORT_PIN_DEFAULT_DRIVER),/*Pin0*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin1*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin2*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin3*/
      (PORT_PIN_PAD_DEFAULT),/*Pin4*/
      (PORT_PIN_PAD_DEFAULT),/*Pin5*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin6*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT)/*Pin7*/
                  ),
    /* Port pins drive strength2 configuration */
    Portx_lPdrConfig2(
      (PORT_PIN_PAD_LEVEL_DEFAULT|FAST_PORT_PIN_DEFAULT_DRIVER),/*Pin8*/
      (PORT_PIN_PAD_LEVEL_DEFAULT|FAST_PORT_PIN_DEFAULT_DRIVER),/*Pin9*/
      (PORT_PIN_PAD_LEVEL_DEFAULT|FAST_PORT_PIN_DEFAULT_DRIVER),/*Pin10*/
      (PORT_PIN_PAD_LEVEL_DEFAULT|FAST_PORT_PIN_DEFAULT_DRIVER),/*Pin11*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin12*/
      (PORT_PIN_PAD_LEVEL_DEFAULT|FAST_PORT_PIN_DEFAULT_DRIVER),/*Pin13*/
      (PORT_PIN_PAD_LEVEL_DEFAULT|FAST_PORT_PIN_DEFAULT_DRIVER),/*Pin14*/
      (PORT_PIN_PAD_DEFAULT)/*Pin15*/
                  ),
    {/* Port pin run time mode changeable or not configuration */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 0 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 1 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 2 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 3 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 4 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 5 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 6 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 7 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 8 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 9 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 10 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 11 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 12 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 13 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 14 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 15 */
    0U /* Reserved */

    },
    {/* Port pin run time direction changeable or not configuration */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 0 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 1 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 2 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 3 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 4 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 5 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 6 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 7 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 8 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 9 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 10 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 11 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 12 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 13 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 14 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 15 */
      0U /* Reserved */

    },
    {
    /* Port pins direction, characteristics and mode configuration if
    direction is changeable */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT5),/*Pin0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin3*/
      (PORT_PIN_DEFAULT),/*Pin4*/
      (PORT_PIN_DEFAULT),/*Pin5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin7*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT5),/*Pin8*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT3),/*Pin9*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT4),/*Pin10*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_GPIO),/*Pin11*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin12*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT5),/*Pin13*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT3),/*Pin14*/
      (PORT_PIN_DEFAULT)/*Pin15*/
    },
    {/* Port pin run time mode changeable or not configuration */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 0 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 1 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 2 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 3 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 4 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 5 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 6 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 7 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 8 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 9 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 10 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 11 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 12 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 13 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 14 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 15 */
      0U /* Reserved */

    }
  },
  /*                              Port21                       */
  {
    {
    
    /* Port pins direction, characteristics and mode configuration */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_OPENDRAIN | PORT_PIN_MODE_GPIO),/*Pin 2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_GPIO),/*Pin 3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_GPIO),/*Pin 4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_GPIO),/*Pin 5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 7*/
    (PORT_PIN_DEFAULT),/*Pin 8*/
    (PORT_PIN_DEFAULT),/*Pin 9*/
    (PORT_PIN_DEFAULT),/*Pin 10*/
    (PORT_PIN_DEFAULT),/*Pin 11*/
    (PORT_PIN_DEFAULT),/*Pin 12*/
    (PORT_PIN_DEFAULT),/*Pin 13*/
    (PORT_PIN_DEFAULT),/*Pin 14*/
    (PORT_PIN_DEFAULT) /*Pin 15*/

    },
    {
    /* Port pins initial level configuration */
      PORT_PIN_LEVEL_LOW,/* Pin 0 */
      PORT_PIN_LEVEL_LOW,/* Pin 1 */
      PORT_PIN_LEVEL_LOW,/* Pin 2 */
      PORT_PIN_LEVEL_LOW,/* Pin 3 */
      PORT_PIN_LEVEL_LOW,/* Pin 4 */
      PORT_PIN_LEVEL_LOW,/* Pin 5 */
      PORT_PIN_LEVEL_LOW,/* Pin 6 */
      PORT_PIN_LEVEL_LOW,/* Pin 7 */
      0U,/* Pin 8 */
      0U,/* Pin 9 */
      0U,/* Pin 10 */
      0U,/* Pin 11 */
      0U,/* Pin 12 */
      0U,/* Pin 13 */
      0U,/* Pin 14 */
      0U,/* Pin 15 */
      0U /* Reserved */
    },
    /* Port pins drive strength1 configuration */
    Portx_lPdrConfig1(
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin0*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin1*/
      (PORT_PIN_PAD_LEVEL_DEFAULT|FAST_PORT_PIN_DEFAULT_DRIVER),/*Pin2*/
      (PORT_PIN_PAD_LEVEL_DEFAULT|FAST_PORT_PIN_DEFAULT_DRIVER),/*Pin3*/
      (PORT_PIN_PAD_LEVEL_DEFAULT|FAST_PORT_PIN_DEFAULT_DRIVER),/*Pin4*/
      (PORT_PIN_PAD_LEVEL_DEFAULT|FAST_PORT_PIN_DEFAULT_DRIVER),/*Pin5*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin6*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT)/*Pin7*/
                  ),
    /* Port pins drive strength2 configuration */
    Portx_lPdrConfig2(
      (PORT_PIN_PAD_DEFAULT),/*Pin8*/
      (PORT_PIN_PAD_DEFAULT),/*Pin9*/
      (PORT_PIN_PAD_DEFAULT),/*Pin10*/
      (PORT_PIN_PAD_DEFAULT),/*Pin11*/
      (PORT_PIN_PAD_DEFAULT),/*Pin12*/
      (PORT_PIN_PAD_DEFAULT),/*Pin13*/
      (PORT_PIN_PAD_DEFAULT),/*Pin14*/
      (PORT_PIN_PAD_DEFAULT)/*Pin15*/
                  ),
    {/* Port pin run time mode changeable or not configuration */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 0 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 1 */
    PORT_PIN_MODE_CHANGEABLE,/* Pin 2 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 3 */
    PORT_PIN_MODE_CHANGEABLE,/* Pin 4 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 5 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 6 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 7 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 8 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 9 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 10 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 11 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 12 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 13 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 14 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 15 */
    0U /* Reserved */

    },
    {/* Port pin run time direction changeable or not configuration */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 0 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 1 */
      PORT_PIN_DIRECTION_CHANGEABLE ,/* Pin 2 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 3 */
      PORT_PIN_DIRECTION_CHANGEABLE ,/* Pin 4 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 5 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 6 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 7 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 8 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 9 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 10 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 11 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 12 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 13 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 14 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 15 */
      0U /* Reserved */

    },
    {
    /* Port pins direction, characteristics and mode configuration if
    direction is changeable */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_GPIO),/*Pin3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_GPIO),/*Pin5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin7*/
      (PORT_PIN_DEFAULT),/*Pin8*/
      (PORT_PIN_DEFAULT),/*Pin9*/
      (PORT_PIN_DEFAULT),/*Pin10*/
      (PORT_PIN_DEFAULT),/*Pin11*/
      (PORT_PIN_DEFAULT),/*Pin12*/
      (PORT_PIN_DEFAULT),/*Pin13*/
      (PORT_PIN_DEFAULT),/*Pin14*/
      (PORT_PIN_DEFAULT)/*Pin15*/
    },
    {/* Port pin run time mode changeable or not configuration */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 0 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 1 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 2 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 3 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 4 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 5 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 6 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 7 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 8 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 9 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 10 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 11 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 12 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 13 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 14 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 15 */
      0U /* Reserved */

    }
  },
  /*                              Port22                       */
  {
    {
    
    /* Port pins direction, characteristics and mode configuration */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 7*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 8*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 9*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 10*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 11*/
    (PORT_PIN_DEFAULT),/*Pin 12*/
    (PORT_PIN_DEFAULT),/*Pin 13*/
    (PORT_PIN_DEFAULT),/*Pin 14*/
    (PORT_PIN_DEFAULT) /*Pin 15*/

    },
    {
    /* Port pins initial level configuration */
      PORT_PIN_LEVEL_LOW,/* Pin 0 */
      PORT_PIN_LEVEL_LOW,/* Pin 1 */
      PORT_PIN_LEVEL_LOW,/* Pin 2 */
      PORT_PIN_LEVEL_LOW,/* Pin 3 */
      PORT_PIN_LEVEL_LOW,/* Pin 4 */
      PORT_PIN_LEVEL_LOW,/* Pin 5 */
      PORT_PIN_LEVEL_LOW,/* Pin 6 */
      PORT_PIN_LEVEL_LOW,/* Pin 7 */
      PORT_PIN_LEVEL_LOW,/* Pin 8 */
      PORT_PIN_LEVEL_LOW,/* Pin 9 */
      PORT_PIN_LEVEL_LOW,/* Pin 10 */
      PORT_PIN_LEVEL_LOW,/* Pin 11 */
      0U,/* Pin 12 */
      0U,/* Pin 13 */
      0U,/* Pin 14 */
      0U,/* Pin 15 */
      0U /* Reserved */
    },
    /* Port pins drive strength1 configuration */
    Portx_lPdrConfig1(
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin0*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin1*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin2*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin3*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin4*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin5*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin6*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT)/*Pin7*/
                  ),
    /* Port pins drive strength2 configuration */
    Portx_lPdrConfig2(
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin8*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin9*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin10*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin11*/
      (PORT_PIN_PAD_DEFAULT),/*Pin12*/
      (PORT_PIN_PAD_DEFAULT),/*Pin13*/
      (PORT_PIN_PAD_DEFAULT),/*Pin14*/
      (PORT_PIN_PAD_DEFAULT)/*Pin15*/
                  ),
    {/* Port pin run time mode changeable or not configuration */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 0 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 1 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 2 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 3 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 4 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 5 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 6 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 7 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 8 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 9 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 10 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 11 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 12 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 13 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 14 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 15 */
    0U /* Reserved */

    },
    {/* Port pin run time direction changeable or not configuration */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 0 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 1 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 2 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 3 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 4 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 5 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 6 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 7 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 8 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 9 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 10 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 11 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 12 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 13 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 14 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 15 */
      0U /* Reserved */

    },
    {
    /* Port pins direction, characteristics and mode configuration if
    direction is changeable */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin7*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin8*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin9*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin10*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin11*/
      (PORT_PIN_DEFAULT),/*Pin12*/
      (PORT_PIN_DEFAULT),/*Pin13*/
      (PORT_PIN_DEFAULT),/*Pin14*/
      (PORT_PIN_DEFAULT)/*Pin15*/
    },
    {/* Port pin run time mode changeable or not configuration */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 0 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 1 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 2 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 3 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 4 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 5 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 6 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 7 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 8 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 9 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 10 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 11 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 12 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 13 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 14 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 15 */
      0U /* Reserved */

    }
  },
  /*                              Port23                       */
  {
    {
    
    /* Port pins direction, characteristics and mode configuration */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT5),/*Pin 1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 7*/
    (PORT_PIN_DEFAULT),/*Pin 8*/
    (PORT_PIN_DEFAULT),/*Pin 9*/
    (PORT_PIN_DEFAULT),/*Pin 10*/
    (PORT_PIN_DEFAULT),/*Pin 11*/
    (PORT_PIN_DEFAULT),/*Pin 12*/
    (PORT_PIN_DEFAULT),/*Pin 13*/
    (PORT_PIN_DEFAULT),/*Pin 14*/
    (PORT_PIN_DEFAULT) /*Pin 15*/

    },
    {
    /* Port pins initial level configuration */
      PORT_PIN_LEVEL_LOW,/* Pin 0 */
      PORT_PIN_LEVEL_HIGH,/* Pin 1 */
      PORT_PIN_LEVEL_LOW,/* Pin 2 */
      PORT_PIN_LEVEL_LOW,/* Pin 3 */
      PORT_PIN_LEVEL_LOW,/* Pin 4 */
      PORT_PIN_LEVEL_LOW,/* Pin 5 */
      PORT_PIN_LEVEL_LOW,/* Pin 6 */
      PORT_PIN_LEVEL_LOW,/* Pin 7 */
      0U,/* Pin 8 */
      0U,/* Pin 9 */
      0U,/* Pin 10 */
      0U,/* Pin 11 */
      0U,/* Pin 12 */
      0U,/* Pin 13 */
      0U,/* Pin 14 */
      0U,/* Pin 15 */
      0U /* Reserved */
    },
    /* Port pins drive strength1 configuration */
    Portx_lPdrConfig1(
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin0*/
      (PORT_PIN_PAD_LEVEL_DEFAULT|FAST_PORT_PIN_DEFAULT_DRIVER),/*Pin1*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin2*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin3*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin4*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin5*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin6*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT)/*Pin7*/
                  ),
    /* Port pins drive strength2 configuration */
    Portx_lPdrConfig2(
      (PORT_PIN_PAD_DEFAULT),/*Pin8*/
      (PORT_PIN_PAD_DEFAULT),/*Pin9*/
      (PORT_PIN_PAD_DEFAULT),/*Pin10*/
      (PORT_PIN_PAD_DEFAULT),/*Pin11*/
      (PORT_PIN_PAD_DEFAULT),/*Pin12*/
      (PORT_PIN_PAD_DEFAULT),/*Pin13*/
      (PORT_PIN_PAD_DEFAULT),/*Pin14*/
      (PORT_PIN_PAD_DEFAULT)/*Pin15*/
                  ),
    {/* Port pin run time mode changeable or not configuration */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 0 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 1 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 2 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 3 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 4 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 5 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 6 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 7 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 8 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 9 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 10 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 11 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 12 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 13 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 14 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 15 */
    0U /* Reserved */

    },
    {/* Port pin run time direction changeable or not configuration */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 0 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 1 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 2 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 3 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 4 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 5 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 6 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 7 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 8 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 9 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 10 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 11 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 12 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 13 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 14 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 15 */
      0U /* Reserved */

    },
    {
    /* Port pins direction, characteristics and mode configuration if
    direction is changeable */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT5),/*Pin1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin7*/
      (PORT_PIN_DEFAULT),/*Pin8*/
      (PORT_PIN_DEFAULT),/*Pin9*/
      (PORT_PIN_DEFAULT),/*Pin10*/
      (PORT_PIN_DEFAULT),/*Pin11*/
      (PORT_PIN_DEFAULT),/*Pin12*/
      (PORT_PIN_DEFAULT),/*Pin13*/
      (PORT_PIN_DEFAULT),/*Pin14*/
      (PORT_PIN_DEFAULT)/*Pin15*/
    },
    {/* Port pin run time mode changeable or not configuration */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 0 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 1 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 2 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 3 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 4 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 5 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 6 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 7 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 8 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 9 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 10 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 11 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 12 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 13 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 14 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 15 */
      0U /* Reserved */

    }
  },
  /*                              Port24                       */
  {
    {
    
    /* Port pins direction, characteristics and mode configuration */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 7*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 8*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 9*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 10*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 11*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 12*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 13*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 14*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO) /*Pin 15*/

    },
    {
    /* Port pins initial level configuration */
      PORT_PIN_LEVEL_LOW,/* Pin 0 */
      PORT_PIN_LEVEL_LOW,/* Pin 1 */
      PORT_PIN_LEVEL_LOW,/* Pin 2 */
      PORT_PIN_LEVEL_LOW,/* Pin 3 */
      PORT_PIN_LEVEL_LOW,/* Pin 4 */
      PORT_PIN_LEVEL_LOW,/* Pin 5 */
      PORT_PIN_LEVEL_LOW,/* Pin 6 */
      PORT_PIN_LEVEL_LOW,/* Pin 7 */
      PORT_PIN_LEVEL_LOW,/* Pin 8 */
      PORT_PIN_LEVEL_LOW,/* Pin 9 */
      PORT_PIN_LEVEL_LOW,/* Pin 10 */
      PORT_PIN_LEVEL_LOW,/* Pin 11 */
      PORT_PIN_LEVEL_LOW,/* Pin 12 */
      PORT_PIN_LEVEL_LOW,/* Pin 13 */
      PORT_PIN_LEVEL_LOW,/* Pin 14 */
      PORT_PIN_LEVEL_LOW,/* Pin 15 */
      0U /* Reserved */
    },
    /* Port pins drive strength1 configuration */
    Portx_lPdrConfig1(
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin0*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin1*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin2*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin3*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin4*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin5*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin6*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT)/*Pin7*/
                  ),
    /* Port pins drive strength2 configuration */
    Portx_lPdrConfig2(
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin8*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin9*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin10*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin11*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin12*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin13*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin14*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT)/*Pin15*/
                  ),
    {/* Port pin run time mode changeable or not configuration */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 0 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 1 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 2 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 3 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 4 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 5 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 6 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 7 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 8 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 9 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 10 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 11 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 12 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 13 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 14 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 15 */
    0U /* Reserved */

    },
    {/* Port pin run time direction changeable or not configuration */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 0 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 1 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 2 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 3 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 4 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 5 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 6 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 7 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 8 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 9 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 10 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 11 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 12 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 13 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 14 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 15 */
      0U /* Reserved */

    },
    {
    /* Port pins direction, characteristics and mode configuration if
    direction is changeable */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin7*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin8*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin9*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin10*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin11*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin12*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin13*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin14*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO)/*Pin15*/
    },
    {/* Port pin run time mode changeable or not configuration */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 0 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 1 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 2 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 3 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 4 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 5 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 6 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 7 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 8 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 9 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 10 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 11 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 12 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 13 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 14 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 15 */
      0U /* Reserved */

    }
  },
  /*                              Port25                       */
  {
    {
    
    /* Port pins direction, characteristics and mode configuration */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 7*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 8*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 9*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 10*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 11*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 12*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 13*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 14*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO) /*Pin 15*/

    },
    {
    /* Port pins initial level configuration */
      PORT_PIN_LEVEL_LOW,/* Pin 0 */
      PORT_PIN_LEVEL_LOW,/* Pin 1 */
      PORT_PIN_LEVEL_LOW,/* Pin 2 */
      PORT_PIN_LEVEL_LOW,/* Pin 3 */
      PORT_PIN_LEVEL_LOW,/* Pin 4 */
      PORT_PIN_LEVEL_LOW,/* Pin 5 */
      PORT_PIN_LEVEL_LOW,/* Pin 6 */
      PORT_PIN_LEVEL_LOW,/* Pin 7 */
      PORT_PIN_LEVEL_LOW,/* Pin 8 */
      PORT_PIN_LEVEL_LOW,/* Pin 9 */
      PORT_PIN_LEVEL_LOW,/* Pin 10 */
      PORT_PIN_LEVEL_LOW,/* Pin 11 */
      PORT_PIN_LEVEL_LOW,/* Pin 12 */
      PORT_PIN_LEVEL_LOW,/* Pin 13 */
      PORT_PIN_LEVEL_LOW,/* Pin 14 */
      PORT_PIN_LEVEL_LOW,/* Pin 15 */
      0U /* Reserved */
    },
    /* Port pins drive strength1 configuration */
    Portx_lPdrConfig1(
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin0*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin1*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin2*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin3*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin4*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin5*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin6*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT)/*Pin7*/
                  ),
    /* Port pins drive strength2 configuration */
    Portx_lPdrConfig2(
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin8*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin9*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin10*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin11*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin12*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin13*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin14*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT)/*Pin15*/
                  ),
    {/* Port pin run time mode changeable or not configuration */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 0 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 1 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 2 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 3 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 4 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 5 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 6 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 7 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 8 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 9 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 10 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 11 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 12 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 13 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 14 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 15 */
    0U /* Reserved */

    },
    {/* Port pin run time direction changeable or not configuration */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 0 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 1 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 2 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 3 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 4 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 5 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 6 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 7 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 8 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 9 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 10 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 11 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 12 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 13 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 14 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 15 */
      0U /* Reserved */

    },
    {
    /* Port pins direction, characteristics and mode configuration if
    direction is changeable */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin7*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin8*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin9*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin10*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin11*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin12*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin13*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin14*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO)/*Pin15*/
    },
    {/* Port pin run time mode changeable or not configuration */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 0 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 1 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 2 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 3 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 4 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 5 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 6 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 7 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 8 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 9 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 10 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 11 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 12 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 13 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 14 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 15 */
      0U /* Reserved */

    }
  },
  /*                              Port26                       */
  {
    {
    
    /* Port pins direction, characteristics and mode configuration */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 0*/
    (PORT_PIN_DEFAULT),/*Pin 1*/
    (PORT_PIN_DEFAULT),/*Pin 2*/
    (PORT_PIN_DEFAULT),/*Pin 3*/
    (PORT_PIN_DEFAULT),/*Pin 4*/
    (PORT_PIN_DEFAULT),/*Pin 5*/
    (PORT_PIN_DEFAULT),/*Pin 6*/
    (PORT_PIN_DEFAULT),/*Pin 7*/
    (PORT_PIN_DEFAULT),/*Pin 8*/
    (PORT_PIN_DEFAULT),/*Pin 9*/
    (PORT_PIN_DEFAULT),/*Pin 10*/
    (PORT_PIN_DEFAULT),/*Pin 11*/
    (PORT_PIN_DEFAULT),/*Pin 12*/
    (PORT_PIN_DEFAULT),/*Pin 13*/
    (PORT_PIN_DEFAULT),/*Pin 14*/
    (PORT_PIN_DEFAULT) /*Pin 15*/

    },
    {
    /* Port pins initial level configuration */
      PORT_PIN_LEVEL_LOW,/* Pin 0 */
      0U,/* Pin 1 */
      0U,/* Pin 2 */
      0U,/* Pin 3 */
      0U,/* Pin 4 */
      0U,/* Pin 5 */
      0U,/* Pin 6 */
      0U,/* Pin 7 */
      0U,/* Pin 8 */
      0U,/* Pin 9 */
      0U,/* Pin 10 */
      0U,/* Pin 11 */
      0U,/* Pin 12 */
      0U,/* Pin 13 */
      0U,/* Pin 14 */
      0U,/* Pin 15 */
      0U /* Reserved */
    },
    /* Port pins drive strength1 configuration */
    Portx_lPdrConfig1(
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin0*/
      (PORT_PIN_PAD_DEFAULT),/*Pin1*/
      (PORT_PIN_PAD_DEFAULT),/*Pin2*/
      (PORT_PIN_PAD_DEFAULT),/*Pin3*/
      (PORT_PIN_PAD_DEFAULT),/*Pin4*/
      (PORT_PIN_PAD_DEFAULT),/*Pin5*/
      (PORT_PIN_PAD_DEFAULT),/*Pin6*/
      (PORT_PIN_PAD_DEFAULT)/*Pin7*/
                  ),
    /* Port pins drive strength2 configuration */
    Portx_lPdrConfig2(
      (PORT_PIN_PAD_DEFAULT),/*Pin8*/
      (PORT_PIN_PAD_DEFAULT),/*Pin9*/
      (PORT_PIN_PAD_DEFAULT),/*Pin10*/
      (PORT_PIN_PAD_DEFAULT),/*Pin11*/
      (PORT_PIN_PAD_DEFAULT),/*Pin12*/
      (PORT_PIN_PAD_DEFAULT),/*Pin13*/
      (PORT_PIN_PAD_DEFAULT),/*Pin14*/
      (PORT_PIN_PAD_DEFAULT)/*Pin15*/
                  ),
    {/* Port pin run time mode changeable or not configuration */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 0 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 1 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 2 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 3 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 4 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 5 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 6 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 7 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 8 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 9 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 10 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 11 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 12 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 13 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 14 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 15 */
    0U /* Reserved */

    },
    {/* Port pin run time direction changeable or not configuration */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 0 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 1 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 2 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 3 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 4 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 5 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 6 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 7 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 8 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 9 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 10 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 11 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 12 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 13 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 14 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 15 */
      0U /* Reserved */

    },
    {
    /* Port pins direction, characteristics and mode configuration if
    direction is changeable */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin0*/
      (PORT_PIN_DEFAULT),/*Pin1*/
      (PORT_PIN_DEFAULT),/*Pin2*/
      (PORT_PIN_DEFAULT),/*Pin3*/
      (PORT_PIN_DEFAULT),/*Pin4*/
      (PORT_PIN_DEFAULT),/*Pin5*/
      (PORT_PIN_DEFAULT),/*Pin6*/
      (PORT_PIN_DEFAULT),/*Pin7*/
      (PORT_PIN_DEFAULT),/*Pin8*/
      (PORT_PIN_DEFAULT),/*Pin9*/
      (PORT_PIN_DEFAULT),/*Pin10*/
      (PORT_PIN_DEFAULT),/*Pin11*/
      (PORT_PIN_DEFAULT),/*Pin12*/
      (PORT_PIN_DEFAULT),/*Pin13*/
      (PORT_PIN_DEFAULT),/*Pin14*/
      (PORT_PIN_DEFAULT)/*Pin15*/
    },
    {/* Port pin run time mode changeable or not configuration */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 0 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 1 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 2 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 3 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 4 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 5 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 6 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 7 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 8 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 9 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 10 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 11 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 12 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 13 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 14 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 15 */
      0U /* Reserved */

    }
  },
  /*                              Port30                       */
  {
    {
    
    /* Port pins direction, characteristics and mode configuration */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 7*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 8*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 9*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 10*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 11*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 12*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 13*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 14*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO) /*Pin 15*/

    },
    {
    /* Port pins initial level configuration */
      PORT_PIN_LEVEL_LOW,/* Pin 0 */
      PORT_PIN_LEVEL_LOW,/* Pin 1 */
      PORT_PIN_LEVEL_LOW,/* Pin 2 */
      PORT_PIN_LEVEL_LOW,/* Pin 3 */
      PORT_PIN_LEVEL_LOW,/* Pin 4 */
      PORT_PIN_LEVEL_LOW,/* Pin 5 */
      PORT_PIN_LEVEL_LOW,/* Pin 6 */
      PORT_PIN_LEVEL_LOW,/* Pin 7 */
      PORT_PIN_LEVEL_LOW,/* Pin 8 */
      PORT_PIN_LEVEL_LOW,/* Pin 9 */
      PORT_PIN_LEVEL_LOW,/* Pin 10 */
      PORT_PIN_LEVEL_LOW,/* Pin 11 */
      PORT_PIN_LEVEL_LOW,/* Pin 12 */
      PORT_PIN_LEVEL_LOW,/* Pin 13 */
      PORT_PIN_LEVEL_LOW,/* Pin 14 */
      PORT_PIN_LEVEL_LOW,/* Pin 15 */
      0U /* Reserved */
    },
    /* Port pins drive strength1 configuration */
    Portx_lPdrConfig1(
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin0*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin1*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin2*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin3*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin4*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin5*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin6*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT)/*Pin7*/
                  ),
    /* Port pins drive strength2 configuration */
    Portx_lPdrConfig2(
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin8*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin9*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin10*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin11*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin12*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin13*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin14*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT)/*Pin15*/
                  ),
    {/* Port pin run time mode changeable or not configuration */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 0 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 1 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 2 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 3 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 4 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 5 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 6 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 7 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 8 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 9 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 10 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 11 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 12 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 13 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 14 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 15 */
    0U /* Reserved */

    },
    {/* Port pin run time direction changeable or not configuration */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 0 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 1 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 2 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 3 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 4 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 5 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 6 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 7 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 8 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 9 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 10 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 11 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 12 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 13 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 14 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 15 */
      0U /* Reserved */

    },
    {
    /* Port pins direction, characteristics and mode configuration if
    direction is changeable */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin7*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin8*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin9*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin10*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin11*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin12*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin13*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin14*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO)/*Pin15*/
    },
    {/* Port pin run time mode changeable or not configuration */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 0 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 1 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 2 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 3 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 4 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 5 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 6 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 7 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 8 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 9 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 10 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 11 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 12 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 13 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 14 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 15 */
      0U /* Reserved */

    }
  },
  /*                              Port31                       */
  {
    {
    
    /* Port pins direction, characteristics and mode configuration */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 7*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 8*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 9*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 10*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 11*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 12*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 13*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 14*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO) /*Pin 15*/

    },
    {
    /* Port pins initial level configuration */
      PORT_PIN_LEVEL_LOW,/* Pin 0 */
      PORT_PIN_LEVEL_LOW,/* Pin 1 */
      PORT_PIN_LEVEL_LOW,/* Pin 2 */
      PORT_PIN_LEVEL_LOW,/* Pin 3 */
      PORT_PIN_LEVEL_LOW,/* Pin 4 */
      PORT_PIN_LEVEL_LOW,/* Pin 5 */
      PORT_PIN_LEVEL_LOW,/* Pin 6 */
      PORT_PIN_LEVEL_LOW,/* Pin 7 */
      PORT_PIN_LEVEL_LOW,/* Pin 8 */
      PORT_PIN_LEVEL_LOW,/* Pin 9 */
      PORT_PIN_LEVEL_LOW,/* Pin 10 */
      PORT_PIN_LEVEL_LOW,/* Pin 11 */
      PORT_PIN_LEVEL_LOW,/* Pin 12 */
      PORT_PIN_LEVEL_LOW,/* Pin 13 */
      PORT_PIN_LEVEL_LOW,/* Pin 14 */
      PORT_PIN_LEVEL_LOW,/* Pin 15 */
      0U /* Reserved */
    },
    /* Port pins drive strength1 configuration */
    Portx_lPdrConfig1(
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin0*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin1*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin2*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin3*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin4*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin5*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin6*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT)/*Pin7*/
                  ),
    /* Port pins drive strength2 configuration */
    Portx_lPdrConfig2(
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin8*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin9*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin10*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin11*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin12*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin13*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin14*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT)/*Pin15*/
                  ),
    {/* Port pin run time mode changeable or not configuration */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 0 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 1 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 2 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 3 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 4 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 5 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 6 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 7 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 8 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 9 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 10 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 11 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 12 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 13 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 14 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 15 */
    0U /* Reserved */

    },
    {/* Port pin run time direction changeable or not configuration */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 0 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 1 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 2 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 3 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 4 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 5 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 6 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 7 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 8 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 9 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 10 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 11 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 12 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 13 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 14 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 15 */
      0U /* Reserved */

    },
    {
    /* Port pins direction, characteristics and mode configuration if
    direction is changeable */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin7*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin8*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin9*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin10*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin11*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin12*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin13*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin14*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO)/*Pin15*/
    },
    {/* Port pin run time mode changeable or not configuration */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 0 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 1 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 2 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 3 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 4 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 5 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 6 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 7 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 8 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 9 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 10 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 11 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 12 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 13 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 14 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 15 */
      0U /* Reserved */

    }
  },
  /*                              Port32                       */
  {
    {
    
    /* Port pins direction, characteristics and mode configuration */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 7*/
    (PORT_PIN_DEFAULT),/*Pin 8*/
    (PORT_PIN_DEFAULT),/*Pin 9*/
    (PORT_PIN_DEFAULT),/*Pin 10*/
    (PORT_PIN_DEFAULT),/*Pin 11*/
    (PORT_PIN_DEFAULT),/*Pin 12*/
    (PORT_PIN_DEFAULT),/*Pin 13*/
    (PORT_PIN_DEFAULT),/*Pin 14*/
    (PORT_PIN_DEFAULT) /*Pin 15*/

    },
    {
    /* Port pins initial level configuration */
      PORT_PIN_LEVEL_LOW,/* Pin 0 */
      PORT_PIN_LEVEL_LOW,/* Pin 1 */
      PORT_PIN_LEVEL_LOW,/* Pin 2 */
      PORT_PIN_LEVEL_LOW,/* Pin 3 */
      PORT_PIN_LEVEL_LOW,/* Pin 4 */
      PORT_PIN_LEVEL_LOW,/* Pin 5 */
      PORT_PIN_LEVEL_LOW,/* Pin 6 */
      PORT_PIN_LEVEL_LOW,/* Pin 7 */
      0U,/* Pin 8 */
      0U,/* Pin 9 */
      0U,/* Pin 10 */
      0U,/* Pin 11 */
      0U,/* Pin 12 */
      0U,/* Pin 13 */
      0U,/* Pin 14 */
      0U,/* Pin 15 */
      0U /* Reserved */
    },
    /* Port pins drive strength1 configuration */
    Portx_lPdrConfig1(
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin0*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin1*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin2*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin3*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin4*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin5*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin6*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT)/*Pin7*/
                  ),
    /* Port pins drive strength2 configuration */
    Portx_lPdrConfig2(
      (PORT_PIN_PAD_DEFAULT),/*Pin8*/
      (PORT_PIN_PAD_DEFAULT),/*Pin9*/
      (PORT_PIN_PAD_DEFAULT),/*Pin10*/
      (PORT_PIN_PAD_DEFAULT),/*Pin11*/
      (PORT_PIN_PAD_DEFAULT),/*Pin12*/
      (PORT_PIN_PAD_DEFAULT),/*Pin13*/
      (PORT_PIN_PAD_DEFAULT),/*Pin14*/
      (PORT_PIN_PAD_DEFAULT)/*Pin15*/
                  ),
    {/* Port pin run time mode changeable or not configuration */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 0 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 1 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 2 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 3 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 4 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 5 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 6 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 7 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 8 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 9 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 10 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 11 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 12 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 13 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 14 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 15 */
    0U /* Reserved */

    },
    {/* Port pin run time direction changeable or not configuration */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 0 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 1 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 2 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 3 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 4 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 5 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 6 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 7 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 8 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 9 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 10 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 11 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 12 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 13 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 14 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 15 */
      0U /* Reserved */

    },
    {
    /* Port pins direction, characteristics and mode configuration if
    direction is changeable */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin7*/
      (PORT_PIN_DEFAULT),/*Pin8*/
      (PORT_PIN_DEFAULT),/*Pin9*/
      (PORT_PIN_DEFAULT),/*Pin10*/
      (PORT_PIN_DEFAULT),/*Pin11*/
      (PORT_PIN_DEFAULT),/*Pin12*/
      (PORT_PIN_DEFAULT),/*Pin13*/
      (PORT_PIN_DEFAULT),/*Pin14*/
      (PORT_PIN_DEFAULT)/*Pin15*/
    },
    {/* Port pin run time mode changeable or not configuration */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 0 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 1 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 2 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 3 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 4 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 5 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 6 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 7 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 8 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 9 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 10 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 11 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 12 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 13 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 14 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 15 */
      0U /* Reserved */

    }
  },
  /*                              Port33                       */
  {
    {
    
    /* Port pins direction, characteristics and mode configuration */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_GPIO),/*Pin 4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_GPIO),/*Pin 5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_GPIO),/*Pin 6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT1),/*Pin 7*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 8*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 9*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_GPIO),/*Pin 10*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 11*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 12*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT4),/*Pin 13*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 14*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO) /*Pin 15*/

    },
    {
    /* Port pins initial level configuration */
      PORT_PIN_LEVEL_LOW,/* Pin 0 */
      PORT_PIN_LEVEL_LOW,/* Pin 1 */
      PORT_PIN_LEVEL_LOW,/* Pin 2 */
      PORT_PIN_LEVEL_LOW,/* Pin 3 */
      PORT_PIN_LEVEL_HIGH,/* Pin 4 */
      PORT_PIN_LEVEL_HIGH,/* Pin 5 */
      PORT_PIN_LEVEL_HIGH,/* Pin 6 */
      PORT_PIN_LEVEL_HIGH,/* Pin 7 */
      PORT_PIN_LEVEL_LOW,/* Pin 8 */
      PORT_PIN_LEVEL_LOW,/* Pin 9 */
      PORT_PIN_LEVEL_LOW,/* Pin 10 */
      PORT_PIN_LEVEL_LOW,/* Pin 11 */
      PORT_PIN_LEVEL_LOW,/* Pin 12 */
      PORT_PIN_LEVEL_HIGH,/* Pin 13 */
      PORT_PIN_LEVEL_LOW,/* Pin 14 */
      PORT_PIN_LEVEL_LOW,/* Pin 15 */
      0U /* Reserved */
    },
    /* Port pins drive strength1 configuration */
    Portx_lPdrConfig1(
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin0*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin1*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin2*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin3*/
      (PORT_PIN_PAD_LEVEL_DEFAULT|SLOW_PORT_PIN_DEFAULT_DRIVER),/*Pin4*/
      (PORT_PIN_PAD_LEVEL_DEFAULT|SLOW_PORT_PIN_DEFAULT_DRIVER),/*Pin5*/
      (PORT_PIN_PAD_LEVEL_DEFAULT|SLOW_PORT_PIN_DEFAULT_DRIVER),/*Pin6*/
      (PORT_PIN_PAD_LEVEL_DEFAULT|SLOW_PORT_PIN_DEFAULT_DRIVER)/*Pin7*/
                  ),
    /* Port pins drive strength2 configuration */
    Portx_lPdrConfig2(
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin8*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin9*/
      (PORT_PIN_PAD_LEVEL_DEFAULT|FAST_PORT_PIN_DEFAULT_DRIVER),/*Pin10*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin11*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin12*/
      (PORT_PIN_PAD_LEVEL_DEFAULT|FAST_PORT_PIN_DEFAULT_DRIVER),/*Pin13*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin14*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT)/*Pin15*/
                  ),
    {/* Port pin run time mode changeable or not configuration */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 0 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 1 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 2 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 3 */
    PORT_PIN_MODE_CHANGEABLE,/* Pin 4 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 5 */
    PORT_PIN_MODE_CHANGEABLE,/* Pin 6 */
    PORT_PIN_MODE_CHANGEABLE,/* Pin 7 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 8 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 9 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 10 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 11 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 12 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 13 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 14 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 15 */
    0U /* Reserved */

    },
    {/* Port pin run time direction changeable or not configuration */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 0 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 1 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 2 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 3 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 4 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 5 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 6 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 7 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 8 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 9 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 10 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 11 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 12 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 13 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 14 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 15 */
      0U /* Reserved */

    },
    {
    /* Port pins direction, characteristics and mode configuration if
    direction is changeable */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_GPIO),/*Pin4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_GPIO),/*Pin5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_GPIO),/*Pin6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT1),/*Pin7*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin8*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin9*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_GPIO),/*Pin10*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin11*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin12*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT4),/*Pin13*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin14*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO)/*Pin15*/
    },
    {/* Port pin run time mode changeable or not configuration */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 0 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 1 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 2 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 3 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 4 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 5 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 6 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 7 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 8 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 9 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 10 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 11 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 12 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 13 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 14 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 15 */
      0U /* Reserved */

    }
  },
  /*                              Port34                       */
  {
    {
    
    /* Port pins direction, characteristics and mode configuration */
    (PORT_PIN_DEFAULT),/*Pin 0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT4),/*Pin 5*/
    (PORT_PIN_DEFAULT),/*Pin 6*/
    (PORT_PIN_DEFAULT),/*Pin 7*/
    (PORT_PIN_DEFAULT),/*Pin 8*/
    (PORT_PIN_DEFAULT),/*Pin 9*/
    (PORT_PIN_DEFAULT),/*Pin 10*/
    (PORT_PIN_DEFAULT),/*Pin 11*/
    (PORT_PIN_DEFAULT),/*Pin 12*/
    (PORT_PIN_DEFAULT),/*Pin 13*/
    (PORT_PIN_DEFAULT),/*Pin 14*/
    (PORT_PIN_DEFAULT) /*Pin 15*/

    },
    {
    /* Port pins initial level configuration */
      0U,/* Pin 0 */
      PORT_PIN_LEVEL_LOW,/* Pin 1 */
      PORT_PIN_LEVEL_LOW,/* Pin 2 */
      PORT_PIN_LEVEL_LOW,/* Pin 3 */
      PORT_PIN_LEVEL_LOW,/* Pin 4 */
      PORT_PIN_LEVEL_LOW,/* Pin 5 */
      0U,/* Pin 6 */
      0U,/* Pin 7 */
      0U,/* Pin 8 */
      0U,/* Pin 9 */
      0U,/* Pin 10 */
      0U,/* Pin 11 */
      0U,/* Pin 12 */
      0U,/* Pin 13 */
      0U,/* Pin 14 */
      0U,/* Pin 15 */
      0U /* Reserved */
    },
    /* Port pins drive strength1 configuration */
    Portx_lPdrConfig1(
      (PORT_PIN_PAD_DEFAULT),/*Pin0*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin1*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin2*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin3*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin4*/
      (PORT_PIN_PAD_LEVEL_DEFAULT|FAST_PORT_PIN_DEFAULT_DRIVER),/*Pin5*/
      (PORT_PIN_PAD_DEFAULT),/*Pin6*/
      (PORT_PIN_PAD_DEFAULT)/*Pin7*/
                  ),
    /* Port pins drive strength2 configuration */
    Portx_lPdrConfig2(
      (PORT_PIN_PAD_DEFAULT),/*Pin8*/
      (PORT_PIN_PAD_DEFAULT),/*Pin9*/
      (PORT_PIN_PAD_DEFAULT),/*Pin10*/
      (PORT_PIN_PAD_DEFAULT),/*Pin11*/
      (PORT_PIN_PAD_DEFAULT),/*Pin12*/
      (PORT_PIN_PAD_DEFAULT),/*Pin13*/
      (PORT_PIN_PAD_DEFAULT),/*Pin14*/
      (PORT_PIN_PAD_DEFAULT)/*Pin15*/
                  ),
    {/* Port pin run time mode changeable or not configuration */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 0 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 1 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 2 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 3 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 4 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 5 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 6 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 7 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 8 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 9 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 10 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 11 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 12 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 13 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 14 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 15 */
    0U /* Reserved */

    },
    {/* Port pin run time direction changeable or not configuration */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 0 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 1 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 2 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 3 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 4 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 5 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 6 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 7 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 8 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 9 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 10 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 11 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 12 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 13 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 14 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 15 */
      0U /* Reserved */

    },
    {
    /* Port pins direction, characteristics and mode configuration if
    direction is changeable */
      (PORT_PIN_DEFAULT),/*Pin0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_OUT | PORT_PIN_OUT_PUSHPULL | PORT_PIN_MODE_ALT4),/*Pin5*/
      (PORT_PIN_DEFAULT),/*Pin6*/
      (PORT_PIN_DEFAULT),/*Pin7*/
      (PORT_PIN_DEFAULT),/*Pin8*/
      (PORT_PIN_DEFAULT),/*Pin9*/
      (PORT_PIN_DEFAULT),/*Pin10*/
      (PORT_PIN_DEFAULT),/*Pin11*/
      (PORT_PIN_DEFAULT),/*Pin12*/
      (PORT_PIN_DEFAULT),/*Pin13*/
      (PORT_PIN_DEFAULT),/*Pin14*/
      (PORT_PIN_DEFAULT)/*Pin15*/
    },
    {/* Port pin run time mode changeable or not configuration */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 0 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 1 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 2 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 3 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 4 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 5 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 6 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 7 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 8 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 9 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 10 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 11 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 12 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 13 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 14 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 15 */
      0U /* Reserved */

    }
  },
  /*                              Port40                       */
  {
    {
    
    /* Port pins direction, characteristics and mode configuration */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 7*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 8*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 9*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 10*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 11*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 12*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 13*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 14*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO) /*Pin 15*/

    },
    {
    /* Port pins initial level configuration */
      PORT_PIN_LEVEL_LOW,/* Pin 0 */
      PORT_PIN_LEVEL_LOW,/* Pin 1 */
      PORT_PIN_LEVEL_LOW,/* Pin 2 */
      PORT_PIN_LEVEL_LOW,/* Pin 3 */
      PORT_PIN_LEVEL_LOW,/* Pin 4 */
      PORT_PIN_LEVEL_LOW,/* Pin 5 */
      PORT_PIN_LEVEL_LOW,/* Pin 6 */
      PORT_PIN_LEVEL_LOW,/* Pin 7 */
      PORT_PIN_LEVEL_LOW,/* Pin 8 */
      PORT_PIN_LEVEL_LOW,/* Pin 9 */
      PORT_PIN_LEVEL_LOW,/* Pin 10 */
      PORT_PIN_LEVEL_LOW,/* Pin 11 */
      PORT_PIN_LEVEL_LOW,/* Pin 12 */
      PORT_PIN_LEVEL_LOW,/* Pin 13 */
      PORT_PIN_LEVEL_LOW,/* Pin 14 */
      PORT_PIN_LEVEL_LOW,/* Pin 15 */
      0U /* Reserved */
    },
    /* Port pins drive strength1 configuration */
    Portx_lPdrConfig1(
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin0*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin1*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin2*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin3*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin4*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin5*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin6*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT)/*Pin7*/
                  ),
    /* Port pins drive strength2 configuration */
    Portx_lPdrConfig2(
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin8*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin9*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin10*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin11*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin12*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin13*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin14*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT)/*Pin15*/
                  ),
    {/* Port pin run time mode changeable or not configuration */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 0 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 1 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 2 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 3 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 4 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 5 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 6 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 7 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 8 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 9 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 10 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 11 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 12 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 13 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 14 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 15 */
    0U /* Reserved */

    },
    {/* Port pin run time direction changeable or not configuration */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 0 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 1 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 2 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 3 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 4 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 5 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 6 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 7 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 8 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 9 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 10 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 11 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 12 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 13 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 14 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 15 */
      0U /* Reserved */

    },
    {
    /* Port pins direction, characteristics and mode configuration if
    direction is changeable */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin7*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin8*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin9*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin10*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin11*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin12*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin13*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin14*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO)/*Pin15*/
    },
    {/* Port pin run time mode changeable or not configuration */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 0 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 1 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 2 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 3 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 4 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 5 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 6 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 7 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 8 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 9 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 10 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 11 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 12 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 13 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 14 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 15 */
      0U /* Reserved */

    }
  },
  /*                              Port41                       */
  {
    {
    
    /* Port pins direction, characteristics and mode configuration */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 7*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
    ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin 8*/
    (PORT_PIN_DEFAULT),/*Pin 9*/
    (PORT_PIN_DEFAULT),/*Pin 10*/
    (PORT_PIN_DEFAULT),/*Pin 11*/
    (PORT_PIN_DEFAULT),/*Pin 12*/
    (PORT_PIN_DEFAULT),/*Pin 13*/
    (PORT_PIN_DEFAULT),/*Pin 14*/
    (PORT_PIN_DEFAULT) /*Pin 15*/

    },
    {
    /* Port pins initial level configuration */
      PORT_PIN_LEVEL_LOW,/* Pin 0 */
      PORT_PIN_LEVEL_LOW,/* Pin 1 */
      PORT_PIN_LEVEL_LOW,/* Pin 2 */
      PORT_PIN_LEVEL_LOW,/* Pin 3 */
      PORT_PIN_LEVEL_LOW,/* Pin 4 */
      PORT_PIN_LEVEL_LOW,/* Pin 5 */
      PORT_PIN_LEVEL_LOW,/* Pin 6 */
      PORT_PIN_LEVEL_LOW,/* Pin 7 */
      PORT_PIN_LEVEL_LOW,/* Pin 8 */
      0U,/* Pin 9 */
      0U,/* Pin 10 */
      0U,/* Pin 11 */
      0U,/* Pin 12 */
      0U,/* Pin 13 */
      0U,/* Pin 14 */
      0U,/* Pin 15 */
      0U /* Reserved */
    },
    /* Port pins drive strength1 configuration */
    Portx_lPdrConfig1(
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin0*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin1*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin2*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin3*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin4*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin5*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin6*/
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT)/*Pin7*/
                  ),
    /* Port pins drive strength2 configuration */
    Portx_lPdrConfig2(
      (PORT_INPUT_LEVEL_CMOS_AUTOMOTIVE|PORT_PIN_PAD_STRENGTH_DEFAULT),/*Pin8*/
      (PORT_PIN_PAD_DEFAULT),/*Pin9*/
      (PORT_PIN_PAD_DEFAULT),/*Pin10*/
      (PORT_PIN_PAD_DEFAULT),/*Pin11*/
      (PORT_PIN_PAD_DEFAULT),/*Pin12*/
      (PORT_PIN_PAD_DEFAULT),/*Pin13*/
      (PORT_PIN_PAD_DEFAULT),/*Pin14*/
      (PORT_PIN_PAD_DEFAULT)/*Pin15*/
                  ),
    {/* Port pin run time mode changeable or not configuration */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 0 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 1 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 2 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 3 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 4 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 5 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 6 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 7 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 8 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 9 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 10 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 11 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 12 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 13 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 14 */
    PORT_PIN_MODE_NOT_CHANGEABLE,/* Pin 15 */
    0U /* Reserved */

    },
    {/* Port pin run time direction changeable or not configuration */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 0 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 1 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 2 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 3 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 4 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 5 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 6 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 7 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 8 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 9 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 10 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 11 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 12 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 13 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 14 */
      PORT_PIN_DIRECTION_NOT_CHANGEABLE ,/* Pin 15 */
      0U /* Reserved */

    },
    {
    /* Port pins direction, characteristics and mode configuration if
    direction is changeable */
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin0*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin1*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin2*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin3*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin4*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin5*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin6*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin7*/
    /* MISRA2012_RULE_10_3_JUSTIFICATION: The port IOCR registers has the
    control bit field for each port pin located  as register bytes. Hence
    typecasting is done for each port pin to uint8*/
      ((uint8)PORT_PIN_IN | PORT_PIN_IN_PULL_UP | PORT_PIN_MODE_GPIO),/*Pin8*/
      (PORT_PIN_DEFAULT),/*Pin9*/
      (PORT_PIN_DEFAULT),/*Pin10*/
      (PORT_PIN_DEFAULT),/*Pin11*/
      (PORT_PIN_DEFAULT),/*Pin12*/
      (PORT_PIN_DEFAULT),/*Pin13*/
      (PORT_PIN_DEFAULT),/*Pin14*/
      (PORT_PIN_DEFAULT)/*Pin15*/
    },
    {/* Port pin run time mode changeable or not configuration */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 0 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 1 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 2 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 3 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 4 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 5 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 6 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 7 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 8 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 9 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 10 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 11 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 12 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 13 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 14 */
      PORT_PIN_EMERGENCY_STOP_DISABLE,/* Pin 15 */
      0U /* Reserved */

    }
  },
};
    
static const uint32 Port_DiscSet[] =
{
  /*        Port0       */
  Port_lDiscSet(
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 0 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 1 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 2 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 3 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 4 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 5 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 6 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 7 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 8 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 9 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 10 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 11 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 12 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 13 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 14 */
    PORT_PIN_ANALOG_INPUT_DISABLE/* Pin 15 */ 
  ),
  /*        Port1       */
  Port_lDiscSet(
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 0 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 1 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 2 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 3 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 4 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 5 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 6 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 7 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 8 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 9 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 10 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 11 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 12 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 13 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 14 */
    PORT_PIN_ANALOG_INPUT_DISABLE/* Pin 15 */ 
  ),
  /*        Port2       */
  Port_lDiscSet(
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 0 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 1 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 2 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 3 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 4 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 5 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 6 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 7 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 8 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 9 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 10 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 11 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 12 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 13 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 14 */
    PORT_PIN_ANALOG_INPUT_DISABLE/* Pin 15 */ 
  ),
  /*        Port33       */
  Port_lDiscSet(
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 0 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 1 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 2 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 3 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 4 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 5 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 6 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 7 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 8 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 9 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 10 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 11 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 12 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 13 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 14 */
    PORT_PIN_ANALOG_INPUT_DISABLE/* Pin 15 */ 
  ),
  /*        Port34       */
  Port_lDiscSet(
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 0 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 1 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 2 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 3 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 4 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 5 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 6 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 7 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 8 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 9 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 10 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 11 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 12 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 13 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 14 */
    PORT_PIN_ANALOG_INPUT_DISABLE/* Pin 15 */ 
  ),
  /*        Port40       */
  Port_lDiscSet(
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 0 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 1 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 2 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 3 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 4 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 5 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 6 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 7 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 8 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 9 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 10 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 11 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 12 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 13 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 14 */
    PORT_PIN_ANALOG_INPUT_DISABLE/* Pin 15 */ 
  ),
  /*        Port41       */
  Port_lDiscSet(
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 0 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 1 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 2 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 3 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 4 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 5 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 6 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 7 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 8 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 9 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 10 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 11 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 12 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 13 */
    PORT_PIN_ANALOG_INPUT_DISABLE,/* Pin 14 */
    PORT_PIN_ANALOG_INPUT_DISABLE/* Pin 15 */ 
  ),

};

    /* LVDS configuration */
static const Port_n_LVDSConfigType Port_kLVDSConfig[] =
{

  { /*             Port13            */
    /*             LPCR0            */
    Port_lLvds(
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PAD_SUPPLY_3_3V,
      PORT_LVDS_PORT_CONTROLLED,
      PORT_LVDS_DISABLE,
      PORT_LVDS_LVDS_VDIFF_ADJ,
      PORT_LVDS_VOSDYN,
      PORT_LVDS_VOSEXT,
      PORT_LVDS_POWER_DOWN,
      PORT_LVDS_TX_PWDPD_DISABLE
      ),
    /*             LPCR1            */
    Port_lLvds(
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PAD_SUPPLY_3_3V,
      PORT_LVDS_PORT_CONTROLLED,
      PORT_LVDS_DISABLE,
      PORT_LVDS_LVDS_VDIFF_ADJ,
      PORT_LVDS_VOSDYN,
      PORT_LVDS_VOSEXT,
      PORT_LVDS_POWER_DOWN,
      PORT_LVDS_TX_PWDPD_DISABLE
      ),
    /*             LPCR2            */
    Port_lLvds(
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PAD_SUPPLY_3_3V,
      PORT_LVDS_PORT_CONTROLLED,
      PORT_LVDS_DISABLE,
      PORT_LVDS_LVDS_VDIFF_ADJ,
      PORT_LVDS_VOSDYN,
      PORT_LVDS_VOSEXT,
      PORT_LVDS_POWER_DOWN,
      PORT_LVDS_TX_PWDPD_DISABLE
      ),
    /*             LPCR3            */
    Port_lLvds(
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PAD_SUPPLY_3_3V,
      PORT_LVDS_PORT_CONTROLLED,
      PORT_LVDS_DISABLE,
      PORT_LVDS_LVDS_VDIFF_ADJ,
      PORT_LVDS_VOSDYN,
      PORT_LVDS_VOSEXT,
      PORT_LVDS_POWER_DOWN,
      PORT_LVDS_TX_PWDPD_DISABLE
      ),
    /*             LPCR4            */
      PORT_LPCR_DEFAULT,
    /*             LPCR5            */
      PORT_LPCR_DEFAULT,
    /*             LPCR6            */
      PORT_LPCR_DEFAULT
  },
  { /*             Port14            */
    /*             LPCR0            */
      PORT_LPCR_DEFAULT,
    /*             LPCR1            */
      PORT_LPCR_DEFAULT,
    /*             LPCR2            */
      PORT_LPCR_DEFAULT,
    /*             LPCR3            */
      PORT_LPCR_DEFAULT,
    /*             LPCR4            */
      PORT_LPCR_DEFAULT,
    /*             LPCR5            */
    Port_lLvds(
      PORT_LVDS_PORT_CONTROLLED,
      PORT_LVDS_DISABLE,
      PORT_LVDS_INTERNAL_TERMINATION,
      PORT_LVDS_POLY_RESISTOR_TERM,
      PORT_LVDS_LVDSH,
      PAD_SUPPLY_3_3V,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT
      ),
    /*             LPCR6            */
      PORT_LPCR_DEFAULT
  },
  { /*             Port21            */
    /*             LPCR0            */
    Port_lLvds(
      PORT_LVDS_PORT_CONTROLLED,
      PORT_LVDS_DISABLE,
      PORT_LVDS_INTERNAL_TERMINATION,
      PORT_LVDS_POLY_RESISTOR_TERM,
      PORT_LVDS_LVDSH,
      PAD_SUPPLY_3_3V,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT
      ),
    /*             LPCR1            */
    Port_lLvds(
      PORT_LVDS_HSCT_CONTROLLED,
      PORT_LVDS_ENABLE,
      PORT_LVDS_INTERNAL_TERMINATION,
      PORT_LVDS_POLY_RESISTOR_TERM,
      PORT_LVDS_LVDSH,
      PAD_SUPPLY_3_3V,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT
      ),
    /*             LPCR2            */
    Port_lLvds(
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PAD_SUPPLY_3_3V,
      PORT_LVDS_HSCT_CONTROLLED,
      PORT_LVDS_ENABLE,
      PORT_LVDS_LVDS_VDIFF_ADJ,
      PORT_LVDS_VOSDYN,
      PORT_LVDS_VOSEXT,
      PORT_LVDS_POWER_DOWN,
      PORT_LVDS_TX_PWDPD_DISABLE
      ),
    /*             LPCR3            */
      PORT_LPCR_DEFAULT,
    /*             LPCR4            */
      PORT_LPCR_DEFAULT,
    /*             LPCR5            */
      PORT_LPCR_DEFAULT,
    /*             LPCR6            */
      PORT_LPCR_DEFAULT
  },
  { /*             Port22            */
    /*             LPCR0            */
    Port_lLvds(
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PAD_SUPPLY_3_3V,
      PORT_LVDS_PORT_CONTROLLED,
      PORT_LVDS_DISABLE,
      PORT_LVDS_LVDS_VDIFF_ADJ,
      PORT_LVDS_VOSDYN,
      PORT_LVDS_VOSEXT,
      PORT_LVDS_POWER_DOWN,
      PORT_LVDS_TX_PWDPD_DISABLE
      ),
    /*             LPCR1            */
    Port_lLvds(
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PORT_LVDS_DEFAULT,
      PAD_SUPPLY_3_3V,
      PORT_LVDS_PORT_CONTROLLED,
      PORT_LVDS_DISABLE,
      PORT_LVDS_LVDS_VDIFF_ADJ,
      PORT_LVDS_VOSDYN,
      PORT_LVDS_VOSEXT,
      PORT_LVDS_POWER_DOWN,
      PORT_LVDS_TX_PWDPD_DISABLE
      ),
    /*             LPCR2            */
      PORT_LPCR_DEFAULT,
    /*             LPCR3            */
      PORT_LPCR_DEFAULT,
    /*             LPCR4            */
      PORT_LPCR_DEFAULT,
    /*             LPCR5            */
      PORT_LPCR_DEFAULT,
    /*             LPCR6            */
      PORT_LPCR_DEFAULT
  }
};
    /* PCSR configuration */
static const Port_n_PCSRConfigType Port_kPCSRConfig[] =
{
  /*           Port0            */
  Port_lPcsr(
      PORT_PCSR_DEFAULT,  /*Pin0*/
      PORT_PCSR_DEFAULT,  /*Pin1*/
      PORT_PCSR_DEFAULT,  /*Pin2*/
      PORT_PCSR_DEFAULT,  /*Pin3*/
      PORT_PCSR_DEFAULT,  /*Pin4*/
      PORT_PCSR_DEFAULT,  /*Pin5*/
      PORT_PCSR_DEFAULT,  /*Pin6*/
      PORT_PCSR_DEFAULT,  /*Pin7*/
      PORT_PCSR_DEFAULT,  /*Pin8*/
      PORT_PCSR_DEFAULT,  /*Pin9*/
      PORT_PCSR_DISABLE,  /*Pin10*/
      PORT_PCSR_DISABLE,  /*Pin11*/
      PORT_PCSR_DEFAULT,  /*Pin12*/
      PORT_PCSR_DEFAULT,  /*Pin13*/
      PORT_PCSR_DEFAULT,  /*Pin14*/
      PORT_PCSR_DEFAULT   /*Pin15*/
                ),
  /*           Port11            */
  Port_lPcsr(
      PORT_PCSR_ENABLE,   /*Pin0*/
      PORT_PCSR_ENABLE,   /*Pin1*/
      PORT_PCSR_ENABLE,   /*Pin2*/
      PORT_PCSR_ENABLE,   /*Pin3*/
      PORT_PCSR_ENABLE,   /*Pin4*/
      PORT_PCSR_DEFAULT,  /*Pin5*/
      PORT_PCSR_ENABLE,   /*Pin6*/
      PORT_PCSR_DEFAULT,  /*Pin7*/
      PORT_PCSR_DEFAULT,  /*Pin8*/
      PORT_PCSR_DEFAULT,  /*Pin9*/
      PORT_PCSR_DEFAULT,  /*Pin10*/
      PORT_PCSR_DEFAULT,  /*Pin11*/
      PORT_PCSR_DEFAULT,  /*Pin12*/
      PORT_PCSR_DEFAULT,  /*Pin13*/
      PORT_PCSR_DEFAULT,  /*Pin14*/
      PORT_PCSR_DEFAULT   /*Pin15*/
                ),
  /*           Port33            */
  Port_lPcsr(
      PORT_PCSR_DISABLE,  /*Pin0*/
      PORT_PCSR_DISABLE,  /*Pin1*/
      PORT_PCSR_DISABLE,  /*Pin2*/
      PORT_PCSR_DISABLE,  /*Pin3*/
      PORT_PCSR_DISABLE,  /*Pin4*/
      PORT_PCSR_DISABLE,  /*Pin5*/
      PORT_PCSR_DISABLE,  /*Pin6*/
      PORT_PCSR_DISABLE,  /*Pin7*/
      PORT_PCSR_DISABLE,  /*Pin8*/
      PORT_PCSR_DISABLE,  /*Pin9*/
      PORT_PCSR_DISABLE,  /*Pin10*/
      PORT_PCSR_DISABLE,  /*Pin11*/
      PORT_PCSR_DISABLE,  /*Pin12*/
      PORT_PCSR_DISABLE,  /*Pin13*/
      PORT_PCSR_DISABLE,  /*Pin14*/
      PORT_PCSR_DISABLE   /*Pin15*/
                ),
  /*           Port34            */
  Port_lPcsr(
      PORT_PCSR_DEFAULT,  /*Pin0*/
      PORT_PCSR_DISABLE,  /*Pin1*/
      PORT_PCSR_DEFAULT,  /*Pin2*/
      PORT_PCSR_DEFAULT,  /*Pin3*/
      PORT_PCSR_DEFAULT,  /*Pin4*/
      PORT_PCSR_DEFAULT,  /*Pin5*/
      PORT_PCSR_DEFAULT,  /*Pin6*/
      PORT_PCSR_DEFAULT,  /*Pin7*/
      PORT_PCSR_DEFAULT,  /*Pin8*/
      PORT_PCSR_DEFAULT,  /*Pin9*/
      PORT_PCSR_DEFAULT,  /*Pin10*/
      PORT_PCSR_DEFAULT,  /*Pin11*/
      PORT_PCSR_DEFAULT,  /*Pin12*/
      PORT_PCSR_DEFAULT,  /*Pin13*/
      PORT_PCSR_DEFAULT,  /*Pin14*/
      PORT_PCSR_DEFAULT   /*Pin15*/
                ),
  /*           Port40            */
  Port_lPcsr(
      PORT_PCSR_DEFAULT,  /*Pin0*/
      PORT_PCSR_DISABLE,  /*Pin1*/
      PORT_PCSR_DISABLE,  /*Pin2*/
      PORT_PCSR_DISABLE,  /*Pin3*/
      PORT_PCSR_DEFAULT,  /*Pin4*/
      PORT_PCSR_DISABLE,  /*Pin5*/
      PORT_PCSR_DEFAULT,  /*Pin6*/
      PORT_PCSR_DEFAULT,  /*Pin7*/
      PORT_PCSR_DEFAULT,  /*Pin8*/
      PORT_PCSR_DEFAULT,  /*Pin9*/
      PORT_PCSR_DISABLE,  /*Pin10*/
      PORT_PCSR_DISABLE,  /*Pin11*/
      PORT_PCSR_DISABLE,  /*Pin12*/
      PORT_PCSR_DEFAULT,  /*Pin13*/
      PORT_PCSR_DEFAULT,  /*Pin14*/
      PORT_PCSR_DISABLE   /*Pin15*/
                )
};
    /*
Array contains information on the modes supported by each port pin
*/
static const Port_n_ModeType Port_kPinSupportedModes[] =
{
  /*     Port0      */
  {
    {
      (uint8)(0xafU),/*Pin0*/
      (uint8)(0xf7U),/*Pin1*/
      (uint8)(0xffU),/*Pin2*/
      (uint8)(0xdfU),/*Pin3*/
      (uint8)(0xdfU),/*Pin4*/
      (uint8)(0xffU),/*Pin5*/
      (uint8)(0xf7U),/*Pin6*/
      (uint8)(0xffU),/*Pin7*/
      (uint8)(0xefU),/*Pin8*/
      (uint8)(0xffU),/*Pin9*/
      (uint8)(0xcfU),/*Pin10*/
      (uint8)(0x1fU),/*Pin11*/
      (uint8)(0x83U),/*Pin12*/
      (uint8)(0x13U),/*Pin13*/
      (uint8)(0x13U),/*Pin14*/
      (uint8)(0x13U) /*Pin15*/
    }
  },
  /*     Port1      */
  {
    {
      (uint8)(0x03U),/*Pin0*/
      (uint8)(0x13U),/*Pin1*/
      (uint8)(0x6bU),/*Pin2*/
      (uint8)(0x33U),/*Pin3*/
      (uint8)(0x1bU),/*Pin4*/
      (uint8)(0x53U),/*Pin5*/
      (uint8)(0x1fU),/*Pin6*/
      (uint8)(0x1bU),/*Pin7*/
      (uint8)(0x03U),/*Pin8*/
      (uint8)(0x47U),/*Pin9*/
      (uint8)(0x07U),/*Pin10*/
      (uint8)(0x07U),/*Pin11*/
      (uint8)(0x47U),/*Pin12*/
      (uint8)(0x77U),/*Pin13*/
      (uint8)(0x43U),/*Pin14*/
      (uint8)(0x03U) /*Pin15*/
    }
  },
  /*     Port2      */
  {
    {
      (uint8)(0xffU),/*Pin0*/
      (uint8)(0x9fU),/*Pin1*/
      (uint8)(0xffU),/*Pin2*/
      (uint8)(0x9fU),/*Pin3*/
      (uint8)(0xffU),/*Pin4*/
      (uint8)(0xffU),/*Pin5*/
      (uint8)(0xbfU),/*Pin6*/
      (uint8)(0xfbU),/*Pin7*/
      (uint8)(0xffU),/*Pin8*/
      (uint8)(0x2fU),/*Pin9*/
      (uint8)(0x03U),/*Pin10*/
      (uint8)(0x0bU),/*Pin11*/
      (uint8)(0x1fU),/*Pin12*/
      (uint8)(0x3fU),/*Pin13*/
      (uint8)(0x07U),/*Pin14*/
      (uint8)(0x5fU) /*Pin15*/
    }
  },
  /*     Port10      */
  {
    {
      (uint8)(0x4fU),/*Pin0*/
      (uint8)(0x3fU),/*Pin1*/
      (uint8)(0x3bU),/*Pin2*/
      (uint8)(0x5bU),/*Pin3*/
      (uint8)(0x3fU),/*Pin4*/
      (uint8)(0xffU),/*Pin5*/
      (uint8)(0x7fU),/*Pin6*/
      (uint8)(0x6fU),/*Pin7*/
      (uint8)(0x1fU),/*Pin8*/
      (uint8)(0x03U),/*Pin9*/
      (uint8)(0x07U),/*Pin10*/
      (uint8)(0x07U),/*Pin11*/
      (uint8)(0x00U),/*Pin12*/
      (uint8)(0x07U),/*Pin13*/
      (uint8)(0x03U),/*Pin14*/
      (uint8)(0x03U) /*Pin15*/
    }
  },
  /*     Port11      */
  {
    {
      (uint8)(0x67U),/*Pin0*/
      (uint8)(0x6fU),/*Pin1*/
      (uint8)(0xfbU),/*Pin2*/
      (uint8)(0xdbU),/*Pin3*/
      (uint8)(0xe7U),/*Pin4*/
      (uint8)(0x23U),/*Pin5*/
      (uint8)(0xffU),/*Pin6*/
      (uint8)(0x03U),/*Pin7*/
      (uint8)(0x03U),/*Pin8*/
      (uint8)(0xabU),/*Pin9*/
      (uint8)(0x9bU),/*Pin10*/
      (uint8)(0xfbU),/*Pin11*/
      (uint8)(0xffU),/*Pin12*/
      (uint8)(0x43U),/*Pin13*/
      (uint8)(0x43U),/*Pin14*/
      (uint8)(0x03U) /*Pin15*/
    }
  },
  /*     Port12      */
  {
    {
      (uint8)(0x43U),/*Pin0*/
      (uint8)(0x27U),/*Pin1*/
      (uint8)(0x00U),/*Pin2*/
      (uint8)(0x00U),/*Pin3*/
      (uint8)(0x00U),/*Pin4*/
      (uint8)(0x00U),/*Pin5*/
      (uint8)(0x00U),/*Pin6*/
      (uint8)(0x00U),/*Pin7*/
      (uint8)(0x00U),/*Pin8*/
      (uint8)(0x00U),/*Pin9*/
      (uint8)(0x00U),/*Pin10*/
      (uint8)(0x00U),/*Pin11*/
      (uint8)(0x00U),/*Pin12*/
      (uint8)(0x00U),/*Pin13*/
      (uint8)(0x00U),/*Pin14*/
      (uint8)(0x00U) /*Pin15*/
    }
  },
  /*     Port13      */
  {
    {
      (uint8)(0xbfU),/*Pin0*/
      (uint8)(0x6bU),/*Pin1*/
      (uint8)(0xffU),/*Pin2*/
      (uint8)(0x6fU),/*Pin3*/
      (uint8)(0xb3U),/*Pin4*/
      (uint8)(0x23U),/*Pin5*/
      (uint8)(0x23U),/*Pin6*/
      (uint8)(0x23U),/*Pin7*/
      (uint8)(0x00U),/*Pin8*/
      (uint8)(0x67U),/*Pin9*/
      (uint8)(0x07U),/*Pin10*/
      (uint8)(0x13U),/*Pin11*/
      (uint8)(0x47U),/*Pin12*/
      (uint8)(0x07U),/*Pin13*/
      (uint8)(0x03U),/*Pin14*/
      (uint8)(0x17U) /*Pin15*/
    }
  },
  /*     Port14      */
  {
    {
      (uint8)(0xffU),/*Pin0*/
      (uint8)(0x87U),/*Pin1*/
      (uint8)(0x4fU),/*Pin2*/
      (uint8)(0x3fU),/*Pin3*/
      (uint8)(0x43U),/*Pin4*/
      (uint8)(0xc3U),/*Pin5*/
      (uint8)(0xdbU),/*Pin6*/
      (uint8)(0x9fU),/*Pin7*/
      (uint8)(0x8fU),/*Pin8*/
      (uint8)(0xffU),/*Pin9*/
      (uint8)(0xfbU),/*Pin10*/
      (uint8)(0x33U),/*Pin11*/
      (uint8)(0x0fU),/*Pin12*/
      (uint8)(0x33U),/*Pin13*/
      (uint8)(0x3fU),/*Pin14*/
      (uint8)(0x07U) /*Pin15*/
    }
  },
  /*     Port15      */
  {
    {
      (uint8)(0x6fU),/*Pin0*/
      (uint8)(0x0fU),/*Pin1*/
      (uint8)(0x6fU),/*Pin2*/
      (uint8)(0x2fU),/*Pin3*/
      (uint8)(0xdfU),/*Pin4*/
      (uint8)(0xefU),/*Pin5*/
      (uint8)(0xefU),/*Pin6*/
      (uint8)(0x9fU),/*Pin7*/
      (uint8)(0xcbU),/*Pin8*/
      (uint8)(0x00U),/*Pin9*/
      (uint8)(0x03U),/*Pin10*/
      (uint8)(0x03U),/*Pin11*/
      (uint8)(0x03U),/*Pin12*/
      (uint8)(0x03U),/*Pin13*/
      (uint8)(0x03U),/*Pin14*/
      (uint8)(0x03U) /*Pin15*/
    }
  },
  /*     Port20      */
  {
    {
      (uint8)(0x2fU),/*Pin0*/
      (uint8)(0x03U),/*Pin1*/
      (uint8)(0x01U),/*Pin2*/
      (uint8)(0x7fU),/*Pin3*/
      (uint8)(0x00U),/*Pin4*/
      (uint8)(0x00U),/*Pin5*/
      (uint8)(0x1fU),/*Pin6*/
      (uint8)(0xa7U),/*Pin7*/
      (uint8)(0xbfU),/*Pin8*/
      (uint8)(0x9bU),/*Pin9*/
      (uint8)(0xffU),/*Pin10*/
      (uint8)(0x8bU),/*Pin11*/
      (uint8)(0x9bU),/*Pin12*/
      (uint8)(0xbbU),/*Pin13*/
      (uint8)(0x0bU),/*Pin14*/
      (uint8)(0x00U) /*Pin15*/
    }
  },
  /*     Port21      */
  {
    {
      (uint8)(0x07U),/*Pin0*/
      (uint8)(0x03U),/*Pin1*/
      (uint8)(0x27U),/*Pin2*/
      (uint8)(0x0fU),/*Pin3*/
      (uint8)(0x0fU),/*Pin4*/
      (uint8)(0x0fU),/*Pin5*/
      (uint8)(0x87U),/*Pin6*/
      (uint8)(0x8fU),/*Pin7*/
      (uint8)(0x00U),/*Pin8*/
      (uint8)(0x00U),/*Pin9*/
      (uint8)(0x00U),/*Pin10*/
      (uint8)(0x00U),/*Pin11*/
      (uint8)(0x00U),/*Pin12*/
      (uint8)(0x00U),/*Pin13*/
      (uint8)(0x00U),/*Pin14*/
      (uint8)(0x00U) /*Pin15*/
    }
  },
  /*     Port22      */
  {
    {
      (uint8)(0xbfU),/*Pin0*/
      (uint8)(0xbfU),/*Pin1*/
      (uint8)(0x3fU),/*Pin2*/
      (uint8)(0x3bU),/*Pin3*/
      (uint8)(0x57U),/*Pin4*/
      (uint8)(0x17U),/*Pin5*/
      (uint8)(0x33U),/*Pin6*/
      (uint8)(0x1fU),/*Pin7*/
      (uint8)(0x37U),/*Pin8*/
      (uint8)(0x13U),/*Pin9*/
      (uint8)(0x37U),/*Pin10*/
      (uint8)(0x1fU),/*Pin11*/
      (uint8)(0x00U),/*Pin12*/
      (uint8)(0x00U),/*Pin13*/
      (uint8)(0x00U),/*Pin14*/
      (uint8)(0x00U) /*Pin15*/
    }
  },
  /*     Port23      */
  {
    {
      (uint8)(0x03U),/*Pin0*/
      (uint8)(0xffU),/*Pin1*/
      (uint8)(0x33U),/*Pin2*/
      (uint8)(0x07U),/*Pin3*/
      (uint8)(0x2fU),/*Pin4*/
      (uint8)(0x6fU),/*Pin5*/
      (uint8)(0x37U),/*Pin6*/
      (uint8)(0x07U),/*Pin7*/
      (uint8)(0x00U),/*Pin8*/
      (uint8)(0x00U),/*Pin9*/
      (uint8)(0x00U),/*Pin10*/
      (uint8)(0x00U),/*Pin11*/
      (uint8)(0x00U),/*Pin12*/
      (uint8)(0x00U),/*Pin13*/
      (uint8)(0x00U),/*Pin14*/
      (uint8)(0x00U) /*Pin15*/
    }
  },
  /*     Port24      */
  {
    {
      (uint8)(0x03U),/*Pin0*/
      (uint8)(0x03U),/*Pin1*/
      (uint8)(0x03U),/*Pin2*/
      (uint8)(0x03U),/*Pin3*/
      (uint8)(0x03U),/*Pin4*/
      (uint8)(0x03U),/*Pin5*/
      (uint8)(0x03U),/*Pin6*/
      (uint8)(0x03U),/*Pin7*/
      (uint8)(0x03U),/*Pin8*/
      (uint8)(0x03U),/*Pin9*/
      (uint8)(0x03U),/*Pin10*/
      (uint8)(0x03U),/*Pin11*/
      (uint8)(0x03U),/*Pin12*/
      (uint8)(0x03U),/*Pin13*/
      (uint8)(0x03U),/*Pin14*/
      (uint8)(0x03U) /*Pin15*/
    }
  },
  /*     Port25      */
  {
    {
      (uint8)(0x03U),/*Pin0*/
      (uint8)(0x03U),/*Pin1*/
      (uint8)(0x03U),/*Pin2*/
      (uint8)(0x03U),/*Pin3*/
      (uint8)(0x03U),/*Pin4*/
      (uint8)(0x03U),/*Pin5*/
      (uint8)(0x03U),/*Pin6*/
      (uint8)(0x03U),/*Pin7*/
      (uint8)(0x03U),/*Pin8*/
      (uint8)(0x03U),/*Pin9*/
      (uint8)(0x03U),/*Pin10*/
      (uint8)(0x03U),/*Pin11*/
      (uint8)(0x03U),/*Pin12*/
      (uint8)(0x03U),/*Pin13*/
      (uint8)(0x03U),/*Pin14*/
      (uint8)(0x03U) /*Pin15*/
    }
  },
  /*     Port26      */
  {
    {
      (uint8)(0x03U),/*Pin0*/
      (uint8)(0x00U),/*Pin1*/
      (uint8)(0x00U),/*Pin2*/
      (uint8)(0x00U),/*Pin3*/
      (uint8)(0x00U),/*Pin4*/
      (uint8)(0x00U),/*Pin5*/
      (uint8)(0x00U),/*Pin6*/
      (uint8)(0x00U),/*Pin7*/
      (uint8)(0x00U),/*Pin8*/
      (uint8)(0x00U),/*Pin9*/
      (uint8)(0x00U),/*Pin10*/
      (uint8)(0x00U),/*Pin11*/
      (uint8)(0x00U),/*Pin12*/
      (uint8)(0x00U),/*Pin13*/
      (uint8)(0x00U),/*Pin14*/
      (uint8)(0x00U) /*Pin15*/
    }
  },
  /*     Port30      */
  {
    {
      (uint8)(0x03U),/*Pin0*/
      (uint8)(0x03U),/*Pin1*/
      (uint8)(0x03U),/*Pin2*/
      (uint8)(0x03U),/*Pin3*/
      (uint8)(0x03U),/*Pin4*/
      (uint8)(0x03U),/*Pin5*/
      (uint8)(0x03U),/*Pin6*/
      (uint8)(0x03U),/*Pin7*/
      (uint8)(0x03U),/*Pin8*/
      (uint8)(0x03U),/*Pin9*/
      (uint8)(0x03U),/*Pin10*/
      (uint8)(0x03U),/*Pin11*/
      (uint8)(0x03U),/*Pin12*/
      (uint8)(0x03U),/*Pin13*/
      (uint8)(0x03U),/*Pin14*/
      (uint8)(0x03U) /*Pin15*/
    }
  },
  /*     Port31      */
  {
    {
      (uint8)(0x03U),/*Pin0*/
      (uint8)(0x03U),/*Pin1*/
      (uint8)(0x03U),/*Pin2*/
      (uint8)(0x03U),/*Pin3*/
      (uint8)(0x03U),/*Pin4*/
      (uint8)(0x03U),/*Pin5*/
      (uint8)(0x03U),/*Pin6*/
      (uint8)(0x03U),/*Pin7*/
      (uint8)(0x03U),/*Pin8*/
      (uint8)(0x03U),/*Pin9*/
      (uint8)(0x03U),/*Pin10*/
      (uint8)(0x03U),/*Pin11*/
      (uint8)(0x03U),/*Pin12*/
      (uint8)(0x03U),/*Pin13*/
      (uint8)(0x03U),/*Pin14*/
      (uint8)(0x03U) /*Pin15*/
    }
  },
  /*     Port32      */
  {
    {
      (uint8)(0x03U),/*Pin0*/
      (uint8)(0x03U),/*Pin1*/
      (uint8)(0x47U),/*Pin2*/
      (uint8)(0x77U),/*Pin3*/
      (uint8)(0xf7U),/*Pin4*/
      (uint8)(0x47U),/*Pin5*/
      (uint8)(0x33U),/*Pin6*/
      (uint8)(0x17U),/*Pin7*/
      (uint8)(0x00U),/*Pin8*/
      (uint8)(0x00U),/*Pin9*/
      (uint8)(0x00U),/*Pin10*/
      (uint8)(0x00U),/*Pin11*/
      (uint8)(0x00U),/*Pin12*/
      (uint8)(0x00U),/*Pin13*/
      (uint8)(0x00U),/*Pin14*/
      (uint8)(0x00U) /*Pin15*/
    }
  },
  /*     Port33      */
  {
    {
      (uint8)(0x57U),/*Pin0*/
      (uint8)(0x3fU),/*Pin1*/
      (uint8)(0xffU),/*Pin2*/
      (uint8)(0xbfU),/*Pin3*/
      (uint8)(0xffU),/*Pin4*/
      (uint8)(0xffU),/*Pin5*/
      (uint8)(0xffU),/*Pin6*/
      (uint8)(0x5fU),/*Pin7*/
      (uint8)(0xafU),/*Pin8*/
      (uint8)(0xffU),/*Pin9*/
      (uint8)(0xbfU),/*Pin10*/
      (uint8)(0xcfU),/*Pin11*/
      (uint8)(0xffU),/*Pin12*/
      (uint8)(0xbfU),/*Pin13*/
      (uint8)(0x8bU),/*Pin14*/
      (uint8)(0x8bU) /*Pin15*/
    }
  },
  /*     Port34      */
  {
    {
      (uint8)(0x00U),/*Pin0*/
      (uint8)(0xb7U),/*Pin1*/
      (uint8)(0x83U),/*Pin2*/
      (uint8)(0x97U),/*Pin3*/
      (uint8)(0x97U),/*Pin4*/
      (uint8)(0x97U),/*Pin5*/
      (uint8)(0x00U),/*Pin6*/
      (uint8)(0x00U),/*Pin7*/
      (uint8)(0x00U),/*Pin8*/
      (uint8)(0x00U),/*Pin9*/
      (uint8)(0x00U),/*Pin10*/
      (uint8)(0x00U),/*Pin11*/
      (uint8)(0x00U),/*Pin12*/
      (uint8)(0x00U),/*Pin13*/
      (uint8)(0x00U),/*Pin14*/
      (uint8)(0x00U) /*Pin15*/
    }
  },
  /*     Port40      */
  {
    {
      (uint8)(0x01U),/*Pin0*/
      (uint8)(0x01U),/*Pin1*/
      (uint8)(0x01U),/*Pin2*/
      (uint8)(0x01U),/*Pin3*/
      (uint8)(0x01U),/*Pin4*/
      (uint8)(0x01U),/*Pin5*/
      (uint8)(0x01U),/*Pin6*/
      (uint8)(0x01U),/*Pin7*/
      (uint8)(0x01U),/*Pin8*/
      (uint8)(0x01U),/*Pin9*/
      (uint8)(0x01U),/*Pin10*/
      (uint8)(0x01U),/*Pin11*/
      (uint8)(0x01U),/*Pin12*/
      (uint8)(0x01U),/*Pin13*/
      (uint8)(0x01U),/*Pin14*/
      (uint8)(0x01U) /*Pin15*/
    }
  },
  /*     Port41      */
  {
    {
      (uint8)(0x01U),/*Pin0*/
      (uint8)(0x01U),/*Pin1*/
      (uint8)(0x01U),/*Pin2*/
      (uint8)(0x01U),/*Pin3*/
      (uint8)(0x01U),/*Pin4*/
      (uint8)(0x01U),/*Pin5*/
      (uint8)(0x01U),/*Pin6*/
      (uint8)(0x01U),/*Pin7*/
      (uint8)(0x01U),/*Pin8*/
      (uint8)(0x00U),/*Pin9*/
      (uint8)(0x00U),/*Pin10*/
      (uint8)(0x00U),/*Pin11*/
      (uint8)(0x00U),/*Pin12*/
      (uint8)(0x00U),/*Pin13*/
      (uint8)(0x00U),/*Pin14*/
      (uint8)(0x00U) /*Pin15*/
    }
  }
/* MISRA2012_RULE_19_2_JUSTIFICATION: Union is needed to access data per port pin
and as a 32 Bit Value*/
};
/* MISRA2012_RULE_8_7_JUSTIFICATION: Module configuration data structure
declaration as per Autosar guidelines. This data structure may be needed
by SW units using Port Driver APIs */
/* MISRA2012_RULE_8_4_JUSTIFICATION: Definition is as per Autosar guidelines */
const Port_ConfigType Port_Config =
{
    /* Port Configuration set  */
  &Port_kConfiguration[0],
  /* Port 40-th Disc configuration set  */
  &Port_DiscSet[0],
  &Port_kPinSupportedModes[0],/* LVDS configuration */
  &Port_kLVDSConfig[0],
  /* PCSR Configuration */
  &Port_kPCSRConfig[0]
};

#define PORT_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Port_Memmap.h header is included without safegaurd.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Port_Memmap.h header included as per Autosar
guidelines. */
#include "Port_MemMap.h"
