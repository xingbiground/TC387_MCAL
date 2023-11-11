/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2023)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : Mcu_17_TimerIp.c                                           **
**                                                                            **
**  VERSION      : 49.0.0                                                     **
**                                                                            **
**  DATE         : 2023-05-22                                                 **
**                                                                            **
**  VARIANT      : Variant PB                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Timer IP functions source file                             **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/*[cover parentID={F2756C3A-492E-44d2-8568-B4B9891F2239}][/cover]*/
/* [cover parentID={F5CF0050-FA3F-4e14-8C3E-FD0E8CB08831}][/cover] */
#include "Mcu.h"
#include "Mcu_17_TimerIp.h"
#include "Mcu_17_TimerIp_Local.h"

#if (MCU_SAFETY_ENABLE == STD_ON)
#include "Mcal_SafetyError.h"
#endif

#if (MCU_GTM_USED == STD_ON)
#include "SchM_Mcu.h"
#include "IfxGtm_bf.h"
#endif

#if (MCU_17_TIMERIP_WDG_USER == STD_ON)
#include "Wdg_17_Scu_Cbk.h"
#endif

#if (MCU_17_TIMERIP_PWM_USER == STD_ON)
#include "Pwm_17_GtmCcu6_Cbk.h"
#endif

#if (MCU_17_TIMERIP_GPT_USER == STD_ON)
#include "Gpt_Cbk.h"
#endif

#if (MCU_17_TIMERIP_ICU_USER == STD_ON)
#include "Icu_17_TimerIp_Cbk.h"
#endif

#if (MCU_17_TIMERIP_STM_USER == STD_ON)
#include "Stm_Cbk.h"
#endif

#if (MCU_17_TIMERIP_DSADC_USER == STD_ON)
#include "Dsadc_Cbk.h"
#endif

#if (MCU_17_TIMERIP_OCU_USER == STD_ON)
#include "Ocu_Cbk.h"
#endif

/* CCU6 SFR */
#include "IfxCcu6_reg.h"
#include "IfxCcu6_bf.h"

/* GPT12 SFR */
#include "IfxGpt12_reg.h"
#include "IfxGpt12_bf.h"

/* STM SFR */
#include "IfxStm_reg.h"
#include "IfxStm_bf.h"

/* ERU IFX Macros */
#include "IfxScu_reg.h"
#include "IfxScu_bf.h"

/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/


/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
#if (MCU_GTM_USED == STD_ON)
#define GTM_BIT_SET                             (0x1U)
#define GTM_BIT_CLEAR                           (0x0U)

/* Macros for GTM ICM registers */
#define GTM_TIM_ICM_BASE_ADDRESS                (&GTM_ICM_IRQG_2)
#define GTM_TOM_ICM_BASE_ADDRESS                (&GTM_ICM_IRQG_6)
#define GTM_ATOM_ICM_BASE_ADDRESS               (&GTM_ICM_IRQG_9)

#define GTM_GET_TIM_INT_STATUS                  (0x1U)
#define GTM_GET_TOM_INT_STATUS                  (0x3U)
#define GTM_GET_ATOM_INT_STATUS                 (0x3U)

/* Macros related to GTM timer user data table */
#define GTM_USER_ID_MSK                         (0xFFU)
#define GTM_LOG_CH_ID_MSK                       (0xFFFFU)
#define GTM_LOG_CH_ID_BITPOS                    (0x8U)  /* Bit position 8 */


#define GTM_ATOM_MODULES_IN_ICM_REG             (0x4U)
#define GTM_CHANNELS_PER_ATOM_MODULE            (MCU_17_GTM_NO_OF_ATOM_CHANNELS)


#define GTM_TIM_MODULES_IN_ICM_REG              (0x4U)
#define GTM_CHANNELS_PER_TIM_MODULE             (MCU_17_GTM_NO_OF_TIM_CHANNELS)

#define GTM_TOM_MODULES_IN_ICM_REG              (0x2U)
#define GTM_CHANNELS_PER_TOM_MODULE             (MCU_17_GTM_NO_OF_TOM_CHANNELS)

#define GTM_OUTEN_ENDIS_CTRL_MSK                (0xFFFFFFFFU)
#define GTM_TOM_EN_MSK                          (0x3U)
#define GTM_ENDIS_OUTEN_BIT_INDEX               (0x3UL)
#define GTM_ATOM_EN_MSK                         (0x3U)
#define TOUTSEL_LEN                             (0x3U)
#define MCAL_SELx_TOUTSEL                       (0x8U)
#define GTM_TIM_RST_RST_CH_LEN                  (0x1)
#define GTM_TIM_CH_CTRL_TIM_EN_LEN              (0x1)
#define GTM_TOUTSEL_SELx_LEN                    (0x4)
#define GTM_TIMINSEL_CHxSEL_LEN                 (0x4)
#define TIM_CTRL_RST_VAL                        (0xFFFFFFFEU)
#define GTM_SPINLOCK_TIMEOUT                    (0xAU)
#define GTM_TGC_CHANNEL_MASK                    (0x7U)
#define GTM_TGC_DIVIDER                         ((uint8)0x3U)
#endif
/* End of #if (MCU_GTM_USED == STD_ON) */

/* CCU6 Timer related macros */
#define CCU6_KERNEL_MSK                         (0xFFU)
#define CCU6_TIMER_POS                          (0x08U)
#define CCU6_TIMER_MSK                          (0xFFU)
#define CCU6_COMPARATOR_POS                     (0x10U)
#define CCU6_COMPARATOR_MSK                     (0xFFU)
#define CCU6_TCTR0_T12_DEINIT_LEN               (0x8)
#define CCU6_TCTR0_T12_DEINIT_VAL               (0x0)

#define CCU6_TCTR0_T13_DEINIT_LEN               (0x6)
#define CCU6_TCTR0_T13_DEINIT_VAL               (0x0)

#define CCU6_MODCTR_T12_DEINIT_VAL              (0x0)
#define CCU6_MODCTR_T13_DEINIT_VAL              (0x0)

#define CCU6_PSLR_T12_DEINIT_VAL                (0x0)
#define CCU6_PSLR_T13_DEINIT_VAL                (0x0)

#define CCU6_IEN_T12_DEINIT_VAL                 (0x0)
#define CCU6_IEN_T13_DEINIT_VAL                 (0x0)
#define CCU6_IEN_CC6_DEINIT_VAL                 (0x0)

#define CCU6_T12PR_CC6_DEINIT_VAL               (0x0)
#define CCU6_T12_CC6_DEINIT_VAL                 (0x0)
#define CCU6_CC6xSR_DEINIT_VAL                  (0x0)
#define CCU6_T13PR_CC6_DEINIT_VAL               (0x0)
#define CCU6_T13_CC6_DEINIT_VAL                 (0x0)
#define CCU6_INP_T12_DEINIT_VAL                 (0x2)
#define CCU6_INP_T13_DEINIT_VAL                 (0x3)
#define CCU6_INP_CC6x_DEINIT_VAL                (0x0)
#define CCU6_PISEL0_CC6x_DEINIT_VAL             (0x0)
#define CCU6_T12MSEL_MSEL6x_DEINIT_VAL          (0x0)
#define CCU6_PISEL2_ISCNTx_DEINIT_VAL           (0x0)
#define CCU6_PISEL2_TxEXT_DEINIT_VAL            (0x0)
#define CCU6_PISEL2_IST13HR_DEINIT_VAL          (0x0)
#define CCU6_CMPSTAT_PS_BITS_DEINIT_VAL         (0x0)
#define CCU6_CMPSTAT_COUT6xPS_DEINIT_VAL        (0x0)
#define CCU6_CMPSTAT_T13IM_DEINIT_VAL           (0x0)
#define CCU6_CMPMODIF_MCC6xS_DEINIT_VAL         (0x0)
#define CCU6_CMPMODIF_MCC6xR_DEINIT_VAL         (0x1)
#define CCU6_TCTR2_T12_DEINIT_VAL               (0x0)

#define CCU6_TCTR0_T12CLK_LEN                   (0x3)
#define CCU6_TCTR0_T12PRE_LEN                   (0x1)
#define CCU6_TCTR0_CTM_LEN                      (0x1)
#define CCU6_MODCTR_T12MODEN_LEN                (0x2)
#define CCU6_PSLR_PSL_LEN                       (0x2)
#define CCU6_TCTR0_T13CLK_LEN                   (0x3)
#define CCU6_TCTR0_T13PRE_LEN                   (0x1)
#define CCU6_MODCTR_ECT13O_LEN                  (0x1)
#define CCU6_MODCTR_T12MODEN_MSK                (0x3U)
#define CCU6_PSLR_PSL_MSK                       (0x3U)
#define CCU6_PSLR_PSL63_OFF                     (0x2U)
#define CCU6_MODCTR_ECT13O_OFF                  (0x2)
#define CCU6_PSLR_PSL63_LEN                     (0x1)
#define CCU6_T12MSEL_MSEL60_LEN                 (0x4)
#define CCU6_T12MSEL_MSEL60_MSK                 (0xFU)
#define CCU6_PISEL0_ISCC60_LEN                  (0x2)
#define CCU6_IEN_ENT12PM_MSK                    (0x1U)
#define CCU6_IEN_ENT12PM_LEN                    (0x1)
#define CCU6_IEN_ENCC6xRF_LEN                   (0x2)
#define CCU6_IEN_ENCC6xRF_MSK                   (0x3U)
#define CCU6_IEN_ENCC6xRF_POS                   (0x1U)
#define CCU6_IEN_ENT13PM_LEN                    (0x1)
#define CCU6_IEN_ENT13PM_MSK                    (0x1U)
#define CCU6_IEN_ENT13CM_LEN                    (0x1)
#define CCU6_IEN_ENT13CM_MSK                    (0x1U)
#define CCU6_IEN_ENT13CM_POS                    (0x1U)
#define CCU6_INP_INPT12_LEN                     (0x2)
#define CCU6_INP_INPT12_MSK                     (0x3U)
#define CCU6_INP_INPT12_POS                     (0x2U)
#define CCU6_INP_INPT13_LEN                     (0x2)
#define CCU6_INP_INPT13_MSK                     (0x3U)
#define CCU6_INP_INPT13_POS                     (0x2U)
#define CCU6_INP_INPCC60_LEN                    (0x2)
#define CCU6_INP_INPCC60_MSK                    (0x3U)
#define CCU6_TCTR4_T12RS_LEN                    (0x1)
#define CCU6_T12_START                          (0x1)
#define CCU6_TCTR4_T13RS_LEN                    (0x1)
#define CCU6_T13_START                          (0x1)
#define CCU6_TCTR4_T13RR_LEN                    (0x1)
#define CCU6_T13_STOP                           (0x1)
#define CCU6_TCTR4_T12RR_LEN                    (0x1)
#define CCU6_T12_STOP                           (0x1)
#define CCU6_TCTR4_T12STR_LEN                   (0x1)
#define CCU6_T12_STR                            (0x1)
#define CCU6_TCTR4_T13STR_LEN                   (0x1)
#define CCU6_T13_STR                            (0x1)
#define CCU6_TIMER_INT_STAT_RST                 (0x1)
#define CCU6_TIMER_RCC6xRF_INT_STAT_RST         (0x3)
#define CCU6_ISR_RT12PM_LEN                     (0x1)
#define CCU6_ISR_RT13PM_LEN                     (0x1)
#define CCU6_ISR_RT13CM_LEN                     (0x1)
#define CCU6_IEN_RCC6xRF_LEN                    (0x2)
#define CCU6_IEN_SINGLE_EDGE                    (0x1)
#define CCU6_IEN_BOTH_EDGE                      (0x2)
#define CCU6_TCTR2_T12SSC_LEN                   (0x1)
#define CCU6_TCTR2_T12SSC_MSK                   (0x1U)
#define CCU6_TCTR2_T12RSEL_LEN                  (0x2)
#define CCU6_TCTR2_T12RSEL_MSK                  (0x3U)
#define CCU6_PISEL2_ISCNT12_LEN                 (0x2)
#define CCU6_PISEL2_ISCNT12_MSK                 (0x3U)
#define CCU6_PISEL2_T12EXT_LEN                  (0x1)
#define CCU6_PISEL2_T12EXT_MSK                  (0x1U)
#define CCU6_PISEL2_ISCNT13_LEN                 (0x2)
#define CCU6_PISEL2_T13EXT_LEN                  (0x1)
#define CCU6_PISEL2_IST13HR_LEN                 (0x2)
#define CCU6_CMPSTAT_COUT63PS_LEN               (0x1)
#define CCU6_CMPSTAT_T13IM_LEN                  (0x1)
#define CCU6_CMPSTAT_PS_BITS_LEN                (0x2)
#define CCU6_CMPSTAT_PS_BITS_MSK                (0x2U)
#define CCU6_CMPMODIF_MCC60S_LEN                (0x1)
#define CCU6_CMPMODIF_MCC60R_LEN                (0x1)
#define CCU6_CMPMODIF_MCC63S_LEN                (0x1)
#define CCU6_CMPMODIF_MCC63R_LEN                (0x1)
#define CCU6_IEN_ENT12OM_MSK                    (0x1u)
#define CCU6_IEN_ENTRPF_MSK                     (0x1u)
#define CCU6_IEN_ENCHE_MSK                      (0x1u)
#define CCU6_IEN_ENWHE_MSK                      (0x1u)
#define CCU6_IEN_ENIDLE_MSK                     (0x1u)
#define CCU6_IEN_ENSTR_MSK                      (0x1u)
#define CCU6_IEN_ENT12OM_LEN                    (0x1)
#define CCU6_IEN_ENTRPF_LEN                     (0x1)
#define CCU6_IEN_ENCHE_LEN                      (0x1)
#define CCU6_IEN_ENWHE_LEN                      (0x1)
#define CCU6_IEN_ENIDLE_LEN                     (0x1)
#define CCU6_IEN_ENSTR_LEN                      (0x1)


#define CCU6_T13_INT_PM_CM_MSK                  (0x300U)
#define CCU6_T12_INT_PM_MSK                     (0x80U)
#define CCU6_T12_INT_CC6x_MSK                   (0x3U)
#define CCU6_T12_MSK                            (0xFFFFU)
#define CCU6_PISEL_MSK                          (0x3U)
#define CCU6_COMPARATOR_BITLEN                  (0x2U)
#define CCU6_BIT_CLEAR                          (0x0U)
#define CCU6_KERNEL_ENABLE                      (0x0U)
#define CCU6_BIT_SET                            (0x1U)

#define CCU6_USER_ID_MSK                        (0xFFU)
#define CCU6_ISR_STS_LEN                        (0x5U)
#define CCU6_LOG_CH_ID_MSK                      (0xFFU)
#define CCU6_LOG_CH_ID_BITPOS                   (0x8U)

/* GPT12 Timer related macros */
#define GPT12_TIMER_ENABLE                      ((uint8)0x0U)
#define GPT12_PISEL_IST2IN_LEN                  (0x1)
#define GPT12_PISEL_IST2EUD_LEN                 (0x1)
#define GPT12_PISEL_ISTxEUD_OFF                 (0x2)

#define GPT12_PISEL_IST3IN_LEN                  (0x2)
#define GPT12_PISEL_IST3EUD_LEN                 (0x2)

#define GPT12_PISEL_IST4IN_LEN                  (0x2)
#define GPT12_PISEL_IST4EUD_LEN                 (0x2)

#define GPT12_PISEL_IST5IN_LEN                  (0x1)
#define GPT12_PISEL_IST5EUD_LEN                 (0x1)

#define GPT12_PISEL_IST6IN_LEN                  (0x1)
#define GPT12_PISEL_IST6EUD_LEN                 (0x1)
#define GPT12_TxCON_RESET_VAL                   (0x0U)

#define GPT12_PISEL_ISTxIN_RESET_VAL            (0x0)
#define GPT12_PISEL_ISTxEUD_RESET_VAL           (0x0)

#define GPT12_Tx_RESET_VAL                      (0x0)
#define GPT12_TxCON_TxR_LEN                     (0x1)
#define GPT12_TxCON_TxR_OFF                     (0x6)
#define GPT12_Tx_START                          (0x1)
#define GPT12_Tx_STOP                           (0x0)
#define GPT12_TxCTRL_MSK                        ((uint32)0x1FFFU)

/* Macros related to GPT12 timer user data table */
#define GPT12_USER_ID_MSK                       (0xFFU)
#define GPT12_BPS_NEG_MSK                       (0xE7FFU)
#define GPT12_BPS_MSK                           (0x1800U)
#define GPT12_LOG_CH_ID_MSK                     (0xFFU)
#define GPT12_LOG_CH_ID_BITPOS                  (0x8U)
#define GPT12_BIT_SET                           (0x1U)

/* ERU Channel related Macros */
#define ERU_FCSTART                             ((uint32)0x10U)
#define ERU_EIFR_MASK                           ((uint32)0xFF000000U)
#define ERU_EIFR_OFFSET                         (0x18U)
#define ERU_CH_OFFSET                           (0xFFU)
#define ERU_IGP_LEN                             (0x2)
#define ERU_OGU_OFFSET                          (0x4U)
#define ERU_BIT_SET                             (0x1U)

/* Macros related to ERU Channel user data table */
#define ERU_LOG_CH_ID_MSK                       (0xFF00U)
#define ERU_USER_ID_MSK                         (0xFF0000U)
#define ERU_IN_CH_ID_MSK                        (0xFFU)
#define ERU_USER_ID_POS                         (0x10U)
#define ERU_LOG_CH_ID_POS                       (0x8U)
#define ERU_PDRR_PDR_MSK                        (0x1U)


/* Macros related to STM timer user data table */
#define STM_TIMER_ID_MASK                       (0xFFU)
#define STM_COMPARATOR_MASK                     (0xFFU)
#define STM_ICR_MASK                            (0x5U)
#define STM_COMP_INT_DIS                        ((uint8)0x0U)
#define STM_ICR_CMP0_EN                         ((uint8)0x1U)
#define STM_ICR_CMP1_EN                         ((uint8)0x5U)
#define STM_ICR_LEN                             (0x3)
#define STM_ISCR_CMPIRR_LEN                     (0x1)
#define STM_CMCON_MSIZE_LEN                     (0x5)
#define STM_ICR_CMPIR_LEN                       (0x1)
#define STM_ICR_CMPEN_LEN                       (0x1)
#define STM_CMP0                                (0x0U)

/* Macro to fetch the position of the bit that is set */
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro
 * 'MCU_GET_SETBIT_POS'
 * defined to fetch the position of the bit that is set.
 * No side effects foreseen by violating this MISRA rule. */
#define MCU_GET_SETBIT_POS(REG)     ((uint8)(0x1FU - \
                                                  Mcal_CountLeadingZeros(REG)))

/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/
/*[cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}][/cover]*/
#define MCU_17_TIMERIP_START_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Mcu_MemMap.h"

static const Mcu_17_Timer_CallbackFuncPtrType \
Mcu_17_Timer_DrivFuncCallbackLst[TIMER_NO_OF_CALLBACK] =
{
  /* ADC driver callback notification */
  NULL_PTR,

  /* WDG driver callback notification */
  #if (MCU_17_TIMERIP_WDG_USER == STD_ON)
  &Wdg_17_Scu_Isr,
  #else
  NULL_PTR,
  #endif

  /* PWM driver callback notification */
  #if (MCU_17_TIMERIP_PWM_USER == STD_ON)
  &Pwm_17_GtmCcu6_Isr,
  #else
  NULL_PTR,
  #endif

  /* GPT driver callback notification */
  #if (MCU_17_TIMERIP_GPT_USER == STD_ON)
  &Gpt_Isr,
  #else
  NULL_PTR,
  #endif

  /* ICU driver callback notification */
  #if (MCU_17_TIMERIP_ICU_USER == STD_ON)
  &Icu_17_TimerIp_Timer_Isr,
  #else
  NULL_PTR,
  #endif

  /* OCU driver callback notification */
  #if (MCU_17_TIMERIP_OCU_USER == STD_ON)
  &Ocu_Timer_Isr,
  #else
  NULL_PTR,
  #endif

  /* DSADC driver callback notification */
  #if (MCU_17_TIMERIP_DSADC_USER == STD_ON)
  /* MISRA2012_RULE_11_1_JUSTIFICATION: 'Dsadc_TimerIsr' API arguments are
   * defined with module specific data types but are basically uint32.
   * No side effects foreseen by violating this MISRA rule */
  &Dsadc_TimerIsr,
  #else
  NULL_PTR,
  #endif

  /* STM driver callback notification */
  #if (MCU_17_TIMERIP_STM_USER == STD_ON)
  &Stm_Isr,
  #else
  NULL_PTR,
  #endif
};

static Ifx_CCU6* const Mcu_17_Ccu6_Kernel[MCU_17_CCU6_NO_OF_KERNELS] =
{
  &MODULE_CCU60,
  #if ( MCU_17_CCU6_NO_OF_KERNELS > 1U )
  &MODULE_CCU61
  #endif
};

static Ifx_STM* const Mcu_17_Stm[MCAL_NO_OF_CORES] =
{
  &MODULE_STM0,

  #if ( MCAL_NO_OF_CORES > 1U )
  &MODULE_STM1,
  #endif

  #if ( MCAL_NO_OF_CORES > 2U )
  &MODULE_STM2,
  #endif

  #if ( MCAL_NO_OF_CORES > 3U )
  &MODULE_STM3,
  #endif

  #if ( MCAL_NO_OF_CORES > 4U )
  &MODULE_STM4,
  #endif

  #if ( MCAL_NO_OF_CORES > 5U )
  &MODULE_STM5
  #endif
};

static volatile uint32* const \
Mcu_17_Gpt12_TimerCtrlReg[MCU_17_GPT12_NO_OF_TIMERS] =
{
  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  (volatile uint32*)&MODULE_GPT120.T2CON.U,
  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  (volatile uint32*)&MODULE_GPT120.T3CON.U,
  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  (volatile uint32*)&MODULE_GPT120.T4CON.U,
  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  (volatile uint32*)&MODULE_GPT120.T5CON.U,
  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  (volatile uint32*)&MODULE_GPT120.T6CON.U
  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
};

#define MCU_17_TIMERIP_STOP_SEC_CONST_ASIL_B_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Mcu_MemMap.h"



#if (MCU_GTM_USED == STD_ON)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define MCU_17_TIMERIP_START_SEC_VAR_INIT_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Mcu_MemMap.h"
/* MISRA2012_RULE_8_9_JUSTIFICATION: No side effects foreseen
 * by violating this MISRA rule, as the variable is accessed via pointer by
 * different API's. */
static uint32 Mcu_17_Tgc_LockAddress \
[MCU_17_GTM_NO_OF_TOM_MODULES][MCU_17_GTM_NO_OF_TOM_TGC] =
{
  /*TGC0, TGC1*/
  {0U, 0U},    /* TOM 0 */
  #if (MCU_17_GTM_NO_OF_TOM_MODULES > 0x1U)
  {0U, 0U},    /* TOM 1 */
  #endif
  #if (MCU_17_GTM_NO_OF_TOM_MODULES > 0x2U)
  {0U, 0U},    /* TOM 2 */
  #endif
  #if (MCU_17_GTM_NO_OF_TOM_MODULES > 0x3U)
  {0U, 0U},    /* TOM 3 */
  #endif
  #if (MCU_17_GTM_NO_OF_TOM_MODULES > 0x4U)
  {0U, 0U},    /* TOM 4 */
  #endif
  #if (MCU_17_GTM_NO_OF_TOM_MODULES > 0x5U)
  {0U, 0U},    /* TOM 5 */
  #endif
};

/* MISRA2012_RULE_8_9_JUSTIFICATION: No side effects foreseen
 * by violating this MISRA rule, as the variable is accessed via pointer by
 * different API's. */
static uint32 Mcu_17_Agc_LockAddress[MCU_17_GTM_NO_OF_ATOM_MODULES]   =
{
  0U, /* ATOM 0  */
  #if (MCU_17_GTM_NO_OF_ATOM_MODULES > 0x1U)
  0U, /* ATOM 1  */
  #endif
  #if (MCU_17_GTM_NO_OF_ATOM_MODULES > 0x2U)
  0U, /* ATOM 2  */
  #endif
  #if (MCU_17_GTM_NO_OF_ATOM_MODULES > 0x3U)
  0U, /* ATOM 3  */
  #endif
  #if (MCU_17_GTM_NO_OF_ATOM_MODULES > 0x4U)
  0U, /* ATOM 4  */
  #endif
  #if (MCU_17_GTM_NO_OF_ATOM_MODULES > 0x5U)
  0U, /* ATOM 5  */
  #endif
  #if (MCU_17_GTM_NO_OF_ATOM_MODULES > 0x6U)
  0U, /* ATOM 6  */
  #endif
  #if (MCU_17_GTM_NO_OF_ATOM_MODULES > 0x7U)
  0U, /* ATOM 7  */
  #endif
  #if (MCU_17_GTM_NO_OF_ATOM_MODULES > 0x8U)
  0U, /* ATOM 8  */
  #endif
  #if (MCU_17_GTM_NO_OF_ATOM_MODULES > 0x9U)
  0U, /* ATOM 9 */
  #endif
  #if (MCU_17_GTM_NO_OF_ATOM_MODULES > 0xAU)
  0U, /* ATOM 10 */
  #endif
  #if (MCU_17_GTM_NO_OF_ATOM_MODULES > 0xBU)
  0U, /* ATOM 11 */
  #endif
};
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define MCU_17_TIMERIP_STOP_SEC_VAR_INIT_ASIL_B_GLOBAL_32
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Mcu_MemMap.h"
#endif
/* End of #if (MCU_GTM_USED == STD_ON) */
/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
#if (MCU_GTM_USED == STD_ON)
    
#define MCU_17_TIMERIP_START_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header included as per Autosar
   guidelines. */
#include "Mcu_MemMap.h"

LOCAL_INLINE uint8 Mcu_17_Gtm_lGetTimIrqStatus(const uint8 Module, \
    const uint8 Channel);

LOCAL_INLINE uint8 Mcu_17_Gtm_lGetTomIrqStatus(const uint8 Module,
    const uint8 Channel);

LOCAL_INLINE uint8 Mcu_17_Gtm_lGetAtomIrqStatus(const uint8 Module,
    const uint8 Channel);

LOCAL_INLINE uint8 Mcu_17_Gtm_lGetIntSource(const uint32 Value, \
    const uint8 Index);

LOCAL_INLINE uint32* Mcu_17_lGetLockAddress(const uint8 Module, \
    const uint8 Index, const Mcu_17_Gtm_TimerOutType TimerType);

#define MCU_17_TIMERIP_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header included as per Autosar
   guidelines. */
#include "Mcu_MemMap.h"

#endif
/* End of #if (MCU_GTM_USED == STD_ON) */

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
#define MCU_17_TIMERIP_START_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header included as per Autosar
   guidelines. */
#include "Mcu_MemMap.h"

