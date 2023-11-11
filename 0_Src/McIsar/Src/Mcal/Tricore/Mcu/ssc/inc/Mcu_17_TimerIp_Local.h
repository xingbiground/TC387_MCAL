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
**  FILENAME     : Mcu_17_TimerIp_Local.h                                     **
**                                                                            **
**  VERSION      : 6.0.0                                                      **
**                                                                            **
**  DATE         : 2021-02-22                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  TRACEABILITY : [cover parentID={54AF25B8-78A1-4d21-BA36-AF97B7635066}]    **
**                                                                            **
**  DESCRIPTION  : Mcu Driver Local header definition file                    **
**                                                                            **
**  SPECIFICATION(S) : Specification of Mcu Driver, AUTOSAR Release 4.2.2     **
**                     and 4.4.0                                              **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/* [cover parentID={F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}][/cover] */
#ifndef MCU_17_TIMERIP_LOCAL_H
#define MCU_17_TIMERIP_LOCAL_H

#define MCU_17_TIMERIP_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Mcu_MemMap.h"
extern const uint32 Mcu_17_Eru_ChUserData[MCU_17_ERU_NO_OF_OGU];

extern const uint32 Mcu_17_Stm_ChUserData[MCU_17_STM_NO_OF_TIMERS];

#if (MCU_GTM_USED == STD_ON)
extern const uint32
Mcu_17_Gtm_TomChUserData\
[MCU_17_GTM_NO_OF_TOM_MODULES][MCU_17_GTM_NO_OF_TOM_CHANNELS];

extern const uint32
Mcu_17_Gtm_AtomChUserData\
[MCU_17_GTM_NO_OF_ATOM_MODULES][MCU_17_GTM_NO_OF_ATOM_CHANNELS];
#endif

#define MCU_17_TIMERIP_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header included as per Autosar
   guidelines. */
#include "Mcu_MemMap.h"

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define MCU_17_TIMERIP_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_16
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header included as per Autosar
   guidelines. */
#include "Mcu_MemMap.h"

extern const uint16
Mcu_17_Ccu6_ChUserData\
[MCU_17_CCU6_NO_OF_KERNELS][MCU_17_CCU6_NO_OF_COMPARATORS];

extern const uint16 Mcu_17_Gpt12_ChUserData[MCU_17_GPT12_NO_OF_TIMERS];

#if (MCU_GTM_USED == STD_ON)

extern const uint16
Mcu_17_Gtm_TimChUserData\
[MCU_17_GTM_NO_OF_TIM_MODULES][MCU_17_GTM_NO_OF_TIM_CHANNELS];
#endif

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define MCU_17_TIMERIP_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_16
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header included as per Autosar
   guidelines. */
#include "Mcu_MemMap.h"

#endif /* MCU_17_TIMERIP_LOCAL_H */
