
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
**  FILENAME  : FlsLoader_Cfg.c                                               **
**                                                                            **
**  VERSION   : 8.0.0                                                         **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:31              !!!IGNORE-LINE!!!           **
**                                                                            **
**  GENERATOR : Build b191017-0938                !!!IGNORE-LINE!!!           **
**                                                                            **
**  BSW MODULE DECRIPTION : FlsLoader.bmd                                     **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : FlsLoader configuration generated out of ECUC file         **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/


/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
  /* Inclusion of Flash header file */
#include "FlsLoader.h"
/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/******************************************************************************/
/*******************************************************************************
** Name             : FlsLoader_GenerateModuleMap                             **
**                                                                            **
** Description      : Macro to generate core-channel mappings for a module    **
**                                                                            **
*******************************************************************************/




#define FLSLOADER_START_SEC_CONST_QM_LOCAL_8
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "FlsLoader_MemMap.h"

/* Number of sectors for each PFlash banks */
const uint8 FlsLoader_PFlashSectorCount[FLSLOADER_NUM_OF_PFLASH_BANK] =
{
    FLSLOADER_NUM_OF_PF0_SECTORS,
    FLSLOADER_NUM_OF_PF1_SECTORS,
    FLSLOADER_NUM_OF_PF2_SECTORS,
    FLSLOADER_NUM_OF_PF3_SECTORS
};

#define FLSLOADER_STOP_SEC_CONST_QM_LOCAL_8
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration of notification function 
  before MemMap inclusion It complies to Autosar guidelines. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "FlsLoader_MemMap.h"


#define FLSLOADER_START_SEC_CONST_QM_LOCAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "FlsLoader_MemMap.h"

/* Start address of all the PFlash banks */
const uint32 FlsLoader_PFlashOffset[FLSLOADER_NUM_OF_PFLASH_BANK] =
{
    (uint32)0XA0000000U,
    (uint32)0XA0300000U,
    (uint32)0XA0600000U,
    (uint32)0XA0900000U
};

/* End address of all the PFlash banks */
const uint32 FlsLoader_PFlashEndAddress[FLSLOADER_NUM_OF_PFLASH_BANK] =
{
    (uint32)0XA02FFFFFU,
    (uint32)0XA05FFFFFU,
    (uint32)0XA08FFFFFU,
    (uint32)0XA09FFFFFU
};


#define FLSLOADER_STOP_SEC_CONST_QM_LOCAL_32
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration of notification function 
  before MemMap inclusion It complies to Autosar guidelines. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "FlsLoader_MemMap.h"
