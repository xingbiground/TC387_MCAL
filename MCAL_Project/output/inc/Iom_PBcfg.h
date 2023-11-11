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
********************************************************************************
**                                                                            **
**  FILENAME  : Iom_PBcfg.h                                                   **
**                                                                            **
**  VERSION   : 1.30.0_4.0.0                                                         **
**                                                                            **
**  DATE, TIME: 2023-11-11, 18:10:34           !!!IGNORE-LINE!!!           **
**                                                                            **
**  GENERATOR : Build b200227-0222               !!!IGNORE-LINE!!!           **
**                                                                            **
**  BSW MODULE DECRIPTION : Iom.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Iom configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of Iom Driver,                           **
**                       AUTOSAR Release 4.2.2                                **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef IOM_PBCFG_H
#define IOM_PBCFG_H
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Iom.h"

/*******************************************************************************
**                      Global Const Definitions                              **
*******************************************************************************/
#define IOM_START_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Iom_MemMap.h"
/* Extern declaration of Iom Config Root */
extern const Iom_ConfigType Iom_Config;
#define IOM_STOP_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "Iom_MemMap.h"
#endif  /* IOM_PBCFG_H */

