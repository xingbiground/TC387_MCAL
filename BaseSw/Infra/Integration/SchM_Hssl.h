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
**  FILENAME     : SchM_Hssl.h                                                 **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2019-05-15                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : SchM file for HSSL driver                                   **
**                                                                            **
**  SPECIFICATION(S) : Specification of RTE, AUTOSAR Release 4.2.2            **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
#ifndef HSSL_SCHM_H
#define HSSL_SCHM_H

extern void SchM_Enter_Hssl_ChannelStatusLock(void);
extern void SchM_Exit_Hssl_ChannelStatusLock(void);

extern void SchM_Enter_Hssl_ActivateSlave(void);
extern void SchM_Exit_Hssl_ActivateSlave(void);

extern void SchM_Enter_Hssl_DeactivateSlave(void);
extern void SchM_Exit_Hssl_DeactivateSlave(void);

extern void SchM_Enter_Hssl_DmaOperatedCmdQueue(void);
extern void SchM_Exit_Hssl_DmaOperatedCmdQueue(void);

#endif /* HSSL_SCHM_H */