#if (MCU_GTM_USED == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={2AE715F1-A045-4a15-A6D1-A5816915906B}] **
**                                                                            **
** Syntax           : void Mcu_17_Gtm_TomChannelInit                          **
**                    (                                                       **
**                     const Mcu_17_Gtm_TomAtomChConfigType * const ConfigPtr **
**                    )                                                       **
**                                                                            **
** Description      : This interface configures an instance of TOM channel.   **
**                    Consumer of a TOM channel invokes this interface at the **
**                    time of channel's initialization.                       **
**                                                                            **
** Service ID       : 0x60                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : ConfigPtr - Pointer to configuration data of a          **
**                    TOM channel                                             **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void Mcu_17_Gtm_TomChannelInit
(const Mcu_17_Gtm_TomAtomChConfigType * const ConfigPtr)
{
  uint8 Module;
  uint8 Channel;

  Ifx_GTM_TOM_CH* TomChannelRegPtr;
  /* Retrieve the TOM module index value */
  Module = (uint8)((ConfigPtr->TimerId & GTM_MODULE_NO_MASK) >>
                   GTM_MODULE_NO_OFF);

  /* Retrieve the TOM module channel number */
  Channel = (uint8)((ConfigPtr->TimerId & GTM_CHANNEL_NO_MASK) >>
                    GTM_CHANNEL_NO_OFF);

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */

  TomChannelRegPtr = GTM_TOM_CH_POINTER((uint8)Module, Channel);

  /* Clear any pending interrupts associated with TOM channel register */
  TomChannelRegPtr->IRQ.NOTIFY.U = GTM_TOM_CLR_PENDING_IRQ;

  /* Disable all TOM interrupts */
  TomChannelRegPtr->IRQ.EN.U = GTM_TOM_REG_RESET;

  /* Configure the TOM Channel control register */
  TomChannelRegPtr->CTRL.U = ConfigPtr->TimerChCtrlReg;

  /* Configure the TOM Channel CCU0 counter register */
  TomChannelRegPtr->CN0.U = ConfigPtr->TimerChCN0Reg;

  /* Configure the TOM Channel CCU0 compare register */
  TomChannelRegPtr->CM0.U = ConfigPtr->TimerChCM0Reg;

  /* Configure the TOM Channel CCU1 compare register */
  TomChannelRegPtr->CM1.U = ConfigPtr->TimerChCM1Reg;

  /* Configure the TOM Channel CCU0 compare shadow register */
  TomChannelRegPtr->SR0.U = ConfigPtr->TimerChSR0Reg;

  /* Configure the TOM Channel CCU1 compare shadow register */
  TomChannelRegPtr->SR1.U = ConfigPtr->TimerChSR1Reg;

  /* Configure the Interrupt mode of  TOM Channel register */
  TomChannelRegPtr->IRQ.MODE.U = ((ConfigPtr->TimerChIntEnMode >>
                                    GTM_TOM_IRQ_MODE_POS) &
                                  (uint32)IFX_GTM_TOM_CH_IRQ_MODE_IRQ_MODE_MSK);

  /* Enable the interrupts associated with TOM Channel register */
  TomChannelRegPtr->IRQ.EN.U = (ConfigPtr->TimerChIntEnMode &
                               (uint32)GTM_TOM_IRQ_EN_REG_MSK);
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability     : [cover parentID={D27F70DF-1073-4640-9355-D9545B8E23C0}] **
**                                                                            **
** Syntax           : void Mcu_17_Gtm_TomChannelShadowTransfer                **
**                    (                                                       **
**                      const uint8 Module,                                   **
**                      const uint8 Channel                                   **
**                    )                                                       **
**                                                                            **
** Description      : This interface is used to initiate a copy of values in  **
**                    shadow registers, Compare values (duty, period) and     **
**                    Clock Source, of the specified TOM channel to its main  **
**                    timer registers.                                        **
**                                                                            **
** Service ID       : 0x61                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : Module  - TOM Module ID                                 **
**                    Channel - TOM Channel ID                                **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void Mcu_17_Gtm_TomChannelShadowTransfer
(
  const uint8 Module,
  const uint8 Channel
)
{
  Mcu_17_Gtm_TomTgc * TomTgcRegPtr;
  uint32* LockAddr;
  uint32  EndisCtrlBackup;
  uint32  OutenCtrlBackup;
  uint32  FupdCtrlBackup;
  uint32  FupdDisableCh;
  uint8 TomTgcIndex = (Channel >> GTM_TGC_DIVIDER);

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TomTgcRegPtr = GTM_TOM_TGC_POINTER(Module, TomTgcIndex);

  /* Calculate the value to disable force update of CM0, CM1 and CRK_SRC
   * registers for the input TOM channel
   */

  FupdDisableCh = ((uint32)GTM_TOM_FORCE_UPDATE_DISABLE <<
                   ((uint32)GTM_TOM_BITS_PER_CHAN *
                    (uint32)((uint32)Channel & GTM_TGC_CHANNEL_MASK)));

  /* Get the Lock address */
  /* [cover parentID={1EA2039E-058C-45ac-9C86-5D792BABE9FA}]
   * Get lock address
   * [/cover] */
  LockAddr = Mcu_17_lGetLockAddress(Module, TomTgcIndex, MCU_GTM_TIMER_TOM);

  /* [cover parentID={4FF44850-AB0C-454f-8C00-B371EFCC5A94}]
   * Enter Critical Section for TOM
   * [/cover] */
  SchM_Enter_Mcu_TomTgcReg();

  /* Acquire Spinlock */
  /* [cover parentID={BF2234C6-D5CF-487c-A5F9-39451006A386}]
   * Acquire SpinLock
   * [/cover] */
  Mcal_GetSpinlock(LockAddr, GTM_SPINLOCK_TIMEOUT);

  /* Backup of ENDIS_CTRL, OUTEN_CTRL and FUPD_CTRL registers */
  /* [cover parentID={EE66DBCE-8D4D-4698-92E9-2C12575C3A63}]
   * Backup content of Control and Status registers of given TOM Module
   * [/cover] */
  EndisCtrlBackup = TomTgcRegPtr->TGC_ENDIS_CTRL.U;
  OutenCtrlBackup = TomTgcRegPtr->TGC_OUTEN_CTRL.U;
  FupdCtrlBackup = TomTgcRegPtr->TGC_FUPD_CTRL.U;

  /* Disable the update of ENDIS_STAT and OUTEN_STAT on a trigger */
  TomTgcRegPtr->TGC_ENDIS_CTRL.U = GTM_TOM_DISABLE_STAT_UPDATE;
  TomTgcRegPtr->TGC_OUTEN_CTRL.U = GTM_TOM_DISABLE_STAT_UPDATE;

  /* Disable the Reset CN0 and force update of all channels */
  TomTgcRegPtr->TGC_FUPD_CTRL.U = GTM_DISABLE_RSTCN0_FUPD;

  /* Enable force update of CM0, CM1 and CRK_SRC registers for the
   * input TOM channel */
  TomTgcRegPtr->TGC_FUPD_CTRL.U = ((uint32)GTM_TOM_FORCE_UPDATE_ENABLE <<
                                   ((uint32)GTM_TOM_BITS_PER_CHAN *
                             (uint32)((uint32)Channel & GTM_TGC_CHANNEL_MASK)));

  /* Initiate Host trigger to update of CM0, CM1 and CLK_SRC
   * registers from their respective shadow registers.*/
  /* [cover parentID={0B276B86-8906-4ba4-A54E-EB8AF076C523}]
   * Initiate Host trigger to update the Compare match and Clock source
   * registers
   * [/cover] */
  (TomTgcRegPtr->TGC_GLB_CTRL.U) |= GTM_TOM_HOST_TRIGGER_ENABLE;

  /* A delay is provided to allow the update of CM0, CM1 and CLK_SRC registers
   * on the next FXCLK. The delay should correspond to a minimum value of
   * 1 FXCLK clock tick, since the force update is execute synchronized to
   * FXCLK clock. This delay is realized using few NOP instruction,
   * which should provide sufficient delay,so that at least 1 FXCLK clock tick
   * to occur*/
  NOP();
  NOP();
  NOP();

  /* Disable force update of CM0, CM1 and CRK_SRC registers for the \
   * input TOM channel */
  TomTgcRegPtr->TGC_FUPD_CTRL.U = FupdDisableCh;

  /* Restore back the contents of FUPD_CTRL, ENDIS_STAT and
   * OUTEN_STAT registers */
  TomTgcRegPtr->TGC_FUPD_CTRL.U = (uint32)(FupdCtrlBackup ^ \
                                  (uint32)GTM_RESTORE_RSTCN0_FUPD);
  TomTgcRegPtr->TGC_ENDIS_CTRL.U = EndisCtrlBackup;
  TomTgcRegPtr->TGC_OUTEN_CTRL.U = OutenCtrlBackup;

  /* Release Spinlock */
  /* [cover parentID={A9655A5B-DE8E-446a-A53E-88D3ED27E193}]
   * Release Spinlock
   * [/cover] */
  Mcal_ReleaseSpinlock(LockAddr);

  /* Exit critical section */
  /* [cover parentID={5231B25E-9026-4360-A738-5C070B46958E}]
   * Exit Critical Section
   * [/cover] */
  SchM_Exit_Mcu_TomTgcReg();
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability     : [cover parentID={B35342B6-7E9C-4d88-9389-3C806EA46BBD}] **
**                                                                            **
** Syntax           : void Mcu_17_Gtm_TomChannelDeInit                        **
**                    (                                                       **
**                      const uint8 Module,                                   **
**                      const uint8 Channel                                   **
**                    )                                                       **
**                                                                            **
** Description      : This interface resets the TOM channel registers to its  **
**                    reset value.                                            **
**                                                                            **
** Service ID       : 0x63                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : Module  - TOM Module ID                                 **
**                    Channel - TOM Channel ID                                **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void Mcu_17_Gtm_TomChannelDeInit
(
  const uint8 Module,
  const uint8 Channel
)
{
  Ifx_GTM_TOM_CH * TomChannelRegPtr; /* Pointer to TOM channel Register */
  Mcu_17_Gtm_TomTgc * TomTgcRegPtr;
  uint32* LockAddr;
  uint8 TomTgcIndex = (Channel >> GTM_TGC_DIVIDER);
  uint8 BitPos = ((uint8)IFX_GTM_TOM_TGC_GLB_CTRL_RST_CH0_OFF +
                  (Channel & GTM_TGC_CHANNEL_MASK));

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TomChannelRegPtr = GTM_TOM_CH_POINTER(Module, Channel);

  /* Clear any pending interrupts associated with TOM channel register */
  TomChannelRegPtr->IRQ.NOTIFY.U = GTM_TOM_CLR_PENDING_IRQ;

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TomTgcRegPtr = GTM_TOM_TGC_POINTER(Module, TomTgcIndex);

  /* Get the Lock address */
  /* [cover parentID={C5CC4845-EDB2-4fae-B617-890BC56E59A7}]
   * Get Lock Address
   * [/cover] */
  LockAddr = Mcu_17_lGetLockAddress(Module, TomTgcIndex, MCU_GTM_TIMER_TOM);

  /* [cover parentID={5505F749-8997-48da-A5F2-E83545032723}]
   * Enter Critical Section
   * [/cover] */
  SchM_Enter_Mcu_TomTgcReg();

  /* Acquire Spinlock */
  /* [cover parentID={AE5E059F-7E79-44bc-85B1-C7EF14DC9219}]
   * Acquire SpinLock
   * [/cover] */
  Mcal_GetSpinlock(LockAddr, GTM_SPINLOCK_TIMEOUT);

  /* [cover parentID={D66BA7C5-46C9-4cea-AAB0-A0604DC11283}]
   * Reset the desired TOM channel through Global control
   * [/cover] */
  TomTgcRegPtr->TGC_GLB_CTRL.U = (0x1UL << BitPos);

  /* Release spinlock */
  /* [cover parentID={16B69607-E141-474d-8DF9-F3C321AA4641}]
   * Release Spin Lock
   * [/cover] */
  Mcal_ReleaseSpinlock(LockAddr);

  /* Exit critical section */
  /* [cover parentID={7DC9B2DF-8845-4f68-821F-20421AB3EA74}]
   * Exit Critical section
   * [/cover] */
  SchM_Exit_Mcu_TomTgcReg();
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability     : [cover parentID={1F09294C-5079-4a20-B703-E5283DCCE041}] **
**                                                                            **
** Syntax           : void Mcu_17_Gtm_TomChannelEnable                        **
**                    (                                                       **
**                      const uint8 Module,                                   **
**                      const uint8 Channel                                   **
**                      const Mcu_17_Gtm_TimerOutputEnableType TimerOutputEn  **
**                    )                                                       **
**                                                                            **
** Description      : This interface is used by applications to enable/start  **
**                    the input TOM channel. Based on the input argument      **
**                    'TimerOutputEn', the application can decide to          **
**                    enable/disable TOM channel output. Applications which   **
**                    use the timer for counting (time base) purposes can     **
**                    disable the output. The TOM channel timer starts        **
**                    running when the channel is enabled                     **
**                                                                            **
** Service ID       : 0x68                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : Module        - TOM Module ID                           **
**                    Channel       - TOM Channel ID                          **
**                    TimerOutputEn - TOM Output enable configuration         **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void Mcu_17_Gtm_TomChannelEnable
(
  const uint8 Module,
  const uint8 Channel,
  const Mcu_17_Gtm_TimerOutputEnableType TimerOutputEn
)
{
  Mcu_17_Gtm_TomTgc * TomTgcRegPtr;
  uint32* LockAddr;
  uint32 EndisCtrlVal, OutEnCtrlVal, RegMaskVal;
  uint8 TomTgcIndex = (Channel >> GTM_TGC_DIVIDER);
  uint8 BitPos =     ((uint8)IFX_GTM_TOM_TGC_ENDIS_STAT_ENDIS_STAT0_LEN *
                       (Channel & GTM_TGC_CHANNEL_MASK));
  uint8 OutputState = GTM_BIT_SET << TimerOutputEn;


  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */

  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TomTgcRegPtr = GTM_TOM_TGC_POINTER(Module, TomTgcIndex);

  /* Get the Lock address */
  /* [cover parentID={1F1294D7-90DE-4297-9BAD-1418231C40B1}]
   * Get Lock Address
   * [/cover] */
  LockAddr = Mcu_17_lGetLockAddress(Module, TomTgcIndex, MCU_GTM_TIMER_TOM);

  /* [cover parentID={956D8543-F2F4-401c-B4F1-68590D49085B}]
   * Enter Critical Section
   * [/cover] */
  SchM_Enter_Mcu_TomTgcReg();

  /* Acquire Spinlock */
  /* [cover parentID={CF9215CB-8822-46b8-8AF1-407BD65AA665}]
   * Acquire SpinLock
   * [/cover] */
  Mcal_GetSpinlock(LockAddr, GTM_SPINLOCK_TIMEOUT);

  /* Enable the TOM channel in ENDIS_STAT register*/
  /* [cover parentID={10B600EE-6DA4-44a9-A02C-F901507AE148}]
   * Enable TOM channel in Enable/Disable Status and then in
   * Enable/Disable control [/cover]*/
  TomTgcRegPtr->TGC_ENDIS_STAT.U = (GTM_TOM_CH_ENABLE << BitPos);

  RegMaskVal = GTM_OUTEN_ENDIS_CTRL_MSK ^ (GTM_ENDIS_OUTEN_BIT_INDEX << BitPos);
  EndisCtrlVal = (GTM_TOM_CH_STAT_NO_UPDATE << BitPos);

  /* Write value 0x0 into TOM channel bit-field in ENDIS_CTRL register,
   * which prevents any update from ENDIS_CTRL to ENDIS_STAT
   * on an update trigger*/
  TomTgcRegPtr->TGC_ENDIS_CTRL.U = RegMaskVal | EndisCtrlVal;

  /* Enable or disable the TOM channel output in OUTEN_STAT register*/
  TomTgcRegPtr->TGC_OUTEN_STAT.U = ((uint32)OutputState << BitPos);

  OutEnCtrlVal = (GTM_TOM_CH_STAT_NO_UPDATE << BitPos);
  /* Write value 0x0 into TOM channel bit-field in OUTEN_CTRL register, which
   * prevents any update from OUTEN_CTRL to OUTEN_STAT on an update trigger*/
  TomTgcRegPtr->TGC_OUTEN_CTRL.U = RegMaskVal | OutEnCtrlVal;
  /*[/cover]*/
  /*[/cover]*/

   /* Release Spinlock */
  /* [cover parentID={FFD916B1-1611-42fd-B84D-2DB75DAF6A45}]
   * Release Spin Lock
   * [/cover] */
  Mcal_ReleaseSpinlock(LockAddr);

  /* Exit critical section */
  /* [cover parentID={01C5E827-6A13-4ae3-B7C2-0DCC17D28694}]
   * Exit Critical section
   * [/cover] */
  SchM_Exit_Mcu_TomTgcReg();
}

/*******************************************************************************
** Traceability     : [cover parentID={DF49F1B9-0C2F-4b7c-A663-16A78691C58C}] **
**                                                                            **
** Syntax           : void Mcu_17_Gtm_TomChannelDisable                       **
**                    (                                                       **
**                      const uint8 Module,                                   **
**                      const uint8 Channel                                   **
**                    )                                                       **
**                                                                            **
** Description      : This interface is used by applications to stop/disable  **
**                    the input TOM channel and also its channel output. The  **
**                    TOM channel timer stops running when the channel is     **
**                    disabled                                                **
**                                                                            **
** Service ID       : 0x69                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : Module  - TOM Module ID                                 **
**                    Channel - TOM Channel ID                                **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void Mcu_17_Gtm_TomChannelDisable
(
  const uint8 Module,
  const uint8 Channel
)
{
  Mcu_17_Gtm_TomTgc * TomTgcRegPtr;
  uint32* LockAddr;
  uint32 EndisCtrlVal, OutEnCtrlVal, RegMaskVal;
  uint8 TomTgcIndex = (Channel >> GTM_TGC_DIVIDER);
  uint8 BitPos =      ((uint8)IFX_GTM_TOM_TGC_ENDIS_STAT_ENDIS_STAT0_LEN *
                       (Channel & GTM_TGC_CHANNEL_MASK));


  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */

  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TomTgcRegPtr = GTM_TOM_TGC_POINTER(Module, TomTgcIndex);

  /* Get the Lock address */
  /* [cover parentID={E4C33ED3-7EE1-41ed-B956-80590BA41E85}]
   * Get Lock Address
   * [/cover] */
  LockAddr = Mcu_17_lGetLockAddress(Module, TomTgcIndex, MCU_GTM_TIMER_TOM);

  /* [cover parentID={880ED82D-BA7A-4252-8921-B3148660FE99}]
   * Enter Critical Section
   * [/cover] */
  SchM_Enter_Mcu_TomTgcReg();

  /* Acquire Spinlock */
  /* [cover parentID={0C81CE85-DDE5-4d9f-B6FA-84B142543744}]
   * Acquire SpinLock
   * [/cover] */
  Mcal_GetSpinlock(LockAddr, GTM_SPINLOCK_TIMEOUT);

  /* Disable the TOM channel in ENDIS_STAT register*/
  /* [cover parentID={73F56B33-B588-4649-8261-C72B967621D0}]
   * Disable TOM channel in Enable/Disable Status and
   * then in Enable/Disable control [/cover]*/
  TomTgcRegPtr->TGC_ENDIS_STAT.U = (GTM_TOM_CH_DISABLE << BitPos);

  /* Disable the TOM channel output in OUTEN_STAT register*/
  TomTgcRegPtr->TGC_OUTEN_STAT.U = (GTM_TOM_CH_OUT_DISABLE << BitPos);

  RegMaskVal = GTM_OUTEN_ENDIS_CTRL_MSK ^ (GTM_ENDIS_OUTEN_BIT_INDEX << BitPos);
  EndisCtrlVal = (GTM_TOM_CH_STAT_NO_UPDATE << BitPos);
  /* Write value 0x0 into TOM channel bit-field in ENDIS_CTRL register,
   *  which prevents any update from ENDIS_CTRL to ENDIS_STAT on an update
   *  trigger*/
  TomTgcRegPtr->TGC_ENDIS_CTRL.U = RegMaskVal | EndisCtrlVal;

  OutEnCtrlVal = (GTM_TOM_CH_STAT_NO_UPDATE << BitPos);
  /* Write value 0x0 into TOM channel bit-field in OUTEN_CTRL register, which
   *  prevents any update from OUTEN_CTRL to OUTEN_STAT on an update trigger*/
  TomTgcRegPtr->TGC_OUTEN_CTRL.U = RegMaskVal | OutEnCtrlVal;
  /*[/cover]*/
  /*[/cover]*/

  /* Release Spinlock */
  /* [cover parentID={FCF26CD2-86F2-4e9e-BA3C-F7D1BFEA86E9}]
   * Release Spin Lock
   * [/cover] */
  Mcal_ReleaseSpinlock(LockAddr);

  /* Exit critical section */
  /* [cover parentID={1D0846ED-F2C5-4325-9DDB-9A3C05525BFE}]
   * Exit Critical section
   * [/cover] */
  SchM_Exit_Mcu_TomTgcReg();
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability     : [cover parentID={19CE2E34-36E7-4e2c-B101-1F00BC116273}] **
**                                                                            **
** Syntax           : Mcu_17_Gtm_TimerStatusType                              **
**                                  Mcu_17_Gtm_IsTomChannelEnabled            **
**                    (                                                       **
**                      const uint8 Module,                                   **
**                      const uint8 Channel                                   **
**                    )                                                       **
**                                                                            **
** Description      : This interface is used by applications to check if the  **
**                    input TOM channel is running or not. The interface      **
**                    returns the channel running status. The channel running **
**                    status is same as its enabled status i.e. channel       **
**                    starts running when the channel is enabled              **
**                                                                            **
** Service ID       : 0x6E                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : Module  - TOM Module ID                                 **
**                    Channel - TOM Channel ID                                **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Mcu_17_Gtm_TimerStatusType -                            **
**                    MCU_GTM_TIMER_STOPPED - Channel is not running          **
**                    MCU_GTM_TIMER_RUNNING - Channel is running              **
**                                                                            **
*******************************************************************************/
Mcu_17_Gtm_TimerStatusType Mcu_17_Gtm_IsTomChannelEnabled
(
  const uint8 Module,
  const uint8 Channel
)
{
  const Mcu_17_Gtm_TomTgc * TomTgcRegPtr;
  uint8 TomChStatus;
  uint8 TomTgcIndex = (Channel >> GTM_TGC_DIVIDER);

  uint8 BitPos = (((uint8)IFX_GTM_TOM_TGC_ENDIS_STAT_ENDIS_STAT0_LEN)*
                  (Channel & GTM_TGC_CHANNEL_MASK));

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */

  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TomTgcRegPtr = GTM_TOM_TGC_POINTER(Module, TomTgcIndex);

  /* Obtain the channel enabled status from ENDIS_STAT register
   * 0x2 - Channel enabled
   * 0x1 - Channel disabled
   */
  TomChStatus = (uint8)((TomTgcRegPtr->TGC_ENDIS_STAT.U >> BitPos) &
                         GTM_TOM_EN_MSK);

  /* Right shift by 1U to fit into return format
   * 0x1 - Channel enabled/running
   * 0x0 - Channel disabled/stopped
   */
  return ((TomChStatus >> GTM_BIT_SET));
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability     : [cover parentID={5D21E0F2-7308-4d93-A4D6-22735933D58F}] **
**                                                                            **
** Syntax           : void Mcu_17_Gtm_TomTriggerRequest                       **
**                    (                                                       **
**                      const uint8 Module,                                   **
**                      const uint8 TomTgcIndex,                              **
**                      const uint16 TriggerChannels                          **
**                    )                                                       **
**                                                                            **
** Description      : This interface is used by applications to enable or     **
**                    disable multiple TOM channels                           **
**                                                                            **
** Service ID       : 0x73                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other TGC                                 **
**                                                                            **
** Parameters(in)   : Module          - TOM Module ID                         **
**                    TomTgcIndex     - TOM TGC ID                            **
**                    TriggerChannels - Mask for the channels to be triggered **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void Mcu_17_Gtm_TomTriggerRequest
(
  const uint8 Module,
  const uint8 TomTgcIndex,
  const uint16 TriggerChannels
)
{
  Mcu_17_Gtm_TomTgc * TomTgcRegPtr;
  uint32*            LockAddr;

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */

  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TomTgcRegPtr = GTM_TOM_TGC_POINTER(Module, TomTgcIndex);

  /* Get the Lock address */
  /* [cover parentID={88F02AD4-F9E4-428a-B478-266CB4FF4C3B}]
   * Get Lock Address
   * [/cover] */
  LockAddr = Mcu_17_lGetLockAddress(Module, TomTgcIndex, MCU_GTM_TIMER_TOM);

  /* [cover parentID={6B59CA64-2508-404b-A192-13ECE72795F8}]
   * Enter Critical Section
   * [/cover] */
  SchM_Enter_Mcu_TomTgcReg();

  /* Acquire Spinlock */
  /* [cover parentID={B4D52D98-E646-49e1-9369-1931FB3F6C38}]
   * Acquire SpinLock
   * [/cover] */
  Mcal_GetSpinlock(LockAddr, GTM_SPINLOCK_TIMEOUT);

  /* [cover parentID={C76861C2-8DFC-43ad-84D6-3309F5091DA5}]
   * Update the Enable/Disable control register and give a Host trigger*/
  TomTgcRegPtr->TGC_ENDIS_CTRL.U = (uint32)TriggerChannels;

  /* Initiate Host trigger to update ENDIS_STAT and OUTEN_STAT registers*/
  (TomTgcRegPtr->TGC_GLB_CTRL.U) |= GTM_TOM_HOST_TRIGGER_ENABLE;
  /*[/cover] */
  /* A delay is provided to allow the update of CM0, CM1 and CLK_SRC registers
  * on the next FXCLK. */
  NOP();
  NOP();
  NOP();

  /* Release Spinlock */
  /* [cover parentID={FD74998E-9641-43c7-AD70-831F80409E48}]
   * Release Spin Lock
   * [/cover] */
  Mcal_ReleaseSpinlock(LockAddr);


  /* Exit critical section */
  /* [cover parentID={2C073CF2-43DF-4d48-B803-29BC4D43D65C}]
   * Exit Critical section
   * [/cover] */
  SchM_Exit_Mcu_TomTgcReg();

  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability     : [cover parentID={ACC53664-B4D6-4704-9A31-A8F4EB259468}] **
**                                                                            **
** Syntax           : Std_ReturnType  Mcu_17_Gtm_TomChInitCheck               **
**                    (                                                       **
**                      const Mcu_17_Gtm_TomAtomChConfigType *const ConfigPtr **
**                    )                                                       **
**                                                                            **
** Description      : This interface verifies the TOM timer channel in        **
**                    context to the initialization contents                  **
**                                                                            **
** Service ID       : 0x74                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different channels                        **
**                                                                            **
** Parameters(in)   : ConfigPtr - Pointer to configuration data of a TOM      **
**                    channel                                                 **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value   :   E_OK      - No error has been detected                  **
**                    E_NOT_OK  - Error has been detected                     **
**                                                                            **
*******************************************************************************/
Std_ReturnType Mcu_17_Gtm_TomChInitCheck
(
  const Mcu_17_Gtm_TomAtomChConfigType *const ConfigPtr
)
{
  const Ifx_GTM_TOM_CH    * TomChannelRegPtr;
  const Mcu_17_Gtm_TomTgc * TomTgcRegPtr;
  volatile uint32 CmpFlag;
  uint32 ConfigVal;
  uint32 SfrVal;
  Std_ReturnType  RetVal;
  uint8 TomTgcIndex;
  uint8 TomChStatus;
  uint8 Module;
  uint8 Channel;
  uint8 BitPos;

  RetVal  = E_NOT_OK;
  CmpFlag = 0xFFFFFFFFU;

  /* Retrieve the TOM module index value */
  Module = (uint8)((ConfigPtr->TimerId & GTM_MODULE_NO_MASK) >>
                   GTM_MODULE_NO_OFF);

  /* Retrieve the TOM module channel number */
  Channel = (uint8)((ConfigPtr->TimerId & GTM_CHANNEL_NO_MASK) >>
                    GTM_CHANNEL_NO_OFF);

  BitPos  = ((uint8)IFX_GTM_TOM_TGC_ENDIS_STAT_ENDIS_STAT0_LEN *
             (Channel & GTM_TGC_CHANNEL_MASK));

  TomTgcIndex = (Channel / (uint8)GTM_TOM_CH_PER_TGC);

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */

  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TomChannelRegPtr = GTM_TOM_CH_POINTER((uint8)Module, Channel);

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TomTgcRegPtr = GTM_TOM_TGC_POINTER(Module, TomTgcIndex);

  /* Verify CTRL register's contents are as per configuration */
  SfrVal =  (uint32)TomChannelRegPtr->CTRL.U;
  ConfigVal = (ConfigPtr->TimerChCtrlReg);
  CmpFlag &= ~(SfrVal ^ ConfigVal);

  /* Verify CN0 register's contents if Timer is not enabled */
  TomChStatus = (uint8)((TomTgcRegPtr->TGC_ENDIS_STAT.U >> BitPos) &
                         GTM_TOM_EN_MSK);

  /* [cover parentID={C1BE73A3-0B84-4c8a-84D0-A47D0A1D5078}]
     * Is channel enabled
     * [/cover] */
  if ((TomChStatus >> GTM_BIT_SET) == 0x0U)
  {
    SfrVal = (uint32)TomChannelRegPtr->CN0.U;
    ConfigVal = (ConfigPtr->TimerChCN0Reg);
    CmpFlag &= ~(SfrVal ^ ConfigVal);
  }

  /* Verify CM0 register's contents are as per configuration */
  SfrVal = (uint32)TomChannelRegPtr->CM0.U;
  ConfigVal = (ConfigPtr->TimerChCM0Reg);
  CmpFlag &= ~(SfrVal ^ ConfigVal);

  /* Verify CM1 register's contents are as per configuration */
  SfrVal = (uint32)TomChannelRegPtr->CM1.U;
  ConfigVal = (ConfigPtr->TimerChCM1Reg);
  CmpFlag &= ~(SfrVal ^ ConfigVal);

  /* Verify SR0 register's contents are as per configuration */
  SfrVal = (uint32)TomChannelRegPtr->SR0.U;
  ConfigVal = (ConfigPtr->TimerChSR0Reg);
  CmpFlag &= ~(SfrVal ^ ConfigVal);

  /* Verify SR1 register's contents are as per configuration */
  SfrVal = (uint32)TomChannelRegPtr->SR1.U;
  ConfigVal = (ConfigPtr->TimerChSR1Reg);
  CmpFlag &= ~(SfrVal ^ ConfigVal);

  /* Verify IRQ_MODE register's contents are as per configuration */
  SfrVal = (uint32)TomChannelRegPtr->IRQ.MODE.U;
  ConfigVal = ((ConfigPtr->TimerChIntEnMode >> GTM_TOM_IRQ_MODE_POS)
               & (uint32)IFX_GTM_TOM_CH_IRQ_MODE_IRQ_MODE_MSK);
  CmpFlag &= ~(SfrVal ^ ConfigVal);

  /* Verify IRQ_EN register's contents against configuration */
  SfrVal = (uint32)TomChannelRegPtr->IRQ.EN.U;
  ConfigVal = (ConfigPtr->TimerChIntEnMode
               & (uint32)GTM_TOM_IRQ_EN_REG_MSK);
  CmpFlag &= ~(SfrVal ^ ConfigVal);

  /* [cover parentID={71C9AC99-5BB5-4ad0-A8E9-004B8AB06E10}]
   * Are all verifications successful
   * [/cover] */
  if(CmpFlag == 0xFFFFFFFFU)
  {
    RetVal = E_OK;
  }

  return RetVal;
}

/*******************************************************************************
** Traceability     : [cover parentID={B4E92C85-8D25-4c2b-91E6-0908ABBA87A3}] **
**                                                                            **
** Syntax           : void  Mcu_17_Gtm_TomChUpdateEnDis                       **
**                    (                                                       **
**                      const uint8 Module,                                   **
**                      const uint8 Channel,                                  **
**                      const Mcu_17_Gtm_TimerUpdateEnableType UpEnVal        **
**                    )                                                       **
**                                                                            **
** Description      : This interface is used by applications to enable or     **
**                    disable the update of CM0, CM1 and CLK_SRC by the       **
**                    corresponding shadow register SR0, SR1 and CLK_SRC_SR   **
**                    on reset of CN0                                         **
**                                                                            **
** Service ID       : 0x75                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : Module  - TOM Module ID                                 **
**                    Channel - TOM Channel ID                                **
**                    UpEnVal - Enable/Disable update                         **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*******************************************************************************/
void Mcu_17_Gtm_TomChUpdateEnDis
(
  const uint8 Module,
  const uint8 Channel,
  const Mcu_17_Gtm_TimerUpdateEnableType UpEnVal
)
{
  Mcu_17_Gtm_TomTgc * TomTgcRegPtr;
  uint32* LockAddr;
  uint8 TomTgcIndex = (Channel >> GTM_TGC_DIVIDER);

  uint8 BitPos =  (((uint8)IFX_GTM_TOM_TGC_GLB_CTRL_UPEN_CTRL0_LEN *
                    (Channel & GTM_TGC_CHANNEL_MASK)) +
                   IFX_GTM_TOM_TGC_GLB_CTRL_UPEN_CTRL0_OFF);

  uint32 UpenValue = ((uint32)GTM_BIT_SET << (uint32)UpEnVal);

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TomTgcRegPtr = GTM_TOM_TGC_POINTER(Module, TomTgcIndex);

  /* Get the Lock address */
  /* [cover parentID={BD90D51F-5E39-4a80-8581-71164C03A362}]
   * Get lock address
   * [/cover] */
  LockAddr = Mcu_17_lGetLockAddress(Module, TomTgcIndex, MCU_GTM_TIMER_TOM);

  /* [cover parentID={C2CF83C6-A29F-4ef8-9558-B7E0B0164D85}]
   * Enter Critical section
   * [/cover] */
  SchM_Enter_Mcu_TomTgcReg();

  /* Acquire Spinlock */
  /* [cover parentID={035E7C0B-6E96-44ad-A176-87CD8E053ECB}]
   * Acquire Spin Lock
   * [/cover] */
  Mcal_GetSpinlock(LockAddr, GTM_SPINLOCK_TIMEOUT);

  /* Enable the TOM channel in Global Control register */
  /* [cover parentID={59E849F1-5421-4118-BF10-213DD1D871BA}]
   * Enable TOM channel in Global control register
   * [/cover] */
  TomTgcRegPtr->TGC_GLB_CTRL.U = (UpenValue << BitPos);

  /* Release Spinlock */
  /* [cover parentID={73631CD7-801C-4de0-BCFE-1AB9DEB06463}]
   * Release Spin Lock
   * [/cover] */
  Mcal_ReleaseSpinlock(LockAddr);

  /* Exit critical section */
  /* [cover parentID={32B97747-74E5-4fb7-86F0-7948D3FB7085}]
   * Exit Critical section
   * [/cover] */
  SchM_Exit_Mcu_TomTgcReg();
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability     : [cover parentID={F071F1C9-2F41-427a-BD67-951FD6F87D97}] **
**                                                                            **
** Syntax           : void  Mcu_17_Gtm_TomChOutEnCtrlUpdate                   **
**                    (                                                       **
**                      const uint8 Module,                                   **
**                      const uint8 Channel,                                  **
**                      const Mcu_17_Gtm_TimerOutputEnTriggerType             **
**                                                      TimerOutputEnDis      **
**                    )                                                       **
**                                                                            **
** Description      : This interface is used by applications to enable or     **
**                    disable the output of an TOM channel on a trigger       **
**                                                                            **
** Service ID       : 0x76                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : Module           - TOM Module ID                        **
**                    Channel          - TOM Channel ID                       **
**                    TimerOutputEnDis - Enable/Disable TOM channel output    **
**                                       on a trigger                         **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*******************************************************************************/
void Mcu_17_Gtm_TomChOutEnCtrlUpdate
(
  const uint8 Module,
  const uint8 Channel,
  const Mcu_17_Gtm_TimerOutputEnTriggerType TimerOutputEnDis
)
{
  Mcu_17_Gtm_TomTgc * TomTgcRegPtr;
  uint32* LockAddr;
  uint32 OutEnCtrlVal, RegMaskVal;
  uint8 TomTgcIndex = (Channel >> GTM_TGC_DIVIDER);
  uint8 BitPos      = ((uint8)IFX_GTM_TOM_TGC_OUTEN_CTRL_OUTEN_CTRL0_LEN *
                       (Channel & GTM_TGC_CHANNEL_MASK));

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TomTgcRegPtr = GTM_TOM_TGC_POINTER(Module, TomTgcIndex);

  /* Get the Lock address */
  /* [cover parentID={CD377DB4-2E49-4a32-A78C-600F94236A8F}]
   * Get lock address
   * [/cover] */
  LockAddr = Mcu_17_lGetLockAddress(Module, TomTgcIndex, MCU_GTM_TIMER_TOM);

  /* [cover parentID={EC770BB4-4E4E-4ce6-B909-2F8762ABB558}]
   * Enter Critical section
   * [/cover] */
  SchM_Enter_Mcu_TomTgcReg();

  /* Acquire Spinlock */
  /* [cover parentID={0099B998-46AA-4679-85A5-4B924F4E7A39}]
   * Acquire Spin Lock
   * [/cover] */
  Mcal_GetSpinlock(LockAddr, GTM_SPINLOCK_TIMEOUT);

  RegMaskVal = GTM_OUTEN_ENDIS_CTRL_MSK ^ (GTM_ENDIS_OUTEN_BIT_INDEX << BitPos);
  OutEnCtrlVal = ((uint32)(TimerOutputEnDis) << BitPos);
  /* Write value 0x0 into TOM channel bit-field in OUTEN_CTRL register, which
   * prevents any update from OUTEN_CTRL to OUTEN_STAT on an update trigger*/
  /* [cover parentID={FA4F4A5E-7A69-4f7e-9795-34DE8C276FE2}]
   * Update Output Enable control register
   * [/cover] */
  TomTgcRegPtr->TGC_OUTEN_CTRL.U = RegMaskVal | OutEnCtrlVal;

  /* Release Spinlock */
  /* [cover parentID={FA574E99-4539-46d7-86FD-A704F88A1944}]
   * Release Spin Lock
   * [/cover] */
  Mcal_ReleaseSpinlock(LockAddr);

  /* Exit critical section */
  /* [cover parentID={AA3D26F5-0CFA-418b-BAD4-8B5FB24181CF}]
   * Exit Critical section
   * [/cover] */
  SchM_Exit_Mcu_TomTgcReg();
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability     : [cover parentID={27BABAF8-876A-4411-AFC5-8BF049A8F677}] **
**                                                                            **
** Syntax           : void  Mcu_17_Gtm_TomChOutEnStatUpdate                   **
**                    (                                                       **
**                      const uint8 Module,                                   **
**                      const uint8 Channel,                                  **
**                      const Mcu_17_Gtm_TimerOutputEnableType                **
**                                                      TimerOutputEnDis      **
**                    )                                                       **
**                                                                            **
** Description      : This interface is used by applications to enable or     **
**                    disable the output of an TOM channel directly           **
**                                                                            **
** Service ID       : 0x77                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : Module           - TOM Module ID                        **
**                    Channel          - TOM Channel ID                       **
**                    TimerOutputEnDis - Enable/Disable TOM channel output    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*******************************************************************************/
void Mcu_17_Gtm_TomChOutEnStatUpdate
(
  const uint8 Module,
  const uint8 Channel,
  const Mcu_17_Gtm_TimerOutputEnableType TimerOutputEnDis
)
{
  Mcu_17_Gtm_TomTgc * TomTgcRegPtr;
  uint32* LockAddr;
  uint8 TomTgcIndex = (Channel >> GTM_TGC_DIVIDER);
  uint8 BitPos      = ((uint8)IFX_GTM_TOM_TGC_OUTEN_STAT_OUTEN_STAT0_LEN *
                       (Channel & GTM_TGC_CHANNEL_MASK));

  uint8 OutputState = GTM_BIT_SET << TimerOutputEnDis;

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TomTgcRegPtr = GTM_TOM_TGC_POINTER(Module, TomTgcIndex);

  /* Get the Lock address */
  /* [cover parentID={A5EE1B77-6E22-4bda-9370-656979A7436A}]
   * Get lock address
   * [/cover] */
  LockAddr = Mcu_17_lGetLockAddress(Module, TomTgcIndex, MCU_GTM_TIMER_TOM);

  /* [cover parentID={4406A44F-CEE7-4713-828F-F0A7B4DFA8C7}]
   * Enter Critical section
   * [/cover] */
  SchM_Enter_Mcu_TomTgcReg();

  /* Acquire Spinlock */
  /* [cover parentID={F51B3828-A431-4521-B3B8-CDDD1CB05A2C}]
   * Acquire Spin Lock
   * [/cover] */
  Mcal_GetSpinlock(LockAddr, GTM_SPINLOCK_TIMEOUT);

  /* Enable or disable the TOM channel output in OUTEN_STAT register*/
  /* [cover parentID={EDBD8B4A-F002-46f9-B12B-C129A1D6D853}]
   * Update TOM channel Output enable status register
   * [/cover] */
  TomTgcRegPtr->TGC_OUTEN_STAT.U = ((uint32)OutputState << BitPos);

  /* Release Spinlock */
  /* [cover parentID={C2EB0393-6DAC-41e5-937B-615C437302FE}]
   * Release Spin Lock
   * [/cover] */
  Mcal_ReleaseSpinlock(LockAddr);

  /* Exit critical section */
  /* [cover parentID={C1CC5BEB-4C7D-480c-90C7-6C7E0A2EE129}]
   * Exit Critical section
   * [/cover] */
  SchM_Exit_Mcu_TomTgcReg();
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability     : [cover parentID={13DDABA7-5C17-4745-B047-3EE9F64EBCF8}] **
**                                                                            **
** Syntax           : void  Mcu_17_Gtm_TomChEndisCtrlUpdate                   **
**                    (                                                       **
**                      const uint8 Module,                                   **
**                      const uint8 Channel,                                  **
**                      const Mcu_17_Gtm_TimerEnTriggerType TimerEnDis        **
**                    )                                                       **
**                                                                            **
** Description      : This interface is used by applications to enable or     **
**                    disable the TOM channel on a trigger                    **
**                                                                            **
** Service ID       : 0x78                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : Module     - TOM Module ID                              **
**                    Channel    - TOM Channel ID                             **
**                    TimerEnDis - Enable/Disable the TOM channel             **
**                                 on a trigger                               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*******************************************************************************/
void Mcu_17_Gtm_TomChEndisCtrlUpdate
(
  const uint8 Module,
  const uint8 Channel,
  const Mcu_17_Gtm_TimerEnTriggerType TimerEnDis
)
{
  Mcu_17_Gtm_TomTgc * TomTgcRegPtr;
  uint32* LockAddr;
  uint32 EndisCtrlVal, RegMaskVal;
  uint8 TomTgcIndex = (Channel >> GTM_TGC_DIVIDER);
  uint8 BitPos      = ((uint8)IFX_GTM_TOM_TGC_ENDIS_STAT_ENDIS_STAT0_LEN *
                       (Channel & GTM_TGC_CHANNEL_MASK));

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TomTgcRegPtr = GTM_TOM_TGC_POINTER(Module, TomTgcIndex);

  /* Get the Lock address */
  /* [cover parentID={CA8FF239-F7A1-4693-AD3D-7B3B5087C894}]
   * Get lock address
   * [/cover] */
  LockAddr = Mcu_17_lGetLockAddress(Module, TomTgcIndex, MCU_GTM_TIMER_TOM);

  /* [cover parentID={273275DA-B14B-4726-8076-D101EC3D2E32}]
   * Enter Critical section
   * [/cover] */
  SchM_Enter_Mcu_TomTgcReg();

  /* Acquire Spinlock */
  /* [cover parentID={8D24120D-B37A-479b-9B62-C2FC2DB01437}]
   * Acquire Spin Lock
   * [/cover] */
  Mcal_GetSpinlock(LockAddr, GTM_SPINLOCK_TIMEOUT);

  RegMaskVal = GTM_OUTEN_ENDIS_CTRL_MSK ^ (GTM_ENDIS_OUTEN_BIT_INDEX << BitPos);
  EndisCtrlVal = ((uint32)(TimerEnDis) << BitPos);

  /* Write value 0x0 into TOM channel bit-field in ENDIS_CTRL register,
   * which prevents any update from ENDIS_CTRL to ENDIS_STAT
   * on an update trigger*/
  /* [cover parentID={F4F8A4DA-DAC4-41f3-8B83-8CDF3CA03FB1}]
   * Update TOM channel Enable/Disable control register
   * [/cover] */
  TomTgcRegPtr->TGC_ENDIS_CTRL.U = RegMaskVal | EndisCtrlVal;

  /* Release Spinlock */
  /* [cover parentID={3853BF67-C472-4371-8008-88664F7883CC}]
   * Release Spin Lock
   * [/cover] */
  Mcal_ReleaseSpinlock(LockAddr);

  /* Exit critical section */
  /* [cover parentID={42C7843A-C6FB-46bf-865A-C58A64B547FA}]
   * Exit Critical section
   * [/cover] */
  SchM_Exit_Mcu_TomTgcReg();
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability     : [cover parentID={5E4F8065-725D-48e0-AEB6-4C19A215587B}] **
**                                                                            **
** Syntax           : void  Mcu_17_Gtm_TomChEndisStatUpdate                   **
**                    (                                                       **
**                      const uint8 Module,                                   **
**                      const uint8 Channel,                                  **
**                      const Mcu_17_Gtm_TimerEnableType TimerEnDis           **
**                    )                                                       **
**                                                                            **
** Description      : This interface is used by applications to enable or     **
**                    disable the TOM channel directly                        **
**                                                                            **
** Service ID       : 0x79                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : Module     - TOM Module ID                              **
**                    Channel    - TOM Channel ID                             **
**                    TimerEnDis - Enable/Disable the TOM channel             **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*******************************************************************************/
void Mcu_17_Gtm_TomChEndisStatUpdate
(
  const uint8 Module,
  const uint8 Channel,
  const Mcu_17_Gtm_TimerEnableType TimerEnDis
)
{
  Mcu_17_Gtm_TomTgc * TomTgcRegPtr;
  uint32* LockAddr;
  uint8 TomTgcIndex = (Channel >> GTM_TGC_DIVIDER);
  uint8 BitPos      = ((uint8)IFX_GTM_TOM_TGC_ENDIS_STAT_ENDIS_STAT0_LEN *
                       (Channel & GTM_TGC_CHANNEL_MASK));

  uint8 EnDisVal = GTM_BIT_SET << TimerEnDis;


  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TomTgcRegPtr = GTM_TOM_TGC_POINTER(Module, TomTgcIndex);

  /* Get the Lock address */
  /* [cover parentID={6DF53FA4-C5F6-4fcf-9CFD-2CABD6C1F73A}]
   * Get lock address
   * [/cover] */
  LockAddr = Mcu_17_lGetLockAddress(Module, TomTgcIndex, MCU_GTM_TIMER_TOM);

  /* [cover parentID={AF52F80F-1F62-4414-B6CA-2FD0D98AF0A7}]
   * Enter Critical section
   * [/cover] */
  SchM_Enter_Mcu_TomTgcReg();

  /* Acquire Spinlock */
  /* [cover parentID={35C519B4-7294-4a54-80A0-ED4EC37C7A60}]
   * Acquire Spin Lock
   * [/cover] */
  Mcal_GetSpinlock(LockAddr, GTM_SPINLOCK_TIMEOUT);

  /* Enable/Disable the TOM channel in ENDIS_STAT register */
  /* [cover parentID={278E87CB-EEA5-4fa2-AC47-54A8788AC8F6}]
   * Update TOM channel Enable/Disable status register
   * [/cover] */
  TomTgcRegPtr->TGC_ENDIS_STAT.U = ((uint32)EnDisVal << BitPos);

  /* Release Spinlock */
  /* [cover parentID={8A09A5EF-708A-4730-AD57-6DA64BAA3848}]
   * Release Spin Lock
   * [/cover] */
  Mcal_ReleaseSpinlock(LockAddr);

  /* Exit critical section */
  /* [cover parentID={113F862B-EAA4-4130-9076-725B4FF622BB}]
   * Exit Critical section
   * [/cover] */
  SchM_Exit_Mcu_TomTgcReg();
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
  
}

/*******************************************************************************
** Traceability     : [cover parentID={274072CD-7F41-4ee2-87FC-C467297730CD}] **
**                                                                            **
** Syntax           : void Mcu_17_Gtm_AtomChannelInit                         **
**                    (                                                       **
**                     const Mcu_17_Gtm_TomAtomChConfigType *const ConfigPtr  **
**                    )                                                       **
**                                                                            **
** Description      : This interface configures an instance of ATOM channel.  **
**                    Consumer of a ATOM channel invokes this interface at    **
**                    the time of channel's initialization.                   **
**                                                                            **
** Service ID       : 0x64                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : ConfigPtr - Pointer to configuration data of an         **
**                    ATOM channel                                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void Mcu_17_Gtm_AtomChannelInit
(
  const Mcu_17_Gtm_TomAtomChConfigType *const ConfigPtr
)
{
  uint8 Module;
  uint8 Channel;

  /* Pointer to ATOM channel Register */
  Ifx_GTM_ATOM_CH *AtomChannelRegPtr;

  /* Retrieve the ATOM module index value */
  Module = (uint8)((ConfigPtr->TimerId & GTM_MODULE_NO_MASK)
                   >> GTM_MODULE_NO_OFF);

  /* Retrieve the ATOM module channel number */
  Channel = (uint8)((ConfigPtr->TimerId & GTM_CHANNEL_NO_MASK)
                    >> GTM_CHANNEL_NO_OFF);

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  AtomChannelRegPtr = GTM_ATOM_CH_POINTER(Module, Channel);

  /* Clear any pending interrupts associated with ATOM channel register */
  AtomChannelRegPtr->IRQ.NOTIFY.U = GTM_ATOM_CLR_PENDING_IRQ;

  /* Disable all ATOM interrupts */
  AtomChannelRegPtr->IRQ.EN.U = GTM_ATOM_REG_RESET;

  /* Configure the ATOM Channel CCU0 counter register */
  AtomChannelRegPtr->CN0.U = ConfigPtr->TimerChCN0Reg;

  /* Configure the ATOM Channel CCU0 compare register */
  AtomChannelRegPtr->CM0.U = ConfigPtr->TimerChCM0Reg;

  /* Configure the ATOM Channel CCU1 compare register */
  AtomChannelRegPtr->CM1.U = ConfigPtr->TimerChCM1Reg;

  /* Configure the ATOM Channel CCU0 compare shadow register */
  AtomChannelRegPtr->SR0.U = ConfigPtr->TimerChSR0Reg;

  /* Configure the ATOM Channel CCU1 compare shadow register */
  AtomChannelRegPtr->SR1.U = ConfigPtr->TimerChSR1Reg;

  /* Configure the ATOM Channel control register */
  AtomChannelRegPtr->CTRL.U = ConfigPtr->TimerChCtrlReg;

  /* Configure the Interrupt mode of ATOM Channel register */
  AtomChannelRegPtr->IRQ.MODE.U = ((ConfigPtr->TimerChIntEnMode >>
                                  GTM_ATOM_IRQ_MODE_POS) &
                                (uint32)IFX_GTM_ATOM_CH_IRQ_MODE_IRQ_MODE_MSK);

  /* Enable the interrupts associated with ATOM Channel register */
  AtomChannelRegPtr->IRQ.EN.U = (ConfigPtr->TimerChIntEnMode &
                                (uint32)GTM_ATOM_IRQ_EN_REG_MSK);
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability     : [cover parentID={54832F53-871A-4084-BD0D-AF7702D79ADC}] **
**                                                                            **
** Syntax           : void Mcu_17_Gtm_AtomChannelShadowTransfer               **
**                    (                                                       **
**                      const uint8 Module,                                   **
**                      const uint8 Channel                                   **
**                    )                                                       **
**                                                                            **
** Description      : This interface is used to initiate a copy of values in  **
**                    shadow registers, Compare values (duty, period) and     **
**                    Clock Source, of the specified ATOM channel to its main **
**                    timer registers.                                        **
**                                                                            **
** Service ID       : 0x65                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : Module - ATOM Module ID                                 **
**                    Channel - ATOM Channel ID                               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void Mcu_17_Gtm_AtomChannelShadowTransfer
(
  const uint8 Module,
  const uint8 Channel
)
{
  Ifx_GTM_ATOM_AGC * AtomAgcRegPtr;     /* Ptr to ATOM AGC Reg */
  uint32*           LockAddr;
  uint32 EndisCtrlBackup;
  uint32 OutenCtrlBackup;
  uint32 FupdCtrlBackup;
  uint32 FupdDisableCh;

  AtomAgcRegPtr = GTM_ATOM_AGC_POINTER(Module);

  /* Calculate the value to disable force update of CM0, CM1 and CRK_SRC
   * registers for the input ATOM channel
   */
  FupdDisableCh = ((uint32)GTM_ATOM_FORCE_UPDATE_DISABLE <<
                   ((uint32)GTM_ATOM_BITS_PER_CHAN * (uint32)Channel));

  /* Get the Lock address */
  /* [cover parentID={D34558FE-277F-49b8-B355-B33B925BC801}]
   * Get Lock address
   * [/cover] */
  LockAddr = Mcu_17_lGetLockAddress(Module, 0, MCU_GTM_TIMER_ATOM);

  /* Enter critical section */
  /* [cover parentID={FD8418FC-576D-4e3c-9D53-AE680846B5B2}]
   * Enter Critical Section for ATOM
   * [/cover] */
  SchM_Enter_Mcu_AtomAgcReg();

  /* Acquire Spinlock */
  /* [cover parentID={D9F2A566-BAA3-4fae-9A3D-56E1221927DF}]
   * Acquire Spinlock
   * [/cover] */
  Mcal_GetSpinlock(LockAddr, GTM_SPINLOCK_TIMEOUT);

  /* Backup of ENDIS_CTRL, OUTEN_CTRL and FUPD_CTRL registers */
  /* [cover parentID={823310C3-FBC7-4beb-8649-CF6FBD69CE04}]
   * Backup content of Control registers of given ATOM module
   * [/cover] */
  EndisCtrlBackup = AtomAgcRegPtr->ENDIS_CTRL.U;
  OutenCtrlBackup = AtomAgcRegPtr->OUTEN_CTRL.U;
  FupdCtrlBackup = AtomAgcRegPtr->FUPD_CTRL.U;

  /* Disable the Reset CN0 and force update of all channels */
  AtomAgcRegPtr->FUPD_CTRL.U = GTM_DISABLE_RSTCN0_FUPD;
  AtomAgcRegPtr->ENDIS_CTRL.U = GTM_ATOM_DISABLE_STAT_UPDATE;
  AtomAgcRegPtr->OUTEN_CTRL.U = GTM_ATOM_DISABLE_STAT_UPDATE;

  /* Enable force update of CM0, CM1 and CRK_SRC registers for
   * the input ATOM channel */
  AtomAgcRegPtr->FUPD_CTRL.U = ((uint32)GTM_ATOM_FORCE_UPDATE_ENABLE <<
                            ((uint32)GTM_ATOM_BITS_PER_CHAN * (uint32)Channel));

  /* Initiate Host trigger to update of CM0, CM1 and CLK_SRC registers
   * from their respective shadow registers. Also ENDIS_STAT and OUTEN_STAT
   * are also updated */
  /*[cover parentID={464D521C-46F9-4827-8145-913737B5D1F0}]
     Initiate Host trigger to update the Compare match and Clock source
   registers
     [/cover] */
  (AtomAgcRegPtr->GLB_CTRL.U) |= GTM_ATOM_HOST_TRIGGER_ENABLE;

  /* A delay is provided to allow the update of CM0, CM1 and CLK_SRC registers
   * on the next FXCLK. The delay should correspond to a minimum value of
   * 1 FXCLK clock tick, since the force update is execute synchronized to
   * FXCLK clock. This delay is realized using few NOP instruction,
   * which should provide sufficient delay,so that at least 1 FXCLK clock tick
   * to occur*/
  NOP();
  NOP();
  NOP();

  /* Disable force update of CM0, CM1 and CRK_SRC registers for
   * the input ATOM channel */
  AtomAgcRegPtr->FUPD_CTRL.U = FupdDisableCh;

  /* Restore back the contents of ENDIS_STAT and OUTEN_STAT registers */
  AtomAgcRegPtr->FUPD_CTRL.U = (uint32)(FupdCtrlBackup ^
                                        (uint32)GTM_RESTORE_RSTCN0_FUPD);
  AtomAgcRegPtr->ENDIS_CTRL.U = EndisCtrlBackup;
  AtomAgcRegPtr->OUTEN_CTRL.U = OutenCtrlBackup;

  /* Release Spinlock */
  /* [cover parentID={D80D74C4-8C39-41aa-BEA2-1B8D272B76B3}]
   * Release Spinlock
   * [/cover] */
  Mcal_ReleaseSpinlock(LockAddr);

  /* Exit critical section */
  /* [cover parentID={BB1DC52C-C54D-4e98-A775-4F0274765AC4}]
   * Exit Critical Section
   * [/cover] */
  SchM_Exit_Mcu_AtomAgcReg();
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability     : [cover parentID={A6134475-8F7A-44de-A999-8E31F8205DC4}] **
**                                                                            **
** Syntax           : void Mcu_17_Gtm_AtomChannelDeInit                       **
**                    (                                                       **
**                      const uint8 Module,                                   **
**                      const uint8 Channel                                   **
**                    )                                                       **
**                                                                            **
** Description      : This interface resets the ATOM channel registers to its **
**                    reset value.                                            **
**                                                                            **
** Service ID       : 0x66                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : Module  - ATOM Module ID                                **
**                    Channel - ATOM Channel ID                               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void Mcu_17_Gtm_AtomChannelDeInit
(
  const uint8 Module,
  const uint8 Channel
)
{
  Ifx_GTM_ATOM_CH  * AtomChannelRegPtr; /* Pointer to ATOM CH Register */
  Ifx_GTM_ATOM_AGC * AtomAgcRegPtr;     /* Pointer to ATOM AGC Register   */
  uint32* LockAddr;
  uint8 BitPos = (uint8)IFX_GTM_ATOM_AGC_GLB_CTRL_RST_CH0_OFF +
                  Channel;

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  AtomChannelRegPtr = GTM_ATOM_CH_POINTER(Module, Channel);

  AtomAgcRegPtr = GTM_ATOM_AGC_POINTER(Module);

  /* Get the Lock address */
  /* [cover parentID={84E7B67F-2AAD-4368-B24E-271DF04D4E09}]
   * Get Lock Address
   * [/cover] */
  LockAddr = Mcu_17_lGetLockAddress(Module, 0, MCU_GTM_TIMER_ATOM);

  /* Enter critical section */
  /* [cover parentID={D278D0BE-14AA-46a1-96EC-A86D8C4CB7F1}]
   * Enter Critical Section
   * [/cover] */
  SchM_Enter_Mcu_AtomAgcReg();

  /* Acquire Spinlock */
  /* [cover parentID={9CC9AFE7-0BA6-4726-8592-D3417528FF11}]
   * Acquire SpinLock
   * [/cover] */
  Mcal_GetSpinlock(LockAddr, GTM_SPINLOCK_TIMEOUT);

  /* Clear any pending interrupts associated with ATOM channel register */
  AtomChannelRegPtr->IRQ.NOTIFY.U = GTM_ATOM_CLR_PENDING_IRQ;

  /* Critical section for GLC_CTRL is taken care by using
   * an atomic instruction */
  /* [cover parentID={AACEDF9E-FD9A-453b-A896-D867AC522471}]
   * Reset the desired ATOM channel through Global control
   * [/cover] */
  AtomAgcRegPtr->GLB_CTRL.U = (GTM_ATOM_CH_SW_RESET << BitPos);

  /* Release Spinlock */
  /* [cover parentID={59683371-A0DC-4c4d-8109-C91C72B68DA8}]
   * Release Spin Lock
   * [/cover] */
  Mcal_ReleaseSpinlock(LockAddr);

  /* Exit critical section */
  /* [cover parentID={95BA8143-155C-4059-B2C2-A805E8ADBF57}]
   * Exit Critical section
   * [/cover] */
  SchM_Exit_Mcu_AtomAgcReg();
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/

}

/*******************************************************************************
** Traceability     : [cover parentID={73B26179-C095-4808-B709-48E619ABC3C9}] **
**                                                                            **
** Syntax           : void Mcu_17_Gtm_AtomChannelEnable                       **
**                    (                                                       **
**                      const uint8 Module,                                   **
**                      const uint8 Channel,                                  **
**                      const Mcu_17_Gtm_TimerOutputEnableType TimerOutputEn  **
**                    )                                                       **
**                                                                            **
** Description      : This interface is used by applications to enable/start  **
**                    the input ATOM channel. Based on the input argument     **
**                    'TimerOutputEn', the application can decide to          **
**                    enable/disable ATOM channel output. Applications which  **
**                    use the timer for counting (time base) purposes can     **
**                    disable the output. The ATOM channel timer starts       **
**                    running when the channel is enabled                     **
**                                                                            **
** Service ID       : 0x6A                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : Module        - ATOM Module ID                          **
**                    Channel       - ATOM Channel ID                         **
**                    TimerOutputEn - ATOM Output enable configuration        **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void Mcu_17_Gtm_AtomChannelEnable
(
  const uint8 Module,
  const uint8 Channel,
  const Mcu_17_Gtm_TimerOutputEnableType TimerOutputEn
)
{
  Ifx_GTM_ATOM_AGC * AtomAgcRegPtr;     /* Ptr to ATOM AGC Reg */
  uint32 * LockAddr;
  uint32 EndisCtrlVal, OutEnCtrlVal, RegMaskVal;
  uint8 OutputState = GTM_BIT_SET << TimerOutputEn;
  uint8 BitPos = (((uint8)IFX_GTM_ATOM_AGC_ENDIS_STAT_ENDIS_STAT0_LEN) *
                    Channel);

  AtomAgcRegPtr =  GTM_ATOM_AGC_POINTER(Module);

  /* Get the Lock address */
  /* [cover parentID={9DC3F8A3-CFFD-4393-8391-B53A0457B9E4}]
   * Get Lock Address
   * [/cover] */
  LockAddr = Mcu_17_lGetLockAddress(Module, 0, MCU_GTM_TIMER_ATOM);

  /* Enter critical section */
  /* [cover parentID={E8C81AEE-7AF6-4cff-861B-E7E68B027431}]
   * Enter Critical Section
   * [/cover] */
  SchM_Enter_Mcu_AtomAgcReg();

  /* Acquire Spinlock */
  /* [cover parentID={C11AF0C2-762E-431a-959C-4B08EF9D0A21}]
   * Acquire SpinLock
   * [/cover] */
  Mcal_GetSpinlock(LockAddr, GTM_SPINLOCK_TIMEOUT);

  /* Enable the ATOM channel in ENDIS_STAT register*/
  /* [cover parentID={303FBB0E-F4FF-4b26-B954-35ABA7CCD955}]
   * Enable ATOM channel in Enable/Disable Status and
   * then in Enable/Disable control*/
  AtomAgcRegPtr->ENDIS_STAT.U = (GTM_ATOM_CH_ENABLE << BitPos);

  RegMaskVal = GTM_OUTEN_ENDIS_CTRL_MSK ^ (GTM_ENDIS_OUTEN_BIT_INDEX << BitPos);
  EndisCtrlVal = (GTM_ATOM_CH_STAT_NO_UPDATE << BitPos);
  /* Write value 0x0 into ATOM channel bit-field in ENDIS_CTRL register,which
   * prevents any update from ENDIS_CTRL to ENDIS_STAT on an update trigger*/
  AtomAgcRegPtr->ENDIS_CTRL.U = RegMaskVal | EndisCtrlVal;

  /* Enable or disable the ATOM channel output in OUTEN_STAT register*/
  AtomAgcRegPtr->OUTEN_STAT.U = ((uint32)OutputState << BitPos);

  OutEnCtrlVal = (GTM_ATOM_CH_STAT_NO_UPDATE << BitPos);
  /* Write value 0x0 into ATOM channel bit-field in OUTEN_CTRL register,
   * which prevents any update from OUTEN_CTRL to OUTEN_STAT on
   * an update trigger*/
  AtomAgcRegPtr->OUTEN_CTRL.U = RegMaskVal | OutEnCtrlVal;
  /*[/cover]*/
  /*[/cover] */

  /* Release Spinlock */
  /* [cover parentID={ED18C816-451E-4477-B573-0822BA2BFF31}]
   * Release Spin Lock
   * [/cover] */
  Mcal_ReleaseSpinlock(LockAddr);

  /* Exit critical section */
  /* [cover parentID={D506F093-92C2-4ef7-8D66-2BB0EEB6FE8C}]
   * Exit Critical section
   * [/cover] */
  SchM_Exit_Mcu_AtomAgcReg();
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/

}

/*******************************************************************************
** Traceability     : [cover parentID={25987D1C-5DFF-4af1-9623-32F09212FA5A}] **
**                                                                            **
** Syntax           : void Mcu_17_Gtm_AtomChannelDisable                      **
**                    (                                                       **
**                      const uint8 Module,                                   **
**                      const uint8 Channel                                   **
**                    )                                                       **
**                                                                            **
** Description      : This interface is used by applications to stop/disable  **
**                    the input ATOM channel and also its channel output. The **
**                    ATOM channel timer stops running when the channel is    **
**                    disabled                                                **
**                                                                            **
** Service ID       : 0x71                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : Module  - ATOM Module ID                                **
**                    Channel - ATOM Channel ID                               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void Mcu_17_Gtm_AtomChannelDisable
(
  const uint8 Module,
  const uint8 Channel
)
{
  Ifx_GTM_ATOM_AGC * AtomAgcRegPtr;     /* Ptr to ATOM AGC Reg */
  uint32* LockAddr;
  uint32 EndisCtrlVal, OutEnCtrlVal, RegMaskVal;
  uint8 BitPos = ((((uint8)IFX_GTM_ATOM_AGC_ENDIS_STAT_ENDIS_STAT0_LEN) *
                    Channel));

  AtomAgcRegPtr =  GTM_ATOM_AGC_POINTER(Module);

  /* Get the Lock address */
  /* [cover parentID={BA982903-ED1F-4929-B519-F1D91D1D5735}]
   * Get Lock Address
   * [/cover] */
  LockAddr = Mcu_17_lGetLockAddress(Module, 0, MCU_GTM_TIMER_ATOM);

  /* Enter critical section */
  /* [cover parentID={53B1E684-AA07-4b3b-9556-349CB4B7D287}]
   * Enter Critical Section
   * [/cover] */
  SchM_Enter_Mcu_AtomAgcReg();

  /* Acquire Spinlock */
  /* [cover parentID={EE43F6B7-97EE-4edb-90B0-C9E934BD9460}]
   * Acquire SpinLock
   * [/cover] */
  Mcal_GetSpinlock(LockAddr, GTM_SPINLOCK_TIMEOUT);

  /* Disable the ATOM channel in ENDIS_STAT register*/
  /* [cover parentID={01C1AE5A-B128-4efd-B095-C230E43D0E20}]
   * Disable ATOM channel in Enable/Disable Status and
   * then in Enable/Disable control*/
  AtomAgcRegPtr->ENDIS_STAT.U = (GTM_ATOM_CH_DISABLE << BitPos);

  /* Disable the ATOM channel output in OUTEN_STAT register*/
  AtomAgcRegPtr->OUTEN_STAT.U = (GTM_ATOM_CH_OUT_DISABLE << BitPos);

  RegMaskVal = GTM_OUTEN_ENDIS_CTRL_MSK ^ (GTM_ENDIS_OUTEN_BIT_INDEX << BitPos);
  EndisCtrlVal = (GTM_ATOM_CH_STAT_NO_UPDATE << BitPos);

  /* Write value 0x0 into ATOM channel bit-field in ENDIS_CTRL register, which
   * prevents any update from ENDIS_CTRL to ENDIS_STAT on an update trigger*/
  AtomAgcRegPtr->ENDIS_CTRL.U = RegMaskVal | EndisCtrlVal;

  OutEnCtrlVal = (GTM_ATOM_CH_STAT_NO_UPDATE << BitPos);
  /* Write value 0x0 into ATOM channel bit-field in OUTEN_CTRL register,
   * which prevents any update from OUTEN_CTRL to OUTEN_STAT on an
   * update trigger*/
  AtomAgcRegPtr->OUTEN_CTRL.U = RegMaskVal | OutEnCtrlVal;
  /*[/cover]*/
  /* [/cover] */

  /* Release Spinlock */
  /* [cover parentID={CC3D55EF-2B67-4ddb-AC4A-6E4146B03B2A}]
   * Release Spin Lock
   * [/cover] */
  Mcal_ReleaseSpinlock(LockAddr);

  /* Exit critical section */
  /* [cover parentID={DDAFD936-3D8A-42cf-A636-1D5D7C2926F5}]
   * Exit Critical section
   * [/cover] */
  SchM_Exit_Mcu_AtomAgcReg();
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/

}

/*******************************************************************************
** Traceability    : [cover parentID={FFEA8D98-7987-490e-A6A1-65BDFC6F650A}]  **
**                                                                            **
** Syntax          : Mcu_17_Gtm_TimerStatusType                               **
**                                  Mcu_17_Gtm_IsAtomChannelEnabled           **
**                  (                                                         **
**                    const uint8 Module,                                     **
**                    const uint8 Channel                                     **
**                  )                                                         **
**                                                                            **
**                                                                            **
** Description      : This interface is used by applications to check if the  **
**                    input ATOM channel is running or not. The interface     **
**                    returns the channel running status. The channel running **
**                    status is same as its enabled status i.e. channel       **
**                    starts running when the channel is enabled              **
**                                                                            **
** Service ID       : 0x6F                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : Module  - ATOM Module ID                                **
**                    Channel - ATOM Channel ID                               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Mcu_17_Gtm_TimerStatusType -                            **
**                    MCU_GTM_TIMER_STOPPED - Channel is not running          **
**                    MCU_GTM_TIMER_RUNNING - Channel is running              **
**                                                                            **
*******************************************************************************/
Mcu_17_Gtm_TimerStatusType Mcu_17_Gtm_IsAtomChannelEnabled
(
  const uint8 Module,
  const uint8 Channel
)
{
  /* Ptr to ATOM AGC Reg */
  const Ifx_GTM_ATOM_AGC * AtomAgcRegPtr;     /* Ptr to ATOM AGC Reg */

  uint8 AtomChStatus;
  uint8 BitPos = ((((uint8)IFX_GTM_ATOM_AGC_ENDIS_STAT_ENDIS_STAT0_LEN) *
                    Channel));

  AtomAgcRegPtr =  GTM_ATOM_AGC_POINTER(Module);

  /* Obtain the channel enabled status from ENDIS_STAT register
   * 0x3 - Channel enabled
   * 0x0 - Channel disabled
   */
  AtomChStatus = (uint8)((AtomAgcRegPtr->ENDIS_STAT.U >> BitPos) &
                          GTM_ATOM_EN_MSK);

  /* Right shift by 1U to fit into return format
   * 0x1 - Channel enabled
   * 0x0 - Channel disabled
   */
  return ((AtomChStatus >> GTM_BIT_SET));
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability     : [cover parentID={67222D53-E6CF-4518-853E-C42BFF651E57}] **
**                                                                            **
** Syntax           : void Mcu_17_Gtm_AtomTriggerRequest                      **
**                    (                                                       **
**                      const uint8 Module,                                   **
**                      const uint16 TriggerChannels                          **
**                    )                                                       **
**                                                                            **
** Description      : This interface is used by applications to enable or     **
**                    disable multiple ATOM channels                          **
**                                                                            **
** Service ID       : 0x7A                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other AGC                                 **
**                                                                            **
** Parameters(in)   : Module          - ATOM Module ID                        **
**                    TriggerChannels - Mask for the channels to be triggered **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void Mcu_17_Gtm_AtomTriggerRequest
(
  const uint8 Module,
  const uint16 TriggerChannels
)
{
  Ifx_GTM_ATOM_AGC * AtomAgcRegPtr;     /* Ptr to ATOM AGC Reg */
  uint32*           LockAddr;

  AtomAgcRegPtr =  GTM_ATOM_AGC_POINTER(Module);

  /* Get the Lock address */
  /* [cover parentID={97E50CD2-B958-4022-B86D-8AA2EBEB0D57}]
   * Get Lock Address
   * [/cover] */
  LockAddr = Mcu_17_lGetLockAddress(Module, 0, MCU_GTM_TIMER_ATOM);

  /* Enter critical section */
  /* [cover parentID={94DE7676-64A4-468a-9DF5-F983B19848A5}]
   * Enter Critical Section
   * [/cover] */
  SchM_Enter_Mcu_AtomAgcReg();

  /* Acquire Spinlock */
  /* [cover parentID={1D80198F-BAEE-4a22-8D15-19180571A256}]
   * Acquire SpinLock
   * [/cover] */
  Mcal_GetSpinlock(LockAddr, GTM_SPINLOCK_TIMEOUT);

  /* [cover parentID={6D62BF2A-2F46-44e9-80B9-FD65FF68B0CD}]
   * Update the Enable/Disable control register and give a Host trigger
   * [/cover] */
  AtomAgcRegPtr->ENDIS_CTRL.U = (uint32)TriggerChannels;

  /* Initiate Host trigger to update ENDIS_STAT and OUTEN_STAT registers*/
  (AtomAgcRegPtr->GLB_CTRL.U) |= GTM_ATOM_HOST_TRIGGER_ENABLE;

  /* A delay is provided to allow the update of CM0, CM1 and CLK_SRC registers
  * on the next FXCLK. */
  NOP();
  NOP();
  NOP();

  /* Release Spinlock */
  /* [cover parentID={8D614D9A-3ADD-47c1-AFEE-26794796D038}]
   * Release Spin Lock
   * [/cover] */
  Mcal_ReleaseSpinlock(LockAddr);

  /* Exit critical section */
  /* [cover parentID={42FDF77E-47A9-40fe-8554-73D1DF91D32C}]
   * Exit Critical section
   * [/cover] */
  SchM_Exit_Mcu_AtomAgcReg();
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability     : [cover parentID={7B136BDE-0619-40ab-9590-1E79DF995AB9}] **
**                                                                            **
** Syntax           : .void  Mcu_17_Gtm_AtomChInitCheck                       **
**                    (                                                       **
**                      const Mcu_17_Gtm_TomAtomChConfigType *const ConfigPtr **
**                    )                                                       **
**                                                                            **
** Description      : This interface verifies the ATOM timer channel in       **
**                    context to the initialization contents                  **
**                                                                            **
** Service ID       : 0x7B                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different channels                        **
**                                                                            **
** Parameters(in)   : ConfigPtr - Pointer to configuration data of a ATOM     **
**                    channel                                                 **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value   :   E_OK      - No error has been detected                  **
**                    E_NOT_OK  - Error has been detected                     **
**                                                                            **
*******************************************************************************/
Std_ReturnType Mcu_17_Gtm_AtomChInitCheck
(
  const Mcu_17_Gtm_TomAtomChConfigType *const ConfigPtr
)
{
  const Ifx_GTM_ATOM_CH  * AtomChannelRegPtr; /* Pointer to ATOM CH Register */
  const Ifx_GTM_ATOM_AGC * AtomAgcRegPtr;     /* Ptr to ATOM AGC Reg         */
  volatile uint32 CmpVal;
  uint32 ConfigVal;
  uint32 SfrVal;
  Std_ReturnType RetVal;
  uint8 AtomChStatus;
  uint8 Module;
  uint8 Channel;
  uint8 BitPos;

  RetVal = E_NOT_OK;
  CmpVal = 0xFFFFFFFFU;

  /* Retrieve the ATOM module index value */
  Module = (uint8)((ConfigPtr->TimerId & GTM_MODULE_NO_MASK) \
                   >> GTM_MODULE_NO_OFF);

  /* Retrieve the ATOM module channel number */
  Channel = (uint8)((ConfigPtr->TimerId & GTM_CHANNEL_NO_MASK) \
                    >> GTM_CHANNEL_NO_OFF);

  BitPos = (((uint8)IFX_GTM_ATOM_AGC_ENDIS_STAT_ENDIS_STAT0_LEN) * Channel);

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
    * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
    * by violating this MISRA rule. */
  AtomChannelRegPtr = GTM_ATOM_CH_POINTER(Module, Channel);

  AtomAgcRegPtr =  GTM_ATOM_AGC_POINTER(Module);

  /* Verify CTRL register's contents are as per configuration */
  SfrVal = (uint32)AtomChannelRegPtr->CTRL.U;
  ConfigVal = (ConfigPtr->TimerChCtrlReg);
  CmpVal &= ~(SfrVal ^ ConfigVal);

  /* Verify CN0 register's contents if Timer is not enabled */
  AtomChStatus = (uint8)((AtomAgcRegPtr->ENDIS_STAT.U >> BitPos) &
                          GTM_ATOM_EN_MSK);

  /* Check is ATOM Channel disabled */
  /* [cover parentID={5CDF6A4A-89B9-4691-B101-6CEBC191D237}]
   * Is channel enabled
   * [/cover] */
  if ((AtomChStatus >> GTM_BIT_SET) == 0x0U)
  {
    SfrVal = (uint32)AtomChannelRegPtr->CN0.U;
    ConfigVal = (ConfigPtr->TimerChCN0Reg);
    CmpVal &= ~(SfrVal ^ ConfigVal);
  }

  /* Verify CM0 register's contents are as per configuration */
  SfrVal = (uint32)AtomChannelRegPtr->CM0.U;
  ConfigVal = (ConfigPtr->TimerChCM0Reg);
  CmpVal &= ~(SfrVal ^ ConfigVal);

  /* Verify CM1 register's contents are as per configuration */
  SfrVal = (uint32)AtomChannelRegPtr->CM1.U;
  ConfigVal = (ConfigPtr->TimerChCM1Reg);
  CmpVal &= ~(SfrVal ^ ConfigVal);

  /* Verify SR0 register's contents are as per configuration */
  SfrVal = (uint32)AtomChannelRegPtr->SR0.U;
  ConfigVal = (ConfigPtr->TimerChSR0Reg);
  CmpVal &= ~(SfrVal ^ ConfigVal);

  /* Verify SR1 register's contents are as per configuration */
  SfrVal = (uint32)AtomChannelRegPtr->SR1.U;
  ConfigVal = (ConfigPtr->TimerChSR1Reg);
  CmpVal &= ~(SfrVal ^ ConfigVal);

  /* Verify IRQ_MODE register's contents are as per configuration */
  SfrVal = (uint32)AtomChannelRegPtr->IRQ.MODE.U;
  ConfigVal = ((ConfigPtr->TimerChIntEnMode >> GTM_ATOM_IRQ_MODE_POS) \
               & (uint32)IFX_GTM_ATOM_CH_IRQ_MODE_IRQ_MODE_MSK);
  CmpVal &= ~(SfrVal ^ ConfigVal);

  /* Verify IRQ_EN register's contents against configuration */
  SfrVal = AtomChannelRegPtr->IRQ.EN.U;
  ConfigVal = (ConfigPtr->TimerChIntEnMode\
               & (uint32)GTM_ATOM_IRQ_EN_REG_MSK);
  CmpVal &= ~(SfrVal ^ ConfigVal);

  /* [cover parentID={2F013B68-336E-4a42-8B06-A71B154B1055}]
   * Are all verifications successful
   * [/cover] */
  if(CmpVal == 0xFFFFFFFFU)
  {
    RetVal = E_OK;
  }

  return RetVal;
}

/*******************************************************************************
** Traceability     : [cover parentID={23976CB4-A3D2-4730-BF1E-AD2BC5019506}] **
**                                                                            **
** Syntax           : void  Mcu_17_Gtm_AtomChUpdateEnDis                      **
**                    (                                                       **
**                      const uint8 Module,                                   **
**                      const uint8 Channel,                                  **
**                      const Mcu_17_Gtm_TimerUpdateEnableType UpEnVal        **
**                    )                                                       **
**                                                                            **
** Description      : This interface is used by applications to enable or     **
**                    disable the update of CM0, CM1 and CLK_SRC by the       **
**                    corresponding shadow register SR0, SR1 and CLK_SRC_SR   **
**                    on reset of CN0                                         **
**                                                                            **
** Service ID       : 0x7C                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : Module  - ATOM Module ID                                **
**                    Channel - ATOM Channel ID                               **
**                    UpEnVal - Enable/Disable update                         **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*******************************************************************************/
void Mcu_17_Gtm_AtomChUpdateEnDis
(
  const uint8 Module,
  const uint8 Channel,
  const Mcu_17_Gtm_TimerUpdateEnableType UpEnVal
)
{
  Ifx_GTM_ATOM_AGC * AtomAgcRegPtr;     /* Ptr to ATOM AGC Reg */
  uint32* LockAddr;
  uint8 BitPos    = ((((uint8)IFX_GTM_ATOM_AGC_GLB_CTRL_UPEN_CTRL0_LEN) * \
                      Channel) + 0x10U);
  uint8 UpenValue = GTM_BIT_SET << UpEnVal;

  AtomAgcRegPtr =  GTM_ATOM_AGC_POINTER(Module);

  /* Get the Lock address */
  /* [cover parentID={EF689D44-5269-4a56-8FBA-D188A3DD8CB8}]
   * Get lock address
   * [/cover] */
  LockAddr = Mcu_17_lGetLockAddress(Module, 0, MCU_GTM_TIMER_ATOM);

  /* Enter critical section */
  /* [cover parentID={362E211C-48DF-4912-B89B-C5C9D8FF4818}]
   * Enter Critical section
   * [/cover] */
  SchM_Enter_Mcu_AtomAgcReg();

  /* Acquire Spinlock */
  /* [cover parentID={D3B96077-51F4-48bd-A479-06974AB9BA39}]
   * Acquire Spin Lock
   * [/cover] */
  Mcal_GetSpinlock(LockAddr, GTM_SPINLOCK_TIMEOUT);

  /* Enable the TOM channel in ENDIS_STAT register */
  /* [cover parentID={E6C1E02B-07F7-458d-98B3-97DFCE8C5695}]
   * Enable ATOM channel in Global control register
   * [/cover] */
  AtomAgcRegPtr->GLB_CTRL.U = ((uint32)UpenValue << BitPos);

  /* Release Spinlock */
  /* [cover parentID={99EB7171-839E-43ef-9301-A1603028E089}]
   * Release Spin Lock
   * [/cover] */
  Mcal_ReleaseSpinlock(LockAddr);

  /* Exit critical section */
  /* [cover parentID={B40FC84D-29F4-42d3-92E0-BB167A29B152}]
   * Exit Critical section
   * [/cover] */
  SchM_Exit_Mcu_AtomAgcReg();
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability     : [cover parentID={00BBA80C-16F6-41ed-906A-561AE7FC59DF}] **
**                                                                            **
** Syntax           : void  Mcu_17_Gtm_AtomChOutEnCtrlUpdate                  **
**                    (                                                       **
**                      const uint8 Module,                                   **
**                      const uint8 Channel,                                  **
**                      const Mcu_17_Gtm_TimerOutputEnTriggerType             **
**                                                      TimerOutputEnDis      **
**                    )                                                       **
**                                                                            **
** Description      : This interface is used by applications to enable or     **
**                    disable the output of an ATOM channel on a trigger      **
**                                                                            **
** Service ID       : 0x7D                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : Module           - ATOM Module ID                       **
**                    Channel          - ATOM Channel ID                      **
**                    TimerOutputEnDis - Enable/Disable ATOM channel output   **
**                                       on a trigger                         **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*******************************************************************************/
void Mcu_17_Gtm_AtomChOutEnCtrlUpdate
(
  const uint8 Module,
  const uint8 Channel,
  const Mcu_17_Gtm_TimerOutputEnTriggerType TimerOutputEnDis
)
{
  Ifx_GTM_ATOM_AGC * AtomAgcRegPtr;     /* Ptr to ATOM AGC Reg */
  uint32* LockAddr;
  uint32 OutEnCtrlVal, RegMaskVal;
  uint8 BitPos = (((uint8)IFX_GTM_ATOM_AGC_OUTEN_CTRL_OUTEN_CTRL0_LEN) * \
                  Channel);

  AtomAgcRegPtr =  GTM_ATOM_AGC_POINTER(Module);

  /* Get the Lock address */
  /* [cover parentID={06530119-A15A-444c-A24A-243A0155269E}]
   * Get lock address
   * [/cover] */
  LockAddr = Mcu_17_lGetLockAddress(Module, 0, MCU_GTM_TIMER_ATOM);

  /* Enter critical section */
  /* [cover parentID={D7D1C718-3663-495b-AF89-46675D96B368}]
   * Enter Critical section
   * [/cover] */
  SchM_Enter_Mcu_AtomAgcReg();

  /* Acquire Spinlock */
  /* [cover parentID={D5C43B8A-C4C1-431d-ADC1-9B99D9884545}]
   * Acquire Spin Lock
   * [/cover] */
  Mcal_GetSpinlock(LockAddr, GTM_SPINLOCK_TIMEOUT);

  RegMaskVal = GTM_OUTEN_ENDIS_CTRL_MSK ^ (GTM_ENDIS_OUTEN_BIT_INDEX << BitPos);
  OutEnCtrlVal = ((uint32)(TimerOutputEnDis) << BitPos);
  /* Write value 0x0 into ATOM channel bit-field in OUTEN_CTRL register,
   * which prevents any update from OUTEN_CTRL to OUTEN_STAT on
   * an update trigger*/
  /* [cover parentID={CDE32B71-A3A4-4d81-A22C-1216C1577CFB}]
   * Update ATOM channel Output enable control register
   * [/cover] */
  AtomAgcRegPtr->OUTEN_CTRL.U = RegMaskVal | OutEnCtrlVal;

  /* Release Spinlock */
  /* [cover parentID={C460BCC6-03D8-4c3f-8274-2AA9EC56B71A}]
   * Release Spin Lock
   * [/cover] */
  Mcal_ReleaseSpinlock(LockAddr);

  /* Exit critical section */
  /* [cover parentID={B58605A0-7C13-4b0c-ABB8-B5FADCC9E2F0}]
   * Exit Critical section
   * [/cover] */
  SchM_Exit_Mcu_AtomAgcReg();
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/

}

/*******************************************************************************
** Traceability     : [cover parentID={645FB845-0087-4517-92F0-853292898BE7}] **
**                                                                            **
** Syntax           : void  Mcu_17_Gtm_AtomChOutEnStatUpdate                  **
**                    (                                                       **
**                      const uint8 Module,                                   **
**                      const uint8 Channel,                                  **
**                      const Mcu_17_Gtm_TimerOutputEnableType                **
**                                                      TimerOutputEnDis      **
**                    )                                                       **
**                                                                            **
** Description      : This interface is used by applications to enable or     **
**                    disable the output of an ATOM channel directly          **
**                                                                            **
** Service ID       : 0x7E                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : Module           - ATOM Module ID                       **
**                    Channel          - ATOM Channel ID                      **
**                    TimerOutputEnDis - Enable/Disable ATOM channel output   **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*******************************************************************************/
void Mcu_17_Gtm_AtomChOutEnStatUpdate
(
  const uint8 Module,
  const uint8 Channel,
  const Mcu_17_Gtm_TimerOutputEnableType TimerOutputEnDis
)
{
  Ifx_GTM_ATOM_AGC * AtomAgcRegPtr;     /* Ptr to ATOM AGC Reg */
  uint32* LockAddr;
  uint8 BitPos = (((uint8)IFX_GTM_ATOM_AGC_OUTEN_STAT_OUTEN_STAT0_LEN) * \
                  Channel);
  uint8 OutputState = GTM_BIT_SET << TimerOutputEnDis;

  AtomAgcRegPtr =  GTM_ATOM_AGC_POINTER(Module);

  /* Get the Lock address */
  /* [cover parentID={9324F012-FDA4-4d33-935B-1E4D4C9CBE23}]
   * Get lock address
   * [/cover] */
  LockAddr = Mcu_17_lGetLockAddress(Module, 0, MCU_GTM_TIMER_ATOM);

  /* Enter critical section */
  /* [cover parentID={2DC09C2E-87DA-43ab-B049-3DB87C74CD2E}]
   * Enter Critical section
   * [/cover] */
  SchM_Enter_Mcu_AtomAgcReg();

  /* Acquire Spinlock */
  /* [cover parentID={C7150D4E-4793-4dc0-8196-80ECA63224AC}]
   * Acquire Spin Lock
   * [/cover] */
  Mcal_GetSpinlock(LockAddr, GTM_SPINLOCK_TIMEOUT);

  /* Enable or disable the ATOM channel output in OUTEN_STAT register*/
  /* [cover parentID={84BE88FA-0D5E-4e04-8E11-D006F3DAC36B}]
   * Update ATOM channel Output enable status register
   * [/cover] */
  AtomAgcRegPtr->OUTEN_STAT.U = ((uint32)OutputState << BitPos);

  /* Release Spinlock */
  /* [cover parentID={7481BC00-3EBD-4d9f-933C-D8891F9196DE}]
   * Release Spin Lock
   * [/cover] */
  Mcal_ReleaseSpinlock(LockAddr);

  /* Exit critical section */
  /* [cover parentID={D4C85C6B-93B7-4b55-BFAE-9381D96FAB92}]
   * Exit Critical section
   * [/cover] */
  SchM_Exit_Mcu_AtomAgcReg();
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability     : [cover parentID={9CA679F0-A68B-433f-85F2-931EBB3C9DC2}] **
**                                                                            **
** Syntax           : void  Mcu_17_Gtm_AtomChEndisCtrlUpdate                  **
**                    (                                                       **
**                      const uint8 Module,                                   **
**                      const uint8 Channel,                                  **
**                      const Mcu_17_Gtm_TimerEnTriggerType TimerEnDis        **
**                    )                                                       **
**                                                                            **
** Description      : This interface is used by applications to enable or     **
**                    disable the ATOM channel on a trigger                   **
**                                                                            **
** Service ID       : 0x7F                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : Module     - ATOM Module ID                             **
**                    Channel    - ATOM Channel ID                            **
**                    TimerEnDis - Enable/Disable the ATOM channel            **
**                                 on a trigger                               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*******************************************************************************/
void Mcu_17_Gtm_AtomChEndisCtrlUpdate
(
  const uint8 Module,
  const uint8 Channel,
  const Mcu_17_Gtm_TimerEnTriggerType TimerEnDis
)
{
  Ifx_GTM_ATOM_AGC * AtomAgcRegPtr;     /* Ptr to ATOM AGC Reg */
  uint32* LockAddr;
  uint32 EndisCtrlVal, RegMaskVal;
  uint8 BitPos = (((uint8)IFX_GTM_ATOM_AGC_ENDIS_CTRL_ENDIS_CTRL0_LEN) * \
                  Channel);

  AtomAgcRegPtr =  GTM_ATOM_AGC_POINTER(Module);

  /* Get the Lock address */
  /* [cover parentID={928AA974-688C-4438-A44E-34AC3A04CC9C}]
   * Get lock address
   * [/cover] */
  LockAddr = Mcu_17_lGetLockAddress(Module, 0, MCU_GTM_TIMER_ATOM);

  /* Enter critical section */
  /* [cover parentID={C680A083-CE0C-4b06-953D-B713B9D14AD4}]
   * Enter Critical section
  [/cover] */
  /* [cover parentID={C680A083-CE0C-4b06-953D-B713B9D14AD4}]
   * Enter Critical section
   * [/cover] */
  SchM_Enter_Mcu_AtomAgcReg();

  /* Acquire Spinlock */
  /* [cover parentID={B41F3DF8-A329-43cb-BD72-73796D7F65E3}]
   * Acquire Spin Lock
   * [/cover] */
  Mcal_GetSpinlock(LockAddr, GTM_SPINLOCK_TIMEOUT);

  RegMaskVal = GTM_OUTEN_ENDIS_CTRL_MSK ^ (GTM_ENDIS_OUTEN_BIT_INDEX << BitPos);
  EndisCtrlVal = ((uint32)(TimerEnDis) << BitPos);
  /* [cover parentID={AC000277-A341-4c63-8A7E-2B8401BFD91F}]
   * Update ATOM channel Enable/Disable control register
   * [/cover] */
  AtomAgcRegPtr->ENDIS_CTRL.U = RegMaskVal | EndisCtrlVal;

  /* Release Spinlock */
  /* [cover parentID={3162B581-0C30-4b9c-85AC-7B51F80136BE}]
   * Release Spin Lock
   * [/cover] */
  Mcal_ReleaseSpinlock(LockAddr);

  /* Exit critical section */
  /* [cover parentID={BC9250C3-C8E4-4a5f-97B7-D387794BD7C5}]
   * Exit Critical section
   * [/cover] */
  SchM_Exit_Mcu_AtomAgcReg();
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability     : [cover parentID={DE6E9DBE-639B-4ba4-9119-DA9367902685}] **
**                                                                            **
** Syntax           : void  Mcu_17_Gtm_AtomChEndisStatUpdate                  **
**                    (                                                       **
**                      const uint8 Module,                                   **
**                      const uint8 Channel,                                  **
**                      const Mcu_17_Gtm_TimerEnableType TimerEnDis           **
**                    )                                                       **
**                                                                            **
** Description      : This interface is used by applications to enable or     **
**                    disable the ATOM channel directly                       **
**                                                                            **
** Service ID       : 0x80                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : Module     - ATOM Module ID                             **
**                    Channel    - ATOM Channel ID                            **
**                    TimerEnDis - Enable/Disable the ATOM channel            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*******************************************************************************/
void Mcu_17_Gtm_AtomChEndisStatUpdate
(
  const uint8 Module,
  const uint8 Channel,
  const Mcu_17_Gtm_TimerEnableType TimerEnDis
)
{
  Ifx_GTM_ATOM_AGC * AtomAgcRegPtr;     /* Ptr to ATOM AGC Reg */
  uint32* LockAddr;
  uint8 BitPos = (((uint8)IFX_GTM_ATOM_AGC_ENDIS_STAT_ENDIS_STAT0_LEN) *
                  Channel);
  uint8 EnDisVal = GTM_BIT_SET << TimerEnDis;

  AtomAgcRegPtr =  GTM_ATOM_AGC_POINTER(Module);

  /* Get the Lock address */
  /* [cover parentID={C10244E8-DA87-4ffd-B7BC-32466D420713}]
   * Get lock address
   * [/cover] */
  LockAddr = Mcu_17_lGetLockAddress(Module, 0, MCU_GTM_TIMER_ATOM);

  /* Enter critical section */
  /* [cover parentID={D03F592D-D365-410f-BAFA-298BFCA5116B}]
   * Enter Critical section
   * [/cover] */
  SchM_Enter_Mcu_AtomAgcReg();

  /* Acquire Spinlock */
  /* [cover parentID={6D842B08-4F37-4f9f-9748-7CF9E1F21629}]
   * Acquire Spin Lock
   * [/cover] */
  Mcal_GetSpinlock(LockAddr, GTM_SPINLOCK_TIMEOUT);

  /* Enable/Disable the ATOM channel in ENDIS_STAT register*/
  /* [cover parentID={058AAD85-CA98-4220-8966-60A767118B0B}]
   * Update ATOM channel Enable/Disable status register
   * [/cover] */
  AtomAgcRegPtr->ENDIS_STAT.U = ((uint32)EnDisVal << BitPos);

  /* Release Spinlock */
  /* [cover parentID={DE42E442-5276-4d4b-B4BC-89096C395C2D}]
   * Release Spin Lock
   * [/cover] */
  Mcal_ReleaseSpinlock(LockAddr);

  /* Exit critical section */
  /* [cover parentID={E854B5FF-8C4E-429f-8438-3CF1D731F461}]
   * Exit Critical section
   * [/cover] */
  SchM_Exit_Mcu_AtomAgcReg();
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability     : [cover parentID={10ED30B3-DDAC-4b18-8785-9EC413EB63DE}] **
**                                                                            **
** Syntax           : void Mcu_17_Gtm_TimChannelInit                          **
**                    (                                                       **
**                      const Mcu_17_Gtm_TimChConfigType * const ConfigPtr    **
**                    )                                                       **
**                                                                            **
** Description      : This interface configures an instance of TIM channel.   **
**                    Consumer of a TIM channel invokes this interface at the **
**                    time of channel's initialization.                       **
**                                                                            **
** Service ID       : 0x62                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : ConfigPtr - Pointer to configuration data of a          **
**                    TIM channel                                             **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void Mcu_17_Gtm_TimChannelInit
(
  const Mcu_17_Gtm_TimChConfigType * const ConfigPtr
)
{
  uint8 Module;
  uint8 Channel;

  Ifx_GTM_TIM_CH *TimChannelRegPtr;
  /* Retrieve the TIM module index value */
  Module = (uint8)((ConfigPtr->TimerId & GTM_MODULE_NO_MASK) \
                   >> GTM_MODULE_NO_OFF);

  /* Retrieve the TIM module channel number */
  Channel = (uint8)((ConfigPtr->TimerId & GTM_CHANNEL_NO_MASK) \
                    >> GTM_CHANNEL_NO_OFF);

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TimChannelRegPtr = GTM_TIM_CH_POINTER(Module, Channel);

  /* Disable the TIM channel by resetting the TIM_EN bit in TIM_CTRL 
     before configuring the channel registers*/
  Mcal_SetBitAtomic(&(TimChannelRegPtr->CTRL.U), \
                    IFX_GTM_TIM_CH_CTRL_TIM_EN_OFF, \
                    GTM_TIM_CH_CTRL_TIM_EN_LEN, \
                    GTM_TIM_CH_DISABLE);

  /* Clear any pending interrupts associated with TIM channel register */
  TimChannelRegPtr->IRQ.NOTIFY.U = GTM_TIM_CLR_PENDING_IRQ;

  /* Configure the Rising Edge filter register */
  TimChannelRegPtr->FLT_RE.U = ConfigPtr->TimChFltRisingEdge;

  /* Configure the falling Edge filter register */
  TimChannelRegPtr->FLT_FE.U = ConfigPtr->TimChFltFallingEdge;

  /* Configure the Interrupt mode of  TIM Channel register */
  TimChannelRegPtr->IRQ.MODE.U = \
      (((uint32)ConfigPtr->TimChIntEnMode >> GTM_TIM_IRQ_MODE_POS) & \
           (uint32)IFX_GTM_TIM_CH_IRQ_MODE_IRQ_MODE_MSK);

  /* Enable the interrupts associated with TIM Channel register */
  TimChannelRegPtr->IRQ.EN.U = \
      ((uint32)ConfigPtr->TimChIntEnMode & (uint32)GTM_TIM_IRQ_EN_REG_MSK);

  /* Configure the Timeout detection control(TDUV) register*/
  TimChannelRegPtr->TDUV.U = ConfigPtr->TimChTduvReg;

  /* Configure the TIM Channel extended control register */
  TimChannelRegPtr->ECTRL.U = ConfigPtr->TimChExtendedCtrlReg;

  /* Configure the TIM Channel control register */
  TimChannelRegPtr->CTRL.U = ConfigPtr->TimChCtrlReg;
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability     : [cover parentID={0BADD393-43B7-4c9d-8E1A-0B10A9EF3A63}] **
**                                                                            **
** Syntax           : void Mcu_17_Gtm_TimChannelDeInit                        **
**                    (                                                       **
**                      const uint8 Module,                                   **
**                      const uint8 Channel                                   **
**                    )                                                       **
**                                                                            **
** Description      : This interface resets the TIM channel registers to its  **
**                    reset value.                                            **
**                                                                            **
** Service ID       : 0x67                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : Module  - TIM Module ID                                 **
**                    Channel - TIM Channel ID                                **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void Mcu_17_Gtm_TimChannelDeInit
(
  const uint8 Module,
  const uint8 Channel
)
{
  Ifx_GTM_TIM_CH *TimChannelRegPtr; /* Pointer to TIM channel Register */

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TimChannelRegPtr = GTM_TIM_CH_POINTER(Module, Channel);

  /* Clear any pending interrupts associated with TIM channel register */
  TimChannelRegPtr->IRQ.NOTIFY.U = GTM_TIM_CLR_PENDING_IRQ;

  /* Reset the TIM channel */
  /* Critical section is not required for the TIM[x]_RST register since the
   * resetting for the input Channel, using an atomic operation
   */
  Mcal_SetBitAtomic(&((MODULE_GTM.TIM + Module)->RST.U),
                    Channel,
                    GTM_TIM_RST_RST_CH_LEN,
                    GTM_TIM_CH_RESET);
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability     : [cover parentID={3AC547A2-DEB0-4294-8CB9-A46BD893E7C1}] **
**                                                                            **
** Syntax           : void Mcu_17_Gtm_TimChannelEnable                        **
**                    (                                                       **
**                      const uint8 Module,                                   **
**                      const uint8 Channel                                   **
**                    )                                                       **
**                                                                            **
** Description      : This interface is used by applications to enable the    **
**                    inputTIM channel. The TIM channel timer starts running  **
**                    when the channel is enabled                             **
**                                                                            **
** Service ID       : 0x6C                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : Module  - TIM Module ID                                 **
**                    Channel - TIM Channel ID                                **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*******************************************************************************/
void Mcu_17_Gtm_TimChannelEnable
(
  const uint8 Module,
  const uint8 Channel
)
{
  Ifx_GTM_TIM_CH *TimChannelRegPtr; /* Pointer to TIM channel Register */

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TimChannelRegPtr = GTM_TIM_CH_POINTER(Module, Channel);
  /* Enable the TIM channel by setting the TIM_EN bit in TIM_CTRL */
  Mcal_SetBitAtomic(&(TimChannelRegPtr->CTRL.U), \
                    IFX_GTM_TIM_CH_CTRL_TIM_EN_OFF, \
                    GTM_TIM_CH_CTRL_TIM_EN_LEN, \
                    GTM_TIM_CH_ENABLE);
  /* MISRA2012_RULE_2_2_JUSTIFICATION: All parameters used in Mcal_SetBitAtomic
   * are used in IMASKLDMST.
   * No other dead code persist is verified by code review.
   * No side effects foreseen by violating this MISRA rule. */
  /* MISRA2012_RULE_8_13_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability     : [cover parentID={EF2AFB02-7BE4-4f61-9A56-1F99083A1DDA}] **
**                                                                            **
** Syntax           : void Mcu_17_Gtm_TimChannelDisable                       **
**                    (                                                       **
**                      const uint8 Module,                                   **
**                      const uint8 Channel                                   **
**                    )                                                       **
**                                                                            **
** Description      : This interface is used by applications to disable the   **
**                    input TIM channel. The TIM channel timer stops running  **
**                    when the channel is disabled                            **
**                                                                            **
** Service ID       : 0x6D                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : Module  - TIM Module ID                                 **
**                    Channel - TIM Channel ID                                **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void Mcu_17_Gtm_TimChannelDisable
(
  const uint8 Module,
  const uint8 Channel
)
{
  Ifx_GTM_TIM_CH *TimChannelRegPtr; /* Pointer to TIM channel Register */

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TimChannelRegPtr = GTM_TIM_CH_POINTER(Module, Channel);

  /* Disable the TIM channel by resetting the TIM_EN bit in TIM_CTRL */
  Mcal_SetBitAtomic(&(TimChannelRegPtr->CTRL.U), \
                    IFX_GTM_TIM_CH_CTRL_TIM_EN_OFF, \
                    GTM_TIM_CH_CTRL_TIM_EN_LEN, \
                    GTM_TIM_CH_DISABLE);
  /* MISRA2012_RULE_2_2_JUSTIFICATION: All parameters used in Mcal_SetBitAtomic
   * are used in IMASKLDMST.
   * No other dead code persist is verified by code review.
   * No side effects foreseen by violating this MISRA rule. */
  /* MISRA2012_RULE_8_13_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability     : [cover parentID={48B2654A-A27C-4314-87FC-F62AF96E2C1E}] **
**                                                                            **
** Syntax           : Mcu_17_Gtm_TimerStatusType                              **
**                                        Mcu_17_Gtm_IsTimChannelEnabled      **
**                    (                                                       **
**                      const uint8 Module,                                   **
**                      const uint8 Channel                                   **
**                    )                                                       **
**                                                                            **
** Description      : This interface is used by applications to check if the  **
**                    input TIM channel is running or not. The interface      **
**                    returns the channel running status. The channel running **
**                    status is same as its enabled status i.e. channel       **
**                    starts running when the channel is enabled              **
**                                                                            **
** Service ID       : 0x70                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters(in)   : Module  - TIM Module ID                                 **
**                    Channel - TIM Channel ID                                **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Mcu_17_Gtm_TimerStatusType -                            **
**                    MCU_GTM_TIMER_STOPPED - Channel is not running          **
**                    MCU_GTM_TIMER_RUNNING - Channel is running              **
**                                                                            **
*******************************************************************************/
Mcu_17_Gtm_TimerStatusType Mcu_17_Gtm_IsTimChannelEnabled
(
  const uint8 Module,
  const uint8 Channel
)
{
  /* Pointer to TIM channel Register */
  const Ifx_GTM_TIM_CH *TimChannelRegPtr;
  uint8 ChannelStatus;

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule. */
  TimChannelRegPtr = GTM_TIM_CH_POINTER(Module, Channel);

  /* Obtain the channel enabled status from TIM_CH_CTRL register
   * 0x1 - Channel enabled
   * 0x0 - Channel disabled
   */
  ChannelStatus = (uint8)Mcal_GetBitAtomic(TimChannelRegPtr->CTRL.U, \
                  IFX_GTM_TIM_CH_CTRL_TIM_EN_OFF, \
                  IFX_GTM_TIM_CH_CTRL_TIM_EN_LEN);

  return (ChannelStatus);
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability     : [cover parentID={9C795D74-E915-464a-8DD4-76BC235ADA72}] **
**                                                                            **
** Syntax           : void  Mcu_17_Gtm_ConnectPortPinToTim                    **
**                   (                                                        **
**                       const uint8 Module,                                  **
**                       const uint8 Channel,                                 **
**                       const uint8 TimerChselValue                          **
**                   )                                                        **
**                                                                            **
** Description      : This API is used to connect a port pin to an input      **
**                    GTM channel(TIM).                                       **
**                                                                            **
** Service ID       : 0x72                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other TIM modules                         **
**                                                                            **
** Parameters(in)   : Module          - TIM Module ID                         **
**                    Channel         - TIM Channel ID                        **
**                    TimerChselValue - Timer input select register CHxSEL    **
**                                      bit-field value                       **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void Mcu_17_Gtm_ConnectPortPinToTim
(
  const uint8 Module,
  const uint8 Channel,
  const uint8 TimerChselValue
)
{
  Mcal_SetBitAtomic(&(MODULE_GTM.TIMINSEL[Module].U), \
                    (IFX_GTM_TIMINSEL_CH1SEL_OFF * Channel), \
                    GTM_TIMINSEL_CHxSEL_LEN, \
                    TimerChselValue);
  /* MISRA2012_RULE_2_7_JUSTIFICATION: TimerChselValue is used in
   * Mcal_SetBitAtomic No side effects foreseen by violating this MISRA rule. */
  /* MISRA2012_RULE_2_7_JUSTIFICATION: Channel, Module is used in
   * Mcal_SetBitAtomic No side effects foreseen by violating this MISRA rule. */
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability     : [cover parentID={C53315D9-D9BC-4866-9F40-6A980782C10B}] **
**                                                                            **
** Syntax           : void  Mcu_17_Gtm_ConnectTimerOutToPortPin               **
**                    (                                                       **
**                      const uint16 Tout_IndexNumber,                        **
**                      const Mcu_17_Gtm_MappedPortTimerOutType               **
**                                                      TimerOutColumnSelect  **
**                    )                                                       **
**                                                                            **
** Description      : This API is used to connect an output GTM channel       **
**                    (TOM/ATOM) to a port pin. The selected port pin is based**
**                    on Tout_IndexNumber value and channel is based on       **
**                    TimerOutColumnSelect parameterThis API is used to       **
**                    connect a port pin to an input                          **
**                                                                            **
** Service ID       : 0xA0                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different port pins                       **
**                                                                            **
** Parameters(in)   : Tout_IndexNumber - Represents mapped column for the     **
**                                       table "GTM Output to Port Connection"**
**                                       in hardware manual                   **
**                    TimerOutColumnSelect - Timer output index number        **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void Mcu_17_Gtm_ConnectTimerOutToPortPin
(
  const uint16 Tout_IndexNumber,
  const Mcu_17_Gtm_MappedPortTimerOutType TimerOutColumnSelect
)
{
  /* Calculate the TOUTSEL register to be written */
  uint8 ToutSelRegIndex = (uint8)(Tout_IndexNumber >> TOUTSEL_LEN);
  /* Calculate the CHSEL index in TOUTSEL register */
  uint8 SelIndex = (uint8)(Tout_IndexNumber % MCAL_SELx_TOUTSEL);


  Mcal_SetBitAtomic(&(MODULE_GTM.TOUTSEL[ToutSelRegIndex].U), \
                    (IFX_GTM_TOUTSEL_SEL1_OFF * SelIndex), \
                    GTM_TOUTSEL_SELx_LEN, \
                    TimerOutColumnSelect);
  /* MISRA2012_RULE_2_2_JUSTIFICATION: All parameters used in Mcal_SetBitAtomic
   * are used in IMASKLDMST.
   * No other dead code persist is verified by code review.
   * No side effects foreseen by violating this MISRA rule. */
  /* MISRA2012_RULE_2_7_JUSTIFICATION: TimerId is used in Mcal_SetBitAtomic
   * No side effects foreseen by violating this MISRA rule. */
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability     : [cover parentID={9A14706E-BC56-4228-9BA7-780DB3A5D015}] **
**                                                                            **
** Syntax           : Std_ReturnType  Mcu_17_Gtm_TimChInitCheck               **
**                    (                                                       **
**                      const Mcu_17_Gtm_TimChConfigType *const ConfigPtr     **
**                    )                                                       **
**                                                                            **
** Description      : This interface verifies the TIM timer channel in        **
**                    context to the initialization contents                  **
**                                                                            **
** Service ID       : 0x81                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different channels                        **
**                                                                            **
** Parameters(in)   : ConfigPtr - Pointer to configuration data of a TIM      **
**                    channel                                                 **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value   :   E_OK      - No error has been detected                  **
**                    E_NOT_OK  - Error has been detected                     **
**                                                                            **
*******************************************************************************/
Std_ReturnType Mcu_17_Gtm_TimChInitCheck
(
  const Mcu_17_Gtm_TimChConfigType *const ConfigPtr
)
{
  const Ifx_GTM_TIM_CH * TimChannelRegPtr;
  uint32 SfrVal;
  uint32 ConfigVal;
  uint32 CmpVal = 0xFFFFFFFFU;
  Std_ReturnType RetVal = E_NOT_OK;
  uint8 Module;
  uint8 Channel;

  /* Retrieve the TIM module index value */
  Module = (uint8)((ConfigPtr->TimerId & GTM_MODULE_NO_MASK) \
                   >> GTM_MODULE_NO_OFF);

  /* Retrieve the TIM module channel number */
  Channel = (uint8)((ConfigPtr->TimerId & GTM_CHANNEL_NO_MASK) \
                    >> GTM_CHANNEL_NO_OFF);

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
  * by violating this MISRA rule, as the pointer to the object type
  * it is getting cast into is a known type . */
  /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
  * by violating this MISRA rule. */
  TimChannelRegPtr = GTM_TIM_CH_POINTER(Module, Channel);

  SfrVal = (uint32)TimChannelRegPtr->FLT_RE.U;
  ConfigVal = (ConfigPtr->TimChFltRisingEdge);
  CmpVal &= ~(SfrVal ^ ConfigVal);

  SfrVal = (uint32)TimChannelRegPtr->FLT_FE.U;
  ConfigVal = (ConfigPtr->TimChFltFallingEdge);
  CmpVal &= ~(SfrVal ^ ConfigVal);

  SfrVal = (uint32)TimChannelRegPtr->IRQ.MODE.U;
  ConfigVal = (((uint32)
                ConfigPtr->TimChIntEnMode >> GTM_TIM_IRQ_MODE_POS) & \
               (uint32)IFX_GTM_TIM_CH_IRQ_MODE_IRQ_MODE_MSK);
  CmpVal &= ~(SfrVal ^ ConfigVal);

  SfrVal = (uint32)TimChannelRegPtr->IRQ.EN.U;
  ConfigVal = ((uint32)ConfigPtr->TimChIntEnMode & \
               (uint32)GTM_TIM_IRQ_EN_REG_MSK);
  CmpVal &= ~(SfrVal ^ ConfigVal);

  SfrVal = (uint32)TimChannelRegPtr->TDUV.U;
  ConfigVal = (ConfigPtr->TimChTduvReg);
  CmpVal &= ~(SfrVal ^ ConfigVal);

  SfrVal = (uint32)TimChannelRegPtr->ECTRL.U;
  ConfigVal = (ConfigPtr->TimChExtendedCtrlReg) ;
  CmpVal &= ~(SfrVal ^ ConfigVal);

  SfrVal = ((uint32)TimChannelRegPtr->CTRL.U & TIM_CTRL_RST_VAL);
  ConfigVal = (ConfigPtr->TimChCtrlReg & TIM_CTRL_RST_VAL);
  CmpVal &= ~(SfrVal ^ ConfigVal);

  /* [cover parentID={C90C5885-980E-4892-853E-F01CEF473621}]
   * Are all verifications successful
   * [/cover] */
  if(CmpVal == 0xFFFFFFFFU)
  {
    RetVal = E_OK;
  }

  return RetVal;
}

#endif
/* End of #if (MCU_GTM_USED == STD_ON) */

/*******************************************************************************
** Traceability     : [cover parentID={1468EECE-9C60-4a67-9D70-EAFB1408995A}] **
**                                                                            **
** Syntax           : void  Mcu_17_Ccu6_TimerInit                             **
**                    (                                                       **
**                       const Mcu_17_Ccu6_TimerConfigType * const ConfigPtr  **
**                    )                                                       **
**                                                                            **
** Description      : This interface configures an instance of a CCU6 timer   **
**                    channel. User of the CCU6 channel invokes this interface**
**                    at the time of channel's initialization.                **
**                                                                            **
** Service ID       : 0x82                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : ConfigPtr - Ccu6 Timer channel initialization contents  **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*******************************************************************************/
void Mcu_17_Ccu6_TimerInit
(
  const Mcu_17_Ccu6_TimerConfigType * const ConfigPtr
)
{
  Mcu_17_Ccu6_KernelIdentifierType Ccu6Kernel;
  Mcu_17_Ccu6_TimerType Ccu6Timer;
  Mcu_17_Ccu6_ComparatorType Ccu6Comparator;

  Ccu6Kernel = (uint8)((ConfigPtr->TimerId) & CCU6_KERNEL_MSK);
  Ccu6Timer = (uint8)((ConfigPtr->TimerId >> CCU6_TIMER_POS) & CCU6_TIMER_MSK);
  Ccu6Comparator = (uint8)((ConfigPtr->TimerId >> CCU6_COMPARATOR_POS) & \
                           CCU6_COMPARATOR_MSK);
  /* Based on the  Kernel, Timer and Comparator type, initialize the channel */
  if(Ccu6Timer == MCU_CCU6_TIMER_T12)
  {
    /* TCTR0.T12CLK */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->TCTR0.U), \
                    IFX_CCU6_TCTR0_T12CLK_OFF, \
                    CCU6_TCTR0_T12CLK_LEN, \
                    ((ConfigPtr->TimerCtrlReg0 >> IFX_CCU6_TCTR0_T12CLK_OFF) & \
                       IFX_CCU6_TCTR0_T12CLK_MSK));

    /* TCTR0.T12PRE */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->TCTR0.U), \
                    IFX_CCU6_TCTR0_T12PRE_OFF, \
                    CCU6_TCTR0_T12PRE_LEN, \
                    ((ConfigPtr->TimerCtrlReg0 >> IFX_CCU6_TCTR0_T12PRE_OFF) & \
                       IFX_CCU6_TCTR0_T12PRE_MSK));

    /* TCTR0.CTM */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->TCTR0.U), \
                      IFX_CCU6_TCTR0_CTM_OFF, \
                      CCU6_TCTR0_CTM_LEN, \
                      ((ConfigPtr->TimerCtrlReg0 >> IFX_CCU6_TCTR0_CTM_OFF) & \
                       IFX_CCU6_TCTR0_CTM_MSK));

    /* MODCTR.T12MODEN */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->MODCTR.U), \
                      (Ccu6Comparator * CCU6_MODCTR_T12MODEN_LEN), \
                      CCU6_MODCTR_T12MODEN_LEN, \
                      (ConfigPtr->ModCtrlReg & CCU6_MODCTR_T12MODEN_MSK));

    /* PSLR.PSL */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->PSLR.U), \
                      (Ccu6Comparator * CCU6_PSLR_PSL_LEN), \
                      CCU6_PSLR_PSL_LEN, \
                      (ConfigPtr->PasStateLvlReg & CCU6_PSLR_PSL_MSK));

    /* Clear the any interrupt status flags */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->ISR.U), \
                      (Ccu6Comparator * CCU6_IEN_RCC6xRF_LEN), \
                      CCU6_IEN_RCC6xRF_LEN, \
                      CCU6_TIMER_RCC6xRF_INT_STAT_RST);

    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->ISR.U), \
                      IFX_CCU6_ISR_RT12PM_OFF, \
                      CCU6_ISR_RT12PM_LEN, \
                      CCU6_TIMER_INT_STAT_RST);

    /* IEN.ENT12PM register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U), \
                      IFX_CCU6_IEN_ENT12PM_OFF, \
                      CCU6_IEN_ENT12PM_LEN, \
                      (ConfigPtr->IntEnReg & CCU6_IEN_ENT12PM_MSK));

    /* IEN.ENCC6xR/F register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U), \
                      (Ccu6Comparator * CCU6_IEN_ENCC6xRF_LEN), \
                      CCU6_IEN_ENCC6xRF_LEN, \
                      ((ConfigPtr->IntEnReg >> CCU6_IEN_ENCC6xRF_POS) & \
                       CCU6_IEN_ENCC6xRF_MSK));

    /* IEN.ENT12OM register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U), \
                      IFX_CCU6_IEN_ENT12OM_OFF, \
                      CCU6_IEN_ENT12OM_LEN, \
                      CCU6_BIT_CLEAR);

    /* IEN.ENTRPF register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U), \
                      IFX_CCU6_IEN_ENTRPF_OFF, \
                      CCU6_IEN_ENTRPF_LEN, \
                      CCU6_BIT_CLEAR);

    /* IEN.ENCHE register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U), \
                      IFX_CCU6_IEN_ENCHE_OFF, \
                      CCU6_IEN_ENCHE_LEN, \
                      CCU6_BIT_CLEAR);

    /* IEN.ENWHE register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U), \
                      IFX_CCU6_IEN_ENWHE_OFF, \
                      CCU6_IEN_ENWHE_LEN, \
                      CCU6_BIT_CLEAR);

    /* IEN.ENIDLE register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U), \
                      IFX_CCU6_IEN_ENIDLE_OFF, \
                      CCU6_IEN_ENIDLE_LEN, \
                      CCU6_BIT_CLEAR);

    /* IEN.ENSTR register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U), \
                      IFX_CCU6_IEN_ENSTR_OFF, \
                      CCU6_IEN_ENSTR_LEN, \
                      CCU6_BIT_CLEAR);

    /* INP.INPT12 register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->INP.U), \
                      IFX_CCU6_INP_INPT12_OFF, \
                      CCU6_INP_INPT12_LEN, \
                      ((ConfigPtr->IntNodePointerReg >> CCU6_INP_INPT12_POS) & \
                       CCU6_INP_INPT12_MSK));

    /* INP.INPCC6x register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->INP.U), \
                      (Ccu6Comparator * CCU6_INP_INPCC60_LEN), \
                      CCU6_INP_INPCC60_LEN, \
                      (ConfigPtr->IntNodePointerReg & CCU6_INP_INPCC60_MSK));

    /* PISEL */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->PISEL0.U), \
                      (Ccu6Comparator * CCU6_PISEL0_ISCC60_LEN), \
                      CCU6_PISEL0_ISCC60_LEN, \
                      ConfigPtr->PortInSelReg0 & CCU6_PISEL_MSK);

    /* T12MSEL */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->T12MSEL.U), \
                      (Ccu6Comparator * CCU6_T12MSEL_MSEL60_LEN), \
                      CCU6_T12MSEL_MSEL60_LEN, \
                      ConfigPtr->TimerModeSelectReg & CCU6_T12MSEL_MSEL60_MSK);

    /* TCTR2.T12SSC */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->TCTR2.U), \
                      IFX_CCU6_TCTR2_T12SSC_OFF, \
                      CCU6_TCTR2_T12SSC_LEN, \
                      CCU6_BIT_CLEAR);

    /* TCTR2.T12RSEL */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->TCTR2.U), \
                      IFX_CCU6_TCTR2_T12RSEL_OFF, \
                      CCU6_TCTR2_T12RSEL_LEN, \
                      CCU6_BIT_CLEAR);

    /* PISEL2.ISCNT12 */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->PISEL2.U), \
                      IFX_CCU6_PISEL2_ISCNT12_OFF, \
                      CCU6_PISEL2_ISCNT12_LEN, \
                      CCU6_BIT_CLEAR);

    /* PISEL2.T12EXT */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->PISEL2.U), \
                      IFX_CCU6_PISEL2_T12EXT_OFF, \
                      CCU6_PISEL2_T12EXT_LEN, \
                      CCU6_BIT_CLEAR);

    /* CMPSTAT.CC6xPS, COUT6xPS */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->CMPSTAT.U), \
                      ((Ccu6Comparator * CCU6_CMPSTAT_PS_BITS_LEN) \
                      + IFX_CCU6_CMPSTAT_CC60PS_OFF), \
                      CCU6_CMPSTAT_PS_BITS_LEN, \
                      CCU6_BIT_CLEAR);

    /* CMPMODIF.MCC6xS */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->CMPMODIF.U), \
                      (Ccu6Comparator * CCU6_CMPMODIF_MCC60S_LEN), \
                      CCU6_CMPMODIF_MCC60S_LEN, \
                      CCU6_BIT_CLEAR);

    /* CMPMODIF.MCC6xR */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->CMPMODIF.U), \
                      ((Ccu6Comparator * CCU6_CMPMODIF_MCC60R_LEN) \
                      + IFX_CCU6_CMPMODIF_MCC60R_OFF), \
                      CCU6_CMPMODIF_MCC60R_LEN, \
                      CCU6_BIT_SET);

    /* T1xPR register */
    Mcu_17_Ccu6_Kernel[Ccu6Kernel]->T12PR.U = ConfigPtr->TimerPeriodReg & \
        CCU6_T12_MSK;
    Mcu_17_Ccu6_Kernel[Ccu6Kernel]->T12.U   = ConfigPtr->TimerCntReg & \
        CCU6_T12_MSK;
    Mcu_17_Ccu6_Kernel[Ccu6Kernel]->CC6SR[Ccu6Comparator].U = \
        ConfigPtr->Ccu6ShadowReg & CCU6_T12_MSK;
  }
  else
  {
    /* TCTR0.T13CLK */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->TCTR0.U), \
                    IFX_CCU6_TCTR0_T13CLK_OFF, \
                    CCU6_TCTR0_T13CLK_LEN, \
                    ((ConfigPtr->TimerCtrlReg0 >> IFX_CCU6_TCTR0_T13CLK_OFF) & \
                    IFX_CCU6_TCTR0_T13CLK_MSK));

    /* TCTR0.T13PRE */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->TCTR0.U), \
                    IFX_CCU6_TCTR0_T13PRE_OFF, \
                    CCU6_TCTR0_T13PRE_LEN, \
                    ((ConfigPtr->TimerCtrlReg0 >> IFX_CCU6_TCTR0_T13PRE_OFF) & \
                    IFX_CCU6_TCTR0_T13PRE_MSK));

    /* MODCTR.ECT13O */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->MODCTR.U), \
                      IFX_CCU6_MODCTR_ECT13O_OFF, \
                      CCU6_MODCTR_ECT13O_LEN, \
                      ((ConfigPtr->ModCtrlReg >> CCU6_MODCTR_ECT13O_OFF) & \
                       IFX_CCU6_MODCTR_ECT13O_MSK));

    /* PSLR.PSL63 */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->PSLR.U), \
                      IFX_CCU6_PSLR_PSL63_OFF, \
                      CCU6_PSLR_PSL63_LEN, \
                      ((ConfigPtr->PasStateLvlReg >> CCU6_PSLR_PSL63_OFF) & \
                       IFX_CCU6_PSLR_PSL63_MSK));

    /* Clear the any interrupt status flags */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->ISR.U), \
                      IFX_CCU6_ISR_RT13PM_OFF, \
                      CCU6_ISR_RT13PM_LEN, \
                      CCU6_TIMER_INT_STAT_RST);

    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->ISR.U), \
                      IFX_CCU6_ISR_RT13CM_OFF, \
                      CCU6_ISR_RT13CM_LEN, \
                      CCU6_TIMER_INT_STAT_RST);

    /* IEN.ENT13PM register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U), \
                      IFX_CCU6_IEN_ENT13PM_OFF, \
                      CCU6_IEN_ENT13PM_LEN, \
                      (ConfigPtr->IntEnReg & CCU6_IEN_ENT13PM_MSK));

    /* IEN.ENT13CM register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U), \
                      IFX_CCU6_IEN_ENT13CM_OFF, \
                      CCU6_IEN_ENT13CM_LEN, \
                      ((ConfigPtr->IntEnReg >> CCU6_IEN_ENT13CM_POS) & \
                       CCU6_IEN_ENT13CM_MSK));

    /* IEN.ENTRPF register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U), \
                      IFX_CCU6_IEN_ENTRPF_OFF, \
                      CCU6_IEN_ENTRPF_LEN, \
                      CCU6_BIT_CLEAR);

    /* IEN.ENCHE register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U), \
                      IFX_CCU6_IEN_ENCHE_OFF, \
                      CCU6_IEN_ENCHE_LEN, \
                      CCU6_BIT_CLEAR);

    /* IEN.ENWHE register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U), \
                      IFX_CCU6_IEN_ENWHE_OFF, \
                      CCU6_IEN_ENWHE_LEN, \
                      CCU6_BIT_CLEAR);

    /* IEN.ENIDLE register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U), \
                      IFX_CCU6_IEN_ENIDLE_OFF, \
                      CCU6_IEN_ENIDLE_LEN, \
                      CCU6_BIT_CLEAR);

    /* IEN.ENSTR register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U), \
                      IFX_CCU6_IEN_ENSTR_OFF, \
                      CCU6_IEN_ENSTR_LEN, \
                      CCU6_BIT_CLEAR);

    /* INP.T13 register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->INP.U), \
                      IFX_CCU6_INP_INPT13_OFF, \
                      CCU6_INP_INPT13_LEN, \
                      ((ConfigPtr->IntNodePointerReg >> CCU6_INP_INPT13_POS) & \
                       CCU6_INP_INPT13_MSK));

    /* PISEL2.ISCNT13 */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->PISEL2.U), \
                      IFX_CCU6_PISEL2_ISCNT13_OFF, \
                      CCU6_PISEL2_ISCNT13_LEN, \
                      CCU6_BIT_CLEAR);

    /* PISEL2.T13EXT */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->PISEL2.U), \
                      IFX_CCU6_PISEL2_T13EXT_OFF, \
                      CCU6_PISEL2_T13EXT_LEN, \
                      CCU6_BIT_CLEAR);

    /* PISEL2.IST13HR */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->PISEL2.U), \
                      IFX_CCU6_PISEL2_IST13HR_OFF, \
                      CCU6_PISEL2_IST13HR_LEN, \
                      CCU6_BIT_CLEAR);

    /* CMPSTAT.COUT63PS */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->CMPSTAT.U), \
                      IFX_CCU6_CMPSTAT_COUT63PS_OFF, \
                      CCU6_CMPSTAT_COUT63PS_LEN, \
                      CCU6_BIT_CLEAR);

    /* CMPSTAT.T13IM */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->CMPSTAT.U), \
                      IFX_CCU6_CMPSTAT_T13IM_OFF, \
                      CCU6_CMPSTAT_T13IM_LEN, \
                      CCU6_BIT_CLEAR);

    /* CMPMODIF.MCC63S */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->CMPMODIF.U), \
                      IFX_CCU6_CMPMODIF_MCC63S_OFF, \
                      CCU6_CMPMODIF_MCC63S_LEN, \
                      CCU6_BIT_CLEAR);

    /* CMPMODIF.MCC63R */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->CMPMODIF.U), \
                      IFX_CCU6_CMPMODIF_MCC63R_OFF, \
                      CCU6_CMPMODIF_MCC63R_LEN, \
                      CCU6_BIT_SET);

    /* T1xPR register */
    Mcu_17_Ccu6_Kernel[Ccu6Kernel]->T13PR.U = ConfigPtr->TimerPeriodReg;
    Mcu_17_Ccu6_Kernel[Ccu6Kernel]->T13.U = ConfigPtr->TimerCntReg;
    Mcu_17_Ccu6_Kernel[Ccu6Kernel]->CC63SR.U = ConfigPtr->Ccu6ShadowReg;
  }
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
   Registers[/cover]*/
}

