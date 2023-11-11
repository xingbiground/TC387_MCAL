
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
**  FILENAME  : Ocu_PBcfg.c                                                   **
**                                                                            **
**  VERSION   : 11.0.0                                                         **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:30             !!!IGNORE-LINE!!!        **
**                                                                            **
**  GENERATOR : Build b191017-0938               !!!IGNORE-LINE!!!          **
**                                                                            **
**  BSW MODULE DECRIPTION : NA                                                **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Ocu configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) :Specification of OCU Driver,AUTOSAR Release 4.2.2&4.4.0 **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                       Includes                                             **
*******************************************************************************/

/* Include module header File */
#include "Ocu.h"

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
/*MISRA2012_RULE_2_5_JUSTIFICATION:
Uses depends upon configuration done in configuration tool*/
#define OCU_GTM_INTERRUPT_LEVEL_MODE          (0U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
Uses depends upon configuration done in configuration tool*/
#define OCU_GTM_INTERRUPT_PULSE_MODE          (1U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
Uses depends upon configuration done in configuration tool*/
#define OCU_GTM_INTERRUPT_PULSE_NOTIFY_MODE   (2U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
Uses depends upon configuration done in configuration tool*/
#define OCU_GTM_INTERRUPT_SINGLE_PULSE_MODE   (3U)

/*
Define for Core identification 
*/
/*MISRA2012_RULE_2_5_JUSTIFICATION:
Uses depends upon configuration done in configuration tool*/
#define OCU_CORE0   (0U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
Uses depends upon configuration done in configuration tool*/
#define OCU_CORE1   (0x100U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
Uses depends upon configuration done in configuration tool*/
#define OCU_CORE2   (0x200U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
Uses depends upon configuration done in configuration tool*/
#define OCU_CORE3   (0x300U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
Uses depends upon configuration done in configuration tool*/
#define OCU_CORE4   (0x400U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
Uses depends upon configuration done in configuration tool*/
#define OCU_CORE5   (0x500U)

/* Alternate port pin selection  */
/*MISRA2012_RULE_2_5_JUSTIFICATION:
Uses depends upon configuration done in configuration tool*/
#define OCU_ALT_SELA ((uint32)0x00)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
Uses depends upon configuration done in configuration tool*/
#define OCU_ALT_SELB ((uint32)0x01)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
Uses depends upon configuration done in configuration tool*/
#define OCU_ALT_SELC ((uint32)0x02)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
Uses depends upon configuration done in configuration tool*/
#define OCU_ALT_SELD ((uint32)0x03)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
Uses depends upon configuration done in configuration tool*/
#define OCU_ALT_SELE ((uint32)0x04)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
Uses depends upon configuration done in configuration tool*/
#define OCU_ALT_SELF ((uint32)0x05)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
Uses depends upon configuration done in configuration tool*/
#define OCU_ALT_SELG ((uint32)0x06)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
Uses depends upon configuration done in configuration tool*/
#define OCU_ALT_SELH ((uint32)0x07)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
Uses depends upon configuration done in configuration tool*/
#define OCU_ALT_SELI ((uint32)0x08)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
Uses depends upon configuration done in configuration tool*/
#define OCU_ALT_SELJ ((uint32)0x09)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
Uses depends upon configuration done in configuration tool*/
#define OCU_ALT_SELK ((uint32)0x0A)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
Uses depends upon configuration done in configuration tool*/
#define OCU_ALT_SELL ((uint32)0x0B)

/* Pin Used */
/*MISRA2012_RULE_2_5_JUSTIFICATION:
Uses depends upon configuration done in configuration tool*/
#define OCU_FALSE (0U)
/*MISRA2012_RULE_2_5_JUSTIFICATION:
Uses depends upon configuration done in configuration tool*/
#define OCU_TRUE  (1U)
  

/* MCU code generation dependency */


/*******************************************************************************
**                       Function Declarations                                **
*******************************************************************************/

/******************************************************************************/

extern void Ocu_Notification_Channel0 (void);


/******************************************************************************/

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/

      


 
/* 
Channel Configuration 
*/
/***********Start of CORE 0 configurations**************/

/* Memory mapping for constants */
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define OCU_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
guideline.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Ocu_MemMap.h"


static const Ocu_ChannelConfigType Ocu_kChannelConfigCore_0[ ] =
{
  {
    /* OCU Channel 0 */
    &Ocu_Notification_Channel0,/*Notification-function name*/
    (uint32)123456,/*DefaultThreshold*/
    (uint32)0xFFFFFFU,/*MaxCounterValue*/
    {
      OCU_GTM_ATOM_SHARED, /* Assigned Hw Unit */
      0x0005, /* Assigned Hw Unit Number */
      (uint8)OCU_LOW, /* Pin default state */
      OCU_TRUE, /* Pin Used */
      OCU_FALSE, /* Dma Used */
      OCU_FALSE, /* Adc Used */
      OCU_GTM_TBU_TS0, /* Clock Select */
      0 /* Reserved and padded to 32 bits */
    },
  }              
};

static const Ocu_CoreConfigType Ocu_kConfigCore_0 =
{
  /* Pointer to Channel Configuration structure */
  &Ocu_kChannelConfigCore_0[0],
  /* MaxChannelCore */
  1
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define OCU_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
guideline.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Ocu_MemMap.h"
/***********End of CORE 0 configurations**************/
/* 
Channel Configuration 
*/
/***********Start of CORE 1 configurations**************/
/***********End of CORE 1 configurations**************/
/* 
Channel Configuration 
*/
/***********Start of CORE 2 configurations**************/
/***********End of CORE 2 configurations**************/
/* 
Channel Configuration 
*/
/***********Start of CORE 3 configurations**************/
/***********End of CORE 3 configurations**************/
/* 
Channel Configuration 
*/
/***********Start of CORE 4 configurations**************/
/***********End of CORE 4 configurations**************/
/* 
Channel Configuration 
*/
/***********Start of CORE 5 configurations**************/
/***********End of CORE 5 configurations**************/
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define OCU_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
guideline.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Ocu_MemMap.h"

const Ocu_ConfigType Ocu_Config =
{
  /* Pointer to channel configuration set per core */
  {
    &Ocu_kConfigCore_0,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR
  },
  #if (OCU_SINGLE_CORE == STD_OFF)
  {
    (uint16)(OCU_CORE0 | (uint8)0)
  }
  #endif
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code due to Autosar Naming constraints.*/
#define OCU_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
guideline.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Ocu_MemMap.h"
