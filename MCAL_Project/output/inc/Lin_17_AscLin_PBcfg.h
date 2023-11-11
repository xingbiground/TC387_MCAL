/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2020)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Lin_17_AscLin_PBcfg.h                                         **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:30      !!!IGNORE-LINE!!!               **
**                                                                            **
**  GENERATOR : Build b191017-0938          !!!IGNORE-LINE!!!               **
**                                                                            **
**  BSW MODULE DECRIPTION : Lin_17_AscLin.bmd                                 **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Lin configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of Lin Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef Lin_17_AscLin_PBCFG_H
#define Lin_17_AscLin_PBCFG_H
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Lin_17_AscLin.h"

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/* <!-- [cover parentID={30A87C0A-EE42-4166-AA4D-EB91CBB4EEC0}]
[/cover] --> */
/* <!-- [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] --> */
#define LIN_17_ASCLIN_START_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safegaurd.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"
/* Extern declaration of Lin Config Root */
extern const Lin_17_AscLin_ConfigType Lin_17_AscLin_Config;
/* <!-- [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
[/cover] --> */
#define LIN_17_ASCLIN_STOP_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines
Lin_17_AscLin_Memmap.h header is included without safegaurd.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Lin_17_AscLin_Memmap.h header included
as per Autosar guidelines. */
#include "Lin_17_AscLin_MemMap.h"
#endif  /* Lin_17_AscLin_PBCFG_H */