/*******************************************************************************
** Traceability     : [cover parentID={D7E7A7EE-D8A0-4489-BD71-DCE1FF87E48F}] **
**                                                                            **
** Syntax           : void  Mcu_17_Ccu6_TimerDeInit                           **
**                      (                                                     **
**                          const Mcu_17_Ccu6_TimerChIdentifierType TimerId   **
**                      )                                                     **
**                                                                            **
** Description      : This function de-initializes the CCU6 timer channel to  **
**                    default values                                          **
**                                                                            **
** Service ID       : 0x83                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : TimerId - CCU6 timer to be de-initialized               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*******************************************************************************/
void Mcu_17_Ccu6_TimerDeInit
(
  const Mcu_17_Ccu6_TimerChIdentifierType TimerId
)
{
  Mcu_17_Ccu6_KernelIdentifierType Ccu6Kernel;
  Mcu_17_Ccu6_TimerType Ccu6Timer;
  Mcu_17_Ccu6_ComparatorType Ccu6Comparator;

  Ccu6Kernel = (uint8)(TimerId & CCU6_KERNEL_MSK) ;
  Ccu6Timer = (uint8)((TimerId >> CCU6_TIMER_POS) & CCU6_TIMER_MSK) ;
  Ccu6Comparator = (uint8)((TimerId >> CCU6_COMPARATOR_POS) & \
                           CCU6_COMPARATOR_MSK) ;

  if(Ccu6Timer == MCU_CCU6_TIMER_T12)
  {
    /* TCTR0 */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->TCTR0.U), \
                      IFX_CCU6_TCTR0_T12CLK_OFF, \
                      CCU6_TCTR0_T12_DEINIT_LEN, \
                      CCU6_TCTR0_T12_DEINIT_VAL);


    /* MODCTR */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->MODCTR.U), \
                      (Ccu6Comparator * CCU6_MODCTR_T12MODEN_LEN), \
                      CCU6_MODCTR_T12MODEN_LEN, \
                      CCU6_MODCTR_T12_DEINIT_VAL);

    /* PSLR */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->PSLR.U), \
                      (Ccu6Comparator * CCU6_PSLR_PSL_LEN), \
                      CCU6_PSLR_PSL_LEN, \
                      CCU6_PSLR_T12_DEINIT_VAL);

    /* IEN.ENT12PM register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U), \
                      IFX_CCU6_IEN_ENT12PM_OFF, \
                      CCU6_IEN_ENT12PM_LEN, \
                      CCU6_IEN_T12_DEINIT_VAL);

    /* IEN.ENCC6xR/F register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U), \
                      (Ccu6Comparator * CCU6_IEN_ENCC6xRF_LEN), \
                      CCU6_IEN_ENCC6xRF_LEN, \
                      CCU6_IEN_CC6_DEINIT_VAL);

    /* IEN.ENT12OM register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U), \
                      IFX_CCU6_IEN_ENT12OM_OFF, \
                      CCU6_IEN_ENT12OM_LEN, \
                      CCU6_IEN_CC6_DEINIT_VAL);

    /* IEN.ENTRPF register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U), \
                      IFX_CCU6_IEN_ENTRPF_OFF, \
                      CCU6_IEN_ENTRPF_LEN, \
                      CCU6_IEN_CC6_DEINIT_VAL);

    /* IEN.ENCHE register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U), \
                      IFX_CCU6_IEN_ENCHE_OFF, \
                      CCU6_IEN_ENCHE_LEN, \
                      CCU6_IEN_CC6_DEINIT_VAL);

    /* IEN.ENWHE register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U), \
                      IFX_CCU6_IEN_ENWHE_OFF, \
                      CCU6_IEN_ENWHE_LEN, \
                      CCU6_IEN_CC6_DEINIT_VAL);

    /* IEN.ENIDLE register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U), \
                      IFX_CCU6_IEN_ENIDLE_OFF, \
                      CCU6_IEN_ENIDLE_LEN, \
                      CCU6_IEN_CC6_DEINIT_VAL);

    /* IEN.ENSTR register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U), \
                      IFX_CCU6_IEN_ENSTR_OFF, \
                      CCU6_IEN_ENSTR_LEN, \
                      CCU6_IEN_CC6_DEINIT_VAL);

    /* INP.INPT12 register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->INP.U), \
                      IFX_CCU6_INP_INPT12_OFF, \
                      CCU6_INP_INPT12_LEN, \
                      CCU6_INP_T12_DEINIT_VAL);

    /* INP.INPCC6x register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->INP.U), \
                      (Ccu6Comparator * CCU6_INP_INPCC60_LEN), \
                      CCU6_INP_INPCC60_LEN, \
                      CCU6_INP_CC6x_DEINIT_VAL);

    /* PISEL */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->PISEL0.U), \
                      (Ccu6Comparator * CCU6_PISEL0_ISCC60_LEN), \
                      CCU6_PISEL0_ISCC60_LEN, \
                      CCU6_PISEL0_CC6x_DEINIT_VAL);


    /* T12MSEL */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->T12MSEL.U), \
                      (Ccu6Comparator * CCU6_T12MSEL_MSEL60_LEN), \
                      CCU6_T12MSEL_MSEL60_LEN, \
                      CCU6_T12MSEL_MSEL6x_DEINIT_VAL);

    /* TCTR2.T12SSC */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->TCTR2.U), \
                      IFX_CCU6_TCTR2_T12SSC_OFF, \
                      CCU6_TCTR2_T12SSC_LEN, \
                      CCU6_TCTR2_T12_DEINIT_VAL);

    /* TCTR2.T12RSEL */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->TCTR2.U), \
                      IFX_CCU6_TCTR2_T12RSEL_OFF, \
                      CCU6_TCTR2_T12RSEL_LEN, \
                      CCU6_TCTR2_T12_DEINIT_VAL);

    /* PISEL2.ISCNT12 */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->PISEL2.U), \
                      IFX_CCU6_PISEL2_ISCNT12_OFF, \
                      CCU6_PISEL2_ISCNT12_LEN, \
                      CCU6_PISEL2_ISCNTx_DEINIT_VAL);

    /* PISEL2.T12EXT */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->PISEL2.U), \
                      IFX_CCU6_PISEL2_T12EXT_OFF, \
                      CCU6_PISEL2_T12EXT_LEN, \
                      CCU6_PISEL2_TxEXT_DEINIT_VAL);

    /* CMPSTAT.CC6xPS, COUT6xPS */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->CMPSTAT.U), \
                      ((Ccu6Comparator * CCU6_CMPSTAT_PS_BITS_LEN) \
                      + IFX_CCU6_CMPSTAT_CC60PS_OFF), \
                      CCU6_CMPSTAT_PS_BITS_LEN, \
                      CCU6_CMPSTAT_PS_BITS_DEINIT_VAL);

    /* CMPMODIF.MCC6xS */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->CMPMODIF.U), \
                      (Ccu6Comparator * CCU6_CMPMODIF_MCC60S_LEN), \
                      CCU6_CMPMODIF_MCC60S_LEN, \
                      CCU6_CMPMODIF_MCC6xS_DEINIT_VAL);

    /* CMPMODIF.MCC6xR */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->CMPMODIF.U), \
                      ((Ccu6Comparator * CCU6_CMPMODIF_MCC60R_LEN) \
                      + IFX_CCU6_CMPMODIF_MCC60R_OFF), \
                      CCU6_CMPMODIF_MCC60R_LEN, \
                      CCU6_CMPMODIF_MCC6xR_DEINIT_VAL);

    /* T1xPR register */
    Mcu_17_Ccu6_Kernel[Ccu6Kernel]->T12PR.U = CCU6_T12PR_CC6_DEINIT_VAL;
    Mcu_17_Ccu6_Kernel[Ccu6Kernel]->T12.U = CCU6_T12_CC6_DEINIT_VAL;
    Mcu_17_Ccu6_Kernel[Ccu6Kernel]->CC6SR[Ccu6Comparator].U = \
        CCU6_CC6xSR_DEINIT_VAL;

  }
  else
  {
    /* TCTR0 */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->TCTR0.U), \
                      IFX_CCU6_TCTR0_T13CLK_OFF, \
                      CCU6_TCTR0_T13_DEINIT_LEN, \
                      CCU6_TCTR0_T13_DEINIT_VAL);

    /* MODCTR */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->MODCTR.U), \
                      IFX_CCU6_MODCTR_ECT13O_OFF, \
                      CCU6_MODCTR_ECT13O_LEN, \
                      CCU6_MODCTR_T13_DEINIT_VAL);


    /* PSLR */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->PSLR.U), \
                      IFX_CCU6_PSLR_PSL63_OFF, \
                      CCU6_PSLR_PSL63_LEN, \
                      CCU6_PSLR_T13_DEINIT_VAL);

    /* IEN.ENT13PM register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U), \
                      IFX_CCU6_IEN_ENT13PM_OFF, \
                      CCU6_IEN_ENT13PM_LEN, \
                      CCU6_IEN_T13_DEINIT_VAL);

    /* IEN.ENT13CM register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U), \
                      IFX_CCU6_IEN_ENT13CM_OFF, \
                      CCU6_IEN_ENT13CM_LEN, \
                      CCU6_IEN_T13_DEINIT_VAL);

    /* IEN.ENTRPF register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U), \
                      IFX_CCU6_IEN_ENTRPF_OFF, \
                      CCU6_IEN_ENTRPF_LEN, \
                      CCU6_IEN_CC6_DEINIT_VAL);

    /* IEN.ENCHE register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U), \
                      IFX_CCU6_IEN_ENCHE_OFF, \
                      CCU6_IEN_ENCHE_LEN, \
                      CCU6_IEN_CC6_DEINIT_VAL);

    /* IEN.ENWHE register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U), \
                      IFX_CCU6_IEN_ENWHE_OFF, \
                      CCU6_IEN_ENWHE_LEN, \
                      CCU6_IEN_CC6_DEINIT_VAL);

    /* IEN.ENIDLE register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U), \
                      IFX_CCU6_IEN_ENIDLE_OFF, \
                      CCU6_IEN_ENIDLE_LEN, \
                      CCU6_IEN_CC6_DEINIT_VAL);

    /* IEN.ENSTR register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U), \
                      IFX_CCU6_IEN_ENSTR_OFF, \
                      CCU6_IEN_ENSTR_LEN, \
                      CCU6_IEN_CC6_DEINIT_VAL);

    /* INP.T13 register*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->INP.U), \
                      IFX_CCU6_INP_INPT13_OFF, \
                      CCU6_INP_INPT13_LEN, \
                      CCU6_INP_T13_DEINIT_VAL);

    /* PISEL2.ISCNT13 */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->PISEL2.U), \
                      IFX_CCU6_PISEL2_ISCNT13_OFF, \
                      CCU6_PISEL2_ISCNT13_LEN, \
                      CCU6_PISEL2_ISCNTx_DEINIT_VAL);

    /* PISEL2.T13EXT */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->PISEL2.U), \
                      IFX_CCU6_PISEL2_T13EXT_OFF, \
                      CCU6_PISEL2_T13EXT_LEN, \
                      CCU6_PISEL2_TxEXT_DEINIT_VAL);

    /* PISEL2.IST13HR */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->PISEL2.U), \
                      IFX_CCU6_PISEL2_IST13HR_OFF, \
                      CCU6_PISEL2_IST13HR_LEN, \
                      CCU6_PISEL2_IST13HR_DEINIT_VAL);

    /* CMPSTAT.COUT63PS */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->CMPSTAT.U), \
                      IFX_CCU6_CMPSTAT_COUT63PS_OFF, \
                      CCU6_CMPSTAT_COUT63PS_LEN, \
                      CCU6_CMPSTAT_COUT6xPS_DEINIT_VAL);

    /* CMPSTAT.T13IM */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->CMPSTAT.U), \
                      IFX_CCU6_CMPSTAT_T13IM_OFF, \
                      CCU6_CMPSTAT_T13IM_LEN, \
                      CCU6_CMPSTAT_T13IM_DEINIT_VAL);

    /* CMPMODIF.MCC63S */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->CMPMODIF.U), \
                      IFX_CCU6_CMPMODIF_MCC63S_OFF, \
                      CCU6_CMPMODIF_MCC63S_LEN, \
                      CCU6_CMPMODIF_MCC6xS_DEINIT_VAL);

    /* CMPMODIF.MCC63R */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->CMPMODIF.U), \
                      IFX_CCU6_CMPMODIF_MCC63R_OFF, \
                      CCU6_CMPMODIF_MCC63R_LEN, \
                      CCU6_CMPMODIF_MCC6xR_DEINIT_VAL);

    /* T1xPR register */
    Mcu_17_Ccu6_Kernel[Ccu6Kernel]->T13PR.U = CCU6_T13PR_CC6_DEINIT_VAL;
    Mcu_17_Ccu6_Kernel[Ccu6Kernel]->T13.U = CCU6_T13_CC6_DEINIT_VAL;
    Mcu_17_Ccu6_Kernel[Ccu6Kernel]->CC63SR.U = CCU6_CC6xSR_DEINIT_VAL;
  }

  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability     : [cover parentID={BF65C68B-CC23-4548-97E8-20EAC029B042}] **
