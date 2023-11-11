/*******************************************************************************
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
**  FILENAME  : Wdg_17_Scu_PBCfg.c                                            **
**                                                                            **
**  VERSION   : 12.0.0                                                        **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:31                   !!!IGNORE-LINE!!!    **
**                                                                            **
**  GENERATOR : Build b191017-0938                       !!!IGNORE-LINE!!!   **
**                                                                            **
**  BSW MODULE DECRIPTION : Wdg.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Wdg configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of Wdg Driver, AUTOSAR Release           **
**                     4.2.2 and 4.4.0                                        **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Include module header File */

/* Module header file, which includes module configuration(Wdg_17_Cfg.h) file */
#include "Wdg_17_Scu.h"

/******************************************************************************
**                      Imported Compiler Switch Checks                      **
*******************************************************************************/

/******************************************************************************
**                      Private Macro Definitions                            **
*******************************************************************************/

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/

      
  /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
#define WDG_17_SCU_START_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
#include "Wdg_17_Scu_MemMap.h"




static const Mcu_17_Stm_TimerConfigType Wdg_StmConfig_0 =
{
  /*STM compare Reg */
  0x00000000U,
  /* StmTimerId*/
  0x0U,
  /*Cmp Register Id*/
  0x0U,
  /* Value for the CMCON register */
  0x1FU,
  /* Reserved */
  0x00U
};


const struct Wdg_17_Scu_ConfigType Wdg_17_Scu_Config_0 =
{
  
  /*STM compare Reg used for Servicing*/
  &Wdg_StmConfig_0,
  
  /*FastMode reload value*/
  (uint16)61629,
  /*SlowMode reload value*/
  65413,
  /*Fast refresh time*/
  7,
  /*Slow refresh time*/
  15,
  /*Wdg initial timeout*/
  10000,
  /*Wdg maximum timeout*/
  32000,
  /*Default mode*/
  WDGIF_OFF_MODE,
  /*Core Disable allowed status*/
  TRUE,
  /*Core Id*/
  0,
  /*CPU Wdg Password*/
  60
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
#define WDG_17_SCU_STOP_SEC_CONFIG_DATA_ASIL_B_CORE0_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
#include "Wdg_17_Scu_MemMap.h"
    
  /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
#define WDG_17_SCU_START_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
#include "Wdg_17_Scu_MemMap.h"




static const Mcu_17_Stm_TimerConfigType Wdg_StmConfig_1 =
{
  /*STM compare Reg */
  0x00000000U,
  /* StmTimerId*/
  0x1U,
  /*Cmp Register Id*/
  0x0U,
  /* Value for the CMCON register */
  0x1FU,
  /* Reserved */
  0x00U
};


const struct Wdg_17_Scu_ConfigType Wdg_17_Scu_Config_1 =
{
  
  /*STM compare Reg used for Servicing*/
  &Wdg_StmConfig_1,
  
  /*FastMode reload value*/
  (uint16)301,
  /*SlowMode reload value*/
  4500,
  /*Fast refresh time*/
  150,
  /*Slow refresh time*/
  1000,
  /*Wdg initial timeout*/
  10000,
  /*Wdg maximum timeout*/
  32000,
  /*Default mode*/
  WDGIF_SLOW_MODE,
  /*Core Disable allowed status*/
  TRUE,
  /*Core Id*/
  1,
  /*CPU Wdg Password*/
  60
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
due to Autosar Naming constraints.*/
#define WDG_17_SCU_STOP_SEC_CONFIG_DATA_ASIL_B_CORE1_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code. Local
function declared before MemMap header file */
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
#include "Wdg_17_Scu_MemMap.h"



