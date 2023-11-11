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
**  FILENAME  : Fee_PBcfg.h                                                   **
**                                                                            **
**  VERSION   : 7.0.0                                                         **
**                                                                            **
**  DATE, TIME: 2023-11-11, 17:37:32    !!!IGNORE-LINE!!!                 **
**                                                                            **
**  GENERATOR : Build b191017-0938                                          **
**                                                                            **
**  BSW MODULE DECRIPTION : Fee.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Fee configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of FEE Driver,                           **
**                     AUTOSAR Release 4.2.2 and 4.4.0                        **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

#ifndef FEE_PBCFG_H
#define FEE_PBCFG_H
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/


/*******************************************************************************
**                      Global Const Declaration                              **
*******************************************************************************/
#define FEE_START_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/* [cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}]*/
/* [cover parentID={566ED99C-0D96-46ac-97BF-E97B04E2C700}]*/
/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]*/
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]*/
/* [cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}]*/
#include "Fee_MemMap.h"
/* Extern declaration of Fee Config Root */
extern const Fee_ConfigType Fee_Config;
#define FEE_STOP_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
#include "Fee_MemMap.h"

#endif  /* FEE_PBCFG_H */