**                                                                            **
** Syntax           : void  Mcu_17_Ccu6_TimerStart                            **
**                    (                                                       **
**                        const Mcu_17_Ccu6_TimerChIdentifierType TimerId     **
**                    )                                                       **
**                                                                            **
** Description      : This function starts the specified CCU6 timer.          **
**                                                                            **
** Service ID       : 0x84                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : TimerId - CCU6 timer to be enabled                      **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*******************************************************************************/
void Mcu_17_Ccu6_TimerStart
(
  const Mcu_17_Ccu6_TimerChIdentifierType TimerId
)
{
  Mcu_17_Ccu6_KernelIdentifierType Ccu6Kernel;
  Mcu_17_Ccu6_TimerType Ccu6Timer;
  Mcu_17_Ccu6_ComparatorType Ccu6Comparator;

  Ccu6Kernel = (uint8)(TimerId & CCU6_KERNEL_MSK) ;
  Ccu6Timer = (uint8)((TimerId >> CCU6_TIMER_POS) & CCU6_TIMER_MSK) ;
  Ccu6Comparator = (uint8)((TimerId >> CCU6_COMPARATOR_POS) & \
                           CCU6_COMPARATOR_MSK) ;

  /* Based on the timer type, start the timer counter */
  if(Ccu6Timer == MCU_CCU6_TIMER_T12)
  {
    /* Clear the any interrupt status flags */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->ISR.U), \
                      (Ccu6Comparator * CCU6_IEN_RCC6xRF_LEN), \
                      CCU6_IEN_RCC6xRF_LEN, \
                      CCU6_TIMER_RCC6xRF_INT_STAT_RST);

    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->ISR.U), \
                      IFX_CCU6_ISR_RT12PM_OFF, \
                      CCU6_ISR_RT12PM_LEN, \
                      CCU6_TIMER_INT_STAT_RST);

    /* Start the timer counter for T12*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->TCTR4.U), \
                      IFX_CCU6_TCTR4_T12RS_OFF, \
                      CCU6_TCTR4_T12RS_LEN, \
                      CCU6_T12_START);
  }
  else
  {
    /* Clear the any interrupt status flags */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->ISR.U), \
                      IFX_CCU6_ISR_RT13PM_OFF, \
                      CCU6_ISR_RT13PM_LEN, \
                      CCU6_TIMER_INT_STAT_RST);

    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->ISR.U), \
                      IFX_CCU6_ISR_RT13CM_OFF, \
                      CCU6_ISR_RT13CM_LEN, \
                      CCU6_TIMER_INT_STAT_RST);

    /* Start the timer counter for T13*/
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->TCTR4.U), \
                      IFX_CCU6_TCTR4_T13RS_OFF, \
                      CCU6_TCTR4_T13RS_LEN, \
                      CCU6_T13_START);
  }
  /*[/cover]*/
  /* MISRA2012_RULE_2_2_JUSTIFICATION: All parameters used in Mcal_SetBitAtomic
   * are used in IMASKLDMST.
   * No other dead code persist is verified by code review.
   * No side effects foreseen by violating this MISRA rule. */
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability     : [cover parentID={4FF5C9DB-8074-47f1-9701-184F5ED4F2E9}] **
**                                                                            **
** Syntax           : void  Mcu_17_Ccu6_TimerStop                             **
**                    (                                                       **
**                        const Mcu_17_Ccu6_TimerChIdentifierType TimerId     **
**                    )                                                       **
**                                                                            **
** Description      : This function starts the specified CCU6 timer.          **
**                                                                            **
** Service ID       : 0x85                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : TimerId - CCU6 timer to be disabled                     **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*******************************************************************************/
void Mcu_17_Ccu6_TimerStop
(
  const Mcu_17_Ccu6_TimerChIdentifierType TimerId
)
{
  Mcu_17_Ccu6_KernelIdentifierType Ccu6Kernel;
  Mcu_17_Ccu6_TimerType Ccu6Timer;

  Ccu6Kernel = (uint8)(TimerId & CCU6_KERNEL_MSK) ;
  Ccu6Timer = (uint8)((TimerId >> CCU6_TIMER_POS) & CCU6_TIMER_MSK) ;

  /* Based on the timer type, stop the timer counter */
  if(Ccu6Timer == MCU_CCU6_TIMER_T12)
  {
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->TCTR4.U), \
                      IFX_CCU6_TCTR4_T12RR_OFF, \
                      CCU6_TCTR4_T12RR_LEN, \
                      CCU6_T12_STOP);
  }
  else
  {
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->TCTR4.U), \
                      IFX_CCU6_TCTR4_T13RR_OFF, \
                      CCU6_TCTR4_T13RR_LEN, \
                      CCU6_T13_STOP);
  }
  /* MISRA2012_RULE_2_2_JUSTIFICATION: All parameters used in Mcal_SetBitAtomic
   * are used in IMASKLDMST.
   * No other dead code persist is verified by code review.
   * No side effects foreseen by violating this MISRA rule. */
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability     : [cover parentID={1301CF4C-A07A-49ab-92DD-2E6B3975C6B3}] **
**                                                                            **
** Syntax           : void  Mcu_17_Ccu6_TimerShadowTransfer                   **
**                    (                                                       **
**                        const Mcu_17_Ccu6_TimerChIdentifierType TimerId     **
**                    )                                                       **
**                                                                            **
** Description      : This function enables the shadow transfer for the       **
**                    specified CCU6 timer channel, that is to copy contents  **
**                    from shadow register to main register.                  **
**                                                                            **
** Service ID       : 0x86                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other CCU6 timers                         **
**                                                                            **
** Parameters(in)   : TimerId - CCU6 timer channel                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*******************************************************************************/
void Mcu_17_Ccu6_TimerShadowTransfer
(
  const Mcu_17_Ccu6_TimerChIdentifierType TimerId
)
{
  Mcu_17_Ccu6_KernelIdentifierType Ccu6Kernel;
  Mcu_17_Ccu6_TimerType Ccu6Timer;

  Ccu6Kernel = (uint8)(TimerId & CCU6_KERNEL_MSK) ;
  Ccu6Timer = (uint8)((TimerId >> CCU6_TIMER_POS) & CCU6_TIMER_MSK) ;

  /* Based on the CCU6 Timer type, initiate the shadow transfer */
  if(Ccu6Timer == MCU_CCU6_TIMER_T12)
  {
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->TCTR4.U), \
                      IFX_CCU6_TCTR4_T12STR_OFF, \
                      CCU6_TCTR4_T12STR_LEN, \
                      CCU6_T12_STR);
  }
  else
  {
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->TCTR4.U), \
                      IFX_CCU6_TCTR4_T13STR_OFF, \
                      CCU6_TCTR4_T13STR_LEN, \
                      CCU6_T13_STR);
  }
  /* MISRA2012_RULE_2_2_JUSTIFICATION: All parameters used in Mcal_SetBitAtomic
   * are used in IMASKLDMST.
   * No other dead code persist is verified by code review.
   * No side effects foreseen by violating this MISRA rule. */
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability     : [cover parentID={9A072C26-65C3-485b-A0AF-0DBF426881F6}] **
**                                                                            **
** Syntax           : void  Mcu_17_Ccu6_TimerIntEnDis                         **
**                    (                                                       **
**                        const Mcu_17_Ccu6_TimerChIntType                    **
**                                                      * const Ccu6IntConfig **
**                    )                                                       **
**                                                                            **
** Description      : This function enables/disables the specified interrupts **
**                    for input the CCU6 timers.                              **
**                                                                            **
** Service ID       : 0x87                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : Ccu6IntConfig - CCU6 timer channel interrupt            **
**                                    configuration                           **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*******************************************************************************/
void Mcu_17_Ccu6_TimerIntEnDis
(
  const Mcu_17_Ccu6_TimerChIntType * const Ccu6IntConfig
)
{
  Mcu_17_Ccu6_KernelIdentifierType Ccu6Kernel = (uint8)(Ccu6IntConfig->TimerId
                                                             & CCU6_KERNEL_MSK);

  if (Ccu6IntConfig->IEnLen == (uint8)CCU6_IEN_SINGLE_EDGE)
  {
    /* Enable/Disable the timers interrupts */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U), \
        Ccu6IntConfig->IEnBitPos, CCU6_IEN_SINGLE_EDGE, Ccu6IntConfig->RegVal);
  }
  else
  {
    /* Enable/Disable the timers interrupts */
    Mcal_SetBitAtomic(&(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U), \
          Ccu6IntConfig->IEnBitPos, CCU6_IEN_BOTH_EDGE, Ccu6IntConfig->RegVal);
  }
  /* MISRA2012_RULE_2_2_JUSTIFICATION: All parameters used in Mcal_SetBitAtomic
   * are used in IMASKLDMST.
   * No other dead code persist is verified by code review.
   * No side effects foreseen by violating this MISRA rule. */
}

