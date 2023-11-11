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
**  FILENAME     : SchM_Adc.h                                                 **
**                                                                            **
**  VERSION      : 7.0.0                                                      **
**                                                                            **
**  DATE         : 2018-08-09                                                 **
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
**  DESCRIPTION  : SchM file for Adc driver                                   **
**                                                                            **
**                                                                            **
**                                                                            **
**  SPECIFICATION(S) : Specification of RTE, AUTOSAR Release 4.2.2            **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
/*[cover parentID={CCC95E46-59A7-4511-8391-227F30F803CF}] SchM_Adc_h[/cover]*/
#ifndef ADC_SCHM_H
#define ADC_SCHM_H
/* [cover parentID={EF1D2627-0E98-4443-B1DE-DFB609DCBE6C}] */
extern void SchM_Enter_Adc_KernelData(void);
extern void SchM_Exit_Adc_KernelData(void);
/*[/cover] */
/* [cover parentID={9684FA7D-407D-41a9-8F62-B5DB01CFF0FF}] */
extern void SchM_Enter_Adc_SrcRegAccess(void);
extern void SchM_Exit_Adc_SrcRegAccess(void);
/*[/cover] */
#endif /* ADC_SCHM_H */
