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
**  FILENAME     : SchM_Fls_17_Dmu.h                                          **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2020-09-25                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY : [cover parentID={}]                                        **
**                                                                            **
**  DESCRIPTION  : SchM file for Fls driver                                   **
**                                                                            **
**  SPECIFICATION(S) : Specification of RTE, AUTOSAR Release 4.2.2 and 4.4.0  **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
#ifndef FLS_17_DMU_SCHM_H
#define FLS_17_DMU_SCHM_H

/*******************************************************************************
** Syntax : void Fls_17_Dmu_MainFunction(void)                                **
**                                                                            **
** Service ID:  0x06                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out): : None                                                   **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description :                                                              **
**         This service shall perform the processing of the flash read,write  **
**         and erase jobs                                                     **
*******************************************************************************/
extern void Fls_17_Dmu_MainFunction(void);

#endif /* End of FLS_17_DMU_SCHM_H */