/*******************************************************************************
** Traceability     : [cover parentID={C87A59D9-F677-4f2c-930A-27C1B77DD1EA}] **
**                                                                            **
** Syntax           : Std_ReturnType  Mcu_17_Ccu6_TimerInitCheck              **
**                    (                                                       **
**                        const Mcu_17_Ccu6_TimerConfigType * const ConfigPtr **
**                    )                                                       **
**                                                                            **
** Description      : This interface verifies the instance of CCU6 timer      **
**                    channel in context to the initialization contents       **
**                                                                            **
** Service ID       : 0x89                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : ConfigPtr - Pointer to configuration data of a CCU6     **
**                    channel                                                 **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value   :   E_OK      - No error has been detected                  **
**                    E_NOT_OK  - Error has been detected                     **
**                                                                            **
*******************************************************************************/
Std_ReturnType Mcu_17_Ccu6_TimerInitCheck
(
  const Mcu_17_Ccu6_TimerConfigType * const ConfigPtr
)
{
  uint32 SfrVal;
  uint32 ConfigVal;
  uint32 CmpVal = 0xFFFFFFFFU;
  Std_ReturnType RetVal = E_NOT_OK;
  Mcu_17_Ccu6_KernelIdentifierType Ccu6Kernel;
  Mcu_17_Ccu6_TimerType Ccu6Timer;
  Mcu_17_Ccu6_ComparatorType Ccu6Comparator;

  Ccu6Kernel = (uint8)((ConfigPtr->TimerId) & CCU6_KERNEL_MSK);
  Ccu6Timer = (uint8)((ConfigPtr->TimerId >> CCU6_TIMER_POS) & CCU6_TIMER_MSK);
  Ccu6Comparator = (uint8)((ConfigPtr->TimerId >> CCU6_COMPARATOR_POS) & \
                           CCU6_COMPARATOR_MSK);

  /* [cover parentID={541D670E-99AB-43d3-9140-AB237931D8C9}]
   * Is selected kernel clock enabled
   * [/cover] */
  if (CCU6_KERNEL_ENABLE == Mcu_17_Ccu6_Kernel[Ccu6Kernel]->CLC.B.DISS)
  {
    /* [cover parentID={FD2BB9C8-F3FC-4b9f-AE85-3B4590371252}]
     * Is Timer T12 selected
     * [/cover] */
    if (Ccu6Timer == MCU_CCU6_TIMER_T12)
    {
      /* TCTR0.T12CLK */
      SfrVal = ((uint32)((Mcu_17_Ccu6_Kernel[Ccu6Kernel]->TCTR0.U) >> \
                        IFX_CCU6_TCTR0_T12CLK_OFF) & IFX_CCU6_TCTR0_T12CLK_MSK);
      ConfigVal = ((ConfigPtr->TimerCtrlReg0 >> IFX_CCU6_TCTR0_T12CLK_OFF) & \
                   IFX_CCU6_TCTR0_T12CLK_MSK);
      CmpVal &= ~(SfrVal ^ ConfigVal);

      /* TCTR0.T12PRE */
      SfrVal = ((uint32)((Mcu_17_Ccu6_Kernel[Ccu6Kernel]->TCTR0.U) >> \
                        IFX_CCU6_TCTR0_T12PRE_OFF) & IFX_CCU6_TCTR0_T12PRE_MSK);
      ConfigVal = ((ConfigPtr->TimerCtrlReg0 >> IFX_CCU6_TCTR0_T12PRE_OFF) & \
                   IFX_CCU6_TCTR0_T12PRE_MSK);
      CmpVal &= ~(SfrVal ^ ConfigVal);

      /* TCTR0.CTM */
      SfrVal = ((uint32)((Mcu_17_Ccu6_Kernel[Ccu6Kernel]->TCTR0.U) >> \
                         IFX_CCU6_TCTR0_CTM_OFF) & IFX_CCU6_TCTR0_CTM_MSK);
      ConfigVal = ((ConfigPtr->TimerCtrlReg0 >> IFX_CCU6_TCTR0_CTM_OFF) & \
                   IFX_CCU6_TCTR0_CTM_MSK);
      CmpVal &= ~(SfrVal ^ ConfigVal);

      /* MODCTR.T12MODEN */
      SfrVal = (((Mcu_17_Ccu6_Kernel[Ccu6Kernel]->MODCTR.U) >> \
                 (Ccu6Comparator * (uint32)CCU6_MODCTR_T12MODEN_LEN)) & \
                CCU6_MODCTR_T12MODEN_MSK);
      ConfigVal = (ConfigPtr->ModCtrlReg & CCU6_MODCTR_T12MODEN_MSK);
      CmpVal &= ~(SfrVal ^ ConfigVal);

      /* PSLR.PSL */
      SfrVal = (((Mcu_17_Ccu6_Kernel[Ccu6Kernel]->PSLR.U) >> \
                 (Ccu6Comparator * (uint32)CCU6_PSLR_PSL_LEN)) & \
                CCU6_PSLR_PSL_MSK);
      ConfigVal = (ConfigPtr->PasStateLvlReg & CCU6_PSLR_PSL_MSK);
      CmpVal &= ~(SfrVal ^ ConfigVal);

      /* IEN.ENT12PM register*/
      SfrVal = ((uint32)((Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U) >> \
                         IFX_CCU6_IEN_ENT12PM_OFF) & CCU6_IEN_ENT12PM_MSK);
      ConfigVal = ((uint32)ConfigPtr->IntEnReg & CCU6_IEN_ENT12PM_MSK);
      CmpVal &= ~(SfrVal ^ ConfigVal);

      /* IEN.ENCC6xR/F register*/
      SfrVal = (((Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U) >> \
                 (Ccu6Comparator * (uint32)CCU6_IEN_ENCC6xRF_LEN)) & \
                CCU6_IEN_ENCC6xRF_MSK);
      ConfigVal = (((uint32)ConfigPtr->IntEnReg >> CCU6_IEN_ENCC6xRF_POS) & \
                   CCU6_IEN_ENCC6xRF_MSK);
      CmpVal &= ~(SfrVal ^ ConfigVal);

      /* IEN.ENT12OM/F register*/
      SfrVal = (((Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U) >> \
                 IFX_CCU6_IEN_ENT12OM_OFF) & CCU6_IEN_ENT12OM_MSK);
      CmpVal &= ~(SfrVal);

      /* IEN.ENTRPF/F register*/
      SfrVal = (((Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U) >> \
                 IFX_CCU6_IEN_ENTRPF_OFF) & CCU6_IEN_ENTRPF_MSK);
      CmpVal &= ~(SfrVal);

      /* IEN.ENCHE/F register*/
      SfrVal = (((Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U) >> \
                 IFX_CCU6_IEN_ENCHE_OFF) & CCU6_IEN_ENCHE_MSK);
      CmpVal &= ~(SfrVal);

     /* IEN.ENWHE register*/
      SfrVal = (((Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U) >> \
                 IFX_CCU6_IEN_ENWHE_OFF) & CCU6_IEN_ENWHE_MSK);
      CmpVal &= ~(SfrVal);

       /* IEN.ENIDLE register*/
      SfrVal = (((Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U) >> \
                 IFX_CCU6_IEN_ENIDLE_OFF) & CCU6_IEN_ENIDLE_MSK);
      CmpVal &= ~(SfrVal);

       /* IEN.ENSTR register*/
      SfrVal = (((Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U) >> \
                 IFX_CCU6_IEN_ENSTR_OFF) & CCU6_IEN_ENSTR_MSK);
      CmpVal &= ~(SfrVal);

      /* INP.INPT12 register*/
      SfrVal = ((uint32)((Mcu_17_Ccu6_Kernel[Ccu6Kernel]->INP.U) >> \
                         IFX_CCU6_INP_INPT12_OFF)& CCU6_INP_INPT12_MSK);
      ConfigVal = (((uint32)\
                    ConfigPtr->IntNodePointerReg >> CCU6_INP_INPT12_POS) & \
                   CCU6_INP_INPT12_MSK);
      CmpVal &= ~(SfrVal ^ ConfigVal);

      /* INP.INPCC6x register*/
      SfrVal = (((Mcu_17_Ccu6_Kernel[Ccu6Kernel]->INP.U) >>  \
                 (Ccu6Comparator * (uint32)CCU6_INP_INPCC60_LEN)) & \
                CCU6_INP_INPCC60_MSK);
      ConfigVal = ((uint32)ConfigPtr->IntNodePointerReg & CCU6_INP_INPCC60_MSK);
      CmpVal &= ~(SfrVal ^ ConfigVal);

      /* PISEL */
      SfrVal = (uint32)(((Mcu_17_Ccu6_Kernel[Ccu6Kernel]->PISEL0.U) >> \
                         (Ccu6Comparator * (uint32)CCU6_PISEL0_ISCC60_LEN)) & \
                        CCU6_PISEL_MSK);
      ConfigVal = ((uint32)ConfigPtr->PortInSelReg0 & CCU6_PISEL_MSK);
      CmpVal &= ~(SfrVal ^ ConfigVal);

      /* T12MSEL */
      SfrVal = (uint32)(((Mcu_17_Ccu6_Kernel[Ccu6Kernel]->T12MSEL.U) >> \
                         (Ccu6Comparator * (uint32)CCU6_T12MSEL_MSEL60_LEN))& \
                        CCU6_T12MSEL_MSEL60_MSK);
      ConfigVal = ((uint32)ConfigPtr->TimerModeSelectReg & \
                   CCU6_T12MSEL_MSEL60_MSK);
      CmpVal &= ~(SfrVal ^ ConfigVal);

      /* TCTR2.T12SSC */
      SfrVal = (uint32)(((Mcu_17_Ccu6_Kernel[Ccu6Kernel]->TCTR2.U) >> \
                         IFX_CCU6_TCTR2_T12SSC_OFF)& \
                         CCU6_TCTR2_T12SSC_MSK);
      CmpVal &= ~(SfrVal);

      /* TCTR2.T12RSEL */
      SfrVal = (uint32)(((Mcu_17_Ccu6_Kernel[Ccu6Kernel]->TCTR2.U) >> \
                         IFX_CCU6_TCTR2_T12RSEL_OFF)& \
                         CCU6_TCTR2_T12RSEL_MSK);
      CmpVal &= ~(SfrVal);

      /* PISEL2.ISCNT12 */
      SfrVal = (uint32)(((Mcu_17_Ccu6_Kernel[Ccu6Kernel]->PISEL2.U) >> \
                         IFX_CCU6_PISEL2_ISCNT12_OFF)& \
                         CCU6_PISEL2_ISCNT12_MSK);
      CmpVal &= ~(SfrVal);

      /* PISEL2.T12EXT */
      SfrVal = (uint32)(((Mcu_17_Ccu6_Kernel[Ccu6Kernel]->PISEL2.U) >> \
                         IFX_CCU6_PISEL2_T12EXT_OFF)& \
                         CCU6_PISEL2_T12EXT_MSK);
      CmpVal &= ~(SfrVal);

      /* CMPSTAT.CC6xPS, COUT6xPS */
      SfrVal = (uint32)(((Mcu_17_Ccu6_Kernel[Ccu6Kernel]->CMPSTAT.U) >> \
                        ((Ccu6Comparator * (uint32)CCU6_CMPSTAT_PS_BITS_LEN) \
                         + IFX_CCU6_CMPSTAT_CC60PS_OFF))& \
                         CCU6_CMPSTAT_PS_BITS_MSK);
      CmpVal &= ~(SfrVal);

      /* T1xPR register */
      SfrVal = Mcu_17_Ccu6_Kernel[Ccu6Kernel]->T12PR.U;
      ConfigVal = (ConfigPtr->TimerPeriodReg & CCU6_T12_MSK);
      CmpVal &= ~(SfrVal ^ ConfigVal);

      /* CC6SR register */
      SfrVal = Mcu_17_Ccu6_Kernel[Ccu6Kernel]->CC6SR[Ccu6Comparator].U;
      ConfigVal = (ConfigPtr->Ccu6ShadowReg & CCU6_T12_MSK);
      CmpVal &= ~(SfrVal ^ ConfigVal);
    }
    else if (Ccu6Timer == MCU_CCU6_TIMER_T13)
    {
      /* TCTR0.T13CLK */
      SfrVal = (uint32)(((Mcu_17_Ccu6_Kernel[Ccu6Kernel]->TCTR0.U) >> \
                        IFX_CCU6_TCTR0_T13CLK_OFF) & IFX_CCU6_TCTR0_T13CLK_MSK);
      ConfigVal = ((ConfigPtr->TimerCtrlReg0 >> IFX_CCU6_TCTR0_T13CLK_OFF) & \
                   IFX_CCU6_TCTR0_T13CLK_MSK);
      CmpVal &= ~(SfrVal ^ ConfigVal);

      /* TCTR0.T13PRE */
      SfrVal = ((uint32)((Mcu_17_Ccu6_Kernel[Ccu6Kernel]->TCTR0.U) >> \
                         IFX_CCU6_TCTR0_T13PRE_OFF)& IFX_CCU6_TCTR0_T13PRE_MSK);
      ConfigVal = ((ConfigPtr->TimerCtrlReg0 >> IFX_CCU6_TCTR0_T13PRE_OFF) & \
                   IFX_CCU6_TCTR0_T13PRE_MSK);
      CmpVal &= ~(SfrVal ^ ConfigVal);

      /* MODCTR.ECT13O */
      SfrVal = (uint32)(((Mcu_17_Ccu6_Kernel[Ccu6Kernel]->MODCTR.U) >> \
                      IFX_CCU6_MODCTR_ECT13O_OFF) & IFX_CCU6_MODCTR_ECT13O_MSK);
      ConfigVal = ((ConfigPtr->ModCtrlReg >> CCU6_MODCTR_ECT13O_OFF) & \
                   IFX_CCU6_MODCTR_ECT13O_MSK);
      CmpVal &= ~(SfrVal ^ ConfigVal);

      /* PSLR.PSL63 */
      SfrVal = ((uint32)(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->PSLR.U >> \
                         IFX_CCU6_PSLR_PSL63_OFF) & IFX_CCU6_PSLR_PSL63_MSK);
      ConfigVal = ((ConfigPtr->PasStateLvlReg >> CCU6_PSLR_PSL63_OFF) & \
                   IFX_CCU6_PSLR_PSL63_MSK);
      CmpVal &= ~(SfrVal ^ ConfigVal);

      /* IEN.ENT13PM register*/
      SfrVal = ((uint32)((Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U) >> \
                         IFX_CCU6_IEN_ENT13PM_OFF) & IFX_CCU6_IEN_ENT13PM_MSK);
      ConfigVal = ((uint32)((uint32)ConfigPtr->IntEnReg & CCU6_IEN_ENT13PM_MSK));
      CmpVal &= ~(SfrVal ^ ConfigVal);

      /* IEN.ENT13CM register*/
      SfrVal = ((uint32)((Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U) >> \
                         IFX_CCU6_IEN_ENT13CM_OFF) & IFX_CCU6_IEN_ENT13CM_MSK);
      ConfigVal = (((uint32)ConfigPtr->IntEnReg >> CCU6_IEN_ENT13CM_POS) & \
                   CCU6_IEN_ENT13CM_MSK);
      CmpVal &= ~(SfrVal ^ ConfigVal);

      /* IEN.ENTRPF/F register*/
      SfrVal = (((Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U) >> \
                 IFX_CCU6_IEN_ENTRPF_OFF) & CCU6_IEN_ENTRPF_MSK);
      CmpVal &= ~(SfrVal);

      /* IEN.ENCHE/F register*/
      SfrVal = (((Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U) >> \
                 IFX_CCU6_IEN_ENCHE_OFF) & CCU6_IEN_ENCHE_MSK);
      CmpVal &= ~(SfrVal);

     /* IEN.ENWHE register*/
      SfrVal = (((Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U) >> \
                 IFX_CCU6_IEN_ENWHE_OFF) & CCU6_IEN_ENWHE_MSK);
      CmpVal &= ~(SfrVal);

       /* IEN.ENIDLE register*/
      SfrVal = (((Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U) >> \
                 IFX_CCU6_IEN_ENIDLE_OFF) & CCU6_IEN_ENIDLE_MSK);
      CmpVal &= ~(SfrVal);

       /* IEN.ENSTR register*/
      SfrVal = (((Mcu_17_Ccu6_Kernel[Ccu6Kernel]->IEN.U) >> \
                 IFX_CCU6_IEN_ENSTR_OFF) & CCU6_IEN_ENSTR_MSK);
      CmpVal &= ~(SfrVal);

      /* INP.T13 register*/
      SfrVal = ((uint32)(((Mcu_17_Ccu6_Kernel[Ccu6Kernel]->INP.U) >> \
                          IFX_CCU6_INP_INPT13_OFF) & IFX_CCU6_INP_INPT13_MSK));
      ConfigVal = (uint32)(((uint32)ConfigPtr->IntNodePointerReg >> \
                            CCU6_INP_INPT13_POS) & CCU6_INP_INPT13_MSK);
      CmpVal &= ~(SfrVal ^ ConfigVal);

      SfrVal = (uint32)(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->CC63SR.U);
      ConfigVal = (ConfigPtr->Ccu6ShadowReg & CCU6_T12_MSK);
      CmpVal &= ~(SfrVal ^ ConfigVal);

      /* PISEL2.ISCNT13 */
      SfrVal = ((uint32)(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->PISEL2.U >> \
                   IFX_CCU6_PISEL2_ISCNT13_OFF) & IFX_CCU6_PISEL2_ISCNT13_MSK);
      CmpVal &= ~(SfrVal);

      /* PISEL2.T13EXT */
      SfrVal = ((uint32)(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->PISEL2.U >> \
                     IFX_CCU6_PISEL2_T13EXT_OFF) & IFX_CCU6_PISEL2_T13EXT_MSK);
      CmpVal &= ~(SfrVal);

      /* PISEL2.IST13HR */
      SfrVal = ((uint32)(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->PISEL2.U >> \
                   IFX_CCU6_PISEL2_IST13HR_OFF) & IFX_CCU6_PISEL2_IST13HR_MSK);
      CmpVal &= ~(SfrVal);

      /* CMPSTAT.T13IM */
      SfrVal = ((uint32)(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->CMPSTAT.U >> \
                     IFX_CCU6_CMPSTAT_T13IM_OFF) & IFX_CCU6_CMPSTAT_T13IM_MSK);
      CmpVal &= ~(SfrVal);

      /* CMPSTAT.COUT63PS */
      SfrVal = ((uint32)(Mcu_17_Ccu6_Kernel[Ccu6Kernel]->CMPSTAT.U >> \
               IFX_CCU6_CMPSTAT_COUT63PS_OFF) & IFX_CCU6_CMPSTAT_COUT63PS_MSK);
      CmpVal &= ~(SfrVal);

    /* T1xPR register */
      SfrVal = Mcu_17_Ccu6_Kernel[Ccu6Kernel]->T13PR.U;
      ConfigVal = (ConfigPtr->TimerPeriodReg & CCU6_T12_MSK);
      CmpVal &= ~(SfrVal ^ ConfigVal);
    }
    else
    {
      /* Reset compare flag to indicate failure */
      CmpVal = 0x0U;
    }
  }
  else
  {
    /* Reset compare flag to indicate failure */
    CmpVal = 0x0U;
  }

  /* [cover parentID={2D4D9C14-25AD-4f55-99D0-F31842B37852}]
   * Are all verifications successful
   * [/cover] */
  if(CmpVal == 0xFFFFFFFFU)
  {
    RetVal = E_OK;
  }

  return RetVal;
}

