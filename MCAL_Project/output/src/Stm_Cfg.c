
/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2018)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Stm_Cfg.c                                                     **
**                                                                            **
**  VERSION   : 4.0.0                                                         **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:30               !!!IGNORE-LINE!!!       **
**                                                                            **
**  GENERATOR : Build b191017-0938                   !!!IGNORE-LINE!!!       **
**                                                                            **
**  BSW MODULE DECRIPTION : Stm.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Stm configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/


/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Include module header File */
#include "Stm.h"
/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/******************************************************************************/
#define STM_START_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Stm_MemMap.h"

/* Select STM module name */
  
/* MISRA2012_RULE_8_4_JUSTIFICATION: The extern declaration for 
Stm_ModuleMap should be done by application.    */ 
/* MISRA2012_RULE_8_9_JUSTIFICATION: Global Constants not
declared within block scope   */ 
/* MISRA2012_RULE_8_7_JUSTIFICATION: Global Constants not
declared within block scope   */
const Stm_ModuleType Stm_ModuleMap[STM_MAX_TIMERS] =
{

  {
    STM_0,
    STM_CMP1_USED
  },

  {
    STM_1,
    STM_CMP0_CMP1_UNUSED
  },

  {
    STM_TIMER_UNUSED,
    STM_CMP0_CMP1_UNUSED
  },



  {
    STM_TIMER_UNUSED,
    STM_CMP0_CMP1_UNUSED
  },





  
};



#define STM_STOP_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration of notification function 
  before MemMap inclusion It complies to Autosar guidelines. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Stm_MemMap.h"
