
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
**  FILENAME  : Smu_PBCfg.c                                                   **
**                                                                            **
**  VERSION   : 8.0.0                                                         **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:31             !!!IGNORE-LINE!!!            **
**                                                                            **
**  GENERATOR : Build b191017-0938               !!!IGNORE-LINE!!!            **
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
**  DESCRIPTION  : Smu configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#include "Smu.h"


      


/*******************************************************************************
**                      Private Macro definition                              **
*******************************************************************************/

/*******************************************************************************
**                      Configuration Options                                 **
*******************************************************************************/

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/


/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/


/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Global Funtion Declarations                           **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
/* Memory Mapping the configuration constant */
#define SMU_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED 
/* MISRA2012_RULE_4_10_JUSTIFICATION: Smu_Memmap.h is repeatedly included
* without include guard. This is as per AUTOSAR */
#include "Smu_MemMap.h"

/* SMU Module Configuration */


const Smu_ConfigType Smu_Config =
{
  
  /* FSP Cfg for Smu_core*/
  (uint32)0x400000U,
  
  /* AGC Cfg for SmuCore*/
  (uint32)0x1U,
  
  /* RTC Cfg for SmuCore*/
  (uint32)0x3fff00U,
  
  /* RTAC00 Cfg for SmuCore*/
  (uint32)0x0U,
  
  /* RTAC01 Cfg for SmuCore*/
  (uint32)0x0U,
  
  /* RTAC10 Cfg for SmuCore*/
  (uint32)0x0U,
  
  /* RTAC11 Cfg for SmuCore*/
  (uint32)0x0U,
  
  /* CMD_STDBY config for SmuStdby*/
  (uint32)0x0U, 
  
  /*AlarmConfig for SmuCore*/
  {
    0x0U,0x0U,0x0U,
    0x0U,0x0U,0x0U,
    0x0U,0x0U,0x0U,
    0x0U,0x0U,0x0U,
    0x0U,0x0U,0x0U,
    0x0U,0x0U,0x0U,
    0x0U,0x0U,0x0U,
    0x0U,0x0U,0x0U,
    0x0U,0x0U,0x0U,
    0x0U,0x0U,0x0U,
    0x0U,0x1U,0x0U,
    0x0U,0x0U,0x0U
  },
  
  /*AlarmFspConfig for SmuCore*/
  {
    0x0U,0x0U,0x0U,0x0U,0x0U,0x0U,0x0U,0x0U,0x0U,0x0U,0x0U,0x0U},
  
  /*AlarmFspConfig for SmuStdby*/
  {
    0x0U,0x0U}
};
#define SMU_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED 
/* MISRA2012_RULE_4_10_JUSTIFICATION: Smu_Memmap.h is repeatedly included
 * without include guard. This is as per AUTOSAR */
/* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of notification functions
 * before include memap.h - Accepted deviation in AUTOSAR */
#include "Smu_MemMap.h"