/*******************************************************************************
** Traceability     : [cover parentID={461B4A1D-0997-4f9a-A8F5-4FA58D11E675}] **
**                                                                            **
** Syntax           : void  Mcu_17_Gpt12_TimerInit                            **
**                    (                                                       **
**                       const Mcu_17_Gpt12_TimerConfigType * const ConfigPtr **
**                    )                                                       **
**                                                                            **
** Description      : This interface configures an instance of a GPT12 timer  **
**                    channel. User of a GPT12 channel invokes this interface **
**                    at the time of formers initialization                   **
**                                                                            **
** Service ID       : 0x8A                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : ConfigPtr - Gpt12 Timer channel initialization contents **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*******************************************************************************/
void Mcu_17_Gpt12_TimerInit
(
  const Mcu_17_Gpt12_TimerConfigType * const ConfigPtr
)
{

  /* TxCON */
  /* Initialize the GPT timer channel
      - Configure the timer control register
      - Configure the timer channel's port selection configuration
      - Configure the timer counter
   */
   Mcu_17_Gpt12_TimerChIdentifierType TimerId;
   TimerId = ConfigPtr->TimerId;
   if ((TimerId == MCU_GPT12_TIMER3) || (TimerId == MCU_GPT12_TIMER6))
   {
       uint32 GptSfrVal = *(Mcu_17_Gpt12_TimerCtrlReg[TimerId]);
       GptSfrVal = (GptSfrVal & GPT12_BPS_MSK);
      *(Mcu_17_Gpt12_TimerCtrlReg[TimerId]) = (GptSfrVal |
                             ((ConfigPtr->TimerCtrlReg) & GPT12_BPS_NEG_MSK));
   }
   else
   {
      *(Mcu_17_Gpt12_TimerCtrlReg[TimerId]) = ConfigPtr->TimerCtrlReg;
   }

  switch(TimerId)
  {
    case MCU_GPT12_TIMER2:
    {
      /* PISEL.IST2IN */
      Mcal_SetBitAtomic(&GPT120_PISEL.U, \
                        IFX_GPT12_PISEL_IST2IN_OFF, \
                        GPT12_PISEL_IST2IN_LEN, \
                        ConfigPtr->PortInSelReg & IFX_GPT12_PISEL_IST2IN_MSK);
      /* PISEL.IST2EUD */
      Mcal_SetBitAtomic(&GPT120_PISEL.U, \
                        IFX_GPT12_PISEL_IST2EUD_OFF, \
                        GPT12_PISEL_IST2EUD_LEN, \
                        (ConfigPtr->PortInSelReg >> GPT12_PISEL_ISTxEUD_OFF) & \
                        IFX_GPT12_PISEL_IST2EUD_MSK);
      /* T2 */
      GPT120_T2.U = ConfigPtr->TimerCntReg;
      break;
    }
    case MCU_GPT12_TIMER3:
    {
      /* PISEL.IST3IN */
      Mcal_SetBitAtomic(&GPT120_PISEL.U, \
                        IFX_GPT12_PISEL_IST3IN_OFF, \
                        GPT12_PISEL_IST3IN_LEN, \
                        ConfigPtr->PortInSelReg & IFX_GPT12_PISEL_IST3IN_MSK);
      /* PISEL.IST3EUD */
      Mcal_SetBitAtomic(&GPT120_PISEL.U, \
                        IFX_GPT12_PISEL_IST3EUD_OFF, \
                        GPT12_PISEL_IST3EUD_LEN, \
                        (ConfigPtr->PortInSelReg >> GPT12_PISEL_ISTxEUD_OFF) & \
                        IFX_GPT12_PISEL_IST3EUD_MSK);

      /* T3 */
      GPT120_T3.U = ConfigPtr->TimerCntReg;
      break;
    }
    case MCU_GPT12_TIMER4:
    {
      /* PISEL.IST4IN */
      Mcal_SetBitAtomic(&GPT120_PISEL.U, \
                        IFX_GPT12_PISEL_IST4IN_OFF, \
                        GPT12_PISEL_IST4IN_LEN, \
                        ConfigPtr->PortInSelReg & IFX_GPT12_PISEL_IST4IN_MSK);
      /* PISEL.IST4EUD */
      Mcal_SetBitAtomic(&GPT120_PISEL.U, \
                        IFX_GPT12_PISEL_IST4EUD_OFF, \
                        GPT12_PISEL_IST4EUD_LEN, \
                        (ConfigPtr->PortInSelReg >> GPT12_PISEL_ISTxEUD_OFF) & \
                        IFX_GPT12_PISEL_IST4EUD_MSK);

      /* T4 */
      GPT120_T4.U = ConfigPtr->TimerCntReg;
      break;
    }
    case MCU_GPT12_TIMER5:
    {
      /* PISEL.IST5IN */
      Mcal_SetBitAtomic(&GPT120_PISEL.U, \
                        IFX_GPT12_PISEL_IST5IN_OFF, \
                        GPT12_PISEL_IST5IN_LEN, \
                        ConfigPtr->PortInSelReg & IFX_GPT12_PISEL_IST5IN_MSK);
      /* PISEL.IST5EUD */
      Mcal_SetBitAtomic(&GPT120_PISEL.U, \
                        IFX_GPT12_PISEL_IST5EUD_OFF, \
                        GPT12_PISEL_IST5EUD_LEN, \
                        (ConfigPtr->PortInSelReg >> GPT12_PISEL_ISTxEUD_OFF) & \
                        IFX_GPT12_PISEL_IST5EUD_MSK);

      /* T5 */
      GPT120_T5.U = ConfigPtr->TimerCntReg;
      break;
    }
    default:
    {
      /* PISEL.IST6IN */
      Mcal_SetBitAtomic(&GPT120_PISEL.U, \
                        IFX_GPT12_PISEL_IST6IN_OFF, \
                        GPT12_PISEL_IST6IN_LEN, \
                        ConfigPtr->PortInSelReg & IFX_GPT12_PISEL_IST6IN_MSK);
      /* PISEL.IST6EUD */
      Mcal_SetBitAtomic(&GPT120_PISEL.U, \
                        IFX_GPT12_PISEL_IST6EUD_OFF, \
                        GPT12_PISEL_IST6EUD_LEN, \
                        (ConfigPtr->PortInSelReg >> GPT12_PISEL_ISTxEUD_OFF) & \
                        IFX_GPT12_PISEL_IST6EUD_MSK);

      /* T6 */
      GPT120_T6.U = ConfigPtr->TimerCntReg;
      break;
    }
  }
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability     : [cover parentID={1344BE7A-847D-4c14-B964-156099B6FF7A}] **
**                                                                            **
** Syntax           : void  Mcu_17_Gpt12_TimerInitCheck                       **
**                    (                                                       **
**                        const Mcu_17_Gpt12_TimerConfigType *const ConfigPtr **
**                    )                                                       **
**                                                                            **
** Description      : This interface verifies the instance of GPT12 timer     **
**                    channel in context to the initialization contents       **
**                                                                            **
** Service ID       : 0x8B                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : ConfigPtr - Gpt12 Timer channel initialization contents **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value   :   E_OK      - No error has been detected                  **
**                    E_NOT_OK  - Error has been detected                     **
**                                                                            **
*******************************************************************************/
Std_ReturnType Mcu_17_Gpt12_TimerInitCheck
(
  const Mcu_17_Gpt12_TimerConfigType *const ConfigPtr
)
{
  volatile uint32 CmpVal = 0xFFFFFFFFU;
  uint32 SfrVal;
  uint32 ConfigVal;
  Mcu_17_Gpt12_TimerChIdentifierType TimerId;
  Std_ReturnType RetVal = E_NOT_OK;

  TimerId = ConfigPtr->TimerId;
  /* [cover parentID={799AB54C-CDD2-4bd7-BFDE-ADF889CD1EB7}]
   * Is GPT12 module enabled
   * [/cover] */
  if(GPT12_TIMER_ENABLE == GPT120_CLC.B.DISS)
  {
    if ((TimerId == MCU_GPT12_TIMER3) || (TimerId == MCU_GPT12_TIMER6))
    {
        SfrVal = *(Mcu_17_Gpt12_TimerCtrlReg[TimerId]);
        SfrVal = (SfrVal & GPT12_BPS_NEG_MSK)& GPT12_TxCTRL_MSK;
    }
    else
    {
       SfrVal = *(Mcu_17_Gpt12_TimerCtrlReg[(ConfigPtr->TimerId)]) & \
              GPT12_TxCTRL_MSK;
    }
    if ((TimerId == MCU_GPT12_TIMER3) || (TimerId == MCU_GPT12_TIMER6))
    {
      ConfigVal = (ConfigPtr->TimerCtrlReg & GPT12_BPS_NEG_MSK) & \
                   GPT12_TxCTRL_MSK;
    }
    else
    {
      ConfigVal = ConfigPtr->TimerCtrlReg & GPT12_TxCTRL_MSK;
    }
    CmpVal   &= ~(SfrVal ^ ConfigVal);

    switch(ConfigPtr->TimerId)
    {
      /* [cover parentID={BBCE343A-FAD9-4070-A0CB-8557E79339FC}]
       * Is Timer 2 selected
       * [/cover] */
      case MCU_GPT12_TIMER2:
      {
        /*GPT12_PISEL.IST2IN Value*/
        SfrVal    = (((uint32)GPT120_PISEL.U >> IFX_GPT12_PISEL_IST2IN_OFF) & \
                     IFX_GPT12_PISEL_IST2IN_MSK);
        ConfigVal = ((uint32)\
                     ConfigPtr->PortInSelReg & IFX_GPT12_PISEL_IST2IN_MSK);
        CmpVal   &= ~(SfrVal ^ ConfigVal);

        /* PISEL.IST2EUD */
        SfrVal    = (((uint32)GPT120_PISEL.U >> IFX_GPT12_PISEL_IST2EUD_OFF) & \
                     IFX_GPT12_PISEL_IST2EUD_MSK);
        ConfigVal = (((uint32)ConfigPtr->PortInSelReg >> \
                      GPT12_PISEL_ISTxEUD_OFF) & IFX_GPT12_PISEL_IST2EUD_MSK);
        CmpVal   &= ~(SfrVal ^ ConfigVal);
        break;
      }

      /* [cover parentID={C5CEA14B-73A1-4ca5-AE3E-A3374F5CA5D4}]
       * Is Timer3 selected
       * [/cover] */
      case MCU_GPT12_TIMER3:
      {
        /* PISEL.IST3IN */
        SfrVal    = (((uint32)GPT120_PISEL.U >> IFX_GPT12_PISEL_IST3IN_OFF) & \
                     IFX_GPT12_PISEL_IST3IN_MSK);
        ConfigVal = ((uint32)ConfigPtr->PortInSelReg & \
                     IFX_GPT12_PISEL_IST3IN_MSK);
        CmpVal   &= ~(SfrVal ^ ConfigVal);

        /* PISEL.IST3EUD */
        SfrVal    = (((uint32)GPT120_PISEL.U >> IFX_GPT12_PISEL_IST3EUD_OFF) & \
                     IFX_GPT12_PISEL_IST3EUD_MSK);
        ConfigVal = (((uint32)ConfigPtr->PortInSelReg >> \
                      GPT12_PISEL_ISTxEUD_OFF) & IFX_GPT12_PISEL_IST3EUD_MSK);
        CmpVal   &= ~(SfrVal ^ ConfigVal);
        break;
      }

      /* [cover parentID={14B570A3-97C7-4f00-BC54-38F2274865C9}]
       * Is Timer4 selected
       * [/cover] */
      case MCU_GPT12_TIMER4:
      {
        /* PISEL.IST4IN */
        SfrVal    = (((uint32)GPT120_PISEL.U >> IFX_GPT12_PISEL_IST4IN_OFF) & \
                     IFX_GPT12_PISEL_IST4IN_MSK);
        ConfigVal = ((uint32)ConfigPtr->PortInSelReg & \
                     IFX_GPT12_PISEL_IST4IN_MSK);
        CmpVal   &= ~(SfrVal ^ ConfigVal);

        /* PISEL.IST4EUD */
        SfrVal    = (((uint32)GPT120_PISEL.U >> IFX_GPT12_PISEL_IST4EUD_OFF) & \
                     IFX_GPT12_PISEL_IST4EUD_MSK);
        ConfigVal = (((uint32)ConfigPtr->PortInSelReg >> \
                      GPT12_PISEL_ISTxEUD_OFF) & IFX_GPT12_PISEL_IST4EUD_MSK);
        CmpVal   &= ~(SfrVal ^ ConfigVal);
        break;
      }

      /* [cover parentID={0685FE4F-78B5-4866-8090-5683B6245117}]
       * Is Timer5 selected
       * [/cover] */
      case MCU_GPT12_TIMER5:
      {
        /* PISEL.IST5IN */
        SfrVal    = (((uint32)GPT120_PISEL.U >> IFX_GPT12_PISEL_IST5IN_OFF) & \
                     IFX_GPT12_PISEL_IST5IN_MSK);
        ConfigVal = ((uint32)ConfigPtr->PortInSelReg & \
                     IFX_GPT12_PISEL_IST5IN_MSK);
        CmpVal   &= ~(SfrVal ^ ConfigVal);

        /* PISEL.IST5EUD */
        SfrVal    = (((uint32)GPT120_PISEL.U >> IFX_GPT12_PISEL_IST5EUD_OFF ) & \
                     IFX_GPT12_PISEL_IST5EUD_MSK);
        ConfigVal = (((uint32)ConfigPtr->PortInSelReg >> \
                      GPT12_PISEL_ISTxEUD_OFF) & IFX_GPT12_PISEL_IST5EUD_MSK);
        CmpVal   &= ~(SfrVal ^ ConfigVal);
        break;
      }

      /* [cover parentID={6CFE497D-ADF1-4305-B136-7DF8FCE66FB5}]
       * Verify Timer6 related register contents against configured value
       * [/cover] */
      default:
      {
        /* PISEL.IST6IN */
        SfrVal    = (((uint32)GPT120_PISEL.U >> IFX_GPT12_PISEL_IST6IN_OFF) & \
                     IFX_GPT12_PISEL_IST6IN_MSK);
        ConfigVal = ((uint32)ConfigPtr->PortInSelReg & \
                     IFX_GPT12_PISEL_IST6IN_MSK);
        CmpVal   &= ~(SfrVal ^ ConfigVal);

        /* PISEL.IST6EUD */
        SfrVal    = (((uint32)GPT120_PISEL.U >> IFX_GPT12_PISEL_IST6EUD_OFF) & \
                     IFX_GPT12_PISEL_IST6EUD_MSK);
        ConfigVal = (((uint32)ConfigPtr->PortInSelReg >> \
                      GPT12_PISEL_ISTxEUD_OFF) & IFX_GPT12_PISEL_IST6EUD_MSK);
        CmpVal   &= ~(SfrVal ^ ConfigVal);
        break;
      }
    }

    /* [cover parentID={66C34A2F-7D69-4af8-9382-03FEF8ED9601}]
     * Are all verifications successful
     * [/cover] */
    if(CmpVal == 0xFFFFFFFFU)
    {
      RetVal = E_OK;
    }
  }



  return RetVal;
}

/*******************************************************************************
** Traceability     : [cover parentID={84BAC3EA-1096-49de-9F8D-1302A908924E}] **
**                                                                            **
** Syntax           : void  Mcu_17_Gpt12_TimerDeInit                          **
**                    (                                                       **
**                       const Mcu_17_Gpt12_TimerChIdentifierType TimerId     **
**                    )                                                       **
**                                                                            **
** Description      : This function de-initializes the input GPT12 timer      **
**                    channel to default values                               **
**                                                                            **
** Service ID       : 0x8C                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : TimerId - GPT12 timer to be de-initialized              **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*******************************************************************************/
void Mcu_17_Gpt12_TimerDeInit
(
  const Mcu_17_Gpt12_TimerChIdentifierType TimerId
)
{

  /* De-initialize the GPT timer channel
      - De-initialize the timer control register
      - De-initialize the timer channel's port selection configuration
      - Reset the timer counter
   */
  /* TxCON */

   if ((TimerId == MCU_GPT12_TIMER3) || (TimerId == MCU_GPT12_TIMER6))
   {
       uint32 GptSfrVal = *(Mcu_17_Gpt12_TimerCtrlReg[TimerId]);
       GptSfrVal = (GptSfrVal & GPT12_BPS_MSK);
      *(Mcu_17_Gpt12_TimerCtrlReg[TimerId]) = GPT12_TxCON_RESET_VAL |
                                              GptSfrVal;
   }
   else
   {
      *(Mcu_17_Gpt12_TimerCtrlReg[TimerId]) = GPT12_TxCON_RESET_VAL;
   }

  switch(TimerId)
  {
    case MCU_GPT12_TIMER2:
    {
      /* PISEL.IST2IN */
      Mcal_SetBitAtomic(&GPT120_PISEL.U, \
                        IFX_GPT12_PISEL_IST2IN_OFF, \
                        GPT12_PISEL_IST2IN_LEN, \
                        GPT12_PISEL_ISTxIN_RESET_VAL);
      /* PISEL.IST2EUD */
      Mcal_SetBitAtomic(&GPT120_PISEL.U, \
                        IFX_GPT12_PISEL_IST2EUD_OFF, \
                        GPT12_PISEL_IST2EUD_LEN, \
                        GPT12_PISEL_ISTxEUD_RESET_VAL);
      /* T2 */
      GPT120_T2.U = GPT12_Tx_RESET_VAL;
      break;
    }
    case MCU_GPT12_TIMER3:
    {
      /* PISEL.IST3IN */
      Mcal_SetBitAtomic(&GPT120_PISEL.U, \
                        IFX_GPT12_PISEL_IST3IN_OFF, \
                        GPT12_PISEL_IST3IN_LEN, \
                        GPT12_PISEL_ISTxIN_RESET_VAL);
      /* PISEL.IST3EUD */
      Mcal_SetBitAtomic(&GPT120_PISEL.U, \
                        IFX_GPT12_PISEL_IST3EUD_OFF, \
                        GPT12_PISEL_IST3EUD_LEN, \
                        GPT12_PISEL_ISTxEUD_RESET_VAL);

      /* T3 */
      GPT120_T3.U = GPT12_Tx_RESET_VAL;
      break;
    }
    case MCU_GPT12_TIMER4:
    {
      /* PISEL.IST4IN */
      Mcal_SetBitAtomic(&GPT120_PISEL.U, \
                        IFX_GPT12_PISEL_IST4IN_OFF, \
                        GPT12_PISEL_IST4IN_LEN, \
                        GPT12_PISEL_ISTxIN_RESET_VAL);
      /* PISEL.IST4EUD */
      Mcal_SetBitAtomic(&GPT120_PISEL.U, \
                        IFX_GPT12_PISEL_IST4EUD_OFF, \
                        GPT12_PISEL_IST4EUD_LEN, \
                        GPT12_PISEL_ISTxEUD_RESET_VAL);

      /* T4 */
      GPT120_T4.U = GPT12_Tx_RESET_VAL;
      break;
    }
    case MCU_GPT12_TIMER5:
    {
      /* PISEL.IST5IN */
      Mcal_SetBitAtomic(&GPT120_PISEL.U, \
                        IFX_GPT12_PISEL_IST5IN_OFF, \
                        GPT12_PISEL_IST5IN_LEN, \
                        GPT12_PISEL_ISTxIN_RESET_VAL);
      /* PISEL.IST5EUD */
      Mcal_SetBitAtomic(&GPT120_PISEL.U, \
                        IFX_GPT12_PISEL_IST5EUD_OFF, \
                        GPT12_PISEL_IST5EUD_LEN, \
                        GPT12_PISEL_ISTxEUD_RESET_VAL);

      /* T5 */
      GPT120_T5.U = GPT12_Tx_RESET_VAL;
      break;
    }
    default:
    {
      /* PISEL.IST6IN */
      Mcal_SetBitAtomic(&GPT120_PISEL.U, \
                        IFX_GPT12_PISEL_IST6IN_OFF, \
                        GPT12_PISEL_IST6IN_LEN, \
                        GPT12_PISEL_ISTxIN_RESET_VAL);
      /* PISEL.IST6EUD */
      Mcal_SetBitAtomic(&GPT120_PISEL.U, \
                        IFX_GPT12_PISEL_IST6EUD_OFF, \
                        GPT12_PISEL_IST6EUD_LEN, \
                        GPT12_PISEL_ISTxEUD_RESET_VAL);

      /* T6 */
      GPT120_T6.U = GPT12_Tx_RESET_VAL;
      break;
    }
  }
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability     : [cover parentID={69504730-4F6C-4945-95E8-FDA683E5F07A}] **
**                                                                            **
** Syntax           : void  Mcu_17_Gpt12_TimerStart                           **
**                    (                                                       **
**                       const Mcu_17_Gpt12_TimerChIdentifierType TimerId     **
**                    )                                                       **
**                                                                            **
** Description      : This function starts the specified GPT12 timer.         **
**                                                                            **
** Service ID       : 0x8D                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : TimerId - GPT12 timer channel to be enabled             **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*******************************************************************************/
void Mcu_17_Gpt12_TimerStart
(
  const Mcu_17_Gpt12_TimerChIdentifierType TimerId
)
{
  /* Start the GPT12 timer channel by writing into its control registers */
  Mcal_SetBitAtomic(Mcu_17_Gpt12_TimerCtrlReg[TimerId], \
                    GPT12_TxCON_TxR_OFF, \
                    GPT12_TxCON_TxR_LEN, \
                    GPT12_Tx_START);
  /* MISRA2012_RULE_2_7_JUSTIFICATION: TimerId is used in Mcal_SetBitAtomic
   * No side effects foreseen by violating this MISRA rule. */
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}


/*******************************************************************************
** Traceability     : [cover parentID={8AF6A928-36DD-4c2c-A9A7-FA86CB6C34D9}] **
**                                                                            **
** Syntax           : void  Mcu_17_Gpt12_TimerStop                            **
**                    (                                                       **
**                       const Mcu_17_Gpt12_TimerChIdentifierType TimerId     **
**                    )                                                       **
**                                                                            **
** Description      : This function stops the specified GPT12 timer.          **
**                                                                            **
** Service ID       : 0x8E                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : TimerId - GPT12 timer channel to be disabled            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*******************************************************************************/
void Mcu_17_Gpt12_TimerStop
(
  const Mcu_17_Gpt12_TimerChIdentifierType TimerId
)
{
  /* Stop the GPT12 timer channel by writing into its control registers */
  Mcal_SetBitAtomic(Mcu_17_Gpt12_TimerCtrlReg[TimerId], \
                    GPT12_TxCON_TxR_OFF, \
                    GPT12_TxCON_TxR_LEN, \
                    GPT12_Tx_STOP);
  /* MISRA2012_RULE_2_7_JUSTIFICATION: TimerId is used in Mcal_SetBitAtomic
   * No side effects foreseen by violating this MISRA rule. */
  /*[cover parentID={C8410B61-0BFF-49d6-9BBD-817EA33BF71D}]Interrupt Control
  Registers[/cover]*/
}

/*******************************************************************************
** Traceability     : [cover parentID={26371E57-9CC0-4341-BE0D-8F42D5330B2F}] **
**                                                                            **
** Syntax           : void  Mcu_17_Stm_SetupComparator                        **
**                    (                                                       **
**                      const Mcu_17_Stm_TimerConfigType * const ConfigPtr    **
**                    )                                                       **
**                                                                            **
** Description      : This interface configures the compare register of STM   **
**                    timer                                                   **
**                                                                            **
** Service ID       : 0x90                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other STM Comparator                      **
**                                                                            **
** Parameters(in)   : ConfigPtr - STM Timer Compare operation contents        **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*******************************************************************************/
void Mcu_17_Stm_SetupComparator
(
  const Mcu_17_Stm_TimerConfigType * const ConfigPtr
)
{
  uint8  StmComparatorId;
  uint8  StmCmpIRRBit;
  uint8  StmTimerId;
  uint8  CmconBitPos;
  uint8  CmpEnable;
  uint8  CmpBitPos;

  StmTimerId = (uint8)(ConfigPtr->StmTimerId & STM_TIMER_ID_MASK);
  StmComparatorId = ((uint8)(ConfigPtr->CMPRegId) & STM_COMPARATOR_MASK);

  /* [cover parentID={9E34378E-B058-49f7-86C5-E8E5EE0C6C9A}]
   * Is Comparator0 used
   * [/cover] */
  if(StmComparatorId == (uint8)STM_CMP0)
  {
    /* Enable CMP0 with Output routed to STMIR0 */
    CmpEnable    = STM_ICR_CMP0_EN;
    CmpBitPos    = IFX_STM_ICR_CMP0EN_OFF;
    CmconBitPos  = IFX_STM_CMCON_MSIZE0_OFF;
    StmCmpIRRBit = IFX_STM_ISCR_CMP0IRR_OFF;
  }
  /* [cover parentID={D73E4288-33E5-4c07-9C91-A1B97DACF2A5}]
   * Enable/Disable CMP1 with Output routed to STMIR1
   * [/cover] */
  else
  {
    /* Enable CMP1 with Output routed to STMIR1 */
    CmpEnable    = STM_ICR_CMP1_EN;
    CmpBitPos    = IFX_STM_ICR_CMP1EN_OFF;
    CmconBitPos  = IFX_STM_CMCON_MSIZE1_OFF;
    StmCmpIRRBit = IFX_STM_ISCR_CMP1IRR_OFF;
  }

  /* Disable compare match interrupt to avoid unwanted interrupts during
     configuring the comparator */
  Mcal_SetBitAtomic((&Mcu_17_Stm[StmTimerId]->ICR.U), \
                    CmpBitPos, \
                    STM_ICR_LEN, \
                    STM_COMP_INT_DIS);

  /* Configure the compare value */
  Mcu_17_Stm[StmTimerId]->CMP[StmComparatorId].U = ConfigPtr->CompareRegVal;

  /* Configure the number of bits to be used for the compare operation */
  Mcal_SetBitAtomic((&Mcu_17_Stm[StmTimerId]->CMCON.U), \
                    CmconBitPos, \
                    STM_CMCON_MSIZE_LEN, \
                    ConfigPtr->CmconRegVal);

  /* Clear ISCR to avoid unintended interrupt from application reset */
  Mcal_SetBitAtomic((&Mcu_17_Stm[StmTimerId]->ISCR.U), \
                    StmCmpIRRBit, \
                    STM_ISCR_CMPIRR_LEN, \
                    0x1U);

  /* Enable the compare match interrupt */
  Mcal_SetBitAtomic((&Mcu_17_Stm[StmTimerId]->ICR.U), \
                    CmpBitPos, \
                    STM_ICR_LEN, \
                    CmpEnable);
  /* MISRA2012_RULE_2_2_JUSTIFICATION: All parameters used in Mcal_SetBitAtomic
   * are used in IMASKLDMST.
   * No other dead code persist is verified by code review.
   * No side effects foreseen by violating this MISRA rule. */
}

/*******************************************************************************
** Traceability     : [cover parentID={F207D130-9495-4ef2-A24A-99996D0DEB27}] **
**                                                                            **
** Syntax           : void  Mcu_17_Stm_CheckComparator                        **
**                    (                                                       **
**                        const Mcu_17_Stm_TimerConfigType * const ConfigPtr  **
**                    )                                                       **
**                                                                            **
** Description      : This interface checks the configuration of compare      **
**                    register against the passed configuration               **
**                                                                            **
** Service ID       : 0x91                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters(in)   : ConfigPtr - STM Timer channel initialization contents   **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value   :   E_OK      - No error has been detected                  **
**                    E_NOT_OK  - Error has been detected                     **
**                                                                            **
*******************************************************************************/
Std_ReturnType Mcu_17_Stm_CheckComparator
(
  const Mcu_17_Stm_TimerConfigType * const ConfigPtr
)
{
  uint32 SfrVal;
  uint32 ConfigVal;
  uint32 CmpVal = 0xFFFFFFFFU;
  Std_ReturnType RetVal = E_NOT_OK;
  uint8  StmComparatorId;
  uint8  StmTimerId;
  uint8  CmconBitPos;
  uint8  CmpBitPos;

  StmTimerId = (uint8)(ConfigPtr->StmTimerId & STM_TIMER_ID_MASK);
  StmComparatorId = ((uint8)(ConfigPtr->CMPRegId) & STM_COMPARATOR_MASK);

  if(StmComparatorId == (uint8)STM_CMP0)
  {
    /* CMP 0 */
    ConfigVal   = STM_ICR_CMP0_EN;
    CmpBitPos   = IFX_STM_ICR_CMP0EN_OFF;
    CmconBitPos = IFX_STM_CMCON_MSIZE0_OFF;
  }
  else
  {
    /* CMP 1 */
    ConfigVal   = STM_ICR_CMP1_EN;
    CmpBitPos   = IFX_STM_ICR_CMP1EN_OFF;
    CmconBitPos = IFX_STM_CMCON_MSIZE1_OFF;
  }

  /* Check ICR Value */
  SfrVal = (Mcal_GetBitAtomic((Mcu_17_Stm[StmTimerId]->ICR.U), \
                              CmpBitPos, \
                              STM_ICR_LEN) & STM_ICR_MASK);
  CmpVal &= ~(SfrVal ^ ConfigVal);

  /* Check CMCON Value */
  SfrVal = Mcal_GetBitAtomic((Mcu_17_Stm[StmTimerId]->CMCON.U), \
                             CmconBitPos, \
                             STM_CMCON_MSIZE_LEN);
  ConfigVal = ConfigPtr->CmconRegVal;
  CmpVal &= ~(SfrVal ^ ConfigVal);

  if(CmpVal == 0xFFFFFFFFU)
  {
    RetVal = E_OK;
  }

  return RetVal;
}

/*******************************************************************************
** Traceability     : [cover parentID={473F1DAD-8F16-4542-AB0D-92B698F24F8E}] **
**                                                                            **
** Syntax           : void Mcu_17_Stm_ComparatorIntDisable                    **
**                    (                                                       **
**                      const uint8 StmTimerId,                               **
**                      const uint8 StmComparatorId                           **
**                    )                                                       **
**                                                                            **
** Description      : This interface disables the comparator interrupt        **
**                                                                            **
** Service ID       : 0x88                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other STM Timers                          **
**                                                                            **
** Parameters(in)   : StmTimerId      - STM Timer ID                          **
**                    StmComparatorId - STM Timer Comparator ID               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*******************************************************************************/
void Mcu_17_Stm_ComparatorIntDisable
(
  const uint8 StmTimerId,
  const uint8 StmComparatorId
)
{
  uint8 CmpBitPos;

  /* Calculate the CmpEN bit based on the comparator */
  if(StmComparatorId == (uint8)STM_CMP0)
  {
    /* CMP 0 */
    CmpBitPos = IFX_STM_ICR_CMP0EN_OFF;
  }
  else
  {
    /* CMP 1 */
    CmpBitPos = IFX_STM_ICR_CMP1EN_OFF;
  }

  /* Disable the compare match interrupt */
  Mcal_SetBitAtomic((&Mcu_17_Stm[StmTimerId]->ICR.U), \
                    CmpBitPos, \
                    STM_ICR_CMPEN_LEN, \
                    STM_COMP_INT_DIS);
  /* MISRA2012_RULE_2_2_JUSTIFICATION: All parameters used in Mcal_SetBitAtomic
   * are used in IMASKLDMST.
   * No other dead code persist is verified by code review.
   * No side effects foreseen by violating this MISRA rule. */
  /* MISRA2012_RULE_2_7_JUSTIFICATION: All parameters used in Mcal_SetBitAtomic
   * are used in IMASKLDMST.
   * No other dead code persist is verified by code review.
   * No side effects foreseen by violating this MISRA rule. */
}

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/

#if (MCU_GTM_USED == STD_ON)

/*******************************************************************************
** Traceability     : [cover parentID={1B75FF1A-BC8B-45e2-81C5-5C5BB8BF93AF}] **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Mcu_17_Gtm_lGetIntSource             **
**                    (                                                       **
**                      const uint32 Value,                                   **
**                      const uint8 Index                                     **
**                    )                                                       **
**                                                                            **
** Description      : This function returns the value at the bit position     **
**                    specified by 'Index' in the data 'Value'. Hence the     **
**                    return value can be 0/1                                 **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Concurrency Safe                                        **
**                                                                            **
** Parameters(in)   : Value - Data                                            **
**                    Index - Bit position                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : 0 - Data in Bit position('Index') is 0                  **
**                    1 - Data in Bit position('Index') is 1                  **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Mcu_17_Gtm_lGetIntSource
(
  const uint32 Value,
  const uint8 Index
)
{
  return((uint8)((Value >> Index) & (uint32)GTM_BIT_SET));

}

/*******************************************************************************
** Traceability     : [cover parentID={CCCEA505-39FC-45ca-B57F-41C2E06CEF1E}] **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Mcu_17_Gtm_lGetTimIrqStatus          **
**                    (                                                       **
**                      const uint8 Module,                                   **
**                      const uint8 Channel                                   **
**                    )                                                       **
**                                                                            **
** Description      : This function returns the extracted information         **
**                    containing the status of the interrupt for the input    **
**                    TIM channel. It informs whether the TIM[Module][Channel]**
**                    triggered the interrupt or not. The information is      **
**                    extracted from ICM register corresponding to TIM module **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Concurrency safe                                        **
**                                                                            **
** Parameters(in)   : Module -        TIM Module ID                           **
**                    Channel -       TIM Channel ID                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Extracted information containing the interrupt status   **
**                    of the input TIM channel                                **
**                                                                            **

*******************************************************************************/
LOCAL_INLINE uint8 Mcu_17_Gtm_lGetTimIrqStatus
(
  const uint8 Module,
  const uint8 Channel
)
{
  uint8 IrqStatus;
  uint8 RegPos;
  uint32 RegVal;

  /* Ascertain the position of Interrupt status for the corresponding module
     and channel*/
  RegPos = (uint8)(((Module % (uint8)GTM_TIM_MODULES_IN_ICM_REG) * \
                    (uint8)GTM_CHANNELS_PER_TIM_MODULE) + Channel);

  /* Identify the ICM register corresponding to the Module number */

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  RegVal = (((volatile uint32*)GTM_TIM_ICM_BASE_ADDRESS) \
             [((uint32)Module / (uint32)GTM_TIM_MODULES_IN_ICM_REG)]);

  /* Retrieve the IRQ status of the channel number */
  IrqStatus = (uint8)((RegVal >> RegPos) & (uint32)GTM_GET_TIM_INT_STATUS);
  return(IrqStatus);
}

/*******************************************************************************
** Traceability     : [cover parentID={9D43D95B-1194-431e-A327-1752667C70C1}] **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Mcu_17_Gtm_lGetTomIrqStatus          **
**                    (                                                       **
**                      const uint8 Module,                                   **
**                      const uint8 Channel                                   **
**                    )                                                       **
**                                                                            **
** Description      : This function returns the extracted information         **
**                    containing the status of the interrupt for the input    **
**                    TOM channel. It informs whether the TOM[Module][Channel]**
**                    triggered the interrupt or not. The information is      **
**                    extracted from ICM register corresponding to TOM module **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Concurrency safe                                        **
**                                                                            **
** Parameters(in)   : Module -        TOM Module ID                           **
**                    Channel -       TOM Channel ID                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Extracted information containing the interrupt status   **
**                    of the input TOM channel                                **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Mcu_17_Gtm_lGetTomIrqStatus
(
  const uint8 Module,
  const uint8 Channel
)
{
  uint8 RegPos;
  uint8 IrqStatus;
  uint32 RegVal;

  /* Ascertain the position of Interrupt status for the corresponding module
     and channel*/
  RegPos = (uint8)(((Module % (uint8)GTM_TOM_MODULES_IN_ICM_REG) * \
                    (uint8)GTM_CHANNELS_PER_TOM_MODULE) + Channel);

  /* Identify the ICM register corresponding to the Module number */

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  RegVal = (((volatile uint32*)GTM_TOM_ICM_BASE_ADDRESS) \
             [((uint32)Module / (uint32)GTM_TOM_MODULES_IN_ICM_REG)]);


  /* Retrieve the IRQ status of the channel number and the next channel */
  IrqStatus = (uint8)((RegVal >> RegPos) & (uint32)GTM_GET_TOM_INT_STATUS);
  return(IrqStatus);
}

/*******************************************************************************
** Traceability     : [cover parentID={33C167B3-9A22-45c6-BA4A-D8C408AFA024}] **
**                                                                            **
** Syntax           : LOCAL_INLINE uint8 Mcu_17_Gtm_lGetAtomIrqStatus         **
**                    (                                                       **
**                      const uint8 Module,                                   **
**                      const uint8 Channel                                   **
**                    )                                                       **
**                                                                            **
** Description      :This function returns the extracted information          **
**                   containing the status of the interrupt for the input     **
**                   ATOM channel.It informs whether the ATOM[Module][Channel]**
**                   triggered the interrupt or not. The information is       **
**                   extracted from ICM register corresponding to TOM module  **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Concurrency safe                                        **
**                                                                            **
** Parameters(in)   : Module -        ATOM Module ID                          **
**                    Channel -       ATOM Channel ID                         **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Extracted information containing the interrupt status   **
**                    of the input ATOM channel                               **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE uint8 Mcu_17_Gtm_lGetAtomIrqStatus
(
  const uint8 Module,
  const uint8 Channel
)
{
  uint8 RegPos;
  uint8 IrqStatus;
  uint32 RegVal;

  /* Ascertain the position of Interrupt status for the corresponding module
     and channel*/
  RegPos = (uint8)(((Module % (uint8)GTM_ATOM_MODULES_IN_ICM_REG) * \
                    (uint8)GTM_CHANNELS_PER_ATOM_MODULE) + Channel);

  /* Identify the ICM register corresponding to the Module number */

  /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
   * by violating this MISRA rule, as the pointer to the object type
   * it is getting cast into is a known type . */
  RegVal = (((volatile uint32*)GTM_ATOM_ICM_BASE_ADDRESS) \
             [((uint32)Module / (uint32)GTM_ATOM_MODULES_IN_ICM_REG)]);


  /* Retrieve the IRQ status of the channel number and the next channel */
  IrqStatus = (uint8)((RegVal >> RegPos) & (uint32)GTM_GET_ATOM_INT_STATUS);
  return(IrqStatus);
}

