/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2017)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : SchM_Pwm_17_GtmCcu6.h                                      **
**                                                                            **
**  VERSION      : 1.0.0                                                      **
**                                                                            **
**  DATE         : 2017-09-12                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : SchM file for Pwm driver                                   **
**                                                                            **
**  SPECIFICATION(S) : Specification of RTE, AUTOSAR Release 4.2.2            **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/
#ifndef PWM_17_GTM_SCHM_H
#define PWM_17_GTM_SCHM_H

extern void SchM_Enter_Pwm_17_GtmCcu6_HandleNotification(void);
extern void SchM_Exit_Pwm_17_GtmCcu6_HandleNotification(void);
extern void SchM_Enter_Pwm_17_GtmCcu6_PeriodAndDutyUpdate(void);
extern void SchM_Exit_Pwm_17_GtmCcu6_PeriodAndDutyUpdate(void);

#endif /* PWM_17_GTM_SCHM_H */
