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
**  FILENAME     : SchM_Dsadc.h                                               **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2021-09-08                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY :                                                            **
**                                                                            **
**  DESCRIPTION  : SchM file for Dsadc driver                                 **
**                                                                            **
**                                                                            **
**                                                                            **
**  SPECIFICATION(S) : Specification of RTE, AUTOSAR Release 4.2.2            **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
/*[cover parentID={614C1E58-7F0D-457f-B44A-41BF7974FB76}] SchM_Dsadc_h[/cover]*/
#ifndef DSADC_SCHM_H
#define DSADC_SCHM_H

/* [cover parentID={114CFF05-9CCF-4e64-A7F3-8EF2752136A6}] */
extern void SchM_Enter_Dsadc_ChannelData(void);
extern void SchM_Exit_Dsadc_ChannelData(void);
/*[/cover] */

/* [cover parentID={EB3AFCA9-8D15-4167-87A3-7A99D451D3B9}] */
extern void SchM_Enter_Dsadc_IntegratorRestart(void);
extern void SchM_Exit_Dsadc_IntegratorRestart(void);
/*[/cover] */


#endif /* DSADC_SCHM_H */