/*******************************************************************************
** Traceability     : [cover parentID={FF289172-274F-4bf7-8A8C-2D88E96547DC}] **
**                                                                            **
** Syntax           : LOCAL_INLINE uint32* Mcu_17_lGetLockAddress             **
**                    (                                                       **
**                      const uint8 Module,                                   **
**                      const uint8 Index,                                    **
**                      const Mcu_17_Gtm_TimerOutType TimerType               **
**                    )                                                       **
**                                                                            **
** Description      :                                                         **
**                                                                            **
** Service ID       :                                                         **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other channels                            **
**                                                                            **
** Parameters(in)   : ConfigPtr - Ccu6 Timer channel initialization contents  **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*******************************************************************************/
LOCAL_INLINE uint32* Mcu_17_lGetLockAddress
(
  const uint8 Module,
  const uint8 Index,
  const Mcu_17_Gtm_TimerOutType TimerType
)
{
  uint32* LockAddress;

  if (TimerType == MCU_GTM_TIMER_TOM)
  {
    LockAddress = &Mcu_17_Tgc_LockAddress[Module][Index];
  }
  else
  {
    LockAddress = &Mcu_17_Agc_LockAddress[Module];
  }

  return LockAddress;
}

#endif
/* End of #if (MCU_GTM_USED == STD_ON) */

#define MCU_17_TIMERIP_STOP_SEC_CODE_ASIL_B_GLOBAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header included as per Autosar
  guidelines. */
#include "Mcu_MemMap.h"

/*******************************************************************************
**                        ISR Function Declarations                           **
*******************************************************************************/
#define MCU_17_TIMERIP_START_SEC_CODE_FAST_ASIL_B_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Mcu_MemMap.h"

#if (MCU_GTM_USED == STD_ON)
/*******************************************************************************
** Traceability     : [cover parentID={45C502CC-32D6-4510-BDC0-6E2C108D1400}] **
**                                                                            **
** Syntax           : void Mcu_17_Gtm_TomChannelIsr                           **
**                    (                                                       **
**                      const uint8 Module,                                   **
**                      const uint8 Channel                                   **
**                    )                                                       **
**                                                                            **
** Description      : This is the interrupt service routine of a TOM channel  **
**                    and is invoked by the interrupt frame installed in the  **
**                    interrupt vector table. It identifies the user of the   **
**                    specified channel from the TOM channel user data table  **
**                    and invokes a known call back function associated       **
**                    with the user.                                          **
**                                                                            **
** Service ID       : 0x92                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different channels                        **
**                                                                            **
** Parameters(in)   : Module  - TOM Module ID                                 **
**                    Channel - TOM Channel ID                                **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
/*[cover parentID={A4DC22AB-1EE4-4ab3-BEC6-20764D46A826}][/cover]*/
void Mcu_17_Gtm_TomChannelIsr
(
  const uint8 Module,
  const uint8 Channel
)
{
  Ifx_GTM_TOM_CH *TomChannelRegPtr;
  uint32 TomChannelNotifySts;
  uint32 TomChannelEnSts;
  uint32 UserData;
  uint32 IcmStatus;
  uint32 IrqStatus;
  uint8  UserId;
  uint32  LogChId;
  uint8  BitPos;
  uint8  ChanIndex;

  /* Get the Irq Group status to detect the channel that has
  triggered the ISR*/
  /* [cover parentID={316310BD-E78B-4630-B6B9-2C3FB7621CA6}]
   * Get interrupt status of TOM channel x and x+1
   * [/cover] */
  IcmStatus = Mcu_17_Gtm_lGetTomIrqStatus(Module, Channel);

  /* Did the input TOM channel 'x' or 'x+1' trigger the interrupt */
  /* [cover parentID={6E0518BC-6822-48f3-8DB1-AC63B7E6F334}]
   * Did any channel trigger an interrupt
   * [/cover] */
  if(IcmStatus != GTM_BIT_CLEAR)
  {
    /* Initialize ChanIndex to the number of channels mapped to one
    TOM Interrupt Node */
    ChanIndex = GTM_TOM_CHAN_PER_SRN;

    /* Loop through both the channels */
    /* [cover parentID={23001D67-DA94-43fa-8B97-F9678409B56F}]
     * Is channel index greater than zero [/cover]*/
    do
    {
      ChanIndex--;
      /* Check which the channel has triggered interrupt
                                        ( 2 TOM channel shares the same SRN)*/
      /*[cover parentID={6E0518BC-6822-48f3-8DB1-AC63B7E6F334}]Interrupt
       * source check[/cover]*/
      /* [cover parentID={46EE2617-270F-4274-9A90-1A460163A831}]
       * Get interrupt source
       * [/cover] */
      if(Mcu_17_Gtm_lGetIntSource(IcmStatus, ChanIndex) == GTM_BIT_SET)
      {
        /* Get the Channel Register Pointer */

        /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects
         * foreseen by violating this MISRA rule, as the pointer to the
         * object type it is getting cast into is a known type . */
        /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects
         * foreseen by violating this MISRA rule. */
        TomChannelRegPtr = GTM_TOM_CH_POINTER(Module, (Channel + ChanIndex));

        TomChannelNotifySts = TomChannelRegPtr->IRQ.NOTIFY.U;
        TomChannelEnSts     = TomChannelRegPtr->IRQ.EN.U;

        /* Mask the interrupts */
        IrqStatus = (uint32)(TomChannelNotifySts & TomChannelEnSts);

        /* Check is the interrupt spurious */
        /* [cover parentID={593033E6-AB2A-4527-8484-31066A74817D}]
         * Check is the interrupt spurious
         * [/cover] */
        if (IrqStatus > 0x0U)
        {
          /* Get the interrupt flag which was set */
          /* Note: The interrupts are serviced in descending order of bits */
          BitPos = MCU_GET_SETBIT_POS(IrqStatus);

          /* Clear the pending interrupt associated with TOM channel register */
          /*[cover parentID={53317525-F445-40cc-A345-9EBFF8EE1B3F}][/cover]*/
          TomChannelRegPtr->IRQ.NOTIFY.U = (uint32)0x1U << BitPos;

          /* Save the interrupt status, to be used by TOM user */
          IrqStatus = (uint32)0x1U << BitPos;

          /* Retrieve the user information from TOM channel user data table */
          UserData = Mcu_17_Gtm_TomChUserData[Module][Channel + ChanIndex];
          UserId =  (uint8)(UserData & (uint32)GTM_USER_ID_MSK);
          LogChId = ((UserData >> (uint32)GTM_LOG_CH_ID_BITPOS) & \
                            (uint32)GTM_LOG_CH_ID_MSK);

          /* Is UserId information a valid one */
          /* [cover parentID={CC5DB789-B654-4e09-8BCC-CAA5A675C638}]
           * Validity check for User Id
           * [/cover] */
          if((UserId != (uint8)TIMER_IP_NO_USER) && \
              (UserId <= (uint8)TIMER_NO_OF_CALLBACK))
          {
            /* Does the valid User ID have a callback function */
            /* [cover parentID={D8B9848C-17AF-4e30-B7AF-A9AA46F09171}]
             * User Id has a call back function or not
             * [/cover] */
            if(NULL_PTR != \
                Mcu_17_Timer_DrivFuncCallbackLst[(UserId - (uint8)GTM_BIT_SET)])
            {
              /* [cover parentID={ECD5DC5A-48CE-41a4-9948-BB3B1E0ED0B2}]
               * Invoke callback notification for identified User Id
               * [/cover] */
              Mcu_17_Timer_DrivFuncCallbackLst[(UserId - (uint8)GTM_BIT_SET)]\
              (LogChId, IrqStatus);
            }
          }
        }
        /* [cover parentID={CCCDB09C-4441-4fe2-A10B-BAA200235174}]
         * If Safety is enabled
         * [/cover] */
        #if (MCU_SAFETY_ENABLE == STD_ON)
        else
        {
          /* Report to Safety Error for spurious interrupt */
          /* [cover parentID={FC2927EF-A452-42d0-AB00-1D98C38C43AC}]
           * Report to Safety Error for spurious interrupt
           * [/cover] */
          Mcal_ReportSafetyError((uint16)MCU_MODULE_ID, MCU_MODULE_INSTANCE, \
                                 MCU_TOM_CH_ISR, MCU_E_INVALID_ISR);
        }
        #endif
      }

      /* Span through both the channels which are mapped to this node */
    } while(ChanIndex > (uint8)GTM_BIT_CLEAR);
    /*[/cover]*/
  }
  #if (MCU_SAFETY_ENABLE == STD_ON)
  else
  {
    /* Report to Safety Error for spurious interrupt */
    /* [cover parentID={FC2927EF-A452-42d0-AB00-1D98C38C43AC}]
     * Report to Safety Error for spurious interrupt
     * [/cover] */
    Mcal_ReportSafetyError((uint16)MCU_MODULE_ID, MCU_MODULE_INSTANCE, \
                           MCU_TOM_CH_ISR, MCU_E_INVALID_ISR);
  }
  #endif
}

