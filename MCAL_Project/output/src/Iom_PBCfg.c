/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2019)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
***************************************************************************** **
**                                                                            **
**  FILENAME    : Iom_PBcfg.c                                                 **
**                                                                            **
**  VERSION     : 1.30.0_6.0.0                                                     **
**                                                                            **
**  DATE, TIME: 2023-11-11, 18:10:34                !!!IGNORE-LINE!!!      **
**                                                                            **
**  GENERATOR : Build b200227-0222                    !!!IGNORE-LINE!!!       **
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
**  DESCRIPTION  : IOM configuration generated out of ECU configuration       **
**                 file (Iom.bmd/.xdm)                                        **
**                                                                            **
**  MAY BE CHANGED BY USER [yes/no]: No                                       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                       Includes                                             **
*******************************************************************************/


/* Include module header file */
#include "Iom.h"


/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/


/* Memory Mapping the configuration constant */
#define IOM_START_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
  guideline.*/

#include "Iom_MemMap.h"

/*******************************************************************************
**                     Utility Macros                                         **
*******************************************************************************/


/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/


  

/* FPC configuration */

static const Iom_FpcConfigType Iom_kFpcConfiguration[] =
{   
  {
    /* FPC control register value */
    (0x00000000U),
    /* FPC unit number */
    ((uint8) 0U)
  }


};
/* LAM Configuration */

static const Iom_LamConfigType Iom_kLamConfiguration[] =
{
  {
    /* LAM threshold value */ 
    ((uint32)0U),
    /* LAM configuration value */ 
    (0x000000000U),
    /* LAM unit number */
    ((uint8) 0U)
  }
  
}; 

/* ECM configuration */

static const Iom_EcmConfigType Iom_kEcmConfiguration =
{ 
  /* ECM counter configuration */
  0x00000000U,
  (0x00000000U)
};

/* MISRA2012_RULE_8_7_JUSTIFICATION: Module configuration data structure
declaration as per Autosar guidelines. This data structure may be needed
by SW units using Iom Driver APIs */   
/* MISRA2012_RULE_8_4_JUSTIFICATION: Definition is as per Autosar guidelines */   

const Iom_ConfigType Iom_Config =
{
  &Iom_kFpcConfiguration[0],
  &Iom_kLamConfiguration[0],
  &Iom_kEcmConfiguration,
  /* GTM configuration */
  (0x00000000U),
  
  /* Clc configuration */
  0x00000100U,
  /* Max Channels configured */ 
  1U
}; 
#define IOM_STOP_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
guideline.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */

#include "Iom_MemMap.h"
 
  