/*******************************************************************************
** Traceability     : [cover parentID={D878FD35-8DBC-4fa4-8F08-86927352A157}] **
**                                                                            **
** Syntax           : void Mcu_17_Gtm_AtomChannelIsr                          **
**                    (                                                       **
**                      const uint8 Module,                                   **
**                      const uint8 Channel                                   **
**                    )                                                       **
**                                                                            **
** Description      : This is the interrupt service routine of a ATOM channel **
**                    and is invoked by the interrupt frame installed in the  **
**                    interrupt vector table. It identifies the user of the   **
**                    specified channel from the ATOM channel user data table **
**                    and invokes a known call back function associated       **
**                    with the user.                                          **
**                                                                            **
** Service ID       : 0x93                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different channels                        **
**                                                                            **
** Parameters(in)   : Module  - ATOM Module ID                                **
**                    Channel - ATOM Channel ID                               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
/*[cover parentID={A4DC22AB-1EE4-4ab3-BEC6-20764D46A826}][/cover]*/
void Mcu_17_Gtm_AtomChannelIsr
(
  const uint8 Module,
  const uint8 Channel
)
{
  Ifx_GTM_ATOM_CH *AtomChannelRegPtr;
  uint32 AtomChannelNotifySts;
  uint32 AtomChannelEnSts;
  uint32 UserData;
  uint32 IcmStatus;
  uint32 IrqStatus;
  uint8  UserId;
  uint32 LogChId;
  uint8  BitPos;
  uint8  ChanIndex;

  /* Get the Irq Group status to detect the channel that has
  triggered the ISR*/
  /* [cover parentID={52187D6C-B174-427e-945B-5818C22B16CF}]
   * Obtain Interrupt status of ATOM channel x and x+1
   * [/cover] */
  IcmStatus = Mcu_17_Gtm_lGetAtomIrqStatus(Module, Channel);

  /* Did the input ATOM channel 'x' or 'x+1' trigger the interrupt */
  /* [cover parentID={D608184E-6D0D-4d50-AADA-C2502FC8CA04}]
   * Did any one of the channel triggered an interrupt
   * [/cover] */
  if(IcmStatus != GTM_BIT_CLEAR)
  {
    /* Initialize ChanIndex to the number of channels mapped to one
    ATOM Interrupt Node */
    ChanIndex = GTM_ATOM_CHAN_PER_SRN;

    /* Loop through both the channels */
    /* [cover parentID={2C7D422E-C0E9-466f-BEB8-D63128BFB0F4}] [/cover]
     * Is Channel Index greater than zero*/
    do
    {
      ChanIndex--;
      /* Check which the channel has triggered interrupt
       *  ( 2 ATOM channel shares the same SRN)*/
      /*[cover parentID={E6A03A68-6F1D-4d31-B722-A9D7349BA1B3}]Interrupt
      source check[/cover]*/
      /* [cover parentID={61C00EAF-14B7-47b3-9D84-2E9AF2DD30DC}]
       * Get interrupt source
       * [/cover] */
      if(Mcu_17_Gtm_lGetIntSource(IcmStatus, ChanIndex) == \
          (uint8)GTM_BIT_SET)
      {
        /* Get the Channel Register Pointer */

        /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects
         * foreseen by violating this MISRA rule, as the pointer to the
         * object type it is getting cast into is a known type . */
        /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects
         * foreseen by violating this MISRA rule. */
        AtomChannelRegPtr = GTM_ATOM_CH_POINTER(Module, (Channel + ChanIndex));

        AtomChannelNotifySts = AtomChannelRegPtr->IRQ.NOTIFY.U;
        AtomChannelEnSts     = AtomChannelRegPtr->IRQ.EN.U;

        /* Mask the interrupts */
        IrqStatus = (uint32)(AtomChannelNotifySts & AtomChannelEnSts);

        /* Check is spurious interrupt */
        /* [cover parentID={E6A03A68-6F1D-4d31-B722-A9D7349BA1B3}]
         * Check is spurious interrupt
         * [/cover] */
        if (IrqStatus > 0x0U)
        {
          /* Get the interrupt flag which was set */
          /* Note: The interrupts are serviced in descending order of bits */
          BitPos = MCU_GET_SETBIT_POS(IrqStatus);

          /* Clear any pending interrupts associated with TOM channel */
          /* [cover parentID={FA18E39A-E9DE-4834-8A3B-F7510ABED7E2}][/cover]*/
          AtomChannelRegPtr->IRQ.NOTIFY.U = (uint32)0x1U << BitPos;

          /* Save the interrupt status, to be used by TOM user */
          IrqStatus = (uint32)0x1U << BitPos;

          /* Retrieve the user information from ATOM channel user data table */
          UserData = Mcu_17_Gtm_AtomChUserData[Module][Channel + ChanIndex];
          UserId =   (uint8)(UserData & (uint32)GTM_USER_ID_MSK);
          LogChId =  ((UserData >> (uint32)GTM_LOG_CH_ID_BITPOS) & \
                             (uint32)GTM_LOG_CH_ID_MSK);

          /* Is UserId information a valid one */
          /* [cover parentID={235B8205-81CB-492e-8B06-5808845CDD92}]
           * Validity Check of User Id
           * [/cover] */
          if((UserId != (uint8)TIMER_IP_NO_USER) && \
              (UserId <= (uint8)TIMER_NO_OF_CALLBACK))
          {
            /* Does the valid User ID have a callback function */
            /* [cover parentID={48E721A2-F42A-412a-B820-7D8899965953}]
             * User Id has a callback function or not
             * [/cover] */
            if(Mcu_17_Timer_DrivFuncCallbackLst[(UserId - (uint8)GTM_BIT_SET)] \
                != NULL_PTR)
            {
              /* [cover parentID={45DD18F1-C3FF-4984-B300-D2CE5011A96F}]
               * Invoke Callback notification for identified User Id
               * [/cover] */
              Mcu_17_Timer_DrivFuncCallbackLst[(UserId - (uint8)GTM_BIT_SET)]\
              (LogChId, IrqStatus);
            }
          }
        }
        /* [cover parentID={5AD8F212-EA88-4ebd-83CB-482BA5B0A771}]
         * If Safety is enabled
         * [/cover] */
        #if (MCU_SAFETY_ENABLE == STD_ON)
        else
        {
          /* Report to Safety Error for spurious interrupt */
          /* [cover parentID={A87A9B23-D389-4635-9EC5-379244ADD1DE}]
           * Report to Safety Error for spurious interrupt
           * [/cover] */
          Mcal_ReportSafetyError((uint16)MCU_MODULE_ID, MCU_MODULE_INSTANCE, \
                                 MCU_ATOM_CH_ISR, MCU_E_INVALID_ISR);
        }
        #endif
      }
      /* Span through both the channels which are mapped to this node */
    } while(ChanIndex > (uint8)GTM_BIT_CLEAR);
    /*[/cover] */
  }
  #if (MCU_SAFETY_ENABLE == STD_ON)
  else
  {
    /* Report to Safety Error for spurious interrupt */
    /* [cover parentID={A87A9B23-D389-4635-9EC5-379244ADD1DE}]
     * Report to Safety Error for spurious interrupt
     * [/cover] */
    Mcal_ReportSafetyError((uint16)MCU_MODULE_ID, MCU_MODULE_INSTANCE, \
                           MCU_ATOM_CH_ISR, MCU_E_INVALID_ISR);
  }
  #endif
}

/*******************************************************************************
** Traceability     : [cover parentID={7FAAF2E5-0A41-4e28-B65E-B426810B9F49}] **
**                                                                            **
** Syntax           : void Mcu_17_Gtm_TimChannelIsr                           **
**                    (                                                       **
**                      const uint8 Module,                                   **
**                      const uint8 Channel                                   **
**                    )                                                       **
**                                                                            **
** Description      : This is the interrupt service routine of a TIM channel  **
**                    and is invoked by the interrupt frame installed in the  **
**                    interrupt vector table. It identifies the user of the   **
**                    specified channel from the TIM channel user data table  **
**                    and invokes a known call back function associated       **
**                    with the user.                                          **
**                                                                            **
** Service ID       : 0x94                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different channels                        **
**                                                                            **
** Parameters(in)   : Module  - TIM Module ID                                 **
**                    Channel - TIM Channel ID                                **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
*******************************************************************************/
void Mcu_17_Gtm_TimChannelIsr
(
  const uint8 Module,
  const uint8 Channel
)
{
  Ifx_GTM_TIM_CH *TimChannelRegPtr;
  uint32 UserData;
  uint32 IrqStatus;
  uint32  LogChId;
  uint8  UserId;

  /* Did the input TIM channel trigger the interrupt */
  /*[cover parentID={98E438AC-CC81-4b50-AECF-58A49BE1CC98}]Interrupt
  source check[/cover]*/
  /* [cover parentID={757ED0C2-4F6D-4457-BDE3-53E9CC7D5C27}]
   * Get the interrupt status of TIM channel
   * [/cover] */
  if(Mcu_17_Gtm_lGetTimIrqStatus(Module, Channel) == (uint8)GTM_BIT_SET)
  {
    /* MISRA2012_RULE_11_3_JUSTIFICATION: SFR access. No side effects foreseen
     * by violating this MISRA rule, as the pointer to the object type
     * it is getting cast into is a known type . */
    /* MISRA2012_RULE_11_5_JUSTIFICATION: SFR access. No side effects foreseen
     * by violating this MISRA rule. */
    TimChannelRegPtr = GTM_TIM_CH_POINTER(Module, Channel);

    /* Save the interrupt status, to be used by TIM user */
    IrqStatus = TimChannelRegPtr->IRQ.NOTIFY.U;
    IrqStatus &= TimChannelRegPtr->IRQ.EN.U;

    /* Clear any TIM channel pending interrupts */
    /* [cover parentID={591B6888-2415-42f1-9957-E149AECB280F}][/cover] */
    TimChannelRegPtr->IRQ.NOTIFY.U = TimChannelRegPtr->IRQ.EN.U;

    /* Check for spurious interrupt */
    /* [cover parentID={98E438AC-CC81-4b50-AECF-58A49BE1CC98}]
       * Did TIM channel trigger an interrupt
       * [/cover] */
    if(IrqStatus > GTM_BIT_CLEAR)
    {
      /* Retrieve the user information from TIM channel user data table */
      UserData = Mcu_17_Gtm_TimChUserData[Module][Channel];
      UserId   = (uint8)(UserData & (uint32)GTM_USER_ID_MSK);
      LogChId  = ((UserData >> (uint32)GTM_LOG_CH_ID_BITPOS) & \
                         (uint32)GTM_LOG_CH_ID_MSK);

      /* Is UserId information a valid one */
      /* [cover parentID={76D17BA3-AB45-4b29-9806-18CE1941425A}]
         * Validity check for User Id
         * [/cover] */
      if((UserId != (uint8)TIMER_IP_NO_USER) && \
          (UserId <= (uint8)TIMER_NO_OF_CALLBACK))
      {
        /* Does the valid User ID have a callback function */
        /* [cover parentID={8345B39E-8218-4506-B5D6-35B7DA5CBC06}]
         * Check if Function call back is available
         * [/cover] */
        if( Mcu_17_Timer_DrivFuncCallbackLst[(UserId - (uint8)GTM_BIT_SET)] != \
            NULL_PTR)
        {
          /* [cover parentID={7F1F8555-BD05-4dc8-8A0A-033634743797}]
           * Invoke callback notification for identified User Id
           * [/cover] */
          Mcu_17_Timer_DrivFuncCallbackLst[(UserId - (uint8)GTM_BIT_SET)]\
          (LogChId, IrqStatus);
        }
      }
    }
    /* [cover parentID={EAFF7BD4-D5A2-4c16-9E0E-A91229FE09F8}]
       * If Safety is enabled
       * [/cover] */
    #if (MCU_SAFETY_ENABLE == STD_ON)
    else
    {
      /* Report to Safety Error for spurious interrupt */
      /* [cover parentID={3E1F2995-1D70-4bd3-87AB-A59BB191A68E}]
         * Report Safety Error for spurious interrupt
         * [/cover] */
      Mcal_ReportSafetyError((uint16)MCU_MODULE_ID, MCU_MODULE_INSTANCE, \
                             MCU_TIM_CH_ISR, MCU_E_INVALID_ISR);
    }
    #endif
  }
  #if (MCU_SAFETY_ENABLE == STD_ON)
  else
  {
    /* Report to Safety Error for spurious interrupt */
    /* [cover parentID={3E1F2995-1D70-4bd3-87AB-A59BB191A68E}]
     * Report to Safety Error for spurious interrupt
     * [/cover] */
    Mcal_ReportSafetyError((uint16)MCU_MODULE_ID, MCU_MODULE_INSTANCE, \
                           MCU_TIM_CH_ISR, MCU_E_INVALID_ISR);
  }
  #endif

}

#endif
/* End of #if (MCU_GTM_USED == STD_ON) */

/*******************************************************************************
** Traceability     : [cover parentID={5B0BA918-7DB6-48dc-A17E-E8BB0825C8BF}] **
**                                                                            **
** Syntax           : void  Mcu_17_Ccu6_ChannelIsr                            **
**                    (                                                       **
**                        const Mcu_17_Ccu6_KernelIdentifierType Kernel       **
**                        const Mcu_17_Ccu6_ComparatorType Comparator         **
**                    )                                                       **
**                                                                            **
** Description      : This is the interrupt service routine of a CCU6 timer   **
**                    channel and is invoked by the interrupt frame installed **
**                    in the interrupt vector table. It identifies the user of**
**                    the specified channel and invokes a known call back     **
**                    function associated with the user.                      **
**                                                                            **
** Service ID       : 0x95                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different channels                        **
**                                                                            **
** Parameters(in)   : Kernel     - CCU6 Kernel                                **
**                    Comparator - CCU6 Comparator type                       **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*******************************************************************************/
void Mcu_17_Ccu6_ChannelIsr
(
  const Mcu_17_Ccu6_KernelIdentifierType Kernel,
  const Mcu_17_Ccu6_ComparatorType Comparator
)
{
  uint32 UserData;
  uint32 KernelIntEn   = CCU6_BIT_CLEAR;
  uint32 KernelIntStat = CCU6_BIT_CLEAR;
  uint32 IrqStatus     = CCU6_BIT_CLEAR;
  uint32 StatusFlags   = CCU6_BIT_CLEAR;
  uint32 LogChId;
  uint8  UserId;

  /* Based on the comparator type, clear the interrupt status flags */
  /* [cover parentID={F1568650-DA09-431f-914B-562B7BF95540}]
   * If Comparator selected is Comparator 03
   * [/cover] */
  if(Comparator == MCU_CCU6_COMPARATOR_CCU63)
  {
    KernelIntEn =  (Mcu_17_Ccu6_Kernel[Kernel]->IEN.U) & CCU6_T13_INT_PM_CM_MSK;
    KernelIntStat = ((Mcu_17_Ccu6_Kernel[Kernel]->IS.U) & \
                     CCU6_T13_INT_PM_CM_MSK);
    IrqStatus = KernelIntEn & KernelIntStat;
  }
  else
  {
    KernelIntEn =  ((Mcu_17_Ccu6_Kernel[Kernel]->IEN.U) &
                    (CCU6_T12_INT_PM_MSK | ((uint32)CCU6_T12_INT_CC6x_MSK << \
                    ((uint32)Comparator * CCU6_COMPARATOR_BITLEN))));

    KernelIntStat = ((Mcu_17_Ccu6_Kernel[Kernel]->IS.U) &
                     (CCU6_T12_INT_PM_MSK | ((uint32)CCU6_T12_INT_CC6x_MSK << \
                         ((uint32)Comparator * CCU6_COMPARATOR_BITLEN))));

    IrqStatus = KernelIntEn & KernelIntStat;
  }

  /* Did the input Comparator trigger the interrupt */
  /*[cover parentID={ED7F742B-FA86-48b3-B1EE-E1AA3B080F87}]Interrupt source
  check[/cover]*/
  /* [cover parentID={ED7F742B-FA86-48b3-B1EE-E1AA3B080F87}]
   * In Case of an Interrupt
   * [/cover] */
  if(IrqStatus > (uint8)CCU6_BIT_CLEAR)
  {
    /* Clear any channel pending interrupts */
    Mcu_17_Ccu6_Kernel[Kernel]->ISR.U = IrqStatus;

    /* Fetch the status bits */
    StatusFlags = (IrqStatus >> \
                   ((uint32)Comparator * CCU6_COMPARATOR_BITLEN)) & \
                  CCU6_T12_INT_CC6x_MSK;
    StatusFlags |= ((IrqStatus & \
                     (CCU6_T13_INT_PM_CM_MSK | CCU6_T12_INT_PM_MSK)) >> \
                    CCU6_ISR_STS_LEN);

    /* Retrieve the user information from CCU6 channel user data table */
    UserData = Mcu_17_Ccu6_ChUserData[Kernel][Comparator];
    UserId   = (uint8)(UserData & (uint32)CCU6_USER_ID_MSK);
    LogChId  = ((UserData >> (uint32)CCU6_LOG_CH_ID_BITPOS) & \
                       (uint32)CCU6_LOG_CH_ID_MSK);

    /* Is UserId information a valid one */
    /* [cover parentID={C39B5003-5D7B-45ae-B2AD-076DB5CA5AAD}]
       * Check for Valid User Id
       * [/cover] */
    if((UserId != (uint8)TIMER_IP_NO_USER) && \
        (UserId <= (uint8)TIMER_NO_OF_CALLBACK))
    {
      /* Does the valid User ID have a callback function */
      /* [cover parentID={A4DFB038-64E3-4729-A876-2D47015B750A}]
       * Check if User Id has Call back function
       * [/cover] */
      if( Mcu_17_Timer_DrivFuncCallbackLst[(UserId - (uint8)0x1U)] != \
          NULL_PTR)
      {
        /* [cover parentID={207BCCF0-3205-49ac-8C7A-36C0923C63FF}]
         * Invoke callback notification for identified User Id
         * [/cover] */
        Mcu_17_Timer_DrivFuncCallbackLst[(UserId - (uint8)0x1U)]\
        (LogChId, StatusFlags);
      }
    }
  }
  /* [cover parentID={75676F48-46B6-4693-A1CC-7D38A0B99E88}]
   * If Safety is Enabled
   * [/cover] */
  #if (MCU_SAFETY_ENABLE == STD_ON)
  else
  {
    /* Report to Safety Error for spurious interrupt */
    /* [cover parentID={8813CC58-9998-44a8-A263-13529B453E00}]
       * Report Safety error for Spurious interrupt
       * [/cover] */
    Mcal_ReportSafetyError((uint16)MCU_MODULE_ID, MCU_MODULE_INSTANCE, \
                           MCU_CCU6_CH_ISR, MCU_E_INVALID_ISR);
  }
  #endif
}

/*******************************************************************************
** Traceability     : [cover parentID={54E3482A-2FEF-4e15-92F7-F7331D2D4D33}] **
**                                                                            **
** Syntax           : void  Mcu_17_Gpt12_ChannelIsr                           **
**                    (                                                       **
**                        const Mcu_17_Gpt12_TimerChIdentifierType Timer      **
**                    )                                                       **
**                                                                            **
** Description      : This is the interrupt service routine of a GPT12        **
**                    timer channel and is invoked by the interrupt frame     **
**                    installed in the interrupt vector table. It identifies  **
**                    the user of the specified channel and invokes a known   **
**                    call back function associated with the user.            **
**                                                                            **
** Service ID       : 0x96                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different channels                        **
**                                                                            **
** Parameters(in)   : Timer  - GPT12 timer                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*******************************************************************************/
void Mcu_17_Gpt12_ChannelIsr
(
  const Mcu_17_Gpt12_TimerChIdentifierType Timer
)
{
  uint32 UserData;
  uint8  UserId;
  uint32 LogChId;

  /* Retrieve the user information from GPT12 channel user data table */
  UserData = Mcu_17_Gpt12_ChUserData[Timer];
  UserId   = (uint8)(UserData & (uint32)GPT12_USER_ID_MSK);
  LogChId  = ((UserData >> (uint32)GPT12_LOG_CH_ID_BITPOS) & \
                     (uint32)GPT12_LOG_CH_ID_MSK);

  /* Is UserId information a valid one */
  /* [cover parentID={54871D22-9726-43fa-9C20-77683569F4F7}]
   * Validity check for User Id
   * [/cover] */
  if((UserId != (uint8)TIMER_IP_NO_USER) && \
      (UserId <= (uint8)TIMER_NO_OF_CALLBACK))
  {
    /* Does the valid User ID have a callback function */
    /* [cover parentID={32627304-EC53-41ce-BB89-997C01D1D907}]
     * User Id has function callback or not
     * [/cover] */
    if( Mcu_17_Timer_DrivFuncCallbackLst[(UserId - (uint8)GPT12_BIT_SET)] != \
        NULL_PTR)
    {
      /* GPT12 has no status flags, hence onus lies on the user to verify the
         validity of Isr */
      /* [cover parentID={423561A7-11F3-4928-9790-2E4E01A52DBA}]
       * Invoke callback notification for identified User Id
       * [/cover] */
      Mcu_17_Timer_DrivFuncCallbackLst[(UserId - (uint8)GPT12_BIT_SET)]\
      (LogChId, 0U);
    }
  }
}

/*******************************************************************************
** Traceability     : [cover parentID={8F77E3BC-2DDA-4966-AC4A-76B0D112B309}] **
**                                                                            **
** Syntax           : void  Mcu_17_Stm_CompareMatchIsr                        **
**                    (                                                       **
**                        const Mcu_17_Stm_StmIdentifierType StmTimerId       **
**                        const Mcu_17_Stm_StmCmpIdentifierType StmCmpId      **
**                    )                                                       **
**                                                                            **
** Description      : This is the interrupt service routine of a STM          **
**                    timer and is invoked by the interrupt frame             **
**                    installed in the interrupt vector table. It identifies  **
**                    the user of the specified STM timer and invokes a known **
**                    call back function associated with the user.            **
**                                                                            **
** Service ID       : 0x97                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for other STM Timers                          **
**                                                                            **
** Parameters(in)   : StmTimerId - STM Timer channel id                       **
**                  : StmCmpId   - STM Comparator id                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*******************************************************************************/
void Mcu_17_Stm_CompareMatchIsr
(
  const Mcu_17_Stm_StmIdentifierType StmTimerId,
  const Mcu_17_Stm_StmCmpIdentifierType StmCmpId
)
{
  uint32 IcrRegVal;
  uint8  UserId;
  uint8  CmpEnSts;
  uint8  IrqStatus;
  uint8  StmCmpEnBit;
  uint8  StmCmpIRBit;
  uint8  StmCmpIRRBit;

  /* Read the ICR register of the STM Timer */
  IcrRegVal = Mcu_17_Stm[StmTimerId]->ICR.U;

  /* Set the IR and IRR bit position based on the comparator */
  if (StmCmpId == (uint8)STM_CMP0)
  {
    /* CMP 0*/
    StmCmpIRBit  = IFX_STM_ICR_CMP0IR_OFF;
    StmCmpIRRBit = IFX_STM_ISCR_CMP0IRR_OFF;
    StmCmpEnBit  = IFX_STM_ICR_CMP0EN_OFF;

    /* Retrieve the user information from STM Timer user data table */
    UserId = (uint8)((Mcu_17_Stm_ChUserData[StmTimerId] & 0xFF00U) >> 0x8U);
  }
  else
  {
    /* CMP 1 */
    StmCmpIRBit  = IFX_STM_ICR_CMP1IR_OFF;
    StmCmpIRRBit = IFX_STM_ISCR_CMP1IRR_OFF;
    StmCmpEnBit  = IFX_STM_ICR_CMP1EN_OFF;

    /* Retrieve the user information from STM Timer user data table */
    UserId = (uint8)((Mcu_17_Stm_ChUserData[StmTimerId] & 0xFF000000U) >> 0x18U);
  }

  /* Check the interrupt source */
  /* [cover parentID={D4E62054-B3C9-419f-86FB-7B5F33C7A5B1}]
   * Identify the source of interrupt
   * [/cover] */
  IrqStatus = (uint8)Mcal_GetBitAtomic(IcrRegVal, StmCmpIRBit, \
                                       STM_ICR_CMPIR_LEN);
  CmpEnSts  = (uint8)Mcal_GetBitAtomic(IcrRegVal, StmCmpEnBit, \
                                       STM_ICR_CMPEN_LEN);

  /* [cover parentID={3F2A02E7-B7C2-40ed-A14D-61D661E59BE3}]
   * Is interrupt set and corresponding comparator is enabled
   * [/cover] */
  if ((IrqStatus == 0x1U) && (CmpEnSts == 0x1U))
  {
    /* Clear the interrupt */
    /*[cover parentID={05647AE6-1DD8-4e0e-B0B2-90942B6CA907}][/cover]*/
    Mcal_SetBitAtomic((&Mcu_17_Stm[StmTimerId]->ISCR.U), \
                      StmCmpIRRBit, \
                      STM_ISCR_CMPIRR_LEN, \
                      0x1U);

    /* Is UserId information a valid one */
    /* [cover parentID={E69D3667-DE49-4401-AC59-24512ECA2976}]
       * Validity Check of User Id
       * [/cover] */
    if((UserId != (uint8)TIMER_IP_NO_USER) && \
        (UserId <= (uint8)TIMER_NO_OF_CALLBACK))
    {
      /* Does the valid User ID have a callback function */
      /* [cover parentID={937CEC13-4989-4227-A0FC-3269A0DB491B}]
       * User Id has a callback function or not
       * [/cover] */
      if( Mcu_17_Timer_DrivFuncCallbackLst[(UserId - (uint8)0x1U)] != \
          NULL_PTR)
      {
        /*[cover parentID={BB08545D-ADB1-4dfa-B027-8B3081499049}][/cover]*/
        Mcu_17_Timer_DrivFuncCallbackLst[(UserId - (uint8)0x1U)]\
        (StmTimerId, StmCmpId);
      }
    }
  }
  /* [cover parentID={B3BBA413-ED3E-4d72-AC84-1B923602BECD}]
   * If Safety is Enabled
   * [/cover] */
  #if (MCU_SAFETY_ENABLE == STD_ON)
  else
  {
    /* Report to Safety Error for spurious interrupt */
    /* [cover parentID={8295FDBB-9095-4e87-A8CC-72F38F7F2D59}]
       * Report safety error for spurious interrupt
       * [/cover] */
    Mcal_ReportSafetyError((uint16)MCU_MODULE_ID, MCU_MODULE_INSTANCE, \
                           MCU_STM_COMP_ISR, MCU_E_INVALID_ISR);
  }
  #endif
  /* MISRA2012_RULE_2_2_JUSTIFICATION: All parameters used in Mcal_SetBitAtomic
   * are used in IMASKLDMST.
   * No other dead code persist is verified by code review.
   * No side effects foreseen by violating this MISRA rule. */
}

/*******************************************************************************
** Traceability     : [cover parentID={987225E7-5231-4d28-87AB-770C78860DC0}] **
**                                                                            **
** Syntax           : void  Mcu_17_Eru_GatingIsr                              **
**                    (                                                       **
**                        const Mcu_17_Eru_SrcIdentifierType EruSrcId         **
**                    )                                                       **
**                                                                            **
** Description      : This is the interrupt service routine of Eru and is     **
**                    invoked by the interrupt frame installed in the         **
**                    interrupt vector table. It identifies the user of the   **
**                    specified Eru Channel and invokes a known call back     **
**                    function associated with the user.                      **
**                                                                            **
** Service ID       : 0x98                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant for different channels                        **
**                                                                            **
** Parameters(in)   : EruSrcId - ERU service node which triggered the         **
**                               interrupt                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
*******************************************************************************/
void Mcu_17_Eru_GatingIsr
(
  const Mcu_17_Eru_SrcIdentifierType EruSrcId
)
{
  uint32 EruIgpVal;
  uint32 UserData;
  uint32 IrqStatus;
  uint32 EruEifrMask;
  uint32 EruPdrStatus;
  uint32 LogChId;
  uint8  UserId, UserId1, UserId2;
  #if (MCU_SAFETY_ENABLE == STD_ON)
  uint8  IrqServiceFlag;
  #endif
  uint8  EruIgpPos;
  uint8  EruChannelId;
  uint8  EruChInputUnit;
  uint8  EruChOutputUnit = EruSrcId;

  /* Retrieve the user information from ERU channel user data table */
  UserId1   = (uint8)((Mcu_17_Eru_ChUserData[EruSrcId] & ERU_USER_ID_MSK) >>
                      ERU_USER_ID_POS);

  UserId2   = (uint8)((Mcu_17_Eru_ChUserData[EruSrcId + ERU_OGU_OFFSET] & \
                       ERU_USER_ID_MSK) >> ERU_USER_ID_POS);

  /* Proceed only for valid users */
  /*[cover parentID={8D43F8FD-E6F1-4fb4-928A-761B50A67D53}][/cover]*/
  if ((UserId1 != (uint8)TIMER_IP_NO_USER) || \
      (UserId2 != (uint8)TIMER_IP_NO_USER))
  {
    /* Calculate the EIFR mask from user data of any paired channel */
    EruEifrMask = (uint32)((Mcu_17_Eru_ChUserData[EruSrcId] & ERU_EIFR_MASK) >>
                           ERU_EIFR_OFFSET);

    /*[cover parentID={718D2CD7-FE8F-4b44-BC61-BF863A2A12E0}][/cover]*/
    if ((UserId1 == TIMER_CH_USED_BY_DSADC_DRIVER) || \
        (UserId2 == TIMER_CH_USED_BY_DSADC_DRIVER))
    {
      /* Note: In the case of DSADC, spurious interrupt cannot be checked as the
       * INTFx is not cleared by SW
       */
      if (UserId1 == TIMER_CH_USED_BY_DSADC_DRIVER)
      {
        /* Fetch the OGU ID */
        EruChOutputUnit =(uint8)(Mcu_17_Eru_ChUserData[EruSrcId] & ERU_CH_OFFSET);
      }
      else
      {
        EruChOutputUnit =(uint8)(Mcu_17_Eru_ChUserData[EruSrcId + ERU_OGU_OFFSET]
                                 & ERU_CH_OFFSET);
      }

      /* Read the PDR and skip Clearing of FMR in case of DSADC */
      EruPdrStatus = (uint32)((MODULE_SCU.PDRR.U >> EruChOutputUnit) & \
                                                            ERU_PDRR_PDR_MSK);

      /* Fetch the User data, User Id and Logical channel Id*/
      UserData = Mcu_17_Eru_ChUserData[EruChOutputUnit];
      UserId   = (uint8)((UserData & ERU_USER_ID_MSK) >> ERU_USER_ID_POS);

      /* Retrieve the user information from ERU channel user data table */
      LogChId  = ((UserData & ERU_LOG_CH_ID_MSK) >> \
                                                   (uint32)ERU_LOG_CH_ID_POS);
      LogChId = (0x1UL << LogChId);

      /* Does the valid User ID have a callback function */
      /* [cover parentID={90C7924A-77DF-4a55-B6C5-BDC1D0F39FD3}]
       * User Id has a callback function or not
       * [/cover] */
      if (Mcu_17_Timer_DrivFuncCallbackLst\
          [(UserId - (uint8)ERU_BIT_SET)] != NULL_PTR)
      {
        /*[cover parentID={F535C781-0665-4860-AE94-3AD5AD5F7CD8}]
         *[/cover]*/
        Mcu_17_Timer_DrivFuncCallbackLst[(UserId - (uint8)ERU_BIT_SET)]\
                                                      (LogChId, EruPdrStatus);
      }
    }
    else
    {
      /* Extract the Interrupt status of the ERS channel */
      IrqStatus = MODULE_SCU.EIFR.U & EruEifrMask;

      /* Check if any interrupt is raised */
      /*[cover parentID={D4806232-40B4-4e41-98E5-D17838310946}][/cover]*/
      if (IrqStatus > 0x0U)
      {
        /* Get the Eicr register to be updated */
        /* Fetch the ERU channel ID */
        if((EruChOutputUnit & 0x1U) == 0U)
        {
          EruIgpPos = IFX_SCU_IGCR_IGP0_OFF;
        }
        else
        {
          EruIgpPos = IFX_SCU_IGCR_IGP1_OFF;
        }

        #if (MCU_SAFETY_ENABLE == STD_ON)
        /* Clear the software status flag */
        IrqServiceFlag = 0x0U;
        #endif

        do
        {
          /* Fetch the ERU channel ID */
          EruChannelId = MCU_GET_SETBIT_POS(IrqStatus);

          if ((Mcu_17_Eru_ChUserData[EruSrcId] & ERU_CH_OFFSET) == EruChannelId)
          {
            EruChOutputUnit = EruSrcId;
          }
          else
          {
            /* Move to the next Eru Channel */
            EruChOutputUnit = EruSrcId + ERU_OGU_OFFSET;
          }

          EruIgpVal = MODULE_SCU.IGCR[EruChOutputUnit / 2U].U;

          /* Check if the interrupts are enabled */
          /* [cover parentID={5ECF4832-2D8C-4a9e-910A-DFD2CB2CFE4A}]
          * Are interrupts enabled
          * [/cover] */
          if (0U != Mcal_GetBitAtomic(EruIgpVal, EruIgpPos, ERU_IGP_LEN))
          {
            /* Fetch the User data, User Id and Logical channel Id*/
            UserData = Mcu_17_Eru_ChUserData[EruChOutputUnit];
            UserId   = (uint8)((UserData & ERU_USER_ID_MSK) >> ERU_USER_ID_POS);

            /* Retrieve the user information from ERU channel user data table */
            LogChId  = ((UserData & ERU_LOG_CH_ID_MSK) >> \
                              (uint32)ERU_LOG_CH_ID_POS);

            EruChInputUnit = (uint8)(UserData & ERU_IN_CH_ID_MSK);

            /* Dummy for other modules */
            EruPdrStatus = 0x0U;

            /* Clear the interrupt flag for the ERU channel */
            /*[cover parentID={EC420D59-760C-4dea-9A19-E3781C17D2CD}][/cover]*/
            MODULE_SCU.FMR.U = (((uint32)ERU_BIT_SET << \
                                              (EruChInputUnit + ERU_FCSTART)));

            /* Does the valid User ID have a callback function */
            /* [cover parentID={FAEE5AC4-8954-483b-AB74-A53621C4D859}]
            * User Id has a callback function or not
            * [/cover] */
            if (Mcu_17_Timer_DrivFuncCallbackLst\
                [(UserId - (uint8)ERU_BIT_SET)] != NULL_PTR)
            {
              /* Status flags are redundant, hence always passed as 0 */
              /*[cover parentID={EBFC8203-77A6-4b69-B903-2FE53494824D}]
              *[/cover]*/
              Mcu_17_Timer_DrivFuncCallbackLst[(UserId - (uint8)ERU_BIT_SET)]\
              (LogChId, EruPdrStatus);
            }

            #if (MCU_SAFETY_ENABLE == STD_ON)
            /* Set the software status flag */
            IrqServiceFlag = 0x1U;
            #endif
          }

          /* Clear the interrupt flag of the channel */
          IrqStatus &= ~(1UL << EruChannelId);

        } while (IrqStatus > 0x0U);
        /* [cover parentID={F5125D8F-ED9B-4303-AC74-F4CE93E7BDB8}]
        * If Safety is Enabled
        * [/cover] */
        #if (MCU_SAFETY_ENABLE == STD_ON)
        if (IrqServiceFlag != 0x1U)
        {
          /* Report to Safety Error for spurious interrupt */
          /* [cover parentID={AD940EB9-75BB-4e22-A692-BE728055A0E1}]
          * Report Safety error for Spurious interrupt
          * [/cover] */
          Mcal_ReportSafetyError((uint16)MCU_MODULE_ID, MCU_MODULE_INSTANCE, \
                                MCU_ERU_OGU_ISR, MCU_E_INVALID_ISR);
        }
        #endif
      }
      /* [cover parentID={F5125D8F-ED9B-4303-AC74-F4CE93E7BDB8}]
      * If Safety is Enabled
      * [/cover] */
      #if (MCU_SAFETY_ENABLE == STD_ON)
      /* [cover parentID={0E64C647-83EF-4106-94C7-CEFDFB464520}]
      * If interrupt serviced for any ERU
      * [/cover] */
      else
      {
        /* Report to Safety Error for spurious interrupt */
        /* [cover parentID={AD940EB9-75BB-4e22-A692-BE728055A0E1}]
        * Report Safety error for Spurious interrupt
        * [/cover] */
        Mcal_ReportSafetyError((uint16)MCU_MODULE_ID, MCU_MODULE_INSTANCE, \
                              MCU_ERU_OGU_ISR, MCU_E_INVALID_ISR);
      }
      #endif
      /*[/cover] */
    }
  }
}

#define MCU_17_TIMERIP_STOP_SEC_CODE_FAST_ASIL_B_GLOBAL
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines. */
#include "Mcu_MemMap.h"

